
#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義


#pragma section	wkram1	// 2010-09-21 wdt-up対策 ｾｸｼｮﾝ=時はBwkram1

/*==========================================================================*/
/*		テスト用の仮定義													*/
/*==========================================================================*/
//UNs		OP_STATUS_DT;			//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H

/*==========================================================================*/
/*		新ワーク領域定義（Sit-S）											*/
/*==========================================================================*/
UNi		SVPV_LCD_FLG;							//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
UNs		SV_DANSUU_SRV_BAK;						//工程数 セーブ
//UNs		SV_TAIKIKAKU_SRV_BAK;					//待機角の格納
//UNl		SV_TAIKIPOS_SRV_BAK;					//待機位置の格納

UNl		SV_TAIKIPOS_SRV;            /* 待機位置 */
UNs		SV_KAITEN_SRV;              /* 回転方式 */
UNs		SV_DANSUU_SRV;              /* 段数 */
UNs		SV_TAIKIKAKU_SRV;           /* 待機角 */
UNs		SV_TAIKSPD_SRV;             /* 基準速度 */
UNl		SV_DAIHAITO_SRV;            /* ダイハイト */
UNs		SV_HOASEI_SRV;              /* 補正データ */
UNs		SV_TAIKTIM_SRV;             /* 待機時間 */
UNs		SV_1DANDEG_SRV;             /* 1段目目標角度 */
UNs		SV_2DANDEG_SRV;             /* 2段目目標角度 */
UNs		SV_3DANDEG_SRV;             /* 3段目目標角度 */
UNs		SV_4DANDEG_SRV;             /* 4段目目標角度 */
UNs		SV_5DANDEG_SRV;             /* 5段目目標角度 */
UNs		SV_6DANDEG_SRV;             /* 6段目目標角度 */
UNs		SV_7DANDEG_SRV;             /* 7段目目標角度 */
UNs		SV_8DANDEG_SRV;             /* 8段目目標角度 */
UNs		SV_9DANDEG_SRV;             /* 9段目目標角度 */
UNs		SV_10DANDEG_SRV;            /* 10段目目標角度 */
UNl		SV_1DANPOS_SRV;             /* 1段目目標位置 */
UNl		SV_2DANPOS_SRV;             /* 2段目目標位置 */
UNl		SV_3DANPOS_SRV;             /* 3段目目標位置 */
UNl		SV_4DANPOS_SRV;             /* 4段目目標位置 */
UNl		SV_5DANPOS_SRV;             /* 5段目目標位置 */
UNl		SV_6DANPOS_SRV;             /* 6段目目標位置 */
UNl		SV_7DANPOS_SRV;             /* 7段目目標位置 */
UNl		SV_8DANPOS_SRV;             /* 8段目目標位置 */
UNl		SV_9DANPOS_SRV;             /* 9段目目標位置 */
UNl		SV_10DANPOS_SRV;            /* 10段目目標位置 */
UNs		SV_1DANSPD_SRV;             /* 1段目移動速度 */
UNs		SV_2DANSPD_SRV;             /* 2段目移動速度 */
UNs		SV_3DANSPD_SRV;             /* 3段目移動速度 */
UNs		SV_4DANSPD_SRV;             /* 4段目移動速度 */
UNs		SV_5DANSPD_SRV;             /* 5段目移動速度 */
UNs		SV_6DANSPD_SRV;             /* 6段目移動速度 */
UNs		SV_7DANSPD_SRV;             /* 7段目移動速度 */
UNs		SV_8DANSPD_SRV;             /* 8段目移動速度 */
UNs		SV_9DANSPD_SRV;             /* 9段目移動速度 */
UNs		SV_10DANSPD_SRV;            /* 10段目移動速度 */
UNs		SV_1DANTIM_SRV;             /* 1段目停止時間 */
UNs		SV_2DANTIM_SRV;             /* 2段目停止時間 */
UNs		SV_3DANTIM_SRV;             /* 3段目停止時間 */
UNs		SV_4DANTIM_SRV;             /* 4段目停止時間 */
UNs		SV_5DANTIM_SRV;             /* 5段目停止時間 */
UNs		SV_6DANTIM_SRV;             /* 6段目停止時間 */
UNs		SV_7DANTIM_SRV;             /* 7段目停止時間 */
UNs		SV_8DANTIM_SRV;             /* 8段目停止時間 */
UNs		SV_9DANTIM_SRV;             /* 9段目停止時間 */
UNs		SV_10DANTIM_SRV;            /* 10段目停止時間 */
//UNs		SV_CYCTIM_SRV;              /* サイクルタイム */
//UNs		SV_TAIKAN_SRV;              /* 待機完了範囲 */
UNs		SV_MOKKAN_SRV;              /* 目標完了範囲 */
UNs		SV_KAJYUU_PRS;				/* 荷重補正 V01m*/
UNs		SV_KAJYUU_OBJP;				/* 荷重目標 V01m*/

UNs		disp_stg, disp_stg_sel;
UNl		language_chg;

UNs		PV_STPTIM_B2;							/* ssc_tbl.c にて使用		*/

//UNs		PV_KOUTEI1_NO;							/*                      	*/
//UNs		PV_KOUTEI2_NO;							/*                      	*/
//UNs		PV_KOUTEI3_NO;							/*                      	*/
//UNs		PV_KOUTEI4_NO;							/*                      	*/
//UNs		PV_KOUTEI5_NO;							/*                      	*/

UNs		PV_STPTM_OLD;							/*                      	*/
UNs		PV_MLNO01_C15;							/*                      	*/
UNs		PV_MLNO02_C15;							/*                      	*/
UNs		PV_MLNO03_C15;							/*                      	*/
UNs		PV_MLNO04_C15;							/*                      	*/
UNs		PV_MLNO05_C15;							/*                      	*/
UNs		PV_MLNO06_C15;							/*                      	*/
UNs		PV_MLNO07_C15;							/*                      	*/
UNs		PV_MLNO08_C15;							/*                      	*/
UNs		PV_MLNO09_C15;							/*                      	*/
UNs		PV_MLNO10_C15;							/*                      	*/

UNs		PV_MLDNO2_F11[8];		//DB 16 DUP(?)	;	/* V01j */

//UNl		PVB_RNAORG_PLS1;						/*							*/
//UNl		SV_GENITI_CHK;							/*							*/

UNs		PV_CAMNA1_C1;							/*                      	*/
UNs		PV_MLDMES_C1;							/*							*/
UNs		PV_OFFSET_A1;							/*							*/
UNs		PV_DATINI_A1;							/*							*/
UNs		PV_KAJYUU_A1;							/*							*/
UNs		PV_GAIBU_A1;							/*							*/
UNs		PV_BACKDA_A1;							/*							*/

//2002-08-08
//UNs		deg_OLD	[ 3 ];							/* 角度前回値				*/
UNs		deg_OLD	[ 4 ];							/* 角度前回値				*/
UNs		rbit_OLD[ 3 ];							/* ﾘｾｯﾄ   指令ﾋﾞｯﾄ前回値	*/
UNs		cbit_OLD[ 3 ];							/* ｶｳﾝﾀUP 指令ﾋﾞｯﾄ前回値	*/

UNs		TAIKI_ZEN_MOD;							/* ルーレット前回描画方向	*/
UNs		TAIKITEN_DIRECT;						/* 待機点データ（クラッチ）	*/

UNs		SEISAN_DISP_FLG;						// 生産行程表示	 (00:なし／FF:あり)
UNs		INTROCK_DISP_FLG;						// ガイダンス表示(00:なし／FF:あり)

UNs		IROCK_NO	 [ INTROCK_MAX ];			/* ｲﾝﾀｰﾛｯｸ表示番号列		*/
UNs		IROCK_NO_LAST[ INTROCK_MAX ];			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/

/*==========================================================================*/
/*		キー入力用のワーク領域定義											*/
/*==========================================================================*/
UNs		KEY_DATA_CODE, KEY_DATA_MODE;

UNs		Key_up[4],Key_dn[4],Key_last[4];

/*==========================================================================*/
/*		旧ワーク領域定義(Sit-2より)											*/
/*==========================================================================*/
/***	表示用のワーク領域定義		***/
UNs		GAMEN_NO;					//DW ?	;/* 画面コード */
UNs		GAMEN_CODE;					//DB ?	;/* 画面コード */
UNs		WINDOW_NO;					//DW ?	;/* 画面コード */
UNs		CSR_FLG;					//DB ?	;/* カーソル有り画面フラグ */

UNs		CSR_CNT;					/* カーソルカウンタ */
UNs		CSR_CNT1;					/* カーソルカウンタ */
UNs		SV_CNT;						/* 設定値カウンタ */
UNs		PV_CNT;						/* 実測値カウンタ */
UNs		SW_CNT;						/* ＳＷデータカウンタ */
UNs		SW_CNT1;					/* ＳＷデータカウンタ */

