;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		�ᑬ�D��@������������		***
;	***		2015-11-17 �����I��		***
;	***						***
;	***						***
;	***						***
;	***************************************************

;	*******************************************
;	***					***
;	***	�o�b�N�O�����h��CALL		***
;	***	�����쐬			***
;	***					***
;	*******************************************
;;;;;;;;;2016-04-18	.IMPORT		_PAR_ACCDN_MATH		;5 2015-11-18 �������@�����D��[CE2]

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
	TST	#_DMATH_CNTROT,R0			;��]�F
	TST_BIT_OF ACCLW_USECHK_100			;no use

	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1SGL+_W1CNT+_W1OPT+_W1INC,R0		;���S�A�A���A�I�v�V����,INC
	TST_BIT_OF ACCLW_USECHK_100			;no use


	MOV.L	#_LINK_1ROT_PLS,R1			;
	MOV.L	@R1,R4					;
	MOV.L	#_ACCLW_GEN_MAX_LNG,R1			;�ő呬�x���̌�������
	MOV.L	R4,@R1					;(�Ƃ肠����360�x��)


	MOV.B	#BIT0,R2				;

ACCLW_USECHK_100
	MOV.L	#_ACCLW_USE_CONF,R1			;
	MOV.W	R2,@R1					;

;;;;;;;;;ACCLW_USECHK_EXT

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�N����CALL(�^�]�tON,�^�C�}��,1�T�C�N��)	***
;	***						***
;	***************************************************
_API_ACCLW_DRV_START1
	SUB_START


	FAR_JSR	#_API_ACCLW_DRV_START2,R0	;
	FAR_JSR	#_API_ACCLW_DRV_WORK_CLR,R0	;�f�o�b�N�p

	SUB_END
	M_RTS

