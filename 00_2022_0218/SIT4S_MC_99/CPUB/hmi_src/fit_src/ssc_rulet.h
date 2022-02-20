/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ルーレット表示処理		定義ファイル				*/
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
#include	"dp_cpuab.h"

/*	定数定義 ****************************************************************/
#define		BIT_06		0x0040

/*	外部参照変数定義 ********************************************************/
//	EXTRN	WORD		SEQ_PAR_101;			/* SEQ_RAM					*/
//	EXTRN	WORD		SEQ_PAR_222;			/* SEQ_RAM					*/

	EXTRN	WORD		RULET_DISP_FLG;			/* ルーレット表示フラグ		*/
	EXTRN	WORD		RULET_HIGH_FLG;			/* 高速描画フラグ			*/

	EXTRN	WORD		TAIKI_ZEN_POS;			/* ルーレット前回描画位置	*/
	EXTRN	WORD		TAIKI_ZEN_MOD;			/* ルーレット前回描画方向	*/

	EXTRN	WORD		DEG_DISP_FLG;			/* 角度表示フラブ			*/
	EXTRN	WORD		DEG_DISP_LST;			/* 角度データ前回値 		*/

	EXTRN	WORD		ENCO_DATA_BCD;			/* 角度エンコードデータ		*/
	EXTRN	WORD		ENCO_DATA_HEX;			/* 角度エンコードデータ		*/

	EXTRN	WORD		TAIKITEN_DIRECT;		/* 待機点データ（クラッチ）	*/
	EXTRN	WORD		TAIKITEN_DAT;			/* 待機点データ（１／１０）	*/

//	EXTRN	WORD		CB1_SPMDAT_PV;			/* ＳＰＭデータ				*/
	EXTRN	WORD		SYS_HIGHSPM_B1;			/* 高速描画開始ＳＰＭ値		*/
	EXTRN	WORD		SYS_LOWSPM_B1;			/* 高速描画停止ＳＰＭ値		*/

	EXTRN	WORD		SEISAN_FLG;				/*							*/
	EXTRN	WORD		TAIKITEN_FLG;			/*							*/
	EXTRN	WORD		TAIKITEN_FLG_FLG;		/*							*/

	EXTRN	DWORD		DEG_DISP_TBL	  [];	/* 4倍角ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ配列	*/
	EXTRN	DWORD		RULET_TBL_BASE	  [];	/* ルーレット●表示データ	*/
	EXTRN	DWORD		RULET_TBL_BASE_00 [];	/* ルーレット○表示データ	*/
	EXTRN	DWORD		RULET_BASE_TBL_TBL[];	/* ルーレット枠表示データ	*/

	EXTRN	DWORD		HAN_RULET_TBL_BASE_00 [];	/* ルーレット○表示データ	*/
	EXTRN	DWORD		HAN_RULET_BASE_TBL_TBL[];	/* ルーレット枠表示データ	*/

/*	外部参照関数定義 ********************************************************/
	EXTRN	void		Lcd_draw(WORD,WORD,WORD,WORD,WORD*);	/* 1ﾗｲﾝ表示	*/

/****************************************************************************/
