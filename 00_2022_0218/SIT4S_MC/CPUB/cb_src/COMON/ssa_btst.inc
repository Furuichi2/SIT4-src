;	***********************************
;	***				***
;	***	��������		***
;	***	�ʒu���ߕ�		***
;	***				***
;	***********************************
;	------- 2010-08-20[�������[�h]
	.EXPORT	_BRKTST_POS_START

	.ALIGN	4				;
_BRKTST_POS_CTL:
	SUB_START
	MOV.L	#_INT_POS_CTL_FLAG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT3,R0			;
	TST_BIT_OF BRKTST_POSCTL_0020		;
	M_BRA	BRKTST_POSCTL_0800		;����~��

BRKTST_POSCTL_0020:
	TST	#BIT0,R0			;
	TST_BIT_OF BRKTST_POSCTL_0040		;
	M_BRA	BRKTST_POSCTL_0200		;�N����


BRKTST_POSCTL_0040:
	MOV.L	#_MNWR_POS_CMD,R6	;��ٽ���o����~
	MOV.W	@R6,R0			;
	AND	#(BIT2+BIT1+BIT0),R0	;
	CMP/EQ	#BIT0,R0		;
	BT	BRKTST_POSCTL_0048		;001
	M_BRA	BRKTST_POSCTL_0190		;EXIT
;	==== �ʏ�̈ʒu���ߋN���R�}���h���
BRKTST_POSCTL_0048:

	XOR	R2,R2
	MOV.L	#_INT_POS_STEP_FLG,R1	;
	MOV.W	R2,@R1			;
	MOV.L	#_INT_DND_CTL_STEP,R1;
	MOV.W	R2,@R1
	MOV.L	#_INT_DND_STEP_FLG,R1	;//(�㎀�_���A�̍H���Ǘ�)
	MOV.W	R2,@R1			;
	MOV.L	#_CAM_CNT_CHG_FLG,R1		;//�A�����P�ï�߂ɂȂ���
	MOV.W	R2,@R1				;

;	------ Ӱ��݉^�] --------
	MOV.L	#_SV_POS_CTL_STEP,R1	;//1msec �����̌�����
	MOV.W	@R1,R4			;
	MOV.L	#_INT_POS_CTL_STEP,R2	;//��������H��1~11
	MOV.W	R4,@R2			;


	FAR_JSR	#_POS_LSI_START_INITAL,R0	;((((((((((((�i��E���_�N���X�L����)))))))))))
	FAR_JSR	#_DND_1STEP_DATA_MAK1,R0	;_LNGTH,SHIN,SPEED


	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0
	FAR_JSR	#_ERR_INFO_DT_IN3,R0		;2004-01-28ADD,TOTAL(�N���J�n)

	FAR_JSR	#_POS_PLSOUT_SET_RETRY,R0	;(��~������̋N���̏ꍇ�̂ݗL���E����̂�)

;	== 2004-03 ===
	FAR_JSR	#_ERR_INFO_DT_CHK2,R0		; SGL ONLY
	MOV.W	#D'2,R0			;
	MOV.L	#_ERR_INFO_DLY_TIM,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_ERR_INFO_DT_IN4,R0		;
	FAR_JSR	#_FWD_REV_START,R1		;�N��
	
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT0,WKREG=R1	;

	FAR_JSR	#_BRK_ERR_WORK_CLR1,R0		;_BRK_ERR_CHK_START2	;2003-07-01

	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0
	
BRKTST_POSCTL_0190:
	M_BRA	BRKTST_POSCTL_0800			;

;	===========================================
;	===		�N����			===
;	===========================================
BRKTST_POSCTL_0200:
	MOV.L	#_MNWR_POS_CMD,R6						;
	MOV.W	@R6,R0								;
	CMP/EQ	#BIT0,R0							;
	BT	BRKTST_POSCTL_0240						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT3,WKREG=R1	;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0				;
	FAR_JSR	#_POS_LSI_EMG_STOP,R0						;�}��~
	FAR_JSR	#_LSI_REST_PLS_CHK_STOP_CLR,R0					;2004-03-03
	M_BRA	BRKTST_POSCTL_0800							;


BRKTST_POSCTL_0240:
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0	;�ʒu����LSI����(������)

;	=== FLAG SET(REST-PLS REFLASH-END)====
	eSHi_SET_IM_MOV DST=_eSHi_REST_RL_HF,L1=W,WKREG1=R1,WKREG2=R0,IMD=1	;


