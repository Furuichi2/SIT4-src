;	***********************************
;	***				***
;	***	�t���N���[�Y�֘A	***
;	***				***
;	***********************************
_POS_LATE1		.EQU	D'1000	;100.0%
_POS_GEN_BEFORE_LNG	.EQU	D'1000	;1000��ٽ
_POS_LATE_CALC_MAX	.EQU	D'1000	;1000��ٽ

	.IMPORT	_PAR_NEGERR_ENB		;2012-05-30
	.IMPORT	_PAR_NEG_EXITTIM	;2012-10-05

;	***********************************
;	***				***
;	***	���o������		***
;	***	(�N������)		***
;	***				***
;	***********************************
;	ANS 	R0=0	 (������)
;	 	R0.BIT2=1(BUSY����)
;
;_INT_CLS_CTL_FLG,R1	;
;BIT0:INIT START
;BIT1:(���]�K�v)==>��~�҂�<�Čv�Z>
;BIT2:Ʊ��ۂɓ�����<1���>==>��~�҂�<���o=0 �҂�>
;BIT3:Ʊ��ۂɓ������܂��͒�~��̏���(KP�Ɋ֌W�Ȃ��c��ٽ=0�Ȃ�1��ٽ�������Ă���)
;BIT4:
;BIT5:
;BIT6:����
;�c����ٽ+A��A�̏����1000��ٽ�Ƃ���<>
;
;
;(�{���͂��̒��ő��i�̓������l�����āA�h�u�h�w��̏������K�v)
;
;;;;	.IMPORT	_CPUB_HENSA_FLG_CLR			;

_POS_CLS_TYP1_POS_CTL1:
	SUB_START
	MOV.L	#_poslsi1_top+_PLSI_CH1+_PLS_OutPposL,R6		;R/W �w����ٽ����(�c��ٽ)
	MOV.L	@R6,R11							;(data latch)
	MOV.L	#_ACCESS_ERR1+9*4,R6					;**

	SWAP.W	R11,R11							;
	MOV.L	#_POSLSI_CHK_RESTPLS,R1					;
	MOV.L	R11,@R1							;

	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:���]Ӱ�ނŉ׏d�ł̸۰�ނ��s��
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	PUSH_REG1 R5					;
	PUSH_REG1 R0					;
	FAR_JSR	#_KJYU_DATA_INFO_SEL,R0			;227.13
	POP_REG1 R0					;
	POP_REG1 R5					;

;;;;	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;

	.AELSE
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(�ڕW�ʒu������ʒu�쐬,R0=R5=�۰�ނ��邩�ǂ����H)
	.AENDI



	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_NOT		;R5=�H�� R0=0��~�H���ł͂Ȃ�

;	---------------2014-09-22 REPEAT-----------
	MOV.L	#_MOT_REP_F,R1				;//BIT0(��߰ē���
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_NOT20		;


	MOV.L	#_CPOS_STEP_MAX,R1			;//�ݒ�
	MOV.W	@R1,R2					;
	ADD	#1,R2					;
	CMP/EQ	R5,R2					;
	BF	POS_CLS_TYP1_POSCTL1_000		;�ŏI�H��(�߂�)�ł͂Ȃ�

POS_CLS_TYP1_POSCTL1_NOT:				;

