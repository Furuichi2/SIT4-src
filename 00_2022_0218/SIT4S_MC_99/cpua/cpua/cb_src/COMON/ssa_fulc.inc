;	***********************************
;	***				***
;	***	フルクローズ関連	***
;	***				***
;	***********************************
_POS_LATE1		.EQU	D'1000	;100.0%
_POS_GEN_BEFORE_LNG	.EQU	D'1000	;1000ﾊﾟﾙｽ
_POS_LATE_CALC_MAX	.EQU	D'1000	;1000ﾊﾟﾙｽ

	.IMPORT	_PAR_NEGERR_ENB		;2012-05-30
	.IMPORT	_PAR_NEG_EXITTIM	;2012-10-05

	.IMPORT	_PAR_KAJYU_HLDSPD	;1　一旦停止中の荷重制御速度
	.IMPORT	_PAR_KAJYU_ARASPD	;2[荷重制御]一旦停止中のromﾊﾟﾗ範囲外 荷重制御速度 pls7/s
	.IMPORT	_PAR_KAJYU_CHGARA	;3[荷重制御] 20KNを設定の荷重完了範囲から引くARA->HLD

	.IMPORT	_PAR_NEGCTL_SPDS1	;

	.IMPORT	_PAR_KAJYU_CTIM1	;2015-06-22周期１
	.IMPORT	_PAR_KAJYU_CTIM2	;2015-06-22周期２
	.IMPORT	_PAR_KAJYU_STPARA	;2015-06-22出力停止幅
	.IMPORT	_PAR_KAJYU_FIRST	;2015-06-22荷重制御開始幅 2015-06-11(H2W/H1F)

	.EXPORT	_REVRSE_BASINC_SPDCALC	;2015-03-15

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
;;;;	.IMPORT	_CPUB_HENSA_FLG_CLR			;

_POS_CLS_TYP1_POS_CTL1:
	SUB_START

;;;;;;ﾃﾞﾊﾞｯｸ	MOV.L	#_poslsi1_top+_PLSI_CH1+_PLS_OutPposL,R6		;R/W 指令ﾊﾟﾙｽｶｳﾝﾀ(残ﾊﾟﾙｽ)
;;;;;;ﾃﾞﾊﾞｯｸ	MOV.L	@R6,R11							;(data latch)
;;;;;;ﾃﾞﾊﾞｯｸ	MOV.L	#_ACCESS_ERR1+9*4,R6					;**
;;;;;;ﾃﾞﾊﾞｯｸ	SWAP.W	R11,R11							;
;;;;;;ﾃﾞﾊﾞｯｸ	MOV.L	#_POSLSI_CHK_RESTPLS,R1					;
;;;;;;ﾃﾞﾊﾞｯｸ	MOV.L	R11,@R1							;

	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	PUSH_REG1 R5					;
	PUSH_REG1 R0					;
	FAR_JSR	#_KJYU_DATA_INFO_SEL,R0			;227.13
	POP_REG1 R0					;
	POP_REG1 R5					;

;;;;	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;

	.AELSE
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0		;(目標位置､実測位置作成,R0=R5=ｸﾛｰｽﾞするかどうか？)
	.AENDI



	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_NOT		;R5=工程 R0=0停止工程ではない

;	---------------2014-09-22 REPEAT-----------
	MOV.L	#_MOT_REP_F,R1				;//BIT0(ﾘﾋﾟｰﾄ動作
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_NOT20		;


	MOV.L	#_CPOS_STEP_MAX,R1			;//設定
	MOV.W	@R1,R2					;
	ADD	#1,R2					;
	CMP/EQ	R5,R2					;
	BF	POS_CLS_TYP1_POSCTL1_000		;最終工程(戻り)ではない

;-----------2019-04-10(戻り信号のラッチ:異常時の処理チェック用)---------
;;;;不要でした	FAR_JSR	#_HANTEN_LAST_SIG_SET,R0
;	--------------------------------------------------------------------

POS_CLS_TYP1_POSCTL1_NOT:				;

;	===== ｻｲｸﾙﾁｪﾝｼﾞ====
;	===== 位置による速度切り替え＋速度連続のｽﾃｯﾌﾟ切替====
	FAR_JSR	#_SPD_STEP_CHG_FWD,R0	;(STEP番号切替/速度切り替え)

POS_CLS_TYP1_POSCTL1_NOT20:				;

	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
;	===========================================
;	===		最終工程		===
;	===========================================
;	ﾊﾝﾄﾞｼｪｲｸのみ行う
;;	FAR_JSR	#_OPEN_ROT_NEAR_ZERO_CHK,R0		;

	FAR_JSR	#_OPEN_ROT_NEAR2_ZERO_CHK,R0		;(ｵｰﾌﾟﾝでﾆｱｾﾞﾛにいるかどうか)


	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
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


;;2012-10-05 2012-05-30では不具合	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;2012-10-05 2012-05-30では不具合	MOV.W	@R1,R0				;
;;2012-10-05 2012-05-30では不具合	MOV.L	#_CALC_FULCLS_MXPLS,R1		;ｲﾝﾁﾝｸﾞMAX量
;;2012-10-05 2012-05-30では不具合	MOV.W	R0,@R1				;

;;;	==============2012-10-05[本来の形 2012-05-30では不具合]=============
;;;	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;;	MOV.W	@R1,R0				;
;;;	MOV.L	#_NEG_CTRL_BEFOR_OBJ_PLS,R1	;//目標－手前
;;;	MOV.L	@R1,R2				;
;;;	ADD	R2,R0				;
;;;	MOV.L	#_CALC_FULCLS_MXPLS,R1		;ｲﾝﾁﾝｸﾞMAX量
;;;	MOV.L	R0,@R1				;2BYTE->4BYTE 2012-10-05 型変更U2B->U4Bに変更
;;;
;	====== 2012-10-05 仕様変更 180度を最大追い込みとする====
	FAR_JSR	#_FULCLS_MAXPLS_CALC,R0




;	===== SIG-OFF[1] =====
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;20060930POR
	TST	#BIT2,R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_050		;[払い出しパルス終了]
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;

;	=========================
;	=====(開始条件成立)======
;	=========================
POS_CLS_TYP1_POSCTL1_050:
	MOV	#BIT0,R0				;
	MOV.L	#_INT_CLS_CTL_FLG,R1			;[step1:ｵｰﾌﾟﾝ後の起動:180度を目指す]
	MOV.W	R0,@R1					;

;	--------- 2012-05-30----------
;[[neg]][[払い出して達しなければSQへ出力するが次へ進む]]-----------
	FAR_JSR	#_FULCLS_MAXOVER_STEP_INI,R0

	MOV.L	#_PAR_NEG_EXITTIM-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;2 2012-10-5追い込み失敗の待ち時間
	MOV.W	@R1,R0							;
	MOV.L	#_NEG_EXITTIM,R1					;//超変な針の穴を通すタイマ  2012-10-05
	MOV.W	R0,@R1							;


;	===ｵｰﾌﾟﾝ出力完了～ｲﾝﾁﾝｸﾞに切り替わる時のﾓ-ﾀ遅延分のﾀｲﾏ===
;;;2012-05-30	MOV.W	#D'50,R0			;50msec
	MOV.L	#_FUL_CLS_DLYTM_SV,R1			;2012-05-30
	MOV.W	@R1,R0					;2012-05-30
	MOV.L	#_INT_CLS_DYL_TIM,R1			;
	MOV.W	R0,@R1					;遅延時間=0

;	=====2011-05-11[必要か???]======
;;;;;;;;;;;;;;;;;;;;;;;;;;2014-09-16悪さをしている	FAR_JSR	#_FUL_START_FUL_OBJ_SET,R0


