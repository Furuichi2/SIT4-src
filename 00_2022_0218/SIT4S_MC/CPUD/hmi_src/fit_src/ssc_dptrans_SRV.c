/****************************************************************************/
/*																			*/
/*	R}cY@aό―	rhs|rRg[								*/
/*																			*/
/*						coq`l © eq`l	f[^]				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//eνΜ€Κθ`
#include	"cm_equ1.h"		//MCΙΔͺ£

#include "ssc_def.h"							//eνΜ€Κθ`
#include "ssc_ext.h"							//QΖΦθ`
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_wk_ext.h"

/* OQΖΟθ` -------------------------------------------------- */
extern	UNs		GMN_PAR020;

/* OQΖΦθ` -------------------------------------------------- */
extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SRV	(void)
{
	S4b		ofs;

	SVP_RNADIR_SEL1		= SV_RNADIR_SEL1;				/* ΨΖ±Ύέ»Ι«			*/
	DPB_SEND_2B(&SVP_RNADIR_SEL1);
	SVP_INCDIR_SEL1		= SV_INCDIR_SEL1;				/* PGΙ«				*/
	DPB_SEND_2B(&SVP_INCDIR_SEL1);
	SVP_INCPLS_1REV		= SV_INCPLS_1REV;				/* PG1ρ]ΚίΩ½Iπ		*/
	DPB_SEND_2B(&SVP_INCPLS_1REV);
	SVP_INCPLS_HOSN		= SV_INCPLS_HOSN;				/* PGβ³N Σ°ΐNρ		*/
	DPB_SEND_2B(&SVP_INCPLS_HOSN);
	SVP_INCPLS_HOSM		= SV_INCPLS_HOSM;				/* PGβ³M ΈΧέΈpM		*/
	DPB_SEND_2B(&SVP_INCPLS_HOSM);
	SVP_MOTRPM_MAXM		= SV_MOTRPM_MAXM;				/* Σ°ΐΕερ]		*/
	DPB_SEND_2B(&SVP_MOTRPM_MAXM);
	SVP_MOTMAX_FREQ		= SV_MOTMAX_FREQ;				/* Σ°ΐΕεwίόg	*/
	DPB_SEND_4B((U4b *)&SVP_MOTMAX_FREQ);
//2002-10-16
//	SVP_RNAORG_POS1		= SV_RNAORG_POS1;				/* @B΄_όΝ			*/
//	SVP_RNAPOS_MAXP		= SV_RNAPOS_MAXP;				/* @Bγΐ				*/
//	SVP_RNAPOS_MINP		= SV_RNAPOS_MINP;				/* @BΊΐ				*/
//2014/12/11	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* @B΄_όΝ			*/
	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* @B΄_όΝ	mmΕθ	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORG_POS1);

//V06n
//	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV_RNAPOS_MAXP, 2);	/* @Bγΐ				*/
//	SVP_RNAPOS_MINP	= cnv_inch_mm(SV_RNAPOS_MINP, 2);	/* @BΊΐ				*/
//2014/12/11	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV0_RNAPOS_MAXO, 2);	/* @Bγΐ				*/
	SVP_RNAPOS_MAXP	= SV0_RNAPOS_MAXO;					/* @Bγΐ		mmΕθ	*/
	DPB_SEND_4B(&SVP_RNAPOS_MAXP);
//2014/12/11	SVP_RNAPOS_MINP	= cnv_inch_mm(SV0_RNAPOS_MINO, 2);	/* @BΊΐ				*/
	SVP_RNAPOS_MINP	= SV0_RNAPOS_MINO;					/* @BΊΐ		mmΕθ	*/
	DPB_SEND_4B(&SVP_RNAPOS_MINP);

