;	*******************************************
;	***					***
;	***	�^�]�����޲ʲĕ␳���Z		***
;	***	�V�\�t�g			***
;	*******************************************
;	***********************************
;	***				***
;	***	�_�C�n�C�g�␳		***
;	***	�����ݸ޲Ƽ��		***
;	***				***
;	***********************************
	.EXPORT	_DAT_MOSTPOS_SIG_CLR	;(�ُ�ؾ�Ď��̂ݸر)
	.EXPORT	_DAI_MOSTPOS_SMPINI
	.EXPORT	_DAI_MOSTPOS_SMPLE
	.EXPORT	_DAI_MOSTPOS_CMPARE

	.EXPORT	_DAI_FULL_SCALE_SMP_INI	;
	.EXPORT	_DAI_FULL_SCALE_SMPLE	;
	.EXPORT	_DAI_FULL_SCALE_SMP_END	;



	.IMPORT	_RNA_POSMAK_SUB

;	*******************************************
;	****		�ُ��ؾ�Ď�		***
;	*******************************************
_DAT_MOSTPOS_SIG_CLR:
	SUB_START
	XOR	R0,R0
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB211,R4	;
	MOV.W	R0,@R4				;
	XOR	R0,R0
	MOV.L	#_DAI_CMP_SMPSTART,R4		;
	MOV.W	R0,@R4				;
	SUB_END
	M_RTS

;	***********************************
;	***	�������Ă����ݒ背�x��	***
;	***********************************
	.EXPORT	_DAI_DRVHOS_CHK
_DAI_DRVHOS_CHK:
	SUB_START
	MOV.L	#_WPAR_DRVHOS_SEL1,R1		;2003-07-09
	MOV.W	@R1,R0				;
	CMP/EQ	#2,R0				;
	BT	DAI_DRVHOS_CKEXT		;

	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF DAI_DRVHOS_CKEXT		;

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_ON DAI_DRVHOS_CKEXT		;

	FAR_JSR	#_DRVHOS_ALL_INI,R0		;�␳���

DAI_DRVHOS_CKEXT:
	SUB_END
	M_RTS


;	*******************************************
;	****		1CYCLE �J�n		***
;	*******************************************
;	===	1CYCLE�J�n	===
;	��]Ӱ�ށE�����A����A�A���AOPT
;
;
;
;	BIT0:�����ݸޗL��
;	BIT1:WAIT��������:DEF�����ݸޒ�
;	BIT2:DEF����:�ʏ������ݸޒ�
;	BIT3:INI�ž�ā@END�Ÿر�@�Q��END���Ă΂�邱�Ƃ�h��
;	BIT4:�L���Ȉʒu�����o����
;	BIT6:�����ݸޗL����Ӱ�ޏ��(�ÓI)
;
_DAI_MOSTPOS_SMPINI:
	SUB_START

	MOV.L	#_MODE_SEL,R1					;
	MOV.W	@R1,R0						;
	TST	#_W1CNT+_W1SGL+_W1INC+_W1OPT,R0			;
	TST_BIT_OF DAI_DRVHOS_CHK100				;

	MOV.L	#_CPOS_CTL_MATH,R1							;
	MOV.W	@R1,R0									;
;;[20091007���U�q]	TST	#_DMATH_CNTROT,R0							;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;[20091007���U�q]
	TST_BIT_OF DAI_DRVHOS_CHK100							;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_DRVHOS_USE_FLG,LG=W,BIT=BIT6,WKREG=R4		;
	M_BRA	DAI_DRVHOS_CHK200							;
DAI_DRVHOS_CHK100:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_DRVHOS_USE_FLG,LG=W,BIT=~(BIT6+BIT3),WKREG=R4	;
DAI_DRVHOS_CHK200:


;	==================================
	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;�����ݸޗL��Ӱ��?
	TST_BIT_ON DRVHOS_SMP_INI1_050		;
	M_BRA	DRVHOS_SMP_INI1_EXT		;����

DRVHOS_SMP_INI1_050

	TST	#BIT2,R0			;
	TST_BIT_ON DRVHOS_SMP_INI1_300		;�����ް������ݸފ���=�ʏ������ݸޒ�
	TST	#BIT1,R0			;
	TST_BIT_ON DRVHOS_SMP_INI1_200		;WAIT�񐔊���=�����ް��쐬��
	TST	#BIT0,R0			;
	TST_BIT_ON DRVHOS_SMP_INI1_100		;�Ƽ�ي����@�L��

;
	MOV.L	#_WPAR_DRVHOS_SEL1,R1		;2003-07-09
	MOV.W	@R1,R0				;
	CMP/EQ	#2,R0				;
	BT	DRVHOS_SMP_INI1_070		;341.6�Ɋ֌W�Ȃ�

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF DRVHOS_SMP_INI1_EXT		;�␳�� EXIT

DRVHOS_SMP_INI1_070:
;	========== 2003-07-14 ========
	XOR	R0,R0
	MOV.L	#_DRVHOS_IDO_CNT,R1	;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	R0,@R1			;
;	===============================
	MEM1_TO_MEM2 MEM1=_WPAR_DRVHOS_WAITCNT,L1=W,MEM2=_DRVHOS_WAIT_CNT_PV,L2=W,WKREG1=R1,WKREG2=R2
	MEM1_BIT0_TO_BIT7_ORSET MEM=_DRVHOS_USE_FLG,LG=W,BIT=BIT0,WKREG=R4	;bit-set