;	========================
;	===== 初期起動==========
;	========================
;	自起動周波数=TOP-SPEED
;;;;2006-09-30	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET1,R0	;''''''''''''''''@@@@見直し''''''''''''''
;	-----------------------------
	FAR_JSR	#_REVRSE_BASINC_SPDCALC,R0		;位置_SET_CLSINC_SPDBAS_PLSをｼｽﾊﾟﾗから
	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;2007-07-07
;	-----------------------------
;;;;;;;;;;;;	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;''''''''''''''''@@@@見直し''''''''''''''
;
	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.L	@R1,R3					;30000ﾊﾟﾙｽでしょう2012-05-30ｺﾒﾝﾄ
							;2012-10-05 2BYTE->4BYTE 型U2B->U4Bに変更
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()

	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
;	-------2015-03-15[R01:2014-08-20]--------
	FAR_JSR	#_KAJYU_START_UPCHK,R0
	.AENDI

	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT	;

POS_CLS_TYP1_POSCTL1_100:
POS_CLS_TYP1_POSCTL1_105:			;
;-----------------------とりあえずここ-----------------
	DN_TIME LG=L,MEM_ADR=_SDAT_WAIT_PVTIM	,WKREG1=R1,WKREG2=R4	;[2015-07-22]


;	===========================
;	===	最終遷移	===
;	===========================
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT6,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_110

	FAR_JSR	#_LOD_POS_STS_REG_POR,R1			;
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

;	---------------- 2012-05-30　[[neg]][[払い出して達しなければSQへ出力するが次へ進む]]-----------
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;2012-05-30
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_112	;
	MOV.W	#(BIT2+BIT0),R0			;1ﾊﾟﾙｽ制御 BIT2:1PLS制御
	MOV.L	#_INT_CLS_CTL_FLG,R1		;
	MOV.W	R0,@R1				;
	FAR_JSR	#_FULCLS_MAXOVER_STEP_INI,R0	;
	M_BRA	POS_CLS_TYP1_POSCTL1_OVER98	;
POS_CLS_TYP1_POSCTL1_112:
;	-----------------------------------------
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_113		;
	M_BRA	POS_CLS_TYP1_POSCTL1_200		;(通常制御)

POS_CLS_TYP1_POSCTL1_113:

;	====== 1回ﾆｱｾﾞﾛに入ってからの処理======
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
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
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;
	FAR_JSR	#_POS_CLS_RNA_KJYU_NZ_CHEAK,R0		;[1度ﾆｱｾﾞﾛに入ってからの処理]
	.AENDI


	CMP/EQ	#0,R0					;
	BT	POS_CLS_TYP1_POSCTL1_ED050		;[step3]今もﾆｱｾﾞﾛ内なら完了

	FAR_JSR	#_OVER_DIG_CHK,R0			;
	TST	R0,R0					;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_OVER99		;
	M_BRA	POS_CLS_TYP1_POSCTL1_118		;




;	===================================
;	==== ﾆｱｾﾞﾛ範囲内 終了決定	===
;	===================================
POS_CLS_TYP1_POSCTL1_OVER98:				;
	nop
	nop
POS_CLS_TYP1_POSCTL1_OVER99:				;
	nop
	nop
	nop

POS_CLS_TYP1_POSCTL1_ED050:
	nop
	nop

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
POS_CLS_TYP1_POSCTL1_118:				;[step3 ﾊﾟﾙｽ出力停止し50msec後毎でここにくる]
;	=== 再起動処理(再起動時はKP=1) ====
;	(方向作成)
;	(ﾃﾞｰﾀ作成)

;	----------- 2015-06-22[荷重・位置共通]--------------
	MOV.L	#_SET1_INCPOS_KP01,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_SETX_KJYU_INCPOS_KP01,R1	;
	MOV.W	R0,@R1				;


;	------- 2015-03-15[R01:2014-07-15] ----------
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;
	MOV.L	#_FULCLS_MATHED,R1			;//0:位置 1:荷重
	MOV.W	@R1,R0					;
	TST	R0,R0
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_119A		;位置の速度JUMP

;	-----------2015-06-22--------
;	[未出力[ﾆｱｾﾞﾛ]/再起動ﾊﾟﾙｽ,遅延周期選択追加]
	FAR_JSR	#_RESTART_WAIT_PLS_DATA_SELECT,R0	;
	TST	R0,R0					;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_119E_EX		;

	FAR_JSR	#_REVRSE_KAJYU_AREACHK_BASSET,R0	;荷重:_SET_CLSINC_SPDBAS_PLSをｼｽﾊﾟﾗから
	M_BRA	POS_CLS_TYP1_POSCTL1_119E		;


POS_CLS_TYP1_POSCTL1_119A:				;
	FAR_JSR	#_REVRSE_BASINC_SPDCALC,R0		;位置_SET_CLSINC_SPDBAS_PLSをｼｽﾊﾟﾗから
POS_CLS_TYP1_POSCTL1_119E:				;
	.AENDI

	FAR_JSR	#_POS_LSI_CLS_TOP_EQ_BAS_SET2,R0	;R6破壊

;	------ 2015-06-22 ---------
;;;;	MOV.L	#_SET1_INCPOS_KP01,R1			;
;;;;	MOV.W	@R1,R3					;8ﾊﾟﾙｽ
	MOV.L	#_SETX_KJYU_INCPOS_KP01,R1		;
	MOV.W	@R1,R3					;8ﾊﾟﾙｽ
	FAR_JSR	#_FUL_PLS_START,R0			;Input R6(SV),R7(PV),R3()
	MOV	#(BIT2+BIT0),R0				;1ﾊﾟﾙｽ制御 BIT2:1PLS制御
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	R0,@R1					;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0			;
POS_CLS_TYP1_POSCTL1_119E_EX:				;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;


;	=========通常運転(ﾆｱｾﾞﾛ待ち) =====
POS_CLS_TYP1_POSCTL1_200:
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;
	FAR_JSR	#_POS_CLS_RNA_KJYU_FIRST_NZ_CHEAK,R0	;

	.AENDI


	CMP/EQ	#0,R0							;
	BF	POS_CLS_TYP1_POSCTL1_220					;
	FAR_JSR	#_FWD_REV_STSIG_OFF,R0						;[step2:停止]
	FAR_JSR	#_POS_LSI_SLOW_STOP,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_CLS_CTL_FLG,LG=W,BIT=BIT1,WKREG=R1	;
	FAR_JSR	#_CPUB_HENSA_FLG_CLR,R0						;
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;ﾆｱｾﾞﾛにはいった

POS_CLS_TYP1_POSCTL1_220:

;	input R0
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
;	-----------2015-03-15 荷重の場合ニアゼロにならないからここでオーバを見る--------
	PUSH_REG1 R0
	FAR_JSR	#_OVER_DIG_CHK,R0
	MOV	R0,R1								;
	POP_REG1 R0

	TST	R1,R1
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_222			;
	M_BRA	POS_CLS_TYP1_POSCTL1_250			;
	.AENDI
	
POS_CLS_TYP1_POSCTL1_222:
;	-----------------------------------------------------------------------




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

;-------------------------2012-05-30 CHECK ----------------
;;[[neg]]
;;[[neg]]	MOV.L	#_PAR_NEGERR_ENB-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;
;;[[neg]]	MOV.W	@R1,R0							;
;;[[neg]]	CMP/EQ	#1,R0							;
;;[[neg]]	BF	POS_CLS_TYP1_POSCTL1_280				;
;;[[neg]]
	MOV.L	#_INT_CLS_CTL_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	#(BIT2+BIT1),R0				;
	TST_BIT_ON POS_CLS_TYP1_POSCTL1_280		;(通常制御)

	FAR_JSR	#_FWD_REV_STSIG_OFF,R0			;
	FAR_JSR	#_LOD_POS_STS_REG_POR,R1		;
	TST	#BIT2,R0				;
	TST_BIT_OF POS_CLS_TYP1_POSCTL1_280		;まだﾊﾟﾙｽがある

