;	***********************************
;	***	cpubに不要なｿﾌﾄ		***
;	***********************************
	.IMPORT	_ACCB_ACCLAT_TIM1

;	***************************************************
;	***						***
;	***	2011-03-22				***
;	***	異常比較関係ｽﾗｲﾄﾞ動作 停止ﾁｪｯｸ		***
;	***						***
;	***************************************************
_SLID_ALM_ELSE_CHK:
	SUB_START

	FAR_JSR	#_SLID_ALM_CHK,R0		;
	FAR_JSR	#_ORIGIN_POS_HAB_CHK,R0	;
	
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	2011-03-22				***
;	***	ｽﾗｲﾄﾞ動作 停止ﾁｪｯｸ			***
;	***						***
;	***************************************************
_SLID_ALM_CHK:
	SUB_START
	MOV.L	#_CB_SEQ_CB_SEL342,R1		;342
	MOV.W	@R1,R0				;
	MOV.W	#(BIT7+BIT6),R4			;
	AND	R4,R0				;
	TST	R0,R0				;
	TST_BIT_ON SLID_ALMCHK_100		;

	MOV.L	#_SLIDALM_CHK_FLG,R1		;
	MOV.W	R0,@R1				;
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB229,LG=W,BIT=~(BIT8),WKRG1=R1,WKRG2=R4
	M_BRA	SLID_ALMCHK_900			;


SLID_ALMCHK_100:
	AND	R4,R0				;BIT7orBIT6=on
	MOV.L	#_SLIDALM_CHK_FLG,R1		;
	MOV.W	@R1,R2				;
	MOV.W	R0,@R1				;

	XOR	R0,R2				;New xor old
	AND	R2,R0				;ON EDGE(新たなONｴｯｼﾞ)=R0
	TST	R0,R0				;
	TST_BIT_OF SLID_ALMCHK_200		;

;	----- START-----------
	MOV.L	#_RNA_ABS_POS,R1		;//ﾎﾞﾙｽﾀ面高さ
	MOV.L	@R1,R2				;
	MOV.L	#_SLIDALM_POS_PULAS,R1		;//最大位置
	MOV.L	R2,@R1				;
	MOV.L	#_SLIDALM_POS_MINAS,R1		;//最小位置
	MOV.L	R2,@R1				;
	MOV.L	#_SLIDALM_CHK_POS,R1		;//計測時間後の位置
	MOV.L	R2,@R1				;

	MOV.L	#_WPAR_SLDALM_TIM,R1		;//ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動測定時間2011-03-22[ｸﾗﾝｸ機構MC　H1F]
	MOV.W	@R1,R0				;
	ADD	#1,R0				;+1
	MOV.L	#_SLIDALM_CHK_TIM,R4		;//計測時間
	MOV.W	R0,@R4				;

SLID_ALMCHK_200:
;	---------- MAX/MIN REFLASEH-----
	MOV.L	#_RNA_ABS_POS,R1		;//ﾎﾞﾙｽﾀ面高さ
	MOV.L	@R1,R2				;

	MOV.L	#_SLIDALM_POS_PULAS,R1		;//最大位置
	MOV.L	@R1,R5				;
	CMP/GE	R2,R5				;data =< MAX
	BT	SLID_ALMCHK_300			;THEN JUMP
	MOV.L	R2,@R1				;REFLASH
SLID_ALMCHK_300:

	MOV.L	#_SLIDALM_POS_MINAS,R1		;//最小位置
	MOV.L	@R1,R6
	CMP/GE	R6,R2				;				;
	BT	SLID_ALMCHK_400			;MIN =< DataTHEN JUMP
	MOV.L	R2,@R1				;REFLASH
SLID_ALMCHK_400:

	MOV.L	#_SLIDALM_CHK_TIM,R4		;//計測時間
	MOV.W	@R4,R0				;
	ADD	#-1	,R0			;
	MOV.W	R0,@R4				;
	TST	R0,R0				;
	TST_BIT_ON SLID_ALMCHK_900		;

	MOV.L	#_WPAR_SLDALM_TIM,R1		;//ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動測定時間2011-03-22[ｸﾗﾝｸ機構MC　H1F]
	MOV.W	@R1,R0				;
	ADD	#1,R0				;+1してｾｯﾄする
	MOV.W	R0,@R4				;


	MOV.L	#_SLIDALM_CHK_FLG,R1		;342.6/7相当
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;上昇?増加
	TST_BIT_ON SLID_ALMCHK_500		;YES(R5=上昇ﾃﾞｰﾀ)

	MOV	R6,R5				;

SLID_ALMCHK_500:

	MOV.L	#_SLIDALM_CHK_POS,R1		;//最上昇値または最下降値
	MOV.L	@R1,R2				;
	MOV.L	R5,@R1				;
	SUB	R5,R2				;
	CMP/PZ	R2				;
	BT	SLID_ALMCHK_550			;
	NEG	R2,R2				;
SLID_ALMCHK_550:

	MOV.L	#_WPAR_SLDALM_LNG,R1		;//ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動量 2011-03-22[ｸﾗﾝｸ機構MC　H1F]
	MOV.W	@R1,R3				;
	TST	R3,R3				;
	TST_BIT_OF SLID_ALMCHK_900		;

	CMP/HS	R3,R2									;
	BT	SLID_ALMCHK_600								;R3=< R2 OK[動作した]
	MEM1_BIT0_F_ORSET MEM=_SQ_CBWK_TOP+_WKSQCB229,LG=W,BIT=BIT8,WKRG1=R1,WKRG2=R4	;
	M_BRA	SLID_ALMCHK_900								;

SLID_ALMCHK_600:
;;;不要	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB229,LG=W,BIT=~(BIT8),WKRG1=R1,WKRG2=R4

SLID_ALMCHK_900:
	SUB_END
	M_RTS









;	*******************************************
;	***					***
;	***					***
;	***					***
;	***	リニアタッチ金型位置算出演算	***
;	***	2011-08-01			***
;	***					***
;	*******************************************
	.IMPORT	_PV_LINK_DG_CHG_CLNK_DG1	;
	.IMPORT	_LINK_PLS_CHG_LINK_DIG		;
	.IMPORT	_SV_CLNK_DG_CHG_LINK_DG1	;ｸﾗﾝｸ(表示)→ﾘﾝｸ(360)
;;	.IMPORT	_SVP_OBJECT_DIG_TOP		;

;;	.IMPORT	_PAR_TECH2_KN1			;3 0:演算は行わない +100knを超えた位置を記憶
;;	.IMPORT	_PAR_TECH2_KN2			;4                  +200knを超えた位置を記憶
;;	.IMPORT	_PAR_TECH2_OFSPLS		;5 -10PLS 演算結果から10ﾊﾟﾙｽ引き算する


	.IMPORT	_DIG36000_CHG_RENEA1			;かなり重い演算

;[1]power-on
;	RNA_INSERT_CHKFLG.BT6=0
;			  BT0=0
;	①開始範囲角度になったbit0=1
;	  call PLS_KJYU_INSERT_CHK
;	       TECH2_KN_FLG.BT0=1:荷重ﾎﾟｲﾝﾄ1を見つけた
;	       TECH2_KN_FLG.BT6=1:荷重ﾎﾟｲﾝﾄ2を見つけた
;	       PVX_MOTINS_AGL:ﾀｯﾁ角度だけを検出->演算しろTECH_USED_F=1
;	       RNA_INSERT_CHKFLG.BT1=1
;	       RNA_INSERT_CHKFLG.BT6=1
;	②終了角度を過ぎた
;	      FAR_JSR	#_INSERT_MOTION_PV_MOV,R0						;
;	       RNA_INSERT_CHKFLG.BT4=1
;	       RNA_INSERT_CHKFLG.BT6=1

_TEACH_BUF_MAX	.EQU	100

	.ALIGN	4				;
_INSERT_TEACH_POS
	SUB_START

;	------ 2012-10-18 新方式----------
;;;;;;2013-02-20[旧]	MOV.L	#(_PAR_TECH2_KN1-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
;;;;;;2013-02-20[旧]	MOV.W	@R1,R0							;
;;;;;;2013-02-20[旧]	TST	R0,R0							;
;;;;;;2013-02-20[旧]	TST_BIT_ON INSERT_TCH_POS050					;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	------- 過去データがほしいから無条件演算----------
;;;;;;2013-02-20[旧]	FAR_JSR	#_TECT_DATA_MAKE,R0					;[荷重ﾃﾞｰﾀ,角度ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ]
;;;;;;2013-02-20[旧]	FAR_JSR	#_KAJYU_BIBUN_DATA_MAKE,R0				;2012-09-25 荷重加速度からのタッチ位置算出
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]INSERT_TCH_POS050




	MOV.L	#_RNA_INSERT_CHKFLG,R1		;	//BIT0	起動
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF INSERT_TCH_POS100		;未完了JUMP



;	----工程１になることを待つ------
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	INSERT_TCH_POS099

	MOV.L	#_RNA_OLD_STEP,R1		;
	MOV.W	@R1,R2				;
	CMP/EQ	R2,R0				;
	BT	INSERT_TCH_POS099		;ずっと１工程

;	--------------------------
	MOV.L	#_SETX_POS_CTL_MATH,R1		;
	MOV.W	@R1,R0				;
	TST	#_DMATH_CNTROT,R0		;回転?
	TST_BIT_ON INSERT_TCH_POS050		;OK

	TST	#_DMATH_DNDRIV,R0		;ふりこ?
	TST_BIT_OF INSERT_TCH_POS099		;NO 反転EXIT

	MOV.L	#_DNM_DIR_NOW_FLG,R1		;//
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON INSERT_TCH_POS099		;復路




INSERT_TCH_POS050
	XOR	R0,R0				;
	MOV.L	#_RNA_INSERT_CHKFLG,R1		;BIT0	起動
	MOV.W	R0,@R1				;

						;2012-10-18 ADD
	MOV.L	#_TECH2_KN_FLG,R1		;//BIT0(FIRST),BIT1(SECOND),BIT6(END)
	MOV.W	R0,@R1				;

INSERT_TCH_POS099
	M_BRA	INSERT_TCH_POS900		;

;	----------開始範囲チェック----------------
INSERT_TCH_POS100
	TST	#BIT0,R0			;
	TST_BIT_ON INSERT_TCH_POS200		;START

;	-----------[回転だけ 一応回転,ふりこ,反転でOK]----
;;;	MOV.L	#_SET1_KJSTR_DIG1,R4				;
	MOV.L	#_SET1_KATTCH_SAG,R4				;2014-05-30
	MOV.W	@R4,R1						;

	MOV.L	#_DNM_CTL_INC3600,R4				;2012-10-17
	MOV.W	@R4,R2						;

;;;	MOV.L	#_SET1_KJEND_DIG1,R4				;
	MOV.L	#_SET1_KATTCH_EAG,R4				;2014-05-30
	MOV.W	@R4,R3						;

	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0	;
	CMP/EQ	#1,R0						;
	BF	INSERT_TCH_POS150
	MEM1_BIT0_TO_BIT7_ORSET MEM=_RNA_INSERT_CHKFLG,LG=W,BIT=(BIT0),WKREG=R1	
INSERT_TCH_POS150
	M_BRA	INSERT_TCH_POS900

;	----------データアップチェック----------------
INSERT_TCH_POS200:

;;;;;;2013-02-20[旧];	-----------2012-09-25 _RNA_BBN_MEUSRE_ACCは荷重加速度が入る----------
;;;;;;2013-02-20[旧];	---------------_SETX_RNA_ACC_CHKPOSは荷重の加速度閾値が入る---------
;;;;;;2013-02-20[旧];	------ 2012-10-18 新方式----------
;;;;;;2013-02-20[旧]	MOV.L	#(_PAR_TECH2_KN1-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
;;;;;;2013-02-20[旧]	MOV.W	@R1,R0							;
;;;;;;2013-02-20[旧]	TST	R0,R0							;
;;;;;;2013-02-20[旧]	TST_BIT_OF INSERT_TCH_POS250					;

