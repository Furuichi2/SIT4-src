;	*******************************************
;	***	DPRAM HANDSYEIKU OUT SH4-->SH2	***
;	*******************************************
_CPU_SV_HAND_ACK:
	SUB_START
	MOV.L	#_CPU_SV_HAND_OUT,R1	;
	MOV.L	@R1,R0			;
	MOV.L	#_HS_SVCHG_A_TO_B,R1	;
	MOV.L	R0,@R1			;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	ﾘﾆｱｾﾝｻLOAD		***
;	***	(CPUAだけ)		***
;	***********************************
	.import	_PV1_SCRW_POS	;

_RENEA_CENCER_LOAD:
	SUB_START

;	-------- 2009-03-11
	MOV.L	#_WPAR_MCNRNA_SEL,R4		;//1:機械でﾘﾆｱｽｹｰﾙを使用しない構造･･原点復帰
	MOV.W	@R4,R0				;
	CMP/EQ	#1,R0				;
	BF	RENEA_CENCER_LD020		;
	MOV.L	#_RNA_POS_OFFSET1,R4		;_SVB_RNAORG_PLS1->_RNA_POS_OFFSET1->_PVP_RNAORG_PLS1
	MOV.L	@R4,R2				;
	M_BRA	RENEA_CENCER_LD040		;原点位置

RENEA_CENCER_LD020:				;
	MOV.L	#_PV1_SCRW_POS,R1	;
	MOV.L	@R1,R2			;(通信生ﾃﾞｰﾀ)
RENEA_CENCER_LD040:				;

	MOV.L	#_PVX_RNA_INDAT,R1	;生	SH4-->SH2 制御系へ
	MOV.L	R2,@R1			;(このﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟへ)

	MOV.L	#_PVP_RNAORG_PLS1,R1	;ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
	MOV.L	R2,@R1			;生通信ﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟさせる

	MOV.L	#_RNA_POS_OFFSET1,R4	;(電源投入時 取込み)
	MOV.L	@R4,R3			;(以降は設定変更時取込)
	SUB	R3,R2			;
	MOV.L	#_SET1_RNADIR_SEL1,R1	;
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF RENEA_CENCER_LD050	;
	NEG	R2,R2			;
RENEA_CENCER_LD050:			;ANS:R2


;;;;	--------------2015-10-15 MTS対応-------------
;;;;;	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:強化ﾘﾆｱ)
;;;;	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
;;;;	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
;;;;	MOV.W	@R1,R0						;
;;;;	CMP/EQ	#1,R0						;標準は0以外 jump(r4=20)
;;;;	BF	RENEA_CENCER_LD070				;(R2を1/2しないで R4=10*2にする)
;;;;	MOV.W	#D'10,R4					;(強化ﾘﾆｱ)0.1um  1/10--->1um (0.001mm)
;;;;RENEA_CENCER_LD070:						;
;;;;	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;	MOV.L	#_PVX_RNA_POSD1,R1				;これに原点ﾃﾞｰﾀを加えれば良い
;;;;	MOV.L	R2,@R1						;原点時の位置=0mm 1um(0.001mm)
;;;;
;;;;	MOV.L	#_RNA_POS_OFFSET2,R1	;
;;;;	MOV.L	@R1,R3			;原点
;;;;	ADD	R3,R2			;

;	---------2014-02-14 X社製-----------------------
	MOV.L	#_RNA_PROTOCOL_X,R1				;"1"X社製ﾌﾟﾛﾄｺﾙ
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;
	BF	RENEA_CENCER_LD060

	MOV.W	#D'1,R4						;1um
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVX_RNA_POSD1,R1				;これに原点ﾃﾞｰﾀを加えれば良い
	MOV.L	R2,@R1						;原点時の位置=0mm 1um(0.001mm)

;	-- 温度補正 2015-10-15
	MOV.L	#_X_PROTCOL_TMP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF RENEA_CENCER_LD090		;補正なし
	MOV.L	#_X_PROTCOL_TMP_PVLNG,R1	;//補正量
	MOV.W	@R1,R0				;+/-
	ADD	R0,R2				;ANS:R2
	M_BRA	RENEA_CENCER_LD090		;

;	--------- ﾐﾂﾄﾖ
RENEA_CENCER_LD060:						;
;	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:強化ﾘﾆｱ)
	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
	MOV.W	@R1,R0						;
	CMP/EQ	#1,R0						;標準は0以外 jump(r4=20)
	BF	RENEA_CENCER_LD070				;(R2を1/2しないで R4=10*2にする)
	MOV.W	#D'10,R4					;(強化ﾘﾆｱ)0.1um  1/10--->1um (0.001mm)
