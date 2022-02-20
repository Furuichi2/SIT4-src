
/* 外部参照変数定義 -------------------------------------------------- */
/*==========================================================================*/
/*		テスト用の仮定義													*/
/*==========================================================================*/
//extern	UNs		OP_STATUS_DT;			//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H

/*==========================================================================*/
/*		新ワーク領域定義（Sit-S）											*/
/*==========================================================================*/
extern	UNi		SVPV_LCD_FLG;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
extern	UNs		SV_DANSUU_SRV_BAK;				//工程数 セーブ
//extern	UNs		SV_TAIKIKAKU_SRV_BAK;			//待機角の格納
//extern	UNl		SV_TAIKIPOS_SRV_BAK;			//待機位置の格納

extern	UNl		SV_TAIKIPOS_SRV;            /* 待機位置 */
extern	UNs		SV_KAITEN_SRV;              /* 回転方式 */
extern	UNs		SV_DANSUU_SRV;              /* 段数 */
extern	UNs		SV_TAIKIKAKU_SRV;           /* 待機角 */
extern	UNs		SV_TAIKSPD_SRV;             /* 基準速度 */
extern	UNl		SV_DAIHAITO_SRV;            /* ダイハイト */
extern	UNs		SV_HOASEI_SRV;              /* 補正データ */
extern	UNs		SV_TAIKTIM_SRV;             /* 待機時間 */
extern	UNs		SV_1DANDEG_SRV;             /* 1段目目標角度 */
extern	UNs		SV_2DANDEG_SRV;             /* 2段目目標角度 */
extern	UNs		SV_3DANDEG_SRV;             /* 3段目目標角度 */
extern	UNs		SV_4DANDEG_SRV;             /* 4段目目標角度 */
extern	UNs		SV_5DANDEG_SRV;             /* 5段目目標角度 */
extern	UNs		SV_6DANDEG_SRV;             /* 6段目目標角度 */
extern	UNs		SV_7DANDEG_SRV;             /* 7段目目標角度 */
extern	UNs		SV_8DANDEG_SRV;             /* 8段目目標角度 */
extern	UNs		SV_9DANDEG_SRV;             /* 9段目目標角度 */
extern	UNs		SV_10DANDEG_SRV;            /* 10段目目標角度 */
extern	UNl		SV_1DANPOS_SRV;             /* 1段目目標位置 */
extern	UNl		SV_2DANPOS_SRV;             /* 2段目目標位置 */
extern	UNl		SV_3DANPOS_SRV;             /* 3段目目標位置 */
extern	UNl		SV_4DANPOS_SRV;             /* 4段目目標位置 */
extern	UNl		SV_5DANPOS_SRV;             /* 5段目目標位置 */
extern	UNl		SV_6DANPOS_SRV;             /* 6段目目標位置 */
extern	UNl		SV_7DANPOS_SRV;             /* 7段目目標位置 */
extern	UNl		SV_8DANPOS_SRV;             /* 8段目目標位置 */
extern	UNl		SV_9DANPOS_SRV;             /* 9段目目標位置 */
extern	UNl		SV_10DANPOS_SRV;            /* 10段目目標位置 */
extern	UNs		SV_1DANSPD_SRV;             /* 1段目移動速度 */
extern	UNs		SV_2DANSPD_SRV;             /* 2段目移動速度 */
extern	UNs		SV_3DANSPD_SRV;             /* 3段目移動速度 */
extern	UNs		SV_4DANSPD_SRV;             /* 4段目移動速度 */
extern	UNs		SV_5DANSPD_SRV;             /* 5段目移動速度 */
extern	UNs		SV_6DANSPD_SRV;             /* 6段目移動速度 */
extern	UNs		SV_7DANSPD_SRV;             /* 7段目移動速度 */
extern	UNs		SV_8DANSPD_SRV;             /* 8段目移動速度 */
extern	UNs		SV_9DANSPD_SRV;             /* 9段目移動速度 */
extern	UNs		SV_10DANSPD_SRV;            /* 10段目移動速度 */
extern	UNs		SV_1DANTIM_SRV;             /* 1段目停止時間 */
extern	UNs		SV_2DANTIM_SRV;             /* 2段目停止時間 */
extern	UNs		SV_3DANTIM_SRV;             /* 3段目停止時間 */
extern	UNs		SV_4DANTIM_SRV;             /* 4段目停止時間 */
extern	UNs		SV_5DANTIM_SRV;             /* 5段目停止時間 */
extern	UNs		SV_6DANTIM_SRV;             /* 6段目停止時間 */
extern	UNs		SV_7DANTIM_SRV;             /* 7段目停止時間 */
extern	UNs		SV_8DANTIM_SRV;             /* 8段目停止時間 */
extern	UNs		SV_9DANTIM_SRV;             /* 9段目停止時間 */
extern	UNs		SV_10DANTIM_SRV;            /* 10段目停止時間 */
//extern	UNs		SV_CYCTIM_SRV;              /* サイクルタイム */
//extern	UNs		SV_TAIKAN_SRV;              /* 待機完了範囲 */
extern	UNs		SV_MOKKAN_SRV;              /* 目標完了範囲 */
extern	UNs		SV_KAJYUU_PRS;				/* 荷重補正 V01m*/
extern	UNs		SV_KAJYUU_OBJP;				/* 荷重目標 V01m*/

extern	UNs		disp_stg, disp_stg_sel;
extern	UNl		language_chg;

extern	UNs		PV_STPTIM_B2;					/* ssc_tbl.c にて使用		*/

//extern	UNs		PV_KOUTEI1_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI2_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI3_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI4_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI5_NO;					/*                      	*/

extern	UNs		PV_CAMNA1_C1;					/*                      	*/

extern	UNs		PV_STPTM_OLD;					/*                      	*/
extern	UNs		PV_MLNO01_C15;					/*                      	*/
extern	UNs		PV_MLNO02_C15;					/*                      	*/
extern	UNs		PV_MLNO03_C15;					/*                      	*/
extern	UNs		PV_MLNO04_C15;					/*                      	*/
extern	UNs		PV_MLNO05_C15;					/*                      	*/
extern	UNs		PV_MLNO06_C15;					/*                      	*/
extern	UNs		PV_MLNO07_C15;					/*                      	*/
extern	UNs		PV_MLNO08_C15;					/*                      	*/
extern	UNs		PV_MLNO09_C15;					/*                      	*/
extern	UNs		PV_MLNO10_C15;					/*                      	*/

extern	UNs		PV_MLDNO2_F11[8];		//DB 16 DUP(?)	;	/* V01j */

//extern	UNl		PVB_RNAORG_PLS1;				/*							*/
//extern	UNl		SV_GENITI_CHK;

extern	UNs		PV_CAMNA1_C1;					/*                      	*/
extern	UNs		PV_MLDMES_C1;					/*							*/
extern	UNs		PV_OFFSET_A1;					/*                      	*/
extern	UNs		PV_DATINI_A1;					/*                      	*/
extern	UNs		PV_KAJYUU_A1;					/*                      	*/
extern	UNs		PV_GAIBU_A1;					/*                      	*/
extern	UNs		PV_BACKDA_A1;					/*                      	*/

extern	UNs		TAIKI_ZEN_MOD;					/* ルーレット前回描画方向	*/
extern	UNs		TAIKITEN_DIRECT;				/* 待機点データ（クラッチ）	*/

extern	UNs		SEISAN_DISP_FLG;				// 生産行程表示	 (00:なし／FF:あり)
extern	UNs		INTROCK_DISP_FLG;				// ガイダンス表示(00:なし／FF:あり)

extern	UNs		IROCK_NO	 [];				/* ｲﾝﾀｰﾛｯｸ表示番号列		*/
extern	UNs		IROCK_NO_LAST[];				/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/

/*==========================================================================*/
/*		キー入力用のワーク領域定義											*/
/*==========================================================================*/
//extern	UNs		KEY_DATA_FLG;				/* Ｋｅｙデータありフラグ */
//extern	UNs		KEY_DATA_NO[4];				/* ＫｅｙデータＮｏ．フラグ */
extern	UNs		KEY_DATA_CODE, KEY_DATA_MODE;
extern	UNs		Key_up[4],Key_dn[4],Key_last[4];

/*==========================================================================*/
/*		旧ワーク領域定義(Sit-2より)											*/
/*==========================================================================*/
/***	表示用のワーク領域定義		***/
extern	UNs		GAMEN_NO;					//DW ?	;/* 画面コード */
extern	UNs		GAMEN_CODE;					//DB ?	;/* 画面コード */
extern	UNs		WINDOW_NO;					//DW ?	;/* 画面コード */
extern	UNs		CSR_FLG;					//DB ?	;/* カーソル有り画面フラグ */

extern	UNs		CSR_CNT;					/* カーソルカウンタ */
extern	UNs		CSR_CNT1;					/* カーソルカウンタ */
extern	UNs		SV_CNT;						/* 設定値カウンタ */
extern	UNs		PV_CNT;						/* 実測値カウンタ */
extern	UNs		SW_CNT;						/* ＳＷデータカウンタ */
extern	UNs		SW_CNT1;					/* ＳＷデータカウンタ */

