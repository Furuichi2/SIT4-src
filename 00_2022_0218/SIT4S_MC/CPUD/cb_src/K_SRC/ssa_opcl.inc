
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
	
	.GLOBAL		_SEQ_DP_TOP		;


	.EXPORT	_COP1_ROT_DT_INI
	

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
	TST_BIT_OF CB_COP_DT_MK2_050						;

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


;	-- 2007-09-06 --
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETX_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETX_KJEND_DIG1,L2=W;

	DATA_STD_CHG_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETY_KJSTR_DIG1,L2=W,CALLSB=_NEG_TAIKI;
	DATA_STD_CHG_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETY_KJEND_DIG1,L2=W,CALLSB=_NEG_TAIKI;

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

;	-- 2009-10-07 --
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

	M_BRA	CB_COP_DT_MK2_200	

CB_COP_DT_MK2_100:
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W,CALLSB=_TAIKI_ADD;

;	-- 2009-10-07 --
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

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

	DATA_STD_SHN_MOV	SRC=_SETX_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETX_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W
	M_BRA	SIG_AREA_DATCHG190


SIG_AREA_DATCHG150:
	DATA_STD_SHN_MOV	SRC=_SETY_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETY_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W
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

	MOV.L	#_SEQ_DP_TOP+109*2,R1		;
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

;	------ 2006-07-28----
	XOR	R0,R0				;
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;2013-06-19
	MOV.W	R0,@R1				;

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


;	=========2006-07-28 BIT4,5 REFLASH========
	FAR_JSR	#_KAJYUU_AREA_SIGMAK,R0		;
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
;	----------- ���ޯ��p--------
	MOV.L	#(_SQ_CBWK_TOP+26*2),R1		;_SQCB226
	MOV.W	R2,@R1				;



CB_COP_SIGMK_EXT:


	MOV.L	#_INC_ENC360,R1		;//360.0�x(�ݺ��ނ͕\���Ɠ���)
	MOV.W	@R1,R2			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	R2,@R1			;


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
;
_KAJYUU_AREA_SIGMAK:
	SUB_START
	MOV.L	#_SETC_KJSTR_DIG1,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R1								;
	MOV.L	#_INC_ENC360,R4							;
	MOV.W	@R4,R2								;

	MOV.L	#_SETC_KJEND_DIG1,R4						;[2009-10-07���U�q]
	MOV.W	@R4,R3			
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BF	KAYJUU_AREASIGMK050						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT0),WKREG=R1	;AREA-ON
	M_BRA	KAYJUU_AREASIGMK090						;
KAYJUU_AREASIGMK050:								;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT0),WKREG=R1	;
KAYJUU_AREASIGMK090:								;


;	-------- �J�n����----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;START ON?
	TST_BIT_ON KAYJUU_AREASIGMK200						;

	MOV.L	#_SET1_KJSTR_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREASIGMK130						;0:POS

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREASIGMK150						;
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREASIGMK190						;

KAYJUU_AREASIGMK130:								;
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT0,R0							;
	TST_BIT_OF KAYJUU_AREASIGMK190						;
KAYJUU_AREASIGMK150:								;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT5+BIT1),WKREG=R1	;AREA-ON
KAYJUU_AREASIGMK190:								;
	M_BRA	KAYJUU_AREASIGMK900						;

KAYJUU_AREASIGMK200:
;	-------- �I������----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;START ON?
	TST_BIT_ON KAYJUU_AREASIGMK290						;


;;;;	MOV.L	#_SET1_KJEND_STEP1,R1						;
;;;;	MOV.W	@R1,R0								;
;;;;	TST	R0,R0								;
;;;;	TST_BIT_ON KAYJUU_AREASIGMK220						;POS�ȊO
;;;;
;;;;
;;;;	MOV.L	#_SET1_MRTION_SEL1,R4						;
;;;;	MOV.W	@R4,R0								;
;;;;	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0				;��]or�ӂ肱��
;;;;	TST_BIT_OF KAYJUU_AREASIGMK240						;���]
;;;;
;;;;;	--------��]�܂��͂ӂ肱�̈ʒu�J��--------------
;;;;	MOV.L	#_KJ_AREA_SIG,R1		;
;;;;	MOV.W	@R1,R0				;
;;;;	TST	#BIT0,R0			;�ʒu�͈�?
;;;;	TST_BIT_OF KAYJUU_AREASIGMK250		;�ʒu�͈͂���o��CLR
;;;;	M_BRA	KAYJUU_AREASIGMK290		;


;----------�H���w��-------------
KAYJUU_AREASIGMK220:
	MOV.L	#_SET1_KJEND_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREASIGMK230						;

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	CMP/HI	R0,R2								;�H���𒴂���
	BT	KAYJUU_AREASIGMK250						;CLR
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREASIGMK290						;

KAYJUU_AREASIGMK230:
	MOV.L	#_SET1_MRTION_SEL1,R4				;
	MOV.W	@R4,R0						;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;��]or�ӂ肱��
	TST_BIT_OF KAYJUU_AREASIGMK240				;���]
	NOP
KAYJUU_AREASIGMK240:						;
;	-------- �ʒu�J���܂��͍H���J���̌��s�H��-------------
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON KAYJUU_AREASIGMK290		;ON���Ă���

	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ON���Ă���
	TST_BIT_ON KAYJUU_AREASIGMK250		;
	M_BRA	KAYJUU_AREASIGMK290		;

;	------------���]�̏ꍇ����----------------
;;;;KAYJUU_AREASIGMK240:
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
;;;;	BT	KAYJUU_AREASIGMK250						;
;;;;	M_BRA	KAYJUU_AREASIGMK290						;
KAYJUU_AREASIGMK250:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT5),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT6+BIT2),WKREG=R1	;END SET
KAYJUU_AREASIGMK290:								;
	NOP
KAYJUU_AREASIGMK900				;

KAYJUU_AREASIGMKEXT
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;


	SUB_END
	M_RTS