RENEA_CENCER_LD070:						;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVX_RNA_POSD1,R1				;これに原点ﾃﾞｰﾀを加えれば良い
	MOV.L	R2,@R1						;原点時の位置=0mm 1um(0.001mm)

RENEA_CENCER_LD090:						;
	MOV.L	#_RNA_POS_OFFSET2,R1	;
	MOV.L	@R1,R3			;原点
	ADD	R3,R2			;ANS:R2

;	===========================================
	MOV.L	#_DEBUG_MOD_CODE,R1		;
	MOV.W	@R1,R0				;
	MOV.W	#H'5AA5,R1			;
	CMP/EQ	R1,R0					;
	BF	DBG_RNA_END				;
;;;;
;;;;	-------------2012-10-05 1234,***,123,210---------------------
;;;;	MOV.L	#_SVP_MACINE_SEL1,R1			;
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#_MCN_FUJI_DBG1,R1			;
;;;;	CMP/EQ	R1,R0					;D=1234 且つｼｰｹﾝｽ
;;;;	BF	DBG_RNA_END			;待機点２が123、待機点３が210
;;;;	MOV.L	#_SVP_WT_DIG2,R1			;待機点選択2 123
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#D'123*10,R1				;
;;;;	CMP/EQ	R1,R0					;
;;;;	BF	DBG_RNA_END				;
;;;;	MOV.L	#_SVP_WT_DIG3,R1			;待機点選択3 210
;;;;	MOV.W	@R1,R0					;
;;;;	MOV.W	#D'210*10,R1				;
;;;;	CMP/EQ	R1,R0					;
;;;;	BF	DBG_RNA_END				;
;;;;	
;;;;
;	======== ﾃﾞﾊﾞｯｸ機能====
	MOV.L	#_INC_ENC_MM_POS,R1	;
	MOV.L	@R1,R2			;
	ADD	R3,R2			;原点

	MOV.L	#_SVP_ORGCAL_DAT5,R1	;ｻｰﾎﾞ8-89 DAT5 
	MOV.L	@R1,R1			;

	MOV.W	#D'10000,R0		;10.000=0 11000=+1.000 9000=-1.000
	SUB	R0,R1			;
	ADD	R1,R2			;ﾘﾆｱは1mm/1mm高い低い
	CMP/PL	R2			
	BT	DBG_RNA_100		;
	MOV	#1,R2
DBG_RNA_100
DBG_RNA_END
;	============================


					;CPUA->CPUB
	MOV.L	#_PVX_RNA_POSD2,R1	;変換	SH4-->SH2 0.5um->1mm+原点
	MOV.L	R2,@R1			;絶対位置(SH2ではこれを使用する)

	MOV.L	#_RNA_ABS_POS,R1	;//ﾎﾞﾙｽﾀ面高さ
	MOV.L	R2,@R1			;


	MOV.L	#_PVX_RNA_STLORK,R1		;//実測
	MOV.L	@R1,R2				;
	MOV.L	#_PVP_RNA_STLORK,R1		;
	MOV.L	R2,@R1				;




	SUB_END
	M_RTS