//V01 (MOV)	SVP_DNDINC_SPD1		= SV_DNDINC_SPD1;				/* iζ¬x				*/
	SVP_UPAREA_SPD1		= SV_UPAREA_SPD1;				/* ?@_A¬x		*/
	DPB_SEND_2B(&SVP_UPAREA_SPD1);
	SVP_STDINC_SPD1		= SV_STDINC_SPD1;				/* ‘?¬x				*/
	DPB_SEND_2B(&SVP_STDINC_SPD1);
	SVP_REVDAT_SPD1		= SV_REVDAT_SPD1;				/* \υ¬xP			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD1);
	SVP_REVDAT_SPD2		= SV_REVDAT_SPD2;				/* \υ¬xQ			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD2);
	SVP_REVDAT_SPD3		= SV_REVDAT_SPD3;				/* \υ¬xR			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD3);
	SVP_TEPDAT_SPD1		= SV_TEPDAT_SPD1;				/* θ?ΚίΩ»¬x			*/
	DPB_SEND_2B(&SVP_TEPDAT_SPD1);
	SVP_TEPLAT_DAT1		= SV_TEPLAT_DAT1;				/* θ?ΚίΩ»α{¦		*/
	DPB_SEND_2B(&SVP_TEPLAT_DAT1);
	SVP_TEPLAT_DAT2		= SV_TEPLAT_DAT2;				/* θ?ΚίΩ»{¦		*/
	DPB_SEND_2B(&SVP_TEPLAT_DAT2);

	SVP_INCPOS_KP01		= SV_INCPOS_KP01;				/* PGΚuδαΉή²έ		*/
	DPB_SEND_2B(&SVP_INCPOS_KP01);
	SVP_RNAPOS_KP01		= SV_RNAPOS_KP01;				/* ΨΖ±ΚuδαΉή²έ		*/
	DPB_SEND_2B(&SVP_RNAPOS_KP01);
	SVP_ACCLAT_TIM1		= SV_ACCLAT__TIM1;				/* ΑΈ¬Τ			*/
	DPB_SEND_2B(&SVP_ACCLAT_TIM1);
	SVP_SSCURV_TIM1		= SV_SSCURV_TIM1;				/* rΤ				*/
	DPB_SEND_2B(&SVP_SSCURV_TIM1);
//2002-10-16
//	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* γ_²έΞίΌήΌ?έ		*/
//	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* Ί_²έΞίΌήΌ?έ		*/
//	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* ΪWΚu²έΞίΌήΌ?έ	*/
/* V00m */
//	SVP_UPAREA_INP1	= cnv_inch_mm(SV_UPAREA_INP1, 2);	/* γ_²έΞίΌήΌ?έ		*/
//	SVP_DNAREA_INP1	= cnv_inch_mm(SV_DNAREA_INP1, 2);	/* Ί_²έΞίΌήΌ?έ		*/
//	SVP_OBJARA_INP1	= cnv_inch_mm(SV_OBJARA_INP1, 2);	/* ΪWΚu²έΞίΌήΌ?έ	*/
	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* \υ		*/
	DPB_SEND_2B(&SVP_UPAREA_INP1);
	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* @BLΡΚΐE		*/
	DPB_SEND_2B(&SVP_DNAREA_INP1);
	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* ρ]₯΅°Μίέ²έΞίΌήΌ?έ	*/
	DPB_SEND_2B(&SVP_OBJARA_INP1);

	SVP_INPPOS_TIM1		= SV_INPPOS_TIM1;				/* ²έΞίΌήΌ?έΑͺ―ΈΤ	*/
	DPB_SEND_2B(&SVP_INPPOS_TIM1);

//2002-10-16
//	SVP_ARACHK_LNG1		= SV_ARACHK_LNG1;				/* γ^Ί_Κί»θΚ	*/
//2014/12/11	SVP_ARACHK_LNG1	= cnv_inch_mm(SV_ARACHK_LNG1, 2);	/* γ^Ί_Κί»θΚ	*/
	SVP_ARACHK_LNG1	= SV_ARACHK_LNG1;				;	/* γ^Ί_Κί»θΚ		mmΕθ	*/
	DPB_SEND_2B(&SVP_ARACHK_LNG1);
	SVP_UPAREA_DIG1		= SV_UPAREA_DIG1; 				/* ρ]?@_(γ_)	*/
	DPB_SEND_2B(&SVP_UPAREA_DIG1);

	SVP_UPAREA_JUDG		= SV_UPAREA_JUDG;				/* γ_»θΝΝ		*/
	DPB_SEND_4B(&SVP_UPAREA_JUDG);
	SVP_DNAREA_JUDG		= SV_DNAREA_JUDG;				/* ½]έθsΒΝΝ		*/
	DPB_SEND_4B(&SVP_DNAREA_JUDG);
