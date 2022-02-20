;	***********************************************************
;	***							***
;	***		電力モニタ関連の演算一式		***
;	***							***
;	***		2010-09-21				***
;	***							***
;	***********************************************************
;SSA_DTMK.SRC
;	---　ﾊﾟﾗﾒｰﾀの転送だけ----
_AD_DLY_BUF_MAX		.EQU	100			;
_CONST_PAI		.EQU	314			;3.1415926=3.1416
_CONST_PAI_LAT		.EQU	100			;

	.IMPORT		_DWORD_BIT0_TBL1
	.IMPORT		_DWORD_BIT1_TBL1
	.IMPORT		_PAR_IVW_RANGE			;243
	.IMPORT		_CB_SYS_PARAM241		;
	.IMPORT		_CB_SYS_PARAM242		;

	.IMPORT	_SVP_EP_VOF		;.SRES	2	;サーボパラメータB0　　電力用ｵﾌｾｯﾄ
	.IMPORT	_SVP_EP_VMX		;.SRES	2	;サーボパラメータB1　　電力用最大値
	.IMPORT	_SVP_EP_TRQ		;.SRES	2	;サーボパラメータB2　　電力用ﾄﾙｸ値
	.IMPORT	_SVP_EP_LTM		;.SRES	2	;サーボパラメータB3　　ﾄﾙｸ側遅れ時間
	.IMPORT	_SVP_EP_K1		;.SRES	2	;サーボパラメータB4　　調整係数A
	.IMPORT	_SVP_EP_K2		;.SRES	2	;サーボパラメータB5　　調整係数B
	.IMPORT	_SVP_EP_ADJSIN		;.SRES	2	;サーボパラメータB6　　調整電力符号
	.IMPORT	_SVP_EP_ADJVAL		;.SRES	2	;サーボパラメータB7　　調整電力
	.IMPORT	_SVP_ECOM_BASE		;.SRES	2	;サーボパラメータB8　　エコメータ基準値
	.IMPORT	_SVP_ECOM_SCAL		;.SRES	2	;サーボパラメータB9　　エコメータスケール


	.IMPORT	_ENC_PLS_SPD
	.IMPORT	_SET1_INCPLS_1REV	;

	.EXPORT	_API_IVW_CYC_START
	.EXPORT	_API_IVW_CYC_END

	.ALIGN	4				;
_PAR_IVW_MOVE
	SUB_START

	MEM_MOV_TO_MEM	SRC_ADR=_PAR_IVW_RANGE,L1=W,DST_ADR=_WPAR_IVW_RANGE,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3

	MEM_MOV_TO_MEM	SRC_ADR=_CB_SYS_PARAM241,L1=W,DST_ADR=_WPAR_IVWSEK_SEL,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3

	MEM_MOV_TO_MEM	SRC_ADR=_CB_SYS_PARAM242,L1=W,DST_ADR=_WPAR_ECOMET_SEL,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3


	SUB_END
	M_RTS

;	---　設定の転送だけ----
;	103.12=0 過負荷保護　103.12=1:電力モニタ
	.ALIGN	4				;
_SET_IVW_MOVE
	SUB_START


	MOV.L	#_SVP_EP_LTM,R1			;
	MOV.W	@R1,R2				;
	MOV.W	#_AD_DLY_BUF_MAX,R4		;0~99
	CMP/HI	R2,R4				;
	BT	SET_IVW_MV050			;
	XOR	R2,R2				;100以上は0
SET_IVW_MV050
	MOV.L	#_SET1_EP_LTM,R1		;
	MOV.W	R2,@R1				;



	MOV.L	#_SVP_ECOM_BASE,R0		;サーボパラメータB8　　エコメータ基準値
	MOV.W	@R0,R2				;0.1kw->*10
	MOV.L	#_SVP_ECOM_SCAL,R0		;サーボパラメータB9　　エコメータスケール
	MOV.W	@R0,R1				;
	MOV.W	#D'10,R4			;100%　[上で10倍しないから 10で割る]
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)
	SHLR2	R2				;1/8
	SHLR	R2				;
	TST	R2,R2				;
	TST_BIT_ON SET_IVW_MV110
	MOV.W	#1,R2
SET_IVW_MV110

	MOV.L	#_ECO_CMP_DLT,R1		;.SRES	2	;kwh
	MOV.W	R2,@R1				;


;	---------------------------------------------
	XOR	R2,R2
	MOV.L	#_SEQAB_DP_TOP+103*2,R1	;
	MOV.W	@R1,R0			;
	MOV.W	#BIT12,R4		;
	TST	R4,R0			;
	TST_BIT_OF SET_IVW_MV120	;
	MOV.W	#H'005A,R2		;
SET_IVW_MV120
	MOV.L	#_MON_SV_IVW_USED,R1	;//0:過負荷モニタ 5A:
	MOV.W	R2,@R1			;

;2010-09-30
	MOV.L	#_SVP_ECOM_BASE,R0		;サーボパラメータB8　　エコメータ基準値
	MOV.W	@R0,R1				;0.1kw->*10
	MOV.W	#D'10,R0			;
	DMULS.L	R1,R0				;
	STS	MACL,R1				;
	MOV.L	#_SET1_ECOM_BASE,R0		;
	MOV.L	R1,@R0				;
	

	SUB_END
	M_RTS

;;_SET_IVW_DATMAK:
;;	SUB_START
;;	SUB_END
;;	M_RTS

;	*******************************************
;	***					***
;	***		電力作成		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_PV1_IVW_DATMAK
	SUB_START

	FAR_JSR	#_AD_SH2_DATA_CHG,R0		;2012-09-25


	MOV.L	#_MON_SV_IVW_USED,R1		;//0:過負荷モニタ 5A:
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON PV1_IVW_DTMK_050		;

;	------------- 過負荷モニタだ-----------
	XOR	R0,R0				;
	MOV.L	#_MON_SV_IVW_RNGE,R1		;//[42,43](0:小数点2桁 5A:小数点1桁)
	MOV.W	R0,@R1				;
	MOV.L	#_PV_IVW_DAT_DSP,R1		;(ｻﾝﾌﾟﾘﾝｸﾞ用)[単位切り替え]
	MOV.L	R0,@R1				;2byte以下のﾃﾞｰﾀ

	XOR	R0,R0				;
	MOV.L	#_PVP_ECO_METER,R1		;ECO METER
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_POWER_KWH,R1		;1CYCLE
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_EPM_SYOHI,R1		;消費
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_EPM_KAISE,R1		;回生
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_IVW_DOT,R1		;0:小数点2桁 5A:小数点1桁 CPUA->CPUB[不要]
	MOV.W	R0,@R1				;
	M_BRA	PV1_IVW_DTMK_900		;


PV1_IVW_DTMK_050
;;;2012-09-25	FAR_JSR	#_AD_SH2_DATA_CHG,R0		;2011-03-22