;;;[2015-10-15 MTS対応]
;;;[2015-10-15]_RENEA_CENCER_LOAD:
;;;[2015-10-15]	SUB_START
;;;[2015-10-15];	-------- 2009-03-11
;;;[2015-10-15]	MOV.L	#_WPAR_MCNRNA_SEL,R4		;//1:機械でﾘﾆｱｽｹｰﾙを使用しない構造･･原点復帰
;;;[2015-10-15]	MOV.W	@R4,R0				;
;;;[2015-10-15]	CMP/EQ	#1,R0				;
;;;[2015-10-15]	BF	RENEA_CENCER_LD020		;
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET1,R4		;_SVB_RNAORG_PLS1->_RNA_POS_OFFSET1->_PVP_RNAORG_PLS1
;;;[2015-10-15]	MOV.L	@R4,R2				;
;;;[2015-10-15]	M_BRA	RENEA_CENCER_LD040		;原点位置
;;;[2015-10-15]
;;;[2015-10-15]RENEA_CENCER_LD020:				;
;;;[2015-10-15]	MOV.L	#_PV1_SCRW_POS,R1	;
;;;[2015-10-15]	MOV.L	@R1,R2			;(通信生ﾃﾞｰﾀ)
;;;[2015-10-15]RENEA_CENCER_LD040:				;
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_INDAT,R1	;生	SH4-->SH2 制御系へ
;;;[2015-10-15]	MOV.L	R2,@R1			;(このﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟへ)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVP_RNAORG_PLS1,R1	;ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
;;;[2015-10-15]	MOV.L	R2,@R1			;生通信ﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟさせる
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET1,R4	;(電源投入時 取込み)
;;;[2015-10-15]	MOV.L	@R4,R3			;(以降は設定変更時取込)
;;;[2015-10-15]	SUB	R3,R2			;
;;;[2015-10-15]	MOV.L	#_SET1_RNADIR_SEL1,R1	;
;;;[2015-10-15]	MOV.W	@R1,R0			;
;;;[2015-10-15]	TST	R0,R0			;
;;;[2015-10-15]	TST_BIT_OF RENEA_CENCER_LD050	;
;;;[2015-10-15]	NEG	R2,R2			;
;;;[2015-10-15]RENEA_CENCER_LD050:			;
;;;[2015-10-15];	-----2008-11-11(h2w:2008-06-11) 1digt=0.05um(0:STD) 1digit=0.1um(1:強化ﾘﾆｱ)
;;;[2015-10-15]	MOV.W	#D'20,R4					;(STD)0.05um 1/20--->1um
;;;[2015-10-15]	MOV.L	#_RNA_PROTOCOL_SEL,R1				;
;;;[2015-10-15]	MOV.W	@R1,R0						;
;;;[2015-10-15]	CMP/EQ	#1,R0						;標準は0以外 jump(r4=20)
;;;[2015-10-15]	BF	RENEA_CENCER_LD070				;(R2を1/2しないで R4=10*2にする)
;;;[2015-10-15]	MOV.W	#D'10,R4					;(強化ﾘﾆｱ)0.1um  1/10--->1um (0.001mm)
;;;[2015-10-15]RENEA_CENCER_LD070:						;
;;;[2015-10-15]	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;[2015-10-15]	MOV.L	#_PVX_RNA_POSD1,R1				;これに原点ﾃﾞｰﾀを加えれば良い
;;;[2015-10-15]	MOV.L	R2,@R1						;原点時の位置=0mm 1um(0.001mm)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_POS_OFFSET2,R1	;
;;;[2015-10-15]	MOV.L	@R1,R3			;原点
;;;[2015-10-15]	ADD	R3,R2			;
;;;[2015-10-15]
;;;[2015-10-15];	===========================================
;;;[2015-10-15];	-------------2012-10-05 1234,***,123,210---------------------
;;;[2015-10-15]	MOV.L	#_SVP_MACINE_SEL1,R1			;
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#_MCN_FUJI_DBG1,R1			;
;;;[2015-10-15]	CMP/EQ	R1,R0					;D=1234 且つｼｰｹﾝｽ
;;;[2015-10-15]	BF	DBG_RNA_END			;待機点２が123、待機点３が210
;;;[2015-10-15]	MOV.L	#_SVP_WT_DIG2,R1			;待機点選択2 123
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#D'123*10,R1				;
;;;[2015-10-15]	CMP/EQ	R1,R0					;
;;;[2015-10-15]	BF	DBG_RNA_END				;
;;;[2015-10-15]	MOV.L	#_SVP_WT_DIG3,R1			;待機点選択3 210
;;;[2015-10-15]	MOV.W	@R1,R0					;
;;;[2015-10-15]	MOV.W	#D'210*10,R1				;
;;;[2015-10-15]	CMP/EQ	R1,R0					;
;;;[2015-10-15]	BF	DBG_RNA_END				;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15];	======== ﾃﾞﾊﾞｯｸ機能====
;;;[2015-10-15]	MOV.L	#_INC_ENC_MM_POS,R1	;
;;;[2015-10-15]	MOV.L	@R1,R2			;
;;;[2015-10-15]	ADD	R3,R2			;原点
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_SVP_ORGCAL_DAT5,R1	;ｻｰﾎﾞ8-89 DAT5 
;;;[2015-10-15]	MOV.L	@R1,R1			;
;;;[2015-10-15]
;;;[2015-10-15]	MOV.W	#D'10000,R0		;10.000=0 11000=+1.000 9000=-1.000
;;;[2015-10-15]	SUB	R0,R1			;
;;;[2015-10-15]	ADD	R1,R2			;ﾘﾆｱは1mm/1mm高い低い
;;;[2015-10-15]	CMP/PL	R2			
;;;[2015-10-15]	BT	DBG_RNA_100		;
;;;[2015-10-15]	MOV	#1,R2
;;;[2015-10-15]DBG_RNA_100
;;;[2015-10-15]DBG_RNA_END
;;;[2015-10-15];	============================
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_POSD2,R1	;変換	SH4-->SH2 0.5um->1mm+原点
;;;[2015-10-15]	MOV.L	R2,@R1			;絶対位置(SH2ではこれを使用する)
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_RNA_ABS_POS,R1	;//ﾎﾞﾙｽﾀ面高さ
;;;[2015-10-15]	MOV.L	R2,@R1			;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]	MOV.L	#_PVX_RNA_STLORK,R1		;//実測
;;;[2015-10-15]	MOV.L	@R1,R2				;
;;;[2015-10-15]	MOV.L	#_PVP_RNA_STLORK,R1		;
;;;[2015-10-15]	MOV.L	R2,@R1				;
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]
;;;[2015-10-15]	SUB_END
;;;[2015-10-15]	M_RTS
;;;[2015-10-15]