;	===== ������ݼ�====
;	===== �ʒu�ɂ�鑬�x�؂�ւ��{���x�A���̽ï�ߐؑ�====
	FAR_JSR	#_SPD_STEP_CHG_FWD,R0	;(STEP�ԍ��ؑ�/���x�؂�ւ�)

POS_CLS_TYP1_POSCTL1_NOT20:				;

	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;	===========================================
;	===		�ŏI�H��		===
;	===========================================
;	���޼����̂ݍs��
;;	FAR_JSR	#_OPEN_ROT_NEAR_ZERO_CHK,R0		;

	FAR_JSR	#_OPEN_ROT_NEAR2_ZERO_CHK,R0		;(����݂�Ʊ��ۂɂ��邩�ǂ���)


	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
	TST	#BIT2,R0				;
	TST_BIT_OF TYP1_OPEN_PRC_200			;���o����?

	FAR_JSR	#_CPU_BA_NZR_ON_JG,R0			;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_050			;���葤�͏I�����
	MOV.L	#_NEAR_IN_FLG,R1			;Ʊ��ۈ���
	MOV.W	@R1,R0					;
	OR	#BIT0,R0				;
	MOV.W	R0,@R1					;
TYP1_OPEN_PRC_050:

	MOV.L	#_NEAR_IN_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_200			;

	FAR_JSR	#_CMPAB_NEAR_END_PROC,R0		;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_200			;

	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;Ʊ���+�����o������

TYP1_OPEN_PRC_200
	XOR	R0,R0
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;




;	===========================
;	===	�ٸ۰��		===
;	===========================
POS_CLS_TYP1_POSCTL1_000:
	MOV.L	#_INT_CLS_CTL_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;�۰�ޏ����J�n?
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_100	;


;;2012-10-05 2012-05-30�ł͕s�	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;2012-10-05 2012-05-30�ł͕s�	MOV.W	@R1,R0				;
;;2012-10-05 2012-05-30�ł͕s�	MOV.L	#_CALC_FULCLS_MXPLS,R1		;���ݸ�MAX��
;;2012-10-05 2012-05-30�ł͕s�	MOV.W	R0,@R1				;

;;;	==============2012-10-05[�{���̌` 2012-05-30�ł͕s�]=============
;;;	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;;	MOV.W	@R1,R0				;
;;;	MOV.L	#_NEG_CTRL_BEFOR_OBJ_PLS,R1	;//�ڕW�|��O
;;;	MOV.L	@R1,R2				;
;;;	ADD	R2,R0				;
;;;	MOV.L	#_CALC_FULCLS_MXPLS,R1		;���ݸ�MAX��
;;;	MOV.L	R0,@R1				;2BYTE->4BYTE 2012-10-05 �^�ύXU2B->U4B�ɕύX
;;;
;	====== 2012-10-05 �d�l�ύX 180�x���ő�ǂ����݂Ƃ���====
	FAR_JSR	#_FULCLS_MAXPLS_CALC,R0




;	===== SIG-OFF[1] =====
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;20060930POR
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_050		;[�����o���p���X�I��]
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	=========================
;	=====(�J�n��������)======
;	=========================
POS_CLS_TYP1_POSCTL1_050:
	MOV	#BIT0,R0				;
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;

;	--------- 2012-05-30----------
;[[neg]][[�����o���ĒB���Ȃ����SQ�֏o�͂��邪���֐i��]]-----------
	FAR_JSR	#_FULCLS_MAXOVER_STEP_INI,R0

	MOV.L	#_PAR_NEG_EXITTIM-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;2 2012-10-5�ǂ����ݎ��s�̑҂�����
	MOV.W	@R1,R0							;
	MOV.L	#_NEG_EXITTIM,R1					;//���ςȐj�̌���ʂ��^�C�}  2012-10-05
	MOV.W	R0,@R1							;


;	===����ݏo�͊����`���ݸނɐ؂�ւ�鎞���-��x���������===
;;;2012-05-30	MOV.W	#D'50,R0			;50msec
	MOV.L	#_FUL_CLS_DLYTM_SV,R1			;2012-05-30
	MOV.W	@R1,R0					;2012-05-30
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	R0,@R1					;�x������=0

;	=====2011-05-11[�K�v��???]======
;;;;;;;;;;;;;;;;;;;;;;;;;;2014-09-16���������Ă���	FAR_JSR	#_FUL_START_FUL_OBJ_SET,R0


;	========================
;	===== �����N��==========
;	========================
;	���N�����g��=TOP-SPEED
;;;;2006-09-30	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET1,R0	;''''''''''''''''@@@@������''''''''''''''
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;''''''''''''''''@@@@������''''''''''''''
;
	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.L	@R1,R3					;30000��ٽ�ł��傤2012-05-30����
							;2012-10-05 2BYTE->4BYTE �^U2B->U4B�ɕύX
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT	;

POS_CLS_TYP1_POSCTL1_100:
POS_CLS_TYP1_POSCTL1_105:			;
;	===========================
;	===	�ŏI�J��	===
;	===========================
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT6,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_110

	FAR_JSR	#_LOD_POS_STS_REG_POR,R1			;
	TST	#BIT2,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_107		;

	FAR_JSR	#_CMPAB_NEAR_END_PROC,R0		;
	TST	R0,R0					;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_108		;
POS_CLS_TYP1_POSCTL1_107:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

POS_CLS_TYP1_POSCTL1_108:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_PC_END		;�I��

;	====================================
;	===	�ʏ�^�]or����ȏ��	====
;	====================================
POS_CLS_TYP1_POSCTL1_110:

;	---------------- 2012-05-30�@[[neg]][[�����o���ĒB���Ȃ����SQ�֏o�͂��邪���֐i��]]-----------
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;2012-05-30
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_112	;
	MOV.W	#(BIT2+BIT0),R0			;1��ٽ���� BIT2:1PLS����
	MOV.L	#_INT_CLS_CTL_FLG,R1		;
	MOV.W	R0,@R1				;
	FAR_JSR	#_FULCLS_MAXOVER_STEP_INI,R0	;
	M_BRA	POS_CLS_TYP1_POSCTL1_OVER99	;
POS_CLS_TYP1_POSCTL1_112:
;	-----------------------------------------


	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_200		;(�ʏ퐧��)

;	====== 1��Ʊ��ۂɓ����Ă���̏���======
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_115		;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;���o�҂������҂�

POS_CLS_TYP1_POSCTL1_115:				;
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	@R1,R0					;�x������=0
	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_117		;
	ADD	#-1,R0					;
	MOV.W	R0,@R1					;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;���o�҂������҂�
POS_CLS_TYP1_POSCTL1_117:				;

;	==== ��~���� ====
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:���]Ӱ�ނŉ׏d�ł̸۰�ނ��s��
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;
	FAR_JSR	#_POS_CLS_RNA_KJYU_NZ_CHEAK,R0		;[1�xƱ��ۂɓ����Ă���̏���]

	.AELSE
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(�ް��ǂݏo�� R6,R7)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
	.AENDI

;;;;2012-10-05	CMP/EQ	#0,R0					;(Ʊ��۔͈͓�)
;;;;012-10-05	BF	POS_CLS_TYP1_POSCTL1_118		;

	CMP/EQ	#0,R0					;
	BT	POS_CLS_TYP1_POSCTL1_ED050		;����

	FAR_JSR	#_OVER_DIG_CHK,R0			;
	TST	R0,R0					;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_OVER99		;
	M_BRA	POS_CLS_TYP1_POSCTL1_118		;




;	===================================
;	==== Ʊ��۔͈͓� �I������	===
;	===================================
POS_CLS_TYP1_POSCTL1_OVER99:				;


POS_CLS_TYP1_POSCTL1_ED050:
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
;	====== ��d��H�΍�<CPUA>===========
	MOV.L	#_INT_CLS_CTL_FLG,R1			;��߂鎖������
	MOV.W	@R1,R0					;
	OR	#BIT6,R0				;
	MOV.W	R0,@R1					;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;

;	==================================
	FAR_JSR	#_POS_LSI_WORK_STOP2,R0
	FAR_JSR	#_POS_LSI_WORK_STOP_CLR,R0
;	==================================

	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	===========================
;	====== ���ݸޏ���==========
;	===========================
POS_CLS_TYP1_POSCTL1_118:					;
;	=== �ċN������(�ċN������KP=1) ====
;	(�����쐬)
;	(�ް��쐬)
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;R6�j��

	MOV.L	#_SET1_INCPOS_KP01,R1			;
	MOV.W	@R1,R3					;8��ٽ
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()
	MOV	#(BIT2+BIT0),R0				;1��ٽ���� BIT2:1PLS����
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;


;	=========�ʏ�^�](Ʊ��ۑ҂�) =====
POS_CLS_TYP1_POSCTL1_200:
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:���]Ӱ�ނŉ׏d�ł̸۰�ނ��s��
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;
	FAR_JSR	#_POS_CLS_RNA_KJYU_FIRST_NZ_CHEAK,R0	;

	.AELSE
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(�ڕW�ʒu������ʒu�쐬)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0			;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
	.AENDI


	CMP/EQ	#0,R0							;
	BF	POS_CLS_TYP1_POSCTL1_220					;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0						;
	FAR_JSR	#_POS_LSI_SLOW_STOP,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_CLS_CTL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0						;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;Ʊ��ۂɂ͂�����

POS_CLS_TYP1_POSCTL1_220:
	CMP/PZ	R0					;+?
	BF	POS_CLS_TYP1_POSCTL1_240		;NO ϲŽ
