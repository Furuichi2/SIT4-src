/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						アドレス定義ファイル								*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
//#define	Ver_005
#define	Ver_100


#ifdef	Ver_005

#define	E_GAMEN_BASE	0x00060000						/* 領域先頭ｱﾄﾞﾚｽ	*/

//#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320ﾋﾞｯﾄﾊﾟﾀｰﾝ登録	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x0001c000)		/* 320ﾋﾞｯﾄﾊﾟﾀｰﾝ登録	*/
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00008000)		/* 基本情報ｱﾄﾞﾚｽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x00013180)		/* ｳｨﾝﾄﾞｳ情報ｱﾄﾞﾚｽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x00015E80)		/* 生産文言ｱﾄﾞﾚｽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00018B08)		/* ｲﾝﾀｰﾛｯｸ文言ｱﾄﾞﾚｽ	*/
#define	E_GAMEN_TOP2	E_GAMEN_TOP						/* 第二カ国語 基本情報ｱﾄﾞﾚｽ	*/

#else

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define	E_GAMEN_BASE	0x00500000						/* 領域先頭ｱﾄﾞﾚｽ	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320ﾋﾞｯﾄﾊﾟﾀｰﾝ登録	*/
#define	E_INTROCK_CHAR	(E_GAMEN_BASE + 0x00006000)		/* ｲﾝﾀｰﾛｯｸ出力文字	*/		//2009/07/14
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00010000)		/* 基本情報ｱﾄﾞﾚｽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x0001B180)		/* ｳｨﾝﾄﾞｳ情報ｱﾄﾞﾚｽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x0001DE80)		/* 生産文言ｱﾄﾞﾚｽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00020B08)		/* ｲﾝﾀｰﾛｯｸ文言ｱﾄﾞﾚｽ	*/
#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x00028000)		/* 第二カ国語 基本情報ｱﾄﾞﾚｽ	*/
#define	E_GAIZI_TOP		(E_GAMEN_BASE + 0x000A0000)		/* 外字情報ｱﾄﾞﾚｽ	*/				//V01l
#define	E_FROM_INI_TOP	(E_GAMEN_BASE + 0x00008000)		/* 設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ	*/
#define	E_FROM_INI_TOP2	(E_FROM_INI_TOP + 0x1606)		/* 設定値初期ﾃﾞｰﾀ型名称ｱﾄﾞﾚｽ	*/
#define	E_2language 	(E_GAMEN_TOP2 - E_GAMEN_TOP)/2	//第二カ国語
#else
#define	E_GAMEN_BASE	0xB9000000						/* 領域先頭ｱﾄﾞﾚｽ	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320ﾋﾞｯﾄﾊﾟﾀｰﾝ登録	*/
#define	E_INTROCK_CHAR	(E_GAMEN_BASE + 0x00006000)		/* ｲﾝﾀｰﾛｯｸ出力文字	*/		//2009/07/14
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00010000)		/* 基本情報ｱﾄﾞﾚｽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x0001B180)		/* ｳｨﾝﾄﾞｳ情報ｱﾄﾞﾚｽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x0001DE80)		/* 生産文言ｱﾄﾞﾚｽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00020B08)		/* ｲﾝﾀｰﾛｯｸ文言ｱﾄﾞﾚｽ	*/
//V06m	#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x0001C000)		/* 第二カ国語 基本情報ｱﾄﾞﾚｽ	*/
#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x00020000)		/* 第二カ国語 基本情報ｱﾄﾞﾚｽ	*/
#define	E_GAIZI_TOP		(E_GAMEN_BASE + 0x000A0000)		/* 外字情報ｱﾄﾞﾚｽ	*/				//V01l
#define	E_FROM_INI_TOP	(E_GAMEN_BASE + 0x00008000)		/* 設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ	*/
#define	E_FROM_INI_TOP2	(E_FROM_INI_TOP + 0x1606)		/* 設定値初期ﾃﾞｰﾀ型名称ｱﾄﾞﾚｽ	*/
#define	E_FROM_INI_TOP3	(E_FROM_INI_TOP + 0x3000)		/* 設定値初期ﾃﾞｰﾀ型名称ｱﾄﾞﾚｽ	*/	//V06n
#define	E_2language 	(E_GAMEN_TOP2 - E_GAMEN_TOP)	//第二カ国語
#endif

#endif



/****************************************************************************/