;	***********************************
;	***	ﾃﾞｰﾀﾊﾝﾄﾞｼｪｲｸあり	***
;	***********************************
_RENEA_ORGIN_SET:
	SUB_START
	MOV.L	#_PVX_RNA_INDAT,R1	;生	SH4-->SH2 制御系へ
	MOV.L	@R1,R2			;(このﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟへ)

	MOV.L	#_PVP_RNAORG_PLS1,R1	;ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
	MOV.L	R2,@R1			;生通信ﾃﾞｰﾀをﾊﾞｯｸｱｯﾌﾟさせる
					;本来はメインで
					;_SVB_RNAORG_PLS1に返すのが正しい姿

	MOV.L	#_RNA_POS_OFFSET1,R1	;(電源投入時 HMI->取込み)
	MOV.L	R2,@R1			;

;	==============================
	MOV.L	#_SET1_RNAORG_POS1,R4	;
	MOV.L	@R4,R0			;

	MOV.L	#_OLD_RNAORG_POS1,R4	;
	MOV.L	R0,@R4			;

	MOV.L	#_RNA_POS_OFFSET2,R4	;原点設定
	MOV.L	R0,@R4			;


	SUB_END
	M_RTS





















;	*******************************************
;	***	ﾊﾞｯｸｸﾞﾗﾝﾄﾞ実測転送		***
;	*******************************************

;
;	ﾃﾞﾊﾞｯｸ機能
;	角度表示
;		ｴﾝｺｰﾀﾞ角度
;		下死点高さ
;
;
_PV_DATA_DP_MOV:
	SUB_START

	MOV.L	#_RNA_ABS_POS,R3	;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
	MOV.L	@R3,R2			
	MOV.L	#_PVP_RENIA_POSI0,R4	;リニアセンサ現在位置(生表示用 ﾎﾞﾙｽﾀ面)
	MOV.L	R2,@R4


;	====== ﾃﾞﾊﾞｯｸ機能 2003-01-27 =====
;;	.AIF	_PRG_CHG20030127 EQ _COMPILE_YES	;ﾌﾟﾛｸﾞﾗﾑ変更箇所(反転仕様以外の標準に入れる変更)
;;	.AENDI

	MOV.L	#_SVP_MACINE_SEL1,R1			;
	MOV.W	@R1,R0					;

	CMP/EQ	#_MCN_DBG_COD21,R0			;89
	BF	NOMAL_DAIHAI_DISP10_1			;
;	==== ﾃﾞﾊﾞｯｸ ===
	MOV.L	#_RNA_ABS_POS,R3	;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
	MOV.L	@R3,R2			;
	M_BRA	NOMAL_DAIHAI_DISP10_E	;

NOMAL_DAIHAI_DISP10_1:

	CMP/EQ	#_MCN_DBG_COD22,R0			;88
	BF	NOMAL_DAIHAI_DISP10_2			;
;	==== ﾃﾞﾊﾞｯｸ ===

NOMAL_DAIHAI_DISP10_2:



NOMAL_DAIHAI_DISP10_S:
	MOV.L	#_RNA_CTL_POS1,R3	;//制御位置(下死点高さ)
	MOV.L	@R3,R2			;

;;	.AIF	_PRG_CHG20030127 EQ _COMPILE_YES	;ﾌﾟﾛｸﾞﾗﾑ変更箇所(反転仕様以外の標準に入れる変更)
;;	.AENDI
;;	MOV.L	#_ORGIN_END_FLG1,R4;	//電源投入の１回ON:OFFはない
;;	MOV.W	@R4,R0			;
;;	TST	R0,R0			;
;;	TST_BIT_ON NOMAL_DAIHAI_DISP10_E;
;;	MOV.L	#_RNA_ABS_POS,R3	;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
;;	MOV.L	@R3,R2			;
NOMAL_DAIHAI_DISP10_E:			;

	REG1_0CHK REG1=R2		;
	MOV.L	#_PVP_NOW_POSI000,R4	;(下死点高さ表示)
	MOV.L	R2,@R4			;


	MOV.L	#_DISP_ENC360,R5	;ｲﾝｸﾘﾒﾝﾀﾙENC
	MOV.L	#_RNA_ENC360,R6		;
	MOV.W	@R5,R2			;ｲﾝｸﾘﾒﾝﾀﾙからのみ表示 2014-09-09a