//2002-10-16
//2002-08-21:ΗΑ
//	SVP_RNA_STLORK		= SV_RNA_STLORK;				//Xg[Nέθ(4)
//2014/12/11	SVP_RNA_STLORK	= cnv_inch_mm(SV_RNA_STLORK, 2);	//Xg[Nέθ(4)
	SVP_RNA_STLORK	= SV_RNA_STLORK;					//Xg[Nέθ(4)		mmΕθ
	DPB_SEND_4B((U4b *)&SVP_RNA_STLORK);
	SVP_OUTPLS_HOSA		= SV_OUTPLS_HOSA;				//oΝΚίΩ½β³A(2)
	DPB_SEND_2B(&SVP_OUTPLS_HOSA);
	SVP_OUTPLS_HOSB		= SV_OUTPLS_HOSB;				//oΝΚίΩ½β³B(2)
	DPB_SEND_2B(&SVP_OUTPLS_HOSB);
	SVP_UPHOLD_DIG		= SV_UPHOLD_DIG;				//γΈΞ°ΩΔήpx(2)
	DPB_SEND_2B(&SVP_UPHOLD_DIG);
	SVP_MACINE_SEL1		= SV_MACINE_SEL1;				//\υi@νIπPj(2)
	DPB_SEND_2B(&SVP_MACINE_SEL1);

	SVP_INCHEN_ELNG		= SV_INCHEN_ELNG;				/* PGΞ·Ων			*/
	DPB_SEND_2B(&SVP_INCHEN_ELNG);
	SVP_INCENC_ELNG		= SV_INCENC_ELNG;				/* PG-ENCκvΚ			*/
	DPB_SEND_2B(&SVP_INCENC_ELNG);
//2002-10-16
//	SVP_INCRNA_ELNG		= SV_INCRNA_ELNG;				/* PG-ΨΖ±κvΚ			*/
//2014/12/11	SVP_INCRNA_ELNG	= cnv_inch_mm(SV_INCRNA_ELNG, 2);	/* PG-ΨΖ±κvΚ			*/
	SVP_INCRNA_ELNG	= SV_INCRNA_ELNG;					/* PG-ΨΖ±κvΚ		mmΕθ	*/
	DPB_SEND_2B(&SVP_INCRNA_ELNG);
	SVP_INCSTP_ELNG		= SV_INCSTP_ELNG;				/* PGβ~ΩνΚ			*/
	DPB_SEND_2B(&SVP_INCSTP_ELNG);
//2002-10-16
//	SVP_RNASTP_ELNG		= SV_RNASTP_ELNG;				/* ΨΖ±β~ΩνΚ		*/
//2014/12/11	SVP_RNASTP_ELNG	= cnv_inch_mm(SV_RNASTP_ELNG, 2);	/* ΨΖ±β~ΩνΚ		*/
	SVP_RNASTP_ELNG	= SV_RNASTP_ELNG;					/* ΨΖ±β~ΩνΚ	mmΕθ	*/
	DPB_SEND_2B(&SVP_RNASTP_ELNG);
	SVP_INCREV_ELNG		= SV_INCREV_ELNG;				/* PGt]ΩνΚ			*/
	DPB_SEND_2B(&SVP_INCREV_ELNG);
//2002-10-16
//	SVP_RNAREV_ELNG		= SV_RNAREV_ELNG;				/* ΨΖ±t]ΩνΚ		*/
//	SVP_DAIHAI_LNG1		= SV_DAIHAI_LNG1;				/* ΐή²Κ²Δβ³δrl(¬)	*/
//	SVP_DAIHAI_LNG2		= SV_DAIHAI_LNG2;				/* ΐή²Κ²Δβ³δrl()	*/
//	SVP_DAIHAI_LNG3		= SV_DAIHAI_LNG3;				/* ΐή²Κ²Δβ³δrl(ε)	*/
//2014/12/11	SVP_RNAREV_ELNG	= cnv_inch_mm(SV_RNAREV_ELNG, 2);	/* ΨΖ±t]ΩνΚ		*/
	SVP_RNAREV_ELNG	= SV_RNAREV_ELNG;					/* ΨΖ±t]ΩνΚ	mmΕθ	*/
	DPB_SEND_2B(&SVP_RNAREV_ELNG);

