/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ＤＰＲＡＭ ← ＦＲＡＭ	データ転送処理				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_def.h"							//各種の共通定義
#include	"ssc_wk_ext.h"


extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/


void	DP_TRANS_MOT	(void)
{

	UNl	wkl1;			/* V00m */

	U2b	posTimeLate;
	posTimeLate=10;//10:100msec  1:10msec 2014-05-30[R02R03]


//2002-10-16
//	SVP_OBJECT_PS01		= SV_1DANPOS_SRV;				/* 01段目目標位置		*/
//	SVP_OBJECT_PS02		= SV_2DANPOS_SRV;				/* 02段目目標位置		*/
//	SVP_OBJECT_PS03		= SV_3DANPOS_SRV;				/* 03段目目標位置		*/
//	SVP_OBJECT_PS04		= SV_4DANPOS_SRV;				/* 04段目目標位置		*/
//	SVP_OBJECT_PS05		= SV_5DANPOS_SRV;				/* 05段目目標位置		*/
//	SVP_OBJECT_PS06		= SV_6DANPOS_SRV;				/* 06段目目標位置		*/
//	SVP_OBJECT_PS07		= SV_7DANPOS_SRV;				/* 07段目目標位置		*/
//	SVP_OBJECT_PS08		= SV_8DANPOS_SRV;				/* 08段目目標位置		*/
//	SVP_OBJECT_PS09		= SV_9DANPOS_SRV;				/* 09段目目標位置		*/
//	SVP_OBJECT_PS10		= SV_10DANPOS_SRV;				/* 10段目目標位置		*/

	/* V00m */
	if( SEQ_050_SV & BIT_1 ) {								//反転　？
		SVP_OBJECT_PS01	= cnv_inch_mm(SV_1DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 01段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS01);
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 02段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS02);
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 03段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS03);
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 04段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS04);
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 05段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS05);
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 06段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS06);
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 07段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS07);
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 08段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS08);
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 09段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS09);
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 10段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS10);
		SVP_OBJECT_PS11		= 0;							/* 11段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS11);
		SVP_OBJECT_PS12		= 0;							/* 12段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS12);
		SVP_OBJECT_PS13		= 0;							/* 13段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS13);
		SVP_OBJECT_PS14		= 0;							/* 14段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS14);
		SVP_OBJECT_PS15		= 0;							/* 15段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS15);
		SVP_OBJECT_PS16		= 0;							/* 16段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS16);
		SVP_OBJECT_PS17		= 0;							/* 17段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS17);
		SVP_OBJECT_PS18		= 0;							/* 18段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS18);
		SVP_OBJECT_PS19		= 0;							/* 19段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS19);
		SVP_OBJECT_PS20		= 0;							/* 20段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS20);
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0) - SV_NEG_OFS_LNG;		/* ダイハイト＝下限位置－下限距離 */
		DPB_SEND_4B((U4b *)&SVP_DAIHAI_ORG0);
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* 待機点位置 */
		DPB_SEND_4B((U4b *)&SVP_UPAREA_POS0);
	}
	else {
		SVP_OBJECT_PS01	= cnv_inch_mm(SV_1DANPOS_SRV, 0);	/* 01段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS01);
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0);	/* 02段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS02);
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0);	/* 03段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS03);
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0);	/* 04段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS04);
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0);	/* 05段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS05);
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0);	/* 06段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS06);
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0);	/* 07段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS07);
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0);	/* 08段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS08);
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0);	/* 09段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS09);
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0);	/* 10段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS10);
		SVP_OBJECT_PS11		= 0;							/* 11段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS11);
		SVP_OBJECT_PS12		= 0;							/* 12段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS12);
		SVP_OBJECT_PS13		= 0;							/* 13段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS13);
		SVP_OBJECT_PS14		= 0;							/* 14段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS14);
		SVP_OBJECT_PS15		= 0;							/* 15段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS15);
		SVP_OBJECT_PS16		= 0;							/* 16段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS16);
		SVP_OBJECT_PS17		= 0;							/* 17段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS17);
		SVP_OBJECT_PS18		= 0;							/* 18段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS18);
		SVP_OBJECT_PS19		= 0;							/* 19段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS19);
		SVP_OBJECT_PS20		= 0;							/* 20段目目標位置		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS20);
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0);	/* ダイハイト			*/
		DPB_SEND_4B((U4b *)&SVP_DAIHAI_ORG0);
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* 待機点位置			*/
		DPB_SEND_4B((U4b *)&SVP_UPAREA_POS0);
	}

	SVP_OBJECT_DG01		= SV_1DANDEG_SRV;				/* 01段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG01);
	SVP_OBJECT_DG02		= SV_2DANDEG_SRV;				/* 02段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG02);
	SVP_OBJECT_DG03		= SV_3DANDEG_SRV;				/* 03段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG03);
	SVP_OBJECT_DG04		= SV_4DANDEG_SRV;				/* 04段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG04);
	SVP_OBJECT_DG05		= SV_5DANDEG_SRV;				/* 05段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG05);
	SVP_OBJECT_DG06		= SV_6DANDEG_SRV;				/* 06段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG06);
	SVP_OBJECT_DG07		= SV_7DANDEG_SRV;				/* 07段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG07);
	SVP_OBJECT_DG08		= SV_8DANDEG_SRV;				/* 08段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG08);
	SVP_OBJECT_DG09		= SV_9DANDEG_SRV;				/* 09段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG09);
	SVP_OBJECT_DG10		= SV_10DANDEG_SRV;				/* 10段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG10);
	SVP_OBJECT_DG11		= 0;							/* 11段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG11);
	SVP_OBJECT_DG12		= 0;							/* 12段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG12);
	SVP_OBJECT_DG13		= 0;							/* 13段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG13);
	SVP_OBJECT_DG14		= 0;							/* 14段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG14);
	SVP_OBJECT_DG15		= 0;							/* 15段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG15);
	SVP_OBJECT_DG16		= 0;							/* 16段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG16);
	SVP_OBJECT_DG17		= 0;							/* 17段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG17);
	SVP_OBJECT_DG18		= 0;							/* 18段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG18);
	SVP_OBJECT_DG19		= 0;							/* 19段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG19);
	SVP_OBJECT_DG20		= 0;							/* 20段目角度位置		*/
	DPB_SEND_2B(&SVP_OBJECT_DG20);

	SVP_OBJECT_SP01		= SV_1DANSPD_SRV;				/* 01段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP01);
	SVP_OBJECT_SP02		= SV_2DANSPD_SRV;				/* 02段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP02);
	SVP_OBJECT_SP03		= SV_3DANSPD_SRV;				/* 03段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP03);
	SVP_OBJECT_SP04		= SV_4DANSPD_SRV;				/* 04段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP04);
	SVP_OBJECT_SP05		= SV_5DANSPD_SRV;				/* 05段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP05);
	SVP_OBJECT_SP06		= SV_6DANSPD_SRV;				/* 06段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP06);
	SVP_OBJECT_SP07		= SV_7DANSPD_SRV;				/* 07段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP07);
	SVP_OBJECT_SP08		= SV_8DANSPD_SRV;				/* 08段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP08);
	SVP_OBJECT_SP09		= SV_9DANSPD_SRV;				/* 09段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP09);
	SVP_OBJECT_SP10		= SV_10DANSPD_SRV;				/* 10段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP10);
	SVP_OBJECT_SP11		= 0;							/* 11段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP11);
	SVP_OBJECT_SP12		= 0;							/* 12段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP12);
	SVP_OBJECT_SP13		= 0;							/* 13段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP13);
	SVP_OBJECT_SP14		= 0;							/* 14段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP14);
	SVP_OBJECT_SP15		= 0;							/* 15段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP15);
	SVP_OBJECT_SP16		= 0;							/* 16段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP16);
	SVP_OBJECT_SP17		= 0;							/* 17段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP17);
	SVP_OBJECT_SP18		= 0;							/* 18段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP18);
	SVP_OBJECT_SP19		= 0;							/* 19段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP19);
	SVP_OBJECT_SP20		= 0;							/* 20段目移動速度		*/
	DPB_SEND_2B(&SVP_OBJECT_SP20);

	SVP_OBJECT_TM01		= SV_1DANTIM_SRV*posTimeLate;				/* 01段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM01);
	SVP_OBJECT_TM02		= SV_2DANTIM_SRV*posTimeLate;				/* 02段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM02);
	SVP_OBJECT_TM03		= SV_3DANTIM_SRV*posTimeLate;				/* 03段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM03);
	SVP_OBJECT_TM04		= SV_4DANTIM_SRV*posTimeLate;				/* 04段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM04);
	SVP_OBJECT_TM05		= SV_5DANTIM_SRV*posTimeLate;				/* 05段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM05);
	SVP_OBJECT_TM06		= SV_6DANTIM_SRV*posTimeLate;				/* 06段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM06);
	SVP_OBJECT_TM07		= SV_7DANTIM_SRV*posTimeLate;				/* 07段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM07);
	SVP_OBJECT_TM08		= SV_8DANTIM_SRV*posTimeLate;				/* 08段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM08);
	SVP_OBJECT_TM09		= SV_9DANTIM_SRV*posTimeLate;				/* 09段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM09);
	SVP_OBJECT_TM10		= SV_10DANTIM_SRV*posTimeLate;				/* 10段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM10);

	SVP_OBJECT_TM11		= 0;							/* 11段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM11);
	SVP_OBJECT_TM12		= 0;							/* 12段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM12);
	SVP_OBJECT_TM13		= 0;							/* 13段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM13);
	SVP_OBJECT_TM14		= 0;							/* 14段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM14);
	SVP_OBJECT_TM15		= 0;							/* 15段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM15);
	SVP_OBJECT_TM16		= 0;							/* 16段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM16);
	SVP_OBJECT_TM17		= 0;							/* 17段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM17);
	SVP_OBJECT_TM18		= 0;							/* 18段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM18);
	SVP_OBJECT_TM19		= 0;							/* 19段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM19);
	SVP_OBJECT_TM20		= 0;							/* 20段目停止時間		*/
	DPB_SEND_2B(&SVP_OBJECT_TM20);