;;;;;2014-09-09a	MOV.L	#_MODE_SEL,R4		;
;;;;;2014-09-09a	MOV.W	@R4,R0			;
;;;;;2014-09-09a
;;;;;2014-09-09a
;;;;;2014-09-09	TST	#(_W1OPT+_W1CNT+_W1SGL+_W1INC+_W1DIC),R0	;
;;;;;2014-09-09a		TST	#(_W1OPT+_W1CNT+_W1SGL+_W1INC),R0		;
;;;;;2014-09-09a	TST_BIT_OF DISP_ENC_DIG_050				;
;;;;;2014-09-09a
;;;;;2014-09-09a	MOV.L	#_emg_err_flg,R1				;
;;;;;2014-09-09a	MOV.W	@R1,R0						;
;;;;;2014-09-09a	TST	R0,R0						;
;;;;;2014-09-09a	TST_BIT_ON DISP_ENC_DIG_050				;非常停止中[急停止はその場から動くから変えない]
;;;;;2014-09-09a
;;;;;2014-09-09a	MOV.L	#_SETX_POS_CTL_MATH,R1				;
;;;;;2014-09-09a	MOV.W	@R1,R0						;
;;;;;2014-09-09a	TST	#_DMATH_REVRSE,R0				;[20091007下振子]
;;;;;2014-09-09a	TST_BIT_OF DISP_ENC_DIG_050				;選択未/回転
;;;;;2014-09-09a	MOV	R5,R0						;
;;;;;2014-09-09a	MOV	R6,R5						;
;;;;;2014-09-09a	MOV	R0,R6						;
;;;;;2014-09-09aDISP_ENC_DIG_050:						;
;;;;;2014-09-09a	MOV.W	@R5,R2			;ｲﾝｸﾘﾒﾝﾀﾙからのみ表示
;;;;;2014-09-09a
;;;;;2014-09-09a;	=============== 4舎５入[2013-03-15] =================
;;;;;2014-09-09a	ADD	#5,R2						;
;;;;;2014-09-09a	MOV.W	#D'10,R4					;
;;;;;2014-09-09a	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
;;;;;2014-09-09a	DMULS.L	R4,R2						;
;;;;;2014-09-09a	STS	MACL,R2						;
;;;;;2014-09-09a	MOV.W	#D'3600,R4					;
;;;;;2014-09-09a	CMP/HI	R2,R4						;R3<R4(3600)
;;;;;2014-09-09a	BT	DISP_ENC_DIG_055				;
;;;;;2014-09-09a	SUB	R4,R2						;
;;;;;2014-09-09aDISP_ENC_DIG_055:
;	=================================================

	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0			;
	MOV.W	#D'3600,R4					;
	CMP/HI	R2,R4						;
	BT	DISP_ENC_DIG_080				;
	SUB	R4,R2						;
DISP_ENC_DIG_080:						;通常制御の結果

;	=============== 4舎５入[2014-09-09] =================
	ADD	#5,R2						;
	MOV.W	#D'10,R4					;
	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	DMULS.L	R4,R2						;
	STS	MACL,R2						;
	MOV.W	#D'3600,R4					;
	CMP/HI	R2,R4						;R3<R4(3600)
	BT	DISP_ENC_DIG_085				;
	SUB	R4,R2						;
DISP_ENC_DIG_085:
;	=================================================




;	===	342.0  ===
	MOV.L	#_CB_SEQ_CB_SEL342,R1			;342
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON DIG_DISP_CHK090			;表示切替ON 360

	MOV.L	#_SVP_MACINE_SEL1,R4			;
	MOV.W	@R4,R0					;
	CMP/EQ	#_MCN_DBG_COD11,R0			;99
	BF	DIG_DISP_CHK100				;
DIG_DISP_CHK090:
	MOV.L	#_CTL_ENC360,R5				;//360.0度
	MOV.W	@R5,R2					;これだけ生
DIG_DISP_CHK100:

	MOV.L	#_PVP_NOW_ANGLE_RNA,R4	;
	MOV.W	R2,@R4			;

;;;20091007	MOV.L	#_SETX_UPAREA_DIG,R3		;2;回転時待機点(上死点/待機点)	
;;;20091007	MOV.W	@R3,R2				;
;;;20091007	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
;;;20091007	MOV.L	#_PVP_TAIKITEN_POS,R4		;
;;;20091007	MOV.W	R2,@R4				;

	FAR_JSR	#_DNM_TAIKI_DIR_DISP,R0		;[2009-10-07下振子] 待機点をHMIへ


;	===	342.0  ===
	MOV.L	#_CB_SEQ_CB_SEL342,R1			;342
	MOV.W	@R1,R0					;
	TST	#BIT0,R0				;
	TST_BIT_ON NOMAL_DAIHAI_DISP20_2A		;

	MOV.L	#_SVP_MACINE_SEL1,R4			;
	MOV.W	@R4,R0					;

	CMP/EQ	#_MCN_DBG_COD31,R0			;79
	BF	NOMAL_DAIHAI_DISP20_1			;

	MOV.L	#_INC_ENC_MM_POS,R3			;79
	MOV.L	@R3,R2					;
	M_BRA	NOMAL_DAIHAI_DISP20_E			;

NOMAL_DAIHAI_DISP20_1:
	CMP/EQ	#_MCN_DBG_COD32,R0			;78
	BF	NOMAL_DAIHAI_DISP20_2			;

	MOV.L	#_CLS_RNA_MOST_DOWN_POS,R3		;最下死点
	MOV.L	@R3,R2					;
	M_BRA	NOMAL_DAIHAI_DISP20_E			;

NOMAL_DAIHAI_DISP20_2:
	CMP/EQ	#_MCN_DBG_COD33,R0			;77
	BF	NOMAL_DAIHAI_DISP20_3			;
NOMAL_DAIHAI_DISP20_2A:
	MOV.L	#_RNA_ABS_POS,R3			;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
	MOV.L	@R3,R2					;
	M_BRA	NOMAL_DAIHAI_DISP20_E			;絶対値

NOMAL_DAIHAI_DISP20_3:
	NOP
NOMAL_DAIHAI_DISP20_S:	;標準ﾌﾟﾛｸﾞﾗﾑ

;	----2013 調査ｿﾌﾄ-------------




	MOV.L	#_PVX_DAI_POS1,R3	;ﾀﾞｲﾊｲﾄ表示値・制御値
	MOV.L	@R3,R2			;
NOMAL_DAIHAI_DISP20_E:
	REG1_0CHK REG1=R2		;
	MOV.L	#_PVP_DYHITO_POS,R4	;
	MOV.L	R2,@R4			;

;
	MOV.L	#_SCAN_DBG_CNT,R1	;
	MOV.W	@R1,R0			;
	ADD	#1,R0			;
	EXTU.B	R0,R0			;
	MOV.W	R0,@R1			;



;	===== １サイクル時間

	MOV.L	#_CYCLE_TIME_PV,R1	;
	MOV.L	@R1,R2			;
;	================================
;;;;	SHLL	R2			;1msec ok
	MOV	R2,R6
	FAR_JSR	#_WD_DIV10,R0		;
	MOV.L	#_PVP_CYCLE_TIME0,R1	;
	MOV.W	R2,@R1			;
;	============================
	MOV.L	#D'60000,R2					;60.000秒
;;;;	MOV.L	#_CYCLE_TIME_PV,R1				;
;;;;	MOV.L	@R1,R4						;

	MOV	R6,R4						;
	TST	R4,R4						;
	TST_BIT_OF SPM_DISP_DAT_ERR				;
	
;;;;;	------ 2012-12-10 4捨5入を2012-12-10にしたがやっぱりやめる.(2013-02-08)
;;;;;		MOV	R4,R0		;
;;;;;		SHLR	R0		;
;;;;;MISS	ADD	R0,R2		;

	FAR_JSR	#_FPU_DIVS_32REG2_32REG1_R4_32REG2_R2,R0	;
	MOV.L	#_PVP_CYCLE_SPM1,R1				;
	MOV.W	R2,@R1						;
	MOV.L	#_PVP_DISP_SPM2,R1				;
	MOV.W	R2,@R1						;
SPM_DISP_DAT_ERR:
	

	MOV.L	#_STOPPING_TIM_FLG,R1		;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ用ﾌﾗｸﾞ BIT0測定開始 BIT6:停止中
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF STOP_TIM_DSP_EXT
	AND	#LOW ~BIT1,R0			;
	MOV.W	R0,@R1				;
	MOV.L	#_STOPPING_TIM_PV2,R1		;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ
	MOV.W	@R1,R2				;(1/10)
	MOV.L	#_PVP_STOP_TIM,R1		;
	MOV.W	R2,@R1				;

STOP_TIM_DSP_EXT:

;;2006-09-30	====== 過負荷モニタ 2003-01-27 =====
;;	MOV.L	#_PV_AD_DATA,R5			; 移動平均とった後の0~1000 DATA
;;	MOV.W	@R5,R2				; data 0~10.00v
;;	MOV.L	#_SET1_AMP100P_VLT,R1		;
;;	MOV.W	@R1,R4				;
;;	MOV.W	#_DT_100PER_1,R1		;data * 100.0per/volt
;;	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0	;(0割算付防止)

;	------ 2006-09-30過負荷ﾓﾆﾀとﾄﾙｸ兼用-----
	MOV.L	#_WPV_POWER_MONI,R1		;
	MOV.W	@R1,R2				;

	MOV.L	#_PVP_POWER_MONI,R1		;
	MOV.W	R2,@R1				;

;	====  2003-07-09 ===
	MOV.L	#_CYCL_DSP_DISENB,R1		;1:非表示 => 反転して出力
	MOV.W	@R1,R0				;0:表示
	NOT	R0,R0				;
	AND	#BIT0,R0			;
	MOV.L	#_CMD_1CYCLE_DSP1,R1		;1:表示
	MOV.W	R0,@R1				;

;	===================================
;	===	下限位置表示		===
;	===================================
;	345.9=0 10回目表示
;	345.9=1 下死点表示


DAIHAITO_DSP_020:
	MOV.L	#_CB_SEQ_CB_COM345,R1		;345
	MOV.W	@R1,R0				;
	MOV.W	#BIT9,R4			;
	TST	R4,R0				;345.9表示切替
	TST_BIT_OF DAIHAITO_DSP_050		;

	MOV.L	#_RNA_ABS_MINPOS,R1		;
	MOV.L	@R1,R2				;
	MOV.L	#_PVP_SLIDE_POS,R1		;
	MOV.L	R2,@R1				;

	MOV.W	#BIT0,R0			;
	MOV.L	#_CMD_DAIPOS_DSP1,R1		;2003-07-09 生産下限位置　 0:非表示　1:表示
	MOV.W	R0,@R1				;
	M_BRA	DAIHAITO_DSP_100		;


;	==== 標準の表示 ====
DAIHAITO_DSP_050:
	MOV.L	#_PRD_DAI_POS1,R1		;//補正含む
	MOV.L	@R1,R2				;

;----ﾃﾞﾊﾞｯｸ-------------
;;;;;	MOV.L	#_RNA_ABS_POS,R1			;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
;;;;;	MOV.L	@R1,R2					;
;----------------------


	MOV.L	#_PVP_SLIDE_POS,R1		;ｽﾗｲﾄﾞ位置・ﾀﾞｲﾊｲﾄを含めた位置(ｸﾗｯﾁは未使用)
	MOV.L	R2,@R1				;

	MOV.L	#_PRD_DAI_CMP_ENB,R1		;//1:比較 0:比較不可
	MOV.W	@R1,R0				;
	AND	#BIT0,R0			;
;----ﾃﾞﾊﾞｯｸ-------------
;;;;;	MOV.W	#BIT0,R0
;----------------------

	MOV.L	#_CMD_DAIPOS_DSP1,R1		;2003-07-09 生産下限位置　 0:非表示　1:表示
	MOV.W	R0,@R1				;
DAIHAITO_DSP_100:


;	=======================================
;	======= 2006-12-05 =====
	MOV.L	#_PRD_KJP_CMP_ENB,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_CMD_KJTECH_DSP1,R1		;
	MOV.W	R0,@R1				;


;	===== ﾃﾞﾊﾞｯｸ情報 ===




;	==== 2003-07-01 ===
	MOV.L	#_OUT_PLS_SPD,R1	;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
	MOV.L	@R1,R0
	MOV.L	#_PVP_OUT_PLS_SPD,R1	;SHIN
	MOV.L	R0,@R1			;

	MOV.L	#_ENC_PLS_SPD,R1	;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
	MOV.L	@R1,R0
	MOV.L	#_PVP_ENC_PLS_SPD,R1	;;SHIN
	MOV.L	R0,@R1			;


	MOV.L	#_ABS_ENC_PLS_SPD,R1	;// 
	MOV.L	@R1,R0
	MOV.L	#_PVP_ABS_ENC_SPD,R1	;ABS
	MOV.L	R0,@R1			;

	MOV.L	#_ABS_OUT_PLS_SPD,R1	;// (MIN機能有り 1KHZ)
	MOV.L	@R1,R0
	MOV.L	#_PVP_ABS_OUT_SPD,R1	;ABS
	MOV.L	R0,@R1			;
	
	MOV.L	#_PV_ENC_SPD_PER,R1	;//0~110.00%
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_ENC_SPD_PER,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PV_OUT_SPD_PER,R1	;//0~110.00%
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_OUT_SPD_PER,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PVC_BRK_ENC_SPD,R1	;= R14(ad2)
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_BRK_ENC_SPD,R1
	MOV.W	R0,@R1			;

	MOV.L	#_ENC_PLS_SPD_DIR,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_ENC_SPD_DIR,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_PVC_BRK_OUT_SPD,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_BRK_OUT_SPD,R1	;
	MOV.W	R0,@R1			;

	MOV.L	#_OUT_PLS_SPD_DIR,R1	;
	MOV.W	@R1,R0			;
	MOV.L	#_PVP_OUT_SPD_DIR,R1	;
	MOV.W	R0,@R1			;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	2009-10-07			***
;	***					***
;	*******************************************
_DNM_TAIKI_DIR_DISP:
	SUB_START
;	----------2011-09-19 ﾌﾞﾚｰｷﾃｽﾄの待機点-----
	MOV.L	#_BRKTST_SW_IN,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF DNM_TAIKI_DIRDISP_050	;

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360度
	MOV.W	#BIT6,R2			;
	NOT	R2,R2				;
	AND	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_WPAR_BRKTST_ORGDEG,R4		;ｸﾗﾝｸ角度直接
	MOV.W	@R4,R2				;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;
	M_BRA	DNM_TAIKI_DIRDISP_200		;
;	-----------------------------

DNM_TAIKI_DIRDISP_050:

	MOV.L	#_SETX_POS_CTL_MATH,R1		;
	MOV.W	@R1,R0				;
	TST	#_DMATH_DNDRIV,R0		;
	TST_BIT_OF DNM_TAIKI_DIRDISP_100	;

	MOV.L	#_DNM_DIR_SET_FLG,R1		;//
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF DNM_TAIKI_DIRDISP_100	;

	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360度
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_DNM_SETX_UPAREA_DIG,R3	;2;回転時待機点(上死点/待機点)	
	MOV.W	@R3,R2				;
	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;
	M_BRA	DNM_TAIKI_DIRDISP_200		;

DNM_TAIKI_DIRDISP_100:
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB222,R1	;
	MOV.W	@R1,R0				;360度
	MOV.W	#BIT6,R2			;
	NOT	R2,R2				;
	AND	R2,R0				;
	MOV.W	R0,@R1				;

	MOV.L	#_SETX_UPAREA_DIG,R3		;2;回転時待機点(上死点/待機点)	
	MOV.W	@R3,R2				;
	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0	;
	MOV.L	#_PVP_TAIKITEN_POS,R4		;
	MOV.W	R2,@R4				;

DNM_TAIKI_DIRDISP_200:

	SUB_END
	M_RTS

;	*******************************************
;	***	ﾒｲﾝにｻｲｸﾙ終了・描画消去要求	***
;	*******************************************
_CYCLE_END_DISP_SET:
	SUB_START
	MOV.W	#BIT0,R0			;
	MOV.L	#_HS_PVP_TAKIKI_FLG,R1		;
	MOV.W	R0,@R1				;
	SUB_END
	M_RTS



;	*******************************************
;	***	ﾒｲﾝにｻｲｸﾙ終了・描画消去要求	***
;	*******************************************
	.IMPORT	_TRD_SHOT_SIG			;

_LOT_SIG_SET:
	SUB_START
	MOV.B	#BIT0,R0			;
	MOV.L	#_HS_PVP_LOTCNT_FLG,R1		;
	MOV.W	R0,@R1				;

;	----- 2014-09-29--- KOMTRAX用
	MOV.L	#_CPUATOD_1CYCL_SIG,R1	;BIT0=0/BIT0=1 ｾｯﾄCPUA CLR CPUD
	MOV.W	R0,@R1				;



	SUB_END
	M_RTS


;	*******************************************
;	***	ﾒｲﾝにｻｲｸﾙ終了・描画消去要求	***
;	*******************************************
	.EXPORT	_TRD_SIG_SET
_TRD_SIG_SET:
	SUB_START

	MOV.W	#H'0F,R0	
	MOV.L	#_TRD_SHOT_SIG,R1
	MOV.W	R0,@R1				;
	
	SUB_END
	M_RTS