//V06n
//	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV_DAIHAI_LNG1, 2);	/* ΐή²Κ²Δβ³δrl(¬)	*/
//	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV_DAIHAI_LNG2, 2);	/* ΐή²Κ²Δβ³δrl()	*/
//2014/12/11	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV0_DAIHAI_LNG1O, 2);	/* ΐή²Κ²Δβ³δrl(¬)	*/
	SVP_DAIHAI_LNG1	= SV0_DAIHAI_LNG1O;					/* ΐή²Κ²Δβ³δrl(¬)		mmΕθ	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG1);
//2014/12/11	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV0_DAIHAI_LNG2O, 2);	/* ΐή²Κ²Δβ³δrl()	*/
//2015/09/29	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV0_DAIHAI_LNG2O, 2);	/* ΐή²Κ²Δβ³δrl()		mmΕθ	*/
	SVP_DAIHAI_LNG2	= SV0_DAIHAI_LNG2O;					/* ΐή²Κ²Δβ³δrl()		mmΕθ	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG2);

//2014/12/11	SVP_DAIHAI_LNG3	= cnv_inch_mm(SV_DAIHAI_LNG3, 2);	/* ΐή²Κ²Δβ³δrl(ε)	*/
	SVP_DAIHAI_LNG3	= SV_DAIHAI_LNG3;					/* ΐή²Κ²Δβ³δrl(ε)		mmΕθ	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG3);

	SVP_AMPERR_VLT1		= SV_AMPERR_VLT1;				/* ίΧd³1			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT1);
	SVP_AMPERR_TIM1		= SV_AMPERR_TIM1;				/* ίΧΤ1			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM1);
	SVP_AMPERR_VLT2		= SV_AMPERR_VLT2;				/* ίΧd³2			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT2);
	SVP_AMPERR_TIM2		= SV_AMPERR_TIM2;				/* ίΧΤ2			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM2);
	SVP_AMPERR_VLT3		= SV_AMPERR_VLT3;				/* ίΧd³3			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT3);
	SVP_AMPERR_TIM3		= SV_AMPERR_TIM3;				/* ίΧΤ3			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM3);

//2002-08-08:ΗΑ
//	SVP_BREAK_DIG		= SV_BRDIG_C1 * 10;				//ΜήΪ°·px   0.1x
	SVP_BREAK_DIG		= SV_BRDIG_C1;					//ΜήΪ°·px   0.1x
	DPB_SEND_2B(&SVP_BREAK_DIG);
	SVP_BREAK_TIM1		= SV_BRTIME_C1;					//u[L^C}έθ
	DPB_SEND_2B(&SVP_BREAK_TIM1);

	SVP_CNT_CNT			= SV_RNZRPM_A12;				//A±ρ]έθl
	DPB_SEND_2B(&SVP_CNT_CNT);
	SVP_CNT_TIM			= SV_RNZTIM_A12;				//A±^C}έθl
	DPB_SEND_2B(&SVP_CNT_TIM);
	SVP_WT_DIG1			= SV_TAIKI1_A12;				//?@_Iπ1
	DPB_SEND_2B(&SVP_WT_DIG1);
	SVP_WT_DIG2			= SV_TAIKI2_A12;				//?@_Iπ2
	DPB_SEND_2B(&SVP_WT_DIG2);
	SVP_WT_DIG3			= SV_TAIKI3_A12;				//?@_Iπ3
	DPB_SEND_2B(&SVP_WT_DIG3);
	SVP_MOTWT_TIM		= SV_HOSTIM_A12;				//N?ΫΨΤ
	DPB_SEND_2B(&SVP_MOTWT_TIM);
	SVP_PSMOD_SEL		= SV_PSDIMD_A1;					//PSID@Σ°ΔήIπ
	DPB_SEND_2B(&SVP_PSMOD_SEL);

	/* V00m */
	SVP_NEG_OFS_LNG		= SV_NEG_OFS_LNG;				//½]Ίΐ£
	DPB_SEND_4B((U4b *)&SVP_NEG_OFS_LNG);
	SVP_AMP100P_VLT		= SV_AMP100P_VLT;				//ίΧΣΖΐ100%d³
	DPB_SEND_2B(&SVP_AMP100P_VLT);

	/* V01v */
	SVP_LSAABN_AGL1		= SV_LSAABN_AGL1;				//LSAΩνmΜpx1
	DPB_SEND_4B(&SVP_LSAABN_AGL1);
	SVP_LSAABN_AGL2		= SV_LSAABN_AGL2;				//LSAΩνmΜpx2
	DPB_SEND_4B(&SVP_LSAABN_AGL2);
	SVP_PLSALO_PLS		= SV_PLSALO_PLS;				//pT{¦α
	DPB_SEND_2B(&SVP_PLSALO_PLS);
	SVP_PLSAHI_PLS		= SV_PLSAHI_PLS;				//pT{¦
	DPB_SEND_2B(&SVP_PLSAHI_PLS);
	SVP_MOADR0_SQH		= SV_MOADR0_SQH;				// j^AhXO@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR0_SQH);
	SVP_MOADR0_SQL		= SV_MOADR0_SQL;				// j^AhXO@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR0_SQL);
	SVP_MOADR1_SQH		= SV_MOADR1_SQH;				// j^AhXP@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR1_SQH);
	SVP_MOADR1_SQL		= SV_MOADR1_SQL;				// j^AhXP@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR1_SQL);
	SVP_MOADR2_SQH		= SV_MOADR2_SQH;				// j^AhXQ@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR2_SQH);
	SVP_MOADR2_SQL		= SV_MOADR2_SQL;				// j^AhXQ@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR2_SQL);
	SVP_MOADR3_SQH		= SV_MOADR3_SQH;				// j^AhXR@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR3_SQH);
	SVP_MOADR3_SQL		= SV_MOADR3_SQL;				// j^AhXR@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR3_SQL);
	SVP_MOADR4_SQH		= SV_MOADR4_SQH;				// j^AhXS@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR4_SQH);
	SVP_MOADR4_SQL		= SV_MOADR4_SQL;				// j^AhXS@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR4_SQL);
	SVP_MOADR5_SQH		= SV_MOADR5_SQH;				// j^AhXT@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR5_SQH);
	SVP_MOADR5_SQL		= SV_MOADR5_SQL;				// j^AhXT@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR5_SQL);
	SVP_MOADR6_SQH		= SV_MOADR6_SQH;				// j^AhXU@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR6_SQH);
	SVP_MOADR6_SQL		= SV_MOADR6_SQL;				// j^AhXU@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR6_SQL);
	SVP_MOADR7_SQH		= SV_MOADR7_SQH;				// j^AhXV@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR7_SQH);
	SVP_MOADR7_SQL		= SV_MOADR7_SQL;				// j^AhXV@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR7_SQL);
	SVP_MOADR8_SQH		= SV_MOADR8_SQH;				// j^AhXW@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR8_SQH);
	SVP_MOADR8_SQL		= SV_MOADR8_SQL;				// j^AhXW@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR8_SQL);
	SVP_MOADR9_SQH		= SV_MOADR9_SQH;				// j^AhXX@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR9_SQH);
	SVP_MOADR9_SQL		= SV_MOADR9_SQL;				// j^AhXX@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADR9_SQL);
	SVP_MOADRA_SQH		= SV_MOADRA_SQH;				// j^AhXPO@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRA_SQH);
	SVP_MOADRA_SQL		= SV_MOADRA_SQL;				// j^AhXPO@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRA_SQL);
	SVP_MOADRB_SQH		= SV_MOADRB_SQH;				// j^AhXPP@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRB_SQH);
	SVP_MOADRB_SQL		= SV_MOADRB_SQL;				// j^AhXPP@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRB_SQL);
	SVP_MOADRC_SQH		= SV_MOADRC_SQH;				// j^AhXPQ@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRC_SQH);
	SVP_MOADRC_SQL		= SV_MOADRC_SQL;				// j^AhXPQ@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRC_SQL);
	SVP_MOADRD_SQH		= SV_MOADRD_SQH;				// j^AhXPR@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRD_SQH);
	SVP_MOADRD_SQL		= SV_MOADRD_SQL;				// j^AhXPR@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRD_SQL);
	SVP_MOADRE_SQH		= SV_MOADRE_SQH;				// j^AhXPS@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRE_SQH);
	SVP_MOADRE_SQL		= SV_MOADRE_SQL;				// j^AhXPS@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRE_SQL);
	SVP_MOADRF_SQH		= SV_MOADRF_SQH;				// j^AhXPT@Ό°Ήέ½γΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRF_SQH);
	SVP_MOADRF_SQL		= SV_MOADRF_SQL;				// j^AhXPT@Ό°Ήέ½ΊΚ@V01v@060713
	DPB_SEND_2B(&SVP_MOADRF_SQL);

	/* COP2ΦW */
	SVP_ORGSOK_PLS		= SV_ORGSOK_PLS;		//΄_ͺθΚίΩ½
	DPB_SEND_4B(&SVP_ORGSOK_PLS);
	SVP_ORGCAL_DAT1		= SV_ORGCAL_DAT1;		//ZW1
	DPB_SEND_4B(&SVP_ORGCAL_DAT1);
	SVP_ORGCAL_DAT2		= SV_ORGCAL_DAT2;		//ZW2
	DPB_SEND_4B(&SVP_ORGCAL_DAT2);
	SVP_ORGCAL_DAT3		= SV_ORGCAL_DAT3;		//ZW3
	DPB_SEND_4B(&SVP_ORGCAL_DAT3);
	SVP_ORGCAL_DAT4		= SV_ORGCAL_DAT4;		//ZW4
	DPB_SEND_4B(&SVP_ORGCAL_DAT4);
	SVP_ORGCAL_DAT5		= SV_ORGCAL_DAT5;		//ZW5
	DPB_SEND_4B(&SVP_ORGCAL_DAT5);
	SVP_ORGCAL_DAT6		= SV_ORGCAL_DAT6;		//ZW6
	DPB_SEND_4B(&SVP_ORGCAL_DAT6);
	SVP_ORGSTRK_LEN1	= SV_ORGSTRK_LEN1;		//½ΔΫ°Έ1
	DPB_SEND_4B(&SVP_ORGSTRK_LEN1);
	SVP_ORGSTRK_LEN2	= SV_ORGSTRK_LEN2;		//½ΔΫ°Έ2
	DPB_SEND_4B(&SVP_ORGSTRK_LEN2);
	SVP_RNAORGMEM_LEG1	= SV_RNAORGMEM_LEG1;	//ΨΖ±΄_1²L―
	DPB_SEND_4B(&SVP_RNAORGMEM_LEG1);
////	SVP_RNAORG_PLS1		= SV_RNAORG_PLS1;		//Κή―Έ±―Μίΐͺ
	SVP_RNAORGMEM_LEG2	= SV_RNAORGMEM_LEG2;	//ΨΖ±΄_2²L―
	DPB_SEND_4B(&SVP_RNAORGMEM_LEG2);
////	SVP_RNAORG_PLS2		= SV_RNAORG_PLS2;		//Κή―Έ±―Μίΐͺ
////	SVP_RNAORG_SIN1		= SV_RNAORG_SIN1;		//Κή―Έ±―Μίΐͺ
////	SVP_RNAORG_SIN2		= SV_RNAORG_SIN2;		//Κή―Έ±―Μίΐͺ
	SVP_ORGRUP_DEG		= SV_ORGRUP_DEG;		//΄_EζΤγ
	DPB_SEND_2B(&SVP_ORGRUP_DEG);
	SVP_ORGRDN_DEG		= SV_ORGRDN_DEG;		//΄_EζΤΊ
	DPB_SEND_2B(&SVP_ORGRDN_DEG);
	SVP_ORGLUP_DEG		= SV_ORGLUP_DEG;		//΄_ΆζΤγ
	DPB_SEND_2B(&SVP_ORGLUP_DEG);
	SVP_ORGLDN_DEG		= SV_ORGLDN_DEG;		//΄_ΆζΤΊ
	DPB_SEND_2B(&SVP_ORGLDN_DEG);
	SVP_ORGMEM_DEG1		= SV_ORGMEM_DEG1;		//px1²
	DPB_SEND_2B(&SVP_ORGMEM_DEG1);
	SVP_ORGMEM_DEGS1	= SV_ORGMEM_DEGS1;		//px1²@ON/OFF
	DPB_SEND_2B(&SVP_ORGMEM_DEGS1);
	SVP_ORGMEM_DEG2		= SV_ORGMEM_DEG2;		//px2²
	DPB_SEND_2B(&SVP_ORGMEM_DEG2);
	SVP_ORGMEM_DEGS2	= SV_ORGMEM_DEGS2;		//px2²@ON/OFF
	DPB_SEND_2B(&SVP_ORGMEM_DEGS2);
	SVP_ORGMPL_SEL1		= SV_ORGMPL_SEL1;		//θΚίΩ»Iπ1²@ON/OFF
	DPB_SEND_2B(&SVP_ORGMPL_SEL1);
	SVP_ORGMPL_SEL2		= SV_ORGMPL_SEL2;		//θΚίΩ»Iπ2²@ON/OFF
	DPB_SEND_2B(&SVP_ORGMPL_SEL2);
	SVP_HOSRAG_PLS1		= SV_HOSRAG_PLS1;		//²Τβ³ΝΝP
	DPB_SEND_2B(&SVP_HOSRAG_PLS1);
	SVP_HOSRAG_PLS2		= SV_HOSRAG_PLS2;		//²Τβ³ΝΝQ
	DPB_SEND_2B(&SVP_HOSRAG_PLS2);
	SVP_HOSEI_SPD		= SV_HOSEI_SPD;			//β³¬x
	DPB_SEND_2B(&SVP_HOSEI_SPD);
	SVP_MANSAM_LEN		= SV_MANSAM_LEN;		//θ?―ϊ
	DPB_SEND_2B(&SVP_MANSAM_LEN);
	SVP_DANSAM_LEN		= SV_DANSAM_LEN;		//iζ―ϊ
	DPB_SEND_2B(&SVP_DANSAM_LEN);
	SVP_RUNSAMER_LEN1	= SV_RUNSAMER_LEN1;		//^]―ϊΩνP
	DPB_SEND_2B(&SVP_RUNSAMER_LEN1);
	SVP_RUNSAMER_LEN2	= SV_RUNSAMER_LEN2;		//^]―ϊΩνQ
	DPB_SEND_2B(&SVP_RUNSAMER_LEN2);
	SVP_MANSAMER_PLS	= SV_MANSAMER_PLS;		//θ?―ϊΩν
	DPB_SEND_2B(&SVP_MANSAMER_PLS);
	SVP_RUNSAMER_PLS	= SV_RUNSAMER_PLS;		//^]―ϊΩν
	DPB_SEND_2B(&SVP_RUNSAMER_PLS);
	SVP_RNADIR_SEL2		= SV_RNADIR_SEL2;		/* ΨΖ±Ύέ»Ι«			*/
	DPB_SEND_2B(&SVP_RNADIR_SEL2);
	SVP_ORGMEM_DEG1A	= SV_ORGMEM_DEG1A;		//px1²
	DPB_SEND_4B(&SVP_ORGMEM_DEG1A);
	SVP_ORGMEM_DEG2A	= SV_ORGMEM_DEG2A;		//px2²
	DPB_SEND_4B(&SVP_ORGMEM_DEG2A);

//V05c
	SVP_FCLS_STR_DEG	= SV_FCLS_STR_DEG	;//ΜΩΈΫJnpx
	DPB_SEND_2B(&SVP_FCLS_STR_DEG);
	SVP_FCLS_STR_HENS	= SV_FCLS_STR_HENS	;//ΜΩΈΫJnΞ·
	DPB_SEND_2B(&SVP_FCLS_STR_HENS);
	SVP_FCLS_ZIKI_SPD1	= SV_FCLS_ZIKI_SPD1	;//ΜΩΈΫ©N?¬x1
	DPB_SEND_2B(&SVP_FCLS_ZIKI_SPD1);
	SVP_FCLS_ZIKI_SPD2	= SV_FCLS_ZIKI_SPD2	;//ΜΩΈΫ©N?¬x2
	DPB_SEND_2B(&SVP_FCLS_ZIKI_SPD2);
	SVP_SYNC_ERR_DEGA	= SV_SYNC_ERR_DEGA	;//―ϊΩνΜζpxA
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGA);
	SVP_SYNC_ERR_DEGB	= SV_SYNC_ERR_DEGB	;//―ϊΩνΜζpxB
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGB);
	SVP_SYNC_ERR_DEGC	= SV_SYNC_ERR_DEGC	;//―ϊΩνΜζpxC
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGC);
	SVP_SYNC_ERR_DEGD	= SV_SYNC_ERR_DEGD	;//―ϊΩνΜζpxD
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGD);
	SVP_SYNC_ERR_RNAA	= SV_SYNC_ERR_RNAA	;//ΨΖ±―ϊΩνA
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAA);
	SVP_SYNC_ERR_RNAB	= SV_SYNC_ERR_RNAB	;//ΨΖ±―ϊΩνB
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAB);
	SVP_SYNC_ERR_RNAC	= SV_SYNC_ERR_RNAC	;//ΨΖ±―ϊΩνC
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAC);
	SVP_SYNC_ERR_RNAD	= SV_SYNC_ERR_RNAD	;//ΨΖ±―ϊΩνD
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAD);
	SVP_SYNC_ERR_PGA	= SV_SYNC_ERR_PGA	;//PG―ϊΩνA
	DPB_SEND_2B(&SVP_SYNC_ERR_PGA);
	SVP_SYNC_ERR_PGB	= SV_SYNC_ERR_PGB	;//PG―ϊΩνB
	DPB_SEND_2B(&SVP_SYNC_ERR_PGB);
	SVP_SYNC_ERR_PGC	= SV_SYNC_ERR_PGC	;//PG―ϊΩνC
	DPB_SEND_2B(&SVP_SYNC_ERR_PGC);
	SVP_SYNC_ERR_PGD	= SV_SYNC_ERR_PGD	;//PG―ϊΩνD
	DPB_SEND_2B(&SVP_SYNC_ERR_PGD);

//V05r
	SVP_BREAK_DIG_RAT	= SV_BRDIG_C2;		//ΜήΪ°·px   
	DPB_SEND_2B(&SVP_BREAK_DIG_RAT);
	SVP_BREAK_TIM_RAT	= SV_BRTIME_C2;		//u[L^C}	
	DPB_SEND_2B(&SVP_BREAK_TIM_RAT);

//V06
	SVP_EP_VOF		= SV_SRVPAR_B0;		// T[{p[^B0@@dΝp΅ΜΎ―Δ
	DPB_SEND_2B(&SVP_EP_VOF);
	SVP_EP_VMX		= SV_SRVPAR_B1;		// T[{p[^B1@@dΝpΕεl
	DPB_SEND_2B(&SVP_EP_VMX);
	SVP_EP_TRQ		= SV_SRVPAR_B2;		// T[{p[^B2@@dΝpΔΩΈl
	DPB_SEND_2B(&SVP_EP_TRQ);
	SVP_EP_LTM		= SV_SRVPAR_B3;		// T[{p[^B3@@ΔΩΈ€xκΤ
	DPB_SEND_2B(&SVP_EP_LTM);
	SVP_EP_K1		= SV_SRVPAR_B4;		// T[{p[^B4@@²?WA
	DPB_SEND_2B(&SVP_EP_K1);
	SVP_EP_K2		= SV_SRVPAR_B5;		// T[{p[^B5@@²?WB
	DPB_SEND_2B(&SVP_EP_K2);
	SVP_EP_ADJSIN	= SV_SRVPAR_B6;		// T[{p[^B6@@²?dΝ
	DPB_SEND_2B(&SVP_EP_ADJSIN);
	SVP_EP_ADJVAL	= SV_SRVPAR_B7;		// T[{p[^B7@@²?dΝ
	DPB_SEND_2B(&SVP_EP_ADJVAL);
	SVP_ECOM_BASE	= SV_SRVPAR_B8;     // T[{p[^B8@@GR[^ξl
	DPB_SEND_2B(&SVP_ECOM_BASE);
	SVP_ECOM_SCAL	= SV_SRVPAR_B9;     // T[{p[^B9@@GR[^XP[
	DPB_SEND_2B(&SVP_ECOM_SCAL);
	SVP_MOTRPM_MAXP	= SV_MOTRPM_MAXP;	// T[{p[^BA.[^Εερ]
	DPB_SEND_2B(&SVP_MOTRPM_MAXP);
	SVP_ACCLAT_TIMP	= SV_ACCLAT__TIMP;	// T[{p[^BB.ΑΈ¬Τ
	DPB_SEND_2B(&SVP_ACCLAT_TIMP);

