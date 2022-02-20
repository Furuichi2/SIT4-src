;	***********************************
;	***				***
;	***	フルクローズ関連	***
;	***				***
;	***********************************
_POS_LATE1		.EQU	D'1000	;100.0%
_POS_GEN_BEFORE_LNG	.EQU	D'1000	;1000ﾊﾟﾙｽ
_POS_LATE_CALC_MAX	.EQU	D'1000	;1000ﾊﾟﾙｽ
;	***********************************
;	***				***
;	***	払出中処理		***
;	***	(起動時の)		***
;	***				***
;	***********************************
;	ANS 	R0=0	 (制御状態)
;	 	R0.BIT2=1(BUSY完了)
;
;_INT_CLS_CTL_FLG,R1	;
;BIT0:INIT START
;BIT1:(反転必要)==>停止待ち<再計算>
;BIT2:ﾆｱｾﾞﾛに入った<1回目>==>停止待ち<払出=0 待ち>
;BIT3:ﾆｱｾﾞﾛに入ったまたは停止後の処理(KPに関係なく残ﾊﾟﾙｽ=0なら1ﾊﾟﾙｽずつ足していく)
;BIT4:
;BIT5:
;BIT6:完了
;残りﾊﾟﾙｽ+AのAの上限は1000ﾊﾟﾙｽとする<>
;
;
;(本当はこの中で多段の動きを考慮して、”Ｖ”指定の処理も必要)
;
	.IMPORT	_CPUB_HENSA_FLG_CLR			;

_POS_CLS_TYP1_POS_CTL1:
	SUB_START
	MOV.L	#_poslsi1_top+_PLSI_CH1+_PLS_OutPposL,R6		;R/W 指令ﾊﾟﾙｽｶｳﾝﾀ(残ﾊﾟﾙｽ)
	MOV.L	@R6,R11							;(data latch)
	MOV.L	#_ACCESS_ERR1+9*4,R6					;**

	SWAP.W	R11,R11							;
	MOV.L	#_POSLSI_CHK_RESTPLS,R1					;
	MOV.L	R11,@R1							;

	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(目標位置､実測位置作成,R0=R5=ｸﾛｰｽﾞするかどうか？)
	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_NOT		;R5=工程 R0=0停止工程ではない
	MOV.L	#_CPOS_STEP_MAX,R1			;//設定
	MOV.W	@R1,R2					;
	ADD	#1,R2					;
	CMP/EQ	R5,R2					;
	BF	POS_CLS_TYP1_POSCTL1_000		;最終工程ではない
POS_CLS_TYP1_POSCTL1_NOT:				;
;	===== ｻｲｸﾙﾁｪﾝｼﾞ====
;	===== 位置による速度切り替え＋速度連続のｽﾃｯﾌﾟ切替====
	FAR_JSR	#_SPD_STEP_CHG_FWD,R0	;(STEP番号切替/速度切り替え)
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;	===========================================
;	===		最終工程		===
;	===========================================
;	ﾊﾝﾄﾞｼｪｲｸのみ行う
;;	FAR_JSR	#_OPEN_ROT_NEAR_ZERO_CHK,R0		;

	FAR_JSR	#_OPEN_ROT_NEAR2_ZERO_CHK,R0		;(ｵｰﾌﾟﾝでﾆｱｾﾞﾛにいるかどうか)
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
	TST	#BIT2,R0				;
	TST_BIT_OF TYP1_OPEN_PRC_200			;払出完了?

	FAR_JSR	#_CPU_BA_NZR_ON_JG,R0			;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_050			;相手側は終わった
	MOV.L	#_NEAR_IN_FLG,R1			;ﾆｱｾﾞﾛ扱い
	MOV.W	@R1,R0					;
	OR	#BIT0,R0				;
	MOV.W	R0,@R1					;
