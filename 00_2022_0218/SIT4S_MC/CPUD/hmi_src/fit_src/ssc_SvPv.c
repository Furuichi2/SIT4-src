/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙ関係								*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-22
*
*************************************************************************************/

#include "string.h"								//標準ライブラリ

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */

/* 外部参照変数定義 -------------------------------------------------- */
extern	U1b		LCD_VRAM[PanelHeight][PanelWidth];
extern	U1b		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		SH2_MAIN_CLK;
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	SVdata_disp(void);						//設定値情報　表示
void	SVdata_disp_ent(UNs);					//設定途中の物は、元に戻す処理
void	SV_csr_set(void);						//設定値カーソル
void	SV_csr_reset(UNs);						//設定値カーソル

void	PVdata_disp_all(void);					//全　実測値情報　表示
UNs		PVdata_disp(UNs, UNs );					//実測値情報　表示

void	SVPV_data_disp(UNl, void *, UNs, UNs);	//設定値＆実測値 表示
void	SVPV_data_NOdisp(void *);				//
void	Count_hosei_csr_on(UNs);				//カウンタ補正の実測値反転処理
void	SVSW_tbl_enzan(void);					//ＳＶＳＷテーブルアドレス演算
void	kyoutyou_set(UNs);						//強調文字変換
void	Nextkno_Name_draw(UNs);					//
void	chk_kajyu_offset1(UNs, UNs);			//2015/05/19

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		SVdata_disp
*  Function Name:	設定値情報　表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		設定値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-22
********************************************************************************
*/
void	SVdata_disp(void)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;
	long	cnv_bf_s;

	if(SV_CNT == 00) {									//設定値有り？
		return;											//なし
	}
	i = SV_CNT;

	for( j = 0 ; i > 0 ; i--,j++ ) {
		if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {		//設定値データ未使用？

			cnv_bf = 0;									//領域クリア

			cnt = (SV_buff[j].BYTE_NO & 0x000f);		//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
			if(cnt == 4){								//long(4byte) ?
				dst_lp = (UNl *)SV_buff[j].DATA_ADR;	//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				cnv_bf = *dst_lp;
				cnv_bf_s = (long)*dst_lp;				//2014/03/13
			}
			else{										//short(2byte)
				dst_p = SV_buff[j].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				cnv_bf = *dst_p;
				cnv_bf_s = (short)*dst_p;				//2014/03/13
			}

			flag = 0x02;								//BCD
			if( (SV_buff[j].TOK_FLG & BIT_0) == 0 ) {	//特殊ﾌﾗｸﾞb0 = BCDﾃﾞｰﾀ　？
				flag = 0x01;							//HEX
			}

			if( SV_buff[j].TOK_FLG & BIT_7 ) {			//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
				k = 0xff;
			}
			else{										//あり
				k = 0x00;
			}

			if ( SV_buff[j].TOK_FLG & BIT_5 ) {			//絶対値表示？		2014/03/13
				if ( cnv_bf_s < 0 ) {
					cnv_bf_s *= -1;
					cnv_bf = (UNs)cnv_bf_s;
				}
			}

			if ( SV_buff[j].TOK_FLG & BIT_6 ) {			//ASCII表示？		2014/03/13
				flag = 0x04;							//ASCII
				k = 0xff;								//ｾﾞﾛｻﾌﾟﾚｽ無し
			}

			SVPV_data_disp(cnv_bf, &SV_buff[j], k, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
		}
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp_one
*  Function Name:	設定値情報　表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		設定値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:A.Shimamura		ON:2014/09/05
********************************************************************************
*/
void	SVdata_disp_one(UNs t_no)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;
	long	cnv_bf_s;

	if(SV_CNT == 00) {									//設定値有り？
		return;											//なし
	}

	if( (SV_buff[t_no].SUB_NO & BIT_F) == 0 ) {		//設定値データ未使用？

		cnv_bf = 0;									//領域クリア

		cnt = (SV_buff[t_no].BYTE_NO & 0x000f);		//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		if(cnt == 4){								//long(4byte) ?
			dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;	//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_lp;
			cnv_bf_s = (long)*dst_lp;				//2014/03/13
		}
		else{										//short(2byte)
			dst_p = SV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_p;
			cnv_bf_s = (short)*dst_p;				//2014/03/13
		}

		flag = 0x02;								//BCD
		if( (SV_buff[t_no].TOK_FLG & BIT_0) == 0 ) {	//特殊ﾌﾗｸﾞb0 = BCDﾃﾞｰﾀ　？
			flag = 0x01;							//HEX
		}

		if( SV_buff[t_no].TOK_FLG & BIT_7 ) {			//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
			k = 0xff;
		}
		else{										//あり
			k = 0x00;
		}

		if ( SV_buff[t_no].TOK_FLG & BIT_5 ) {			//絶対値表示？		2014/03/13
			if ( cnv_bf_s < 0 ) {
				cnv_bf_s *= -1;
				cnv_bf = (UNs)cnv_bf_s;
			}
		}

		if ( SV_buff[t_no].TOK_FLG & BIT_6 ) {			//ASCII表示？		2014/03/13
			flag = 0x04;							//ASCII
			k = 0xff;								//ｾﾞﾛｻﾌﾟﾚｽ無し
		}

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], k, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp1
*  Function Name:	設定値情報　表示 (設定値未使用の場合はﾍﾞｰｽ色で塗潰し)
*  Input	:		なし
*  Return	: 		なし
*  Note		:		設定値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	SVdata_disp1(void)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;

	if(SV_CNT == 00) {									//設定値有り？
		return;											//なし
	}
	i = SV_CNT;

	for( j = 0 ; i > 0 ; i--,j++ ) {
		if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {		//設定値データ未使用？

			cnv_bf = 0;									//領域クリア

			cnt = (SV_buff[j].BYTE_NO & 0x000f);		//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
			if(cnt == 4){								//long(4byte) ?
				dst_lp = (UNl *)SV_buff[j].DATA_ADR;	//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				cnv_bf = *dst_lp;
			}
			else{										//short(2byte)
				dst_p = SV_buff[j].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				cnv_bf = *dst_p;
			}

			flag = 0x02;								//BCD
			if( (SV_buff[j].TOK_FLG & BIT_0) == 0 ) {	//特殊ﾌﾗｸﾞb0 = BCDﾃﾞｰﾀ　？
				flag = 0x01;							//HEX
			}

			if( SV_buff[j].TOK_FLG & BIT_7 ) {			//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
				k = 0xff;
			}
			else{										//あり
				k = 0x00;
			}
			SVPV_data_disp(cnv_bf, &SV_buff[j], k, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
		}
		else {
			disp_moji_s_paint(
				SV_buff[j].M_LEN,		//半角桁数
				SV_buff[j].X_POS,		//X始点
				SV_buff[j].Y_POS,		//Y始点
				GAMENn_HEAD.scr_col,	//塗潰し色
				SV_buff[j].SIZE,		//X/Y
				LCD_VRAM
				);
		}
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp_ent
*  Function Name:	設定途中の物は、元に戻す処理
*  Input	:		ﾃｰﾌﾞﾙ番号
*
*  Return	: 		なし
*  Note		:		設定値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
void	SVdata_disp_ent(UNs T_no)
{
	UNs		*dst_p, cnt, i, flag;
	UNl		*dst_lp, cnv_bf;

	if(SV_DATA_CHG != 00){									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
		SV_DATA_CHG = 0;									//重複して処理をしないように

		cnv_bf = 0;											//領域クリア

		cnt = (SV_buff[T_no].BYTE_NO & 0x000f);				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		if(cnt == 4){										//long(4byte) ?
			dst_lp = (UNl *)SV_buff[T_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_lp;
		}
		else{												//short(2byte)
			dst_p = SV_buff[T_no].DATA_ADR;					//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_p;
		}

		flag = 0x02;									//BCD
		if( (SV_buff[T_no].TOK_FLG & BIT_0) == 0 ) {	//特殊ﾌﾗｸﾞb0 = BCDﾃﾞｰﾀ　？
			flag = 0x01;								//HEX
		}

		if( SV_buff[T_no].TOK_FLG & BIT_7 ) {			//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
			i = 0xff;
		}
		else{											//あり
			i = 0x00;
		}
		SVPV_data_disp(cnv_bf, &SV_buff[T_no], i, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
	}

	SV_csr_reset(T_no);								//設定値カーソル

}


/*
********************************************************************************
*  Module Name:		SV_csr_set
*  Function Name:	設定値カーソル表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	SV_csr_set(void)
{
	UNs		xy_no, t_no, cnt;
	UNs		*Dst_p;

	if( SV_CNT != 00 &&										//設定値あり
			SV_TBL_POS_NOW != 0xff ) {						//異常コードでない

		t_no = SV_TBL_POS_NOW;
		xy_no = SV_buff[t_no].XY_POS;						//ｶｰｿﾙのX,Y軸

		Dst_p = &LCD_WORK2[xy_no & 0x000f][15][(xy_no >> 4)&0x3f];	//カーソルデータよりアドレス演算
		cnt = xy_no >> 10;									//文字数
		while(cnt --) {
			*Dst_p++ = 0x00ff;
		}
		Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);				//ｷｬﾗ単位表示
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	SV_csr_set(void)
{
	UNs		t_no, xdot, ydot, size, leng, leng1;
	UNb		*Dst_p;

	if( SV_CNT != 00 &&										//設定値あり
			SV_TBL_POS_NOW != 0xff ) {						//異常コードでない

		t_no = SV_TBL_POS_NOW;

		xdot = SV_buff[t_no].X_POS;
		ydot = SV_buff[t_no].Y_POS;
		size = SV_buff[t_no].SIZE;							// 上位Xサイズ、下位Yサイズ
		leng = SV_buff[t_no].M_LEN;

		ydot = ydot + ( (size & 0x0ff) * 16 ) - 1;			// アンダーカーソル表示Ｙ位置算出
		leng = leng * 8 * (size >> 8);						// カーソル長さ算出
		leng1 = leng;
		Dst_p = &LCD_VBASE[ydot][xdot];						// 表示ＶＲＡＭセット
		while(leng --) {
			*Dst_p++ = SV_UNDER_COLOR;
		}
		Dst_p = &LCD_VRAM[ydot][xdot];						// 表示ＶＲＡＭセット
		while(leng1 --) {
			*Dst_p++ = SV_UNDER_COLOR;
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SV_csr_reset
*  Function Name:	設定値カーソル消去
*  Input	:		ﾃｰﾌﾞﾙ番号
*
*  Return	: 		なし
*  Note		:		設定値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	SV_csr_reset(UNs T_no)
{
	UNs		i, j, k;


	if(SV_CNT == 00 ||									//設定値有り？
		T_no == 0xff ) {
		return;											//なし
	}

	k = j = i = SV_buff[T_no].XY_POS;					//設定値表示のX,Y軸
	i &= 0x000f;										//行のｱﾄﾞﾚｽ　算出
	j = ( j >> 4) & 0x003f;								//桁のｱﾄﾞﾚｽ　算出
	k >>= 10;											//文字数　算出

	for( ; k > 0 ; k--, j++) {
		LCD_WORK2[i][15][j] &= 0x0000;					//ｸﾘｱ
	}

	Lcd_cr(01, SV_buff[T_no].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	SV_csr_reset(UNs T_no)
{
	UNs		xdot, ydot, size, leng, leng1;
	UNb		*Dst_p;

	if(SV_CNT == 00 ||									//設定値有り？
		T_no == 0xff ) {
		return;											//なし
	}

	xdot = SV_buff[T_no].X_POS;
	ydot = SV_buff[T_no].Y_POS;
	size = SV_buff[T_no].SIZE;							// 上位Xサイズ、下位Yサイズ
	leng = SV_buff[T_no].M_LEN;

	ydot = ydot + ( (size & 0x0ff) * 16 ) - 1;			// アンダーカーソル表示Ｙ位置算出
	leng = leng * 8 * (size >> 8);						// カーソル長さ算出
	leng1 = leng;
	Dst_p = &LCD_VBASE[ydot][xdot];						// 表示ＶＲＡＭセット
	while(leng --) {
		*Dst_p++ = SV_buff[T_no].B_COL1;
	}
	Dst_p = &LCD_VRAM[ydot][xdot];						// 表示ＶＲＡＭセット
	while(leng1 --) {
		*Dst_p++ = SV_buff[T_no].B_COL1;
	}
}
#endif


/*
********************************************************************************
*  Module Name:		PVdata_disp_all
*  Function Name:	全　実測値情報　表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		全実測値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	PVdata_disp_all(void)
{
	UNi		i, j;

	if ( (SEQ_PAR_341 & BIT_3) && (GAMEN_NO == 1) && (WINDOW_NO == 0) ) {		//2013/07/22
		//下限PV表示の高速化対応
		for( j=1, i=PV_CNT ; i > 0 ; i-- ) {
			j = PVdata_disp( j, 0x00ff );					//実測値情報　表示

			if ( (i&0x03) == 0 ) {
				//◆◆◆下限位置表示ﾘﾌﾚｯｼｭ◆◆◆
				SH2_MAIN_CLK ^= cBIT0;						//測定用
				PV_CHANGE_hanten();							//下限位置GET
				PVdata_disp( 7, 0x00ff );					//下限位置表示
			}
		}
	}
	else {
		for( j=1, i=PV_CNT ; i > 0 ; i-- ) {
			j = PVdata_disp( j, 0x00ff );					//実測値情報　表示
		}
	}

	PV_DISP_CNT = 1;									//表示実測値カウンタ 初期化

}


/*
********************************************************************************
*  Module Name:		PVdata_disp
*  Function Name:	実測値情報　表示
*  Input	:		表示ﾃｰﾌﾞﾙ番号
*					表示種別(0：通常／0xff：全表示)
*
*  Return	: 		次表示ﾃｰﾌﾞﾙ番号
*  Note		:		実測値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
UNs		PVdata_disp(UNs disp_no, UNs flag)
{
	UNs		*dst_p, cnt;
	UNl		*dst_lp, cnv_bf;
	UNi		t_no, j;
	UNs		xy_wk;
	UNs		c_wk[16];

	if(PV_CNT == 00) {									//実測値有り？

		chk_kajyu_offset1(disp_no, 0x30);				//ｵﾌｾｯﾄ校正完了が消えた用網掛けﾌﾟﾛｸﾞﾗﾑ

		return;											//なし
	}

	if( disp_no > PV_CNT ) {
		disp_no = 1;									//表示 番号初期化
	}
	t_no = (disp_no - 1);									//表示実測値テーブル番号

	if ( (SVPV_LCD_FLG == 0) && (PV_buff[t_no].GRP_NO == 54) ) {	//単位データ？		For SIT4

		chk_kajyu_offset1(disp_no, 0x31);				//ｵﾌｾｯﾄ校正完了が消えた用網掛けﾌﾟﾛｸﾞﾗﾑ

		disp_no ++;										//次回 表示実測値カウンタ
		return(disp_no);
	}
	if ( (SVPV_LCD_FLG == 0) && (PV_buff[t_no].GRP_NO == 56) ) {	//型データ？		For SIT4

		chk_kajyu_offset1(disp_no, 0x32);				//ｵﾌｾｯﾄ校正完了が消えた用網掛けﾌﾟﾛｸﾞﾗﾑ

		disp_no ++;										//次回 表示実測値カウンタ
		return(disp_no);
	}

	if( (PV_buff[t_no].SUB_NO & BIT_F) ||					//実測値データ未使用？
		(flag == 0 && PV_buff[t_no].TOK_FLG & BIT_6) ) {	//特殊ﾌﾗｸﾞb6 = 単位％型データ？

		chk_kajyu_offset1(disp_no, 0x33);				//ｵﾌｾｯﾄ校正完了が消えた用網掛けﾌﾟﾛｸﾞﾗﾑ

		disp_no ++;										//次回 表示実測値カウンタ
		return(disp_no);

//		if(PV_CNT == 1 || PVDATA_NON != 00){
//			return;
//		}
//		if( disp_no > PV_CNT ) {
//			disp_no = 1;								//表示 番号初期化
//		}
//		t_no = (disp_no - 1);								//表示実測値テーブル番号
	}

	cnv_bf = 0;											//領域クリア

	cnt = (PV_buff[t_no].BYTE_NO & 0x000f);				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
	if(cnt == 4){										//long(4byte) ?
		dst_lp = (UNl *)PV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		cnv_bf = *dst_lp;								//データ読込
	}
	else{												//short(2byte)
		dst_p = PV_buff[t_no].DATA_ADR;					//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		cnv_bf = *dst_p;								//データ読込
	}

	switch(PV_buff[t_no].SUB_NO & /*0x000f V01j*/0x001f) {				//ｻﾌﾞﾙｰﾁﾝ番号 取得
		default:
		case 0x00:				//そのまま表示
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			break;

		case 0x01:				//シーケンスデータ	(?)
			cnv_bf = 0;										//領域 00 クリア
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x02);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 0x02:				//ＢＣＤデータ
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x02);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			break;

		case 0x03:				//セロサプレスなし
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 0x04:				//荷重表示
			if( SEQ_PAR_385 & BIT_7) {								//荷重測定中(表示なし)1:荷重表示
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//設定値＆実測値 表示
			}
			else {										//Yes
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x50);	//設定値＆実測値 表示
			}
			break;

		case 0x05:				//4ﾊﾞｲﾄ表示
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 0x06:				//ASCII表示
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 0x07:				//強調
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//設定値＆実測値 表示
			break;

		case 0x08:				//ストッピングタイム
//			if( SEQ_PAR_084 & BIT_1) {					//ストッピングタイム バルブＯＮ中？
//				cnv_bf = 0xffff;						//ｽﾍﾟｰｽ　領域クリア
//				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x10);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
//			}
//			else {										//No
//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX → BCD 変換
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
//			}
			break;

		case 0x09:				//セロサプレスなし強調
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x41);	//設定値＆実測値 表示
			break;

		case 0x0a:				//生産SPM設定中
			if( SW14_ON1_FLG == 0x01) {					//今生産設定が押し？
			}
			else {
//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX → BCD 変換
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			}
			break;

		case 11:				//データ符号あり(－時は、反転表示)
			if( cnv_bf & 0x80000000 ){								//マイナス？
				cnv_bf *= -1;										//表示データを算出

				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x81);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/反転表示)
			}
			else{
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			}
			break;

		case 12:				//HEX表示
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x101);	//HEX表示(ｾﾞﾛｻﾌﾟﾚｽなし)	shima
			break;

		/* V01 (INS) */
		case 13:				//サイクル表示
			if (CMD_1CYCLE_DSP1) {
				/* そのまま表示 */
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			}
			else {
				/* 表示消去 */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(151);
				xy_wk = (6 << 10);			//ﾊﾞｲﾄ数
				xy_wk |= (10 << 4);			//桁
				xy_wk |= 6;					//行
				Lcd_cr(00, xy_wk, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
#else
				disp_moji_s_paint(
					PV_buff[t_no].M_LEN,
					PV_buff[t_no].X_POS,
					PV_buff[t_no].Y_POS,
					GAMENn_HEAD.scr_col,
					PV_buff[t_no].SIZE,
					LCD_VRAM
					);
#endif
			}
			break;

		/* V01 (INS) */
		case 14:				//生産下限／下限上高さ　表示
			if (SEQ_PAR_200 & BIT_5) {						//段取寸動？
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				xy_wk = (8 << 10);			//ﾊﾞｲﾄ数
				xy_wk |= (11 << 4);			//桁
				xy_wk |= 7;					//行
				Lcd_cr(0, xy_wk, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
				xy_wk = (8 << 10);			//ﾊﾞｲﾄ数
				xy_wk |= (3 << 4);			//桁
				xy_wk |= 7;					//行
				Lcd_cr(0, xy_wk, &LCD_WORK3[0][0][0]);		//ｷｬﾗ単位表示
#else
				disp_moji_s_rif (				/* 「下限上高」の文字を表示 */
					8, 
					160, 
					224, 
					0x0101
					);
				disp_moji_s_paint(				/* 「生産下限」の文字を消す */
					8, 
					96, 
					224, 
					GAMENn_HEAD.scr_col,
					0x0101,
					LCD_VRAM
					);
#endif
				/* 「下限上高」そのまま表示 */
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			}

			else {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				xy_wk = (8 << 10);			//ﾊﾞｲﾄ数
				xy_wk |= (3 << 4);			//桁
				xy_wk |= 7;					//行
				Lcd_cr(0, xy_wk, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
				xy_wk = (8 << 10);			//ﾊﾞｲﾄ数
				xy_wk |= (11 << 4);			//桁
				xy_wk |= 7;					//行
				Lcd_cr(0, xy_wk, &LCD_WORK3[0][0][0]);		//ｷｬﾗ単位表示
#else
				disp_moji_s_paint (				/* 「下限上高」の文字を消す */
					8, 
					160, 
					224, 
					GAMENn_HEAD.scr_col,
					0x0101,
					LCD_VRAM
					);
				disp_moji_s_rif(				/* 「生産下限」の文字を表示 */
					8, 
					96, 
					224, 
					0x0101
					);
#endif
				if (CMD_DAIPOS_DSP1) {		//表示？（0=非表示  1=表示）
					/* 「生産下限」そのまま表示 */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				}
				else {
					/* 「生産下限」実測表示消去 */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
					CSR_CLS_FLG = 0xff;
					CSR_disp_cls(152);
					xy_wk = (12 << 10);			//ﾊﾞｲﾄ数
					xy_wk |= (3 << 4);			//桁
					xy_wk |= 8;					//行
					Lcd_cr(00, xy_wk, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
#else
					disp_moji_s_paint(
						PV_buff[t_no].M_LEN,
						PV_buff[t_no].X_POS,
						PV_buff[t_no].Y_POS,
						GAMENn_HEAD.scr_col,
						PV_buff[t_no].SIZE,
						LCD_VRAM
						);
#endif
				}
			}
			break;

		case 15:				//ADC Windowの次型No.表示セロサプレスなし	V01j
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x201);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 16:				//ADC Windowの名称ASCII表示					V01j
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x204);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			break;

		case 17:				//ﾓｰｼｮﾝ補正(荷重)単位ASCII表示				V01j
//V01m			if(SEQ_024_SV & BIT_4)		//荷重有り？
			if(SEQ_050_SV & BIT_9)		//荷重有り？
			{
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
			}
			break;

		case 18:				//ｽﾗｲﾄﾞ自動待機機能  待機判定位置 行程 の --表示
			if (SEQ_PAR_151 & cBIT9) {
				c_wk[0] = 0x2d2d;
				disp_moji_s_color (
					PV_buff[t_no].M_LEN, 
					PV_buff[t_no].X_POS, 
					PV_buff[t_no].Y_POS, 
					PV_buff[t_no].C_COL,
					PV_buff[t_no].B_COL1, 
					PV_buff[t_no].SIZE, 
					&c_wk[0], 
					LCD_VBASE
					);
				disp_moji_s_rif (
					PV_buff[t_no].M_LEN, 
					PV_buff[t_no].X_POS, 
					PV_buff[t_no].Y_POS, 
					PV_buff[t_no].SIZE
					);
			}
			else {
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			}
			break;
	}

	chk_kajyu_offset1(disp_no, PV_buff[t_no].SUB_NO & 0x001f);	//ｵﾌｾｯﾄ校正完了が消えた用網掛けﾌﾟﾛｸﾞﾗﾑ


	disp_no ++;											//次回 表示実測値カウンタ

	return(disp_no);
}


/*
********************************************************************************
*  Module Name:		PVdata_disp1
*  Function Name:	実測値情報　表示
*  Input	:		表示ﾃｰﾌﾞﾙ番号
*					表示種別(0：通常／0xff：全表示)
*
*  Return	: 		次表示ﾃｰﾌﾞﾙ番号
*  Note		:		実測値の情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void		PVdata_disp1(UNs t_no, UNs flag)
{
	UNs		*dst_p, cnt;
	UNl		*dst_lp, cnv_bf;
	UNi		j;
	UNs		xy_wk;


	if( (PV_buff[t_no].SUB_NO & BIT_F) ||					//実測値データ未使用？
		(flag == 0 && PV_buff[t_no].TOK_FLG & BIT_6) ) {	//特殊ﾌﾗｸﾞb6 = 単位％型データ？

		disp_moji_s_paint(
			PV_buff[t_no].M_LEN,		//半角桁数
			PV_buff[t_no].X_POS,		//X始点
			PV_buff[t_no].Y_POS,		//Y始点
			GAMENn_HEAD.scr_col,	//塗潰し色
			PV_buff[t_no].SIZE,		//X/Y
			LCD_VRAM
			);
	}
	else {
		cnv_bf = 0;											//領域クリア

		cnt = (PV_buff[t_no].BYTE_NO & 0x000f);				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		if(cnt == 4){										//long(4byte) ?
			dst_lp = (UNl *)PV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_lp;								//データ読込
		}
		else{												//short(2byte)
			dst_p = PV_buff[t_no].DATA_ADR;					//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_bf = *dst_p;								//データ読込
		}

		switch(PV_buff[t_no].SUB_NO & /*0x000f V01j*/0x001f) {				//ｻﾌﾞﾙｰﾁﾝ番号 取得
			default:
			case 0x00:				//そのまま表示
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				break;
	
			case 0x01:				//シーケンスデータ	(?)
				cnv_bf = 0;										//領域 00 クリア
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x02);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 0x02:				//ＢＣＤデータ
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x02);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				break;
	
			case 0x03:				//セロサプレスなし
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 0x04:				//荷重表示
				if( SEQ_PAR_385 & BIT_7) {								//荷重測定中(表示なし)1:荷重表示
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//設定値＆実測値 表示
				}
				else {										//Yes
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x50);	//設定値＆実測値 表示
				}
				break;
	
			case 0x05:				//4ﾊﾞｲﾄ表示
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 0x06:				//ASCII表示
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 0x07:				//強調
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//設定値＆実測値 表示
				break;
	
			case 0x08:				//ストッピングタイム
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 0x09:				//セロサプレスなし強調
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x41);	//設定値＆実測値 表示
				break;
	
			case 0x0a:				//生産SPM設定中
				if( SW14_ON1_FLG == 0x01) {					//今生産設定が押し？
				}
				else {
	//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX → BCD 変換
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				}
				break;
	
			case 11:				//データ符号あり(－時は、反転表示)
				if( cnv_bf & 0x80000000 ){								//マイナス？
					cnv_bf *= -1;										//表示データを算出
	
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x81);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/反転表示)
				}
				else{
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				}
				break;
	
			case 12:				//HEX表示
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x101);	//HEX表示(ｾﾞﾛｻﾌﾟﾚｽなし)	shima
				break;
	
			/* V01 (INS) */
			case 13:				//サイクル表示
				if (CMD_1CYCLE_DSP1) {
					/* そのまま表示 */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				}
				else {
					/* 表示消去 */
					disp_moji_s_paint(
						PV_buff[t_no].M_LEN,
						PV_buff[t_no].X_POS,
						PV_buff[t_no].Y_POS,
						GAMENn_HEAD.scr_col,
						PV_buff[t_no].SIZE,
						LCD_VRAM
						);
				}
				break;
	
			/* V01 (INS) */
			case 14:				//生産下限／下限上高さ　表示
				if (SEQ_PAR_200 & BIT_5) {						//段取寸動？
					disp_moji_s_rif (				/* 「下限上高」の文字を表示 */
						8, 
						160, 
						224, 
						0x0101
						);
					disp_moji_s_paint(				/* 「生産下限」の文字を消す */
						8, 
						96, 
						224, 
						GAMENn_HEAD.scr_col,
						0x0101,
						LCD_VRAM
						);
					/* 「下限上高」そのまま表示 */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				}
	
				else {
					disp_moji_s_paint (				/* 「下限上高」の文字を消す */
						8, 
						160, 
						224, 
						GAMENn_HEAD.scr_col,
						0x0101,
						LCD_VRAM
						);
					disp_moji_s_rif(				/* 「生産下限」の文字を表示 */
						8, 
						96, 
						224, 
						0x0101
						);
					if (CMD_DAIPOS_DSP1) {		//表示？（0=非表示  1=表示）
						/* 「生産下限」そのまま表示 */
						SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
					}
					else {
						/* 「生産下限」実測表示消去 */
						disp_moji_s_paint(
							PV_buff[t_no].M_LEN,
							PV_buff[t_no].X_POS,
							PV_buff[t_no].Y_POS,
							GAMENn_HEAD.scr_col,
							PV_buff[t_no].SIZE,
							LCD_VRAM
							);
					}
				}
				break;
	
			case 15:				//ADC Windowの次型No.表示セロサプレスなし	V01j
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x201);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 16:				//ADC Windowの名称ASCII表示					V01j
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x204);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				break;
	
			case 17:				//ﾓｰｼｮﾝ補正(荷重)単位ASCII表示				V01j
				if(SEQ_050_SV & BIT_9)		//荷重有り？
				{
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽなし/正常表示)
				}
				break;

		}
	}
}


/*
********************************************************************************
*  Module Name:		SVPV_data_disp
*  Function Name:	設定値＆実測値ＬＣＤ表示
*  Input	:		ﾃﾞｰﾀ(long)
*					情報ﾃｰﾌﾞﾙ先頭ｱﾄﾞﾚｽ
*					ｾﾞﾛｻﾌﾟﾚｽ(00:あり／ff：なし)
*					フラグ：B0 = 1:HEXﾃﾞｰﾀ
*							B1 = 1:BCDﾃﾞｰﾀ
*							B2 = 1:ASCIIﾃﾞｰﾀ
*							B4 = 1:ｽﾍﾟｰｽ表示
*							B6 = 0:通常表示／1:強調表示
*							B7 = 0:正常表示／1:反転表示
*							B8 = 1:HEX表示	shima
*							B9 = 1:一番上のDotを描画
*							B10= 1:反転表示時背景緑色			V06p
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-22
********************************************************************************
*/
void	SVPV_data_disp(UNl bcd_d, void *tbl_p, UNs flag, UNs flag_2)
{
	SV_TBL_TDEF	*t_p;
	UNi		i, j, k;
	UNs		c_wk[16], w_bf;
	UNb		wk[16], wk1[16], *byte_p;
	UNs		*dst_p, *src_p;

	t_p = tbl_p;
	memset(&wk[0], E_AS_SP, 16);					//領域 ｽﾍﾟｰｽ ｸﾘｱ

	if(flag_2 & BIT_1){								//B1 = 1:BCDﾃﾞｰﾀ ?
		BCD_ASCII(bcd_d, &wk[0]);					//BCD→ASCII 変換
	}
	else if(flag_2 & BIT_2){						//B2 = 1:ASCIIﾃﾞｰﾀ ?
		i = (t_p->XY_POS >> 10);					//
		i &= 0x000f;
		i ++;
		i >>= 1;
		dst_p = &c_wk[0];
		src_p = t_p->DATA_ADR;						//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		while(i--) {
			*dst_p++ = *src_p++;
		}
	}
	else if(flag_2 & BIT_4){						//B4 = 1:ｽﾍﾟｰｽ表示 ?
	}
	else if(flag_2 & BIT_8){						//B8 = 1:HEX表示 ?	shima
		HEX_ASCII(bcd_d, &wk[0]);					//HEX→ASCII 変換	shima
	}
	else{											//B0 = 1:HEXﾃﾞｰﾀ ?
		if( t_p->TOK_FLG & BIT_8 ) {				//特殊ﾌﾗｸﾞ(B8=1:値を1/10して表示)
			bcd_d /= 10;
		}
		else if(t_p->TOK_FLG & BIT_9){				//特殊ﾌﾗｸﾞ(B9=1:mm-> mm/INCH表示)
			bcd_d = cnv_mm_inch(bcd_d, 1);			//単位切替(mm→mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_10){				//特殊ﾌﾗｸﾞ(B10=1:mm-> mm/INCH表示)
			bcd_d = cnv_mi_mi(bcd_d);				//単位切替(mm/INCH→mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_11){				//特殊ﾌﾗｸﾞ(B11=1:mm-> mm/INCH表示)
			bcd_d = cnv_mm_inch(bcd_d, 2);			//単位切替(mm→mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_12){				//特殊ﾌﾗｸﾞ(B12=1:mm/INCH-> mm/INCH表示)		V01m
			bcd_d = cnv_mi_mi_sur(bcd_d);			//単位切替(mm/INCH→mm/INCH)	ｽﾗｲﾄﾞ自動調節用
		}
		bcd_d = HEX_BCD4(bcd_d);					//HEX → BCD 変換
		BCD_ASCII(bcd_d, &wk[0]);					//BCD→ASCII 変換
	}

	if(00 == (flag_2 & BIT_2)) {					//B2 = 1:ASCIIﾃﾞｰﾀ ?
		j = i = (t_p->TEN_POS & 0x0007);				//少数点の位置の取得
		j = 8 - i;										//移動数の算出
		byte_p = &wk[7];								//ﾊﾞｯﾌｧの最終ｱﾄﾞﾚｽ算出
		if( i != 00 ){									//少数点 あり？
			while(j--) {
				*(byte_p+1) = *byte_p;
				byte_p--;
			}
			wk[i] = E_AS_TEN;							//”.”　 ［ASCIIｺｰﾄﾞ］少数点の挿入
		}

		if( flag == 0x00 ) {							//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
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
		}

		i = (t_p->XY_POS >> 10);						//BYTE -> WORD に変換
		if( t_p->TOK_FLG & BIT_2 ) {					//特殊ﾌﾗｸﾞb2 = 全角指定　？
			i >>= 1;
			k = i;
			for( j=0 ; i > 0 ; i--, j++ ){
				wk1[j] = wk[i-1];
			}
			Ascii_Sjis(k, &wk1[0], &c_wk[0]);			//ASCII -> S-JIS 変換
		}
		else{
			for( j=0 ; i > 0 ; i--, j++ ){
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
		}
	}

	if(flag_2 & BIT_7){								//B7=0:正常表示／1:反転表示
		w_bf = 0xff;								//反転表示
		if (flag_2 & BIT_10) {
			w_bf = 0x55;							//反転時の背景は緑色
		}
	}
	else{
		w_bf = 0x00;								//正常表示
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_moji_s(t_p->XY_POS, &c_wk[0], &LCD_WORK1[0][0][0], w_bf);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
#else
	if (w_bf == 0) {
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			t_p->B_COL1, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
	else if (w_bf == 0x55) {				//V06p
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			COL_GREEN, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
	else {
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			t_p->B_COL2, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
#endif


	w_bf = t_p->XY_POS;
	if( 12 == (w_bf & 0x000f) ) {					//行の取得
		dst_p = &LCD_WORK1[12][15][2];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(12行目15ﾄﾞｯﾄ目の2ﾊﾞｲﾄ目)
		i = (40-4);
		while(i--) {
			*dst_p++ |= 0x00ff;
		}
		*dst_p |= 0x0080;							//最後の１ドット
	}

//	if( WINDOW_NO != 0 && 6 == (w_bf & 0x000f) ) {	//行の取得
//		i = (w_bf >> 4);							//
//		i &= 0x003f;
//		dst_p = &LCD_WORK1[6][0][i];				//裏画面ウインドウの上段の枠を書く
//		i = (w_bf >> 10);							//
//		while(i--) {
//			*dst_p++ |= 0x00ff;
//		}
//	}

	if(flag_2 & BIT_6){								//B6 = 0:通常表示／1:強調表示
		kyoutyou_set(w_bf);							//強調文字変換
	}

	if(flag_2 & BIT_9){								//B9 = 0:通常表示／1:最上位DOTに描画	V01j
		Nextkno_Name_draw(w_bf);					//
	}

	if( SVPV_LCD_FLG == 00 ) {						//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Lcd_cr(00, w_bf, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
#else
		disp_moji_s_rif (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->SIZE
			);
#endif
	}

}


void	SVPV_data_NOdisp(void *tbl_p)
{
	SV_TBL_TDEF	*t_p;
	UNs		w_bf;
	t_p = tbl_p;
	w_bf = t_p->XY_POS;
	Lcd_cr(00, w_bf, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示

}


/*
********************************************************************************
*  Module Name:		Count_hosei_csr_on
*  Function Name:	カウンタ補正の実測値反転処理
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
void	Count_hosei_csr_on(UNs xy_no)
{
	if(00 != xy_no){
		disp_memnot(xy_no, &LCD_WORK2[0][0][0]);	//表示用領域の指定ﾃﾞｰﾀを反転
		Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);		//ｷｬﾗ単位表示
	}
}


/*
********************************************************************************
*  Module Name:		SVSW_tbl_enzan
*  Function Name:	ＳＶＳＷテーブルアドレス演算
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
void	SVSW_tbl_enzan(void)
{
	UNs		i, j;

	CSR_TBL_POS_NOW = CSR_FLG_CNT - 1;							//カーソル番号検索

	if( SV_CNT == 00 ) {										//設定値なし
		SV_TBL_POS_NOW = 0xff;									//異常コードセット
	}
	else {
		SV_TBL_POS_NOW = 0xff;									//異常コードセット
		for( i = SV_CNT,j=0 ; i > 0 ; i--, j++) {
			if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {			//設定値データ未使用？
				if(SV_buff[j].CSR_NO == CSR_FLG_CNT &&			//ｶｰｿﾙ認識番号
					SV_buff[j].DSP_NO == SV_FLG_CNT ) {			//ｶｰｿﾙ認識番号内の移動順位

					SV_TBL_POS_NOW = j;							//設定値データ検索終了
					break;
				}
			}
		}
	}

	if( SW_CNT == 00 ) {										//ＳＷデータなし
		SW_TBL_POS_NOW = 0xff;									//異常コードセット
	}
	else {
		SW_TBL_POS_NOW = 0xff;									//異常コードセット
		for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
			if(SW_buff[j].CSR_NO == CSR_FLG_CNT &&				//ｶｰｿﾙ認識番号
				SW_buff[j].DSP_NO == SW_FLG_CNT ) {				//ｶｰｿﾙ認識番号内の移動順位

				SW_TBL_POS_NOW = j;								//ＳＷデータ検索終了
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		kyoutyou_set
*  Function Name:	強調文字変換
*  Input	:		表示位置情報
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-18
********************************************************************************
*/
void	kyoutyou_set(UNs xy_no)
{
	UNi		i, j;
	UNs		*dst_p, *dst_p1, cy_flg, wk;

	i = xy_no & 0x000f;						//行のｱﾄﾞﾚｽ　算出
	j = ( xy_no >> 4) & 0x003f;				//桁のｱﾄﾞﾚｽ　算出
	dst_p1 = &LCD_WORK1[i][0][j];			//LCD表示領域のｱﾄﾞﾚｽ設定

	for( i=16 ; i > 0 ; i-- ) {
		dst_p = dst_p1;
		cy_flg = 0;
		j = ( xy_no >> 10);					//文字数　算出
		while(j--){
			wk = *dst_p;
			if(wk & 0x0001){				//次の文字へ反映されるか？
				wk >>= 1;
				wk |= cy_flg;
				cy_flg = 0x0080;
			}
			else{							//No
				wk >>= 1;
				wk |= cy_flg;
				cy_flg = 0x0000;
			}
			*dst_p++ |= wk;
		}
		dst_p1 += E_next_dot;				//1文字の次dot位置数
	}
}


/*
********************************************************************************
*  Module Name:		Nextkno_Name_draw
*  Function Name:	最上位DOTに描画
*  Input	:		表示位置情報
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-06-01			V01j
********************************************************************************
*/
void	Nextkno_Name_draw(UNs xy_no)
{
	UNi		i, j, k;

	i = xy_no & 0x000f;						//行
	j = ( xy_no >> 4) & 0x003f;				//桁
	k = ( xy_no >> 10) & 0x003f;			//文字数

	for( ; k > 0 ; k--, j++ ) {
		LCD_WORK1[i][0][j] = 0xff;			//
	}
}


/*
********************************************************************************
*  Function Name:	網掛け
*
*  履 歴	:Shima		ON:2015-05-19
********************************************************************************
*/
void	chk_kajyu_offset1(UNs disp_no, UNs code)
{
	if (GAMEN_NO == 44) {
		if ( (disp_no >= 1) && (disp_no <= 3) ) {
			chk_kjofs_dat[disp_no-1] = code+1;
		}
	}
}


/*** END ***/