//V06d
	if (SEQ_PAR_113 & cBIT10) {			//{ItZbg		2013/09/27
		SVP_VOLST_L	= SV_SRVPAR_BC+(GMN_PAR020*100);		// T[{p[^BC@@dΝp΅ΜΎ―Δ
		DPB_SEND_4B(&SVP_VOLST_L);
	}
	else if (SEQ_PAR_113 & cBIT11) {	//|ItZbg
		ofs = SV_SRVPAR_BC - (GMN_PAR020*100);
		if (ofs<0) {
			ofs = 0;
		}
		SVP_VOLST_L	= ofs;									// T[{p[^BC@@dΝp΅ΜΎ―Δ
		DPB_SEND_4B(&SVP_VOLST_L);
	}
	else {
		SVP_VOLST_L	= SV_SRVPAR_BC;							// T[{p[^BC@@dΝp΅ΜΎ―Δ
		DPB_SEND_4B(&SVP_VOLST_L);
	}

	SVP_SLIDE_S		= SV_SRVPAR_BD;		// T[{p[^BD@@dΝpΕεl
	DPB_SEND_4B(&SVP_SLIDE_S);
	SVP_RAD			= SV_SRVPAR_BE;		// T[{p[^BE@@dΝpΔΩΈl
	DPB_SEND_4B(&SVP_RAD);
	SVP_ORGREV_AGL	= SV_SRVPAR_BF;		// T[{p[^BF@@ΔΩΈ€xκΤ
	DPB_SEND_4B(&SVP_ORGREV_AGL);
	SVP_ORGFWD_AGL	= SV_SRVPAR_BG;		// T[{p[^BG@@²?WA
	DPB_SEND_4B(&SVP_ORGFWD_AGL);

//V06f
	SVP_RISE_ZWID	= (U2b)SV_SRVPAR_BH;		// T[{p[^BH@@γΈΔΎήΫ
	DPB_SEND_2B(&SVP_RISE_ZWID);
	SVP_RISE_CMP1	= (U2b)SV_SRVPAR_BI;		// T[{p[^BI@@γΈΔδr1
	DPB_SEND_2B(&SVP_RISE_CMP1);
	SVP_RISE_CMP2	= (U2b)SV_SRVPAR_BJ;		// T[{p[^BJ@@γΈΔδr2
	DPB_SEND_2B(&SVP_RISE_CMP2);
	SVP_RISE_CMP3	= (U2b)SV_SRVPAR_BK;		// T[{p[^BK@@γΈΔδr\υ
	DPB_SEND_2B(&SVP_RISE_CMP3);
	SVP_RISE_DLY1	= (U2b)SV_SRVPAR_BL;		// T[{p[^BL@@Δx1
	DPB_SEND_2B(&SVP_RISE_DLY1);
	SVP_RISE_DLY2	= (U2b)SV_SRVPAR_BM;		// T[{p[^BM@@Δx2
	DPB_SEND_2B(&SVP_RISE_DLY2);

}
/****************************************************************************/
