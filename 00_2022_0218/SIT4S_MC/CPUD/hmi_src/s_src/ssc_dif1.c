//;	*******************************************************************
//;	***																***
//;	***																***
//;	***		ＨＭＩ各インターフェイスソフト							***
//;	***																***
//;	***																***
//;	*******************************************************************
#include	"cm_equ1.h"
#include	"CPU_REG.h"
#include	"ssc_wrms.h"
#include	"ssc_ver1.h"
#include	"ssc_def.h"

extern	U2b	LCD_WORK1[15][16][40];
extern	U2b	LCD_WORK2[15][16][40];

extern	U1b	LCD_CTRL[2];
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
extern	U1b	kan_bank_outp;
#else
extern	U4b	kan_bank_outp;
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
#endif

extern	void LCD_CR_ASM(void);
extern	void GLC_BUSY(void);
extern	void WDT_Rifresh(void);
extern	void KATA_SAVE_ASM(void);
extern	void KATA_LOAD_ASM(void);
extern	void kan_rom_top(void);

extern	U2b		SEQ_043_SV;
extern	U2b		SEQ_044_SV;
extern	U2b		SEQ_045_SV;
extern	U2b		SEQ_046_SV;
extern	U2b		SEQ_047_SV;



#pragma	section
//;	***************************************************
//;	***												***
//;	***		型データ→ＦＲＯＭ						***
//;	***												***
//;	***************************************************
void kata_save(U2b no, U2b *poi1)
{
	kata_no_sv = no;
	kata_adr_sv = poi1;

	KATA_SAVE_ASM();
}


//;	***************************************************
//;	***												***
//;	***		型データ←ＦＲＯＭ						***
//;	***												***
//;	***************************************************
void kata_load(U2b no, U2b *poi1)
{
	kata_no_ld = no;
	kata_adr_ld = poi1;

//2016/04/22
	SEQ_043_SV_WK = SEQ_043_SV;			//PUSH	MB(前/全/後)選択、防護柵(前/全/後)選択
	SEQ_044_SV_WK = SEQ_044_SV;			//PUSH	バランサ調圧(設定圧/基準圧)選択、スライド自動調節(生産/段取1/段取2)選択
	SEQ_045_SV_WK = SEQ_045_SV;			//PUSH	ダイクッション調節(左/右)選択
	SEQ_046_SV_WK = SEQ_046_SV;			//PUSH	ダイクッション調節(ｽﾄﾛｰｸ／圧力)
	SEQ_047_SV_WK = SEQ_047_SV;			//PUSH	ADC(搬入/交換/搬出)

	KATA_LOAD_ASM();

//2016/04/22
	SEQ_043_SV = SEQ_043_SV_WK;										//POP	MB(前/全/後)選択、防護柵(前/全/後)選択
	SEQ_044_SV = SEQ_044_SV_WK;										//POP	バランサ調圧(設定圧/基準圧)選択、スライド自動調節(生産/段取1/段取2)選択
	SEQ_045_SV = (SEQ_045_SV & 0xff00) | (SEQ_045_SV_WK & 0x00ff);	//POP	ダイクッション調節(左/右)選択
	SEQ_046_SV = (SEQ_046_SV & 0x00ff) | (SEQ_046_SV_WK & 0xff00);	//POP	ダイクッション調節(ｽﾄﾛｰｸ／圧力)
	SEQ_047_SV = SEQ_047_SV_WK;										//POP	ADC(搬入/交換/搬出)
}


