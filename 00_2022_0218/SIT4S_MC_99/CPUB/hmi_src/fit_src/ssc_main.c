/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			画面操作のメイン処理													*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-07
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
#include "CPU_REG.h"							//SH7055 ﾚｼﾞｽﾀ
#include "ssc_ver1.h"
#include "ssc_addr.h"

/* 外部参照関数定義 -------------------------------------------------- */
extern	void	IROCK_SHR(void);						//インターロックデータ検索
extern	void	IROCK_SHR_OUT(void);					//インターロックデータ検索出力		2009/07/14
extern	void	SEISAN_INF_DISP(void);					//生産画面行程表示
extern	void	RULET_GAMEN_DISP(void);					//ルーレット画面表示
extern	void	DEG_DISP(void);							//角度表示処理

extern	void	DP_TRANS_SRV(void);
extern	void	DP_TRANS_SYS(void);
extern	void	DP_TRANS_MOT(void);
extern	void	DP_TRANS_SEQ(void);
extern	void	DP_TRANS_CAM(void);
extern	void	DP_TRANS_GEN(void);
extern	void	DP_GET_SENS	(void);
extern	void	DP_BACK_SENS(void);

extern	void	TIM_mcn_smp(void);

extern	void	COP1_MAIN_TLINK_DAT_REF();//2003-01-31

extern	void	KAT_ENB_GAMEN001_disp(void);			//GAMEN001の時に型ﾃﾞｰﾀ管理が有効になったときの画面再表示
extern	void	Tlink1_mng(void);						//Tlink通信処理
extern	void	ADC_MAIN_MNG(void);						/* 自動金型交換ＭＡＩＮ処理		V01j */
extern	void	ADC_DATA_INI(void);						/* ＡＤＣデータイニシャル次型データクリア処理	SIT4 */

extern	UNs		swap_iw(void *);						//ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(word)

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
extern	void	Alltbl_set(void);
#else
extern	void	ASM_ALLTBL_SET_COL(void);
extern	void	Gamen_Init(void);
#endif

////extern	void	ASM_ET1_IP_BACK(void);					// V05j


/* 外部参照変数定義 -------------------------------------------------- */
extern	U2b	cop_enc_int_enb;
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		CB_SYS_PARAM279;				// /* V06m */
extern	UNs		GMN_PAR014;						// /* V01p */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR011;						//荷重目標変更上下限値
extern	UNs		GMN_PAR040;						//制動性能試験予告ﾀｲﾏ		V05r
extern	UNs		GMN_PAR039;						//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ	V06h
extern	UNs		ALL_CHR_TBL;			//V06
extern	UNs		GAM_INF_TBL;			//V06
extern	UNs		GMN_PAR020;				//V06m
extern	UNs		SH2_MAIN_CLK;


/* 定数定義 ---------------------------------------------------------- */
#define		E_DEBUG		0							//デバッグモード指定(1:ﾃﾞﾊﾞｯｸﾞﾓｰﾄﾞ)
#define		E_DEBUG_1	0							//デバッグモード指定

#define		BLK_MOT		0x0004						/* ﾓｰｼｮﾝ	ﾌﾞﾛｯｸ		*/

/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	dsp_init1(void);						//割込み解除前1回
void	dsp_init2(void);						//割込み解除後1回
void	dsp_init3(void);						//ｲﾆｼｬﾙﾃﾞｰﾀ受信後1回
void	dsp_time_5ms(void);						//5ms定周期処理

void	dsp_main(void);							//画面表示メインルーチン
void	Mode_mng(void);							//Ｋｅｙコードによりモード管理
void	Any_mng(void);							//毎スキャンの固定処理

void	keep_ry_smp(void);						//キープリレーサンプリング

void	GAIBU_cnt_rst(void);					//外部カウンタクリア処理
void	ONOFF_mng(void);						//仕様 有／無 によるｼｰｹﾝｽ制御
void	ONOFF_sub(void);						//仕様 有／無 による入切制御
void	ROTTO_chk(void);						//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

void	CAMname_pon_read(void);					//電源投入時の汎用ｶﾑ名称の読込み
void	FRAM_csum_set(void);					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
void	FRAM_csum_chk(void);					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
void	FRAM_KAT_csum_set(void);				//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
void	FRAM_KAT_csum_chk(void);				//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ

void	Power_down(void);						//パワーダウン処理
void	PV_CHANGE_hanten(void);					//反転仕様時のＰＶ変換
void	debug_dat_mng(void);					//ﾃﾞﾊﾞｯｸﾞﾃﾞｰﾀ転送処理
void	his_dat_mng(void);						//異常履歴ﾃﾞｰﾀ転送処理
void	taikikaku_chg_mng(void);				//待機角変更処理
void	FURIKO_Cancel_mng(void);				// 振子非表示指令の処理		/* V06p */
void	Gamen_Redisp_mng(void);					//画面再表示処理

void	Sampring_Disp(void);					//サンプリング中●表示
void	Trend_disp(void);						//トレンド中■表示
void	Trend_stop(void);						//トレンドの停止
void	KASIN_mark_Disp(void);					//加振制御実行を示す◆表示
void	cop2_pvdata_sin(void);
void	real_kajyu_check(void);
void	SEIDOUSEINOU_mng(void);					// V05r
void	EcoMeter_Disp(void);					// V06
void	LANG_SEQ_OUT(void);						// V06m
void	HAN_MODE_SEQ_OUT(void);					// V06m
void	DIE_HEIGHT_OFFSET(void);				// V06m
void	FURIKO_SPEC_ON_OFF(void);				// V06m
void	SYSSET_SEQ_OUT(void);					// V06n
void 	EPM_data_rif(UNl ADD_BUF[][2], UNs *ADD_POI, UNl MON_BUF[][2], UNs *MON_POI, UNs tim);
void	kagen_disp(void);

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
extern	const	UNs *	Camcsr_Name_Tbl[20];
extern	const	UNs *	Camcsr_Name_Tbl1[16];
extern	const	UNs *	Camcsr_Name_TblSW[16];


/*
********************************************************************************
*  Module Name:		dsp_init1
*  Function Name:	割込み解除前1回
*  Input	: 		なし
*  Return	: 		なし
*  Note		:
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
//MC-KOMA void	dsp_init1(void)
//MC-KOMA{
//MC-KOMA	UNb	b1,b2;
//MC-KOMA	UNs	*poi, chk;
//MC-KOMA
//MC-KOMA	FRAM_csum_chk();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
//MC-KOMA	FRAM_KAT_csum_chk();			//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
//MC-KOMA
//MC-KOMA

//MC-KOMA	INTR_DAT_OFS = 0x140000;
//MC-KOMA	poi = (UNs *)E_INTROCK_PAT;
//MC-KOMA	poi += INTR_DAT_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		INTR_DAT_OFS = 0;
//MC-KOMA	}

//MC-KOMA	INIT_DAT_OFS = 0x140000;
//MC-KOMA	poi = (UNs *)E_FROM_INI_TOP;
//MC-KOMA	poi += INIT_DAT_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		INIT_DAT_OFS = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA	ALL_CHR_TBL_OFS = 0x140000;
//MC-KOMA	poi = &ALL_CHR_TBL;
//MC-KOMA	poi += ALL_CHR_TBL_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		ALL_CHR_TBL_OFS = 0;
//MC-KOMA	}

//MC-KOMA	GAM_INF_TBL_OFS = 0x140000 + 0x018000;
//MC-KOMA	poi = &GAM_INF_TBL;
//MC-KOMA	poi += GAM_INF_TBL_OFS/2;
//MC-KOMA	poi += 512/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	chk &= 0xff00;
//MC-KOMA	if (chk != 0x5a00) {
//MC-KOMA		GAM_INF_TBL_OFS = 0;
//MC-KOMA	}
	// =============================================================
//MC-KOMA
//MC-KOMA
//MC-KOMA	EPM_TOTAL_INF = BIT_0;								//V06a
//MC-KOMA

//MC-KOMA#if ( SIT_TYPE_SEL == TYPE_SIT4)
//MC-KOMA	Gamen_Init();
//MC-KOMA#endif
//MC-KOMA
//MC-KOMA	OP_STATUS = OP_STATUS_REAL;							// V01e
//MC-KOMA	b1 = OP_STATUS_REAL;
//MC-KOMA	b2 = OP_STATUS_REAL;
//MC-KOMA	if ( (OP_STATUS != 0x55) && (OP_STATUS != 0x54) )
//MC-KOMA	{
//MC-KOMA		OP_STATUS = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA	MEM_ARI = MEM_ARI_REAL;								// V05h
//MC-KOMA	b1 = MEM_ARI_REAL;
//MC-KOMA	b2 = MEM_ARI_REAL;
//MC-KOMA	if ( MEM_ARI != 0xA5 )
//MC-KOMA	{
//MC-KOMA		MEM_ARI = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA}


void	dsp_init1(void)
{
	UNb	b1,b2;

	OP_STATUS = OP_STATUS_REAL;							// V01e
	b1 = OP_STATUS_REAL;
	b2 = OP_STATUS_REAL;
	if ( (OP_STATUS != 0x55) && (OP_STATUS != 0x54) )
	{
		OP_STATUS = 0;
	}

	MEM_ARI = MEM_ARI_REAL;								// V05h
	b1 = MEM_ARI_REAL;
	b2 = MEM_ARI_REAL;
	if ( MEM_ARI != 0xA5 )
	{
		MEM_ARI = 0;
	}

}


/*
********************************************************************************
*  Module Name:		dsp_init2
*  Function Name:	割込み解除後1回
*  Input	: 		なし
*  Return	: 		なし
*  Note		:
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	dsp_init2(void)
{
	UNs		sum_rem;

	sum_rem = 0;

//V06n
	SV0_RNAPOS_MINO = SV_RNAPOS_MINP;			//機械下限
	SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP;			//機械上限
	SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1;			//ダイハイト下限
	SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2;			//ダイハイト上限

	LANG_SEQ_OUT();									//V06m
	GENGO_chg(0xff);								//第２カ国語切替え処理

	SVSW_CHG_FLG = 0x0050;

	PODATA_SET_FLG = 0xff;
	OPdata_bak();									//ｵﾌﾟｼｮﾝの現位置ﾃﾞｰﾀ返還
	OPdata_set_kaku();								//ｵﾌﾟｼｮﾝ ﾃﾞｰﾀ転送処理
	POSdata_set_kaku();								//ﾎﾟｼﾞｼｮﾅｰ ﾃﾞｰﾀ転送処理
	OPdata_sys_kaku();								//ｵﾌﾟｼｮﾝにｼｽﾊﾟﾗを格納

	ONOFF_sub();									//仕様有り無しによる入切制御
	ROTTO_chk();									//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

	CAR_mkssi_set();								//単位切換データ格納処理
	CAMname_pon_read();								//電源投入時の汎用ｶﾑ名称の読込み

	mmon_sel_chk();									//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
	mmon_trans_get();								//回転方式によるﾃﾞｰﾀの取得

	taikikaku_chg_mng();							//待機角GET		/* V01m_a */


	if ( (SV_LANGUAGE < 1) || (3 < SV_LANGUAGE) ) {	//V06n
		SV_LANGUAGE = 1;
		sum_rem = 0xff;
	}
	if ( 9 < SV_HAN_P ) {	//V06n
		SV_HAN_P = 0;
		sum_rem = 0xff;
	}
	if ( 9 < SV_HAN_S ) {	//V06n
		SV_HAN_S = 0;
		sum_rem = 0xff;
	}
	if ( (SV_KATTCH_SPD < 1) || (100 < SV_KATTCH_SPD) ) {	//V06p
		SV_KATTCH_SPD = 50;
		sum_rem = 0xff;
	}

	if (sum_rem) {
		FRAM_csum_set();
	}


	DP_TRANS_SRV();									/* ｻｰﾎﾞ  ﾌﾞﾛｯｸ転送処理	*/
	DP_TRANS_SYS();									/* ｼｽﾊﾟﾗ ﾌﾞﾛｯｸ転送処理	*/
	DP_TRANS_MOT();									/* ﾓｰｼｮﾝ ﾌﾞﾛｯｸ転送処理	*/
	DP_TRANS_SEQ();									/* ｼｰｹﾝｽ ﾌﾞﾛｯｸ転送処理	*/
	DP_TRANS_CAM();									/* ｶﾑ    ﾌﾞﾛｯｸ転送処理	*/
	DP_TRANS_GEN();									/* 原点  ﾌﾞﾛｯｸ転送処理	*/

	DP_BACK_SENS();									/* ﾘﾆｱｾﾝｻBACKUP値 復旧	*/

	SVSW_CHG_FLG	= 0x0000;						/* 要求ﾌﾗｸﾞ ｸﾘｱ			*/
	HS_SVCHG_B_TO_A	= 0x0000;						/* ﾊﾝﾄﾞｼｪｲｸ 書込領域ｸﾘｱ	*/
	HS_SVCHG_A_TO_B	= 0x0000;						/* ﾊﾝﾄﾞｼｪｲｸ 読込領域ｸﾘｱ	*/

	SURA_CHG_LST = 0;								// V01l_c

/* V01  */
	SVB_DYHITO_POS = PV_DYHITO_POS;					// 下限位置ﾊﾞｯｸｱｯﾌﾟをC/Bへ戻す
	SVB_SLIDE_POS = PV_SLIDE_POS;					// 生産下限位置ﾊﾞｯｸｱｯﾌﾟをC/Bへ戻す

	SEQ_PAR_076 = PV_MLDNO1_F1;						// V05d

////	ASM_ET1_IP_BACK();								// V05j

}


/*
********************************************************************************
*  Module Name:		dsp_init3
*  Function Name:	ｲﾆｼｬﾙﾃﾞｰﾀ受信後1回
*  Input	: 		なし
*  Return	: 		なし
*  Note		:
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	dsp_init3(void)
{

#if	E_DEBUG								//デバッグモード指定
	SEQ_PAR_101 = 0xff;					//ﾃﾞﾊﾞｯｸﾞ用
	SEQ_PAR_107 |= 0x01ff;				//ﾃﾞﾊﾞｯｸﾞ用
#endif

	kido_data_set();					//輝度表示 & データ作成

	CSR_FLG = 0;						//ホームポジションセット
	disp_stg = 00;						//生産画面
	disp_stg_sel = E_sstg_init;			//生産[基本]へ
	GAMEN_NO = 1;
	GAMEN_disp();						//画面表示

}


/*
********************************************************************************
*  Module Name:		dsp_time_5ms
*  Function Name:	5ms定周期処理
*  Input	: 		なし
*  Return	: 		なし
*  Note		:
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
#define		def_1min_cnt	12000	// = 60秒／5ms
#define		def_1sec_cnt	200		// =  1秒／5ms

//	"SIT4-MCのcpubでは呼ばれていない"
void	dsp_time_5ms(void)
{
	UNs		wk1,wk2;
	UNl		dwk1,dwk2;

	TIM_5MS_COUNT();						// ロットカウンタ処理

	TIM_mcn_smp();							//メンテナンス時間 処理

	ROTTO_chk();							//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ

//2014-01	if(cop_enc_int_enb){//koma add
//2014-01		COP1_MAIN_TLINK_DAT_REF();//2003-01-31// SAITO 2004-05-21
//2014-01	}

	if(step_flick_cnt==0) {
		step_flick_cnt = 100;				// 500ms
		step_flick_flg ^= 0xffff;
	}
	else {
		step_flick_cnt--;
	}

//V01o	SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_T);		//荷重（TON）(1word) → Ｃ／Ｂ			V01k
//V01p	SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_KEEP_T);		//荷重（TON）(1word) → Ｃ／Ｂ			V01k
	if (GMN_PAR014 == 0)	//V01p
	{
		SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_T);		//荷重（TON）(1word) → Ｃ／Ｂ
	}
	else
	{
		SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_KEEP_T);		//荷重（TON）(1word) → Ｃ／Ｂ
	}

	Dsp_PvWave_5ms();			//V05o


	/****************************************************/
	/*		性動性能試験			V05r				*/
	/****************************************************/
	if(sys_1min_cnt)	sys_1min_cnt--;
	if(sys_1min_cnt == 0)
	{
		sys_1min_cnt = def_1min_cnt;
		/* 1min 処理 */

#if 0	//2011/09/12  変更  V06h
		if(PVTIM_seidouseinou_inter)	PVTIM_seidouseinou_inter--;			//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ
		if(PVTIM_seidouseinou_yokok)	PVTIM_seidouseinou_yokok--;			//制動性能試験予告ﾀｲﾏ
#endif
		if (SEQ_PAR_113 & BIT_0) {
			if(PV_INTER_TIM) {
				PV_INTER_TIM--;				//制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ
			}
		}
	}

	/****************************************************/
	/*		電力モニタ				V06					*/
	/****************************************************/
	if(sys_1sec_cnt)	sys_1sec_cnt--;
	if(sys_1sec_cnt == 0)
	{
		sys_1sec_cnt = def_1sec_cnt;
		/* 1sec 処理 */

		EPM_SEC_2_MESMIN_ADD[0] += PVP_EPM_SYOHI;			//消費電力量 積算(kWs)
		EPM_SEC_2_MESMIN_ADD[1] += PVP_EPM_KAISE;			//回生電力量 積算(kWs)

		EPM_SEC_MESMIN_CNT += 1;

//V06b		if(EPM_SEC_MESMIN_CNT >= 60*5)					//5分積算更新
		if(EPM_SEC_MESMIN_CNT >= 60*1)					//1分積算更新
		{
			EPM_SEC_MESMIN_CNT = 0;

			EPM_data_rif(EPM_05MIN_BUF, &EPM_05MIN_POI, EPM_05MON_BUF, &EPM_05MON_POI, 05);
			EPM_data_rif(EPM_10MIN_BUF, &EPM_10MIN_POI, EPM_10MON_BUF, &EPM_10MON_POI, 10);
			EPM_data_rif(EPM_15MIN_BUF, &EPM_15MIN_POI, EPM_15MON_BUF, &EPM_15MON_POI, 15);
			EPM_data_rif(EPM_20MIN_BUF, &EPM_20MIN_POI, EPM_20MON_BUF, &EPM_20MON_POI, 20);
			EPM_data_rif(EPM_25MIN_BUF, &EPM_25MIN_POI, EPM_25MON_BUF, &EPM_25MON_POI, 25);
			EPM_data_rif(EPM_30MIN_BUF, &EPM_30MIN_POI, EPM_30MON_BUF, &EPM_30MON_POI, 30);
			EPM_data_rif(EPM_35MIN_BUF, &EPM_35MIN_POI, EPM_35MON_BUF, &EPM_35MON_POI, 35);
			EPM_data_rif(EPM_40MIN_BUF, &EPM_40MIN_POI, EPM_40MON_BUF, &EPM_40MON_POI, 40);
			EPM_data_rif(EPM_45MIN_BUF, &EPM_45MIN_POI, EPM_45MON_BUF, &EPM_45MON_POI, 45);
			EPM_data_rif(EPM_50MIN_BUF, &EPM_50MIN_POI, EPM_50MON_BUF, &EPM_50MON_POI, 50);
			EPM_data_rif(EPM_55MIN_BUF, &EPM_55MIN_POI, EPM_55MON_BUF, &EPM_55MON_POI, 55);
			EPM_data_rif(EPM_60MIN_BUF, &EPM_60MIN_POI, EPM_60MON_BUF, &EPM_60MON_POI, 60);

			EPM_SEC_2_MESMIN_ADD[0] = 0;							//消費電力量 5積算(kWs)クリア
			EPM_SEC_2_MESMIN_ADD[1] = 0;							//回生電力量 5積算(kWs)クリア

			EPM_GAMEN_RIF = 1;	//画面ﾘﾌﾚｯｼｭ			//V06b
		}
	}

	if(EPM_CLR_TIM)		EPM_CLR_TIM--;				//電力ﾓﾆﾀｸﾘｱ時間

}


