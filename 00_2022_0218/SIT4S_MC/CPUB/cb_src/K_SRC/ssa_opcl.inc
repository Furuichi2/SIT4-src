
	.GLOBAL		_PAR_COP_CNTROT_ZDG1	;+10.0�x
	.GLOBAL		_CB_SYS_PARAM081	;��] ��ے��I��    =�׏d����J�n�p�x
	.GLOBAL		_PAR_COP_CNTROT_ZDG2	;+20.0�x
	.GLOBAL		_CB_SYS_PARAM082	;��] �׏d����J�n�p�x
	.GLOBAL		_PAR_COP_CNTROT_SDG1	;+20.0�x
	.GLOBAL		_CB_SYS_PARAM083	;��] �׏d����J�n�I��
	.GLOBAL		_PAR_COP_CNTROT_SDG2	;230.0�x
	.GLOBAL		_CB_SYS_PARAM084	;���] ��ے��J�n�p�x   +N
	.GLOBAL		_PAR_COP_REVRSE_ZDG1	;5.0�x
	.GLOBAL		_CB_SYS_PARAM085	;���] ��ے��J�n�I��   +M
	.GLOBAL		_PAR_COP_REVRSE_ZDG2	;15.0�x
	.GLOBAL		_CB_SYS_PARAM086	;���] �׏d����J�n�p�x+N 
	.GLOBAL		_PAR_COP_REVRSE_SDG1	;�ҋ@�_+5.0�x�����؂����p�x
	.GLOBAL		_CB_SYS_PARAM087	;���] �׏d����J�n�I��+M
	.GLOBAL		_PAR_COP_REVRSE_SDG2	;�ҋ@�_+5.0�x�����؂����p�x:�ŏI�H���ȍ~
	


	.EXPORT	_COP1_ROT_DT_INI
	
	.IMPORT	_ATOB_KJYUALL_SMPCLR		
	.IMPORT	_ATOB_KJYUALL_SMPSTART		;
	.IMPORT	_ATOB_KJYUTRD_SMPCLR		;CPUA=>CPUB 1: CPUB=0CLR CPUB��0�ر����
	.IMPORT	_ATOB_KJYUTRD_SMPSTART		;CPUA= 0->1 1->0         CPUB�͎Q�Ƃ̂�

;	*******************************************
;	***					***
;	***	�ް��]�� �����g��		***
;	***	2Bor4B-->2B/4B			***
;	*******************************************
;;	.MACRO	DATA_STD_SHN_MOV	SRC,L1,DST,L2
;;	MOV.L	#\SRC,R5		;
;;	MOV.\L1	@R5,R2			;
;;
;;	MOV.L	#\DST,R6		;
;;	MOV.\L2	R2,@R6			;
;;	.ENDM
;;
;;	.MACRO	DATA_STD_CHG_MOV	SRC,L1,DST,L2,CALLSB
;;	MOV.L	#\SRC,R8						;
;;	MOV.\L1	@R8,R2							;
;;
;;	FAR_JSR	#\CALLSB,R0		;
;;
;;	MOV.L	#\DST,R9		;
;;	MOV.\L2	R2,@R9			;
;;	.ENDM


_COP1_ROT_DT_INI:
	SUB_START
	FAR_JSR	#_CB_COP_DT_MAK1,R0
	FAR_JSR	#_CB_COP_DT_MAK2,R0

	MOV.L	#_INC_ENC360,R1		;//360.0�x(�ݺ��ނ͕\���Ɠ���)
	MOV.W	@R1,R2			;
;;;���g�p	MOV.L	#_COP_ENC3600,R1	;
;;;���g�p	MOV.W	R2,@R1			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	R2,@R1			;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT0),WKREG=R1

;	SH4-->SH2�֓n���@2010-12-08
	MEM_MOV_TO_MEM	SRC_ADR=_COP_CB_LD_MONI_SIG,L1=W,DST_ADR=_DP_COP_CB_LD_MONI_SIG,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3


	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	���Ұ�			***
;	***	��ݸ�ݒ�Ƃ���		***
;	***	�S�đҋ@�_�{�ň���	***
;	***				***
;	***********************************


_CB_COP_DT_MAK1:
	SUB_START
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_ZDG1,L1=W,DST=_WPAR_COP_CNTROT_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_ZDG2,L1=W,DST=_WPAR_COP_CNTROT_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_SDG1,L1=W,DST=_WPAR_COP_CNTROT_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_SDG2,L1=W,DST=_WPAR_COP_CNTROT_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_ZDG1,L1=W,DST=_WPAR_COP_REVRSE_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_ZDG2,L1=W,DST=_WPAR_COP_REVRSE_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_SDG1,L1=W,DST=_WPAR_COP_REVRSE_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_SDG2,L1=W,DST=_WPAR_COP_REVRSE_SDG2,L2=W


	SUB_END
	M_RTS

;	===================================
;	===				===
;	===	���쎞�̓���ւ�	===
;	===				===
;	===================================
;	�ҋ@�_�{�ݒ�ɕϊ�����
_CB_COP_DT_MAK2:
	SUB_START

;	=========[2009-10-07���U�q]
	MOV.L	#_SET1_MRTION_SEL1,R1						;
	MOV.W	@R1,R0								;
	TST	#(_DMATH_DNDRIV),R0						;2007-09-06
	TST_BIT_ON CB_COP_DT_MK2_010						;
	M_BRA	CB_COP_DT_MK2_050						;

CB_COP_DT_MK2_010						;

;	-------���H-------
;	���]���ް����g�p����
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPARX_COP_DNDRV1_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPARX_COP_DNDRV1_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPARX_COP_DNDRV1_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPARX_COP_DNDRV1_SDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;

;	-------���H-------
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPARX_COP_DNDRV2_ZDG1,L2=W,CALLSB=_NEG_TAIKI_SUB;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPARX_COP_DNDRV2_ZDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPARX_COP_DNDRV2_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPARX_COP_DNDRV2_SDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;


;	-- 2007-09-06 [�׏d�␳][�ӂ肱���H]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETX_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETX_KJEND_DIG1,L2=W;

;	-----------------------[�ӂ肱���H]
	DATA_STD_CHG_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETY_KJSTR_DIG1,L2=W,CALLSB=_NEG_TAIKI;
	DATA_STD_CHG_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETY_KJEND_DIG1,L2=W,CALLSB=_NEG_TAIKI;



;	-- 2014-05-30 --[�����][�ӂ肱���H]
;;;;;2014-10-10�s�	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
;;;;;2014-10-10�s�	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETX_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETX_KJEND_DIG2,L2=W;

;	-----------------------[�ӂ肱���H]
	DATA_STD_CHG_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETY_KJSTR_DIG2,L2=W,CALLSB=_NEG_TAIKI;
	DATA_STD_CHG_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETY_KJEND_DIG2,L2=W,CALLSB=_NEG_TAIKI;
	M_BRA	CB_COP_DT_MK2_200



CB_COP_DT_MK2_050:
;;[2009-10-07���U�q]	MOV.L	#_SET1_MRTION_SEL1,R1	;
;;[2009-10-07���U�q]	MOV.W	@R1,R0			;
	CMP/EQ	#_DMATH_CNTROT,R0	;DRIVE MATH �A����]
	BF	CB_COP_DT_MK2_100	;NO:���]

