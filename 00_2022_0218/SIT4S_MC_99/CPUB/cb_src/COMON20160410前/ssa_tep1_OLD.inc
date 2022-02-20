;	***********************************
;	***				***
;	***	手動パルサコントロール	***
;	***				***
;	***********************************
;	両手offで終了
;	符号チェンジ
;	符号チェンジによる停止指令
;	停止待ち
;	
;	+方向動作中にｶｳﾝﾀが"-1以下"になったら+動作完了後"-"に戻す：ｶｳﾝﾀの更新,0CLRは行なわない
;	-方向動作中にｶｳﾝﾀが"+1以上"になったら-動作完了後"+"に進める:
;
;	(1)DIRECTIONﾌﾗｸﾞとｶｳﾝﾀを比較する
;	(2-1)同じ方向にﾊﾟﾙｽが増えたらｶｳﾝﾀ→位置決めLSIに足しこむ.ｶｳﾝﾀ=0とする
;	(2-2)逆方向に増えたらﾊﾟﾙｽ払い出しを待つ
;BIT1	(>3-1)残りﾊﾟﾙｽ=0になったら指令をOFFする。：：：ｽﾃｯﾌﾟｼｰｹﾝｽ開始
;BIT2	(>3-2)位置決め完了したら10msecWAITする
;BIT6	(>3-3)起動演算を行なう
;
;	TEP_STEP_FLG
;		.BIT0 払出完了
;		.BIT1 5msecWAIT
;		
;
;	plsData-->start-on
	.EXPORT	_TEP_FLG_CLR
	.EXPORT	_TEPA_START_CHK			;
	.EXPORT	_TEPA_PLSCNT_CLR		;
	.EXPORT	_TEPA_PLSCNT_CHK		;

	.IMPORT	_PAR_TEP_WATTIM		;3 1~50msec
	.IMPORT	_PAR_TEP_BEFPLS		;4 10pls
	.IMPORT	_PAR_TEP_MINSPD		;

	.IMPORT	_SH4toSH2_TEPSIG	;
	.IMPORT	_SH2toSH4_TEPSIG	;


_DND_TEP_STEP_CTRL:
	SUB_START

;	-------- 2013-06-05 -----------------------------
	DN_TIME LG=W,MEM_ADR=_TEP_CNTSMP_TIM,WKREG1=R1,WKREG2=R2	;定周期


	FAR_JSR	#_TEP_ADD_PLS_MAK,R0		;

	MOV.L	#_TEP_STEP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF DND_TEPSTEPCTL_020		;
	M_BRA	DND_TEPSTEPCTL_400		;
DND_TEPSTEPCTL_020:

	TST	#BIT0,R0			;
	TST_BIT_ON DND_TEPSTEPCTL_200		;

	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0	;
	FAR_JSR	#_LOD_POS_STS_REG,R1		;
	TST	#BIT2,R0			;停止?
	TST_BIT_OF DND_TEPSTEPCTL_180		;NO 停止中? 0:払出中 1:停止 

	FAR_JSR	#_TEP_CPUAB_HAND_CLR,R0		;

;	------ ILDE --------
	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	MOV.L	@R1,R2				;
	TST	R2,R2				;
	TST_BIT_OF DND_TEPSTEPCTL_180		;
	M_BRA	DND_TEPSTEPCTL_100		;起動

;;	MOV.L	#_POS_DRV_DIRECT,R1		;
;;	MOV.W	@R1,R0				;
;;	CMP/PZ	R2				;
;;	BF	DND_TEPSTEPCTL_050		;"逆回転"
;;	TST	#BIT0,R0			;
;;	TST_BIT_ON DND_TEPSTEPCTL_100		;正転状態で"-"のﾊﾟﾙｽがきた。一旦停止させる
;;
;;	FAR_JSR	#_TEP_ADD_OBJMAK,R0		;"+"
;;	FAR_JSR	#_TEP_START_INIT1,R0		;
;;	MOV.L	#_POS_DRV_DIRECT,R1		;
;;	MOV.W	@R1,R0				;
;;	TST	R0,R0				;
;;	TST_BIT_OF DND_TEPSTEPCTL_180		;
;;	FAR_JSR	#_POS_CALC_MISS1,R0		;
;;	M_BRA	DND_TEPSTEPCTL_180		;

