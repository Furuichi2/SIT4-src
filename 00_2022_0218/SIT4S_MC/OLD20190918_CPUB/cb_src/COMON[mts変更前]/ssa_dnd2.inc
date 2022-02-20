;	***********************************
;	***				***
;	***	段取寸動コントロール	***
;	***				***
;	***********************************
;	***********************************
;	***				***
;	***	ﾓｰｼｮﾝ全工程		***
;	***				***
;	***********************************
;	======== 停止待ち(速度変更)	0000,0000	====
;	======== ﾀｲﾏ計測 		BIT0		====
;	======== 再起動/終了		BIT1		====
;	======== BIT6;終了
_DND_ROT_STEP_CTRL:
	SUB_START

	MOV.L	#_CPOS_DND_STOP_SW,R1		;
	MOV.W	@R1,R0				;
	TST	#(BIT1+BIT0),R0			;
	TST_BIT_ON DND_ROTSTEPCTL_050		;
	M_BRA	DND_ROTSTEPCTL_EXT		;

DND_ROTSTEPCTL_050:
	MOV.L	#_INT_DND_STEP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT5,R0			;
	TST_BIT_ON DND_ROTSTEPCTL_080		;終了

	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0	;
	FAR_JSR	#_LOD_POS_STS_REG,R1		;
	TST	#BIT2,R0			;停止?
	TST_BIT_ON DND_ROTSTEPCTL_200		;YES 停止中 1:停止 0:払出中
DND_ROTSTEPCTL_080:
	M_BRA	DND_ROTSTEPCTL_900		;

;	===========================
;	===	払出停止	===
;	===	回転時		===
;	===========================
DND_ROTSTEPCTL_200:
DND_ROTSTEPCTL_400:
;	===================================
;	===	二重回路対策		===
;	===	工程完了		===
;	===================================
	FAR_JSR	#_CMPAB_STEP_END_PROC,R0	;
	TST	R0,R0				;
	TST_BIT_ON DND_ROTSTEPCTL_420		;
	M_BRA	DND_ROTSTEPCTL_900		;

DND_ROTSTEPCTL_420:				;
	FAR_JSR	#_CMPSTP_STEP_END_CLR,R0	;//位置決め完了としたい

;	====  工程を進めて終了する =====
	MOV.L	#_DNDINC_CTRL_STEP,R5		;
	MOV.W	@R5,R3				;
	MOV.L	#_CPOS_DND_STOP_SW,R1		;
	MOV.W	@R1,R0				;
	AND	#(BIT1+BIT0),R0			;
	CMP/EQ	#(BIT1+BIT0),R0			;
	BT	DND_ROTSTEPCTL_440		;
	MOV	#1,R3				;
	M_BRA	DND_ROTSTEPCTL_500		;
DND_ROTSTEPCTL_440:				;
	ADD	#1,R3				;
	MOV.W	#2,R2				;
	CMP/HI	R2,R3				;
	BF	DND_ROTSTEPCTL_500		;
	MOV.W	#1,R3				;
DND_ROTSTEPCTL_500:				;
	MOV.W	R3,@R5				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_DND_STEP_FLG,LG=W,BIT=BIT5,WKREG=R1	;BIT5=1 END

;	--------- 2014-08-05----------
	FAR_JSR	#_API_BREAK_VALV_FLG_OF,R0

DND_ROTSTEPCTL_900:
	NOP
DND_ROTSTEPCTL_EXT:
	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	初起動時のエリア作成	***
;	***				***
;	***********************************
_DND_AREA_HIS		.EQU	20		;2.0DIG
_DNDINC_STEP_MAKE:
	SUB_START
	MOV.L	#_DNDINC_CTRL_STEP,R5		;
	MOV.W	@R5,R3				;
	TST	R3,R3				;
	TST_BIT_OF DNDINC_STEP_MK100		;再計算

	MOV.L	#_CPOS_DND_STOP_SW,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CPOS_DND_STOP_SWOLD,R1	;
	MOV.W	@R1,R2
	MOV.W	R0,@R1				;
	XOR	R0,R2				;
	TST	R2,R2				;
	TST_BIT_ON DNDINC_STEP_MK100		;SW変更有り　再計算

	MOV.L	#_POS_DRV_DIRECT,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CPOS_DND_STOP_DIRECTOLD,R1	;
	MOV.W	@R1,R2				;
	MOV.W	R0,@R1				;
	XOR	R0,R2				;
	TST	R2,R2				;
	TST_BIT_ON DNDINC_STEP_MK100		;DIRD変更有り　再計算
	M_BRA	DNDINC_STEP_MK150		
	
;;20060919	M_BRA	DNDINC_STEP_MK300		;


