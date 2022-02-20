
	.GLOBAL		_PAR_COP_CNTROT_ZDG1	;+10.0度
	.GLOBAL		_CB_SYS_PARAM081	;回転 ｾﾞﾛ調終了    =荷重測定開始角度
	.GLOBAL		_PAR_COP_CNTROT_ZDG2	;+20.0度
	.GLOBAL		_CB_SYS_PARAM082	;回転 荷重測定開始角度
	.GLOBAL		_PAR_COP_CNTROT_SDG1	;+20.0度
	.GLOBAL		_CB_SYS_PARAM083	;回転 荷重測定開始終了
	.GLOBAL		_PAR_COP_CNTROT_SDG2	;230.0度
	.GLOBAL		_CB_SYS_PARAM084	;反転 ｾﾞﾛ調開始角度   +N
	.GLOBAL		_PAR_COP_REVRSE_ZDG1	;5.0度
	.GLOBAL		_CB_SYS_PARAM085	;反転 ｾﾞﾛ調開始終了   +M
	.GLOBAL		_PAR_COP_REVRSE_ZDG2	;15.0度
	.GLOBAL		_CB_SYS_PARAM086	;反転 荷重測定開始角度+N 
	.GLOBAL		_PAR_COP_REVRSE_SDG1	;待機点+5.0度を横切った角度
	.GLOBAL		_CB_SYS_PARAM087	;反転 荷重測定開始終了+M
	.GLOBAL		_PAR_COP_REVRSE_SDG2	;待機点+5.0度を横切った角度:最終工程以降
	


	.EXPORT	_COP1_ROT_DT_INI
	
	.IMPORT	_ATOB_KJYUALL_SMPCLR		
	.IMPORT	_ATOB_KJYUALL_SMPSTART		;
	.IMPORT	_ATOB_KJYUTRD_SMPCLR		;CPUA=>CPUB 1: CPUB=0CLR CPUBは0ｸﾘｱする
	.IMPORT	_ATOB_KJYUTRD_SMPSTART		;CPUA= 0->1 1->0         CPUBは参照のみ

;	*******************************************
;	***					***
;	***	ﾃﾞｰﾀ転送 符号拡張		***
;	***	2Bor4B-->2B/4B			***
;	*******************************************
;;	.MACRO	DATA_STD_SHN_MOV	SRC,L1,DST,L2
;;	MOV.L	#\SRC,R5		;
;;	MOV.\L1	@R5,R2			;
;;
;;	MOV.L	#\DST,R6		;
;;	MOV.\L2	R2,@R6			;
;;	.ENDM
;;
;;	.MACRO	DATA_STD_CHG_MOV	SRC,L1,DST,L2,CALLSB
;;	MOV.L	#\SRC,R8						;
;;	MOV.\L1	@R8,R2							;
;;
;;	FAR_JSR	#\CALLSB,R0		;
;;
;;	MOV.L	#\DST,R9		;
;;	MOV.\L2	R2,@R9			;
;;	.ENDM


_COP1_ROT_DT_INI:
	SUB_START
	FAR_JSR	#_CB_COP_DT_MAK1,R0
	FAR_JSR	#_CB_COP_DT_MAK2,R0

	MOV.L	#_INC_ENC360,R1		;//360.0度(ｴﾝｺｰﾀﾞは表示と同じ)
	MOV.W	@R1,R2			;
;;;未使用	MOV.L	#_COP_ENC3600,R1	;
;;;未使用	MOV.W	R2,@R1			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	R2,@R1			;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT0),WKREG=R1

;	SH4-->SH2へ渡す　2010-12-08
	MEM_MOV_TO_MEM	SRC_ADR=_COP_CB_LD_MONI_SIG,L1=W,DST_ADR=_DP_COP_CB_LD_MONI_SIG,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3


	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	ﾊﾟﾗﾒｰﾀ			***
;	***	ｸﾗﾝｸ設定とする		***
;	***	全て待機点＋で扱う	***
;	***				***
;	***********************************


_CB_COP_DT_MAK1:
	SUB_START
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_ZDG1,L1=W,DST=_WPAR_COP_CNTROT_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_ZDG2,L1=W,DST=_WPAR_COP_CNTROT_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_SDG1,L1=W,DST=_WPAR_COP_CNTROT_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_CNTROT_SDG2,L1=W,DST=_WPAR_COP_CNTROT_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_ZDG1,L1=W,DST=_WPAR_COP_REVRSE_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_ZDG2,L1=W,DST=_WPAR_COP_REVRSE_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_SDG1,L1=W,DST=_WPAR_COP_REVRSE_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_PAR_COP_REVRSE_SDG2,L1=W,DST=_WPAR_COP_REVRSE_SDG2,L2=W


	SUB_END
	M_RTS

;	===================================
;	===				===
;	===	動作時の入れ替え	===
;	===				===
;	===================================
;	待機点＋設定に変換する
_CB_COP_DT_MAK2:
	SUB_START

;	=========[2009-10-07下振子]
	MOV.L	#_SET1_MRTION_SEL1,R1						;
	MOV.W	@R1,R0								;
	TST	#(_DMATH_DNDRIV),R0						;2007-09-06
	TST_BIT_ON CB_COP_DT_MK2_010						;
	M_BRA	CB_COP_DT_MK2_050						;

CB_COP_DT_MK2_010						;

;	-------往路-------
;	反転のﾃﾞｰﾀを使用する
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPARX_COP_DNDRV1_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPARX_COP_DNDRV1_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPARX_COP_DNDRV1_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPARX_COP_DNDRV1_SDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;

;	-------復路-------
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPARX_COP_DNDRV2_ZDG1,L2=W,CALLSB=_NEG_TAIKI_SUB;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPARX_COP_DNDRV2_ZDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPARX_COP_DNDRV2_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPARX_COP_DNDRV2_SDG2,L2=W,CALLSB=_NEG_TAIKI_SUB;


;	-- 2007-09-06 [荷重補正][ふりこ往路]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETX_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETX_KJEND_DIG1,L2=W;

;	-----------------------[ふりこ復路]
	DATA_STD_CHG_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETY_KJSTR_DIG1,L2=W,CALLSB=_NEG_TAIKI;
	DATA_STD_CHG_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETY_KJEND_DIG1,L2=W,CALLSB=_NEG_TAIKI;



;	-- 2014-05-30 --[ﾄﾚﾝﾄﾞ][ふりこ往路]
;;;;;2014-10-10不具合	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
;;;;;2014-10-10不具合	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETX_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETX_KJEND_DIG2,L2=W;

;	-----------------------[ふりこ復路]
	DATA_STD_CHG_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETY_KJSTR_DIG2,L2=W,CALLSB=_NEG_TAIKI;
	DATA_STD_CHG_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETY_KJEND_DIG2,L2=W,CALLSB=_NEG_TAIKI;
	M_BRA	CB_COP_DT_MK2_200



CB_COP_DT_MK2_050:
;;[2009-10-07下振子]	MOV.L	#_SET1_MRTION_SEL1,R1	;
;;[2009-10-07下振子]	MOV.W	@R1,R0			;
	CMP/EQ	#_DMATH_CNTROT,R0	;DRIVE MATH 連続回転
	BF	CB_COP_DT_MK2_100	;NO:反転

;	------- 回転(待機点0だからいいけど)-------
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_CNTROT_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W,CALLSB=_TAIKI_ADD;

;	-- 2009-10-07 --[荷重補正][回転]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

