;�f�o�b�N�̂��߂ɕύX2019-08-21
;	*******************************************
;	***	DPRAM HANDSYEIKU OUT SH4-->SH2	***
;	*******************************************
_CPU_SV_HAND_ACK:
	SUB_START
	MOV.L	#_CPU_SV_HAND_OUT,R1	;
	MOV.L	@R1,R0			;
	MOV.L	#_HS_SVCHG_A_TO_B,R1	;
	MOV.L	R0,@R1			;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	�Ʊ�ݻLOAD		***
;	***	(CPUA����)		***
;	***********************************
	.import	_PV1_SCRW_POS	;

_RENEA_CENCER_LOAD:
	SUB_START

;	-------- 2009-03-11
	MOV.L	#_WPAR_MCNRNA_SEL,R4		;//1:�@�B���Ʊ���ق��g�p���Ȃ��\�������_���A
	MOV.W	@R4,R0				;
	CMP/EQ	#1,R0				;
	BF	RENEA_CENCER_LD020		;
	MOV.L	#_RNA_POS_OFFSET1,R4		;_SVB_RNAORG_PLS1->_RNA_POS_OFFSET1->_PVP_RNAORG_PLS1
	MOV.L	@R4,R2				;
	M_BRA	RENEA_CENCER_LD040		;���_�ʒu

RENEA_CENCER_LD020:				;
	MOV.L	#_PV1_SCRW_POS,R1	;
	MOV.L	@R1,R2			;(�ʐM���ް�)
RENEA_CENCER_LD040:				;

	MOV.L	#_PVX_RNA_INDAT,R1	;��	SH4-->SH2 ����n��
	MOV.L	R2,@R1			;(�����ް����ޯ����߂�)

	MOV.L	#_PVP_RNAORG_PLS1,R1	;�Ʊ��ʒu��ٽ(�ޯ����ߐ�p)
	MOV.L	R2,@R1			;���ʐM�ް����ޯ����߂�����

	MOV.L	#_RNA_POS_OFFSET1,R4	;(�d�������� �捞��)
	MOV.L	@R4,R3			;(�ȍ~�͐ݒ�ύX���捞)
	SUB	R3,R2			;
	MOV.L	#_SET1_RNADIR_SEL1,R1	;
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF RENEA_CENCER_LD050	;
	NEG	R2,R2			;
RENEA_CENCER_LD050:			;ANS:R2


;;;;	--------------2015-10-15 MTS�Ή�-------------
;;;;;	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:�����Ʊ)
;;;;	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
;;;;	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
;;;;	MOV.W	@R1,R0						;
;;;;	CMP/EQ	#1,R0						;�W����0�ȊO jump(r4=20)
;;;;	BF	RENEA_CENCER_LD070				;(R2��1/2���Ȃ��� R4=10*2�ɂ���)
;;;;	MOV.W	#D'10,R4					;(�����Ʊ)0.1um  1/10--->1um (0.001mm)
;;;;RENEA_CENCER_LD070:						;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	MOV.L	#_PVX_RNA_POSD1,R1				;����Ɍ��_�ް���������Ηǂ�
;;;;	MOV.L	R2,@R1						;���_���̈ʒu=0mm 1um(0.001mm)
;;;;
;;;;	MOV.L	#_RNA_POS_OFFSET2,R1	;
;;;;	MOV.L	@R1,R3			;���_
;;;;	ADD	R3,R2			;

;	---------2014-02-14 X�А�-----------------------
	MOV.L	#_RNA_PROTOCOL_X,R1				;"1"X�А����ĺ�
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	RENEA_CENCER_LD060

	MOV.W	#D'1,R4						;1um
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVX_RNA_POSD1,R1				;����Ɍ��_�ް���������Ηǂ�
	MOV.L	R2,@R1						;���_���̈ʒu=0mm 1um(0.001mm)

;	-- ���x�␳ 2015-10-15
	MOV.L	#_X_PROTCOL_TMP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF RENEA_CENCER_LD090		;�␳�Ȃ�
	MOV.L	#_X_PROTCOL_TMP_PVLNG,R1	;//�␳��
	MOV.W	@R1,R0				;+/-
	ADD	R0,R2				;ANS:R2
	M_BRA	RENEA_CENCER_LD090		;

;	--------- ����
RENEA_CENCER_LD060:						;
;	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:�����Ʊ)
	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;�W����0�ȊO jump(r4=20)
	BF	RENEA_CENCER_LD070				;(R2��1/2���Ȃ��� R4=10*2�ɂ���)
	MOV.W	#D'10,R4					;(�����Ʊ)0.1um  1/10--->1um (0.001mm)
RENEA_CENCER_LD070:						;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVX_RNA_POSD1,R1				;����Ɍ��_�ް���������Ηǂ�
	MOV.L	R2,@R1						;���_���̈ʒu=0mm 1um(0.001mm)

