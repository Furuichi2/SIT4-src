_BANK_CNT_STEP_NEXT_CHK:
	SUB_START
;	===== �ŏI�H���ōŏI�ڕW�ʒu�𒴂����玟�̉�]���ւ̐؂�ւ����s��
	MOV.L	#_INT_POS_CTL_STEP,R11			;//��������H��1~11
	MOV.W	@R11,R0					;
	ADD	#-1,R0					;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1			;
	MOV.L	@(R0,R1),R2				;����̍H���̖ڕW�H��
	MOV.L	#_CPOS_STEP_MAX,R1			;
	MOV.W	@R1,R3					;
	ADD	#1,R3					;�ݒ�+1(�A���1�ï��)
	CMP/EQ	R2,R3					;
	BT	BCNT_STEP_NEXTCHK_100			;(�ŏI�H������)
	M_BRA	BCNT_STEP_NEXTCHK_EXT			;�ŏI�H�����s�����Ƃ��Ă��Ȃ����c��ʂ��������Ƃ͗L��
							;...�s�v
;	======= �ŏI�H�������̏��=======
;	======= ���������Ǝc�苗��=====
BCNT_STEP_NEXTCHK_100:
	MOV.L	#_CPOS_SDAT1_STPAPOS,R4					;
	MOV	R0,R2							;
	SHLL	R2							;
	ADD	R2,R4							;
	MOV.L	@R4+,R1							;
	MOV.L	@R4,R2							;�ڕW�ʒu(SV_OBJ_ABSPLS)

	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1
	BF	BCNT_STEP_NEXTCHK_200			;"-" ������JUMP
	TST	R1,R1					;
	TST_BIT_OF BCNT_STEP_NEXTCHK_120		;
	M_BRA	BCNT_STEP_NEXTCHK_CHK			;
BCNT_STEP_NEXTCHK_120:
	TST	R2,R2					;
	TST_BIT_OF BCNT_STEP_NEXTCHK_200		;
	M_BRA	BCNT_STEP_NEXTCHK_CHK			;

;	--- ������(�T�C�N���ύX���s�Ȃ�)---
BCNT_STEP_NEXTCHK_200:
;(��~�w�߂��o�Ă���Α����Ȃ�)
	MOV.L	#_CPOS_MOD_FLG1,R1					;
	MOV.W	@R1,R0							;
	TST	#BIT2,R0						;
	TST_BIT_ON BCNT_STEP_NEXTCHK_250				;�ҋ@�_��~���Ȃ��^�]

	MOV.L	#_STOP_LATCH_B,R1					;//BIT0:�į�ߖt
	MOV.W	@R1,R0							;
	TST	#BIT0,R0						;
	TST_BIT_OF BCNT_STEP_NEXTCHK_250				;

;	----- ��~�����ON(���肦�Ȃ�) -----
	MEM1_BIT0_TO_BIT7_ORSET MEM=_STOP_LATCH,LG=W,BIT=BIT0,WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_CNT_STOP_CTRL_FLG,LG=W,BIT=BIT0,WKREG=R1	;
	M_BRA	BCNT_STEP_NEXTCHK_EXT					;


BCNT_STEP_NEXTCHK_250:

	MOV.L	#_CPOS_MOD_FLG1,R1					;
	MOV.W	@R1,R0							;
	TST	#BIT3,R0						;
	TST_BIT_OF BCNT_STEP_NEXTCHK_300				;(��~�̂Ȃ��^�]���̂ݕ␳����)

;	========== �����_�␳(�^�C�}���S���Ȃ��^�]) ============
;;;	FAR_JSR	#_GPOINT_HOS_CALC,R0			;CPU-A/B()
;	==================================
;;;;;;;;20060919	.AIF	_CB_CPU_SEL EQ	_CB_CPUB	;
;;;;;;;;	FAR_JSR	#_CNT_SYNC_HOS_SPD_TYP,R0		;
;;;;;;;;	.AENDI					;

;	========== �V�c����ٽ�␳===============
;	�덷��1000PLS�𒴂�������g����ς��� 1HZ
;	�덷��2000PLS�𒴂�������g����ς��� 2HZ
;	�덷��3000PLS�𒴂�������g����ς��� 4HZ
;
;
;
;	====================================
BCNT_STEP_NEXTCHK_300:

	FAR_JSR	#_CNT_VMODE_NEXT_CYCL_START,R0		;(STOPׯ��͂܂����������������)

	M_BRA	BCNT_STEP_NEXTCHK_EXT			;


