;	***************************************************
;	***						***
;	***						***
;	***						***
;	***	行程前に加速・減速処理			***
;	***	行程後に加速・減速処理			***
;	***	各行程での指定				***
;	***	2016-04-18				***
;	***						***
;	***						***
;	***						***
;	***************************************************
	.IMPORT		_PAR_ACCDN_MATH		;5 2015-11-18 加減速　減速優先[CE2]
;	*******************************************
;	***					***
;	***	バックグランドでCALL		***
;	***	条件作成			***
;	***					***
;	*******************************************
_ACC_MATHED_SEL_MAIN
	SUB_START
	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_SEL_MN_100		;

;	-----	低速優先	-----
	FAR_JSR	#_ACCLW_DATA_MAIN,R0		;[1だ]
	M_BRA	ACC_MATHED_SEL_MN_END		;


ACC_MATHED_SEL_MN_100				;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_SEL_MN_END		;

;	-----	各段指定	-----
	FAR_JSR	#_ACCST_DATA_MAIN,R0		;[2だ]


ACC_MATHED_SEL_MN_END				;


	SUB_END
	M_RTS



;	***************************************************
;	***						***
;	***	起動時CALL(運転釦ON,タイマ後,1サイクル)	***
;	***						***
;	***************************************************
_API_ACC_MATHED_COM_DRV_START1
	SUB_START

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_COM_DRVST1_100	;

;	-----	低速優先	-----
	FAR_JSR	#_API_ACCLW_DRV_START1,R0	;

	M_BRA	ACC_MATHED_COM_DRVST1_END	;


ACC_MATHED_COM_DRVST1_100			;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_COM_DRVST1_END	;

;	-----	各段指定	-----
	FAR_JSR	#_API_ACCST_DRV_START1,R0	;

ACC_MATHED_COM_DRVST1_END:	;

	SUB_END
	M_RTS





;	*******************************************
;	***					***
;	***	位置決め中断時CALL		***
;	***	位置決め停止タイマ時CALL	***
;	***	異常時CALL			***
;	***					***
;	*******************************************
;//BIT0:起動[API]
;//BIT6:[減速開始]
;//BIT7:演算完了[停止行程まで演算不要：もう低速設定がない]:予備
;//

_API_ACC_MATHED_COM_DRV_STOP
	SUB_START
;	(ここは判断がなくてもいいでしょう)

;	-----	低速優先	-----
;	---	フラグクリア	---
	FAR_JSR	#_API_ACCLW_DRV_STOP,R0

;	-----	各段指定	-----
;	---	フラグクリア	---
	FAR_JSR	#_API_ACCST_DRV_STOP,R0


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	1msecでCALL	メイン		***
;	***					***
;	*******************************************
;	[Input R2]
_ACC_MATHED_SEL_CTRL
	SUB_START

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_CTLSEL_100		;

;	-----	低速優先	-----
	FAR_JSR	#_ACCLW_CTRL_CALC,R0		;2015-11-17 減速選択

	M_BRA	ACC_MATHED_CTLSEL_END		;


ACC_MATHED_CTLSEL_100				;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_CTLSEL_END		;

;	-----	各段指定	-----
	FAR_JSR	#_ACCST_CTRL_CALC,R0		;[2だ]

ACC_MATHED_CTLSEL_END				;


	SUB_END
	M_RTS













;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	レジスタはR0以外破壊しないこと
;	R0=0/R0=1(前減速,前加速)-速度チェック１不要
_ACCSEL_CHGSPD_LIMIT_INFO_LOAD:
	SUB_START

	PUSH_REG1 R1

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACCCHGSPD_LMT_INF_LD_100	;

;	-----	低速優先	-----
	XOR	R0,R0
	M_BRA	ACCCHGSPD_LMT_INF_LD_END	;


ACCCHGSPD_LMT_INF_LD_100:
	CMP/EQ	#2,R0				;
	BF	ACCCHGSPD_LMT_INF_LD_200

;	-----	各段指定	-----
	FAR_JSR	#_ACCST_CHGSPD_LIMIT_INFO_LOAD,R0	;
	M_BRA	ACCCHGSPD_LMT_INF_LD_END		;

ACCCHGSPD_LMT_INF_LD_200				;
	XOR	R0,R0
ACCCHGSPD_LMT_INF_LD_END				;

	POP_REG1 R1

	SUB_END
	M_RTS
	
