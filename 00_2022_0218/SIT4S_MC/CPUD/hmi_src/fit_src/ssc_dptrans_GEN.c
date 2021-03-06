/****************************************************************************/
/*																			*/
/*	R}cY@aü¯	rhs|rRg[								*/
/*																			*/
/*						coq`l © eq`l	f[^]				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include "ssc_ver1.h"							//eíÌ¤Êè`
#include	"cm_equ1.h"		//MCÉÄª£

#include	"ssc_def.h"							//eíÌ¤Êè`
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
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_GEN	(void)
{
//2002-10-16
//	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* @B´_üÍ			*/
//2014/12/11	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* @B´_üÍ			*/
	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* @B´_üÍ mmÅè	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORG_POS1);


	SVP_RNAORGMEM_LEG1	= cnv_inch_mm(SV_RNAORGMEM_LEG1, 2);	/* @B´_üÍ	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG1);
	SVP_RNAORGMEM_LEG2	= cnv_inch_mm(SV_RNAORGMEM_LEG2, 2);	/* @B´_üÍ	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG2);


	if(DEB_WORD_FLG1 == 0x05a)		/* V01n_b */
	{
		PV_DEB_WORD_WK1 = PV_DEB_WORD_WK1 + 1;
	}
	DEB_WORD_FLG1 = 0x05a;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l ¨ eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_GET_SENS		(void)
{
	/* jAZTf[^Àªlðeq`lÉÛ¶·éB*/

	PV_NOW_POS		= PVP_RENIA_POSI0;				/* jAZT»ÝÊu	*/
//	PV_NOW_POS		= PVP_NOW_POSI000;				/* »ÝÊu	 			*/
	PV_ENCOD_BCD	= PVP_NOW_ANGLE00;				/* »Ýpx				*/
	PV_CYCLE_TIME	= PVP_CYCLE_TIME0;				/* TCNÔ			*/

	PV_RNAORG_PLS1	= PVP_RNAORG_PLS1;				/* ØÆ±îÊuÊßÙ½		*/

//2002-10-10:ÇÁ
	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* ØÆ±îÊuÊßÙ½		*/


	PV_BAKORG_PLS1	= PVP_BAKORG_PLS1;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	PV_BAKORG_PLS2	= PVP_BAKORG_PLS2;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* ØÆ±îÊuÊßÙ½	COP2	*/


	PV_DEB_WORD_WK2 = PV_DEB_WORD_WK2 + 1;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_BACK_SENS	(void)
{
	/* eq`lÉÛ¶µ½jAZTf[^ðcoq`lÉ³·éB*/

	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* ØÆ±îÊuÊßÙ½		*/
	DPB_SEND_4B((U4b *)&SVB_RNAORG_PLS1);

	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS2);
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* ØÆ±îÊuÊßÙ½	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_RENIA_BUP1	= PV_RENIA_BUP1;				//jAXP[obNAbvp
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP1);
	SVB_RENIA_BUP2	= PV_RENIA_BUP2;				//jAXP[obNAbvp
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP2);
	SVB_RENIA_BUP3	= PV_RENIA_BUP3;				//jAXP[obNAbvp
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP3);
	SVB_RENIA_BUP4	= PV_RENIA_BUP4;				//jAXP[obNAbvp
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP4);

	SVB_ARA1_KAJ_T2	= PV_ARA1_KAJ_T2;				//×dÀª½Ï		V02a
	DPB_SEND_2B((U2b *)&SVB_ARA1_KAJ_T2);

}
/****************************************************************************/
