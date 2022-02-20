/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			画面操作のメイン処理													*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-11-12
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include "dp_cpuab.h"							//DPRAM参照変数定義
#include "ssa_opram.h"							//OPRAM参照変数定義

/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		GMN_PAR009;						//ポジショナビット飛び回数		V01l_d

/* 定数定義 ---------------------------------------------------------- */
#define		E_OPSTS_OK	0x55					//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り
#define		E_OPSTS_WDT	0x54					//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り(WDT-UP)
#define		E_OPSTS_NON	0x00					//ｵﾌﾟｼｮﾝｶｰﾄﾞなし

#define		E_OPERR_CHK	0xff					//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ ﾁｪｯｸ

/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	OPDP_trans_chk(void);					//OP-DPRAM ⇔ FRAM ﾃﾞｰﾀ転送 & ﾁｪｯｸ処理

void	OPdata_set_kaku(void);					//ｵﾌﾟｼｮﾝ ﾃﾞｰﾀ転送処理
void	OPdata_sys_kaku(void);					//ｵﾌﾟｼｮﾝにｼｽﾊﾟﾗを格納
void	OP_pvdata_smp(void);					//ｵﾌﾟｼｮﾝ実測値ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
void	POSdata_set_kaku(void);					//ﾎﾟｼﾞｼｮﾅｰ ﾃﾞｰﾀ転送処理
void	OFF_set_start(void);					//ｵﾌｾｯﾄ調整ｽﾀｰﾄ
void	OFF_set_start_mng(void);				//ｵﾌｾｯﾄ ｽﾀｰﾄ表示管理
void	OPdata_offkan_smp(void);				//ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
void	KOUSEI_start(void);						//校正ｽﾀｰﾄ
void	KOUSEI_start_mng(void);					//校正ｽﾀｰﾄ表示管理
void	OPdata_koukan_smp(void);				//ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
void	AUTO_sura_seq_start(void);				//ｽﾗｲﾄﾞ自動調整ｼｰｹﾝｽ ｽﾀｰﾄ
void	AUTO_sura_start(void);					//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ
void	SURA_auto_start_mng(void);				//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ表示管理
void	MAIN_op_seq(void);						//ｼｰｹﾝｽをｵﾌﾟｼｮﾝへ転送
void	OPdata_bak_up(void);					//ｵﾌﾟｼｮﾝ ﾊﾞｯｸ ｱｯﾌﾟ処理
void	SURA_select_mng(void);					//ｽﾗｲﾄﾞ自動調節選択切り換え処理
void	POJI_data_chk(void);					//ﾎﾟｼﾞｼｮﾅﾊﾞｯｸｱｯﾌﾟ値監視

void	OPdata_bak(void);						//ｵﾌﾟｼｮﾝの現位置ﾃﾞｰﾀ返還

