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

#include	"ssc_def.h"							//各種の共通定義
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_wk_ext.h"


extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_GEN	(void)
{
//2002-10-16
//	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* 機械原点入力			*/
//2014/12/11	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* 機械原点入力			*/
	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* 機械原点入力 mm固定	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORG_POS1);


	SVP_RNAORGMEM_LEG1	= cnv_inch_mm(SV_RNAORGMEM_LEG1, 2);	/* 機械原点入力	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG1);
	SVP_RNAORGMEM_LEG2	= cnv_inch_mm(SV_RNAORGMEM_LEG2, 2);	/* 機械原点入力	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG2);


	if(DEB_WORD_FLG1 == 0x05a)		/* V01n_b */
	{
		PV_DEB_WORD_WK1 = PV_DEB_WORD_WK1 + 1;
	}
	DEB_WORD_FLG1 = 0x05a;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ → ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_GET_SENS		(void)
{
	/* リニアセンサデータ実測値をＦＲＡＭに保存する。*/

	PV_NOW_POS		= PVP_RENIA_POSI0;				/* リニアセンサ現在位置	*/
//	PV_NOW_POS		= PVP_NOW_POSI000;				/* 現在位置	 			*/
	PV_ENCOD_BCD	= PVP_NOW_ANGLE00;				/* 現在角度				*/
	PV_CYCLE_TIME	= PVP_CYCLE_TIME0;				/* サイクル時間			*/

	PV_RNAORG_PLS1	= PVP_RNAORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ		*/

//2002-10-10:追加
	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ		*/


	PV_BAKORG_PLS1	= PVP_BAKORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	PV_BAKORG_PLS2	= PVP_BAKORG_PLS2;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/


	PV_DEB_WORD_WK2 = PV_DEB_WORD_WK2 + 1;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_BACK_SENS	(void)
{
	/* ＦＲＡＭに保存したリニアセンサデータをＤＰＲＡＭに復元する。*/

	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ		*/
	DPB_SEND_4B((U4b *)&SVB_RNAORG_PLS1);

	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS2);
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_RENIA_BUP1	= PV_RENIA_BUP1;				//リニアスケールバックアップ用
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP1);
	SVB_RENIA_BUP2	= PV_RENIA_BUP2;				//リニアスケールバックアップ用
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP2);
	SVB_RENIA_BUP3	= PV_RENIA_BUP3;				//リニアスケールバックアップ用
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP3);
	SVB_RENIA_BUP4	= PV_RENIA_BUP4;				//リニアスケールバックアップ用
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP4);

	SVB_ARA1_KAJ_T2	= PV_ARA1_KAJ_T2;				//荷重実測平均		V02a
	DPB_SEND_2B((U2b *)&SVB_ARA1_KAJ_T2);

}
/****************************************************************************/
