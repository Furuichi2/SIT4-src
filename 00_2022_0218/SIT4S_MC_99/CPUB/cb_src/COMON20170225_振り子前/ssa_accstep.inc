;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		各段前/後変則指定処理		***
;	***		2016-04-18 前・後選択		***
;	***		(加速でも減速でも)		***
;	***						***
;	***						***
;	***************************************************

;	*******************************************
;	***					***
;	***	バックグランドでCALL		***
;	***	条件作成			***
;	***					***
;	*******************************************

_ACCST_DATA_MAIN
	SUB_START


	XOR	R2,R2
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;回転：
	TST_BIT_OF ACCST_USECHK_100			;no use

	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1SGL+_W1CNT+_W1OPT+_W1INC,R0		;安全、連続、オプション,INC
	TST_BIT_OF ACCST_USECHK_100			;no use

	MOV.L	#_LINK_1ROT_PLS,R1			;
	MOV.L	@R1,R4					;
	MOV.L	#_ACCST_GEN_MAX_LNG,R1			;最大速度時の減速距離
	MOV.L	R4,@R1					;(とりあえず360度分)

	MOV.B	#BIT0,R2				;

ACCST_USECHK_100
	MOV.L	#_ACCST_USE_CONF,R1			;
	MOV.W	R2,@R1					;



	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	起動時CALL(運転釦ON,タイマ後,1サイクル)	***
;	***						***
;	***************************************************
_API_ACCST_DRV_START1
	SUB_START


	FAR_JSR	#_API_ACCST_DRV_START2,R0	;
	FAR_JSR	#_API_ACCST_DRV_WORK_CLR,R0	;デバック用

	SUB_END
	M_RTS

;	----------- ﾃﾞﾊﾞｯｸ用にｸﾘｱ------------
_API_ACCST_DRV_WORK_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCST_GET_SET_SPD,R1		;//BIT1=1時の対象速度
	MOV.L	R0,@R1				;ｸﾘｱ不要:ﾃﾞﾊﾞｯｸ用
	MOV.L	#_ACCST_OUT_SET_SPD,R1		;//出力速度
	MOV.L	R0,@R1				;ｸﾘｱ不要:ﾃﾞﾊﾞｯｸ用
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	起動時CALL(減速完了,次の減速演算)	***
;	***						***
;	***************************************************
_API_ACCST_DRV_START2
	SUB_START

	MOV.L	#_ACCST_USE_CONF,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF API_ACCST_DRVSTR2_EXT		;

	MOV.B	#BIT0,R0				;
	MOV.L	#_ACCST_CALC_FLG,R1			;
	MOV.W	R0,@R1					;[BIT6,BIT7CLR BIT0=1]


API_ACCST_DRVSTR2_EXT

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	位置決め中断時CALL		***
;	***	位置決め停止タイマ時CALL	***
;	***	異常時CALL			***
;	***					***
;	*******************************************
;//BIT0:起動[API]
;//BIT6:[減速開始]
;//BIT7:演算完了[停止行程まで演算不要：もう低速設定がない]:予備

_API_ACCST_DRV_STOP
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCST_CALC_FLG,R1		;
	MOV.W	R0,@R1				;

;	---------行程番号-------
	XOR	R0,R0					;
	MOV.L	#_ACCST_GET_STEP_NO,R1			;//BIT1=1時の対象行程
	MOV.W	R0,@R1					;

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	1msecでCALL	メイン		***
;	***					***
;	*******************************************
;	2015-11-17 減速選択
;	[オーバライド前にCALL]
;	Input  R2:設定速度
;	Output R2:設定速度相当
;	PAR_ACCDN_MATH=1 減速優先演算
;
_ACCST_CTRL_CALC			;2015-11-17 減速選択
	SUB_START

	MOV.L	#_ACCST_SET_SPD,R1				;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	R2,@R1						;

	MOV.W	#D'1000,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_ACCST_REAL_SPD1MS,R1				;1ms差分
	MOV.L	R2,@R1						;

	MOV.L	#_ACCST_CALC_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_ON ACCST_CTRLCALC_100	;[起動中]
	M_BRA	ACCST_CTRLCALC_800

