;	*******************************************
;	***					***
;	***	dpram r/w			***
;	***	cop2-program			***
;	***					***
;	*******************************************
;	cpua=>cop2
;	cpua<=cop2
;
;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
	.MACRO DAT_MOV1 SRC,L1,DST,L2,REG1,REG2,DTREG
	MOV.L	#\SRC,\REG1		;
	MOV.L	#\DST,\REG2		;
	MOV.\L1	@\REG1,\DTREG		;
	MOV.\L2	\DTREG,@\REG2		;
	.ENDM

	.MACRO DAT_MOV1_LOP SRC,L1,DST,L2,REG1,REG2,DTREG,LOPREG,CNT,ADRADD
	MOV.L	#\SRC,\REG1		;
	MOV.L	#\DST,\REG2		;
	MOV.L	#\CNT,\LOPREG

JMPLOP\@:
	TST \LOPREG,\LOPREG		;
	TST_BIT_OF JMP01\@		;
	MOV.\L1	@\REG1+,\DTREG		;
	MOV.\L2	\DTREG,@\REG2		;
	ADD	#-1,\LOPREG		;
	ADD	#\ADRADD,\REG2		;
	M_BRA JMPLOP\@
JMP01\@:
	.ENDM

_cop2_BAKdata_move:
	SUB_START
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	ssa_dtmk.src call
_cop2_PONdata_move:
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
_cop2_SYSdata_move:
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	ssa_dtmk.src call
_cop2_SV1data_move:
	SUB_START
	FAR_JSR	#_cop2_TUNSV1data_move,R0
	FAR_JSR	#_cop2_TUNSV2data_move,R0
	FAR_JSR	#_cop2_SV1data_move1,R0
	FAR_JSR	#_cop2_SV1data_move2,R0
	FAR_JSR	#_cop2_SV1data_move3,R0
	FAR_JSR	#_cop2_SV2data_move,R0
	SUB_END
	M_RTS

;
;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
_cop2_TUNSV1data_move:
	SUB_START
	SUB_END
	M_RTS

;
;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
_cop2_TUNSV2data_move:
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	-----------------モーションデータ-------------
_cop2_SV1data_move1:
	SUB_START

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	----------------通常データ---------------------
_cop2_SV1data_move2:
	SUB_START
	SUB_END
	M_RTS

;
;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
_cop2_SV1data_move3:
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	----------------実測データをcop2に教える---------------------
_cop2_SV2data_move:
	SUB_START
	SUB_END
	M_RTS









;	***************************************************
;	***						***
;	***		実測				***
;	***		COP-->SIT->DISP			***
;	***		(NEW)				***
;	***************************************************
_cop2_PV1data_move:
	SUB_START

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***		実測				***
;	***		VER COP2->CPUA-CPUB		***
;	***		(NEW)				***
;	***************************************************
;	ssa_K.src call
;	CPUA:COP2.DPRAM-->CPUB.DPRAM
;
_cop2_VERdata_move:
	SUB_START
	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***		seq				***
;	***						***
;	***************************************************
;	ssa_dtmk.src call
_cop2_SEQCMD1data_move:
	SUB_START

	DAT_MOV1_LOP SRC=_COP2_SEQ_DP_340,L1=W,DST=_SEQ_DP_TOP+340*2,L2=W,REG1=R1,REG2=R2,DTREG=R0,LOPREG=R4,CNT=30,ADRADD=2;//30word

	SUB_END
	M_RTS

_cop2_SEQSTS1data_move:
	SUB_START
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***		dio情報				***
;	***						***
;	***************************************************
	.EXPORT	_dio_data_move1
_dio_data_move1:
	SUB_START
	DAT_MOV1 SRC=_COP2_di1_cb_ctl1,L1=W,DST=_di1_cb_ctl1,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	DAT_MOV1 SRC=_COP2_di2_cb_ctl2,L1=W,DST=_di2_cb_ctl2,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	DAT_MOV1 SRC=_COP2_di3_cb_inp1,L1=W,DST=_di3_cb_inp1,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	DAT_MOV1 SRC=_COP2_di4_cb_inp2,L1=W,DST=_di4_cb_inp2,L2=W,REG1=R1,REG2=R2,DTREG=R0;//

	DAT_MOV1 SRC=_COP2_INT_SFY_INP_DAT,L1=W,DST=_INT_SFY_INP_DAT,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	DAT_MOV1 SRC=_COP2_INT_STP_INP_DAT,L1=W,DST=_INT_STP_INP_DAT,L2=W,REG1=R1,REG2=R2,DTREG=R0;//


	DAT_MOV1 SRC=_COP2_PVX_SH4_SFTY_IN,L1=W,DST=_PVX_SH4_SFTY_IN,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	DAT_MOV1 SRC=_COP2_ENC360_INDT,L1=W,DST=_ENC360_INDT,L2=W,REG1=R1,REG2=R2,DTREG=R0;//
	
	SUB_END
	M_RTS