void EPM_data_rif(UNl ADD_BUF[][2], UNs *ADD_POI, UNl MON_BUF[][2], UNs *MON_POI, UNs tim)
{
	UNs		wk1, wk2;
	UNl		dwk1, dwk2;

	ADD_BUF[*ADD_POI][0] = EPM_SEC_2_MESMIN_ADD[0];		//消費電力量 1分積算(kWs)格納
	ADD_BUF[*ADD_POI][1] = EPM_SEC_2_MESMIN_ADD[1];		//回生電力量 1分積算(kWs)格納

	*ADD_POI += 1;

//V06b	if (*ADD_POI >= (tim/5))
	if (*ADD_POI >= tim)
	{
		*ADD_POI = 0;
//V06b		for (wk1=0,dwk1=0,dwk2=0; wk1<(tim/5); wk1++)
		for (wk1=0,dwk1=0,dwk2=0; wk1<tim; wk1++)
		{
			dwk1 += ADD_BUF[wk1][0];
			dwk2 += ADD_BUF[wk1][1];
		}
		MON_BUF[*MON_POI][0] = dwk1;
		MON_BUF[*MON_POI][1] = dwk2;
		*MON_POI += 1;
//V06b		if(*MON_POI >= 20)
		if(*MON_POI >= 19)
		{
			*MON_POI = 0;
		}
//V06b		if (tim == SV_EPMCSR_TIM)	EPM_GAMEN_RIF = 1;	//画面ﾘﾌﾚｯｼｭ
	}
}

/*
********************************************************************************
*  Module Name:		dsp_main
*  Function Name:	画面表示メインルーチン
*  Input	: 		なし
*  Return	: 		なし
*  Note		:
*  履 歴	:FIT)田端		ON:2002-05-20
********************************************************************************
*/
void	dsp_main(void)
{
	Key_mng();					/* ｷｰ入力の確定	*/
	Mode_mng();					/* Ｋｅｙコードによりモード管理 */

	Any_mng();					/* 毎スキャンの固定処理 */
}


	extern	short	DSET_SW_FLG;		// 2006-07-22 SAITO ソフト共通化

/*
********************************************************************************
*  Module Name:		Mode_mng
*  Function Name:	Ｋｅｙコードによりモード管理
*  Input	:		ＫＥＹ＿ＤＡＴＡ＿ＭＯＤＥ
*					ＫＥＹ＿ＤＡＴＡ＿ＣＯＤＥ
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-15
********************************************************************************
*/
void	Mode_mng(void)
{
//	if (SEQ_PAR_103 & BIT_11)		return;		// 制動試験WIN表示中		V06
	if (SEQ_PAR_103 & BIT_11)		goto	MODE_CHG_SKIP;		// 制動試験WIN表示中		V06

//2006-07-22 SAITO	if( (PDDR ^ SET_KEY_LST) & BIT_10 ) {		/* 生産画面　←→　データ設定画面　の切替え	*/
//2006-07-22 SAITO		SET_KEY_LST = PDDR;
	if( (DSET_SW_FLG ^ SET_KEY_LST) & BIT_10 ) {	/* 生産画面　←→　データ設定画面　の切替え	*/
		SET_KEY_LST = DSET_SW_FLG;					//2006-07-22 SAITO ソフト共通化
		if(SET_KEY_LST & BIT_10) {					//データ設定画面　？
			disp_stg = 02;							//データ設定画面
			disp_stg_sel = E_dstg_init;				//データ設定[基本]へ
			GAMEN_NO = 17;
		}
		else {										//No
			SEI_csr_ichk();							//生産カーソル位置初期化
			CSR_FLG = 0;							//ホームポジションセット
			disp_stg = 00;							//生産画面
			disp_stg_sel = E_sstg_init;				//生産[基本]へ
			GAMEN_NO = 1;
		}
		GAMEN_disp();								//画面表示
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	else if(KEY_DATA_MODE == E_key_sw7_mode){	/* 生産画面　←→　型段取画面　の切替え	*/
		if(00 == (SET_KEY_LST & BIT_10)){			//生産画面？
			if(disp_stg == 00){						//生産画面?
				DAN_csr_ichk();						//段取カーソル位置初期化
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00){
					DAN_KEY_FLG = 0xff;				//型段取キーにて高機能型画面移動時の処理
					disp_stg = 01;					//段取画面
					disp_stg_sel = E_kstg_init;		//段取[基本]へ
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10) {	// V01r
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//画面表示
				}
			}
			else if(disp_stg == 01) {				//型段取画面?
				SEI_csr_ichk();						//生産カーソル位置初期化

				CSR_FLG = 0;						//ホームポジションセット
				disp_stg = 00;						//生産画面
				disp_stg_sel = E_sstg_init;			//生産[基本]へ
				GAMEN_NO = 1;
				GAMEN_disp();							//画面表示
			}
		}
		DAN_KEY_FLG = 0x00;						//型段取キーにて高機能型画面移動時の処理
	}
#else
	else if(00 == (SET_KEY_LST & BIT_10)){			//生産画面？
		if ( 00 != (SEQ_PAR_101 & BIT_10) ) {
			if(disp_stg == 00){						//生産画面?
				DAN_csr_ichk();						//段取カーソル位置初期化
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00){
					DAN_KEY_FLG = 0xff;				//型段取キーにて高機能型画面移動時の処理
					disp_stg = 01;					//段取画面
					disp_stg_sel = E_kstg_init;		//段取[基本]へ
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10) {	// V01r
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//画面表示
				}
				DAN_KEY_FLG = 0x00;						//型段取キーにて高機能型画面移動時の処理
			}
		}
		else {
			if(disp_stg == 01) {				//型段取画面?
				SEI_csr_ichk();						//生産カーソル位置初期化

				CSR_FLG = 0;						//ホームポジションセット
				disp_stg = 00;						//生産画面
				disp_stg_sel = E_sstg_init;			//生産[基本]へ
				GAMEN_NO = 1;
				GAMEN_disp();							//画面表示
				DAN_KEY_FLG = 0x00;						//型段取キーにて高機能型画面移動時の処理
			}
		}
	}
#endif


MODE_CHG_SKIP:


//SIT4	else if(KEY_DATA_MODE == E_key_ten_mode)	//ten key mode?
	if(KEY_DATA_MODE == E_key_ten_mode)		//ten key mode?
	{
		Key_Ten_in(KEY_DATA_CODE);				//Ten KEY入力
	}

	else if(KEY_DATA_MODE == E_key_csr_mode) {	//ｶｰｿﾙ key mode?
		if( CSR_CNT != 00 ){
			CSR_FLG = KEY_DATA_CODE;

			switch(GAMEN_NO) {
				case 1:
					SEI_csr_mng();				//生産[基本]の専用　カーソル移動管理
					break;
				case 7:			//段取り画面表示中は専用のルーチンを走る
					DAN_csr_mng();				//段取[基本]の専用　カーソル移動管理
					break;
				case 8:			//段取り画面表示中は専用のルーチンを走る	//V01r
					DAN_csr_mng();				//段取[基本]の専用　カーソル移動管理
					break;
				case 12:		//カム名称入力画面
				case 16:		//型名称入力画面
				case 23:		//メモデータ入力画面
					NAME_csr_mng();				//名称画面カーソル制御
					break;
				case 15:		//型データ一覧画面
					if(PV_MLDMES_C1 == 0){						//メッセージ表示中はカーソルを移動しない
						CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//まだ移動ＯＫ
					}											//メッセージ表示中はＮＧ
					break;
				default:
					CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);	//カーソル移動
					break;
			}

//?			CALL	SPATH_DISP			;/* 生産設定のミスフィード表示時のスペース表示   */
			SV_csr_set();								//設定値カーソル

			if(WINDOW_NO == 0){
				RULET_NOW_LST = 0xffff;
				DEG_DISP_LST = 0xffff;					/* 角度ﾃﾞｰﾀ変化あり？ */
				STOPTIME_DISP_LST = 0xffff;				/* 角度ﾃﾞｰﾀ変化あり？ */
			}
			else{
				Lcd_line(00, 6, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 7, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 8, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 9, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 10, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 11, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
				Lcd_line(00, 12, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)
			}
			Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);		//行表示(LCD1)
			Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);		//行表示(LCD1)
			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示(LCD2)
			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//行表示(LCD2)
		}
	}

/* V00p */
	else if(((SEQ_050_SV & BIT_1) && ((SEQ_PAR_101_BAK & BIT_9)==0) && (SEQ_PAR_101 & BIT_9)) ||
			((SEQ_050_SV & BIT_1) && (SEQ_PAR_101_BAK & BIT_9) && ((SEQ_PAR_101 & BIT_9)==0))) {		//反転　？
		disp_stg_sel_bak = disp_stg_sel;
		WINDOW_NO_bak = WINDOW_NO;
		if (RULET_DISP_FLG != 0x00) {
			GAMEN_disp();
			if (disp_stg_sel_bak != 0 ) {
				disp_stg_sel = disp_stg_sel_bak;
				WINDOW_NO = WINDOW_NO_bak;
				WIN_gamen_disp();					//ウインドウ画面表示
			}
		}
	}

	else {
		switch(disp_stg) {
			case 0x00:				/* 生産画面	*/
				dsp_Seisan();
				break;

			case 0x01:				/* 段取画面	*/
				dsp_Dandori();
				break;

			case 0x02:				/* データ設定画面	*/
				dsp_Dataset();
				break;

			case 0x03:				/* システム設定画面	*/
				dsp_Sysset();
				break;

			default:
				break;
		}
	}

/* V00p */
	SEQ_PAR_101_BAK = SEQ_PAR_101;
}


/*
********************************************************************************
*  Module Name:		Any_mng
*  Function Name:	毎スキャンの固定処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	Any_mng(void)
{
	UNl		w1,w2;

/* V00t */
//	PV_DISP_CNT = PVdata_disp( PV_DISP_CNT, 0x00 );	//実測値情報　表示
	PVdata_disp_all();								//全　実測値情報　表示
/********/

	SWchg_disp_pv_any();							//SWﾃﾞｰﾀ　実測値 表示

	IROCK_SHR();									//インターロックデータ検索
	IROCK_SHR_OUT();								//インターロックデータ検索出力		2009/07/14
	SEISAN_INF_DISP();								//生産画面行程表示

	keep_ry_smp();									//キープリレーサンプリング

///////////////////////////////////////////////////////////////////////
#if	E_DEBUG											//デバッグモード指定
	PVP_NOW_ANGLE_RNA	= (PVP_NOW_ANGLE00 * 10);	// エンコーダ×１０
	HS_SVCHG_A_TO_B		= HS_SVCHG_B_TO_A;			// ハンドシェイク
#endif
///////////////////////////////////////////////////////////////////////

	RULET_GAMEN_DISP();								//ルーレット画面表示
	DEG_DISP();										//角度表示処理
//	SPM_DISP();										//ＳＰＭ表示処理


	GAIBU_cnt_rst();								//外部カウンタクリア処理
	ONOFF_mng();									//仕様 有／無 によるｼｰｹﾝｽ制御

	DP_TRANS_CHK();									//DPRAM ← FRAM ﾃﾞｰﾀ転送処理
	OPDP_trans_chk();								//OP-DPRAM ⇔ FRAM ﾃﾞｰﾀ転送 & ﾁｪｯｸ処理

	GENGO_SEQ_CHG();								/* 言語切り換え機能		*/		/* V01x */
	GENGO_chg(0x00);								//第２カ国語切替え処理

	PV_CHANGE_hanten();								//反転仕様時のＰＶ変換

	debug_dat_mng();

/* V00s */
	SEQ_PAR_060 = SV_CAMNA0_C1;						//ロータリカム汎用出力
	SEQ_PAR_061 = SV_CAMNA1_C1;						//ロータリカム汎用出力
	SEQ_PAR_062 = SV_CAMNA2_C1;						//ロータリカム汎用出力
	SEQ_PAR_063 = SV_CAMNA3_C1;						//ロータリカム汎用出力
	SEQ_PAR_064 = SV_CAMNA4_C1;						//ロータリカム汎用出力
	SEQ_PAR_065 = SV_CAMNA5_C1;						//ロータリカム汎用出力
	SEQ_PAR_066 = SV_CAMNA6_C1;						//ロータリカム汎用出力
	SEQ_PAR_067 = SV_CAMNA7_C1;						//ロータリカム汎用出力
	SEQ_PAR_068 = SV_CAMNA8_C1;						//ロータリカム汎用出力
	SEQ_PAR_069 = SV_CAMNA9_C1;						//ロータリカム汎用出力
	SEQ_PAR_070 = SV_CAMNAA_C1;						//ロータリカム汎用出力
	SEQ_PAR_071 = SV_CAMNAB_C1;						//ロータリカム汎用出力
	SEQ_PAR_072 = SV_CAMNAC_C1;						//ロータリカム汎用出力
	SEQ_PAR_073 = SV_CAMNAD_C1;						//ロータリカム汎用出力
	SEQ_PAR_074 = SV_CAMNAE_C1;						//ロータリカム汎用出力
	SEQ_PAR_075 = SV_CAMNAF_C1;						//ロータリカム汎用出力

	PV_DYHITO_POS = PVP_DYHITO_POS;					// 下限位置ﾊﾞｯｸｱｯﾌﾟ			/* V01  */
	PV_SLIDE_POS = PVP_SLIDE_POS;					// 生産下限位置ﾊﾞｯｸｱｯﾌﾟ		/* V01  */

	his_dat_mng();									// 異常履歴ﾃﾞｰﾀ転送処理		/* V01  */

	taikikaku_chg_mng();							// 待機角変更処理			/* V01i */

	FURIKO_Cancel_mng();							// 振子非表示指令の処理		/* V06p */

	Gamen_Redisp_mng();								// 画面再表示処理			/* V01i */

	KAT_ENB_GAMEN001_disp();						//GAMEN001の時に型ﾃﾞｰﾀ管理が有効になったときの画面再表示 /* V01j */

	Tlink1_mng();									//Tlink通信処理		/* V01j */
	ADC_MAIN_MNG();									/* 自動金型交換ＭＡＩＮ処理		V01j */
	ADC_DATA_INI();									/* ＡＤＣデータイニシャル次型データクリア処理	SIT4 */

	Sampring_Disp();								/* ｻﾝﾌﾟﾘﾝｸﾞ中の表示 */
	Trend_disp();									/* ﾄﾚﾝﾄﾞ中の表示 */
	Trend_stop();									/* ﾄﾚﾝﾄﾞの停止 */
	KASIN_mark_Disp();								//加振制御実行を示す◆表示	V05r

	cop2_pvdata_sin();								/* COP2 */

	w1 = PV_LIFE_COUNT[1];							/* 稼働回数 下位 */
	w2 = PV_LIFE_COUNT[0]<<16;						/* 稼働回数 上位 */
	PVP_MENTE_CNT = w1 | w2;						// V02

	real_kajyu_check();								// V04

	SEQ_PAR_076 = PV_MLDNO1_F1;						// V05d

////	ASM_ET1_IP_BACK();								// V05j

	SEIDOUSEINOU_mng();								// V05r

	EcoMeter_Disp();								// V06

	LANG_SEQ_OUT();									// V06m
	HAN_MODE_SEQ_OUT();								// V06m
	DIE_HEIGHT_OFFSET();							// V06m
//	FURIKO_SPEC_ON_OFF();							// V06m		//V06p(DEL)
	SYSSET_SEQ_OUT();								// V06n

//	---2013-02-07 koma 現地対応
	if(SV_PUR1SV_B4==0){//設定==0
		SEQ_PAR_098 |= cBIT0;
	}else{
		SEQ_PAR_098 &= ~cBIT0;
		
	}
	if(SV_PUR2SV_B41==0){//設定==0
		SEQ_PAR_098 |= cBIT1;
	}else{
		SEQ_PAR_098 &= ~cBIT1;
	}

//V06p
	PV0_CKSPD_OVBIT = PVP_CKSPD_OVBIT | ((PVP_CKSPD_OVBIT>>1) & BIT_14);
	if( ((GAMEN_NO == 3) && (SV_DANSUU_SRV > 5)) ||
		((GAMEN_NO == 28) && (SV_DANSUU_SRV > 5)) ) {
		PV0_CKSPD_OVBIT &= ~BIT_14;
	}

//V06p
	if (GAMEN_NO == 108) {							//機器交換画面
		SEQ_PAR_051 |= cBIT13;						//表示中
	}
	else {
		SEQ_PAR_051 &= ~cBIT13;
	}
		

	//◆◆◆下限位置表示ﾘﾌﾚｯｼｭ◆◆◆
	SH2_MAIN_CLK ^= cBIT0;							//2013/07/23	測定用
	kagen_disp();									//2013/07/22	下限PV表示の高速化

}


/*
********************************************************************************
*  Module Name:		kagen_disp
*  Function Name:	下限位置表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
********************************************************************************
*/
void	kagen_disp(void)
{
	if ( SEQ_PAR_341 & BIT_3 ) {						//2013/07/22	下限PV表示の高速化
		if ( (GAMEN_NO == 1) && (WINDOW_NO == 0) ) {
			PV_CHANGE_hanten();							//反転仕様時のＰＶ変換
			PVdata_disp( 7, 0x00ff );					//実測値情報　表示
		}
	}
}


#if	E_DEBUG_1											//デバッグモード指定

//ANY_MNG		PROC	FAR
//
//OK			CALL	SEQ_CB1_DTST			; SEQ DATA SET
//OK			CALL	SEQ_SVDATA_SET			;/* ＳＥＱのＳＶデータ格納 */
//OK			CALL	GAM_SV_DTST			; GAMEN DATA SET

//OK(Sit-Sなし)	CALL	PV_DATA_SMP			;/* 実測値サンプリング */

//OK			CALL	PVDATA_DISP			;/* 実測値表示 */
//OK			CALL	SWCHG_DISP_PV_ANY		;/* ＳＷＣＨＧデータ表示実測処理 */
//OK			CALL	IROCK_SHR			;/* インターロックデータ検索	*/
//OK			CALL	SEISAN_INF_DISP			;/* 生産画面行程表示            */

//	CALL	ERR_MONI_CHK			;/* 異常チェックモニターデータメイク */

//再チェック	CALL	OPDATA_SET_KAKU			;/* オプションーデータ転送処理*/
//再チェック	CALL	POSDATA_SET_KAKU		;/* ポジショナーデータ転送処理	*/
//再チェック	CALL	OFF_SET_START_MNG		;/* オフセット スタート表示管理	*/
//再チェック	CALL	KOUSEI_START_MNG		;/* 校正スタート表示管理*/
//再チェック	CALL	SURA_AUTO_START_MNG		;/* スライド自動調整スタート表示管理*/

//OK			CALL	ONOFF_MNG			;/* 仕様有り無しによる入切制御 	*/

//OK			CALL	KEEP_RY_SMP			;V02 /* キープリレーサンプリング */

//再チェック	CALL	MAIN_OP_SEQ			;V03 /* シーケンスをオプションへ転送 */

//再チェック	CALL	AUTO_SURA_SEQ_START		;/* スライド自動調整シーケンススタート */
//再チェック	CALL	SURA_SV_CHG			;/* スライド自動調節ＳＶ変更処理 */

//OK			CALL	SEIDAN_CSR_BACK			;/* 生産・段取戻りカーソル位置初期化		*/
//OK			CALL	RULET_TBL_SET			;/* ルーレット表示テーブル検索 */
//OK			CALL	RULET_GAMEN_DISP		;/* ルーレット画面表示 	*/

//OK			CALL	SET_KEY_MNG			;/* 設定データキー変更処理 */

//OK			CALL	DEG_DISP			;/* 角度表示処理     	*/
//OK(Sit-Sなし)	CALL	SPM_DISP			;/* ＳＰＭ表示処理     	*/
//OK			CALL	GAIBU_CNT_RST			;/* 外部カウンタクリア処理 			*/

//再チェック			CALL	OPDATA_BAK_UP			;/* オプションバックアップ処理	*/

//Sit-Sなし		CALL	SETSPM_SV_CHG			;/* 生産ＳＰＭＳＶ変更処理 			*/

//Sit-Sなし		CALL	GENGO_SEQ_CHG			;V06/* 言語切り換え機能		*/
//OK			CALL	GENGO_CHG			;/* 第二外国語切換処理	*/


//Sit-Sなし		CALL	ADC_MAIN_MNG			;/* 自動金型交換ＭＡＩＮ処理		*/
//Sit-Sなし		CALL	ADC_DATA_INI			;/* ＡＤＣデータイニシャル次型データクリア処理	*/

//再チェック		CALL	SURA_SELECT_MNG			;V03k/* スライド自動調節選択切り換え処理	*/
//再チェック		CALL	POJI_DATA_CHK			;V05 2000-09-11/* ポジショナバックアップ値監視 */

//Sit-Sなし		CALL	SEI_GAIBU_MNG			;V06/* 生産速度外部切り換え機能 */
//Sit-Sなし		CALL	TLINK_NEXT_READ			;V06/* Ｔ－ＬＩＮＫ外部型番号読込処理	 */

//	RET					;
//;
//ANY_MNG		ENDP

#endif

/*
********************************************************************************
*  Module Name:		keep_ry_smp
*  Function Name:	キープリレーサンプリング
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-12
********************************************************************************
*/
void	keep_ry_smp(void)
{

//;
//;sit-s		MOV_SEQB(SEQ_PAR_312,SEQ_BAK_312)
//;sit-s		MOV_SEQB(SEQ_PAR_313,SEQ_BAK_313)
//;sit-s		MOV_SEQB(SEQ_PAR_314,SEQ_BAK_314)
//;sit-s		MOV_SEQB(SEQ_PAR_315,SEQ_BAK_315)
//;sit-s		MOV_SEQB(SEQ_PAR_316,SEQ_BAK_316)
//;sit-s		MOV_SEQB(SEQ_PAR_317,SEQ_BAK_317)
//;sit-s		MOV_SEQB(SEQ_PAR_318,SEQ_BAK_318)
//;sit-s		MOV_SEQB(SEQ_PAR_319,SEQ_BAK_319)
//;

}