ACCST_CTRLCALC_100
;	---------- 行程変更チェック----------------------------------
;	[行程変更があれば=ACCST_CALC_FLG=BIT0(BIT6,BIT7をｸﾘｱする)]	;
	MOV.L	#_INT_POS_CTL_STEP,R1					;//内部制御工程1~11
	MOV.W	@R1,R3							;
	TST	R3,R3							;
	TST_BIT_OF ACCST_CTRLCALC_800					;ありえない(CALC_FLG=0)

	FAR_JSR	#_ACCST_CHGSTEP_GET_MAKE,R0				;(停止,最終行程ではやらない.ACCST_ACC_MATH_SEL=0)

;	-------------------------------------------------------------
	MOV.L	#_ACCST_ACC_MATH_SEL,R1					;//1STEP分
	MOV.W	@R1,R0							;
	TST	#BIT0,R0						;
	TST_BIT_OF ACCST_CTRLCALC_800					;(後加速,減速の場合は何もしない)

	MOV.L	#_ACCST_CALC_FLG,R1					;
	MOV.W	@R1,R0						;
	TST	#BIT7,R0					;
	TST_BIT_ON ACCST_CTRLCALC_800				;演算不要:行程変更が変わるまで演算しなくていい

	TST	#BIT6,R0		;
	TST_BIT_ON ACCST_CTRLCALC_200	;[減速or加速中か YES]

;	------- 減速/加速開始条件チェック---------
	FAR_JSR	#_ACCST_UPDN_START_CONF_CHECK,R0		;この行程だけ見ればいい.ACCST_ACC_MATH_SEL.BIT1=0/1(減速加速)

	MOV.L	#_ACCST_CALC_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT6,R0				;
	TST_BIT_OF ACCST_CTRLCALC_800			;演算不要

;	------------- 減速中-----------
ACCST_CTRLCALC_200

;	------- 加速・減速終了条件チェック---------
	FAR_JSR	#_ACCST_UPDN_END_CONF_CHECK,R0
	TST	R0,R0								;
	TST_BIT_ON ACCST_CTRLCALC_300						;減速/加速演算継続
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT7,WKREG=R1	;
	M_BRA	ACCST_CTRLCALC_800						;演算終了:

ACCST_CTRLCALC_300
	FAR_JSR	#_ACCST_UPDN_OUTSPD_CALC,R0	;
	M_BRA	ACCST_CTRLCALC_900		;

;	----------- R2を設定値に戻す----------------
ACCST_CTRLCALC_800				;
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	@R1,R2				;
	M_BRA	ACCST_CTRLCALC_EXT		;

;	---------  演算中なので演算結果を出力する---------
ACCST_CTRLCALC_900				;
	MOV.L	#_ACCST_OUT_SET_SPD,R1		;	//出力速度
	MOV.L	@R1,R2				;

ACCST_CTRLCALC_EXT				;

	MOV.L	#_ACCST_ACC_MATH_SEL,R1		;//1STEP分
	MOV.W	@R1,R0				;
	AND	#BIT1+BIT0,R0			;
	SHLL8	R0				;
	MOV	R0,R4
	MOV.L	#_ACCST_CALC_FLG,R1		;
	MOV.W	@R1,R0				;BIT0,BIT6,BIT7
	AND	#BIT0+BIT6+BIT7,R0		;
	OR	R4,R0				;BIT0,BIT6,BIT7,BIT8,BIT9
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB255,R1	;255
	MOV.W	R0,@R1				;

;	------- output [R2] --------------

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***	加速または減速終了条件		***
;	***					***
;	***					***
;	*******************************************
;	前変則でのみ実行
;	OUTPUT R0 	R0=0:加速,減速終了
;			R0=1:加速中,減速中
;
_ACCST_UPDN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_ACC_MATH_SEL,R1		;//1STEP分
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON ACCST_UPDN_END_CONFCHK_100	;BIT1=1減速

	FAR_JSR	#_ACCST_UP_END_CONF_CHECK,R0	;
	M_BRA	ACCST_UPDN_END_CONFCHK_200	;