TYP1_OPEN_PRC_050:

	MOV.L	#_NEAR_IN_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_200			;

	FAR_JSR	#_CMPAB_NEAR_END_PROC,R0		;
	TST	R0,R0					;
	TST_BIT_OF TYP1_OPEN_PRC_200			;

	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;ﾆｱｾﾞﾛ+払い出し完了

TYP1_OPEN_PRC_200
	XOR	R0,R0
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;




;	===========================
;	===	ﾌﾙｸﾛｰｽﾞ		===
;	===========================
POS_CLS_TYP1_POSCTL1_000:
	MOV.L	#_INT_CLS_CTL_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ｸﾛｰｽﾞ処理開始?
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_100	;

	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CALC_FULCLS_MXPLS,R1		;ｲﾝﾁﾝｸﾞMAX量
	MOV.W	R0,@R1				;

;	===== SIG-OFF[1] =====
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_050		;

;	======= 第一払い出し中====
;;	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(目標位置､実測位置作成)
;;	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;ANS R0,R6(ﾘﾆｱ実測ﾊﾟﾙｽ),R7(1回転内目標ﾊﾟﾙｽ)
;;	CMP/EQ	#0,R0					;
;;	BF	POS_CLS_TYP1_POSCTL1_030
;;	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;;	FAR_JSR	#_POS_LSI_SLOW_STOP,R0			;
;;	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
;;POS_CLS_TYP1_POSCTL1_030:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	=========================
;	=====(開始条件成立)======
;	=========================
POS_CLS_TYP1_POSCTL1_050:
	MOV	#BIT0,R0				;
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;

	MOV.W	#D'50,R0				;50msec
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	R0,@R1					;遅延時間=0

;	========================
;	===== 初期起動==========
;	========================
;	自起動周波数=TOP-SPEED
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET1,R0	;

	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.W	@R1,R3					;8ﾊﾟﾙｽ
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT	;

POS_CLS_TYP1_POSCTL1_100:
POS_CLS_TYP1_POSCTL1_105:			;
;	===========================
;	===	最終遷移	===
;	===========================
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT6,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_110

	FAR_JSR	#_LOD_POS_STS_REG,R1			;
	TST	#BIT2,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_107		;

	FAR_JSR	#_CMPAB_NEAR_END_PROC,R0		;
	TST	R0,R0					;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_108		;
POS_CLS_TYP1_POSCTL1_107:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

POS_CLS_TYP1_POSCTL1_108:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_PC_END		;終了

;	====================================
;	===	通常運転or特殊な状態	====
;	====================================
POS_CLS_TYP1_POSCTL1_110:
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_200		;(通常制御)

;	====== 1回ﾆｱｾﾞﾛに入ってからの処理======
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG,R1			;
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_115		;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;払出待ち完了待ち

POS_CLS_TYP1_POSCTL1_115:				;
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	@R1,R0					;遅延時間=0
	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_117		;
	ADD	#-1,R0					;
	MOV.W	R0,@R1					;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;払出待ち完了待ち
POS_CLS_TYP1_POSCTL1_117:				;

;	==== 停止した ====
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(ﾃﾞｰﾀ読み出し R6,R7)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;ANS R0,R6(ﾘﾆｱ実測ﾊﾟﾙｽ),R7(1回転内目標ﾊﾟﾙｽ)
;;;;;;	CMP/EQ	#0,R0					;(ﾆｱｾﾞﾛ範囲内)
;;;;;;	BF	POS_CLS_TYP1_POSCTL1_118		;
	CMP/EQ	#0,R0					;(ﾆｱｾﾞﾛ範囲内)
	BF	POS_CLS_TYP1_POSCTL1_118		;
;	===================================
;	==== ﾆｱｾﾞﾛ範囲内 終了決定	===
;	===================================
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
;	====== 二重回路対策<CPUA>===========
	MOV.L	#_INT_CLS_CTL_FLG,R1			;やめる事を決定
	MOV.W	@R1,R0					;
	OR	#BIT6,R0				;
	MOV.W	R0,@R1					;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;