void	swap_ml(void *, UNl);					//ｲﾝﾃﾙ形式でﾃﾞｰﾀを格納(long)
void	swap_mw(void *, UNs);					//ｲﾝﾃﾙ形式でﾃﾞｰﾀを格納(word)
UNl		swap_il(void *);						//ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(long)
UNs		swap_iw(void *);						//ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(word)

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		OPDP_trans_chk
*  Function Name:	OP-DPRAM ⇔ FRAM ﾃﾞｰﾀ転送 & ﾁｪｯｸ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-01
********************************************************************************
*/
void	OPDP_trans_chk(void)
{

	if( OP_STATUS != E_OPSTS_NON ) {			//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り？		OP_STATUS が E_OPSTS_NON(0) じゃなければ始めはＯＰがいた。

/**************** V05j *********************
		if( OP_STATUS == E_OPSTS_WDT ) {		//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り(WDT-UP)？
			SEQ_PAR_079 |= BIT_10;				//ｵﾌﾟｼｮﾝ WDT異常
		}
		if( OP_ERROR1 & E_OPERR_CHK ) {			//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
			SEQ_PAR_079 |= BIT_8;				//ｵﾌﾟｼｮﾝ異常1(EPROM)
		}
		if( OP_ERROR2 & E_OPERR_CHK ) {			//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
			SEQ_PAR_079 |= BIT_9;				//ｵﾌﾟｼｮﾝ異常1(RAM)
		}
*******************************************/
		if( OP_STATUS_REAL != E_OPSTS_OK ) {		//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り(WDT-UP)？
			SEQ_PAR_079 |= BIT_10;					//ｵﾌﾟｼｮﾝ WDT異常
		}
		if( OP_ERROR1 & E_OPERR_CHK ) {				//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
			SEQ_PAR_079 |= BIT_8;					//ｵﾌﾟｼｮﾝ異常1(EPROM)
		}
		if( OP_ERROR2 & E_OPERR_CHK ) {				//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
			SEQ_PAR_079 |= BIT_9;					//ｵﾌﾟｼｮﾝ異常1(RAM)
		}


//		if( OP_STATUS == E_OPSTS_WDT ) {		//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り(WDT-UP)？
//			SEQ_PAR_079 |= BIT_10;				//ｵﾌﾟｼｮﾝ WDT異常
//		}else{
//			SEQ_PAR_079 &= ~BIT_10;				//ｵﾌﾟｼｮﾝ WDT異常
//		}
//		if( OP_ERROR1 & E_OPERR_CHK ) {			//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
//			SEQ_PAR_079 |= BIT_8;				//ｵﾌﾟｼｮﾝ異常1(EPROM)
//		}else{
//			SEQ_PAR_079 &= ~BIT_8;				//ｵﾌﾟｼｮﾝ異常1(EPROM)
//		}
//		if( OP_ERROR2 & E_OPERR_CHK ) {			//ｵﾌﾟｼｮﾝｶｰﾄﾞ ｴﾗｰ？
//			SEQ_PAR_079 |= BIT_9;				//ｵﾌﾟｼｮﾝ異常1(RAM)
//		}else{
//			SEQ_PAR_079 &= ~BIT_9;				//ｵﾌﾟｼｮﾝ異常1(RAM)
//		}

	}

	OPdata_set_kaku();							//オプションーデータ転送処理
	POSdata_set_kaku();							//ポジショナーデータ転送処理

	OFF_set_start_mng();						//ｵﾌｾｯﾄ ｽﾀｰﾄ表示管理
	KOUSEI_start_mng();							//校正ｽﾀｰﾄ表示管理
	SURA_auto_start_mng();						//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ表示管理

	MAIN_op_seq();								//ｼｰｹﾝｽをｵﾌﾟｼｮﾝへ転送

	AUTO_sura_seq_start();						//ｽﾗｲﾄﾞ自動調整ｼｰｹﾝｽ ｽﾀｰﾄ
	SURA_sv_chg();								//ｽﾗｲﾄﾞ自動調節ＳＶ変更処理

	OPdata_bak_up();							//ｵﾌﾟｼｮﾝ ﾊﾞｯｸ ｱｯﾌﾟ処理

	SURA_select_mng();							//ｽﾗｲﾄﾞ自動調節選択切り換え処理
	POJI_data_chk();							//ﾎﾟｼﾞｼｮﾅﾊﾞｯｸｱｯﾌﾟ値監視

}


/*
********************************************************************************
*  Module Name:		OPdata_set_kaku
*  Function Name:	ｵﾌﾟｼｮﾝ ﾃﾞｰﾀ転送処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OPdata_set_kaku(void)
{

	if( 00 == (CSTATUS_C & 0x06) ) {					//転送ＯＫ？ (OPｶｰﾄﾞ設定値転送ｽﾃｰﾀｽ読込)
		if( SVSW_CHG_FLG & BIT_4 ) {					//オプションデータチェンジフラグセット
			SVSW_CHG_FLG &= ~BIT_4;						//要求ﾌﾗｸﾞ ｸﾘｱ

			swap_ml(&CPOS_SET_POSI, SV_ATUOSU_D9);		//スライド自動調整設定値(2word)

//Sit-S 小数点入力なし
//	MOV	AL,SEQ_016_SV			;
//	AND	AL,BIT_6			;
//	SHR	AL,6				;
//	MOV	BL,SV_POINT_A1			;
//	DEC	BL				;
//	AND	BL,BIT_0			;
//	SHL	BL,1				;
//	OR	AL,BL				;
//	MOV	ES:CPOS_SET_UNIT,AL		;/* 単位＆小数点位置 */
			CPOS_SET_UNIT = 0;							//単位＆小数点位置(ﾀﾞﾐｰ)

			swap_mw(&CLO_STRAIN_L, SV_MAXHIZ_A24);		//最大歪　（左）(1word)
			swap_mw(&CLO_STRAIN_R, SV_MAXHI3_A24);		//最大歪　（右）(1word)

			swap_mw(&CLO_MAXLD_L, SV_MAXKAJ_A24);		//最大荷重（左）(1word)
			swap_mw(&CLO_MAXLD_T, SV_MAXKA2_A24);		//最大荷重（全）(1word)
			swap_mw(&CLO_MAXLD_R, SV_MAXKA3_A24);		//最大荷重（右）(1word)

			swap_mw(&CLO_PROOF_L, SV_KOUKAJ_A24);		//校正荷重（左）(1word)
			swap_mw(&CLO_PROOF_T, SV_KOUKA2_A24);		//校正荷重（全）(1word)
			swap_mw(&CLO_PROOF_R, SV_KOUKA3_A24);		//校正荷重（右）(1word)

			CLO_PROOF_SEI = SV_KOUSEI_A24;				//校正精度(1byte)

			swap_mw(&CLO_OVER_L, SV_OVERE1_A26);		//ｵｰﾊﾞｰﾛｰﾄﾞ（左）(1word)
			swap_mw(&CLO_OVER_T, SV_OVERE2_A26);		//ｵｰﾊﾞｰﾛｰﾄﾞ（全）(1word)
			swap_mw(&CLO_OVER_R, SV_OVERE3_A26);		//ｵｰﾊﾞｰﾛｰﾄﾞ（右）(1word)

			swap_mw(&CLO_LOWER_L, SV_ROALM1_A26);		//ﾛｱｰﾘﾐｯﾄ  （左）(1word)
			swap_mw(&CLO_LOWER_T, SV_ROALM2_A26);		//ﾛｱｰﾘﾐｯﾄ  （全）(1word)
			swap_mw(&CLO_LOWER_R, SV_ROALM3_A26);		//ﾛｱｰﾘﾐｯﾄ  （右）(1word)

			OPdata_sys_kaku();							//ｵﾌﾟｼｮﾝにｼｽﾊﾟﾗを格納

			CSTATUS_C |= 0x06;							//データ格納フラグセット
		}
	}

	OP_pvdata_smp();									//ｵﾌﾟｼｮﾝ実測値ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理

}