;	------------- 電力モニタだ-----------
	FAR_JSR	#_IVW_DATA_CALC,R0			;

	MOV.L	#_PV_IVW_DAT_1W,R1				;//1[w] data
	MOV.L	R2,@R1						;+/-1w

	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_PV_IVW_DAT_10W,R1				;//10[w]=0.01kw data
	MOV.L	R2,@R1						;0.01kw
	MOV.L	#_PV_IVW_DAT_INP,R1				;//10[w]=0.01kw data[見える化ﾗｲﾄ用]
	MOV.L	R2,@R1						;


	PUSH_REG1 R2
	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_PV_IVW_DAT_100W,R1				;//10[w] data
	MOV.L	R2,@R1						;0.1kw
	POP_REG1 R3						;32767でﾘﾐｯﾄ必要

	XOR	R4,R4
	MOV.L	#_WPAR_IVW_RANGE,R1				;0:小数点２桁 1:小数点１桁
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	PV1_IVW_DTMK_100				;小数点2桁JUMP
	MOV	R2,R3						;
	MOV.W	#H'005A,R4					;
PV1_IVW_DTMK_100
	MOV.L	#_MON_SV_IVW_RNGE,R1				;//[42,43](0:小数点2桁 5A:小数点1桁)
	MOV.W	R4,@R1						;
	MOV.L	#_PV_IVW_DAT_DSP,R1				;(ﾊﾟｿｺﾝのｻﾝﾌﾟﾘﾝｸﾞ用)[単位切り替え]
	MOV.L	R3,@R1						;


;	----------電力量(1cycle,1秒,回生1秒)----------
	FAR_JSR	#_SEKI_IVW_DAT_MAKE,R0				;[]





PV1_IVW_DTMK_900

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		AD->ﾄﾙｸ作成		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_TRQ_DATA_MAKE:
	SUB_START
;;;2011-03-22	MOV.L	#_PV_AD_DATA,R1			;0~1000= 0V~10.00V
	MOV.L	#_PVXSH2_AD_DATA,R1			;0~1000= 0V~10.00V
	MOV.W	@R1,R2				;
	MOV.L	#_AD_IVW_DAT,R1			;
	MOV.W	R2,@R1				;0~1000
						;
	MOV.L	#_SVP_EP_VOF,R1			;ｵﾌｾﾄ電圧
	MOV.W	@R1,R3				;500(5.00V)
	SUB	R3,R2				;
	MOV.L	#_SVP_EP_VMX,R1			;
	MOV.W	@R1,R4				;
	SUB	R3,R4				;
						;PV=900
						;OFS=500
						;MAX=1000
						;PV=400 OFS=500

	MOV.L	#_SVP_EP_TRQ,R5			;
	MOV.W	@R5,R1				;[N･m] 1~32767

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)
	MOV.L	#_PV_TRQ_NM_DAT,R1		;+/- 1[N･m]~ 32767
	MOV.L	R2,@R1				;[N･m] or 1w data

;;;;2012-12-10	MOV.L	#_SQ_CBWK_TOP+_WKSQCB246,R1	;
;;;;2012-12-10	MOV.W	R2,@R1				;ﾃﾞﾊﾞｯｸ専用

	CMP/PZ	R2				;
	BT	TRQ_DATA_MK200			;
	NEG	R2,R2				;
TRQ_DATA_MK200:
	MOV.L	#_PV_ABS_TRQ_NM_DAT,R1		;
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		電力メータ演算		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_IVW_METER_DATA_MAKE:
	SUB_START
;;;2011-03-22	MOV.L	#_PV_AD_DATA,R1			;0~1000= 0V~10.00V
	MOV.L	#_PVXSH2_AD_DATA,R1			;0~1000= 0V~10.00V
	MOV.W	@R1,R2				;
	MOV.L	#_AD_IVW_DAT,R1			;
	MOV.W	R2,@R1				;0~1000
						;
	MOV.L	#_SVP_EP_VOF,R1			;ｵﾌｾﾄ電圧
	MOV.W	@R1,R3				;500(5.00V)
	SUB	R3,R2				;
	MOV.L	#_SVP_EP_VMX,R1			;
	MOV.W	@R1,R4				;
	SUB	R3,R4				;
						;PV=900
						;OFS=500
						;MAX=1000
						;PV=400 OFS=500

;	----- 電力測定器使用する00
	MOV.L	#_SET1_ECOM_BASE,R0		;
	MOV.L	@R0,R1				;サーボパラメータB8　　エコメータ基準値*10
						;0.01kw
	ADD	R1,R1				;*2
	MOV	R1,R0				;
	ADD	R1,R1				;*4
	ADD	R1,R1				;*8
	ADD	R0,R1				;*10 1w data

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)

	MOV.L	#_PV_TRQ_NM_DAT,R1		;1w data
	MOV.L	R2,@R1				;

	MOV.L	#_PV_IVW_DAT,R1			;// data(output data)
	MOV.L	R2,@R1				;+/- 1w data 

;;;;2012-12-10	MOV.L	#_SQ_CBWK_TOP+_WKSQCB246,R1	;
;;;;2012-12-10	MOV.W	R2,@R1				;ﾃﾞﾊﾞｯｸ専用


	CMP/PZ	R2				;
	BT	IVW_METER_DATMK200
	NEG	R2,R2				;
IVW_METER_DATMK200:
	MOV.L	#_PV_ABS_TRQ_NM_DAT,R1		;
	MOV.L	R2,@R1				;



	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		遅延データ作成		***
;	***					***
;	*******************************************
;	ﾊﾞﾌｧ100max
;	input  R2
;	BUF-MAX=100
;	Output R2
;
	.ALIGN	4				;
_AD_DLY_MAKE
	SUB_START

	MOV.L	#_AD_DLY_POINT,R6		;
	MOV.W	@R6,R0				;
	MOV	R0,R3				;POINTER PUSH
	SHLL	R0				;*2
	MOV.L	#_AD_DLY_BUF,R5			;遅延ﾃﾞｰﾀ作成
	ADD	R5,R0				;
	MOV.W	R2,@R0				;NEW-SAVE

	MOV	R3,R0				;
	ADD	#1,R0				;
	MOV.W	#_AD_DLY_BUF_MAX,R4		;
	CMP/HS	R4,R0				;100=<
	BF	AD_DLYMK_100			;
	XOR	R0,R0				;
AD_DLYMK_100					;
	MOV.W	R0,@R6				;NEXT POINTER SAVE

	MOV.L	#_SET1_EP_LTM,R1	
	MOV.W	@R1,R0				;DELAY DATA LOAD
	SUB	R0,R3				;SAVE POINT
	CMP/PZ	R3				;
	BT	AD_DLYMK_200			;
	ADD	R4,R3				;MAX
AD_DLYMK_200					;
	SHLL	R3				;*2
	ADD	R5,R3				;
	MOV.W	@R3,R2				;
	SUB_END
	M_RTS




	.ALIGN	4				;
_SPD_DLY_MAKE
	SUB_START

	MOV.L	#_AD_DLY_POINT,R6		;
	MOV.W	@R6,R0				;
	MOV	R0,R3				;POINTER PUSH
	SHLL	R0				;*2
	SHLL	R0				;*2
	MOV.L	#_SPD_DLY_BUF,R5			;遅延ﾃﾞｰﾀ作成
	ADD	R5,R0				;
	MOV.L	R2,@R0				;NEW-SAVE

	MOV	R3,R0				;
	ADD	#1,R0				;
	MOV.W	#_AD_DLY_BUF_MAX,R4		;
	CMP/HS	R4,R0				;100=<
	BF	SPD_DLYMK_100			;
	XOR	R0,R0				;
