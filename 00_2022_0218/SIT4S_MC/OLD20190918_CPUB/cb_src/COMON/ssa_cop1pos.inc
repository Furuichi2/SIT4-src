;	***********************************
;	***				***
;	***	�߼޼�œ���		***
;	***				***
;	***********************************
;	cpua����
;
;	�@"�����޲ʲĽ���":�蓮�޲ʲĂƓ��ꉉ�Z�ɂ��޲ʲĈʒu��\������
;	�A�ʒu��r
;
;	341.9
	.IMPORT		_SVP_ATSLID_OBJ1	; �X���C�h�������ߐݒ�l�i���ݓ��쒆�j0.001mm
	.IMPORT		_SVP_ATSLID_DNOBJ1	; �X���C�h�������߁@���~��~ 0~99
	.IMPORT		_SVP_ATSLID_UPOBJ1	; �X���C�h�������߁@�㏸��~ "
	.IMPORT		_SVP_ATSLID_BAKLNG	; �X���C�h�������߁@�߂��   "
	.IMPORT		_SVP_ATSLID_COEF1	; �X���C�h�������߁@���䐸�x "
	.IMPORT		_SVP_SLPOS_DIR		;�ʒu���ߕ��� 0(�㏸)/1(���~)
	.IMPORT		_SVP_SL_TENPOS		;�����_


	.EXPORT	_POSITIONER_DAIHAITO
_POSITIONER_DAIHAITO
	SUB_START

	MOV.L	#_POSINER_FLG,R5		;
	MOV.W	@R5,R0				;
	TST	R0,R0				;
	TST_BIT_ON POSITIONER_DAICTL_100	;

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341.9
	MOV.W	@R1,R0				;
	MOV.W	#BIT9,R4			;
	TST	R4,R0				;
	TST_BIT_ON POSITIONER_DAICTL_020	;
	M_BRA	POSITIONER_DAICTL_EXT		;

;	-------------- �N��-----------------
POSITIONER_DAICTL_020
	MOV.B	#BIT0,R0			;
	MOV.W	R0,@R5				;FLG.0=1

;	------------------------------------
	XOR	R0,R0				;
	MOV.L	#_POSINER_RETRY_CNT,R1		;
	MOV.W	R0,@R1				;


	MOV.B	#BIT1,R0			;�㏸�����+�ʒu���ߒ�
	MOV.L	#_SVP_SLPOS_DIR,R1		;�ʒu���ߕ���
	MOV.W	@R1,R4				;
	TST	R4,R4				;
	TST_BIT_OF POSITIONER_DAICTL_040	;
	MOV.B	#BIT6+BIT1,R0			;���~�����+�ʒu���ߒ�
POSITIONER_DAICTL_040:
	MOV.L	#_POSINER_STS,R1		;BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MOV.W	R0,@R1				;
	FAR_JSR	#_POSITIONER_DAI_DATA,R0
	M_BRA	POSITIONER_DAICTL_800



;	----------------------------------------------
POSITIONER_DAICTL_100

	MOV.L	#_PVX_DAI_POS1,R1		;�޲ʲĕ\���l�E����l
	MOV.L	@R1,R2				;SAVE R2 -->NEXT CALC USED
	MOV.L	#_POSINER_PV_POS,R1		;//�ڕW�ʒu
	MOV.L	R2,@R1				;

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341.9
	MOV.W	@R1,R2				;
	MOV.W	#BIT9,R4			;
	TST	R4,R2				;
	TST_BIT_ON POSITIONER_DAICTL_200	;

;	--------------- �w��OFF �I��---------------
	XOR	R0,R0				;
	MOV.L	#_POSINER_FLG,R5		;
	MOV.W	R0,@R5				;
	MOV.L	#_POSINER_STS,R1		;
	MOV.W	R0,@R1				;
	M_BRA	POSITIONER_DAICTL_800

;	-------------- �^�]--------------------
POSITIONER_DAICTL_200
	MOV.L	#_POSINER_FLG,R5		;
	MOV.W	@R5,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON POSITIONER_DAICTL_300	;

;	------- �������Z--------
	FAR_JSR	#_POSITIONER_DAI_OBJ1MAK,R0				;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	M_BRA	POSITIONER_DAICTL_800