;	------ 2012-10-18 新方式----------
	FAR_JSR	#_PLS_KJYU_INSERT_CHK,R0			;
	TST	R0,R0						;
	TST_BIT_OF INSERT_TCH_POS300				;条件未成立

;;;;;;2013-02-20[旧]	M_BRA	INSERT_TCH_POS280				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	---------------------------------------
;;;;;;2013-02-20[旧]INSERT_TCH_POS250:
;;;;;;2013-02-20[旧]	FAR_JSR	#_KAJYUU_INSRET_CHK,R0		;[荷重条件での完了～計算まで]
;;;;;;2013-02-20[旧]	TST	R0,R0				;
;;;;;;2013-02-20[旧]	TST_BIT_OF INSERT_TCH_POS300		;条件未成立
;;;;;;2013-02-20[旧]INSERT_TCH_POS280:

;;;;;;2013-03-10	FAR_JSR	#_INSERT_MOTION_PV_MOV,R0

	MEM1_BIT0_TO_BIT7_ORSET MEM=_RNA_INSERT_CHKFLG,LG=W,BIT=(BIT6+BIT1),WKREG=R1	;見つけた
	M_BRA	INSERT_TCH_POS900




INSERT_TCH_POS300
;	-----------[回転/ふりこ]----
;;;	MOV.L	#_SET1_KJSTR_DIG1,R4			;
	MOV.L	#_SET1_KATTCH_SAG,R4			;2014-05-30
	MOV.W	@R4,R1								;

	MOV.L	#_DNM_CTL_INC3600,R4						;2012-10-17
	MOV.W	@R4,R2								;
;;;	MOV.L	#_SET1_KJEND_DIG1,R4						;
	MOV.L	#_SET1_KATTCH_EAG,R4				;2014-05-30
	MOV.W	@R4,R3								;

	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BT	INSERT_TCH_POS350

;	---------- 見つからずに範囲からでた-------------------
;;;;;;	XOR	R3,R3									;
;;;;;;	MOV.L	#_PVX_MOTINS_DAN,R1							;前のﾃﾞｰﾀをｸﾘｱできていない
;;;;;;	MOV.W	R3,@R1									;
;;;;;;	FAR_JSR	#_INSERT_MOTION_PV_MOV,R0						;

	FAR_JSR	#_INSERT_MOTION_DISENB,R0						;2015-05-20
	MEM1_BIT0_TO_BIT7_ORSET MEM=_RNA_INSERT_CHKFLG,LG=W,BIT=(BIT6+BIT4),WKREG=R1	;見つけれなかった

INSERT_TCH_POS350
	M_BRA	INSERT_TCH_POS900


INSERT_TCH_POS900
	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
	MOV.W	@R1,R0				;
	MOV.L	#_RNA_OLD_STEP,R1		;
	MOV.W	R0,@R1				;


;;;2012-05-15
;;;;	MOV.L	#_RNA_INSERT_CHKFLG,R1		;
;;;;	MOV.W	@R1,R2				;
;;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB231,R1	;
;;;;	MOV.W	R2,@R1				;

	MOV.L	#_RNA_INSERT_CHKFLG,R1		;
	MOV.W	@R1,R0				;
	EXTU.B	R0,R0				;
	MOV.L	#_TECH2_KN_FLG,R1		;
	MOV.W	@R1,R2				;
	EXTU.B	R2,R2				;
	SHLL8	R2				;
	OR	R2,R0				;

	MOV.L	#_TECH_USED_F,R1		;演算ｲﾍﾞﾝﾄｸﾘｱ
	MOV.W	@R1,R2				;
	TST	R2,R2				;
	TST_BIT_OF INSERT_TCH_POS920		;
	MOV.W	#BIT15,R2			;
	OR	R2,R0				;
INSERT_TCH_POS920
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB257,R1	;BIT0,BIT1,BIT4:BIT6:RNA_INSERT_CHKFLG
	MOV.W	R0,@R1				;BIT0[START]*0x100,BIT6[END]*0x100:TECH2_KN_FLG
						;BIT15:TECH_USED_F

	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	荷重での比較条件		***
;	***	2012-10-17			***
;	*******************************************
;;;;;;2013-02-20[旧]	.ALIGN	4				;
;;;;;;2013-02-20[旧]_KAJYUU_INSRET_CHK:
;;;;;;2013-02-20[旧]	SUB_START
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MEUSRE_ACC,R5				;
;;;;;;2013-02-20[旧]	MOV.L	@R5,R2						;0.01mm/s 1000.00mm/s
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_SETX_RNA_ACC_CHKPOS,R1	;
;;;;;;2013-02-20[旧]	MOV.L	@R1,R3				;
;;;;;;2013-02-20[旧]	CMP/GE	R3,R2				;符号付で加速したら
;;;;;;2013-02-20[旧]	BF	KJINSERT_TCHPOS300		;まだ加速してない　jump
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	---------- 加速条件成立--------------
;;;;;;2013-02-20[旧]	MOV.L	#_SETX_RNA_ACC_BEFTIM,R0	;
;;;;;;2013-02-20[旧]	MOV.W	@R0,R1				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.W	#_TEACH_BUF_MAX,R4		;
;;;;;;2013-02-20[旧]	CMP/HI	R1,R4				;
;;;;;;2013-02-20[旧]	BT	KJINSERT_TCHPOS270		;R7=<99
;;;;;;2013-02-20[旧]	XOR	R1,R1				;100より大きいなら0
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]KJINSERT_TCHPOS270
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_TECH_POINT,R5		;
;;;;;;2013-02-20[旧]	MOV.W	@R5,R0				;これからSAVEする値
;;;;;;2013-02-20[旧]	ADD	#-1,R0				;
;;;;;;2013-02-20[旧]	SUB	R1,R0				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	CMP/PZ	R0
;;;;;;2013-02-20[旧]	BT	KJINSERT_TCHPOS280		;
;;;;;;2013-02-20[旧]	ADD	R4,R0				;
;;;;;;2013-02-20[旧]KJINSERT_TCHPOS280
;;;;;;2013-02-20[旧]	SHLL2	R0				;
;;;;;;2013-02-20[旧]	SHLL2	R0				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_TECH_POSBUF,R6		;
;;;;;;2013-02-20[旧]	ADD	R0,R6				;
;;;;;;2013-02-20[旧]	MOV.L	@R6+,R2				;0.001mm[内部]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_PVX_MOTINS_POS,R1		;
;;;;;;2013-02-20[旧]	MOV.L	R2,@R1				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	@R6+,R3				;STEP
;;;;;;2013-02-20[旧]	MOV.L	#_PVX_MOTINS_DAN,R1		;
;;;;;;2013-02-20[旧]	MOV.W	R3,@R1				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	@R6,R2				;inc
;;;;;;2013-02-20[旧]	MOV.L	#_PVX_MOTINS_AGL,R1		;
;;;;;;2013-02-20[旧]	MOV.W	R2,@R1				;
;;;;;;2013-02-20[旧]	MOV.L	#_TECH_WK_DIG1,R1		;
;;;;;;2013-02-20[旧]	MOV.W	R2,@R1				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	FAR_JSR	#_TECH_DAN_DIG_RECALC,R0	;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.B	#-1,R0				;END
;;;;;;2013-02-20[旧]	M_BRA	KJINSERT_TCHPOS900		;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]KJINSERT_TCHPOS300:
;;;;;;2013-02-20[旧]	XOR	R0,R0
;;;;;;2013-02-20[旧]KJINSERT_TCHPOS900:
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	SUB_END
;;;;;;2013-02-20[旧]	M_RTS

;	*******************************************
;	***					***
;	***	PLS-荷重での比較条件		***
;	***	2012-10-18			***
;	*******************************************
	.ALIGN	4				;
_PLS_KJYU_INSERT_CHK:
	SUB_START

	MOV.L	#_PVPAB_KAJLIV_TTL,R1		;//荷重生（TON）(1word)
	MOV.L	@R1,R2				;
	MOV.L	#_RNA_BBN_MESURE_SSPD,R1	;MONI[生荷重]->ﾃﾞﾊﾞｸ表示用[ﾄﾚﾝﾄﾞtype7]
	MOV.L	R2,@R1				;

	MOV.L	#_TECH2_KN_FLG,R1		;//BIT0(FIRST),BIT6(END)
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_OF PLS_KJYU_INSERTCK_100	;
	M_BRA	PLS_KJYU_INSERTCK_800		;bit6=1

