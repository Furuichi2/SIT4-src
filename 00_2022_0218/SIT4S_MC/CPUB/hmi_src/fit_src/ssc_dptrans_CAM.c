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
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"
#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"

/****************************************************************************/
/*																			*/
/*	f[^]		F	coq`l © eq`l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CAM	(void)
{
	SVP_RCAMON_P000		= SV_RCLSTA11_C17;				/* ΚuΆΡ000 nmHφ	*/
	SVP_RCAMON_D000		= SV_RCLS11_C17 * 10;			/* ΚuΆΡ000 nmpx	*/
	SVP_RCAMOF_P000		= SV_RCLSTP12_C17;				/* ΚuΆΡ000 neHφ	*/
	SVP_RCAMOF_D000		= SV_RCLS12_C17 * 10;			/* ΚuΆΡ000 nepx	*/
	SVP_RCAMON_P001		= SV_RCLSTA21_C17;				/* ΚuΆΡ001 nmHφ	*/
	SVP_RCAMON_D001		= SV_RCLS21_C17 * 10;			/* ΚuΆΡ001 nmpx	*/
	SVP_RCAMOF_P001		= SV_RCLSTP22_C17;				/* ΚuΆΡ001 neHφ	*/
	SVP_RCAMOF_D001		= SV_RCLS22_C17 * 10;			/* ΚuΆΡ001 nepx	*/
	SVP_RCAMON_P002		= SV_RCLSTA31_C17;				/* ΚuΆΡ002 nmHφ	*/
	SVP_RCAMON_D002		= SV_RCLS31_C17 * 10;			/* ΚuΆΡ002 nmpx	*/
	SVP_RCAMOF_P002		= SV_RCLSTP32_C17;				/* ΚuΆΡ002 neHφ	*/
	SVP_RCAMOF_D002		= SV_RCLS32_C17 * 10;			/* ΚuΆΡ002 nepx	*/
	SVP_RCAMON_P003		= SV_RCLSTA41_C17;				/* ΚuΆΡ003 nmHφ	*/
	SVP_RCAMON_D003		= SV_RCLS41_C17 * 10;			/* ΚuΆΡ003 nmpx	*/
	SVP_RCAMOF_P003		= SV_RCLSTP42_C17;				/* ΚuΆΡ003 neHφ	*/
	SVP_RCAMOF_D003		= SV_RCLS42_C17 * 10;			/* ΚuΆΡ003 nepx	*/
	SVP_RCAMON_P004		= SV_RCLSTA51_C18;				/* ΚuΆΡ004 nmHφ	*/
	SVP_RCAMON_D004		= SV_RCLS51_C18 * 10;			/* ΚuΆΡ004 nmpx	*/
	SVP_RCAMOF_P004		= SV_RCLSTP52_C18;				/* ΚuΆΡ004 neHφ	*/
	SVP_RCAMOF_D004		= SV_RCLS52_C18 * 10;			/* ΚuΆΡ004 nepx	*/
	SVP_RCAMON_P005		= SV_RCLSTA61_C18;				/* ΚuΆΡ005 nmHφ	*/
	SVP_RCAMON_D005		= SV_RCLS61_C18 * 10;			/* ΚuΆΡ005 nmpx	*/
	SVP_RCAMOF_P005		= SV_RCLSTP62_C18;				/* ΚuΆΡ005 neHφ	*/
	SVP_RCAMOF_D005		= SV_RCLS62_C18 * 10;			/* ΚuΆΡ005 nepx	*/
	SVP_RCAMON_P006		= SV_RCLSTA71_C18;				/* ΚuΆΡ006 nmHφ	*/
	SVP_RCAMON_D006		= SV_RCLS71_C18 * 10;			/* ΚuΆΡ006 nmpx	*/
	SVP_RCAMOF_P006		= SV_RCLSTP72_C18;				/* ΚuΆΡ006 neHφ	*/
	SVP_RCAMOF_D006		= SV_RCLS72_C18 * 10;			/* ΚuΆΡ006 nepx	*/
	SVP_RCAMON_P007		= SV_RCLSTA81_C18;				/* ΚuΆΡ007 nmHφ	*/
	SVP_RCAMON_D007		= SV_RCLS81_C18 * 10;			/* ΚuΆΡ007 nmpx	*/
	SVP_RCAMOF_P007		= SV_RCLSTP82_C18;				/* ΚuΆΡ007 neHφ	*/
	SVP_RCAMOF_D007		= SV_RCLS82_C18 * 10;			/* ΚuΆΡ007 nepx	*/
	SVP_RCAMON_P008		= SV_RCLSTA11_C19;				/* ΚuΆΡ008 nmHφ	*/
	SVP_RCAMON_D008		= SV_RCLS11_C19 * 10;			/* ΚuΆΡ008 nmpx	*/
	SVP_RCAMOF_P008		= SV_RCLSTP12_C19;				/* ΚuΆΡ008 neHφ	*/
	SVP_RCAMOF_D008		= SV_RCLS12_C19 * 10;			/* ΚuΆΡ008 nepx	*/
	SVP_RCAMON_P009		= SV_RCLSTA21_C19;				/* ΚuΆΡ009 nmHφ	*/
	SVP_RCAMON_D009		= SV_RCLS21_C19 * 10;			/* ΚuΆΡ009 nmpx	*/
	SVP_RCAMOF_P009		= SV_RCLSTA22_C19;				/* ΚuΆΡ009 neHφ	*/
	SVP_RCAMOF_D009		= SV_RCLS22_C19 * 10;			/* ΚuΆΡ009 nepx	*/
	SVP_RCAMON_P00A		= SV_RCLSTA31_C19;				/* ΚuΆΡ00A nmHφ	*/
	SVP_RCAMON_D00A		= SV_RCLS31_C19 * 10;			/* ΚuΆΡ00A nmpx	*/
	SVP_RCAMOF_P00A		= SV_RCLSTA32_C19;				/* ΚuΆΡ00A neHφ	*/
	SVP_RCAMOF_D00A		= SV_RCLS32_C19 * 10;			/* ΚuΆΡ00A nepx	*/
	SVP_RCAMON_P00B		= SV_RCLSTA41_C19;				/* ΚuΆΡ00B nmHφ	*/
	SVP_RCAMON_D00B		= SV_RCLS41_C19 * 10;			/* ΚuΆΡ00B nmpx	*/
	SVP_RCAMOF_P00B		= SV_RCLSTA42_C19;				/* ΚuΆΡ00B neHφ	*/
	SVP_RCAMOF_D00B		= SV_RCLS42_C19 * 10;			/* ΚuΆΡ00B nepx	*/
	SVP_RCAMON_P00C		= SV_RCLSTA51_C19;				/* ΚuΆΡ00C nmHφ	*/
	SVP_RCAMON_D00C		= SV_RCLS51_C20 * 10;			/* ΚuΆΡ00C nmpx	*/
	SVP_RCAMOF_P00C		= SV_RCLSTA52_C20;				/* ΚuΆΡ00C neHφ	*/
	SVP_RCAMOF_D00C		= SV_RCLS52_C20 * 10;			/* ΚuΆΡ00C nepx	*/
	SVP_RCAMON_P00D		= SV_RCLSTA61_C20;				/* ΚuΆΡ00D nmHφ	*/
	SVP_RCAMON_D00D		= SV_RCLS61_C20 * 10;			/* ΚuΆΡ00D nmpx	*/
	SVP_RCAMOF_P00D		= SV_RCLSTA62_C20;				/* ΚuΆΡ00D neHφ	*/
	SVP_RCAMOF_D00D		= SV_RCLS62_C20 * 10;			/* ΚuΆΡ00D nepx	*/
	SVP_RCAMON_P00E		= SV_RCLSTA71_C20;				/* ΚuΆΡ00E nmHφ	*/
	SVP_RCAMON_D00E		= SV_RCLS71_C20 * 10;			/* ΚuΆΡ00E nmpx	*/
	SVP_RCAMOF_P00E		= SV_RCLSTA72_C20;				/* ΚuΆΡ00E neHφ	*/
	SVP_RCAMOF_D00E		= SV_RCLS72_C20 * 10;			/* ΚuΆΡ00E nepx	*/
	SVP_RCAMON_P00F		= SV_RCLSTA81_C20;				/* ΚuΆΡ00F nmHφ	*/
	SVP_RCAMON_D00F		= SV_RCLS81_C20 * 10;			/* ΚuΆΡ00F nmpx	*/
	SVP_RCAMOF_P00F		= SV_RCLSTA82_C20;				/* ΚuΆΡ00F neHφ	*/
	SVP_RCAMOF_D00F		= SV_RCLS82_C20 * 10;			/* ΚuΆΡ00F nepx	*/

	SVP_RCAMON_P010		= SV_MISSTA1_C9;				/* ΚuΆΡ010 ~XtB[hP nmHφ	*/
	SVP_RCAMON_D010		= SV_MISSK1_C9 * 10;			/* ΚuΆΡ010 ~XtB[hP nmpx	*/
	SVP_RCAMOF_P010		= SV_MISSTP1_C9;				/* ΚuΆΡ010 ~XtB[hP neeHφ	*/
	SVP_RCAMOF_D010		= SV_MISSK2_C9 * 10;			/* ΚuΆΡ010 ~XtB[hP neepx	*/
	SVP_RCAMON_P011		= SV_MISSTA2_C9;				/* ΚuΆΡ011 ~XtB[hQ nmHφ	*/
	SVP_RCAMON_D011		= SV_MISSK3_C9 * 10;			/* ΚuΆΡ011 ~XtB[hQ nmpx	*/
	SVP_RCAMOF_P011		= SV_MISSTP2_C9;				/* ΚuΆΡ011 ~XtB[hQ neeHφ	*/
	SVP_RCAMOF_D011		= SV_MISSK4_C9 * 10;			/* ΚuΆΡ011 ~XtB[hQ neepx	*/
	SVP_RCAMON_P012		= SV_MISSTA3_C9;				/* ΚuΆΡ012 ~XtB[hR nmHφ	*/
	SVP_RCAMON_D012		= SV_MISSK5_C9 * 10;			/* ΚuΆΡ012 ~XtB[hR nmpx	*/
	SVP_RCAMOF_P012		= SV_MISSTP3_C9;				/* ΚuΆΡ012 ~XtB[hR neeHφ	*/
	SVP_RCAMOF_D012		= SV_MISSK6_C9 * 10;			/* ΚuΆΡ012 ~XtB[hR neepx	*/
	SVP_RCAMON_P013		= SV_MISSTA4_C9;				/* ΚuΆΡ013 ~XtB[hS nmHφ	*/
	SVP_RCAMON_D013		= SV_MISSK7_C9 * 10;			/* ΚuΆΡ013 ~XtB[hS nmpx	*/
	SVP_RCAMOF_P013		= SV_MISSTP4_C9;				/* ΚuΆΡ013 ~XtB[hS neeHφ	*/
	SVP_RCAMOF_D013		= SV_MISSK8_C9 * 10;			/* ΚuΆΡ013 ~XtB[hS neepx	*/
	SVP_RCAMON_P014		= SV_MISSTA5_C10;				/* ΚuΆΡ014 ~XtB[hT nmHφ	*/
	SVP_RCAMON_D014		= SV_MISSK1_C10 * 10;			/* ΚuΆΡ014 ~XtB[hT nmpx	*/
	SVP_RCAMOF_P014		= SV_MISSTP5_C10;				/* ΚuΆΡ014 ~XtB[hT neeHφ	*/
	SVP_RCAMOF_D014		= SV_MISSK2_C10 * 10;			/* ΚuΆΡ014 ~XtB[hT neepx	*/
	SVP_RCAMON_P015		= SV_MISSTA6_C10;				/* ΚuΆΡ015 ~XtB[hU nmHφ	*/
	SVP_RCAMON_D015		= SV_MISSK3_C10 * 10;			/* ΚuΆΡ015 ~XtB[hU nmpx	*/
	SVP_RCAMOF_P015		= SV_MISSTP6_C10;				/* ΚuΆΡ015 ~XtB[hU neeHφ	*/
	SVP_RCAMOF_D015		= SV_MISSK4_C10 * 10;			/* ΚuΆΡ015 ~XtB[hU neepx	*/
	SVP_RCAMON_P016		= SV_MISSTA7_C10;				/* ΚuΆΡ016 ~XtB[hV nmHφ	*/
	SVP_RCAMON_D016		= SV_MISSK5_C10 * 10;			/* ΚuΆΡ016 ~XtB[hV nmpx	*/
	SVP_RCAMOF_P016		= SV_MISSTP7_C10;				/* ΚuΆΡ016 ~XtB[hV neeHφ	*/
	SVP_RCAMOF_D016		= SV_MISSK6_C10 * 10;			/* ΚuΆΡ016 ~XtB[hV neepx	*/
	SVP_RCAMON_P017		= SV_MISSTA8_C10;				/* ΚuΆΡ017 ~XtB[hW nmHφ	*/
	SVP_RCAMON_D017		= SV_MISSK7_C10 * 10;			/* ΚuΆΡ017 ~XtB[hW nmpx	*/
	SVP_RCAMOF_P017		= SV_MISSTP8_C10;				/* ΚuΆΡ017 ~XtB[hW neeHφ	*/
	SVP_RCAMOF_D017		= SV_MISSK8_C10 * 10;			/* ΚuΆΡ017 ~XtB[hW neepx	*/

	SVP_RCAMON_P018		= 0;							/* ΚuΆΡ018 nmHφ	*/
	SVP_RCAMON_D018		= SV_RCLSA1_A17 * 10;			/* ΚuΆΡ018 nmpx	VXeJ`@nmpx	*/
	SVP_RCAMOF_P018		= 0;							/* ΚuΆΡ018 neHφ	*/
	SVP_RCAMOF_D018		= SV_RCLSA2_A17 * 10;			/* ΚuΆΡ018 nepx	VXeJ`@neepx	*/
	SVP_RCAMON_P019		= 0;							/* ΚuΆΡ019 nmHφ	*/
	SVP_RCAMON_D019		= SV_RCLSB1_A17 * 10;			/* ΚuΆΡ019 nmpx	VXeJa@nmpx	*/
	SVP_RCAMOF_P019		= 0;							/* ΚuΆΡ019 neHφ	*/
	SVP_RCAMOF_D019		= SV_RCLSB2_A17 * 10;			/* ΚuΆΡ019 nepx	VXeJa@neepx	*/
	SVP_RCAMON_P01A		= 0;							/* ΚuΆΡ01A nmHφ	*/
	SVP_RCAMON_D01A		= SV_RCLSC1_A17 * 10;			/* ΚuΆΡ01A nmpx	VXeJb@nmpx	*/
	SVP_RCAMOF_P01A		= 0;							/* ΚuΆΡ01A neHφ	*/
	SVP_RCAMOF_D01A		= SV_RCLSC2_A17 * 10;			/* ΚuΆΡ01A nepx	VXeJb@neepx	*/
	SVP_RCAMON_P01B		= 0;							/* ΚuΆΡ01B nmHφ	*/
	SVP_RCAMON_D01B		= SV_RCLSD1_A17 * 10;			/* ΚuΆΡ01B nmpx	VXeJc@nmpx	*/
	SVP_RCAMOF_P01B		= 0;							/* ΚuΆΡ01B neHφ	*/
	SVP_RCAMOF_D01B		= SV_RCLSD2_A17 * 10;			/* ΚuΆΡ01B nepx	VXeJc@neepx	*/
	SVP_RCAMON_P01C		= 0;							/* ΚuΆΡ01C nmHφ	*/
	SVP_RCAMON_D01C		= SV_RCLSE1_A17 * 10;			/* ΚuΆΡ01C nmpx	VXeJd@nmpx	*/
	SVP_RCAMOF_P01C		= 0;							/* ΚuΆΡ01C neHφ	*/
	SVP_RCAMOF_D01C		= SV_RCLSE2_A17 * 10;			/* ΚuΆΡ01C nepx	VXeJd@neepx	*/
	SVP_RCAMON_P01D		= 0;							/* ΚuΆΡ01D nmHφ	*/
	SVP_RCAMON_D01D		= SV_RCLSF1_A18 * 10;			/* ΚuΆΡ01D nmpx	VXeJe@nmpx	*/
	SVP_RCAMOF_P01D		= 0;							/* ΚuΆΡ01D neHφ	*/
	SVP_RCAMOF_D01D		= SV_RCLSF2_A18 * 10;			/* ΚuΆΡ01D nepx	VXeJe@neepx	*/
	SVP_RCAMON_P01E		= 0;							/* ΚuΆΡ01E nmHφ	*/
	SVP_RCAMON_D01E		= SV_RCLSG1_A18 * 10;			/* ΚuΆΡ01E nmpx	VXeJf@nmpx	*/
	SVP_RCAMOF_P01E		= 0;							/* ΚuΆΡ01E neHφ	*/
	SVP_RCAMOF_D01E		= SV_RCLSG2_A18 * 10;			/* ΚuΆΡ01E nepx	VXeJf@neepx	*/
	SVP_RCAMON_P01F		= 0;							/* ΚuΆΡ01F nmHφ	*/
	SVP_RCAMON_D01F		= SV_RCLSH1_A18 * 10;			/* ΚuΆΡ01F nmpx	VXeJg@nmpx	*/
	SVP_RCAMOF_P01F		= 0;							/* ΚuΆΡ01F neHφ	*/
	SVP_RCAMOF_D01F		= SV_RCLSH2_A18 * 10;			/* ΚuΆΡ01F nepx	VXeJg@neepx	*/

	SVP_RCAMON_P020		= SV_EJESAT1_C4;				/* ΚuΆΡ020 GWFN^P nmHφ   Jdl */
	SVP_RCAMON_D020		= SV_EJEKK1_C4 * 10;			/* ΚuΆΡ020 GWFN^P nmpx   Jdl */
	SVP_RCAMOF_P020		= SV_EJESTP1_C4;				/* ΚuΆΡ020 GWFN^P neeHφ Jdl */
	SVP_RCAMOF_D020		= SV_EJEKK2_C4 * 10;			/* ΚuΆΡ020 GWFN^P neepx Jdl */
	SVP_RCAMON_P021		= SV_EJESAT1_C4A;				/* ΚuΆΡ021 GWFN^Q nmHφ   Jdl */
	SVP_RCAMON_D021		= SV_EJEKK1_C4A * 10;			/* ΚuΆΡ021 GWN^Q nmpx   Jdl */
	SVP_RCAMOF_P021		= SV_EJESTP1_C4A;				/* ΚuΆΡ021 GWFN^Q neeHφ Jdl */
	SVP_RCAMOF_D021		= SV_EJEKK2_C4A * 10;			/* ΚuΆΡ021 GWFN^Q neepx Jdl */
	SVP_RCAMON_P022		= SV_EJESAT1_C4B;				/* ΚuΆΡ022 GWFN^R nmHφ   Jdl */
	SVP_RCAMON_D022		= SV_EJEKK1_C4B * 10;			/* ΚuΆΡ022 GWN^R nmpx   Jdl */
	SVP_RCAMOF_P022		= SV_EJESTP1_C4B;				/* ΚuΆΡ022 GWFN^R neeHφ Jdl */
	SVP_RCAMOF_D022		= SV_EJEKK2_C4B * 10;			/* ΚuΆΡ022 GWFN^R neepx Jdl */
	SVP_RCAMON_P023		= SV_AUTSTA_C41;				/* ΚuΆΡ023 ©?»P nmHφ	 Jdl */
	SVP_RCAMON_D023		= SV_AUTKK1_C41 * 10;			/* ΚuΆΡ023 ©?»P nmpx	 Jdl */
	SVP_RCAMOF_P023		= SV_AUTSTP_C41;				/* ΚuΆΡ023 ©?»P neeHφ Jdl */
	SVP_RCAMOF_D023		= SV_AUTKK2_C41 * 10;			/* ΚuΆΡ023 ©?»P neepx Jdl */
	SVP_RCAMON_P024		= SV_AUTSTA_C41A;				/* ΚuΆΡ024 ©?»Q nmHφ	 Jdl */
	SVP_RCAMON_D024		= SV_AUTKK1_C41A * 10;			/* ΚuΆΡ024 ©?»Q nmpx	 Jdl */
	SVP_RCAMOF_P024		= SV_AUTSTP_C41A;				/* ΚuΆΡ024 ©?»Q neeHφ Jdl */
	SVP_RCAMOF_D024		= SV_AUTKK2_C41A * 10;			/* ΚuΆΡ024 ©?»Q neepx Jdl */
	SVP_RCAMON_P025		= SV_AUTSTA_C41B;				/* ΚuΆΡ025 ©?»R nmHφ	 Jdl */
	SVP_RCAMON_D025		= SV_AUTKK1_C41B * 10;			/* ΚuΆΡ025 ©?»R nmpx	 Jdl */
	SVP_RCAMOF_P025		= SV_AUTSTP_C41B;				/* ΚuΆΡ025 ©?»R neeHφ Jdl */
	SVP_RCAMOF_D025		= SV_AUTKK2_C41B * 10;			/* ΚuΆΡ025 ©?»R neepx Jdl */
	SVP_RCAMON_P026		= 0;							/* ΚuΆΡ026 nmHφ	*/
	SVP_RCAMON_D026		= 0;							/* ΚuΆΡ026 nmpx	*/
	SVP_RCAMOF_P026		= 0;							/* ΚuΆΡ026 neHφ	*/
	SVP_RCAMOF_D026		= 0;							/* ΚuΆΡ026 nepx	*/
	SVP_RCAMON_P027		= 0;							/* ΚuΆΡ027 nmHφ	*/
	SVP_RCAMON_D027		= 0;							/* ΚuΆΡ027 nmpx	*/
	SVP_RCAMOF_P027		= 0;							/* ΚuΆΡ027 neHφ	*/
	SVP_RCAMOF_D027		= 0;							/* ΚuΆΡ027 nepx	*/
	SVP_RCAMON_P028		= 0;							/* ΚuΆΡ028 nmHφ	*/
	SVP_RCAMON_D028		= 0;							/* ΚuΆΡ028 nmpx	*/
	SVP_RCAMOF_P028		= 0;							/* ΚuΆΡ028 neHφ	*/
	SVP_RCAMOF_D028		= 0;							/* ΚuΆΡ028 nepx	*/
	SVP_RCAMON_P029		= 0;							/* ΚuΆΡ029 nmHφ	*/
	SVP_RCAMON_D029		= 0;							/* ΚuΆΡ029 nmpx	*/
	SVP_RCAMOF_P029		= 0;							/* ΚuΆΡ029 neHφ	*/
	SVP_RCAMOF_D029		= 0;							/* ΚuΆΡ029 nepx	*/
	SVP_RCAMON_P02A		= 0;							/* ΚuΆΡ02A nmHφ	*/
	SVP_RCAMON_D02A		= 0;							/* ΚuΆΡ02A nmpx	*/
	SVP_RCAMOF_P02A		= 0;							/* ΚuΆΡ02A neHφ	*/
	SVP_RCAMOF_D02A		= 0;							/* ΚuΆΡ02A nepx	*/
	SVP_RCAMON_P02B		= 0;							/* ΚuΆΡ02B nmHφ	*/
	SVP_RCAMON_D02B		= 0;							/* ΚuΆΡ02B nmpx	*/
	SVP_RCAMOF_P02B		= 0;							/* ΚuΆΡ02B neHφ	*/
	SVP_RCAMOF_D02B		= 0;							/* ΚuΆΡ02B nepx	*/
	SVP_RCAMON_P02C		= 0;							/* ΚuΆΡ02C nmHφ	*/
	SVP_RCAMON_D02C		= 0;							/* ΚuΆΡ02C nmpx	*/
	SVP_RCAMOF_P02C		= 0;							/* ΚuΆΡ02C neHφ	*/
	SVP_RCAMOF_D02C		= 0;							/* ΚuΆΡ02C nepx	*/
	SVP_RCAMON_P02D		= 0;							/* ΚuΆΡ02D nmHφ	*/
	SVP_RCAMON_D02D		= 0;							/* ΚuΆΡ02D nmpx	*/
	SVP_RCAMOF_P02D		= 0;							/* ΚuΆΡ02D neHφ	*/
	SVP_RCAMOF_D02D		= 0;							/* ΚuΆΡ02D nepx	*/
	SVP_RCAMON_P02E		= 0;							/* ΚuΆΡ02E nmHφ	*/
	SVP_RCAMON_D02E		= 0;							/* ΚuΆΡ02E nmpx	*/
	SVP_RCAMOF_P02E		= 0;							/* ΚuΆΡ02E neHφ	*/
	SVP_RCAMOF_D02E		= 0;							/* ΚuΆΡ02E nepx	*/
	SVP_RCAMON_P02F		= 0;							/* ΚuΆΡ02F nmHφ	*/
	SVP_RCAMON_D02F		= 0;							/* ΚuΆΡ02F nmpx	*/
	SVP_RCAMOF_P02F		= 0;							/* ΚuΆΡ02F neHφ	*/
	SVP_RCAMOF_D02F		= 0;							/* ΚuΆΡ02F nepx	*/

	SVP_RCAMON_P100		= SV_EJESTA_C5;					/* ^C}ΆΡ000 nmHφ	*/
	SVP_RCAMON_D100		= SV_EJEKK3_C5 * 10;			/* ^C}ΆΡ000 nmpx	*/
	SVP_RCAMOF_P100		= SV_EJESTP_C5;					/* ^C}ΆΡ000 neHφ	*/
	SVP_RCAMOF_D100		= SV_EJETIM_C5 * 10;			/* ^C}ΆΡ000 neΤ	*/
	SVP_RCAMON_P101		= SV_EJESTA_C5A;				/* ^C}ΆΡ001 nmHφ	*/
	SVP_RCAMON_D101		= SV_EJEKK3_C5A * 10;			/* ^C}ΆΡ001 nmpx	*/
	SVP_RCAMOF_P101		= SV_EJESTP_C5A;				/* ^C}ΆΡ001 neHφ	*/
	SVP_RCAMOF_D101		= SV_EJETIM_C5A * 10;			/* ^C}ΆΡ001 neΤ	*/
	SVP_RCAMON_P102		= SV_EJESTA_C5B;				/* ^C}ΆΡ002 nmHφ	*/
	SVP_RCAMON_D102		= SV_EJEKK3_C5B * 10;			/* ^C}ΆΡ002 nmpx	*/
	SVP_RCAMOF_P102		= SV_EJESTP_C5B;				/* ^C}ΆΡ002 neHφ	*/
	SVP_RCAMOF_D102		= SV_EJETIM_C5B * 10;			/* ^C}ΆΡ002 neΤ	*/
	SVP_RCAMON_P103		= SV_AUTSTA_C51;				/* ^C}ΆΡ003 nmHφ	*/
	SVP_RCAMON_D103		= SV_AUTKK3_C51 * 10;			/* ^C}ΆΡ003 nmpx	*/
	SVP_RCAMOF_P103		= SV_AUTSTP_C51;				/* ^C}ΆΡ003 neHφ	*/
	SVP_RCAMOF_D103		= SV_AUTTIM_C51 * 10;			/* ^C}ΆΡ003 neΤ	*/
	SVP_RCAMON_P104		= SV_AUTSTA_C51A;				/* ^C}ΆΡ004 nmHφ	*/
	SVP_RCAMON_D104		= SV_AUTKK3_C51A * 10;			/* ^C}ΆΡ004 nmpx	*/
	SVP_RCAMOF_P104		= SV_AUTSTP_C51A;				/* ^C}ΆΡ004 neHφ	*/
	SVP_RCAMOF_D104		= SV_AUTTIM_C51A * 10;			/* ^C}ΆΡ004 neΤ	*/
	SVP_RCAMON_P105		= SV_AUTSTA_C51B;				/* ^C}ΆΡ005 nmHφ	*/
	SVP_RCAMON_D105		= SV_AUTKK3_C51B * 10;			/* ^C}ΆΡ005 nmpx	*/
	SVP_RCAMOF_P105		= SV_AUTSTP_C51B;				/* ^C}ΆΡ005 neHφ	*/
	SVP_RCAMOF_D105		= SV_AUTTIM_C51B * 10;			/* ^C}ΆΡ005 neΤ	*/
	SVP_RCAMON_P106		= 0;							/* ^C}ΆΡ006 nmHφ	*/
	SVP_RCAMON_D106		= 0;							/* ^C}ΆΡ006 nmpx	*/
	SVP_RCAMOF_P106		= 0;							/* ^C}ΆΡ006 neHφ	*/
	SVP_RCAMOF_D106		= 0;							/* ^C}ΆΡ006 neΤ	*/
	SVP_RCAMON_P107		= 0;							/* ^C}ΆΡ007 nmHφ	*/
	SVP_RCAMON_D107		= 0;							/* ^C}ΆΡ007 nmpx	*/
	SVP_RCAMOF_P107		= 0;							/* ^C}ΆΡ007 neHφ	*/
	SVP_RCAMOF_D107		= 0;							/* ^C}ΆΡ007 neΤ	*/
	SVP_RCAMON_P108		= 0;							/* ^C}ΆΡ008 nmHφ	*/
	SVP_RCAMON_D108		= 0;							/* ^C}ΆΡ008 nmpx	*/
	SVP_RCAMOF_P108		= 0;							/* ^C}ΆΡ008 neHφ	*/
	SVP_RCAMOF_D108		= 0;							/* ^C}ΆΡ008 neΤ	*/
	SVP_RCAMON_P109		= 0;							/* ^C}ΆΡ009 nmHφ	*/
	SVP_RCAMON_D109		= 0;							/* ^C}ΆΡ009 nmpx	*/
	SVP_RCAMOF_P109		= 0;							/* ^C}ΆΡ009 neHφ	*/
	SVP_RCAMOF_D109		= 0;							/* ^C}ΆΡ009 neΤ	*/
	SVP_RCAMON_P10A		= 0;							/* ^C}ΆΡ00A nmHφ	*/
	SVP_RCAMON_D10A		= 0;							/* ^C}ΆΡ00A nmpx	*/
	SVP_RCAMOF_P10A		= 0;							/* ^C}ΆΡ00A neHφ	*/
	SVP_RCAMOF_D10A		= 0;							/* ^C}ΆΡ00A neΤ	*/
	SVP_RCAMON_P10B		= 0;							/* ^C}ΆΡ00B nmHφ	*/
	SVP_RCAMON_D10B		= 0;							/* ^C}ΆΡ00B nmpx	*/
	SVP_RCAMOF_P10B		= 0;							/* ^C}ΆΡ00B neHφ	*/
	SVP_RCAMOF_D10B		= 0;							/* ^C}ΆΡ00B neΤ	*/
	SVP_RCAMON_P10C		= 0;							/* ^C}ΆΡ00C nmHφ	*/
	SVP_RCAMON_D10C		= 0;							/* ^C}ΆΡ00C nmpx	*/
	SVP_RCAMOF_P10C		= 0;							/* ^C}ΆΡ00C neHφ	*/
	SVP_RCAMOF_D10C		= 0;							/* ^C}ΆΡ00C neΤ	*/
	SVP_RCAMON_P10D		= 0;							/* ^C}ΆΡ00D nmHφ	*/
	SVP_RCAMON_D10D		= 0;							/* ^C}ΆΡ00D nmpx	*/
	SVP_RCAMOF_P10D		= 0;							/* ^C}ΆΡ00D neHφ	*/
	SVP_RCAMOF_D10D		= 0;							/* ^C}ΆΡ00D neΤ	*/
	SVP_RCAMON_P10E		= 0;							/* ^C}ΆΡ00E nmHφ	*/
	SVP_RCAMON_D10E		= 0;							/* ^C}ΆΡ00E nmpx	*/
	SVP_RCAMOF_P10E		= 0;							/* ^C}ΆΡ00E neHφ	*/
	SVP_RCAMOF_D10E		= 0;							/* ^C}ΆΡ00E neΤ	*/
	SVP_RCAMON_P10F		= 0;							/* ^C}ΆΡ00F nmHφ	*/
	SVP_RCAMON_D10F		= 0;							/* ^C}ΆΡ00F nmpx	*/
	SVP_RCAMOF_P10F		= 0;							/* ^C}ΆΡ00F neHφ	*/
	SVP_RCAMOF_D10F		= 0;							/* ^C}ΆΡ00F neΤ	*/

