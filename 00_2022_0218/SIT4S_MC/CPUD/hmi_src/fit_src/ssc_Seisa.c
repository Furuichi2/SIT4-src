/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			生産の操作メイン処理													*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-06-04
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//参照変数定義

/* 外部参照関数定義 -------------------------------------------------- */
extern	void	GRAPH_INIT(void);				//グラフ描画初期処理
extern	void	GRAPH_DISP(void);				//グラフ描画処理

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		GMN_PAR003;						//連寸一行程時の目標角度上限 /* V01e */
extern	UNs		GMN_PAR021;						//振子ﾓｰｼｮﾝ設定制限		/* V06m */
extern	UNs		Key_Data_WK[4];					//V06a
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR077;						//繰り返し回数上限								2014/09/08
extern	UNb		LCD_VMON2[6*16*2][PanelWidth];	//2015/01/15
extern	UNs		GMN_PAR083;						//戻り行程速度下限値							2015/07/03

/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	dsp_Seisan(void);						//生産の管理

void	Seisan_sel(void);						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)

void	sw34_gamen_01(UNs);						//生産[基本]のSW3･4の処理
void	sw56_gamen_01(UNs);						//生産[基本]のSW5･6の処理
void	sw56_window_02(UNs);					//生産[輝度設定]のSW5･6の処理
void	kido_data_set(void);					//輝度表示 & データ作成

//void	mmon_taiki_chg(void);					//待機角入力変更
void	mmon_kaiten_chg(void);					//回転方式による設定値 切換え
void	mmon_sv_chg(UNs);						//角度&位置の設定値変更
void	mmon_tchk_disp(UNi);					//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
void	mmon_sel_chk(void);						//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
void	mmon_trans_get(void);					//回転方式によるﾃﾞｰﾀの取得
void	mmon_trans_put(void);					//回転方式によるﾃﾞｰﾀの格納
void	mmon_spd_in(void);						//速度リミット値を入力
void	mmon_agl_in(void);						//角度リミット値を入力

UNl		cnv_mi_mi_sur(UNl);						//単位切替(mm/INCH→mm/INCH)
UNl		cnv_mi_mi(UNl);							//単位切替(mm/INCH→mm/INCH)
UNl		cnv_mm_inch(UNl, UNi);					//単位切替(mm→mm/INCH)
UNl		cnv_inch_mm(UNl, UNi);					//単位切替(mm/INCH→mm)

void	SEI_csr_ichk(void);						//生産カーソル位置初期化
void	SEI_csr_mng(void);						//生産[基本]の専用　カーソル移動管理

void	mmon_deg_chg_uphold1(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt);
void	mmon_deg_chg_uphold2(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt);

void	KJ_CHK_MEM_CLR(void);
void	EPM_MEM_CLR(void);

void	SEI_Worker_GET(void);					//生産管理データ取得		V06c
void	SEI_Worker_SET(void);					//生産管理データ登録		V06c
void	SEI_Worker_STP(void);					//生産管理作業終了			V06c

void	FURIKO_SW_del(void);					//振子SWの表示／非表示		V06p
void	FURIKO_SW_chk(void);					//振子SWの表示／非表示		V06p

void	mmon_f_off(UNs t_no);					//一定速度設定のクリア		2014/09/25

void	mmon_pos_kaj_chg(UNs no);				//下限／荷重目標切換え		2015/01/15


/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		dsp_Seisan
*  Function Name:	生産の管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-04
********************************************************************************
*/
void	dsp_Seisan(void)
{
	UNs	*bf_p, i, j;
	UNs	bit;

	switch(disp_stg_sel) {

		case E_sstg_init:		//生産[基本]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							CAR_mkssi_set();					//単位切換  V01u
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3
							sw34_gamen_01(KEY_DATA_CODE);		//生産[基本]のSW3･4の処理
							break;
						case E_key_sw4:			//key code SW4
							if( (SEQ_016_SV & BIT_12) || (SEQ_016_SV & BIT_14) ){	//ﾛｯﾄｶｳﾝﾀ1/2の非表示
								sw34_gamen_01(KEY_DATA_CODE);	//生産[基本]のSW3･4の処理
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW3
							sw34_gamen_01(KEY_DATA_CODE);		//生産[基本]のSW3･4の処理
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_gamen_01(KEY_DATA_CODE);				//生産[基本]のSW5･6の処理
					break;
			}
			break;

		case E_sstg_set1:		//生産[生産設定1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(MIS_GAMEN_NON != 0xff){
								disp_stg_sel = E_sstg_set2;			//生産[生産設定2]へ
								WINDOW_NO = 19;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
							disp_stg_sel = E_sstg_koud;			//生産[輝度設定]へ
							WINDOW_NO = 2;
							WIN_gamen_disp();					//ウインドウ画面表示
#else
							if (SEQ_PAR_113 & BIT_9) { 			//仕様設定No.135「KOMTRAX」& 機能選択1「型ﾃﾞｰﾀ管理」	V06c
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
								WINDOW_NO = 23;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
#endif
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ

							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//行程設定箇所				2014/09/08
								 (GMN_PAR077 != 0) ) {								//繰り返し機能有り

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON行程
									bit = cBIT0;
									SV_EJECAM_ONR |= (bit << CSR_TBL_POS_NOW);
								}
								else {											//OFF行程
									bit = cBIT0;
									SV_EJECAM_OFR |= (bit << CSR_TBL_POS_NOW);
								}
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
								KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
								SW16data_onset(0xff, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							else {
		 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

								SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_set2:		//生産[生産設定2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_sstg_set1;			//生産[生産設定1]へ
								WINDOW_NO = 5;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
							disp_stg_sel = E_sstg_koud;			//生産[輝度設定]へ
							WINDOW_NO = 2;
							WIN_gamen_disp();					//ウインドウ画面表示
#else
							if (SEQ_PAR_113 & BIT_9) { 			//仕様設定No.135「KOMTRAX」& 機能選択1「型ﾃﾞｰﾀ管理」	V06e
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
								WINDOW_NO = 23;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
#endif
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw5:			//key code SW5
							SW_FLG_CNT = 1;
							SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

							SWchg_ent();						//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//行程設定箇所				2014/09/08
								 (GMN_PAR077 != 0) ) {								//繰り返し機能有り

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON行程
									bit = cBIT0;
									SV_MISCAM_ONR |= (bit << CSR_TBL_POS_NOW);
								}
								else {											//OFF行程
									bit = cBIT0;
									SV_MISCAM_OFR |= (bit << CSR_TBL_POS_NOW);
								}
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
								KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
								SW16data_onset(0xff, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							else {
								SW_FLG_CNT = 2;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

								SWchg_ent();						//SW CHG データ ENT
								KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ

								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_koud:		//生産[輝度設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode（なし）
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_window_02(KEY_DATA_CODE);		//生産[輝度設定]のSW5･6の処理
					break;
			}
			break;

		case E_sstg_gaid:		//生産[ガイダンス表示]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode（なし）
//V01v				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode	//V01v
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_schk;			//生産[シーケンスチェック]へ
							WINDOW_NO = 4;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
						case E_key_sw4:			//key code SW4（なし）
							break;
						case E_key_sw5:			//key code SW5	//V01v（追加）
//2014/09/02
////							disp_stg_sel = E_sstg_samp;			//生産[サンプリング]へ
////							if ( SEQ_024_SV & BIT_7 ) {			//仕様設定136	簡易見える化		V06l
////								GAMEN_NO = 67;					//簡易見える化 有り
////							}
////							else {
////								GAMEN_NO = 105;					//簡易見える化 無し
////							}
////							GAMEN_disp();						//画面表示
							break;

						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_samp;			//生産[サンプリング]へ
							if ( SEQ_024_SV & BIT_7 ) {			//仕様設定136	簡易見える化		V06l
								GAMEN_NO = 67;					//簡易見える化 有り
							}
							else {
								GAMEN_NO = 105;					//簡易見える化 無し
							}
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw6:			//key code SW6	//V01v（追加）
//2014/09/02							SEQ_PAR_056 |= BIT_12;					//ｻﾝﾌﾟﾘﾝｸﾞｽﾀｰﾄSW＝ON
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6_down:	//key code SW6(立下り)	//V01v（追加）
//2014/09/02							SEQ_PAR_056 &= ~BIT_12;					//ｻﾝﾌﾟﾘﾝｸﾞｽﾀｰﾄSW＝OFF
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_schk:		//生産[シーケンスチェック]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;
						case E_key_sw3:			//key code SW3（なし）
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
												// デバッグ画面ＭＡＫＥ shima
						case E_key_sw6:			//key code SW6
							if(SEQ_025_SV & BIT_14) {
								disp_stg_sel = E_sstg_deb;			//生産[デバッグ]へ
								GAMEN_NO = 70;
								GAMEN_disp();						//画面表示
							}
							break;
					}
					break;
			}
			break;

		case E_sstg_deb:		//生産[デバッグ]shima
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5:			//key code SW5	// V05i
//V05j							KJ_CHK_MEM_CLR();
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_sstg_his;			//生産[異常履歴]へ
							GAMEN_NO = 69;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_sstg_his:		//生産[異常履歴]shima
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_sstg_mmon:		//生産[モーションモニタ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//設定値の確定
					mmon_sv_chg(i);								//角度&位置の設定値変更
					mmon_tchk_disp(0x00);						//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					mmon_f_off(j);								//一定速度設定ｸﾘｱ				2014/09/25
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4（V01w(INS)）
							if( (SEQ_050_SV & BIT_1) == 0) {		//反転以外？		2014/08/20
								disp_stg_sel = E_sstg_hos;			//生産[補正モニタ]へ
								WINDOW_NO = 20;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							break;

						case E_key_sw5:			//key code SW5
							if( SEQ_PAR_107 & BIT_2 ) {			//機能選択3(生産数値設定　1:有)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWﾃｰﾌﾞﾙ個数
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
									SWchg_ent();								//SW CHG データ ENT
									mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
								}
								SEI_test_out_sw5();								//生産設定ﾃｽﾄ出力処理(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示

							if( SEQ_PAR_107 & BIT_2 ) {			//機能選択3(生産数値設定　1:有)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//ｶｰｿﾙ認識番号内の移動順位
											bf_p = SW_buff[j].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//ｶｰｿﾙ認識番号内の移動順位
												SW_TBL_POS_NOW = j;					//ＳＷデータ検索終了
												break;
											}
										}
									}
									FURIKO_SW_del();								//下往復（振子）の非表示セット		//V06p
									SWchg_move_ent();								//SW CHGの移動 ﾃﾞｰﾀENT
									SV0_MOT_FIX = 0;								//一定速度ブラグクリア			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//回転方式による設定値 切換え
									FURIKO_SW_chk();								//下往復（振子）の非表示セット		//V06p
//2014/08/20 再描画しちゃえ！
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6下段ｷｬﾗｸﾀ
										//停止の「V」入力
										SWchg_mmon_ent();								//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
										mmon_trans_put();								//回転方式によるﾃﾞｰﾀの格納
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 99) {	//SW56upｷｬﾗ＝速度＝ｶｰｿﾙは速度		V06p
										//速度のﾘﾐｯﾄ値入力
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 97) {	//SW56upｷｬﾗ＝速度＝ｶｰｿﾙは速度		V06p
										//角度のﾘﾐｯﾄ値入力
										mmon_agl_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6下段ｷｬﾗｸﾀ目標値		2015/01/15
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//下限／荷重目標切換え
									}
								}
								/* V00m */
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
			 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
								}
							}
							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57) {
			 					SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//仕様設定No.140
								disp_stg_sel = E_sstg_epm;			//データ設定[電力モニタ]へ
								GAMEN_NO = 102;
								GAMEN_disp();						//画面表示
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(立下り)
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		/* V01d */
		case E_sstg_mmon2:		//生産[モーションモニタ6～10]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//設定値の確定
					mmon_sv_chg(i);								//角度&位置の設定値変更
					mmon_tchk_disp(0x00);						//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					mmon_f_off(j);								//一定速度設定ｸﾘｱ				2014/09/25
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4（V01w(INS)）
							if( (SEQ_050_SV & BIT_1) == 0) {		//反転以外？		2014/08/20
								disp_stg_sel = E_sstg_hos;			//生産[補正モニタ]へ
								WINDOW_NO = 20;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							break;

						case E_key_sw5:			//key code SW5
							if( SEQ_PAR_107 & BIT_2 ) {			//機能選択3(生産数値設定　1:有)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWﾃｰﾌﾞﾙ個数
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
									SWchg_ent();								//SW CHG データ ENT
									mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
								}
								SEI_test_out_sw5();								//生産設定ﾃｽﾄ出力処理(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示

							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 58) {
		 						SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
							}
							break;

						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示

							if( SEQ_PAR_107 & BIT_2 ) {			//機能選択3(生産数値設定　1:有)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//ｶｰｿﾙ認識番号内の移動順位
											bf_p = SW_buff[j].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//ｶｰｿﾙ認識番号内の移動順位
												SW_TBL_POS_NOW = j;					//ＳＷデータ検索終了
												break;
											}
										}
									}
									FURIKO_SW_del();								//下往復（振子）の非表示セット		//V06p
									SWchg_move_ent();								//SW CHGの移動 ﾃﾞｰﾀENT
									SV0_MOT_FIX = 0;								//一定速度ブラグクリア			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//回転方式による設定値 切換え
									FURIKO_SW_chk();								//下往復（振子）の非表示セット		//V06p
//2014/08/20 再描画しちゃえ！
									disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
									GAMEN_NO = 3;
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6下段ｷｬﾗｸﾀ
										//停止の「V」入力
										SWchg_mmon_ent();								//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
										mmon_trans_put();								//回転方式によるﾃﾞｰﾀの格納
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 99) {	//SW56upｷｬﾗ＝速度＝ｶｰｿﾙは速度		V06p
										//速度のﾘﾐｯﾄ値入力
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 97) {	//SW56upｷｬﾗ＝速度＝ｶｰｿﾙは速度		V06p
										//角度のﾘﾐｯﾄ値入力
										mmon_agl_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6下段ｷｬﾗｸﾀ目標値		2015/01/15
//2015/04/10										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//下限／荷重目標切換え
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97+5);	//下限／荷重目標切換え
									}
								}
								/* V00m */
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
			 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
								}
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//仕様設定No.140
								disp_stg_sel = E_sstg_epm;			//データ設定[電力モニタ]へ
								GAMEN_NO = 102;
								GAMEN_disp();						//画面表示
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(立下り)
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_mcg:		//生産[モーショングラフ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3（なし）
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_024_SV & BIT_7) {
								disp_stg_sel = E_sstg_pvsmp;		//生産[モーションサンプリング表示]へ	//V05o(追加)
								GAMEN_NO = 9;
								GAMEN_disp();						//画面表示
								Dsp_Pvgraph_INIT();
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							if (SEQ_024_SV & BIT_7) {
								disp_stg_sel = E_sstg_pvtrd;		//生産[モーショントレンド表示]へ		//V05o(追加)
								GAMEN_NO = 10;
								SV_WAVE_PAGE = 0;					//V05o_a
								GAMEN_disp();						//画面表示
								Dsp_Pvgraph_INIT();
							}
							break;
#endif
					}
					break;
			}
			break;

		case E_sstg_samp:		//生産[サンプリング]	//V01v(追加)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode（なし）
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_trnd;			//生産[トレンド]へ			//V01z(INS)
							if ( SEQ_024_SV & BIT_7 ) {			//仕様設定136	簡易見える化		V06l
								GAMEN_NO = 66;					//簡易見える化 有り
							}
							else {
								GAMEN_NO = 104;					//簡易見える化 無し
							}
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw4:			//key code SW4
							break;
						case E_key_sw5:			//key code SW5
//V01z							if(CSR_FLG_CNT>2) {
//V05o							if(CSR_FLG_CNT<=4) {

							if(GAMEN_NO == 67) {					//V06l
								//画面No. 67  ｻﾝﾌﾟﾘﾝｸﾞ設定画面  SIT見える化設定有り
//2014/09/02
////								if( (CSR_FLG_CNT==1) ||
////									(CSR_FLG_CNT==2) ||
////									(CSR_FLG_CNT==3) ||
////									(CSR_FLG_CNT==4) ||
////									(CSR_FLG_CNT==6) )
								if( (CSR_FLG_CNT==1) ||
									(CSR_FLG_CNT==2) ||
									(CSR_FLG_CNT==3) ||
									(CSR_FLG_CNT==5) ||
									(CSR_FLG_CNT==7) )
								{
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									SWchg_ent();							//SW CHG データ ENT
									SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								}
							}
							else {
								//画面No.105  ｻﾝﾌﾟﾘﾝｸﾞ設定画面  SIT見える化設定無し
								if(CSR_FLG_CNT<=4) {
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									SWchg_ent();							//SW CHG データ ENT
									SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								}
							}

							break;
						case E_key_sw6:			//key code SW6
