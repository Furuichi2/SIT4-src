/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			システム設定の操作メイン処理											*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-06-04
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_addr.h"							//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
/* 定数定義 ---------------------------------------------------------- */
#define		E_MM		0x6d6d2020			//mm		距離
#define		E_INCH		0x494e4348			//INCH
#define		E_MICRO		0x83ca2020			//μ					2014/03/10

#define		E_TON		0x746f6e20			//ton		重量
#define		E_KN		0x6b4e2020			//kN

#define		E_K			0x4b202020			//K			重さ
#define		E_PSI		0x50534920			//PSI
#define		E_MPA		0x4d506120			//MPa

#if (mot100_test == 1)
#define		E_DO		0x818b2020			//°
#define		E_PAR		0x25202020			//%
#define		E_TIM		0x73202020			//s
#endif


/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	dsp_Sysset(void);						//システム設定の管理
void	Sys_sel_dstg_mmon(void);				//データ設定[メンテナンスモニタ]へ
void	Sys_sel_dstg_ksel(void);				//データ設定[機能選択]へ
void	Sys_dsp_move(void);						//画面と管理ｽﾃｰｼﾞの移動
void	CAR_mkssi_set(void);					//単位切換ﾃﾞｰﾀ格納処理
void	INI_data_set(void);						//データ初期化
void	Dat_mm_inch_chg(void);					//データ切替（mm⇔inch）

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */



/*
********************************************************************************
*  Module Name:		dsp_Sysset
*  Function Name:	システム設定の管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-04
********************************************************************************
*/
void	dsp_Sysset(void)
{

	switch(disp_stg_sel) {

		case E_ystg_init:		//ｼｽﾃﾑ設定[基本]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(なし)
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
							break;
						case E_key_sw6:			//key code SW6
							Sys_dsp_move();						//画面と管理ｽﾃｰｼﾞの移動
							break;
					}
					break;
			}
			break;

		case E_ystg_sys1:		//ｼｽﾃﾑ設定[仕様設定1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					SWchg_ent();								//SW CHG データ ENT
					ROTTO_chk();								//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
					CAR_mkssi_set();							//単位切換データ格納処理
					Dat_mm_inch_chg();							//データmm⇔inch切替				2015/01/20

					if(00 == (SEQ_016_SV & BIT_14)){			//ﾛｯﾄｶｳﾝﾀ2　強制OFFかもしれない？
						SWCHG_DISP_ON_FLG = 0x0FF;
						SWchg_disp();							//SWﾃﾞｰﾀ情報　表示
						SWCHG_DISP_ON_FLG = 0;
					}
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_sys2;			//ｼｽﾃﾑ設定[仕様設定2]へ
							GAMEN_NO = 33;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_ystg_sys2:		//ｼｽﾃﾑ設定[仕様設定2]
		case E_ystg_sys3:		//ｼｽﾃﾑ設定[仕様設定3]
		case E_ystg_sys4:		//ｼｽﾃﾑ設定[仕様設定4]
		case E_ystg_sys5:		//ｼｽﾃﾑ設定[仕様設定5]
		case E_ystg_sys6:		//ｼｽﾃﾑ設定[仕様設定6]
		case E_ystg_sys7:		//ｼｽﾃﾑ設定[仕様設定7]
		case E_ystg_sys8:		//ｼｽﾃﾑ設定[仕様設定8]
		case E_ystg_sys9:		//ｼｽﾃﾑ設定[仕様設定9]			V06m
		case E_ystg_sysA:		//ｼｽﾃﾑ設定[仕様設定10]			V06m
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					SWchg_ent();								//SW CHG データ ENT
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5) {			//key code SW5
						disp_stg_sel --;
						if(disp_stg_sel == E_ystg_sys6){		//ｼｽﾃﾑ設定[仕様設定6]?
							GAMEN_NO = 37;
						}
						else if(disp_stg_sel == E_ystg_sys8){		//ｼｽﾃﾑ設定[仕様設定8]?			V06m
							GAMEN_NO = 56;
						}
						else{									//NO
							GAMEN_NO --;
						}
						GAMEN_disp();							//画面表示
					}
					else if(KEY_DATA_CODE == E_key_sw6){		//key code SW6
//V06m						if (disp_stg_sel != E_ystg_sys8) {
						if (disp_stg_sel != E_ystg_sysA) {
							disp_stg_sel ++;
							if(disp_stg_sel == E_ystg_sys7){		//ｼｽﾃﾑ設定[仕様設定7]?
								GAMEN_NO = 55;
							}
							else if(disp_stg_sel == E_ystg_sys9){		//ｼｽﾃﾑ設定[仕様設定9]?		V06m
								GAMEN_NO = 106;
							}
							else{									//NO
								GAMEN_NO ++;
							}
							GAMEN_disp();							//画面表示
						}
					}
					break;
			}
			break;

//V06m
//		case E_ystg_sys8:		//ｼｽﾃﾑ設定[仕様設定8]
//			switch(KEY_DATA_MODE) {
//				case E_key_ent_mode:		//ENT key mode
//					SWchg_ent();								//SW CHG データ ENT
//					break;
//
//				case E_key_sw14_mode:		//SW1～4 key mode
//					switch(KEY_DATA_CODE) {
//						case E_key_sw1:			//key code SW1
//							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
//							GAMEN_NO = 31;
//							GAMEN_disp();						//画面表示
//							break;
//						case E_key_sw2:			//key code SW2
//							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
//							break;
//						case E_key_sw3:			//key code SW3
//							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
//							break;
//						case E_key_sw4:			//key code SW4(なし)
//							break;
//					}
//					break;
//
//				case E_key_sw56_mode:		//SW5/6 key mode
//					if(KEY_DATA_CODE == E_key_sw5) {			//key code SW5
//						disp_stg_sel = E_ystg_sys7;				//ｼｽﾃﾑ設定[仕様設定7]
//						GAMEN_NO = 55;
//						GAMEN_disp();							//画面表示
//					}
//					break;
//			}
//			break;

		case E_ystg_cbs1:		//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();						//SW CHG データ ENT

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_cbs2;			//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ2]へ
							GAMEN_NO = 51;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_cbs2:		//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(なし)
					Key_Ent_sv();								//設定値の確定		V05 (INS)
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();						//SW CHG データ ENT

							SW16data_onset(0xff, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_cbs1;			//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ1]へ
							GAMEN_NO = 38;
							GAMEN_disp();						//画面表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_spr1:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;

						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_spr2;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ2]へ
							GAMEN_NO = 40;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_ystg_spr2:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ2]
		case E_ystg_spr3:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ3]
		case E_ystg_spr4:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ4]
		case E_ystg_spr5:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ5]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel --;					//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1/2/3/4]へ
							if(disp_stg_sel == E_ystg_spr2){
								GAMEN_NO = 40;
							}
							else{
								GAMEN_NO --;
							}
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6
							disp_stg_sel ++;					//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ3/4/5/6]へ
							if(disp_stg_sel == E_ystg_spr3){
								GAMEN_NO = 57;
							}
							else{
								GAMEN_NO ++;
							}
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_ystg_spr6:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ6]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr5;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ5]へ
							GAMEN_NO = 59;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6(なし)
							disp_stg_sel = E_ystg_spr7;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ7]へ	// V01v追加
							GAMEN_NO = 61;													// V01v追加
							GAMEN_disp();						//画面表示					// V01v追加
							break;
					}
					break;
			}
			break;

		case E_ystg_spr7:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ7]			// V01v追加
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr6;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ6]へ
							GAMEN_NO = 60;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6(COP2対応)
							disp_stg_sel = E_ystg_spr8;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8]へ
							GAMEN_NO = 62;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_ystg_spr8:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8]			// COP2対応
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr7;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ7]へ
							GAMEN_NO = 61;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6
//V05c							disp_stg_sel = E_ystg_spr9;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9]へ
//V05c							GAMEN_NO = 63;
//V05c							GAMEN_disp();						//画面表示

							disp_stg_sel = E_ystg_sprB;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀB]へ		V06
							GAMEN_NO = 103;
							GAMEN_disp();						//画面表示

							break;
					}
					break;
			}
			break;

		case E_ystg_spr9:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9]			// COP2対応
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
//V05c							disp_stg_sel = E_ystg_spr8;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8]へ
//V05c							GAMEN_NO = 62;
//V05c							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_sprA;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ10]へ
							GAMEN_NO = 64;
							GAMEN_disp();						//画面表示
							break;
					}
					break;
			}
			break;

		case E_ystg_sprA:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ10]			// COP2対応
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr9;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9]へ
							GAMEN_NO = 63;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6(なし)
							break;
					}
					break;
			}
			break;

		case E_ystg_sprB:		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀB]			// V06
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr8;			//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8]へ
							GAMEN_NO = 62;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw6:			//key code SW6
							break;
					}
					break;
			}
			break;

		case E_ystg_scm:		//ｼｽﾃﾑ設定[ｼｽﾃﾑｶﾑ設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(なし)
					break;
			}
			break;

		case E_ystg_tmct:		//ｼｽﾃﾑ設定[ﾀｲﾏ/ｶｳﾝﾀ]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(なし)
					break;
			}
			break;

		case E_ystg_kjyu:		//ｼｽﾃﾑ設定[荷重計設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;

						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();					//生産設定ﾃｽﾄ出力処理(SW6)

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_sura:		//ｼｽﾃﾑ設定[ｽﾗｲﾄﾞ設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
//Sit-Sなし			CAR_mkssi_set();							//単位切換データ格納処理
					CAR_mkssi_set();							//単位切換データ格納処理	V01m
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//ｼｽﾃﾑ設定OK(1:OK)
								PODATA_SET_FLG = 0xff;
								POSdata_set_kaku();					//確認ｷｰによるﾎﾟｼﾞｼｮﾅｰ設定ﾃﾞｰﾀ格納(ｵﾌﾟｼｮﾝ領域にﾃﾞｰﾀを転送)
								SEQ_PAR_450 |= BIT_0;
								PVGENNITI_FLG = 00;					//ﾊﾞｯｸｱｯﾌﾟ画面にて現位置データを変更してから”確認”が押される迄ｻﾝﾌﾟﾘﾝｸﾞしない

								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示

								PV_DEB_WORD_WK3 = PV_DEB_WORD_WK3 + 1;			/* V01n_b */
							}
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							SEQ_PAR_450 &= ~BIT_0;
							break;
					}
					break;
			}
			break;

		case E_ystg_dbak:			//ｼｽﾃﾑ設定[ﾊﾞｯｸｱｯﾌﾟﾃﾞｰﾀ設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(なし)
					break;
			}
			break;

		case E_ystg_dini:		//ｼｽﾃﾑ設定[ﾃﾞｰﾀ初期化]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(なし)
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
							break;

						case E_key_sw5:			//key code SW5
//							if(SEQ_PAR_101 & BIT_4 ){			//ﾃﾞｰﾀ初期化OK(1:OK)？
//Sit-Sなし						&& MLD_100_CARD_FLG == 0xAA){		//外部メモリ有り？
//
//								PV_GAIBU_A1 = 6;				//外部データ読込み中
//
//								SWCHG_DISP_ON_FLG = 0x0FF;
//								SWchg_disp_gaibu();				//SWﾃﾞｰﾀ情報　表示
//								SWCHG_DISP_ON_FLG = 0;
//
//2次								MLD100_ini();					//１００型データイニシャル
//								PV_GAIBU_A1 = 7;				//外部データ読み込み完了
//
//								SWchg_disp();					//ＳＷデータ情報　表示
//							}
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_4){			//ﾃﾞｰﾀ初期化OK(1:OK)？

								PV_DATINI_A1 = 3;

								SWCHG_DISP_ON_FLG = 0x0FF;
								SWchg_disp_gaibu();				//SWﾃﾞｰﾀ情報　表示
								SWCHG_DISP_ON_FLG = 0;

								INI_data_set();					//データ初期化
								PV_DATINI_A1 = 4;

								SWCHG_DISP_ON_FLG = 0x0FF;
								SWchg_disp();					//ＳＷデータ情報　表示
								SWCHG_DISP_ON_FLG = 0;
							}
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_dail:	/* V01j */	//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節左]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//ｼｽﾃﾑ設定OK(1:OK)
								SEI_test_out_sw6();					//生産設定ﾃｽﾄ出力処理(SW6)
								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_dair:	/* V01j */	//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節右]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//ｼｽﾃﾑ設定OK(1:OK)
								SEI_test_out_sw6();					//生産設定ﾃｽﾄ出力処理(SW6)
								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_atuc:	/* V01j */	//ｼｽﾃﾑ設定[圧力調節設定]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//ｼｽﾃﾑ設定OK(1:OK)
								SEI_test_out_sw6();					//生産設定ﾃｽﾄ出力処理(SW6)
								SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							}
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_ystg_kchg:		//ｼｽﾃﾑ設定[機器交換時設定]へ		/* V06p */
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//ｼｽﾃﾑ設定[基本]へ
							GAMEN_NO = 31;
							GAMEN_disp();						//画面表示
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//データ設定[メンテナンスモニタ]へ
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//データ設定[機能選択]へ
							break;
						case E_key_sw4:			//key code SW4(なし)
						case E_key_sw5:			//key code SW5(なし)
						case E_key_sw5_down:	//key code SW5(立下り)(なし)
							break;

						case E_key_sw6:			//key code SW6
							SWchg_ent();						//SW CHG データ ENT
							SEI_test_out_sw6();					//生産設定ﾃｽﾄ出力処理(SW6)

							SW16data_onset(0xff, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw6_down:	//key code SW6(立下り)
							SW16data_onset(00, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;
	}
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dstg_mmon
*  Function Name:	データ設定[メンテナンスモニタ]へ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-06
********************************************************************************
*/
void	Sys_sel_dstg_mmon(void)
{
	disp_stg = 02;						//データ設定画面へ
	disp_stg_sel = E_dstg_mmon;			//データ設定[メンテナンスモニタ]へ

	GAMEN_NO = 13;
	GAMEN_disp();						//画面表示
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dstg_ksel
*  Function Name:	データ設定[機能選択]へ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-06
********************************************************************************
*/
void	Sys_sel_dstg_ksel(void)
{
	disp_stg = 02;						//データ設定画面へ
	disp_stg_sel = E_dstg_ksel;			//データ設定[機能選択]へ

	GAMEN_NO = 14;
	GAMEN_disp();						//画面表示
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dsp（旧:GAMEN_MOVE）
*  Function Name:	画面と管理ｽﾃｰｼﾞの移動
*  Input	:		なし
*  Return	: 		なし
*  Note		:カーソル情報テーブルの画面移動番号による画面と管理ｽﾃｰｼﾞの移動
*
*  履 歴	:FIT)田端		ON:2002-06-06
********************************************************************************
*/
void	Sys_dsp_move(void)
{
	UNs		i;

	i = CSR_buff[CSR_TBL_POS_NOW].MOVE_NO;				//画面移動番号
	i &= 0x00ff;
	if( i == 0 || i == 0xff){
//		nop();
	}
	else{
		if( i == 32 ){
			disp_stg_sel = E_ystg_sys1;		//ｼｽﾃﾑ設定[仕様設定1]
		}
		else if( i == 38 ){
			disp_stg_sel = E_ystg_cbs1;		//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ1]へ
		}
		else if( i == 39 ){
			disp_stg_sel = E_ystg_spr1;		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1]へ
		}
		else if( i == 41 ){
			disp_stg_sel = E_ystg_scm;		//ｼｽﾃﾑ設定[ｼｽﾃﾑｶﾑ設定]へ
		}
		else if( i == 43 ){
			disp_stg_sel = E_ystg_tmct;		//ｼｽﾃﾑ設定[ﾀｲﾏ/ｶｳﾝﾀ]へ
		}
		else if( i == 44 ){
			disp_stg_sel = E_ystg_kjyu;		//ｼｽﾃﾑ設定[荷重計設定]へ
		}
		else if( i == 45 ){
			disp_stg_sel = E_ystg_sura;		//ｼｽﾃﾑ設定[ｽﾗｲﾄﾞ設定]へ
		}
		else if( i == 47 ){					// V01j
			disp_stg_sel = E_ystg_dail;		//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節左]へ
		}
		else if( i == 48 ){					// V01j
			disp_stg_sel = E_ystg_dair;		//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節右]へ
		}
		else if( i == 49 ){					// V01j
			disp_stg_sel = E_ystg_atuc;		//ｼｽﾃﾑ設定[圧力調節設定]へ
		}
		else if( i == 50 ){
			disp_stg_sel = E_ystg_dbak;		//ｼｽﾃﾑ設定[ﾊﾞｯｸｱｯﾌﾟﾃﾞｰﾀ設定]へ
		}
		else if( i == 52 ){
			disp_stg_sel = E_ystg_dini;		//ｼｽﾃﾑ設定[ﾃﾞｰﾀ初期化]へ
		}
		else if( i == 63 ){		// V05c
			disp_stg_sel = E_ystg_spr9;		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9]へ
		}
		else if( i == 108 ){		// V06p
			disp_stg_sel = E_ystg_kchg;		//ｼｽﾃﾑ設定[機器交換時設定]へ
		}
		else{
			i = 31;
		}
		GAMEN_NO = i;
		GAMEN_disp();						//画面表示
	}
}