PLS_KJYU_INSERTCK_100:
	TST	#BIT0,R0			;
	TST_BIT_ON PLS_KJYU_INSERTCK_300	;

	MOV.L	#(_PAR_TECH2_KN1-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R3							;
	EXTU.W	R3,R3							;[[[[[[[[[[XOR R3,R3]]]]]]]]]
	CMP/GE	R3,R2							;SV=<PV?
	BF	PLS_KJYU_INSERTCK_700					;NO

	MOV.L	#_TECH2_KJYU_LT1KN,R1					;//FIRST  KN
	MOV.L	R2,@R1							;

	MOV.L	#_LINK_PV_ABSPLS,R0					;
	MOV.L	@R0+,R5							;
	MOV.L	@R0,R6							;(制御目標値/今は実測だけど)

	MOV.L	#_TECH2_KJYU_LT1PLS,R0
	MOV.L	R5,@R0							;
	MOV.L	R6,@(4,R0)						;

	MOV.L	#_INC_LINK_NOWROT_OFSPLS_P,R0				;[[[実測 1REV PLS]]]
	MOV.L	@R0,R4							;
	MOV.L	#_TECH2_KJYU_LT1PLS_OFS,R0					;
	MOV.L	R4,@R0							;

;;;;;2013-02-20		MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
;;;;;2013-02-20		MOV.W	@R1,R3				;
;;;;;2013-02-20		MOV.L	#_PVX_MOTINS_DAN,R1		;
;;;;;2013-02-20		MOV.W	R3,@R1				;[発生した段数]

	MEM1_BIT0_TO_BIT7_ORSET MEM=_TECH2_KN_FLG,LG=W,BIT=(BIT0),WKREG=R1	;


PLS_KJYU_INSERTCK_300:
	MOV.L	#(_PAR_TECH2_KN2-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;
	MOV.W	@R1,R3								;
	EXTU.W	R3,R3								;[[[[[[[[[[XOR R3,R3]]]]]]]]]
	CMP/GE	R3,R2								;SV=<PV?
	BF	PLS_KJYU_INSERTCK_700						;NO

	MOV.L	#_TECH2_KJYU_LT2KN,R1			;//SECOND  KN
	MOV.L	R2,@R1					;

	MOV.L	#_LINK_PV_ABSPLS,R0			;
	MOV.L	@R0+,R5					;
	MOV.L	@R0,R6					;(制御目標値/今は実測だけど)

	MOV.L	#_TECH2_KJYU_LT2PLS,R0
	MOV.L	R5,@R0					;
	MOV.L	R6,@(4,R0)				;

	MOV.L	#_INC_LINK_NOWROT_OFSPLS_P,R0		;[[[実測 1REV PLS]]]
	MOV.L	@R0,R4					;
	MOV.L	#_TECH2_KJYU_LT2PLS_OFS,R0		;
	MOV.L	R4,@R0					;

	FAR_JSR	#_PLS_KJYUU_TECHCALC,R0			;ﾀｯﾁ角度 PVX_MOTINS_AGL,

	MEM1_BIT0_TO_BIT7_ORSET MEM=_TECH_USED_F,LG=W,BIT=(BIT0),WKREG=R1	;


;;;;;;2013-03-10	FAR_JSR	#_TECH_DAN_DIG_RECALC,R0		;ﾀｯﾁ角度から挿入ﾃﾞｰﾀを算出

	MEM1_BIT0_TO_BIT7_ORSET MEM=_TECH2_KN_FLG,LG=W,BIT=(BIT6),WKREG=R1	;
	M_BRA	PLS_KJYU_INSERTCK_800


PLS_KJYU_INSERTCK_700:
	XOR	R0,R0
	M_BRA	PLS_KJYU_INSERTCK_900
;	-------------終了----
PLS_KJYU_INSERTCK_800:
	MOV.B	#-1,R0
PLS_KJYU_INSERTCK_900:
	
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	PLS-荷重からタッチ位置を演算	***
;	***	2012-10-18			***
;	*******************************************
;	PLSから角度を求める
;	
;	L=P2-P1
;	K=K2-K1
;	L/K * K1= L1
;
	.ALIGN	4				;
_PLS_KJYUU_TECHCALC:
	SUB_START

	MOV.L	#_TECH2_KJYU_LT2PLS,R0					;
	MOV.L	@R0,R1							;
	MOV.L	@(4,R0),R2						;

	MOV.L	#_TECH2_KJYU_LT1PLS,R0					;
	MOV.L	@R0,R3							;
	MOV.L	@(4,R0),R4						;

	SUB8B DT_REGH=R3,DT_REGL=R4,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2(相手-自分)
	TST	R1,R1							;
	TST_BIT_OF PLS_KJYUU_TCHCAL100					;8BYTEはありえない,ﾏｲﾅｽもない
	XOR	R1,R1							;
	MOV.B	#1,R2							;
PLS_KJYUU_TCHCAL100:							;

	MOV.L	#_TECH2_KJYU_LT2KN,R0					;//SECOND  KN
	MOV.L	@R0,R4							;

	MOV.L	#_TECH2_KJYU_LT1KN,R0					;//SECOND  KN
	MOV.L	@R0,R1							;
	SUB	R1,R4							;

	CMP/PL	R4
	BT	PLS_KJYUU_TCHCAL200					;
	MOV.B	#1,R4							;
PLS_KJYUU_TCHCAL200:							;

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;ｼﾌﾄ距離 "+"
	NEG	R2,R2						;

	MOV.L	#(_PAR_TECH2_OFSPLS-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;
	MOV.W	@R1,R0								;
	ADD	R0,R2

	MOV.L	#_TECH2_KJYU_LNG,R1					;//演算ｼﾌﾄ+ｼｽﾊﾟﾗｽﾌﾄ
	MOV.L	R2,@R1							;"-"data


	MOV.L	#_LINK_1ROT_PLS,R1					;
	MOV.L	@R1,R4							;

	MOV.L	#_TECH2_KJYU_LT1PLS_OFS,R1				;
	MOV.L	@R1,R3							;
	ADD	R2,R3							;+/-
	CMP/PZ	R3							;
	BT	PLS_KJYUU_TCHCAL300					;

	ADD	R4,R3							;

PLS_KJYUU_TCHCAL300:							;
	CMP/HS	R3,R4							;
	BT	PLS_KJYUU_TCHCAL400					;
	MOV	R4,R3							;
PLS_KJYUU_TCHCAL400:							;
	MOV.L	#_TECH2_KJYU_PLS,R1					;//ﾀｯﾁ位置-ｼﾌﾄ
	MOV.L	R3,@R1							;

	MOV	R3,R2						;

	FAR_JSR	#_LINK_PLS_CHG_LINK_DIG,R0			;


	MOV.L	#_TECH2_KJYU_DIG,R1				;//0.1度
	MOV.W	R2,@R1						;

	MOV.L	#_PVX_MOTINS_AGL,R1				;
	MOV.W	R2,@R1						;ﾀｯﾁ角度


	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	演算を独立させる		***
;	***	2013-03-10				***
;	*******************************************
;	MAIN ｽｷｬﾝ

	.EXPORT	_TECH_DAN_DIG_MAKE
	
_TECH_DAN_DIG_MAKE:
	SUB_START
;;;	
;;;	MOV.L	#_SETX_POS_CTL_MATH,R1		;
;;;	MOV.W	@R1,R0				;
;;;	TST	#_DMATH_REVRSE,R0		;反転
;;;	TST_BIT_ON TECH_DAN_DIGMK_EXT		;YES EXIT

	MOV.L	#_TECH_USED_F,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF TECH_DAN_DIGMK_EXT		;ﾃﾞｰﾀは存在する? NO

	FAR_JSR	#_TECH_DAN_DIG_RECALC,R0	;ﾀｯﾁ角度から挿入ﾃﾞｰﾀを算出

	FAR_JSR	#_INSERT_MOTION_PV_MOV,R0	;

TECH_DAN_DIGMK_EXT:
	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	荷重及びパルスでの挿入演算	***
;	***					***
;	***	2012-10-17			***
;	***					***
;	*******************************************
;	Input
;	MOV.L	#_PVX_MOTINS_DAN,R1		;段数
;	MOV.L	#_PVX_MOTINS_AGL,R1		;角度
;	
;	Outut
;	MOV.L	#_PVX_MOTINS_DAN,R1		;段数 WORD
;	MOV.L	#_PVX_MOTINS_AGL,R1		;角度 WORD
;	MOV.L	#_PVX_MOTINS_POS,R1		;LONG
;
;	引いた結果が前の段に変わるなら、前の段と同じ値にする.
;	段は変えない
;
;

	.ALIGN	4				;
_TECH_DAN_DIG_RECALC:
	SUB_START
;	--------金型ﾀｯﾁ角度挿入段数,挿入ﾃﾞｰﾀ-[現ﾃﾞｰﾀに対しての段数]---
	MOV.L	#_PVX_MOTINS_AGL,R1				;ﾀｯﾁ角度・ﾘﾝｸ
	MOV.W	@R1,R2						;
	MOV.L	#_PVX_MOTINS_AGLX,R5				;ｸﾗﾝｸ角度
	MOV.L	#_PVX_MOTINS_POS,R6				;ﾘﾆｱmm
	FAR_JSR	#_PVDIG_TO_CLANK_RNA_MAK,R0			;ﾀｯﾁ角度・ﾘﾝｸ->ｸﾗﾝｸ角度,ﾘﾆｱmm

	MOV.L	#_PVX_MOTINS_AGLX,R5				;ｸﾗﾝｸ角度
	MOV.W	@R5,R2						;
	FAR_JSR	#_SERCH_INSERT_DIG,R0				;IN R2 OUT R3

	MOV.W	#_EQ_STEP_MX2,R4				;max10
	MOV.W	#_EQ_STEP_MAX,R5				;max5
	FAR_JSR	#_INSERT_DAN_MAXCHK,R0				;IN R3 OUT R3

	MOV.L	#_PVX_MOTINS_DAN,R1				;
	MOV.W	R3,@R1						;0:1~10

	TST	R3,R3						;
	TST_BIT_ON TECH_DAN_DIG_RECAL050			;
	M_BRA	TECH_DAN_DIG_RECAL800				;ERR挿入角度が10段以内にない

TECH_DAN_DIG_RECAL050:
	MOV.W	#D'1800,R4					;
	MOV.L	#_PVX_MOTINS_AGLX,R5				;ｸﾗﾝｸ角度
	MOV.W	@R5,R2						;
	CMP/GE	R2,R4						;R2=<R4(1800)
	BT	TECH_DAN_DIG_RECAL080				;OK
	M_BRA	TECH_DAN_DIG_RECAL800				;ERR挿入角度が1800を超えた


TECH_DAN_DIG_RECAL080:
;	-------- 金型挿入位置はOK------				;
	MOV.W	#BIT0,R2					;
	FAR_JSR	#_MOTINS_INF_CLR,R0				;


;	-----------------------------------------------
;	------- 速度から減速角度ﾘﾝｸを算出する ---------
;	-----------------------------------------------
	MOV.L	#_PVX_MOTINS_DAN,R1				;
	MOV.W	@R1,R0						;0:1~10
	ADD	#-1,R0						;1
	TST	R0,R0						;
	TST_BIT_OF TECH_DAN_DIG_RECAL145			;1段目に挿入する--1段目の速度で動作する
	ADD	#-1,R0						;2段目に挿入する場合,減速対象の速度は1個前
TECH_DAN_DIG_RECAL145:
	SHLL2	R0						;
	MOV.L	#_SET1_OBJECT_SPD_TOP,R5			;
	ADD	R0,R5						;

	MOV.L	@R5,R3						;速度PLS/S

	MOV.L	#_SET1_KATTCH_SPD,R0				;
	MOV.L	@R0,R2						;ﾀｰｹﾞｯﾄ速度PLS/S

	FAR_JSR	#_COM_GENSK_LENGTH_CALC,R0			;input R2,R3


;ANS R2:PLS--LENGTH=>DIG
	FAR_JSR	#_LINK_PLS_CHG_LINK_DIG,R0			;

	TST	R2,R2						;
	TST_BIT_ON TECH_DAN_DIG_RECAL150			;
	MOV.W	#BIT1,R2					;距離=0　速度が同じ(または演算結果が0.1度以下)
	FAR_JSR	#_MOTINS_INF_CLR,R0				;正常
	XOR	R3,R3						;
	MOV.L	#_PVX_MOTINS_DANBEF,R1				;挿入は不要
	MOV.W	R3,@R1						;
	M_BRA	TECH_DAN_DIG_RECAL300				;


TECH_DAN_DIG_RECAL150:

;	------- 減速角度ﾘﾝｸからｸﾗﾝｸを算出する ---------
	MOV	R2,R3						;引き算する角度
	MOV.L	#_PVX_MOTINS_AGL,R1				;ﾀｯﾁ角度・ﾘﾝｸ
	MOV.W	@R1,R2						;

	SUB	R3,R2						;
	CMP/PZ	R2
	BT	TECH_DAN_DIG_RECAL160				;
	MOV.W	#D'3600,R4					;
	ADD	R4,R2						;
TECH_DAN_DIG_RECAL160:						;


	PUSH_REG1	R2

;	---待機点[ﾘﾝｸ,ﾒｲﾝｼｬﾌﾄ,360]を跨ぐ場合は待機点にする---
	MOV	R2,R1					;開始点(引いた結果)
	MOV.L	#_PVX_MOTINS_AGL,R0			;ﾀｯﾁ角度・ﾘﾝｸ
	MOV.W	@R0,R3					;引く前
	MOV.L	#_SET1_UPAREA_DIG0,R0			;　_SETX_LINK_UP_POS_UP
	MOV.W	@R0,R2					;
	FAR_JSR	#_DIG_AREA_CHK0,R0			;この範囲なら異常R0=1範囲内

	POP_REG1	R3				;
	TST	R0,R0					;
	TST_BIT_ON TECH_DAN_DIG_RECAL180		;ﾘﾐｯﾄをかける　R2:UP　ANS
	MOV	R3,R2					;通常ﾃﾞｰﾀ
TECH_DAN_DIG_RECAL180:					;






	MOV.L	#_PVX_MOTINS_AG2,R1				;
	MOV.W	R2,@R1						;ﾘﾝｸ減速

	MOV.L	#_PVX_MOTINS_AG2X,R5				;ｸﾗﾝｸ角度
	MOV.L	#_PVX_MOTINS_PS2,R6				;ﾘﾆｱmm
	FAR_JSR	#_PVDIG_TO_CLANK_RNA_MAK,R0			;ﾀｯﾁ角度・ﾘﾝｸ->ｸﾗﾝｸ角度,ﾘﾆｱmm


	MOV.L	#_PVX_MOTINS_AG2X,R5				;ｸﾗﾝｸ角度
	MOV.W	@R5,R2						;
	FAR_JSR	#_SERCH_INSERT_DIG,R0				;IN R2 OUT R3

	MOV.W	#_EQ_STEP_MX2-1,R4				;max10
	MOV.W	#_EQ_STEP_MAX-1,R5				;max5
	FAR_JSR	#_INSERT_DAN_MAXCHK,R0				;IN R3 OUT R3

	MOV.L	#_PVX_MOTINS_DANBEF,R1				;
	MOV.W	R3,@R1						;0:1~10


	TST	R3,R3						;
	TST_BIT_ON TECH_DAN_DIG_RECAL300			;
	M_BRA	TECH_DAN_DIG_RECAL850				;ERR



;	======== AFFTER角度=========
TECH_DAN_DIG_RECAL300:
;	-------- 減速演算は挿入位置はOK[挿入する・しないは別]------	;
	MOV.W	#BIT1,R2					;
	FAR_JSR	#_MOTINS_INF_CLR,R0				;

;	========= タッチ後位置挿入[]===============
	MOV.L	#_SET1_MRTION_SEL1,R1				;
	MOV.W	@R1,R0						;
	CMP/EQ	#_DMATH_REVRSE,R0				;DRIVE MATH 反転
	BF	TECH_DAN_DIG_RECAL320				;2013-04-08


;	==== ｸﾗﾝｸ角度で設定する=====
	MOV.L	#_SET1_DNAREA_JUDG,R1				;反転設定不可範囲[注意4byte] P41
	MOV.L	@R1,R2						;
	ADD	#-10,R2						;1度ﾏｲﾅｽする[2013-04-14]
	CMP/PZ	R2						;
	BT	TECH_DAN_DIG_RECAL305				;
	XOR	R2,R2						;
TECH_DAN_DIG_RECAL305:


	MOV.L	#_PVX_MOTINS_AG3X,R1				;
	MOV.W	R2,@R1						;ｸﾗﾝｸがﾊﾟﾗﾒｰﾀになるように設定する
	FAR_JSR	#_SV_CLNK_DG_CHG_LINK_DG1,R0			;
	MOV.L	#_PVX_MOTINS_AG3,R1				;
	MOV.W	R2,@R1						;ﾘﾝｸ

	MOV	#100,R4						;
	DMULS.L	R4,R2						;
	STS.L	MACL,R2						;
	FAR_JSR	#_DIG36000_CHG_RENEA1,R0			;360.000度-->0.001mm
	MOV.L	#_SET1_NEG_OFS_LNG,R1				;
	MOV.L	@R1,R0						;
	SUB	R0,R2						;
	CMP/PZ	R2						;
	BT	TECH_DAN_DIG_RECAL310				;
	XOR	R0,R0						;
TECH_DAN_DIG_RECAL310:						;

	MOV.L	#_PVX_MOTINS_PS3,R1				;mm=0
	MOV.L	R2,@R1						;
	M_BRA	TECH_DAN_DIG_RECAL350				;


TECH_DAN_DIG_RECAL320:
	MOV.W	#D'1800,R2					;
	MOV.L	#_PVX_MOTINS_AG3,R1				;
	MOV.W	R2,@R1						;ﾘﾝｸ
	MOV.L	#_PVX_MOTINS_AG3X,R1				;
	MOV.W	R2,@R1						;ｸﾗﾝｸ
	MOV.L	#_PVX_MOTINS_PS3,R1				;mm=0
	XOR	R2,R2						;
	MOV.L	R2,@R1
TECH_DAN_DIG_RECAL350:






	MOV.L	#_PVX_MOTINS_AG3X,R5				;
	MOV.W	@R5,R2						;
	FAR_JSR	#_SERCH2_INSERT_DIG,R0				;IN R2 OUT R3

	MOV.W	#_EQ_STEP_MX2-1,R4				;max10
	MOV.W	#_EQ_STEP_MAX-1,R5				;max5
	FAR_JSR	#_INSERT_DAN_MAXCHK,R0				;IN R3 OUT R3

	MOV.L	#_PVX_MOTINS_DANAFT,R1				;
	MOV.W	R3,@R1						;0:1~10

	TST	R3,R3						;
	TST_BIT_ON TECH_DAN_DIG_RECAL400			;
	M_BRA	TECH_DAN_DIG_RECAL880				;

TECH_DAN_DIG_RECAL400:
;	-------- 180度挿入位置はOK------			;
	MOV.W	#BIT2,R2					;
	FAR_JSR	#_MOTINS_INF_CLR,R0				;



;;;;	========タッチ挿入位置　同位置で同速度データがあれば挿入しない[金型タッチ挿入]===
;;;;	MOV.L	#_SVP_KATTCH_SPD,R1				;
;;;;	MOV.W	@R1,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2:速度
;;;;	MOV	R2,R7						;
;;;;	MOV.L	#_PVX_MOTINS_AGLX,R1				;
;;;;	MOV.W	@R1,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	MOV	R2,R8						;1度
;;;;
;;;;	MOV.L	#_PVX_MOTINS_DAN,R1				;
;;;;	MOV.W	@R1,R3						;0:1~10
;;;;	FAR_JSR	#_SERCH_CMP_SPDPOS,R0				;
;;;;	TST	R0,R0						;
;;;;	TST_BIT_OF TECH_DAN_DIG_RECAL420			;
;;;;	XOR	R3,R3						;
;;;;	MOV.L	#_PVX_MOTINS_DAN,R1				;
;;;;	MOV.W	R3,@R1						;0:1~10
;;;;TECH_DAN_DIG_RECAL420:
;;;;
;;;;;	========タッチ後挿入位置　同位置で同速度データがあれば挿入しない===
;;;;	MOV.L	#_SVP_KATTCH_SPD,R1				;
;;;;	MOV.W	@R1,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;R2:速度
;;;;	MOV	R2,R7						;
;;;;	MOV.L	#_PVX_MOTINS_AG3X,R1				;
;;;;	MOV.W	@R1,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	MOV	R2,R8						;1度ﾃﾞｰﾀ
;;;;
;;;;	MOV.L	#_PVX_MOTINS_DANAFT,R1				;
;;;;	MOV.W	@R1,R3						;0:1~10
;;;;	FAR_JSR	#_SERCH_CMP_SPDPOS,R0				;
;;;;	TST	R0,R0						;
;;;;	TST_BIT_OF TECH_DAN_DIG_RECAL480			;
;;;;	XOR	R3,R3						;
;;;;	MOV.L	#_PVX_MOTINS_DANAFT,R1				;
;;;;	MOV.W	R3,@R1						;挿入しない
;;;;TECH_DAN_DIG_RECAL480:
;;;;
;;;;
;;;;;	============ 減速の同じ挿入データチェック===============
;;;;	MOV.L	#_PVX_MOTINS_AG2X,R1				;
;;;;	MOV.W	@R1,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	MOV	R2,R8						;1度ﾃﾞｰﾀ
;;;;
;;;;	MOV.L	#_PVX_MOTINS_DANBEF,R1				;
;;;;	MOV.W	@R1,R3						;
;;;;	ADD	#-1,R3						;
;;;;	SHLL	R3						;
;;;;	MOV.L	#_SVP_OBJECT_DIG_TOP,R6				;01段目角度
;;;;	ADD	R3,R6						;
;;;;	MOV.W	@R6,R2						;
;;;;	MOV.W	#D'10,R4					;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	CMP/EQ	R2,R8						;
;;;;	BF	TECH_DAN_DIG_RECAL600				;
;;;;
;;;;
;;;;	MOV.L	#_SVP_OBJECT_SPD_TOP,R6				;01段目移動速度
;;;;	MOV.L	#_PVX_MOTINS_DANBEF,R1				;
;;;;	MOV.W	@R1,R3						;
;;;;	ADD	#-1,R3						;
;;;;	TST	R3,R3						;初段に挿入
;;;;	TST_BIT_OF TECH_DAN_DIG_RECAL500			;YES
;;;;	ADD	#-1,R3						;
;;;;TECH_DAN_DIG_RECAL500:						;
;;;;	SHLL	R3						;
;;;;	ADD	R3,R6						;
;;;;
;;;;
;;;;TECH_DAN_DIG_RECAL600:
	M_BRA	TECH_DAN_DIG_RECAL900			;



TECH_DAN_DIG_RECAL800:
	MOV.W	#BIT0,R2					;[BIT0]
	M_BRA	TECH_DAN_DIG_RECAL890				;

TECH_DAN_DIG_RECAL850:
	MOV.W	#BIT1,R2					;
	M_BRA	TECH_DAN_DIG_RECAL890				;

TECH_DAN_DIG_RECAL880:
	MOV.W	#BIT2,R2					;

TECH_DAN_DIG_RECAL890:
	FAR_JSR	#_MOTINS_INF_ERR,R0				;

TECH_DAN_DIG_RECAL900:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	INF-ERR-SET			***
;	***					***
;	*******************************************
;	input R2
_MOTINS_INF_ERR
	SUB_START
	MOV.L	#_PVX_MOTINS_INF,R1	;
	MOV.W	@R1,R0			;
	OR	R2,R0			;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	INF-ERR-CLR			***
;	***					***
;	*******************************************
;	input R2
_MOTINS_INF_CLR
	SUB_START
	MOV.L	#_PVX_MOTINS_INF,R1	;
	MOV.W	@R1,R0			;
	NOT	R2,R3
	AND	R3,R0			;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	減速距離演算(実)		***
;	***					***
;	*******************************************
;		R2:V2:OBJ SPED
;		R3:V1
;		ANS:R2
;
_COM_GENSK_LENGTH_CALC
	SUB_START

	MOV.L	#_SETX_POS_CTL_MATH,R1		;
	MOV.W	@R1,R0				;
	TST	#_DMATH_DNDRIV,R0		;
	TST_BIT_ON COMFPUGCALC_050		;

	MOV.L	#_SET1_ACCLAT_TIM1,R1		;反転(このﾃﾞｰﾀは既に比率倍されている)・回転
	MOV.W	@R1,R4				;
	M_BRA	COMFPUGCALC_100			;

;	-------------- ふりこ------------
COMFPUGCALC_050:
	MOV.L	#_ACCB_ACCLAT_TIM1,R1		;
	MOV.W	@R1,R4				;

COMFPUGCALC_100:
	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R1,R1				;

	MOV.W	#D'1000,R5
	FAR_JSR	#_FPU_CALC_GEN_LENGTH,R0	;

	TST	R2,R2
	TST_BIT_OF COMFPUGCALC_200		;

	MOV.W	#D'1000,R0							;
	MOV.L	#(_PAR_TECH_GENPLS-_CB_SYS_PARAM000+_W_PARAM_TOP),R1		;
	MOV.W	@R1,R0								;
	ADD	R0,R2								;

	MOV.L	#_LINK_1ROT_PLS,R1		;//1回転ﾊﾟﾙｽ(設定ﾚﾍﾞﾙ)
	MOV.L	@R1,R0				;
	CMP/HS	R2,R0				;R2=< R0
	BT	COMFPUGCALC_200			;
		
	MOV	R0,R2				;3600度以上の減速は許さない

COMFPUGCALC_200:

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	input 			***
;	***		R2:OBJ SPEED	***
;	***				***
;	***********************************
;	input R2:V2:OBJ    P/S
;	input R3:V1:OLD    P/S
;	input R1:SPDMAX P/S
;	input R4:TIMAX ms
;	input R5:1000 msec
;
;
;	S=(V2^2 - V1^2)* 1/2 *(Tmax/(Vmax*1000))
;	α:Vmax*1000/Tmaxを先に演算し、整数部のみ取出す　整数のLATEだから
;	S=(V2^2 - V1^2)* 1/2 *α
;
;
_FPU_CALC_GEN_LENGTH:
	SUB_START

	TST	R4,R4				;
	TST_BIT_OF FPU_CALC_GENLNGTH_ERR	;割算できない

	LDS	R1,FPUL				;
	FLOAT	FPUL,FR1			;PLS/S

	LDS	R5,FPUL				;
	FLOAT	FPUL,FR2			;1000

	FMUL	FR1,FR2				;PLS/S*1000

	LDS	R4,FPUL				;
	FLOAT	FPUL,FR4			;TIM-MAX

	FDIV	FR4,FR2				;α

	FTRC	FR2,FPUL			;
	STS	FPUL,R0				;
	TST	R0,R0				;
	TST_BIT_OF FPU_CALC_GENLNGTH_ERR	;


	LDS	R0,FPUL				;
	FLOAT	FPUL,FR4			;
	FADD	FR4,FR4				;FR4=2α


;;;	CMP/GE	R3,R2				;
;;;	BT	FPU_CALC_GENLNGTH_100		;R3 =< R2 加速
;;;	FNEG	FR4				;-α
;;;FPU_CALC_GENLNGTH_100				;


	LDS	R3,FPUL				;
	FLOAT	FPUL,FR1			;V1

	LDS	R2,FPUL				;
	FLOAT	FPUL,FR2			;V2

	FMUL	FR1,FR1				;
	FMUL	FR2,FR2				;
	FSUB	FR1,FR2				;(V2^2-V1^2)/2α

	FDIV	FR4,FR2				;

	FTRC	FR2,FPUL			;
	STS	FPUL,R2				;
	CMP/PZ	R2				;
	BT	FPU_CALC_GENLNGTH_100		;
	NEG	R2,R2				;
FPU_CALC_GENLNGTH_100				;
	M_BRA	FPU_CALC_GENLNGTH_EXT		;



FPU_CALC_GENLNGTH_ERR:
	XOR	R2,R2				;R2=0
FPU_CALC_GENLNGTH_EXT:

	SUB_END
	M_RTS


;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_DAN,R1		;
;;;[2013-02-20]		MOV.W	@R1,R0				;[発生した段数]
;;;[2013-02-20]	
;;;[2013-02-20]		MOV.L	#_SETX_POS_STEP_MAX,R1		;
;;;[2013-02-20]		MOV.W	@R1,R2				;
;;;[2013-02-20]	
;;;[2013-02-20]		CMP/HI	R2,R0				;
;;;[2013-02-20]		BT	TECH_DAN_DIGRECAL050		;R2<R0　最終(戻りの前)YES JUMP
;;;[2013-02-20]		M_BRA	TECH_DAN_DIGRECAL100		;R0=<R2
;;;[2013-02-20]	
;;;[2013-02-20]	TECH_DAN_DIGRECAL050:				;
;;;[2013-02-20]		MOV	R2,R0				;戻りの前のデータ
;;;[2013-02-20]	TECH_DAN_DIGRECAL100:				;
;;;[2013-02-20]	
;;;[2013-02-20]		MOV.L	#_SVP_OBJECT_SPD_TOP,R5		;0~100.0%,2byte
;;;[2013-02-20]		ADD	#-1,R0				;
;;;[2013-02-20]		ADD	R0,R0
;;;[2013-02-20]		ADD	R0,R5				;
;;;[2013-02-20]		MOV.W	@R5,R2				;%速度
;;;[2013-02-20]	
;;;[2013-02-20]		FAR_JSR	#_TECH_GENSOK_DIG_LENGTH,R0	;ANS R2:DEG
;;;[2013-02-20]	
;;;[2013-02-20]	;	========== input R2 INC角度 OutPut ｸﾗﾝｸ角度
;;;[2013-02-20]	;;;;;	MOV.L	#_INC_ENC360,R4			;
;;;[2013-02-20]	;;;;;	MOV.L	#_DNM_CTL_INC3600,R4		;
;;;[2013-02-20]	
;;;[2013-02-20]	
;;;[2013-02-20]		FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
;;;[2013-02-20]		MOV.W	#D'3600,R4			;
;;;[2013-02-20]		CMP/HI	R2,R4				;
;;;[2013-02-20]		BT	TECH_DAN_DIGRECAL200		;
;;;[2013-02-20]		SUB	R4,R2				;画面表示角度(ｸﾗﾝｸ)
;;;[2013-02-20]	TECH_DAN_DIGRECAL200:				;
;;;[2013-02-20]	
;;;[2013-02-20]	;	===========今は前の段でリミッタする=======
;;;[2013-02-20]	;	===========
;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_DAN,R1		;
;;;[2013-02-20]	MOV.W	@R1,R0				;[発生した段数]
;;;[2013-02-20]	CMP/EQ	#1,R0				;
;;;[2013-02-20]	BT	TECH_DAN_DIGRECAL300		;OK
;;;[2013-02-20]
;;;[2013-02-20];	----------------------------
;;;[2013-02-20];	--------2段目	------------
;;;[2013-02-20];	----------------------------
;;;[2013-02-20];	-------2段目なら1段目にしても構わない-----
;;;[2013-02-20]	MOV.L	#_SVP_OBJECT_DIG_TOP,R5		;ｸﾗﾝｸ上で必ず+になる
;;;[2013-02-20]	ADD	#-2,R0				;
;;;[2013-02-20]	ADD	R0,R0				;
;;;[2013-02-20]	ADD	R0,R5				;
;;;[2013-02-20]	MOV.W	@R5,R3				;
;;;[2013-02-20]	CMP/HS	R3,R2				;
;;;[2013-02-20]	BT	TECH_DAN_DIGRECAL300		;R3<R2 OK
;;;[2013-02-20]
;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_DAN,R1		;
;;;[2013-02-20]	MOV.W	@R1,R0				;[発生した段数]
;;;[2013-02-20]	ADD	#-1,R0				;
;;;[2013-02-20]	MOV.W	R0,@R1				;
;;;[2013-02-20]	CMP/EQ	#1,R0				;
;;;[2013-02-20]	BT	TECH_DAN_DIGRECAL300		;
;;;[2013-02-20]
;;;[2013-02-20];	-----------------------------
;;;[2013-02-20];	--------3段目以降------------
;;;[2013-02-20];	-----------------------------
;;;[2013-02-20]	MOV.L	#_SVP_OBJECT_DIG_TOP,R5		;ｸﾗﾝｸ上で必ず+になる
;;;[2013-02-20]	ADD	#-2,R0				;
;;;[2013-02-20]	ADD	R0,R0				;
;;;[2013-02-20]	ADD	R0,R5				;
;;;[2013-02-20]	MOV.W	@R5,R3				;
;;;[2013-02-20]	ADD	#D'1,R3				;0.1度
;;;[2013-02-20]	CMP/HS	R3,R2				;
;;;[2013-02-20]	BT	TECH_DAN_DIGRECAL280		;R3<R2 OK
;;;[2013-02-20]	MOV	R3,R2				;LIMIT
;;;[2013-02-20]TECH_DAN_DIGRECAL280:				;
;;;[2013-02-20]	NOP
;;;[2013-02-20]	NOP
;;;[2013-02-20]TECH_DAN_DIGRECAL300:
;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_AGL,R1		;
;;;[2013-02-20]	MOV.W	R2,@R1				;
;;;[2013-02-20]
;;;[2013-02-20];	---------------------------------
;;;[2013-02-20]	FAR_JSR	#_SV_CLNK_DG_CHG_LINK_DG1,R0	;ｸﾗﾝｸ(表示)→ﾘﾝｸ(360)
;;;[2013-02-20]
;;;[2013-02-20];	--------------ﾘﾝｸ/ﾘﾆｱ演算-------
;;;[2013-02-20]	MOV.B	#D'100,R4			;
;;;[2013-02-20]	DMULS.L	R4,R2				;
;;;[2013-02-20]	STS.L	MACL,R2				;
;;;[2013-02-20]	FAR_JSR	#_DIG36000_CHG_RENEA1,R0	;かなり重い演算
;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_POS,R1		;
;;;[2013-02-20]	MOV.L	R2,@R1				;
;;;[2013-02-20]
;;;[2013-02-20]	SUB_END
;;;[2013-02-20]	M_RTS
;;;[2013-02-20]
;;;[2013-02-20];
;;;[2013-02-20];
;;;[2013-02-20];	S = (V1^2 - V2^2) *1/2 * Vmax/Tmax
;;;[2013-02-20];	  V2=V1* 1/2
;;;[2013-02-20];	S = 3/4 * V1^2 * 1/2 * Vmax/Tmax
;;;[2013-02-20];	  = 3/8 * V1^2 * Vmax/Tmax
;;;[2013-02-20];	V1=Vmax*K1/1000   ,Tmax=Umax/1000   K1=0~100.0% Umax=***[ms]
;;;[2013-02-20];	
;;;[2013-02-20];	S= (K1^2 * Vmax)/(1000^2) * Umax * 1/1000 * 3/8
;;;[2013-02-20];
;;;[2013-02-20]	.ALIGN	4				;
;;;[2013-02-20]_TECH_GENSOK_DIG_LENGTH:
;;;[2013-02-20]	SUB_START
;;;[2013-02-20]
;;;[2013-02-20];	-------- K1^2* VMAX ---------------
;;;[2013-02-20]	DMULS.L	R2,R2				;K1(100.0%)
;;;[2013-02-20]	MOV.L	#_LINK_MAX_SPD_PLS,R0		;
;;;[2013-02-20]	MOV.L	@R0,R1				;2500000~500000PLS/S
;;;[2013-02-20]
;;;[2013-02-20]	STS.L	MACL,R2				;1000000
;;;[2013-02-20]	DMULS.L	R2,R1				;1000,000,*500,000
;;;[2013-02-20]
;;;[2013-02-20];	-------- K1^2* VMAX /1000^2---------------
;;;[2013-02-20]	STS	MACL,R2				;
;;;[2013-02-20]	STS	MACH,R1				;
;;;[2013-02-20]	MOV.L	#D'1000*D'1000,R4		;
;;;[2013-02-20]	FAR_JSR	#_DIVS_64R1R2_32R4_32R2,R0	;ANS ~500,000
;;;[2013-02-20]
;;;[2013-02-20];	--------- *3/8 --------------
;;;[2013-02-20]	MOV	R2,R1				;
;;;[2013-02-20]	ADD	R1,R1				;
;;;[2013-02-20]	ADD	R1,R2				;*3
;;;[2013-02-20]
;;;[2013-02-20]	SHLR	R2				;1/2
;;;[2013-02-20]	SHLR	R2				;1/4
;;;[2013-02-20]	SHLR	R2				;1/8
;;;[2013-02-20]
;;;[2013-02-20];	--------- *Mmax/1000 --------------
;;;[2013-02-20]	MOV.L	#_SET1_ACCLAT_TIM1,R0				;
;;;[2013-02-20]	MOV.W	@R0,R1						;
;;;[2013-02-20]	MOV.W	#D'1000,R4					;
;;;[2013-02-20]	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;
;;;[2013-02-20]
;;;[2013-02-20]	MOV.L	#_TECH_WK_PLS1,R1				;移動PLS
;;;[2013-02-20]	MOV.L	R2,@R1						;
;;;[2013-02-20]
;;;[2013-02-20]
;;;[2013-02-20]	FAR_JSR	#_LINK_PLS_CHG_LINK_DIG,R0			;
;;;[2013-02-20]	MOV.L	#_TECH_WK_DIG2,R1				;
;;;[2013-02-20]	MOV.W	R2,@R1						;
;;;[2013-02-20]
;;;[2013-02-20]
;;;[2013-02-20]	MOV.L	#_PVX_MOTINS_AGL,R1				;
;;;[2013-02-20]	MOV.W	@R1,R3						;
;;;[2013-02-20]
;;;[2013-02-20]	SUB	R2,R3						;
;;;[2013-02-20]	MOV	R3,R2						;
;;;[2013-02-20]	CMP/PZ	R2
;;;[2013-02-20]	BT	TECH_GENSOK_DIGLGT100				;
;;;[2013-02-20]	MOV.W	#D'3600,R4					;
;;;[2013-02-20]	ADD	R4,R2						;
;;;[2013-02-20]TECH_GENSOK_DIGLGT100:						;
;;;[2013-02-20]	MOV.L	#_TECH_WK_DIG3,R1				;
;;;[2013-02-20]	MOV.W	R2,@R1						;この角度が段数を変える場合は,
;;;[2013-02-20]
;;;[2013-02-20]	SUB_END
;;;[2013-02-20]	M_RTS


;	***************************************************
;	***						***
;	***	リンクデータをクランク、リニアに変換	***
;	***						***
;	***************************************************
;	2013-02-20
;	INPUT:R2
;	INPUT:R5(角度2B ADR),R6
;
;
_PVDIG_TO_CLANK_RNA_MAK:
	SUB_START

	PUSH_REG1 R5
	PUSH_REG1 R6

	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0			;
	MOV.W	#D'3600,R4					;
	CMP/HI	R2,R4						;
	BT	PVDIG_TO_CLANKRNAMK_100				;
	SUB	R4,R2						;画面表示角度(ｸﾗﾝｸ)
PVDIG_TO_CLANKRNAMK_100:					;

	POP_REG1 R6
	POP_REG1 R5

	MOV.W	R2,@R5						;

	PUSH_REG1 R6
;	--------------------------------------------------------
	FAR_JSR	#_SV_CLNK_DG_CHG_LINK_DG1,R0			;ｸﾗﾝｸ(表示)→ﾘﾝｸ(360)
;	--------------ﾘﾝｸ/ﾘﾆｱ演算-------------------------------
	MOV.B	#D'100,R4					;
	DMULS.L	R4,R2						;
	STS.L	MACL,R2						;
	FAR_JSR	#_DIG36000_CHG_RENEA1,R0			;かなり重い演算

	POP_REG1 R6						;

;	------2013-04-08 反転を考慮---------
	MOV.L	#_SET1_MRTION_SEL1,R1				;
	MOV.W	@R1,R0						;
	CMP/EQ	#_DMATH_REVRSE,R0				;DRIVE MATH 反転
	BF	PVDIG_TO_CLANKRNAMK_150				;

	MOV.L	#_SET1_NEG_OFS_LNG,R1				;
	MOV.L	@R1,R0						;
	SUB	R0,R2						;
	CMP/PZ	R2
	BT	PVDIG_TO_CLANKRNAMK_150				;
	XOR	R0,R0						;
PVDIG_TO_CLANKRNAMK_150:					;
	MOV.L	R2,@R6						;

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	クランク上で				***
;	***	R2より小さい設定の中で最も大きな行程	***
;	***	無い場合は1行程目			***
;	***	2013-02-20				***
;	***************************************************
;	Input  R2:角度[170度]
;	Output R3:行程 1~10　:0は既に行程数が10行程使用されている
;
_SERCH_INSERT_DIG:
	SUB_START
	MOV.L	#_SVP_OBJECT_DIG_TOP,R6			;01段目角度

	XOR	R3,R3					;

	MOV.L	#_SETX_POS_STEP_MAX,R1			;
	MOV.W	@R1,R5					;設定1~10
							;1段の場合    1個の位置ﾁｪｯｸ
							;10段の場合  10個の位置ﾁｪｯｸ
	MOV	R5,R0					;
	ADD	#-1,R0					;
	ADD	R0,R0					;
	ADD	R0,R6					;最終角度TOP

SERCH_INSERTDG_100LOP:
	MOV.W	@R6,R1					;200度
	CMP/GE	R1,R2					;R1=< R2
	BT	SERCH_INSERTDG_200			;
	ADD	#-1,R5					;
	ADD	#-2,R6					;
	TST	R5,R5					;
	TST_BIT_ON SERCH_INSERTDG_100LOP		;
SERCH_INSERTDG_200:
	MOV	R5,R3					;
	ADD	#1,R3					;挿入すべき行程 1~11
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	角度が同じの場合、若い段数にする	***
;	***						***
;	***************************************************
_SERCH2_INSERT_DIG:
	SUB_START
	MOV.L	#_SVP_OBJECT_DIG_TOP,R6			;01段目角度

	XOR	R3,R3					;

	MOV.L	#_SETX_POS_STEP_MAX,R1			;
	MOV.W	@R1,R5					;設定1~10
							;1段の場合    1個の位置ﾁｪｯｸ
							;10段の場合  10個の位置ﾁｪｯｸ
	MOV	R5,R0					;
	ADD	#-1,R0					;
	ADD	R0,R0					;
	ADD	R0,R6					;最終角度TOP

SERCH2_INSERTDG_100LOP:
	MOV.W	@R6,R1					;200度
	CMP/GT	R1,R2					;R1=< R2
	BT	SERCH2_INSERTDG_200			;
	ADD	#-1,R5					;
	ADD	#-2,R6					;
	TST	R5,R5					;
	TST_BIT_ON SERCH2_INSERTDG_100LOP		;
SERCH2_INSERTDG_200:
	MOV	R5,R3					;
	ADD	#1,R3					;挿入すべき行程 1~11
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	段数チェック			***
;	***					***
;	*******************************************
;INPUT  R3  ,R4:MAX=10段,R5:MAX=5
;OUTPUT R3  1~10,ERR:R3=0
;;;;	MOV.W	#_EQ_STEP_MX2,R4			;max10
;;;;	MOV.W	#_EQ_STEP_MAX,R4			;max5
_INSERT_DAN_MAXCHK:
	SUB_START

	MOV.L	#_WFSYS_MAX_STEP_SEL,R1			;
	MOV.W	@R1,R0					;
	CMP/EQ	#1,R0					;10段仕様?
	BT	INSERTDANMAX_300
	MOV	R5,R4					;
INSERTDANMAX_300
	CMP/GE	R3,R4					;
	BT	INSERTDANMAX_EXT			;R3=< MAX(10or5)
	XOR	R3,R3					;ERR
INSERTDANMAX_EXT:

	SUB_END
	M_RTS







;	***************************************************
;	***						***
;	***	指定された段数の速度,位置が同じか	***
;	***						***
;	***************************************************
;	同じ R0=1 ELSE R0=0
;
;	input R7:SPEED
;	input R8:DIG
;	input R3:段数
;
_SERCH_CMP_SPDPOS
	SUB_START

	ADD	#-1,R3					;
	SHLL	R3					;
	MOV.L	#_SVP_OBJECT_SPD_TOP,R6			;01段目移動速度
	ADD	R3,R6					;
	MOV.W	@R6,R0					;0.1%data
	CMP/EQ	R7,R0					;
	BF	SERCH_CMPSPDPOS_100			;速度が同じじゃない


	MOV.L	#_SVP_OBJECT_DIG_TOP,R6				;01段目角度
	ADD	R3,R6						;
	MOV.W	@R6,R2						;
	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;

	CMP/EQ	R8,R2						;
	BF	SERCH_CMPSPDPOS_100				;角度1度単位が同じじゃない
	MOV.B	#1,R0						;
	M_BRA	SERCH_CMPSPDPOS_200				;

SERCH_CMPSPDPOS_100:
	XOR	R0,R0
SERCH_CMPSPDPOS_200:


	SUB_END
	M_RTS



;;[ﾘﾆｱ2012-10-17削除];	*******************************************
;;[ﾘﾆｱ2012-10-17削除];	***					***
;;[ﾘﾆｱ2012-10-17削除];	***					***
;;[ﾘﾆｱ2012-10-17削除];	***					***
;;[ﾘﾆｱ2012-10-17削除];	***	リニア加速度演算		***
;;[ﾘﾆｱ2012-10-17削除];	***	2011-08-01			***
;;[ﾘﾆｱ2012-10-17削除];	***					***
;;[ﾘﾆｱ2012-10-17削除];	*******************************************
;;[ﾘﾆｱ2012-10-17削除]	.ALIGN	4				;
;;[ﾘﾆｱ2012-10-17削除]_RNA_BIBUN_DATA_MAKE				;
;;[ﾘﾆｱ2012-10-17削除]	SUB_START
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除];	-------- 4msec 固定------------
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	#D'4,R0					;2011-08-29
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_SET_TIME,R1			;//MAX20msec
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	R0,@R1					;
;;[ﾘﾆｱ2012-10-17削除];	--------------------------------
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MESURE_POINT,R1	;
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	@R1,R0				;
;;[ﾘﾆｱ2012-10-17削除]	SHLL2	R0				;*4
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除];	--------------------------------------
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MESURE_SPOS_BUF,R10	;//8byte
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MESURE_SSPD_BUF,R11	;//4byte
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MEUSRE_ACC_SRC,R12	;ANS
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_ABS_POS,R13		;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MESURE_SSPD,R14	;//4byte SV-POS[2個だけ]
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	ADD.L	R0,R10							;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	@R10,R4							;OLD-LOAD(SV=30msec前)
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	@R13,R2							;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	R2,@R10							;NEW data R1,R2 SAVE
;;[ﾘﾆｱ2012-10-17削除]	SUB	R4,R2							;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	R2,@R14							;R2=[mm-mm]=SPD[mm/1000]
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	ADD	R0,R11							;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	@R11,R5							;OLD SPEED
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	R2,@R11							;NEW SPEED
;;[ﾘﾆｱ2012-10-17削除]	SUB	R5,R2							;ACC 但し時間換算しいない状態
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	R2,@R12							;R2=mm/s[1/1000]/s[1/1000]
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除];	------NEXT SET----
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_SET_TIME,R1					;//MAX20msec
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	@R1,R7							;1~20
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MESURE_POINT,R1				;
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	@R1,R0							;
;;[ﾘﾆｱ2012-10-17削除]	ADD	#1,R0						;
;;[ﾘﾆｱ2012-10-17削除]	CMP/HS	R7,R0						;
;;[ﾘﾆｱ2012-10-17削除]	BF	RNA_BIBUN_DATMAK500				;
;;[ﾘﾆｱ2012-10-17削除]	XOR	R0,R0
;;[ﾘﾆｱ2012-10-17削除]RNA_BIBUN_DATMAK500					;
;;[ﾘﾆｱ2012-10-17削除]	MOV.W	R0,@R1				;
;;[ﾘﾆｱ2012-10-17削除]RNA_BIBUN_DATMAK600					;
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除];	-------正解は data*1000*1000/tim(20)*tim(20)が正解------------------------
;;[ﾘﾆｱ2012-10-17削除]	M_BRA	RNA_BIBUN_DATMAK700
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]RNA_BIBUN_DATMAK700:
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	DMULS.L	R7,R7				;
;;[ﾘﾆｱ2012-10-17削除]	STS	MACL,R7				;msec
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MEUSRE_ACC_SRC,R5	;ANS
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	@R5,R2				;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#1000*1000,R1			;
;;[ﾘﾆｱ2012-10-17削除]	MOV	R7,R4				;
;;[ﾘﾆｱ2012-10-17削除]	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	#_RNA_BBN_MEUSRE_ACC,R5		;
;;[ﾘﾆｱ2012-10-17削除]	MOV.L	R2,@R5				;0.01mm/s 1000.00mm/s
;;[ﾘﾆｱ2012-10-17削除]
;;[ﾘﾆｱ2012-10-17削除]	SUB_END
;;[ﾘﾆｱ2012-10-17削除]	M_RTS