//2002-10-16
//2002-08-08
//	SVP_DAIHAI_ORG0		= SV_DAIHAITO_SRV;				/* ダイハイト			*/
//	SVP_DAIHAI_ORG0		= SV_DAIHAITO_SRV * 10;			/* ダイハイト			*/


//V01m	if (SEQ_024_SV & BIT_4)							//荷重補正あり？	V01k
//	{
//		SVP_KAJYUU_OBJP	= SV_DAIHAITO_SRV;				/* 目標荷重設定値 */
//	}
//	else
//	{
//		/* V00m */
//		if( SEQ_050_SV & BIT_1 ) {								//反転　？
//			SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0) - SV_NEG_OFS_LNG;		/* ダイハイト＝下限位置－下限距離 */
//		}
//		else {
//			SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0);	/* ダイハイト			*/
//		}
//	}
	SVP_KAJYUU_OBJP	= SV_KAJYUU_OBJP;				/* 目標荷重設定値 */
	DPB_SEND_2B(&SVP_KAJYUU_OBJP);


//2002-08-08
//	SVP_MRTION_SEL1		= SV_KAITEN_SRV;				/* 回転方式				*/
	SVP_MTSTEP_MAXM		= SV_DANSUU_SRV;				/* 段数					*/
	DPB_SEND_2B(&SVP_MTSTEP_MAXM);

//2002-10-16
//	SVP_UPAREA_POS0		= SV_TAIKIPOS_SRV;				/* 待機点位置			*/

//V01m	/* V00m */
//	if( SEQ_050_SV & BIT_1 ) {								//反転　？
//		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* 待機点位置 */
//	}
//	else {
//		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* 待機点位置			*/
//	}

	SVP_UPAREA_DIG0		= SV_TAIKIKAKU_SRV;				/* 待機点角度			*/
	DPB_SEND_2B(&SVP_UPAREA_DIG0);

//2002-08-02
//	SVP_UPAREA_SPD0		= 0;							/* 基準速度				*/
	SVP_UPAREA_SPD0		= SV_TAIKSPD_SRV;				/* 基準速度				*/
	DPB_SEND_2B(&SVP_UPAREA_SPD0);

	SVP_UPAREA_TIM0		= SV_TAIKTIM_SRV*posTimeLate;	/* 待機時間				*/
	DPB_SEND_2B(&SVP_UPAREA_TIM0);

	/* 補正追加 2002.06.28 */
//V01m	if (SEQ_024_SV & BIT_4)							//荷重補正あり？	V01j
//	{
//		SVP_KAJYUU_PRS1	= SV_HOASEI_SRV;				/* 荷重補正データ		*/
//	}
//	else
//	{
//		SVP_DAIHSA_LENG	= SV_HOASEI_SRV;				/* 補正データ			*/
//	}
	SVP_KAJYUU_PRS1	= SV_KAJYUU_PRS;				/* 荷重補正データ		*/
	DPB_SEND_2B(&SVP_KAJYUU_PRS1);

//2014/12/23
////	SVP_DAIHSA_LENG	= SV_HOASEI_SRV;				/* 補正データ			*/
	SVP_DAIHSA_LENG	= cnv_uinch_um(SV_HOASEI_SRV);		/* 補正データ			*/
	DPB_SEND_2B(&SVP_DAIHSA_LENG);


//	SVP_DNAREA_INP0		= SV_TAIKAN_SRV;				/* 待機完了範囲			*/
//2002-10-16
//	SVP_OBJARA_INP0		= SV_MOKKAN_SRV;				/* 目標完了範囲			*/
	SVP_OBJARA_INP0	= cnv_inch_mm(SV_MOKKAN_SRV, 0);	/* 目標完了範囲			*/
	DPB_SEND_2B(&SVP_OBJARA_INP0);

//2002-10-17
//2002-08-08:追加
//	SVP_SLID_POS1		= SV_ATUOS0_D9 * 10;			//スライド自動調節　生産設定
//	SVP_SLID_POS2		= SV_ATUOS1_D9 * 10;			//スライド自動調節　段取り１設定
//	SVP_SLID_POS3		= SV_ATUOS2_D9 * 10;			//スライド自動調節　段取り２設定

	if( SEQ_016_SV & BIT_6 ) {							//単位切替 mm/INCH 単位系(1:INCH)
		SVP_SLID_POS1		= cnv_inch_mm(SV_ATUOS0_D9, 0);	//スライド自動調節　生産設定
		DPB_SEND_4B(&SVP_SLID_POS1);
		SVP_SLID_POS2		= cnv_inch_mm(SV_ATUOS1_D9, 0);	//スライド自動調節　段取１設定
		DPB_SEND_4B(&SVP_SLID_POS2);
		SVP_SLID_POS3		= cnv_inch_mm(SV_ATUOS2_D9, 0);	//スライド自動調節　段取り２設定
		DPB_SEND_4B(&SVP_SLID_POS3);

		SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9, 0);	//スライド自動調節  生産設定/段取り１/段取２		2014/06/03
		DPB_SEND_4B(&SVP_ATSLID_OBJ1);
	}
	else {
		if (SV_POINT_A1 == 0) {
			wkl1 = 1000;
		}
		else if (SV_POINT_A1 == 1) {
			wkl1 = 100;
		}
		else if (SV_POINT_A1 == 2) {
			wkl1 = 10;
		}
		else {
			wkl1 = 1;
		}
		SVP_SLID_POS1		= cnv_inch_mm(SV_ATUOS0_D9 * wkl1, 0);	//スライド自動調節　生産設定
		DPB_SEND_4B(&SVP_SLID_POS1);
		SVP_SLID_POS2		= cnv_inch_mm(SV_ATUOS1_D9 * wkl1, 0);	//スライド自動調節　段取１設定
		DPB_SEND_4B(&SVP_SLID_POS2);
		SVP_SLID_POS3		= cnv_inch_mm(SV_ATUOS2_D9 * wkl1, 0);	//スライド自動調節　段取り２設定
		DPB_SEND_4B(&SVP_SLID_POS3);

		SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9 * wkl1, 0);	//スライド自動調節  生産設定/段取り１/段取２		2014/06/03
		DPB_SEND_4B(&SVP_ATSLID_OBJ1);
	}

//2002-10-07:削除
//	SVP_GMNSEQ_CNT01	= SV_COUNT1_A1;					//内部カウンタ１
//	SVP_GMNSEQ_CNT02	= SV_COUNT2_A1;					//内部カウンタ２
//	SVP_GMNSEQ_CNT03	= SV_COUNT3_A1;					//内部カウンタ３
//	SVP_GMNSEQ_CNT04	= 0;							//予備
//	SVP_GMNSEQ_CNT05	= 0;							//予備
//	SVP_GMNSEQ_CNT06	= 0;							//予備
//	SVP_GMNSEQ_CNT07	= 0;							//予備
//	SVP_GMNSEQ_CNT08	= 0;							//予備
//
//	SVP_GMNSEQ_TIM01	= SV_TIMER1_A1;					//内部タイマ１
//	SVP_GMNSEQ_TIM02	= SV_TIMER2_A1;					//内部タイマ２
//	SVP_GMNSEQ_TIM03	= SV_TIMER3_A1;					//内部タイマ３
//	SVP_GMNSEQ_TIM04	= 0;							//予備
//	SVP_GMNSEQ_TIM05	= 0;							//予備
//	SVP_GMNSEQ_TIM06	= 0;							//予備
//	SVP_GMNSEQ_TIM07	= 0;							//予備
//	SVP_GMNSEQ_TIM08	= 0;							//予備

//2002-08-29:追加
//2002-10-17
//	SVP_ATSLID_OBJ1		= SV_ATUOSU_D9 * 10;			//スライド自動調節設定値（現在動作中）
//2014/06/03	SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9, 0);	//スライド自動調節設定値（現在動作中）
////////////	DPB_SEND_4B(&SVP_ATSLID_OBJ1);

	SVP_ATSLID_DNOBJ1	= SV_DNSTOP_A21;				//スライド自動調節　下降停止
	DPB_SEND_2B(&SVP_ATSLID_DNOBJ1);
	SVP_ATSLID_UPOBJ1	= SV_UPSTOP_A21;				//スライド自動調節　上昇停止
	DPB_SEND_2B(&SVP_ATSLID_UPOBJ1);
	SVP_ATSLID_BAKLNG	= SV_MODORI_A21;				//スライド自動調節　戻り量
	DPB_SEND_2B(&SVP_ATSLID_BAKLNG);
	SVP_ATSLID_COEF1	= SV_SSEIDO_A21;				//スライド自動調節　制御精度
	DPB_SEND_2B(&SVP_ATSLID_COEF1);

//V01 (INS)
	SVP_DNDINC_SPD1		= SV_SPDDAN_B1;					/* 段取速度				*/
	DPB_SEND_2B(&SVP_DNDINC_SPD1);

//V01w(INS)
	SVP_OVERLIDE_COF	= SV_OVERLIDE_COF;				/* ｵｰﾊﾞﾗｲﾄﾞ比率				*/
	DPB_SEND_2B(&SVP_OVERLIDE_COF);
	SVP_DND_STOPDIG1	= SV_DND_STOPDIG1;				/* 段取停止角度				*/
	DPB_SEND_2B(&SVP_DND_STOPDIG1);
	SVP_KJSTR_STEP1		= SV_KJSTR_STEP1;				//0,1~工程 
	DPB_SEND_2B(&SVP_KJSTR_STEP1);
	SVP_KJSTR_DIG1		= SV_KJSTR_DIG1	;				//359.0
	DPB_SEND_2B(&SVP_KJSTR_DIG1);
	SVP_KJEND_STEP1		= SV_KJEND_STEP1;				//0,1~工程
	DPB_SEND_2B(&SVP_KJEND_STEP1);
	SVP_KJEND_DIG1		= SV_KJEND_DIG1	;				//359.0
	DPB_SEND_2B(&SVP_KJEND_DIG1);