SPD_DLYMK_100					;
	MOV.W	R0,@R6				;NEXT POINTER SAVE

	MOV.L	#_SET1_EP_LTM,R1	
	MOV.W	@R1,R0				;DELAY DATA LOAD
	SUB	R0,R3				;SAVE POINT
	CMP/PZ	R3				;
	BT	SPD_DLYMK_200			;
	ADD	R4,R3				;MAX
SPD_DLYMK_200					;
	SHLL	R3				;*2
	SHLL	R3				;*2
	ADD	R5,R3				;
	MOV.L	@R3,R2				;
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***		角速度			***
;	***					***
;	*******************************************
;	ｴﾝｺｰﾀﾞ移動量/1msec*10msec
;	ｴﾝｺｰﾀﾞ 1回転 2048ﾊﾟﾙｽ
;	3000rpm:50rot/1sec
;	50*2048=102,400ﾊﾟﾙｽ /1sec･･･3000rpm　1msecで100ﾊﾟﾙｽ
;	66*4096=
;	10msecなら 1000ﾊﾟﾙｽ 10msecの移動量にしましょう
;	MOV.L	#_ENC_PLS_SPD,R11			;= R11(ad4)
;	符号付き
;	10msec分のﾊﾞﾌｧから速度算出
;	結果はPLS/sec
;
;	Freq*2*PAI
;	PLS速度/1回転ﾊﾟﾙｽ数 * 2 * pai
;
;
	.ALIGN	4				;
_OMEGA_DATA_MAKE:
	SUB_START



	MOV.L	#H'123456,R2			;TEST

	MOV.L	#_ENC_PLS_SPD,R1		;
	MOV.L	@R1,R2				;+/-　pls/s
	FAR_JSR	#_SPD_DLY_MAKE,R0		;

	MOV.L	#_SPD_ENC_DATX,R1		;
	MOV.L	R2,@R1				;


;	--------- ﾃﾞﾊﾞｯｸ-----
;;;;	MOV.L	#D'50*8192,R2			;50HZ
;;;;	NEG	R2,R2				;
;;;;	NEG	R2,R2				;
;	---------------------

	MOV.L	#_CONST_PAI*2,R1		;314*2

	MOV.L	#_SET1_INCPLS_1REV,R5		;
	MOV.L	@R5,R4				;1回転(ﾃｽﾄｽﾀﾝﾄﾞは8192)

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;ENC_PLS_SPD[PLS/S]*2*Π/(1REV*100)


	MOV.L	#_OMEGA_RAD,R1			;100HZ*3.14=314rad/s
	MOV.L	R2,@R1				;*100倍


	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***	R2*A/B+C			***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	Output R2 +/-1w data
	.ALIGN	4				;
_IVW_DATA_CALC:
	SUB_START
	MOV.W	#BIT6,R0			;[ﾃﾞﾊﾞｯｸ用]

	MOV.L	#_CB_SEQ_CB_COM345,R0		;
	MOV.W	@R0,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF IVW_DATA_CAL100		;[電力測定器使用しない JUMP]
;	-------- 電力計-------
	FAR_JSR	#_IVW_METER_DATA_MAKE,R0	;
	MOV.L	#_PV_IVW_DAT,R1			;
	MOV.L	@R1,R2				;+/- 1w data
	M_BRA	IVW_DATA_CAL900

IVW_DATA_CAL100:
;	-------- 電力計-------
	FAR_JSR	#_TRQ_DATA_MAKE,R0			;TRQ
	FAR_JSR	#_OMEGA_DATA_MAKE,R0			;

	MOV.L	#_OMEGA_RAD,R1				;100HZ*3.14=314rad/s
	MOV.L	@R1,R2					;*100倍
	MOV.L	#_PV_TRQ_NM_DAT,R3			;
	MOV.L	@R3,R1					;+/-

	MOV.L	#_CONST_PAI_LAT,R4			;100
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;ENC_PLS_SPD[PLS/S]*2*Π/(1REV*100)
	MOV.L	#_PV_IVW_DAT,R1				;// data
	MOV.L	R2,@R1					;+/- 1w data

;	------------------DEBUG
;;;	MOV.L	#_PV_ENC_SPD_PER,R5		;0~100.00%
;;;	MOV.W	@R5,R2				;
;	------------------
	PUSH_REG1 R2
	FAR_JSR	#_IVW_PARAM_MAKE,R0		;ANS R1,R4
	POP_REG1 R2


	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;1w data *(補正A-B)/1000

	MOV.L	#_SVP_EP_ADJVAL,R1		;サーボパラメータB7　　調整電力
	MOV.W	@R1,R3				;
	EXTU.W	R3,R3				
	MOV.L	#_SVP_EP_ADJSIN,R1		;サーボパラメータB6　　調整電力符号
	MOV.W	@R1,R0				;
	TST	R0,R0
	TST_BIT_OF IVW_DATA_CAL500		;
	NEG	R3,R3				
IVW_DATA_CAL500:
	ADD	R3,R2				;+/- 1wdata

IVW_DATA_CAL900:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***		補正係数算出		***
;	***					***
;	*******************************************
;	MOV.L	#_SVP_EP_K1,R3			;サーボパラメータB4　　調整係数A
;	MOV.W	@R3,R1				;
;	MOV.L	#_SVP_EP_K2,R3			;サーボパラメータB5　　調整係数B
;	MOV.W	@R3,R4				;
;	ANS R1,R4
;

	.ALIGN	4				;
_IVW_PARAM_MAKE:
	SUB_START

	MOV.L	#_PV_ENC_SPD_PER,R5		;0~100.00%
	MOV.W	@R5,R2				;

	MOV.L	#_SVP_EP_K1,R3			;サーボパラメータB4　　調整係数A
	MOV.W	@R3,R1				;

	MOV.W	#D'10000,R4			;100.00per
	CMP/HS	R4,R2				;
	BT	IVW_PARAM_MK500			;100per以上 R1=係数B

	MOV.L	#_SVP_EP_K2,R3			;サーボパラメータB5　　調整係数B
	MOV.W	@R3,R5				;min
	SUB	R5,R1				;

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;R2(0-10000)*R1(A-B)/10000
	ADD	R5,R2				;
	MOV	R2,R1				;

IVW_PARAM_MK500
	MOV.W	#D'100,R4			;ANS

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		電力量積算		***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	_PV_IVW_DAT_INP		;2000,00kw [10w]
;
_SEKISAN_TIM_LAT	.EQU	60*1000	;1分 60sec　CPUBの1秒のｻﾝﾌﾟﾘﾝｸﾞ誤差は1/60になる

	.ALIGN	4				;
_SEKI_IVW_DAT_MAKE:
	SUB_START


;	---		[1]		----
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8