;	------- ��](�ҋ@�_0�����炢������)-------
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W,CALLSB=_TAIKI_ADD;

;	-- 2009-10-07 --[�׏d�␳][��]]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

;	-- 2014-05-30 --[�����][��]]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;

	M_BRA	CB_COP_DT_MK2_200	

CB_COP_DT_MK2_100:
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W,CALLSB=_TAIKI_ADD;

;	-- 2009-10-07 --[�׏d�␳][���]]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

;	-- 2014-05-30 --[�����][���]]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;

CB_COP_DT_MK2_200:

	SUB_END
	M_RTS

;	***************************
;	***	�ҋ@�_+data	***
;	***************************
;	
_TAIKI_ADD;
	SUB_START
	MOV.L	#_SETX_UPAREA_DIG,R1					;2;��]/���]���ҋ@�_
	MOV.W	@R1,R0							;
	DIG_REGA_ADD_REGB_ANS_REGB REGA=R0,REGB=R2,WKREG=R1,LATE=3600	;R0+R2==>R2
	SUB_END
	M_RTS

;	***************************
;	***	2009-10-07���U�q***
;	***************************
;	Input +R2
_NEG_TAIKI_SUB;
	SUB_START

	MOV.L	#_SETX_UPAREA_DIG,R1					;2;��]/���]���ҋ@�_
	MOV.W	@R1,R1							;
	MOV.W	#3600,R0						;
	SUB	R1,R0							;
	DIG_REGA_SUB_REGB_ANS_REGB REGA=R2,REGB=R0,WKREG=R1,LATE=3600	;R0=R0-R2
	MOV	R0,R2							;

	SUB_END
	M_RTS

;	***************************
;	***	2009-10-07���U�q***
;	***************************
;	Input +R2
_NEG_TAIKI;
	SUB_START

	MOV.W	#3600,R0						;
	SUB	R2,R0							;
	MOV	R0,R2							;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	�f�[�^����ւ�			***
;	***	2009-10-07	���U�q		***
;	*******************************************
_SIG_AREA_DATA_CHG:
	SUB_START
	MOV.L	#_DNM_DIR_SET_FLG,R1			;
	MOV.W	@R1,R0					;
	MOV.L	#_DNM_DIR_FLG_OLD,R1			;
	MOV.W	@R1,R2					;
	MOV.W	R0,@R1					;
	XOR	R2,R0					;CHG DIRECTION
	TST	R0,R0					;
	TST_BIT_OF SIG_AREA_DATCHG050			;

	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=~(BIT2+BIT1),WKREG=R1				;BIT1:���M��
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)),WKREG=R1	;2006-07-28

SIG_AREA_DATCHG050:

	MOV.L	#_SET1_MRTION_SEL1,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;
	TST_BIT_OF SIG_AREA_DATCHG100			;

	M_BRA	SIG_AREA_DATCHG500			;

SIG_AREA_DATCHG100:

	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON SIG_AREA_DATCHG120			;
	M_BRA	SIG_AREA_DATCHG200			;

SIG_AREA_DATCHG120:
	MOV.L	#_DNM_DIR_SET_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_ON SIG_AREA_DATCHG150

;-------- ���H-------
	DATA_STD_SHN_MOV	SRC=_SETX_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETX_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_SETX_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETX_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
	M_BRA	SIG_AREA_DATCHG190


SIG_AREA_DATCHG150:
	DATA_STD_SHN_MOV	SRC=_SETY_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETY_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_SETY_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETY_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
SIG_AREA_DATCHG190:
	M_BRA	SIG_AREA_DATCHG500			;

SIG_AREA_DATCHG200:


SIG_AREA_DATCHG500:



	SUB_END
	M_RTS

