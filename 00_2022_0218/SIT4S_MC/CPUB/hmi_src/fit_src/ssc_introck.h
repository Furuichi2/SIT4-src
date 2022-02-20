/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						生産／ｲﾝﾀｰﾛｯｸ表示処理	定義ファイル				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned int

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_def.h"
#include	"ssc_wk_ext.h"

/*	定数定義 ****************************************************************/
// #define	LANG_BIT		0x2000				/* 言語切替ﾋﾞｯﾄ				*/

#define		SEISAN_LNG		20					/* 生産文言長		20BYTE	*/
#define		SEISAN_POS		0x3053				/* 生産情報表示位置情報		*/
												/* 12BYTE, X=5ｶﾗﾑ, Y=3ｶﾗﾑ	*/

#define		INTROCK_MAX		7					/* ｲﾝﾀｰﾛｯｸ検索件数			*/
#define		INTROCK_LNG		40					/* ｲﾝﾀｰﾛｯｸ文言長	40BYTE	*/
#define		INTROCK_POS1	0x78A0				/* ｲﾝﾀｰﾛｯｸ表示位置情報 1	*/
												/* 30BYTE, X=10ｶﾗﾑ, Y=0ｶﾗﾑ	*/
#define		INTROCK_POS2	0xA006				/* ｲﾝﾀｰﾛｯｸ表示位置情報 2	*/
												/* 40BYTE, X=0ｶﾗﾑ, Y=6ｶﾗﾑ	*/

/*	外部参照変数定義 ********************************************************/
//	EXTRN	WORD		SEQ_PAR_100;			/* SEQ_RAM	ﾓｰﾄﾞSW表示		*/
//	EXTRN	WORD		SEQ_PAR_120;			/* ｲﾝﾀｰﾛｯｸ選択	1			*/
//	EXTRN	WORD		SEQ_PAR_121;			/* ｲﾝﾀｰﾛｯｸ選択	2			*/
//	EXTRN	WORD		SEQ_PAR_122;			/* ｲﾝﾀｰﾛｯｸ ﾋﾞｯﾄ域 TOP		*/

	EXTRN	WORD		WINDOW_NO;				/* 画面番号（ｳｨﾝﾄﾞｳ ON/OFF）*/
//	EXTRN	DWORD		language_chg;			/* 言語切替用オフセット値	*/

	EXTRN	WORD		SEI_INF_FLG;			/* 生産情報フラグ			*/
	EXTRN	WORD		SEI_INF_FLG_LAST;		/* 生産情報フラグ前回値		*/

	EXTRN	WORD		IROCK_NO	 [];		/* ｲﾝﾀｰﾛｯｸ表示番号列		*/
	EXTRN	WORD		IROCK_NO_LAST[];		/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/


/*	外部参照関数定義 ********************************************************/
	EXTRN	void		Disp_moji(WORD,WORD*,WORD);		/* LCD文字列表示	*/

/****************************************************************************/