;	--------消費　積算(有効+無効分)---
	MOV.L	#_CYC_SEK_WORK,R5					;有効+無効CYCLE
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	ADD8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;


;	--------回生　積算(無効分)---
	CMP/PZ	R7							;
	BT	SEKI_IVW_DATMK_020					;+ THEN EXIT
	MOV.L	#_CYC_SEK_KAIWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	SUB8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;実際にはR7,R8の-を"+"にして足し算と同じ
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;
	M_BRA	SEKI_IVW_DATMK_025

SEKI_IVW_DATMK_020:
	MOV.L	#_CYC_SEK_PULSWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	ADD8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;
SEKI_IVW_DATMK_025:


	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	ADD	#1,R4							;
	CMP/PL	R4
	BT	SEKI_IVW_DATMK_030					;
	ADD	#-1,R4							;MAX=7FFF,FFFF
SEKI_IVW_DATMK_030:
	MOV.L	R4,@R6							;
;	------------- ADD ------
	MOV.L	#_CYC_INP_STS,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_CYC_LTH_STS,R1	;
	MOV.W	@R1,R3			;
	MOV.W	R0,@R1			;
	CMP/EQ	R3,R0			;
	BT	SEKI_IVW_DATMK_150	;[EXIT]
					; n(1)->0:計算する
					; n(1)->n+1(2):計算する
					; 0   ->n(1):0ｸﾘｱする
					
;	--- 変化あり?:前回計測中であれば実測を作成/ｱｲﾄﾞﾙなら計測開始だけ--
	TST	R3,R3							;
	TST_BIT_OF SEKI_IVW_DATMK_150					;


	FAR_JSR	#_CYC_SEKI_CALC,R0

SEKI_IVW_DATMK_150:





;	--------------[2]----------------------------
;	=========== 消費測定(現状1分毎に1分平均値をHMI出力　長いほど精度はよいが5分単位で割り切れる数値)=========
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8

	MOV.L	#_IVW_WP_SEK_WORK,R5					;1000msec or 60000msec積算
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	ADD8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;

	MOV.L	#_IVW_WP_SEK_TIME,R6		;1000msec or 60000msec
	MOV.L	@R6,R4				;
	ADD	#1,R4				;
	MOV.L	R4,@R6				;

	MOV.L	#_SEKISAN_TIM_LAT,R0		;
	CMP/HS	R0,R4				;
	BF	SEKI_IVW_DATMK_300		;

;----消費電力1秒[測定時間=1000]or1分[測定時間=6000]ﾃﾞｰﾀ作成
;----1000or60000[測定時間]
;R1,R2/R4(1000or60000)
	CMP/PZ	R1
	BT	SEKI_IVW_DATMK_250			;
	XOR	R1,R1					;
	XOR	R2,R2					;
SEKI_IVW_DATMK_250:
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0		;ANS R2[10w-data]
	MOV.L	#_PVP_EPM_SYOHI,R1			;消費 0.01kw 固定
	MOV.W	R2,@R1					;

	XOR	R0,R0
	MOV.L	#_IVW_WP_SEK_TIME,R6			;有効1sec
	MOV.L	R0,@R6					;

	MOV.L	#_IVW_WP_SEK_WORK,R5			;WORK - CLR
	MOV.L	R0,@R5					;
	MOV.L	R0,@(4,R5)				;

SEKI_IVW_DATMK_300:



;	--------------[3]----------------------------
;	=========== 回生測定(現状1分毎に1分平均値をHMI出力　長いほど精度はよいが5分単位で割り切れる数値)=========
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	CMP/PZ	R8				;
	BF	SEKI_IVW_DATMK_350		;
	XOR	R8,R8				;
SEKI_IVW_DATMK_350:
	NEG	R8,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8

	MOV.L	#_IVW_WN_SEK_WORK,R5					;1000msec or 60000msec積算
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	ADD8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;

	MOV.L	#_IVW_WN_SEK_TIME,R6		;1000msec or 60000msec
	MOV.L	@R6,R4				;
	ADD	#1,R4				;
	MOV.L	R4,@R6				;

	MOV.L	#_SEKISAN_TIM_LAT,R0		;
	CMP/HS	R0,R4				;
	BF	SEKI_IVW_DATMK_400		;

;----回生電力1秒[測定時間=1000]or1分[測定時間=6000]ﾃﾞｰﾀ作成
;----1000or60000[測定時間]
;R1,R2/R4(1000or60000)
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0			;ANS R2[10w-data]
	MOV.L	#_PVP_EPM_KAISE,R1				;回生 0.01kw 固定
	MOV.W	R2,@R1						;


	XOR	R0,R0
	MOV.L	#_IVW_WN_SEK_TIME,R6			;有効1sec
	MOV.L	R0,@R6					;

	MOV.L	#_IVW_WN_SEK_WORK,R5			;WORK - CLR
	MOV.L	R0,@R5					;
	MOV.L	R0,@(4,R5)				;

SEKI_IVW_DATMK_400:






	SUB_END
	M_RTS


;	--------------- ｻｲｸﾙ 開始(次ｻｲｸﾙ開始)-----------------

	.ALIGN	4				;
_API_IVW_CYC_START
	SUB_START
	MOV.L	#_CYC_INP_STS,R1	;
	MOV.W	@R1,R0			;
	ADD	#1,R0			;
	TST	R0,R0			;
	TST_BIT_ON API_IVW_CYC_STR_100	;
	ADD	#1,R0			;
API_IVW_CYC_STR_100			;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS


	.ALIGN	4				;
_API_IVW_CYC_END
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_CYC_INP_STS,R1	;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***********************************
;	***	１サイクル時作成データ	***
;	***********************************
	.ALIGN	4				;
_CYC_SEKI_CALC:
	SUB_START

;	-------------消費電力演算------------
	MOV.L	#_CYC_SEK_WORK,R5					;有効1sec
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w　[0.01kw]

	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0				;ANS R2[10w-data]

	MOV.L	#_CYC_IVW_PV0,R1					;
	MOV.L	R2,@R1							;+/- 0.01kw data

	CMP/PZ	R2
	BT	CYC_SEKICAL_050					;
	XOR	R2,R2							;
CYC_SEKICAL_050:
	MOV.L	#_CYC_IVW_PV1,R1					;
	MOV.L	R2,@R1							;

	MOV.L	#D'60000,R4				;
	CMP/GE	R2,R4					;
	BT	CYC_SEKICAL_100				;
	MOV	R4,R2					;
CYC_SEKICAL_100:
	MOV.L	#_CYC_IVW_PV2,R1			;
	MOV.W	R2,@R1					;***.** kw


	MOV.L	#_CYC_SEK_WORK,R5			;
	MOV.L	@R5,R1					;
	MOV.L	@(4,R5),R2				;10w　[0.01kw]
;;;;	MOV.L	#D'1000*D'3600,R4			;1時間ﾃﾞｰﾀ 0.01kwh
	MOV.L	#D'3600,R4				;10w*1000/3600=0.01wh
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0		;

	CMP/PZ	R2
	BT	CYC_SEKICAL_150				;
	XOR	R2,R2					;