;	====(�ŏI�H�������ł����ɂ���)=====
BCNT_STEP_NEXTCHK_CHK:
	MOV.L	#_CNT_STOP_CTRL_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON BCNT_STEP_NEXTCHK_EXT	;
;	=== ��~�̌��Z�͂ǂ��ł��ǂ�====
;	=== ��~������ꍇ�͒�~�ōs�����猋�ǂ͍ŏI�H�������ň���===
	FAR_JSR	#_CNT_GPOINT_STOP_TYP2,R0	;�A����~�������\���ǂ����`�F�b�N


BCNT_STEP_NEXTCHK_EXT:
	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	�H���؂�ւ�		***
;	***	data add		***
;	***				***
;	***********************************
_CNT_VMODE_NEXT_CYCL_START:
	SUB_START
	FAR_JSR	#_CHG_STEP_INFO_MAKE_ESTEP_BEFOR,R0	;����p
	FAR_JSR	#_CHG_STEP_INFO_MAKE_STEP_DAT,R0	;����p

	FAR_JSR	#_CPU_AB_CST_ON_OUT2,R0			;���ւ�����!
	FAR_JSR	#_MOTION_CYCLE_END,R0			;
	FAR_JSR	#_MOTION_CYCLE_ED2,R0			;2003-07-09
	FAR_JSR	#_LOT_SIG_FLG_CLR,R0			;�ʏ�̘A��
;;2016-10-31	FAR_JSR	#_DBG_END_CNT3,R0			;

;	--------- 2020-05-07-----------
	MOV.L	#_M_LINK_AREASIG,R4			;
	MOV.W	@R4,R0						;
	TST	#(BIT1),R0						;���~����̊J�n
	TST_BIT_OF VMODE_LOT_SIG_ON			;
	MOV.L	#_LOT_CHK_FLG,R1			;
	MOV.W	@R1,R0						;
	OR	#(BIT2+BIT1+BIT0),R0			;(�ҋ@�_�͒ʉ�)
	MOV.W	R0,@R1						;
VMODE_LOT_SIG_ON:

;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB260,R4	;
;;;	MOV.W	R0,@R4						;
;;;
;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB257,R1		;257.0,1,2,3(END),4
;;;	MOV.W	@R1,R0
;;;	ADD		#1,R0
;;;	MOV.W	R0,@R1
;	-----------------------------------


	XOR	R0,R0					;
	MOV.L	#_INT_POS_STEP_FLG,R1			;//�ï��,�i��苤��
	MOV.W	R0,@R1					;

	FAR_JSR	#_BANK_CHK_NEXT_CYCL_STR1,R0		;

;	------------------2006-12-18----------------------
	FAR_JSR	#_OVER_RID_UPDN_LAT_DTMK,R0		;20060919:
;	--------------------------------------------------

	MOV.L	#_SV_POS_CTL_STEP,R1			;//1msec �����̌�����
	MOV.W	@R1,R4					;
	MOV.L	#_INT_POS_CTL_STEP,R2			;//��������H��1~11
	MOV.W	R4,@R2					;


;;	FAR_JSR	#_POS_1STEP_DATA_MAK2,R0		;_LNGTH,SHIN,SPEED<�ݒ肩�狁�߂�>


;	==== �ŏI�H�������łȂ���Α��x��؂�ւ��邾��===
;	LINKX-->LINK��
;	���̑O�̏����ōs���Ă���͂��Ȃ̂ŕs�v
	MOV.L	#_CPOS_MOD_FLG1,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT3,R0				;
	TST_BIT_ON CNT_VMODE_NEXT_CYCLSTR_050		;

;	=== ��ϒ�~�L�� ===�����ňړ��ʂ͍쐬���Ȃ�===
	FAR_JSR	#_CNT_SPD_SET,R0			;(����ł̓X�e�b�v��̉^�]�J�n�Ƃ͂������N���܂ŗ����Ă��邩��ǂ�)
	M_BRA	CNT_VMODE_NEXT_CYCLSTR_100


