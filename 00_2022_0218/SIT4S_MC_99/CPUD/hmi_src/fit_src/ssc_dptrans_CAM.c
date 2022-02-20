/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�c�o�q�`�l �� �e�q�`�l	�f�[�^�]������				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"


extern	void	DPB_SEND_2B(U2b *Src);


/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CAM	(void)
{
	SVP_RCAMON_P000		= SV_RCLSTA11_C17;				/* �ʒu��000 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P000);
	SVP_RCAMON_D000		= SV_RCLS11_C17 * 10;			/* �ʒu��000 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D000);
	SVP_RCAMOF_P000		= SV_RCLSTP12_C17;				/* �ʒu��000 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P000);
	SVP_RCAMOF_D000		= SV_RCLS12_C17 * 10;			/* �ʒu��000 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D000);
	SVP_RCAMON_P001		= SV_RCLSTA21_C17;				/* �ʒu��001 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P001);
	SVP_RCAMON_D001		= SV_RCLS21_C17 * 10;			/* �ʒu��001 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D001);
	SVP_RCAMOF_P001		= SV_RCLSTP22_C17;				/* �ʒu��001 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P001);
	SVP_RCAMOF_D001		= SV_RCLS22_C17 * 10;			/* �ʒu��001 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D001);
	SVP_RCAMON_P002		= SV_RCLSTA31_C17;				/* �ʒu��002 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P002);
	SVP_RCAMON_D002		= SV_RCLS31_C17 * 10;			/* �ʒu��002 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D002);
	SVP_RCAMOF_P002		= SV_RCLSTP32_C17;				/* �ʒu��002 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P002);
	SVP_RCAMOF_D002		= SV_RCLS32_C17 * 10;			/* �ʒu��002 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D002);
	SVP_RCAMON_P003		= SV_RCLSTA41_C17;				/* �ʒu��003 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P003);
	SVP_RCAMON_D003		= SV_RCLS41_C17 * 10;			/* �ʒu��003 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D003);
	SVP_RCAMOF_P003		= SV_RCLSTP42_C17;				/* �ʒu��003 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P003);
	SVP_RCAMOF_D003		= SV_RCLS42_C17 * 10;			/* �ʒu��003 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D003);
	SVP_RCAMON_P004		= SV_RCLSTA51_C18;				/* �ʒu��004 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P004);
	SVP_RCAMON_D004		= SV_RCLS51_C18 * 10;			/* �ʒu��004 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D004);
	SVP_RCAMOF_P004		= SV_RCLSTP52_C18;				/* �ʒu��004 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P004);
	SVP_RCAMOF_D004		= SV_RCLS52_C18 * 10;			/* �ʒu��004 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D004);
	SVP_RCAMON_P005		= SV_RCLSTA61_C18;				/* �ʒu��005 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P005);
	SVP_RCAMON_D005		= SV_RCLS61_C18 * 10;			/* �ʒu��005 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D005);
	SVP_RCAMOF_P005		= SV_RCLSTP62_C18;				/* �ʒu��005 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P005);
	SVP_RCAMOF_D005		= SV_RCLS62_C18 * 10;			/* �ʒu��005 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D005);
	SVP_RCAMON_P006		= SV_RCLSTA71_C18;				/* �ʒu��006 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P006);
	SVP_RCAMON_D006		= SV_RCLS71_C18 * 10;			/* �ʒu��006 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D006);
	SVP_RCAMOF_P006		= SV_RCLSTP72_C18;				/* �ʒu��006 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P006);
	SVP_RCAMOF_D006		= SV_RCLS72_C18 * 10;			/* �ʒu��006 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D006);
	SVP_RCAMON_P007		= SV_RCLSTA81_C18;				/* �ʒu��007 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P007);
	SVP_RCAMON_D007		= SV_RCLS81_C18 * 10;			/* �ʒu��007 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D007);
	SVP_RCAMOF_P007		= SV_RCLSTP82_C18;				/* �ʒu��007 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P007);
	SVP_RCAMOF_D007		= SV_RCLS82_C18 * 10;			/* �ʒu��007 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D007);
	SVP_RCAMON_P008		= SV_RCLSTA11_C19;				/* �ʒu��008 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P008);
	SVP_RCAMON_D008		= SV_RCLS11_C19 * 10;			/* �ʒu��008 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D008);
	SVP_RCAMOF_P008		= SV_RCLSTP12_C19;				/* �ʒu��008 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P008);
	SVP_RCAMOF_D008		= SV_RCLS12_C19 * 10;			/* �ʒu��008 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D008);
	SVP_RCAMON_P009		= SV_RCLSTA21_C19;				/* �ʒu��009 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P009);
	SVP_RCAMON_D009		= SV_RCLS21_C19 * 10;			/* �ʒu��009 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D009);
	SVP_RCAMOF_P009		= SV_RCLSTA22_C19;				/* �ʒu��009 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P009);
	SVP_RCAMOF_D009		= SV_RCLS22_C19 * 10;			/* �ʒu��009 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D009);
	SVP_RCAMON_P00A		= SV_RCLSTA31_C19;				/* �ʒu��00A �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00A);
	SVP_RCAMON_D00A		= SV_RCLS31_C19 * 10;			/* �ʒu��00A �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00A);
	SVP_RCAMOF_P00A		= SV_RCLSTA32_C19;				/* �ʒu��00A �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00A);
	SVP_RCAMOF_D00A		= SV_RCLS32_C19 * 10;			/* �ʒu��00A �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00A);
	SVP_RCAMON_P00B		= SV_RCLSTA41_C19;				/* �ʒu��00B �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00B);
	SVP_RCAMON_D00B		= SV_RCLS41_C19 * 10;			/* �ʒu��00B �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00B);
	SVP_RCAMOF_P00B		= SV_RCLSTA42_C19;				/* �ʒu��00B �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00B);
	SVP_RCAMOF_D00B		= SV_RCLS42_C19 * 10;			/* �ʒu��00B �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00B);
	SVP_RCAMON_P00C		= SV_RCLSTA51_C19;				/* �ʒu��00C �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00C);
	SVP_RCAMON_D00C		= SV_RCLS51_C20 * 10;			/* �ʒu��00C �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00C);
	SVP_RCAMOF_P00C		= SV_RCLSTA52_C20;				/* �ʒu��00C �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00C);
	SVP_RCAMOF_D00C		= SV_RCLS52_C20 * 10;			/* �ʒu��00C �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00C);
	SVP_RCAMON_P00D		= SV_RCLSTA61_C20;				/* �ʒu��00D �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00D);
	SVP_RCAMON_D00D		= SV_RCLS61_C20 * 10;			/* �ʒu��00D �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00D);
	SVP_RCAMOF_P00D		= SV_RCLSTA62_C20;				/* �ʒu��00D �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00D);
	SVP_RCAMOF_D00D		= SV_RCLS62_C20 * 10;			/* �ʒu��00D �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00D);
	SVP_RCAMON_P00E		= SV_RCLSTA71_C20;				/* �ʒu��00E �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00E);
	SVP_RCAMON_D00E		= SV_RCLS71_C20 * 10;			/* �ʒu��00E �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00E);
	SVP_RCAMOF_P00E		= SV_RCLSTA72_C20;				/* �ʒu��00E �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00E);
	SVP_RCAMOF_D00E		= SV_RCLS72_C20 * 10;			/* �ʒu��00E �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00E);
	SVP_RCAMON_P00F		= SV_RCLSTA81_C20;				/* �ʒu��00F �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P00F);
	SVP_RCAMON_D00F		= SV_RCLS81_C20 * 10;			/* �ʒu��00F �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D00F);
	SVP_RCAMOF_P00F		= SV_RCLSTA82_C20;				/* �ʒu��00F �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P00F);
	SVP_RCAMOF_D00F		= SV_RCLS82_C20 * 10;			/* �ʒu��00F �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D00F);

	SVP_RCAMON_P010		= SV_MISSTA1_C9;				/* �ʒu��010 �~�X�t�B�[�h�P �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P010);
	SVP_RCAMON_D010		= SV_MISSK1_C9 * 10;			/* �ʒu��010 �~�X�t�B�[�h�P �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D010);
	SVP_RCAMOF_P010		= SV_MISSTP1_C9;				/* �ʒu��010 �~�X�t�B�[�h�P �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P010);
	SVP_RCAMOF_D010		= SV_MISSK2_C9 * 10;			/* �ʒu��010 �~�X�t�B�[�h�P �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D010);
	SVP_RCAMON_P011		= SV_MISSTA2_C9;				/* �ʒu��011 �~�X�t�B�[�h�Q �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P011);
	SVP_RCAMON_D011		= SV_MISSK3_C9 * 10;			/* �ʒu��011 �~�X�t�B�[�h�Q �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D011);
	SVP_RCAMOF_P011		= SV_MISSTP2_C9;				/* �ʒu��011 �~�X�t�B�[�h�Q �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P011);
	SVP_RCAMOF_D011		= SV_MISSK4_C9 * 10;			/* �ʒu��011 �~�X�t�B�[�h�Q �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D011);
	SVP_RCAMON_P012		= SV_MISSTA3_C9;				/* �ʒu��012 �~�X�t�B�[�h�R �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P012);
	SVP_RCAMON_D012		= SV_MISSK5_C9 * 10;			/* �ʒu��012 �~�X�t�B�[�h�R �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D012);
	SVP_RCAMOF_P012		= SV_MISSTP3_C9;				/* �ʒu��012 �~�X�t�B�[�h�R �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P012);
	SVP_RCAMOF_D012		= SV_MISSK6_C9 * 10;			/* �ʒu��012 �~�X�t�B�[�h�R �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D012);
	SVP_RCAMON_P013		= SV_MISSTA4_C9;				/* �ʒu��013 �~�X�t�B�[�h�S �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P013);
	SVP_RCAMON_D013		= SV_MISSK7_C9 * 10;			/* �ʒu��013 �~�X�t�B�[�h�S �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D013);
	SVP_RCAMOF_P013		= SV_MISSTP4_C9;				/* �ʒu��013 �~�X�t�B�[�h�S �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P013);
	SVP_RCAMOF_D013		= SV_MISSK8_C9 * 10;			/* �ʒu��013 �~�X�t�B�[�h�S �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D013);
	SVP_RCAMON_P014		= SV_MISSTA5_C10;				/* �ʒu��014 �~�X�t�B�[�h�T �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P014);
	SVP_RCAMON_D014		= SV_MISSK1_C10 * 10;			/* �ʒu��014 �~�X�t�B�[�h�T �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D014);
	SVP_RCAMOF_P014		= SV_MISSTP5_C10;				/* �ʒu��014 �~�X�t�B�[�h�T �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P014);
	SVP_RCAMOF_D014		= SV_MISSK2_C10 * 10;			/* �ʒu��014 �~�X�t�B�[�h�T �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D014);
	SVP_RCAMON_P015		= SV_MISSTA6_C10;				/* �ʒu��015 �~�X�t�B�[�h�U �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P015);
	SVP_RCAMON_D015		= SV_MISSK3_C10 * 10;			/* �ʒu��015 �~�X�t�B�[�h�U �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D015);
	SVP_RCAMOF_P015		= SV_MISSTP6_C10;				/* �ʒu��015 �~�X�t�B�[�h�U �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P015);
	SVP_RCAMOF_D015		= SV_MISSK4_C10 * 10;			/* �ʒu��015 �~�X�t�B�[�h�U �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D015);
	SVP_RCAMON_P016		= SV_MISSTA7_C10;				/* �ʒu��016 �~�X�t�B�[�h�V �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P016);
	SVP_RCAMON_D016		= SV_MISSK5_C10 * 10;			/* �ʒu��016 �~�X�t�B�[�h�V �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D016);
	SVP_RCAMOF_P016		= SV_MISSTP7_C10;				/* �ʒu��016 �~�X�t�B�[�h�V �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P016);
	SVP_RCAMOF_D016		= SV_MISSK6_C10 * 10;			/* �ʒu��016 �~�X�t�B�[�h�V �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D016);
	SVP_RCAMON_P017		= SV_MISSTA8_C10;				/* �ʒu��017 �~�X�t�B�[�h�W �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P017);
	SVP_RCAMON_D017		= SV_MISSK7_C10 * 10;			/* �ʒu��017 �~�X�t�B�[�h�W �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D017);
	SVP_RCAMOF_P017		= SV_MISSTP8_C10;				/* �ʒu��017 �~�X�t�B�[�h�W �n�e�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P017);
	SVP_RCAMOF_D017		= SV_MISSK8_C10 * 10;			/* �ʒu��017 �~�X�t�B�[�h�W �n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D017);

	SVP_RCAMON_P018		= 0;							/* �ʒu��018 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P018);
	SVP_RCAMON_D018		= SV_RCLSA1_A17 * 10;			/* �ʒu��018 �n�m�p�x	�V�X�e���J���`�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D018);
	SVP_RCAMOF_P018		= 0;							/* �ʒu��018 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P018);
	SVP_RCAMOF_D018		= SV_RCLSA2_A17 * 10;			/* �ʒu��018 �n�e�p�x	�V�X�e���J���`�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D018);
	SVP_RCAMON_P019		= 0;							/* �ʒu��019 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P019);
	SVP_RCAMON_D019		= SV_RCLSB1_A17 * 10;			/* �ʒu��019 �n�m�p�x	�V�X�e���J���a�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D019);
	SVP_RCAMOF_P019		= 0;							/* �ʒu��019 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P019);
	SVP_RCAMOF_D019		= SV_RCLSB2_A17 * 10;			/* �ʒu��019 �n�e�p�x	�V�X�e���J���a�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D019);
	SVP_RCAMON_P01A		= 0;							/* �ʒu��01A �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01A);
	SVP_RCAMON_D01A		= SV_RCLSC1_A17 * 10;			/* �ʒu��01A �n�m�p�x	�V�X�e���J���b�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01A);
	SVP_RCAMOF_P01A		= 0;							/* �ʒu��01A �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01A);
	SVP_RCAMOF_D01A		= SV_RCLSC2_A17 * 10;			/* �ʒu��01A �n�e�p�x	�V�X�e���J���b�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01A);
	SVP_RCAMON_P01B		= 0;							/* �ʒu��01B �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01B);
	SVP_RCAMON_D01B		= SV_RCLSD1_A17 * 10;			/* �ʒu��01B �n�m�p�x	�V�X�e���J���c�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01B);
	SVP_RCAMOF_P01B		= 0;							/* �ʒu��01B �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01B);
	SVP_RCAMOF_D01B		= SV_RCLSD2_A17 * 10;			/* �ʒu��01B �n�e�p�x	�V�X�e���J���c�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01B);
	SVP_RCAMON_P01C		= 0;							/* �ʒu��01C �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01C);
	SVP_RCAMON_D01C		= SV_RCLSE1_A17 * 10;			/* �ʒu��01C �n�m�p�x	�V�X�e���J���d�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01C);
	SVP_RCAMOF_P01C		= 0;							/* �ʒu��01C �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01C);
	SVP_RCAMOF_D01C		= SV_RCLSE2_A17 * 10;			/* �ʒu��01C �n�e�p�x	�V�X�e���J���d�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01C);
	SVP_RCAMON_P01D		= 0;							/* �ʒu��01D �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01D);
	SVP_RCAMON_D01D		= SV_RCLSF1_A18 * 10;			/* �ʒu��01D �n�m�p�x	�V�X�e���J���e�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01D);
	SVP_RCAMOF_P01D		= 0;							/* �ʒu��01D �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01D);
	SVP_RCAMOF_D01D		= SV_RCLSF2_A18 * 10;			/* �ʒu��01D �n�e�p�x	�V�X�e���J���e�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01D);
	SVP_RCAMON_P01E		= 0;							/* �ʒu��01E �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01E);
	SVP_RCAMON_D01E		= SV_RCLSG1_A18 * 10;			/* �ʒu��01E �n�m�p�x	�V�X�e���J���f�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01E);
	SVP_RCAMOF_P01E		= 0;							/* �ʒu��01E �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01E);
	SVP_RCAMOF_D01E		= SV_RCLSG2_A18 * 10;			/* �ʒu��01E �n�e�p�x	�V�X�e���J���f�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01E);
	SVP_RCAMON_P01F		= 0;							/* �ʒu��01F �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P01F);
	SVP_RCAMON_D01F		= SV_RCLSH1_A18 * 10;			/* �ʒu��01F �n�m�p�x	�V�X�e���J���g�@�n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D01F);
	SVP_RCAMOF_P01F		= 0;							/* �ʒu��01F �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P01F);
	SVP_RCAMOF_D01F		= SV_RCLSH2_A18 * 10;			/* �ʒu��01F �n�e�p�x	�V�X�e���J���g�@�n�e�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D01F);

	SVP_RCAMON_P020		= SV_EJESAT1_C4;				/* �ʒu��020 �G�W�F�N�^�P �n�m�H��   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P020);
	SVP_RCAMON_D020		= SV_EJEKK1_C4 * 10;			/* �ʒu��020 �G�W�F�N�^�P �n�m�p�x   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D020);
	SVP_RCAMOF_P020		= SV_EJESTP1_C4;				/* �ʒu��020 �G�W�F�N�^�P �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P020);
	SVP_RCAMOF_D020		= SV_EJEKK2_C4 * 10;			/* �ʒu��020 �G�W�F�N�^�P �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D020);
	SVP_RCAMON_P021		= SV_EJESAT1_C4A;				/* �ʒu��021 �G�W�F�N�^�Q �n�m�H��   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P021);
	SVP_RCAMON_D021		= SV_EJEKK1_C4A * 10;			/* �ʒu��021 �G�W���N�^�Q �n�m�p�x   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D021);
	SVP_RCAMOF_P021		= SV_EJESTP1_C4A;				/* �ʒu��021 �G�W�F�N�^�Q �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P021);
	SVP_RCAMOF_D021		= SV_EJEKK2_C4A * 10;			/* �ʒu��021 �G�W�F�N�^�Q �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D021);
	SVP_RCAMON_P022		= SV_EJESAT1_C4B;				/* �ʒu��022 �G�W�F�N�^�R �n�m�H��   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P022);
	SVP_RCAMON_D022		= SV_EJEKK1_C4B * 10;			/* �ʒu��022 �G�W���N�^�R �n�m�p�x   �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D022);
	SVP_RCAMOF_P022		= SV_EJESTP1_C4B;				/* �ʒu��022 �G�W�F�N�^�R �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P022);
	SVP_RCAMOF_D022		= SV_EJEKK2_C4B * 10;			/* �ʒu��022 �G�W�F�N�^�R �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D022);
	SVP_RCAMON_P023		= SV_AUTSTA_C41;				/* �ʒu��023 �������P �n�m�H��	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P023);
	SVP_RCAMON_D023		= SV_AUTKK1_C41 * 10;			/* �ʒu��023 �������P �n�m�p�x	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D023);
	SVP_RCAMOF_P023		= SV_AUTSTP_C41;				/* �ʒu��023 �������P �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P023);
	SVP_RCAMOF_D023		= SV_AUTKK2_C41 * 10;			/* �ʒu��023 �������P �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D023);
	SVP_RCAMON_P024		= SV_AUTSTA_C41A;				/* �ʒu��024 �������Q �n�m�H��	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P024);
	SVP_RCAMON_D024		= SV_AUTKK1_C41A * 10;			/* �ʒu��024 �������Q �n�m�p�x	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D024);
	SVP_RCAMOF_P024		= SV_AUTSTP_C41A;				/* �ʒu��024 �������Q �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P024);
	SVP_RCAMOF_D024		= SV_AUTKK2_C41A * 10;			/* �ʒu��024 �������Q �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D024);
	SVP_RCAMON_P025		= SV_AUTSTA_C41B;				/* �ʒu��025 �������R �n�m�H��	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_P025);
	SVP_RCAMON_D025		= SV_AUTKK1_C41B * 10;			/* �ʒu��025 �������R �n�m�p�x	 �J���d�l */
	DPB_SEND_2B(&SVP_RCAMON_D025);
	SVP_RCAMOF_P025		= SV_AUTSTP_C41B;				/* �ʒu��025 �������R �n�e�e�H�� �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_P025);
	SVP_RCAMOF_D025		= SV_AUTKK2_C41B * 10;			/* �ʒu��025 �������R �n�e�e�p�x �J���d�l */
	DPB_SEND_2B(&SVP_RCAMOF_D025);
	SVP_RCAMON_P026		= 0;							/* �ʒu��026 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P026);
	SVP_RCAMON_D026		= 0;							/* �ʒu��026 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D026);
	SVP_RCAMOF_P026		= 0;							/* �ʒu��026 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P026);
	SVP_RCAMOF_D026		= 0;							/* �ʒu��026 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D026);
	SVP_RCAMON_P027		= 0;							/* �ʒu��027 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P027);
	SVP_RCAMON_D027		= 0;							/* �ʒu��027 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D027);
	SVP_RCAMOF_P027		= 0;							/* �ʒu��027 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P027);
	SVP_RCAMOF_D027		= 0;							/* �ʒu��027 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D027);
	SVP_RCAMON_P028		= 0;							/* �ʒu��028 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P028);
	SVP_RCAMON_D028		= 0;							/* �ʒu��028 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D028);
	SVP_RCAMOF_P028		= 0;							/* �ʒu��028 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P028);
	SVP_RCAMOF_D028		= 0;							/* �ʒu��028 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D028);
	SVP_RCAMON_P029		= 0;							/* �ʒu��029 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P029);
	SVP_RCAMON_D029		= 0;							/* �ʒu��029 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D029);
	SVP_RCAMOF_P029		= 0;							/* �ʒu��029 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P029);
	SVP_RCAMOF_D029		= 0;							/* �ʒu��029 �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D029);
	SVP_RCAMON_P02A		= 0;							/* �ʒu��02A �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02A);
	SVP_RCAMON_D02A		= 0;							/* �ʒu��02A �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02A);
	SVP_RCAMOF_P02A		= 0;							/* �ʒu��02A �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02A);
	SVP_RCAMOF_D02A		= 0;							/* �ʒu��02A �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02A);
	SVP_RCAMON_P02B		= 0;							/* �ʒu��02B �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02B);
	SVP_RCAMON_D02B		= 0;							/* �ʒu��02B �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02B);
	SVP_RCAMOF_P02B		= 0;							/* �ʒu��02B �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02B);
	SVP_RCAMOF_D02B		= 0;							/* �ʒu��02B �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02B);
	SVP_RCAMON_P02C		= 0;							/* �ʒu��02C �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02C);
	SVP_RCAMON_D02C		= 0;							/* �ʒu��02C �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02C);
	SVP_RCAMOF_P02C		= 0;							/* �ʒu��02C �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02C);
	SVP_RCAMOF_D02C		= 0;							/* �ʒu��02C �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02C);
	SVP_RCAMON_P02D		= 0;							/* �ʒu��02D �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02D);
	SVP_RCAMON_D02D		= 0;							/* �ʒu��02D �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02D);
	SVP_RCAMOF_P02D		= 0;							/* �ʒu��02D �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02D);
	SVP_RCAMOF_D02D		= 0;							/* �ʒu��02D �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02D);
	SVP_RCAMON_P02E		= 0;							/* �ʒu��02E �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02E);
	SVP_RCAMON_D02E		= 0;							/* �ʒu��02E �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02E);
	SVP_RCAMOF_P02E		= 0;							/* �ʒu��02E �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02E);
	SVP_RCAMOF_D02E		= 0;							/* �ʒu��02E �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02E);
	SVP_RCAMON_P02F		= 0;							/* �ʒu��02F �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P02F);
	SVP_RCAMON_D02F		= 0;							/* �ʒu��02F �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D02F);
	SVP_RCAMOF_P02F		= 0;							/* �ʒu��02F �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P02F);
	SVP_RCAMOF_D02F		= 0;							/* �ʒu��02F �n�e�p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_D02F);

	SVP_RCAMON_P100		= SV_EJESTA_C5;					/* �^�C�}��000 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P100);
	SVP_RCAMON_D100		= SV_EJEKK3_C5 * 10;			/* �^�C�}��000 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D100);
	SVP_RCAMOF_P100		= SV_EJESTP_C5;					/* �^�C�}��000 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P100);
	SVP_RCAMOF_D100		= SV_EJETIM_C5 * 10;			/* �^�C�}��000 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D100);
	SVP_RCAMON_P101		= SV_EJESTA_C5A;				/* �^�C�}��001 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P101);
	SVP_RCAMON_D101		= SV_EJEKK3_C5A * 10;			/* �^�C�}��001 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D101);
	SVP_RCAMOF_P101		= SV_EJESTP_C5A;				/* �^�C�}��001 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P101);
	SVP_RCAMOF_D101		= SV_EJETIM_C5A * 10;			/* �^�C�}��001 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D101);
	SVP_RCAMON_P102		= SV_EJESTA_C5B;				/* �^�C�}��002 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P102);
	SVP_RCAMON_D102		= SV_EJEKK3_C5B * 10;			/* �^�C�}��002 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D102);
	SVP_RCAMOF_P102		= SV_EJESTP_C5B;				/* �^�C�}��002 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P102);
	SVP_RCAMOF_D102		= SV_EJETIM_C5B * 10;			/* �^�C�}��002 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D102);
	SVP_RCAMON_P103		= SV_AUTSTA_C51;				/* �^�C�}��003 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P103);
	SVP_RCAMON_D103		= SV_AUTKK3_C51 * 10;			/* �^�C�}��003 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D103);
	SVP_RCAMOF_P103		= SV_AUTSTP_C51;				/* �^�C�}��003 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P103);
	SVP_RCAMOF_D103		= SV_AUTTIM_C51 * 10;			/* �^�C�}��003 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D103);
	SVP_RCAMON_P104		= SV_AUTSTA_C51A;				/* �^�C�}��004 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P104);
	SVP_RCAMON_D104		= SV_AUTKK3_C51A * 10;			/* �^�C�}��004 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D104);
	SVP_RCAMOF_P104		= SV_AUTSTP_C51A;				/* �^�C�}��004 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P104);
	SVP_RCAMOF_D104		= SV_AUTTIM_C51A * 10;			/* �^�C�}��004 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D104);
	SVP_RCAMON_P105		= SV_AUTSTA_C51B;				/* �^�C�}��005 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P105);
	SVP_RCAMON_D105		= SV_AUTKK3_C51B * 10;			/* �^�C�}��005 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D105);
	SVP_RCAMOF_P105		= SV_AUTSTP_C51B;				/* �^�C�}��005 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P105);
	SVP_RCAMOF_D105		= SV_AUTTIM_C51B * 10;			/* �^�C�}��005 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D105);
	SVP_RCAMON_P106		= 0;							/* �^�C�}��006 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P106);
	SVP_RCAMON_D106		= 0;							/* �^�C�}��006 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D106);
	SVP_RCAMOF_P106		= 0;							/* �^�C�}��006 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P106);
	SVP_RCAMOF_D106		= 0;							/* �^�C�}��006 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D106);
	SVP_RCAMON_P107		= 0;							/* �^�C�}��007 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P107);
	SVP_RCAMON_D107		= 0;							/* �^�C�}��007 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D107);
	SVP_RCAMOF_P107		= 0;							/* �^�C�}��007 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P107);
	SVP_RCAMOF_D107		= 0;							/* �^�C�}��007 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D107);
	SVP_RCAMON_P108		= 0;							/* �^�C�}��008 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P108);
	SVP_RCAMON_D108		= 0;							/* �^�C�}��008 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D108);
	SVP_RCAMOF_P108		= 0;							/* �^�C�}��008 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P108);
	SVP_RCAMOF_D108		= 0;							/* �^�C�}��008 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D108);
	SVP_RCAMON_P109		= 0;							/* �^�C�}��009 �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P109);
	SVP_RCAMON_D109		= 0;							/* �^�C�}��009 �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D109);
	SVP_RCAMOF_P109		= 0;							/* �^�C�}��009 �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P109);
	SVP_RCAMOF_D109		= 0;							/* �^�C�}��009 �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D109);
	SVP_RCAMON_P10A		= 0;							/* �^�C�}��00A �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10A);
	SVP_RCAMON_D10A		= 0;							/* �^�C�}��00A �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10A);
	SVP_RCAMOF_P10A		= 0;							/* �^�C�}��00A �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10A);
	SVP_RCAMOF_D10A		= 0;							/* �^�C�}��00A �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10A);
	SVP_RCAMON_P10B		= 0;							/* �^�C�}��00B �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10B);
	SVP_RCAMON_D10B		= 0;							/* �^�C�}��00B �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10B);
	SVP_RCAMOF_P10B		= 0;							/* �^�C�}��00B �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10B);
	SVP_RCAMOF_D10B		= 0;							/* �^�C�}��00B �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10B);
	SVP_RCAMON_P10C		= 0;							/* �^�C�}��00C �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10C);
	SVP_RCAMON_D10C		= 0;							/* �^�C�}��00C �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10C);
	SVP_RCAMOF_P10C		= 0;							/* �^�C�}��00C �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10C);
	SVP_RCAMOF_D10C		= 0;							/* �^�C�}��00C �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10C);
	SVP_RCAMON_P10D		= 0;							/* �^�C�}��00D �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10D);
	SVP_RCAMON_D10D		= 0;							/* �^�C�}��00D �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10D);
	SVP_RCAMOF_P10D		= 0;							/* �^�C�}��00D �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10D);
	SVP_RCAMOF_D10D		= 0;							/* �^�C�}��00D �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10D);
	SVP_RCAMON_P10E		= 0;							/* �^�C�}��00E �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10E);
	SVP_RCAMON_D10E		= 0;							/* �^�C�}��00E �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10E);
	SVP_RCAMOF_P10E		= 0;							/* �^�C�}��00E �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10E);
	SVP_RCAMOF_D10E		= 0;							/* �^�C�}��00E �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10E);
	SVP_RCAMON_P10F		= 0;							/* �^�C�}��00F �n�m�H��	*/
	DPB_SEND_2B(&SVP_RCAMON_P10F);
	SVP_RCAMON_D10F		= 0;							/* �^�C�}��00F �n�m�p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_D10F);
	SVP_RCAMOF_P10F		= 0;							/* �^�C�}��00F �n�e�H��	*/
	DPB_SEND_2B(&SVP_RCAMOF_P10F);
	SVP_RCAMOF_D10F		= 0;							/* �^�C�}��00F �n�e����	*/
	DPB_SEND_2B(&SVP_RCAMOF_D10F);

//2002-08-28:�ǉ�
	SVP_CAMFUN_SEL00	= SV_CAMNA0_C1;					//���[�^���J���P�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL00);
	SVP_CAMFUN_SEL01	= SV_CAMNA1_C1;					//���[�^���J���Q�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL01);
	SVP_CAMFUN_SEL02	= SV_CAMNA2_C1;					//���[�^���J���R�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL02);
	SVP_CAMFUN_SEL03	= SV_CAMNA3_C1;					//���[�^���J���S�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL03);
	SVP_CAMFUN_SEL04	= SV_CAMNA4_C1;					//���[�^���J���T�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL04);
	SVP_CAMFUN_SEL05	= SV_CAMNA5_C1;					//���[�^���J���U�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL05);
	SVP_CAMFUN_SEL06	= SV_CAMNA6_C1;					//���[�^���J���V�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL06);
	SVP_CAMFUN_SEL07	= SV_CAMNA7_C1;					//���[�^���J���W�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL07);
	SVP_CAMFUN_SEL08	= SV_CAMNA8_C1;					//���[�^���J���X�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL08);
	SVP_CAMFUN_SEL09	= SV_CAMNA9_C1;					//���[�^���J���P�O�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL09);
	SVP_CAMFUN_SEL0A	= SV_CAMNAA_C1;					//���[�^���J���P�P�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0A);
	SVP_CAMFUN_SEL0B	= SV_CAMNAB_C1;					//���[�^���J���P�Q�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0B);
	SVP_CAMFUN_SEL0C	= SV_CAMNAC_C1;					//���[�^���J���P�R�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0C);
	SVP_CAMFUN_SEL0D	= SV_CAMNAD_C1;					//���[�^���J���P�S�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0D);
	SVP_CAMFUN_SEL0E	= SV_CAMNAE_C1;					//���[�^���J���P�T�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0E);
	SVP_CAMFUN_SEL0F	= SV_CAMNAF_C1;					//���[�^���J���P�U�ėp�I�����
	DPB_SEND_2B(&SVP_CAMFUN_SEL0F);

//2014/09/02
	SVP_RCAMON_SA00		= SV_RCSS11_C17 * 10;			/* ���[�^���J���O�P  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA00);
	SVP_RCAMON_ST00		= SV_RCSS21_C17;				/* ���[�^���J���O�P  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST00);
	SVP_RCAMOF_SA00		= SV_RCSS31_C17 * 10;			/* ���[�^���J���O�P  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA00);
	SVP_RCAMOF_ST00		= SV_RCSS41_C17;				/* ���[�^���J���O�P  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST00);
	SVP_RCAMON_SA01		= SV_RCSS12_C17 * 10;			/* ���[�^���J���O�Q  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA01);
	SVP_RCAMON_ST01		= SV_RCSS22_C17;				/* ���[�^���J���O�Q  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST01);
	SVP_RCAMOF_SA01		= SV_RCSS32_C17 * 10;			/* ���[�^���J���O�Q  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA01);
	SVP_RCAMOF_ST01		= SV_RCSS42_C17;				/* ���[�^���J���O�Q  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST01);
	SVP_RCAMON_SA02		= SV_RCSS13_C17 * 10;			/* ���[�^���J���O�R  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA02);
	SVP_RCAMON_ST02		= SV_RCSS23_C17;				/* ���[�^���J���O�R  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST02);
	SVP_RCAMOF_SA02		= SV_RCSS33_C17 * 10;			/* ���[�^���J���O�R  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA02);
	SVP_RCAMOF_ST02		= SV_RCSS43_C17;				/* ���[�^���J���O�R  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST02);
	SVP_RCAMON_SA03		= SV_RCSS14_C17 * 10;			/* ���[�^���J���O�S  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA03);
	SVP_RCAMON_ST03		= SV_RCSS24_C17;				/* ���[�^���J���O�S  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST03);
	SVP_RCAMOF_SA03		= SV_RCSS34_C17 * 10;			/* ���[�^���J���O�S  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA03);
	SVP_RCAMOF_ST03		= SV_RCSS44_C17;				/* ���[�^���J���O�S  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST03);
	SVP_RCAMON_SA04		= SV_RCSS11_C18 * 10;			/* ���[�^���J���O�T  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA04);
	SVP_RCAMON_ST04		= SV_RCSS21_C18;				/* ���[�^���J���O�T  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST04);
	SVP_RCAMOF_SA04		= SV_RCSS31_C18 * 10;			/* ���[�^���J���O�T  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA04);
	SVP_RCAMOF_ST04		= SV_RCSS41_C18;				/* ���[�^���J���O�T  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST04);
	SVP_RCAMON_SA05		= SV_RCSS12_C18 * 10;			/* ���[�^���J���O�U  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA05);
	SVP_RCAMON_ST05		= SV_RCSS22_C18;				/* ���[�^���J���O�U  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST05);
	SVP_RCAMOF_SA05		= SV_RCSS32_C18 * 10;			/* ���[�^���J���O�U  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA05);
	SVP_RCAMOF_ST05		= SV_RCSS42_C18;				/* ���[�^���J���O�U  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST05);
	SVP_RCAMON_SA06		= SV_RCSS13_C18 * 10;			/* ���[�^���J���O�V  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA06);
	SVP_RCAMON_ST06		= SV_RCSS23_C18;				/* ���[�^���J���O�V  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST06);
	SVP_RCAMOF_SA06		= SV_RCSS33_C18 * 10;			/* ���[�^���J���O�V  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA06);
	SVP_RCAMOF_ST06		= SV_RCSS43_C18;				/* ���[�^���J���O�V  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST06);
	SVP_RCAMON_SA07		= SV_RCSS14_C18 * 10;			/* ���[�^���J���O�W  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA07);
	SVP_RCAMON_ST07		= SV_RCSS24_C18;				/* ���[�^���J���O�W  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST07);
	SVP_RCAMOF_SA07		= SV_RCSS34_C18 * 10;			/* ���[�^���J���O�W  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA07);
	SVP_RCAMOF_ST07		= SV_RCSS44_C18;				/* ���[�^���J���O�W  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST07);
	SVP_RCAMON_SA08		= SV_RCSS11_C19 * 10;			/* ���[�^���J���O�X  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA08);
	SVP_RCAMON_ST08		= SV_RCSS21_C19;				/* ���[�^���J���O�X  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST08);
	SVP_RCAMOF_SA08		= SV_RCSS31_C19 * 10;			/* ���[�^���J���O�X  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA08);
	SVP_RCAMOF_ST08		= SV_RCSS41_C19;				/* ���[�^���J���O�X  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST08);
	SVP_RCAMON_SA09		= SV_RCSS12_C19 * 10;			/* ���[�^���J���P�O  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA09);
	SVP_RCAMON_ST09		= SV_RCSS22_C19;				/* ���[�^���J���P�O  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST09);
	SVP_RCAMOF_SA09		= SV_RCSS32_C19 * 10;			/* ���[�^���J���P�O  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA09);
	SVP_RCAMOF_ST09		= SV_RCSS42_C19;				/* ���[�^���J���P�O  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST09);
	SVP_RCAMON_SA10		= SV_RCSS13_C19 * 10;			/* ���[�^���J���P�P  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA10);
	SVP_RCAMON_ST10		= SV_RCSS23_C19;				/* ���[�^���J���P�P  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST10);
	SVP_RCAMOF_SA10		= SV_RCSS33_C19 * 10;			/* ���[�^���J���P�P  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA10);
	SVP_RCAMOF_ST10		= SV_RCSS43_C19;				/* ���[�^���J���P�P  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST10);
	SVP_RCAMON_SA11		= SV_RCSS14_C19 * 10;			/* ���[�^���J���P�Q  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA11);
	SVP_RCAMON_ST11		= SV_RCSS24_C19;				/* ���[�^���J���P�Q  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST11);
	SVP_RCAMOF_SA11		= SV_RCSS34_C19 * 10;			/* ���[�^���J���P�Q  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA11);
	SVP_RCAMOF_ST11		= SV_RCSS44_C19;				/* ���[�^���J���P�Q  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST11);
	SVP_RCAMON_SA12		= SV_RCSS11_C20 * 10;			/* ���[�^���J���P�R  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA12);
	SVP_RCAMON_ST12		= SV_RCSS21_C20;				/* ���[�^���J���P�R  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST12);
	SVP_RCAMOF_SA12		= SV_RCSS31_C20 * 10;			/* ���[�^���J���P�R  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA12);
	SVP_RCAMOF_ST12		= SV_RCSS41_C20;				/* ���[�^���J���P�R  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST12);
	SVP_RCAMON_SA13		= SV_RCSS12_C20 * 10;			/* ���[�^���J���P�S  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA13);
	SVP_RCAMON_ST13		= SV_RCSS22_C20;				/* ���[�^���J���P�S  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST13);
	SVP_RCAMOF_SA13		= SV_RCSS32_C20 * 10;			/* ���[�^���J���P�S  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA13);
	SVP_RCAMOF_ST13		= SV_RCSS42_C20;				/* ���[�^���J���P�S  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST13);
	SVP_RCAMON_SA14		= SV_RCSS13_C20 * 10;			/* ���[�^���J���P�T  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA14);
	SVP_RCAMON_ST14		= SV_RCSS23_C20;				/* ���[�^���J���P�T  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST14);
	SVP_RCAMOF_SA14		= SV_RCSS33_C20 * 10;			/* ���[�^���J���P�T  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA14);
	SVP_RCAMOF_ST14		= SV_RCSS43_C20;				/* ���[�^���J���P�T  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST14);
	SVP_RCAMON_SA15		= SV_RCSS14_C20 * 10;			/* ���[�^���J���P�U  ON�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMON_SA15);
	SVP_RCAMON_ST15		= SV_RCSS24_C20;				/* ���[�^���J���P�U  ON�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMON_ST15);
	SVP_RCAMOF_SA15		= SV_RCSS34_C20 * 10;			/* ���[�^���J���P�U  OFF�i�p  �p�x	*/
	DPB_SEND_2B(&SVP_RCAMOF_SA15);
	SVP_RCAMOF_ST15		= SV_RCSS44_C20;				/* ���[�^���J���P�U  OFF�i�p  ����	*/
	DPB_SEND_2B(&SVP_RCAMOF_ST15);

//2014/09/05
	SVP_ROTCAM_ONR		= SV_ROTCAM_ONR;				//۰�ض� ON�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_ROTCAM_ONR);
	SVP_ROTCAM_OFR		= SV_ROTCAM_OFR;				//۰�ض� OFF�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_ROTCAM_OFR);
	SVP_EJECAM_ONR		= SV_EJECAM_ONR;				//��ު�� ON�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_EJECAM_ONR);
	SVP_EJECAM_OFR		= SV_EJECAM_OFR;				//��ު�� OFF�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_EJECAM_OFR);
	SVP_MISCAM_ONR		= SV_MISCAM_ONR;				//н̨���  ON�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_MISCAM_ONR);
	SVP_MISCAM_OFR		= SV_MISCAM_OFR;				//н̨���  OFF�s�� ��߰Ė߂�
	DPB_SEND_2B(&SVP_MISCAM_OFR);

//;	=== 2016/11/15 ���[�^���J���^�C�}�d�l =====
	SVP_RCAMON_P110		= SV_RCLSTA11_C17T   ;// ���[�^���J���P�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P110);
	SVP_RCAMON_D110		= SV_RCLS11_C17T * 10    ;// ���[�^���J���P�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D110);
	SVP_RCAMOF_P110		= SV_RCLSTP12_C17T   ;// ���[�^���J���P�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P110);
	SVP_RCAMOF_D110		= SV_RCLS12_C17T / 10    ;// ���[�^���J���P�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D110);
	SVP_RCAMON_P111		= SV_RCLSTA21_C17T   ;// ���[�^���J���Q�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P111);
	SVP_RCAMON_D111		= SV_RCLS21_C17T * 10     ;// ���[�^���J���Q�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D111);
	SVP_RCAMOF_P111		= SV_RCLSTP22_C17T   ;// ���[�^���J���Q�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P111);
	SVP_RCAMOF_D111		= SV_RCLS22_C17T / 10     ;// ���[�^���J���Q�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D111);
	SVP_RCAMON_P112		= SV_RCLSTA31_C17T   ;// ���[�^���J���R�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P112);
	SVP_RCAMON_D112		= SV_RCLS31_C17T * 10     ;// ���[�^���J���R�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D112);
	SVP_RCAMOF_P112		= SV_RCLSTP32_C17T   ;// ���[�^���J���R�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P112);
	SVP_RCAMOF_D112		= SV_RCLS32_C17T / 10     ;// ���[�^���J���R�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D112);
	SVP_RCAMON_P113		= SV_RCLSTA41_C17T   ;// ���[�^���J���S�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P113);
	SVP_RCAMON_D113		= SV_RCLS41_C17T * 10     ;// ���[�^���J���S�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D113);
	SVP_RCAMOF_P113		= SV_RCLSTP42_C17T   ;// ���[�^���J���S�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P113);
	SVP_RCAMOF_D113		= SV_RCLS42_C17T / 10     ;// ���[�^���J���S�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D113);
	SVP_RCAMON_P114		= SV_RCLSTA51_C18T   ;// ���[�^���J���T�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P114);
	SVP_RCAMON_D114		= SV_RCLS51_C18T * 10     ;// ���[�^���J���T�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D114);
	SVP_RCAMOF_P114		= SV_RCLSTP52_C18T   ;// ���[�^���J���T�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P114);
	SVP_RCAMOF_D114		= SV_RCLS52_C18T / 10     ;// ���[�^���J���T�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D114);
	SVP_RCAMON_P115		= SV_RCLSTA61_C18T   ;// ���[�^���J���U�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P115);
	SVP_RCAMON_D115		= SV_RCLS61_C18T * 10     ;// ���[�^���J���U�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D115);
	SVP_RCAMOF_P115		= SV_RCLSTP62_C18T   ;// ���[�^���J���U�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P115);
	SVP_RCAMOF_D115		= SV_RCLS62_C18T / 10     ;// ���[�^���J���U�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D115);
	SVP_RCAMON_P116		= SV_RCLSTA71_C18T   ;// ���[�^���J���V�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P116);
	SVP_RCAMON_D116		= SV_RCLS71_C18T * 10     ;// ���[�^���J���V�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D116);
	SVP_RCAMOF_P116		= SV_RCLSTP72_C18T   ;// ���[�^���J���V�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P116);
	SVP_RCAMOF_D116		= SV_RCLS72_C18T / 10     ;// ���[�^���J���V�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D116);
	SVP_RCAMON_P117		= SV_RCLSTA81_C18T   ;// ���[�^���J���W�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P117);
	SVP_RCAMON_D117		= SV_RCLS81_C18T * 10     ;// ���[�^���J���W�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D117);
	SVP_RCAMOF_P117		= SV_RCLSTP82_C18T   ;// ���[�^���J���W�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P117);
	SVP_RCAMOF_D117		= SV_RCLS82_C18T / 10     ;// ���[�^���J���W�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D117);
	SVP_RCAMON_P118		= SV_RCLSTA11_C19T   ;// ���[�^���J���X�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P118);
	SVP_RCAMON_D118		= SV_RCLS11_C19T * 10     ;// ���[�^���J���X�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D118);
	SVP_RCAMOF_P118		= SV_RCLSTP12_C19T   ;// ���[�^���J���X�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P118);
	SVP_RCAMOF_D118		= SV_RCLS12_C19T / 10     ;// ���[�^���J���X�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D118);
	SVP_RCAMON_P119		= SV_RCLSTA21_C19T   ;// ���[�^���J���P�O�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P119);
	SVP_RCAMON_D119		= SV_RCLS21_C19T * 10     ;// ���[�^���J���P�O�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D119);
	SVP_RCAMOF_P119		= SV_RCLSTA22_C19T   ;// ���[�^���J���P�O�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P119);
	SVP_RCAMOF_D119		= SV_RCLS22_C19T / 10     ;// ���[�^���J���P�O�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D119);
	SVP_RCAMON_P11A		= SV_RCLSTA31_C19T   ;// ���[�^���J���P�P�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11A);
	SVP_RCAMON_D11A		= SV_RCLS31_C19T * 10     ;// ���[�^���J���P�P�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11A);
	SVP_RCAMOF_P11A		= SV_RCLSTA32_C19T   ;// ���[�^���J���P�P�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11A);
	SVP_RCAMOF_D11A		= SV_RCLS32_C19T / 10     ;// ���[�^���J���P�P�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11A);
	SVP_RCAMON_P11B		= SV_RCLSTA41_C19T   ;// ���[�^���J���P�Q�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11B);
	SVP_RCAMON_D11B		= SV_RCLS41_C19T * 10     ;// ���[�^���J���P�Q�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11B);
	SVP_RCAMOF_P11B		= SV_RCLSTA42_C19T   ;// ���[�^���J���P�Q�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11B);
	SVP_RCAMOF_D11B		= SV_RCLS42_C19T / 10     ;// ���[�^���J���P�Q�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11B);
	SVP_RCAMON_P11C		= SV_RCLSTA51_C19T   ;// ���[�^���J���P�R�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11C);
	SVP_RCAMON_D11C		= SV_RCLS51_C20T * 10     ;// ���[�^���J���P�R�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11C);
	SVP_RCAMOF_P11C		= SV_RCLSTA52_C20T   ;// ���[�^���J���P�R�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11C);
	SVP_RCAMOF_D11C		= SV_RCLS52_C20T / 10     ;// ���[�^���J���P�R�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11C);
	SVP_RCAMON_P11D		= SV_RCLSTA61_C20T   ;// ���[�^���J���P�S�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11D);
	SVP_RCAMON_D11D		= SV_RCLS61_C20T * 10     ;// ���[�^���J���P�S�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11D);
	SVP_RCAMOF_P11D		= SV_RCLSTA62_C20T   ;// ���[�^���J���P�S�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11D);
	SVP_RCAMOF_D11D		= SV_RCLS62_C20T / 10     ;// ���[�^���J���P�S�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11D);
	SVP_RCAMON_P11E		= SV_RCLSTA71_C20T   ;// ���[�^���J���P�T�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11E);
	SVP_RCAMON_D11E		= SV_RCLS71_C20T * 10     ;// ���[�^���J���P�T�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11E);
	SVP_RCAMOF_P11E		= SV_RCLSTA72_C20T   ;// ���[�^���J���P�T�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11E);
	SVP_RCAMOF_D11E		= SV_RCLS72_C20T / 10     ;// ���[�^���J���P�T�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11E);
	SVP_RCAMON_P11F		= SV_RCLSTA81_C20T   ;// ���[�^���J���P�U�@�n�m�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_P11F);
	SVP_RCAMON_D11F		= SV_RCLS81_C20T * 10     ;// ���[�^���J���P�U�@�n�m�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMON_D11F);
	SVP_RCAMOF_P11F		= SV_RCLSTA82_C20T   ;// ���[�^���J���P�U�@�n�e�e�H���@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_P11F);
	SVP_RCAMOF_D11F		= SV_RCLS82_C20T / 10     ;// ���[�^���J���P�U�@�n�e�e�p�x�@�^�C�}�d�l�@2016/11/14
	DPB_SEND_2B(&SVP_RCAMOF_D11F);

}
/****************************************************************************/