RENEA_CENCER_LD090:						;
	MOV.L	#_RNA_POS_OFFSET2,R1	;
	MOV.L	@R1,R3			;���_
	ADD	R3,R2			;ANS:R2

;	===========================================
	MOV.L	#_DEBUG_MOD_CODE,R1		;
	MOV.W	@R1,R0				;
	MOV.W	#H'5AA5,R1			;
	CMP/EQ	R1,R0					;
	BF	DBG_RNA_END				;
;2020-12-15[�ꎞ�f�o�b�N�@�\OFF]
	M_BRA	DBG_RNA_END				;


;;;;
;;;;	-------------2012-10-05 1234,***,123,210---------------------
;;;;	MOV.L	#_SVP_MACINE_SEL1,R1			;
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#_MCN_FUJI_DBG1,R1			;
;;;;	CMP/EQ	R1,R0					;D=1234 ���¼��ݽ
;;;;	BF	DBG_RNA_END			;�ҋ@�_�Q��123�A�ҋ@�_�R��210
;;;;	MOV.L	#_SVP_WT_DIG2,R1			;�ҋ@�_�I��2 123
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#D'123*10,R1				;
;;;;	CMP/EQ	R1,R0					;
;;;;	BF	DBG_RNA_END				;
;;;;	MOV.L	#_SVP_WT_DIG3,R1			;�ҋ@�_�I��3 210
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#D'210*10,R1				;
;;;;	CMP/EQ	R1,R0					;
;;;;	BF	DBG_RNA_END				;
;;;;	
;;;;
;	======== ���ޯ��@�\====
	MOV.L	#_INC_ENC_MM_POS,R1	;
	MOV.L	@R1,R2			;
	ADD	R3,R2			;���_

	MOV.L	#_SVP_ORGCAL_DAT5,R1	;����8-89 DAT5 
	MOV.L	@R1,R1			;

	MOV.W	#D'10000,R0		;10.000=0 11000=+1.000 9000=-1.000
	SUB	R0,R1			;
	ADD	R1,R2			;�Ʊ��1mm/1mm�����Ⴂ
	CMP/PL	R2			
	BT	DBG_RNA_100		;
	MOV	#1,R2
DBG_RNA_100
DBG_RNA_END
;	============================


					;CPUA->CPUB
	MOV.L	#_PVX_RNA_POSD2,R1	;�ϊ�	SH4-->SH2 0.5um->1mm+���_
	MOV.L	R2,@R1			;��Έʒu(SH2�ł͂�����g�p����)

	MOV.L	#_RNA_ABS_POS,R1	;//��ٽ��ʍ���
	MOV.L	R2,@R1			;


	MOV.L	#_PVX_RNA_STLORK,R1		;//����
	MOV.L	@R1,R2				;
	MOV.L	#_PVP_RNA_STLORK,R1		;
	MOV.L	R2,@R1				;




	SUB_END
	M_RTS