;	==================================
	FAR_JSR	#_POS_LSI_WORK_STOP2,R0
	FAR_JSR	#_POS_LSI_WORK_STOP_CLR,R0
;	==================================

	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	===========================
;	====== ｲﾝﾁﾝｸﾞ処理==========
;	===========================
POS_CLS_TYP1_POSCTL1_118:					;
;	=== 再起動処理(再起動時はKP=1) ====
;	(方向作成)
;	(ﾃﾞｰﾀ作成)
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;R6破壊

	MOV.L	#_SET1_INCPOS_KP01,R1			;
	MOV.W	@R1,R3					;8ﾊﾟﾙｽ
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()
	MOV	#(BIT2+BIT0),R0				;1ﾊﾟﾙｽ制御 BIT2:1PLS制御
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;


;	=========通常運転(ﾆｱｾﾞﾛ待ち) =====
POS_CLS_TYP1_POSCTL1_200:
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(目標位置､実測位置作成)
	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0			;ANS R0,R6(ﾘﾆｱ実測ﾊﾟﾙｽ),R7(1回転内目標ﾊﾟﾙｽ)
	CMP/EQ	#0,R0							;
	BF	POS_CLS_TYP1_POSCTL1_220					;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0						;
	FAR_JSR	#_POS_LSI_SLOW_STOP,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_CLS_CTL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0						;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;ﾆｱｾﾞﾛにはいった

POS_CLS_TYP1_POSCTL1_220:
	CMP/PZ	R0					;+?
	BF	POS_CLS_TYP1_POSCTL1_240		;NO ﾏｲﾅｽ
;	=== ＋方向へ行き過ぎている　ﾏｲﾅｽへ向かうべきだ	;
	MOV.L	#_POSLSI_DRIV_SHIN,R4			;//BIT0
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_260		;OK
	M_BRA	POS_CLS_TYP1_POSCTL1_250		;

POS_CLS_TYP1_POSCTL1_240:
	MOV.L	#_POSLSI_DRIV_SHIN,R4			;//BIT0
	MOV.W	@R4,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_260		;OK

;	======== 行き過ぎた ====
POS_CLS_TYP1_POSCTL1_250:
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0						;
	FAR_JSR	#_POS_LSI_SLOW_STOP,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_CLS_CTL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0						;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT					;

POS_CLS_TYP1_POSCTL1_260:
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;



POS_CLS_TYP1_POSCTL1_PC_END:
	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;

POS_CLS_TYP1_POSCTL1_OUT_WAIT:				;
	XOR	R0,R0					;まだよ
POS_CLS_TYP1_POSCTL1_END:
	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	ﾌﾙｸﾛｰｽﾞﾆｱｾﾞﾛ		***
;	***				***
;	***********************************
;	ANS R0(ﾌﾙｸﾛｰｽﾞすべきかどうか R0=0しない R0 !=0(工程)ﾌﾙｸﾛｰｽﾞ)
;	ANS R6 1回転目標ﾊﾟﾙｽ
;	ANS R7 1回転ﾘﾆｱﾊﾟﾙｽ
;
;
;	設定=0度　==>312度を目標 
;	180より大きい区間は　－扱いで考える(1)
;	もし1800より大きければ
;
;	-1*(3600-現在ﾊﾟﾙｽ)
_POS_CLS_TYP1_PROC_CHK:
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;
	MOV	R0,R5				;工程PUSH
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R0			;現状の工程の目標工程
	MOV.L	#_SDATCLS_TRG_STEP,R1;//速度連続の最後のｽﾃｯﾌﾟ
	MOV.W	R0,@R1

	CMP/EQ	R0,R5				;停止させる工程でのみﾌﾙｸﾛｰｽﾞは行う
	BT	POS_CLS_TYP1_PROCCHK_050	;R0=R5 ANS R5=工程,R0
	XOR	R0,R0				;ANS MAK
POS_CLS_TYP1_PROCCHK_050:			;
	PUSH_REG1 R0				;