;;DND_TEPSTEPCTL_050:
;;	TST	#BIT0,R0			;
;;	TST_BIT_OF DND_TEPSTEPCTL_100		;逆転中に正転がきた
;;	FAR_JSR	#_TEP_ADD_OBJMAK,R0		;
;;	FAR_JSR	#_TEP_START_INIT1,R0		;
;;	MOV.L	#_POS_DRV_DIRECT,R1		;
;;	MOV.W	@R1,R0				;
;;	TST	R0,R0				;
;;	TST_BIT_ON DND_TEPSTEPCTL_180		;
;;	FAR_JSR	#_POS_CALC_MISS1,R0		;
;;	M_BRA	DND_TEPSTEPCTL_180		;

DND_TEPSTEPCTL_100:
	FAR_JSR	#_INT_TEP_RESTART,R0						;2013-05-26
	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;[この時点でﾊﾟﾙｽ設定していない]

DND_TEPSTEPCTL_180:
	M_BRA	DND_TEPSTEPCTL_900		;

;	-------------- 払い出し待ち------------
DND_TEPSTEPCTL_200:
	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0					;
	FAR_JSR	#_LOD_POS_STS_REG,R1						;
	TST	#BIT2,R0							;停止?
	TST_BIT_OF DND_TEPSTEPCTL_220						;NO 停止中? 0:払出中 1:停止 

	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT1,WKREG=R1	;

;;;;;;;;	MEM1_DATA_SET MEM=_TEP_STEP_WTTM,LG=W,DATA=5,WKREG1=R1,WKREG2=R2	;5msec
;	----- 2013-05-26 ------------
;;;;;;	MOV.W	#D'100,R2						;DEF 100msec
;;;;;;	MOV.L	#(_PAR_TEP_WATTIM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
;;;;;;	MOV.W	@R1,R0							;
;;;;;;	TST	R0,R0							;
;;;;;;	TST_BIT_OF DND_TEPSTEPCTL_210					;
;;;;;;	MOV	R0,R2							;
;;;;;;DND_TEPSTEPCTL_210:							;

;	------- 2013-06-05--------
	MOV.L	#_TEP_STEP_SVWTTM1,R1					;//2013-06-05
	MOV.W	@R1,R2							;

	MOV.L	#_TEP_STEP_WTTM,R1					;
	MOV.W	R2,@R1							;
	M_BRA	DND_TEPSTEPCTL_900					;

DND_TEPSTEPCTL_220:								;
;	2013-05-20 動作中の加算						;
	FAR_JSR	#_TEP_CPUAB_HAND,R0					;
	TST	R0,R0							;
	TST_BIT_OF DND_TEPSTEPCTL_290					;[止めると決めた人がいる]

	FAR_JSR	#_TEPA_ADD_LSI,R0					;

DND_TEPSTEPCTL_290:							;
	M_BRA	DND_TEPSTEPCTL_900					;


;	-------- 遅延待ち--------
DND_TEPSTEPCTL_400:
	MOV.L	#_TEP_STEP_WTTM,R1				;
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_OF DND_TEPSTEPCTL_420				;
	ADD	#-1,R0						;
	MOV.W	R0,@R1						;
	M_BRA	DND_TEPSTEPCTL_900				;

DND_TEPSTEPCTL_420:						;
;	---- 再起動--------
	MOV.L	#_TEP_POS_ADD_CNT,R1			;
	MOV.L	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF DND_TEPSTEPCTL_800			;

	FAR_JSR	#_INT_TEP_RESTART,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;
	M_BRA	DND_TEPSTEPCTL_900						;


DND_TEPSTEPCTL_800:
	FAR_JSR	#_TEP_START_INIT1,R0						;



DND_TEPSTEPCTL_900:
	NOP
DND_TEPSTEPCTL_EXT:
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	起動処理		***
;	***				***
;	***********************************
_MN_TEP_START
	SUB_START
	FAR_JSR	#_TEP_START_INIT1,R0			;

	MOV.L	#_LINK_PV_ABSPLS,R4		;
	MOV.L	@R4+,R1					;
	MOV.L	@R4,R2					;
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@(0,R4)				;
	MOV.L	R2,@(4,R4)				;
	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4			;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@R4					;
	MOV.L	R2,@(1*4,R4)				;目標位置ｾｯﾄ
	FAR_JSR	#_NOW_INC_DIG_MAK,R0			;
	FAR_JSR	#_TEP_ADD_PLS_MAK,R0			;
;	--- 位置データを作らない---- FAR_JSR #_TEP_SV_OBJ_MAK,R0


	FAR_JSR	#_DNDINC_SPD_SET,R4				;とりあえずこれは触らない[]