;	=== �{�����֍s���߂��Ă���@ϲŽ�֌������ׂ���	;
	MOV.L	#_POSLSI_DRIV_SHIN,R4			;//BIT0
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_260		;OK
	M_BRA	POS_CLS_TYP1_POSCTL1_250		;

POS_CLS_TYP1_POSCTL1_240:
	MOV.L	#_POSLSI_DRIV_SHIN,R4			;//BIT0
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_260		;OK

;	======== �s���߂��� ====
POS_CLS_TYP1_POSCTL1_250:
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0						;
	FAR_JSR	#_POS_LSI_SLOW_STOP,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_CLS_CTL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0						;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT					;

POS_CLS_TYP1_POSCTL1_260:

;-------------------------2012-05-30 CHECK ----------------
;;[[neg]]
;;[[neg]]	MOV.L	#_PAR_NEGERR_ENB-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;
;;[[neg]]	MOV.W	@R1,R0							;
;;[[neg]]	CMP/EQ	#1,R0							;
;;[[neg]]	BF	POS_CLS_TYP1_POSCTL1_280				;
;;[[neg]]
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_280		;(�ʏ퐧��)

	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
	TST	#BIT2,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_280		;�܂���ٽ������

;	---��ٽ���Ȃ��Ȃ���---
	FAR_JSR	#_FULCLS_MAXOVER_ERR_WT,R0		;2012-05-30/2012-10-05

;	----------------------------------------------------------
POS_CLS_TYP1_POSCTL1_280:
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;



POS_CLS_TYP1_POSCTL1_PC_END:
	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;

POS_CLS_TYP1_POSCTL1_OUT_WAIT:				;
	XOR	R0,R0					;�܂���
POS_CLS_TYP1_POSCTL1_END:
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.IMPORT	_POSCHG_LINK_DIG_TO_LINK_PLS		;

	.ALIGN	4						;
_FULCLS_MAXPLS_CALC:
	SUB_START

;;;;DEBUG	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;;;DEBUG	MOV.W	@R1,R2				;
;;;;DEBUG	M_BRA	FULCLS_MAXPLSCAL_200		;


	MOV.L	#_SV_OBJ360,R1				;��~�ڕW�ʒu�p�x
	MOV.W	@R1,R3					;
	MOV.W	#D'1800,R4				;
	MOV	R4,R2					;
	SUB	R3,R2					;
	CMP/PZ	R2					;
	BT	FULCLS_MAXPLSCAL_100			;
	ADD	R4,R2					;�p�x0.1�x
FULCLS_MAXPLSCAL_100:					;
	ADD	#1,R2					;+0.1�x
	FAR_JSR	#_POSCHG_LINK_DIG_TO_LINK_PLS,R0	;



FULCLS_MAXPLSCAL_200:					;
	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.L	R2,@R1					;

;;;	MOV.L	#_LINK_NOWROT_OFSPLS_P,R4	;[[[�ڕW]]]
;;;	MOV.L	@R4,R2				;
;;;
;;;	MOV.L	#_LINK_SV_OBJ_ABSPLS,R5		;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
;;;	MOV.L	R1,@R5				;
;;;	MOV.L	R2,@(4,R5)			;
;;;
;;;	MOV.L	#_CALC_FULCLS_MXPLS,R1		;���ݸ�MAX��
;;;	MOV.L	R0,@R1				;2BYTE->4BYTE 2012-10-05 �^�ύXU2B->U4B�ɕύX


	SUB_END
	M_RTS


;	*******************************************
;	***		2012-10-05		***
;	***					***
;	***	180.0�x�ɒB������EXIT		***
;	*******************************************
_OVER_DIG_CHK:
	SUB_START
	MOV.L	#_INC_ENC360,R1			;
	MOV.W	@R1,R2				;
	MOV.W	#D'1798,R0			;179.8
	CMP/HS	R0,R2				;
	BF	OVER_DIGCHK_NOMAL		;���ނ͂��Ă��Ȃ�

OVER_DIGCHK_ERR:
	FAR_JSR	#_FULCLS_MAXOVER_ERR,R0		;��ςȂ�
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;
	MOV.W	@R1,R0				;
	AND	#BIT6,R0			
	TST	R0,R0				;
	TST_BIT_OF OVER_DIGCHK_NOMAL		;R0=0SET
	MOV.B	#1,R0				;R0=1
	M_BRA	OVER_DIGCHK_END
OVER_DIGCHK_NOMAL
	XOR	R0,R0
OVER_DIGCHK_END

	SUB_END
	M_RTS


;	***************************
;	***	2012-05-30	***
;	***	���]�I�[�o	***
;	***************************
;	[[neg]][[�����o���ĒB���Ȃ����SQ�֏o�͂��邪���֐i��]]-----------
	.ALIGN	4						;
_FULCLS_MAXOVER_ERR:
	SUB_START
	M_BRA	FULCLS_MAXOVER_ERRSET		;

_FULCLS_MAXOVER_ERR_WT:
	SUB_START

	MOV.L	#_NEG_EXITTIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF FULCLS_MAXOVER_ERRSET	;
	ADD	#-1,R0				;
	MOV.W	R0,@R1				;
	M_BRA	FULCLS_MAXOVER_ERRWAT		;

FULCLS_MAXOVER_ERRSET:
	MOV.L	#_PAR_NEGERR_ENB-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;
	MOV.W	@R1,R0							;
	CMP/EQ	#1,R0							;
	BF	FULCLS_MAXOVER_ERRWAT					;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_FUL_CLS_MAXOVER_F,LG=W,BIT=(BIT6+BIT0),WKREG=R1	;BIT6:ERR BIT0:����


FULCLS_MAXOVER_ERRWAT:
	SUB_END
	M_RTS

;	***************************
;	***	2012-05-30	***
;	***	���]�I�[�oCLR	***
;	***************************
;	[[neg]][[�����o���ĒB���Ȃ����SQ�֏o�͂��邪���֐i��]]-----------
	.ALIGN	4						;
	.EXPORT	_FULCLS_MAXOVER_CLR	;
_FULCLS_MAXOVER_CLR:
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_FUL_CLS_MAXOVER_F,R1	;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***************************
;	***	2012-05-30	***
;	***	���]�I�[�oINI	***
;	***************************
;	[[neg]][[�����o���ĒB���Ȃ����SQ�֏o�͂��邪���֐i��]]-----------
	.ALIGN	4						;
_FULCLS_MAXOVER_STEP_INI:
	SUB_START

	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_FUL_CLS_MAXOVER_F,LG=W,BIT=~BIT0,WKREG=R1	;


	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	�ǂ����ݒB�����M���o��	***
;	***	224.9  �e�s��		***
;	***	224.10 1��ł�		***
;	***				***
;	***********************************
	.EXPORT	_FULCLS_OVER_SIG

	.ALIGN	4			;2012-05-30
_FULCLS_OVER_SIG
	SUB_START

	XOR	R3,R3
	XOR	R4,R4
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF FULCLS_OVERSG_100		;�ُ�L���Ȃ�
	MOV.W	#BIT9,R3			;�ُ�L��E���Z�b�g�܂ŕێ�
FULCLS_OVERSG_100

;;;;;	TST	#BIT0,R0			;
;;;;;	TST_BIT_OF FULCLS_OVERSG_200		;���䒆�Ȃ�
;;;;;	MOV.W	#BIT10,R4			;�ُ�L��E�L���͂��Ȃ�
;;;;;FULCLS_OVERSG_200

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB224,R1	;
	MOV.W	@R1,R0				;
	MOV.W	#(BIT10+BIT9),R2		;
	NOT	R2,R2				;
	AND	R2,R0				;
	OR	R3,R0				;
	OR	R4,R0				;
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	�ٸ۰��Ʊ���		***
;	***				***
;	***********************************
;	ANS R0(�ٸ۰�ނ��ׂ����ǂ��� R0=0���Ȃ� R0 !=0(�H��)�ٸ۰��)
;	ANS R6 1��]�ڕW��ٽ
;	ANS R7 1��]�Ʊ��ٽ
;
;
;	�ݒ�=0�x�@==>312�x��ڕW 
;	180���傫����Ԃ́@�|�����ōl����(1)
;	����1800���傫�����
;
;	-1*(3600-������ٽ)
	.ALIGN	4						;

