/****************************************************************************/
/*																			*/
/*	R}cY@aü¯	rhs|rRg[								*/
/*																			*/
/*						coq`l © eq`l	f[^]				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//eíÌ¤Êè`
#include	"cm_equ1.h"		//MCÉÄª£

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"


extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SEQ	(void)
{
	SEQ_PAR_031		= SEQ_031_SV;				/* úñHÝèV[PXRP	*/
	DPB_SEND_2B(&SEQ_PAR_031);
	SEQ_PAR_032		= SEQ_032_SV;				/* úñHÝèV[PXRQ	*/
	DPB_SEND_2B(&SEQ_PAR_032);
//	SEQ_PAR_033		= SEQ_033_SV;				/* úñHÝèV[PXRR	*/
	SEQ_PAR_034		= SEQ_034_SV;				/* úñHÝèV[PXRS	*/
	DPB_SEND_2B(&SEQ_PAR_034);
//	SEQ_PAR_035		= SEQ_035_SV;				/* úñHÝèV[PXRT	*/
	SEQ_PAR_036		= SEQ_036_SV;				/* úñHÝèV[PXRU	*/
	DPB_SEND_2B(&SEQ_PAR_036);
	SEQ_PAR_037		= SEQ_037_SV;				/* úñHÝèV[PXRV	*/
	DPB_SEND_2B(&SEQ_PAR_037);
	SEQ_PAR_038		= SEQ_038_SV;				/* úñHÝèV[PXRW	*/
	DPB_SEND_2B(&SEQ_PAR_038);
	SEQ_PAR_039		= SEQ_039_SV;				/* úñHÝèV[PXRX	*/
	DPB_SEND_2B(&SEQ_PAR_039);

	SEQ_PAR_040		= SEQ_040_SV;				/* úñHÝèV[PXSO	*/
	DPB_SEND_2B(&SEQ_PAR_040);
	SEQ_PAR_041		= (SEQ_041_SV & 0xFCFC);	/* úñHÝèV[PXSP	*/
	DPB_SEND_2B(&SEQ_PAR_041);
	SEQ_PAR_042		= (SEQ_042_SV & 0xFCFC);	/* úñHÝèV[PXSQ	*/
	DPB_SEND_2B(&SEQ_PAR_042);
	SEQ_PAR_043		= (SEQ_043_SV & 0xFCFC);	/* úñHÝèV[PXSR	*/
	DPB_SEND_2B(&SEQ_PAR_043);
	SEQ_PAR_044		= (SEQ_044_SV & 0xBFBC);	/* úñHÝèV[PXSS	*/
	DPB_SEND_2B(&SEQ_PAR_044);
	SEQ_PAR_045		= (SEQ_045_SV & 0xBFFC);	/* úñHÝèV[PXST	*/
	DPB_SEND_2B(&SEQ_PAR_045);
	SEQ_PAR_046		= (SEQ_046_SV & 0xFCFC);	/* úñHÝèV[PXSU	*/
	DPB_SEND_2B(&SEQ_PAR_046);
//2016/04/22	SEQ_PAR_047		= SEQ_047_SV;				/* úñHÝèV[PXSV	*/
	SEQ_PAR_047		= (SEQ_PAR_047 & 0x7F1F) | (SEQ_047_SV & ~0x7F1F);			/* úñHÝèV[PXSV	*/
	DPB_SEND_2B(&SEQ_PAR_047);
	SEQ_PAR_048		= SEQ_048_SV;				/* úñHÝèV[PXSW	*/
	DPB_SEND_2B(&SEQ_PAR_048);
	SEQ_PAR_049		= SEQ_049_SV;				/* úñHÝèV[PXSX	*/
	DPB_SEND_2B(&SEQ_PAR_049);

