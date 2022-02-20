;	*******************************************
;	***										***
;	***		クラッチ信号のバックアップ		***
;	***										***
;	*******************************************
;	---2011-09-14----- ｸﾗｯﾁ信号記憶[FERAM]----
	.import		_FRAM_CBSTS_SQCOD1	;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	.import		_FRAM_CBSTS_SQDAT1	;*data1
	.import		_FRAM_CBSTS_SQDAT1_SUM	;data1の反転
	.import		_FRAM_CBSTS_SQDAT2	;*data2
	.import		_FRAM_CBSTS_SQDAT2_SUM	;data2の反転
	.import		_FRAM_CBSTS_SQDAT3	;*data3
	.import		_FRAM_CBSTS_SQDAT3_SUM	;data3

;	---2011-09-14 [16ﾊﾞｲﾄ] [DPRAM] -----
	.import		_CPUATOB_STS_SAVECMD	;5AA5 or A55A
	.import		_CPUATOB_STS_SAVEDAT1	;BAKUP DATA1
	.import		_CPUATOB_STS_SAVEDAT2	;BAKUP DATA2
	.import		_CPUATOB_STS_SAVEDAT3	;BAKUP DATA3

	.import		_CPUBTOA_STS_LOADSTS	;5AA5 or A55A
	.import		_CPUBTOA_STS_LOADDAT1	;BAKUP DATA1
	.import		_CPUBTOA_STS_LOADDAT2	;BAKUP DATA2 
	.import		_CPUBTOA_STS_LOADDAT3	;BAKUP DATA3 3DFE,3DFF もうここには隙間なし

;	---------------------------------------
;//	*******************************************
;//	***										***
;//	*** 		CPUB専用ﾊﾞｯｸｱｯﾌﾟ			***
;//	***			2011-09-14					***
;//	***										***
;//	*******************************************
__CBSTSBAKUP_COD	.EQU	H'5AA5
	.ALIGN	4		;
_CBB_STS_BKUP_SAVE:
	SUB_START

	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF CBB_STS_BKUPSV_EXT		;

	MOV.L	#_CPUATOB_STS_SAVECMD,R5	;
	MOV.W	@R5,R0				;DPRAM LOAD
	MOV.L	#_CBSTS_SAVE_CMDWK,R6		;
	MOV.W	@R6,R2				;WORKRAM LOAD
	CMP/EQ	R0,R2				;
	BT	CBB_STS_BKUPSV_EXT		;ｺﾏﾝﾄﾞはない

	MOV.W	#__CBSTSBAKUP_COD,R4			;
	CMP/EQ	R4,R0				;
	BT	CBB_STS_BKUPSV_100		;
	NOT	R4,R4
	CMP/EQ	R4,R0				;
	BF	CBB_STS_BKUPSV_EXT		;
CBB_STS_BKUPSV_100:				;
	MOV.W	R0,@R6				;SAVE CMD


	MOV.L	#_CPUATOB_STS_SAVEDAT1,R5	;DPRAM-data1
	MOV.L	#_FRAM_CBSTS_SQDAT1,R6		;FERAM-data1

;----------[1個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
;----------[2個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
;----------[3個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;

	MOV.L	#_FRAM_CBSTS_SQCOD1,R1		;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	MOV.W	R0,@R1				;有効なデータがある

CBB_STS_BKUPSV_EXT:
	SUB_END
	M_RTS


;//	*******************************************
;//	***										***
;//	*** 	CPUB専用ﾊﾞｯｸｱｯﾌﾟ戻し			***
;//	***	2011-09-14							***
;//	***										***
;//	*******************************************
_CBB_STS_BKUP_LOAD:
	SUB_START
	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON CBB_STS_BKUP_LD_EXT		;

	MOV.L	#_FRAM_CBSTS_SQCOD1,R1		;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	MOV.W	@R1,R0				;有効なデータがある
	MOV.W	#__CBSTSBAKUP_COD,R4			;
	CMP/EQ	R4,R0				;
	BT	CBB_STS_BKUP_LD_100		;
	NOT	R4,R4				;
	CMP/EQ	R4,R0				;
	BF	CBB_STS_BKUP_LD_400		;
CBB_STS_BKUP_LD_100:
	MOV.L	#_FRAM_CBSTS_SQDAT1,R5		;FERAM-data1
	MOV.L	#_CPUBTOA_STS_LOADDAT1,R6	;DPRAM-data1
	MOV.W	#D'3,R3				;


CBB_STS_BKUP_LD_200LOP:
	TST	R3,R3				;
	TST_BIT_OF CBB_STS_BKUP_LD_500		;
	MOV.W	@R5+,R0				;NOMAL DATA
	MOV.W	@R5+,R1				;NOT DATA
	NOT	R1,R1				;
	CMP/EQ	R1,R0				;
	BF	CBB_STS_BKUP_LD_400		;ERR
	MOV.W	R0,@R6				;
	ADD	#2,R6				;
	ADD	#-1,R3				;
	M_BRA	CBB_STS_BKUP_LD_200LOP		;

;----異常あり-----------
CBB_STS_BKUP_LD_400:
	XOR	R0,R0
	MOV.L	#_CPUBTOA_STS_LOADDAT1,R6	;BAKUP DATA1
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	R0,@R6
CBB_STS_BKUP_LD_500:
	MOV.W	#__CBSTSBAKUP_COD,R4
	MOV.L	#_CPUBTOA_STS_LOADSTS,R1	;
	MOV.W	R4,@R1				;

	MOV.W	#BIT0,R0		;
	MOV.L	#_CBSTS_LOAD_FLG,R1	;
	MOV.W	R0,@R1			;

CBB_STS_BKUP_LD_EXT:
	SUB_END
	M_RTS


;	*******************************************
;	***										***
;	***										***
;	***										***
;	***		[2018-11-11]					***
;	***		CPUD/B共通-VERTION				***
;	***		下限位置ﾊﾞｯｸｱｯﾌﾟ				***
;	***										***
;	***										***
;	***										***
;	*******************************************
_CPUD_ON_CPUB_DP		.DEFINE		"_CMPILE_YES"		;

;	------------------------------------------------------------------------------------------
;	-----2018-11-11<ﾊﾟﾜｰﾀﾞｳﾝ監視も行い,ﾊﾟﾜｰﾀﾞｳﾝ時はﾊﾞｯｸｱｯﾌﾟしない> 下限位置関連(8word準備) ---
;	------------------------------------------------------------------------------------------
	.IMPORT		_FRAM_CBPV1_COD1		;USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	.IMPORT		_FRAM_CBPV1_DAT01		;data1
	.IMPORT		_FRAM_CBPV1_DAT01_SUM	;data1の反転
	.IMPORT		_FRAM_CBPV1_DAT02		;data2
	.IMPORT		_FRAM_CBPV1_DAT02_SUM	;data2の反転
	.IMPORT		_FRAM_CBPV1_DAT03		;data3
	.IMPORT		_FRAM_CBPV1_DAT03_SUM	;data3の反転
	.IMPORT		_FRAM_CBPV1_DAT04		;data4
	.IMPORT		_FRAM_CBPV1_DAT04_SUM	;data4の反転
	.IMPORT		_FRAM_CBPV1_DAT05		;data5
	.IMPORT		_FRAM_CBPV1_DAT05_SUM	;data5の反転
	.IMPORT		_FRAM_CBPV1_DAT06		;data6
	.IMPORT		_FRAM_CBPV1_DAT06_SUM	;data6の反転
	.IMPORT		_FRAM_CBPV1_DAT07		;data7
	.IMPORT		_FRAM_CBPV1_DAT07_SUM	;data7の反転
	.IMPORT		_FRAM_CBPV1_DAT08		;data8
	.IMPORT		_FRAM_CBPV1_DAT08_SUM	;data8の反転

	.EXPORT		_Api_DAIHAITO_REC_PON_INIT
	.EXPORT		_Api_DAIHAITO_REC_BAK
	.EXPORT		_Api_DAIHAITO_REC_CLR
	.EXPORT		_Api_DAIHAITO_REC_SET

;	*******************************************
;	***										***
;	***			電源投入１回				***
;	***			2018-11-11					***
;	***										***
;	*******************************************
_Api_DAIHAITO_REC_PON_INIT
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***										***
;	***			データ戻す					***
;	***			2018-11-11					***
;	***										***
;	*******************************************
_Api_DAIHAITO_REC_BAK
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***										***
;	***			データCLR					***
;	***			2018-11-11					***
;	***										***
;	*******************************************
_Api_DAIHAITO_REC_CLR
	SUB_START
	SUB_END
	M_RTS

;	*******************************************
;	***										***
;	***			データ保存					***
;	***			2018-11-11					***
;	***										***
;	*******************************************
_Api_DAIHAITO_REC_SET
	SUB_START
	SUB_END
	M_RTS


;	***************************************************
;	***												***
;	***												***
;	***												***
;	***												***
;	***												***
;	***		[2018-11-11]							***
;	***		CPUD-VERTION							***
;	***		異常履歴[2018-11-11 VER]				***
;	***												***
;	***		記録と表示は完全に別次元				***
;	***												***
;	***												***
;	***												***
;	***												***
;	***************************************************
;	***************************************************
;	***												***
;	***												***
;	***												***
;	***												***
;	***						記録					***
;	***												***
;	***												***
;	***												***
;	***												***
;	***												***
;	***************************************************

;	--------- [2018-11-11全面変更] --------------
;	--------- FERAM -------
	.IMPORT		_FRAM_CB_BAKUP_INF_TOP		;
	.IMPORT		_FRAM_CB_USELFUL_COD1		;5AA51234なら有効

	.IMPORT		_FRAM_CB_STSA_POINT			;最新値ﾎﾟｲﾝﾀの指示位置
	.IMPORT		_FRAM_CB_STSA_CNT			;実行回数
	.IMPORT		_FRAM_CB_STSB_POINT			;最新値ﾎﾟｲﾝﾀの指示位置
	.IMPORT		_FRAM_CB_STSB_CNT			;実行回数
	
	.IMPORT		_FRAM_POWER_ON_CNT			;電源投入回数
	.IMPORT		_FRAM_ERR_INFO_CPUA_TOP		;(128byte*8頁)
	.IMPORT		_FRAM_ERR_INFO_CPUB_TOP		;(128byte*8頁)
	.IMPORT		_FRAM_CB_BAKUP_INF_END				;B4007CFF以下であれば良い

;	------ DPRAM----------
	.IMPORT		_CB_STS_SAVE_FLG	;
	.IMPORT		_PV_CB_STS_DAT_TOP	;

;	------ DPRAM----------
	.IMPORT		_SVP_MONALM_S01	
	.IMPORT		_SVP_MONALM_S02		
	.IMPORT		_SVP_MONALM_S03		
	.IMPORT		_SVP_MONALM_S04		

;	------- WORK --------
	.IMPORT		_OLD_SVP_MONALM_S04;		//

;	------ EXPORT----------
	.EXPORT	_Api_ERR_HIS_REC_PON_INIT	;
	.EXPORT	_Api_ERR_HIS_REC_CLR		
	.EXPORT	_Api_ERR_HIS_REC_SET


;	*******************************************
;	***										***
;	***			電源投入１回				***
;	***			2018-11-11					***
;	***			画面CPUD/B共通				***
;	***										***
;	*******************************************
;	SSA_K.SRC _ASM_DMK1_DATA_INIT
;
_Api_ERR_HIS_REC_PON_INIT
	SUB_START
	MOV.L	#_FRAM_CB_USELFUL_COD1,R1		;5AA51234なら有効
	MOV.L	@R1,R0							;
	MOV.L	#_CB_BAK_SUM_COD1,R2				;
	CMP/EQ 	R2,R0							;
	BT		ERR_HIS_REC_PONINIT_100			;

	FAR_JSR	#_Api_ERR_HIS_REC_CLR,R0	;CLR

ERR_HIS_REC_PONINIT_100					;

	MOV.L	#_FRAM_POWER_ON_CNT,R1			;電源投入回数
	MOV.W	@R1,R0							;
	ADD		#1,R0							;
	MOV.W	R0,@R1							;

;	----------DPRAM------------------------
	XOR		R0,R0										;
	MOV.L	#(_CB_STS_SAVE_FLG-_dpram_top)+_dpram_top,R5	;CPUA-DPRAM
	MOV.W	R0,@R5											;

 .AIF _CPUD_ON_CPUB_DP EQ _CMPILE_YES
	XOR		R0,R0										;
	MOV.L	#(_CB_STS_SAVE_FLG-_dpram_top)+_dpramB_top,R5	;CPUB-DPRAM
	MOV.W	R0,@R5											;
 .AELSE
 .AENDI

	SUB_END
	M_RTS

;	*******************************************
;	***										***
;	***			データ初期化/CLR			***
;	***			2018-11-11					***
;	***			画面CPUD/B共通				***
;	***										***
;	*******************************************
_ERR_HIS_CLRCMD_CHECK:
	SUB_START
	MOV.L	#_SVP_MONALM_S04,R5	;NEW
	MOV.W	@R5,R0				;
	MOV.L	#_OLD_SVP_MONALM_S04,R6
	MOV.W	@R6,R1				;
	MOV.W	R0,@R6				

	CMP/EQ	R0,R1				;
	BT	ERR_HIS_CLRCMD_CHKEXT	;
	MOV.W	#D'100,R4			;
	CMP/EQ	R4,R0				;
	BF	ERR_HIS_CLRCMD_CHKEXT	;
	MOV.W	#D'99,R4			;
	CMP/EQ	R4,R1				;
	BF	ERR_HIS_CLRCMD_CHKEXT	;99->100に変更


	FAR_JSR	#_Api_ERR_HIS_REC_CLR,R0

ERR_HIS_CLRCMD_CHKEXT:

	SUB_END
	M_RTS

_Api_ERR_HIS_REC_CLR
	SUB_START

	MOV.L	#_FRAM_CB_BAKUP_INF_TOP,R5
	MOV.L	#(_FRAM_CB_BAKUP_INF_END-_FRAM_CB_BAKUP_INF_TOP)/2,R3	;LOOP
	XOR		R1,R1

ERR_HIS_RECCLR_LOP
	TST		R3,R3
	TST_BIT_OF ERR_HIS_RECCLR_END
	MOV.W	R1,@R5
	ADD		#2,R5
	ADD		#-1,R3
	M_BRA	ERR_HIS_RECCLR_LOP

ERR_HIS_RECCLR_END
	MOV.L	#_FRAM_CB_USELFUL_COD1,R1		;5AA51234なら有効
	MOV.L	#_CB_BAK_SUM_COD1,R2					;
	MOV.L	R2,@R1							;4BYTE ALIGN

	SUB_END
	M_RTS

;	***************************************************
;	***												***
;	***		データ保存(A.B判定)						***
;	***		2018-11-11								***
;	***		画面CPUDのみ							***
;	***												***
;	***************************************************
;	ﾊﾟﾜｰﾀﾞｳﾝ判定後の処理で呼ばれる.割込
;;	.IMPORT	_dpram_top
;;	.IMPORT	_dpramB_top
;
;	SSA_K.SRC _ASM_K1_CTRL_MAIN
;

_ERR_HIS_REC_MAIN
	SUB_START

;	------------- CLR CMD CHECK----------
	FAR_JSR	#_ERR_HIS_CLRCMD_CHECK,R0

;	----------DPRAM CPUA------------------------
	MOV.L	#(_CB_STS_SAVE_FLG-_dpram_top)+_dpram_top,R5	;CPUA-DPRAM
	MOV.W	@R5,R0											;
	MOV.W	#_CB_BAKUP_CMD2,R4								;BAKUP-CMD-CODE(BLK)1234
	CMP/EQ	R4,R0											;
	BF		ERR_HIS_REC_MN100								;

	PUSH_REG1 R5
	MOV.W	#1,R0							;CPUA
	FAR_JSR	#_Api_ERR_HIS_REC_SET,R1		;SAVE
	POP_REG1 R5

	XOR		R0,R0											;
	MOV.W	R0,@R5											;CMD-CLR

ERR_HIS_REC_MN100:

;	------------CPUD時CPUB------------------------
 .AIF _CPUD_ON_CPUB_DP EQ _CMPILE_YES
	MOV.L	#(_CB_STS_SAVE_FLG-_dpram_top)+_dpramB_top,R5	;CPUB-DPRAM
	MOV.W	@R5,R0											;
 .AELSE
;	------------CPUB時CPUB(WORK-RAM)------------------------
 .AENDI

	MOV.W	#_CB_BAKUP_CMD2,R4								;BAKUP-CMD-CODE
	CMP/EQ	R4,R0											;
	BF		ERR_HIS_REC_MN200								;

	PUSH_REG1 R5
	MOV.W	#2,R0							;CPUA
	FAR_JSR	#_Api_ERR_HIS_REC_SET,R1		;SAVE
	POP_REG1 R5

	XOR		R0,R0											;
	MOV.W	R0,@R5											;CMD-CLR

ERR_HIS_REC_MN200:

	
	SUB_END
	M_RTS


;	***************************************************
;	***												***
;	***		データ保存								***
;	***		2018-11-11								***
;	***		画面CPUDのみ							***
;	***		画面CPUBの場合参照がDPRAMではないかも	***
;	***												***
;	***************************************************
;	input R0=2(CPUB)
;	--------- CPUA OR CPUBのどちらか先に検知した方のデータのみSAVE-------------
;	input R0(1(A),2(B))
_Api_ERR_HIS_REC_SET
	SUB_START
	
	CMP/EQ	#2,R0							;
	BT	ERR_HIS_RECSET050

	MOV.L	#(_PV_CB_STS_DAT_TOP-_dpram_top)+_dpram_top,R11			;SRC1
	MOV.L	#_FRAM_ERR_INFO_CPUA_TOP,R13							;DST
	MOV.L	#_FRAM_CB_STSA_CNT,R8									;実行回数
	MOV.L	#_FRAM_CB_STSA_POINT,R9									;
	M_BRA	ERR_HIS_RECSET100

ERR_HIS_RECSET050
;	----------CPUD時CPUB------------------------
 .AIF _CPUD_ON_CPUB_DP EQ _CMPILE_YES
	MOV.L	#(_PV_CB_STS_DAT_TOP-_dpram_top)+_dpramB_top,R11		;SRC1
	MOV.L	#_FRAM_ERR_INFO_CPUB_TOP,R13							;DST
	MOV.L	#_FRAM_CB_STSB_CNT,R8									;実行回数
	MOV.L	#_FRAM_CB_STSB_POINT,R9									;
 .AELSE
;	----------CPUB時CPUB(WORK-RAM)------------------------
 .AENDI
ERR_HIS_RECSET100:


;	------R8(実行回数),R9(POINT),R11(SRC1 64BYTE),R12(SRC2 64BYTE),R13(SAVE 128)----------------
	MOV.W	@R8,R0							;記録回数
	ADD		#1,R0							;
	MOV.W	R0,@R8							;

;	-------- 記録--------------
	MOV.W	@R9,R0							;NUM
	AND		#(_CB_ERR_INFO_PSIZE-1),R0		;07(暴走防止)
	MOV.W	#_CB_ERR_INFO_MEM,R1			;128BYTE
	MULU.W	R0,R1							;
	STS.L	MACL,R4							;
	ADD		R4,R13							;DST+POINT*128
	ADD		#1,R0							;
	AND		#(_CB_ERR_INFO_PSIZE-1),R0		;07
	MOV.W	R0,@R9							;NEXT SET

;	--------- 128BYTE  R11からは64BYTE(R11 SRC,R13 DST,R1)-----------
	MOV.W	#(D'128/4),R1					;128BYTEはR11(_PV_CB_STS_DAT_TOP)からとる
	BLOCK_MOV1	L,4,R11,R13,R0,R1			;32-LONG



	SUB_END
	M_RTS





;	***************************************************
;	***												***
;	***												***
;	***												***
;	***												***
;	***						表示					***
;	***												***
;	***												***
;	***			CPUA,CPUB,1,15,1,15頁OK				***
;	***			PON,CNT,POINT,OK					***
;	***												***
;	***************************************************
	.IMPORT		_PVP_MONALM1_TOP	;=_PVP_MONALM_C01	;64 WORD TOP
	.IMPORT		_PVP_MONALM_P01		
	.IMPORT		_PVP_MONALM_P02		
	.IMPORT		_PVP_MONALM_P03		
	.IMPORT		_PVP_MONALM_P04		

_ERR_HIS_DISP_MAIN
	SUB_START

	MEM_MOV_TO_MEM	SRC_ADR=_FRAM_POWER_ON_CNT,L1=W,DST_ADR=_PVP_MONALM_P01,L2=W,WKREG1=R1,WKREG2=R2,WKREG3=R3

	MOV.L	#_SVP_MONALM_S01,R1
	MOV.W	@R1,R0					;
	TST		R0,R0					;
	TST_BIT_ON ERR_HIS_DISP_MN_EXT	;ｻﾝﾌﾟﾘﾝｸﾞ中,履歴表示不可

	MOV.L	#_SVP_MONALM_S04,R1
	MOV.W	@R1,R0					;
	TST		R0,R0					;
	TST_BIT_OF ERR_HIS_DISP_MN_EXT	;ｻﾝﾌﾟﾘﾝｸﾞ中,履歴表示不可

	CMP/EQ	#1,R0					;異常履歴(CPUD/CPUB)+CPUA
	BT	ERR_HIS_DISP_MN_100			;
	CMP/EQ	#2,R0					;異常履歴(CPUD/CPUB)+CPUA
	BT	ERR_HIS_DISP_MN_200			;
	M_BRA	ERR_HIS_DISP_MN_EXT		

;	1:CPUA記録 2:CPUB記録
ERR_HIS_DISP_MN_100

	MOV.L	#_FRAM_ERR_INFO_CPUA_TOP,R11	;バファ
	MOV.L	#_FRAM_CB_STSA_POINT,R12		;最新値ﾎﾟｲﾝﾀの指示位置
	MOV.L	#_FRAM_CB_STSA_CNT,R13			;実行回数
	M_BRA	ERR_HIS_DISP_MN_300


ERR_HIS_DISP_MN_200
	MOV.L	#_FRAM_ERR_INFO_CPUB_TOP,R11	;バファ
	MOV.L	#_FRAM_CB_STSB_POINT,R12		;最新値ﾎﾟｲﾝﾀの指示位置
	MOV.L	#_FRAM_CB_STSB_CNT,R13			;実行回数

ERR_HIS_DISP_MN_300

	MOV.L	#_SVP_MONALM_S02,R1				;
	MOV.W	@R1,R0							;
	AND		#(_CB_ERR_INFO_PSIZE*2-1),R0	;8*2-1=15(暴走防止)
	MOV.L	#_PVP_MONALM_P02,R1				;
	MOV.W	R0,@R1							;

	MOV.W	#D'64,R1							;64固定(ﾃﾞｰﾀは128BYTE)
	MULU.W	R0,R1							;
	STS.L	MACL,R4							;
	ADD		R4,R11							;DST+PAGE*64

;	--------- 128BYTEだが表示は64固定  R11からは64BYTE(R11 SRC,R13 DST,R1)-----------
	MOV.L	#_PVP_MONALM1_TOP,R6
	MOV.W	#(64/4),R1					;64BYTEはR11(_PV_CB_STS_DAT_TOP)からとる
	BLOCK_MOV1	L,4,R11,R6,R0,R1			;32-LONG


	MOV.W	@R12,R0
	MOV.L	#_PVP_MONALM_P03,R1		;ﾎﾟｲﾝﾄ 
	MOV.W	R0,@R1
	
	MOV.W	@R13,R0
	MOV.L	#_PVP_MONALM_P04,R1		;ｶｳﾝﾀ
	MOV.W	R0,@R1


ERR_HIS_DISP_MN_EXT

	SUB_END
	M_RTS





















