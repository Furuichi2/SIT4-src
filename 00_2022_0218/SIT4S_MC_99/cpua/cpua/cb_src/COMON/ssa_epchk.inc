;	***********************************
;	***				***
;	***	EP�ݻ����		***
;	***				***
;	***********************************
;	�d��������
;	�ʒu�Â��;����������,�Ɨ������@�\
;	ANTI-ON���Ă���

	.EXPORT		_EPSEN_CLR			

	.GLOBAL		_PAR_EPCHK_SEL		;5 0:EP�ݻ�������Ȃ� 1:��������
	.GLOBAL		_PAR_EP1STR_DLYTM	;6 �J�n�x������ ms
	.GLOBAL		_PAR_EP2FVINOF_ERTM	;7 �Е��ڰOF(0)�m�F���Ԍ���ѱ��
	.GLOBAL		_PAR_EP3BRKON_DLYTM	;8 ��ڰ�ON�o�͒x��
	.GLOBAL		_PAR_EP4EPINOF_ERTM	;9 EP�ݻoff�m�F���Ԍ���ѱ��
	.GLOBAL		_PAR_EP5RSTON_DLYTM	;10 EP�ݻؾ��ON�x������
	.GLOBAL		_PAR_EP6RSTON_JGTM	;1 ؾ��ON���Ԍ����莞��
	.GLOBAL		_PAR_EP6RSTOF_INTTM	;2 OFF���-��َ���
	.GLOBAL		_PAR_EP6RST_RETRY	;3 ؾ����ײ��
	.GLOBAL		_PAR_EP7AB_DLYTM	;4 CPUA-->CPUBýĒx������
	.GLOBAL		_PAR_EP7END_DLYTM	;5 CPUB-->�I���x������


	.MACRO	STEP_NEXT MEM
	MOV.L	#\MEM,R1	;
	MOV.W	@R1,R0		;
	ADD	#1,R0		;
	MOV.W	R0,@R1		;
	.ENDM

	.ALIGN	4				;
_EP_JMP_TBL

	.DATA.L		EP_STEP_USE_RY_DATSET_A	;0
	.DATA.L		EP_STEP_USE_RY_A	;1 �Ќ��L��RY-ON,�Ќ����ݻ�m�F
	.DATA.L		EP_STEP_VALVON_DATSET	;2
	.DATA.L		EP_STEP_VALVON_COM	;3 �����ON,EP�ݻ�m�F
	.DATA.L		EP_STEP_EPSENSIG_A	;4
	.DATA.L		EP_STEP_RESET_DATSET1	;5
	.DATA.L		EP_STEP_RESETON_COM	;6
	.DATA.L		EP_STEP_ENDSIG_A	;7
	.DATA.L		EP_STEP_USE_RY_DATSET_B	;8
	.DATA.L		EP_STEP_USE_RY_B	;9
	.DATA.L		EP_STEP_VALVON_DATSET	;10
	.DATA.L		EP_STEP_VALVON_COM	;11
	.DATA.L		EP_STEP_EPSENSIG_B	;12
	.DATA.L		EP_STEP_RESET_DATSET1	;13
	.DATA.L		EP_STEP_RESETON_COM	;14
	.DATA.L		EP_STEP_ENDSIG_B	;15
	.DATA.L		EP_STEP_XX		;16
	.DATA.L		EP_STEP_XX		;17
	.DATA.L		EP_STEP_XX		;18
	.DATA.L		EP_STEP_XX		;19
	.DATA.L		EP_STEP_XX		;20
	.DATA.L		EP_STEP_XX		;21
	.DATA.L		EP_STEP_XX		;22
	.DATA.L		EP_STEP_XX		;23
	.DATA.L		EP_STEP_XX		;24
	.DATA.L		EP_STEP_XX		;25
	.DATA.L		EP_STEP_XX		;26
	.DATA.L		EP_STEP_XX		;27
	.DATA.L		EP_STEP_XX		;28
	.DATA.L		EP_STEP_XX		;29
	.DATA.L		EP_STEP_XX		;30
	.DATA.L		EP_STEP_XX		;31
	.DATA.L		EP_STEP_XX		;32



	.ALIGN	4				;
	.EXPORT	_EP_SENCER_CHECK
_EP_SENCER_CHECK
	SUB_START

	MOV.L	#_EPCHK_FLG,R1			;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON EP_SENCER_CK050		;

	MOV.L	#_EPCHK_COM,R1			;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON EP_SENCER_CK020		;
	M_BRA	EP_SENCER_CKEXT			;IDEL

;	--------- �J�n����-----------
EP_SENCER_CK020:

	MOV.L	#(_PAR_EPCHK_SEL-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;
	CMP/EQ	#1,R0							;
	BT	EP_SENCER_CK030						;
	M_BRA	EP_SENCER_CK800						;����I��


EP_SENCER_CK030:

	FAR_JSR	#_EP_SENCHK_STOPCONF1,R0	;
	TST	R0,R0				;
	TST_BIT_OF EP_SENCER_CK040		;

	XOR	R0,R0
	MOV.L	#_EPCHK_STS,R1			;
	MOV.W	R0,@R1				;
	M_BRA	EP_SENCER_CK900			;

EP_SENCER_CK040:
	MOV.B	#BIT0,R0		;
	MOV.L	#_EPCHK_FLG,R1		;
	MOV.W	R0,@R1			;

	XOR	R0,R0			;
	MOV.L	#_EPCHK_STEP,R1		;
	MOV.W	R0,@R1			;

	MOV.B	#BIT0,R0		;
	MOV.L	#_EPCHK_STS,R1		;
	MOV.W	R0,@R1			;

;	---------------------------
	XOR	R2,R2
	MOV.L	#_EPCHK_DLY_TIM,R1					;
	MOV.W	R2,@R1							;

	M_BRA	EP_SENCER_CKEND		;


EP_SENCER_CK050:
	TST	#BIT7,R0		;
	TST_BIT_OF EP_SENCER_CK100	;
	M_BRA	EP_SENCER_CKEND	;

;	---------- ������---------------
EP_SENCER_CK100:

	DN_TIME LG=W,MEM_ADR=_EPCHK_DLY_TIM,WKREG1=R1,WKREG2=R4	;

;	-------- ���f����--------------------
	FAR_JSR	#_EP_SENCHK_STOPCONF2,R0	;
	TST	R0,R0				;
	TST_BIT_OF EP_SENCER_CK150		;
	M_BRA	EP_SENCER_CK900			;�ُ�

EP_SENCER_CK150:

;	-----------�x�����ԏ���--------
	MOV.L	#_EPCHK_DLY_TIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF EP_SENCER_CK200		;
	M_BRA	EP_SENCER_CKEND		;

;	---------- �x�����Ԓ��ُ͈���϶��Ă��Ȃ�-----------
EP_SENCER_CK200:
	DN_TIME LG=W,MEM_ADR=_EPCHK_ERR_TIM,WKREG1=R1,WKREG2=R4	;

	MOV.L	#_EPCHK_STEP,R1				;
	MOV.W	@R1,R0					;
	AND	#H'1F,R0				;MAX 16�ï��
	SHLL2	R0					;
	MOV.L	#_EP_JMP_TBL,R1				;
	ADD	R0,R1					;
	MOV.L	@R1,R0					;
	REG_JMP	WKREG=R0				;


;	---------------------------------------------------
;	---	�x�����,�L���ڰ,�ُ���Ͼ��[STEP0]	---
;	---------------------------------------------------
EP_STEP_USE_RY_DATSET_A
;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP1STR_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;�J�n�x��
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_DLY_TIM,R1					;
	MOV.W	R2,@R1							;
	M_BRA	EP_STEP_USE_RY_DATSETCOM

EP_STEP_USE_RY_DATSET_B
;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP7AB_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;�J�n�x��
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_DLY_TIM,R1					;
	MOV.W	R2,@R1							;

EP_STEP_USE_RY_DATSETCOM

;	---------��Ͼ��[�ُ�]-----------------
	MOV.L	#(_PAR_EP2FVINOF_ERTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;�Е��ڰOF(0)�m�F���Ԍ���ѱ��
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_ERR_TIM,R1					;
	MOV.W	R2,@R1							;
	STEP_NEXT MEM=_EPCHK_STEP					;
	M_BRA	EP_SENCER_CKEND						;


;	---------------------------------------------------
;	---	VF-RY�̕Ќ��ݻ�҂��C�ُ�CHK[STEP1]	---
;	---------------------------------------------------
;	��ѱ��ߑO�ɓ��͂��m�F���A���͂�"L"�Ȃ瑦�J�ڂ���,���ԓ���"L"�ɂȂ�Ȃ���Έُ�
;	----------- A:�ï��1,B:�ï��1----------
EP_STEP_USE_RY_A
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT5),WKRG1=R1,WKRG2=R4	;BIT5=1:A�Ќ��v��
	M_BRA	EP_STEP_USE_RY_COM		;


EP_STEP_USE_RY_B
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT6),WKRG1=R1,WKRG2=R4	;BIT6=A�Ќ��v��
EP_STEP_USE_RY_COM

	FAR_JSR	#_VFRY_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT14(ON)

	TST	R0,R0								;
	TST_BIT_ON EP_STEP_USE_RY_COM_150					;