;	====================================
	MOV	R5,R0				;工程
	MOV.L	#_SDATCLS_UPOBJ_PLS,R5		;
	MOV.L	#_CPOS_STEP_MAX,R1		;//設定
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/GE	R2,R0				;MAX=NOW
	BT	POS_CLS_TYP1_PROCCHK_100	;

	MOV.L	#_SDATCLS_OBJPLS,R5		;
	ADD	#-1,R0				;
	SHLL2	R0				;4BYTE
	ADD	R0,R5				;
POS_CLS_TYP1_PROCCHK_100:
	MOV.L	@R5,R7				;
	MOV	R7,R2
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(目標ﾊﾟﾙｽ+/-ﾊﾟﾙｽ変換)
	MOV	R2,R7				;R7:目標位置;ANS:目標位置(設定ﾚﾍﾞﾙ)
;	============================================

;	==== 2003-02-21 ===
	MOV.L	#_DBG_REVMOD_OBJPLS,R4
	MOV.L	R2,@R4
;	====================

;	============================================
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4	;//余り角度 +ﾃﾞｰﾀ
	MOV.L	@R4,R6				;
	MOV	R6,R2				;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(ﾘﾆｱｽｹｰﾙ==>+/-ﾊﾟﾙｽ変換)
	MOV	R2,R6				;

;	==== 2003-02-21 ===
	MOV.L	#_DBG_REVMOD_CTLPLS,R0	;
	MOV.L	R2,@R0			;
;	===================

	POP_REG1 R0				;
	MOV	R0,R5				
	SUB_END	
	M_RTS

;	Input 工程=R5
;	Input R7
;	ANS 	R0:0,1,-1
;	R0	=0 :ﾆｱｾﾞﾛ範囲内
;		=1 :正(正転運転では行き過ぎている/逆転運転では生きたりない)
;		=-1:負(正運転では行きたりない    /逆転運転では行き過ぎている)
;	ANS	R6:ﾘﾆｱPLS現在位置

;
_POS_CLS_TYP1_NEAR_ZERO_CHEAK:
	SUB_START
	MOV.L	#_SDATCLS_TRG_STEP,R4		;//速度連続の最後のｽﾃｯﾌﾟ
	MOV.W	@R4,R0				;
	ADD	#-1,R0				;
	SHLL2	R0				;
	SHLL	R0				;8byte
	MOV.L	#_SDATCLS_OBJ_NEAR_UPDNPLS,R4	;//+0*4:UP +1*4 DN
	ADD	R0,R4				;
	MOV.L	@R4+,R3				;目標位置+ALFA(結果"-")
	MOV.L	@R4,R1				;目標位置-ALFA
	CMP/GE	R1,R3				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_100	;
	MOV	R1,R0				;
	MOV	R3,R1				;
	MOV	R0,R3				;
POS_CLS_TYP1_NEAR_ZR_CHK_100:			;

;	==== 2003-02-21 ===================
	MOV.L	#_DBG_REVMOD_UPPLS,R0	;
	MOV.L	R3,@R0			;
	MOV.L	#_DBG_REVMOD_DNPLS,R0	;
	MOV.L	R1,@R0			;
;	===================================



	MOV	#1,R0
	CMP/GT	R3,R6				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+側へｵｰﾊﾞ

	MOV	#-1,R0				;
	CMP/GE	R1,R6				;R1=< R6 NO
	BF	POS_CLS_TYP1_NEAR_ZR_CHK_200	;(範囲内)
	XOR	R0,R0
POS_CLS_TYP1_NEAR_ZR_CHK_200:			;
;	===========================================
;	=== <CPU-Aが終わりを告げたら終わり> 	===
;	=== <CPU-Bが終わりを告げても終わり?>	===
;	===========================================
	PUSH_REG1 R2
	PUSH_REG1 R3

	PUSH_REG1 R0
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
	XOR	R2,R2				;CPUAは自分から終わる
	.AELSE
	FAR_JSR	#_CPU_BA_NZR_ON_JG,R0		;
	MOV	R0,R2				;
	.AENDI
	POP_REG1 R0				;

	TST	R2,R2				;
	TST_BIT_OF POS_CLS_CPUB_TO_CPUA_100	;
	XOR	R0,R0				;
