;	***********************************
;	***				***
;	***	�t���N���[�Y�֘A	***
;	***				***
;	***********************************
_POS_LATE1		.EQU	D'1000	;100.0%
_POS_GEN_BEFORE_LNG	.EQU	D'1000	;1000��ٽ
_POS_LATE_CALC_MAX	.EQU	D'1000	;1000��ٽ
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
	.IMPORT	_CPUB_HENSA_FLG_CLR			;

_POS_CLS_TYP1_POS_CTL1:
	SUB_START
	MOV.L	#_poslsi1_top+_PLSI_CH1+_PLS_OutPposL,R6		;R/W �w����ٽ����(�c��ٽ)
	MOV.L	@R6,R11							;(data latch)
	MOV.L	#_ACCESS_ERR1+9*4,R6					;**

	SWAP.W	R11,R11							;
	MOV.L	#_POSLSI_CHK_RESTPLS,R1					;
	MOV.L	R11,@R1							;

	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(�ڕW�ʒu������ʒu�쐬,R0=R5=�۰�ނ��邩�ǂ����H)
	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_NOT		;R5=�H�� R0=0��~�H���ł͂Ȃ�
	MOV.L	#_CPOS_STEP_MAX,R1			;//�ݒ�
	MOV.W	@R1,R2					;
	ADD	#1,R2					;
	CMP/EQ	R5,R2					;
	BF	POS_CLS_TYP1_POSCTL1_000		;�ŏI�H���ł͂Ȃ�
POS_CLS_TYP1_POSCTL1_NOT:				;
;	===== ������ݼ�====
;	===== �ʒu�ɂ�鑬�x�؂�ւ��{���x�A���̽ï�ߐؑ�====
	FAR_JSR	#_SPD_STEP_CHG_FWD,R0	;(STEP�ԍ��ؑ�/���x�؂�ւ�)
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;	===========================================
;	===		�ŏI�H��		===
;	===========================================
;	���޼����̂ݍs��
;;	FAR_JSR	#_OPEN_ROT_NEAR_ZERO_CHK,R0		;

	FAR_JSR	#_OPEN_ROT_NEAR2_ZERO_CHK,R0		;(����݂�Ʊ��ۂɂ��邩�ǂ���)
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
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

	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CALC_FULCLS_MXPLS,R1		;���ݸ�MAX��
	MOV.W	R0,@R1				;

;	===== SIG-OFF[1] =====
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_050		;

;	======= ��ꕥ���o����====
;;	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(�ڕW�ʒu������ʒu�쐬)
;;	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
;;	CMP/EQ	#0,R0					;
;;	BF	POS_CLS_TYP1_POSCTL1_030
;;	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;;	FAR_JSR	#_POS_LSI_SLOW_STOP,R0			;
;;	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
;;POS_CLS_TYP1_POSCTL1_030:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	=========================
;	=====(�J�n��������)======
;	=========================
POS_CLS_TYP1_POSCTL1_050:
	MOV	#BIT0,R0				;
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;

	MOV.W	#D'50,R0				;50msec
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	R0,@R1					;�x������=0

;	========================
;	===== �����N��==========
;	========================
;	���N�����g��=TOP-SPEED
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET1,R0	;

	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.W	@R1,R3					;8��ٽ
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

	FAR_JSR	#_LOD_POS_STS_REG,R1			;
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
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_200		;(�ʏ퐧��)

;	====== 1��Ʊ��ۂɓ����Ă���̏���======
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
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
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(�ް��ǂݏo�� R6,R7)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
;;;;;;	CMP/EQ	#0,R0					;(Ʊ��۔͈͓�)
;;;;;;	BF	POS_CLS_TYP1_POSCTL1_118		;
	CMP/EQ	#0,R0					;(Ʊ��۔͈͓�)
	BF	POS_CLS_TYP1_POSCTL1_118		;
;	===================================
;	==== Ʊ��۔͈͓� �I������	===
;	===================================
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
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(�ڕW�ʒu������ʒu�쐬)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0			;ANS R0,R6(�Ʊ������ٽ),R7(1��]���ڕW��ٽ)
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
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;



POS_CLS_TYP1_POSCTL1_PC_END:
	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;

POS_CLS_TYP1_POSCTL1_OUT_WAIT:				;
	XOR	R0,R0					;�܂���
POS_CLS_TYP1_POSCTL1_END:
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



	MOV	#1,R0
	CMP/GT	R3,R6				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+���ֵ���

	MOV	#-1,R0				;
	CMP/GE	R1,R6				;R1=< R6 NO
	BF	POS_CLS_TYP1_NEAR_ZR_CHK_200	;(�͈͓�)
	XOR	R0,R0
POS_CLS_TYP1_NEAR_ZR_CHK_200:			;
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

;	===== INPUT R2()
_CLS_POS_OUT_PLS_MAK1:
	SUB_START

	CMP/PZ	R2
	BT	POS_CLS_TYP1_POSCTL1_320		;
	NEG	R2,R2					;
POS_CLS_TYP1_POSCTL1_320:				;
	MOV	R2,R10					;?

	MOV.L	#_CALC_FULCLS_MXPLS,R1		;���ݸ�MAX��
	MOV.W	@R1,R2				;
	MOV	R2,R3				;
	SHLR	R3				;
	MOV.W	R3,@R1				;

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