;	-------- 開始計算--------
DNDINC_STEP_MK100:
	MOV.L	#_CPOS_DND_STOP_SW,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CPOS_DND_STOP_SWOLD,R1	;
	MOV.W	R0,@R1				;

	MOV.L	#_POS_DRV_DIRECT,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_CPOS_DND_STOP_DIRECTOLD,R1	;
	MOV.W	R2,@R1				;

	AND	#(BIT1+BIT0),R0			;
	CMP/EQ	#(BIT1+BIT0),R0			;
	BT	DNDINC_STEP_MK150		;

	MOV.L	#_DNDINC_CTRL_STEP,R5		;
	MOV.W	#1,R3				;STEP=1
	MOV.W	R3,@R5				;
	M_BRA	DNDINC_STEP_MK300		;

DNDINC_STEP_MK150:
	MOV.L	#_POS_DRV_DIRECT,R1		;
	MOV.W	@R1,R0
	TST	R0,R0				;
	TST_BIT_ON DNDINC_STEP_MK180		;

	MOV.W	#_DND_AREA_HIS,R4					;
	MOV.L	#_CPOS_DND_DIGTOP+0*2,R1				;
	MOV.W	@R1,R2							;
	DIG_REGA_SUB_REGB_ANS_REGB REGA=R4,REGB=R2,WKREG=R1,LATE=3600	;dig-2.0

	MOV.L	#_CPOS_DND_DIGTOP+1*2,R1	;
	MOV.W	@R1,R3				;
	DIG_REGA_SUB_REGB_ANS_REGB REGA=R4,REGB=R3,WKREG=R1,LATE=3600	;dig-2.0
	M_BRA	DNDINC_STEP_MK200

DNDINC_STEP_MK180:							;

	MOV.W	#_DND_AREA_HIS,R4					;
	MOV.L	#_CPOS_DND_DIGTOP+0*2,R1				;
	MOV.W	@R1,R3							;
	DIG_REGA_ADD_REGB_ANS_REGB REGA=R4,REGB=R3,WKREG=R1,LATE=3600	;
	
	MOV.L	#_CPOS_DND_DIGTOP+1*2,R1				;
	MOV.W	@R1,R2							;
	DIG_REGA_ADD_REGB_ANS_REGB REGA=R4,REGB=R2,WKREG=R1,LATE=3600	;

DNDINC_STEP_MK200:						;
	MOV.L	#_INC_ENC360,R1					;
	MOV.W	@R1,R4						;

	DIG_AREA_CHK STREG=R3,EDREG=R2,PVREG=R4,ANSREG=R0	;R0 !=0 範囲内
	TST	R0,R0						;
	TST_BIT_OF DNDINC_STEP_MK220				;
	MOV.L	#_DNDINC_CTRL_STEP,R5				;
	MOV.W	#2,R3						;STEP=2 待機点に戻ってきている
	MOV.W	R3,@R5						;
	M_BRA	DNDINC_STEP_MK300				;
DNDINC_STEP_MK220:						;
	MOV.L	#_DNDINC_CTRL_STEP,R5				;
	MOV.W	#1,R3						;STEP=1 待機点を越えている
	MOV.W	R3,@R5						;
DNDINC_STEP_MK300:
	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	工程からの目標位置作成	***
;	***				***
;	***********************************
_DNDINC_MAKE_OBJPOS:
	SUB_START

	MOV.L	#_CPOS_DND_STOP_SW,R1		;
	MOV.W	@R1,R0				;
	AND	#(BIT1+BIT0),R0			;
	CMP/EQ	#(BIT1+BIT0),R0			;
	BT	DNDINC_MAKOBJPOS_100		;

	TST	#BIT0,R0			;待機点のみ
	TST_BIT_ON DNDINC_MAKOBJPOS_120		;YES
	M_BRA	DNDINC_MAKOBJPOS_150		;途中位置

DNDINC_MAKOBJPOS_100:
	MOV.L	#_DNDINC_CTRL_STEP,R1		;
	MOV.W	@R1,R3				;
	MOV.W	#2,R2				;
	CMP/EQ	R3,R2
	BF	DNDINC_MAKOBJPOS_150		;
DNDINC_MAKOBJPOS_120:
	MOV.L	#_CPOS_DND_PLSTOP+0*4,R1	;
	MOV.L	@R1,R2				;STEP2=待機点に戻る
	M_BRA	DNDINC_MAKOBJPOS_200		;

DNDINC_MAKOBJPOS_150:
	MOV.L	#_CPOS_DND_PLSTOP+1*4,R1	;
	MOV.L	@R1,R2				;STEP1=待機点から次へ出発

DNDINC_MAKOBJPOS_200:
	MOV.L	#_POS_DRV_DIRECT,R1		;
	MOV.W	@R1,R0
	FAR_JSR	#_LNKPLS_OBJ_DAT_MAK2,R1	;


	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	Input R2			***
;	***	ﾘﾝｸ(内部制御)ﾊﾟﾙｽ		***
;	***	Input R0 DIRECT			***
;	***	方向固定			***
;	***					***
;	*******************************************
;	MOV.L	#_SETX_DNAREA_JG_PLS,R4			;反転設定不可範囲LINK-PLS
;	MOV.L	@R4,R2					;

_LNKPLS_OBJ_DAT_MAK2:
	SUB_START
	PUSH_REG1 R0					;SHIN
	PUSH_REG1 R2					;1ROT DATA