/*
********************************************************************************
*  Module Name:		CAR_mkssi_set
*  Function Name:	単位切換ﾃﾞｰﾀ格納処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-17
********************************************************************************
*/
void	CAR_mkssi_set(void)
{
//SIT-S新規

	if( SEQ_016_SV & BIT_6 ) {		//単位切替 mm/INCH 単位系(1:INCH)
		CAR_LNG_AREA = E_INCH;			//INCH
		CAR_KAJ_AREA = E_TON;			//ton
		CAR_ATU_AREA = E_PSI;			//PSI

		if( SEQ_016_SV & BIT_7 ) {	//単位 高精度(1:高精度)
			SYO_LNG_CNT = 4;			//小数点位置
			SYOD_LNG_CNT = 4;			//小数点位置
			SYO_LNG_SUR_CNT = 4;		//小数点位置
		}
		else{
			SYO_LNG_CNT = 3;			//小数点位置
			SYOD_LNG_CNT = 3;			//小数点位置
			SYO_LNG_SUR_CNT = 3;		//小数点位置
		}
		SYO_ATU_CNT = 0;				//圧力は小数点無し
		SYOD_ATU_CNT = 0;
		SYO_KAJ_CNT = 0;				//小数点無し	V05r
	}
	else{								//SI単位系(ﾃﾞﾌｫﾙﾄ)
		CAR_LNG_AREA = E_MM;			//mm						(6line 2002-12-11:変更)
		CAR_KAJ_AREA = E_KN;			//kN
		CAR_ATU_AREA = E_MPA;			//MPa

		if( SEQ_016_SV & BIT_7 ) {	//単位 高精度(1:高精度)
			SYO_LNG_CNT = 3;			//小数点位置
			if (SV_POINT_A1 == 0) {
				SYO_LNG_SUR_CNT = 3;			//小数点位置
			}
			else {
				SYO_LNG_SUR_CNT = (UNs)SV_POINT_A1+1;		//小数点位置
			}
//2014/12/23
////			SYOD_LNG_CNT = 3;			//小数点位置
			if (SV_POINT_A47 == 0) {
				SYOD_LNG_CNT = 3;			//小数点位置
			}
			else {
				SYOD_LNG_CNT = (UNs)SV_POINT_A47+1;		//小数点位置
			}
		}
		else{
			SYO_LNG_CNT = 2;			//小数点位置
			if (SV_POINT_A1 == 0) {
				SYO_LNG_SUR_CNT = 2;			//小数点位置
			}
			else {
				SYO_LNG_SUR_CNT = (UNs)SV_POINT_A1;		//小数点位置
			}
//2014/12/23
////			SYOD_LNG_CNT = 2;			//小数点位置
			if (SV_POINT_A47 == 0) {
				SYOD_LNG_CNT = 2;			//小数点位置
			}
			else {
				SYOD_LNG_CNT = (UNs)SV_POINT_A47;		//小数点位置
			}
		}
		SYO_ATU_CNT = 0;				//圧力は小数点無し
		SYOD_ATU_CNT = 0;
		SYO_KAJ_CNT = 0;				//小数点無し	V05r
	}

	if (SEQ_024_SV & BIT_9)			//荷重単位切替有り？（仕様設定No.138）			//V05r
	{
		if( SEQ_016_SV & BIT_5 ) {			//単位切替 kN/ton	（仕様設定No.6）
			CAR_KAJ_AREA = E_TON;			//ton
			SYO_KAJ_CNT = 1;				//小数点1桁
		}
		else{								//
			CAR_KAJ_AREA = E_KN;			//kN
			SYO_KAJ_CNT = 0;				//小数点無し
		}
	}

	if(SEQ_050_SV & BIT_9) {				//ﾓｰｼｮﾝ下限／荷重？			2014/08/20
		/*--- 荷重 ---*/
		CAR_MICRO_KAJ_AREA = CAR_KAJ_AREA;
	}
	else {
		/*--- 下限 ---*/
		CAR_MICRO_KAJ_AREA = E_MICRO;
	}


//SIT-Sでは、なし
//
//	if(SV_POINT_A1 == 0 ||				//ｽﾗｲﾄﾞ調節　小数点位置
//		SV_POINT_A1 > 2 ) {
//		SV_POINT_A1 = 1;				//ｽﾗｲﾄﾞ調節　小数点位置(ﾃﾞﾌｫﾙﾄ)
//	}
//	if(SV_POINT_A47 == 0 ||				//ﾀﾞｲｸｯｼｮﾝ自動調節左　小数点位置
//		SV_POINT_A47 > 2 ) {
//		SV_POINT_A47 = 1;				//ﾀﾞｲｸｯｼｮﾝ自動調節左　小数点位置(ﾃﾞﾌｫﾙﾄ)
//	}
//	if(SV_POINT_A48 == 0 ||				//ﾀﾞｲｸｯｼｮﾝ自動調節右　小数点位置
//		SV_POINT_A48 > 2 ) {
//		SV_POINT_A48 = 1;				//ﾀﾞｲｸｯｼｮﾝ自動調節右　小数点位置(ﾃﾞﾌｫﾙﾄ)
//	}
//
//	if( SEQ_016_SV & BIT_4 ) {			//単位切替 MKS単位系(1:有)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = '  K ';			//K
//
//		SYO_LNG_CNT = SV_POINT_A1;		//小数点位置
//		SYOD_LNG_CNT = SV_POINT_A47;	//小数点位置
//
//		SYO_ATU_CNT = 0;				//圧力は小数点無し
//		SYOD_ATU_CNT = 0;
//	}
//	else if( SEQ_016_SV & BIT_5 ) {		//単位切替 SI単位系(1:有)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' kN ';			//kN
//		CAR_ATU_AREA = 'MPa ';			//MPa
//
//		SYO_LNG_CNT = SV_POINT_A1;		//小数点位置
//		SYOD_LNG_CNT = SV_POINT_A47;	//小数点位置
//
//		SYO_ATU_CNT = 2;				//圧力は小数点２桁
//		SYOD_ATU_CNT = 2;
//	}
//	else if( SEQ_016_SV & BIT_6 ) {		//単位切替 INCH単位系(1:有)
//		CAR_LNG_AREA = 'INCH';			//INCH
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = ' PSI';			//PSI
//
//		SYO_LNG_CNT = 3;				//小数点位置
//		SYOD_LNG_CNT = 3;				//小数点位置
//
//		SYO_ATU_CNT = 0;				//圧力は小数点無し
//		SYOD_ATU_CNT = 0;
//	}
//	else{								//MKS単位系(ﾃﾞﾌｫﾙﾄ)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = '  K ';			//K
//
//		SYO_LNG_CNT = 1;				//小数点位置
//		SYOD_LNG_CNT = 1;				//小数点位置
//
//		SYO_ATU_CNT = 0;				//圧力は小数点無し
//		SYOD_ATU_CNT = 0;
//	}

	/* モーション画面の下限設定単位を荷重設定単位に変更する */
//V01m	if (SEQ_024_SV & BIT_4)						//荷重補正あり？	V01k
	if (SEQ_050_SV & BIT_9)						//荷重補正あり？	V01k
	{
		if (SEQ_024_SV & BIT_9)					//荷重単位切替有り？（仕様設定No.138）			//V05r
		{
			if( SEQ_016_SV & BIT_5 ) {				//単位切替 kN/ton	（仕様設定No.6）
				CAR_LNG_KAJ_AREA = E_TON;			//ton
				SYO_LNG_KAJ_CNT = 1;				//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 1;				//補正の小数点位置		V05r
			}
			else {
				CAR_LNG_KAJ_AREA = E_KN;			//kN
				SYO_LNG_KAJ_CNT = 0;				//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 0;				//補正の小数点位置		V05r
			}
		}
		else
		{
			if( SEQ_016_SV & BIT_6 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				CAR_LNG_KAJ_AREA = E_TON;			//ton
			}
			else {
				CAR_LNG_KAJ_AREA = E_KN;			//kN
			}
			SYO_LNG_KAJ_CNT = 0;					//下限／荷重の小数点位置
			SYO_HOS_KAJ_CNT = 0;					//補正の小数点位置		V05r
		}
	}
	else {
		if( SEQ_016_SV & BIT_6 ) {				//単位切替 mm/INCH 単位系(1:INCH)
			CAR_LNG_KAJ_AREA = E_INCH;			//INCH

			if( SEQ_016_SV & BIT_7 ) {			//単位 高精度(1:高精度)
				SYO_LNG_KAJ_CNT = 4;			//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 0;			//補正の小数点位置		V05r
			}
			else{
				SYO_LNG_KAJ_CNT = 3;			//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 0;			//補正の小数点位置		V05r
			}
		}
		else {
			CAR_LNG_KAJ_AREA = E_MM;			//mm

			if( SEQ_016_SV & BIT_7 ) {		//単位 高精度(1:高精度)
//V01m				SYO_LNG_KAJ_CNT = 3;			//下限／荷重の小数点位置
				SYO_LNG_KAJ_CNT = SYO_LNG_SUR_CNT;	//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 0;				//補正の小数点位置		V05r
			}
			else{
//V01m				SYO_LNG_KAJ_CNT = 2;			//下限／荷重の小数点位置
				SYO_LNG_KAJ_CNT = SYO_LNG_SUR_CNT;	//下限／荷重の小数点位置
				SYO_HOS_KAJ_CNT = 0;				//補正の小数点位置		V05r
			}
		}
	}

#if (mot100_test == 1)
	CAR_DO_AREA		= E_DO;					//単位(°)
	CAR_PAR_AREA	= E_PAR;				//単位(%)
	CAR_TIM_AREA	= E_TIM;				//単位(s)
#endif
}