/*
********************************************************************************
*  Module Name:		GAIBU_cnt_rst
*  Function Name:	外部カウンタクリア処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-03
********************************************************************************
*/
void	GAIBU_cnt_rst(void)
{
	UNs		i, chg_flg;

	chg_flg = 0;

	i = GAIBU_RST_LAST;					//外部リセット指令立ち上がり？
	GAIBU_RST_LAST = SEQ_PAR_102;
	i ^= SEQ_PAR_102;
	i &= SEQ_PAR_102;

/* V00t */
//	if( i & BIT_3 ) {					//トータルカウンタ１リセット？
//		PV_TOTLC1_B3 = 0;				//トータルカウンタ１クリア
//		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
//	}
//	if( i & BIT_7 ) {					//トータルカウンタ２リセット？
//		PV_TOTLC2_B31 = 0;				//トータルカウンタ２クリア
//		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
//	}
//	if( i & BIT_B ) {					//ロットカウンタ１リセット？
//		PV_LOTCT1_B4 = 0;				//ロットカウンタ１クリア
//		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
//		SEQ_PAR_033 &= ~BIT_0;			//ロットカウンタ１アップ　クリア
//	}
//	if( i & BIT_F ) {					//ロットカウンタ２リセット？
//		PV_LOTCT2_B41 = 0;				//ロットカウンタ２クリア
//		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
//		SEQ_PAR_033 &= ~BIT_1;			//ロットカウンタ２アップ　クリア
//	}
/********/

	if( SEQ_017_SV & BIT_1 ){			//カウンタ外部 入／切　仕様有無(1:有)
		if( i & 0x0033 ){
			if(SEQ_016_SV & BIT_8){		//トータルカウンタ 有り(1:有)？ 
				if(i & BIT_0){			//トータルカウンタ 切指令(1:切) 立上り？ 
					SEQ_032_SV &= ~BIT_0;	//トータルカウンタ 切
					chg_flg |= BIT_0;
				}
				if(i & BIT_1){			//トータルカウンタ 入指令(1:入) 立上り？
					SEQ_032_SV |= BIT_0;	//トータルカウンタ 入
					chg_flg |= BIT_0;
				}
			}
//GAIBU_CNT_RST_450:
		}
//GAIBU_CNT_RST_500:
		if( i & 0x3300){
			if(SEQ_016_SV & BIT_C){		//ロットカウンタ1 有り(1:有)？ 
				if(i & BIT_8){			//ロットカウンタ1 切指令(1:切) 立上り？ 
					SEQ_032_SV &= ~BIT_2;	//ロットカウンタ1 切
					chg_flg |= BIT_0;
				}
				if(i & BIT_9){			//ロットカウンタ1 入指令(1:入) 立上り？
					SEQ_032_SV |= BIT_2;	//ロットカウンタ1 入
					chg_flg |= BIT_0;
				}
			}
			if(SEQ_016_SV & BIT_E){		//ロットカウンタ2 有り(1:有)？ 
				if(i & BIT_C){			//ロットカウンタ2 切指令(1:切) 立上り？ 
					SEQ_032_SV &= ~BIT_3;	//ロットカウンタ2 切
					chg_flg |= BIT_0;
				}
				if(i & BIT_D){			//ロットカウンタ2 入指令(1:入) 立上り？
					SEQ_032_SV |= BIT_3;	//ロットカウンタ2 入
					chg_flg |= BIT_0;
				}
			}
			ROTTO_chk();							//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
		}
	}
//GAIBU_CNT_RST_700:
	if( SEQ_017_SV & BIT_2 ){			//エジェクタ外部 入／切　仕様有無(1:有)
		i = GAIBU_RST_LAST2;			//外部リセット指令立ち上がり？
		GAIBU_RST_LAST2 = SEQ_PAR_104;
		i ^= SEQ_PAR_104;
		i &= SEQ_PAR_104;
		if( i & 0x0fff ){					//エジェクタ１～６立ち上がり？

			if(SEQ_017_SV & BIT_4){			//エジェクタ１ 有り(1:有)？ 
				if(i & BIT_0){				//エジェクタ１ 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_0;	//エジェクタ１ 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_1){				//エジェクタ１ 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_0;	//エジェクタ１ 入
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_7){			//エジェクタ2 有り(1:有)？ 
				if(i & BIT_2){				//エジェクタ2 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_1;	//エジェクタ2 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_3){				//エジェクタ2 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_1;	//エジェクタ2 入
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_10){		//エジェクタ3 有り(1:有)？ 
				if(i & BIT_4){				//エジェクタ3 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_2;	//エジェクタ3 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_5){				//エジェクタ3 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_2;	//エジェクタ3 入
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_13){		//エジェクタ4 有り(1:有)？ 
				if(i & BIT_6){				//エジェクタ4 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_3;	//エジェクタ4 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_7){				//エジェクタ4 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_3;	//エジェクタ4 入
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_018_SV & BIT_0){			//エジェクタ5 有り(1:有)？ 
				if(i & BIT_8){				//エジェクタ5 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_4;	//エジェクタ5 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_9){				//エジェクタ5 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_4;	//エジェクタ5 入
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_018_SV & BIT_3){			//エジェクタ6 有り(1:有)？ 
				if(i & BIT_10){				//エジェクタ6 切指令(1:切) 立上り？ 
					SEQ_034_SV &= ~BIT_5;	//エジェクタ6 切
					chg_flg |= BIT_1;
				}
				if(i & BIT_11){				//エジェクタ6 入指令(1:入) 立上り？
					SEQ_034_SV |= BIT_5;	//エジェクタ6 入
					chg_flg |= BIT_1;
				}
			}
		}
	}
//GAIBU_CNT_RST_800:
	if( SEQ_017_SV & BIT_3 ){			//ミスフィード外部 入／切　仕様有無(1:有)
		i = GAIBU_RST_LAST3;			//外部リセット指令立ち上がり？
		GAIBU_RST_LAST3 = SEQ_PAR_105;
		i ^= SEQ_PAR_105;
		i &= SEQ_PAR_105;
		if( i & 0xffff ){					//ミスフィード1～8立ち上がり？

			if(SEQ_018_SV & BIT_8){			//ミスフィード1 有り(1:有)？ 
				if(i & BIT_0){				//ミスフィード1 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_0;	//ミスフィード1 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_1){				//ミスフィード1 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_0;	//ミスフィード1 入
					chg_flg |= BIT_2;
				}
			}
			if(SEQ_018_SV & BIT_9){			//ミスフィード2 有り(1:有)？ 
				if(i & BIT_2){				//ミスフィード2 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_1;	//ミスフィード2 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_3){				//ミスフィード2 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_1;	//ミスフィード2 入
					chg_flg |= BIT_2;
				}
			}
			if(SEQ_018_SV & BIT_10){		//ミスフィード3～4 有り(1:有)？ 
				if(i & BIT_4){				//ミスフィード3 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_2;	//ミスフィード3 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_5){				//ミスフィード3 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_2;	//ミスフィード3 入
					chg_flg |= BIT_2;
				}

				if(i & BIT_6){				//ミスフィード4 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_3;	//ミスフィード4 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_7){				//ミスフィード4 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_3;	//ミスフィード4 入
					chg_flg |= BIT_2;
				}

/*** V01d
				if(i & BIT_8){				//ミスフィード5 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_4;	//ミスフィード5 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_9){				//ミスフィード5 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_4;	//ミスフィード5 入
					chg_flg |= BIT_2;
				}

				if(i & BIT_10){				//ミスフィード6 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_5;	//ミスフィード6 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_11){				//ミスフィード6 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_5;	//ミスフィード6 入
					chg_flg |= BIT_2;
				}
***/
			}
			if(SEQ_018_SV & BIT_11){		//ミスフィード5～8 有り(1:有)？ 

				/* V01d */
				if(i & BIT_8){				//ミスフィード5 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_4;	//ミスフィード5 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_9){				//ミスフィード5 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_4;	//ミスフィード5 入
					chg_flg |= BIT_2;
				}

				/* V01d */
				if(i & BIT_10){				//ミスフィード6 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_5;	//ミスフィード6 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_11){				//ミスフィード6 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_5;	//ミスフィード6 入
					chg_flg |= BIT_2;
				}

				if(i & BIT_12){				//ミスフィード7 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_6;	//ミスフィード7 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_13){				//ミスフィード7 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_6;	//ミスフィード7 入
					chg_flg |= BIT_2;
				}

				if(i & BIT_14){				//ミスフィード8 切指令(1:切) 立上り？ 
					SEQ_036_SV &= ~BIT_7;	//ミスフィード8 切
					chg_flg |= BIT_2;
				}
				if(i & BIT_15){				//ミスフィード8 入指令(1:入) 立上り？
					SEQ_036_SV |= BIT_7;	//ミスフィード8 入
					chg_flg |= BIT_2;
				}
			}
		}
	}
//GAIBU_CNT_RST_900:
	if( chg_flg & 0x0007 ){
		SVSW_CHG_FLG |= BIT_3;
		SVSW_CHG_FLG |= BIT_5;

		i = 0xff;
		if(chg_flg & BIT_0){
			if(GAMEN_NO == 1 || GAMEN_NO == 17){
				i = 0;
			}
		}
		if(chg_flg & BIT_1){
			if(GAMEN_NO == 19 || WINDOW_NO == 5){
				i = 0;
			}
		}
		if(chg_flg & BIT_2){
			if(GAMEN_NO == 20 || WINDOW_NO == 19){
				i = 0;
			}
		}

		if( i == 0 ){
			SWCHG_DISP_ON_FLG = 0x0FF;
			SWchg_disp_gaibu();					//SWﾃﾞｰﾀ情報　表示
			SWCHG_DISP_ON_FLG = 0;
		}
		FRAM_csum_set();							//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	}

/* V00t */
////GAIBU_CNT_RST_1000:
//	if( SEQ_PAR_107 & BIT_6 ){						//ﾛｯﾄｶｳﾝﾀ減算式？
//		PV_LOTCT1_B1 = (SV_PUR1SV_B4 - PV_LOTCT1_B4);
//		PV_LOTCT2_B1 = (SV_PUR2SV_B41 - PV_LOTCT2_B41);
//													//減算方式時ﾏｲﾅｽ表示対策
//		if( PV_LOTCT1_B1 & 0x80000000 ) {
//			PV_LOTCT1_B1 = 0;
//		}
//		if( PV_LOTCT2_B1 & 0x80000000 ) {
//			PV_LOTCT2_B1 = 0;
//		}
//	}
//	else{
//		PV_LOTCT1_B1 = PV_LOTCT1_B4;
//		PV_LOTCT2_B1 = PV_LOTCT2_B41;
//	}
/********/
}


/*
********************************************************************************
*  Module Name:		ONOFF_mng
*  Function Name:	仕様 有／無 によるｼｰｹﾝｽ制御
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-05
********************************************************************************
*/
void	ONOFF_mng(void)
{
	UNs		bf, i, j;

	bf = SEQ_016_SV & 0x5500;
	j = ONOFF_LAST1;
	ONOFF_LAST1 = bf;
	bf ^= j;
	bf &= j;

	i = SEQ_017_SV & 0x6db0;
	j = ONOFF_LAST2;
	ONOFF_LAST2 = i;
	i ^= j;
	i &= j;
	bf |= i;

	i = SEQ_018_SV & 0x5f1b;
	j = ONOFF_LAST3;
	ONOFF_LAST3 = i;
	i ^= j;
	i &= j;
	bf |= i;

	i = SEQ_019_SV & 0xfaa5;
	j = ONOFF_LAST4;
	ONOFF_LAST4 = i;
	i ^= j;
	bf |= i;

	i = SEQ_020_SV & 0x4045;
	j = ONOFF_LAST5;
	ONOFF_LAST5 = i;
	i ^= j;
	bf |= i;

	i = SEQ_021_SV & 0x00f3;
	j = ONOFF_LAST6;
	ONOFF_LAST6 = i;
	i ^= j;
	bf |= i;

	if(bf != 00){
		ONOFF_sub();						//仕様有り無しによる入切制御
	}
}


/*
********************************************************************************
*  Module Name:		ONOFF_sub
*  Function Name:	仕様 有／無 による入切制御
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-06
********************************************************************************
*/
void	ONOFF_sub(void)
{

	ONOFF_FLG = 0;

	if(00 == (SEQ_016_SV & BIT_8) &&		//トータルカウンタ無し
		SEQ_032_SV & BIT_0 ){				//トータルカウンタ入り

		SEQ_032_SV &= ~BIT_0;
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_016_SV & BIT_12) &&		//ロットカウンタ１無し
		SEQ_032_SV & BIT_2 ){				//ロットカウンタ１入り

		SEQ_032_SV &= ~BIT_2;
		ROTTO_chk();						//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_016_SV & BIT_14) &&		//ロットカウンタ２無し
		SEQ_032_SV & BIT_3 ){				//ロットカウンタ２入り

		SEQ_032_SV &= ~BIT_3;
		ROTTO_chk();						//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_018_SV & BIT_8)){			//ﾐｽﾌｨｰﾄﾞ1 無し
		SEQ_037_SV &= ~BIT_8;				//ﾐｽﾌｨｰﾄﾞ1 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_0){				//ﾐｽﾌｨｰﾄﾞ1 入り
			SEQ_036_SV &= ~BIT_0;			//ﾐｽﾌｨｰﾄﾞ1 入／切
			SEQ_036_SV &= ~BIT_8;			//ﾐｽﾌｨｰﾄﾞ1 即／連
			SEQ_037_SV &= ~BIT_0;			//ﾐｽﾌｨｰﾄﾞ1 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_9)){			//ﾐｽﾌｨｰﾄﾞ2 無し
		SEQ_037_SV &= ~BIT_9;				//ﾐｽﾌｨｰﾄﾞ2 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_1){				//ﾐｽﾌｨｰﾄﾞ2 入り
			SEQ_036_SV &= ~BIT_1;			//ﾐｽﾌｨｰﾄﾞ2 入／切
			SEQ_036_SV &= ~BIT_9;			//ﾐｽﾌｨｰﾄﾞ2 即／連
			SEQ_037_SV &= ~BIT_1;			//ﾐｽﾌｨｰﾄﾞ2 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_10)){		//ﾐｽﾌｨｰﾄﾞ3 無し
		SEQ_037_SV &= ~BIT_10;				//ﾐｽﾌｨｰﾄﾞ3 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_2){				//ﾐｽﾌｨｰﾄﾞ3 入り
			SEQ_036_SV &= ~BIT_2;			//ﾐｽﾌｨｰﾄﾞ3 入／切
			SEQ_036_SV &= ~BIT_10;			//ﾐｽﾌｨｰﾄﾞ3 即／連
			SEQ_037_SV &= ~BIT_2;			//ﾐｽﾌｨｰﾄﾞ3 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_10)){		//ﾐｽﾌｨｰﾄﾞ4 無し
		SEQ_037_SV &= ~BIT_11;				//ﾐｽﾌｨｰﾄﾞ4 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_3){				//ﾐｽﾌｨｰﾄﾞ4 入り
			SEQ_036_SV &= ~BIT_3;			//ﾐｽﾌｨｰﾄﾞ4 入／切
			SEQ_036_SV &= ~BIT_11;			//ﾐｽﾌｨｰﾄﾞ4 即／連
			SEQ_037_SV &= ~BIT_3;			//ﾐｽﾌｨｰﾄﾞ4 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

//V01d	if(00 == (SEQ_018_SV & BIT_10)){		//ﾐｽﾌｨｰﾄﾞ5 無し
	if(00 == (SEQ_018_SV & BIT_11)){		//ﾐｽﾌｨｰﾄﾞ5 無し
		SEQ_037_SV &= ~BIT_12;				//ﾐｽﾌｨｰﾄﾞ5 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_4){				//ﾐｽﾌｨｰﾄﾞ5 入り
			SEQ_036_SV &= ~BIT_4;			//ﾐｽﾌｨｰﾄﾞ5 入／切
			SEQ_036_SV &= ~BIT_12;			//ﾐｽﾌｨｰﾄﾞ5 即／連
			SEQ_037_SV &= ~BIT_4;			//ﾐｽﾌｨｰﾄﾞ5 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

//V01d	if(00 == (SEQ_018_SV & BIT_10)){		//ﾐｽﾌｨｰﾄﾞ6 無し
	if(00 == (SEQ_018_SV & BIT_11)){		//ﾐｽﾌｨｰﾄﾞ6 無し
		SEQ_037_SV &= ~BIT_13;				//ﾐｽﾌｨｰﾄﾞ6 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_5){				//ﾐｽﾌｨｰﾄﾞ6 入り
			SEQ_036_SV &= ~BIT_5;			//ﾐｽﾌｨｰﾄﾞ6 入／切
			SEQ_036_SV &= ~BIT_13;			//ﾐｽﾌｨｰﾄﾞ6 即／連
			SEQ_037_SV &= ~BIT_5;			//ﾐｽﾌｨｰﾄﾞ6 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_11)){		//ﾐｽﾌｨｰﾄﾞ7 無し
		SEQ_037_SV &= ~BIT_14;				//ﾐｽﾌｨｰﾄﾞ7 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_6){				//ﾐｽﾌｨｰﾄﾞ7 入り
			SEQ_036_SV &= ~BIT_6;			//ﾐｽﾌｨｰﾄﾞ7 入／切
			SEQ_036_SV &= ~BIT_14;			//ﾐｽﾌｨｰﾄﾞ7 即／連
			SEQ_037_SV &= ~BIT_6;			//ﾐｽﾌｨｰﾄﾞ7 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_11)){		//ﾐｽﾌｨｰﾄﾞ8 無し
		SEQ_037_SV &= ~BIT_15;				//ﾐｽﾌｨｰﾄﾞ8 接触／保持
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_7){				//ﾐｽﾌｨｰﾄﾞ8 入り
			SEQ_036_SV &= ~BIT_7;			//ﾐｽﾌｨｰﾄﾞ8 入／切
			SEQ_036_SV &= ~BIT_15;			//ﾐｽﾌｨｰﾄﾞ8 即／連
			SEQ_037_SV &= ~BIT_7;			//ﾐｽﾌｨｰﾄﾞ8 N.O／N.C
			ONOFF_FLG = 0xff;
		}
	}


	if(00 == (SEQ_018_SV & BIT_12) &&		//ﾛｰﾀﾘｶﾑ 1～4無し
		SEQ_038_SV & 0x000f ){				//RCLS 1～4入り

		SEQ_038_SV &= 0xfff0;				//RCLS 1～4 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_14) &&		//ﾛｰﾀﾘｶﾑ 5～8無し
		SEQ_038_SV & 0x00f0 ){				//RCLS 5～8入り

		SEQ_038_SV &= 0xff0f;				//RCLS 5～8 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_019_SV & BIT_0) &&		//ﾛｰﾀﾘｶﾑ 9～12無し
		SEQ_038_SV & 0x0f00 ){				//RCLS 9～12入り

		SEQ_038_SV &= 0xf0ff;				//RCLS 9～12 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_019_SV & BIT_2) &&		//ﾛｰﾀﾘｶﾑ 13～16無し
		SEQ_038_SV & 0xf000 ){				//RCLS 13～16入り

		SEQ_038_SV &= 0x0fff;				//RCLS 13～16 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_6) &&		//ﾛｰﾀﾘｶﾑ 17～20無し
		SEQ_039_SV & 0x000f ){				//RCLS 17～20入り

		SEQ_039_SV &= 0xfff0;				//RCLS 17～20 切
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_017_SV & BIT_4) &&		//ｴｼﾞｪｸﾀ1 無し
		SEQ_034_SV & BIT_0 ){				//ｴｼﾞｪｸﾀ1 入り

		SEQ_034_SV &= ~BIT_0;				//ｴｼﾞｪｸﾀ1 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_7) &&		//ｴｼﾞｪｸﾀ2 無し
		SEQ_034_SV & BIT_1 ){				//ｴｼﾞｪｸﾀ2 入り

		SEQ_034_SV &= ~BIT_1;				//ｴｼﾞｪｸﾀ2 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_10) &&		//ｴｼﾞｪｸﾀ3 無し
		SEQ_034_SV & BIT_2 ){				//ｴｼﾞｪｸﾀ3 入り

		SEQ_034_SV &= ~BIT_2;				//ｴｼﾞｪｸﾀ3 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_13) &&		//ｴｼﾞｪｸﾀ4 無し
		SEQ_034_SV & BIT_3 ){				//ｴｼﾞｪｸﾀ4 入り

		SEQ_034_SV &= ~BIT_3;				//ｴｼﾞｪｸﾀ4 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_0) &&		//ｴｼﾞｪｸﾀ5 無し
		SEQ_034_SV & BIT_4 ){				//ｴｼﾞｪｸﾀ5 入り

		SEQ_034_SV &= ~BIT_4;				//ｴｼﾞｪｸﾀ5 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_3) &&		//ｴｼﾞｪｸﾀ6 無し
		SEQ_034_SV & BIT_5 ){				//ｴｼﾞｪｸﾀ6 入り

		SEQ_034_SV &= ~BIT_5;				//ｴｼﾞｪｸﾀ6 切
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_5) &&		//ｴｼﾞｪｸﾀ1 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_8 ){				//ｴｼﾞｪｸﾀ1 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_8;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_8) &&		//ｴｼﾞｪｸﾀ2 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_9 ){				//ｴｼﾞｪｸﾀ2 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_9;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_11) &&		//ｴｼﾞｪｸﾀ3 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_10 ){				//ｴｼﾞｪｸﾀ3 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_10;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_14) &&		//ｴｼﾞｪｸﾀ4 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_11 ){				//ｴｼﾞｪｸﾀ4 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_11;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_1) &&		//ｴｼﾞｪｸﾀ5 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_12 ){				//ｴｼﾞｪｸﾀ5 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_12;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_4) &&		//ｴｼﾞｪｸﾀ6 ﾀｲﾏ 無し
		SEQ_034_SV & BIT_13 ){				//ｴｼﾞｪｸﾀ6 ﾀｲﾏ 選択

		SEQ_034_SV &= ~BIT_13;
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_021_SV & BIT_4) &&		//項目番号01 無し
		SEQ_040_SV & BIT_0 ){				//項目番号01 入れ

		SEQ_040_SV &= ~BIT_0;				//項目番号01 切れ
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_5) &&		//項目番号02 無し
		SEQ_040_SV & BIT_1 ){				//項目番号02 入れ

		SEQ_040_SV &= ~BIT_1;				//項目番号02 切れ
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_6) &&		//項目番号03 無し
		SEQ_040_SV & BIT_2 ){				//項目番号03 入れ

		SEQ_040_SV &= ~BIT_2;				//項目番号03 切れ
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_7) &&		//項目番号04 無し
		SEQ_040_SV & BIT_3 ){				//項目番号04 入れ

		SEQ_040_SV &= ~BIT_3;				//項目番号04 切れ
		ONOFF_FLG = 0xff;
	}


											//段取り信号強制ＯＦＦ
	SEQ_041_SV &= 0x1cfc;
	SEQ_042_SV &= 0x1c1c;
	SEQ_043_SV &= 0x1c1c;
	SEQ_044_SV &= 0x0c1c;
	SEQ_045_SV &= 0x1c14;
	SEQ_046_SV &= 0x0c1c;
	DANseq_alloff();						//段取り用シーケンスＯＦＦ

	DAN_sel(&SEQ_041_SV, SEQ_019_SV, BIT_5, 0x00);	//上型クランパ選択
	DAN_sel(&SEQ_041_SV, SEQ_019_SV, BIT_7, 0x01);	//下型クランパ選択
	DAN_sel(&SEQ_042_SV, SEQ_019_SV, BIT_9, 0x00);	//ダイリフタ選択
	DAN_sel(&SEQ_044_SV, SEQ_020_SV, BIT_6, 0x00);	//スライド自動選択

	SWchg_bit_chk();						//ＳＷデータ入力時強制選択拒否処理

	FRAM_csum_set();						//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	if(ONOFF_FLG == 0xff){
		SVSW_CHG_FLG |= 0x002f;				//データ格納フラブセット
	}
}


/*
********************************************************************************
*  Module Name:		ROTTO_chk
*  Function Name:	ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-14
********************************************************************************
*/
void	ROTTO_chk(void)
{
//	UNs		wk;
	UNl		wk;			//V06j 2012/03/23

//V06e
//	if( 0 == (SEQ_016_SV & BIT_C) ||			//ﾛｯﾄｶｳﾝﾀ1(1:有)
//		0 == (SEQ_032_SV & BIT_2) ||			//ﾛｯﾄｶｳﾝﾀ1入／切(1:入)
//		SEQ_PAR_102 & BIT_B ||					//ﾛｯﾄｶｳﾝﾀ1 ﾘｾｯﾄ指令(1:ﾘｾｯﾄ)
//		SV_PUR1SV_B4 > PV_LOTCT1_B4 ) {
//
//		SEQ_PAR_033 &= ~BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
//	}
//	else{
//		SEQ_PAR_033 |= BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
//	}
//
//	if( 0 == (SEQ_016_SV & BIT_E) ||			//ﾛｯﾄｶｳﾝﾀ2(1:有)
//		0 == (SEQ_032_SV & BIT_3) ||			//ﾛｯﾄｶｳﾝﾀ2入／切(1:入)
//			SEQ_PAR_102 & BIT_F ||				//ﾛｯﾄｶｳﾝﾀ2 ﾘｾｯﾄ指令(1:ﾘｾｯﾄ)
//			SV_PUR2SV_B41 > PV_LOTCT2_B41) {
//
//		SEQ_PAR_033 &= ~BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
//	}
//	else{
//		SEQ_PAR_033 |= BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
//	}

	if( 0 == (SEQ_016_SV & BIT_C) ||			//ﾛｯﾄｶｳﾝﾀ1(1:有)
		0 == (SEQ_032_SV & BIT_2) ||			//ﾛｯﾄｶｳﾝﾀ1入／切(1:入)
		SEQ_PAR_102 & BIT_B ) {					//ﾛｯﾄｶｳﾝﾀ1 ﾘｾｯﾄ指令(1:ﾘｾｯﾄ)

		SEQ_PAR_033 &= ~BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		SEQ_PAR_033 &= ~BIT_4;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
	}
	else {
		if ( SV_PUR1SV_B4 > PV_LOTCT1_B4 ) {

			SEQ_PAR_033 &= ~BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
		else{
			SEQ_PAR_033 |= BIT_0;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}

		wk = SV_PUR1SV_B4;
		if (wk) {
			wk = wk - 1;
		}
		if ( wk > PV_LOTCT1_B4 ) {

			SEQ_PAR_033 &= ~BIT_4;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
		else{
			SEQ_PAR_033 |= BIT_4;					//ﾛｯﾄｶｳﾝﾀ1 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
	}

	if( 0 == (SEQ_016_SV & BIT_E) ||			//ﾛｯﾄｶｳﾝﾀ2(1:有)
		0 == (SEQ_032_SV & BIT_3) ||			//ﾛｯﾄｶｳﾝﾀ2入／切(1:入)
			SEQ_PAR_102 & BIT_F ) {				//ﾛｯﾄｶｳﾝﾀ2 ﾘｾｯﾄ指令(1:ﾘｾｯﾄ)

		SEQ_PAR_033 &= ~BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		SEQ_PAR_033 &= ~BIT_5;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
	}
	else {
		if (SV_PUR2SV_B41 > PV_LOTCT2_B41) {

			SEQ_PAR_033 &= ~BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
		else{
			SEQ_PAR_033 |= BIT_1;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}

		wk = SV_PUR2SV_B41;
		if (wk) {
			wk = wk - 1;
		}
		if ( wk > PV_LOTCT2_B41 ) {

			SEQ_PAR_033 &= ~BIT_5;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
		else{
			SEQ_PAR_033 |= BIT_5;					//ﾛｯﾄｶｳﾝﾀ2 ｶｳﾝﾄUP(1:ｶｳﾝﾄUP)
		}
	}

}


/*
********************************************************************************
*  Module Name:		CAMname_pon_read
*  Function Name:	電源投入時の汎用ｶﾑ名称の読込み
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-22
********************************************************************************
*/
void	CAMname_pon_read(void)
{
	UNs		*src_p, *dst_p, b_d0, b_d1;
	UNi		cnt, cnt2, cnt3;

	//汎用出力選択SW 名称を領域へコピー
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(12,  8, 11, &PV_CAMSW1_C1[0], 4);				//汎用出力選択 SW1をｺﾋﾟｰ
	disp_char_cpy(12,  8, 21, &PV_CAMSW2_C1[0], 4);				//汎用出力選択 SW2をｺﾋﾟｰ
	disp_char_cpy(12,  8, 31, &PV_CAMSW3_C1[0], 4);				//汎用出力選択 SW3をｺﾋﾟｰ
	disp_char_cpy(12,  9,  1, &PV_CAMSW4_C1[0], 4);				//汎用出力選択 SW4をｺﾋﾟｰ
	disp_char_cpy(12,  9, 11, &PV_CAMSW5_C1[0], 4);				//汎用出力選択 SW5をｺﾋﾟｰ
	disp_char_cpy(12,  9, 21, &PV_CAMSW6_C1[0], 4);				//汎用出力選択 SW6をｺﾋﾟｰ
	disp_char_cpy(12,  9, 31, &PV_CAMSW7_C1[0], 4);				//汎用出力選択 SW7をｺﾋﾟｰ
	disp_char_cpy(12, 10,  1, &PV_CAMSW8_C1[0], 4);				//汎用出力選択 SW8をｺﾋﾟｰ
	disp_char_cpy(12, 10, 11, &PV_CAMSW9_C1[0], 4);				//汎用出力選択 SW9をｺﾋﾟｰ
	disp_char_cpy(12, 10, 21, &PV_CAMSWA_C1[0], 4);				//汎用出力選択 SW10をｺﾋﾟｰ
	disp_char_cpy(12, 10, 31, &PV_CAMSWB_C1[0], 4);				//汎用出力選択 SW11をｺﾋﾟｰ
	disp_char_cpy(12, 11,  1, &PV_CAMSWC_C1[0], 4);				//汎用出力選択 SW12をｺﾋﾟｰ
	disp_char_cpy(12, 11, 11, &PV_CAMSWD_C1[0], 4);				//汎用出力選択 SW13をｺﾋﾟｰ
	disp_char_cpy(12, 11, 21, &PV_CAMSWE_C1[0], 4);				//汎用出力選択 SW14をｺﾋﾟｰ
	disp_char_cpy(12, 11, 31, &PV_CAMSWF_C1[0], 4);				//汎用出力選択 SW15をｺﾋﾟｰ
#else
	disp_char_SWcpy(199, &PV_CAMSW1_C1[0], 4);				//汎用出力選択 SW1をｺﾋﾟｰ
	disp_char_SWcpy(200, &PV_CAMSW2_C1[0], 4);				//汎用出力選択 SW2をｺﾋﾟｰ
	disp_char_SWcpy(201, &PV_CAMSW3_C1[0], 4);				//汎用出力選択 SW3をｺﾋﾟｰ
	disp_char_SWcpy(202, &PV_CAMSW4_C1[0], 4);				//汎用出力選択 SW4をｺﾋﾟｰ
	disp_char_SWcpy(203, &PV_CAMSW5_C1[0], 4);				//汎用出力選択 SW5をｺﾋﾟｰ
	disp_char_SWcpy(204, &PV_CAMSW6_C1[0], 4);				//汎用出力選択 SW6をｺﾋﾟｰ
	disp_char_SWcpy(205, &PV_CAMSW7_C1[0], 4);				//汎用出力選択 SW7をｺﾋﾟｰ
	disp_char_SWcpy(206, &PV_CAMSW8_C1[0], 4);				//汎用出力選択 SW8をｺﾋﾟｰ
	disp_char_SWcpy(207, &PV_CAMSW9_C1[0], 4);				//汎用出力選択 SW9をｺﾋﾟｰ
	disp_char_SWcpy(208, &PV_CAMSWA_C1[0], 4);				//汎用出力選択 SW10をｺﾋﾟｰ
	disp_char_SWcpy(209, &PV_CAMSWB_C1[0], 4);				//汎用出力選択 SW11をｺﾋﾟｰ
	disp_char_SWcpy(210, &PV_CAMSWC_C1[0], 4);				//汎用出力選択 SW12をｺﾋﾟｰ
	disp_char_SWcpy(211, &PV_CAMSWD_C1[0], 4);				//汎用出力選択 SW13をｺﾋﾟｰ
	disp_char_SWcpy(212, &PV_CAMSWE_C1[0], 4);				//汎用出力選択 SW14をｺﾋﾟｰ
	disp_char_SWcpy(213, &PV_CAMSWF_C1[0], 4);				//汎用出力選択 SW15をｺﾋﾟｰ
#endif

	//汎用出力選択ＳＷをチェック（複数立っていたら）
	for(cnt=0 ; cnt < 16 ; cnt++){
		src_p = Camcsr_Name_Tbl1[cnt];
		b_d0 = *src_p;
		b_d1 = BIT_0;
		for(cnt2=16, cnt3=0 ; cnt2 > 0 ; cnt2--){
			if( b_d0 & b_d1 ){
				cnt3 ++;
			}
			b_d1 <<= 1;
		}
		if(cnt3 != 1){
			*src_p = BIT_0;
		}
	}

//ロータリカム 名称を領域へコピー
	CAM_name_ref();										//ﾛｰﾀﾘｶﾑ汎用選択種別に対応したｶﾑ名称の更新

//ロータリカム 名称を対応までのデバッグモード
//	disp_char_cpy(21,  4, 0, &PV_CAMNA01_C1[0], 4);
//	disp_char_cpy(21,  5, 0, &PV_CAMNA02_C1[0], 4);
//	disp_char_cpy(21,  6, 0, &PV_CAMNA03_C1[0], 4);
//	disp_char_cpy(21,  7, 0, &PV_CAMNA04_C1[0], 4);
//	disp_char_cpy(21,  8, 0, &PV_CAMNA05_C1[0], 4);
//	disp_char_cpy(21,  9, 0, &PV_CAMNA06_C1[0], 4);
//	disp_char_cpy(21, 10, 0, &PV_CAMNA07_C1[0], 4);
//	disp_char_cpy(21, 11, 0, &PV_CAMNA08_C1[0], 4);
//	disp_char_cpy(22,  4, 0, &PV_CAMNA09_C1[0], 4);
//	disp_char_cpy(22,  5, 0, &PV_CAMNA10_C1[0], 4);
//	disp_char_cpy(22,  6, 0, &PV_CAMNA11_C1[0], 4);
//	disp_char_cpy(22,  7, 0, &PV_CAMNA12_C1[0], 4);
//	disp_char_cpy(22,  8, 0, &PV_CAMNA13_C1[0], 4);
//	disp_char_cpy(22,  9, 0, &PV_CAMNA14_C1[0], 4);
//	disp_char_cpy(22, 10, 0, &PV_CAMNA15_C1[0], 4);
//	disp_char_cpy(22, 11, 0, &PV_CAMNA16_C1[0], 4);
//ロータリカム 名称を対応までのデバッグモード


//エジェクタ 名称を領域へコピー
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(33,  2,  4, &SV_EJENAM01_C1[0], 4);		//ｴｼﾞｪｸﾀ名称1をｺﾋﾟｰ
	disp_char_cpy(33,  5,  4, &SV_EJENAM02_C1[0], 4);		//ｴｼﾞｪｸﾀ名称2をｺﾋﾟｰ
	disp_char_cpy(33,  8,  4, &SV_EJENAM03_C1[0], 4);		//ｴｼﾞｪｸﾀ名称3をｺﾋﾟｰ
	disp_char_cpy(33, 11,  4, &SV_EJENAM04_C1[0], 4);		//ｴｼﾞｪｸﾀ名称4をｺﾋﾟｰ
	disp_char_cpy(33,  4, 24, &SV_EJENAM05_C1[0], 4);		//ｴｼﾞｪｸﾀ名称5をｺﾋﾟｰ
	disp_char_cpy(33,  7, 24, &SV_EJENAM06_C1[0], 4);		//ｴｼﾞｪｸﾀ名称6をｺﾋﾟｰ
#else
	disp_char_CSRcpy(67, &SV_EJENAM01_C1[0], 4);		//ｴｼﾞｪｸﾀ名称1をｺﾋﾟｰ
	disp_char_CSRcpy(70, &SV_EJENAM02_C1[0], 4);		//ｴｼﾞｪｸﾀ名称2をｺﾋﾟｰ
	disp_char_CSRcpy(73, &SV_EJENAM03_C1[0], 4);		//ｴｼﾞｪｸﾀ名称3をｺﾋﾟｰ
	disp_char_CSRcpy(76, &SV_EJENAM04_C1[0], 4);		//ｴｼﾞｪｸﾀ名称4をｺﾋﾟｰ
	disp_char_CSRcpy(79, &SV_EJENAM05_C1[0], 4);		//ｴｼﾞｪｸﾀ名称5をｺﾋﾟｰ
	disp_char_CSRcpy(82, &SV_EJENAM06_C1[0], 4);		//ｴｼﾞｪｸﾀ名称6をｺﾋﾟｰ
#endif

	FRAM_csum_set();										//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

//項目番号 名称を領域へコピー
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(36, 6, 4, &PV_KOUMOKU1_NAME[0], 8);		//項目番号1をｺﾋﾟｰ
	disp_char_cpy(36, 7, 4, &PV_KOUMOKU2_NAME[0], 8);		//項目番号2をｺﾋﾟｰ
	disp_char_cpy(36, 8, 4, &PV_KOUMOKU3_NAME[0], 8);		//項目番号3をｺﾋﾟｰ
	disp_char_cpy(36, 9, 4, &PV_KOUMOKU4_NAME[0], 8);		//項目番号4をｺﾋﾟｰ
#else
	disp_char_CSRcpy(131, &PV_KOUMOKU1_NAME[0], 8);		//項目番号1をｺﾋﾟｰ
	disp_char_CSRcpy(132, &PV_KOUMOKU2_NAME[0], 8);		//項目番号2をｺﾋﾟｰ
	disp_char_CSRcpy(133, &PV_KOUMOKU3_NAME[0], 8);		//項目番号3をｺﾋﾟｰ
	disp_char_CSRcpy(134, &PV_KOUMOKU4_NAME[0], 8);		//項目番号4をｺﾋﾟｰ
#endif

//機能選択 名称を領域へコピー
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(14, 2,  3, &PV_KINOU01_NAE[0], 8);		//機能選択項目1をｺﾋﾟｰ
	disp_char_cpy(14, 3,  3, &PV_KINOU02_NAE[0], 8);		//機能選択項目2をｺﾋﾟｰ
	disp_char_cpy(14, 4,  3, &PV_KINOU03_NAE[0], 8);		//機能選択項目3をｺﾋﾟｰ
	disp_char_cpy(14, 5,  3, &PV_KINOU04_NAE[0], 8);		//機能選択項目4をｺﾋﾟｰ
	disp_char_cpy(14, 6,  3, &PV_KINOU05_NAE[0], 8);		//機能選択項目5をｺﾋﾟｰ
	disp_char_cpy(14, 7,  3, &PV_KINOU06_NAE[0], 8);		//機能選択項目6をｺﾋﾟｰ
	disp_char_cpy(14, 8,  3, &PV_KINOU07_NAE[0], 8);		//機能選択項目7をｺﾋﾟｰ
	disp_char_cpy(14, 9,  3, &PV_KINOU08_NAE[0], 8);		//機能選択項目8をｺﾋﾟｰ
	disp_char_cpy(14, 2, 23, &PV_KINOU09_NAE[0], 8);		//機能選択項目9をｺﾋﾟｰ
	disp_char_cpy(14, 3, 23, &PV_KINOU10_NAE[0], 8);		//機能選択項目10をｺﾋﾟｰ
	disp_char_cpy(14, 4, 23, &PV_KINOU11_NAE[0], 8);		//機能選択項目11をｺﾋﾟｰ
	disp_char_cpy(14, 5, 23, &PV_KINOU12_NAE[0], 8);		//機能選択項目12をｺﾋﾟｰ
	disp_char_cpy(14, 6, 23, &PV_KINOU13_NAE[0], 8);		//機能選択項目13をｺﾋﾟｰ
	disp_char_cpy(14, 7, 23, &PV_KINOU14_NAE[0], 8);		//機能選択項目14をｺﾋﾟｰ
	disp_char_cpy(14, 8, 23, &PV_KINOU15_NAE[0], 8);		//機能選択項目15をｺﾋﾟｰ
	disp_char_cpy(14, 9, 23, &PV_KINOU16_NAE[0], 8);		//機能選択項目16をｺﾋﾟｰ
#else
	disp_char_CSRcpy(310, &PV_KINOU01_NAE[0], 8);		//機能選択項目1をｺﾋﾟｰ
	disp_char_CSRcpy(311, &PV_KINOU02_NAE[0], 8);		//機能選択項目2をｺﾋﾟｰ
	disp_char_CSRcpy(312, &PV_KINOU03_NAE[0], 8);		//機能選択項目3をｺﾋﾟｰ
	disp_char_CSRcpy(313, &PV_KINOU04_NAE[0], 8);		//機能選択項目4をｺﾋﾟｰ
	disp_char_CSRcpy(314, &PV_KINOU05_NAE[0], 8);		//機能選択項目5をｺﾋﾟｰ
	disp_char_CSRcpy(315, &PV_KINOU06_NAE[0], 8);		//機能選択項目6をｺﾋﾟｰ
	disp_char_CSRcpy(316, &PV_KINOU07_NAE[0], 8);		//機能選択項目7をｺﾋﾟｰ
	disp_char_CSRcpy(317, &PV_KINOU08_NAE[0], 8);		//機能選択項目8をｺﾋﾟｰ
	disp_char_CSRcpy(318, &PV_KINOU09_NAE[0], 8);		//機能選択項目9をｺﾋﾟｰ
	disp_char_CSRcpy(319, &PV_KINOU10_NAE[0], 8);		//機能選択項目10をｺﾋﾟｰ
	disp_char_CSRcpy(320, &PV_KINOU11_NAE[0], 8);		//機能選択項目11をｺﾋﾟｰ
	disp_char_CSRcpy(321, &PV_KINOU12_NAE[0], 8);		//機能選択項目12をｺﾋﾟｰ
	disp_char_CSRcpy(322, &PV_KINOU13_NAE[0], 8);		//機能選択項目13をｺﾋﾟｰ
	disp_char_CSRcpy(323, &PV_KINOU14_NAE[0], 8);		//機能選択項目14をｺﾋﾟｰ
	disp_char_CSRcpy(324, &PV_KINOU15_NAE[0], 8);		//機能選択項目15をｺﾋﾟｰ
	disp_char_CSRcpy(325, &PV_KINOU16_NAE[0], 8);		//機能選択項目16をｺﾋﾟｰ
#endif

}


/*
********************************************************************************
*  Module Name:		FRAM_csum_set(旧:SUM_CHK_SET)
*  Function Name:	ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-23
********************************************************************************
*/
void	FRAM_csum_set(void)
{
	UNl		*src_p, scode;
	UNi		cnt;

	scode = 0;									//ｸﾘｱ
	src_p = (UNl *)&SEQ_016_SV;					//ﾌﾗｼｭRAM領域の設定値 ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &PV_TOTLC1_B3 - (UNl *)&SEQ_016_SV;	//ﾌﾗｼｭRAM領域の設定値 ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

	SUM_CHK = scode;							//設定値サムチェックコード

}


/*
********************************************************************************
*  Module Name:		FRAM_csum_chk(旧:SUM_CHK_CHK)
*  Function Name:	ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-23
********************************************************************************
*/
void	FRAM_csum_chk(void)
{
	UNl		*src_p, scode;
	UNi		cnt;

	scode = 0;									//ｸﾘｱ
	src_p = (UNl *)&SEQ_016_SV;					//ﾌﾗｼｭRAM領域の設定値 ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &PV_TOTLC1_B3 - (UNl *)&SEQ_016_SV;	//ﾌﾗｼｭRAM領域の設定値 ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

	if(SUM_CHK != scode ){						//設定値サムチェックコード チェック
		SEQ_PAR_079 |= BIT_0;					//設定値ﾁｪｯｸｻﾑ異常
	}
}


/*
********************************************************************************
*  Module Name:		FRAM_KAT_csum_set(旧:SUM_CHK_SET)
*  Function Name:	ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-23
********************************************************************************
*/
void	FRAM_KAT_csum_set(void)
{
	UNs		*src_p, scode;
	UNi		cnt;

	scode = 0;									//ｸﾘｱ
	src_p = &KAT_NAME_01[0];					//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];	//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

//V06n
	src_p = &KAT_NAME_101[0];					//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];	//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

	SUM_CHK_KAT = scode;						//型ﾃﾞｰﾀ 名称＆メモ サムチェックコード

}


/*
********************************************************************************
*  Module Name:		FRAM_KAT_csum_chk(旧:SUM_CHK_CHK)
*  Function Name:	ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-23
********************************************************************************
*/
void	FRAM_KAT_csum_chk(void)
{
	UNs		*src_p, scode;
	UNi		cnt;

	scode = 0;									//ｸﾘｱ
	src_p = &KAT_NAME_01[0];					//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];	//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

//V06n
	src_p = &KAT_NAME_101[0];					//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ﾄｯﾌﾟｱﾄﾞﾚｽ
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];	//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモ ENDｱﾄﾞﾚｽ - ﾄｯﾌﾟｱﾄﾞﾚｽ

	while(cnt --){								//BCC作成
		scode += *src_p++;
	}

	if(SUM_CHK_KAT != scode ){					//型ﾃﾞｰﾀ 名称＆メモ サムチェックコード
		SEQ_PAR_079 |= BIT_0;					//設定値ﾁｪｯｸｻﾑ異常
	}

}


/*
********************************************************************************
*  Module Name:		Power_down
*  Function Name:	パワーダウン処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-10-07
********************************************************************************
*/
void	Power_down(void)
{

	FRAM_csum_set();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
	FRAM_KAT_csum_set();			//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	GAMEN_NO = 5;					//瞬停画面
	GAMEN_disp();					//画面表示

}


/*
********************************************************************************
*  Module Name:		PV_CHANGE_hanten
*  Function Name:	反転仕様時のＰＶ変換
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2003-02-04
********************************************************************************
*/


void	PV_CHANGE_hanten(void)
{
	UNl		cnv_bf1,cnv_bf2,cnv_bf3;

	cnv_bf1 = PVP_NOW_POSI000;								//下限上高さPV
	cnv_bf2 = PVP_DYHITO_POS;								//下限位置PV
	cnv_bf3 = PVP_SLIDE_POS;								//生産下限PV

	if( SEQ_050_SV & BIT_1 ) {								//反転　？

		cnv_bf1 = cnv_bf1 - SV_NEG_OFS_LNG;					//下限上高さPV＝下死点高さ－下限距離
		if( cnv_bf1 & 0x80000000 ) cnv_bf1 = 0;				//マイナスなら０

		cnv_bf2 = cnv_bf2 + SV_NEG_OFS_LNG;					//下限位置PV＝ﾀﾞｲﾊｲﾄPV＋下限距離

		/* V01  */
		cnv_bf3 = cnv_bf3 + SV_NEG_OFS_LNG;					//生産下限PV＝ﾀﾞｲﾊｲﾄPV＋下限距離

	}

	PV0_NOW_POSI000 = cnv_bf1;
	PV0_DYHITO_POS = cnv_bf2;
	PV0_SLIDE_POS = cnv_bf3;

//V01m	/* V01  */
//	if (SEQ_PAR_200 & BIT_5) {						//段取寸動？
//		PV0_NOWPOSI_SLIDE = PV0_NOW_POSI000;		//段取寸動時は下限上高さPVを表示
//	}
//	else {
//		PV0_NOWPOSI_SLIDE = PV0_SLIDE_POS;			//それ以外は生産下限PVを表示
//	}
	if (SEQ_PAR_200 & BIT_5) {						//段取寸動？
		cnv_bf2 = cnv_mm_inch(PV0_NOW_POSI000, 1);	//単位切替(mm→mm/INCH)
	}
	else {
		cnv_bf2 = cnv_mm_inch(PV0_SLIDE_POS, 1);	//単位切替(mm→mm/INCH)
	}
	if( SEQ_016_SV & BIT_6 ) { }					//単位切替 mm/INCH 単位系(1:INCH)
	else {
		if (SV_POINT_A1 == 1) {
			cnv_bf2 /= 10;
		}
	}
	PV0_NOWPOSI_SLIDE = cnv_bf2;				//段取寸動時は下限上高さPVを表示

//V01m	if( SEQ_PAR_107 & BIT_13 ){						//生産画面の下限部にポジショナ表示？	/* V01l_b */
//		PV0_KAGEN_POSITIONER = PV_DAIHAI_B5*10;		//ポジショナ
//	}
//	else {
//		PV0_KAGEN_POSITIONER = PV0_DYHITO_POS;		//下限
//	}
	if( SEQ_PAR_107 & BIT_13 ){						//生産画面の下限部にポジショナ表示？
		PV0_KAGEN_POSITIONER = PV_DAIHAI_B5;		//ポジショナ
	}
	else {
		cnv_bf2 = cnv_mm_inch(PV0_DYHITO_POS, 1);		//単位切替(mm→mm/INCH)
		if( SEQ_016_SV & BIT_6 ) { }					//単位切替 mm/INCH 単位系(1:INCH)
		else {
			if (SV_POINT_A1 == 1) {
				cnv_bf2 /= 10;
			}
		}
		PV0_KAGEN_POSITIONER = cnv_bf2;				//下限
	}



}




/*
********************************************************************************
*  Module Name:		debug_dat_mng
*  Function Name:	ﾃﾞﾊﾞｯｸﾞ･ﾓﾆﾀ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2002-11-12
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define		SH2_DPRMTOP		0x00600000
#define		SH2_SRAMTOP		0x00400000
#define		SH2_FROMTOP		0x00500000
#define		SH2_FRAMTOP		0x00800000
#define		SH2_OPRMTOP		0x00870000
#else
#define		SH2_DPRMTOP		0xB8000000
#define		SH2_SRAMTOP		0xAC090000
#define		SH2_FROMTOP		0xB9000000
#define		SH2_FRAMTOP		0xB4000000
#define		SH2_OPRMTOP		0xB5000000
#endif
void	debug_dat_mng(void)
{
	UNs	*bf_p;

	if (GAMEN_NO == 70) {

		SVP_DEB_SEL0 = SV_DEB_SEL0;					//領域選択 0
		SVP_DEB_ADR0 = (SV_DEB_ADR0 & 0xfffffffe);	//相対ｱﾄﾞﾚｽ 0
		SVP_DEB_SEL1 = SV_DEB_SEL1;					//領域選択 1
		SVP_DEB_ADR1 = (SV_DEB_ADR1 & 0xfffffffe);	//相対ｱﾄﾞﾚｽ 1
		SVP_DEB_SEL2 = SV_DEB_SEL2;					//領域選択 2
		SVP_DEB_ADR2 = (SV_DEB_ADR2 & 0xfffffffe);	//相対ｱﾄﾞﾚｽ 2
		SVP_DEB_SEL3 = SV_DEB_SEL3;					//領域選択 3
		SVP_DEB_ADR3 = (SV_DEB_ADR3 & 0xfffffffe);	//相対ｱﾄﾞﾚｽ 3
		SVP_DEB_SEL4 = SV_DEB_SEL4;					//領域選択 4
		SVP_DEB_ADR4 = (SV_DEB_ADR4 & 0xfffffffe);	//相対ｱﾄﾞﾚｽ 4

		if ( SVP_DEB_SEL0 < 9 ) {
			switch(SVP_DEB_SEL0) {
				case 0:								//SH2-DPRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_DPRMTOP);
					break;
				case 1:								//SH2-SRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_SRAMTOP);
					break;
				case 2:								//SH2-FROM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_FROMTOP);
					break;
				case 3:								//SH2-FRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_FRAMTOP);
					break;
				case 4:								//SH2-OPRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT0 = *bf_p++;
			PVP_DEB_DAT1 = *bf_p;
		}
		if ( SVP_DEB_SEL1 < 9 ) {
			switch(SVP_DEB_SEL1) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT2 = *bf_p++;
			PVP_DEB_DAT3 = *bf_p;
		}
		if ( SVP_DEB_SEL2 < 9 ) {
			switch(SVP_DEB_SEL2) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT4 = *bf_p++;
			PVP_DEB_DAT5 = *bf_p;
		}
		if ( SVP_DEB_SEL3 < 9 ) {
			switch(SVP_DEB_SEL3) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT6 = *bf_p++;
			PVP_DEB_DAT7 = *bf_p;
		}
		if ( SVP_DEB_SEL4 < 9 ) {
			switch(SVP_DEB_SEL4) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT8 = *bf_p++;
			PVP_DEB_DAT9 = *bf_p;
		}
	}
}



/*
********************************************************************************
*  Module Name:		his_dat_mng
*  Function Name:	異常履歴ﾃﾞｰﾀ転送処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2003-07-09
********************************************************************************
*/
void	his_dat_mng(void)
{
	UNs	w2b;
	UNl	w4b;

	SVP_MONALM_S01 = SV_MONALM_S01;
	SVP_MONALM_S02 = SV_MONALM_S02;
	SVP_MONALM_S03 = SV_MONALM_S03;
	SVP_MONALM_S04 = SV_MONALM_S04;

	if (GAMEN_NO == 69) {
		PV0_MONALM_P01 = PVP_MONALM_P01;
		PV0_MONALM_P02 = PVP_MONALM_P02;
		PV0_MONALM_P03 = PVP_MONALM_P03;
		PV0_MONALM_P04 = PVP_MONALM_P04;
		PV0_MONALM_A01 = PVP_MONALM_A01;
		PV0_MONALM_A02 = PVP_MONALM_A02;
		PV0_MONALM_A03 = PVP_MONALM_A03;
		PV0_MONALM_A04 = PVP_MONALM_A04;
		PV0_MONALM_A05 = PVP_MONALM_A05;
		PV0_MONALM_A06 = PVP_MONALM_A06;
		PV0_MONALM_A07 = PVP_MONALM_A07;
		PV0_MONALM_A08 = PVP_MONALM_A08;

		PV0_MONALM_B01 = PVP_MONALM_B01;
		PV0_MONALM_B01_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B01 & 0x8000) != 0 ) {
			PV0_MONALM_B01 = 0 - PV0_MONALM_B01;
			PV0_MONALM_B01_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B02 = PVP_MONALM_B02;
		PV0_MONALM_B02_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B02 & 0x8000) != 0 ) {
			PV0_MONALM_B02 = 0 - PV0_MONALM_B02;
			PV0_MONALM_B02_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B03 = PVP_MONALM_B03;
		PV0_MONALM_B03_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B03 & 0x8000) != 0 ) {
			PV0_MONALM_B03 = 0 - PV0_MONALM_B03;
			PV0_MONALM_B03_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B04 = PVP_MONALM_B04;
		PV0_MONALM_B04_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B04 & 0x8000) != 0 ) {
			PV0_MONALM_B04 = 0 - PV0_MONALM_B04;
			PV0_MONALM_B04_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B05 = PVP_MONALM_B05;
		PV0_MONALM_B05_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B05 & 0x8000) != 0 ) {
			PV0_MONALM_B05 = 0 - PV0_MONALM_B05;
			PV0_MONALM_B05_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B06 = PVP_MONALM_B06;
		PV0_MONALM_B06_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B06 & 0x8000) != 0 ) {
			PV0_MONALM_B06 = 0 - PV0_MONALM_B06;
			PV0_MONALM_B06_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B07 = PVP_MONALM_B07;
		PV0_MONALM_B07_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B07 & 0x8000) != 0 ) {
			PV0_MONALM_B07 = 0 - PV0_MONALM_B07;
			PV0_MONALM_B07_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B08 = PVP_MONALM_B08;
		PV0_MONALM_B08_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B08 & 0x8000) != 0 ) {
			PV0_MONALM_B08 = 0 - PV0_MONALM_B08;
			PV0_MONALM_B08_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C01 = PVP_MONALM_C01;
		PV0_MONALM_C01_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C01 & 0x80000000) != 0 ) {
			PV0_MONALM_C01 = 0 - PV0_MONALM_C01;
			PV0_MONALM_C01_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C02 = PVP_MONALM_C02;
		PV0_MONALM_C02_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C02 & 0x80000000) != 0 ) {
			PV0_MONALM_C02 = 0 - PV0_MONALM_C02;
			PV0_MONALM_C02_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C03 = PVP_MONALM_C03;
		PV0_MONALM_C03_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C03 & 0x80000000) != 0 ) {
			PV0_MONALM_C03 = 0 - PV0_MONALM_C03;
			PV0_MONALM_C03_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C04 = PVP_MONALM_C04;
		PV0_MONALM_C04_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C04 & 0x80000000) != 0 ) {
			PV0_MONALM_C04 = 0 - PV0_MONALM_C04;
			PV0_MONALM_C04_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C05 = PVP_MONALM_C05;
		PV0_MONALM_C05_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C05 & 0x80000000) != 0 ) {
			PV0_MONALM_C05 = 0 - PV0_MONALM_C05;
			PV0_MONALM_C05_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C06 = PVP_MONALM_C06;
		PV0_MONALM_C06_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C06 & 0x80000000) != 0 ) {
			PV0_MONALM_C06 = 0 - PV0_MONALM_C06;
			PV0_MONALM_C06_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C07 = PVP_MONALM_C07;
		PV0_MONALM_C07_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C07 & 0x80000000) != 0 ) {
			PV0_MONALM_C07 = 0 - PV0_MONALM_C07;
			PV0_MONALM_C07_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C08 = PVP_MONALM_C08;
		PV0_MONALM_C08_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C08 & 0x80000000) != 0 ) {
			PV0_MONALM_C08 = 0 - PV0_MONALM_C08;
			PV0_MONALM_C08_SIGN = DISP_MN << 8;
		}
	}
}