ACCST_UPDN_END_CONFCHK_100
	FAR_JSR	#_ACCST_DN_END_CONF_CHECK,R0	;
ACCST_UPDN_END_CONFCHK_200
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	減速終了条件			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:減速終了 1:減速中
;	INPUT:R2(設定速度:符号無し)
_ACCST_DN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCST_GET_SET_SPD,R1		;対象の設定速度
	MOV.L	@R1,R3				;
	CMP/GE	R2,R3				;R2(ﾓｰｼｮﾝ演算部演算結果)≦R3(設定)(R2=R3)
	BT	ACCST_DN_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;まだ減速継続
	M_BRA	ACCST_DN_END_CONFCHK_300	;

ACCST_DN_END_CONFCHK_100
	XOR	R0,R0
ACCST_DN_END_CONFCHK_300

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	加速終了条件			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:加速終了 1:加速中
;	INPUT:R2(設定速度:符号無し)
_ACCST_UP_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCST_GET_SET_SPD,R1		;対象の設定速度
	MOV.L	@R1,R3				;
	CMP/GE	R3,R2				;R3(対象の設定速度)≦R2(モーション演算部の速度)(R2=R3)
	BT	ACCST_UP_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;まだ加速継続
	M_BRA	ACCST_UP_END_CONFCHK_300	;

ACCST_UP_END_CONFCHK_100
	XOR	R0,R0
ACCST_UP_END_CONFCHK_300

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	行程切替時			***
;	***					***
;	*******************************************
;	INPUT R3: INT_POS_CTL_STEP 0以外
;	(停止,最終行程ではやらない.ACCST_ACC_MATH_SEL=0)
;
_ACCST_CHGSTEP_GET_MAKE
	SUB_START

	MOV.L	#_ACCST_GET_STEP_NO,R5			;//BIT1=1時の対象行程
	MOV.W	@R5,R0					;
	MOV.W	R3,@R5					;
	CMP/EQ	R3,R0					;
	BT	ACCST_CHGSTEP_GETINF_EXT		;同じ

	PUSH_REG1 R3
	FAR_JSR	#_API_ACCST_DRV_START2,R0		;
	POP_REG1 R3
	
;	---------------------------------------------
	XOR	R6,R6
	MOV.L	#_CPOS_STEP_MAX,R1			;
	MOV.W	@R1,R0					;
	ADD	#1,R0					;[MAX:R0]
	CMP/GE	R0,R3					;最終行程
	BT	ACCST_CHGSTEP_GETINF_SET		;最終行程は固定

	MOV.L	#_CPOS_SDAT1_INF1,R14			;4B
	MOV	R3,R4					;
	ADD	#-1,R4					;
	SHLL2	R4					;
	ADD	R4,R14					;
	MOV.L	@R14,R0					;
	TST	#BIT0,R0				;連続か?
	TST_BIT_OF ACCST_CHGSTEP_GETINF_SET		;演算しない

;	-----------------------------------------------
	MOV.L	#_SET1_MOT_INF,R5			;
	MOV	R3,R4
	ADD	#-1,R4					;
	SHLL	R4					;
	ADD	R4,R5					;
	MOV.W	@R5,R0					;
	TST	#BIT1,R0				;
	TST_BIT_ON ACCST_CHGSTEP_GETINF_100		;BIT1=1[後変則]:通常ソフト(R6=0)
	MOV.B	#BIT0,R6				;BIT1=0[前変則]:行程切替前変則
ACCST_CHGSTEP_GETINF_100				;
;	---------------------------------------------------

ACCST_CHGSTEP_GETINF_SET
	MOV.L	#_ACCST_ACC_MATH_SEL,R1			;//1STEP分
	MOV.W	R6,@R1					;指定されている行程の終わり方の抽出
							;BIT0:SET,BIT1=CLR()
ACCST_CHGSTEP_GETINF_EXT

	SUB_END
	M_RTS