;	-- 2014-05-30 --[ﾄﾚﾝﾄﾞ][回転]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;

	M_BRA	CB_COP_DT_MK2_200	

CB_COP_DT_MK2_100:
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W,CALLSB=_TAIKI_ADD;
	DATA_STD_CHG_MOV	SRC=_WPAR_COP_REVRSE_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W,CALLSB=_TAIKI_ADD;

;	-- 2009-10-07 --[荷重補正][反転]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;

;	-- 2014-05-30 --[ﾄﾚﾝﾄﾞ][反転]
	DATA_STD_SHN_MOV	SRC=_SET1_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SET1_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;

CB_COP_DT_MK2_200:

	SUB_END
	M_RTS

;	***************************
;	***	待機点+data	***
;	***************************
;	
_TAIKI_ADD;
	SUB_START
	MOV.L	#_SETX_UPAREA_DIG,R1					;2;回転/反転時待機点
	MOV.W	@R1,R0							;
	DIG_REGA_ADD_REGB_ANS_REGB REGA=R0,REGB=R2,WKREG=R1,LATE=3600	;R0+R2==>R2
	SUB_END
	M_RTS

;	***************************
;	***	2009-10-07下振子***
;	***************************
;	Input +R2
_NEG_TAIKI_SUB;
	SUB_START

	MOV.L	#_SETX_UPAREA_DIG,R1					;2;回転/反転時待機点
	MOV.W	@R1,R1							;
	MOV.W	#3600,R0						;
	SUB	R1,R0							;
	DIG_REGA_SUB_REGB_ANS_REGB REGA=R2,REGB=R0,WKREG=R1,LATE=3600	;R0=R0-R2
	MOV	R0,R2							;

	SUB_END
	M_RTS

;	***************************
;	***	2009-10-07下振子***
;	***************************
;	Input +R2
_NEG_TAIKI;
	SUB_START

	MOV.W	#3600,R0						;
	SUB	R2,R0							;
	MOV	R0,R2							;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	データ入れ替え			***
;	***	2009-10-07	下振子		***
;	*******************************************
_SIG_AREA_DATA_CHG:
	SUB_START
	MOV.L	#_DNM_DIR_SET_FLG,R1			;
	MOV.W	@R1,R0					;
	MOV.L	#_DNM_DIR_FLG_OLD,R1			;
	MOV.W	@R1,R2					;
	MOV.W	R0,@R1					;
	XOR	R2,R0					;CHG DIRECTION
	TST	R0,R0					;
	TST_BIT_OF SIG_AREA_DATCHG050			;

	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=~(BIT2+BIT1),WKREG=R1				;BIT1:生信号
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)),WKREG=R1	;2006-07-28

SIG_AREA_DATCHG050:

	MOV.L	#_SET1_MRTION_SEL1,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_CNTROT,R0			;
	TST_BIT_OF SIG_AREA_DATCHG100			;

	M_BRA	SIG_AREA_DATCHG500			;

SIG_AREA_DATCHG100:

	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON SIG_AREA_DATCHG120			;
	M_BRA	SIG_AREA_DATCHG200			;

SIG_AREA_DATCHG120:
	MOV.L	#_DNM_DIR_SET_FLG,R1			;
	MOV.W	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_ON SIG_AREA_DATCHG150

;-------- 往路-------
	DATA_STD_SHN_MOV	SRC=_SETX_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETX_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV1_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_SETX_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETX_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
	M_BRA	SIG_AREA_DATCHG190


SIG_AREA_DATCHG150:
	DATA_STD_SHN_MOV	SRC=_SETY_KJSTR_DIG1,L1=W,DST=_SETC_KJSTR_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETY_KJEND_DIG1,L1=W,DST=_SETC_KJEND_DIG1,L2=W;
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG1,L1=W,DST=_WPAR_COP_ZDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_ZDG2,L1=W,DST=_WPAR_COP_ZDG2,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG1,L1=W,DST=_WPAR_COP_SDG1,L2=W
	DATA_STD_SHN_MOV	SRC=_WPARX_COP_DNDRV2_SDG2,L1=W,DST=_WPAR_COP_SDG2,L2=W

	DATA_STD_SHN_MOV	SRC=_SETY_KJSTR_DIG2,L1=W,DST=_SETC_KJSTR_DIG2,L2=W;
	DATA_STD_SHN_MOV	SRC=_SETY_KJEND_DIG2,L1=W,DST=_SETC_KJEND_DIG2,L2=W;
SIG_AREA_DATCHG190:
	M_BRA	SIG_AREA_DATCHG500			;

SIG_AREA_DATCHG200:


SIG_AREA_DATCHG500:



	SUB_END
	M_RTS

;	***************************
;	***			***
;	***************************
;
;	工程=1~MAX
;	0:終了ﾌﾗｸﾞ,0:開始ﾌﾗｸﾞ
;
;	//原点復帰ではやらない
;	//RESET解除時にｲﾆｼｬﾙ処理を行う:終了状態 BIT1=0(ｻﾝﾌﾟﾘﾝｸﾞ開始有効の意味)
;	//
;
;	(1)ｸﾗｯﾁに運転開始ｶｳﾝﾀを作る
;	(2)中断
;	(3)完了
;
;	回転
;	開始条件 :運転開始+角度a～角度b
;	終了条件 :角度Bをcwで横切った

;	反転
;	開始条件 :運転開始+角度a～角度b
;	終了条件 :最終工程で且つ角度aより待機点側にいる
;
;	=========================
;	COP_CB_LD_MONI_SIG;//荷重測定用信号 2003-01-31
;	BIT0=1 常時ON
;	BIT1=1 ゼロ調整角度
;	BIT2=1 荷重測定角度
;	BIT3=1 荷重測定完了
;	(BIT4)=1 ｾﾞﾛ調完了
;	BIT5=1 ACTIVE
;	*ｾﾞﾛ調整信号より荷重測定を優先する。
;
;	[ﾄﾚﾝﾄﾞ,最大値,最小値,幅ｻﾝﾌﾟﾘﾝｸﾞ]--->226.13
;	KJ_AREATRD_SIG：_KAJYUU_AREA2_SIGMAK
;		BIT0:1:指定位置内
;		BIT1:1:測定開始(行程含む)～サイクル終了
;		BIT2:1:測定終了
;		BIT3
;		BIT4
;		BIT5:測定開始(BIT1と同時)~測定終了()
;		BIT6:1:終了～サイクル終了
;		BIT7
;
;	[荷重補正]	----->226.5を見ればよい
;	_KJ_AREA_SIG：：_KAJYUU_AREA1_SIGMAK
;		BIT0:1:指定位置内
;		BIT1:1:測定開始(行程含む)～サイクル終了
;		BIT2:1:測定終了
;		BIT3
;		BIT4
;		BIT5:測定開始(BIT1と同時)~測定終了()
;		BIT6:1:終了～サイクル終了
;		BIT7
;


	.EXPORT	_CB_COP_SIG_MAK	
_CB_COP_SIG_MAK:		;
	SUB_START

	FAR_JSR	#_SIG_AREA_DATA_CHG,R0	;[2009-10-07下振子]

	MOV.L	#_INC_ENC360,R1		;//360.0度(ｴﾝｺｰﾀﾞは表示と同じ)
	MOV.W	@R1,R2			;
	MOV	R2,R8			;R8:NOW
