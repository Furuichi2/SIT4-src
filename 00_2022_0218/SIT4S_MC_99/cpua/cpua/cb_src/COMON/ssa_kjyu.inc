;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;
	.EXPORT	_KAJYUU_REFLASH
_KAJYUU_REFLASH
	SUB_START
;;2006-07-28	MOV.L	#_SVP_KAJYUU_PV1,R1		;�ő�׏d(��߼�݂̎�����C/B�̐ݒ�Ƃ��ēn��)
;;2006-07-28	MOV.W	@R1,R2				;

	MOV.L	#_PVPAB_ARA1_KAJ_T,R1		;��Ԃł̍ő�׏d(��߼�݂̎�����C/B�̎����Ƃ��ēn��)
	MOV.L	@R1,R2				;(���������ް�)

	MOV.L	#_KJYUU_IN_DAT_PV,R1		;//2byte->4byte
	MOV.L	R2,@R1				;


;?????????????????????? �ǂ�����
;;;;;;;;;2015-04-09	MOV.L	#_PVP_KAJLIV_TTL,R1		;//�׏d���iTON�j(2word)
;;;;;;;;;2015-04-09	MOV.W	@R1,R6				;2byte

	MOV.L	#_PVPAB_KAJLIV_TTL,R1		;
	MOV.L	@R1,R6				;4byte

;------- ���ޯ��̍ۂ�R6�����ւ���----------------
;;;;;;;;;	MOV.L	#_DEBUG_MOD_CODE,R1			;
;;;;;;;;;	MOV.W	@R1,R0					;
;;;;;;;;;	MOV.W	#H'5AA5,R1				;
;;;;;;;;;	CMP/EQ	R1,R0					;D=1234 ���¼��ݽ
;;;;;;;;;	BF	KAJYUU_RF_DBGCHG010			;
;;;;;;;;;	MOV.L	#_PV_AD_DATA,R1				;
;;;;;;;;;	MOV.W	@R1,R6					;
;;;;;;;;;KAJYUU_RF_DBGCHG010					;
;--------------------------------------------------
	CMP/PZ	R6
	BT	KAJYUU_RF150
	XOR	R6,R6			;
KAJYUU_RF150

	MOV.L	#_W4_PVP_KAJLIV_TTL,R1		;//�׏d���iTON�j(2word)
	MOV.L	R6,@R1				;

	FAR_JSR	#_KAJYUU_IDO_FILTER,R0		;

	SUB_END
	M_RTS







	.IMPORT	_IDO_BUF_SRC2B_TOTAL_4B_CAL	

_KAJYUU_IDO_FILTER
	SUB_START

	MOV.L	#_W4_PVP_KAJLIV_TTL,R1					;//�׏d���iTON�j(2word)
	MOV.L	@R1,R2							;(+�̂�)

	MOV.L	#(_PAR_KJYU_IDOSEL-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;4 �׏d���䎞�̈ړ����ω�0,1��1��[R01 2014-03-14]
	MOV.W	@R1,R0							;
	TST	R0,R0							;
	TST_BIT_OF KAJYUU_IDOFLT_100					;
	CMP/EQ	#1,R0							;
	BT	KAJYUU_IDOFLT_100					;

	MOV.W	#D'50,R4						;
	CMP/HI	R4,R0							;
	BT	KAJYUU_IDOFLT_100					;50<R0

	MOV	R0,R4							;���ό� MAX(2~50)
	MOV.L	#_KAJLIV_TTL_TOTAL,R5					;
	MOV.L	#_KAJLIV_TTL_IDOBUF,R0					;
	MOV.L	#_KAJLIV_TTL_POINT,R3					;
	FAR_JSR	#_IDO_BUF_SRC2B_TOTAL_4B_CAL,R1				;

	EXTS.W	R2,R2							;

KAJYUU_IDOFLT_100

	MOV.L	#_W4_PV_FLT_KJYU_TTL,R1		;//̨���l[��׽�̂�]
	MOV.L	R2,@R1				;

	CMP/PZ	R2
	BT	KAJYUU_IDOFLT_200
	XOR	R2,R2				;