;;;[2015-10-15 MTS�Ή�]
;;;[2015-10-15]_RENEA_CENCER_LOAD:
;;;[2015-10-15]	SUB_START
;;;[2015-10-15];	-------- 2009-03-11
;;;[2015-10-15]	MOV.L	#_WPAR_MCNRNA_SEL,R4		;//1:�@�B���Ʊ���ق��g�p���Ȃ��\�������_���A
;;;[2015-10-15]	MOV.W	@R4,R0				;
;;;[2015-10-15]	CMP/EQ	#1,R0				;
;;;[2015-10-15]	BF	RENEA_CENCER_LD020		;
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET1,R4		;_SVB_RNAORG_PLS1->_RNA_POS_OFFSET1->_PVP_RNAORG_PLS1
;;;[2015-10-15]	MOV.L	@R4,R2				;
;;;[2015-10-15]	M_BRA	RENEA_CENCER_LD040		;���_�ʒu
;;;[2015-10-15]
;;;[2015-10-15]RENEA_CENCER_LD020:				;
;;;[2015-10-15]	MOV.L	#_PV1_SCRW_POS,R1	;
;;;[2015-10-15]	MOV.L	@R1,R2			;(�ʐM���ް�)
;;;[2015-10-15]RENEA_CENCER_LD040:				;
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_INDAT,R1	;��	SH4-->SH2 ����n��
;;;[2015-10-15]	MOV.L	R2,@R1			;(�����ް����ޯ����߂�)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVP_RNAORG_PLS1,R1	;�Ʊ��ʒu��ٽ(�ޯ����ߐ�p)
;;;[2015-10-15]	MOV.L	R2,@R1			;���ʐM�ް����ޯ����߂�����
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET1,R4	;(�d�������� �捞��)
;;;[2015-10-15]	MOV.L	@R4,R3			;(�ȍ~�͐ݒ�ύX���捞)
;;;[2015-10-15]	SUB	R3,R2			;
;;;[2015-10-15]	MOV.L	#_SET1_RNADIR_SEL1,R1	;
;;;[2015-10-15]	MOV.W	@R1,R0			;
;;;[2015-10-15]	TST	R0,R0			;
;;;[2015-10-15]	TST_BIT_OF RENEA_CENCER_LD050	;
;;;[2015-10-15]	NEG	R2,R2			;
;;;[2015-10-15]RENEA_CENCER_LD050:			;
;;;[2015-10-15];	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:�����Ʊ)
;;;[2015-10-15]	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
;;;[2015-10-15]	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
;;;[2015-10-15]	MOV.W	@R1,R0						;
;;;[2015-10-15]	CMP/EQ	#1,R0						;�W����0�ȊO jump(r4=20)
;;;[2015-10-15]	BF	RENEA_CENCER_LD070				;(R2��1/2���Ȃ��� R4=10*2�ɂ���)
;;;[2015-10-15]	MOV.W	#D'10,R4					;(�����Ʊ)0.1um  1/10--->1um (0.001mm)
;;;[2015-10-15]RENEA_CENCER_LD070:						;
;;;[2015-10-15]	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;[2015-10-15]	MOV.L	#_PVX_RNA_POSD1,R1				;����Ɍ��_�ް���������Ηǂ�
;;;[2015-10-15]	MOV.L	R2,@R1						;���_���̈ʒu=0mm 1um(0.001mm)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET2,R1	;
;;;[2015-10-15]	MOV.L	@R1,R3			;���_
;;;[2015-10-15]	ADD	R3,R2			;
;;;[2015-10-15]
;;;[2015-10-15];	===========================================
;;;[2015-10-15];	-------------2012-10-05 1234,***,123,210---------------------
;;;[2015-10-15]	MOV.L	#_SVP_MACINE_SEL1,R1			;
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#_MCN_FUJI_DBG1,R1			;
;;;[2015-10-15]	CMP/EQ	R1,R0					;D=1234 ���¼��ݽ
;;;[2015-10-15]	BF	DBG_RNA_END			;�ҋ@�_�Q��123�A�ҋ@�_�R��210
;;;[2015-10-15]	MOV.L	#_SVP_WT_DIG2,R1			;�ҋ@�_�I��2 123
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#D'123*10,R1				;
;;;[2015-10-15]	CMP/EQ	R1,R0					;
;;;[2015-10-15]	BF	DBG_RNA_END				;
;;;[2015-10-15]	MOV.L	#_SVP_WT_DIG3,R1			;�ҋ@�_�I��3 210
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#D'210*10,R1				;
;;;[2015-10-15]	CMP/EQ	R1,R0					;
;;;[2015-10-15]	BF	DBG_RNA_END				;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15];	======== ���ޯ��@�\====
;;;[2015-10-15]	MOV.L	#_INC_ENC_MM_POS,R1	;
;;;[2015-10-15]	MOV.L	@R1,R2			;
;;;[2015-10-15]	ADD	R3,R2			;���_
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_SVP_ORGCAL_DAT5,R1	;����8-89 DAT5 
;;;[2015-10-15]	MOV.L	@R1,R1			;
;;;[2015-10-15]
;;;[2015-10-15]	MOV.W	#D'10000,R0		;10.000=0 11000=+1.000 9000=-1.000
;;;[2015-10-15]	SUB	R0,R1			;
;;;[2015-10-15]	ADD	R1,R2			;�Ʊ��1mm/1mm�����Ⴂ
;;;[2015-10-15]	CMP/PL	R2			
;;;[2015-10-15]	BT	DBG_RNA_100		;
;;;[2015-10-15]	MOV	#1,R2
;;;[2015-10-15]DBG_RNA_100
;;;[2015-10-15]DBG_RNA_END
;;;[2015-10-15];	============================
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_POSD2,R1	;�ϊ�	SH4-->SH2 0.5um->1mm+���_
;;;[2015-10-15]	MOV.L	R2,@R1			;��Έʒu(SH2�ł͂�����g�p����)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_ABS_POS,R1	;//��ٽ��ʍ���
;;;[2015-10-15]	MOV.L	R2,@R1			;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_STLORK,R1		;//����
;;;[2015-10-15]	MOV.L	@R1,R2				;
;;;[2015-10-15]	MOV.L	#_PVP_RNA_STLORK,R1		;
;;;[2015-10-15]	MOV.L	R2,@R1				;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]	SUB_END
;;;[2015-10-15]	M_RTS
;;;[2015-10-15]