extern	CSR_TBL_TDEF	CSR_buff[110];		/* カーソル情報テーブル定義領域	*/
extern	SV_TBL_TDEF		SV_buff[100];		/* 設定値情報テーブル定義領域	*/
extern	PV_TBL_TDEF		PV_buff[40];		/* 実測値情報テーブル定義領域	*/
extern	SW_TBL_TDEF		SW_buff[40];		/* ＳＷデータ情報テーブル定義領域	*/

extern	UNs		PV_DISP_CNT;				/* 表示実測値カウンタ */
extern	UNs		SW_DISP_CNT;				//次回表示ＳＷデータカウンタ

extern	UNs		LCD_WORK1[15][16][40];		/* 表示ﾜｰｸ領域LCD1[何行何ﾄﾞｯﾄ目何文字目] */
extern	UNs		LCD_WORK2[15][16][40];		/* 表示ﾜｰｸ領域LCD2[何行何ﾄﾞｯﾄ目何文字目] */
extern	UNs		LCD_WORK3[15][16][40];		/* 表示ﾜｰｸ領域LCD3[何行何ﾄﾞｯﾄ目何文字目] */ /* V01  */

extern	UNs		CSR_FLG_CNT;				//DW ?	;/* 現在のカーソル位置カウント */
extern	UNs		SV_FLG_CNT;					//DW ?	;/* 初期値セット */
extern	UNs		SW_FLG_CNT;					//DW ?	;/* 初期値セット */

extern	UNs		CSR_POS;					//DW ?	;/* カーソルポジションデータ読込 */
extern	UNs		CSR_POS_LAST;				//DW ?	;/* 前回カーソルポジションデータ読込 */
extern	UNs		CSR_ON_FLG;					//DB ?	;/* カーソル表示フラグＯＮ */

extern	UNs		SWDATA_DISP_CNT;			//DW ?	;/* ＳＷデータ表示用ループカウント */
extern	UNs		SVSW_CHG_FLG;				//DB ?	;/* データチェンジフラグセット */

extern	UNl		SV_DISP_BUFF;				//DB 20 DUP(?)	;/* 設定値中間バッファ（ＡＳＣＩＩ） */
extern	UNs		SV_DATA_CHG;				//DB ?	;//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
extern	UNs		CSR_TBL_POS_NOW;			//DW ?	;/* カーソル現在位置アドレス */
extern	UNs		SV_TBL_POS_NOW;				//DW ?	;/* カーソル現在位置アドレス */
extern	UNs		SW_TBL_POS_NOW;				//DW ?	;/* カーソル現在位置アドレス */
extern	UNs		DISP_CHG_FLG;				//DB ?	;/* 表示反転フラグセット */

extern	UNs		SV_DISP_CNT;				//DB ?	;/* 設定値表示個数＝入力処理個数 */
extern	UNs		SV_ENT_CNT;					//DB ?
extern	UNs		TENKEY_CNT;					//DB ?	;/* 入力オーバー？ */
extern	UNs		NO_SUPRESU;					//DB ?
extern	UNs		INTER_ROCK_FLG;				//DB ?	;/* インターロック有り？ */
extern	UNs		PATH_WORD_CNT;				//DB ?		;

extern	UNs		SEI_INF_BUFF[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
extern	UNs		SEI_INF_BUFF1[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
extern	UNs		SEI_INF_BUFF2[280];			//DW 280H DUP(?)	;/* データ格納アドレス */
extern	UNs		SEI_WRT_POS;				//DW ?	;/* 表示位置 */
extern	UNs		SEI_WRT_CNT;				//DW ?		;/* 表示文字数 */
extern	UNs		SEI_WRT_ADR;				//DW ?		;/* 表示文字数 */
extern	UNs		IROCK_BUFF[40];				//DW 40 DUP(?)	;
extern	UNs		IROCK_BUFF01[320/2];		//DB 320 DUP(?)	;
extern	UNs		SEI_INF_FLG;				//DB ?
extern	UNs		SEI_INF_FLG_LAST;			//DB ?		;

extern	UNs		GAMEN_WRITE_CNT;			//DB ?		;
extern	UNs		SEQ_044_WORK[30/2];				//DB 30 DUP(?)	;

extern	UNs		IROC_CHG_FLG;				//DW ?	;
extern	UNs		IROC_CHG_FLG1;				//DW ?	;
extern	UNs		IL_DISP_LAST;				//DB ?
extern	UNs		GAMEN_NO_IROCK;				//DW ?
extern	UNs		SEISAN_FLG;					//DB ?	;
extern	UNs		SEISAN_FLG_LAST;			//DB ?	;
extern	UNs		IROCK_SHR_LAST;				//DB ?
extern	UNs		SVPV_DATA_FLG;				//DB ?
extern	UNs		SOUSA_LEFT_FLG;				//DB ?
extern	UNs		ERR_MONI_LAST1;				//DW ?
extern	UNs		ERR_MONI_LAST2;				//DW ?
extern	UNs		ERR_MONI_LAST3;				//DW ?
extern	UNs		DAN_SOUSA_DAT;				//DW ?
extern	UNs		RULET_DIG_TBL_ADR;			//DW ?
extern	UNs		SEI_COUNT_LAST1;			//DB ?;
extern	UNs		SEI_COUNT_LAST2;			//DB ?;
extern	UNs		SEI_COUNT_LAST3;			//DB ?;
extern	UNs		SEI_COUNT_LAST4;			//DB ?;

extern	UNs		GAMEN_ON_FLG;				//DB ?
extern	UNs		IL_DISP_FLG;				//DB ?		;/* ＩＬ表示フラグリセット */
extern	UNs		INI_FLG	;					//DB ?
extern	UNs		SEQ_018_SV_BUFF;			//DB ?
extern	UNs		BASE_CLS_CNT;				//DW ?
extern	UNs		SEI_INF_SPATH_CNT;			//DW ?
extern	UNs		SUM_CHK_ERR;				//DB ?
extern	UNs		DAN_NON_GAMEN;				//DB ?
extern	UNs		SV_CHK_ERR;					//DB ?
extern	UNs		SV_CMP_ERR;					//DB ?
extern	UNs		SV_SUM1_ERR;				//DB ?
extern	UNs		SV_SUM2_ERR;				//DB ?
extern	UNs		SV_DPRAM_ERR;				//DB ?

extern	UNs		INCH_DATA_FLG;				//DB ?	;/* INCH処理フラグ */

extern	UNs		OP_MESS_DISP_LAST1;			//DB ?	;
extern	UNs		OP_MESS_DISP_LAST2;			//DB ?	;
extern	UNs		OP_MESS_DISP_LAST3;			//DB ?	;

extern	UNs		OFF_SET_MNG_LAST;			//DB ?	;
extern	UNs		OFF_SET_MNG_LAST1;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST1;			//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST;			//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST1;		//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST2;		//DB ?	;

extern	UNs		SEIGAMEN_CNT;				//DB ?	;
extern	UNs		SEGAMEN_ADR;				//DW ?	;

extern	UNs		OFF_SET_MNG_LAST2;			//DB ?	;
extern	UNs		OFF_SET_MNG_LAST3;			//DB ?	;
extern	UNs		OFF_SET_MNG_LASTX;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST2;			//DB ?	;
extern	UNs		YOUBI_LAST;					//DB ?

extern	UNs		PODATA_SET_FLG;				//DB ?	;

extern	UNs		ONOFF_FLG;					//DB ?	;
extern	UNs		ONOFF_LAST1;				//DB ?	;
extern	UNs		ONOFF_LAST2;				//DB ?	;
extern	UNs		ONOFF_LAST3;				//DB ?	;
extern	UNs		ONOFF_LAST4;				//DB ?	;
extern	UNs		ONOFF_LAST5;				//DB ?	;
extern	UNs		ONOFF_LAST6;				//DB ?	;
//extern	UNs		ONOFF_LAST7;				//DB ?	;
//extern	UNs		ONOFF_LAST8;				//DB ?	;
//extern	UNs		ONOFF_LAST9;				//DB ?	;
//extern	UNs		ONOFF_LAST10;				//DB ?	;

extern	UNs		GAMEN_B6_NON_FLG;			//DB ?	;

extern	UNs		INI_POS_ERR_FLG;			//DB ?	;

extern	UNs		PV_ADBAKD_A14;				//DW ?	;

extern	UNs		ENCO_DATA_BCD;				//DW ?	;
extern	UNs		ENCO_DATA_HEX;				//DW ?	;

extern	UNs		OFFSET_END_FLG;				//DB ?	;/* オフセット調整完了？ */

extern	UNs		MCN_SEQ_LAST1;				//DB ?		;
extern	UNs		MCN_SEQ_LAST2;				//DB ?		;
extern	UNs		MCN_SEQ_LAST3;				//DB ?		;
extern	UNs		MCN_SEQ_LAST4;				//DB ?		;
extern	UNs		MCN_SEQ_LAST5;				//DB ?		;

extern	UNs		MCN_DATA_NO1;				//DB ?		;
extern	UNs		MCN_DATA_NO2;				//DB ?		;
extern	UNs		MCN_DATA_NO3;				//DB ?		;
extern	UNs		MCN_DATA_NO4;				//DB ?		;
extern	UNs		MCN_DATA_NO5;				//DB ?		;

extern	UNs		MCN_REC_FLG;				//DB ?		;

//extern	UNs		GAMEN_DISP_FLG;				//DB ?	;
extern	UNs		GGAMEN_DISP_FLG;			//DB ?	;

extern	UNs		CARA_CHG_FLG;				//DB ?	;
extern	UNs		YOKOBAI_CNT;				//DW ?	;/* 横倍カウンタ */
extern	UNs		YOKOBAI_ADR;				//DW ?	;/* 横倍アドレス */
extern	UNs		YOKO_BAI_WORK[32*16];		//DB 32*16 DUP(?)	;/* データをワーク領域へ転送 */

extern	UNs		KAN_BANK_NO;				//DB ?		;V05

extern	UNs		GENGO_CHG_LAST;				//DB ?		;
//extern	UNs		GENGO_CHG_LAST1;			//DB ?		;
extern	UNs		WORK_BUFF_NAME[20];			//DW 20 DUP(?);

extern	UNs		BASE_WORK;					//DW ?		;

extern	UNs		KT_DUMMY_01;				//DW ?	;
extern	UNs		KT_DUMMY_02;				//DB ?	;

extern	UNs		DAI_SVDATA_FLG;				//DB ?	;/* ダイハイト処理有効？ */
extern	UNs		SEQ_023_WK;					//DB ?	;

extern	UNs		AUTO_SEQ_LST;				//DB ?	;

extern	UNs		SV_0401_FLG;				//DB 	?	;
extern	UNs		SV_1101_FLG;				//DB ?	;
extern	UNs		SW_1101_FLG;				//DB ?	;
extern	UNs		SW_1102_FLG;				//DB ?	;
extern	UNs		SW_1103_FLG;				//DB ?	;

extern	UNs		CSR_MLD_WORK[32/2];			//DB 32 DUP(?)	;/* カーソルを移動すると文字の */

extern	UNs		SIT_MOLD3_RCV_BUFF[50];		//DW	50	DUP(?)	;

extern	UNs		TAIKITEN_DAT;				//DW ?	;/* 待機点だったらルーレットを再表示 */	EXTRN	TAIKITEN_DAT		: WORD	;/* 待機点だったらルーレットを再表示 */
extern	UNs		RULET_NOW_LST;				//DW ?	;
extern	UNs		DEG_DISP_LST;				//DW ?	;/* 角度ﾃﾞｰﾀ変化あり？ */
extern	UNl		DEG_DISP_DATA[2];			//DD	?	;
									//DD	?	;

extern	UNs		DEG_LCD_BUFF[32*12];		//DB 32*12 DUP(?)	;/* 角度表示専用バッファ */

extern	UNs		STOPTIME_DISP_LST;			//DW ?	;/* 角度ﾃﾞｰﾀ変化あり？ */
extern	UNl		STOPTIME_DISP_DATA[2];		//DD	?	;
									//DD	?	;

extern	UNs		STOPTIME_LCD_BUFF[32*12];	//DB 32*12 DUP(?)	;/* 角度表示専用バッファ */

extern	UNs		PFOUT_DATA_BAK;				//DB ?	;

extern	UNs		DAT_LCD_KAN_BAK;			//DB ?	;

extern	UNs		DEG_DISP_FLG;				//DB ?	;
//extern	UNs		STOP_DISP_FLG;				//DB ?	;
extern	UNs		RULET_DISP_FLG;				//DB ?	;/* ルーレット表示ＯＫ */
//extern	UNs		RULET_NON_FLG;				//DB ?	;
extern	UNs		CSR_MOVE_OK_FLG;			//DB ?	;/* カーソル移動禁止 */

extern	UNs		SW14_ON_FLG;				//DB ?	;
extern	UNs		SW14_ON_CNT;				//DB ?	;
extern	UNs		SET_KEY_LST;				//DB ?	;

extern	UNs		KIDO_FLG_FLG;				//DB 2 DUP(?)	;/* 輝度データ読込＆格納 */
extern	UNs		KIDO_FLG_PV;				//DB ?		;/* 輝度データ読込＆格納 */

extern	UNs		GAIBU_RST_LAST;				//DB ?	;
//extern	UNs		GAIBU_RST_LAST1;			//DB ?	;
extern	UNs		GAIBU_RST_LAST2;			//DB ?	;
extern	UNs		GAIBU_RST_LAST3;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST4;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST5;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST6;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST7;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST8;			//DB ?	;

//extern	UNs		GAIBU_CHG_FLG;				//DB ?	;

extern	UNs		TAIKITEN_FLG;				//DB ?	;
extern	UNs		TAIKITEN_LAST;				//DB ?
extern	UNs		TAIKITEN_DATA;				//DW ?
extern	UNs		TAIKI_NOW_POS;				//DW ?	;
extern	UNs		TAIKI_ZEN_POS;				//DW ?	;

extern	UNs		COUNT_HOSEI_ADR;			//DW ?	;/* 反転アドレスデータ待避 */
extern	UNs		SURA_HOSEI_ADR;				//DW ?	;/* 反転アドレスデータ待避 */

extern	UNs		SWCHG_DISP_ON_FLG;			//DB ?	;
extern	UNs		SEISAN_SW56_FLG;			//DB ?	;
extern	UNs		SEISAN_SW56_TIM;			//DW ?	;
extern	UNs		OPBAK_UP_LST;				//DB ?	;
extern	UNs		OPBAK_UP_LST1;				//DB ?	;

extern	UNs		SW14_ON1_FLG;				//DB ?	;
extern	UNs		SW14_ON6_FLG;				//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK2;			//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK3;			//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK;			//DB ?	;
extern	UNs		SW14_ON6_FLG_BAK;			//DB ?	;
extern	UNs		SW14_ON6_FLG_BACK;			//DB ?	;

extern	UNs		TAIKI_LST;					//DW ?	;

extern	UNs		CAMNAME_INP_CNT;			//DB ?	;
extern	UNs		NAME_CHG_FLG;				//DB ?	;/* 名称変更中？ */
extern	UNs		CAM_NAME_NO;				//DB ?	;/* 変更カム名称番号読込 */
extern	UNs		SUOERTH_BUFF[3];			//DW 3 DUP(?)	;

extern	UNs		CSR_FLG_CNT_BAK;			//DW ?	;/* 現在のカーソル位置カウント */
extern	UNs		CSR_FLG_CNT_BAK3;			//DW ?	;/* 現在のカーソル位置カウント */
extern	UNs		SV_FLG_CNT_BAK;				//DW ?	;/* 初期値セット */
extern	UNs		SW_FLG_CNT_BAK;				//DW ?	;/* 初期値セット */

extern	UNs		CAMOUT_MUSK;				//DW ?	;/* 汎用出力マスクビット */
extern	UNs		CAMOUT_BIT;					//DW ?	;/* 汎用出力ビット */

extern	UNs		GAMEN_NO_CAM;				//DW ?	;
extern	UNs		DAN_WIN_FLG;				//DB ?	;	V01j(ins)
extern	UNs		DAN_CSR_LST;				//DB ?	;

//extern	UNs		SW14_DISP7_NON;				//DB ?	;

extern	UNs		SET_SPM_LST;				//DB ?	;
extern	UNs		KATNAME_INP_CNT;			//DB ?	;/* 入力カウンター１ */

//extern	UNs		PV_MLDNO1_F0[16];			//DB 16 DUP(?)	;
extern	UNs		PV_MLDNO1_F0;				//DB 16 DUP(?)	;
extern	UNs		PV_MLDNO2_F0[16];			//DB 16 DUP(?)	;

extern	UNs		SINCAM_LST;					//DB ?	;	
extern	UNs		TAIKITEN_FLG_FLG;			//DB ?	;/* すでにフラグを立てていたらやめ */

extern	UNs		CSR_CLS_FLG;				//DB ?	;
extern	UNs		PVCNT_DISP_CNT;				//DB ?	;
extern	UNs		PVALL_FLG;					//DB ?	;
extern	UNs		PVGENNITI_FLG;				//DB ?	;

extern	UNs		CSR_FLG_BUF;				//DW ?	;/*  */
extern	UNs		SV_FLG_BUF;					//DW ?	;/*  */

extern	UNs		ENCO_DATA_HEX1;				//DW ?	;

extern	UNs		RULET_GAKU_FLG;				//DW ?	;
extern	UNs		RULET_GAKU_LST;				//DB ?	;

extern	UNs		SEI_ON6_LST1;				//DB ?	;
extern	UNs		SEI_ON6_LST2;				//DB ?	;
extern	UNs		SEI_ON6_LST3;				//DB ?	;
extern	UNs		SEI_ON6_LST4;				//DB ?	;
extern	UNs		SEI_ON1_LST;				//DB ?	;

extern	UNs		DAN_GAMEN_NON;				//DB ?	;
extern	UNs		SEL_GAMEN_NON;				//DB ?	;
extern	UNs		CAM_GAMEN_NON;				//DB ?	;
extern	UNs		EJE_GAMEN_NON;				//DB ?	;
extern	UNs		MIS_GAMEN_NON;				//DB ?	;
extern	UNs		ROT_GAMEN_NON;				//DB ?	;

extern	UNs		ROT1_GAMEN_NON;				//DB ?	;
extern	UNs		ROT2_GAMEN_NON;				//DB ?	;
extern	UNs		ROT3_GAMEN_NON;				//DB ?	;

extern	UNs		CSR_FLG_CNT_LST;			//DW ?	;/* カーソル番号セット */

extern	UNs		POWRE_OK_FLG;				//DW ?	;

extern	UNs		PVDATA_NON;					//DB ?	;

extern	UNs		CAR_ROM_SEG;				//DW ?	;

extern	UNs		PV_SUM_CHK;					//DW ?	;
extern	UNs		EE_SUM_CHK;					//DW ?	;

extern	UNs		POWER_DOWN_FLG;				//DB ?	;

extern	UNs		SW56_UPTOP_FLG;				//DB ?	;'98-08-05

//V01u	extern	UNs		KAT_DATCHG_FLG;				//DB ?	;
extern	UNs		KAT_DATCHG_FLG_DUMMY;				//DB ?	;
extern	UNs		KAT_CNTCHG_FLG;				//DB ?	;

extern	UNs		SW14_DISP7_DANNON;			//DB ?	;'98-08-31/*スライド以外ないときはジャンプ  */
//extern	UNs		OP_NON_FLG;					//DB ?	;

extern	UNs		SYS_HIGHSPM_B1;				//DW ?	;V01a
extern	UNs		SYS_LOWSPM_B1;				//DW ?	;V01a
extern	UNs		RULET_HIGH_FLG;				//DB ?	;/* 高速ルーレット描画フラグセット */
extern	UNs		RULET_HIGH_LST;				//DB ?	;
extern	UNs		CB1_SPMDAT_PVV;				//DW ?	;/* 読み込み */

extern	UNs		PV_TLINKSMP_DAT;			//DW ?	;V03j

extern	UNs		ENC_SPD_CNT;				//DW ?		;
extern	UNl		ENCSPD_ADD;					//DD	?		;
extern	UNs		ENCSPD_BF[20];				//DW	10	DUP (?)	;
									//DW	10	DUP (?)	;

extern	UNs		CSR_DAN_CSR_LST;			//DW ?		;V01a/* 段取り画面SW56ｼｰｹﾝｽｷｬﾝｾﾙ用 */

extern	UNs		SW56_MUSK_FLG;				//DW ?		;V01b

extern	UNs		MLD_100_GNO;				//DW ?		;MLD100/* 型管理画面番号初期化 */
//extern	UNs		MLD_100_NO;					//DW ?		;MLD100/* 型管理画面番号初期化 */
extern	UNs		MLD_100_FLG;				//DB ?		;MLD100/* 型管理フラグ初期化 */
//extern	UNs		MLD_100_CARD_FLG;			//DB ?		;MLD100/*  */

extern	UNs		MEM_ADR;					//DW ?	;
extern	UNs		MEM_BNK;					//DW ?	;
extern	UNs		MLD_WRITE_BNK;				//DB ?	;

extern	UNs		CSR_POS_G15;				//DB ?	;/*  */

extern	UNs		CSR_MOVE_NON;				//DB ?	;/* カーソルは動かない？ */

extern	UNs		MLD100_INI_FLG;				//DB ?	;

extern	UNs		DAN_DAN_FLG;				//DB ?	;

extern	UNs		CSR_FLG_CNT_BACK;			//DW ?		;
extern	UNs		WINDOW_NO_BACK;				//DW ? 		;

extern	UNs		DAN_KEY_FLG;				//DB ?		;

extern	UNs		G07_WIN_FLG;				//DB ?		;

extern	UNs		FILCK_CNT;					//DW ?			;
extern	UNs		FILCK_STEP1_FLG;			//DB ?			;
extern	UNs		FILCK_STEP2_FLG;			//DB ?			;
extern	UNs		FILCK_STEP3_FLG;			//DB ?			;

extern	UNs		NEXT_READ_NO;				//DW ?	;/* 次型番号設定値 */

extern	UNs		KEY_DOWN14_FLG;				//DB ?	;/* ＫＥＹ立ち下がりフラグリセット */
extern	UNs		SW14_MUSK_FLG;				//DW ?	;

extern	UNs		SW14_MUSK_FLG_SW2;			//DW ?	;

extern	UNs		CSR_G07_NO1;				//DW ?	;/* カーソル先頭位置と同じ？ */
extern	UNs		CSR_G07_NO2;				//DW ?	;/* カーソル先頭位置と同じ？ */

extern	UNs		SYS_SPMPM_B1P;				//DW ?	;
extern	UNs		SYS_SPMPM_B1M;				//DW ?	;

extern	UNs		SEQ_019_FLG;				//DB ?	;

extern	UNs		SYS_MISSEL_SV;				//DB ?		;

extern	UNs		SURA_SEL_LST;				//DB ?	;

extern	UNs		DAN_CLS_CNT;				//DW ?		;2000-07-04/* 表示した個数カウンタ */

extern	UNs		SEI_GAI_LST;				//DB ?
extern	UNs		GENG_SEQ_LST;				//DB ?
extern	UNs		NEXT_MLDSEQ_FLG;			//DB ?		;2001-08-07 /*シーケンス用次型データ読み込みフラグＯＮ*/

extern	UNs		PV_CAMSW1_C1[4];		//DB 8 DUP(?)	;BIT_1
extern	UNs		PV_CAMSW2_C1[4];		//DB 8 DUP(?)	;BIT_2
extern	UNs		PV_CAMSW3_C1[4];		//DB 8 DUP(?)	;BIT_3
extern	UNs		PV_CAMSW4_C1[4];		//DB 8 DUP(?)	;BIT_4
extern	UNs		PV_CAMSW5_C1[4];		//DB 8 DUP(?)	;BIT_5
extern	UNs		PV_CAMSW6_C1[4];		//DB 8 DUP(?)	;BIT_6
extern	UNs		PV_CAMSW7_C1[4];		//DB 8 DUP(?)	;BIT_7
extern	UNs		PV_CAMSW8_C1[4];		//DB 8 DUP(?)	;BIT_8
extern	UNs		PV_CAMSW9_C1[4];		//DB 8 DUP(?)	;BIT_9
extern	UNs		PV_CAMSWA_C1[4];		//DB 8 DUP(?)	;BIT_A
extern	UNs		PV_CAMSWB_C1[4];		//DB 8 DUP(?)	;BIT_B
extern	UNs		PV_CAMSWC_C1[4];		//DB 8 DUP(?)	;BIT_C
extern	UNs		PV_CAMSWD_C1[4];		//DB 8 DUP(?)	;BIT_D
extern	UNs		PV_CAMSWE_C1[4];		//DB 8 DUP(?)	;BIT_E
extern	UNs		PV_CAMSWF_C1[4];		//DB 8 DUP(?)	;BIT_F

extern	UNs		PV_CAMNA01_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１名称 */
extern	UNs		PV_CAMNA02_C1[4];		//DB 8 DUP(?)	;/* ロータリカム２名称 */
extern	UNs		PV_CAMNA03_C1[4];		//DB 8 DUP(?)	;/* ロータリカム３名称 */
extern	UNs		PV_CAMNA04_C1[4];		//DB 8 DUP(?)	;/* ロータリカム４名称 */
extern	UNs		PV_CAMNA05_C1[4];		//DB 8 DUP(?)	;/* ロータリカム５名称 */
extern	UNs		PV_CAMNA06_C1[4];		//DB 8 DUP(?)	;/* ロータリカム６名称 */
extern	UNs		PV_CAMNA07_C1[4];		//DB 8 DUP(?)	;/* ロータリカム７名称 */
extern	UNs		PV_CAMNA08_C1[4];		//DB 8 DUP(?)	;/* ロータリカム８名称 */
extern	UNs		PV_CAMNA09_C1[4];		//DB 8 DUP(?)	;/* ロータリカム９名称 */
extern	UNs		PV_CAMNA10_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１０名称 */
extern	UNs		PV_CAMNA11_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１１名称 */
extern	UNs		PV_CAMNA12_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１２名称 */
extern	UNs		PV_CAMNA13_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１３名称 */
extern	UNs		PV_CAMNA14_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１４名称 */
extern	UNs		PV_CAMNA15_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１５名称 */
extern	UNs		PV_CAMNA16_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１６名称 */
extern	UNs		PV_CAMNA17_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１７名称 */
extern	UNs		PV_CAMNA18_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１８名称 */
extern	UNs		PV_CAMNA19_C1[4];		//DB 8 DUP(?)	;/* ロータリカム１９名称 */
extern	UNs		PV_CAMNA20_C1[4];		//DB 8 DUP(?)	;/* ロータリカム２０名称 */

extern	UNs		PV_KOUMOKU1_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU2_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU3_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU4_NAME[8];	//DB 16 DUP(?)	;

extern	UNs		PV_KINOU01_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU02_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU03_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU04_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU05_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU06_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU07_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU08_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU09_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU10_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU11_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU12_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU13_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU14_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU15_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU16_NAE[8];		//DB 16 DUP(?)	;

extern	UNs		SEQ_PAR_101_BAK;		/* V00p */
extern	UNs		disp_stg_sel_bak;		/* V00p */
extern	UNs		WINDOW_NO_bak;			/* V00p */
extern	UNs		PV0_PAR_A_CHAR;         /* V00p */    /* ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
extern	UNs		PV0_PAR_B_CHAR;         /* V00p */    /* ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
extern	UNs		PV0_TBL_A_CHAR;         /* V00p */    /* ｾﾝｻのﾃｰﾌﾞﾙ番号 ASCII */
extern	UNs		PV0_TBL_B_CHAR;         /* V00p */    /* ｾﾝｻのﾃｰﾌﾞﾙ番号 ASCII */
extern	UNs		PV0_INTER_VER2;			/* V00p */    /* ｲﾝﾀｰﾛｯｸﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
extern	UNs		PV0_DEFULT_VER2;		/* V00p */    /* 初期値ﾃﾞｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
extern	UNs		PV0_SEQ_VER2;			/* V00p */    /* ｼｰｹﾝｽﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII */
extern	UNl		PV0_NOW_POSI000;		/* V00q */    /* 下限上高さPV */
extern	UNl		PV0_DYHITO_POS;			/* V00q */    /* 下限位置PV */
extern	UNl		PV0_SLIDE_POS;			/* V01  */    /* 生産下限PV */
extern	UNl		PV0_NOWPOSI_SLIDE;		/* V01  */    /* 生産下限or下限上高PV */

extern	UNs		GAIBU_RST_BAK;			/* V00t */

extern	UNs		PV0_MONALM_P01;
extern	UNs		PV0_MONALM_P02;
extern	UNs		PV0_MONALM_P03;
extern	UNs		PV0_MONALM_P04;
extern	UNs		PV0_MONALM_A01;
extern	UNs		PV0_MONALM_A02;
extern	UNs		PV0_MONALM_A03;
extern	UNs		PV0_MONALM_A04;
extern	UNs		PV0_MONALM_A05;
extern	UNs		PV0_MONALM_A06;
extern	UNs		PV0_MONALM_A07;
extern	UNs		PV0_MONALM_A08;
extern	UNs		PV0_MONALM_B01;
extern	UNs		PV0_MONALM_B02;
extern	UNs		PV0_MONALM_B03;
extern	UNs		PV0_MONALM_B04;
extern	UNs		PV0_MONALM_B05;
extern	UNs		PV0_MONALM_B06;
extern	UNs		PV0_MONALM_B07;
extern	UNs		PV0_MONALM_B08;
extern	UNl		PV0_MONALM_C01;
extern	UNl		PV0_MONALM_C02;
extern	UNl		PV0_MONALM_C03;
extern	UNl		PV0_MONALM_C04;
extern	UNl		PV0_MONALM_C05;
extern	UNl		PV0_MONALM_C06;
extern	UNl		PV0_MONALM_C07;
extern	UNl		PV0_MONALM_C08;
extern	UNs		PV0_MONALM_B01_SIGN;
extern	UNs		PV0_MONALM_B02_SIGN;
extern	UNs		PV0_MONALM_B03_SIGN;
extern	UNs		PV0_MONALM_B04_SIGN;
extern	UNs		PV0_MONALM_B05_SIGN;
extern	UNs		PV0_MONALM_B06_SIGN;
extern	UNs		PV0_MONALM_B07_SIGN;
extern	UNs		PV0_MONALM_B08_SIGN;
extern	UNs		PV0_MONALM_C01_SIGN;
extern	UNs		PV0_MONALM_C02_SIGN;
extern	UNs		PV0_MONALM_C03_SIGN;
extern	UNs		PV0_MONALM_C04_SIGN;
extern	UNs		PV0_MONALM_C05_SIGN;
extern	UNs		PV0_MONALM_C06_SIGN;
extern	UNs		PV0_MONALM_C07_SIGN;
extern	UNs		PV0_MONALM_C08_SIGN;

extern	UNs		MOTION_SV_CHG_CANCEL;			/* V01d */

extern	UNs		TAIKIKAKU_CHG_FLG;				/* V01i */
extern	UNs		GAMNE_REDISP_COD;				/* V01i */

extern	UNs		SEQ_PAR_107_BAK;				/* V01j */
extern	UNs		SEQ_PAR_427_CHG;				/* V01j */
extern	UNs		SEQ_PAR_427_ONE;				/* V01j */
extern	UNs		SEQ_PAR_427_OFE;				/* V01j */
extern	UNs		SEQ_PAR_427_BAK;				/* V01j */
extern	UNs		autokana_sw56_bak;				/* V01j */
extern	UNs		ADC_DISP_FLG;					/* V01j */
extern	UNs		ADC_CHG_LST;					/* V01j */
extern	UNs		ADC_CHG_LST1;					/* V01j */
extern	UNs		ADC_CHG_LST2;					/* V01j */
extern	UNs		ADC_CHG_LST3;					/* V01j */
extern	UNs		ADC_CHG_LST4;					/* V01j */
extern	UNs		ADC_CHG_LST5;					/* V01j */
extern	UNs		ADC_CHG_LST2_2;					/* V01j */
extern	UNs		ADC_MODE_FLG;					/* V01j */
extern	UNs		ADC_STEP_FLG;					/* V01j */
extern	UNs		ADC_STPCHG_FLG;					/* V01j */
extern	UNs		ADC_FILCK_LST;					/* V01j */
extern	UNs		ADC_SW2_FLG;					/* V01j */
extern	UNs		ADC_SW34_FLG;					/* V01j */
extern	UNs		ADC_SW5_FLG;					/* V01j */
extern	UNs		ADC_SW6_FLG;					/* V01j */
extern	UNs		SW14_DISP7_NON;					/* V01j */
extern	UNs		ADC_STEP_NO[4];					/* V01j */
extern	UNs		ADC_STEP_NO_LAST[4];			/* V01j */
extern	UNs		step_flick_flg;					/* V01j */
extern	UNs		step_flick_flg_bak;				/* V01j */
extern	UNs		step_flick_cnt;					/* V01j */

extern	UNl		CAR_LNG_KAJ_AREA;				/* V01k */
extern	UNs		SYO_LNG_KAJ_CNT;				/* V01k */

extern	UNl		PV0_KAGEN_POSITIONER;			/* V01l_b */

extern	UNs		SYO_LNG_SUR_CNT;				/* V01m */

extern	UNs		DEB_WORD_FLG1;					/* V01n_b */
extern	UNs		DEB_WORD_FLG2;					/* V01n_b */
extern	UNs		DEB_WORD_FLG3;					/* V01n_b */
extern	UNs		DEB_WORD_FLG4;					/* V01n_b */
extern	UNs		DEB_WORD_FLG5;					/* V01n_b */
extern	UNs		DEB_WORD_FLG6;					/* V01n_b */
extern	UNs		DEB_WORD_FLG7;					/* V01n_b */
extern	UNs		DEB_WORD_FLG8;					/* V01n_b */
extern	UNs		DEB_WORD_FLG9;					/* V01n_b */
extern	UNs		DEB_WORD_FLG10;					/* V01n_b */
extern	UNs		DEB_WORD_FLG11;					/* V01n_b */
extern	UNs		DEB_WORD_FLG12;					/* V01n_b */
extern	UNs		DEB_WORD_FLG13;					/* V01n_b */
extern	UNs		DEB_WORD_FLG14;					/* V01n_b */
extern	UNs		DEB_WORD_FLG15;					/* V01n_b */
extern	UNs		DEB_WORD_FLG16;					/* V01n_b */

//★★★★★★★	以下、ＳＩＴ－４で追加		★★★★★★★
extern	UNl		DEBUG_CNT;

extern	UNs		CSR_BAK_M_LEN;	
extern	UNs		CSR_BAK_X_POS;	
extern	UNs		CSR_BAK_Y_POS;	
extern	UNs		CSR_BAK_C_COL;	
extern	UNs		CSR_BAK_B_COL;	
extern	UNs		CSR_BAK_SIZE;	
extern	UNs		*CSR_BAK_G_P;	

extern	GAMENn_HEAD_st	GAMENn_HEAD;
extern	DISP_INFO_st	DISP_INFO;

extern	UNl		CHR_TABLE_ADR;			// キャラクタテーブルの文字列キャラクタ先頭アドレス
extern	UNl		CSR_TABLE_ADR;			// キャラクタテーブルのカーソルキャラクタ先頭アドレス
extern	UNl		SWL_TABLE_ADR;			// キャラクタテーブルのＳＷ－ＬＡＭＰキャラクタ先頭アドレス
extern	UNl		S56_TABLE_ADR;			// キャラクタテーブルのＳＷ５・６下段キャラクタ先頭アドレス
extern	UNl		MES_TABLE_ADR;			// キャラクタテーブルのメッセージキャラクタ先頭アドレス
extern	UNl		S56U_TABLE_ADR;			// キャラクタテーブルのＳＷ５・６上段キャラクタ先頭アドレス
extern	UNl		SPE_TABLE_ADR;			// キャラクタテーブルの特別キャラクタ先頭アドレス

extern	UNl		GAMENN_MOJ_INF_ADR;		// 画面ｎの文字列情報の先頭アドレス			（画面ｎを表示するときに算出）
extern	UNl		GAMENN_CSR_INF_ADR;		// 画面ｎのカーソル情報の先頭アドレス		（画面ｎを表示するときに算出）
extern	UNl		GAMENN_SVP_INF_ADR;		// 画面ｎの設定値情報の先頭アドレス			（画面ｎを表示するときに算出）
extern	UNl		GAMENN_PVP_INF_ADR;		// 画面ｎの実測値情報の先頭アドレス			（画面ｎを表示するときに算出）
extern	UNl		GAMENN_SWL_INF_ADR;		// 画面ｎのＳＷ－ＬＡＭＰの先頭アドレス		（画面ｎを表示するときに算出）
extern	UNl		GAMENN_GRP_INF_ADR;		// 画面ｎのグラフィック情報の先頭アドレス	（画面ｎを表示するときに算出）

extern	UNs		CHRTBL_CHR_CNT;			// キャラクタテーブルの文字列キャラクタ個数
extern	UNs		CHRTBL_CSR_CNT;			// キャラクタテーブルのカーソルキャラクタ個数
extern	UNs		CHRTBL_SWL_CNT;			// キャラクタテーブルのＳＷ－ＬＡＭＰキャラクタ個数
extern	UNs		CHRTBL_S56_CNT;			// キャラクタテーブルのＳＷ５・６下段キャラクタ個数
extern	UNs		CHRTBL_MES_CNT;			// キャラクタテーブルのメッセージキャラクタ個数
extern	UNs		CHRTBL_S56U_CNT;		// キャラクタテーブルのＳＷ５・６下段キャラクタ個数
extern	UNs		CHRTBL_SPE_CNT;			// キャラクタテーブルの特別キャラクタ個数

extern	UNs		GAMENn_SCR_COL;			//画面のｽｸﾘｰﾝ色（Windowを表示して変わらないこと）

extern	UNs		PVW_ZURE_PLS_SIN;		//軸間ｽﾞﾚ実測符号
extern	UNs		PVW_ZURE_RNA_SIN;		//軸間ｽﾞﾚﾘﾆｱ符号
extern	UNs		PVW_ZURE_PLS;			//軸間ｽﾞﾚ実測
extern	UNs		PVW_ZURE_RNA;			//軸間ｽﾞﾚﾘﾆｱ
extern	UNs		PVW_BAKORG_SIN1;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
extern	UNs		PVW_BAKORG_SIN2;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
extern	UNl		SVBW_BAKORG_PLS1;		//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2
extern	UNl		SVBW_BAKORG_PLS2;		//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2

extern	UNs		GAM_CHG_WIN_NO_BAK;		/* V04a */

extern	UNb		OP_STATUS;			//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H			//V01e
extern	UNb		OP_STATUS_DUM;			//DB	?		; OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H		//V01e

extern	UNb		MEM_ARI;				//DB	?		; OPｱﾘ:A5H		//V05h

extern	UNs		PV0_CB_C_VER[6];		//ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
extern	UNs		PV0_PAR_C_CHAR;			//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
extern	UNs		PV0_TBL_C_CHAR;			//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)

//;	******** 2007/12/12 ***********
extern	UNs		PV0_IPM_ADR0;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
extern	UNs		PV0_IPM_ADR1;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
extern	UNs		PV0_IPM_ADR2;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
extern	UNs		PV0_IPM_ADR3;			//IPｱﾄﾞﾚｽ(ﾓﾆﾀ)

//;	******** 2009/07/14 ***********
extern	UNs		IROCK_OUT_NO[8];			/* ｲﾝﾀｰﾛｯｸ発生番号		*/
extern	UNb		IROCK_CHAR[8][8];			/* ｲﾝﾀｰﾛｯｸ発生番号に対するｷｬﾗｸﾀ文字		*/

//;	******** 2009/08/-- *********** V05o(INS)	実測波形表示用
extern	UNs		WAVE_SAMP_DTP[2];					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ		+0:最新  +1:前回値
extern	UNs		WAVE_TRND_DTP[2];					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ		+0:最新  +1:前回値
extern	WAVE_SAMP_DATA_ST	WAVE_SAMP_DATA[501];	//実測ｻﾝﾌﾟﾘﾝｸﾞ波形用ﾃﾞｰﾀ
extern	WAVE_TRND_DATA_ST	WAVE_TRND_DATA[5001];	//実測ﾄﾚﾝﾄﾞ波形用ﾃﾞｰﾀ
extern	WAVE_SAMP_DOT_ST	WAVE_SAMP_DOT[501];		//実測ｻﾝﾌﾟﾘﾝｸﾞ波形用ﾃﾞｰﾀ
extern	WAVE_TRND_DOT_ST	WAVE_TRND_DOT[5001];	//実測ﾄﾚﾝﾄﾞ波形用ﾃﾞｰﾀ
extern	UNs		CSR_PVSAMP[2];						//実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面のｶｰｿﾙ位置	+0:最新  +1:前回値
extern	UNs		CSR_PVTRND[2];						//実測ﾄﾚﾝﾄﾞ波形画面のｶｰｿﾙ位置		+0:最新  +1:前回値
extern	UNs		PW_Key_up[4];						//実測波形画面用ｷｰ立上り変化	(5ms割込みで監視)
extern	UNs		PW_Key_dn[4];						//実測波形画面用ｷｰ立下り変化	(5ms割込みで監視)
extern	UNs		PW_Key_last[4];						//実測波形画面用ｷｰ前回値		(5ms割込みで監視)
extern	UNs		PW_Key_tim02[4];					//実測波形画面用ｷｰ長押し時間	(5ms割込みで監視)
extern	UNs		PW_Key_tim30[4];					//実測波形画面用ｷｰ長押し時間	(5ms割込みで監視)
extern	UNs		PV0_SMPCSR_KJT;						//ｶｰｿﾙ位置の合計荷重
extern	UNs		PV0_SMPCSR_KJL;						//ｶｰｿﾙ位置の左荷重
extern	UNs		PV0_SMPCSR_KJR;						//ｶｰｿﾙ位置の右荷重
extern	UNs		PV0_SMPCSR_AGL;						//ｶｰｿﾙ位置の角度
extern	UNl		PV0_SMPCSR_RNA1;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
extern	UNl		PV0_SMPCSR_RNA2;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
extern	UNs		PV0_SMPCSR_SEQ0;					//ｶｰｿﾙ位置のｼｰｹﾝｽ
extern	UNs		PV0_SMPCSR_SEQ1;					//ｶｰｿﾙ位置のｼｰｹﾝｽ
extern	UNs		PV0_SMPCSR_TIM;						//ｶｰｿﾙ位置の時間
extern	UNs		PV0_SMPCSR_POS;						//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ
extern	UNl		PV0_TRDCSR_RNAU;					//ｽﾗｲﾄﾞ上限検出位置
extern	UNl		PV0_TRDCSR_RNAD;					//ｽﾗｲﾄﾞ下限検出位置
extern	UNs		PV0_TRDCSR_KJT;						//ｶｰｿﾙ位置の合計荷重
extern	UNs		PV0_TRDCSR_KJL;						//ｶｰｿﾙ位置の左荷重
extern	UNs		PV0_TRDCSR_KJR;						//ｶｰｿﾙ位置の右荷重
extern	UNl		PV0_TRDCSR_RNA1;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
extern	UNl		PV0_TRDCSR_RNA2;					//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
extern	UNs		PV0_TRDCSR_TIM;						//ｶｰｿﾙ位置の時間
extern	UNs		PV0_TRDCSR_POS;						//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ
extern	UNs		PV0_TRDCSR_POSL;					//ｶ-ｿﾙ範囲
extern	UNs		PV0_TRDCSR_POSR;					//ｶ-ｿﾙ範囲

//;	******** 2010/08/10~ *********** V05r(INS)
extern	UNs		SEIDOU_SEQ_LST;						//
extern	UNs		sys_1min_cnt;						//1minｶｳﾝﾀ
//extern	UNs		PVTIM_seidouseinou_inter;			//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ(1minﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)
//extern	UNs		PVTIM_seidouseinou_yokok;			//制動性能試験予告ﾀｲﾏ(1minﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)
extern	UNs		SYO_HOS_KAJ_CNT;
extern	UNs		PV0_INTER_TIM;						//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ(1hﾃﾞｸﾘﾒﾝﾄﾀｲﾏ)

//;	******** 2010/08/31~ *********** V06 (INS)
extern	UNl		INTR_DAT_OFS;
extern	UNl		INIT_DAT_OFS;
extern	UNl		ALL_CHR_TBL_OFS;
extern	UNl		GAM_INF_TBL_OFS;
extern	UNs		EcoMeter_bit;
extern	UNs		PV0_EPMCSR_HOR;
extern	UNs		PV0_EPMCSR_MIN;
extern	UNl		PV0_EPMCSR_UEP;
extern	UNl		PV0_EPMCSR_KEP;
extern	UNl		PV0_EPMCSR_TEP;
extern	UNl		PV0_EPML_SCRH;
extern	UNl		PV0_EPML_SCRM;
extern	UNl		PV0_EPML_SCRL;
extern	UNl		PV0_EPMR_SCRH;
extern	UNl		PV0_EPMR_SCRM;
extern	UNl		PV0_EPMR_SCRL;
extern	UNl		PV0_EPM_KWH[20][3];					//電力モニタ用グラフデータ
extern	UNs		EPM_CSR[2];							//電力モニタ用カーソル位置
extern	UNs		EPM_TIM_BAK;						//単位時間
extern	UNl		EPM_GRP_MXL;						//棒グラフ最大値変わった？
extern	UNl		EPM_GRP_MXR;						//折れ線グラフ最大値変わった？
extern	UNs		sys_1sec_cnt;						//1secｶｳﾝﾀ

//extern	UNl		EPM_SEC_60ADD[2];					//消費電力量 60sec積算(kWs)
//extern	UNs		EPM_SEC_60CNT;
//extern	UNl		EPM_HOR_BUF[24*60][2];				//消費電力量 1440分(kWs)
//extern	UNs		EPM_HOR_POI;
extern	UNs		EPM_GAMEN_RIF;						//電力モニタ画面リフレッシュフラグ

extern	UNl		PV0_SMPCSR_EP;						//ｻﾝﾌﾟﾘﾝｸﾞ波形画面ｶｰｿﾙ位置の瞬時電力
extern	int		PV0_SMPCSR_EP_SIN;					//ｻﾝﾌﾟﾘﾝｸﾞ波形画面ｶｰｿﾙ位置の瞬時電力		//V06a
extern	UNl		PV0_TRDCSR_EP;						//ﾄﾚﾝﾄﾞ波形画面   ｶｰｿﾙ位置の電力量

extern	UNs		SEIDOU_DSP_LST;

extern	UNs		PV0_INTER_VER1;						/* ｲﾝﾀｰﾛｯｸﾊﾞｰｼﾞｮﾝ 数値 */
extern	UNs		PV0_DEFULT_VER1;					/* 初期値ﾃﾞｰﾀﾊﾞｰｼﾞｮﾝ 数値 */

extern	UNs		PV0_EPMDAT_SIN;						//ｻﾝﾌﾟﾘﾝｸﾞ波形画面の電力値符号BIT
extern	UNs		EPM_TOTAL_INF;						//電力ﾓﾆﾀ画面累計値切替の表示情報			//V06a
extern	UNs		EPM_TLINF_BAK;						//電力ﾓﾆﾀ画面累計値切替の表示情報			//V06a
extern	UNs		EPM_CLR_TIM;						//電力ﾓﾆﾀ内部ﾃﾞｰﾀｸﾘｱﾀｲﾑ						//V06a
extern	UNs		EPM_CLR_FLG;						//電力ﾓﾆﾀｸﾘｱ受付ﾌﾗｸﾞ						//V06a
extern	UNs		EPM_GAMRIF_CNT;						//電力ﾓﾆﾀ画面ﾘﾌﾚｯｼｭﾀｲﾐﾝｸﾞｶﾝｳﾀ				//V06a

extern	UNs		SV0_EP_AVE;


extern	UNl		EPM_SEC_2_MESMIN_ADD[2];
extern	UNs		EPM_SEC_MESMIN_CNT;

extern	UNl		EPM_05MIN_BUF[5/5][2] ;
extern	UNl		EPM_10MIN_BUF[10/5][2];
extern	UNl		EPM_15MIN_BUF[15/5][2];
extern	UNl		EPM_20MIN_BUF[20/5][2];
extern	UNl		EPM_25MIN_BUF[25/5][2];
extern	UNl		EPM_30MIN_BUF[30/5][2];
extern	UNl		EPM_35MIN_BUF[35/5][2];
extern	UNl		EPM_40MIN_BUF[40/5][2];
extern	UNl		EPM_45MIN_BUF[45/5][2];
extern	UNl		EPM_50MIN_BUF[50/5][2];
extern	UNl		EPM_55MIN_BUF[55/5][2];
extern	UNl		EPM_60MIN_BUF[60/5][2];

extern	UNs		EPM_05MIN_POI;
extern	UNs		EPM_10MIN_POI;
extern	UNs		EPM_15MIN_POI;
extern	UNs		EPM_20MIN_POI;
extern	UNs		EPM_25MIN_POI;
extern	UNs		EPM_30MIN_POI;
extern	UNs		EPM_35MIN_POI;
extern	UNs		EPM_40MIN_POI;
extern	UNs		EPM_45MIN_POI;
extern	UNs		EPM_50MIN_POI;
extern	UNs		EPM_55MIN_POI;
extern	UNs		EPM_60MIN_POI;

extern	UNl		EPM_05MON_BUF[20][2];
extern	UNl		EPM_10MON_BUF[20][2];
extern	UNl		EPM_15MON_BUF[20][2];
extern	UNl		EPM_20MON_BUF[20][2];
extern	UNl		EPM_25MON_BUF[20][2];
extern	UNl		EPM_30MON_BUF[20][2];
extern	UNl		EPM_35MON_BUF[20][2];
extern	UNl		EPM_40MON_BUF[20][2];
extern	UNl		EPM_45MON_BUF[20][2];
extern	UNl		EPM_50MON_BUF[20][2];
extern	UNl		EPM_55MON_BUF[20][2];
extern	UNl		EPM_60MON_BUF[20][2];

extern	UNs		EPM_05MON_POI;
extern	UNs		EPM_10MON_POI;
extern	UNs		EPM_15MON_POI;
extern	UNs		EPM_20MON_POI;
extern	UNs		EPM_25MON_POI;
extern	UNs		EPM_30MON_POI;
extern	UNs		EPM_35MON_POI;
extern	UNs		EPM_40MON_POI;
extern	UNs		EPM_45MON_POI;
extern	UNs		EPM_50MON_POI;
extern	UNs		EPM_55MON_POI;
extern	UNs		EPM_60MON_POI;

//;	******** 2010/12/06 *********** V06b (INS)
extern	UNs		rulet_taiki_pos1;			//反転、振り子時の待機点
extern	UNs		rulet_taiki_pos2;			//		振り子時の待機点
extern	UNl		SV0_TAL1_CNT;				//ﾄｰﾀﾙｶｳﾝﾀ修正値
extern	UNl		SV0_LOT1_CNT;				//ﾛｯﾄｶｳﾝﾀ1修正値
extern	UNl		SV0_LOT2_CNT;				//ﾛｯﾄｶｳﾝﾀ2修正値

//;	******** 2011/01/02 *********** V06c (INS)
extern	UNs		SV0_WORKER_COD_BAK	;		//作業者ｺｰﾄﾞ退避
extern	UNl		SV0_ORDER_COD_BAK	;		//注番ｺｰﾄﾞ退避
extern	UNl		SV0_PLAN_CNT_BAK		;		//計画数退避
extern	UNs		SV0_WORKER_COD		;		//作業者ｺｰﾄﾞ取得
extern	UNl		SV0_ORDER_COD		;		//注番ｺｰﾄﾞ取得
extern	UNl		SV0_PLAN_CNT		;		//計画数取得

extern	UNs		SV0_WORK_STR_FLG		;	//作業開始ﾌﾗｸﾞ（to C/B用）
extern	UNs		SV0SP_WORKER_COD	;		//作業開始時作業者ｺｰﾄﾞ
extern	UNl		SV0SP_ORDER_COD		;		//作業開始時注番ｺｰﾄﾞ
extern	UNl		SV0SP_PLAN_CNT		;		//作業開始時計画数
extern	UNl		SV0SP_BAD_CNT		;		//作業開始時不良数
extern	UNs		SV0SP_KATA_NO		;		//作業開始時型番号
extern	UNs		SV0SP_KATA_NAME[7]	;		//作業開始時型名称
extern	UNs		SV0SP_KATA_MEMO[7]	;		//作業開始時型メモ

extern	UNs		SV0_WORK_STP_FLG		;	//作業終了ﾌﾗｸﾞ（to C/B用）
extern	UNs		SV0SR_WORKER_COD	;		//作業終了時作業者ｺｰﾄﾞ
extern	UNl		SV0SR_ORDER_COD		;		//作業終了時注番ｺｰﾄﾞ
extern	UNl		SV0SR_PLAN_CNT		;		//作業終了時計画数
extern	UNl		SV0SR_BAD_CNT		;		//作業終了時不良数
extern	UNs		SV0SR_KATA_NO		;		//作業終了時型番号
extern	UNs		SV0SR_KATA_NAME[7]	;		//作業終了時型名称
extern	UNs		SV0SR_KATA_MEMO[7]	;		//作業終了時型メモ

extern	UNs		KAT_RD_CSR_POS	;			//型読出し時のCSR_TBL_POS_NOW

//;	******** 2012/09/24 *********** V06m (INS)
extern	UNs		DIEH_OFS_FLG;
extern	UNs		FURIKO_FLG;

//;	******** 2012/10/15 *********** V06n (INS)
extern	UNl		SV0_RNAPOS_MAXO;
extern	UNl		SV0_RNAPOS_MINO;
extern	UNs		SV0_DAIHAI_LNG1O;
extern	UNs		SV0_DAIHAI_LNG2O;
extern	UNs		MOT_MODE_BAK;

//;	******** 2013/02/18 *********** V06p (INS)
extern	UNs		PV0_CKSPD_OVBIT;
extern	UNs		PV0_KATRD_BIT;
extern	UNs		TEST_SEQ;
extern	UNs		FURIKO_SEQ_LST;

//;	******** 2013/12/11 *********** SIT4-MC
extern	UNb		*VRAM_Dst8;
extern	UNs		*VRAM_Dst;
extern	UNb		*VRAM_Src;
extern	UNb		*VRAM_End;
extern	UNs		GAM_COPY_FLG;
extern	UNs		GAM_COPY_STS;

//;	******** 2014/02/06 *********** SIT4-MC
extern	UNs		IROCK_COL_CHG_NO;

//;	******** 2014/03/13 *********** SIT4-MC
extern	UNs		SMP_KAJ_MAX_SIN;
extern	UNs		SMP_KAJ_MIN_SIN;
extern	UNs		SMP_EP_MAX_SIN;
extern	UNs		SMP_EP_MIN_SIN;
extern	UNs		TRD_KAJ_MAX_SIN;
extern	UNs		TRD_KAJ_MIN_SIN;
extern	UNs		TRD_EP_MAX_SIN;
extern	UNs		TRD_EP_MIN_SIN;
extern	UNs		OVER_LOAD_SEL;
extern	UNs		LOW_LIMIT_SEL;
extern	UNs		SV0_OVLD_SEL;
extern	UNs		SV0_LWLM_SEL;
extern	UNs		MEM_KAJ_SEL;

//;	******** 2014/04/15 *********** SIT4-MC
extern	UNs		PV0_CKAGL_OVBIT;

//;	******** 2014/06/04 *********** SIT4-MC
extern	UNs		SLDTUN_RNA_SEL ;

//;	******** 2014/08/20 ***********
extern	UNl		CAR_MICRO_KAJ_AREA;

//;	******** 2014/08/26 SIT4-MC ***********
extern	UNl		SV0_RELE_POS	;			//リリース高さ
extern	UNs		SV0_RELE_SNO0	;			//リリースカムオン行程
extern	UNs		SV0_RELE_AGL0	;			//リリースカムオン角度
extern	UNs		SV0_RELE_SNO1	;			//リリースカムオフ行程
extern	UNs		SV0_RELE_AGL1	;			//リリースカムオフ角度
extern	UNs		SV0_RELE_CAM	;			//リリースカム設定対象
extern	UNl		SV0_SEND_POS	;			//送り高さ
extern	UNs		SV0_SEND_SNO0	;			//送りカムオン行程
extern	UNs		SV0_SEND_AGL0	;			//送りカムオン角度
extern	UNs		SV0_SEND_SNO1	;			//送りカムオフ行程
extern	UNs		SV0_SEND_AGL1	;			//送りカムオフ角度
extern	UNs		SV0_SEND_CAM	;			//送りカム設定対象
extern	UNs		SV0_TIMING_SNO0	;			//タイミングカムオン行程
extern	UNs		SV0_TIMING_AGL0	;			//タイミングカムオン角度
extern	UNs		SV0_TIMING_SNO1	;			//タイミングカムオフ行程
extern	UNs		SV0_TIMING_AGL1	;			//タイミングカムオフ角度
extern	UNs		SV0_TIMING_CAM	;			//タイミングカム設定対象
extern	UNs		PV0_CAMATCAL_MES1;			//カム自動演算設定不可時のメッセージ番号
extern	UNs		PV0_CAMATCAL_MES2;			//カム自動演算設定不可時のメッセージ番号
extern	UNs		PV0_CAMATCAL_MES3;			//カム自動演算設定不可時のメッセージ番号
extern	UNs		PV0_MOTION_INF;				//BIT0：ﾓｰｼｮﾝに停止行程がある。
extern	UNs		PV0_SINKAKU_UPDN1;			//BITn：ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。
extern	UNs		PV0_SINKAKU_UPDN2;			//BITn：ﾛｰﾀﾘｶﾑnのOFF進角が加減速範囲にある。

extern	UNs		SV0_MOT_REP;				//モーションのリピート情報
extern	UNs		SV0_MOT_FIX;				//モーションの一定領域情報
extern	UNs		SV0_FIXARA_AGLS;			//一定領域　開始角度
extern	UNl		SV0_FIXARA_POSS;			//一定領域　開始位置
extern	UNs		SV0_FIXARA_SPDB;			//一定領域　開始前速度
extern	UNs		SV0_FIXARA_SPDF;			//一定領域　一定速度
extern	UNs		SV0_FIXARA_AGLE;			//一定領域　終了角度
extern	UNl		SV0_FIXARA_POSE;			//一定領域　終了位置
extern	UNs		PV0_FIXBF_SPD;				//一定領域　開始前速度

extern	UNs		PV0_CAMATCAL_FLG;			//カム出力自動設定フラグクリア			2014/09/12

extern	UNs		SV0_REP_FIX_FLG;			//繰り返し／一定領域  有効／無効ﾌﾗｸﾞ	2014/09/23
extern	UNs		MOT_FERR_TIM;				//F挿入ERR信号ON時間					2014/09/25

extern	UNs		PV0_FMOTSET_MES1;			//一定速度設定時のメッセージ番号		2014/10/09

//;	******** 2015/01/14 ***********
extern	UNs		SV_1DANPRS_SRV;             /* 1段目目標荷重 */
extern	UNs		SV_2DANPRS_SRV;             /* 2段目目標荷重 */
extern	UNs		SV_3DANPRS_SRV;             /* 3段目目標荷重 */
extern	UNs		SV_4DANPRS_SRV;             /* 4段目目標荷重 */
extern	UNs		SV_5DANPRS_SRV;             /* 5段目目標荷重 */
extern	UNs		SV_6DANPRS_SRV;             /* 6段目目標荷重 */
extern	UNs		SV_7DANPRS_SRV;             /* 7段目目標荷重 */
extern	UNs		SV_8DANPRS_SRV;             /* 8段目目標荷重 */
extern	UNs		SV_9DANPRS_SRV;             /* 9段目目標荷重 */
extern	UNs		SV_10DANPRS_SRV;            /* 10段目目標荷重 */
extern	UNs		SV_KAJOBJ_HAB;				/* 荷重完了範囲 */

//;	******** 2015/01/20 ***********
extern	UNs		TANNI_SEQ_LST;

//;	******** 2015/05/19 ***********
extern	UNs		TRND_DTP_FLG;
extern	UNs		chk_kjofs_dat[10];

//;	******** 2015/07/10 ***********
extern	UNs		PV0_CKSPD_LMBIT;

//;	******** 機器交換画面の入力制限対応 ***********		2016/02/25
extern	UNs		SV0_RNAORG_ENB1;				//機械原点入力（入力許可）
extern	UNs		SV0_ORGCAL_ENB2;				//機番（入力許可）
extern	UNs		SV0_ORGCAL_ENB1;				//機種（入力許可）
extern	UNs		SV0_MACINE_ENB1;				//角度値切替（入力許可）
extern	UNs		SV0_OFSET_ENB;					//ｵﾌｾｯﾄ調整（入力許可）
extern	UNs		SV0_KOUSEI_ENB;					//荷重校正（入力許可）
extern	UNs		SV0_MAXHIZ_ENB;					//最大歪（入力許可）
extern	UNs		SV0_MAXKAJ_ENB;					//最大荷重（入力許可）
extern	UNs		SV0_KOUKAJ_ENB;					//校正荷重（入力許可）

//;	******** 周辺機連動機能追加仕様 ***********		2016/04/22
extern	UNs		SQ_ORIDE_BAK;
extern	UNs		TLINK_NEXT_LAST;
extern	UNs		TLINK_NEXT_LAST1;
extern	UNs		TLINK_NEXT_NO;
extern	UNs		ADC_SW5_ON_FLG;
extern	UNs		ADC_SW6_ON_FLG;