;;;未使用	MOV.L	#_COP_ENC3600,R1	;
;;;未使用	MOV.W	R2,@R1			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	@R1,R9			;R9:OLD
;;;;このﾀｲﾐﾝｸﾞでﾘﾌﾚｯｼｭはしない	MOV.W	R2,@R1			;

	MOV.L	#_SEQAB_DP_TOP+109*2,R1		;
	MOV.W	@R1,R0				;109.12
	MOV.W	#BIT12,R4			;
	TST	R4,R0				;
	TST_BIT_ON CB_COP_SIGMK_100		;

	MOV.W	#BIT0,R0			;
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;荷重測定しない
	MOV.W	R0,@R1				;BIT0=1(常時)
	
	XOR	R0,R0				;
	MOV.L	#_COP_DIG_SIG_FLG,R1		;
	MOV.W	R0,@R1				;
	
;	------ 2006-07-28----
	XOR	R0,R0				;
	MOV.L	#_KJ_AREA_SIG,R1;
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;2013-06-19
	MOV.W	R0,@R1				;

	MOV.L	#_KJ_AREATRD_SIG,R1
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1;//2013-06-19
	MOV.W	R0,@R1				;

	M_BRA	CB_COP_SIGMK_EXT		;


;	*******************************************
;	***					***
;	***	運転・非運転に関わらず行う	***
;	***					***
;	*******************************************
;	Z-DIG1:CWで横切ったらONor区間
;	Z-DIG2:CWで横切ったらOFF+完了
;	S-DIG1:CWで横切ったらONor区間(待機点)
;	S-DIG2:CWで横切ったらOFF+完了(待機点)
;	==========================
;	Z-DIG1:CWで横切ったらONor区間
;	Z-DIG2:CWで横切ったらOFF+完了
;	S-DIG1:CWで横切ったらONor区間(待機点+6度以上~180)
;	S-DIG2:CCWで横切ったらOFF+完了 (待機点+5度以下) SDIG2<SIDG1 (SDIG2が待機点に近い)
;
CB_COP_SIGMK_100:				;
	MOV.L	#_COP_DIG_SIG_FLG,R1				;
	MOV.W	@R1,R0						;
	TST	#BIT2,R0					;荷重測定中
	TST_BIT_ON CB_COP_SIGMK_120				;ZERO調整信号OFF

;	=============ｾﾞﾛ調整信号作成====================
	MOV.L	#_WPAR_COP_ZDG1,R0							;ZERO調整開始角度
	MOV.W	@R0,R1									;
	MOV.L	#_WPAR_COP_ZDG2,R0							;終了角度
	MOV.W	@R0,R3									;
	MOV	R8,R2									;
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0				;
	CMP/EQ	#1,R0									;
	BF	CB_COP_SIGMK_120							;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_DIG_SIG_FLG,LG=W,BIT=BIT1,WKREG=R1		;範囲内
	M_BRA	CB_COP_SIGMK_150							;

CB_COP_SIGMK_120:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=~BIT1,WKREG=R1		;BIT1:生信号
CB_COP_SIGMK_150:									;


;	============ 荷重信号 ============
	MOV.L	#_SET1_MRTION_SEL1,R1		;
	MOV.W	@R1,R0				;
;;2009-10-07下振子	CMP/EQ	#_DMATH_CNTROT,R0		;DRIVE MATH 連続回転
;;2009-10-07下振子	BF	CB_COP_SIGMK_250		;反転

	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0	;2009-10-06
	TST_BIT_OF CB_COP_SIGMK_250			;NO:反転

;	=== 回転 ==
	MOV.L	#_WPAR_COP_SDG1,R0			;荷重開始角度
	MOV.W	@R0,R1					;
	MOV.L	#_WPAR_COP_SDG2,R0			;終了角度
	MOV.W	@R0,R3					;
	M_BRA	CB_COP_SIGMK_280			;

;	=== 反転 ==
CB_COP_SIGMK_250:
	MOV.L	#_COP_DIG_SIG_FLG,R1				;
	MOV.W	@R1,R0						;
	TST	#BIT2,R0					;ON
	TST_BIT_ON CB_COP_SIGMK_270				;

	MOV.L	#_WPAR_COP_SDG1,R0			;荷重開始角度
	MOV.W	@R0,R1					;
	MOV.W	#_UPDN_DIRJG_DIG,R3			;"角度(距離ではない つもり)"
	M_BRA	CB_COP_SIGMK_280			;

CB_COP_SIGMK_270:
	MOV.L	#_WPAR_COP_SDG2,R0				;終了角度~待機点な角度保持
	MOV.W	@R0,R1						;
	MOV.L	#_SETX_UPAREA_DIG,R0				;
	MOV.W	@R0,R3						;

CB_COP_SIGMK_280:
	MOV	R8,R2									;
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0				;
	CMP/EQ	#1,R0									;
	BF	CB_COP_SIGMK_290							;範囲外
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_DIG_SIG_FLG,LG=W,BIT=(BIT2),WKREG=R1		;荷重SET
	M_BRA	CB_COP_SIGMK_300

CB_COP_SIGMK_290:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_DIG_SIG_FLG,LG=W,BIT=(~BIT2),WKREG=R1		;荷重ｸﾘｱ
CB_COP_SIGMK_300:


;	===== 出力信号作成 ======
	MOV.L	#_COP_DIG_SIG_FLG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT1,R0		;
	TST_BIT_ON CB_COP_SIGMK_550	;

	MOV.L	#_COP_CB_LD_MONI_SIG,R1	;
	MOV.W	@R1,R0			;
	TST	#BIT1,R0		;
	TST_BIT_OF CB_COP_SIGMK_520	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT4),WKREG=R1	;ｾﾞﾛ完了
CB_COP_SIGMK_520:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT1),WKREG=R1	;ｾﾞﾛｸﾘｱ
	M_BRA	CB_COP_SIGMK_580	;

CB_COP_SIGMK_550:
;;2006-07-28	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT4+BIT3+BIT2)),WKREG=R1	;ｾﾞﾛ完了ｸﾘｱ
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~(BIT6+BIT5+BIT4+BIT3+BIT2)),WKREG=R1	;2006-07-28
												;ｾﾞﾛ完了ｸﾘｱ
												;荷重測定中ｸﾘｱ
												;荷重完了ｸﾘｱ
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT1),WKREG=R1		;ｾﾞﾛ中

;	------｢ｾﾞﾛ調整中｣----
	XOR	R0,R0				;
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;2013-06-19
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG,R1
	MOV.W	R0,@R1				;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;

;	-------------- 荷重前回ﾃﾞｰﾀｸﾘｱ----------
	MOV.B	#BIT0,R0			;
	MOV.L	#_ATOB_KJYUALL_SMPCLR,R1	;ｸﾘｱしろ
	MOV.W	R0,@R1				;
	MOV.L	#_ATOB_KJYUTRD_SMPCLR,R1	;ｸﾘｱしろ
	MOV.W	R0,@R1				;
;	-------------------------------------------




CB_COP_SIGMK_580:


	MOV.L	#_COP_DIG_SIG_FLG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;
	TST_BIT_ON CB_COP_SIGMK_650						;

	MOV.L	#_COP_CB_LD_MONI_SIG,R1							;
	MOV.W	@R1,R0									;
	TST	#BIT2,R0								;荷重測定中だったか？
	TST_BIT_OF CB_COP_SIGMK_620							;NO
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT3),WKREG=R1	;荷重測定完了
CB_COP_SIGMK_620:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT2),WKREG=R1	;荷重測定ｸﾘｱ
	M_BRA	CB_COP_SIGMK_680	;