DRVHOS_SMP_INI1_100

	MOV.L	#_DRVHOS_WAIT_CNT_PV,R1			;
	MOV.W	@R1,R2					;
	TST	R2,R2					;
	TST_BIT_ON DRVHOS_SMP_INI1_END			;

;	=== MODE CHECK ==

	MEM1_BIT0_TO_BIT7_ORSET MEM=_DRVHOS_USE_FLG,LG=W,BIT=BIT1,WKREG=R4	;
	MEM1_TO_MEM2 MEM1=_WPAR_DRVHOS_AVLCNT,L1=W,MEM2=_DRVHOS_DEF_CNT_PV,L2=W,WKREG1=R1,WKREG2=R2	;
	XOR	R2,R2											;
	FAR_JSR	#_DRVHOS_IDO_AVL_INI,R0									;

;	===2003-06-06[1-2]===
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_DRVHOS_USE_FLG,LG=W,BIT=~BIT4,WKREG=R4	;BIT4=0 ����̈斢
	M_BRA	DRVHOS_SMP_INI1_END									;

DRVHOS_SMP_INI1_200:						;WAIT�񐔊���=�����ް������ݸޒ�
	M_BRA	DRVHOS_SMP_INI1_400		;

DRVHOS_SMP_INI1_300:				;�����ް������ݸފ�����=�ʏ������ݸޒ�
	M_BRA	DRVHOS_SMP_INI1_400		;(�I�����ŏ��������)

DRVHOS_SMP_INI1_400:

DRVHOS_SMP_INI1_END
	MEM1_BIT0_TO_BIT7_ORSET MEM=_DRVHOS_USE_FLG,LG=W,BIT=BIT3,WKREG=R4	;�N������
DRVHOS_SMP_INI1_EXT
	SUB_END
	M_RTS


;	***************************
;	***			***
;	***	������		***
;	***			***
;	***************************
;	Input R2
_DRVHOS_IDO_AVL_INI:
	SUB_START
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON DRVHOS_IDO_AVLINI_040	;
	MOV.W	#1,R0
DRVHOS_IDO_AVLINI_040:
	MOV	R0,R4				;data push

	MOV.L	#_DRVHOS_IDO_BUF,R5		;
DRVHOS_IDO_AVLINI_100:
	MOV.L	R2,@R5				;
	ADD	#4,R5				;
	ADD	#-1,R0				;
	TST	R0,R0				;
	TST_BIT_ON DRVHOS_IDO_AVLINI_100	;

	DMULS.L	R4,R2				;
	STS.L	MACL,R2				;
	MOV.L	#_DRVHOS_IDO_TOTAL,R1		;
	MOV.L	R2,@R1				;R2*R4

	XOR	R0,R0
	MOV.L	#_DRVHOS_IDO_POINT,R1		;//�ޯ̧�Ǘ��߲��
	MOV.W	R0,@R1				;

;	==== 2003-07-14 ==
	XOR	R0,R0
	MOV.L	#_DRVHOS_IDO_CNT,R1	;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	R0,@R1			;
;	==================

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	1CYCLE��		***
;	***				***
;	***********************************
;	===	1CYCLE��	===
_DAI_MOSTPOS_SMPLE:
	SUB_START


	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	AND	#(BIT6+BIT3+BIT1+BIT0),R0	;BIT3:�N������
	CMP/EQ	#(BIT6+BIT3+BIT1+BIT0),R0	;
	BT	DRVHOS_SAMPLE1_020		;�L����Ӱ�ނŊ��»����ݸމ\����
	M_BRA	DRVHOS_SAMPLE1_EXT		;

DRVHOS_SAMPLE1_020:				;
;	==== �͈����� ======
	MOV.L	#_CTL_ENC360,R4			;//360.0�x
	MOV.W	@R4,R2				;
	MOV.L	#_WPAR_DRVHOS_DIG1,R4		;//0.1�x(165.0):Ӱ����ݺ��ފp�x�Ŕ�r
	MOV.W	@R4,R1				;START
	MOV.L	#_WPAR_DRVHOS_DIG2,R4		;
	MOV.W	@R4,R3				;
	FAR_JSR	#_DIG_AREA_CHK1,R0		;R1~R3�̒��ɂ��邩
	CMP/PL	R5					;
	BF	DRVHOS_SAMPLE1_EXT		;NO!   R5=0/R5<0

	MOV.L	#_DRVHOS_USE_FLG,R5		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R5,R0				;
	TST	#BIT4,R0			;
	TST_BIT_ON DRVHOS_SAMPLE1_100		;
	OR	#BIT4,R0			;
	MOV.W	R0,@R5				;
	MOV.L	#_RNA_ABS_POS,R1		;
	MOV.L	@R1,R2				;
	MOV.L	#_DRVHOS_MOST_DN_RNAPOS,R1	;//�ŉ����_��WORK(175~359) 175�x����̫�Ă��쐬
	MOV.L	R2,@R1				;
	M_BRA	DRVHOS_SAMPLE1_EXT		;
DRVHOS_SAMPLE1_100:				;
	MOV.L	#_RNA_ABS_POS,R1		;
	MOV.L	@R1,R2				;
	MOV.L	#_DRVHOS_MOST_DN_RNAPOS,R5	;//�ŉ����_��WORK(175~359) 175�x����̫�Ă��쐬
	MOV.L	@R5,R1				;
	CMP/GE	R1,R2				;NOW >= MOST-LOW
	BT	DRVHOS_SAMPLE1_EXT		;
	MOV.L	R2,@R5				;MOST DATA REFLASH
DRVHOS_SAMPLE1_EXT:				;
	SUB_END
	M_RTS

;	***************************
;	***			***
;	***	�ړ�����	***
;	***			***
;	***************************
;	MOV.L	#_DRVHOS_MOST_DN_RNAPOS,R1	;//�ŉ����_��WORK(175~359) 175�x����̫�Ă��쐬
;	MOV.L	@R1,R2				;R2:data
;	MOV.L	#_DRVHOS_IDO_TOTAL,R5		;
;	MOV.L	#_DRVHOS_IDO_BUF,R6		;
;	MOV.L	#_DRVHOS_IDO_POINT,R7		;//�ޯ̧�Ǘ��߲��
;	Input LOAD R2:data
;	Input R3:SYSPARAM
;	R5:4B-TOTAL-ADR
;	R6:4B-BUF-ADR
;	R7:2B-POINTER-ADR
;	
;	ANS R2=TOTAL
_IDO_AVL4B_MAK1:
	SUB_START
	MOV.W	@R7,R4			;POINTER
	MOV	R4,R0			;
	SHLL2	R0			;
	MOV.L	@(R0,R6),R1		;OLD
	MOV.L	R2,@(R0,R6)		;NEW-BUF-SAVE

	MOV.L	@R5,R0			;TOTAL-LOAD
	ADD	R0,R2			;TOTAL+NEW
	SUB	R1,R2			;
	MOV.L	R2,@R5			;R2:TOTAL SAVE

	ADD	#1,R4			;
	CMP/HI	R4,R3			;R4 < R3 
	BT	IDO_AVL4B_MK1_050	;
	XOR	R4,R4			;
IDO_AVL4B_MK1_050:			;
	MOV.W	R4,@R7			;POINTER SAVE
	SUB_END
	M_RTS




;	***********************************
;	***				***
;	***	1CYCLE�I��		***
;	***				***
;	***********************************
;	===	1CYCLE�I��	===
;	�ʏ�ł��������ł��ړ����ς͂���Ă���
;
;
_DAI_MOSTPOS_CMPARE:
	SUB_START

;	===2003-06-06[1-3]  BIT4�̸ر�ύX===
	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R14				;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_DRVHOS_USE_FLG,LG=W,BIT=~BIT4,WKREG=R1	;BIT4=0 ����̈斢
;	====================================

	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	AND	#(BIT6+BIT3+BIT0),R0		;
	CMP/EQ	#(BIT6+BIT3+BIT0),R0		;BIT3:�J�n����
	BT	DRVHOS_SMP_END1_020		;
	M_BRA	DRVHOS_SMP_END1_EXT		;
DRVHOS_SMP_END1_020:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_DRVHOS_USE_FLG,LG=W,BIT=~BIT3,WKREG=R4	;//�J�n������ʉ߂������H

;	==================================
	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	TST	#(BIT2+BIT1),R0			;
	TST_BIT_ON DRVHOS_SMP_END1_100		;�����ް��쐬��or�ʏ��ް��쐬��
	MOV.L	#_DRVHOS_WAIT_CNT_PV,R5		;
	MOV.W	@R5,R2				;
	TST	R2,R2				;
	TST_BIT_OF DRVHOS_SMP_END1_050		;
	ADD	#-1,R2				;
	MOV.W	R2,@R5				;
;	===== 2003-07-14 ===
	FAR_JSR	#_DAI_DEF_PVMAK,R0		;�{����MIN_POS�����ł���
;	=====================
DRVHOS_SMP_END1_050:				;
	M_BRA	DRVHOS_SMP_END1_EXT		;

;	====== �����ݸޗL�苤�� =========
DRVHOS_SMP_END1_100:

;	=== 2003-06-06[1-4] ===
	MOV.W	#BIT4,R2			;
	TST	R2,R14				;
	TST_BIT_ON DRVHOS_SMP_END1_120		;�����ݸ��ް��L��
	M_BRA	DRVHOS_SMP_END1_EXT		;

DRVHOS_SMP_END1_120:

	PUSH_REG1 R0
	MOV.L	#_DRVHOS_MOST_DN_RNAPOS,R1	;//�ŉ����_��WORK(175~359) 175�x����̫�Ă��쐬
	MOV.L	@R1,R2				;R2:data
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_DRVHOS_IDO_TOTAL,R5		;
	MOV.L	#_DRVHOS_IDO_BUF,R6		;
	MOV.L	#_DRVHOS_IDO_POINT,R7		;//�ޯ̧�Ǘ��߲��
	FAR_JSR	#_IDO_AVL4B_MAK1,R0		;

;	============== 2003-07-14 ============
	MOV.L	#_DRVHOS_IDO_CNT,R5		;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	@R5,R0				;
	ADD	#1,R0				;
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R4				;
	CMP/HI	R4,R0				;
	BT	DRVHOS_SMP_END1_150		;R4(10)<11
	MOV.W	R0,@R5				;R4(10)>=R0 0,1~10
DRVHOS_SMP_END1_150				;
;	=======================================[2003-07-14]

	POP_REG1 R0				;
	TST	#BIT2,R0			;�ʏ풆?
	TST_BIT_ON DRVHOS_SMP_END1_300		;YES

;	==== ���������ݸޒ�(1~10��) ==========
	MOV.L	#_DRVHOS_DEF_CNT_PV,R5					;
	MOV.W	@R5,R0							;
	TST	R0,R0							;
	TST_BIT_OF DRVHOS_SMP_END1_EXT					;
	ADD	#-1,R0							;
	MOV.W	R0,@R5							;
	TST	R0,R0							;
	TST_BIT_OF DRVHOS_SMP_END1_200					;

;	�����񐔒�(���ω�)
;	===== 2003-07-14 ===
	FAR_JSR	#_DAI_DEF_PVMAK,R0		;�����ȕ��ω�
	M_BRA	DRVHOS_SMP_END1_EXT			;


DRVHOS_SMP_END1_200:
	MEM1_BIT0_TO_BIT7_ORSET MEM=_DRVHOS_USE_FLG,LG=W,BIT=BIT2,WKREG=R4	;
	FAR_JSR	#_DRVHOS_DN_DATA_SERCH,R0	;ANS R2
	MOV.L	#_DRVHOS_DEF_RNA_POS,R1	;//�ŉ����_�̏����l
	MOV.L	R2,@R1			;
	M_BRA	DRVHOS_SMP_END1_EXT	;�������񐔂��Ȃ���

DRVHOS_SMP_END1_300:
	MOV.L	#_WPAR_DRVHOS_SEL1,R1	;2003-07-09
	MOV.W	@R1,R0			;
	CMP/EQ	#2,R0			;
	BT	DRVHOS_SMP_END1_350	;

;	==== ����� ===
	FAR_JSR	#_DRVHOS_DN_DATA_SERCH,R0	;ANS R2
	MOV.L	#_DRVHOS_DEF_RNA_POS,R1		;//�ŉ����_�̏����l
	MOV.L	@R1,R3				;
	SUB	R3,R2				;����オ������␳���グ��
	MOV.L	#_RNA_ABS_DRVHOS_DT,R1		;//�␳�ް� 2003-01-31
	MOV.L	R2,@R1				;

	FAR_JSR	#_RNA_DAIHAITO_MAK,R0		;�޲ʲč쐬(PARAM=2�ł͖��Ӗ��ȃP�[�X)
	MOV.L	#_PVX_DYHITO_POS,R6		;
	MOV.L	R2,@R6				;

	FAR_JSR	#_DAI_DATA_CMP_SEQ_MAK,R0	;��r
	M_BRA	DRVHOS_SMP_END1_EXT		;


DRVHOS_SMP_END1_350:
;	==2003-07-09 NEW ===
	MOV.W	#BIT0,R0
	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
	MOV.W	R0,@R1				;

	FAR_JSR	#_DRVHOS_DN_DATA_SERCH,R0	;ANS R2
	MOV.L	#_PRD_DAI_POS0,R1		;//���Y����(��)
	MOV.L	R2,@R1				;
	MOV.L	#_PRD_DAI_POS1,R1		;//�␳�܂�
	MOV.L	R2,@R1				;


	FAR_JSR	#_DAI_DATA_CMP_SEQ_MK2,R0	;��r


DRVHOS_SMP_END1_EXT:			;
	SUB_END
	M_RTS

