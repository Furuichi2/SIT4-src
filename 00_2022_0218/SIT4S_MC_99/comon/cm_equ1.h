/*	***********************************	*/
/*	***		基本		***	*/
/*	***********************************	*/
#define 	cBIT0	0x1	/* */
#define 	cBIT1	0x2	/* */
#define 	cBIT2	0x4	/* */
#define 	cBIT3	0x8	/* */
#define 	cBIT4	0x10	/* */
#define 	cBIT5	0x20	/* */
#define 	cBIT6	0x40	/* */
#define 	cBIT7	0x80	/* */
#define 	cBIT8	0x100	/* */
#define 	cBIT9	0x200	/* */
#define 	cBIT10	0x400	/* */
#define 	cBIT11	0x800	/* */
#define 	cBIT12	0x1000	/* */
#define 	cBIT13	0x2000	/* */
#define 	cBIT14	0x4000	/* */
#define 	cBIT15	0x8000	/* */

//	*******************************************
//	***					***
//	***					***
//	***					***
//	*******************************************
//
//	共通定義 型に意味のある場合下記を仕様する
typedef unsigned char 	Uchar;		//
typedef unsigned short	Ushort;		//
typedef unsigned int	Uint;		//
typedef unsigned long	Ulong;		//
typedef signed char 	Char;		//
typedef signed short	Short;		//
typedef signed int 	Int;		//
typedef signed long 	Long;		//

/*	共通定義 ﾊﾞｲﾄ長に意味のある場合下記を仕様する	*/
typedef unsigned char 	U1b;		/*	u1b	*/
typedef unsigned short	U2b;		/*	u2b	*/
typedef unsigned long	U4b;		/*	u4b	*/
typedef signed char 	S1b;		/*	s1b	*/
typedef signed short	S2b;		/*	s2b	*/
typedef signed long 	S4b;		/*	s4b	*/

/*	============ 通常この記述を使用 =============	*/
//typedef signed char 	BYTE;		/*	s1b	*/
//typedef signed short	WORD;		/*	s2b	*/
//typedef signed long	DWORD;		/*	s4b	*/

/*	***********************************	*/
/*	***		sh3		***	*/
/*	***********************************	*/
/*	=================================	*/
#define		Debug_YES	1
#define		Debug_NO	0
#define		CMPILE_YES	1
#define		CMPILE_NO	0

#define		CB_STS_BUF_MAX		512		//128
#define		CB_TRD_BUF_MAX		2048	//2048 total 2048確保
#define		CB_TRD_SMP_CNT		128		//128個