;	***************************
;	***			***
;	***************************
;
;	�H��=1~MAX
;	0:�I���׸�,0:�J�n�׸�
;
;	//���_���A�ł͂��Ȃ�
;	//RESET�������ɲƼ�ُ������s��:�I����� BIT1=0(�����ݸފJ�n�L���̈Ӗ�)
;	//
;
;	(1)�ׯ��ɉ^�]�J�n���������
;	(2)���f
;	(3)����
;
;	��]
;	�J�n���� :�^�]�J�n+�p�xa�`�p�xb
;	�I������ :�p�xB��cw�ŉ��؂���

;	���]
;	�J�n���� :�^�]�J�n+�p�xa�`�p�xb
;	�I������ :�ŏI�H���Ŋ��p�xa���ҋ@�_���ɂ���
;
;	=========================
;	COP_CB_LD_MONI_SIG;//�׏d����p�M�� 2003-01-31
;	BIT0=1 �펞ON
;	BIT1=1 �[�������p�x
;	BIT2=1 �׏d����p�x
;	BIT3=1 �׏d���芮��
;	(BIT4)=1 ��ے�����
;	BIT5=1 ACTIVE
;	*��ے����M�����׏d�����D�悷��B
;
;	[�����,�ő�l,�ŏ��l,�������ݸ�]--->226.13
;	KJ_AREATRD_SIG�F_KAJYUU_AREA2_SIGMAK
;		BIT0:1:�w��ʒu��
;		BIT1:1:����J�n(�s���܂�)�`�T�C�N���I��
;		BIT2:1:����I��
;		BIT3
;		BIT4
;		BIT5:����J�n(BIT1�Ɠ���)~����I��()
;		BIT6:1:�I���`�T�C�N���I��
;		BIT7
;
;	[�׏d�␳]	----->226.5������΂悢
;	_KJ_AREA_SIG�F�F_KAJYUU_AREA1_SIGMAK
;		BIT0:1:�w��ʒu��
;		BIT1:1:����J�n(�s���܂�)�`�T�C�N���I��
;		BIT2:1:����I��
;		BIT3
;		BIT4
;		BIT5:����J�n(BIT1�Ɠ���)~����I��()
;		BIT6:1:�I���`�T�C�N���I��
;		BIT7
;


	.EXPORT	_CB_COP_SIG_MAK	
_CB_COP_SIG_MAK:		;
	SUB_START

	FAR_JSR	#_SIG_AREA_DATA_CHG,R0	;[2009-10-07���U�q]

	MOV.L	#_INC_ENC360,R1		;//360.0�x(�ݺ��ނ͕\���Ɠ���)
	MOV.W	@R1,R2			;
	MOV	R2,R8			;R8:NOW
;;;���g�p	MOV.L	#_COP_ENC3600,R1	;
;;;���g�p	MOV.W	R2,@R1			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	@R1,R9			;R9:OLD
;;;;�������ݸނ���گ���͂��Ȃ�	MOV.W	R2,@R1			;

	MOV.L	#_SEQAB_DP_TOP+109*2,R1		;
	MOV.W	@R1,R0				;109.12
	MOV.W	#BIT12,R4			;
	TST	R4,R0				;
	TST_BIT_ON CB_COP_SIGMK_100		;

	MOV.W	#BIT0,R0			;
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;�׏d���肵�Ȃ�
	MOV.W	R0,@R1				;BIT0=1(�펞)
	
	XOR	R0,R0				;
	MOV.L	#_COP_DIG_SIG_FLG,R1		;
	MOV.W	R0,@R1				;
	
;	------ 2006-07-28----
	XOR	R0,R0				;
	MOV.L	#_KJ_AREA_SIG,R1;
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;2013-06-19
	MOV.W	R0,@R1				;

	MOV.L	#_KJ_AREATRD_SIG,R1
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1;//2013-06-19
	MOV.W	R0,@R1				;

	M_BRA	CB_COP_SIGMK_EXT		;


;	*******************************************
;	***					***
;	***	�^�]�E��^�]�Ɋւ�炸�s��	***
;	***					***
;	*******************************************
;	Z-DIG1:CW�ŉ��؂�����ONor���
;	Z-DIG2:CW�ŉ��؂�����OFF+����
;	S-DIG1:CW�ŉ��؂�����ONor���(�ҋ@�_)
;	S-DIG2:CW�ŉ��؂�����OFF+����(�ҋ@�_)
;	==========================
;	Z-DIG1:CW�ŉ��؂�����ONor���
;	Z-DIG2:CW�ŉ��؂�����OFF+����
;	S-DIG1:CW�ŉ��؂�����ONor���(�ҋ@�_+6�x�ȏ�~180)
;	S-DIG2:CCW�ŉ��؂�����OFF+���� (�ҋ@�_+5�x�ȉ�) SDIG2<SIDG1 (SDIG2���ҋ@�_�ɋ߂�)
;
CB_COP_SIGMK_100:				;
	MOV.L	#_COP_DIG_SIG_FLG,R1				;
	MOV.W	@R1,R0						;
	TST	#BIT2,R0					;�׏d���蒆
	TST_BIT_ON CB_COP_SIGMK_120				;ZERO�����M��OFF

;	=============��ے����M���쐬====================
	MOV.L	#_WPAR_COP_ZDG1,R0							;ZERO�����J�n�p�x
	MOV.W	@R0,R1									;
	MOV.L	#_WPAR_COP_ZDG2,R0							;�I���p�x
	MOV.W	@R0,R3									;
	MOV	R8,R2									;
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0				;
	CMP/EQ	#1,R0									;
	BF	CB_COP_SIGMK_120							;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_DIG_SIG_FLG,LG=W,BIT=BIT1,WKREG=R1		;�͈͓�
	M_BRA	CB_COP_SIGMK_150							;

CB_COP_SIGMK_120:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=~BIT1,WKREG=R1		;BIT1:���M��
CB_COP_SIGMK_150:									;


;	============ �׏d�M�� ============
	MOV.L	#_SET1_MRTION_SEL1,R1		;
	MOV.W	@R1,R0				;
;;2009-10-07���U�q	CMP/EQ	#_DMATH_CNTROT,R0		;DRIVE MATH �A����]
;;2009-10-07���U�q	BF	CB_COP_SIGMK_250		;���]

	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0	;2009-10-06
	TST_BIT_OF CB_COP_SIGMK_250			;NO:���]

;	=== ��] ==
	MOV.L	#_WPAR_COP_SDG1,R0			;�׏d�J�n�p�x
	MOV.W	@R0,R1					;
	MOV.L	#_WPAR_COP_SDG2,R0			;�I���p�x
	MOV.W	@R0,R3					;
	M_BRA	CB_COP_SIGMK_280			;

;	=== ���] ==
CB_COP_SIGMK_250:
	MOV.L	#_COP_DIG_SIG_FLG,R1				;
	MOV.W	@R1,R0						;
	TST	#BIT2,R0					;ON
	TST_BIT_ON CB_COP_SIGMK_270				;

	MOV.L	#_WPAR_COP_SDG1,R0			;�׏d�J�n�p�x
	MOV.W	@R0,R1					;
	MOV.W	#_UPDN_DIRJG_DIG,R3			;"�p�x(�����ł͂Ȃ� ����)"
	M_BRA	CB_COP_SIGMK_280			;

CB_COP_SIGMK_270:
	MOV.L	#_WPAR_COP_SDG2,R0				;�I���p�x~�ҋ@�_�Ȋp�x�ێ�
	MOV.W	@R0,R1						;
	MOV.L	#_SETX_UPAREA_DIG,R0				;
	MOV.W	@R0,R3						;

CB_COP_SIGMK_280:
	MOV	R8,R2									;
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0				;
	CMP/EQ	#1,R0									;
	BF	CB_COP_SIGMK_290							;�͈͊O
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_DIG_SIG_FLG,LG=W,BIT=(BIT2),WKREG=R1		;�׏dSET
	M_BRA	CB_COP_SIGMK_300

CB_COP_SIGMK_290:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=(~BIT2),WKREG=R1		;�׏d�ر
CB_COP_SIGMK_300:


;	===== �o�͐M���쐬 ======
	MOV.L	#_COP_DIG_SIG_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT1,R0		;
	TST_BIT_ON CB_COP_SIGMK_550	;

	MOV.L	#_COP_CB_LD_MONI_SIG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT1,R0		;
	TST_BIT_OF CB_COP_SIGMK_520	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT4),WKREG=R1	;��ۊ���
CB_COP_SIGMK_520:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT1),WKREG=R1	;��۸ر
	M_BRA	CB_COP_SIGMK_580	;

CB_COP_SIGMK_550:
;;2006-07-28	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT4+BIT3+BIT2)),WKREG=R1	;��ۊ����ر
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT6+BIT5+BIT4+BIT3+BIT2)),WKREG=R1	;2006-07-28
												;��ۊ����ر
												;�׏d���蒆�ر
												;�׏d�����ر
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT1),WKREG=R1		;��ے�

;	------���ے������----
	XOR	R0,R0				;
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;2013-06-19
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG,R1
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;

;	-------------- �׏d�O���ް��ر----------
	MOV.B	#BIT0,R0			;
	MOV.L	#_ATOB_KJYUALL_SMPCLR,R1	;�ر����
	MOV.W	R0,@R1				;
	MOV.L	#_ATOB_KJYUTRD_SMPCLR,R1	;�ر����
	MOV.W	R0,@R1				;
;	-------------------------------------------




CB_COP_SIGMK_580:


	MOV.L	#_COP_DIG_SIG_FLG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;
	TST_BIT_ON CB_COP_SIGMK_650						;

	MOV.L	#_COP_CB_LD_MONI_SIG,R1							;
	MOV.W	@R1,R0									;
	TST	#BIT2,R0								;�׏d���蒆���������H
	TST_BIT_OF CB_COP_SIGMK_620							;NO
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT3),WKREG=R1	;�׏d���芮��
CB_COP_SIGMK_620:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT2),WKREG=R1	;�׏d����ر
	M_BRA	CB_COP_SIGMK_680	;

CB_COP_SIGMK_650:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT3),WKREG=R1	;�׏d�����ر
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT2),WKREG=R1	;�׏d���蒆
CB_COP_SIGMK_680:

;	------------ 2014-05-30--------------
	FAR_JSR	#_KAJYUU_AREA2_SIGMAK,R0		;

;	=========2006-07-28 BIT4,5 REFLASH========
	FAR_JSR	#_KAJYUU_AREA1_SIGMAK,R0		;


	MOV.W	#(BIT6+BIT5),R4			;
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	@R1,R0				;
	AND	#(BIT6+BIT5),R0			;
	NOT	R4,R4
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;
	MOV.W	@R1,R2				;
	AND	R4,R2				;
	OR	R0,R2				;
	MOV.W	R2,@R1				;


;	----------- ���ޯ��pBIT8~BIT15(�����--------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	SHLL8	R0				;
	EXTU.B	R2,R2				;
	OR	R0,R2				;

	MOV.L	#(_SQ_CBWK_TOP+26*2),R1		;_SQCB226.7~0=COP_CB_LD_MONI_SIG
	MOV.W	R2,@R1				;


;	---------2014-02-05 �ŏ��l,�ő�l,�������ݸ�(�׏d�v�Ɠ������ 60~270�x)--------------
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;
	TST_BIT_ON KAJYUU_MIN_SMP100		;[�S�̂̑���J�n�w�ߒ��@29~238�x]

	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1	;�����ݸގw��OFF
	MOV.W	@R1,R2				;
	TST	R2,R2
	TST_BIT_OF KAJYUU_MIN_SMP250		;

	XOR	R2,R2				;
	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1	;�����ݸގw��OFF
	MOV.W	R2,@R1				;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJYU_CMP_CMD,LG=W,BIT=BIT1,WKREG=R1	;BIT1�I�������u��
	M_BRA	KAJYUU_MIN_SMP250		;

KAJYUU_MIN_SMP100

	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1		;�����ݸގw��
	MOV.W	@R1,R2				;
	TST	R2,R2				;�ȑO��OFF��������
	TST_BIT_ON KAJYUU_MIN_SMP200		;NO ON


	MOV.W	#BIT0,R3			;
	MOV.L	#_ATOB_KJYUALL_SMPCLR,R4	;�ر����
	MOV.W	R3,@R4				;

	MOV.W	#BIT0,R2			;����J�n����
	MOV.W	R2,@R1				;
	M_BRA	CB_COP_SIGMK_EXT		;

;
KAJYUU_MIN_SMP200
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJYU_CMP_CMD,LG=W,BIT=BIT0,WKREG=R1	;BIT0 ��r���




KAJYUU_MIN_SMP250:
CB_COP_SIGMK_EXT:


	MOV.L	#_INC_ENC360,R1		;//360.0�x(�ݺ��ނ͕\���Ɠ���)
	MOV.W	@R1,R2			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	R2,@R1			;


	FAR_JSR	#_KAJYUU_DEBUG_ANACHG,R0	;�����Ă������͂��Ȃ�

	FAR_JSR	#_KAJYUU_OVER_LOW_CHK,R0	;


	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***	�{���͍H�����Ǘ����Ȃ��Ƃ����Ȃ�	***
;	***						***
;	***************************************************
;	BIT0=1 AREA��
;	BIT1=1 START�ɓ������܂��͍H����������
;	BIT2=1 END�𒴂����܂��͔͈͊O�ɂȂ���
;	CLR �H��MAX~�H��1�ɂȂ���
;
;	[�׏d�␳���]
;
_KAJYUU_AREA1_SIGMAK:
	SUB_START
	MOV.L	#_SETC_KJSTR_DIG1,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R1								;
	MOV.L	#_INC_ENC360,R4							;
	MOV.W	@R4,R2								;

	MOV.L	#_SETC_KJEND_DIG1,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R3			
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BF	KAYJUU_AREA1SIGMK050						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT0),WKREG=R1	;AREA-ON
	M_BRA	KAYJUU_AREA1SIGMK090						;
KAYJUU_AREA1SIGMK050:								;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT0),WKREG=R1	;
KAYJUU_AREA1SIGMK090:								;


;	-------- �J�n����----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA1SIGMK200						;

	MOV.L	#_SET1_KJSTR_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA1SIGMK130						;0:POS

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA1SIGMK190						;�H��=0
	
	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREA1SIGMK150						;
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA1SIGMK190						;

KAYJUU_AREA1SIGMK130:								;
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT0,R0							;
	TST_BIT_OF KAYJUU_AREA1SIGMK190						;
KAYJUU_AREA1SIGMK150:								;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT5+BIT1),WKREG=R1	;AREA-ON
KAYJUU_AREA1SIGMK190:								;
	M_BRA	KAYJUU_AREA1SIGMK900						;

KAYJUU_AREA1SIGMK200:
;	-------- �I������----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA1SIGMK290						;(����I��,���̻��ّ҂�)


;;;;	MOV.L	#_SET1_KJEND_STEP1,R1						;
;;;;	MOV.W	@R1,R0								;
;;;;	TST	R0,R0								;
;;;;	TST_BIT_ON KAYJUU_AREA1SIGMK220						;POS�ȊO
;;;;
;;;;
;;;;	MOV.L	#_SET1_MRTION_SEL1,R4						;
;;;;	MOV.W	@R4,R0								;
;;;;	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0				;��]or�ӂ肱��
;;;;	TST_BIT_OF KAYJUU_AREA1SIGMK240						;���]
;;;;
;;;;;	--------��]�܂��͂ӂ肱�̈ʒu�J��--------------
;;;;	MOV.L	#_KJ_AREA_SIG,R1		;
;;;;	MOV.W	@R1,R0				;
;;;;	TST	#BIT0,R0			;�ʒu�͈�?
;;;;	TST_BIT_OF KAYJUU_AREA1SIGMK250		;�ʒu�͈͂���o��CLR
;;;;	M_BRA	KAYJUU_AREA1SIGMK290		;


