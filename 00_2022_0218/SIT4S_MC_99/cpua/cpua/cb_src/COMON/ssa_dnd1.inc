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
_DND_NEG_STEP_CTRL:
	SUB_START

	MOV.L	#_INT_DND_STEP_FLG,R1		;段取り共通
	MOV.W	@R1,R0				;
	TST	#(BIT1+BIT0),R0			;
	TST_BIT_OF DND_NEGSTEPCTL_100		;BIT0:ﾀｲﾏ制御開始
	M_BRA	DND_NEGSTEPCTL_300		;BIT1:次の回転起動

DND_NEGSTEPCTL_100:
	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0	;

	FAR_JSR	#_LOD_POS_STS_REG,R1	;
	TST	#BIT2,R0		;停止?
	TST_BIT_ON DND_NEGSTEPCTL_200	;YES 停止中 1:停止 0:払出中
	M_BRA	DND_NEGSTEPCTL_900	;

;	===========================
;	===	払出停止	===
;	===	回転時		===
;	===========================
;	--------払い出し完了----------
DND_NEGSTEPCTL_200:

;	------------ 2021-11-11-------------
	MOV.L	#_NEG_DND_STOP_POS_END_F,R1			;
	MOV.B	@R1,R0								;
	TST		R0,R0								;
	TST_BIT_ON DND_NEGSTEPCTL_900				;

;	------------ 2021-11-11-------------
	FAR_JSR	#_DND_NEG_STOP_SVCHK,R0				;

	MOV.L	#_NEG_DND_STOP_USE_F,R1				;	//上死点(0)<停止<170の時 On
	MOV.B	@R1,R0								;
	TST		R0,R0								;
	TST_BIT_OF DND_NEGSTEPCTL_250				;

	FAR_JSR	#_DND_NEG_LNK_STEP_CHANGE2,R0		;

	MOV.B	#BIT0,R0
	MOV.L	#_NEG_DND_STOP_POS_END_F,R1			;
	MOV.B	R0,@R1								;

	M_BRA	DND_NEGSTEPCTL_900					;


DND_NEGSTEPCTL_250:
;	-----------------------------------

;	>>>> 切替ﾀｲﾏｾｯﾄ <<<<
;	===============================================
;;;2014-05-30	MOV.L	#_PAR_START_WAIT_DND,R1					;段取時切替WAIT時間
	MOV.L	#(_PAR_START_WAIT_DND-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;段取時切替WAIT時間
	MOV.W	@R1,R1					;
	MOV.L	#_SDAT_WAIT_PVTIM,R4						;
	MOV.L	R1,@R4								;
;	FLG=(BIT0):ｾｯﾄ								;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_DND_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;ﾀｲﾏ起動
	M_BRA	DND_NEGSTEPCTL_900						;

DND_NEGSTEPCTL_300:
	TST	#BIT1,R0		;
	TST_BIT_ON DND_NEGSTEPCTL_400	;

;	===== 切替ﾀｲﾏ待ち ====

	DN_TIME LG=L,MEM_ADR=_SDAT_WAIT_PVTIM	,WKREG1=R1,WKREG2=R4	;2014-05-30


	MOV.L	#_SDAT_WAIT_PVTIM,R4	;
	MOV.L	@R4,R1			;
	TST	R1,R1			;
	TST_BIT_OF DND_NEGSTEPCTL_320	;
	M_BRA	DND_NEGSTEPCTL_900	;

DND_NEGSTEPCTL_320:
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_DND_STEP_FLG,LG=W,BIT=BIT1,WKREG=R1 ;TIME UP
	M_BRA	DND_NEGSTEPCTL_900		;


;	======= 次の起動 =====
DND_NEGSTEPCTL_400:
;	===================================
;	===	二重回路対策		===
;	===	工程完了		===
;	===================================
	FAR_JSR	#_CMPAB_STEP_END_PROC,R0	;
	TST	R0,R0				;
	TST_BIT_ON DND_NEGSTEPCTL_420		;
	M_BRA	DND_NEGSTEPCTL_900		;

DND_NEGSTEPCTL_420:				;
	FAR_JSR	#_CMPSTP_STEP_END_CLR,R0	;//位置決め完了としたい

;;2021-11-11;	====  次の動作の演算 =====
;;2021-11-11	MOV.L	#_INT_DND_NEG_STEP,R5		;
;;2021-11-11	MOV.W	@R5,R0				;
;;2021-11-11	CMP/EQ	#1,R0				;
;;2021-11-11	BF	DND_NEGSTEPCTL_440		;もし0or2なら待機点なので1へ遷移
;;2021-11-11	MOV	#2,R0				;もし1(目標位置への動作)なら2へ（待機点）
;;2021-11-11	M_BRA	DND_NEGSTEPCTL_460		;
;;2021-11-11DND_NEGSTEPCTL_440:				;
;;2021-11-11	MOV	#1,R0				;もし0or2(待機点への動作)なら1
;;2021-11-11DND_NEGSTEPCTL_460:				;
;;2021-11-11	MOV.W	R0,@R5				;
;;2021-11-11	FAR_JSR	#_DND_LNK_STEP_CHECK1,R0	;<<>>
;;2021-11-11	FAR_JSR	#_DND_LNKPLS_OBJMAK1,R1		;ｽﾃｯﾌﾟに応じて待機点1/目標位置/待機点2 _POS_DRV_DIRECT
;;2021-11-11

	FAR_JSR	#_DND_NEG_LNK_STEP_CHANGE0,R0				;
	FAR_JSR	#_DND_LNKPLS_OBJMAK1,R1					;ｽﾃｯﾌﾟに応じて待機点1/目標位置/待機点2 _POS_DRV_DIRECT

;	===================
;	===	起動	===
;	===================
DND_NEGSTEPCTL_580:
	FAR_JSR	#_DND_1STEP_DATA_MAK1,R0	;_LNGTH,SHIN,SPEED
	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0	;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0	;位置決めLSIｱｸｾｽ(毎ｽｷｬﾝ)
	FAR_JSR	#_FWD_REV_START,R1		;起動
	XOR	R0,R0				;
	MOV.L	#_INT_DND_STEP_FLG,R1		;//ｽﾃｯﾌﾟ,段取り共通
	MOV.W	R0,@R1				;Q
	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0	;

DND_NEGSTEPCTL_900:
	SUB_END
	M_RTS



