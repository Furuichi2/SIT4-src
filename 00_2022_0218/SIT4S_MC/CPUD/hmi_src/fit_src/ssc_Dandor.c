/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			型段取の操作メイン処理													*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-06-21
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
typedef struct {
	UNs	*SADR;			//選択
	UNs	S_ONOFF;		//選択有無ビット
	UNs	*DADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNs	S_BIT1;			//第一選択
	UNs	S_BIT2;			//第二選択
	UNs	S_BIT3;			//第三選択
	UNs	S_IAO;			//内全外選択
	UNs	AKI;			//空き
	} DAN_TBL_TDEF;

typedef struct {
	UNs	*SADR;			//仕様有無ｱﾄﾞﾚｽ
	UNs	S_ONOFF;		//仕様有無判別ﾋﾞｯﾄ
	UNs	*DADR;			//出力領域ｱﾄﾞﾚｽ
	UNs	NSUU;			//ノッチ数
	UNs	N_BIT1;			//ノッチ１ビット
	UNs	N_BIT2;			//ノッチ２ビット
	UNs	N_BIT3;			//ノッチ３ビット
	UNs	N_BIT4;			//ノッチ４ビット
	UNs	N_BIT5;			//ノッチ５ビット
	UNs	S_IAO1;			//内全外選択
	UNs	S_IAO2;			//内全外選択
	UNs	S_IAO3;			//空き
	UNs	S_IAO4;			//空き
	UNs	S_IAO5;			//空き
	} ADC_SW2_TBL_TDEF;


/* プロトタイプ宣言 -------------------------------------------------- */
void	dsp_Dandori(void);						//段取の管理

void	sw56_gamen_07(UNs);						//段取[基本]のSW5･6の処理
void	sw234_gamen_07(UNs);					//段取[基本]のSW2･3･4の処理
void	DANseq_sw56off(UNs);					//段取り用ｼｰｹﾝｽOFF
void	DAN_select_ent(UNs);					//段取り画面選択項目セレクト入力

void	DANseq_alloff(void);					//段取り用シーケンスＯＦＦ
void	DAN_select_diap(void);					//段取画面 選択項目セレクト表示
void	DAN_sel_cara(UNs);						//段取り選択項目キャラクタ表示
void	DAN_SW14_no_set(void);					//段取画面 SW14認識番号転送
void	DAN_dispseq_out(void);					//段取画面 ｶｰｿﾙ位置ｼｰｹﾝｽ出力

void	DAN_csr_ichk(void);						//段取カーソル位置初期化
void	DAN_csr_mng(void);						//段取[基本]の専用　カーソル移動管理

void	SURA_sv_chg(void);						//スライド自動調節ＳＶ変更処理
void	ADC_MAIN_MNG(void);						//自動金型交換ＭＡＩＮ処理
void	ADC_GAMEN_CHG(void);					//自動金型交換ＷＩＮ画面変更処理
void	ADC_WIN_DISP(UNs);						//ＡＤＣ Ｗｉｎｄｏｗ表示
void	ADC_STEP_DISP(void);					//ＡＤＣステップ表示処理
void	ADC_STEP_CARA(UNs *);					//ＡＤＣステップキャラ表示
void	ADC_STEP_ATR(UNs);						//ＡＤＣステップアトリビュート
void	ADC_SW2_SELECT(void);					//自動ＳＷ２選択入力処理
void	ADC_SW2_DISP(void);						//自動ＳＷ２選択表示処理
void	ADC_SW56DN_DISP(void);					/* ＡＤＣＳＷ５６下表示切換		*/
void	ADC_SW5SEQ_OUT(void);					//ＡＤＣ　ＳＷ５シーケンス出力
void	ADC_SW6SEQ_OUT(void);					//ＡＤＣ　ＳＷ６シーケンス出力
void	ADC_NEXT_READ(void);					/* ＡＤＣ次型番号読込処理		*/
void	ADC_GAMEN_END(void);					/* ＡＤＣ画面戻り処理			*/
void	ADC_STEP_SHR(void);						/* ＡＤＣステップモニタデータ検索	*/
void	ADC_NEXTNAME_SET(void);					/* ＡＤＣ次型番号名称 			*/
void	NEXT_READ_AFTER(void);					/* 次期読み込み後の再表示 		*/
void	ADC_GRPH_DISP(void);					//ＡＤＣ専用グラフィック描画
void	ADC_SW56UP_DISP(void);					//ＡＤＣＳＷ５６上段メッセージ表示
void	ADC_STEP_DISP1(void);					//ＡＤＣステップモニタの表示

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
const	DAN_TBL_TDEF	Dan_Sel_Tbl_07[15] = {
		{			/* ０１　自動金型交換		*/
			&SEQ_020_SV,		/* 選択		 */
			BIT_E,				/* 選択有無ビット	 */
			&SEQ_047_SV,		/* データ		 */
			BIT_5,				/* 第一選択		 */
			BIT_6,				/* 第二選択		 */
			BIT_7,				/* 第三選択		 */
			10,					/* 内全外選択		 */
			0xff1f				/* 空き		 */
		},
		{			/* ０２　スライド調節	 */
			&SEQ_020_SV,		/* 選択		 */
			BIT_OFF,			/* 選択有無ビット	 */
			&SEQ_043_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_C,				/* 第三選択		 */
			3,					/* 前全後選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* ０３　上型クランパ選択	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_5,				/* 選択有無ビット	 */
			&SEQ_041_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_3,				/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			1,					/* 内全外選択		 */
			0xffe3				/* 空き		 */
		},
		{			/* ０４　下型クランパ選択	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_7,				/* 選択有無ビット	 */
			&SEQ_041_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_C,				/* 第三選択		 */
			1,					/* 内全外選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* ０５　ダイリフタ選択	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_9,				/* 選択有無ビット	 */
			&SEQ_042_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_3,				/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			1,					/* 内全外選択		 */
			0xffe3				/* 空き		 */
		},
		{			/* ０６　ダイクッション選択	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_B,				/* 選択有無ビット	 */
			&SEQ_042_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_C,				/* 第三選択		 */
			2,					/* 左全右選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* ０７　防護柵選択	 */
			&SEQ_020_SV,		/* 選択		 */
			BIT_2,				/* 選択有無ビット	 */
			&SEQ_043_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_3,				/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			3,					/* 前全後選択		 */
			0xffe3				/* 空き		 */
		},
		{			/* ０８　ＭＢ		 */
			&SEQ_021_SV,		/* 選択		 */
			BIT_0,				/* 選択有無ビット	 */
			&SEQ_043_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_C,				/* 第三選択		 */
			5,					/* 前共後選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* ０９　バランサ		*/
			0,				/* 選択		 */
			0,				/* 選択有無ビット	 */
			0,				/* データ		 */
			0,				/* 第一選択		 */
			0,				/* 第二選択		 */
			0,				/* 第三選択		 */
			0,				/* 内全外選択		 */
			0				/* 空き		 */
		},
		{			/* １０　ダイクッション調節		*/
			&SEQ_019_SV,		/* 選択		 */
			0xb000,				/* 選択有無ビット	 */
			&SEQ_046_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_OFF,			/* 第三選択		 */
			7,					/* 選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* １１　スライド自動調節	 */
			&SEQ_020_SV,		/* 選択		 */
			BIT_6,				/* 選択有無ビット	 */
			&SEQ_044_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_3,				/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			4,					/* 前全後選択		 */
			0xffe3				/* 空き		 */
		},
		{			/* １２　バランサ圧力調節	 */
			&SEQ_020_SV,		/* 選択		 */
			BIT_B,				/* 選択有無ビット	 */
			&SEQ_044_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_OFF,			/* 第三選択		 */
			6,					/* 前全後選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* １３　ストローク調節	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_E,				/* 選択有無ビット	 */
			&SEQ_045_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_OFF,			/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			9,					/* 左全右選択		 */
			0xffe3				/* 空き		 */
		},
		{			/* １４　ダイクッション自動調節	 */
			&SEQ_019_SV,		/* 選択		 */
			BIT_E,				/* 選択有無ビット	 */
			&SEQ_045_SV,		/* データ		 */
			BIT_A,				/* 第一選択		 */
			BIT_B,				/* 第二選択		 */
			BIT_C,				/* 第三選択		 */
			2,					/* 左全右選択		 */
			0xe3ff				/* 空き		 */
		},
		{			/* １５　ダイクッション調圧	 */
			&SEQ_020_SV,		/* 選択		 */
			BIT_0,				/* 選択有無ビット	 */
			&SEQ_046_SV,		/* データ		 */
			BIT_2,				/* 第一選択		 */
			BIT_3,				/* 第二選択		 */
			BIT_4,				/* 第三選択		 */
			2,					/* 左全右選択		 */
			0xffe3				/* 空き		 */
		}
	};

const	UNs		Dan_sel_cara_tbl[11][4] = {
		{ 0, 0, 0, 0},			//00
		{ 24, 25, 26, 0},		//01 内全外
		{ 27, 25, 28, 0},		//02 さ全右
		{ 29, 25, 30, 0},		//03 前全後
		{ 31, 32, 33, 0},		//04 生産・段取１・２
		{ 29, 43, 30, 0},		//05 前共後
		{ 44, 45, 0xff, 0},		//06 設定圧・基準圧
		{ 46, 46, 0xff, 0},		//07 調節・調節
		{ 47, 48, 0xff, 0},		//08 ｽﾄﾛｰｸ・圧力
		{ 27, 0xff, 28, 0},		//09 左  右
		{ 53, 54, 55, 0}		//10 搬入・交換・搬出
	};


const	ADC_SW2_TBL_TDEF	ADC_SW2_TBL[6] = {
		{/******	ダイクッション操作ウインドウ１３	***********/
			&SEQ_019_SV,			/* 仕様有無 */
			BIT_11,					/* 仕様有無判別 */
			&SEQ_042_SV,			/* 出力領域 */
			3,						/* ノッチ数 */
			BIT_10,					/* ノッチ１ビット */
			BIT_11,					/* ノッチ２ビット */
			BIT_12,					/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			27,						/* 左 */
			25,						/* 全 */
			28,						/* 右 */
			0,						/* 予備４ */
			0						/* 予備５ */
		},
		{/******	スライド調節操作ウインドウ１４	***********/
			&SEQ_020_SV,			/* 仕様有無 */
			BIT_4,					/* 仕様有無判別 */
			&SEQ_053_SV,			/* 出力領域 */
			0,						/* ノッチ数 */
			BIT_OFF,				/* ノッチ１ビット */
			BIT_OFF,				/* ノッチ２ビット */
			BIT_OFF,				/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			0,						/* 左 */
			0,						/* 全 */
			0,						/* 右 */
			0,						/* 予備４ */
			0						/* 予備５ */
		},
		{/******	スライド自動調節確認ウインドウ１５	***********/
			&SEQ_020_SV,			/* 仕様有無 */
			BIT_6,					/* 仕様有無判別 */
			&SEQ_044_SV,			/* 出力領域 */
			3,						/* ノッチ数 */
			BIT_2,					/* ノッチ１ビット */
			BIT_3,					/* ノッチ２ビット */
			BIT_4,					/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			31,						/* 生産 */
			32,						/* 段取１ */
			33,						/* 段取２ */
			0,						/* 予備４ */
			0						/* 予備５ */
		},
		{/******	ダイクッション操作ウインドウ１６	***********/
			&SEQ_019_SV,			/* 仕様有無 */
			BIT_14,					/* 仕様有無判別 */
			&SEQ_045_SV,			/* 出力領域 */
			2,						/* ノッチ数 */
			BIT_2,					/* ノッチ１ビット */
			BIT_4,					/* ノッチ２ビット */
			0,						/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			27,						/* 左 */
			28,						/* 右 */
			0,						/* 予備３ */
			0,						/* 予備４ */
			0						/* 予備５ */
		},
		{/******	ダイクッション自動調節確認ウインドウ１７	***********/
			&SEQ_019_SV,			/* 仕様有無 */
			BIT_14,					/* 仕様有無判別 */
			&SEQ_045_SV,			/* 出力領域 */
			3,						/* ノッチ数 */
			BIT_10,					/* ノッチ１ビット */
			BIT_11,					/* ノッチ２ビット */
			BIT_12,					/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			27,						/* 左 */
			25,						/* 全 */
			28,						/* 右 */
			0,						/* 予備４ */
			0						/* 予備５ */
		},
		{/******	ＭＢ操作ウインドウ１８	***********/
			&SEQ_021_SV,			/* 仕様有無 */
			BIT_0,					/* 仕様有無判別 */
			&SEQ_043_SV,			/* 出力領域 */
			2,						/* ノッチ数 */
			BIT_10,					/* ノッチ１ビット */
			BIT_12,					/* ノッチ２ビット */
			0,						/* ノッチ３ビット */
			0,						/* ノッチ４ビット */
			0,						/* ノッチ５ビット */
			29,						/* 前 */
			30,						/* 後 */
			0,						/* 予備３ */
			0,						/* 予備４ */
			0						/* 予備５ */
		}
	};

extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs	SPACE_ASCII_40[40];


/*
********************************************************************************
*  Module Name:		dsp_Dandori
*  Function Name:	段取の管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-21
********************************************************************************
*/
void	dsp_Dandori(void)
{

	switch(disp_stg_sel) {

		case E_kstg_init:		//段取[基本]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(なし)
					Key_Ent_sv();								//設定値の確定		//V06p
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ　開閉完了ﾌﾗｸﾞｸﾘｱ
							DANseq_alloff();					//段取り用シーケンスＯＦＦ

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = 0;
							WINDOW_NO_BACK = 0;

							disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
							WINDOW_NO = 10;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw2:			//key code SW2(なし)
						case E_key_sw3:			//key code SW3(なし)
						case E_key_sw4:			//key code SW4(なし)
							KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ				/* V01j */
							DAN_select_ent(KEY_DATA_CODE);		//段取り画面選択項目セレクト入力	/* V01j */
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示			/* V01j */
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示			/* V01j */
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示			/* V01j */
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示			/* V01j */
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_gamen_07(KEY_DATA_CODE);				//段取[基本]のSW5･6の処理
					break;
			}
			break;

		case E_kstg_gaid:		//段取[ガイダンス表示]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode（なし）
				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							DAN_DAN_FLG = 0xff;
							disp_stg_sel = E_kstg_init;			//段取[基本]へ
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();						//画面表示

							DAN_DAN_FLG = 0x00;
							break;
						case E_key_sw2:			//key code SW2（なし）
						case E_key_sw4:			//key code SW4（なし）
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_kstg_schk;			//段取[シーケンスチェック]へ
							WINDOW_NO = 11;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
					}
					break;
			}
			break;

		case E_kstg_schk:		//段取[シーケンスチェック]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;
				case E_key_sw56_mode:		//SW5/6 key mode（なし）
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							DAN_DAN_FLG = 0xff;
							disp_stg_sel = E_kstg_init;			//段取[基本]へ
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();						//画面表示

							DAN_DAN_FLG = 0x00;
							break;
						case E_key_sw2:			//key code SW2（なし）
						case E_key_sw3:			//key code SW3（なし）
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
							WINDOW_NO = 10;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;
					}
					break;
			}
			break;

		case E_kstg_scon:		//段取[スライド調節]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定

					SURA_CHG_LST = 0;
					SURA_sv_chg();								//スライド自動調節ＳＶ変更処理
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ　開閉完了ﾌﾗｸﾞｸﾘｱ
							DANseq_alloff();					//段取り用シーケンスＯＦＦ

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
							SWCHG_DISP_ON_FLG = 0;

//2014/09/09
////							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
////							WINDOW_NO_BACK = WINDOW_NO;
////
////							disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
////							WINDOW_NO = 10;
////							WIN_gamen_disp();					//ウインドウ画面表示

							disp_stg_sel = E_kstg_init;					//段取[基本]へ
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();								//画面表示

							CSR_FLG = 5;								//カーソル表示位置指定
							CSR_FLG_CNT = CSR_FLG_CNT_LST;				//カーソル番号セット
							SV_FLG_CNT = 1;								//設定値番号セット
							SW_FLG_CNT = 1;								//ＳＷ番号セット
							CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//カーソル移動(戻り値指定,移動)

							autokana_sw56_bak = 0;						//

							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//段取り画面選択項目セレクト入力
							KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							if( CSR_FLG_CNT == 2 ){					//カーソルが自動スタートの位置の時だけスタートする
								AUTO_sura_start();					//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ
							}
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();					//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_kstg_bara:	/* V01j */	//段取[バランサ調圧]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ　開閉完了ﾌﾗｸﾞｸﾘｱ
							DANseq_alloff();					//段取り用シーケンスＯＦＦ

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
							WINDOW_NO_BACK = WINDOW_NO;

							disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
							WINDOW_NO = 10;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//段取り画面選択項目セレクト入力
							KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();					//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_kstg_daic:	/* V01j */	//段取[ダイクッション調節]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ　開閉完了ﾌﾗｸﾞｸﾘｱ
							DANseq_alloff();					//段取り用シーケンスＯＦＦ

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
							WINDOW_NO_BACK = WINDOW_NO;

							disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
							WINDOW_NO = 10;
							WIN_gamen_disp();					//ウインドウ画面表示
							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//段取り画面選択項目セレクト入力
							KAT_DATCHG_FLG = 0xff;				//カウンタ値変更フラグ
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();					//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							break;
					}
					break;
			}
			break;

		case E_kstg_kana:	/* V01j*/	//段取[自動金型交換]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//設定値の確定
					break;

				case E_key_sw14_mode:		//SW1～4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					if (KEY_DATA_CODE == E_key_sw1)
					{
						SEQ_PAR_108 = 0;					//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ　開閉完了ﾌﾗｸﾞｸﾘｱ
						DANseq_alloff();					//段取り用シーケンスＯＦＦ

						SWCHG_DISP_ON_FLG = 0x0FF;
						SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
						SWCHG_DISP_ON_FLG = 0;

						CSR_FLG_CNT_BACK = CSR_FLG_CNT;
						WINDOW_NO_BACK = WINDOW_NO;

						disp_stg_sel = E_kstg_gaid;			//段取[ガイダンス表示]へ
						WINDOW_NO = 10;
						WIN_gamen_disp();					//ウインドウ画面表示

						autokana_sw56_bak = 0;				// V01j(INS)
					}
					switch(WINDOW_NO) {
						case 12:		//ＡＤＣステップモニタ
							switch(KEY_DATA_CODE) {
								case E_key_sw2:			//key code SW2
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
								default:
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
							}
							break;
						case 13:		//ＡＤＣダイクッション
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN13_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(立下り)
									SW16data_onset(0, 3);
									SEQ_PAR_042 &= ~BIT_8;			// 下降 SEQ OFF !
									goto	WIN13_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(立下り)
									SW16data_onset(0, 4);
									SEQ_PAR_042 &= ~BIT_9;			// 上昇 SEQ OFF !
									goto	WIN13_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN13_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_042 |= BIT_8;			// 下降 SEQ ON !
									SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN13_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_042 |= BIT_9;			// 上昇 SEQ ON !
									SW16data_onset(0xff, 4);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN13_SW24_EXIT;
WIN13_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 14:		//ＡＤＣスライド調節
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN14_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(立下り)
									SW16data_onset(0, 3);
									SEQ_PAR_044 &= ~BIT_0;			// 下降 SEQ OFF !
									goto	WIN14_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(立下り)
									SW16data_onset(0, 4);
									SEQ_PAR_044 &= ~BIT_1;			// 上昇 SEQ OFF !
									goto	WIN14_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN14_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_044 |= BIT_0;			// 下降 SEQ ON !
									SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN14_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_044 |= BIT_1;			// 上昇 SEQ ON !
									SW16data_onset(0xff, 4);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN14_SW24_EXIT;
WIN14_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 15:		//ＡＤＣスライド自動調節
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN15_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN15_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN15_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 16:		//ＡＤＣダイクッション調節
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN16_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(立下り)
									SW16data_onset(0, 3);
									SEQ_PAR_045 &= ~BIT_0;			// 下降 SEQ OFF !
									goto	WIN16_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(立下り)
									SW16data_onset(0, 4);
									SEQ_PAR_045 &= BIT_1;			// 上昇 SEQ OFF !
									goto	WIN16_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN16_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_045 |= BIT_0;			// 下降 SEQ ON !
									SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN16_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_045 |= BIT_1;			// 上昇 SEQ ON 1
									SW16data_onset(0xff, 4);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
									ADC_SW34_FLG = 0xff;
									goto	WIN16_SW24_EXIT;
WIN16_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 17:		//ＡＤＣダイクッション自動調節
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN17_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN17_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN17_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 18:		//ＭＢ選択
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(立下り)
									SW16data_onset(0, 2);
									goto	WIN18_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* 自動ＳＷ２選択入力処理		*/
									KAT_DATCHG_FLG = 0xFF;		/* カウンタ値変更フラグ */
									goto	WIN18_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN18_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}
					switch(KEY_DATA_CODE) {
						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
							SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							ADC_SW5_ON_FLG = 0xff;					//2016/04/22
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
							SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							ADC_SW6_ON_FLG = 0xff;					//2016/04/22
							break;

						case E_key_sw5_down:	//key code SW5(立下り)
						case E_key_sw6_down:	//key code SW6(立下り)
							DANseq_alloff();					//段取り用シーケンスＯＦＦ
							SW16data_onset(0x00, 7);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							SW16data_onset(0x00, 8);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
							ADC_SW5_ON_FLG = 0;					//2016/04/22
							ADC_SW6_ON_FLG = 0;					//2016/04/22
							break;
					}
			}
	}
}


