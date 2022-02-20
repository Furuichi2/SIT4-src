;	***********************************
;	***				***
;	***	制動制御		***
;	***	位置決め部		***
;	***				***
;	***********************************
;	------- 2010-08-20[制動モード]
	.EXPORT	_BRKTST_POS_START

	.ALIGN	4				;
_BRKTST_POS_CTL:
	SUB_START
	MOV.L	#_INT_POS_CTL_FLAG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT3,R0			;
	TST_BIT_OF BRKTST_POSCTL_0020		;
	M_BRA	BRKTST_POSCTL_0800		;非常停止中

BRKTST_POSCTL_0020:
	TST	#BIT0,R0			;
	TST_BIT_OF BRKTST_POSCTL_0040		;
	M_BRA	BRKTST_POSCTL_0200		;起動中


BRKTST_POSCTL_0040:
	MOV.L	#_MNWR_POS_CMD,R6	;ﾊﾟﾙｽ払出即停止
	MOV.W	@R6,R0			;
	AND	#(BIT2+BIT1+BIT0),R0	;
	CMP/EQ	#BIT0,R0		;
	BT	BRKTST_POSCTL_0048		;001
	M_BRA	BRKTST_POSCTL_0190		;EXIT
;	==== 通常の位置決め起動コマンド状態
BRKTST_POSCTL_0048:

	XOR	R2,R2
	MOV.L	#_INT_POS_STEP_FLG,R1	;
	MOV.W	R2,@R1			;
	MOV.L	#_INT_DND_CTL_STEP,R1;
	MOV.W	R2,@R1
	MOV.L	#_INT_DND_STEP_FLG,R1	;//(上死点復帰の工程管理)
	MOV.W	R2,@R1			;
	MOV.L	#_CAM_CNT_CHG_FLG,R1		;//連続が１ｽﾃｯﾌﾟになった
	MOV.W	R2,@R1				;

;	------ ﾓｰｼｮﾝ運転 --------
	MOV.L	#_SV_POS_CTL_STEP,R1	;//1msec 制御上の見かけ
	MOV.W	@R1,R4			;
	MOV.L	#_INT_POS_CTL_STEP,R2	;//内部制御工程1~11
	MOV.W	R4,@R2			;


	FAR_JSR	#_POS_LSI_START_INITAL,R0	;((((((((((((段取・原点起動スキャン)))))))))))
	FAR_JSR	#_DND_1STEP_DATA_MAK1,R0	;_LNGTH,SHIN,SPEED


	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0
	FAR_JSR	#_ERR_INFO_DT_IN3,R0		;2004-01-28ADD,TOTAL(起動開始)

	FAR_JSR	#_POS_PLSOUT_SET_RETRY,R0	;(停止時からの起動の場合のみ有効・安一のみ)

;	== 2004-03 ===
	FAR_JSR	#_ERR_INFO_DT_CHK2,R0		; SGL ONLY
	MOV.W	#D'2,R0			;
	MOV.L	#_ERR_INFO_DLY_TIM,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_ERR_INFO_DT_IN4,R0		;
	FAR_JSR	#_FWD_REV_START,R1		;起動
	
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT0,WKREG=R1	;

	FAR_JSR	#_BRK_ERR_WORK_CLR1,R0		;_BRK_ERR_CHK_START2	;2003-07-01

	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0
	
BRKTST_POSCTL_0190:
	M_BRA	BRKTST_POSCTL_0800			;

;	===========================================
;	===		起動中			===
;	===========================================
BRKTST_POSCTL_0200:
	MOV.L	#_MNWR_POS_CMD,R6						;
	MOV.W	@R6,R0								;
	CMP/EQ	#BIT0,R0							;
	BT	BRKTST_POSCTL_0240						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT3,WKREG=R1	;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0				;
	FAR_JSR	#_POS_LSI_EMG_STOP,R0						;急停止
	FAR_JSR	#_LSI_REST_PLS_CHK_STOP_CLR,R0					;2004-03-03
	M_BRA	BRKTST_POSCTL_0800							;


BRKTST_POSCTL_0240:
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0	;位置決めLSIｱｸｾｽ(毎ｽｷｬﾝ)

;	=== FLAG SET(REST-PLS REFLASH-END)====
	eSHi_SET_IM_MOV DST=_eSHi_REST_RL_HF,L1=W,WKREG1=R1,WKREG2=R0,IMD=1	;


