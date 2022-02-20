	.IMPORT	_dio_top1

;;;;;;;;;;;;;;;;;;;;;	.AIF	_CB_CPU_SEL EQ _CB_CPUA

;	***************************************************
;	***						***
;	***						***
;	***		�Z���t�`�F�b�N�\�t�g		***
;	***						***
;	***						***
;	***************************************************
;	ssa_self.src����INCLUDE����

_STEP00	.EQU	0	;
_STEP01	.EQU	1	;
_STEP02	.EQU	2	;
_STEP03	.EQU	3	;
_STEP04	.EQU	4	;
_STEP05	.EQU	5	;
_STEP06	.EQU	6	;
_STEP07	.EQU	7	;
_STEP08	.EQU	8	;
_STEP09	.EQU	9	;
_STEP10	.EQU	10	;
_STEP11	.EQU	11	;
_STEP12	.EQU	12	;
_STEP13	.EQU	13	;
_STEP14	.EQU	14	;
_STEP15	.EQU	15	;

;	======================================== SAITO INS 2002-09-12
;	==== ������������� ====
	.EXPORT	_SLF_HNDFLG_LOAD	; CPUA,B FLG����ւ�LOAD
	.EXPORT	_SELF_CHECK_ACT		; �Z���t�`�F�b�N������
	.EXPORT	_SLF_HNDFLG_STORE	; CPUA,B FLG����ւ�STORE
;	========================================


	.IMPORT	_CPUA_SELF_HAND_FLG		; �����̏���׸�DPRAM
	.IMPORT	_CPUB_SELF_HAND_FLG		; ����̏���׸�DPRAM

	.LIST	OFF
	.INCLUDE	"ssa_out1.mac"		; //
	.INCLUDE	"ssa_wrmy.ext"		; 
	.include	"ssa_seq1.equ"
	.INCLUDE	"ssa_wram.ext"		; 
	.INCLUDE	"ssa_had1.equ"		; 
	.LIST	ON

	.IMPORT	_dio_top2			;
;;	.IMPORT	_SEQ_CARD_RAM			; ���ı�� 2008-07-30 SAITO
	.IMPORT	_SEQAB_DP_TOP			; 2008-07-30 SAITO

	.IMPORT	_FRCYCL_ON			; *FCYCL,RCYCL ON �L��
	.IMPORT	_FRCYCL_OF			; *FCYCL,RCYCL ON ����

	.IMPORT	_RESET_OUT			; RST ON
	.IMPORT	_RESET_END_OUT			; RST OFF

	.IMPORT	_EMG_STOP			; ����~�ɂ���

;	--------2014-09-14----------
;;	.IMPORT	_MONI_SELF_STS1;
;;	.IMPORT	_MONI_SELF_STS2;

;	*******************************************
;	***	DPRAM SELF HAND FLG STORE	***
;	*******************************************
;	_SELF_CHECK_ACT�̌��CALL
;	*******************************************
;	***	DPRAM SELF HAND FLG LOAD	***
;	*******************************************
;	_SELF_CHECK_ACT�̑O��CALL
;
_SLF_HNDFLG_LOAD:
	SUB_START
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;	=== CPUA ===
;;;�Ӗ�����		MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;;�Ӗ�����		MOV.W	@R1,R2				;
	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	@R3,R4				;

;;;�Ӗ�����		MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;;�Ӗ�����		MOV.W	R2,@R1				;
	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	R4,@R3				;

	.AELSE
;	=== CPUB ===
	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	@R1,R2				;
;;;�Ӗ�����	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;;�Ӗ�����	MOV.W	@R3,R4				;

;;;�Ӗ�����	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;;�Ӗ�����	MOV.W	R4,@R1				;
	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	R2,@R3				;

	.AENDI

	SUB_END
	M_RTS

;	*******************************************
;	***	DPRAM SELF HAND FLG STORE	***
;	*******************************************
;	_SELF_CHECK_ACT�̌��CALL
;
_SLF_HNDFLG_STORE:
	SUB_START
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;	=== CPUA ===
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	@R1,R2				;
;;;;;�����	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;;;;�����	MOV.W	@R3,R4				;

	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	R2,@R1				;
;;;;;�����	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;;;;�����	MOV.W	R4,@R3				;

	.AELSE
;	=== CPUB ===
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	@R1,R2				;
;;;;;�����	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;;;;�����	MOV.W	@R3,R4				;

;;;;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;;;;	MOV.W	R4,@R1				;
	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	R2,@R3				;

	.AENDI

	SUB_END
	M_RTS

;	*******************************************
;	***	DPRAM SELF HAND FLG LOAD	***
;	*******************************************
;	_SELF_CHECK_ACT�̑O��CALL
;
;;_SLF_HNDFLG_LOAD:
;;	SUB_START
;;	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;;;	=== CPUA ===
;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R1,R2				;
;;	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R3,R4				;
;;
;;	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R2,@R1				;
;;	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R4,@R3				;
;;
;;	.AELSE
;;;	=== CPUB ===
;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R1,R2				;
;;	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R3,R4				;
;;
;;	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R4,@R1				;
;;	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R2,@R3				;
;;
;;	.AENDI
;;
;;	SUB_END
;;	M_RTS

;
;;_SLF_HNDFLG_STORE:
;;	SUB_START
;;	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;;;	=== CPUA ===
;;	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R1,R2				;
;;	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R3,R4				;
;;
;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R2,@R1				;
;;	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R4,@R3				;
;;
;;	.AELSE
;;;	=== CPUB ===
;;	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R1,R2				;
;;	MOV.L	#_SELF_HAND_FLG2,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	@R3,R4				;
;;
;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; �����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R4,@R1				;
;;	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; ����̏���׸ވُ�STEP�ɂȂ���������
;;	MOV.W	R2,@R3				;
;;
;;	.AENDI
;;
;;	SUB_END
;;	M_RTS


_SELF_CHK_TM	.EQU	D'20000		; 20S

;	*******************************************
;	***	�Z���t�`�F�b�N�������\�t�g	***
;	*******************************************
_SELF_CHECK_ACT:
	SUB_START
;	===== 2006-04-10(2��ނ̾���������s�����߂����ł͏I�点�Ȃ�) =====
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7����������튮��
	MOV.W	@R1,R0					;

	MOV.L	#_SELF_FLG,R1				;
	MOV.W	@R1,R4					;
	OR	R4,R0					;

	MOV.W	#BIT7,R4				;
	TST	R4,R0					;
	TST_BIT_OF SELF_CHECKACT_STR00			;
	M_BRA _SELF_CHK_ACT_EXIT			; �������Ȃ�

SELF_CHECKACT_STR00:
;		-----------------------------------------

	MOV.L	#_SELF_FLG,R1			; BIT0:��������J�n�w��
	MOV.W	@R1,R0				;
	CMP/EQ	#BIT0,R0			;
	BF	_SELF_CHECK_ACT_CMDCHK020	; �w��ON����Ȃ� THEN JUMP

;	======== ��ǉ�<2003-01-28> ===
	MOV.L	#_SELF_START_WAIT_TM,R3		;��������J�n����WAIT(Ӱ���~����)
	MOV.W	@R3,R2				;
	TST	R2,R2				;
	TST_BIT_OF _SELF_CHECK_ACT_CMDCHK010	;
	M_BRA _SELF_CHK_ACT_EXIT		; �������Ȃ�
_SELF_CHECK_ACT_CMDCHK010:			;


;	------------------ 2014-09-14 KOMA ----------
	XOR	R3,R3
	MOV.L	#_MONI_SELF_STS1,R2		;
	MOV.W	R3,@R2				;
	MOV.L	#_MONI_SELF_STS2,R2		;
	MOV.W	R3,@R2				;
;	-----------------------------------------------

	MOV.W	#BIT0,R3			;
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	R3,@R2				; �Z���t�`�F�b�N���Z�b�g
	M_BRA	_SELF_CHECK_ACT_CMDCHK100	; �w��ON����Ȃ� THEN JUMP
_SELF_CHECK_ACT_CMDCHK020:
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	@R2,R3				; �Z���t�`�F�b�N�� CHECK
	MOV.W	#BIT0,R4			;
	CMP/EQ	R4,R3				;
	BT	_SELF_CHECK_ACT_CMDCHK040	; �Z���t�`�F�b�N�� THEN JUMP

	MOV.W	#BIT6,R4			; �ُ폈�����i���f���j
	CMP/EQ	R4,R3				;
	BT	_SELF_CHECK_ACT_CMDCHK100	;

	M_BRA _SELF_CHK_ACT_EXIT		; �������Ă��Ȃ� THEN EXIT

_SELF_CHECK_ACT_CMDCHK040:
	MOV.W	#BIT6,R3			;
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	R3,@R2				; ���f��SET

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ폈������� SET
	MOV.W	R0,@R1				;

_SELF_CHECK_ACT_CMDCHK100:

;;;;;	MOV.L	#_SELF_FLG,R1			; BIT0:��������J�n�w��
;;;;;	MOV.W	@R1,R0				;
;;;;;	MOV.W	#H'003F,R2			;
;;;;;	TST	R2,R0				;
;;;;;	TST_BIT_ON _SELF_CHK_ACT020		;
;;;;;	M_BRA _SELF_CHK_ACT_EXIT		; �w��ON�A����������Ȃ� THEN EXIT

_SELF_CHK_ACT020:
;	*** ����̏���׸ވُ�STEP�ɂȂ��������� ***
	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸ވُ�STEP�ɂȂ���������
	MOV.W	@R1,R0				;
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_ACT100		; �ُ�ɂȂ��Ă��Ȃ� THEN JUMP

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸ވُ폈������� SET
	MOV.W	R0,@R1				;

_SELF_CHK_ACT100:
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�LOAD
	MOV.W	@R1,R0				;

;	*** �Z���t�H���O  �Z���t�`�F�b�N����I ***
_SELF_CHK_STEP00:
	MOV.W	#_STEP00,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP01		; STEP=0 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP00,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP00_020		;

	MOV.W	#_STEP01,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP00_EXT		;

_SELF_CHK_STEP00_020:
	MOV.W	#_STEP01,R0			; STEP <- 1
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�1SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP00_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���P ����҂� ***
_SELF_CHK_STEP01:
	MOV.W	#_STEP01,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP02		; STEP=1 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP01,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP01_020		;

	MOV.W	#_STEP02,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP01_EXT		;
_SELF_CHK_STEP01_020:

	MOV.W	#_STEP02,R0			; STEP <- 2
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�2SET �Z���t�`�F�b�N�n�m�`�F�b�N�J�n
	MOV.W	R0,@R1				;

_SELF_CHK_STEP01_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���Q ***
_SELF_CHK_STEP02:
	MOV.W	#_STEP02,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP03		; STEP=2 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP02,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP02_020		;

	MOV.W	#_STEP03,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP02_EXT		;
_SELF_CHK_STEP02_020:

	FAR_JSR	#_SELF_ONCHECK_INIT,R0		; �Z���t�n�m�`�F�b�N�C�j�V����

	MOV.W	#_STEP03,R0			; STEP <- 3
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�3SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP02_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���R �n�m�`�F�b�N ***
_SELF_CHK_STEP03:
	MOV.W	#_STEP03,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP04		; STEP=3 NO THEN JUMP

	MOV.L	#_IOGA2_CTRL_DAT1+_IOGAo_PF,R1	;
	MOV.W	@R1,R1				;
	MOV.W	#BIT3,R2			;
	AND	R2,R1				;
	TST	R1,R1				; CHK OFF THEN WAIT
	BF	_SELF_CHK_STEP03_010		; ON THEN JUMP

	FAR_JSR	#_SELF_ONCHECK_INIT,R0		; �Z���t�n�m�`�F�b�N�C�j�V����
	M_BRA	_SELF_CHK_STEP03_EXT		;

_SELF_CHK_STEP03_010:
	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP03,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP03_020		;

	MOV.W	#_STEP04,R2			; ���肪���łɐi��ł��Ă��`�F�b�N���s
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP03_EXT		;
_SELF_CHK_STEP03_020:

	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	@R1,R1				;
	TST	R1,R1				;
	TST_BIT_OF _SELF_CHK_STEP03_ERR		; SELF CHECK TIMER UP THEN ERR

	FAR_JSR	#_SELF_ON_CHECK,R0		; �Z���t�n�m�`�F�b�N

;	---------- 2014-09-14 ����-------
	MOV.L	#_MONI_SELF_STS1,R0		;
	MOV.W	R10,@R0				;
;	---------------------------------

	MOV.W	#(BIT2+BIT1+BIT0),R0		;
	CMP/EQ	R0,R10				; �`�F�b�N����CHECK
	BF	_SELF_CHK_STEP03_EXT		; ������ THEN JUMP

	MOV.W	#_STEP04,R0			; STEP <- 4
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�4SET
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_STEP03_EXT		;

_SELF_CHK_STEP03_ERR:
	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�10SET NEXT �ُ폈��
	MOV.W	R0,@R1				;

	MOV.L	#(_SQ_CBWK_TOP+_SQCB217),R1	;
	MOV.W	@R1,R0				;
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				; ERR SEQ WK RAM SET

	MOV.W	#H'2176,R4			;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			; ����~�ɂ���

	M_BRA	_SELF_CHK_ACT_EXIT		;

_SELF_CHK_STEP03_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;


;	*** �Z���t�H���S �n�m�`�F�b�N�I������҂� ***
_SELF_CHK_STEP04:
	MOV.W	#_STEP04,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP05		; STEP=4 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP04,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP04_020		;

	MOV.W	#_STEP05,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP04_EXT		;
_SELF_CHK_STEP04_020:

	MOV.W	#_STEP05,R0			; STEP <- 5
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸� �Z���t�`�F�b�N�n�e�e�`�F�b�N�J�n
	MOV.W	R0,@R1				;

_SELF_CHK_STEP04_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���T �Z���t�`�F�b�N�n�e�e�`�F�b�N�J�n ***
_SELF_CHK_STEP05:
	MOV.W	#_STEP05,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP06		; STEP=5 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP05,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP05_020		;

	MOV.W	#_STEP06,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP05_EXT		;
_SELF_CHK_STEP05_020:

	FAR_JSR	#_SELF_OFCHECK_INIT,R0		; �Z���t�n�e�e�`�F�b�N�C�j�V����

	MOV.W	#_STEP06,R0			; STEP <- 6
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�3SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP05_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���U �n�e�e�`�F�b�N�J�n����҂� ***
_SELF_CHK_STEP06:
	MOV.W	#_STEP06,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP07		; STEP=6 NO THEN JUMP

	MOV.L	#_IOGA2_CTRL_DAT1+_IOGAo_PF,R1	;
	MOV.W	@R1,R1				;
	MOV.W	#BIT3,R2			;
	AND	R2,R1				;
	TST	R1,R1				; CHK ON THEN WAIT
	BT	_SELF_CHK_STEP06_010		; OFF THEN JUMP

	FAR_JSR	#_SELF_OFCHECK_INIT,R0		; �Z���tOFF�`�F�b�N�C�j�V����
	M_BRA	_SELF_CHK_STEP06_EXT		;

_SELF_CHK_STEP06_010:

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP06,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP06_020		;

	MOV.W	#_STEP07,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP06_EXT		;
_SELF_CHK_STEP06_020:

	MOV.W	#_STEP07,R0			; STEP <- 7
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸� �n�e�e�`�F�b�N��
	MOV.W	R0,@R1				;

_SELF_CHK_STEP06_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���V �Z���t�n�e�e�`�F�b�N ***
_SELF_CHK_STEP07:
	MOV.W	#_STEP07,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP08		; STEP=7 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP07,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP07_020		;

	MOV.W	#_STEP08,R2			; ���肪���łɐi��ł��Ă��`�F�b�N����
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP07_EXT		;
_SELF_CHK_STEP07_020:

	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	@R1,R1				;
	TST	R1,R1				;
	TST_BIT_OF _SELF_CHK_STEP07_ERR		; SELF CHECK TIMER UP THEN ERR

	FAR_JSR	#_SELF_OF_CHECK,R0		; �Z���t�n�e�e�`�F�b�N
;	---------- 2014-09-14 ����-------
	MOV.L	#_MONI_SELF_STS2,R0		;
	MOV.W	R10,@R0				;
;	---------------------------------

	MOV.W	#(BIT2+BIT1+BIT0),R0		;
	CMP/EQ	R0,R10				; �`�F�b�N����CHECK
	BF	_SELF_CHK_STEP07_EXT		; ������ THEN JUMP

	FAR_JSR	#_RESET_OUT,R0			; RST ON

	MOV.W	#_STEP08,R0			; STEP <- 8
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�7SET
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_STEP07_EXT		;

_SELF_CHK_STEP07_ERR:
	MOV.L	#(_SQ_CBWK_TOP+_SQCB217),R1	;
	MOV.W	@R1,R0				;
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				; ERR SEQ WK RAM SET

	MOV.W	#H'2176,R4			;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			; ����~�ɂ���

	M_BRA	_SELF_CHK_STEP07_EXT		;

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�10SET NEXT �ُ폈��
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_ACT_EXIT		;

_SELF_CHK_STEP07_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���W �n�e�e�`�F�b�N�I������҂� ***
_SELF_CHK_STEP08:
	MOV.W	#_STEP08,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP09		; STEP=8 NO THEN JUMP

;	=== STPA,STPB CHECK 2003-01-26 ===
;	********** SIT3_CPUB PROGRAM **********
	.AIF	_SIT_CPU_SEL	EQ	_SIT3_CPUB
	MOV.L	#_PDDR,R1	;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT12+BIT11),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;

;	********** SIT4_CPUA PROGRAM **********
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUA
	MOV.L	#_dio_top1+_IOGA_PDR2,R1		;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
;	********** SIT4_CPUB PROGRAM **********
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUB
	MOV.L	#_dio_top1+_IOGA_PDR2,R1		;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
;	********** SIT3_CPUA PROGRAM **********
	.AELSE
	MOV.L	#(_IOGA1_CTRL_DAT1+_IOGAi_PC),R1	;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3				;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
	.AENDI

	FAR_JSR	#_RESET_END_OUT,R1			; RST OFF

;	==================================

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP08,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP08_020		;

	MOV.W	#_STEP09,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP08_EXT		;
_SELF_CHK_STEP08_020:

	MOV.W	#_STEP09,R0			; STEP <- 09
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸� ����I�������
	MOV.W	R0,@R1				;

_SELF_CHK_STEP08_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���X ***
_SELF_CHK_STEP09:
	MOV.W	#_STEP09,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP10		; STEP=9 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP09,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP09_020		;

	MOV.W	#_STEP15,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP09_EXT		;
_SELF_CHK_STEP09_020:

	FAR_JSR	#_SELF_CHK_NMLEND,R0		; �Z���t�`�F�b�N����I������

	MOV.W	#_STEP15,R0			; STEP <- 15
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�15SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP09_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** �Z���t�H���P�O �ُ�I������� ***
_SELF_CHK_STEP10:
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP11		; STEP=10 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP10_020		;

	MOV.W	#_STEP11,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP10_EXT		;
_SELF_CHK_STEP10_020:


;;;;;	_MC_CH0_ON_WK1	R1,R2,R3		; VSER
;;;;;	_MC_CHK_ON_WK1	R1,R2,R3		;
	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
	_MC_CHK_OF_WK1	R1,R2,R3		;
	_MC_CH1_OF_WK1	R1,R2,R3		;
	_MC_CH2_OF_WK1	R1,R2,R3		;
;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

	FAR_JSR	#_FRCYCL_OF,R0			; *FCYCL,RCYCL ON ����

	MOV.W	#_STEP11,R0			; STEP <- 11
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸� �ُ�I������
	MOV.W	R0,@R1				;

_SELF_CHK_STEP10_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** �Z���t�H���P�P ***
_SELF_CHK_STEP11:
	MOV.W	#_STEP11,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP12		; STEP=11 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP11,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP11_020		;

	MOV.W	#_STEP14,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP11_EXT		;
_SELF_CHK_STEP11_020:

	FAR_JSR	#_SELF_CHK_ERREND,R0		; �Z���t�`�F�b�N�ُ�I������

	MOV.W	#_STEP14,R0			; STEP <- 14
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�14SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP11_EXT:

	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** �Z���t�H���P�Q ***
_SELF_CHK_STEP12:
	MOV.W	#D'12,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP13		; STEP=12 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP12,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP12_020		;

	MOV.W	#_STEP13,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP12_EXT		;
_SELF_CHK_STEP12_020:

_SELF_CHK_STEP12_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** �Z���t�H���P�R ***
_SELF_CHK_STEP13:
	MOV.W	#13,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP14		; STEP=13 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP13,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP13_020		;

	MOV.W	#_STEP14,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP13_EXT		;
_SELF_CHK_STEP13_020:

_SELF_CHK_STEP13_EXT:

	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** �Z���t�H���P�S �ُ�I������***