;;	MOV.L	#_LINK_PV_ABSPLS,R4		;
;;	MOV.L	@R4+,R1					;
;;	MOV.L	@R4,R2					;
;;	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)
;;	MOV.L	R1,@(0,R4)				;
;;	MOV.L	R2,@(4,R4)				;

	FAR_JSR	#_X_SET_PV_ABS_TO_OBJ,R0			;20060919

	FAR_JSR	#_NOW_INC_DIG_MAK,R0			;


;	=== 目標角度() ====
	MOV.L	#_LINK_NOWROT_OFSPLS_P,R4		;[目標側の位置]
	MOV.L	@R4,R1					;現在 ***.* pls "+"data
							;目標 ***.* pls
	POP_REG1 R2					;
	POP_REG1 R0					;
	TST	R0,R0					;
	TST_BIT_ON LNKPLS_OBJ_DAT_MK2_100		;DIRECT MINAS
;--------FWD-----------
	SUB	R1,R2					;R1(PV) < R2(SV);
	CMP/PL	R2					;
	BT	LNKPLS_OBJ_DAT_MK2_050			;YES 
	MOV.L	#_LINK_1ROT_PLS,R5			;
	MOV.L	@R5,R4					;
	ADD	R4,R2					;
	CMP/PZ	R2
	BT	LNKPLS_OBJ_DAT_MK2_050			;0,+
	FAR_JSR	#_POS_CALC_MISS0,R1			;EMG-ERR
	XOR	R2,R2					;
LNKPLS_OBJ_DAT_MK2_050					;+1REV
;	----------------ﾆｱｾﾞﾛなら1回転+する----------------
	MOV.L	#_SET1_OBJARA_INPXPLS,R1		;
	MOV.W	@R1,R3					;
	CMP/GE	R3,R2					;
	BT	LNKPLS_OBJ_DAT_MK2_080			;
	MOV.L	#_LINK_1ROT_PLS,R5			;
	MOV.L	@R5,R4					;
	ADD	R4,R2					;
LNKPLS_OBJ_DAT_MK2_080					;
	M_BRA	LNKPLS_OBJ_DAT_MK2_300			;


;--------REV-----------
LNKPLS_OBJ_DAT_MK2_100:					;R2
	SUB	R1,R2					;R1(PV) > R2(SV)
	CMP/PZ	R2					;
	BF	LNKPLS_OBJ_DAT_MK2_150			;YES
	MOV.L	#_LINK_1ROT_PLS,R5			;"0,+"
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
LNKPLS_OBJ_DAT_MK2_150					;-1REV
	CMP/PL	R2					;
	BF	LNKPLS_OBJ_DAT_MK2_200			;0,"-"
	FAR_JSR	#_POS_CALC_MISS0,R1			;EMG-ERR
	XOR	R2,R2					;
LNKPLS_OBJ_DAT_MK2_200					;

;	----------------ﾆｱｾﾞﾛなら1回転+する----------------
	MOV.L	#_SET1_OBJARA_INPXPLS,R1		;
	MOV.W	@R1,R3					;
	NEG	R3,R3					;
	CMP/GE	R3,R2					;-2000
	BF	LNKPLS_OBJ_DAT_MK2_280			;
	MOV.L	#_LINK_1ROT_PLS,R5			;
	MOV.L	@R5,R4					;
	SUB	R4,R2					;
LNKPLS_OBJ_DAT_MK2_280					;
;	---------------------------------------------------


LNKPLS_OBJ_DAT_MK2_300					;
	XOR	R5,R5					;
	MOV	R2,R6					;R5,R6
	CMP/PZ	R2					;
	BT	LNKPLS_OBJ_DAT_MK2_600			;
	MOV	#-1,R5					;
LNKPLS_OBJ_DAT_MK2_600:					;


	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)	;
	MOV.L	@R4+,R1					;
	MOV.L	@R4,R2					;
	PUSH_REG1 R1
	PUSH_REG1 R2
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4				;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@R4						;
	MOV.L	R2,@(1*4,R4)					;目標位置ｾｯﾄ
	POP_REG1 R6
	POP_REG1 R5
	
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2
	XOR	R3,R3
	CMP/PZ	R1				;
	BT	LNKPLS_OBJ_DAT_MK2_750		;
	MOV	#BIT0,R3			;
LNKPLS_OBJ_DAT_MK2_750:				;
	MOV.L	#_POS_DRV_DIRECT,R1		;起動時(SV-LEVEL)
	MOV.W	@R1,R2				;
	MOV.W	R3,@R1				;
	XOR	R3,R2				;
	TST	R2,R2				;
	TST_BIT_OF LNKPLS_OBJ_DAT_MK2_800	;
	FAR_JSR	#_POS_CALC_MISS0,R1			;EMG-ERR
LNKPLS_OBJ_DAT_MK2_800:				;

	MOV.L	#_POSLSI_DRIV_SHIN,R1		;//BIT0
	MOV.W	@R1,R0				;
	AND	#LOW ~BIT0,R0			;
	OR	R3,R0				;
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS


