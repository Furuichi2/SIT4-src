/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			画　面　表　示															*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-29
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
#include "dp_cpuab.h"							//DPRAM参照変数定義
#include "ssa_opram.h"							//OPRAM参照変数定義
#include "ssc_wrmh.h"							//work ram 参照変数定義


#define		Disp_Debug_YES	1
#define		Disp_Debug_NO	0
//#define		Disp_Debug		Disp_Debug_YES		//出荷時=NO
#define		Disp_Debug		Disp_Debug_NO		//出荷時=NO

#define		KATA_DATA_ADR_TOP	0xB9040000		//V06p


/* 外部参照関数定義 -------------------------------------------------- */
extern	void	RULET_GAMEN_INIT(void);			//ﾙｰﾚｯﾄ表示の初期化
//extern	void	GRAPH_INIT(void);				//グラフ描画初期処理
//extern	void	GRAPH_DISP(void);				//グラフ描画処理
extern	void	kag_to_kaj_sub_chg(void);		//下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		SV_SEQDT2_A91_INI;				//シーケンスモニタ設定２ /* V00p */
extern	UNs		SV_INTER_VER2;					// ｲﾝﾀｰﾛｰｯｸのﾊﾞｰｼﾞｮﾝ	(121.15-140.0~15をつぶす) /* V00p */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		ET1_VER[4];						// ET1ﾊﾞｰｼﾞｮﾝ		V05
extern	UNs		SV_SEQDT1_A91_INI;				//V06
extern	UNs		SV_INTER_VER1;					//V06
extern	UNs		GMN_PAR137;
extern	UNs		GMN_PAR021;						//V06m

/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	GAMEN_disp(void);						//画面表示
void	WIN_gamen_disp(void);					//ｳｲﾝﾄﾞｳ画面表示
void	GAMEN_base_disp(void);					//ベース画面表示
void	GAMEN_no_chg(void);						//画面Ｎｏ．変更
void	GAMEN_cls(void);						//画面データクリア
void	WIN_gamen_cls(void);					//ｳｲﾝﾄﾞｳ画面データクリア
void	DISP_after_csr(void);					//画面表示のカーソル後処理
void	DISP_after(void);						//画面表示の後処理
void	WIN_disp_after(void);					//ｳｲﾝﾄﾞｳ画面表示の後処理
void	WIN_disp_after2(void);					//ｳｲﾝﾄﾞｳ画面表示の後処理2
void	Alltbl_set(void);						//情報ﾃｰﾌﾞﾙの作成
void	Wintbl_set(void);						//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの作成
void	Disp_data_set(void);					//情報ﾃｰﾌﾞﾙの非表示処理(作成)
void	gamen_tbl_set(void);					//画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)
void	win_tbl_set(void);						//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)
void	motion_csr_clr(void);
void	EPM_TANI_CHG(void);
void	mot_type_SWset(UNs ktop);				//モーションTYPE用SWセット		V06p


/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
extern	const	UNl *	CSCOUNT_Adr_tbl[70];
extern	const	CSR_TBL_TDEF *	CSTBL_Adr_tbl[70];
extern	const	UNl *	SVCOUNT_Adr_tbl[70];
extern	const	SV_TBL_TDEF *	SVTBL_Adr_tbl[70];
extern	const	UNl *	PVCOUNT_Adr_tbl[70];
extern	const	PV_TBL_TDEF *	PVTBL_Adr_tbl[70];
extern	const	UNl *	SWCOUNT_Adr_tbl[70];
extern	const	SW_TBL_TDEF *	SWTBL_Adr_tbl[70];

extern	const	UNl *	CSCOUNT_Win_Adr_tbl[30];
extern	const	CSR_TBL_TDEF *	CSTBL_Win_Adr_tbl[30];
extern	const	UNl *	SVCOUNT_Win_Adr_tbl[30];
extern	const	SV_TBL_TDEF *	SVTBL_Win_Adr_tbl[30];
extern	const	UNl	 *PVCOUNT_Win_Adr_tbl[30];
extern	const	PV_TBL_TDEF *	PVTBL_Win_Adr_tbl[30];
extern	const	UNl *	SWCOUNT_Win_Adr_tbl[30];
extern	const	SW_TBL_TDEF *	SWTBL_Win_Adr_tbl[30];

const	UNs *	Camcsr_Name_Tbl[20] = {
			&PV_CAMNA01_C1[0],		//00/* ロータリカム１名称 */
			&PV_CAMNA02_C1[0],		//01/* ロータリカム２名称 */
			&PV_CAMNA03_C1[0],		//02/* ロータリカム３名称 */
			&PV_CAMNA04_C1[0],		//03/* ロータリカム４名称 */
			&PV_CAMNA05_C1[0],		//04/* ロータリカム５名称 */
			&PV_CAMNA06_C1[0],		//05/* ロータリカム６名称 */
			&PV_CAMNA07_C1[0],		//06/* ロータリカム７名称 */
			&PV_CAMNA08_C1[0],		//07/* ロータリカム８名称 */
			&PV_CAMNA09_C1[0],		//08/* ロータリカム９名称 */
			&PV_CAMNA10_C1[0],		//09/* ロータリカム１０名称 */
			&PV_CAMNA11_C1[0],		//10/* ロータリカム１１名称 */
			&PV_CAMNA12_C1[0],		//11/* ロータリカム１２名称 */
			&PV_CAMNA13_C1[0],		//12/* ロータリカム１３名称 */
			&PV_CAMNA14_C1[0],		//13/* ロータリカム１４名称 */
			&PV_CAMNA15_C1[0],		//14/* ロータリカム１５名称 */
			&PV_CAMNA16_C1[0],		//15/* ロータリカム１６名称 */
			&PV_CAMNA17_C1[0],		//16/* ロータリカム１７名称 */
			&PV_CAMNA18_C1[0],		//17/* ロータリカム１８名称 */
			&PV_CAMNA19_C1[0],		//18/* ロータリカム１９名称 */
			&PV_CAMNA20_C1[0]		//19/* ロータリカム２０名称 */
		};

const	UNs *	Camcsr_Name_TblSV[20] = {
			&SV_CAMNA01_C1[0],		//00/* ロータリカム１名称 */
			&SV_CAMNA02_C1[0],		//01/* ロータリカム２名称 */
			&SV_CAMNA03_C1[0],		//02/* ロータリカム３名称 */
			&SV_CAMNA04_C1[0],		//03/* ロータリカム４名称 */
			&SV_CAMNA05_C1[0],		//04/* ロータリカム５名称 */
			&SV_CAMNA06_C1[0],		//05/* ロータリカム６名称 */
			&SV_CAMNA07_C1[0],		//06/* ロータリカム７名称 */
			&SV_CAMNA08_C1[0],		//07/* ロータリカム８名称 */
			&SV_CAMNA09_C1[0],		//08/* ロータリカム９名称 */
			&SV_CAMNA10_C1[0],		//09/* ロータリカム１０名称 */
			&SV_CAMNA11_C1[0],		//10/* ロータリカム１１名称 */
			&SV_CAMNA12_C1[0],		//11/* ロータリカム１２名称 */
			&SV_CAMNA13_C1[0],		//12/* ロータリカム１３名称 */
			&SV_CAMNA14_C1[0],		//13/* ロータリカム１４名称 */
			&SV_CAMNA15_C1[0],		//14/* ロータリカム１５名称 */
			&SV_CAMNA16_C1[0],		//15/* ロータリカム１６名称 */
			&SV_CAMNA17_C1[0],		//16/* ロータリカム１７名称 */
			&SV_CAMNA18_C1[0],		//17/* ロータリカム１８名称 */
			&SV_CAMNA19_C1[0],		//18/* ロータリカム１９名称 */
			&SV_CAMNA20_C1[0]		//19/* ロータリカム２０名称 */
		};

const	UNs *	Camcsr_Name_Tbl1[20] = {
			&SV_CAMNA0_C1,			//ロータリカム１汎用選択種別
			&SV_CAMNA1_C1,			//ロータリカム２汎用選択種別
			&SV_CAMNA2_C1,			//ロータリカム３汎用選択種別
			&SV_CAMNA3_C1,			//ロータリカム４汎用選択種別
			&SV_CAMNA4_C1,			//ロータリカム５汎用選択種別
			&SV_CAMNA5_C1,			//ロータリカム６汎用選択種別
			&SV_CAMNA6_C1,			//ロータリカム７汎用選択種別
			&SV_CAMNA7_C1,			//ロータリカム８汎用選択種別
			&SV_CAMNA8_C1,			//ロータリカム９汎用選択種別
			&SV_CAMNA9_C1,			//ロータリカム１０汎用選択種別
			&SV_CAMNAA_C1,			//ロータリカム１１汎用選択種別
			&SV_CAMNAB_C1,			//ロータリカム１２汎用選択種別
			&SV_CAMNAC_C1,			//ロータリカム１３汎用選択種別
			&SV_CAMNAD_C1,			//ロータリカム１４汎用選択種別
			&SV_CAMNAE_C1,			//ロータリカム１５汎用選択種別
			&SV_CAMNAF_C1,			//ロータリカム１６汎用選択種別

			&SV_CAMNA_C1,			//ロータリカム１７～２０用ダミー領域
			&SV_CAMNA_C1,			//ロータリカム１７～２０用ダミー領域
			&SV_CAMNA_C1,			//ロータリカム１７～２０用ダミー領域
			&SV_CAMNA_C1			//ロータリカム１７～２０用ダミー領域
		};

const	UNs *	Camcsr_Name_TblSW[16] = {
			&PV_CAMNAM_C2[0],		//汎用出力識別 BIT_0
			&PV_CAMSW1_C1[0],		//汎用出力識別 BIT_1
			&PV_CAMSW2_C1[0],		//汎用出力識別 BIT_2
			&PV_CAMSW3_C1[0],		//汎用出力識別 BIT_3
			&PV_CAMSW4_C1[0],		//汎用出力識別 BIT_4
			&PV_CAMSW5_C1[0],		//汎用出力識別 BIT_5
			&PV_CAMSW6_C1[0],		//汎用出力識別 BIT_6
			&PV_CAMSW7_C1[0],		//汎用出力識別 BIT_7
			&PV_CAMSW8_C1[0],		//汎用出力識別 BIT_8
			&PV_CAMSW9_C1[0],		//汎用出力識別 BIT_9
			&PV_CAMSWA_C1[0],		//汎用出力識別 BIT_A
			&PV_CAMSWB_C1[0],		//汎用出力識別 BIT_B
			&PV_CAMSWC_C1[0],		//汎用出力識別 BIT_C
			&PV_CAMSWD_C1[0],		//汎用出力識別 BIT_D
			&PV_CAMSWE_C1[0],		//汎用出力識別 BIT_E
			&PV_CAMSWF_C1[0],		//汎用出力識別 BIT_F
		};


/*
********************************************************************************
*  Module Name:		GAMEN_disp
*  Function Name:	画面表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	GAMEN_disp(void)
{
	GGAMEN_DISP_FLG = 0xff;					//画面表示制御中フラグＯＮ
	SVPV_LCD_FLG = 0xff;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)

	Lcd_off();								//画面OFF

	GAMEN_base_disp();						//ベース画面表示

	SVdata_disp();							//設定値情報　表示
	PVdata_disp_all();						//全　実測値情報　表示

	SWchg_disp();							//ＳＷデータ情報　表示

	Under_grph();							//下段のグラフィックセット

	DISP_after();							//画面表示の後処理

	if(CSR_FLG == 5){
	}
	else{
		CSR_FLG = 0;						//ホームポジションセット
	}
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動
	CSR_FLG = 0;							//ホームポジションセット

	DISP_after_csr();						//画面表示のカーソル後処理

	DISP_cam_csr_name();					//カムカーソル名称表示

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//全表示

	Lcd_on();								//画面ON

	SVPV_LCD_FLG = 0x00;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
	GGAMEN_DISP_FLG = 0x00;					//画面表示制御中フラグＯＦＦ

}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	GAMEN_disp(void)
{
	GGAMEN_DISP_FLG = 0xff;					//画面表示制御中フラグＯＮ
	SVPV_LCD_FLG = 0xff;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ	INS

	GAMEN_base_disp();						//ベース画面表示

	SEQ_PAR_051 &= ~cBIT14;					//モード変更有りフラグOFF		V06n

	Gamenn_Disp_Csr(LCD_VBASE);					//画面Ｎｏ．ｎのカーソルキャラクタ全表示

	SVdata_disp();							//設定値情報　表示
	PVdata_disp_all();						//全　実測値情報　表示

	SWchg_disp();							//ＳＷデータ情報　表示

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ	INS

	Gamenn_Graphic(LCD_VBASE);					//画面Ｎｏ．ｎのグラフィック全表示

	DISP_after();							//画面表示の後処理

	if(CSR_FLG == 5){
	}
	else{
		CSR_FLG = 0;						//ホームポジションセット
	}

	DISP_after_csr();						//画面表示のカーソル後処理

	DISP_cam_csr_name();					//カムカーソル名称表示

	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動
	CSR_FLG = 0;							//ホームポジションセット

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	if ( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30)	//モーション領域をワークへ   やむをえず
	{
		mmon_vabse_to_vmon1();
		SV_DANSUU_SRV_BAK = 0;
		mmon_tchk_disp(0);
		mmon_vmon2_to_vbase();
	}

	LCD_All_Disp();

	if ( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30)	//モーション領域をワークへ   やむをえず
	{
		mmon_vmon1_to_vbase();
	}

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ	INS

	SVPV_LCD_FLG = 0x00;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
	GGAMEN_DISP_FLG = 0x00;					//画面表示制御中フラグＯＦＦ

}
#endif


/*
********************************************************************************
*  Module Name:		WIN_gamen_disp
*  Function Name:	ｳｲﾝﾄﾞｳ画面表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	WIN_gamen_disp(void)
{
	UNs		i;

	SVPV_LCD_FLG = 0xff;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)

	WIN_gamen_cls();						//ｳｲﾝﾄﾞｳ画面データクリア

	WIN_disp_after();						//画面表示の後処理

	i = 0x0001;
	if( WINDOW_NO == 6 ) {					//半ｳｲﾝﾄﾞｳ画面　？
		i |= BIT_15;						//半ｳｲﾝﾄﾞｳ ﾌﾗｸﾞ ON
	}
	if( (WINDOW_NO > 6) && (WINDOW_NO < 10) ) {		//半ｳｲﾝﾄﾞｳ画面　？		V01j
		i |= BIT_15;						//半ｳｲﾝﾄﾞｳ ﾌﾗｸﾞ ON
	}
	disp_all_s(WINDOW_NO, i, 0x00);			//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	Wintbl_set();							//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの作成

	SVdata_disp();							//設定値情報　表示
	PVdata_disp_all();						//全　実測値情報　表示
	SWchg_disp();							//ＳＷデータ情報　表示

	DISP_cam_csr_name();					//カムカーソル名称表示

	WIN_disp_after2();						//ｳｲﾝﾄﾞｳ画面表示の後処理2

	CSR_FLG = 0;							//ホームポジションセット
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

	Under_grph();							//下段のグラフィックセット

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	for( i=6 ; i < 15 ; i++ ) {
		Lcd_line(00, i, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
		Lcd_line(01, i, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示(LCD2)
	}

	SVPV_LCD_FLG = 0x00;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	WIN_gamen_disp(void)
{
	UNs		i;

	SVPV_LCD_FLG = 0xff;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)

	Windown_Disp_Init();

	WIN_gamen_cls();						//ｳｲﾝﾄﾞｳ画面データクリア

	WIN_disp_after();						//画面表示の後処理

	i = 0x0001;
	if( WINDOW_NO == 6 ) {					//半ｳｲﾝﾄﾞｳ画面　？
		i |= BIT_15;						//半ｳｲﾝﾄﾞｳ ﾌﾗｸﾞ ON
	}
	if( (WINDOW_NO > 6) && (WINDOW_NO < 10) ) {		//半ｳｲﾝﾄﾞｳ画面　？		V01j
		i |= BIT_15;						//半ｳｲﾝﾄﾞｳ ﾌﾗｸﾞ ON
	}

	disp_all_s_color(LCD_VBASE);		//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	Wintbl_set();							//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの作成

	Gamenn_Disp_Csr(LCD_VBASE);						//画面Ｎｏ．ｎのカーソルキャラクタ全表示

	SVdata_disp();							//設定値情報　表示
	PVdata_disp_all();						//全　実測値情報　表示

	SWchg_disp();							//ＳＷデータ情報　表示

	DISP_cam_csr_name();					//カムカーソル名称表示

	WIN_disp_after2();						//ｳｲﾝﾄﾞｳ画面表示の後処理2

	Gamenn_Graphic(LCD_VBASE);					//画面Ｎｏ．ｎのグラフィック全表示

	CSR_FLG = 0;							//ホームポジションセット
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

	WDT_Rifresh();							//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	WIN_All_Disp();

	SVPV_LCD_FLG = 0x00;					//設定値＆実測値のLCD表示ﾌﾗｸﾞ(00＝表示／00≠非表示)
}
#endif


/*
********************************************************************************
*  Module Name:		GAMEN_base_disp
*  Function Name:	ベース画面表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
void	GAMEN_base_disp(void)
{

	GAMEN_no_chg();						//画面Ｎｏ．変更
	GAMEN_cls();						//画面データクリア

	disp_all_s(GAMEN_NO, 0x00, 0x00);	//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	Alltbl_set();						//情報ﾃｰﾌﾞﾙの作成
}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
void	GAMEN_base_disp(void)
{
	Gamenn_Disp_Init();

	GAMEN_no_chg();						//画面Ｎｏ．変更
	GAMEN_cls();						//画面データクリア

	disp_all_s_color(LCD_VBASE);		//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換

	if (SEQ_PAR_113 & BIT_2)			//制動性能試験中？			//V05r(INS)
	{
//		Disp_seidouseinou(1,LCD_VBASE);		//制動性能表示
		SEIDOU_SEQ_LST &= ~BIT_2;			//制動性能表示
	}

	WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	Alltbl_set();						//情報ﾃｰﾌﾞﾙの作成
}
#endif


/*
********************************************************************************
*  Module Name:		GAMEN_no_chg
*  Function Name:	画面Ｎｏ．変更
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	GAMEN_no_chg(void)
{

	if(GAMEN_NO == 2){				//生産画面　2は未使用
		GAMEN_NO = 1;				//生産画面　基本
	}

	/* V01d */
////	else if(GAMEN_NO == 6){			//段取画面　簡易表示　なし
////		GAMEN_NO = 7;				//段取画面　高機能表示
////	}

//	else if(GAMEN_NO == 11){		//設定画面　ﾃﾞｰﾀ設定
//SIT-Sなし		if(SEQ_016_SV & BIT_7){		//高機能選択(簡易型／高機能型(1:高機能))
//			GAMEN_NO == 17;			//設定画面　ﾃﾞｰﾀ設定中型
//		}
//	}

	else if(GAMEN_NO == 21){		//設定画面　ﾛｰﾀﾘｶﾑ1画面？
		if(ROT1_GAMEN_NON == 0xff){
			GAMEN_NO == 22;			//設定画面　ﾛｰﾀﾘｶﾑ2
		}
		if(ROT2_GAMEN_NON == 0xff){
			GAMEN_NO == 25;			//設定画面　ﾛｰﾀﾘｶﾑ3
		}
		if(ROT3_GAMEN_NON == 0xff){
			GAMEN_NO == 21;			//設定画面　ﾛｰﾀﾘｶﾑ1
		}
	}

//;/*********	2000-01-05	上型クランパ６回路選択 V03a	**************/
//	CMP	GAMEN_NO,18			;
//	JNE	GAMNO_CHG_500			;
//;
//	TEST	SEQ_022_SV,BIT_5		;/* 上型ｸﾗﾝﾊﾟ選択がＯＮだったらだめ */
//	JNZ	GAMNO_CHG_500			;
//	TEST	SEQ_026_SV,BIT_1		;/*  */
//	JZ	GAMNO_CHG_500			;
//;
//	MOV	GAMEN_NO,28			;
//	JMP	GAMNO_CHG_END			;
//;/****************************************************************************/
//GAMNO_CHG_500:
//;
//GAMNO_CHG_END:

}


/*
********************************************************************************
*  Module Name:		GAMEN_cls
*  Function Name:	画面データクリア
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	GAMEN_cls(void)
{
	UNi	size;
	UNs	*dst1_p, *dst2_p;

	DANseq_alloff();					//段取り用シーケンスＯＦＦ

	WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

#if	( SIT_TYPE_SEL == TYPE_SIT3 )
	dst1_p= &LCD_WORK1[0][0][0];		//領域クリア(表示ﾜｰｸ領域LCD1)
	dst2_p= &LCD_WORK2[0][0][0];		//領域クリア(表示ﾜｰｸ領域LCD2)
	size = (sizeof(LCD_WORK1) >> 1);
	while(size--) {
		*dst1_p++ = 0x0000;				//領域コピー
		*dst2_p++ = 0x0000;				//領域コピー
	}
#else
	Gamenn_Screen(LCD_VBASE);						//ｽｸﾘｰﾝ色で埋める
#endif

	WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ

	memset_word(&CSR_buff[0].XY_POS, 0x0000, (sizeof(CSR_buff)/2));		//領域クリア(カーソル情報テーブル定義領域)
	memset_word(&SV_buff[0].XY_POS, 0x0000, (sizeof(SV_buff)/2));		//領域クリア(設定値情報テーブル定義領域)
	memset_word(&PV_buff[0].XY_POS, 0x0000, (sizeof(PV_buff)/2));		//領域クリア(実測値情報テーブル定義領域)
	memset_word(&SW_buff[0].XY_POS, 0x0000, (sizeof(SW_buff)/2));		//領域クリア(ＳＷデータ情報テーブル定義領域)

	CSR_CNT = 0;						/* カーソルカウンタ */
	CSR_CNT1 = 0;						/* カーソルカウンタ */
	SV_CNT = 0;							/* 設定値カウンタ */
	PV_CNT = 0;							/* 実測値カウンタ */
	SW_CNT = 0;							/* ＳＷデータカウンタ */
	SW_CNT1 = 0;						/* ＳＷデータカウンタ */

	CSR_TBL_POS_NOW = 0xff;
	SV_TBL_POS_NOW = 0xff;
	SW_TBL_POS_NOW = 0xff;

	CSR_MOVE_OK_FLG = 0;				//ｶｰｿﾙ移動ﾌﾗｸﾞ(00:移動／FF:禁止)
	CSR_MOVE_NON = 0;					//ENT KEY後のｶｰｿﾙ移動ﾌﾗｸﾞ(00:移動／FF:禁止)

	CSR_POS_LAST = 0xffff;				/* 前回カーソルポジションデータクリア */
	CSR_BAK_X_POS = 0xffff;				/* 前回カーソルポジションデータクリア */

	SV_DATA_CHG = 0x00;					//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
	CSR_ON_FLG = 0x00;					/* カーソル表示フラグＯＦＦ */
	SW14_ON_FLG = 0x00;

	RULET_DISP_FLG = 0;					//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
	DEG_DISP_FLG = 0;					//角度表示フラグ(00:なし／FF:あり)
	SEISAN_DISP_FLG = 0;				//生産の行程表示(00:なし／FF:あり)
	INTROCK_DISP_FLG = 0;				//ガイダンス表示(00:なし／FF:あり)

//	STOP_DISP_FLG = 0;					//ＳＰＭ表示(00:なし／FF:あり)

	SEI_INF_FLG_LAST = 0x0FF;
//	IL_DISP_LAST = 0x0FF;

	IROCK_NO_LAST[0] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[1] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[2] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[3] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[4] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[5] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[6] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/

//	IL_DISP_FLG = 0x00;					/* ＩＬ表示フラグリセット */

	WINDOW_NO = 0x00;					/* ウインドウ画面番号クリア */

	PV_DISP_CNT = 0x01;

	RULET_NOW_LST = 0x0FFFF;
	DEG_DISP_LST = 0x0FFFF;				/* 角度ﾃﾞｰﾀ変化あり？ */
	STOPTIME_DISP_LST = 0x0FFFF;		/* 角度ﾃﾞｰﾀ変化あり？ */

	SEISAN_SW56_FLG = 0x00;

//V06n	SEQ_PAR_051 = 0;
	SEQ_PAR_052 = 0;
	SEQ_PAR_054 = 0;

	RULET_HIGH_FLG = 0x055;				/* 高速ルーレット描画フラグクリア */

	CSR_DAN_CSR_LST = 0x0FF;			/* 段取り画面SW56ｼｰｹﾝｽｷｬﾝｾﾙ用 */

	SW56_MUSK_FLG = 0x0404;

	ADC_DISP_FLG = 0;			/* ＡＤＣウインドウ表示中クリア */
	ADC_SW2_FLG = 0;			/* ＳＷ３４がＯＮしていれば受け付けない */
	ADC_SW34_FLG = 0;			/* ＳＷ３４がＯＮしていれば受け付けない */

	ADC_SW5_FLG = 0;			/* ＳＷ５出力シーケンスクリア */
	ADC_SW6_FLG = 0;			/* ＳＷ５出力シーケンスクリア */

	EPM_TANI_CHG();				//V06a
}


/*
********************************************************************************
*  Module Name:		WIN_gamen_cls
*  Function Name:	ｳｲﾝﾄﾞｳ画面データクリア
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
void	WIN_gamen_cls(void)
{

	CSR_POS_LAST = 0xffff;				/* 前回カーソルポジションデータクリア */	//V06c
	CSR_BAK_X_POS = 0xffff;				/* 前回カーソルポジションデータクリア */	//V06c

	CSR_disp_off();						//カーソル表示消去

#if	( SIT_TYPE_SEL == TYPE_SIT3 )
	memset_word(&LCD_WORK2[6][0][0], 0x0000, 9*16*40);	//裏画面のルーレット表示部をクリアする
#else
	Window_Screen(LCD_VBASE);					//ｽｸﾘｰﾝ色で埋める
#endif

	CSR_TBL_POS_NOW = 0xff;
	SV_TBL_POS_NOW = 0xff;
	SW_TBL_POS_NOW = 0xff;

	CSR_MOVE_OK_FLG = 0;				//ｶｰｿﾙ移動ﾌﾗｸﾞ(00:移動／FF:禁止)

	SV_DATA_CHG = 0x00;					//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
	SW14_ON_FLG = 0x00;

//	IL_DISP_LAST = 0x0FF;

	IROCK_NO_LAST[0] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[1] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[2] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[3] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[4] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[5] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/
	IROCK_NO_LAST[6] = 0xffff;			/* ｲﾝﾀｰﾛｯｸ表示番号列前回値	*/

//	IL_DISP_FLG = 0x00;					/* ＩＬ表示フラグリセット */
	RULET_NOW_LST = 0x0FFFF;

	SEISAN_SW56_FLG = 0x00;

	RULET_HIGH_FLG = 0x055;				/* 高速ルーレット描画フラグクリア */
	CSR_DAN_CSR_LST = 0x0FF;			/* 段取り画面SW56ｼｰｹﾝｽｷｬﾝｾﾙ用 */
	SW56_MUSK_FLG = 0x0404;

	ADC_DISP_FLG = 0;			/* ＡＤＣウインドウ表示中クリア */
	ADC_SW2_FLG = 0;			/* ＳＷ３４がＯＮしていれば受け付けない */
	ADC_SW34_FLG = 0;			/* ＳＷ３４がＯＮしていれば受け付けない */

	ADC_SW5_FLG = 0;			/* ＳＷ５出力シーケンスクリア */
	ADC_SW6_FLG = 0;			/* ＳＷ５出力シーケンスクリア */

	EPM_TANI_CHG();				//V06a
}


/*
********************************************************************************
*  Module Name:		DISP_after_csr
*  Function Name:	画面表示のカーソル後処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
void	DISP_after_csr(void)
{
	switch(GAMEN_NO) {
		default:
		case 2:			//生産画面　中型基本(未使用)
		case 6:			//段取画面　基本(画面番号６ＳＷ１～４処理)(未使用)
			break;

		case 1:			//生産画面　基本(画面番号１ＳＷ１～４処理)
			if( 00 == (SEQ_016_SV & BIT_12) &&		//ﾛｯﾄｶｳﾝﾀ1の非表示
				00 == (SEQ_016_SV & BIT_14) ) {		//ﾛｯﾄｶｳﾝﾀ2の非表示
				SW56_dncara_disp(0xff, 4);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 12);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				Under_grph();						//下段のグラフィックセット
			}
			switch(SW14_ON1_FLG) {
				default:
					SW14_ON1_FLG = 0;
				case 0000:							//前回何かのキーが押されいたか？
					break;

				case 0x0002:						//今ﾄｰﾀﾙｶｳﾝﾀが押し
				case 0x0082:						//今ﾄｰﾀﾙｶｳﾝﾀが押し
					CSR_FLG_CNT = 1;				//カーソル番号セット
					SV_FLG_CNT = 0;					//設定値番号セット
					SW_FLG_CNT = 1;					//ＳＷ番号セット
					CSR_move(05, 00);				//カーソル移動(戻り値指定,移動OK)

					SW16data_onset(0xff, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
					SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

					if(SW14_ON1_FLG & 0x80){
						COUNT_HOSEI_ADR = PV_buff[0].XY_POS;	//反転アドレスデータ待避
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
																//カウンタ補正,ＳＷ５
						SW56_upcara_disp(06, 05);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
														//減,ＳＷ５
						SW56_dncara_disp(05, 07);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
														//増,ＳＷ６
						SW56_dncara_disp(06, 0x08);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
					}
					Under_grph();					//下段のグラフィックセット
					break;

				case 0x0003:						//今ﾛｯﾄｶｳﾝﾀ1が押し
				case 0x0083:						//今ﾛｯﾄｶｳﾝﾀ1が押し
					if( SEQ_016_SV & BIT_12 ) {		//ﾛｯﾄｶｳﾝﾀ1の非表示？
						CSR_FLG_CNT = 2;				//カーソル番号セット
						SV_FLG_CNT = 1;					//設定値番号セット
						SW_FLG_CNT = 1;					//ＳＷ番号セット
						CSR_move(05, 00);				//カーソル移動(戻り値指定,移動OK)

						SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

						if(SW14_ON1_FLG & 0x80){
							COUNT_HOSEI_ADR = PV_buff[1].XY_POS;	//反転アドレスデータ待避
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
														//カウンタ補正,ＳＷ５
							SW56_upcara_disp(06, 05);	//ＳＷ５６上段キャラクタをＳＷ領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
														//減,ＳＷ５
							SW56_dncara_disp(05, 07);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
														//増,ＳＷ６
							SW56_dncara_disp(06, 0x08);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
						}
						Under_grph();					//下段のグラフィックセット
					}
					else{
						SW14_ON1_FLG = 0;
					}
					break;

				case 0x0004:						//今ﾛｯﾄｶｳﾝﾀ2が押し
				case 0x0084:						//今ﾛｯﾄｶｳﾝﾀ2が押し
					if( SEQ_016_SV & BIT_14 ) {		//ﾛｯﾄｶｳﾝﾀ2の非表示
						CSR_FLG_CNT = 3;				//カーソル番号セット
						SV_FLG_CNT = 1;					//設定値番号セット
						SW_FLG_CNT = 1;					//ＳＷ番号セット
						CSR_move(05, 00);				//カーソル移動(戻り値指定,移動OK)

						SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
						SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

						if(SW14_ON1_FLG & 0x80){
							COUNT_HOSEI_ADR = PV_buff[2].XY_POS;	//反転アドレスデータ待避
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//カウンタ補正の実測値反転処理
														//カウンタ補正,ＳＷ５
							SW56_upcara_disp(06, 5);	//ＳＷ５６上段キャラクタをＳＷ領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
														//減,ＳＷ５
							SW56_dncara_disp(05, 7);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
														//増,ＳＷ６
							SW56_dncara_disp(06, 8);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
						}
						Under_grph();					//下段のグラフィックセット
					}
					else{
						SW14_ON1_FLG = 0;
					}
					break;

				case 5:						//今ｵｰﾊﾞﾗｲﾄﾞが押し		V01z(追加)
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
					break;

			}
			break;

//		case 3:			//生産画面　ﾓｰｼｮﾝ設定
//		case 28:		//設定画面　ﾓｰｼｮﾝ設定
//			mmon_kaiten_chg();							//回転方式による設定値 切換え
//			break;

		case 7:			//段取画面　中型基本(画面番号６ＳＷ１～４処理)
//			if(SW14_DISP7_NON == 0xff){
//				return;
//			}
			if(SW14_ON6_FLG < 11){
				if(SW14_ON6_FLG == 0){				//前回何も押されていない？
					CSR_FLG_CNT = 1;				//カーソル番号セット
				}
				else{
					CSR_FLG = 5;							//カーソル表示位置指定
					CSR_FLG_CNT = (SW14_ON6_FLG & 0x00ff);	//カーソル番号セット
					CSR_FLG_CNT --;
				}
			}
			else{
				CSR_FLG = 5;						//カーソル表示位置指定
				CSR_FLG_CNT = CSR_FLG_CNT_LST;		//カーソル番号セット
			}

			SV_FLG_CNT = 0;							//設定値番号セット
			SW_FLG_CNT = 0;							//ＳＷ番号セット
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

			SW16data_onset(0xff, 05);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			if(CSR_FLG_CNT == 1 &&		//スライド調節
				SEQ_020_SV & 0x0050){				//ウインドウを出す条件
//				SEQ_020_SV & 0x0060){				//ウインドウを出す条件
													//SW5
				SW56_dncara_disp(0xff, 7);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
													//SW6 開く
				SW56_dncara_disp(16, 8);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();						//下段のグラフィックセット
			}
			if(DAN_DAN_FLG != 0xff ||				//ウィンドウ画面まで戻す処理
				WINDOW_NO_BACK == 0 ){				//段取り画面へ戻るときはいらない
				return;
			}
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//現在のｶｰｿﾙ位置情報読込
//			DAN_WIN_FLG = 0xff;

			CSR_FLG = 5;							//カーソル表示位置指定
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//カーソル番号セット
			SV_FLG_CNT = 1;							//設定値番号セット
			SW_FLG_CNT = 1;							//ＳＷ番号セット

			disp_stg_sel = E_kstg_scon;				//段取[スライド調節]へ
			WINDOW_NO = WINDOW_NO_BACK;				//開く
			WIN_gamen_disp();						//ｳｲﾝﾄﾞｳ画面表示

//			DAN_WIN_FLG = 0x00;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理

			CSR_FLG = 5;							//カーソル表示位置指定
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//カーソル番号セット
			SV_FLG_CNT = 1;							//設定値番号セット
			SW_FLG_CNT = 1;							//ＳＷ番号セット
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

			G07_WIN_FLG = 0xff;
			break;

		case 8:			//段取画面　中型基本(画面番号６ＳＷ１～４処理)  //V01r
//			if(SW14_DISP7_NON == 0xff){
//				return;
//			}
			if(SW14_ON6_FLG < 11){
				if(SW14_ON6_FLG == 0){				//前回何も押されていない？
					CSR_FLG_CNT = 1;				//カーソル番号セット
				}
				else{
					CSR_FLG = 5;							//カーソル表示位置指定
					CSR_FLG_CNT = (SW14_ON6_FLG & 0x00ff);	//カーソル番号セット
//V01j					CSR_FLG_CNT --;
				}
			}
			else{
				CSR_FLG = 5;						//カーソル表示位置指定
				CSR_FLG_CNT = CSR_FLG_CNT_LST;		//カーソル番号セット
			}

			SV_FLG_CNT = 0;							//設定値番号セット
			SW_FLG_CNT = 0;							//ＳＷ番号セット
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

			SW16data_onset(0xff, 05);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			if(CSR_FLG_CNT == /*1 V01j*/2 &&		//スライド調節
				SEQ_020_SV & 0x0050){				//ウインドウを出す条件
//				SEQ_020_SV & 0x0060){				//ウインドウを出す条件
													//SW5
				SW56_dncara_disp(0xff, 7);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
													//SW6 開く
				SW56_dncara_disp(16, 8);			//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();						//下段のグラフィックセット
			}
			if(DAN_DAN_FLG != 0xff ||				//ウィンドウ画面まで戻す処理
				WINDOW_NO_BACK == 0 ){				//段取り画面へ戻るときはいらない
				return;
			}
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//現在のｶｰｿﾙ位置情報読込
//			DAN_WIN_FLG = 0xff;

			CSR_FLG = 5;							//カーソル表示位置指定
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//カーソル番号セット
			SV_FLG_CNT = 1;							//設定値番号セット
			SW_FLG_CNT = 1;							//ＳＷ番号セット

//V01j			disp_stg_sel = E_kstg_scon;				//段取[スライド調節]へ
			WINDOW_NO = WINDOW_NO_BACK;				//開く
			if (WINDOW_NO == 6) {					//V01j
				disp_stg_sel = E_kstg_scon;			//段取[スライド調節]へ
			}
			else if (WINDOW_NO == 7) {
				disp_stg_sel = E_kstg_bara;			//段取[バランサ圧力調節]へ
			}
			else if ( (WINDOW_NO == 8) || (WINDOW_NO == 9) ) {
				disp_stg_sel = E_kstg_daic;			//段取[ダイクッション調節]へ
			}
			else if ( (WINDOW_NO >= 12) || (WINDOW_NO <= 18) ) {
				disp_stg_sel = E_kstg_kana;			//段取[自動金型交換]へ
			}
			WIN_gamen_disp();						//ｳｲﾝﾄﾞｳ画面表示

//			DAN_WIN_FLG = 0x00;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//カウンタ補正の実測値反転処理

			CSR_FLG = 5;							//カーソル表示位置指定
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//カーソル番号セット
			SV_FLG_CNT = 1;							//設定値番号セット
			SW_FLG_CNT = 1;							//ＳＷ番号セット
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//カーソル移動

			G07_WIN_FLG = 0xff;
			break;
	}
}


/*
********************************************************************************
*  Module Name:		DISP_after
*  Function Name:	画面表示の後処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
void	DISP_after(void)
{
	UNs		*bf_p, i, j;
	UNb		wk[8];
	UNs		xy_wk;
	UNs		ktop;

	GAMENn_SCR_COL = GAMENn_HEAD.scr_col;

	switch(GAMEN_NO) {
		default:
		case 2:			//生産画面　中型基本(未使用)
		case 11:		//設定画面　ﾃﾞｰﾀ設定
		case 18:		//設定画面　ﾃﾞｰﾀ設定選択中型
		case 24:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ　NO/NC設定
		case 25:		//設定画面　ﾛｰﾀﾘｶﾑ　17～20設定
		case 27:		//設定画面　ｺｲﾙﾗｲﾝｶﾑ設定
		case 42:		//ｼｽﾃﾑ画面　速度到達ﾃﾞｰﾀ設定
		case 46:		//ｼｽﾃﾑ画面　ｵﾌﾟｼｮﾝ構成ﾃﾞｰﾀ画面
//V01j		case 47:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(左)
//V01j		case 48:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(右)
//V01j		case 49:		//ｼｽﾃﾑ画面　ﾊﾞﾗﾝｻ圧力調整
		case 53:		//ｼｽﾃﾑ画面　ｺｲﾙﾗｲﾝ仕様設定画面
		case 54:		//ｼｽﾃﾑ画面　ﾃﾞｰﾀﾛｰﾄﾞ画面
			break;

		case 1:			//生産画面　基本
			RULET_DISP_FLG = 0xff;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)
			SEISAN_DISP_FLG = 0xff;			//生産の行程表示(00:なし／FF:あり)
			INTROCK_DISP_FLG = 0xff;		//ガイダンス表示(00:なし／FF:あり)

			RULET_GAMEN_INIT();				//ﾙｰﾚｯﾄ表示の初期化

			CSR_MOVE_OK_FLG = 0xff;			//ｶｰｿﾙ移動ﾌﾗｸﾞ(00:移動／FF:禁止)

//V06n			SEQ_PAR_051 = BIT_0;			//生産画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//生産画面表示(1:表示中)

			break;

		case 3:			//生産画面　ﾓｰｼｮﾝ設定
		case 28:		//設定画面　ﾓｰｼｮﾝ設定
		case 6:			//生産画面　ﾓｰｼｮﾝ設定6～10		/* V01d */
		case 30:		//設定画面　ﾓｰｼｮﾝ設定6～10		/* V01d */
			CSR_FLG = 0;						//カーソル表示位置指定
			CSR_FLG_CNT = 1;					//カーソル番号セット
			SV_FLG_CNT = 1;						//設定値番号セット
			SW_FLG_CNT = 1;						//ＳＷ番号セット

			SW16data_onset(0xff, 02);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);			//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			mmon_sel_chk();						//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ

//V05f			fSV_DANSUU_SRV_BAK = 5;				//初期値
			SV_DANSUU_SRV_BAK = 0;				//初期値
			mmon_kaiten_chg();					//回転方式による設定値 切換え

//			mmon_trans_get();					//回転方式によるﾃﾞｰﾀの取得
//
//			SV_TAIKIKAKU_SRV_BAK = SV_TAIKIKAKU_SRV;	//待機角の格納
//			SV_TAIKIPOS_SRV_BAK = SV_TAIKIPOS_SRV;		//待機位置の格納
//
//			SV_DANSUU_SRV_BAK = 5;				//初期値
//			mmon_tchk_disp();					//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示

//V01d			if(GAMEN_NO == 3){		//生産画面　ﾓｰｼｮﾝ設定
			if( (GAMEN_NO == 3) || (GAMEN_NO == 6) ){		//生産画面　ﾓｰｼｮﾝ設定
				INTROCK_DISP_FLG = 0xff;		//ガイダンス表示(00:なし／FF:あり)

//V06n				SEQ_PAR_051 = BIT_0;			//生産画面表示(1:表示中)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//生産画面表示(1:表示中)

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//機能選択3(生産数値設定　1:有)
					SV_CNT = 00;
//V01d					CSR_CNT = 00;
					CSR_CNT = 02;
				}
			}
			else{					//設定画面　ﾓｰｼｮﾝ設定
//V06n				SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

				DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)

				EJE_GAMEN_NON = 0;				//エジェクタ 有
				if(00 == EJE_check()) {			//エジェクタ有無チェック
					EJE_GAMEN_NON = 0xff;		//エジェクタ 無
				}
				MIS_GAMEN_NON = 0;				//ミスフィード 有
				if(00 == MIS_check()){			//ミスフィード有無チェック
					MIS_GAMEN_NON = 0xff;		//ミスフィード 無
				}
				ROT1_GAMEN_NON = 0;				//ロータリカム１～８ 有
				if( 00 == ROT1_check() ) {		//ロータリカム１～８有無チェック
					ROT1_GAMEN_NON = 0xff;		//ロータリカム１～８ 無
				}
				ROT2_GAMEN_NON = 0;				//ロータリカム９～１６ 有
				if( 00 == ROT2_check() ) {		//ロータリカム９～１６有無チェック
					ROT2_GAMEN_NON = 0xff;		//ロータリカム９～１６ 無
				}

				ROT_GAMEN_NON = 0;				//ロータリカム 有
				if(ROT1_GAMEN_NON == 0xff) {	//ロータリカム１～８ 無　？
					if(ROT2_GAMEN_NON == 0xff){	//ロータリカム９～１６ 無　？
						ROT_GAMEN_NON = 0xff;	//ロータリカム 無
					}
				}

				CAM_GAMEN_NON = 0;						//ﾀｲﾐﾝｸﾞ設定 有
				if(EJE_GAMEN_NON == 0xff) {				//エジェクタ 無　？
					if(MIS_GAMEN_NON == 0xff){			//ミスフィード 無　？
						if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
							CAM_GAMEN_NON = 0xff;		//ﾀｲﾐﾝｸﾞ設定 無
							SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
							SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
							Under_grph();				//下段のグラフィックセット
						}
					}
				}
			}
			break;

		case 4:			//生産画面　ｸﾞﾗﾌﾓｰｼｮﾝ
		case 29:		//設定画面　ｸﾞﾗﾌﾓｰｼｮﾝ
			CSR_MOVE_OK_FLG = 0xff;			//ｶｰｿﾙ移動ﾌﾗｸﾞ(00:移動／FF:禁止)
			SW16data_onset(0xff, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			if(GAMEN_NO == 4){		//生産画面　ｸﾞﾗﾌﾓｰｼｮﾝ
				INTROCK_DISP_FLG = 0xff;		//ガイダンス表示(00:なし／FF:あり)
//V06n				SEQ_PAR_051 = BIT_0;			//生産画面表示(1:表示中)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//生産画面表示(1:表示中)

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//機能選択3(生産数値設定　1:有)
					SV_CNT = 00;
					CSR_CNT = 00;
				}
			}
			else{					//設定画面　ｸﾞﾗﾌﾓｰｼｮﾝ
//				SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

				DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)

				if(EJE_GAMEN_NON == 0xff) {				//エジェクタ 無　？
					if(MIS_GAMEN_NON == 0xff){			//ミスフィード 無　？
						if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
							SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
							SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
							Under_grph();				//下段のグラフィックセット
						}
					}
				}
			}
			break;

		case 7:			//段取画面　中型基本
			RULET_DISP_FLG = 0xff;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)
			SEISAN_DISP_FLG = 0xff;			//生産の行程表示(00:なし／FF:あり)
			INTROCK_DISP_FLG = 0xff;		//ガイダンス表示(00:なし／FF:あり)

			RULET_GAMEN_INIT();				//ﾙｰﾚｯﾄ表示の初期化

			CSR_FLG = 0;

			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_1;			//型段取画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_1;			//型段取画面表示(1:表示中)
			break;

		case 8:			//段取画面　中型基本		//V01r
			RULET_DISP_FLG = 0xff;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)
			SEISAN_DISP_FLG = 0xff;			//生産の行程表示(00:なし／FF:あり)
			INTROCK_DISP_FLG = 0xff;		//ガイダンス表示(00:なし／FF:あり)

			RULET_GAMEN_INIT();				//ﾙｰﾚｯﾄ表示の初期化

			CSR_FLG = 0;

			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_1;			//型段取画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_1;			//型段取画面表示(1:表示中)
			break;

		case 12:		//設定画面　ｶﾑ名称設定
		case 26:		//設定画面　ﾛｰﾀﾘｶﾑ名称入力
			NAME_CHG_FLG = 0;						//名称変更中クリア
			CAMNAME_INP_CNT = 0;					//入力カウンタ初期化

			SW16data_onset(0xff, 2);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;			//現在のカーソル位置カウント
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//変更カム名称番号読込
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//カム名称番号読込
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();							//ＳＷデータ情報　表示

			DATA_svsw(SEQ_PAR_101,BIT_0);			//ﾃﾞｰﾀ設定OK(1:OK)
//V06n			SEQ_PAR_051 = BIT_2;					//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			break;

		case 13:		//設定画面　ﾒﾝﾃﾅﾝｽ ﾓﾆﾀ
			CSR_FLG = 0;					//カーソル表示位置指定
			CSR_FLG_CNT = 1;				//カーソル番号セット
			SV_FLG_CNT = 1;					//設定値番号セット
			SW_FLG_CNT = 1;					//ＳＷ番号セット

			SW16data_onset(0xff, 2);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)
			break;

		case 14:		//設定画面　機能選択
			CSR_FLG = 0;					//カーソル表示位置指定
			CSR_FLG_CNT = 1;				//カーソル番号セット
			SV_FLG_CNT = 1;					//設定値番号セット
			SW_FLG_CNT = 1;					//ＳＷ番号セット

			SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)
			break;

		case 15:		//設定画面　型ﾃﾞｰﾀ管理
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)

			MLD_100_FLG = 0;					//型管理 1～10が有効
			if( SEQ_025_SV & BIT_15 ) {			//型ﾃﾞｰﾀ1～100が有効　？
				MLD_100_FLG = 0xaa;				//型管理 1～100が有効
				if ( SEQ_026_SV & BIT_0 ) {		//型ﾃﾞｰﾀ101～200が有効　？		V06n
					MLD_100_FLG = 0xbb;			//型管理 1～200が有効
				}
			}
												//カーソル表示位置制御
			if(CSR_POS_G15 == 0xff){			//型データ管理画面のカーソル表示位置は現在の型データの場所
				CSR_FLG = 5;					//カーソル表示位置指定
				i = PV_MLDNO1_F1;				//現在の型番号

//V06n				if(MLD_100_FLG != 0xaa){		//型管理 1～100が有効？
				if(MLD_100_FLG == 0){			//型管理 1～10が有効？
					if( i > 10 ) {
						i = 1;
					}
				}
				else if(MLD_100_FLG == 0xaa) {	//型管理 1～100が有効？		V06n
					if( i > 100 || i == 0 ) {
						i = 1;
					}
				}
				else if(MLD_100_FLG == 0xbb) {	//型管理 1～200が有効？		V06n
					if( i > 200 || i == 0 ) {
						i = 1;
					}
				}
				j = (i % 10);
				i /= 10;
				if(j == 0){
					j = 10;
					i -= 1;
				}
				CSR_FLG_CNT = (j << 1);
				MLD_100_GNO = i;
			}
			else if(CSR_POS_G15 == 0xaa){
				CSR_FLG = 5;					//カーソル表示位置指定
				j = (PV_SEARCH_C15 % 10);		//型番号検索ナンバー読込
				if(j == 0){
					j = 10;
				}
				CSR_FLG_CNT = (j << 1);
			}
			else if(CSR_POS_G15 == 0x55){		//名称登録画面から戻って来た時用
				CSR_FLG = 5;					//カーソル表示位置指定
				j = (PV_MLDNO1_F0 % 10);
				if(j == 0){
					j = 10;
				}
				CSR_FLG_CNT = (j << 1);
			}
			else{
				CSR_FLG = 5;				//カーソル表示位置指定
				CSR_FLG_CNT = 2;			//カーソル番号セット
			}

											//MLD100 型管理番号表示データ作成
			i = (MLD_100_GNO * 10);
			i ++;
			ktop = i;						//V06p(INS)
			PV_MLNO01_C15 = i++;			//型管理実測データ
			PV_MLNO02_C15 = i++;			//型管理実測データ
			PV_MLNO03_C15 = i++;			//型管理実測データ
			PV_MLNO04_C15 = i++;			//型管理実測データ
			PV_MLNO05_C15 = i++;			//型管理実測データ
			PV_MLNO06_C15 = i++;			//型管理実測データ
			PV_MLNO07_C15 = i++;			//型管理実測データ
			PV_MLNO08_C15 = i++;			//型管理実測データ
			PV_MLNO09_C15 = i++;			//型管理実測データ
			PV_MLNO10_C15 = i;				//型管理実測データ


			mot_type_SWset(ktop);			//モーションTYPE用SWセット


			PV_MLDMES_C1 = 0;
			SWchg_disp();					//ＳＷデータ情報　表示


			if(MLD_100_GNO == 0){
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)

//V06n				if(MLD_100_FLG != 0xaa){		//型管理 1～100が有効？
				if(MLD_100_FLG == 0){			//型管理 1～100が有効？
					SW56_dncara_disp(0xff, 3);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
					SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				}
			}
//V06n			else if(MLD_100_GNO == 9){
			else if ( ( (MLD_100_FLG == 0xaa) && (MLD_100_GNO == 9) ) || 
					  ( (MLD_100_FLG == 0xbb) && (MLD_100_GNO ==19) ) ) {
				SW56_dncara_disp(0xff, 3);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
			}
			Under_grph();						//下段のグラフィックセット
			break;

		case 16:		//設定画面　型ﾃﾞｰﾀ名称設定
		case 23:		//設定画面　ﾒﾓ名称入力画面
			NAME_CHG_FLG = 0;				//名称変更中クリア
			CAMNAME_INP_CNT = 0;			//入力カウンタ初期化

			CSR_FLG = 5;					//カーソル表示位置指定
			CSR_FLG_CNT = 2;				//カーソル番号セット

			SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)
			break;

		case 17:		//設定画面　ﾃﾞｰﾀ設定中型
			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;		//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			DATA_svsw(SEQ_PAR_101,BIT_0);		//ﾃﾞｰﾀ設定OK(1:OK)

			if(0==(SEQ_PAR_107 & BIT_0)){		//機能選択1(型ﾃﾞｰﾀ管理　1:有)
												//ＳＷ３上
				SW56_dncara_disp(0xff, 03);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
												//ＳＷ３下
				SW56_dncara_disp(0xff, 11);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();					//下段のグラフィックセット
			}

			SEL_GAMEN_NON = 0;
			i = SEQ_019_SV & 0xeaa0;
			i |= SEQ_018_SV & BIT_7;			//ｺｲﾙﾗｲﾝ設定(1=有)
			i |= SEQ_020_SV & BIT_0;			//ﾀﾞｲｸｯｼｮﾝ圧力調整選択(1=有)
/**************	V03a 上型ｸﾗﾝﾊﾟ６選択追加	*********************/
//			i |= SEQ_021_SV & BIT_1;
/***************************************************************************/
			if( i == 0 ){
				SEL_GAMEN_NON = 0xff;
				SW56_dncara_disp(0xff, 1);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 9);		//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();					//下段のグラフィックセット
			}
			MLD_100_GNO = 0;					//型管理画面番号初期化
			MLD_100_FLG = 0;					//型管理フラグ初期化
			break;

		case 19:		//設定画面　ｴｼﾞｪｸﾀ／自動化ｶﾑ設定
			GAMEN_NO_CAM = 19;			//前回データ有り

			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)

			if(MIS_GAMEN_NON == 0xff){		//ミスフィード 無　？
				SW56_dncara_disp(0xff, 03);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
				SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 20:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ設定
			GAMEN_NO_CAM = 20;

			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			DATA_svsw(SEQ_PAR_101,BIT_0);		//ﾃﾞｰﾀ設定OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//エジェクタ 無　？
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
				SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 21:		//設定画面　ﾛｰﾀﾘｶﾑ1～8ｶﾑ設定
			GAMEN_NO_CAM = 21;

			NAME_CHG_FLG = 0;			//名称変更中クリア
			CAMNAME_INP_CNT = 0;		//入力カウンタ初期化

			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//変更カム名称番号読込
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//カム名称番号読込
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();								//ＳＷデータ情報　表示

			DATA_svsw(SEQ_PAR_101,BIT_0);				//ﾃﾞｰﾀ設定OK(1:OK)

//V06n			SEQ_PAR_051 = BIT_2;						//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			if(EJE_GAMEN_NON == 0xff) {		//エジェクタ 無　？
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(MIS_GAMEN_NON == 0xff){		//ミスフィード 無　？
				SW56_dncara_disp(0xff, 03);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 22:		//設定画面　ﾛｰﾀﾘｶﾑ9～16ｶﾑ設定
			GAMEN_NO_CAM = 22;

			NAME_CHG_FLG = 0;			//名称変更中クリア
			CAMNAME_INP_CNT = 0;		//入力カウンタ初期化

			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//変更カム名称番号読込
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//カム名称番号読込
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//カム名称を入れておく

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();								//ＳＷデータ情報　表示

			DATA_svsw(SEQ_PAR_101,BIT_0);		//ﾃﾞｰﾀ設定OK(1:OK)

//V06n			SEQ_PAR_051 = BIT_2;				//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			if(EJE_GAMEN_NON == 0xff) {		//エジェクタ 無　？
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(MIS_GAMEN_NON == 0xff){		//ミスフィード 無　？
				SW56_dncara_disp(0xff, 03);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 31:		//ｼｽﾃﾑ設定　画面
			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			//画面ﾊﾞｰｼﾞｮﾝ：表示数=4(ASCIIﾃﾞｰﾀ)
			wk[0] = E_CPUC_VER1;								//CPU-C VER. No.
			wk[1] = E_CPUC_VER2;								//CPU-C VER. No.
			wk[2] = E_CPUC_VER3;								//CPU-C VER. No.
			wk[3] = E_CPUC_VER4;								//CPU-C VER. No.
			memcpy_word(&PV_GMNVER_A1[0], (UNs *)&wk[0], 2);	//画面ﾊﾞｰｼﾞｮﾝをｺﾋﾟｰ

			//ｼｽﾊﾟﾗ･ﾊﾞｰｼﾞｮﾝ：表示数=2(ASCIIﾃﾞｰﾀ)(ROM　ｼｰｹﾝｽ･ﾊﾟﾗﾒｰﾀにて決定)
			//PV_SYSVER_A1       .SRES        2           ; シスパラ　バージョン
			memset_word(&PV_SYSVER_A1, E_AS_SPSP, 1);

			//CPU-A C/Bﾊﾞｰｼﾞｮﾝ：表示数=6(ASCIIﾃﾞｰﾀ)
			//PV_CBAVER_A1       .SRES        6           ; ＣＰＵ－Ａ　バージョン
			wk[0] = PVP_CB_A_VER[0];							//CPU-A VER. No.
			wk[1] = PVP_CB_A_VER[1];
			wk[2] = PVP_CB_A_VER[2];
			wk[3] = PVP_CB_A_VER[3];
			wk[4] = PVP_CB_A_VER[4];
			wk[5] = PVP_CB_A_VER[5];
			memcpy_word(&PV_CBAVER_A1[0], (UNs *)&wk[0], 3);	//画面ﾊﾞｰｼﾞｮﾝをｺﾋﾟｰ

			//CPU-B C/Bﾊﾞｰｼﾞｮﾝ：表示数=6(ASCIIﾃﾞｰﾀ)
			//PV_CBBVER_A1       .SRES        6           ; ＣＰＵ－Ｂ　バージョン
			wk[0] = PVP_CB_B_VER[0];							//CPU-B VER. No.
			wk[1] = PVP_CB_B_VER[1];
			wk[2] = PVP_CB_B_VER[2];
			wk[3] = PVP_CB_B_VER[3];
			wk[4] = PVP_CB_B_VER[4];
			wk[5] = PVP_CB_B_VER[5];
			memcpy_word(&PV_CBBVER_A1[0], (UNs *)&wk[0], 3);	//画面ﾊﾞｰｼﾞｮﾝをｺﾋﾟｰ

			//ｵﾌﾟｼｮﾝ･ﾊﾞｰｼﾞｮﾝ：表示数=2(HEXﾃﾞｰﾀ)
			PV_OPCVER_A1[0] = OP_VER;								//Option Ver

			//初期値ﾊﾞｰｼﾞｮﾝ：表示数=2(HEXﾃﾞｰﾀ)		V06
			bf_p = &SV_SEQDT1_A91_INI;
			bf_p += INIT_DAT_OFS/2;
			PV0_DEFULT_VER1 = *bf_p;

			//ｲﾝﾀｰﾛｯｸﾊﾞｰｼﾞｮﾝ：表示数=2(HEXﾃﾞｰﾀ)		V06
			bf_p = &SV_INTER_VER1;
			bf_p += INTR_DAT_OFS/2;
			PV0_INTER_VER1 = *bf_p;

			//末尾のﾊﾞｰｼﾞｮﾝｷｬﾗｸﾀ：表示数=1(ASCIIﾃﾞｰﾀ)
			PV0_PAR_A_CHAR = PVP_PAR_A_CHAR << 8;
			PV0_PAR_B_CHAR = PVP_PAR_B_CHAR << 8;
			PV0_TBL_A_CHAR = PVP_TBL_A_CHAR << 8;
			PV0_TBL_B_CHAR = PVP_TBL_B_CHAR << 8;
			PV0_SEQ_VER2 = SEQ_PAR_198 << 8;

//V06			PV0_DEFULT_VER2 = SV_SEQDT2_A91_INI << 8;
			bf_p = &SV_SEQDT2_A91_INI;
			bf_p += INIT_DAT_OFS/2;
			PV0_DEFULT_VER2 = *bf_p << 8;

//V06			PV0_INTER_VER2 = SV_INTER_VER2 << 8;
			bf_p = &SV_INTER_VER2;
			bf_p += INTR_DAT_OFS/2;
			PV0_INTER_VER2 = *bf_p << 8;

			//ｵﾌﾟｼｮﾝET1ﾊﾞｰｼﾞｮﾝ：表示数=4(ASCIIﾃﾞｰﾀ)				//V05
			if(MEM_ARI == 0xA5) {							//OPｱﾘ(OK):A5H
				wk[0] = ET1_VER[0];							//CPU-B VER. No.
				wk[1] = ET1_VER[1];
				wk[2] = ET1_VER[2];
				wk[3] = ET1_VER[3];
			}
			else{
				wk[0] = 0x20;							//CPU-B VER. No.
				wk[1] = 0x20;
				wk[2] = 0x20;
				wk[3] = 0x20;
			}
			memcpy_word(&PV_ET1VER_A1[0], (UNs *)&wk[0], 2);	//画面ﾊﾞｰｼﾞｮﾝをｺﾋﾟｰ

			break;

		case 32:		//ｼｽﾃﾑ設定　仕様設定1
		case 33:		//ｼｽﾃﾑ設定　仕様設定2
		case 34:		//ｼｽﾃﾑ設定　仕様設定3
		case 35:		//ｼｽﾃﾑ設定　仕様設定4
		case 36:		//ｼｽﾃﾑ設定　仕様設定5
		case 37:		//ｼｽﾃﾑ設定　仕様設定6
		case 38:		//ｼｽﾃﾑ設定　C/Bｼｽﾃﾑ定数
		case 39:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1
		case 40:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ2
		case 41:		//ｼｽﾃﾑ設定　ｼｽﾃﾑｶﾑ設定
		case 43:		//ｼｽﾃﾑ設定　内部ｶﾑ･ﾀｲﾏ設定
		case 44:		//ｼｽﾃﾑ設定　荷重計設定
		case 45:		//ｼｽﾃﾑ設定　ｽﾗｲﾄﾞ自動設定
		case 47:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(左)	V01j
		case 48:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(右)	V01j
		case 49:		//ｼｽﾃﾑ画面　圧力調節設定			V01j
		case 50:		//ｼｽﾃﾑ設定　ﾊﾞｯｸｱｯﾌﾟﾃﾞｰﾀ設定
		case 51:		//ｼｽﾃﾑ設定　C/Bｼｽﾃﾑ定数2
		case 55:		//ｼｽﾃﾑ画面　仕様設定7
		case 56:		//ｼｽﾃﾑ画面　仕様設定8
		case 57:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ3
		case 58:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ4
		case 59:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ5
		case 60:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ6
		case 61:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ7		//V01v

		case 62:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8		//2012-03-28 copy,h2w V05
		case 63:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9		//2012-03-28 copy,h2w V05
		case 64:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ10	//2012-03-28 copy,h2w V05
		case 103:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀB		//2012-03-28 copy,h2w V06
		case 106:		//ｼｽﾃﾑ画面　仕様設定9		//V06m
		case 107:		//ｼｽﾃﾑ画面　仕様設定10		//V06m
			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			DATA_svsw(SEQ_PAR_101,BIT_1);	//ｼｽﾃﾑ設定OK(1:OK)
			break;

		case 52:		//ｼｽﾃﾑ設定　ﾃﾞｰﾀ初期化
			NAME_CHG_FLG = 0;				//名称変更中クリア
			CAMNAME_INP_CNT = 0;			//入力カウンタ初期化

			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//ﾃﾞｰﾀ設定OK(1:OK)
//			if(MLD_100_CARD_FLG != 0xaa){	//外部メモリ有り？
//											//SW5下
				SW56_dncara_disp(0xff, 7);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
//			}
			break;

		/* V01d */
		case 68:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ設定5～8
			GAMEN_NO_CAM = 68;

			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 3);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 5);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 6);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			DATA_svsw(SEQ_PAR_101,BIT_0);		//ﾃﾞｰﾀ設定OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//エジェクタ 無　？
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
				SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 66:		//生産画面　トレンド			//V01z
		case 104:		//生産画面　トレンド			//V06l
			SW16data_onset(0xff, 3);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;
		case 67:		//生産画面　サンプリング		//V01z
		case 105:		//生産画面　サンプリング		//V06l
			SW16data_onset(0xff, 2);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 9:			//生産画面　サンプリング波形	//V05o
			SW16data_onset(0xff, 4);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;
		case 10:		//生産画面　ドレンド波形		//V05o
			SW16data_onset(0xff, 9);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 101:		//データ設定画面　加振機能設定	//V05r
			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 9);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

//V06n			SEQ_PAR_051 = BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//ﾃﾞｰﾀ設定画面表示(1:表示中)

			DATA_svsw(SEQ_PAR_101,BIT_0);		//ﾃﾞｰﾀ設定OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//エジェクタ 無　？
				SW56_dncara_disp(0xff, 2);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 10);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(MIS_GAMEN_NON == 0xff){		//ミスフィード 無　？
				SW56_dncara_disp(0xff, 03);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56上段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff, 11);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			if(ROT_GAMEN_NON == 0xff) {		//ロータリカム 無　？
				SW56_dncara_disp(0xff, 4);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				SW56_dncara_disp(0xff,12);	//SW56下段ｷｬﾗｸﾀをSW領域へ格納(SW56下段ｷｬﾗｸﾀ,表示位置)
				Under_grph();				//下段のグラフィックセット
			}
			break;

		case 102:		//生産画面　電力モニタ	//V06
			CSR_FLG = 0;				//カーソル表示位置指定
			CSR_FLG_CNT = 1;			//カーソル番号セット
			SV_FLG_CNT = 1;				//設定値番号セット
			SW_FLG_CNT = 1;				//ＳＷ番号セット

			SW16data_onset(0xff, 9);					//SW1～6の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)

			break;
	}
}


/*
********************************************************************************
*  Module Name:		WIN_disp_after
*  Function Name:	ｳｲﾝﾄﾞｳ画面表示の後処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
void	WIN_disp_after(void)
{
	UNs		i;

	switch(WINDOW_NO) {
		default:
//V01r		case 1:			//生産画面　生産設定
//V01r		case 8:			//段取画面　ﾀﾞｲｸｯｼｮﾝ調整
//V01r		case 9:			//段取画面　ﾀﾞｲｸｯｼｮﾝ圧力調整
//V01j		case 12:		//段取画面　ｽﾃｯﾌﾟﾓﾆﾀ
//V01r		case 13:		//段取画面　ﾀﾞｲｸｯｼｮﾝ操作
//V01r		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作
//V01r		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認
//V01r		case 16:		//段取画面　ﾀﾞｲｸｯｼｮﾝ調節操作
//V01r		case 17:		//段取画面　ﾀﾞｲｸｯｼｮﾝ自動調節確認
//V01r		case 18:		//段取画面　MB選択操作
			break;

		case 1:			//生産画面　生産設定				//V01r
		case 8:			//段取画面　ﾀﾞｲｸｯｼｮﾝ調整			//V01r
		case 9:			//段取画面　ﾀﾞｲｸｯｼｮﾝ圧力調整		//V01r
		case 13:		//段取画面　ﾀﾞｲｸｯｼｮﾝ操作			//V01r
		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作			//V01r
		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認		//V01r
		case 16:		//段取画面　ﾀﾞｲｸｯｼｮﾝ調節操作		//V01r
		case 17:		//段取画面　ﾀﾞｲｸｯｼｮﾝ自動調節確認	//V01r
		case 18:		//段取画面　MB選択操作				//V01r
		case 02:		//生産画面　輝度設定
		case 03:		//生産画面　ｶﾞｲﾀﾞﾝｽ表示
		case 04:		//生産画面　ｼｰｹﾝｽﾁｪｯｸ
		case 05:		//生産画面　生産設定中型
		case 07:		//段取画面　ﾊﾞﾗﾝｻ圧力調整
		case 10:		//段取画面　ｶﾞｲﾀﾞﾝｽ表示
		case 11:		//段取画面　ｼｰｹﾝｽﾁｪｯｸ
		case 19:		//生産画面　生産設定2
		case 21:		//生産画面　制動試験WIN				//V06
			RULET_DISP_FLG = 0x55;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)
			break;

		case 06:		//段取画面　ｽﾗｲﾄﾞ調節
			RULET_DISP_FLG = 0x55;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)

			i = SEQ_019_SV & 0x0550;		//上型クランパから防護柵までの選択項目チェック
			i |= SEQ_020_SV & BIT_1;
			SW14_DISP7_DANNON = i;
			break;

		case 12:	/*V01j*/	//段取画面　ｽﾃｯﾌﾟﾓﾆﾀ
			RULET_DISP_FLG = 0x55;			//ルーレット表示(00:なし／55:ｳｨﾝﾄﾞｳ表示／FF:通常表示)	V01r
			DEG_DISP_FLG = 0xff;			//角度表示フラグ(00:なし／FF:あり)						V01r

			ADC_STEP_NO_LAST[0] = 0xffff;
			ADC_STEP_NO_LAST[1] = 0xffff;
			ADC_STEP_NO_LAST[2] = 0xffff;
			ADC_STEP_NO_LAST[3] = 0xffff;
			break;
	}
}


/*
********************************************************************************
*  Module Name:		WIN_disp_after2(旧:WIN_DISP_AFTER_A)
*  Function Name:	ｳｲﾝﾄﾞｳ画面表示の後処理2
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
void	WIN_disp_after2(void)
{
	UNs		*Dst_p, dot_d, i;
	UNi		cnt;

	switch(WINDOW_NO) {
		default:
		case 1:			//生産画面　生産設定
//V01j		case 8:			//段取画面　ﾀﾞｲｸｯｼｮﾝ調整
//V01j		case 9:			//段取画面　ﾀﾞｲｸｯｼｮﾝ圧力調整
//V01j		case 12:		//段取画面　ｽﾃｯﾌﾟﾓﾆﾀ
//V01j		case 13:		//段取画面　ﾀﾞｲｸｯｼｮﾝ操作
//V01j		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作
//V01j		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認
//V01j		case 16:		//段取画面　ﾀﾞｲｸｯｼｮﾝ調節操作
//V01j		case 17:		//段取画面　ﾀﾞｲｸｯｼｮﾝ自動調節確認
//V01j		case 18:		//段取画面　MB選択操作
			break;

		case 2:			//生産画面　輝度設定
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 3:			//生産画面　ｶﾞｲﾀﾞﾝｽ表示
		case 10:		//段取画面　ｶﾞｲﾀﾞﾝｽ表示
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 4:			//生産画面　ｼｰｹﾝｽﾁｪｯｸ
			if(SEQ_025_SV & BIT_14) {			//shima
				SW56_dncara_disp(64, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納
			}
		case 11:		//段取画面　ｼｰｹﾝｽﾁｪｯｸ
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 5:			//生産画面　生産設定中型
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {		//機能選択3(生産数値設定　1:有)
				SV_CNT = 00;
				for(i=0 ; i < 12 ; i++){			//生産設定禁止だったらＳＶカウントＭＡＸを０にする
													//これをやらないと二回押さないと右に移動しない
					CSR_buff[i].SV_MAX = 0x00;		//設定値ﾃｰﾌﾞﾙ個数
				}
			}
//V01l			if(00 == EJE_check()) {					//エジェクタ有無チェック
			if( (00 == EJE_check() ) &&
					(00 == SEQ_016_SV & BIT_2) ) {	//エジェクタ有無チェック
				CSR_CNT = 00;						//エジェクタ 無
			}
			SW16data_onset(0xff, 02);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);				//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 6:			//段取画面　ｽﾗｲﾄﾞ調節
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//機能選択4(段取数値設定　1:有)
				SV_CNT = 00;
			}
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 7:			//段取画面　ﾊﾞﾗﾝｻ圧力調整
		case 8:			//段取画面　ﾀﾞｲｸｯｼｮﾝ調整			/* V01j */
		case 9:			//段取画面　ﾀﾞｲｸｯｼｮﾝ圧力調整		/* V01j */
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//機能選択4(段取数値設定　1:有)
				SV_CNT = 00;
			}
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 12:		//段取画面　ｽﾃｯﾌﾟﾓﾆﾀ				/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 13:		//段取画面　ﾀﾞｲｸｯｼｮﾝ操作			/* V01j */
		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作			/* V01j */
		case 16:		//段取画面　ﾀﾞｲｸｯｼｮﾝ調節操作		/* V01j */
		case 18:		//段取画面　MB選択操作				/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			ADC_SW2_DISP();
			break;

		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認		/* V01j */
		case 17:		//段取画面　ﾀﾞｲｸｯｼｮﾝ自動調節確認	/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 03);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0x00, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//機能選択4(段取数値設定　1:有)
				SV_CNT = 00;
			}
			ADC_SW2_DISP();
			break;

		case 19:		//生産画面　生産設定2
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {		//機能選択3(生産数値設定　1:有)
				SV_CNT = 00;
			}
//V01l			if(00 == MIS_check()){					//ミスフィード有無チェック
			if( (00 == MIS_check() ) &&
					(00 == SEQ_016_SV & BIT_2) ) {	//ミスフィード有無チェック
				CSR_CNT = 00;						//ミスフィード 無
			}
			SW16data_onset(0xff, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 20:		//生産画面　補正モニタ		/* V01w */
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//機能選択3(生産数値設定　1:有)		//V05g
				SV_CNT = 00;
				CSR_CNT = 00;
			}
			SW16data_onset(0x00, 02);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xFF, 04);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 05);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			SW16data_onset(0xff, 06);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 22:		//データ設定画面　ｶｳﾝﾄ値修正	/* V06b */
			SW16data_onset(0xff, 9);		//ＳＷ１～６の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

		case 23:		//生産画面　生産管理		/* V06c */
		case 51:		//生産画面　作業開始0		/* V06c */
		case 52:		//生産画面　作業開始1		/* V06c */
		case 53:		//生産画面　作業開始2		/* V06c */
		case 54:		//生産画面　作業開始3		/* V06c */
		case 55:		//生産画面　作業開始4		/* V06c */
		case 56:		//生産画面　作業開始5		/* V06c */
		case 57:		//生産画面　作業開始6		/* V06c */
		case 58:		//生産画面　作業終了0		/* V06c */
			SW16data_onset(0xff, 3);		//ＳＷ３の反転指定を行う(ﾊﾟﾀｰﾝﾃﾞｰﾀ,SW位置)
			break;

	}

	if(WINDOW_NO < 6 || (WINDOW_NO != 20 && WINDOW_NO >= 10) ){	//段取りウインドウ？
		Dst_p = &LCD_WORK1[6][0][0];				//裏画面ウインドウの上段の枠を書く
		dot_d = 0x00ff;								//ドットパターンセット
		cnt = E_line;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}
	}
	else{
		Dst_p = &LCD_WORK1[6][0][0];				//裏画面ウインドウの上段の枠を書く
		dot_d = 0x00ff;								//ドットパターンセット
		cnt = 23;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}

		Dst_p = &LCD_WORK1[6][0][22];				//段取りウインドウの縦枠を書く
		dot_d = BIT_0;								//ドットパターンセット
		cnt = 16*7;
		while(cnt--) {
			*Dst_p |= dot_d;
			Dst_p += E_next_dot;					//1文字の次dot位置数
		}
	}
}


/*
********************************************************************************
*  Module Name:		Alltbl_set
*  Function Name:	情報ﾃｰﾌﾞﾙの作成
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙを作成する
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
void	Alltbl_set(void)
{
CSR_TBL_TDEF	*csr_tp, *csr_p, *d1_p;
SV_TBL_TDEF		*sv_tp, *sv_p, *d2_p;
PV_TBL_TDEF		*pv_tp, *pv_p, *d3_p;
SW_TBL_TDEF		*sw_tp, *sw_p, *d4_p;
UNl		cnt, i;


	csr_tp = CSTBL_Adr_tbl[GAMEN_NO];				//各画面の情報ﾃｰﾌﾞﾙのｱﾄﾞﾚｽを取得
	cnt = *CSCOUNT_Adr_tbl[GAMEN_NO];				//カーソルカウンタ
	CSR_CNT1 = CSR_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d1_p = &CSR_buff[i];						//格納ポインタセット
		csr_p = &csr_tp[i];							//格納ポインタセット

		d1_p->XY_POS = csr_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d1_p->DATA_NO = csr_p->DATA_NO;				//ｶｰｿﾙ種別番号
		d1_p->SV_MAX = csr_p->SV_MAX;				//設定値ﾃｰﾌﾞﾙ個数
		d1_p->SW_MAX = csr_p->SW_MAX;				//SWﾃｰﾌﾞﾙ個数
		d1_p->CARA_NO = csr_p->CARA_NO;				//ｶｰｿﾙ表示ｷｬﾗ種別（未使用）
		d1_p->MOVE_NO = csr_p->MOVE_NO;				//画面移動番号
		d1_p->TOK_NO = csr_p->TOK_NO;				//特殊番号(B0:ｶｰｿﾙ無し)
		d1_p->YOBI1 = csr_p->YOBI1;					//予備１
		d1_p->YOBI2 = csr_p->YOBI2;					//予備２
		d1_p->SW56_UP = csr_p->SW56_UP;				//SW56上段ｷｬﾗｸﾀ
		d1_p->SW5_DN = csr_p->SW5_DN;				//SW5下段ｷｬﾗｸﾀ
		d1_p->SW6_DN = csr_p->SW6_DN;				//SW6下段ｷｬﾗｸﾀ
		d1_p->SW5_SUB = csr_p->SW5_SUB;				//SW5ﾃﾞｰﾀ処理番号
		d1_p->SW6_SUB = csr_p->SW6_SUB;				//SW6ﾃﾞｰﾀ処理番号
		d1_p->YOBI3 = csr_p->YOBI3;					//予備３
		d1_p->AKI = csr_p->AKI;						//空き
		i++;
	}

	sv_tp = SVTBL_Adr_tbl[GAMEN_NO];
	cnt = *SVCOUNT_Adr_tbl[GAMEN_NO];				//カーソルカウンタ
	SV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d2_p = &SV_buff[i];							//格納ポインタセット
		sv_p = &sv_tp[i];							//格納ポインタセット

		d2_p->XY_POS = sv_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d2_p->AKI = sv_p->AKI;						//空き
		d2_p->DATA_ADR = sv_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d2_p->SUB_NO = sv_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d2_p->GRP_NO = sv_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d2_p->TOK_FLG = sv_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d2_p->BYTE_NO = sv_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d2_p->TEN_POS = sv_p->TEN_POS;				//少数点の位置
		d2_p->CSR_NO = sv_p->CSR_NO;				//ｶｰｿﾙ認識番号
		d2_p->DSP_NO = sv_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
		d2_p->SAVE_NO = sv_p->SAVE_NO;				//格納ﾌﾗｸﾞ
		d2_p->YOBI_NO = sv_p->YOBI_NO;				//予備
		d2_p->AKI2 = sv_p->AKI2;					//空き
		i++;
	}

	pv_tp = PVTBL_Adr_tbl[GAMEN_NO];
	cnt = *PVCOUNT_Adr_tbl[GAMEN_NO];				//カーソルカウンタ
	PV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d3_p = &PV_buff[i];							//格納ポインタセット
		pv_p = &pv_tp[i];							//格納ポインタセット

		d3_p->XY_POS = pv_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d3_p->AKI = pv_p->AKI;						//空き
		d3_p->DATA_ADR = pv_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d3_p->SUB_NO = pv_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d3_p->GRP_NO = pv_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d3_p->TOK_FLG = pv_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d3_p->BYTE_NO = pv_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d3_p->TEN_POS = pv_p->TEN_POS;				//少数点の位置
		d3_p->YOBI1 = pv_p->YOBI1;					//予備１
		d3_p->YOBI2 = pv_p->YOBI2;					//予備２
		d3_p->AKI2 = pv_p->AKI2;					//空き
		i++;
	}

	sw_tp = SWTBL_Adr_tbl[GAMEN_NO];
	cnt = *SWCOUNT_Adr_tbl[GAMEN_NO];				//カーソルカウンタ
	SW_CNT1 = SW_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d4_p = &SW_buff[i];							//格納ポインタセット
		sw_p = &sw_tp[i];							//格納ポインタセット

		d4_p->XY_POS = sw_p->XY_POS;				//ｶｰｿﾙのX,Y軸
		d4_p->AKI = sw_p->AKI;						//空き
		d4_p->DATA_ADR = sw_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d4_p->SUB_NO = sw_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d4_p->GRP_NO = sw_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d4_p->TOK_FLG = sw_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d4_p->CHG_NO = sw_p->CHG_NO;				//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
		d4_p->CSR_NO = sw_p->CSR_NO;				//この設定値の属するｶｰｿﾙ認識番号
		d4_p->DSP_NO = sw_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
		d4_p->CARA_NO = sw_p->CARA_NO;				//ｶｰｿﾙ表示ｷｬﾗ種別
		d4_p->KAN_NO = sw_p->KAN_NO;				//関連ﾊﾞｲﾄ
		d4_p->KAN_ADR = sw_p->KAN_ADR;				//関連ｱﾄﾞﾚｽ
		d4_p->SAVE_NO = sw_p->SAVE_NO;				//格納ﾌﾗｸﾞ
		d4_p->YOBI2 = sw_p->YOBI2;					//予備２
		i++;
	}

	Disp_data_set();								//情報ﾃｰﾌﾞﾙの非表示処理(作成)
}
#else
void	Alltbl_set(void)
{
	Gamenn_CSRtbl_set();
	Gamenn_SVtbl_set();
	Gamenn_PVtbl_set();
	Gamenn_SWLtbl_set();
	Disp_data_set();								//情報ﾃｰﾌﾞﾙの非表示処理(作成)
}
#endif

/*
********************************************************************************
*  Module Name:		Wintbl_set
*  Function Name:	ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの作成
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙを作成する
*
*  履 歴	:FIT)田端		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
void	Wintbl_set(void)
{
CSR_TBL_TDEF	*csr_tp, *csr_p, *d1_p;
SV_TBL_TDEF		*sv_tp, *sv_p, *d2_p;
PV_TBL_TDEF		*pv_tp, *pv_p, *d3_p;
SW_TBL_TDEF		*sw_tp, *sw_p, *d4_p;
UNl		cnt, i;


	csr_tp = CSTBL_Win_Adr_tbl[WINDOW_NO];				//各画面の情報ﾃｰﾌﾞﾙのｱﾄﾞﾚｽを取得
	cnt = *CSCOUNT_Win_Adr_tbl[WINDOW_NO];				//カーソルカウンタ
	CSR_CNT1 = CSR_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d1_p = &CSR_buff[i];						//格納ポインタセット
		csr_p = &csr_tp[i];							//格納ポインタセット

		d1_p->XY_POS = csr_p->XY_POS + 6;			//ｶｰｿﾙのX,Y軸 (表示行数をウインドウ画面に会わせる)
		d1_p->DATA_NO = csr_p->DATA_NO;				//ｶｰｿﾙ種別番号
		d1_p->SV_MAX = csr_p->SV_MAX;				//設定値ﾃｰﾌﾞﾙ個数
		d1_p->SW_MAX = csr_p->SW_MAX;				//SWﾃｰﾌﾞﾙ個数
		d1_p->CARA_NO = csr_p->CARA_NO;				//ｶｰｿﾙ表示ｷｬﾗ種別（未使用）
		d1_p->MOVE_NO = csr_p->MOVE_NO;				//画面移動番号
		d1_p->TOK_NO = csr_p->TOK_NO;				//特殊番号(B0:ｶｰｿﾙ無し)
		d1_p->YOBI1 = csr_p->YOBI1;					//予備１
		d1_p->YOBI2 = csr_p->YOBI2;					//予備２
		d1_p->SW56_UP = csr_p->SW56_UP;				//SW56上段ｷｬﾗｸﾀ
		d1_p->SW5_DN = csr_p->SW5_DN;				//SW5下段ｷｬﾗｸﾀ
		d1_p->SW6_DN = csr_p->SW6_DN;				//SW6下段ｷｬﾗｸﾀ
		d1_p->SW5_SUB = csr_p->SW5_SUB;				//SW5ﾃﾞｰﾀ処理番号
		d1_p->SW6_SUB = csr_p->SW6_SUB;				//SW6ﾃﾞｰﾀ処理番号
		d1_p->YOBI3 = csr_p->YOBI3;					//予備３
		d1_p->AKI = csr_p->AKI;						//空き
		i++;
	}

	sv_tp = SVTBL_Win_Adr_tbl[WINDOW_NO];
	cnt = *SVCOUNT_Win_Adr_tbl[WINDOW_NO];				//カーソルカウンタ
	SV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d2_p = &SV_buff[i];							//格納ポインタセット
		sv_p = &sv_tp[i];							//格納ポインタセット

		d2_p->XY_POS = sv_p->XY_POS + 6;			//ｶｰｿﾙのX,Y軸 (表示行数をウインドウ画面に会わせる)
		d2_p->AKI = sv_p->AKI;						//空き
		d2_p->DATA_ADR = sv_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d2_p->SUB_NO = sv_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d2_p->GRP_NO = sv_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d2_p->TOK_FLG = sv_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d2_p->BYTE_NO = sv_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d2_p->TEN_POS = sv_p->TEN_POS;				//少数点の位置
		d2_p->CSR_NO = sv_p->CSR_NO;				//ｶｰｿﾙ認識番号
		d2_p->DSP_NO = sv_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
		d2_p->SAVE_NO = sv_p->SAVE_NO;				//格納ﾌﾗｸﾞ
		d2_p->YOBI_NO = sv_p->YOBI_NO;				//予備
		d2_p->AKI2 = sv_p->AKI2;					//空き
		i++;
	}

	pv_tp = PVTBL_Win_Adr_tbl[WINDOW_NO];
	cnt = *PVCOUNT_Win_Adr_tbl[WINDOW_NO];				//カーソルカウンタ
	PV_CNT = (UNs)cnt;
	i = 0;
//	if(GAMEN_NO == 1){
//		PV_CNT++;
//		i++;
//	}
	while( cnt-- ) {
		d3_p = &PV_buff[i];							//格納ポインタセット
		pv_p = &pv_tp[i];							//格納ポインタセット

		d3_p->XY_POS = pv_p->XY_POS + 6;			//ｶｰｿﾙのX,Y軸(表示行数をウインドウ画面に会わせる)
		d3_p->AKI = pv_p->AKI;						//空き
		d3_p->DATA_ADR = pv_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
		d3_p->SUB_NO = pv_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
		d3_p->GRP_NO = pv_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
		d3_p->TOK_FLG = pv_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
		d3_p->BYTE_NO = pv_p->BYTE_NO;				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		d3_p->TEN_POS = pv_p->TEN_POS;				//少数点の位置
		d3_p->YOBI1 = pv_p->YOBI1;					//予備１
		d3_p->YOBI2 = pv_p->YOBI2;					//予備２
		d3_p->AKI2 = pv_p->AKI2;					//空き
		i++;
	}

	if(WINDOW_NO < 6 || WINDOW_NO >= 10) {				//段取り用ウインドウ画面？
		sw_tp = SWTBL_Win_Adr_tbl[WINDOW_NO];
		cnt = *SWCOUNT_Win_Adr_tbl[WINDOW_NO];				//カーソルカウンタ
		SW_CNT1 = SW_CNT = (UNs)cnt;
		i = 0;
		while( cnt-- ) {
			d4_p = &SW_buff[i];							//格納ポインタセット
			sw_p = &sw_tp[i];							//格納ポインタセット

			d4_p->XY_POS = sw_p->XY_POS + 6;			//ｶｰｿﾙのX,Y軸(表示行数をウインドウ画面に会わせる)
			d4_p->AKI = sw_p->AKI;						//空き
			d4_p->DATA_ADR = sw_p->DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			d4_p->SUB_NO = sw_p->SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
			d4_p->GRP_NO = sw_p->GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
			d4_p->TOK_FLG = sw_p->TOK_FLG;				//特殊ﾌﾗｸﾞ
			d4_p->CHG_NO = sw_p->CHG_NO;				//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
			d4_p->CSR_NO = sw_p->CSR_NO;				//この設定値の属するｶｰｿﾙ認識番号
			d4_p->DSP_NO = sw_p->DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
			d4_p->CARA_NO = sw_p->CARA_NO;				//ｶｰｿﾙ表示ｷｬﾗ種別
			d4_p->KAN_NO = sw_p->KAN_NO;				//関連ﾊﾞｲﾄ
			d4_p->KAN_ADR = sw_p->KAN_ADR;				//関連ｱﾄﾞﾚｽ
			d4_p->SAVE_NO = sw_p->SAVE_NO;				//格納ﾌﾗｸﾞ
			d4_p->YOBI2 = sw_p->YOBI2;					//予備２
			i++;
		}
	}
	Disp_data_set();									//情報ﾃｰﾌﾞﾙの非表示処理(作成)

}
#else
void	Wintbl_set(void)
{
	Gamenn_CSRtbl_set();
	Gamenn_SVtbl_set();
	Gamenn_PVtbl_set();
	Gamenn_SWLtbl_set();
	Disp_data_set();									//情報ﾃｰﾌﾞﾙの非表示処理(作成)
}
#endif


/*
********************************************************************************
*  Module Name:		Disp_data_set
*  Function Name:	情報ﾃｰﾌﾞﾙの非表示処理(作成)
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙを作成する
*
*  履 歴	:FIT)田端		ON:2002-07-10
********************************************************************************
*/
void	Disp_data_set(void)
{

	CSR_CLS_FLG = 0;						//初期化する

	if(WINDOW_NO == 0){						//ウインドウ画面表示中？
		gamen_tbl_set();
	}
	else{									//YES
		win_tbl_set();
	}

	PVdata_non_sub();
}