;	***********************************
;	***	�ް����޼�������	***
;	***********************************
_RENEA_ORGIN_SET:
	SUB_START
	MOV.L	#_PVX_RNA_INDAT,R1	;��	SH4-->SH2 ����n��
	MOV.L	@R1,R2			;(�����ް����ޯ����߂�)

	MOV.L	#_PVP_RNAORG_PLS1,R1	;�Ʊ��ʒu��ٽ(�ޯ����ߐ�p)
	MOV.L	R2,@R1			;���ʐM�ް����ޯ����߂�����
					;�{���̓��C����
					;_SVB_RNAORG_PLS1�ɕԂ��̂��������p

	MOV.L	#_RNA_POS_OFFSET1,R1	;(�d�������� HMI->�捞��)
	MOV.L	R2,@R1			;

;	==============================
	MOV.L	#_SET1_RNAORG_POS1,R4	;
	MOV.L	@R4,R0			;

	MOV.L	#_OLD_RNAORG_POS1,R4	;
	MOV.L	R0,@R4			;

	MOV.L	#_RNA_POS_OFFSET2,R4	;���_�ݒ�
	MOV.L	R0,@R4			;


	SUB_END
	M_RTS





















;	*******************************************
;	***	�ޯ������ގ����]��		***
;	*******************************************

;
;	���ޯ��@�\
;	�p�x�\��
;		�ݺ��ފp�x
;		�����_����
;
;
_PV_DATA_DP_MOV:
	SUB_START

	MOV.L	#_RNA_ABS_POS,R3	;//��ٽ��ʍ���(��Έʒu)
	MOV.L	@R3,R2			
	MOV.L	#_PVP_RENIA_POSI0,R4	;���j�A�Z���T���݈ʒu(���\���p ��ٽ���)
	MOV.L	R2,@R4


;	====== ���ޯ��@�\ 2003-01-27 =====
;;	.AIF	_PRG_CHG20030127 EQ _COMPILE_YES	;��۸��ѕύX�ӏ�(���]�d�l�ȊO�̕W���ɓ����ύX)
;;	.AENDI

	MOV.L	#_SVP_MACINE_SEL1,R1			;
	MOV.W	@R1,R0					;

	CMP/EQ	#_MCN_DBG_COD21,R0			;89
	BF	NOMAL_DAIHAI_DISP10_1			;
;	==== ���ޯ� ===
	MOV.L	#_RNA_ABS_POS,R3	;//��ٽ��ʍ���(��Έʒu)
	MOV.L	@R3,R2			;
	M_BRA	NOMAL_DAIHAI_DISP10_E	;

NOMAL_DAIHAI_DISP10_1:

	CMP/EQ	#_MCN_DBG_COD22,R0			;88
	BF	NOMAL_DAIHAI_DISP10_2			;
;	==== ���ޯ� ===

NOMAL_DAIHAI_DISP10_2:



NOMAL_DAIHAI_DISP10_S:
	MOV.L	#_RNA_CTL_POS1,R3	;//����ʒu(�����_����)
	MOV.L	@R3,R2			;

;;	.AIF	_PRG_CHG20030127 EQ _COMPILE_YES	;��۸��ѕύX�ӏ�(���]�d�l�ȊO�̕W���ɓ����ύX)
;;	.AENDI
;;	MOV.L	#_ORGIN_END_FLG1,R4;	//�d�������̂P��ON:OFF�͂Ȃ�
;;	MOV.W	@R4,R0			;
;;	TST	R0,R0			;
;;	TST_BIT_ON NOMAL_DAIHAI_DISP10_E;
;;	MOV.L	#_RNA_ABS_POS,R3	;//��ٽ��ʍ���(��Έʒu)
;;	MOV.L	@R3,R2			;
NOMAL_DAIHAI_DISP10_E:			;

	REG1_0CHK REG1=R2		;
	MOV.L	#_PVP_NOW_POSI000,R4	;(�����_�����\��)
	MOV.L	R2,@R4			;


	MOV.L	#_DISP_ENC360,R5	;�ݸ�����ENC
	MOV.L	#_RNA_ENC360,R6		;
	MOV.W	@R5,R2			;�ݸ����ق���̂ݕ\�� 2014-09-09a