_SELF_CHK_STEP14:
	MOV.W	#_STEP14,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP15		; STEP=14 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP14,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP14_020		;

	MOV.W	#_STEP00,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP14_EXT		;
_SELF_CHK_STEP14_020:

	MOV.W	#_STEP00,R0			; STEP <- 0
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�15SET
	MOV.W	R0,@R1				;

;;	===== 2006-04-10(2��ނ̾���������s�����߂����ł͏I�点�Ȃ�) =====
;;	MOV.W	#(BIT7+BIT6),R0			;
;;	MOV.L	#_SELF_FLG,R1			; BIT7��������ُ튮��
;;	MOV.W	R0,@R1				;
;;
;;	XOR	R0,R0				;
;;	MOV.L	#_SELF_COM,R1			;//BIT0:��������w�� CLEAR
;;	MOV.W	R0,@R1				;
;;
;	======== FIRST SELF END==========
	MOV.W	#(BIT7+BIT6),R0				;
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7����������튮��
	MOV.W	R0,@R1					;

	XOR	R0,R0				;
	MOV.L	#_SELF_ACT_FLG,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_RESET_END_OUT,R1		; RST OFF


_SELF_CHK_STEP14_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** �Z���t�H���P�T ����I������ ***
_SELF_CHK_STEP15:
	MOV.L	#_SELF_HAND_FLG2,R1		; ����̏���׸�LOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP15,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP15_020		;

	MOV.W	#_STEP00,R2			; ���肪���łɐi��ł����玩�������ɐi��
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP15_EXT		;
_SELF_CHK_STEP15_020:

	MOV.W	#_STEP00,R0			; STEP <- 0
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸�15SET
	MOV.W	R0,@R1				;
	
;;	===== 2006-04-10(2��ނ̾���������s�����߂����ł͏I�点�Ȃ�) =====
;;	MOV.W	#BIT7,R0			;
;;	MOV.L	#_SELF_FLG,R1			; BIT7����������튮��
;;	MOV.W	R0,@R1				;
;;
;;	XOR	R0,R0				;
;;	MOV.L	#_SELF_COM,R1			;//BIT0:��������w�� CLEAR
;;	MOV.W	R0,@R1				;

;	======== FIRST SELF END==========
	MOV.W	#BIT7,R0				;
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7����������튮��
	MOV.W	R0,@R1					;

	XOR	R0,R0					;ADD 2006-04-10
	MOV.L	#_SELF_ACT_FLG,R1			;
	MOV.W	R0,@R1					;

	FAR_JSR	#_RESET_END_OUT,R1		; RST OFF

_SELF_CHK_STEP15_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;


_SELF_CHK_ACT_NML_EXIT:
;;;;;	MOV.L	#_emg_lev_flg,R1		;//�ُ���(���ް�)
	MOV.L	#_emg_err_flg,R1		;//�ُ�ׯ�
	MOV.W	@R1,R0				; �Z���t�`�F�b�N���ɔ���~�Ȃ�Z���t�`�F�b�N�ُ�I��
	TST	R0,R0				;
	TST_BIT_OF _SELF_CHK_NML_ACT_EX_020	;
	M_BRA	_SELF_CHK_NML_ACT_EX_040

_SELF_CHK_NML_ACT_EX_020:
	MOV.L	#_exq_err_flg,R1		;//�ُ�ׯ�
	MOV.W	@R1,R0				; �Z���t�`�F�b�N���ɋ}��~�Ȃ�Z���t�`�F�b�N�ُ�I��
	TST	R0,R0				;
	TST_BIT_OF _SELF_CHK_ACT_EXIT		;

_SELF_CHK_NML_ACT_EX_040:
	MOV.W	#_STEP10,R2			;
	MOV.L	#_SELF_HAND_FLG1,R1		; �����̏���׸� �ُ�I�����������
	MOV.W	R2,@R1				;

_SELF_CHK_ACT_EXIT:

	SUB_END
	M_RTS






;	************************************
;	*** �Z���t�n�m�`�F�b�N�C�j�V���� ***
;	************************************
_SELF_ONCHECK_INIT:
	SUB_START

	XOR	R0,R0				;
	MOV.L	#_SELF_FSTY_USE,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_SELF_RSTY_USE,R1		;
	MOV.W	R0,@R1				;

;	*** CH�M��ON ***
;	*CHK,CH0,1,2
	_MC_CH0_ON_WK1	R1,R2,R3		; VSER
	_MC_CHK_ON_WK1	R1,R2,R3		;

	MOV.W	#(BIT7+BIT0),R5			; �V�[�P���XON 208.7,208.0

	_MC_CH1_OF_WK1	R1,R2,R3		;
	_MC_CH2_OF_WK1	R1,R2,R3		;

;	================= 2012-12-05 �s��C��=====
	FAR_JSR	#_SELFCHK_SFTY_CONFCHK,R0	;


	TST	R0,R0
	TST_BIT_OF _SELF_ONCHK_INIT_010		;���܂łƓ�������
	CMP/EQ	#1,R0				;�L��
	BT	_SELF_ONCHK_INIT_015		;LABEL�ǉ��@2012-12-05
	M_BRA	_SELF_ONCHK_INIT_040		;-1����

_SELF_ONCHK_INIT_010:
;	------------------2012-12-05�}��---------------

	MOV.L	#(_SEQAB_DP_TOP+_SQ200),R1	; DP 2008-09-15 ���S���u�����Ȃ�`�F�b�N�M���n�m���Ȃ�
	MOV.W	@R1,R0				;
	MOV.W	#(BIT13+BIT12),R2		;
	AND	R2,R0				;
	MOV.W	#BIT13,R2			;
	CMP/EQ	R0,R2				;
	BF	_SELF_ONCHK_INIT_040		; ���� THEN JUMP