/*
********************************************************************************
*  Module Name:		OPdata_sys_kaku
*  Function Name:	ｵﾌﾟｼｮﾝにｼｽﾊﾟﾗを格納
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OPdata_sys_kaku(void)
{
	UNs	i;

	V25_OP_0 = SV_APARAD_A24;			//最低表示荷重 (1byte)

	i = (SEQ_020_SV & 0x01e0);
	i >>= 1;
	V25_OP_1 = i;						//(1byte)

	V25_OP_4 = (UNb)GMN_PAR009;			// ポジショナビット飛び回数		V01l_d



//	MOV	AX,SEQ_ROM			;V01c/* スライド角度＆エンコーダビット飛び回数のＲＯＭパラより転送 */
//	MOV	ES,AX				;V01c
//	MOV	SI,SYS_OPBIT_B1			;V01c
//	MOV	BL,ES:[SI]			;V01c
//	MOV	SI,SYS_OPSUR_B1			;V01c
//	MOV	AX,ES:[SI]			;V01c
//	MOV	DX,OP_AREA			;V01c
//	MOV	ES,DX				;V01c
//	MOV	ES:V25_OP_2,AL			;V01c
//	MOV	ES:V25_OP_3,AH			;V01c
//	MOV	ES:V25_OP_4,BL			;V01c

//	MOV	AX,SEQ_ROM			;V07/* スライド自動調節　異常検知シスパラ */
//	MOV	ES,AX				;V07
//	MOV	SI,SYS_OP_SU_TIME		;V07
//	MOV	AX,ES:[SI]			;V07
//	MOV	SI,SYS_OP_SU_POS		;V07
//	MOV	BX,ES:[SI]			;V07
//	MOV	SI,SYS_OP_SU_POS1		;V07
//	MOV	CX,ES:[SI]			;V07
//	MOV	DX,OP_AREA			;V07
//	MOV	ES,DX				;V07
//	MOV	ES:V25_OP_10,AX			;V07
//	MOV	ES:V25_OP_11,BX			;V07
//	MOV	ES:V25_OP_12,CX			;V07

}


/*
********************************************************************************
*  Module Name:		OP_pvdata_smp
*  Function Name:	ｵﾌﾟｼｮﾝ実測値ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-01
********************************************************************************
*/
void	OP_pvdata_smp(void)
{

//	if( OP_STATUS_DT == 0x55 ) {					//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {					//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?

		PV_LAMPDT_A23 = swap_iw(&CLO_OFAD_L);		//オフセット調整左(1word)
		PV_RAMPDT_A23 = swap_iw(&CLO_OFAD_R);		//オフセット調整右(1word)
		PV_AMPDAT_A23 = swap_iw(&CLO_OFAD_T);		//オフセット調整合計(1word)

//2011-01-18 koma		PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_L);		//荷重（TON）(1word)
//2011-01-18 koma		PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_T);		//荷重（TON）(1word)
//2011-01-18 koma		PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_R);		//荷重（TON）(1word)
//	ｼｰｹﾝｽにより表示内容を切り替える
		if( SEQ_PAR_113 & BIT_8 ) {
			PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_KEEP_L);	//荷重（TON）(1word)
			PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_KEEP_T);	//荷重（TON）(1word)
			PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_KEEP_R);	//荷重（TON）(1word)
		}
		else {
			PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_L);		//荷重（TON）(1word)
			PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_T);		//荷重（TON）(1word)
			PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_R);		//荷重（TON）(1word)
		}


		PV_DAIHAI_B5 = swap_il(&CPOS_NOW_MM);		//ﾀﾞｲﾊｲﾄ(2word)