;	---------- 2013-06-05
	XOR	R0,R0						;
	MOV.L	#_TEP_CNTSMP_TIM,R1				;
	MOV.W	R0,@R1						;
	MOV.L	#_TEP_STEP_WTTM,R1				;
	MOV.W	R0,@R1						;




	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	再起動処理		***
;	***				***
;	***********************************
;	<<<<<<<<<<<100msecの速度で動作させる>>>>>>>>>>
;
_INT_TEP_RESTART
	SUB_START

;	--------- 2013-06-19 -----------------
	FAR_JSR	#_TEP_CPUAB_HAND_CLR,R0		;

;	--------- 2013-06-05 -----------------
	FAR_JSR	#_TEP_SPD_CALC1,R0			;
	FAR_JSR	#_TEP_SPD_SET,R0			;

;;;2013-06-05	FAR_JSR	#_DNDINC_SPD_SET,R4		;

;;;;;;	FAR_JSR	#_POS_LSI_START_INITAL,R0					;
	FAR_JSR	#_POS_LSI_START_INITAL_TEP,R0					;2013-06-13

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1						;目標速度
	MOV.L	@R1,R2								;
	FAR_JSR	#_POS_LSI_TOP_SPEED_SET,R1					;
	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0					;

	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0					;
	FAR_JSR	#_POS_PLSOUT_SET_RETRY,R0					;(停止時からの起動の場合のみ有効・安一のみ)
	FAR_JSR	#_FWD_REV_START,R1						;起動
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT0,WKREG=R1	;
	FAR_JSR	#_BRK_ERR_WORK_CLR1,R0						;
	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0					;
	FAR_JSR	#_TEP_START_INIT1,R0						;
	SUB_END
	M_RTS


;;;;;;;;2013-06-05元元未使用	***********************************
;;;;;;;;	***				***
;;;;;;;;	***	再ADD			***
;;;;;;;;	***				***
;;;;;;;;;	***********************************
;;;;;;;;_TEP_ADD_OBJMAK:
;;;;;;;;	SUB_START
;;;;;;;;	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0		;
;;;;;;;;	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0		;
;;;;;;;;	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;位置決めLSIｱｸｾｽ(毎ｽｷｬﾝ)
;;;;;;;;	FAR_JSR	#_TEP_START_INIT1,R0			;
;;;;;;;;	SUB_END
;;;;;;;;	M_RTS


_TEP_START_INIT1
	SUB_START
	MEM1_0CLR MEM=_TEP_STEP_FLG,LG=W,WKREG1=R1,CLRREG=R0		;
	MEM1_0CLR MEM=_TEP_POS_ADD_CNT,LG=L,WKREG1=R1,CLRREG=R0		;
;;;;;;;;2013-06-05	MEM1_0CLR MEM=_TEP_POS_ADD_CNTOLD,LG=L,WKREG1=R1,CLRREG=R0	;
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***		倍率			***
;	***					***
;	*******************************************
;	Output R2:NEW CUNTER
;	Output R3:OLD CUNTER
;	起動時はR2,R3は使用しない
_TEP_ADD_PLS_MAK:
	SUB_START
	MOV.L	#_SET1_PLSALO_PLS,R3		;//パルサ倍率低
	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;0:LOW 1:HIGH
	TST_BIT_OF TEP_ADD_PLSMK_050		;
	MOV.L	#_SET1_PLSAHI_PLS,R3		;パルサ倍率高
TEP_ADD_PLSMK_050:
	MOV.W	@R3,R1				;
	MOV.W	#D'1000,R4			;
	CMP/HS	R1,R4				;
	BT	TEP_ADD_PLSMK_100		;
	MOV	R4,R1				;
TEP_ADD_PLSMK_100:				;
	TST	R1,R1				;
	TST_BIT_ON TEP_ADD_PLSMK_150		;
	MOV	#1,R1				;
TEP_ADD_PLSMK_150:				;

	XOR	R0,R0
	MOV.L	#_TEP_IN_ADD,R4			;
	MOV.W	@R4,R2				;
	MOV.W	R0,@R4				;0CLR

	MULS.W	R2,R1				;
	STS	MACL,R2				;
	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	MOV.L	@R1,R3				;
	ADD	R3,R2				;
	MOV.L	R2,@R1				;R3:OLD R2:NEW
