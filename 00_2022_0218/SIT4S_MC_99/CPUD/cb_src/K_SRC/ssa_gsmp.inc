;	*******************************************
;	***					***
;	***					***
;	***					***
;	***	��ʃT���v�����O�f�[�^		***
;	***		cpu-b����		***
;	***		2009-09-25		***
;	***					***
;	*******************************************
	.IMPORT		_WAVE_SAMP_DATA	;CPUB SAMPLEING 20byte*501
	.IMPORT		_WAVE_TRND_DATA	;CPUB TREND 16*5001byte
	.IMPORT		_WAVE_SAMP_DTP	;CPUB SAMPLE CNT 2BYTE
	.IMPORT		_WAVE_TRND_DTP	;CPUB TREND CNT 2BYTE
	
	
	.ALIGN 4
_GAMEN_SMP2_TRD2_CPUB
	SUB_START


	FAR_JSR	#_GSMP2_RCV_INT_MAIN,R0		;
	FAR_JSR	#_GSHT2_RCV_INT_MAIN,R0		;

GSMP2_TRD2_CPUB_END

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		CPUB�����		***
;	***		(���ޯ��p)		***
;	***					***
;	*******************************************
	.IMPORT		_CPA_SMPDAT2		;24byte*4block=96
	.IMPORT		_CPA_SHTDAT2		;20byte*1block=20
	.IMPORT		_HND_SMPCNT_FLG2	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
	.IMPORT		_HND_SHTCNT_FLG2	;0,1	   (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
;
;	FLG2 BIT15=1(FIRST�ް�)
;_GSMP2_RCV_CNT		.SRES	2		;��M������
;_GSMP2_RCV_TOP			.SRES	__SMP2_1LINE_CNT*(__SMP2_BUF_MAX2)	;24b*500=12000 
;
_SHT_BUF_SMP_MAX	.EQU	5000	;

;;2010-09-21 __HMI_SMP2_1LINE_CNT	.EQU	20
__HMI_SMP2_1LINE_CNT	.EQU	24	;,�d��(4B)
__HMI_SHT2_1LINE_CNT	.EQU	16	;

__SMP2_SND_SDMAX	.EQU	4	;4BLOCK;;[2009-09-25]
;;���ޯ�__SMP2_BUF_MAX2		.EQU	500	;2009-09-25;;[2009-09-25]
;;���ޯ�__SMP2_1LINE_CNT	.EQU	24
;;���ޯ�__SHT2_1LINE_CNT	.EQU	20	;

;	*******************************************
;	***					***
;	***		�����ݸގ�M		***
;	***					***
;	*******************************************
;

_GSMP2_RCV_INT_MAIN:
	SUB_START
	
	XOR	R9,R9			;debug

	MOV.L	#_HND_SMPCNT_FLG2,R1	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF GSMP2_RCV_INTMN_500	;data �L��
	
;	--------- data �L��------------
	MOV.W	#BIT15,R4			;
	TST	R4,R0				;
	TST_BIT_OF GSMP2_RCV_INTMN_100		;

;	---- ��M������ ---
	XOR	R2,R2
	MOV.L	#_GSMP2_RCV_CNT,R1		;
	MOV.W	R2,@R1				;
	
GSMP2_RCV_INTMN_100:

	NOT	R4,R4				;
	AND	R4,R0				;BIT15=0 CLR
	TST	R0,R0				;
	TST_BIT_OF GSMP2_RCV_INTMN_400		;data err(0)��CPUA��ď゠�肦�Ȃ�

	MOV.W	#__SMP2_SND_SDMAX,R4		;
	CMP/HS	R0,R4				;R0=<R4(4)
	BF	GSMP2_RCV_INTMN_390		;data err

	MOV.L	#_GSMP2_RCV_CNT,R1			;
	MOV.W	@R1,R3					;���݌�
	MOV	R3,R2					;
	ADD	R0,R2					;R3:�O���
	MOV.W	R2,@R1					;R2:�V��
							;R0:��M��
	MOV.W	#D'500,R4				;
	CMP/HI	R4,R2					;500<R2
	BT	GSMP2_RCV_INTMN_399			;data ERR(CPUA��500�ُ푗���Ă���)


	ADD	#1,R3					;HMI��1�Ԓn�`500�Ԓn*20
	MOV.W	#__HMI_SMP2_1LINE_CNT,R1		;
	MULU.W	R1,R3					;500*20
	STS	MACL,R4					;1*24 2*24  599*24

;;;;DEBUG	MOV.L	#_GSMP2_RCV_TOP,R6			;(HMI�p)[[[[[HMI-ADR]]]]

	MOV.L	#_WAVE_SAMP_DATA,R6		;CPUB SAMPLEING 20byte*501
	ADD	R4,R6				;
	MOV.L	#_CPA_SMPDAT2,R5		;dpram(24*4byte)


;	---R0=0�͂Ȃ�
GSMP2_RCV_INTMN_200LOP:

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;RNA1 4B
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;RNA2 4B
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;DIG2B,���v�׏d2B
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;��2B�A�E�׏d2B
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;���ݽ2B
	MOV.L	R4,@R6				;�\��2B
	ADD	#4,R6				;

;;;;2010-09-21 �d�͒ǉ�ADD	#4,R5				;HMI��20byte�@DPRAM��24byte

;	-- �d��---
	MOV.L	@R5+,R4				;�d��(4b)0.01kw
	MOV.L	R4,@R6				;
	ADD	#4,R6				;

	ADD	#-1,R0				;
	TST	R0,R0
	TST_BIT_ON GSMP2_RCV_INTMN_200LOP	;


	MOV.L	#_GSMP2_RCV_CNT,R1		;
	MOV.W	@R1,R0				;���݌�-->HMI��
						;[[[[[[[HMI-ADR]]]]]
	MOV.L	#_WAVE_SAMP_DTP,R1		;CPUB SAMPLE CNT 2BYTE
	MOV.W	R0,@R1				;
	M_BRA	GSMP2_RCV_INTMN_450		;

GSMP2_RCV_INTMN_399:
	ADD	#1,R9	;500�ُ�CPUA�͑������@�v���I���
GSMP2_RCV_INTMN_390:
	ADD	#1,R9	;4��葽������CPUA��������
GSMP2_RCV_INTMN_400:
	ADD	#1,R9	;0�̑��M��������

GSMP2_RCV_INTMN_450:
	XOR	R0,R0
	MOV.L	#_HND_SMPCNT_FLG2,R1	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
	MOV.W	R0,@R1			;

GSMP2_RCV_INTMN_500:
	SUB_END
	M_RTS






;	*******************************************
;	***					***
;	***		SHOT��M		***
;	***					***
;	*******************************************
_GSHT2_RCV_INT_MAIN:
	SUB_START
	XOR	R9,R9			;debug

	MOV.L	#_HND_SHTCNT_FLG2,R1	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF GSHT2_RCV_INTMN_500	;data �L�� NO EXIT

;	--------- data �L��------------
	MOV.W	#BIT15,R4			;
	TST	R4,R0				;
	TST_BIT_OF GSHT2_RCV_INTMN_100		;

;	---- ��M������(�߲��) ---
	XOR	R2,R2				;FIRST
	MOV.L	#_GSHT2_RCV_CNT,R1		;
	MOV.W	R2,@R1				;

GSHT2_RCV_INTMN_100:

	NOT	R4,R4				;
	AND	R4,R0				;BIT15=0 CLR
	TST	R0,R0				;
	TST_BIT_OF GSHT2_RCV_INTMN_400		;data err(0)��CPUA��ď゠�肦�Ȃ�

	MOV.W	#1,R4				;
	CMP/HS	R0,R4				;R0=<R4(1)
	BF	GSHT2_RCV_INTMN_390		;data err


	MOV.L	#_GSHT2_RCV_CNT,R1			;
	MOV.W	@R1,R2					;���݌�
	ADD	R0,R2					;R3:�O���

	MOV.W	#_SHT_BUF_SMP_MAX,R4			;
	CMP/HI	R4,R2					;5000<R2
	BF	GSHT2_RCV_INTMN_150			;0,1~5000

	SUB	R4,R2					;5001�Ȃ�1
							;5002�Ȃ�2

GSHT2_RCV_INTMN_150:

	MOV.W	R2,@R1					;R2:�V��
							;R0:��M��

	MOV	R2,R3					;
;;;����+1���ꂽ����	ADD	#1,R3			;HMI��1�Ԓn�`5000�Ԓn*16
	MOV.W	#__HMI_SHT2_1LINE_CNT,R1		;
	MULU.W	R1,R3					;500*20
	STS	MACL,R4					;1*20 2*20  5000*20

;;DEBUG	MOV.L	#_GSHT2_RCV_TOP,R6			;(HMI�p)[[[[[HMI-ADR]]]]
	MOV.L	#_WAVE_TRND_DATA,R6	;CPUB TREND 16*5001byte

	ADD	R4,R6					;
	MOV.L	#_CPA_SHTDAT2,R5			;


;	----R0=0�͂Ȃ�
GSHT2_RCV_INTMN_200LOP:

	MOV.L	@R5+,R4				;16byte
	MOV.L	R4,@R6				;
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;
	ADD	#4,R6				;

	MOV.L	@R5+,R4				;
	MOV.L	R4,@R6				;
	ADD	#4,R6				;
	ADD	#4,R5				;DPRAM��20byte HMI��16byte�@

	ADD	#-1,R0				;
	TST	R0,R0
	TST_BIT_ON GSHT2_RCV_INTMN_200LOP	;


	MOV.L	#_GSHT2_RCV_CNT,R1		;
	MOV.W	@R1,R0				;���݌�-->HMI��
						;[[[[[[[HMI-ADR]]]]]
	MOV.L	#_WAVE_TRND_DTP,R1	;CPUB TREND CNT 2BYTE
	MOV.W	R0,@R1			;

	M_BRA	GSHT2_RCV_INTMN_450		;

GSHT2_RCV_INTMN_399:
	ADD	#1,R9	;500�ُ�CPUA�͑������@�v���I���
GSHT2_RCV_INTMN_390:
	ADD	#1,R9	;4��葽������CPUA��������
GSHT2_RCV_INTMN_400:
	ADD	#1,R9	;0�̑��M��������

GSHT2_RCV_INTMN_450:
	XOR	R0,R0
	MOV.L	#_HND_SHTCNT_FLG2,R1	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
	MOV.W	R0,@R1			;

GSHT2_RCV_INTMN_500:

;----------���ޯ�-----------------
;;;;;	2011-09-14 ���̗̈���g�p����
;;;;;	MOV.L	#_GSHT2_RCV_CNT,R1		;
;;;;;	MOV.W	@R1,R0				;���݌�-->HMI��
;;;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB228,R4	;
;;;;;	MOV.W	R0,@R4				;

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		�������錾		***
;	***					***
;	***					***
;	*******************************************
	.ALIGN 4
	.SECTION	Bwkram1,DATA			;
;	------------ CPUB ------------------
_GSMP2_RCV_CNT		.SRES	2
	.EXPORT		_GSHT2_RCV_CNT
_GSHT2_RCV_CNT		.SRES	2


	.ALIGN 4
;	-------- CPUB
;;_GSMP2_RCV_TOP		.SRES	__SMP2_1LINE_CNT*(__SMP2_BUF_MAX2+1)	;24b*500=12000 
;;_GSHT2_RCV_TOP		.SRES	__SHT2_1LINE_CNT*(5000+1)		;

;	--------�߂�------------
;;;;;	.SECTION	P,CODE			;
;;;;;	.ALIGN	4