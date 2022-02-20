/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			表　示　関　数															*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-21
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_addr.h"							//参照変数定義
#include "ssc_ver1.h"
#include "ssc_dpram_seq_ext.h"					//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	GENGO_chg(UNi);							//第２カ国語切替え処理

void	Disp_line(UNs, UNs, UNs, UNs);			//画面表示用 1行表示
void	Disp_moji(UNs, UNs *, UNs);				//文字表示
void	Disp_char(UNs, UNs, UNs, UNs *, UNs);	//ﾄﾞｯﾄ表示

void	disp_all_s(UNs, UNs, UNs);				//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
void	disp_line_s(UNs, UNs *, UNs *);			//1行表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

void	disp_memset(UNs, UNs *, UNs);			//表示用領域を指定ﾃﾞｰﾀで設定
UNi		disp_memnot(UNs, UNs *);				//表示用領域の指定ﾃﾞｰﾀを反転
void	disp_moji_s(UNs , UNs *, UNs *, UNi);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

UNi		code_dot_cnv(UNs, UNb *, UNi);			//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

UNs *	disp_adr_shr(UNs, UNs, UNs);			//画面のｷｬﾗｸﾀｱﾄﾞﾚｽの算出
void	disp_char_cpy(UNs, UNs, UNs, UNs *, UNs);	//画面のｷｬﾗｸﾀのｺﾋﾟｰ
UNs *	mess_adr_shr(UNi);						//メッセージ画面キャラクタアドレス検索

void	BCD_ASCII(UNl, UNb *);					//BCD→ASCII　変換
void	HEX_ASCII(UNl, UNb *);					//HEX→ASCII　変換	shima
UNl		BCD_HEX4(UNl);							//BCD→HEX　変換
UNl		HEX_BCD4(UNl);							//HEX→BCD　変換
void	Ascii_Sjis(UNs, UNb *, UNs *);			//Asciiｺｰﾄﾞ → 全角S-Jisｺｰﾄﾞ　変換
UNs		jiscnv(UNs);							//シフトＪＩＳ→ＪＩＳ変換

void	memset_word(UNs *, UNs, UNs);			//指定領域を指定ﾃﾞｰﾀにてﾜｰﾄﾞ単位で設定
void	memcpy_word(UNs *, UNs *, UNs);			//指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
extern	const	UNs	Han_MPtn_Table[256][16];		//半角文字パターン　テーブル



/*
********************************************************************************
*  Module Name:		GENGO_chg
*  Function Name:	言語切り換え機能
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2006-09-01	V01x
********************************************************************************
*/
void	GENGO_SEQ_CHG(void)
{
	UNs		seq_chg, seq_bit, seq_one ;

//V06m	seq_chg = seq_bit = SEQ_PAR_103 & (BIT_4+BIT_5);		// new
	seq_chg = seq_bit = (SEQ_PAR_103 & (BIT_4+BIT_5)) | (SEQ_PAR_113 & BIT_12);		// new

	seq_chg ^= GENG_SEQ_LST;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	GENG_SEQ_LST = seq_bit;

//V06m
//	if ( seq_one & BIT_4 )
//	{
//		SEQ_020_SV &= ~BIT_13;
//	}
//	if ( seq_one & BIT_5 )
//	{
//		SEQ_020_SV |= BIT_13;
//	}
	if ( seq_one & BIT_4 )
	{
//V06n		SV_LANGUAGE = 0;
		SV_LANGUAGE = 1;
		FRAM_csum_set();
	}
	else if ( seq_one & BIT_5 )
	{
//V06n		SV_LANGUAGE = 1;
		SV_LANGUAGE = 2;
		FRAM_csum_set();
	}
	else if ( seq_one & BIT_12 )
	{
//V06n		SV_LANGUAGE = 2;
		SV_LANGUAGE = 3;
		FRAM_csum_set();
	}

}