;;;;;2014-09-09a	MOV.L	#_MODE_SEL,R4		;
;;;;;2014-09-09a	MOV.W	@R4,R0			;
;;;;;2014-09-09a
;;;;;2014-09-09a
;;;;;2014-09-09	TST	#(_W1OPT+_W1CNT+_W1SGL+_W1INC+_W1DIC),R0	;
;;;;;2014-09-09a		TST	#(_W1OPT+_W1CNT+_W1SGL+_W1INC),R0		;
;;;;;2014-09-09a	TST_BIT_OF DISP_ENC_DIG_050				;
;;;;;2014-09-09a
;;;;;2014-09-09a	MOV.L	#_emg_err_flg,R1				;
;;;;;2014-09-09a	MOV.W	@R1,R0						;
;;;;;2014-09-09a	TST	R0,R0						;
;;;;;2014-09-09a	TST_BIT_ON DISP_ENC_DIG_050				;����~��[�}��~�͂��̏ꂩ�瓮������ς��Ȃ�]
;;;;;2014-09-09a
;;;;;2014-09-09a	MOV.L	#_SETX_POS_CTL_MATH,R1				;
;;;;;2014-09-09a	MOV.W	@R1,R0						;
;;;;;2014-09-09a	TST	#_DMATH_REVRSE,R0				;[20091007���U�q]
;;;;;2014-09-09a	TST_BIT_OF DISP_ENC_DIG_050				;�I��/��]
;;;;;2014-09-09a	MOV	R5,R0						;
;;;;;2014-09-09a	MOV	R6,R5						;
;;;;;2014-09-09a	MOV	R0,R6						;
;;;;;2014-09-09aDISP_ENC_DIG_050:						;
;;;;;2014-09-09a	MOV.W	@R5,R2			;�ݸ����ق���̂ݕ\��
;;;;;2014-09-09a
;;;;;2014-09-09a;	=============== 4�ɂT��[2013-03-15] =================
;;;;;2014-09-09a	ADD	#5,R2						;
;;;;;2014-09-09a	MOV.W	#D'10,R4					;
;;;;;2014-09-09a	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;;2014-09-09a	DMULS.L	R4,R2						;
;;;;;2014-09-09a	STS	MACL,R2						;
;;;;;2014-09-09a	MOV.W	#D'3600,R4					;
;;;;;2014-09-09a	CMP/HI	R2,R4						;R3<R4(3600)
;;;;;2014-09-09a	BT	DISP_ENC_DIG_055				;
;;;;;2014-09-09a	SUB	R4,R2						;
;;;;;2014-09-09aDISP_ENC_DIG_055:
;	=================================================

	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0			;
	MOV.W	#D'3600,R4					;
	CMP/HI	R2,R4						;
	BT	DISP_ENC_DIG_080				;
	SUB	R4,R2						;
DISP_ENC_DIG_080:						;�ʏ퐧��̌���

;	=============== 4�ɂT��[2014-09-09] =================
	ADD	#5,R2						;
	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	DMULS.L	R4,R2						;
	STS	MACL,R2						;
	MOV.W	#D'3600,R4					;
	CMP/HI	R2,R4						;R3<R4(3600)
	BT	DISP_ENC_DIG_085				;
	SUB	R4,R2						;
DISP_ENC_DIG_085:
;	=================================================




;	===	342.0  ===
	MOV.L	#_CB_SEQ_CB_SEL342,R1			;342
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON DIG_DISP_CHK090			;�\���ؑ�ON 360

	MOV.L	#_SVP_MACINE_SEL1,R4			;
	MOV.W	@R4,R0					;
	CMP/EQ	#_MCN_DBG_COD11,R0			;99
	BF	DIG_DISP_CHK100				;
DIG_DISP_CHK090:
	MOV.L	#_CTL_ENC360,R5				;//360.0�x
	MOV.W	@R5,R2					;���ꂾ����
DIG_DISP_CHK100:

	MOV.L	#_PVP_NOW_ANGLE_RNA,R4	;
	MOV.W	R2,@R4			;

;;;20091007	MOV.L	#_SETX_UPAREA_DIG,R3		;2;��]���ҋ@�_(�㎀�_/�ҋ@�_)	
;;;20091007	MOV.W	@R3,R2				;
;;;20091007	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
;;;20091007	MOV.L	#_PVP_TAIKITEN_POS,R4		;
;;;20091007	MOV.W	R2,@R4				;

	FAR_JSR	#_DNM_TAIKI_DIR_DISP,R0		;[2009-10-07���U�q] �ҋ@�_��HMI��


;;2018-12-10 ;	===	342.0  ===
;;2018-12-10 	MOV.L	#_CB_SEQ_CB_SEL342,R1			;342
;;2018-12-10 	MOV.W	@R1,R0							;
;;2018-12-10 	TST	#BIT0,R0							;
;;2018-12-10 	TST_BIT_ON NOMAL_DAIHAI_DISP20_2A		;debug
;;2018-12-10 
;;2018-12-10 	MOV.L	#_SVP_MACINE_SEL1,R4			;
;;2018-12-10 	MOV.W	@R4,R0					;
;;2018-12-10 
;;2018-12-10 	CMP/EQ	#_MCN_DBG_COD31,R0			;79
;;2018-12-10	BF	NOMAL_DAIHAI_DISP20_1			;
;;2018-12-10
;;2018-12-10	MOV.L	#_INC_ENC_MM_POS,R3			;79
;;2018-12-10	MOV.L	@R3,R2					;
;;2018-12-10	M_BRA	NOMAL_DAIHAI_DISP20_E			;
;;2018-12-10
;;2018-12-10NOMAL_DAIHAI_DISP20_1:
;;2018-12-10	CMP/EQ	#_MCN_DBG_COD32,R0			;78
;;2018-12-10	BF	NOMAL_DAIHAI_DISP20_2			;
;;2018-12-10
;;2018-12-10	MOV.L	#_CLS_RNA_MOST_DOWN_POS,R3		;�ŉ����_
;;2018-12-10	MOV.L	@R3,R2					;
;;2018-12-10	M_BRA	NOMAL_DAIHAI_DISP20_E			;
;;2018-12-10
;;2018-12-10NOMAL_DAIHAI_DISP20_2:
;;2018-12-10	CMP/EQ	#_MCN_DBG_COD33,R0			;77
;;2018-12-10	BF	NOMAL_DAIHAI_DISP20_3			;
;;2018-12-10
;;2018-12-10NOMAL_DAIHAI_DISP20_2A:					;debug
;;2018-12-10	MOV.L	#_RNA_ABS_POS,R3			;//��ٽ��ʍ���(��Έʒu)
;;2018-12-10	MOV.L	@R3,R2					;
;;2018-12-10	M_BRA	NOMAL_DAIHAI_DISP20_E			;��Βl
;;2018-12-10
;;2018-12-10NOMAL_DAIHAI_DISP20_3:
;;2018-12-10	NOP
;;2018-12-10NOMAL_DAIHAI_DISP20_S:	;�W����۸���
;;2018-12-10
;;2018-12-10	MOV.L	#_PVX_DAI_POS1,R3	;�޲ʲĕ\���l�E����l
;;2018-12-10	MOV.L	@R3,R2				;
;;2018-12-10
;;2018-12-10
;;2018-12-10NOMAL_DAIHAI_DISP20_E:
;;2018-12-10	REG1_0CHK REG1=R2		;
;;2018-12-10	MOV.L	#_PVP_DYHITO_POS,R4	;
;;2018-12-10	MOV.L	R2,@R4			;
;;2018-12-10
;;2018-12-10

	MOV.L	#_SCAN_DBG_CNT,R1	;
	MOV.W	@R1,R0			;
	ADD	#1,R0			;
	EXTU.B	R0,R0			;
	MOV.W	R0,@R1			;


;2019-08-20�f�o�b�N
	MOV.L	#_CYCL_DSP_DISENB,R1		;1:��\�� => ���]���ďo��
	MOV.W	@R1,R0						;0:�\��
	TST		#BIT0,R0					;
	TST_BIT_ON DEBUG20190820_100
	NOP
	NOP
	NOP
	NOP
	M_BRA	DEBUG20190820_200
DEBUG20190820_100
	NOP
	NOP
	NOP
	NOP
DEBUG20190820_200
	MOV.L	#_CYCL_DSP_CNT_PV,R1		;//��\������ 2->1->0(�\��)
	MOV.W	@R1,R0						;











;	===== �P�T�C�N������

	MOV.L	#_CYCLE_TIME_PV,R1	;
	MOV.L	@R1,R2			;
;	================================
;;;;	SHLL	R2			;1msec ok
	MOV	R2,R6
	FAR_JSR	#_WD_DIV10,R0		;
	MOV.L	#_PVP_CYCLE_TIME0,R1	;
	MOV.W	R2,@R1			;
;	============================
	MOV.L	#D'60000,R2					;60.000�b
;;;;	MOV.L	#_CYCLE_TIME_PV,R1				;
;;;;	MOV.L	@R1,R4						;

	MOV	R6,R4						;
	TST	R4,R4						;
	TST_BIT_OF SPM_DISP_DAT_ERR				;
	
;;;;;	------ 2012-12-10 4��5����2012-12-10�ɂ���������ς��߂�.(2013-02-08)
;;;;;		MOV	R4,R0		;
;;;;;		SHLR	R0		;
;;;;;MISS	ADD	R0,R2		;

	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVP_CYCLE_SPM1,R1				;
	MOV.W	R2,@R1						;
	MOV.L	#_PVP_DISP_SPM2,R1				;
	MOV.W	R2,@R1						;
SPM_DISP_DAT_ERR:
	

	MOV.L	#_STOPPING_TIM_FLG,R1		;//�į��ݸ���ϗp�׸� BIT0����J�n BIT6:��~��
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF STOP_TIM_DSP_EXT
	AND	#LOW ~BIT1,R0			;
	MOV.W	R0,@R1				;
	MOV.L	#_STOPPING_TIM_PV2,R1		;//�į��ݸ����
	MOV.W	@R1,R2				;(1/10)
	MOV.L	#_PVP_STOP_TIM,R1		;
	MOV.W	R2,@R1				;

STOP_TIM_DSP_EXT:

;;2006-09-30	====== �ߕ��׃��j�^ 2003-01-27 =====
;;	MOV.L	#_PV_AD_DATA,R5			; �ړ����ςƂ������0~1000 DATA
;;	MOV.W	@R5,R2				; data 0~10.00v
;;	MOV.L	#_SET1_AMP100P_VLT,R1		;
;;	MOV.W	@R1,R4				;
;;	MOV.W	#_DT_100PER_1,R1		;data * 100.0per/volt
;;	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0���Z�t�h�~)

;	------ 2006-09-30�ߕ���������ٸ���p-----
	MOV.L	#_WPV_POWER_MONI,R1		;
	MOV.W	@R1,R2				;

	MOV.L	#_PVP_POWER_MONI,R1		;
	MOV.W	R2,@R1				;

;	====  2003-07-09 ===
	MOV.L	#_CYCL_DSP_DISENB,R1		;1:��\�� => ���]���ďo��
	MOV.W	@R1,R0				;0:�\��
	NOT	R0,R0				;
	AND	#BIT0,R0			;
	MOV.L	#_CMD_1CYCLE_DSP1,R1		;1:�\��
	MOV.W	R0,@R1				;

;	===================================
;	===	�����ʒu�\��		===
;	===================================
;	345.9=0 10��ڕ\��
;	345.9=1 �����_�\��


DAIHAITO_DSP_020:
	MOV.L	#_CB_SEQ_CB_COM345,R1		;345
	MOV.W	@R1,R0				;
	MOV.W	#BIT9,R4			;
	TST	R4,R0				;345.9�\���ؑ�
	TST_BIT_OF DAIHAITO_DSP_050		;

	MOV.L	#_RNA_ABS_MINPOS,R1		;
	MOV.L	@R1,R2				;
	MOV.L	#_PVP_SLIDE_POS,R1		;
	MOV.L	R2,@R1				;

	MOV.W	#BIT0,R0			;
	MOV.L	#_CMD_DAIPOS_DSP1,R1		;2003-07-09 ���Y�����ʒu�@ 0:��\���@1:�\��
	MOV.W	R0,@R1				;
	M_BRA	DAIHAITO_DSP_100		;


;	==== �W���̕\�� ====
DAIHAITO_DSP_050:
	MOV.L	#_PRD_DAI_POS1,R1		;//�␳�܂�
	MOV.L	@R1,R2				;

;----���ޯ�-------------
;;;;;	MOV.L	#_RNA_ABS_POS,R1			;//��ٽ��ʍ���(��Έʒu)
;;;;;	MOV.L	@R1,R2					;
;----------------------


	MOV.L	#_PVP_SLIDE_POS,R1		;�ײ�ވʒu�E�޲ʲĂ��܂߂��ʒu(�ׯ��͖��g�p)
	MOV.L	R2,@R1				;

	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//1:��r 0:��r�s��
	MOV.W	@R1,R0				;
	AND	#BIT0,R0			;
;----���ޯ�-------------
;;;;;	MOV.W	#BIT0,R0
;----------------------

	MOV.L	#_CMD_DAIPOS_DSP1,R1		;2003-07-09 ���Y�����ʒu�@ 0:��\���@1:�\��
	MOV.W	R0,@R1				;
DAIHAITO_DSP_100:


;	=======================================
;	======= 2006-12-05 =====
	MOV.L	#_PRD_KJP_CMP_ENB,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CMD_KJTECH_DSP1,R1		;
	MOV.W	R0,@R1				;


;	===== ���ޯ���� ===




;	==== 2003-07-01 ===
	MOV.L	#_OUT_PLS_SPD,R1	;//+/- 1000,000HZ �ɐ����ς��Ƃ���0pls/s�ɂȂ�
	MOV.L	@R1,R0
	MOV.L	#_PVP_OUT_PLS_SPD,R1	;SHIN
	MOV.L	R0,@R1			;

	MOV.L	#_ENC_PLS_SPD,R1	;//+/- 1000,000HZ �ɐ����ς��Ƃ���0pls/s�ɂȂ�
	MOV.L	@R1,R0
	MOV.L	#_PVP_ENC_PLS_SPD,R1	;;SHIN
	MOV.L	R0,@R1			;


	MOV.L	#_ABS_ENC_PLS_SPD,R1	;// 
	MOV.L	@R1,R0
	MOV.L	#_PVP_ABS_ENC_SPD,R1	;ABS
	MOV.L	R0,@R1			;

	MOV.L	#_ABS_OUT_PLS_SPD,R1	;// (MIN�@�\�L�� 1KHZ)
	MOV.L	@R1,R0
	MOV.L	#_PVP_ABS_OUT_SPD,R1	;ABS
	MOV.L	R0,@R1			;
	
	MOV.L	#_PV_ENC_SPD_PER,R1	;//0~110.00%
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_ENC_SPD_PER,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PV_OUT_SPD_PER,R1	;//0~110.00%
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_OUT_SPD_PER,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PVC_BRK_ENC_SPD,R1	;= R14(ad2)
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_BRK_ENC_SPD,R1
	MOV.W	R0,@R1			;

	MOV.L	#_ENC_PLS_SPD_DIR,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_ENC_SPD_DIR,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PVC_BRK_OUT_SPD,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_BRK_OUT_SPD,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_OUT_PLS_SPD_DIR,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_OUT_SPD_DIR,R1	;
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	2009-10-07			***
;	***					***
;	*******************************************
_DNM_TAIKI_DIR_DISP:
	SUB_START