_SELF_ONCHK_INIT_015:				;LABEL�ǉ��@2012-12-05

	MOV.L	#(_SEQAB_DP_TOP+_SQ028),R1	; DPRAM 2008-07-30 SAITO
	MOV.W	@R1,R0				;
	MOV.W	#BIT0,R2			;
	TST	R2,R0				;
	TST_BIT_OF _SELF_ONCHK_INIT_020		; �Z���t�`�F�b�N�I���Ȃ� THEN JUMP
	_MC_CH1_ON_WK1	R1,R2,R3		; FSFTY
	MOV.W	#BIT2,R2			;
	OR	R2,R5				; �V�[�P���XON 208.2
	FAR_JSR	#_FRCYCL_ON,R0			; *FCYCL,RCYCL OF �L��
	MOV.W	#H'FFFF,R0			;
	MOV.L	#_SELF_FSTY_USE,R1		;
	MOV.W	R0,@R1				; �O���S���u�`�F�b�N�L��

_SELF_ONCHK_INIT_020:
	MOV.L	#(_SEQAB_DP_TOP+_SQ028),R1	; DPRAM 2008-07-30 SAITO
	MOV.W	@R1,R0				;
	MOV.W	#BIT7,R2			;
	TST	R2,R0				;
	TST_BIT_OF _SELF_ONCHK_INIT_040		; �Z���t�`�F�b�N�I���Ȃ� THEN JUMP
	_MC_CH2_ON_WK1	R1,R2,R3		; RSFTY
	MOV.W	#BIT3,R2			;
	OR	R2,R5				; �V�[�P���XON 208.3
	FAR_JSR	#_FRCYCL_ON,R0			; *FCYCL,RCYCL OF �L��
	MOV.W	#H'FFFF,R0			;
	MOV.L	#_SELF_RSTY_USE,R1		;
	MOV.W	R0,@R1				; ����S���u�`�F�b�N�L��
_SELF_ONCHK_INIT_040:

;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;	*** �V�[�P���XON ***
;	*CHK,CH0,1,2
	MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
	MOV.W	R5,@R1				; SEQ WK RAM SET


	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	#_SELF_CHK_TM,R2		;
	MOV.W	R2,@R1				; SELF CHECK TIMER SET


	SUB_END
	M_RTS


;
;		2012-12-05
;	=== ���S���u���͂𐧓������Ɏg�p����ꍇ������
;	0:���S���u���͂Ŏg�p(1�ȊO) 1:���������Ɏg�p����
;78 _PAR_FSWFUN_SEL		.DATA.W		1		;1�ȊO:���S���u�L������SW�^1:�����������[�hSW
;79 _PAR_FSWSEL_MASK	.DATA.W		0		;1�ȊO:���S���u�L���Œ�/1:���S���u����
;	78 ,79
;	0  , *    -->���s��SW�ɏ]��
;       1  , 0    -->���Œ�
;       1  , 1    -->���Ȃ��Œ�
;	ANS
;	OUTPUT R0=0 ���܂łƓ����@�r�v�Q��
;	OUTPUT R0=1 �r�v�͎Q�Ƃ��Ȃ����L��
;	OUTPUT R0=-1 ����

_SELFCHK_SFTY_CONFCHK
	SUB_START

	MOV.L	#_PAR_FSWFUN_SEL,R1		;
	MOV.W	@R1,R0				;SW�̈Ӗ����قȂ�?
	CMP/EQ	#1,R0				;
	BF	SELF_CYCLON_INF100		;1�ȊO(0)

	MOV.L	#_PAR_FSWSEL_MASK,R1		;1�ȊO:���S���u�L���Œ�/1:���S���u����
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	SELF_CYCLON_INF200		;1�ł͂Ȃ�(0)���B�L��

	MOV.W	#-1,R0				;
	M_BRA	SELF_CYCLON_INFEND		;


SELF_CYCLON_INF100
	XOR	R0,R0				;���܂ł̃\�t�g
	M_BRA	SELF_CYCLON_INFEND		;

SELF_CYCLON_INF200
	MOV.W	#1,R0				;
SELF_CYCLON_INFEND

	SUB_END
	M_RTS


;	**************************
;	*** �Z���t�n�m�`�F�b�N ***
;	**************************
;	VSER���ł邱�ƁA�Ռ��������邱��
_SELF_ON_CHECK:
	SUB_START

	XOR	R10,R10					;
;	*** VSER CHECK ***
	MOV.L	#(_IOGA1_CTRL_DAT1+_IOGAi_PB),R1	;
	MOV.W	@R1,R1					;
	MOV.W	#BIT0,R2				;
	TST	R2,R1					; VSER CHK
	TST_BIT_OF _SELF_ON_CHK_EXIT			; VSER�������Ȃ� THEN EXIT
	MOV.W	#BIT0,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

;	*** �O���S���u�Ռ��`�F�b�N ***
_SELF_ON_CHK_FSFT:
	MOV.L	#_SELF_FSTY_USE,R1			;
	MOV.W	@R1,R0					; �O���S���u�`�F�b�N�L��`�F�b�N
	TST	R0,R0					;
	TST_BIT_ON _SELF_ON_CHK_FSFT020			; �`�F�b�N�L�� THEN JUMP
	MOV.W	#BIT1,R0				;
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	M_BRA	_SELF_ON_CHK_RSFT			;

_SELF_ON_CHK_FSFT020:
	FAR_JSR	#_SLF_FSTY_CHK,R0			; �Ռ��`�F�b�N
	MOV.W	#H'00FF,R1				;
	CMP/EQ	R1,R0					;
	BF	_SELF_ON_CHK_EXIT			; �Ռ�����Ȃ� THEN EXIT
	MOV.W	#BIT1,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

_SELF_ON_CHK_RSFT:
	MOV.L	#_SELF_RSTY_USE,R1			;
	MOV.W	@R1,R0					; �O���S���u�`�F�b�N�L��`�F�b�N
	TST	R0,R0					;
	TST_BIT_ON _SELF_ON_CHK_RSFT020			; �`�F�b�N�L�� THEN JUMP
	MOV.W	#BIT2,R0				; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	M_BRA	_SELF_ON_CHK_EXIT			;

_SELF_ON_CHK_RSFT020:
	FAR_JSR	#_SLF_RSTY_CHK,R0			; �Ռ��`�F�b�N
	MOV.W	#H'00FF,R1				;
	CMP/EQ	R1,R0					;
	BF	_SELF_ON_CHK_EXIT			; �Ռ�����Ȃ� THEN EXIT
	MOV.W	#BIT2,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

_SELF_ON_CHK_EXIT:			;
	SUB_END
	M_RTS


;	**************************************
;	*** �Z���t�n�e�e�`�F�b�N�C�j�V���� ***
;	**************************************
_SELF_OFCHECK_INIT:
	SUB_START

;	*** CH�M��OFF ***
;	*CHK,CH0,1,2
	_MC_CHK_OF_WK1	R1,R2,R3		; 2003-01-23
	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
	_MC_CH1_OF_WK1	R1,R2,R3		; 2003-01-23
	_MC_CH2_OF_WK1	R1,R2,R3		; 2003-01-23
;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

	FAR_JSR	#_FRCYCL_OF,R0			; *FCYCL,RCYCL ON ����

	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	#_SELF_CHK_TM,R2		;
	MOV.W	R2,@R1				; SELF CHECK TIMER SET

	SUB_END
	M_RTS


;	****************************
;	*** �Z���t�n�e�e�`�F�b�N ***
;	****************************
_SELF_OF_CHECK:
	SUB_START

	XOR	R10,R10					;
;	*** VSER CHECK ***
	MOV.L	#(_IOGA1_CTRL_DAT1+_IOGAi_PB),R1	;
	MOV.W	@R1,R1					;
	MOV.W	#BIT0,R2				;
	TST	R2,R1					; VSER CHK
	TST_BIT_ON _SELF_OF_CHK_EXIT			; VSER�������Ȃ� THEN EXIT
	MOV.W	#BIT0,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

;	*** �O���S���u�Ռ��`�F�b�N ***
_SELF_OF_CHK_FSFT:
	MOV.L	#_SELF_FSTY_USE,R1			;
	MOV.W	@R1,R0					; �O���S���u�`�F�b�N�L��`�F�b�N
	TST	R0,R0					;
	TST_BIT_ON _SELF_OF_CHK_FSFT020			; �`�F�b�N�L�� THEN JUMP
	MOV.W	#BIT1,R0				; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	M_BRA	_SELF_OF_CHK_RSFT			;

_SELF_OF_CHK_FSFT020:
	FAR_JSR	#_SLF_FSTY_CHK,R0			; �ʌ��`�F�b�N
;;;;;	MOV.W	#H'000F,R1				;
	MOV.W	#H'0000,R1				; 2003-01-23 SAITO
	CMP/EQ	R1,R0					;
	BF	_SELF_OF_CHK_EXIT			; �Ռ�����Ȃ� THEN EXIT
	MOV.W	#BIT1,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

_SELF_OF_CHK_RSFT:
	MOV.L	#_SELF_RSTY_USE,R1			;
	MOV.W	@R1,R0					; �O���S���u�`�F�b�N�L��`�F�b�N
	TST	R0,R0					;
	TST_BIT_ON _SELF_OF_CHK_RSFT020			; �`�F�b�N�L�� THEN JUMP
	MOV.W	#BIT2,R0				; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET
	M_BRA	_SELF_OF_CHK_EXIT			;

_SELF_OF_CHK_RSFT020:
	FAR_JSR	#_SLF_RSTY_CHK,R0			; �ʌ��`�F�b�N
;;;;;	MOV.W	#H'000F,R1				;
	MOV.W	#H'0000,R1				; 2003-01-23 SAITO
	CMP/EQ	R1,R0					;
	BF	_SELF_OF_CHK_EXIT			; �Ռ�����Ȃ� THEN EXIT
	MOV.W	#BIT2,R0				; OK CODE SET
	OR	R0,R10					; �`�F�b�N�Ȃ��Ȃ�OK CODE SET

_SELF_OF_CHK_EXIT:

	SUB_END
	M_RTS


;	**********************************
;	*** �Z���t�`�F�b�N����I������ ***
;	**********************************
_SELF_CHK_NMLEND:
	SUB_START

	_MC_CHK_OF_WK1	R1,R2,R3		; 
	_MC_CH0_OF_WK1	R1,R2,R3		; 2003-01-23
	_MC_CH1_OF_WK1	R1,R2,R3		;
	_MC_CH2_OF_WK1	R1,R2,R3		;
;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;;;;2006-04-26	XOR	R5,R5				;
;;;;		MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
;;;;		MOV.W	R5,@R1				; SEQ WK RAM CLEAR

	SUB_END
	M_RTS



;	**********************************
;	*** �Z���t�`�F�b�N�ُ�I������ ***
;	**********************************
_SELF_CHK_ERREND:
	SUB_START

	_MC_CHK_OF_WK1	R1,R2,R3		; 
	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
	_MC_CH1_OF_WK1	R1,R2,R3		;
	_MC_CH2_OF_WK1	R1,R2,R3		;

;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

	XOR	R5,R5				;
	MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
	MOV.W	R5,@R1				; SEQ WK RAM CLEAR

	SUB_END
	M_RTS






;	***********************************
;	***	�O���S���u����		***
;	***********************************
;	R0=00H 	FACT=FDEV=�ʌ�
;	R0=0FH	FACT:�Ռ� FEDV=�ʌ�
;	R0=F0H  FACT:�ʍs FDEV=�Ռ� �L�蓾�Ȃ�
;	R0=FFH	FACT=FDEV=�Ռ�
_SLF_FSTY_CHK:
	SUB_START

	XOR	R0,R0			;

	MOV.L	#_FACT_IN_DATA,R1			;
	MOV.W	@R1,R2					; FACT���ް�
	MOV.L	#_FDEV_IN_DATA,R1			;
	MOV.W	@R1,R3					; FDEV���ް�
	SHLL2	R3					;
	SHLL2	R3					;
	OR	R3,R2					;
	MOV.W	#(BIT4+BIT0),R4				;
	AND	R4,R2					;
	MOV.W	#0,R4					;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK020			;

	MOV.W	#H'00FF,R0				; FACT=FDEV=L THEN �Ռ�
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK020:
	MOV.W	#BIT0,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK040			;

	MOV.W	#H'00F0,R0				; FACT=�ʌ��AFDEV=�Ռ� ���肦�Ȃ��g�ݍ��킹
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK040:
	MOV.W	#BIT4,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK060			;

	MOV.W	#H'000F,R0				; FACT=�Ռ��AFDEV=�ʌ�
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK060:
	MOV.W	#(BIT4+BIT0),R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK080			;

	M_BRA	_SLF_FSTY_CHK_EXIT			; FACT=FDEV=�ʌ�

_SLF_FSTY_CHK080:
_SLF_FSTY_CHK_EXIT:
	SUB_END
	M_RTS

;	***********************************
;	***	�O���S���u����		***
;	***********************************
;	R0=00H 	FACT=FDEV=�ʌ�
;	R0=0FH	FACT:�Ռ� FEDV=�ʌ�
;	R0=F0H  FACT:�ʍs FDEV=�Ռ� �L�蓾�Ȃ�
;	R0=FFH	FACT=FDEV=�Ռ�
_SLF_RSTY_CHK:
	SUB_START

	XOR	R0,R0			;

	MOV.L	#_RACT_IN_DATA,R1			;
	MOV.W	@R1,R2					; RACT���ް�
	MOV.L	#_RDEV_IN_DATA,R1			;
	MOV.W	@R1,R3					; RDEV���ް�
	SHLL2	R3					;
	SHLL2	R3					;
	OR	R3,R2					;
	MOV.W	#(BIT4+BIT0),R4				;
	AND	R4,R2					;
	MOV.W	#0,R4					;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK020			;

	MOV.W	#H'00FF,R0				; RACT=RDEV=L THEN �Ռ�
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK020:
	MOV.W	#BIT0,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK040			;

	MOV.W	#H'00F0,R0				; RACT=�ʌ��ARDEV=�Ռ� ���肦�Ȃ��g�ݍ��킹
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK040:
	MOV.W	#BIT4,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK060			;

	MOV.W	#H'000F,R0				; RACT=�Ռ��ARDEV=�ʌ�
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK060:
	MOV.W	#(BIT4+BIT0),R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK080			;

	M_BRA	_SLF_RSTY_CHK_EXIT			; RACT=RDEV=�ʌ�

_SLF_RSTY_CHK080:
_SLF_RSTY_CHK_EXIT:
	SUB_END
	M_RTS


;	********************************************* 2003-01-23
;	*** �Z���t�`�F�b�N�M�� �S�n�e�e CHK,CH0~2 ***
;	*** �Z���t�`�F�b�N�����~�ɂ�蒆�f��  ***
;	*********************************************
_STP_SELF_OUT_OFF:
	SUB_START

;	===== 2003-01-20 SAITO =====

	_MC_CHK_OF_WK1	R1,R2,R3		; 
	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
	_MC_CH1_OF_WK1	R1,R2,R3		;
	_MC_CH2_OF_WK1	R1,R2,R3		;

;SAITO	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;	============================

	SUB_END
	M_RTS


;;;;;;;;;;;;;;;;;;;	.AELSE
;;;;;;;;;;;;;;;;;;;;;CPUB�ł����B�B�B�폜 2010-12-27
;;;;;;;;;;;;;;;;;;;;;	.AENDI