;	*******************************************
;	***					***
;	***	出力演算			***
;	***	通常の減速演算を使用するので	***
;	***	今のところ演算不要		***
;	***					***
;	*******************************************
;	出力速度演算
_ACCST_UPDN_OUTSPD_CALC
	SUB_START
	MOV.L	#_ACCST_GET_SET_SPD,R1		;対象の設定速度
	MOV.L	@R1,R3				;

	MOV.L	#_ACCST_OUT_SET_SPD,R1		;出力速度
	MOV.L	R3,@R1				;

	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***	判定用に現在速度・現在加速度の算出	***
;	***	[オーバライド後で演算する]		***
;	***						***
;	***************************************************
;	*******************************************
;	***					***
;	***	現在の行程から減速行程を探す	***
;	***					***
;	*******************************************
;	S4b	CPOS_SDAT1_CNTSTEP[100+10];		//SETX-->起動時COPY
;	S4b	CPOS_SDAT1_INF1[100+10];		//SETX-->起動時COPY
;	S4b	CPOS_SDAT1_CHGAPOS[2*(100+10)];		//起動時,その他で演算 8byte data
;	S4b	CPOS_SDAT1_STPAPOS[2*(100+10)];		//起動時,その他で演算 8byte data
;

_ACCST_UPDN_START_CONF_CHECK
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_050	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT	;

ACCST_UPDN_START_CONFCHK_050
	MOV.L	#_CPOS_STEP_MAX,R1		;
	MOV.W	@R1,R5				;
	ADD	#1,R5				;[MAX:R5]
	CMP/GE	R5,R0				;最終行程
	BF	ACCST_UPDN_START_CONFCHK_100	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT	;R5=R0最終行程

;	---------------------------------------
ACCST_UPDN_START_CONFCHK_100
	MOV	R0,R8				;行程

;	行程1の場合
;	INF1:行程1を参照
;	CHG :行程1を参照
;	速度:行程2を参照

	ADD	#-1,R0				;
	SHLL2	R0				;*4
	MOV.L	#_CPOS_SDAT1_SPD,R13		;4B
	ADD	R0,R13				;
	MOV.L	@R13,R7				;現段の設定速度
	ADD	#4,R13				;次段の設定速度(評価対象目標速度)

	MOV.L	#_CPOS_SDAT1_INF1,R14		;4B
	ADD	R0,R14				;

	SHLL	R0
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R12	;切替位置8B
	ADD	R0,R12				;



	MOV.L	@R14,R0				;INF
	TST	#BIT0,R0			;連続か?
	TST_BIT_OF ACCST_UPDN_START_CONFCHK_550	;この行程は停止なので終了

;	(------- 方向判別は不要R0.BIT1--------)
;	--------- 連続-----------
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;ﾘｱﾙﾀｲﾑ目標位置
	MOV.L	@(0,R12),R1						;
	MOV.L	@(4,R12),R2						;設定位置
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2-R5,R6

	CMP/PZ	R1				;
	BT	ACCST_UPDN_START_CONFCHK_250	;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R0	;|R1,R2|=設定-現在目標位置
ACCST_UPDN_START_CONFCHK_250:			;


	TST	R1,R1					;
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_580		;まだ距離が十分にある

	MOV.L	#_ACCST_REAL_SPD1MS,R5			;
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
	CMP/PL	R2	
	BT	ACCST_UPDN_START_CONFCHK_280		;
	MOV.W	#1,R2					;
ACCST_UPDN_START_CONFCHK_280:				;R2:残り距離

	MOV.L	#_ACCST_GEN_MAX_LNG,R5			;最大速度時の減速距離(100->0 0->100%に必要な距離)
	MOV.L	@R5,R4					;
	CMP/HI	R4,R2					;R4<R2
	BT	ACCST_UPDN_START_CONFCHK_580		;まだ距離が十分にある

	MOV.L	@R13,R0					;次の段
	CMP/EQ	R0,R7					;現行の段
	BT	ACCST_UPDN_START_CONFCHK_540		;

	CMP/GE	R7,R0					;
	BT	ACCST_UPDN_START_CONFCHK_300		;加速

