/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ＤＰＲＡＭ ← ＦＲＡＭ	データ転送処理				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"								//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"

/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SEQ	(void)
{
	SEQ_PAR_031		= SEQ_031_SV;				/* 初期回路設定シーケンス３１	*/
	SEQ_PAR_032		= SEQ_032_SV;				/* 初期回路設定シーケンス３２	*/
//	SEQ_PAR_033		= SEQ_033_SV;				/* 初期回路設定シーケンス３３	*/
	SEQ_PAR_034		= SEQ_034_SV;				/* 初期回路設定シーケンス３４	*/
//	SEQ_PAR_035		= SEQ_035_SV;				/* 初期回路設定シーケンス３５	*/
	SEQ_PAR_036		= SEQ_036_SV;				/* 初期回路設定シーケンス３６	*/
	SEQ_PAR_037		= SEQ_037_SV;				/* 初期回路設定シーケンス３７	*/
	SEQ_PAR_038		= SEQ_038_SV;				/* 初期回路設定シーケンス３８	*/
	SEQ_PAR_039		= SEQ_039_SV;				/* 初期回路設定シーケンス３９	*/

	SEQ_PAR_040		= SEQ_040_SV;				/* 初期回路設定シーケンス４０	*/
	SEQ_PAR_041		= (SEQ_041_SV & 0xFCFC);	/* 初期回路設定シーケンス４１	*/
	SEQ_PAR_042		= (SEQ_042_SV & 0xFCFC);	/* 初期回路設定シーケンス４２	*/
	SEQ_PAR_043		= (SEQ_043_SV & 0xFCFC);	/* 初期回路設定シーケンス４３	*/
	SEQ_PAR_044		= (SEQ_044_SV & 0xBFBC);	/* 初期回路設定シーケンス４４	*/
	SEQ_PAR_045		= (SEQ_045_SV & 0xBFFC);	/* 初期回路設定シーケンス４５	*/
	SEQ_PAR_046		= (SEQ_046_SV & 0xFCFC);	/* 初期回路設定シーケンス４６	*/
	SEQ_PAR_047		= SEQ_047_SV;				/* 初期回路設定シーケンス４７	*/
	SEQ_PAR_048		= SEQ_048_SV;				/* 初期回路設定シーケンス４８	*/
	SEQ_PAR_049		= SEQ_049_SV;				/* 初期回路設定シーケンス４９	*/

//V04 	SEQ_PAR_050		= SEQ_050_SV;				/* 初期回路設定シーケンス５０	*/
//V04 	SVP_MRTION_SEL1	= SEQ_050_SV;				/* 初期回路設定シーケンス５０	*/
//V06m	SEQ_PAR_050		= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* 初期回路設定シーケンス５０	*/
//V06m	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* 初期回路設定シーケンス５０	*/
	SEQ_PAR_050		= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* 初期回路設定シーケンス５０	*/
	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* 初期回路設定シーケンス５０	*/


//	SEQ_PAR_051		= SEQ_051_SV;			/* 初期回路設定シーケンス５１	*/
//	SEQ_PAR_052		= SEQ_052_SV;			/* 初期回路設定シーケンス５２	*/
//	SEQ_PAR_053		= SEQ_053_SV;			/* 初期回路設定シーケンス５３	*/
//	SEQ_PAR_054		= SEQ_054_SV;			/* 初期回路設定シーケンス５４	*/
//	SEQ_PAR_055		= SEQ_055_SV;			/* 初期回路設定シーケンス５５	*/

	SEQ_PAR_056		= SEQ_056_SV;			/* 初期回路設定シーケンス５６	*/	//V01v
	SEQ_PAR_057		= SEQ_057_SV;			/* 初期回路設定シーケンス５７	*/	//V05o

//	SEQ_PAR_058		= SEQ_058_SV;			/* 初期回路設定シーケンス５８	*/
//	SEQ_PAR_059		= SEQ_059_SV;			/* 初期回路設定シーケンス５９	*/
//
//	SEQ_PAR_060		= SEQ_060_SV;			/* 初期回路設定シーケンス６０	*/
//	SEQ_PAR_061		= SEQ_061_SV;			/* 初期回路設定シーケンス６１	*/
//	SEQ_PAR_062		= SEQ_062_SV;			/* 初期回路設定シーケンス６２	*/
//	SEQ_PAR_063		= SEQ_063_SV;			/* 初期回路設定シーケンス６３	*/
//	SEQ_PAR_064		= SEQ_064_SV;			/* 初期回路設定シーケンス６４	*/
//	SEQ_PAR_065		= SEQ_065_SV;			/* 初期回路設定シーケンス６５	*/
//	SEQ_PAR_066		= SEQ_066_SV;			/* 初期回路設定シーケンス６６	*/
//	SEQ_PAR_067		= SEQ_067_SV;			/* 初期回路設定シーケンス６７	*/
//	SEQ_PAR_068		= SEQ_068_SV;			/* 初期回路設定シーケンス６８	*/
//	SEQ_PAR_069		= SEQ_069_SV;			/* 初期回路設定シーケンス６９	*/
//
//	SEQ_PAR_070		= SEQ_070_SV;			/* 初期回路設定シーケンス７０	*/
//	SEQ_PAR_071		= SEQ_071_SV;			/* 初期回路設定シーケンス７１	*/
//	SEQ_PAR_072		= SEQ_072_SV;			/* 初期回路設定シーケンス７２	*/
//	SEQ_PAR_073		= SEQ_073_SV;			/* 初期回路設定シーケンス７３	*/
//	SEQ_PAR_074		= SEQ_074_SV;			/* 初期回路設定シーケンス７４	*/
//	SEQ_PAR_075		= SEQ_075_SV;			/* 初期回路設定シーケンス７５	*/
//	SEQ_PAR_076		= SEQ_076_SV;			/* 初期回路設定シーケンス７６	*/
//	SEQ_PAR_077		= SEQ_077_SV;			/* 初期回路設定シーケンス７７	*/
//	SEQ_PAR_078		= SEQ_078_SV;			/* 初期回路設定シーケンス７８	*/
//	SEQ_PAR_079		= SEQ_079_SV;			/* 初期回路設定シーケンス７９	*/

	SEQ_PAR_080	= SV_TIMER1_A1;					//内部タイマ１
	SEQ_PAR_081	= SV_TIMER2_A1;					//内部タイマ２
	SEQ_PAR_082	= SV_TIMER3_A1;					//内部タイマ３
	SEQ_PAR_083	= SV_TIMER4_A1;					//外部タイマ	V05r

	SEQ_PAR_088	= SV_COUNT1_A1;					//内部カウンタ１
	SEQ_PAR_089	= SV_COUNT2_A1;					//内部カウンタ２
	SEQ_PAR_090	= SV_COUNT3_A1;					//内部カウンタ３

//V01v:追加(ｻﾝﾌﾟﾘﾝｸﾞ画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMPSTR_KAJ	= SV_SMPSTR_KAJ;			// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ荷重
	SVP_SMPSTR_AGL	= SV_SMPSTR_AGL;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ角度
	SVP_SMPSTR_FUK	= SV_SMPSTR_FUK;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ負荷率
	SVP_SMPSTR_SEH	= SV_SMPSTR_SEH;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（上位ｱﾄﾞﾚｽ）
	SVP_SMPSTR_SQL	= SV_SMPSTR_SQL;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（下位ｱﾄﾞﾚｽ）
	SVP_SMPMAX_CNT	= SV_SMPMAX_CNT;			//  ｻﾝﾌﾟﾘﾝｸﾞ　最大個数
	SVP_SMPTRG_CNT	= SV_SMPTRG_CNT;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数
	SVP_SMPCYC_TIM	= SV_SMPCYC_TIM;			//  ｻﾝﾌﾟﾘﾝｸﾞ　周期

//V01z:追加(ｻﾝﾌﾟﾘﾝｸﾞ画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMP_CNT	= SV_SMP_CNT;				//  ｻﾝﾌﾟﾘﾝｸﾞ収集形式　毎
	SVP_TRD_CNT	= SV_TRD_CNT;				//  ﾄﾚﾝﾄﾞ収集形式　毎

//V05o:追加(ｻﾝﾌﾟﾘﾝｸﾞ設定画面、ﾄﾚﾝﾄﾞ設定画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMPTRG_CNT1	= SV_SMPTRG_CNT1;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数（SIT用）
	SVP_TRDCSR_RNAU	= cnv_inch_mm(SV_TRDCSR_RNAU, 0);	/* ｽﾗｲﾄﾞ上限検出位置	*/
	SVP_TRDCSR_RNAD	= cnv_inch_mm(SV_TRDCSR_RNAD, 0);	/* ｽﾗｲﾄﾞ上限検出位置	*/ 

//V05r:追加(加振機能設定画面、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_MAX_KJYU	= SV_MAXKA2_A24;		//最大荷重設定(ｵﾌﾟｼｮﾝにしかない)
	SVP_VIB_KJYU_TTL= SV_KASIN_KAJ;			//vibration(振動)荷重

}
/****************************************************************************/