;	------- OFF���� ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_USE_RY_COM_150								;
	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_USE_RY_COM_190					;

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT2),WKRG1=R1,WKRG2=R4	;̨����ޯ����s
	M_BRA	EP_SENCER_CK900							;

EP_STEP_USE_RY_COM_190								;
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	�x�����,�����ON,�ُ���Ͼ��[STEP2]	---
;	---------------------------------------------------
EP_STEP_VALVON_DATSET
;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP3BRKON_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;��ڰ�ON�o�͒x��
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;

;	---------��Ͼ��[�ُ�]-----------------
	MOV.L	#(_PAR_EP4EPINOF_ERTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;�����ON���Ԍ���ѱ�Ď���
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_ERR_TIM,R1					;
	MOV.W	R2,@R1							;
	STEP_NEXT MEM=_EPCHK_STEP					;
	M_BRA	EP_SENCER_CKEND						;


;	---------------------------------------------------
;	---	�����ON�̱ݻEP�҂��C�ُ�CHK[STEP3]	---
;	---------------------------------------------------
;	��ѱ��ߌ�ɓ��͂��m�F���A���͂�"L"�Ȃ�J��,"H"�Ȃ�ُ�
;	----------- A:�ï��,B:�ï��----------
EP_STEP_VALVON_COM
	MOV.B	#(BIT0),R0			;��ڰ�����
	MOV.L	#_EPCHK_FORCE_VONCMD,R1		;
	MOV.W	R0,@R1				;


	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_VALV_COM_190					;

;	��ѱ��ߌ������
	XOR	R0,R0				;
	MOV.L	#_EPCHK_FORCE_VONCMD,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_EPSEN_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT15(ON)

	TST	R0,R0								;
	TST_BIT_ON EP_STEP_VALV_COM_150					;

;	------- OFF���� ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_VALV_COM_150								;

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT3),WKRG1=R1,WKRG2=R4	;EP�ݻ���s
	M_BRA	EP_SENCER_CK900							;

EP_STEP_VALV_COM_190
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	EP�m�F����[STEP4]			---
;	---------------------------------------------------
EP_STEP_EPSENSIG_A:
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT7),WKRG1=R1,WKRG2=R4	;
	XOR	R0,R0								;
	MOV.L	#_EPCHK_RETRY_CNT,R1						;STEP5�̑O�ɍs��
	MOV.W	R0,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_EPSENSIG_B:
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT8),WKRG1=R1,WKRG2=R4	;
	XOR	R0,R0								;STEP5�̑O�ɍs��
	MOV.L	#_EPCHK_RETRY_CNT,R1						;
	MOV.W	R0,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;


;	---------------------------------------------------
;	---	EPؾ��ON�x��,��ѱ�Đݒ�[STEP5]		---
;	---------------------------------------------------
EP_STEP_RESET_DATSET1:
	MOV.L	#_EPCHK_RETRY_CNT,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON EP_STEP_RESET_100		;��ײ

;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP5RSTON_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ؾ��ON�x������
	MOV.W	@R1,R2								;(ؾ��OFF����)
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;
	M_BRA	EP_STEP_RESET_DATSET_COM					;

EP_STEP_RESET_100:
;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP6RSTOF_INTTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ؾ��ON�x������(������َ���)
	MOV.W	@R1,R2								;(ؾ��OFF����)
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;

EP_STEP_RESET_DATSET_COM:

;	---------��Ͼ��[�ُ�]-----------------
	MOV.L	#(_PAR_EP6RSTON_JGTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ؾ��ON���Ԍ���ѱ�Ď���
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	R2,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;




;	---------------------------------------------------
;	---	ؾ��ON�̱ݻEP�҂��C�ُ�CHK[STEP6]	---
;	---------------------------------------------------
;	��ѱ��ߌ�ɓ��͂��m�F���A���͂�"�g"�Ȃ�J��,"�k"�Ȃ�ُ�@��ײ
;	----------- A:�ï��,B:�ï��----------
EP_STEP_RESETON_COM

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT9),WKRG1=R1,WKRG2=R4	;ؾ�ĺ����

	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_RESET_COM_190					;

;	------- ��ѱ��ߌ������--------
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9),WKRG1=R1,WKRG2=R4	;ؾ��OFF


	FAR_JSR	#_EPSEN_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT15(ON)

	TST	R0,R0								;
	TST_BIT_OF EP_STEP_RESET_COM_150					;

