/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			表　示　関　数															*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-21
*
*************************************************************************************/


/* データ型定義 ------------------------------------------------------ */
typedef	unsigned int	UNi;
typedef	unsigned char	UNb;
typedef	unsigned short	UNs;
typedef	unsigned long	UNl;

/* 外部参照関数定義 -------------------------------------------------- */
extern	void Lcd_all(UNs, UNs, UNs *);					//全表示
extern	void Lcd_line(UNs, UNs, UNs, UNs *);			//行表示
extern	void Lcd_cr(UNs, UNs, UNs *);					//ｷｬﾗ単位表示
extern	void Lcd_draw(UNs, UNs, UNs, UNs, UNs *);		//ﾄﾞｯﾄ表示
extern	void Lcd_on(void);								//画面ON
extern	void Lcd_off(void);								//画面OFF
extern	UNb *	kan_rom_set(UNs);						//漢字ＲＯＭよりデータセット

/* 外部参照変数定義 -------------------------------------------------- */
/* 定数定義 ---------------------------------------------------------- */
/***	表示用の定義	***/
#define	E_gmen_bf		15*16*40				//1画面の表示用ﾊﾞｯﾌｧ数
#define	E_gmen_size		15*16*40*2				//1画面の表示用ﾊﾞｯﾌｧ･ｻｲｽﾞ
#define	E_line			40						//1行の表示文字数
#define	E_line_bf		16*40					//1行の表示用ﾊﾞｯﾌｧ数
#define	E_line_size		16*40*2					//1行の表示用ﾊﾞｯﾌｧ･ｻｲｽﾞ
#define	E_next_dot		40*2					//1文字の次dot位置数

/* プロトタイプ宣言 -------------------------------------------------- */
/* 内部変数定義 ------------------------------------------------------ */
UNs		LCD_WORK1[15][16][40];		/* 表示ﾜｰｸ領域LCD1[何行何ﾄﾞｯﾄ目何文字目] */

/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		disp_test
*  Function Name:	表示テスト
*  Input	:		なし
*  Return	:		なし
*  Note		:
********************************************************************************
*/
void	disp_test(void)
{
	UNb	*src_p;
	UNs	*dst_p, wk1;
	UNi	i, j, k, type;


/*		LCD_WORK1に1画面分のデータを設定する		*/
//0行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2422);			//"あ"(0x2422)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[0][0][j];			//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//1行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x242b);			//"か"(0x242b)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[1][0][j];			//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//2行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2435);			//"さ"(0x2435)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[2][0][j];			//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//3行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x254f);			//"ハ"(0x254f)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[3][0][j];			//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//4行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x255e);			//"マ"(0x255e)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[4][0][j];			//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//5行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2564);				//"ヤ"(0x2564)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[5][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//6行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2330);				//"０"(0x2330)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[6][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//7行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2331);				//"１"(0x2331)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[7][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//8行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2332);				//"２"(0x2332)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[8][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//9行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2358);				//"Ｘ"(0x2358)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[9][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//10行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2359);				//"Ｙ"(0x2359)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[10][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//11行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x235a);				//"Ｚ"(0x235a)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[11][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//12行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3021);				//"亜"(0x3021)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[12][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//13行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3066);				//"井"(0x3066)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[13][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//14行目
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3127);				//"宇"(0x3127)　JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[14][0][j];				//1行を埋める。
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}


/*		データを表示する		*/

	type = 0;

	if( type == 0 ) {		//全表示?
		Lcd_off();											//画面OFF

		Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);		//全表示

		Lcd_on();											//画面ON
	}
	else{
		Lcd_cr(00, 0xa000, &LCD_WORK1[0][0][0]);					//LCD1に0行目を表示する。
		Lcd_cr(01, 0xa002, &LCD_WORK1[0][0][0]);					//LCD2に2行目を表示する。

		Lcd_line(0x00, 4, E_line_bf, &LCD_WORK1[0][0][0]);			//LCD1に4行目を表示する。
		Lcd_line(0x01, 6, E_line_bf, &LCD_WORK1[0][0][0]);			//LCD2に6行目を表示する。

		Lcd_draw(0x00, 0, 8*16, 40, &LCD_WORK1[8][0][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+1, 40, &LCD_WORK1[8][1][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+2, 40, &LCD_WORK1[8][2][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+3, 40, &LCD_WORK1[8][3][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+4, 40, &LCD_WORK1[8][4][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+5, 40, &LCD_WORK1[8][5][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+6, 40, &LCD_WORK1[8][6][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+7, 40, &LCD_WORK1[8][7][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+8, 40, &LCD_WORK1[8][8][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+9, 40, &LCD_WORK1[8][9][0]);			//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+10, 40, &LCD_WORK1[8][10][0]);		//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+11, 40, &LCD_WORK1[8][11][0]);		//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+12, 40, &LCD_WORK1[8][12][0]);		//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+13, 40, &LCD_WORK1[8][13][0]);		//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+14, 40, &LCD_WORK1[8][14][0]);		//LCD1に8行目を表示する。
		Lcd_draw(0x00, 0, 8*16+15, 40, &LCD_WORK1[8][15][0]);		//LCD1に8行目を表示する。

		Lcd_draw(0x01, 0, 10*16, 40, &LCD_WORK1[10][0][0]);			//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+1, 40, &LCD_WORK1[10][1][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+2, 40, &LCD_WORK1[10][2][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+3, 40, &LCD_WORK1[10][3][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+4, 40, &LCD_WORK1[10][4][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+5, 40, &LCD_WORK1[10][5][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+6, 40, &LCD_WORK1[10][6][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+7, 40, &LCD_WORK1[10][7][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+8, 40, &LCD_WORK1[10][8][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+9, 40, &LCD_WORK1[10][9][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+10, 40, &LCD_WORK1[10][10][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+11, 40, &LCD_WORK1[10][11][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+12, 40, &LCD_WORK1[10][12][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+13, 40, &LCD_WORK1[10][13][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+14, 40, &LCD_WORK1[10][14][0]);		//LCD2に10行目を表示する。
		Lcd_draw(0x01, 0, 10*16+15, 40, &LCD_WORK1[10][15][0]);		//LCD2に10行目を表示する。
	}

}



/*** END ***/