#pragma	section	hwsetup1
//;	***************************************************
//;	***												***
//;	***		ＬＣＤシステムシニシャライズ			***
//;	***												***
//;	***************************************************
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void init_LCD(void)
{
	U2b		i;

	LCD_CTRL[1] = 0x40;							// [[ LCD SYSTEM RESET PROCESSING ]]
	LCD_CTRL[0] = 0x30;							// P1 : [M0:0][M1:0][M2:0][WS:0]
	LCD_CTRL[0] = 0x07;							// P2 : [FX:7][WF:0]
	LCD_CTRL[0] = 0x07;							// P3 : [FY:7]
	LCD_CTRL[0] = 0x27;							// P4 : [CR:27]
	LCD_CTRL[0] = 0x40;							// P5 : [TC/R: 68 -> 40 ]
	LCD_CTRL[0] = 0xef;							// P6 : [LF:EF]
	LCD_CTRL[0] = 0x28;							// P7 : [APL:28]
	LCD_CTRL[0] = 0x00;							// P8 : [APH:00]

	LCD_CTRL[1] = 0x5a;							// [[ HDOT SCR SET PROCESSING ]]
	LCD_CTRL[0] = 0x00;							// SCROLE : [D0,D1,D2 : 000]

	LCD_CTRL[1] = 0x44;							// [[ SCROLL SET PROSECCING ]]
	LCD_CTRL[0] = 0x00;							// SAD1L
	LCD_CTRL[0] = 0x00;							// ASD1H
	LCD_CTRL[0] = 0xef;							// SL1
	LCD_CTRL[0] = 0x80;							// SAD2L
	LCD_CTRL[0] = 0x25;							// SAD2H
	LCD_CTRL[0] = 0xef;							// SL2
	LCD_CTRL[0] = 0x00;							// SAD3L
	LCD_CTRL[0] = 0x4b;							// SAD3H
	LCD_CTRL[0] = 0x00;							// SAD4L
	LCD_CTRL[0] = 0x60;							// SAD4H

	LCD_CTRL[1] = 0x5b;							// [[ OVLAY SET PROCESSING ]]
	LCD_CTRL[0] = 0x0d;							//

	LCD_CTRL[1] = 0x59;							// [[ DISP ON SET ]]
	LCD_CTRL[0] = 0x54;							//
///ためし12-23	LCD_CTRL[0] = 0x04;							//

	LCD_CTRL[1] = 0x46;							// [[ DISPALY V.REM ALL CLEAR ]]
	LCD_CTRL[0] = 0x00;							//
	LCD_CTRL[0] = 0x00;							//

	LCD_CTRL[1] = 0x4c;							// [[ SIFT COMMAND OUTPUT ]]
	LCD_CTRL[1] = 0x42;							// DATA WRITE COMMAND OUTPUT

	for (i=0x4b00; i>0; --i)					// CLEAR COUNTER SET
	{
		LCD_CTRL[0] = 0x00;						//
	}

	LCD_CTRL[1] = 0x46;							//  [[ DISPALY V.REM ALL CLEAR ]]
	LCD_CTRL[0] = 0x80;							//
	LCD_CTRL[0] = 0x25;							//

	LCD_CTRL[1] = 0x4c;							// [[ SIFT COMMAND OUTPUT ]]
	LCD_CTRL[1] = 0x42;							// DATA WRITE COMMAND OUTPUT

	for (i=0x2580; i>0; --i)					// CLEAR COUNTER SET
	{
		LCD_CTRL[0] = 0x00;						//
	}
}

#else