CNT_VMODE_NEXT_CYCLSTR_050:
;	=== ��ϒ�~�S���Ȃ� ===�����ňړ��ʂ��쐬===
	FAR_JSR	#_POS_CNT_BANK_DTMAK2,R0		;CNT_SPD
	FAR_JSR	#_BANK_CNT_STOP_CHK_TYP1,R0		;

CNT_VMODE_NEXT_CYCLSTR_100:



;;;����	FAR_JSR	#_POS_CNT_BANK_DTMAK2,R0		;

;	==== 2004-03-29 ====
	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0	;OK!
	FAR_JSR	#_MOTION_CYCLE_START,R0		;
	MOV.L	#_CAM_CNT_CHG_FLG,R1	;	//�A�����P�ï�߂ɂȂ���
	MOV.W	#BIT0,R0		;
	MOV.W	R0,@R1			;


;	==================================
	FAR_JSR	#_CMPCYC_START_CLR,R0
;	===============================================
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_NEAR_IN_FLG,LG=W,BIT=~BIT0,WKREG=R1 ;//
	FAR_JSR	#_SET_NZ_TIM_DAT,R0	;2003-06-13
;	===============================================
	FAR_JSR	#_FUL_DATA_INIT,R0
;	==================================
	FAR_JSR	#_BRK_ERR_WORK_CLR1,R0		;_BRK_ERR_CHK_START2	;2003-07-01
;	================<<<2004-03-25>>>==========	
	FAR_JSR	#_CHG_STEP_INFO_MAKE_ESTEP_AFTER,R0		;����p
	FAR_JSR	#_CHG_STEP_INFO_MAKE_STEP_DAT,R0		;����p
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	*******************************************
;	***********************************
;	***				***
;	***	�ړ������̂�+SPEED	***
;	***				***
;	***********************************
;	FAR_JSR	#_LENGH_ADD_CALC,R0	;
;	��
;	FAR_JSR	#_LENGH_ADD_CALC_SV_TYPE,R0	;
;	�ɂȂ��Ă��邾��
;	(��]�r���̉��Z�@�P��]��)

;	===== �^�C�}��~��N����===
_POS_CNT_BANK_DTMAK3:				;�㎀�_���=0�œr���Ŏ~�܂鎞
	SUB_START

;	-------debug break-point set----------
	PUSH_REG1 R0
	PUSH_REG1 R1
	MOV.L	#_di2_cb_ctl2,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT7,R0		;�A����ı��ߖt
	TST_BIT_OF CNTBANK_DBGBRK_100	;

	NOP
	NOP
	NOP
	NOP
	NOP


CNTBANK_DBGBRK_100

	
	POP_REG1 R1
	POP_REG1 R0




	FAR_JSR	#_X_SET_PV_ABS_TO_OBJ,R0			;20060919

	FAR_JSR	#_POS_CNT_LAST_STEP_CHK,R0	;

	MOV.L	#_CPOS_SDAT1_STPAPOS,R4			;//�N����,���̑��ŉ��Z 8byte data
	TST	R0,R0					;
	TST_BIT_OF POS_CNT_BANKDTMAK12_COM		;�ŏI�H���łȂ����

	MOV.L	#_CPOS_SDAT1_STPAPOS2,R4		;//�N����,���̑��ŉ��Z 8byte data
	MOV.W	#1,R0					;
	M_BRA	POS_CNT_BANKDTMAK123_COM		;�ŏI�H�������Ȃ�


_POS_CNT_BANK_DTMAK2:					;�ǂ��ɂ��~�܂�Ȃ��Ƃ�
	SUB_START
	M_BRA	POS_CNT_BANKDTMAK12_COM

;	===== ����̋N����===
_POS_CNT_BANK_DTMAK1:
	SUB_START

