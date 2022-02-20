/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ルーレット表示処理									*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long


//#define		DEBUG_AUTO
#define		DEG_ZENKAKU
#define		DEG_DISP_NEW


// #define	SUMILATE
#ifdef		SUMILATE
#include	<stdio.h>
#include	<stdlib.h>
#endif

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		BIT_06		0x0040

#define		ALL_DISP	0xFF					/* 全画面表示				*/
#define		HALF_DISP	0x55					/* ウィンドウ表示			*/
#define		NO_DISP		0x00					/* 表示しない				*/

EXTRN		DWORD		DEG_DISP_TBL	  [];	/* 4倍角ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ配列	*/
EXTRN		DWORD		RULET_TBL_BASE	  [];	/* ルーレット●表示データ	*/
EXTRN		DWORD		RULET_TBL_BASE_00 [];	/* ルーレット○表示データ	*/
EXTRN		DWORD		HAN_RULET_TBL_BASE_00 [];	/* ルーレット○表示データ 2003-01-24 */
EXTRN		DWORD		RULET_BASE_TBL_TBL[];	/* ルーレット枠表示データ	*/
EXTRN		DWORD		HAN_RULET_BASE_TBL_TBL[];	/* ルーレット枠表示データ 2003-01-24 */

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
EXTRN		DWORD		DEG4_DISP_TBL	  [];	/* 4倍角ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ配列	*/
#endif

/* ﾌﾟﾛﾄﾀｲﾌﾟ */
void		DEG_DISP		(void);				/* 角度４倍角表示処理		*/
void		RULET_GAMEN_DISP(void);				/* ルーレット画面表示		*/
void		RULET_GAMEN_INIT(void);				/* ルーレット初期設定		*/
void		RULET_GAMEN_ALL	(void);				/* ルーレット●全描画		*/
void		RULET_GAMEN_CLR	(void);				/* ルーレット●全クリア		*/
void		RULET_DISP_SUB	(WORD);				/* ●描画サブルーチン		*/
void		RULET_CLEAR_SUB	(WORD);				/* ●消去サブルーチン		*/
void		RULET_CLEAR_SUB2(WORD);				/* ●消去サブルーチン２		*/

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
#include	"ssc_rulet_pos.c"
#endif


/****************************************************************************/
/*																			*/
/*	角度数字表示処理		：	４倍角数字表示								*/
/*																			*/
/*		エンコーダの角度データが変化したら、角度（数字３桁）を表示する。	*/
/*		ＬＣＤ１に、１文字ずつ表示×３回を行う。							*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	：	角度データ		（小数点１位 0～3599まで）	*/
/*																			*/
/*		ENCO_DATA_BCD		：	角度データを格納する						*/
/*		DEG_DISP_FLG		：	角度表示フラグ								*/
/*		DEG_DISP_LST		：	前回値保存領域								*/
/*		DEG_DISP_TBL		：	４倍角データのアドレステーブル				*/
/*																			*/
/*		画面切り替え時は、前回値保存領域をクリアすること。					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	DEG_DISP		(void)
{
	WORD	i,		t,		x;
	WORD	C1,		C2;
	WORD	disp,	indx;
	WORD	keta,	line;
	WORD	data[3];
	WORD	buff[4];
	BYTE*	addr;
	DWORD	calc;

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* 角度表示しない		*/