;;;;;;;2013-06-05	MOV.L	#_TEP_POS_ADD_CNTOLD,R1		;[[[[[[[[使用していない]]]]]]]]]]]]]]]]
;;;;;;;2013-06-05	MOV.L	R3,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	位置決め側			***
;	***	起動時の位置作成		***
;	***	再起動時の位置作成		***
;	***					***
;	*******************************************
_TEP_1STEP_DATA_MAK1:
	SUB_START

	MOV.L	#_CPOS_CTL_MATH,R0		;
	MOV.W	@R0,R0				;
;;	TST	#_DMATH_CNTROT,R0		;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0	;[2009-10-07下振子]
	TST_BIT_ON TEP_1STEP_DATMK1_080		;

	FAR_JSR	#_NEG_TEPA_AREA_CHK,R0		;反転モードのエリア
	TST	R0,R0				;
	TST_BIT_OF TEP_1STEP_DATMK1_080		;+/- OK

	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	MOV.L	@R1,R2				;
	CMP/PZ	R2				;
	BT	TEP_1STEP_DATMK1_050		;
;	------ "-" PLS入ってきた----
	CMP/PZ	R0				;
	BT	TEP_1STEP_DATMK1_070		;+のみ許可
	M_BRA	TEP_1STEP_DATMK1_080		;-:OK

;	------ + PLS----
TEP_1STEP_DATMK1_050:
	CMP/PL	R0				;"+"OK?
	BT	TEP_1STEP_DATMK1_080		;YES OK
TEP_1STEP_DATMK1_070:
	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	XOR	R0,R0				;
	MOV.L	R0,@R1				;

TEP_1STEP_DATMK1_080:


	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4					;
	MOV.L	@R4,R1							;
	MOV.L	@(1*4,R4),R2						;

	MOV.L	#_TEP_POS_ADD_CNT,R0					;位置決め側使用データ
	MOV.L	@R0,R6							;
	EXTS_4B_TO_8B REG8B_H=R5,REG4B=R6				;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2

;;	------2007-01-23 LIMIT R1,R2(OBJ) R5,R6(DELT):反転の時---------------
;;	MOV.L	#_CPOS_CTL_MATH,R0		;
;;	MOV.W	@R0,R0				;
;;	TST	#_DMATH_CNTROT,R0		;
;;	TST_BIT_ON TEP_1STEP_DATMK1_200		;
;;
;;	--(反転)--
;;	MOV.L	#_TEP_POS_ADD_CNT,R0		;位置決め側使用データ
;;	MOV.L	@R0,R0				;
;;	CMP/PZ	R0				;
;;	BT	TEP_1STEP_DATMK1_100		;
;;	----- MINAS LIMIT -------
;;
;;
;;TEP_1STEP_DATMK1_100:
;;	----- PLAS LIMIT -------
;;
;;
;;
;;
;;TEP_1STEP_DATMK1_200:
	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4			;
	MOV.L	R1,@R4					;
	MOV.L	R2,@(1*4,R4)				;
	MOV.L	#_LINKX_SV_OBJ_ABSPLS,R4		;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@R4					;
	MOV.L	R2,@(4,R4)				;

	MOV.L	#_LNGTH_ADD_DATA,R4			;//符号付き
	MOV.L	R5,@R4					;
	MOV.L	R6,@(4,R4)				;

	MOV.L	#_LT_LNGTH_ADD_DATA,R4			;//符号付き
	MOV.L	R5,@R4					;
	MOV.L	R6,@(4,R4)				;

	XOR	R3,R3					;
	CMP/PZ	R5					;
	BT	TEP_1STEP_DATMK1_100			;
	MOV.W	#BIT0,R3				;
TEP_1STEP_DATMK1_100:
	MOV.L	#_POS_DRV_DIRECT,R1			;起動時(SV-LEVEL)
	MOV.W	R3,@R1					;

	MOV.L	#_POSLSI_DRIV_SHIN,R1			;
	MOV.W	@R1,R0					;
	AND	#LOW ~BIT0,R0				;
	OR	R3,R0					;
	MOV.W	R0,@R1					;

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	手動パルサの反転のリミット	***
;	***	2007-01-23			***
;	*******************************************
;	0~165が動作範囲とする
;	180~0~165までは+側を受け付ける(=165~180まではﾌﾟﾗｽを受付けない)
;	0~165~180までは-側を受け付ける(=180~0まではﾏｲﾅｽを受付けない)
;	実測で0~165の範囲は+/-受け付ける
;
;
;	180
;
;
;
;
;	MOV.L	#_INC_LINK_NOWROT_OFSPLS_P,R4			;これを使用するか
;	MOV.L	@R4,R2						;
;
;	0(+/-)ok
;	1(+)ok
;	-1(-)ok
;
_TEP_DNPOS_HIS	.EQU	100	;10.0度