/*
********************************************************************************
*  Module Name:		sw56_gamen_07
*  Function Name:	段取[基本]のSW5･6の処理
*  Input	:		ｷｰｺｰﾄﾞ(SW5/6)
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-27
********************************************************************************
*/
void	sw56_gamen_07(UNs k_code)
{
	UNs		i, seq_bit;

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//立下り?
		DANseq_sw56off(k_code);						//段取り用ｼｰｹﾝｽOFF
		return;
	}

	if ( SW14_ON6_FLG == 1 ) {						//自動金型交換			/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//カーソル番号セット
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//反転アドレスデータ待避

			disp_stg_sel = E_kstg_kana;				//段取[自動金型交換]へ
			seq_bit = SEQ_PAR_115 & 0x007f;
			ADC_WIN_DISP(seq_bit);					/* ＡＤＣウインドウ画面表示 		*/

			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理
		}
	}

	else if( SW14_ON6_FLG == 2 ) {						//スライド自動調節
		i = (SEQ_020_SV & 0x0070);
		if( i == BIT_4 ){							//スライド調節のみ選択中
			goto	SW56_G07_310;
		}
		else if(k_code == E_key_sw6){				//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//カーソル番号セット
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//反転アドレスデータ待避
//			DAN_WIN_FLG = 0xff;

			disp_stg_sel = E_kstg_scon;				//段取[スライド調節]へ
			WINDOW_NO = 6;
			WIN_gamen_disp();						//ウインドウ画面表示

//			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理
		}
	}

	else if( SW14_ON6_FLG <= /*5 V01j*/ 8 ) {		//上型ｸﾗﾝﾊﾟ･下型ｸﾗﾝﾊﾟ･ﾀﾞｲﾘﾌﾀ  +  ﾀﾞｲｸｯｼｮﾝ･防護柵･ＭＢ
SW56_G07_310:
		if(k_code == E_key_sw5){					//SW5?
			SEI_test_out_sw5();						//生産設定ﾃｽﾄ出力処理(SW5)
		}
		else{
			SEI_test_out_sw6();						//生産設定ﾃｽﾄ出力処理(SW6)
		}
		SW16data_onset(0xff, k_code+2 );						//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示
	}

	else if ( SW14_ON6_FLG == 9 ) {					//ﾊﾞﾗﾝｻ調圧				/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//カーソル番号セット
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//反転アドレスデータ待避

			disp_stg_sel = E_kstg_bara;				//段取[バランサ調圧]へ
			WINDOW_NO = 7;
			WIN_gamen_disp();						//ウインドウ画面表示

			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理
		}
	}

	else if ( SW14_ON6_FLG == 10 ) {				//ﾀﾞｲｸｯｼｮﾝ調節			/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//カーソル番号セット
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//反転アドレスデータ待避

			disp_stg_sel = E_kstg_daic;				//段取[ダイクッション調節]へ
			if (SEQ_PAR_046 & BIT_11)	WINDOW_NO = 9;
			else						WINDOW_NO = 8;
			WIN_gamen_disp();						//ウインドウ画面表示

			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理
		}
	}

}


/*
********************************************************************************
*  Module Name:		DANseq_sw56off
*  Function Name:	段取り用ｼｰｹﾝｽOFF
*  Input	:		ｷｰｺｰﾄﾞ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-14
********************************************************************************
*/
void	DANseq_sw56off(UNs k_code)
{

	if(k_code == E_key_sw5_down){	//key code SW5(立下り)

		SEQ_PAR_035 = 0;				//ｴｼﾞｪｸﾀ1～6 ﾃｽﾄ(1:ﾃｽﾄ中)
		SEQ_PAR_041 &= 0xfefe;			//上型ｸﾗﾝﾊﾟ，下型ｸﾗﾝﾊﾟ　閉SW(1:SW ON)
		SEQ_PAR_042 &= 0xfefe;			//ﾀﾞｲﾘﾌﾀ，ﾀﾞｲｸｯｼｮﾝ　下降SW(1:SW ON)
		SEQ_PAR_043 &= 0xfefe;			//防護柵　下降SW，ＭＢ　入SW　(1:SW ON)
		SEQ_PAR_044 &= 0xbfbe;			//ｽﾗｲﾄﾞ調節，ﾊﾞﾗﾝｻ調圧
		SEQ_PAR_045 &= 0xbffe;			//ﾀﾞｲｸｯｼｮﾝ調節
		SEQ_PAR_046 &= 0xffbf;			//ﾀﾞｲｸｯｼｮﾝ調節
		SEQ_PAR_047 &= 0xfffc;			//ADC SW(1:SW ON)

		SW16data_onset(0x00, 7);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
	}
	else if(k_code == E_key_sw6_down){	//key code SW6(立下り)

		SEQ_PAR_035 = 0;				//ｴｼﾞｪｸﾀ1～6 ﾃｽﾄ(1:ﾃｽﾄ中)
		SEQ_PAR_041 &= 0xfdfd;			//上型ｸﾗﾝﾊﾟ，下型ｸﾗﾝﾊﾟ　開SW(1:SW ON)
		SEQ_PAR_042 &= 0xfdfd;			//ﾀﾞｲﾘﾌﾀ，ﾀﾞｲｸｯｼｮﾝ　上昇SW(1:SW ON)
		SEQ_PAR_043 &= 0xfdfd;			//防護柵　上昇SW，ＭＢ　出SW　(1:SW ON)
		SEQ_PAR_044 &= 0xbfbd;			//ｽﾗｲﾄﾞ調節，ﾊﾞﾗﾝｻ調圧
		SEQ_PAR_045 &= 0xbffd;			//ﾀﾞｲｸｯｼｮﾝ調節
		SEQ_PAR_046 &= 0xffbf;			//ﾀﾞｲｸｯｼｮﾝ調節
		SEQ_PAR_047 &= 0xffe3;			//ADC SW(1:SW ON)

		SW16data_onset(0x00, 8);							//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示
	}
}