KAJYUU_IDOFLT_200
	MOV.L	#_W4_PV_FLT_KJYU_TTL_P,R1	;//̨���l[��׽�̂�]
	MOV.L	R2,@R1				;

	MOV.L	#_W4_PV_CTL_KJYU_TTL_P,R1	;//����l=̨���l�\��
	MOV.L	R2,@R1				;

;	----------- �U������p(2015-04-10)------------
	MOV.L	#_WPVX_KAJLIV_TTL,R1		;
	MOV.W	R2,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	****		�ُ��ؾ�Ď�		***
;	*******************************************
	.EXPORT	_KJPHOS_SIG_CLR	;2004-07-05
_KJPHOS_SIG_CLR:
	SUB_START
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB209,R1	;
	MOV.W	@R1,R4				;
	MOV.W	#LWORD ~(BIT9+BIT8),R3		;
	AND	R3,R4				;
	MOV.W	R4,@R1				;
	SUB_END
	M_RTS

;	***********************************
;	***	�������Ă����ݒ背�x��	***
;	***********************************
	.EXPORT	_KJPHOS_CHECK	;2004-07-05(ssa_kjyu.inc)
_KJPHOS_CHECK:
	SUB_START

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT7,R0			;
	TST_BIT_ON KJPHOS_CHKCEXT		;

	FAR_JSR	#_KJPHOS_SIG_CLR,R0		;
	FAR_JSR	#_KJPHOS_FLG_DEF,R0		;

KJPHOS_CHKCEXT:
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	���_���A������
;	�␳��
	.EXPORT		_KJPHOS_FLG_DEF		;2004-07-05(ssa_kjyu.inc)
_KJPHOS_FLG_DEF:
	SUB_START
	XOR	R0,R0				;
	MOV.L	#_KJPHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	R0,@R1				;
	SUB_END
	M_RTS


;	*******************************************
;	****		1CYCLE �J�n		***
;	*******************************************
;	===	1CYCLE�J�n	===
;	��]Ӱ�ށE�����A����A�A���AOPT
;	KJPHOS_USE_FLG
;	BIT0:�����ݸޗL��
;	BIT1:WAIT��������:DEF�����ݸޒ�
;	BIT2:DEF����:�ʏ������ݸޒ�
;	BIT3:INI�ž�ā@END�Ÿر�@�Q��END���Ă΂�邱�Ƃ�h��
;	BIT4:�L���Ȉʒu�����o����
;	BIT6:�����ݸޗL����Ӱ�ޏ��
;
;	���_���Ƀt���O�N���A
;
;	�N�����E1CYCL�J�n(SMPINI)	BIT6=1 set Ӱ��+��]
;					BIT0=1 BIT6=1�Ŋ��␳SW����
;					BIT4=1 ���肷�ׂ���Ԃɓ�����
;
	.EXPORT	_KJPHOS_SMPINI	
_KJPHOS_SMPINI:
	SUB_START

	MOV.L	#_MODE_SEL,R1								;
	MOV.W	@R1,R0									;
	TST	#_W1CNT+_W1SGL+_W1INC+_W1OPT,R0						;
	TST_BIT_OF KJPHOS_CHK100							;

	MOV.L	#_CPOS_CTL_MATH,R1							;
	MOV.W	@R1,R0									;
;;[2009-10-07���U�q]	TST	#_DMATH_CNTROT,R0					;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0	;_DMATH_CNTROT,R0		;[2009-10-07���U�q]
	TST_BIT_OF KJPHOS_CHK100							;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJPHOS_USE_FLG,LG=W,BIT=BIT6,WKREG=R4		;
	M_BRA	KJPHOS_CHK200								;
KJPHOS_CHK100:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJPHOS_USE_FLG,LG=W,BIT=~(BIT6+BIT3),WKREG=R4	;
KJPHOS_CHK200:


;	==================================
	MOV.L	#_KJPHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;�����ݸޗL��Ӱ��?
	TST_BIT_ON KJPHOS_SMP_INI1_050		;
	M_BRA	KJPHOS_SMP_INI1_EXT		;����

KJPHOS_SMP_INI1_050

	TST	#BIT2,R0			;
	TST_BIT_ON KJPHOS_SMP_INI1_300		;�����ް������ݸފ���=�ʏ������ݸޒ�
	TST	#BIT1,R0			;
	TST_BIT_ON KJPHOS_SMP_INI1_200		;WAIT�񐔊���=�����ް��쐬��
	TST	#BIT0,R0			;
	TST_BIT_ON KJPHOS_SMP_INI1_100		;�Ƽ�ي����@�L��

	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT7,R0			;341.7=1�׏d�̕␳���Z����
	TST_BIT_OF KJPHOS_SMP_INI1_EXT		;�␳�� EXIT

	MEM1_TO_MEM2 MEM1=_WPAR_DRVHOS_WAITCNT,L1=W,MEM2=_KJPHOS_WAIT_CNT_PV,L2=W,WKREG1=R1,WKREG2=R2
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJPHOS_USE_FLG,LG=W,BIT=BIT0,WKREG=R4	;bit-set

KJPHOS_SMP_INI1_100

	MOV.L	#_KJPHOS_WAIT_CNT_PV,R1			;
	MOV.W	@R1,R2					;
	TST	R2,R2					;
	TST_BIT_ON KJPHOS_SMP_INI1_END			;

;	=== MODE CHECK(���������E�ʏ������ݸޑO����) ==
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJPHOS_USE_FLG,LG=W,BIT=BIT1,WKREG=R4	;
	MEM1_TO_MEM2 MEM1=_WPAR_DRVHOS_AVLCNT,L1=W,MEM2=_KJPHOS_DEF_CNT_PV,L2=W,WKREG1=R1,WKREG2=R2	;
	XOR	R2,R2											;
	FAR_JSR	#_KJPHOS_IDO_AVL_INI,R0									;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJPHOS_USE_FLG,LG=W,BIT=~BIT4,WKREG=R4			;BIT4=0 ����̈斢
	M_BRA	KJPHOS_SMP_INI1_END									;

KJPHOS_SMP_INI1_200:						;WAIT�񐔊���=�����ް������ݸޒ�
KJPHOS_SMP_INI1_300:						;�����ް������ݸފ�����=�ʏ������ݸޒ�
KJPHOS_SMP_INI1_400:
KJPHOS_SMP_INI1_END
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJPHOS_USE_FLG,LG=W,BIT=BIT3,WKREG=R4	;�N������
KJPHOS_SMP_INI1_EXT
	SUB_END
	M_RTS


;	***************************
;	***			***
;	***	������		***
;	***	2004-07-05	***
;	***	CHEAK OK!	***
;	***************************
;	Input R2�őS�Ẵo�t�@�𖄂߂�
;	R2=0
;
_KJPHOS_IDO_AVL_INI:
	SUB_START
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON KJPHOS_IDO_AVLINI_040	;
	MOV.W	#1,R0
KJPHOS_IDO_AVLINI_040:
	MOV	R0,R4				;data push

	MOV.L	#_KJPHOS_IDO_BUF,R5		;
KJPHOS_IDO_AVLINI_100:
	MOV.L	R2,@R5				;
	ADD	#4,R5				;
	ADD	#-1,R0				;
	TST	R0,R0				;
	TST_BIT_ON KJPHOS_IDO_AVLINI_100	;

	DMULS.L	R4,R2				;
	STS.L	MACL,R2				;
	MOV.L	#_KJPHOS_IDO_TOTAL,R1		;
	MOV.L	R2,@R1				;R2*R4

	XOR	R0,R0
	MOV.L	#_KJPHOS_IDO_POINT,R1		;//�ޯ̧�Ǘ��߲��
	MOV.W	R0,@R1				;

;	==== 20061204(2003-07-14)==
	XOR	R0,R0
	MOV.L	#_KJPHOS_IDO_CNT,R1	;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
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
	.EXPORT	_KJPHOS_SAMPLING1
_KJPHOS_SAMPLING1:
	SUB_START

	MOV.L	#_KJPHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	AND	#(BIT6+BIT3+BIT1+BIT0),R0	;BIT3:�N������
	CMP/EQ	#(BIT6+BIT3+BIT1+BIT0),R0	;
	BT	KJPHOS_SAMPLE1_020		;�L����Ӱ�ނŊ��»����ݸމ\����
	M_BRA	KJPHOS_SAMPLE1_EXT		;

KJPHOS_SAMPLE1_020:				;
;	�׏d�v�̃^�C�~���O�ɕύX
;	==== �͈����� ======
	MOV.L	#_CTL_ENC360,R4			;//360.0�x
	MOV.W	@R4,R2				;
	MOV.L	#_WPAR_DRVHOS_DIG1,R4		;//0.1�x(165.0):Ӱ����ݺ��ފp�x�Ŕ�r
	MOV.W	@R4,R1				;START
	MOV.L	#_WPAR_DRVHOS_DIG2,R4		;
	MOV.W	@R4,R3				;
	FAR_JSR	#_DIG_AREA_CHK1,R0		;R1~R3�̒��ɂ��邩
	CMP/PL	R5				;
	BF	KJPHOS_SAMPLE1_EXT		;NO!   R5=0/R5<0
;	===================

	MOV.L	#_KJPHOS_USE_FLG,R5		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R5,R0				;
	TST	#BIT4,R0			;
	TST_BIT_ON KJPHOS_SAMPLE1_100		;
	OR	#BIT4,R0			;
	MOV.W	R0,@R5				;
	M_BRA	KJPHOS_SAMPLE1_EXT		;(���肷�ׂ��̈�ɓ�����)

KJPHOS_SAMPLE1_100:				;
;	=== �ő�׏d�̻����ݸނ̓I�v�V����========
KJPHOS_SAMPLE1_EXT:				;
	SUB_END
	M_RTS

;	***************************
;	***			***
;	***	�ړ�����	***
;	***			***
;	***************************
;	MOV.L	#_KJPHOS_MOST_DN_RNAPOS,R1	;//�ŉ����_��WORK(175~359) 175�x����̫�Ă��쐬
;	MOV.L	@R1,R2				;R2:data
;	MOV.L	#_KJPHOS_IDO_TOTAL,R5		;
;	MOV.L	#_KJPHOS_IDO_BUF,R6		;
;	MOV.L	#_KJPHOS_IDO_POINT,R7		;//�ޯ̧�Ǘ��߲��
;	Input LOAD R2:data
;	Input R3:SYSPARAM
;	R5:4B-TOTAL-ADR
;	R6:4B-BUF-ADR
;	R7:2B-POINTER-ADR
;	
;	ANS R2=TOTAL
;_IDO_AVL4B_MAK1:



;	***********************************
;	***				***
;	***	1CYCLE�I��		***
;	***				***
;	***********************************
;	===	1CYCLE�I��	===
	.EXPORT	_KJPHOS_SMPLING_END1
_KJPHOS_SMPLING_END1
	SUB_START

;	===2003-06-06[1-3]  BIT4�̸ر�ύX===
	MOV.L	#_KJPHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R14				;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJPHOS_USE_FLG,LG=W,BIT=~BIT4,WKREG=R1	;BIT4=0 ����̈斢
;	====================================

	MOV.L	#_KJPHOS_USE_FLG,R1			;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0					;
	AND	#(BIT6+BIT3+BIT0),R0			;
	CMP/EQ	#(BIT6+BIT3+BIT0),R0			;BIT3:�J�n����
	BT	KJPHOS_SMP_END1_020			;
	M_BRA	KJPHOS_SMP_END1_EXT			;
KJPHOS_SMP_END1_020:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJPHOS_USE_FLG,LG=W,BIT=~BIT3,WKREG=R4	;//�J�n������ʉ߂������H


;	==================================
	MOV.L	#_KJPHOS_USE_FLG,R1		;//BIT2=1 BIT1=1,BIT0=1 �␳�ް����g�p���Ă�����
	MOV.W	@R1,R0				;
	TST	#(BIT2+BIT1),R0			;
	TST_BIT_ON KJPHOS_SMP_END1_100		;�����ް��쐬��or�ʏ��ް��쐬��
	MOV.L	#_KJPHOS_WAIT_CNT_PV,R5		;
	MOV.W	@R5,R2				;
	TST	R2,R2				;
	TST_BIT_OF KJPHOS_SMP_END1_050		;
	ADD	#-1,R2				;
	MOV.W	R2,@R5				;
KJPHOS_SMP_END1_050:				;
	M_BRA	KJPHOS_SMP_END1_EXT		;

;	====== �����ݸޗL�苤�� =========
KJPHOS_SMP_END1_100:

	MOV.W	#BIT4,R2			;
	TST	R2,R14				;
	TST_BIT_ON KJPHOS_SMP_END1_120		;�����ݸ��ް��L��
	M_BRA	KJPHOS_SMP_END1_EXT		;

KJPHOS_SMP_END1_120:

	PUSH_REG1 R0				;KJPHOS_USE_FLG
	MOV.L	#_KJYUU_IN_DAT_PV,R1		;
	MOV.L	@R1,R2				;R2:indata
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_KJPHOS_IDO_TOTAL,R5		;
	MOV.L	#_KJPHOS_IDO_BUF,R6		;
	MOV.L	#_KJPHOS_IDO_POINT,R7		;//�ޯ̧�Ǘ��߲��
	FAR_JSR	#_IDO_AVL4B_MAK1,R0		;�o�t�@�ւ�SAVE��İ��(R2)�̂ݍ쐬

;	============== 20061204(2003-07-14) ============
	MOV.L	#_KJPHOS_IDO_CNT,R5		;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	@R5,R0				;
	ADD	#1,R0				;
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R4				;
	CMP/HI	R4,R0				;
	BT	KJPHOS_SMP_END1_150		;R4(10)<11
	MOV.W	R0,@R5				;R4(10)>=R0 0,1~10
KJPHOS_SMP_END1_150				;
;	=======================================20061204([2003-07-14])

	POP_REG1 R0				;
	TST	#BIT2,R0			;�ʏ풆?
	TST_BIT_ON KJPHOS_SMP_END1_300		;YES

;	==== ���������ݸޒ� ==========
	MOV.L	#_KJPHOS_DEF_CNT_PV,R5					;(�͂��߂�10��E�ړ������ް����ł���܂�)
	MOV.W	@R5,R0							;
	TST	R0,R0							;
	TST_BIT_OF KJPHOS_SMP_END1_EXT					;
	ADD	#-1,R0							;
	MOV.W	R0,@R5							;
	TST	R0,R0							;
	TST_BIT_OF KJPHOS_SMP_END1_200					;(�I������u��)
;;;20061204	TST_BIT_ON KJPHOS_SMP_END1_EXT					;

;	�����񐔒�(���ω�)
;	===== 20061206(2003-07-14)===
	FAR_JSR	#_KJP_DEF_PVMAK,R0	;
	M_BRA	KJPHOS_SMP_END1_EXT	;

KJPHOS_SMP_END1_200:
;	==(���������ݸފ���)==
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJPHOS_USE_FLG,LG=W,BIT=BIT2,WKREG=R4	;
	FAR_JSR	#_KJPHOS_DATA_SERCH,R0						;ANS R2
	MOV.L	#_KJYUU_DEF_DAT_PV,R1						;
	MOV.L	R2,@R1								;�͂��߂�10���ް�
	MOV.L	#_KJYUU_NEW_DAT_PV,R1						;//4byte
	MOV.L	R2,@R1								;
	M_BRA	KJPHOS_SMP_END1_EXT						;

KJPHOS_SMP_END1_300:
;	==2006-12-05 NEW ===
	MOV.W	#BIT0,R0
	MOV.L	#_PRD_KJP_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
	MOV.W	R0,@R1				;BIT0=0�����\

	FAR_JSR	#_KJPHOS_DATA_SERCH,R0						;ANS R2
	MOV.L	#_KJYUU_NEW_DAT_PV,R1						;//4byte
	MOV.L	R2,@R1								;

	FAR_JSR	#_KJYUU_CMP_SEQ_MAK,R0	;��r