/*
********************************************************************************
*  Module Name:		taikikaku_chg_mng
*  Function Name:	待機角変更処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2004-05-19		V01i
********************************************************************************
*/
void	taikikaku_chg_mng(void)
{
	UNs		w2b;
	UNs		*w2b_p;
	UNs		seq;
	
	seq = SEQ_PAR_201;

	if (CB_SYS_PARAM279 == 1) {							// 待機点２無効				V06m	2012/09/24
		seq &= ~cBIT5;
	}

	if (CB_SYS_PARAM045 == 1) {
		w2b = 0;
		if ( seq & (BIT_4+BIT_5+BIT_6) ) {
			if(seq & BIT_4) {							// 待機角度１選択？
				w2b =1;
				w2b_p = &SV_TAIKI1_A12;
			}
			else if(seq & BIT_5) {						// 待機角度２選択？
				w2b =2;
				w2b_p = &SV_TAIKI2_A12;
			}
			else if(seq & BIT_6) {						// 待機角度３選択？
				w2b =3;
				w2b_p = &SV_TAIKI3_A12;
			}
			else {
				w2b_p = &SV_TAIKI1_A12;					// DUMMY
			}

			SV_TAIKIKAKU_SRV = *w2b_p;
			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

			if(SEQ_050_SV & BIT_1) {		//反転　？
				SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
			}
			SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)

			SVP_UPAREA_DIG0		= SV_TAIKIKAKU_SRV;				/* 待機点角度			*/
			if( SEQ_050_SV & BIT_1 ) {								//反転　？
				SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* 待機点位置 */
			}
			else {
				SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* 待機点位置			*/
			}

			if (TAIKIKAKU_CHG_FLG != w2b)
			{											// 待機角度選択変わった？
				TAIKIKAKU_CHG_FLG = w2b;
//V01m_a				SV_TAIKIKAKU_SRV = *w2b_p;

//V01m_a				SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

//V01m_a				if(SEQ_050_SV & BIT_1) {		//反転　？
//V01m_a					SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
//V01m_a				}
//V01m_a				SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)

				SVSW_CHG_FLG |=  BLK_MOT;
				if ( (GAMEN_NO == 3) || (GAMEN_NO == 4) || (GAMEN_NO == 6) ||
					 (GAMEN_NO == 28) || (GAMEN_NO == 29) || (GAMEN_NO == 30) ) {
					GAMNE_REDISP_COD = 0xff;								//画面再表示要求
				}
			}
		}
	}
}



/*
********************************************************************************
*  Module Name:		FURIKO_Cancel_mng
*  Function Name:	振子非表示指令の処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2013-02-22		V06p
********************************************************************************
*/
void	FURIKO_Cancel_mng(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= FURIKO_SEQ_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & FURIKO_SEQ_LST;				// chg & old = ofe
	FURIKO_SEQ_LST = seq_bit;

	if( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30 ) {
		if ( (seq_one & BIT_15) || (seq_ofe & BIT_15) ) {
			if ( (SEQ_050_SV & BIT_2) == 0 ) {
				GAMNE_REDISP_COD = 0xff;
			}
		}
	}

}


/*
********************************************************************************
*  Module Name:		Gamen_Redisp_mng
*  Function Name:	画面再表示処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:島村		ON:2004-05-19		V01i
********************************************************************************
*/
void	Gamen_Redisp_mng(void)
{
// 2005-08-26 V01s 反映指令の再描画ｲﾝﾀｰﾛｯｸはずす	if (CB_SYS_PARAM045 == 1) {
		if (GAMNE_REDISP_COD != 0) {
			GAMNE_REDISP_COD = 0;
			GAMEN_disp();								//画面再表示
		}
//	}
}