_POS_CLS_TYP1_PROC_CHK:
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//��������H��1~11
	MOV.W	@R1,R0				;
	MOV	R0,R5				;�H��PUSH
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R0			;����̍H���̖ڕW�H��
	MOV.L	#_SDATCLS_TRG_STEP,R1;//���x�A���̍Ō�̽ï��
	MOV.W	R0,@R1

	CMP/EQ	R0,R5				;��~������H���ł̂��ٸ۰�ނ͍s��
	BT	POS_CLS_TYP1_PROCCHK_050	;R0=R5 ANS R5=�H��,R0
	XOR	R0,R0				;ANS MAK
POS_CLS_TYP1_PROCCHK_050:			;
	PUSH_REG1 R0				;
;	====================================
	MOV	R5,R0				;�H��
	MOV.L	#_SDATCLS_UPOBJ_PLS,R5		;
	MOV.L	#_CPOS_STEP_MAX,R1		;//�ݒ�
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/GE	R2,R0				;MAX=NOW
	BT	POS_CLS_TYP1_PROCCHK_100	;

	MOV.L	#_SDATCLS_OBJPLS,R5		;
	ADD	#-1,R0				;
	SHLL2	R0				;4BYTE
	ADD	R0,R5				;
POS_CLS_TYP1_PROCCHK_100:
	MOV.L	@R5,R7				;
	MOV	R7,R2
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(�ڕW��ٽ+/-��ٽ�ϊ�)
	MOV	R2,R7				;R7:�ڕW�ʒu;ANS:�ڕW�ʒu(�ݒ�����)
;	============================================

;	==== 2003-02-21 ===
	MOV.L	#_DBG_REVMOD_OBJPLS,R4
	MOV.L	R2,@R4
;	====================

;	============================================
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4	;//�]��p�x +�ް�
	MOV.L	@R4,R6				;
	MOV	R6,R2				;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(�Ʊ����==>+/-��ٽ�ϊ�)
	MOV	R2,R6				;

;	==== 2003-02-21 ===
	MOV.L	#_DBG_REVMOD_CTLPLS,R0	;
	MOV.L	R2,@R0			;
;	===================

	POP_REG1 R0				;
	MOV	R0,R5				
	SUB_END	
	M_RTS

;	Input �H��=R5
;	Input R7
;	ANS 	R0:0,1,-1
;	R0	=0 :Ʊ��۔͈͓�
;		=1 :��(���]�^�]�ł͍s���߂��Ă���/�t�]�^�]�ł͐�������Ȃ�)
;		=-1:��(���^�]�ł͍s������Ȃ�    /�t�]�^�]�ł͍s���߂��Ă���)
;	ANS	R6:�ƱPLS���݈ʒu

;
_POS_CLS_TYP1_NEAR_ZERO_CHEAK:
	SUB_START
	MOV.L	#_SDATCLS_TRG_STEP,R4		;//���x�A���̍Ō�̽ï��
	MOV.W	@R4,R0				;
	ADD	#-1,R0				;
	SHLL2	R0				;
	SHLL	R0				;8byte
	MOV.L	#_SDATCLS_OBJ_NEAR_UPDNPLS,R4	;//+0*4:UP +1*4 DN
	ADD	R0,R4				;
	MOV.L	@R4+,R3				;�ڕW�ʒu+ALFA(����"-")
	MOV.L	@R4,R1				;�ڕW�ʒu-ALFA
	CMP/GE	R1,R3				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_100	;
	MOV	R1,R0				;
	MOV	R3,R1				;
	MOV	R0,R3				;
POS_CLS_TYP1_NEAR_ZR_CHK_100:			;

;	==== 2003-02-21 ===================
	MOV.L	#_DBG_REVMOD_UPPLS,R0	;
	MOV.L	R3,@R0			;
	MOV.L	#_DBG_REVMOD_DNPLS,R0	;
	MOV.L	R1,@R0			;

;	===================================
;;;	MOV	#1,R0
;;;	CMP/GT	R3,R6				;
;;;	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+���ֵ���
;;;
;;;	MOV	#-1,R0				;
;;;	CMP/GE	R1,R6				;R1=< R6 NO
;;;	BF	POS_CLS_TYP1_NEAR_ZR_CHK_200	;(�͈͓� NO)
;;;	XOR	R0,R0				;
;;;POS_CLS_TYP1_NEAR_ZR_CHK_200:			;

	MOV	#1,R0
	CMP/GT	R3,R6				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+���ֵ���

	MOV	#-1,R0				;
	CMP/GE	R1,R6				;R1=< R6 NO
	BF	POS_CLS_TYP1_NEAR_ZR_CHK_201	;(�͈͓� NO)
	XOR	R0,R0				;
	M_BRA	POS_CLS_TYP1_NEAR_ZR_CHK_202	