CB_COP_SIGMK_650:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(~BIT3),WKREG=R1	;荷重完了ｸﾘｱ
	MEM1_BIT0_TO_BIT7_ORSET MEM=_COP_CB_LD_MONI_SIG,LG=W,BIT=(BIT2),WKREG=R1	;荷重測定中
CB_COP_SIGMK_680:

;	------------ 2014-05-30--------------
	FAR_JSR	#_KAJYUU_AREA2_SIGMAK,R0		;

;	=========2006-07-28 BIT4,5 REFLASH========
	FAR_JSR	#_KAJYUU_AREA1_SIGMAK,R0		;


	MOV.W	#(BIT6+BIT5),R4			;
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	@R1,R0				;
	AND	#(BIT6+BIT5),R0			;
	NOT	R4,R4
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;
	MOV.W	@R1,R2				;
	AND	R4,R2				;
	OR	R0,R2				;
	MOV.W	R2,@R1				;


;	----------- ﾃﾞﾊﾞｯｸ用BIT8~BIT15(ﾄﾚﾝﾄﾞ--------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	SHLL8	R0				;
	EXTU.B	R2,R2				;
	OR	R0,R2				;

	MOV.L	#(_SQ_CBWK_TOP+26*2),R1		;_SQCB226.7~0=COP_CB_LD_MONI_SIG
	MOV.W	R2,@R1				;


;	---------2014-02-05 最小値,最大値,幅ｻﾝﾌﾟﾘﾝｸﾞ(荷重計と同じ区間 60~270度)--------------
	MOV.L	#_COP_CB_LD_MONI_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;
	TST_BIT_ON KAJYUU_MIN_SMP100		;[全体の測定開始指令中　29~238度]

	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1	;ｻﾝﾌﾟﾘﾝｸﾞ指令OFF
	MOV.W	@R1,R2				;
	TST	R2,R2
	TST_BIT_OF KAJYUU_MIN_SMP250		;

	XOR	R2,R2				;
	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1	;ｻﾝﾌﾟﾘﾝｸﾞ指令OFF
	MOV.W	R2,@R1				;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJYU_CMP_CMD,LG=W,BIT=BIT1,WKREG=R1	;BIT1終了した瞬間
	M_BRA	KAJYUU_MIN_SMP250		;

KAJYUU_MIN_SMP100

	MOV.L	#_ATOB_KJYUALL_SMPSTART,R1		;ｻﾝﾌﾟﾘﾝｸﾞ指令
	MOV.W	@R1,R2				;
	TST	R2,R2				;以前はOFFだったか
	TST_BIT_ON KAJYUU_MIN_SMP200		;NO ON


	MOV.W	#BIT0,R3			;
	MOV.L	#_ATOB_KJYUALL_SMPCLR,R4	;ｸﾘｱしろ
	MOV.W	R3,@R4				;

	MOV.W	#BIT0,R2			;測定開始しろ
	MOV.W	R2,@R1				;
	M_BRA	CB_COP_SIGMK_EXT		;

;
KAJYUU_MIN_SMP200
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJYU_CMP_CMD,LG=W,BIT=BIT0,WKREG=R1	;BIT0 比較区間




KAJYUU_MIN_SMP250:
CB_COP_SIGMK_EXT:


	MOV.L	#_INC_ENC360,R1		;//360.0度(ｴﾝｺｰﾀﾞは表示と同じ)
	MOV.W	@R1,R2			;
	MOV.L	#_COP_OLD_ENC3600,R1	;
	MOV.W	R2,@R1			;


	FAR_JSR	#_KAJYUU_DEBUG_ANACHG,R0	;あっても悪さはしない

	FAR_JSR	#_KAJYUU_OVER_LOW_CHK,R0	;


	SUB_END
	M_RTS


;	***************************************************
;	***						***
;	***	本当は工程も管理しないといけない	***
;	***						***
;	***************************************************
;	BIT0=1 AREA内
;	BIT1=1 STARTに入ったまたは工程が超えた
;	BIT2=1 ENDを超えたまたは範囲外になった
;	CLR 工程MAX~工程1になった
;
;	[荷重補正区間]
;
_KAJYUU_AREA1_SIGMAK:
	SUB_START
	MOV.L	#_SETC_KJSTR_DIG1,R4						;[2009-10-07下振子]
	MOV.W	@R4,R1								;
	MOV.L	#_INC_ENC360,R4							;
	MOV.W	@R4,R2								;

	MOV.L	#_SETC_KJEND_DIG1,R4						;[2009-10-07下振子]
	MOV.W	@R4,R3			
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BF	KAYJUU_AREA1SIGMK050						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT0),WKREG=R1	;AREA-ON
	M_BRA	KAYJUU_AREA1SIGMK090						;
KAYJUU_AREA1SIGMK050:								;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT0),WKREG=R1	;
KAYJUU_AREA1SIGMK090:								;


;	-------- 開始条件----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA1SIGMK200						;

	MOV.L	#_SET1_KJSTR_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA1SIGMK130						;0:POS

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA1SIGMK190						;工程=0
	
	CMP/HI	R0,R2								;工程を超えた
	BT	KAYJUU_AREA1SIGMK150						;
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA1SIGMK190						;

KAYJUU_AREA1SIGMK130:								;
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT0,R0							;
	TST_BIT_OF KAYJUU_AREA1SIGMK190						;
KAYJUU_AREA1SIGMK150:								;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT5+BIT1),WKREG=R1	;AREA-ON
KAYJUU_AREA1SIGMK190:								;
	M_BRA	KAYJUU_AREA1SIGMK900						;

KAYJUU_AREA1SIGMK200:
;	-------- 終了条件----
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA1SIGMK290						;(測定終了,次のｻｲｸﾙ待ち)


;;;;	MOV.L	#_SET1_KJEND_STEP1,R1						;
;;;;	MOV.W	@R1,R0								;
;;;;	TST	R0,R0								;
;;;;	TST_BIT_ON KAYJUU_AREA1SIGMK220						;POS以外
;;;;
;;;;
;;;;	MOV.L	#_SET1_MRTION_SEL1,R4						;
;;;;	MOV.W	@R4,R0								;
;;;;	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0				;回転orふりこか
;;;;	TST_BIT_OF KAYJUU_AREA1SIGMK240						;反転
;;;;
;;;;;	--------回転またはふりこの位置カム--------------
;;;;	MOV.L	#_KJ_AREA_SIG,R1		;
;;;;	MOV.W	@R1,R0				;
;;;;	TST	#BIT0,R0			;位置範囲?
;;;;	TST_BIT_OF KAYJUU_AREA1SIGMK250		;位置範囲から出たCLR
;;;;	M_BRA	KAYJUU_AREA1SIGMK290		;


;----------工程指定-------------
KAYJUU_AREA1SIGMK220:
	MOV.L	#_SET1_KJEND_STEP1,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA1SIGMK230						;

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA1SIGMK290						;工程=0

	CMP/HI	R0,R2								;工程を超えた
	BT	KAYJUU_AREA1SIGMK250						;終了

	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA1SIGMK290						;

KAYJUU_AREA1SIGMK230:
	MOV.L	#_SET1_MRTION_SEL1,R4				;
	MOV.W	@R4,R0						;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;回転orふりこか
	TST_BIT_OF KAYJUU_AREA1SIGMK240				;反転
	NOP