;;;;;;2013-02-20[旧];	*******************************************
;;;;;;2013-02-20[旧];	***					***
;;;;;;2013-02-20[旧];	***					***
;;;;;;2013-02-20[旧];	***					***
;;;;;;2013-02-20[旧];	***	荷重加速度演算			***
;;;;;;2013-02-20[旧];	***	2012-09-25			***
;;;;;;2013-02-20[旧];	***					***
;;;;;;2013-02-20[旧];	*******************************************
;;;;;;2013-02-20[旧]	.ALIGN	4				;
;;;;;;2013-02-20[旧]_KAJYU_BIBUN_DATA_MAKE				;
;;;;;;2013-02-20[旧]	SUB_START
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	--------------- ﾃﾞﾊﾞｯｸ用-------------
;;;;;;2013-02-20[旧]	MOV.L	#_PV_ENC_SPD_PER,R1		;ﾃﾞﾊﾞｯｸ用実測
;;;;;;2013-02-20[旧]	MOV.W	@R1,R2				;
;;;;;;2013-02-20[旧];	-------------------------------------
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_PVPAB_KAJLIV_TTL,R1		;//荷重生（TON）(1word)
;;;;;;2013-02-20[旧]	MOV.W	@R1,R2				;
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MESURE_SSPD,R1	;MONI[生荷重]
;;;;;;2013-02-20[旧]	MOV.L	R2,@R1				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#(_PAR_INSERT_SMPTM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
;;;;;;2013-02-20[旧]	MOV.W	@R1,R0							;
;;;;;;2013-02-20[旧]	MOV.W	#D'2,R4
;;;;;;2013-02-20[旧]	CMP/HS	R4,R0
;;;;;;2013-02-20[旧]	BT	KAJYU_BIBUN_DATMAK050					;2=<R0 OK
;;;;;;2013-02-20[旧]	MOV.W	#D'4,R0							;ELSE 4
;;;;;;2013-02-20[旧]KAJYU_BIBUN_DATMAK050							;
;;;;;;2013-02-20[旧]	MOV.W	#D'20,R4						;
;;;;;;2013-02-20[旧]	CMP/HS	R0,R4							;
;;;;;;2013-02-20[旧]	BT	KAJYU_BIBUN_DATMAK070					;R0=<20
;;;;;;2013-02-20[旧]	MOV	R4,R0							;
;;;;;;2013-02-20[旧]KAJYU_BIBUN_DATMAK070							;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_SET_TIME,R1			;//MAX20msec
;;;;;;2013-02-20[旧]	MOV.W	R0,@R1					;
;;;;;;2013-02-20[旧];	--------------------------------
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MESURE_POINT,R1	;
;;;;;;2013-02-20[旧]	MOV.W	@R1,R0				;
;;;;;;2013-02-20[旧]	SHLL2	R0				;*4
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	--------------------------------------
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MESURE_SPOS_BUF,R10	;//4byte*50BUF
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MESURE_SSPD,R13	;MONI[生荷重]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MEUSRE_ACC_SRC,R14	;//4byte SV-POS[2個だけ]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	ADD.L	R0,R10							;
;;;;;;2013-02-20[旧]	MOV.L	@R10,R4							;OLD-LOAD(SV=30msec前)
;;;;;;2013-02-20[旧]	MOV.L	@R13,R2							;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	R2,@R10							;NEW data R1,R2 SAVE
;;;;;;2013-02-20[旧]	SUB	R4,R2							;
;;;;;;2013-02-20[旧]	MOV.L	R2,@R14							;R2=[mm-mm]=SPD[mm/1000]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	------NEXT SET----
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_SET_TIME,R1					;//MAX20msec
;;;;;;2013-02-20[旧]	MOV.W	@R1,R7							;1~20
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MESURE_POINT,R1				;
;;;;;;2013-02-20[旧]	MOV.W	@R1,R0							;
;;;;;;2013-02-20[旧]	ADD	#1,R0						;
;;;;;;2013-02-20[旧]	CMP/HS	R7,R0						;
;;;;;;2013-02-20[旧]	BF	KAJYU_BIBUN_DATMAK500				;
;;;;;;2013-02-20[旧]	XOR	R0,R0
;;;;;;2013-02-20[旧]KAJYU_BIBUN_DATMAK500					;
;;;;;;2013-02-20[旧]	MOV.W	R0,@R1				;
;;;;;;2013-02-20[旧]KAJYU_BIBUN_DATMAK600					;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	-------正解は data*1000/tim(20)が正解------------------------
;;;;;;2013-02-20[旧]	M_BRA	KAJYU_BIBUN_DATMAK700
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]KAJYU_BIBUN_DATMAK700:
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MEUSRE_ACC_SRC,R5	;ANS
;;;;;;2013-02-20[旧]	MOV.L	@R5,R2				;
;;;;;;2013-02-20[旧]	MOV.L	#D'1000,R1			;
;;;;;;2013-02-20[旧]	MOV	R7,R4				;
;;;;;;2013-02-20[旧]	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_BBN_MEUSRE_ACC,R5		;
;;;;;;2013-02-20[旧]	MOV.L	R2,@R5				;KN/s
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	SUB_END
;;;;;;2013-02-20[旧]	M_RTS
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	.ALIGN	4				;
;;;;;;2013-02-20[旧]_TECT_DATA_MAKE
;;;;;;2013-02-20[旧]	SUB_START
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧];	-----------------------------
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_CTL_POS1,R1		;//制御位置
;;;;;;2013-02-20[旧]	MOV.L	@R1,R2				;0.001mm
;;;;;;2013-02-20[旧]	MOV.L	#_INT_POS_CTL_STEP,R1		;//内部制御工程1~11
;;;;;;2013-02-20[旧]	MOV.W	@R1,R3				;
;;;;;;2013-02-20[旧]	MOV.L	#_DNM_CTL_INC3600,R1		;//CAM、ﾛｯﾄｶｳﾝﾀ、荷重用
;;;;;;2013-02-20[旧]	MOV.W	@R1,R7				;
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_TECH_POINT,R5		;
;;;;;;2013-02-20[旧]	MOV.W	@R5,R0				;
;;;;;;2013-02-20[旧]	MOV.L	#_RNA_TECH_POSBUF,R6		;[過去]
;;;;;;2013-02-20[旧]	MOV	R0,R4				;
;;;;;;2013-02-20[旧]	SHLL2	R4				;
;;;;;;2013-02-20[旧]	SHLL2	R4				;
;;;;;;2013-02-20[旧]	ADD	R4,R6				;[POS]4byte,[STEP]4byte
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	MOV.L	R2,@R6				;
;;;;;;2013-02-20[旧]	ADD	#4,R6				;
;;;;;;2013-02-20[旧]	MOV.L	R3,@R6				;
;;;;;;2013-02-20[旧]	ADD	#4,R6				;
;;;;;;2013-02-20[旧]	MOV.L	R7,@R6
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	ADD	#1,R0				;
;;;;;;2013-02-20[旧]	MOV.W	#_TEACH_BUF_MAX,R4		;
;;;;;;2013-02-20[旧]	CMP/HS	R4,R0				;
;;;;;;2013-02-20[旧]	BF	TECT_DATA_MAK100		;
;;;;;;2013-02-20[旧]	XOR	R0,R0				;0~99
;;;;;;2013-02-20[旧]TECT_DATA_MAK100:				;
;;;;;;2013-02-20[旧]	MOV.W	R0,@R5				;
;;;;;;2013-02-20[旧];	---------------------------------
;;;;;;2013-02-20[旧]
;;;;;;2013-02-20[旧]	SUB_END
;;;;;;2013-02-20[旧]	M_RTS



;;	.IMPORT	_PVP_MOTINS_DAN
;;	.IMPORT	_PVP_MOTINS_AGL
;;	.IMPORT	_PVP_MOTINS_POS

;;	.IMPORT	_PVP_MOTINS_AG2		;2012-10-19
;;	.IMPORT	_PVP_MOTINS_PS2		;2012-10-19

;	.GLOBAL	_PVX_MOTINS_PS2;	
;	.GLOBAL	_PVX_MOTINS_POS;	
;	.GLOBAL	_PVX_MOTINS_PS3;	
;
;	.GLOBAL	_PVX_MOTINS_AG2;	
;	.GLOBAL	_PVX_MOTINS_AG2X;
;
;	.GLOBAL	_PVX_MOTINS_AGL;	
;	.GLOBAL	_PVX_MOTINS_AGLX;
;
;	.GLOBAL	_PVX_MOTINS_AG3;	
;	.GLOBAL	_PVX_MOTINS_AG3X;

	.ALIGN	4				;
_INSERT_MOTION_PV_MOV
	SUB_START

;	----位置、角度はﾀｯﾁ----------
	MEM_MOV_TO_MEM	_PVX_MOTINS_AGLX,W	,_PVP_MOTINS_AGL,W,R1,R2,R3		;0.1
	MEM_MOV_TO_MEM	_PVX_MOTINS_POS,L	,_PVP_MOTINS_POS,L,R1,R2,R3		;0.001mm
	MEM_MOV_TO_MEM	_PVX_MOTINS_DAN		,W,_PVP_MOTINS_DAN,W,R1,R2,R3		;


;	----位置、角度はﾀｯﾁした時点より減速演算分手前--------
	MEM_MOV_TO_MEM	_PVX_MOTINS_AG2X,W	,_PVP_MOTINS_AG2,W,R1,R2,R3		;0.1
	MEM_MOV_TO_MEM	_PVX_MOTINS_PS2,L	,_PVP_MOTINS_PS2,L,R1,R2,R3		;0.001mm
	MEM_MOV_TO_MEM	_PVX_MOTINS_DANBEF,W	,_PVP_MOTINS_DANBEF,W,R1,R2,R3	;0:有効な段数無し 1~9:金型ﾀｯﾁ減速挿入段数

;	-------- その後-------
	MEM_MOV_TO_MEM	_PVX_MOTINS_AG3X,W	,_PVP_MOTINS_AG3,W,R1,R2,R3		;0.1
	MEM_MOV_TO_MEM	_PVX_MOTINS_PS3,L	,_PVP_MOTINS_PS3,L,R1,R2,R3		;0.001mm
	MEM_MOV_TO_MEM	_PVX_MOTINS_DANAFT	,W,_PVP_MOTINS_DANAFT,W,R1,R2,R3	;0:有効な段数無し 1~9:金型ﾀｯﾁ減速挿入段数


;	------------------0以外 挿入不可----------
	MEM_MOV_TO_MEM	_PVX_MOTINS_INF	,W,_PVP_MOTINS_INF,W,R1,R2,R3	;


	SUB_END
	M_RTS

;	--------- 2015-05-20---------
;	ﾓｰｼｮﾝ挿入不可
;	範囲外での運転で、範囲を超えた時、みつけれなかった場合
	.GLOBAL	_INSERT_MOTION_DISENB

_INSERT_MOTION_DISENB
	SUB_START


	MOV.B	#BIT0,R0
	MOV.L	#_PVX_MOTINS_INF,R1					;ﾓｰｼｮﾝ挿入不可
	MOV.W	R0,@R1							;

	XOR	R0,R0							;
	MOV.L	#_PVX_MOTINS_DAN,R1					;
	MOV.W	R0,@R1							;

	XOR	R0,R0
	MOV.L	#_TECH_USED_F,R1					;演算ｲﾍﾞﾝﾄｸﾘｱ
	MOV.W	R0,@R1							;

	FAR_JSR	#_INSERT_MOTION_PV_MOV,R0				;

	SUB_END
	M_RTS


	.EXPORT	_INSERT_MOTCHK_SVCHG
_INSERT_MOTCHK_SVCHG
	SUB_START

	MOV.L	#_INSERT_MOT_SV_CHGF,R1
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF INSERT_MOTCK_SVCG100


	FAR_JSR	#_INSERT_MOTION_DISENB,R0	;

	MOV.L	#_INSERT_MOT_SV_CHGF,R1
	XOR	R0,R0				;
	MOV.W	R0,@R1				;

INSERT_MOTCK_SVCG100

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	加振動制御			***
;	***					***
;	***	2010-08-23			***
;	*******************************************
	.EXPORT	_VAIBU_CTRL
;;;;;;;;	.IMPORT	_IDO_BUF_SRC2B_TOTAL_4B_CAL


_VAIBU_CTRL:
	SUB_START

;	Input R2: NEW DATA
;	Input R5:TOTAL.ADR
;	Input R0:IDO BAF ADR
;	      R3:POINTER ADR
;	      R4:BUF CNT MAX
;;;;;;;;;;;;;;;移動	2015-04-09:KAJYUU_REFLASH
;;;;;;;;;;;;;;;移動	MOV.W	#D'200,R3			;DEBUG
;;;;;;;;;;;;;;;移動	MOV.W	#D'1000,R4			;5.000
;;;;;;;;;;;;;;;移動	MOV.W	#D'1800,R5			;
;;;;;;;;;;;;;;;移動	MOV.W	#D'1900,R6			;

;;;;;;;;;;;;;;;移動	MOV.L	#_PVPAB_KAJLIV_TTL,R1		;//荷重生（TON）(1word)
;;;;;;;;;;;;;;;移動	MOV.L	@R1,R2				;
;;;;;;;;;;;;;;;移動	MOV.L	#_KAJLIV_TTL_TOTAL,R5		;
;;;;;;;;;;;;;;;移動	MOV.L	#_KAJLIV_TTL_IDOBUF,R0		;//
;;;;;;;;;;;;;;;移動	MOV.L	#_KAJLIV_TTL_POINT,R3		;
;;;;;;;;;;;;;;;移動	MOV.W	#D'10,R4			;平均個数 MAX
;;;;;;;;;;;;;;;移動	FAR_JSR	#_IDO_BUF_SRC2B_TOTAL_4B_CAL,R1	;
;;;;;;;;;;;;;;;移動	MOV.L	#_WPVX_KAJLIV_TTL,R1		;
;;;;;;;;;;;;;;;移動	MOV.W	R2,@R1				;


;	------- 加振動制御開始指令------
	MOV.L	#_CB_SEQ_CB_COM349,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT3,R0			;
	TST_BIT_ON VAIBU_CTL_050		;
	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB205),LG=W,BIT=~(BIT6+BIT5),WKRG1=R1,WKRG2=R4	;
	XOR	R0,R0				;
	MOV.L	#_VIB_STEP_FLG,R1		;
	MOV.W	R0,@R1				;
	M_BRA	VAIBU_CTL_900			;