/*
********************************************************************************
*  Module Name:		DAN_select_ent
*  Function Name:	段取り画面選択項目セレクト入力
*  Input	:		入力ｷｰｺｰﾄﾞ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	DAN_select_ent(UNs k_code)
{
	UNs		bit_d, s_no, *adr_p;

	if(SW14_ON6_FLG == 00 || SW14_ON6_FLG >= 16){
		return;
	}

	if(SW14_ON6_FLG == 10)		/* ダイクッション調節 */		/* V01q (ins) */
	{
		if(k_code == E_key_sw2) {					//key code SW2
			if (SEQ_019_SV & BIT_13) {				// ｽﾄﾛｰｸ調節選択項目有？
				SEQ_046_SV &= ~(BIT_10+BIT_11);
				SEQ_046_SV |= BIT_10;

				SVSW_CHG_FLG |= 0x000c;					//データチェンジフラグセット
				DAN_select_diap();						//段取画面 選択項目セレクト表示
				Under_grph();							//下段のグラフィックセット

				FRAM_csum_set();						//FeRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成	V06i(INS)
			}
		}
		else if(k_code == E_key_sw3) {				//key code SW2
			if (SEQ_019_SV & BIT_15) {				// 圧力調節選択項目有？
				SEQ_046_SV &= ~(BIT_10+BIT_11);
				SEQ_046_SV |= BIT_11;

				SVSW_CHG_FLG |= 0x000c;					//データチェンジフラグセット
				DAN_select_diap();						//段取画面 選択項目セレクト表示
				Under_grph();							//下段のグラフィックセット
			}

				FRAM_csum_set();						//FeRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成	V06i(INS)
		}
	}
	else
	{
		s_no = (SW14_ON6_FLG - 1);
		adr_p = Dan_Sel_Tbl_07[s_no].SADR;				//選択
		bit_d = Dan_Sel_Tbl_07[s_no].S_ONOFF;			//選択有無ビット
		if(*adr_p & bit_d){								//選択項目無し?
			if(k_code == E_key_sw2) {					//key code SW2
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT1;	//第一選択
			}
			else if(k_code == E_key_sw3){				//key code SW3
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT2;	//第二選択
			}
			else{										//key code SW4
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT3;	//第三選択
			}

			if(bit_d != 00){
				adr_p = Dan_Sel_Tbl_07[s_no].DADR;		//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*adr_p &= Dan_Sel_Tbl_07[s_no].AKI;		//選択データ初期化
				*adr_p |= bit_d;

//2014-08-08koma 試し				SVSW_CHG_FLG |= 0x000c;					//データチェンジフラグセット
				SVSW_CHG_FLG |= 0x0008;					//データチェンジフラグセット 2014-08-08koma 試し
				DAN_select_diap();						//段取画面 選択項目セレクト表示
				Under_grph();							//下段のグラフィックセット

				FRAM_csum_set();						//FeRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成	V06i(INS)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DANseq_alloff
*  Function Name:	段取り用シーケンスＯＦＦ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	DANseq_alloff(void)
{
	SEQ_PAR_035 = 0;				//ｴｼﾞｪｸﾀ1～6 ﾃｽﾄ(1:ﾃｽﾄ中)
	SEQ_PAR_041 &= 0xfcfc;			//上型ｸﾗﾝﾊﾟ，下型ｸﾗﾝﾊﾟ　閉開SW(1:SW ON)
	SEQ_PAR_042 &= 0xfcfc;			//ﾀﾞｲﾘﾌﾀ，ﾀﾞｲｸｯｼｮﾝ　下降 上昇SW(1:SW ON)
	SEQ_PAR_043 &= 0xfcfc;			//防護柵　下降 上昇SW，ＭＢ　入 出SW　(1:SW ON)
	SEQ_PAR_044 &= 0xbfbc;			//ｽﾗｲﾄﾞ調節，ﾊﾞﾗﾝｻ調圧
	SEQ_PAR_045 &= 0xbffc;			//ﾀﾞｲｸｯｼｮﾝ調節
	SEQ_PAR_046 &= 0xffbf;			//ﾀﾞｲｸｯｼｮﾝ調節
	SEQ_PAR_047 &= 0xffe0;			//ADC SW(1:SW ON)
}


/*
********************************************************************************
*  Module Name:		DAN_select_diap
*  Function Name:	段取画面 選択項目セレクト表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	DAN_select_diap(void)
{
	UNs		*sel_p, *dt_p, i;
	UNs		sel_bit, bit_s1, bit_s2, bit_s3, sel_us, aki_d;


//V01r	if( GAMEN_NO != 7 )						//中型段取画面
	if( GAMEN_NO != 7 && GAMEN_NO != 8 )		//中型段取画面
//			GAMEN_NO != 18 )					//中型データ設定選択画面
	{
		return;
	}
//	if((WINDOW_NO != 0 && WINDOW_NO < 6) || WINDOW_NO >= 10) {
//		return;
//	}
//V01j	if( WINDOW_NO != 6 ) {
//V01j		return;
//V01j	}
	if((WINDOW_NO != 0 && WINDOW_NO < 6) || WINDOW_NO >= 10) {
		return;
	}

	SW56_dncara_disp(0xff, 2);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2上)
	SW56_dncara_disp(0xff, 3);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3上)
	SW56_dncara_disp(0xff, 4);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW4上)

	SW56_dncara_disp(0xff, 10);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
	SW56_dncara_disp(0xff, 11);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3下)
	SW56_dncara_disp(0xff, 12);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW4下)

	SW16data_onset(0x00, 2);					//SW1～6の反転指定を行う
	SW16data_onset(0x00, 3);					//SW1～6の反転指定を行う
	SW16data_onset(0x00, 4);					//SW1～6の反転指定を行う

	if(SW14_ON6_FLG == 00 || SW14_ON6_FLG >= 16){
		return;
	}

	i = SW14_ON6_FLG - 1;

	sel_p = Dan_Sel_Tbl_07[i].SADR;				//選択
	sel_bit = Dan_Sel_Tbl_07[i].S_ONOFF;		//選択有無ビット
	dt_p = Dan_Sel_Tbl_07[i].DADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	bit_s1 = Dan_Sel_Tbl_07[i].S_BIT1;			//第一選択
	bit_s2 = Dan_Sel_Tbl_07[i].S_BIT2;			//第二選択
	bit_s3 = Dan_Sel_Tbl_07[i].S_BIT3;			//第三選択
	sel_us = Dan_Sel_Tbl_07[i].S_IAO;			//内全外選択
	aki_d = Dan_Sel_Tbl_07[i].AKI;				//空き

	if(*sel_p & sel_bit) {						//選択有無判別
		DAN_sel_cara(sel_us);					//段取り選択項目キャラクタ表示

		if(*dt_p & bit_s1) {					//第一選択
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 2);			//SW1～6の反転指定を行う
////#else
////			i = Dan_sel_cara_tbl[sel_us][0];
////			SW56_dncara_disp_color(i, 10, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
////#endif
			SW16data_onset(0xff, 2);			//SW1～6の反転指定を行う
			SW16data_onset(0x00, 3);			//SW1～6の反転指定を行う
			SW16data_onset(0x00, 4);			//SW1～6の反転指定を行う
		}

		else if(*dt_p & bit_s2){				//第二選択
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 3);			//SW1～6の反転指定を行う
////#else
////			i = Dan_sel_cara_tbl[sel_us][1];
////			SW56_dncara_disp_color(i, 11, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
////#endif
			SW16data_onset(0x00, 2);			//SW1～6の反転指定を行う
			SW16data_onset(0xff, 3);			//SW1～6の反転指定を行う
			SW16data_onset(0x00, 4);			//SW1～6の反転指定を行う
		}
		else if(*dt_p & bit_s3){				//第三選択
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 4);			//SW1～6の反転指定を行う
////#else
////			i = Dan_sel_cara_tbl[sel_us][2];
////			SW56_dncara_disp_color(i, 12, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
////#endif
			SW16data_onset(0x00, 2);			//SW1～6の反転指定を行う
			SW16data_onset(0x00, 3);			//SW1～6の反転指定を行う
			SW16data_onset(0xff, 4);			//SW1～6の反転指定を行う
		}
		else{									//選択項目無し
			return;
		}

		if(SW14_ON6_FLG == 10){					//ﾀﾞｲｸｯｼｮﾝ調節のSW2,3 消去処理
			if(00 == (SEQ_019_SV & (/*BIT_12 | V01q*/ BIT_13))){
				SW56_dncara_disp(0xff, 2);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2上)
				SW56_dncara_disp(0xff, 10);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
			}
			if(00 == (SEQ_019_SV & BIT_15)){
				SW56_dncara_disp(0xff, 3);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3上)
				SW56_dncara_disp(0xff, 11);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3下)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_sel_cara
*  Function Name:	段取り選択項目キャラクタ表示
*  Input	:		選択項目
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	DAN_sel_cara(UNs c_no)
{
	UNs		i;

	if(c_no == 7){							//特別に７の時は上段もキャラクタを書く
		i = Dan_sel_cara_tbl[8][0];
		SW56_dncara_disp(i, 2);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2上)

		i = Dan_sel_cara_tbl[8][1];
		SW56_dncara_disp(i, 3);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3上)

		i = Dan_sel_cara_tbl[8][2];
		SW56_dncara_disp(i, 4);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW4上)
	}

	i = Dan_sel_cara_tbl[c_no][0];
	SW56_dncara_disp(i, 10);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)

	i = Dan_sel_cara_tbl[c_no][1];
	SW56_dncara_disp(i, 11);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW3下)

	i = Dan_sel_cara_tbl[c_no][2];
	SW56_dncara_disp(i, 12);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW4下)
}


