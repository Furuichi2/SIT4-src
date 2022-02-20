/****************************************************************************************
*	File Name	:	ssc_CmnDef.h
*	Function	:	シーケンス 共通定義
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-09 Y.Kobayashi
****************************************************************************************/
#ifndef _SSC_CMNDEF_H_
#define _SSC_CMNDEF_H_

//[koma]#include "itron.h"
//[koma]#include "kernel.h"


//----- Defines ---------------------------------------------------------------

// BIT定義
#define cBIT0					0x1
#define cBIT1					0x2
#define cBIT2					0x4
#define cBIT3					0x8
#define cBIT4					0x10
#define cBIT5					0x20
#define cBIT6					0x40
#define cBIT7					0x80
#define cBIT8					0x100
#define cBIT9					0x200
#define cBIT10					0x400
#define cBIT11					0x800
#define cBIT12					0x1000
#define cBIT13					0x2000
#define cBIT14					0x4000
#define cBIT15					0x8000

// メモリ領域番号
#define MkindNoX				1				// 実入力領域番号
#define MkindNoY				2				// 実出力領域番号
#define MkindNoM				3				// 非保持領域番号
#define MkindNoL				4				// 保持領域番号
#define MkindNoT				5				// タイマ領域番号
#define MkindNoC				6				// カウンタ領域番号
#define MkindNoTd				7				// タイマ実測領域番号
#define MkindNoCd				8				// カウンタ実測領域番号
#define MkindNoF				13				// 機能領域領域番号
#define MkindNoS				14				// システム領域番号
#define MkindNoA				15				// アナウンス領域番号
#define MkindNoMax				15				// メモリ領域番号MAX


//----- Typedef ---------------------------------------------------------------

typedef unsigned char 	Uchar;
typedef unsigned short	Ushort;
typedef unsigned int	Uint;
typedef unsigned long	Ulong;
typedef signed char 	Char;
typedef signed short	Short;
typedef signed int 		Int;
typedef signed long 	Long;

typedef unsigned char 	U1b;
typedef unsigned short	U2b;
typedef unsigned long	U4b;
typedef signed char 	S1b;
typedef signed short	S2b;
typedef signed long 	S4b;

//typedef signed char 	BYTE;
//typedef signed short	WORD;
//typedef signed long	DWORD;

//	============== itrondef.h====================
//----- Macros ----------------------------------------------------------------

#define NORMAL	0
#define ERROR	-1
#define TRUE	1
#define FALSE	0

// データ変換
#define MAKEWORD(low, high)		((U_int)(((U_char)(low)) | ((U_int)((U_char)(high))) << 8))
#define MAKEDWORD(low, high)	((U_long)(((U_int)(low)) | ((U_long)((U_int)(high))) << 16))
#define LOWORD(l)				((U_int)(l))
#define HIWORD(l)				((U_int)(((U_long)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)				((U_char)(w))
#define HIBYTE(w)				((U_char)(((U_int)(w) >> 8) & 0xFF))
#define LONG_LOBYTE(l)			(U_char)l
#define LONG_MIBYTE(l)			(U_char)(l >> 8)
#define LONG_HIBYTE(l)			(U_char)(l >> 16)
#define BYTE_TO_WORD(a)			(a) / 2
#define WORD_TO_BYTE(a)			(a) * 2


//----- Defines -----------------------------------------------------

// 状態
#define TRUE		1				// 真
#define FALSE		0				// 偽
#define ON			1				// ON
#define OFF			0				// OFF
#define OK 			0				// 正常終了
#define NG 			1				// 異常終了
#define WAY			2				// 処理中
#define WAY2		3				// 処理中2
#define NG2			4				// NG2
// データ位置
#define	H_BYTE		0				// 上位バイト
#define	H_WORD		0				// 上位ワード
#define	L_BYTE		1				// 下位バイト
#define	L_WORD		1				// 下位ワード
#define	HH_BYTE		0				// HHバイト
#define	HL_BYTE		1				// HLバイト
#define	LH_BYTE		2				// LHバイト
#define	LL_BYTE		3				// LLバイト
// BIT
#define BIT0		0x1
#define BIT1		0x2
#define BIT2		0x4
#define BIT3		0x8
#define BIT4		0x10
#define BIT5		0x20
#define BIT6		0x40
#define BIT7		0x80
#define BIT8		0x100
#define BIT9		0x200
#define BIT10		0x400
#define BIT11		0x800
#define BIT12		0x1000
#define BIT13		0x2000
#define BIT14		0x4000
#define BIT15		0x8000
// ステージ
#define STAGE0		0
#define STAGE1		1
#define STAGE2		2
#define STAGE3		3
#define STAGE4		4
#define STAGE5		5
#define STAGE6		6
#define STAGE7		7
#define STAGE8		8
#define STAGE9		9
#define STAGE10		10
#define STAGE11		11
#define STAGE12		12
#define STAGE13		13
#define STAGE14		14
#define STAGE15		15


//----- Typedef -----------------------------------------------------

typedef	unsigned char		UCHAR;
typedef	unsigned short		USHORT;
typedef	unsigned long		ULONG;

typedef unsigned char		U_char;			// CHAR  8 Bit
typedef char				S_char;			// CHAR  8 Bit
typedef unsigned short int	U_int;			// WORD 16 Bit
typedef signed short int	S_int;			// INT	 16 Bit
typedef unsigned long int	U_long;			// DWORD 32 bit
typedef signed long int 	S_long;			// DINT  32 bit



//	============== itron.h======================
typedef signed char		B;				/* signed 8 bit integer				*/
typedef signed short	H;				/* signed 16 bit integer			*/
typedef signed long		W;				/* signed 32 bit integer			*/

typedef unsigned char	UB;				/* unsigned 8 bit integer			*/
typedef unsigned short	UH;				/* unsigned 16 bit integer			*/
typedef unsigned long	UW;				/* unsigned 32 bit integer			*/

typedef B				VB;				/* variable data type (8 bit)		*/
typedef H				VH;				/* variable data type (16 bit)		*/
typedef W				VW;				/* variable data type (32 bit)		*/

typedef void			*VP;			/* pointer to variable data type	*/
typedef void			(*FP)(void);	/* program start address			*/

typedef int				INT;			/* signed integer (CPU dependent)	*/
typedef unsigned int	UINT;			/* unsigned integer (CPU dependent) */

typedef INT				BOOL;			/* Bool value						*/

typedef W				FN;				/* function code					*/
typedef W				ER;				/* error code						*/
typedef H				ID;				/* object ID (xxxid)				*/
typedef UW				ATR;			/* attribute						*/
typedef UW				STAT;			/* object status					*/
typedef UW				MODE;			/* action mode						*/
typedef H				PRI;			/* task priority					*/
typedef UW				SIZE;			/* memory area size					*/

typedef W				TMO;			/* time out							*/
typedef UW				RELTIM;			/* relative time					*/

typedef struct {						/* system clock						*/
			UH			utime;			/* current date/time (upper)		*/
/***		VH			_Hrsv;				   reserved					  ***/
			UW			ltime;			/* current date/time (lower)		*/
		} SYSTIM;

typedef INT				VP_INT;			/* integer or pointer to var. data	*/

typedef	ER				ER_BOOL;		/* error code or bool value			*/
typedef ER				ER_ID;			/* error code or object ID			*/
typedef ER				ER_UINT;		/* error code or unsigned integer	*/

#endif	/* _SSC_CMNDEF_H_ */