;	---ﾊﾟﾙｽがなくなった---
	FAR_JSR	#_FULCLS_MAXOVER_ERR_WT,R0		;2012-05-30/2012-10-05

;	----------------------------------------------------------
POS_CLS_TYP1_POSCTL1_280:
	M_BRA	POS_CLS_TYP1_POSCTL1_OUT_WAIT		;



POS_CLS_TYP1_POSCTL1_PC_END:
	MOV	#BIT2,R0				;
	M_BRA	POS_CLS_TYP1_POSCTL1_END		;

POS_CLS_TYP1_POSCTL1_OUT_WAIT:				;
	XOR	R0,R0					;まだよ
POS_CLS_TYP1_POSCTL1_END:

;;;;2018-02-10 	PUSH_REG1 R0
;;;;2018-02-10 	PUSH_REG1 R1
;;;;2018-02-10 	MOV.L	#_FULCLS_TIM_SETFLG,R1		;
;;;;2018-02-10 	MOV.W	@R1,R0				;
;;;;2018-02-10 	MOV.L	#_SQ_CBWK_TOP+_WKSQCB247,R1	;247.0/247.1
;;;;2018-02-10 	MOV.W	R0,@R1				;
;;;;2018-02-10 	POP_REG1 R1
;;;;2018-02-10 	POP_REG1 R0

	SUB_END
	M_RTS


;	***************************
;	***			***
;	***	2015-06-22	***
;;	***			***
;	***************************
;	出力しない,ﾊﾟﾙｽ,遅延周期を設定
;	ANS:R0=0:出力しない
;
_RESTART_WAIT_PLS_DATA_SELECT:
	SUB_START


	FAR_JSR	#_KJYU_NEARZERO3_CHK,R0			;0,1,-1,-2
	TST	R0,R0					;
	TST_BIT_OF RESTART_WAIT_PLS_DATASEL_END		;[ﾘｽﾀｰﾄしない]

	CMP/PZ	R0					;+()
	BT	RESTART_WAIT_PLS_DATASEL_100		;

;	---------範囲外---------
;;;;H2W	MOV.L	#_SVP_OUTPLS_HOSA,R1		;44

	MOV.L	#_PAR_KAJYU_CTIM1-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;368:範囲外
	MOV.W	@R1,R0				;
	MOV.L	#_INT_CLS_DYL_TIM,R1		;
	MOV.W	R0,@R1				;遅延時間=0

	MOV.L	#_SET1_INCPOS_KP01,R1		;31
	MOV.W	@R1,R0				;
	MOV.L	#_SETX_KJYU_INCPOS_KP01,R1	;
	MOV.W	R0,@R1				;

	M_BRA	RESTART_WAIT_PLS_DATASEL_OUT		;

;	------------ニアゼロ範囲内-------------
RESTART_WAIT_PLS_DATASEL_100:

;;;H2W	MOV.L	#_SVP_OUTPLS_HOSB,R1		;45
	MOV.L	#_PAR_KAJYU_CTIM2-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;369:範囲内
	MOV.W	@R1,R0				;
	MOV.L	#_INT_CLS_DYL_TIM,R1		;
	MOV.W	R0,@R1				;遅延時間=0

	MOV.L	#_SET1_RNAPOS_KP01,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_SETX_KJYU_INCPOS_KP01,R1	;
	MOV.W	R0,@R1				;

RESTART_WAIT_PLS_DATASEL_OUT:
	MOV.B	#1,R0					;START
RESTART_WAIT_PLS_DATASEL_END:
	
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.IMPORT	_POSCHG_LINK_DIG_TO_LINK_PLS		;
	.IMPORT	_OBJ_POS_DIG_MAK			;2015-03-15[R01:2014-08-20]

	.ALIGN	4						;
_FULCLS_MAXPLS_CALC:
	SUB_START

;;;;DEBUG	MOV.L	#_SET1_FULCLS_MXPLS,R1		;
;;;;DEBUG	MOV.W	@R1,R2				;
;;;;DEBUG	M_BRA	FULCLS_MAXPLSCAL_200		;

;	-------- 2015-03-15 -----------
	FAR_JSR	#_OBJ_POS_DIG_MAK,R0			;これがない 2015-03-15[R012014-08-20]
;	--------------------------

	MOV.L	#_SV_OBJ360,R1				;停止目標位置角度
	MOV.W	@R1,R3					;
	MOV.W	#D'1800,R4				;
	MOV	R4,R2					;
	SUB	R3,R2					;
	CMP/PZ	R2					;
	BT	FULCLS_MAXPLSCAL_100			;
	ADD	R4,R2					;角度0.1度
FULCLS_MAXPLSCAL_100:					;
	ADD	#1,R2					;+0.1度
	FAR_JSR	#_POSCHG_LINK_DIG_TO_LINK_PLS,R0	;



FULCLS_MAXPLSCAL_200:					;
	MOV.L	#_CALC_FULCLS_MXPLS,R1			;
	MOV.L	R2,@R1					;

;;;	MOV.L	#_LINK_NOWROT_OFSPLS_P,R4	;[[[目標]]]
;;;	MOV.L	@R4,R2				;
;;;
;;;	MOV.L	#_LINK_SV_OBJ_ABSPLS,R5		;//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
;;;	MOV.L	R1,@R5				;
;;;	MOV.L	R2,@(4,R5)			;
;;;
;;;	MOV.L	#_CALC_FULCLS_MXPLS,R1		;ｲﾝﾁﾝｸﾞMAX量
;;;	MOV.L	R0,@R1				;2BYTE->4BYTE 2012-10-05 型変更U2B->U4Bに変更


	SUB_END
	M_RTS


;	*******************************************
;	***		2012-10-05		***
;	***					***
;	***	180.0度に達したらEXIT		***
;	*******************************************
_OVER_DIG_CHK:
	SUB_START
	MOV.L	#_INC_ENC360,R1			;
	MOV.W	@R1,R2				;
	MOV.W	#D'1798,R0			;179.8
	CMP/HS	R0,R2				;
	BF	OVER_DIGCHK_NOMAL		;ｵｰﾊﾞはしていない

OVER_DIGCHK_ERR:
	FAR_JSR	#_FULCLS_MAXOVER_ERR,R0		;ﾀｲﾏなし
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;
	MOV.W	@R1,R0				;
	AND	#BIT6,R0			
	TST	R0,R0				;
	TST_BIT_OF OVER_DIGCHK_NOMAL		;R0=0SET
	MOV.B	#1,R0				;R0=1
	M_BRA	OVER_DIGCHK_END
OVER_DIGCHK_NOMAL
	XOR	R0,R0
OVER_DIGCHK_END

	SUB_END
	M_RTS


;	***************************
;	***	2012-05-30	***
;	***	反転オーバ	***
;	***************************
;	[[neg]][[払い出して達しなければSQへ出力するが次へ進む]]-----------
	.ALIGN	4						;
_FULCLS_MAXOVER_ERR:
	SUB_START
	M_BRA	FULCLS_MAXOVER_ERRSET		;

_FULCLS_MAXOVER_ERR_WT:
	SUB_START

	MOV.L	#_NEG_EXITTIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF FULCLS_MAXOVER_ERRSET	;
	ADD	#-1,R0				;
	MOV.W	R0,@R1				;
	M_BRA	FULCLS_MAXOVER_ERRWAT		;

FULCLS_MAXOVER_ERRSET:
	MOV.L	#_PAR_NEGERR_ENB-_CB_SYS_PARAM000+_W_PARAM_TOP,R1	;
	MOV.W	@R1,R0							;
	CMP/EQ	#1,R0							;
	BF	FULCLS_MAXOVER_ERRWAT					;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_FUL_CLS_MAXOVER_F,LG=W,BIT=(BIT6+BIT0),WKREG=R1	;BIT6:ERR BIT0:制御


	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