;	----------------------------------------
POSITIONER_DAICTL_300
	TST	#BIT2,R0			;
	TST_BIT_ON POSITIONER_DAICTL_400	;

	FAR_JSR	#_POSITIONER_DAI_OBJ1CMP,R0	;//�ڕW�ʒu+���ޗ�
	PUSH_REG1 R0				;
	FAR_JSR	#_POSITIONER_DAI_OUT,R1		;input R0
	POP_REG1 R0
	TST	R0,R0
	TST_BIT_ON POSITIONER_DAICTL_350
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_FLG,LG=W,BIT=BIT2,WKREG=R1	;
POSITIONER_DAICTL_350
	M_BRA	POSITIONER_DAICTL_800


;	----------------------------------------
POSITIONER_DAICTL_400
	TST	#BIT3,R0			;
	TST_BIT_ON POSITIONER_DAICTL_500	;
	FAR_JSR	#_POSITIONER_DAI_OBJ2CMP,R0	;//�ڕW�ʒu+���ޗ�-���ׂ�
	PUSH_REG1 R0				;
	FAR_JSR	#_POSITIONER_DAI_OUT,R1		;input R0
	POP_REG1 R0
	TST	R0,R0
	TST_BIT_ON POSITIONER_DAICTL_450
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_FLG,LG=W,BIT=BIT3,WKREG=R1	;


	MOV.L	#_POSINER_STOPCHK_TIM1,R1;//1000 1�b
	MOV.W	#D'1000,R2		;
	MOV.W	R2,@R1			;
	MOV.L	#_POSINER_STOPCHK_TIM2,R1;//1000 1�b
	MOV.W	R2,@R1			;


	MOV.L	#_POSINER_PV_POS,R1	;
	MOV.L	@R1,R2			;
	MOV.L	#_POSINER_OLDPV_POS,R1	;
	MOV.L	R2,@R1			;
	MOV.L	#_POSINER_MOSTPV_POS,R1	;//�w��OFF��̲��߼޼�݂ɂ����Ƃ��߂��ʒu
	MOV.L	R2,@R1			;

POSITIONER_DAICTL_450
	M_BRA	POSITIONER_DAICTL_800


;	-------------- ��~�҂�------------------
POSITIONER_DAICTL_500
	TST	#BIT4,R0			;
	TST_BIT_ON POSITIONER_DAICTL_800	;

	FAR_JSR	#_POSITIONER_DAI_STPCHK,R1	;
	TST	R0,R0				;
	TST_BIT_OF POSITIONER_DAICTL_590	;"R0=1 END R0=-1 END(���s)

	CMP/EQ	#1,R0				;
	BF	POSITIONER_DAICTL_530		;

;	����I��
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_FLG,LG=W,BIT=BIT4,WKREG=R1	;

;	�ʒu���ߊ���ON
;	BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_POSINER_STS,LG=W,BIT=(~(BIT4|BIT3|BIT1)),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_STS,LG=W,BIT=BIT0,WKREG=R1	;
	M_BRA	POSITIONER_DAICTL_800


POSITIONER_DAICTL_530
;	�ُ�I��
	MOV.L	#_POSINER_RETRY_CNT,R1
	MOV.W	@R1,R2
	ADD	#1,R2
	MOV.W	R2,@R1
	MOV.B	#3,R4
	CMP/HS	R2,R4			;
	BT	POSITIONER_DAICTL_550	;R2=<R4(3) ��ײ(�ʏ�+��ײ3��=4��܂ł��)

;	�ُ�I��
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_FLG,LG=W,BIT=BIT4,WKREG=R1	;
;	�ُ튮��ON
;	BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_POSINER_STS,LG=W,BIT=(~(BIT4|BIT3|BIT1)),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSINER_STS,LG=W,BIT=BIT2,WKREG=R1	;
	M_BRA	POSITIONER_DAICTL_800

;	----------------��ײ�J�n-----------
POSITIONER_DAICTL_550
	MOV.B	#BIT0,R0			;
	MOV.L	#_POSINER_FLG,R1		;
	MOV.W	R0,@R1				;������

POSITIONER_DAICTL_590
	M_BRA	POSITIONER_DAICTL_800