;	-------------- 減速 -------------
;INPUT R13:ターゲット設定 R1,R2:距離
	FAR_JSR	#_ACCST_DN_START_CONF_CHECK,R0
	TST	R0,R0
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_500				;減速すべき
	M_BRA	ACCST_UPDN_START_CONFCHK_580				;まだ減速は不要

ACCST_UPDN_START_CONFCHK_300:							;
;	-------------- 加速 ---------------
	FAR_JSR	#_ACCST_UP_START_CONF_CHECK,R0
	TST	R0,R0
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_520				;加速すべき
	M_BRA	ACCST_UPDN_START_CONFCHK_580				;まだ加速は不要



;	---------------- 減速開始する[減速スタートする]、演算はやめる-----------
ACCST_UPDN_START_CONFCHK_500:								;
	MOV.L	@R13,R2									;設定速度NEW SPEED
	MOV.L	#_ACCST_GET_SET_SPD,R1							;
	MOV.L	R2,@R1									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1		;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_ACC_MATH_SEL,LG=W,BIT=BIT1,WKREG=R1		;<<<<<<<<減速 これは上で評価>>>>>>>
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT						;


;	---------------- 加速開始する[加速スタートする]、演算はやめる-----------
ACCST_UPDN_START_CONFCHK_520:								;
	MOV.L	@R13,R2									;設定速度NEW SPEED
	MOV.L	#_ACCST_GET_SET_SPD,R1							;
	MOV.L	R2,@R1									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1		;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_ACCST_ACC_MATH_SEL,LG=W,BIT=~BIT1,WKREG=R1	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT						;

;	---------------- 停止行程なのでやめる----------------
ACCST_UPDN_START_CONFCHK_540:			;
	NOP					;ここははじくべき
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT
ACCST_UPDN_START_CONFCHK_550:			;
	NOP					;ここははじいているのでこない
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT
;	----------まだその判定の位置にない------------
ACCST_UPDN_START_CONFCHK_580:			;
ACCST_UPDN_START_CONFCHK_EXT
	SUB_END
	M_RTS







;	***********************************************************
;	***							***
;	***	減速すべき設定で減速すべき範囲内でR0 !=0	***
;	***							***
;	***********************************************************
;	ANS R0!=0 減速すべき位置
_ACCST_DN_START_CONF_CHECK
	SUB_START

;[速度が高い場合評価をやめる]
;	現在速度^2≧２α(S－現在速度/1000)+指定段数速度^2

;;不要	PUSH_REG1 R8	;行程
;;不要	PUSH_REG1 R12	;POS
;;不要	PUSH_REG1 R13	;SPD
;;不要	PUSH_REG1 R14	;INF1
	MOV.L	#_POSCTL_RL_SPD,R4					;
	MOV.L	@R4,R9							;

	MOV.L	@R13,R10						;SPD：次段設定
	PUSH_REG1 R1							;
	PUSH_REG1 R2							;
	MOV	R10,R2							;
	FAR_JSR	#_OVER_LIDE_SPD_CALC,R0					;INPUT R2-OUTPUT R2
	MOV	R2,R10							;
	POP_REG1 R2							;
	POP_REG1 R1							;

	MOV.L	#_POSCTL_SV_DN_ACC,R4					;500,000/1000
	MOV.L	@R4,R11							;ｵｰﾊﾞﾗｲﾄﾞ後
									;Input R1,R2 距離
									;Input R9    現在速度
									;Input R10   ｵﾌｾｯﾄ速度[指定段数速度]
									;Input R11   減速距離

	XOR	R0,R0
	CMP/GE	R9,R10							;R9(現在速度)≦R10(設定速度):不要
	BT	ACCST_DN_START_CONFCHK_400				;

;	***	Input R1,R2(残り距離)		***
;	***	Input R9:SPEED  DATA		***
;	***	Input R10:OFFSET SPEED		***
;	***	Input R11:ACC_LATE		***
	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0				;ANS R0!=0 減速