;	=== 2004-01-28===
	FAR_JSR	#_ERR_INFO_DT_CHK2,R0		;0CHEAK(�N�����펞) SGL-ONLY
	FAR_JSR	#_ERR_INFO_DT_CHK3,R0		;PLS SGL-OMLY

	.AIF _CMP_ERR_SPEC_ENB	EQ _CMPILE_YES	;2006-09-19
	FAR_JSR	#_ERR_INFO_DT_CHK_CMP2,R0	;SGL-ONLY
	.AENDI


BRKTST_POSCTL_0800:

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		�ڕW�ʒu�쐬		***
;	***					***
;	*******************************************
	.ALIGN	4				;
_BRKTST_POS_START:
	SUB_START

;	----------2014-11-10------------
	XOR	R0,R0
	MOV.L	#_MOVE_MODE_MATH_LATCH,R1	;//0:(�ӂ肱�ȊO �܂��� �i��E���_���[�h)1:(�ӂ肱��Ӱ��݂��Ă���)
	MOV.W	R0,@R1				;
;	----------------------------------


;	=== �ڕW�ʒu����=========
	FAR_JSR	#_BRKTST_OBJ_MAKE,R0

	FAR_JSR	#_X_SET_PV_ABS_TO_OBJ,R0
	FAR_JSR	#_SGL_CMP_ERR_DT_CLR,R0

	FAR_JSR	#_LSI_REST_PLS_CHK_START_CLR,R0	;
	FAR_JSR	#_GPOSIN_HOS_DRV_INI,R0

	XOR	R2,R2
	MOV.L	#_INT_DND_CTL_STEP,R1;
	MOV.W	R2,@R1
	MOV.L	#_INT_DND_STEP_FLG,R1	;//(�㎀�_���A�̍H���Ǘ�)
	MOV.W	R2,@R1

	XOR	R0,R0				;(1���ي�������OFF���Ă��Ȃ��ƂȂ�Ȃ��M���Ȃ̂�)
	MOV.L	#_INT_POS_CTL_FLAG,R1		;
	MOV.W	R0,@R1				;

;	=== 2004-12-20 ===
	MOV.L	#_CNT_STOP_CTRL_FLG,R1	;//BIT0,BIT1:���������I��
	MOV.W	R0,@R1				;

	FAR_JSR	#_CNTREST_HOS_RESET,R1	;

;	=== 2004-01-26 CCS===
	XOR	R0,R0
	MOV.L	#_CCS_BTTN_OFF,R1		;����ON�ȊO�̏�Ԃ��^�]���ɂ������B�K�������~�߂�
	MOV.W	R0,@R1				;


;	====== ��U��~�M��OFF=====
	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB206),LG=W,BIT=(~BIT9),WKRG1=R1,WKRG2=R4

	FAR_JSR	#_CMPCYC_START_CLR,R0		;
	FAR_JSR	#_CMPSTP_CNT_STOP_CLR,R0	;�N�����̂ݘA����~�N���A�i��̓T�C�N�����������j

	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0	;

	FAR_JSR	#_DAI_MOSTPOS_SMPINI,R0		;2003-02-03
	FAR_JSR	#_KJPHOS_SMPINI,R0		;2004-07-05

	FAR_JSR	#_POS_LSI_WORK_STOP2,R0

	XOR	R0,R0			;
	MOV.L	#_INT_CYC_DRV_STS,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_STOP_LATCH,R1		;//BIT0:�į�ߖt
	MOV.W	R0,@R1			;
	MOV.L	#_STOP_LATCH_B,R1	;//BIT0:�į�ߖt
	MOV.W	R0,@R1			;
	MOV.L	#_INT_CLS_CTL_FLG,R1	;//BIT0=1 START �N�����ر
	MOV.W	R0,@R1			;
;;2016-10-31���g�p	MOV.L	#_LOT_CNT_TO_MOD,R1	;
;;2016-10-31���g�p	MOV.W	R0,@R1			;




	MOV.L	#_ORIGN_OBJ_CTL_FLG,R1		;2004-05-24
	XOR	R0,R0				;
	MOV.W	R0,@R1				;


	MOV.W	#BIT0,R0			;�N��
	MOV.L	#_MNWR_POS_CMD,R1		;
	MOV.W	R0,@R1				;