CYC_SEKICAL_150:
	MOV.L	#D'60000,R4				;
	CMP/GE	R2,R4					;
	BT	CYC_SEKICAL_200				;
	MOV	R4,R2					;
CYC_SEKICAL_200:
	MOV.L	#_CYC_IVWHR_PV2,R1			;
	MOV.W	R2,@R1					;***.** kw



;	-------------回生電力演算------------
	MOV.L	#_CYC_SEK_KAIWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w　[0.01kw]

	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0				;ANS R2[10w-data]
	MOV.L	#_CYC_IVWKAI_PV1,R1					;確定ﾃﾞｰﾀ 0.01kw 回生
	MOV.L	R2,@R1							;+ ONLY

	MOV.L	#D'60000,R4						;
	CMP/GE	R2,R4							;
	BT	CYC_SEKICAL_300					;
	MOV	R4,R2							;
CYC_SEKICAL_300:
	MOV.L	#_CYC_IVWKAI_PV2,R1					;確定ﾃﾞｰﾀ 0.01kw 回生
	MOV.W	R2,@R1							;***.** kw


;	-------------＋側のみ電力演算------------
	MOV.L	#_CYC_SEK_PULSWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w　[0.01kw]

	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0				;ANS R2[10w-data]
	MOV.L	#_CYC_IVWPULS_PV1,R1					;確定ﾃﾞｰﾀ 0.01kw 回生
	MOV.L	R2,@R1							;+ ONLY

	MOV.L	#D'60000,R4						;
	CMP/GE	R2,R4							;
	BT	CYC_SEKICAL_350					;
	MOV	R4,R2							;
CYC_SEKICAL_350:
	MOV.L	#_CYC_IVWPULS_PV2,R1					;確定ﾃﾞｰﾀ 0.01kw +
	MOV.W	R2,@R1							;***.** kw







;	============(電力モニタの表示値、見える化トレンドのデータ)=========
	MOV.L	#_CYC_IVW_PV2,R1				;
	MOV.W	@R1,R3						;***.** kw

	XOR	R4,R4
	MOV.L	#_WPAR_IVWSEK_SEL,R1				;0:平均 1:電力量
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	CYC_SEKICAL_450					;
	MOV.L	#_CYC_IVWHR_PV2,R1				;
	MOV.W	@R1,R3						;***.** wh
	MOV.W	#H'005A,R4					;
CYC_SEKICAL_450:
	MOV.L	#_MON_SV_IVW_CSEL,R1				;//[42,43](0:小数点2桁 5A:小数点1桁)
	MOV.W	R4,@R1						;
	MOV.L	#_PVP_POWER_KWH,R1				;***.** kwh
	MOV.W	R3,@R1						;

	FAR_JSR	#_ECO_METER_MAKE,R0			;

;	----- CLR -------
	XOR	R0,R0			;
	MOV.L	#_CYC_SEK_WORK,R5					;有効1sec
	MOV.L	R0,@R5			;
	MOV.L	R0,@(4,R5)		;

	MOV.L	#_CYC_SEK_KAIWORK,R5	;
	MOV.L	R0,@R5			;
	MOV.L	R0,@(4,R5)		;

	MOV.L	#_CYC_SEK_PULSWORK,R5	;+分
	MOV.L	R0,@R5			;
	MOV.L	R0,@(4,R5)		;



	MOV.L	#_CYC_SEK_TIME,R6	;
	MOV.L	R0,@R6			;
	SUB_END
	M_RTS




;	***************************************************
;	***						***
;	***************************************************
	.ALIGN	4				;
_ECO_METER_MAKE:
	SUB_START

	MOV.L	#_CYC_DEBUG_CNT,R1		;
	MOV.W	@R1,R0				;
	ADD	#1,R0				;
	CMP/EQ	#10,R0				;
	BF	ECO_METER_MK020			;
	XOR	R0,R0
ECO_METER_MK020:
	MOV.W	R0,@R1				;


	
	MOV.L	#_WPAR_ECOMET_SEL,R1		;
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BT	ECO_METER_MK100			;
	FAR_JSR	#_ECO_METER_MAKE1,R0			;
	M_BRA	ECO_METER_MK200

ECO_METER_MK100:
	FAR_JSR	#_ECO_METER_MAKE2,R0		;

ECO_METER_MK200:

	SUB_END
	M_RTS

;	***************************************************
;	***	基準値に対する平均電力	 ***.**kwh	***
;	***************************************************
	.ALIGN	4				;
_ECO_METER_MAKE1:
	SUB_START

	MOV.L	#_CYC_IVW_PV2,R1			;
	MOV.W	@R1,R2					;***.** kw
	MOV	R2,R1					;

	MOV.L	#_SET1_ECOM_BASE,R0				;
	MOV.L	@R0,R2						;サーボパラメータB8　　エコメータ基準値*10
	SUB	R1,R2						;
	CMP/PZ	R2
	BT	ECO_METERMAK1_050				;
	XOR	R2,R2
ECO_METERMAK1_050:						;

	MOV.L	#_ECO_CMP_DLT,R1				;.SRES	2	;kwh
	MOV.W	@R1,R4						;

	FAR_JSR	#_ECO_METER_CHG,R0


	SUB_END
	M_RTS


;	***************************************************
;	***		回生	 ***.**kwh		***
;	***************************************************
;	|回生| ／ ((｜+側｜*ｴｺﾒｰﾀｽｹｰﾙ%/100%)/8)
	.ALIGN	4				;
_ECO_METER_MAKE2:
	SUB_START

;;;	MOV.L	#_PVP_EPM_SYOHI,R1				;消費 0.01kw 固定
;;;	MOV.W	@R1,R2						;

	MOV.L	#_CYC_IVWPULS_PV2,R1				;確定ﾃﾞｰﾀ 0.01kw +
	MOV.W	@R1,R2						;***.** kw
;;;;2010-11-02	MOV.L	#_CYC_IVWKAI_PV2,R1				;確定ﾃﾞｰﾀ 0.01kw 回生
;;;;2010-11-02	MOV.W	@R1,R4						;***.** kw
;;;;2010-11-02	ADD	R4,R2						;

	MOV.L	#_SVP_ECOM_SCAL,R0				;サーボパラメータB9　　エコメータスケール
	MOV.W	@R0,R1						;
	MOV.W	#D'100,R4					;100%
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;(0割算付防止)
	SHLR2	R2						;1/8
	SHLR	R2						;
	TST	R2,R2						;
	TST_BIT_ON ECO_METERMAK2_050				;
	MOV.W	#1,R2						;
ECO_METERMAK2_050:						;
	MOV	R2,R4						;

	MOV.L	#_CYC_IVWKAI_PV2,R1				;確定ﾃﾞｰﾀ 0.01kw 回生
	MOV.W	@R1,R2						;***.** kw

	FAR_JSR	#_ECO_METER_CHG,R0				;


	SUB_END
	M_RTS

;	***************************
;	***			***
;	***	R2/R4..MOD	***
;	***	切り上げ	***
;	***************************
	.ALIGN	4				;