;	=== 2004-01-28===
	FAR_JSR	#_ERR_INFO_DT_CHK2,R0		;0CHEAK(起動中常時) SGL-ONLY
	FAR_JSR	#_ERR_INFO_DT_CHK3,R0		;PLS SGL-OMLY

	.AIF _CMP_ERR_SPEC_ENB	EQ _CMPILE_YES	;2006-09-19
	FAR_JSR	#_ERR_INFO_DT_CHK_CMP2,R0	;SGL-ONLY
	.AENDI


BRKTST_POSCTL_0800:

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		目標位置作成		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_BRKTST_POS_START:
	SUB_START

;	----------2014-11-10------------
	XOR	R0,R0
	MOV.L	#_MOVE_MODE_MATH_LATCH,R1	;//0:(ふりこ以外 または 段取・原点モード)1:(ふりこでﾓｰｼｮﾝしていた)
	MOV.W	R0,@R1				;
;	----------------------------------


;	=== 目標位置生成=========
	FAR_JSR	#_BRKTST_OBJ_MAKE,R0

	FAR_JSR	#_X_SET_PV_ABS_TO_OBJ,R0
	FAR_JSR	#_SGL_CMP_ERR_DT_CLR,R0

	FAR_JSR	#_LSI_REST_PLS_CHK_START_CLR,R0	;
	FAR_JSR	#_GPOSIN_HOS_DRV_INI,R0

	XOR	R2,R2
	MOV.L	#_INT_DND_CTL_STEP,R1;
	MOV.W	R2,@R1
	MOV.L	#_INT_DND_STEP_FLG,R1	;//(上死点復帰の工程管理)
	MOV.W	R2,@R1

	XOR	R0,R0				;(1ｻｲｸﾙ完了時にOFFしていないとならない信号なのに)
	MOV.L	#_INT_POS_CTL_FLAG,R1		;
	MOV.W	R0,@R1				;

;	=== 2004-12-20 ===
	MOV.L	#_CNT_STOP_CTRL_FLG,R1	;//BIT0,BIT1:差し引き終了
	MOV.W	R0,@R1				;

	FAR_JSR	#_CNTREST_HOS_RESET,R1	;

;	=== 2004-01-26 CCS===
	XOR	R0,R0
	MOV.L	#_CCS_BTTN_OFF,R1		;両手ON以外の状態が運転中にあった。必ずいつか止める
	MOV.W	R0,@R1				;


;	====== 一旦停止信号OFF=====
	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB206),LG=W,BIT=(~BIT9),WKRG1=R1,WKRG2=R4

	FAR_JSR	#_CMPCYC_START_CLR,R0		;
	FAR_JSR	#_CMPSTP_CNT_STOP_CLR,R0	;起動時のみ連続停止クリア（後はサイクル完了時も）

	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0	;

	FAR_JSR	#_DAI_MOSTPOS_SMPINI,R0		;2003-02-03
	FAR_JSR	#_KJPHOS_SMPINI,R0		;2004-07-05

	FAR_JSR	#_POS_LSI_WORK_STOP2,R0

	XOR	R0,R0			;
	MOV.L	#_INT_CYC_DRV_STS,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_STOP_LATCH,R1		;//BIT0:ｽﾄｯﾌﾟ釦
	MOV.W	R0,@R1			;
	MOV.L	#_STOP_LATCH_B,R1	;//BIT0:ｽﾄｯﾌﾟ釦
	MOV.W	R0,@R1			;
	MOV.L	#_INT_CLS_CTL_FLG,R1	;//BIT0=1 START 起動時ｸﾘｱ
	MOV.W	R0,@R1			;
;;2016-10-31未使用	MOV.L	#_LOT_CNT_TO_MOD,R1	;
;;2016-10-31未使用	MOV.W	R0,@R1			;




	MOV.L	#_ORIGN_OBJ_CTL_FLG,R1		;2004-05-24
	XOR	R0,R0				;
	MOV.W	R0,@R1				;


	MOV.W	#BIT0,R0			;起動
	MOV.L	#_MNWR_POS_CMD,R1		;
	MOV.W	R0,@R1				;

;	--------2009-04-01 起動したらフラグクリア[原点時の]
	MEM1_BIT0_F_ADCLR MEM=_ORIGN_180ARA_FLG,LG=W,BIT=(~BIT5),WKRG1=R4,WKRG2=R1	;原点起動で使用
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB207,LG=W,BIT=(~BIT5),WKRG1=R4,WKRG2=R1