_NEG_TEPA_AREA_CHK:
	SUB_START


	MOV.L	#_SETX_UPDN_CHK_DN_DIG,R4	;180.0度(下死点角度 180.0)
	MOV.L	@R4,R1				;
;;;;	MOV.L	#_SETX_LINK_UP_POS_DN,R4	;ﾘﾝｸ(範囲比較)
;;;;	MOV.W	@R4,R3				;待機点-α

	MOV.L	#_SET1_UPAREA_DIG1,R4		;ﾘﾝｸ(範囲比較)
	MOV.W	@R4,R3				;待機点
	MOV.L	#_INC_ENC360,R4			;
	MOV.W	@R4,R2				;R1(180)~R3(0)の範囲か？
	FAR_JSR	#_DIG_AREA_CHK1,R0		;ANS.R5=1(ﾏｲﾅｽを受け付けない)
	CMP/PZ	R5				;
	BT	NEG_TEPA_ARACHK200		;+のみ可能


	MOV.L	#_SETX_DNAREA_JG_LNK,R4		;反転設定不可範囲LINK 度
	MOV.L	@R4,R1				;
	MOV.L	#_SETX_UPDN_CHK_DN_DIG,R4	;180.0度(下死点角度 180.0)
	MOV.L	@R4,R3				;
	MOV.W	#_TEP_DNPOS_HIS,R0		;10.0
	ADD	R0,R3				;10.0は..
	MOV.L	#_INC_ENC360,R4			;
	MOV.W	@R4,R2				;R1(180)~R3(0)の範囲か？
	FAR_JSR	#_DIG_AREA_CHK1,R0		;ANS.R5=1(+受け付けない)
	BT	NEG_TEPA_ARACHK100		;

	XOR	R0,R0				;
	M_BRA	NEG_TEPA_ARACHK300		;+/- OK

;	-------- -を受け付ける=====
NEG_TEPA_ARACHK100:
	MOV	#-1,R0				;
	M_BRA	NEG_TEPA_ARACHK300		;

;	-------- +を受け付ける=====
NEG_TEPA_ARACHK200:
	MOV	#1,R0				;
NEG_TEPA_ARACHK300:


	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	手動パルサフラグ	***
;	***				***
;	***********************************
_TEP_FLG_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_TEP_MODE_DRV,R1	;//起動時に判定
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

_TEP_FLG_START
	SUB_START
	MOV.W	#BIT0,R0
	MOV.L	#_TEP_MODE_DRV,R1	;//起動時に判定
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	手動パルサ起動条件	***
;	***	起動=1			***
;	***				***
;	***********************************
;------------ 341.1ON→片手ON→手パの順位に変更する2011-07-04
;
_TEPA_START_CHK:
	SUB_START

	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04手パ時間
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON TEPA_STARTCHK_NG		;手パが先になった

	MOV.L	#_BTTN_FLG,R1			;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF TEPA_STARTCHK_NG		;

	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	@R1,R2				;
	CMP/PZ	R2				;
	BT	TEPA_STARTCHK_050		;
	NEG	R2,R2				;
TEPA_STARTCHK_050:
	MOV.W	#D'1,R1				;1で良いか
	CMP/GE	R1,R2				;
	BT	TEPA_STARTCHK_OK		;
TEPA_STARTCHK_NG:
	XOR	R0,R0				;
	M_BRA	TEPA_STARTCHK_END		;

TEPA_STARTCHK_OK:
	FAR_JSR	#_TEP_FLG_START,R0		;
	MOV	#1,R0				;
TEPA_STARTCHK_END:

	SUB_END
	M_RTS

;;;	------------ 341.1ON→片手ON→手パの順位に変更する2011-07-04
;;;_TEPA_START_CHK:
;;;	SUB_START
;;;
;;;	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
;;;	MOV.W	@R1,R0				;
;;;	TST	#BIT1,R0			;
;;;	TST_BIT_OF TEPA_STARTCHK_NG		;無効
;;;
;;;	MOV.L	#_TEP_IN_ADD,R1			;
;;;	MOV.W	@R1,R2				;
;;;	CMP/PZ	R2				;
;;;	BT	TEPA_STARTCHK_050		;
;;;	NEG	R2,R2				;
;;;TEPA_STARTCHK_050:
;;;	MOV.W	#D'1,R1				;1で良いか
;;;	CMP/GE	R1,R2				;
;;;	BT	TEPA_STARTCHK_OK		;
;;;TEPA_STARTCHK_NG:
;;;	XOR	R0,R0				;
;;;	M_BRA	TEPA_STARTCHK_END		;
;;;
;;;TEPA_STARTCHK_OK:
;;;	FAR_JSR	#_TEP_FLG_START,R0		;
;;;	MOV	#1,R0				;
;;;TEPA_STARTCHK_END:
;;;
;;;	SUB_END
;;;	M_RTS