/*
********************************************************************************
*  Module Name:		gamen_tbl_set
*  Function Name:	画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙを作成する
*
*  履 歴	:FIT)田端		ON:2002-07-10
********************************************************************************
*/
void	gamen_tbl_set(void)
{
	UNs	wk2b;

	switch(GAMEN_NO) {
		default:
		case 2:			//生産画面　中型基本(未使用)
//V01d		case 6:			//段取画面　基本
		case 11:		//設定画面　ﾃﾞｰﾀ設定
		case 14:		//設定画面　機能選択
//V06p		case 15:		//設定画面　型ﾃﾞｰﾀ管理
		case 18:		//設定画面　ﾃﾞｰﾀ設定選択中型
		case 24:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ　NO/NC設定
		case 25:		//設定画面　ﾛｰﾀﾘｶﾑ　17～20設定
		case 27:		//設定画面　ｺｲﾙﾗｲﾝｶﾑ設定
		case 32:		//ｼｽﾃﾑ設定　仕様設定1
		case 33:		//ｼｽﾃﾑ設定　仕様設定2
		case 34:		//ｼｽﾃﾑ設定　仕様設定3
		case 35:		//ｼｽﾃﾑ設定　仕様設定4
		case 36:		//ｼｽﾃﾑ設定　仕様設定5
		case 37:		//ｼｽﾃﾑ設定　仕様設定6
		case 38:		//ｼｽﾃﾑ設定　C/Bｼｽﾃﾑ定数
		case 39:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1
		case 40:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ2
		case 41:		//ｼｽﾃﾑ設定　ｼｽﾃﾑｶﾑ設定
		case 42:		//ｼｽﾃﾑ画面　速度到達ﾃﾞｰﾀ設定
		case 43:		//ｼｽﾃﾑ設定　内部ｶﾑ･ﾀｲﾏ設定
//V01r		case 44:		//ｼｽﾃﾑ設定　荷重計設定
		case 46:		//ｼｽﾃﾑ画面　ｵﾌﾟｼｮﾝ構成ﾃﾞｰﾀ画面
		case 47:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(左)
		case 48:		//ｼｽﾃﾑ画面　ﾀﾞｲｸｯｼｮﾝ自動調節(右)
		case 49:		//ｼｽﾃﾑ画面　ﾊﾞﾗﾝｻ圧力調整
		case 50:		//ｼｽﾃﾑ設定　ﾊﾞｯｸｱｯﾌﾟﾃﾞｰﾀ設定
		case 51:		//ｼｽﾃﾑ設定　C/Bｼｽﾃﾑ定数2
		case 52:		//ｼｽﾃﾑ設定　ﾃﾞｰﾀ初期化
		case 53:		//ｼｽﾃﾑ画面　ｺｲﾙﾗｲﾝ仕様設定画面
		case 54:		//ｼｽﾃﾑ画面　ﾃﾞｰﾀﾛｰﾄﾞ画面
		case 55:		//ｼｽﾃﾑ画面　仕様設定7
		case 56:		//ｼｽﾃﾑ画面　仕様設定8
		case 57:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ3
		case 58:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ4
		case 59:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ5
		case 60:		//ｼｽﾃﾑ設定　ｻｰﾎﾞﾊﾟﾗﾒｰﾀ6
		case 106:		//ｼｽﾃﾑ画面　仕様設定9		//V06m
		case 107:		//ｼｽﾃﾑ画面　仕様設定10		//V06m
			break;

		case 1:			//生産画面　基本
//V01m			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(19, SYO_LNG_SUR_CNT);							//小数点の変更(設定値&実測値)

			SV_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			PV_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			SW_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ﾛｯﾄｶｳﾝﾀ1の非表示
			CSR_disp_cls(1);										//ﾛｯﾄｶｳﾝﾀ1のｶｰｿﾙ
			CSR_disp_cls(2);										//ﾛｯﾄｶｳﾝﾀ1の設定文字

			SV_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			PV_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			SW_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ﾛｯﾄｶｳﾝﾀ2の非表示
			CSR_disp_cls(3);										//ﾛｯﾄｶｳﾝﾀ2のｶｰｿﾙ
			CSR_disp_cls(4);										//ﾛｯﾄｶｳﾝﾀ2の設定文字

//V01m			LENG_svpv(52, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(52, SYO_LNG_SUR_CNT);							//小数点の変更(設定値&実測値)

			PV_cls(52, SEQ_020_SV, BIT_5);							//ﾀﾞｲﾊｲﾄ実測の非表示
			PV_cls(54, SEQ_020_SV, BIT_5);							//ﾀﾞｲﾊｲﾄ実測の非表示
			CSR_disp_cls(5);										//ﾀﾞｲﾊｲﾄの文字

			PV_cls(53, SEQ_020_SV, BIT_8);							//荷重計実測の非表示
			CSR_disp_cls(6);										//荷重計の文字

			PV_cls(68, SEQ_016_SV, BIT_3);							//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ実測の非表示
			CSR_disp_cls(79);										//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏの文字
			CSR_disp_cls(80);										//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏの文字

			SCAN_kat_cls();											//

			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r

//			SV_cls(72, SEQ_016_SV, BIT_1);							//VS仕様の非表示
//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS仕様の非表示
//			CSR_cls(72, SEQ_016_SV, BIT_1);							//VS仕様の非表示
//			CSR_disp_cls(93);										//VS仕様のｶｰｿﾙ

			PV_cls(124, SEQ_PAR_113, BIT_3);						//制動試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ実測の非表示	V06h

			break;

		case 6:			//生産画面　ﾓｰｼｮﾝ設定	/* V01d */
		case 30:		//設定画面　ﾓｰｼｮﾝ設定	/* V01d */
		case 3:			//生産画面　ﾓｰｼｮﾝ設定
		case 28:		//設定画面　ﾓｰｼｮﾝ設定
			kag_to_kaj_sub_chg();					//下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換		V01k

			LENG_svpv(91, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(92, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(93, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(94, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(95, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(96, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(112, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V01k
			LENG_svpv(113, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V01k
			LENG_svpv(114, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V01k
			LENG_svpv(115, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V01k
			LENG_svpv(116, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V01k
			LENG_svpv(117, SYO_LNG_KAJ_CNT);						//小数点の変更(設定値&実測値) V01k
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//小数点の変更(設定値&実測値) V05r

			SW_cls(62, SEQ_023_SV, BIT_8);							//下往復の非表示
			CSR_disp_cls(136);										//下往復のｶｰｿﾙ

			if ( (SEQ_050_SV & BIT_2) == 0 ) {							//V06p
				SW_cls(62, ~SEQ_PAR_113, BIT_15);					//下往復の非表示
			}

			SW_cls(63, SEQ_023_SV, BIT_9);							//上往復の非表示
			CSR_disp_cls(137);										//上往復のｶｰｿﾙ
			SW_cls(64, SEQ_024_SV, BIT_2);							//反転の非表示
			CSR_disp_cls(150);										//反転のｶｰｿﾙ

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号

			motion_csr_clr();										//ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ対応	/* V01n */

			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//負荷率実測の非表示	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//電力量実測の非表示	//V06

			if (SEQ_050_SV & BIT_0) {	//V06b
				//設定値背景＝白（入力不可）
				SV_col_chg(85, COL_BLACK, COL_WHITE, COL_WHITE);	//回転の時は上限角の背景を白にする。	V06b
				SV_col_chg(91, COL_BLACK, COL_WHITE, COL_WHITE);	//回転の時は上限位置の背景を白にする。	V06b
			}
			
			if (SEQ_050_SV & BIT_2) {	//V06m
				if (GMN_PAR021 == 1) {
					//設定値背景＝白（入力不可）
					SV_col_chg2( 2, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は工程の背景を白にする。
					SV_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は１段目停止時間の背景を白にする。
					SV_col_chg2(27, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は戻り速度の背景を白にする。
					SW_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//振子の時は１段目「Ｖ」の背景を白にする。
				}
			}
			
			break;

		case 4:			//生産画面　ｸﾞﾗﾌﾓｰｼｮﾝ
		case 29:		//設定画面　ｸﾞﾗﾌﾓｰｼｮﾝ
			kag_to_kaj_sub_chg();					//下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換		V01k

			LENG_svpv(91, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(117, SYO_LNG_KAJ_CNT);						//小数点の変更(設定値&実測値) V01k
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//小数点の変更(設定値&実測値) V05r

			SW_cls(62, SEQ_023_SV, BIT_8);							//下往復の非表示
			CSR_disp_cls(136);										//下往復のｶｰｿﾙ
			SW_cls(63, SEQ_023_SV, BIT_9);							//上往復の非表示
			CSR_disp_cls(137);										//上往復のｶｰｿﾙ
			SW_cls(64, SEQ_024_SV, BIT_2);							//反転の非表示
			CSR_disp_cls(150);										//反転のｶｰｿﾙ

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号

			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//負荷率実測の非表示	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//電力量実測の非表示	//V06
			break;

		case 7:			//段取画面　中型基本
//			DANsel_csr(83, SEQ_020_SV, BIT_14, 118);				//金型自動交換		V01j
			DANsel_csr(67, SEQ_020_SV, BIT_4 | BIT_6, 119-1);			//スライド調節
			DANsel_csr(62, SEQ_019_SV, BIT_4, 120-1);					//上型クランパ
			DANsel_csr(63, SEQ_019_SV, BIT_6, 121-1);					//下型クランパ
			DANsel_csr(64, SEQ_019_SV, BIT_8, 122-1);					//ダイリフタ
//			DANsel_csr(65, SEQ_019_SV, BIT_10,123);					//ダイクッション	V01j
//			DANsel_csr(66, SEQ_020_SV, BIT_1, 124);					//防護柵			V01j
//			DANsel_csr(80, SEQ_020_SV, BIT_15,125);					//ＭＢ				V01j
//			DANsel_csr(81, SEQ_020_SV, BIT_11,126);					//バランサ
//			DANsel_csr(82, SEQ_019_SV, BIT_12 | BIT_13 | BIT_15,127);	//ﾀﾞｲｸｯｼｮﾝ調節

			SW_cls(30, SEQ_019_SV, BIT_4);							//上型クランパの非表示
			SW_cls(31, SEQ_019_SV, BIT_6);							//下型クランパの非表示
			SW_cls(32, SEQ_019_SV, BIT_8);							//ダイリフタの非表示
//			SW_cls(33, SEQ_019_SV, BIT_10);							//ダイクッション非表示	V01j
//			SW_cls(34, SEQ_020_SV, BIT_1);							//防護柵の非表示		V01j
//			SW_cls(35, SEQ_020_SV, BIT_15);							//ＭＢの非表示			V01j

			DAN_csr_set();											//段取画面　表示した個数カウンタ

			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(52, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)

			PV_cls(68, SEQ_016_SV, BIT_3);							//ストッピング表示
			CSR_disp_cls(79);
			CSR_disp_cls(80);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 81);					//型番号
			KAT_cls(56, SEQ_PAR_107, BIT_0, 61);					//型番号
			MEMO_cls(69, SEQ_PAR_107,BIT_0, 83);					//メモ

//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS仕様
//			CSR_disp_cls(93);
			break;

		case 8:			//段取画面　中型基本		//V01r
			DANsel_csr(83, SEQ_020_SV, BIT_14, 118);				//金型自動交換		V01j
			DANsel_csr(67, SEQ_020_SV, BIT_4 | BIT_6, 119);			//スライド調節
			DANsel_csr(62, SEQ_019_SV, BIT_4, 120);					//上型クランパ
			DANsel_csr(63, SEQ_019_SV, BIT_6, 121);					//下型クランパ
			DANsel_csr(64, SEQ_019_SV, BIT_8, 122);					//ダイリフタ
			DANsel_csr(65, SEQ_019_SV, BIT_10,123);					//ダイクッション	V01j
			DANsel_csr(66, SEQ_020_SV, BIT_1, 124);					//防護柵			V01j
			DANsel_csr(80, SEQ_020_SV, BIT_15,125);					//ＭＢ				V01j
			DANsel_csr(81, SEQ_020_SV, BIT_11,126);					//バランサ
			DANsel_csr(82, SEQ_019_SV, BIT_12 | BIT_13 | BIT_15,127);	//ﾀﾞｲｸｯｼｮﾝ調節

			SW_cls(30, SEQ_019_SV, BIT_4);							//上型クランパの非表示
			SW_cls(31, SEQ_019_SV, BIT_6);							//下型クランパの非表示
			SW_cls(32, SEQ_019_SV, BIT_8);							//ダイリフタの非表示
			SW_cls(33, SEQ_019_SV, BIT_10);							//ダイクッション非表示	V01j
			SW_cls(34, SEQ_020_SV, BIT_1);							//防護柵の非表示		V01j
			SW_cls(35, SEQ_020_SV, BIT_15);							//ＭＢの非表示			V01j

			DAN_csr_set();											//段取画面　表示した個数カウンタ

			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)

			PV_cls(68, SEQ_016_SV, BIT_3);							//ストッピング表示
			CSR_disp_cls(79);
			CSR_disp_cls(80);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 81);					//型番号
			KAT_cls(56, SEQ_PAR_107, BIT_0, 61);					//型番号
			MEMO_cls(69, SEQ_PAR_107,BIT_0, 83);					//メモ

//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS仕様
//			CSR_disp_cls(93);
			break;

		case 12:		//設定画面　ｶﾑ名称設定
		case 16:		//設定画面　型ﾃﾞｰﾀ名称設定
		case 23:		//設定画面　ﾒﾓ名称入力画面
		case 26:		//設定画面　ﾛｰﾀﾘｶﾑ名称入力
			NAME_cls_sub();
			CSR_disp_cls(96);
			CSR_disp_cls(97);
			CSR_disp_cls(98);
			break;

		case 13:		//設定画面　ﾒﾝﾃﾅﾝｽ ﾓﾆﾀ
//			PV_cls(68, SEQ_016_SV, BIT_3);							//ｽﾄｯﾋﾟﾝｸﾞの非表示
//			SV_cls(68, SEQ_016_SV, BIT_3);							//ｽﾄｯﾋﾟﾝｸﾞの非表示
//			CSR_disp_cls(88);
//			CSR_disp_cls(89);
//			CSR_disp_cls(90);
//			CSR_cls(68, SEQ_016_SV, BIT_3);							//ｽﾄｯﾋﾟﾝｸﾞの非表示
			break;

		case 17:		//設定画面　ﾃﾞｰﾀ設定中型
			kag_to_kaj_sub_chg();					//下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換		V01r

//V01m			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(19, SYO_LNG_SUR_CNT);							//小数点の変更(設定値&実測値)

//			ATU_svpv(21, SYO_ATU_CNT);								//設定値情報ﾃｰﾌﾞﾙの変更

			SV_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			PV_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			SW_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ﾛｯﾄｶｳﾝﾀ1の非表示
			CSR_disp_cls(7);										//ﾛｯﾄｶｳﾝﾀ1の1行

			SV_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			PV_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			SW_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ﾛｯﾄｶｳﾝﾀ2の非表示
			CSR_disp_cls(8);										//ﾛｯﾄｶｳﾝﾀ2の1行

			SV_cls(19, SEQ_020_SV, BIT_6);							//ﾀﾞｲﾊｲﾄの非表示
			PV_cls(54, SEQ_020_SV, BIT_6);							//ﾀﾞｲﾊｲﾄの非表示
			CSR_cls(54, SEQ_020_SV, BIT_6);							//ﾀﾞｲﾊｲﾄの非表示
			CSR_disp_cls(14);
			CSR_disp_cls(15);
			CSR_disp_cls(16);
			CSR_disp_cls(17);

//			SV_cls(21, SEQ_020_SV, BIT_11);							//ﾊﾞﾗﾝｻ圧力の非表示
//			PV_cls(55, SEQ_020_SV, BIT_11);							//ﾊﾞﾗﾝｻ圧力の非表示
//			CSR_cls(55, SEQ_020_SV, BIT_11);						//ﾊﾞﾗﾝｻ圧力の非表示
//			CSR_disp_cls(18);

			SV_cls(53, SEQ_020_SV, BIT_8);							//荷重計の非表示
			PV_cls(53, SEQ_020_SV, BIT_8);							//荷重計の非表示
			CSR_cls(53, SEQ_020_SV, BIT_8);							//荷重計の非表示
			CSR_disp_cls(9);
			CSR_disp_cls(10);
			CSR_disp_cls(11);
			CSR_disp_cls(12);
			CSR_disp_cls(13);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号

			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//小数点の変更(設定値&実測値) V05r

//			SV_cls(72, SEQ_016_SV, BIT_1);							//VS仕様の非表示
//			CSR_cls(72, SEQ_016_SV, BIT_1);							//VS仕様の非表示
//			CSR_disp_cls(94);										//VS仕様のｶｰｿﾙ
			break;

		case 19:		//設定画面　ｴｼﾞｪｸﾀ／自動化ｶﾑ設定
			if( SV_CNT != 00 ) {
				EJE_grp(1, 2, BIT_8, SEQ_017_SV, BIT_4, 32, SEQ_017_SV, BIT_6, 19);			//エジェクタ１
				EJE_grp(22, 23, BIT_9, SEQ_017_SV, BIT_7, 33, SEQ_017_SV, BIT_9, 20);		//エジェクタ２
				EJE_grp(24, 25, BIT_10, SEQ_017_SV, BIT_10, 34, SEQ_017_SV, BIT_12, 21);	//エジェクタ３
				EJE_grp(26, 27, BIT_11, SEQ_017_SV, BIT_13, 35, SEQ_017_SV, BIT_15, 22);	//エジェクタ４
				EJE_grp(28, 29, BIT_12, SEQ_018_SV, BIT_0, 36, SEQ_018_SV, BIT_2, 23);		//エジェクタ５
				EJE_grp(30, 31, BIT_13, SEQ_018_SV, BIT_3, 37, SEQ_018_SV, BIT_5, 24);		//エジェクタ６

				EJE_sw(19, SEQ_017_SV, BIT_4);						//エジェクタ１
				EJE_sw(20, SEQ_017_SV, BIT_7);						//エジェクタ２
				EJE_sw(21, SEQ_017_SV, BIT_10);						//エジェクタ３
				EJE_sw(22, SEQ_017_SV, BIT_13);						//エジェクタ４
				EJE_sw(23, SEQ_018_SV, BIT_0);						//エジェクタ５
				EJE_sw(24, SEQ_018_SV, BIT_3);						//エジェクタ６

				if( CSR_CNT != 00 ) {
					EJE_csr(0x91, SEQ_017_SV, BIT_4, SEQ_017_SV, BIT_6, 25);				//エジェクタ1
					EJE_csr(0x92, SEQ_017_SV, BIT_7, SEQ_017_SV, BIT_9, 26);				//エジェクタ2
					EJE_csr(0x93, SEQ_017_SV, BIT_10, SEQ_017_SV, BIT_12, 27);				//エジェクタ3
					EJE_csr(0x94, SEQ_017_SV, BIT_13, SEQ_017_SV, BIT_15, 28);				//エジェクタ4
					EJE_csr(0x95, SEQ_018_SV, BIT_0, SEQ_018_SV, BIT_2, 29);				//エジェクタ5
					EJE_csr(0x96, SEQ_018_SV, BIT_3, SEQ_018_SV, BIT_5, 30);				//エジェクタ6
				}
			}
			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号
			break;

		case 20:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ設定
			SYS_MISSEL_SV = SEQ_024_SV;								//ﾐｽﾌｨｰﾄﾞ7～8 保持/排出　情報ｺﾋﾟｰ
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//ﾐｽﾌｨｰﾄﾞ1～6 保持/排出　情報ｺﾋﾟｰ

			MIS_sv(46, SEQ_018_SV, BIT_8);							//ミスフィード１
			MIS_sv(47, SEQ_018_SV, BIT_9);							//ミスフィード２
			MIS_sv(48, SEQ_018_SV, BIT_10);							//ミスフィード３
			MIS_sv(49, SEQ_018_SV, BIT_10);							//ミスフィード４

			EJE_sw(25, SEQ_018_SV, BIT_8);							//ミスフィード１
			EJE_sw(26, SEQ_018_SV, BIT_9);							//ミスフィード２
			EJE_sw(27, SEQ_018_SV, BIT_10);							//ミスフィード３
			EJE_sw(28, SEQ_018_SV, BIT_10);							//ミスフィード４

			MIS_csr(15, SEQ_018_SV, BIT_8, 31, 138);				//ミスフィード１
			MIS_csr(16, SEQ_018_SV, BIT_9, 32, 139);				//ミスフィード２
			MIS_csr(17, SEQ_018_SV, BIT_10,33, 140);				//ミスフィード３
			MIS_csr(18, SEQ_018_SV, BIT_10,34, 141);				//ミスフィード４

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号

			MISS_swcara();
			break;

		case 68:		//設定画面　ﾐｽﾌｨｰﾄﾞｶﾑ設定	// V01r(INS)
			SYS_MISSEL_SV = SEQ_024_SV;								//ﾐｽﾌｨｰﾄﾞ7～8 保持/排出　情報ｺﾋﾟｰ
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//ﾐｽﾌｨｰﾄﾞ1～6 保持/排出　情報ｺﾋﾟｰ

			MIS_sv(103, SEQ_018_SV, BIT_11);						//ミスフィード５
			MIS_sv(104, SEQ_018_SV, BIT_11);						//ミスフィード６

			EJE_sw(57, SEQ_018_SV, BIT_11);							//ミスフィード５
			EJE_sw(58, SEQ_018_SV, BIT_11);							//ミスフィード６

			MIS_csr(79, SEQ_018_SV, BIT_11,66, 0);					//ミスフィード５
			MIS_csr(80, SEQ_018_SV, BIT_11,67, 0);					//ミスフィード６

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//型番号

			MISS56_swcara();
			break;

		case 21:		//設定画面　ﾛｰﾀﾘｶﾑ1～8ｶﾑ設定
						/*********	汎用カムの汎用出力選択時の設定値消去処理		*************/
			ROT_cam_sv(1, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 35);	//ﾛｰﾀﾘｶﾑ1
			CSR_disp_cls(142);
			ROT_cam_sv(2, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 36);	//ﾛｰﾀﾘｶﾑ2
			CSR_disp_cls(143);
			ROT_cam_sv(3, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 37);	//ﾛｰﾀﾘｶﾑ3
			CSR_disp_cls(144);
			ROT_cam_sv(4, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 38);	//ﾛｰﾀﾘｶﾑ4
			CSR_disp_cls(145);
			ROT_cam_sv(5, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 39);	//ﾛｰﾀﾘｶﾑ5
			CSR_disp_cls(146);
			ROT_cam_sv(6, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 40);	//ﾛｰﾀﾘｶﾑ6
			CSR_disp_cls(147);
			ROT_cam_sv(7, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 41);	//ﾛｰﾀﾘｶﾑ7
			CSR_disp_cls(148);
			ROT_cam_sv(8, BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 42);	//ﾛｰﾀﾘｶﾑ8
			CSR_disp_cls(149);

						/*********	汎用カムの汎用出力選択時のＳＷデータ消去処理		*************/
			ROT_cam_sw(3, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12);		//ﾛｰﾀﾘｶﾑ1
			ROT_cam_sw(4, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12);		//ﾛｰﾀﾘｶﾑ2
			ROT_cam_sw(5, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12);		//ﾛｰﾀﾘｶﾑ3
			ROT_cam_sw(6, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12);		//ﾛｰﾀﾘｶﾑ4
			ROT_cam_sw(7, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14);		//ﾛｰﾀﾘｶﾑ5
			ROT_cam_sw(8, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14);		//ﾛｰﾀﾘｶﾑ6
			ROT_cam_sw(9, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14);		//ﾛｰﾀﾘｶﾑ7
			ROT_cam_sw(10,BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14);		//ﾛｰﾀﾘｶﾑ8

						/*********	汎用カムの汎用出力選択時のカーソルデータ消去処理		*************/
			ROT_cam_csr(0x80, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12, BIT_13, 43);	//ﾛｰﾀﾘｶﾑ1
			ROT_cam_csr(0x81, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12, BIT_13, 44);	//ﾛｰﾀﾘｶﾑ2
			ROT_cam_csr(0x82, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12, BIT_13, 45);	//ﾛｰﾀﾘｶﾑ3
			ROT_cam_csr(0x83, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12, BIT_13, 46);	//ﾛｰﾀﾘｶﾑ4
			ROT_cam_csr(0x84, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14, BIT_15, 47);	//ﾛｰﾀﾘｶﾑ5
			ROT_cam_csr(0x85, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14, BIT_15, 48);	//ﾛｰﾀﾘｶﾑ6
			ROT_cam_csr(0x86, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14, BIT_15, 49);	//ﾛｰﾀﾘｶﾑ7
			ROT_cam_csr(0x87, BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14, BIT_15, 50);	//ﾛｰﾀﾘｶﾑ8

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//型番号
			break;

		case 22:		//設定画面　ﾛｰﾀﾘｶﾑ9～16ｶﾑ設定
						/*********	汎用カムの汎用出力選択時の設定値消去処理		*************/
			ROT_cam_sv(1, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 35);	//ﾛｰﾀﾘｶﾑ9
			CSR_disp_cls(142);
//V06p
			ROT_cam_sv(1, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14, 40, BIT_1, 35);	//ﾛｰﾀﾘｶﾑ9
			CSR_disp_cls(142);

			ROT_cam_sv(2, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 36);	//ﾛｰﾀﾘｶﾑ10
			CSR_disp_cls(143);
			ROT_cam_sv(3, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 37);	//ﾛｰﾀﾘｶﾑ11
			CSR_disp_cls(144);

			ROT_cam_sv(4, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 38);	//ﾛｰﾀﾘｶﾑ12
			CSR_disp_cls(145);
//V06p
			ROT_cam_sv(4, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6, 40, BIT_1, 38);	//ﾛｰﾀﾘｶﾑ12
			CSR_disp_cls(145);

			ROT_cam_sv(5, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 39);	//ﾛｰﾀﾘｶﾑ13
			CSR_disp_cls(146);
			ROT_cam_sv(6, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 40);	//ﾛｰﾀﾘｶﾑ14
			CSR_disp_cls(147);
			ROT_cam_sv(7, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 41);	//ﾛｰﾀﾘｶﾑ15
			CSR_disp_cls(148);
			ROT_cam_sv(8, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 42);	//ﾛｰﾀﾘｶﾑ16
			CSR_disp_cls(149);

						/*********	汎用カムの汎用出力選択時のＳＷデータ消去処理		*************/
			ROT_cam_sw(11, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0);		//ﾛｰﾀﾘｶﾑ9
//V06p
			ROT_cam_sw(11, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14);		//ﾛｰﾀﾘｶﾑ9

			ROT_cam_sw(12, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0);		//ﾛｰﾀﾘｶﾑ10
			ROT_cam_sw(13, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0);		//ﾛｰﾀﾘｶﾑ11

			ROT_cam_sw(14, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0);		//ﾛｰﾀﾘｶﾑ12
//V06p
			ROT_cam_sw(14, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6);		//ﾛｰﾀﾘｶﾑ12

			ROT_cam_sw(15, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2);		//ﾛｰﾀﾘｶﾑ13
			ROT_cam_sw(16, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2);		//ﾛｰﾀﾘｶﾑ14
			ROT_cam_sw(17, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2);		//ﾛｰﾀﾘｶﾑ15
			ROT_cam_sw(18, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2);		//ﾛｰﾀﾘｶﾑ16

						/*********	汎用カムの汎用出力選択時のカーソルデータ消去処理		*************/
			ROT_cam_csr(0x88, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, BIT_1, 43);	//ﾛｰﾀﾘｶﾑ9
//V06p
			ROT_cam_csr(0x88, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14, BIT_1, 43);	//ﾛｰﾀﾘｶﾑ9

			ROT_cam_csr(0x89, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, BIT_1, 44);	//ﾛｰﾀﾘｶﾑ10
			ROT_cam_csr(0x8A, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, BIT_1, 45);	//ﾛｰﾀﾘｶﾑ11

			ROT_cam_csr(0x8B, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, BIT_1, 46);	//ﾛｰﾀﾘｶﾑ12
//V06p
			ROT_cam_csr(0x8B, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6, BIT_1, 46);	//ﾛｰﾀﾘｶﾑ12

			ROT_cam_csr(0x8C, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2, BIT_3, 47);	//ﾛｰﾀﾘｶﾑ13
			ROT_cam_csr(0x8D, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2, BIT_3, 48);	//ﾛｰﾀﾘｶﾑ14
			ROT_cam_csr(0x8E, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2, BIT_3, 49);	//ﾛｰﾀﾘｶﾑ15
			ROT_cam_csr(0x8F, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2, BIT_3, 50);	//ﾛｰﾀﾘｶﾑ16

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//型番号
			break;

		case 31:		//ｼｽﾃﾑ設定　画面
//			if(OP_STATUS_DT == 00) {						//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
//				PV_cls(73, OP_STATUS_DT, 0xff);
/*** V01j
			if(OP_STATUS == 00) {							//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
				PV_cls(73, OP_STATUS, 0xff);
				CSR_disp_cls(95);
			}
********/
			if(OP_STATUS != 0x55) {							//OPﾅｼ:00H,OPｱﾘ(OK):55H,OPｱﾘ(WDTup):54H
				PV_cls(73, 0, 0);
				CSR_disp_cls(95);
			}
			if(MEM_ARI != 0xA5) {							//OPｱﾘ(OK):A5H			V05 (INS)
				PV_cls(119, 0, 0);
			}

			if (SEQ_PAR_113 & BIT_7) {						//ｼｽﾃﾑ設定1-15非表示指令		V06p
				CSR_cls(126, ~SEQ_PAR_113, BIT_7);			//ｼｽﾃﾑ設定1-15の非表示
			}
			break;

		case 45:		//ｼｽﾃﾑ設定　ｽﾗｲﾄﾞ自動設定
			if( 00 == (SEQ_PAR_101 & BIT_1) ) {				//ｼｽﾃﾑ設定OK？(1:OK)
			 	SW56_dncara_disp(0xff, 8);					//SW56下段ｷｬﾗｸﾀをSW領域へ格納
			}
			break;

		case 9:			//生産画面　サンプリング波形	//V05o
		case 10:		//生産画面　ドレンド波形		//V05o
			LENG_svpv(120, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V06

			SV_cls(122, SEQ_PAR_103, BIT_12);						//電力の非表示		V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//電力の非表示		V06
			CSR_cls(122, SEQ_PAR_103, BIT_12);						//電力の非表示		V06
			SW_cls(122, SEQ_PAR_103, BIT_12);						//電力の非表示		V06a

			SV_cls(125, ~SEQ_PAR_103, BIT_10);						//タッチ位置自動検出非表示		V06p
			CSR_cls(125, ~SEQ_PAR_103, BIT_10);						//タッチ位置自動検出非表示		V06p

			LENG_svpv(127, SYO_LNG_CNT);				//小数点の変更(設定値&実測値)  ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			SV_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			PV_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			CSR_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			SW_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)

			break;

		case 44:		//ｼｽﾃﾑ設定　荷重計設定			//V05r
			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r
			break;

		case 66:		//生産画面　トレンド			//V05o
		case 104:		//生産画面　トレンド			//V06l
			LENG_svpv(120, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)

			LENG_svpv(127, SYO_LNG_CNT);				//小数点の変更(設定値&実測値)  ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			SV_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			PV_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			CSR_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			SW_cls(127, ~SEQ_PAR_113, BIT_5);			//ｽﾗｲﾄﾞ上限／下限	V06p(INS)
			break;

		case 67:		//生産画面　サンプリング		//V05r
		case 105:		//生産画面　サンプリング		//V06l
			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r
			break;

		case 101:		//データ設定画面　加振機能設定	//V05r
			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r
			break;

		case 15:		//設定画面　型ﾃﾞｰﾀ管理		//V06p
			for(wk2b=1; wk2b<41; wk2b++) {
				SW_buff[wk2b].SUB_NO |= BIT_15;						//回転/反転/振子/上往復は一旦全て非表示とする。
			}
			break;

		case 108:		//機器交換時設定画面		//V06p
			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更
			break;
	}
}


/*
********************************************************************************
*  Module Name:		win_tbl_set
*  Function Name:	ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙを作成する
*
*  履 歴	:FIT)田端		ON:2002-07-10
********************************************************************************
*/
void	win_tbl_set(void)
{
	UNs	wk2b;

	switch(WINDOW_NO) {
		default:
		case 1:			//生産画面　生産設定
		case 2:			//生産画面　輝度設定
		case 3:			//生産画面　ｶﾞｲﾀﾞﾝｽ表示
		case 4:			//生産画面　ｼｰｹﾝｽﾁｪｯｸ
		case 7:			//段取画面　ﾊﾞﾗﾝｻ圧力調整
		case 8:			//段取画面　ﾀﾞｲｸｯｼｮﾝ調整
		case 9:			//段取画面　ﾀﾞｲｸｯｼｮﾝ圧力調整
		case 10:		//段取画面　ｶﾞｲﾀﾞﾝｽ表示
		case 11:		//段取画面　ｼｰｹﾝｽﾁｪｯｸ
		case 12:		//段取画面　ｽﾃｯﾌﾟﾓﾆﾀ
		case 13:		//段取画面　ﾀﾞｲｸｯｼｮﾝ操作
//V01m		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作
//V01m		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認
		case 16:		//段取画面　ﾀﾞｲｸｯｼｮﾝ調節操作
		case 17:		//段取画面　ﾀﾞｲｸｯｼｮﾝ自動調節確認
		case 18:		//段取画面　MB選択操作
			break;

		case 05:		//生産画面　生産設定中型
			EJE_grp(1,  2,  BIT_8,  SEQ_017_SV, BIT_4, 32, SEQ_017_SV, BIT_6, 0);	//エジェクタ１
			EJE_grp(22, 23, BIT_9,  SEQ_017_SV, BIT_7, 33, SEQ_017_SV, BIT_9, 0);	//エジェクタ２
			EJE_grp(24, 25, BIT_10, SEQ_017_SV, BIT_10,34, SEQ_017_SV, BIT_12,0);	//エジェクタ３
			EJE_grp(26, 27, BIT_11, SEQ_017_SV, BIT_13,35, SEQ_017_SV, BIT_15,0);	//エジェクタ４
			EJE_grp(28, 29, BIT_12, SEQ_018_SV, BIT_0, 36, SEQ_018_SV, BIT_2, 0);	//エジェクタ５
			EJE_grp(30, 31, BIT_13, SEQ_018_SV, BIT_3, 37, SEQ_018_SV, BIT_5, 0);	//エジェクタ６

			EJE_sw(19, SEQ_017_SV, BIT_4);						//エジェクタ１
			EJE_sw(20, SEQ_017_SV, BIT_7);						//エジェクタ２
			EJE_sw(21, SEQ_017_SV, BIT_10);						//エジェクタ３
			EJE_sw(22, SEQ_017_SV, BIT_13);						//エジェクタ４
			EJE_sw(23, SEQ_018_SV, BIT_0);						//エジェクタ５
			EJE_sw(24, SEQ_018_SV, BIT_3);						//エジェクタ６

			EJE_csr(0x91, SEQ_017_SV, BIT_4, SEQ_017_SV, BIT_6, 62);				//エジェクタ1
			EJE_csr(0x92, SEQ_017_SV, BIT_7, SEQ_017_SV, BIT_9, 63);				//エジェクタ2
			EJE_csr(0x93, SEQ_017_SV, BIT_10,SEQ_017_SV, BIT_12,64);				//エジェクタ3
			EJE_csr(0x94, SEQ_017_SV, BIT_13,SEQ_017_SV, BIT_15,65);				//エジェクタ4
			EJE_csr(0x95, SEQ_018_SV, BIT_0, SEQ_018_SV, BIT_2, 66);				//エジェクタ5
			EJE_csr(0x96, SEQ_018_SV, BIT_3, SEQ_018_SV, BIT_5, 67);				//エジェクタ6

			MIS_csr(14, SEQ_016_SV, BIT_2, 91, 0);				//オーバーロードリミット	/* V01l */

			break;

		case 06:		//段取画面　ｽﾗｲﾄﾞ調節
//V01m			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(19, SYO_LNG_SUR_CNT);								//小数点の変更(設定値&実測値)
			LENG_svpv(52, SYO_LNG_SUR_CNT);								//小数点の変更(設定値&実測値) V01m(INS)

			DANsel_csr(67, SEQ_020_SV, BIT_4, 78);					//スライド調節

			if(0x0030 == (SEQ_020_SV & 0x0070)){					//ｽﾗｲﾄﾞ自動調節が無しでｽﾗｲﾄﾞ有りﾀﾞｲﾊｲﾄ表示有り
				DANsel_csr(70, SEQ_020_SV, BIT_6, 84);				//スライド自動調節
				PV_cls(54, SEQ_020_SV, BIT_6);						//ダイハイト単位
				SV_cls(19, SEQ_020_SV, BIT_6);						//ダイハイト設定値
				CSR_disp_cls(85);
				CSR_disp_cls(86);
				CSR_disp_cls(87);
			}
			break;

		case 14:		//段取画面　ｽﾗｲﾄﾞ調節操作			V01m
		case 15:		//段取画面　ｽﾗｲﾄﾞ自動調節確認		V01m
			LENG_svpv(19, SYO_LNG_SUR_CNT);								//小数点の変更(設定値&実測値)
			break;

		case 19:		//生産画面　生産設定2
			SYS_MISSEL_SV = SEQ_024_SV;								//ﾐｽﾌｨｰﾄﾞ7～8 保持/排出　情報ｺﾋﾟｰ
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//ﾐｽﾌｨｰﾄﾞ1～6 保持/排出　情報ｺﾋﾟｰ

			MIS_sv(46, SEQ_018_SV, BIT_8);							//ミスフィード１
			MIS_sv(47, SEQ_018_SV, BIT_9);							//ミスフィード２
			MIS_sv(48, SEQ_018_SV, BIT_10);							//ミスフィード３
			MIS_sv(49, SEQ_018_SV, BIT_10);							//ミスフィード４
			MIS_sv(103, SEQ_018_SV, BIT_11);						//ミスフィード５	/* V01d */
			MIS_sv(104, SEQ_018_SV, BIT_11);						//ミスフィード６	/* V01d */

			EJE_sw(25, SEQ_018_SV, BIT_8);							//ミスフィード１
			EJE_sw(26, SEQ_018_SV, BIT_9);							//ミスフィード２
			EJE_sw(27, SEQ_018_SV, BIT_10);							//ミスフィード３
			EJE_sw(28, SEQ_018_SV, BIT_10);							//ミスフィード４
			EJE_sw(57, SEQ_018_SV, BIT_11);							//ミスフィード５	/* V01d */
			EJE_sw(58, SEQ_018_SV, BIT_11);							//ミスフィード６	/* V01d */

			MIS_csr(15, SEQ_018_SV, BIT_8, 68, 0);					//ミスフィード１
			MIS_csr(16, SEQ_018_SV, BIT_9, 69, 0);					//ミスフィード２
			MIS_csr(17, SEQ_018_SV, BIT_10,70, 0);					//ミスフィード３
			MIS_csr(18, SEQ_018_SV, BIT_10,71, 0);					//ミスフィード４
			MIS_csr(79, SEQ_018_SV, BIT_11,66, 0);					//ミスフィード５	/* V01d */
			MIS_csr(80, SEQ_018_SV, BIT_11,67, 0);					//ミスフィード６	/* V01d */

			MIS_csr(14, SEQ_016_SV, BIT_2, 91, 0);				//オーバーロードリミット	/* V01l */

			MISS_swcara_win();										//ミスフィードＳＷ表示キャラ切り換え
			break;

		case 20:		//生産画面　補正モニタ		/* V01w */
			LENG_svpv(19, SYO_LNG_CNT);								//小数点の変更(設定値&実測値)
			
			LENG_svpv(117, SYO_LNG_CNT);							//小数点の変更(設定値&実測値) V05h

			KAJ_svpv(53, SYO_KAJ_CNT);								//荷重の小数点変更	V05r

//2010/09/23			PV_cls(121, SEQ_PAR_107, BIT_7);						//負荷率実測の非表示	//V06
//2010/09/23			wk2b = ~SEQ_PAR_107;
//2010/09/23			PV_cls(122, wk2b, BIT_7);								//電力量実測の非表示	//V06
			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//負荷率実測の非表示	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//電力量実測の非表示	//V06
			break;

		case 22:		//データ設定画面　ｶｳﾝﾄ値修正	/* V06b */
			SV_cls(50, SEQ_016_SV, BIT_12);							//ﾛｯﾄｶｳﾝﾀ1の非表示
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ﾛｯﾄｶｳﾝﾀ1の非表示
			SV_cls(51, SEQ_016_SV, BIT_14);							//ﾛｯﾄｶｳﾝﾀ2の非表示
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ﾛｯﾄｶｳﾝﾀ2の非表示
			break;

		case 23:		//生産画面　生産管理		/* V06c */
			wk2b = 0;
			if (SV_WORKER_ENT_FLG == 0x5aa5) {
				wk2b = BIT_0;
			}
			PV_cls(123, wk2b, BIT_0);						//作業者ｺｰﾄﾞの非表示
			break;



	}
}

/*
********************************************************************************
*  Module Name:		motion_csr_clr
*  Function Name:	ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ対応
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ﾓｰｼｮﾝの３段目だけにｶｰｿﾙがいくようにする
*
*  履 歴	:A.Shimamura		ON:2004-11-26 V01n
********************************************************************************
*/
void	motion_csr_clr(void)
{
	UNs		cnt, no;

	if (SEQ_024_SV & BIT_5)
	{														// 有効？
		for(cnt = CSR_CNT, no=0 ; cnt > 0 ; cnt--, no++ )
		{
			if(CSR_buff[no].DATA_NO != 99 )
			{												//３段目？
				CSR_buff[no].TOK_NO |= BIT_0;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EPM_TANI_CHG
*  Function Name:	電力量単位切換え
*  Input	:		なし
*  Return	: 		なし
*  Note		:		
*
*  履 歴	:A.Shimamura		ON:2010-10-26
********************************************************************************
*/
void	EPM_TANI_CHG(void)
{
	if (SEQ_PAR_103 & BIT_12)	//0：負荷率／1：電力量			V06a
	{
		if (GMN_PAR137 == 1)
		{
//			SV0_EP_AVE &= ~BIT_0;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : kW
//			SV0_EP_AVE |=  BIT_1;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : Wh
//			SV0_EP_AVE &= ~BIT_4;		//ﾓｰｼｮﾝﾓﾆﾀ画面の電力量の単位 : kW
//			SV0_EP_AVE |=  BIT_5;		//ﾓｰｼｮﾝﾓﾆﾀ画面の電力量の単位 : Wh
			SV0_EP_AVE = BIT_1 + BIT_5;
		}
		else
		{
//			SV0_EP_AVE |=  BIT_0;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : kW
//			SV0_EP_AVE &= ~BIT_1;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : Wh
//			SV0_EP_AVE |=  BIT_4;		//ﾓｰｼｮﾝﾓﾆﾀ画面の電力量の単位 : kW
//			SV0_EP_AVE &= ~BIT_5;		//ﾓｰｼｮﾝﾓﾆﾀ画面の電力量の単位 : Wh
			SV0_EP_AVE = BIT_0 + BIT_4;
		}
	}
	else
	{
//		SV0_EP_AVE &= ~(BIT_4 + BIT_5);	//ﾓｰｼｮﾝﾓﾆﾀ画面の電力量の単位消す（負荷率の%を表示）
		if (GMN_PAR137 == 1)
		{
//			SV0_EP_AVE &= ~BIT_0;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : kW
//			SV0_EP_AVE |=  BIT_1;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : Wh
			SV0_EP_AVE = BIT_1;
		}
		else
		{
//			SV0_EP_AVE |=  BIT_0;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : kW
//			SV0_EP_AVE &= ~BIT_1;		//ﾄﾚﾝﾄﾞ画面の電力量の単位 : Wh
			SV0_EP_AVE = BIT_0;
		}
	}
}


/*
********************************************************************************
*  Module Name:		mot_type_SWset
*  Function Name:	モーションTYPE用SWセット
*  Input	:		先頭型No.
*  Return	: 		なし
*  Note		:		
*
*  履 歴	:A.Shimamura		ON:2013-02-18		V06p
********************************************************************************
*/
void	mot_type_SWset(UNs ktop)
{
	UNl		adr;
	UNs		i, *type, bit;

	adr = KATA_DATA_ADR_TOP;
	if (ktop>100) {
		adr += 0x180000;					//型No.101からTOPアドレス変わる。
		ktop -= 100;
	}
	adr = adr + (ktop-1) * 0x800;
	adr += (0x534-0x500);						//回転方式が格納されているアドレス
	bit = BIT_0;
	PV0_KATRD_BIT = 0;

	for (i=0; i<10; i++, bit<<=1) {
		type = (UNs *)adr;
		if (*type & BIT_0) {
			/* 回転 */
			SW_buff[1+i*4+0].SUB_NO &= ~BIT_15;		//回転表示セット
		}
		else if (*type & BIT_1) {
			/* 反転 */
			SW_buff[1+i*4+1].SUB_NO &= ~BIT_15;		//反転表示セット
			if ((SEQ_024_SV & BIT_2) ==0) {		//反転仕様OFF？
				PV0_KATRD_BIT |= bit;			//反転表示の背景変更（読めないよ。）
			}
		}
		else if (*type & BIT_2) {
			/* 振子 */
			SW_buff[1+i*4+2].SUB_NO &= ~BIT_15;		//振子表示セット
			if ( ((SEQ_023_SV & BIT_8) ==0) || (SEQ_PAR_113 & BIT_15) ) {		//振子仕様OFF？ or 振子非表示指令ON
				PV0_KATRD_BIT |= bit;			//振子表示の背景変更（読めないよ。）
			}
		}
		else if (*type & BIT_3) {
			/* 上往復 */
			SW_buff[1+i*4+3].SUB_NO &= ~BIT_15;		//上往復表示セット
			if ((SEQ_023_SV & BIT_9) ==0) {		//上往復仕様OFF？
				PV0_KATRD_BIT |= bit;			//上往復表示の背景変更（読めないよ。）
			}
		}
		adr += 0x800;
	}
}


/*** END ***/