POS_CLS_TYP1_NEAR_ZR_CHK_200:			;
	NOP
	M_BRA	POS_CLS_TYP1_NEAR_ZR_CHK_202	
POS_CLS_TYP1_NEAR_ZR_CHK_201:			;
	NOP
POS_CLS_TYP1_NEAR_ZR_CHK_202:			;

;	===========================================
;	=== <CPU-A���I������������I���> 	===
;	=== <CPU-B���I���������Ă��I���?>	===
;	===========================================
	PUSH_REG1 R2
	PUSH_REG1 R3

	PUSH_REG1 R0
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
	XOR	R2,R2				;CPUA�͎�������I���
	.AELSE
	FAR_JSR	#_CPU_BA_NZR_ON_JG,R0		;
	MOV	R0,R2				;
	.AENDI
	POP_REG1 R0				;

	TST	R2,R2				;
	TST_BIT_OF POS_CLS_CPUB_TO_CPUA_100	;
	XOR	R0,R0				;
POS_CLS_CPUB_TO_CPUA_100:			;

	POP_REG1 R3
	POP_REG1 R2
	SUB_END
	M_RTS


;	***********************************
;	***	Input R1,R2		***
;	***********************************
;	R1,R2 ��Βl
_CLS_POS_LENGTH_ADD_DATA:
	SUB_START
	MOV.L	#_POSLSI_DRIV_SHIN,R4					;
	MOV.W	@R4,R0							;
	TST	#BIT0,R0						;
	TST_BIT_OF CLS_POS_LENGTH_ADDATA_050				;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R4				;|R1,R2|
CLS_POS_LENGTH_ADDATA_050:						;
	MOV.L	#_LNGTH_TOTAL_OUTPLS,R7					;//������ TOTAL=TOTAL+ADD ADD_DATA<=0
	MOV.L	@R7,R5							;
	MOV.L	@(4,R7),R6						;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R7							;
	MOV.L	R2,@(4,R7)						;
	SUB_END
	M_RTS


;	*******************************************
;	***	260����0�x�̊Ԃ�"-"�ɂȂ�	***
;	*******************************************
;	R0~R2
	.EXPORT	_FUL_CLS_OBJPLS_CHK
_FUL_CLS_OBJPLS_CHK:	;Input R2 ����260~0�̊ԂȂ�"-"����ٽ�ɂȂ�
	SUB_START
	MOV.L	#_SETX_FULCLS_AREA_PLS,R1	;//260.0==>PLS
	MOV.L	@R1,R0				;
	CMP/GE	R0,R2				;R2 OK
	BF	FUL_CLS_OBJPLSCK_050		;
	MOV.L	#_LINK_1ROT_PLS,R1		;//1��]��ٽ(�ݒ�����)
	MOV.L	@R1,R0				;
	SUB	R2,R0				;360-359=1
	NEG	R0,R2				;-1
	CMP/PL	R2				;
	BF	FUL_CLS_OBJPLSCK_050		;
	XOR	R2,R2				;
FUL_CLS_OBJPLSCK_050:				;
	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	�ڕW�ʒu��LENGTH	***
;	***				***
;	***********************************
;	Input R1,R2(�ڕW�ʒu)
;	Output R1,R2                       
	.IMPORT	_POSCHG_LINK_ABSPLS_ROTNUM_OFSPLS
_FUL_CLS_LENGH_ADD_CALC:
	SUB_START

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R5	;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R5						;
	MOV.L	R2,@(4,R5)					;��ΖڕW�ʒu
	
;	== ۯ��ް�����菜��==					;
	FAR_JSR	#_POSCHG_LINK_ABSPLS_ROTNUM_OFSPLS,R0		;R1,R2+/-��]�� �]��p���X(������)
	MOV	R3,R2						;��ٽ
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL200				;
	MOV.L	#_LINK_1ROT_PLS,R1				;<�ҋ@�_340�x 	�ڕW30�x 30-340+360>
	MOV.L	@R1,R4						;		<30>
	ADD	R4,R2						;
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL200				;
	XOR	R2,R2						;"���Z�덷0":���肦�Ȃ��͂�?BREAK CHEAK
FULCLS_LNG_ADD_CAL200:						;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0
	PUSH_REG1 R2
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4			;//�]��p�x +�ް�
	MOV.L	@R4,R2						;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;
	MOV	R2,R3				;
	POP_REG1 R2				;
;	==== �^�]����(CW/CCW)==
	MOV.L	#_INT_POS_CTL_STEP,R1		;//��������H��1~11
	MOV.W	@R1,R4				;���LOAD
	ADD	#-1,R4				;
	SHLL2	R4				;
	MOV.L	#_CPOS_SDAT1_INF1,R0		;
	MOV.L	@(R0,R4),R0			;BIT1=0 CW
	TST	#BIT1,R0			;
	TST_BIT_ON FULCLS_LNG_ADD_CAL300	;
;	====== ���]�^�] ===
	SUB	R3,R2				;
;;	CMP/PZ	R2				;
;;	BT	FULCLS_LNG_ADD_CAL250		;
;;	MOV.L	#_LINK_1ROT_PLS,R1		;
;;	MOV.L	@R1,R4				;
;;	ADD	R4,R2				;
;;FULCLS_LNG_ADD_CAL250:				;
	M_BRA	FULCLS_LNG_ADD_CAL400		;

FULCLS_LNG_ADD_CAL300:
;	====== �t�]�^�] ===
	SUB	R3,R2				;
;;	CMP/PL	R2				;
;;	BF	FULCLS_LNG_ADD_CAL350		;
;;	MOV.L	#_LINK_1ROT_PLS,R1		;
;;	MOV.L	@R1,R4				;
;;	SUB	R4,R2				;
;;FULCLS_LNG_ADD_CAL350:
;;	NOP
FULCLS_LNG_ADD_CAL400:
	XOR	R1,R1						;
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL450				;
	ADD	#-1,R1						;
FULCLS_LNG_ADD_CAL450:

;	====== ����======
	MOV.L	#_LNGTH_ADD_DATA,R4		;//�����t��
	MOV.L	R1,@R4				;
	MOV.L	R2,@(4,R4)			;
	SUB_END
	M_RTS


	.EXPORT	_FUL_DATA_INIT	;USED R1,R0
_FUL_DATA_INIT:
	SUB_START
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	XOR	R0,R0					;
	MOV.W	R0,@R1					;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***********************************
