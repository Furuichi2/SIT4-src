;	***************************************************
;	***						***
;	***		���[�_�R�}���h����		***
;	***						***
;	***************************************************
;	***********************************
;	***	�ޯĕ��� STEP ���� 0~7	***
;	***********************************
;	�ޯĂ̏�ʂ���g�p����Ɩ��ʂ��Ȃ�

	.MACRO	BIT_STEP_CNTL1	FLG,LG,CALL0,CALL1,CALL2,CALL3,CALL4,CALL5,CALL6,CALL7,CALL8
	MOV.L	#\FLG,R10		;
	MOV.\LG	@R10,R0			;
	TST	R0,R0			;�����ꂩON?
	TST_BIT_OF JMP8\@		;

	TST	#BIT7,R0		;
	TST_BIT_OF JMP1\@		;
	FAR_JSR	#\CALL8,R10		;
	M_BRA	JMP_END\@		;
JMP1\@:					;
	TST	#BIT6,R0		;
	TST_BIT_OF JMP2\@		;
	FAR_JSR	#\CALL7,R10		;
	M_BRA	JMP_END\@		;
JMP2\@:					;
	TST	#BIT5,R0		;
	TST_BIT_OF JMP3\@		;
	FAR_JSR	#\CALL6,R10		;
	M_BRA	JMP_END\@		;
JMP3\@:					;
	TST	#BIT4,R0		;
	TST_BIT_OF JMP4\@		;
	FAR_JSR	#\CALL5,R10		;
	M_BRA	JMP_END\@		;
JMP4\@:					;
	TST	#BIT3,R0		;
	TST_BIT_OF JMP5\@		;
	FAR_JSR	#\CALL4,R10		;
	M_BRA	JMP_END\@		;
JMP5\@:					;
	TST	#BIT2,R0		;
	TST_BIT_OF JMP6\@		;
	FAR_JSR	#\CALL3,R10		;
	M_BRA	JMP_END\@		;
JMP6\@:					;
	TST	#BIT1,R0		;
	TST_BIT_OF JMP7\@		;
	FAR_JSR	#\CALL2,R10		;
	M_BRA	JMP_END\@		;
JMP7\@:					;
	FAR_JSR	#\CALL1,R10		;BIT0 ON
	M_BRA	JMP_END\@		;

JMP8\@:					;
	FAR_JSR	#\CALL0,R10		;
JMP_END\@:

	.ENDM