;	----------- ���ޯ��p�ɸر------------
_API_ACCLW_DRV_WORK_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCLW_GET_STEP_NO,R1		;//BIT1=1���̑Ώۍs��
	MOV.W	R0,@R1				;
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;//BIT1=1���̑Ώۑ��x
	MOV.L	R0,@R1				;�ر�s�v:���ޯ��p
	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;//�o�͑��x
	MOV.L	R0,@R1				;�ر�s�v:���ޯ��p
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�N����CALL(��������,���̌������Z)	***
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
;	***	�ʒu���ߒ��f��CALL		***
;	***	�ʒu���ߒ�~�^�C�}��CALL	***
;	***	�ُ펞CALL			***
;	***					***
;	*******************************************
;//BIT0:�N��[API]
;//BIT6:[�����J�n]
;//BIT7:���Z����[��~�s���܂ŉ��Z�s�v�F�����ᑬ�ݒ肪�Ȃ�]:�\��
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
;	***	1msec��CALL	���C��		***
;	***					***
;	*******************************************
;	2015-11-17 �����I��
;	[�I�[�o���C�h�O��CALL]
;	Input  R2:�ݒ葬�x
;	Output R2:�ݒ葬�x����
;	PAR_ACCDN_MATH=1 �����D�扉�Z
;
_ACCLW_CTRL_CALC			;2015-11-17 �����I��
	SUB_START

	MOV.L	#_ACCLW_SET_SPD,R1				;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	R2,@R1						;

	MOV.W	#D'1000,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_ACCLW_REAL_SPD1MS,R1				;1ms����
	MOV.L	R2,@R1						;


	MOV.L	#_ACCLW_CALC_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_ON ACCLW_CTRLCALC_100	;[�N����]
	M_BRA	ACCLW_CTRLCALC_800

ACCLW_CTRLCALC_100
	TST	#BIT7,R0		;
	TST_BIT_OF ACCLW_CTRLCALC_120	;
	M_BRA	ACCLW_CTRLCALC_800	;���Z�s�v:�ċN��������܂ŉ��Z���Ȃ��Ă���

ACCLW_CTRLCALC_120
	TST	#BIT6,R0		;
	TST_BIT_ON ACCLW_CTRLCALC_200	;[��������? YES]


;	------- �����J�n�����`�F�b�N---------

	FAR_JSR	#_ACCLW_GEN_START_CONF_CHECK,R0

	MOV.L	#_ACCLW_CALC_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_ON ACCLW_CTRLCALC_300		;
	M_BRA	ACCLW_CTRLCALC_800		;



;	------------- ������-----------
ACCLW_CTRLCALC_200
;	------- �����I�������`�F�b�N---------
	FAR_JSR	#_ACCLW_GEN_END_CONF_CHECK,R0
	TST	R0,R0				;
	TST_BIT_ON ACCLW_CTRLCALC_300		;������

	FAR_JSR	#_API_ACCLW_DRV_START2,R0	;��������:����T��
	M_BRA	ACCLW_CTRLCALC_800		;

ACCLW_CTRLCALC_300
	FAR_JSR	#_ACCLW_GEN_OUTSPD_CALC,R0	;
	M_BRA	ACCLW_CTRLCALC_900				;


ACCLW_CTRLCALC_800				;
	MOV.L	#_ACCLW_SET_SPD,R1		;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	@R1,R2				;
	M_BRA	ACCLW_CTRLCALC_EXT		;

ACCLW_CTRLCALC_900				;
	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;	//�o�͑��x
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
;	***	�����I������			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:�����I�� 1:������
;	INPUT:R2(�ݒ葬�x:��������)
_ACCLW_GEN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCLW_SET_SPD,R1		;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;//BIT1=1���̑Ώۑ��x
	MOV.L	@R1,R3				;
	CMP/GE	R2,R3				;R2��R3(R2=R3)
	BT	ACCLW_GEN_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;�܂������p��
	M_BRA	ACCLW_GEN_END_CONFCHK_300	;

ACCLW_GEN_END_CONFCHK_100
	XOR	R0,R0
ACCLW_GEN_END_CONFCHK_300

	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	�o�͉��Z			***
;	***	�ʏ�̌������Z���g�p����̂�	***
;	***	���̂Ƃ��뉉�Z�s�v		***
;	***					***
;	*******************************************
;	�o�͑��x���Z
_ACCLW_GEN_OUTSPD_CALC
	SUB_START
	MOV.L	#_ACCLW_GET_SET_SPD,R1		;
	MOV.L	@R1,R3				;

	MOV.L	#_ACCLW_OUT_SET_SPD,R1		;�o�͑��x
	MOV.L	R3,@R1				;

	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***	����p�Ɍ��ݑ��x�E���݉����x�̎Z�o	***
;	***	[�I�[�o���C�h��ŉ��Z����]		***
;	***						***
;	***************************************************
;	*******************************************
;	***					***
;	***	���݂̍s�����猸���s����T��	***
;	***					***
;	*******************************************
;	S4b	CPOS_SDAT1_CNTSTEP[100+10];		//SETX-->�N����COPY
;	S4b	CPOS_SDAT1_INF1[100+10];		//SETX-->�N����COPY
;	S4b	CPOS_SDAT1_CHGAPOS[2*(100+10)];		//�N����,���̑��ŉ��Z 8byte data
;	S4b	CPOS_SDAT1_STPAPOS[2*(100+10)];		//�N����,���̑��ŉ��Z 8byte data
;

_ACCLW_GEN_START_CONF_CHECK
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//��������H��1~11
	MOV.W	@R1,R0				;

	TST	R0,R0				;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_050	;
	M_BRA	ACCLW_GEN_START_CONFCHK_EXT	;

ACCLW_GEN_START_CONFCHK_050
	MOV.L	#_CPOS_STEP_MAX,R1		;
	MOV.W	@R1,R5				;
	ADD	#1,R5				;[MAX:R5]
	CMP/GE	R5,R0				;�ŏI�s��
	BF	ACCLW_GEN_START_CONFCHK_100	;
	M_BRA	ACCLW_GEN_START_CONFCHK_EXT	;R5=R0�ŏI�s��

;	---------------------------------------
ACCLW_GEN_START_CONFCHK_100
	MOV	R0,R8				;�s��

	SUB	R0,R5				;1~98
	MOV.W	#D'10,R4			;��ǂ�10�i�܂�[100�i�͂��킢����]
	CMP/GE	R5,R4				;R5��R4
	BT	ACCLW_GEN_START_CONFCHK_120	;
	MOV	R4,R5				;
ACCLW_GEN_START_CONFCHK_120
;	����̍s���`�ő�P�O�i�̒���
;	��~�s���܂��͖߂�s���I���܂Ō������s��.
;
;	�s��1�̏ꍇ
;	INF1:�s��1���Q��
;	CHG :�s��1���Q��
;	���x:�s��2���Q��

	ADD	#-1,R0				;
	SHLL2	R0				;*4
	MOV.L	#_CPOS_SDAT1_SPD,R13		;4B
	ADD	R0,R13				;
	ADD	#4,R13				;���x�͎��̒i�̑��x

	MOV.L	#_CPOS_SDAT1_INF1,R14		;4B
	ADD	R0,R14				;

	SHLL	R0
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R12	;�ؑֈʒu8B
	ADD	R0,R12				;


ACCLW_GEN_START_CONFCHK_200LOP:			;
	PUSH_REG1 R5

	MOV.L	@R14,R0				;INF
	TST	#BIT0,R0			;�A����?
	TST_BIT_OF ACCLW_GEN_START_CONFCHK_550	;���̍s���͒�~�Ȃ̂ŏI��

;	(------- �������ʂ͕s�vR0.BIT1--------)
;	--------- �A��-----------
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;ر���іڕW�ʒu
	MOV.L	@(0,R12),R1						;
	MOV.L	@(4,R12),R2						;�ݒ�ʒu
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2-R5,R6

	CMP/PZ	R1				;
	BT	ACCLW_GEN_START_CONFCHK_250	;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R0	;|R1,R2|
ACCLW_GEN_START_CONFCHK_250:			;


	TST	R1,R1					;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_550		;�܂��������\���ɂ���

	MOV.L	#_ACCLW_REAL_SPD1MS,R5			;
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
	CMP/PL	R2	
	BT	ACCLW_GEN_START_CONFCHK_280		;
	MOV.W	#1,R2					;
ACCLW_GEN_START_CONFCHK_280:				;

	MOV.L	#_ACCLW_GEN_MAX_LNG,R5			;�ő呬�x���̌�������
	MOV.L	@R5,R4					;
	CMP/HI	R4,R2					;R4<R2
	BT	ACCLW_GEN_START_CONFCHK_550		;�܂��������\���ɂ���

;[���x�������ꍇ�]������߂�]

;	���ݑ��x^2���Q��(S�|���ݑ��x/1000)+�w��i�����x^2
	PUSH_REG1 R8	;�s��
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
	MOV.L	@R4,R11							;����ײ�ތ�
									;Input R1,R2 ����
									;Input R9    ���ݑ��x
									;Input R10   �̾�đ��x[�w��i�����x]
									;Input R11   ��������

	XOR	R0,R0
	CMP/GE	R9,R10					;R9(���ݑ��x)��R10(�ݒ葬�x)
	BT	ACCLW_GEN_START_CONFCHK_400		;

	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0		;

ACCLW_GEN_START_CONFCHK_400:			;


	POP_REG1 R14
	POP_REG1 R13
	POP_REG1 R12
	POP_REG1 R8

	TST	R0,R0
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_500				;�������ׂ�
	M_BRA	ACCLW_GEN_START_CONFCHK_580				;


;	---------------- �����J�n����[�����X�^�[�g����]�A���Z�͂�߂�-----------
ACCLW_GEN_START_CONFCHK_500:					;
	MOV.L	@R13,R2						;NEW SPEED
	MOV.L	#_ACCLW_GET_SET_SPD,R1				;
	MOV.L	R2,@R1						;
	MOV.L	#_ACCLW_GET_STEP_NO,R1				;//BIT1=1���̑Ώۍs��
	MOV.W	R8,@R1						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCLW_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1	;[�������邩�牉�Z�͂�߂�R0=BIT0]


;	---------------- ��~�s���Ȃ̂ł�߂�----------------
ACCLW_GEN_START_CONFCHK_550:			;
	MOV.B	#BIT0,R0			;
	M_BRA	ACCLW_GEN_START_CONFCHK_600	;

;	--------------- �������Z����-------------------------
ACCLW_GEN_START_CONFCHK_580:			;
	XOR	R0,R0				;
ACCLW_GEN_START_CONFCHK_600:			;

	POP_REG1 R5
	ADD	#-1,R5				;
	TST	R5,R5				;
	TST_BIT_OF ACCLW_GEN_START_CONFCHK_EXT	;
	TST	R0,R0				;
	TST_BIT_ON ACCLW_GEN_START_CONFCHK_EXT	;�I���
	ADD	#4,R13				;SPD
	ADD	#4,R14				;INF
	ADD	#8,R12				;POS
	ADD	#1,R8				;�s��[�s�v����]
	M_BRA	ACCLW_GEN_START_CONFCHK_200LOP	;



ACCLW_GEN_START_CONFCHK_EXT
	SUB_END
	M_RTS