/*
********************************************************************************
*  Module Name:		INI_data_set
*  Function Name:	データ初期化
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-09-10
********************************************************************************
*/
void	INI_data_set(void)
{
	UNs		*src_p, cnt, i;


	cnt = (UNs *)&PV_TOTLC1_B3 - &SEQ_016_SV;		//ﾌﾗｼｭRAM領域の設定値 ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ
	src_p = (UNs *)E_FROM_INI_TOP;					//設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&SEQ_016_SV, src_p, cnt);

/*V00p*/
	cnt = (UNs *)&SV_RNZRPM_A12 - &SEQ_016_SV;		//
	src_p = (UNs *)E_FROM_INI_TOP;					//設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//ﾌﾗｯｼｭROMの連続回転設定値
	SV_RNZRPM_A12 = *src_p;							//
/*V00p*/
	cnt = (UNs *)&SV_RNZTIM_A12 - &SEQ_016_SV;		//
	src_p = (UNs *)E_FROM_INI_TOP;					//設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//ﾌﾗｯｼｭROMの連続タイマ設定値
	SV_RNZTIM_A12 = *src_p;							//

/*V05b*/
	cnt = (UNs *)&SV_SMPSTR_KAJ - &SEQ_016_SV;		//ﾌﾗｼｭRAM領域の設定値 ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ
	src_p = (UNs *)E_FROM_INI_TOP;					//設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//ﾌﾗｯｼｭROMの連続回転設定値
	memcpy_word(&SV_SMPSTR_KAJ, src_p, 10);

#if (mot100_test == 1)
	cnt = (UNs *)&SV_MOTDEG0_001 - &SEQ_016_SV;		//ﾌﾗｼｭRAM領域の設定値 ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ
	src_p = (UNs *)E_FROM_INI_TOP;					//設定値初期ﾃﾞｰﾀｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//ﾌﾗｯｼｭROMの連続回転設定値
	memcpy_word(&SV_MOTDEG0_001, src_p, 0x1800/2);
#endif

	FRAM_csum_set();								//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成


	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];		//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ
	src_p = (UNs *)E_FROM_INI_TOP2;					//設定値初期ﾃﾞｰﾀ型名称ｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&KAT_NAME_01[0], src_p, cnt);

//V06n
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];		//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ
	src_p = (UNs *)E_FROM_INI_TOP3;					//設定値初期ﾃﾞｰﾀ型名称ｱﾄﾞﾚｽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&KAT_NAME_101[0], src_p, cnt);

	FRAM_KAT_csum_set();							//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	SVSW_CHG_FLG = 0x013f;
	ONOFF_sub();									//仕様有り無しによる入切制御

	mmon_sel_chk();									//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
	mmon_trans_get();								//回転方式によるﾃﾞｰﾀの取得

	CAR_mkssi_set();								//単位切換データ格納処理
	CAMname_pon_read();								//電源投入時の汎用ｶﾑ名称の読込み
	SURA_sv_chg();									//ｽﾗｲﾄﾞ自動調節ＳＶ変更処理
	SEI_ON6_LST1 = 0xff;							//電源投入時必ず段取りの項目有無チェックをするため。

	PV_MLDNO1_F1 = 1;									//型データの初期値を挿入
	memcpy_word(&PV_MLDNO2_F1[0], &KAT_NAME_01[0], 8);	//型データ名称１を挿入
	memcpy_word(&PV_MLDNO3_F1[0], &KAT_MEMO_01[0], 8);	//型データメモ１を挿入

	FRAM_csum_set();								//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成


//V06n	for(cnt=100, i=1 ; cnt > 0 ; cnt--, i++){
//SIT4-MC	for(cnt=200, i=1 ; cnt > 0 ; cnt--, i++){
	for(cnt=220, i=1 ; cnt > 0 ; cnt--, i++){
		WDT_Rifresh();								//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ
		kata_save(i, &FRAM_KAT_TOP);				//型データをFROMへ格納
	}

#if (mot100_test == 1)
	for(cnt=220, i=1 ; cnt > 0 ; cnt--, i++){
		kata_save2(i, &SV_MOTDEG0_001);				//型データ(100段モーション)をFROMへ格納
	}
#endif


	SURA_CHG_LST = 0;								//型データを読んだ後に正常に動作しない
	SET_SPM_LST = 0;

	MCN_MENT_CNT1 = 0;								//メンテナンスカウンタ１
	MCN_MENT_CNT2 = 0;								//メンテナンスカウンタ２
	MCN_MENT_CNT3 = 0;								//メンテナンスカウンタ３
	MCN_MENT_CNT4 = 0;								//メンテナンスカウンタ４
	MCN_MENT_CNT5 = 0;								//メンテナンスカウンタ５
	MCN_MENT_CNT6 = 0;								//メンテナンスカウンタ６
	MCN_MENT_CNT7 = 0;								//メンテナンスカウンタ７
	MCN_MENT_CNT8 = 0;								//メンテナンスカウンタ８
	MCN_MENT_TIM1 = 0;								//メンテナンス時間１（1secカウンタ）
	MCN_MENT_TIM1_10 = 0;							//メンテナンス時間１（10msecカウンタ）
	MCN_MENT_TIM2 = 0;								//メンテナンス時間２（1secカウンタ）
	MCN_MENT_TIM2_10 = 0;							//メンテナンス時間２（10msecカウンタ）
	MCN_MENT_TIM3 = 0;								//メンテナンス時間３（1secカウンタ）
	MCN_MENT_TIM3_10 = 0;							//メンテナンス時間３（10msecカウンタ）

	PV_LIFE_COUNT[0] = 0;							//機械総カウンタ
	PV_LIFE_COUNT[1] = 0;							//機械総カウンタ
	PV_LIFE_COUNT[2] = 0;							//機械総カウンタ
	PV_LIFE_TIME_10 = 0;							//機械総時間（10msecカウンタ）
	PV_LIFE_TIME = 0;								//機械総時間（1secカウンタ）

	PV_GAIN_BAK1L = 0;								//最大歪み２０００左ゲイン
	PV_GAIN_BAK1R = 0;								//最大歪み２０００右ゲイン
	PV_GAIN_BAK2L = 0;								//最大歪み１５００左ゲイン
	PV_GAIN_BAK2R = 0;								//最大歪み１５００右ゲイン
	PV_GAIN_BAK3L = 0;								//最大歪み　８００左ゲイン
	PV_GAIN_BAK3R = 0;								//最大歪み　８００右ゲイン
	PV_GAIN_BAK4L = 0;								//最大歪み　４００左ゲイン
	PV_GAIN_BAK4R = 0;								//最大歪み　４００右ゲイン
	PV_GAIN_BAK5L = 0;								//最大歪み　２００左ゲイン
	PV_GAIN_BAK5R = 0;								//最大歪み　２００右ゲイン
	PV_OF_BAKL = 0;									//オフセット値左
	PV_OF_BAKR = 0;									//オフセット値右
	PV_OF_AVE_BAKL = 0;								//オフセット補正左
	PV_OF_AVE_BAKR = 0;								//オフセット補正右
	PV_OF_AVE_BAKT = 0;								//オフセット補正合計
	PV_GENITI_B2 = 0;								//現位置データ

}


