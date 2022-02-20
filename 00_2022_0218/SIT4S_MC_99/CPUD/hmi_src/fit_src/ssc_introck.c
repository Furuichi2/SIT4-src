/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						生産／インターロック表示処理						*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		ALL_DISP		0xFF				/* 全画面表示				*/
#define		HALF_DISP		0x55				/* ウィンドウ表示			*/
#define		NO_DISP			0x00				/* 表示しない				*/

#define		SEISAN_LNG		20					/* 生産文言長		20BYTE	*/
#define		SEISAN_POS		0x3053				/* 生産情報表示位置情報		*/
												/* 12BYTE, X=5ｶﾗﾑ, Y=3ｶﾗﾑ	*/
#define		INTROCK_LNG		40					/* ｲﾝﾀｰﾛｯｸ文言長	40BYTE	*/
#define		INTROCK_POS1	0x78A0				/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
												/* 30BYTE, X=10ｶﾗﾑ, Y=0ｶﾗﾑ	*/
#define		INTROCK_POS2	0xA006				/* ｲﾝﾀｰﾛｯｸ表示位置情報 2	*/
												/* 40BYTE, X=0ｶﾗﾑ, Y=6ｶﾗﾑ	*/

#define		INTROCK_XPOS1	160					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
#define		INTROCK_YPOS1	0					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
#define		INTROCK_LENG1	30					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
#define		INTROCK_XPOS2	0					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
#define		INTROCK_YPOS2	192					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
#define		INTROCK_LENG2	40					/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/


/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];

/* ﾌﾟﾛﾄﾀｲﾌﾟ */
void		SEISAN_INF_DISP	(void);				/* 生産行程表示				*/
void		IROCK_SHR		(void);				/* ｲﾝﾀｰﾛｯｸ表示				*/
void		IROCK_SHR_OUT	(void);				/* 発生インターロックのキャラクタデータ出力処理	*/	//2009/07/14

/****************************************************************************/
/*																			*/
/*	生産行程表示			：	４倍角数字表示の上に生産工程を表示する。	*/
/*																			*/
/*		シーケンサのモードＳＷ・１６ビットを読んで							*/
/*		最初に１になっているモードをメッセージ表示する。					*/
/*																			*/
/*		SEQ_PAR_100			：	シーケンサ・モードＳＷ表示					*/
/*		language_chg		：	文言ｱﾄﾞﾚｽ	言語切替用オフセット値			*/
/*																			*/
/*		SEISAN_DISP_FLG		：	生産情報表示フラグ							*/
/*		SEI_INF_FLG			：	生産情報フラグ								*/
/*		SEI_INF_FLG_LAST	：	生産情報フラグ前回値						*/
/*																			*/
/*		画面切り替え時は、前回値保存領域をクリアすること。					*/
/*																			*/
/****************************************************************************/
void	SEISAN_INF_DISP	(void)
{
	WORD	i;
	WORD	chk;
	WORD	mode;
	WORD	temp;
	WORD*	addr;
	DWORD	calc;
	UNl		adr;
	UNs		*hrom;

	if (SEISAN_DISP_FLG != ALL_DISP)	return;		/* 生産表示しない		*/

	mode = SEQ_PAR_100;								/* ﾓｰﾄﾞSW読込			*/
	chk  = 0x0001;

	for (i=0; i<16; i++){							/* ﾋﾞｯﾄﾁｪｯｸ				*/
		if ((mode & chk) != 0x0000)		break;		/* 検索OK				*/
		chk = (chk << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/

	/* ONなしの場合 i=16 で空白表示になる */

	SEI_INF_FLG 	 = i;							/* 生産情報ﾌﾗｸﾞ			*/
	temp 			 = SEI_INF_FLG_LAST;			/* 前回値読込			*/
	SEI_INF_FLG_LAST = SEI_INF_FLG;					/* 前回値更新			*/
	if (temp == SEI_INF_FLG)			return;		/* 前回と同じ、描画なし	*/

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_CHAR_TOP + language_chg);			/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
	calc  = (E_CHAR_TOP + (language_chg*2));		/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
/********/
	calc += (SEI_INF_FLG * SEISAN_LNG);				/* ｵﾌｾｯﾄ値加算			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(SEISAN_POS,addr,0);					/* LCD文字列表示		*/
#else
	adr =  CHR_TABLE_ADR + ((i+1) * CHAR_MOJI_SIZE);	// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		10, 
		80, 
		96, 
		0,
		6, 
		0x0202, 
		hrom, 
		LCD_VRAM
		);
#endif
}
/****************************************************************************/
/*																			*/
/*	インターロックデータ表示処理											*/
/*																			*/
/*		シーケンサのインターロック選択（３２モード）に応じたパターンで		*/
/*		３２０ビットのインターロック表示をチェックする。					*/
/*		チェックパターンは、ユーザ定義。									*/
/*		アドレス昇順に検索し、先優先で該当するメッセージを表示する。		*/
/*		表示は、画面最上行とウィンドウに行う。（最大件数 INTROCK_MAX）		*/
/*																			*/
/*		SEQ_PAR_120			：	シーケンサ・インターロック選択	上位16bit	*/
/*		SEQ_PAR_121			：	シーケンサ・インターロック選択	下位16bit	*/
/*		SEQ_PAR_122			：	シーケンサ・インターロックビット域先頭		*/
/*																			*/
/*		language_chg		：	文言ｱﾄﾞﾚｽ	言語切替用オフセット値			*/
/*		WINDOW_NO			：	画面番号（ウィンドウ表示ＯＮ／ＯＦＦ）		*/
/*		INTROCK_DISP_FLG	：	ガイダンス表示フラグ						*/
/*																			*/
/*		IROCK_NO	 [INTROCK_MAX]	：	インターロック表示番号列			*/
/*		IROCK_NO_LAST[INTROCK_MAX]	：	インターロック表示番号列前回値		*/
/*																			*/
/*		画面切り替え時は、前回値保存領域をクリアすること。					*/
/*																			*/
/****************************************************************************/
void	IROCK_SHR		(void)
{
	WORD	i,	t,	x;
	WORD	chk;
	WORD	pos, ypos, xpos;
	WORD	pat1;
	WORD	pat2;
	WORD*	intr;
	WORD*	addr;
	DWORD	chk2;
	DWORD	mode;
	DWORD	calc;
	WORD	nop[40];
	WORD	moji_col, back_col;

	if (INTROCK_DISP_FLG != ALL_DISP)	return;		/* ｶﾞｲﾀﾞﾝｽ表示しない	*/

	mode  = ((SEQ_PAR_121 << 16) & 0xFFFF0000);		/* ｲﾝﾀｰﾛｯｸﾊﾟﾀｰﾝ選択		*/
	mode |=  (SEQ_PAR_120        & 0x0000FFFF);		/* ﾋﾞｯﾄ0 優先			*/
	chk2  = 0x00000001;								/* ﾊﾟﾀｰﾝ検索			*/

	for (i=0; i<32; i++){							/* ﾋﾞｯﾄﾁｪｯｸ				*/
		if ((mode & chk2)!= 0x00000000)	break;		/* 検索OK				*/
		chk2 = (chk2 << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/
	if (i == 32)	i = 0;							/* ONﾅｼなら先頭を使用	*/

	calc  = (DWORD)E_INTROCK_PAT;					/* ﾁｪｯｸﾊﾟﾀｰﾝ登録ｴﾘｱ先頭	*/
	calc += INTR_DAT_OFS;			//V06
	calc += (i * 20 * 2);							/* ｵﾌｾｯﾄ値加算			*/
	addr  = (WORD*)calc;							/*						*/

	intr  = &SEQ_PAR_122;							/* ｲﾝﾀｰﾛｯｸﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
	t	  = 0;										/* ﾃｰﾌﾞﾙ index ｸﾘｱ		*/
	x	  = 0;										/* ﾙｰﾌﾟｶｳﾝﾀ				*/

IROCK_SEARCH:										/* 検索開始				*/
	chk  = 0x0001;									/*						*/
	pat1 = (*addr);									/* ｲﾝﾀｰﾛｯｸ ﾁｪｯｸﾋﾞｯﾄ		*/
	pat2 = (*intr);									/* ｲﾝﾀｰﾛｯｸ 情報ﾋﾞｯﾄ		*/
	if ((pat1 == 0)||(pat2 == 0))					/* ﾁｪｯｸ or 情報ﾋﾞｯﾄ OFF	*/
		goto	IROCK_SEARCH_NEXT;					/* 検索次候補へ			*/

	for (i=0; i<16; i++){							/* 16 BIT				*/
		if (((pat1 & chk)!=0)&&((pat2 & chk)!=0)){	/* ﾁｪｯｸ & 情報ﾋﾞｯﾄ ON	*/
			IROCK_NO[t] = ((x * 16) + i);			/* ｲﾝﾀｰﾛｯｸ番号			*/
			t++;									/* 番号列ｲﾝﾃﾞｯｸｽ更新	*/
			if (t >= INTROCK_MAX)					/*						*/
				goto	IROCK_SKIP;					/* 検索終了				*/
		}											/*						*/
		chk = (chk << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/

IROCK_SEARCH_NEXT:									/* 検索次候補			*/
	addr ++;										/* ﾁｪｯｸﾊﾟﾀｰﾝ 更新		*/
	intr ++;										/* ｼｰｹﾝｻｱﾄﾞﾚｽ更新		*/
	x    ++;										/*						*/
	if (x < 20)				goto	IROCK_SEARCH;	/* 20 WORD				*/

	for (i=t; i<INTROCK_MAX; i++)					/* 未使用域ｸﾘｱ			*/
		IROCK_NO[i] = 0xFFFF;						/* ｲﾝﾀｰﾛｯｸ番号ｸﾘｱ		*/

IROCK_SKIP:											/* 検索完了				*/
	for (i=0; i<20; i++)	nop[i]=0x2020;			/* NOP ﾃﾞｰﾀ作成			*/

//V05r	if (IROCK_NO[0] == IROCK_NO_LAST[0])			/* 最上行変化なし		*/
//V05r		goto	IROCK_WIN_TOP;						/*						*/

	if (IROCK_NO[0] == 0xFFFF){						/* ｲﾝﾀｰﾛｯｸなし			*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Disp_moji(INTROCK_POS1,nop,0);				/* LCD文字列表示・消去	*/
#else
	disp_moji_s_color(
		INTROCK_LENG1,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS1,							/* 書出しX位置		*/
		INTROCK_YPOS1,							/* 書出しY位置		*/
		7,										/* 文字色			*/
		GAMENn_HEAD.scr_col,					/* 背景色			*/
		0x0202,									/* 文字ｻｲｽﾞ			*/
		&nop[0],								/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE								/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG1,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS1,							/* 書出しX位置		*/
		INTROCK_YPOS1,							/* 書出しY位置		*/
		0x0202									/* 文字ｻｲｽﾞ			*/
		);
#endif
		goto	IROCK_WIN_TOP;						/*						*/
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_INTROCK_TOP + language_chg);			/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
	calc  = (E_INTROCK_TOP + (language_chg*2));		/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
/********/
	calc += (IROCK_NO[0] * 40);						/* ｵﾌｾｯﾄ値加算			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(INTROCK_POS1,(WORD*)addr,0);			/* LCD文字列表示		*/
#else
	calc = MES_TABLE_ADR + (IROCK_NO[0] * CHAR_MES_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	calc += 2;
	addr  = (WORD*)calc;							/*						*/
	moji_col = COL_WHITE;//white
	back_col = COL_RED;//red

////	<<< SIT-4 MC ROMﾊﾟﾗ指定に変更	2014/02/06  >>>
////	if ( IROCK_NO[0]>89-1 ) {
////		moji_col = COL_BLACK;//black
////		back_col = GAMENn_SCR_COL;//画面ｽｸﾘｰﾝ色
////	}
	if ( (IROCK_NO[0] > IROCK_COL_CHG_NO) || (IROCK_COL_CHG_NO == 3465) ) {
		moji_col = COL_BLACK;//black
		back_col = GAMENn_SCR_COL;//画面ｽｸﾘｰﾝ色
	}

	if (SEQ_PAR_113 & BIT_2)			//制動性能試験中？			//V05r(INS)
	{
		moji_col = COL_BLACK;			//制動性能文字色
		back_col = COL_YELLOW;			//制動性能背景色
	}
	
	disp_moji_s_color(
		INTROCK_LENG1,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS1,							/* 書出しX位置		*/
		INTROCK_YPOS1,							/* 書出しY位置		*/
		moji_col,								/* 文字色			*/
		back_col,									/* 背景色			*/
		0x0202,									/* 文字ｻｲｽﾞ			*/
		addr,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE								/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG1,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS1,							/* 書出しX位置		*/
		INTROCK_YPOS1,							/* 書出しY位置		*/
		0x0202									/* 文字ｻｲｽﾞ			*/
		);
#endif

IROCK_WIN_TOP:										/* ｳｨﾝﾄﾞｳ表示			*/
	if ((WINDOW_NO != 3)&&(WINDOW_NO != 10))		/*						*/
		goto	IROCK_RET;							/* 非表示				*/

	pos = INTROCK_POS2;								/* ｲﾝﾀｰﾛｯｸ表示位置情報	*/
	ypos = INTROCK_YPOS2;							/* ｲﾝﾀｰﾛｯｸ表示位置情報	*/
	i	= 0;										/*						*/

IROCK_WIN_LOOP:										/* ｳｨﾝﾄﾞｳ表示 LOOP		*/
	if (IROCK_NO[i] == IROCK_NO_LAST[i])			/* 変化なし				*/
		goto	IROCK_WIN_NEXT;						/*						*/

	if (IROCK_NO[i] == 0xFFFF){						/* ｲﾝﾀｰﾛｯｸなし			*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Disp_moji(pos,nop,0);						/* LCD文字列表示・消去	*/
#else
		disp_moji_s_color(
			INTROCK_LENG2,							/* ｷｬﾗｸ長			*/
			INTROCK_XPOS2,							/* 書出しX位置		*/
			ypos,									/* 書出しY位置		*/
			0,										/* 文字色			*/
			GAMENn_HEAD.scr_col,					/* 背景色			*/
			0x0202,									/* 文字ｻｲｽﾞ			*/
			&nop[0],								/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE								/* 表示ﾒﾓﾘ			*/
			);
		disp_moji_s_rif (
			INTROCK_LENG2,							/* ｷｬﾗｸ長			*/
			INTROCK_XPOS2,							/* 書出しX位置		*/
			ypos,									/* 書出しY位置		*/
			0x0202									/* 文字ｻｲｽﾞ			*/
			);
#endif
		goto	IROCK_WIN_NEXT;						/*						*/
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_INTROCK_TOP + language_chg);			/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
	calc  = (E_INTROCK_TOP + (language_chg*2));		/* 文言ｱﾄﾞﾚｽ + 言語判定	*/
/********/
	calc += (IROCK_NO[i] * 40);						/* ｵﾌｾｯﾄ値加算			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(pos,addr,0);							/* LCD文字列表示		*/
#else
	calc = MES_TABLE_ADR + (IROCK_NO[i] * CHAR_MES_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	calc += 2;
	addr  = (WORD*)calc;							/*						*/
	disp_moji_s_color(
		INTROCK_LENG2,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS2,							/* 書出しX位置		*/
		ypos,									/* 書出しY位置		*/
		0,										/* 文字色			*/
		GAMENn_HEAD.scr_col,					/* 背景色			*/
		0x0202,									/* 文字ｻｲｽﾞ			*/
		addr,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE								/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG2,							/* ｷｬﾗｸ長			*/
		INTROCK_XPOS2,							/* 書出しX位置		*/
		ypos,									/* 書出しY位置		*/
		0x0202									/* 文字ｻｲｽﾞ			*/
		);
#endif

IROCK_WIN_NEXT:										/* ｳｨﾝﾄﾞｳ表示次行		*/
	pos ++;											/* 行ｶﾗﾑ位置更新		*/
	ypos += (16*2);									/* 行ｶﾗﾑ位置更新		*/
	i   ++;											/* 次候補				*/
	if (i < INTROCK_MAX)	goto  IROCK_WIN_LOOP;	/* 						*/

IROCK_WIN_END:										/* ｳｨﾝﾄﾞｳ表示完了		*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	for (i=0; i<40; i++)	nop[i] = 0xFFFF;		/* LINE ﾃﾞｰﾀ作成		*/
//V00m	Lcd_draw(0,0, 96,40,nop);						/* LINE 描画			*/
//V00o復活
	Lcd_draw(0,0, 96,40,nop);						/* LINE 描画			*/
	nop[36] = 0xFF80;								/*						*/
//V00m	Lcd_draw(0,2,207,37,nop);						/*						*/
//V00o復活
	Lcd_draw(0,2,207,37,nop);						/*						*/
#else
	for (i=0, xpos=0, ypos=192; i<640; i++, xpos++)	/* LINE ﾃﾞｰﾀ作成		*/
	{
		LCD_VBASE[ypos][xpos] = 0;
		LCD_VRAM[ypos][xpos] = 0;
	}
#endif

IROCK_RET:											/* 表示完了				*/
	for (i=0; i<INTROCK_MAX; i++)					/* 番号列を前回域ｺﾋﾟｰ	*/
		IROCK_NO_LAST[i] = IROCK_NO[i];				/*						*/
}


/****************************************************************************/
/*																			*/
/*	発生インターロックのキャラクタデータ出力処理		2009/07/14			*/
/*																			*/
/*		シーケンサのインターロック選択（３２モード）に応じたパターンで		*/
/*		３２０ビットのインターロック表示をチェックする。					*/
/*		チェックパターンは、ユーザ定義。									*/
/*		アドレス昇順に検索し、先優先で該当するメッセージを表示する。		*/
/*		表示は、画面最上行とウィンドウに行う。（最大件数 8）				*/
/*																			*/
/*		SEQ_PAR_120			：	シーケンサ・インターロック選択	上位16bit	*/
/*		SEQ_PAR_121			：	シーケンサ・インターロック選択	下位16bit	*/
/*		SEQ_PAR_122			：	シーケンサ・インターロックビット域先頭		*/
/*																			*/
/*		IROCK_OUT_NO	 [8]	：	インターロック発生番号					*/
/*		IROCK_OUT_NO_LAST[8][8]	：	インターロック発生番号に対するキャラクタ*/
/*																			*/
/****************************************************************************/
void	IROCK_SHR_OUT		(void)
{
	BYTE*	sadr;
	WORD	i,	t,	x;
	WORD	chk;
	WORD	pat1;
	WORD	pat2;
	WORD*	intr;
	WORD*	addr;
	DWORD	chk2;
	DWORD	mode;
	DWORD	calc;
	BYTE	nop[8];

	if ( (SEQ_024_SV & BIT_6) == 0 )	return;

	mode  = ((SEQ_PAR_121 << 16) & 0xFFFF0000);		/* ｲﾝﾀｰﾛｯｸﾊﾟﾀｰﾝ選択		*/
	mode |=  (SEQ_PAR_120        & 0x0000FFFF);		/* ﾋﾞｯﾄ0 優先			*/
	chk2  = 0x00000001;								/* ﾊﾟﾀｰﾝ検索			*/

	for (i=0; i<32; i++){							/* ﾋﾞｯﾄﾁｪｯｸ				*/
		if ((mode & chk2)!= 0x00000000)	break;		/* 検索OK				*/
		chk2 = (chk2 << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/
	if (i == 32)	i = 0;							/* ONﾅｼなら先頭を使用	*/

	calc  = (DWORD)E_INTROCK_PAT;					/* ﾁｪｯｸﾊﾟﾀｰﾝ登録ｴﾘｱ先頭	*/
	calc += INTR_DAT_OFS;			//V06
	calc += (i * 20 * 2);							/* ｵﾌｾｯﾄ値加算			*/
	addr  = (WORD*)calc;							/*						*/

	intr  = &SEQ_PAR_122;							/* ｲﾝﾀｰﾛｯｸﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
	t	  = 0;										/* ﾃｰﾌﾞﾙ index ｸﾘｱ		*/
	x	  = 0;										/* ﾙｰﾌﾟｶｳﾝﾀ				*/

IROCK_SCH_OUT:										/* 検索開始				*/
	chk  = 0x0001;									/*						*/
	pat1 = (*addr);									/* ｲﾝﾀｰﾛｯｸ ﾁｪｯｸﾋﾞｯﾄ		*/
	pat2 = (*intr);									/* ｲﾝﾀｰﾛｯｸ 情報ﾋﾞｯﾄ		*/
	if ((pat1 == 0)||(pat2 == 0))					/* ﾁｪｯｸ or 情報ﾋﾞｯﾄ OFF	*/
		goto	IROCK_SCH_OUT_NEXT;					/* 検索次候補へ			*/

	for (i=0; i<16; i++){							/* 16 BIT				*/
		if (((pat1 & chk)!=0)&&((pat2 & chk)!=0)){	/* ﾁｪｯｸ & 情報ﾋﾞｯﾄ ON	*/
			IROCK_OUT_NO[t] = ((x * 16) + i);			/* ｲﾝﾀｰﾛｯｸ番号			*/
			t++;									/* 番号列ｲﾝﾃﾞｯｸｽ更新	*/
			if (t >= 8)								/*						*/
				goto	IROCK_SCH_OUT_SKIP;			/* 検索終了				*/
		}											/*						*/
		chk = (chk << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/

IROCK_SCH_OUT_NEXT:									/* 検索次候補			*/
	addr ++;										/* ﾁｪｯｸﾊﾟﾀｰﾝ 更新		*/
	intr ++;										/* ｼｰｹﾝｻｱﾄﾞﾚｽ更新		*/
	x    ++;										/*						*/
	if (x < 20)				goto	IROCK_SCH_OUT;	/* 20 WORD				*/

	for (i=t; i<8; i++)								/* 未使用域ｸﾘｱ			*/
		IROCK_OUT_NO[i] = 0xFFFF;						/* ｲﾝﾀｰﾛｯｸ番号ｸﾘｱ		*/

IROCK_SCH_OUT_SKIP:											/* 検索完了				*/
	for (i=0; i<8; i++)	nop[i]=0x20;				/* NOP ﾃﾞｰﾀ作成			*/


	for (i=0; i<8; i++)
	{
		if (IROCK_OUT_NO[i] == 0xffff)
		{
			break;
		}
		else {
			calc  = E_INTROCK_CHAR;							/* 文言ｱﾄﾞﾚｽ	*/
			calc += INTR_DAT_OFS;			//V06
			calc += (IROCK_OUT_NO[i] * 8);						/* ｵﾌｾｯﾄ値加算			*/
			sadr  = (BYTE*)calc;							/*						*/
			for (t=0; t<8; t++)
			{
				IROCK_CHAR[i][t] = *sadr;
				sadr++;
			}
		}
	}

	for (; i<8; i++)
	{
		for (t=0; t<8; t++)
		{
			IROCK_CHAR[i][t] = nop[t];
		}
	}

}


/****************************************************************************/
