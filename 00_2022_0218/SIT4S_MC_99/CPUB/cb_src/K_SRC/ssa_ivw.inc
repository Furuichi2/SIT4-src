;	***********************************************************
;	***							***
;	***		�d�̓��j�^�֘A�̉��Z�ꎮ		***
;	***							***
;	***		2010-09-21				***
;	***							***
;	***********************************************************
;SSA_DTMK.SRC
;	---�@���Ұ��̓]������----
_AD_DLY_BUF_MAX		.EQU	100			;
_CONST_PAI		.EQU	314			;3.1415926=3.1416
_CONST_PAI_LAT		.EQU	100			;

	.IMPORT		_DWORD_BIT0_TBL1
	.IMPORT		_DWORD_BIT1_TBL1
	.IMPORT		_PAR_IVW_RANGE			;243
	.IMPORT		_CB_SYS_PARAM241		;
	.IMPORT		_CB_SYS_PARAM242		;

	.IMPORT	_SVP_EP_VOF		;.SRES	2	;�T�[�{�p�����[�^B0�@�@�d�͗p�̾��
	.IMPORT	_SVP_EP_VMX		;.SRES	2	;�T�[�{�p�����[�^B1�@�@�d�͗p�ő�l
	.IMPORT	_SVP_EP_TRQ		;.SRES	2	;�T�[�{�p�����[�^B2�@�@�d�͗p�ٸ�l
	.IMPORT	_SVP_EP_LTM		;.SRES	2	;�T�[�{�p�����[�^B3�@�@�ٸ���x�ꎞ��
	.IMPORT	_SVP_EP_K1		;.SRES	2	;�T�[�{�p�����[�^B4�@�@�����W��A
	.IMPORT	_SVP_EP_K2		;.SRES	2	;�T�[�{�p�����[�^B5�@�@�����W��B
	.IMPORT	_SVP_EP_ADJSIN		;.SRES	2	;�T�[�{�p�����[�^B6�@�@�����d�͕���
	.IMPORT	_SVP_EP_ADJVAL		;.SRES	2	;�T�[�{�p�����[�^B7�@�@�����d��
	.IMPORT	_SVP_ECOM_BASE		;.SRES	2	;�T�[�{�p�����[�^B8�@�@�G�R���[�^��l
	.IMPORT	_SVP_ECOM_SCAL		;.SRES	2	;�T�[�{�p�����[�^B9�@�@�G�R���[�^�X�P�[��


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

;	---�@�ݒ�̓]������----
;	103.12=0 �ߕ��וی�@103.12=1:�d�̓��j�^
	.ALIGN	4				;
_SET_IVW_MOVE
	SUB_START


	MOV.L	#_SVP_EP_LTM,R1			;
	MOV.W	@R1,R2				;
	MOV.W	#_AD_DLY_BUF_MAX,R4		;0~99
	CMP/HI	R2,R4				;
	BT	SET_IVW_MV050			;
	XOR	R2,R2				;100�ȏ��0
SET_IVW_MV050
	MOV.L	#_SET1_EP_LTM,R1		;
	MOV.W	R2,@R1				;



	MOV.L	#_SVP_ECOM_BASE,R0		;�T�[�{�p�����[�^B8�@�@�G�R���[�^��l
	MOV.W	@R0,R2				;0.1kw->*10
	MOV.L	#_SVP_ECOM_SCAL,R0		;�T�[�{�p�����[�^B9�@�@�G�R���[�^�X�P�[��
	MOV.W	@R0,R1				;
	MOV.W	#D'10,R4			;100%�@[���10�{���Ȃ����� 10�Ŋ���]
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)
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
	MOV.L	#_MON_SV_IVW_USED,R1	;//0:�ߕ��׃��j�^ 5A:
	MOV.W	R2,@R1			;

;2010-09-30
	MOV.L	#_SVP_ECOM_BASE,R0		;�T�[�{�p�����[�^B8�@�@�G�R���[�^��l
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
;	***		�d�͍쐬		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_PV1_IVW_DATMAK
	SUB_START

	FAR_JSR	#_AD_SH2_DATA_CHG,R0		;2012-09-25


	MOV.L	#_MON_SV_IVW_USED,R1		;//0:�ߕ��׃��j�^ 5A:
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON PV1_IVW_DTMK_050		;

;	------------- �ߕ��׃��j�^��-----------
	XOR	R0,R0				;
	MOV.L	#_MON_SV_IVW_RNGE,R1		;//[42,43](0:�����_2�� 5A:�����_1��)
	MOV.W	R0,@R1				;
	MOV.L	#_PV_IVW_DAT_DSP,R1		;(�����ݸޗp)[�P�ʐ؂�ւ�]
	MOV.L	R0,@R1				;2byte�ȉ����ް�

	XOR	R0,R0				;
	MOV.L	#_PVP_ECO_METER,R1		;ECO METER
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_POWER_KWH,R1		;1CYCLE
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_EPM_SYOHI,R1		;����
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_EPM_KAISE,R1		;��
	MOV.W	R0,@R1				;
	MOV.L	#_PVP_IVW_DOT,R1		;0:�����_2�� 5A:�����_1�� CPUA->CPUB[�s�v]
	MOV.W	R0,@R1				;
	M_BRA	PV1_IVW_DTMK_900		;


PV1_IVW_DTMK_050
;;;2012-09-25	FAR_JSR	#_AD_SH2_DATA_CHG,R0		;2011-03-22


;	------------- �d�̓��j�^��-----------
	FAR_JSR	#_IVW_DATA_CALC,R0			;

	MOV.L	#_PV_IVW_DAT_1W,R1				;//1[w] data
	MOV.L	R2,@R1						;+/-1w

	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_PV_IVW_DAT_10W,R1				;//10[w]=0.01kw data
	MOV.L	R2,@R1						;0.01kw
	MOV.L	#_PV_IVW_DAT_INP,R1				;//10[w]=0.01kw data[�����鉻ײėp]
	MOV.L	R2,@R1						;


	PUSH_REG1 R2
	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_PV_IVW_DAT_100W,R1				;//10[w] data
	MOV.L	R2,@R1						;0.1kw
	POP_REG1 R3						;32767���ЯĕK�v

	XOR	R4,R4
	MOV.L	#_WPAR_IVW_RANGE,R1				;0:�����_�Q�� 1:�����_�P��
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	PV1_IVW_DTMK_100				;�����_2��JUMP
	MOV	R2,R3						;
	MOV.W	#H'005A,R4					;
PV1_IVW_DTMK_100
	MOV.L	#_MON_SV_IVW_RNGE,R1				;//[42,43](0:�����_2�� 5A:�����_1��)
	MOV.W	R4,@R1						;
	MOV.L	#_PV_IVW_DAT_DSP,R1				;(�߿�݂̻����ݸޗp)[�P�ʐ؂�ւ�]
	MOV.L	R3,@R1						;


;	----------�d�͗�(1cycle,1�b,��1�b)----------
	FAR_JSR	#_SEKI_IVW_DAT_MAKE,R0				;[]





PV1_IVW_DTMK_900

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		AD->�ٸ�쐬		***
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
	MOV.L	#_SVP_EP_VOF,R1			;�̾ēd��
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
	MOV.W	@R5,R1				;[N�m] 1~32767

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)
	MOV.L	#_PV_TRQ_NM_DAT,R1		;+/- 1[N�m]~ 32767
	MOV.L	R2,@R1				;[N�m] or 1w data

;;;;2012-12-10	MOV.L	#_SQ_CBWK_TOP+_WKSQCB246,R1	;
;;;;2012-12-10	MOV.W	R2,@R1				;���ޯ���p

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
;	***		�d�̓��[�^���Z		***
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
	MOV.L	#_SVP_EP_VOF,R1			;�̾ēd��
	MOV.W	@R1,R3				;500(5.00V)
	SUB	R3,R2				;
	MOV.L	#_SVP_EP_VMX,R1			;
	MOV.W	@R1,R4				;
	SUB	R3,R4				;
						;PV=900
						;OFS=500
						;MAX=1000
						;PV=400 OFS=500

;	----- �d�͑����g�p����00
	MOV.L	#_SET1_ECOM_BASE,R0		;
	MOV.L	@R0,R1				;�T�[�{�p�����[�^B8�@�@�G�R���[�^��l*10
						;0.01kw
	ADD	R1,R1				;*2
	MOV	R1,R0				;
	ADD	R1,R1				;*4
	ADD	R1,R1				;*8
	ADD	R0,R1				;*10 1w data

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)

	MOV.L	#_PV_TRQ_NM_DAT,R1		;1w data
	MOV.L	R2,@R1				;

	MOV.L	#_PV_IVW_DAT,R1			;// data(output data)
	MOV.L	R2,@R1				;+/- 1w data 

;;;;2012-12-10	MOV.L	#_SQ_CBWK_TOP+_WKSQCB246,R1	;
;;;;2012-12-10	MOV.W	R2,@R1				;���ޯ���p


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
;	***		�x���f�[�^�쐬		***
;	***					***
;	*******************************************
;	��̧100max
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
	MOV.L	#_AD_DLY_BUF,R5			;�x���ް��쐬
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
	MOV.L	#_SPD_DLY_BUF,R5			;�x���ް��쐬
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
;	***		�p���x			***
;	***					***
;	*******************************************
;	�ݺ��ވړ���/1msec*10msec
;	�ݺ��� 1��] 2048��ٽ
;	3000rpm:50rot/1sec
;	50*2048=102,400��ٽ /1sec���3000rpm�@1msec��100��ٽ
;	66*4096=
;	10msec�Ȃ� 1000��ٽ 10msec�̈ړ��ʂɂ��܂��傤
;	MOV.L	#_ENC_PLS_SPD,R11			;= R11(ad4)
;	�����t��
;	10msec������̧���瑬�x�Z�o
;	���ʂ�PLS/sec
;
;	Freq*2*PAI
;	PLS���x/1��]��ٽ�� * 2 * pai
;
;
	.ALIGN	4				;
_OMEGA_DATA_MAKE:
	SUB_START



	MOV.L	#H'123456,R2			;TEST

	MOV.L	#_ENC_PLS_SPD,R1		;
	MOV.L	@R1,R2				;+/-�@pls/s
	FAR_JSR	#_SPD_DLY_MAKE,R0		;

	MOV.L	#_SPD_ENC_DATX,R1		;
	MOV.L	R2,@R1				;


;	--------- ���ޯ�-----
;;;;	MOV.L	#D'50*8192,R2			;50HZ
;;;;	NEG	R2,R2				;
;;;;	NEG	R2,R2				;
;	---------------------

	MOV.L	#_CONST_PAI*2,R1		;314*2

	MOV.L	#_SET1_INCPLS_1REV,R5		;
	MOV.L	@R5,R4				;1��](ýĽ���ނ�8192)

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;ENC_PLS_SPD[PLS/S]*2*��/(1REV*100)


	MOV.L	#_OMEGA_RAD,R1			;100HZ*3.14=314rad/s
	MOV.L	R2,@R1				;*100�{


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
	MOV.W	#BIT6,R0			;[���ޯ��p]

	MOV.L	#_CB_SEQ_CB_COM345,R0		;
	MOV.W	@R0,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF IVW_DATA_CAL100		;[�d�͑����g�p���Ȃ� JUMP]
;	-------- �d�͌v-------
	FAR_JSR	#_IVW_METER_DATA_MAKE,R0	;
	MOV.L	#_PV_IVW_DAT,R1			;
	MOV.L	@R1,R2				;+/- 1w data
	M_BRA	IVW_DATA_CAL900

IVW_DATA_CAL100:
;	-------- �d�͌v-------
	FAR_JSR	#_TRQ_DATA_MAKE,R0			;TRQ
	FAR_JSR	#_OMEGA_DATA_MAKE,R0			;

	MOV.L	#_OMEGA_RAD,R1				;100HZ*3.14=314rad/s
	MOV.L	@R1,R2					;*100�{
	MOV.L	#_PV_TRQ_NM_DAT,R3			;
	MOV.L	@R3,R1					;+/-

	MOV.L	#_CONST_PAI_LAT,R4			;100
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;ENC_PLS_SPD[PLS/S]*2*��/(1REV*100)
	MOV.L	#_PV_IVW_DAT,R1				;// data
	MOV.L	R2,@R1					;+/- 1w data

;	------------------DEBUG
;;;	MOV.L	#_PV_ENC_SPD_PER,R5		;0~100.00%
;;;	MOV.W	@R5,R2				;
;	------------------
	PUSH_REG1 R2
	FAR_JSR	#_IVW_PARAM_MAKE,R0		;ANS R1,R4
	POP_REG1 R2


	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;1w data *(�␳A-B)/1000

	MOV.L	#_SVP_EP_ADJVAL,R1		;�T�[�{�p�����[�^B7�@�@�����d��
	MOV.W	@R1,R3				;
	EXTU.W	R3,R3				
	MOV.L	#_SVP_EP_ADJSIN,R1		;�T�[�{�p�����[�^B6�@�@�����d�͕���
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
;	***		�␳�W���Z�o		***
;	***					***
;	*******************************************
;	MOV.L	#_SVP_EP_K1,R3			;�T�[�{�p�����[�^B4�@�@�����W��A
;	MOV.W	@R3,R1				;
;	MOV.L	#_SVP_EP_K2,R3			;�T�[�{�p�����[�^B5�@�@�����W��B
;	MOV.W	@R3,R4				;
;	ANS R1,R4
;

	.ALIGN	4				;
_IVW_PARAM_MAKE:
	SUB_START

	MOV.L	#_PV_ENC_SPD_PER,R5		;0~100.00%
	MOV.W	@R5,R2				;

	MOV.L	#_SVP_EP_K1,R3			;�T�[�{�p�����[�^B4�@�@�����W��A
	MOV.W	@R3,R1				;

	MOV.W	#D'10000,R4			;100.00per
	CMP/HS	R4,R2				;
	BT	IVW_PARAM_MK500			;100per�ȏ� R1=�W��B

	MOV.L	#_SVP_EP_K2,R3			;�T�[�{�p�����[�^B5�@�@�����W��B
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
;	***		�d�͗ʐώZ		***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	_PV_IVW_DAT_INP		;2000,00kw [10w]
;
_SEKISAN_TIM_LAT	.EQU	60*1000	;1�� 60sec�@CPUB��1�b�̻����ݸތ덷��1/60�ɂȂ�

	.ALIGN	4				;
_SEKI_IVW_DAT_MAKE:
	SUB_START


;	---		[1]		----
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8


;	--------����@�ώZ(�L��+������)---
	MOV.L	#_CYC_SEK_WORK,R5					;�L��+����CYCLE
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	ADD8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R5							;
	MOV.L	R2,@(4,R5)						;


;	--------�񐶁@�ώZ(������)---
	CMP/PZ	R7							;
	BT	SEKI_IVW_DATMK_020					;+ THEN EXIT
	MOV.L	#_CYC_SEK_KAIWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;
	SUB8B DT_REGH=R7,DT_REGL=R8,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;���ۂɂ�R7,R8��-��"+"�ɂ��đ����Z�Ɠ���
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
					; n(1)->0:�v�Z����
					; n(1)->n+1(2):�v�Z����
					; 0   ->n(1):0�ر����
					
;	--- �ω�����?:�O��v�����ł���Ύ������쐬/����قȂ�v���J�n����--
	TST	R3,R3							;
	TST_BIT_OF SEKI_IVW_DATMK_150					;


	FAR_JSR	#_CYC_SEKI_CALC,R0

SEKI_IVW_DATMK_150:





;	--------------[2]----------------------------
;	=========== �����(����1������1�����ϒl��HMI�o�́@�����قǐ��x�͂悢��5���P�ʂŊ���؂�鐔�l)=========
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8

	MOV.L	#_IVW_WP_SEK_WORK,R5					;1000msec or 60000msec�ώZ
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

;----����d��1�b[���莞��=1000]or1��[���莞��=6000]�ް��쐬
;----1000or60000[���莞��]
;R1,R2/R4(1000or60000)
	CMP/PZ	R1
	BT	SEKI_IVW_DATMK_250			;
	XOR	R1,R1					;
	XOR	R2,R2					;
SEKI_IVW_DATMK_250:
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0		;ANS R2[10w-data]
	MOV.L	#_PVP_EPM_SYOHI,R1			;���� 0.01kw �Œ�
	MOV.W	R2,@R1					;

	XOR	R0,R0
	MOV.L	#_IVW_WP_SEK_TIME,R6			;�L��1sec
	MOV.L	R0,@R6					;

	MOV.L	#_IVW_WP_SEK_WORK,R5			;WORK - CLR
	MOV.L	R0,@R5					;
	MOV.L	R0,@(4,R5)				;

SEKI_IVW_DATMK_300:



;	--------------[3]----------------------------
;	=========== �񐶑���(����1������1�����ϒl��HMI�o�́@�����قǐ��x�͂悢��5���P�ʂŊ���؂�鐔�l)=========
	MOV.L	#_PV_IVW_DAT_INP,R5		;//10[w] data
	MOV.L	@R5,R8				;
	CMP/PZ	R8				;
	BF	SEKI_IVW_DATMK_350		;
	XOR	R8,R8				;
SEKI_IVW_DATMK_350:
	NEG	R8,R8				;
	EXTS_4B_TO_8B REG8B_H=R7,REG4B=R8	;R7,R8

	MOV.L	#_IVW_WN_SEK_WORK,R5					;1000msec or 60000msec�ώZ
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

;----�񐶓d��1�b[���莞��=1000]or1��[���莞��=6000]�ް��쐬
;----1000or60000[���莞��]
;R1,R2/R4(1000or60000)
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0			;ANS R2[10w-data]
	MOV.L	#_PVP_EPM_KAISE,R1				;�� 0.01kw �Œ�
	MOV.W	R2,@R1						;


	XOR	R0,R0
	MOV.L	#_IVW_WN_SEK_TIME,R6			;�L��1sec
	MOV.L	R0,@R6					;

	MOV.L	#_IVW_WN_SEK_WORK,R5			;WORK - CLR
	MOV.L	R0,@R5					;
	MOV.L	R0,@(4,R5)				;

SEKI_IVW_DATMK_400:






	SUB_END
	M_RTS


;	--------------- ���� �J�n(�����يJ�n)-----------------

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
;	***	�P�T�C�N�����쐬�f�[�^	***
;	***********************************
	.ALIGN	4				;
_CYC_SEKI_CALC:
	SUB_START

;	-------------����d�͉��Z------------
	MOV.L	#_CYC_SEK_WORK,R5					;�L��1sec
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w�@[0.01kw]

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
	MOV.L	@(4,R5),R2				;10w�@[0.01kw]
;;;;	MOV.L	#D'1000*D'3600,R4			;1�����ް� 0.01kwh
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



;	-------------�񐶓d�͉��Z------------
	MOV.L	#_CYC_SEK_KAIWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w�@[0.01kw]

	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0				;ANS R2[10w-data]
	MOV.L	#_CYC_IVWKAI_PV1,R1					;�m���ް� 0.01kw ��
	MOV.L	R2,@R1							;+ ONLY

	MOV.L	#D'60000,R4						;
	CMP/GE	R2,R4							;
	BT	CYC_SEKICAL_300					;
	MOV	R4,R2							;
CYC_SEKICAL_300:
	MOV.L	#_CYC_IVWKAI_PV2,R1					;�m���ް� 0.01kw ��
	MOV.W	R2,@R1							;***.** kw


;	-------------�{���̂ݓd�͉��Z------------
	MOV.L	#_CYC_SEK_PULSWORK,R5					;
	MOV.L	@R5,R1							;
	MOV.L	@(4,R5),R2						;10w�@[0.01kw]

	MOV.L	#_CYC_SEK_TIME,R6					;
	MOV.L	@R6,R4							;
	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0				;ANS R2[10w-data]
	MOV.L	#_CYC_IVWPULS_PV1,R1					;�m���ް� 0.01kw ��
	MOV.L	R2,@R1							;+ ONLY

	MOV.L	#D'60000,R4						;
	CMP/GE	R2,R4							;
	BT	CYC_SEKICAL_350					;
	MOV	R4,R2							;
CYC_SEKICAL_350:
	MOV.L	#_CYC_IVWPULS_PV2,R1					;�m���ް� 0.01kw +
	MOV.W	R2,@R1							;***.** kw







;	============(�d�̓��j�^�̕\���l�A�����鉻�g�����h�̃f�[�^)=========
	MOV.L	#_CYC_IVW_PV2,R1				;
	MOV.W	@R1,R3						;***.** kw

	XOR	R4,R4
	MOV.L	#_WPAR_IVWSEK_SEL,R1				;0:���� 1:�d�͗�
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	CYC_SEKICAL_450					;
	MOV.L	#_CYC_IVWHR_PV2,R1				;
	MOV.W	@R1,R3						;***.** wh
	MOV.W	#H'005A,R4					;
CYC_SEKICAL_450:
	MOV.L	#_MON_SV_IVW_CSEL,R1				;//[42,43](0:�����_2�� 5A:�����_1��)
	MOV.W	R4,@R1						;
	MOV.L	#_PVP_POWER_KWH,R1				;***.** kwh
	MOV.W	R3,@R1						;

	FAR_JSR	#_ECO_METER_MAKE,R0			;

;	----- CLR -------
	XOR	R0,R0			;
	MOV.L	#_CYC_SEK_WORK,R5					;�L��1sec
	MOV.L	R0,@R5			;
	MOV.L	R0,@(4,R5)		;

	MOV.L	#_CYC_SEK_KAIWORK,R5	;
	MOV.L	R0,@R5			;
	MOV.L	R0,@(4,R5)		;

	MOV.L	#_CYC_SEK_PULSWORK,R5	;+��
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
;	***	��l�ɑ΂��镽�ϓd��	 ***.**kwh	***
;	***************************************************
	.ALIGN	4				;
_ECO_METER_MAKE1:
	SUB_START

	MOV.L	#_CYC_IVW_PV2,R1			;
	MOV.W	@R1,R2					;***.** kw
	MOV	R2,R1					;

	MOV.L	#_SET1_ECOM_BASE,R0				;
	MOV.L	@R0,R2						;�T�[�{�p�����[�^B8�@�@�G�R���[�^��l*10
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
;	***		��	 ***.**kwh		***
;	***************************************************
;	|��| �^ ((�b+���b*��Ұ�����%/100%)/8)
	.ALIGN	4				;
_ECO_METER_MAKE2:
	SUB_START

;;;	MOV.L	#_PVP_EPM_SYOHI,R1				;���� 0.01kw �Œ�
;;;	MOV.W	@R1,R2						;

	MOV.L	#_CYC_IVWPULS_PV2,R1				;�m���ް� 0.01kw +
	MOV.W	@R1,R2						;***.** kw
;;;;2010-11-02	MOV.L	#_CYC_IVWKAI_PV2,R1				;�m���ް� 0.01kw ��
;;;;2010-11-02	MOV.W	@R1,R4						;***.** kw
;;;;2010-11-02	ADD	R4,R2						;

	MOV.L	#_SVP_ECOM_SCAL,R0				;�T�[�{�p�����[�^B9�@�@�G�R���[�^�X�P�[��
	MOV.W	@R0,R1						;
	MOV.W	#D'100,R4					;100%
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;(0���Z�t�h�~)
	SHLR2	R2						;1/8
	SHLR	R2						;
	TST	R2,R2						;
	TST_BIT_ON ECO_METERMAK2_050				;
	MOV.W	#1,R2						;
ECO_METERMAK2_050:						;
	MOV	R2,R4						;

	MOV.L	#_CYC_IVWKAI_PV2,R1				;�m���ް� 0.01kw ��
	MOV.W	@R1,R2						;***.** kw

	FAR_JSR	#_ECO_METER_CHG,R0				;


	SUB_END
	M_RTS

;	***************************
;	***			***
;	***	R2/R4..MOD	***
;	***	�؂�グ	***
;	***************************
	.ALIGN	4				;
_ECO_METER_CHG:
	SUB_START

	TST	R2,R2						;
	TST_BIT_OF ECO_METERCHG_100				;0
	ADD	R4,R2						;R2/R4���@(R2+(R4-1))/R4:�؏�@
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
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)
	MOV.L	#_PVXSH2_AD_DATA,R1		;//0~1000= 0V~10.00V
	MOV.W	R2,@R1				;

	SUB_END
	M_RTS



;	***********************************************************
;	***							***
;	***	2012-09-25					***
;	***	�I�[�o�q�[�g�d������				***
;	***							***
;	***********************************************************
	.IMPORT	_DIVU_64R1R2_32R4_64R1R2
	.IMPORT	_ROOT2_64R1R2_ANS_R2
	.IMPORT	_FPU_POS_HOKAN1			;Xn_1=< X =<Xn (Xn_1<Xn)

	.IMPORT	_CLR_SQ224_11
	.IMPORT	_SET_SQ224_11
	.IMPORT	_OVERH_MODE_DT_MAK


	.EXPORT	_TRQ_OVERHEAT_CALC	;
;;;;2012-10-19	.EXPORT	_OVERH_CYC_START	;���يJ�n
	.EXPORT	_OVERH_CYC_END		;���ُI��
	.EXPORT	_OVERH_CYC_STOP		;EMG,MODE

;	***********************************
;	***				***
;	***	�������֘A		***
;	***				***
;	***********************************

	.IMPORT	_PAR_IVW_KAMP			;
	.IMPORT	_CB_SYS_PARAM000		;
	.IMPORT	_W_PARAM_TOP			;

	.IMPORT	_SETX_OVERH_LNGTH		;//1mm Main->OVERH SOFT
	.IMPORT	_SETX_OVERH_AMP			;//OVERH->AMP臒l[���ۂ�2BYTE]
	.IMPORT	_OVERH_MODE_SEL			;//0[��]]/1[���]]/2[�ӂ肱]/3[�ӂ肱]
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

;;;2012-10-19	 ���ُI��~���ُI���܂ł𑪒肷��
;;;2012-10-19	MOV.L	#_CYC2_INP_STS,R1		;
;;;2012-10-19	MOV.W	@R1,R0				;
;;;2012-10-19	TST	R0,R0				;
;;;2012-10-19	TST_BIT_OF TRQ_OVERHEAT_CAL450		;BIT6=1(END) or BIT0=1(�J�n) or BIT6=1,BIT0=1(�A���̻���END+�J�n)

	MOV.L	#_CYC2_INP_STS,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF TRQ_OVERHEAT_CAL200		;���ُI�����Ă��Ȃ��ώZ�J�n

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


;	---------- �Ō�̐ώZ ----------
	FAR_JSR	#_OVERH_SEKI_ADD,R0	;

;	-----------���ϓd�����Z------------
	FAR_JSR	#_OVERH_IAMP_DT_CALC,R0	;

;	-----------�I�[�o�q�[�g�d�����Z------
	FAR_JSR	#_OVERH_AMP_SV_CALC,R0	;


;	-----------�I�[�o�q�[�g�d����r------
	FAR_JSR	#_OVERH_AMP_CMP,R0	;

TRQ_OVERHEAT_CAL180:

	M_BRA	TRQ_OVERHEAT_CAL500	;CLR

TRQ_OVERHEAT_CAL200:
;;;;;2012-10-19	MOV.L	#_CYC2_INP_STS,R1		;
;;;;;2012-10-19	MOV.W	@R1,R0				;
;;;;;2012-10-19	TST	#BIT0,R0		;
;;;;;2012-10-19	TST_BIT_OF TRQ_OVERHEAT_CAL250	;��^�]��

;	---------- �ώZ ----------
	FAR_JSR	#_OVERH_SEKI_ADD,R0	;

;;;;;TRQ_OVERHEAT_CAL250:
	M_BRA	TRQ_OVERHEAT_CAL800	;


;	-------------���Z��~�N���A------------------
TRQ_OVERHEAT_CAL400				;

	XOR	R0,R0				;
	MOV.L	#_CYC2_INP_STS,R1		;
	MOV.W	R0,@R1				;

;;;;;;;;2012-10-19	------------�N�������@�N���A����	-----------------
;;;;;;;;2012-10-19	TRQ_OVERHEAT_CAL450				;

	MOV.W	#1,R2					;�ǂ̃��[�h���P��ُ͈�Ƃ��Ȃ�
	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1CNT,R0				;
	TST_BIT_OF TRQ_OVERHEAT_CAL470			;

	MOV.L	#(_PAR_OVHALM_WTCNT-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2

TRQ_OVERHEAT_CAL470				;

	MOV.L	#_CYC2_WAIT_CNTPV,R1		;2012-10-16 �A���̂ݑ҂��J�E���^
	MOV.W	R2,@R1				;2012-10-19�@�A���ȊO���P��ڂ͎̂�


;	------------���Z�����@�N���A����	-----------------
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
;	***	�I�[�o�q�[�g�u���d�������쐬	***
;	***					***
;	*******************************************
	.ALIGN 4
_TRQ_OVERHEAT_DTMAK:
	SUB_START

	MOV.L	#_PVXSH2_AD_DATA,R1		;0~1000= 0V~10.00V
	MOV.W	@R1,R2				;
	
	MOV.L	#_SVP_EP_VOF,R1			;�̾ēd��
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
	MOV.W	@R5,R1				;[N�m] 1~32767

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)

	CMP/PZ	R2				;
	BT	OVERHEAT_DTMK200		;
	NEG	R2,R2				;
OVERHEAT_DTMK200:				;

	MOV.L	#(_PAR_IVW_KAMP-_CB_SYS_PARAM000+_W_PARAM_TOP),R0	;
	MOV.W	@R0,R1							;
	MOV.W	#D'1000,R4						;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)


	MOV.L	#_PV_ABS_OVERH_TRQ,R1		;
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***		�ώZ		***
;	***				***
;	***********************************
	.ALIGN	4			;
_OVERH_SEKI_ADD
	SUB_START

	MOV.L	#_CYC2_SEK_TIME,R1	;1msec*10��
	MOV.L	@R1,R0			;
	ADD	#1,R0			;
	MOV.L	#D'10*60*1000,R4	;1msec*1000(1sec)*60(min)*10:10����MAX
	CMP/HS	R4,R0			;R4=<R0
	BT	TRQ_OVERHEATCALC_OVER	;���Z�s�\
	MOV.L	R0,@R1			;���+1


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
;	***		���ϓd�����Z	***
;	***				***
;	***********************************
;	12BYTE(96�ޯ�)��ٰĂ��Ă��玞�ԂŊ���
;	12BYTE��8BYTE(����*����)�Ŋ����Ă���ٰĂ���
;	IAVL=1/T*ROOT(I1^2+I2^2����)
;	IAVL=ROOT{(I1^2+I2^2����)/(T^2)}
;
;
;	AD*32767(500�O��)/1000=32767 (500[Nm])
;	I*I=1000*1000���4BYTE�Ŏ��܂�
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

	MOV.L	#H'7FFFFFFF,R1			;LIMIT(�{����4,16,64,256,65536,���ż�Ă����Z�A����ق�������ٰĂŊ���)
	MOV.L	#H'FFFFFFFF,R2			;

OVERH_IAMP_DTCALC_100
	MOV.L	#_CYC2_SEK_TIME,R0		;1msec*1����
	MOV.L	@R0,R4				;
	FAR_JSR	#_DIVU_64R1R2_32R4_64R1R2,R0	;R1R2/R4

	FAR_JSR	#_ROOT2_64R1R2_ANS_R2,R0	;R1R2->R2

	MOV.L	#_PV_OVERH_AMP_AVL,R1		;���ϒl
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
	.IMPORT	_PAR_ROTITBL_Y0		;2 ��] 100A
	.IMPORT	_PAR_REVITBL_X0		;3 ���]��۰�X0 0mm [0~32767mm]
	.IMPORT	_PAR_DN1ITBL_X0		;7 X0 0mm [0~32767mm]
	.IMPORT	_PAR_OVRH_LATE2		;6 ����˰�臒l�{�� 


_OVERH_TBLMAX	.EQU	7		;ð����ް���X0~X6��7��

	.ALIGN 4
_OVERH_AMP_SV_CALC
	SUB_START

	MOV.L	#_OVERH_MODE_SEL,R1				;//0[��]]/1[���]]/2[�ӂ肱1]/3[�ӂ肱2]
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BT	OVERH_AMP_SVCAL050				;
	CMP/EQ	#2,R0						;
	BT	OVERH_AMP_SVCAL100				;

;	--------------- ��]------------------------
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
	MOV	R2,R6				;�ް��ُ펞���Я�
	FAR_JSR	#_FPU_POS_HOKAN1,R0		;Xn_1=< X =<Xn (Xn_1<Xn)

OVERH_AMP_SVCAL800

	MOV.L	#_SETX_OVERH_AMP,R1		;//OVERH->AMP臒l
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

	MOV.L	#_SETX_OVERH_AMP,R1		;//OVERH->AMP臒l
	MOV.L	@R1,R4				;

;	-���S��s�����̂��߂̔{��--
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








	MOV.L	#_PV_OVERH_AMP_AVL,R1		;���ϒl
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
;;	2012-10-19 �P�T�C�N���J�n�`�I������߂ĂP�T�C�N���I���`1�T�C�N���I���܂ł𑪒�
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




;//	------- 1���ٓd�͗ʁ@------
;_CYC_INP_STS		.SRES	2	;0:�����(���ُI��) 1:���ْ�->2:NEXT����.....FFFF->1
;_CYC_LTH_STS		.SRES	2	;0:����� 1:���ْ�
;	.ALIGN 4
;_CYC_SEK_WORK		.SRES	8	;�ώZ�ް�
;_CYC_SEK_DATA		.SRES	8	;�m���ް� 10w
;_CYC_SEK_TIME		.SRES	4	;1msec*2min=
;_CYC_IVW_PV		.SRES	4	;�m���ް� 0.1kw


;_IVW_WP_SEK_WORK		.SRES	8	;�L��1sec
;_IVW_WP_SEK_TIME		.SRES	4	;�L��1sec
;_IVW_WP_1S_PV			.SRES	4	;�L��1sec

;_IVW_WN_SEK_WORK		.SRES	8	;����1sec
;_IVW_WN_SEK_TIME		.SRES	4	;����1sec
;_IVW_WN_1S_PV			.SRES	4	;�L��1sec