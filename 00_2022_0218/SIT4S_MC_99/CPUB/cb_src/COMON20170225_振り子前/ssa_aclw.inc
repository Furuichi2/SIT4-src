;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		低速優先　内部減速処理		***
;	***		2015-11-17 減速選択		***
;	***						***
;	***						***
;	***						***
;	***************************************************

;	*******************************************
;	***					***
;	***	バックグランドでCALL		***
;	***	条件作成			***
;	***					***
;	*******************************************
;;;;;;;;;2016-04-18	.IMPORT		_PAR_ACCDN_MATH		;5 2015-11-18 加減速　減速優先[CE2]

_ACCLW_DATA_MAIN
	SUB_START

;;;;;;;;;2016-04-18
;;;;;;;;;	================ USE-CHECK-----------------
;;;;;;;;;	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
;;;;;;;;;	MOV.W	@R1,R0				;
;;;;;;;;;	CMP/EQ	#1,R0				;
;;;;;;;;;	BF	ACCLW_USECHK_EXT		;

	XOR	R2,R2
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;回転：
	TST_BIT_OF ACCLW_USECHK_100			;no use

	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1SGL+_W1CNT+_W1OPT+_W1INC,R0		;安全、連続、オプション,INC
	TST_BIT_OF ACCLW_USECHK_100			;no use


	MOV.L	#_LINK_1ROT_PLS,R1			;
	MOV.L	@R1,R4					;
	MOV.L	#_ACCLW_GEN_MAX_LNG,R1			;最大速度時の減速距離
	MOV.L	R4,@R1					;(とりあえず360度分)


	MOV.B	#BIT0,R2				;

ACCLW_USECHK_100
	MOV.L	#_ACCLW_USE_CONF,R1			;
	MOV.W	R2,@R1					;

;;;;;;;;;ACCLW_USECHK_EXT

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	起動時CALL(運転釦ON,タイマ後,1サイクル)	***
;	***						***
;	***************************************************
_API_ACCLW_DRV_START1
	SUB_START


	FAR_JSR	#_API_ACCLW_DRV_START2,R0	;
	FAR_JSR	#_API_ACCLW_DRV_WORK_CLR,R0	;デバック用

	SUB_END
	M_RTS

;	----------- ﾃﾞﾊﾞｯｸ用にｸﾘｱ------------
_API_ACCLW_DRV_WORK_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCLW_GET_STEP_NO,R1		;//BIT1=1時の対象行程
	MOV.W	R0,@R1				;
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;//BIT1=1時の対象速度
	MOV.L	R0,@R1				;ｸﾘｱ不要:ﾃﾞﾊﾞｯｸ用
	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;//出力速度
	MOV.L	R0,@R1				;ｸﾘｱ不要:ﾃﾞﾊﾞｯｸ用
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	起動時CALL(減速完了,次の減速演算)	***
;	***						***
;	***************************************************
_API_ACCLW_DRV_START2
	SUB_START

	MOV.L	#_ACCLW_USE_CONF,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF API_ACCLW_DRVSTR2_EXT		;

	MOV.B	#BIT0,R0			;
	MOV.L	#_ACCLW_CALC_FLG,R1		;
	MOV.W	R0,@R1				;[BIT6,BIT7CLR BIT0=1]

API_ACCLW_DRVSTR2_EXT

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
;//

_API_ACCLW_DRV_STOP
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCLW_CALC_FLG,R1		;
	MOV.W	R0,@R1				;
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
_ACCLW_CTRL_CALC			;2015-11-17 減速選択
	SUB_START

	MOV.L	#_ACCLW_SET_SPD,R1				;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	R2,@R1						;

	MOV.W	#D'1000,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_ACCLW_REAL_SPD1MS,R1				;1ms差分
	MOV.L	R2,@R1						;


	MOV.L	#_ACCLW_CALC_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_ON ACCLW_CTRLCALC_100	;[起動中]
	M_BRA	ACCLW_CTRLCALC_800