//	C1 = PVP_NOW_ANGLE00;							/* BCDﾃﾞｰﾀ作成			*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCDﾃﾞｰﾀ作成			*/

	C2 = (C1 % 10);
	ENCO_DATA_BCD = C2;
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 4);
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 8);						/* 保存					*/

	if (ENCO_DATA_BCD == DEG_DISP_LST)	return;		/* 角度ﾃﾞｰﾀ変化なし		*/
	DEG_DISP_LST = ENCO_DATA_BCD;					/* 前回値保存			*/

	data[2] = (ENCO_DATA_BCD & 0x0F00) >> 8;		/* 表示用ﾃﾞｰﾀ格納		*/
	data[1] = (ENCO_DATA_BCD & 0x00F0) >> 4;		/*						*/
	data[0] = (ENCO_DATA_BCD & 0x000F);				/*						*/

	if (data[2] ==  0){								/* ﾌﾞﾗﾝｸ表示CHECK		*/
		data[2] =  10;								/* 10 でﾌﾞﾗﾝｸ表示		*/
		if (data[1] ==  0)							/*						*/
			data[1] =  10;							/*						*/
	}

	for(i=0; i<3; i++){								/* ３文字				*/
		disp  = (2 - i);							/* 角度数値 2～0桁		*/
		keta  = (4 + (4 * i));						/* 表示桁位置			*/
		line  = (4 * 16);							/* 表示行4ｶﾗﾑ目から		*/
													/*						*/
		indx  = data[disp];							/* 表示数字				*/
		calc  = DEG_DISP_TBL[indx];					/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
		addr  = (BYTE*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/

		for(t=0; t<32; t++){						/* 縦2ｶﾗﾑ分 32bit		*/
			for(x=0; x<4; x++){						/* 表示ﾃﾞｰﾀ格納			*/
				buff[x] = ((*addr) & 0x00FF);		/*						*/
				addr ++;							/*						*/
			}										/*						*/
			Lcd_draw(1,keta,line,4,buff);			/* LCD1 1Line(1dot)表示	*/
			line ++;								/*						*/
		}											/*						*/
	}
}
#else
#ifdef DEG_DISP_NEW
/*★★★★★★★★★	ＳＩＴ－４用（新）	★★★★★★★★★*/
void	DEG_DISP		(void)
{
	WORD	C1, C2, xdot, ydot, startx, starty, wk2b;
	WORD	i, t, x, j;
	WORD	disp,	indx;
	WORD	keta,	line;
	WORD	data[3];
	WORD	buff;
	WORD*	addr;
	DWORD	calc;

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* 角度表示しない		*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCDﾃﾞｰﾀ作成			*/
#ifdef	DEBUG_AUTO
	C1 = (DEBUG_CNT / 10);					/* BCDﾃﾞｰﾀ作成			*/
#endif

	C2 = (C1 % 10);
	ENCO_DATA_BCD = C2;
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 4);
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 8);						/* 保存					*/

	if (ENCO_DATA_BCD == DEG_DISP_LST)	return;		/* 角度ﾃﾞｰﾀ変化なし		*/
	DEG_DISP_LST = ENCO_DATA_BCD;					/* 前回値保存			*/

	data[2] = (ENCO_DATA_BCD & 0x0F00) >> 8;		/* 表示用ﾃﾞｰﾀ格納		*/
	data[1] = (ENCO_DATA_BCD & 0x00F0) >> 4;		/*						*/
	data[0] = (ENCO_DATA_BCD & 0x000F);				/*						*/

	if (data[2] ==  0){								/* ﾌﾞﾗﾝｸ表示CHECK		*/
		data[2] =  10;								/* 10 でﾌﾞﾗﾝｸ表示		*/
		if (data[1] ==  0)							/*						*/
			data[1] =  10;							/*						*/
	}

	/* 100桁目 */
	startx = 64;
	starty = 128;
	indx  = data[2];							/* 表示数字				*/
	calc  = DEG4_DISP_TBL[indx];				/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr  = (WORD*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* 縦64bit				*/
		for(x=0; x<4; x++){						/* 表示ﾃﾞｰﾀ格納			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dotデータのﾋﾞｯﾄが立っている？
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	/* 010桁目 */
	startx = 64+64;
	starty = 128;
	indx  = data[1];							/* 表示数字				*/
	calc  = DEG4_DISP_TBL[indx];				/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr  = (WORD*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* 縦64bit				*/
		for(x=0; x<4; x++){						/* 表示ﾃﾞｰﾀ格納			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dotデータのﾋﾞｯﾄが立っている？
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	/* 001桁目 */
	startx = 64+64+64;
	starty = 128;
	indx  = data[0];							/* 表示数字				*/
	calc  = DEG4_DISP_TBL[indx];				/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr  = (WORD*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* 縦64bit				*/
		for(x=0; x<4; x++){						/* 表示ﾃﾞｰﾀ格納			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dotデータのﾋﾞｯﾄが立っている？
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	disp_moji_s_rif (
		6,		/*t_p->M_LEN,*/
		8*8,	/*t_p->X_POS,*/
		8*16,	/*t_p->Y_POS,*/
		0x0404	/*t_p->SIZE,*/
		);
}
#else
/*★★★★★★★★★	ＳＩＴ－４用（旧）	★★★★★★★★★*/
void	DEG_DISP		(void)
{
	WORD	C1;
	UNi		i, j, k;
	UNb		wk[16], wk1[16];
	UNs		c_wk[16], w_bf, bcd_d;
	char	c_wk1[16];

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* 角度表示しない		*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCDﾃﾞｰﾀ作成			*/
#ifdef	DEBUG_AUTO
	C1 = (DEBUG_CNT / 10);					/* BCDﾃﾞｰﾀ作成			*/
#endif

	memset(&wk[0], E_AS_SP, 16);					//領域 ｽﾍﾟｰｽ ｸﾘｱ

	bcd_d = HEX_BCD4(C1);					//HEX → BCD 変換
	BCD_ASCII(bcd_d, &wk[0]);					//BCD→ASCII 変換

	for(i = 7; i > 0 ; i--) {
		if( wk[i-1] == E_AS_TEN){				//”.”　 ［ASCIIｺｰﾄﾞ］
			break;
		}
		else if(wk[i] == '0' || wk[i] == E_AS_SP) {
			wk[i] = E_AS_SP;					//スペース［ASCIIｺｰﾄﾞ］
		}
		else {
			break;
		}
	}
	for( j=0,i=3 ; i > 0 ; i--, j++ ){
		w_bf = wk[i-1];
		w_bf <<= 8;
		if(i <= 1){
			w_bf |= (UNb)E_AS_SP;				//スペース［ASCIIｺｰﾄﾞ］
		}
		else{
			i--;
			w_bf |= wk[i-1];
		}
		c_wk[j] = w_bf;
	}

#ifdef	DEG_ZENKAKU
	i = 3;
	k = i;
	for( j=0 ; i > 0 ; i--, j++ ){
		wk1[j] = wk[i-1];
	}
	Ascii_Sjis(k, &wk1[0], &c_wk[0]);			//ASCII -> S-JIS 変換
#endif

	disp_moji_s_color (
		6,					/*t_p->M_LEN,*/
		8*8,				/*t_p->X_POS,*/
		8*16,				/*t_p->Y_POS,*/
		0,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,		/*t_p->B_COL1,*/
		0x0404,				/*t_p->SIZE,*/
		&c_wk[0], 
		LCD_VBASE
		);

	disp_moji_s_rif (
		6,		/*t_p->M_LEN,*/
		8*8,	/*t_p->X_POS,*/
		8*16,	/*t_p->Y_POS,*/
		0x0404	/*t_p->SIZE,*/
		);
}
#endif
#endif


/****************************************************************************/
/*																			*/
/*	ルーレット画面表示														*/
/*																			*/
/*		エンコーダの角度に応じて、ＬＣＤ２に●を描画する。					*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	：	角度データ		（小数点１位 0～3599まで）	*/
/*		PVP_TAIKITEN_POS	：	待機点データ	（小数点１位 0～3599まで）	*/
/*		HS_PVP_TAKIKI_FLG	：	待機点通過フラグ（通過＝１）				*/
/*																			*/
/*		SEQ_PAR_101			：	シーケンサ・高速ルーレット表示許可			*/
/*		SEQ_PAR_222			：	シーケンサ・正転／逆転						*/
/*																			*/
/*		CB1_SPMDAT_PV		：	ＳＰＭ現在値								*/
/*		SYS_HIGHSPM_B1		：	高速描画開始ＳＰＭ値						*/
/*		SYS_LOWSPM_B1		：	高速描画停止ＳＰＭ値						*/
/*																			*/
/*		TAIKITEN_DAT		：	前回待機点データ（１／１０）				*/
/*		TAIKI_ZEN_POS		：	前回描画位置	（１／１０）				*/
/*		TAIKI_ZEN_MOD		：	前回描画方向	（正転≠０／逆転＝０）		*/
/*																			*/
/*		RULET_DISP_FLG		：	ルーレット表示フラグ（ｳｨﾝﾄﾞｳ表示中＝0x55）	*/
/*		RULET_HIGH_FLG		：	高速描画フラグ								*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_DISP(void)
{
	WORD	i,		t;
	WORD	real_deg;
	WORD	real_tik;
	WORD	temp;
	WORD	deg0,	deg1;
	WORD	tk_0,	tk_1;
	WORD	md_0,	md_1;
	WORD	wk_0,	wk_1;
	WORD	cnt;

	if (RULET_DISP_FLG == NO_DISP)		return;		/* ﾙｰﾚｯﾄ表示しない		*/

//	高速描画（塗りつぶし）判定 ///////////////////////////////////////////////
//	if ((SEQ_PAR_101 & BIT_06) != 0){				/* ﾙｰﾚｯﾄ高速表示許可？	*/
//		if (RULET_HIGH_FLG == 0){					/* 高速ﾙｰﾚｯﾄ描画でない	*/
//			if (CB1_SPMDAT_PV > SYS_HIGHSPM_B1)		/* SPM HIGHｼｷｲ値以上？	*/
//				RULET_HIGH_FLG = ALL_DISP;			/* 高速ﾙｰﾚｯﾄ描画ON		*/
//		}											/*						*/
//		else{										/*						*/
//			if (CB1_SPMDAT_PV <= SYS_LOWSPM_B1)		/* SPM LOWｼｷｲ値以下？	*/
//				RULET_HIGH_FLG = NO_DISP;			/* 高速ﾙｰﾚｯﾄ描画OFF		*/
//				TAIKI_ZEN_POS  = TAIKITEN_DAT;		/* 前位置を待機点にする	*/
//		}											/*						*/
//		if (RULET_HIGH_FLG == ALL_DISP){			/* 高速ﾙｰﾚｯﾄ描画ON		*/
//			RULET_GAMEN_ALL();						/* 全描画				*/
//			return;									/*						*/
//		}											/*						*/
//	}												/*						*/
//	else											/*						*/
//		RULET_HIGH_FLG = 0;							/* 高速ﾙｰﾚｯﾄ描画OFF		*/

	RULET_HIGH_FLG = 0;								/* DEBUG				*/

//	前回値／今回値設定 ///////////////////////////////////////////////////////
	real_deg = (PVP_NOW_ANGLE_RNA / 10);			/* 角度ﾃﾞｰﾀ取得			*/
#ifdef	DEBUG_AUTO
	real_deg = (DEBUG_CNT / 10);			/* 角度ﾃﾞｰﾀ取得			*/
#endif
	deg1	 = (real_deg / 10);						/* ｴﾝｺｰﾄﾞ値	1/10		*/
	temp	 = (real_deg % 10);						/*						*/
	if (temp >=  5)					deg1 ++;		/* 四捨五入				*/
	if (deg1 >= 36)					deg1 = 0;		/* 360度 = 0度			*/
	deg0		  = TAIKI_ZEN_POS;					/* 前回描画位置			*/
	TAIKI_ZEN_POS = deg1;							/*						*/

	real_tik = (PVP_TAIKITEN_POS / 10);				/* 待機点ﾃﾞｰﾀ取得		*/
	tk_1	 = (real_tik / 10);						/* 待機点値	1/10		*/
	temp	 = (real_tik % 10);						/*						*/
	if (temp >=  5)					tk_1 ++;		/* 四捨五入				*/
	if (tk_1 >= 36)					tk_1 = 0;		/* 360度 = 0度			*/
	tk_0		  = TAIKITEN_DAT;					/* 前回待機点			*/
	TAIKITEN_DAT  = tk_1;							/* 待機点保存			*/

	md_1 = (SEQ_PAR_222 & BIT_06) ^ BIT_06;			/* 回転方向				*/ //2009-10-07 SHIMA 振り子
//	md_1 = 0xFFFF;									/* DEBUG	正転固定	*/
//	md_1 = 0x0000;									/* DEBUG	逆転固定	*/
	md_0		  = TAIKI_ZEN_MOD;					/* 前回転方向			*/
	TAIKI_ZEN_MOD = md_1;							/* 現回転方向保存		*/

//	特殊描画判定 /////////////////////////////////////////////////////////////
	if ((tk_0 != tk_1)	||							/* 待機点変化時			*/
		(md_0 != md_1)	||							/* 回転方向変化時		*/
		(HS_PVP_TAKIKI_FLG != 0)){					/* 待機点通過時			*/
													/*						*/
		RULET_GAMEN_CLR();							/* ●全ｸﾘｱ				*/
													/*						*/
		if(md_1 != 0){								/* 正転方向				*/
			if(deg1 >= tk_1)	cnt =  deg1;		/* ●数ｶｳﾝﾄ				*/
			else				cnt = (deg1 + 36);	/*						*/
			cnt -= tk_1;							/*						*/
			cnt += 1;								/* 描画個数				*/
			t    = tk_1;							/* 描画開始位置			*/
		}											/*						*/
		else{										/* 逆転方向				*/
			if(tk_1 >= deg1)	cnt =  tk_1;		/* ●数ｶｳﾝﾄ				*/
			else				cnt = (tk_1 + 36);	/*						*/
			cnt -= deg1;							/*						*/
			cnt += 1;								/* 描画個数				*/
			t    = deg1;							/* 描画開始位置			*/
		}											/*						*/
		for(i=0; i<cnt; i++){						/*						*/
			RULET_DISP_SUB(t);						/* 描画ｻﾌﾞﾙｰﾁﾝ			*/
			t++;									/*						*/
			if (t >= 36)	t = 0;					/*						*/
		}											/*						*/
													/*						*/
		HS_PVP_TAKIKI_FLG = 0;						/* 待機点通過ﾌﾗｸﾞｸﾘｱ	*/
		return;										/*						*/
	}												/*						*/

	if	(deg1 == tk_1){								/* 待機点と一致時		*/
		if (deg0 != deg1)	RULET_GAMEN_CLR();		/* ●全ｸﾘｱ				*/
		RULET_DISP_SUB (tk_1);						/* 描画ｻﾌﾞﾙｰﾁﾝ			*/
		TAIKITEN_FLG = 0;							/* 待機点通過ﾌﾗｸﾞｸﾘｱ	*/
		return;										/*						*/
	}												/*						*/

	if (deg1 == deg0)								/* 角度変化なしの場合	*/
		return;										/* なにもしない			*/

//	通常描画処理 /////////////////////////////////////////////////////////////
	if (md_1 != 0){									/* 正転方向				*/
		if (deg0 >= tk_1)	wk_0 =  deg0;			/* 前位置０補正			*/
		else				wk_0 = (deg0 + 36);		/*						*/
		if (deg1 >= tk_1)	wk_1 =  deg1;			/* 現位置０補正			*/
		else				wk_1 = (deg1 + 36);		/*						*/
		wk_0 -= tk_1;								/* 待機点からの相対数	*/
		wk_1 -= tk_1;								/*						*/
													/*						*/
		if (wk_1 >= wk_0){							/* 描画					*/
			cnt	= (wk_1 - wk_0) + 1;				/* ●数ｶｳﾝﾄ				*/
			t	= deg0;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_DISP_SUB(t);					/* 描画ｻﾌﾞﾙｰﾁﾝ			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
		else{										/* ｸﾘｱ					*/
			cnt = (wk_0 - wk_1);					/* ○数ｶｳﾝﾄ				*/
			t	= (deg1 + 1);						/*						*/
			if (t >= 36)		t = 0;				/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_CLEAR_SUB(t);					/* ｸﾘｱｻﾌﾞﾙｰﾁﾝ			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
	}
	else{											/* 逆転方向				*/
		if (deg0 > tk_1)	wk_0 =  deg0;			/* 前位置０補正			*/
		else				wk_0 = (deg0 + 36);		/*						*/
		if (deg1 > tk_1)	wk_1 =  deg1;			/* 現位置０補正			*/
		else				wk_1 = (deg1 + 36);		/*						*/
		wk_0 -= tk_1;								/* 待機点からの相対数	*/
		wk_1 -= tk_1;								/*						*/
													/*						*/
		if (wk_0 >= wk_1){							/* 描画					*/
			cnt = (wk_0 - wk_1) + 1;				/* ●数ｶｳﾝﾄ				*/
			t	= deg1;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_DISP_SUB(t);					/* 描画ｻﾌﾞﾙｰﾁﾝ			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
		else{										/* ｸﾘｱ					*/
			cnt	= (wk_1 - wk_0);					/* ○数ｶｳﾝﾄ				*/
			t	= deg0;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_CLEAR_SUB(t);					/* ｸﾘｱｻﾌﾞﾙｰﾁﾝ			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	ルーレット画面初期設定	：	最初に１回コールすること。					*/
/*																			*/
/*		ＬＣＤ１にルーレットの枠と４ヵ所の白ヌキ○を表示する。				*/
/*		ＬＣＤ２に●のクリアデータを表示しておく。							*/
/*																			*/
/*		RURET_BASE_TBL_TBL	：	枠表示データのアドレステーブル				*/
/*		RULET_TBL_BASE_00	：	○表示データのアドレステーブル				*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	RULET_GAMEN_INIT(void)
{
	WORD	i,		t,		x;
	WORD	keta,	line,	cnt;
	WORD	gyou,	dotl;
	WORD	buff[20];
	WORD	temp;
	WORD*	addr;
	BYTE*	bitd;
	DWORD	calc;

	for(i=0; i<20; i++){							/* 枠×２０回			*/
		/* V00m */
		if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？
			calc  = HAN_RULET_BASE_TBL_TBL[i];		/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/  /* 斉藤作成 2003-01-24 */
		}
		else {
			calc  = RULET_BASE_TBL_TBL[i];			/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
		}
		addr  = (WORD*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
													/*						*/
		line  = ((*addr) / 40);						/* 表示行位置			*/
		addr++;										/*						*/
		keta  =  (*addr);							/* 表示桁位置			*/
		addr++;										/*						*/
		cnt   = ((*addr) - keta + 1);				/* 表示ｶﾗﾑ数			*/
		addr++;										/*						*/
		addr++;										/* SKIP					*/
		bitd  = (BYTE*)addr;						/* ﾊﾞｲﾄｱｸｾｽ用			*/

		for(t=0; t<16; t++){							/* 縦1ｶﾗﾑ分 16bit		*/
			gyou	 = (line / 16);						/* 行位置算出			*/
			dotl	 = (line % 16);						/* 端数ドット			*/
			for(x=0; x<cnt; x++){						/* 表示ﾃﾞｰﾀ格納			*/
				buff[x] = ((*bitd) & 0x00FF);			/* 型変換				*/
				bitd++;									/* ﾊﾞｲﾄｱﾄﾞﾚｽ更新		*/
				LCD_WORK1[gyou][dotl][keta+x]=buff[x];	/* 表示ﾃﾞｰﾀ格納			*/
			}											/*						*/
			Lcd_draw(0,keta,line,cnt,buff);				/* LCD1 1Line(1dot)表示	*/
			line ++;									/*						*/
		}
	}

	for(i=0; i<4; i++){								/* ○×４回				*/
		/* V00m */
		if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？
			calc  = HAN_RULET_TBL_BASE_00[i];		/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/  /* 斉藤作成 2003-01-24 */
		}
		else {
			calc  = RULET_TBL_BASE_00[i];			/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
		}
		addr  = (WORD*)calc;						/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/
													/*						*/
		line  = ((*addr) / 40);						/* 表示行位置			*/
		keta  = ((*addr) % 40);						/* 表示桁位置			*/
		addr++;										/*						*/

		for(t=0; t<8; t++){								/* 縦1/2ｶﾗﾑ分 8bit	*/
			gyou	 = (line / 16);						/* 行位置算出		*/
			dotl	 = (line % 16);						/* 端数ドット		*/
			buff[0]  = LCD_WORK1[gyou][dotl][keta  ];	/* 現在表示ﾃﾞｰﾀ		*/
			buff[1]  = LCD_WORK1[gyou][dotl][keta+1];	/*					*/
			buff[0] |= (((*addr) & 0xFF00) >> 8);		/* ○ﾃﾞｰﾀを上書き	*/
			buff[1] |=  ((*addr) & 0x00FF);				/*					*/
			Lcd_draw(0,keta,line,2,buff);				/* LCD1 1Line表示	*/
			addr ++;									/*					*/
			line ++;									/*					*/
			LCD_WORK1[gyou][dotl][keta  ] = buff[0];	/* 表示ﾃﾞｰﾀ格納		*/
			LCD_WORK1[gyou][dotl][keta+1] = buff[1];	/*					*/
		}												/*					*/
	}

	TAIKI_ZEN_POS	= TAIKITEN_DAT;					/* 描画前位置を待機点に	*/
	temp			= RULET_DISP_FLG;				/* 一時保存				*/
	RULET_DISP_FLG	= ALL_DISP;						/* 全画面表示			*/
	RULET_GAMEN_CLR	();								/* LCD2 ● ｸﾘｱ			*/
	RULET_DISP_FLG	= temp;							/*						*/
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	RULET_GAMEN_INIT(void)
{
	WORD	temp;
	UNb		*rulet_t1;

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？	V01y
#include "ssc_circleHAN.c"
	}
	else {
#include "ssc_circle.c"
	}

	TAIKI_ZEN_POS	= TAIKITEN_DAT;					/* 描画前位置を待機点に	*/
	temp			= RULET_DISP_FLG;				/* 一時保存				*/
	RULET_DISP_FLG	= ALL_DISP;						/* 全画面表示			*/
	RULET_GAMEN_CLR	();								/* LCD2 ● ｸﾘｱ			*/
	RULET_DISP_FLG	= temp;							/*						*/
}
#endif
/****************************************************************************/
/*																			*/
/*	ルーレット全描画	（未使用）											*/
/*																			*/
/*		ＬＣＤ２の●領域を全て描画する。描画サブルーチンをコールする。		*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_ALL	(void)
{
	WORD	i;
	for(i=0; i<36; i++){							/* ●×３６回			*/
		RULET_DISP_SUB	(i);						/* 描画ｻﾌﾞﾙｰﾁﾝ			*/
	}
}
/****************************************************************************/
/*																			*/
/*	ルーレット全クリア														*/
/*																			*/
/*		ＬＣＤ２の●領域を全てクリアする。クリアサブルーチン２をコールする。*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_CLR	(void)
{
	WORD	i;
	for(i=0; i<36; i++){							/* ●×３６回			*/
		RULET_CLEAR_SUB2(i);						/* ｸﾘｱｻﾌﾞﾙｰﾁﾝ			*/
	}
}
/****************************************************************************/
/*																			*/
/*	ルーレット描画サブルーチン												*/
/*																			*/
/*		ＬＣＤ２の●領域を描画する。										*/
/*																			*/
/*		RULET_DISP_FLG	：	ルーレット表示フラグ（ｳｨﾝﾄﾞｳ表示中 = 0x55）		*/
/*		RULET_TBL_BASE	：	●表示データのアドレステーブル					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	RULET_DISP_SUB	(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD DRAW  ● %d \n",i);
	return;
#endif

	/* V00m */
	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？
		if (i > 18)	return;							/* 描画ｽｷｯﾌﾟ			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 9)&&(i <= 27))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[i];					/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr	= (WORD*)calc;							/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/

	line	= ((*addr) / 40);						/* 表示行位置			*/
	keta	= ((*addr) % 40);						/* 表示桁位置			*/
	addr++;											/*						*/

	for(t=0; t<8; t++){								/* 縦1/2ｶﾗﾑ分 8bit		*/
		gyou	 = (line / 16);						/* 行位置算出			*/
		dotl	 = (line % 16);						/* 端数ドット			*/
													/*						*/
		buff[0]  = LCD_WORK2[gyou][dotl][keta  ];	/* 現在表示ﾃﾞｰﾀ			*/
		buff[1]  = LCD_WORK2[gyou][dotl][keta+1];	/*						*/
		buff[0] |= (((*addr) & 0xFF00) >> 8);		/* ●ﾃﾞｰﾀを上書き		*/
		buff[1] |=  ((*addr) & 0x00FF);				/*						*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)表示	*/
		addr ++;									/*						*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* 表示ﾃﾞｰﾀ格納			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	RULET_DISP_SUB	(WORD i)
{
	UNs		MARU, col;

	MARU = 0x819C;	//●

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？	V01y
		if (i > 18)	return;							/* 描画ｽｷｯﾌﾟ			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 10)&&(i <= 26))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	col = COL_YELLOW;//YELLOW
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = COL_RED;//RED
	}

	if (SEQ_050_SV & BIT_1) {						//反転　？	V06b
		if (i==rulet_taiki_pos1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//下往復　？	V06b
		if ((i==rulet_taiki_pos1) || (i==rulet_taiki_pos2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,							/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],		/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],		/*t_p->Y_POS,*/
		col,						/*t_p->C_COL,*/
		GAMENn_SCR_COL,				/*t_p->B_COL1,*/
		0x0101,						/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}