;	***********************************
;	***				***
;	***	手動パルサ遷移時の	***
;	***	パルスクリア		***
;	***				***
;	***********************************
	.IMPORT		_PVP_CPUA_TEPPLS
	.IMPORT		_PVP_CPUB_TEPPLS

_TEPA_PLSCNT_CLR
	SUB_START

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_PVP_CPUA_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AELSE
	MOV.L	#_PVP_CPUB_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AENDI

	MOV.L	#_NEW_TEP_CNT,R1		;
	MOV.W	R2,@R1				;

	XOR	R2,R2
	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	R2,@R1				;

	MOV.L	#_TEP_POS_ADD_CNT,R1		;位置決め側使用データ
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	手動ﾊﾟﾙｻの増分ﾁｪｯｸ	***
;	***				***
;	***				***
;	***********************************
_TEPA_PLSCNT_CHK:
	SUB_START

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_PVP_CPUA_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AELSE
	MOV.L	#_PVP_CPUB_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AENDI

	MOV.L	#_NEW_TEP_CNT,R1		;
	MOV.W	@R1,R3				;
	MOV.W	R2,@R1				;
	SUB	R3,R2				;
	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	R2,@R1				;

;	------ 2011-07-04 追加　運転釦が先--
	TST	R2,R2				;変化あり?
	TST_BIT_OF TEPA_PLSCNTCHK_100		;

	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04手パ時間
	MOV.W	@R1,R0				;
	TST	R0,R0
	TST_BIT_ON TEPA_PLSCNTCHK_050		;

	MOV.L	#_BTTN_FLG,R1			;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON TEPA_PLSCNTCHK_100		;

TEPA_PLSCNTCHK_050:

	MOV.W	#D'51,R0			;50*10=0.5秒
	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04手パ時間
	MOV.W	R0,@R1				;

TEPA_PLSCNTCHK_100:
	

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	2013-05-26			***
;	***					***
;	*******************************************
;	10ﾊﾟﾙｽ,方向無視----→修正必要
_TEPA_ADD_LSI:
	SUB_START

;	----------- 復活 2013-06-05--------
	MOV.L	#_TEP_CNTSMP_TIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON TEPA_ADDLSI_EXT		;


;	-----------------------------------
	MOV.L	#_TEP_STEP_SVSMPTM,R0		;
	MOV.W	@R0,R2				;
	MOV.W	R2,@R1				;
;	-----------------------------------


	MOV.L	#_TEP_POS_ADD_CNT,R1			;
	MOV.L	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF TEPA_ADDLSI_EXT			;

;;;;;;;;;;;;;	MOV	R0,R1
;;;;;;;;;;;;;	CMP/PZ	R1
;;;;;;;;;;;;;	BT	TEPA_ADDLSI_020
;;;;;;;;;;;;;	NEG	R1,R1					;
;;;;;;;;;;;;;TEPA_ADDLSI_020:
;;;;;;;;;;;;;	MOV.W	#D'4,R4					;
;;;;;;;;;;;;;	CMP/HS	R4,R1					;
;;;;;;;;;;;;;	BF	TEPA_ADDLSI_EXT				;


	XOR	R2,R2					;
	CMP/PZ	R0					;
	BT	TEPA_ADDLSI_050				;+ PLS?
	MOV.W	#BIT0,R2				;
TEPA_ADDLSI_050

	MOV.L	#_POS_DRV_DIRECT,R1			;起動時(SV-LEVEL)
	MOV.W	@R1,R0					;
	XOR	R2,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF TEPA_ADDLSI_100			;符号そのまま

;;;;	符号反転の場合加算しない+速度をｱｯﾌﾟあせる場合は以下
	FAR_JSR	#_TEP_SPD_CALC3,R0			;
	FAR_JSR	#_TEP_SPD_SET_CHG,R0			;

	FAR_JSR	#_TEP_CPUAB_HAND_STOP,R0		;2013-06-19

	M_BRA	TEPA_ADDLSI_EXT				;



