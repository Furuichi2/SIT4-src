/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�c�o�q�`�l �� �e�q�`�l	�f�[�^�]������				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_def.h"							//�e��̋��ʒ�`
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
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_GEN	(void)
{
//2002-10-16
//	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* �@�B���_����			*/
//2014/12/11	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* �@�B���_����			*/
	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* �@�B���_���� mm�Œ�	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORG_POS1);


	SVP_RNAORGMEM_LEG1	= cnv_inch_mm(SV_RNAORGMEM_LEG1, 2);	/* �@�B���_����	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG1);
	SVP_RNAORGMEM_LEG2	= cnv_inch_mm(SV_RNAORGMEM_LEG2, 2);	/* �@�B���_����	COP2	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORGMEM_LEG2);


	if(DEB_WORD_FLG1 == 0x05a)		/* V01n_b */
	{
		PV_DEB_WORD_WK1 = PV_DEB_WORD_WK1 + 1;
	}
	DEB_WORD_FLG1 = 0x05a;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_GET_SENS		(void)
{
	/* ���j�A�Z���T�f�[�^�����l���e�q�`�l�ɕۑ�����B*/

	PV_NOW_POS		= PVP_RENIA_POSI0;				/* ���j�A�Z���T���݈ʒu	*/
//	PV_NOW_POS		= PVP_NOW_POSI000;				/* ���݈ʒu	 			*/
	PV_ENCOD_BCD	= PVP_NOW_ANGLE00;				/* ���݊p�x				*/
	PV_CYCLE_TIME	= PVP_CYCLE_TIME0;				/* �T�C�N������			*/

	PV_RNAORG_PLS1	= PVP_RNAORG_PLS1;				/* �Ʊ��ʒu��ٽ		*/

//2002-10-10:�ǉ�
	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* �Ʊ��ʒu��ٽ		*/


	PV_BAKORG_PLS1	= PVP_BAKORG_PLS1;				/* �Ʊ��ʒu��ٽ	COP2	*/
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* �Ʊ��ʒu��ٽ	COP2	*/
	PV_BAKORG_PLS2	= PVP_BAKORG_PLS2;				/* �Ʊ��ʒu��ٽ	COP2	*/
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* �Ʊ��ʒu��ٽ	COP2	*/


	PV_DEB_WORD_WK2 = PV_DEB_WORD_WK2 + 1;			/* V01n_b */
}
/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_BACK_SENS	(void)
{
	/* �e�q�`�l�ɕۑ��������j�A�Z���T�f�[�^���c�o�q�`�l�ɕ�������B*/

	SVB_RNAORG_PLS1	= PV_RNAORG_PLS1;				/* �Ʊ��ʒu��ٽ		*/
	DPB_SEND_4B((U4b *)&SVB_RNAORG_PLS1);

	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* �Ʊ��ʒu��ٽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_BAKORG_PLS2	= PV_BAKORG_PLS2;				/* �Ʊ��ʒu��ٽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS2);
	SVB_BAKORG_PLS1	= PV_BAKORG_PLS1;				/* �Ʊ��ʒu��ٽ	COP2	*/
	DPB_SEND_4B((U4b *)&SVB_BAKORG_PLS1);
	SVB_RENIA_BUP1	= PV_RENIA_BUP1;				//���j�A�X�P�[���o�b�N�A�b�v�p
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP1);
	SVB_RENIA_BUP2	= PV_RENIA_BUP2;				//���j�A�X�P�[���o�b�N�A�b�v�p
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP2);
	SVB_RENIA_BUP3	= PV_RENIA_BUP3;				//���j�A�X�P�[���o�b�N�A�b�v�p
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP3);
	SVB_RENIA_BUP4	= PV_RENIA_BUP4;				//���j�A�X�P�[���o�b�N�A�b�v�p
	DPB_SEND_4B((U4b *)&SVB_RENIA_BUP4);

	SVB_ARA1_KAJ_T2	= PV_ARA1_KAJ_T2;				//�׏d��������		V02a
	DPB_SEND_2B((U2b *)&SVB_ARA1_KAJ_T2);

}
/****************************************************************************/