/*
********************************************************************************
*  Module Name:		DAN_SW14_no_set(旧:SW14_no_set)
*  Function Name:	段取画面 SW14認識番号転送
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-28
********************************************************************************
*/
void	DAN_SW14_no_set(void)
{
//V01r	if( (GAMEN_NO == 7 && SW14_ON6_FLG == 0) ||				//０の時は必ずセットする
//V01r			(GAMEN_NO == 18) )							//段取り選択画面は必ずセットする
	if( ((GAMEN_NO == 7 || GAMEN_NO == 8) && SW14_ON6_FLG == 0) ||				//０の時は必ずセットする
			(GAMEN_NO == 18) )							//段取り選択画面は必ずセットする
	{
		SW14_ON6_FLG = CSR_buff[CSR_TBL_POS_NOW].YOBI2;		//予備２
	}
//V01r	if( DAN_DAN_FLG != 0xff &&								//ウインドウ画面から戻るときはセットしない
//V01r		GGAMEN_DISP_FLG != 0xff &&							//画面表示制御中フラグＯＮ
//V01r		WINDOW_NO != 11 && GAMEN_NO == 7 )					//高機能段取り画面でシーケンスチェックを出した後にカーソル位置が初期化されてしまう
	if( DAN_DAN_FLG != 0xff &&								//ウインドウ画面から戻るときはセットしない
		GGAMEN_DISP_FLG != 0xff &&							//画面表示制御中フラグＯＮ
		WINDOW_NO != 11 && (GAMEN_NO == 7 || GAMEN_NO == 8) )					//高機能段取り画面でシーケンスチェックを出した後にカーソル位置が初期化されてしまう
	{
		SW14_ON6_FLG = CSR_buff[CSR_TBL_POS_NOW].YOBI2;		//予備２
	}

	if(DAN_KEY_FLG == 0xff) {
		if(SW14_ON6_FLG == 11) {							//スライド自動
			SW14_ON6_FLG = 2;
		}
		else if(SW14_ON6_FLG == 12) {						//バランサ圧
			SW14_ON6_FLG = 9;
		}
		else if(SW14_ON6_FLG >= 13 && SW14_ON6_FLG < 16) {	//ﾀﾞｲｸｯｼｮﾝ調節
			SW14_ON6_FLG = 10;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_dispseq_out
*  Function Name:	段取画面ｶｰｿﾙ位置ｼｰｹﾝｽ出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-28
********************************************************************************
*/
void	DAN_dispseq_out(void)
{
	UNs		i, bitp1, bitp2;

//V01r	if( GAMEN_NO != 7 || WINDOW_NO >= 10 || CSR_CNT == 0 )
	if( (GAMEN_NO != 7 && GAMEN_NO != 8) || WINDOW_NO >= 10 || CSR_CNT == 0 )
	{
		return;
	}

	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;
	bitp1 = bitp2 = 0;

	if(i == 27){									//上型クランパ
		bitp1 = BIT_0;
	}
	else if(i == 28){								//下型クランパ
		bitp1 = BIT_1;
	}
	else if(i == 29){								//ダイリフタ
		bitp1 = BIT_2;
	}
	else if(i == 46){								//ダイクッション
		bitp1 = BIT_3;
	}
	else if(i == 47){								//防護柵
		bitp1 = BIT_4;
	}
	else if(i == 48){								//スライド自動調節
		bitp2 = BIT_5;
	}
	else if(i == 58){								//スライド調節
		bitp1 = BIT_6;
	}
	else if(i == 89){								//ＭＢ
		bitp1 = BIT_5;
	}
	else if(i == 84){								//バランサ
		bitp1 = BIT_7;
	}
	else if(i == 85){								//ﾀﾞｲｸｯｼｮﾝ調節
		bitp2 = BIT_0;
	}
	else if(i == 86){								//ストローク調節
		bitp2 = BIT_1;
	}
	else if(i == 59){								//ストローク自動調節
		bitp2 = BIT_2;
	}
	else if(i == 87){								//圧力調節
		bitp2 = BIT_3;
	}
	else if(i == 88){								//自動金型交換
		bitp2 = BIT_6;
	}

	SEQ_PAR_052 = bitp1;
	SEQ_PAR_054 = bitp2;

}


/*
********************************************************************************
*  Module Name:		DAN_csr_ichk(旧:SEIDAN_CSR_BACK)
*  Function Name:	段取カーソル位置初期化
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_ichk(void)
{
	UNs		bf, bf1, bf2, bf3;

	bf = SEQ_019_SV;
	bf &= (BIT_4 | BIT_6 | BIT_8);
	bf2 = SEI_ON6_LST1;
	SEI_ON6_LST1 = bf;
	bf3 = bf;
	bf ^= bf2;

	bf1 = SEQ_020_SV;
	bf1 &= (BIT_4 | BIT_6);
	bf2 = SEI_ON6_LST2;
	SEI_ON6_LST2 = bf1;
	bf3 |= bf1;
	bf1 ^= bf2;
	bf |= bf1;

	if(bf != 0){
		SW14_ON6_FLG = 0;				//段取画面カーソルモード初期化

		DAN_GAMEN_NON = 0;
		if( bf3 == 0){
			DAN_GAMEN_NON = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_csr_mng
*  Function Name:	段取[基本]の専用　カーソル移動管理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_mng(void)
{
	UNs		i;

//V01r	if(GAMEN_NO != 7)
	if(GAMEN_NO != 7 && GAMEN_NO != 8)
	{						//段取[基本]？
		return;
	}

	if(WINDOW_NO == 00 ){
		if(DAN_CLS_CNT <= 1 ){				//表示個数１個	?
			return;
		}

		if(CSR_FLG == E_key_up){						//key code ↑ ?
			if(CSR_FLG_CNT == CSR_G07_NO1){				//カーソル先頭位置と同じ？
				CSR_FLG = 5;							//カーソル表示位置指定
				CSR_FLG_CNT = CSR_G07_NO2;				//カーソル最後位置
			}
		}
		else if(CSR_FLG == E_key_down){					//key code ↓ ?
			if(CSR_FLG_CNT == CSR_G07_NO2){				//カーソル最後位置と同じ？
				CSR_FLG = 5;							//カーソル表示位置指定
				CSR_FLG_CNT = CSR_G07_NO1;				//カーソル先頭位置
			}
		}

		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//カーソル移動(戻り値指定,移動)

		i = (SEQ_020_SV & 0x0070);						//ウインドウを出す条件
		if (GAMEN_NO == 7)				// V01r
		{
			if( (CSR_FLG_CNT == 1) && (i & 0x0060) ) {		//スライド調節
				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW5下)ｽﾍﾟｰｽ
				SW56_dncara_disp(16, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW6下) 開く
				Under_grph();								//下段のグラフィックセット
			}
		}
		else
		{
			if( (CSR_FLG_CNT == /*1 V01j*/2) && (i & 0x0060) ) {		//スライド調節
				SW56_dncara_disp(0xff, 7);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW5下)ｽﾍﾟｰｽ
				SW56_dncara_disp(16, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW6下) 開く
				Under_grph();								//下段のグラフィックセット
			}
		}
	}
//DAN_CSR_900:
	else{									//ｳｨﾝﾄﾞｳ用
		if( CSR_FLG_CNT == 1 &&								//ウインドウの最上部にカーソル有り？
			CSR_FLG == E_key_up &&							//key code ↑ ?
			SV_FLG_CNT == 1 &&								//設定値の先頭？
			WINDOW_NO != 11 ) {								//ｼｰｹﾝｽﾁｪｯｸ画面？
			goto	DAN_CSR_970;
		}
//DAN_CSR_950:
		if( SW14_ON6_FLG == 11 ) {							//スライド自動調節でスライド調節が無いとき
			if( SEQ_020_SV & BIT_4 ||
				CSR_FLG != E_key_up ){							//上移動？
				goto	DAN_CSR_960;
			}
			else if(SV_FLG_CNT == 1){							//設定値の先頭？
				goto	DAN_CSR_970;
			}
			else {
				goto	DAN_CSR_960;
			}
		}
//DAN_CSR_955:
		else if(SW14_ON6_FLG == 14){						//ストローク自動調節でストロークが無いとき
			if( SEQ_019_SV & BIT_12 ||
				CSR_FLG != E_key_up ){							//上移動？
				goto	DAN_CSR_960;
			}
			else if(SV_FLG_CNT == 1){							//設定値の先頭？
				goto	DAN_CSR_970;
			}
			else {
				goto	DAN_CSR_960;
			}
		}
DAN_CSR_960:
		if( CSR_FLG != E_key_up){ 							//key code ↑ ?
//DAN_CSR_962:
			if(CSR_FLG == E_key_down){						//key code ↓
				if(SV_FLG_CNT < CSR_buff[CSR_TBL_POS_NOW].SV_MAX){
					CSR_FLG = E_key_right;					//key code →
				}
			}
		}
		else if( SV_FLG_CNT != 1 ){
			CSR_FLG = E_key_left;							//key code ←
		}
//DAN_CSR_968:
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//カーソル移動(戻り値指定,移動)
		goto	DAN_CSR_END;

DAN_CSR_970:
//		if(ADC_DISP_FLG != 0xff){						//ＡＤＣ表示中はこの操作で戻らない
			disp_stg_sel = E_kstg_init;					//段取[基本]へ
			GAMEN_NO = 7;
			if (SEQ_016_SV & BIT_10) {	// V01r
				GAMEN_NO = 8;
			}
			GAMEN_disp();								//画面表示
//			SW14_DISP7_NON = 0;

			CSR_FLG = 5;								//カーソル表示位置指定
			CSR_FLG_CNT = CSR_FLG_CNT_LST;				//カーソル番号セット
			SV_FLG_CNT = 1;								//設定値番号セット
			SW_FLG_CNT = 1;								//ＳＷ番号セット
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//カーソル移動(戻り値指定,移動)

			i = (SEQ_020_SV & 0x0070);					//ウインドウを出す条件
			if (GAMEN_NO == 7)				// V01r
			{
				if( (CSR_FLG_CNT == 1) && (i & 0x0060) ) {	//スライド調節
					SW56_dncara_disp(0xff, 7);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW5下)ｽﾍﾟｰｽ
					SW56_dncara_disp(16, 8);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW6下) 開く
					Under_grph();							//下段のグラフィックセット
				}
			}
			else
			{
				if( (CSR_FLG_CNT == /*1 V01j*/2) && (i & 0x0060) ) {	//スライド調節
					SW56_dncara_disp(0xff, 7);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW5下)ｽﾍﾟｰｽ
					SW56_dncara_disp(16, 8);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW6下) 開く
					Under_grph();							//下段のグラフィックセット
				}
			}
			autokana_sw56_bak = 0;						// V01j(INS)
//		}
	}
DAN_CSR_END:
	return;
}


/*
********************************************************************************
*  Module Name:		SURA_sv_chg
*  Function Name:	スライド自動調節ＳＶ変更処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-23
********************************************************************************
*/
void	SURA_sv_chg(void)
{
	UNs	i, j;

	i = (SEQ_PAR_109 & 0x001c);
	j = SURA_CHG_LST;
	SURA_CHG_LST = i;
	j ^= i;
	if( i & j ){
		if( i & BIT_2 ){
			SV_ATUOSU_D9 = SV_ATUOS0_D9;			//スライド自動調節　生産設定
		}
		else if( i & BIT_3 ){
			SV_ATUOSU_D9 = SV_ATUOS1_D9;			//スライド自動調節　段取り１設定
		}
		else if( i & BIT_4 ){
			SV_ATUOSU_D9 = SV_ATUOS2_D9;			//スライド自動調節　段取り２設定
		}
		SVSW_CHG_FLG |= BIT_2;						//ﾓｰｼｮﾝ(MOT)要求
		SVSW_CHG_FLG |= BIT_4;						//OPﾃﾞｰﾀ転送要求	/* V01j */

		FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	}
}