;;;;2014-09-14	----------------------------------------------
;;;;2014-09-14	MOV.L	#_POS_HOLD_RDY_EXITF2,R1	;//���傤���Ȃ�
;;;;2014-09-14	MOV.W	@R1,R0				;
;;;;2014-09-14	TST	#BIT0,R0			;
;;;;2014-09-14	TST_BIT_OF POSCNT_BANKDT050		;
;;;;2014-09-14
;;;;2014-09-14	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4		;//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)
;;;;2014-09-14	MOV.L	@(0,R4),R1			;
;;;;2014-09-14	MOV.L	@(4,R4),R2			;
;;;;2014-09-14	M_BRA	POSCNT_BANKDT075		;
;;;;2014-09-14
;;;;2014-09-14
;;;;2014-09-14POSCNT_BANKDT050
;;;;2014-09-14
;;;;2014-09-14	FAR_JSR	#_X_SET_PV_ABS_TO_OBJ,R0			;20060919
;;;;2014-09-14
;;;;2014-09-14	MOV.L	#_LINK_PV_ABSPLS,R4	;(�ٸ۰�ގ��͑Ώۂ�ς���)
;;;;2014-09-14	MOV.L	@R4+,R1				;
;;;;2014-09-14	MOV.L	@R4,R2				;
;;;;2014-09-14
;;;;2014-09-14POSCNT_BANKDT075

	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4		;//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)
	MOV.L	@(0,R4),R1			;
	MOV.L	@(4,R4),R2			;

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R5		;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R5				;
	MOV.L	R2,@(4,R5)			;
	MOV.L	#_LINKX_SV_OBJ_ABSPLS,R5	;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R5				;
	MOV.L	R2,@(4,R5)			;

POSCNT_BANKDT100

	FAR_JSR	#_POS_CNT_LAST_STEP_CHK,R0	;�㎀�_�^�C�}�Ȃ��Ŏ~�܂鎞�E�~�܂�Ȃ���

	MOV.L	#_CPOS_SDAT1_STPAPOS,R4		;
	TST	R0,R0				;
	TST_BIT_OF POS_CNT_BANKDTMAK12_COM	;�ŏI�H���łȂ����

	MOV.L	#_CPOS_SDAT1_STPAPOS2,R4	;//�N����,���̑��ŉ��Z 8byte data
	MOV.W	#1,R0				;
	M_BRA	POS_CNT_BANKDTMAK123_COM	;�ŏI�H�������Ȃ�













POS_CNT_BANKDTMAK12_COM:
	FAR_JSR	#_POS_CNT_LAST_STEP_CHK,R0	;

	MOV.L	#_CPOS_SDAT1_STPAPOS,R4		;//�N����,���̑��ŉ��Z 8byte data
	TST	R0,R0				;
	TST_BIT_OF POS_CNT_BANKDTMAK12_050	;
	MOV.L	#_CPOS_SDAT1_STPAPOS2,R4	;//�N����,���̑��ŉ��Z 8byte data
POS_CNT_BANKDTMAK12_050:



	MOV.L	#_INT_POS_CTL_STEP,R2		;//��������H��1~11
	MOV.W	@R2,R0				;
POS_CNT_BANKDTMAK123_COM:
	ADD	#-1,R0				;
	SHLL2	R0				;
	SHLL	R0				;*2
	ADD	R0,R4				;
	MOV.L	@R4+,R1				;
	MOV.L	@R4,R2				;(�ڕW�ʒu)
	FAR_JSR	#_POS_CNT_BANK_DTMAK_CM,R0	;LINKX����v�Z����ADDDATA�쐬
	FAR_JSR	#_CNT_SPD_SET,R0		;



	SUB_END
	M_RTS




;	***************************************************
;	***	���x�p�����ʂ̍ŏI�X�e�b�v������	***
;	***************************************************
;	ANS R0!=0 �ŏI
_POS_CNT_LAST_STEP_CHK:
	SUB_START
	PUSH_REG1 R1
	PUSH_REG1 R2
	PUSH_REG1 R3

	MOV.L	#_INT_POS_CTL_STEP,R2		;//��������H��1~11
	MOV.W	@R2,R0				;
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R2			;����̍H���̖ڕW�H��
	MOV.L	#_CPOS_STEP_MAX,R1		;
	MOV.W	@R1,R3				;
	ADD	#1,R3				;�ݒ�+1(�A���1�ï��)

	XOR	R0,R0				;
	CMP/EQ	R2,R3				;
	BF	POS_CNT_LASTSTEPCHK_END		;
	MOV	#-1,R0				;LAST����
