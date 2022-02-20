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
#include	"dp_cpuab.h"

/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CAM	(void)
{
	SVP_RCAMON_P000		= SV_RCLSTA11_C17;				/* 位置ｶﾑ000 ＯＮ工程	*/
	SVP_RCAMON_D000		= SV_RCLS11_C17 * 10;			/* 位置ｶﾑ000 ＯＮ角度	*/
	SVP_RCAMOF_P000		= SV_RCLSTP12_C17;				/* 位置ｶﾑ000 ＯＦ工程	*/
	SVP_RCAMOF_D000		= SV_RCLS12_C17 * 10;			/* 位置ｶﾑ000 ＯＦ角度	*/
	SVP_RCAMON_P001		= SV_RCLSTA21_C17;				/* 位置ｶﾑ001 ＯＮ工程	*/
	SVP_RCAMON_D001		= SV_RCLS21_C17 * 10;			/* 位置ｶﾑ001 ＯＮ角度	*/
	SVP_RCAMOF_P001		= SV_RCLSTP22_C17;				/* 位置ｶﾑ001 ＯＦ工程	*/
	SVP_RCAMOF_D001		= SV_RCLS22_C17 * 10;			/* 位置ｶﾑ001 ＯＦ角度	*/
	SVP_RCAMON_P002		= SV_RCLSTA31_C17;				/* 位置ｶﾑ002 ＯＮ工程	*/
	SVP_RCAMON_D002		= SV_RCLS31_C17 * 10;			/* 位置ｶﾑ002 ＯＮ角度	*/
	SVP_RCAMOF_P002		= SV_RCLSTP32_C17;				/* 位置ｶﾑ002 ＯＦ工程	*/
	SVP_RCAMOF_D002		= SV_RCLS32_C17 * 10;			/* 位置ｶﾑ002 ＯＦ角度	*/
	SVP_RCAMON_P003		= SV_RCLSTA41_C17;				/* 位置ｶﾑ003 ＯＮ工程	*/
	SVP_RCAMON_D003		= SV_RCLS41_C17 * 10;			/* 位置ｶﾑ003 ＯＮ角度	*/
	SVP_RCAMOF_P003		= SV_RCLSTP42_C17;				/* 位置ｶﾑ003 ＯＦ工程	*/
	SVP_RCAMOF_D003		= SV_RCLS42_C17 * 10;			/* 位置ｶﾑ003 ＯＦ角度	*/
	SVP_RCAMON_P004		= SV_RCLSTA51_C18;				/* 位置ｶﾑ004 ＯＮ工程	*/
	SVP_RCAMON_D004		= SV_RCLS51_C18 * 10;			/* 位置ｶﾑ004 ＯＮ角度	*/
	SVP_RCAMOF_P004		= SV_RCLSTP52_C18;				/* 位置ｶﾑ004 ＯＦ工程	*/
	SVP_RCAMOF_D004		= SV_RCLS52_C18 * 10;			/* 位置ｶﾑ004 ＯＦ角度	*/
	SVP_RCAMON_P005		= SV_RCLSTA61_C18;				/* 位置ｶﾑ005 ＯＮ工程	*/
	SVP_RCAMON_D005		= SV_RCLS61_C18 * 10;			/* 位置ｶﾑ005 ＯＮ角度	*/
	SVP_RCAMOF_P005		= SV_RCLSTP62_C18;				/* 位置ｶﾑ005 ＯＦ工程	*/
	SVP_RCAMOF_D005		= SV_RCLS62_C18 * 10;			/* 位置ｶﾑ005 ＯＦ角度	*/
	SVP_RCAMON_P006		= SV_RCLSTA71_C18;				/* 位置ｶﾑ006 ＯＮ工程	*/
	SVP_RCAMON_D006		= SV_RCLS71_C18 * 10;			/* 位置ｶﾑ006 ＯＮ角度	*/
	SVP_RCAMOF_P006		= SV_RCLSTP72_C18;				/* 位置ｶﾑ006 ＯＦ工程	*/
	SVP_RCAMOF_D006		= SV_RCLS72_C18 * 10;			/* 位置ｶﾑ006 ＯＦ角度	*/
	SVP_RCAMON_P007		= SV_RCLSTA81_C18;				/* 位置ｶﾑ007 ＯＮ工程	*/
	SVP_RCAMON_D007		= SV_RCLS81_C18 * 10;			/* 位置ｶﾑ007 ＯＮ角度	*/
	SVP_RCAMOF_P007		= SV_RCLSTP82_C18;				/* 位置ｶﾑ007 ＯＦ工程	*/
	SVP_RCAMOF_D007		= SV_RCLS82_C18 * 10;			/* 位置ｶﾑ007 ＯＦ角度	*/
	SVP_RCAMON_P008		= SV_RCLSTA11_C19;				/* 位置ｶﾑ008 ＯＮ工程	*/
	SVP_RCAMON_D008		= SV_RCLS11_C19 * 10;			/* 位置ｶﾑ008 ＯＮ角度	*/
	SVP_RCAMOF_P008		= SV_RCLSTP12_C19;				/* 位置ｶﾑ008 ＯＦ工程	*/
	SVP_RCAMOF_D008		= SV_RCLS12_C19 * 10;			/* 位置ｶﾑ008 ＯＦ角度	*/
	SVP_RCAMON_P009		= SV_RCLSTA21_C19;				/* 位置ｶﾑ009 ＯＮ工程	*/
	SVP_RCAMON_D009		= SV_RCLS21_C19 * 10;			/* 位置ｶﾑ009 ＯＮ角度	*/
	SVP_RCAMOF_P009		= SV_RCLSTA22_C19;				/* 位置ｶﾑ009 ＯＦ工程	*/
	SVP_RCAMOF_D009		= SV_RCLS22_C19 * 10;			/* 位置ｶﾑ009 ＯＦ角度	*/
	SVP_RCAMON_P00A		= SV_RCLSTA31_C19;				/* 位置ｶﾑ00A ＯＮ工程	*/
	SVP_RCAMON_D00A		= SV_RCLS31_C19 * 10;			/* 位置ｶﾑ00A ＯＮ角度	*/
	SVP_RCAMOF_P00A		= SV_RCLSTA32_C19;				/* 位置ｶﾑ00A ＯＦ工程	*/
	SVP_RCAMOF_D00A		= SV_RCLS32_C19 * 10;			/* 位置ｶﾑ00A ＯＦ角度	*/
	SVP_RCAMON_P00B		= SV_RCLSTA41_C19;				/* 位置ｶﾑ00B ＯＮ工程	*/
	SVP_RCAMON_D00B		= SV_RCLS41_C19 * 10;			/* 位置ｶﾑ00B ＯＮ角度	*/
	SVP_RCAMOF_P00B		= SV_RCLSTA42_C19;				/* 位置ｶﾑ00B ＯＦ工程	*/
	SVP_RCAMOF_D00B		= SV_RCLS42_C19 * 10;			/* 位置ｶﾑ00B ＯＦ角度	*/
	SVP_RCAMON_P00C		= SV_RCLSTA51_C19;				/* 位置ｶﾑ00C ＯＮ工程	*/
	SVP_RCAMON_D00C		= SV_RCLS51_C20 * 10;			/* 位置ｶﾑ00C ＯＮ角度	*/
	SVP_RCAMOF_P00C		= SV_RCLSTA52_C20;				/* 位置ｶﾑ00C ＯＦ工程	*/
	SVP_RCAMOF_D00C		= SV_RCLS52_C20 * 10;			/* 位置ｶﾑ00C ＯＦ角度	*/
	SVP_RCAMON_P00D		= SV_RCLSTA61_C20;				/* 位置ｶﾑ00D ＯＮ工程	*/
	SVP_RCAMON_D00D		= SV_RCLS61_C20 * 10;			/* 位置ｶﾑ00D ＯＮ角度	*/
	SVP_RCAMOF_P00D		= SV_RCLSTA62_C20;				/* 位置ｶﾑ00D ＯＦ工程	*/
	SVP_RCAMOF_D00D		= SV_RCLS62_C20 * 10;			/* 位置ｶﾑ00D ＯＦ角度	*/
	SVP_RCAMON_P00E		= SV_RCLSTA71_C20;				/* 位置ｶﾑ00E ＯＮ工程	*/
	SVP_RCAMON_D00E		= SV_RCLS71_C20 * 10;			/* 位置ｶﾑ00E ＯＮ角度	*/
	SVP_RCAMOF_P00E		= SV_RCLSTA72_C20;				/* 位置ｶﾑ00E ＯＦ工程	*/
	SVP_RCAMOF_D00E		= SV_RCLS72_C20 * 10;			/* 位置ｶﾑ00E ＯＦ角度	*/
	SVP_RCAMON_P00F		= SV_RCLSTA81_C20;				/* 位置ｶﾑ00F ＯＮ工程	*/
	SVP_RCAMON_D00F		= SV_RCLS81_C20 * 10;			/* 位置ｶﾑ00F ＯＮ角度	*/
	SVP_RCAMOF_P00F		= SV_RCLSTA82_C20;				/* 位置ｶﾑ00F ＯＦ工程	*/
	SVP_RCAMOF_D00F		= SV_RCLS82_C20 * 10;			/* 位置ｶﾑ00F ＯＦ角度	*/

	SVP_RCAMON_P010		= SV_MISSTA1_C9;				/* 位置ｶﾑ010 ミスフィード１ ＯＮ工程	*/
	SVP_RCAMON_D010		= SV_MISSK1_C9 * 10;			/* 位置ｶﾑ010 ミスフィード１ ＯＮ角度	*/
	SVP_RCAMOF_P010		= SV_MISSTP1_C9;				/* 位置ｶﾑ010 ミスフィード１ ＯＦＦ工程	*/
	SVP_RCAMOF_D010		= SV_MISSK2_C9 * 10;			/* 位置ｶﾑ010 ミスフィード１ ＯＦＦ角度	*/
	SVP_RCAMON_P011		= SV_MISSTA2_C9;				/* 位置ｶﾑ011 ミスフィード２ ＯＮ工程	*/
	SVP_RCAMON_D011		= SV_MISSK3_C9 * 10;			/* 位置ｶﾑ011 ミスフィード２ ＯＮ角度	*/
	SVP_RCAMOF_P011		= SV_MISSTP2_C9;				/* 位置ｶﾑ011 ミスフィード２ ＯＦＦ工程	*/
	SVP_RCAMOF_D011		= SV_MISSK4_C9 * 10;			/* 位置ｶﾑ011 ミスフィード２ ＯＦＦ角度	*/
	SVP_RCAMON_P012		= SV_MISSTA3_C9;				/* 位置ｶﾑ012 ミスフィード３ ＯＮ工程	*/
	SVP_RCAMON_D012		= SV_MISSK5_C9 * 10;			/* 位置ｶﾑ012 ミスフィード３ ＯＮ角度	*/
	SVP_RCAMOF_P012		= SV_MISSTP3_C9;				/* 位置ｶﾑ012 ミスフィード３ ＯＦＦ工程	*/
	SVP_RCAMOF_D012		= SV_MISSK6_C9 * 10;			/* 位置ｶﾑ012 ミスフィード３ ＯＦＦ角度	*/
	SVP_RCAMON_P013		= SV_MISSTA4_C9;				/* 位置ｶﾑ013 ミスフィード４ ＯＮ工程	*/
	SVP_RCAMON_D013		= SV_MISSK7_C9 * 10;			/* 位置ｶﾑ013 ミスフィード４ ＯＮ角度	*/
	SVP_RCAMOF_P013		= SV_MISSTP4_C9;				/* 位置ｶﾑ013 ミスフィード４ ＯＦＦ工程	*/
	SVP_RCAMOF_D013		= SV_MISSK8_C9 * 10;			/* 位置ｶﾑ013 ミスフィード４ ＯＦＦ角度	*/
	SVP_RCAMON_P014		= SV_MISSTA5_C10;				/* 位置ｶﾑ014 ミスフィード５ ＯＮ工程	*/
	SVP_RCAMON_D014		= SV_MISSK1_C10 * 10;			/* 位置ｶﾑ014 ミスフィード５ ＯＮ角度	*/
	SVP_RCAMOF_P014		= SV_MISSTP5_C10;				/* 位置ｶﾑ014 ミスフィード５ ＯＦＦ工程	*/
	SVP_RCAMOF_D014		= SV_MISSK2_C10 * 10;			/* 位置ｶﾑ014 ミスフィード５ ＯＦＦ角度	*/
	SVP_RCAMON_P015		= SV_MISSTA6_C10;				/* 位置ｶﾑ015 ミスフィード６ ＯＮ工程	*/
	SVP_RCAMON_D015		= SV_MISSK3_C10 * 10;			/* 位置ｶﾑ015 ミスフィード６ ＯＮ角度	*/
	SVP_RCAMOF_P015		= SV_MISSTP6_C10;				/* 位置ｶﾑ015 ミスフィード６ ＯＦＦ工程	*/
	SVP_RCAMOF_D015		= SV_MISSK4_C10 * 10;			/* 位置ｶﾑ015 ミスフィード６ ＯＦＦ角度	*/
	SVP_RCAMON_P016		= SV_MISSTA7_C10;				/* 位置ｶﾑ016 ミスフィード７ ＯＮ工程	*/
	SVP_RCAMON_D016		= SV_MISSK5_C10 * 10;			/* 位置ｶﾑ016 ミスフィード７ ＯＮ角度	*/
	SVP_RCAMOF_P016		= SV_MISSTP7_C10;				/* 位置ｶﾑ016 ミスフィード７ ＯＦＦ工程	*/
	SVP_RCAMOF_D016		= SV_MISSK6_C10 * 10;			/* 位置ｶﾑ016 ミスフィード７ ＯＦＦ角度	*/
	SVP_RCAMON_P017		= SV_MISSTA8_C10;				/* 位置ｶﾑ017 ミスフィード８ ＯＮ工程	*/
	SVP_RCAMON_D017		= SV_MISSK7_C10 * 10;			/* 位置ｶﾑ017 ミスフィード８ ＯＮ角度	*/
	SVP_RCAMOF_P017		= SV_MISSTP8_C10;				/* 位置ｶﾑ017 ミスフィード８ ＯＦＦ工程	*/
	SVP_RCAMOF_D017		= SV_MISSK8_C10 * 10;			/* 位置ｶﾑ017 ミスフィード８ ＯＦＦ角度	*/

	SVP_RCAMON_P018		= 0;							/* 位置ｶﾑ018 ＯＮ工程	*/
	SVP_RCAMON_D018		= SV_RCLSA1_A17 * 10;			/* 位置ｶﾑ018 ＯＮ角度	システムカムＡ　ＯＮ角度	*/
	SVP_RCAMOF_P018		= 0;							/* 位置ｶﾑ018 ＯＦ工程	*/
	SVP_RCAMOF_D018		= SV_RCLSA2_A17 * 10;			/* 位置ｶﾑ018 ＯＦ角度	システムカムＡ　ＯＦＦ角度	*/
	SVP_RCAMON_P019		= 0;							/* 位置ｶﾑ019 ＯＮ工程	*/
	SVP_RCAMON_D019		= SV_RCLSB1_A17 * 10;			/* 位置ｶﾑ019 ＯＮ角度	システムカムＢ　ＯＮ角度	*/
	SVP_RCAMOF_P019		= 0;							/* 位置ｶﾑ019 ＯＦ工程	*/
	SVP_RCAMOF_D019		= SV_RCLSB2_A17 * 10;			/* 位置ｶﾑ019 ＯＦ角度	システムカムＢ　ＯＦＦ角度	*/
	SVP_RCAMON_P01A		= 0;							/* 位置ｶﾑ01A ＯＮ工程	*/
	SVP_RCAMON_D01A		= SV_RCLSC1_A17 * 10;			/* 位置ｶﾑ01A ＯＮ角度	システムカムＣ　ＯＮ角度	*/
	SVP_RCAMOF_P01A		= 0;							/* 位置ｶﾑ01A ＯＦ工程	*/
	SVP_RCAMOF_D01A		= SV_RCLSC2_A17 * 10;			/* 位置ｶﾑ01A ＯＦ角度	システムカムＣ　ＯＦＦ角度	*/
	SVP_RCAMON_P01B		= 0;							/* 位置ｶﾑ01B ＯＮ工程	*/
	SVP_RCAMON_D01B		= SV_RCLSD1_A17 * 10;			/* 位置ｶﾑ01B ＯＮ角度	システムカムＤ　ＯＮ角度	*/
	SVP_RCAMOF_P01B		= 0;							/* 位置ｶﾑ01B ＯＦ工程	*/
	SVP_RCAMOF_D01B		= SV_RCLSD2_A17 * 10;			/* 位置ｶﾑ01B ＯＦ角度	システムカムＤ　ＯＦＦ角度	*/
	SVP_RCAMON_P01C		= 0;							/* 位置ｶﾑ01C ＯＮ工程	*/
	SVP_RCAMON_D01C		= SV_RCLSE1_A17 * 10;			/* 位置ｶﾑ01C ＯＮ角度	システムカムＥ　ＯＮ角度	*/
	SVP_RCAMOF_P01C		= 0;							/* 位置ｶﾑ01C ＯＦ工程	*/
	SVP_RCAMOF_D01C		= SV_RCLSE2_A17 * 10;			/* 位置ｶﾑ01C ＯＦ角度	システムカムＥ　ＯＦＦ角度	*/
	SVP_RCAMON_P01D		= 0;							/* 位置ｶﾑ01D ＯＮ工程	*/
	SVP_RCAMON_D01D		= SV_RCLSF1_A18 * 10;			/* 位置ｶﾑ01D ＯＮ角度	システムカムＦ　ＯＮ角度	*/
	SVP_RCAMOF_P01D		= 0;							/* 位置ｶﾑ01D ＯＦ工程	*/
	SVP_RCAMOF_D01D		= SV_RCLSF2_A18 * 10;			/* 位置ｶﾑ01D ＯＦ角度	システムカムＦ　ＯＦＦ角度	*/
	SVP_RCAMON_P01E		= 0;							/* 位置ｶﾑ01E ＯＮ工程	*/
	SVP_RCAMON_D01E		= SV_RCLSG1_A18 * 10;			/* 位置ｶﾑ01E ＯＮ角度	システムカムＧ　ＯＮ角度	*/
	SVP_RCAMOF_P01E		= 0;							/* 位置ｶﾑ01E ＯＦ工程	*/
	SVP_RCAMOF_D01E		= SV_RCLSG2_A18 * 10;			/* 位置ｶﾑ01E ＯＦ角度	システムカムＧ　ＯＦＦ角度	*/
	SVP_RCAMON_P01F		= 0;							/* 位置ｶﾑ01F ＯＮ工程	*/
	SVP_RCAMON_D01F		= SV_RCLSH1_A18 * 10;			/* 位置ｶﾑ01F ＯＮ角度	システムカムＨ　ＯＮ角度	*/
	SVP_RCAMOF_P01F		= 0;							/* 位置ｶﾑ01F ＯＦ工程	*/
	SVP_RCAMOF_D01F		= SV_RCLSH2_A18 * 10;			/* 位置ｶﾑ01F ＯＦ角度	システムカムＨ　ＯＦＦ角度	*/

	SVP_RCAMON_P020		= SV_EJESAT1_C4;				/* 位置ｶﾑ020 エジェクタ１ ＯＮ工程   カム仕様 */
	SVP_RCAMON_D020		= SV_EJEKK1_C4 * 10;			/* 位置ｶﾑ020 エジェクタ１ ＯＮ角度   カム仕様 */
	SVP_RCAMOF_P020		= SV_EJESTP1_C4;				/* 位置ｶﾑ020 エジェクタ１ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D020		= SV_EJEKK2_C4 * 10;			/* 位置ｶﾑ020 エジェクタ１ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P021		= SV_EJESAT1_C4A;				/* 位置ｶﾑ021 エジェクタ２ ＯＮ工程   カム仕様 */
	SVP_RCAMON_D021		= SV_EJEKK1_C4A * 10;			/* 位置ｶﾑ021 エジャクタ２ ＯＮ角度   カム仕様 */
	SVP_RCAMOF_P021		= SV_EJESTP1_C4A;				/* 位置ｶﾑ021 エジェクタ２ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D021		= SV_EJEKK2_C4A * 10;			/* 位置ｶﾑ021 エジェクタ２ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P022		= SV_EJESAT1_C4B;				/* 位置ｶﾑ022 エジェクタ３ ＯＮ工程   カム仕様 */
	SVP_RCAMON_D022		= SV_EJEKK1_C4B * 10;			/* 位置ｶﾑ022 エジャクタ３ ＯＮ角度   カム仕様 */
	SVP_RCAMOF_P022		= SV_EJESTP1_C4B;				/* 位置ｶﾑ022 エジェクタ３ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D022		= SV_EJEKK2_C4B * 10;			/* 位置ｶﾑ022 エジェクタ３ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P023		= SV_AUTSTA_C41;				/* 位置ｶﾑ023 自動化１ ＯＮ工程	 カム仕様 */
	SVP_RCAMON_D023		= SV_AUTKK1_C41 * 10;			/* 位置ｶﾑ023 自動化１ ＯＮ角度	 カム仕様 */
	SVP_RCAMOF_P023		= SV_AUTSTP_C41;				/* 位置ｶﾑ023 自動化１ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D023		= SV_AUTKK2_C41 * 10;			/* 位置ｶﾑ023 自動化１ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P024		= SV_AUTSTA_C41A;				/* 位置ｶﾑ024 自動化２ ＯＮ工程	 カム仕様 */
	SVP_RCAMON_D024		= SV_AUTKK1_C41A * 10;			/* 位置ｶﾑ024 自動化２ ＯＮ角度	 カム仕様 */
	SVP_RCAMOF_P024		= SV_AUTSTP_C41A;				/* 位置ｶﾑ024 自動化２ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D024		= SV_AUTKK2_C41A * 10;			/* 位置ｶﾑ024 自動化２ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P025		= SV_AUTSTA_C41B;				/* 位置ｶﾑ025 自動化３ ＯＮ工程	 カム仕様 */
	SVP_RCAMON_D025		= SV_AUTKK1_C41B * 10;			/* 位置ｶﾑ025 自動化３ ＯＮ角度	 カム仕様 */
	SVP_RCAMOF_P025		= SV_AUTSTP_C41B;				/* 位置ｶﾑ025 自動化３ ＯＦＦ工程 カム仕様 */
	SVP_RCAMOF_D025		= SV_AUTKK2_C41B * 10;			/* 位置ｶﾑ025 自動化３ ＯＦＦ角度 カム仕様 */
	SVP_RCAMON_P026		= 0;							/* 位置ｶﾑ026 ＯＮ工程	*/
	SVP_RCAMON_D026		= 0;							/* 位置ｶﾑ026 ＯＮ角度	*/
	SVP_RCAMOF_P026		= 0;							/* 位置ｶﾑ026 ＯＦ工程	*/
	SVP_RCAMOF_D026		= 0;							/* 位置ｶﾑ026 ＯＦ角度	*/
	SVP_RCAMON_P027		= 0;							/* 位置ｶﾑ027 ＯＮ工程	*/
	SVP_RCAMON_D027		= 0;							/* 位置ｶﾑ027 ＯＮ角度	*/
	SVP_RCAMOF_P027		= 0;							/* 位置ｶﾑ027 ＯＦ工程	*/
	SVP_RCAMOF_D027		= 0;							/* 位置ｶﾑ027 ＯＦ角度	*/
	SVP_RCAMON_P028		= 0;							/* 位置ｶﾑ028 ＯＮ工程	*/
	SVP_RCAMON_D028		= 0;							/* 位置ｶﾑ028 ＯＮ角度	*/
	SVP_RCAMOF_P028		= 0;							/* 位置ｶﾑ028 ＯＦ工程	*/
	SVP_RCAMOF_D028		= 0;							/* 位置ｶﾑ028 ＯＦ角度	*/
	SVP_RCAMON_P029		= 0;							/* 位置ｶﾑ029 ＯＮ工程	*/
	SVP_RCAMON_D029		= 0;							/* 位置ｶﾑ029 ＯＮ角度	*/
	SVP_RCAMOF_P029		= 0;							/* 位置ｶﾑ029 ＯＦ工程	*/
	SVP_RCAMOF_D029		= 0;							/* 位置ｶﾑ029 ＯＦ角度	*/
	SVP_RCAMON_P02A		= 0;							/* 位置ｶﾑ02A ＯＮ工程	*/
	SVP_RCAMON_D02A		= 0;							/* 位置ｶﾑ02A ＯＮ角度	*/
	SVP_RCAMOF_P02A		= 0;							/* 位置ｶﾑ02A ＯＦ工程	*/
	SVP_RCAMOF_D02A		= 0;							/* 位置ｶﾑ02A ＯＦ角度	*/
	SVP_RCAMON_P02B		= 0;							/* 位置ｶﾑ02B ＯＮ工程	*/
	SVP_RCAMON_D02B		= 0;							/* 位置ｶﾑ02B ＯＮ角度	*/
	SVP_RCAMOF_P02B		= 0;							/* 位置ｶﾑ02B ＯＦ工程	*/
	SVP_RCAMOF_D02B		= 0;							/* 位置ｶﾑ02B ＯＦ角度	*/
	SVP_RCAMON_P02C		= 0;							/* 位置ｶﾑ02C ＯＮ工程	*/
	SVP_RCAMON_D02C		= 0;							/* 位置ｶﾑ02C ＯＮ角度	*/
	SVP_RCAMOF_P02C		= 0;							/* 位置ｶﾑ02C ＯＦ工程	*/
	SVP_RCAMOF_D02C		= 0;							/* 位置ｶﾑ02C ＯＦ角度	*/
	SVP_RCAMON_P02D		= 0;							/* 位置ｶﾑ02D ＯＮ工程	*/
	SVP_RCAMON_D02D		= 0;							/* 位置ｶﾑ02D ＯＮ角度	*/
	SVP_RCAMOF_P02D		= 0;							/* 位置ｶﾑ02D ＯＦ工程	*/
	SVP_RCAMOF_D02D		= 0;							/* 位置ｶﾑ02D ＯＦ角度	*/
	SVP_RCAMON_P02E		= 0;							/* 位置ｶﾑ02E ＯＮ工程	*/
	SVP_RCAMON_D02E		= 0;							/* 位置ｶﾑ02E ＯＮ角度	*/
	SVP_RCAMOF_P02E		= 0;							/* 位置ｶﾑ02E ＯＦ工程	*/
	SVP_RCAMOF_D02E		= 0;							/* 位置ｶﾑ02E ＯＦ角度	*/
	SVP_RCAMON_P02F		= 0;							/* 位置ｶﾑ02F ＯＮ工程	*/
	SVP_RCAMON_D02F		= 0;							/* 位置ｶﾑ02F ＯＮ角度	*/
	SVP_RCAMOF_P02F		= 0;							/* 位置ｶﾑ02F ＯＦ工程	*/
	SVP_RCAMOF_D02F		= 0;							/* 位置ｶﾑ02F ＯＦ角度	*/

	SVP_RCAMON_P100		= SV_EJESTA_C5;					/* タイマｶﾑ000 ＯＮ工程	*/
	SVP_RCAMON_D100		= SV_EJEKK3_C5 * 10;			/* タイマｶﾑ000 ＯＮ角度	*/
	SVP_RCAMOF_P100		= SV_EJESTP_C5;					/* タイマｶﾑ000 ＯＦ工程	*/
	SVP_RCAMOF_D100		= SV_EJETIM_C5 * 10;			/* タイマｶﾑ000 ＯＦ時間	*/
	SVP_RCAMON_P101		= SV_EJESTA_C5A;				/* タイマｶﾑ001 ＯＮ工程	*/
	SVP_RCAMON_D101		= SV_EJEKK3_C5A * 10;			/* タイマｶﾑ001 ＯＮ角度	*/
	SVP_RCAMOF_P101		= SV_EJESTP_C5A;				/* タイマｶﾑ001 ＯＦ工程	*/
	SVP_RCAMOF_D101		= SV_EJETIM_C5A * 10;			/* タイマｶﾑ001 ＯＦ時間	*/
	SVP_RCAMON_P102		= SV_EJESTA_C5B;				/* タイマｶﾑ002 ＯＮ工程	*/
	SVP_RCAMON_D102		= SV_EJEKK3_C5B * 10;			/* タイマｶﾑ002 ＯＮ角度	*/
	SVP_RCAMOF_P102		= SV_EJESTP_C5B;				/* タイマｶﾑ002 ＯＦ工程	*/
	SVP_RCAMOF_D102		= SV_EJETIM_C5B * 10;			/* タイマｶﾑ002 ＯＦ時間	*/
	SVP_RCAMON_P103		= SV_AUTSTA_C51;				/* タイマｶﾑ003 ＯＮ工程	*/
	SVP_RCAMON_D103		= SV_AUTKK3_C51 * 10;			/* タイマｶﾑ003 ＯＮ角度	*/
	SVP_RCAMOF_P103		= SV_AUTSTP_C51;				/* タイマｶﾑ003 ＯＦ工程	*/
	SVP_RCAMOF_D103		= SV_AUTTIM_C51 * 10;			/* タイマｶﾑ003 ＯＦ時間	*/
	SVP_RCAMON_P104		= SV_AUTSTA_C51A;				/* タイマｶﾑ004 ＯＮ工程	*/
	SVP_RCAMON_D104		= SV_AUTKK3_C51A * 10;			/* タイマｶﾑ004 ＯＮ角度	*/
	SVP_RCAMOF_P104		= SV_AUTSTP_C51A;				/* タイマｶﾑ004 ＯＦ工程	*/
	SVP_RCAMOF_D104		= SV_AUTTIM_C51A * 10;			/* タイマｶﾑ004 ＯＦ時間	*/
	SVP_RCAMON_P105		= SV_AUTSTA_C51B;				/* タイマｶﾑ005 ＯＮ工程	*/
	SVP_RCAMON_D105		= SV_AUTKK3_C51B * 10;			/* タイマｶﾑ005 ＯＮ角度	*/
	SVP_RCAMOF_P105		= SV_AUTSTP_C51B;				/* タイマｶﾑ005 ＯＦ工程	*/
	SVP_RCAMOF_D105		= SV_AUTTIM_C51B * 10;			/* タイマｶﾑ005 ＯＦ時間	*/
	SVP_RCAMON_P106		= 0;							/* タイマｶﾑ006 ＯＮ工程	*/
	SVP_RCAMON_D106		= 0;							/* タイマｶﾑ006 ＯＮ角度	*/
	SVP_RCAMOF_P106		= 0;							/* タイマｶﾑ006 ＯＦ工程	*/
	SVP_RCAMOF_D106		= 0;							/* タイマｶﾑ006 ＯＦ時間	*/
	SVP_RCAMON_P107		= 0;							/* タイマｶﾑ007 ＯＮ工程	*/
	SVP_RCAMON_D107		= 0;							/* タイマｶﾑ007 ＯＮ角度	*/
	SVP_RCAMOF_P107		= 0;							/* タイマｶﾑ007 ＯＦ工程	*/
	SVP_RCAMOF_D107		= 0;							/* タイマｶﾑ007 ＯＦ時間	*/
	SVP_RCAMON_P108		= 0;							/* タイマｶﾑ008 ＯＮ工程	*/
	SVP_RCAMON_D108		= 0;							/* タイマｶﾑ008 ＯＮ角度	*/
	SVP_RCAMOF_P108		= 0;							/* タイマｶﾑ008 ＯＦ工程	*/
	SVP_RCAMOF_D108		= 0;							/* タイマｶﾑ008 ＯＦ時間	*/
	SVP_RCAMON_P109		= 0;							/* タイマｶﾑ009 ＯＮ工程	*/
	SVP_RCAMON_D109		= 0;							/* タイマｶﾑ009 ＯＮ角度	*/
	SVP_RCAMOF_P109		= 0;							/* タイマｶﾑ009 ＯＦ工程	*/
	SVP_RCAMOF_D109		= 0;							/* タイマｶﾑ009 ＯＦ時間	*/
	SVP_RCAMON_P10A		= 0;							/* タイマｶﾑ00A ＯＮ工程	*/
	SVP_RCAMON_D10A		= 0;							/* タイマｶﾑ00A ＯＮ角度	*/
	SVP_RCAMOF_P10A		= 0;							/* タイマｶﾑ00A ＯＦ工程	*/
	SVP_RCAMOF_D10A		= 0;							/* タイマｶﾑ00A ＯＦ時間	*/
	SVP_RCAMON_P10B		= 0;							/* タイマｶﾑ00B ＯＮ工程	*/
	SVP_RCAMON_D10B		= 0;							/* タイマｶﾑ00B ＯＮ角度	*/
	SVP_RCAMOF_P10B		= 0;							/* タイマｶﾑ00B ＯＦ工程	*/
	SVP_RCAMOF_D10B		= 0;							/* タイマｶﾑ00B ＯＦ時間	*/
	SVP_RCAMON_P10C		= 0;							/* タイマｶﾑ00C ＯＮ工程	*/
	SVP_RCAMON_D10C		= 0;							/* タイマｶﾑ00C ＯＮ角度	*/
	SVP_RCAMOF_P10C		= 0;							/* タイマｶﾑ00C ＯＦ工程	*/
	SVP_RCAMOF_D10C		= 0;							/* タイマｶﾑ00C ＯＦ時間	*/
	SVP_RCAMON_P10D		= 0;							/* タイマｶﾑ00D ＯＮ工程	*/
	SVP_RCAMON_D10D		= 0;							/* タイマｶﾑ00D ＯＮ角度	*/
	SVP_RCAMOF_P10D		= 0;							/* タイマｶﾑ00D ＯＦ工程	*/
	SVP_RCAMOF_D10D		= 0;							/* タイマｶﾑ00D ＯＦ時間	*/
	SVP_RCAMON_P10E		= 0;							/* タイマｶﾑ00E ＯＮ工程	*/
	SVP_RCAMON_D10E		= 0;							/* タイマｶﾑ00E ＯＮ角度	*/
	SVP_RCAMOF_P10E		= 0;							/* タイマｶﾑ00E ＯＦ工程	*/
	SVP_RCAMOF_D10E		= 0;							/* タイマｶﾑ00E ＯＦ時間	*/
	SVP_RCAMON_P10F		= 0;							/* タイマｶﾑ00F ＯＮ工程	*/
	SVP_RCAMON_D10F		= 0;							/* タイマｶﾑ00F ＯＮ角度	*/
	SVP_RCAMOF_P10F		= 0;							/* タイマｶﾑ00F ＯＦ工程	*/
	SVP_RCAMOF_D10F		= 0;							/* タイマｶﾑ00F ＯＦ時間	*/

//2002-08-28:追加
	SVP_CAMFUN_SEL00	= SV_CAMNA0_C1;					//ロータリカム１汎用選択種別
	SVP_CAMFUN_SEL01	= SV_CAMNA1_C1;					//ロータリカム２汎用選択種別
	SVP_CAMFUN_SEL02	= SV_CAMNA2_C1;					//ロータリカム３汎用選択種別
	SVP_CAMFUN_SEL03	= SV_CAMNA3_C1;					//ロータリカム４汎用選択種別
	SVP_CAMFUN_SEL04	= SV_CAMNA4_C1;					//ロータリカム５汎用選択種別
	SVP_CAMFUN_SEL05	= SV_CAMNA5_C1;					//ロータリカム６汎用選択種別
	SVP_CAMFUN_SEL06	= SV_CAMNA6_C1;					//ロータリカム７汎用選択種別
	SVP_CAMFUN_SEL07	= SV_CAMNA7_C1;					//ロータリカム８汎用選択種別
	SVP_CAMFUN_SEL08	= SV_CAMNA8_C1;					//ロータリカム９汎用選択種別
	SVP_CAMFUN_SEL09	= SV_CAMNA9_C1;					//ロータリカム１０汎用選択種別
	SVP_CAMFUN_SEL0A	= SV_CAMNAA_C1;					//ロータリカム１１汎用選択種別
	SVP_CAMFUN_SEL0B	= SV_CAMNAB_C1;					//ロータリカム１２汎用選択種別
	SVP_CAMFUN_SEL0C	= SV_CAMNAC_C1;					//ロータリカム１３汎用選択種別
	SVP_CAMFUN_SEL0D	= SV_CAMNAD_C1;					//ロータリカム１４汎用選択種別
	SVP_CAMFUN_SEL0E	= SV_CAMNAE_C1;					//ロータリカム１５汎用選択種別
	SVP_CAMFUN_SEL0F	= SV_CAMNAF_C1;					//ロータリカム１６汎用選択種別

}
/****************************************************************************/