;
;	Input R6:PV
;	Input R7:SV
;
;	Input R3:���ݸޗ�
;
_FUL_PLS_START:
	SUB_START
	PUSH_REG1 R3
	FAR_JSR	#_POS_LSI_WORK_STOP2,R0

	FAR_JSR	#_POS_LSI_WORK_STOP_CLR,R0
	
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(�ڕW�ʒu������ʒu�쐬)
	POP_REG1 R3
	MOV.L	#_POSLSI_DRIV_SHIN,R4				;
	MOV.W	@R4,R0
	AND	#LOW ~BIT0,R0				;
	MOV	R7,R2					;R7:SV R6:PV
	SUB	R6,R2					;SV_-PV_RNA(�΍�)
	CMP/PZ	R2					;
	BT	FUL_PLS_ST120
	OR	#BIT0,R0				;
FUL_PLS_ST120:						;
	MOV.W	R0,@R4					;�����쐬
	XOR	R1,R1					;R1,R2(�����ٽ)
	MOV	R3,R2					;
	FAR_JSR	#_CLS_POS_LENGTH_ADD_DATA,R0		;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;�ʒu����LSI����(������)
	FAR_JSR	#_FWD_REV_START,R1			;�N��
	NOP
	NOP
	NOP
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	2013-04-14		***
;	***	(���x�p�����̂�CALL)	***
;	***				***
;	***********************************
;	�ʒu�P�@��~�ʒu�Q�@��O�ɂ������ʁ@��O�ʒu���ʒu�P���ʒu�Q�̏ꍇ�A�ʒu�P�̎�O�Œ�~����
;	ANS 	R0=1:�ؑ֕K�v
;	ANS	R2=X:�ؑ֍s��
_REV_BEFORE_CHGKOUTEICHK:
	SUB_START
	PUSH_REG1 R5
	PUSH_REG1 R9
	PUSH_REG1 R11
	
	MOV.L	#_INT_POS_CTL_STEP,R11					;//��������H��1~11
	MOV.W	@R11,R9							;���LOAD
	MOV	R9,R5							;
	ADD	#-1,R5							;
	SHLL2	R5							;
	MOV	R5,R2
	SHLL	R2
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R0					;
	ADD	R2,R0
	MOV.L	@R0+,R1							;�ʒu
	MOV.L	@R0,R2							;

	XOR	R5,R5							;
	MOV.L	#_NEG_CTRL_BEFOR_OBJ_PLS,R4				;//�ڕW�|��O
	MOV.L	@R4,R6							;
	ADD	#D'1,R6						;

	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;R5,R6 �����ʒu-->�ڕW�ʒu
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1
	BF	REV_BEFORE_CHGKOUTEICK100				;"-" �߂���

	MOV	R1,R0
	OR	R2,R0
	TST	R0,R0
	TST_BIT_OF REV_BEFORE_CHGKOUTEICK090				;
	M_BRA	REV_BEFORE_CHGKOUTEICK300				;

REV_BEFORE_CHGKOUTEICK090:
	NOP
REV_BEFORE_CHGKOUTEICK100:
	MOV	R9,R0				;
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R2			;����̍H���̖ڕW�H��
	CMP/HS	R2,R9				;
	BT	REV_BEFORE_CHGKOUTEICK300	;���łɂ��̍s��

REV_BEFORE_CHGKOUTEICK200:
	MOV.B	#1,R0				;ANS R2,R0
	M_BRA	REV_BEFORE_CHGKOUTEICK400

REV_BEFORE_CHGKOUTEICK300:
	XOR	R0,R0
REV_BEFORE_CHGKOUTEICK400:

	POP_REG1 R11
	POP_REG1 R9
	POP_REG1 R5

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	****		�׏d�|�ʒu�ϊ�		***
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	INPUT
;	INPUT
;	OUTPUT
	.IMPORT	_SVP_ORGRUP_DEG		;���_�E��ԏ�[�׏d���ޯ�]KN
	.IMPORT	_SVP_ORGRDN_DEG		;���_�E��ԉ�[�׏d���ޯ�]PLS
	.IMPORT	_SVP_ORGLUP_DEG		;���_����ԏ�[�׏d���ޯ�]KN
	.IMPORT	_SVP_ORGLDN_DEG		;���_����ԉ�[�׏d���ޯ�]PLS



_SVPX_KTBL_MIN_KN	.DEFINE		"_SVP_ORGRUP_DEG"
_SVPX_KTBL_MIN_PLS	.DEFINE		"_SVP_ORGLUP_DEG"

_SVPX_KTBL_MAX_KN	.DEFINE		"_SVP_ORGRDN_DEG"
_SVPX_KTBL_MAX_PLS	.DEFINE		"_SVP_ORGLDN_DEG"

;	R3:Yn_1		R5:Xn_1
;	R2:Yn		R4:Xn
;	ANS:R2=y	R1:x
;	limit R6(Yn)

_CLS_KJYU_PLS_CHANGE
	SUB_START

	MOV.L	#_KJYUCLS_OBJ_KN,R1		;//���̍s���̃^�[�Q�b�g
	MOV.L	@R1,R2				;
	MOV.L	#_W4_PV_CTL_KJYU_TTL_P,R1	;//����l=̨���l�\��
	MOV.L	@R1,R0				;�׏d����
	SUB	R0,R2				;
	MOV.L	#_KJYUCLS_KN_HENSA,R1		;//�׏d�̕΍�
	MOV.L	R2,@R1				;

;	------KN->PLS���Z�͕s�v KN=PLS�ɂ��Ă��܂����߃R�����g�ɂ���
	MOV.L	#_KJYUCLS_KN_HENSA_PLS,R1	;//�׏d�̕΍������̃p���X
	MOV.L	R2,@R1				;PLS="+":�����Ɛ��]���Ă���

	SUB_END
	M_RTS