#endif
/****************************************************************************/
/*																			*/
/*	ルーレット描画クリアサブルーチン										*/
/*																			*/
/*		ＬＣＤ２の●領域をクリアする。										*/
/*																			*/
/*		RULET_DISP_FLG	：	ルーレット表示フラグ（ｳｨﾝﾄﾞｳ表示中 = 0x55）		*/
/*		RULET_TBL_BASE	：	●表示データのアドレステーブル					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	RULET_CLEAR_SUB	(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD CLEAR ○ %d \n",i);
	return;
#endif

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 9)&&(i <= 27))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[ i ];					/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr	= (WORD*)calc;							/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/

	line	= ((*addr) / 40);						/* 表示行位置			*/
	keta	= ((*addr) % 40);						/* 表示桁位置			*/
	addr++;											/*						*/

	for(t=0; t<8; t++){								/* 縦1/2ｶﾗﾑ分 8bit		*/
		gyou	 = (line / 16);						/* 行位置算出			*/
		dotl	 = (line % 16);						/* 端数ドット			*/
													/*						*/
		buff[0]  = LCD_WORK2[gyou][dotl][keta  ];	/* 現在表示ﾃﾞｰﾀ			*/
		buff[1]  = LCD_WORK2[gyou][dotl][keta+1];	/*						*/
		buff[0] &= (~(((*addr) & 0xFF00) >> 8));	/* ●ﾃﾞｰﾀを消去			*/
		buff[1] &= (~ ((*addr) & 0x00FF));			/*						*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)表示	*/
		addr ++;									/*						*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* 表示ﾃﾞｰﾀ格納			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	RULET_CLEAR_SUB(WORD i)
{
	UNs		MARU, col;

	MARU = 0x819C;	//●

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？	V01y
		if (i > 18)	return;							/* 描画ｽｷｯﾌﾟ			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 10)&&(i <= 26))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	col = GAMENn_SCR_COL;
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = 11;
	}

	if (SEQ_050_SV & BIT_1) {						//反転　？	V06b
		if (i==rulet_taiki_pos1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//下往復　？	V06b
		if ((i==rulet_taiki_pos1) || (i==rulet_taiki_pos2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}
#endif
/****************************************************************************/
/*																			*/
/*	ルーレット描画クリアサブルーチン										*/
/*																			*/
/*		ＬＣＤ２の●領域をクリアする。			（イニシャル、全クリア用）	*/
/*																			*/
/*		RULET_DISP_FLG	：	ルーレット表示フラグ（ｳｨﾝﾄﾞｳ表示中 = 0x55）		*/
/*		RULET_TBL_BASE	：	●表示データのアドレステーブル					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	RULET_CLEAR_SUB2(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD CLEAR2 ○ %d \n",i);
	return;
#endif

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 9)&&(i <= 27))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[ i ];					/* 表示ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ	*/
	addr	= (WORD*)calc;							/* 表示ﾃﾞｰﾀ先頭ｱﾄﾞﾚｽ	*/

	line	= ((*addr) / 40);						/* 表示行位置			*/
	keta	= ((*addr) % 40);						/* 表示桁位置			*/
													/*						*/
	buff[0] = 0;									/*						*/
	buff[1] = 0;									/*						*/

	for(t=0; t<8; t++){								/* 縦1/2ｶﾗﾑ分 8bit		*/
		gyou	 = (line / 16);						/* 行位置算出			*/
		dotl	 = (line % 16);						/* 端数ドット			*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)表示	*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* 表示ﾃﾞｰﾀ格納			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	RULET_CLEAR_SUB2(WORD i)
{
	UNs		MARU, col;
	UNs		tmaru1, tamar1, tmaru2, tamar2;

	MARU = 0x819C;	//●

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//反転　？	V01y
		if (i > 18)	return;							/* 描画ｽｷｯﾌﾟ			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ｳｨﾝﾄﾞｳ表示中			*/
		if ((i >= 10)&&(i <= 26))	return;			/* 描画ｽｷｯﾌﾟ			*/
	}												/*						*/

	col = GAMENn_SCR_COL;
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = COL_GRAY4;
	}

	if (SEQ_050_SV & BIT_1) {						//反転　？	V06b
		tmaru1 = SV_TAIKIKAKU_SRV / 100;
		tamar1 = SV_TAIKIKAKU_SRV % 100;
		if (tamar1 >= 50) {
			tmaru1 = tmaru1+1;
			if (tmaru1 >= 36) {
				tmaru1 = 0;
			}
		}
		rulet_taiki_pos1 = tmaru1;
		if (i==tmaru1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//下往復　？	V06b
		tmaru1 = SV_TAIKIKAKU_SRV / 100;
		tamar1 = SV_TAIKIKAKU_SRV % 100;
		if (tamar1 >= 50) {
			tmaru1 = tmaru1+1;
			if (tmaru1 >= 36) {
				tmaru1 = 0;
			}
		}

//V06d		tmaru2 = ((1800-SV_TAIKIKAKU_SRV)+1800) / 100;
//////		tamar2 = ((1800-SV_TAIKIKAKU_SRV)+1800) % 100;
//////		if (tamar2 >= 50) {
//////			tmaru2 = tmaru2+1;
//////			if (tmaru2 >= 36) {
//////				tmaru2 = 0;
//////			}
//////		}
		tmaru2 = (18-tmaru1)+18;
		if (tmaru2 >= 36) {
			tmaru2 = 0;
		}

		rulet_taiki_pos1 = tmaru1;
		rulet_taiki_pos2 = tmaru2;
		if ((i==tmaru1)||(i==tmaru2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
}
#endif


/****************************************************************************/