/*
********************************************************************************
*  Module Name:		KAT_ENB_GAMEN001_disp
*  Function Name:	GAMEN001の時に型ﾃﾞｰﾀ管理が有効になったときの画面再表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		電源投入時に画面001を表示した時、型番号＆名称が表示しない不具合対策
*					原因は表示する時に、まだｼｰｹﾝｽが完全に動いていないので、SEQ_107のBIT_0
*					がONしていないため。
*
*  履 歴	:Shima		ON:2004-05-26			V01j
********************************************************************************
*/
void	KAT_ENB_GAMEN001_disp(void)
{
	UNs		xy_no;

	if (SEQ_PAR_107_BAK & BIT_0) { /*既に有効なら何もしない*/ }		// 型ﾃﾞｰﾀ管理既に有効？
	else{
		if (SEQ_PAR_107 & BIT_0)					// 型ﾃﾞｰﾀ管理有効になった？
		{											// はい
			SEQ_PAR_107_BAK = SEQ_PAR_107;
			if (GAMEN_NO == 1)
			{
//SIT4				disp_all_s(GAMEN_NO, 0x00, 0x00);	//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
//				WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ
//				Alltbl_set();						//情報ﾃｰﾌﾞﾙの作成
//				Under_grph();						//下段のグラフィックセット		/* V01w */
//				xy_no = 1 | (21<<4) | (6<<10);		// 1行目/21桁目から6文字表示
//				Lcd_cr(0, xy_no, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示
//				xy_no = 2 | (21<<4) | (4<<10);		// 2行目/21桁目から6文字表示
//				Lcd_cr(0, xy_no, &LCD_WORK1[0][0][0]);		//ｷｬﾗ単位表示

				GAMEN_disp();								//画面再表示
				
			}
			if ( (GAMEN_NO == 11) || (GAMEN_NO == 17) )		//V01h_c
			{
//SIT4				disp_all_s(GAMEN_NO, 0x00, 0x00);	//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
//				WDT_Rifresh();						//ｳｫｯﾁﾄﾞｯｸﾀｲﾏ- ﾘﾌﾚｯｼｭ
//				Alltbl_set();						//情報ﾃｰﾌﾞﾙの作成
//				Lcd_line(00, 1, E_line_bf, &LCD_WORK1[0][0][0]);		//行表示(LCD1)

				GAMEN_disp();								//画面再表示

			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Sampring_Disp
*  Function Name:	ｻﾝﾌﾟﾘﾝｸﾞ中を示す●表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ｻﾝﾌﾟﾘﾝｸﾞ中を示す●表示
*
*  履 歴	:Shima		ON:2006-07-13			V01v
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	Sampring_Disp(void)
{
	U1b	*src_p;
	U2b	*dst_p;
	U2b	k;

	if (GAMEN_NO != 1){
		return;
	}
	if (SEQ_PAR_101 & BIT_13) {
		src_p = kan_rom_set(0x217c);				//"●"(0x217c) JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[1][0][0];
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p = dst_p+39;
		}
	}
	else {
		src_p = kan_rom_set(0x2121);				//"　"(0x2121) JIS変換→漢字ROMｱﾄﾞﾚｽ
		dst_p = &LCD_WORK1[1][0][0];
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p = dst_p+39;
		}
	}
	Lcd_cr(00, 0x0801, &LCD_WORK1[0][0][0]);					//1行目,0桁目,2文字を表示する。
}
#else
void	Sampring_Disp(void)
{
	UNs		MARU, col;

	MARU  = 0x819C;	//●

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_101 & BIT_13) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//ｽﾍﾟｰｽ
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		0,						/*t_p->X_POS,*/
		32,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
	disp_moji_s_rif (
		2,				/*t_p->M_LEN,*/
		0,				/*t_p->X_POS,*/
		32,				/*t_p->Y_POS,*/
		0x0101			/*t_p->SIZE,*/
		);
}
#endif

/*
********************************************************************************
*  Module Name:		Trend_disp
*  Function Name:	ﾄﾚﾝﾄﾞ計測中を示す■表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ﾄﾚﾝﾄﾞ計測中を示す■表示
*
*  履 歴	:Shima
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	Trend_disp(void)
{
}

void	Trend_stop(void)
{
}

#else

void	Trend_disp(void)
{
	UNs		MARU, col;

	MARU  = 0x81a1;	//■

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_101 & BIT_12) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//ｽﾍﾟｰｽ
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		0,						/*t_p->X_POS,*/
		48,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
	disp_moji_s_rif (
		2,				/*t_p->M_LEN,*/
		0,				/*t_p->X_POS,*/
		48,				/*t_p->Y_POS,*/
		0x0101			/*t_p->SIZE,*/
		);
}

void	Trend_stop(void)
{
	UNs		MARU, col;

	if (SEQ_PAR_101 & BIT_11)				//トレンド停止？
	{
		if (SEQ_056_SV & BIT_11)			//トレンド入ＯＮ中
		{
			SEQ_056_SV &= ~BIT_11;			//トレンド入→切
			if (GAMEN_NO == 66)				//トレンド画面表示中？
			{
				GAMEN_disp();				//画面再表示
			}
			SVSW_CHG_FLG |= 0x0008;
		}
	}
}
#endif

/*
********************************************************************************
*  Module Name:		KASIN_mark_Disp
*  Function Name:	加振制御実行を示す◆表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:		加振制御実行を示す◆表示
*
*  履 歴	:Shima		ON:2010/08/30	V05r
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	KASIN_mark_Disp(void)
{
}

#else

void	KASIN_mark_Disp(void)
{
	UNs		MARU, col;

	MARU  = 0x819F;	//◆

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_113 & BIT_4) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//ｽﾍﾟｰｽ
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		16,						/*t_p->X_POS,*/
		32,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}


#endif


void cop2_pvdata_sin(void)
{
	if ( (PVP_ZURE_PLS & 0x8000) == 0) {
		PVW_ZURE_PLS_SIN = 0;
		PVW_ZURE_PLS = PVP_ZURE_PLS;
	}
	else {
		PVW_ZURE_PLS_SIN = 1;
		PVW_ZURE_PLS = PVP_ZURE_PLS * -1;
	}

	if ( (PVP_ZURE_RNA & 0x8000) == 0) {
		PVW_ZURE_RNA_SIN = 0;
		PVW_ZURE_RNA = PVP_ZURE_RNA;
	}
	else {
		PVW_ZURE_RNA_SIN = 1;
		PVW_ZURE_RNA = PVP_ZURE_RNA * -1;
	}

	if ( (SVB_BAKORG_PLS1 & 0x80000000) == 0) {
		PVW_BAKORG_SIN1 = 0;
		SVBW_BAKORG_PLS1 = SVB_BAKORG_PLS1;
	}
	else {
		PVW_BAKORG_SIN1 = 1;
		SVBW_BAKORG_PLS1 = SVB_BAKORG_PLS1 * -1;
	}

	if ( (SVB_BAKORG_PLS2 & 0x80000000) == 0) {
		PVW_BAKORG_SIN2 = 0;
		SVBW_BAKORG_PLS2 = SVB_BAKORG_PLS2;
	}
	else {
		PVW_BAKORG_SIN2 = 1;
		SVBW_BAKORG_PLS2 = SVB_BAKORG_PLS2 * -1;
	}

	if ( PVP_RNABUP_ENB == 1 )
	{
		PV_RENIA_BUP1	=	PVP_RENIA_BUP1;//リニアスケールバックアップ用
		PV_RENIA_BUP2	=	PVP_RENIA_BUP2;//リニアスケールバックアップ用
		PV_RENIA_BUP3	=	PVP_RENIA_BUP3;//リニアスケールバックアップ用
		PV_RENIA_BUP4	=	PVP_RENIA_BUP4;//リニアスケールバックアップ用
	}

	if ( CMD_KJTECH_DSP1 != 0 )			// V02a
	{
		PV_ARA1_KAJ_T2	=	PVP_ARA1_KAJ_T2;
	}
}