;	***********************************
;	***	�����f�[�^�쐬		***
;	***********************************
;	ANS.R2= (_DRVHOS_CAL_RNA_POS) �X�V
_DRVHOS_DN_DATA_SERCH:
	SUB_START

	MOV.L	#_WPAR_DRVHOS_NO_USE,R1				;
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_ON DRVHOS_DNDAT_SRCH100				;
	XOR	R8,R8	
	FAR_JSR	#_DRVHOS_IDO_AVL_CALC,R0			;
	M_BRA	DRVHOS_DNDAT_SRCH_EXT				;

DRVHOS_DNDAT_SRCH100:
	CMP/EQ	#1,R0						;
	BF	DRVHOS_DNDAT_SRCH200				;
;	=======================================
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_DRVHOS_IDO_BUF,R6		;
	FAR_JSR	#_MAX1_MIN1_SERCH,R0		;MAX+MIN�̌��ʂ������Ă��� R8
	FAR_JSR	#_DRVHOS_IDO_AVL_CALC,R0	;
	M_BRA	DRVHOS_DNDAT_SRCH_EXT		;

DRVHOS_DNDAT_SRCH200:
	CMP/EQ	#2,R0						;
	BF	DRVHOS_DNDAT_SRCH300				;

	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_DRVHOS_IDO_BUF,R6		;
	FAR_JSR	#_MAX2_MIN2_SERCH,R0		;MAX+MIN�̌��ʂ������Ă��� R8
	FAR_JSR	#_DRVHOS_IDO_AVL_CALC,R0	;
	M_BRA	DRVHOS_DNDAT_SRCH_EXT		;

DRVHOS_DNDAT_SRCH300:
;	======= �ɂȂ�m���t���[�ɐݒ肵���ꍇ�̱ٺ�ؽ�тɂ��� ======
	XOR	R8,R8						;
	FAR_JSR	#_DRVHOS_IDO_AVL_CALC,R0			;
	M_BRA	DRVHOS_DNDAT_SRCH_EXT				;


DRVHOS_DNDAT_SRCH_EXT:
	MOV.L	#_DRVHOS_CAL_RNA_POS,R1	;
	MOV.L	R2,@R1			;
	SUB_END
	M_RTS



;	*******************************************
;	***	MAX1/MIN1��T��MAX+MIN��R8��	***
;	*******************************************
;	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
;	MOV.W	@R1,R3				;
;	MOV.L	#_DRVHOS_IDO_BUF,R6		;
;	FAR_JSR	#_MAX1_MIN1_SERCH,R0		;MAX+MIN�̌��ʂ������Ă��� R8
;	<R4MIN1,R5MAX1>
_MAX1_MIN1_SERCH:
	SUB_START
	XOR	R0,R0				;
	MOV.L	@R6+,R2				;INITAL DATA LOAD
	MOV	R2,R4				;MIN
	MOV	R2,R5				;MAX
	ADD	#-1,R3				;

MAX1_MIN1_SRH_050:
	CMP/PL	R3				;
	BF	MAX1_MIN1_SRH_200		;
	MOV.L	@R6+,R2				;
	CMP/GE	R4,R2				;MIN =< DATA
	BT	MAX1_MIN1_SRH_100		;
	MOV	R2,R4				;REF DATA < MIN
MAX1_MIN1_SRH_100:
	CMP/GE	R2,R5				;DATA =< R5MAX
	BT	MAX1_MIN1_SRH_150		;
	MOV	R2,R5				;REF R5MAX < DATA 
MAX1_MIN1_SRH_150:
	ADD	#-1,R3				;
	M_BRA	MAX1_MIN1_SRH_050		;

MAX1_MIN1_SRH_200:				;
	MOV	R4,R8				;
	ADD	R5,R8				;
	SUB_END
	M_RTS

;	*******************************************
;	***	MAX1/MIN1��T��MAX+MIN��R8��	***
;	*******************************************
;	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
;	MOV.W	@R1,R3				;
;	MOV.L	#_DRVHOS_IDO_BUF,R6		;
;	FAR_JSR	#_MAX1_MIN1_SERCH,R0		;MAX+MIN�̌��ʂ������Ă��� R8
;	R4,R10
;	R5,R11

_MAX2_MIN2_SERCH:
	SUB_START
	XOR	R0,R0				;
	MOV.L	@R6+,R4				;INITAL DATA LOAD
	MOV.L	@R6+,R5				;
	CMP/GE	R4,R5				;
	BT	MAX2_MIN2_SRH_010		;
	MOV	R5,R2				;
	MOV	R4,R5				;
	MOV	R2,R4				;R4<R5
MAX2_MIN2_SRH_010:				;

	MOV.L	@R6+,R2				;R4<R10<R11<R5
	CMP/GE	R5,R2				;
	BF	MAX2_MIN2_SRH_012		;
	MOV	R5,R10				;R4<R10<R5
	MOV	R2,R5				;
	M_BRA	MAX2_MIN2_SRH_020		;<R5
MAX2_MIN2_SRH_012:				;
	CMP/GE	R4,R2				;
	BT	MAX2_MIN2_SRH_014		;R4<R10<R5
	MOV	R4,R10				;
	MOV	R2,R4				;
	M_BRA	MAX2_MIN2_SRH_020		;
MAX2_MIN2_SRH_014:				;
	MOV	R2,R10				;
MAX2_MIN2_SRH_020:				;

	MOV.L	@R6+,R2				;R4<R10<R5
	CMP/GE	R5,R2				;
	BF	MAX2_MIN2_SRH_022		;
	MOV	R5,R11				;
	MOV	R2,R5				;
	M_BRA	MAX2_MIN2_SRH_040		;
MAX2_MIN2_SRH_022:				;
	CMP/GE	R10,R2				;
	BF	MAX2_MIN2_SRH_024		;
	MOV	R2,R11				;
	M_BRA	MAX2_MIN2_SRH_040		;
MAX2_MIN2_SRH_024:				;
	CMP/GE	R4,R2				;
	BF	MAX2_MIN2_SRH_026		;
	MOV	R10,R11				;
	MOV	R2,R10				;
	M_BRA	MAX2_MIN2_SRH_040		;

MAX2_MIN2_SRH_026:				;
	MOV	R10,R11				;
	MOV	R4,R10				;
	MOV	R2,R4				;
MAX2_MIN2_SRH_040:
;
;	R4<R10<R11<R5
;
;

	ADD	#-4,R3				;

MAX2_MIN2_SRH_050:
	CMP/PL	R3
	BF	MAX2_MIN2_SRH_500		;
	MOV.L	@R6+,R2				;

	CMP/GE	R4,R2				;MIN =< DATA
	BT	MAX2_MIN2_SRH_100		;
	MOV	R4,R10				;MIN1==>MIN2
	MOV	R2,R4				;NEW-MIN=>MIN1
	M_BRA	MAX2_MIN2_SRH_250
MAX2_MIN2_SRH_100:
	CMP/GE	R10,R2				;
	BT	MAX2_MIN2_SRH_150		;
	MOV	R2,R10				;
	M_BRA	MAX2_MIN2_SRH_250

MAX2_MIN2_SRH_150:				;
	CMP/GE	R2,R5				;DATA =< R5 MAX1��گ��=>MAX2
	BT	MAX2_MIN2_SRH_200		;
	MOV	R5,R11				;
	MOV	R2,R5				;REF R5MAX < DATA 
	M_BRA	MAX2_MIN2_SRH_250
MAX2_MIN2_SRH_200:
	CMP/GE	R2,R11				;DATA =< R5 MAX2�̂���گ��
	BT	MAX2_MIN2_SRH_250		;
	MOV	R2,R11				;
MAX2_MIN2_SRH_250:
	ADD	#-1,R3				;
	M_BRA	MAX2_MIN2_SRH_050		;

MAX2_MIN2_SRH_500:				;
	MOV	R4,R8				;
	ADD	R5,R8				;
	ADD	R10,R8				;
	ADD	R11,R8				;
	SUB_END
	M_RTS


;	*******************************************************************
;	***								***
;	***		���Z						***
;	***		(TOTAL-MAX1-MIN1-MAX2-MIN2-...)/AVL-2*NOUSE	***
;	***								***
;	*******************************************************************
;	Input R8:MAX+MIN
_DRVHOS_IDO_AVL_CALC:
	SUB_START
	MOV.L	#_DRVHOS_IDO_TOTAL,R1				;
	MOV.L	@R1,R2						;
	SUB	R8,R2						;
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1				;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R4						;
	MOV.L	#_WPAR_DRVHOS_NO_USE,R1				;
	MOV.W	@R1,R0						;
	ADD	R0,R0						;
	SUB	R0,R4						;
	TST	R4,R4						;
	TST_BIT_OF DRVHOS_IDO_AVLCAL050				;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
DRVHOS_IDO_AVLCAL050:						;

	SUB_END
	M_RTS

;	*******************************************
;	***	���ω񐔂ɒB����܂ł̕\��	***
;	*******************************************
_DAI_DEF_PVMAK:
	SUB_START
;	==2003-07-09 NEW ===
	MOV.W	#BIT0,R0
	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
	MOV.W	R0,@R1				;

	MOV.L	#_RNA_ABS_MINPOS,R1			;//�ŉ����_
	MOV.L	@R1,R2					;

	MOV.L	#_DRVHOS_IDO_CNT,R1			;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	@R1,R4					;
	TST	R4,R4					;
	TST_BIT_OF DAI_DEFPVMK_END			;���Z���ʂȂ�/�ŉ����_(���肦�Ȃ�?)

	MOV.L	#_DRVHOS_IDO_TOTAL,R1				;
	MOV.L	@R1,R2						;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;TOTAL/

DAI_DEFPVMK_END:
	MOV.L	#_PRD_DAI_POS0,R1			;//���Y����(��)[1]
	MOV.L	R2,@R1					;
	MOV.L	#_PRD_DAI_POS1,R1		;//�␳�܂�
	MOV.L	R2,@R1				;
	SUB_END
	M_RTS


;	***********************************
;	***	�޲ʲĂ̔�r		***
;	***********************************
_DAI_DATA_CMP_SEQ_MAK:
	SUB_START
	MOV.L	#_PVX_DYHITO_POS,R6	;
	MOV.L	@R6,R2			;

	XOR	R7,R7			;
	XOR	R6,R6
	MOV.L	#_SET1_DAIORG0_CMP3DN,R5		;//	4	;�_�C�n�C�g()
	MOV.L	@R5,R4
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R6		;SV_MIN(R4) > PV(R2) .11
;;2003-07-09	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R1,ANS_REG=R7	;SV_MIN(R4) > PV(R1) .5
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R7		;SV_MIN(R4) > PV(R1) .5

	MOV.L	#_SET1_DAIORG0_CMP3UP,R5				;
	MOV.L	@R5,R4
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R6		;PV(R2) > SV_MAX(R4) .10
;;2003-07-09	REG1_CMP_REG2_ROTL REG1=R1,CF=GT,REG2=R4,ANS_REG=R7	;PV(R1) > SV_MAX(R4) .4
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R7		;PV(R1) > SV_MAX(R4) .4


;	===2002-12-16 ==
	SHLL2	R6							;9,8
	SHLL2	R7							;3,2
;	================

	MOV.L	#_SET1_DAIORG0_CMP1DN,R5				;
	MOV.L	@R5,R4							;
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R6		;SV_MIN(R4) > PV(R2) .7
;;2003-07-09	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R1,ANS_REG=R7	;SV_MIN(R4) > PV(R1) .1
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R7		;SV_MIN(R4) > PV(R1) .1

	MOV.L	#_SET1_DAIORG0_CMP1UP,R5				;
	MOV.L	@R5,R4							;
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R6		;PV(R2) > SV_MAX(R4) .6
;;2003-07-09	REG1_CMP_REG2_ROTL REG1=R1,CF=GT,REG2=R4,ANS_REG=R7	;PV(R1) > SV_MAX(R4) .0
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R7		;PV(R1) > SV_MAX(R4) .0

	SHLL2	R7
	SHLL2	R7
	SHLL2	R7
	OR	R6,R7							;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB211,R4	;
	MOV.W	@R4,R0				;
	MOV.W	#H'0CF3,R1			;2002-12-16 [0000][1100][11,11][0011]
	AND	R1,R7				;
	NOT	R1,R1				;
	AND	R1,R0				;
	OR	R7,R0				;
	MOV.W	R0,@R4				;
	SUB_END
	M_RTS


;	***********************************
;	***	�޲ʲĂ̔�r		***
;	***********************************
_DAI_DATA_CMP_SEQ_MK2:
	SUB_START
	MOV.L	#_PVX_DAI_POS1,R1	;�޲ʲĕ\���l�E����l
	MOV.L	@R1,R2			;

;;;;;	MOV.L	#_PVX_DYHITO_POS,R1	;(�O�͂�����g���Ă���)
;;;;;	MOV.L	R2,@R1			;

	MOV.L	#_PRD_DAI_POS1,R1	;
	MOV.L	@R1,R1			;

	XOR	R7,R7			;
	XOR	R6,R6
	MOV.L	#_SET1_DAIORG0_CMP3DN,R5		;//	4	;�_�C�n�C�g()
	MOV.L	@R5,R4
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R6		;SV_MIN(R4) > PV(R2) .11
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R1,ANS_REG=R7		;SV_MIN(R4) > PV(R1) .5

	MOV.L	#_SET1_DAIORG0_CMP3UP,R5				;
	MOV.L	@R5,R4
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R6		;PV(R2) > SV_MAX(R4) .10
	REG1_CMP_REG2_ROTL REG1=R1,CF=GT,REG2=R4,ANS_REG=R7		;PV(R1) > SV_MAX(R4) .4


;	===2002-12-16 ==
	SHLL2	R6							;9,8
	SHLL2	R7							;3,2
;	================

	MOV.L	#_SET1_DAIORG0_CMP1DN,R5				;
	MOV.L	@R5,R4							;
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R2,ANS_REG=R6		;SV_MIN(R4) > PV(R2) .7
	REG1_CMP_REG2_ROTL REG1=R4,CF=GT,REG2=R1,ANS_REG=R7		;SV_MIN(R4) > PV(R1) .1

	MOV.L	#_SET1_DAIORG0_CMP1UP,R5				;
	MOV.L	@R5,R4							;
	REG1_CMP_REG2_ROTL REG1=R2,CF=GT,REG2=R4,ANS_REG=R6		;PV(R2) > SV_MAX(R4) .6
	REG1_CMP_REG2_ROTL REG1=R1,CF=GT,REG2=R4,ANS_REG=R7		;PV(R1) > SV_MAX(R4) .0

	SHLL2	R7
	SHLL2	R7
	SHLL2	R7
	OR	R6,R7							;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB211,R4	;
	MOV.W	@R4,R0				;
	MOV.W	#H'0CF3,R1			;2002-12-16 [0000][1100][11,11][0011]
	AND	R1,R7				;
	NOT	R1,R1				;
	AND	R1,R0				;
	OR	R7,R0				;
	MOV.W	R0,@R4				;
	SUB_END
	M_RTS




;	*******************************************
;	**** 	���܂œ��l�ɂ��̏����͎c�� 	***
;	*******************************************
_DAI_FULL_SCALE_SMP_INI
	SUB_START
	MOV.L	#_DAI_CMP_SMPSTART,R4		;
	MOV.W	@R4,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON DAI_MOSTPOS_SPINI_050	;
	OR	#BIT0,R0			;
	MOV.W	R0,@R4				;
	MOV.L	#_RNA_ABS_POS,R1		;//��ٽ��ʍ���(��Έʒu)
	MOV.L	@R1,R2				;
	MOV.L	#_RNA_ABS_WKMINPOS,R4		;//�����ݸ�ܰ��N���ORNA_ABS_POS-full��Ă̂�
	MOV.L	R2,@R4				;

;	------- 2009-10-07���U��q�ł��Ă΂�邩���]����----
	MOV.L	#_CPOS_CTL_MATH,R1		;[2009-10-07���U�q]
	MOV.W	@R1,R0				;[2009-10-07���U�q]
	TST	#_DMATH_CNTROT,R0		;[2009-10-07���U�q]
	TST_BIT_OF DAI_MOSTPOS_SPINI_050	;[2009-10-07���U�q]

	MOV.L	#_RNA_ABS_WKMAXPOS,R4		;//�����ݸ�ܰ��N���ORNA_ABS_POS
	MOV.L	R2,@R4				;(�㎀�_�␳)

DAI_MOSTPOS_SPINI_050:				;
	SUB_END
	M_RTS

;	*******************************************
;	**** 	���܂œ��l�ɂ��̏����͎c�� 	***
;	*******************************************
_DAI_FULL_SCALE_SMPLE:
	SUB_START
;	====== ���܂œ��l�ɂ��̏����͎c�� =======
	MOV.L	#_DAI_CMP_SMPSTART,R4		;
	MOV.W	@R4,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF DAI_MOSTPOS_SMP100		;

	MOV.L	#_RNA_ABS_POS,R1	;//��ٽ��ʍ���(��Έʒu)
	MOV.L	@R1,R2			;

;	------- 2009-10-07���U��q�ł��Ă΂�邩���]����----
	MOV.L	#_CPOS_CTL_MATH,R1		;[2009-10-07���U�q]
	MOV.W	@R1,R0				;[2009-10-07���U�q]
	TST	#_DMATH_CNTROT,R0		;[2009-10-07���U�q]
	TST_BIT_OF DAI_MOSTPOS_SMP050		;[2009-10-07���U�q]

	MOV.L	#_RNA_ABS_WKMAXPOS,R5	;
	MOV.L	@R5,R0			;
	CMP/GE	R2,R0			;
	BT	DAI_MOSTPOS_SMP050	;MAX >= NEW THEN EXIT
	MOV.L	R2,@R5			;NEW REF
DAI_MOSTPOS_SMP050:			;

	MOV.L	#_RNA_ABS_WKMINPOS,R6	;
	MOV.L	@R6,R4			;
	CMP/GE	R4,R2			;MIN =< NEW THEN EXIT
	BT	DAI_MOSTPOS_SMP100	;
	MOV.L	R2,@R6			;NEW REF
DAI_MOSTPOS_SMP100:			;
;	====== ���܂œ��l�ɂ��̏����͎c�� =======
	SUB_END
	M_RTS

;	*******************************************
;	***	���܂ł̏����̈ꕔ���c��	***
;	*******************************************
_DAI_FULL_SCALE_SMP_END:
	SUB_START
;	------- 2009-10-07���U��q�ł��Ă΂�邩���]����----
	MOV.L	#_CPOS_CTL_MATH,R1		;[2009-10-07���U�q]
	MOV.W	@R1,R0				;[2009-10-07���U�q]
	TST	#_DMATH_CNTROT,R0		;[2009-10-07���U�q]
	TST_BIT_OF DAI_MOSTPOS_CMP020		;[2009-10-07���U�q]

	MOV.L	#_RNA_ABS_WKMAXPOS,R5		;�ٿ�Ă݂̂�work
	MOV.L	@R5,R2				;

	MOV.L	#_RNA_ABS_MAXPOS,R4		;//�ŏ㎀�_--Ӱ�ދN���ORNA_ABS_POS(���̿�Ă̂�)
	MOV.L	R2,@R4				;

DAI_MOSTPOS_CMP020

	MOV.L	#_RNA_ABS_WKMINPOS,R5		;�ٿ�Ă݂̂�work
	MOV.L	@R5,R1				;
	MOV.L	#_RNA_ABS_MINPOS,R4		;//�ŏ㎀�_--Ӱ�ދN���ORNA_ABS_POS(���̿�Ă̂�)
	MOV.L	R1,@R4				;

	MOV.L	#_DAI_CMP_SMPSTART,R4		;
	MOV.W	@R4,R0				;
	TST	#BIT1,R0			;1���-SET
	TST_BIT_ON DAI_MOSTPOS_CMP050		;
	OR	#BIT1,R0			;
	MOV.W	R0,@R4				;
	M_BRA	DAI_MOSTPOS_CMP100		;

DAI_MOSTPOS_CMP050

DAI_MOSTPOS_CMP100:

	MOV.L	#_DAI_CMP_SMPSTART,R4		;���ꃂ�[�h�ł͖����Ƀ`�F�b�N���s��
	MOV.W	@R4,R0				;
	AND	#LOW ~BIT0,R0			;
	MOV.W	R0,@R4				;
	SUB_END
	M_RTS


;	=======  ==========
;	*******************************************
;	***					***
;	***	�V�^�@�^�]���@�_�C�n�C�g�␳	***
;	***					***
;	*******************************************
;	/�␳�@��=>�؁@�펞�Ď�
;	/_DRVHOS_MEMORG_SET_INI�����s �␳DATA=0,�␳����FLG=0
;	/��=>�� �������Ȃ�
;	/���_���A���� _DRVHOS_MEMORG_SET_INI�����s �␳DATA=0,�␳����FLG=0
;	/1��ڂ̉^�]�J�n �␳���Ȃ� FLG.BIT0=1�ɂ�WAIT����_SV=>PV�־��
;	/�I���� ����PV�𔻒f FLG.BIT1=1
;	/PV=0�Ȃ� =>��������������Ă���,TOTAL=0�ɂ���,�ޯ̧=0,���������ް���1�ڂɓ����,TOTAL�쐬
;	/......���������ް����ł����� FLG.BIT2=1�ɂ��� ��ް�=�␳�Ƃ���DATA=0�̂͂�
;	/
;	*******************************************
;	***					***
;	***	�V�^�^�]���̕␳�̌��_������	***
;	***					***
;	*******************************************
;	MEMORG�ɏ������݂������Ȃ����ۂɍs������
;	DRVHOS_DT<=0
;
_DRVHOS_MEMORG_SET_INI:
	SUB_START
	XOR	R0,R0				;
	MOV.L	#_RNA_ABS_DRVHOS_DT,R1		;//�␳�ް� 2003-01-31
	MOV.L	R0,@R1				;
	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	R0,@R1				;
	SUB_END					;
	M_RTS

;	***********************************************************
;	***							***
;       ***     ���ꂩ�牺�������ݸނ��J�n���邽�߂̲Ƽ��	***
;	***							***
;	***	�␳��=>��					***
;	***							***
;	***********************************************************
;	=== �����ʒu�쐬��10��O�Ƽ�� ===
_DRVHOS_ALL_INI:
	SUB_START
	XOR	R0,R0				;
	MOV.L	#_RNA_ABS_DRVHOS_DT,R1		;//�␳�ް� 2003-01-31
	MOV.L	R0,@R1				;
	MOV.L	#_DRVHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	R0,@R1				;

;	===2003-07-09 ===
	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS

;	***********************************************************
;	***							***
;	***	�V�^�^�]���̕␳�P�O��(���������l)������	***
;	***							***
;	***********************************************************
;	=== �����ʒu�쐬��10���Ƽ�� ===
_DRVHOS_SMP_INI:
	SUB_START
	SUB_END
	M_RTS