ACCST_DN_START_CONFCHK_400:						;


;;不要	POP_REG1 R14
;;不要	POP_REG1 R13
;;不要	POP_REG1 R12
;;不要	POP_REG1 R8

	SUB_END
	M_RTS


;	***********************************************************
;	***							***
;	***	加速すべき設定で加速すべき範囲内でR0 !=0	***
;	***							***
;	***********************************************************
;	ANS R0!=0 減速すべき位置
_ACCST_UP_START_CONF_CHECK
	SUB_START

;[速度が高い場合評価をやめる]
;	現在速度^2≧２α(S－現在速度/1000)+指定段数速度^2

;;不要	PUSH_REG1 R8	;行程
;;不要	PUSH_REG1 R12	;POS
;;不要	PUSH_REG1 R13	;SPD
;;不要	PUSH_REG1 R14	;INF1
	MOV.L	#_POSCTL_RL_SPD,R4					;
	MOV.L	@R4,R9							;

	MOV.L	@R13,R10						;SPD：次段設定
	PUSH_REG1 R1							;
	PUSH_REG1 R2							;
	MOV	R10,R2							;
	FAR_JSR	#_OVER_LIDE_SPD_CALC,R0					;INPUT R2-OUTPUT R2
	MOV	R2,R10							;
	POP_REG1 R2							;
	POP_REG1 R1							;

	MOV.L	#_POSCTL_SV_UP_ACC,R4					;500,000/1000
	MOV.L	@R4,R11							;ｵｰﾊﾞﾗｲﾄﾞ後
									;Input R1,R2 距離
									;Input R9    現在速度
									;Input R10   ｵﾌｾｯﾄ速度[指定段数速度]
									;Input R11   減速距離

	XOR	R0,R0
	CMP/GE	R10,R9							;R10(設定速度)≦R9(現在速度):不要
	BT	ACCST_UP_START_CONFCHK_400				;

;	***	Input R1,R2(残り距離)		***
;	***	Input R9:SPEED  DATA		***
;	***	Input R10:OFFSET SPEED		***
;	***	Input R11:ACC_LATE		***

	MOV	R10,R0
	MOV	R9,R10
	MOV	R0,R9							;
	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0				;ANS R0!=0 減速

ACCST_UP_START_CONFCHK_400:						;


;;不要	POP_REG1 R14
;;不要	POP_REG1 R13
;;不要	POP_REG1 R12
;;不要	POP_REG1 R8

	SUB_END
	M_RTS






;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	レジスタはR0以外破壊しないこと
;	R0=0/R0=1(前減速,前加速)
;	input R5:行程番号
;
_ACCST_CHGSPD_LIMIT_INFO_LOAD
	SUB_START
	PUSH_REG1 R1
	PUSH_REG1 R2

	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;回転：
	TST_BIT_OF ACCST_CHGSPD_LMT_INF_LD_200		;回転ではない

	MOV.L	#_MOTION_SPD_CHKCNT,R1
	MOV.W	@R1,R0					;1段目=0 2段目=4 3段目=8,,,
	MOV.L	#_SET1_MOT_INF,R1			;評価の前の段が前変速か
	SHLL	R0					;
	ADD	R0,R1					;
	MOV.W	@R1,R0					;
	TST	#BIT1,R0				;
	TST_BIT_ON ACCST_CHGSPD_LMT_INF_LD_200		;ON:後変速
	M_BRA	ACCST_CHGSPD_LMT_INF_LD_300		;OFF:前変速



;	--------------- 通常の評価を実施する---------------
ACCST_CHGSPD_LMT_INF_LD_200				;
	XOR	R0,R0
	M_BRA	ACCST_CHGSPD_LMT_INF_LD_END		;


;	--------------- 前変則だから評価不要-----------
ACCST_CHGSPD_LMT_INF_LD_300				;
	MOV.B	#1,R0					;
ACCST_CHGSPD_LMT_INF_LD_END				;

	POP_REG1 R2
	POP_REG1 R1


	SUB_END
	M_RTS