POS_CLS_CPUB_TO_CPUA_100:			;

	POP_REG1 R3
	POP_REG1 R2
	SUB_END
	M_RTS


;	***********************************
;	***	Input R1,R2		***
;	***********************************
;	R1,R2 絶対値
_CLS_POS_LENGTH_ADD_DATA:
	SUB_START
	MOV.L	#_POSLSI_DRIV_SHIN,R4					;
	MOV.W	@R4,R0							;
	TST	#BIT0,R0						;
	TST_BIT_OF CLS_POS_LENGTH_ADDATA_050				;
	NEG1_64	H_REG=R1,L_REG=R2,WKREG=R4				;|R1,R2|
CLS_POS_LENGTH_ADDATA_050:						;
	MOV.L	#_LNGTH_TOTAL_OUTPLS,R7					;//符号つき TOTAL=TOTAL+ADD ADD_DATA<=0
	MOV.L	@R7,R5							;
	MOV.L	@(4,R7),R6						;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;
	MOV.L	R1,@R7							;
	MOV.L	R2,@(4,R7)						;
	SUB_END
	M_RTS

;	===== INPUT R2()
_CLS_POS_OUT_PLS_MAK1:
	SUB_START

	CMP/PZ	R2
	BT	POS_CLS_TYP1_POSCTL1_320		;
	NEG	R2,R2					;
POS_CLS_TYP1_POSCTL1_320:				;
	MOV	R2,R10					;?

	MOV.L	#_CALC_FULCLS_MXPLS,R1		;ｲﾝﾁﾝｸﾞMAX量
	MOV.W	@R1,R2				;
	MOV	R2,R3				;
	SHLR	R3				;
	MOV.W	R3,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***	260から0度の間は"-"になる	***
;	*******************************************
;	R0~R2
	.EXPORT	_FUL_CLS_OBJPLS_CHK
_FUL_CLS_OBJPLS_CHK:	;Input R2 もし260~0の間なら"-"のﾊﾟﾙｽになる
	SUB_START
	MOV.L	#_SETX_FULCLS_AREA_PLS,R1	;//260.0==>PLS
	MOV.L	@R1,R0				;
	CMP/GE	R0,R2				;R2 OK
	BF	FUL_CLS_OBJPLSCK_050		;
	MOV.L	#_LINK_1ROT_PLS,R1		;//1回転ﾊﾟﾙｽ(設定ﾚﾍﾞﾙ)
	MOV.L	@R1,R0				;
	SUB	R2,R0				;360-359=1
	NEG	R0,R2				;-1
	CMP/PL	R2				;
	BF	FUL_CLS_OBJPLSCK_050		;
	XOR	R2,R2				;
FUL_CLS_OBJPLSCK_050:				;
	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	目標位置→LENGTH	***
;	***				***
;	***********************************
;	Input R1,R2(目標位置)
;	Output R1,R2                       
	.IMPORT	_POSCHG_LINK_ABSPLS_ROTNUM_OFSPLS
_FUL_CLS_LENGH_ADD_CALC:
	SUB_START

	MOV.L	#_LINK_SV_OBJ_ABSPLS,R5	;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	MOV.L	R1,@R5						;
	MOV.L	R2,@(4,R5)					;絶対目標位置
	
;	== ﾛｯﾄﾃﾞｰﾀを取り除く==					;
	FAR_JSR	#_POSCHG_LINK_ABSPLS_ROTNUM_OFSPLS,R0		;R1,R2+/-回転数 余りパルス(符号つき)
	MOV	R3,R2						;ﾊﾟﾙｽ
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL200				;
	MOV.L	#_LINK_1ROT_PLS,R1				;<待機点340度 	目標30度 30-340+360>
	MOV.L	@R1,R4						;		<30>
	ADD	R4,R2						;
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL200				;
	XOR	R2,R2						;"演算誤差0":ありえないはず?BREAK CHEAK