;	***************************************************
;	***		�f�[�^�ϊ�	2001-07-08	***
;	***************************************************
;	.MACRO	INTEL_WORD REG1,REG2
;	SWAP.B	\REG1,\REG2
;	.ENDM


;	***********************************************************
;	*	ү����sx dpram ���ϯ�� ���۰�,�׸�,�ް��̈�	***
;	***********************************************************
;	���۰��׸� 0000h
;				A4000000
;	*******************************************
;	***	�����A�h���XEQU��`		***
;	*******************************************
;	========== DPRAM �������ڽ ==========

;_MAIN_MSGWR_TOP				.EQU	H'400			;PC/AT==>ISA==>PRO
;_MAIN_MSGRD_TOP				.EQU	H'700			;PC/AT<==ISA<==PRO

;_MSG_OUT_BOX				.EQU	_MAIN_MSGRD_TOP		;

;_MAIN_MSGSRQ_DAT			.EQU	H'1			;ү���ޑ��M�׸��ް�
_MAIN_MSGRRQ_DAT			.EQU	H'1			;ү���ގ�M�׸��ް�

;	-------ү���ޗ̈�------
;_MAIN_MSGWR_MAX				.EQU	D'523			;ү���ޑ��M�̈�
;_MAIN_MSGRD_MAX				.EQU	D'523			;ү���ޑ��M�̈�


;	*********************************************************
;	*	i/o sx dpram ���ϯ�� ���۰�,�׸�,�ް�		*
;	*********************************************************
;	*******************************************
;	***					***
;	***					***
;	***	���[�_�R�}���h�p//�a�n�w	***
;	***					***
;	***					***
;	*******************************************
;	۰�޺����	�ڰ�max

MsgSZ_frameMAX 		.DEFINE		"511"		;512

;	-------- ͯ�ޕ� ------------
;;MAIN_Lcmd_OFS		.DEFINE		"H'0B"		;���ڽ�̾��
MAIN_Lcmd_OFS		.DEFINE		"H'01"		;���ڽ�̾��
LcmdIM_HDCNT		.DEFINE		"3"		;ү�����ް�����+3

LcmdIM_HDstrcod		.DEFINE		"0"		;���ĺ��� 0x5a			[1
LcmdIM_HDtransl		.DEFINE		"1"		;�`����L			[2
LcmdIM_HDtransh		.DEFINE		"2"		;�`����H			[3
LcmdIM_CDprcsts		.DEFINE		"3"		;�����ð��			[4
LcmdIM_CDcnmath		.DEFINE		"4"		;�ڑ����� conection mathed	[5
LcmdIM_CDcnIDl		.DEFINE		"5"		;�ڑ�id-high			[6
LcmdIM_CDcnIDh		.DEFINE		"6"		;�ڑ�id-high			[7
LcmdIM_CDmcncod		.DEFINE		"7"		;�@��I��cod 0x11		[8
LcmdIM_CDtrlock		.DEFINE		"8"		;�`������ۯ�			[9
LcmdIM_CDpassll		.DEFINE		"9"		;�߽ܰ��			[10
LcmdIM_CDpasslh		.DEFINE		"10"		;�߽ܰ��			[11
LcmdIM_CDpasshl		.DEFINE		"11"		;�߽ܰ��			[12
LcmdIM_CDpasshh		.DEFINE		"12"		;�߽ܰ��			[13
LcmdIM_CDcomnd		.DEFINE		"13"		;�����				[14
LcmdIM_CDmode		.DEFINE		"14"		;Ӱ��				[15
LcmdIM_CDeinfo		.DEFINE		"15"		;�I�����			[16
LcmdIM_CDseqno		.DEFINE		"16"		;seq �ԍ�			[17
LcmdIM_CDdcntl		.DEFINE		"17"		; rd/wr data�ڰ�bytel		[19
LcmdIM_CDdcnth		.DEFINE		"18"		; rd/wr data�ڰ�byteh		[20

LcmdIM_DTTOP		.DEFINE		"3+16"	; wr data top

;	--------------- ����ޖ����ް�̫�ϯ� -----------	*/
LcmdIM_DT_mincnt	.DEFINE		"6"			;�ŏ��� 6��
LcmdIM_DT_RDWR01_memno	.DEFINE		"LcmdIM_DTTOP+0"	; data format 01-��؎��
LcmdIM_DT_RDWR01_adrsl	.DEFINE		"LcmdIM_DTTOP+1"	; data format 01-adress-l
LcmdIM_DT_RDWR01_adrsm	.DEFINE		"LcmdIM_DTTOP+2"	; data format 01-adress-m
LcmdIM_DT_RDWR01_adrsh	.DEFINE		"LcmdIM_DTTOP+3"	; data format 01-adress-h
LcmdIM_DT_RDWR01_dcntl	.DEFINE		"LcmdIM_DTTOP+4"	; data format 01-�Ǐo�޲Ē�l
LcmdIM_DT_RDWR01_dcnth	.DEFINE		"LcmdIM_DTTOP+5"	; data format 01-�Ǐo�޲Ē�m
LcmdIM_DT_RDWR01_dattop	.DEFINE		"LcmdIM_DTTOP+6"	; data top[wr]


;	*******************************************
;	***	���ݽ�ԍ��܂�			***
;	*******************************************
LcmdIM_MSGcntDcnt	.DEFINE		"16"					;�����ð���`�`����
LcmdIM_MSGcntSeq	.DEFINE		"14"					;�����ð���`���ݽ�ԍ��܂�
LcmdIM_MSGMOVcnt	.DEFINE		"MAIN_Lcmd_OFS+ LcmdIM_DTTOP +LcmdIM_DT_mincnt"	;0B+19 +6



;	*******************************************
;	***	ڽ��ݽ�ް�			***
;	*******************************************
CDprcsts_NOMAL		.DEFINE		"00"	;NOMAL CODE
CDprcsts_ERR42		.DEFINE		"H'42"	;ERR CODE ��ر����ُ�



;	----------------------
_MONI_ram_top		.DEFINE		"_TREND_INFO_TOP-H'18000"	;NOMAL CODE

;	***************************************************
;	***						***
;	***		���[�_�R�}���h����		***
;	***						***
;	***************************************************
;	***************************************************
;	***	۰�޺���މ���,�]��,����č쐬		***
;	***************************************************
;	LODER_COM_FLG
;	BIT0:START 	--->���޼����׸�40HON
;			-->DRIVER COMMAND �捞
;			-->���޼����׸�CLR       
;	BIT2:�{��1����	-->ڽ��ݽ�쐬            
;	BIT4:		-->ڽ��ݽ���� IRQ SET    
;	BIT6:		44H=0//�҂�[]

LOD_STEP_DLY1	.EQU	1			;20msec
LOD_STEP_DLY2	.EQU	1			;200			;20msec
LOD_STEP_DLY3	.EQU	1			;200			;20msec

	.ALIGN	4				;
_LODER_CMD_IF:
	SUB_START
	BIT_STEP_CNTL1	FLG=_LODER_COM_FLG	,;
+			LG=B			,	;BYTE FLAG
+		CALL0=_LOD_STR_CHK		,	;ALL OFF  ?SCAN	 IF START THEN [RD+FLAG CLR] "BIT6"
+		CALL1=_LOD_DUMMY		,	;BIT0
+		CALL2=_LOD_DUMMY		,	;BIT1
+		CALL3=_LOD_DUMMY		,	;BIT2
+		CALL4=_LOD_DUMMY		,	;BIT3
+		CALL5=_LOD_DUMMY		,	;BIT4
+		CALL6=_LOD_RDWR_PROC		,	;BIT5
+		CALL7=_LOD_RESPONS_MK_WR	,	;BIT6 ON  1SCAN	 	[DATA MAKE + WR + RRQ ON + IRQ]
+		CALL8=_LOD_END_CHK			;BIT7 ON  ?SACN	
	SUB_END					;
	M_RTS					;

_LOD_DUMMY:
	M_RTS

;	***********************************
;	***				***
;	***	�J�n����		***
;	***	LODER_COM_FLG=0		***
;	***	���������� BIT5=1	***
;	***				***
;	***********************************
_LOD_STR_CHK:
	SUB_START

	MOV.L	#_HMI2CB_LDCMD_FLG,R10			;�J�n�׸ޱ��ڽ ISA-->PRO
	MOV.W	@R10,R0					;
	TST	R0,R0					;
	TST_BIT_OF LOD_STR_CK_EXT			;MAIN_MSGSRQ_DAT,R0

	FAR_JSR #_LODER_CMD_READ,R10			;

	MOV.L	#_LODER_COM_FLG,R10			;
	MOV	#BIT5,R0				;
	MOV.B	R0,@R10					;



LOD_STR_CK_EXT:
	SUB_END
	M_RTS

;	***********************************
;	***	READ//WRITE ����	***
;	***********************************
;	READ  --->MEM / DATA ---> OUTBOX ��
;	WRITE --->DPRAM      ---> WORK MEM��
_LOD_RDWR_PROC:
	SUB_START
	MOV.L	#_MSG_IN_COMMND,R10		;
	MOV.B	@R10,R0				;
	TST	R0,R0				;
	TST_BIT_ON LOD_RDWR_PR050		;
	FAR_JSR	#_LODER_RD_PROC,R10		;READ ����  WORK MEM--->OUT BOX
	M_BRA	LOD_RDWR_PR100			;

LOD_RDWR_PR050:					;
	FAR_JSR	#_LODER_WR_PROC,R10		;WRITE ���� DPRAM   --->WORK MEM
LOD_RDWR_PR100:
	FAR_JSR	#_LODER_ELSE_MAK,R10		;�����ð��,DATA����,BCC

;	------------- �ް��捞���� -------------------
	MOV.L	#_LODER_COM_FLG,R10		;
	MOV	#BIT6,R0			;
	MOV.B	R0,@R10				;


	MOV.L	#_HMI2CB_LDCMD_FLG,R10		;�J�n�׸ޱ��ڽ
	XOR	R0,R0					;
	MOV.W	R0,@R10					;

LOD_RDWR_PREXT:
	SUB_END
	M_RTS

;	***********************************
;	***	�쐬�{WR+�׸�ON+IRQ ON	***
;	***********************************
_LOD_RESPONS_MK_WR:
	SUB_START

	FAR_JSR	#_RESPONS_OUT,R0			;

;	========= �׸�ON+�������� =======
	MOV.L	#_CB2HMI_LDCMD_FLG,R10				;ү���ގ�M�׸ޱ��ڽ 44H ڽ��ݽ����
	MOV.W	#_MAIN_MSGRRQ_DAT,R0				;
	MOV.W	R0,@R10						;

	MOV.L	#_LODER_COM_FLG,R10		;
	MOV	#BIT7,R0			;
	MOV.B	R0,@R10				;


LOD_RESPONS_MKWR_EXT:				;
	SUB_END
	M_RTS

;	***********************************
;	***	�I������		***
;	***********************************
_LOD_END_CHK:
	SUB_START
	MOV.L	#_CB2HMI_LDCMD_FLG,R10				;ү���ގ�M�׸ޱ��ڽ 44H ڽ��ݽ����
	MOV.W	@R10,R0						;
	MOV.W	#_MAIN_MSGRRQ_DAT,R1				;

	CMP/EQ	R0,R1						;
	BT	LOD_END_CK_EXT					;�������ް��Ɠ��� THEN EXIT

	MOV.L	#_LODER_COM_FLG,R10			;
	XOR	R0,R0					;
	MOV.B	R0,@R10					;

;	--------------------------------------------
	MOV.L	#_MSG_DATA_ADR,R10			;�Ǐo/�������ڽ     ���ڽ��2�{����K�v�����邩? "NO!"
	MOV.L	@R10,R0					;
	MOV.L	#_DTCHG_LOD_CMD_ADR,R11			;
	MOV.L	R0,@R11					;

	MOV.L	#_MSG_DATA_CNT,R10			;"511 LIMIT"
	MOV.W	@R10,R0					;
	MOV.L	#_DTCHG_LOD_CMD_DAT,R10			;
	MOV.W	R0,@R10					;

	MOV.L	#_MSG_IN_COMMND,R10			;
	MOV.B	@R10,R0					;0:READ 1:WRITE
	MOV.L	#_DTCHG_LOD_CMD_STS,R11			;
	MOV.B	R0,@R11					;
	MOV.L	#_DTCHG_LOD_CMD_STS2,R11			;"TMP USED"
	MOV.B	R0,@R11					;

	MOV	R0,R1
	MOV.L	#_DTCHG_LOD_CMD_CNT,R10			;
	MOV.B	@R10,R0					;
	ADD	#1,R0					;
	MOV.B	R0,@R10					;

;	=============================================
	MOV.L	#_LOD_CHK_MONI_STS,R10			;���ޯ��p
	EXTU.B	R1,R1					;
	EXTU.B	R0,R0					;
	SHLL8	R1					;
	OR	R1,R0					;
	MOV.W	R0,@R10					;


LOD_END_CK_EXT:
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	۰�޺���ނׂ̈̏���		***
;	***					***
;	*******************************************
;	*******************************************
;	***	۰�޺����ү���ގ�o��		***
;	*******************************************
;	DPRAM DATA -------->IN BOX
;	Read CMD//Write CMD
_LODER_CMD_READ:
	SUB_START

;	-----------------------------------------------------------------
	FAR_JSR	#_HMI_CMD_MOV,R0				;

;	-----------------------------------------------------------------
	MOV.L	#_IN_LDCMD_DAT,R11			;
	MOV.L	#_MSG_OUT_BOX,R12				;TOP�`DATA��1�ڰт܂ŏo�͗pBOX��
	MOV.L	#((LcmdIM_MSGMOVcnt+1)/2),R1			;BYTE --> WORD �����\�Ƃ��� +1�͐؏�p
								;[0B+19 +6]�Œ�I�ɕK���Ԃ�
	FAR_JSR	#_WORD_BLOCK_MOV,R10				;��ۯ��]�� R11-- WORD --->R12

;	-------------------------------------------
;	---		����ގ�o		---
;	-------------------------------------------
;	------	CMD=00,MODE=00 	READ    SH-WORK  --> DPRAM 	-----
;	------	CMD=01,MODE=00	WRITE   DPRAM    --> SH-WORK	-----
;	------- "ELSE READ"		--
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_CDcomnd,R10	;
	MOV.B	@R10,R0							;�����
	CMP/EQ	#1,R0							;
	BT	LODER_CMD_CMDRD						;
	XOR	R0,R0							;
LODER_CMD_CMDRD:							;
	MOV	R0,R2							;PUSH MODE DATA
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_CDmode,R10	;
	MOV.B	@R10,R0							;Ӱ��
	CMP/EQ	#0,R0							;
	BT	LODER_CMD_MODERD					;
	XOR	R2,R2							;DATA ERR THEN READ MODE SET
LODER_CMD_MODERD:							;
	MOV.L	#_MSG_IN_COMMND,R10					;
	MOV.B	R2,@R10							;0:READ 1:WRITE ELSE READ

	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_CDdcntl,R10	;0B+17d
	MOV.W	@R10,R0							;
	INTEL_WORD REG1=R0,REG2=R0
	EXTU.W	R0,R0								;
	SHLR	R0							;2�̔{���␳
	SHLL	R0							;
	MOV.L	#_MSG_BYTE_CNT,R10					;(NO-USED)
	MOV.W	R0,@R10							;
	SUB_END
	M_RTS

;	***********************************************************
;	***	READ ����ޏ���  SH-WORK MEM --->OUT-BOX		***
;	***********************************************************
_LODER_RD_PROC:									;READ ����  WORK MEM--->OUT BOX
	SUB_START
	FAR_JSR	#_LODER_ADRESS_CNT_GET,R10					;ANS.R5 ADRESS=2BYTE
										;ANS.R6 CNT
	MOV.L	#_MONI_ram_top,R4						;ܰ�top
	ADD	R4,R5								;

	MOV	R5,R11								;�]����ADRESS
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_dattop,R12		;�]���� 0B+19+5=
	MOV	R6,R1								;�]��ܰ�ސ�
	FAR_JSR	#_ISA_WORD_BLOCK_MOV,R10						;��ۯ��]�� R11-- WORD --->R12 

;	-------------  �Ǐo�ް�W�� ��� ---------------------------------------
	PUSH_REG1 R6
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_dcntl,R10	;
	INTEL_WORD REG1=R6,REG2=R6
	MOV.W	R6,@R10							
									;�Ǐo�ް�W�� SET
	POP_REG1 R6
										;�Ǐo�ް�W�� SET
;	--------------- BYTEn ��� ----------------------------------------------
	SHLL	R6								;�Ǐo�ް�W��*2 + "6"
	MOV.L	#LcmdIM_DT_mincnt,R4						;
	ADD	R4,R6								;
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_CDdcntl,R10	;
	INTEL_WORD REG1=R6,REG2=R6
	MOV.W	R6,@R10								;
	SUB_END
	M_RTS									;

;	***********************************************************
;	***	WRITE ����ޏ���  DPRAM MEM --->SH-WORK		***
;	***********************************************************
_LODER_WR_PROC:					;WRITE ���� DPRAM   --->WORK MEM
	SUB_START
	FAR_JSR	#_LODER_ADRESS_CNT_GET,R10	;ANS.R5 ADRESS
						;ANS.R6 CNT
	MOV.L	#_MONI_ram_top,R4		;
	ADD	R4,R5				;�]����ADRESS

;	---------------- �������� dpram-->sram ---------------------------------
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_dattop,R11	;�]���� 0B+19+5=
	MOV	R5,R12								;�]���� ADRESS
	MOV	R6,R1								;�]��ܰ�ސ�
	FAR_JSR	#_ISA_WORD_BLOCK_MOV,R10					;��ۯ��]�� R11-- WORD --->R12 

;	-------------  �����ް�W�� ��� ---------------------------------------
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_dcntl,R10
	INTEL_WORD REG1=R6,REG2=R6
	EXTU.W	R6,R6								;
	MOV.W	R6,@R10
										;�Ǐo�ް�W�� SET

;	--------------- BYTEn ��� ----------------------------------------------
	MOV.L	#LcmdIM_DT_mincnt,R6						;
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_CDdcntl,R10
	INTEL_WORD REG1=R6,REG2=R6
	EXTU.W	R6,R6								;
	MOV.W	R6,@R10

										;BYTEN MAKE END
	SUB_END
	M_RTS

;	***********************************************************
;	***		���ڽ/���� GET				***
;	***********************************************************
;	ANS.R5 ADRESS
;	ANS.R6 CNT
_LODER_ADRESS_CNT_GET:
	SUB_START
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_adrsl,R10
	MOV.B	@R10,R0					;
	MOV	R0,R2					;
	EXTU.B	R2,R2					;

	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_adrsm,R10
	MOV.B	@R10,R0					;
	MOV	R0,R3					;
	EXTU.B	R3,R3					;

	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_adrsh,R10
	MOV.B	@R10,R0					;
	EXTU.B	R0,R0					;

;	R0,R3,R2
	SHLL16	R0					;
	SHLL8	R3					;
	OR	R2,R0					;
	OR	R3,R0					;R2.ADRESS
;	===================/////////// ================
	SHLR	R0					;
	SHLL	R0					;"*2"

;	===================///////////=================

	MOV.L	#_MSG_DATA_ADR,R10			;�Ǐo/�������ڽ     ���ڽ��2�{����K�v�����邩? "NO!"
	MOV.L	R0,@R10					;��������128K���Я�
	MOV	R0,R5					;

LODER_ADRCNT_GET050:					;

;;;	MOV.L	#H'3FFFF,R4				;
	MOV.L	#H'7FFFF,R4				;(2006-11-21)
	CMP/HS	R5,R4					;R5[ADRESS] =< R4 THEN NOMAL
	BT	LODER_ADRCNT_GET100			;
	MOV.L	#_MSG_ERR_IN,R10				;
	MOV.B	@R10,R0					;
	OR	#(BIT7+BIT1),R0				;���шُ����
	MOV.B	R0,@R10					;
	XOR	R5,R5					;
LODER_ADRCNT_GET100:					;

;	-------------- WORD ���ǂݏo�� -------
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS+LcmdIM_DT_RDWR01_dcntl,R10	;
	MOV.W	@R10,R6								;
	INTEL_WORD REG1=R6,REG2=R6						;
	EXTU.W	R6,R6								;

	MOV.L	#MsgSZ_frameMAX,R4			;
	CMP/HS	R6,R4					;R5 =< R4 THEN NOMAL
	BT	LODER_ADRCNT_GET150

	MOV.L	#_MSG_ERR_IN,R10				;
	MOV.B	@R10,R0					;
	OR	#(BIT7+BIT2),R0				;���шُ����
	MOV.B	R0,@R10					;
	XOR	R6,R6					;
LODER_ADRCNT_GET150:					;
	MOV.L	#_MSG_DATA_CNT,R10			;"511 LIMIT"
	MOV.W	R6,@R10					;ANS=R6 USED
	SUB_END
	M_RTS						;

;	��Ԓn����̱����̏ꍇ�ͼ��шُ�
;	LIMIT 512W
;	LIMIT ����͋����ɒu��������

;	*******************************************
;	***	�ް�����,�����ð��,������	***
;	*******************************************
_LODER_ELSE_MAK:
	SUB_START
	MOV.L	#_MSG_ERR_IN,R10			;
	MOV.B	@R10,R2				;

	MOV.L	#_MSG_ERR_FLG,R11		;
	MOV.B	@R11,R1				;
	OR	R2,R1				;
	MOV.B	R1,@R11				;
	XOR	R0,R0				;
	MOV.B	R0,@R10				;_IN CLR


	MOV.B	#CDprcsts_NOMAL,R0		;
	TST	R2,R2				;
	TST_BIT_OF LODER_ELSE_MKPROC_020	;NOMAL JUMP
	MOV.B	#CDprcsts_ERR42,R0		;
	MOV.B	#CDprcsts_NOMAL,R0		;���ޯ�
LODER_ELSE_MKPROC_020:
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_CDprcsts,R10	;�����ð��NOMAL
	MOV.B	R0,@R10

;	----------- ͯ�ޕ��ް��� ----------
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_CDdcntl,R10
	MOV.W	@R10,R0						;
	INTEL_WORD REG1=R0,REG2=R0				;
	EXTU.W	R0,R0						;
;	===================PC/AT�̿�Ă�������========================
	MOV.W	#MsgSZ_frameMAX+LcmdIM_DT_mincnt+(LcmdIM_CDdcnth+1-LcmdIM_HDCNT+1),R4	;18+1-3+1
	CMP/GE	R0,R4									;R0 =< R4
	BT	CMD_SUM_CHK_CHK80							;
CMD_SUM_CHK_CHK20:
	MOV.W	#2,R0								;0~2
CMD_SUM_CHK_CHK80
;	===========================================

										;BYTEn LOAD
	MOV.L	#(LcmdIM_CDdcnth+1-LcmdIM_HDCNT+1),R4				;18+1-3+1=19-3=16+1[BCC]
	ADD	R4,R0								;16+ADR-L~DATA END +1

	PUSH_REG1	R0
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_HDtransl,R10
	INTEL_WORD REG1=R0,REG2=R0
	MOV.W	R0,@R10						;��SAVE
	POP_REG1	R0

	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS,R10	;R10=TOP TOP ADRESS
								;R0:�`����

	PUSH_REG1	R0
	PUSH_REG1	R10							;"TOP+1"
	MOV	R10,R12								;Input TOP ADRESS R12
										;R0:�ް���


	FAR_JSR	#_LODER_SUM_MAK,R10						;R2:ANS
	POP_REG1	R10							;TOP
	POP_REG1	R0							;
	
	ADD	#LcmdIM_HDCNT-1,R0						;TOP + �`����  "BCC"
	
	;------------- ISA_SWAP -----------
	MOV.B	R2,@(R0,R10)							;ISA-------BYTE ���̂܂�
	SUB_END
	M_RTS

;	***********************************
;	***	LODER BCC MAKE		***
;	***********************************
;	Input R12:�ް�L���ڽ  [����]
;	Input R0 :�ް�H,L��
;	ANS   R2 :SUM DATA
_LODER_SUM_MAK:
	SUB_START
;	--------------- BCC �쐬 ------------
;	R12:�ް�������:BCC �Ώ�TOP
;	R0:BCC�܂ތ�

	ADD	#H'FF,R0				;-1 [BCC�܂܂Ȃ���=�������������ڽ[�ް�����������݂�]
	ADD	#LcmdIM_HDCNT-1,R0			;�����̌����܂�
	XOR	R2,R2					;
	ADD	#1,R12					;ͯ�ނ�����[����TOP]

;	---- �������籸���J�n�Ŋ������ŻтȂ̂ŔԒn�̏��Ԃ͕���ėǂ� ---
SUM_MAK_LOOP:
	TST	R0,R0					;
	TST_BIT_OF SUM_MAK_END				;
	MOV.B	@R12,R1					;
	EXTU.B	R1,R1					;
	ADD	R1,R2					;
	ADD	#1,R12					;ADRESS +1
	ADD	#H'FF,R0				;CNT    -1
	M_BRA	SUM_MAK_LOOP				;
SUM_MAK_END:						;
	NEG	R2,R2					;
	SUB_END
	M_RTS

;	***********************************
;	***	ڽ��ݽ�o��		***
;	***********************************
_RESPONS_OUT:					;
	SUB_START
;	----------- ͯ�ޕ��ް��� ----------
	FAR_JSR	#_CB_RESPONS_MOV,R0

;;	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS+LcmdIM_HDtransl,R10
;;	MOV.W	@R10,R1
;;	INTEL_WORD REG1=R1,REG2=R1
;;	EXTU.W	R1,R1								;
;;	MOV.L	#(MAIN_Lcmd_OFS+LcmdIM_HDCNT+1)+2,R4				;0B+3+��+1:�����␳+2 "�\��"
;;	ADD	R4,R1								;
;;	SHLR	R1								;BYTE-->WORD
;;	MOV.L	#_MSG_OUT_BOX,R11						;
;;	MOV.L	#_MAIN_MSGRD_TOP+_ISAdp_top,R12						;
;;	FAR_JSR	#_WORD_BLOCK_MOV,R10						;

	SUB_END
	M_RTS									;




;	***********************************
;	***				***
;	***				***
;	***				***
;	***********************************
;	+0 --> +B
;	+1 --> +C
;	...
_HMI_CMD_MOV:
	SUB_START
	MOV.L	#_HMI2CB_LDCMD_DAT,R10				;
	MOV.L	#_IN_LDCMD_DAT+MAIN_Lcmd_OFS,R11		;
	MOV.W	#D'512/2,R3					;

HMI_CMDMOV_100:
	MOV.W	@R10+,R0					;
	SWAP.B	R0,R1						;R0=+0 R1=+1

	MOV.B	R1,@R11
	ADD	#1,R11
	MOV.B	R0,@R11
	ADD	#1,R11						;

	ADD	#-1,R3						;
	TST	R3,R3						;
	TST_BIT_ON HMI_CMDMOV_100				;
	SUB_END
	M_RTS

_CB_RESPONS_MOV
	SUB_START
	MOV.L	#_MSG_OUT_BOX+MAIN_Lcmd_OFS,R10		;
	MOV.L	#_CB2HMI_LDCMD_DAT,R11			;
	MOV.W	#D'512/2,R3				;
	
CB_RESPONSMOV_100
	MOV.B	@R10+,R0
	MOV.B	@R10+,R1
	EXTU.B	R0,R0			;
	EXTU.B	R1,R1			;
	SHLL8	R0			;
	OR	R1,R0			;
	MOV.W	R0,@R11			;
	ADD	#2,R11			;
	ADD	#-1,R3
	TST	R3,R3			;
	TST_BIT_ON CB_RESPONSMOV_100	;

	SUB_END
	M_RTS

	
;	*******************************************
;	***	R11-->R0-->R12 WORD		***
;	***	����=R1				***
;	*******************************************
;	"R2=2 �ݸ�����" R0,R1,R0,R11,R12
;	Input 	R1:CNT
;		R11:SRC	ADRESS
;		R12:DST	ADRESS
;	R0 WORK
;
	.ALIGN	4				;
_WORD_BLOCK_MOV:
	SUB_START
WORD_BLOCKMOV_LOOP:
	TST	R1,R1				;WORD CNT
	TST_BIT_OF WORD_BLOCK_MV_END		;
	MOV.W	@R11,R0				;
	MOV.W	R0,@R12				;
	ADD	#2,R11				;
	ADD	#2,R12				;
	ADD	#H'FF,R1			;-1
	M_BRA	WORD_BLOCKMOV_LOOP		;

WORD_BLOCK_MV_END:				;
	SUB_END					;
	M_RTS

;	*******************************************************************
;	***	ISA ��Ԃ��ް�(����)��WORD������۰ׂƂ��Ĉ�����		***
;	*******************************************************************
;	R11:�ް��� TOP
;	R12:�ް��� 
;	R1 :�ް���(ܰ�ސ�)
;
_ISA_WORD_BLOCK_MOV:
	SUB_START

ISA_WORD_BLOCKMOV_LOOP:
	TST	R1,R1				;WORD CNT
	TST_BIT_OF ISA_WORD_BLOCK_MV_END	;
	MOV.W	@R11+,R0			;
	INTEL_WORD R0,R0
	MOV.W	R0,@R12				;
	ADD	#2,R12				;
	ADD	#H'FF,R1			;-
	M_BRA	ISA_WORD_BLOCKMOV_LOOP		;

ISA_WORD_BLOCK_MV_END:				;
	SUB_END
	M_RTS