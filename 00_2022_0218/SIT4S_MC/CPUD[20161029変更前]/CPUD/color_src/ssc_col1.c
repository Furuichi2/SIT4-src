/************************************************************************************/
/*																					*/
/*		コマツ参機殿向け　ＳＩＴ－４　ＨＭＩプログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			カラーＬＣＤ（640*480）表示												*/
/*																					*/
/************************************************************************************/
#include "cm_equ1.h"							//各種の共通定義
#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義
#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_dpram_seq_ext.h"


//#define		OLD_RIF									/* ﾃﾞﾊﾞｯｸﾞ	ｻﾝﾌﾟﾙ描画	*/
#define		NEW_RIF									/* ﾃﾞﾊﾞｯｸﾞ	ｻﾝﾌﾟﾙ描画	*/


/* 外部参照関数定義 -------------------------------------------------- */
extern	void	GAM_INF_TBL(void);				//画面表示情報テーブル
extern	void	ALL_CHR_TBL(void);				//表示キャラクタテーブル
extern	void	ALLTBL_CSTBL(void);				//カーソル制御情報テーブル
extern	void	ALLTBL_SVTBL(void);				//設定値制御情報テーブル
extern	void	ALLTBL_PVTBL(void);				//実測値制御情報テーブル
extern	void	ALLTBL_SWTBL(void);				//ＳＷ－ＬＡＭＰ制御情報テーブル
extern	void	ALLTBL_CHARTBL(void);
extern	void	disp_moji_s_color(UNs len, UNs x, UNs y, UNs c_col, UNs b_col, UNs size, UNs *g_adr_p, UNb Lcd_p[][PanelWidth]);
extern	void	disp_moji_s_paint(UNs len, UNs x, UNs y, UNs col, UNs size, UNb Lcd_p[][PanelWidth]);
//2014/09/02	extern	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth]);
extern	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth], UNs off);

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VMON1[6*16*2][PanelWidth];
extern	UNb		LCD_VMON2[6*16*2][PanelWidth];

/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	Gamen_Init(void);					//イニシャル
void	Gamenn_Disp_Init(void);				//画面Ｎｏ．ｎを表示する時のイニシャル
void	Windown_Disp_Init(void);			//ウィンドウＮｏ．ｎを表示する時のイニシャル	未使用
void	Gamenn_Disp_Moji(void);				//画面Ｎｏ．ｎの文字列表示
void	CSR_disp_color(void);
void	Backgnd_Disp(U4b c_tbl_adr);		//背景色表示
void	Moji_Disp_Char(U4b c_tbl_adr);		//文字列表示
void	Gamenn_CSRtbl_set(void);
void	Gamenn_SVtbl_set(void);
void	Gamenn_PVtbl_set(void);
void	Gamenn_SWLtbl_set(void);

/* テーブル定義 ------------------------------------------------------ */
extern	const	UNs *	SW56_Cam_Name_Tbl[69];
extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs *	KAT_sv_memo_tbl[101];
extern	const	UNs		SPACE_ASCII_40[40];			// V05a