//UNs		CSR_CNT2;				/* カーソルカウンタ */
//UNs		SV_CNT2;				/* 設定値カウンタ */
//UNs		PV_CNT2;				/* 実測値カウンタ */
//UNs		SW_CNT2;				/* ＳＷデータカウンタ */

CSR_TBL_TDEF	CSR_buff[110];		/* カーソル情報テーブル定義領域	*/
SV_TBL_TDEF		SV_buff[80];		/* 設定値情報テーブル定義領域	*/
PV_TBL_TDEF		PV_buff[40];		/* 実測値情報テーブル定義領域	*/
SW_TBL_TDEF		SW_buff[70];		/* ＳＷデータ情報テーブル定義領域	*/

UNs		PV_DISP_CNT;				/* 表示実測値カウンタ */
UNs		SW_DISP_CNT;				//次回表示ＳＷデータカウンタ

UNs		LCD_WORK1[15][16][40];		/* 表示ﾜｰｸ領域LCD1[何行何ﾄﾞｯﾄ目何文字目] */
UNs		LCD_WORK2[15][16][40];		/* 表示ﾜｰｸ領域LCD2[何行何ﾄﾞｯﾄ目何文字目] */
UNs		LCD_WORK3[15][16][40];		/* 表示ﾜｰｸ領域LCD3[何行何ﾄﾞｯﾄ目何文字目] */ /* V01  */
//UNs		LCD_WIN1[9][16][40];	/* 表示ﾜｰｸ領域LCD1[何行何ﾄﾞｯﾄ目何文字目] */
//UNs		LCD_WIN2[9][16][40];	/* 表示ﾜｰｸ領域LCD2[何行何ﾄﾞｯﾄ目何文字目] */

UNs		CSR_FLG_CNT;				//DW ?	;/* 現在のカーソル位置カウント */
UNs		SV_FLG_CNT;					//DW ?	;/* 初期値セット */
UNs		SW_FLG_CNT;					//DW ?	;/* 初期値セット */

UNs		CSR_POS;					//DW ?	;/* カーソルポジションデータ読込 */
UNs		CSR_POS_LAST;				//DW ?	;/* 前回カーソルポジションデータ読込 */
UNs		CSR_ON_FLG;					//DB ?	;/* カーソル表示フラグＯＮ */

UNs		SWDATA_DISP_CNT;			//DW ?	;/* ＳＷデータ表示用ループカウント */
UNs		SVSW_CHG_FLG;				//DB ?	;/* データチェンジフラグセット */

//UNs		SV_DISP_BUFF[20];			//DB 20 DUP(?)	;/* 設定値中間バッファ（ＡＳＣＩＩ） */
UNl		SV_DISP_BUFF;				//DB 20 DUP(?)	;/* 設定値中間バッファ（ＡＳＣＩＩ） */

UNs		SV_DATA_CHG;				//DB ?	;//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
UNs		CSR_TBL_POS_NOW;			//DW ?	;/* カーソル現在位置アドレス */
UNs		SV_TBL_POS_NOW;				//DW ?	;/* カーソル現在位置アドレス */
UNs		SW_TBL_POS_NOW;				//DW ?	;/* カーソル現在位置アドレス */
UNs		DISP_CHG_FLG;				//DB ?	;/* 表示反転フラグセット */

UNs		SV_DISP_CNT;				//DB ?	;/* 設定値表示個数＝入力処理個数 */
UNs		SV_ENT_CNT;					//DB ?
UNs		TENKEY_CNT;					//DB ?	;/* 入力オーバー？ */
UNs		NO_SUPRESU;					//DB ?
UNs		INTER_ROCK_FLG;				//DB ?	;/* インターロック有り？ */
UNs		PATH_WORD_CNT;				//DB ?		;

UNs		SEI_INF_BUFF[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
UNs		SEI_INF_BUFF1[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
UNs		SEI_INF_BUFF2[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
UNs		SEI_WRT_POS;				//DW ?	;/* 表示位置 */
UNs		SEI_WRT_CNT;				//DW ?		;/* 表示文字数 */
UNs		SEI_WRT_ADR;				//DW ?		;/* 表示文字数 */
UNs		IROCK_BUFF[40];				//DW 40 DUP(?)	;
UNs		IROCK_BUFF01[320/2];		//DB 320 DUP(?)	;
UNs		SEI_INF_FLG;				//DB ?
UNs		SEI_INF_FLG_LAST;			//DB ?		;

UNs		GAMEN_WRITE_CNT;			//DB ?		;
//UNs		SEQ_056_WORK[30/2];				//DB 30 DUP(?)	;
UNs		SEQ_044_WORK[30/2];				//DB 30 DUP(?)	;
//UNs		IROCK_NO01;					//DW ?;
//UNs		IROCK_NO02;					//DW ?;
//UNs		IROCK_NO03;					//DW ?;
//UNs		IROCK_NO04;					//DW ?;
//UNs		IROCK_NO05;					//DW ?;
//UNs		IROCK_NO06;					//DW ?;
//UNs		IROCK_NO07;					//DW ?;
//UNs		IROCK_NO08;					//DW ?;
//UNs		IROCK_NO09;					//DW ?;
//UNs		IROCK_NO010;				//DW ?;
//UNs		IROCK_NO011;				//DW ?;
//UNs		IROCK_NO012;				//DW ?;

//UNs		IROCK_NO1_LAST;				//DW ?
//UNs		IROCK_NO01_LAST[30];		//DW 30 DUP(?)	;
UNs		IROC_CHG_FLG;				//DW ?	;
UNs		IROC_CHG_FLG1;				//DW ?	;
UNs		IL_DISP_LAST;				//DB ?
UNs		GAMEN_NO_IROCK;				//DW ?
UNs		SEISAN_FLG;					//DB ?	;
UNs		SEISAN_FLG_LAST;			//DB ?	;
UNs		IROCK_SHR_LAST;				//DB ?
UNs		SVPV_DATA_FLG;				//DB ?
UNs		SOUSA_LEFT_FLG;				//DB ?
UNs		ERR_MONI_LAST1;				//DW ?
UNs		ERR_MONI_LAST2;				//DW ?
UNs		ERR_MONI_LAST3;				//DW ?
UNs		DAN_SOUSA_DAT;				//DW ?
UNs		RULET_DIG_TBL_ADR;			//DW ?
UNs		SEI_COUNT_LAST1;			//DB ?;
UNs		SEI_COUNT_LAST2;			//DB ?;
UNs		SEI_COUNT_LAST3;			//DB ?;
UNs		SEI_COUNT_LAST4;			//DB ?;

//UNs		GAMEN_ON_FLG;				//DB ?
UNs		IL_DISP_FLG;				//DB ?		;/* ＩＬ表示フラグリセット */
UNs		INI_FLG	;					//DB ?
//UNs		SEQ_020_SV_BUFF;			//DB ?
UNs		SEQ_018_SV_BUFF;			//DB ?
UNs		BASE_CLS_CNT;				//DW ?
UNs		SEI_INF_SPATH_CNT;			//DW ?
UNs		SUM_CHK_ERR;				//DB ?
UNs		DAN_NON_GAMEN;				//DB ?
UNs		SV_CHK_ERR;					//DB ?
UNs		SV_CMP_ERR;					//DB ?
UNs		SV_SUM1_ERR;				//DB ?
UNs		SV_SUM2_ERR;				//DB ?
UNs		SV_DPRAM_ERR;				//DB ?

UNs		INCH_DATA_FLG;				//DB ?	;/* INCH処理フラグ */

UNs		OP_MESS_DISP_LAST1;			//DB ?	;
UNs		OP_MESS_DISP_LAST2;			//DB ?	;
UNs		OP_MESS_DISP_LAST3;			//DB ?	;

UNs		OFF_SET_MNG_LAST;			//DB ?	;
UNs		OFF_SET_MNG_LAST1;			//DB ?	;
UNs		KOUSEI_MNG_LAST;			//DB ?	;
UNs		KOUSEI_MNG_LAST1;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST1;		//DB ?	;
UNs		SURA_AUTO_MNG_LAST2;		//DB ?	;

UNs		SEIGAMEN_CNT;				//DB ?	;
UNs		SEGAMEN_ADR;				//DW ?	;

UNs		OFF_SET_MNG_LAST2;			//DB ?	;
UNs		OFF_SET_MNG_LAST3;			//DB ?	;
UNs		OFF_SET_MNG_LASTX;			//DB ?	;
UNs		KOUSEI_MNG_LAST2;			//DB ?	;
UNs		YOUBI_LAST;					//DB ?

UNs		PODATA_SET_FLG;				//DB ?	;

UNs		ONOFF_FLG;					//DB ?	;
UNs		ONOFF_LAST1;				//DB ?	;
UNs		ONOFF_LAST2;				//DB ?	;
UNs		ONOFF_LAST3;				//DB ?	;
UNs		ONOFF_LAST4;				//DB ?	;
UNs		ONOFF_LAST5;				//DB ?	;
UNs		ONOFF_LAST6;				//DB ?	;
//UNs		ONOFF_LAST7;				//DB ?	;
//UNs		ONOFF_LAST8;				//DB ?	;
//UNs		ONOFF_LAST9;				//DB ?	;
//UNs		ONOFF_LAST10;				//DB ?	;

UNs		GAMEN_B6_NON_FLG;			//DB ?	;

UNs		INI_POS_ERR_FLG;			//DB ?	;

UNs		PV_ADBAKD_A14;				//DW ?	;

UNs		ENCO_DATA_BCD;				//DW ?	;
UNs		ENCO_DATA_HEX;				//DW ?	;

UNs		OFFSET_END_FLG;				//DB ?	;/* オフセット調整完了？ */

UNs		MCN_SEQ_LAST1;				//DB ?		;
UNs		MCN_SEQ_LAST2;				//DB ?		;
UNs		MCN_SEQ_LAST3;				//DB ?		;
UNs		MCN_SEQ_LAST4;				//DB ?		;
UNs		MCN_SEQ_LAST5;				//DB ?		;

UNs		MCN_DATA_NO1;				//DB ?		;
UNs		MCN_DATA_NO2;				//DB ?		;
UNs		MCN_DATA_NO3;				//DB ?		;
UNs		MCN_DATA_NO4;				//DB ?		;
UNs		MCN_DATA_NO5;				//DB ?		;

UNs		MCN_REC_FLG;				//DB ?		;

//UNs		GAMEN_DISP_FLG;				//DB ?	;
UNs		GGAMEN_DISP_FLG;			//DB ?	;

UNs		CARA_CHG_FLG;				//DB ?	;
UNs		YOKOBAI_CNT;				//DW ?	;/* 横倍カウンタ */
UNs		YOKOBAI_ADR;				//DW ?	;/* 横倍アドレス */
UNs		YOKO_BAI_WORK[32*16];		//DB 32*16 DUP(?)	;/* データをワーク領域へ転送 */

UNs		KAN_BANK_NO;				//DB ?		;V05

UNs		GENGO_CHG_LAST;				//DB ?		;
//UNs		GENGO_CHG_LAST1;			//DB ?		;
UNs		WORK_BUFF_NAME[20];			//DW 20 DUP(?);

UNs		BASE_WORK;					//DW ?		;

UNs		KT_DUMMY_01;				//DW ?	;
UNs		KT_DUMMY_02;				//DB ?	;

UNs		DAI_SVDATA_FLG;				//DB ?	;/* ダイハイト処理有効？ */
//UNs		SEQ_030_WK;					//DB ?	;
UNs		SEQ_023_WK;					//DB ?	;

UNs		AUTO_SEQ_LST;				//DB ?	;

UNs		SV_0401_FLG;				//DB 	?	;
UNs		SV_1101_FLG;				//DB ?	;
UNs		SW_1101_FLG;				//DB ?	;
UNs		SW_1102_FLG;				//DB ?	;
UNs		SW_1103_FLG;				//DB ?	;

UNs		CSR_MLD_WORK[32/2];			//DB 32 DUP(?)	;/* カーソルを移動すると文字の */

UNs		SIT_MOLD3_RCV_BUFF[50];		//DW	50	DUP(?)	;

UNs		TAIKITEN_DAT;				//DW ?	;/* 待機点だったらルーレットを再表示 */	EXTRN	TAIKITEN_DAT		: WORD	;/* 待機点だったらルーレットを再表示 */
UNs		RULET_NOW_LST;				//DW ?	;
UNs		DEG_DISP_LST;				//DW ?	;/* 角度ﾃﾞｰﾀ変化あり？ */
UNl		DEG_DISP_DATA[2];			//DD	?	;
									//DD	?	;

UNs		DEG_LCD_BUFF[32*12];		//DB 32*12 DUP(?)	;/* 角度表示専用バッファ */

UNs		STOPTIME_DISP_LST;			//DW ?	;/* 角度ﾃﾞｰﾀ変化あり？ */
UNl		STOPTIME_DISP_DATA[2];		//DD	?	;
									//DD	?	;

UNs		STOPTIME_LCD_BUFF[32*12];	//DB 32*12 DUP(?)	;/* 角度表示専用バッファ */

UNs		PFOUT_DATA_BAK;				//DB ?	;

UNs		DAT_LCD_KAN_BAK;			//DB ?	;

UNs		DEG_DISP_FLG;				//DB ?	;
//UNs		STOP_DISP_FLG;				//DB ?	;
UNs		RULET_DISP_FLG;				//DB ?	;/* ルーレット表示ＯＫ */
//UNs		RULET_NON_FLG;				//DB ?	;
UNs		CSR_MOVE_OK_FLG;			//DB ?	;/* カーソル移動禁止 */

UNs		SW14_ON_FLG;				//DB ?	;
UNs		SW14_ON_CNT;				//DB ?	;
UNs		SET_KEY_LST;				//DB ?	;

UNs		KIDO_FLG_FLG;				//DB 2 DUP(?)	;/* 輝度データ読込＆格納 */
UNs		KIDO_FLG_PV;				//DB ?		;/* 輝度データ読込＆格納 */

UNs		GAIBU_RST_LAST;				//DB ?	;
//UNs		GAIBU_RST_LAST1;			//DB ?	;
UNs		GAIBU_RST_LAST2;			//DB ?	;
UNs		GAIBU_RST_LAST3;			//DB ?	;
//UNs		GAIBU_RST_LAST4;			//DB ?	;
//UNs		GAIBU_RST_LAST5;			//DB ?	;
//UNs		GAIBU_RST_LAST6;			//DB ?	;
//UNs		GAIBU_RST_LAST7;			//DB ?	;
//UNs		GAIBU_RST_LAST8;			//DB ?	;

//UNs		GAIBU_CHG_FLG;				//DB ?	;

UNs		TAIKITEN_FLG;				//DB ?	;
UNs		TAIKITEN_LAST;				//DB ?
UNs		TAIKITEN_DATA;				//DW ?
UNs		TAIKI_NOW_POS;				//DW ?	;
UNs		TAIKI_ZEN_POS;				//DW ?	;

UNs		COUNT_HOSEI_ADR;			//DW ?	;/* 反転アドレスデータ待避 */
UNs		SURA_HOSEI_ADR;				//DW ?	;/* 反転アドレスデータ待避 */

UNs		SWCHG_DISP_ON_FLG;			//DB ?	;
UNs		SEISAN_SW56_FLG;			//DB ?	;
UNs		SEISAN_SW56_TIM;			//DW ?	;
UNs		OPBAK_UP_LST;				//DB ?	;
UNs		OPBAK_UP_LST1;				//DB ?	;

UNs		SW14_ON1_FLG;				//DB ?	;
UNs		SW14_ON6_FLG;				//DB ?	;
UNs		SW14_ON1_FLG_BAK2;			//DB ?	;
UNs		SW14_ON1_FLG_BAK3;			//DB ?	;
UNs		SW14_ON1_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BACK;			//DB ?	;

UNs		TAIKI_LST;					//DW ?	;

UNs		CAMNAME_INP_CNT;			//DB ?	;
UNs		NAME_CHG_FLG;				//DB ?	;/* 名称変更中？ */
UNs		CAM_NAME_NO;				//DB ?	;/* 変更カム名称番号読込 */
UNs		SUOERTH_BUFF[3];			//DW 3 DUP(?)	;

UNs		CSR_FLG_CNT_BAK;			//DW ?	;/* 現在のカーソル位置カウント */
UNs		CSR_FLG_CNT_BAK3;			//DW ?	;/* 現在のカーソル位置カウント */
UNs		SV_FLG_CNT_BAK;				//DW ?	;/* 初期値セット */
UNs		SW_FLG_CNT_BAK;				//DW ?	;/* 初期値セット */

UNs		CAMOUT_MUSK;				//DW ?	;/* 汎用出力マスクビット */
UNs		CAMOUT_BIT;					//DW ?	;/* 汎用出力ビット */

UNs		GAMEN_NO_CAM;				//DW ?	;
UNs		DAN_WIN_FLG;				//DB ?	;	V01j(INS)
UNs		DAN_CSR_LST;				//DB ?	;

//UNs		SW14_DISP7_NON;				//DB ?	;

UNs		SET_SPM_LST;				//DB ?	;
UNs		KATNAME_INP_CNT;			//DB ?	;/* 入力カウンター１ */

//UNs		PV_MLDNO1_F0[16];			//DB 16 DUP(?)	;
UNs		PV_MLDNO1_F0;				//DB 16 DUP(?)	;
UNs		PV_MLDNO2_F0[16];			//DB 16 DUP(?)	;

UNs		SINCAM_LST;					//DB ?	;	
UNs		TAIKITEN_FLG_FLG;			//DB ?	;/* すでにフラグを立てていたらやめ */

UNs		CSR_CLS_FLG;				//DB ?	;
UNs		PVCNT_DISP_CNT;				//DB ?	;
UNs		PVALL_FLG;					//DB ?	;
UNs		PVGENNITI_FLG;				//DB ?	;

UNs		CSR_FLG_BUF;				//DW ?	;/*  */
UNs		SV_FLG_BUF;					//DW ?	;/*  */

UNs		ENCO_DATA_HEX1;				//DW ?	;

UNs		RULET_GAKU_FLG;				//DW ?	;
UNs		RULET_GAKU_LST;				//DB ?	;

UNs		SEI_ON6_LST1;				//DB ?	;
UNs		SEI_ON6_LST2;				//DB ?	;
UNs		SEI_ON6_LST3;				//DB ?	;
UNs		SEI_ON6_LST4;				//DB ?	;
UNs		SEI_ON1_LST;				//DB ?	;

UNs		DAN_GAMEN_NON;				//DB ?	;
UNs		SEL_GAMEN_NON;				//DB ?	;
UNs		CAM_GAMEN_NON;				//DB ?	;
UNs		EJE_GAMEN_NON;				//DB ?	;
UNs		MIS_GAMEN_NON;				//DB ?	;
UNs		ROT_GAMEN_NON;				//DB ?	;

UNs		ROT1_GAMEN_NON;				//DB ?	;
UNs		ROT2_GAMEN_NON;				//DB ?	;
UNs		ROT3_GAMEN_NON;				//DB ?	;

UNs		CSR_FLG_CNT_LST;			//DW ?	;/* カーソル番号セット */

UNs		POWRE_OK_FLG;				//DW ?	;

UNs		PVDATA_NON;					//DB ?	;

UNs		CAR_ROM_SEG;				//DW ?	;

UNs		PV_SUM_CHK;					//DW ?	;
UNs		EE_SUM_CHK;					//DW ?	;

UNs		POWER_DOWN_FLG;				//DB ?	;

UNs		SW56_UPTOP_FLG;				//DB ?	;'98-08-05

//V01u	UNs		KAT_DATCHG_FLG;				//DB ?	;
UNs		KAT_DATCHG_FLG_DUMMY;				//DB ?	;
UNs		KAT_CNTCHG_FLG;				//DB ?	;

UNs		SW14_DISP7_DANNON;			//DB ?	;'98-08-31/*スライド以外ないときはジャンプ  */
//UNs		OP_NON_FLG;					//DB ?	;

UNs		SYS_HIGHSPM_B1;				//DW ?	;V01a
UNs		SYS_LOWSPM_B1;				//DW ?	;V01a
UNs		RULET_HIGH_FLG;				//DB ?	;/* 高速ルーレット描画フラグセット */
UNs		RULET_HIGH_LST;				//DB ?	;
UNs		CB1_SPMDAT_PVV;				//DW ?	;/* 読み込み */

UNs		PV_TLINKSMP_DAT;			//DW ?	;V03j

UNs		ENC_SPD_CNT;				//DW ?		;
UNl		ENCSPD_ADD;					//DD	?		;
UNs		ENCSPD_BF[20];				//DW	10	DUP (?)	;
									//DW	10	DUP (?)	;

UNs		CSR_DAN_CSR_LST;			//DW ?		;V01a/* 段取り画面SW56ｼｰｹﾝｽｷｬﾝｾﾙ用 */

UNs		SW56_MUSK_FLG;				//DW ?		;V01b

UNs		MLD_100_GNO;				//DW ?		;MLD100/* 型管理画面番号初期化 */
//UNs		MLD_100_NO;					//DW ?		;MLD100/* 型管理画面番号初期化 */
UNs		MLD_100_FLG;				//DB ?		;MLD100/* 型管理フラグ初期化 */
//UNs		MLD_100_CARD_FLG;			//DB ?		;MLD100/*  */

UNs		MEM_ADR;					//DW ?	;
UNs		MEM_BNK;					//DW ?	;
UNs		MLD_WRITE_BNK;				//DB ?	;

UNs		CSR_POS_G15;				//DB ?	;/*  */

UNs		CSR_MOVE_NON;				//DB ?	;/* カーソルは動かない？ */

UNs		MLD100_INI_FLG;				//DB ?	;

UNs		DAN_DAN_FLG;				//DB ?	;

UNs		CSR_FLG_CNT_BACK;			//DW ?		;
UNs		WINDOW_NO_BACK;				//DW ? 		;

UNs		DAN_KEY_FLG;				//DB ?		;

UNs		G07_WIN_FLG;				//DB ?		;

UNs		FILCK_CNT;					//DW ?			;
UNs		FILCK_STEP1_FLG;			//DB ?			;
UNs		FILCK_STEP2_FLG;			//DB ?			;
UNs		FILCK_STEP3_FLG;			//DB ?			;

UNs		NEXT_READ_NO;				//DW ?	;/* 次型番号設定値 */

UNs		KEY_DOWN14_FLG;				//DB ?	;/* ＫＥＹ立ち下がりフラグリセット */
UNs		SW14_MUSK_FLG;				//DW ?	;

UNs		SW14_MUSK_FLG_SW2;			//DW ?	;

UNs		CSR_G07_NO1;				//DW ?	;/* カーソル先頭位置と同じ？ */
UNs		CSR_G07_NO2;				//DW ?	;/* カーソル先頭位置と同じ？ */

UNs		SYS_SPMPM_B1P;				//DW ?	;
UNs		SYS_SPMPM_B1M;				//DW ?	;

//UNs		SEQ_022_FLG;				//DB ?	;
UNs		SEQ_019_FLG;				//DB ?	;

UNs		SYS_MISSEL_SV;				//DB ?		;

UNs		SURA_SEL_LST;				//DB ?	;

UNs		DAN_CLS_CNT;				//DW ?		;2000-07-04/* 表示した個数カウンタ */

UNs		SEI_GAI_LST;				//DB ?
UNs		GENG_SEQ_LST;				//DB ?
UNs		NEXT_MLDSEQ_FLG;			//DB ?		;2001-08-07 /*シーケンス用次型データ読み込みフラグＯＮ*/

UNs		PV_CAMSW1_C1[4];		//DB 8 DUP(?)	;BIT_1
UNs		PV_CAMSW2_C1[4];		//DB 8 DUP(?)	;BIT_2
UNs		PV_CAMSW3_C1[4];		//DB 8 DUP(?)	;BIT_3
UNs		PV_CAMSW4_C1[4];		//DB 8 DUP(?)	;BIT_4
UNs		PV_CAMSW5_C1[4];		//DB 8 DUP(?)	;BIT_5
UNs		PV_CAMSW6_C1[4];		//DB 8 DUP(?)	;BIT_6
UNs		PV_CAMSW7_C1[4];		//DB 8 DUP(?)	;BIT_7
UNs		PV_CAMSW8_C1[4];		//DB 8 DUP(?)	;BIT_8
UNs		PV_CAMSW9_C1[4];		//DB 8 DUP(?)	;BIT_9
UNs		PV_CAMSWA_C1[4];		//DB 8 DUP(?)	;BIT_A
UNs		PV_CAMSWB_C1[4];		//DB 8 DUP(?)	;BIT_B
UNs		PV_CAMSWC_C1[4];		//DB 8 DUP(?)	;BIT_C
UNs		PV_CAMSWD_C1[4];		//DB 8 DUP(?)	;BIT_D
UNs		PV_CAMSWE_C1[4];		//DB 8 DUP(?)	;BIT_E
UNs		PV_CAMSWF_C1[4];		//DB 8 DUP(?)	;BIT_F

UNs		PV_CAMNA01_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１名称 */
UNs		PV_CAMNA02_C1[4];		//DB 8 DUP(?)	;/* ロータリカム２名称 */
UNs		PV_CAMNA03_C1[4];		//DB 8 DUP(?)	;/* ロータリカム３名称 */
UNs		PV_CAMNA04_C1[4];		//DB 8 DUP(?)	;/* ロータリカム４名称 */
UNs		PV_CAMNA05_C1[4];		//DB 8 DUP(?)	;/* ロータリカム５名称 */
UNs		PV_CAMNA06_C1[4];		//DB 8 DUP(?)	;/* ロータリカム６名称 */
UNs		PV_CAMNA07_C1[4];		//DB 8 DUP(?)	;/* ロータリカム７名称 */
UNs		PV_CAMNA08_C1[4];		//DB 8 DUP(?)	;/* ロータリカム８名称 */
UNs		PV_CAMNA09_C1[4];		//DB 8 DUP(?)	;/* ロータリカム９名称 */
UNs		PV_CAMNA10_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１０名称 */
UNs		PV_CAMNA11_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１１名称 */
UNs		PV_CAMNA12_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１２名称 */
UNs		PV_CAMNA13_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１３名称 */
UNs		PV_CAMNA14_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１４名称 */
UNs		PV_CAMNA15_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１５名称 */
UNs		PV_CAMNA16_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１６名称 */
UNs		PV_CAMNA17_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１７名称 */
UNs		PV_CAMNA18_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１８名称 */
UNs		PV_CAMNA19_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１９名称 */
UNs		PV_CAMNA20_C1[4];		//DB 8 DUP(?)	;/* ロータリカム２０名称 */

//UNs		PV_EJECT1_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT2_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT3_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT4_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT5_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT6_NAME[4];		//DB 10 DUP(?)   ;

UNs		PV_KOUMOKU1_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU2_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU3_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU4_NAME[8];	//DB 16 DUP(?)	;

UNs		PV_KINOU01_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU02_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU03_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU04_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU05_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU06_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU07_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU08_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU09_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU10_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU11_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU12_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU13_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU14_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU15_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU16_NAE[8];		//DB 16 DUP(?)	;


UNs		SEQ_PAR_101_BAK;		/* V00p */
UNs		disp_stg_sel_bak;		/* V00p */
UNs		WINDOW_NO_bak;			/* V00p */
UNs		PV0_PAR_A_CHAR;			/* V00p */    /* ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
UNs		PV0_PAR_B_CHAR;			/* V00p */    /* ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
UNs		PV0_TBL_A_CHAR;			/* V00p */    /* ｾﾝｻのﾃｰﾌﾞﾙ番号 ASCII */
UNs		PV0_TBL_B_CHAR;			/* V00p */    /* ｾﾝｻのﾃｰﾌﾞﾙ番号 ASCII */
UNs		PV0_INTER_VER2;			/* V00p */    /* ｲﾝﾀｰﾛｯｸﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
UNs		PV0_DEFULT_VER2;		/* V00p */    /* 初期値ﾃﾞｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
UNs		PV0_SEQ_VER2;			/* V00p */    /* ｼｰｹﾝｽﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
UNl		PV0_NOW_POSI000;		/* V00q */    /* 下限上高さPV */
UNl		PV0_DYHITO_POS;			/* V00q */    /* 下限位置PV */
UNl		PV0_SLIDE_POS;			/* V01  */    /* 生産下限PV */
UNl		PV0_NOWPOSI_SLIDE;		/* V01  */    /* 生産下限or下限上高PV */

UNs		GAIBU_RST_BAK;			/* V00t */

UNs		PV0_MONALM_P01;
UNs		PV0_MONALM_P02;
UNs		PV0_MONALM_P03;
UNs		PV0_MONALM_P04;
UNs		PV0_MONALM_A01;
UNs		PV0_MONALM_A02;
UNs		PV0_MONALM_A03;
UNs		PV0_MONALM_A04;
UNs		PV0_MONALM_A05;
UNs		PV0_MONALM_A06;
UNs		PV0_MONALM_A07;
UNs		PV0_MONALM_A08;
UNs		PV0_MONALM_B01;
UNs		PV0_MONALM_B02;
UNs		PV0_MONALM_B03;
UNs		PV0_MONALM_B04;
UNs		PV0_MONALM_B05;
UNs		PV0_MONALM_B06;
UNs		PV0_MONALM_B07;
UNs		PV0_MONALM_B08;
UNl		PV0_MONALM_C01;
UNl		PV0_MONALM_C02;
UNl		PV0_MONALM_C03;
UNl		PV0_MONALM_C04;
UNl		PV0_MONALM_C05;
UNl		PV0_MONALM_C06;
UNl		PV0_MONALM_C07;
UNl		PV0_MONALM_C08;
UNs		PV0_MONALM_B01_SIGN;
UNs		PV0_MONALM_B02_SIGN;
UNs		PV0_MONALM_B03_SIGN;
UNs		PV0_MONALM_B04_SIGN;
UNs		PV0_MONALM_B05_SIGN;
UNs		PV0_MONALM_B06_SIGN;
UNs		PV0_MONALM_B07_SIGN;
UNs		PV0_MONALM_B08_SIGN;
UNs		PV0_MONALM_C01_SIGN;
UNs		PV0_MONALM_C02_SIGN;
UNs		PV0_MONALM_C03_SIGN;
UNs		PV0_MONALM_C04_SIGN;
UNs		PV0_MONALM_C05_SIGN;
UNs		PV0_MONALM_C06_SIGN;
UNs		PV0_MONALM_C07_SIGN;
UNs		PV0_MONALM_C08_SIGN;

UNs		MOTION_SV_CHG_CANCEL;			/* V01d */

UNs		TAIKIKAKU_CHG_FLG;				/* V01i */
UNs		GAMNE_REDISP_COD;				/* V01i */

UNs		SEQ_PAR_107_BAK;				/* V01j */
UNs		SEQ_PAR_427_CHG;				/* V01j */
UNs		SEQ_PAR_427_ONE;				/* V01j */
UNs		SEQ_PAR_427_OFE;				/* V01j */
UNs		SEQ_PAR_427_BAK;				/* V01j */
UNs		autokana_sw56_bak;				/* V01j */
UNs		ADC_DISP_FLG;					/* V01j */
UNs		ADC_CHG_LST;					/* V01j */
UNs		ADC_CHG_LST1;					/* V01j */
UNs		ADC_CHG_LST2;					/* V01j */
UNs		ADC_CHG_LST3;					/* V01j */
UNs		ADC_CHG_LST4;					/* V01j */
UNs		ADC_CHG_LST5;					/* V01j */
UNs		ADC_CHG_LST2_2;					/* V01j */
UNs		ADC_MODE_FLG;					/* V01j */
UNs		ADC_STEP_FLG;					/* V01j */
UNs		ADC_STPCHG_FLG;					/* V01j */
UNs		ADC_FILCK_LST;					/* V01j */
UNs		ADC_SW2_FLG;					/* V01j */
UNs		ADC_SW34_FLG;					/* V01j */
UNs		ADC_SW5_FLG;					/* V01j */
UNs		ADC_SW6_FLG;					/* V01j */
UNs		SW14_DISP7_NON;					/* V01j */
UNs		ADC_STEP_NO[4];					/* V01j */
UNs		ADC_STEP_NO_LAST[4];			/* V01j */
UNs		step_flick_flg;					/* V01j */
UNs		step_flick_flg_bak;				/* V01j */
UNs		step_flick_cnt;					/* V01j */

UNl		CAR_LNG_KAJ_AREA;				/* V01k */
UNs		SYO_LNG_KAJ_CNT;				/* V01k */

UNl		PV0_KAGEN_POSITIONER;				/* V01l_b */

UNs		SYO_LNG_SUR_CNT;				/* V01m */

UNs		DEB_WORD_FLG1;					/* V01n_b */
UNs		DEB_WORD_FLG2;					/* V01n_b */
UNs		DEB_WORD_FLG3;					/* V01n_b */
UNs		DEB_WORD_FLG4;					/* V01n_b */
UNs		DEB_WORD_FLG5;					/* V01n_b */
UNs		DEB_WORD_FLG6;					/* V01n_b */
UNs		DEB_WORD_FLG7;					/* V01n_b */
UNs		DEB_WORD_FLG8;					/* V01n_b */
UNs		DEB_WORD_FLG9;					/* V01n_b */
UNs		DEB_WORD_FLG10;					/* V01n_b */
UNs		DEB_WORD_FLG11;					/* V01n_b */
UNs		DEB_WORD_FLG12;					/* V01n_b */
UNs		DEB_WORD_FLG13;					/* V01n_b */
UNs		DEB_WORD_FLG14;					/* V01n_b */
UNs		DEB_WORD_FLG15;					/* V01n_b */
UNs		DEB_WORD_FLG16;					/* V01n_b */

//★★★★★★★	以下、ＳＩＴ−４で追加		★★★★★★★
UNl		DEBUG_CNT;

UNs		CSR_BAK_M_LEN;	
UNs		CSR_BAK_X_POS;	
UNs		CSR_BAK_Y_POS;	
UNs		CSR_BAK_C_COL;	
UNs		CSR_BAK_B_COL;	
UNs		CSR_BAK_SIZE;	
UNs		*CSR_BAK_G_P;	

GAMENn_HEAD_st	GAMENn_HEAD;
DISP_INFO_st	DISP_INFO;

UNl		CHR_TABLE_ADR;			// キャラクタテーブルの文字列キャラクタ先頭アドレス
UNl		CSR_TABLE_ADR;			// キャラクタテーブルのカーソルキャラクタ先頭アドレス
UNl		SWL_TABLE_ADR;			// キャラクタテーブルのＳＷ−ＬＡＭＰキャラクタ先頭アドレス
UNl		S56_TABLE_ADR;			// キャラクタテーブルのＳＷ５・６下段キャラクタ先頭アドレス
UNl		MES_TABLE_ADR;			// キャラクタテーブルのメッセージキャラクタ先頭アドレス
UNl		S56U_TABLE_ADR;			// キャラクタテーブルのＳＷ５・６上段キャラクタ先頭アドレス
UNl		SPE_TABLE_ADR;			// キャラクタテーブルの特別キャラクタ先頭アドレス

UNl		GAMENN_MOJ_INF_ADR;		// 画面ｎの文字列情報の先頭アドレス			（画面ｎを表示するときに算出）
UNl		GAMENN_CSR_INF_ADR;		// 画面ｎのカーソル情報の先頭アドレス		（画面ｎを表示するときに算出）
UNl		GAMENN_SVP_INF_ADR;		// 画面ｎの設定値情報の先頭アドレス			（画面ｎを表示するときに算出）
UNl		GAMENN_PVP_INF_ADR;		// 画面ｎの実測値情報の先頭アドレス			（画面ｎを表示するときに算出）
UNl		GAMENN_SWL_INF_ADR;		// 画面ｎのＳＷ−ＬＡＭＰの先頭アドレス		（画面ｎを表示するときに算出）
UNl		GAMENN_GRP_INF_ADR;		// 画面ｎのグラフィック情報の先頭アドレス	（画面ｎを表示するときに算出）

UNs		CHRTBL_CHR_CNT;			// キャラクタテーブルの文字列キャラクタ個数
UNs		CHRTBL_CSR_CNT;			// キャラクタテーブルのカーソルキャラクタ個数
UNs		CHRTBL_SWL_CNT;			// キャラクタテーブルのＳＷ−ＬＡＭＰキャラクタ個数
UNs		CHRTBL_S56_CNT;			// キャラクタテーブルのＳＷ５・６下段キャラクタ個数
UNs		CHRTBL_MES_CNT;			// キャラクタテーブルのメッセージキャラクタ個数
UNs		CHRTBL_S56U_CNT;		// キャラクタテーブルのＳＷ５・６下段キャラクタ個数
UNs		CHRTBL_SPE_CNT;			// キャラクタテーブルの特別キャラクタ個数

UNs		GAMENn_SCR_COL;			//画面のｽｸﾘｰﾝ色（Windowを表示して変わらないこと）

UNs		PVW_ZURE_PLS_SIN;		//軸間ｽﾞﾚ実測符号
UNs		PVW_ZURE_RNA_SIN;		//軸間ｽﾞﾚﾘﾆｱ符号
UNs		PVW_ZURE_PLS;			//軸間ｽﾞﾚ実測
UNs		PVW_ZURE_RNA;			//軸間ｽﾞﾚﾘﾆｱ
UNs		PVW_BAKORG_SIN1;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
UNs		PVW_BAKORG_SIN2;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
UNl		SVBW_BAKORG_PLS1;		//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2
UNl		SVBW_BAKORG_PLS2;		//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2

UNs		GAM_CHG_WIN_NO_BAK;		/* V04a */

UNb		OP_STATUS;				//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H		//V01e
UNb		OP_STATUS_DUM;			//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H		//V01e

UNb		MEM_ARI;				//DB	?		; OPｱﾘ:A5H		//V05h

UNs		PV0_CB_C_VER[6];		//ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
UNs		PV0_PAR_C_CHAR;			//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
UNs		PV0_TBL_C_CHAR;			//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)

//;	******** 2007/12/12 ***********
UNs		PV0_IPM_ADR0;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
UNs		PV0_IPM_ADR1;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
UNs		PV0_IPM_ADR2;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
UNs		PV0_IPM_ADR3;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)

//;	******** 2009/07/14 ***********
UNs		IROCK_OUT_NO[8];			/* ｲﾝﾀｰﾛｯｸ発生番号		*/
UNb		IROCK_CHAR[8][8];			/* ｲﾝﾀｰﾛｯｸ発生番号に対するｷｬﾗｸﾀ文字		*/

//;	******** 2009/08/-- *********** V05o(INS)	実測波形表示用
UNs		WAVE_SAMP_DTP[2];					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ		+0:最新  +1:前回値
UNs		WAVE_TRND_DTP[2];					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ		+0:最新  +1:前回値
WAVE_SAMP_DATA_ST	WAVE_SAMP_DATA[501];	//実測ｻﾝﾌﾟﾘﾝｸﾞ波形用ﾃﾞｰﾀ
WAVE_TRND_DATA_ST	WAVE_TRND_DATA[5001];	//実測ﾄﾚﾝﾄﾞ波形用ﾃﾞｰﾀ
WAVE_SAMP_DOT_ST	WAVE_SAMP_DOT[501];		//実測ｻﾝﾌﾟﾘﾝｸﾞ波形用ﾃﾞｰﾀ
WAVE_TRND_DOT_ST	WAVE_TRND_DOT[5001];	//実測ﾄﾚﾝﾄﾞ波形用ﾃﾞｰﾀ
UNs		CSR_PVSAMP[2];						//実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面のｶｰｿﾙ位置	+0:最新  +1:前回値
UNs		CSR_PVTRND[2];						//実測ﾄﾚﾝﾄﾞ波形画面のｶｰｿﾙ位置		+0:最新  +1:前回値
UNs		PW_Key_up[4];						//実測波形画面用ｷｰ立上り変化	(5ms割込みで監視)
UNs		PW_Key_dn[4];						//実測波形画面用ｷｰ立下り変化	(5ms割込みで監視)
UNs		PW_Key_last[4];						//実測波形画面用ｷｰ前回値		(5ms割込みで監視)
UNs		PW_Key_tim02[4];					//実測波形画面用ｷｰ長押し時間	(5ms割込みで監視)
UNs		PW_Key_tim30[4];					//実測波形画面用ｷｰ長押し時間	(5ms割込みで監視)
UNs		PV0_SMPCSR_KJT;						//ｶｰｿﾙ位置の合計荷重
UNs		PV0_SMPCSR_KJL;						//ｶｰｿﾙ位置の左荷重
UNs		PV0_SMPCSR_KJR;						//ｶｰｿﾙ位置の右荷重
UNs		PV0_SMPCSR_AGL;						//ｶｰｿﾙ位置の角度
UNl		PV0_SMPCSR_RNA1;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
UNl		PV0_SMPCSR_RNA2;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
UNs		PV0_SMPCSR_SEQ0;					//ｶｰｿﾙ位置のｼｰｹﾝｽ
UNs		PV0_SMPCSR_SEQ1;					//ｶｰｿﾙ位置のｼｰｹﾝｽ
UNs		PV0_SMPCSR_TIM;						//ｶｰｿﾙ位置の時間
UNs		PV0_SMPCSR_POS;						//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ
UNl		PV0_TRDCSR_RNAU;					//ｽﾗｲﾄﾞ上限検出位置
UNl		PV0_TRDCSR_RNAD;					//ｽﾗｲﾄﾞ下限検出位置
UNs		PV0_TRDCSR_KJT;						//ｶｰｿﾙ位置の合計荷重
UNs		PV0_TRDCSR_KJL;						//ｶｰｿﾙ位置の左荷重
UNs		PV0_TRDCSR_KJR;						//ｶｰｿﾙ位置の右荷重
UNl		PV0_TRDCSR_RNA1;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
UNl		PV0_TRDCSR_RNA2;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
UNs		PV0_TRDCSR_TIM;						//ｶｰｿﾙ位置の時間
UNs		PV0_TRDCSR_POS;						//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ
UNs		PV0_TRDCSR_POSL;					//ｶ-ｿﾙ範囲
UNs		PV0_TRDCSR_POSR;					//ｶ-ｿﾙ範囲

//;	******** 2010/08/10~ *********** V05r(INS)
UNs		SEIDOU_SEQ_LST;						//
UNs		sys_1min_cnt;						//1minｶｳﾝﾀ
//UNs		PVTIM_seidouseinou_inter;			//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ(1minﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)
//UNs		PVTIM_seidouseinou_yokok;			//制動性能試験予告ﾀｲﾏ(1minﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)
UNs		SYO_HOS_KAJ_CNT;
UNs		PV0_INTER_TIM;						//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ(1hﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)

//;	******** 2010/08/31~ *********** V06 (INS)
UNl		INTR_DAT_OFS;
UNl		INIT_DAT_OFS;
UNl		ALL_CHR_TBL_OFS;
UNl		GAM_INF_TBL_OFS;
UNs		EcoMeter_bit;
UNs		PV0_EPMCSR_HOR;						//電力モニタカーソル位置の時間
UNs		PV0_EPMCSR_MIN;						//電力モニタカーソル位置の分
UNl		PV0_EPMCSR_UEP;						//電力モニタカーソル位置の消費電力量
UNl		PV0_EPMCSR_KEP;						//電力モニタカーソル位置の回生電力量
UNl		PV0_EPMCSR_TEP;						//電力モニタカーソル位置の累計値
UNl		PV0_EPML_SCRH;						//電力モニタグラフ左上メモリ
UNl		PV0_EPML_SCRM;						//電力モニタグラフ左中メモリ
UNl		PV0_EPML_SCRL;						//電力モニタグラフ左下メモリ
UNl		PV0_EPMR_SCRH;						//電力モニタグラフ右上メモリ
UNl		PV0_EPMR_SCRM;						//電力モニタグラフ右中メモリ
UNl		PV0_EPMR_SCRL;						//電力モニタグラフ右下メモリ
UNl		PV0_EPM_KWH[20][3];					//電力モニタ用グラフデータ
UNs		EPM_CSR[2];							//電力モニタ用カーソル位置
UNs		EPM_TIM_BAK;						//単位時間
UNl		EPM_GRP_MXL;						//棒グラフ最大値変わった？
UNl		EPM_GRP_MXR;						//折れ線グラフ最大値変わった？
UNs		sys_1sec_cnt;						//1secｶｳﾝﾀ

//UNl		EPM_SEC_60ADD[2];					//消費電力量 60sec積算(kWs)
//UNs		EPM_SEC_60CNT;
//UNl		EPM_HOR_BUF[24*60][2];				//消費電力量 1440分(kWs)
//UNs		EPM_HOR_POI;
UNs		EPM_GAMEN_RIF;						//電力モニタ画面リフレッシュフラグ

UNl		PV0_SMPCSR_EP;						//ｻﾝﾌﾟﾘﾝｸﾞ波形画面ｶｰｿﾙ位置の瞬時電力
int		PV0_SMPCSR_EP_SIN;					//ｻﾝﾌﾟﾘﾝｸﾞ波形画面ｶｰｿﾙ位置の瞬時電力		//V06a
UNl		PV0_TRDCSR_EP;						//ﾄﾚﾝﾄﾞ波形画面   ｶｰｿﾙ位置の電力量

UNs		SEIDOU_DSP_LST;

UNs		PV0_INTER_VER1;						/* ｲﾝﾀｰﾛｯｸﾊﾞｰｼﾞｮﾝ 数値 */
UNs		PV0_DEFULT_VER1;					/* 初期値ﾃﾞｰﾀﾊﾞｰｼﾞｮﾝ 数値 */

UNs		PV0_EPMDAT_SIN;						//ｻﾝﾌﾟﾘﾝｸﾞ波形画面の電力値符号BIT			//V06a
UNs		EPM_TOTAL_INF;						//電力ﾓﾆﾀ画面累計値切替の表示情報			//V06a
UNs		EPM_TLINF_BAK;						//電力ﾓﾆﾀ画面累計値切替の表示情報			//V06a
UNs		EPM_CLR_TIM;						//電力ﾓﾆﾀ内部ﾃﾞｰﾀｸﾘｱﾀｲﾑ						//V06a
UNs		EPM_CLR_FLG;						//電力ﾓﾆﾀｸﾘｱ受付ﾌﾗｸﾞ						//V06a
UNs		EPM_GAMRIF_CNT;						//電力ﾓﾆﾀ画面ﾘﾌﾚｯｼｭﾀｲﾐﾝｸﾞｶﾝｳﾀ				//V06a

UNs		SV0_EP_AVE;


UNl		EPM_SEC_2_MESMIN_ADD[2];
UNs		EPM_SEC_MESMIN_CNT;

//V06b	UNl		EPM_05MIN_BUF[5/5][2] ;
//////	UNl		EPM_10MIN_BUF[10/5][2];
//////	UNl		EPM_15MIN_BUF[15/5][2];
//////	UNl		EPM_20MIN_BUF[20/5][2];
//////	UNl		EPM_25MIN_BUF[25/5][2];
//////	UNl		EPM_30MIN_BUF[30/5][2];
//////	UNl		EPM_35MIN_BUF[35/5][2];
//////	UNl		EPM_40MIN_BUF[40/5][2];
//////	UNl		EPM_45MIN_BUF[45/5][2];
//////	UNl		EPM_50MIN_BUF[50/5][2];
//////	UNl		EPM_55MIN_BUF[55/5][2];
//////	UNl		EPM_60MIN_BUF[60/5][2];
UNl		EPM_05MIN_BUF[5][2] ;
UNl		EPM_10MIN_BUF[10][2];
UNl		EPM_15MIN_BUF[15][2];
UNl		EPM_20MIN_BUF[20][2];
UNl		EPM_25MIN_BUF[25][2];
UNl		EPM_30MIN_BUF[30][2];
UNl		EPM_35MIN_BUF[35][2];
UNl		EPM_40MIN_BUF[40][2];
UNl		EPM_45MIN_BUF[45][2];
UNl		EPM_50MIN_BUF[50][2];
UNl		EPM_55MIN_BUF[55][2];
UNl		EPM_60MIN_BUF[60][2];

UNs		EPM_05MIN_POI;
UNs		EPM_10MIN_POI;
UNs		EPM_15MIN_POI;
UNs		EPM_20MIN_POI;
UNs		EPM_25MIN_POI;
UNs		EPM_30MIN_POI;
UNs		EPM_35MIN_POI;
UNs		EPM_40MIN_POI;
UNs		EPM_45MIN_POI;
UNs		EPM_50MIN_POI;
UNs		EPM_55MIN_POI;
UNs		EPM_60MIN_POI;

UNl		EPM_05MON_BUF[20][2];
UNl		EPM_10MON_BUF[20][2];
UNl		EPM_15MON_BUF[20][2];
UNl		EPM_20MON_BUF[20][2];
UNl		EPM_25MON_BUF[20][2];
UNl		EPM_30MON_BUF[20][2];
UNl		EPM_35MON_BUF[20][2];
UNl		EPM_40MON_BUF[20][2];
UNl		EPM_45MON_BUF[20][2];
UNl		EPM_50MON_BUF[20][2];
UNl		EPM_55MON_BUF[20][2];
UNl		EPM_60MON_BUF[20][2];

UNs		EPM_05MON_POI;
UNs		EPM_10MON_POI;
UNs		EPM_15MON_POI;
UNs		EPM_20MON_POI;
UNs		EPM_25MON_POI;
UNs		EPM_30MON_POI;
UNs		EPM_35MON_POI;
UNs		EPM_40MON_POI;
UNs		EPM_45MON_POI;
UNs		EPM_50MON_POI;
UNs		EPM_55MON_POI;
UNs		EPM_60MON_POI;

//;	******** 2010/12/06 *********** V06b (INS)
UNs		rulet_taiki_pos1;			//反転、振り子時の待機点
UNs		rulet_taiki_pos2;			//		振り子時の待機点
UNl		SV0_TAL1_CNT;				//ﾄｰﾀﾙｶｳﾝﾀ修正値
UNl		SV0_LOT1_CNT;				//ﾛｯﾄｶｳﾝﾀ1修正値
UNl		SV0_LOT2_CNT;				//ﾛｯﾄｶｳﾝﾀ2修正値

//;	******** 2011/01/02 *********** V06c (INS)
UNs		SV0_WORKER_COD_BAK	;		//作業者ｺｰﾄﾞ退避
UNl		SV0_ORDER_COD_BAK	;		//注番ｺｰﾄﾞ退避
UNl		SV0_PLAN_CNT_BAK	;		//計画数退避
UNs		SV0_WORKER_COD		;		//作業者ｺｰﾄﾞ
UNl		SV0_ORDER_COD		;		//注番ｺｰﾄﾞ
UNl		SV0_PLAN_CNT		;		//計画数

UNs		SV0_WORK_STR_FLG		;	//作業開始ﾌﾗｸﾞ（to C/B用）
UNs		SV0SP_WORKER_COD	;		//作業開始時作業者ｺｰﾄﾞ
UNl		SV0SP_ORDER_COD		;		//作業開始時注番ｺｰﾄﾞ
UNl		SV0SP_PLAN_CNT		;		//作業開始時計画数
UNl		SV0SP_BAD_CNT		;		//作業開始時不良数
UNs		SV0SP_KATA_NO		;		//作業開始時型番号
UNs		SV0SP_KATA_NAME[7]	;		//作業開始時型名称
UNs		SV0SP_KATA_MEMO[7]	;		//作業開始時型メモ

UNs		SV0_WORK_STP_FLG		;	//作業終了ﾌﾗｸﾞ（to C/B用）
UNs		SV0SR_WORKER_COD	;		//作業終了時作業者ｺｰﾄﾞ
UNl		SV0SR_ORDER_COD		;		//作業終了時注番ｺｰﾄﾞ
UNl		SV0SR_PLAN_CNT		;		//作業終了時計画数
UNl		SV0SR_BAD_CNT		;		//作業終了時不良数
UNs		SV0SR_KATA_NO		;		//作業終了時型番号
UNs		SV0SR_KATA_NAME[7]	;		//作業終了時型名称
UNs		SV0SR_KATA_MEMO[7]	;		//作業終了時型メモ

UNs		KAT_RD_CSR_POS	;			//型読出し時のCSR_TBL_POS_NOW

//;	******** 2012/09/24 *********** V06m (INS)
UNs		DIEH_OFS_FLG;
UNs		FURIKO_FLG;

//;	******** 2012/10/15 *********** V06n (INS)
UNl		SV0_RNAPOS_MAXO;
UNl		SV0_RNAPOS_MINO;
UNs		SV0_DAIHAI_LNG1O;
UNs		SV0_DAIHAI_LNG2O;
UNs		MOT_MODE_BAK;

//;	******** 2013/02/18 *********** V06p (INS)
UNs		PV0_CKSPD_OVBIT;
UNs		PV0_KATRD_BIT;
UNs		TEST_SEQ;
UNs		FURIKO_SEQ_LST;

//;	******** 2013/12/11 *********** SIT4-MC
UNb		*VRAM_Dst8;
UNs		*VRAM_Dst;
UNb		*VRAM_Src;
UNb		*VRAM_End;
UNs		GAM_COPY_FLG;
UNs		GAM_COPY_STS;

//;	******** 2014/02/06 *********** SIT4-MC
UNs		IROCK_COL_CHG_NO;

//;	******** 2014/03/13 *********** SIT4-MC
UNs		SMP_KAJ_MAX_SIN;
UNs		SMP_KAJ_MIN_SIN;
UNs		SMP_EP_MAX_SIN;
UNs		SMP_EP_MIN_SIN;
UNs		TRD_KAJ_MAX_SIN;
UNs		TRD_KAJ_MIN_SIN;
UNs		TRD_EP_MAX_SIN;
UNs		TRD_EP_MIN_SIN;
UNs		OVER_LOAD_SEL;
UNs		LOW_LIMIT_SEL;
UNs		SV0_OVLD_SEL;
UNs		SV0_LWLM_SEL;
UNs		MEM_KAJ_SEL;

//;	******** 2014/04/15 *********** SIT4-MC
UNs		PV0_CKAGL_OVBIT;

//;	******** 2014/06/04 *********** SIT4-MC
UNs		SLDTUN_RNA_SEL ;

//;	******** 2014/08/20 ***********
UNl		CAR_MICRO_KAJ_AREA;

//;	******** 2014/08/26 SIT4-MC ***********
UNl		SV0_RELE_POS	;			//リリース高さ
UNs		SV0_RELE_SNO0	;			//リリースカムオン行程
UNs		SV0_RELE_AGL0	;			//リリースカムオン角度
UNs		SV0_RELE_SNO1	;			//リリースカムオフ行程
UNs		SV0_RELE_AGL1	;			//リリースカムオフ角度
UNs		SV0_RELE_CAM	;			//リリースカム設定対象
UNl		SV0_SEND_POS	;			//送り高さ
UNs		SV0_SEND_SNO0	;			//送りカムオン行程
UNs		SV0_SEND_AGL0	;			//送りカムオン角度
UNs		SV0_SEND_SNO1	;			//送りカムオフ行程
UNs		SV0_SEND_AGL1	;			//送りカムオフ角度
UNs		SV0_SEND_CAM	;			//送りカム設定対象
UNs		SV0_TIMING_SNO0	;			//タイミングカムオン行程
UNs		SV0_TIMING_AGL0	;			//タイミングカムオン角度
UNs		SV0_TIMING_SNO1	;			//タイミングカムオフ行程
UNs		SV0_TIMING_AGL1	;			//タイミングカムオフ角度
UNs		SV0_TIMING_CAM	;			//タイミングカム設定対象
UNs		PV0_CAMATCAL_MES1;			//カム自動演算設定不可時のメッセージ番号
UNs		PV0_CAMATCAL_MES2;			//カム自動演算設定不可時のメッセージ番号
UNs		PV0_CAMATCAL_MES3;			//カム自動演算設定不可時のメッセージ番号
UNs		PV0_MOTION_INF;				//BIT0：ﾓｰｼｮﾝに停止行程がある。
									//BIT1：ﾓｰｼｮﾝに逆転行程がある。
UNs		PV0_SINKAKU_UPDN1;			//BITn：ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。
UNs		PV0_SINKAKU_UPDN2;			//BITn：ﾛｰﾀﾘｶﾑnのOFF進角が加減速範囲にある。

UNs		SV0_MOT_REP;				//モーションのリピート情報
UNs		SV0_MOT_FIX;				//モーションの一定領域情報
UNs		SV0_FIXARA_AGLS;			//一定領域　開始角度
UNl		SV0_FIXARA_POSS;			//一定領域　開始位置
UNs		SV0_FIXARA_SPDB;			//一定領域　開始前速度
UNs		SV0_FIXARA_SPDF;			//一定領域　一定速度
UNs		SV0_FIXARA_AGLE;			//一定領域　終了角度
UNl		SV0_FIXARA_POSE;			//一定領域　終了位置
UNs		PV0_FIXBF_SPD;				//一定領域　開始前速度

UNs		PV0_CAMATCAL_FLG;			//カム出力自動設定フラグクリア			2014/09/12

UNs		SV0_REP_FIX_FLG;			//繰り返し／一定領域  有効／無効ﾌﾗｸﾞ	2014/09/23
UNs		MOT_FERR_TIM;				//F挿入ERR信号ON時間					2014/09/25

UNs		PV0_FMOTSET_MES1;			//一定速度設定時のメッセージ番号		2014/10/09

//;	******** 2015/01/14 ***********
UNs		SV_1DANPRS_SRV;             /* 1段目目標荷重 */
UNs		SV_2DANPRS_SRV;             /* 2段目目標荷重 */
UNs		SV_3DANPRS_SRV;             /* 3段目目標荷重 */
UNs		SV_4DANPRS_SRV;             /* 4段目目標荷重 */
UNs		SV_5DANPRS_SRV;             /* 5段目目標荷重 */
UNs		SV_6DANPRS_SRV;             /* 6段目目標荷重 */
UNs		SV_7DANPRS_SRV;             /* 7段目目標荷重 */
UNs		SV_8DANPRS_SRV;             /* 8段目目標荷重 */
UNs		SV_9DANPRS_SRV;             /* 9段目目標荷重 */
UNs		SV_10DANPRS_SRV;            /* 10段目目標荷重 */
UNs		SV_KAJOBJ_HAB;				/* 荷重完了範囲 */

//;	******** 2015/01/20 ***********
UNs		TANNI_SEQ_LST;

//;	******** 2015/05/19 ***********
UNs		TRND_DTP_FLG;
UNs		chk_kjofs_dat[10];

//;	******** 2015/07/10 ***********
UNs		PV0_CKSPD_LMBIT;

//;	******** 機器交換画面の入力制限対応 ***********		2016/02/24
UNs		SV0_RNAORG_ENB1;				//機械原点入力（入力許可）
UNs		SV0_ORGCAL_ENB2;				//機番（入力許可）
UNs		SV0_ORGCAL_ENB1;				//機種（入力許可）
UNs		SV0_MACINE_ENB1;				//角度値切替（入力許可）
UNs		SV0_OFSET_ENB;					//ｵﾌｾｯﾄ調整（入力許可）
UNs		SV0_KOUSEI_ENB;					//荷重校正（入力許可）
UNs		SV0_MAXHIZ_ENB;					//最大歪（入力許可）
UNs		SV0_MAXKAJ_ENB;					//最大荷重（入力許可）
UNs		SV0_KOUKAJ_ENB;					//校正荷重（入力許可）

//;	******** 周辺機連動機能追加仕様 ***********		2016/04/22
UNs		SQ_ORIDE_BAK;
UNs		TLINK_NEXT_LAST;
UNs		TLINK_NEXT_LAST1;
UNs		TLINK_NEXT_NO;
UNs		ADC_SW5_ON_FLG;
UNs		ADC_SW6_ON_FLG;

/***	END		***/