//V04 	SEQ_PAR_050		= SEQ_050_SV;				/* úñHÝèV[PXTO	*/
//V04 	SVP_MRTION_SEL1	= SEQ_050_SV;				/* úñHÝèV[PXTO	*/
//V06m	SEQ_PAR_050		= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* úñHÝèV[PXTO	*/
//V06m	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* úñHÝèV[PXTO	*/
	SEQ_PAR_050		= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* úñHÝèV[PXTO	*/
	DPB_SEND_2B(&SEQ_PAR_050);
	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* úñHÝèV[PXTO	*/
	DPB_SEND_2B(&SVP_MRTION_SEL1);


//	SEQ_PAR_051		= SEQ_051_SV;			/* úñHÝèV[PXTP	*/
//	SEQ_PAR_052		= SEQ_052_SV;			/* úñHÝèV[PXTQ	*/
//	SEQ_PAR_053		= SEQ_053_SV;			/* úñHÝèV[PXTR	*/
//	SEQ_PAR_054		= SEQ_054_SV;			/* úñHÝèV[PXTS	*/

//2014/09/01
	SEQ_PAR_055		= SEQ_055_SV;			/* úñHÝèV[PXTT	*/
	DPB_SEND_2B(&SEQ_PAR_055);

	SEQ_PAR_056		= SEQ_056_SV;			/* úñHÝèV[PXTU	*/	//V01v
	DPB_SEND_2B(&SEQ_PAR_056);
	SEQ_PAR_057		= SEQ_057_SV;			/* úñHÝèV[PXTV	*/	//V05o
	DPB_SEND_2B(&SEQ_PAR_057);

//	SEQ_PAR_058		= SEQ_058_SV;			/* úñHÝèV[PXTW	*/

//2014/09/01
	SEQ_PAR_059		= SEQ_059_SV;			/* úñHÝèV[PXTX	*/
	DPB_SEND_2B(&SEQ_PAR_059);

//	SEQ_PAR_060		= SEQ_060_SV;			/* úñHÝèV[PXUO	*/
//	SEQ_PAR_061		= SEQ_061_SV;			/* úñHÝèV[PXUP	*/
//	SEQ_PAR_062		= SEQ_062_SV;			/* úñHÝèV[PXUQ	*/
//	SEQ_PAR_063		= SEQ_063_SV;			/* úñHÝèV[PXUR	*/
//	SEQ_PAR_064		= SEQ_064_SV;			/* úñHÝèV[PXUS	*/
//	SEQ_PAR_065		= SEQ_065_SV;			/* úñHÝèV[PXUT	*/
//	SEQ_PAR_066		= SEQ_066_SV;			/* úñHÝèV[PXUU	*/
//	SEQ_PAR_067		= SEQ_067_SV;			/* úñHÝèV[PXUV	*/
//	SEQ_PAR_068		= SEQ_068_SV;			/* úñHÝèV[PXUW	*/
//	SEQ_PAR_069		= SEQ_069_SV;			/* úñHÝèV[PXUX	*/
//
//	SEQ_PAR_070		= SEQ_070_SV;			/* úñHÝèV[PXVO	*/
//	SEQ_PAR_071		= SEQ_071_SV;			/* úñHÝèV[PXVP	*/
//	SEQ_PAR_072		= SEQ_072_SV;			/* úñHÝèV[PXVQ	*/
//	SEQ_PAR_073		= SEQ_073_SV;			/* úñHÝèV[PXVR	*/
//	SEQ_PAR_074		= SEQ_074_SV;			/* úñHÝèV[PXVS	*/
//	SEQ_PAR_075		= SEQ_075_SV;			/* úñHÝèV[PXVT	*/
//	SEQ_PAR_076		= SEQ_076_SV;			/* úñHÝèV[PXVU	*/
//	SEQ_PAR_077		= SEQ_077_SV;			/* úñHÝèV[PXVV	*/
//	SEQ_PAR_078		= SEQ_078_SV;			/* úñHÝèV[PXVW	*/
//	SEQ_PAR_079		= SEQ_079_SV;			/* úñHÝèV[PXVX	*/

	SEQ_PAR_080	= SV_TIMER1_A1;					//à^C}P
	DPB_SEND_2B(&SEQ_PAR_080);
	SEQ_PAR_081	= SV_TIMER2_A1;					//à^C}Q
	DPB_SEND_2B(&SEQ_PAR_081);
	SEQ_PAR_082	= SV_TIMER3_A1;					//à^C}R
	DPB_SEND_2B(&SEQ_PAR_082);
	SEQ_PAR_083	= SV_TIMER4_A1;					//O^C}	V05r
	DPB_SEND_2B(&SEQ_PAR_083);

	SEQ_PAR_088	= SV_COUNT1_A1;					//àJE^P
	DPB_SEND_2B(&SEQ_PAR_088);
	SEQ_PAR_089	= SV_COUNT2_A1;					//àJE^Q
	DPB_SEND_2B(&SEQ_PAR_089);
	SEQ_PAR_090	= SV_COUNT3_A1;					//àJE^R
	DPB_SEND_2B(&SEQ_PAR_090);

//V01v:ÇÁ(»ÝÌßØÝ¸ÞæÊÌÝèlAÆè ¦¸¼°¹Ý½ÆêÉ]·éB)
	SVP_SMPSTR_KAJ	= SV_SMPSTR_KAJ;			// »ÝÌßØÝ¸Þ@ÄØ¶Þ×d
	DPB_SEND_2B(&SVP_SMPSTR_KAJ);
	SVP_SMPSTR_AGL	= SV_SMPSTR_AGL;			//  »ÝÌßØÝ¸Þ@ÄØ¶Þpx
	DPB_SEND_2B(&SVP_SMPSTR_AGL);
	SVP_SMPSTR_FUK	= SV_SMPSTR_FUK;			//  »ÝÌßØÝ¸Þ@ÄØ¶Þ×¦
	DPB_SEND_2B(&SVP_SMPSTR_FUK);
	SVP_SMPSTR_SEH	= SV_SMPSTR_SEH;			//  »ÝÌßØÝ¸Þ@ÄØ¶Þ¼°¹Ý½iãÊ±ÄÞÚ½j
	DPB_SEND_2B(&SVP_SMPSTR_SEH);
	SVP_SMPSTR_SQL	= SV_SMPSTR_SQL;			//  »ÝÌßØÝ¸Þ@ÄØ¶Þ¼°¹Ý½iºÊ±ÄÞÚ½j
	DPB_SEND_2B(&SVP_SMPSTR_SQL);
	SVP_SMPMAX_CNT	= SV_SMPMAX_CNT;			//  »ÝÌßØÝ¸Þ@ÅåÂ
	DPB_SEND_2B(&SVP_SMPMAX_CNT);
	SVP_SMPTRG_CNT	= SV_SMPTRG_CNT;			//  »ÝÌßØÝ¸Þ@ÌßØÄØ¶ÞÂ
	DPB_SEND_2B(&SVP_SMPTRG_CNT);
	SVP_SMPCYC_TIM	= SV_SMPCYC_TIM;			//  »ÝÌßØÝ¸Þ@üú
	DPB_SEND_2B(&SVP_SMPCYC_TIM);

//2014/09/03
	SVP_SMPMAX_CNT2	= SV_SMPMAX_CNT2;			//  »ÝÌßØÝ¸Þ@ÅåÂ(SIT)
	DPB_SEND_2B(&SVP_SMPMAX_CNT2);
	SVP_SMPCYC_TIM2	= SV_SMPCYC_TIM2;			//  »ÝÌßØÝ¸Þ@üú
	DPB_SEND_2B(&SVP_SMPCYC_TIM2);

//V01z:ÇÁ(»ÝÌßØÝ¸ÞæÊÌÝèlAÆè ¦¸¼°¹Ý½ÆêÉ]·éB)
	SVP_SMP_CNT	= SV_SMP_CNT;				//  »ÝÌßØÝ¸ÞûW`®@
	DPB_SEND_2B(&SVP_SMP_CNT);
	SVP_TRD_CNT	= SV_TRD_CNT;				//  ÄÚÝÄÞûW`®@
	DPB_SEND_2B(&SVP_TRD_CNT);

//V05o:ÇÁ(»ÝÌßØÝ¸ÞÝèæÊAÄÚÝÄÞÝèæÊÌÝèlAÆè ¦¸¼°¹Ý½ÆêÉ]·éB)
	SVP_SMPTRG_CNT1	= SV_SMPTRG_CNT1;			//  »ÝÌßØÝ¸Þ@ÌßØÄØ¶ÞÂiSITpj
	DPB_SEND_2B(&SVP_SMPTRG_CNT1);
	SVP_TRDCSR_RNAU	= cnv_inch_mm(SV_TRDCSR_RNAU, 0);	/* ½×²ÄÞãÀoÊu	*/
	DPB_SEND_4B(&SVP_TRDCSR_RNAU);
	SVP_TRDCSR_RNAD	= cnv_inch_mm(SV_TRDCSR_RNAD, 0);	/* ½×²ÄÞãÀoÊu	*/ 
	DPB_SEND_4B(&SVP_TRDCSR_RNAD);

//V05r:ÇÁ(ÁU@\ÝèæÊAÆè ¦¸¼°¹Ý½ÆêÉ]·éB)
	SVP_MAX_KJYU	= SV_MAXKA2_A24;		//Åå×dÝè(µÌß¼®ÝÉµ©È¢)
	DPB_SEND_2B(&SVP_MAX_KJYU);
	SVP_VIB_KJYU_TTL= SV_KASIN_KAJ;			//vibration(U®)×d
	DPB_SEND_2B(&SVP_VIB_KJYU_TTL);

//2014/03/17
	SVP_KAJAREA_SNO	= SV_KAJAREA_SNO;		//×dªèÍÍ JnHöNo.
	SVP_KAJAREA_SAG	= SV_KAJAREA_SAG;		//×dªèÍÍ Jnpx
	SVP_KAJAREA_ENO	= SV_KAJAREA_ENO;		//×dªèÍÍ I¹HöNo.
	SVP_KAJAREA_EAG	= SV_KAJAREA_EAG;		//×dªèÍÍ I¹px
	SVP_KAJAREA_SEL	= SV_KAJAREA_SEL;		//L^×dIð

}
/****************************************************************************/