void real_kajyu_check(void)
{
	UNs		ww0, ww1;

	ww0 = 0;
	if ( CMD_KJTECH_DSP1 != 0 )
	{
		ww1 = PVP_ARA1_KAJ_T2 + GMN_PAR011;
		if (ww1 < SV_KAJYUU_OBJP )				// 変更大きすぎ？
		{
			ww0 = 0xff;
		}
		ww1 = PVP_ARA1_KAJ_T2 - GMN_PAR011;
		if(ww1 & 0x8000)
		{
			ww1 = 0;
		}
		if (ww1 > SV_KAJYUU_OBJP )				// 変更小さすぎ？
		{
			ww0 = 0xff;
		}
		if (ww0 != 0) {
			SEQ_PAR_050 |= BIT_11;
		}
		else {
			SEQ_PAR_050 &= ~BIT_11;							// 変更大きすぎず小さすぎず
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEIDOUSEINOU_mng
*  Function Name:	制動性能試験切換え
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
void	SEIDOUSEINOU_mng(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;

	seq_chg = seq_bit = SEQ_PAR_113 & (BIT_2+BIT_1+BIT_0);		// new
	seq_chg ^= SEIDOU_SEQ_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & SEIDOU_SEQ_LST;				// chg & old = ofe
	SEIDOU_SEQ_LST = seq_bit;

	/*** 表示切換え処理 ***/
	if (seq_one & BIT_2)		Disp_seidouseinou(1, LCD_VRAM);		//制動性能表示
	if (seq_ofe & BIT_2)		Disp_seidouseinou(0, LCD_VRAM);		//通常表示


#if 0	//2011/09/12  変更  V06h
	/*** 制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ処理 ***/
	if (seq_one & BIT_0)	PVTIM_seidouseinou_inter = SV_INTER_TIM * 60;		//ﾀｲﾏﾌﾟﾘｾｯﾄ(min)
	if (seq_bit & BIT_0)
	{
		if (PVTIM_seidouseinou_inter == 0)
		{
			SEQ_PAR_058 |= BIT_0;
		}
	}
	if (seq_ofe & BIT_0)	SEQ_PAR_058 &= ~BIT_0;
	
	/*** 制動性能試験予告ﾀｲﾏ処理 ***/
//V06	if (seq_one & BIT_1)	PVTIM_seidouseinou_yokok = GMN_PAR040 * 60;			//ﾀｲﾏﾌﾟﾘｾｯﾄ(min)
	if (seq_one & BIT_1)	PVTIM_seidouseinou_yokok = (SV_INTER_TIM - GMN_PAR040) * 60;			//ﾀｲﾏﾌﾟﾘｾｯﾄ(min)
	if (seq_bit & BIT_1)
	{
		if (PVTIM_seidouseinou_yokok == 0)
		{
			SEQ_PAR_058 |= BIT_1;
		}
	}
	if (seq_ofe & BIT_1)	SEQ_PAR_058 &= ~BIT_1;
#endif

	/*** 制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ処理 ***/
	if (seq_one & BIT_1) {
		PV_INTER_TIM = GMN_PAR039 * 60;		//ﾀｲﾏﾌﾟﾘｾｯﾄ(min)
	}
	if (PV_INTER_TIM == 0) {
		SEQ_PAR_058 |= BIT_0;
	}
	else {
		SEQ_PAR_058 &= ~BIT_0;
	}

	/*** 制動性能試験予告ﾀｲﾏ処理 ***/
	if ( PV_INTER_TIM <= (GMN_PAR040 * 60) ) {
		SEQ_PAR_058 |= BIT_1;
	}
	else {
		SEQ_PAR_058 &= ~BIT_1;
	}

	PV0_INTER_TIM = PV_INTER_TIM / 60;


	/*** 制動性能試験ｳｨﾝﾄﾞｳ表示処理 ***/
	seq_chg = seq_bit = SEQ_PAR_103 & BIT_11;		// new
	seq_chg ^= SEIDOU_DSP_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & SEIDOU_DSP_LST;				// chg & old = ofe
	SEIDOU_DSP_LST = seq_bit;

	if (seq_bit & BIT_11)
	{
		if (seq_one & BIT_11)
		{
			if (GAMEN_NO != 1) 
			{
				SEI_csr_ichk();							//生産カーソル位置初期化
				CSR_FLG = 0;							//ホームポジションセット
				disp_stg = 00;							//生産画面
				disp_stg_sel = E_sstg_init;				//生産[基本]へ
				GAMEN_NO = 1;
				GAMEN_disp();						//画面表示
			}
			disp_stg_sel = E_sstg_seidou;			//生産[制動試験WIN]へ
			WINDOW_NO = 21;
			WIN_gamen_disp();						//ウインドウ画面表示
		}
	}
	else
	{
		SEQ_PAR_058 &= ~BIT_4;

		if (seq_ofe & BIT_11)
		{
			if( DSET_SW_FLG & BIT_10 ) 
			{
				disp_stg = 02;							//データ設定画面
				disp_stg_sel = E_dstg_init;				//データ設定[基本]へ
				GAMEN_NO = 17;
				GAMEN_disp();						//画面表示
			}
			else if( 00 != (SEQ_PAR_101 & BIT_10) )
			{
				DAN_csr_ichk();						//段取カーソル位置初期化
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00 )
				{
					DAN_KEY_FLG = 0xff;				//型段取キーにて高機能型画面移動時の処理
					disp_stg = 01;					//段取画面
					disp_stg_sel = E_kstg_init;		//段取[基本]へ
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10)
					{
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//画面表示
				}
				else
				{
					SEI_csr_ichk();							//生産カーソル位置初期化
					CSR_FLG = 0;							//ホームポジションセット
					disp_stg = 00;							//生産画面
					disp_stg_sel = E_sstg_init;				//生産[基本]へ
					GAMEN_NO = 1;
					GAMEN_disp();								//画面表示
				}
				DAN_KEY_FLG = 0x00;						//型段取キーにて高機能型画面移動時の処理
			}
			else{
				SEI_csr_ichk();							//生産カーソル位置初期化
				CSR_FLG = 0;							//ホームポジションセット
				disp_stg = 00;							//生産画面
				disp_stg_sel = E_sstg_init;				//生産[基本]へ
				GAMEN_NO = 1;
				GAMEN_disp();								//画面表示
				DAN_KEY_FLG = 0x00;						//型段取キーにて高機能型画面移動時の処理
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEIDOUSEINOU_mng
*  Function Name:	制動性能試験切換え
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
#define		Meter_start_Xdot	16*6+3	// 96dot
#define		Meter_start_Ydot	16*5	// 80dot
#define		OneMeter_Xleg		16		// 16dot
#define		OneMeter_Yleg		16		// 16dot
void	EcoMeter_Disp(void)
{
	UNs	bit, xcnt, ycnt, Mcnt;
	UNs	xdot, ydot;

	UNl	bg_adr;
	UNb	*bg_col, Eco_col;

	if ((SEQ_PAR_103 & BIT_12) == 0)		return;
	if (GAMEN_NO != 1)						return;

	bg_adr = (UNl)&GAM_INF_TBL;
	bg_adr += GAM_INF_TBL_OFS;
	bg_adr += 514;
	bg_adr += 6;						//生産画面のｽｸﾘｰﾝ色が格納されているｱﾄﾞﾚｽ
	bg_col = (UNb *)bg_adr;

	bit = PVP_ECO_METER;

	for (Mcnt=0; Mcnt<8; Mcnt++, bit=bit>>1)
	{
		ydot = Meter_start_Ydot;				//Yｽﾀｰﾄdot
		xdot = Meter_start_Xdot;
		xdot += Mcnt * (OneMeter_Xleg-1);		//n個目のXｽﾀｰﾄdot

		if (bit & BIT_0) {					//ﾒｰﾀ色表示？
			Eco_col = COL_EcoM0 + Mcnt;
		}
		else {
			Eco_col = *bg_col;
		}

		Dsp_sikaku1(xdot, ydot, OneMeter_Xleg, OneMeter_Yleg, COL_BLACK, Eco_col);
	}
}


/*
********************************************************************************
*  Module Name:		LANG_SEQ_OUT
*  Function Name:	表示言語をビットでＳＥＱへ出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	LANG_SEQ_OUT(void)
{
	UNs		dt, seq, cnt;

//V06n	dt = SV_LANGUAGE;
	dt = SV_LANGUAGE - 1;
	if (dt > 2) {
//V06n		seq = 0;
		seq = BIT_12;
	}
	else {
		seq = BIT_12;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_050 = (SEQ_PAR_050 & ~(BIT_12+BIT_13+BIT_14)) | seq;
}


/*
********************************************************************************
*  Module Name:		HAN_MODE_SEQ_OUT
*  Function Name:	反転モード Ｐ／Ｓ設定をビットでＳＥＱへ出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	HAN_MODE_SEQ_OUT(void)
{
	UNs		dt, seq, cnt;

	dt = SV_HAN_P;
	if (dt > 9) {
//V06n		seq = 0;
		seq = 0x0001;
	}
	else {
		seq = 0x0001;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_048 = (SEQ_PAR_048 & ~0x3ff) | seq;

	dt = SV_HAN_S;
	if (dt > 9) {
//V06n		seq = 0;
		seq = 0x0001;
	}
	else {
		seq = 0x0001;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_049 = (SEQ_PAR_049 & ~0x3ff) | seq;
}


/*
********************************************************************************
*  Module Name:		DIE_HEIGHT_OFFSET
*  Function Name:	ダイハイトオフセット
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2012-09-24	V06m, V06n
********************************************************************************
*/
void	DIE_HEIGHT_OFFSET(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;
	S4b		ofs;
	S4b		sWK1, sWK2, sWK3, sWK4;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= DIEH_OFS_FLG;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & DIEH_OFS_FLG;				// chg & old = ofe
	DIEH_OFS_FLG = seq_bit;

	if (seq_one & cBIT10) {				//＋オフセット指令
		ofs = (S4b)GMN_PAR020;
		ofs *= 1000;					//小数点3桁へ
		ofs = cnv_mm_inch(ofs, 2);
		SV0_RNAPOS_MINO = SV_RNAPOS_MINP + ofs;			//機械下限
		SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP + ofs;			//機械上限

		ofs = (S4b)GMN_PAR020;
		ofs *= 10;						//小数点1桁へ
		ofs = cnv_mm_inch(ofs, 2);
		SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1 + ofs;			//ダイハイト下限
		SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2 + ofs;			//ダイハイト上限

		SVSW_CHG_FLG |= 0x0001;
	}

	if (seq_one & cBIT11) {				//－オフセット指令
		ofs = (S4b)GMN_PAR020;
		ofs *= 1000;					//小数点3桁へ
		ofs = cnv_mm_inch(ofs, 2);

		sWK1 = (S4b)SV_RNAPOS_MINP;		//機械下限
		sWK1 -= ofs;
		if (sWK1 < 1000) {
			sWK1 = 1000;
		}
		sWK2 = (S4b)SV_RNAPOS_MAXP;		//機械上限
		sWK2 -= ofs;
		if (sWK2 < sWK1) {
			sWK2 = sWK1;
		}

		ofs = (S4b)GMN_PAR020;
		ofs *= 10;						//小数点1桁へ
		ofs = cnv_mm_inch(ofs, 2);

		sWK3 = (S4b)SV_DAIHAI_LNG1;		//ダイハイト下限
		sWK3 -= ofs;
		sWK3 *= 100;
		if (sWK3 < sWK1) {
			sWK3 = sWK1;
		}
		sWK4 = (S4b)SV_DAIHAI_LNG2;		//ダイハイト上限
		sWK4 -= ofs;
		sWK4 *= 100;
		if (sWK4 < sWK1) {
			sWK4 = sWK1;
		}

		SV0_RNAPOS_MINO = sWK1;			//機械下限
		SV0_RNAPOS_MAXO = sWK2;			//機械上限
		SV0_DAIHAI_LNG1O = sWK3 / 100;	//ダイハイト下限
		SV0_DAIHAI_LNG2O = sWK4 / 100;	//ダイハイト上限

		SVSW_CHG_FLG |= 0x0001;
	}

	if ( (seq_ofe & cBIT10) || (seq_ofe & cBIT11) ) {
		SV0_RNAPOS_MINO = SV_RNAPOS_MINP;			//機械下限
		SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP;			//機械上限
		SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1;			//ダイハイト下限
		SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2;			//ダイハイト上限

		SVSW_CHG_FLG |= 0x0001;
	}
}


/*
********************************************************************************
*  Module Name:		FURIKO_SPEC_ON_OFF
*  Function Name:	振子(下往復)仕様ON/OFF
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	FURIKO_SPEC_ON_OFF(void)
{
#if 0	//V06p(DEL)
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;
	UNs		gam_chg;

	if (disp_stg == 1)		return;

	gam_chg = 0;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= FURIKO_FLG;							// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & FURIKO_FLG;				// chg & old = ofe
	FURIKO_FLG = seq_bit;

	if (seq_one & cBIT14) {				//仕様設定ON指令
		if (SEQ_023_SV & BIT_8) {
			//既にONなら何もしない。
		}
		else {
			SEQ_023_SV |= BIT_8;			//仕様設定121(下往復)  0N
			FRAM_csum_set();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
			
			gam_chg = 1;
		}
	}

	if (seq_one & cBIT15) {				//仕様設定OFF指令
		if (SEQ_023_SV & BIT_8) {
			SEQ_023_SV &= ~BIT_8;			//仕様設定121(下往復)  0FF
			FRAM_csum_set();				//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			gam_chg = 1;
		}
		else {
			//既にOFFなら何もしない。
		}
	}

	if (gam_chg) {
		MOT_MODE_BAK = SEQ_050_SV;				//V06n
		if (disp_stg == 0) {
			disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
			CAR_mkssi_set();					//単位切換
			GAMEN_NO = 3;
			GAMEN_disp();						//画面表示
			SEQ_PAR_051 |= BIT_14;				//画面遷移有り		V06n
		}
		else if (disp_stg == 2) {
			disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
			CAR_mkssi_set();					//単位切換
			GAMEN_NO = 28;
			GAMEN_disp();						//画面表示
			SEQ_PAR_051 |= BIT_14;				//画面遷移有り		V06n
		}
		else if (disp_stg == 3) {
			disp_stg = 2;						//データ設定画面へ
			disp_stg_sel = E_dstg_mset;			//データ設定[モーション設定]へ
			CAR_mkssi_set();					//単位切換
			GAMEN_NO = 28;
			GAMEN_disp();						//画面表示
			SEQ_PAR_051 |= BIT_14;				//画面遷移有り		V06n
		}
	}
#endif
}


/*
********************************************************************************
*  Module Name:		SYSSET_SEQ_OUT
*  Function Name:	システム設定画面への遷移可／不可をビットでＳＥＱへ出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2012-10-14	V06n
********************************************************************************
*/
void	SYSSET_SEQ_OUT(void)
{
	if (SEQ_PAR_101 & cBIT1) {					//システム設定変更可
		SEQ_PAR_051 |= cBIT15;					//システム設定画面への遷移可
	}
	else {
		if (SEQ_PAR_113 & cBIT13) {				//システム設定画面への遷移許可
			SEQ_PAR_051 |= cBIT15;				//遷移可
		}
		else {
			SEQ_PAR_051 &= ~cBIT15;				//遷移不可
		}
	}
	
}


/*** END ***/



#if	E_DEBUG_1											//デバッグモード指定

;/***************************************************************/
;/*								*/
;/*		Ｅ２ＰＲＯＭ　バックアップデータチェック	*/
;/*		（Ｅ２Ｐ＿ＲＯＭ＿ＤＴ＿ＣＨＫ）		*/
;/*								*/
;/*				ｂｙ　　　　ｍａｍａ		*/
;/*								*/
;/***************************************************************/
E2_DATA_SET		PROC	NEAR
;
;
;
;
	CALL	SV_EEPROM_CHK			;/* 設定値ＥＥＰＲＯＭデータチェック*/
	CALL	CB_V55_H8_HND1			;/* イニシャルハンドシェイク処理 */
;
;
	PUSH	ES				;
	MOV	AX,SEQ_RAM			;
	MOV	ES,AX				;
;
	MOV	AL,SEQ_016_SV			;/* リモートＩ／Ｏ有無セット */
	AND	AL,00000001B			;
	MOV	ES:SEQ_RIO_STS,AL		;
	POP	ES				;
;
;
	MOV	TAIKI_LST,0FFFFH		;
;
;
;
	MOV 	AX,ENCO_DATA_HEX	; NOW DEG --> DX
;
	PUSH	ES			;
	MOV	BX,SEQ_RAM		;
	MOV	ES,BX			;
	MOV	BX,165			;
	MOV	DX,165+30		;
	TEST	ES:SEQ_PAR_222,01000000B;
	POP	ES			;
	JZ	COUNT_DEC_0100		;
	MOV	BX,165-30		;
	MOV	DX,165			;
;
COUNT_DEC_0100:
;
	CMP	AX,BX			;
	JNB	COUNT_DEC_010		;
	JMP	COUNT_DEC_170		;
COUNT_DEC_010:
	CMP	AX,DX			;
	JB	COUNT_DEC_020		;

;




	JMP	COUNT_DEC_170		;
COUNT_DEC_020:
;
	TEST	SEQ_017_SV,BIT_1		;/* トータルカウント１　外部カウント？ */
	JNZ	COUNT_DEC_110			;YES
	TEST	SEQ_017_SV,BIT_0		;/* トータルカウンタ１有り？ */
	JZ	COUNT_DEC_110			;NO
	TEST	SEQ_038_SV,BIT_0		;/* トータルカウンタ１入 */
	JZ	COUNT_DEC_110			;NO
;
;
	SUB	PV_TOTLC1_B3,1 			;/* トータルカウンタ１ */
	SBB	PV_TOTLC1_B3+2,0		;/* トータルカウンタ１ */
COUNT_DEC_110:
COUNT_DEC_120:
;
	PUSH	ES				;
	MOV	AX,SEQ_RAM			;
	MOV	ES,AX				;
;
;
	TEST	SEQ_017_SV,BIT_5		;/* ロットカウント１　外部カウント？ */
	JNZ	COUNT_DEC_130			;YES
	TEST	SEQ_017_SV,BIT_4		;/* ロットカウント１　有り？ */
	JZ	COUNT_DEC_130			;NO
	TEST	SEQ_038_SV,BIT_2		;/* ロットカウント１　入り？ */
	JZ	COUNT_DEC_130			;NO
	TEST	ES:SEQ_PAR_039,BIT_0		;/* ロットカウント１　ＵＰ？ */
	JNZ	COUNT_DEC_130			;YES
;
	MOV	AX,SV_PUR1SV_B4			;
	MOV	DX,SV_PUR1SV_B4+2		;
	CMP	PV_LOTCT1_B4+2,DX		;
	JC	COUNT_DEC_125			;
	JNZ	COUNT_DEC_130			;
	CMP	PV_LOTCT1_B4,AX			;
	JA	COUNT_DEC_130			;
COUNT_DEC_125:					;
;
	SUB	PV_LOTCT1_B4,1 			;/* ロットカウンタ１ */
	SBB	PV_LOTCT1_B4+2,0		;/* ロットカウンタ１ */
;
COUNT_DEC_130:					;
;
;
	TEST	SEQ_017_SV,BIT_7		;/* ロットカウント２　外部カウント？ */
	JNZ	COUNT_DEC_140			;YES
	TEST	SEQ_017_SV,BIT_6		;/* ロットカウント２　有り？ */
	JZ	COUNT_DEC_140			;NO
	TEST	SEQ_038_SV,BIT_3		;/* ロットカウント２　入り？ */
	JZ	COUNT_DEC_140			;NO
	TEST	ES:SEQ_PAR_039,BIT_1		;/* ロットカウント２　ＵＰ？ */
	JNZ	COUNT_DEC_140			;YES
;
	MOV	AX,SV_PUR2SV_B41		;
	MOV	DX,SV_PUR2SV_B41+2		;
	CMP	PV_LOTCT2_B41+2,DX		;
	JC	COUNT_DEC_135			;
	JNZ	COUNT_DEC_140			;
	CMP	PV_LOTCT2_B41,AX		;
	JA	COUNT_DEC_140			;
COUNT_DEC_135:					;
;
;
;
;sit-2		TEST	SEQ_020_SV,BIT_2		;
;sit-2		JNZ	COUNT_DEC_140			;
;
	SUB	PV_LOTCT2_B41,1			;/* ロットカウンタ２ */
	SBB	PV_LOTCT2_B41+2,0		;/* ロットカウンタ２ */
;
COUNT_DEC_140:					;
;
;
	POP	ES				;
;
	SUB	PV_LIFE_COUNT,1			;
	SBB	PV_LIFE_COUNT+2,0		;
	SBB	PV_LIFE_COUNT+4,0		;
;V02	SBB	PV_LIFE_COUNT+6,0		;
;
COUNT_DEC_170:					;
;
;
	JMP	COUNT_DEC_END			;
;
;
;
;
COUNT_DEC_END:

;
	RET					;
;
E2_DATA_SET		ENDP

//;/***************************************************************/
//;/*								*/
//;/* 		設定値ＥＥＰＲＯＭデータチェック		*/
//;/*		（ＳＶ＿ＥＥＰＲＯＭ＿ＣＨＫ）			*/
//;/*								*/
//;/*			ＯＵＴ＝ＢＫＵＰ＿ＲＡＭ＿ＥＲＲ	*/
//;/*			　　　＝ＳＶ＿ＣＨＫ＿ＥＲＲ		*/
//;/*								*/
//;/*				ｂｙ　　　　ｍａｍａ		*/
//;/*								*/
//;/***************************************************************/
//SV_EEPROM_CHK	PROC	FAR
//;
//	PUSH	DS				;
//	PUSH	ES				;
//;
//	CALL	FAR PTR WDT_RESET		;V05
//;
//	CALL	FAR PTR SUM_CHK_CHK		;/* 設定値サムチェックコードチェック	*/
//;
//	MOV	AX,BAK_RAM			;
//	MOV	DS,AX				;
//	MOV	AX,DAT_RAM			;
//	MOV	ES,AX				;
//;
//	MOV	DI,OFFSET SV_TOP		;/* Ｅ２ＰＲＯＭよりデータ読込 */
//	MOV	SI,DI				;
//	MOV	CX,OFFSET SV_END		;/*  */
//	MOV	CX,2000H/2			;
//;
//	SUB	SI,SV_OFFSET			;
//	CLD					;
//	REP	MOVSW				;
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	MOV	SI,OFFSET PV_TOTLC1_B3 		;
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,40H				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	SI,OFFSET PV_CB1_MAXSPD		;
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,4				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	SI,OFFSET MCN_MENT_CNT1		;/* 機械レコーダ読込 */
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,64				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	AX,DAT_RAM			;
//	MOV	DS,AX				;
//;
//	MOV	POWRE_OK_FLG,9876H		;
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	SYS_CBDATA_READ			;V05/* シスパラよりクラッチ設定データ読み込み */
//;
//	CALL	KEEP_RY_BAK			;/*V02 キープリレーデータ返却	 		*/
//;
//SV_EEPROM_CHK_500:
//	PUSH	ES				;
//	MOV	AX,SEQ_ROM			;
//	MOV	ES,AX				;
//	XOR	AH,AH				;
//	MOV	AL,ES:ROM1_PAR_PSMOD_SEL	;
//	MOV	SV_PSDIMD_A1,AX			;/* PSDI MODE No. */
//	POP	ES				;
//;
//	CMP	SV_CHK_ERR,0			;/* 設定値異常有り？ */
//	JNE	SV_EEPROM_CHK_600		; YES
//;
//	MOV	SVSW_CHG_FLG,10111111B		;
//	CALL	GAM_SV_DTST			;/* Ｃ／ＢのＳＶデータ格納 */
//;
//SV_EEPROM_CHK_600:
//;
//;
//;/*************		仕様値ＭＡＸデータチェック　'95-04-27	*************/
//;
//	CMP	SV_MAXSPM_A14,330		;
//	JBE	E2_DATA_SET_000			;
//	MOV	SV_MAXSPM_A14,330		;
//;
//E2_DATA_SET_000:
//;
//;/***************************************************************************/
//;
//	MOV	AL,SEQ_025_SV			;/* 第二外国語切換有り？ */
//	AND	AL,BIT_5			;
//	MOV	GENGO_CHG_LAST,AL		;
//	CALL	GENGO_SEG_SET			;'98-07-17/* 言語セグメント確定 */
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	SEQ_SVDATA_SET			;/* ＳＥＱのＳＶデータ格納 */
//;
//	MOV	PODATA_SET_FLG,0FFH		;
//	CALL	OPDATA_BAK			;/* オプションの現位置データ返還 */
//	CALL	OPDATA_SET_KAKU			;/* オプションーデータ転送処理*/
//	CALL	FAR PTR WDT_RESET		;sit-2
//	CALL	POSDATA_SET_KAKU		;/* ポジショナーデータ転送処理*/
//	CALL	OPDATA_SYS_KAKU			;/* オプションにシスパラ格納  Ｖ０３ */
//;
//	PUSH	ES				;/* 進角設定データ書き込みフラグセット */
//	MOV	AX,SEQ_RAM			;
//	MOV	ES,AX				;
//	MOV	ES:ENTFLG,0FFH			;
//	POP	ES				;
//;
//	CMP	SV_CHK_ERR,0			;/* 全行程にて異常無し？ */
//	JE	SV_EEPROM_CHK_700		; YES
//;
//	MOV	AX,SEQ_RAM			;
//	MOV	ES,AX				;
//;
//	MOV	ES:BKUP_RAM_ERR,0FFH		;
//	MOV	AL,SV_SUM1_ERR			;
//	OR	AL,SV_SUM2_ERR			;
//	OR	AL,SV_DPRAM_ERR			;/* Ｃ／ＢＤ．Ｐ．ＲＡＭ照合異常フラグセット */
//	MOV	ES:SEQ_PAR_078,AL		;
//;
//SV_EEPROM_CHK_700:
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	FAR PTR INI_POSTION_CHK			;/* ポジショナーデータ　イニシャルチェック処理	*/
//;
//	CALL	FAR PTR ONOFF_SUB			;/* 仕様有り無しによる入切制御 */
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	KIDO_DATA_SET			;/* 輝度表示用データ作成 */
//	CALL	CAMNAME_PON_READ		;/* 電源投入時の汎用カム名称データ読込	*/
//	CALL	CAR_MKSSI_SET			;/* 単位切換データ格納処理			*/
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//;V02/*********	  バージョンＮｏ．セット  	******************************/
//;
//	MOV	PV_GMNVER_A1,CPUC_VER1		;/* ＣＰＵ－ＣバージョンＮｏ．セット */
//	MOV	PV_GMNVER_A1+1,CPUC_VER2	;/* ＣＰＵ－ＣバージョンＮｏ．セット */
//	MOV	PV_GMNVER_A1+2,CPUC_VER3	;/* ＣＰＵ－ＣバージョンＮｏ．セット */
//	MOV	PV_GMNVER_A1+3,CPUC_VER4	;/* ＣＰＵ－ＣバージョンＮｏ．セット */
//;
//;
//;V02/*************************************************************************/
//
//;
//;/*********	  バージョンＮｏ．セット  	******************************/
//	PUSH	DS				;
//	PUSH	ES				;
//	MOV	AX,SYS_ROM2
//	MOV	DS,AX				; ES = DATA RAM SEG
//	MOV	AX,DAT_RAM
//	MOV	ES,AX				; ES = DATA RAM SEG
//;
//	MOV	SI,OFFSET ROM_VERTION_DISP	;
//	MOV	DI,OFFSET PV_CBBVER_A1+5	;V02/* バージョンＮｏ． */
//	MOV	CX,6				;
//SV_EEPROM_CHK_800:
//	MOV	AL,DS:[SI]			;
//	MOV	ES:[DI],AL			;
//	INC	SI				;
//	DEC	DI				;
//	LOOP	SV_EEPROM_CHK_800		;
//;
//;
//	MOV	AX,SEQ_ROM			;
//	MOV	DS,AX				;
//	MOV	DI,OFFSET PV_SYSVER_A1+1	;'98-09-01/* シスパラバージョン */
//	MOV	SI,OFFSET SYS_ROM_VER		;
//	MOV	CX,2				;
//SV_EEPROM_CHK_810:
//	MOV	AL,DS:[SI]			;
//	MOV	ES:[DI],AL			;
//	INC	SI				;
//	DEC	DI				;
//	LOOP	SV_EEPROM_CHK_810		;
//;
//	POP	ES				;
//	POP	DS				
//;/***************************************************************************/
//	MOV	SEI_ON6_LST1,0FFH		;/* 電源投入時必ず段取りの項目有無チェックをするため。 */
//;
//	CALL	ROTTO_CHK			;/* ロットカウンタアップチェック		*/
//;
//	CALL	MLD100_NAMEREAD_INI		;MLD100/* 電源投入時１００型名称＆メモデータ読込処理 	*/
//	CALL	ADC_NEXTNAME_SET		;/* ＡＤＣ次型番号名称 			*/
//;
//;
//SV_EEPROM_CHK_END:
//;
//	POP	ES				;
//	POP	DS				;
//	RET					;
//;
//SV_EEPROM_CHK	ENDP
//;

#endif