/**************** V05j *********************
		if( PVGENNITI_FLG != 0xff ) {				//ﾊﾞｯｸｱｯﾌﾟ画面にて現位置データを変更してから”確認”が押される迄ｻﾝﾌﾟﾘﾝｸﾞしない
			PV_GENITI_B2 = swap_il(&CPOS_STD);		//現位置(2word)
		}
*******************************************/
	}

	if( SEQ_021_SV & BIT_2 ) {						//ｽﾗｲﾄﾞ自動調節ﾒﾓの時は設定値を挿入
		PV_DAIHAI_B5 = SV_ATUOS0_D9;				//ﾀﾞｲﾊｲﾄ(2word)
	}

}


/*
********************************************************************************
*  Module Name:		POSdata_set_kaku
*  Function Name:	ﾎﾟｼﾞｼｮﾅｰ ﾃﾞｰﾀ転送処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	POSdata_set_kaku(void)
{

	if( 00 == (CSTATUS_C & BIT_0) ) {				//転送ＯＫ？ (OPｶｰﾄﾞ設定値転送ｽﾃｰﾀｽ読込)
		if( SVSW_CHG_FLG & BIT_6 ) {				//ﾎﾟｼﾞｼｮﾅｰ ﾃﾞｰﾀ ﾁｪﾝｼﾞﾌﾗｸﾞｾｯﾄ？
			SVSW_CHG_FLG &= ~BIT_6;					//要求ﾌﾗｸﾞ ｸﾘｱ

//Sit-Sなし	%MOV_OP_2W(SV_KANDO_A21,CPOS_SET_MRE)	;/* 感度 */
//Sit-Sなし	%MOV_OP_2W(SV_UPDATA_A21,CPOS_SET_TOPL)	;/* 上限 */
//Sit-Sなし	%MOV_OP_2W(SV_DNDATA_A21,CPOS_SET_LOWL)	;/* 下限 */
//Sit-Sなし	%MOV_OP_2W(SV_GENITI_A21,CPOS_SET_STD)	;/* 現位置 */


			swap_ml(&CPOS_SET_MRE, SV_KANDO_A21);		//感度		V01j
			swap_ml(&CPOS_SET_TOPL, SV_UPDATA_A21);		//上限		V01j
			swap_ml(&CPOS_SET_LOWL, SV_DNDATA_A21);		//下限		V01j
			swap_ml(&CPOS_SET_STD, SV_GENITI_A21);		//現位置	V01j


			CPOS_SET_DELTA = SV_MODORI_A21;			//戻り量(1byte)
			CPOS_SET_ALFA = SV_DNSTOP_A21;			//下降停止(1byte)
			CPOS_SET_BETA = SV_UPSTOP_A21;			//上昇停止(1byte)
			CPOS_SET_GANMA = SV_SSEIDO_A21;			//制御精度(1byte)

			CSTATUS_C |= BIT_0;						//データ格納フラグセット

			PODATA_SET_FLG = 0;
		}
	}
}


/*
********************************************************************************
*  Module Name:		OFF_set_start
*  Function Name:	ｵﾌｾｯﾄ調整ｽﾀｰﾄ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
void	OFF_set_start(void)
{

	SEQ_PAR_451 |= BIT_0;				//荷重計 ｵﾌｾｯﾄ調整ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	OFF_SET_MNG_LAST = 0;				//V05j

}


/*
********************************************************************************
*  Module Name:		OFF_set_start_mng
*  Function Name:	ｵﾌｾｯﾄ ｽﾀｰﾄ表示管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OFF_set_start_mng(void)
{
	UNs	bf1, bf2;

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?			V05j
		return;
	}

/**************** V05j *********************
	bf1 = (SEQ_PAR_385 & BIT_0);			//ｵﾌｾｯﾄ終了(1:完了又は、異常)
	bf2 = OFF_SET_MNG_LAST;
	OFF_SET_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){							//オフセット調整終了？
		SEQ_PAR_451 &= ~BIT_0;				//荷重計 ｵﾌｾｯﾄ調整ｽﾀｰﾄ(1:ｽﾀｰﾄ)
		OPdata_offkan_smp();				//ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
	}
*******************************************/

	bf1 = (SEQ_PAR_382 & BIT_1);			//ｵﾌｾｯﾄ調整表示ﾃﾞｰﾀ作成
	bf1 >>= 1;
	PV_OFFSET_A1 = bf1;
}