KAYJUU_AREA1SIGMK240:						;
;	-------- 位置カムまたは工程カムの現行工程-------------
	MOV.L	#_KJ_AREA_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON KAYJUU_AREA1SIGMK290		;ONしている

	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ONしていた
	TST_BIT_ON KAYJUU_AREA1SIGMK250		;
	M_BRA	KAYJUU_AREA1SIGMK290		;

;	------------反転の場合だけ----------------
;;;;KAYJUU_AREA1SIGMK240:
;;;;
;;;;	MOV.L	#_COP_OLD_ENC3600,R0			;
;;;;	MOV.W	@R0,R4					;
;;;;	MOV.L	#_SETC_KJEND_DIG1,R0			;・・・・
;;;;	MOV.W	@R0,R2					;
;;;;	MOV.L	#_INC_ENC360,R0				;逆回転で横切ったら;
;;;;	MOV.W	@R0,R1			
;;;;
;;;;	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
;;;;	CMP/EQ	#1,R0								;
;;;;	BT	KAYJUU_AREA1SIGMK250						;
;;;;	M_BRA	KAYJUU_AREA1SIGMK290						;
KAYJUU_AREA1SIGMK250:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREA_SIG,LG=W,BIT=(~BIT5),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREA_SIG,LG=W,BIT=(BIT6+BIT2),WKREG=R1	;END SET
KAYJUU_AREA1SIGMK290:								;
	NOP
KAYJUU_AREA1SIGMK900				;

KAYJUU_AREA1SIGMKEXT
	MOV.L	#_KJ_AREA_SIG,R1						;
	MOV.W	@R1,R0								;
	MOV.L	#_KJ_AREA_BT0_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;


	SUB_END
	M_RTS








;	***************************************************
;	***						***
;	***	本当は工程も管理しないといけない	***
;	***						***
;	***************************************************
;	BIT0=1 AREA内
;	BIT1=1 STARTに入ったまたは工程が超えた
;	BIT2=1 ENDを超えたまたは範囲外になった
;	CLR 工程MAX~工程1になった
;
;	[トレンド区間]
;
_KAJYUU_AREA2_SIGMAK:
	SUB_START
	MOV.L	#_SETC_KJSTR_DIG2,R4						;[2009-10-07下振子]
	MOV.W	@R4,R1								;
	MOV.L	#_INC_ENC360,R4							;
	MOV.W	@R4,R2								;

	MOV.L	#_SETC_KJEND_DIG2,R4						;[2009-10-07下振子]
	MOV.W	@R4,R3			
	DIG_AREA_CHK STREG=R1,EDREG=R3,PVREG=R2,ANSREG=R0			;
	CMP/EQ	#1,R0								;
	BF	KAYJUU_AREA2SIGMK050						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT0),WKREG=R1	;AREA-ON
	M_BRA	KAYJUU_AREA2SIGMK090						;
KAYJUU_AREA2SIGMK050:								;
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREATRD_SIG,LG=W,BIT=(~BIT0),WKREG=R1	;
KAYJUU_AREA2SIGMK090:								;


;	-------- 開始条件----
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT1,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA2SIGMK200						;

	MOV.L	#_SET1_KAJAREA_SNO,R1						;開始工程
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK130						;0:POS

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA2SIGMK190						;工程=0

	CMP/HI	R0,R2								;工程を超えた
	BT	KAYJUU_AREA2SIGMK150						;
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA2SIGMK190						;

KAYJUU_AREA2SIGMK130:									;
	MOV.L	#_KJ_AREATRD_SIG,R1							;
	MOV.W	@R1,R0									;
	TST	#BIT0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK190							;
KAYJUU_AREA2SIGMK150:									;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT5+BIT1),WKREG=R1	;BIT1,BIT5:工程で且つ角度ON
KAYJUU_AREA2SIGMK190:									;
	M_BRA	KAYJUU_AREA2SIGMK900							;

KAYJUU_AREA2SIGMK200:
;	-------- 終了条件----
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	TST	#BIT2,R0							;START ON?
	TST_BIT_ON KAYJUU_AREA2SIGMK290						;終了　次のサイクル待ち


;----------工程指定-------------
KAYJUU_AREA2SIGMK220:
	MOV.L	#_SET1_KAJAREA_ENO,R1						;
	MOV.W	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF KAYJUU_AREA2SIGMK230						;

	MOV.L	#_INT_POS_CTL_STEP,R1						;
	MOV.W	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF KAYJUU_AREA2SIGMK290						;工程=0
	
	CMP/HI	R0,R2								;工程を超えた
	BT	KAYJUU_AREA2SIGMK250						;CLR
	CMP/EQ	R0,R2								;
	BF	KAYJUU_AREA2SIGMK290						;

KAYJUU_AREA2SIGMK230:
	MOV.L	#_SET1_MRTION_SEL1,R4				;
	MOV.W	@R4,R0						;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0		;回転orふりこか
	TST_BIT_OF KAYJUU_AREA2SIGMK240				;反転
	NOP
KAYJUU_AREA2SIGMK240:						;
;	-------- 位置カムまたは工程カムの現行工程-------------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_ON KAYJUU_AREA2SIGMK290		;ONしている

	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;ONしていた
	TST_BIT_ON KAYJUU_AREA2SIGMK250		;
	M_BRA	KAYJUU_AREA2SIGMK290		;

KAYJUU_AREA2SIGMK250:
	MEM1_BIT0_TO_BIT7_ANDCLR MEM=_KJ_AREATRD_SIG,LG=W,BIT=(~BIT5),WKREG=R1	;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_KJ_AREATRD_SIG,LG=W,BIT=(BIT6+BIT2),WKREG=R1	;END SET
KAYJUU_AREA2SIGMK290:								;
	NOP
KAYJUU_AREA2SIGMK900				;

KAYJUU_AREA2SIGMKEXT
	MOV.L	#_KJ_AREATRD_SIG,R1						;
	MOV.W	@R1,R0								;
	MOV.L	#_KJ_AREATRD_SIG_OLD,R1		;//2013-06-19
	MOV.W	R0,@R1				;



;	---------2014-02-05 最小値,最大値,幅ｻﾝﾌﾟﾘﾝｸﾞ(荷重計と同じ区間 60~270度)--------------
	MOV.L	#_KJ_AREATRD_SIG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;終了?
	TST_BIT_ON KAYJUU_AREA2SMP050		;
	TST	#BIT1,R0			;
	TST_BIT_ON KAYJUU_AREA2SMP100		;開始? YES JUMP

KAYJUU_AREA2SMP050
	XOR	R2,R2				;
	MOV.L	#_ATOB_KJYUTRD_SMPSTART,R1	;ｻﾝﾌﾟﾘﾝｸﾞ指令OFF
	MOV.W	R2,@R1				;
	M_BRA	KAYJUU_AREA2SMP200		;

KAYJUU_AREA2SMP100
	MOV.L	#_ATOB_KJYUTRD_SMPSTART,R1		;ｻﾝﾌﾟﾘﾝｸﾞ指令
	MOV.W	@R1,R2				;
	TST	R2,R2				;以前はOFFだったか
	TST_BIT_ON KAYJUU_AREA2SMP200		;NO ON


	MOV.W	#BIT0,R3			;
	MOV.L	#_ATOB_KJYUTRD_SMPCLR,R4		;ｸﾘｱしろ
	MOV.W	R3,@R4				;

	MOV.W	#BIT0,R2			;測定開始しろ
	MOV.W	R2,@R1				;