FULCLS_LNG_ADD_CAL200:						;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0
	PUSH_REG1 R2
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4			;//余り角度 +ﾃﾞｰﾀ
	MOV.L	@R4,R2						;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;
	MOV	R2,R3				;
	POP_REG1 R2				;
;	==== 運転方向(CW/CCW)==
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R4				;ﾀｲﾏLOAD
	ADD	#-1,R4				;
	SHLL2	R4				;
	MOV.L	#_CPOS_SDAT1_INF1,R0		;
	MOV.L	@(R0,R4),R0			;BIT1=0 CW
	TST	#BIT1,R0			;
	TST_BIT_ON FULCLS_LNG_ADD_CAL300	;
;	====== 正転運転 ===
	SUB	R3,R2				;
;;	CMP/PZ	R2				;
;;	BT	FULCLS_LNG_ADD_CAL250		;
;;	MOV.L	#_LINK_1ROT_PLS,R1		;
;;	MOV.L	@R1,R4				;
;;	ADD	R4,R2				;
;;FULCLS_LNG_ADD_CAL250:				;
	M_BRA	FULCLS_LNG_ADD_CAL400		;

FULCLS_LNG_ADD_CAL300:
;	====== 逆転運転 ===
	SUB	R3,R2				;
;;	CMP/PL	R2				;
;;	BF	FULCLS_LNG_ADD_CAL350		;
;;	MOV.L	#_LINK_1ROT_PLS,R1		;
;;	MOV.L	@R1,R4				;
;;	SUB	R4,R2				;
;;FULCLS_LNG_ADD_CAL350:
;;	NOP
FULCLS_LNG_ADD_CAL400:
	XOR	R1,R1						;
	CMP/PZ	R2						;
	BT	FULCLS_LNG_ADD_CAL450				;
	ADD	#-1,R1						;
FULCLS_LNG_ADD_CAL450:

;	====== 差分======
	MOV.L	#_LNGTH_ADD_DATA,R4		;//符号付き
	MOV.L	R1,@R4				;
	MOV.L	R2,@(4,R4)			;
	SUB_END
	M_RTS


	.EXPORT	_FUL_DATA_INIT	;USED R1,R0
_FUL_DATA_INIT:
	SUB_START
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	XOR	R0,R0					;
	MOV.W	R0,@R1					;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***********************************
;
;	Input R6:PV
;	Input R7:SV
;
;	Input R3:ｲﾝﾁﾝｸﾞ量
;
_FUL_PLS_START:
	SUB_START
	PUSH_REG1 R3
	FAR_JSR	#_POS_LSI_WORK_STOP2,R0

	FAR_JSR	#_POS_LSI_WORK_STOP_CLR,R0
	
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(目標位置､実測位置作成)
	POP_REG1 R3
	MOV.L	#_POSLSI_DRIV_SHIN,R4				;
	MOV.W	@R4,R0
	AND	#LOW ~BIT0,R0				;
	MOV	R7,R2					;R7:SV R6:PV
	SUB	R6,R2					;SV_-PV_RNA(偏差)
	CMP/PZ	R2					;
	BT	FUL_PLS_ST120
	OR	#BIT0,R0				;
FUL_PLS_ST120:						;
	MOV.W	R0,@R4					;方向作成
	XOR	R1,R1					;R1,R2(絶対ﾊﾟﾙｽ)
	MOV	R3,R2					;
	FAR_JSR	#_CLS_POS_LENGTH_ADD_DATA,R0		;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;位置決めLSIｱｸｾｽ(毎ｽｷｬﾝ)
	FAR_JSR	#_FWD_REV_START,R1			;起動
	NOP
	NOP
	NOP
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	SUB_END
	M_RTS