;----------�H���w��-------------
KAYJUU_AREA1SIGMK220:
	MOV.L	#_SET1_KJEND_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA1SIGMK230						;

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA1SIGMK290						;�H��=0

	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREA1SIGMK250						;�I��

	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA1SIGMK290						;

KAYJUU_AREA1SIGMK230:
	MOV.L	#_SET1_MRTION_SEL1,R4				;
	MOV.W	@R4,R0						;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;��]or�ӂ肱��
	TST_BIT_OF KAYJUU_AREA1SIGMK240				;���]
	NOP
KAYJUU_AREA1SIGMK240:						;
;	-------- �ʒu�J���܂��͍H���J���̌��s�H��-------------
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON KAYJUU_AREA1SIGMK290		;ON���Ă���

	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ON���Ă���
	TST_BIT_ON KAYJUU_AREA1SIGMK250		;
	M_BRA	KAYJUU_AREA1SIGMK290		;

;	------------���]�̏ꍇ����----------------
;;;;KAYJUU_AREA1SIGMK240:
;;;;
;;;;	MOV.L	#_COP_OLD_ENC3600,R0			;
;;;;	MOV.W	@R0,R4					;
;;;;	MOV.L	#_SETC_KJEND_DIG1,R0			;�E�E�E�E
;;;;	MOV.W	@R0,R2					;
;;;;	MOV.L	#_INC_ENC360,R0				;�t��]�ŉ��؂�����;
;;;;	MOV.W	@R0,R1			
;;;;
;;;;	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
;;;;	CMP/EQ	#1,R0								;
;;;;	BT	KAYJUU_AREA1SIGMK250						;
;;;;	M_BRA	KAYJUU_AREA1SIGMK290						;
KAYJUU_AREA1SIGMK250:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT5),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT6+BIT2),WKREG=R1	;END SET
KAYJUU_AREA1SIGMK290:								;
	NOP
KAYJUU_AREA1SIGMK900				;

KAYJUU_AREA1SIGMKEXT
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;


	SUB_END
	M_RTS








;	***************************************************
;	***						***
;	***	�{���͍H�����Ǘ����Ȃ��Ƃ����Ȃ�	***
;	***						***
;	***************************************************
;	BIT0=1 AREA��
;	BIT1=1 START�ɓ������܂��͍H����������
;	BIT2=1 END�𒴂����܂��͔͈͊O�ɂȂ���
;	CLR �H��MAX~�H��1�ɂȂ���
;
;	[�g�����h���]
;
_KAJYUU_AREA2_SIGMAK:
	SUB_START
	MOV.L	#_SETC_KJSTR_DIG2,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R1								;
	MOV.L	#_INC_ENC360,R4							;
	MOV.W	@R4,R2								;

	MOV.L	#_SETC_KJEND_DIG2,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R3			
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BF	KAYJUU_AREA2SIGMK050						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT0),WKREG=R1	;AREA-ON
	M_BRA	KAYJUU_AREA2SIGMK090						;
KAYJUU_AREA2SIGMK050:								;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREATRD_SIG,LG=W,BIT=(~BIT0),WKREG=R1	;
KAYJUU_AREA2SIGMK090:								;


;	-------- �J�n����----
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA2SIGMK200						;

	MOV.L	#_SET1_KAJAREA_SNO,R1						;�J�n�H��
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK130						;0:POS

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA2SIGMK190						;�H��=0

	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREA2SIGMK150						;
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA2SIGMK190						;

KAYJUU_AREA2SIGMK130:									;
	MOV.L	#_KJ_AREATRD_SIG,R1							;
	MOV.W	@R1,R0									;
	TST	#BIT0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK190							;
KAYJUU_AREA2SIGMK150:									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT5+BIT1),WKREG=R1	;BIT1,BIT5:�H���Ŋ��p�xON
KAYJUU_AREA2SIGMK190:									;
	M_BRA	KAYJUU_AREA2SIGMK900							;

KAYJUU_AREA2SIGMK200:
;	-------- �I������----
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA2SIGMK290						;�I���@���̃T�C�N���҂�


;----------�H���w��-------------
KAYJUU_AREA2SIGMK220:
	MOV.L	#_SET1_KAJAREA_ENO,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK230						;

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA2SIGMK290						;�H��=0
	
	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREA2SIGMK250						;CLR
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA2SIGMK290						;

KAYJUU_AREA2SIGMK230:
	MOV.L	#_SET1_MRTION_SEL1,R4				;
	MOV.W	@R4,R0						;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;��]or�ӂ肱��
	TST_BIT_OF KAYJUU_AREA2SIGMK240				;���]
	NOP
KAYJUU_AREA2SIGMK240:						;
;	-------- �ʒu�J���܂��͍H���J���̌��s�H��-------------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON KAYJUU_AREA2SIGMK290		;ON���Ă���

	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ON���Ă���
	TST_BIT_ON KAYJUU_AREA2SIGMK250		;
	M_BRA	KAYJUU_AREA2SIGMK290		;

KAYJUU_AREA2SIGMK250:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREATRD_SIG,LG=W,BIT=(~BIT5),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT6+BIT2),WKREG=R1	;END SET
KAYJUU_AREA2SIGMK290:								;
	NOP
KAYJUU_AREA2SIGMK900				;

KAYJUU_AREA2SIGMKEXT
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;



;	---------2014-02-05 �ŏ��l,�ő�l,�������ݸ�(�׏d�v�Ɠ������ 60~270�x)--------------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;�I��?
	TST_BIT_ON KAYJUU_AREA2SMP050		;
	TST	#BIT1,R0			;
	TST_BIT_ON KAYJUU_AREA2SMP100		;�J�n? YES JUMP

KAYJUU_AREA2SMP050
	XOR	R2,R2				;
	MOV.L	#_ATOB_KJYUTRD_SMPSTART,R1	;�����ݸގw��OFF
	MOV.W	R2,@R1				;
	M_BRA	KAYJUU_AREA2SMP200		;

KAYJUU_AREA2SMP100
	MOV.L	#_ATOB_KJYUTRD_SMPSTART,R1		;�����ݸގw��
	MOV.W	@R1,R2				;
	TST	R2,R2				;�ȑO��OFF��������
	TST_BIT_ON KAYJUU_AREA2SMP200		;NO ON


	MOV.W	#BIT0,R3			;
	MOV.L	#_ATOB_KJYUTRD_SMPCLR,R4		;�ر����
	MOV.W	R3,@R4				;

	MOV.W	#BIT0,R2			;����J�n����
	MOV.W	R2,@R1				;

KAYJUU_AREA2SMP200

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	�S�̋�Ԃɑ΂����r
;	�ő�l�A�ŏ��l(ϲŽ�ő�),���ɑ΂��Ĕ�r���s���B
;	�ő�l�̏ꍇ�̵���۰��,۱�ЯĂ͉׏d�v���s��.
;	�ŏ��l(ϲŽ�ő�),���l�ɑ΂��čs���B
;	SW=0000,0001(�ő�l��r)
;	SW=0000,0010(�ŏ��l��r)
;	SW=0000,0100(����r)
;
;	.GLOBAL	_KJYU_CMP_CMD;		//BIT0=1 :����۰�ޔ�r(��ԓ�) BIT1=1۱�ЯĔ�r(��ԉ�)
;	.GLOBAL	_KJYU_CMP_SELSW1;	//BIT0,BIT1(),BIT2()
;	.GLOBAL	_KJYU_CMP_SELSW2;	//BIT0,BIT1(),BIT2()
;	.GLOBAL	_KJYU_CMP_SEQMINS;	//�ŏ��l(ϲŽ��) ����BIT0(��),BIT1(�E),BIT2(���v)
;	.GLOBAL	_KJYU_CMP_SEQHABA;	//��             ����BIT0(��),BIT1(�E),BIT2(���v)


_KAJYUU_OVER_LOW_CHK
	SUB_START
	MOV.L	#_di1_cb_ctl1_dt,R1			;���قɕύX
	MOV.W	@R1,R0					;
	MOV.W	#_W1RST,R4				;ؾ�Ėt
	TST	R4,R0					;
	TST_BIT_OF KAJYUU_OVER_LOWCHK100		;
	XOR	R0,R0					;ؾ��:���ݽ�ر
	MOV.L	#_KJYU_CMP_SEQMINS,R1			;
	MOV.W	R0,@R1					;
	MOV.L	#_KJYU_CMP_SEQHABA,R1			;
	MOV.W	R0,@R1					;
	MOV.L	#_KJYU_CMP_CMD,R1			;
	MOV.W	R0,@R1					;
	M_BRA	KAJYUU_OVER_LOWCHKEXT			;

KAJYUU_OVER_LOWCHK100

	MOV.L	#_KJYU_CMP_CMD,R5			;
	MOV.W	@R5,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF KAJYUU_OVER_LOWCHK200		;BIT0=1:����۰�ދ��
	AND	#LOW ~BIT0,R0				;
	MOV.W	R0,@R5					;


	FAR_JSR	#_KAJYU_OVERLOAD_CHK,R0			;


KAJYUU_OVER_LOWCHK200

	MOV.L	#_KJYU_CMP_CMD,R5			;
	MOV.W	@R5,R0					;
	TST	#BIT1,R0				;
	TST_BIT_OF KAJYUU_OVER_LOWCHK300		;BIT1=1:۱�Яċ��
	AND	#LOW ~BIT1,R0				;
	MOV.W	R0,@R5					;


	FAR_JSR	#_KAJYU_LOWLIMIT_CHK,R0			;


KAJYUU_OVER_LOWCHK300
KAJYUU_OVER_LOWCHKEXT

	MOV.L	#_KJYU_CMP_SEQMINS,R1		;��r�M�����
	MOV.W	@R1,R0				;
	EXTU.W	R0,R0
	MOV.L	#_KJYU_CMP_SEQHABA,R1		;
	MOV.W	@R1,R2				;
	SHLL8	R2
	OR	R2,R0
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB250,R1	;250
	MOV.W	R0,@R1				;



	SUB_END
	M_RTS


;_BTOA_LFT_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
;_BTOA_LFT_HAB		.SRES	4	;

;_BTOA_RIH_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
;_BTOA_RIH_HAB		.SRES	4	;

;_BTOA_TTL_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
;_BTOA_TTL_HAB		.SRES	4	;