POS_CNT_LASTSTEPCHK_END:			;

	POP_REG1 R3
	POP_REG1 R2
	POP_REG1 R1

	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	�ړ������̂�		***
;	***				***
;	***********************************
;	FAR_JSR	#_LENGH_ADD_CALC,R0	;
;	��
;	FAR_JSR	#_LENGH_ADD_CALC_SV_TYPE,R0	;
;	�ɂȂ��Ă��邾��
;	(��]�r���̉��Z�@�P��]��)
_CNT_SPD_SET:
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R2			;//��������H��1~11
	MOV.W	@R2,R0					;
	ADD	#-1,R0					;
	SHLL2	R0					;
	MOV.L	#_CPOS_SDAT1_SPD,R4			;	//SETX-->�N����COPY
	MOV.L	@(R0,R4),R2				;
	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1			;//�ڕW���x
	MOV.L	R2,@R1					;
	FAR_JSR	#_POS_LSI_TOP_SPEED_SETX,R1		;
	SUB_END
	M_RTS

_POS_CNT_BANK_DTMAK_CM:
	SUB_START

	FAR_JSR	#_BANK_LENGH_ADD_CALC_SV_TYPE,R0	;LINKX�̂�+

	XOR	R3,R3				;
	CMP/PZ	R1				;+���]?
	BT	POS_CNT_BANKDTMKCM_050		;
	MOV	#BIT0,R3			;
POS_CNT_BANKDTMKCM_050
	MOV.L	#_POSLSI_DRIV_SHIN,R1	;//BIT0
	MOV.W	@R1,R0			;
	AND	#LOW ~BIT0,R0		;
	OR	R3,R0			;
	MOV.W	R0,@R1			;

POS_CNT_BANKDTMKCM_EXT:
	SUB_END
	M_RTS








;	***************************************************
;	***						***
;	***	BANK2 �ް��쐬				***
;	***	�N����BANK1�ް����쐬����ɌĂ΂��	***
;	***	MODE�֌W�Ȃ��ŌĂ΂��̂ł��̒�������	***
;	***						***
;	***************************************************
;
_START_CNT_BANK2_MAK_CHK:
	SUB_START
	MOV.L	#_CPOS_BANK_USELFUL,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF START_CNT_BANK2_MAKCHK_END	;

	MOV.L	#_BANK1_CALC_ROT_NUM_ZR,R1	;
	MOV.L	@R1,R2				;
	ADD	#1,R2				;
	FAR_JSR	#_BANK2_CPOS_ABS_POS_SET,R0	;

;	--------- 2014-08-30 ΰ��ވʒu-----------
	FAR_JSR	#_HLDCAM_BANK2_ABS_POS_SET,R0	;ssa_dtmk.src 2014-08-30

START_CNT_BANK2_MAKCHK_END:
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	�H���؂�ւ�		***
;	***	�O�̋@�\�������ōs��	***
;	***				***
;	***********************************
;	Input R2
_BANK_CHK_NEXT_CYCL_STR1;
	SUB_START

	MOV.L	#_CPOS_BANK_USELFUL,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF BANKCHKNEXT_CYCL_STR1_020	;

	MOV.W	#1,R4				;
	MOV.L	#_SV_POS_CTL_STEP,R1		;
	MOV.W	R4,@R1				;W

	FAR_JSR	#_BANK2_TO_BANK1_MOV,R0		;
	MOV.L	#_BANK2_LINK_OBJROT_NUM_ZR,R1	;//NOW ROTATION �ԍ�
	MOV.L	@R1,R2				;
	PUSH_REG1 R2				;
	FAR_JSR	#_CPOS_ROT_NUM_SET,R1		;
	POP_REG1 R2				;
	ADD	#1,R2				;NEW-ROT
	FAR_JSR	#_BANK2_CPOS_ABS_POS_SET,R0	;

;	--------- 2014-08-30 ΰ��ވʒu-----------
	FAR_JSR	#_HLDCAM_BANK2_ABS_POS_SET,R0	;ssa_dtmk.src 2014-08-30

;--------2011-05-11----
	FAR_JSR	#_CNT_BEF_LOT_SIGCHK,R0		;���ٰ�� 2011-05-11