TEPA_ADDLSI_100

	FAR_JSR	#_LOAD_REST_PLS,R0					;LOAD PLS

	MOV.L	#_TEP_ADDCHK_SVPLS,R1					;SYS_PARA 10PLS
	MOV.W	@R1,R4

	CMP/HI	R0,R4							;10pls以下 R0<10
	BT	TEPA_ADDLSI_EXT						;"二重回路HAND対象"
									;難しい

;	---------パルス加算処理 2013-06-05 --------------
	FAR_JSR	#_TEP_SPD_CALC2,R0			;
	FAR_JSR	#_TEP_SPD_SET_CHG,R0			;

	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0		;CNT=0 CLR,目標変更
	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0		;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;位置決めLSIｱｸｾｽ(毎ｽｷｬﾝ)

	XOR	R0,R0
	MOV.L	#_TEP_POS_ADD_CNT,R1
	MOV.L	R0,@R1


TEPA_ADDLSI_EXT:

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	初起動時のエリア作成	***
;	***				***
;	***********************************
;;2013-05-26 _DNDTEP_STEP_MAKE:
;;2013-05-26	SUB_START
;;2013-05-26	SUB_END
;;2013-05-26	M_RTS

;	***********************************
;	***				***
;	***	工程からの目標位置作成	***
;	***				***
;	***********************************
;;2013-05-26_DNDTEP_MAKE_OBJPOS:
;;2013-05-26	SUB_START
;;2013-05-26
;;2013-05-26
;;2013-05-26	SUB_END
;;2013-05-26	M_RTS

_TEP_SPD_CALC1:
	SUB_START
	MOV.L	#_TEP_STEP_SVWTTM1,R3	;//2013-06-05
	MOV.W	@R3,R4			;
	FAR_JSR	#_TEP_SPD_CALC_COM,R0	;ANS=TEP1

	MOV.L	#_TEP_CHG_SPD1,R1	;起動時はSPD1,SPD2とも同じ速度
	MOV.L	@R1,R2			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;SPD2が実際に使用する速度

	SUB_END
	M_RTS

_TEP_SPD_CALC2:
	SUB_START

	MOV.L	#_TEP_CHG_SPD1,R1	;起動時はSPD1,SPD2とも同じ速度
	MOV.L	@R1,R2			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;SPD2が実際に使用する速度

	MOV.L	#_TEP_STEP_SVSMPTM,R3
	MOV.W	@R3,R4			;
	FAR_JSR	#_TEP_SPD_CALC_COM,R0	;
	SUB_END
	M_RTS


_TEP_SPD_CALC_COM
	SUB_START

	MOV.L	#_TEP_POS_ADD_CNT,R3		;
	MOV.L	@R3,R2				;
	CMP/PZ	R2
	BT	TEP_SPD_CALCCOM_100			;
	NEG	R2,R2					;
TEP_SPD_CALCCOM_100

	MOV.W	#D'1000,R1				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;10PLS:100msec

	TST	R2,R2					;
	TST_BIT_ON TEP_SPD_CALCCOM_200			;
	MOV.W	#1,R2					;
TEP_SPD_CALCCOM_200


	MOV.L	#_SET1_DNDINC_SPD1,R1	;
	MOV.L	@R1,R3			;

;	-----------MAX LIMIT----------
	CMP/HS	R2,R3
	BT	TEP_SPD_CALCCOM_300	
	MOV	R3,R2			;
TEP_SPD_CALCCOM_300


;	---------- MIN LIMIT -------------
	MOV.L	#_TEP_MIN_SPD_PLS,R1	;
	MOV.L	@R1,R3			;PLS/S

	CMP/HS	R3,R2
	BT	TEP_SPD_CALCCOM_400	
	MOV	R3,R2			;
TEP_SPD_CALCCOM_400

	MOV.L	#_TEP_CHG_SPD1,R1	;
	MOV.L	R2,@R1			;

	SUB_END
	M_RTS

;	-----------------------------------
_TEP_SPD_CALC3:
	SUB_START
	MOV.L	#_SET1_DNDINC_SPD1,R1	;
	MOV.L	@R1,R2			;
;;;;	MOV.L	#_TEP_CHG_SPD1,R1	;
;;;;	MOV.L	R2,@R1			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;
	SUB_END
	M_RTS



_TEP_SPD_SET:
	SUB_START

	MOV.L	#_TEP_CHG_SPD1,R1			;
	MOV.L	@R1,R2					;

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1			;//目標速度
	MOV.L	R2,@R1					;

	SUB_END
	M_RTS