;;;;2007-11-26	MEM1_TO_MEM2 MEM1=_KJYUU_IN_DAT_PV	,L1=L	,MEM2=_DBG4_MONI_A02,L2=L,WKREG1=R1,WKREG2=R2

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;2006-11-21
	MEM1_TO_MEM2 MEM1=_KJYUU_NEW_DAT_PV	,L1=L	,MEM2=_PVP_ARA1_KAJ_T2,L2=W,WKREG1=R1,WKREG2=R2
	.AENDI


KJPHOS_SMP_END1_EXT:			;
	SUB_END
	M_RTS

;	***********************************
;	***	�����f�[�^�쐬		***
;	***********************************
;	ANS.R2= (_KJPHOS_CAL_RNA_POS) �X�V
_KJPHOS_DATA_SERCH:
	SUB_START

	MOV.L	#_WPAR_DRVHOS_NO_USE,R1				;
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_ON KJPHOS_DNDAT_SRCH100				;���g�p��0? NO
	XOR	R8,R8						;
	FAR_JSR	#_KJPHOS_IDO_AVL_CALC,R0			;���g�p��0 ������R8(=0)
	M_BRA	KJPHOS_DNDAT_SRCH_EXT				;

KJPHOS_DNDAT_SRCH100:
	CMP/EQ	#1,R0						;
	BF	KJPHOS_DNDAT_SRCH200				;
;	=======================================
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_KJPHOS_IDO_BUF,R6		;
	FAR_JSR	#_MAX1_MIN1_SERCH,R0		;MAX1+MIN1�̌��ʂ������Ă��� R8
	FAR_JSR	#_KJPHOS_IDO_AVL_CALC,R0	;
	M_BRA	KJPHOS_DNDAT_SRCH_EXT		;

KJPHOS_DNDAT_SRCH200:
	CMP/EQ	#2,R0						;
	BF	KJPHOS_DNDAT_SRCH300				;

	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1		;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R3				;
	MOV.L	#_KJPHOS_IDO_BUF,R6		;
	FAR_JSR	#_MAX2_MIN2_SERCH,R0		;MAX1+MAX2+MIN1+MIN2�̌��ʂ������Ă��� R8
	FAR_JSR	#_KJPHOS_IDO_AVL_CALC,R0	;
	M_BRA	KJPHOS_DNDAT_SRCH_EXT		;

KJPHOS_DNDAT_SRCH300:
;	======= �ɂȂ�m���t���[�ɐݒ肵���ꍇ�̱ٺ�ؽ�тɂ��� ======
	XOR	R8,R8						;
	FAR_JSR	#_KJPHOS_IDO_AVL_CALC,R0			;
	M_BRA	KJPHOS_DNDAT_SRCH_EXT				;


KJPHOS_DNDAT_SRCH_EXT:
	MOV.L	#_KJPHOS_CAL_PRS,R1	;
	MOV.L	R2,@R1			;
	SUB_END
	M_RTS





;	*******************************************************************
;	***								***
;	***		���Z						***
;	***		(TOTAL-MAX1-MIN1-MAX2-MIN2-...)/AVL-2*NOUSE	***
;	***								***
;	*******************************************************************
;	Input R8:MAX+MIN or MAX1+MAX2+MIN1+MIN2 or 0
_KJPHOS_IDO_AVL_CALC:
	SUB_START
	MOV.L	#_KJPHOS_IDO_TOTAL,R1				;
	MOV.L	@R1,R2						;
	SUB	R8,R2						;
	MOV.L	#_WPAR_DRVHOS_AVLCNT,R1				;//�ړ����ς̌��f�[�^��
	MOV.W	@R1,R4						;
	MOV.L	#_WPAR_DRVHOS_NO_USE,R1				;
	MOV.W	@R1,R0						;
	ADD	R0,R0						;
	SUB	R0,R4						;
	TST	R4,R4						;
	TST_BIT_OF KJPHOS_IDO_AVLCAL050				;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
KJPHOS_IDO_AVLCAL050:						;

	SUB_END
	M_RTS


;	*******************************************
;	***	���ω񐔂ɒB����܂ł̕\��	***
;	*******************************************
_KJP_DEF_PVMAK:
	SUB_START
;;;	MOV.W	#BIT0,R0
;;;	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
;;;	MOV.W	R0,@R1				;

;	==2006-12-05 NEW ===
	MOV.W	#BIT0,R0
	MOV.L	#_PRD_KJP_CMP_ENB,R1		;//BIT0=1:��r ��r�s��
	MOV.W	R0,@R1				;BIT0=0�����\

	MOV.L	#_KJYUU_IN_DAT_PV,R1
	MOV.L	@R1,R2					;

	MOV.L	#_KJPHOS_IDO_CNT,R1			;//�ړ����ω񐔂��Ă�1��,2��,,,�ł����ς��o����悤�ɂ���
	MOV.W	@R1,R4					;
	TST	R4,R4					;
	TST_BIT_OF KJP_DEFPVMK_END			;���Z���ʂȂ�/�ŉ����_(���肦�Ȃ�?)

	MOV.L	#_KJPHOS_IDO_TOTAL,R1				;
	MOV.L	@R1,R2						;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;TOTAL/

KJP_DEFPVMK_END:
	MOV.L	#_KJYUU_NEW_DAT_PV,R1
	MOV.L	R2,@R1					;
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;2006-11-21
	MEM1_TO_MEM2 MEM1=_KJYUU_NEW_DAT_PV	,L1=L	,MEM2=_PVP_ARA1_KAJ_T2,L2=W,WKREG1=R1,WKREG2=R2
	.AENDI
	SUB_END
	M_RTS


;	***************************
;	***	���ݽ��r	***
;	***************************
_KJYUU_CMP_SEQ_MAK:
	SUB_START
	MOV.L	#_SVP_KAJYUU_OBJP,R1		;�׏d�ڕW�l 1Kn(2004-07-01)
	MOV.W	@R1,R3				;
	EXTU.W	R3,R3				;

	MOV.L	#_SVP_KAJYUU_PRS1,R1		;�׏d�␳ 1Kn (2004-06-08)
	MOV.W	@R1,R4				;
	EXTU.W	R4,R4				;
	
	MOV	R3,R5				;
	ADD	R4,R5				;OBJ+HOS=R5
	SUB	R4,R3				;OBJ-HOS=R3

	XOR	R0,R0				;BIT8/BIT9
	MOV.L	#_KJYUU_NEW_DAT_PV,R1		;//4byte
	MOV.L	@R1,R2				;
	EXTU.W	R2,R2				;
	CMP/GT	R5,R2				;OBJ+HOS < R2
	BF	KJYUU_CMP_SEQMK_050		;
	MOV.W	#BIT9,R0			;
	M_BRA	KJYUU_CMP_SEQMK_100		;
KJYUU_CMP_SEQMK_050:				;
	CMP/GE	R3,R2				;OBJ-HOS =< R2
	BT	KJYUU_CMP_SEQMK_100		;
	MOV.W	#BIT8,R0			;

KJYUU_CMP_SEQMK_100:

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB209,R1	;
	MOV.W	@R1,R4				;
	MOV.W	#LWORD ~(BIT9+BIT8),R3		;
	AND	R3,R4				;
	OR	R0,R4				;
	MOV.W	R4,@R1				;

	SUB_END
	M_RTS




	.EXPORT	_KAJYUU_BAKUP_INIT_DISP
_KAJYUU_BAKUP_INIT_DISP:
	SUB_START
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;2006-11-21
	MOV.L	#_SVB_ARA1_KAJ_T2,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_KJYUU_NEW_DAT_PV,R1		;
	MOV.L	R2,@R1					;
	MEM1_TO_MEM2 MEM1=_KJYUU_NEW_DAT_PV	,L1=L	,MEM2=_PVP_ARA1_KAJ_T2,L2=W,WKREG1=R1,WKREG2=R2
	.AENDI
	SUB_END
	M_RTS