//V06p(INS)
	SVP_KATTCH_SPD		= SV_KATTCH_SPD *100;			//タッチ位置検出速度
	DPB_SEND_2B(&SVP_KATTCH_SPD);

//2014/04/14
	SVP_KATTCH_SAG		= SV_KATTCH_SAG;				//タッチ位置検出角度
	DPB_SEND_2B(&SVP_KATTCH_SAG);
	SVP_KATTCH_EAG		= SV_KATTCH_EAG;				//タッチ位置検出角度
	DPB_SEND_2B(&SVP_KATTCH_EAG);

//2014/04/14
	SVP_KANDO_A21	= SV_KANDO_A21;			//感度
	SVP_UPDATA_A21	= SV_UPDATA_A21;		//上限
	SVP_DNDATA_A21	= SV_DNDATA_A21;		//下限
	SVP_GENITI_A21	= SV_GENITI_A21;		//現位置
	SVP_MODORI_A21	= SV_MODORI_A21;		//戻り量
	SVP_DNSTOP_A21	= SV_DNSTOP_A21;		//下降停止
	SVP_UPSTOP_A21	= SV_UPSTOP_A21;		//上昇停止
//2014/06/03	SVP_SSEIDO_A21	= SV_SSEIDO_A21;		//制御精度
	SVP_SL_TENPOS	= SV_POINT_A1;			//スライド自動調節  小数点位置						2014/06/03
	SVP_SLPOS_DIR	= SV_SLPOS_DIR;			//位置決め方向

//2014/06/03
//;	-------------- 最大値選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	SVP_OVERE1_A26	= SV_OVERE1_A26;		// 荷重計　オーバーロード１
	DPB_SEND_2B(&SVP_OVERE1_A26);
	SVP_ROALM1_A26	= SV_ROALM1_A26;		// 荷重計　ロアーリッミト１
	DPB_SEND_2B(&SVP_ROALM1_A26);
	SVP_OVERE2_A26	= SV_OVERE2_A26;		// 荷重計　オーバーロード２
	DPB_SEND_2B(&SVP_OVERE2_A26);
	SVP_ROALM2_A26	= SV_ROALM2_A26;		// 荷重計　ロアーリッミト２
	DPB_SEND_2B(&SVP_ROALM2_A26);
	SVP_OVERE3_A26	= SV_OVERE3_A26;		// 荷重計　オーバーロード３
	DPB_SEND_2B(&SVP_OVERE3_A26);
	SVP_ROALM3_A26	= SV_ROALM3_A26;		// 荷重計　ロアーリッミト３
	DPB_SEND_2B(&SVP_ROALM3_A26);

//;	-------------- 最小(ﾏｲﾅｽ最大)選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	SVP_OVERE1_A27	= SV_OVERE1_A27;		// 荷重計　オーバーロード１ 　（最小値）
	DPB_SEND_2B(&SVP_OVERE1_A27);
	SVP_ROALM1_A27	= SV_ROALM1_A27;		// 荷重計　ロアーリッミト１  　（最小値）
	DPB_SEND_2B(&SVP_ROALM1_A27);
	SVP_OVERE2_A27	= SV_OVERE2_A27;		// 荷重計　オーバーロード２  　（最小値）
	DPB_SEND_2B(&SVP_OVERE2_A27);
	SVP_ROALM2_A27	= SV_ROALM2_A27;		// 荷重計　ロアーリッミト２  　（最小値）
	DPB_SEND_2B(&SVP_ROALM2_A27);
	SVP_OVERE3_A27	= SV_OVERE3_A27;		// 荷重計　オーバーロード３  　（最小値）
	DPB_SEND_2B(&SVP_OVERE3_A27);
	SVP_ROALM3_A27	= SV_ROALM3_A27;		// 荷重計　ロアーリッミト３  　（最小値）
	DPB_SEND_2B(&SVP_ROALM3_A27);

