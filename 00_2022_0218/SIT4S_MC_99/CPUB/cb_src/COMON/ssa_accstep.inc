;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		�e�i�O/��ϑ��w�菈��		***
;	***		2016-04-18 �O�E��I��		***
;	***		(�����ł������ł�)		***
;	***						***
;	***						***
;	***************************************************

;	*******************************************
;	***					***
;	***	�o�b�N�O�����h��CALL		***
;	***	�����쐬			***
;	***					***
;	*******************************************

_ACCST_DATA_MAIN
	SUB_START


	XOR	R2,R2
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;��]�F
	TST_BIT_OF ACCST_USECHK_100			;no use

	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#_W1SGL+_W1CNT+_W1OPT+_W1INC,R0		;���S�A�A���A�I�v�V����,INC
	TST_BIT_OF ACCST_USECHK_100			;no use

	MOV.L	#_LINK_1ROT_PLS,R1			;
	MOV.L	@R1,R4					;
	MOV.L	#_ACCST_GEN_MAX_LNG,R1			;�ő呬�x���̌�������
	MOV.L	R4,@R1					;(�Ƃ肠����360�x��)

	MOV.B	#BIT0,R2				;

ACCST_USECHK_100
	MOV.L	#_ACCST_USE_CONF,R1			;
	MOV.W	R2,@R1					;



	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�N����CALL(�^�]�tON,�^�C�}��,1�T�C�N��)	***
;	***						***
;	***************************************************
_API_ACCST_DRV_START1
	SUB_START


	FAR_JSR	#_API_ACCST_DRV_START2,R0	;
	FAR_JSR	#_API_ACCST_DRV_WORK_CLR,R0	;�f�o�b�N�p

	SUB_END
	M_RTS

;	----------- ���ޯ��p�ɸر------------
_API_ACCST_DRV_WORK_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCST_GET_SET_SPD,R1		;//BIT1=1���̑Ώۑ��x
	MOV.L	R0,@R1				;�ر�s�v:���ޯ��p
	MOV.L	#_ACCST_OUT_SET_SPD,R1		;//�o�͑��x
	MOV.L	R0,@R1				;�ر�s�v:���ޯ��p
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�N����CALL(��������,���̌������Z)	***
;	***						***
;	***************************************************
_API_ACCST_DRV_START2
	SUB_START

	MOV.L	#_ACCST_USE_CONF,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF API_ACCST_DRVSTR2_EXT		;

	MOV.B	#BIT0,R0				;
	MOV.L	#_ACCST_CALC_FLG,R1			;
	MOV.W	R0,@R1					;[BIT6,BIT7CLR BIT0=1]


API_ACCST_DRVSTR2_EXT

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

_API_ACCST_DRV_STOP
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACCST_CALC_FLG,R1		;
	MOV.W	R0,@R1				;

;	---------�s���ԍ�-------
	XOR	R0,R0					;
	MOV.L	#_ACCST_GET_STEP_NO,R1			;//BIT1=1���̑Ώۍs��
	MOV.W	R0,@R1					;

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
_ACCST_CTRL_CALC			;2015-11-17 �����I��
	SUB_START

	MOV.L	#_ACCST_SET_SPD,R1				;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	R2,@R1						;

	MOV.W	#D'1000,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2/R4 
	MOV.L	#_ACCST_REAL_SPD1MS,R1				;1ms����
	MOV.L	R2,@R1						;

	MOV.L	#_ACCST_CALC_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_ON ACCST_CTRLCALC_100	;[�N����]
	M_BRA	ACCST_CTRLCALC_800