/*
********************************************************************************
*  Module Name:		ADC_MAIN_MNG
*  Function Name:	自動金型交換ＭＡＩＮ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_MAIN_MNG (void) {
	ADC_GAMEN_CHG();			/* 自動金型交換ＷＩＮ画面変更処理	*/
	ADC_STEP_DISP();			/* ＡＤＣステップ表示処理	 	*/
	ADC_SW56DN_DISP();			/* ＡＤＣＳＷ５６下表示切換		*/
	ADC_NEXT_READ();			/* ＡＤＣ次型番号読込処理		*/
	ADC_GAMEN_END();			/* ＡＤＣ画面戻り処理			*/
	ADC_STEP_SHR();				/* ＡＤＣステップモニタデータ検索	*/
}


/*
********************************************************************************
*  Module Name:		ADC_DATA_INI
*  Function Name:	ＡＤＣデータイニシャル処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2006-08-28
********************************************************************************
*/
void	ADC_DATA_INI (void) {
	UNs		seq_chg, seq_bit, seq_old, seq_one ;
	UNs		i, *adr;

	if(SEQ_020_SV & BIT_14 == 0 )	{ return; }		//自動金型交換仕様あり？

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_5;		// new
	seq_old = ADC_CHG_LST5;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST5 = seq_bit;

	if(seq_one == 0)	{ return; }					//立上りエッジなし？

	SV_NEXTNO_D1 = 0;
	SEQ_047_SV |= BIT_15;
	FRAM_csum_set();								//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
	
	adr = &PV_MLDNO2_F11[0];
	for(i=0; i<7; i++, adr++) {
		*adr = 0x2020;
	}

	if (WINDOW_NO == 12) {
		NEXT_READ_AFTER();								/* 次期読み込み後の再表示 		*/
	}
}


/*
********************************************************************************
*  Module Name:		ADC_GAMEN_CHG
*  Function Name:	自動金型交換ＷＩＮ画面変更処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GAMEN_CHG(void) {

	UNs		seq_chg, seq_bit;

	if (ADC_DISP_FLG != 0xff)	{return;}

	seq_chg = seq_bit = SEQ_PAR_115 & 0x007f;
	seq_chg ^= ADC_CHG_LST;
	ADC_CHG_LST = seq_bit;
	if (seq_chg) {
		ADC_WIN_DISP(seq_bit);
	}
}


/*
********************************************************************************
*  Module Name:		ADC_WIN_DISP
*  Function Name:	ＡＤＣ Ｗｉｎｄｏｗ表示
*  Input	:		ｼｰｹﾝｽ115
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_WIN_DISP (UNs seq_bit)
{
	UNs		win_no;

	win_no = 12;
	if (seq_bit == BIT_1) 		{ win_no = 13; }
	else if (seq_bit == BIT_2)	{ win_no = 14; }
	else if (seq_bit == BIT_3)	{ win_no = 15; }
	else if (seq_bit == BIT_4)	{ win_no = 16; }
	else if (seq_bit == BIT_5)	{ win_no = 17; }
	else if (seq_bit == BIT_6)	{ win_no = 18; }

	if (WINDOW_NO != win_no) {
		WINDOW_NO = win_no;
		WIN_gamen_disp();						//ウインドウ画面表示

		ADC_DISP_FLG = 0x0FF;					/* ＡＤＣウインドウ表示中 */
		ADC_CHG_LST1 = 0;
		ADC_CHG_LST2 = 0;
		ADC_CHG_LST2_2 = 0;
	}
}


/*
********************************************************************************
*  Module Name:		ADC_GRPH_DISP
*  Function Name:	ＡＤＣ専用グラフィック描画
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GRPH_DISP(void) {

	UNs		*Dst_p, dot_d, line_no, dot_no;
	UNi		cnt;

	Dst_p = &LCD_WORK1[7][8][16];				//(7行目8ﾄﾞｯﾄ目の16ﾊﾞｲﾄ目)
	dot_d = 0x00ff;								//ドットパターンセット
	cnt = (40-16);
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}

	line_no = 7;
	dot_no = 8;
	dot_d = 0x0080;								//ドットパターンセット
	for ( ; line_no<13; line_no++) {
		for ( ; dot_no<16; dot_no++) {
			LCD_WORK1[line_no][dot_no][16] |= dot_d;
		}
		dot_no = 0;
	}
}

/*
********************************************************************************
*  Module Name:		ADC_SW56UP_DISP
*  Function Name:	ＡＤＣＳＷ５６上段メッセージ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW56UP_DISP(void) {

	UNs		xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	if(SEQ_047_SV & BIT_5)		{ ADC_MODE_FLG = 0; }
	else if(SEQ_047_SV & BIT_6)	{ ADC_MODE_FLG = 1; }
	else if(SEQ_047_SV & BIT_7)	{ ADC_MODE_FLG = 2; }
	else 						{ ADC_MODE_FLG = 3; }

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	g_p = mess_adr_shr( 14 );						//メッセージ画面キャラクタアドレス検索
	g_p += ADC_MODE_FLG*10;							//２０倍
	xy_no = 13;										//１３行目
	xy_no |= ((40-2-12) << 4);						//(40-2-12=26)桁目
	xy_no |= (12 << 10);							//文字数１２
	disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
#else
	xdot = 30*8*2;			// 30桁目×8ﾄﾞｯﾄ×2倍角
	ydot = 13*16*2;			// 13行目×16ﾄﾞｯﾄ×2倍角
	adr = CHR_TABLE_ADR + ((271+ADC_MODE_FLG-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		8,						/* ｷｬﾗｸ長			*/
		xdot,					/* 書出しX位置		*/
		ydot,					/* 書出しY位置		*/
		0,						/* 文字色			*/
		GAMENn_HEAD.scr_col,	/* 背景色			*/
		0x0202,					/* 文字ｻｲｽﾞ			*/
		hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VBASE				/* 表示ﾒﾓﾘ			*/
		);
	disp_moji_s_rif(
		8,						/* ｷｬﾗｸ長			*/
		xdot,					/* 書出しX位置		*/
		ydot,					/* 書出しY位置		*/
		0x0202					/* 文字ｻｲｽﾞ			*/
		);
#endif
}