;	-----------------------------------
POSITIONER_DAICTL_800





	MOV.L	#_POSINER_STS,R1			;
	MOV.W	@R1,R0					;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB251,R1		;251
	MOV.W	@R1,R2					;
	MOV.W	#(BIT5+BIT4+BIT3+BIT2+BIT1+BIT0),R4	;
	AND	R4,R0
	NOT	R4,R4
	AND	R4,R2
	OR	R0,R2
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB251,R1		;251
	MOV.W	R2,@R1					;





POSITIONER_DAICTL_EXT

	SUB_END
	M_RTS


;_SVP_KANDO_A21				.SRES	4	;���x
;_SVP_UPDATA_A21			.SRES	4	;���
;_SVP_DNDATA_A21			.SRES	4	;����
;_SVP_GENITI_A21			.SRES	4	;���ʒu
;_SVP_MODORI_A21			.SRES	2	;�߂��
;_SVP_DNSTOP_A21			.SRES	2	;���~��~
;_SVP_UPSTOP_A21			.SRES	2	;�㏸��~
;_SVP_SSEIDO_A21			.SRES	2	;���䐸�x


;_SVP_SLID_POS1		.SRES	4	;�ײ�ވʒu�@���Y
;_SVP_SLID_POS2		.SRES	4	;�ײ�ވʒu�@�i��1
;_SVP_SLID_POS3		.SRES	4	;�ײ�ވʒu�@�i��2
;
;	***********************************************************
;	***							***
;	***	[�㏸����J�n]					***
;	***	�ݒ�+�߂��(���݈ʒu�{�߂��)			***
;	***	�ݒ�+�߂��-���~��(���݈ʒu�{�߂��-���~��)	***
;	***							***
;	***********************************************************

_POSITIONER_DAI_OBJ1MAK:
	SUB_START

	MOV.L	#_POSINER_SV_POS,R1		;//�ڕW�ʒu
	MOV.L	@R1,R2				;

	MOV.L	#_POSINER_RETRY_CNT,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF POSITIONER_DAIOBJ1MK_100	;

	MOV.L	#_POSINER_PV_POS,R1		;
	MOV.L	@R1,R2				;[R5�ڕW�ʒu]

POSITIONER_DAIOBJ1MK_100:

;	in R2

	MOV.L	#_POSINER_STS,R1		;BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;����
	TST_BIT_ON POSITIONER_DAIOBJ1MK_200	;

;	---------- �㏸����J�n-----------
	MOV.L	#_SET1_ATSLID_BAKLNG,R1		;//�X���C�h�������߁@�߂��   "
	MOV.L	@R1,R3				;0.001mm(ADD)

	MOV.L	#_SET1_ATSLID_DNOBJ1,R1		;//�X���C�h�������߁@���~��~ 0~99
	MOV.L	@R1,R4				;0.001mm
	M_BRA	POSITIONER_DAIOBJ1MK_300


POSITIONER_DAIOBJ1MK_200:
;	------- ���~����J�n -------------
	MOV.L	#_SET1_ATSLID_BAKLNG,R1		;//�X���C�h�������߁@�߂��   "
	MOV.L	@R1,R3				;0.001mm(ADD)
	NEG	R3,R3

	MOV.L	#_SET1_ATSLID_UPOBJ1,R1		;//�X���C�h�������߁@�㏸��~ 0~99
	MOV.L	@R1,R4				;0.001mm
	NEG	R4,R4				;

POSITIONER_DAIOBJ1MK_300:


	ADD	R3,R2				;
	FAR_JSR	#_POSITIONER_UPDN_LIMIT,R0	;


;	-------------��~�ʒu�͈��--------------
	MOV.L	#_POSINER_SV_OVRPOS,R1		;//�ڕW�ʒu+���ޗ�
	MOV.L	R2,@R1				;


	MOV.L	#_POSINER_SV_POS,R1		;//�ڕW�ʒu
	MOV.L	@R1,R2				;

	ADD	R4,R2				;�ڕW+��
	FAR_JSR	#_POSITIONER_UPDN_LIMIT,R0	;
	MOV.L	#_POSINER_SV_STPPOS,R1		;//�ڕW�ʒu+��~��
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS


;	INPU R2,DESTORY R1,R3,ANS R2
_POSITIONER_UPDN_LIMIT
	SUB_START

	MOV.L	#_SET1_RNAPOS_MAXP,R1	;19�@�B����@�B ?0.001mm
	MOV.L	@R1,R3			;UP
	CMP/GE	R2,R3			;
	BT	POSITIONER_UPDNLMT100	;R2(SV)=<R3(MAX) OK
	MOV	R3,R2			;
POSITIONER_UPDNLMT100			;

	MOV.L	#_SET1_RNAPOS_MINP,R1	;1A �@�B�����@�B
	MOV.L	@R1,R3			;DN
	CMP/GE	R3,R2			;
	BT	POSITIONER_UPDNLMT200	;R3(MIN)=<R2(MAX) OK
	MOV	R3,R2			;
POSITIONER_UPDNLMT200			;

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�ݒ�f�[�^��0.001mm�ɂ���	***
;	***					***
;	*******************************************
_POSITIONER_DAI_DATA
	SUB_START

	MOV.L	#_SVP_SL_TENPOS,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_SET1_ATDAT_DOTPOS,R1		;//�����_
	MOV.W	R0,@R1				;

	MOV.W	#D'1,R3				;LATE
	CMP/EQ	#3,R0
	BT	POSITIONER_DAIDAT_100		;�����_3��

	MOV.W	#D'10,R3			;
	CMP/EQ	#2,R0
	BT	POSITIONER_DAIDAT_100		;�����_2��

	MOV.W	#D'100,R3			;
	CMP/EQ	#1,R0
	BT	POSITIONER_DAIDAT_100		;�����_1��

	MOV.W	#D'1000,R3			;�����_����

POSITIONER_DAIDAT_100				;


	MOV.L	#_SVP_ATSLID_DNOBJ1,R1		; �X���C�h�������߁@���~��~ 0~99
	MOV.W	@R1,R2				;
	DMULS.L	R2,R3				;
	STS.L	MACL,R2				;
	MOV.L	#_SET1_ATSLID_DNOBJ1,R1		;//�X���C�h�������߁@���~��~ 0~99
	MOV.L	R2,@R1				;0.001mm

	MOV.L	#_SVP_ATSLID_UPOBJ1,R1		; �X���C�h�������߁@�㏸��~ "
	MOV.W	@R1,R2				;
	DMULS.L	R2,R3				;
	STS.L	MACL,R2				;
	MOV.L	#_SET1_ATSLID_UPOBJ1,R1		;//�X���C�h�������߁@�㏸��~ "
	MOV.L	R2,@R1				;0.001mm

	MOV.L	#_SVP_ATSLID_BAKLNG,R1		; �X���C�h�������߁@�߂��   "
	MOV.W	@R1,R2				;
	DMULS.L	R2,R3				;
	STS.L	MACL,R2				;
	MOV.L	#_SET1_ATSLID_BAKLNG,R1		;//�X���C�h�������߁@�߂��   "
	MOV.L	R2,@R1				;0.001mm

	MOV.L	#_SVP_ATSLID_COEF1,R1		; �X���C�h�������߁@���䐸�x "
	MOV.W	@R1,R2				;
	DMULS.L	R2,R3				;
	STS.L	MACL,R2				;
	MOV.L	#_SET1_ATSLID_COEF1,R1		;
	MOV.L	R2,@R1				;0.001mm


	MOV.L	#_SVP_ATSLID_OBJ1,R1		; �X���C�h�������ߐݒ�l�i���ݓ��쒆�j0.001mm
	MOV.L	@R1,R2				;0.001mm
	MOV.L	#_POSINER_SV_POS,R1		;//�ڕW�ʒu0.001mm
	MOV.L	R2,@R1				;


	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		�߂�ʒu��r		***
;	***					***
;	*******************************************
_POSITIONER_DAI_OBJ1CMP:
	SUB_START


	MOV.L	#_POSINER_PV_POS,R1		;//�ڕW�ʒu
	MOV.L	@R1,R2				;

	MOV.L	#_POSINER_SV_OVRPOS,R1		;//�ڕW�ʒu+���ޗ�
	MOV.L	@R1,R3				;

	MOV.L	#_POSINER_STS,R1		;BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;����
	TST_BIT_ON POSITIONER_DAI_OBJ1CP_100	;

;	�㏸
	CMP/GE	R3,R2				;SV(R3)=<PV(R2)?
	BT POSITIONER_DAI_OBJ1CP_OVR		;YES
	M_BRA	POSITIONER_DAI_OBJ1CP_WATUP	;

POSITIONER_DAI_OBJ1CP_100:

;	���~
	CMP/GE	R2,R3				;PV(R2)=<SV(R3)?
	BT POSITIONER_DAI_OBJ1CP_OVR		;YES
	M_BRA	POSITIONER_DAI_OBJ1CP_WATDN	;



POSITIONER_DAI_OBJ1CP_WATUP:
	MOV.B	#1,R0
	M_BRA	POSITIONER_DAI_OBJ1CP_END	

POSITIONER_DAI_OBJ1CP_WATDN:
	MOV.B	#-1,R0
	M_BRA	POSITIONER_DAI_OBJ1CP_END	
	
POSITIONER_DAI_OBJ1CP_OVR:
	XOR	R0,R0				;
POSITIONER_DAI_OBJ1CP_END:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***		�w��OFF�ʒu��r		***
;	***					***
;	*******************************************
_POSITIONER_DAI_OBJ2CMP:
	SUB_START


	MOV.L	#_POSINER_PV_POS,R1		;//�ڕW�ʒu
	MOV.L	@R1,R2				;

	MOV.L	#_POSINER_SV_STPPOS,R1		;//�ڕW�ʒu+��ʗ�-���~��
	MOV.L	@R1,R3				;

	MOV.L	#_POSINER_STS,R1		;BIT0(����),BIT1(�ʒu���ߒ�),BIT2(���s),BIT3(�㏸),BIT4(���~), BIT6:(DIR)
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;����
	TST_BIT_ON POSITIONER_DAI_OBJ2CP_100	;

;	�㏸����J�n�̉��~��
	CMP/GE	R2,R3				;PV(R2)=<SV(R3)?
	BT POSITIONER_DAI_OBJ2CP_STP		;YES
	M_BRA	POSITIONER_DAI_OBJ2CP_WATDN	;

POSITIONER_DAI_OBJ2CP_100:

;	���~����J�n�̏㏸��
	CMP/GE	R3,R2				;SV(R3)=<PV(R2)?
	BT POSITIONER_DAI_OBJ2CP_STP		;YES
	M_BRA	POSITIONER_DAI_OBJ2CP_WATUP	;



POSITIONER_DAI_OBJ2CP_WATUP:
	MOV.B	#1,R0
	M_BRA	POSITIONER_DAI_OBJ2CP_END	
POSITIONER_DAI_OBJ2CP_WATDN:
	MOV.B	#-1,R0				;
	M_BRA	POSITIONER_DAI_OBJ2CP_END	
	
POSITIONER_DAI_OBJ2CP_STP:
	XOR	R0,R0
POSITIONER_DAI_OBJ2CP_END:

	SUB_END
	M_RTS



_POSITIONER_DAI_OUT:
	SUB_START
	
	XOR	R2,R2		;��~

	TST	R0,R0
	TST_BIT_OF POSITIONER_DAIOUT_100

	MOV.B	#BIT3,R2
	CMP/EQ	#1,R0
	BT	POSITIONER_DAIOUT_100

	MOV.B	#BIT4,R2

POSITIONER_DAIOUT_100:
	MOV.L	#_POSINER_STS,R1
	MOV.W	@R1,R0	
	AND	#LOW ~(BIT4+BIT3),R0
	OR	R2,R0
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***		��~�҂�		***
;	***					***
;	*******************************************
;	��{�͂P�b�ԓ��삵�Ȃ��Ȃ��āA�C���|�W���ɂ��邩
;	R0=0(���쒆) R0=1(��~�@���߼�OK) R0=-1(��~,���߼ވُ�)
;	�E��������̈ʒu���P�b�ԍX�V����Ȃ������Ƃ�
;		MOV.L	#_POSINER_STOPCHK_TIM1,R1;//1000 1�b
;	�E0.01mm�̈ړ���1�b�Ԗ���
_POSITIONER_DAI_STPCHK:
	SUB_START

	MOV.L	#_POSINER_PV_POS,R1	;
	MOV.L	@R1,R2			;

	MOV.L	#_POSINER_MOSTPV_POS,R5	;//�w��OFF��̲��߼޼�݂ɂ����Ƃ��߂��ʒu
	MOV.L	@R5,R4				;

	MOV.L	#_POSINER_STS,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;���� 0:���~(����)�ŏI��
	TST_BIT_ON POSITIONER_DAI_STPCK100	;

	CMP/GE	R4,R2				;�ŉ��ʒu(R4)=<���݈ʒu(R2)
	BT	POSITIONER_DAI_STPCK200		;OK
	M_BRA	POSITIONER_DAI_STPCK150		;�ړ�����


POSITIONER_DAI_STPCK100:
	CMP/GE	R2,R4				;���݈ʒu(R2)=<�ŏ�ʒu(R4)
	BT	POSITIONER_DAI_STPCK200		;OK
POSITIONER_DAI_STPCK150:			;

	MOV.L	R2,@R5				;�ŉ��ʒu(�ŏ�ʒu)�X�V:������

	MOV.W	#D'1000,R0
	MOV.L	#_POSINER_STOPCHK_TIM1,R1	;
	MOV.W	R0,@R1
	MOV.L	#_POSINER_STOPCHK_TIM2,R1	;
	MOV.W	R0,@R1


POSITIONER_DAI_STPCK200:
	MOV.L	#_POSINER_STOPCHK_TIM1,R4
	MOV.W	@R4,R0
	TST	R0,R0
	TST_BIT_OF POSITIONER_DAI_STPCK250		;
	ADD	#-1,R0
	MOV.W	R0,@R4					;
	TST	R0,R0					;
	TST_BIT_ON POSITIONER_DAI_STPCK230
	MOV.L	#_POSINER_OLDPV_POS,R1			;
	MOV.L	R2,@R1					;R2(NOW),R3(OLD)
POSITIONER_DAI_STPCK230:
	M_BRA	POSITIONER_DAI_STPCKWAT			;


POSITIONER_DAI_STPCK250:
;	---FIRST���OK---
	MOV.L	#_POSINER_OLDPV_POS,R5
	MOV.L	@R5,R3			;R2(NOW),R3(OLD)
	SUB	R2,R3			;
	CMP/PZ	R3			;
	BT	POSITIONER_DAI_STPCK280	;
	NEG	R3,R3			;
POSITIONER_DAI_STPCK280:		;
	MOV.W	#D'10,R0
	CMP/HI	R3,R0			;R3<R0(10 0.01mm)
	BT	POSITIONER_DAI_STPCK300	;

;	------------- 0.01mm������------------
	MOV.L	R2,@R5				;�O��ʒu�X�V
	MOV.W	#D'1000,R0			;
	MOV.L	#_POSINER_STOPCHK_TIM2,R1	;
	MOV.W	R0,@R1				;

POSITIONER_DAI_STPCK300:			;


	DN_TIME LG=W,MEM_ADR=_POSINER_STOPCHK_TIM2,WKREG1=R1,WKREG2=R4	;10msec �����

	MOV.L	#_POSINER_STOPCHK_TIM2,R4
	MOV.W	@R4,R0
	TST	R0,R0
	TST_BIT_ON POSITIONER_DAI_STPCKWAT		;


;	��~�I��,���߼޼��
	MOV.L	#_POSINER_PV_POS,R1		;
	MOV.L	@R1,R2				;
	MOV.L	#_POSINER_SV_POS,R1		;//�ڕW�ʒu
	MOV.L	@R1,R3				;
	SUB	R2,R3				;
	CMP/PZ	R3			
	BT	POSITIONER_DAI_STPCK320		;
	NEG	R3,R3
POSITIONER_DAI_STPCK320:			;

	MOV.L	#_SET1_ATSLID_COEF1,R1		;
	MOV.L	@R1,R0				;0.001mm
	CMP/GE	R3,R0				;
	BT	POSITIONER_DAI_STPCKINP		;���߼޼��
	M_BRA	POSITIONER_DAI_STPCKERR		;


POSITIONER_DAI_STPCKWAT:	
	XOR	R0,R0
	M_BRA	POSITIONER_DAI_STPCKEND		;

POSITIONER_DAI_STPCKERR:			;
	MOV.B	#-1,R0				;
	M_BRA	POSITIONER_DAI_STPCKEND		;

POSITIONER_DAI_STPCKINP:			;
	MOV.B	#1,R0				;

POSITIONER_DAI_STPCKEND:

	SUB_END
	M_RTS