/*
********************************************************************************
*
*	イニシャル
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamen_Init(void)
{
	U2b		*adr;
	U4b		i;

	i = (U4b)&ALL_CHR_TBL;
	i += ALL_CHR_TBL_OFS;			//V06
	i += language_chg;
	adr = (U2b *)i;
	CHRTBL_CHR_CNT = *adr++;
	CHRTBL_CSR_CNT = *adr++;
	CHRTBL_SWL_CNT = *adr++;
	CHRTBL_S56_CNT = *adr++;
	CHRTBL_MES_CNT = *adr++;
	CHRTBL_S56U_CNT = *adr++;
	CHRTBL_SPE_CNT = *adr++;

//V06r	CHR_TABLE_ADR = (U4b)&ALL_CHR_TBL + language_chg + All_chr_head_size;	// キャラクタテーブルの文字列キャラクタ先頭アドレス
	CHR_TABLE_ADR = (U4b)&ALL_CHR_TBL + ALL_CHR_TBL_OFS + language_chg + All_chr_head_size;	// キャラクタテーブルの文字列キャラクタ先頭アドレス

	CSR_TABLE_ADR = CHR_TABLE_ADR + (CHRTBL_CHR_CNT * CHAR_MOJI_SIZE) +2;	// キャラクタテーブルのカーソルキャラクタ先頭アドレス
	SWL_TABLE_ADR = CSR_TABLE_ADR + (CHRTBL_CSR_CNT * CHAR_CSR_SIZE) +2;	// キャラクタテーブルのＳＷ－ＬＡＭＰキャラクタ先頭アドレス
	S56_TABLE_ADR = SWL_TABLE_ADR + (CHRTBL_SWL_CNT * CHAR_SWL_SIZE) +2;	// キャラクタテーブルのＳＷ５・６下段キャラクタ先頭アドレス
	MES_TABLE_ADR = S56_TABLE_ADR + (CHRTBL_S56_CNT * CHAR_S56_SIZE) +2;	// キャラクタテーブルのメッセージキャラクタ先頭アドレス
	S56U_TABLE_ADR = MES_TABLE_ADR + (CHRTBL_MES_CNT * CHAR_MES_SIZE) +2;	// キャラクタテーブルのＳＷ５・６上段キャラクタ先頭アドレス
	SPE_TABLE_ADR = S56U_TABLE_ADR + (CHRTBL_S56U_CNT * CHAR_S56U_SIZE) +2;	// キャラクタテーブルの特別キャラクタ先頭アドレス
}


/*
********************************************************************************
*
*	画面Ｎｏ．ｎを表示する時のイニシャル	未使用
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_Disp_Init(void)
{
	U4b		i, g_top, adr, gn_top;
	U4b		*g_top2;
	U2b		*hrom, *hram;
	U1b		*vram;

	g_top = (GAMEN_NO-1) * 4 + (U4b)&GAM_INF_TBL;
	g_top += GAM_INF_TBL_OFS;							//V06
	g_top2 = (U4b *)g_top;
	gn_top = *g_top2;
	gn_top += (U4b)&GAM_INF_TBL;
	gn_top += GAM_INF_TBL_OFS;							//V06
	gn_top += 514;

	hrom = (U2b *)gn_top;
	adr	= (U4b)&GAMENn_HEAD;
	hram = (U2b *)adr;

	for (i=0; i<GAMENn_HEAD_SIZE/2; i++,hrom++,hram++)		//画面ｎのヘッダー情報をＲＡＭにコピー
	{
		*hram = *hrom;
	}

	GAMENN_MOJ_INF_ADR = gn_top + GAMENn_HEAD_SIZE;										//文字列情報の先頭アドレス
	GAMENN_CSR_INF_ADR = GAMENn_HEAD.chr_cnt * DISP_INFO_SIZE + GAMENN_MOJ_INF_ADR;		//カーソル情報の先頭アドレス
	GAMENN_SVP_INF_ADR = GAMENn_HEAD.csr_cnt * DISP_INFO_SIZE + GAMENN_CSR_INF_ADR;		//設定値情報の先頭アドレス
	GAMENN_PVP_INF_ADR = GAMENn_HEAD.svp_cnt * DISP_INFO_SIZE + GAMENN_SVP_INF_ADR;		//実測値情報の先頭アドレス
	GAMENN_SWL_INF_ADR = GAMENn_HEAD.pvp_cnt * DISP_INFO_SIZE + GAMENN_PVP_INF_ADR;		//SW-LAMP情報の先頭アドレス
	GAMENN_GRP_INF_ADR = GAMENn_HEAD.swl_cnt * DISP_INFO_SIZE + GAMENN_SWL_INF_ADR;		//グラッフィク情報の先頭アドレス
}


/*
********************************************************************************
*
*	ウィンドウＮｏ．ｎを表示する時のイニシャル	未使用
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Windown_Disp_Init(void)
{
	U4b		i, g_top, adr, gn_top;
	U4b		*g_top2;
	U2b		*hrom, *hram;
	U1b		*vram;

	g_top = (WINDOW_NO+70-1) * 4 + (U4b)&GAM_INF_TBL;
	g_top += GAM_INF_TBL_OFS;							//V06
	g_top2 = (U4b *)g_top;
	gn_top = *g_top2;
	gn_top += (U4b)&GAM_INF_TBL;
	gn_top += GAM_INF_TBL_OFS;							//V06
	gn_top += 514;

	hrom = (U2b *)gn_top;
	adr	= (U4b)&GAMENn_HEAD;
	hram = (U2b *)adr;

	for (i=0; i<GAMENn_HEAD_SIZE/2; i++,hrom++,hram++)		//画面ｎのヘッダー情報をＲＡＭにコピー
	{
		*hram = *hrom;
	}

	GAMENN_MOJ_INF_ADR = gn_top + GAMENn_HEAD_SIZE;										//文字列情報の先頭アドレス
	GAMENN_CSR_INF_ADR = GAMENn_HEAD.chr_cnt * DISP_INFO_SIZE + GAMENN_MOJ_INF_ADR;		//カーソル情報の先頭アドレス
	GAMENN_SVP_INF_ADR = GAMENn_HEAD.csr_cnt * DISP_INFO_SIZE + GAMENN_CSR_INF_ADR;		//設定値情報の先頭アドレス
	GAMENN_PVP_INF_ADR = GAMENn_HEAD.svp_cnt * DISP_INFO_SIZE + GAMENN_SVP_INF_ADR;		//実測値情報の先頭アドレス
	GAMENN_SWL_INF_ADR = GAMENn_HEAD.pvp_cnt * DISP_INFO_SIZE + GAMENN_PVP_INF_ADR;		//SW-LAMP情報の先頭アドレス
	GAMENN_GRP_INF_ADR = GAMENn_HEAD.swl_cnt * DISP_INFO_SIZE + GAMENN_SWL_INF_ADR;		//グラッフィク情報の先頭アドレス
}


/*
********************************************************************************
*
*	画面Ｎｏ．ｎのスクリーン色を表示
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_Screen( UNb Lcd_p[][PanelWidth] )
{
	UNl		cnt, col, wk;
	UNl		*vram;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	vram = (UNl *)&Lcd_p[0][0];
	cnt = (PanelWidth * PanelHeight) / 4;
	
	while (cnt--)
	{
		*vram++ = col;
	}
}


/*
********************************************************************************
*
*	ウィンドウＮｏ．ｎのスクリーン色を表示
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Window_Screen( UNb Lcd_p[][PanelWidth] )
{
	UNl		cnt, col, wk;
	UNl		*vram;
	UNs		xdot, ydot;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	if( (42 <= WINDOW_NO) && (WINDOW_NO <= 47) )		//V06c
	{	//作業開始/終了WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-Window2Height][0];
		cnt = (PanelWidth * Window2Height) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}

	else if( (51 <= WINDOW_NO) && (WINDOW_NO <= 58) )		//V06c
	{	//作業開始/終了WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-Window2Height][0];
		cnt = (PanelWidth * Window2Height) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}

	else if( (6 <= WINDOW_NO) && (WINDOW_NO <= 9) )
	{	//段取WINDOW
		for(ydot=PanelHeight-WindowHeight; ydot<PanelHeight; ydot++)
		{
			for(xdot=0; xdot<PanelDANWidth; xdot++)
			{
				Lcd_p[ydot][xdot] = (UNb)col;
			}
		}
	}
	else
	{	//通常WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-WindowHeight][0];
		cnt = (PanelWidth * WindowHeight) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_all_s
*  Function Name:	全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*  Input	:		画面番号
*					0:通常画面／1:ｳｲﾝﾄﾞｳ画面(BIT_15=1:半ｳｲﾝﾄﾞｳ画面)
*					LCDﾜｰｸの選択(0:LCD_WORK1/1:LCD_WORK2)
*
*  Return	: 		なし
*  Note		:
*
********************************************************************************
*/
void	disp_all_s_color( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr, adr1;
	U2b		*hrom, *hram;
	U2b		ccnt, len;
	U2b		dat, bit;
	U4b		*c_adr;
	U2b		*c_adr1;

	if (GAMENn_HEAD.chr_cnt == 0)	return;						// 文字列ある？

	ccnt = GAMENn_HEAD.chr_cnt;									// 文字列個数
	g_top = GAMENN_MOJ_INF_ADR;									// 文字列表示情報先頭ｱﾄﾞﾚｽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		if ( DISP_INFO.chr_no != 0 )
		{
			if (DISP_INFO.link_no == 0)
			{
				adr = CHR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (U2b *)adr;

				len = *hrom++;
				len >>= 8;

				if(len > MOJI_DATA_SIZE)					// V04a
				{
					len = MOJI_DATA_SIZE;
				}

				disp_moji_s_color(
					len, 
					DISP_INFO.bgn_xdot, 
					DISP_INFO.bgn_ydot, 
					DISP_INFO.chr_col,
					DISP_INFO.bgnd1_col, 
					DISP_INFO.chr_size, 
					hrom, 
					Lcd_p
					);
			}
			else
			{
				adr = adr1 = (DISP_INFO.link_no-1) * CTL_CHR_TBL_SIZE + (U4b)&ALLTBL_CHARTBL;
				adr1 += 4;

				c_adr	= (U4b *)adr;
				adr		= *c_adr;
				c_adr1	= (U2b *)adr;
				dat		= *c_adr1;
	
				c_adr1	= (U2b *)adr1;
				bit		= *c_adr1;

				// V06 負論理対応 =================================
				adr1 += 2;
				c_adr1	= (U2b *)adr1;
				if (*c_adr1 == 1)
				{
					dat = ~dat;
				}
				//=================================================

				if (dat & bit)
				{
					adr =  CHR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
					hrom = (U2b *)adr;
	
					len = *hrom++;
					len >>= 8;

					if(len > MOJI_DATA_SIZE)					// V04a
					{
						len = MOJI_DATA_SIZE;
					}

					disp_moji_s_color(
						len, 
						DISP_INFO.bgn_xdot, 
						DISP_INFO.bgn_ydot, 
						DISP_INFO.chr_col,
						DISP_INFO.bgnd1_col, 
						DISP_INFO.chr_size, 
						hrom, 
						Lcd_p
						);
				}
			}
		}
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	画面Ｎｏ．ｎのカーソルキャラクタ全表示
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_Disp_Csr( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, len, t_no;

	if (GAMENn_HEAD.csr_cnt == 0)	return;						// 文字列ある？

	ccnt = GAMENn_HEAD.csr_cnt;									// 文字列個数
	g_top = GAMENN_CSR_INF_ADR;									// 文字列表示情報先頭ｱﾄﾞﾚｽ

	t_no = 0;
	while (ccnt--)
	{
		if ((CSR_buff[t_no].TOK_NO & BIT_0) == 0)				//非表示の設定？  bit0=1 then 非表示
		{
			hrom = (U2b *)g_top;
			adr	= (U4b)&DISP_INFO;
			hram = (U2b *)adr;

			for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
			{
				*hram = *hrom;
			}

			adr =  CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
			hrom = (U2b *)adr;

			len = *hrom++;
			len >>= 8;

			if(len > CSR_DATA_SIZE)					// V04a
			{
				len = CSR_DATA_SIZE;
			}

			disp_moji_s_color(
				len, 
				DISP_INFO.bgn_xdot, 
				DISP_INFO.bgn_ydot, 
				DISP_INFO.chr_col,
				DISP_INFO.bgnd1_col, 
				DISP_INFO.chr_size, 
				hrom, 
				Lcd_p
				);
		}
		t_no++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	指定カーソルNo.の文字列表示
*
*	Input	:		なし
*	Return	: 		なし
*
*	履 歴	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	Disp_Csr_Moji(UNs t_no)
{
	U4b		adr;
	U2b		*hrom;
	U2b		len;

	if ((CSR_buff[t_no].TOK_NO & BIT_0) == 0)				//非表示の設定？  bit0=1 then 非表示
	{
		adr =  CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (U2b *)adr;

		len = *hrom++;
		len >>= 8;

		if(len > CSR_DATA_SIZE)					// V04a
		{
			len = CSR_DATA_SIZE;
		}

		disp_moji_s_color(
			len, 
			CSR_buff[t_no].X_POS, 
			CSR_buff[t_no].Y_POS, 
			CSR_buff[t_no].C_COL,
			CSR_buff[t_no].B_COL1, 
			CSR_buff[t_no].SIZE, 
			hrom, 
			LCD_VRAM
			);
	}
	else {
		disp_moji_s_paint(
			CSR_buff[t_no].M_LEN,		//半角桁数
			CSR_buff[t_no].X_POS,		//X始点
			CSR_buff[t_no].Y_POS,		//Y始点
			GAMENn_HEAD.scr_col,		//塗潰し色
			CSR_buff[t_no].SIZE,		//X2倍/Y2倍
			LCD_VRAM
			);
	}
}


/*
********************************************************************************
*
*	画面Ｎｏ．ｎのグラフィック全表示
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_Graphic( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;
	U2b		xdot, ydot;

	if (GAMENn_HEAD.grp_cnt == 0)	return;						// グラフィックある？

	ccnt = GAMENn_HEAD.grp_cnt;									// グラフィック個数
	g_top = GAMENN_GRP_INF_ADR;									// グラフィック表示情報先頭ｱﾄﾞﾚｽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		switch(DISP_INFO.parts_no)
		{
			case 0:		//直線
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				if( DISP_INFO.chr_no == 0 )		// Ｘ距離０？
				{		//縦線
					k = DISP_INFO.chr_size;							// Ｙ距離
					while(k--) {
						Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
						ydot++;
					}
				}
				else if( DISP_INFO.chr_size == 0 )		// Ｙ距離０？
				{		//横線
					k = DISP_INFO.chr_no;							// Ｘ距離
					while(k--) {
						Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
						xdot++;
					}
				}
				else
				{		//斜め線
				}
				break;

			case 1:		//ＢＯＸ
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				//縦線
				k = DISP_INFO.chr_size;							// Ｙ距離
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					ydot++;
				}
				//横線
				k = DISP_INFO.chr_no;							// Ｘ距離
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					xdot++;
				}
				//縦線
				k = DISP_INFO.chr_size;							// Ｙ距離
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					ydot--;
				}
				//横線
				k = DISP_INFO.chr_no;							// Ｘ距離
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					xdot--;
				}
				break;

			default :
				break;
		}

		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	画面Ｎｏ．ｎのグラフィック全表示
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_Graphic_All(void)
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;
	U2b		xdot, ydot;

	if (GAMENn_HEAD.grp_cnt == 0)	return;						// グラフィックある？

	ccnt = GAMENn_HEAD.grp_cnt;									// グラフィック個数
	g_top = GAMENN_GRP_INF_ADR;									// グラフィック表示情報先頭ｱﾄﾞﾚｽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		switch(DISP_INFO.parts_no)
		{
			case 0:		//直線
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				if( DISP_INFO.chr_no == 0 )		// Ｘ距離０？
				{		//縦線
					k = DISP_INFO.chr_size;							// Ｙ距離
					while(k--) {
						LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
						LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
						ydot++;
					}
				}
				else if( DISP_INFO.chr_size == 0 )		// Ｙ距離０？
				{		//横線
					k = DISP_INFO.chr_no;							// Ｘ距離
					while(k--) {
						LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
						LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
						xdot++;
					}
				}
				else
				{		//斜め線
				}
				break;

			case 1:		//ＢＯＸ
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				//縦線
				k = DISP_INFO.chr_size;							// Ｙ距離
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					ydot++;
				}
				//横線
				k = DISP_INFO.chr_no;							// Ｘ距離
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					xdot++;
				}
				//縦線
				k = DISP_INFO.chr_size;							// Ｙ距離
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					ydot--;
				}
				//横線
				k = DISP_INFO.chr_no;							// Ｘ距離
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					xdot--;
				}
				break;

			default :
				break;
		}

		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	背景色表示
*
*	Input	: 始点X、始点Y、文字列長(ﾊﾞｲﾄ長)、背景色、文字ｻｲｽﾞ(上位X,下位Y)
*	Return	: なし
*
********************************************************************************
*/
void	Backgnd_Disp(U4b c_tbl_adr)
{
#ifdef	OLD_RIF
	U2b		x_dot_leng, y_dot_leng;
	U2b		xcnt, ycnt;
	U2b		xdot, ydot;
	U4b		adr;
	U2b		cnt, *Dst_p;

	adr = c_tbl_adr + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	Dst_p = (U2b *)adr;

	cnt = *Dst_p++;
	cnt = (cnt>>8) & 0x0ff;								// 文字列長

	x_dot_leng = ((DISP_INFO.chr_size>>8) & 0x0ff) * cnt * 8;			// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = (DISP_INFO.chr_size & 0x0ff) * 16;						// ｻｲｽﾞ × 16dot／1文字

	xdot = DISP_INFO.bgn_xdot;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = DISP_INFO.bgn_ydot;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			LCD_VRAM[ydot][xdot] = DISP_INFO.bgnd1_col;
		}
	}
#endif
}


/*
********************************************************************************
*
*	文字列キャラタク表示（文字列ﾃﾞｰﾀ＝ｼﾌﾄJIS）
*
*	Input	: 始点X、始点Y、ｷｬﾗｸﾀNo.、文字色、文字ｻｲｽﾞ(上位X,下位Y)
*	Return	: なし
*
********************************************************************************
*/
void	Moji_Disp_Char(U4b c_tbl_adr)
{
#ifdef	OLD_RIF
	U4b		adr, flg;
	U2b		cnt, cnv_wk, *Dst_p, xcnt, ycnt;
	U2b		xdot, ydot, xsize, ysize, xdot_bak;
	U4b		i, j, k, l;
	U1b		moji[M_char], dot_wk[32], wk1b;

	flg = 0;
	xdot = DISP_INFO.bgn_xdot;
	ydot = DISP_INFO.bgn_ydot;
	xsize = (DISP_INFO.chr_size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = DISP_INFO.chr_size & 0x0ff;							// Yのｻｲｽﾞ

	adr = c_tbl_adr + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	Dst_p = (U2b *)adr;

	cnt = *Dst_p++;
	cnt = (cnt>>8) & 0x0ff;								// 文字列長

	for( i=0 ; i < cnt ; i += 2 ) {						// ﾜｰﾄﾞ→ﾊﾞｲﾄ単位ｱｸｾｽ可能領域にｺﾋﾟｰ
		cnv_wk = *Dst_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//文字ｺｰﾄﾞの設定
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
															//半角
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = DISP_INFO.bgn_ydot;
		}
		else {												//全角
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					//全角左側
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					//全角右側
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k+1] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k += 2;
			}
			i++;
			xdot_bak += xsize * 2 * 8;
			xdot = xdot_bak;
			ydot = DISP_INFO.bgn_ydot;
		}
	}
#endif
}


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*					LCD格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*					フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		なし
*  Note		:
*
********************************************************************************
*/
void	disp_moji_s_color(
			UNs len,
			UNs x,
			UNs y,
			UNs c_col, 
			UNs b_col, 
			UNs size, 
			UNs *g_adr_p, 
			UNb Lcd_p[][PanelWidth]
			)
{
	UNi		i, j, k, l, flg;
	UNs		cnt, cnv_wk;
	UNs		xdot, ydot, xdot_bak, ydot_bak;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNb		moji[E_line], dot_wk[32], wk1b;
	UNl		*Src_p, *Dst_p, wkl;

	flg = 0;

	cnt = len;											//文字数　算出
	xsize = (size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = size & 0x0ff;						// Yのｻｲｽﾞ

	/******** 背景色塗り潰し *********/
#ifdef	OLD_RIF
	x_dot_leng = xsize * cnt * 8;				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = ysize * 16;					// ｻｲｽﾞ × 16dot／1文字
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
#endif
#ifdef	NEW_RIF
	x_dot_leng = (xsize * cnt * 8);				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = (ysize * 16);					// ｻｲｽﾞ × 16dot／1文字
	xdot = x;
	wkl = b_col;
	wkl |= wkl<<8;
	wkl |= wkl<<16;
	
	xcnt = ((~xdot+1) & 0x03);
	x_dot_leng -= xcnt;
	for ( ; xcnt>0; xcnt--,xdot++)				// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
	for ( xcnt=x_dot_leng; xcnt>3; xcnt-=4,xdot+=4 )			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		Dst_p = (UNl *)&Lcd_p[ydot][xdot];
		for (ycnt=y_dot_leng;  ycnt>0; ycnt-- )		// Y方向塗り潰し
		{
			*Dst_p = wkl ;
			Dst_p += (PanelWidth/4);
		}
	}
	for ( ; xcnt>0; xcnt--,xdot++)				// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
#endif

	/******** 文字表示 *********/
	xdot = x;
	ydot = y;

	for( i=0 ; i < cnt ; i += 2 ) {						//ﾜｰﾄﾞ→ﾊﾞｲﾄ単位ｱｸｾｽ可能領域にｺﾋﾟｰ
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//文字ｺｰﾄﾞの設定
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
															//半角
			for ( l=0, k=0; l<16; l++ ) {
				switch (xsize)
				{
					case 1:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=1;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					case 2:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=2;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					case 4:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=4;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					default:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
									for ( xcnt=0; xcnt<xsize; xcnt++ ) {
										Lcd_p[ydot][xdot] = c_col;
										xdot++;
									}
								}
								else {
									for ( xcnt=0; xcnt<xsize; xcnt++ ) {
										xdot++;
									}
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
		else {												//全角
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					//全角左側
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								Lcd_p[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					//全角右側
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k+1] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								Lcd_p[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k += 2;
			}
			i++;
			xdot_bak += xsize * 2 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*					LCD格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*					フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		なし
*  Note		:
*
********************************************************************************
*/
#ifdef	OLD_RIF
void	disp_moji_s_rif(
			UNs len,
			UNs x,
			UNs y,
			UNs size
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;

	xsize = (size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = size & 0x0ff;						// Yのｻｲｽﾞ

	/******** 背景色塗り潰し *********/
	x_dot_leng = xsize * len * 8;				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = ysize * 16;					// ｻｲｽﾞ × 16dot／1文字
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			LCD_VRAM[ydot][xdot] = LCD_VBASE[ydot][xdot];
		}
	}
}
#endif

#ifdef	NEW_RIF
void	disp_moji_s_rif(
			UNs len,
			UNs x,
			UNs y,
			UNs size
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNl		*Src_p, *Dst_p;

	xsize = (size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = size & 0x0ff;						// Yのｻｲｽﾞ

	x_dot_leng = (xsize * len * 8);				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ
	y_dot_leng = (ysize * 16);						// ｻｲｽﾞ × 16dot／1文字
	xdot = x;

	xcnt = ((~xdot+1) & 0x03);
	x_dot_leng -= xcnt;
	for ( ; xcnt>0; xcnt--,xdot++)				// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			LCD_VRAM[ydot][xdot] = LCD_VRAM[ydot][xdot];
		}
	}
	for ( xcnt=x_dot_leng; xcnt>3; xcnt-=4,xdot+=4 )			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		Src_p = (UNl *)&LCD_VBASE[ydot][xdot];
		Dst_p = (UNl *)&LCD_VRAM[ydot][xdot];
		for (ycnt=y_dot_leng;  ycnt>0; ycnt-- )		// Y方向塗り潰し
		{
			*Dst_p = *Src_p ;
			Src_p += (PanelWidth/4);
			Dst_p += (PanelWidth/4);
		}
	}
	for ( ; xcnt>0; xcnt--,xdot++)				// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			LCD_VRAM[ydot][xdot] = LCD_VRAM[ydot][xdot];
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*					LCD格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*					フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		なし
*  Note		:
*
********************************************************************************
*/
void	disp_moji_s_paint(
			UNs len,
			UNs x,
			UNs y,
			UNs col,
			UNs size,
			UNb Lcd_p[][PanelWidth]
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;

	xsize = (size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = size & 0x0ff;						// Yのｻｲｽﾞ

	/******** 指定色塗り潰し *********/
	x_dot_leng = xsize * len * 8;				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = ysize * 16;					// ｻｲｽﾞ × 16dot／1文字
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			Lcd_p[ydot][xdot] = col;
		}
	}
}


/*
********************************************************************************
*
*	カーソルの制御情報テーブルセット
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_CSRtbl_set(void)
{
	CSR_TBL_TDEF	*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k, wk;

	CSR_CNT = CSR_CNT1 = GAMENn_HEAD.csr_cnt;

	if (GAMENn_HEAD.csr_cnt == 0)	return;						// カーソルある？

	ccnt = GAMENn_HEAD.csr_cnt;									// カーソル個数
	g_top = GAMENN_CSR_INF_ADR;									// カーソル表示情報先頭ｱﾄﾞﾚｽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		d_p = &CSR_buff[k];													//格納ポインタセット
		adr = (DISP_INFO.link_no-1) * CTL_CSR_TBL_SIZE + (U4b)&ALLTBL_CSTBL;
		v_p = (CSR_TBL_TDEF *)adr;

//		d_p->XY_POS		= v_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d_p->DATA_NO	= v_p->DATA_NO;				//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
		d_p->SV_MAX		= v_p->SV_MAX;				//設定値ﾃｰﾌﾞﾙ個数
		d_p->SW_MAX		= v_p->SW_MAX;				//SWﾃｰﾌﾞﾙ個数
		d_p->CARA_NO	= DISP_INFO.chr_no;			//ｶｰｿﾙ表示ｷｬﾗ種別（未使用）
		d_p->MOVE_NO	= v_p->MOVE_NO;				//画面移動番号
		d_p->TOK_NO		= v_p->TOK_NO;				//特殊番号(B0:ｶｰｿﾙ無し)
		d_p->YOBI1		= v_p->YOBI1;				//予備１
		d_p->YOBI2		= v_p->YOBI2;				//予備２
		d_p->SW56_UP	= v_p->SW56_UP;				//SW56上段ｷｬﾗｸﾀ
		d_p->SW5_DN		= v_p->SW5_DN;				//SW5下段ｷｬﾗｸﾀ
		d_p->SW6_DN		= v_p->SW6_DN;				//SW6下段ｷｬﾗｸﾀ
		d_p->SW5_SUB	= v_p->SW5_SUB;				//SW5ﾃﾞｰﾀ処理番号
		d_p->SW6_SUB	= v_p->SW6_SUB;				//SW6ﾃﾞｰﾀ処理番号
		d_p->YOBI3		= v_p->YOBI3;				//予備３
		d_p->AKI		= v_p->AKI;					//空き
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//表示Xﾄﾞｯﾄ位置
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//表示Yﾄﾞｯﾄ位置
		d_p->SIZE		= DISP_INFO.chr_size;		//文字サイズ
		d_p->C_COL		= DISP_INFO.chr_col;		//文字色
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//背景色
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//背景色

		adr = CSR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (U2b *)adr;
		wk = *hrom;
		wk = (wk>>8) & 0x0ff;					// 文字列長
		d_p->M_LEN		= wk;					//表示文字数(半角で)
		d_p->XY_POS		= wk<<10;				//表示文字数(半角で)
		d_p->XY_POS		|= (d_p->X_POS/8)<<4;	//表示桁(半角で)
		d_p->XY_POS		|= d_p->Y_POS/16;		//表示行(半角で)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	設定値の制御情報テーブルセット
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_SVtbl_set(void)
{
	SV_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;

	SV_CNT = GAMENn_HEAD.svp_cnt;

	if (GAMENn_HEAD.svp_cnt == 0)	return;						// カーソルある？

	ccnt = GAMENn_HEAD.svp_cnt;									// カーソル個数
	g_top = GAMENN_SVP_INF_ADR;									// カーソル表示情報先頭ｱﾄﾞﾚｽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		d_p = &SV_buff[k];													//格納ポインタセット
		adr = (DISP_INFO.link_no-1) * CTL_SVP_TBL_SIZE + (U4b)&ALLTBL_SVTBL;
		v_p = (SV_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//設定値表示のX,Y軸
		d_p->AKI		= v_p->AKI;					//空き
		d_p->DATA_ADR	= v_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d_p->SUB_NO		= v_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d_p->GRP_NO		= v_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d_p->TOK_FLG	= v_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d_p->BYTE_NO	= v_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d_p->TEN_POS	= v_p->TEN_POS;				//少数点の位置
		d_p->CSR_NO		= v_p->CSR_NO;				//ｶｰｿﾙ認識番号
		d_p->DSP_NO		= v_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
		d_p->SAVE_NO	= v_p->SAVE_NO;				//格納ﾌﾗｸﾞ
		d_p->YOBI_NO	= v_p->YOBI_NO;				//予備
		d_p->AKI2		= v_p->AKI2;				//空き
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//表示Xﾄﾞｯﾄ位置
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//表示Yﾄﾞｯﾄ位置
		d_p->M_LEN		= DISP_INFO.chr_no;			//表示文字数(半角で)
		d_p->SIZE		= DISP_INFO.chr_size;		//文字サイズ
		d_p->C_COL		= DISP_INFO.chr_col;		//文字色
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//背景色
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//背景色

		d_p->TOK_FLG	= ( d_p->TOK_FLG & ~BIT_2 ) | (( DISP_INFO.option << 2 ) & BIT_2 );		//ｵﾌﾟｼｮﾝ（半角／全角）

		d_p->XY_POS		= DISP_INFO.chr_no<<10;		//表示文字数(半角で)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	実測値の制御情報テーブルセット
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_PVtbl_set(void)
{
	PV_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;

	PV_CNT = GAMENn_HEAD.pvp_cnt;

	if (GAMENn_HEAD.pvp_cnt == 0)	return;						// カーソルある？

	ccnt = GAMENn_HEAD.pvp_cnt;									// カーソル個数
	g_top = GAMENN_PVP_INF_ADR;									// カーソル表示情報先頭ｱﾄﾞﾚｽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		d_p = &PV_buff[k];													//格納ポインタセット
		adr = (DISP_INFO.link_no-1) * CTL_PVP_TBL_SIZE + (U4b)&ALLTBL_PVTBL;
		v_p = (PV_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d_p->AKI		= v_p->AKI;					//空き
		d_p->DATA_ADR	= v_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d_p->SUB_NO		= v_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d_p->GRP_NO		= v_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d_p->TOK_FLG	= v_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d_p->BYTE_NO	= v_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d_p->TEN_POS	= v_p->TEN_POS;				//少数点の位置
		d_p->YOBI1		= v_p->YOBI1;				//予備１
		d_p->YOBI2		= v_p->YOBI2;				//予備２
		d_p->AKI2		= v_p->AKI2;				//空き
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//表示Xﾄﾞｯﾄ位置
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//表示Yﾄﾞｯﾄ位置
		d_p->M_LEN		= DISP_INFO.chr_no;			//表示文字数(半角で)
		d_p->SIZE		= DISP_INFO.chr_size;		//文字サイズ
		d_p->C_COL		= DISP_INFO.chr_col;		//文字色
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//背景色
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//背景色

		d_p->TOK_FLG	= ( d_p->TOK_FLG & ~BIT_2 ) | (( DISP_INFO.option << 2 ) & BIT_2 );		//ｵﾌﾟｼｮﾝ（半角／全角）

		d_p->XY_POS		= DISP_INFO.chr_no<<10;		//表示文字数(半角で)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	ＳＷ－ＬＡＭＰの制御情報テーブルセット
*
*	Input	:		なし
*	Return	: 		なし
*
********************************************************************************
*/
void	Gamenn_SWLtbl_set(void)
{
	SW_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k, wk;

	SW_CNT = SW_CNT1 = GAMENn_HEAD.swl_cnt;

	if (GAMENn_HEAD.swl_cnt == 0)	return;						// カーソルある？

	ccnt = GAMENn_HEAD.swl_cnt;									// カーソル個数
	g_top = GAMENN_SWL_INF_ADR;									// カーソル表示情報先頭ｱﾄﾞﾚｽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//文字列情報ををＲＡＭにコピー
		{
			*hram = *hrom;
		}

		d_p = &SW_buff[k];													//格納ポインタセット
		adr = (DISP_INFO.link_no-1) * CTL_SWL_TBL_SIZE + (U4b)&ALLTBL_SWTBL;
		v_p = (SW_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//実測値表示のX,Y軸
		d_p->AKI		= v_p->AKI;					//空き
		d_p->DATA_ADR	= v_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d_p->SUB_NO		= v_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d_p->GRP_NO		= v_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
		d_p->TOK_FLG	= v_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d_p->CHG_NO		= v_p->CHG_NO;				//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
		d_p->CSR_NO		= v_p->CSR_NO;				//この設定値の属するｶｰｿﾙ認識番号
		d_p->DSP_NO		= v_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
		d_p->CARA_NO	= DISP_INFO.chr_no;			//表示用ｷｬﾗｸﾀ番号
		d_p->KAN_NO		= v_p->KAN_NO;				//関連ﾊﾞｲﾄ
		d_p->KAN_ADR	= v_p->KAN_ADR;				//関連ｱﾄﾞﾚｽ
		d_p->SAVE_NO	= v_p->SAVE_NO;				//格納ﾌﾗｸﾞ
		d_p->YOBI2		= v_p->YOBI2;				//予備２
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//表示Xﾄﾞｯﾄ位置
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//表示Yﾄﾞｯﾄ位置
		d_p->SIZE		= DISP_INFO.chr_size;		//文字サイズ
		d_p->C_COL		= DISP_INFO.chr_col;		//文字色
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//背景色
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//背景色

		adr = SWL_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (U2b *)adr;
		wk = *hrom;
		wk = (wk>>8) & 0x0ff;					// 文字列長
		d_p->M_LEN		= wk;					//表示文字数(半角で)
		d_p->XY_POS		= wk<<10;				//表示文字数(半角で)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set
*  Function Name:	ＳＷキャラクタ表示処理
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*					表示用ｷｬﾗｸﾀ番号
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*  Return	: 		なし
*  Note		:
********************************************************************************
*/
//2014/09/02	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth])
void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth], UNs off)
{
	UNs		j, *buff_p, *g_p, len, b_col;
	U4b		adr;

	adr =  SWL_TABLE_ADR + ((c_no-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	g_p = (U2b *)adr;
	
	len = *g_p++;
	len >>= 8;

	buff_p = SW_buff[T_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	j = SW_buff[T_no].CHG_NO;						//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置

	if(off) {										//強制OFF表示		2014/09/02
		j=0;
	}

	if(*buff_p & j) {								//ＯＮ状態？
		g_p += (8/2);
		b_col = SW_buff[T_no].B_COL2;
	}
	else {
		b_col = SW_buff[T_no].B_COL1;
	}
	disp_moji_s_color(
		len, 
		SW_buff[T_no].X_POS, 
		SW_buff[T_no].Y_POS, 
		SW_buff[T_no].C_COL,
		b_col,
		SW_buff[T_no].SIZE, 
		g_p, 
		Lcd_p
		);
	if ( SVPV_LCD_FLG == 0) {
		disp_moji_s_rif (
			SW_buff[T_no].M_LEN, 
			SW_buff[T_no].X_POS, 
			SW_buff[T_no].Y_POS, 
			SW_buff[T_no].SIZE
			);
	}
}


/*
********************************************************************************
*
*	指定スイッチNo.の文字列表示
*
*	Input	:		なし
*	Return	: 		なし
*
*	履 歴	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	Disp_SW(UNi t_no)
{
	UNs		j, *buff_p, *g_p, len, b_col;
	U4b		adr;

	adr =  SWL_TABLE_ADR + ((SW_buff[t_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	g_p = (U2b *)adr;
	
	len = *g_p++;
	len >>= 8;

	if ( ( SW_buff[t_no].SUB_NO & BIT_F) == 0 ) {
		buff_p = SW_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		j = SW_buff[t_no].CHG_NO;						//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置

		if(*buff_p & j) {								//ＯＮ状態？
			g_p += (8/2);
			b_col = SW_buff[t_no].B_COL2;
		}
		else {
			b_col = SW_buff[t_no].B_COL1;
		}
		disp_moji_s_color(
			len, 
			SW_buff[t_no].X_POS, 
			SW_buff[t_no].Y_POS, 
			SW_buff[t_no].C_COL,
			b_col,
			SW_buff[t_no].SIZE, 
			g_p, 
			LCD_VRAM
			);
	}
	else {
		disp_moji_s_paint(
			SW_buff[t_no].M_LEN,		//半角桁数
			SW_buff[t_no].X_POS,		//X始点
			SW_buff[t_no].Y_POS,		//Y始点
			GAMENn_HEAD.scr_col,		//塗潰し色
			SW_buff[t_no].SIZE,			//X2倍/Y2倍
			LCD_VRAM
			);
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set_dan
*  Function Name:	ＳＷキャラクタ表示処理(段取り用)
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		: V05a MAKE
********************************************************************************
*/
void	SWchg_set_dan_color(UNi T_no, UNb Lcd_p[][PanelWidth])
{
	UNs		j, k, *buff_p;
	UNs		len, col;
	UNl		adr;
	UNs		*hrom;

	adr =  SWL_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	hrom = (UNs *)adr;
	len = *hrom++;
	len >>= 8;
	col = SW_buff[T_no].B_COL1;						/* 背景色			*/

	buff_p = SW_buff[T_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	j = SW_buff[T_no].CHG_NO;						//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
	k = *buff_p;									//必要なビットだけを抽出
	k &= j;

	if(k==0 || k==j ) {								//０＝スペース || ３＝スペース
		hrom = &SPACE_ASCII_40[0];
		col = GAMENn_HEAD.scr_col;
	}
	else{
		j &= 0x00aa;
		if( k & j) {
			hrom += SWL_DATA_SIZE/2;				//ＯＮの時は全角４後ろに有るので
			col = SW_buff[T_no].B_COL2;				/* 背景色			*/
		}
	}

	disp_moji_s_color(
		len,									/* ｷｬﾗｸ長			*/
		SW_buff[T_no].X_POS,					/* 書出しX位置		*/
		SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
		SW_buff[T_no].C_COL,					/* 文字色			*/
		col,									/* 背景色			*/
		SW_buff[T_no].SIZE,						/* 文字ｻｲｽﾞ			*/
		hrom,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE								/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif (
		len,									/* ｷｬﾗｸ長			*/
		SW_buff[T_no].X_POS,					/* 書出しX位置		*/
		SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
		SW_buff[T_no].SIZE						/* 文字ｻｲｽﾞ			*/
		);
}


/*
********************************************************************************
*  Module Name:		CSR_disp
*  Function Name:	カーソル表示
*  Input	:		
*  Return	: 		なし
*  Note		:
********************************************************************************
*/
void	CSR_disp_color(void)
{
	UNs		t_no, c_no;
	UNl		adr;
	UNs		*g_p;

	t_no = CSR_TBL_POS_NOW;

	if( (CSR_BAK_X_POS == CSR_buff[t_no].X_POS) &&
			 (CSR_BAK_Y_POS == CSR_buff[t_no].Y_POS) ) {	//カーソルポジションデータ更新 ?
		return;												//カーソル位置が一緒の場合は終了
	}

	if( CSR_BAK_X_POS != 0xffff &&							//前回カーソルポジションデータなし
			00 == (CSR_buff[t_no].TOK_NO & BIT_0) &&		//特殊番号(B0:ｶｰｿﾙ無し)
			00 != CSR_BAK_M_LEN ) {							//ｶｰｿﾙ長=０？

		disp_moji_s_color(
			CSR_BAK_M_LEN,
			CSR_BAK_X_POS,
			CSR_BAK_Y_POS,
			CSR_BAK_C_COL,
			CSR_BAK_B_COL,
			CSR_BAK_SIZE,
			CSR_BAK_G_P,
			LCD_VBASE
			);
		disp_moji_s_rif(
			CSR_BAK_M_LEN,
			CSR_BAK_X_POS,
			CSR_BAK_Y_POS,
			CSR_BAK_SIZE
			);
	}

	if( 00 != CSR_buff[t_no].M_LEN ) {					//ｶｰｿﾙ長=０？
		if( 0 == (CSR_buff[t_no].TOK_NO & BIT_0)) {			//特殊番号(B0:ｶｰｿﾙ無し)

			c_no = CSR_buff[t_no].SW56_UP;							//SW56上段ｷｬﾗｸﾀ
			if( c_no >= 0x80 && c_no < 0xc5 ) {						//0x80 ≦ 上段ｷｬﾗｸﾀ ＜ 0xc5
				g_p = SW56_Cam_Name_Tbl[c_no - 0x80];
				if( (c_no >= 0xa0) && (c_no < 0xb5) &&			//現在の名称表示処理？  CSR_SW56_UP=0AAH
					 (c_no != 0xaa) && (MLD_100_GNO != 0) ) {	//１１～１００型の名称＆メモ表示

					if( c_no < 0xab ){							//型管理番号を１０倍して型管理番号を細工する
						c_no -= 0xa0;							//名称表示
						g_p = KAT_sv_name_tbl[c_no+(MLD_100_GNO*10)+1];
					}
					else{
						c_no -= 0xab;							//メモ表示
						g_p = KAT_sv_memo_tbl[c_no+(MLD_100_GNO*10)+1];
					}
				}
			}
			else
			{
				adr = CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				adr += CSR_HEAD_SIZE;
				g_p = (U2b *)adr;
			}

			CSR_BAK_M_LEN	= CSR_buff[t_no].M_LEN;
			CSR_BAK_X_POS	= CSR_buff[t_no].X_POS;
			CSR_BAK_Y_POS	= CSR_buff[t_no].Y_POS;
			CSR_BAK_C_COL	= CSR_buff[t_no].C_COL;
			CSR_BAK_B_COL	= CSR_buff[t_no].B_COL2;
			CSR_BAK_SIZE	= CSR_buff[t_no].SIZE;
			CSR_BAK_G_P = g_p;
			disp_moji_s_color(
				CSR_BAK_M_LEN,
				CSR_BAK_X_POS,
				CSR_BAK_Y_POS,
				CSR_BAK_C_COL,
				CSR_BAK_B_COL,
				CSR_BAK_SIZE,
				CSR_BAK_G_P,
				LCD_VBASE
				);
			disp_moji_s_rif(
				CSR_BAK_M_LEN,
				CSR_BAK_X_POS,
				CSR_BAK_Y_POS,
				CSR_BAK_SIZE
				);
			CSR_BAK_B_COL	= CSR_buff[t_no].B_COL1;
		}
	}
}

void	LCD_All_Disp(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[0][0];
	Dis_p = (UNl *)&LCD_VRAM[0][0];

	cnt =(PanelWidth * PanelHeight) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
//		Src_p++;
//		Dis_p++;
	}
}


void	WIN_All_Disp(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	if( (42 <= WINDOW_NO) && (WINDOW_NO <= 47) )		//V06c
	{	//作業開始/終了WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-Window2Height][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-Window2Height][0];
		cnt =(PanelWidth * Window2Height) / 4;
	}

	else if( (51 <= WINDOW_NO) && (WINDOW_NO <= 58) )		//V06c
	{	//作業開始/終了WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-Window2Height][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-Window2Height][0];
		cnt =(PanelWidth * Window2Height) / 4;
	}

	else
	{	//通常WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-WindowHeight][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-WindowHeight][0];
		cnt =(PanelWidth * WindowHeight) / 4;
	}

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vabse_to_vmon1
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション設定部の表示ＶＢＡＳＥをワーク１へ退避
*					（モーション画面を表示するときの小細工（やもをえず））
********************************************************************************
*/
void	mmon_vabse_to_vmon1(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[6*16*2][0];
	Dis_p = (UNl *)&LCD_VMON1[0][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}

/*
********************************************************************************
*  Module Name:		mmon_vmon1_to_vbase
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション設定部の表示ワーク１をＶＲＡＭへ戻す
*					（モーション画面を表示するときの小細工（やもをえず））
********************************************************************************
*/
void	mmon_vmon1_to_vbase(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON1[0][0];
	Dis_p = (UNl *)&LCD_VBASE[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vmon2_to_vbase
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション設定部の表示ワークををＶＢＡＳＥへ戻す
*					（モーション画面を表示するときの小細工（やもをえず））
********************************************************************************
*/
void	mmon_vmon2_to_vbase(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON2[0][0];
	Dis_p = (UNl *)&LCD_VBASE[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vabse_to_vmon2
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション設定部の表示ＶＢＡＳＥをワーク２へ
*					（モーション画面時、行程数を変更したときの表示用）
********************************************************************************
*/
void	mmon_vabse_to_vmon2(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[6*16*2][0];
	Dis_p = (UNl *)&LCD_VMON2[0][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vmon2_to_vram
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション設定部の表示ワーク２をＶＲＡＭへ
*					（モーション画面時、行程数を変更したときにワークで編集し表示ＶＲＡＭ領域へ）
********************************************************************************
*/
void	mmon_vmon2_to_vram(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON2[0][0];
	Dis_p = (UNl *)&LCD_VRAM[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		vmon2_line_erase
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーション画面時、不要行程行を削除
********************************************************************************
*/
void	vmon2_line_erase(UNs line_no)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt, col, wk;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	Dis_p = (UNl *)&LCD_VMON2[(line_no-6)*16*2][0];

	cnt = (PanelWidth * (1*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = col;
	}
}


/*
********************************************************************************
*  Module Name:		Disp_seidouseinou
*  Function Name:	制動性能キャラクタ表示
*  Input	:		通常文字表示 or 制動性能文字表示
*					LCD格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
void	Disp_seidouseinou( UNs inf, UNb Lcd_p[][PanelWidth] )
{
	U4b		g_top, adr;
	U2b		*hrom, *hram;
	U2b		i, len;

	if (inf==0)
	{
		disp_moji_s_rif (
			10,									/* ｷｬﾗｸ長			*/
			0,									/* 書出しX位置		*/
			0,									/* 書出しY位置		*/
			0x202								/* 文字ｻｲｽﾞ			*/
			);
	}
	else
	{
		adr = CHR_TABLE_ADR + ((372-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (U2b *)adr;
		len = *hrom++;
		len >>= 8;

		disp_moji_s_color(
			10,									/* ｷｬﾗｸ長			*/
			0,									/* 書出しX位置		*/
			0,									/* 書出しY位置		*/
			COL_BLACK,							/* 文字色			*/
			COL_GREEN,							/* 背景色			*/
			0x202,								/* 文字ｻｲｽﾞ			*/
			hrom,								/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			Lcd_p								/* 表示ﾒﾓﾘ			*/
			);
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_sikaku1
*  Function Name:	枠付き四角表示（左から右へ、上から下へ、描画する）
*  Input	:		書き出しX位置
*					書き出しY位置
*					X長さ
*					Y長さ
*					枠の色
*					中の色
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2010-09-10	V06
********************************************************************************
*/
void	Dsp_sikaku1 (UNs startX, UNs startY, UNs lngX, UNs lngY, UNs col_waku, UNs col_naka)
{
	UNs	xdot, ydot;
	UNs	xcnt, ycnt;

	ydot = startY;

	for (ycnt=0; ycnt<lngY; ycnt++, ydot++)
	{
		xdot = startX;

		if ( (ycnt==0) || (ycnt==(lngY-1)) )
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				LCD_VRAM[ydot][xdot] = col_waku;
			}
		}
		else
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				if ( (xcnt==0) || (xcnt==(lngX-1)) )
				{
					LCD_VRAM[ydot][xdot] = col_waku;
				}
				else
				{
					LCD_VRAM[ydot][xdot] = col_naka;
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_sikaku2
*  Function Name:	枠付き四角表示（左から右へ、下から上へ、描画する）
*  Input	:		書き出しX位置
*					書き出しY位置
*					X長さ
*					Y長さ
*					枠の色
*					中の色
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2010-09-10	V06
********************************************************************************
*/
void	Dsp_sikaku2 (UNl startX, UNl startY, UNl lngX, UNl lngY, UNs col_waku, UNs col_naka, UNl Ylim)
{
	UNs	xdot, ydot;
	UNs	xcnt, ycnt;

	ydot = startY;

	for (ycnt=0; ycnt<lngY; ycnt++, ydot--)
	{
		xdot = startX;

		if (ydot < Ylim)		break;

		if ( (ycnt==0) || (ycnt==(lngY-1)) )
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				LCD_VRAM[ydot][xdot] = col_waku;
			}
		}
		else
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				if ( (xcnt==0) || (xcnt==(lngX-1)) )
				{
					LCD_VRAM[ydot][xdot] = col_waku;
				}
				else
				{
					LCD_VRAM[ydot][xdot] = col_naka;
				}
			}
		}
	}
}


/****************************************************************************/
/*																			*/
/*	ドットデータセット		：	グラフ用ドットデータをセットする。			*/
/*																			*/
/*		Ｘ－Ｙ座標２点で示されるライン（ドットデータ）を描画する。			*/
/*																			*/
/****************************************************************************/
void	Disp_Line	(UNl X1, UNl Y1, UNl X2, UNl Y2, UNs col)
{
	UNs		i;
	UNs		bt;
	UNs		xb,		yb;
	UNs		cnt,	db;
	UNs		wb,		zb;
	UNs		tb,		nb,		hb;
	UNs		x_dif,	y_dif;
	UNs		minus;
	UNs		temp;
	UNs		rate_0;
	UNl		wkl;


//	先頭のバイト位置、ビット位置を算出 ///////////////////////////////////////
	yb = Y1;
	xb = X1;
	bt = col;

//	タテ線、ヨコ線処理 ///////////////////////////////////////////////////////
	if (X1 == X2){									/* ﾀﾃ線 X軸方向変化なし	*/
		if (Y1 == Y2){								/* Y軸方向変化なし		*/
			LCD_VRAM[yb][xb] = bt;						/* 1 ﾄﾞｯﾄ座標 ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y軸 下方向変化		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				LCD_VRAM[yb+nb][xb] = bt;			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}else{										/* Y軸 上方向変化		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				LCD_VRAM[yb-nb][xb] |= bt;			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 対応なし		*/

	if (Y1 == Y2){									/* ﾖｺ線 Y軸方向変化なし	*/
		for (i=X1; i<=X2; i++){						/* X軸のﾋﾞｯﾄ数繰り返す	*/
			LCD_VRAM[yb][xb] = bt;					/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			xb += 1;								/* 次ﾊﾞｲﾄへ移動			*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	通常の線（ななめ線）描画処理 /////////////////////////////////////////////
	if (Y1 < Y2){									/* 描画方向を求める		*/
		y_dif = (Y2 - Y1);				/* 600倍で演算する		*/
		x_dif = (X2 - X1);				/* X軸のﾋﾞｯﾄ変化数算出	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<X2; )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				yb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<X2; )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					yb++;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
	else
	{											/* max 95 * 600 = 57000	*/
		y_dif = (Y1 - Y2);				/* 600倍で演算する		*/
		x_dif = (X2 - X1);				/* X軸のﾋﾞｯﾄ変化数算出	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<X2; )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				yb--;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<X2; )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					yb--;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb--)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
}


/****************************************************************************/
/*																			*/
/*	ドットデータセット		：	グラフ用ドットデータをセットする。			*/
/*																			*/
/*		Ｘ－Ｙ座標２点で示されるライン（ドットデータ）を描画する。			*/
/*																			*/
/****************************************************************************/
void	Disp_Line_Box	(UNs X1, UNs Y1, UNs X2, UNs Y2, UNs col)
{
	UNs		i;
	UNs		xb, yb;

	yb = Y1;
	xb = X1;

	for (i=X2; i!=0; i--, xb++)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 ﾄﾞｯﾄ座標 ON		*/
	}
	for (i=Y2; i!=0; i--, yb++)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 ﾄﾞｯﾄ座標 ON		*/
	}
	for (i=X2; i!=0; i--, xb--)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 ﾄﾞｯﾄ座標 ON		*/
	}
	for (i=Y2; i!=0; i--, yb--)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 ﾄﾞｯﾄ座標 ON		*/
	}

}