_ECO_METER_CHG:
	SUB_START

	TST	R2,R2						;
	TST_BIT_OF ECO_METERCHG_100				;0
	ADD	R4,R2						;R2/R4→　(R2+(R4-1))/R4:切上　
	ADD	#-1,R2						;
ECO_METERCHG_100:						;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 


	MOV.W	#D'8,R4						;
	CMP/HS	R2,R4
	BT	ECO_METERCHG_150				;
	MOV	R4,R2						;
ECO_METERCHG_150:						;

	MOV.L	#_DWORD_BIT0_TBL1,R3				;
	SHLL2	R2						;*4 4byte
	ADD	R2,R3
	MOV.L	@R3,R0						;byte-bit
	MOV.L	#_PVP_ECO_METER,R1				;
	MOV.W	R0,@R1						;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		2011-03-22		***
;	***					***
;	*******************************************
;;;MC	.import		_SH2_AD_DATA		;2011-03-18:0~1024 ad 1msec data(10bit)
	.import		_PVPAB_SH2_AD_DATA		;2011-03-18:0~1024 ad 1msec data(10bit)
	.ALIGN	4				;
_AD_SH2_DATA_CHG
	SUB_START
;;;MC	MOV.L	#_SH2_AD_DATA,R1		;2011-03-18:0~1024 ad 1msec data(10bit)
	MOV.L	#_PVPAB_SH2_AD_DATA,R1		;2011-03-18:0~1024 ad 1msec data(10bit)
	MOV.W	@R1,R2				;IN data

	MOV.L	#_SH2_AD_TOTAL,R6		;

	MOV.L	#_SH2_AD_FILTBUF,R5
	MOV.L	#_SH2_AD_POINT,R1		;
	MOV.W	@R1,R0				;
	ADD	R0,R5				;
	ADD	R0,R5				;*2(2byte)
	ADD	#1,R0				;
	AND	#B'00000111,R0			;
	MOV.W	R0,@R1				;POINTER +1

	MOV.W	@R5,R3				;OLD LOAD
	MOV.W	R2,@R5				;NEW SAVE

	MOV.L	@R6,R4				;
	ADD	R2,R4				;NEW ADD
	SUB	R3,R4				;OLD SUB
	MOV.L	R4,@R6				;

	SHLR2	R4				;1/4
	SHLR	R4				;1/8(*1/2)

;;2011-05-30	MOV.L	#_PVXSH2_AD_DATA,R1		;//0~1000= 0V~10.00V
;;2011-05-30	MOV.W	R4,@R1				;

;---- data*1000/1023
	MOV	R4,R2				;
	MOV.W	#D'1000,R1			;
	MOV.W	#D'1023,R4			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)
	MOV.L	#_PVXSH2_AD_DATA,R1		;//0~1000= 0V~10.00V
	MOV.W	R2,@R1				;

	SUB_END
	M_RTS



;	***********************************************************
;	***							***
;	***	2012-09-25					***
;	***	オーバヒート電流測定				***
;	***							***
;	***********************************************************
	.IMPORT	_DIVU_64R1R2_32R4_64R1R2
	.IMPORT	_ROOT2_64R1R2_ANS_R2
	.IMPORT	_FPU_POS_HOKAN1			;Xn_1=< X =<Xn (Xn_1<Xn)

	.IMPORT	_CLR_SQ224_11
	.IMPORT	_SET_SQ224_11
	.IMPORT	_OVERH_MODE_DT_MAK


	.EXPORT	_TRQ_OVERHEAT_CALC	;
;;;;2012-10-19	.EXPORT	_OVERH_CYC_START	;ｻｲｸﾙ開始
	.EXPORT	_OVERH_CYC_END		;ｻｲｸﾙ終了
	.EXPORT	_OVERH_CYC_STOP		;EMG,MODE

;	***********************************
;	***				***
;	***	メモリ関連		***
;	***				***
;	***********************************

	.IMPORT	_PAR_IVW_KAMP			;
	.IMPORT	_CB_SYS_PARAM000		;
	.IMPORT	_W_PARAM_TOP			;

	.IMPORT	_SETX_OVERH_LNGTH		;//1mm Main->OVERH SOFT
	.IMPORT	_SETX_OVERH_AMP			;//OVERH->AMP閾値[実際は2BYTE]
	.IMPORT	_OVERH_MODE_SEL			;//0[回転]/1[反転]/2[ふりこ]/3[ふりこ]
	.IMPORT	_SQ_OVERH_CMP			;//OVERH-> MAIN
	.IMPORT	_OVERH_CALC_USE			;//MODE,EXQ,EMG,
	.IMPORT	_PAR_OVHALM_WTCNT		;2012-10-16
	.IMPORT	_MODE_SEL			;2012-10-16



	.ALIGN	4			;
_TRQ_OVERHEAT_CALC:
	SUB_START


	MOV.L	#_OVERH_CALC_USE,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF TRQ_OVERHEAT_CAL400		;

	FAR_JSR	#_TRQ_OVERHEAT_DTMAK,R0

;;;2012-10-19	 ｻｲｸﾙ終了~ｻｲｸﾙ終了までを測定する
;;;2012-10-19	MOV.L	#_CYC2_INP_STS,R1		;
;;;2012-10-19	MOV.W	@R1,R0				;
;;;2012-10-19	TST	R0,R0				;
;;;2012-10-19	TST_BIT_OF TRQ_OVERHEAT_CAL450		;BIT6=1(END) or BIT0=1(開始) or BIT6=1,BIT0=1(連続のｻｲｸﾙEND+開始)

	MOV.L	#_CYC2_INP_STS,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF TRQ_OVERHEAT_CAL200		;ｻｲｸﾙ終了していない積算開始

	MOV.L	#_CYC2_INP_STS,R1		;
	MOV.W	@R1,R0				;
	AND	#LOW ~BIT6,R0			;
	MOV.W	R0,@R1				;


;	--------------- 2012-10-16 --------
	MOV.L	#_CYC2_WAIT_CNTPV,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF TRQ_OVERHEAT_CAL100		;
	ADD	#-1,R0				;
	MOV.W	R0,@R1				;
	M_BRA	TRQ_OVERHEAT_CAL180		;

TRQ_OVERHEAT_CAL100:


;	---------- 最後の積算 ----------
	FAR_JSR	#_OVERH_SEKI_ADD,R0	;

;	-----------平均電流演算------------
	FAR_JSR	#_OVERH_IAMP_DT_CALC,R0	;

;	-----------オーバヒート電流演算------
	FAR_JSR	#_OVERH_AMP_SV_CALC,R0	;


;	-----------オーバヒート電流比較------
	FAR_JSR	#_OVERH_AMP_CMP,R0	;

TRQ_OVERHEAT_CAL180:

	M_BRA	TRQ_OVERHEAT_CAL500	;CLR

TRQ_OVERHEAT_CAL200:
;;;;;2012-10-19	MOV.L	#_CYC2_INP_STS,R1		;
;;;;;2012-10-19	MOV.W	@R1,R0				;
;;;;;2012-10-19	TST	#BIT0,R0		;
;;;;;2012-10-19	TST_BIT_OF TRQ_OVERHEAT_CAL250	;非運転中