KAYJUU_AREA2SMP200

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
;	全体区間に対する比較
;	最大値、最小値(ﾏｲﾅｽ最大),幅に対して比較を行う。
;	最大値の場合のｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄは荷重計が行う.
;	最小値(ﾏｲﾅｽ最大),幅値に対して行う。
;	SW=0000,0001(最大値比較)
;	SW=0000,0010(最小値比較)
;	SW=0000,0100(幅比較)
;
;	.GLOBAL	_KJYU_CMP_CMD;		//BIT0=1 :ｵｰﾊﾞﾛｰﾄﾞ比較(区間内) BIT1=1ﾛｱﾘﾐｯﾄ比較(区間過)
;	.GLOBAL	_KJYU_CMP_SELSW1;	//BIT0,BIT1(),BIT2()
;	.GLOBAL	_KJYU_CMP_SELSW2;	//BIT0,BIT1(),BIT2()
;	.GLOBAL	_KJYU_CMP_SEQMINS;	//最小値(ﾏｲﾅｽ側) ｵｰﾊﾞBIT0(左),BIT1(右),BIT2(合計)
;	.GLOBAL	_KJYU_CMP_SEQHABA;	//幅             ｵｰﾊﾞBIT0(左),BIT1(右),BIT2(合計)


_KAJYUU_OVER_LOW_CHK
	SUB_START
	MOV.L	#_di1_cb_ctl1_dt,R1			;ﾚﾍﾞﾙに変更
	MOV.W	@R1,R0					;
	MOV.W	#_W1RST,R4				;ﾘｾｯﾄ釦
	TST	R4,R0					;
	TST_BIT_OF KAJYUU_OVER_LOWCHK100		;
	XOR	R0,R0					;ﾘｾｯﾄ:ｼｰｹﾝｽｸﾘｱ
	MOV.L	#_KJYU_CMP_SEQMINS,R1			;
	MOV.W	R0,@R1					;
	MOV.L	#_KJYU_CMP_SEQHABA,R1			;
	MOV.W	R0,@R1					;
	MOV.L	#_KJYU_CMP_CMD,R1			;
	MOV.W	R0,@R1					;
	M_BRA	KAJYUU_OVER_LOWCHKEXT			;

KAJYUU_OVER_LOWCHK100

	MOV.L	#_KJYU_CMP_CMD,R5			;
	MOV.W	@R5,R0					;
	TST	#BIT0,R0				;
	TST_BIT_OF KAJYUU_OVER_LOWCHK200		;BIT0=1:ｵｰﾊﾞﾛｰﾄﾞ区間
	AND	#LOW ~BIT0,R0				;
	MOV.W	R0,@R5					;


	FAR_JSR	#_KAJYU_OVERLOAD_CHK,R0			;


KAJYUU_OVER_LOWCHK200

	MOV.L	#_KJYU_CMP_CMD,R5			;
	MOV.W	@R5,R0					;
	TST	#BIT1,R0				;
	TST_BIT_OF KAJYUU_OVER_LOWCHK300		;BIT1=1:ﾛｱﾘﾐｯﾄ区間
	AND	#LOW ~BIT1,R0				;
	MOV.W	R0,@R5					;


	FAR_JSR	#_KAJYU_LOWLIMIT_CHK,R0			;


KAJYUU_OVER_LOWCHK300
KAJYUU_OVER_LOWCHKEXT

	MOV.L	#_KJYU_CMP_SEQMINS,R1		;比較信号ｾｯﾄ
	MOV.W	@R1,R0				;
	EXTU.W	R0,R0
	MOV.L	#_KJYU_CMP_SEQHABA,R1		;
	MOV.W	@R1,R2				;
	SHLL8	R2
	OR	R2,R0
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB250,R1	;250
	MOV.W	R0,@R1				;



	SUB_END
	M_RTS


;_BTOA_LFT_MAX		.SRES	4	;(これは使用しない予定,荷重計がやっているから)
;_BTOA_LFT_HAB		.SRES	4	;

;_BTOA_RIH_MAX		.SRES	4	;(これは使用しない予定,荷重計がやっているから)
;_BTOA_RIH_HAB		.SRES	4	;

;_BTOA_TTL_MAX		.SRES	4	;(これは使用しない予定,荷重計がやっているから)
;_BTOA_TTL_HAB		.SRES	4	;

;	-------------- 最小(ﾏｲﾅｽ最大)選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	.IMPORT		_SVP_OVERE1_A27			; 荷重計　オーバーロード１ 　（最小値）
	.IMPORT		_SVP_ROALM1_A27			; 荷重計　ロアーリッミト１  　（最小値）
	.IMPORT		_SVP_OVERE2_A27			; 荷重計　オーバーロード２  　（最小値）
	.IMPORT		_SVP_ROALM2_A27			; 荷重計　ロアーリッミト２  　（最小値）
	.IMPORT		_SVP_OVERE3_A27			; 荷重計　オーバーロード３  　（最小値）
	.IMPORT		_SVP_ROALM3_A27			; 荷重計　ロアーリッミト３  　（最小値）

;	-------------- 振幅選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	.IMPORT		_SVP_OVERE1_A28			; 荷重計　オーバーロード１ 　（振幅）
	.IMPORT		_SVP_ROALM1_A28			; 荷重計　ロアーリッミト１  　（振幅）
	.IMPORT		_SVP_OVERE2_A28			; 荷重計　オーバーロード２  　（振幅）
	.IMPORT		_SVP_ROALM2_A28			; 荷重計　ロアーリッミト２  　（振幅）
	.IMPORT		_SVP_OVERE3_A28			; 荷重計　オーバーロード３  　（振幅）
	.IMPORT		_SVP_ROALM3_A28			; 荷重計　ロアーリッミト３  　（振幅）

;	--------全区間(ｵｰﾊﾞﾛｰﾄﾞ,ﾛﾘﾐｯﾄ用)-------------------
	.IMPORT		_BTOA_LFT_MAX		;(これは使用しない予定,荷重計がやっているから)
	.IMPORT		_BTOA_LFT_MIN		;
	.IMPORT		_BTOA_LFT_HAB		;

	.IMPORT		_BTOA_RIH_MAX		;(これは使用しない予定,荷重計がやっているから)
	.IMPORT		_BTOA_RIH_MIN		;
	.IMPORT		_BTOA_RIH_HAB		;

	.IMPORT		_BTOA_TTL_MAX		;(これは使用しない予定,荷重計がやっているから)
	.IMPORT		_BTOA_TTL_MIN		;
	.IMPORT		_BTOA_TTL_HAB		;


;	*******************************************
;	***					***
;	***	ｵｰﾊﾞﾛｰﾄﾞ			***
;	***					***
;	*******************************************
_KAJYU_OVERLOAD_CHK:
	SUB_START


;;	MOV.L	#_KJYU_CMP_SELSW1,R1		;
	MOV.L	#_CB_SEQ_SW_SEL058,R1		;00
	MOV.W	@R1,R0				;
	SHLR8	R0				;BIT9,BIT8=00,01,10
	AND	#(BIT1+BIT0),R0			;

	CMP/EQ	#BIT0,R0			;最小荷重(ﾏｲﾅｽ最大?)
	BT	KAJYU_OVERLOADCK_100		;
	CMP/EQ	#BIT1,R0			;幅?
	BT	KAJYU_OVERLOADCK_200		;

