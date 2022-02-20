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
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_wk_ext.h"

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		GMN_PAR020;


/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SRV	(void)
{
	S4b		ofs;

	SVP_RNADIR_SEL1		= SV_RNADIR_SEL1;				/* �Ʊ�ݻ�ɐ�			*/
	SVP_INCDIR_SEL1		= SV_INCDIR_SEL1;				/* PG�ɐ�				*/
	SVP_INCPLS_1REV		= SV_INCPLS_1REV;				/* PG1��]��ٽ�I��		*/
	SVP_INCPLS_HOSN		= SV_INCPLS_HOSN;				/* PG�␳N Ӱ�N��		*/
	SVP_INCPLS_HOSM		= SV_INCPLS_HOSM;				/* PG�␳M ��ݸ�pM		*/
	SVP_MOTRPM_MAXM		= SV_MOTRPM_MAXM;				/* Ӱ��ő��]��		*/
	SVP_MOTMAX_FREQ		= SV_MOTMAX_FREQ;				/* Ӱ��ő�w�ߎ��g��	*/
//2002-10-16
//	SVP_RNAORG_POS1		= SV_RNAORG_POS1;				/* �@�B���_����			*/
//	SVP_RNAPOS_MAXP		= SV_RNAPOS_MAXP;				/* �@�B���				*/
//	SVP_RNAPOS_MINP		= SV_RNAPOS_MINP;				/* �@�B����				*/
	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* �@�B���_����			*/

//V06n
//	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV_RNAPOS_MAXP, 2);	/* �@�B���				*/
//	SVP_RNAPOS_MINP	= cnv_inch_mm(SV_RNAPOS_MINP, 2);	/* �@�B����				*/
	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV0_RNAPOS_MAXO, 2);	/* �@�B���				*/
	SVP_RNAPOS_MINP	= cnv_inch_mm(SV0_RNAPOS_MINO, 2);	/* �@�B����				*/

//V01 (MOV)	SVP_DNDINC_SPD1		= SV_DNDINC_SPD1;				/* �i�摬�x				*/
	SVP_UPAREA_SPD1		= SV_UPAREA_SPD1;				/* �ҋ@�_���A���x		*/
	SVP_STDINC_SPD1		= SV_STDINC_SPD1;				/* �������x				*/
	SVP_REVDAT_SPD1		= SV_REVDAT_SPD1;				/* �\�����x�P			*/
	SVP_REVDAT_SPD2		= SV_REVDAT_SPD2;				/* �\�����x�Q			*/
	SVP_REVDAT_SPD3		= SV_REVDAT_SPD3;				/* �\�����x�R			*/
	SVP_TEPDAT_SPD1		= SV_TEPDAT_SPD1;				/* �蓮��ٻ���x			*/
	SVP_TEPLAT_DAT1		= SV_TEPLAT_DAT1;				/* �蓮��ٻ��{��		*/
	SVP_TEPLAT_DAT2		= SV_TEPLAT_DAT2;				/* �蓮��ٻ���{��		*/

	SVP_INCPOS_KP01		= SV_INCPOS_KP01;				/* PG�ʒu���޲�		*/
	SVP_RNAPOS_KP01		= SV_RNAPOS_KP01;				/* �Ʊ�ʒu���޲�		*/
	SVP_ACCLAT_TIM1		= SV_ACCLAT__TIM1;				/* ����������			*/
	SVP_SSCURV_TIM1		= SV_SSCURV_TIM1;				/* �r������				*/
//2002-10-16
//	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* �㎀�_���߼޼��		*/
//	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* �����_���߼޼��		*/
//	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* �ڕW�ʒu���߼޼��	*/
/* V00m */
//	SVP_UPAREA_INP1	= cnv_inch_mm(SV_UPAREA_INP1, 2);	/* �㎀�_���߼޼��		*/
//	SVP_DNAREA_INP1	= cnv_inch_mm(SV_DNAREA_INP1, 2);	/* �����_���߼޼��		*/
//	SVP_OBJARA_INP1	= cnv_inch_mm(SV_OBJARA_INP1, 2);	/* �ڕW�ʒu���߼޼��	*/
	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* �\��		*/
	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* �@�B�L�їʌ��E		*/
	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* ��]�����ݲ��߼޼��	*/

	SVP_INPPOS_TIM1		= SV_INPPOS_TIM1;				/* ���߼޼����������	*/

//2002-10-16
//	SVP_ARACHK_LNG1		= SV_ARACHK_LNG1;				/* ��^�����_�ʉߔ����	*/
	SVP_ARACHK_LNG1	= cnv_inch_mm(SV_ARACHK_LNG1, 2);	/* ��^�����_�ʉߔ����	*/
	SVP_UPAREA_DIG1		= SV_UPAREA_DIG1; 				/* ��]���ҋ@�_(�㎀�_)	*/

	SVP_UPAREA_JUDG		= SV_UPAREA_JUDG;				/* �㎀�_����͈�		*/
	SVP_DNAREA_JUDG		= SV_DNAREA_JUDG;				/* ���]�ݒ�s�͈�		*/
//2002-10-16
//2002-08-21:�ǉ�
//	SVP_RNA_STLORK		= SV_RNA_STLORK;				//�X�g���[�N�ݒ�(4)
	SVP_RNA_STLORK	= cnv_inch_mm(SV_RNA_STLORK, 2);	//�X�g���[�N�ݒ�(4)
	SVP_OUTPLS_HOSA		= SV_OUTPLS_HOSA;				//�o����ٽ�␳A(2)
	SVP_OUTPLS_HOSB		= SV_OUTPLS_HOSB;				//�o����ٽ�␳B(2)
	SVP_UPHOLD_DIG		= SV_UPHOLD_DIG;				//�㏸ΰ��ފp�x(2)
	SVP_MACINE_SEL1		= SV_MACINE_SEL1;				//�\���i�@��I���P�j(2)

	SVP_INCHEN_ELNG		= SV_INCHEN_ELNG;				/* PG�΍��ُ핝			*/
	SVP_INCENC_ELNG		= SV_INCENC_ELNG;				/* PG-ENC��v��			*/
//2002-10-16
//	SVP_INCRNA_ELNG		= SV_INCRNA_ELNG;				/* PG-�Ʊ��v��			*/
	SVP_INCRNA_ELNG	= cnv_inch_mm(SV_INCRNA_ELNG, 2);	/* PG-�Ʊ��v��			*/
	SVP_INCSTP_ELNG		= SV_INCSTP_ELNG;				/* PG��~�ُ��			*/
//2002-10-16
//	SVP_RNASTP_ELNG		= SV_RNASTP_ELNG;				/* �Ʊ��~�ُ��		*/
	SVP_RNASTP_ELNG	= cnv_inch_mm(SV_RNASTP_ELNG, 2);	/* �Ʊ��~�ُ��		*/
	SVP_INCREV_ELNG		= SV_INCREV_ELNG;				/* PG�t�]�ُ��			*/
//2002-10-16
//	SVP_RNAREV_ELNG		= SV_RNAREV_ELNG;				/* �Ʊ�t�]�ُ��		*/
//	SVP_DAIHAI_LNG1		= SV_DAIHAI_LNG1;				/* �޲ʲĕ␳��r�l(��)	*/
//	SVP_DAIHAI_LNG2		= SV_DAIHAI_LNG2;				/* �޲ʲĕ␳��r�l(��)	*/
//	SVP_DAIHAI_LNG3		= SV_DAIHAI_LNG3;				/* �޲ʲĕ␳��r�l(��)	*/
	SVP_RNAREV_ELNG	= cnv_inch_mm(SV_RNAREV_ELNG, 2);	/* �Ʊ�t�]�ُ��		*/