;	---------- 積算 ----------
	FAR_JSR	#_OVERH_SEKI_ADD,R0	;

;;;;;TRQ_OVERHEAT_CAL250:
	M_BRA	TRQ_OVERHEAT_CAL800	;


;	-------------演算停止クリア------------------
TRQ_OVERHEAT_CAL400				;

	XOR	R0,R0				;
	MOV.L	#_CYC2_INP_STS,R1		;
	MOV.W	R0,@R1				;

;;;;;;;;2012-10-19	------------起動した　クリア処理	-----------------
;;;;;;;;2012-10-19	TRQ_OVERHEAT_CAL450				;

	MOV.W	#1,R2					;どのモードも１回は異常としない
	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1CNT,R0				;
	TST_BIT_OF TRQ_OVERHEAT_CAL470			;

	MOV.L	#(_PAR_OVHALM_WTCNT-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2

TRQ_OVERHEAT_CAL470				;

	MOV.L	#_CYC2_WAIT_CNTPV,R1		;2012-10-16 連続のみ待ちカウンタ
	MOV.W	R2,@R1				;2012-10-19　連続以外も１回目は捨て


;	------------演算した　クリア処理	-----------------
TRQ_OVERHEAT_CAL500				;
	XOR	R0,R0				;
	MOV.L	#_CYC2_SEK_TIME,R1		;
	MOV.L	R0,@R1				;

	MOV.L	#_PV_ABS_OVERH_TRQSEK,R1	;
	MOV.L	R0,@(0*4,R1)			;
	MOV.L	R0,@(1*4,R1)			;
	MOV.L	R0,@(2*4,R1)			;

TRQ_OVERHEAT_CAL800



	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	2012-09-25			***
;	***	オーバヒート瞬時電流実測作成	***
;	***					***
;	*******************************************
	.ALIGN 4
_TRQ_OVERHEAT_DTMAK:
	SUB_START

	MOV.L	#_PVXSH2_AD_DATA,R1		;0~1000= 0V~10.00V
	MOV.W	@R1,R2				;
	
	MOV.L	#_SVP_EP_VOF,R1			;ｵﾌｾﾄ電圧
	MOV.W	@R1,R3				;500(5.00V)
	SUB	R3,R2				;
	MOV.L	#_SVP_EP_VMX,R1			;
	MOV.W	@R1,R4				;
	SUB	R3,R4				;
						;PV=900
						;OFS=500
						;MAX=1000
						;PV=400 OFS=500

	MOV.L	#_SVP_EP_TRQ,R5			;
	MOV.W	@R5,R1				;[N･m] 1~32767

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)

	CMP/PZ	R2				;
	BT	OVERHEAT_DTMK200		;
	NEG	R2,R2				;
OVERHEAT_DTMK200:				;

	MOV.L	#(_PAR_IVW_KAMP-_CB_SYS_PARAM000+_W_PARAM_TOP),R0	;
	MOV.W	@R0,R1							;
	MOV.W	#D'1000,R4						;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)


	MOV.L	#_PV_ABS_OVERH_TRQ,R1		;
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***		積算		***
;	***				***
;	***********************************
	.ALIGN	4			;
_OVERH_SEKI_ADD
	SUB_START

	MOV.L	#_CYC2_SEK_TIME,R1	;1msec*10分
	MOV.L	@R1,R0			;
	ADD	#1,R0			;
	MOV.L	#D'10*60*1000,R4	;1msec*1000(1sec)*60(min)*10:10分がMAX
	CMP/HS	R4,R0			;R4=<R0
	BT	TRQ_OVERHEATCALC_OVER	;演算不可能
	MOV.L	R0,@R1			;ﾀｲﾏ+1


	MOV.L	#_PV_ABS_OVERH_TRQ,R1		;
	MOV.L	@R1,R2				;
	DMULS.L	R2,R2				;

	XOR	R0,R0
	STS	MACH,R3				;
	STS	MACL,R4				;

	MOV.L	#_PV_ABS_OVERH_TRQSEK,R1	;
	MOV.L	@(0*4,R1),R5			;
	MOV.L	@(1*4,R1),R6			;
	MOV.L	@(2*4,R1),R7			;

	CLRT
	ADDC	R4,R7
	ADDC	R3,R6
	ADDC	R0,R5

	MOV.L	R5,@(0*4,R1)			;
	MOV.L	R6,@(1*4,R1)			;
	MOV.L	R7,@(2*4,R1)			;



TRQ_OVERHEATCALC_OVER:

	SUB_END
	M_RTS




;	***********************************
;	***				***
;	***		平均電流演算	***
;	***				***
;	***********************************
;	12BYTE(96ﾋﾞｯﾄ)をﾙｰﾄしてから時間で割る
;	12BYTEを8BYTE(時間*時間)で割ってからﾙｰﾄする
;	IAVL=1/T*ROOT(I1^2+I2^2････)
;	IAVL=ROOT{(I1^2+I2^2････)/(T^2)}
;
;
;	AD*32767(500前後)/1000=32767 (500[Nm])
;	I*I=1000*1000･･･4BYTEで収まる
;
;
;;;	.IMPORT	_ROOT2_64R1R2_ANS_R2	;

	.ALIGN	4			;
_OVERH_IAMP_DT_CALC
	SUB_START
	MOV.L	#_PV_ABS_OVERH_TRQSEK,R5	;
	MOV.L	@(0*4,R5),R0			;
	MOV.L	@(1*4,R5),R1			;
	MOV.L	@(2*4,R5),R2			;

	TST	R0,R0				;
	TST_BIT_OF OVERH_IAMP_DTCALC_100	;

	MOV.L	#H'7FFFFFFF,R1			;LIMIT(本当は4,16,64,256,65536,･･でｼﾌﾄし演算、割るほうもそのﾙｰﾄで割る)
	MOV.L	#H'FFFFFFFF,R2			;

OVERH_IAMP_DTCALC_100
	MOV.L	#_CYC2_SEK_TIME,R0		;1msec*1時間
	MOV.L	@R0,R4				;
	FAR_JSR	#_DIVU_64R1R2_32R4_64R1R2,R0	;R1R2/R4

	FAR_JSR	#_ROOT2_64R1R2_ANS_R2,R0	;R1R2->R2

	MOV.L	#_PV_OVERH_AMP_AVL,R1		;平均値
	MOV.L	R2,@R1				;



	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***********************************
	.IMPORT	_PAR_ROTITBL_Y0		;2 回転 100A
	.IMPORT	_PAR_REVITBL_X0		;3 反転ｽﾄﾛｰｸX0 0mm [0~32767mm]
	.IMPORT	_PAR_DN1ITBL_X0		;7 X0 0mm [0~32767mm]
	.IMPORT	_PAR_OVRH_LATE2		;6 ｵｰﾊﾞﾋｰﾄ閾値倍率 


_OVERH_TBLMAX	.EQU	7		;ﾃｰﾌﾞﾙﾃﾞｰﾀはX0~X6の7個

	.ALIGN 4