;--------2011-05-05----
;;	MOV.L	#_CNT_STOP_CMD_BEF1,R1		;//�������������̃��b�g�J�E���^�̂P��]�I�[�o��h��
;;	MOV.W	@R1,R0				;
;;	TST	R0,R0				;
;;	TST_BIT_OF BANKCHKNEXT_CYCL_STR1_010	;
;;	MOV.L	#_STOP_LATCH_B,R1		;//BIT0:�į�ߖt
;;	MOV.W	@R1,R0				;
;;	OR	#BIT0,R0			;
;;	MOV.W	R0,@R1				;
;;BANKCHKNEXT_CYCL_STR1_010:

	M_BRA	BANKCHKNEXT_CYCL_STR1_100	;

BANKCHKNEXT_CYCL_STR1_020:
	MOV.L	#_CPOS_CTL_MATH,R1		;
	MOV.W	@R1,R0				;
	TST	#_DMATH_CNTROT,R0		;��]?
	TST_BIT_OF BANKCHKNEXT_CYCL_STR1_050
	ADD	#1,R2				;��]��+1<���]>
BANKCHKNEXT_CYCL_STR1_050:

	MOV.W	#1,R4
	MOV.L	#_SV_POS_CTL_STEP,R1		;
	MOV.W	R4,@R1				;(1�����ł����̂�/���蒼���K�v������̂�)
	PUSH_REG1 R2
	FAR_JSR	#_CPOS_ROT_NUM_SET,R1		;Input R2 ��]
	POP_REG1 R2
	FAR_JSR	#_CPOS_ABS_POS_SET,R1		;Input R2 ��]

;	--------- 2014-08-30 ΰ��ވʒu-----------
	FAR_JSR	#_HLDCAM_ABS_POS_SET,R0		;2014-08-30

BANKCHKNEXT_CYCL_STR1_100:
;	=====2003-07-09 ���x============
	FAR_JSR	#_CPOS_SPD_DTMOV,R0		;
;	===== 2003-07-14 TIME ======
	FAR_JSR	#_CPOS_TIM_DTMOV,R0		;



	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	2011-05-11				***
;	***	���b�g�J�E���^UP��1��]�O�M��		***
;	***	�N�����_�ł��ꂪON�Ȃ炱�̉�]�Ŏ~�߂�	***
;	***						***
;	***************************************************
;
	.ALIGN	4				;
_CNT_BEF_LOT_SIGCHK:
	SUB_START

	MOV.L	#_CNT_STOP_CMD_BEF1,R1		;//�������������̃��b�g�J�E���^�̂P��]�I�[�o��h��
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF BANKCHKNEXT_CYCL_STR1_010	;
	MOV.L	#_STOP_LATCH_B,R1		;//BIT0:�į�ߖt
	MOV.W	@R1,R0				;
	OR	#BIT0,R0			;
	MOV.W	R0,@R1				;
BANKCHKNEXT_CYCL_STR1_010:

	SUB_END
	M_RTS

;	***************************************************
;	***	��~������^�C�v			***
;	***	��~���Ȃ��^�C�v�ł��P��]���ł͉\	***
;	***	BIT3=0 BIT2=1				***
;	***************************************************
	.ALIGN	4				;
_BANK_CNT_STOP_CHK_TYP1
	SUB_START

	MOV.L	#_CNT_STOP_CTRL_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON BANK_CNT_STOPCHK_TYP1_200	;��~���Z����

	FAR_JSR	#_POS_CNT_LAST_STEP_CHK,R0	;
	TST	R0,R0				;
	TST_BIT_OF BANK_CNT_STOPCHK_TYP1_200

	FAR_JSR	#_CNT_SUB_DATA_CALC,R0		;

	MOV.L	#_STOP_LATCH_B,R1		;//BIT0:�į�ߖt
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF BANK_CNT_STOPCHK_TYP1_200;

;	----- ��~�����ON -----
	FAR_JSR	#_CNT_STOP_CMD_DATA_SUB1,R0	;(�A��ALL-�ł͂��̏����͂Ȃ��F�����ɂ��������ɂ��Ȃ�)

	MEM1_BIT0_TO_BIT7_ORSET MEM=_STOP_LATCH,LG=W,BIT=BIT0,WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_CNT_STOP_CTRL_FLG,LG=W,BIT=BIT1,WKREG=R1	;