/*
********************************************************************************
*  Module Name:		GENGO_chg
*  Function Name:	第２カ国語切替え処理
*  Input	:		ﾌﾗｸﾞ：0:通常処理／0xff:初期化時
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-17
********************************************************************************
*/
void	GENGO_chg(UNi flag)
{
	UNs	*g_p, bf1, bf2;

//V06m	bf1 = (SEQ_020_SV & BIT_D);						//第二カ国語 切替え有り(1:英文)
	bf1 = (SEQ_PAR_050 & (BIT_12+BIT_13+BIT_14));

	bf2 = GENGO_CHG_LAST;
	GENGO_CHG_LAST = bf1;
	bf1 ^= bf2;

	if( 00 != bf1 ) {								//変化有り？

//V06m
//		if(SEQ_020_SV & BIT_D){						//第二カ国語 切替え有り(1:英文)？
//			g_p = (UNs *)E_GAMEN_TOP2;				//第二カ国語 基本情報ｱﾄﾞﾚｽ
//
//			if( 0x0000 == *g_p || 0xffff == *g_p ){	//第二カ国語 画面キャラクタ有り？
//				language_chg = 00;					//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(日本語)
//			}
//			else{									//YES
//				language_chg = E_2language;			//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(英文)
//			}
//		}
//		else {										//日本語
//			language_chg = 00;						//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(日本語)
//		}
		if (SEQ_PAR_050 & BIT_12) {
			language_chg = E_2language * 0;			//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(日本語)
		}
		else if (SEQ_PAR_050 & BIT_13) {
			language_chg = E_2language * 1;			//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(英語)
		}
		else if (SEQ_PAR_050 & BIT_14) {
			language_chg = E_2language * 2;			//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(中国語)
		}
		else {
			language_chg = E_2language * 0;			//ｵﾌｾｯﾄｱﾄﾞﾚｽの設定(日本語)
		}


#if (SIT_TYPE_SEL == TYPE_SIT3)
#else
		Gamen_Init();							//画面表示
		CAMname_pon_read();						//
#endif
		if( flag == 0 )								//通常処理？
		{
			GAM_CHG_WIN_NO_BAK = WINDOW_NO;

			GAMEN_disp();							//画面表示

			if ( (GAMEN_NO == 4) || (GAMEN_NO == 29) )	// V04a
			{
				GRAPH_INIT();						//グラフ描画初期処理
				GRAPH_DISP();						//グラフ描画処理
			}

			WINDOW_NO = GAM_CHG_WIN_NO_BAK;
			if (WINDOW_NO != 0)							// V04a
			{
				WIN_gamen_disp();					//画面表示
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Disp_line
*  Function Name:	画面表示用 1行表示
*  Input	:		画面番号
*					0:通常画面／1:ｳｲﾝﾄﾞｳ画面
*					LCDﾜｰｸの選択(0:LCD_WORK1/1:LCD_WORK2)
*					表示行数
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	Disp_line(UNs g_no, UNs g_sel, UNs l_no, UNs line_no)
{
	UNs	*g_adr_p, *dst_p;

	if( g_sel == 0 ){								//通常画面？
		g_no --;
		g_no &= 0x003f;								//画面番号を63以下に設定
		g_adr_p = (UNs *)E_GAMEN_TOP;				//画面キャラクタのアドレス算出
		g_adr_p += g_no * (0x280/2);
		g_adr_p += language_chg;					//第２カ国語切替え
		g_adr_p += line_no * (E_line/2);			//画面キャラクタのアドレス　更新
	}
	else{											//ｳｲﾝﾄﾞｳ画面
		if( g_no != 00 ) {
			g_no --;
		}
		g_no &= 0x001f;								//画面番号を31以下に設定
		g_adr_p = (UNs *)E_WINDOW_TOP;				//ウインドウ画面のアドレス算出
		g_adr_p += g_no * (0x180/2);
		g_adr_p += language_chg;					//第２カ国語切替え
		g_adr_p += (line_no-6) * (E_line/2);		//画面キャラクタのアドレス　更新
	}

	if(l_no == 0){									//LCDﾜｰｸの選択 0:LCD_WORK1 ?
		dst_p = &LCD_WORK1[0][0][0];
	}
	else{
		dst_p = &LCD_WORK2[0][0][0];
	}

	disp_line_s(line_no, g_adr_p, dst_p);			//1行表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
	Lcd_line(00, line_no, E_line_bf, dst_p);		//表行表示

}


/*
********************************************************************************
*  Module Name:		Disp_moji
*  Function Name:	文字表示
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*					フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-20
********************************************************************************
*/
void	Disp_moji(UNs xy_no, UNs *g_adr_p, UNs flg )
{

	disp_moji_s(xy_no, g_adr_p, &LCD_WORK1[0][0][0], flg);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	Lcd_cr(00, xy_no, &LCD_WORK1[0][0][0]);					//ｷｬﾗ単位表示

}


/*
********************************************************************************
*  Module Name:		Disp_char
*  Function Name:	ﾄﾞｯﾄ表示
*  Input	:		x_no ：表示 X軸(0～39)［桁］
*					Y_no ：表示 Y軸(0～14)［行］
*					c_cnt：ｶﾗﾑ数(1～40)［文字数］
*					*src_p：表示ﾃﾞｰﾀ･格納ｱﾄﾞﾚｽ
*					flg：フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-05
********************************************************************************
*/
void	Disp_char(UNs x_no, UNs y_no, UNs c_cnt, UNs *src_p, UNs flg)
{
	UNs		y, i, wk[40], *dst_p;

	if(flg == 0x00 ) {									//正常表示？
		y = (y_no << 4);								//Y軸(0～14)［行］* 16 = Y軸ﾄﾞｯﾄ位置
		dst_p = src_p;
		for(i = 16; i > 0 ; i--, y++) {
			Lcd_draw(00, x_no, y, c_cnt, src_p);		//ﾄﾞｯﾄ表示
			dst_p += (c_cnt << 1);						//次ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		}
	}
	else {												//反転表示
		y = (c_cnt << 4);
		dst_p = &wk[0];
		while(y--){
			*dst_p++ = ~(*src_p++);						//ﾃﾞｰﾀ反転
		}

		y = (y_no << 4);								//Y軸(0～14)［行］* 16 = Y軸ﾄﾞｯﾄ位置
		dst_p = &wk[0];
		for(i = 16; i > 0 ; i--, y++) {
			Lcd_draw(00, x_no, y, c_cnt, dst_p);		//ﾄﾞｯﾄ表示
			dst_p += (c_cnt << 1);						//次ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
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
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	disp_all_s(UNs g_no, UNs g_sel, UNs l_no)
{
	UNs	*g_adr_p, *dst_p, xy_no;
	UNi	i;

	if(l_no == 0){									//LCDﾜｰｸの選択 0:LCD_WORK1 ?
		dst_p = &LCD_WORK1[0][0][0];
	}
	else{
		dst_p = &LCD_WORK2[0][0][0];
	}

	if( g_sel == 0 ){								//通常画面？
		g_no --;
//shima		g_no &= 0x003f;								//画面番号を63以下に設定
		g_adr_p = (UNs *)E_GAMEN_TOP;				//画面キャラクタのアドレス算出
		g_adr_p += g_no * (0x280/2);
		g_adr_p += language_chg;					//第２カ国語切替え
		i = 0;										//行の設定

		for( ; i < 15 ; i++ ) {						//1画面分表示ﾃﾞｰﾀのｺﾋﾟｰ
			disp_line_s( i, g_adr_p, dst_p);		//1行表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			g_adr_p += (E_line/2);					//画面キャラクタのアドレス　更新
		}
	}
	else{											//ｳｲﾝﾄﾞｳ画面
		if( g_no != 00 ) {
			g_no --;
		}
		g_no &= 0x001f;								//画面番号を31以下に設定
		g_adr_p = (UNs *)E_WINDOW_TOP;				//ウインドウ画面のアドレス算出
		g_adr_p += g_no * (0x180/2);
		g_adr_p += language_chg;					//第２カ国語切替え

		xy_no = 0xa000;								//ｶｰｿﾙ長＝40文字
		if( g_sel & BIT_15 ) {
			xy_no = 0x5800;							//ｶｰｿﾙ長＝22文字
		}

		for( i = 6 ; i < 15 ; i++ ) {				//1画面分表示ﾃﾞｰﾀのｺﾋﾟｰ(行の設定)
			xy_no &= 0xfc00;
			xy_no |= (i & 0x000f);
			disp_moji_s(xy_no, g_adr_p, dst_p, 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			g_adr_p += (E_line/2);						//画面キャラクタのアドレス　更新
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_line_s
*  Function Name:	1行表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*  Input	:		表示行数
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	disp_line_s(UNs l_no, UNs *g_adr_p, UNs *Lcd_p)
{
	UNs		xy_no;

	xy_no = (l_no & 0x000f);
	xy_no |= 0xa000;								//ｶｰｿﾙ長＝40文字
	disp_moji_s(xy_no, g_adr_p, Lcd_p, 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

}


/*
********************************************************************************
*  Module Name:		disp_memset
*  Function Name:	表示用領域を指定ﾃﾞｰﾀで設定
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*			:		設定ﾃﾞｰﾀ
*
*  Return	: 		なし
*  Note		:	指定された表示用領域の先頭から、指定ﾃﾞｰﾀを指定文字数分設定する
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	disp_memset(UNs xy_no, UNs *Lcd_p, UNs s_dt )
{
	UNi	i, j, k;
	UNs	*Dst_p;

	i = xy_no & 0x000f;						//行のｱﾄﾞﾚｽ　算出
	i *= E_line_size;
	j = ( xy_no >> 4) & 0x003f;				//桁のｱﾄﾞﾚｽ　算出
	Lcd_p += i + j;							//LCD表示領域のｱﾄﾞﾚｽ設定

	i = 16;
	while(i--) {
		Dst_p = Lcd_p;
		k = ( xy_no >> 10);						//文字数　算出
		while(k--) {
			*Dst_p++ = (s_dt & 0x00ff);			//指定ﾃﾞｰﾀを指定文字数分設定
		}
		Lcd_p += E_next_dot;					//1文字の次dot位置数
	}
}


/*
********************************************************************************
*  Module Name:		disp_memnot
*  Function Name:	表示用領域の指定ﾃﾞｰﾀを反転
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		LCD格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		00:正常終了／ff：異常終了
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	disp_memnot(UNs xy_no, UNs *Lcd_p)
{
	UNi	i, j, k;
	UNs	*Dst_p, wk;

	i = xy_no & 0x000f;							//行のｱﾄﾞﾚｽ　算出
	i *= E_line_size;
	j = ( xy_no >> 4) & 0x003f;					//桁のｱﾄﾞﾚｽ　算出
	Lcd_p += i + j;								//LCD表示領域のｱﾄﾞﾚｽ設定

	k = ( xy_no >> 10);							//文字数　算出
	if( k == 00){
		return(0xff);
	}
	else {
		i = 16;
		while(i--) {
			Dst_p = Lcd_p;
			k = ( xy_no >> 10);					//文字数　算出
			while(k--) {						//指定ﾃﾞｰﾀを指定文字数分設定
				wk = ~(*Dst_p);					//ﾃﾞｰﾀの反転
				*Dst_p++ = (wk & 0x00ff);
			}
			Lcd_p += E_next_dot;				//1文字の次dot位置数
		}
	}
	return(0x00);
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
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	disp_moji_s(UNs xy_no, UNs *g_adr_p, UNs *Lcd_p, UNi flg)
{
	UNi	i, j, size;
	UNs	cnt, cnv_wk, *Dst_p;
	UNb	moji[E_line], dot_wk[32];

	cnt = xy_no >> 10;									//文字数　算出
	for( i=0 ; i < cnt ; i += 2 ) {						//ﾜｰﾄﾞ→ﾊﾞｲﾄ単位ｱｸｾｽ可能領域にｺﾋﾟｰ
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	i = xy_no & 0x000f;									//行のｱﾄﾞﾚｽ　算出
	i *= E_line_size;
	j = (xy_no >> 4) & 0x003f;							//桁のｱﾄﾞﾚｽ　算出
	Lcd_p += (i + j);									//LCD表示領域のｱﾄﾞﾚｽ設定

	for( i=0 ; i < cnt ; i++ ){
		cnv_wk = moji[i+1];								//文字ｺｰﾄﾞの設定
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
															//半角
			j = 0;
			size = 16;
			Dst_p = Lcd_p;
			while(size--) {
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*Dst_p = cnv_wk;
				Dst_p += E_next_dot;						//1文字の次dot位置数
			}
			Lcd_p ++;										//格納ﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ　更新
		}
		else {												//全角
			j = 0;
			size = 16;
			Dst_p = Lcd_p;
			while(size--) {
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*Dst_p = cnv_wk;
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*(Dst_p+1) = cnv_wk;
				Dst_p += E_next_dot;						//1文字の次dot位置数
			}
			Lcd_p ++;										//格納ﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ　更新
			Lcd_p ++;
			i++;											//+1
		}
	}
}


/*
********************************************************************************
*  Module Name:		code_dot_cnv	(旧：CARA_ONE_SET)
*  Function Name:	文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
*
*  Input	:		文字ｺｰﾄﾞ
*			:		格納ﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ(ﾊﾞｲﾄｱｸｾｽ領域)
*					フラグ：（0x00=正常表示／0xff:反転表示）
*
*  Return	: 		0:半角
*					1:全角
*
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-20
********************************************************************************
*/
UNi		code_dot_cnv(UNs d_cara, UNb *Dst_p, UNi flg)
{
#if (SIT_TYPE_SEL == TYPE_SIT3)
	UNb	*Src_p;
	UNb	*Dst_px;
#else
	UNs	*Src_p;
	UNs	*Dst_px;
#endif
	UNb	code1;
	UNs	*Srcw_p, d_cara_swap, dat;
	UNi	type, r_wk, size;

#if (SIT_TYPE_SEL == TYPE_SIT3)
	Dst_px = Dst_p;
#else
	Dst_px = (UNs *)Dst_p;
#endif

	code1 = d_cara & 0x00ff;
	if( code1 < 0x80 ) {						//半角コード？
		type = 00;								//Yes
	}
	else if(code1 < 0xA0) {						//全角コード？
		type = 01;								//Yes
	}
	else if(code1 < 0xE0) {						//半角コード？
		type = 00;								//Yes
	}
	else {
		type = 01;								//全角コード
	}

	d_cara_swap = ((d_cara<<8)&0xff00) | ((d_cara>>8)&0x0ff);	//swap
	if(0x0f040 <= d_cara_swap && d_cara_swap <= 0x0f594) {	//外字コード？		V01l
		type = 02;								//Yes
	}


	if(type == 01) {							//全角コード ?
	/**************** 漢字コードドット変換処理 ***************/
#if (SIT_TYPE_SEL == TYPE_SIT3)
		Src_p = kan_rom_set(jiscnv(d_cara));	//シフトＪＩＳ→ＪＩＳ変換→漢字ＲＯＭアドレスセット
#else
		Src_p = (UNs *)kan_rom_set(jiscnv(d_cara));	//シフトＪＩＳ→ＪＩＳ変換→漢字ＲＯＭアドレスセット
#endif

#if (SIT_TYPE_SEL == TYPE_SIT3)
			size = 32;						/* ﾃﾞｰﾀCopy */
#else
			size = 16;						/* ﾃﾞｰﾀCopy */
#endif
		if(flg == 0xff ) {					//反転表示？
			while( size-- ) {
//				*Dst_p++ = ~(*Src_p++);		//ﾋﾞｯﾄ反転
				*Dst_px++ = ~(*Src_p++);		//ﾋﾞｯﾄ反転
			}
		}
		else {								//正常表示
			while( size-- ) {
//				*Dst_p++ = *Src_p++;
				*Dst_px++ = *Src_p++;
			}
		}
		r_wk = 1;							//全角ｺｰﾄﾞ
	}

	else if(type == 02) {
	/**************** 外字コードドット変換処理 ***************/		//V01l
		Srcw_p = (UNs *)E_GAIZI_TOP;		//画面キャラクタのアドレス算出
		Srcw_p += (d_cara_swap-0xf040)*16;

		if(flg == 0xff ) {					//反転表示？
			size = 16;						/* ﾃﾞｰﾀCopy */
			while( size-- ) {
				dat = ~(*Srcw_p++);			//ﾋﾞｯﾄ反転
				*Dst_p++ = (dat>>8) & 0xff;
				*Dst_p++ = dat & 0xff;
			}
		}
		else {								//正常表示
			size = 16;						/* ﾃﾞｰﾀCopy */
			while( size-- ) {
				dat = *Srcw_p++;
				*Dst_p++ = (dat>>8) & 0xff;
				*Dst_p++ = dat & 0xff;
			}
		}
		r_wk = 1;							//全角ｺｰﾄﾞ
	}

	else {										//半角コード
	/**************** 半角コードドット変換処理 ***************/
		Srcw_p = &Han_MPtn_Table[code1][0];	//半角文字ﾊﾟﾀｰﾝﾃｰﾌﾞﾙ ｱﾄﾞﾚｽ算出

		if(flg == 0xff ) {					//反転表示？
			size = 16;						/* ﾃﾞｰﾀCopy */
			while( size-- ) {
				*Dst_p++ = ~(*Srcw_p++);	//ﾋﾞｯﾄ反転
			}
		}
		else {								//正常表示
			size = 16;						/* ﾃﾞｰﾀCopy */
			while( size-- ) {
				*Dst_p++ = *Srcw_p++;
			}
		}
		r_wk = 0;							//半角ｺｰﾄﾞ
	}

	return (r_wk);
}


/*
********************************************************************************
*  Module Name:		disp_adr_shr
*  Function Name:	画面のｷｬﾗｸﾀｱﾄﾞﾚｽの算出
*  Input	:		画面番号
*					行
*					桁(奇数は不可)
*
*  Return	: 		画面のｷｬﾗｸﾀの先頭ｱﾄﾞﾚｽ
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-22
********************************************************************************
*/
UNs *	disp_adr_shr(UNs g_no, UNs l_no, UNs k_no)
{
	UNs	*g_p;

	g_no --;
	g_no &= 0x003f;							//画面番号を63以下に設定
	g_p = (UNs *)E_GAMEN_TOP;				//画面キャラクタのアドレス算出
	g_p += g_no * (0x280/2);
	g_p += language_chg;					//第２カ国語切替え
	g_p += l_no * (E_line/2);				//画面キャラクタのアドレス　更新
	g_p += (k_no >> 1);						//画面キャラクタのアドレス　更新

	return(g_p);
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	画面のｷｬﾗｸﾀのｺﾋﾟｰ
*  Input	:		画面番号
*					行
*					桁
*					格納ｱﾄﾞﾚｽ
*					転送ﾜｰﾄﾞ数
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-22
********************************************************************************
*/
void	disp_char_cpy(UNs g_no, UNs l_no, UNs k_no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;

	g_p = disp_adr_shr(g_no, l_no, k_no);	//画面のｷｬﾗｸﾀｱﾄﾞﾚｽの算出(画面番号, 行, 桁(奇数は不可))

	if(k_no & 0x0001){						//奇数 桁？
		for( ; w_cnt > 0 ; w_cnt-- ) {
			wk_bf = *g_p++;
			wk_bf <<= 8;
			wk_bf |= (*g_p >> 8);
			*bf_p++ = wk_bf;
		}
	}
	else{									//偶数
		memcpy_word(bf_p, g_p, w_cnt);		//画面のｷｬﾗｸﾀのｺﾋﾟｰ
	}
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	画面のｷｬﾗｸﾀのｺﾋﾟｰ
*  Input	:		画面番号
*					行
*					桁
*					格納ｱﾄﾞﾚｽ
*					転送ﾜｰﾄﾞ数
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-22
********************************************************************************
*/
void	disp_char_SWcpy(UNl no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;
	UNl		adr;

	adr =  SWL_TABLE_ADR + ((no-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	g_p = (UNs *)adr;
	g_p++;

	memcpy_word(bf_p, g_p, w_cnt);		//画面のｷｬﾗｸﾀのｺﾋﾟｰ
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	画面のｷｬﾗｸﾀのｺﾋﾟｰ
*  Input	:		画面番号
*					行
*					桁
*					格納ｱﾄﾞﾚｽ
*					転送ﾜｰﾄﾞ数
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-22
********************************************************************************
*/
void	disp_char_CSRcpy(UNl no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;
	UNl		adr;

	adr =  CSR_TABLE_ADR + ((no-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	g_p = (UNs *)adr;
	g_p++;

	memcpy_word(bf_p, g_p, w_cnt);		//画面のｷｬﾗｸﾀのｺﾋﾟｰ
}


/*
********************************************************************************
*  Module Name:		mess_adr_shr
*  Function Name:	メッセージ画面キャラクタアドレス検索
*  Input	:		メッセージ番号
*
*  Return	: 		メッセージ先頭アドレス
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
UNs *	mess_adr_shr(UNi m_no)
{
	UNs	*g_p;

	if(m_no >= /*15 V01j*/20) {
		g_p = (UNs *)E_INTROCK_TOP;					//ガイダンス画面データ
	}
	else{
		if(m_no != 0){
			m_no --;
		}
		g_p = (UNs *)E_CHAR_TOP;					//キャラクタ画面データ
		g_p += m_no * (0x258/2);
	}
	g_p += language_chg;							//第２カ国語切替え
	return(g_p);
}


/*
********************************************************************************
*  Module Name:		BCD_ASCII
*  Function Name:	BCD→ASCII 変換
*  Input	:		BCD data(long)
*					ASCII 格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:	4Byte BCD DATA(8桁) -> 8Byte ASCII DATA
*
*  履 歴	:FIT)田端		ON:2002-05-22
********************************************************************************
*/
void	BCD_ASCII(UNl bcd_d, UNb *dst_p)
{
	UNi		Size;

	Size = 8;
	while(Size--) {
		*dst_p++ = (UNs)((bcd_d & 0x000f) + '0');
		bcd_d >>= 4;
	}
}


/*
********************************************************************************
*  Module Name:		HEX_ASCII
*  Function Name:	HEX→ASCII 変換
*  Input	:		HEX data(long)
*					ASCII 格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:	4Byte HEX DATA(8桁) -> 8Byte ASCII DATA
*
*  履 歴	:shima		ON:2002-11-12
********************************************************************************
*/
void	HEX_ASCII(UNl bcd_d, UNb *dst_p)
{
	UNi		Size;

	Size = 8;
	while(Size--) {
		if ((bcd_d & 0x000f) > 9 ) {
			*dst_p++ = (UNs)(((bcd_d & 0x000f)-0x0a) + 'A');
		}
		else {
			*dst_p++ = (UNs)((bcd_d & 0x000f) + '0');
		}
		bcd_d >>= 4;
	}
}


/*
********************************************************************************
*  Module Name:		BCD_HEX4
*  Function Name:	BCD→HEX　変換
*  Input	:		BCD DATA(long)
*
*  Return	: 		HEX DATA(long)
*  Note		:		BCD 8桁 -> 4Byte HEX DATA
*
*  履 歴	:FIT)田端		ON:2002-06-11
********************************************************************************
*/
//BCD -> HEX 変換ﾃｰﾌﾞﾙ
const UNl bhex_cnvtbl2[10] = { 00,10,      20,      30,      40,      50,      60,      70,      80,      90 };
const UNl bhex_cnvtbl3[10] = { 00,100,     200,     300,     400,     500,     600,     700,     800,     900 };
const UNl bhex_cnvtbl4[10] = { 00,1000,    2000,    3000,    4000,    5000,    6000,    7000,    8000,    9000 };
const UNl bhex_cnvtbl5[10] = { 00,10000,   20000,   30000,   40000,   50000,   60000,   70000,   80000,   90000 };
const UNl bhex_cnvtbl6[10] = { 00,100000,  200000,  300000,  400000,  500000,  600000,  700000,  800000,  900000 };
const UNl bhex_cnvtbl7[10] = { 00,1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000 };
const UNl bhex_cnvtbl8[10] = { 00,10000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000 };

UNl		BCD_HEX4(UNl bcd_d)
{
	UNl		cnv, i;

	cnv = 0;
	cnv = bcd_d & 0x000f;		//1位

	i = bcd_d >> 4;				//10位
	i &= 0x000f;
	cnv += bhex_cnvtbl2[i];

	i = bcd_d >> 8;				//100位
	i &= 0x000f;
	cnv += bhex_cnvtbl3[i];

	i = bcd_d >> 12;			//1000位
	i &= 0x000f;
	cnv += bhex_cnvtbl4[i];

	i = bcd_d >> 16;			//10000位
	i &= 0x000f;
	cnv += bhex_cnvtbl5[i];

	i = bcd_d >> 20;			//100000位
	i &= 0x000f;
	cnv += bhex_cnvtbl6[i];

	i = bcd_d >> 24;			//1000000位
	i &= 0x000f;
	cnv += bhex_cnvtbl7[i];

	i = bcd_d >> 28;			//10000000位
	i &= 0x000f;
	cnv += bhex_cnvtbl8[i];

	return(cnv);
}


/*
********************************************************************************
*  Module Name:		HEX_BCD4
*  Function Name:	Hex→BCD　変換
*  Input	:		HEX data(long)
*
*  Return	: 		BCD data(long)
*  Note		:	4Byte HEX DATA -> 4Byte BCD DATA(8桁)
*
*  履 歴	:FIT)田端		ON:2002-05-22
********************************************************************************
*/
UNl		HEX_BCD4(UNl hex_bf)
{
	UNl		i, bcd_bf;
	UNl		j;

	bcd_bf = 0;
	i = hex_bf;
	if(i > 99999999 ) {			//上限チェック
		i = 99999999;
	}
//							8位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10000000 ) {
			i -= 10000000;
		}
		else {
			break;
		}
	}
	bcd_bf = (j << 28);

//							7位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1000000 ) {
			i -= 1000000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 24);

//							6位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 100000 ) {
			i -= 100000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 20);

//							5位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10000 ) {
			i -= 10000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 16);

//							4位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1000 ) {
			i -= 1000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 12);

//							3位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 100 ) {
			i -= 100;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 8);

//							2位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10 ) {
			i -= 10;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 4);

//							1位
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1 ) {
			i -= 1;
		}
		else {
			break;
		}
	}
	bcd_bf |= j;

	return(bcd_bf);
}


/*
********************************************************************************
*  Module Name:		ASCII_SJIS
*  Function Name:	Asciiｺｰﾄﾞ → 全角S-Jisｺｰﾄﾞ　変換
*  Input	:		変換のﾊﾞｲﾄ数
*					Asciiｺｰﾄﾞ領域のｱﾄﾞﾚｽ
*					全角S-Jisｺｰﾄﾞ領域のｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-26
********************************************************************************
*/
void	Ascii_Sjis(UNs size, UNb *code_p, UNs *dst_p)
{
	/* 半角コード→全角ＳＪＩＳコード変換テーブル */
	/* 漢字コード表（半角文字）に対応 */
const unsigned short code_chg_tbl[158] =
	{0x8140,0x8149,0x818d,0x8194,0x8190,0x8193,0x8195,0x818c,0x8169,0x816a,0x8196,0x817b,0x8143,0x817c,0x8144,0x815e
	,0x824f,0x8250,0x8251,0x8252,0x8253,0x8254,0x8255,0x8256,0x8257,0x8258,0x8146,0x8147,0x8183,0x8181,0x8184,0x8148
	,0x8197,0x8260,0x8261,0x8262,0x8263,0x8264,0x8265,0x8266,0x8267,0x8268,0x8269,0x826a,0x826b,0x826c,0x826d,0x826e
	,0x826f,0x8270,0x8271,0x8272,0x8273,0x8274,0x8275,0x8276,0x8277,0x8278,0x8279,0x816d,0x818f,0x816e,0x81c8,0x8151
	,0x8140,0x8281,0x8282,0x8283,0x8284,0x8285,0x8286,0x8287,0x8288,0x8289,0x828a,0x828b,0x828c,0x828d,0x828e,0x828f
	,0x8290,0x8291,0x8292,0x8293,0x8294,0x8295,0x8296,0x8297,0x8298,0x8299,0x829a,0x816f,0x8162,0x8170,0x8150
	,0x8142,0x8175,0x8176,0x8141,0x8140,0x8392,0x8340,0x8342,0x8344,0x8346,0x8348,0x8383,0x8385,0x8387,0x8362
	,0x815b,0x8341,0x8343,0x8345,0x8347,0x8349,0x834a,0x834c,0x834e,0x8350,0x8352,0x8354,0x8356,0x8358,0x835a,0x835c
	,0x835e,0x8360,0x8363,0x8365,0x8367,0x8369,0x836a,0x836b,0x836c,0x836d,0x836e,0x8371,0x8374,0x8377,0x837a,0x837d
	,0x837e,0x8380,0x8381,0x8382,0x8384,0x8386,0x8388,0x8389,0x838a,0x838b,0x838c,0x838d,0x838f,0x8393,0x814a,0x814b};


	while(size--) {
		*dst_p++ = code_chg_tbl[(*code_p) - 0x20];		//ASCIIコードをSJISコードに変換
		code_p++;
	}
}


/*
********************************************************************************
*  Module Name:		jiscnv
*  Function Name:	シフトＪＩＳ→ＪＩＳ変換
*  Input	:		シフトJISコード
*  Return	: 		JISコード
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-20
********************************************************************************
*/
UNs	jiscnv(UNs d_cara)
{
	UNs	k;
	UNb	i,j;

//	i = d_cara >> 8;
	i = (UNb)(d_cara & 0x00ff);
	if( i >= 0xe0) {
		i -= 0x40;
	}
	if( i < 0x81 ) {
		i -= 0x81;
		i <<= 1;
		i |= 0x01;
	}
	else{
		i -= 0x81;
		i <<= 1;
	}
		i += 0x21;

//	j = d_cara;
	j = d_cara >> 8;
	if(j >= 0x80) {
		j --;
	}
	if(j >= 0x9e) {
		i ++;
		j -= 0x7d;
	}
	else{
		j -= 0x1f;
	}

	k = i;
	k <<= 8;
	k |= j;
	return (k);
}


/*
********************************************************************************
*  Module Name:		memset_word
*  Function Name:	指定領域を指定ﾃﾞｰﾀにてﾜｰﾄﾞ単位で設定
*  Input	:		格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*			:		設定ﾃﾞｰﾀ
*			:		ｻｲｽﾞ（ﾜｰﾄﾞ数）
*
*  Return	: 		なし
*  Note		:	指定された領域の先頭から、指定ﾃﾞｰﾀを指定数分設定する
*
*  履 歴	:FIT)田端		ON:2002-06-26
********************************************************************************
*/
void	memset_word(UNs *dst_p, UNs dta, UNs size)
{

	while(size--) {
		*dst_p++ = dta;				//領域コピー
	}

}


/*
********************************************************************************
*  Module Name:		memset_long
*  Function Name:	指定領域を指定ﾃﾞｰﾀにてﾛﾝｸﾞ単位で設定
*  Input	:		格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*			:		設定ﾃﾞｰﾀ
*			:		ｻｲｽﾞ（ﾛﾝｸﾞ数）
*
*  Return	: 		なし
*  Note		:	指定された領域の先頭から、指定ﾃﾞｰﾀを指定数分設定する
*
*  履 歴	:Shimamura		ON:2010-10-19
********************************************************************************
*/
void	memset_long(UNl *dst_p, UNl dta, UNs size)
{

	while(size--) {
		*dst_p++ = dta;				//領域コピー
	}

}


/*
********************************************************************************
*  Module Name:		memcpy_word
*  Function Name:	指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー
*  Input	:		格納先ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*			:		格納元ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*			:		ｻｲｽﾞ（ﾜｰﾄﾞ数）
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-26
********************************************************************************
*/
void	memcpy_word(UNs *dst_p, UNs *src_p, UNs size)
{

	while(size--) {
		*dst_p++ = *src_p++;			//領域コピー
	}
}


/*** END ***/