;	----------2011-09-19 ��ڰ�ýĂ̑ҋ@�_-----
	MOV.L	#_BRKTST_SW_IN,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF DNM_TAIKI_DIRDISP_050	;

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360�x
	MOV.W	#BIT6,R2			;
	NOT	R2,R2				;
	AND	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_WPAR_BRKTST_ORGDEG,R4		;��ݸ�p�x����
	MOV.W	@R4,R2				;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;
	M_BRA	DNM_TAIKI_DIRDISP_200		;
;	-----------------------------

DNM_TAIKI_DIRDISP_050:

	MOV.L	#_SETX_POS_CTL_MATH,R1		;
	MOV.W	@R1,R0				;
	TST	#_DMATH_DNDRIV,R0		;
	TST_BIT_OF DNM_TAIKI_DIRDISP_100	;

;	--------- 2018-10-09�L�q(sit4-mc:2018-09-06���) --------------
	MOV.L	#_emg_err_flg,R1			;
	MOV.W	@R1,R0						;
	TST		R0,R0						;
	TST_BIT_OF DNM_TAIKI_DIRDISP_070	;


	MOV.L	#_MOVE_MODE_MATH_LATCH,R1	;//0:(�ӂ肱�ȊO �܂��� �i��E���_���[�h)1:(�ӂ肱��Ӱ��݂��Ă���)
	MOV.W	@R1,R0						;
	TST	#BIT0,R0						;
	TST_BIT_OF DNM_TAIKI_DIRDISP_070	;


	MOV.L	#_DNM_DIR_FLG_INC_LATCH,R1	;	//�ӂ肱�̏ꍇ�̑O��܂ł̓������
	MOV.W	@R1,R0						;
	TST		R0,R0						;
	TST_BIT_ON DNM_TAIKI_DIRDISP_075	;


DNM_TAIKI_DIRDISP_070:
;	----------------------------------------

	MOV.L	#_DNM_DIR_SET_FLG,R1		;//
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF DNM_TAIKI_DIRDISP_100	;

DNM_TAIKI_DIRDISP_075:

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360�x
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_DNM_SETX_UPAREA_DIG,R3	;2;��]���ҋ@�_(�㎀�_/�ҋ@�_)	
	MOV.W	@R3,R2				;
	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;
	M_BRA	DNM_TAIKI_DIRDISP_200		;

DNM_TAIKI_DIRDISP_100:
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360�x
	MOV.W	#BIT6,R2			;
	NOT	R2,R2				;
	AND	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_SETX_UPAREA_DIG,R3		;2;��]���ҋ@�_(�㎀�_/�ҋ@�_)	
	MOV.W	@R3,R2				;
	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;

DNM_TAIKI_DIRDISP_200:

	SUB_END
	M_RTS

;	*******************************************
;	***	Ҳ݂ɻ��ُI���E�`������v��	***
;	*******************************************
_CYCLE_END_DISP_SET:
	SUB_START
	MOV.W	#BIT0,R0			;
	MOV.L	#_HS_PVP_TAKIKI_FLG,R1		;
	MOV.W	R0,@R1				;
	SUB_END
	M_RTS



;	*******************************************
;	***	Ҳ݂ɻ��ُI���E�`������v��	***
;	*******************************************
	.IMPORT	_TRD_SHOT_SIG			;

_LOT_SIG_SET:
	SUB_START
	MOV.B	#BIT0,R0			;
	MOV.L	#_HS_PVP_LOTCNT_FLG,R1		;
	MOV.W	R0,@R1				;

;	----- 2014-09-29--- KOMTRAX�p
	MOV.L	#_CPUATOD_1CYCL_SIG,R1	;BIT0=0/BIT0=1 ���CPUA CLR CPUD
	MOV.W	R0,@R1				;



	SUB_END
	M_RTS


;	*******************************************
;	***	Ҳ݂ɻ��ُI���E�`������v��	***
;	*******************************************
	.EXPORT	_TRD_SIG_SET
_TRD_SIG_SET:
	SUB_START

	MOV.W	#H'0F,R0	
	MOV.L	#_TRD_SHOT_SIG,R1
	MOV.W	R0,@R1				;
	
	SUB_END
	M_RTS