;	--------2009-04-01 �N��������t���O�N���A[���_����]
	MEM1_BIT0_F_ADCLR MEM=_ORIGN_180ARA_FLG,LG=W,BIT=(~BIT5),WKRG1=R4,WKRG2=R1	;���_�N���Ŏg�p
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB207,LG=W,BIT=(~BIT5),WKRG1=R4,WKRG2=R1

;	------- �N��------------
	MOV.W	#BIT0,R0		;
	MOV.L	#_BRKTST_STR_FLG,R1	;
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS


	.ALIGN	4				;
_BRKTST_OBJ_MAKE
	SUB_START
;	--------------------------------------------
	MOV.L	#_CTL_ENC360,R0				;//360.0�x(���܂̂Ƃ���s�v)
	MOV.W	@R0,R1					;
	MOV.L	#_STR_ENC3600_DIG,R4			;//�^�]�J�n����360.0�p�x
	MOV.W	R1,@R4					;

;	-----------------------------------------
	MOV.L	#_LINK_PV_ABSPLS,R4			;
	MOV.L	@R4+,R1					;
	MOV.L	@R4,R2					;
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)
	MOV.L	R1,@(0,R4)				;
	MOV.L	R2,@(4,R4)				;

;	---------- �ڕW�ʒu�ݒ�------
	MOV.L	#_LINK_1ROT_PLS,R4			;//1��]��ٽ(�ݒ�����)
	MOV.L	@R4,R6					;
	XOR	R5,R5					;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R5,R6 +R1,R2=>R1,R2

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4		;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R4				;
	MOV.L	R2,@(1*4,R4)			;�ڕW�ʒu���


;	---------- ����------
	XOR	R0,R0				;BIT0=0:��
	MOV.L	#_POS_DRV_DIRECT,R1		;�N����(SV-LEVEL)
	MOV.W	R0,@R1


;	---------- �ڕW�ʒu�ݒ�------
;;;;;2011-09-14	MOV.L	#_POS_DRV_DIRECT,R1		;�N����(SV-LEVEL)
;;;;;2011-09-14	MOV.W	@R1,R0
;;;;;2011-09-14	FAR_JSR	#_LINK_P_M_MAX,R4		;Input R0:BIT0 DIRECT
						;_LINK_SV_OBJ_ABSPLS,R4		;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)




	FAR_JSR	#_NOW_INC_DIG_MAK,R0			;

;	---------- SPEED SET---------------
;;	MOV.L	#_FREQ_PLSI_MAX_FRQ,R1	;
;;;	MOV.L	#_LINK_MAX_SPD_PLS,R1

	MOV.L	#_BRKTST_OUTSPD_PLS,R1	;
	MOV.L	@R1,R2			;
	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1	;//�ڕW���x
	MOV.L	R2,@R1			;

	FAR_JSR	#_POS_LSI_TOP_SPEED_SET,R0	;input R2




;	-------------------����ײ���ް�MAX-----------
	MOV.W	#_OVRLIDE_LATE_MAX,R2						;
	REG_MOV_TO_MEM	DST_ADR=_SET_SPD_OVRLIDE,L1=W,DT_REG=R2,WKREG1=R1	;
	REG_MOV_TO_MEM	DST_ADR=_SET_ACC_OVRLIDE,L1=W,DT_REG=R2,WKREG1=R1	;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_OVER_RIDE_USEFUL,LG=W,BIT=~BIT1,WKREG=R4	;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_OVER_RIDE_USEFUL,LG=W,BIT=~(BIT1+BIT0),WKREG=R4	;

	FAR_JSR	#_OVERRIDE_CALC_LATE_SEL,R0	;
	FAR_JSR	#_OVERRIDE_CALC_SPED_SEL,R0	;

;	--------- ��ڰ��ُ��ް�1�@����ײ�ނɂ��Ή����Ă���----
	FAR_JSR	#_ACCBRK1_SV_MAKE,R0		;
	FAR_JSR	#_ACCBRK2_SV_MAKE,R0		;


;	------------------2011-09-14----------��~�ʒu-----
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)
	MOV.L	@(0,R4),R1
	MOV.L	@(4,R4),R2

	MOV.L	#_WPARX_BRKTST_STPLNG,R4		;//������ٽ
	MOV.L	@R4,R6					;
	XOR	R5,R5					;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R5,R6 +R1,R2=>R1,R2

	MOV.L	#_BRKTST_STP_ABSPLS,R4					;
	MOV.L	R1,@R4							;
	MOV.L	R2,@(1*4,R4)						;


	SUB_END
	M_RTS