ACCLW_CTRLCALC_100
	TST	#BIT7,R0		;
	TST_BIT_OF ACCLW_CTRLCALC_120	;
	M_BRA	ACCLW_CTRLCALC_800	;演算不要:再起動かかるまで演算しなくていい

ACCLW_CTRLCALC_120
	TST	#BIT6,R0		;
	TST_BIT_ON ACCLW_CTRLCALC_200	;[減速中か? YES]


;	------- 減速開始条件チェック---------

	FAR_JSR	#_ACCLW_GEN_START_CONF_CHECK,R0

	MOV.L	#_ACCLW_CALC_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_ON ACCLW_CTRLCALC_300		;
	M_BRA	ACCLW_CTRLCALC_800		;



;	------------- 減速中-----------
ACCLW_CTRLCALC_200
;	------- 減速終了条件チェック---------
	FAR_JSR	#_ACCLW_GEN_END_CONF_CHECK,R0
	TST	R0,R0				;
	TST_BIT_ON ACCLW_CTRLCALC_300		;減速中

	FAR_JSR	#_API_ACCLW_DRV_START2,R0	;減速完了:次を探す
	M_BRA	ACCLW_CTRLCALC_800		;

ACCLW_CTRLCALC_300
	FAR_JSR	#_ACCLW_GEN_OUTSPD_CALC,R0	;
	M_BRA	ACCLW_CTRLCALC_900				;


ACCLW_CTRLCALC_800				;
	MOV.L	#_ACCLW_SET_SPD,R1		;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	@R1,R2				;
	M_BRA	ACCLW_CTRLCALC_EXT		;

ACCLW_CTRLCALC_900				;
	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;	//出力速度
	MOV.L	@R1,R2				;

ACCLW_CTRLCALC_EXT				;


	MOV.L	#_ACCLW_CALC_FLG,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB255,R1	;255
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	減速終了条件			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:減速終了 1:減速中
;	INPUT:R2(設定速度:符号無し)
_ACCLW_GEN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCLW_SET_SPD,R1		;//INPUT モーション演算部からの速度 (オーバライド前)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;//BIT1=1時の対象速度
	MOV.L	@R1,R3				;
	CMP/GE	R2,R3				;R2≦R3(R2=R3)
	BT	ACCLW_GEN_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;まだ減速継続
	M_BRA	ACCLW_GEN_END_CONFCHK_300	;

ACCLW_GEN_END_CONFCHK_100
	XOR	R0,R0
ACCLW_GEN_END_CONFCHK_300

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
_ACCLW_GEN_OUTSPD_CALC
	SUB_START
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;
	MOV.L	@R1,R3				;

	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;出力速度
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

_ACCLW_GEN_START_CONF_CHECK
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;

	TST	R0,R0				;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_050	;
	M_BRA	ACCLW_GEN_START_CONFCHK_EXT	;

ACCLW_GEN_START_CONFCHK_050
	MOV.L	#_CPOS_STEP_MAX,R1		;
	MOV.W	@R1,R5				;
	ADD	#1,R5				;[MAX:R5]
	CMP/GE	R5,R0				;最終行程
	BF	ACCLW_GEN_START_CONFCHK_100	;
	M_BRA	ACCLW_GEN_START_CONFCHK_EXT	;R5=R0最終行程

;	---------------------------------------
ACCLW_GEN_START_CONFCHK_100
	MOV	R0,R8				;行程

	SUB	R0,R5				;1~98
	MOV.W	#D'10,R4			;先読み10段まで[100段はかわいそう]
	CMP/GE	R5,R4				;R5≦R4
	BT	ACCLW_GEN_START_CONFCHK_120	;
	MOV	R4,R5				;
ACCLW_GEN_START_CONFCHK_120
;	現状の行程～最大１０段の中で
;	停止行程または戻り行程終了まで検索を行う.
;
;	行程1の場合
;	INF1:行程1を参照
;	CHG :行程1を参照
;	速度:行程2を参照

	ADD	#-1,R0				;
	SHLL2	R0				;*4
	MOV.L	#_CPOS_SDAT1_SPD,R13		;4B
	ADD	R0,R13				;
	ADD	#4,R13				;速度は次の段の速度

	MOV.L	#_CPOS_SDAT1_INF1,R14		;4B
	ADD	R0,R14				;

	SHLL	R0
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R12	;切替位置8B
	ADD	R0,R12				;


