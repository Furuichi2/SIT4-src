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

/* OQÆÖè` -------------------------------------------------- */
extern	void	DPB_SEND_2B(U2b *Src);

/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SYS	(void)
{
	SEQ_PAR_016		= SEQ_016_SV;			/* úñHÝèV[PXPU	*/
	DPB_SEND_2B(&SEQ_PAR_016);
	SEQ_PAR_017		= SEQ_017_SV;			/* úñHÝèV[PXPV	*/
	DPB_SEND_2B(&SEQ_PAR_017);
	SEQ_PAR_018		= SEQ_018_SV;			/* úñHÝèV[PXPW	*/
	DPB_SEND_2B(&SEQ_PAR_018);
	SEQ_PAR_019		= SEQ_019_SV;			/* úñHÝèV[PXPX	*/
	DPB_SEND_2B(&SEQ_PAR_019);
	SEQ_PAR_020		= SEQ_020_SV;			/* úñHÝèV[PXQO	*/
	DPB_SEND_2B(&SEQ_PAR_020);
	SEQ_PAR_021		= SEQ_021_SV;			/* úñHÝèV[PXQP	*/
	DPB_SEND_2B(&SEQ_PAR_021);
	SEQ_PAR_022		= SEQ_022_SV;			/* úñHÝèV[PXQQ	*/
	DPB_SEND_2B(&SEQ_PAR_022);
	SEQ_PAR_023		= SEQ_023_SV;			/* úñHÝèV[PXQR	*/
	DPB_SEND_2B(&SEQ_PAR_023);
	SEQ_PAR_024		= SEQ_024_SV;			/* úñHÝèV[PXQS	*/
	DPB_SEND_2B(&SEQ_PAR_024);
	SEQ_PAR_025		= SEQ_025_SV;			/* úñHÝèV[PXQT	*/
	DPB_SEND_2B(&SEQ_PAR_025);
	SEQ_PAR_026		= SEQ_026_SV;			/* úñHÝèV[PXQU	*/
	DPB_SEND_2B(&SEQ_PAR_026);
	SEQ_PAR_027		= SEQ_027_SV;			/* úñHÝèV[PXQV	*/
	DPB_SEND_2B(&SEQ_PAR_027);
	SEQ_PAR_028		= SEQ_028_SV;			/* úñHÝèV[PXQW	*/
	DPB_SEND_2B(&SEQ_PAR_028);
	SEQ_PAR_029		= SEQ_029_SV;			/* úñHÝèV[PXQX	*/
	DPB_SEND_2B(&SEQ_PAR_029);
	SEQ_PAR_030		= SEQ_030_SV;			/* úñHÝèV[PXRO	*/
	DPB_SEND_2B(&SEQ_PAR_030);

}
/****************************************************************************/