/*
********************************************************************************
*  Module Name:		OPdata_offkan_smp
*  Function Name:	ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OPdata_offkan_smp(void)
{
//	if( OP_STATUS_DT == 0x55 ) {						//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {						//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?

		PV_OF_BAKL = CLO_OF_SETL;						//オフセット値左(1byte)
		PV_OF_BAKR = CLO_OF_SETR;						//オフセット値右(1byte)

		PV_OF_AVE_BAKL = swap_iw(&CLO_OF_AVE_SETL);		//オフセット補正左(1word)
		PV_OF_AVE_BAKR = swap_iw(&CLO_OF_AVE_SETR);		//オフセット補正右(1word)
		PV_OF_AVE_BAKT = swap_iw(&CLO_OF_AVE_SETT);		//オフセット補正合計(1word)

/**************** V05j *********************
		KJ_CHK_CNT4++;						//V05i

		PV_OF_BAKL_X = CLO_OF_SETL;						//オフセット値左(1byte)		V05i
		PV_OF_BAKR_X = CLO_OF_SETR;						//オフセット値右(1byte)		V05i

		PV_OF_AVE_BAKL_X = swap_iw(&CLO_OF_AVE_SETL);	//オフセット補正左(1word)	V05i
		PV_OF_AVE_BAKR_X = swap_iw(&CLO_OF_AVE_SETR);	//オフセット補正右(1word)	V05i
		PV_OF_AVE_BAKT_X = swap_iw(&CLO_OF_AVE_SETT);	//オフセット補正合計(1word)	V05i
*******************************************/
	}
}


/*
********************************************************************************
*  Module Name:		KOUSEI_start
*  Function Name:	校正ｽﾀｰﾄ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
void	KOUSEI_start(void)
{

	SEQ_PAR_451 |= BIT_1;				//荷重計 荷重校正ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	KOUSEI_MNG_LAST = 0;				//V05j

}


/*
********************************************************************************
*  Module Name:		KOUSEI_start_mng
*  Function Name:	校正ｽﾀｰﾄ表示管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	KOUSEI_start_mng(void)
{
	UNs	bf1, bf2;

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?			V05j
		return;
	}

/**************** V05j *********************
	bf1 = (SEQ_PAR_385 & BIT_1);			//荷重校正終了(1:完了又は、異常)
	bf2 = KOUSEI_MNG_LAST;
	KOUSEI_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_451 &= ~BIT_1;				//荷重計 荷重校正ｽﾀｰﾄ(1:ｽﾀｰﾄ)
		OPdata_koukan_smp();				//ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
	}
*******************************************/

	bf1 = (SEQ_PAR_382 & BIT_3);			//荷重計 荷重校正完了
	bf1 >>= 2;
	PV_KAJYUU_A1 = bf1;
}


/*
********************************************************************************
*  Module Name:		OPdata_koukan_smp
*  Function Name:	ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OPdata_koukan_smp(void)
{
//	if( OP_STATUS_DT == 0x55 ) {						//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {						//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?

		PV_GAIN_BAK1L = swap_iw(&CLO_GAIN_SET1L);		//最大歪み２０００左ゲイン(1word)
		PV_GAIN_BAK1R = swap_iw(&CLO_GAIN_SET1R);		//最大歪み２０００右ゲイン(1word)

		PV_GAIN_BAK2L = swap_iw(&CLO_GAIN_SET2L);		//最大歪み１５００左ゲイン(1word)
		PV_GAIN_BAK2R = swap_iw(&CLO_GAIN_SET2R);		//最大歪み１５００右ゲイン(1word)

		PV_GAIN_BAK3L = swap_iw(&CLO_GAIN_SET3L);		//最大歪み　８００左ゲイン(1word)
		PV_GAIN_BAK3R = swap_iw(&CLO_GAIN_SET3R);		//最大歪み　８００右ゲイン(1word)

		PV_GAIN_BAK4L = swap_iw(&CLO_GAIN_SET4L);		//最大歪み　４００左ゲイン(1word)
		PV_GAIN_BAK4R = swap_iw(&CLO_GAIN_SET4R);		//最大歪み　４００右ゲイン(1word)

		PV_GAIN_BAK5L = swap_iw(&CLO_GAIN_SET5L);		//最大歪み　２００左ゲイン(1word)
		PV_GAIN_BAK5R = swap_iw(&CLO_GAIN_SET5R);		//最大歪み　２００右ゲイン(1word)

/**************** V05j *********************
		KJ_CHK_CNT5++;						//V05i

		PV_GAIN_BAK1L_X = swap_iw(&CLO_GAIN_SET1L);		//最大歪み２０００左ゲイン(1word)	V05i
		PV_GAIN_BAK1R_X = swap_iw(&CLO_GAIN_SET1R);		//最大歪み２０００右ゲイン(1word)	V05i

		PV_GAIN_BAK2L_X = swap_iw(&CLO_GAIN_SET2L);		//最大歪み１５００左ゲイン(1word)	V05i
		PV_GAIN_BAK2R_X = swap_iw(&CLO_GAIN_SET2R);		//最大歪み１５００右ゲイン(1word)	V05i

		PV_GAIN_BAK3L_X = swap_iw(&CLO_GAIN_SET3L);		//最大歪み　８００左ゲイン(1word)	V05i
		PV_GAIN_BAK3R_X = swap_iw(&CLO_GAIN_SET3R);		//最大歪み　８００右ゲイン(1word)	V05i

		PV_GAIN_BAK4L_X = swap_iw(&CLO_GAIN_SET4L);		//最大歪み　４００左ゲイン(1word)	V05i
		PV_GAIN_BAK4R_X = swap_iw(&CLO_GAIN_SET4R);		//最大歪み　４００右ゲイン(1word)	V05i

		PV_GAIN_BAK5L_X = swap_iw(&CLO_GAIN_SET5L);		//最大歪み　２００左ゲイン(1word)	V05i
		PV_GAIN_BAK5R_X = swap_iw(&CLO_GAIN_SET5R);		//最大歪み　２００右ゲイン(1word)	V05i
*******************************************/

	}
}