BANK_CNT_STOPCHK_TYP1_200

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	�ʏ�^�]��Ԃł̒�~����	***
;	***					***
;	*******************************************
_PROC_2MS_PLS	.EQU	2000	;2000pls 500KHZ=500pls

_CNT_GPOINT_STOP_TYP2:
	SUB_START
	MOV.L	#_STOP_LATCH_B,R1			;//BIT0:�į�ߖt
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF CNT_GPOINT_STOPTYP2_100		;

	FAR_JSR	#_CNT_SUB_DATA_CALC,R0			;����������

;;2007-03-02	TST	R0,R0					;
;;2007-03-02	TST_BIT_ON CNT_GPOINT_STOPTYP2_100		;���Z�s��JUMP

;	-------- 2007-03-02------
	FAR_JSR	#_CMP_CNT_CTLGENSOK,R0			;
	CMP/EQ	#-1,R0					;
	BT	CNT_GPOINT_STOPTYP2_100			;���Z�s��JUMP(ERR)

	TST	R0,R0					;
	TST_BIT_OF CNT_GPOINT_STOPTYP2_050		;�~�܂��

;	---- ����CPU�͂Ȃ�Ă����Ă����-----
	FAR_JSR	#_CPU_BA_CST_ON_JG,R0			;
	TST	R0,R0					;
	TST_BIT_OF CNT_GPOINT_STOPTYP2_100		;����͒�܂�Ƃ����Ă����Ȃ�JUMP

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CMP_RECOVER_FLG,LG=W,BIT=BIT1,WKREG=R1	;bit-set

CNT_GPOINT_STOPTYP2_050:
	MOV.L	#_CONT_STOP_END_SUBPLS,R4					;
	MOV.L	@R4,R2								;
	NEG	R2,R3								;

	POS_LSI_32BIT_DAT_SET ADR=_PLS_OutPposL,ADR_REG=R1,DAT_REG=R3		;

	FAR_JSR	#_CNT_STOP_CMD_DATA_SUB1,R0					;LINK_SV_OBJ_ABSPLS-ESUB
	FAR_JSR	#_CNT_STOP_CMD_DATA_SUB2,R0					;

;;;;	MEM1_BIT0_TO_BIT7_ORSET MEM=_STOP_LATCH,LG=W,BIT=BIT0,WKREG=R1		;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_CNT_STOP_CTRL_FLG,LG=W,BIT=BIT1,WKREG=R1	;

;	----- 2007-03-02---
	FAR_JSR	#_STOP_LTH_OUT,R0


CNT_GPOINT_STOPTYP2_100:
	SUB_END
	M_RTS


;;_CNT_GPOINT_STOP_TYP2:
;;	SUB_START
;;	MOV.L	#_STOP_LATCH_B,R1		;//BIT0:�į�ߖt
;;	MOV.W	@R1,R0				;
;	TST	#BIT0,R0			;
;;	TST_BIT_OF CNT_GPOINT_STOPTYP2_100	;
;;
;;	FAR_JSR	#_CNT_SUB_DATA_CALC,R0		;����������
;;
;;	MOV.L	#_CONT_STOP_END_SUBPLS,R4	;
;;	MOV.L	@R4,R2				;
;;	NEG	R2,R3				;
;;
;;	MOV.W	#_PROC_2MS_PLS,R4		;
;;	ADD	R4,R2				;
;;	FAR_JSR	#_LOAD_GPOINT_PLS,R0		;2004-12-19
;;	MOV	R0,R6				;R/W �����_=R6
;;	ADD	R6,R2				;
;;
;;	FAR_JSR	#_LOAD_REST_PLS,R0				;ANS R0
;;	SUBPLS+GPOSINT+1000PLS ���c����ٽ 			;
;;	CMP/GE	R2,R0						;
;;	BF	CNT_GPOINT_STOPTYP2_100				;���Z�s��JUMP
;;
;;	POS_LSI_32BIT_DAT_SET ADR=_PLS_OutPposL,ADR_REG=R1,DAT_REG=R3		;
;;
;;	FAR_JSR	#_CNT_STOP_CMD_DATA_SUB1,R0					;
;;	FAR_JSR	#_CNT_STOP_CMD_DATA_SUB2,R0					;
;;
;;	MEM1_BIT0_TO_BIT7_ORSET MEM=_STOP_LATCH,LG=W,BIT=BIT0,WKREG=R1		;
;;	MEM1_BIT0_TO_BIT7_ORSET MEM=_CNT_STOP_CTRL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
;;
;;
;;CNT_GPOINT_STOPTYP2_100:
;;
;;
;;	SUB_END
;;	M_RTS

