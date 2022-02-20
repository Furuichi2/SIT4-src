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
#include	"cm_equ1.h"		//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"


extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SEQ	(void)
{
	SEQ_PAR_031		= SEQ_031_SV;				/* 初期回路設定シーケンス３１	*/
	DPB_SEND_2B(&SEQ_PAR_031);
	SEQ_PAR_032		= SEQ_032_SV;				/* 初期回路設定シーケンス３２	*/
	DPB_SEND_2B(&SEQ_PAR_032);
//	SEQ_PAR_033		= SEQ_033_SV;				/* 初期回路設定シーケンス３３	*/
	SEQ_PAR_034		= SEQ_034_SV;				/* 初期回路設定シーケンス３４	*/
	DPB_SEND_2B(&SEQ_PAR_034);
//	SEQ_PAR_035		= SEQ_035_SV;				/* 初期回路設定シーケンス３５	*/
	SEQ_PAR_036		= SEQ_036_SV;				/* 初期回路設定シーケンス３６	*/
	DPB_SEND_2B(&SEQ_PAR_036);
	SEQ_PAR_037		= SEQ_037_SV;				/* 初期回路設定シーケンス３７	*/
	DPB_SEND_2B(&SEQ_PAR_037);
	SEQ_PAR_038		= SEQ_038_SV;				/* 初期回路設定シーケンス３８	*/
	DPB_SEND_2B(&SEQ_PAR_038);
	SEQ_PAR_039		= SEQ_039_SV;				/* 初期回路設定シーケンス３９	*/
	DPB_SEND_2B(&SEQ_PAR_039);

	SEQ_PAR_040		= SEQ_040_SV;				/* 初期回路設定シーケンス４０	*/
	DPB_SEND_2B(&SEQ_PAR_040);
	SEQ_PAR_041		= (SEQ_041_SV & 0xFCFC);	/* 初期回路設定シーケンス４１	*/
	DPB_SEND_2B(&SEQ_PAR_041);
	SEQ_PAR_042		= (SEQ_042_SV & 0xFCFC);	/* 初期回路設定シーケンス４２	*/
	DPB_SEND_2B(&SEQ_PAR_042);
	SEQ_PAR_043		= (SEQ_043_SV & 0xFCFC);	/* 初期回路設定シーケンス４３	*/
	DPB_SEND_2B(&SEQ_PAR_043);
	SEQ_PAR_044		= (SEQ_044_SV & 0xBFBC);	/* 初期回路設定シーケンス４４	*/
	DPB_SEND_2B(&SEQ_PAR_044);
	SEQ_PAR_045		= (SEQ_045_SV & 0xBFFC);	/* 初期回路設定シーケンス４５	*/
	DPB_SEND_2B(&SEQ_PAR_045);
	SEQ_PAR_046		= (SEQ_046_SV & 0xFCFC);	/* 初期回路設定シーケンス４６	*/
	DPB_SEND_2B(&SEQ_PAR_046);
//2016/04/22	SEQ_PAR_047		= SEQ_047_SV;				/* 初期回路設定シーケンス４７	*/
	SEQ_PAR_047		= (SEQ_PAR_047 & 0x7F1F) | (SEQ_047_SV & ~0x7F1F);			/* 初期回路設定シーケンス４７	*/
	DPB_SEND_2B(&SEQ_PAR_047);
	SEQ_PAR_048		= SEQ_048_SV;				/* 初期回路設定シーケンス４８	*/
	DPB_SEND_2B(&SEQ_PAR_048);
	SEQ_PAR_049		= SEQ_049_SV;				/* 初期回路設定シーケンス４９	*/
	DPB_SEND_2B(&SEQ_PAR_049);

//V04 	SEQ_PAR_050		= SEQ_050_SV;				/* 初期回路設定シーケンス５０	*/
//V04 	SVP_MRTION_SEL1	= SEQ_050_SV;				/* 初期回路設定シーケンス５０	*/
//V06m	SEQ_PAR_050		= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* 初期回路設定シーケンス５０	*/
//V06m	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* 初期回路設定シーケンス５０	*/
	SEQ_PAR_050		= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* 初期回路設定シーケンス５０	*/
	DPB_SEND_2B(&SEQ_PAR_050);
	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* 初期回路設定シーケンス５０	*/
	DPB_SEND_2B(&SVP_MRTION_SEL1);


//	SEQ_PAR_051		= SEQ_051_SV;			/* 初期回路設定シーケンス５１	*/
//	SEQ_PAR_052		= SEQ_052_SV;			/* 初期回路設定シーケンス５２	*/
//	SEQ_PAR_053		= SEQ_053_SV;			/* 初期回路設定シーケンス５３	*/
//	SEQ_PAR_054		= SEQ_054_SV;			/* 初期回路設定シーケンス５４	*/

//2014/09/01
	SEQ_PAR_055		= SEQ_055_SV;			/* 初期回路設定シーケンス５５	*/
	DPB_SEND_2B(&SEQ_PAR_055);

	SEQ_PAR_056		= SEQ_056_SV;			/* 初期回路設定シーケンス５６	*/	//V01v
	DPB_SEND_2B(&SEQ_PAR_056);
	SEQ_PAR_057		= SEQ_057_SV;			/* 初期回路設定シーケンス５７	*/	//V05o
	DPB_SEND_2B(&SEQ_PAR_057);

//	SEQ_PAR_058		= SEQ_058_SV;			/* 初期回路設定シーケンス５８	*/

//2014/09/01
	SEQ_PAR_059		= SEQ_059_SV;			/* 初期回路設定シーケンス５９	*/
	DPB_SEND_2B(&SEQ_PAR_059);

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
	DPB_SEND_2B(&SEQ_PAR_080);
	SEQ_PAR_081	= SV_TIMER2_A1;					//内部タイマ２
	DPB_SEND_2B(&SEQ_PAR_081);
	SEQ_PAR_082	= SV_TIMER3_A1;					//内部タイマ３
	DPB_SEND_2B(&SEQ_PAR_082);
	SEQ_PAR_083	= SV_TIMER4_A1;					//外部タイマ	V05r
	DPB_SEND_2B(&SEQ_PAR_083);

	SEQ_PAR_088	= SV_COUNT1_A1;					//内部カウンタ１
	DPB_SEND_2B(&SEQ_PAR_088);
	SEQ_PAR_089	= SV_COUNT2_A1;					//内部カウンタ２
	DPB_SEND_2B(&SEQ_PAR_089);
	SEQ_PAR_090	= SV_COUNT3_A1;					//内部カウンタ３
	DPB_SEND_2B(&SEQ_PAR_090);

//V01v:追加(ｻﾝﾌﾟﾘﾝｸﾞ画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMPSTR_KAJ	= SV_SMPSTR_KAJ;			// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ荷重
	DPB_SEND_2B(&SVP_SMPSTR_KAJ);
	SVP_SMPSTR_AGL	= SV_SMPSTR_AGL;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ角度
	DPB_SEND_2B(&SVP_SMPSTR_AGL);
	SVP_SMPSTR_FUK	= SV_SMPSTR_FUK;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ負荷率
	DPB_SEND_2B(&SVP_SMPSTR_FUK);
	SVP_SMPSTR_SEH	= SV_SMPSTR_SEH;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（上位ｱﾄﾞﾚｽ）
	DPB_SEND_2B(&SVP_SMPSTR_SEH);
	SVP_SMPSTR_SQL	= SV_SMPSTR_SQL;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（下位ｱﾄﾞﾚｽ）
	DPB_SEND_2B(&SVP_SMPSTR_SQL);
	SVP_SMPMAX_CNT	= SV_SMPMAX_CNT;			//  ｻﾝﾌﾟﾘﾝｸﾞ　最大個数
	DPB_SEND_2B(&SVP_SMPMAX_CNT);
	SVP_SMPTRG_CNT	= SV_SMPTRG_CNT;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数
	DPB_SEND_2B(&SVP_SMPTRG_CNT);
	SVP_SMPCYC_TIM	= SV_SMPCYC_TIM;			//  ｻﾝﾌﾟﾘﾝｸﾞ　周期
	DPB_SEND_2B(&SVP_SMPCYC_TIM);

//2014/09/03
	SVP_SMPMAX_CNT2	= SV_SMPMAX_CNT2;			//  ｻﾝﾌﾟﾘﾝｸﾞ　最大個数(SIT)
	DPB_SEND_2B(&SVP_SMPMAX_CNT2);
	SVP_SMPCYC_TIM2	= SV_SMPCYC_TIM2;			//  ｻﾝﾌﾟﾘﾝｸﾞ　周期
	DPB_SEND_2B(&SVP_SMPCYC_TIM2);

//V01z:追加(ｻﾝﾌﾟﾘﾝｸﾞ画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMP_CNT	= SV_SMP_CNT;				//  ｻﾝﾌﾟﾘﾝｸﾞ収集形式　毎
	DPB_SEND_2B(&SVP_SMP_CNT);
	SVP_TRD_CNT	= SV_TRD_CNT;				//  ﾄﾚﾝﾄﾞ収集形式　毎
	DPB_SEND_2B(&SVP_TRD_CNT);

//V05o:追加(ｻﾝﾌﾟﾘﾝｸﾞ設定画面、ﾄﾚﾝﾄﾞ設定画面の設定値、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_SMPTRG_CNT1	= SV_SMPTRG_CNT1;			//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数（SIT用）
	DPB_SEND_2B(&SVP_SMPTRG_CNT1);
	SVP_TRDCSR_RNAU	= cnv_inch_mm(SV_TRDCSR_RNAU, 0);	/* ｽﾗｲﾄﾞ上限検出位置	*/
	DPB_SEND_4B(&SVP_TRDCSR_RNAU);
	SVP_TRDCSR_RNAD	= cnv_inch_mm(SV_TRDCSR_RNAD, 0);	/* ｽﾗｲﾄﾞ上限検出位置	*/ 
	DPB_SEND_4B(&SVP_TRDCSR_RNAD);

//V05r:追加(加振機能設定画面、とりあえずｼｰｹﾝｽと一緒に転送する。)
	SVP_MAX_KJYU	= SV_MAXKA2_A24;		//最大荷重設定(ｵﾌﾟｼｮﾝにしかない)
	DPB_SEND_2B(&SVP_MAX_KJYU);
	SVP_VIB_KJYU_TTL= SV_KASIN_KAJ;			//vibration(振動)荷重
	DPB_SEND_2B(&SVP_VIB_KJYU_TTL);

//2014/03/17
	SVP_KAJAREA_SNO	= SV_KAJAREA_SNO;		//荷重測定範囲 開始工程No.
	SVP_KAJAREA_SAG	= SV_KAJAREA_SAG;		//荷重測定範囲 開始角度
	SVP_KAJAREA_ENO	= SV_KAJAREA_ENO;		//荷重測定範囲 終了工程No.
	SVP_KAJAREA_EAG	= SV_KAJAREA_EAG;		//荷重測定範囲 終了角度
	SVP_KAJAREA_SEL	= SV_KAJAREA_SEL;		//記録荷重選択

}
/****************************************************************************/