;	------- 最大荷重(COP1Z) --------------------------
;	------- 最小荷重(ﾏｲﾅｽ最大?),幅信号はｸﾘｱ-----------
	MOV.L	#_KJYU_CMP_SEQMINS,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;

	MOV.L	#_KJYU_CMP_SEQHABA,R5
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;
	M_BRA	KAJYU_OVERLOADCK_EXT		;


;	------- 最小荷重(ﾏｲﾅｽ最大?)-----
KAJYU_OVERLOADCK_100:


	XOR	R8,R8				;SEQ
	MOV.W	#BIT0,R7			;
	MOV.L	#_BTOA_LFT_MIN,R5		;4B符号付
	MOV.L	#_SVP_OVERE1_A27,R6		;2B符号無し  荷重計　オーバーロード１ 　（最小値）
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;

	MOV.W	#BIT1,R7			;
	MOV.L	#_BTOA_RIH_MIN,R5		;4B符号付
	MOV.L	#_SVP_OVERE2_A27,R6		;2B符号無し  荷重計　オーバーロード２  　（最小値）
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;

	MOV.W	#BIT2,R7			;
	MOV.L	#_BTOA_TTL_MIN,R5		;4B符号付
	MOV.L	#_SVP_OVERE3_A27,R6		;2B符号無し  荷重計　オーバーロード３  　（最小値）
	FAR_JSR	#_KAJYU_OVER_NEGCMP,R0		;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;比較信号ｾｯﾄ
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;幅信号はｸﾘｱ
	M_BRA	KAJYU_OVERLOADCK_EXT		;

;	------- 幅信号-----------
KAJYU_OVERLOADCK_200:

	XOR	R8,R8				;SEQ
	MOV.W	#BIT0,R7			;
	MOV.L	#_BTOA_LFT_HAB,R5		;4B符号付
	MOV.L	#_SVP_OVERE1_A28,R6		;2B符号無し  荷重計　オーバーロード１ 　（幅）
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;

	MOV.W	#BIT1,R7			;
	MOV.L	#_BTOA_RIH_HAB,R5		;4B符号付
	MOV.L	#_SVP_OVERE2_A28,R6		;2B符号無し  荷重計　オーバーロード２  　（幅）
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;

	MOV.W	#BIT2,R7			;
	MOV.L	#_BTOA_TTL_HAB,R5		;4B符号付
	MOV.L	#_SVP_OVERE3_A28,R6		;2B符号無し  荷重計　オーバーロード３  　（幅）
	FAR_JSR	#_KAJYU_OVER_CMP,R0		;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;比較信号ｾｯﾄ
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;ﾏｲﾅｽ信号はｸﾘｱ
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT2|BIT1|BIT0),R0	;
	MOV.W	R0,@R5				;
KAJYU_OVERLOADCK_EXT:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	符号付比較で大きければ正常	***
;	***					***
;	*******************************************
;
;
_KAJYU_OVER_NEGCMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;符号無し
	NEG	R3,R3			;

	CMP/GE	R3,R2			;
	BT KAJYU_OVER_NEGCP_END		;-300 =< -200 THEN JUMP

	OR	R7,R8			;ABNOMAL ｼｰｹﾝｽﾋﾞｯﾄON

KAJYU_OVER_NEGCP_END:


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	符号付比較で大きければ異常	***
;	***					***
;	*******************************************
_KAJYU_OVER_CMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;符号無し

	CMP/GE	R3,R2			;
	BF	KAJYU_OVER_CP_END	;200 < 300? NO! THEN JUMP
	OR	R7,R8			;ｼｰｹﾝｽﾋﾞｯﾄON
KAJYU_OVER_CP_END:

	SUB_END
	M_RTS




;	*******************************************
;	***					***
;	***	ﾛｱﾘﾐｯﾄ				***
;	***					***
;	*******************************************
_KAJYU_LOWLIMIT_CHK
	SUB_START


;;;;	MOV.L	#_KJYU_CMP_SELSW2,R1		;
	MOV.L	#_CB_SEQ_SW_SEL058,R1		;00
	MOV.W	@R1,R0				;
	SHLR8	R0				;BIT11,BIT10=00,01,10
	AND	#(BIT3+BIT2),R0			;

	CMP/EQ	#BIT2,R0			;最小荷重(ﾏｲﾅｽ最大?)
	BT	KAJYU_LOWLIMITCK_100		;
	
	CMP/EQ	#BIT3,R0			;幅?
	BT	KAJYU_LOWLIMITCK_200		;

;	------- 最大荷重(COP1Z) --------------------------
;	------- 最小荷重(ﾏｲﾅｽ最大?),幅信号はｸﾘｱ-----------
	MOV.L	#_KJYU_CMP_SEQMINS,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
	MOV.L	#_KJYU_CMP_SEQHABA,R5
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
	M_BRA	KAJYU_LOWLIMITCK_EXT		;


;	------- 最小荷重(ﾏｲﾅｽ最大?)-----
KAJYU_LOWLIMITCK_100:


	XOR	R8,R8				;SEQ
	MOV.W	#BIT3,R7			;
	MOV.L	#_BTOA_LFT_MIN,R5		;4B符号付
	MOV.L	#_SVP_ROALM1_A27,R6		;2B符号無し  荷重計　オーバーロード１ 　（最小値）
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;

	MOV.W	#BIT4,R7			;
	MOV.L	#_BTOA_RIH_MIN,R5		;4B符号付
	MOV.L	#_SVP_ROALM2_A27,R6		;2B符号無し  荷重計　オーバーロード２  　（最小値）
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;

	MOV.W	#BIT5,R7			;
	MOV.L	#_BTOA_TTL_MIN,R5		;4B符号付
	MOV.L	#_SVP_ROALM3_A27,R6		;2B符号無し  荷重計　オーバーロード３  　（最小値）
	FAR_JSR	#_KAJYU_LOWLMT_NEGCMP,R0		;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;比較信号ｾｯﾄ
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;幅信号はｸﾘｱ
	M_BRA	KAJYU_LOWLIMITCK_EXT		;

;	------- 幅信号-----------
KAJYU_LOWLIMITCK_200:

	XOR	R8,R8				;SEQ
	MOV.W	#BIT3,R7			;
	MOV.L	#_BTOA_LFT_HAB,R5		;4B符号付
	MOV.L	#_SVP_ROALM1_A28,R6		;2B符号無し  荷重計　オーバーロード１ 　（幅）
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;

	MOV.W	#BIT4,R7			;
	MOV.L	#_BTOA_RIH_HAB,R5		;4B符号付
	MOV.L	#_SVP_ROALM2_A28,R6		;2B符号無し  荷重計　オーバーロード２  　（幅）
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;

	MOV.W	#BIT5,R7			;
	MOV.L	#_BTOA_TTL_HAB,R5		;4B符号付
	MOV.L	#_SVP_ROALM3_A28,R6		;2B符号無し  荷重計　オーバーロード３  　（幅）
	FAR_JSR	#_KAJYU_LOWLMT_CMP,R0		;


	MOV.L	#_KJYU_CMP_SEQHABA,R5		;比較信号ｾｯﾄ
	MOV.W	@R5,R0				;
	OR	R8,R0
	MOV.W	R0,@R5				;


	MOV.L	#_KJYU_CMP_SEQMINS,R5		;ﾏｲﾅｽ信号はｸﾘｱ
	MOV.W	@R5,R0				;
	AND	#LOW ~(BIT5|BIT4|BIT3),R0	;
	MOV.W	R0,@R5				;