/*
********************************************************************************
*  Function Name:	データ切替（mm⇔inch）
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
void	KAT_mm_2_inch_all(void)
{
	short	wk_S2b;
	UNs		c;
	UNl		*dst_l, *src_l;

	//モーション回転データ
#if (mot100_test == 1)										//2017/08/21
	dst_l = &SV_MOTPOS0_001;								//
	src_l = &SV_MOTPOS0_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_mm_inch2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS0_SRV		= cnv_mm_inch2(SV_1DANPOS0_SRV, 0);			//目標位置1
	SV_2DANPOS0_SRV		= cnv_mm_inch2(SV_2DANPOS0_SRV, 0);			//目標位置2
	SV_3DANPOS0_SRV		= cnv_mm_inch2(SV_3DANPOS0_SRV, 0);			//目標位置3
	SV_4DANPOS0_SRV		= cnv_mm_inch2(SV_4DANPOS0_SRV, 0);			//目標位置4
	SV_5DANPOS0_SRV		= cnv_mm_inch2(SV_5DANPOS0_SRV, 0);			//目標位置5
	SV_6DANPOS0_SRV		= cnv_mm_inch2(SV_6DANPOS0_SRV, 0);			//目標位置6
	SV_7DANPOS0_SRV		= cnv_mm_inch2(SV_7DANPOS0_SRV, 0);			//目標位置7
	SV_8DANPOS0_SRV		= cnv_mm_inch2(SV_8DANPOS0_SRV, 0);			//目標位置8
	SV_9DANPOS0_SRV		= cnv_mm_inch2(SV_9DANPOS0_SRV, 0);			//目標位置9
	SV_10DANPOS0_SRV	= cnv_mm_inch2(SV_10DANPOS0_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS0_SRV	= cnv_mm_inch2(SV_TAIKIPOS0_SRV, 0);		//上限位置
	SV_DAIHAITO0_SRV	= cnv_mm_inch2(SV_DAIHAITO0_SRV, 0);		//下限位置
	SV_HOASEI0_SRV		= cnv_um_uinch2(SV_HOASEI0_SRV, 0);			//下限補正
	SV_MOKKAN0_SRV		= cnv_mm_inch2(SV_MOKKAN0_SRV, 0);			//目標完了範囲

	//モーション反転データ
#if (mot100_test == 1)										//2017/08/21
	dst_l = &SV_MOTPOS1_001;								//
	src_l = &SV_MOTPOS1_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_mm_inch2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS1_SRV		= cnv_mm_inch2(SV_1DANPOS1_SRV, 0);			//目標位置1
	SV_2DANPOS1_SRV		= cnv_mm_inch2(SV_2DANPOS1_SRV, 0);			//目標位置2
	SV_3DANPOS1_SRV		= cnv_mm_inch2(SV_3DANPOS1_SRV, 0);			//目標位置3
	SV_4DANPOS1_SRV		= cnv_mm_inch2(SV_4DANPOS1_SRV, 0);			//目標位置4
	SV_5DANPOS1_SRV		= cnv_mm_inch2(SV_5DANPOS1_SRV, 0);			//目標位置5
	SV_6DANPOS1_SRV		= cnv_mm_inch2(SV_6DANPOS1_SRV, 0);			//目標位置6
	SV_7DANPOS1_SRV		= cnv_mm_inch2(SV_7DANPOS1_SRV, 0);			//目標位置7
	SV_8DANPOS1_SRV		= cnv_mm_inch2(SV_8DANPOS1_SRV, 0);			//目標位置8
	SV_9DANPOS1_SRV		= cnv_mm_inch2(SV_9DANPOS1_SRV, 0);			//目標位置9
	SV_10DANPOS1_SRV	= cnv_mm_inch2(SV_10DANPOS1_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS1_SRV	= cnv_mm_inch2(SV_TAIKIPOS1_SRV, 0);		//上限位置
	SV_DAIHAITO1_SRV	= cnv_mm_inch2(SV_DAIHAITO1_SRV, 0);		//下限位置
	SV_HOASEI1_SRV		= cnv_um_uinch2(SV_HOASEI1_SRV, 0);			//下限補正
	SV_MOKKAN1_SRV		= cnv_mm_inch2(SV_MOKKAN1_SRV, 0);			//目標完了範囲

	//モーション振子データ
#if (mot100_test == 1)										//2017/08/21
	dst_l = &SV_MOTPOS2_001;								//
	src_l = &SV_MOTPOS2_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_mm_inch2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS2_SRV		= cnv_mm_inch2(SV_1DANPOS2_SRV, 0);			//目標位置1
	SV_2DANPOS2_SRV		= cnv_mm_inch2(SV_2DANPOS2_SRV, 0);			//目標位置2
	SV_3DANPOS2_SRV		= cnv_mm_inch2(SV_3DANPOS2_SRV, 0);			//目標位置3
	SV_4DANPOS2_SRV		= cnv_mm_inch2(SV_4DANPOS2_SRV, 0);			//目標位置4
	SV_5DANPOS2_SRV		= cnv_mm_inch2(SV_5DANPOS2_SRV, 0);			//目標位置5
	SV_6DANPOS2_SRV		= cnv_mm_inch2(SV_6DANPOS2_SRV, 0);			//目標位置6
	SV_7DANPOS2_SRV		= cnv_mm_inch2(SV_7DANPOS2_SRV, 0);			//目標位置7
	SV_8DANPOS2_SRV		= cnv_mm_inch2(SV_8DANPOS2_SRV, 0);			//目標位置8
	SV_9DANPOS2_SRV		= cnv_mm_inch2(SV_9DANPOS2_SRV, 0);			//目標位置9
	SV_10DANPOS2_SRV	= cnv_mm_inch2(SV_10DANPOS2_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS2_SRV	= cnv_mm_inch2(SV_TAIKIPOS2_SRV, 0);		//上限位置
	SV_DAIHAITO2_SRV	= cnv_mm_inch2(SV_DAIHAITO2_SRV, 0);		//下限位置
	SV_HOASEI2_SRV		= cnv_um_uinch2(SV_HOASEI2_SRV, 0);			//下限補正
	SV_MOKKAN2_SRV		= cnv_mm_inch2(SV_MOKKAN2_SRV, 0);			//目標完了範囲

	//モーション上往復データ
#if (mot100_test == 1)										//2017/08/21
	dst_l = &SV_MOTPOS3_001;								//
	src_l = &SV_MOTPOS3_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_mm_inch2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS3_SRV		= cnv_mm_inch2(SV_1DANPOS3_SRV, 0);			//目標位置1
	SV_2DANPOS3_SRV		= cnv_mm_inch2(SV_2DANPOS3_SRV, 0);			//目標位置2
	SV_3DANPOS3_SRV		= cnv_mm_inch2(SV_3DANPOS3_SRV, 0);			//目標位置3
	SV_4DANPOS3_SRV		= cnv_mm_inch2(SV_4DANPOS3_SRV, 0);			//目標位置4
	SV_5DANPOS3_SRV		= cnv_mm_inch2(SV_5DANPOS3_SRV, 0);			//目標位置5
	SV_6DANPOS3_SRV		= cnv_mm_inch2(SV_6DANPOS3_SRV, 0);			//目標位置6
	SV_7DANPOS3_SRV		= cnv_mm_inch2(SV_7DANPOS3_SRV, 0);			//目標位置7
	SV_8DANPOS3_SRV		= cnv_mm_inch2(SV_8DANPOS3_SRV, 0);			//目標位置8
	SV_9DANPOS3_SRV		= cnv_mm_inch2(SV_9DANPOS3_SRV, 0);			//目標位置9
	SV_10DANPOS3_SRV	= cnv_mm_inch2(SV_10DANPOS3_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS3_SRV	= cnv_mm_inch2(SV_TAIKIPOS3_SRV, 0);		//上限位置
	SV_DAIHAITO3_SRV	= cnv_mm_inch2(SV_DAIHAITO3_SRV, 0);		//下限位置
	SV_HOASEI3_SRV		= cnv_um_uinch2(SV_HOASEI3_SRV, 0);			//下限補正
	SV_MOKKAN3_SRV		= cnv_mm_inch2(SV_MOKKAN3_SRV, 0);			//目標完了範囲

	//スライド自動調節
	if (SV_POINT_A1 == 1) {
		SV_ATUOS0_D9		= cnv_mm_inch2(SV_ATUOS0_D9*100, 0);			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_mm_inch2(SV_ATUOS1_D9*100, 0);			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_mm_inch2(SV_ATUOS2_D9*100, 0);			//スライド自動調節　段取り２設定
	}
	else if (SV_POINT_A1 == 3) {
		SV_ATUOS0_D9		= cnv_mm_inch2(SV_ATUOS0_D9, 0);			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_mm_inch2(SV_ATUOS1_D9, 0);			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_mm_inch2(SV_ATUOS2_D9, 0);			//スライド自動調節　段取り２設定
	}
	else {
		SV_ATUOS0_D9		= cnv_mm_inch2(SV_ATUOS0_D9*10, 0);			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_mm_inch2(SV_ATUOS1_D9*10, 0);			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_mm_inch2(SV_ATUOS2_D9*10, 0);			//スライド自動調節　段取り２設定
	}

	//スライド自動待機
	SV_INTLIM_POS		= cnv_mm_inch2(SV_INTLIM_POS, 0);			//干渉限界位置　位置

	//ダイクッション
	if (SV_POINT_A47 == 1) {
		SV_DAIKA1_C27		= cnv_mm_inch2(SV_DAIKA1_C27*100, 0);			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_mm_inch2(SV_DAIKA2_C27*100, 0);			//ダイクッション調節２
	}
	else if (SV_POINT_A47 == 3) {
		SV_DAIKA1_C27		= cnv_mm_inch2(SV_DAIKA1_C27, 0);			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_mm_inch2(SV_DAIKA2_C27, 0);			//ダイクッション調節２
	}
	else {
		SV_DAIKA1_C27		= cnv_mm_inch2(SV_DAIKA1_C27*10, 0);			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_mm_inch2(SV_DAIKA2_C27*10, 0);			//ダイクッション調節２
	}

	//レベラフィーダ	2016/03/24
	SV_LFEED_LNG1		= cnv_mm_inch2(SV_LFEED_LNG1*10, 0);			//送り長さ
	if ((short)SV_LFEED_HOSIN < 0) {
		wk_S2b = SV_LFEED_HOSIN;
		wk_S2b *= 10;													//小数点3桁へ
		wk_S2b *= -1;													//絶対値
		wk_S2b = cnv_mm_inch2(wk_S2b, 0);
		SV_LFEED_HOSIN		= wk_S2b * -1;								//矯正量入口
	}
	else {
		SV_LFEED_HOSIN		= cnv_mm_inch2(SV_LFEED_HOSIN*10, 0);		//矯正量入口
	}
	if ((short)SV_LFEED_HOSOT < 0) {
		wk_S2b = SV_LFEED_HOSOT;
		wk_S2b *= 10;													//小数点3桁へ
		wk_S2b *= -1;													//絶対値
		wk_S2b = cnv_mm_inch2(wk_S2b, 0);
		SV_LFEED_HOSOT		= wk_S2b * -1;								//矯正量出口
	}
	else {
		SV_LFEED_HOSOT		= cnv_mm_inch2(SV_LFEED_HOSOT*10, 0);		//矯正量出口
	}
	SV_LFEED_STRPOS		= cnv_mm_inch2(SV_LFEED_STRPOS, 0);				//送り位置
	SV_LFEED_ENDPOS		= cnv_mm_inch2(SV_LFEED_ENDPOS, 0);				//リリース位置

	SV_KAT_MM_INCH = 1;				//inch通常データ
}

void	SYS_mm_2_inch_all(void)
{
	//見える化画面
	SV_WAVE_SCL1U		= cnv_mm_inch2(SV_WAVE_SCL1U, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL1D		= cnv_mm_inch2(SV_WAVE_SCL1D, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL3U		= cnv_mm_inch2(SV_WAVE_SCL3U, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ﾄﾚﾝﾄﾞ画面)
	SV_WAVE_SCL3D		= cnv_mm_inch2(SV_WAVE_SCL3D, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ﾄﾚﾝﾄﾞ画面)

	//一定速度領域
	SV0_FIXARA_POSS		= cnv_mm_inch2(SV0_FIXARA_POSS, 0);			//一定領域　開始位置
	SV0_FIXARA_POSE		= cnv_mm_inch2(SV0_FIXARA_POSE, 0);			//一定領域　終了位置

	//トレンド
	SV_TRDCSR_RNAU		= cnv_mm_inch2(SV_TRDCSR_RNAU, 0);			//ｽﾗｲﾄﾞ位置上限検出位置
	SV_TRDCSR_RNAD		= cnv_mm_inch2(SV_TRDCSR_RNAD, 0);			//ｽﾗｲﾄﾞ位置下限検出位置

	//多段モーション	2017/08/21
	SV_MSSTAT_POS		= cnv_mm_inch2(SV_MSSTAT_POS, 0);			//多段モーション開始位置
	SV_MSEND_POS		= cnv_mm_inch2(SV_MSEND_POS, 0);			//多段モーション終了位置
}

void	KAT_inch_2_mm_all(void)
{
	short	wk_S2b;
	UNs		c;
	UNl		*dst_l, *src_l;

	//モーション回転データ
#if (mot100_test == 1)
	dst_l = &SV_MOTPOS0_001;								//
	src_l = &SV_MOTPOS0_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_inch_mm2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS0_SRV		= cnv_inch_mm2(SV_1DANPOS0_SRV, 0);			//目標位置1
	SV_2DANPOS0_SRV		= cnv_inch_mm2(SV_2DANPOS0_SRV, 0);			//目標位置2
	SV_3DANPOS0_SRV		= cnv_inch_mm2(SV_3DANPOS0_SRV, 0);			//目標位置3
	SV_4DANPOS0_SRV		= cnv_inch_mm2(SV_4DANPOS0_SRV, 0);			//目標位置4
	SV_5DANPOS0_SRV		= cnv_inch_mm2(SV_5DANPOS0_SRV, 0);			//目標位置5
	SV_6DANPOS0_SRV		= cnv_inch_mm2(SV_6DANPOS0_SRV, 0);			//目標位置6
	SV_7DANPOS0_SRV		= cnv_inch_mm2(SV_7DANPOS0_SRV, 0);			//目標位置7
	SV_8DANPOS0_SRV		= cnv_inch_mm2(SV_8DANPOS0_SRV, 0);			//目標位置8
	SV_9DANPOS0_SRV		= cnv_inch_mm2(SV_9DANPOS0_SRV, 0);			//目標位置9
	SV_10DANPOS0_SRV	= cnv_inch_mm2(SV_10DANPOS0_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS0_SRV	= cnv_inch_mm2(SV_TAIKIPOS0_SRV, 0);		//上限位置
	SV_DAIHAITO0_SRV	= cnv_inch_mm2(SV_DAIHAITO0_SRV, 0);		//下限位置
	SV_HOASEI0_SRV		= cnv_uinch_um2(SV_HOASEI0_SRV, 0);			//下限補正
	SV_MOKKAN0_SRV		= cnv_inch_mm2(SV_MOKKAN0_SRV, 0);			//目標完了範囲

	//モーション反転データ
#if (mot100_test == 1)
	dst_l = &SV_MOTPOS1_001;								//
	src_l = &SV_MOTPOS1_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_inch_mm2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS1_SRV		= cnv_inch_mm2(SV_1DANPOS1_SRV, 0);			//目標位置1
	SV_2DANPOS1_SRV		= cnv_inch_mm2(SV_2DANPOS1_SRV, 0);			//目標位置2
	SV_3DANPOS1_SRV		= cnv_inch_mm2(SV_3DANPOS1_SRV, 0);			//目標位置3
	SV_4DANPOS1_SRV		= cnv_inch_mm2(SV_4DANPOS1_SRV, 0);			//目標位置4
	SV_5DANPOS1_SRV		= cnv_inch_mm2(SV_5DANPOS1_SRV, 0);			//目標位置5
	SV_6DANPOS1_SRV		= cnv_inch_mm2(SV_6DANPOS1_SRV, 0);			//目標位置6
	SV_7DANPOS1_SRV		= cnv_inch_mm2(SV_7DANPOS1_SRV, 0);			//目標位置7
	SV_8DANPOS1_SRV		= cnv_inch_mm2(SV_8DANPOS1_SRV, 0);			//目標位置8
	SV_9DANPOS1_SRV		= cnv_inch_mm2(SV_9DANPOS1_SRV, 0);			//目標位置9
	SV_10DANPOS1_SRV	= cnv_inch_mm2(SV_10DANPOS1_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS1_SRV	= cnv_inch_mm2(SV_TAIKIPOS1_SRV, 0);		//上限位置
	SV_DAIHAITO1_SRV	= cnv_inch_mm2(SV_DAIHAITO1_SRV, 0);		//下限位置
	SV_HOASEI1_SRV		= cnv_uinch_um2(SV_HOASEI1_SRV, 0);			//下限補正
	SV_MOKKAN1_SRV		= cnv_inch_mm2(SV_MOKKAN1_SRV, 0);			//目標完了範囲

	//モーション振子データ
#if (mot100_test == 1)
	dst_l = &SV_MOTPOS2_001;								//
	src_l = &SV_MOTPOS2_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_inch_mm2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS2_SRV		= cnv_inch_mm2(SV_1DANPOS2_SRV, 0);			//目標位置1
	SV_2DANPOS2_SRV		= cnv_inch_mm2(SV_2DANPOS2_SRV, 0);			//目標位置2
	SV_3DANPOS2_SRV		= cnv_inch_mm2(SV_3DANPOS2_SRV, 0);			//目標位置3
	SV_4DANPOS2_SRV		= cnv_inch_mm2(SV_4DANPOS2_SRV, 0);			//目標位置4
	SV_5DANPOS2_SRV		= cnv_inch_mm2(SV_5DANPOS2_SRV, 0);			//目標位置5
	SV_6DANPOS2_SRV		= cnv_inch_mm2(SV_6DANPOS2_SRV, 0);			//目標位置6
	SV_7DANPOS2_SRV		= cnv_inch_mm2(SV_7DANPOS2_SRV, 0);			//目標位置7
	SV_8DANPOS2_SRV		= cnv_inch_mm2(SV_8DANPOS2_SRV, 0);			//目標位置8
	SV_9DANPOS2_SRV		= cnv_inch_mm2(SV_9DANPOS2_SRV, 0);			//目標位置9
	SV_10DANPOS2_SRV	= cnv_inch_mm2(SV_10DANPOS2_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS2_SRV	= cnv_inch_mm2(SV_TAIKIPOS2_SRV, 0);		//上限位置
	SV_DAIHAITO2_SRV	= cnv_inch_mm2(SV_DAIHAITO2_SRV, 0);		//下限位置
	SV_HOASEI2_SRV		= cnv_uinch_um2(SV_HOASEI2_SRV, 0);			//下限補正
	SV_MOKKAN2_SRV		= cnv_inch_mm2(SV_MOKKAN2_SRV, 0);			//目標完了範囲

	//モーション上往復データ
#if (mot100_test == 1)
	dst_l = &SV_MOTPOS3_001;								//
	src_l = &SV_MOTPOS3_001;								//FRAM
	for (c=0; c<100; c++, dst_l++, src_l++) {
		*dst_l = cnv_inch_mm2(*src_l, 0);					//目標位置
	}
#else
	SV_1DANPOS3_SRV		= cnv_inch_mm2(SV_1DANPOS3_SRV, 0);			//目標位置1
	SV_2DANPOS3_SRV		= cnv_inch_mm2(SV_2DANPOS3_SRV, 0);			//目標位置2
	SV_3DANPOS3_SRV		= cnv_inch_mm2(SV_3DANPOS3_SRV, 0);			//目標位置3
	SV_4DANPOS3_SRV		= cnv_inch_mm2(SV_4DANPOS3_SRV, 0);			//目標位置4
	SV_5DANPOS3_SRV		= cnv_inch_mm2(SV_5DANPOS3_SRV, 0);			//目標位置5
	SV_6DANPOS3_SRV		= cnv_inch_mm2(SV_6DANPOS3_SRV, 0);			//目標位置6
	SV_7DANPOS3_SRV		= cnv_inch_mm2(SV_7DANPOS3_SRV, 0);			//目標位置7
	SV_8DANPOS3_SRV		= cnv_inch_mm2(SV_8DANPOS3_SRV, 0);			//目標位置8
	SV_9DANPOS3_SRV		= cnv_inch_mm2(SV_9DANPOS3_SRV, 0);			//目標位置9
	SV_10DANPOS3_SRV	= cnv_inch_mm2(SV_10DANPOS3_SRV, 0);		//目標位置10
#endif
	SV_TAIKIPOS3_SRV	= cnv_inch_mm2(SV_TAIKIPOS3_SRV, 0);		//上限位置
	SV_DAIHAITO3_SRV	= cnv_inch_mm2(SV_DAIHAITO3_SRV, 0);		//下限位置
	SV_HOASEI3_SRV		= cnv_uinch_um2(SV_HOASEI3_SRV, 0);			//下限補正
	SV_MOKKAN3_SRV		= cnv_inch_mm2(SV_MOKKAN3_SRV, 0);			//目標完了範囲

	//スライド自動調節
	if (SV_POINT_A1 == 1) {
		SV_ATUOS0_D9		= cnv_inch_mm2(SV_ATUOS0_D9, 0)/100;			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_inch_mm2(SV_ATUOS1_D9, 0)/100;			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_inch_mm2(SV_ATUOS2_D9, 0)/100;			//スライド自動調節　段取り２設定
	}
	else if (SV_POINT_A1 == 3) {
		SV_ATUOS0_D9		= cnv_inch_mm2(SV_ATUOS0_D9, 0);			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_inch_mm2(SV_ATUOS1_D9, 0);			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_inch_mm2(SV_ATUOS2_D9, 0);			//スライド自動調節　段取り２設定
	}
	else {
		SV_ATUOS0_D9		= cnv_inch_mm2(SV_ATUOS0_D9, 0)/10;			//スライド自動調節　生産設定
		SV_ATUOS1_D9		= cnv_inch_mm2(SV_ATUOS1_D9, 0)/10;			//スライド自動調節　段取り１設定
		SV_ATUOS2_D9		= cnv_inch_mm2(SV_ATUOS2_D9, 0)/10;			//スライド自動調節　段取り２設定
	}

	//スライド自動待機
	SV_INTLIM_POS		= cnv_inch_mm2(SV_INTLIM_POS, 0);			//干渉限界位置　位置

	//ダイクッション
	if (SV_POINT_A47 == 1) {
		SV_DAIKA1_C27		= cnv_inch_mm2(SV_DAIKA1_C27, 0)/100;			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_inch_mm2(SV_DAIKA2_C27, 0)/100;			//ダイクッション調節２
	}
	else if (SV_POINT_A47 == 3) {
		SV_DAIKA1_C27		= cnv_inch_mm2(SV_DAIKA1_C27, 0);			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_inch_mm2(SV_DAIKA2_C27, 0);			//ダイクッション調節２
	}
	else {
		SV_DAIKA1_C27		= cnv_inch_mm2(SV_DAIKA1_C27, 0)/10;			//ダイクッション調節１
		SV_DAIKA2_C27		= cnv_inch_mm2(SV_DAIKA2_C27, 0)/10;			//ダイクッション調節２
	}

	//レベラフィーダ	2016/03/24
	SV_LFEED_LNG1		= cnv_inch_mm2(SV_LFEED_LNG1, 0)/10;			//送り長さ
	if ((short)SV_LFEED_HOSIN < 0) {
		wk_S2b = SV_LFEED_HOSIN;
		wk_S2b *= -1;													//絶対値
		wk_S2b = cnv_inch_mm2(wk_S2b, 0) / 10;
		SV_LFEED_HOSIN		= wk_S2b * -1;								//矯正量入口
	}
	else {
		SV_LFEED_HOSIN		= cnv_inch_mm2(SV_LFEED_HOSIN, 0)/10;		//矯正量入口
	}
	if ((short)SV_LFEED_HOSOT < 0) {
		wk_S2b = SV_LFEED_HOSOT;
		wk_S2b *= -1;													//絶対値
		wk_S2b = cnv_inch_mm2(wk_S2b, 0) / 10;
		SV_LFEED_HOSOT		= wk_S2b * -1;								//矯正量出口
	}
	else {
		SV_LFEED_HOSOT		= cnv_inch_mm2(SV_LFEED_HOSOT, 0)/10;		//矯正量出口
	}
	SV_LFEED_STRPOS		= cnv_inch_mm2(SV_LFEED_STRPOS, 0);				//送り位置
	SV_LFEED_ENDPOS		= cnv_inch_mm2(SV_LFEED_ENDPOS, 0);				//リリース位置

	SV_KAT_MM_INCH = 0;				//mm通常データ
}

void	SYS_inch_2_mm_all(void)
{
	//見える化画面
	SV_WAVE_SCL1U		= cnv_inch_mm2(SV_WAVE_SCL1U, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL1D		= cnv_inch_mm2(SV_WAVE_SCL1D, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL3U		= cnv_inch_mm2(SV_WAVE_SCL3U, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ﾄﾚﾝﾄﾞ画面)
	SV_WAVE_SCL3D		= cnv_inch_mm2(SV_WAVE_SCL3D, 0);			//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ﾄﾚﾝﾄﾞ画面)

	//一定速度領域
	SV0_FIXARA_POSS		= cnv_inch_mm2(SV0_FIXARA_POSS, 0);			//一定領域　開始位置
	SV0_FIXARA_POSE		= cnv_inch_mm2(SV0_FIXARA_POSE, 0);			//一定領域　終了位置

	//トレンド
	SV_TRDCSR_RNAU		= cnv_inch_mm2(SV_TRDCSR_RNAU, 0);			//ｽﾗｲﾄﾞ位置上限検出位置
	SV_TRDCSR_RNAD		= cnv_inch_mm2(SV_TRDCSR_RNAD, 0);			//ｽﾗｲﾄﾞ位置下限検出位置

	//多段モーション	2017/08/21
	SV_MSSTAT_POS		= cnv_inch_mm2(SV_MSSTAT_POS, 0);			//多段モーション開始位置
	SV_MSEND_POS		= cnv_inch_mm2(SV_MSEND_POS, 0);			//多段モーション終了位置
}

void	KAT_keta_up(void)
{
	//モーション回転データ
	SV_1DANPOS0_SRV		*= 10;		//目標位置1
	SV_2DANPOS0_SRV		*= 10;		//目標位置2
	SV_3DANPOS0_SRV		*= 10;		//目標位置3
	SV_4DANPOS0_SRV		*= 10;		//目標位置4
	SV_5DANPOS0_SRV		*= 10;		//目標位置5
	SV_6DANPOS0_SRV		*= 10;		//目標位置6
	SV_7DANPOS0_SRV		*= 10;		//目標位置7
	SV_8DANPOS0_SRV		*= 10;		//目標位置8
	SV_9DANPOS0_SRV		*= 10;		//目標位置9
	SV_10DANPOS0_SRV	*= 10;		//目標位置10
	SV_TAIKIPOS0_SRV	*= 10;		//上限位置
	SV_DAIHAITO0_SRV	*= 10;		//下限位置
	SV_MOKKAN0_SRV		*= 10;		//目標完了範囲

	//モーション反転データ
	SV_1DANPOS1_SRV		*= 10;		//目標位置1
	SV_2DANPOS1_SRV		*= 10;		//目標位置2
	SV_3DANPOS1_SRV		*= 10;		//目標位置3
	SV_4DANPOS1_SRV		*= 10;		//目標位置4
	SV_5DANPOS1_SRV		*= 10;		//目標位置5
	SV_6DANPOS1_SRV		*= 10;		//目標位置6
	SV_7DANPOS1_SRV		*= 10;		//目標位置7
	SV_8DANPOS1_SRV		*= 10;		//目標位置8
	SV_9DANPOS1_SRV		*= 10;		//目標位置9
	SV_10DANPOS1_SRV	*= 10;		//目標位置10
	SV_TAIKIPOS1_SRV	*= 10;		//上限位置
	SV_DAIHAITO1_SRV	*= 10;		//下限位置
	SV_MOKKAN1_SRV		*= 10;		//目標完了範囲

	//モーション振子データ
	SV_1DANPOS2_SRV		*= 10;		//目標位置1
	SV_2DANPOS2_SRV		*= 10;		//目標位置2
	SV_3DANPOS2_SRV		*= 10;		//目標位置3
	SV_4DANPOS2_SRV		*= 10;		//目標位置4
	SV_5DANPOS2_SRV		*= 10;		//目標位置5
	SV_6DANPOS2_SRV		*= 10;		//目標位置6
	SV_7DANPOS2_SRV		*= 10;		//目標位置7
	SV_8DANPOS2_SRV		*= 10;		//目標位置8
	SV_9DANPOS2_SRV		*= 10;		//目標位置9
	SV_10DANPOS2_SRV	*= 10;		//目標位置10
	SV_TAIKIPOS2_SRV	*= 10;		//上限位置
	SV_DAIHAITO2_SRV	*= 10;		//下限位置
	SV_MOKKAN2_SRV		*= 10;		//目標完了範囲

	//モーション上往復データ
	SV_1DANPOS3_SRV		*= 10;		//目標位置1
	SV_2DANPOS3_SRV		*= 10;		//目標位置2
	SV_3DANPOS3_SRV		*= 10;		//目標位置3
	SV_4DANPOS3_SRV		*= 10;		//目標位置4
	SV_5DANPOS3_SRV		*= 10;		//目標位置5
	SV_6DANPOS3_SRV		*= 10;		//目標位置6
	SV_7DANPOS3_SRV		*= 10;		//目標位置7
	SV_8DANPOS3_SRV		*= 10;		//目標位置8
	SV_9DANPOS3_SRV		*= 10;		//目標位置9
	SV_10DANPOS3_SRV	*= 10;		//目標位置10
	SV_TAIKIPOS3_SRV	*= 10;		//上限位置
	SV_DAIHAITO3_SRV	*= 10;		//下限位置
	SV_MOKKAN3_SRV		*= 10;		//目標完了範囲

	//スライド自動調節
	SV_ATUOS0_D9		*= 10;		//スライド自動調節　生産設定
	SV_ATUOS1_D9		*= 10;		//スライド自動調節　段取り１設定
	SV_ATUOS2_D9		*= 10;		//スライド自動調節　段取り２設定

	//スライド自動待機
	SV_INTLIM_POS		*= 10;		//干渉限界位置　位置

	//ダイクッション
	SV_DAIKA1_C27		*= 10;		//ダイクッション調節１
	SV_DAIKA2_C27		*= 10;		//ダイクッション調節２

	//レベラフィーダ	2016/03/24
	SV_LFEED_LNG1		*= 10;		//送り長さ
	SV_LFEED_HOSIN		*= 10;		//矯正量入口
	SV_LFEED_HOSOT		*= 10;		//矯正量出口
	SV_LFEED_STRPOS		*= 10;		//送り位置
	SV_LFEED_ENDPOS		*= 10;		//リリース位置

	SV_KAT_MM_INCH = 2;				//inch高精度データ
}

void	SYS_keta_up(void)
{
	//見える化画面
	SV_WAVE_SCL1U		*= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL1D		*= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL3U		*= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ﾄﾚﾝﾄﾞ画面)
	SV_WAVE_SCL3D		*= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ﾄﾚﾝﾄﾞ画面)

	//一定速度領域
	SV0_FIXARA_POSS		*= 10;		//一定領域　開始位置
	SV0_FIXARA_POSE		*= 10;		//一定領域　終了位置

	//トレンド
	SV_TRDCSR_RNAU		*= 10;		//ｽﾗｲﾄﾞ位置上限検出位置
	SV_TRDCSR_RNAD		*= 10;		//ｽﾗｲﾄﾞ位置下限検出位置
}

void	KAT_keta_down(void)
{
	//モーション回転データ
	SV_1DANPOS0_SRV		/= 10;		//目標位置1
	SV_2DANPOS0_SRV		/= 10;		//目標位置2
	SV_3DANPOS0_SRV		/= 10;		//目標位置3
	SV_4DANPOS0_SRV		/= 10;		//目標位置4
	SV_5DANPOS0_SRV		/= 10;		//目標位置5
	SV_6DANPOS0_SRV		/= 10;		//目標位置6
	SV_7DANPOS0_SRV		/= 10;		//目標位置7
	SV_8DANPOS0_SRV		/= 10;		//目標位置8
	SV_9DANPOS0_SRV		/= 10;		//目標位置9
	SV_10DANPOS0_SRV	/= 10;		//目標位置10
	SV_TAIKIPOS0_SRV	/= 10;		//上限位置
	SV_DAIHAITO0_SRV	/= 10;		//下限位置
	SV_MOKKAN0_SRV		/= 10;		//目標完了範囲

	//モーション反転データ
	SV_1DANPOS1_SRV		/= 10;		//目標位置1
	SV_2DANPOS1_SRV		/= 10;		//目標位置2
	SV_3DANPOS1_SRV		/= 10;		//目標位置3
	SV_4DANPOS1_SRV		/= 10;		//目標位置4
	SV_5DANPOS1_SRV		/= 10;		//目標位置5
	SV_6DANPOS1_SRV		/= 10;		//目標位置6
	SV_7DANPOS1_SRV		/= 10;		//目標位置7
	SV_8DANPOS1_SRV		/= 10;		//目標位置8
	SV_9DANPOS1_SRV		/= 10;		//目標位置9
	SV_10DANPOS1_SRV	/= 10;		//目標位置10
	SV_TAIKIPOS1_SRV	/= 10;		//上限位置
	SV_DAIHAITO1_SRV	/= 10;		//下限位置
	SV_MOKKAN1_SRV		/= 10;		//目標完了範囲

	//モーション振子データ
	SV_1DANPOS2_SRV		/= 10;		//目標位置1
	SV_2DANPOS2_SRV		/= 10;		//目標位置2
	SV_3DANPOS2_SRV		/= 10;		//目標位置3
	SV_4DANPOS2_SRV		/= 10;		//目標位置4
	SV_5DANPOS2_SRV		/= 10;		//目標位置5
	SV_6DANPOS2_SRV		/= 10;		//目標位置6
	SV_7DANPOS2_SRV		/= 10;		//目標位置7
	SV_8DANPOS2_SRV		/= 10;		//目標位置8
	SV_9DANPOS2_SRV		/= 10;		//目標位置9
	SV_10DANPOS2_SRV	/= 10;		//目標位置10
	SV_TAIKIPOS2_SRV	/= 10;		//上限位置
	SV_DAIHAITO2_SRV	/= 10;		//下限位置
	SV_MOKKAN2_SRV		/= 10;		//目標完了範囲

	//モーション上往復データ
	SV_1DANPOS3_SRV		/= 10;		//目標位置1
	SV_2DANPOS3_SRV		/= 10;		//目標位置2
	SV_3DANPOS3_SRV		/= 10;		//目標位置3
	SV_4DANPOS3_SRV		/= 10;		//目標位置4
	SV_5DANPOS3_SRV		/= 10;		//目標位置5
	SV_6DANPOS3_SRV		/= 10;		//目標位置6
	SV_7DANPOS3_SRV		/= 10;		//目標位置7
	SV_8DANPOS3_SRV		/= 10;		//目標位置8
	SV_9DANPOS3_SRV		/= 10;		//目標位置9
	SV_10DANPOS3_SRV	/= 10;		//目標位置10
	SV_TAIKIPOS3_SRV	/= 10;		//上限位置
	SV_DAIHAITO3_SRV	/= 10;		//下限位置
	SV_MOKKAN3_SRV		/= 10;		//目標完了範囲

	//スライド自動調節
	SV_ATUOS0_D9		/= 10;		//スライド自動調節　生産設定
	SV_ATUOS1_D9		/= 10;		//スライド自動調節　段取り１設定
	SV_ATUOS2_D9		/= 10;		//スライド自動調節　段取り２設定

	//スライド自動待機
	SV_INTLIM_POS		/= 10;		//干渉限界位置　位置

	//ダイクッション
	SV_DAIKA1_C27		/= 10;		//ダイクッション調節１
	SV_DAIKA2_C27		/= 10;		//ダイクッション調節２

	//レベラフィーダ	2016/03/24
	SV_LFEED_LNG1		/= 10;		//送り長さ
	SV_LFEED_HOSIN		/= 10;		//矯正量入口
	SV_LFEED_HOSOT		/= 10;		//矯正量出口
	SV_LFEED_STRPOS		/= 10;		//送り位置
	SV_LFEED_ENDPOS		/= 10;		//リリース位置

	SV_KAT_MM_INCH = 1;				//inch通常データ
}

void	SYS_keta_down(void)
{
	//見える化画面
	SV_WAVE_SCL1U		/= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL1D		/= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ｻﾝﾌﾟﾘﾝｸﾞ画面)
	SV_WAVE_SCL3U		/= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ上限(ﾄﾚﾝﾄﾞ画面)
	SV_WAVE_SCL3D		/= 10;		//ｽﾗｲﾄﾞ位置ｽｹｰﾙ下限(ﾄﾚﾝﾄﾞ画面)

	//一定速度領域
	SV0_FIXARA_POSS		/= 10;		//一定領域　開始位置
	SV0_FIXARA_POSE		/= 10;		//一定領域　終了位置

	//トレンド
	SV_TRDCSR_RNAU		/= 10;		//ｽﾗｲﾄﾞ位置上限検出位置
	SV_TRDCSR_RNAD		/= 10;		//ｽﾗｲﾄﾞ位置下限検出位置
}

void	Dat_mm_inch_chg(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;

	seq_chg = seq_bit = SEQ_016_SV;					// new
	seq_chg ^= TANNI_SEQ_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & TANNI_SEQ_LST;				// chg & old = ofe
	TANNI_SEQ_LST = seq_bit;

	if ( seq_chg & (BIT_6+BIT_7) ) {
		if (seq_one & BIT_6) {							//仕様設定No.7  単位切換 inch選択
			KAT_mm_2_inch_all();
			SYS_mm_2_inch_all();
		}
		else if (seq_ofe & BIT_6) {						//仕様設定No.7  単位切換 mm選択
			KAT_inch_2_mm_all();
			SYS_inch_2_mm_all();
		}
		else if (seq_one & BIT_7) {						//仕様設定No.8  単位 高精度選択
			if (seq_bit & BIT_6) {
				//単位inchの時    小数点以下3桁 inch ⇒ 小数点以下4桁 inch
				KAT_keta_up();
				SYS_keta_up();
			}
		}
		else if (seq_ofe & BIT_7) {						//仕様設定No.8  単位 通常選択
			if (seq_bit & BIT_6) {
				//単位inchの時    小数点以下4桁 inch ⇒ 小数点以下3桁 inch
				KAT_keta_down();
				SYS_keta_down();
			}
		}
		mmon_trans_get();							//2017/08/21
		FRAM_KAT_csum_set();						//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
		FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	}
}


/*** END ***/
