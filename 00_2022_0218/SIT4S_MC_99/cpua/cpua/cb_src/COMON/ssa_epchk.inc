;	***********************************
;	***				***
;	***	EPｾﾝｻﾁｪｯｸ		***
;	***				***
;	***********************************
;	電源投入時
;	位置づけはｾﾙﾌﾁｪｯｸだが,独立した機能
;	ANTI-ONしてから

	.EXPORT		_EPSEN_CLR			

	.GLOBAL		_PAR_EPCHK_SEL		;5 0:EPｾﾝｻﾁｪｯｸしない 1:ﾁｪｯｸする
	.GLOBAL		_PAR_EP1STR_DLYTM	;6 開始遅延時間 ms
	.GLOBAL		_PAR_EP2FVINOF_ERTM	;7 片方ﾘﾚｰOF(0)確認時間兼ﾀｲﾑｱｳﾄ
	.GLOBAL		_PAR_EP3BRKON_DLYTM	;8 ﾌﾞﾚｰｷON出力遅延
	.GLOBAL		_PAR_EP4EPINOF_ERTM	;9 EPｾﾝｻoff確認時間兼ﾀｲﾑｱｳﾄ
	.GLOBAL		_PAR_EP5RSTON_DLYTM	;10 EPｾﾝｻﾘｾｯﾄON遅延時間
	.GLOBAL		_PAR_EP6RSTON_JGTM	;1 ﾘｾｯﾄON時間兼判定時間
	.GLOBAL		_PAR_EP6RSTOF_INTTM	;2 OFFｲﾝﾀ-ﾊﾞﾙ時間
	.GLOBAL		_PAR_EP6RST_RETRY	;3 ﾘｾｯﾄﾘﾄﾗｲ回数
	.GLOBAL		_PAR_EP7AB_DLYTM	;4 CPUA-->CPUBﾃｽﾄ遅延時間
	.GLOBAL		_PAR_EP7END_DLYTM	;5 CPUB-->終了遅延時間


	.MACRO	STEP_NEXT MEM
	MOV.L	#\MEM,R1	;
	MOV.W	@R1,R0		;
	ADD	#1,R0		;
	MOV.W	R0,@R1		;
	.ENDM

	.ALIGN	4				;
_EP_JMP_TBL

	.DATA.L		EP_STEP_USE_RY_DATSET_A	;0
	.DATA.L		EP_STEP_USE_RY_A	;1 片効有効RY-ON,片効きｾﾝｻ確認
	.DATA.L		EP_STEP_VALVON_DATSET	;2
	.DATA.L		EP_STEP_VALVON_COM	;3 ﾊﾞﾙﾌﾞON,EPｾﾝｻ確認
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

;	--------- 開始処理-----------
EP_SENCER_CK020:

	MOV.L	#(_PAR_EPCHK_SEL-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;
	CMP/EQ	#1,R0							;
	BT	EP_SENCER_CK030						;
	M_BRA	EP_SENCER_CK800						;正常終了


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

;	---------- 処理中---------------
EP_SENCER_CK100:

	DN_TIME LG=W,MEM_ADR=_EPCHK_DLY_TIM,WKREG1=R1,WKREG2=R4	;

;	-------- 中断条件--------------------
	FAR_JSR	#_EP_SENCHK_STOPCONF2,R0	;
	TST	R0,R0				;
	TST_BIT_OF EP_SENCER_CK150		;
	M_BRA	EP_SENCER_CK900			;異常

EP_SENCER_CK150:

;	-----------遅延時間処理--------
	MOV.L	#_EPCHK_DLY_TIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF EP_SENCER_CK200		;
	M_BRA	EP_SENCER_CKEND		;

;	---------- 遅延時間中は異常ﾀｲﾏｶｳﾝﾄしない-----------
EP_SENCER_CK200:
	DN_TIME LG=W,MEM_ADR=_EPCHK_ERR_TIM,WKREG1=R1,WKREG2=R4	;

	MOV.L	#_EPCHK_STEP,R1				;
	MOV.W	@R1,R0					;
	AND	#H'1F,R0				;MAX 16ｽﾃｯﾌﾟ
	SHLL2	R0					;
	MOV.L	#_EP_JMP_TBL,R1				;
	ADD	R0,R1					;
	MOV.L	@R1,R0					;
	REG_JMP	WKREG=R0				;


;	---------------------------------------------------
;	---	遅延ﾀｲﾏ,有効ﾘﾚｰ,異常ﾀｲﾏｾｯﾄ[STEP0]	---
;	---------------------------------------------------
EP_STEP_USE_RY_DATSET_A
;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP1STR_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;開始遅延
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_DLY_TIM,R1					;
	MOV.W	R2,@R1							;
	M_BRA	EP_STEP_USE_RY_DATSETCOM

EP_STEP_USE_RY_DATSET_B
;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP7AB_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;開始遅延
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_DLY_TIM,R1					;
	MOV.W	R2,@R1							;

EP_STEP_USE_RY_DATSETCOM

;	---------ﾀｲﾏｾｯﾄ[異常]-----------------
	MOV.L	#(_PAR_EP2FVINOF_ERTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;片方ﾘﾚｰOF(0)確認時間兼ﾀｲﾑｱｳﾄ
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_ERR_TIM,R1					;
	MOV.W	R2,@R1							;
	STEP_NEXT MEM=_EPCHK_STEP					;
	M_BRA	EP_SENCER_CKEND						;


;	---------------------------------------------------
;	---	VF-RYの片効ｱﾝｻ待ち，異常CHK[STEP1]	---
;	---------------------------------------------------
;	ﾀｲﾑｱｯﾌﾟ前に入力を確認し、入力が"L"なら即遷移する,時間内に"L"にならなければ異常
;	----------- A:ｽﾃｯﾌﾟ1,B:ｽﾃｯﾌﾟ1----------
EP_STEP_USE_RY_A
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT5),WKRG1=R1,WKRG2=R4	;BIT5=1:A片効要求
	M_BRA	EP_STEP_USE_RY_COM		;


EP_STEP_USE_RY_B
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT6),WKRG1=R1,WKRG2=R4	;BIT6=A片効要求
EP_STEP_USE_RY_COM

	FAR_JSR	#_VFRY_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT14(ON)

	TST	R0,R0								;
	TST_BIT_ON EP_STEP_USE_RY_COM_150					;

;	------- OFF発見 ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_USE_RY_COM_150								;
	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_USE_RY_COM_190					;

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT2),WKRG1=R1,WKRG2=R4	;ﾌｨｰﾄﾞﾊﾞｯｸ失敗
	M_BRA	EP_SENCER_CK900							;

EP_STEP_USE_RY_COM_190								;
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	遅延ﾀｲﾏ,ﾊﾞﾙﾌﾞON,異常ﾀｲﾏｾｯﾄ[STEP2]	---
;	---------------------------------------------------
EP_STEP_VALVON_DATSET
;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP3BRKON_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ﾌﾞﾚｰｷON出力遅延
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;

;	---------ﾀｲﾏｾｯﾄ[異常]-----------------
	MOV.L	#(_PAR_EP4EPINOF_ERTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;ﾊﾞﾙﾌﾞON時間兼ﾀｲﾑｱｳﾄ時間
	MOV.W	@R1,R2							;
	MOV.L	#_EPCHK_ERR_TIM,R1					;
	MOV.W	R2,@R1							;
	STEP_NEXT MEM=_EPCHK_STEP					;
	M_BRA	EP_SENCER_CKEND						;


;	---------------------------------------------------
;	---	ﾊﾞﾙﾌﾞONのｱﾝｻEP待ち，異常CHK[STEP3]	---
;	---------------------------------------------------
;	ﾀｲﾑｱｯﾌﾟ後に入力を確認し、入力が"L"なら遷移,"H"なら異常
;	----------- A:ｽﾃｯﾌﾟ,B:ｽﾃｯﾌﾟ----------
EP_STEP_VALVON_COM
	MOV.B	#(BIT0),R0			;ﾌﾞﾚｰｷ解除
	MOV.L	#_EPCHK_FORCE_VONCMD,R1		;
	MOV.W	R0,@R1				;


	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_VALV_COM_190					;

;	ﾀｲﾑｱｯﾌﾟ後にﾁｪｯｸ
	XOR	R0,R0				;
	MOV.L	#_EPCHK_FORCE_VONCMD,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_EPSEN_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT15(ON)

	TST	R0,R0								;
	TST_BIT_ON EP_STEP_VALV_COM_150					;

;	------- OFF発見 ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_VALV_COM_150								;

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT3),WKRG1=R1,WKRG2=R4	;EPｾﾝｻ失敗
	M_BRA	EP_SENCER_CK900							;

EP_STEP_VALV_COM_190
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	EP確認完了[STEP4]			---
;	---------------------------------------------------
EP_STEP_EPSENSIG_A:
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT7),WKRG1=R1,WKRG2=R4	;
	XOR	R0,R0								;
	MOV.L	#_EPCHK_RETRY_CNT,R1						;STEP5の前に行う
	MOV.W	R0,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_EPSENSIG_B:
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT8),WKRG1=R1,WKRG2=R4	;
	XOR	R0,R0								;STEP5の前に行う
	MOV.L	#_EPCHK_RETRY_CNT,R1						;
	MOV.W	R0,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;


;	---------------------------------------------------
;	---	EPﾘｾｯﾄON遅延,ﾀｲﾑｱｳﾄ設定[STEP5]		---
;	---------------------------------------------------
EP_STEP_RESET_DATSET1:
	MOV.L	#_EPCHK_RETRY_CNT,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON EP_STEP_RESET_100		;ﾘﾄﾗｲ

;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP5RSTON_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ﾘｾｯﾄON遅延時間
	MOV.W	@R1,R2								;(ﾘｾｯﾄOFF時間)
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;
	M_BRA	EP_STEP_RESET_DATSET_COM					;

EP_STEP_RESET_100:
;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP6RSTOF_INTTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ﾘｾｯﾄON遅延時間(ｲﾝﾀｰﾊﾞﾙ時間)
	MOV.W	@R1,R2								;(ﾘｾｯﾄOFF時間)
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;

EP_STEP_RESET_DATSET_COM:

;	---------ﾀｲﾏｾｯﾄ[異常]-----------------
	MOV.L	#(_PAR_EP6RSTON_JGTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ﾘｾｯﾄON時間兼ﾀｲﾑｱｳﾄ時間
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	R2,@R1								;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;




;	---------------------------------------------------
;	---	ﾘｾｯﾄONのｱﾝｻEP待ち，異常CHK[STEP6]	---
;	---------------------------------------------------
;	ﾀｲﾑｱｯﾌﾟ後に入力を確認し、入力が"Ｈ"なら遷移,"Ｌ"なら異常　ﾘﾄﾗｲ
;	----------- A:ｽﾃｯﾌﾟ,B:ｽﾃｯﾌﾟ----------
EP_STEP_RESETON_COM

	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT9),WKRG1=R1,WKRG2=R4	;ﾘｾｯﾄｺﾏﾝﾄﾞ

	MOV.L	#_EPCHK_ERR_TIM,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_ON EP_STEP_RESET_COM_190					;

;	------- ﾀｲﾑｱｯﾌﾟ後にﾁｪｯｸ--------
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9),WKRG1=R1,WKRG2=R4	;ﾘｾｯﾄOFF


	FAR_JSR	#_EPSEN_IN_CHK,R0						;ANS R0=0(OFF) R0=BIT15(ON)

	TST	R0,R0								;
	TST_BIT_OF EP_STEP_RESET_COM_150					;

;	------- ON発見 ------
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;

EP_STEP_RESET_COM_150								;
	MOV.L	#(_PAR_EP6RST_RETRY-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;ﾘｾｯﾄﾘﾄﾗｲ回数
	MOV.W	@R1,R2								;0:ﾘﾄﾗｲしない
	MOV.L	#_EPCHK_RETRY_CNT,R5						;
	MOV.W	@R5,R0								;
	CMP/HS	R2,R0								;0(SV)=<0(PV)
	BT	EP_STEP_RESET_COM_170						;ﾘﾄﾗｲｵｰﾊﾞ
	ADD	#1,R0								;
	MOV.W	R0,@R5								;

	MOV.L	#_EPCHK_STEP,R1				;1個前からやり直す
	MOV.W	@R1,R0					;
	ADD	#-1,R0					;
	MOV.W	R0,@R1					;
	M_BRA	EP_SENCER_CKEND							;


EP_STEP_RESET_COM_170								;終了処理
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT4),WKRG1=R1,WKRG2=R4	;EPｾﾝｻﾘｾｯﾄ失敗
	M_BRA	EP_SENCER_CK900							;

EP_STEP_RESET_COM_190
	M_BRA	EP_SENCER_CKEND							;



;	---------------------------------------------------
;	---	CPUA終了,CPUB開始遅延+ﾀｲﾑｱｳﾄ設定[STEP7]	---
;	---------------------------------------------------
EP_STEP_ENDSIG_A
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9|BIT5),WKRG1=R1,WKRG2=R4	;ﾘｾｯﾄOFF
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT10),WKRG1=R1,WKRG2=R4		;A完了
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT1),WKRG1=R1,WKRG2=R4		;B開始
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND								;

EP_STEP_ENDSIG_B
	MEM1_BIT0_F_ADCLR MEM=_EPCHK_STS,LG=W,BIT=~(BIT9|BIT6),WKRG1=R1,WKRG2=R4	;ﾘｾｯﾄOFF
	MEM1_BIT0_F_ORSET MEM=_EPCHK_STS,LG=W,BIT=(BIT11),WKRG1=R1,WKRG2=R4	;

;	---------- 処理遅延ｾｯﾄ-------------
	MOV.L	#(_PAR_EP7END_DLYTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;終了遅延
	MOV.W	@R1,R2								;
	MOV.L	#_EPCHK_DLY_TIM,R1						;
	MOV.W	R2,@R1								;
;;;;2015-10-26ｺﾞﾐ　悪さはしないが	M_BRA	EP_STEP_RESET_DATSET_COM					;
	STEP_NEXT MEM=_EPCHK_STEP						;
	M_BRA	EP_SENCER_CKEND							;


EP_STEP_ENDSIG
	M_BRA	EP_SENCER_CK800							;


EP_STEP_XX:

;	-----------正常終了処理--------
EP_SENCER_CK800:

	MOV.W	#BIT7,R0			;
	MOV.L	#_EPCHK_FLG,R1			;
	MOV.W	R0,@R1				;

	MOV.W	#BIT15,R0
	MOV.L	#_EPCHK_STS,R1			;BIT15:正常完了
	MOV.W	R0,@R1				;

	M_BRA	EP_SENCER_CK950			;


;	-----------異常終了処理--------
EP_SENCER_CK900:

	MOV.W	#H'239E,R4		;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			;

	XOR	R0,R0					;
	MOV.L	#_EPCHK_FLG,R1				;
	MOV.W	R0,@R1					;

	MOV.L	#_EPCHK_STS,R1				;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT4|BIT3|BIT2),R4			;異常要因以外をｸﾘｱ
	AND	R4,R0					;

	MOV.W	#BIT14,R4				;BIT14異常終了ｾｯﾄ
	OR	R4,R0					;
	MOV.W	R0,@R1					;

;	-----------終了共通処理--------
EP_SENCER_CK950:
	XOR	R0,R0					;
	MOV.L	#_EPCHK_COM,R1				;
	MOV.W	R0,@R1					;
	MOV.L	#_EPCHK_FORCE_VONCMD,R1			;強制ﾊﾞﾙﾌﾞON:OFF
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

	MOV.L	#_emg_err_flg,R1	;//異常ﾗｯﾁ
	MOV.W	@R1,R0			;
	MOV.L	#_exq_err_flg,R1	;//異常ﾗｯﾁ
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