KAJYU_LOWLIMITCK_EXT:

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	符号付比較で小さければ正常	***
;	***					***
;	*******************************************
;
;
_KAJYU_LOWLMT_NEGCMP:
	SUB_START
	MOV.L	@R5,R2			;PV
	MOV.W	@R6,R3			;SV
	EXTU.W	R3,R3			;符号無し
	NEG	R3,R3			;

	CMP/GT	R3,R2			;
	BF KAJYU_LOWLMT_NEGCP_END	;-300(R3) < -200(R2) NO! R3(-300) >=R2(-400)

	OR	R7,R8			;ABNOMAL ｼｰｹﾝｽﾋﾞｯﾄON

KAJYU_LOWLMT_NEGCP_END:


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	符号付比較で小さければ異常	***
;	***					***
;	*******************************************
_KAJYU_LOWLMT_CMP:
	SUB_START
	MOV.L	@R5,R2			;
	MOV.W	@R6,R3			;
	EXTU.W	R3,R3			;符号無し

	CMP/GE	R3,R2			;
	BT	KAJYU_LOWLMT_CP_END	;200(R3) <= 300 (R2)? THEN NOMAL JUMP
	OR	R7,R8			;ｼｰｹﾝｽﾋﾞｯﾄON
KAJYU_LOWLMT_CP_END:

	SUB_END
	M_RTS


;	*******************************************
;	****		荷重ﾃﾞﾊﾞｯｸ用		***
;	*******************************************
;	CPUB側デ10倍シテイル
;	0     ~ 130.0    =0KN
;	130.0 ~ 150.0    = (角度-130.0)*10(cpua)*10(cpub)= 0~2000kn
;	150.0 ~          =0kn

	.IMPORT	_PVPAB_DBG_KYUIN1	;()
	.IMPORT	_PVPAB_DBG_KYUIN2	;()
	.IMPORT	_PVPAB_DBG_KYUIN3	;()
	.IMPORT	_TRD_SMP_PV_PGDG	;

_KAJYUU_DEBUG_ANACHG
	SUB_START

	MOV.L	#_TRD_SMP_PV_PGDG,R4		;
	MOV.W	@R4,R2				;0~360.0

;;;;	FAR_JSR	#_KAJYUU_DEBUG_ANACG1,R0
	FAR_JSR	#_KAJYUU_DEBUG_ANACG2,R0


;	R2を10倍する(CPUBが10倍しているので実質100倍)

	MOV.W	#D'10,R3			;180(cpua*10)->1800->(cpub*10)=18000
	DMULS.L	R3,R2				;
	STS	MACL,R2				;

	MOV	R2,R3
	ADD	#D'10,R3			;
	MOV	R2,R4				;
	ADD	#D'20,R4			;

	MOV.L	#_PVPAB_DBG_KYUIN1,R1		;
	SWAP.B	R2,R2				;ｲﾝﾃﾙ(左)
	MOV.W	R2,@R1				;

	MOV.L	#_PVPAB_DBG_KYUIN2,R1		;
	SWAP.B	R3,R3				;ｲﾝﾃﾙ(合計)
	MOV.W	R3,@R1				;

	MOV.L	#_PVPAB_DBG_KYUIN3,R1		;
	SWAP.B	R4,R4				;ｲﾝﾃﾙ(右)
	MOV.W	R4,@R1				;

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***　ある区間だけ荷重増加	***
;	***　ある区間以外は0KN		***
;	***				***
;	***********************************
_KAJYUU_DEBUG_ANACG1
	SUB_START

	MOV.W	#D'1300,R4			;130.0度
	MOV.W	#D'1500,R1			;150.0度

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG1_050		;
	XOR	R2,R2				;150.0~360.0:THEN 0
	M_BRA	KAJYUU_DBG_ANACG1_100		;


KAJYUU_DBG_ANACG1_050				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG1_100		;JUMP(130.0~150.0)
	XOR	R2,R2				;0~130.0度
KAJYUU_DBG_ANACG1_100				;

	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	ふりこ用2区間		***
;	***				***
;	***********************************
_KAJYUU_DEBUG_ANACG2
	SUB_START

	MOV.W	#D'1300,R4			;130.0度
	MOV.W	#D'1500,R1			;150.0度

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG2_050		;
	M_BRA	KAJYUU_DBG_ANACG2_100		;150.0~360.0:THEN 0

;	0~150.0
KAJYUU_DBG_ANACG2_050				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG2_090		;JUMP(130.0~150.0)
	XOR	R2,R2				;0~130.0度
KAJYUU_DBG_ANACG2_090				;
	M_BRA	KAJYUU_DBG_ANACG2_END		;

;	----------- 復路用-------------
KAJYUU_DBG_ANACG2_100				;
	MOV.W	#D'2300,R1			;3600-130.0度
	MOV.W	#D'2100,R4			;3600-150.0度

	CMP/HS	R1,R2				;
	BF	KAJYUU_DBG_ANACG2_150		;
	XOR	R2,R2				;2300~3600
	M_BRA	KAJYUU_DBG_ANACG2_END		;

;	0~150.0
KAJYUU_DBG_ANACG2_150				;
	SUB	R4,R2				;
	CMP/PZ	R2				;
	BT	KAJYUU_DBG_ANACG2_190		;JUMP(130.0~150.0)
	XOR	R2,R2				;180~210.0度
	M_BRA	KAJYUU_DBG_ANACG2_END		;
KAJYUU_DBG_ANACG2_190				;
	MOV	R2,R4				;
	MOV.W	#(D'2300-D'2100)+1,R2		;201-**
	SUB	R4,R2				;
KAJYUU_DBG_ANACG2_END				;


	SUB_END
	M_RTS


;;;_KAJYUU_SHOT_ADR_SET:
;;;	SUB_START
;;;	MOV.L	#_SET1_KAJAREA_SEL,R1	;//ﾄﾚﾝﾄﾞ荷重表示選択0:(最大),1:(最小),2(幅)
;;;	MOV.W	@R1,R0			;
;;;
;;;	MOV.L	#_BTOA_LFT_TRDHAB,R1
;;;	MOV.L	#_BTOA_RIH_TRDHAB,R2
;;;	MOV.L	#_BTOA_TTL_TRDHAB,R4
;;;	CMP/EQ	#2,R0			;
;;;	BT KAJYUU_SHOTADRSET_100
;;;
;;;
;;;	MOV.L	#_BTOA_LFT_TRDMIN,R1
;;;	MOV.L	#_BTOA_RIH_TRDMIN,R2
;;;	MOV.L	#_BTOA_TTL_TRDMIN,R4
;;;
;;;	CMP/EQ	#1,R0			;
;;;	BT KAJYUU_SHOTADRSET_100
;;;
;;;	MOV.L	#_BTOA_LFT_TRDMAX,R1
;;;	MOV.L	#_BTOA_RIH_TRDMAX,R2
;;;	MOV.L	#_BTOA_TTL_TRDMAX,R4
;;;
;;;KAJYUU_SHOTADRSET_100:
;;;
;;;	MOV.L	#_SHOT_ADR_LFT,R0		;ADR
;;;	MOV.L	R1,@R0
;;;	MOV.L	#_SHOT_ADR_RIH,R0		;ADR
;;;	MOV.L	R2,@R0
;;;	MOV.L	#_SHOT_ADR_TTL,R0		;ADR
;;;	MOV.L	R4,@R0
;;;
;;;	SUB_END
;;;	M_RTS
