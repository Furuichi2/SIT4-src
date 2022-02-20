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
#include	"cm_equ1.h"								//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"

/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SEQ	(void)
{
	SEQ_PAR_031		= SEQ_031_SV;				/* ������H�ݒ�V�[�P���X�R�P	*/
	SEQ_PAR_032		= SEQ_032_SV;				/* ������H�ݒ�V�[�P���X�R�Q	*/
//	SEQ_PAR_033		= SEQ_033_SV;				/* ������H�ݒ�V�[�P���X�R�R	*/
	SEQ_PAR_034		= SEQ_034_SV;				/* ������H�ݒ�V�[�P���X�R�S	*/
//	SEQ_PAR_035		= SEQ_035_SV;				/* ������H�ݒ�V�[�P���X�R�T	*/
	SEQ_PAR_036		= SEQ_036_SV;				/* ������H�ݒ�V�[�P���X�R�U	*/
	SEQ_PAR_037		= SEQ_037_SV;				/* ������H�ݒ�V�[�P���X�R�V	*/
	SEQ_PAR_038		= SEQ_038_SV;				/* ������H�ݒ�V�[�P���X�R�W	*/
	SEQ_PAR_039		= SEQ_039_SV;				/* ������H�ݒ�V�[�P���X�R�X	*/

	SEQ_PAR_040		= SEQ_040_SV;				/* ������H�ݒ�V�[�P���X�S�O	*/
	SEQ_PAR_041		= (SEQ_041_SV & 0xFCFC);	/* ������H�ݒ�V�[�P���X�S�P	*/
	SEQ_PAR_042		= (SEQ_042_SV & 0xFCFC);	/* ������H�ݒ�V�[�P���X�S�Q	*/
	SEQ_PAR_043		= (SEQ_043_SV & 0xFCFC);	/* ������H�ݒ�V�[�P���X�S�R	*/
	SEQ_PAR_044		= (SEQ_044_SV & 0xBFBC);	/* ������H�ݒ�V�[�P���X�S�S	*/
	SEQ_PAR_045		= (SEQ_045_SV & 0xBFFC);	/* ������H�ݒ�V�[�P���X�S�T	*/
	SEQ_PAR_046		= (SEQ_046_SV & 0xFCFC);	/* ������H�ݒ�V�[�P���X�S�U	*/
	SEQ_PAR_047		= SEQ_047_SV;				/* ������H�ݒ�V�[�P���X�S�V	*/
	SEQ_PAR_048		= SEQ_048_SV;				/* ������H�ݒ�V�[�P���X�S�W	*/
	SEQ_PAR_049		= SEQ_049_SV;				/* ������H�ݒ�V�[�P���X�S�X	*/

//V04 	SEQ_PAR_050		= SEQ_050_SV;				/* ������H�ݒ�V�[�P���X�T�O	*/
//V04 	SVP_MRTION_SEL1	= SEQ_050_SV;				/* ������H�ݒ�V�[�P���X�T�O	*/
//V06m	SEQ_PAR_050		= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* ������H�ݒ�V�[�P���X�T�O	*/
//V06m	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0x0800) | (SEQ_050_SV & 0xF7FF);				/* ������H�ݒ�V�[�P���X�T�O	*/
	SEQ_PAR_050		= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* ������H�ݒ�V�[�P���X�T�O	*/
	SVP_MRTION_SEL1	= (SEQ_PAR_050 & 0xf800) | (SEQ_050_SV & 0x07FF);				/* ������H�ݒ�V�[�P���X�T�O	*/


//	SEQ_PAR_051		= SEQ_051_SV;			/* ������H�ݒ�V�[�P���X�T�P	*/
//	SEQ_PAR_052		= SEQ_052_SV;			/* ������H�ݒ�V�[�P���X�T�Q	*/
//	SEQ_PAR_053		= SEQ_053_SV;			/* ������H�ݒ�V�[�P���X�T�R	*/
//	SEQ_PAR_054		= SEQ_054_SV;			/* ������H�ݒ�V�[�P���X�T�S	*/
//	SEQ_PAR_055		= SEQ_055_SV;			/* ������H�ݒ�V�[�P���X�T�T	*/

	SEQ_PAR_056		= SEQ_056_SV;			/* ������H�ݒ�V�[�P���X�T�U	*/	//V01v
	SEQ_PAR_057		= SEQ_057_SV;			/* ������H�ݒ�V�[�P���X�T�V	*/	//V05o

//	SEQ_PAR_058		= SEQ_058_SV;			/* ������H�ݒ�V�[�P���X�T�W	*/
//	SEQ_PAR_059		= SEQ_059_SV;			/* ������H�ݒ�V�[�P���X�T�X	*/
//
//	SEQ_PAR_060		= SEQ_060_SV;			/* ������H�ݒ�V�[�P���X�U�O	*/
//	SEQ_PAR_061		= SEQ_061_SV;			/* ������H�ݒ�V�[�P���X�U�P	*/
//	SEQ_PAR_062		= SEQ_062_SV;			/* ������H�ݒ�V�[�P���X�U�Q	*/
//	SEQ_PAR_063		= SEQ_063_SV;			/* ������H�ݒ�V�[�P���X�U�R	*/
//	SEQ_PAR_064		= SEQ_064_SV;			/* ������H�ݒ�V�[�P���X�U�S	*/
//	SEQ_PAR_065		= SEQ_065_SV;			/* ������H�ݒ�V�[�P���X�U�T	*/
//	SEQ_PAR_066		= SEQ_066_SV;			/* ������H�ݒ�V�[�P���X�U�U	*/
//	SEQ_PAR_067		= SEQ_067_SV;			/* ������H�ݒ�V�[�P���X�U�V	*/
//	SEQ_PAR_068		= SEQ_068_SV;			/* ������H�ݒ�V�[�P���X�U�W	*/
//	SEQ_PAR_069		= SEQ_069_SV;			/* ������H�ݒ�V�[�P���X�U�X	*/
//
//	SEQ_PAR_070		= SEQ_070_SV;			/* ������H�ݒ�V�[�P���X�V�O	*/
//	SEQ_PAR_071		= SEQ_071_SV;			/* ������H�ݒ�V�[�P���X�V�P	*/
//	SEQ_PAR_072		= SEQ_072_SV;			/* ������H�ݒ�V�[�P���X�V�Q	*/
//	SEQ_PAR_073		= SEQ_073_SV;			/* ������H�ݒ�V�[�P���X�V�R	*/
//	SEQ_PAR_074		= SEQ_074_SV;			/* ������H�ݒ�V�[�P���X�V�S	*/
//	SEQ_PAR_075		= SEQ_075_SV;			/* ������H�ݒ�V�[�P���X�V�T	*/
//	SEQ_PAR_076		= SEQ_076_SV;			/* ������H�ݒ�V�[�P���X�V�U	*/
//	SEQ_PAR_077		= SEQ_077_SV;			/* ������H�ݒ�V�[�P���X�V�V	*/
//	SEQ_PAR_078		= SEQ_078_SV;			/* ������H�ݒ�V�[�P���X�V�W	*/
//	SEQ_PAR_079		= SEQ_079_SV;			/* ������H�ݒ�V�[�P���X�V�X	*/

	SEQ_PAR_080	= SV_TIMER1_A1;					//�����^�C�}�P
	SEQ_PAR_081	= SV_TIMER2_A1;					//�����^�C�}�Q
	SEQ_PAR_082	= SV_TIMER3_A1;					//�����^�C�}�R
	SEQ_PAR_083	= SV_TIMER4_A1;					//�O���^�C�}	V05r

	SEQ_PAR_088	= SV_COUNT1_A1;					//�����J�E���^�P
	SEQ_PAR_089	= SV_COUNT2_A1;					//�����J�E���^�Q
	SEQ_PAR_090	= SV_COUNT3_A1;					//�����J�E���^�R

//V01v:�ǉ�(�����ݸމ�ʂ̐ݒ�l�A�Ƃ肠�������ݽ�ƈꏏ�ɓ]������B)
	SVP_SMPSTR_KAJ	= SV_SMPSTR_KAJ;			// �����ݸށ@�ضމ׏d
	SVP_SMPSTR_AGL	= SV_SMPSTR_AGL;			//  �����ݸށ@�ضފp�x
	SVP_SMPSTR_FUK	= SV_SMPSTR_FUK;			//  �����ݸށ@�ضޕ��ח�
	SVP_SMPSTR_SEH	= SV_SMPSTR_SEH;			//  �����ݸށ@�ض޼��ݽ�i��ʱ��ڽ�j
	SVP_SMPSTR_SQL	= SV_SMPSTR_SQL;			//  �����ݸށ@�ض޼��ݽ�i���ʱ��ڽ�j
	SVP_SMPMAX_CNT	= SV_SMPMAX_CNT;			//  �����ݸށ@�ő��
	SVP_SMPTRG_CNT	= SV_SMPTRG_CNT;			//  �����ݸށ@����ضތ�
	SVP_SMPCYC_TIM	= SV_SMPCYC_TIM;			//  �����ݸށ@����

//V01z:�ǉ�(�����ݸމ�ʂ̐ݒ�l�A�Ƃ肠�������ݽ�ƈꏏ�ɓ]������B)
	SVP_SMP_CNT	= SV_SMP_CNT;				//  �����ݸގ��W�`���@��
	SVP_TRD_CNT	= SV_TRD_CNT;				//  ����ގ��W�`���@��

//V05o:�ǉ�(�����ݸސݒ��ʁA����ސݒ��ʂ̐ݒ�l�A�Ƃ肠�������ݽ�ƈꏏ�ɓ]������B)
	SVP_SMPTRG_CNT1	= SV_SMPTRG_CNT1;			//  �����ݸށ@����ضތ��iSIT�p�j
	SVP_TRDCSR_RNAU	= cnv_inch_mm(SV_TRDCSR_RNAU, 0);	/* �ײ�ޏ�����o�ʒu	*/
	SVP_TRDCSR_RNAD	= cnv_inch_mm(SV_TRDCSR_RNAD, 0);	/* �ײ�ޏ�����o�ʒu	*/ 

//V05r:�ǉ�(���U�@�\�ݒ��ʁA�Ƃ肠�������ݽ�ƈꏏ�ɓ]������B)
	SVP_MAX_KJYU	= SV_MAXKA2_A24;		//�ő�׏d�ݒ�(��߼�݂ɂ����Ȃ�)
	SVP_VIB_KJYU_TTL= SV_KASIN_KAJ;			//vibration(�U��)�׏d

}
/****************************************************************************/