ACCST_CTRLCALC_100
;	---------- �s���ύX�`�F�b�N----------------------------------
;	[�s���ύX�������=ACCST_CALC_FLG=BIT0(BIT6,BIT7��ر����)]	;
	MOV.L	#_INT_POS_CTL_STEP,R1					;//��������H��1~11
	MOV.W	@R1,R3							;
	TST	R3,R3							;
	TST_BIT_OF ACCST_CTRLCALC_800					;���肦�Ȃ�(CALC_FLG=0)

	FAR_JSR	#_ACCST_CHGSTEP_GET_MAKE,R0				;(��~,�ŏI�s���ł͂��Ȃ�.ACCST_ACC_MATH_SEL=0)

;	-------------------------------------------------------------
	MOV.L	#_ACCST_ACC_MATH_SEL,R1					;//1STEP��
	MOV.W	@R1,R0							;
	TST	#BIT0,R0						;
	TST_BIT_OF ACCST_CTRLCALC_800					;(�����,�����̏ꍇ�͉������Ȃ�)

	MOV.L	#_ACCST_CALC_FLG,R1					;
	MOV.W	@R1,R0						;
	TST	#BIT7,R0					;
	TST_BIT_ON ACCST_CTRLCALC_800				;���Z�s�v:�s���ύX���ς��܂ŉ��Z���Ȃ��Ă���

	TST	#BIT6,R0		;
	TST_BIT_ON ACCST_CTRLCALC_200	;[����or�������� YES]

;	------- ����/�����J�n�����`�F�b�N---------
	FAR_JSR	#_ACCST_UPDN_START_CONF_CHECK,R0		;���̍s����������΂���.ACCST_ACC_MATH_SEL.BIT1=0/1(��������)

	MOV.L	#_ACCST_CALC_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT6,R0				;
	TST_BIT_OF ACCST_CTRLCALC_800			;���Z�s�v

;	------------- ������-----------
ACCST_CTRLCALC_200