;	------2015-03-15[R01:2014-08-20] 荷重制御情報追加-------------
	MOV.L	#_FULCLS_MATHED,R1			;//0:位置 1:荷重
	MOV.W	@R1,R0					;
	CMP/EQ	#1,R0					;
	BF	FULCLS_MAXOVER_ERRS100			;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_FUL_CLS_MAXOVER_F,LG=W,BIT=(BIT5),WKREG=R1	;BIT5:荷重

FULCLS_MAXOVER_ERRS100:
;	-----------------------------------------------
	.AENDI


FULCLS_MAXOVER_ERRWAT:
	SUB_END
	M_RTS

;	***************************
;	***	2012-05-30	***
;	***	反転オーバCLR	***
;	***************************
;	[[neg]][[払い出して達しなければSQへ出力するが次へ進む]]-----------
	.ALIGN	4						;
	.EXPORT	_FULCLS_MAXOVER_CLR	;
_FULCLS_MAXOVER_CLR:
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_FUL_CLS_MAXOVER_F,R1	;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***************************
;	***	2012-05-30	***
;	***	反転オーバINI	***
;	***************************
;	[[neg]][[払い出して達しなければSQへ出力するが次へ進む]]-----------
	.ALIGN	4						;
_FULCLS_MAXOVER_STEP_INI:
	SUB_START

	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_FUL_CLS_MAXOVER_F,LG=W,BIT=~BIT0,WKREG=R1	;


	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	追い込み達せず信号出力	***
;	***	224.9  各行程		***
;	***	224.10 1回でも		***
;	***				***
;	***********************************
	.EXPORT	_FULCLS_OVER_SIG

	.ALIGN	4			;2012-05-30
_FULCLS_OVER_SIG
	SUB_START

	XOR	R3,R3
	XOR	R4,R4
	MOV.L	#_FUL_CLS_MAXOVER_F,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF FULCLS_OVERSG_100		;異常記憶なし
	MOV.W	#BIT9,R3			;異常有り・リセットまで保持



	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
;	--2015-03-15[R01:2014-08-20追加]---
	TST	#BIT5,R0			;荷重?
	TST_BIT_OF FULCLS_OVERSG_100		;NO
	MOV.W	#BIT10,R3			;
	.AENDI

FULCLS_OVERSG_100

;;;;;	TST	#BIT0,R0			;
;;;;;	TST_BIT_OF FULCLS_OVERSG_200		;制御中なし
;;;;;	MOV.W	#BIT10,R4			;異常有り・記憶はしない
;;;;;FULCLS_OVERSG_200

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB224,R1	;
	MOV.W	@R1,R0				;
	MOV.W	#(BIT10+BIT9),R2		;
	NOT	R2,R2				;
	AND	R2,R0				;
	OR	R3,R0				;
	OR	R4,R0				;
	MOV.W	R0,@R1				;

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
	.ALIGN	4						;
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
;;;	MOV	#1,R0
;;;	CMP/GT	R3,R6				;
;;;	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+側へｵｰﾊﾞ
;;;
;;;	MOV	#-1,R0				;
;;;	CMP/GE	R1,R6				;R1=< R6 NO
;;;	BF	POS_CLS_TYP1_NEAR_ZR_CHK_200	;(範囲内 NO)
;;;	XOR	R0,R0				;
;;;POS_CLS_TYP1_NEAR_ZR_CHK_200:			;

	MOV	#1,R0
	CMP/GT	R3,R6				;
	BT	POS_CLS_TYP1_NEAR_ZR_CHK_200	;+側へｵｰﾊﾞ

	MOV	#-1,R0				;
	CMP/GE	R1,R6				;R1=< R6 NO
	BF	POS_CLS_TYP1_NEAR_ZR_CHK_201	;(範囲内 NO)
	XOR	R0,R0				;
	M_BRA	POS_CLS_TYP1_NEAR_ZR_CHK_202	

POS_CLS_TYP1_NEAR_ZR_CHK_200:			;
	NOP
	M_BRA	POS_CLS_TYP1_NEAR_ZR_CHK_202	
POS_CLS_TYP1_NEAR_ZR_CHK_201:			;
	NOP
POS_CLS_TYP1_NEAR_ZR_CHK_202:			;

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

;	------2015-03-15
	.AIF	_KJYU_CLS EQ	_CMPILE_YES		;YES:反転ﾓｰﾄﾞで荷重でのｸﾛｰｽﾞを行う
	FAR_JSR	#_POS_CLS_START_CONF,R0			;
	FAR_JSR	#_POS_CLS_OBJPLS_PVPLS_MAKE,R0		;R7=100,R6=90 OBJ=100KN PV=90KN
	.AELSE
	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(目標位置､実測位置作成)
	.AENDI

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


;	***********************************
;	***				***
;	***	2013-04-14		***
;	***	(速度継続中のみCALL)	***
;	***				***
;	***********************************
;	位置１　停止位置２　手前にした結果　手前位置＜位置１＜位置２の場合、位置１の手前で停止する
;	ANS 	R0=1:切替必要
;	ANS	R2=X:切替行程
_REV_BEFORE_CHGKOUTEICHK:
	SUB_START
	PUSH_REG1 R5
	PUSH_REG1 R9
	PUSH_REG1 R11
	
	MOV.L	#_INT_POS_CTL_STEP,R11					;//内部制御工程1~11
	MOV.W	@R11,R9							;ﾀｲﾏLOAD
	MOV	R9,R5							;
	ADD	#-1,R5							;
	SHLL2	R5							;
	MOV	R5,R2
	SHLL	R2
	MOV.L	#_CPOS_SDAT1_CHGAPOS,R0					;
	ADD	R2,R0
	MOV.L	@R0+,R1							;位置
	MOV.L	@R0,R2							;

	XOR	R5,R5							;
	MOV.L	#_NEG_CTRL_BEFOR_OBJ_PLS,R4				;//目標－手前
	MOV.L	@R4,R6							;
	ADD	#D'1,R6						;

	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4					;
	MOV.L	@R4+,R5							;
	MOV.L	@R4,R6							;R5,R6 実測位置-->目標位置
	SUB8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;

	CMP/PZ	R1
	BF	REV_BEFORE_CHGKOUTEICK100				;"-" 過ぎた

	MOV	R1,R0
	OR	R2,R0
	TST	R0,R0
	TST_BIT_OF REV_BEFORE_CHGKOUTEICK090				;
	M_BRA	REV_BEFORE_CHGKOUTEICK300				;

REV_BEFORE_CHGKOUTEICK090:
	NOP
REV_BEFORE_CHGKOUTEICK100:
	MOV	R9,R0				;
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R2			;現状の工程の目標工程
	CMP/HS	R2,R9				;
	BT	REV_BEFORE_CHGKOUTEICK300	;すでにこの行程

REV_BEFORE_CHGKOUTEICK200:
	MOV.B	#1,R0				;ANS R2,R0
	M_BRA	REV_BEFORE_CHGKOUTEICK400

REV_BEFORE_CHGKOUTEICK300:
	XOR	R0,R0
REV_BEFORE_CHGKOUTEICK400:

	POP_REG1 R11
	POP_REG1 R9
	POP_REG1 R5

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	****		荷重－位置変換		***
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	INPUT
;	INPUT
;	OUTPUT
	.IMPORT	_SVP_ORGRUP_DEG		;原点右区間上[荷重ﾃﾞﾊﾞｯｸ]KN
	.IMPORT	_SVP_ORGRDN_DEG		;原点右区間下[荷重ﾃﾞﾊﾞｯｸ]PLS
	.IMPORT	_SVP_ORGLUP_DEG		;原点左区間上[荷重ﾃﾞﾊﾞｯｸ]KN
	.IMPORT	_SVP_ORGLDN_DEG		;原点左区間下[荷重ﾃﾞﾊﾞｯｸ]PLS



