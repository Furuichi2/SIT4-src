/************************************************************************************/
/*																					*/
/*		�鰹ｬ松製作所殿向け　ＳＩＴ−Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			固定データ　テーブル													*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-21
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義


/****************************************************/
/*	半角文字パターン　テーブル(有効ﾃﾞｰﾀ：下位ﾊﾞｲﾄ)	*/
/****************************************************/
//const	UNb		Han_MPtn_Table[256][16]={
const	UNs		Han_MPtn_Table[256][16]={

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 00	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 01	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 02	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 03	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 04	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 05	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 06	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 07	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 08	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 09	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0A	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0B	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0C	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0D	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0E	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 0F	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 10	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 11	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 12	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 13	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 14	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 15	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 16	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 17	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 18	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 19	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1A	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1B	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1C	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1D	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1E	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 1F	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 20	SPACE
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x010,0x010,0x010,0x010,0x010,0x010,0x010,	// 21	"!"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x06C,0x06C,0x024,0x048,0x000,0x000,0x000,	// 22	"""
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x024,0x024,0x024,0x026,0x03C,0x064,0x024,	// 23	"#"
		0x024,0x026,0x03C,0x064,0x024,0x024,0x024,0x000 },

	{	0x000,0x008,0x01C,0x02A,0x049,0x048,0x028,0x01C,	// 24	"$"
		0x00A,0x009,0x009,0x049,0x02A,0x01C,0x008,0x000 },

	{	0x000,0x022,0x054,0x054,0x024,0x008,0x008,0x008,	// 25	"PARSENT"
		0x010,0x010,0x010,0x024,0x02A,0x02A,0x044,0x000 },

	{	0x000,0x038,0x044,0x044,0x044,0x044,0x058,0x020,	// 26	"&"
		0x020,0x052,0x052,0x04A,0x04A,0x044,0x03A,0x000 },

	{	0x000,0x060,0x060,0x020,0x040,0x000,0x000,0x000,	// 27	"'"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x004,0x008,0x008,0x010,0x010,0x020,0x020,0x020,	// 28	"("
		0x020,0x020,0x020,0x010,0x010,0x008,0x008,0x004 },

	{	0x020,0x010,0x010,0x008,0x008,0x004,0x004,0x004,	// 29	")"
		0x004,0x004,0x004,0x008,0x008,0x010,0x010,0x020 },

	{	0x000,0x000,0x008,0x008,0x049,0x049,0x02A,0x01C,	// 2A	"*"
		0x008,0x01C,0x02A,0x049,0x049,0x008,0x008,0x000 },

	{	0x000,0x000,0x000,0x008,0x008,0x008,0x008,0x07F,	// 2B	"//"
		0x008,0x008,0x008,0x008,0x008,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 2C	","
		0x000,0x000,0x000,0x000,0x060,0x060,0x020,0x040 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x07E,	// 2D	"-"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 2E	"."
		0x000,0x000,0x000,0x000,0x000,0x060,0x060,0x000 },

	{	0x000,0x002,0x004,0x004,0x004,0x008,0x008,0x008,	// 2F	"/"
		0x010,0x010,0x010,0x020,0x020,0x020,0x040,0x000 },

	{	0x000,0x03C,0x042,0x042,0x042,0x042,0x042,0x042,	// 30	"0"
		0x042,0x042,0x042,0x042,0x042,0x042,0x03C,0x000 },

	{	0x000,0x008,0x018,0x028,0x008,0x008,0x008,0x008,	// 31	"1"
		0x008,0x008,0x008,0x008,0x008,0x008,0x01C,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x002,0x004,	// 32	"2"
		0x008,0x010,0x020,0x020,0x040,0x040,0x07E,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x002,0x004,0x018,	// 33	"3"
		0x004,0x002,0x042,0x042,0x042,0x024,0x018,0x000 },

	{	0x000,0x004,0x00C,0x00C,0x014,0x014,0x014,0x024,	// 34	"4"
		0x024,0x044,0x044,0x07E,0x004,0x004,0x004,0x000 },

	{	0x000,0x07E,0x040,0x040,0x040,0x058,0x064,0x042,	// 35	"5"
		0x002,0x002,0x002,0x042,0x042,0x024,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x040,0x058,0x064,	// 36	"6"
		0x042,0x042,0x042,0x042,0x042,0x024,0x018,0x000 },

	{	0x000,0x07E,0x042,0x042,0x042,0x004,0x004,0x008,	// 37	"7"
		0x008,0x008,0x008,0x008,0x008,0x008,0x008,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x024,0x018,	// 38	"8"
		0x024,0x042,0x042,0x042,0x042,0x024,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x042,0x042,	// 39	"9"
		0x026,0x01A,0x002,0x042,0x042,0x024,0x018,0x000 },

	{	0x000,0x000,0x000,0x000,0x018,0x018,0x000,0x000,	// 3A	":"
		0x000,0x000,0x000,0x000,0x018,0x018,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x018,0x018,0x000,0x000,	// 3B	"//"
		0x000,0x000,0x000,0x000,0x018,0x018,0x008,0x010 },

	{	0x000,0x000,0x002,0x004,0x008,0x010,0x020,0x040,	// 3C	"<"
		0x040,0x020,0x010,0x008,0x004,0x002,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x07E,0x000,	// 3D	"="
		0x000,0x07E,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x040,0x020,0x010,0x008,0x004,0x002,	// 3E	">"
		0x002,0x004,0x008,0x010,0x020,0x040,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 3F	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x01C,0x022,0x041,0x049,0x055,0x055,0x055,	// 40	"@"
		0x055,0x055,0x055,0x04A,0x040,0x021,0x01E,0x000 },

	{	0x000,0x018,0x018,0x024,0x024,0x024,0x024,0x024,	// 41	"A"
		0x03C,0x042,0x042,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x078,0x044,0x042,0x042,0x042,0x044,0x078,	// 42	"B"
		0x044,0x042,0x042,0x042,0x044,0x078,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x040,0x040,0x040,	// 43	"C"
		0x040,0x040,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x078,0x044,0x042,0x042,0x042,0x042,0x042,	// 44	"D"
		0x042,0x042,0x042,0x042,0x044,0x078,0x000,0x000 },

	{	0x000,0x07E,0x040,0x040,0x040,0x040,0x040,0x07C,	// 45	"E"
		0x040,0x040,0x040,0x040,0x040,0x07E,0x000,0x000 },

	{	0x000,0x07E,0x040,0x040,0x040,0x040,0x040,0x07C,	// 46	"F"
		0x040,0x040,0x040,0x040,0x040,0x040,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x040,0x040,0x040,0x04E,	// 47	"G"
		0x042,0x042,0x042,0x042,0x026,0x01A,0x000,0x000 },

	{	0x000,0x042,0x042,0x042,0x042,0x042,0x042,0x07E,	// 48	"H"
		0x042,0x042,0x042,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x01C,0x008,0x008,0x008,0x008,0x008,0x008,	// 49	"I"
		0x008,0x008,0x008,0x008,0x008,0x01C,0x000,0x000 },

	{	0x000,0x002,0x002,0x002,0x002,0x002,0x002,0x002,	// 4A	"J"
		0x002,0x002,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x042,0x044,0x044,0x048,0x048,0x050,0x060,	// 4B	"K"
		0x050,0x048,0x048,0x044,0x044,0x042,0x000,0x000 },

	{	0x000,0x040,0x040,0x040,0x040,0x040,0x040,0x040,	// 4C	"L"
		0x040,0x040,0x040,0x040,0x040,0x07E,0x000,0x000 },

	{	0x000,0x041,0x063,0x063,0x055,0x055,0x049,0x049,	// 4D	"M"
		0x041,0x041,0x041,0x041,0x041,0x041,0x000,0x000 },

	{	0x000,0x042,0x062,0x062,0x052,0x052,0x052,0x052,	// 4E	"N"
		0x04A,0x04A,0x04A,0x046,0x046,0x042,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x042,0x042,	// 4F	"O"
		0x042,0x042,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x078,0x044,0x042,0x042,0x042,0x044,0x078,	// 50	"P"
		0x040,0x040,0x040,0x040,0x040,0x040,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x042,0x042,	// 51	"Q"
		0x042,0x042,0x052,0x04A,0x024,0x01A,0x000,0x000 },

	{	0x000,0x078,0x044,0x042,0x042,0x042,0x044,0x078,	// 52	"R"
		0x050,0x050,0x048,0x048,0x044,0x042,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x040,0x040,0x020,0x018,	// 53	"S"
		0x004,0x002,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x07F,0x008,0x008,0x008,0x008,0x008,0x008,	// 54	"T"
		0x008,0x008,0x008,0x008,0x008,0x008,0x000,0x000 },

	{	0x000,0x042,0x042,0x042,0x042,0x042,0x042,0x042,	// 55	"U"
		0x042,0x042,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x041,0x041,0x041,0x041,0x022,0x022,0x022,	// 56	"V"
		0x022,0x014,0x014,0x014,0x008,0x008,0x000,0x000 },

	{	0x000,0x041,0x041,0x041,0x041,0x049,0x049,0x049,	// 57	"W"
		0x055,0x055,0x055,0x055,0x022,0x022,0x022,0x000 },

	{	0x000,0x042,0x042,0x042,0x024,0x024,0x018,0x018,	// 58	"X"
		0x024,0x024,0x024,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x041,0x041,0x041,0x022,0x022,0x014,0x014,	// 59	"Y"
		0x008,0x008,0x008,0x008,0x008,0x008,0x000,0x000 },

	{	0x000,0x07E,0x002,0x004,0x004,0x008,0x008,0x010,	// 5A	"Z"
		0x010,0x020,0x020,0x040,0x040,0x07E,0x000,0x000 },

	{	0x00E,0x008,0x008,0x008,0x008,0x008,0x008,0x008,	// 5B	"["
		0x008,0x008,0x008,0x008,0x008,0x008,0x008,0x00E },

// IF ENGLISH
//	0x	000,0x040,0x040,0x020,0x020,0x010,0x010,0x008H	// 5C	ﾊﾞｯｸｽﾗｯｼｭ
//	0x	008,0x004,0x004,0x002,0x002,0x001,0x001,0x000H
// ELSE

	{	0x000,0x041,0x041,0x022,0x022,0x014,0x014,0x07F,	// 5C	"\"
		0x008,0x008,0x07F,0x008,0x008,0x008,0x008,0x000 },

// ENDIF
	{	0x038,0x008,0x008,0x008,0x008,0x008,0x008,0x008,	// 5D	"]"
		0x008,0x008,0x008,0x008,0x008,0x008,0x008,0x038 },

	{	0x018,0x024,0x042,0x000,0x000,0x000,0x000,0x000,	// 5E	"^"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 5F	"_"
		0x000,0x000,0x000,0x000,0x000,0x07E,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 60	SPACE
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x018,0x024,0x042,	// 61	"a"
		0x01A,0x026,0x042,0x042,0x026,0x01A,0x000,0x000 },

	{	0x000,0x040,0x040,0x040,0x040,0x058,0x064,0x042,	// 62	"b"
		0x042,0x042,0x042,0x042,0x064,0x058,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x018,0x024,0x042,	// 63	"c"
		0x040,0x040,0x040,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x002,0x002,0x002,0x002,0x01A,0x026,0x042,	// 64	"d"
		0x042,0x042,0x042,0x042,0x026,0x01A,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x018,0x024,0x042,	// 65	"e"
		0x042,0x07E,0x040,0x040,0x022,0x01C,0x000,0x000 },

	{	0x000,0x008,0x014,0x010,0x010,0x07C,0x010,0x010,	// 66	"f"
		0x010,0x010,0x010,0x010,0x010,0x010,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x01A,0x026,0x042,	// 67	"g"
		0x042,0x042,0x042,0x026,0x01A,0x002,0x044,0x038 },

	{	0x000,0x040,0x040,0x040,0x040,0x058,0x064,0x042,	// 68	"h"
		0x042,0x042,0x042,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x000,0x010,0x010,0x000,0x000,0x010,0x010,	// 69	"i"
		0x010,0x010,0x010,0x010,0x010,0x010,0x000,0x000 },

	{	0x000,0x000,0x004,0x004,0x000,0x000,0x004,0x004,	// 6A	"j"
		0x004,0x004,0x004,0x004,0x004,0x024,0x024,0x018 },

	{	0x000,0x040,0x040,0x040,0x040,0x042,0x044,0x048,	// 6B	"k"
		0x050,0x060,0x050,0x048,0x044,0x042,0x000,0x000 },

	{	0x000,0x030,0x010,0x010,0x010,0x010,0x010,0x010,	// 6C	"l"
		0x010,0x010,0x010,0x010,0x010,0x010,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x056,0x069,0x049,	// 6D	"m"
		0x049,0x049,0x049,0x049,0x049,0x049,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x058,0x064,0x042,	// 6E	"n"
		0x042,0x042,0x042,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x018,0x024,0x042,	// 6F	"o"
		0x042,0x042,0x042,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x058,0x064,0x042,	// 70	"p"
		0x042,0x042,0x042,0x064,0x058,0x040,0x040,0x040 },

	{	0x000,0x000,0x000,0x000,0x000,0x01A,0x026,0x042,	// 71	"q"
		0x042,0x042,0x042,0x026,0x01A,0x002,0x002,0x002 },

	{	0x000,0x000,0x000,0x000,0x000,0x02C,0x032,0x022,	// 72	"r"
		0x020,0x020,0x020,0x020,0x020,0x020,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x018,0x024,0x042,	// 73	"s"
		0x040,0x03C,0x002,0x042,0x024,0x018,0x000,0x000 },

	{	0x000,0x000,0x000,0x010,0x010,0x07C,0x010,0x010,	// 74	"t"
		0x010,0x010,0x010,0x012,0x012,0x00C,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x042,0x042,0x042,	// 75	"u"
		0x042,0x042,0x042,0x042,0x026,0x01A,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x042,0x042,0x042,	// 76	"v"
		0x042,0x024,0x024,0x024,0x018,0x018,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x041,0x049,0x049,	// 77	"w"
		0x055,0x055,0x055,0x055,0x022,0x022,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x042,0x042,0x024,	// 78	"x"
		0x018,0x018,0x024,0x042,0x042,0x042,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x042,0x042,0x042,	// 79	"y"
		0x044,0x024,0x024,0x018,0x008,0x010,0x020,0x040 },

	{	0x000,0x000,0x000,0x000,0x000,0x07E,0x002,0x004,	// 7A	"z"
		0x008,0x008,0x010,0x020,0x040,0x07E,0x000,0x000 },

	{	0x006,0x008,0x008,0x008,0x008,0x008,0x008,0x010,	// 7B	"{"
		0x010,0x008,0x008,0x008,0x008,0x008,0x008,0x006 },

	{	0x000,0x008,0x008,0x008,0x008,0x008,0x008,0x000,	// 7C	"|"
		0x000,0x008,0x008,0x008,0x008,0x008,0x008,0x000 },

	{	0x030,0x008,0x008,0x008,0x008,0x008,0x008,0x004,	// 7D	"}"
		0x004,0x008,0x008,0x008,0x008,0x008,0x008,0x030 },

	{	0x030,0x049,0x006,0x000,0x000,0x000,0x000,0x000,	// 7E	"nami"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// 7F	SPACE
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 80	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 81	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 82	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 83	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 84	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 85	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 86	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 87	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 88	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 89	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8A	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8B	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8C	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8D	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8E	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 8F	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 90	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 91	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 92	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 93	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 94	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 95	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 96	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 97	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 98	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 99	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9A	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9B	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9C	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9D	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9E	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// 9F	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// A0	SPACE
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// A1	"maru"
		0x000,0x000,0x000,0x000,0x020,0x050,0x050,0x020 },

	{	0x01E,0x010,0x010,0x010,0x010,0x010,0x010,0x010,	// A2	"kagiL"
		0x010,0x010,0x010,0x010,0x010,0x010,0x010,0x010 },

	{	0x004,0x004,0x004,0x004,0x004,0x004,0x004,0x004,	// A3	"kagiR"
		0x004,0x004,0x004,0x004,0x004,0x004,0x004,0x07C },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,	// A4	"ten"
		0x000,0x000,0x000,0x000,0x000,0x040,0x020,0x020 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x030,	// A5	"."
		0x030,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x07E,0x002,0x002,0x002,0x07E,0x002,	// A6	"wo"
		0x002,0x004,0x004,0x008,0x008,0x010,0x020,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x07E,0x002,0x002,	// A7	"a"
		0x014,0x018,0x010,0x010,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x000,0x000,0x002,0x002,0x004,0x004,	// A8	"i"
		0x008,0x018,0x068,0x008,0x008,0x008,0x008,0x000 },

	{	0x000,0x000,0x000,0x000,0x008,0x008,0x07E,0x042,	// A9	"u"
		0x042,0x042,0x002,0x004,0x004,0x008,0x030,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x03E,0x008,0x008,	// AA	"e"
		0x008,0x008,0x008,0x008,0x008,0x07F,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x008,0x008,0x07E,0x008,	// AB	"o"
		0x018,0x018,0x028,0x028,0x048,0x008,0x018,0x000 },

	{	0x000,0x000,0x000,0x000,0x010,0x010,0x010,0x01F,	// AC	"ya"
		0x071,0x012,0x014,0x010,0x010,0x010,0x010,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x038,0x008,	// AD	"yu"
		0x008,0x008,0x008,0x008,0x008,0x07E,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x07C,0x004,0x004,	// AE	"yo"
		0x004,0x07C,0x004,0x004,0x004,0x07C,0x000,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x052,0x052,0x052,	// AF	"tsu"
		0x052,0x002,0x002,0x004,0x004,0x008,0x030,0x000 },

	{	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x07E,	// B0	"-"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x000,0x07E,0x002,0x002,0x004,0x014,0x018,	// B1	"a"
		0x010,0x010,0x010,0x010,0x010,0x020,0x040,0x000 },

	{	0x000,0x002,0x002,0x002,0x004,0x004,0x004,0x008,	// B2	"i"
		0x018,0x068,0x008,0x008,0x008,0x008,0x008,0x000 },

	{	0x000,0x008,0x008,0x07E,0x042,0x042,0x042,0x042,	// B3	"u"
		0x002,0x004,0x004,0x008,0x008,0x010,0x020,0x000 },

	{	0x000,0x000,0x000,0x03E,0x008,0x008,0x008,0x008,	// B4	"e"
		0x008,0x008,0x008,0x008,0x008,0x07F,0x000,0x000 },

	{	0x000,0x004,0x004,0x004,0x07F,0x004,0x00C,0x00C,	// B5	"o"
		0x014,0x014,0x014,0x024,0x044,0x004,0x00C,0x000 },

	{	0x000,0x010,0x010,0x010,0x07E,0x012,0x012,0x012,	// B6	"ka"
		0x012,0x012,0x012,0x022,0x022,0x022,0x046,0x000 },

	{	0x000,0x010,0x010,0x010,0x010,0x07E,0x010,0x010,	// B7	"ki"
		0x008,0x008,0x07E,0x008,0x008,0x008,0x008,0x000 },

	{	0x000,0x010,0x010,0x01E,0x012,0x022,0x022,0x042,	// B8	"ku"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x020,0x020,0x020,0x03E,0x024,0x024,0x044,	// B9	"ke"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x000,0x07E,0x002,0x002,0x002,0x002,	// BA	"ko"
		0x002,0x002,0x002,0x002,0x002,0x07E,0x000,0x000 },

	{	0x000,0x024,0x024,0x024,0x024,0x07E,0x024,0x024,	// BB	"sa"
		0x024,0x024,0x004,0x008,0x008,0x010,0x020,0x000 },

	{	0x000,0x000,0x060,0x010,0x002,0x002,0x062,0x012,	// BC	"shi"
		0x002,0x002,0x004,0x004,0x008,0x010,0x060,0x000 },

	{	0x000,0x000,0x07C,0x004,0x004,0x004,0x004,0x008,	// BD	"su"
		0x008,0x008,0x014,0x014,0x012,0x022,0x042,0x000 },

	{	0x000,0x020,0x020,0x020,0x03E,0x062,0x024,0x028,	// BE	"se"
		0x020,0x020,0x020,0x020,0x020,0x01E,0x000,0x000 },

	{	0x000,0x000,0x042,0x022,0x022,0x012,0x012,0x002,	// BF	"so"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x010,0x010,0x01E,0x012,0x022,0x032,0x04A,	// C0	"ta"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x002,0x00C,0x078,0x008,0x008,0x008,0x07E,	// C1	"thi"
		0x008,0x008,0x008,0x010,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x052,0x052,0x052,0x052,0x052,0x052,	// C2	"tsu"
		0x002,0x004,0x004,0x008,0x008,0x010,0x020,0x000 },

	{	0x000,0x000,0x03C,0x000,0x000,0x000,0x07E,0x008,	// C3	"te"
		0x008,0x008,0x008,0x010,0x010,0x020,0x040,0x000 },

	{	0x000,0x020,0x020,0x020,0x020,0x020,0x030,0x02C,	// C4	"to"
		0x022,0x020,0x020,0x020,0x020,0x020,0x020,0x000 },

	{	0x000,0x008,0x008,0x008,0x008,0x07E,0x008,0x008,	// C5	"na"
		0x008,0x008,0x008,0x010,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x000,0x03C,0x000,0x000,0x000,0x000,	// C6	"ni"
		0x000,0x000,0x000,0x000,0x000,0x07E,0x000,0x000 },

	{	0x000,0x000,0x07C,0x004,0x004,0x004,0x024,0x014,	// C7	"nu"
		0x008,0x008,0x014,0x012,0x010,0x020,0x040,0x000 },

	{	0x000,0x010,0x008,0x000,0x07E,0x002,0x004,0x004,	// C8	"ne"
		0x008,0x01C,0x02A,0x048,0x008,0x008,0x008,0x000 },

	{	0x000,0x000,0x002,0x002,0x002,0x002,0x002,0x004,	// C9	"no"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x004,0x002,0x012,0x012,0x012,0x012,	// CA	"ha"
		0x011,0x011,0x021,0x021,0x021,0x041,0x000,0x000 },

	{	0x000,0x000,0x040,0x040,0x042,0x04C,0x070,0x040,	// CB	"hi"
		0x040,0x040,0x040,0x040,0x040,0x03E,0x000,0x000 },

	{	0x000,0x000,0x07E,0x002,0x002,0x002,0x002,0x002,	// CC	"fu"
		0x004,0x004,0x008,0x008,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x000,0x010,0x028,0x028,0x028,0x044,	// CD	"he"
		0x004,0x004,0x002,0x002,0x002,0x001,0x000,0x000 },

	{	0x000,0x008,0x008,0x008,0x07F,0x008,0x008,0x02A,	// CE	"ho"
		0x02A,0x02A,0x02A,0x02A,0x049,0x008,0x008,0x000 },

	{	0x000,0x000,0x07E,0x002,0x002,0x002,0x002,0x002,	// CF	"ma"
		0x004,0x044,0x028,0x010,0x008,0x004,0x004,0x000 },

	{	0x000,0x060,0x018,0x004,0x000,0x000,0x060,0x018,	// D0	"mi"
		0x004,0x000,0x000,0x060,0x018,0x004,0x002,0x000 },

	{	0x000,0x008,0x008,0x008,0x008,0x010,0x010,0x010,	// D1	"mu"
		0x010,0x024,0x022,0x022,0x02E,0x072,0x002,0x000 },

	{	0x000,0x004,0x004,0x004,0x004,0x044,0x024,0x014,	// D2	"me"
		0x008,0x008,0x014,0x012,0x010,0x020,0x040,0x000 },

	{	0x000,0x000,0x07E,0x010,0x010,0x010,0x010,0x07E,	// D3	"mo"
		0x010,0x010,0x010,0x010,0x010,0x00E,0x000,0x000 },

	{	0x000,0x010,0x010,0x010,0x010,0x01F,0x071,0x012,	// D4	"ya"
		0x014,0x010,0x010,0x010,0x010,0x010,0x010,0x000 },

	{	0x000,0x000,0x03C,0x004,0x004,0x004,0x004,0x004,	// D5	"yu"
		0x004,0x004,0x004,0x004,0x004,0x07F,0x000,0x000 },

	{	0x000,0x000,0x07E,0x002,0x002,0x002,0x002,0x03E,	// D6	"yo"
		0x002,0x002,0x002,0x002,0x002,0x07E,0x000,0x000 },

	{	0x000,0x000,0x03C,0x000,0x000,0x000,0x07E,0x002,	// D7	"ra"
		0x002,0x002,0x004,0x004,0x008,0x010,0x020,0x000 },

	{	0x000,0x002,0x042,0x042,0x042,0x042,0x042,0x042,	// D8	"ri"
		0x042,0x042,0x004,0x004,0x008,0x010,0x020,0x000 },

	{	0x000,0x008,0x028,0x028,0x028,0x028,0x028,0x028,	// D9	"ru"
		0x028,0x02A,0x02A,0x02A,0x02A,0x02C,0x048,0x000 },

	{	0x000,0x040,0x040,0x040,0x040,0x040,0x042,0x042,	// DA	"re"
		0x042,0x044,0x044,0x048,0x048,0x050,0x060,0x000 },

	{	0x000,0x000,0x000,0x07E,0x042,0x042,0x042,0x042,	// 0x	"ro"
		0x042,0x042,0x042,0x042,0x042,0x07E,0x000,0x000 },

	{	0x000,0x000,0x07E,0x042,0x042,0x042,0x042,0x042,	// DC	"wa"
		0x002,0x004,0x004,0x008,0x008,0x010,0x020,0x000 },

	{	0x000,0x000,0x000,0x070,0x002,0x002,0x002,0x002,	// DD	"n"
		0x002,0x002,0x004,0x004,0x008,0x010,0x060,0x000 },

	{	0x028,0x028,0x000,0x000,0x000,0x000,0x000,0x000,	// DE	"dakuten"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x010,0x028,0x028,0x010,0x000,0x000,0x000,0x000,	// DF	"maru"
		0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E0	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E1	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E2	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E3	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E4	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E5	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E6	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E7	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E8	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// E9	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// EA	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// EB	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// EC	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// ED	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// EE	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// EF	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F0	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F1	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F2	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F3	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F4	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F5	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F6	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F7	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F8	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// F9	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FA	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FB	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FC	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FD	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FE	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 },

	{	0x000,0x018,0x024,0x042,0x042,0x042,0x004,0x008,	// FF	"?"
		0x010,0x010,0x010,0x000,0x000,0x018,0x018,0x000 }
	};



/*** END ***/
