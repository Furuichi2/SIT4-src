/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						グラフ描画処理										*/
/*																			*/
/*						2002.07.31				FIT			mizukawa		*/
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

// #define	DEBUG_1									/* ﾃﾞﾊﾞｯｸﾞ	ｻﾝﾌﾟﾙ描画	*/
// #define	DEBUG_2									/* ﾃﾞﾊﾞｯｸﾞ	仮座標描画	*/
// #define	DEBUG_3									/* ﾃﾞﾊﾞｯｸﾞ	仮座標描画	*/

#define		ALL_DISP			0xFF				/* 全画面表示			*/
#define		HALF_DISP			0x55				/* ウィンドウ表示		*/
#define		NO_DISP				0x00				/* 表示しない			*/

#define		GRAPH_CLEAR_POS		0xA005				/* ｸﾞﾗﾌ描画ｸﾘｱ位置情報	*/
													/* 40BYTE,X=0ｶﾗﾑ,Y=5ｶﾗﾑ	*/
#define		GRAPH_CLM_TOP		  2					/* ｸﾞﾗﾌ描画最左列ｶﾗﾑ	*/
#define		GRAPH_CLM_MAX		 37					/* ｸﾞﾗﾌ描画１行のｶﾗﾑ数	*/
#define		GRAPH_LIN_TOP		  5					/* ｸﾞﾗﾌ描画最上行ｶﾗﾑ	*/
#define		GRAPH_LIN_MAX		  6					/* ｸﾞﾗﾌ描画ﾗｲﾝ数(ｶﾗﾑ )	*/
#define		GRAPH_DOT_MAX		 94					/* ｸﾞﾗﾌ描画ﾗｲﾝ数(ﾄﾞｯﾄ)	*/

#define		GRAPH_DOT_TOP		 81					/* 描画可能範囲 ﾄﾞｯﾄ	*/
#define		GRAPH_DOT_LEFT		 16					/* GRAPH_CLM_TOP * 8	*/
#define		GRAPH_DOT_BTM		174					/* DOT TOP + MAX - 1	*/
#define		GRAPH_DOT_RIGHT		304					/* CLM * 8				*/

#define		GRAPH_RATE			600					/* Y軸演算・分解能		*/
#define		GRAPH_RATE_HALF		(GRAPH_RATE / 2)	/* 四捨五入用			*/

// #define	GRAPH_POINT_MAX		 23					/* 最大座標数			*/
#define		GRAPH_POINT_MAX		 46					/* 最大座標数			*/

#define		GRAPH_X_RATE1		 72					/* ﾄﾞｯﾄ最大値	288 / 4	*/
#define		GRAPH_X_RATE2		125					/* ｸﾞﾗﾌ最大値	500 / 4	*/
#define		GRAPH_Y_RATE1		 93					/* ﾄﾞｯﾄ最大値	-1		*/
#define		GRAPH_Y_RATE2		500					/* ｸﾞﾗﾌ最大値			*/

/* 外部変数 */
WORD		BT[ 8 ];								/* ﾋﾞｯﾄﾃﾞｰﾀ				*/
WORD		OT[ GRAPH_POINT_MAX ][ 2 ];				/* X-Y 座標群 前回値	*/
WORD		PT[ GRAPH_POINT_MAX ][ 2 ];				/* X-Y 座標群			*/
WORD		GT[ GRAPH_DOT_MAX   ][ GRAPH_CLM_MAX ];	/* ｸﾞﾗﾌﾃﾞｰﾀ領域			*/

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];


/* プロトタイプ */
void		GRAPH_DOT_SET	(WORD,WORD,WORD,WORD);	/* ﾄﾞｯﾄﾃﾞｰﾀｾｯﾄ			*/