//V01z							if(CSR_FLG_CNT<3) {
//////								SW_FLG_CNT = 1;
//////							}
//////							else {
//////								SW_FLG_CNT = 2;
//////							}
//V05o							if( (CSR_FLG_CNT>=2) && (CSR_FLG_CNT<=4) ) {

							if(GAMEN_NO == 67) {					//V06l
								//画面No. 67  ｻﾝﾌﾟﾘﾝｸﾞ設定画面  SIT見える化設定有り
//2014/09/02
////								if( (CSR_FLG_CNT==3) ||
////									(CSR_FLG_CNT==4) ||
////									(CSR_FLG_CNT==6) )
								if( (CSR_FLG_CNT==3) ||
									(CSR_FLG_CNT==5) ||
									(CSR_FLG_CNT==7) )
								{
									SW_FLG_CNT = 2;
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									SWchg_ent();							//SW CHG データ ENT
									SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								}
//2014/09/02
////								else if( (CSR_FLG_CNT==5) ||
////										 (CSR_FLG_CNT==7) )
								else if( (CSR_FLG_CNT==4) ||
										 (CSR_FLG_CNT==6) ||
										 (CSR_FLG_CNT==8) )
								{
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									SWchg_ent();							//SW CHG データ ENT
									SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								}
							}
							else {
								//画面No.105  ｻﾝﾌﾟﾘﾝｸﾞ設定画面  SIT見える化設定無し
								if( (CSR_FLG_CNT>=2) && (CSR_FLG_CNT<=4) ) {
									SW_FLG_CNT = 2;
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									SWchg_ent();							//SW CHG データ ENT
									SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								}
							}

							break;
						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_trnd:		//生産[トレンド]	//V01z(追加)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode（なし）
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							disp_stg_sel = E_sstg_gaid;			//生産[ガイダンス表示]へ
							WINDOW_NO = 3;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_samp;			//生産[サンプリング]へ
							if ( SEQ_024_SV & BIT_7 ) {			//仕様設定136	簡易見える化		V06l
								GAMEN_NO = 67;					//簡易見える化 有り
							}
							else {
								GAMEN_NO = 105;					//簡易見える化 無し
							}
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							break;
						case E_key_sw5:			//key code SW5
							if(CSR_FLG_CNT<=1) {
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
								SWchg_ent();							//SW CHG データ ENT
								SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;
						case E_key_sw6:			//key code SW6
							if(CSR_FLG_CNT<=1) {
								SW_FLG_CNT = 2;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
								SWchg_ent();							//SW CHG データ ENT
								SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							else if(CSR_FLG_CNT<=3) {									//V05o(INS)
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
								SWchg_ent();							//SW CHG データ ENT
								SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}

							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB != 0) {								//2014/03/17
		 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
								SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							}
							break;
						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_hos:		//生産[補正モニタ]	//V01w(追加)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					Key_Ent_sv();								//設定値の確定
//2017/11/09
////					mmon_sv_chg(i);								//角度&位置の設定値変更
////					mmon_tchk_disp(0x00);						//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示

					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw5:			//key code SW5
//2017/11/08
							if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWﾃｰﾌﾞﾙ個数
								CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								SWchg_ent();								//SW CHG データ ENT
								mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
							}
	 						SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)

							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
	 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//仕様設定No.140
								disp_stg_sel = E_sstg_epm;			//データ設定[電力モニタ]へ
								GAMEN_NO = 102;
								GAMEN_disp();						//画面表示
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(立下り)
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_pvsmp:		//生産[モーションサンプリング表示]	//V05o(追加)

			Dsp_PvSamp_Wave();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3（なし）
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4（なし）
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_pvtrd;		//生産[モーショントレンド表示]へ		//V05o(追加)
							GAMEN_NO = 10;
							SV_WAVE_PAGE = 0;					//V05o_a
							GAMEN_disp();						//画面表示
							Dsp_Pvgraph_INIT();
							break;
#endif

						case E_key_sw6:			//key code SW6_SUB		//V06g  2011/07/28
							if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 257) {			//V06g 2011/07/28
	 							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
								SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							}
							break;

						case E_key_sw6_down:	//key code SW6(立下り)	//V06g  2011/07/28
							if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 257) {			//V06g 2011/07/28
								SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							}
							break;

					}
					break;
			}
			break;

		case E_sstg_pvtrd:		//生産[モーショントレンド表示]		//V05o(追加)

			Dsp_PvTrnd_Wave();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3（なし）
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4（なし）
							disp_stg_sel = E_sstg_pvsmp;		//生産[モーションサンプリング表示]へ
							GAMEN_NO = 9;
							GAMEN_disp();						//画面表示
							Dsp_Pvgraph_INIT();
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif
					}
					break;
			}
			break;

		case E_sstg_epm:		//生産[電力モニタ]		V06

			Dsp_EPM_GRAPH();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					if (CSR_FLG_CNT == 1)
					{
						i = EPM_TOTAL_INF;
						if (i == BIT_0)				i = BIT_1;
						else if (i == BIT_1)		i = BIT_2;
						else if (i == BIT_2)		i = BIT_0;
						EPM_TOTAL_INF = i;
						EPM_GAMEN_RIF = 1;							//再描画
					}
					else if (CSR_FLG_CNT == 4)
					{
						EPM_CLR_TIM = 1000;						//5sec
						EPM_CLR_FLG = 1;
					}
					else
					{
						Key_Ent_sv();								//設定値の確定
					}

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
							GAMEN_NO = 3;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//生産[モーショングラフ]へ
							GAMEN_NO = 4;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;

						case E_key_sw4:			//key code SW4（V01w(INS)）
							if( (SEQ_050_SV & BIT_1) == 0) {		//反転以外？		2014/08/20
								disp_stg_sel = E_sstg_hos;			//生産[補正モニタ]へ
								WINDOW_NO = 20;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif

					}
					break;
			}

			if ( (CSR_FLG_CNT == 4) && (Key_Data_WK[0] & BIT_2 ) )			//V06a
			{
				if ( (EPM_CLR_TIM == 0) && (EPM_CLR_FLG == 1) )
				{
					EPM_MEM_CLR();
					EPM_CLR_FLG = 0;
					EPM_GAMEN_RIF = 1;						//再描画
				}
			}
			else
			{
				EPM_CLR_FLG = 0;
			}

			break;

		case E_sstg_seidou:		//生産[制動試験WIN]		V06

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
						case E_key_sw5:			//key code SW5
							break;

						case E_key_sw6:			//key code SW6
							SEQ_PAR_058 |= BIT_4;
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							break;
#endif

						case E_key_sw5_down:	//key code SW5(立下り)
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SEQ_PAR_058 &= ~BIT_4;
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

					}
					break;
			}
			break;

		case E_sstg_seikan:		//生産[生産管理]	V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//作業者あり？
								disp_stg_sel = E_sstg_wkstr0;		//生産[作業開始0]へ
								WINDOW_NO = 51;
								WIN_gamen_disp();					//ウインドウ画面表示
							}
							else {
								disp_stg_sel = E_sstg_wkstr1;		//生産[作業開始1]へ
								WINDOW_NO = 52;
								WIN_gamen_disp();					//ウインドウ画面表示

								SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//今までの作業者ｺｰﾄﾞ退避
								SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//今までの注番ｺｰﾄﾞ退避
								SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//今までの計画数退避
							}
							break;

						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_wkstp0;		//生産[作業終了]へ
							WINDOW_NO = 58;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw5:			//key code SW5
							if (CSR_FLG_CNT == 2) {				//ｶｰｿﾙ＝不良数？
								if (SV_BAD_CNT) {
									SV_BAD_CNT--;
									FRAM_csum_set();			//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
								}
								SVdata_disp();					//設定値情報　表示
							}
							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							if (CSR_FLG_CNT == 2) {				//ｶｰｿﾙ＝不良数？
								if (SV_BAD_CNT<99999999) {		//V06d（LIMIT追加）
									SV_BAD_CNT++;
									FRAM_csum_set();			//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
									SVdata_disp();					//設定値情報　表示
								}
							}
							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr0:		//生産[作業開始0]	V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
							WINDOW_NO = 23;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							SEI_Worker_STP();					//生産管理作業終了

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_wkstr1;		//生産[作業開始1]へ
							WINDOW_NO = 52;
							WIN_gamen_disp();					//ウインドウ画面表示

							SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//今までの作業者ｺｰﾄﾞ退避
							SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//今までの注番ｺｰﾄﾞ退避
							SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//今までの計画数退避

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr1:		//生産[作業開始1]作業者ｺｰﾄﾞの入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();						//設定値の確定

					disp_stg_sel = E_sstg_wkstr2;		//生産[作業開始2]へ
					WINDOW_NO = 53;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//ｽｷｯﾌﾟ
							disp_stg_sel = E_sstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 54;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr2:		//生産[作業開始2]作業者ｺｰﾄﾞの確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_WORKER_COD = SV0_WORKER_COD_BAK;	//前に戻す

							disp_stg_sel = E_sstg_wkstr1;		//生産[作業開始1]へ
							WINDOW_NO = 52;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_sstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 54;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr3:		//生産[作業開始3]注番ｺｰﾄﾞの入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定

					disp_stg_sel = E_sstg_wkstr4;		//生産[作業開始4]へ
					WINDOW_NO = 55;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//ｽｷｯﾌﾟ
							disp_stg_sel = E_sstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 56;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr4:		//生産[作業開始4]注番ｺｰﾄﾞの確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_ORDER_COD = SV0_ORDER_COD_BAK;	//前に戻す

							disp_stg_sel = E_sstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 54;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_sstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 56;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr5:		//生産[作業開始5]計画数の入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定

					disp_stg_sel = E_sstg_wkstr6;		//生産[作業開始6]へ
					WINDOW_NO = 57;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//ｽｷｯﾌﾟ
							SEI_Worker_SET();					//作業ﾃﾞｰﾀ確定

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
							WINDOW_NO = 23;
							WIN_gamen_disp();					//ウインドウ画面表示


							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr6:		//生産[作業開始6]計画数の確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_PLAN_CNT = SV0_PLAN_CNT_BAK;		//前に戻す

							disp_stg_sel = E_sstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 56;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							SEI_Worker_SET();					//作業ﾃﾞｰﾀ確定

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
							WINDOW_NO = 23;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstp0:		//生産[作業終了]作業終了の確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//ウインドウ画面表示
							disp_stg_sel = E_sstg_init;			//生産[基本]へ
							GAMEN_NO = 1;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
							WINDOW_NO = 23;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//ｽｷｯﾌﾟ
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//作業者あり？
								SEI_Worker_STP();					//生産管理作業終了
    
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//生産[生産管理]へ
								WINDOW_NO = 23;
								WIN_gamen_disp();					//ウインドウ画面表示
    
								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();						//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;




	}
}


/*
********************************************************************************
*  Module Name:		Seisan_sel
*  Function Name:	生産設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ)
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-20
********************************************************************************
*/
void	Seisan_sel(void)
{

	EJE_GAMEN_NON = 0;						//エジェクタ 有
	if(00 == EJE_check()) {					//エジェクタ有無チェック
		EJE_GAMEN_NON = 0xff;				//エジェクタ 無
	}

	MIS_GAMEN_NON = 0;						//ミスフィード 有
	if(00 == MIS_check()){					//ミスフィード有無チェック
		MIS_GAMEN_NON = 0xff;				//ミスフィード 無
	}

	if(EJE_GAMEN_NON == 0){
		disp_stg_sel = E_sstg_set1;			//生産[生産設定1]へ
		WINDOW_NO = 5;
	}
	else if(MIS_GAMEN_NON == 0){
		disp_stg_sel = E_sstg_set2;			//生産[生産設定2]へ
		WINDOW_NO = 19;
	}
	else{
		disp_stg_sel = E_sstg_set1;			//生産[生産設定1]へ
		WINDOW_NO = 5;
	}
	WIN_gamen_disp();						//ウインドウ画面表示
}


/*
********************************************************************************
*  Module Name:		sw34_gamen_01
*  Function Name:	生産[基本]のSW3･4の処理
*  Input	:		ｷｰｺｰﾄﾞ(SW3/4)
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-13
********************************************************************************
*/
void	sw34_gamen_01(UNs k_code)
{

	if(k_code == E_key_sw3){	//SW3(トータルカウンタ)？
		if(SW14_ON1_FLG == 2){								//今トータルカウンタ１が押されていたか？
			if(SEQ_PAR_107 & BIT_4){						//機能選択5(ｶｳﾝﾄ値修正　1:有)
				SW14_ON1_FLG = 0x82;						//今トータルカウンタ１が押し

				COUNT_HOSEI_ADR = PV_buff[0].XY_POS;		//反転アドレスデータ待避
				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//カウンタ補正の実測値反転処理

				SW56_upcara_disp(6, 5);						//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(5, 7);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(6, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			}
			else{
				SW14_ON1_FLG = 0;							//データクリア

				SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
				CSR_disp_off();								//カーソル表示消去
//2014/09/02
////				SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
////				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
////				SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_upcara_disp(266, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(76, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(77, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

				SW16data_onset(0x00, 3);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			}
		}
		else if(SW14_ON1_FLG == 0x82){
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//今他のモード中？
			if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
				Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
			}
			SW14_ON1_FLG = 0;							//データクリア

			SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
			CSR_disp_off();								//カーソル表示消去
//2014/09/02
////			SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
////			SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
////			SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			SW56_upcara_disp(266, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
			SW56_dncara_disp(76, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			SW56_dncara_disp(77, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

			SW16data_onset(0x00, 3);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
		else{
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//今他のモード中？
			if(SW14_ON1_FLG & 0x80){						//今カウンタ補正機能中？
				if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
				}
			}
			SW14_ON1_FLG = 0x02;							//今トータルカウンタ１が押し

			CSR_FLG = 5;									//カーソル表示位置指定
			CSR_FLG_CNT = 1;								//カーソル番号セット
			SV_FLG_CNT = 0;									//設定値番号セット
			SW_FLG_CNT = 1;									//ＳＷ番号セット
			CSR_move(CSR_FLG, 00);							//カーソル移動(戻り値指定,移動OK)

			SW16data_onset(0xff, 3);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 4);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 9);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)	V01z(追加)
			SW16data_onset(0xff, 5);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
	}
	else if(k_code == E_key_sw4){	//SW4(ロットカウンタ1 / 2)
		switch(SW14_ON1_FLG) {
			default:
				if(SW14_ON1_FLG & 0x80){						//今カウンタ補正機能中？
					if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
					}
				}
				SW14_ON1_FLG = 0;
				SW14_ON1_FLG_BAK = 0;
			case 00:
//				if(SW14_ON1_FLG_BAK == 0){
					SW14_ON1_FLG = 0x03;							//今トータルカウンタ１が押し

					CSR_FLG = 5;									//カーソル表示位置指定
					CSR_FLG_CNT = 2;								//カーソル番号セット
					SV_FLG_CNT = 1;									//設定値番号セット
					SW_FLG_CNT = 1;									//ＳＷ番号セット
					CSR_move(CSR_FLG, 00);							//カーソル移動(戻り値指定,移動OK)

					SW16data_onset(0x00, 3);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0xff, 4);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0x00, 9);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)	V01z(追加)
					SW16data_onset(0xff, 5);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0xff, 6);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//				}
//				else{
//
//				}
				break;

			case 0x03:							//前回何かのキーが押されいたか？
			case 0x04:							//前回何かのキーが押されいたか？
				if(SEQ_PAR_107 & BIT_4){						//機能選択5(ｶｳﾝﾄ値修正　1:有)
					if(SW14_ON1_FLG == 0x03){
						SW14_ON1_FLG = 0x83;						//今ロットカウンタ１が押し
						COUNT_HOSEI_ADR = PV_buff[1].XY_POS;		//反転アドレスデータ待避
					}
					else{
						SW14_ON1_FLG = 0x84;						//今ロットカウンタ2が押し
						COUNT_HOSEI_ADR = PV_buff[2].XY_POS;		//反転アドレスデータ待避
					}
					Count_hosei_csr_on(COUNT_HOSEI_ADR);		//カウンタ補正の実測値反転処理

					SW56_upcara_disp(6, 5);						//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
					SW56_dncara_disp(5, 7);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
					SW56_dncara_disp(6, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				}
				else{
					SW14_ON1_FLG_BAK = SW14_ON1_FLG;
					SW14_ON1_FLG = 0;							//データクリア

					SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
					CSR_disp_off();								//カーソル表示消去
//2014/09/02
////					SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
////					SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
////					SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
					SW56_upcara_disp(266, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
					SW56_dncara_disp(76, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
					SW56_dncara_disp(77, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

					SW16data_onset(0x00, 4);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				}
				break;

			case 0x83:							//前回何かのキーが押されいたか？
			case 0x84:							//前回何かのキーが押されいたか？
//				SW56dn_clear(SW14_ON1_FLG & 0x7f);				//今他のモード中？
				if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
				}

				SW14_ON1_FLG_BAK = SW14_ON1_FLG;
				SW14_ON1_FLG = 0;							//データクリア

				SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
				CSR_disp_off();								//カーソル表示消去
//2024/09/02
////				SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
////				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
////				SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_upcara_disp(266, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(76, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(77, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

				SW16data_onset(0x00, 4);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
				break;
		}
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
	else if(k_code == E_key_sw7){	//SW7(オーバライド)		/* V01z */
		if(SW14_ON1_FLG == 5){	//ｵｰﾊﾞﾗｲﾄﾞ処理か？
			SW14_ON1_FLG = 0;							//データクリア

			SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
			CSR_disp_off();								//カーソル表示消去
//2014/09/02
////			SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
////			SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
////			SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			SW56_upcara_disp(266, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
			SW56_dncara_disp(76, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			SW56_dncara_disp(77, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

			SW16data_onset(0x00, 9);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
		else {
			if(SW14_ON1_FLG & 0x80){						//今カウンタ補正機能中？
				if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
				}
			}
			SW14_ON1_FLG = 0x05;							//今トータルカウンタ１が押し

			CSR_FLG = 5;									//カーソル表示位置指定
			CSR_FLG_CNT = 4;								//カーソル番号セット
			SV_FLG_CNT = 1;									//設定値番号セット
			SW_FLG_CNT = 1;									//ＳＷ番号セット
			CSR_move(CSR_FLG, 00);							//カーソル移動(戻り値指定,移動OK)

			SW16data_onset(0x00, 3);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 4);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 9);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
	}
#endif
	Under_grph();											//下段のグラフィックセット
	Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);		//行表示(LCD1)
	Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);		//行表示(LCD1)
	Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示(LCD2)
	Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示(LCD2)
}


//		if(SW14_ON1_FLG == 4){								//ロットカウンタ2が押されていたか？
///			if(SEQ_PAR_107 & BIT_4){						//機能選択5(ｶｳﾝﾄ値修正　1:有)
//				SW14_ON1_FLG = 0x84;						//今ロットカウンタ2が押し
//
//				COUNT_HOSEI_ADR = PV_buff[2].XY_POS;		//反転アドレスデータ待避
//				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//カウンタ補正の実測値反転処理
//
//				SW56_upcara_disp(6, 5);						//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(5, 7);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(6, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//			}
//			else{
//				SW14_ON1_FLG = 0;							//データクリア
//
//				SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
//				CSR_disp_off();								//カーソル表示消去
//				SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//
//				SW16data_onset(0x00, 4);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//				SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//				SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			}
//		}
//		else if(SW14_ON1_FLG == 0x84){						//ロットカウンタ2が押されていたか？
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//今他のモード中？
//			if(SW14_ON1_FLG & 0x80){						//今カウンタ補正機能中？
//				if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
//					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
//				}
//			}
//			SW14_ON1_FLG = 0x04;							//今トータルカウンタ2が押し
//
//			CSR_FLG = 5;									//カーソル表示位置指定
//			CSR_FLG_CNT = 3;								//カーソル番号セット
//			SV_FLG_CNT = 1;									//設定値番号セット
//			SW_FLG_CNT = 1;									//ＳＷ番号セット
//			CSR_move(CSR_FLG, 00);							//カーソル移動(戻り値指定,移動OK)
//
//			SW16data_onset(0x00, 3);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 4);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 5);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 6);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//		}
//		else if(SW14_ON1_FLG == 3){							//今ロットカウンタ１が押されていたか？
//			if(SEQ_PAR_107 & BIT_4){						//機能選択5(ｶｳﾝﾄ値修正　1:有)
//				SW14_ON1_FLG = 0x83;						//今ロットカウンタ１が押し
//
//				COUNT_HOSEI_ADR = PV_buff[1].XY_POS;		//反転アドレスデータ待避
//				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//カウンタ補正の実測値反転処理
//
//				SW56_upcara_disp(6, 5);						//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(5, 7);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(6, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//			}
//			else{
//				SW14_ON1_FLG = 0;							//データクリア
//
//				SVdata_disp_ent(SV_TBL_POS_NOW);			//設定途中の物は、元に戻す処理
//				CSR_disp_off();								//カーソル表示消去
//				SW56_upcara_disp(0xff, 5);					//SW56上段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//				SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//
//				SW16data_onset(0x00, 4);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//				SW16data_onset(0x00, 5);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//				SW16data_onset(0x00, 6);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			}
//		}
//		else{
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//今他のモード中？
//			if(SW14_ON1_FLG & 0x80){						//今カウンタ補正機能中？
//				if(COUNT_HOSEI_ADR != 00){					//反転アドレスデータ待避
//					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
//				}
//			}
//			SW14_ON1_FLG = 0x03;							//今トータルカウンタ１が押し
//
//			CSR_FLG = 5;									//カーソル表示位置指定
//			CSR_FLG_CNT = 2;								//カーソル番号セット
//			SV_FLG_CNT = 1;									//設定値番号セット
//			SW_FLG_CNT = 1;									//ＳＷ番号セット
//			CSR_move(CSR_FLG, 00);							//カーソル移動(戻り値指定,移動OK)
//
//			SW16data_onset(0x00, 3);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 4);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 5);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//			SW16data_onset(0xff, 6);						//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//		}


/*
********************************************************************************
*  Module Name:		sw56_gamen_01
*  Function Name:	生産[基本]のSW5･6の処理
*  Input	:		ｷｰｺｰﾄﾞ(SW5/6)
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-13
********************************************************************************
*/
void	sw56_gamen_01(UNs k_code)
{
	UNs		t_no;
	UNl		dat;

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//立下り?
		DANseq_sw56off(k_code);						//段取り用シーケンスＯＦＦ
		SEISAN_SW56_FLG = 0;

		SEQ_PAR_056 &= ~(cBIT12+cBIT15);			//2014/09/02

		return;
	}

	if(SW14_ON1_FLG == 2){							//トータルカウンタが押されていたか？
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG データ ENT
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
		}
		else{
			PV_TOTLC1_B3 = 0;						//トータルカウンタ１実測値クリア
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
		}
	}
	else if(SW14_ON1_FLG == 3){						//ロットカウンタが押されていたか？
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG データ ENT
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			if( 00 == (SEQ_032_SV & BIT_2)){
				SEQ_PAR_033 &= ~BIT_0;				//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
			}
		}
		else{
			PV_LOTCT1_B4 = 0;						//ロットカウンタ１実測値クリア
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			SEQ_PAR_033 &= ~BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
	}
	else if(SW14_ON1_FLG == 0x82){					//今トータルカウンタ（カウンタ補正）が押されていたか？
		if(k_code == E_key_sw5){					//SW5? 減算？
			if(PV_TOTLC1_B3 != 00){
				PV_TOTLC1_B3 --;					//トータルカウンタ１実測値減算
				KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
			}
		}
		else{
			PV_TOTLC1_B3 ++;						//トータルカウンタ１実測値増算
			KAT_DATCHG_FLG = 0xff;					//カウンタ値変更フラグ
			if(0x00989680 <= PV_TOTLC1_B3 ){
				PV_TOTLC1_B3 --;
			}
		}
	}
	else if(SW14_ON1_FLG == 0x83){					//今ロットカウンタ（カウンタ補正）が押されていたか？
		if(k_code == E_key_sw5){					//SW5? 減算？
			PV_LOTCT1_B4 --;						//ロットカウンタ１実測値減算
			KAT_DATCHG_FLG = 0xff;					//カウンタ値変更フラグ
			if(SV_PUR1SV_B4 <= PV_LOTCT1_B4){
				PV_LOTCT1_B4 = 0;
				KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
			}
		}
		else{
			PV_LOTCT1_B4 ++;						//ロットカウンタ１実測値増算
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			if(SV_PUR1SV_B4 <= PV_LOTCT1_B4){
				PV_LOTCT1_B4 = SV_PUR1SV_B4;
				KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
			}
		}
		ROTTO_chk();								//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
	}
	else if(SW14_ON1_FLG == 4){						//ロットカウンタが押されていたか？
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG データ ENT
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			if( 00 == (SEQ_032_SV & BIT_3)){
				SEQ_PAR_033 &= ~BIT_1;				//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
			}
		}
		else{
			PV_LOTCT2_B41 = 0;						//ロットカウンタ2実測値クリア
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			SEQ_PAR_033 &= ~BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
	}
	else if(SW14_ON1_FLG == 0x84){					//今ロットカウンタ（カウンタ補正）が押されていたか？
		if(k_code == E_key_sw5){					//SW5? 減算？
			PV_LOTCT2_B41 --;						//ロットカウンタ2実測値減算
			KAT_DATCHG_FLG = 0xff;					//カウンタ値変更フラグ
			if(SV_PUR2SV_B41 <= PV_LOTCT2_B41){
				PV_LOTCT2_B41 = 0;
				KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
			}
		}
		else{
			PV_LOTCT2_B41 ++;						//ロットカウンタ2実測値増算
			KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
			if(SV_PUR2SV_B41 <= PV_LOTCT2_B41){
				PV_LOTCT2_B41 = SV_PUR2SV_B41;
				KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
			}
		}
		ROTTO_chk();								//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
	}
	else if(SW14_ON1_FLG == 5){					//	V01w(INS)
		if(k_code == E_key_sw5){					//SW5?
			if ( (SV_OVERLIDE_COF-1) >= 1 ) {
				SV_OVERLIDE_COF--;
				dat = SV_OVERLIDE_COF;
				t_no = SV_TBL_POS_NOW;
				SVPV_data_disp(dat, &SV_buff[t_no], 0, 0);		//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
				SVSW_CHG_FLG |= 0x0004;
			}
		}
		else{
			if ( (SV_OVERLIDE_COF+1) <= 100 ) {
				SV_OVERLIDE_COF++;
				dat = SV_OVERLIDE_COF;
				t_no = SV_TBL_POS_NOW;
				SVPV_data_disp(dat, &SV_buff[t_no], 0, 0);		//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
				SVSW_CHG_FLG |= 0x0004;
			}
		}
	}
	else if(SW14_ON1_FLG == 0){						//2014/09/02
		if(k_code == E_key_sw5){					//SW5?
			SEQ_PAR_056 |= cBIT15;
		}
		else {
			SEQ_PAR_056 |= cBIT12;
		}
	}
	else{
		return;
	}

	FRAM_csum_set();								//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	SW16data_onset(0xff, k_code+2 );						//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
	Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示
	Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示

}


/*
********************************************************************************
*  Module Name:		sw56_window_02
*  Function Name:	生産[輝度設定]のSW5･6の処理
*  Input	:		ｷｰｺｰﾄﾞ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-05
********************************************************************************
*/
void	sw56_window_02(UNs k_code)
{

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//立下り?
		SW16data_onset(0x00, 7);						//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		SW16data_onset(0x00, 8);						//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
	}
	else{
		if(k_code == E_key_sw5){						//SW5?
			if(KIDO_FLG_SV != 0){
				KIDO_FLG_SV --;
			}
			SVdata_disp();								//設定値情報　表示
			SWchg_disp();								//ＳＷデータ情報　表示
			SW16data_onset(0xff, 7);					//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
		else{											//SW6
			KIDO_FLG_SV ++;

			SVdata_disp();								//設定値情報　表示
			SWchg_disp();								//ＳＷデータ情報　表示
			SW16data_onset(0xff, 8);					//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		}
		kido_data_set();								//輝度表示 & データ作成

		FRAM_csum_set();								//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	}
	Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
}


/*
********************************************************************************
*  Module Name:		kido_data_set
*  Function Name:	輝度表示 & データ作成
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-05
********************************************************************************
*/
void	kido_data_set(void)
{
	UNs	i,j;

	if(KIDO_FLG_SV > 15) {
		KIDO_FLG_SV = 15;
	}

	i = KIDO_FLG_SV + 1;
	for( j = 0 ; i > 0 ; i--){
		j <<= 1;
		j |= 0x0001;
	}
	KIDO_FLG_FLG = j;

	KIDO_FLG_PV = KIDO_FLG_SV + 1;

	Lcd_contrast_chage(KIDO_FLG_SV);				//LCD輝度設定
}


/*
********************************************************************************
*  Module Name:		mmon_kaiten_chg
*  Function Name:	回転方式による設定値 切換え
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-10-07
********************************************************************************
*/
void	mmon_kaiten_chg(void)
{
	UNl		long_bf;
	UNs		t_no;

	mmon_trans_get();								//回転方式によるﾃﾞｰﾀの取得

	if( SV_CNT == 00 ){
		return;
	}

	if( SEQ_050_SV & BIT_1 ){						//反転　？
		t_no = grpno_sv_srch(86);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(87);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(88);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(89);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(90);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(107);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(108);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(109);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(110);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(111);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 54;

		// 下限設定非表示  2014/08/20
		t_no = grpno_sv_srch(117);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ		下限
		SV_buff[t_no].SUB_NO |= BIT_F;				//非表示ｾｯﾄ
		CSR_buff[4].TOK_NO |= BIT_0;				//ｶｰｿﾙ非表示の設定
		PV_buff[3].SUB_NO |= BIT_F;					//単位表示の設定

		// 補正設定非表示  2014/08/20
		t_no = grpno_sv_srch(118);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ		補正
		SV_buff[t_no].SUB_NO |= BIT_F;				//非表示ｾｯﾄ
		CSR_buff[5].TOK_NO |= BIT_0;				//ｶｰｿﾙ非表示の設定
		SW_buff[4].SUB_NO |= BIT_F;					//ｽｲｯﾁ入/切 非表示の設定
		PV_buff[4].SUB_NO |= BIT_F;					//単位表示の設定
	}
	else{
		t_no = grpno_sv_srch(86);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
//V01j		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(87);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//V01d		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO &= 0x8000;				//間違えてｺﾒﾝﾄにしてしまったのを復活  V01h_b
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(88);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(89);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(90);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(107);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(108);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(109);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(110);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(111);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
		SV_buff[t_no].SUB_NO &= 0x8000;				//ｻﾌﾞﾙｰﾁﾝ番号
		SV_buff[t_no].SUB_NO |= 74;

		// 下限設定表示  2014/08/20
		t_no = grpno_sv_srch(117);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ		下限
		SV_buff[t_no].SUB_NO &= ~BIT_F;				//表示ｾｯﾄ
		CSR_buff[4].TOK_NO &= ~BIT_0;				//ｶｰｿﾙ表示の設定
		PV_buff[3].SUB_NO &= ~BIT_F;				//単位表示の設定

		// 補正設定表示  2014/08/20
		t_no = grpno_sv_srch(118);					//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ		補正
		SV_buff[t_no].SUB_NO &= ~BIT_F;				//表示ｾｯﾄ
		CSR_buff[5].TOK_NO &= ~BIT_0;				//ｶｰｿﾙ表示の設定
		SW_buff[4].SUB_NO &= ~BIT_F;				//ｽｲｯﾁ入/切 表示の設定
		PV_buff[4].SUB_NO &= ~BIT_F;				//単位表示の設定
	}

	grpno_sv_open(85);								//設定値情報ﾃｰﾌﾞﾙの表示 設定(待機角)
	grpno_sv_open(91);								//設定値情報ﾃｰﾌﾞﾙの表示 設定(待機位置)


	csrno_sv_open(2);								//設定値情報ﾃｰﾌﾞﾙの表示 設定(行程)	V06m
	CSR_opn_tokusyu(97, 92);						//1段目停止時間のｶｰｿﾙ表示		V06m
	CSR_opn_tokusyu(102, 99);						//戻り速度のｶｰｿﾙ表示			V06m


	mmon_tchk_disp(0xff);							//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示


	if( SEQ_050_SV & (BIT_0 | BIT_3) ){				//回転／上往復　？
		grpno_sv_cls(85);							//設定値情報ﾃｰﾌﾞﾙの非表示 設定(待機角)
		grpno_sv_cls(91);							//設定値情報ﾃｰﾌﾞﾙの非表示 設定(待機位置)
	}

	if (SEQ_050_SV & BIT_2) {						//V06m
		if (GMN_PAR021 == 1) {
			csrno_sv_cls(2);						//設定値情報ﾃｰﾌﾞﾙの非表示 設定(行程)
			CSR_cls_tokusyu(97, 92);				//1段目停止時間のｶｰｿﾙ非表示
			CSR_cls_tokusyu(102, 99);				//戻り速度のｶｰｿﾙ非表示
		}
	}

	mmon_trans_put();								//回転方式によるﾃﾞｰﾀの格納

}


/*
********************************************************************************
*  Module Name:		mmon_taiki_chg
*  Function Name:	待機角入力変更
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-30
********************************************************************************
*/
//void	mmon_taiki_chg(void)
//{
//	UNl		long_bf;
//	UNs		t_no;
//
//	if( SV_CNT == 00 ){
//		return;
//	}
//
//	if(SV_TAIKIKAKU_SRV != 0){
//		SV_TAIKIKAKU_SRV_BAK = SV_TAIKIKAKU_SRV;			//待機角の格納
//		SV_TAIKIPOS_SRV_BAK = SV_TAIKIPOS_SRV;				//待機位置の格納
//	}
//
//	if( SEQ_050_SV & (BIT_0 | BIT_3) ){						//回転　上往復　？
//
//		SV_TAIKIKAKU_SRV = 0;								//待機角 = 0
//		t_no = grpno_sv_srch(85);							//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//
//		long_bf = SV_TAIKIKAKU_SRV;							//待機角の表示
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
//
//		mmon_sv_chg(t_no);									//角度&位置の設定値変更（待機位置の表示）
//
//		grpno_sv_cls(85);									//設定値情報ﾃｰﾌﾞﾙの非表示 設定(待機角)
//		grpno_sv_cls(91);									//設定値情報ﾃｰﾌﾞﾙの非表示 設定(待機位置)
//	}
//	else {													//NO
//		grpno_sv_open(85);									//設定値情報ﾃｰﾌﾞﾙの表示 設定(待機角)
//		grpno_sv_open(91);									//設定値情報ﾃｰﾌﾞﾙの表示 設定(待機位置)
//
//		SV_TAIKIKAKU_SRV = SV_TAIKIKAKU_SRV_BAK;			//待機角の復元
//		t_no = grpno_sv_srch(85);							//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		long_bf = SV_TAIKIKAKU_SRV;							//待機角の表示
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
//
//		SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV_BAK;				//待機位置復元
//		t_no = grpno_sv_srch(91);							//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		long_bf = SV_TAIKIPOS_SRV;							//待機位置の表示
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
//	}
//
//	if( SEQ_050_SV & BIT_1 ){							//反転　？
//		t_no = grpno_sv_srch(86);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(87);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(88);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(89);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(90);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 54;
//	}
//	else{
//		t_no = grpno_sv_srch(86);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(87);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(88);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(89);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(90);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
//		SV_buff[t_no].SUB_NO &= 0x8000;					//ｻﾌﾞﾙｰﾁﾝ番号
//		SV_buff[t_no].SUB_NO |= 55;
//	}
//
//}


/*
********************************************************************************
*  Module Name:		mmon_sv_chg
*  Function Name:	角度&位置の設定値変更
*  Input	:		なし
*  Return	: 		なし
*  Note		:角度→位置の設定値変更、或は 位置→角度の設定値変更を行う。
*
*  履 歴	:FIT)田端		ON:2002-07-24
********************************************************************************
*/
void	mmon_sv_chg( UNs t_no )
{
	UNl		long_bf;
	UNs		i;

	if( SV_CNT == 00 ){
		return;
	}

	long_bf = 0;

	i = SV_buff[t_no].GRP_NO;											//ｸﾞﾙｰﾌﾟ番号
	switch( i ) {
		case 85:				//ﾓｰｼｮﾝ画面　待機角
			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
			}
			SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)

			long_bf = SV_TAIKIPOS_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			break;

		case 86:				//ﾓｰｼｮﾝ画面　目標角1
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_1DANPOS_SRV = DigRnaChange1(SV_1DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_1DANPOS_SRV = SV_1DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_1DANPOS_SRV	= cnv_mm_inch(SV_1DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_1DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_0)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_1DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold1(t_no, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
			break;

		case 87:				//ﾓｰｼｮﾝ画面　目標角2
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_2DANPOS_SRV = DigRnaChange1(SV_2DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_2DANPOS_SRV = SV_2DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_2DANPOS_SRV	= cnv_mm_inch(SV_2DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_2DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_1)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_2DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold1(t_no, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
			break;

		case 88:				//ﾓｰｼｮﾝ画面　目標角3
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_3DANPOS_SRV = DigRnaChange1(SV_3DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_3DANPOS_SRV = SV_3DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_3DANPOS_SRV	= cnv_mm_inch(SV_3DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_3DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_2)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_3DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold1(t_no, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
			break;

		case 89:				//ﾓｰｼｮﾝ画面　目標角4
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_4DANPOS_SRV = DigRnaChange1(SV_4DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_4DANPOS_SRV = SV_4DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_4DANPOS_SRV	= cnv_mm_inch(SV_4DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_4DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_3)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_4DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold1(t_no, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
			break;

		case 90:				//ﾓｰｼｮﾝ画面　目標角5
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_5DANPOS_SRV = DigRnaChange1(SV_5DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_5DANPOS_SRV = SV_5DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_5DANPOS_SRV	= cnv_mm_inch(SV_5DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_5DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_4)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_5DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold1(t_no, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
			break;

		/* V01d */
		case 107:				//ﾓｰｼｮﾝ画面　目標角6
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_6DANPOS_SRV = DigRnaChange1(SV_6DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_6DANPOS_SRV = SV_6DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_6DANPOS_SRV	= cnv_mm_inch(SV_6DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_6DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_5)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_6DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold2(t_no, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, 4);	/* V01d */
			break;

		/* V01d */
		case 108:				//ﾓｰｼｮﾝ画面　目標角7
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_7DANPOS_SRV = DigRnaChange1(SV_7DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_7DANPOS_SRV = SV_7DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_7DANPOS_SRV	= cnv_mm_inch(SV_7DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_7DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_6)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_7DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold2(t_no, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, 3);	/* V01d */
			break;

		/* V01d */
		case 109:				//ﾓｰｼｮﾝ画面　目標角8
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_8DANPOS_SRV = DigRnaChange1(SV_8DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_8DANPOS_SRV = SV_8DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_8DANPOS_SRV	= cnv_mm_inch(SV_8DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_8DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_7)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_8DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold2(t_no, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, 2);	/* V01d */
			break;

		/* V01d */
		case 110:				//ﾓｰｼｮﾝ画面　目標角9
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_9DANPOS_SRV = DigRnaChange1(SV_9DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_9DANPOS_SRV = SV_9DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_9DANPOS_SRV	= cnv_mm_inch(SV_9DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_9DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_8)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_9DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}

			mmon_deg_chg_uphold2(t_no, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, &SV_10DANDEG_SRV, &SV_10DANPOS_SRV, 1);	/* V01d */
			break;

		/* V01d */
		case 111:				//ﾓｰｼｮﾝ画面　目標角10
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_10DANPOS_SRV = DigRnaChange1(SV_10DANDEG_SRV);				//角度→mm変換

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//反転　？
					SV_10DANPOS_SRV = SV_10DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_10DANPOS_SRV	= cnv_mm_inch(SV_10DANPOS_SRV, 0);			//単位切替(mm→mm/INCH)
			}

//2015/01/15
////			long_bf = SV_10DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_9)==0) ) ) {		//反転で目標が下限の場合は表示	2014/03/12
				long_bf = SV_10DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
				SV_csr_set();							//設定値ｶｰｿﾙ表示
			}
			break;

		case 91:				//ﾓｰｼｮﾝ画面　待機位置
			long_bf = cnv_inch_mm(SV_TAIKIPOS_SRV, 0);						//単位切替(mm/INCH→mm)

//koma 2014-08-11			/* V00m */
//koma 2014-08-11			if(SEQ_050_SV & BIT_1) {		//反転　？
//koma 2014-08-11				long_bf = long_bf + SV_NEG_OFS_LNG;
//koma 2014-08-11			}
//koma 2014-08-11			SV_TAIKIKAKU_SRV = RnaDigChange1(SV_TAIKIKAKU_SRV, long_bf);	//mm変換→角度

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
				SV_TAIKIKAKU_SRV = RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//2014-08-11 koma mm変換→角度
														//SV_DNAREA_JUDGはどんな時でも下降領域(右半球の設定)
														//
			}else{
				if(SEQ_050_SV & BIT_2) {//2014-08-19 ふりこ
					SV_TAIKIKAKU_SRV = RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm変換→角度[待機点は必ず右半球]
				}else{
					SV_TAIKIKAKU_SRV = RnaDigChange1(SV_TAIKIKAKU_SRV, long_bf);	//mm変換→角度
				}
			
			}

			long_bf = SV_TAIKIKAKU_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			break;

		case 92:				//ﾓｰｼｮﾝ画面　目標位置1
			long_bf = cnv_inch_mm(SV_1DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_1DANDEG_SRV = RnaDigChange1(SV_1DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_1DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold1(t_no-1, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
			break;

		case 93:				//ﾓｰｼｮﾝ画面　目標位置2
			long_bf = cnv_inch_mm(SV_2DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_2DANDEG_SRV = RnaDigChange1(SV_2DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_2DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold1(t_no-1, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
			break;

		case 94:				//ﾓｰｼｮﾝ画面　目標位置3
			long_bf = cnv_inch_mm(SV_3DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_3DANDEG_SRV = RnaDigChange1(SV_3DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_3DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold1(t_no-1, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
			break;

		case 95:				//ﾓｰｼｮﾝ画面　目標位置4
			long_bf = cnv_inch_mm(SV_4DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_4DANDEG_SRV = RnaDigChange1(SV_4DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_4DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold1(t_no-1, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
			break;

		case 96:				//ﾓｰｼｮﾝ画面　目標位置5
			long_bf = cnv_inch_mm(SV_5DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_5DANDEG_SRV = RnaDigChange1(SV_5DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_5DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold1(t_no-1, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
			break;

		/* V01d */
		case 112:				//ﾓｰｼｮﾝ画面　目標位置6
			long_bf = cnv_inch_mm(SV_6DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_6DANDEG_SRV = RnaDigChange1(SV_6DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_6DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold2(t_no-1, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, 4);	/* V01d */
			break;

		/* V01d */
		case 113:				//ﾓｰｼｮﾝ画面　目標位置7
			long_bf = cnv_inch_mm(SV_7DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_7DANDEG_SRV = RnaDigChange1(SV_7DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_7DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold2(t_no-1, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, 3);	/* V01d */
			break;

		/* V01d */
		case 114:				//ﾓｰｼｮﾝ画面　目標位置8
			long_bf = cnv_inch_mm(SV_8DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_8DANDEG_SRV = RnaDigChange1(SV_8DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_8DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold2(t_no-1, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, 2);	/* V01d */
			break;

		/* V01d */
		case 115:				//ﾓｰｼｮﾝ画面　目標位置9
			long_bf = cnv_inch_mm(SV_9DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_9DANDEG_SRV = RnaDigChange1(SV_9DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_9DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)

			mmon_deg_chg_uphold2(t_no-1, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, &SV_10DANDEG_SRV, &SV_10DANPOS_SRV, 1);	/* V01d */
			break;

		/* V01d */
		case 116:				//ﾓｰｼｮﾝ画面　目標位置10
			long_bf = cnv_inch_mm(SV_10DANPOS_SRV, 0);					//単位切替(mm/INCH→mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//反転　？
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_10DANDEG_SRV = RnaDigChange1(SV_10DANDEG_SRV, long_bf);	//mm変換→角度
			}

			long_bf = SV_10DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
			break;
	}
	MOTION_SV_CHG_CANCEL = 0;	/* V01d */
	SV_csr_set();											//設定値ｶｰｿﾙ表示		2014/04/15
}


/*
********************************************************************************
*  Module Name:		mmon_deg_chg_uphold1
*  Function Name:	ﾓｰｼｮﾝ1～5角度の上昇ﾎｰﾙﾄﾞ角度ﾁｪｯｸ＆表示
*  Input	:		
*  Return	: 		なし
*  Note		:
*
*  履 歴	: A.Shimamura		ON:2004-01-16
********************************************************************************
*/
void	mmon_deg_chg_uphold1(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt)
{
	UNl		long_bf1, long_bf2;
	UNs		i, b1;

//2016-04-16	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma

	{
//V01e		if(*nowdeg >= SV_UPHOLD_DIG)
		if(*nowdeg >= GMN_PAR003)
		{
			b1 = SV_DANSUU_SRV;
			if (b1 > 5)		b1 = 5;

			for(i=4; 0<cnt; cnt--,i+=4, nexdeg++, nexpos++)
			{
				if(*nexdeg < *nowdeg)
				{
					*nexdeg = *nowdeg;
					*nexpos = *nowpos;
					long_bf1 = *nexdeg;
					long_bf2 = *nexpos;
					if ( (10-cnt) < b1 )
					{
						SVPV_data_disp(long_bf1, &SV_buff[t_no+i], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
						SVPV_data_disp(long_bf2, &SV_buff[t_no+i+1], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
					}
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_deg_chg_uphold1
*  Function Name:	ﾓｰｼｮﾝ6～10角度の上昇ﾎｰﾙﾄﾞ角度ﾁｪｯｸ＆表示
*  Input	:		
*  Return	: 		なし
*  Note		:
*
*  履 歴	: A.Shimamura		ON:2004-01-16
********************************************************************************
*/
void	mmon_deg_chg_uphold2(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt)
{
	UNl		long_bf1, long_bf2;
	UNs		i, b1;

//2016-04-16	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
	{
//V01e		if(*nowdeg >= SV_UPHOLD_DIG)
		if(*nowdeg >= GMN_PAR003)
		{
			b1 = SV_DANSUU_SRV - 5;

			for(i=4; 0<cnt; cnt--,i+=4, nexdeg++, nexpos++)
			{
				if(*nexdeg < *nowdeg)
				{
					*nexdeg = *nowdeg;
					*nexpos = *nowpos;
					long_bf1 = *nexdeg;
					long_bf2 = *nexpos;
					if ( (5-cnt) < b1 )
					{
						SVPV_data_disp(long_bf1, &SV_buff[t_no+i], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
						SVPV_data_disp(long_bf2, &SV_buff[t_no+i+1], 0, 0x01);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽあり/正常表示)
					}
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_tchk_disp
*  Function Name:	ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
*  Input	:		ﾌﾗｸﾞ：0＝通常表示
*						  0≠強制表示
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-02
********************************************************************************
*/
#if 0	/* V01d */
const	UNs	mmon_tchk_tbl[6][4]={				//各工程の情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
			{ 97, 86, 92,  6},
			{ 97, 86, 92,  6},						//工程数 1
			{ 98, 87, 93,  7},						//工程数 2
			{ 99, 88, 94,  8},						//工程数 3
			{100, 89, 95,  9},						//工程数 4
			{101, 90, 96, 10}						//工程数 5
		};

void	mmon_tchk_disp(UNi flag)
{
	UNs		cnt, t_no, g_no;

	if( SV_CNT == 00 ){
		return;
	}

	if( SV_DANSUU_SRV  == 00 ){
		SV_DANSUU_SRV = 1;
	}
	else if( SV_DANSUU_SRV > 5 ){
		SV_DANSUU_SRV = 5;
	}

	if(SV_DANSUU_SRV != SV_DANSUU_SRV_BAK){			//工程数 変化あり？
		if(SV_DANSUU_SRV > SV_DANSUU_SRV_BAK) {		//工程数 追加（表示）
			t_no = SV_DANSUU_SRV_BAK + 1;
			for( cnt=SV_DANSUU_SRV_BAK ; cnt < SV_DANSUU_SRV ; cnt++, t_no++){
				g_no = mmon_tchk_tbl[t_no][0];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				mmon_tbl_open(g_no);

				g_no = mmon_tchk_tbl[t_no][1];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				grpno_sv_open(g_no);

				g_no = mmon_tchk_tbl[t_no][2];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				grpno_sv_open(g_no);

				g_no = mmon_tchk_tbl[t_no][3];						//行数
				Disp_line(GAMEN_NO, 0, 0, g_no);					//画面表示用 1行表示
			}

//			SVdata_disp();							//設定値情報　表示
			flag = 0xff;							//設定値情報　表示
		}

		else{								//工程数 削除（消去）
			t_no = SV_DANSUU_SRV + 1;
			for( cnt=SV_DANSUU_SRV ; cnt < SV_DANSUU_SRV_BAK ; cnt++, t_no++){
				g_no = mmon_tchk_tbl[t_no][0];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				mmon_tbl_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][1];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				grpno_sv_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][2];						//情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
				grpno_sv_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][3];						//行数
				g_no |= 0xa000;
				disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//表示用領域を指定ﾃﾞｰﾀで設定
				g_no &= 0x000f;
				Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//表行表示
			}
		}

		SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;		//工程数 セーブ
	}

	if(flag != 00){								//表示？
		SVdata_disp();							//設定値情報　表示
	}

	SWCHG_DISP_ON_FLG = 0xff;					//表示ﾓｰﾄﾞ
	SWchg_disp();								//ＳＷデータ情報　表示
	SWCHG_DISP_ON_FLG = 0x00;					//非表示ﾓｰﾄﾞ
}

#else

const	UNs	mmon_tchk_tbl1[7][4]={				//各工程の情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
			{ 97, 86, 92,  6},
			{ 97, 86, 92,  6},						//工程数 1
			{ 98, 87, 93,  7},						//工程数 2
			{ 99, 88, 94,  8},						//工程数 3
			{100, 89, 95,  9},						//工程数 4
			{101, 90, 96, 10},						//工程数 5
			{102, 00, 00, 11}						//工程数 戻り
		};

const	UNs	mmon_tchk_tbl2[7][4]={				//各工程の情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
			{ 97, 107, 112,  6},
			{ 97, 107, 112,  6},					//工程数 6
			{ 98, 108, 113,  7},					//工程数 7
			{ 99, 109, 114,  8},					//工程数 8
			{100, 110, 115,  9},					//工程数 9
			{101, 111, 116, 10},					//工程数 10
			{102, 00, 00, 11}						//工程数 戻り
		};

void	mmon_tchk_disp(UNi flag)
{
	UNs		cnt, t_no, g_no;
	UNs		dan;
	UNs		*tbl;

	if( SV_CNT == 00 ){
		return;
	}

	if(SV_DANSUU_SRV != SV_DANSUU_SRV_BAK) {			//工程数 変化あり？
		dan = SV_DANSUU_SRV;
		tbl = &mmon_tchk_tbl1[0][0];
		if( ((GAMEN_NO == 3) && (dan > 5))	||
			((GAMEN_NO == 28) && (dan > 5))		 )
		{
			dan = 5;
		}
		else if ( (GAMEN_NO == 6) || (GAMEN_NO == 30) )		// 画面No.6 or 画面No.30
		{
			if (dan > 5)	dan -= 5;
			else			dan = 0;
			tbl = &mmon_tchk_tbl2[0][0];
		}
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
		mmon_vabse_to_vmon2();						// モーション部分をワークへ
#endif
		for( cnt=0, t_no=1 ; cnt < dan ; cnt++, t_no++)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_open(g_no);
			g_no = *(tbl + (t_no * 4) + 1);
			grpno_sv_open(g_no);
			g_no = *(tbl + (t_no * 4) + 2);
			grpno_sv_open(g_no);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no = *(tbl + (t_no * 4) + 3);
			Disp_line(GAMEN_NO, 0, 0, g_no);					//画面表示用 1行表示
#endif
		}
		for( ; cnt < 5 ; cnt++, t_no++)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 1);
			grpno_sv_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 2);
			grpno_sv_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 3);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no |= 0xa000;
			disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//表示用領域を指定ﾃﾞｰﾀで設定
			g_no &= 0x000f;
			Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//表行表示
#else
			vmon2_line_erase(g_no);
#endif
		}

		if(	((GAMEN_NO == 3)  && (SV_DANSUU_SRV <= 5))	||
			((GAMEN_NO == 6)  && (SV_DANSUU_SRV > 5))	||
			((GAMEN_NO == 28) && (SV_DANSUU_SRV <= 5))	||
			((GAMEN_NO == 30) && (SV_DANSUU_SRV > 5))		)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_open(g_no);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no = *(tbl + (t_no * 4) + 3);
			Disp_line(GAMEN_NO, 0, 0, g_no);					//画面表示用 1行表示
#endif
		}
		else
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 3);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no |= 0xa000;
			disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//表示用領域を指定ﾃﾞｰﾀで設定
			g_no &= 0x000f;
			Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//表行表示
#else
//2015/01/15
////			vmon2_line_erase(g_no);
			if( (GAMEN_NO == 3) && (SV_DANSUU_SRV > 5) ) {
				vmon2_line_erase(g_no);								//戻り行を消去
			}
			else if( (GAMEN_NO == 28) && (SV_DANSUU_SRV > 5) ) {
				disp_moji_s_paint(									//戻りの箇所を消去
					20,							//半角桁数
					320,						//X始点
					352-192,					//Y始点
					GAMENn_HEAD.scr_col,		//塗潰し色
					0x0202,						//X2倍/Y2倍
					LCD_VMON2
					);
			}
#endif
		}

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
		if ( GGAMEN_DISP_FLG == 0 ) {
			mmon_vmon2_to_vram();						// モーション部分をVRAMへ
		}
#endif

		flag = 0xff;							//設定値情報　表示
		SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;		//工程数 セーブ
	}

	if( (GAMEN_NO == 3) && (SV_DANSUU_SRV > 5) ) {
		SW_buff[16].SUB_NO |= BIT_F;			// 行程●表示しない
	}
	else {
		SW_buff[16].SUB_NO &= ~BIT_F;			// 行程●表示する。
	}

	if(flag != 00){								//表示？
		if (SEQ_050_SV & BIT_0) {	//V06b
			//設定値背景＝白（入力不可）
			SV_col_chg(85, COL_BLACK, COL_WHITE, COL_WHITE);	//回転の時は上限角の背景を白にする。	V06b
			SV_col_chg(91, COL_BLACK, COL_WHITE, COL_WHITE);	//回転の時は上限位置の背景を白にする。	V06b
		}
		else{						//V06b
			//設定値背景＝水色（通常）
			SV_col_chg(85, COL_BLACK, COL_LBULE, COL_WHITE);	//その他は上限角の背景を水色にする。	V06b
			SV_col_chg(91, COL_BLACK, COL_LBULE, COL_WHITE);	//その他は上限位置の背景を水色にする。	V06b
		}

		if ( (SEQ_050_SV & BIT_2) && (GMN_PAR021==1) ) {	//V06m
			//設定値背景＝白（入力不可）
			SV_col_chg2( 2, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は工程の背景を白にする。
			SV_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は１段目停止時間の背景を白にする。
			SV_col_chg2(27, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は戻り速度の背景を白にする。
			SW_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は１段目「Ｖ」の背景を白にする。

			CSR_cls_tokusyu(97, 92);							//1段目停止時間のｶｰｿﾙ非表示
			if( ( (GAMEN_NO == 3) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO == 6) ||
				( (GAMEN_NO ==28) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO ==30) ) {		//V06p
				CSR_cls_tokusyu(102, 99);						//戻り速度のｶｰｿﾙ非表示
			}
		}
		else{
			//設定値背景＝水色（通常）
			SV_col_chg2( 2, COL_BLACK, COL_LBULE, COL_WHITE);	//振子の時は工程の背景を水色にする。
			SV_col_chg2(10, COL_BLACK, COL_LBULE, COL_WHITE);	//振子の時は１段目停止時間の背景を水色にする。
			SV_col_chg2(27, COL_BLACK, COL_LBULE, COL_WHITE);	//振子の時は戻り速度の背景を水色にする。
			SW_col_chg2(10, COL_BLACK, COL_LBULE, COL_WHITE);	//振子の時は１段目「Ｖ」の背景を白にする。

			CSR_opn_tokusyu(97, 92);							//1段目停止時間のｶｰｿﾙ表示
			if( ( (GAMEN_NO == 3) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO == 6) ||
				( (GAMEN_NO ==28) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO ==30) ) {		//V06p
				CSR_opn_tokusyu(102, 99);						//戻り速度のｶｰｿﾙ表示
			}
		}

//2014/08/20		SVdata_disp();							//設定値情報　表示
//2014/12/23		SVdata_disp1();							//設定値情報　表示
		SVdata_disp();							//設定値情報　表示

	}

//	下限設定、補正設定の表示／非表示			2014/08/20
	Disp_Csr_Moji(4);							//カーソル「下限」表示／非表示
	Disp_Csr_Moji(5);							//カーソル「補正」表示／非表示
	Disp_SW(4);									//スイッチ「補正入/切」表示／表示
	PVdata_disp1(3, 0);							//下限／荷重の単位 表示／表示
	PVdata_disp1(4, 0);							//補正の単位 表示／表示


	SWCHG_DISP_ON_FLG = 0xff;					//表示ﾓｰﾄﾞ
	SWchg_disp();								//ＳＷデータ情報　表示
	SWCHG_DISP_ON_FLG = 0x00;					//非表示ﾓｰﾄﾞ
}
#endif


/*
********************************************************************************
*  Module Name:		mmon_sel_chk
*  Function Name:	ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-10-04
********************************************************************************
*/
void	mmon_sel_chk(void)
{
	UNi		j, k;
	UNs		i;

	k = 0;
	i = SEQ_050_SV;
	for( j=4 ; j > 0 ; j--, i>>=1 ) {
		if( i & BIT_0 ) {						//方式　あり？
			k ++;								//方式　あり＋１
		}
	}


	if( SEQ_050_SV & BIT_1 ) {					//方式選択＝反転？
		if( 00 == (SEQ_024_SV & BIT_2) ) {		//反転は有効(0：無効)？
			k = 0;								//異常
		}
	}
	else if( SEQ_050_SV & BIT_2 ) {				//方式選択＝下往復？
		if( 00 == (SEQ_023_SV & BIT_8) ) {		//下往復は有効(0：無効)？
			k = 0;								//異常
		}
	}
	else if( SEQ_050_SV & BIT_3 ) {				//方式選択＝上往復？
		if( 00 == (SEQ_023_SV & BIT_9) ) {		//上往復は有効(0：無効)？
			k = 0;								//異常
		}
	}

	if( k == 0 || k >= 2 ) {					//異常？
		SEQ_050_SV &= BIT_8;					//方式選択　ｸﾘｱ
		SEQ_050_SV |= BIT_0;					//方式選択＝回転

		SVSW_CHG_FLG |= BIT_3;					//SEQ(ｼｰｹﾝｽ) ﾃﾞｰﾀ格納ﾌﾗｸﾞｾｯﾄ
	}
}


/*
********************************************************************************
*  Module Name:		mmon_trans_get
*  Function Name:	回転方式によるﾃﾞｰﾀの取得
*  Input	:		なし
*  Return	: 		なし
*  Note		:回転・反転・下往復・上往復　の設定によるF-RAM→ﾜｰｸ への転送
*
*  履 歴	:FIT)田端		ON:2002-10-04
********************************************************************************
*/
void	mmon_trans_get(void)
{

	if( SEQ_050_SV & BIT_1 ) {								//反転　？
		SV_1DANPOS_SRV	=	SV_1DANPOS1_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS1_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS1_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS1_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS1_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS1_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS1_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS1_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS1_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS1_SRV;				/* 10段目目標位置		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG1_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG1_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG1_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG1_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG1_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG1_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG1_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG1_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG1_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG1_SRV;				/* 10段目角度位置		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD1_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD1_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD1_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD1_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD1_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD1_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD1_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD1_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD1_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD1_SRV;				/* 10段目移動速度		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM1_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM1_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM1_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM1_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM1_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM1_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM1_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM1_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM1_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM1_SRV;				/* 10段目停止時間		*/

		SV_DANSUU_SRV	=	SV_DANSUU1_SRV;					/* 段数					*/
//2019-06-07		if (CB_SYS_PARAM045 == 1) { }	// V01i
//2019-06-07		else {
//2019-06-07			SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU1_SRV;			/* 待機点角度			*/
//2019-06-07			SV_TAIKIPOS_SRV	=	SV_TAIKIPOS1_SRV;			/* 待機点位置			*/
//2019-06-07		}
//koma 2019-06-07 反転はparam045に影響を受けない
		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU1_SRV;			/* 待機点角度			*/
		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS1_SRV;			/* 待機点位置			*/

		SV_DAIHAITO_SRV	=	SV_DAIHAITO1_SRV;				/* ダイハイト			*/
		SV_HOASEI_SRV	=	SV_HOASEI1_SRV;					/* 補正データ			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD1_SRV;				/* 基準速度				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM1_SRV;				/* 待機時間				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN1_SRV;					/* 待機完了範囲			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN1_SRV;					/* 目標完了範囲			*/

		SEQ_050_SV		&=	~BIT_8;							/* 補正ｸﾘｱ				*/
		SEQ_050_SV		|=	(SV_KAITEN1_SRV & BIT_8);		/* 回転方式				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP1;					/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS1;						/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS1_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS1_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS1_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS1_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS1_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS1_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS1_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS1_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS1_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS1_SRV;				/* 10段目目標位置		*/
		SV_KAJOBJ_HAB	=	SV_KAJOBJ1_HAB;					/* 荷重完了範囲			*/
	}
	else if( SEQ_050_SV & BIT_2 ) {							//下往復　？
		SV_1DANPOS_SRV	=	SV_1DANPOS2_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS2_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS2_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS2_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS2_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS2_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS2_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS2_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS2_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS2_SRV;				/* 10段目目標位置		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG2_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG2_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG2_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG2_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG2_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG2_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG2_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG2_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG2_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG2_SRV;				/* 10段目角度位置		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD2_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD2_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD2_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD2_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD2_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD2_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD2_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD2_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD2_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD2_SRV;				/* 10段目移動速度		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM2_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM2_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM2_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM2_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM2_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM2_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM2_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM2_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM2_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM2_SRV;				/* 10段目停止時間		*/

		SV_DANSUU_SRV	=	SV_DANSUU2_SRV;					/* 段数					*/

//2019-06-07		if (CB_SYS_PARAM045 == 1) { }	// V01i
//2019-06-07		else {
//2019-06-07			SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU2_SRV;			/* 待機点角度			*/
//2019-06-07			SV_TAIKIPOS_SRV	=	SV_TAIKIPOS2_SRV;			/* 待機点位置			*/
//2019-06-07		}
//koma 2019-06-07 振子はparam045に影響を受けない
		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU2_SRV;			/* 待機点角度			*/
		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS2_SRV;			/* 待機点位置			*/

		SV_DAIHAITO_SRV	=	SV_DAIHAITO2_SRV;				/* ダイハイト			*/
		SV_HOASEI_SRV	=	SV_HOASEI2_SRV;					/* 補正データ			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD2_SRV;				/* 基準速度				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM2_SRV;				/* 待機時間				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN2_SRV;					/* 待機完了範囲			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN2_SRV;					/* 目標完了範囲			*/

		SEQ_050_SV		&=	~BIT_8;							/* 補正ｸﾘｱ				*/
		SEQ_050_SV		|=	(SV_KAITEN2_SRV & BIT_8);		/* 回転方式				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP2;					/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS2;						/* 荷重補正		V01m	*/

		if (GMN_PAR021 == 1) {						//V06m
			SV_DANSUU_SRV	= 1;					/* 段数					*/
			SV_1DANTIM_SRV	= 0;					/* 01段目停止時間		*/
			SV_TAIKSPD_SRV	= SV_1DANSPD_SRV;		/* 戻り移動速度			*/
		}

//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS2_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS2_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS2_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS2_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS2_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS2_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS2_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS2_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS2_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS2_SRV;				/* 10段目目標位置		*/
		SV_KAJOBJ_HAB	=	SV_KAJOBJ2_HAB;					/* 荷重完了範囲			*/
	}
	else if( SEQ_050_SV & BIT_3 ) {							//上往復　？
		SV_1DANPOS_SRV	=	SV_1DANPOS3_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS3_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS3_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS3_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS3_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS3_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS3_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS3_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS3_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS3_SRV;				/* 10段目目標位置		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG3_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG3_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG3_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG3_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG3_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG3_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG3_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG3_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG3_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG3_SRV;				/* 10段目角度位置		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD3_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD3_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD3_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD3_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD3_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD3_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD3_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD3_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD3_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD3_SRV;				/* 10段目移動速度		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM3_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM3_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM3_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM3_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM3_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM3_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM3_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM3_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM3_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM3_SRV;				/* 10段目停止時間		*/

		SV_DANSUU_SRV	=	SV_DANSUU3_SRV;					/* 段数					*/
//		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS3_SRV;				/* 待機点位置			*/
//		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU3_SRV;				/* 待機点角度			*/
		if (CB_SYS_PARAM045 == 1) { }	// V01i
		else {
			SV_TAIKIKAKU_SRV =	0;							/* 待機点角度			*/
//V06b			SV_TAIKIPOS_SRV	=	0;							/* 待機点位置			*/
//2015/01/08			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);	//角度→mm変換
			SV_TAIKIPOS_SRV = cnv_mm_inch(DigRnaChange1(SV_TAIKIKAKU_SRV), 0);	//角度→mm変換→inch変換
		}
		SV_DAIHAITO_SRV	=	SV_DAIHAITO3_SRV;				/* ダイハイト			*/
		SV_HOASEI_SRV	=	SV_HOASEI3_SRV;					/* 補正データ			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD3_SRV;				/* 基準速度				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM3_SRV;				/* 待機時間				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN3_SRV;					/* 待機完了範囲			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN3_SRV;					/* 目標完了範囲			*/

		SEQ_050_SV		&=	~BIT_8;							/* 補正ｸﾘｱ				*/
		SEQ_050_SV		|=	(SV_KAITEN3_SRV & BIT_8);		/* 回転方式				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP3;					/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS3;						/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS3_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS3_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS3_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS3_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS3_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS3_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS3_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS3_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS3_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS3_SRV;				/* 10段目目標位置		*/
		SV_KAJOBJ_HAB	=	SV_KAJOBJ3_HAB;					/* 荷重完了範囲			*/
	}
	else {													//回転　？
		SV_1DANPOS_SRV	=	SV_1DANPOS0_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS0_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS0_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS0_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS0_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS0_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS0_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS0_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS0_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS0_SRV;				/* 10段目目標位置		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG0_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG0_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG0_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG0_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG0_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG0_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG0_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG0_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG0_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG0_SRV;				/* 10段目角度位置		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD0_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD0_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD0_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD0_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD0_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD0_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD0_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD0_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD0_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD0_SRV;				/* 10段目移動速度		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM0_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM0_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM0_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM0_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM0_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM0_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM0_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM0_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM0_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM0_SRV;				/* 10段目停止時間		*/

		SV_DANSUU_SRV	=	SV_DANSUU0_SRV;					/* 段数					*/
//		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS0_SRV;				/* 待機点位置			*/
//		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU0_SRV;				/* 待機点角度			*/
		if (CB_SYS_PARAM045 == 1) { }	// V01i
		else {
			SV_TAIKIKAKU_SRV =	0;							/* 待機点角度			*/
//V06b			SV_TAIKIPOS_SRV	=	0;							/* 待機点位置			*/
//2015/01/08			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);	//角度→mm変換
			SV_TAIKIPOS_SRV = cnv_mm_inch(DigRnaChange1(SV_TAIKIKAKU_SRV), 0);	//角度→mm変換→inch変換
		}
		SV_DAIHAITO_SRV	=	SV_DAIHAITO0_SRV;				/* ダイハイト			*/
		SV_HOASEI_SRV	=	SV_HOASEI0_SRV;					/* 補正データ			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD0_SRV;				/* 基準速度				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM0_SRV;				/* 待機時間				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN0_SRV;					/* 待機完了範囲			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN0_SRV;					/* 目標完了範囲			*/

		SEQ_050_SV		&=	~BIT_8;							/* 補正ｸﾘｱ				*/
		SEQ_050_SV		|=	(SV_KAITEN0_SRV & BIT_8);		/* 回転方式				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP0;					/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS0;						/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS0_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS0_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS0_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS0_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS0_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS0_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS0_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS0_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS0_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS0_SRV;				/* 10段目目標位置		*/
		SV_KAJOBJ_HAB	=	SV_KAJOBJ0_HAB;					/* 荷重完了範囲			*/
	}

	SVSW_CHG_FLG |= (BIT_2 | BIT_3);						//MOT(ﾓｰｼｮﾝ)/SEQ(ｼｰｹﾝｽ) ﾃﾞｰﾀ格納ﾌﾗｸﾞｾｯﾄ

}


/*
********************************************************************************
*  Module Name:		mmon_trans_put
*  Function Name:	回転方式によるﾃﾞｰﾀの格納
*  Input	:		なし
*  Return	: 		なし
*  Note		:回転・反転・下往復・上往復　の設定によるﾜｰｸ→F-RAM への転送
*
*  履 歴	:FIT)田端		ON:2002-10-04
********************************************************************************
*/
void	mmon_trans_put(void)
{

	if( SEQ_050_SV & BIT_0 ) {								//回転　？
		SV_1DANPOS0_SRV		=	SV_1DANPOS_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS0_SRV		=	SV_2DANPOS_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS0_SRV		=	SV_3DANPOS_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS0_SRV		=	SV_4DANPOS_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS0_SRV		=	SV_5DANPOS_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS0_SRV		=	SV_6DANPOS_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS0_SRV		=	SV_7DANPOS_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS0_SRV		=	SV_8DANPOS_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS0_SRV		=	SV_9DANPOS_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS0_SRV	=	SV_10DANPOS_SRV;			/* 10段目目標位置		*/

		SV_1DANDEG0_SRV		=	SV_1DANDEG_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG0_SRV		=	SV_2DANDEG_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG0_SRV		=	SV_3DANDEG_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG0_SRV		=	SV_4DANDEG_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG0_SRV		=	SV_5DANDEG_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG0_SRV		=	SV_6DANDEG_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG0_SRV		=	SV_7DANDEG_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG0_SRV		=	SV_8DANDEG_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG0_SRV		=	SV_9DANDEG_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG0_SRV	=	SV_10DANDEG_SRV;			/* 10段目角度位置		*/

		SV_1DANSPD0_SRV		=	SV_1DANSPD_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD0_SRV		=	SV_2DANSPD_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD0_SRV		=	SV_3DANSPD_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD0_SRV		=	SV_4DANSPD_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD0_SRV		=	SV_5DANSPD_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD0_SRV		=	SV_6DANSPD_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD0_SRV		=	SV_7DANSPD_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD0_SRV		=	SV_8DANSPD_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD0_SRV		=	SV_9DANSPD_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD0_SRV	=	SV_10DANSPD_SRV;			/* 10段目移動速度		*/

		SV_1DANTIM0_SRV		=	SV_1DANTIM_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM0_SRV		=	SV_2DANTIM_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM0_SRV		=	SV_3DANTIM_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM0_SRV		=	SV_4DANTIM_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM0_SRV		=	SV_5DANTIM_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM0_SRV		=	SV_6DANTIM_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM0_SRV		=	SV_7DANTIM_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM0_SRV		=	SV_8DANTIM_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM0_SRV		=	SV_9DANTIM_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM0_SRV	=	SV_10DANTIM_SRV;			/* 10段目停止時間		*/

		SV_DANSUU0_SRV		=	SV_DANSUU_SRV;				/* 段数					*/
		SV_DAIHAITO0_SRV	=	SV_DAIHAITO_SRV;			/* ダイハイト			*/
		SV_TAIKIPOS0_SRV	=	SV_TAIKIPOS_SRV;			/* 待機点位置			*/
		SV_TAIKIKAKU0_SRV	=	SV_TAIKIKAKU_SRV;			/* 待機点角度			*/
		SV_HOASEI0_SRV		=	SV_HOASEI_SRV;				/* 補正データ			*/

		SV_TAIKSPD0_SRV		=	SV_TAIKSPD_SRV;				/* 基準速度				*/
		SV_TAIKTIM0_SRV		=	SV_TAIKTIM_SRV;				/* 待機時間				*/

//		SV_TAIKAN0_SRV		=	SV_TAIKAN_SRV;				/* 待機完了範囲			*/
		SV_MOKKAN0_SRV		=	SV_MOKKAN_SRV;				/* 目標完了範囲			*/

		SV_KAITEN0_SRV 		=	SEQ_050_SV;					/* 回転方式				*/

		SV_KAJYUU_OBJP0		=	SV_KAJYUU_OBJP;				/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS0		=	SV_KAJYUU_PRS;				/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS0_SRV		=	SV_1DANPRS_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS0_SRV		=	SV_2DANPRS_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS0_SRV		=	SV_3DANPRS_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS0_SRV		=	SV_4DANPRS_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS0_SRV		=	SV_5DANPRS_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS0_SRV		=	SV_6DANPRS_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS0_SRV		=	SV_7DANPRS_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS0_SRV		=	SV_8DANPRS_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS0_SRV		=	SV_9DANPRS_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS0_SRV	=	SV_10DANPRS_SRV;			/* 10段目目標位置		*/
		SV_KAJOBJ0_HAB		=	SV_KAJOBJ_HAB;				/* 荷重完了範囲			*/
	}
	else if( SEQ_050_SV & BIT_1 ) {							//反転　？
		SV_1DANPOS1_SRV		=	SV_1DANPOS_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS1_SRV		=	SV_2DANPOS_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS1_SRV		=	SV_3DANPOS_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS1_SRV		=	SV_4DANPOS_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS1_SRV		=	SV_5DANPOS_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS1_SRV		=	SV_6DANPOS_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS1_SRV		=	SV_7DANPOS_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS1_SRV		=	SV_8DANPOS_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS1_SRV		=	SV_9DANPOS_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS1_SRV	=	SV_10DANPOS_SRV;			/* 10段目目標位置		*/

		SV_1DANDEG1_SRV		=	SV_1DANDEG_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG1_SRV		=	SV_2DANDEG_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG1_SRV		=	SV_3DANDEG_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG1_SRV		=	SV_4DANDEG_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG1_SRV		=	SV_5DANDEG_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG1_SRV		=	SV_6DANDEG_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG1_SRV		=	SV_7DANDEG_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG1_SRV		=	SV_8DANDEG_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG1_SRV		=	SV_9DANDEG_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG1_SRV	=	SV_10DANDEG_SRV;			/* 10段目角度位置		*/

		SV_1DANSPD1_SRV		=	SV_1DANSPD_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD1_SRV		=	SV_2DANSPD_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD1_SRV		=	SV_3DANSPD_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD1_SRV		=	SV_4DANSPD_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD1_SRV		=	SV_5DANSPD_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD1_SRV		=	SV_6DANSPD_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD1_SRV		=	SV_7DANSPD_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD1_SRV		=	SV_8DANSPD_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD1_SRV		=	SV_9DANSPD_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD1_SRV	=	SV_10DANSPD_SRV;			/* 10段目移動速度		*/

		SV_1DANTIM1_SRV		=	SV_1DANTIM_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM1_SRV		=	SV_2DANTIM_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM1_SRV		=	SV_3DANTIM_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM1_SRV		=	SV_4DANTIM_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM1_SRV		=	SV_5DANTIM_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM1_SRV		=	SV_6DANTIM_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM1_SRV		=	SV_7DANTIM_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM1_SRV		=	SV_8DANTIM_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM1_SRV		=	SV_9DANTIM_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM1_SRV	=	SV_10DANTIM_SRV;			/* 10段目停止時間		*/

		SV_DANSUU1_SRV		=	SV_DANSUU_SRV;				/* 段数					*/
		SV_DAIHAITO1_SRV	=	SV_DAIHAITO_SRV;			/* ダイハイト			*/
		SV_TAIKIPOS1_SRV	=	SV_TAIKIPOS_SRV;			/* 待機点位置			*/
		SV_TAIKIKAKU1_SRV	=	SV_TAIKIKAKU_SRV;			/* 待機点角度			*/
		SV_HOASEI1_SRV		=	SV_HOASEI_SRV;				/* 補正データ			*/

		SV_TAIKSPD1_SRV		=	SV_TAIKSPD_SRV;				/* 基準速度				*/
		SV_TAIKTIM1_SRV		=	SV_TAIKTIM_SRV;				/* 待機時間				*/

//		SV_TAIKAN1_SRV		=	SV_TAIKAN_SRV;				/* 待機完了範囲			*/
		SV_MOKKAN1_SRV		=	SV_MOKKAN_SRV;				/* 目標完了範囲			*/

		SV_KAITEN1_SRV 		=	SEQ_050_SV;					/* 回転方式				*/

		SV_KAJYUU_OBJP1		=	SV_KAJYUU_OBJP;				/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS1		=	SV_KAJYUU_PRS;				/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS1_SRV		=	SV_1DANPRS_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS1_SRV		=	SV_2DANPRS_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS1_SRV		=	SV_3DANPRS_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS1_SRV		=	SV_4DANPRS_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS1_SRV		=	SV_5DANPRS_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS1_SRV		=	SV_6DANPRS_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS1_SRV		=	SV_7DANPRS_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS1_SRV		=	SV_8DANPRS_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS1_SRV		=	SV_9DANPRS_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS1_SRV	=	SV_10DANPRS_SRV;			/* 10段目目標位置		*/
		SV_KAJOBJ1_HAB		=	SV_KAJOBJ_HAB;				/* 荷重完了範囲			*/
	}
	else if( SEQ_050_SV & BIT_2 ) {							//下往復　？
		SV_1DANPOS2_SRV		=	SV_1DANPOS_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS2_SRV		=	SV_2DANPOS_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS2_SRV		=	SV_3DANPOS_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS2_SRV		=	SV_4DANPOS_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS2_SRV		=	SV_5DANPOS_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS2_SRV		=	SV_6DANPOS_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS2_SRV		=	SV_7DANPOS_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS2_SRV		=	SV_8DANPOS_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS2_SRV		=	SV_9DANPOS_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS2_SRV	=	SV_10DANPOS_SRV;			/* 10段目目標位置		*/

		SV_1DANDEG2_SRV		=	SV_1DANDEG_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG2_SRV		=	SV_2DANDEG_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG2_SRV		=	SV_3DANDEG_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG2_SRV		=	SV_4DANDEG_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG2_SRV		=	SV_5DANDEG_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG2_SRV		=	SV_6DANDEG_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG2_SRV		=	SV_7DANDEG_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG2_SRV		=	SV_8DANDEG_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG2_SRV		=	SV_9DANDEG_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG2_SRV	=	SV_10DANDEG_SRV;			/* 10段目角度位置		*/

		SV_1DANSPD2_SRV		=	SV_1DANSPD_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD2_SRV		=	SV_2DANSPD_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD2_SRV		=	SV_3DANSPD_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD2_SRV		=	SV_4DANSPD_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD2_SRV		=	SV_5DANSPD_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD2_SRV		=	SV_6DANSPD_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD2_SRV		=	SV_7DANSPD_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD2_SRV		=	SV_8DANSPD_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD2_SRV		=	SV_9DANSPD_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD2_SRV	=	SV_10DANSPD_SRV;			/* 10段目移動速度		*/

		SV_1DANTIM2_SRV		=	SV_1DANTIM_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM2_SRV		=	SV_2DANTIM_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM2_SRV		=	SV_3DANTIM_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM2_SRV		=	SV_4DANTIM_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM2_SRV		=	SV_5DANTIM_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM2_SRV		=	SV_6DANTIM_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM2_SRV		=	SV_7DANTIM_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM2_SRV		=	SV_8DANTIM_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM2_SRV		=	SV_9DANTIM_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM2_SRV	=	SV_10DANTIM_SRV;			/* 10段目停止時間		*/

		SV_DANSUU2_SRV		=	SV_DANSUU_SRV;				/* 段数					*/
		SV_DAIHAITO2_SRV	=	SV_DAIHAITO_SRV;			/* ダイハイト			*/
		SV_TAIKIPOS2_SRV	=	SV_TAIKIPOS_SRV;			/* 待機点位置			*/
		SV_TAIKIKAKU2_SRV	=	SV_TAIKIKAKU_SRV;			/* 待機点角度			*/
		SV_HOASEI2_SRV		=	SV_HOASEI_SRV;				/* 補正データ			*/

		SV_TAIKSPD2_SRV		=	SV_TAIKSPD_SRV;				/* 基準速度				*/
		SV_TAIKTIM2_SRV		=	SV_TAIKTIM_SRV;				/* 待機時間				*/

//		SV_TAIKAN2_SRV		=	SV_TAIKAN_SRV;				/* 待機完了範囲			*/
		SV_MOKKAN2_SRV		=	SV_MOKKAN_SRV;				/* 目標完了範囲			*/

		SV_KAITEN2_SRV 		=	SEQ_050_SV;					/* 回転方式				*/

		SV_KAJYUU_OBJP2		=	SV_KAJYUU_OBJP;				/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS2		=	SV_KAJYUU_PRS;				/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS2_SRV		=	SV_1DANPRS_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS2_SRV		=	SV_2DANPRS_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS2_SRV		=	SV_3DANPRS_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS2_SRV		=	SV_4DANPRS_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS2_SRV		=	SV_5DANPRS_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS2_SRV		=	SV_6DANPRS_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS2_SRV		=	SV_7DANPRS_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS2_SRV		=	SV_8DANPRS_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS2_SRV		=	SV_9DANPRS_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS2_SRV	=	SV_10DANPRS_SRV;			/* 10段目目標位置		*/
		SV_KAJOBJ2_HAB		=	SV_KAJOBJ_HAB;				/* 荷重完了範囲			*/
	}
	else if( SEQ_050_SV & BIT_3 ) {							//上往復　？
		SV_1DANPOS3_SRV		=	SV_1DANPOS_SRV;				/* 01段目目標位置		*/
		SV_2DANPOS3_SRV		=	SV_2DANPOS_SRV;				/* 02段目目標位置		*/
		SV_3DANPOS3_SRV		=	SV_3DANPOS_SRV;				/* 03段目目標位置		*/
		SV_4DANPOS3_SRV		=	SV_4DANPOS_SRV;				/* 04段目目標位置		*/
		SV_5DANPOS3_SRV		=	SV_5DANPOS_SRV;				/* 05段目目標位置		*/
		SV_6DANPOS3_SRV		=	SV_6DANPOS_SRV;				/* 06段目目標位置		*/
		SV_7DANPOS3_SRV		=	SV_7DANPOS_SRV;				/* 07段目目標位置		*/
		SV_8DANPOS3_SRV		=	SV_8DANPOS_SRV;				/* 08段目目標位置		*/
		SV_9DANPOS3_SRV		=	SV_9DANPOS_SRV;				/* 09段目目標位置		*/
		SV_10DANPOS3_SRV	=	SV_10DANPOS_SRV;			/* 10段目目標位置		*/

		SV_1DANDEG3_SRV		=	SV_1DANDEG_SRV;				/* 01段目角度位置		*/
		SV_2DANDEG3_SRV		=	SV_2DANDEG_SRV;				/* 02段目角度位置		*/
		SV_3DANDEG3_SRV		=	SV_3DANDEG_SRV;				/* 03段目角度位置		*/
		SV_4DANDEG3_SRV		=	SV_4DANDEG_SRV;				/* 04段目角度位置		*/
		SV_5DANDEG3_SRV		=	SV_5DANDEG_SRV;				/* 05段目角度位置		*/
		SV_6DANDEG3_SRV		=	SV_6DANDEG_SRV;				/* 06段目角度位置		*/
		SV_7DANDEG3_SRV		=	SV_7DANDEG_SRV;				/* 07段目角度位置		*/
		SV_8DANDEG3_SRV		=	SV_8DANDEG_SRV;				/* 08段目角度位置		*/
		SV_9DANDEG3_SRV		=	SV_9DANDEG_SRV;				/* 09段目角度位置		*/
		SV_10DANDEG3_SRV	=	SV_10DANDEG_SRV;			/* 10段目角度位置		*/

		SV_1DANSPD3_SRV		=	SV_1DANSPD_SRV;				/* 01段目移動速度		*/
		SV_2DANSPD3_SRV		=	SV_2DANSPD_SRV;				/* 02段目移動速度		*/
		SV_3DANSPD3_SRV		=	SV_3DANSPD_SRV;				/* 03段目移動速度		*/
		SV_4DANSPD3_SRV		=	SV_4DANSPD_SRV;				/* 04段目移動速度		*/
		SV_5DANSPD3_SRV		=	SV_5DANSPD_SRV;				/* 05段目移動速度		*/
		SV_6DANSPD3_SRV		=	SV_6DANSPD_SRV;				/* 06段目移動速度		*/
		SV_7DANSPD3_SRV		=	SV_7DANSPD_SRV;				/* 07段目移動速度		*/
		SV_8DANSPD3_SRV		=	SV_8DANSPD_SRV;				/* 08段目移動速度		*/
		SV_9DANSPD3_SRV		=	SV_9DANSPD_SRV;				/* 09段目移動速度		*/
		SV_10DANSPD3_SRV	=	SV_10DANSPD_SRV;			/* 10段目移動速度		*/

		SV_1DANTIM3_SRV		=	SV_1DANTIM_SRV;				/* 01段目停止時間		*/
		SV_2DANTIM3_SRV		=	SV_2DANTIM_SRV;				/* 02段目停止時間		*/
		SV_3DANTIM3_SRV		=	SV_3DANTIM_SRV;				/* 03段目停止時間		*/
		SV_4DANTIM3_SRV		=	SV_4DANTIM_SRV;				/* 04段目停止時間		*/
		SV_5DANTIM3_SRV		=	SV_5DANTIM_SRV;				/* 05段目停止時間		*/
		SV_6DANTIM3_SRV		=	SV_6DANTIM_SRV;				/* 06段目停止時間		*/
		SV_7DANTIM3_SRV		=	SV_7DANTIM_SRV;				/* 07段目停止時間		*/
		SV_8DANTIM3_SRV		=	SV_8DANTIM_SRV;				/* 08段目停止時間		*/
		SV_9DANTIM3_SRV		=	SV_9DANTIM_SRV;				/* 09段目停止時間		*/
		SV_10DANTIM3_SRV	=	SV_10DANTIM_SRV;			/* 10段目停止時間		*/

		SV_DANSUU3_SRV		=	SV_DANSUU_SRV;				/* 段数					*/
		SV_DAIHAITO3_SRV	=	SV_DAIHAITO_SRV;			/* ダイハイト			*/
		SV_TAIKIPOS3_SRV	=	SV_TAIKIPOS_SRV;			/* 待機点位置			*/
		SV_TAIKIKAKU3_SRV	=	SV_TAIKIKAKU_SRV;			/* 待機点角度			*/
		SV_HOASEI3_SRV		=	SV_HOASEI_SRV;				/* 補正データ			*/

		SV_TAIKSPD3_SRV		=	SV_TAIKSPD_SRV;				/* 基準速度				*/
		SV_TAIKTIM3_SRV		=	SV_TAIKTIM_SRV;				/* 待機時間				*/

//		SV_TAIKAN3_SRV		=	SV_TAIKAN_SRV;				/* 待機完了範囲			*/
		SV_MOKKAN3_SRV		=	SV_MOKKAN_SRV;				/* 目標完了範囲			*/

		SV_KAITEN3_SRV 		=	SEQ_050_SV;					/* 回転方式				*/

		SV_KAJYUU_OBJP3		=	SV_KAJYUU_OBJP;				/* 荷重目標		V01m	*/
		SV_KAJYUU_PRS3		=	SV_KAJYUU_PRS;				/* 荷重補正		V01m	*/

//2015/01/14
		SV_1DANPRS3_SRV		=	SV_1DANPRS_SRV;				/* 01段目目標位置		*/
		SV_2DANPRS3_SRV		=	SV_2DANPRS_SRV;				/* 02段目目標位置		*/
		SV_3DANPRS3_SRV		=	SV_3DANPRS_SRV;				/* 03段目目標位置		*/
		SV_4DANPRS3_SRV		=	SV_4DANPRS_SRV;				/* 04段目目標位置		*/
		SV_5DANPRS3_SRV		=	SV_5DANPRS_SRV;				/* 05段目目標位置		*/
		SV_6DANPRS3_SRV		=	SV_6DANPRS_SRV;				/* 06段目目標位置		*/
		SV_7DANPRS3_SRV		=	SV_7DANPRS_SRV;				/* 07段目目標位置		*/
		SV_8DANPRS3_SRV		=	SV_8DANPRS_SRV;				/* 08段目目標位置		*/
		SV_9DANPRS3_SRV		=	SV_9DANPRS_SRV;				/* 09段目目標位置		*/
		SV_10DANPRS3_SRV	=	SV_10DANPRS_SRV;			/* 10段目目標位置		*/
		SV_KAJOBJ3_HAB		=	SV_KAJOBJ_HAB;				/* 荷重完了範囲			*/
	}

	FRAM_csum_set();										//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	KAT_DATCHG_FLG = 0xff;									//型データ変更フラグ

}


/*
********************************************************************************
*  Module Name:		mmon_spd_in
*  Function Name:	速度リミット値を入力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2013-02-16		V06p
********************************************************************************
*/
void	mmon_spd_in(void)
{
	UNs		t_no, i, bit;
	UNs		limit_spd;
	UNs		chg;

	chg = 0;
	bit = BIT_0;
	t_no = CSR_TBL_POS_NOW;

	if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon) ) || 			//モーションモニタ1-5画面
		 ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset) ) ) {			//モーション設定1-5画面

		if (CSR_buff[t_no].DATA_NO == 102) {
			if (PV0_CKSPD_LMBIT & BIT_15) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//戻り速度
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & BIT_15) {
				limit_spd = PVP_CKLMT_MDSPD;			//戻り速度
				chg = 0xff;
			}
		}
		else {
			i = CSR_buff[t_no].DATA_NO - 97;
			bit<<=i;
			if (PV0_CKSPD_LMBIT & bit) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//戻り速度
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & bit) {
				limit_spd = PVP_CKLMT_SPDTOP[i];		//各工程速度
				chg = 0xff;
			}
		}
	}
	else if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon2) ) || 			//モーションモニタ6-10画面
			  ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset2) ) ) {			//モーション設定6-10画面

		if (CSR_buff[t_no].DATA_NO == 102) {
			if (PV0_CKSPD_LMBIT & BIT_15) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//戻り速度
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & BIT_15) {
				limit_spd = PVP_CKLMT_MDSPD;			//戻り速度
				chg = 0xff;
			}
		}
		else {
			i = CSR_buff[t_no].DATA_NO - 97;
			i += 5;
			bit<<=i;
			if (PV0_CKSPD_LMBIT & bit) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//戻り速度
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & bit) {
				limit_spd = PVP_CKLMT_SPDTOP[i];		//各工程速度
				chg = 0xff;
			}
		}
	}

	if (chg) {
		t_no = SV_TBL_POS_NOW;

		SV_DATA_CHG = 0x55;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
		SV_DISP_BUFF = HEX_BCD4(limit_spd);					//変更データバッファクリア

		TENKEY_CNT = 0;

		SVPV_data_disp(SV_DISP_BUFF, &SV_buff[t_no], 0, 0x482);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/反転表示(背景緑))
	}

}


/*
********************************************************************************
*  Module Name:		mmon_agl_in
*  Function Name:	角度リミット値を入力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2014-04-15
********************************************************************************
*/
void	mmon_agl_in(void)
{
	UNs		t_no, i, bit;
	UNs		limit_agl;
	UNl		limit_pos;
	UNs		chg;

	chg = 0;
	bit = BIT_0;
	t_no = CSR_TBL_POS_NOW;

	if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon) ) || 			//モーションモニタ1-5画面
		 ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset) ) ) {			//モーション設定1-5画面

		i = CSR_buff[t_no].DATA_NO - 97;
		bit<<=i;
		if (PVP_CKAGL_OVBIT & bit) {
			limit_agl = PVP_CKLMT_AGLTOP[i];		//各工程角度
			chg = 0xff;
		}
	}
	else if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon2) ) || 			//モーションモニタ6-10画面
			  ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset2) ) ) {			//モーション設定6-10画面

		i = CSR_buff[t_no].DATA_NO - 97;
		i += 5;
		bit<<=i;
		if (PVP_CKAGL_OVBIT & bit) {
			limit_agl = PVP_CKLMT_AGLTOP[i];		//各工程角度
			chg = 0xff;
		}
	}

	if (chg) {
		t_no = SV_TBL_POS_NOW;

		SV_DATA_CHG = 0xff;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
		SV_DISP_BUFF = HEX_BCD4(limit_agl/10);

		TENKEY_CNT = 0;

		SVPV_data_disp((UNl)limit_agl, &SV_buff[t_no], 0, 0x481);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/反転表示(背景緑))
	}

}


/*
********************************************************************************
*  Function Name:	下限／荷重目標切換え
*  Input	:		工程No.0～9（1～10段目の意味）
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2015/01/15
********************************************************************************
*/
void	mmon_pos_kaj_chg(UNs no)
{
	UNs		bit, cnt, t_no, sarch, t_no_tanni;
	UNl		*pos;
	UNs		*kaj;

	if ( (SEQ_050_SV & BIT_1) == 0 ) 		return;			//反転？
	if ( (SEQ_PAR_151 & BIT_2) == 0 )		return;

	bit = BIT_0;
	bit <<= no;

	SV_MOTOBJ_INF1 ^= bit;								//位置⇔荷重 切替

	FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	KAT_DATCHG_FLG = 0xff;								//型データ変更フラグ

	pos = &SV_1DANPOS_SRV;
	pos += no;
	kaj = &SV_1DANPRS_SRV;
	kaj += no;

	if (no<5) {
		sarch = 92+no;									//1～5段目の検索する設定値ｸﾞﾙｰﾌﾟNo.
		t_no_tanni = 5+no;								//1～5段目の単位のﾊﾞｯﾌｧｱﾄﾞﾚｽ
	}
	else {
//2015/04/10		sarch = 112+no;									//6～10段目の検索する設定値ｸﾞﾙｰﾌﾟNo.
////////////		t_no_tanni = 5+no;								//6～10段目の単位のﾊﾞｯﾌｧｱﾄﾞﾚｽ
		sarch = 112+(no-5);									//6～10段目の検索する設定値ｸﾞﾙｰﾌﾟNo.
		t_no_tanni = 5+(no-5);								//6～10段目の単位のﾊﾞｯﾌｧｱﾄﾞﾚｽ
	}

	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == sarch) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if (SV_MOTOBJ_INF1 & bit) {
				/* 位置 -> 荷重*/
				SV_buff[t_no].DATA_ADR = kaj;			//格納先ｱﾄﾞﾚｽ変更
				SV_buff[t_no].BYTE_NO = 2;				//ﾊﾞｲﾄ長の変更
				SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;	//小数点位置
				SV_buff[t_no].TOK_FLG = 0;				//特殊ﾌﾗｸﾞ
				SV_buff[t_no].SUB_NO = 123;				//ｻﾌﾞﾙｰﾁﾝNo.

				PV_buff[t_no_tanni].DATA_ADR = (UNs *)&CAR_KAJ_AREA;		//単位
			}
			else {
				/* 荷重 -> 位置 */
				SV_buff[t_no].DATA_ADR = (UNs *)pos;	//格納先ｱﾄﾞﾚｽ変更
				SV_buff[t_no].BYTE_NO = 4;				//ﾊﾞｲﾄ長の変更
				SV_buff[t_no].TEN_POS = SYO_LNG_CNT;	//小数点位置
				SV_buff[t_no].TOK_FLG = 0x0400;			//特殊ﾌﾗｸﾞ（内部10倍）
				SV_buff[t_no].SUB_NO = 75;				//ｻﾌﾞﾙｰﾁﾝNo.

				PV_buff[t_no_tanni].DATA_ADR = (UNs *)&CAR_LNG_AREA;		//単位
			}
			break;
		}
	}

	SVdata_disp();							//全設定値表示
	SV_csr_set();							//設定値ｶｰｿﾙ表示
	CSR_sw56_disp();						//SW56文字表示
	PVdata_disp1(t_no_tanni, 0);			//単位 表示
}


/*
********************************************************************************
*  Module Name:		cnv_mi_mi
*  Function Name:	単位切替(mm/INCH→mm/INCH)
*  Input	:		mm/INCH
*  Return	: 		mm/INCH
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_mi_mi(UNl mm_bf)
{
	UNl		wk1;

	wk1 = mm_bf;
	if( SEQ_016_SV & BIT_6 ) {		//単位切替 mm/INCH 単位系(1:INCH)
	}
	else{
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//単位 高精度(1:高精度)
			wk1 /= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mi_mi_sur
*  Function Name:	単位切替(mm/INCH→mm/INCH)
*  Input	:		mm(少数点3桁)/INCH(少数点3桁)
*  Return	: 		mm(少数点1or2桁)/INCH(少数点3桁)
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2004-10-04	V01m
********************************************************************************
*/
UNl		cnv_mi_mi_sur(UNl mm_bf)
{
	UNl		wk1;

	wk1 = mm_bf;
	if( SEQ_016_SV & BIT_6 ) {		//単位切替 mm/INCH 単位系(1:INCH)
	}
	else{
//2014/12/23
////		wk1 /= 10;
////		if (SV_POINT_A1 == 1) {
////			wk1 /= 10;
////		}
		if (SV_POINT_A1 == 0) {
			wk1 /= 1000;					//内部データ小数点以下3桁→小数点以下0桁表示
		}
		else if (SV_POINT_A1 == 1) {
			wk1 /= 100;						//内部データ小数点以下3桁→小数点以下1桁表示
		}
		else if (SV_POINT_A1 == 2) {
			wk1 /= 10;						//内部データ小数点以下3桁→小数点以下2桁表示
		}
		else {
			wk1 /= 1;						//内部データ小数点以下3桁→小数点以下3桁表示
		}

	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mm_inch
*  Function Name:	単位切替(mm→mm/INCH)
*  Input	:		mm(小数点 3桁)
*					0=なし／1=10倍／2=10の1なし
*
*  Return	: 		mm/INCH
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:FIT)田端		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_mm_inch(UNl mm_bf, UNi flg)
{
	UNl		wk1;

	wk1 = mm_bf;

	if( SEQ_016_SV & BIT_6 ) {		//単位切替 mm/INCH 単位系(1:INCH)
		wk1 *=10;					//1 INCH = 25.4mm
		wk1 /=254;

		if(flg != 2) {
			if( SEQ_016_SV & BIT_7 ) {	//単位 高精度(1:高精度)
				wk1 *=10;
			}
		}
	}
	else if(flg == 1){
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//単位 高精度(1:高精度)
			wk1 /= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_inch_mm
*  Function Name:	単位切替(mm/INCH→mm)
*  Input	:		mm/INCH
*					0=なし／1=10倍／2=10の1なし
*
*  Return	: 		mm(小数点 3桁)
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:FIT)田端		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_inch_mm(UNl inch_bf, UNi flg)
{
	UNl		wk1;

	wk1 = inch_bf;

	if( SEQ_016_SV & BIT_6 ) {				//単位切替 mm/INCH 単位系(1:INCH)
		wk1 *=254;							//1 INCH = 25.4mm
		wk1 /=10;

		if(flg != 2) {
			if( SEQ_016_SV & BIT_7 ) {			//単位 高精度(1:高精度)
				wk1 /=10;
			}
		}
	}
	else if(flg == 1){
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//単位 高精度(1:高精度)
			wk1 *= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_um_uinch
*  Function Name:	単位切替(um→um/uINCH)
*  Input	:		um(小数点なし)
*
*  Return	: 		mm/INCH
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_um_uinch(UNl um_bf)
{
	UNl		wk1;

	wk1 = um_bf;

	if( SEQ_016_SV & BIT_6 ) {		//単位切替 mm/INCH 単位系(1:INCH)
		wk1 *=10;					//1uINCH = 2.5um（本当は25.4um）
		wk1 /=25;
	}
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_uinch_um
*  Function Name:	単位切替(um/uINCH→um)
*  Input	:		umm/uINCH
*
*  Return	: 		um(小数点なし)
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_uinch_um(UNl uinch_bf)
{
	UNl		wk1;

	wk1 = uinch_bf;

	if( SEQ_016_SV & BIT_6 ) {				//単位切替 mm/INCH 単位系(1:INCH)
		wk1 *=25;							//1uINCH = 2.5um（本当は25.4um）
		wk1 /=10;
	}
	
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mm_inch2
*  Function Name:	単位切替(mm→INCH)
*  Input	:		mm(小数点 3桁)
*					0=なし／1=10倍／2=10の1なし
*
*  Return	: 		INCH
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
UNl		cnv_mm_inch2(UNl mm_bf, UNi flg)
{
	UNl		wk1;

	wk1 = mm_bf;

	wk1 *=100;
	wk1 /=254;

	if( (SEQ_016_SV & BIT_7) == 0 ) {	//単位 高精度(1:高精度)
		wk1 /=10;
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_inch_mm2
*  Function Name:	単位切替(INCH→mm)
*  Input	:		INCH
*					0=なし／1=10倍／2=10の1なし
*
*  Return	: 		mm(小数点 3桁)
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
UNl		cnv_inch_mm2(UNl inch_bf, UNi flg)
{
	UNl		wk1;

	wk1 = inch_bf;

	wk1 *=254;							//1 INCH = 25.4mm
	wk1 /=10;

	if( SEQ_016_SV & BIT_7 ) {			//単位 高精度(1:高精度)
		wk1 /=10;
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_um_uinch2
*  Function Name:	単位切替(um→uINCH)
*  Input	:		um(小数点なし)
*
*  Return	: 		uINCH
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_um_uinch2(UNl um_bf)
{
	UNl		wk1;

	wk1 = um_bf;

	wk1 *=10;					//1uINCH = 2.5um（本当は25.4um）
	wk1 /=25;

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_uinch_um2
*  Function Name:	単位切替(uINCH→um)
*  Input	:		umm
*
*  Return	: 		um(小数点なし)
*  Note		:単位切替 mm/INCHが有効時、変換
*
*  履 歴	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_uinch_um2(UNl uinch_bf)
{
	UNl		wk1;

	wk1 = uinch_bf;

	wk1 *=25;							//1uINCH = 2.5um（本当は25.4um）
	wk1 /=10;
	
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		SEI_csr_ichk(旧:SEIDAN_CSR_BACK)
*  Function Name:	生産カーソル位置初期化
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-27
********************************************************************************
*/
void	SEI_csr_ichk(void)
{
	UNs		bf, bf1;

	bf = SEQ_016_SV;
	bf &= (BIT_8 | BIT_12 | BIT_14);
	bf1 = SEI_ON1_LST;
	SEI_ON1_LST = bf;
	bf ^= bf1;

	if(bf != 0){
		bf1 = SW14_ON1_FLG & 0x0007;
		switch( bf1 ) {
			default:
				SW14_ON1_FLG = 0;
				break;

			case 0x0002:								//ﾄｰﾀﾙｶｳﾝﾀ
				if( 00 == (SEQ_016_SV & BIT_8) ) {		//ﾄｰﾀﾙｶｳﾝﾀの非表示？
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;

			case 0x0003:								//ﾛｯﾄｶｳﾝﾀ1
				if( 00 == (SEQ_016_SV & BIT_12) ) {		//ﾛｯﾄｶｳﾝﾀ1の非表示？
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;

			case 0x0004:								//ﾛｯﾄｶｳﾝﾀ2
				if( 00 == (SEQ_016_SV & BIT_14) ) {		//ﾛｯﾄｶｳﾝﾀ2の非表示
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEI_csr_mng
*  Function Name:	生産[基本]の専用　カーソル移動管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-30
********************************************************************************
*/
void	SEI_csr_mng(void)
{
	if(GAMEN_NO != 1){
		return;
	}

	if(WINDOW_NO != 00 ){
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//カーソル移動
		return;
	}

	switch (CSR_FLG)
	{
		case E_key_up:
			if(SW14_ON1_FLG == 4 || SW14_ON1_FLG == 0x84){	//ﾛｯﾄｶｳﾝﾀ2処理か？
				if(SW14_ON1_FLG & 0x80){					//今カウンタ補正機能中？
					if(COUNT_HOSEI_ADR != 00){				//反転アドレスデータ待避
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
					}
				}
				SW14_ON1_FLG = 0x03;						//ﾛｯﾄｶｳﾝﾀ1

				CSR_FLG = 5;								//カーソル表示位置指定
				CSR_FLG_CNT = 2;							//カーソル番号セット
				SV_FLG_CNT = 1;								//設定値番号セット
				SW_FLG_CNT = 1;								//ＳＷ番号セット
				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//カーソル移動(戻り値指定,移動)
			}
			break;

		case E_key_down:
			if(SW14_ON1_FLG == 3 || SW14_ON1_FLG == 0x83){	//ﾛｯﾄｶｳﾝﾀ1処理か？
				if(SEQ_016_SV & BIT_14){						//ﾛｯﾄｶｳﾝﾀ2有り？
					if(SW14_ON1_FLG & 0x80){				//今カウンタ補正機能中？
						if(COUNT_HOSEI_ADR != 00){			//反転アドレスデータ待避
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
						}
					}
					SW14_ON1_FLG = 0x04;					//ﾛｯﾄｶｳﾝﾀ2

					CSR_FLG = 5;							//カーソル表示位置指定
					CSR_FLG_CNT = 3;						//カーソル番号セット
					SV_FLG_CNT = 1;							//設定値番号セット
					SW_FLG_CNT = 1;							//ＳＷ番号セット
					CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動(戻り値指定,移動)
				}
			}
			break;

//V01z		case E_key_left:
//////			if( (SW14_ON1_FLG == 2 || SW14_ON1_FLG == 0x82 ) ||		/* ﾄｰﾀﾙｶｳﾝﾀ処理か？ */
//////				(SW14_ON1_FLG == 3 || SW14_ON1_FLG == 0x83 ) ||		/* ﾛｯﾄｶｳﾝﾀ1処理か？ */
//////				(SW14_ON1_FLG == 4 || SW14_ON1_FLG == 0x84) ) {		/* ﾛｯﾄｶｳﾝﾀ2処理か？ */
//////
//////				if(SW14_ON1_FLG & 0x80){				//今カウンタ補正機能中？
//////					if(COUNT_HOSEI_ADR != 00){			//反転アドレスデータ待避
//////						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
//////					}
//////				}
//////
//////				SW14_ON1_FLG_BAK3 = SW14_ON1_FLG;		//前の位置記憶
//////				CSR_FLG_CNT_BAK3 = CSR_FLG_CNT;			//前の位置記憶
//////
//////				SW14_ON1_FLG = 0x05;					//ｵｰﾊﾞﾗｲﾄﾞ
//////
//////				CSR_FLG = 5;							//カーソル表示位置指定
//////				CSR_FLG_CNT = 4;						//カーソル番号セット
//////				SV_FLG_CNT = 1;							//設定値番号セット
//////				SW_FLG_CNT = 1;							//ＳＷ番号セット
//////				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動(戻り値指定,移動)
//////			}
//////			break;
//////
//////		case E_key_right:
//////			if(SW14_ON1_FLG == 5){	//ｵｰﾊﾞﾗｲﾄﾞ処理か？
//////				SW14_ON1_FLG = SW14_ON1_FLG_BAK3;		//前の位置に戻す
//////
//////				CSR_FLG = 5;							//カーソル表示位置指定
//////				CSR_FLG_CNT = CSR_FLG_CNT_BAK3;			//前の位置に戻す
//////				SV_FLG_CNT = 1;							//設定値番号セット
//////				SW_FLG_CNT = 1;							//ＳＷ番号セット
//////				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動(戻り値指定,移動)
//////			}
//////			break;

		default:
			break;
	}
}


/*
********************************************************************************
*  Module Name:		EPM_MEM_CLR
*  Function Name:	電力モニタ用ワークメモリクリア
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2010-10-26
********************************************************************************
*/
void EPM_MEM_CLR(void)
{

	memset_long(&EPM_SEC_2_MESMIN_ADD[0], 0x0000, (sizeof(EPM_SEC_2_MESMIN_ADD)/4));
	EPM_SEC_MESMIN_CNT = 0;

	memset_long(&EPM_05MIN_BUF[0][0], 0x0000, (sizeof(EPM_05MIN_BUF)/4));
	memset_long(&EPM_10MIN_BUF[0][0], 0x0000, (sizeof(EPM_10MIN_BUF)/4));
	memset_long(&EPM_15MIN_BUF[0][0], 0x0000, (sizeof(EPM_15MIN_BUF)/4));
	memset_long(&EPM_20MIN_BUF[0][0], 0x0000, (sizeof(EPM_20MIN_BUF)/4));
	memset_long(&EPM_25MIN_BUF[0][0], 0x0000, (sizeof(EPM_25MIN_BUF)/4));
	memset_long(&EPM_30MIN_BUF[0][0], 0x0000, (sizeof(EPM_30MIN_BUF)/4));
	memset_long(&EPM_35MIN_BUF[0][0], 0x0000, (sizeof(EPM_35MIN_BUF)/4));
	memset_long(&EPM_40MIN_BUF[0][0], 0x0000, (sizeof(EPM_40MIN_BUF)/4));
	memset_long(&EPM_45MIN_BUF[0][0], 0x0000, (sizeof(EPM_45MIN_BUF)/4));
	memset_long(&EPM_50MIN_BUF[0][0], 0x0000, (sizeof(EPM_50MIN_BUF)/4));
	memset_long(&EPM_55MIN_BUF[0][0], 0x0000, (sizeof(EPM_55MIN_BUF)/4));
	memset_long(&EPM_60MIN_BUF[0][0], 0x0000, (sizeof(EPM_60MIN_BUF)/4));

	EPM_05MIN_POI = 0;
	EPM_10MIN_POI = 0;
	EPM_15MIN_POI = 0;
	EPM_20MIN_POI = 0;
	EPM_25MIN_POI = 0;
	EPM_30MIN_POI = 0;
	EPM_35MIN_POI = 0;
	EPM_40MIN_POI = 0;
	EPM_45MIN_POI = 0;
	EPM_50MIN_POI = 0;
	EPM_55MIN_POI = 0;
	EPM_60MIN_POI = 0;

	memset_long(&EPM_05MON_BUF[0][0], 0x0000, (sizeof(EPM_05MON_BUF)/4));
	memset_long(&EPM_10MON_BUF[0][0], 0x0000, (sizeof(EPM_10MON_BUF)/4));
	memset_long(&EPM_15MON_BUF[0][0], 0x0000, (sizeof(EPM_15MON_BUF)/4));
	memset_long(&EPM_20MON_BUF[0][0], 0x0000, (sizeof(EPM_20MON_BUF)/4));
	memset_long(&EPM_25MON_BUF[0][0], 0x0000, (sizeof(EPM_25MON_BUF)/4));
	memset_long(&EPM_30MON_BUF[0][0], 0x0000, (sizeof(EPM_30MON_BUF)/4));
	memset_long(&EPM_35MON_BUF[0][0], 0x0000, (sizeof(EPM_35MON_BUF)/4));
	memset_long(&EPM_40MON_BUF[0][0], 0x0000, (sizeof(EPM_40MON_BUF)/4));
	memset_long(&EPM_45MON_BUF[0][0], 0x0000, (sizeof(EPM_45MON_BUF)/4));
	memset_long(&EPM_50MON_BUF[0][0], 0x0000, (sizeof(EPM_50MON_BUF)/4));
	memset_long(&EPM_55MON_BUF[0][0], 0x0000, (sizeof(EPM_55MON_BUF)/4));
	memset_long(&EPM_60MON_BUF[0][0], 0x0000, (sizeof(EPM_60MON_BUF)/4));

	EPM_05MON_POI = 0;
	EPM_10MON_POI = 0;
	EPM_15MON_POI = 0;
	EPM_20MON_POI = 0;
	EPM_25MON_POI = 0;
	EPM_30MON_POI = 0;
	EPM_35MON_POI = 0;
	EPM_40MON_POI = 0;
	EPM_45MON_POI = 0;
	EPM_50MON_POI = 0;
	EPM_55MON_POI = 0;
	EPM_60MON_POI = 0;
}


/*
********************************************************************************
*  Module Name:		SEI_Worker_GET
*  Function Name:	生産管理データ取得
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_GET(void)
{
	SV0_WORKER_COD	= SV_WORKER_COD	;	//作業者ｺｰﾄﾞ取得
	SV0_ORDER_COD	= SV_ORDER_COD	;	//注番ｺｰﾄﾞ取得
	SV0_PLAN_CNT	= SV_PLAN_CNT	;	//計画数取得
}

/*
********************************************************************************
*  Module Name:		SEI_Worker_SET
*  Function Name:	生産管理データ登録
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_SET(void)
{
	SV_WORKER_COD	= SV0_WORKER_COD	;	//作業者ｺｰﾄﾞ確定退避
	SV_ORDER_COD	= SV0_ORDER_COD		;	//注番ｺｰﾄﾞ確定
	SV_PLAN_CNT		= SV0_PLAN_CNT		;	//計画数確定
	SV_BAD_CNT = 0;							//不良数ｸﾘｱ

//2015/09/20	FRAM_csum_set();

	SV0SR_WORKER_COD	= SV0_WORKER_COD	;		//作業開始時作業者ｺｰﾄﾞ
	SV0SR_ORDER_COD		= HEX_BCD4(SV0_ORDER_COD);	//作業開始時注番ｺｰﾄﾞ
	SV0SR_PLAN_CNT		= SV0_PLAN_CNT		;		//作業開始時計画数
	SV0SR_BAD_CNT		= SV_BAD_CNT		;		//作業開始時不良数
	SV0SR_KATA_NO		= PV_MLDNO1_F1		;		//作業開始時型番号
	memcpy_word(&SV0SR_KATA_NAME[0], &PV_MLDNO2_F1[0],7)	;	//作業開始時型名称
	memcpy_word(&SV0SR_KATA_MEMO[0], &PV_MLDNO3_F1[0],7)	;	//作業開始時型メモ

	SV0_WORK_STR_FLG = 0x5AA5;			// C/Bへ

	SV_WORKER_ENT_FLG = 0x5AA5;			//作業者登録有り

	FRAM_csum_set();						//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
}

/*
********************************************************************************
*  Module Name:		SEI_Worker_STP
*  Function Name:	生産管理作業終了
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_STP(void)
{
	SV0SP_WORKER_COD	= SV_WORKER_COD	;		//作業終了時作業者ｺｰﾄﾞ SV0_WORKER_COD
	SV0SP_ORDER_COD		= HEX_BCD4(SV_ORDER_COD);	//作業終了時注番ｺｰﾄﾞSV0_ORDER_COD
	SV0SP_PLAN_CNT		= SV_PLAN_CNT		;		//作業終了時計画数  SV0_PLAN_CNT
	SV0SP_BAD_CNT		= SV_BAD_CNT		;		//作業終了時不良数
	SV0SP_KATA_NO		= PV_MLDNO1_F1		;		//作業終了時型番号
	memcpy_word(&SV0SP_KATA_NAME[0], &PV_MLDNO2_F1[0],7)	;	//作業終了時型名称
	memcpy_word(&SV0SP_KATA_MEMO[0], &PV_MLDNO3_F1[0],7)	;	//作業終了時型メモ

	SV0_WORK_STP_FLG = 0xA55A;			// C/Bへ

	SV_WORKER_ENT_FLG = 0;				//作業者登録無し

	FRAM_csum_set();						//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
}


/*
********************************************************************************
*  Module Name:		FURIKO_SW_del
*  Function Name:	振子SWの表示／非表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2013-2-19		V06p
********************************************************************************
*/
void	FURIKO_SW_del(void)
{
	if( CSR_TBL_POS_NOW == 0 ) {						//カーソルは回転方式の位置
		if (SEQ_PAR_113 & BIT_15) {						//振子非表示指令（ON=非表示）
			SW_buff[2].SUB_NO |= BIT_15;				//振子の非表示の設定
		}
	}
}


/*
********************************************************************************
*  Module Name:		FURIKO_SW_chk
*  Function Name:	振子SWの表示／非表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2013-2-19		V06p
********************************************************************************
*/
void	FURIKO_SW_chk(void)
{
	if( CSR_TBL_POS_NOW == 0 ) {						//カーソルは回転方式の位置
		if (SEQ_PAR_113 & BIT_15) {						//振子非表示指令（ON=非表示）
			SW_buff[2].SUB_NO |= BIT_15;				//振子の非表示の設定
			disp_moji_s_paint(
				6,						//半角桁数
				368,					//X始点
				64,						//Y始点
				GAMENn_HEAD.scr_col,	//塗潰し色
				0x0202,					//X2倍/Y2倍
				LCD_VRAM
				);
		}
		else {
			if (SEQ_023_SV & BIT_8) {					//振子の仕様選択有効？
				SW_buff[2].SUB_NO &= ~BIT_15;			//振子の非表示の設定
				SWchg_disp_one(2);						//1ＳＷデータ情報　表示
			}
		}
	}
}


//;	*******************************************************************
//;	***																***
//;	***	荷重計バックアップ化け不具合調査プログラム					***	2007/10/05 V05i
//;	***																***
//;	*******************************************************************
void KJ_CHK_MEM_CLR(void)
{
	PV_OF_BAKL_X = PV_OF_BAKL;				//オフセット値左(1byte)				2007/10/30
	PV_OF_BAKR_X = PV_OF_BAKR;				//オフセット値右(1byte)				2007/10/30

	PV_OF_AVE_BAKL_X = PV_OF_AVE_BAKL;		//オフセット補正左(1word)			2007/10/30
	PV_OF_AVE_BAKR_X = PV_OF_AVE_BAKR;		//オフセット補正右(1word)			2007/10/30
	PV_OF_AVE_BAKT_X = PV_OF_AVE_BAKT;		//オフセット補正合計(1word)			2007/10/30

	PV_GAIN_BAK1L_X = PV_GAIN_BAK1L;		//最大歪み２０００左ゲイン(1word)	2007/10/30
	PV_GAIN_BAK1R_X = PV_GAIN_BAK1R;		//最大歪み２０００右ゲイン(1word)	2007/10/30
                      
	PV_GAIN_BAK2L_X = PV_GAIN_BAK2L;		//最大歪み１５００左ゲイン(1word)	2007/10/30
	PV_GAIN_BAK2R_X = PV_GAIN_BAK2R;		//最大歪み１５００右ゲイン(1word)	2007/10/30
                      
	PV_GAIN_BAK3L_X = PV_GAIN_BAK3L;		//最大歪み　８００左ゲイン(1word)	2007/10/30
	PV_GAIN_BAK3R_X = PV_GAIN_BAK3R;		//最大歪み　８００右ゲイン(1word)	2007/10/30
                      
	PV_GAIN_BAK4L_X = PV_GAIN_BAK4L;		//最大歪み　４００左ゲイン(1word)	2007/10/30
	PV_GAIN_BAK4R_X = PV_GAIN_BAK4R;		//最大歪み　４００右ゲイン(1word)	2007/10/30
                      
	PV_GAIN_BAK5L_X = PV_GAIN_BAK5L;		//最大歪み　２００左ゲイン(1word)	2007/10/30
	PV_GAIN_BAK5R_X = PV_GAIN_BAK5R;		//最大歪み　２００右ゲイン(1word)	2007/10/30

	KJ_CHK_CNT1		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ1 */
	KJ_CHK_CNT2		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ2 */
	KJ_CHK_CNT3		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ3 */
	KJ_CHK_CNT4		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ4 */
	KJ_CHK_CNT5		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ5 */
	KJ_CHK_CNT6		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ6 */
	KJ_CHK_CNT7		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ7 */
	KJ_CHK_CNT8		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ8 */
	KJ_CHK_CNT9		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ9 */
	KJ_CHK_CNT10	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ10 */
	KJ_CHK_CNT11	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ11 */
	KJ_CHK_CNT12	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ12 */
	KJ_CHK_CNT13	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ13 */
	KJ_CHK_CNT14	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ14 */
	KJ_CHK_CNT15	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ｶｳﾝﾀ15 */
	KJ_CHK_DAT0		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ0 */
	KJ_CHK_DAT1		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ1 */
	KJ_CHK_DAT2		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ2 */
	KJ_CHK_DAT3		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ3 */
	KJ_CHK_DAT4		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ4 */
	KJ_CHK_DAT5		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ5 */
	KJ_CHK_DAT6		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ6 */
	KJ_CHK_DAT7		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ7 */
	KJ_CHK_DAT8		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ8 */
	KJ_CHK_DAT9		= 0;                /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ9 */
	KJ_CHK_DAT10	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ10 */
	KJ_CHK_DAT11	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ11 */
	KJ_CHK_DAT12	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ12 */
	KJ_CHK_DAT13	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ13 */
	KJ_CHK_DAT14	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ14 */
	KJ_CHK_DAT15	= 0;               /* 荷重計ﾊﾞｯｸｱｱﾌﾟﾃﾞｰﾀ化け調査ﾃﾞｰﾀ15 */
}


/*
********************************************************************************
*  Function Name:	一定速度設定のクリア
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shimamura		ON:2014/09/25
********************************************************************************
*/
void	mmon_f_off(UNs t_no)
{
	UNs		no, fbit;

	no = CSR_buff[t_no].DATA_NO;

	if ( (no >= 97) && (no <= 101) ) {
		no -= 97;
		if ( (GAMEN_NO == 3) || (GAMEN_NO == 28) ) {
			/* ﾓｰｼｮﾝ1～5段目設定 */
			fbit = cBIT0;
		}
		else {
			/* ﾓｰｼｮﾝ6～10段目設定 */
			fbit = cBIT5;
		}

		fbit <<= no;

//2014/10/09		SV_MOT_FIX &= ~fbit;
		if (SV0_MOT_FIX & fbit) {
			SV0_MOT_FIX = 0;
		}
	}
}

							
/*** END ***/