;	-------------- �ŏ�(ϲŽ�ő�)�I���� ����۰��,۱�Я� ��,���v,�E
	.IMPORT		_SVP_OVERE1_A27			; �׏d�v�@�I�[�o�[���[�h�P �@�i�ŏ��l�j
	.IMPORT		_SVP_ROALM1_A27			; �׏d�v�@���A�[���b�~�g�P  �@�i�ŏ��l�j
	.IMPORT		_SVP_OVERE2_A27			; �׏d�v�@�I�[�o�[���[�h�Q  �@�i�ŏ��l�j
	.IMPORT		_SVP_ROALM2_A27			; �׏d�v�@���A�[���b�~�g�Q  �@�i�ŏ��l�j
	.IMPORT		_SVP_OVERE3_A27			; �׏d�v�@�I�[�o�[���[�h�R  �@�i�ŏ��l�j
	.IMPORT		_SVP_ROALM3_A27			; �׏d�v�@���A�[���b�~�g�R  �@�i�ŏ��l�j

;	-------------- �U���I���� ����۰��,۱�Я� ��,���v,�E
	.IMPORT		_SVP_OVERE1_A28			; �׏d�v�@�I�[�o�[���[�h�P �@�i�U���j
	.IMPORT		_SVP_ROALM1_A28			; �׏d�v�@���A�[���b�~�g�P  �@�i�U���j
	.IMPORT		_SVP_OVERE2_A28			; �׏d�v�@�I�[�o�[���[�h�Q  �@�i�U���j
	.IMPORT		_SVP_ROALM2_A28			; �׏d�v�@���A�[���b�~�g�Q  �@�i�U���j
	.IMPORT		_SVP_OVERE3_A28			; �׏d�v�@�I�[�o�[���[�h�R  �@�i�U���j
	.IMPORT		_SVP_ROALM3_A28			; �׏d�v�@���A�[���b�~�g�R  �@�i�U���j

;	--------�S���(����۰��,��Яėp)-------------------
	.IMPORT		_BTOA_LFT_MAX		;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
	.IMPORT		_BTOA_LFT_MIN		;
	.IMPORT		_BTOA_LFT_HAB		;

	.IMPORT		_BTOA_RIH_MAX		;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
	.IMPORT		_BTOA_RIH_MIN		;
	.IMPORT		_BTOA_RIH_HAB		;

	.IMPORT		_BTOA_TTL_MAX		;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
	.IMPORT		_BTOA_TTL_MIN		;
	.IMPORT		_BTOA_TTL_HAB		;


;	*******************************************
;	***					***
;	***	����۰��			***
;	***					***
;	*******************************************
_KAJYU_OVERLOAD_CHK:
	SUB_START


;;	MOV.L	#_KJYU_CMP_SELSW1,R1		;
	MOV.L	#_CB_SEQ_SW_SEL058,R1		;00
	MOV.W	@R1,R0				;
	SHLR8	R0				;BIT9,BIT8=00,01,10
	AND	#(BIT1+BIT0),R0			;

	CMP/EQ	#BIT0,R0			;�ŏ��׏d(ϲŽ�ő�?)
	BT	KAJYU_OVERLOADCK_100		;
	CMP/EQ	#BIT1,R0			;��?
	BT	KAJYU_OVERLOADCK_200		;

;	------- �ő�׏d(COP1Z) --------------------------
;	------- �ŏ��׏d(ϲŽ�ő�?),���M���͸ر-----------
	MOV.L	#_KJYU_CMP_SEQMINS,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;

	MOV.L	#_KJYU_CMP_SEQHABA,R5
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;
	M_BRA	KAJYU_OVERLOADCK_EXT		;


;	------- �ŏ��׏d(ϲŽ�ő�?)-----
KAJYU_OVERLOADCK_100:


	XOR	R8,R8				;SEQ
	MOV.W	#BIT0,R7			;
	MOV.L	#_BTOA_LFT_MIN,R5		;4B�����t
	MOV.L	#_SVP_OVERE1_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�P �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;

	MOV.W	#BIT1,R7			;
	MOV.L	#_BTOA_RIH_MIN,R5		;4B�����t
	MOV.L	#_SVP_OVERE2_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�Q  �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;

	MOV.W	#BIT2,R7			;
	MOV.L	#_BTOA_TTL_MIN,R5		;4B�����t
	MOV.L	#_SVP_OVERE3_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�R  �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;��r�M�����
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;���M���͸ر
	M_BRA	KAJYU_OVERLOADCK_EXT		;

;	------- ���M��-----------
KAJYU_OVERLOADCK_200:

	XOR	R8,R8				;SEQ
	MOV.W	#BIT0,R7			;
	MOV.L	#_BTOA_LFT_HAB,R5		;4B�����t
	MOV.L	#_SVP_OVERE1_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�P �@�i���j
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;

	MOV.W	#BIT1,R7			;
	MOV.L	#_BTOA_RIH_HAB,R5		;4B�����t
	MOV.L	#_SVP_OVERE2_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�Q  �@�i���j
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;

	MOV.W	#BIT2,R7			;
	MOV.L	#_BTOA_TTL_HAB,R5		;4B�����t
	MOV.L	#_SVP_OVERE3_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�R  �@�i���j
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;��r�M�����
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;ϲŽ�M���͸ر
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;
KAJYU_OVERLOADCK_EXT:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�����t��r�ő傫����ΐ���	***
;	***					***
;	*******************************************
;
;
_KAJYU_OVER_NEGCMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;��������
	NEG	R3,R3			;

	CMP/GE	R3,R2			;
	BT KAJYU_OVER_NEGCP_END		;-300 =< -200 THEN JUMP

	OR	R7,R8			;ABNOMAL ���ݽ�ޯ�ON

KAJYU_OVER_NEGCP_END:


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�����t��r�ő傫����Έُ�	***
;	***					***
;	*******************************************
_KAJYU_OVER_CMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;��������

	CMP/GE	R3,R2			;
	BF	KAJYU_OVER_CP_END	;200 < 300? NO! THEN JUMP
	OR	R7,R8			;���ݽ�ޯ�ON
KAJYU_OVER_CP_END:

	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	۱�Я�				***
;	***					***
;	*******************************************
_KAJYU_LOWLIMIT_CHK
	SUB_START


;;;;	MOV.L	#_KJYU_CMP_SELSW2,R1		;
	MOV.L	#_CB_SEQ_SW_SEL058,R1		;00
	MOV.W	@R1,R0				;
	SHLR8	R0				;BIT11,BIT10=00,01,10
	AND	#(BIT3+BIT2),R0			;

	CMP/EQ	#BIT2,R0			;�ŏ��׏d(ϲŽ�ő�?)
	BT	KAJYU_LOWLIMITCK_100		;
	
	CMP/EQ	#BIT3,R0			;��?
	BT	KAJYU_LOWLIMITCK_200		;

;	------- �ő�׏d(COP1Z) --------------------------
;	------- �ŏ��׏d(ϲŽ�ő�?),���M���͸ر-----------
	MOV.L	#_KJYU_CMP_SEQMINS,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
	MOV.L	#_KJYU_CMP_SEQHABA,R5
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
	M_BRA	KAJYU_LOWLIMITCK_EXT		;


;	------- �ŏ��׏d(ϲŽ�ő�?)-----
KAJYU_LOWLIMITCK_100:


	XOR	R8,R8				;SEQ
	MOV.W	#BIT3,R7			;
	MOV.L	#_BTOA_LFT_MIN,R5		;4B�����t
	MOV.L	#_SVP_ROALM1_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�P �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;

	MOV.W	#BIT4,R7			;
	MOV.L	#_BTOA_RIH_MIN,R5		;4B�����t
	MOV.L	#_SVP_ROALM2_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�Q  �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;

	MOV.W	#BIT5,R7			;
	MOV.L	#_BTOA_TTL_MIN,R5		;4B�����t
	MOV.L	#_SVP_ROALM3_A27,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�R  �@�i�ŏ��l�j
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;��r�M�����
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;���M���͸ر
	M_BRA	KAJYU_LOWLIMITCK_EXT		;

;	------- ���M��-----------
KAJYU_LOWLIMITCK_200:

	XOR	R8,R8				;SEQ
	MOV.W	#BIT3,R7			;
	MOV.L	#_BTOA_LFT_HAB,R5		;4B�����t
	MOV.L	#_SVP_ROALM1_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�P �@�i���j
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;

	MOV.W	#BIT4,R7			;
	MOV.L	#_BTOA_RIH_HAB,R5		;4B�����t
	MOV.L	#_SVP_ROALM2_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�Q  �@�i���j
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;

	MOV.W	#BIT5,R7			;
	MOV.L	#_BTOA_TTL_HAB,R5		;4B�����t
	MOV.L	#_SVP_ROALM3_A28,R6		;2B��������  �׏d�v�@�I�[�o�[���[�h�R  �@�i���j
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;��r�M�����
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;ϲŽ�M���͸ر
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
KAJYU_LOWLIMITCK_EXT:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	�����t��r�ŏ�������ΐ���	***
;	***					***
;	*******************************************
;
;
_KAJYU_LOWLMT_NEGCMP:
	SUB_START
	MOV.L	@R5,R2			;PV
	MOV.W	@R6,R3			;SV
	EXTU.W	R3,R3			;��������
	NEG	R3,R3			;

	CMP/GT	R3,R2			;
	BF KAJYU_LOWLMT_NEGCP_END	;-300(R3) < -200(R2) NO! R3(-300) >=R2(-400)

	OR	R7,R8			;ABNOMAL ���ݽ�ޯ�ON

KAJYU_LOWLMT_NEGCP_END:


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�����t��r�ŏ�������Έُ�	***
;	***					***
;	*******************************************
_KAJYU_LOWLMT_CMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;��������

	CMP/GE	R3,R2			;
	BT	KAJYU_LOWLMT_CP_END	;200(R3) <= 300 (R2)? THEN NOMAL JUMP
	OR	R7,R8			;���ݽ�ޯ�ON
KAJYU_LOWLMT_CP_END:

	SUB_END
	M_RTS


;	*******************************************
;	****		�׏d���ޯ��p		***
;	*******************************************
;	CPUB���f10�{�V�e�C��
;	0     ~ 130.0    =0KN
;	130.0 ~ 150.0    = (�p�x-130.0)*10(cpua)*10(cpub)= 0~2000kn
;	150.0 ~          =0kn

	.IMPORT	_PVPAB_DBG_KYUIN1	;()
	.IMPORT	_PVPAB_DBG_KYUIN2	;()
	.IMPORT	_PVPAB_DBG_KYUIN3	;()
	.IMPORT	_TRD_SMP_PV_PGDG	;

_KAJYUU_DEBUG_ANACHG
	SUB_START

	MOV.L	#_TRD_SMP_PV_PGDG,R4		;
	MOV.W	@R4,R2				;0~360.0

;;;;	FAR_JSR	#_KAJYUU_DEBUG_ANACG1,R0
	FAR_JSR	#_KAJYUU_DEBUG_ANACG2,R0


;	R2��10�{����(CPUB��10�{���Ă���̂Ŏ���100�{)

	MOV.W	#D'10,R3			;180(cpua*10)->1800->(cpub*10)=18000
	DMULS.L	R3,R2				;
	STS	MACL,R2				;

	MOV	R2,R3
	ADD	#D'10,R3			;
	MOV	R2,R4				;
	ADD	#D'20,R4			;

	MOV.L	#_PVPAB_DBG_KYUIN1,R1		;
	SWAP.B	R2,R2				;����(��)
	MOV.W	R2,@R1				;

	MOV.L	#_PVPAB_DBG_KYUIN2,R1		;
	SWAP.B	R3,R3				;����(���v)
	MOV.W	R3,@R1				;

	MOV.L	#_PVPAB_DBG_KYUIN3,R1		;
	SWAP.B	R4,R4				;����(�E)
	MOV.W	R4,@R1				;

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***�@�����Ԃ����׏d����	***
;	***�@�����ԈȊO��0KN		***
;	***				***
;	***********************************
_KAJYUU_DEBUG_ANACG1
	SUB_START

	MOV.W	#D'1300,R4			;130.0�x
	MOV.W	#D'1500,R1			;150.0�x

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG1_050		;
	XOR	R2,R2				;150.0~360.0:THEN 0
	M_BRA	KAJYUU_DBG_ANACG1_100		;


KAJYUU_DBG_ANACG1_050				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG1_100		;JUMP(130.0~150.0)
	XOR	R2,R2				;0~130.0�x
KAJYUU_DBG_ANACG1_100				;

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	�ӂ肱�p2���		***
;	***				***
;	***********************************
_KAJYUU_DEBUG_ANACG2
	SUB_START

	MOV.W	#D'1300,R4			;130.0�x
	MOV.W	#D'1500,R1			;150.0�x

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG2_050		;
	M_BRA	KAJYUU_DBG_ANACG2_100		;150.0~360.0:THEN 0

;	0~150.0
KAJYUU_DBG_ANACG2_050				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG2_090		;JUMP(130.0~150.0)
	XOR	R2,R2				;0~130.0�x
KAJYUU_DBG_ANACG2_090				;
	M_BRA	KAJYUU_DBG_ANACG2_END		;

;	----------- ���H�p-------------
KAJYUU_DBG_ANACG2_100				;
	MOV.W	#D'2300,R1			;3600-130.0�x
	MOV.W	#D'2100,R4			;3600-150.0�x

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG2_150		;
	XOR	R2,R2				;2300~3600
	M_BRA	KAJYUU_DBG_ANACG2_END		;

;	0~150.0
KAJYUU_DBG_ANACG2_150				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG2_190		;JUMP(130.0~150.0)
	XOR	R2,R2				;180~210.0�x
	M_BRA	KAJYUU_DBG_ANACG2_END		;
KAJYUU_DBG_ANACG2_190				;
	MOV	R2,R4				;
	MOV.W	#(D'2300-D'2100)+1,R2		;201-**
	SUB	R4,R2				;
KAJYUU_DBG_ANACG2_END				;


	SUB_END
	M_RTS


;;;_KAJYUU_SHOT_ADR_SET:
;;;	SUB_START
;;;	MOV.L	#_SET1_KAJAREA_SEL,R1	;//����މ׏d�\���I��0:(�ő�),1:(�ŏ�),2(��)
;;;	MOV.W	@R1,R0			;
;;;
;;;	MOV.L	#_BTOA_LFT_TRDHAB,R1
;;;	MOV.L	#_BTOA_RIH_TRDHAB,R2
;;;	MOV.L	#_BTOA_TTL_TRDHAB,R4
;;;	CMP/EQ	#2,R0			;
;;;	BT KAJYUU_SHOTADRSET_100
;;;
;;;
;;;	MOV.L	#_BTOA_LFT_TRDMIN,R1
;;;	MOV.L	#_BTOA_RIH_TRDMIN,R2
;;;	MOV.L	#_BTOA_TTL_TRDMIN,R4
;;;
;;;	CMP/EQ	#1,R0			;
;;;	BT KAJYUU_SHOTADRSET_100
;;;
;;;	MOV.L	#_BTOA_LFT_TRDMAX,R1
;;;	MOV.L	#_BTOA_RIH_TRDMAX,R2
;;;	MOV.L	#_BTOA_TTL_TRDMAX,R4
;;;
;;;KAJYUU_SHOTADRSET_100:
;;;
;;;	MOV.L	#_SHOT_ADR_LFT,R0		;ADR
;;;	MOV.L	R1,@R0
;;;	MOV.L	#_SHOT_ADR_RIH,R0		;ADR
;;;	MOV.L	R2,@R0
;;;	MOV.L	#_SHOT_ADR_TTL,R0		;ADR
;;;	MOV.L	R4,@R0
;;;
;;;	SUB_END
;;;	M_RTS