_OVERH_AMP_SV_CALC
	SUB_START

	MOV.L	#_OVERH_MODE_SEL,R1				;//0[回転]/1[反転]/2[ふりこ1]/3[ふりこ2]
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BT	OVERH_AMP_SVCAL050				;
	CMP/EQ	#2,R0						;
	BT	OVERH_AMP_SVCAL100				;

;	--------------- 回転------------------------
	MOV.L	#(_PAR_ROTITBL_Y0-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2							;
	M_BRA	OVERH_AMP_SVCAL800					;

OVERH_AMP_SVCAL050
;;;2012-10-18	MOV.L	#_PAR_REVITBL_X0,R10		;
	MOV.L	#(_PAR_REVITBL_X0-_CB_SYS_PARAM000+_W_PARAM_TOP),R10	;
	M_BRA	OVERH_AMP_SVCAL200

OVERH_AMP_SVCAL100
;;;2012-10-18	MOV.L	#_PAR_DN1ITBL_X0,R10		;
	MOV.L	#(_PAR_DN1ITBL_X0-_CB_SYS_PARAM000+_W_PARAM_TOP),R10	;
	M_BRA	OVERH_AMP_SVCAL200

OVERH_AMP_SVCAL200
	MOV	R10,R11				;R10,TOP

	MOV.L	#_SETX_OVERH_LNGTH,R1		;
	MOV.L	@R1,R2				;1mm 1000mm=1m 10000=10m

	MOV.W	@R11,R3				;
	CMP/HI	R3,R2				;R3<R2
	BT	OVERH_AMP_SVCAL300		;
	ADD	#2,R11				;
	MOV.W	@R11,R2				;
	M_BRA	OVERH_AMP_SVCAL800		;MIN SET


OVERH_AMP_SVCAL300
	MOV	R2,R1				;R1=Xn
	MOV	#(_OVERH_TBLMAX-1),R7		;LOOP

	MOV.W	@R10+,R5			;Xn_1
	MOV.W	@R10+,R3			;Yn_1

OVERH_AMP_SVCAL350LOP
	MOV.W	@R10+,R4			;Xn
	MOV.W	@R10+,R2			;Yn
	CMP/HS	R1,R4				;R1=<R4[Xn]
	BT	OVERH_AMP_SVCAL400		;YES
	MOV	R4,R5				;Xn=>Xn_1
	MOV	R2,R3				;Yn=>Yn_1
	ADD	#-1,R7				;
	TST	R7,R7				;
	TST_BIT_ON OVERH_AMP_SVCAL350LOP	;

	ADD	#(_OVERH_TBLMAX-1)*2*2+2,R11	;
	MOV.W	@R11,R2				;
	M_BRA	OVERH_AMP_SVCAL800		;MAX SET

OVERH_AMP_SVCAL400
	MOV	R2,R6				;ﾃﾞｰﾀ異常時のﾘﾐｯﾄ
	FAR_JSR	#_FPU_POS_HOKAN1,R0		;Xn_1=< X =<Xn (Xn_1<Xn)

OVERH_AMP_SVCAL800

	MOV.L	#_SETX_OVERH_AMP,R1		;//OVERH->AMP閾値
	MOV.L	R2,@R1				;2byte

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***********************************
	.IMPORT	_CB_SEQ_CB_COM349		;

	.ALIGN	4				;
_OVERH_AMP_CMP:
	SUB_START

	MOV.L	#_SETX_OVERH_AMP,R1		;//OVERH->AMP閾値
	MOV.L	@R1,R4				;

;	-安全一行程等のための倍率--
	MOV.L	#_CB_SEQ_CB_COM349,R1		;
	MOV.W	@R1,R0				;
	MOV.W	#BIT7,R3			;
	TST	R3,R0				;
	TST_BIT_OF OVERH_AMPCMP_050		;

	MOV.L	#(_PAR_OVRH_LATE2-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2							;
	MOV	R4,R1							;
	MOV.W	#D'1000,R4						;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0				;

	MOV	R2,R4							;

OVERH_AMPCMP_050:








	MOV.L	#_PV_OVERH_AMP_AVL,R1		;平均値
	MOV.L	@R1,R2				;

	CMP/HI	R4,R2				;
	BT	OVERH_AMPCMP_100		;R4<R2 ERR

OVERH_AMPCMP_090:
	MOV.L	#_SQ_OVERH_CMP,R1		;//OVERH-> MAIN
	MOV.W	@R1,R0				;
	AND	#LOW ~BIT0,R0			;
	MOV.W	R0,@R1				;
	FAR_JSR	#_CLR_SQ224_11,R0
	M_BRA	OVERH_AMPCMP_200		;

OVERH_AMPCMP_100:
	MOV.L	#_SQ_OVERH_CMP,R1		;//OVERH-> MAIN
	MOV.W	@R1,R0				;
	OR	#BIT0,R0			;
	MOV.W	R0,@R1				;
	FAR_JSR	#_SET_SQ224_11,R0
OVERH_AMPCMP_200:


	SUB_END
	M_RTS




;	***********************************
;	***				***
;	***********************************
;;	2012-10-19 １サイクル開始～終了をやめて１サイクル終了～1サイクル終了までを測定
;;	.ALIGN 4
;;_OVERH_CYC_START
;;	SUB_START
;;	MOV.L	#_CYC2_INP_STS,R1	;
;;	MOV.W	@R1,R0			;
;;	OR	#BIT0,R0		;
;;	MOV.W	R0,@R1			;
;;	SUB_END
;;	M_RTS


	.ALIGN 4
_OVERH_CYC_END
	SUB_START
	MOV.W	#BIT6,R0		;BIT6=1,BIT0=0
	MOV.L	#_CYC2_INP_STS,R1	;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS


	.ALIGN 4
_OVERH_CYC_STOP
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_CYC2_INP_STS,R1	;BIT6=1,BIT0=0
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS




;//	------- 1ｻｲｸﾙ電力量　------
;_CYC_INP_STS		.SRES	2	;0:ｱｲﾄﾞﾙ(ｻｲｸﾙ終了) 1:ｻｲｸﾙ中->2:NEXTｻｲｸﾙ.....FFFF->1
;_CYC_LTH_STS		.SRES	2	;0:ｱｲﾄﾞﾙ 1:ｻｲｸﾙ中
;	.ALIGN 4
;_CYC_SEK_WORK		.SRES	8	;積算ﾃﾞｰﾀ
;_CYC_SEK_DATA		.SRES	8	;確定ﾃﾞｰﾀ 10w
;_CYC_SEK_TIME		.SRES	4	;1msec*2min=
;_CYC_IVW_PV		.SRES	4	;確定ﾃﾞｰﾀ 0.1kw


;_IVW_WP_SEK_WORK		.SRES	8	;有効1sec
;_IVW_WP_SEK_TIME		.SRES	4	;有効1sec
;_IVW_WP_1S_PV			.SRES	4	;有効1sec

;_IVW_WN_SEK_WORK		.SRES	8	;無効1sec
;_IVW_WN_SEK_TIME		.SRES	4	;無効1sec
;_IVW_WN_1S_PV			.SRES	4	;有効1sec