const	U4b		TFT_COL_PLDATA[64]={			//V06  16->64
/*	   0,R,G,B		*/
	0x00000000,					/* 00：黒				R:000,G:000,B:000	*/
	0x000000FF,					/* 01：青				R:000,G:000,B:255	*/
	0x0000FF00,					/* 02：緑				R:000,G:255,B:000	*/
	0x0000FFFF,					/* 03：ｼｱﾝ（水色）		R:000,G:255,B:255	*/
	0x00FF0000,					/* 04：赤				R:255,G:000,B:000	*/
	0x00FF00FF,					/* 05：ﾏｾﾞﾝﾀﾞ（ﾋﾟﾝｸ）	R:255,G:000,B:255	*/
	0x00FFFF00,					/* 06：黄				R:255,G:255,B:000	*/
	0x00FFFFFF,					/* 07：白				R:255,G:255,B:255	*/
	0x00D8D8D8,					/* 08：灰色1			R:216,G:216,B:216	*/
	0x00C0C0C0,					/* 09：灰色2			R:192,G:192,B:192	*/
	0x00A0A0A0,					/* 0A：灰色3			R:160,G:160,B:160	*/
	0x00808080,					/* 0B：灰色4			R:128,G:128,B:128	*/
	0x00FF8000,					/* 0C：ｵﾚﾝｼﾞ			R:255,G:128,B:000	*/	//V05o
	0x0080FF00,					/* 0D：黄緑				R:128,G:255,B:000	*/	//V05o
	0x00000000,					/* 0E：予備									*/
	0x00000000,					/* 0F：予備									*/
	0x00000000,					/* 10：予備									*/
	0x00000000,					/* 11：予備									*/
	0x00000000,					/* 12：予備									*/
	0x00000000,					/* 13：予備									*/
	0x00000000,					/* 14：予備									*/
	0x00000000,					/* 15：予備									*/
	0x00000000,					/* 16：予備									*/
	0x00000000,					/* 17：予備									*/
	0x00000000,					/* 18：予備									*/
	0x00000000,					/* 19：予備									*/
	0x00000000,					/* 1A：予備									*/
	0x00000000,					/* 1B：予備									*/
	0x00000000,					/* 1C：予備									*/
	0x00000000,					/* 1D：予備									*/
	0x00000000,					/* 1E：予備									*/
	0x00000000,					/* 1F：予備									*/
	0x00000000,					/* 20：予備									*/
	0x00000000,					/* 21：予備									*/
	0x00000000,					/* 22：予備									*/
	0x00000000,					/* 23：予備									*/
	0x00000000,					/* 24：予備									*/
	0x00000000,					/* 25：予備									*/
	0x00000000,					/* 26：予備									*/
	0x00000000,					/* 27：予備									*/
	0x00000000,					/* 28：予備									*/
	0x00000000,					/* 29：予備									*/
	0x00000000,					/* 2A：予備									*/
	0x00000000,					/* 2B：予備									*/
	0x00000000,					/* 2C：予備									*/
	0x00000000,					/* 2D：予備									*/
	0x00000000,					/* 2E：予備									*/
	0x00000000,					/* 2F：予備									*/
	0x00008F00,					/* 30：EcoMeter0		R:000,G:255,B:000	*/
	0x00009F00,					/* 31：EcoMeter1		R:000,G:-16,B:000	*/
	0x0000AF00,					/* 32：EcoMeter2		R:000,G:-16,B:000	*/
	0x0000BF00,					/* 33：EcoMeter3		R:000,G:-16,B:000	*/
	0x0000CF00,					/* 34：EcoMeter4		R:000,G:-16,B:000	*/
	0x0000DF00,					/* 35：EcoMeter5		R:000,G:-16,B:000	*/
	0x0000EF00,					/* 36：EcoMeter6		R:000,G:-16,B:000	*/
	0x0000FF00,					/* 37：EcoMeter7		R:000,G:-16,B:000	*/
	0x00000000,					/* 38：予備									*/
	0x00000000,					/* 39：予備									*/
	0x00000000,					/* 3A：予備									*/
	0x00000000,					/* 3B：予備									*/
	0x00000000,					/* 3C：予備									*/
	0x00000000,					/* 3D：予備									*/
	0x00000000,					/* 3E：予備									*/
	0x00000000					/* 3F：予備									*/
};

void init_LCD(void)
{
	U2b		i;

	LDICKR = 0x0002;			//; インプットクロックレジスタ
								//; 入力ｸﾛｯｸ＝CKIO ／ 分周費＝1/2  よって、DOTCLK＝29.4912MHz
	LDMTR = 0xc02b;				//; モジュールタイプレジスタ
								//; ＴＦＴカラー１６ビットデータバスモジュール
	LDDFR = 0x000C;				//; データフォーマットレジスタ
								//; カラー256色8bpp（ﾊﾟﾚｯﾄ経由）
//	LDSMR = 初期値でＯＫ		//; スキャンモードレジスタ

	LDSARU = (U4b)&LCD_VRAM[0][0];	//; 上部表示パネル用データ取り込み開始アドレスレジスタ
//	LDSARL = 初期値でＯＫ		//; 下部表示パネル用データ取り込み開始アドレスレジスタ

	LDLAOR = 640;				//; 表示パネル用取り込みデータラインアドレスオフセットレジスタ
								//; 横幅640
	LDHCNR = 0x4F63;			//; 水平キャラクタナンバーレジスタ
								//; 表示ｷｬﾗｸﾀﾅﾝﾊﾞｰ ＝ 79 ＝ 横640／ｷｬﾀｸﾀ8ﾄﾞｯﾄ単位－1    総ｷｬﾗｸﾀﾅﾝﾊﾞｰ ＝ 99 ＝ 横800／ ｷｬﾀｸﾀ8ﾄﾞｯﾄ単位－1
	LDHSYNR = 0xB051;			//; 水平同期信号レジスタ
								//; 信号幅 ＝ 11 ＝ 96ﾄﾞｯﾄ/ｷｬﾀｸﾀ8ﾄﾞｯﾄ単位-1    信号出力位置 ＝ 81 ＝ (横640＋ﾌﾛﾝﾄﾎﾟｰﾁ16ﾄﾞｯﾄ)／ｷｬﾀｸﾀ8ﾄﾞｯﾄ単位－1
	LDVDLNR = 479;				//; 垂直表示ラインナンバーレジスタ
								//; 縦480－1
	LDVTLNR = 524;				//; 垂直総ラインナンバーレジスタ
								//; 縦525－1
	LDVSYNR = 0x11E8;			//; 垂直同期信号レジスタ
								//; 垂直同期信号幅 ＝ 1 ＝ 2ﾗｲﾝ－1   垂直同期信号出力位置 ＝ 488 ＝ 490ﾗｲﾝ目－2

	LDPMMR = 0xFF70;			//; パワーマネジメントモードレジスタ
								//; RGBﾃﾞｰﾀ、ﾀｲﾐﾝｸﾞﾃﾞｰﾀは、ﾎﾟｰﾄで出力ｲﾈｰﾌﾞﾙにしているから実際はVCPWCを出力したいだけ。
	LDPSPR = 0xFFFF;			//; 電源シーケンス期間レジスタ
								//; RGBﾃﾞｰﾀ、ﾀｲﾐﾝｸﾞﾃﾞｰﾀは、ﾎﾟｰﾄで出力ｲﾈｰﾌﾞﾙにしているから実際はVCPWCを出力したいだけ。

//カラーパレット設定
	LDPALCR = 0x0001;			//; ＣＰＵがパレットを使用。

	for (i=0; i<64; i++)		//V06  16->64
	{
		LDPR00[i] = TFT_COL_PLDATA[i];
	}

	LDPALCR = 0x0000;			//; ＬＣＤＣがパレットを使用。

}
#endif


#pragma	section	hwsetup1
/*
********************************************************************************
*
*  Function Name:	ＬＣＤイニシャル画面表示
*
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT4 )

extern	const	UNs	Han_MPtn_Table[256][16];		//半角文字パターン　テーブル

const	char	INIT_MOJI[] = "Initialize";
const	char	INIT_MOJI_dummy = 0x00;			//V05g

UNs	init_code_dot_cnv(UNs d_cara, UNb *Dst_p, UNs flg)
{
	UNs	*Src_p;
	UNs	*Dst_px;
	UNb	code1;
	UNs	*Srcw_p, d_cara_swap, dat;
	UNi	type, r_wk, size;

	Dst_px = (UNs *)Dst_p;

	code1 = d_cara & 0x00ff;

	/**************** 半角コードドット変換処理 ***************/
	Srcw_p = &Han_MPtn_Table[code1][0];	//半角文字ﾊﾟﾀｰﾝﾃｰﾌﾞﾙ ｱﾄﾞﾚｽ算出

	if(flg == 0xff ) {					//反転表示？
		size = 16;						/* ﾃﾞｰﾀCopy */
		while( size-- ) {
			*Dst_p++ = ~(*Srcw_p++);	//ﾋﾞｯﾄ反転
		}
	}
	else {								//正常表示
		size = 16;						/* ﾃﾞｰﾀCopy */
		while( size-- ) {
			*Dst_p++ = *Srcw_p++;
		}
	}
	r_wk = 0;							//半角ｺｰﾄﾞ
	return (r_wk);
}


void	disp_init_moji(
			UNs len,
			UNs x,
			UNs y,
			UNs c_col, 
			UNs b_col, 
			UNs size, 
			UNs *g_adr_p
			)
{
	UNi		i, j, k, l, flg;
	UNs		cnt, cnv_wk, *Dst_p;
	UNs		xdot, ydot, xdot_bak, ydot_bak;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNb		moji[E_line], dot_wk[32], wk1b;

	flg = 0;

	cnt = len;											//文字数　算出
	xsize = (size>>8) & 0x0ff;					// Xのｻｲｽﾞ
	ysize = size & 0x0ff;						// Yのｻｲｽﾞ

	/******** 背景色塗り潰し *********/
	x_dot_leng = xsize * cnt * 8;				// ｻｲｽﾞ × ﾊﾞｲﾄ長 × 8ﾄﾞｯﾄ/1byte
	y_dot_leng = ysize * 16;					// ｻｲｽﾞ × 16dot／1文字
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X方向＋１ﾄﾞｯﾄ
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y方向塗り潰し
		{
			LCD_VRAM[ydot][xdot] = b_col;
		}
	}

	/******** 文字表示 *********/
	xdot = x;
	ydot = y;

	for( i=0 ; i < cnt ; i += 2 ) {						//ﾜｰﾄﾞ→ﾊﾞｲﾄ単位ｱｸｾｽ可能領域にｺﾋﾟｰ
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//文字ｺｰﾄﾞの設定
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == init_code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
															//半角
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dotデータのﾋﾞｯﾄが立っている？
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
		else {												//全角
		}
	}
}


void init_DISP(void)
{
	UNl		col, cnt, *vram;

	col = 0x06060606;
	vram = (UNl *)&LCD_VRAM[0][0];
	cnt = (PanelWidth * PanelHeight) / 4;
	
	while (cnt--)
	{
		*vram++ = col;
	}

	disp_init_moji(
		10,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		224,					/* SW_buff[T_no].Y_POS, 	*/
		0,						/* SW_buff[T_no].C_COL,		*/
		8,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&INIT_MOJI
		);

	LDCNTR = 0x0011;					//SH7727-LCDC動作

	for(cnt=0x0ffffff; cnt>0; cnt--)
	{
		if( (LDPMMR & 0x0003) == 0x0003)
		{
			break;
		}
	}
	if (cnt != 0)
	{
		PEDR = 0;					// *LCD_ONイネーブル
	}
}


/*
********************************************************************************
*
*  Function Name:	「画面をﾊﾞｰｼﾞｮﾝUPしてください」の表示		V05i
*
********************************************************************************
*/
const	char	VUP_MESG_MOJI[] = "PLEASE V-UP[G]";
const	char	VUP_MESG__MOJIdummy = 0x00;

void vup_mesG_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESG_MOJI
		);
}


/*
********************************************************************************
*
*  Function Name:	「CPUBをﾊﾞｰｼﾞｮﾝUPしてください」の表示		V05i
*
********************************************************************************
*/
const	char	VUP_MESB_MOJI[] = "PLEASE V-UP[B]";
const	char	VUP_MESB__MOJIdummy = 0x00;

void vup_mesB_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESB_MOJI
		);
}


/*
********************************************************************************
*
*  Function Name:	「CPUAをﾊﾞｰｼﾞｮﾝUPしてください」の表示		V05i
*
********************************************************************************
*/
const	char	VUP_MESA_MOJI[] = "PLEASE V-UP[A]";
const	char	VUP_MESA__MOJIdummy = 0x00;

void vup_mesA_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESA_MOJI
		);
}


#endif



#pragma section

//;	***************************************************
//;	***												***
//;	***		画面ｷｬﾗ表示								***
//;	***												***
//;	***************************************************
/******************** V01b ********************
void Lcd_cr(U2b lcd_no, U2b xy_pos, U2b *poi1)
{
	U2b	i,i2,j,k,m,n,d;
	U2b	*poi2;

	i = (xy_pos & 0x000f);			// 行番号読込み
	j = ((xy_pos>>4) & 0x003f);			// 桁番号
	k = (xy_pos>>10) & 0x003f;			// 文字数

	i = i * 640 + j;				// 表示ｽﾀｰﾄ位置
	poi1 = poi1 + i * 1;				// 

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	for(n=16; n>0; --n)
	{
		poi2 = poi1;
		GLC_BUSY();
		LCD_CTRL[1] = 0x46;		// ｽﾀｰﾄ位置設定ｺﾏﾝﾄﾞ発行
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[0] = i;		// ｽﾀｰﾄｱﾄﾞﾚｽ(下位)発行
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[0] = i>>8;		// ｽﾀｰﾄｱﾄﾞﾚｽ(上位)発行
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[1] = 0x42;		// 表示ﾒﾓﾘへの書込みｺﾏﾝﾄﾞ発行

		GLC_BUSY();
		for (m=0; m<k; ++m)
		{
			if(lcd_no==0)
			{
				d = ~*poi2++;			// 表示ﾃﾞｰﾀ書込み
			}
			else{
				d = *poi2++;
			}
			LCD_CTRL[0] = d;		// 表示ﾃﾞｰﾀ書込み
		}
		poi1 += 40;
		i += 40;
	}
}
********************* V01b *******************/

void Lcd_cr(U2b lcd_no, U2b xy_pos, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	i,i2,j,k,m,n,d;
	U2b	*poi2;

	i = (xy_pos & 0x000f);			// 行番号読込み
	j = ((xy_pos>>4) & 0x003f);			// 桁番号
	k = (xy_pos>>10) & 0x003f;			// 文字数

	i = i * 640 + j;				// 表示ｽﾀｰﾄ位置
	poi1 = poi1 + i * 1;				// 

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	aLCD_NO = lcd_no;
	aLCD_MOZI_SUU = k;

	for(n=16; n>0; --n)
	{
		aLCD_BUFF = poi1;
		aLCD_WR_ADR = i;
		LCD_CR_ASM();
		poi1 += 40;
		i += 40;
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		画面1行表示								***
//;	***												***
//;	***************************************************
void Lcd_line(U2b lcd_no, U2b l_no, U2b cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	xy;
	xy = l_no | (0<<4) | (40<<10);
	Lcd_cr(lcd_no, xy, &(poi1[0]));
#else
	UNl		*Src_p, *Dis_p;
	UNl		i;
	if(lcd_no == 0)
	{
		Src_p = (UNl *)&LCD_VBASE[l_no*16*2][0];
		Dis_p = (UNl *)&LCD_VRAM[l_no*16*2][0];
		i = (PanelWidth * (1*16*2)) / 4;
		while(i--)
		{
			*Dis_p++ = *Src_p++;
		}
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		画面全表示								***
//;	***												***
//;	***************************************************
void Lcd_all(U2b lcd_no, U2b cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	l_no;
	cnt = 0;

	for (l_no=0; l_no<15; ++l_no)
	{
		WDT_Rifresh();
		Lcd_line(lcd_no, l_no, cnt, &(poi1[0]));
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		画面ﾄﾞｯﾄ表示							***
//;	***												***
//;	***************************************************
/******************** V01b ********************
void Lcd_draw(U2b lcd_no, U2b X_clm, U2b Y_dot, U2b C_cnt, U2b *poi1)
{
	U2b	no,x,y,c;
	U2b	*poi2;

	no = lcd_no;
	x = X_clm;									// ｶﾗﾑ先頭		0～39
	y = Y_dot;									// ﾄﾞｯﾄ位置		0～239(16×15)
	c = C_cnt;									// 表示ｶﾗﾑ数	1～40
	poi2 = poi1;

	y = y * 40 + x;								// 表示ｽﾀｰﾄ位置

	if (no!=0) {
		y += 15*16*40;
	}

	GLC_BUSY();
	LCD_CTRL[1] = 0x46;		// ｽﾀｰﾄ位置設定ｺﾏﾝﾄﾞ発行
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[0] = y;		// ｽﾀｰﾄｱﾄﾞﾚｽ(下位)発行
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[0] = y>>8;		// ｽﾀｰﾄｱﾄﾞﾚｽ(上位)発行
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[1] = 0x42;		// 表示ﾒﾓﾘへの書込みｺﾏﾝﾄﾞ発行
	while(LCD_CTRL[0] & 0x40){}//(2002-12-23画面ﾁﾗﾂｷ対策1)
	GLC_BUSY();

	for ( ; c>0; --c)
	{
		if(no==0)
		{
			LCD_CTRL[0] = ~*poi2++;			// 表示
		}
		else{
			LCD_CTRL[0] = *poi2++;			// 表示
		}
		while(LCD_CTRL[0] & 0x40){}//(2002-12-23画面ﾁﾗﾂｷ対策1)
	}
}
********************* V01b *******************/

void Lcd_draw(U2b lcd_no, U2b X_clm, U2b Y_dot, U2b C_cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	k,i;

	k = C_cnt;									// 表示ｶﾗﾑ数	1～40
	i = Y_dot * 40 + X_clm;								// 表示ｽﾀｰﾄ位置

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	aLCD_NO = lcd_no;
	aLCD_MOZI_SUU = k;
	aLCD_BUFF = poi1;
	aLCD_WR_ADR = i;
	LCD_CR_ASM();
#endif
}

//;	***************************************************
//;	***												***
//;	***		画面ON									***
//;	***												***
//;	***************************************************
void Lcd_on(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	LCD_CTRL[1] = 0x59;
	LCD_CTRL[0] = 0x54;
	GAMEN_ON_FLG = 0;
#endif
}

//;	***************************************************
//;	***												***
//;	***		画面OFF									***
//;	***												***
//;	***************************************************
void Lcd_off(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	if(GAMEN_ON_FLG != 0x0ff)
	{
		LCD_CTRL[1] = 0x58;
		LCD_CTRL[0] = 0x54;
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		LCD輝度設定								***
//;	***												***
//;	***************************************************
	extern	U2b	IOGA1_CTRL_DAT1[8];
#define		IOGA_P4		4*2
void Lcd_contrast_chage(U2b con)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	PADR = (PADR & 0xff0f) | ((con<<4) & 0x00f0);
#else
	*(IOGA1_CTRL_DAT1+IOGA_P4) = (con & 0x000f);
#endif
}

//;	***************************************************
//;	***  漢字ＲＯＭよりデータセット					***
//;	***  Input	: JISコード							***
//;	***  Return	: 漢字ＲＯＭアドレス				***
//;	***************************************************
#define		E_gai_code		0xEB9F					//外字コード
#define		GAMEN_ADR_TOP	0x400000				//1画面文字ｺｰﾄﾞのﾄｯﾌﾟ ｱﾄﾞﾚｽ
#define		E_GAMEN_LIM		0x280					//1画面文字ｺｰﾄﾞの領域長
#define		E_line			40						//1行の表示文字数
#define		E_line_byte		16*40					//1行の表示用ﾊﾞｯﾌｧ数

#define		E_AS_SP			0x20					//スペース［ASCIIｺｰﾄﾞ］
#define		E_AS_TEN		0x2e					//”.”　 ［ASCIIｺｰﾄﾞ］

#define		E_SJ_SP			0x8140					//スペース［S-JISｺｰﾄﾞ］
#define		E_SJ_TEN		0x8144					//”.”　 ［S-JISｺｰﾄﾞ］
#define		E_SJ_Base		0x821f					//ASCII+0x821f=０～９［S-JISｺｰﾄﾞ］

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define		DEF_KAN_ROM_TOP		0x00860000
#else
#define		DEF_KAN_ROM_TOP		0xA0058000
#endif


U1b *kan_rom_set(U2b d_cara)
{
	U2b	k;
	U4b	i,j;
	U1b	*ch;

	i = d_cara >> 8;
	if(i < 0x30) {									// 非漢字コード

		/************ 非漢字コード *****************/
		i = d_cara;									// 漢字バンクポート確定
		j = d_cara >> 8;

		j &= 0x07;									//AND	BH,07H
		i &= 0x60;									//AND	DL,60H
		i >>= 2;									//SHR 	DL,2
		j |= i;										//OR 	BH,DL
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;									//SHL	BH,2
		k = (kan_bank_dat & 0x0003);				//MOV	AL,DAT_LCD_KAN_BAK		;//AND	AL,00000011B			;
		k |= j;										//OR	BH,AL				;
		kan_bank_outp = k;							/* データ出力 */
#else
		j <<= 12;
		kan_bank_outp = j;							/* データ出力 */
		kan_bank_outp &= 0x03f000;					/* データ出力 */
#endif
		d_cara &= 0x001f;							//AND	BL,00011111B			;
		d_cara <<= 5;								//SHL	BX,5				;
	}

	else if(i< 0x50) {								//第１水準漢字コード

		/************ 漢字コード *******************/
		i = d_cara;									/* 漢字バンクポート確定 */
		j = d_cara >> 8;

		j &= 0x4f;
		i = j & 0xf0;
		i >>= 2;
		i &= 0x10;
		j &= 0x0f;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;
		k = (kan_bank_dat & 0x0003);
		k |= j;
		kan_bank_outp = k;							/* データ出力 */
#else
		j <<= 12;
		kan_bank_outp = j;							/* データ出力 */
		kan_bank_outp &= 0x03f000;					/* データ出力 */
#endif
		d_cara &= 0x007f;
		d_cara <<= 5;
	}

	else if(i < 0x70) {								//第２水準コード(0x50,0x60)

	/************ ５０Ｈ，６０Ｈ　漢字コード *******************/
		i = d_cara;									/* 漢字バンクポート確定 */
		j = d_cara >> 8;

		j &= 0x2f;
		i = j & 0xf0;
		i >>= 1;
		i &= 0x10;
		j &= 0x0f;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;
		k = (kan_bank_dat & 0x0007);
		k |= j;
		k |= 0x80;									/* CA12=1 第二水準だから */
		kan_bank_outp = k;							/* データ出力 */
#else
		j <<= 12;
		kan_bank_outp = j;							/* データ出力 */
		kan_bank_outp |= 0x020000;					/* データ出力 */	//V05r(INS)
		kan_bank_outp &= 0x03f000;					/* データ出力 */
#endif
		d_cara &= 0x007f;
		d_cara <<= 5;
	}

	else{											//第２水準コード(0x70)

	/************ ７０Ｈ漢字コード *****************/
		i = d_cara;									/* 漢字バンクポート確定 */
		j = d_cara >> 8;

		j &= 0x07;
		i &= 0x60;
		i >>= 2;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 1;
		k = (kan_bank_dat & 0x0007);
		k |= j;
		k |= 0x80;								/* CA12=1 第二水準だから */
		kan_bank_outp = k;						/* データ出力 */
#else
		j <<= 12;
		kan_bank_outp = j;							/* データ出力 */
		kan_bank_outp |= 0x020000;					/* データ出力 */	//V05r(INS)
		kan_bank_outp &= 0x03f000;					/* データ出力 */
#endif
		d_cara &= 0x001f;
		d_cara <<= 5;
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	ch=(U1b *)d_cara;
#else
	kan_bank_outp |= d_cara;
	ch=(U1b *)kan_bank_outp;
#endif

//	ch += DEF_KAN_ROM_TOP;
	ch += (U4b)&kan_rom_top;
	return(ch);
}


/*
********************************************************************************
*  Function Name:	指定型データ読出し／書込み
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shima		ON:2014/04/17
********************************************************************************
*/
void	KATAn_RW(viod)
{
}


/*** END ***/
