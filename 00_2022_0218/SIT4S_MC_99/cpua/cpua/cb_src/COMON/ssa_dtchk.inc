;	*******************************************
;	***					***
;	***					***
;	***		Ӱ����ް�����		***
;	***					***
;	***	2015-10-23�X�V			***
;	***					***
;	*******************************************
;	�������ɂ���"1"�̎���������:�����ӏ��������Ă��������邽��
;	�^�]�����ύX
;	�i���ύX
;	�p�x�ύX
;	���x�ύX
;	�^�C�}�ύX(0<=>0�ȊO)
;	�I�[�o���C�h�ύX
;
_EQ_MODORI_INFO		.EQU	100			;�߂�̲�̫Ұ��� 100�i��
_BT_SPD_LMT	.EQU	BIT0
_BT_AGL_LMT	.EQU	BIT1
_BT_SPD_LLL	.EQU	BIT2		;��
_BT_SPD_STP	.EQU	BIT3		;���̓��~�b�g�̑Ώۍs��


_MOTION_DATA_LMT_CHK		;[3������]
	SUB_START




	MOV.L	#_MOTION_CHK_START_FLG,R1	;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF MOTION_DATA_LMTCHK_500	;

	CMP/EQ	#1,R0				;
	BT	MOTION_DATA_LMTCHK_100		;[�v�Z����]

	ADD	#-1,R0				;2->1=�v�Z����
	MOV.L	#_MOTION_CHK_START_FLG,R1	;
	MOV.W	R0,@R1				;

	FAR_JSR	#_DISP_LIMIT_STS_CLR,R0		;��U�ر����

	M_BRA	MOTION_DATA_LMTCHK_500		;

;	----------- �ް���������-------------
MOTION_DATA_LMTCHK_100

;
	FAR_JSR	#_MOTION_DATASPD_CHK,R0

;	--- ���x�ŏ����~�b�g��(����ײ�ނ��Ώ�) ------
	FAR_JSR	#_SPD_POS_SET_ERRCHK1,R0	;���x�ް�����




;	----------- �ð���ް����t-----------------
	FAR_JSR	#_DISP_LIMIT_STS_SEND,R0		;

;	----��������(�ر���Ȃ���΂��̽��݂����񂩉񂵂Ă��ǂ�)-------
	XOR	R0,R0					;�v�Z�I��
	MOV.L	#_MOTION_CHK_START_FLG,R1		;
	MOV.W	R0,@R1					;

MOTION_DATA_LMTCHK_500

;	=============== �J�[�\���ʒu�̑��݂��郊�~�b�g�f�[�^�𑗐M===============
	FAR_JSR	#_DISP_SPD_POS_LIMIT_DATA,R0


	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***		�ݒ�ύX�L��C�x���g		***
;	***		(�ݒ�)				***
;	***************************************************
;	�������ɂ���"1"�̎���������:�����ӏ��������Ă��������邽��
_API_DATA_CHK_CALC_START
	SUB_START
	MOV.B	#3,R0				;
	MOV.L	#_MOTION_CHK_START_FLG,R1	;//3:�ް�CHK�J�n(2),1=���Z,0:�ް������I��
	MOV.W	R0,@R1				;
	SUB_END
	M_RTS

;
;
;
;
;	***************************************************
;	***						***
;	***	�J�[�\���ʒu�̃��~�b�g�𑗕t����	***
;	***						***
;	***************************************************
_DISP_SPD_POS_LIMIT_DATA
	SUB_START

	MOV.L	#_SVP_MOT_CSR_STEP,R1		;Ӱ��݉�ʂŶ��ق�����s��No.
	MOV.W	@R1,R3				;
	TST	R3,R3				;
	TST_BIT_OF DISP_SPD_POS_LIMIT_DT_EXT	;

	ADD	#-1,R3				;
	MOV.L	#_WK_PVP_MOT_STS,R5		;TOP
	SHLL	R3
	ADD	R3,R5				;
	MOV.W	@R5,R0				;



;	---------- ���x�ЯĒl------------
	XOR	R2,R2				;
	TST	#_BT_SPD_LMT,R0			;
	TST_BIT_OF DISP_SPD_POS_LIMIT_DT120	;
	MOV.L	#_PVPX1_CKLMT_SPDTOP,R1		;
	ADD	R3,R1				;
	MOV.W	@R1,R2				;
DISP_SPD_POS_LIMIT_DT120
	MOV.L	#_PVP_CKLMT_SPD,R1		;���x�ЯĒl(���وʒu��)�@���x�Ԋ�
	MOV.W	R2,@R1				;

;	---------- �p�x�ЯĒl------------
	XOR	R2,R2				;
	TST	#_BT_AGL_LMT,R0			;
	TST_BIT_OF DISP_SPD_POS_LIMIT_DT220	;
	MOV.L	#_PVPX1_CKLMT_AGLTOP,R1		;
	ADD	R3,R1				;
	MOV.W	@R1,R2				;
DISP_SPD_POS_LIMIT_DT220			;
	MOV.L	#_PVP_CKLMT_AGL,R1		;�p�x�ЯĒl(���وʒu��)�@�p�x�Ԋ�
	MOV.W	R2,@R1				;


DISP_SPD_POS_LIMIT_DT_EXT

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	�J�[�\�������o�͂���			***
;	***						***
;	***************************************************
;�\���ð��
;	BIT0:�ԁ@���x
;	BIT1:�ԁ@�ʒu
;	BIT2:��
_DISP_LIMIT_STS_CLR
	SUB_START

	MOV.W	#D'100,R3			;
	XOR	R2,R2				;
	MOV.L	#_WK_PVP_MOT_STS,R5

DISP_LIMIT_STSCLR_LOP:
	TST	R3,R3
	TST_BIT_OF DISP_LIMIT_STSCLR_END	;
	MOV.W	R2,@R5				;
	ADD	#2,R5				;
	ADD	#-1,R3				;
	M_BRA	DISP_LIMIT_STSCLR_LOP		;
	
DISP_LIMIT_STSCLR_END

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	�X�e�[�^�X���M			***
;	***					***
;	*******************************************
;
_DISP_LIMIT_STS_SEND
	SUB_START

	DATA_LOP_SHN_MOV SRC=_WK_PVP_MOT_STS,L1=W,DST=_PVP_MOT_STS,L2=W,LOOP=D'100,CNT_REG=R7,DSTADD=2	;

	SUB_END
	M_RTS



;	***************************************************
;	***						***
;	***						***
;	***		Ӱ����ް�����			***
;	***		���x�p���s���ł͑��x����	***
;	***		��~�s���ł͊p�x����		***
;	***						***
;	***************************************************
;	***************************************************
;	***	���i���Ɉ�葬�ɂȂ�Ȃ��B�����ł��Ȃ�	***
;	***	���x�Ԋۂ�SET				***
;	***	PVX_CKSPD_OVBIT	->PVP_MOT_STS[n].BIT1	***
;	***	PVP_CKLMT_SPDTOP->PVPX1_CKLMT_SPDTOP	***
;	***	->[�J�[�\��]PVP_CKLMT_SPD		***
;	***************************************************
;	***************************************************
;	***	��~�s���̒��O�̒i����葬�x�ɂȂ�Ȃ��B***
;	***	�p�x�Ԋۂ�SET				***
;	***	PVP_CKAGL_OVBIT	->PVP_MOT_STS[n].BIT2	***
;	***	PVP_CKLMT_AGLTOP->PVPX1_CKLMT_AGLTOP	***
;	***	->[�J�[�\��]PVP_CKLMT_AGL		***
;	***************************************************
;	MOV.L	#_SETX_POS_SDAT1_SPD,R12		;pls/s
;	MOV.L	#_SETX_POS_SDAT1_TIM,R13		;
;	MOV.L	#_SETX_POS_SDAT1_OFSPOS,R14		;+1��]���l�������ʒu
;	�O�̒i����~�s�����ƂO����̉������Z�ɂȂ邼�I
;
;	[�����\�ł��鑬�x���̃`�F�b�N,���ʂ͑��x���C�����邽�߂̃��~�b�g���x���o��]
;	PVX_CKSPD_OVBIT
;	PVP_CKLMT_MDSPD,R14	;�߂葬�x�@ANS

	.IMPORT	_ACCSEL_CHGSPD_LIMIT_INFO_LOAD	;2016-04-18 �O/�������(ssa_accupdnsel.inc)


_MOTION_DATASPD_CHK:
	SUB_START
;;;;;;;;;;;;;;2017-02-25
;;;;;;;;;;;;;;	------- 2015-10-30 
;;;;;;;;;;;;;;	MOV.L	#_SYS_100STEP_DNM_SEL,R1		;//100�i���̐U�q
;;;;;;;;;;;;;;	MOV.W	@R1,R0					;
;;;;;;;;;;;;;;	CMP/EQ	#1,R0					;�U�q�ł������ōs��(100�i)
;;;;;;;;;;;;;;	BT	MOTION_DATSPDCK_020			;

	.AIF _CHG_DNM_20170225 EQ _CMPILE_YES		;
	MOV.L	#_WPAR_ACC_MATHED,R1			;
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF MOTION_DATSPDCK_020
	.AENDI


	MOV.L	#_SETX_POS_CTL_MATH,R1			;[�ݒ�l������]
	MOV.W	@R1,R0					;
	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON MOTION_DATSPDCK_050			;[]

;	-------------- �ʏ� ����----------------
MOTION_DATSPDCK_020:
	MOV.L	#_SET1_ACCLAT_TIM1,R1			;
	MOV.W	@R1,R2					;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1					;
	M_BRA	MOTION_DATSPDCK_100

;	-------------- �ӂ肱------------------
MOTION_DATSPDCK_050:

	MOV.L	#_ACCB_ACCLAT_TIM1,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1				;


MOTION_DATSPDCK_100:
	MOV.L	#_LINK_MAX_SPD_PLS,R1	;//�ݸ����ٴݺ��ފ��Z�l�@pls/s
	MOV.L	@R1,R2			;
	MOV.L	#_CHKSPDWORKVMAX,R1	;//PLS/S
	MOV.L	R2,@R1			;


	XOR	R0,R0				;
	MOV.L	#_PVX_CKAGL_OVBIT,R1		;�p�x���ސM��
	MOV.W	R0,@R1				;
	MOV.L	#_MOTION_SPD_CHKCNT,R1		;2016-04-18 POINTER[ACCST�p]
	MOV.W	R0,@R1				;2016-04-18 

	FAR_JSR	#_ACCSEL_CHGSPD_LIMIT_INFO_LOAD,R0	;R0=0(��)/1(��)input MOTION_SPD_CHKCNT
	MOV.L	#_CHKACCINF2,R1				;
	MOV.W	R0,@R1					;
;	----------- ACCST�p �O�ϑ��p--------
	XOR	R0,R0		;
	MOV.L	#_CHKACCINF1,R1	;�O(0=��ϑ�)
	MOV.W	R0,@R1		;
	MOV.L	#_CHKACCINF0,R1	;�O�X(0=��ϑ�)
	MOV.W	R0,@R1		;


	MOV.L	#_SETX_POS_STEP_MAX,R1			;
	MOV.W	@R1,R5					;�ݒ�1~10
	ADD	#1,R5					;1�i�̏ꍇ    2�̑��x����
							;10�i�̏ꍇ  11�̑��x����

;;;;;;	2015-10-26
;;;;;;	XOR	R0,R0					;
;;;;;;	MOV.L	#_CHKSPDPOSOFS,R1			;
;;;;;;;	MOV.W	R0,@R1					;//2014-06-10

	XOR	R7,R7					;�ʒu���Z�̶�����R7[_CHKSPDPOSOFS]���g�p

;;;;2015-10-26	XOR	R7,R7					;���x���ސM�� STEP���Z����[���g�p]
;;;;2015-10-26	MOV.W	#BIT0,R8			;
	MOV.L	#_WK_PVP_MOT_STS,R8			;�߂�s��TOP+(100-1) 2015-10-26

	MOV.L	#_SETX_POS_SDAT1_SPD,R9			;
	MOV.L	#_SETX_POS_SDAT1_TIM,R10		;
	MOV.L	#_SETX_POS_SDAT1_OFSPOS,R11		;
	MOV.L	#_SETX_POS_SDAT1_INF1,R12		;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R13		;0.1%

	MOV.L	#_PVPX1_CKLMT_SPDTOP,R14		;2015-09-30 SAVE(���xLIMIT-SAVE)


;	-------- �������x=0 ---------
	XOR	R2,R2					;(OLD)
	MOV.L	#_CHKSPDWORK1,R1			;PLS/S
	MOV.L	R2,@R1					;WORK=0 SPEED
	MOV.L	#_CHKSPDPERWORK1,R1			;//
	MOV.W	R2,@R1					;%

	MOV.L	#_CHKSPDWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.L	R2,@R1					;2016-04-18[�O�X�i ACCST�p]
	MOV.L	#_CHKSPDPERWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.W	R2,@R1					;2016-04-18[�O�X�i ACCST�p]


;	-------- �����ʒu=�ҋ@�_ ---------
	MOV.L	#_SETX_UPAREA_PLS,R1			;//4;�ҋ@�_
	MOV.L	@R1,R2					;
	MOV.L	#_CHKPOSWORK1,R1			;�O�iPOS
	MOV.L	R2,@R1					;
	MOV.L	#_CHKPOSWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.L	R2,@R1					;2016-04-18[�O�X�i ACCST�p]



MOTION_DATSPDCK_200LOP:
	MOV	R7,R0					;2015-10-28[����+4]

	MOV.W	#1,R4					;�c��
	CMP/EQ	R4,R5					;�c��=1 �s��MAX
	BF	MOTION_DATSPDCK_220
	M_BRA	MOTION_DATSPDCK_800			;
;;;;;	------------- �ŏI�i�̉��Z----------------
;;;;;	MOV.L	#_SVP_UPAREA_SPD0,R1			;�s��MAX���͖߂葬�x
;;;;;	MOV.W	@R1,R2					;
;;;;;	M_BRA	MOTION_DATSPDCK_240			;
;;;;;	M_BRA	MOTION_DATSPDCK_800			;



MOTION_DATSPDCK_220
;	-------- �ݒ葬�x0.1%-------------------
	MOV.W	@R13,R2					;���x%
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%

;	---------�ݒ葬�xPLS/S---------------
	MOV.L	@(R0,R9),R2				;�ڕW���xPLS/S
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;WORK=0 SPEED


;	---------�ݒ�p�xPLS---------------
	MOV.L	@(R0,R11),R2				;�ڕW�ʒu
	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	R2,@R1					;








;	---------------------------------
;;;;�s�v	MOV.L	@(R0,R10),R3				;
;;;;�s�v	TST	R3,R3					;tim != 0 ��~�s��
;;;;�s�v		TST_BIT_ON MOTION_DATSPDCK_500			;

	MOV.L	@(R0,R12),R2				;
	MOV.L	#_CHKSPDPOSINFO,R1			;
	MOV.W	R2,@R1					;INFO SAVE(BIT1=1�t�])

	MOV.B	#BIT0,R4				;
	TST	R4,R2					;
	TST_BIT_OF MOTION_DATSPDCK_500			;��~�̍s��(������,���]����,��ϗL)

;;;;;�t�]�̍s�������Z����	MOV.W	#BIT1,R4				;
;;;;;�t�]�̍s�������Z����	TST	R4,R2					;
;;;;;�t�]�̍s�������Z����	TST_BIT_ON MOTION_DATSPDCK_500			;�t�]�s���͉��Z���Ȃ�



	PUSH_REG1 R0	;ADR
	PUSH_REG1 R7	;ADR

;;	PUSH_REG1 R5	;CNT
;;	PUSH_REG1 R7	;�o���׸�
;;	PUSH_REG1 R8	;BIT0~BIT9,BIT15
;;	PUSH_REG1 R9	;TOP
;;	PUSH_REG1 R10	;TOP
;;	PUSH_REG1 R11	;TOP
;;	PUSH_REG1 R12	;TOP

	FAR_JSR	#_CHGSPD_LIMIT_CALC,R0

;;	POP_REG1 R12	;TOP
;;	POP_REG1 R11	;TOP
;;	POP_REG1 R10	;TOP
;;	POP_REG1 R9	;TOP
;;	POP_REG1 R8	;BIT0~BIT9,BIT15
;;	POP_REG1 R7	;�o���׸�
;;	POP_REG1 R5	;CNT

	POP_REG1 R7			;ADR
	POP_REG1 R0			;ADR
	M_BRA	MOTION_DATSPDCK_600	;


;	--------- ��~�s��[�ʒu�̉��Z���s��]------------
MOTION_DATSPDCK_500:

;;;;;;2016-04-18	PUSH_REG1 R0	;ADR
	PUSH_REG1 R7	;ADR
	FAR_JSR	#_CHGPOS_LIMIT_CALC,R0
	POP_REG1 R7			;ADR
;;;;;;2016-04-18	POP_REG1 R0			;ADR


;	--------- ���x��0����͂��߂�-----------
	XOR	R2,R2					;
	MOV.L	#_CHKSPDWORK2,R1			;���̉��Z�ɂ�0����J�n��
	MOV.L	R2,@R1					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%

;	------ 2016-04-18------------
	XOR	R2,R2					;
	MOV.L	#_CHKACCINF0,R1				;��(0=��ϑ�)
	MOV.W	R2,@R1					;(�O�̒i����ϑ��ɂ���������)

MOTION_DATSPDCK_600:

;;;2015-10-28	ADD	#4,R0				;CHKSPDPOSOFS
;;;2015-10-28	MOV.L	#_CHKSPDPOSOFS,R1		;
;;;2015-10-28	MOV.W	R0,@R1				;

	ADD	#-1,R5					;
	TST	R5,R5					;
	TST_BIT_OF MOTION_DATSPDCK_700			;

	MOV.L	#_CHKSPDWORK2,R1			;���i
	MOV.L	@R1,R2					;
	MOV.L	#_CHKSPDWORK1,R1			;�O�i
	MOV.L	@R1,R0					;2016-04-18[ACCST�p]
	MOV.L	R2,@R1					;
	MOV.L	#_CHKSPDWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.L	R0,@R1					;2016-04-18[�O�X�i ACCST�p]


	MOV.L	#_CHKPOSWORK2,R1			;���i
	MOV.L	@R1,R2					;
	MOV.L	#_CHKPOSWORK1,R1			;�O�i
	MOV.L	@R1,R0					;2016-04-18[ACCST�p]
	MOV.L	R2,@R1					;
	MOV.L	#_CHKPOSWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.L	R0,@R1					;2016-04-18[�O�X�i ACCST�p]

	MOV.L	#_CHKSPDPERWORK2,R1			;���i
	MOV.W	@R1,R2					;0.1%
	MOV.L	#_CHKSPDPERWORK1,R1			;�O�i
	MOV.W	@R1,R0					;2016-04-18[ACCST�p]
	MOV.W	R2,@R1					;0.1%
	MOV.L	#_CHKSPDPERWORK0,R1			;2016-04-18[�O�X�i ACCST�p]
	MOV.W	R0,@R1					;2016-04-18[�O�X�i ACCST�p]


;	----------- CNT 0:1�i�� 1:2�i�� 2016-04-18----------
	MOV.L	#_MOTION_SPD_CHKCNT,R1			;2016-04-18
	MOV.W	@R1,R0					;2016-04-18
	ADD	#1,R0					;2016-04-18
	MOV.W	R0,@R1					;2016-04-18
	FAR_JSR	#_ACCSEL_CHGSPD_LIMIT_INFO_LOAD,R0	;R0=0(��)/1(��)input MOTION_SPD_CHKCNT

	MOV.L	#_CHKACCINF2,R4			;
	MOV.W	@R4,R2				;
	MOV.W	R0,@R4				;NEW DATA SAVE
	MOV.L	#_CHKACCINF1,R1		;
	MOV.W	@R1,R0			;
	MOV.W	R2,@R1			;INF2(�����O)
	MOV.L	#_CHKACCINF0,R1		;
	MOV.W	R0,@R1			;INF1(�O���O�X�i)




	ADD	#4,R7					;2015-10-28CHKSPDPOSOFS
;;;	SHLL	R8					;2015-10-28 BIT->ADR
	ADD	#2,R8					;2015-10-28
	ADD	#2,R13					;
	ADD	#2,R14					;



	M_BRA	MOTION_DATSPDCK_200LOP			;

MOTION_DATSPDCK_700:
	M_BRA	MOTION_DATSPDCK_900

;	----------- �ŏI���x-----------
MOTION_DATSPDCK_800:
	MOV.L	#_SVP_UPAREA_SPD0,R1			;�s��MAX���͖߂葬�x
	MOV.W	@R1,R2					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%
;	---------�ݒ葬�xPLS/S---------------
	MOV.L	@(R0,R9),R2				;�ڕW���xPLS/S
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;
;	---------�ݒ�p�xPLS---------------
	MOV.L	@(R0,R11),R2				;�ڕW�ʒu
	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	R2,@R1					;


	PUSH_REG1 R0	;ADR
	FAR_JSR	#_LASTSPD_LIMIT_CALC,R0
	POP_REG1 R0			;ADR




MOTION_DATSPDCK_900:

;;;;;	2015-10-28
;;;;;	MOV.L	#_PVX_CKSPD_OVBIT,R1			;�ԕ\��(BIT0~BIT9 BIT15:�ߑ��x)
;;;;;	MOV.W	R7,@R1					;

MOTION_DATSPDCK_EXT:
;;;;;2015-10-28	FAR_JSR	#_MOTION_DATCK_MOVE,R0				;

	SUB_END
	M_RTS

;
;
;	.GLOBAL	_CHKSPDWORK1;
;	.GLOBAL	_CHKSPDWORK2;
;
;
;
;;;MOTION_DATSPDCK_CLR:
;;;	SUB_START
;;;	XOR	R0,R0			;
;;;	MOV.L	#_PVX_CKSPD_OVBIT,R1	;
;;;	MOV.W	R0,@R1
;;;	SUB_END
;;;	M_RTS



;;;;;2015-10-28_MOTION_DATCK_MOVE:
;;;;;2015-10-28	SUB_START
;;;;;2015-10-28
;;;;;2015-10-28;	-------------------------------
;;;;;2015-10-28	MOV.L	#_PVX_CKSPD_OVBIT,R1		;
;;;;;2015-10-28	MOV.W	@R1,R0				;
;;;;;2015-10-28	MOV.L	#_PVP_CKSPD_OVBIT,R1		;
;;;;;2015-10-28	MOV.W	R0,@R1				;
;;;;;2015-10-28
;;;;;2015-10-28;	-------------------------------
;;;;;2015-10-28	MOV.L	#_PVX_CKAGL_OVBIT,R1			;�p�x���ސM��
;;;;;2015-10-28	MOV.W	@R1,R0				;
;;;;;2015-10-28	MOV.L	#_PVP_CKAGL_OVBIT,R1		;
;;;;;2015-10-28	MOV.W	R0,@R1				;
;;;;;2015-10-28	SUB_END
;;;;;2015-10-28	M_RTS

;	***********************************
;	***				***
;	***				***
;	***				***
;	***********************************

_CHGSPD_LIMIT		.EQU	2000	;
_CHGSPD_HIS		.EQU	20	;2.0%

_CHGSPD_LIMIT_CALC:
	SUB_START

	PUSH_REG1 R14


;	------2016-04-18--------------------------
	MOV.L	#_CHKACCINF1,R4				;
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF CHGSPD_LMT_CAL050			;��ϑ�

	FAR_JSR	#_FPU_SEL_CALC_SPD,R0			;ANS:R2
	M_BRA	CHGSPD_LMT_CAL100			;

CHGSPD_LMT_CAL050

	FAR_JSR	#_FPU_CALC_SPD,R0		;LIMIT���Z R0~R4,R6,FPU ANS=R2 100.00%

CHGSPD_LMT_CAL100

	MOV.L	#_CHKSPDPERWORK1,R4	;//0.1
	MOV.W	@R4,R6			;Vn_1
	MOV.L	#_CHKSPDPERWORK2,R4	;//0.1
	MOV.W	@R4,R1			;Vn


	MOV.W	#1,R4			;
	CMP/EQ	R4,R5			;�c"1"[�߂�]
	BF	CHGSPD_LMT_CAL300	;

;;;2015-10-26	MOV.L	#_PVP_CKLMT_MDSPD,R14	;�߂葬�x�@ANS
;;;2015-10-26	MOV.W	#BIT15,R8		;�߂�BIT15
	MOV.L	#_PVPX1_CKLMT_SPDTOP+(_EQ_MODORI_INFO-1)*2,R14	;//cpua=>cpud ���x�Я� [0:1�i��]
	MOV.L	#_WK_PVP_MOT_STS+(_EQ_MODORI_INFO-1)*2,R8	;�߂�s��TOP+(100-1)


CHGSPD_LMT_CAL300:

	CMP/EQ	R1,R6				;�������x
	BT	CHGSPD_LMT_CAL900		;���Ȃ�

	CMP/GT	R6,R1				;����
	BT	CHGSPD_LMT_CAL600		;YES�@R6(Vn_1)<R1(Vn)

;	------ ����----
	CMP/GT	R1,R2			;Vn < V_minLIMIT
	BF	CHGSPD_LMT_CAL800	;NO! OK
;;;	OR	R8,R7			;�ԐM�����[Vn < V_minLIMIT]
	FAR_JSR	#_SPD_LMT_BIT_ON,R0	;2015-10-28�ԐM�����
	M_BRA	CHGSPD_LMT_CAL800	;

CHGSPD_LMT_CAL600
;	----- ���� -------

	CMP/GT	R2,R1			;V_maxLIMIT < Vn
	BF	CHGSPD_LMT_CAL800	;NO! OK
;;;	OR	R8,R7			;�ԐM�����[V_maxLIMIT < Vn]
	FAR_JSR	#_SPD_LMT_BIT_ON,R0	;2015-10-28�ԐM�����
CHGSPD_LMT_CAL800:

	MOV.W	R2,@R14			;LIMIT SET ���x�\��

CHGSPD_LMT_CAL900:
	POP_REG1 R14

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***				***
;	***	��ϑ����\��?		***
;	***	���̎��̃��~�b�g���x	***
;	***				***
;	***********************************
;	.GLOBAL	_CHKSPDWORK1;//PLS/S
;	.GLOBAL	_CHKSPDWORK2;//PLS/
;	.GLOBAL	_CHKPOSWORK;//PLS
;	.GLOBAL	_CHKSPDWORKANS;//PLS/S
;	.GLOBAL	_CHKSPDWORKVMAX;//PLS/S
;	.GLOBAL	_CHKSPDWORKTMAX;//ms
;	.GLOBAL	_CHKSPDANSPER;// 1%�P���ް� 100.00
;
;
;
_FPU_CALC_SPD
	SUB_START

	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_CALCSPD_ZERO			;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	CMP/PZ	R3					;
	BT	FPU_CALCSPD_050				;
	NEG	R3,R3					;
FPU_CALCSPD_050:					;


;	-------- ���E�r=R1*R2/R4 *R3 ------
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1*FR2=>FR2

	FDIV	FR4,FR2					;

	FTRC	FR2,FPUL				;
	STS	FPUL,R0					;�����_�폜
	LDS	R0,FPUL					;
	FLOAT	FPUL,FR2				;

	FADD	FR2,FR2					;FR2*2

	LDS	R3,FPUL					;
	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)

	FMUL	FR1,FR2					;FR2�F�Q�E���E�r
;	----------------------------

	MOV.L	#_CHKSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1==FR2

	MOV.L	#_CHKSPDWORK2,R0			;//PLS/S
	MOV.L	@R0,R2					;
	CMP/HS	R1,R2					;
	BF	FPU_CALCSPD_100				;

	FADD	FR1,FR2					;����
	M_BRA	FPU_CALCSPD_200				;

FPU_CALCSPD_100:					;
	FNEG	FR2
	FADD	FR1,FR2					;����
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	CMP/PL	R2					;
	BF	FPU_CALCSPD_ZERO			;
FPU_CALCSPD_200:					;
	FSQRT	FR2					;
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;

	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	R2,@R0					;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R4					;
	MOV.L	#D'1000,R1				;100.0%


	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1(1000)*FR2(pls/s)/(VMAX)
	FDIV	FR4,FR2					;


	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.W	#_CHGSPD_LIMIT,R4			;200.0%
	CMP/HS	R2,R4					;
	BT	FPU_CALCSPD_EXT				;
	MOV	R4,R2					;
	M_BRA	FPU_CALCSPD_EXT				;0.1%

FPU_CALCSPD_ZERO:
	MOV.L	#0,R2					;0.1%

FPU_CALCSPD_EXT:
	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data ��1����.0

	SUB_END
	M_RTS



;	***************************************************
;	***						***
;	***		���[�V������~�ʒu�`�F�b�N	***
;	***						***
;	***************************************************
;	���̑��x�Œ�~�\�����`�F�b�N����B
;	V^2= 2����S
;	S= V^2/(2���)
;	R2(SPD)*R2(SPD)
;	���](S2>S1) S2-S ��S1 ���ok�@ S2-S<S1�@then S1=S2-S
;	�t�](S2<S1) S2+S ��S1 ���ok�@ S2+S<S1�@then S1=S2+S
;
_DCHKDIGHOS	.EQU	20	

_CHGPOS_LIMIT_CALC:
	SUB_START

	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_CALCPOS_ZERO			;[����0�Ȃ̂łǂ�ȉ��������\]


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	CMP/PZ	R3					;
	BT	FPU_CALCPOS_050				;
	NEG	R3,R3					;
FPU_CALCPOS_050:					;


;	-------- ��=R1*R2/R4  ------
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1*FR2=>FR2

	FDIV	FR4,FR2					;

	FTRC	FR2,FPUL				;
	STS	FPUL,R0					;�����_�폜
	LDS	R0,FPUL					;
	FLOAT	FPUL,FR2				;

	TST	R0,R0					;
	TST_BIT_OF FPU_CALCPOS_ZERO			;��=0 ���Z�s��

;	--------- FR2=2�� --------------
	FADD	FR2,FR2					;FR2*2�FFR2=2*��


;	----------------------------
;;;[[[2014-0808]]]	MOV.L	#_CHKSPDWORK2,R0			;//PLS/S
;;;[[[2014-0808]]]	MOV.L	@R0,R1					;Vn
	MOV.L	#_CHKSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1:V^2


	FDIV	FR2,FR1					;FR1(V^2)/FR2(2��)
	FTRC	FR1,FPUL				;
	STS	FPUL,R2					;R2=FR1:����


	CMP/GE	R2,R3					;R2(���Z����)=<R3(�ݒ�)
	BT	FPU_CALCPOS_500				;
							;����ʒu
;	=========== �p�x�I�[�o�ʒu�ł���=============
;;;	2-15-10-26
;;;	MOV	R8,R4
;;;	SHLR	R4					;
;;;	MOV.L	#_PVX_CKAGL_OVBIT,R1			;�p�x���ސM��
;;;	MOV.W	@R1,R0					;
;;;	OR	R4,R0					;�������Ă���1�O
;;;	MOV.W	R0,@R1					;
;	--------- �����s����1�O--------------
	TST	R7,R7					;����!=0
	TST_BIT_OF FPU_CALCPOS_060			;

	MOV	R8,R4					;
	ADD	#-2,R8					;
	FAR_JSR	#_AGL_LMT_BIT_ON,R0			;
	MOV	R4,R8					;

FPU_CALCPOS_060:					;

;	---------------------------------------



;	"R2":����
	MOV.L	#_CHKPOSWORK2,R1			;//PLS
	MOV.L	@R1,R4					;

	ADD	#_DCHKDIGHOS,R2				;20PLS

	MOV.L	#_CHKSPDPOSINFO,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT1,R0				;
	TST_BIT_OF FPU_CALCPOS_100			;��

	NEG	R2,R2					;

FPU_CALCPOS_100:
	SUB	R2,R4					;R4:

	MOV	R4,R2					;R2=S2-LNGTH

;	-- ��ٽ----
	MOV.L	#_CHKPOSWORKANS,R1				;//PLS(2014-06-10�ʒu�����p)
	MOV.L	R2,@R1						;

	MOV.L	#_SETY_INCPLS_HOSM01X,R0			;//0.1�x
	MOV.L	@R0,R1						;
	MOV.L	#_CALC_MEM_1REV_MUL_NROT,R0			;
	MOV.L	@R0,R4						;R2:X��]
	CMP/GE	R2,R4						;R2 <= R4
	BT	FPU_CALCPOS_150
	SUB	R4,R2						;
FPU_CALCPOS_150:
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;R2*1REV*HOSN/HOSM



	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0			;R0,R1,R2�̂ݎg�p

	MOV.L	#_CHKPOSANSDIG,R1				;
	MOV.W	R2,@R1						;

;;;;;2015-10-28	MOV.L	#_CHKSPDPOSOFS,R1				;
;;;;;2015-10-28	MOV.W	@R1,R0						;
	MOV	R7,R0	;2015-10-28 CHKSPDPOSOFS +4�Â̃J�E���^

	TST	R0,R0
	TST_BIT_OF FPU_CALCPOS_EXT				;
	ADD	#-4,R0						;
	SHLR	R0						;1/2
	MOV.L	#_PVPX1_CKLMT_AGLTOP,R1				;2015-09-30 100�i
	ADD	R0,R1						;
	MOV.W	R2,@R1						;

FPU_CALCPOS_500:
FPU_CALCPOS_ZERO:
FPU_CALCPOS_EXT:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�ŏI���x�i�߂葬�x�j		***
;	***					***
;	*******************************************
;	Vn^2 > ���ES�{Vn_1^2/2�Ȃ瑬�x�ُ��
;	�Яđ��x=��(���ES�{Vn_1^2/2)

_LASTSPD_LIMIT_CALC:
	SUB_START

	PUSH_REG1 R14

;	-----------------------------------------------
;	-----------------------------------------------
;	-----------------------------------------------
	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_LASTCALCSPD_ZERO			;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	TST	R3,R3
	TST_BIT_ON FPU_LASTCALCSPD_030			;
	M_BRA	FPU_LASTCALCSPD_ZERO			;����=0�@�ُ� ���肦�Ȃ�

FPU_LASTCALCSPD_030:					;
	CMP/PZ	R3					;
	BT	FPU_LASTCALCSPD_050			;
	NEG	R3,R3					;
FPU_LASTCALCSPD_050:					;


;	-------- ���E�r=R1*R2/R4 *R3 ------
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1*FR2=>FR2

	FDIV	FR4,FR2					;

	FTRC	FR2,FPUL				;
	STS	FPUL,R0					;�����_�폜
	LDS	R0,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R3,FPUL					;
	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)

	FMUL	FR1,FR2					;FR2�F���E�r

;	----------------------------

	MOV.L	#_CHKSPDWORK1,R0			;//Vn_1:PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1==FR2

	MOV.W	#2,R4
	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;
	FDIV	FR4,FR1					;

;	FR1 =      Vn_1^2 /2 = FR1*FR1/FR4

	FADD	FR1,FR2					;FR2:���~S+Vn_1^2/2
	FSQRT	FR2					;
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	R2,@R0					;R2=��(���~S+Vn_1^2/2)

;	---------------- �Яđ��x���Z----------------

	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R4					;
	MOV.L	#D'1000,R1				;100.0%

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1(1000)*FR2(pls/s)/(VMAX)
	FDIV	FR4,FR2					;


	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.W	#_CHGSPD_LIMIT,R4			;200.0%
	CMP/HS	R2,R4					;
	BT	FPU_LASTCALCSPD_EXT			;
	MOV	R4,R2					;
	M_BRA	FPU_LASTCALCSPD_EXT			;0.1%

FPU_LASTCALCSPD_ZERO:
	MOV.L	#0,R2					;0.1%

FPU_LASTCALCSPD_EXT:
	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data ��1����.0

;	-----------------------------------------------
;	-----------------------------------------------
;	-----------------------------------------------
;;;;2015-10-28	MOV.L	#_PVP_CKLMT_MDSPD,R14	;�߂葬�x�@ANS
;;;;2015-10-28	MOV.W	#BIT15,R8		;�߂�BIT15
	MOV.L	#_PVPX1_CKLMT_SPDTOP+(_EQ_MODORI_INFO-1)*2,R14	;//cpua=>cpud ���x�Я� [0:1�i��]
	MOV.L	#_WK_PVP_MOT_STS+(_EQ_MODORI_INFO-1)*2,R8	;�߂�s��TOP+(100-1)


	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	@R0,R2					;R2=��(���~S+Vn_1^2/2)

	MOV.L	#_CHKSPDWORK2,R0	;//PLS/S
	MOV.L	@R0,R1			;���x

	CMP/GT	R2,R1			;LIMIT < Vn
	BF	LASTSPD_LMT_CAL800	;NO! OK
;;;;	OR	R8,R7			;�ԐM�����
	FAR_JSR	#_SPD_LMT_BIT_ON,R0	;2015-10-28�ԐM�����

LASTSPD_LMT_CAL800:

	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	@R0,R2					;0~100.0%data ��1����.0
	MOV.W	R2,@R14					;LIMIT SET

LASTSPD_LMT_CAL900:
	POP_REG1 R14

	SUB_END
	M_RTS








;	***********************************
;	***				***
;	***				***
;	***	��ϑ����\��?		***
;	***	���̎��̃��~�b�g���x	***
;	***				***
;	***********************************
;	MOV.L	#_CHKACCINF1,R4				;
;	MOV.W	@R4,R0					;
;	TST	#BIT0,R0				;
;	TST_BIT_OF CHGSPD_LMT_CAL050			;��ϑ�
;
;	�O�̒i�͑O�ϑ��̏���
;
;
_FPU_SEL_CALC_SPD
	SUB_START

	MOV.L	#_CHKACCINF0,R4				;
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF FPU_SEL_CALCSPD_200			;�O�O�i����ϑ� JUMP(���\���)

;;	CALSPDWORK1;//�O�s��PLS/S
;;	CALSPDWORK2;//�]�����錻�s��PLS/
;;	CALPOSWORK1;//�O�s��PLS
;;	CALPOSWORK2;//�]�����錻�s��PLS

	MEM_MOV_TO_MEM	_CHKSPDWORK2,L,_CALSPDWORK2,L,R1,R2,R4;NEW
	MEM_MOV_TO_MEM	_CHKSPDWORK1,L,_CALSPDWORK1,L,R1,R2,R4;OLD
	MEM_MOV_TO_MEM	_CHKPOSWORK2,L,_CALPOSWORK2,L,R1,R2,R4;NEW
	MEM_MOV_TO_MEM	_CHKPOSWORK1,L,_CALPOSWORK1,L,R1,R2,R4;OLD
	XOR	R0,R0					;
	MOV.L	#_CALPOSLNWORK,R1			;
	MOV.L	R0,@R1					;

	FAR_JSR	#_FPU_COM_CALC_SPD,R0			;
	CMP/PZ	R0					;
	BT	FPU_SEL_CALCSPD_100			;
	MOV.L	#_CHKSPDPERWORK1,R1			;
	MOV.W	@R1,R2					;�O�i
FPU_SEL_CALCSPD_100
	M_BRA	FPU_SEL_CALCSPD_500

;	---------------------------------------------------------
FPU_SEL_CALCSPD_200

;	-----------------------
	MEM_MOV_TO_MEM	_CHKSPDWORK1,L,_CALSPDWORK2,L,R1,R2,R4;NEW �O�i
	MEM_MOV_TO_MEM	_CHKSPDWORK0,L,_CALSPDWORK1,L,R1,R2,R4;OLD �O�O�i
	FAR_JSR	#_FPU_COM_CALC_LNG,R0


;	-----------------------SPD2�͉���/����������
	MEM_MOV_TO_MEM	_CHKSPDWORK2	,L,_CALSPDWORK2,L,R1,R2,R4;NEW
	MEM_MOV_TO_MEM	_CHKSPDWORK1	,L,_CALSPDWORK1,L,R1,R2,R4;OLD
	MEM_MOV_TO_MEM	_CHKPOSWORK1	,L,_CALPOSWORK2,L,R1,R2,R4;NEW
	MEM_MOV_TO_MEM	_CHKPOSWORK0	,L,_CALPOSWORK1,L,R1,R2,R4;OLD
	MEM_MOV_TO_MEM	_CALPOSANSLNG	,L,_CALPOSLNWORK,L,R1,R2,R4;
	FAR_JSR	#_FPU_COM_CALC_SPD,R0			;
	CMP/PZ	R0					;
	BT	FPU_SEL_CALCSPD_300			;
	MOV.L	#_CHKSPDPERWORK1,R1			;
	MOV.W	@R1,R2					;�O�i
FPU_SEL_CALCSPD_300					;
	NOP						;
FPU_SEL_CALCSPD_500
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	2016-04-18			***
;	***	Vlimit= ��(V1^2+|2��S|)		***
;	***	Vlimit= ��(V1^2-|2��S|)		***
;	***					***
;	*******************************************
;	�قڊ��S�ȋ��ʃT�u���[�`��
;	��=Vmax/Tmax CHKSPDWORKVMAX/CHKSPDWORKTMAX
;	S=|CALPOSWK2-CALPOSWK1|-CALPOSLN_WORK
;	����:CALSPDWORK2-CALSPDWORK1
;	CALSPDWORKANS=PLS/S
;	CALSPDANSPER=% (MAX200%)
;
;	R0=1 ERR Vn=0
;	R0=0 NOMAL
;	R0=-1 ERR �O��Vn
;
;	input1
;	CHKSPDWORKTMAX
;	CHKSPDWORKVMAX
;
;	input2
;	CALSPDWORK1;//�O�s��PLS/S
;	CALSPDWORK2;//�]�����錻�s��PLS/
;	CALPOSWORK1;//�O�s��PLS
;	CALPOSWORK2;//�]�����錻�s��PLS
;	CALPOSLNWORK;//0
;
;	output R2,R0(�ð��)
;	CALSPDWORKANS;//PLS/S
;	CALSPDANSPER;//0.1%�P���ް� 100
;
_FPU_COM_CALC_SPD
	SUB_START

	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_COM_CALCSPD_ZERO			;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CALPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CALPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	CMP/PZ	R3					;
	BT	FPU_COM_CALCSPD_050			;
	NEG	R3,R3					;
FPU_COM_CALCSPD_050:					;


	MOV.L	#_CALPOSLNWORK,R0			;
	MOV.L	@R0,R6					;(�ʏ��0)
	SUB	R6,R3					;
	
	CMP/PL	R3
	BT	FPU_COM_CALCSPD_080			;
	M_BRA	FPU_COM_CALCSPD_ERR			;

FPU_COM_CALCSPD_080:					;


;	-------- ���E�r=R1*R2/R4 *R3 ------
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1*FR2=>FR2

	FDIV	FR4,FR2					;

	FTRC	FR2,FPUL				;
	STS	FPUL,R0					;�����_�폜
	LDS	R0,FPUL					;
	FLOAT	FPUL,FR2				;

	FADD	FR2,FR2					;FR2*2

	LDS	R3,FPUL					;
	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)

	FMUL	FR1,FR2					;FR2�F|�Q�E���E�r|
;	----------------------------

	MOV.L	#_CALSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1==FR2

	MOV.L	#_CALSPDWORK2,R0			;(������p)
	MOV.L	@R0,R2					;
	CMP/HS	R1,R2					;
	BF	FPU_COM_CALCSPD_100				;

	FADD	FR1,FR2					;���� Vn_1^2+|2��S|
	M_BRA	FPU_COM_CALCSPD_200				;

FPU_COM_CALCSPD_100:					;
	FNEG	FR2					;FR2�F-|2��S|
	FADD	FR1,FR2					;���� Vn_1^2-|2��S|
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	CMP/PL	R2					;
	BF	FPU_COM_CALCSPD_ZERO			;
FPU_COM_CALCSPD_200:					;
	FSQRT	FR2					;
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;

	MOV.L	#_CALSPDWORKANS,R0			;//PLS/S
	MOV.L	R2,@R0					;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R4					;
	MOV.L	#D'1000,R1				;100.0%


	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1(1000)*FR2(pls/s)/(VMAX)
	FDIV	FR4,FR2					;


	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.W	#_CHGSPD_LIMIT,R4			;200.0%
	CMP/HS	R2,R4					;
	BT	FPU_COM_CALCSPD_900				;
	MOV	R4,R2					;
	M_BRA	FPU_COM_CALCSPD_900				;0.1%


FPU_COM_CALCSPD_ERR:
	MOV.L	#0,R2					;0.1%
	MOV.L	#_CALSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data ��1����.0
	MOV.B	#-1,R0					;ERR1:�O�̒l��\������
	M_BRA	FPU_COM_CALCSPD_END

FPU_COM_CALCSPD_ZERO:
	MOV.L	#0,R2					;0.1%
	MOV.L	#_CALSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data ��1����.0
	MOV.B	#1,R0					;ERR1:
	M_BRA	FPU_COM_CALCSPD_END

FPU_COM_CALCSPD_900:
	MOV.L	#_CALSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data ��1����.0
	XOR	R0,R0					;NOMAL
FPU_COM_CALCSPD_END:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	2016-04-18			***
;	***	LNEGTH=(V2^2-V1^2)/(2��)	***
;	***					***
;	***					***
;	*******************************************
;	�قڊ��S�ȋ��ʃT�u���[�`��
;
;	R0=1 ERR Vn=0
;	R0=0 NOMAL
;	INPUT1
;_CHKSPDWORKTMAX			;//
;_CHKSPDWORKVMAX			;//PLS/S
;	INPUT2
;_CALSPDWORK2				;//PLS/S
;_CALSPDWORK1				;//PLS/S
;	OUTPUT R2
;_CALPOSANSLNG

_FPU_COM_CALC_LNG
	SUB_START


	MOV.L	#_CALSPDWORK2,R0			;//PLS/S
	MOV.L	@R0,R2					;
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;
	FMUL	FR2,FR2					;FR2*FR2

;	----------------------------
	MOV.L	#_CALSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;
	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1
	FSUB	FR1,FR2					;FR2= V2^2-V1^2


	CMP/HS	R1,R2					;
	BT	FPU_COM_CALCLNG_100			;R1 =< R2
	FNEG	FR2					;
FPU_COM_CALCLNG_100:					;

	MOV.L	#D'1000*2,R4				;(V2^2-V1^2)*Tmax/Vmax /2/1000
	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;
	FDIV	FR4,FR2					;


	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R1					;
	TST	R1,R1					;
	TST_BIT_OF FPU_COM_CALCLNG_ZERO			;

	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_COM_CALCLNG_ZERO			;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1(1000)*Tmax/(VMAX)
	FDIV	FR4,FR2					;FR2:ANS

	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	M_BRA	FPU_COM_CALCLNG_900			;


FPU_COM_CALCLNG_ZERO:
	MOV.L	#0,R2					;0.1%
	MOV.L	#_CALPOSANSLNG,R0			;
	MOV.L	R2,@R0					;0~100.0%data ��1����.0
	MOV.B	#1,R0					;ERR1:
	M_BRA	FPU_COM_CALCLNG_END


FPU_COM_CALCLNG_900:
	MOV.L	#_CALPOSANSLNG,R0			;
	MOV.L	R2,@R0					;0~100.0%data ��1����.0
	XOR	R0,R0					;NOMAL
FPU_COM_CALCLNG_END:

	SUB_END
	M_RTS




;	***************************************************
;	***						***
;	***	���i���Ɉ�葬�ɂȂ�Ȃ��B�����ł��Ȃ�	***
;	***	���x�Ԋۂ�SET				***
;	***	BIT0					***
;	***						***
;	***************************************************
_SPD_LMT_BIT_ON
	SUB_START
	MOV.W	@R8,R0					;
	OR	#_BT_SPD_LMT,R0				;���x�Ԋ��ޯ�
	MOV.W	R0,@R8					;
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	��~�s���̒��O�̒i����葬�x�ɂȂ�Ȃ��B***
;	***	�p�x�Ԋۂ�SET				***
;	***	BIT1					***
;	***						***
;	***************************************************
_AGL_LMT_BIT_ON
	SUB_START
	MOV.W	@R8,R0					;
	OR	#_BT_AGL_LMT,R0				;�p�x�Ԋ��ޯ�
	MOV.W	R0,@R8					;
	SUB_END
	M_RTS








;	*******************************************
;	***					***
;	***					***
;	***	�߂葬�x�w��ُ�		***
;	***	�߂�1�O�p�x�w��ُ�		***
;	***	2015-07-07			***
;	***	[h2w 2015-05-15~]		***
;	***					***
;	*******************************************
;	<>234.0,234.1�M��=0,��=0,�s������=0 [���],�ӂ肱]
;	<>234.0,234.1�M��=*,��=*,�s������=* [��]-�i��,���_,�A��,����,����]
;	�^�]Ӱ�ނ̔���ͼ��ݽ�ɂčs��
;	ؾ�Ē���OFF����
;
;
;
;;;;;	_PVP_CKSPD_LMBIT	;
;;;;;	_PVP_CKSPD_STEP		;���x�ЯđΏۍs�� 0:���� 1:1�ȏ�̍s��,,,10(10�s���Ɩ߂�),11(�߂�)
;;;;;
;;[1]�^�]���� ��],���],�U�q
;;

	.IMPORT	_WORD_BIT_TBL0	;


_SPD_POS_SET_ERRCHK1
	SUB_START

	MOV.L	#_SET1_MRTION_SEL1,R1		;[_SEQ_DP_TOP+50*2]
	MOV.W	@R1,R0				;
	TST	#_DMATH_CNTROT,R0		;
	TST_BIT_ON SPD_SET_ERCK1_020		;��]

;	---- ���],�U�q -----
	FAR_JSR	#_SPD_CKSIG_ALL_CLR,R0		;
	M_BRA	SPDPOS_SET_ERCK1_END		;

SPD_SET_ERCK1_020				;

;R7:234,0/234.1
;R8:�����Ώۍs��

;	-------------------------------------------------------------------
;	---		���x�ُ̈팟�m�����J�n				---
;	-------------------------------------------------------------------
	MOV.L	#(_PAR_MODORI_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R6							;1%(R6��0.1%�ް��ł��̊֐��Ԃ�KEEP)
	TST	R6,R6							;
	TST_BIT_ON SPD_SET_ERCK1_100					;��������

;	----���x��������-----
	FAR_JSR	#_SPD_CKSIG_ALL_CLR,R0					;
	M_BRA	SPDPOS_SET_ERCK1_END					;


;	-------------------------------------------------------------------
;	---	�߂�s�����x���� INPUT R6(���x1%�ް�),R7(�ُ�ANS=0)	---
;	-------------------------------------------------------------------
;	R7:���ݽ�ւُ̈�E�x��o��
;	R8:�ُ팟�o�s��
;
SPD_SET_ERCK1_100
	XOR	R7,R7							;
	MOV.L	#_WK_PVP_MOT_STS+(_EQ_MODORI_INFO-1)*2,R8		;�߂�s��TOP+(100-1)
	REG_MUL10 DAT_REG=R6,WKREG1=R0			;ROM���=R6 0.1%

	FAR_JSR	#_SPD_STP_BIT_ON,R0			;�߂�s���͏�ɓ��͐��������s��


	MOV.L	#_SVP_UPAREA_SPD0,R1			;�ߑ��x
	MOV.W	@R1,R2					;0.1%~100.0%
	CMP/HS	R6,R2					;R6(ROM���*10)
	BT	SPD_SET_ERCK1_200			;ROM <= SV_SPD THEN OK
	MOV.W	#BIT0,R0				;
	OR	R0,R7					;234.0:ERR-SET

	FAR_JSR	#_SPD_LLL_BIT_ON,R0			;INPUT R8(�ە\���ޯ�SET)
	M_BRA	SPD_SET_ERCK1_220			;

SPD_SET_ERCK1_200:					;
							;OFF
SPD_SET_ERCK1_220:					;


	MOV.L	#_SET1_OVERLIDE_COF,R0			;
	MOV.W	@R0,R1					;����ײ�ޔ䗦
	MOV.W	#_OVRLIDE_LATE_MAX,R4				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;R2(�߂葬�x)*����ײ��

	CMP/HS	R6,R2					;R6(ROM���*10)
	BT	SPD_SET_ERCK1_300			;ROM <= SV_SPD' THEN OK
	MOV.W	#BIT1,R0				;
	OR	R0,R7					;234.1:ALM-SET
SPD_SET_ERCK1_300:					;


;	-------------------------------------------------------------------
;	---		�p�x�ُ̈팟�m�����J�n				---
;	-------------------------------------------------------------------
	MOV.L	#(_PAR_LAST_MAXDIG-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R6							;1�x
	TST	R6,R6							;
	TST_BIT_ON POS_SET_ERCK1_100					;
									;
	FAR_JSR	#_SPD_CKSIG_SET1,R0					;�p�x�ł������͖���:�߂�s���̂������Ώ�
									;���ݽ�֏o��
	M_BRA	SPDPOS_SET_ERCK1_END					;


;	---------------------------------------------------------------------------
;	---	�p�x���� INPUT R6(1�x�ް�:��ݸ),R7(�ُ�ANS input BIT0,BIT1)	---
;	---------------------------------------------------------------------------
;	�߂�s���͕]���ς� �߂�P�O�s���i�s���̑傫���ق��j����]��,��~�s��������ΏI��
;
;	ANS R7:234.0(ERR) 234.1(ALM) 
;	ANS R8:�]�����ׂ��s��----->�ð�����ڽ BIT3(�]���E�ЯĂ��ׂ��s��),BIT2(�ە\��)
;	ANS R9:��--------------->���g�p
;	
;
;
POS_SET_ERCK1_100
	REG_MUL10	DAT_REG=R6,WKREG1=R0			;ROM���=R6 0.1�x

	MOV.L	#_SETX_POS_STEP_MAX,R1				;//�ݒ�=1~10(2~11)
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_OF POS_SET_ERCK1_400				;

	MOV	R0,R3						;LOOP-CNT(R3)
	ADD	#-1,R0
	SHLL	R0						;*2 BYTE
	MOV.L	#_WK_PVP_MOT_STS,R8				;�o�͐�
	ADD	R0,R8						;
	MOV.L	#_SVPX1_OBJECT_DIG_TOP,R10			;
	ADD	R0,R10						;
	MOV.L	#_SVPX1_OBJECT_TIM_TOP,R11			;01�i�ڒ�~����
	ADD	R0,R11						;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R12			;01�i�ڈړ����x
	ADD	R0,R12						;
	MOV.L	#H'7FFFFFFF,R2					;�����l:R2=MAX�p�x

	MOV.L	#(_PAR_MODORI_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R13							;1%(R13��0.1%�ް��ł��̊֐��Ԃ�KEEP)
	REG_MUL10 DAT_REG=R13,WKREG1=R0					;ROM���=R13 0.1%


POS_SET_ERCK1_150LOP

	MOV.W	@R11,R1						;TIMER
	TST	R1,R1						;
	TST_BIT_ON POS_SET_ERCK1_400				;��~�L��[EXIT]

	MOV	R2,R1						;
	MOV.W	@R10,R2						;0.1�x�ް�
	CMP/HI	R1,R2						;R1 < R2(�߂���)
	BT	POS_SET_ERCK1_400				;��~�L��

	MOV	R3,R0						;
	CMP/EQ	#1,R0						;1�s��?
	BT	POS_SET_ERCK1_160				;YES

	MOV	R10,R4						;
	ADD	#-2,R4						;
	MOV.W	@R4,R4						;
	CMP/HI	R2,R4						;R2(2�i��)<R4(1�i��):
	BT	POS_SET_ERCK1_400				;����t�]�ł�


POS_SET_ERCK1_160

	CMP/HS	R2,R6						;R2<=R6 NOMAL
	BT	POS_SET_ERCK1_400				;POS<=ROM THEN OK(����������Ⴂ�i���̓`�F�b�N�s�v)

;	-----�]���Ώۍs��[BIT3] ���͎�HMI���Я�------
;;;	OR	R14,R8						;
	FAR_JSR	#_SPD_STP_BIT_ON,R0				;��ʓ��͂𐧌�����s��->HMI

;	----------------------
	MOV.W	@R12,R1						;���x
	CMP/HS	R13,R1						;�ŏ��l(R13)=< R1
	BT	POS_SET_ERCK1_170				;

;	-----�]�����ʐ�[BIT2]------
;;;;;	OR	R14,R9						;
	FAR_JSR	#_SPD_LLL_BIT_ON,R0				;�����s���ő��x���Ⴂ(�ە\���ޯ�SET)
	MOV.W	#BIT0,R0					;
	OR	R0,R7						;234.0
	M_BRA	POS_SET_ERCK1_180				;

POS_SET_ERCK1_170:					;
							;OFF
POS_SET_ERCK1_180:					;

	PUSH_REG1 R2
	MOV.L	#_SET1_OVERLIDE_COF,R0				;
	MOV.W	@R0,R2						;����ײ�ޔ䗦
	MOV.W	#_OVRLIDE_LATE_MAX,R4				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;R1(�߂葬�x)*����ײ��(R2)
	
	CMP/HS	R13,R2						;�ŏ��l(R13)=< R1
	BT	POS_SET_ERCK1_190				;

;	-----�]�����ʵ���ײ��------
	MOV.W	#BIT1,R0					;
	OR	R0,R7						;234.1�@WARINING

POS_SET_ERCK1_190						;
	POP_REG1 R2


POS_SET_ERCK1_200:						;
;;;;;	SHLR	R14						;
	ADD	#-1,R3						;cnt
	ADD	#-2,R10						;�p�x
	ADD	#-2,R11						;���
	ADD	#-2,R12						;���x
	ADD	#-2,R8						;�ð��

	TST	R3,R3
	TST_BIT_OF POS_SET_ERCK1_400				;
	M_BRA	POS_SET_ERCK1_150LOP				;


POS_SET_ERCK1_400:						;

	FAR_JSR	#_SPD_CKSIG_SET1,R0				;234.0/234.1�̌��ʂ��o��



SPDPOS_SET_ERCK1_END:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	���x�ŏ��ȉ��@�ۂ�SET/CLR	***
;	***	BIT2				***
;	***					***
;	*******************************************
_SPD_LLL_BIT_ON
	SUB_START
	MOV.W	@R8,R0					;
	OR	#_BT_SPD_LLL,R0				;���ޯ�
	MOV.W	R0,@R8					;
	SUB_END
	M_RTS

;;;;;;;_SPD_LLL_BIT_OF
;;;;;;;	SUB_START
;;;;;;;	MOV.W	@R8,R0					;
;;;;;;;	AND	#LOW ~_BT_SPD_LLL,R0			;���ޯ�CLR
;;;;;;;	MOV.W	R0,@R8					;
;;;;;;;	SUB_END
;;;;;;;	M_RTS


;
;
;	*******************************************
;	***					***
;	***	��ʓ��͂̐����s����SET/CLR	***
;	***	BIT3				***
;	***					***
;	*******************************************
_SPD_STP_BIT_ON
	SUB_START
	MOV.W	@R8,R0					;
	OR	#_BT_SPD_STP,R0				;HMI�Őݒ��ЯĂ��ׂ��s����
	MOV.W	R0,@R8					;
	SUB_END
	M_RTS

;;;;;;;_SPD_STP_BIT_OF
;;;;;;;	SUB_START
;;;;;;;	MOV.W	@R8,R0					;
;;;;;;;	AND	#LOW ~_BT_SPD_STP,R0			;
;;;;;;;	MOV.W	R0,@R8					;
;;;;;;;	SUB_END
;;;;;;;	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
_SPD_CKSIG_ALL_CLR
	SUB_START

;	-------- 2015-08-19----------
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB234,LG=W,BIT=~(BIT3+BIT2+BIT1+BIT0),WKRG1=R1,WKRG2=R4

;;;;;;;;;;;;;;;	------------- ���L�͖��g�p�ɂȂ���(2015-10-23)
;;;;;;;;;;;;;;;	XOR	R0,R0				;
;;;;;;;;;;;;;;;	MOV.L	#_PVP_CKSPD_LMBIT,R1		;
;;;;;;;;;;;;;;;	MOV.W	R0,@R1				;
;;;;;;;;;;;;;;;	MOV.L	#_PVP_CKSPD_STPBT,R1		;���x�ЯđΏۍs�� BIT0~BIT9,BIT15(�����Ώۍs��)
;;;;;;;;;;;;;;;	MOV.W	R0,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	HMI�ɂ͐ۈʒu�Ɠ��͉�����������ӏ���������
;
_SPD_CKSIG_SET1
	SUB_START

;	--------- 2015-08-19-----------
	MOV.W	#(BIT3+BIT2+BIT1+BIT0),R4
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB234,R1	;���ۂ̎d�l��BIT0,BIT1����BIT2,BIT3��\��
	MOV.W	@R1,R0				;
	AND	R4,R7				;
	NOT	R4,R4
	AND	R4,R0				;
	OR	R0,R7
	MOV.W	R7,@R1				;


;;;;;;;;;;;;;;;	------------- ���L�͖��g�p�ɂȂ���(2015-10-23)
;;;;;;;;;;;;;;;	MOV.L	#_PVP_CKSPD_STPBT,R1		;���x�ЯđΏۍs�� BIT0~BIT9,BIT15(�����Ώۍs��)
;;;;;;;;;;;;;;;	MOV.W	R8,@R1				;
;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;	MOV.L	#_PVP_CKSPD_LMBIT,R1
;;;;;;;;;;;;;;;	MOV.W	R9,@R1				;

	SUB_END
	M_RTS