;	------- �����E�����I�������`�F�b�N---------
	FAR_JSR	#_ACCST_UPDN_END_CONF_CHECK,R0
	TST	R0,R0								;
	TST_BIT_ON ACCST_CTRLCALC_300						;����/�������Z�p��
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT7,WKREG=R1	;
	M_BRA	ACCST_CTRLCALC_800						;���Z�I��:

ACCST_CTRLCALC_300
	FAR_JSR	#_ACCST_UPDN_OUTSPD_CALC,R0	;
	M_BRA	ACCST_CTRLCALC_900		;

;	----------- R2��ݒ�l�ɖ߂�----------------
ACCST_CTRLCALC_800				;
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	@R1,R2				;
	M_BRA	ACCST_CTRLCALC_EXT		;

;	---------  ���Z���Ȃ̂ŉ��Z���ʂ��o�͂���---------
ACCST_CTRLCALC_900				;
	MOV.L	#_ACCST_OUT_SET_SPD,R1		;	//�o�͑��x
	MOV.L	@R1,R2				;

ACCST_CTRLCALC_EXT				;

	MOV.L	#_ACCST_ACC_MATH_SEL,R1		;//1STEP��
	MOV.W	@R1,R0				;
	AND	#BIT1+BIT0,R0			;
	SHLL8	R0				;
	MOV	R0,R4
	MOV.L	#_ACCST_CALC_FLG,R1		;
	MOV.W	@R1,R0				;BIT0,BIT6,BIT7
	AND	#BIT0+BIT6+BIT7,R0		;
	OR	R4,R0				;BIT0,BIT6,BIT7,BIT8,BIT9
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB255,R1	;255
	MOV.W	R0,@R1				;

;	------- output [R2] --------------

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***	�����܂��͌����I������		***
;	***					***
;	***					***
;	*******************************************
;	�O�ϑ��ł̂ݎ��s
;	OUTPUT R0 	R0=0:����,�����I��
;			R0=1:������,������
;
_ACCST_UPDN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_ACC_MATH_SEL,R1		;//1STEP��
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON ACCST_UPDN_END_CONFCHK_100	;BIT1=1����

	FAR_JSR	#_ACCST_UP_END_CONF_CHECK,R0	;
	M_BRA	ACCST_UPDN_END_CONFCHK_200	;

ACCST_UPDN_END_CONFCHK_100
	FAR_JSR	#_ACCST_DN_END_CONF_CHECK,R0	;
ACCST_UPDN_END_CONFCHK_200
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	�����I������			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:�����I�� 1:������
;	INPUT:R2(�ݒ葬�x:��������)
_ACCST_DN_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCST_GET_SET_SPD,R1		;�Ώۂ̐ݒ葬�x
	MOV.L	@R1,R3				;
	CMP/GE	R2,R3				;R2(Ӱ��݉��Z�����Z����)��R3(�ݒ�)(R2=R3)
	BT	ACCST_DN_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;�܂������p��
	M_BRA	ACCST_DN_END_CONFCHK_300	;

ACCST_DN_END_CONFCHK_100
	XOR	R0,R0
ACCST_DN_END_CONFCHK_300

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	�����I������			***
;	***					***
;	*******************************************
;	OUTPUT R0:0:�����I�� 1:������
;	INPUT:R2(�ݒ葬�x:��������)
_ACCST_UP_END_CONF_CHECK
	SUB_START
	MOV.L	#_ACCST_SET_SPD,R1		;//INPUT ���[�V�������Z������̑��x (�I�[�o���C�h�O)
	MOV.L	@R1,R2				;
	MOV.L	#_ACCST_GET_SET_SPD,R1		;�Ώۂ̐ݒ葬�x
	MOV.L	@R1,R3				;
	CMP/GE	R3,R2				;R3(�Ώۂ̐ݒ葬�x)��R2(���[�V�������Z���̑��x)(R2=R3)
	BT	ACCST_UP_END_CONFCHK_100	;
	MOV.B	#BIT0,R0			;�܂������p��
	M_BRA	ACCST_UP_END_CONFCHK_300	;

ACCST_UP_END_CONFCHK_100
	XOR	R0,R0
ACCST_UP_END_CONFCHK_300

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	�s���ؑ֎�			***
;	***					***
;	*******************************************
;	INPUT R3: INT_POS_CTL_STEP 0�ȊO
;	(��~,�ŏI�s���ł͂��Ȃ�.ACCST_ACC_MATH_SEL=0)
;
_ACCST_CHGSTEP_GET_MAKE
	SUB_START

	MOV.L	#_ACCST_GET_STEP_NO,R5			;//BIT1=1���̑Ώۍs��
	MOV.W	@R5,R0					;
	MOV.W	R3,@R5					;
	CMP/EQ	R3,R0					;
	BT	ACCST_CHGSTEP_GETINF_EXT		;����

	PUSH_REG1 R3
	FAR_JSR	#_API_ACCST_DRV_START2,R0		;
	POP_REG1 R3
	
;	---------------------------------------------
	XOR	R6,R6
	MOV.L	#_CPOS_STEP_MAX,R1			;
	MOV.W	@R1,R0					;
	ADD	#1,R0					;[MAX:R0]
	CMP/GE	R0,R3					;�ŏI�s��
	BT	ACCST_CHGSTEP_GETINF_SET		;�ŏI�s���͌Œ�

	MOV.L	#_CPOS_SDAT1_INF1,R14			;4B
	MOV	R3,R4					;
	ADD	#-1,R4					;
	SHLL2	R4					;
	ADD	R4,R14					;
	MOV.L	@R14,R0					;
	TST	#BIT0,R0				;�A����?
	TST_BIT_OF ACCST_CHGSTEP_GETINF_SET		;���Z���Ȃ�

;	-----------------------------------------------
	MOV.L	#_SET1_MOT_INF,R5			;
	MOV	R3,R4
	ADD	#-1,R4					;
	SHLL	R4					;
	ADD	R4,R5					;
	MOV.W	@R5,R0					;
	TST	#BIT1,R0				;
	TST_BIT_ON ACCST_CHGSTEP_GETINF_100		;BIT1=1[��ϑ�]:�ʏ�\�t�g(R6=0)
	MOV.B	#BIT0,R6				;BIT1=0[�O�ϑ�]:�s���֑ؑO�ϑ�
ACCST_CHGSTEP_GETINF_100				;
;	---------------------------------------------------

ACCST_CHGSTEP_GETINF_SET
	MOV.L	#_ACCST_ACC_MATH_SEL,R1			;//1STEP��
	MOV.W	R6,@R1					;�w�肳��Ă���s���̏I�����̒��o
							;BIT0:SET,BIT1=CLR()
ACCST_CHGSTEP_GETINF_EXT

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
_ACCST_UPDN_OUTSPD_CALC
	SUB_START
	MOV.L	#_ACCST_GET_SET_SPD,R1		;�Ώۂ̐ݒ葬�x
	MOV.L	@R1,R3				;

	MOV.L	#_ACCST_OUT_SET_SPD,R1		;�o�͑��x
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

_ACCST_UPDN_START_CONF_CHECK
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//��������H��1~11
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_050	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT	;

ACCST_UPDN_START_CONFCHK_050
	MOV.L	#_CPOS_STEP_MAX,R1		;
	MOV.W	@R1,R5				;
	ADD	#1,R5				;[MAX:R5]
	CMP/GE	R5,R0				;�ŏI�s��
	BF	ACCST_UPDN_START_CONFCHK_100	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT	;R5=R0�ŏI�s��

;	---------------------------------------
ACCST_UPDN_START_CONFCHK_100
	MOV	R0,R8				;�s��

;	�s��1�̏ꍇ
;	INF1:�s��1���Q��
;	CHG :�s��1���Q��
;	���x:�s��2���Q��

	ADD	#-1,R0				;
	SHLL2	R0				;*4
	MOV.L	#_CPOS_SDAT1_SPD,R13		;4B
	ADD	R0,R13				;
	MOV.L	@R13,R7				;���i�̐ݒ葬�x
	ADD	#4,R13				;���i�̐ݒ葬�x(�]���ΏۖڕW���x)

	MOV.L	#_CPOS_SDAT1_INF1,R14		;4B
	ADD	R0,R14				;

	SHLL	R0
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R12	;�ؑֈʒu8B
	ADD	R0,R12				;



	MOV.L	@R14,R0				;INF
	TST	#BIT0,R0			;�A����?
	TST_BIT_OF ACCST_UPDN_START_CONFCHK_550	;���̍s���͒�~�Ȃ̂ŏI��

;	(------- �������ʂ͕s�vR0.BIT1--------)
;	--------- �A��-----------
	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;ر���іڕW�ʒu
	MOV.L	@(0,R12),R1						;
	MOV.L	@(4,R12),R2						;�ݒ�ʒu
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2-R5,R6

	CMP/PZ	R1				;
	BT	ACCST_UPDN_START_CONFCHK_250	;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R0	;|R1,R2|=�ݒ�-���ݖڕW�ʒu
ACCST_UPDN_START_CONFCHK_250:			;


	TST	R1,R1					;
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_580		;�܂��������\���ɂ���

	MOV.L	#_ACCST_REAL_SPD1MS,R5			;
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
	CMP/PL	R2	
	BT	ACCST_UPDN_START_CONFCHK_280		;
	MOV.W	#1,R2					;
ACCST_UPDN_START_CONFCHK_280:				;R2:�c�苗��

	MOV.L	#_ACCST_GEN_MAX_LNG,R5			;�ő呬�x���̌�������(100->0 0->100%�ɕK�v�ȋ���)
	MOV.L	@R5,R4					;
	CMP/HI	R4,R2					;R4<R2
	BT	ACCST_UPDN_START_CONFCHK_580		;�܂��������\���ɂ���

	MOV.L	@R13,R0					;���̒i
	CMP/EQ	R0,R7					;���s�̒i
	BT	ACCST_UPDN_START_CONFCHK_540		;

	CMP/GE	R7,R0					;
	BT	ACCST_UPDN_START_CONFCHK_300		;����

;	-------------- ���� -------------
;INPUT R13:�^�[�Q�b�g�ݒ� R1,R2:����
	FAR_JSR	#_ACCST_DN_START_CONF_CHECK,R0
	TST	R0,R0
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_500				;�������ׂ�
	M_BRA	ACCST_UPDN_START_CONFCHK_580				;�܂������͕s�v

ACCST_UPDN_START_CONFCHK_300:							;
;	-------------- ���� ---------------
	FAR_JSR	#_ACCST_UP_START_CONF_CHECK,R0
	TST	R0,R0
	TST_BIT_ON ACCST_UPDN_START_CONFCHK_520				;�������ׂ�
	M_BRA	ACCST_UPDN_START_CONFCHK_580				;�܂������͕s�v



;	---------------- �����J�n����[�����X�^�[�g����]�A���Z�͂�߂�-----------
ACCST_UPDN_START_CONFCHK_500:								;
	MOV.L	@R13,R2									;�ݒ葬�xNEW SPEED
	MOV.L	#_ACCST_GET_SET_SPD,R1							;
	MOV.L	R2,@R1									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1		;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_ACC_MATH_SEL,LG=W,BIT=BIT1,WKREG=R1		;<<<<<<<<���� ����͏�ŕ]��>>>>>>>
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT						;


;	---------------- �����J�n����[�����X�^�[�g����]�A���Z�͂�߂�-----------
ACCST_UPDN_START_CONFCHK_520:								;
	MOV.L	@R13,R2									;�ݒ葬�xNEW SPEED
	MOV.L	#_ACCST_GET_SET_SPD,R1							;
	MOV.L	R2,@R1									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACCST_CALC_FLG,LG=W,BIT=BIT6,WKREG=R1		;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_ACCST_ACC_MATH_SEL,LG=W,BIT=~BIT1,WKREG=R1	;
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT						;

;	---------------- ��~�s���Ȃ̂ł�߂�----------------
ACCST_UPDN_START_CONFCHK_540:			;
	NOP					;�����͂͂����ׂ�
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT
ACCST_UPDN_START_CONFCHK_550:			;
	NOP					;�����͂͂����Ă���̂ł��Ȃ�
	M_BRA	ACCST_UPDN_START_CONFCHK_EXT
;	----------�܂����̔���̈ʒu�ɂȂ�------------
ACCST_UPDN_START_CONFCHK_580:			;
ACCST_UPDN_START_CONFCHK_EXT
	SUB_END
	M_RTS







;	***********************************************************
;	***							***
;	***	�������ׂ��ݒ�Ō������ׂ��͈͓���R0 !=0	***
;	***							***
;	***********************************************************
;	ANS R0!=0 �������ׂ��ʒu
_ACCST_DN_START_CONF_CHECK
	SUB_START

;[���x�������ꍇ�]������߂�]
;	���ݑ��x^2���Q��(S�|���ݑ��x/1000)+�w��i�����x^2

;;�s�v	PUSH_REG1 R8	;�s��
;;�s�v	PUSH_REG1 R12	;POS
;;�s�v	PUSH_REG1 R13	;SPD
;;�s�v	PUSH_REG1 R14	;INF1
	MOV.L	#_POSCTL_RL_SPD,R4					;
	MOV.L	@R4,R9							;

	MOV.L	@R13,R10						;SPD�F���i�ݒ�
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
	CMP/GE	R9,R10							;R9(���ݑ��x)��R10(�ݒ葬�x):�s�v
	BT	ACCST_DN_START_CONFCHK_400				;

;	***	Input R1,R2(�c�苗��)		***
;	***	Input R9:SPEED  DATA		***
;	***	Input R10:OFFSET SPEED		***
;	***	Input R11:ACC_LATE		***
	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0				;ANS R0!=0 ����

ACCST_DN_START_CONFCHK_400:						;


;;�s�v	POP_REG1 R14
;;�s�v	POP_REG1 R13
;;�s�v	POP_REG1 R12
;;�s�v	POP_REG1 R8

	SUB_END
	M_RTS


;	***********************************************************
;	***							***
;	***	�������ׂ��ݒ�ŉ������ׂ��͈͓���R0 !=0	***
;	***							***
;	***********************************************************
;	ANS R0!=0 �������ׂ��ʒu
_ACCST_UP_START_CONF_CHECK
	SUB_START

;[���x�������ꍇ�]������߂�]
;	���ݑ��x^2���Q��(S�|���ݑ��x/1000)+�w��i�����x^2

;;�s�v	PUSH_REG1 R8	;�s��
;;�s�v	PUSH_REG1 R12	;POS
;;�s�v	PUSH_REG1 R13	;SPD
;;�s�v	PUSH_REG1 R14	;INF1
	MOV.L	#_POSCTL_RL_SPD,R4					;
	MOV.L	@R4,R9							;

	MOV.L	@R13,R10						;SPD�F���i�ݒ�
	PUSH_REG1 R1							;
	PUSH_REG1 R2							;
	MOV	R10,R2							;
	FAR_JSR	#_OVER_LIDE_SPD_CALC,R0					;INPUT R2-OUTPUT R2
	MOV	R2,R10							;
	POP_REG1 R2							;
	POP_REG1 R1							;

	MOV.L	#_POSCTL_SV_UP_ACC,R4					;500,000/1000
	MOV.L	@R4,R11							;����ײ�ތ�
									;Input R1,R2 ����
									;Input R9    ���ݑ��x
									;Input R10   �̾�đ��x[�w��i�����x]
									;Input R11   ��������

	XOR	R0,R0
	CMP/GE	R10,R9							;R10(�ݒ葬�x)��R9(���ݑ��x):�s�v
	BT	ACCST_UP_START_CONFCHK_400				;

;	***	Input R1,R2(�c�苗��)		***
;	***	Input R9:SPEED  DATA		***
;	***	Input R10:OFFSET SPEED		***
;	***	Input R11:ACC_LATE		***

	MOV	R10,R0
	MOV	R9,R10
	MOV	R0,R9							;
	FAR_JSR	#_CMP_SPD_REST_PLSCHKCOM,R0				;ANS R0!=0 ����

ACCST_UP_START_CONFCHK_400:						;


;;�s�v	POP_REG1 R14
;;�s�v	POP_REG1 R13
;;�s�v	POP_REG1 R12
;;�s�v	POP_REG1 R8

	SUB_END
	M_RTS






;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	���W�X�^��R0�ȊO�j�󂵂Ȃ�����
;	R0=0/R0=1(�O����,�O����)
;	input R5:�s���ԍ�
;
_ACCST_CHGSPD_LIMIT_INFO_LOAD
	SUB_START
	PUSH_REG1 R1
	PUSH_REG1 R2

	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;��]�F
	TST_BIT_OF ACCST_CHGSPD_LMT_INF_LD_200		;��]�ł͂Ȃ�

	MOV.L	#_MOTION_SPD_CHKCNT,R1
	MOV.W	@R1,R0					;1�i��=0 2�i��=4 3�i��=8,,,
	MOV.L	#_SET1_MOT_INF,R1			;�]���̑O�̒i���O�ϑ���
	SHLL	R0					;
	ADD	R0,R1					;
	MOV.W	@R1,R0					;
	TST	#BIT1,R0				;
	TST_BIT_ON ACCST_CHGSPD_LMT_INF_LD_200		;ON:��ϑ�
	M_BRA	ACCST_CHGSPD_LMT_INF_LD_300		;OFF:�O�ϑ�



;	--------------- �ʏ�̕]�������{����---------------
ACCST_CHGSPD_LMT_INF_LD_200				;
	XOR	R0,R0
	M_BRA	ACCST_CHGSPD_LMT_INF_LD_END		;


;	--------------- �O�ϑ�������]���s�v-----------
ACCST_CHGSPD_LMT_INF_LD_300				;
	MOV.B	#1,R0					;
ACCST_CHGSPD_LMT_INF_LD_END				;

	POP_REG1 R2
	POP_REG1 R1


	SUB_END
	M_RTS