;	------- ON���� ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_RESET_COM_150								;
	MOV.L	#(_PAR_EP6RST_RETRY-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ؾ����ײ��
	MOV.W	@R1,R2								;0:��ײ���Ȃ�
	MOV.L	#_EPCHK_RETRY_CNT,R5						;
	MOV.W	@R5,R0								;
	CMP/HS	R2,R0								;0(SV)=<0(PV)
	BT	EP_STEP_RESET_COM_170						;��ײ����
	ADD	#1,R0								;
	MOV.W	R0,@R5								;

	MOV.L	#_EPCHK_STEP,R1				;1�O�����蒼��
	MOV.W	@R1,R0					;
	ADD	#-1,R0					;
	MOV.W	R0,@R1					;
	M_BRA	EP_SENCER_CKEND							;


EP_STEP_RESET_COM_170								;�I������
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT4),WKRG1=R1,WKRG2=R4	;EP�ݻؾ�Ď��s
	M_BRA	EP_SENCER_CK900							;

EP_STEP_RESET_COM_190
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	CPUA�I��,CPUB�J�n�x��+��ѱ�Đݒ�[STEP7]	---
;	---------------------------------------------------
EP_STEP_ENDSIG_A
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9|BIT5),WKRG1=R1,WKRG2=R4	;ؾ��OFF
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT10),WKRG1=R1,WKRG2=R4		;A����
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT1),WKRG1=R1,WKRG2=R4		;B�J�n
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND								;

EP_STEP_ENDSIG_B
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9|BIT6),WKRG1=R1,WKRG2=R4	;ؾ��OFF
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT11),WKRG1=R1,WKRG2=R4	;

;	---------- �����x�����-------------
	MOV.L	#(_PAR_EP7END_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;�I���x��
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;
;;;;2015-10-26��Ё@�����͂��Ȃ���	M_BRA	EP_STEP_RESET_DATSET_COM					;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;


EP_STEP_ENDSIG
	M_BRA	EP_SENCER_CK800							;


EP_STEP_XX:

;	-----------����I������--------
EP_SENCER_CK800:

	MOV.W	#BIT7,R0			;
	MOV.L	#_EPCHK_FLG,R1			;
	MOV.W	R0,@R1				;

	MOV.W	#BIT15,R0
	MOV.L	#_EPCHK_STS,R1			;BIT15:���튮��
	MOV.W	R0,@R1				;

	M_BRA	EP_SENCER_CK950			;


;	-----------�ُ�I������--------
EP_SENCER_CK900:

	MOV.W	#H'239E,R4		;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			;

	XOR	R0,R0					;
	MOV.L	#_EPCHK_FLG,R1				;
	MOV.W	R0,@R1					;

	MOV.L	#_EPCHK_STS,R1				;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT4|BIT3|BIT2),R4			;�ُ�v���ȊO��ر
	AND	R4,R0					;

	MOV.W	#BIT14,R4				;BIT14�ُ�I�����
	OR	R4,R0					;
	MOV.W	R0,@R1					;

;	-----------�I�����ʏ���--------
EP_SENCER_CK950:
	XOR	R0,R0					;
	MOV.L	#_EPCHK_COM,R1				;
	MOV.W	R0,@R1					;
	MOV.L	#_EPCHK_FORCE_VONCMD,R1			;���������ON:OFF
	MOV.W	R0,@R1					;


EP_SENCER_CKEND
	MOV.L	#_EPCHK_STS,R1			;
	MOV.W	@R1,R2				;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB239,R1	;239
	MOV.W	R2,@R1				;

EP_SENCER_CKEXT
	SUB_END
	M_RTS


_EP_SENCHK_STOPCONF1:
_EP_SENCHK_STOPCONF2:
	SUB_START

	MOV.L	#_emg_err_flg,R1	;//�ُ�ׯ�
	MOV.W	@R1,R0			;
	MOV.L	#_exq_err_flg,R1	;//�ُ�ׯ�
	MOV.W	@R1,R2			;
	OR	R2,R0			;

	SUB_END
	M_RTS


;	ANS R0=0(OFF) R0=BIT14(ON)
_VFRY_IN_CHK:
	SUB_START
	MOV.W	#BIT14,R4			;
	MOV.L	#_CB_SEQ_CB_COM349,R1		;
	MOV.W	@R1,R0				;
	AND	R4,R0				;0orBIT14

	SUB_END
	M_RTS


_EPSEN_IN_CHK
	SUB_START
	MOV.W	#BIT15,R4			;
	MOV.L	#_CB_SEQ_CB_COM349,R1		;
	MOV.W	@R1,R0				;
	AND	R4,R0				;0orBIT15

	SUB_END
	M_RTS


_EPSEN_CLR
	SUB_START

	MOV.W	#BIT15,R4
	MOV.L	#_EPCHK_STS,R1			;
	MOV.W	@R1,R0
	AND	R4,R0
	MOV.W	R0,@R1				;
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB239,R1	;239
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS
