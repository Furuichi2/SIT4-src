;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		振り子加速度演算		***
;	***						***
;	***						***
;	***						***
;	***************************************************
;	SSA_POS1.SRCにｲﾝｸﾙｰﾄﾞされる
_ACC_PER_V_MAX	.EQU	10000	;10000換算
_ACC_CALC_TIM	.EQU	1000	;1/1000msec
;
	.INCLUDE	"ssa_acrm.ext"		; //



	.IMPORT		_DNM_MAXSPM_ACCLAT_MAK		;2010-10-05


;//	*******************************************
;//	***		振り子加速		***
;//	*******************************************
;	***************************************************
;	***						***
;	***		ふりこ加速テーブル		***
;	***		パラメータに入れる		***
;	***						***
;	***************************************************
	.GLOBAL		_CB_SYS_PARTBL001	;CODE:ｺｰﾄﾞ存在なければﾃﾞｰﾀなし
	.GLOBAL		_CB_SYS_PARTBL002	;1:加速度ﾃｰﾌﾞﾙ使用NO.[1個より増えた場合用]
	.GLOBAL		_CB_SYS_PARTBL003	;1:最大回転速度/加減速時間ﾃｰﾌﾞﾙ使用[1個より増えた場合用]
	.GLOBAL		_CB_SYS_PARTBL004	;加速度ﾃｰﾌﾞﾙ1　<設定位置１未満
	.GLOBAL		_CB_SYS_PARTBL005	;加速度ﾃｰﾌﾞﾙ2　位置1≦＜位置2


;	***************************************************
;	***						***
;	***		mm-最大回転数,加減速時間	***
;	***						***
;	***************************************************
	.GLOBAL		_CB_SYS_DNMTBL1_CNT		;
	.GLOBAL		_CB_SYS_DNMTBL1_DATA_TOP	;
	.GLOBAL		_CB_SYS_ACCTBL1_CNT		;
	.GLOBAL		_CB_SYS_ACCTBL1_IN_TOP		;
	.GLOBAL		_CB_SYS_ACCTBL2_CNT		;
	.GLOBAL		_CB_SYS_ACCTBL2_IN_TOP		;
	.GLOBAL		_CB_SYS_ACCTBL3_CNT		;
	.GLOBAL		_CB_SYS_ACCTBL3_IN_TOP		;

	.import		_SYS2_DT_LOAD

;	***************************************************
;	***						***
;	***		速度テーブル			***
;	***						***
;	***************************************************
	.ALIGN	4						;
;;;;;	.INCLUDE	"ssa_atbl.inc"		;//2010-09-21

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA

	.IMPORT	_PDTRB
	.MACRO	_A_WDT_CLR
	PUSH_REG1 R10
	PUSH_REG1 R11
	PUSH_REG1 R12

	DI_PUSH_SR_SHn	WK_REG1=R10,WK_REG2=R11

	MOV.L	#_PDTRB,R10
	MOV.W	@R10,R11
	MOV.W	#NBIT2,R12		;;;;2012-10-18	MOV.W	#NBIT0,R12	; PORT18
	AND	R12,R11			;
	MOV.W	R11,@R10		;
	MOV.W	#BIT2,R12		;;;;2012-10-18	MOV.W	#BIT0,R12	;
	OR	R12,R11			;
	MOV.W	R11,@R10		;

	EI_POP_SR_SHn 			;

	POP_REG1 R12
	POP_REG1 R11
	POP_REG1 R10
	.ENDM

	.AELSE
;CPU-Bは5msecでたたいているから不要
	.MACRO	_A_WDT_CLR
	.ENDM


	.AENDI

;
;	_DNM_TBL_CALC:	ﾃｰﾌﾞﾙ作成[DTMK]
;	_DNM_START_ACC_CALC:API 起動 往路/復路CHANGE [POS1]
;	_DNM_STEP_ACC_CHANGE:API 工程切替 ;[POS1]
;	_DNM_SPD_CALC:速度演算→ACC算出,反映[POS1]
;


;	***************************************************
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***		振り子加速度テーブル作成	***
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***************************************************
;	dtmkにて演算(WDT-CLR必要)
	.ALIGN	4						;
_DNM_TBL_CALC:
	SUB_START

	FAR_JSR	#_CHK_DNM_SPEC_MOD1,R0		;
	TST	R0,R0
	TST_BIT_OF DNM_TBLCAL_200				;ふりこでない

	FAR_JSR	#_DNM_MOTION_DATA_MAK,R0			;振り子時
	MOV.W	#1,R0
	M_BRA	DNM_TBLCAL_300					;

DNM_TBLCAL_200:
	XOR	R0,R0
DNM_TBLCAL_300:
	MOV.L	#_DNM_ACC_CALFLG,R1				;//0/1
	MOV.W	R0,@R1						;



;	============ ﾃﾞﾊﾞｯｸ===========
 .AIF	_CB_CPU_SEL EQ	_CB_CPUA
	MOV.L	#_SH4_DNM_CALC_INFO,R1		;SH4 TO SH2 +SH4演算部
 .AELSE
	MOV.L	#_SH2_DNM_CALC_INFO,R1		;SH2 TO SH4 +SH2演算部
 .AENDI
	MOV.W	@R1,R0
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB258,R1	;258,328
	MOV.W	R0,@R1

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***		各データ作成CALL	***
;	***					***
;	*******************************************
;	速度演算結果 * 速度比率/100　･･･速度
;	ﾃｰﾌﾞﾙの距離を速度比率/100････残距離比較
;	残り距離*100/速度比率
;
;	[起動時に比率を取込む]
;
;	--------2015-03-15[ふりこの設定状態]

	.MACRO	DNM_INFO_SET SETCOD

	MOV.W	#\SETCOD,R0
 .AIF	_CB_CPU_SEL EQ	_CB_CPUA
	MOV.L	#_SH4_DNM_CALC_INFO,R1		;SH4 TO SH2 +SH4演算部
 .AELSE
	MOV.L	#_SH2_DNM_CALC_INFO,R1		;SH2 TO SH4 +SH2演算部
 .AENDI
	MOV.W	R0,@R1				;

	.ENDM

	.IMPORT	_SH4_DNM_CALC_INFO		;
	.IMPORT	_SH2_DNM_CALC_INFO		;


_DNM_MOTION_DATA_MAK:
	SUB_START



	XOR	R7,R7				;
	MOV.L	#_SVP_UPAREA_SPD0,R5		;基準速度(戻速度)
	MOV.L	#_SVX_UPAREA_SPD0OLD,R6		;
	FAR_JSR	#_DATA_CMP2B_R5R6_REF,R0	;


	MOV.W	#D'20,R3			;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R5		;
	MOV.L	#_SVX_OBJ_SPD_OLDTOP,R6		;

ACC_INFMAK1_DTCHGCHKLOP
	FAR_JSR	#_DATA_CMP2B_R5R6_REF,R0	;
	ADD	#-1,R3				;
	TST	R3,R3				;
	TST_BIT_ON ACC_INFMAK1_DTCHGCHKLOP	;
	TST	R7,R7				;
	TST_BIT_ON ACC_INFMAK1_START		;[速度設定変更有り]

	MOV.L	#_emg_err_flg,R1		;//異常ﾗｯﾁ
	MOV.W	@R1,R0				;
	MOV.L	#_exq_err_flg,R1		;//異常ﾗｯﾁ
	MOV.W	@R1,R2				;
	OR	R2,R0				;
	TST	R0,R0				;
	TST_BIT_ON ACC_INFMAK1_START050		;異常状態での演算

	FAR_JSR	#_API_SETACC_STS_CLR,R0		;

	M_BRA	ACC_INFMAK1_EXT			;

;	----------[CPUA/B間で演算完了状態であれば 反映して良い]--------
ACC_INFMAK1_START
	DNM_INFO_SET SETCOD=BIT0;	;演算中
	M_BRA	ACC_INFMAK1_START100		;

ACC_INFMAK1_START050:
	DNM_INFO_SET SETCOD=BIT1		;演算中

ACC_INFMAK1_START100:

	FAR_JSR	#_SYS2_DT_LOAD,R0			;


	FAR_JSR	#_ACC_STEP_INF_MAKE1,R0		;
						;_ACC_INF1_STEPSP01	;000%[前状態],050%[設定]
						;_ACC_INF1_STEP001	;BIT2=[0=加速/1=減速] 
						;
	FAR_JSR	#_ACC_TBL_MAKE1,R0		;


	DNM_INFO_SET SETCOD=BIT2		;演算すべき状態、演算結果を反映して良い状態

ACC_INFMAK1_EXT

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	*** 自分がBIT2=1で相手がBIT2=1またはBIT3=1	***
;	*** なら演算を反映する				***
;	***						***
;	***************************************************
;
;
	.EXPORT	_API_SETACC_INFO_GET
_API_SETACC_INFO_GET:
	SUB_START


 .AIF	_CB_CPU_SEL EQ	_CB_CPUA
	MOV.L	#_SH4_DNM_CALC_INFO,R5		;SH4 TO SH2 +SH4演算部
	MOV.L	#_SH2_DNM_CALC_INFO,R6		;SH2 TO SH4 +SH2演算部
	
 .AELSE
	MOV.L	#_SH2_DNM_CALC_INFO,R5		;SH2 TO SH4 +SH2演算部
	MOV.L	#_SH4_DNM_CALC_INFO,R6		;SH4 TO SH2 +SH4演算部
 .AENDI
	MOV.W	@R5,R0				;
	MOV.W	@R6,R2
	MOV	R2,R4
	OR	R0,R4

	TST	R4,R4				;
	TST_BIT_OF API_SETACC_INFOGET_CALOK2	;演算してもいいよ

	TST	#BIT2,R0			;自分がON
	TST_BIT_OF API_SETACC_INFOGET_CALNG	;

	MOV.B	#(BIT3+BIT2),R4			;
	TST	R4,R2				;
	TST_BIT_ON API_SETACC_INFOGET_CALOK1	;
	M_BRA	API_SETACC_INFOGET_CALNG	;


API_SETACC_INFOGET_CALOK1:
	MOV.B	#BIT0,R0			;演算しろ[完了にしてね！！]
	M_BRA	API_SETACC_INFOGET_CALEXT	;

API_SETACC_INFOGET_CALOK2:
	MOV.B	#BIT1,R0			;完了にしないでね
	M_BRA	API_SETACC_INFOGET_CALEXT

API_SETACC_INFOGET_CALNG:
	XOR	R0,R0
API_SETACC_INFOGET_CALEXT:
	
	SUB_END
	M_RTS

	.EXPORT	_API_SETACC_STS_END		;

_API_SETACC_STS_END:
	SUB_START

	DNM_INFO_SET SETCOD=BIT3		;演算終了した状態

	SUB_END
	M_RTS

;	----CLRはCPUAはCPUAとCPUBを行う-----------
_API_SETACC_STS_CLR:
	SUB_START
 .AIF	_CB_CPU_SEL EQ	_CB_CPUA
	MOV.L	#_SH4_DNM_CALC_INFO,R5		;SH4 TO SH2 +SH4演算部
	MOV.W	@R5,R0				;
	MOV.L	#_SH2_DNM_CALC_INFO,R6		;SH2 TO SH4 +SH2演算部
	MOV.W	@R6,R2				;
;;;;[本当はこっち]	MOV.B	#BIT3,R4
	MOV.B	#BIT2,R4			;ｽｷｬﾝﾃｽﾄ
	CMP/EQ	R4,R2				;(R2==R0 R0?BIT3　の論理は危険 )
	BF	API_SETACC_STSCLR_EXT		;
	CMP/EQ	R4,R0				;完了？
	BF	API_SETACC_STSCLR_EXT		;

	XOR	R0,R0				;IDEL
	MOV.W	R0,@R5				;
	MOV.W	R0,@R6				;

API_SETACC_STSCLR_EXT:
	
 .AENDI

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***		ステップINFOMATION	***
;	***					***
;	*******************************************


_ACC_STEP_INF_MAKE1:
	SUB_START


	MOV.L	#_SETX_POS_SDAT1_INF1,R14		;往路情報 long data(BIT1=0正/1逆, BIT0=0 速度停止)

	MOV.L	#_SETX_POS_STEP_MAX,R1			;//SETXは設定=1~10 戻り分+1してない
	MOV.W	@R1,R5					;
	ADD	#1,R5


	MOV.L	#_ACC_INF1_STEP001,R8			;BIT2=[0=加速/1=減速] 
							;BIT1=[0=正,1=逆]   
							;BIT0=[0=停/1=連続]

	MOV.L	#_ACC_INF1_STEPSP01,R9			;000%[前状態],050%[設定]

	XOR	R7,R7					;(前回速度)
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R10		;

ACC_STEPINF_MAK1_100LOP:					;


	MOV.W	@R10+,R2				;

	MOV.W	#1,R4					;
	CMP/EQ	R4,R5					;"残りｽﾃｯﾌﾟ数=1"(戻りﾃﾞｰﾀ)
	BF	ACC_STEPINF_MAK1_120			;
	MOV.L	#_SVP_UPAREA_SPD0,R1			;0.1%　戻り速度
	MOV.W	@R1,R2					;
ACC_STEPINF_MAK1_120:
	FAR_JSR	#_R2_MUL10_ANS_R2,R1			;


;R7=0,R2=sv

	MOV.L	@R14+,R0				;
	AND	#LOW ~BIT2,R0				;

	CMP/EQ	R7,R2					;R7(OLD)==R2
	BF	ACC_STEPINF_MAK1_180			;NO

;	====== 速度が同じ場合、前の段の加速・減速情報を使用する
	ADD	#-2,R8					;
	MOV.W	@R8+,R1					;
	MOV.W	#BIT2,R4				;
	TST	R4,R1					;
	TST_BIT_OF ACC_STEPINF_MAK1_200			;
	OR	#BIT2,R0				;
	M_BRA	ACC_STEPINF_MAK1_200			;



ACC_STEPINF_MAK1_180:					;
	CMP/GE	R7,R2					;R7(OLD)=<R2
	TST_BIT_OF ACC_STEPINF_MAK1_200			;加速JUMP
	OR	#BIT2,R0				;
ACC_STEPINF_MAK1_200:					;
	MOV.W	R0,@R8					;BIT2,BIT1,BIT0 SAVE
	ADD	#2,R8					;

	MOV.W	R7,@R9					;OLD
	ADD	#2,R9					;
	MOV.W	R2,@R9					;TARGET
	ADD	#2,R9					;


	TST	#BIT0,R0				;
	TST_BIT_ON ACC_STEPINF_MAK1_250			;BIT0=0(停止) NO! JUMP
	XOR	R2,R2					;
ACC_STEPINF_MAK1_250:					;
	MOV	R2,R7					;
	ADD	#-1,R5					;
	TST	R5,R5					;
	TST_BIT_OF ACC_STEPINF_MAK1_300			;
	M_BRA	ACC_STEPINF_MAK1_100LOP			;

ACC_STEPINF_MAK1_300:					;

	SUB_END
	M_RTS


_R2_MUL10_ANS_R2:
	SUB_START
	PUSH_REG1 R1
	MOV.W	#D'10,R1	;
	DMULS.L	R1,R2		;
	STS	MACL,R2		;
	POP_REG1 R1
	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***	振り子加速度テーブル作成		***
;	***						***
;	***						***
;	***						***
;	***************************************************
;	256個　0番目=0と255番目=10000とすること
;;_ACC_IN_TBL_TIM	.DATA.W		255		;255msec時間 ループ数は256
;;_ACC_IN_TBL_TIM	.DATA.W		50		;255msec時間 ループ数は256
;
;
;	演算タイミングは
;			「速度設定変更時」
;			「非常停止時」
;			「起動中」
;
;
_ACC_TBL_MAKE1
	SUB_START



;;;;2013-02-05[移動]	FAR_JSR	#_USE_IN_TBL_MOV,R0		;2010-10-20
;;;;2013-02-05[移動];	---------<<<<<加減速時間 1~1000>>>>>-----------
;;;;2013-02-05[移動]	MOV.L	#_TBL_ANS_ACCTIM,R1				;2010-10-25
;;;;2013-02-05[移動]	MOV.W	@R1,R2						;
;;;;2013-02-05[移動]	TST	R2,R2
;;;;2013-02-05[移動]	TST_BIT_ON ACC_TBLMAK1_DTCHK050				;
;;;;2013-02-05[移動]	MOV.W	#1,R2						;
;;;;2013-02-05[移動]ACC_TBLMAK1_DTCHK050						;
;;;;2013-02-05[移動]	MOV.W	#D'1000,R0					;
;;;;2013-02-05[移動]	CMP/HS	R2,R0						;
;;;;2013-02-05[移動]	BT	ACC_TBLMAK1_DTCHK100				;
;;;;2013-02-05[移動]	MOV	R0,R2						;1msec~1000でﾘﾐｯﾄ
;;;;2013-02-05[移動]ACC_TBLMAK1_DTCHK100						;
;;;;2013-02-05[移動]	MOV.L	#_ACCB_ACCLAT_TIM1,R1				;
;;;;2013-02-05[移動]	MOV.W	R2,@R1						;


;;;[2013-05-20 前から未使用];	-----------------------------------------------------------
;;;[2013-05-20 前から未使用];	---							---
;;;[2013-05-20 前から未使用];	---	BASE(0%->100%=100%→0% 最終減速)ﾃﾞｰﾀの作成	---
;;;[2013-05-20 前から未使用];	---							---
;;;[2013-05-20 前から未使用];	-----------------------------------------------------------
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];	-------------- BASE(0~100.00%の加速時間,速度ﾃｰﾌﾞﾙ作成)---------------
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_IN_TBLUSE,R11				;元ﾃｰﾌﾞﾙADR(2byte)
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_IN_TBL_TIM,R1				;255msec ﾙｰﾌﾟは256回
;;;[2013-05-20 前から未使用]	MOV.W	@R1,R12						;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.L	#_ACCB_ACCLAT_TIM1,R1				;_SET1_ACCLAT_TIM1
;;;[2013-05-20 前から未使用]	MOV.W	@R1,R7						;R7=最大加速時間
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.W	#0,R8						;R8:BASE SPEED速度
;;;[2013-05-20 前から未使用]	MOV.W	#_ACC_PER_V_MAX,R9				;R9:目標速度
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_STPVTBL,R13			;R13:速度格納用//
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_STPVTBL,R5			;(このｹｰｽでは不要)前の段の速度-RAM
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_ACCTM,R14				;R14:加減速時間
;;;[2013-05-20 前から未使用]								;
;;;[2013-05-20 前から未使用]								;R5:前の段の速度-RAM
;;;[2013-05-20 前から未使用]								;R7:最大加減速時間
;;;[2013-05-20 前から未使用]								;R8:OLD-SPD
;;;[2013-05-20 前から未使用]								;R9:TARGET
;;;[2013-05-20 前から未使用]	MOV	R7,R10						;2013-05-20 R10:(前段の加速時間/PLS TABLE用/)
;;;[2013-05-20 前から未使用]								;R11:SRC - SPD TABLE
;;;[2013-05-20 前から未使用]								;R12:SRC - 時間
;;;[2013-05-20 前から未使用]								;<R13:Output - SPD RAM>
;;;[2013-05-20 前から未使用]								;<R14:Output - ACC RAM>
;;;[2013-05-20 前から未使用]								
;;;[2013-05-20 前から未使用]	PUSH_ALL						;
;;;[2013-05-20 前から未使用]	FAR_JSR	#_ACC_TBL_MAKSPD1_SUB,R0			;
;;;[2013-05-20 前から未使用]	POP_ALL							;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];	-------------- BASE(速度ﾃｰﾌﾞﾙ作成→ﾊﾟﾙｽﾃｰﾌﾞﾙ作成)-----------
;;;[2013-05-20 前から未使用]	MOV.L	#_LINK_MAX_SPD_PLS,R1				;
;;;[2013-05-20 前から未使用]	MOV.L	@R1,R6						;
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_STPPTBL,R10			;
;;;[2013-05-20 前から未使用]								;R6=MAX pls/s
;;;[2013-05-20 前から未使用]								;R13=_ACC_BASEDAT_STPVTBL
;;;[2013-05-20 前から未使用]								;R14=_ACC_BASEDAT_ACCTM
;;;[2013-05-20 前から未使用]								;R10=_ACC_BASEDAT_STPPTBL
;;;[2013-05-20 前から未使用]	FAR_JSR	#_ACC_TBL_MAKPLS1_SUB,R0			;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];	-------- 2013-02-25 ﾃﾞｰﾀﾁｪｯｸ及び金型ﾀｯﾁ用 ----------
;;;[2013-05-20 前から未使用]	MOV.L	#_DNM_MAX_GENSOK_LENGTH,R1			;//100%時→0時の減速距離
;;;[2013-05-20 前から未使用]	MOV.L	R7,@R1						;


								;

;	-----------------------------------------------------------
;	---							---
;	---	1段目Data(old-sv%->sv%)ﾃﾞｰﾀの作成		---
;	---	1段目Data(0%->sv%)ﾃﾞｰﾀの作成[再起動,減速用]	---
;	---							---
;	-----------------------------------------------------------
	MOV.L	#_ACC_STEP01_TBL_TOP,R0				;
	LDC	R0,GBR						;
	FAR_JSR	#_ACC_INFO_CHNAGE_TBL_MAK,R0			;

;	-----------------------------------------------------------
;	---							---
;	---	2段目Data(old-sv%->sv%)ﾃﾞｰﾀの作成		---
;	---	2段目Data(0%->sv%)ﾃﾞｰﾀの作成[再起動,減速用]	---
;	---							---
;	-----------------------------------------------------------
	MOV.L	#_SETX_POS_STEP_MAX,R1			;//SETXは設定=1~10 戻り分+1してない
	MOV.W	@R1,R5						;
	ADD	#1,R5

	MOV.L	#_ACC_TBL_CAL_IN_TOP,R6				;
	MOV.L	@R6+,R0						;1段目分
	ADD	#-1,R5						;

ACC_TBLMAK1_200LOP
	MOV.L	@R6+,R0						;
	PUSH_REG1 R5
	PUSH_REG1 R6

	LDC	R0,GBR						;
	FAR_JSR	#_ACC_INFO_CHNAGE_TBL_MAK,R0			;

	POP_REG1 R6
	POP_REG1 R5
	ADD	#-1,R5
	TST	R5,R5						;
	TST_BIT_ON ACC_TBLMAK1_200LOP				;



	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	加速度パターン選択+転送		***
;	***					***
;	*******************************************
_USE_IN_TBL_MOV:
	SUB_START


;	-----------------------------------------------
;;;;2013-02-05	MOV.L	#_TBL_ANS_ACC_SEL,R1				;(0,1),2[TBL2],3[TBL3]
;;;;2013-02-05	MOV.W	@R1,R0						;
;;;;2013-02-05
;;;;2013-02-05
;;;;2013-02-05
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL3_CNT,R7				;
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL3_IN_TOP,R5			;
;;;;2013-02-05
;;;;2013-02-05	CMP/EQ	#3,R0						;
;;;;2013-02-05	BT	USE_IN_TBLMV_100				;
;;;;2013-02-05
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL2_CNT,R7				;
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL2_IN_TOP,R5
;;;;2013-02-05	CMP/EQ	#2,R0						;
;;;;2013-02-05	BT	USE_IN_TBLMV_100				;
;;;;2013-02-05
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL1_CNT,R7				;
;;;;2013-02-05	MOV.L	#_CB_SYS_ACCTBL1_IN_TOP,R5			;
;;;;2013-02-05
;;;;2013-02-05	USE_IN_TBLMV_100:

	MOV.L	#_CB_SYS_ACCTBL1_CNT,R7				;
	MOV.L	#_CB_SYS_ACCTBL1_IN_TOP,R5			;
	MOV.W	@R7,R3						;
	MOV.L	#_ACC_IN_TBL_TIM,R1				;255msec ﾙｰﾌﾟは256回
	MOV.W	R3,@R1						;
	ADD	#2,R3						;

	MOV.L	#_ACC_IN_TBLUSE,R6				;元ﾃｰﾌﾞﾙADR(2byte)

USE_IN_TBLMV_100LOP:
	TST	R3,R3
	TST_BIT_OF USE_IN_TBLMV_500
	MOV.W	@R5+,R0
	MOV.W	R0,@R6
	ADD	#2,R6				;
	ADD	#-1,R3				;
	M_BRA	USE_IN_TBLMV_100LOP		;
	
USE_IN_TBLMV_500:

	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***		INFO->TABLE			***
;	***						***
;	***************************************************
;	Input GBR
_ACC_INFO_CHNAGE_TBL_MAK:
	SUB_START
	MOV.L	@(AFM_SRC_TBL_TOP-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R11						;ACC_IN_TBL1;元ﾃｰﾌﾞﾙADR(2byte)

	MOV.L	@(AFM_SRC_TBL_MEM-ACC_FORM_TOP,GBR),R0		;
	MOV.W	@R0,R12						;_ACC_IN_TBL_TIM

	MOV.L	#_ACCB_ACCLAT_TIM1,R1				;_SET1_ACCLAT_TIM1
	MOV.W	@R1,R7						;R7=最大加速時間

	MOV.L	@(AFM_STEP_INF_SPD-ACC_FORM_TOP,GBR),R0		;
	MOV.W	@R0+,R8						;R8:BASE SPEED速度
	MOV.W	@R0,R9						;R9:目標速度

	MOV.L	@(AFM_OLD_CTLVTBL-ACC_FORM_TOP,GBR),R0		;前段の速度TBL(前段=現段速度時使用)
	MOV	R0,R5						;
	MOV.L	@(AFM_DST_CTLVTBL-ACC_FORM_TOP,GBR),R0		;今回の速度格納用
	MOV	R0,R13						;

	MOV.L	@(AFM_DST_CTLACTM-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R14						;今回の加速時間格納用

	MOV.L	@(AFM_OLD_CTLACTM-ACC_FORM_TOP,GBR),R0		;2013-05-20 
	MOV.W	@R0,R10						;注意　前段の加速時間(前段=現段速度時使用)



	PUSH_ALL						;
	FAR_JSR	#_ACC_TBL_MAKSPD1_SUB,R0			;X%(OLD)->Y%(NEW:ﾀｰｹﾞｯﾄ作成)ANS R13,R14
	POP_ALL							;


;	-----------------(停止演算 0->設定% 速度)--------
	XOR	R8,R8						;0(R8)--設定(R9)
	MOV.L	@(AFM_OLD_STPVTBL-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R5						;(暴走対策/ありえない)
	MOV.L	@(AFM_DST_STPVTBL-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R13						;
	MOV.L	@(AFM_DST_STPACTM-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R14						;

	MOV.L	@(AFM_OLD_STPACTM-ACC_FORM_TOP,GBR),R0		;2013-05-20 
	MOV.W	@R0,R10						;注意　前段の加速時間(前段=現段速度時使用)

	PUSH_ALL						;
	FAR_JSR	#_ACC_TBL_MAKSPD1_SUB,R0			;0%->Y%(NEW:ﾀｰｹﾞｯﾄ作成)ANS R13,R14
	POP_ALL							;


;	---------------(停止演算 0->設定% pls)--------
;	-------------- (速度ﾃｰﾌﾞﾙ作成→ﾊﾟﾙｽﾃｰﾌﾞﾙ作成)-----------
	MOV.L	#_LINK_MAX_SPD_PLS,R1				;
	MOV.L	@R1,R6						;
	MOV.L	@(AFM_DST_STPPTBL-ACC_FORM_TOP,GBR),R0		;
	MOV	R0,R10						;
								;
								;R6=MAX pls/s
								;R13=_ACC_****_STPVTBL(ﾃﾞｰﾀ元)
								;R14=_ACC_****_ACTM(LOOP個数)
								;R10=_ACC_****_STPPTBL ANS
	FAR_JSR	#_ACC_TBL_MAKPLS1_SUB,R0			;

	SUB_END
	M_RTS




	.ALIGN	4					;
_ACC_TBL_CAL_IN_TOP
	.DATA.L	_ACC_STEP01_TBL_TOP
	.DATA.L	_ACC_STEP02_TBL_TOP
	.DATA.L	_ACC_STEP03_TBL_TOP
	.DATA.L	_ACC_STEP04_TBL_TOP
	.DATA.L	_ACC_STEP05_TBL_TOP
	.DATA.L	_ACC_STEP06_TBL_TOP
	.DATA.L	_ACC_STEP07_TBL_TOP
	.DATA.L	_ACC_STEP08_TBL_TOP
	.DATA.L	_ACC_STEP09_TBL_TOP
	.DATA.L	_ACC_STEP10_TBL_TOP
	.DATA.L	_ACC_STEP11_TBL_TOP



	.ALIGN	4					;
_ACC_STEP01_TBL_TOP
ACC_FORM_TOP
AFM_SRC_TBL_TOP		.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
AFM_SRC_TBL_MEM		.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
AFM_STEP_INF_SPD	.DATA.L		_ACC_INF1_STEPSP01	;[03]000%[前状態],050%[設定]
AFM_STEP_INF_FLG	.DATA.L		_ACC_INF1_STEP001	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
AFM_OLD_CTLVTBL		.DATA.L		_ACC_STEP001_VTBL	;[05]前回速度(前段=現段速度)1段では使用しない
AFM_OLD_CTLACTM		.DATA.L		_ACC_STEP001_ACTM	;[06]前回時間(前段=現段速度)1段では使用しない
AFM_DST_CTLVTBL		.DATA.L		_ACC_STEP001_VTBL	;[07]
AFM_DST_CTLACTM		.DATA.L		_ACC_STEP001_ACTM	;[08]
AFM_OLD_STPVTBL		.DATA.L		_ACC_STOP001_VTBL	;[09]前回速度(前段=現段速度)1段では使用しない
AFM_OLD_STPACTM		.DATA.L		_ACC_STOP001_ACTM	;[10]前回時間(前段=現段速度)1段では使用しない
AFM_DST_STPVTBL		.DATA.L		_ACC_STOP001_VTBL	;[11]
AFM_DST_STPACTM		.DATA.L		_ACC_STOP001_ACTM	;[12]
AFM_DST_STPPTBL		.DATA.L		_ACC_STOP001_PTBL	;[13]



_ACC_STEP02_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP02	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP002	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP001_VTBL	;[05]前回速度(前段=現段速度)
	.DATA.L		_ACC_STEP001_ACTM	;[06]前回時間(前段=現段速度)
	.DATA.L		_ACC_STEP002_VTBL	;[07]
	.DATA.L		_ACC_STEP002_ACTM	;[08]
	.DATA.L		_ACC_STOP001_VTBL	;[09]前回速度(前段=現段速度)
	.DATA.L		_ACC_STOP001_ACTM	;[10]前回時間(前段=現段速度)
	.DATA.L		_ACC_STOP002_VTBL	;[11]
	.DATA.L		_ACC_STOP002_ACTM	;[12]
	.DATA.L		_ACC_STOP002_PTBL	;[13]

_ACC_STEP03_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP03	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP003	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP002_VTBL	;[05]
	.DATA.L		_ACC_STEP002_ACTM	;[06]
	.DATA.L		_ACC_STEP003_VTBL	;[07]
	.DATA.L		_ACC_STEP003_ACTM	;[08]
	.DATA.L		_ACC_STOP002_VTBL	;[09]
	.DATA.L		_ACC_STOP002_ACTM	;[10]
	.DATA.L		_ACC_STOP003_VTBL	;[11]
	.DATA.L		_ACC_STOP003_ACTM	;[12]
	.DATA.L		_ACC_STOP003_PTBL	;[13]

_ACC_STEP04_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP04	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP004	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP003_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP003_ACTM	;[06]
	.DATA.L		_ACC_STEP004_VTBL	;[07]
	.DATA.L		_ACC_STEP004_ACTM	;[08]
	.DATA.L		_ACC_STOP003_VTBL	;[09]
	.DATA.L		_ACC_STOP003_ACTM	;[10]
	.DATA.L		_ACC_STOP004_VTBL	;[11]
	.DATA.L		_ACC_STOP004_ACTM	;[12]
	.DATA.L		_ACC_STOP004_PTBL	;[13]


_ACC_STEP05_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP05	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP005	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP004_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP004_ACTM	;[06]
	.DATA.L		_ACC_STEP005_VTBL	;[07]
	.DATA.L		_ACC_STEP005_ACTM	;[08]
	.DATA.L		_ACC_STOP004_VTBL	;[09]
	.DATA.L		_ACC_STOP004_ACTM	;[10]
	.DATA.L		_ACC_STOP005_VTBL	;[11]
	.DATA.L		_ACC_STOP005_ACTM	;[12]
	.DATA.L		_ACC_STOP005_PTBL	;[13]

_ACC_STEP06_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP06	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP006	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP005_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP005_ACTM	;[06]
	.DATA.L		_ACC_STEP006_VTBL	;[07]
	.DATA.L		_ACC_STEP006_ACTM	;[08]
	.DATA.L		_ACC_STOP005_VTBL	;[09]
	.DATA.L		_ACC_STOP005_ACTM	;[10]
	.DATA.L		_ACC_STOP006_VTBL	;[11]
	.DATA.L		_ACC_STOP006_ACTM	;[12]
	.DATA.L		_ACC_STOP006_PTBL	;[13]

_ACC_STEP07_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP07	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP007	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP006_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP006_ACTM	;[06]
	.DATA.L		_ACC_STEP007_VTBL	;[07]
	.DATA.L		_ACC_STEP007_ACTM	;[08]
	.DATA.L		_ACC_STOP006_VTBL	;[09]
	.DATA.L		_ACC_STOP006_ACTM	;[10]
	.DATA.L		_ACC_STOP007_VTBL	;[11]
	.DATA.L		_ACC_STOP007_ACTM	;[12]
	.DATA.L		_ACC_STOP007_PTBL	;[13]

_ACC_STEP08_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP08	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP008	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP007_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP007_ACTM	;[06]
	.DATA.L		_ACC_STEP008_VTBL	;[07]
	.DATA.L		_ACC_STEP008_ACTM	;[08]
	.DATA.L		_ACC_STOP007_VTBL	;[09]
	.DATA.L		_ACC_STOP007_ACTM	;[10]
	.DATA.L		_ACC_STOP008_VTBL	;[11]
	.DATA.L		_ACC_STOP008_ACTM	;[12]
	.DATA.L		_ACC_STOP008_PTBL	;[13]

_ACC_STEP09_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP09	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP009	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP008_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP008_ACTM	;[06]
	.DATA.L		_ACC_STEP009_VTBL	;[07]
	.DATA.L		_ACC_STEP009_ACTM	;[08]
	.DATA.L		_ACC_STOP008_VTBL	;[09]
	.DATA.L		_ACC_STOP008_ACTM	;[10]
	.DATA.L		_ACC_STOP009_VTBL	;[11]
	.DATA.L		_ACC_STOP009_ACTM	;[12]
	.DATA.L		_ACC_STOP009_PTBL	;[13]

_ACC_STEP10_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP10	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP010	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP009_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP009_ACTM	;[06]
	.DATA.L		_ACC_STEP010_VTBL	;[07]
	.DATA.L		_ACC_STEP010_ACTM	;[08]
	.DATA.L		_ACC_STOP009_VTBL	;[09]
	.DATA.L		_ACC_STOP009_ACTM	;[10]
	.DATA.L		_ACC_STOP010_VTBL	;[11]
	.DATA.L		_ACC_STOP010_ACTM	;[12]
	.DATA.L		_ACC_STOP010_PTBL	;[13]

_ACC_STEP11_TBL_TOP
	.DATA.L		_ACC_IN_TBLUSE		;[01]元ﾃｰﾌﾞﾙADR(2byte)
	.DATA.L		_ACC_IN_TBL_TIM		;[02]255msec WOD
	.DATA.L		_ACC_INF1_STEPSP11	;[03]000%[前状態],050%[設定]
	.DATA.L		_ACC_INF1_STEP011	;[04]//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
	.DATA.L		_ACC_STEP010_VTBL	;[05](STEP1では使用しない)
	.DATA.L		_ACC_STEP010_ACTM	;[06]
	.DATA.L		_ACC_STEP011_VTBL	;[07]
	.DATA.L		_ACC_STEP011_ACTM	;[08]
	.DATA.L		_ACC_STOP010_VTBL	;[09]
	.DATA.L		_ACC_STOP010_ACTM	;[10]
	.DATA.L		_ACC_STOP011_VTBL	;[11]
	.DATA.L		_ACC_STOP011_ACTM	;[12]
	.DATA.L		_ACC_STOP011_PTBL	;[13]










;	***********************************************************
;	***							***
;	***	振り子加速度テーブル作成SUB1			***
;	***							***
;	***	速度のみを算出する				***
;	***	ﾃﾞｰﾀ元ﾃｰﾌﾞﾙ→最大加速時間と速度の変化量から	***
;	***	加速時間と速度ﾃｰﾌﾞﾙを求める			***
;	***	[完成済み]					***
;	***							***
;	***********************************************************
;	input    R5:前段のOUTPUT-TABLE-TOP
;	Input	R11:BASE-TABLE-TOP         :ﾃｰﾌﾞﾙは1~1000または1~255まで使用する。
;	Input	R12:BASE-TABLE-時間 1000(ROM),255(ROM),設定(1~1000)加減速時間
;	Input   R13:OUTPUT-TABLE-TOP       :
;	Input   R14:OUTPUT-ACC時間　　　　 :加減速時間
;
;	Input   R7 :最大加減速時間
;	Input   R8:BASE  -SPD
;	Input   R9:TARGET-SPD  BASE=< TARGET SPD
;		(R10:ﾊﾟﾙｽﾃｰﾌﾞﾙ)
;	Output ﾃｰﾌﾞﾙに速度を周波数で記述
;	[1ﾃｰﾌﾞﾙ作成前にWDTを叩く]
;
;	・速度は0.01%で扱う
;
_ACC_TBL_MAKSPD1_SUB
	SUB_START
	_A_WDT_CLR				;



	CMP/GT	R8,R9				;R8[前段]<R9[今回]
	BT	ACC_TBLMKSPD1_SB100
	MOV	R8,R0				;
	MOV	R9,R8				;
	MOV	R0,R9				;
ACC_TBLMKSPD1_SB100:				;
	SUB	R8,R9				;R9=R9-R8
	TST	R9,R9				;
	TST_BIT_ON ACC_TBLMKSPD1_SB200		;

;	----速度が同じ場合、前段の速度データをＣＯＰＹする---
	MOV	R7,R3				;最大時間1000
	ADD	#1,R3				;ﾙｰﾌﾟ数は1001個ﾙｰﾌﾟ
ACC_TBLMKSPD1_SB150:				;
	MOV.W	@R5+,R0				;前段ﾃｰﾌﾞﾙ速度
	MOV.W	R0,@R13				;今回ﾃｰﾌﾞﾙ速度
	ADD	#2,R13				;
	ADD	#-1,R3				;
	TST	R3,R3				;(2013-05-15 COPY されていない)
	TST_BIT_ON ACC_TBLMKSPD1_SB150		;

	MOV.W	R10,@R14			;前段の加速時間を今回に使用
	M_BRA	ACC_TBLMKSPD1_SB900		;

ACC_TBLMKSPD1_SB200:				;
	MOV	R7,R2				;最大時間
	MOV	R9,R1				;変化率
	MOV.W	#_ACC_PER_V_MAX,R4		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;
	MOV	R2,R4

	TST	R4,R4				;
	TST_BIT_ON ACC_TBLMKSPD1_SB220		;
	ADD	#1,R4				;
ACC_TBLMKSPD1_SB220:				;
	MOV.W	R4,@R14				;時間

;	R8はオフセット速度
;	R9は変化率
;	@R14=R4=時間　+すればﾙｰﾌﾟ回数1

	MOV	R4,R3				;R4:減速時間
	ADD	#1,R3				;

	XOR	R2,R2				;Tx

ACC_TBLMKSPD1_SB250LOP:				;
	TST	R3,R3				;
	TST_BIT_OF ACC_TBLMKSPD1_SB500		;
	PUSH_REG1 R2


	MOV	R12,R1				;R12 ﾃﾞｰﾀ元側MAX時間

	PUSH_REG1 R4				;R4 ﾃﾞｰﾀ格納側MAX時間
;R2*R1/R4 =data･･･MOD
	DMULS.L	R2,R1						;
	STS	MACL,R2						;
	FAR_JSR	#_FPU_DIVS_32REG2_DIV_32REG4_R2_MOD_R1,R0	;R2...R1

	MOV	R11,R5				;ﾃﾞｰﾀ元側 TOP
	ADD	R2,R5				;TOP+NUM*2byte
	ADD	R2,R5				;
	MOV.W	@R5+,R6				;Fn[]

	CMP/HI	R2,R12				;
	BT	ACC_TBLMKSPD1_SB300		;
	ADD	#-2,R5				;
ACC_TBLMKSPD1_SB300:				;
	MOV.W	@R5,R2				;Fn+1
	SUB	R6,R2				;R2=(Fn+1 -Fn )
	POP_REG1 R4				;


	PUSH_REG1 R4				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;[R2](Fn+1 -Fn ) * [R1]MOD/[R4]格納側Tmax
	ADD	R6,R2				;R2速度

	MOV	R9,R1				;
	MOV.W	#_ACC_PER_V_MAX,R4		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;[R2](速度) * [R1]変化率/[R4]100.00
	POP_REG1 R4				;

	ADD	R8,R2				;+ｵﾌｾｯﾄ

	MOV.W	R2,@R13				;速度SAVE

	POP_REG1 R2
	ADD	#2,R13				;
	ADD	#-1,R3				;
	ADD	#1,R2				;
	M_BRA	ACC_TBLMKSPD1_SB250LOP		;

ACC_TBLMKSPD1_SB500:				;
	NOP					;

ACC_TBLMKSPD1_SB900:				;
	_A_WDT_CLR				;
	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***	振り子加速度テーブル作成SUB1		***
;	***						***
;	***	速度テーブルをパルスに変換する		***
;	***	[完成済み]				***
;	***************************************************
;	Input   R6:最大周波数　PLS/Sec
;	Input   R13:V-TABLE-TOP
;	Input   R14:加減速時間-MEM WORD: ﾙｰﾌﾟ数は0番目を含むから+1回
;	Input   R10:ﾊﾟﾙｽﾃｰﾌﾞﾙ
;
_ACC_TBL_MAKPLS1_SUB
	SUB_START
	_A_WDT_CLR					;

	MOV.W	@R14,R5						;時間
	ADD	#1,R5						;LOOPは+1

	XOR	R7,R7						;積算数 500,000HZ/1000*1000=4byte
	MOV	R6,R1						;data(0~10000) *500,000/(10000*1/1000(msec)
	MOV.L	#_ACC_PER_V_MAX*_ACC_CALC_TIM,R4		;

ACC_TBLMKPLS1_SBLOP200
	TST	R5,R5				;
	TST_BIT_OF ACC_TBLMKPLS1_SB_END		;
	MOV.W	@R13+,R2			;V% LOAD
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;V%*FREQ/100.00% *1/1000=deltV
						;R2(10000)*500000 8BYTE






;;	ADD	#1,R2				;(1ﾊﾟﾙｽはMOD分･･最大1000ﾊﾟﾙｽ程度の+側に誤差がでる)
	TST	R2,R2
	TST_BIT_ON ACC_TBLMKPLS1_SBLOP220	;
	ADD	#1,R2
ACC_TBLMKPLS1_SBLOP220

	ADD	R2,R7				;S=S+deltV
	MOV.L	R7,@R10				;
	ADD	#4,R10				;

	ADD	#-1,R5
	M_BRA	ACC_TBLMKPLS1_SBLOP200		;


ACC_TBLMKPLS1_SB_END

	SUB_END
	M_RTS









;	***************************************************
;	***						***
;	***						***
;	***						***
;	***		振り子API			***
;	***						***
;	***						***
;	***************************************************
;	サイクル開始(往路/復路),停止からの起動,タイマ停止からの起動
_DNM_START_ACC_CALC:
	SUB_START

	XOR	R0,R0
	MOV.L	#_ACC_STEP_POINT,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_ACC_STEP_FLG,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_ACC_STR_STEP,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_ACC_CTRL_STS1,R1		;
	MOV.W	R0,@R1			;

;	---- 2010-09-29---
	XOR	R0,R0
	MOV.L	#_ACC_LAST_POINT,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_ACC_STOP_POINT,R1	;
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS

;	工程切替
_DNM_STEP_ACC_CHANGE:
	SUB_START

	MOV.L	#_INT_POS_CTL_STEP,R1	;//内部制御工程1~11
	MOV.W	@R1,R0			;
	TST	R0,R0
	TST_BIT_OF DNM_STEP_ACC_CHG_100	;WHY

	MOV.L	#_ACC_POS_STEP,R1	;
	MOV.W	@R1,R2			;
	MOV.W	R0,@R1			;
	CMP/EQ	R0,R2			;
	BT	DNM_STEP_ACC_CHG_100	;変更なし
	MOV.L	#_ACC_STR_STEP,R1	;
	MOV.W	R0,@R1			;

	cmp/eq	#1,r0			;
	BF	DNM_STEP_ACC_CHGDBG10
	NOP
DNM_STEP_ACC_CHGDBG10:
	cmp/eq	#2,r0			;
	BF	DNM_STEP_ACC_CHGDBG20	;
	NOP
DNM_STEP_ACC_CHGDBG20:			;

	XOR	R0,R0
	MOV.L	#_ACC_STEP_POINT,R1	;
	MOV.W	R0,@R1
	MOV.L	#_ACC_STEP_FLG,R1	;
	MOV.W	R0,@R1



;	---- 2010-09-29---
	XOR	R0,R0
	MOV.L	#_ACC_LAST_POINT,R1	;
	MOV.W	R0,@R1			;
	MOV.L	#_ACC_STOP_POINT,R1	;
	MOV.W	R0,@R1			;



DNM_STEP_ACC_CHG_100:

	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***		振り子加速度演算		***
;	***		(LSIの演算部の代わり)		***
;	***						***
;	***						***
;	***						***
;	***						***
;	***						***
;	***************************************************
;	_PLS_LSI_CTRL
;		_PLS_LSI_CTL_CALC
;			POSCTL_SV_SPD
_DNM_SPD_CALC:
	SUB_START
	XOR	R0,R0
	MOV.L	#_ACC_ANS_ACCDAT,R1		;(加速または減速すべき　加速度):0変化するﾃﾞｰﾀがない
	MOV.L	R0,@R1				;


	XOR	R0,R0				;
	MOV.L	#_ACC_CTRL_STS2,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_DNM_STEP_ACC_CHANGE,R0	;

	FAR_JSR	#_DNM_ACC_CALC,R0		;

;	-------- DEBUG OUT ------------------
	MOV.L	#_ACC_CTRL_STS1,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_ACC_CTRL_STS2,R1		;
	MOV.W	@R1,R2				;
	OR	R2,R0				;

	MOV.L	#_ACC_STEP_FLG,R1		;
	MOV.W	@R1,R3				;
	SHLL8	R3				;
	OR	R3,R0				;

;;;;;;;;2015-07-22	MOV.L	#_SQ_CBWK_TOP+_WKSQCB247,R1	;
;;;;;;;;2015-07-22	MOV.W	R0,@R1				;

	MOV.L	#_ACC_ANS_ACCDAT,R1	;(加速または減速すべき　加速度):0変化するﾃﾞｰﾀがない
	MOV.L	@R1,R2			;
	MOV.L	#_ACC_MONITOR_DAT1,R1	;リニア
	MOV.L	R2,@R1			;+/-1

	MOV.L	#_ACC_LAST_POINT,R1	;最大速度から求まる
	MOV.W	@R1,R2			;
	FAR_JSR	#_R2_MUL10_ANS_R2,R1	;*10
	MOV.L	#_ACC_MONITOR_DAT2,R1	;ｴﾝｺｰﾀﾞ角度
	MOV.L	R2,@R1			;

	MOV.L	#_ACC_STOP_POINT,R1	;ステップ速度停止の中で求まる（停止予定の行程）
	MOV.W	@R1,R2			;
	FAR_JSR	#_R2_MUL10_ANS_R2,R1	;*10
	MOV.L	#_ACC_MONITOR_DAT3,R1	;PG角度
	MOV.L	R2,@R1			;

	MOV.L	#_ACC_STEP_POINT,R1	;ステップ
	MOV.W	@R1,R2			;
	MOV.L	#_ACC_MONITOR_DAT4,R1	;負荷率
	MOV.L	R2,@R1			;


;DAT5


	MOV.L	#_ACC_LAST_SPD,R1	;
	MOV.L	@R1,R2			;
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	MOV.L	#_ACC_MONITOR_DAT6,R1	;左
	MOV.L	R2,@R1			;

	MOV.L	#_ACC_STOP_SPD,R1	;
	MOV.L	@R1,R2			;
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	MOV.L	#_ACC_MONITOR_DAT7,R1	;右
	MOV.L	R2,@R1			;

	MOV.L	#_ACC_STEP_SPD,R1	;
	MOV.L	@R1,R2			;
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	SHLR	R2
	MOV.L	#_ACC_MONITOR_DAT8,R1	;合計
	MOV.L	R2,@R1			;




	SUB_END
	M_RTS



_DNM_ACC_CALC
	SUB_START

	FAR_JSR	#_DNM_ACC_OVER_PLS_MAK,R0

	MOV.L	#_ACC_POS_STEP,R1	;//内部制御工程1~11
	MOV.W	@R1,R0			;
;----------必要か？  2011-03-22 
	TST	R0,R0	
	TST_BIT_ON DNM_ACCCALC_020
	MOV.W	#1,R0			;
DNM_ACCCALC_020


	MOV.L	#_ACC_STOP_NUMBER,R1	;停止に使用するデータ番号=停止ステップ
	MOV.W	R0,@R1			;

	MOV.L	#_ACC_STEP_NUMBER,R1	;加減速に使用するデータ番号=動作ステップ
	MOV.W	R0,@R1			;

	XOR	R0,R0
	MOV.L	#_ACC_ANS_ACCDAT,R1		;(加速または減速すべき　加速度):0変化するﾃﾞｰﾀがない
	MOV.L	R0,@R1				;

;;;	FAR_JSR	#_TBLACC_LAST_SP_MAKE,R0	;最終減速演算：現在速度より高ければこれに置き換える

	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R1,R0				;
	MOV.L	#_ACC_LAST_SPD,R1		;最終速度から求まる
	MOV.L	R0,@R1				;PLS/S



	FAR_JSR	#_TBLACC_STOP_SP_MAKE,R0	;現行ｽﾃｯﾌﾟからの減速演算：最大以下であれば最大

	FAR_JSR	#_TBLACC_STEP_SP_MAKE,R0	;減速演算２つより低い範囲で加速または減速する

;	比較結果を加速度で表す

	XOR	R8,R8				;FLAG
	MOV.L	#_ACC_LAST_SPD,R1		;最終速度から求まる
	MOV.L	@R1,R6				;PLS/S
	MOV.L	#_ACC_STOP_SPD,R1		;停止ステップのデータから求まる
	MOV.L	@R1,R5				;
	CMP/GE	R5,R6				;
	BT	DNM_ACCCALC_100			;
	MOV.W	#BIT0,R4			;
	OR	R4,R8				;
	MOV	R6,R5				;R5:LIMIT
DNM_ACCCALC_100


	MOV.L	#_ACC_STEP_SPD,R1		;これから変化させようと考えている速度
	MOV.L	@R1,R2				;
	CMP/GE	R2,R5				;
	BT	DNM_ACCCALC_200			;

;	--- limit on----
	MOV.W	#BIT1,R4			;
	OR	R4,R8				;
	MOV	R5,R2				;LIMIT

DNM_ACCCALC_200
	MOV.L	#_ACC_CALC_SPDX,R1		;
	MOV.L	R2,@R1				;

	FAR_JSR	#_DNM_ACC_OVER_SPD_MAK,R0		;
	MOV.L	#_ACC_CALC_SPD,R1		;
	MOV.L	@R1,R2				;


	MOV.L	#_POSCTL_SV_OFS_SPD,R1		;
	MOV.L	@R1,R3				;
	CMP/GE	R3,R2				;
	BT	DNM_ACCCALC_300			;

;	--- UNDER　LIMIT----
	MOV.W	#BIT2,R4			;[BIT2はにせもの]
	OR	R4,R8				;
	MOV	R3,R2				;

DNM_ACCCALC_300
	MOV.L	#_ACC_CTRL_STS1,R1		;
	MOV.W	@R1,R0				;
	AND	#LOW ~BIT2,R0
	OR	R8,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_POSCTL_RL_SPD,R1		;現在速度
	MOV.L	@R1,R3				;
	SUB	R3,R2				;
	MOV.L	#_ACC_ANS_ACCDAT,R1		;(加速または減速すべき　加速度):0変化するﾃﾞｰﾀがない
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS






;	*******************************************
;	***					***
;	***	演算上で使用するデータ		***
;	***					***
;	*******************************************
_DNM_ACC_OVER_PLS_MAK:
	SUB_START
	MOV.L	#_ACC_REST_ABS_PLS,R5	;//
	MOV.L	@R5+,R1			;
	MOV.L	@R5,R2			;

;	*1/比率
	MOV.L	#_ACC_REST_FLG,R4		;//0:減速ﾁｪｯｸしなくていい(500,000*30sec以上距離がある)
	MOV.W	@R4,R0				;
	TST	R0,R0				;
	TST_BIT_OF DNM_ACC_OVER_PLSMK200	;

	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R4					;
	MOV.W	#_OVRLIDE_LATE_MAX,R1			;
	FAR_JSR	#_MULDIV_R2S32mR1S32dR4S32aR1R2S64,R0	;

	TST	R1,R1					;
	TST_BIT_ON DNM_ACC_OVER_PLSMK100		;まだ4byte以上ある

	MOV.L	#_GENSOK_LNGTH_MAX,R4			;30秒*500KHよりも距離がある
	CMP/GE	R4,R2					;
	BT	DNM_ACC_OVER_PLSMK100			;
	M_BRA	DNM_ACC_OVER_PLSMK200			;

DNM_ACC_OVER_PLSMK100
	MOV.W	#-1,R0
	MOV.L	#_ACC_REST_FLG,R4		;//0:減速ﾁｪｯｸしなくていい(500,000*30sec以上距離がある)
	MOV.W	R0,@R4				;

DNM_ACC_OVER_PLSMK200:
	MOV.L	#_ACC_REST_ABS_PLSX,R6	;//これで演算
	MOV.L	R1,@R6			;
	MOV.L	R2,@(4,R6)		;


;	_TBLACC_ACC_ADDCHKの演算に使用している箇所の拡大
;	設定速度の拡大 DATA*MAX/比率
	MOV.L	#_POSCTL_SV_SPD,R1			;
	MOV.L	@R1,R2					;
	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R4					;
	MOV.W	#_OVRLIDE_LATE_MAX,R1			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;
	MOV.L	#_ACC_POSCTL_SV_SPDX,R1			;
	MOV.L	R2,@R1					;



;	実速度の拡大 DATA*MAX/比率(ACC_)
	MOV.L	#_POSCTL_RL_SPD,R1			;
	MOV.L	@R1,R2					;
	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R4					;
	MOV.W	#_OVRLIDE_LATE_MAX,R1			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;
	MOV.L	#_ACC_POSCTL_RL_SPDX,R1			;
	MOV.L	R2,@R1					;



;	加速度の拡大 DATA*MAX/比率
	MOV.L	#_POSCTL_SV_UP_ACC,R1			;
	MOV.L	@R1,R2					;
	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R4					;
	MOV.W	#_OVRLIDE_LATE_MAX,R1			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;
	MOV.L	#_ACC_POSCTL_SV_UP_ACCX,R1		;
	MOV.L	R2,@R1					;


;	加速度の拡大 DATA*MAX/比率
	MOV.L	#_POSCTL_SV_DN_ACC,R1			;
	MOV.L	@R1,R2					;
	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R4					;
	MOV.W	#_OVRLIDE_LATE_MAX,R1			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;
	MOV.L	#_ACC_POSCTL_SV_DN_ACCX,R1		;
	MOV.L	R2,@R1					;






	SUB_END
	M_RTS


_DNM_ACC_OVER_SPD_MAK:
	SUB_START
	MOV.L	#_ACC_CALC_SPDX,R1			;
	MOV.L	@R1,R2					;

;      *比率
	MOV.L	#_POSCTL_OVER_SPD_LAT,R3		;
	MOV.W	@R3,R1					;
	MOV.W	#_OVRLIDE_LATE_MAX,R4			;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;


	MOV.L	#_ACC_CALC_SPD,R1		;
	MOV.L	R2,@R1				;
	SUB_END
	M_RTS



;	***************************************************
;	***						***
;	***		最終減速演算			***
;	***		100%->0%			***
;	***		距離を使用する			***
;	***						***
;	***************************************************
;①全工程
;;;[2013-05-20 前から未使用]_TBLACC_LAST_SP_MAKE
;;;[2013-05-20 前から未使用]	SUB_START
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];最大速度時の減速速度
;;;[2013-05-20 前から未使用];最大速度時の減速パルス
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_ACCTM,R1		;加減速時間
;;;[2013-05-20 前から未使用]	MOV.W	@R1,R6				;
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_STPPTBL,R13	;
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_BASEDAT_STPVTBL,R11	;
;;;[2013-05-20 前から未使用]	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
;;;[2013-05-20 前から未使用]	MOV.L	@R1,R5				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_REST_ABS_PLSX,R0		;
;;;[2013-05-20 前から未使用]	MOV.L	@R0,R1				;
;;;[2013-05-20 前から未使用]	MOV.L	@(4,R0),R2			;USED R2
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	FAR_JSR	#_POINT_SERCH_PLS1,R0
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];;	MOV.L	#_ACC_LAST_SPD,R1		;最終速度から求まる
;;;[2013-05-20 前から未使用];;	MOV.L	R2,@R1				;PLS/S
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];;	MOV.L	#_ACC_LAST_POINT,R1		;
;;;[2013-05-20 前から未使用];;	MOV.W	R0,@R1
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	TST	R0,R0
;;;[2013-05-20 前から未使用]	TST_BIT_OF TBLACC_LASTSP_MK100		;
;;;[2013-05-20 前から未使用]	NOP
;;;[2013-05-20 前から未使用]	M_BRA	TBLACC_LASTSP_MK150
;;;[2013-05-20 前から未使用]TBLACC_LASTSP_MK100
;;;[2013-05-20 前から未使用]	NOP
;;;[2013-05-20 前から未使用]TBLACC_LASTSP_MK150
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_LAST_POINT,R5		;
;;;[2013-05-20 前から未使用]	MOV.W	@R5,R3				;
;;;[2013-05-20 前から未使用]	TST	R3,R3				;
;;;[2013-05-20 前から未使用]	TST_BIT_OF TBLACC_LASTSP_MK500		;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	CMP/HS	R3,R0				;R3=<R0
;;;[2013-05-20 前から未使用]	BF	TBLACC_LASTSP_MK200		;NO! R0<R3 ok減速した
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	ADD	#-1,R3				;
;;;[2013-05-20 前から未使用]	MOV	R3,R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]TBLACC_LASTSP_MK200:
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	TST	R0,R0				;
;;;[2013-05-20 前から未使用]	TST_BIT_ON TBLACC_LASTSP_MK400
;;;[2013-05-20 前から未使用]	MOV.W	#1,R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]TBLACC_LASTSP_MK400
;;;[2013-05-20 前から未使用]	PUSH_REG1 R0
;;;[2013-05-20 前から未使用]	FAR_JSR	#_POINT_GET_SPD1,R1		;
;;;[2013-05-20 前から未使用]	POP_REG1 R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]TBLACC_LASTSP_MK500				;
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_LAST_POINT,R5		;
;;;[2013-05-20 前から未使用]	MOV.W	R0,@R5
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_LAST_SPD,R1		;最終速度から求まる
;;;[2013-05-20 前から未使用]	MOV.L	R2,@R1				;PLS/S
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用];	----------- 使用しない---
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	SUB_END
;;;[2013-05-20 前から未使用]	M_RTS



;	***************************************************
;	***						***
;	***		停止減速演算			***
;	***		x%->0%				***
;	***		距離を使用する			***
;	***						***
;	***************************************************
;②全工程(全段数に対して存在する)
_TBLACC_STOP_SP_MAKE
	SUB_START

	MOV.L	#_ACC_STOP_NUMBER,R1	;停止に使用するデータ番号=停止ステップ
	MOV.W	@R1,R5			;

	FAR_JSR	#_ACC_NUMBER_SELTBL1,R0	;

	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R1,R5				;

	MOV.L	#_ACC_REST_ABS_PLSX,R0		;
	MOV.L	@R0,R1				;
	MOV.L	@(4,R0),R2			;USED R2

	FAR_JSR	#_POINT_SERCH_PLS_HOKAN1,R0	;
	M_BRA	TBLACC_STOPSP_MK500		

;;;[2013-05-20 前から未使用]	TST	R0,R0
;;;[2013-05-20 前から未使用]	TST_BIT_OF TBLACC_STOPSP_MK100		;
;;;[2013-05-20 前から未使用]	NOP
;;;[2013-05-20 前から未使用]	M_BRA	TBLACC_STOPSP_MK150
;;;[2013-05-20 前から未使用]TBLACC_STOPSP_MK100
;;;[2013-05-20 前から未使用]	NOP
;;;[2013-05-20 前から未使用]TBLACC_STOPSP_MK150
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	MOV.L	#_ACC_STOP_POINT,R5		;
;;;[2013-05-20 前から未使用]	MOV.W	@R5,R3				;
;;;[2013-05-20 前から未使用]	TST	R3,R3				;
;;;[2013-05-20 前から未使用]	TST_BIT_OF TBLACC_STOPSP_MK500		;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	CMP/HS	R3,R0				;R3=<R0
;;;[2013-05-20 前から未使用]	BF	TBLACC_STOPSP_MK200		;NO! R0<R3 ok減速した
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	ADD	#-1,R3				;
;;;[2013-05-20 前から未使用]	MOV	R3,R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]TBLACC_STOPSP_MK200:
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]	TST	R0,R0				;
;;;[2013-05-20 前から未使用]	TST_BIT_ON TBLACC_STOPSP_MK400
;;;[2013-05-20 前から未使用]	MOV.W	#1,R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]TBLACC_STOPSP_MK400
;;;[2013-05-20 前から未使用]	PUSH_REG1 R0
;;;[2013-05-20 前から未使用]	FAR_JSR	#_POINT_GET_SPD1,R1		;
;;;[2013-05-20 前から未使用]	POP_REG1 R0				;
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
;;;[2013-05-20 前から未使用]
TBLACC_STOPSP_MK500				;
	MOV.L	#_ACC_STOP_POINT,R5		;
	MOV.W	R0,@R5
	MOV.L	#_ACC_STOP_SPD,R1		;最終速度から求まる
	MOV.L	R2,@R1				;PLS/S

	SUB_END
	M_RTS

;	***************************************************
;	***						***
;	***						***
;	***		加速演算			***
;	***		減速演算			***
;	***						***
;	***						***
;	***************************************************

_TBLACC_STEP_SP_MAKE
	SUB_START

	MOV.L	#_ACC_STEP_NUMBER,R1		;加減速に使用するデータ番号=動作ステップ
	MOV.W	@R1,R5				;
	FAR_JSR	#_ACC_NUMBER_SELTBL2,R0		;


	MOV.L	#_ACC_STEP_FLG,R1		;BIT0:START BIT1:CALC BIT2:LIMIT
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;
	TST_BIT_ON TBLACC_STEP_SPMAK_400	;
	TST	#(BIT1+BIT0),R0			;
	TST_BIT_ON TBLACC_STEP_SPMAK_200	;

	MOV.L	#_ACC_STEP_POINT,R1		;0:ｻｰﾁ前(目標速度切り替わり時:0)
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON TBLACC_STEP_SPMAK_200	;

;;;;	MOV.L	#_POSCTL_RL_SPD,R0		;pls/s
	MOV.L	#_ACC_POSCTL_RL_SPDX,R0		;
	MOV.L	@R0,R2				;


;	========= DEBUG 
	MOV.L	#_ACC_STEP_NUMBER,R1		;加減速に使用するデータ番号=動作ステップ
	MOV.W	@R1,R0				;
	CMP/EQ	#2,R0				;
	BF	DEBUG_JMP10			;
	NOP
	NOP
	NOP
DEBUG_JMP10

;	-------------加減速直線演算固定させたいだけ2014-09-22
	MOV.L	#_MOT_REP_F,R1			;//BIT0
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON TBLACC_STEP_SPMAK_CNST050

	FAR_JSR	#_POINT_SERCH_SPD1,R0		;

	TST	R0,R0				;
	TST_BIT_ON TBLACC_STEP_SPMAK_100	;範囲内でいる JUMP

TBLACC_STEP_SPMAK_CNST050:

;一定加速・一定減速演算
	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACC_CTRL_STS2,LG=W,BIT=BIT4,WKREG=R1	;
	FAR_JSR	#_TBLACC_ACC_ADDCHK,R0		;ANS R2
	M_BRA	TBLACC_STEP_SPMAK_500	;


TBLACC_STEP_SPMAK_100
	MOV.L	#_ACC_STEP_POINT,R1		;0:ｻｰﾁ前(目標速度切り替わり時:0)
	MOV.W	R0,@R1				;

	MOV.W	#BIT0,R0
	MOV.L	#_ACC_STEP_FLG,R1		;BIT0:START BIT1:CALC BIT2:LIMIT
	MOV.W	R0,@R1				;


TBLACC_STEP_SPMAK_200
	MOV	R8,R0				;
	TST	#BIT2,R0			;BIT2=0加速
	TST_BIT_OF TBLACC_STEP_SPMAK_250	;
;	---減速--
	MOV.L	#_ACC_STEP_POINT,R1		;0:ｻｰﾁ前(目標速度切り替わり時:0)
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BT	TBLACC_STEP_SPMAK_400		;LIMIT
	ADD	#-1,R0				;
	MOV.W	R0,@R1				;
	M_BRA	TBLACC_STEP_SPMAK_300		;

TBLACC_STEP_SPMAK_250
;	---加速--
	MOV.L	#_ACC_STEP_POINT,R1		;0:ｻｰﾁ前(目標速度切り替わり時:0)
	MOV.W	@R1,R0				;
	CMP/HS	R6,R0				;
	BT	TBLACC_STEP_SPMAK_400		;LIMIT
	ADD	#1,R0				;
	MOV.W	R0,@R1				;
TBLACC_STEP_SPMAK_300
	FAR_JSR	#_POINT_GET_SPD1,R1		;input R0

	MOV.W	#(BIT1+BIT0),R0			;
	MOV.L	#_ACC_STEP_FLG,R1		;BIT0:START BIT1:CALC BIT2:LIMIT
	MOV.W	R0,@R1				;
	M_BRA	TBLACC_STEP_SPMAK_500		;

;	---------LIMIT-ON  ---------
TBLACC_STEP_SPMAK_400
;;;不要	MOV.L	#_POSCTL_RL_SPD,R0		;pls/s
;;不要	MOV.L	@R0,R2				;
	FAR_JSR	#_TBLACC_ACC_ADDCHK,R0		;ANS R2

	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACC_STEP_FLG,LG=W,BIT=BIT2,WKREG=R1	;

TBLACC_STEP_SPMAK_500
	MOV.L	#_ACC_STEP_SPD,R1		;ステップ
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	各工程時のインフォメーション	***
;	***					***
;	*******************************************
;;	MOV.L	#_ACC_BASEDAT_ACCTM,R1		;加減速時間
;;	MOV.W	@R1,R6				;
;;	MOV.L	#_ACC_BASEDAT_STPPTBL,R13	;
;;	MOV.L	#_ACC_BASEDAT_STPVTBL,R11	;
;	MOV.L	@(AFM_STEP_INF_FLG-ACC_FORM_TOP,GBR),R0	;
;	MOV.W	R0,R8					;BIT2=[0=加速/1=減速] 
_ACC_NUMBER_SELTBL1:
	SUB_START

	ADD	#-1,R5						;
	SHLL2	R5						;*4byte
	MOV.L	#_ACC_TBL_CAL_IN_TOP,R6				;
	ADD	R5,R6						;
	MOV.L	@R6,R0
	LDC	R0,GBR					

	MOV.L	@(AFM_DST_STPACTM-ACC_FORM_TOP,GBR),R0	;
	MOV.W	@R0,R6					;
	MOV.L	@(AFM_DST_STPPTBL-ACC_FORM_TOP,GBR),R0	;
	MOV	R0,R13
	MOV.L	@(AFM_DST_STPVTBL-ACC_FORM_TOP,GBR),R0	;
	MOV	R0,R11					;
	MOV.L	@(AFM_STEP_INF_FLG-ACC_FORM_TOP,GBR),R0	;
	MOV.W	@R0,R8					;BIT2=[0=加速/1=減速] 

	SUB_END
	M_RTS

_ACC_NUMBER_SELTBL2:
	SUB_START

	ADD	#-1,R5						;
	SHLL2	R5						;*4byte
	MOV.L	#_ACC_TBL_CAL_IN_TOP,R6				;
	ADD	R5,R6						;
	MOV.L	@R6,R0
	LDC	R0,GBR					

	MOV.L	@(AFM_DST_CTLACTM-ACC_FORM_TOP,GBR),R0	;
	MOV.W	@R0,R6					;
;;;;;	MOV.L	@(AFM_DST_STPPTBL-ACC_FORM_TOP,GBR),R0	;
;;;;;	MOV	R0,R13
	MOV.L	@(AFM_DST_CTLVTBL-ACC_FORM_TOP,GBR),R0	;
	MOV	R0,R11					;
	MOV	R0,R13					;
	MOV.L	@(AFM_STEP_INF_FLG-ACC_FORM_TOP,GBR),R0	;
	MOV.W	@R0,R8					;BIT2=[0=加速/1=減速] 

	SUB_END
	M_RTS


;AFM_SRC_TBL_TOP		.DATA.L		_ACC_IN_TBLUSE		;元ﾃｰﾌﾞﾙADR(2byte)
;AFM_SRC_TBL_MEM		.DATA.L		_ACC_IN_TBL_TIM		;255msec WOD
;AFM_STEP_INF_SPD	.DATA.L		_ACC_INF1_STEPSP01	;000%[前状態],050%[設定]
;AFM_STEP_INF_FLG	.DATA.L		_ACC_INF1_STEP001	;//BIT2=[加速:0/減速:1] BIT1=[]   BIT0=0(停止) =1(連続)
;AFM_OLD_CTLVTBL		.DATA.L		_ACC_STEP001_VTBL	;(STEP1では使用しない)
;AFM_DST_CTLVTBL		.DATA.L		_ACC_STEP001_VTBL	;
;AFM_DST_CTLACTM		.DATA.L		_ACC_STEP001_ACTM	;
;AFM_OLD_STPVTBL		.DATA.L		_ACC_STOP001_VTBL	;
;AFM_DST_STPVTBL		.DATA.L		_ACC_STOP001_VTBL	;
;AFM_DST_STPACTM		.DATA.L		_ACC_STOP001_ACTM	;
;AFM_DST_STPPTBL		.DATA.L		_ACC_STOP001_PTBL	;

;	*******************************************
;	***					***
;	***		サーチ			***
;	***		速度型サーチ		***
;	***					***
;	*******************************************
;	テーブルは増加方向である
;	サーチは加速方向と減速方向がある。
;
;	Input 現在速度 R2 ()
;	      TABEL_TOP_ADR R13
;	      TABEL個数(加減速時間+1)をもらう R6
;	      	ﾃｰﾌﾞﾙ方向 
;		ｻｰﾁ方向   0:加速(大きくなる点をサーチする) 1:減速（小さくなる限界点をサーチする）
;	Output:ﾎﾟｲﾝﾀ 1~ﾃｰﾌﾞﾙ個数 0(ﾃｰﾌﾞﾙ範囲外),-1(ﾃｰﾌﾞﾙ範囲外)
;
;	MAX 10回:1023まで
;	0~15(16個)   4回   5bit
;	0~31(32個)   5回   6
;	0~63(64個)   6回   7
;	0~127(128個) 7回   8
;	0~255(256個) 8回   9
;	0~511(512個) 9回   10
;	0~1023(1024個)10回 11
;
;	MOV.L	#_ACC_BASEDAT_ACCTM,R1		;加減速時間
;	MOV.W	@R1,R6				;
;	MOV.L	#_ACC_BASEDAT_STPPTBL,R13	;
;	MOV.L	#_ACC_BASEDAT_STPVTBL,R11	;
;	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
;	MOV.L	@R1,R5				;
;
;
;
;
;
_POINT_SERCH_SPD1
	SUB_START
	PUSH_REG1 R2

	MOV.L	#_LINK_MAX_SPD_PLS,R0		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R0,R4				;
	MOV.W	#_ACC_PER_V_MAX,R1		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;

	MOV	R6,R0				;加減速時間
	SHLL	R0				;2byte
	MOV.W	@(R0,R11),R1			;(V)
	CMP/HI	R1,R2				;
	BT	POINT_SERCHSPD1_100		;最大よりも大きい:範囲外

	MOV.W	@R11,R1				;(V)MIN
	CMP/HI	R2,R1				;
	BT	POINT_SERCHSPD1_100		;最小よりも小さい:範囲外

	FAR_JSR	#_POINT_SERCH_BIG_2B,R0		;
	MOV	R9,R0				;
	M_BRA	POINT_SERCHSPD1_END		;



POINT_SERCHSPD1_100:				;
	XOR	R0,R0				;範囲外
	M_BRA	POINT_SERCHSPD1_END		;

POINT_SERCHSPD1_END:				;

	POP_REG1 R2
	SUB_END
	M_RTS


;input R0
_POINT_GET_SPD1
	SUB_START
	SHLL	R0				;2byte
	MOV.W	@(R0,R11),R2			;
	MOV.L	#_LINK_MAX_SPD_PLS,R0		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R0,R1				;
	MOV.W	#_ACC_PER_V_MAX,R4		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;ANS R2
	SUB_END
	M_RTS






;	*******************************************
;	***					***
;	***		サーチ			***
;	***		位置型サーチ		***
;	***					***
;	*******************************************
;	MOV.L	#_ACC_BASEDAT_ACCTM,R1		;加減速時間
;	MOV.W	@R1,R6				;
;	MOV.L	#_ACC_BASEDAT_STPPTBL,R13	;
;	MOV.L	#_ACC_BASEDAT_STPVTBL,R11	;
;	MOV.L	#_LINK_MAX_SPD_PLS,R1		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
;	MOV.L	@R1,R5				;
;
;	[減速位置のため]
;
_POINT_SERCH_PLS1
	SUB_START

	MOV.L	#_ACC_REST_FLG,R4		;
	MOV.W	@R4,R0				;
	TST	R0,R0				;
	TST_BIT_OF POINT_SERCHPLS1_100		;R0=0まだまだ残り距離が十分あるから減速演算不要[いまやってもｵｰﾊﾞﾌﾛする]

	MOV	R6,R0				;加減速時間
	SHLL2	R0				;4byte
	MOV.L	@(R0,R13),R1			;(P)
	CMP/HI	R1,R2				;SV(最も大きいパルス)<PV 
	BT	POINT_SERCHPLS1_100		;

	FAR_JSR	#_POINT_SERCH_BIG_4B,R0		;ANS R9 大きい順に探した超えた最も近い点
;;;;不要	ADD	#-1,R9				;
	CMP/PL	R9				;
	BT	POINT_SERCHPLS1_050		;
	MOV.W	#1,R9				;
POINT_SERCHPLS1_050:
	MOV	R9,R0				;
	SHLL	R0				;2byte
	MOV.W	@(R0,R11),R1			;(V)SPEED
	MOV.L	#_LINK_MAX_SPD_PLS,R0		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R0,R2				;
	MOV.W	#_ACC_PER_V_MAX,R4		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;V%*FREQ/100.00% *1/1000=deltV
	M_BRA	POINT_SERCHPLS1_200		;PLS/sec

POINT_SERCHPLS1_100:
	MOV	R5,R2
	XOR	R0,R0
	M_BRA	POINT_SERCHPLS1_END		;
POINT_SERCHPLS1_200:				;
	MOV	R9,R0				;POINTER(0以外)
POINT_SERCHPLS1_END:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***		サーチ			***
;	***		位置型サーチ		***
;	***					***
;	*******************************************
;R5
_POINT_SERCH_PLS_HOKAN1
	SUB_START
	PUSH_REG1 R6
	PUSH_REG1 R7
	PUSH_REG1 R8

	MOV.L	#_ACC_REST_FLG,R4		;
	MOV.W	@R4,R0				;
	TST	R0,R0				;
	TST_BIT_OF POINT_SERCHPLS_HKN1_400	;R0=0まだまだ残り距離が十分あるから減速演算不要[いまやってもｵｰﾊﾞﾌﾛする]
;-----ｵｰﾊﾞﾌﾛｰはしない-----
	MOV	R6,R0				;加減速時間
	SHLL2	R0				;4byte
	MOV.L	@(R0,R13),R1			;(P)
	CMP/HI	R1,R2				;SV(最も大きいパルス)<PV 
	BT	POINT_SERCHPLS_HKN1_400		;

	PUSH_REG1 R2				;残り距離ﾊﾟﾙｽ


	FAR_JSR	#_POINT_SERCH_BIG_4B,R0		;ANS R9 大きい順に探した超えた最も近い点
	MOV	R9,R8				;

	CMP/PL	R9				;
	BT	POINT_SERCHPLS_HKN1_050		;
	MOV.W	#1,R9				;
POINT_SERCHPLS_HKN1_050:			;
	MOV	R9,R0				;
	SHLL	R0				;2byte
	MOV.W	@(R0,R11),R3			;(Yn_1)SPEED
	SHLL	R0
	MOV.L	@(R0,R13),R5			;(Xn_1)POS

	ADD	#1,R8				;
	CMP/HS	R8,R6				;
	BT	POINT_SERCHPLS_HKN1_100		;
	MOV	R6,R8				;加減速時間
POINT_SERCHPLS_HKN1_100:			;
	MOV	R8,R0				;
	SHLL	R0				;2byte
	MOV.W	@(R0,R11),R2			;(Yn)SPEED
	SHLL	R0
	MOV.L	@(R0,R13),R4			;(Xn_1)POS

	POP_REG1 R1				;残り距離ﾊﾟﾙｽ
	MOV	R2,R6				;

;	R3:Yn_1		R5:Xn_1
;	R2:Yn		R4:Xn
;	ANS:R2=y	R1:x
;	limit R6(Yn)

	FAR_JSR	#_FPU_POS_HOKAN1,R0		;V%=算出 R2

	MOV.L	#_LINK_MAX_SPD_PLS,R0		;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R0,R1				;
	MOV.W	#_ACC_PER_V_MAX,R4		;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;V%*FREQ/100.00% *1/1000=deltV
	M_BRA	POINT_SERCHPLS_HKN1_500		;PLS/sec

POINT_SERCHPLS_HKN1_400:
	MOV	R5,R2
	XOR	R0,R0
	M_BRA	POINT_SERCHPLS_HKN1_END		;

POINT_SERCHPLS_HKN1_500:			;
	MOV	R9,R0				;POINTER(0以外)
POINT_SERCHPLS_HKN1_END:


	POP_REG1 R8
	POP_REG1 R7
	POP_REG1 R6

	SUB_END
	M_RTS





;	*******************************************
;	***					***
;	***		サーチ			***
;	***					***
;	*******************************************
;	テーブルは増加方向である
;	サーチは加速方向で行う
;
;	Input 現在速度 R2 ()     table-V(n) =< R2 =<table-V(n+1) となる　ﾃｰﾌﾞﾙ番号
;			         加速時はnをそのまま使用する
;				 減速時はn-1を使用
;	      TABEL_TOP_ADR R13
;	      TABEL個数-1(加減速時間)をもらう R6
;	      	ﾃｰﾌﾞﾙ方向 
;		ｻｰﾁ方向   0:加速(大きくなる点をサーチする) 
;	Output:ﾎﾟｲﾝﾀ 1~ﾃｰﾌﾞﾙ個数 0(ﾃｰﾌﾞﾙ範囲外),-1(ﾃｰﾌﾞﾙ範囲外)
;
;	MAX 10回:1023まで
;	0~15(16個)   4回   5bit
;	0~31(32個)   5回   6
;	0~63(64個)   6回   7
;	0~127(128個) 7回   8
;	0~255(256個) 8回   9
;	0~511(512個) 9回   10
;	0~1023(1024個)10回 11

;	*******************************************
;	***					***
;	***	2byte ｻｰﾁ			***
;	***					***
;	*******************************************
;	ANS R9
;
_POINT_SERCH_BIG_2B
	SUB_START
	PUSH_REG1 R6
	PUSH_REG1 R7
	PUSH_REG1 R8
	PUSH_REG1 R10
	PUSH_REG1 R11
	PUSH_REG1 R12
	PUSH_REG1 R13
	PUSH_REG1 R14

	MOV	R6,R7				;カウンタ個数

	XOR	R8,R8				;min
	MOV	R7,R10				;max
	SHLR	R7				;IF 11bitの場合10回ｻｰﾁする
	MOV	R7,R9				;今回=(MAX=1024+MIN=0)/2=512
						;R8(MIN=0)=< R9(R10+R8)/2 =< R10(MAX)

	XOR	R7,R7				;ﾃﾞﾊﾞｯｸ

	MOV	R8,R11				;MIN
	MOV	R10,R12				;MAX


PINT_SERCH_BIG2B_200LOP

;======= 2byte/4byteの相違部分=====
	MOV	R9,R0				;ANS R9
	SHLL	R0				;2byte
	MOV.W	@(R0,R13),R1			;2byte SV

	CMP/EQ	R1,R2				;
	BT	PINT_SERCH_BIG2B_800		;ﾋﾟｯﾀﾘ賞
	CMP/HS	R1,R2				;SV=<PV
	BT	PINT_SERCH_BIG2B_300		;YES:大きい

;	R8(MIN)=< [R2] =<R9(MAX/MIN)/2 =<R10(MAX)
	MOV	R9,R10				;
	ADD	R8,R9				;(R8[MIN]+R10[MAX])
	SHLR	R9				;R9=(R8[MIN]+R10[MAX])/2
	M_BRA	PINT_SERCH_BIG2B_500		;


;	R8(MIN)=< R9(MAX/MIN)/2 =< [R2] =<R10(MAX)
PINT_SERCH_BIG2B_300
	MOV	R9,R8				;
	ADD	R10,R9				;(R8[MIN]+R10[MAX])
	SHLR	R9				;R9=(R8[MIN]+R10[MAX])/2

PINT_SERCH_BIG2B_500
	ADD	#1,R7				;デバック
;(MAX,MINがかわらなくなったら終わりを入れるか?)
	CMP/EQ	R8,R11				;
	BF	PINT_SERCH_BIG2B_600		;MIN=OLD-MIN NO
	CMP/EQ	R10,R12				;
	BF	PINT_SERCH_BIG2B_600		;MAX=OLD-MAX NO
	M_BRA	PINT_SERCH_BIG4B_900		;終了でいい(更新されない・・・終了)


PINT_SERCH_BIG2B_600
	MOV	R8,R11				;
	MOV	R10,R12				;
	M_BRA	PINT_SERCH_BIG2B_200LOP		;

;	----------- ピッタリ賞 R9:ANS--------------
PINT_SERCH_BIG2B_800
;	----------- R9:ANS--------------
PINT_SERCH_BIG2B_900

	POP_REG1 R14
	POP_REG1 R13
	POP_REG1 R12
	POP_REG1 R11
	POP_REG1 R10
	POP_REG1 R8
	POP_REG1 R7
	POP_REG1 R6
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	4byte ｻｰﾁ			***
;	***					***
;	*******************************************
;	Input 現在ﾊﾟﾙｽ R2 ()     table-V(n) =< R2 =<table-V(n+1) となる　ﾃｰﾌﾞﾙ番号
;				 減速時はn-1を使用する
;	Input TABEL_TOP_ADR R13
;	Input TABEL個数-1(加減速時間)をもらう R6
;
;	ANS R9 TABLE NO.
;
_POINT_SERCH_BIG_4B
	SUB_START
	PUSH_REG1 R6
	PUSH_REG1 R7
	PUSH_REG1 R8
	PUSH_REG1 R10
	PUSH_REG1 R11
	PUSH_REG1 R12
	PUSH_REG1 R13
	PUSH_REG1 R14

	MOV	R6,R7				;カウンタ個数

	XOR	R8,R8				;min
	MOV	R7,R10				;max
	SHLR	R7				;IF 11bitの場合10回ｻｰﾁする
	MOV	R7,R9				;今回=(MAX=1024+MIN=0)/2=512
						;R8(MIN=0)=< R9(R10+R8)/2 =< R10(MAX)
	XOR	R7,R7				;ﾃﾞﾊﾞｯｸ

PINT_SERCH_BIG4B_200LOP

;======= 2byte/4byteの相違部分=====
	MOV	R9,R0				;ANS R9
	SHLL2	R0				;4byte
	MOV.L	@(R0,R13),R1			;4byte SV

	CMP/EQ	R1,R2				;
	BT	PINT_SERCH_BIG4B_800		;ﾋﾟｯﾀﾘ賞
	CMP/HS	R1,R2				;SV=<PV
	BT	PINT_SERCH_BIG4B_300		;YES:大きい

;	R8(MIN)=< [R2] =<R9(MAX/MIN)/2 =<R10(MAX)
	MOV	R9,R10				;
	ADD	R8,R9				;(R8[MIN]+R10[MAX])
	SHLR	R9				;R9=(R8[MIN]+R10[MAX])/2
	M_BRA	PINT_SERCH_BIG4B_500		;


;	R8(MIN)=< R9(MAX/MIN)/2 =< [R2] =<R10(MAX)
PINT_SERCH_BIG4B_300
	MOV	R9,R8				;
	ADD	R10,R9				;(R8[MIN]+R10[MAX])
	SHLR	R9				;R9=(R8[MIN]+R10[MAX])/2

PINT_SERCH_BIG4B_500
	ADD	#1,R7				;デバック

;(MAX,MINがかわらなくなったら終わりを入れるか?)
	CMP/EQ	R8,R11				;
	BF	PINT_SERCH_BIG4B_600		;MIN=OLD-MIN NO
	CMP/EQ	R10,R12				;
	BF	PINT_SERCH_BIG4B_600		;MAX=OLD-MAX NO

	M_BRA	PINT_SERCH_BIG4B_900		;終了でいい(更新されない・・・終了)

PINT_SERCH_BIG4B_600
	MOV	R8,R11				;
	MOV	R10,R12				;
	M_BRA	PINT_SERCH_BIG4B_200LOP		;

;	----------- ピッタリ賞 R9:ANS--------------
PINT_SERCH_BIG4B_800
;	----------- R9:ANS--------------
PINT_SERCH_BIG4B_900

	POP_REG1 R14
	POP_REG1 R13
	POP_REG1 R12
	POP_REG1 R11
	POP_REG1 R10
	POP_REG1 R8
	POP_REG1 R7
	POP_REG1 R6
	SUB_END
	M_RTS




;	***************************************************
;	***						***
;	***						***
;	***		直線加速・減速			***
;	***						***
;	***						***
;	***						***
;	***************************************************
;	ANS R0:0ﾃﾞｰﾀ変更なし R0:1ﾃﾞｰﾀ変更有り
;	ANS R2
_TBLACC_ACC_ADDCHK:
	SUB_START

	MEM1_BIT0_TO_BIT7_ORSET MEM=_ACC_CTRL_STS2,LG=W,BIT=BIT5,WKREG=R1	;



	XOR	R0,R0						;変化してない　R0=0

	MOV.L	#_ACC_POSCTL_SV_SPDX,R1				;･････
	MOV.L	@R1,R3						;
	MOV.L	#_ACC_POSCTL_RL_SPDX,R5				;
	MOV.L	@R5,R2						;
	CMP/EQ	R2,R3						;
	BT	TBLACC_ACC_ADD_END				;SV=REAL
	CMP/GE	R2,R3						;R2<R3
	BF	TBLACC_ACC_ADD_200					;NO 減速しろ
;	---加速しろ----
	MOV.L	#_ACC_POSCTL_SV_UP_ACCX,R4				;500,000/1000
	MOV.L	@R4,R1							;
	ADD	R1,R2							;
	CMP/GT	R2,R3							;
	BT	TBLACC_ACC_ADD_300					;R2<R3(SV) THEN そのまま加速
	MOV	R3,R2							;SV→REAL
	M_BRA	TBLACC_ACC_ADD_300					;

TBLACC_ACC_ADD_200:
;	---減速しろ---
	MOV.L	#_ACC_POSCTL_SV_DN_ACCX,R4				;500,000/1000
	MOV.L	@R4,R1							;
	SUB	R1,R2							;
	CMP/GT	R3,R2							;
	BT	TBLACC_ACC_ADD_300					;R3<R2
	MOV	R3,R2							;
TBLACC_ACC_ADD_300:							;
	MOV	#1,R0							;変化した R0=1
TBLACC_ACC_ADD_END:
	SUB_END
	M_RTS































;	*******************************************
;	***					***
;	***					***
;	***		演算			***
;	***					***
;	***		(等身大結果で扱う)	***
;	***					***
;	*******************************************
_DNM_PLS_LSICTL_CALC:
	SUB_START

;	--------- 2010-09-27 残りパルス演算の共通化----
	FAR_JSR	#_ACC_REST_INFO_MAKE,R0

	MOV.L	#_DNM_ACC_CALFLG,R1			;//0/1
	MOV.W	@R1,R0					;
	CMP/EQ	#1,R0					;
	BF	DNM_PLS_LSICTLCAL_010			;
	FAR_JSR	#_DNM_SPD_CALC,R0			;
DNM_PLS_LSICTLCAL_010:


	MOV.L	#_POSCTL_STEP_FLG,R1						;//0(IDLE) BIT0/BIT6 END (BIT1 LATCH)
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;
	TST_BIT_ON DNM_PLS_LSICTLCAL_020					;強制減速停止中(寸動停止)

	TST	#BIT2,R0							;
	TST_BIT_ON DNM_PLS_LSICTLCAL_050					;最終減速状態YES
	M_BRA	DNM_PLS_LSICTLCAL_100						;

DNM_PLS_LSICTLCAL_020
;	--- 減速コマンドラッチ---
	MOV.L	#_POSCTL_SV_OFS_SPD,R1						;//自起動 PLS/S
	MOV.L	@R1,R2								;
	MOV.L	#_POSCTL_RL_SPD,R5						;
	MOV.L	@R5,R3								;
	CMP/HI	R2,R3								;R2(SV) < R3(NOW)
	BT	DNM_PLS_LSICTLCAL_050						;YES
	M_BRA	DNM_PLS_LSICTLCAL_800						;(減速停止)終了処理
DNM_PLS_LSICTLCAL_050:
	M_BRA	DNM_PLS_LSICTLCAL_700						;減速処理




DNM_PLS_LSICTLCAL_100:
	MOV.L	#_POSCTL_STEP_CMD,R1						;//3:EMG停止(速度=0) 1:起動ｺﾏﾝﾄﾞ 2:(減速停止)
	MOV.W	@R1,R0								;EMG-STOP
	CMP/EQ	#2,R0								;減速停止
	BF	DNM_PLS_LSICTLCAL_150						;NO
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT1,WKREG=R1	;強制減速停止指令(寸動停止)
	M_BRA	DNM_PLS_LSICTLCAL_500						;

;-------通常制御----
DNM_PLS_LSICTLCAL_150:
	MOV.L	#_INT_CLS_CTL_FLG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT0,R0							;
	TST_BIT_OF DNM_PLS_LSICTLCAL_160						;
;	-----------やるべきことが今一不明--------
	M_BRA	DNM_PLS_LSICTLCAL_EXT						;


DNM_PLS_LSICTLCAL_160:

;;;;ふりこ	FAR_JSR	#_CMP_POSLSI_CTLGENSOK,R0					;<<<2010-09-21>>>

;<<<2010-09-21>>>
	MOV.L	#_DNM_ACC_CALFLG,R1			;//0/1
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	DNM_PLS_LSICTLCAL_180				;
	MOV.L	#_ACC_CTRL_STS1,R1				;
	MOV.W	@R1,R0						;
	AND	#(BIT2+BIT1),R0					;
	CMP/EQ	#(BIT2+BIT1),R0					;
	BT	DNM_PLS_LSICTLCAL_700				;
	FAR_JSR	#_DNM_AUTO_UP_DN_CALC,R0			;
	M_BRA	DNM_PLS_LSICTLCAL_510				;


DNM_PLS_LSICTLCAL_180:
	FAR_JSR	#_CMP_POSLSI_CTLGENSOK,R0					;
DNM_PLS_LSICTLCAL_190:

	TST	R0,R0								;
	TST_BIT_OF DNM_PLS_LSICTLCAL_500
	CMP/EQ	#1,R0								;
	BT	DNM_PLS_LSICTLCAL_700
;	----- ABNOMAL CALC------						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_CALC_ERR,LG=W,BIT=BIT1,WKREG=R4	;
	M_BRA	DNM_PLS_LSICTLCAL_ERR

;	===== 距離がありそう =====
DNM_PLS_LSICTLCAL_500:								;
;<<<2010-09-21>>>
	FAR_JSR	#_PLS_LSI_SPD_ACC_ADD,R0					;<<<2010-09-21>>>
DNM_PLS_LSICTLCAL_510:								;

	TST	R0,R0								;
	TST_BIT_OF DNM_PLS_LSICTLCAL_EXT						;書き換えない
	FAR_JSR	#_PLS_LSI_CTL_SPDSET,R0						;LSI SET
	M_BRA	DNM_PLS_LSICTLCAL_900						;



;------------最終減速処理(自動・手動ともこの演算を行なう)----------
DNM_PLS_LSICTLCAL_700:
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT2,WKREG=R1	;減速中
;	---払い出し完了ならやめる---------
	FAR_JSR	#_LOD_POS_STS_REG_IN,R0		;
	TST	#BIT2,R0			;停止?
	TST_BIT_ON DNM_PLS_LSICTLCAL_820	;YES:ﾌﾗｸﾞ終了

;	============================================
;<<<2010-09-21>>>
	MOV.L	#_DNM_ACC_CALFLG,R1		;//0/1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	DNM_PLS_LSICTLCAL_710		;

	MOV.L	#_POSCTL_STEP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON DNM_PLS_LSICTLCAL_710	;

;	自動減速
	FAR_JSR	#_DNM_AUTO_UP_DN_CALC,R0	;
	M_BRA	DNM_PLS_LSICTLCAL_740		;


DNM_PLS_LSICTLCAL_710:
;	============================================

;	----ここにきたら目標位置が変わるまで加速はしない------
	MOV.L	#_POSCTL_RL_SPD,R5		;
	MOV.L	@R5,R2				;
	MOV.L	#_POSCTL_SV_DN_ACC,R4		;
	MOV.L	@R4,R3				;
	TST	R3,R3				;
	TST_BIT_ON DNM_PLS_LSICTLCAL_720		;
	MOV	#1,R3				;
DNM_PLS_LSICTLCAL_720:				;
	SUB	R3,R2				;
	CMP/PZ	R2				;
	BT	DNM_PLS_LSICTLCAL_740		;
	XOR	R2,R2				;
DNM_PLS_LSICTLCAL_740:				;



	MOV.L	#_POSCTL_SV_OFS_SPD,R1		;
	MOV.L	@R1,R3				;
	CMP/HI	R3,R2				;
	BT	DNM_PLS_LSICTLCAL_760		;OFS < CALC
	MOV	R3,R2				;MNINLINIT
;	-------------------
	MOV.L	#_POSCTL_STEP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;手動減速中
	TST_BIT_ON DNM_PLS_LSICTLCAL_800	;手動減速中なら終了

DNM_PLS_LSICTLCAL_760:				;
	MOV.L	R2,@R5				;
	FAR_JSR	#_PLS_LSI_CTL_SPDSET,R0						;LSI SET
	M_BRA	DNM_PLS_LSICTLCAL_900		;

;	-------------終了処理(STEP STOP)----------
DNM_PLS_LSICTLCAL_800:
	FAR_JSR	#_PLS_LSI_SPEED_OFF,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT5,WKREG=R1	;DEBUG
DNM_PLS_LSICTLCAL_820:
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT6,WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT3,WKREG=R1	;DEBUG

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA

	FAR_JSR	#_VIB_PLS_OUT_OF,R0	;2010-08-23加振動制御
	.AENDI

DNM_PLS_LSICTLCAL_900:
	M_BRA	DNM_PLS_LSICTLCAL_EXT						;

DNM_PLS_LSICTLCAL_ERR:
	FAR_JSR	#_PLS_LSI_SPEED_OFF,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_POSCTL_STEP_FLG,LG=W,BIT=BIT6,WKREG=R1	;

DNM_PLS_LSICTLCAL_EXT:
	SUB_END
	M_RTS


;
;
;
;
;
_DNM_AUTO_UP_DN_CALC:
	SUB_START
	MOV.L	#_ACC_ANS_ACCDAT,R1		;
	MOV.L	@R1,R0				;
	MOV.L	#_POSCTL_RL_SPD,R5		;
	MOV.L	@R5,R2				;
	ADD	R0,R2				;
	MOV.L	R2,@R5				;
	SUB_END
	M_RTS




;		