_SVPX_KTBL_MIN_KN	.DEFINE		"_SVP_ORGRUP_DEG"
_SVPX_KTBL_MIN_PLS	.DEFINE		"_SVP_ORGLUP_DEG"

_SVPX_KTBL_MAX_KN	.DEFINE		"_SVP_ORGRDN_DEG"
_SVPX_KTBL_MAX_PLS	.DEFINE		"_SVP_ORGLDN_DEG"

;	R3:Yn_1		R5:Xn_1
;	R2:Yn		R4:Xn
;	ANS:R2=y	R1:x
;	limit R6(Yn)

_CLS_KJYU_PLS_CHANGE
	SUB_START

	MOV.L	#_KJYUCLS_OBJ_KN,R1		;//その行程のターゲット
	MOV.L	@R1,R2				;
	MOV.L	#_W4_PV_CTL_KJYU_TTL_P,R1	;//制御値=ﾌｨﾙﾀ値予定
	MOV.L	@R1,R0				;荷重実測
	SUB	R0,R2				;
	MOV.L	#_KJYUCLS_KN_HENSA,R1		;//荷重の偏差
	MOV.L	R2,@R1				;

;	------KN->PLS換算は不要 KN=PLSにしてしますためコメントにする
	MOV.L	#_KJYUCLS_KN_HENSA_PLS,R1	;//荷重の偏差相当のパルス
	MOV.L	R2,@R1				;PLS="+":もっと正転していい

	SUB_END
	M_RTS




;;	FAR_JSR	#_POS_CLS_TYP1_PROC_CHK,R0				;(目標位置､実測位置作成)
;;		①この段でフルクロを行うかどうか R0=0　しない R0 != フルクロする
;;		②R6:目標停止位置[PLS],R7リニアの実測位置[PLS] 1回転上のオフセットパルス
;;
;;	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0			;ANS R0,R6(ﾘﾆｱ実測ﾊﾟﾙｽ),R7(1回転内目標ﾊﾟﾙｽ)
;;		①ニアゼロの範囲内 R0=0, ＋側へオーバR0=1,-側へオーバR0=-1
;;		 CPUBはCPUAがニアゼロならニアＺロと認識

;	*******************************************
;	***					***
;	***	ﾌﾙｸﾛｰｽﾞを行う段数かチェック	***
;	***	[ﾘﾆｱ・荷重切替]			***
;	*******************************************
;	最終段の場合はﾌﾙｸﾛｰｽﾞしない。このソフトの上で見ている
;	input INT_POS_CTL_STEP,CPOS_SDAT1_CNTSTEP
;	ANS R0:0 ﾌﾙｸﾛｰｽﾞしない
;	      :0以外 ﾌﾙｸﾛｰｽﾞする
;	ANS R5:この行程の停止行程
;[_POS_CLS_START_CONFは_POS_CLS_TYP1_PROC_CHKの一部]
;
_POS_CLS_START_CONF:
	SUB_START
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;
	MOV	R0,R5				;工程PUSH
	ADD	#-1,R0				;
	SHLL2	R0
	MOV.L	#_CPOS_SDAT1_CNTSTEP,R1		;
	MOV.L	@(R0,R1),R0			;現状の工程の目標工程
	MOV.L	#_SDATCLS_TRG_STEP,R1		;//速度連続の最後のｽﾃｯﾌﾟ
	MOV.W	R0,@R1

	CMP/EQ	R0,R5				;停止させる工程でのみﾌﾙｸﾛｰｽﾞは行う
	BT	POS_CLS_START_050		;R0=R5 ANS R5=工程,R0
	XOR	R0,R0				;ANS MAK
POS_CLS_START_050:				;

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	目標位置(ﾊﾟﾙｽ)と制御対象実測作成	***
;	***	[ﾘﾆｱ・荷重切替]				***
;	***						***
;	***************************************************
;	input _SDATCLS_TRG_STEP	;//速度連続の最後のｽﾃｯﾌﾟ
;	ANS 
;	R7:目標停止位置
;	R6:ﾘﾆｱ位置　または　荷重からの位置
;		荷重の場合は(目標荷重-実測荷重)*K+目標位置
;				(完了幅内では+1,0,-1ﾊﾟﾙｽにする)
;
;[_POS_CLS_OBJPLS_PVPLS_MAKEは_POS_CLS_TYP1_PROC_CHKの一部]
;
;
;
_POS_CLS_OBJPLS_PVPLS_MAKE
	SUB_START

	MOV.L	#_SDATCLS_TRG_STEP,R1		;//速度連続の最後のｽﾃｯﾌﾟ
	MOV.W	@R1,R0				;[R5]

	MOV.L	#_SDATCLS_UPOBJ_PLS,R5		;[目標位置=待機点]
	MOV.L	#_CPOS_STEP_MAX,R1		;//設定
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/GE	R2,R0				;MAX=NOW
	BT	POS_CLS_OBJPVPLSMAK100	;

	MOV.L	#_SDATCLS_OBJPLS,R5		;[目標位置=各段設定位置]
	ADD	#-1,R0				;
	SHLL2	R0				;4BYTE
	ADD	R0,R5				;
POS_CLS_OBJPVPLSMAK100	;

	MOV.L	@R5,R7				;待機点または目標位置(停止)
	MOV	R7,R2
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(目標ﾊﾟﾙｽ+/-ﾊﾟﾙｽ変換)
	MOV	R2,R7				;R7:目標位置;ANS:目標位置(設定ﾚﾍﾞﾙ)

	MOV.L	#_DBG_REVMOD_OBJPLS,R4		;
	MOV.L	R2,@R4				;ﾃﾞﾊﾞｯｸ用内部ﾃﾞｰﾀﾓﾆﾀ

;	==========R7:停止目標位置============
	MOV.L	#_FULCLS_MATHED,R1		;//0:位置 1:荷重
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_OBJPVPLSMAK300	;荷重 JUMP

;	=====	R6:リニア	======
	MOV.L	#_RNA_LINK_NOWROT_OFSPLS_P,R4	;//余り角度 +ﾃﾞｰﾀ
	MOV.L	@R4,R6				;
	MOV	R6,R2				;
	FAR_JSR	#_FUL_CLS_OBJPLS_CHK,R0		;USED R0~R2(ﾘﾆｱｽｹｰﾙ==>+/-ﾊﾟﾙｽ変換)
	MOV	R2,R6				;
	MOV.L	#_DBG_REVMOD_CTLPLS,R0		;
	MOV.L	R2,@R0				;
	M_BRA	POS_CLS_OBJPVPLSMAK500		;


;	=====		荷重		======
POS_CLS_OBJPVPLSMAK300:
;;	S4b	KJYUCLS_OBJ_KN;		//各段の荷重目標
;;	S4b	KJYUCLS_KN_HENSA;	//荷重の偏差
;;	S4b	KJYUCLS_KN_HENSA_PLS;	//荷重の偏差相当のパルス

	PUSH_REG1 R7				;
	FAR_JSR	#_CLS_KJYU_PLS_CHANGE,R0	;OUTPUT R2:偏差ﾊﾟﾙｽ+/-
	POP_REG1 R7				;


	TST	R2,R2				;
	TST_BIT_ON POS_CLS_OBJPVPLSMAK310	;

	MOV.B	#1,R2				;0なら1にする

POS_CLS_OBJPVPLSMAK310:				;
						;"R2=2"
	MOV	R7,R6				;OBJ=100PLS 
	SUB	R2,R6				;PV = 98PLS