/*
********************************************************************************
*  Module Name:		ADC_STEP_DISP
*  Function Name:	ＡＤＣステップ表示処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	ADC_STEP_DISP(void)
{
	UNs		seq_bit, seq_old, seq_bt, xy_no, *g_p;

	if (ADC_DISP_FLG != 0xff)	{return;}

	ADC_STPCHG_FLG = seq_bit = SEQ_PAR_114 & 0x3f00;			// new
	seq_old = ADC_CHG_LST1;								// old
	ADC_STPCHG_FLG ^= seq_old;									// new ^ old = chg
	ADC_CHG_LST1 = seq_bit;

	if (ADC_STPCHG_FLG) {

		if (ADC_STPCHG_FLG & 0x0300) {					//ｽﾃｯﾌﾟ1変化？
			FILCK_STEP1_FLG = 0;
			seq_bt = seq_bit & 0x0300;
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				xy_no = 7;									//７行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else if (seq_bt == 0x0100) {				// 反転ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//７行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			else if (seq_bt == 0x0200) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP1_FLG = 0xff;
			}
			else if (seq_bt == 0x0300) {				// 点灯ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//７行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}

		if (ADC_STPCHG_FLG & 0x0c00) {					//ｽﾃｯﾌﾟ2変化？
			FILCK_STEP2_FLG = 0;
			seq_bt = seq_bit & 0x0c00;
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				xy_no = 9;									//９行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else if (seq_bt == 0x0400) {				// 反転ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//９行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			else if (seq_bt == 0x0800) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP2_FLG = 0xff;
			}
			else if (seq_bt == 0x0c00) {				// 点灯ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//９行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}

		if (ADC_STPCHG_FLG & 0x3000) {					//ｽﾃｯﾌﾟ3変化？
			FILCK_STEP3_FLG = 0;
			seq_bt = seq_bit & 0x3000;
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				xy_no = 11;									//１１行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else if (seq_bt == 0x1000) {				// 反転ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//１１行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			else if (seq_bt == 0x2000) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP3_FLG = 0xff;
			}
			else if (seq_bt == 0x3000) {				// 点灯ﾓｰﾄﾞ？
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//１１行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}
	}

	/***************　フリッカー処理 *************/
	if(step_flick_flg != step_flick_flg_bak) {
		step_flick_flg_bak = step_flick_flg;

		if(FILCK_STEP1_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 7;									//７行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else {
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//７行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}

		if(FILCK_STEP2_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 9;									//９行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else {
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//９行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}

		if(FILCK_STEP3_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 11;									//１１行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else {
				g_p = mess_adr_shr( 14 );					//メッセージ画面キャラクタアドレス検索
				g_p += 8*10;								//mess14の8ｷｬﾗ目先頭ｱﾄﾞﾚｽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//１１行目
				xy_no |= (2 << 4);							//２桁目
				xy_no |= (12 << 10);						//文字数１２
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	ADC_STEP_DISP(void)
{
	UNs		seq_bit, seq_old, seq_bt, xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	if (ADC_DISP_FLG != 0xff)	{return;}

	ADC_STPCHG_FLG = seq_bit = SEQ_PAR_114 & 0x3f00;			// new
	seq_old = ADC_CHG_LST1;								// old
	ADC_STPCHG_FLG ^= seq_old;									// new ^ old = chg
	ADC_CHG_LST1 = seq_bit;

	if (ADC_STPCHG_FLG) {

		if (ADC_STPCHG_FLG & 0x0300) {					//ｽﾃｯﾌﾟ1変化？
			FILCK_STEP1_FLG = 0;
			seq_bt = seq_bit & 0x0300;
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 7*16*2;			// 7行目×16ﾄﾞｯﾄ×2倍角
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x0100) {				// 反転ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					11,						/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x0200) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP1_FLG = 0xff;
			}
			else if (seq_bt == 0x0300) {				// 点灯ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}

		if (ADC_STPCHG_FLG & 0x0c00) {					//ｽﾃｯﾌﾟ2変化？
			FILCK_STEP2_FLG = 0;
			seq_bt = seq_bit & 0x0c00;
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 9*16*2;			// 9行目×16ﾄﾞｯﾄ×2倍角
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x0400) {				// 反転ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					11,						/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x0800) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP2_FLG = 0xff;
			}
			else if (seq_bt == 0x0c00) {				// 点灯ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}

		if (ADC_STPCHG_FLG & 0x3000) {					//ｽﾃｯﾌﾟ3変化？
			FILCK_STEP3_FLG = 0;
			seq_bt = seq_bit & 0x3000;
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 11*16*2;			// 11行目×16ﾄﾞｯﾄ×2倍角
			if (seq_bt == 0) {							// 消去ﾓｰﾄﾞ？
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x1000) {				// 反転ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					11,						/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else if (seq_bt == 0x2000) {				// 点滅ﾓｰﾄﾞ？
				FILCK_STEP3_FLG = 0xff;
			}
			else if (seq_bt == 0x3000) {				// 点灯ﾓｰﾄﾞ？
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}
	}

	/***************　フリッカー処理 *************/
	if(step_flick_flg != step_flick_flg_bak) {
		step_flick_flg_bak = step_flick_flg;

		if(FILCK_STEP1_FLG == 0xff) {
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 7*16*2;			// 7行目×16ﾄﾞｯﾄ×2倍角
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}

		if(FILCK_STEP2_FLG == 0xff) {
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 9*16*2;			// 9行目×16ﾄﾞｯﾄ×2倍角
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}

		if(FILCK_STEP3_FLG == 0xff) {
			xdot = 2*8*2;			// 2桁目×8ﾄﾞｯﾄ×2倍角
			ydot = 11*16*2;			// 11行目×16ﾄﾞｯﾄ×2倍角
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ｷｬﾗｸ長			*/
					xdot,					/* 書出しX位置		*/
					ydot,					/* 書出しY位置		*/
					0,						/* 文字色			*/
					GAMENn_HEAD.scr_col,	/* 背景色			*/
					0x0202,					/* 文字ｻｲｽﾞ			*/
					hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE				/* 表示ﾒﾓﾘ			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		ADC_STEP_CARA
*  Function Name:	ＡＤＣステップキャラ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_CARA(UNs *top_adr)
{
}

/*
********************************************************************************
*  Module Name:		ADC_STEP_ATR
*  Function Name:	ＡＤＣステップアトリビュート
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_ATR(UNs atr)
{
	if(ADC_STEP_FLG == 1) {
//		CSR_ENZAN(0x3817);
	}
	else if(ADC_STEP_FLG == 2) {
//		CSR_ENZAN(0x3819);
	}
	else if(ADC_STEP_FLG == 3) {
//		CSR_ENZAN(0x381b);
	}
}


/*
********************************************************************************
*  Module Name:		ADC_SW2_SELECT
*  Function Name:	自動ＳＷ２選択入力処理
*  Input	:		入力ｷｰｺｰﾄﾞ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW2_SELECT(void)
{
	UNs		bit_d, s_no, *adr_p, onbit, ofbit, i;

	if (SEQ_PAR_114 & BIT_15 == 0)	{ return; }
//V01r	if (GAMEN_NO != 7)	{ return; }
	if (GAMEN_NO != 7 && GAMEN_NO != 8)	{ return; }
	if (WINDOW_NO < 13 || WINDOW_NO > 18)	{ return; }

	s_no = WINDOW_NO - 13;
	adr_p = ADC_SW2_TBL[s_no].SADR;				//仕様
	bit_d = ADC_SW2_TBL[s_no].S_ONOFF;			//仕様有無ビット
	if(*adr_p & bit_d == 0)	{ return; }			//仕様目無し?

	i = ADC_SW2_TBL[s_no].NSUU;					//ノッチ数
//2016/04/22	adr_p = Dan_Sel_Tbl_07[s_no].DADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	adr_p = ADC_SW2_TBL[s_no].DADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	bit_d = *adr_p;

	if (i == 0) {								//ノッチ数０？
		ofbit = 0xffff;							//
		onbit = ADC_SW2_TBL[s_no].N_BIT1;		//ノッチ１ビット
	}
	else if (i == 2) {									//ノッチ数２？
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//今ノッチ１？
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT1;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT2;			//次はノッチ２ビット
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//今ノッチ２？
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT2;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//次はノッチ１ビット
		}
		else {
			ofbit = 0xffff;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//次はノッチ１ビット
		}
	}
	else if (i == 3) {									//ノッチ数３？
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//今ノッチ１？
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT1;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT2;			//次はノッチ２ビット
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//今ノッチ２？
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT2;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT3;			//次はノッチ３ビット
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT3){		//今ノッチ３？
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT3;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//次はノッチ１ビット
		}
		else {
			ofbit = 0xffff;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//次はノッチ１ビット
		}
	}
	if(WINDOW_NO == 16)	{ ofbit = 0xffe3; }			//
	if(WINDOW_NO == 18)	{ ofbit = 0xe3ff; }			//

	bit_d &= ofbit;
	bit_d |= onbit;
	*adr_p = bit_d;

	SVSW_CHG_FLG |= BIT_3;					/* データチェンジフラグセット */

	ADC_SW2_DISP();
	Under_grph();

	SW16data_onset(0xff, 2);				//SW1～6の反転指定を行う

	ADC_SW2_FLG = 0xFF;						/* ＳＷ２がＯＮしていれば受け付けない */
}


/*
********************************************************************************
*  Module Name:		ADC_SW2_DISP
*  Function Name:	自動ＳＷ２選択表示処理
*  Input	:		入力ｷｰｺｰﾄﾞ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW2_DISP(void) {

	UNs		bit_d, s_no, *adr_p, ch, i;

//V01r	if (GAMEN_NO != 7)	{ return; }
	if (GAMEN_NO != 7 && GAMEN_NO != 8)	{ return; }
	if (WINDOW_NO < 13 || WINDOW_NO > 18)	{ return; }

	SW56_dncara_disp(0xff, 2);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2上)
	SW56_dncara_disp(0xff, 10);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
	SW16data_onset(0, 2);					//SW1～6の反転指定を行う

	s_no = WINDOW_NO - 13;
	adr_p = ADC_SW2_TBL[s_no].SADR;				//仕様
	bit_d = ADC_SW2_TBL[s_no].S_ONOFF;			//仕様有無ビット
	if(*adr_p & bit_d == 0)	{ return; }			//仕様目無し?

	i = ADC_SW2_TBL[s_no].NSUU;					//ノッチ数
//2016/04/22	adr_p = Dan_Sel_Tbl_07[s_no].DADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	adr_p = ADC_SW2_TBL[s_no].DADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	bit_d = *adr_p;

	if (i == 0) {								//ノッチ数０？
		return;
	}
	else if (i == 2) {									//ノッチ数２？
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//今ノッチ１？
			ch = ADC_SW2_TBL[s_no].S_IAO1;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//今ノッチ２？
			ch = ADC_SW2_TBL[s_no].S_IAO2;
		}
		else {return;}
	}
	else if (i == 3) {									//ノッチ数３？
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//今ノッチ１？
			ch = ADC_SW2_TBL[s_no].S_IAO1;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//今ノッチ２？
			ch = ADC_SW2_TBL[s_no].S_IAO2;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT3){		//今ノッチ３？
			ch = ADC_SW2_TBL[s_no].S_IAO3;
		}
		else {return;}
	}
	SW56_dncara_disp(ch, 10);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW2下)
}


/*
********************************************************************************
*  Module Name:		ADC_SW56DN_DISP
*  Function Name:	ＡＤＣＳＷ５６下表示切換
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW56DN_DISP(void)
{
	UNs		Sbit, w1, sw5_ch, sw6_ch;

	if(ADC_DISP_FLG != 0xff)	{ return;}

	Sbit = SEQ_PAR_114 & 0x001f;
	w1 = Sbit & 0x0003;
	sw5_ch = 0xff;
	ADC_SW5_FLG &= ~(BIT_0+BIT_1);
	if (w1 == BIT_0) {
		sw5_ch = 52;
		ADC_SW5_FLG |= BIT_0;
	}
	else if (w1 == BIT_1) {
		sw5_ch = 51;
		ADC_SW5_FLG |= BIT_1;
	}

	w1 = Sbit & 0x001c;
	sw6_ch = 0xff;
	ADC_SW6_FLG &= ~(BIT_2+BIT_3+BIT_4);
	if (w1 == BIT_2) {
		sw6_ch = 50;
		ADC_SW6_FLG |= BIT_2;
	}
	else if (w1 == BIT_3) {
		sw6_ch = 49;
		ADC_SW6_FLG |= BIT_3;
	}
	else if (w1 == BIT_4) {
		sw6_ch = 23;
		ADC_SW6_FLG |= BIT_4;
	}

	SW56_dncara_disp(sw5_ch, 7);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW5下)
	SW56_dncara_disp(sw6_ch, 8);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW6下)
	Under_grph();							//下段のグラフィックセット

//2016/04/22
	if(ADC_SW5_ON_FLG == 0xff) {
		SW16data_onset(0xff, 7);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
	}
	if(ADC_SW6_ON_FLG == 0xff) {
		SW16data_onset(0xff, 8);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
	}

	Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示			/* V01j */
	Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//行表示			/* V01j */
}


/*
********************************************************************************
*  Module Name:		ADC_SW5SEQ_OUT
*  Function Name:	ＡＤＣ　ＳＷ５シーケンス出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW5SEQ_OUT(void) {
	UNs		i;
	i = SEQ_PAR_047 & ~0x0003;
	i |= ADC_SW5_FLG & 0x0003;
	SEQ_PAR_047 = i;
}


/*
********************************************************************************
*  Module Name:		ADC_SW6SEQ_OUT
*  Function Name:	ＡＤＣ　ＳＷ６シーケンス出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW6SEQ_OUT(void) {
	UNs		i;
	i = SEQ_PAR_047 & ~0x001c;
	i |= ADC_SW6_FLG & 0x001c;
	SEQ_PAR_047 = i;
}


/*
********************************************************************************
*  Module Name:		ADC_NEXT_READ
*  Function Name:	ＡＤＣ次型番号読込処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_NEXT_READ(void)
{
	UNs		seq_chg, seq_bit, seq_old, seq_one ;

	if(SEQ_020_SV & BIT_14 == 0 )	{ return; }		//自動金型交換仕様あり？

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_7;		// new
	seq_old = ADC_CHG_LST3;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST3 = seq_bit;

	if(seq_one == 0)	{ return; }					//立上りエッジなし？

//2016/04/22	if(SV_NEXTNO_D1 == 0 || SV_NEXTNO_D1 > 100)	{ return; }
	if(SV_NEXTNO_D1 == 0 || SV_NEXTNO_D1 > 200)	{ return; }

//2016/04/22
////	kata_load(SV_NEXTNO_D1, &FRAM_KAT_TOP);				//型データをFROMから読込み
////
////	if(SEQ_PAR_078 & BIT_0)	{ return; }				// 型ﾃﾞｰﾀｻﾑ異常なら何もしないで終わり。
////
////	Dat_mm_inch_chg2();						//2015/01/28
////
////	if ( 9 < SV_HAN_P ) {	//V06n
////		SV_HAN_P = 0;
////	}
////	if ( 9 < SV_HAN_S ) {	//V06n
////		SV_HAN_S = 0;
////	}
////
////	SV0_MOT_FIX = 0;								//一定速度ブラグクリア			2014/10/09

	KAT_data_read_com(SV_NEXTNO_D1);


	SV_NEXTNO_D1 = 0;
	SEQ_047_SV |= BIT_15;
	FRAM_csum_set();								//設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成		2015/09/20
	
	ADC_NEXTNAME_SET();								/* ＡＤＣ次型番号名称 			*/
	NEXT_READ_AFTER();								/* 次期読み込み後の再表示 		*/
}


/*
********************************************************************************
*  Module Name:		NEXT_DATA_READ
*  Function Name:	次期型データ読込処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2016/04/22
********************************************************************************
*/
void	NEXT_DATA_READ(UNs KatNo)
{
	KAT_data_read_com(KatNo);
}


/*
********************************************************************************
*  Module Name:		ADC_NEXTNAME_SET
*  Function Name:	ＡＤＣ次型番号名称
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_NEXTNAME_SET(void)
{
	UNs		*adr, i;

	if(SV_NEXTNO_D1 == 0) {
		adr = &PV_MLDNO2_F11[0];
		for(i=0; i<7; i++, adr++) {
			*adr = 0x2020;
		}
		SEQ_047_SV |= BIT_15;
		SVSW_CHG_FLG |= BIT_3;					//データ転送シーケンス		2016/05/10
	}
//2016/04/22	else if(SV_NEXTNO_D1 <= 100) {
	else if(SV_NEXTNO_D1 <= 200) {
		adr = KAT_sv_name_tbl[SV_NEXTNO_D1];				//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
		memcpy_word(&PV_MLDNO2_F11[0], adr, 8);				//型ﾃﾞｰﾀ 書込画面用の型名称
		SEQ_047_SV &= ~BIT_15;
		SVSW_CHG_FLG |= BIT_3;					//データ転送シーケンス		2016/05/10
	}
}


/*
********************************************************************************
*  Module Name:		NEXT_READ_AFTER
*  Function Name:	次期読み込み後の再表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	NEXT_READ_AFTER(void)
{
	UNs		win_no;

	if(WINDOW_NO != 0) {
		CSR_FLG_CNT_BACK = CSR_FLG_CNT;
		WINDOW_NO_BACK = WINDOW_NO;
//		SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//反転アドレスデータ待避
	}
	win_no = WINDOW_NO;			// push
	WINDOW_NO = 0;
	GAMEN_disp();
	WINDOW_NO = win_no;			// pop

	if(WINDOW_NO != 0) {
		CSR_FLG = 5;
		CSR_FLG_CNT = CSR_FLG_CNT_BACK;
		SV_FLG_CNT = 1;
		SW_FLG_CNT = 1;
		
		if (WINDOW_NO >= 6 && WINDOW_NO >= 10) {
			DAN_WIN_FLG = 0xff;
		}
		WINDOW_NO = WINDOW_NO_BACK;
		WIN_gamen_disp();

//2016/05/12		if (WINDOW_NO >= 12 && WINDOW_NO >= 18) {
		if (WINDOW_NO >= 12 && WINDOW_NO <= 18) {
			ADC_DISP_FLG = 0xFF;
			ADC_CHG_LST1 = 0;
			ADC_CHG_LST2 = 0;
		}
//V01r		if (GAMEN_NO == 7)
		if ( GAMEN_NO == 7 || GAMEN_NO == 8)
		{
			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理
		}
	}
}

/*
********************************************************************************
*  Module Name:		ADC_GAMEN_END
*  Function Name:	ＡＤＣ画面戻り処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GAMEN_END(void)
{
	UNs		seq_chg, seq_bit, seq_old, seq_one ;

	if(ADC_DISP_FLG != 0xff)	{ return; }

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_6;		// new
	seq_old = ADC_CHG_LST4;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST4 = seq_bit;

	if(seq_one == 0)	{ return; }					//立上りエッジなし？

	CSR_FLG = 5;
	CSR_FLG_CNT = CSR_FLG_CNT_LST;
	SV_FLG_CNT = 1;
	SW_FLG_CNT = 1;
	disp_stg_sel = E_kstg_init;						//段取[基本]へ		2016/04/22
	GAMEN_NO = 7;
	if (SEQ_016_SV & BIT_10) {	// V01r
		GAMEN_NO = 8;
	}
	GAMEN_disp();
	SW14_DISP7_NON = 0;

	CSR_FLG = 5;
	CSR_FLG_CNT = CSR_FLG_CNT_LST;
	SV_FLG_CNT = 1;
	SW_FLG_CNT = 1;
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//カーソル移動(戻り値指定,移動)
}


/*
********************************************************************************
*  Module Name:		ADC_STEP_SHR
*  Function Name:	ＡＤＣステップモニタデータ検索
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_SHR(void)
{
	UNs		Sbit, i, cnt, no;

	if (WINDOW_NO != 12)	{ return; }			// ステップモニタ表示中？

	ADC_STEP_NO[0] = 0xffff;
	ADC_STEP_NO[1] = 0xffff;
	ADC_STEP_NO[2] = 0xffff;
	ADC_STEP_NO[3] = 0xffff;

	no = 0;
	cnt = 0;
	Sbit = SEQ_PAR_116;
	for (i=0; i<16; i++, no++, Sbit>>=1) {
		if (Sbit & BIT_0) {
			ADC_STEP_NO[cnt] = no;				// ステップモニタＮｏ．格納
			cnt++;
			if(cnt >= 4) {
				goto	ADC_STEPSHR_500;
			}
		}
	}
	Sbit = SEQ_PAR_117;
	for (i=0; i<14; i++, no++, Sbit>>=1) {
		if (Sbit & BIT_0) {
			ADC_STEP_NO[cnt] = no;				// ステップモニタＮｏ．格納
			cnt++;
			if(cnt >= 4) {
				goto	ADC_STEPSHR_500;
			}
		}
	}

ADC_STEPSHR_500:

	ADC_STEP_DISP1();

}


/*
********************************************************************************
*  Module Name:		ADC_STEP_DISP1
*  Function Name:	ＡＤＣステップモニタの表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	ADC_STEP_DISP1(void) {

	UNs		no, cnt;
	UNs		xy_no, *g_p;

	for (cnt=0; cnt<4; cnt++) {
		if (ADC_STEP_NO[cnt] != ADC_STEP_NO_LAST[cnt]) {

			ADC_STEP_NO_LAST[cnt] = ADC_STEP_NO[cnt];

			if (ADC_STEP_NO[cnt] == 0xffff) {
				xy_no = cnt+8;									//ｘ行目
				xy_no |= (18 << 4);								//１８桁目
				xy_no |= (20 << 10);							//文字数２０
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
			}
			else {
				g_p = mess_adr_shr( 15 );						//メッセージ画面キャラクタアドレス検索
				g_p += ADC_STEP_NO[cnt] *10;					//２０倍
				xy_no = cnt+8;									//ｘ行目
				xy_no |= (18 << 4);								//１８桁目
				xy_no |= (20 << 10);							//文字数２０
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
			}
			Lcd_line( 00,cnt+8, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		}
	}
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	ADC_STEP_DISP1(void) {

	UNs		no, cnt;
	UNs		xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	for (cnt=0; cnt<4; cnt++) {
		if (ADC_STEP_NO[cnt] != ADC_STEP_NO_LAST[cnt]) {

			ADC_STEP_NO_LAST[cnt] = ADC_STEP_NO[cnt];
			xdot = 288;
			ydot = 256 + (cnt * 32);

			if (ADC_STEP_NO[cnt] == 0xffff) {
				hrom = &SPACE_ASCII_40[0];
			}
			else {
				adr = CHR_TABLE_ADR + ((ADC_STEP_NO[cnt]+287-1) * CHAR_MOJI_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
				hrom = (UNs *)adr;
				hrom++;
			}
			disp_moji_s_color(
				16,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0,						/* 文字色			*/
				GAMENn_HEAD.scr_col,	/* 背景色			*/
				0x0202,					/* 文字ｻｲｽﾞ			*/
				hrom,					/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
				LCD_VBASE				/* 表示ﾒﾓﾘ			*/
				);
			disp_moji_s_rif(
				16,						/* ｷｬﾗｸ長			*/
				xdot,					/* 書出しX位置		*/
				ydot,					/* 書出しY位置		*/
				0x0202					/* 文字ｻｲｽﾞ			*/
				);
		}
	}
}
#endif


/*** END ***/
