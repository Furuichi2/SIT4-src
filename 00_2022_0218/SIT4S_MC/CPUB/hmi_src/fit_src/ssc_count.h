/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						カウント処理			定義ファイル				*/
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
#include	"dp_cpuab.h"

/*	定数定義 ****************************************************************/
#define		BIT_15		0x8000
#define		BIT_14		0x4000
#define		BIT_13		0x2000
#define		BIT_12		0x1000
#define		BIT_11		0x0800
#define		BIT_10		0x0400
#define		BIT_09		0x0200
#define		BIT_08		0x0100
#define		BIT_07		0x0080
#define		BIT_06		0x0040
#define		BIT_05		0x0020
#define		BIT_04		0x0010
#define		BIT_03		0x0008
#define		BIT_02		0x0004
#define		BIT_01		0x0002
#define		BIT_00		0x0001

#define		CNT_LIMIT	9999999					/* ｶｳﾝﾀ限界値 超えたら 0ｸﾘｱ	*/

/*	外部参照変数定義 ********************************************************/
//	EXTRN	WORD		SEQ_PAR_016;			/* ｶｳﾝﾀ 有/無 内部/外部		*/
//	EXTRN	WORD		SEQ_PAR_032;			/* ｶｳﾝﾀ 入/切 				*/
//	EXTRN	WORD		SEQ_PAR_033;			/* ｶｳﾝﾀ UP					*/
//	EXTRN	WORD		SEQ_PAR_102;			/* ｶｳﾝﾀ UP指令				*/
//	EXTRN	WORD		SEQ_PAR_160;			/* 正転/逆転				*/

	EXTRN	WORD		ENCO_DATA_HEX;			/* 角度エンコードデータ		*/

	EXTRN	WORD		deg_OLD;				/* 角度前回値				*/
	EXTRN	WORD		count_bit_OLD[];		/* ｶｳﾝﾀ UP指令ﾋﾞｯﾄ前回値	*/

	EXTRN	DWORD		COUNT_T;				/* ｶｳﾝﾀ ﾄｰﾀﾙ				*/
	EXTRN	DWORD		COUNT_1;				/* ｶｳﾝﾀ 1					*/
	EXTRN	DWORD		COUNT_2;				/* ｶｳﾝﾀ 2					*/

/*	外部参照関数定義 ********************************************************/


/****************************************************************************/