POS_CLS_OBJPVPLSMAK500:

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	リニア　ニアゼロまたは荷重ニアゼロ	***
;	***						***
;	***************************************************
;	input	R6:ﾘﾆｱ位置
;	ANS	R0:-1,0,1
	.IMPORT	_SVP_KAJOBJ_HAB	;荷重完了範囲

_POS_CLS_RNA_KJYU_FIRST_NZ_CHEAK:
	SUB_START

	MOV.L	#_FULCLS_MATHED,R1		;//0:位置 1:荷重
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_RNA_KJYU_FIRST_NZ_CHK100	;

	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;目標位置とリニアスケールの論理は逆
	M_BRA	POS_CLS_RNA_KJYU_FIRST_NZ_CHKEND

POS_CLS_RNA_KJYU_FIRST_NZ_CHK100:

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;
;	-2015-06-22
	MOV.L	#(_PAR_KAJYU_FIRST-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R3							;
	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//荷重の偏差　＋：目標-実荷重:"+"まだ不足している
	MOV.L	@R1,R2			;"+/-"
	CMP/PZ	R2
	BT	POS_CLS_RNA_KJYU_FIRST_NZ_CHK120
	NEG	R2,R2					;
POS_CLS_RNA_KJYU_FIRST_NZ_CHK120			;
	CMP/HI	R3,R2					;R3<R2
	BT	POS_CLS_RNA_KJYU_FIRST_NZ_CHKEND	;
	XOR	R0,R0					;

POS_CLS_RNA_KJYU_FIRST_NZ_CHKEND:

	SUB_END
	M_RTS





_POS_CLS_RNA_KJYU_NZ_CHEAK:
	SUB_START

	MOV.L	#_FULCLS_MATHED,R1		;//0:位置 1:荷重
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK100	;

	FAR_JSR	#_POS_CLS_TYP1_NEAR_ZERO_CHEAK,R0	;目標位置とリニアスケールの論理は逆
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND

POS_CLS_RNA_KJYU_NZ_CHK100:

;	---------------------------------------------------
	.IMPORT	_SEQ_DP_TOP

	MOV.L	#_CB_SEQ_CB_COM349,R1		;[[[[[[[[[[[[
	MOV.W	@R1,R0				;
	MOV.W	#BIT12,R4			;

	TST	R4,R0				;
	TST_BIT_OF POS_CLS_RNA_KJYU_NZ_CHK500	;ﾀｲﾏ中は制御しない

	MOV.L	#_FULCLS_TIM_SETFLG,R1		;//BIT0:SET BIT1:ﾀｲﾑｱｯﾌﾟ()
	MOV.W	@R1,R0				;
	TST	#BIT1,R0
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK400	;

	TST	#BIT0,R0			;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK200	;ﾆｱｾﾞﾛに入ったか？

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;
	TST	R0,R0				;ﾆｱｾﾞﾛか?
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK490	;ﾆｱｾﾞﾛではない

	MOV.B	#BIT0,R0			;
	MOV.L	#_FULCLS_TIM_SETFLG,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_FCLS_NZ_TIM_SET,R0		;ﾀｲﾏｾｯﾄ
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHK490	;

POS_CLS_RNA_KJYU_NZ_CHK200:


	MOV.L	#_SDAT_WAIT_PVTIM,R4		;
	MOV.L	@R4,R1				;
	TST	R1,R1				;
	TST_BIT_ON POS_CLS_RNA_KJYU_NZ_CHK490	;ﾀｲﾏ中

;	--------ﾀｲﾑｱｯﾌﾟ------------
	MOV.B	#BIT1+BIT0,R0			;
	MOV.L	#_FULCLS_TIM_SETFLG,R1		;
	MOV.W	R0,@R1				;

POS_CLS_RNA_KJYU_NZ_CHK400:
	XOR	R0,R0				;完了
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND	;


POS_CLS_RNA_KJYU_NZ_CHK490:
	FAR_JSR	#_KJYU_OUT_DIRCT,R0		;ANS R0=1(戻れ)/-1(進め)　終わらない
	M_BRA	POS_CLS_RNA_KJYU_NZ_CHKEND	;


;	--------------------------------------------
POS_CLS_RNA_KJYU_NZ_CHK500:

	FAR_JSR	#_KJYU_NEARZERO_CHK,R0		;0(完了),1(戻れ),-1(進め)

POS_CLS_RNA_KJYU_NZ_CHKEND:


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	ユーザ設定荷重完了範囲との比較	***
;	***					***
;	*******************************************
_KJYU_NEARZERO_CHK:
	SUB_START

	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//荷重の偏差　＋：目標-実荷重:"+"まだ不足している
	MOV.L	@R1,R2			;"+/-"

	MOV.L	#_SVP_KAJOBJ_HAB,R1	;荷重完了範囲
	MOV.W	@R1,R3			;

	NEG	R3,R4			;-R4~+R3

	MOV.B	#-1,R0				;手前だ
	CMP/GT	R3,R2				;R3<R2
	BT	KJYU_NEARZERO_CK200		;まだ荷重が上がっていない

	XOR	R0,R0				;範囲内
	CMP/GE	R4,R2				;
	BT	KJYU_NEARZERO_CK200		;
	MOV.B	#1,R0				;
KJYU_NEARZERO_CK200:

	MOV.L	#_KJYU_CHK_NEARSIG,R1	;-1:まだ不足(進め) 1:荷重オーバ(戻れ)
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS
;	***************************************************
;	***						***
;	***	ユーザ設定荷重完了範囲-シスパラとの比較	***
;	***	[2015-03-15]				***
;	***************************************************
;;;;;;;;;;_KJYU_NEARZERO2_CHK:
;;;;;;;;;;	SUB_START
;;;;;;;;;;
;;;;;;;;;;	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//荷重の偏差　＋：目標-実荷重:"+"まだ不足している
;;;;;;;;;;	MOV.L	@R1,R2			;"+/-"
;;;;;;;;;;
;;;;;;;;;;	MOV.L	#_SVP_KAJOBJ_HAB,R1	;荷重完了範囲
;;;;;;;;;;	MOV.W	@R1,R3			;
;;;;;;;;;;
;;;;;;;;;;	MOV.L	#(_PAR_KAJYU_CHGARA-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
;;;;;;;;;;	MOV.W	@R1,R0							;
;;;;;;;;;;	SUB	R0,R3							;
;;;;;;;;;;	CMP/PL	R0							;
;;;;;;;;;;	BT	KJYU_NEARZERO2_CK100					;R0=
;;;;;;;;;;
;;;;;;;;;;	XOR	R0,R0							;荷重範囲内(設定が荷重いつでも荷重到達になる)
;;;;;;;;;;	M_BRA	KJYU_NEARZERO2_CK200					;
;;;;;;;;;;
;;;;;;;;;;KJYU_NEARZERO2_CK100							;
;;;;;;;;;;
;;;;;;;;;;	NEG	R3,R4			;-R4~+R3
;;;;;;;;;;
;;;;;;;;;;	MOV.B	#-1,R0				;手前だ
;;;;;;;;;;	CMP/GT	R3,R2				;R3<R2
;;;;;;;;;;	BT	KJYU_NEARZERO2_CK200		;まだ荷重が上がっていない
;;;;;;;;;;
;;;;;;;;;;	XOR	R0,R0				;範囲内
;;;;;;;;;;	CMP/GE	R4,R2				;
;;;;;;;;;;	BT	KJYU_NEARZERO2_CK200		;
;;;;;;;;;;	MOV.B	#1,R0				;
;;;;;;;;;;KJYU_NEARZERO2_CK200:
;;;;;;;;;;
;;;;;;;;;;
;;;;;;;;;;	SUB_END
;;;;;;;;;;	M_RTS