//2002-08-28:ΗΑ
	SVP_CAMFUN_SEL00	= SV_CAMNA0_C1;					//[^JPΔpIπνΚ
	SVP_CAMFUN_SEL01	= SV_CAMNA1_C1;					//[^JQΔpIπνΚ
	SVP_CAMFUN_SEL02	= SV_CAMNA2_C1;					//[^JRΔpIπνΚ
	SVP_CAMFUN_SEL03	= SV_CAMNA3_C1;					//[^JSΔpIπνΚ
	SVP_CAMFUN_SEL04	= SV_CAMNA4_C1;					//[^JTΔpIπνΚ
	SVP_CAMFUN_SEL05	= SV_CAMNA5_C1;					//[^JUΔpIπνΚ
	SVP_CAMFUN_SEL06	= SV_CAMNA6_C1;					//[^JVΔpIπνΚ
	SVP_CAMFUN_SEL07	= SV_CAMNA7_C1;					//[^JWΔpIπνΚ
	SVP_CAMFUN_SEL08	= SV_CAMNA8_C1;					//[^JXΔpIπνΚ
	SVP_CAMFUN_SEL09	= SV_CAMNA9_C1;					//[^JPOΔpIπνΚ
	SVP_CAMFUN_SEL0A	= SV_CAMNAA_C1;					//[^JPPΔpIπνΚ
	SVP_CAMFUN_SEL0B	= SV_CAMNAB_C1;					//[^JPQΔpIπνΚ
	SVP_CAMFUN_SEL0C	= SV_CAMNAC_C1;					//[^JPRΔpIπνΚ
	SVP_CAMFUN_SEL0D	= SV_CAMNAD_C1;					//[^JPSΔpIπνΚ
	SVP_CAMFUN_SEL0E	= SV_CAMNAE_C1;					//[^JPTΔpIπνΚ
	SVP_CAMFUN_SEL0F	= SV_CAMNAF_C1;					//[^JPUΔpIπνΚ

}
/****************************************************************************/