/****************************************************************************/
/*																			*/
/*	グラフ描画初期処理		：	グラフ描画の初期設定処理を行う。			*/
/*																			*/
/*		GRAPH_DISP_FLG		：	グラフ描画フラグ							*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	GRAPH_INIT	(void)
{
	WORD	i,	t;
	WORD	pos;
	WORD	nop	[ 40 ];
	WORD	lin	[ 40 ];

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* グラフ描画しない		*/

	for (i=0; i<40; i++)		nop[i] = 0x2020;	/* NOP ﾃﾞｰﾀ作成			*/
	for (i=0; i<40; i++)		lin[i] = 0xFFFF;	/* LINE ﾃﾞｰﾀ作成		*/

	pos = GRAPH_CLEAR_POS;							/* ｸﾞﾗﾌ描画位置情報		*/
	i	= 0;										/*						*/

CLEAR_LOOP:											/* ｳｨﾝﾄﾞｳ部分ｸﾘｱ LOOP	*/
	Disp_moji(pos,nop,0);							/* LCD文字列表示・消去	*/
	pos ++;											/* 行ｶﾗﾑ位置更新		*/
	i	++;											/* 次候補				*/
	if (i < GRAPH_LIN_MAX)		goto  CLEAR_LOOP;	/* 						*/

	lin[ 0] = 0xFF00;								/* 外枠描画				*/
	lin[ 1] = 0xFF01;								/*						*/
	lin[38] = 0xFFC0;								/*						*/
	lin[39] = 0xFF00;								/*						*/
	Lcd_draw (0,0,GRAPH_DOT_TOP-1,40,lin);			/*						*/
	Lcd_draw (0,0,GRAPH_DOT_BTM+1,40,lin);			/*						*/
	lin[38] = 0xFF40;								/*						*/
	for (i=GRAPH_DOT_TOP;i<=GRAPH_DOT_BTM;i++){		/*						*/
		Lcd_draw (0, 1,i,1,&lin[ 1]);				/* 左枠					*/
		Lcd_draw (0,38,i,1,&lin[38]);				/* 右枠					*/
	}												/*						*/

	lin[0] = 0xFF40;								/* 内枠描画				*/
	lin[1] = 0xFF10;								/* １点鎖線				*/
	lin[2] = 0xFF08;								/*						*/
	lin[3] = 0xFF02;								/*						*/
	for (i=GRAPH_DOT_TOP+1;i<=GRAPH_DOT_BTM;i+=2){	/*						*/
		Lcd_draw (0, 9,i,1,&lin[0]);				/*						*/
		Lcd_draw (0,16,i,1,&lin[1]);				/*						*/
		Lcd_draw (0,23,i,1,&lin[2]);				/*						*/
		Lcd_draw (0,30,i,1,&lin[3]);				/*						*/
	}												/*						*/

	for (t=0; t<GRAPH_DOT_MAX; t++){				/* ｸﾞﾗﾌﾃﾞｰﾀｸﾘｱ			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群ｸﾘｱ		*/
		OT[i][0] = 0xFFFF;							/* X					*/
		OT[i][1] = 0xFFFF;							/* Y					*/
		PT[i][0] = 0;								/* X					*/
		PT[i][1] = 0;								/* Y					*/
	}												/*						*/

	for (t=0x0080,i=0; i<8; i++){					/* ﾋﾞｯﾄﾃﾞｰﾀ作成			*/
		BT[i] = (0xFF00 | t);						/*						*/
		t = (t >> 1);								/*						*/
	}												/*						*/
}
#else

#define		GRAPH_XDOT_LEG		500
#define		GRAPH_YDOT_LEG		190//200

#define		GRAPH_XDOT_BGN1		70				
#define		GRAPH_XDOT_BGN2		GRAPH_XDOT_BGN1 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN3		GRAPH_XDOT_BGN2 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN4		GRAPH_XDOT_BGN3 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN5		GRAPH_XDOT_BGN4 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN6		GRAPH_XDOT_BGN1 + GRAPH_XDOT_LEG
#define		GRAPH_YDOT_BGN1		160				
#define		GRAPH_YDOT_BGN2		GRAPH_YDOT_BGN1 + GRAPH_YDOT_LEG

void	GRAPH_INIT	(void)
{
	UNs		xpos, ypos;
	short	cnt;
	WORD	i,	t;

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_XDOT_LEG;
	for ( ; 0<cnt; cnt--, xpos++) {					//横上ライン作成
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN2;
	cnt = GRAPH_XDOT_LEG;
	for ( ; 0<cnt; cnt--, xpos++) {					//横下ライン作成
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt--, ypos++) {					//一番左縦ライン作成（左外枠）
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN6;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt--, ypos++) {					//一番右ライン作成（右外枠）
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN2;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//左から２番目ライン作成
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN3;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//左から３番目ライン作成
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN4;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//左から４番目ライン作成
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN5;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//左から５番目ライン作成
		LCD_VRAM[ypos][xpos] = 1;
	}

	for (t=0; t<GRAPH_DOT_MAX; t++){				/* ｸﾞﾗﾌﾃﾞｰﾀｸﾘｱ			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群ｸﾘｱ		*/
		OT[i][0] = 0xFFFF;							/* X					*/
		OT[i][1] = 0xFFFF;							/* Y					*/
		PT[i][0] = 0;								/* X					*/
		PT[i][1] = 0;								/* Y					*/
	}												/*						*/
}
#endif




#if ( SIT_TYPE_SEL == TYPE_SIT3 )	//--------------------------------------------------------------------------------------------

/****************************************************************************/
/*																			*/
/*	グラフ描画処理			：	グラフを描画する。							*/
/*																			*/
/*		GRAPH_DISP_FLG		：	グラフ描画フラグ							*/
/*																			*/
/****************************************************************************/
void	GRAPH_DISP	(void)
{
	WORD	i,	t;
	WORD	x1,	x2,	y1,	y2;
	WORD	ret;
	WORD	XT [ GRAPH_POINT_MAX ];
	WORD	YT [ GRAPH_POINT_MAX ];
	WORD	CT,	ST,	FL;

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* グラフ描画しない		*/

#ifdef	DEBUG_1
	CT	=  0;
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;		/* ｻﾝﾌﾟﾙﾃﾞｰﾀ 座標		*/
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;		/* X = 16 ～ 304		*/
	PT[CT][0]	=  17;		PT[CT++][1]	= 173;		/* Y = 81 ～ 174		*/
	PT[CT][0]	=  17;		PT[CT++][1]	= 173;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;
	PT[CT][0]	=  17;		PT[CT++][1]	= 112;
	PT[CT][0]	=  47;		PT[CT++][1]	= 112;
	PT[CT][0]	=  77;		PT[CT++][1]	= 142;
	PT[CT][0]	=  77;		PT[CT++][1]	= 173;
	PT[CT][0]	= 168;		PT[CT++][1]	=  82;
	PT[CT][0]	= 169;		PT[CT++][1]	= 173;
	PT[CT][0]	= 200;		PT[CT++][1]	= 173;
	PT[CT][0]	= 201;		PT[CT++][1]	=  82;
	PT[CT][0]	= 231;		PT[CT++][1]	= 112;
	PT[CT][0]	= 261;		PT[CT++][1]	= 113;
	PT[CT][0]	= 261;		PT[CT++][1]	= 153;
	PT[CT][0]	= 291;		PT[CT++][1]	= 152;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	goto	DISP_CHECK;
#endif

	ST	= 0;										/*						*/
	ret = SvStepXYDataMake1 (XT,YT,&CT,&ST,&FL);	/* 座標設定関数			*/

#ifdef	DEBUG_2
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

#ifdef	DEBUG_3
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

	if ( FL == 0)						return;		/* 有効ﾃﾞ-ﾀなし			*/
	if ((CT <= 0)||(CT > GRAPH_POINT_MAX))			/* 有効ﾃﾞｰﾀ数 NG		*/
										return;		/*						*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* ｸﾞﾗﾌﾃﾞｰﾀｺﾋﾟｰ			*/
		if (i < CT){								/* 有効ﾃﾞｰﾀ				*/
			PT[i][0] = (XT[i]*GRAPH_X_RATE1/GRAPH_X_RATE2+GRAPH_DOT_LEFT);
			PT[i][1] = (YT[i]*GRAPH_Y_RATE1/GRAPH_Y_RATE2+GRAPH_DOT_TOP );
		}else{										/*						*/
			PT[i][0] = 0;							/* X ｸﾘｱ				*/
			PT[i][1] = 0;							/* Y ｸﾘｱ				*/
		}											/*						*/
	}												/*						*/

DISP_CHECK:											/* 描画判定				*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群変化ﾁｪｯｸ	*/
		if ((OT[i][0] != PT[i][0]) ||				/* 0 : X 座標			*/
			(OT[i][1] != PT[i][1]))					/* 1 : Y 座標			*/
		goto	DISP_STEP;							/* 変化あり 描画		*/
	}												/*						*/
	return;											/* 変化なし				*/

DISP_STEP:											/* 描画開始				*/
	for (t=0; t<GRAPH_DOT_MAX; t++){				/* ｸﾞﾗﾌﾃﾞｰﾀｸﾘｱ			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<(CT-1); i++)						/* ｸﾞﾗﾌﾃﾞｰﾀｾｯﾄ			*/
		GRAPH_DOT_SET (PT[i][0],PT[i][1],PT[i+1][0],PT[i+1][1]);

	for (t=0; t<GRAPH_DOT_MAX; t++)					/* ｸﾞﾗﾌﾃﾞｰﾀ描画			*/
		Lcd_draw (1,GRAPH_CLM_TOP,GRAPH_DOT_TOP+t,GRAPH_CLM_MAX,&GT[t][0]);

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群保存		*/
		OT[i][0] = PT[i][0];						/* X					*/
		OT[i][1] = PT[i][1];						/* Y					*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	ドットデータセット		：	グラフ用ドットデータをセットする。			*/
/*																			*/
/*		Ｘ－Ｙ座標２点で示されるライン（ドットデータ）を					*/
/*		描画用データ域にセットする。描画は行わない。						*/
/*																			*/
/****************************************************************************/
void	GRAPH_DOT_SET	(WORD X1,WORD Y1,WORD X2,WORD Y2)
{
	WORD	i;
	WORD	bt;
	WORD	xb,		yb;
	WORD	cnt,	db;
	WORD	wb,		zb;
	WORD	tb,		nb,		hb;
	WORD	x_dif,	y_dif;
	WORD	minus;
	WORD	temp;
	WORD	rate_0;

	if ((X1 < GRAPH_DOT_LEFT) || (X1 > GRAPH_DOT_RIGHT) ||
		(X2 < GRAPH_DOT_LEFT) || (X2 > GRAPH_DOT_RIGHT) ||
		(Y1 < GRAPH_DOT_TOP ) || (Y1 > GRAPH_DOT_BTM  ) ||
		(Y2 < GRAPH_DOT_TOP ) || (Y2 > GRAPH_DOT_BTM  ))
		return;										/* 描画範囲 ｴﾗｰ			*/

//	先頭のバイト位置、ビット位置を算出 ///////////////////////////////////////
	yb = ( Y1 - GRAPH_DOT_TOP );					/* Y軸ﾊﾞｲﾄ 位置算出		*/
	xb = ((X1 - GRAPH_DOT_LEFT) / 8);				/* X軸ﾊﾞｲﾄ 位置算出		*/
	bt = ((X1 - GRAPH_DOT_LEFT) % 8);				/* 開始ﾋﾞｯﾄ位置算出		*/

//	タテ線、ヨコ線処理 ///////////////////////////////////////////////////////
	if (X1 == X2){									/* ﾀﾃ線 X軸方向変化なし	*/
		if (Y1 == Y2){								/* Y軸方向変化なし		*/
			GT[yb][xb] |= BT[bt];					/* 1 ﾄﾞｯﾄ座標 ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y軸 下方向変化		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				GT[yb+nb][xb] |= BT[bt];			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}else{										/* Y軸 上方向変化		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				GT[yb-nb][xb] |= BT[bt];			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 対応なし		*/

	if (Y1 == Y2){									/* ﾖｺ線 Y軸方向変化なし	*/
		for (i=X1; i<=X2; i++){						/* X軸のﾋﾞｯﾄ数繰り返す	*/
			GT[yb][xb] |= BT[bt];					/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			bt ++;									/* X軸 次ﾋﾞｯﾄに更新		*/
			if (bt > 7){							/*						*/
				bt  = 0;							/*						*/
				xb += 1;							/* 次ﾊﾞｲﾄへ移動			*/
			}										/*						*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	通常の線（ななめ線）描画処理 /////////////////////////////////////////////
	if (Y1 < Y2){									/* 描画方向を求める		*/
			minus = 0;								/* plus  direction	下	*/
			y_dif = ((Y2 - Y1) * GRAPH_RATE);		/* 600倍で演算する		*/
	}else{											/* max 95 * 600 = 57000	*/
			minus = 1;								/* minus direction	上	*/
			y_dif = ((Y1 - Y2) * GRAPH_RATE);		/*						*/
	}												/*						*/

	x_dif  = (X2 - X1);								/* X軸のﾋﾞｯﾄ変化数算出	*/
	rate_0 = (y_dif / x_dif);						/* X軸に対するY軸率		*/

	GT[yb][xb] |= BT[bt];							/* 先頭ﾄﾞｯﾄ座標 ON		*/
	zb	= yb;										/* Y軸前回値保存		*/
	cnt	= 1; 										/* ﾄﾞｯﾄｶｳﾝﾀ				*/

DOT_LOOP:											/*						*/
	if (cnt > x_dif)				return;			/* 全ﾄﾞｯﾄ描画終了		*/

	temp = (rate_0 * cnt);							/* Y軸の変化数を算出	*/
	db	 = (temp / GRAPH_RATE);						/*						*/
	temp = (temp % GRAPH_RATE);						/*						*/
	if (temp >= GRAPH_RATE_HALF)	db += 1;		/* 四捨五入				*/

	if (minus == 0){								/* plus  direction		*/
			wb = (yb + db);							/* Y軸次位置			*/
			tb = (wb - zb);							/* Y軸差分				*/
	}else{											/* minus direction		*/
			wb = (yb - db);							/*						*/
			tb = (zb - wb);							/*						*/
	}												/*						*/

//	Ｙ軸移動量が１以下の場合のドット描画処理 /////////////////////////////////
	if (tb <= 1){									/* つなぎ線不要			*/
		bt ++;										/* X位置を次ﾋﾞｯﾄに更新	*/
		if (bt > 7){								/* 次ﾊﾞｲﾄへ移動			*/
			bt  = 0;								/*						*/
			xb += 1;								/*						*/
		}											/*						*/
		GT[wb][xb] |= BT[bt];						/* ﾄﾞｯﾄ座標 ON			*/
		zb = wb;									/* Y軸前回値保存		*/
		cnt ++;										/*						*/
		goto	DOT_LOOP;							/*						*/
	}												/*						*/

//	Ｙ軸移動量が大きい場合のつなぎ線描画処理 /////////////////////////////////
	hb = ((tb + 1) / 2);							/* Y軸の半分の位置算出	*/
	nb	= 0; 										/* ﾗｲﾝｶｳﾝﾀ				*/

LIN_LOOP:											/* つなぎ線描画			*/
	if (nb > tb){									/* 全ﾄﾞｯﾄ描画終了		*/
		zb = wb;									/* Y軸前回値保存		*/
		cnt ++;										/*						*/
		goto	DOT_LOOP;							/*						*/
	}
	if (nb == hb){									/* 半分					*/
		bt ++;										/* X位置を次ﾋﾞｯﾄに更新	*/
		if (bt > 7){								/* 次ﾊﾞｲﾄへ移動			*/
			bt  = 0;								/*						*/
			xb += 1;								/*						*/
		}											/*						*/
	}
	if (minus == 0)		wb = (zb + nb);				/* Y軸次位置			*/
	else				wb = (zb - nb);				/*						*/

	GT[wb][xb] |= BT[bt];							/* ﾄﾞｯﾄ座標 ON			*/
	nb ++;											/*						*/
	goto	LIN_LOOP;								/*						*/
}

#else		//--------------------------------------------------------------------------------------------------------------------

/****************************************************************************/
/*																			*/
/*	グラフ描画処理			：	グラフを描画する。							*/
/*																			*/
/*		GRAPH_DISP_FLG		：	グラフ描画フラグ							*/
/*																			*/
/****************************************************************************/
void	GRAPH_DISP	(void)
{
	WORD	i,	t;
	WORD	x1,	x2,	y1,	y2;
	WORD	ret;
	WORD	XT [ GRAPH_POINT_MAX ];
	WORD	YT [ GRAPH_POINT_MAX ];
	WORD	CT,	ST,	FL;

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* グラフ描画しない		*/

	ST	= 0;										/*						*/
	ret = SvStepXYDataMake1 (XT,YT,&CT,&ST,&FL);	/* 座標設定関数			*/

#ifdef	DEB_1
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 100;
	XT[CT] = 200;		YT[CT++] = 100;
	XT[CT] = 200;		YT[CT++] = 200;
	XT[CT] = 300;		YT[CT++] = 200;
	XT[CT] = 300;		YT[CT++] = 300;
	XT[CT] = 400;		YT[CT++] = 300;
	XT[CT] = 400;		YT[CT++] = 400;
	XT[CT] = 500;		YT[CT++] = 400;
	XT[CT] = 500;		YT[CT++] = 500;
#endif
#ifdef	DEB_2
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] =  50;		YT[CT++] = 500;
	XT[CT] = 100;		YT[CT++] =  50;
	XT[CT] = 150;		YT[CT++] = 200;
	XT[CT] = 200;		YT[CT++] = 150;
	XT[CT] = 250;		YT[CT++] = 300;
	XT[CT] = 300;		YT[CT++] = 250;
	XT[CT] = 350;		YT[CT++] = 400;
	XT[CT] = 400;		YT[CT++] = 350;
	XT[CT] = 450;		YT[CT++] = 350;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

	if ( FL == 0)						return;		/* 有効ﾃﾞ-ﾀなし			*/
	if ((CT <= 0)||(CT > GRAPH_POINT_MAX))			/* 有効ﾃﾞｰﾀ数 NG		*/
										return;		/*						*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* ｸﾞﾗﾌﾃﾞｰﾀｺﾋﾟｰ			*/
		if (i < CT){								/* 有効ﾃﾞｰﾀ				*/
			PT[i][0] = XT[i];
			PT[i][1] = (YT[i]*GRAPH_YDOT_LEG)/GRAPH_XDOT_LEG;
		}else{										/*						*/
			PT[i][0] = 0;							/* X ｸﾘｱ				*/
			PT[i][1] = 0;							/* Y ｸﾘｱ				*/
		}											/*						*/
	}												/*						*/

DISP_CHECK:											/* 描画判定				*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群変化ﾁｪｯｸ	*/
		if ((OT[i][0] != PT[i][0]) ||				/* 0 : X 座標			*/
			(OT[i][1] != PT[i][1]))					/* 1 : Y 座標			*/
		goto	DISP_STEP;							/* 変化あり 描画		*/
	}												/*						*/
	return;											/* 変化なし				*/

DISP_STEP:											/* 描画開始				*/
	for (i=0; i<(CT-1); i++)						/* ｸﾞﾗﾌﾃﾞｰﾀｾｯﾄ			*/
		GRAPH_DOT_SET (PT[i][0],PT[i][1],PT[i+1][0],PT[i+1][1]);

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y 座標群保存		*/
		OT[i][0] = PT[i][0];						/* X					*/
		OT[i][1] = PT[i][1];						/* Y					*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	ドットデータセット		：	グラフ用ドットデータをセットする。			*/
/*																			*/
/*		Ｘ－Ｙ座標２点で示されるライン（ドットデータ）を					*/
/*		描画用データ域にセットする。描画は行わない。						*/
/*																			*/
/****************************************************************************/
void	GRAPH_DOT_SET	(WORD X1,WORD Y1,WORD X2,WORD Y2)
{
	WORD	i;
	WORD	bt;
	WORD	xb,		yb;
	WORD	cnt,	db;
	WORD	wb,		zb;
	WORD	tb,		nb,		hb;
	WORD	x_dif,	y_dif;
	WORD	minus;
	WORD	temp;
	WORD	rate_0;
	UNl		wkl;


//	先頭のバイト位置、ビット位置を算出 ///////////////////////////////////////
	yb = Y1+GRAPH_YDOT_BGN1;//( Y1 - GRAPH_DOT_TOP );					/* Y軸ﾊﾞｲﾄ 位置算出		*/
	xb = X1+GRAPH_XDOT_BGN1;//((X1 - GRAPH_DOT_LEFT) / 8);				/* X軸ﾊﾞｲﾄ 位置算出		*/
	bt = 4;//((X1 - GRAPH_DOT_LEFT) % 8);				/* 開始ﾋﾞｯﾄ位置算出		*/

//	タテ線、ヨコ線処理 ///////////////////////////////////////////////////////
	if (X1 == X2){									/* ﾀﾃ線 X軸方向変化なし	*/
		if (Y1 == Y2){								/* Y軸方向変化なし		*/
			LCD_VRAM[yb][xb] = bt;						/* 1 ﾄﾞｯﾄ座標 ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y軸 下方向変化		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				LCD_VRAM[yb+nb][xb] = bt;			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}else{										/* Y軸 上方向変化		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y軸のﾋﾞｯﾄ数繰り返す	*/
				LCD_VRAM[yb-nb][xb] |= bt;			/* 縦ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 対応なし		*/

	if (Y1 == Y2){									/* ﾖｺ線 Y軸方向変化なし	*/
		for (i=X1; i<=X2; i++){						/* X軸のﾋﾞｯﾄ数繰り返す	*/
			LCD_VRAM[yb][xb] = bt;					/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
			xb += 1;								/* 次ﾊﾞｲﾄへ移動			*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	通常の線（ななめ線）描画処理 /////////////////////////////////////////////
	if (Y1 < Y2){									/* 描画方向を求める		*/
		y_dif = (Y2 - Y1);				/* 600倍で演算する		*/
		x_dif = (X2 - X1);				/* X軸のﾋﾞｯﾄ変化数算出	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				yb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					yb++;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
	else
	{											/* max 95 * 600 = 57000	*/
		y_dif = (Y1 - Y2);				/* 600倍で演算する		*/
		x_dif = (X2 - X1);				/* X軸のﾋﾞｯﾄ変化数算出	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				yb--;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
					yb--;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb--)
				{
					LCD_VRAM[yb][xb] = bt;				/* 横ﾗｲﾝ ﾄﾞｯﾄ座標 ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
}
#endif		//--------------------------------------------------------------------------------------------------------------------


#include	"ssc_pvwave.c"			//V05o(INS)


/*** END ***/