;;;	R0=0 範囲内
;;;	R0=1:荷重ｵｰﾊﾞ,R0=-1荷重不足
;;;	MOV.L	#_KJYU_CHK_NEARSIG,R1	;-1:まだ不足(進め) 1:荷重オーバ(戻れ)
;;;	MOV.W	R0,@R1			;


;	***************************************************
;	***						***
;	***	各種荷重範囲比較			***
;	***	2015-06-11				***
;	***************************************************
_KJYU_NEARZERO3_CHK:
	SUB_START

	MOV.L	#_KJYUCLS_KN_HENSA,R1					;//荷重の偏差　＋：目標-実荷重:"+"まだ不足している
	MOV.L	@R1,R2							;"+/-"
	CMP/PZ	R2							;
	BT	KJYU_NEARZERO3CHK_100					;
	NEG	R2,R2							;
KJYU_NEARZERO3CHK_100:

	MOV.L	#(_PAR_KAJYU_STPARA-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;[荷重停止範囲] 2015-06-22
	MOV.W	@R1,R3							;
	CMP/HS	R2,R3							;
	BT	KJYU_NEARZERO3CHK_OUT_OFF				;R2<=R3

	MOV.L	#_SVP_KAJOBJ_HAB,R1					;荷重完了範囲
	MOV.W	@R1,R4							;
	MOV	R4,R3							;

	MOV.L	#(_PAR_KAJYU_CHGARA-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;
	SUB	R0,R3							;
	CMP/PZ	R3
	BT	KJYU_NEARZERO3CHK_200					;
	MOV	R4,R3							;
KJYU_NEARZERO3CHK_200:							;
	CMP/HS	R2,R3							;R2<=R3 到達範囲?
	BT	KJYU_NEARZERO3CHK_TOUTATU				;

	CMP/HS	R2,R4							;R2<=R4 荷重ニアゼロ範囲?
	BT	KJYU_NEARZERO3CHK_YES
	MOV.B	#-2,R0							;範囲外
	M_BRA	KJYU_NEARZERO3CHK_END					;


KJYU_NEARZERO3_CK100							;
	CMP/GE	R3,R2							;
	BT	KJYU_NEARZERO3CHK_TOUTATU				;R3<=R2
	MOV.B	#-1,R0							;
	M_BRA	KJYU_NEARZERO3CHK_END					;


KJYU_NEARZERO3CHK_OUT_OFF:
	XOR	R0,R0							;一番小さい
	M_BRA	KJYU_NEARZERO3CHK_END

KJYU_NEARZERO3CHK_TOUTATU:						;
	MOV.B	#1,R0							;二番目小さい
	M_BRA	KJYU_NEARZERO3CHK_END					;

KJYU_NEARZERO3CHK_YES
	MOV.B	#2,R0							;三番目小さい

KJYU_NEARZERO3CHK_END
	SUB_END
	M_RTS



_KJYU_OUT_DIRCT:
	SUB_START

	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//荷重の偏差
	MOV.L	@R1,R0			;"+/-"

	CMP/PZ	R0
	BT	KJYU_OUTDIR100		;
	MOV.B	#1,R0			;R0=1:"+"へ行き過ぎてる 戻れ
	M_BRA	KJYU_OUTDIR200		;

KJYU_OUTDIR100:
	MOV.B	#-1,R0			;R0=-1"-"進め

KJYU_OUTDIR200:


	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	荷重制御中　タイマ中も制御し続ける 349.12
;	ニアゼロ
_FCLS_NZ_TIM_SET
	SUB_START


	MOV.L	#_INT_POS_CTL_STEP,R2	;//内部制御工程1~11
	MOV.W	@R2,R0			;ﾀｲﾏLOAD
	ADD	#-1,R0			;
	MOV.L	#_CPOS_SDAT1_TIM,R4	;
	SHLL2	R0			;
	MOV.L	@(R0,R4),R1		;TIM
	MOV.L	#_SDAT_WAIT_PVTIM,R4	;
	MOV.L	R1,@R4			;

	SUB_END
	M_RTS


_FCLS_KJYU_STEPCHG_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_FULCLS_TIM_SETFLG,R1	;
	MOV.W	R0,@R1			;
	
	MOV.L	#_FULCLS_MATHED,R1
	MOV.W	R0,@R1			;
	
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***						***
;	***						***
;	***************************************************
;	どこかで異常検出をする(仕様でないのに荷重ＳＷがＯＮだ)
	.IMPORT	_WORD_BIT_TBL1

_KJYU_DATA_INFO_SEL
	SUB_START

	MOV.L	#_SDATCLS_TRG_STEP,R1		;//速度連続の最後のｽﾃｯﾌﾟ
	MOV.W	@R1,R0				;1~10
	TST	R0,R0				;
	TST_BIT_OF KJYU_DATA_INFOSL100		;

	MOV.L	#_CPOS_STEP_MAX,R1		;//設定
	MOV.W	@R1,R2				;
	ADD	#1,R2				;
	CMP/EQ	R0,R2				;戻り行程?
	BT	KJYU_DATA_INFOSL100		;


;;;;;;;;;2017-08-15	ADD	#-1,R0				;
;;;;;;;;;2017-08-15	SHLL	R0				;
;;;;;;;;;2017-08-15	MOV.L	#_WORD_BIT_TBL1,R4		;R0=0のときにBIT0
;;;;;;;;;2017-08-15	ADD	R0,R4				;
;;;;;;;;;2017-08-15	MOV.W	@R4,R2				;ﾁｪｯｸﾋﾞｯﾄ
;;;;;;;;;2017-08-15	MOV.L	#_CPOS_FULCLS_MATEHD_SW,R1	;
;;;;;;;;;2017-08-15	MOV.W	@R1,R3				;
;;;;;;;;;2017-08-15	TST	R2,R3				;
;;;;;;;;;2017-08-15	TST_BIT_OF KJYU_DATA_INFOSL100		;位置
;;;;;;;;;2017-08-15	SHLL	R0				;*2

;	------------2017-08-15-----
	ADD	#-1,R0						;
	SHLL	R0						;
	MOV.L	#_SET1_MOT_INF,R4		;
	ADD	R0,R4						;
	MOV.W	@R4,R2					;
	MOV.W	#BIT0,R3				;
	TST	R2,R3						;
	TST_BIT_OF KJYU_DATA_INFOSL100	;位置

	SHLL	R0						;*2
	MOV.L	#_CPOS_KJYUCLS_OBJ,R1		;
	ADD	R0,R1				;
	MOV.L	@R1,R2				;
	MOV.L	#_KJYUCLS_OBJ_KN,R1		;各段の荷重目標
	MOV.L	R2,@R1				;

	MEM1_BIT0_F_ORSET MEM=_SQ_CBWK_TOP+_WKSQCB227,LG=W,BIT=(BIT13),WKRG1=R1,WKRG2=R4	;

	MOV.B	#BIT0,R0			;
	M_BRA	KJYU_DATA_INFOSL300		;

KJYU_DATA_INFOSL100
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB227,LG=W,BIT=~(BIT13),WKRG1=R1,WKRG2=R4
	XOR	R0,R0
KJYU_DATA_INFOSL300
	MOV.L	#_FULCLS_MATHED,R1		;//0:位置 1:荷重
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS






;	***************************************************
;	***						***
;	***	１回目の荷重制御開始時に荷重が高いか?	***
;	***	[2015-03-15]					***
;	***************************************************
_KAJYU_START_UPCHK:
	SUB_START
	MOV.L	#_FULCLS_MATHED,R1	;//0:位置 1:荷重
	MOV.W	@R1,R0			;
	CMP/EQ	#1,R0			;
	BF	KAJYU_START_UPCK_EXT	;荷重ではない

	MOV.L	#_FULCLS_ELSE_STS,R1	;	//BIT0=0->1:初めての荷重制御開始
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_ON KAJYU_START_UPCK_EXT	;既にチェック済み
	OR	#BIT0,R0		;
	MOV.W	R0,@R1			;

	MOV.L	#_KJYUCLS_KN_HENSA,R1	;//荷重の偏差
	MOV.L	@R1,R0			;
	CMP/PZ	R0			;
	BT	KAJYU_START_UPCK_EXT	;目標>=実測

	MEM1_BIT0_F_ORSET MEM=(_SQ_CBWK_TOP+_WKSQCB224),LG=W,BIT=(BIT12),WKRG1=R1,WKRG2=R4

KAJYU_START_UPCK_EXT:

	SUB_END
	M_RTS

;	---------起動、異常-------
	.EXPORT	_KAJYU_ELSE_STS_CLR
_KAJYU_ELSE_STS_CLR:
	SUB_START

	FAR_JSR	#_KAJYU_ELSE_STS_FLG_CLR,R0	;

	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB224),LG=W,BIT=~(BIT12),WKRG1=R1,WKRG2=R4

	SUB_END
	M_RTS

_KAJYU_ELSE_STS_FLG_CLR:
	SUB_START
	XOR	R0,R0
	MOV.L	#_FULCLS_ELSE_STS,R1	;	//BIT0=0->1:初めての荷重制御開始
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS


















;	H2WではDTMKだがＱ
;	***************************************************
;	***						***
;	***		起動時荷重データ判断		***
;	***						***
;	***		範囲1				***
;	***		範囲2				***
;	***************************************************
;	"既に荷重範囲に一度は入った前提"
;

_REVRSE_KAJYU_AREACHK_BASSET:
	SUB_START
	MOV.L	#(_PAR_KAJYU_CHGARA-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;到達範囲
	TST	R0,R0							;
	TST_BIT_OF REVRSE_KAJYU_AREACK_LASTSPD				;最終範囲を使用しない

;;;;;2015-06-22
;;;;;	FAR_JSR	#_KJYU_NEARZERO2_CHK,R0
;;;;;	TST	R0,R0					;
;;;;;	TST_BIT_OF REVRSE_KAJYU_AREACK_LASTSPD		;到達範囲内

;	速度選択のニアゼロサブルーチン変更
	FAR_JSR	#_KJYU_NEARZERO3_CHK,R0
	CMP/EQ	#0,R0
	BT	REVRSE_KAJYU_AREACK_LASTSPD		;到達範囲内 0,1
	CMP/EQ	#1,R0
	BT	REVRSE_KAJYU_AREACK_LASTSPD		;到達範囲内 0,1

	FAR_JSR	#_REVRSE_KAJYU1_BASINCSET,R0		;
	M_BRA	REVRSE_KAJYU_AREACK_END			;

;	--------------最後の範囲内の運転--------------
REVRSE_KAJYU_AREACK_LASTSPD:	
	FAR_JSR	#_REVRSE_KAJYU2_BASINCSET,R0

REVRSE_KAJYU_AREACK_END:

	SUB_END
	M_RTS




;もしﾊﾟ-ｾﾝﾃﾞｰﾀなら
;DATA(%)*MAX(freq)/10000=freq
;freq*FFFF/500,000=LATE
;
;
;もしﾚｰﾄ(7pls/s)なら
;DATA()*500,000/FFFF=PLS/S

;	------ 2014-08-20-------------------------------------------------------------
;	---------------- 荷重制御の一旦荷重幅に入った＋最終幅に入っていない-----------
_REVRSE_KAJYU1_BASINCSET:
	SUB_START

	MOV.L	#(_PAR_KAJYU_ARASPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;Pno.362
	MOV.W	@R1,R2							;[7PLS/S]
	TST	R2,R2							;
	TST_BIT_ON CLSINC1_SEL_020					;

	FAR_JSR	#_REVRSE_BASINC_SPDCALC,R0				;
	M_BRA	CLSINC1_SEL_END						;

CLSINC1_SEL_020
	FAR_JSR	#_CHG_LSI_LATE_TO_PLS,R0				;R2*POS_FRQ_SPDMAX(500000)/POS_LSI_SPDMAX(FFFF)

	MOV.L	#_SET_CLSINC_SPDBAS_PLS,R1				;
	MOV.L	R2,@R1							;
CLSINC1_SEL_END

	SUB_END
	M_RTS


;	-------2014-07-14-----------
;	------ 2014-08-20-----------
;	---------------- 荷重制御の一旦荷重幅に入った＋最終幅に入った-----------
_REVRSE_KAJYU2_BASINCSET:
	SUB_START

	MOV.L	#(_PAR_KAJYU_HLDSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;Pno.361
	MOV.W	@R1,R2							;[7PLS/S]
	TST	R2,R2							;
	TST_BIT_ON CLSINC2_SEL_020					;

	FAR_JSR	#_REVRSE_BASINC_SPDCALC,R0				;
	M_BRA	CLSINC2_SEL_END						;

CLSINC2_SEL_020
	FAR_JSR	#_CHG_LSI_LATE_TO_PLS,R0				;R2*POS_FRQ_SPDMAX(500000)/POS_LSI_SPDMAX(FFFF)

	MOV.L	#_SET_CLSINC_SPDBAS_PLS,R1				;
	MOV.L	R2,@R1							;
CLSINC2_SEL_END

	SUB_END
	M_RTS


;	***********************************
;	***	S01~S09処理		***
;	***********************************
_REVRSE_BASINC_SPDCALC:
	SUB_START

;	=======  2012-10-05 =========
	MOV.L	#_CB_SEQ_CB_COM351,R1					;ｲﾝﾁﾝｸﾞ速度選択
	MOV.W	@R1,R0							;
	MOV.W	#BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1,R4	;
	TST	R4,R0							;
	TST_BIT_OF CLSINC_SEL_DEF					;

	MOV.B	#D'9-1,R3							;
	MOV.B	#BIT1,R4						;
	MOV.L	#(_PAR_NEGCTL_SPDS1-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;

CLSINC_SEL_050LOP:
	TST	R4,R0
	TST_BIT_ON CLSINC_SEL_100	;
	SHLL	R4
	ADD	#2,R1			;
	ADD	#-1,R3			;
	TST	R3,R3			;
	TST_BIT_ON CLSINC_SEL_050LOP	;BIT1~BIT8
CLSINC_SEL_100:
	MOV.W	@R1,R2			;
	TST	R2,R2			;
	TST_BIT_ON CLSINC_SEL_300	;
	ADD	#1,R2			;
	M_BRA	CLSINC_SEL_300		;


CLSINC_SEL_DEF:
	MOV.L	#_POS_LSI_CLSINC_SPDBAS,R1		;ｲﾝﾁﾝｸﾞ時
	MOV.L	@R1,R2
CLSINC_SEL_300
	FAR_JSR	#_CHG_LSI_LATE_TO_PLS,R0		;
	MOV.L	#_SET_CLSINC_SPDBAS_PLS,R1		;//PLS/S
	MOV.L	R2,@R1					;
							;

	SUB_END
	M_RTS

;-----------2019-04-10(戻り信号のラッチ:異常時の処理チェック用)---------
;;;_HANTEN_LAST_SIG_CLR
;;;	SUB_START
;;;	XOR		R0,R0
;;;	MOV.L	#_HANTEN_LAST_STEP_F,R1	;
;;;	MOV.W	R0,@R1					;
;;;	SUB_END
;;;	M_RTS
;;;
;;;_HANTEN_LAST_SIG_SET
;;;	SUB_START
;;;	MOV.L	#_HANTEN_LAST_STEP_F,R1	;
;;;	MOV.W	@R1,R0					;
;;;	OR		#BIT0,R0				;
;;;	MOV.W	R0,@R1					;
;;;	SUB_END
;;;	M_RTS