/*
********************************************************************************
*  Module Name:		AUTO_sura_seq_start
*  Function Name:	ｽﾗｲﾄﾞ自動調整ｼｰｹﾝｽ ｽﾀｰﾄ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	AUTO_sura_seq_start(void)
{
	UNs	i, j;

	i = (SEQ_PAR_109 & BIT_6);		//ｽﾗｲﾄﾞ自動調整 ｽﾀｰﾄ(1:ｽﾀｰﾄ) 0 → 1　？
	j = AUTO_SEQ_LST;
	AUTO_SEQ_LST = i;
	j ^= i;
	if( i & j ){
		AUTO_sura_start();			//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ
	}

}


/*
********************************************************************************
*  Module Name:		AUTO_sura_start
*  Function Name:	ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	AUTO_sura_start(void)
{

	if(00 == (SEQ_PAR_109 & BIT_7)) {			//ｽﾗｲﾄﾞ自動調整 停止(1:停止)
		if(00 == (SEQ_PAR_385 & BIT_2)){		//位置決め終了の信号がＯＮの時は再スタートしない
			if(00 == (SEQ_021_SV & BIT_2)){		//ｽﾗｲﾄﾞ自動調節メモ機能有りの場合はスタートさせない
				SEQ_PAR_450 |= BIT_1;			//ｽﾗｲﾄﾞ自動調節 ｽﾀｰﾄ(1:ｽﾀｰﾄ)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SURA_auto_start_mng
*  Function Name:	ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ表示管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	SURA_auto_start_mng(void)
{
	UNs	bf1, bf2;

	bf1 = (SEQ_PAR_385 & BIT_2);			//位置決め終了(1:完了又は、異常)
	bf2 = SURA_AUTO_MNG_LAST;
	SURA_AUTO_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_450 &= ~BIT_1;				//ｽﾗｲﾄﾞ自動調節 ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	}

/*************	スライド自動調節中止信号立ち上がり？     ************/
	bf1 = (SEQ_PAR_109 & BIT_7);			//ｽﾗｲﾄﾞ自動調節 停止？
	bf2 = SURA_AUTO_MNG_LAST1;
	SURA_AUTO_MNG_LAST1 = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_450 &= ~BIT_1;				//ｽﾗｲﾄﾞ自動調節 ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	}
}


/*
********************************************************************************
*  Module Name:		MAIN_op_seq
*  Function Name:	ｼｰｹﾝｽをｵﾌﾟｼｮﾝへ転送
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	MAIN_op_seq(void)
{
	UNs	i, j;

	i = (SEQ_020_SV >> 5);				//荷重計ﾛｱｰﾘﾐｯﾄ検出
	j = (SEQ_020_SV >> 7);				//荷重計ｵｰﾊﾞｰﾛｰﾄﾞ検出
	i &= BIT_4;
	j &= BIT_3;
	i |= j;
	i |= (SEQ_PAR_451 & 0x00e7);
	SEQ_PAR_451 = i;

	SEQ_PAR_452 = ((SEQ_PAR_109 >> 8) & 0x009f);

/***********	109.13-->450.2   109.14-->450.3	****************/
	i = (SEQ_PAR_109 & 0x6003);
	j = (i >> 11);
	j |= (i << 4);
	j |= (SEQ_PAR_450 & 0xffc3);
	SEQ_PAR_450 = j;

}


