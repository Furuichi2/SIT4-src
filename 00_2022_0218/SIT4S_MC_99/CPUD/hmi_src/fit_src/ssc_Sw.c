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
#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		GMN_PAR035;						//ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間 /* V01n */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR077;
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	SWchg_ent(void);						//SW CHG データ ENT
void	SWchg_move_ent(void);					//SW CHGの移動 ﾃﾞｰﾀENT
void	SWchg_mmon_ent(void);					//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT

void	SWchg_bit_chk(void);					//ＳＷデータ入力時強制選択拒否処理
void	SWchg_disp_pv_any(void);				//SWﾃﾞｰﾀ　実測値 表示
void	SWchg_disp_pv(void);					//ＳＷＣＨＧデータ表示実測処理

void	SWchg_disp(void);						//ＳＷデータ情報　表示
void	SWchg_disp_gaibu(void);					//SWﾃﾞｰﾀ情報　表示
void	SWchg_disp_one(UNi);					//1ＳＷデータ情報　表示
void	SWchg_set(UNi, UNs, UNs *);				//ＳＷキャラクタ表示処理
void	SWchg_set_dan(UNi, UNs *);				//ＳＷキャラクタ表示処理(段取り用)
void	SWchg_set_op(UNi, UNs *);				//ＳＷキャラクタ表示処理(オフセット調節用)
void	SWchg_dispset(UNi);						//カーソル反転表示処理
void	SWchg_dispset_dan(UNi);					//カーソル反転表示処理(段取り用)

void	Under_grph(void);						//下段のグラフィックセット
void	WIN_grph(void);							//ウインドウ画面上グラフィック描画

void	SW16data_onset(UNs, UNi);				//ＳＷ１～６の反転指定を行う
void	SW56_upcara_disp(UNs, UNs);				//ＳＷ５６上段キャラクタをＳＷ領域へ格納
void	SW56_dncara_disp(UNs, UNs);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納
void	SW56dn_clear(UNs);						//SWｷｬﾗｸﾀのﾃﾞｰﾀﾊﾟｰﾀｰﾝｸﾘｱ

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
extern	const	UNs *	SW56_Cam_Name_Tbl[69];
extern	const	UNs *	Camcsr_Name_Tbl1[16];

const	UNs	SW56_Up_Pos_Tbl[13]={
				0x002d,					//{2,13}	//00
				0x002d,					//{2,13}	//01
				0x008d,					//{8,13}	//02
				0x00ed,					//{14,13}	//03
				0x014d,					//{20,13}	//04
				0x01ad,					//{26,13}	//05
				0x020d,					//{32,13}	//06
				0x01ae,					//{26,14}	//07
				0x020e,					//{32,14}	//08
				0x002e,					//{2,14}	//09
				0x008e,					//{8,14}	//10
				0x00ee,					//{14,14}	//11
				0x014e					//{20,14}	//12
			};

const	UNs	SW56_Up_Pos_Tbl_color[15][2]={
			{  10,	416 },//00
			{  10,	416 },//01	SW1上段
			{ 100,	416 },//02	SW2上段
			{ 190,	416 },//03	SW3上段
			{ 280,	416 },//04	SW4上段
			{ 460,	416 },//05	SW5上段
			{ 550,	416 },//06	SW6上段
			{ 460,	448 },//07	SW5下段
			{ 550,	448 },//08	SW6下段
			{  10,	448 },//09	SW1下段
			{ 100,	448 },//10	SW2下段
			{ 190,	448 },//11	SW3下段
			{ 280,	448 },//12	SW4下段
			{ 370,	416 },//13	SW7上段			2014/09/09
			{ 370,	448 } //14	SW7下段			2014/09/09
			};

const	UNs	SPACE_ASCII_40[40]={
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020
			};


/*
********************************************************************************
*  Module Name:		SWchg_ent
*  Function Name:	SW CHG データ ENT
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	SWchg_ent(void)
{
	UNs		*bf_p, bit_d1, bit_d2, bit_d3, bit_d4;
	UNi		t_no;


	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//ＳＷデータ 有り？
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWﾃｰﾌﾞﾙ個数 が無いときはＳＷ無しでやめる
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//特殊ﾌﾗｸﾞ b1=入力処理無し
		return;
	}

	bf_p = SW_buff[t_no].DATA_ADR;						//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	bit_d2 = bit_d1 = SW_buff[t_no].CHG_NO;				//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
	bit_d4 = bit_d3 = *bf_p;

	bit_d2 = ~bit_d2;									//反転
	bit_d3 &= bit_d1;
	bit_d4 &= bit_d2;
	bit_d3 = ~bit_d3;									//反転
	bit_d3 &= bit_d1;
	bit_d4 |= bit_d3;
	*bf_p = bit_d4;										//変更後のデータを格納する

	SWchg_bit_chk();									//ＳＷデータ入力時強制選択拒否処理
	ONOFF_FLG = 0;										//ここでは使用しないため強制クリア

	FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	bit_d1 = SW_buff[t_no].SAVE_NO;						//格納ﾌﾗｸﾞ
	SVSW_CHG_FLG |= bit_d1;								//データチェンジフラグセット

	SWchg_disp_one(t_no);								//1ＳＷデータ情報　表示

	WIN_grph();											//ウインドウ画面上グラフィック描画

	Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);	//ｷｬﾗ単位表示
	Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示

}


/*
********************************************************************************
*  Module Name:		SWchg_move_ent
*  Function Name:	SW CHGの移動 ﾃﾞｰﾀENT
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-02
********************************************************************************
*/
void	SWchg_move_ent(void)
{
	UNs		t_no, c_no, c_max, sw_no;

	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//ＳＷデータ 有り？
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWﾃｰﾌﾞﾙ個数 が無いときはＳＷ無しでやめる
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//特殊ﾌﾗｸﾞ b1=入力処理無し
		return;
	}

	SWchg_ent();										//SW CHG データ ENT

	c_max = CSR_buff[CSR_TBL_POS_NOW].SW_MAX;
	if( c_max > 1 ){									//ｶｰｿﾙ数が1以上？
		c_no = SW_buff[t_no].CSR_NO;					//この設定値の属するｶｰｿﾙ認識番号
		sw_no = SW_buff[t_no].DSP_NO;					//ｶｰｿﾙ認識番号内の移動順位

		do {
			sw_no ++;
			if( sw_no > c_max ){
				sw_no = 1;								//ｶｰｿﾙ認識番号内の移動順位 を初期化
			}
			for( t_no=0 ;  t_no < SW_CNT ; t_no++ ){
				if(SW_buff[t_no].CSR_NO == c_no){		//ｶｰｿﾙ認識番号が一致
					if(SW_buff[t_no].DSP_NO == sw_no){	//移動順位が一致
						SW_TBL_POS_NOW = t_no;			//次位置の設定
						break;
					}
				}
			}
		} while( SW_buff[t_no].SUB_NO & BIT_F );		//SWﾃﾞｰﾀ未使用？

		SWchg_ent();									//SW CHG データ ENT
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_mmon_ent
*  Function Name:	ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-31
********************************************************************************
*/
void	SWchg_mmon_ent(void)
{
	UNs		*bf_p, bit_d1;
	UNi		t_no;
	UNs		*degn, i, j, ww0;

	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//ＳＷデータ 有り？
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWﾃｰﾌﾞﾙ個数 が無いときはＳＷ無しでやめる
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//特殊ﾌﾗｸﾞ b1=入力処理無し
		return;
	}

/* V01n INS */
	if ( ((SEQ_024_SV & BIT_5) == BIT_5) && (CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 99))		// V01n(INS)
	{																						//ﾓｰｼｮﾝ3段目
		j = SEQ_PAR_119 >> 12;
		if (j & 0x000F)
		{
			degn = &GMN_PAR035;
			for ( i=4 ; i>0 ; i--, j=j>>1, degn++)
			{
				if (j & BIT_0)
				{
					ww0 = *degn;
					break;
				}
			}
			if (ww0 != 0)
			{
				goto SWchg_mmon_et_EXT;
			}
		}
	}
/* END */

	bf_p = SW_buff[t_no].DATA_ADR;						//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	*bf_p = 0;											//変更後のデータを格納する

//	FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	bit_d1 = SW_buff[t_no].SAVE_NO;						//格納ﾌﾗｸﾞ
	SVSW_CHG_FLG |= bit_d1;								//データチェンジフラグセット

	SWchg_disp_one(t_no);								//1ＳＷデータ情報　表示
	SV_csr_set();										//2014/09/25

	mmon_f_off(CSR_TBL_POS_NOW);						//一定速度設定ｸﾘｱ				2014/09/25

	Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);	//ｷｬﾗ単位表示
//	Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示

SWchg_mmon_et_EXT:
	return;
}


/*
********************************************************************************
*  Module Name:		SWchg_bit_chk
*  Function Name:	ＳＷデータ入力時強制選択拒否処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	SWchg_bit_chk(void)
{

	if(ONOFF_FLG != 0xff){
		ONOFF_FLG = 0;
	}
//SIT-Sなし
//	if( 00 == (SEQ_016_SV & BIT_7)){			//簡易機能選択？
//		if( SEQ_017_SV & 0xffc0 ){				//エジェクタ１進角＋エジェクタ２選択
//			SEQ_017_SV &= 0x003f;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_018_SV & 0xae3f ){
//			SEQ_018_SV &= 0x51c0;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_019_SV & 0xfeaf ){
//			SEQ_019_SV &= 0x0150;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_020_SV & 0x0957 ){
//			SEQ_020_SV &= 0xf6a8;
//			ONOFF_FLG = 0xff;
//		}
//	}
	if( 00 == (SEQ_016_SV & BIT_C)){			//ロットカウンタ１有り？
		if(SEQ_016_SV & BIT_E){					//ロットカウンタ２選択？
			SEQ_016_SV &= ~BIT_E;
			ONOFF_FLG = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_pv_any
*  Function Name:	SWﾃﾞｰﾀ　実測値 表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	SWchg_disp_pv_any(void)
{
	UNi	cnt;
	UNs	*src_p;

	if( WINDOW_NO==4 || WINDOW_NO==11 ){			//シーケンスチェック画面
	/* ｼｰｹﾝｽ･ﾃﾞｰﾀの設定	*/
		src_p = &SEQ_PAR_000;						//ｼｰｹﾝｽ領域の先頭ｱﾄﾞﾚｽ
		PV_SEQDT1_A91 = *(src_p + SV_SEQDT1_A91);	//ｼｰｹﾝｽﾓﾆﾀ設定1
		PV_SEQDT2_A91 = *(src_p + SV_SEQDT2_A91);	//ｼｰｹﾝｽﾓﾆﾀ設定2
		PV_SEQDT3_A91 = *(src_p + SV_SEQDT3_A91);	//ｼｰｹﾝｽﾓﾆﾀ設定3
		PV_SEQDT4_A91 = *(src_p + SV_SEQDT4_A91);	//ｼｰｹﾝｽﾓﾆﾀ設定4

//		cnt = (SW_CNT >> 1);					//1/2
		cnt = (SW_CNT >> 2);					//1/4
	}
	else{										//No
		cnt = 1;
	}
	while(cnt--){
		SWchg_disp_pv();						//ＳＷＣＨＧデータ表示実測処理
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_pv
*  Function Name:	ＳＷＣＨＧデータ表示実測処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	SWchg_disp_pv(void)
{
	UNi		t_no;

	if(SW_CNT == 00) {									//ＳＷデータ 有り？
		return;											//なし
	}

	if(SW_DISP_CNT > SW_CNT ){							//ＳＷデータ実測値
		SW_DISP_CNT = 1;
	}
	t_no = (SW_DISP_CNT - 1);

	if( 00 == (SW_buff[t_no].SUB_NO & BIT_F) ) {		//ＳＷデータ未使用？
		if( SW_buff[t_no].TOK_FLG & BIT_1 ) {			//ＳＷ表示有り？
			if(00 == (SW_buff[t_no].TOK_FLG & BIT_6)){	//一回だけ表示？

				SWchg_disp_one(t_no);					//1ＳＷデータ情報　表示

				Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
				if( SW_buff[t_no].TOK_FLG & BIT_0 ) {						//反転表示有り？
					Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示
				}
			}
		}
	}
	SW_DISP_CNT ++;										//次回表示ＳＷデータカウンタ
}


/*
********************************************************************************
*  Module Name:		SWchg_disp
*  Function Name:	ＳＷデータ情報　表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ＳＷデータの情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	SWchg_disp(void)
{
	UNi		i, j;

	if(SW_CNT == 00) {									//ＳＷデータ 有り？
		return;											//なし
	}
	i = SW_CNT;
	j = 0;

//	if( SW_buff[j].SUB_NO & BIT_F ) {					//ＳＷデータ未使用？
//		j ++;											//次 情報ﾃｰﾌﾞﾙ
//		i --;
//	}
	for( ; i > 0 ; i --,j++ ) {

		if( 00 == (SW_buff[j].SUB_NO & BIT_F) ) {			//ＳＷデータ未使用？

			SWchg_disp_one(j);								//1ＳＷデータ情報　表示

			if( SWCHG_DISP_ON_FLG == 0xff ) {
				Lcd_cr(00, SW_buff[j].XY_POS, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示

				if( SW_buff[j].TOK_FLG & BIT_0 ) {			//反転表示有り？
					Lcd_cr(01, SW_buff[j].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_gaibu
*  Function Name:	SWﾃﾞｰﾀ情報　表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		SWﾃﾞｰﾀの情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-07-17
********************************************************************************
*/
void	SWchg_disp_gaibu(void)
{
	UNi		cnt, t_no;

	if(SW_CNT1 == 00) {									//ＳＷデータ 有り？
		return;											//なし
	}
	cnt = SW_CNT1;
	t_no = 0;

//	if( SW_buff[t_no].SUB_NO & BIT_F ) {				//ＳＷデータ未使用？
//		t_no ++;										//次 情報ﾃｰﾌﾞﾙ
//		cnt --;
//	}
	for( ; cnt > 0 ; cnt--,t_no++ ) {

		if( 00 == (SW_buff[t_no].SUB_NO & BIT_F) ) {		//ＳＷデータ未使用？

			SWchg_disp_one(t_no);							//1ＳＷデータ情報　表示

			if( SWCHG_DISP_ON_FLG == 0xff ) {
				Lcd_cr(0, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示

				if( SW_buff[t_no].TOK_FLG & BIT_0 ) {						//反転表示有り？
					Lcd_cr(1, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_one
*  Function Name:	1ＳＷデータ情報　表示
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*
*  Return	: 		なし
*  Note		:		指定されたＳＷデータの情報ﾃｰﾌﾞﾙを基に表示する
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	SWchg_disp_one(UNi T_no)
{
	UNs		*Src_p, i, j;

	i = SW_buff[T_no].SUB_NO;							//ｻﾌﾞﾙｰﾁﾝ番号 取得
	if( i & BIT_F ) {									//ＳＷデータ未使用？
		i = 1;
	}
//2014/09/04
////	else{												//No
////		i &= 0x0007;
////	}

	switch( i ) {
		default:
		case 0x0000:				//通常の２ノッチＳＷ
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//ＳＷキャラクタ表示処理
			SWchg_dispset(T_no);								//カーソル反転表示処理
#else
//2014/09/02			SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//ＳＷキャラクタ表示処理
			SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ表示処理
#endif
			break;

		case 0x0001:				//仕様初期画面用ベースキャラクタの反転選択
			if(GAMEN_NO != 18) {						//データ設定選択で反転してしまう
				SWchg_dispset(T_no);					//カーソル反転表示処理
			}
			break;

		case 0x0002:				//段取り画面閉開等のシーケンスバック処理
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_set_dan(T_no, &LCD_WORK1[0][0][0]);			//ＳＷキャラクタ表示処理(段取り用)
			SWchg_dispset_dan(T_no);					//カーソル反転表示処理(段取り用)
#else
			SWchg_set_dan_color(T_no, LCD_VBASE);			//ＳＷキャラクタ表示処理(段取り用)	//V05a
#endif
			break;

		case 0x0003:				//カム名称汎用出力反転処理
			SWchg_dispset(T_no);						//カーソル反転表示処理
			break;

		case 0x0004:				//データ設定（中型）画面選択表示処理
			Src_p = SW_buff[T_no].KAN_ADR;							//関連ｱﾄﾞﾚｽ
			i = SW_buff[T_no].KAN_NO;								//関連ﾊﾞｲﾄ

			if( *Src_p & i ) {										//選択有り？
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//ＳＷキャラクタ表示処理
				SWchg_dispset(T_no);								//カーソル反転表示処理
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//ＳＷキャラクタ表示処理
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ表示処理
#endif
			}
			else{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, 0x0000, &LCD_WORK1[0][0][0]);				//ＳＷキャラクタ表示処理
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//ＳＷキャラクタ表示処理
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ表示処理
#endif
			}
			break;

		case 0x0005:				//オフセット調節&荷重構成メッセージ表示
			SWchg_set_op(T_no, &LCD_WORK1[0][0][0]);				//ＳＷキャラクタ表示処理(オフセット調節用)
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_dispset(T_no);						//カーソル反転表示処理
#endif
			break;
//		case 0x0006:				//上型ｸﾗﾝﾊﾟ６選択		SIT-Sでは、機能なし
//			break;

		case 0x0006:				//ﾓｰｼｮﾝ設定　停止時間
			Src_p = SW_buff[T_no].DATA_ADR;							//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			if( *Src_p == 00 ) {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//ＳＷキャラクタ表示処理
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//ＳＷキャラクタ表示処理
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ表示処理
#endif
			}
			break;

		case 7:						//進角の単位			2014/09/02
			if ((SEQ_PAR_151 & BIT_11)==0) {				//時間進角機能
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 1);	//ＳＷ OFFキャラクタ表示処理
			}
			else {
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ表示処理
			}
			break;

		case 8:						//ロータリカム、エジェクタ、ミスフォードの行程「Ｒ」表示		//2014/09/04
			if (GMN_PAR077 != 0) {
				Src_p = SW_buff[T_no].DATA_ADR;							//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				j = SW_buff[T_no].CHG_NO;								//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
				if(*Src_p & j) {										//ＯＮ状態？
					SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//ＳＷキャラクタ「Ｒ」表示処理
					SV_csr_set();
				}
			}
			break;


	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set
*  Function Name:	ＳＷキャラクタ表示処理
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*					表示用ｷｬﾗｸﾀ番号
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
void	SWchg_set(UNi T_no, UNs c_no, UNs *Dst_p)
{
	UNs		i, j, *buff_p, *g_p;

//	i = SW_buff[T_no].CARA_NO;						//表示用ｷｬﾗｸﾀ番号
	i = c_no;										//表示用ｷｬﾗｸﾀ番号
	i *= 10;										//一キャラクタのグループは全角１０文字とするので２０倍

	buff_p = SW_buff[T_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	j = SW_buff[T_no].CHG_NO;						//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
	if(*buff_p & j) {								//ＯＮ状態？
		i += 5;										//ＯＮの時は全角４後ろに有るので
	}

	g_p = mess_adr_shr( 10 );								//メッセージ画面キャラクタアドレス検索
	g_p += i;												//メッセージ画面キャラクタアドレス算出
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

}


/*
********************************************************************************
*  Module Name:		SWchg_set_dan
*  Function Name:	ＳＷキャラクタ表示処理(段取り用)
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-24
********************************************************************************
*/
void	SWchg_set_dan(UNi T_no, UNs *Dst_p)
{
	UNs		i, j, k, *buff_p, *g_p;


	i = SW_buff[T_no].CARA_NO;						//表示用ｷｬﾗｸﾀ番号
	i *= 10;										//一キャラクタのグループは全角１０文字とするので２０倍

	buff_p = SW_buff[T_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	j = SW_buff[T_no].CHG_NO;						//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
	k = *buff_p;									//必要なビットだけを抽出
	k &= j;

	if(k==0 || k==j ) {								//０＝スペース || ３＝スペース
		i = 0;
	}
	else{
		j &= 0x00aa;
		if( k & j) {
			i += 5;									//ＯＮの時は全角４後ろに有るので
		}
	}
	g_p = mess_adr_shr( 10 );								//メッセージ画面キャラクタアドレス検索
	g_p += i;												//メッセージ画面キャラクタアドレス算出
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

}


/*
********************************************************************************
*  Module Name:		SWchg_set_op
*  Function Name:	ＳＷキャラクタ表示処理(オフセット調節用)
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*					格納ﾊﾞｯﾌｧｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-24
********************************************************************************
*/
void	SWchg_set_op(UNi T_no, UNs *Dst_p)
{
	UNs		i, *g_p, *buff_p;
	UNi		flg;
	UNs		len, col;
	UNl		adr;
	UNs		*hrom;

	buff_p = SW_buff[T_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	i = *buff_p;									//ｷｬﾗｸﾀ番号
	if(i == 0) {
		flg = 0;									//正常表示
	}
	else{
		flg = 0xff;									//反転表示
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	i *= 20;										//一キャラクタのグループは全角２０文字とするので４０倍
	g_p = mess_adr_shr( 13 );								//メッセージ画面キャラクタアドレス検索
	g_p += i;												//メッセージ画面キャラクタアドレス算出
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, flg);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
#else
	adr = SPE_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SPE_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	hrom = (UNs *)adr;
	len = *hrom++;
	len >>= 8;
	if ( i == 0 ) {
		hrom = &SPACE_ASCII_40[0];
		col = SW_buff[T_no].B_COL1;					/* 背景色			*/
	}
	else {
		adr = SPE_TABLE_ADR + ((i-1) * CHAR_SPE_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (UNs *)adr;
		hrom++;
		col = SW_buff[T_no].B_COL2;					/* 背景色			*/
	}
	disp_moji_s_color(
		len,									/* ｷｬﾗｸ長			*/
		SW_buff[T_no].X_POS,					/* 書出しX位置		*/
		SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
		SW_buff[T_no].C_COL,					/* 文字色			*/
		col,									/* 背景色			*/
		SW_buff[T_no].SIZE,						/* 文字ｻｲｽﾞ			*/
		hrom,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE								/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif (
		len,									/* ｷｬﾗｸ長			*/
		SW_buff[T_no].X_POS,					/* 書出しX位置		*/
		SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
		SW_buff[T_no].SIZE						/* 文字ｻｲｽﾞ			*/
		);
#endif
}


/*
********************************************************************************
*  Module Name:		SWchg_dispset
*  Function Name:	カーソル反転表示処理
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-23
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	SWchg_dispset(UNi T_no )
{
	UNs		j, *buff_p;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {								//ＯＮ反転あり？
		/*** まず通常のＯＦＦ状態	***/
		disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0x00 );		//表示用領域を指定ﾃﾞｰﾀで設定

		/***	指定がＯＮ状態の時は反転させる	***/
		buff_p = SW_buff[T_no].DATA_ADR;							//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		j = SW_buff[T_no].CHG_NO;									//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置

		if(*buff_p & j) {											//ＯＮ状態？
			disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0xff );	//表示用領域を指定ﾃﾞｰﾀで設定
		}
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	SWchg_dispset(UNi T_no )
{
	UNs		j, *buff_p;
	UNl		adr;
	UNs		*hrom, len;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {								//ＯＮ反転あり？

		/*** まず通常のＯＦＦ状態	***/
		adr =  SWL_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (UNs *)adr;
		len = *hrom++;
		len >>= 8;
		disp_moji_s_color(
			len,									/* ｷｬﾗｸ長			*/
			SW_buff[T_no].X_POS,					/* 書出しX位置		*/
			SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
			SW_buff[T_no].C_COL,					/* 文字色			*/
			SW_buff[T_no].B_COL1,					/* 背景色			*/
			SW_buff[T_no].SIZE,						/* 文字ｻｲｽﾞ			*/
			hrom,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE								/* 表示ﾒﾓﾘ			*/
			);

		/***	指定がＯＮ状態の時は反転させる	***/
		buff_p = SW_buff[T_no].DATA_ADR;							//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		j = SW_buff[T_no].CHG_NO;									//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置

		if(*buff_p & j) {											//ＯＮ状態？
			hrom += (8/2);
			disp_moji_s_color(
				len,									/* ｷｬﾗｸ長			*/
				SW_buff[T_no].X_POS,					/* 書出しX位置		*/
				SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
				SW_buff[T_no].C_COL,					/* 文字色			*/
				SW_buff[T_no].B_COL2,					/* 背景色			*/
				SW_buff[T_no].SIZE,						/* 文字ｻｲｽﾞ			*/
				hrom,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
				LCD_VBASE								/* 表示ﾒﾓﾘ			*/
				);
		}

		disp_moji_s_rif (
			len,									/* ｷｬﾗｸ長			*/
			SW_buff[T_no].X_POS,					/* 書出しX位置		*/
			SW_buff[T_no].Y_POS,					/* 書出しY位置		*/
			SW_buff[T_no].SIZE						/* 文字ｻｲｽﾞ			*/
			);
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SWchg_dispset_dan
*  Function Name:	カーソル反転表示処理(段取り用)
*  Input	:		ＳＷデータ情報ﾃｰﾌﾞﾙの番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-24
********************************************************************************
*/
void	SWchg_dispset_dan(UNi T_no )
{
	UNs		i, j, *buff_p;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {									//ＯＮ反転あり？
		/*** まず通常のＯＦＦ状態	***/
		disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0x00 );	//表示用領域を指定ﾃﾞｰﾀで設定

		/***	指定がＯＮ状態の時は反転させる	***/
		buff_p = SW_buff[T_no].DATA_ADR;								//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		j = SW_buff[T_no].CHG_NO;										//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
		i = *buff_p;													//必要なビットだけを抽出

		i &= j;															//不必要なビットをマスクする。
		if( i != j ) {													//両方のビットがたっていたら反転しない
			j &= 0x00aa;												//反転表示ビットを作成（２ビットの左側がＯＮ表示）
			if( i & j) {												//ＯＮ状態？
				disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0xff );	//表示用領域を指定ﾃﾞｰﾀで設定
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Under_grph
*  Function Name:	下段のグラフィックセット
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-24
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	Under_grph(void)
{
	UNs		*Dst_p, dot_d;
	UNi		cnt;

	Dst_p = &LCD_WORK1[12][15][2];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(12行目15ﾄﾞｯﾄ目の2ﾊﾞｲﾄ目)
	dot_d = 0x00ff;								//ドットパターンセット
	cnt = (40-4);
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}
	*Dst_p |= 0x0080;							//最後の１ドット

	//速度設定部分の横線
	Dst_p = &LCD_WORK1[13][15][26];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目15ﾄﾞｯﾄ目の26ﾊﾞｲﾄ目)
	dot_d = 0x00ff;								//ドットパターンセット
	cnt = 12;
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}

	//下段の縦ライン１
	Dst_p = &LCD_WORK1[13][0][2];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の2ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン２
	Dst_p = &LCD_WORK1[13][0][8];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の8ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン３
	Dst_p = &LCD_WORK1[13][0][14];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の14ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン4
	Dst_p = &LCD_WORK1[13][0][20];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の20ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン5
	Dst_p = &LCD_WORK1[13][0][26];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の26ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン7
	Dst_p = &LCD_WORK1[13][0][38];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(13行目の38ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//下段の縦ライン８半分
	Dst_p = &LCD_WORK1[14][0][32];				//下段のｱﾝﾀﾞｰﾗｲﾝのｱﾄﾞﾚｽ算出(14行目の32ﾊﾞｲﾄ目)
	dot_d = 0x0080;								//ドットパターンセット
	cnt = 16;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1文字の次dot位置数
	}

	//画面先頭半角１０文字分の反転
	disp_memset(0x2800, &LCD_WORK2[0][0][0], 0xff );	//0行目0桁目から10文字

}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
const	UNs	UNDER_GRAP_TBL[8][4] = {
		{   0, 416,  91,  64 },
		{  91, 416,  91,  64 },
		{ 182, 416,  91,  64 },
		{ 273, 416,  91,  64 },
		{ 364, 416,  92,  64 },
		{ 456, 416, 184,  32 },
		{ 456, 448,  92,  32 },
		{ 548, 448,  92,  32 }
		};

void	Under_grph(void)
{
	UNs		k, i, xdot, ydot;

	for (i=0; i<8; i++)
	{
		xdot = UNDER_GRAP_TBL[i][0];
		ydot = UNDER_GRAP_TBL[i][1];

		//縦線
		k = UNDER_GRAP_TBL[i][3];;							// Ｙ距離
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			ydot++;
		}
		//横線
		k = UNDER_GRAP_TBL[i][2];;							// Ｙ距離
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			xdot++;
		}
		//縦線
		k = UNDER_GRAP_TBL[i][3];;							// Ｙ距離
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			ydot--;
		}
		//横線
		k = UNDER_GRAP_TBL[i][2];;							// Ｙ距離
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			xdot--;
		}
	}
}
#endif

/*
********************************************************************************
*  Module Name:		WIN_grph(旧:WIN_GRPH_WRITE)
*  Function Name:	ウインドウ画面上グラフィック描画
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	WIN_grph(void)
{
	UNs		*Dst_p, dot_d;
	UNi		cnt;

	if(WINDOW_NO == 5 || WINDOW_NO == 19){

		Dst_p = &LCD_WORK1[6][0][0];				//裏画面ウインドウの上段の枠を書く
		dot_d = 0x00ff;								//ドットパターンセット
		cnt = 40;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	WIN_grph(void)
{
	UNs		i, xpos, ypos;

	if(WINDOW_NO == 5 || WINDOW_NO == 19 || WINDOW_NO == 20){
		for (i=0, xpos=0, ypos=PanelHeight-WindowHeight; i<PanelWidth; i++, xpos++)	/* LINE ﾃﾞｰﾀ作成		*/
		{
			LCD_VBASE[ypos][xpos] = 0;
			LCD_VRAM[ypos][xpos] = 0;
		}
	}
	else if( (6 <= WINDOW_NO) && (WINDOW_NO <= 9) ) {
		for (i=0, xpos=0, ypos=PanelHeight-WindowHeight; i<PanelDANWidth; i++, xpos++)	/* LINE ﾃﾞｰﾀ作成		*/
		{
			LCD_VBASE[ypos][xpos] = 0;
			LCD_VRAM[ypos][xpos] = 0;
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SW16data_onset
*  Function Name:	ＳＷ１～６の反転指定を行う
*  Input	:		ﾊﾟﾀｰﾝﾃﾞｰﾀの指定
*					SW位置：1=SW1,2=SW2,3=SW3,4=SW4,
*							5=SW5上,6=SW6上,7=SW5下,8=SW6下
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-28
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
typedef struct {
	UNs	*ADDR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNi	CNT1;
	UNi	CNT2;
	} SW14_TBL_TDEF;

const	SW14_TBL_TDEF	SW14data_Pos_Tbl[9] = {
				{&LCD_WORK2[13][0][2], 06, 32},			//00[SW1]
				{&LCD_WORK2[13][0][2], 06, 32},			//01[SW1]
				{&LCD_WORK2[13][0][8], 06, 32},			//02[SW2]
				{&LCD_WORK2[13][0][14], 06, 32},		//03[SW3]
				{&LCD_WORK2[13][0][20], 06, 32},		//04[SW4]
				{&LCD_WORK2[13][0][26], 06, 15},		//05[SW5上]
				{&LCD_WORK2[13][0][32], 06, 15},		//06[SW6上]
//				{&LCD_WORK2[13][0][26], 06, 16},		//05[SW5上]
//				{&LCD_WORK2[13][0][32], 06, 16},		//06[SW6上]
				{&LCD_WORK2[14][0][26], 06, 16},		//07[SW5下]
				{&LCD_WORK2[14][0][32], 06, 16} };		//08[SW6下]

void	SW16data_onset(UNs d_ptn, UNi sw_no)
{
	UNs	*bf_p, *dst_p;
	UNi	cnt1, cnt2, i;

	bf_p = SW14data_Pos_Tbl[sw_no].ADDR;				//LCD用ﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
	cnt1 = SW14data_Pos_Tbl[sw_no].CNT1;				//長さ
	cnt2 = SW14data_Pos_Tbl[sw_no].CNT2;				//高さ

	for( ; cnt2 > 0 ; cnt2--) {
		dst_p = bf_p;
		i = cnt1;
		if( sw_no != 06) {							//ＳＷ６クリア？
			i--;									//最初のワードは反転すると縦線が消えるから対策
			*dst_p++ = d_ptn & 0x007f;
		}
		while(i--){
			*dst_p++ = d_ptn & 0x00ff;
		}
		bf_p += E_next_dot;							//1文字の次dot位置数
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/		//V01y
////		{   0, 416,  91,  64 },
////		{  91, 416,  91,  64 },
////		{ 182, 416,  91,  64 },
////		{ 273, 416,  91,  64 },
////		{ 364, 416,  92,  64 },
////		{ 456, 416, 184,  32 },
////		{ 456, 448,  92,  32 },
////		{ 548, 448,  92,  32 }
typedef struct {
	UNs	stat_xdot;			// x開始位置
	UNs	stat_ydot;			// y開始位置
	UNs	leng_xdot;			// x長さ
	UNs	leng_ydot;			// y長さ
	UNs	back_col;			// 反転色
	} SW14_TBL_TDEF;

const	SW14_TBL_TDEF	SW14data_Pos_Tbl[10] = {
				{ 01, 417,  90, 63, 11},					//00[SW1]
				{ 01, 417,  90, 63, 11},					//01[SW1]
				{ 92, 417,  90, 63, 11},					//02[SW2]
				{183, 417,  90, 63, 11},					//03[SW3]
				{274, 417,  90, 63, 11},					//04[SW4]
				{457, 417, 183, 31, 11},					//05[SW56上]
				{457, 417, 183, 31, 11},					//06[SW56上]
				{457, 449,  91, 31, 11},					//07[SW5下]
				{549, 449,  91, 31, 11},					//08[SW6下]
				{365, 417,  91, 63, 11}						//09[SW7]	V01z(追加)
		};

void	SW16data_onset(UNs d_ptn, UNi sw_no)
{
	UNs	dx, dy;
	UNs	lx, ly, col;

	dx = SW14data_Pos_Tbl[sw_no].stat_xdot;				// Xｽﾀｰﾄ位置
	dy = SW14data_Pos_Tbl[sw_no].stat_ydot;				// Yｽﾀｰﾄ位置

	if ( d_ptn == 0 ) {
		col = GAMENn_HEAD.scr_col;						// 背景色
	}
	else {
		col = SW14data_Pos_Tbl[sw_no].back_col;			// 背景色
	}

	ly = SW14data_Pos_Tbl[sw_no].leng_ydot;				// Y長さ
	for ( ; ly>0; ly-- )
	{
		lx = SW14data_Pos_Tbl[sw_no].leng_xdot;			// X長さ
		for ( ; lx>0; lx-- )
		{
			if( LCD_VBASE[dy][dx] != 0 )					// dot色＝黒？（黒は文字色と決めうち、黒以外を背景色とする）
			{
				LCD_VBASE[dy][dx] = col;				// 背景色変更
			}
			LCD_VRAM[dy][dx] = LCD_VBASE[dy][dx];		// 念のためVBASEにｺﾋﾟｰ
			dx++;
		}
		dx = SW14data_Pos_Tbl[sw_no].stat_xdot;				// Xｽﾀｰﾄ位置
		dy = dy + 1;										// Yｽﾀｰﾄ位置
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SW56_upcara_disp
*  Function Name:	ＳＷ５６上段キャラクタをＳＷ領域へ格納
*  Input	:		SW56上段ｷｬﾗｸﾀ
*					表示位置のﾃｰﾌﾞﾙ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	SW56_upcara_disp(UNs cr_no, UNs p_no)
{
	UNi		s_no, up_flg;
	UNs		xy_no, *g_p, s_bf[3];


	if(cr_no == 00) {		//５６のキャラクタ番号が０の時は書かない
		return;
	}
	if(cr_no == 0xff) {		//５６のキャラクタ番号が０ＦＦＨの時はスペースを書く
		cr_no = 0;
	}
	xy_no = SW56_Up_Pos_Tbl[p_no];				//表示位置(画面の最初の位置)

	up_flg = 00;
	if(cr_no < 0x80 ) {
		s_no = 0;								//通常
	}
	else if(cr_no < 0x9f) {
		s_no = 1;								//カム名称対応
	}
	else if(cr_no < 0xb5) {
		s_no = 2;								//機能選択名称対応
	}
	else if(cr_no >= 0xc5) {
		s_no = 2;								//機能選択名称対応
	}
	else {
		up_flg = 0xff;							//機能選択の文字は１２ｷｬﾗ表示する
		s_no = 1;
	}

	switch(s_no) {
		case 0x0000:
			g_p = mess_adr_shr( 2 );						//メッセージ画面キャラクタアドレス検索
			g_p += cr_no*10;								//２０倍
			xy_no |= (12 << 10);							//文字数
			disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			break;

		case 0x0001:
			g_p = SW56_Cam_Name_Tbl[cr_no - 0x80];
			if(up_flg == 0x00 ){
				s_bf[0] = 0x2020;								//スペース書き込み
				s_bf[1] = 0x2020;								//スペース書き込み
				xy_no |= (1 << 10);								//文字数
				disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

				xy_no += 0x0010;							//次 桁
				xy_no &= 0x03ff;
				xy_no |= (8 << 10);							//文字数
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
				xy_no += 0x0080;							//次 桁

				xy_no &= 0x03ff;
				xy_no |= (3 << 10);							//文字数
				disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			else{											//機能選択の文字は１２ｷｬﾗ表示する
				xy_no |= (12 << 10);						//文字数
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
				xy_no += 0x00c0;							//次 桁
			}
			break;

		case 0x0002:			//この番号はベースのキャラクタのままとする？
			break;
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	SW56_upcara_disp(UNs cr_no, UNs p_no)
{
	UNi		s_no, up_flg;
	UNs		xy_no, *g_p, s_bf[8];
	UNs		x_dot, y_dot, len;
	UNl		adr;
	UNs		*hrom;

	if(cr_no == 00) {		//５６のキャラクタ番号が０の時は書かない
		return;
	}
	if(cr_no == 0xff) {		//５６のキャラクタ番号が０ＦＦＨの時はスペースを書く
		cr_no = 0;
	}
	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//表示位置(画面の最初の位置)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//表示位置(画面の最初の位置)

	up_flg = 00;
	if( (cr_no >= 256) && (cr_no <= 511) ) {	//V06c
		s_no = 0;								//通常
	}
	else if(cr_no < 0x80 ) {
		s_no = 0;								//通常
	}
	else if(cr_no < 0x9f) {
		s_no = 1;								//カム名称対応
	}
	else if(cr_no < 0xb5) {
		s_no = 2;								//機能選択名称対応
	}
	else if(cr_no >= 0xc5) {
		s_no = 2;								//機能選択名称対応
	}
	else {
		up_flg = 0xff;							//機能選択の文字は１２ｷｬﾗ表示する
		s_no = 1;
	}

	switch(s_no) {
		case 0x0000:
			if(cr_no==0)
			{
				s_bf[0] = 0x2020;								//スペース書き込み
				s_bf[1] = 0x2020;								//スペース書き込み
				s_bf[2] = 0x2020;								//スペース書き込み
				s_bf[3] = 0x2020;								//スペース書き込み
				s_bf[4] = 0x2020;								//スペース書き込み
				s_bf[5] = 0x2020;								//スペース書き込み
				hrom = &s_bf[0];
			}
			else
			{
				adr =  S56U_TABLE_ADR + ((cr_no-1) * CHAR_S56U_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
			}
			len = 12;
			disp_moji_s_color(
				len,					/* ｷｬﾗｸ長			*/
				x_dot,					/* 書出しX位置		*/
				y_dot,					/* 書出しY位置		*/
				0,						/* 文字色			*/
				GAMENn_HEAD.scr_col,	/* 背景色			*/
				0x0202,					/* 文字ｻｲｽﾞ			*/
				hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
				LCD_VBASE				/* 表示ﾒﾓﾘ			*/
				);
			disp_moji_s_rif(
				len,					/* ｷｬﾗｸ長			*/
				x_dot,					/* 書出しX位置		*/
				y_dot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
			break;

		case 0x0001:
			g_p = SW56_Cam_Name_Tbl[cr_no - 0x80];
			if(up_flg == 0x00 ){
				s_bf[0] = 0x2020;								//スペース書き込み
				len = 1;
				disp_moji_s_color(
					len,					/* ｷｬﾗｸ長			*/
					x_dot,					/* 書出しX位置		*/
					y_dot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
				len = 8;
				disp_moji_s_color(
					len,					/* ｷｬﾗｸ長			*/
					x_dot+(8*2*1),			/* 書出しX位置		*/
					y_dot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					g_p,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
				len = 9;
				disp_moji_s_rif(
					len,					/* ｷｬﾗｸ長			*/
					x_dot,					/* 書出しX位置		*/
					y_dot,					/* 書出しY位置		*/
					0x0202					/* 文字ｻｲｽﾞ			*/
					);
			}
			else{											//機能選択の文字は１２ｷｬﾗ表示する
				adr = CSR_TABLE_ADR + ((CSR_buff[CSR_TBL_POS_NOW].CARA_NO-1) * CHAR_CSR_SIZE);	// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				len = 12;
				disp_moji_s_color(
					len,					/* ｷｬﾗｸ長			*/
					x_dot,					/* 書出しX位置		*/
					y_dot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
				disp_moji_s_rif(
					len,					/* ｷｬﾗｸ長			*/
					x_dot,					/* 書出しX位置		*/
					y_dot,					/* 書出しY位置		*/
					0x0202					/* 文字ｻｲｽﾞ			*/
					);
			}
			break;

		case 0x0002:			//この番号はベースのキャラクタのままとする？
			break;
	}
	SW16data_onset(0xff, 5);			//V01y
}
#endif


/*
********************************************************************************
*  Module Name:		SW56_dncara_disp
*  Function Name:	SW56下段ｷｬﾗｸﾀをSW領域へ格納
*  Input	:		SW56下段ｷｬﾗｸﾀ
*					表示位置のﾃｰﾌﾞﾙ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	SW56_dncara_disp(UNs cr_no, UNs p_no)
{
	UNs		xy_no, *g_p, s_bf[3], i;

	if(cr_no == 00) {		//５６のキャラクタ番号が０の時は書かない
		return;
	}
	if(cr_no == 0xff) {		//５６のキャラクタ番号が０ＦＦＨの時はスペースを書く
		cr_no = 0;
	}
	xy_no = SW56_Up_Pos_Tbl[p_no];				//表示位置(画面の最初の位置)

//	if(cr_no < 60) {							//６０を越えたらアドレス変更
		g_p = mess_adr_shr( 7 );				//メッセージ画面キャラクタアドレス検索
//	}
//	else{
//		g_p = mess_adr_shr( 14 );				//メッセージ画面キャラクタアドレス検索
//		cr_no -= 60;
//	}
	g_p += cr_no*5;									//10倍
	xy_no |= (6 << 10);								//文字数
	disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	//汎用出力の汎用選択時入／切を削除
	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;			//SW56上段ｷｬﾗｸﾀ
	if((p_no == 7) && (0x80 <= i) && (i < 0x90)){	//ＳＷ５下？
		xy_no &= 0x03ff;
		g_p = Camcsr_Name_Tbl1[i - 0x80];
		if( 00 == (*g_p & BIT_0) ) {				//カム出力選択？
			s_bf[0] = 0x2020;								//スペース書き込み
			s_bf[1] = 0x2020;								//スペース書き込み
			s_bf[2] = 0x2020;								//スペース書き込み
			xy_no |= (6 << 10);								//文字数
			disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
		}
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	SW56_dncara_disp(UNs cr_no, UNs p_no)
{
	UNs		s_bf[4];
	UNs		x_dot, y_dot;
	UNl		adr;
	UNs		*hrom, len;
	UNs		*cam_p, bit;

	if(cr_no == 00) {		//５６のキャラクタ番号が０の時は書かない
		return;
	}
	if(cr_no == 0xff) {		//５６のキャラクタ番号が０ＦＦＨの時はスペースを書く
		cr_no = 0;
	}

	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//表示位置(画面の最初の位置)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//表示位置(画面の最初の位置)
	if (cr_no != 0)
	{
		if (p_no == 8) {										//SW6文字
////			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//ロータリカム画面					2014/09/01
////				 (GAMEN_NO == 24) || (GAMEN_NO == 25) ||		//ロータリカム進角付画面
////				 (GAMEN_NO == 19) || (WINDOW_NO == 5) || 		//エジェクタ画面
////				 (WINDOW_NO == 19) )							//ミスフィード画面

////			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//ロータリカム画面					2016/03/24（生産設定winを独立）
////				 (GAMEN_NO == 24) || (GAMEN_NO == 25) ||		//ロータリカム進角付画面
////				 (GAMEN_NO == 19) ) 							//エジェクタ画面

			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//ロータリカム画面					2016/11/15（エジェクタ画面を独立）
				 (GAMEN_NO == 24) || (GAMEN_NO == 25) )		//ロータリカム進角付画面
			{
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//時間進角有効
						cr_no = 12;								//SW6の文字を「ｶﾑ/ﾀｲﾏ」の切替
					}
				}
////				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {		//2016/11/15（1/3独立）
				else if ( SV_FLG_CNT == 1 ) {
					if ( (GAMEN_NO == 21) || (GAMEN_NO == 24) ) {	//ロータリカム画面1
						cam_p = &SV_CAMNA0_C1;
					}
					else {
						cam_p = &SV_CAMNA8_C1;
					}
					cam_p += CSR_TBL_POS_NOW;
					if (*cam_p & BIT_0) {						//ユーザーカム
						if (GMN_PAR077 != 0) {					//繰り返し機能有効
							cr_no = 78;							//SW6の文字を「指定」の切替
						}
					}
				}
				else if ( SV_FLG_CNT == 3 ) {
					if (GMN_PAR077 != 0) {						//繰り返し機能有効
						cr_no = 78;								//SW6の文字を「指定」の切替
					}
				}
				else if ( SV_FLG_CNT == 4 ) {					//2016/11/15
					if (SEQ_022_SV & BIT_D) {					//カムタイマ仕様有効
						cr_no = 12;								//SW6の文字を「ｶﾑ/ﾀｲﾏ」の切替
					}
				}
			}
			else if ( GAMEN_NO == 19 ) {					//エジェクタ画面					2016/11/15
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//時間進角有効
						cr_no = 12;								//SW6の文字を「ｶﾑ/ﾀｲﾏ」の切替
					}
				}
				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
					if (GMN_PAR077 != 0) {						//繰り返し機能有効
						cr_no = 78;								//SW6の文字を「指定」の切替
					}
				}
			}
			else if ( (WINDOW_NO == 5) || (WINDOW_NO == 19) )	//生産設定							2016/03/24
			{
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//時間進角有効
						cr_no = 12;								//SW6の文字を「ｶﾑ/ﾀｲﾏ」の切替
					}
				}
				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
					if (GMN_PAR077 != 0) {						//繰り返し機能有効
						if (SEQ_PAR_107 & BIT_2) {				//生産数値設定有効
							cr_no = 78;							//SW6の文字を「指定」の切替
						}
					}
				}
			}
			else if ( (GAMEN_NO == 20) || (GAMEN_NO == 68) )	//ミスフィード画面					2014/09/08
			{
				if ( (CSR_TBL_POS_NOW == 0) || (CSR_TBL_POS_NOW == 2) ||
					 (CSR_TBL_POS_NOW == 4) || (CSR_TBL_POS_NOW == 6) ) {
					if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
						if (GMN_PAR077 != 0) {						//繰り返し機能有効
							cr_no = 78;								//SW6の文字を「指定」の切替
						}
					}
				}
			}
		}

		adr =  S56_TABLE_ADR + ((cr_no-1) * CHAR_S56_SIZE);	// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (UNs *)adr;
		hrom++;
		len = 5;
		disp_moji_s_color(
			len,					/* ｷｬﾗｸ長			*/
			x_dot,					/* 書出しX位置		*/
			y_dot,					/* 書出しY位置		*/
			0,						/* 文字色			*/
			GAMENn_HEAD.scr_col,	/* 背景色			*/
			0x0202, 				/* 文字ｻｲｽﾞ			*/
			hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE				/* 表示ﾒﾓﾘ			*/
			);
	}
	else
	{
		s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
		len = 5;
		disp_moji_s_color(
			len,					/* ｷｬﾗｸ長			*/
			x_dot,					/* 書出しX位置		*/
			y_dot,					/* 書出しY位置		*/
			0,						/* 文字色			*/
			GAMENn_HEAD.scr_col,	/* 背景色			*/
			0x0202, 				/* 文字ｻｲｽﾞ			*/
			&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE				/* 表示ﾒﾓﾘ			*/
			);
	}
}

void	SW56_dncara_disp_color(UNs cr_no, UNs p_no, UNs b_col)
{
	UNs		s_bf[4];
	UNs		x_dot, y_dot;
	UNl		adr;
	UNs		*hrom, len;

	if(cr_no == 00) {		//５６のキャラクタ番号が０の時は書かない
		return;
	}
	if(cr_no == 0xff) {		//５６のキャラクタ番号が０ＦＦＨの時はスペースを書く
		cr_no = 0;
	}

	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//表示位置(画面の最初の位置)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//表示位置(画面の最初の位置)
	if (cr_no != 0)
	{
		adr =  S56_TABLE_ADR + ((cr_no-1) * CHAR_S56_SIZE);	// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
		hrom = (UNs *)adr;
		hrom++;
		len = 5;
		disp_moji_s_color(
			len,					/* ｷｬﾗｸ長			*/
			x_dot,					/* 書出しX位置		*/
			y_dot,					/* 書出しY位置		*/
			0,						/* 文字色			*/
			b_col,					/* 背景色			*/
			0x0202, 				/* 文字ｻｲｽﾞ			*/
			hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE				/* 表示ﾒﾓﾘ			*/
			);
	}
	else
	{
		s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
		len = 5;
		disp_moji_s_color(
			len,					/* ｷｬﾗｸ長			*/
			x_dot,					/* 書出しX位置		*/
			y_dot,					/* 書出しY位置		*/
			0,						/* 文字色			*/
			GAMENn_HEAD.scr_col,	/* 背景色			*/
			0x0202, 				/* 文字ｻｲｽﾞ			*/
			&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE				/* 表示ﾒﾓﾘ			*/
			);
	}
}
#endif

/*
********************************************************************************
*  Module Name:		SW56dn_clear
*  Function Name:	SWｷｬﾗｸﾀのﾃﾞｰﾀﾊﾟｰﾀｰﾝｸﾘｱ
*  Input	:		表示位置のﾃｰﾌﾞﾙ番号-1
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-14
********************************************************************************
*/
void	SW56dn_clear(UNs p_no)
{
	if(p_no != 00){
		SW16data_onset(0x00, p_no + 1);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
	}
}



/*** END ***/