//V06n
//	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV_DAIHAI_LNG1, 2);	/* �޲ʲĕ␳��r�l(��)	*/
//	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV_DAIHAI_LNG2, 2);	/* �޲ʲĕ␳��r�l(��)	*/
	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV0_DAIHAI_LNG1O, 2);	/* �޲ʲĕ␳��r�l(��)	*/
	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV0_DAIHAI_LNG2O, 2);	/* �޲ʲĕ␳��r�l(��)	*/

	SVP_DAIHAI_LNG3	= cnv_inch_mm(SV_DAIHAI_LNG3, 2);	/* �޲ʲĕ␳��r�l(��)	*/

	SVP_AMPERR_VLT1		= SV_AMPERR_VLT1;				/* �ߕ��דd��1			*/
	SVP_AMPERR_TIM1		= SV_AMPERR_TIM1;				/* �ߕ��׎���1			*/
	SVP_AMPERR_VLT2		= SV_AMPERR_VLT2;				/* �ߕ��דd��2			*/
	SVP_AMPERR_TIM2		= SV_AMPERR_TIM2;				/* �ߕ��׎���2			*/
	SVP_AMPERR_VLT3		= SV_AMPERR_VLT3;				/* �ߕ��דd��3			*/
	SVP_AMPERR_TIM3		= SV_AMPERR_TIM3;				/* �ߕ��׎���3			*/

//2002-08-08:�ǉ�
//	SVP_BREAK_DIG		= SV_BRDIG_C1 * 10;				//��ڰ��p�x   0.1�x
	SVP_BREAK_DIG		= SV_BRDIG_C1;					//��ڰ��p�x   0.1�x
	SVP_BREAK_TIM1		= SV_BRTIME_C1;					//�u���[�L�^�C�}�ݒ�

	SVP_CNT_CNT			= SV_RNZRPM_A12;				//�A����]�ݒ�l
	SVP_CNT_TIM			= SV_RNZTIM_A12;				//�A���^�C�}�ݒ�l
	SVP_WT_DIG1			= SV_TAIKI1_A12;				//�ҋ@�_�I��1
	SVP_WT_DIG2			= SV_TAIKI2_A12;				//�ҋ@�_�I��2
	SVP_WT_DIG3			= SV_TAIKI3_A12;				//�ҋ@�_�I��3
	SVP_MOTWT_TIM		= SV_HOSTIM_A12;				//�N���ۏ؎���
	SVP_PSMOD_SEL		= SV_PSDIMD_A1;					//PSID�@Ӱ�ޑI��

	/* V00m */
	SVP_NEG_OFS_LNG		= SV_NEG_OFS_LNG;				//���]��������
	SVP_AMP100P_VLT		= SV_AMP100P_VLT;				//�ߕ������100%�d��

	/* V01v */
	SVP_LSAABN_AGL1		= SV_LSAABN_AGL1;				//LSA�ُ팟�m�̊p�x1
	SVP_LSAABN_AGL2		= SV_LSAABN_AGL2;				//LSA�ُ팟�m�̊p�x2
	SVP_PLSALO_PLS		= SV_PLSALO_PLS;				//�p���T�{����
	SVP_PLSAHI_PLS		= SV_PLSAHI_PLS;				//�p���T�{����
	SVP_MOADR0_SQH		= SV_MOADR0_SQH;				// ���j�^�A�h���X�O�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR0_SQL		= SV_MOADR0_SQL;				// ���j�^�A�h���X�O�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR1_SQH		= SV_MOADR1_SQH;				// ���j�^�A�h���X�P�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR1_SQL		= SV_MOADR1_SQL;				// ���j�^�A�h���X�P�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR2_SQH		= SV_MOADR2_SQH;				// ���j�^�A�h���X�Q�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR2_SQL		= SV_MOADR2_SQL;				// ���j�^�A�h���X�Q�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR3_SQH		= SV_MOADR3_SQH;				// ���j�^�A�h���X�R�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR3_SQL		= SV_MOADR3_SQL;				// ���j�^�A�h���X�R�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR4_SQH		= SV_MOADR4_SQH;				// ���j�^�A�h���X�S�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR4_SQL		= SV_MOADR4_SQL;				// ���j�^�A�h���X�S�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR5_SQH		= SV_MOADR5_SQH;				// ���j�^�A�h���X�T�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR5_SQL		= SV_MOADR5_SQL;				// ���j�^�A�h���X�T�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR6_SQH		= SV_MOADR6_SQH;				// ���j�^�A�h���X�U�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR6_SQL		= SV_MOADR6_SQL;				// ���j�^�A�h���X�U�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR7_SQH		= SV_MOADR7_SQH;				// ���j�^�A�h���X�V�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR7_SQL		= SV_MOADR7_SQL;				// ���j�^�A�h���X�V�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR8_SQH		= SV_MOADR8_SQH;				// ���j�^�A�h���X�W�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR8_SQL		= SV_MOADR8_SQL;				// ���j�^�A�h���X�W�@���ݽ���ʁ@V01v�@060713
	SVP_MOADR9_SQH		= SV_MOADR9_SQH;				// ���j�^�A�h���X�X�@���ݽ��ʁ@V01v�@060713
	SVP_MOADR9_SQL		= SV_MOADR9_SQL;				// ���j�^�A�h���X�X�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRA_SQH		= SV_MOADRA_SQH;				// ���j�^�A�h���X�P�O�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRA_SQL		= SV_MOADRA_SQL;				// ���j�^�A�h���X�P�O�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRB_SQH		= SV_MOADRB_SQH;				// ���j�^�A�h���X�P�P�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRB_SQL		= SV_MOADRB_SQL;				// ���j�^�A�h���X�P�P�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRC_SQH		= SV_MOADRC_SQH;				// ���j�^�A�h���X�P�Q�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRC_SQL		= SV_MOADRC_SQL;				// ���j�^�A�h���X�P�Q�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRD_SQH		= SV_MOADRD_SQH;				// ���j�^�A�h���X�P�R�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRD_SQL		= SV_MOADRD_SQL;				// ���j�^�A�h���X�P�R�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRE_SQH		= SV_MOADRE_SQH;				// ���j�^�A�h���X�P�S�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRE_SQL		= SV_MOADRE_SQL;				// ���j�^�A�h���X�P�S�@���ݽ���ʁ@V01v�@060713
	SVP_MOADRF_SQH		= SV_MOADRF_SQH;				// ���j�^�A�h���X�P�T�@���ݽ��ʁ@V01v�@060713
	SVP_MOADRF_SQL		= SV_MOADRF_SQL;				// ���j�^�A�h���X�P�T�@���ݽ���ʁ@V01v�@060713

	/* COP2�֌W */
	SVP_ORGSOK_PLS		= SV_ORGSOK_PLS;		//���_������ٽ
	SVP_ORGCAL_DAT1		= SV_ORGCAL_DAT1;		//���Z�W��1
	SVP_ORGCAL_DAT2		= SV_ORGCAL_DAT2;		//���Z�W��2
	SVP_ORGCAL_DAT3		= SV_ORGCAL_DAT3;		//���Z�W��3
	SVP_ORGCAL_DAT4		= SV_ORGCAL_DAT4;		//���Z�W��4
	SVP_ORGCAL_DAT5		= SV_ORGCAL_DAT5;		//���Z�W��5
	SVP_ORGCAL_DAT6		= SV_ORGCAL_DAT6;		//���Z�W��6
	SVP_ORGSTRK_LEN1	= SV_ORGSTRK_LEN1;		//��۰�1
	SVP_ORGSTRK_LEN2	= SV_ORGSTRK_LEN2;		//��۰�2
	SVP_RNAORGMEM_LEG1	= SV_RNAORGMEM_LEG1;	//�Ʊ���_1���L��
////	SVP_RNAORG_PLS1		= SV_RNAORG_PLS1;		//�ޯ����ߎ���
	SVP_RNAORGMEM_LEG2	= SV_RNAORGMEM_LEG2;	//�Ʊ���_2���L��
////	SVP_RNAORG_PLS2		= SV_RNAORG_PLS2;		//�ޯ����ߎ���
////	SVP_RNAORG_SIN1		= SV_RNAORG_SIN1;		//�ޯ����ߎ�������
////	SVP_RNAORG_SIN2		= SV_RNAORG_SIN2;		//�ޯ����ߎ�������
	SVP_ORGRUP_DEG		= SV_ORGRUP_DEG;		//���_�E��ԏ�
	SVP_ORGRDN_DEG		= SV_ORGRDN_DEG;		//���_�E��ԉ�
	SVP_ORGLUP_DEG		= SV_ORGLUP_DEG;		//���_����ԏ�
	SVP_ORGLDN_DEG		= SV_ORGLDN_DEG;		//���_����ԉ�
	SVP_ORGMEM_DEG1		= SV_ORGMEM_DEG1;		//�p�x1��
	SVP_ORGMEM_DEGS1	= SV_ORGMEM_DEGS1;		//�p�x1���@ON/OFF
	SVP_ORGMEM_DEG2		= SV_ORGMEM_DEG2;		//�p�x2��
	SVP_ORGMEM_DEGS2	= SV_ORGMEM_DEGS2;		//�p�x2���@ON/OFF
	SVP_ORGMPL_SEL1		= SV_ORGMPL_SEL1;		//����ٻ�I��1���@ON/OFF
	SVP_ORGMPL_SEL2		= SV_ORGMPL_SEL2;		//����ٻ�I��2���@ON/OFF
	SVP_HOSRAG_PLS1		= SV_HOSRAG_PLS1;		//���ԕ␳�͈͂P
	SVP_HOSRAG_PLS2		= SV_HOSRAG_PLS2;		//���ԕ␳�͈͂Q
	SVP_HOSEI_SPD		= SV_HOSEI_SPD;			//�␳���x
	SVP_MANSAM_LEN		= SV_MANSAM_LEN;		//�蓮������
	SVP_DANSAM_LEN		= SV_DANSAM_LEN;		//�i�掚����
	SVP_RUNSAMER_LEN1	= SV_RUNSAMER_LEN1;		//�^�]�����ُ�P
	SVP_RUNSAMER_LEN2	= SV_RUNSAMER_LEN2;		//�^�]�����ُ�Q
	SVP_MANSAMER_PLS	= SV_MANSAMER_PLS;		//�蓮�����ُ�
	SVP_RUNSAMER_PLS	= SV_RUNSAMER_PLS;		//�^�]�����ُ�
	SVP_RNADIR_SEL2		= SV_RNADIR_SEL2;		/* �Ʊ�ݻ�ɐ�			*/
	SVP_ORGMEM_DEG1A	= SV_ORGMEM_DEG1A;		//�p�x1��
	SVP_ORGMEM_DEG2A	= SV_ORGMEM_DEG2A;		//�p�x2��

//V05c
	SVP_FCLS_STR_DEG	= SV_FCLS_STR_DEG	;//�ٸۊJ�n�p�x
	SVP_FCLS_STR_HENS	= SV_FCLS_STR_HENS	;//�ٸۊJ�n�΍�
	SVP_FCLS_ZIKI_SPD1	= SV_FCLS_ZIKI_SPD1	;//�ٸێ��N�����x1
	SVP_FCLS_ZIKI_SPD2	= SV_FCLS_ZIKI_SPD2	;//�ٸێ��N�����x2
	SVP_SYNC_ERR_DEGA	= SV_SYNC_ERR_DEGA	;//�����ُ�̈�p�xA
	SVP_SYNC_ERR_DEGB	= SV_SYNC_ERR_DEGB	;//�����ُ�̈�p�xB
	SVP_SYNC_ERR_DEGC	= SV_SYNC_ERR_DEGC	;//�����ُ�̈�p�xC
	SVP_SYNC_ERR_DEGD	= SV_SYNC_ERR_DEGD	;//�����ُ�̈�p�xD
	SVP_SYNC_ERR_RNAA	= SV_SYNC_ERR_RNAA	;//�Ʊ�����ُ�A
	SVP_SYNC_ERR_RNAB	= SV_SYNC_ERR_RNAB	;//�Ʊ�����ُ�B
	SVP_SYNC_ERR_RNAC	= SV_SYNC_ERR_RNAC	;//�Ʊ�����ُ�C
	SVP_SYNC_ERR_RNAD	= SV_SYNC_ERR_RNAD	;//�Ʊ�����ُ�D
	SVP_SYNC_ERR_PGA	= SV_SYNC_ERR_PGA	;//PG�����ُ�A
	SVP_SYNC_ERR_PGB	= SV_SYNC_ERR_PGB	;//PG�����ُ�B
	SVP_SYNC_ERR_PGC	= SV_SYNC_ERR_PGC	;//PG�����ُ�C
	SVP_SYNC_ERR_PGD	= SV_SYNC_ERR_PGD	;//PG�����ُ�D

//V05r
	SVP_BREAK_DIG_RAT	= SV_BRDIG_C2;		//��ڰ��p�x   ����
	SVP_BREAK_TIM_RAT	= SV_BRTIME_C2;		//�u���[�L�^�C�}	����

//V06
	SVP_EP_VOF		= SV_SRVPAR_B0;		// �T�[�{�p�����[�^B0�@�@�d�͗p�̾��
	SVP_EP_VMX		= SV_SRVPAR_B1;		// �T�[�{�p�����[�^B1�@�@�d�͗p�ő�l
	SVP_EP_TRQ		= SV_SRVPAR_B2;		// �T�[�{�p�����[�^B2�@�@�d�͗p�ٸ�l
	SVP_EP_LTM		= SV_SRVPAR_B3;		// �T�[�{�p�����[�^B3�@�@�ٸ���x�ꎞ��
	SVP_EP_K1		= SV_SRVPAR_B4;		// �T�[�{�p�����[�^B4�@�@�����W��A
	SVP_EP_K2		= SV_SRVPAR_B5;		// �T�[�{�p�����[�^B5�@�@�����W��B
	SVP_EP_ADJSIN	= SV_SRVPAR_B6;		// �T�[�{�p�����[�^B6�@�@�����d�͕���
	SVP_EP_ADJVAL	= SV_SRVPAR_B7;		// �T�[�{�p�����[�^B7�@�@�����d��
	SVP_ECOM_BASE	= SV_SRVPAR_B8;     // �T�[�{�p�����[�^B8�@�@�G�R���[�^��l
	SVP_ECOM_SCAL	= SV_SRVPAR_B9;     // �T�[�{�p�����[�^B9�@�@�G�R���[�^�X�P�[��
	SVP_MOTRPM_MAXP	= SV_MOTRPM_MAXP;	// �T�[�{�p�����[�^BA.���[�^�ő��]��
	SVP_ACCLAT_TIMP	= SV_ACCLAT__TIMP;	// �T�[�{�p�����[�^BB.����������

//V06d
	if (SEQ_PAR_113 & cBIT10) {			//�{�I�t�Z�b�g		2013/09/27
		SVP_VOLST_L	= SV_SRVPAR_BC+(GMN_PAR020*100);		// �T�[�{�p�����[�^BC�@�@�d�͗p�̾��
	}
	else if (SEQ_PAR_113 & cBIT11) {	//�|�I�t�Z�b�g
		ofs = SV_SRVPAR_BC - (GMN_PAR020*100);
		if (ofs<0) {
			ofs = 0;
		}
		SVP_VOLST_L	= ofs;									// �T�[�{�p�����[�^BC�@�@�d�͗p�̾��
	}
	else {
		SVP_VOLST_L	= SV_SRVPAR_BC;							// �T�[�{�p�����[�^BC�@�@�d�͗p�̾��
	}

	SVP_SLIDE_S		= SV_SRVPAR_BD;		// �T�[�{�p�����[�^BD�@�@�d�͗p�ő�l
	SVP_RAD			= SV_SRVPAR_BE;		// �T�[�{�p�����[�^BE�@�@�d�͗p�ٸ�l
	SVP_ORGREV_AGL	= SV_SRVPAR_BF;		// �T�[�{�p�����[�^BF�@�@�ٸ���x�ꎞ��
	SVP_ORGFWD_AGL	= SV_SRVPAR_BG;		// �T�[�{�p�����[�^BG�@�@�����W��A

//V06f
	SVP_RISE_ZWID	= (U2b)SV_SRVPAR_BH;		// �T�[�{�p�����[�^BH�@�@�㏸�Ď���ە�
	SVP_RISE_CMP1	= (U2b)SV_SRVPAR_BI;		// �T�[�{�p�����[�^BI�@�@�㏸�Ď���r1
	SVP_RISE_CMP2	= (U2b)SV_SRVPAR_BJ;		// �T�[�{�p�����[�^BJ�@�@�㏸�Ď���r2
	SVP_RISE_CMP3	= (U2b)SV_SRVPAR_BK;		// �T�[�{�p�����[�^BK�@�@�㏸�Ď���r�\��
	SVP_RISE_DLY1	= (U2b)SV_SRVPAR_BL;		// �T�[�{�p�����[�^BL�@�@�Ď��x��1
	SVP_RISE_DLY2	= (U2b)SV_SRVPAR_BM;		// �T�[�{�p�����[�^BM�@�@�Ď��x��2

}
/****************************************************************************/
