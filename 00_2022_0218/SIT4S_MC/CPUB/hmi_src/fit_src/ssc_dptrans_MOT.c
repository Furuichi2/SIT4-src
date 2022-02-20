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
#include	"dp_cpuab.h"
#include	"ssc_def.h"							//各種の共通定義
#include	"ssc_wk_ext.h"

/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_MOT	(void)
{
	UNl	wkl1;			/* V00m */

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
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 02段目目標位置		*/
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 03段目目標位置		*/
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 04段目目標位置		*/
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 05段目目標位置		*/
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 06段目目標位置		*/
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 07段目目標位置		*/
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 08段目目標位置		*/
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 09段目目標位置		*/
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 10段目目標位置		*/
		SVP_OBJECT_PS11		= 0;							/* 11段目目標位置		*/
		SVP_OBJECT_PS12		= 0;							/* 12段目目標位置		*/
		SVP_OBJECT_PS13		= 0;							/* 13段目目標位置		*/
		SVP_OBJECT_PS14		= 0;							/* 14段目目標位置		*/
		SVP_OBJECT_PS15		= 0;							/* 15段目目標位置		*/
		SVP_OBJECT_PS16		= 0;							/* 16段目目標位置		*/
		SVP_OBJECT_PS17		= 0;							/* 17段目目標位置		*/
		SVP_OBJECT_PS18		= 0;							/* 18段目目標位置		*/
		SVP_OBJECT_PS19		= 0;							/* 19段目目標位置		*/
		SVP_OBJECT_PS20		= 0;							/* 20段目目標位置		*/
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0) - SV_NEG_OFS_LNG;		/* ダイハイト＝下限位置－下限距離 */
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* 待機点位置 */
	}
	else {
		SVP_OBJECT_PS01	= cnv_inch_mm(SV_1DANPOS_SRV, 0);	/* 01段目目標位置		*/
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0);	/* 02段目目標位置		*/
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0);	/* 03段目目標位置		*/
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0);	/* 04段目目標位置		*/
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0);	/* 05段目目標位置		*/
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0);	/* 06段目目標位置		*/
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0);	/* 07段目目標位置		*/
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0);	/* 08段目目標位置		*/
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0);	/* 09段目目標位置		*/
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0);	/* 10段目目標位置		*/
		SVP_OBJECT_PS11		= 0;							/* 11段目目標位置		*/
		SVP_OBJECT_PS12		= 0;							/* 12段目目標位置		*/
		SVP_OBJECT_PS13		= 0;							/* 13段目目標位置		*/
		SVP_OBJECT_PS14		= 0;							/* 14段目目標位置		*/
		SVP_OBJECT_PS15		= 0;							/* 15段目目標位置		*/
		SVP_OBJECT_PS16		= 0;							/* 16段目目標位置		*/
		SVP_OBJECT_PS17		= 0;							/* 17段目目標位置		*/
		SVP_OBJECT_PS18		= 0;							/* 18段目目標位置		*/
		SVP_OBJECT_PS19		= 0;							/* 19段目目標位置		*/
		SVP_OBJECT_PS20		= 0;							/* 20段目目標位置		*/
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0);	/* ダイハイト			*/
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* 待機点位置			*/
	}

	SVP_OBJECT_DG01		= SV_1DANDEG_SRV;				/* 01段目角度位置		*/
	SVP_OBJECT_DG02		= SV_2DANDEG_SRV;				/* 02段目角度位置		*/
	SVP_OBJECT_DG03		= SV_3DANDEG_SRV;				/* 03段目角度位置		*/
	SVP_OBJECT_DG04		= SV_4DANDEG_SRV;				/* 04段目角度位置		*/
	SVP_OBJECT_DG05		= SV_5DANDEG_SRV;				/* 05段目角度位置		*/
	SVP_OBJECT_DG06		= SV_6DANDEG_SRV;				/* 06段目角度位置		*/
	SVP_OBJECT_DG07		= SV_7DANDEG_SRV;				/* 07段目角度位置		*/
	SVP_OBJECT_DG08		= SV_8DANDEG_SRV;				/* 08段目角度位置		*/
	SVP_OBJECT_DG09		= SV_9DANDEG_SRV;				/* 09段目角度位置		*/
	SVP_OBJECT_DG10		= SV_10DANDEG_SRV;				/* 10段目角度位置		*/
	SVP_OBJECT_DG11		= 0;							/* 11段目角度位置		*/
	SVP_OBJECT_DG12		= 0;							/* 12段目角度位置		*/
	SVP_OBJECT_DG13		= 0;							/* 13段目角度位置		*/
	SVP_OBJECT_DG14		= 0;							/* 14段目角度位置		*/
	SVP_OBJECT_DG15		= 0;							/* 15段目角度位置		*/
	SVP_OBJECT_DG16		= 0;							/* 16段目角度位置		*/
	SVP_OBJECT_DG17		= 0;							/* 17段目角度位置		*/
	SVP_OBJECT_DG18		= 0;							/* 18段目角度位置		*/
	SVP_OBJECT_DG19		= 0;							/* 19段目角度位置		*/
	SVP_OBJECT_DG20		= 0;							/* 20段目角度位置		*/

	SVP_OBJECT_SP01		= SV_1DANSPD_SRV;				/* 01段目移動速度		*/
	SVP_OBJECT_SP02		= SV_2DANSPD_SRV;				/* 02段目移動速度		*/
	SVP_OBJECT_SP03		= SV_3DANSPD_SRV;				/* 03段目移動速度		*/
	SVP_OBJECT_SP04		= SV_4DANSPD_SRV;				/* 04段目移動速度		*/
	SVP_OBJECT_SP05		= SV_5DANSPD_SRV;				/* 05段目移動速度		*/
	SVP_OBJECT_SP06		= SV_6DANSPD_SRV;				/* 06段目移動速度		*/
	SVP_OBJECT_SP07		= SV_7DANSPD_SRV;				/* 07段目移動速度		*/
	SVP_OBJECT_SP08		= SV_8DANSPD_SRV;				/* 08段目移動速度		*/
	SVP_OBJECT_SP09		= SV_9DANSPD_SRV;				/* 09段目移動速度		*/
	SVP_OBJECT_SP10		= SV_10DANSPD_SRV;				/* 10段目移動速度		*/
	SVP_OBJECT_SP11		= 0;							/* 11段目移動速度		*/
	SVP_OBJECT_SP12		= 0;							/* 12段目移動速度		*/
	SVP_OBJECT_SP13		= 0;							/* 13段目移動速度		*/
	SVP_OBJECT_SP14		= 0;							/* 14段目移動速度		*/
	SVP_OBJECT_SP15		= 0;							/* 15段目移動速度		*/
	SVP_OBJECT_SP16		= 0;							/* 16段目移動速度		*/
	SVP_OBJECT_SP17		= 0;							/* 17段目移動速度		*/
	SVP_OBJECT_SP18		= 0;							/* 18段目移動速度		*/
	SVP_OBJECT_SP19		= 0;							/* 19段目移動速度		*/
	SVP_OBJECT_SP20		= 0;							/* 20段目移動速度		*/

	SVP_OBJECT_TM01		= SV_1DANTIM_SRV;				/* 01段目停止時間		*/
	SVP_OBJECT_TM02		= SV_2DANTIM_SRV;				/* 02段目停止時間		*/
	SVP_OBJECT_TM03		= SV_3DANTIM_SRV;				/* 03段目停止時間		*/
	SVP_OBJECT_TM04		= SV_4DANTIM_SRV;				/* 04段目停止時間		*/
	SVP_OBJECT_TM05		= SV_5DANTIM_SRV;				/* 05段目停止時間		*/
	SVP_OBJECT_TM06		= SV_6DANTIM_SRV;				/* 06段目停止時間		*/
	SVP_OBJECT_TM07		= SV_7DANTIM_SRV;				/* 07段目停止時間		*/
	SVP_OBJECT_TM08		= SV_8DANTIM_SRV;				/* 08段目停止時間		*/
	SVP_OBJECT_TM09		= SV_9DANTIM_SRV;				/* 09段目停止時間		*/
	SVP_OBJECT_TM10		= SV_10DANTIM_SRV;				/* 10段目停止時間		*/
	SVP_OBJECT_TM11		= 0;							/* 11段目停止時間		*/
	SVP_OBJECT_TM12		= 0;							/* 12段目停止時間		*/
	SVP_OBJECT_TM13		= 0;							/* 13段目停止時間		*/
	SVP_OBJECT_TM14		= 0;							/* 14段目停止時間		*/
	SVP_OBJECT_TM15		= 0;							/* 15段目停止時間		*/
	SVP_OBJECT_TM16		= 0;							/* 16段目停止時間		*/
	SVP_OBJECT_TM17		= 0;							/* 17段目停止時間		*/
	SVP_OBJECT_TM18		= 0;							/* 18段目停止時間		*/
	SVP_OBJECT_TM19		= 0;							/* 19段目停止時間		*/
	SVP_OBJECT_TM20		= 0;							/* 20段目停止時間		*/

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


//2002-08-08
//	SVP_MRTION_SEL1		= SV_KAITEN_SRV;				/* 回転方式				*/
	SVP_MTSTEP_MAXM		= SV_DANSUU_SRV;				/* 段数					*/

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

//2002-08-02
//	SVP_UPAREA_SPD0		= 0;							/* 基準速度				*/
	SVP_UPAREA_SPD0		= SV_TAIKSPD_SRV;				/* 基準速度				*/
	SVP_UPAREA_TIM0		= SV_TAIKTIM_SRV;				/* 待機時間				*/

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
	SVP_DAIHSA_LENG	= SV_HOASEI_SRV;				/* 補正データ			*/


//	SVP_DNAREA_INP0		= SV_TAIKAN_SRV;				/* 待機完了範囲			*/
//2002-10-16
//	SVP_OBJARA_INP0		= SV_MOKKAN_SRV;				/* 目標完了範囲			*/
	SVP_OBJARA_INP0	= cnv_inch_mm(SV_MOKKAN_SRV, 0);	/* 目標完了範囲			*/

//2002-10-17
//2002-08-08:追加
//	SVP_SLID_POS1		= SV_ATUOS0_D9 * 10;			//スライド自動調節　生産設定
//	SVP_SLID_POS2		= SV_ATUOS1_D9 * 10;			//スライド自動調節　段取り１設定
//	SVP_SLID_POS3		= SV_ATUOS2_D9 * 10;			//スライド自動調節　段取り２設定
	SVP_SLID_POS1		= cnv_inch_mm(SV_ATUOS0_D9, 0);	//スライド自動調節　生産設定
	SVP_SLID_POS2		= cnv_inch_mm(SV_ATUOS1_D9, 0);	//スライド自動調節　段取り１設定
	SVP_SLID_POS3		= cnv_inch_mm(SV_ATUOS2_D9, 0);	//スライド自動調節　段取り２設定

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
	SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9, 0);	//スライド自動調節設定値（現在動作中）

	SVP_ATSLID_DNOBJ1	= SV_DNSTOP_A21;				//スライド自動調節　下降停止
	SVP_ATSLID_UPOBJ1	= SV_UPSTOP_A21;				//スライド自動調節　上昇停止
	SVP_ATSLID_BAKLNG	= SV_MODORI_A21;				//スライド自動調節　戻り量
	SVP_ATSLID_COEF1	= SV_SSEIDO_A21;				//スライド自動調節　制御精度

//V01 (INS)
	SVP_DNDINC_SPD1		= SV_SPDDAN_B1;					/* 段取速度				*/

//V01w(INS)
	SVP_OVERLIDE_COF	= SV_OVERLIDE_COF;				/* ｵｰﾊﾞﾗｲﾄﾞ比率				*/
	SVP_DND_STOPDIG1	= SV_DND_STOPDIG1;				/* 段取停止角度				*/
	SVP_KJSTR_STEP1		= SV_KJSTR_STEP1;				//0,1~工程 
	SVP_KJSTR_DIG1		= SV_KJSTR_DIG1	;				//359.0
	SVP_KJEND_STEP1		= SV_KJEND_STEP1;				//0,1~工程
	SVP_KJEND_DIG1		= SV_KJEND_DIG1	;				//359.0

//V06p(INS)
	SVP_KATTCH_SPD		= SV_KATTCH_SPD *100;			//タッチ位置検出速度

}
/****************************************************************************/