//;	-------------- 振幅選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	SVP_OVERE1_A28	= SV_OVERE1_A28;		// 荷重計　オーバーロード１ 　（振幅）
	DPB_SEND_2B(&SVP_OVERE1_A28);
	SVP_ROALM1_A28	= SV_ROALM1_A28;		// 荷重計　ロアーリッミト１  　（振幅）
	DPB_SEND_2B(&SVP_ROALM1_A28);
	SVP_OVERE2_A28	= SV_OVERE2_A28;		// 荷重計　オーバーロード２  　（振幅）
	DPB_SEND_2B(&SVP_OVERE2_A28);
	SVP_ROALM2_A28	= SV_ROALM2_A28;		// 荷重計　ロアーリッミト２  　（振幅）
	DPB_SEND_2B(&SVP_ROALM2_A28);
	SVP_OVERE3_A28	= SV_OVERE3_A28;		// 荷重計　オーバーロード３  　（振幅）
	DPB_SEND_2B(&SVP_OVERE3_A28);
	SVP_ROALM3_A28	= SV_ROALM3_A28;		// 荷重計　ロアーリッミト３  　（振幅）
	DPB_SEND_2B(&SVP_ROALM3_A28);

//2014/08/27
	SVP_INTLIM_SNO = SV_INTLIM_SNO;				//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　行程
	DPB_SEND_2B(&SVP_INTLIM_SNO);
	SVP_INTLIM_AGL = SV_INTLIM_AGL;				//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　角度
	DPB_SEND_2B(&SVP_INTLIM_AGL);
	SVP_INTLIM_POS = SV_INTLIM_POS;				//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　位置
	DPB_SEND_4B(&SVP_INTLIM_POS);
	SVP_WTTIM_MAX = SV_WTTIM_MAX;				//ｽﾗｲﾄﾞ自動待機機能  待機時間上限
	DPB_SEND_2B(&SVP_WTTIM_MAX);

//2014/09/04
	SVP_MOTREP_STGS		= SV_MOTREP_STGS;		//繰り返し開始行程
	DPB_SEND_2B(&SVP_MOTREP_STGS);
	SVP_MOTREP_STGE		= SV_MOTREP_STGE;		//繰り返し終了行程
	DPB_SEND_2B(&SVP_MOTREP_STGE);
	SVP_MOTREP_SPD		= SV_MOTREP_SPD;		//繰り返し戻り速度
	DPB_SEND_2B(&SVP_MOTREP_SPD);
	SVP_MOTREP_CNT		= SV_MOTREP_CNT;		//繰り返し回数
	DPB_SEND_2B(&SVP_MOTREP_CNT);

//2014/09/04
//2014/10/09	SVP_MOT_FIX			= SV_MOT_FIX;			//一定速度領域 行程BIT情報
	SVP_MOT_FIX			= SV0_MOT_FIX;			//一定速度領域 行程BIT情報
	DPB_SEND_2B(&SVP_MOT_FIX);

//2015/01/14
	SVP_OBJECT_PRS01	= SV_1DANPRS_SRV;				//工程1 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS01);
	SVP_OBJECT_PRS02	= SV_2DANPRS_SRV;				//工程2 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS02);
	SVP_OBJECT_PRS03	= SV_3DANPRS_SRV;				//工程3 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS03);
	SVP_OBJECT_PRS04	= SV_4DANPRS_SRV;				//工程4 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS04);
	SVP_OBJECT_PRS05	= SV_5DANPRS_SRV;				//工程5 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS05);
	SVP_OBJECT_PRS06	= SV_6DANPRS_SRV;				//工程6 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS06);
	SVP_OBJECT_PRS07	= SV_7DANPRS_SRV;				//工程7 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS07);
	SVP_OBJECT_PRS08	= SV_8DANPRS_SRV;				//工程8 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS08);
	SVP_OBJECT_PRS09	= SV_9DANPRS_SRV;				//工程9 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS09);
	SVP_OBJECT_PRS10	= SV_10DANPRS_SRV;				//工程10 荷重目標
	DPB_SEND_2B(&SVP_OBJECT_PRS10);
	SVP_KAJOBJ_HAB		= SV_KAJOBJ_HAB;				//荷重完了範囲
	DPB_SEND_2B(&SVP_KAJOBJ_HAB);
}
/****************************************************************************/