/*
********************************************************************************
*  Module Name:		OPdata_bak_up
*  Function Name:	ｵﾌﾟｼｮﾝ ﾊﾞｯｸ ｱｯﾌﾟ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-05
********************************************************************************
*/
void	OPdata_bak_up(void)
{
	UNs	bf1, bf2;

/**************** V05j *********************
	bf1 = (SEQ_PAR_382 & 0x000a);
	bf2 = OPBAK_UP_LST;
	OPBAK_UP_LST = bf1;
	bf2 ^= bf1;
	if( 00 == (bf2 & bf1) ) {
		bf1 = OP_GENITI_READ;				//現位置データ読込完了フラグ　０ＦＦＨ＝完了
		OP_GENITI_READ = 0;
		bf2 = OPBAK_UP_LST1;
		OPBAK_UP_LST1 = bf1;
		bf2 ^= bf1;
		if( 00 == (bf2 & bf1) ) {
			return;
		}
	}

//	if( OP_STATUS_DT == 0x55 )				//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK )			//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?
	{										
											//念のために再度サンプリングしておく
		OPdata_koukan_smp();				//ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
		OP_pvdata_smp();					//ｵﾌﾟｼｮﾝ実測値ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
		OPdata_offkan_smp();				//ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理

		FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	}
*******************************************/

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//ｵﾌﾟｼｮﾝｶｰﾄﾞ有り?
		return;
	}

	/*** オフセット調整終了処理 ***/
	bf1 = SEQ_PAR_382 & (BIT_1+BIT_2+BIT_5);			//ｵﾌｾｯﾄ終了(bit1:正常終了、bit2,5:異常終了)
	bf2 = OFF_SET_MNG_LAST;
	OFF_SET_MNG_LAST = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if(bf2)										//終了に変化した？
	{
		if ( SEQ_PAR_451 & BIT_0 )				//オフセット調整スタートしてた？
		{
			if (bf2 & BIT_1)					//正常終了？
			{
				OPdata_offkan_smp();			//ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
				FRAM_csum_set();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
			}
		}
		SEQ_PAR_451 &= ~BIT_0;				//荷重計 ｵﾌｾｯﾄ調整ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	}

	/*** 荷重校正終了処理 ***/
	bf1 = SEQ_PAR_382 & (BIT_3+BIT_4);			//校正終了(bit3:正常終了、bit4:異常終了)
	bf2 = KOUSEI_MNG_LAST;
	KOUSEI_MNG_LAST = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if(bf2)										//終了に変化した？
	{
		if ( SEQ_PAR_451 & BIT_1 )				//校正スタートしてた？
		{
			if (bf2 & BIT_3)					//正常終了？
			{
				OPdata_koukan_smp();			//ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
				FRAM_csum_set();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
			}
		}
		SEQ_PAR_451 &= ~BIT_1;				//荷重計 荷重校正ｽﾀｰﾄ(1:ｽﾀｰﾄ)
	}

	/*** ポジショナ現位置データ登録処理 ***/
	bf1 = OP_GENITI_READ;					//現位置データ読込完了フラグ　０ＦＦＨ＝完了
	OP_GENITI_READ = 0;
	bf2 = OPBAK_UP_LST1;
	OPBAK_UP_LST1 = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if( bf2 )								//終了に変化した？
	{
		if ( SEQ_PAR_450 & BIT_0 )			//現位置登録スタートしてた？
		{
			if( 0xff == bf2 )				//正常終了？
			{
				PV_GENITI_B2 = swap_il(&CPOS_STD);		//現位置(2word)
				FRAM_csum_set();						//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
			}
		}
		SEQ_PAR_450 &= ~BIT_0;				//現位置登録(1:登録)
	}
}


/*
********************************************************************************
*  Module Name:		SURA_select_mng
*  Function Name:	ｽﾗｲﾄﾞ自動調節選択切り換え処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-07
********************************************************************************
*/
void	SURA_select_mng(void)
{
//sit-2のSEQ_PAR_168に対応した、sit-sの領域がないので、削除

//	UNs	bf1, bf2;
//
//	bf1 = (SEQ_PAR_168 & 0x0007);
//	bf2 = SURA_SEL_LST;
//	SURA_SEL_LST = bf1;
//
//	bf2 ^= bf1;
//	if(bf2 & bf1){
//		bf1 <<= 2;
//		SEQ_044_SV &= 0xffe3;
//		SEQ_044_SV |= bf1;
//
//		SVSW_CHG_FLG |= BIT_3;				//ｼｰｹﾝｽ(SEQ)転送要求
//		FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
//
//		if(WINDOW_NO == 6){					//段取　ｽﾗｲﾄﾞ調整
//
//			DAN_select_diap();				//段取画面 選択項目セレクト表示
//
//			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
//			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
//		}
//	}
}


/*
********************************************************************************
*  Module Name:		POJI_data_chk
*  Function Name:	ﾎﾟｼﾞｼｮﾅﾊﾞｯｸｱｯﾌﾟ値監視
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-07
********************************************************************************
*/
void	POJI_data_chk(void)
{

	if( SEQ_020_SV & BIT_6 ) {					//ｽﾗｲﾄﾞ自動調整(1：有)？

		if( PV_GENITI_B2 != SV_GENITI_CHK ) {
			SEQ_PAR_078 |= BIT_6;				//ﾎﾟｼﾞｼｮﾅﾊﾞｯｸｱｯﾌﾟ値照合異常
		}
	}
}


/*
********************************************************************************
*  Module Name:		OPdata_bak
*  Function Name:	ｵﾌﾟｼｮﾝの現位置ﾃﾞｰﾀ返還
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
void	OPdata_bak(void)
{

	swap_ml(&CPOS_STD_BAK, PV_GENITI_B2);			//現位置(2word)

	swap_mw(&CLO_GAIN_BAK1L, PV_GAIN_BAK1L);		//(1word)
	swap_mw(&CLO_GAIN_BAK1R, PV_GAIN_BAK1R);		//(1word)
	swap_mw(&CLO_GAIN_BAK2L, PV_GAIN_BAK2L);		//(1word)
	swap_mw(&CLO_GAIN_BAK2R, PV_GAIN_BAK2R);		//(1word)
	swap_mw(&CLO_GAIN_BAK3L, PV_GAIN_BAK3L);		//(1word)
	swap_mw(&CLO_GAIN_BAK3R, PV_GAIN_BAK3R);		//(1word)
	swap_mw(&CLO_GAIN_BAK4L, PV_GAIN_BAK4L);		//(1word)
	swap_mw(&CLO_GAIN_BAK4R, PV_GAIN_BAK4R);		//(1word)
	swap_mw(&CLO_GAIN_BAK5L, PV_GAIN_BAK5L);		//(1word)
	swap_mw(&CLO_GAIN_BAK5R, PV_GAIN_BAK5R);		//(1word)

	CLO_OF_BAKL = PV_OF_BAKL;						//(1byte)
	CLO_OF_BAKR = PV_OF_BAKR;						//(1byte)

	swap_mw(&CLO_OF_AVE_BAKL, PV_OF_AVE_BAKL);		//(1word)
	swap_mw(&CLO_OF_AVE_BAKR, PV_OF_AVE_BAKR);		//(1word)
	swap_mw(&CLO_OF_AVE_BAKT, PV_OF_AVE_BAKT);		//(1word)

}


/*
********************************************************************************
*  Module Name:		swap_ml
*  Function Name:	ｲﾝﾃﾙ形式でﾃﾞｰﾀを格納(long)
*  Input	:		転送先ｱﾄﾞﾚｽ[ｲﾝﾃﾙ形式]
*					転送元ﾃﾞｰﾀ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
void	swap_ml(void *dst_p, UNl src_d)
{
	UNb	*wk_p;

	wk_p = dst_p;

	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p = (src_d & 0x000000ff);

}

/*
********************************************************************************
*  Module Name:		swap_mw
*  Function Name:	ｲﾝﾃﾙ形式でﾃﾞｰﾀを格納(word)
*  Input	:		転送先ｱﾄﾞﾚｽ[ｲﾝﾃﾙ形式]
*					転送元ﾃﾞｰﾀ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
void	swap_mw(void *dst_p, UNs src_d)
{
	UNb	*wk_p;

	wk_p = dst_p;

	*wk_p++ = (src_d & 0x00ff);
	src_d >>= 8;
	*wk_p = (src_d & 0x00ff);

}


/*
********************************************************************************
*  Module Name:		swap_il
*  Function Name:	ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(long)
*  Input	:		転送元ｱﾄﾞﾚｽ[ｲﾝﾃﾙ形式]
*  Return	: 		取得ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
UNl		swap_il(void *src_p)
{
	UNb	*wk_p;
	UNl	wk;

	wk_p = src_p;

	wk = *(wk_p+3);
	wk <<= 24;
	wk |= (*(wk_p+2) << 16);
	wk |= (*(wk_p+1) << 8);
	wk |= *wk_p;

	return(wk);
}


/*
********************************************************************************
*  Module Name:		swap_iw
*  Function Name:	ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(word)
*  Input	:		転送元ｱﾄﾞﾚｽ[ｲﾝﾃﾙ形式]
*  Return	: 		取得ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-11-12
********************************************************************************
*/
UNs		swap_iw(void *src_p)
{
	UNb	*wk_p;
	UNs	wk;

	wk_p = src_p;

	wk = *(wk_p+1);
	wk <<= 8;
	wk |= *wk_p;

	return(wk);
}


/*** END ***/