_TEP_SPD_SET_CHG:
	SUB_START

;;;;	MOV.L	#_TEP_CHG_SPD1,R1			;
;;;;	MOV.L	@R1,R2					;

	MOV.L	#_TEP_CHG_SPD2,R1			;
	MOV.L	@R1,R2					;

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1			;//目標速度
	MOV.L	R2,@R1					;

	FAR_JSR	#_POS_LSI_TOP_SPEED_SETX,R1		;input R2

	SUB_END
	M_RTS




;	***************************************************
;	***						***
;	***						***
;	***						***
;	***						***
;	***************************************************
	.EXPORT	_TEP_DTMAK
_TEP_DTMAK:
	SUB_START

;	------------------------------------
	MOV.L	#(_PAR_TEP_BEFPLS-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R4							;
	MOV.W	#D'10,R0						;MIN PLS
	CMP/HS	R0,R4							;R4(10PLS)=< R0
	BT	TEP_SYS_SET080						;
	MOV	R0,R4							;
TEP_SYS_SET080:
	MOV.L	#_TEP_ADDCHK_SVPLS,R1
	MOV.W	R4,@R1			

;	--------------2013-06-05 -----------
	MOV.W	#D'100,R2						;DEF 100msec
	MOV.L	#(_PAR_TEP_WATTIM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;
	TST	R0,R0							;
	TST_BIT_OF TEP_SYS_SET100					;
	MOV	R0,R2							;
TEP_SYS_SET100:
	MOV.L	#_TEP_STEP_SVWTTM1,R1	;//2013-06-05
	MOV.W	R2,@R1			;

	MOV.L	#_TEP_STEP_SVWTTM1,R1	;//2013-06-05
	MOV.W	@R1,R2			;
	SHLR	R2			;
	MOV.L	#_TEP_STEP_SVSMPTM,R1	;
	MOV.W	R2,@R1			;1/2時間

;	---------- 最小速度兼自起動速度
	MOV.L	#(_PAR_TEP_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2							;
	TST	R2,R2							;
	TST_BIT_ON TEP_SYS_SET200					;
	MOV.W	#1,R2							;0.01%
TEP_SYS_SET200:								;
	FAR_JSR	#_CYCLE_SPD1,R0						;
	MOV.L	#_TEP_MIN_SPD_PLS,R1					;
	MOV.L	R2,@R1							;PLS/S

	MOV.L	#_POS_LSI_SPDMAX,R0				;
	MOV.L	@R0,R1						;
	MOV.L	#_POS_FRQ_SPDMAX,R0				;500KHZ(500000PLS/S)
	MOV.L	@R0,R4						;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;
	MOV.L	#_TEP_MIN_SPD_FRQ,R1				;//自起動速度
	MOV.L	R2,@R1						;


	SUB_END
	M_RTS

;
_TEP_CPUAB_HAND
	SUB_START
	XOR	R0,R0
	MOV.L	#_SH4toSH2_TEPSIG,R5	;
	MOV.W	@R5,R1			;
	MOV.L	#_SH2toSH4_TEPSIG,R6	;
	MOV.W	@R6,R2			;
	CMP/EQ	R1,R2			;
	BF	TEP_CPUAB_HDEXT		;
	MOV.B	#BIT0,R0			;
TEP_CPUAB_HDEXT

	SUB_END
	M_RTS

_TEP_CPUAB_HAND_CLR
	SUB_START
	XOR	R0,R0

 .AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_SH4toSH2_TEPSIG,R5	;
 .AELSE
	MOV.L	#_SH2toSH4_TEPSIG,R5	;
 .AENDI
	MOV.W	R0,@R5


	SUB_END
	M_RTS

;*******************************************

_TEP_CPUAB_HAND_STOP
	SUB_START
	MOV.B	#BIT0,R0		;

 .AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_SH4toSH2_TEPSIG,R5	;
 .AELSE
	MOV.L	#_SH2toSH4_TEPSIG,R5	;
 .AENDI
	MOV.W	R0,@R5


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	Input R2			***
;	***	ﾘﾝｸ(内部制御)ﾊﾟﾙｽ		***
;	***	Input R0 DIRECT			***
;	***	方向固定			***
;	***					***
;	*******************************************
;	MOV.L	#_SETX_DNAREA_JG_PLS,R4			;反転設定不可範囲LINK-PLS
;	MOV.L	@R4,R2					;
;