;;	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(�ڕW�ʒu������ʒu�쐬)
;;		�@���̒i�Ńt���N�����s�����ǂ��� R0=0�@���Ȃ� R0 != �t���N������
;;		�AR6:�ڕW��~�ʒu[PLS],R7���j�A�̎����ʒu[PLS] 1��]��̃I�t�Z�b�g�p���X
;;
;;	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0			;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
;;		�@�j�A�[���͈͓̔� R0=0, �{���փI�[�oR0=1,-���փI�[�oR0=-1
;;		 CPUB��CPUA���j�A�[���Ȃ�j�A�y���ƔF��

;	*******************************************
;	***					***
;	***	�ٸ۰�ނ��s���i�����`�F�b�N	***
;	***	[�Ʊ�E�׏d�ؑ�]			***
;	*******************************************
;	�ŏI�i�̏ꍇ���ٸ۰�ނ��Ȃ��B���̃\�t�g�̏�Ō��Ă���
;	input INT_POS_CTL_STEP,CPOS_SDAT1_CNTSTEP
;	ANS R0:0 �ٸ۰�ނ��Ȃ�
;	      :0�ȊO �ٸ۰�ނ���
;	ANS R5:���̍s���̒�~�s��
;[_POS_CLS_START_CONF��_POS_CLS_TYP1_PROC_CHK�̈ꕔ]
;
_POS_CLS_START_CONF:
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//��������H��1~11
	MOV.W	@R1,R0				;
	MOV	R0,R5				;�H��PUSH
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R0			;����̍H���̖ڕW�H��
	MOV.L	#_SDATCLS_TRG_STEP,R1		;//���x�A���̍Ō�̽ï��
	MOV.W	R0,@R1

	CMP/EQ	R0,R5				;��~������H���ł̂��ٸ۰�ނ͍s��
	BT	POS_CLS_START_050		;R0=R5 ANS R5=�H��,R0
	XOR	R0,R0				;ANS MAK
POS_CLS_START_050:				;

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�ڕW�ʒu(��ٽ)�Ɛ���Ώێ����쐬	***
;	***	[�Ʊ�E�׏d�ؑ�]				***
;	***						***
;	***************************************************
;	input _SDATCLS_TRG_STEP	;//���x�A���̍Ō�̽ï��
;	ANS 
;	R7:�ڕW��~�ʒu
;	R6:�Ʊ�ʒu�@�܂��́@�׏d����̈ʒu
;		�׏d�̏ꍇ��(�ڕW�׏d-�����׏d)*K+�ڕW�ʒu
;				(���������ł�+1,0,-1��ٽ�ɂ���)
;
;[_POS_CLS_OBJPLS_PVPLS_MAKE��_POS_CLS_TYP1_PROC_CHK�̈ꕔ]
;
;
;
_POS_CLS_OBJPLS_PVPLS_MAKE
	SUB_START

	MOV.L	#_SDATCLS_TRG_STEP,R1		;//���x�A���̍Ō�̽ï��
	MOV.W	@R1,R0				;[R5]

	MOV.L	#_SDATCLS_UPOBJ_PLS,R5		;[�ڕW�ʒu=�ҋ@�_]
	MOV.L	#_CPOS_STEP_MAX,R1		;//�ݒ�
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/GE	R2,R0				;MAX=NOW
	BT	POS_CLS_OBJPVPLSMAK100	;

	MOV.L	#_SDATCLS_OBJPLS,R5		;[�ڕW�ʒu=�e�i�ݒ�ʒu]
	ADD	#-1,R0				;
	SHLL2	R0				;4BYTE
	ADD	R0,R5				;
POS_CLS_OBJPVPLSMAK100	;

	MOV.L	@R5,R7				;�ҋ@�_�܂��͖ڕW�ʒu(��~)
	MOV	R7,R2
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(�ڕW��ٽ+/-��ٽ�ϊ�)
	MOV	R2,R7				;R7:�ڕW�ʒu;ANS:�ڕW�ʒu(�ݒ�����)

	MOV.L	#_DBG_REVMOD_OBJPLS,R4		;
	MOV.L	R2,@R4				;���ޯ��p�����ް����

;	==========R7:��~�ڕW�ʒu============
	MOV.L	#_FULCLS_MATHED,R1		;//0:�ʒu 1:�׏d
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_OBJPVPLSMAK300	;�׏d JUMP

;	=====	R6:���j�A	======
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4	;//�]��p�x +�ް�
	MOV.L	@R4,R6				;
	MOV	R6,R2				;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(�Ʊ����==>+/-��ٽ�ϊ�)
	MOV	R2,R6				;
	MOV.L	#_DBG_REVMOD_CTLPLS,R0		;
	MOV.L	R2,@R0				;
	M_BRA	POS_CLS_OBJPVPLSMAK500		;


;	=====		�׏d		======
POS_CLS_OBJPVPLSMAK300:
;;	S4b	KJYUCLS_OBJ_KN;		//�e�i�̉׏d�ڕW
;;	S4b	KJYUCLS_KN_HENSA;	//�׏d�̕΍�
;;	S4b	KJYUCLS_KN_HENSA_PLS;	//�׏d�̕΍������̃p���X

	PUSH_REG1 R7				;
	FAR_JSR	#_CLS_KJYU_PLS_CHANGE,R0	;OUTPUT R2:�΍���ٽ+/-
	POP_REG1 R7				;


	TST	R2,R2				;
	TST_BIT_ON POS_CLS_OBJPVPLSMAK310	;

	MOV.B	#1,R2				;0�Ȃ�1�ɂ���

POS_CLS_OBJPVPLSMAK310:				;
						;"R2=2"
	MOV	R7,R6				;OBJ=100PLS 
	SUB	R2,R6				;PV = 98PLS




POS_CLS_OBJPVPLSMAK500:

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	���j�A�@�j�A�[���܂��͉׏d�j�A�[��	***
;	***						***
;	***************************************************
;	input	R6:�Ʊ�ʒu
;	ANS	R0:-1,0,1
	.IMPORT	_SVP_KAJOBJ_HAB	;�׏d�����͈�

_POS_CLS_RNA_KJYU_FIRST_NZ_CHEAK:
	SUB_START

	MOV.L	#_FULCLS_MATHED,R1		;//0:�ʒu 1:�׏d
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_RNA_KJYU_FIRST_NZ_CHK100	;

	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;�ڕW�ʒu�ƃ��j�A�X�P�[���̘_���͋t
	M_BRA	POS_CLS_RNA_KJYU_FIRST_NZ_CHKEND

POS_CLS_RNA_KJYU_FIRST_NZ_CHK100:

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;

POS_CLS_RNA_KJYU_FIRST_NZ_CHKEND:

	SUB_END
	M_RTS





_POS_CLS_RNA_KJYU_NZ_CHEAK:
	SUB_START

	MOV.L	#_FULCLS_MATHED,R1		;//0:�ʒu 1:�׏d
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK100	;

	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;�ڕW�ʒu�ƃ��j�A�X�P�[���̘_���͋t
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND

POS_CLS_RNA_KJYU_NZ_CHK100:

;	---------------------------------------------------
	.IMPORT	_SEQ_DP_TOP

	MOV.L	#_CB_SEQ_CB_COM349,R1		;[[[[[[[[[[[[
	MOV.W	@R1,R0				;
	MOV.W	#BIT12,R4			;

	TST	R4,R0				;
	TST_BIT_OF POS_CLS_RNA_KJYU_NZ_CHK500	;��ϒ��͐��䂵�Ȃ�

	MOV.L	#_FULCLS_TIM_SETFLG,R1		;//BIT0:SET BIT1:��ѱ���()
	MOV.W	@R1,R0				;
	TST	#BIT1,R0
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK400	;

	TST	#BIT0,R0			;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK200	;Ʊ��ۂɓ��������H

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;
	TST	R0,R0				;Ʊ��ۂ�?
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK490	;Ʊ��ۂł͂Ȃ�

	MOV.B	#BIT0,R0			;
	MOV.L	#_FULCLS_TIM_SETFLG,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_FCLS_NZ_TIM_SET,R0		;��Ͼ��
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHK490	;

POS_CLS_RNA_KJYU_NZ_CHK200:
	MOV.L	#_SDAT_WAIT_PVTIM,R4		;
	MOV.L	@R4,R1				;
	TST	R1,R1				;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK490	;��ϒ�

;	--------��ѱ���------------
	MOV.B	#BIT1+BIT0,R0			;
	MOV.L	#_FULCLS_TIM_SETFLG,R1		;
	MOV.W	R0,@R1				;

POS_CLS_RNA_KJYU_NZ_CHK400:
	XOR	R0,R0				;
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND	;


POS_CLS_RNA_KJYU_NZ_CHK490:
	FAR_JSR	#_KJYU_OUT_DIRCT,R0		;ANS R0
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND	;


;	--------------------------------------------
POS_CLS_RNA_KJYU_NZ_CHK500:

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;

POS_CLS_RNA_KJYU_NZ_CHKEND:


	SUB_END
	M_RTS



;
;
;
;
;
_KJYU_NEARZERO_CHK:
	SUB_START

	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//�׏d�̕΍��@�{�F�ڕW-���׏d:"+"�܂��s�����Ă���
	MOV.L	@R1,R2			;"+/-"

	MOV.L	#_SVP_KAJOBJ_HAB,R1	;�׏d�����͈�
	MOV.W	@R1,R3			;

	NEG	R3,R4			;-R4~+R3

	MOV.B	#-1,R0				;��O��
	CMP/GT	R3,R2				;R3<R2
	BT	KJYU_NEARZERO_CK200		;�܂��׏d���オ���Ă��Ȃ�

	XOR	R0,R0				;�͈͓�
	CMP/GE	R4,R2				;
	BT	KJYU_NEARZERO_CK200		;
	MOV.B	#1,R0				;
KJYU_NEARZERO_CK200:

	MOV.L	#_KJYU_CHK_NEARSIG,R1	;-1:�܂��s��(�i��) 1:�׏d�I�[�o(�߂�)
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS


_KJYU_OUT_DIRCT:
	SUB_START

	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//�׏d�̕΍�
	MOV.L	@R1,R0			;"+/-"

	CMP/PZ	R0
	BT	KJYU_OUTDIR100		;
;;;;	MOV.B	#-1,R0
	MOV.B	#1,R0			;R0=1:"+"�֍s���߂��Ă� �߂�
	M_BRA	KJYU_OUTDIR200		;

KJYU_OUTDIR100:
;;;	MOV.B	#1,R0			;
	MOV.B	#-1,R0			;R0=-1"-"�i��

KJYU_OUTDIR200:


	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	�׏d���䒆�@�^�C�}�������䂵������ 349.12
;	�j�A�[��
_FCLS_NZ_TIM_SET
	SUB_START


	MOV.L	#_INT_POS_CTL_STEP,R2	;//��������H��1~11
	MOV.W	@R2,R0			;���LOAD
	ADD	#-1,R0			;
	MOV.L	#_CPOS_SDAT1_TIM,R4	;
	SHLL2	R0			;
	MOV.L	@(R0,R4),R1		;TIM
	MOV.L	#_SDAT_WAIT_PVTIM,R4	;
	MOV.L	R1,@R4			;

	SUB_END
	M_RTS


_FCLS_KJYU_STEPCHG_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_FULCLS_TIM_SETFLG,R1	;
	MOV.W	R0,@R1			;
	
	MOV.L	#_FULCLS_MATHED,R1
	MOV.W	R0,@R1			;
	
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***						***
;	***						***
;	***************************************************
	.IMPORT	_WORD_BIT_TBL1

_KJYU_DATA_INFO_SEL
	SUB_START

	MOV.L	#_SDATCLS_TRG_STEP,R1		;//���x�A���̍Ō�̽ï��
	MOV.W	@R1,R0				;1~10
	TST	R0,R0				;
	TST_BIT_OF KJYU_DATA_INFOSL100		;

	MOV.L	#_CPOS_STEP_MAX,R1		;//�ݒ�
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/EQ	R0,R2				;�߂�s��?
	BT	KJYU_DATA_INFOSL100		;


	ADD	#-1,R0				;
	SHLL	R0				;
	MOV.L	#_WORD_BIT_TBL1,R4		;R0=0�̂Ƃ���BIT0
	ADD	R0,R4				;
	MOV.W	@R4,R2				;�����ޯ�
	MOV.L	#_CPOS_FULCLS_MATEHD_SW,R1	;
	MOV.W	@R1,R3				;
	TST	R2,R3				;
	TST_BIT_OF KJYU_DATA_INFOSL100		;�ʒu

	SHLL	R0				;*2
	MOV.L	#_CPOS_KJYUCLS_OBJ,R1		;
	ADD	R0,R1				;
	MOV.L	@R1,R2				;
	MOV.L	#_KJYUCLS_OBJ_KN,R1		;�e�i�̉׏d�ڕW
	MOV.L	R2,@R1				;

	MEM1_BIT0_F_ORSET MEM=_SQ_CBWK_TOP+_WKSQCB227,LG=W,BIT=(BIT13),WKRG1=R1,WKRG2=R4	;

	MOV.B	#BIT0,R0			;
	M_BRA	KJYU_DATA_INFOSL300		;

KJYU_DATA_INFOSL100
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB227,LG=W,BIT=~(BIT13),WKRG1=R1,WKRG2=R4
	XOR	R0,R0
KJYU_DATA_INFOSL300
	MOV.L	#_FULCLS_MATHED,R1		;//0:�ʒu 1:�׏d
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS





