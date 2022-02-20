/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			データ設定の操作メイン処理												*/
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
#include	"dp_cpud.h"	//[MC-add 2013-11]
#include "dp_cpuab.h"							//DPRAM参照変数定義

/* 外部参照関数定義 -------------------------------------------------- */
extern	void	GRAPH_INIT(void);				//グラフ描画初期処理
extern	void	GRAPH_DISP(void);				//グラフ描画処理

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];

/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	dsp_Dataset(void);						//データ設定の管理

void	Data_sel_cam(void);						//ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)

void	SHARCH_gamen_15(void);					//検索入力時の画面移動
void	SW56_gamen_15(void);					//型ﾃﾞｰﾀ画面　SW56処理

void	MEMO_data_write(void);					//型ﾃﾞｰﾀ ﾒﾓ書込
void	KAT_data_read(void);					//型ﾃﾞｰﾀ 読込
void	KAT_data_write(void);					//型ﾃﾞｰﾀ 書込
void	KAT_read_sura_chk(void);				//型データ読込み時スライド設定値チェック

void	NAME_csr_mng(void);						//名称画面カーソル制御
void	KATname_inp(void);						//型名称 入力処理
void	KATname_cls(void);						//型名称 訂正処理
void	KATname_ref(UNs, UNs *);				//カム名称リフレッシュ
void	CSR_disp_on(UNs);						//裏画面反転
UNs		NAME_leng_chk(UNb *, UNs);				//名称の入力文字数をチェック

void	CAMname_inp(void);						//カム名称 入力処理
void	CAMname_cls(void);						//カム名称 訂正処理
UNi		CAMname_inp_chk(void);					//カム名称入力可チェック
void	CAMname_touroku(void);					//カム名称登録
void	CAMname_sw_ent(void);					//汎用出力選択
void	CAM_name_ref(void);						//ﾛｰﾀﾘｶﾑ汎用選択種別に対応したｶﾑ名称の更新


/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs *	KAT_sv_memo_tbl[101];
extern	const	UNs *	Camcsr_Name_Tbl[20];
extern	const	UNs *	Camcsr_Name_TblSV[20];
extern	const	UNs *	Camcsr_Name_Tbl1[20];
extern	const	UNs *	Camcsr_Name_TblSW[16];


/*
********************************************************************************
*  Module Name:		dsp_Dataset
*  Function Name:	データ設定の管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-04
********************************************************************************
*/
void	dsp_Dataset(void)
{
	UNs	*bf_p, i, j;

	switch(disp_stg_sel) {

		case E_dstg_init:		//データ設定[基本]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					ROTTO_chk();								//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

//2次	MOV	SET_SPM_LST,0				;
//2次	CALL	SETSPM_SV_CHG		;/* 生産ＳＰＭＳＶ変更処理 			*/
					SURA_CHG_LST = 0;
					SURA_sv_chg();								//スライド自動調節ＳＶ変更処理

					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(なし)
//V06n							disp_stg_sel = E_dstg_Lang;		//データ設定[言語設定]へ		V06m
//V06n							WINDOW_NO = 24;
//V06n							WIN_gamen_disp();				//ウインドウ画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							CAR_mkssi_set();					//単位切換  V01u
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_PAR_107 & BIT_0){			//機能選択1(型ﾃﾞｰﾀ管理　1:有)
								disp_stg_sel = E_dstg_kata;		//データ設定[型番号]へ
								CSR_POS_G15 = 0xff;				//カーソル表示位置を現在の番号の位置へ
								GAMEN_NO = 15;
								GAMEN_disp();					//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ
							GAMEN_NO = 13;
							GAMEN_disp();						//画面表示
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7	//V06b
							if (SEQ_PAR_107 & BIT_4) {
								SV0_TAL1_CNT = PV_TOTLC1_B3;
								SV0_LOT1_CNT = PV_LOTCT1_B1;
								SV0_LOT2_CNT = PV_LOTCT2_B1;
								disp_stg_sel = E_dstg_cntc;		//データ設定[ｶｳﾝﾄ値修正]へ
								WINDOW_NO = 22;
								WIN_gamen_disp();				//ウインドウ画面表示
							}
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG データ ENT
						KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
						ROTTO_chk();							//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

						mmon_trans_put();						//回転方式によるﾃﾞｰﾀの格納

						SW16data_onset(0xff, 07);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

						SW16data_onset(0xff, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else{									//key code SW5/SW6(立下り)
						SW16data_onset(0x00, 07);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0x00, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_mset:		//データ設定[モーション設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					Key_Ent_sv();								//設定値の確定
					mmon_sv_chg(i);								//角度&位置の設定値変更
					mmon_tchk_disp(0x00);						//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2(なし)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_mcg;			//データ設定[モーショングラフ]へ
							GAMEN_NO = 29;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
							break;

						case E_key_sw5:			//key code SW5
							if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWﾃｰﾌﾞﾙ個数
								CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								SWchg_ent();								//SW CHG データ ENT
								mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
							}
							SEI_test_out_sw5();								//生産設定ﾃｽﾄ出力処理(SW6)	V01m
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示

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
								mmon_kaiten_chg();								//回転方式による設定値 切換え
								FURIKO_SW_chk();								//下往復（振子）の非表示セット		//V06p
							}
//V01z							else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
							else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
									(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6下段ｷｬﾗｸﾀ
									SWchg_mmon_ent();								//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
									mmon_trans_put();								//回転方式によるﾃﾞｰﾀの格納
								}
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 74) {	//SW6下段ｷｬﾗｸﾀ		V06p
									//速度のﾘﾐｯﾄ値入力
									mmon_spd_in();
								}
							}
							/* V00m */
							else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
		 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							}
							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57) {
			 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							}
							break;

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
		case E_dstg_mset2:		//データ設定[モーション設定6～10]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					Key_Ent_sv();								//設定値の確定
					mmon_sv_chg(i);								//角度&位置の設定値変更
					mmon_tchk_disp(0x00);						//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2(なし)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_mcg;			//データ設定[モーショングラフ]へ
							GAMEN_NO = 29;
							GAMEN_disp();						//画面表示

							GRAPH_INIT();						//グラフ描画初期処理
							GRAPH_DISP();						//グラフ描画処理
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
							break;

						case E_key_sw5:			//key code SW5
							if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWﾃｰﾌﾞﾙ個数
								CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								SWchg_ent();								//SW CHG データ ENT
								mmon_trans_put();							//回転方式によるﾃﾞｰﾀの格納
							}
							SEI_test_out_sw5();								//生産設定ﾃｽﾄ出力処理(SW6)	V01m
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
								mmon_kaiten_chg();								//回転方式による設定値 切換え
								FURIKO_SW_chk();								//下往復（振子）の非表示セット		//V06p
							}
//V01z							else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
							else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
									(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
								if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6下段ｷｬﾗｸﾀ
									SWchg_mmon_ent();								//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
									mmon_trans_put();								//回転方式によるﾃﾞｰﾀの格納
								}
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 74) {	//SW6下段ｷｬﾗｸﾀ		V06p
									//速度のﾘﾐｯﾄ値入力
									mmon_spd_in();
								}
							}
							/* V00m */
							else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
		 						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							}
							break;

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

		case E_dstg_mcg:		//データ設定[モーショングラフ]へ
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
							break;
					}
					break;
			}
			break;

		case E_dstg_ksin:		//データ設定[加振機能設定]		V05r		======================================
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
								GAMEN_NO = 19;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if(SEQ_018_SV & 0x0700) {		// V05g
									disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
									GAMEN_NO = 20;
								}
								else {
									disp_stg_sel = E_dstg_tms3;			//データ設定[ミスフィード2]へ
									GAMEN_NO = 68;
								}
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//ロータリカム１～８ 有
									GAMEN_NO = 21;
									disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
								}
								else{								//ロータリカム９～１６ 有
									GAMEN_NO = 22;
									disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]
								}
								GAMEN_disp();						//画面表示
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG データ ENT
						KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ

						SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

						SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else{									//key code SW5/SW6(立下り)
						SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_tms1:		//データ設定[エジェクタ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if(SEQ_018_SV & 0x0700) {		// V05g
									disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
									GAMEN_NO = 20;
								}
								else {
									disp_stg_sel = E_dstg_tms3;			//データ設定[ミスフィード2]へ
									GAMEN_NO = 68;
								}
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//ロータリカム１～８ 有
									GAMEN_NO = 21;
									disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
								}
								else{								//ロータリカム９～１６ 有
									GAMEN_NO = 22;
									disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]
								}
								GAMEN_disp();						//画面表示
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//仕様設定No.139
								disp_stg_sel = E_dstg_ksin;			//データ設定[加振機能設定]へ
								GAMEN_NO = 101;
								GAMEN_disp();						//画面表示
							}
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG データ ENT
						KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ

						SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

						SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else{									//key code SW5/SW6(立下り)
						SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_tms2:		//データ設定[ミスフィード1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
								GAMEN_NO = 19;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
							/* V01d */
							if (SEQ_018_SV & BIT_11) {
								disp_stg_sel = E_dstg_tms3;			//データ設定[ミスフィード2]へ
								GAMEN_NO = 68;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//ロータリカム１～８ 有
									GAMEN_NO = 21;
									disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
								}
								else{								//ロータリカム９～１６ 有
									GAMEN_NO = 22;
									disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]
								}
								GAMEN_disp();						//画面表示
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//仕様設定No.139
								disp_stg_sel = E_dstg_ksin;			//データ設定[加振機能設定]へ
								GAMEN_NO = 101;
								GAMEN_disp();						//画面表示
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5ﾃﾞｰﾀ処理番号
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

								SWchg_ent();						//SW CHG データ ENT
								KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ
							}
							else{
								SEI_test_out_sw5();					//生産設定ﾃｽﾄ出力処理(SW5)
							}
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5ﾃﾞｰﾀ処理番号
								SW_FLG_CNT = 2;
							}
							else{
								SW_FLG_CNT = 1;
							}
							SVSW_tbl_enzan();						//ＳＶＳＷテーブルアドレス演算
							SWchg_ent();							//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ

							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
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

		/* V01d */
		case E_dstg_tms3:		//データ設定[ミスフィード2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
								GAMEN_NO = 19;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_018_SV & 0x0700) {		// V05g
								disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
								GAMEN_NO = 20;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//ロータリカム１～８ 有
									GAMEN_NO = 21;
									disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
								}
								else{								//ロータリカム９～１６ 有
									GAMEN_NO = 22;
									disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]
								}
								GAMEN_disp();						//画面表示
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//仕様設定No.139
								disp_stg_sel = E_dstg_ksin;			//データ設定[加振機能設定]へ
								GAMEN_NO = 101;
								GAMEN_disp();						//画面表示
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5ﾃﾞｰﾀ処理番号
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

								SWchg_ent();						//SW CHG データ ENT
								KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ
							}
							else{
								SEI_test_out_sw5();					//生産設定ﾃｽﾄ出力処理(SW5)
							}
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5ﾃﾞｰﾀ処理番号
								SW_FLG_CNT = 2;
							}
							else{
								SW_FLG_CNT = 1;
							}
							SVSW_tbl_enzan();						//ＳＶＳＷテーブルアドレス演算
							SWchg_ent();							//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ

							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
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

		case E_dstg_tms4:		//データ設定[ロータリカム1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
								GAMEN_NO = 19;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if(SEQ_018_SV & 0x0700) {		// V05g
									disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
									GAMEN_NO = 20;
								}
								else {
									disp_stg_sel = E_dstg_tms3;			//データ設定[ミスフィード2]へ
									GAMEN_NO = 68;
								}
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT2_GAMEN_NON != 0xff){			//ロータリカム９～１６ 無　？
								disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]へ
								GAMEN_NO = 22;
								GAMEN_disp();					//画面表示
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//仕様設定No.139
								disp_stg_sel = E_dstg_ksin;			//データ設定[加振機能設定]へ
								GAMEN_NO = 101;
								GAMEN_disp();						//画面表示
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
							ROTTO_chk();							//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
//							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

							i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
							if( i < 0x80 || i >= 0x90 ){				//カム名称画面移動処理？
								SW16data_onset(0xff, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							else {										//YES
								CAM_NAME_NO = (i - 0x80);				//変更カム名称番号読込
								disp_stg_sel = E_dstg_tms6;				//データ設定[ロータリカム名称]へ
								GAMEN_NO = 12;
								GAMEN_disp();						//画面表示
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

		case E_dstg_tms5:		//データ設定[ロータリカム2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
								GAMEN_NO = 19;
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if(SEQ_018_SV & 0x0700) {		// V05g
									disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
									GAMEN_NO = 20;
								}
								else {
									disp_stg_sel = E_dstg_tms3;			//データ設定[ミスフィード2]へ
									GAMEN_NO = 68;
								}
								GAMEN_disp();						//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT1_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms4;			//データ設定[ロータリカム1]へ
								GAMEN_NO = 21;
								GAMEN_disp();						//画面表示
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//仕様設定No.139
								disp_stg_sel = E_dstg_ksin;			//データ設定[加振機能設定]へ
								GAMEN_NO = 101;
								GAMEN_disp();						//画面表示
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG データ ENT
							KAT_DATCHG_FLG = 0xff;					//型データ変更フラグ
							ROTTO_chk();							//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
                            
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
//							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

							i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
							if( i < 0x80 || i >= 0x90 ){				//カム名称画面移動処理？
								SW16data_onset(0xff, 0x08);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							else {										//YES
								CAM_NAME_NO = (i - 0x80);				//変更カム名称番号読込
								disp_stg_sel = E_dstg_tms6;				//データ設定[ロータリカム名称]へ
								GAMEN_NO = 12;
								GAMEN_disp();						//画面表示
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

		case E_dstg_tms6:		//データ設定[ロータリカム名称]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					CAMname_inp();								//カム名称 入力処理
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {

						case E_key_sw6:			//key code SW6
//							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							CAMname_touroku();						//カム名称登録
//							break;
						case E_key_sw1:			//key code SW1
							CSR_FLG_CNT = CSR_FLG_CNT_BAK;			//現在のカーソル位置カウント
							SV_FLG_CNT = SV_FLG_CNT_BAK;
							SW_FLG_CNT = SW_FLG_CNT_BAK;
							CSR_FLG = 5;

							GAMEN_NO = GAMEN_NO_CAM;
							if(GAMEN_NO == 21){
								disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
							}
							else{
								disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]へ
							}
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2(なし)
							break;
						case E_key_sw3:			//key code SW3(なし)
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ
							GAMEN_NO = 13;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							if( 19 == CSR_buff[CSR_TBL_POS_NOW].SW5_DN ){		//選択？
								CAMname_sw_ent();								//汎用出力選択
							}
							else if(20 == CSR_buff[CSR_TBL_POS_NOW].SW5_DN){	//訂正？
								CAMname_cls();									//カム名称訂正処理
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_kata:		//データ設定[型番号]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					if(SV_DATA_CHG == 0xff){					//データ変更有り？
						CSR_MOVE_NON = 0xff;					//ENT KEY ｶｰｿﾙ移動禁止
						Key_Ent_sv();							//設定値の確定
						CSR_MOVE_NON = 0x00;					//ENT KEY ｶｰｿﾙ移動

						SHARCH_gamen_15();						//検索入力時の画面移動
					}
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							if(MLD_100_GNO != 00) {				//型管理データ戻り処理
								MLD_100_GNO--;					//サブ画面ナンバー更新
								CSR_POS_G15 = 0x00;				//カーソル表示位置を名称の先頭へ
								GAMEN_NO = 15;
								GAMEN_disp();					//画面表示
							}
							break;
						case E_key_sw3:			//key code SW3
//V06n							if(MLD_100_GNO < 0x09 && MLD_100_FLG == 0xaa ) {	//型管理データ戻り処理
							if ( ( MLD_100_GNO <  9 && MLD_100_FLG == 0xaa ) ||
								 ( MLD_100_GNO < 19 && MLD_100_FLG == 0xbb ) )	 {	//型管理データ戻り処理
								MLD_100_GNO++;					//サブ画面ナンバー更新
								CSR_POS_G15 = 0x00;				//カーソル表示位置を名称の先頭へ
								GAMEN_NO = 15;
								GAMEN_disp();					//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							CSR_FLG_CNT = 1;
							CSR_FLG = 5;
							CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);	//カーソル移動
//?	CALL	SPATH_DISP			;/* 生産設定のミスフィード表示時のスペース表示   */
							Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
							Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5:			//key code SW5
						case E_key_sw6:			//key code SW6
							SW56_gamen_15();					//型ﾃﾞｰﾀ画面　SW56処理
							break;
					}
					break;
			}
			break;

		case E_dstg_name:		//データ設定[型番号名称]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					KATname_inp();								//型名称 入力処理
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							CSR_POS_G15 = 0x55;					//カーソル表示位置を現在の番号の位置へ
							disp_stg_sel = E_dstg_kata;			//データ設定[型番号]へ
							GAMEN_NO = 15;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2(なし)
						case E_key_sw3:			//key code SW3(なし)
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							KATname_cls();						//型名称 訂正処理

							SW16data_onset(0xff, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							KAT_data_write();					//型ﾃﾞｰﾀ 書込

							disp_stg_sel = E_dstg_kata;			//データ設定[型番号]へ
							GAMEN_NO = 15;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
//						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//							SW16data_onset(0x00, 8);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_dstg_memo:		//データ設定[型番号メモ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					KATname_inp();								//型名称 入力処理
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_kata;			//データ設定[型番号]へ
							GAMEN_NO = 15;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2(なし)
						case E_key_sw3:			//key code SW3(なし)
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							KATname_cls();						//型名称 訂正処理

							SW16data_onset(0xff, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							MEMO_data_write();					//型ﾃﾞｰﾀ ﾒﾓ書込

							disp_stg_sel = E_dstg_kata;			//データ設定[型番号]へ
							GAMEN_NO = 15;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
//						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(0x00, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
//							SW16data_onset(0x00, 8);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_dstg_mmon:		//データ設定[メンテナンスモニタ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_ksel;			//データ設定[機能選択]へ
							GAMEN_NO = 14;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_PAR_051 & cBIT15) {			//V06n
								disp_stg = 03;						//システム設定画面へ
								disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
								GAMEN_NO = 31;
								GAMEN_disp();						//画面表示
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7	//V06n
							disp_stg_sel = E_dstg_Lang;		//データ設定[言語設定]へ
							WINDOW_NO = 24;
							WIN_gamen_disp();				//ウインドウ画面表示
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw6_down) {	//key code SW6(立下り)
						SW16data_onset(0x00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)

						SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_ksel:		//データ設定[機能選択]へ
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(なし)
					Key_Ent_sv();								//設定値の確定			// V05j
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ
							GAMEN_NO = 13;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3(なし)
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_PAR_051 & cBIT15) {			//V06n
								disp_stg = 03;						//システム設定画面へ
								disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
								GAMEN_NO = 31;
								GAMEN_disp();						//画面表示
							}
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5_down ) {	//key code SW5(立下り)
						SW16data_onset(0x00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					else if(KEY_DATA_CODE == E_key_sw5){	//key code SW5
						SWchg_ent();							//SW CHG データ ENT

						SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
					}
					break;
			}
			break;

		case E_dstg_cntc:		//データ設定[ｶｳﾝﾄ値修正]	//V06b
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(なし)
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
							CAR_mkssi_set();					//単位切換  V01u
							GAMEN_NO = 28;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_PAR_107 & BIT_0){			//機能選択1(型ﾃﾞｰﾀ管理　1:有)
								disp_stg_sel = E_dstg_kata;		//データ設定[型番号]へ
								CSR_POS_G15 = 0xff;				//カーソル表示位置を現在の番号の位置へ
								GAMEN_NO = 15;
								GAMEN_disp();					//画面表示
							}
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ
							GAMEN_NO = 13;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_dstg_Lang:		//データ設定[言語設定]			//V06m
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(なし)
//V06n							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
//V06n							GAMEN_NO = 17;
							disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ
							GAMEN_NO = 13;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr1:		//生産[作業開始1]作業者ｺｰﾄﾞの入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();						//設定値の確定

					disp_stg_sel = E_dstg_wkstr2;		//生産[作業開始2]へ
					WINDOW_NO = 43;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
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
							disp_stg_sel = E_dstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 44;
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

		case E_dstg_wkstr2:		//生産[作業開始2]作業者ｺｰﾄﾞの確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_WORKER_COD = SV0_WORKER_COD_BAK;	//前に戻す

							disp_stg_sel = E_dstg_wkstr1;		//生産[作業開始1]へ
							WINDOW_NO = 42;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_dstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 44;
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

		case E_dstg_wkstr3:		//生産[作業開始3]注番ｺｰﾄﾞの入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定

					disp_stg_sel = E_dstg_wkstr4;		//生産[作業開始4]へ
					WINDOW_NO = 45;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
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
							disp_stg_sel = E_dstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 46;
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

		case E_dstg_wkstr4:		//生産[作業開始4]注番ｺｰﾄﾞの確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_ORDER_COD = SV0_ORDER_COD_BAK;	//前に戻す

							disp_stg_sel = E_dstg_wkstr3;		//生産[作業開始3]へ
							WINDOW_NO = 44;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_dstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 46;
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

		case E_dstg_wkstr5:		//生産[作業開始5]計画数の入力		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定

					disp_stg_sel = E_dstg_wkstr6;		//生産[作業開始6]へ
					WINDOW_NO = 47;
					WIN_gamen_disp();					//ウインドウ画面表示

					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
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
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//作業者あり？
								SEI_Worker_STP();					//生産管理作業終了
							}

							CSR_TBL_POS_NOW = KAT_RD_CSR_POS;
							KAT_data_read();					//型データ読込

							SEI_Worker_SET();					//作業ﾃﾞｰﾀ確定

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

		case E_dstg_wkstr6:		//生産[作業開始6]計画数の確認		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//データ設定[基本]へ
							GAMEN_NO = 17;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_PLAN_CNT = SV0_PLAN_CNT_BAK;		//前に戻す

							disp_stg_sel = E_dstg_wkstr5;		//生産[作業開始5]へ
							WINDOW_NO = 46;
							WIN_gamen_disp();					//ウインドウ画面表示

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6	//YES
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//作業者あり？
								SEI_Worker_STP();					//生産管理作業終了
							}

							CSR_TBL_POS_NOW = KAT_RD_CSR_POS;
							KAT_data_read();					//型データ読込

							SEI_Worker_SET();					//作業ﾃﾞｰﾀ確定

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




	}
}


/*
********************************************************************************
*  Module Name:		Data_sel_cam
*  Function Name:	ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-06
********************************************************************************
*/
void	Data_sel_cam(void)
{
	UNs		i;

	i = GAMEN_NO_CAM;

	if(CAM_GAMEN_NON == 00){					//ﾀｲﾐﾝｸﾞ設定 有 ?
		if( i <= 19 || i >= 23 ){				//前回データ有り
			if(00 != EJE_check()){				//エジェクタ有無チェック
				i = 19;
				disp_stg_sel = E_dstg_tms1;		//データ設定[エジェクタ]へ
				goto DATA_SEL_800;
			}
		}
		else if( i == 20 ){
 			if(00 != MIS_check()){				//ミスフィード有無チェック
				i = 20;
				disp_stg_sel = E_dstg_tms2;		//データ設定[ミスフィード1]へ
				goto DATA_SEL_800;
			}
		}
		else{
			if( 00 != ROT1_check() ) {			//ロータリカム１～８有無チェック
				i = 21;
				disp_stg_sel = E_dstg_tms4;		//データ設定[ロータリカム1]へ
				goto DATA_SEL_800;

			}
			else if( 00 != ROT2_check() ) {		//ロータリカム９～１６有無チェック
				i = 22;
				disp_stg_sel = E_dstg_tms5;		//データ設定[ロータリカム2]
				goto DATA_SEL_800;
			}
		}

//遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
		if(00 != EJE_check()){					//エジェクタ有無チェック
			i = 19;
			disp_stg_sel = E_dstg_tms1;			//データ設定[エジェクタ]へ
		}
 		else if(00 != MIS_check()){				//ミスフィード有無チェック
			i = 20;
			disp_stg_sel = E_dstg_tms2;			//データ設定[ミスフィード1]へ
		}
		else if( 00 != ROT1_check() ) {			//ロータリカム１～８有無チェック
			i = 21;
			disp_stg_sel = E_dstg_tms4;			//データ設定[ロータリカム1]へ
		}
		else if( 00 != ROT2_check() ) {			//ロータリカム９～１６有無チェック
			i = 22;
			disp_stg_sel = E_dstg_tms5;			//データ設定[ロータリカム2]
		}
		else{
			return;
		}

DATA_SEL_800:
		GAMEN_NO = i;
		GAMEN_disp();						//画面表示
	}
}


/*
********************************************************************************
*  Module Name:		SHARCH_gamen_15
*  Function Name:	検索入力時の画面移動
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-05
********************************************************************************
*/
void	SHARCH_gamen_15(void)
{
	UNs		i, j;

//V06n	if( PV_SEARCH_C15 < 11 ||
//V06n		MLD_100_FLG == 0xaa ) {				//型管理 1～100が有効
	if( PV_SEARCH_C15 < 11 ||
		MLD_100_FLG != 0 ) {				//型管理 1～100が有効

		i = PV_SEARCH_C15 / 10;
		j = PV_SEARCH_C15 % 10;
		if(j == 0){							//あまりが０の時は１つ少ない画面番号です。
			i --;
		}
		MLD_100_GNO = i;
		CSR_POS_G15 = 0xaa;					//カーソル表示位置を現在の番号の位置へ

		GAMEN_NO = 15;
		GAMEN_disp();						//画面表示
	}
}


/*
********************************************************************************
*  Module Name:		SW56_gamen_15
*  Function Name:	型ﾃﾞｰﾀ画面　SW56処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-05
********************************************************************************
*/
void	SW56_gamen_15(void)
{
	UNs		i, j, *bf_p;
	UNs		bit;

//SW56_G15_100:
	if(CSR_CNT != 00){							//ｶｰｿﾙがないときは処理しない

		if( CSR_FLG_CNT == 1 ) {				//検索ﾓｰﾄﾞ？
			return;								//Yes
		}


//V06p
		i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
		if ( (0xa0 <= i) && (i <= 0xa9) ) {
			i &= 0x000f;
			bit = BIT_0;
		}
		else if ( (0xab <= i) && (i <= 0xb4) ) {
			i -= 0xab;
			i &= 0x000f;
			bit = BIT_0;
		}
		else {
			bit = 0;
		}
		if (bit) {
			bit<<=i;
			if (PV0_KATRD_BIT & bit) {					//回転方式不一致
				return;
			}
		}


		if(KEY_DATA_CODE == E_key_sw5) {		//key code SW5
			i = CSR_buff[CSR_TBL_POS_NOW].XY_POS;
			i >>= 4;
			i &= 0x003f;
			if( i >= 20 ){								//メモ入力モード？
//SW56_G15_150:											//メモ入力
				i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
				i -= 0xab;
				i += 1;										//0ABH～0A4H = 1～１０に対応しているから
				i += (MLD_100_GNO * 10);					//型管理番号を１０倍して型管理番号を細工する
				PV_MLDNO1_F0 = i;							//型ﾃﾞｰﾀ 書込画面用の型番号

				bf_p = KAT_sv_memo_tbl[i];					//型ﾃﾞｰﾀ メモ領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
				memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

				disp_stg_sel = E_dstg_memo;					//データ設定[型番号メモ]へ
				GAMEN_NO = 23;
				GAMEN_disp();								//画面表示
			}
			else if(PV_MLDMES_C1 == 00){					//メッセージ表示中
//SW56_G15_110:
				i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
				i &= 0x000f;
				i += 1;										//0A0H～0A9H = 1～１０に対応しているから
				i += (MLD_100_GNO * 10);					//型管理番号を１０倍して型管理番号を細工する
				PV_MLDNO1_F0 = i;							//型ﾃﾞｰﾀ 書込画面用の型番号

				bf_p = KAT_sv_name_tbl[i];					//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
				memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

				disp_stg_sel = E_dstg_name;					//データ設定[型番号名称]へ
				GAMEN_NO = 16;
				GAMEN_disp();								//画面表示
			}
			else{											//YES 必ず読込だけ
//SW56_G15_320:
				if (SEQ_PAR_113 & BIT_9) {					//仕様設定No.135「KOMTRAX」&& 機能選択1「型ﾃﾞｰﾀ管理」		V06c
					KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

					SEI_Worker_GET();
					disp_stg_sel = E_dstg_wkstr1;			//生産[作業開始1]へ
					WINDOW_NO = 42;
					WIN_gamen_disp();						//ウインドウ画面表示

					SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//今までの作業者ｺｰﾄﾞ退避
					SV0_ORDER_COD_BAK	= SV0_ORDER_COD;		//今までの注番ｺｰﾄﾞ退避
					SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//今までの計画数退避
				}
				else {
					KAT_data_read();							//型データ読込
				}
			}
		}
//SW56_G15_200:
		else{									//key code SW6
			i = CSR_buff[CSR_TBL_POS_NOW].XY_POS;
			i >>= 4;
			i &= 0x003f;
			if( i < 20 ){								//型データ　モード？
				if(PV_MLDMES_C1 == 00 &&				//メッセージ表示中
					00 == (SEQ_PAR_107 & BIT_9) ) {		//読込時の自動書込機能有り

					if(KAT_DATCHG_FLG != 0){			//ﾃﾞｰﾀ変更有り？
//SW56_G15_220:
						PV_MLDMES_C1 = 5;				//メッセージ表示
						SWchg_disp();					//ＳＷデータ情報　表示
						SW56_dncara_disp(37, 7);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
						SW56_dncara_disp(38, 8);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
						Under_grph();											//下段のグラフィックセット
						Lcd_line(00, 12, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
						Lcd_line(01, 12, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
						Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
					}
					else{
//SW56_G15_320:
						if (SEQ_PAR_113 & BIT_9) {					//仕様設定No.135「KOMTRAX」&& 機能選択1「型ﾃﾞｰﾀ管理」		V06c
							KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

							SEI_Worker_GET();
							disp_stg_sel = E_dstg_wkstr1;			//生産[作業開始1]へ
							WINDOW_NO = 42;
							WIN_gamen_disp();						//ウインドウ画面表示

							SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//今までの作業者ｺｰﾄﾞ退避
							SV0_ORDER_COD_BAK	= SV0_ORDER_COD;		//今までの注番ｺｰﾄﾞ退避
							SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//今までの計画数退避
						}
						else {
							KAT_data_read();					//型データ読込
						}
					}
				}
				else{								//型ﾃﾞｰﾀを書込み→読込む
//SW56_G15_300:
					PV_MLDNO1_F0 = PV_MLDNO1_F1;				//型ﾃﾞｰﾀ 書込画面用の型番号
					bf_p = KAT_sv_name_tbl[PV_MLDNO1_F0];		//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
					memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

					KAT_data_write();							//型ﾃﾞｰﾀ 書込
//SW56_G15_320:
					if (SEQ_PAR_113 & BIT_9) {					//仕様設定No.135「KOMTRAX」&& 機能選択1「型ﾃﾞｰﾀ管理」		V06c
						KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

						SEI_Worker_GET();
						disp_stg_sel = E_dstg_wkstr1;			//生産[作業開始1]へ
						WINDOW_NO = 42;
						WIN_gamen_disp();						//ウインドウ画面表示

						SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//今までの作業者ｺｰﾄﾞ退避
						SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//今までの注番ｺｰﾄﾞ退避
						SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//今までの計画数退避
					}
					else {
						KAT_data_read();							//型データ読込
					}
				}
			}
//SW56_G15_500:
//SW56_G15_900:
			SW16data_onset(0xff, KEY_DATA_CODE+2);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
		}
	}
//SW56_G15_END:
	return;
}


/*
********************************************************************************
*  Module Name:		MEMO_data_write
*  Function Name:	型ﾃﾞｰﾀ ﾒﾓ書込
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	MEMO_data_write(void)
{
	UNs		*bf_p;
	UNi		i;

	i = PV_MLDNO1_F0;
	bf_p = KAT_sv_memo_tbl[i];					//型ﾃﾞｰﾀ メモ領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
	memcpy_word(bf_p, &PV_MLDNO2_F0[0], 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

	FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	FRAM_KAT_csum_set();						//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

}


/*
********************************************************************************
*  Module Name:		KAT_data_read
*  Function Name:	型ﾃﾞｰﾀ 読込
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-05
********************************************************************************
*/
void	KAT_data_read(void)
{
	UNs		i, *bf_p;

	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
	i &= 0x000f;
	i += 1;										//0A0H～0A9H = 1～１０に対応しているから
	i += (MLD_100_GNO * 10);					//型管理番号を１０倍して型管理番号を細工する

	kata_load(i, &FRAM_KAT_TOP);				//型データをFROMから読込み

	if(00 == (SEQ_PAR_078 & BIT_0 ) ){			//型ﾃﾞｰﾀ　BCC正常？
		
		if ( 9 < SV_HAN_P ) {	//V06n
			SV_HAN_P = 0;
		}
		if ( 9 < SV_HAN_S ) {	//V06n
			SV_HAN_S = 0;
		}

		PV_TOTLC1_B3 = PV_TOTLC1_B3_KAT;			//トータルカウンタ１実測値をコピー
		PV_LOTCT1_B4 = PV_LOTCT1_B4_KAT;			//ロットカウンタ１実測値をコピー
		PV_TOTLC2_B31 = PV_TOTLC2_B31_KAT;			//未使用
		PV_LOTCT2_B41 = PV_LOTCT2_B41_KAT;			//ロットカウンタ２実測値をコピー

		bf_p = KAT_sv_name_tbl[i];					//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
		memcpy_word(&PV_MLDNO2_F1[0], bf_p, 8);		//型ﾃﾞｰﾀ 書込画面用の型名称
		bf_p = KAT_sv_memo_tbl[i];					//型ﾃﾞｰﾀ メモ領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
		memcpy_word(&PV_MLDNO3_F1[0], bf_p, 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

		PV_MLDNO1_F1 = i;							//型ﾃﾞｰﾀ 書込画面用の型番号

//		MOV	SVSW_CHG_FLG,10111111B			;
		SVSW_CHG_FLG = 0xff;
		ONOFF_sub();								//仕様有り無しによる入切制御

		mmon_sel_chk();								//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
		mmon_trans_get();							//回転方式によるﾃﾞｰﾀの取得

		ROTTO_chk();								//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

		SURA_CHG_LST = 0;							//型データを読んだ後に正常に動作しない
		SET_SPM_LST = 0;							//

		CAM_name_ref();								//ﾛｰﾀﾘｶﾑ汎用選択種別に対応したｶﾑ名称の更新

		KAT_read_sura_chk();						//型データ読込み時スライド設定値チェック

		FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
		FRAM_KAT_csum_set();						//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

		disp_stg_sel = E_dstg_init;					//データ設定[基本]へ
		GAMEN_NO = 17;
		GAMEN_disp();								//型データ読込後はデータ設定画面は自動的に戻る	

		KAT_DATCHG_FLG = 0;							//型データ読込後はデータ変更フラグクリア
	}
}


/*
********************************************************************************
*  Module Name:		KAT_data_write
*  Function Name:	型ﾃﾞｰﾀ 書込
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-06
********************************************************************************
*/
void	KAT_data_write(void)
{
	UNs		i, *bf_p;

	i = PV_MLDNO1_F0;							//現在の型番号 書込

	bf_p = KAT_sv_name_tbl[i];					//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
	memcpy_word(bf_p, &PV_MLDNO2_F0[0], 8);		//型ﾃﾞｰﾀ 書込画面用の型名称

	PV_TOTLC1_B3_KAT = PV_TOTLC1_B3;			//トータルカウンタ１実測値をコピー
	PV_LOTCT1_B4_KAT = PV_LOTCT1_B4;			//ロットカウンタ１実測値をコピー
	PV_TOTLC2_B31_KAT = PV_TOTLC2_B31;			//未使用
	PV_LOTCT2_B41_KAT = PV_LOTCT2_B41;			//ロットカウンタ２実測値をコピー

	kata_save(i, &FRAM_KAT_TOP);				//型データをFROMへ格納

	FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	FRAM_KAT_csum_set();						//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	KAT_DATCHG_FLG = 0;							//型データ書込後はデータ変更フラグクリア

}


/*
********************************************************************************
*  Module Name:		KAT_read_sura_chk
*  Function Name:	型データ読込み時スライド設定値チェック
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-06
********************************************************************************
*/
void	KAT_read_sura_chk(void)
{

	if(SEQ_024_SV & BIT_6){						//ｽﾗｲﾄﾞ自動調節が無かったらやらない

		//下限≦設定値(スライド自動調節　生産設定)≦上限
		if( SV_ATUOS0_D9 > SV_UPDATA_A21 ||		//設定値 > 上限 ？
			SV_ATUOS0_D9 < SV_DNDATA_A21 ) {	//設定値 < 下限 ？

			SV_ATUOS0_D9 = SV_UPDATA_A21;		//設定値 = 上限
		}

		//下限≦設定値(スライド自動調節　段取り１設定)≦上限
		if( SV_ATUOS1_D9 > SV_UPDATA_A21 ||		//設定値 > 上限 ？
			SV_ATUOS1_D9 < SV_DNDATA_A21 ) {	//設定値 < 下限 ？

			SV_ATUOS1_D9 = SV_UPDATA_A21;		//設定値 = 上限
		}

		//下限≦設定値(スライド自動調節　段取り２設定)≦上限
		if( SV_ATUOS2_D9 > SV_UPDATA_A21 ||		//設定値 > 上限 ？
			SV_ATUOS2_D9 < SV_DNDATA_A21 ) {	//設定値 < 下限 ？

			SV_ATUOS2_D9 = SV_UPDATA_A21;		//設定値 = 上限
		}
	}
}


/*
********************************************************************************
*  Module Name:		NAME_csr_mng
*  Function Name:	名称画面カーソル制御
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	NAME_csr_mng(void)
{
	UNs	csr_pos;

	if(GAMEN_NO == 12){							//カム名称入力画面？
		if( PV_CAMNA1_C1 & BIT_0 ) {			//カム名称選択中
			if(NAME_CHG_FLG != 0xff){			//名称変更中？
				goto NAME_500;					//この状態では何処でも移動可
			}
		}
		else{									//汎用出力選択中は移動しない
			return;
		}
	}
//NAME_CSR_200:
	csr_pos = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//ｶｰｿﾙのX,Y軸

	if( CSR_FLG == E_key_up ) {					//key code ↑ ？
		if( 3 == (csr_pos & 0x000f) ) {			//現在のカーソル位置が３行目だったら上には移動しない
			return;
		}
	}
	else if( CSR_FLG == E_key_left ) {			//key code ←
		if( 0x13 == (csr_pos & 0x03ff) ) {		//現在のカーソル位置が??移動しない
			return;
		}
	}
NAME_500:
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//カーソル移動

}


/*
********************************************************************************
*  Module Name:		KATname_inp
*  Function Name:	型名称 入力処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	KATname_inp(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[16], *wk_p;


	wk_p = &wk[0];
	dst_p = &PV_MLDNO2_F0[0];
	xy_no = CSR_buff[0].XY_POS;

	if(NAME_CHG_FLG != 0xff){						//名称変更中？
		memset_word(dst_p, E_AS_SPSP, 8);			//カム名称エリア８桁クリア
		NAME_CHG_FLG = 0xff;						//名称変更中
		KATNAME_INP_CNT = 0;						//入力カウンタ初期化

													//ｶｰｿﾙ表示(反転)
		CSR_disp_on(xy_no);							//裏画面反転
	}

	if(KATNAME_INP_CNT < 14){						//入力カウンタオーバ？
		memcpy_word((UNs *)&wk[0], dst_p, 8);		//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

		wk_p += KATNAME_INP_CNT;					//データ格納
		*wk_p = CSR_buff[CSR_TBL_POS_NOW].YOBI1;	//カム名称キャラクタコード読込

		memcpy_word(dst_p, (UNs *)&wk[0], 8);		//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

		KATNAME_INP_CNT++;							//入力カウンタ＋１
		KATname_ref(xy_no, dst_p);					//カム名称リフレッシュ
	}
}


/*
********************************************************************************
*  Module Name:		KATname_cls
*  Function Name:	型名称 訂正処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	KATname_cls(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[16], *wk_p;


	wk_p = &wk[0];
	dst_p = &PV_MLDNO2_F0[0];
	xy_no = CSR_buff[0].XY_POS;

	memcpy_word((UNs *)&wk[0], dst_p, 8);			//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

	if(NAME_CHG_FLG != 0xff){						//名称変更中？
													//ｶｰｿﾙ表示(反転)
		CSR_disp_on(xy_no);							//裏画面反転

		NAME_CHG_FLG = 0xff;						//名称変更中
		KATNAME_INP_CNT = NAME_leng_chk(wk_p, 14);	//名称の入力文字数をチェック
	}

	if(KATNAME_INP_CNT != 00){
		KATNAME_INP_CNT --;							//入力カウンタ-1
	}

	wk_p += KATNAME_INP_CNT;						//前入力をｽﾍﾟｰｽｸﾘｱ
	*wk_p = E_AS_SP;
	memcpy_word(dst_p, (UNs *)&wk[0], 8);			//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

	KATname_ref(xy_no, dst_p);						//カム名称リフレッシュ

}


/*
********************************************************************************
*  Module Name:		KATname_ref
*  Function Name:	カム名称リフレッシュ
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*			:		文字ｺｰﾄﾞ･格納ｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	KATname_ref(UNs xy_no, UNs *g_adr_p)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	Disp_moji(xy_no, g_adr_p, 0 );				//文字表示
#else
	disp_moji_s_color(
		CSR_buff[0].M_LEN,						/* ｷｬﾗｸ長			*/
		CSR_buff[0].X_POS,						/* 書出しX位置		*/
		CSR_buff[0].Y_POS,						/* 書出しY位置		*/
		CSR_buff[0].C_COL,						/* 文字色			*/
		CSR_buff[0].B_COL2,						/* 背景色			*/
		CSR_buff[0].SIZE,						/* 文字ｻｲｽﾞ			*/
		g_adr_p,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VRAM								/* 表示ﾒﾓﾘ			*/
		);
#endif
}


/*
********************************************************************************
*  Module Name:		CSR_disp_on(旧:CSR_DISP_ON，CSR_DISP_ON_OFF)
*  Function Name:	裏画面反転
*  Input	:		表示軸(b0～b3:行,b4～b9:桁,b10～b15:文字数)
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
void	CSR_disp_on(UNs xy_no )
{

	disp_memnot(xy_no, &LCD_WORK2[0][0][0]);	//表示用領域の指定ﾃﾞｰﾀを反転
	Lcd_cr(1, xy_no, &LCD_WORK2[0][0][0]);		//ｷｬﾗ単位表示

}


/*
********************************************************************************
*  Module Name:		NAME_leng_chk
*  Function Name:	名称の入力文字数をチェック
*  Input	:		ﾁｪｯｸﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
*					ﾁｪｯｸ長
*
*  Return	: 		ﾁｪｯｸの結果長
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-21
********************************************************************************
*/
UNs		NAME_leng_chk(UNb *dst_p, UNs len)
{
	UNs	i;

	i = len;
	dst_p += len;
	dst_p --;

	for( ; len > 0 ; len-- ){
		if(*dst_p == E_AS_SP){
			dst_p--;
			i--;
		}
		else{
			break;
		}
	}

	return(i);
}


/*
********************************************************************************
*  Module Name:		CAMname_inp
*  Function Name:	カム名称 入力処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-26
********************************************************************************
*/
void	CAMname_inp(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[10], *wk_p;

	wk_p = &wk[0];
	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	if(CSR_buff[CSR_TBL_POS_NOW].YOBI1 != 0xff){			//最上部カーソルコード?

		if(00 == CAMname_inp_chk() ){						//カム名称入力可チェック
			if(NAME_CHG_FLG != 0xff){						//名称変更中？
				memset_word(dst_p, E_AS_SPSP, 4);			//カム名称エリア８桁クリア
				NAME_CHG_FLG = 0xff;						//名称変更中
				CAMNAME_INP_CNT = 0;						//入力カウンタ初期化

															//ｶｰｿﾙ表示(反転)
				CSR_disp_on(xy_no);							//裏画面反転
			}
			if(CAMNAME_INP_CNT < 8){						//入力カウンタオーバ？

				memcpy_word((UNs *)&wk[0], dst_p, 4);		//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

				wk_p += CAMNAME_INP_CNT;					//データ格納
				*wk_p = CSR_buff[CSR_TBL_POS_NOW].YOBI1;	//カム名称キャラクタコード読込

				memcpy_word(dst_p, (UNs *)&wk[0], 4);		//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

				CAMNAME_INP_CNT++;							//入力カウンタ＋１

				KATname_ref(xy_no, dst_p);					//カム名称リフレッシュ

			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CAMname_cls
*  Function Name:	カム名称 訂正処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-26
********************************************************************************
*/
void	CAMname_cls(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[10], *wk_p;

	wk_p = &wk[0];
	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	if(00 == CAMname_inp_chk() ){						//カム名称入力可チェック
		memcpy_word((UNs *)&wk[0], dst_p, 4);			//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

		if(NAME_CHG_FLG != 0xff){						//名称変更中？
														//ｶｰｿﾙ表示(反転)
			CSR_disp_on(xy_no);							//裏画面反転

			NAME_CHG_FLG = 0xff;						//名称変更中
			CAMNAME_INP_CNT = NAME_leng_chk(wk_p, 8);	//名称の入力文字数をチェック
		}

		if(CAMNAME_INP_CNT != 00){
			CAMNAME_INP_CNT --;							//入力カウンタ-1
		}

		wk_p += CAMNAME_INP_CNT;						//前入力をｽﾍﾟｰｽｸﾘｱ
		*wk_p = E_AS_SP;
		memcpy_word(dst_p, (UNs *)&wk[0], 4);			//カム名称エリア コピー(ﾓﾄﾛｰﾗ対応)

		KATname_ref(xy_no, dst_p);					//カム名称リフレッシュ
	}
}


/*
********************************************************************************
*  Module Name:		CAMname_inp_chk
*  Function Name:	カム名称入力可チェック
*  Input	:		なし
*  Return	: 		00 ＝ 正常
					00 ≠ 異常
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-26
********************************************************************************
*/
UNi		CAMname_inp_chk(void)
{
	UNs		i;
	UNi		ref;

	ref = 0;							//正常
	i = PV_CAMNA1_C1;

	if( i & 0xfffe ){					//カム出力制御以外が立っているか
		ref = 0xff;						//異常
	}
	else if( 00 == (i & 0x0001) ){		//カム出力制御が選ばれているか？
		ref = 0xff;						//異常
	}

	return(ref);
}


/*
********************************************************************************
*  Module Name:		CAMname_touroku
*  Function Name:	カム名称登録
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-26
********************************************************************************
*/
void	CAMname_touroku(void)
{
	UNs		*bf_p;
	UNi		i;

	CAMNAME_INP_CNT = 0;							//入力カウンタ初期化

	i = CAM_NAME_NO;								//変更カム名称番号読込
	bf_p = Camcsr_Name_Tbl[i];						//ロータリカム名称のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
	memcpy_word(bf_p, &PV_CAMNAM_C1[0], 4);			//カム名称

	if(NAME_CHG_FLG == 0xff){						//名称変更
		memcpy_word(&PV_CAMNAM_C2[0], &PV_CAMNAM_C1[0], 4);		//カム名称

		bf_p = Camcsr_Name_TblSV[i];				//ロータリカム名称のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
		memcpy_word(bf_p, &PV_CAMNAM_C1[0], 4);		//カム名称

	}

	bf_p = Camcsr_Name_Tbl1[i];						//ロータリカム１汎用選択種別のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
	*bf_p = PV_CAMNA1_C1;

	FRAM_csum_set();								//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	KAT_DATCHG_FLG = 0xff;							//型データ変更フラグ
	SVSW_CHG_FLG |= BIT_5;							//ｶﾑﾃﾞｰﾀ(CAM)要求
	NAME_CHG_FLG = 0;								//名称変更中クリア
}


/*
********************************************************************************
*  Module Name:		CAMname_sw_ent
*  Function Name:	汎用出力選択
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-26
********************************************************************************
*/
void	CAMname_sw_ent(void)
{
	UNi 	cnt, cnt2;
	UNs		*dst_p, *src_p, xy_no, b_d0;

	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	CAMNAME_INP_CNT = 0;								//入力カウンタ初期化

	//汎用出力選択ＳＷをチェック（複数立っていたら）
	PV_CAMNA1_C1 <<= 1;									//移動
	b_d0 = BIT_0;
	for(cnt=16, cnt2=0 ; cnt > 0 ; cnt--){
		if( PV_CAMNA1_C1 & b_d0 ){
			cnt2 ++;
		}
		b_d0 <<= 1;
	}
	if(cnt2 != 1){
		PV_CAMNA1_C1 = BIT_0;
	}

	//汎用が選ばれているものだけ汎用キャラクタを転送
	b_d0 = BIT_0;
	for(cnt=0 ; cnt < 16 ; cnt++){
		if( PV_CAMNA1_C1 & b_d0 ){
			src_p = Camcsr_Name_TblSW[cnt];
			memcpy_word(dst_p, src_p, 4);				//指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー
			KATname_ref(xy_no, dst_p);					//カム名称リフレッシュ

			NAME_CHG_FLG = 0;							//名称変更中クリア
			CAMNAME_INP_CNT = 0;						//入力カウンタ初期化

			CSR_sw56_disp();							//ＳＷ５６キャラクタ表示
			Under_grph();								//下段のグラフィックセット

			cnt = SW_CNT;
			while(cnt--){
				SWchg_disp_pv();						//ＳＷＣＨＧデータ表示実測処理
			}
			Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
			Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示
			break;
		}
		b_d0 <<= 1;
	}
}


/*
********************************************************************************
*  Module Name:		CAM_name_ref(旧:KATA_READ_CAMNAME)
*  Function Name:	ﾛｰﾀﾘｶﾑ汎用選択種別に対応したｶﾑ名称の更新
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-30
********************************************************************************
*/
void	CAM_name_ref(void)
{
	UNs		*src_p, *dst_p, b_d0, b_d1;
	UNi		cnt, cnt2;

	for(cnt=0 ; cnt < 16 ; cnt++){						//ﾛｰﾀﾘｶﾑ1～16
		src_p = Camcsr_Name_Tbl1[cnt];
		b_d0 = *src_p;
		if(b_d0 == BIT_0){								//ｶﾑ選択？
			dst_p = Camcsr_Name_Tbl[cnt];				//YES
			src_p = Camcsr_Name_TblSV[cnt];
			memcpy_word(dst_p, src_p, 4);				//指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー
		}
		else{											//汎用が選ばれているものだけ汎用キャラクタを転送
			b_d1 = BIT_0;								//ｶﾑ汎用選択種別ﾁｪｯｸ
			for(cnt2=0 ; cnt2 < 16 ; cnt2++){
				if( b_d0 & b_d1 ){
					dst_p = Camcsr_Name_Tbl[cnt];
					src_p = Camcsr_Name_TblSW[cnt2];
					memcpy_word(dst_p, src_p, 4);		//指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー
					break;
				}
				b_d1 <<= 1;
			}
		}
	}
}



/*** END ***/