;	***************************
;	***	��~���Z	***
;	***************************
;	CASE1:���S�A��	--->	�~�܂��ʒu�F�c��p���X���P��](SV_OBJ_-�ŏI)�{���̌����_
;	CASE2:��ϗL��	--->	�ŏI�H�������̓���J�n������ٽ�𑫂��Ȃ�(���Z��������)
;				���쒆�ŏI�H�������Ƀp���X�����炷(SV-OBJ-�ŏI)
;(�N����)
_CNT_SUB_DATA_CALC:
	SUB_START

	MOV.L	#_CPOS_STEP_MAX,R1				;
	MOV.W	@R1,R0						;+1����-1�����v�Z
	MOV.L	#_CPOS_SDAT1_STPAPOS,R4					;
	SHLL2	R0							;
	SHLL	R0							;
	ADD	R0,R4							;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;�ڕW�ʒu(SV_OBJ_ABSPLS)

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R1							;
	MOV.L	@R4,R2							;
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1				;
	BT	CNT_SUB_DATACALC_100		;
	XOR	R1,R1				;
	XOR	R2,R2				;ERR(-)

CNT_SUB_DATACALC_100:
	TST	R1,R1				;
	TST_BIT_ON CNT_SUB_DATACALC_120		;ERR(over)

	MOV.L	#H'3FFFFFF,R1			;(�{����PLS*2+)
	CMP/HS	R2,R1				;
	BT	CNT_SUB_DATACALC_150		;����
CNT_SUB_DATACALC_120:
	XOR	R1,R1				;
	XOR	R2,R2				;ERR(over)

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CNT_BANK_CALC_ERR,LG=W,BIT=BIT0,WKREG=R1	;

CNT_SUB_DATACALC_150:
	MOV.L	#_CONT_STOP_END_SUBPLS,R4	;
	MOV.L	R2,@R4				;

;	(�ڕW)-R2(�ҋ@�_)
	SUB_END
	M_RTS











;	***********************************
;	***	�f�[�^�̌��Z1		***
;	***********************************
;	�����͂��̏�Ō���
_CNT_STOP_CMD_DATA_SUB1:
	SUB_START

	MOV.L	#_CONT_STOP_END_SUBPLS,R4				;
	MOV.L	@R4,R6							;
	XOR	R5,R5							;

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4					;
	MOV.L	@R4,R1							;
	MOV.L	@(4,R4),R2						;
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;
	MOV.L	#_LINKX_SV_OBJ_ABSPLS,R4				;
	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;

	MOV.L	#_LNGTH_ADD_DATA,R4					;//�����t��
	MOV.L	@R4,R1							;
	MOV.L	@(4,R4),R2						;
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1
	BT	CNT_STOP_CMD_DATSUB1_100				;
	XOR	R1,R1							;
	XOR	R2,R2							;
CNT_STOP_CMD_DATSUB1_100:						;

	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;

	MOV.L	#_LT_LNGTH_ADD_DATA,R4					;//�����t��
	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;


	SUB_END
	M_RTS


_CNT_STOP_CMD_DATA_SUB2:
	SUB_START
	MOV.L	#_CONT_STOP_END_SUBPLS,R4				;
	MOV.L	@R4,R6							;
	XOR	R5,R5							;

	MOV.L	#_LNGTH_TOTAL_OUTPLS,R4					;
	MOV.L	@R4,R1							;
	MOV.L	@(4,R4),R2						;
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1							;
	BT	CNT_STOP_CMD_DATSUB2_100				;
	XOR	R1,R1
	XOR	R2,R2
CNT_STOP_CMD_DATSUB2_100:
	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;

	MOV.L	#_LT_LNGTH_TOTAL_OUTPLS,R4				;
	MOV.L	R1,@R4							;
	MOV.L	R2,@(4,R4)						;

	SUB_END
	M_RTS