VAIBU_CTL_050:
;	--------------比較----------------------
	MOV.L	#_WPVX_KAJLIV_TTL,R1		;
	MOV.W	@R1,R2				;

	MOV.L	#_SET1_VIB_KJYU_TTL,R1		;
	MOV.W	@R1,R3				;
	EXTU.W	R3,R3				;
	CMP/GE	R3,R2				;
	BT	VAIBU_CTL_100
	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB205),LG=W,BIT=~(BIT5),WKRG1=R1,WKRG2=R4	;
	M_BRA	VAIBU_CTL_200									;
VAIBU_CTL_100
	MEM1_BIT0_F_ORSET MEM=(_SQ_CBWK_TOP+_WKSQCB205),LG=W,BIT=(BIT5),WKRG1=R1,WKRG2=R4	;
VAIBU_CTL_200


;	.GLOBAL	_VIB_STEP_FLG;//BIT0:停止ラッチ BIT1:TIMEUP BIT6:ﾀｲﾑｱｯﾌﾟ
;	.GLOBAL	_VIB_STEP_COM;//1:払い出し中 0:停止中
;	.GLOBAL	_VIB_GET_SET_TIM;
;	.GLOBAL	_VIB_USE_SET_TIM;//
;	.GLOBAL	_VIB_PV_UP_TIM;//
;

	MOV.L	#_VIB_STEP_COM,R1	;//1:払い出し中 0:停止中
	MOV.W	@R1,R0			;
	TST	#BIT0,R0		;
	TST_BIT_OF VAIBU_CTL_300	;ﾊﾟﾙｽ払い出ししていない()

;	---------ﾊﾟﾙｽ払い出し中は clr---------
	XOR	R0,R0			;
	MOV.L	#_VIB_STEP_FLG,R1	;
	MOV.W	R0,@R1			;
	MEM1_BIT0_F_ADCLR MEM=(_SQ_CBWK_TOP+_WKSQCB205),LG=W,BIT=~(BIT6),WKRG1=R1,WKRG2=R4	;
	M_BRA	VAIBU_CTL_900		;


VAIBU_CTL_300:
	MOV.L	#_VIB_STEP_FLG,R5	;BIT0=1 INITAL
	MOV.W	@R5,R0			;BIT1=1 DLY END
					;BIT2=1 FIRST DATA LOAD
	TST	#BIT0,R0		;BIT6=1 UP-ON
	TST_BIT_ON VAIBU_CTL_400	;

;	-------- INITAL ----------
	MOV.W	#BIT0,R0		;
	MOV.W	R0,@R5			;FLG=BIT0

	MOV.W	#D'50,R0		;
	MOV.L	#_VIB_DLY_TIM,R1	;DELAY TIM SET
	MOV.W	R0,@R1			;

VAIBU_CTL_400:
	MOV.W	@R5,R0			;
	TST	#BIT6,R0		;BIT6=1 UP-ON
	TST_BIT_ON VAIBU_CTL_900	;

	TST	#BIT1,R0		;BIT6=1 UP-ON
	TST_BIT_ON VAIBU_CTL_500	;

	MOV.L	#_VIB_DLY_TIM,R1				;DELAY TIM SET
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF VAIBU_CTL_450						;
	ADD	#-1,R2								;
	MOV.W	R2,@R1								;
	M_BRA	VAIBU_CTL_900							;
VAIBU_CTL_450:									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_VIB_STEP_FLG,LG=W,BIT=BIT1,WKREG=R4	;

VAIBU_CTL_500:

	MOV.L	#_CB_SEQ_CB_COM349,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT4,R0			;
	TST_BIT_ON VAIBU_CTL_550		;1:ﾃｰﾌﾞﾙ参照する指令
	M_BRA	VAIBU_CTL_700			;0:ﾃｰﾌﾞﾙ参照しない指令

VAIBU_CTL_550:

;	============ TABLE DATA MAKE START====
	MOV.L	#_WPVX_KAJLIV_TTL,R3		;実測荷重
	MOV.W	@R3,R2				;
	MOV.L	#_SET1_MAX_KJYU,R3		;2;
	MOV.W	@R3,R4				;
	EXTU.W	R4,R4				;
	MOV.W	#D'10,R1			;

	MOV.L	#_WPAR_KJYU_STOPTBL,R6		;0,1~9,10~19,20~29,,,,90~99,100

	TST	R2,R2				;
	TST_BIT_OF VAIBU_CTL_600		;PVdata=0%

	TST	R4,R4				;
	TST_BIT_OF VAIBU_CTL_560		;KAJYU_MAX=0 THEN 

	CMP/GE	R4,R2				;MAX =< R2
	BF	VAIBU_CTL_570			;NO
VAIBU_CTL_560:
	ADD	#D'11*2,R6			;
	M_BRA	VAIBU_CTL_600			;100%ﾃﾞｰﾀ

VAIBU_CTL_570:

	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;

	ADD	#2,R6				;TOP+2
	ADD	R2,R2				;0~9*2
	ADD	R2,R6				;
VAIBU_CTL_600					;
	MOV.W	@R6,R2				;msec data load
	MOV.L	#_VIB_GET_SET_TIM,R1
	MOV.W	R2,@R1				;

;	============ TABLE DATA R2=======
;	1回目の遅延後はﾃﾞｰﾀを入れる
	MOV.L	#_VIB_STEP_FLG,R5		;BIT0=1 INITAL
	MOV.W	@R5,R0				;BIT1=1 DLY END
	TST	#BIT2,R0			;BIT2=1
	TST_BIT_ON VAIBU_CTL_630		;
	OR	#BIT2,R0
	MOV.W	R0,@R5				;

	MOV.L	#_VIB_USE_SET_TIM,R1		;
	MOV.W	R2,@R1				;

	XOR	R0,R0				;
	MOV.L	#_VIB_PV_UP_TIM,R1		;
	MOV.W	R0,@R1				;

VAIBU_CTL_630:
	MOV.L	#_VIB_USE_SET_TIM,R1		;
	MOV.W	@R1,R3				;
	CMP/HS	R3,R2				;
	BT	VAIBU_CTL_650			;R3(USE)=<R2(NEW) THEN  EXIT
	MOV.W	R2,@R1				;TIMER SET
VAIBU_CTL_650:
;	----------- TIMER +1 ---------------
	MOV.L	#_VIB_PV_UP_TIM,R1	;
	MOV.W	@R1,R0			;
	ADD	#1,R0			;
	TST	R0,R0			;
	TST_BIT_OF VAIBU_CTL_670	;
	MOV.W	R0,@R1			;
VAIBU_CTL_670

	MOV.L	#_VIB_GET_SET_TIM,R1	;
	MOV.W	@R1,R2			;
	TST	R2,R2			;
	TST_BIT_OF VAIBU_CTL_900	;GET-TIME=0 THEN EXIT

	MOV.L	#_VIB_USE_SET_TIM,R1		;
	MOV.W	@R1,R3				;
	CMP/HS	R3,R0			;SV =< PV
	BT	VAIBU_CTL_700		;TIME UP
	M_BRA	VAIBU_CTL_900		;


VAIBU_CTL_700				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_VIB_STEP_FLG,LG=W,BIT=BIT6,WKREG=R4	;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_VIB_STEP_FLG,LG=W,BIT=~BIT2,WKREG=R4	;(荷重ﾃﾞｰﾀ参照済みｸﾘｱ)
	MEM1_BIT0_F_ORSET MEM=(_SQ_CBWK_TOP+_WKSQCB205),LG=W,BIT=(BIT6),WKRG1=R1,WKRG2=R4	;
VAIBU_CTL_900


	SUB_END
	M_RTS

	.EXPORT	_VIB_PLS_OUT_ON		;2010-08-23加振動制御
	.EXPORT	_VIB_PLS_OUT_OF		;2010-08-23加振動制御

;	*******************************************
;	***					***
;	***	起動:_FWD_REV_START		***
;	***					***
;	***					***
;	*******************************************
_VIB_PLS_OUT_ON
	SUB_START
	MOV.B	#BIT0,R0
	MOV.L	#_VIB_STEP_COM,R1	;//1:払い出し中 0:停止中
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	急停止:_EXQ_POS_FLG_PROC		***
;	***	ＥＭＧ:_EMG_POS_FLG_PROC		***
;	***	パルス出力停止:_PLS_LSI_CTL_CALC	***
;	***						***
;	***************************************************
;
_VIB_PLS_OUT_OF
	SUB_START

	XOR	R0,R0
	MOV.L	#_VIB_STEP_COM,R1	;//1:払い出し中 0:停止中
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS





;	*******************************************
;	***					***
;	***	2012-09-25			***
;	***					***
;	***	ｵｰﾊﾞﾋｰﾄ電流			***
;	***					***
;	*******************************************
;	---------------------------------------------------
;	---	オーバヒート電流	2012-09-25	---
;	---------------------------------------------------
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
	.EXPORT	_OVERH_MODE_DT_MAK		;
	.EXPORT	_SET_SQ224_11
	.EXPORT	_CLR_SQ224_11
	.AENDI

	.ALIGN	4			;
_OVERH_MODE_DT_MAK:
	SUB_START
	MOV.L	#_emg_err_flg,R1			;//異常ﾗｯﾁ
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_ON OVERH_MODE_DTMK050			;

	MOV.L	#_MODE_SEL,R1				;
	MOV.W	@R1,R0					;
	TST	#(_W1OPT+_W1CNT+_W1SGL+_W1INC),R0	;
	TST_BIT_OF OVERH_MODE_DTMK050			;

	MOV.L	#_BRKTST_INPUT_CMD,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON OVERH_MODE_DTMK050			;

	M_BRA	OVERH_MODE_DTMK080			;

OVERH_MODE_DTMK050:
	XOR	R0,R0
	MOV.L	#_OVERH_CALC_USE,R1	;//MODE,
	MOV.W	R0,@R1			;
	M_BRA	OVERH_MODE_DTMK700	;

OVERH_MODE_DTMK080:
	XOR	R2,R2
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_REVRSE,R0			;
	TST_BIT_ON OVERH_MODE_DTMK100			;
	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON OVERH_MODE_DTMK200			;
;回転	
	XOR	R5,R5
	MOV.L	#_RNA_STLORK,R1				;
	M_BRA	OVERH_MODE_DTMK400			;

;	------- 反転------
OVERH_MODE_DTMK100:
	MOV.W	#1,R5					;
	MOV.L	#_SETX_UPAREA_RNA,R1			;(内部で作成)
	M_BRA	OVERH_MODE_DTMK400			;

;	------- ふりこ------
OVERH_MODE_DTMK200:
	MOV.W	#2,R5					;
	MOV.L	#_SETX_UPAREA_RNA,R1			;(内部で作成)


OVERH_MODE_DTMK400:
	MOV.L	@R1,R2						;0.001mm
	MOV.W	#D'1000,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;


;	INPUT R5(MODE) R2(LENGTH 1mm)
OVERH_MODE_DTMK500:
	MOV.L	#_SETX_OVERH_LNGTH,R1	;//1mm Main->OVERH SOFT
	MOV.L	R2,@R1			;
	MOV.L	#_OVERH_MODE_SEL,R1	;//0[回転]/1[反転]/2[ふりこ]/3[ふりこ]
	MOV.W	R5,@R1			;

	MOV.W	#1,R0			;
	MOV.L	#_OVERH_CALC_USE,R1	;//MODE,
	MOV.W	R0,@R1			;


OVERH_MODE_DTMK700:






	SUB_END
	M_RTS

	.ALIGN	4			;
_SET_SQ224_11
	SUB_START
	MEM1_BIT0_F_ORSET MEM=_SQ_CBWK_TOP+_WKSQCB224,LG=W,BIT=(BIT11),WKRG1=R1,WKRG2=R4
	SUB_END
	M_RTS

	.ALIGN	4			;
_CLR_SQ224_11
	SUB_START
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB224,LG=W,BIT=~(BIT11),WKRG1=R1,WKRG2=R4
	SUB_END
	M_RTS