ACCLW_GEN_START_CONFCHK_200LOP:			;
	PUSH_REG1 R5

	MOV.L	@R14,R0				;INF
	TST	#BIT0,R0			;連続か?
	TST_BIT_OF ACCLW_GEN_START_CONFCHK_550	;この行程は停止なので終了

;	(------- 方向判別は不要R0.BIT1--------)
;	--------- 連続-----------
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;ﾘｱﾙﾀｲﾑ目標位置
	MOV.L	@(0,R12),R1						;
	MOV.L	@(4,R12),R2						;設定位置
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2-R5,R6

	CMP/PZ	R1				;
	BT	ACCLW_GEN_START_CONFCHK_250	;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R0	;|R1,R2|
ACCLW_GEN_START_CONFCHK_250:			;


	TST	R1,R1					;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_550		;まだ距離が十分にある

	MOV.L	#_ACCLW_REAL_SPD1MS,R5			;
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
	CMP/PL	R2	
	BT	ACCLW_GEN_START_CONFCHK_280		;
	MOV.W	#1,R2					;
ACCLW_GEN_START_CONFCHK_280:				;

	MOV.L	#_ACCLW_GEN_MAX_LNG,R5			;最大速度時の減速距離
	MOV.L	@R5,R4					;
	CMP/HI	R4,R2					;R4<R2
	BT	ACCLW_GEN_START_CONFCHK_550		;まだ距離が十分にある

;[速度が高い場合評価をやめる]

;	現在速度^2≧２α(S－現在速度/1000)+指定段数速度^2
	PUSH_REG1 R8	;行程
	PUSH_REG1 R12	;POS
	PUSH_REG1 R13	;SPD
	PUSH_REG1 R14	;INF1
	MOV.L	#_POSCTL_RL_SPD,R4					;
	MOV.L	@R4,R9							;

	MOV.L	@R13,R10						;SPD
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
	CMP/GE	R9,R10					;R9(現在速度)≦R10(設定速度)
	BT	ACCLW_GEN_START_CONFCHK_400		;

	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0		;

ACCLW_GEN_START_CONFCHK_400:			;


	POP_REG1 R14
	POP_REG1 R13
	POP_REG1 R12
	POP_REG1 R8

	TST	R0,R0
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_500				;減速すべき
	M_BRA	ACCLW_GEN_START_CONFCHK_580				;


;	---------------- 減速開始する[減速スタートする]、演算はやめる-----------
ACCLW_GEN_START_CONFCHK_500:					;
	MOV.L	@R13,R2						;NEW SPEED
	MOV.L	#_ACCLW_GET_SET_SPD,R1				;
	MOV.L	R2,@R1						;
	MOV.L	#_ACCLW_GET_STEP_NO,R1				;//BIT1=1時の対象行程
	MOV.W	R8,@R1						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCLW_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1	;[減速するから演算はやめるR0=BIT0]


;	---------------- 停止行程なのでやめる----------------
ACCLW_GEN_START_CONFCHK_550:			;
	MOV.B	#BIT0,R0			;
	M_BRA	ACCLW_GEN_START_CONFCHK_600	;

;	--------------- 次を演算する-------------------------
ACCLW_GEN_START_CONFCHK_580:			;
	XOR	R0,R0				;
ACCLW_GEN_START_CONFCHK_600:			;

	POP_REG1 R5
	ADD	#-1,R5				;
	TST	R5,R5				;
	TST_BIT_OF ACCLW_GEN_START_CONFCHK_EXT	;
	TST	R0,R0				;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_EXT	;終わり
	ADD	#4,R13				;SPD
	ADD	#4,R14				;INF
	ADD	#8,R12				;POS
	ADD	#1,R8				;行程[不要だが]
	M_BRA	ACCLW_GEN_START_CONFCHK_200LOP	;



ACCLW_GEN_START_CONFCHK_EXT
	SUB_END
	M_RTS