;	------- 起動------------
	MOV.W	#BIT0,R0		;
	MOV.L	#_BRKTST_STR_FLG,R1	;
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS


	.ALIGN	4				;
_BRKTST_OBJ_MAKE
	SUB_START
;	--------------------------------------------
	MOV.L	#_CTL_ENC360,R0				;//360.0度(いまのところ不要)
	MOV.W	@R0,R1					;
	MOV.L	#_STR_ENC3600_DIG,R4			;//運転開始時の360.0角度
	MOV.W	R1,@R4					;

;	-----------------------------------------
	MOV.L	#_LINK_PV_ABSPLS,R4			;
	MOV.L	@R4+,R1					;
	MOV.L	@R4,R2					;
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@(0,R4)				;
	MOV.L	R2,@(4,R4)				;

;	---------- 目標位置設定------
	MOV.L	#_LINK_1ROT_PLS,R4			;//1回転ﾊﾟﾙｽ(設定ﾚﾍﾞﾙ)
	MOV.L	@R4,R6					;
	XOR	R5,R5					;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R5,R6 +R1,R2=>R1,R2

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4		;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@R4				;
	MOV.L	R2,@(1*4,R4)			;目標位置ｾｯﾄ


;	---------- 方向------
	XOR	R0,R0				;BIT0=0:正
	MOV.L	#_POS_DRV_DIRECT,R1		;起動時(SV-LEVEL)
	MOV.W	R0,@R1


;	---------- 目標位置設定------
;;;;;2011-09-14	MOV.L	#_POS_DRV_DIRECT,R1		;起動時(SV-LEVEL)
;;;;;2011-09-14	MOV.W	@R1,R0
;;;;;2011-09-14	FAR_JSR	#_LINK_P_M_MAX,R4		;Input R0:BIT0 DIRECT
						;_LINK_SV_OBJ_ABSPLS,R4		;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)




	FAR_JSR	#_NOW_INC_DIG_MAK,R0			;

;	---------- SPEED SET---------------
;;	MOV.L	#_FREQ_PLSI_MAX_FRQ,R1	;
;;;	MOV.L	#_LINK_MAX_SPD_PLS,R1

	MOV.L	#_BRKTST_OUTSPD_PLS,R1	;
	MOV.L	@R1,R2			;
	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1	;//目標速度
	MOV.L	R2,@R1			;

	FAR_JSR	#_POS_LSI_TOP_SPEED_SET,R0	;input R2




;	-------------------ｵｰﾊﾞﾗｲﾄﾞﾃﾞｰﾀMAX-----------
	MOV.W	#_OVRLIDE_LATE_MAX,R2						;
	REG_MOV_TO_MEM	DST_ADR=_SET_SPD_OVRLIDE,L1=W,DT_REG=R2,WKREG1=R1	;
	REG_MOV_TO_MEM	DST_ADR=_SET_ACC_OVRLIDE,L1=W,DT_REG=R2,WKREG1=R1	;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_OVER_RIDE_USEFUL,LG=W,BIT=~BIT1,WKREG=R4	;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_OVER_RIDE_USEFUL,LG=W,BIT=~(BIT1+BIT0),WKREG=R4	;

	FAR_JSR	#_OVERRIDE_CALC_LATE_SEL,R0	;
	FAR_JSR	#_OVERRIDE_CALC_SPED_SEL,R0	;

;	--------- ﾌﾞﾚｰｷ異常ﾃﾞｰﾀ1　ｵｰﾊﾞﾗｲﾄﾞにも対応しておく----
	FAR_JSR	#_ACCBRK1_SV_MAKE,R0		;
	FAR_JSR	#_ACCBRK2_SV_MAKE,R0		;


;	------------------2011-09-14----------停止位置-----
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)
	MOV.L	@(0,R4),R1
	MOV.L	@(4,R4),R2

	MOV.L	#_WPARX_BRKTST_STPLNG,R4		;//相対ﾊﾟﾙｽ
	MOV.L	@R4,R6					;
	XOR	R5,R5					;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R5,R6 +R1,R2=>R1,R2

	MOV.L	#_BRKTST_STP_ABSPLS,R4					;
	MOV.L	R1,@R4							;
	MOV.L	R2,@(1*4,R4)						;


	SUB_END
	M_RTS

