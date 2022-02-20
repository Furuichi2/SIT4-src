/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			���Y�̑��상�C������													*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-06-04
*
*************************************************************************************/

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//�Q�ƕϐ���`

/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	GRAPH_INIT(void);				//�O���t�`�揉������
extern	void	GRAPH_DISP(void);				//�O���t�`�揈��

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		GMN_PAR003;						//�A����s�����̖ڕW�p�x��� /* V01e */
extern	UNs		GMN_PAR021;						//�U�qӰ��ݐݒ萧��		/* V06m */
extern	UNs		Key_Data_WK[4];					//V06a
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR077;						//�J��Ԃ��񐔏��								2014/09/08
extern	UNb		LCD_VMON2[6*16*2][PanelWidth];	//2015/01/15
extern	UNs		GMN_PAR083;						//�߂�s�����x�����l							2015/07/03
extern	UNs		GMN_PAR048;						//�׏d����L���^����							2015/09/29
extern	UNs		CB_SYS_PARAM375;				//Ӱ��݉������I��								2016/04/16

/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	dsp_Seisan(void);						//���Y�̊Ǘ�

void	Seisan_sel(void);						//���Y�ݒ�ւ̑J��(��ު��/н̨���)

void	sw34_gamen_01(UNs);						//���Y[��{]��SW3�4�̏���
void	sw56_gamen_01(UNs);						//���Y[��{]��SW5�6�̏���
void	sw56_window_02(UNs);					//���Y[�P�x�ݒ�]��SW5�6�̏���
void	kido_data_set(void);					//�P�x�\�� & �f�[�^�쐬

//void	mmon_taiki_chg(void);					//�ҋ@�p���͕ύX
void	mmon_kaiten_chg(void);					//��]�����ɂ��ݒ�l �؊���
void	mmon_sv_chg(UNs);						//�p�x&�ʒu�̐ݒ�l�ύX
void	mmon_tchk_disp(UNi);					//Ӱ��݉�ʗp���ð��ق�����&�\��
void	mmon_sel_chk(void);						//Ӱ��݂̕����I������
void	mmon_trans_get(void);					//��]�����ɂ���ް��̎擾
void	mmon_trans_put(void);					//��]�����ɂ���ް��̊i�[
void	mmon_spd_in(void);						//���x���~�b�g�l�����
void	mmon_agl_in(void);						//�p�x���~�b�g�l�����

UNl		cnv_mi_mi_sur(UNl);						//�P�ʐؑ�(mm/INCH��mm/INCH)
UNl		cnv_mi_mi(UNl);							//�P�ʐؑ�(mm/INCH��mm/INCH)
UNl		cnv_mm_inch(UNl, UNi);					//�P�ʐؑ�(mm��mm/INCH)
UNl		cnv_inch_mm(UNl, UNi);					//�P�ʐؑ�(mm/INCH��mm)

void	SEI_csr_ichk(void);						//���Y�J�[�\���ʒu������
void	SEI_csr_mng(void);						//���Y[��{]�̐�p�@�J�[�\���ړ��Ǘ�

void	mmon_deg_chg_uphold1(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt);
void	mmon_deg_chg_uphold2(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt);

void	KJ_CHK_MEM_CLR(void);
void	EPM_MEM_CLR(void);

void	SEI_Worker_GET(void);					//���Y�Ǘ��f�[�^�擾		V06c
void	SEI_Worker_SET(void);					//���Y�Ǘ��f�[�^�o�^		V06c
void	SEI_Worker_STP(void);					//���Y�Ǘ���ƏI��			V06c

void	FURIKO_SW_del(void);					//�U�qSW�̕\���^��\��		V06p
void	FURIKO_SW_chk(void);					//�U�qSW�̕\���^��\��		V06p

void	mmon_f_off(UNs t_no);					//��葬�x�ݒ�̃N���A		2014/09/25
void	mmon_pos_kaj_chg(UNs no);				//�����^�׏d�ڕW�؊���		2015/01/15
#if (mot100_test == 1)
void	mmon_step_chg_disp(void);				//�s�����ύX������&�\��
UNs		step_pos_prs_chk(UNs step);				//�w��s���̖ڕW�m�F�i�ʒuor�׏d�j
void	mmon_agl_ovbit_make(void);				//�ڕW�p���I�[�o�[���Ă���s�̃r�b�g�����쐬
void	mmon_spd_ovbit_make(void);				//���x���I�[�o�[���Ă���s�̃r�b�g�����쐬
void	mmon_spd_lmbit_make(void);				//���x���Ⴗ����s�̃r�b�g�����쐬
void	mmon_act_step_bit_make(void);			//���[�V�������s�s���̃r�b�g�����쐬
void	MOT_CHG_REQ(UNs t_no);					//���[�V�����ύX�s���̑��M�v��
void	mmon_deg_chg_uphold100(UNs step, UNs *deg, UNl *pos);
void	step_chg_spd_make(void);				//�ϑ����쐬�i�Oor��j
#endif

/* �����ϐ���` ------------------------------------------------------ */

/* �e�[�u����` ------------------------------------------------------ */
#if (mot100_test == 1)
typedef struct {
	UNs		*DEG1, *DEG2, *DEG3, *DEG4, *DEG5;
	UNl		*POS1, *POS2, *POS3, *POS4, *POS5;
	UNs		*PRS1, *PRS2, *PRS3, *PRS4, *PRS5;
	UNs		*SPD1, *SPD2, *SPD3, *SPD4, *SPD5;
	UNs		*TIM1, *TIM2, *TIM3, *TIM4, *TIM5;
} MOT_PAGE_DAT_TDEF;

const	MOT_PAGE_DAT_TDEF	MOT_PAGE_DAT[20] = {
	{
		/* 1�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_1DANDEG_SRV, &SV_2DANDEG_SRV, &SV_3DANDEG_SRV, &SV_4DANDEG_SRV, &SV_5DANDEG_SRV,		//�p�x
		&SV_1DANPOS_SRV, &SV_2DANPOS_SRV, &SV_3DANPOS_SRV, &SV_4DANPOS_SRV, &SV_5DANPOS_SRV,		//�ʒu
		&SV_1DANPRS_SRV, &SV_2DANPRS_SRV, &SV_3DANPRS_SRV, &SV_4DANPRS_SRV, &SV_5DANPRS_SRV,		//�׏d
		&SV_1DANSPD_SRV, &SV_2DANSPD_SRV, &SV_3DANSPD_SRV, &SV_4DANSPD_SRV, &SV_5DANSPD_SRV,		//���x
		&SV_1DANTIM_SRV, &SV_2DANTIM_SRV, &SV_3DANTIM_SRV, &SV_4DANTIM_SRV, &SV_5DANTIM_SRV			//��~����
	},
	{
		/* 2�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_6DANDEG_SRV, &SV_7DANDEG_SRV, &SV_8DANDEG_SRV, &SV_9DANDEG_SRV, &SV_10DANDEG_SRV,		//�p�x
		&SV_6DANPOS_SRV, &SV_7DANPOS_SRV, &SV_8DANPOS_SRV, &SV_9DANPOS_SRV, &SV_10DANPOS_SRV,		//�ʒu
		&SV_6DANPRS_SRV, &SV_7DANPRS_SRV, &SV_8DANPRS_SRV, &SV_9DANPRS_SRV, &SV_10DANPRS_SRV,		//�׏d
		&SV_6DANSPD_SRV, &SV_7DANSPD_SRV, &SV_8DANSPD_SRV, &SV_9DANSPD_SRV, &SV_10DANSPD_SRV,		//���x
		&SV_6DANTIM_SRV, &SV_7DANTIM_SRV, &SV_8DANTIM_SRV, &SV_9DANTIM_SRV, &SV_10DANTIM_SRV			//��~����
	},
	{
		/* 3�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_11DANDEG_SRV, &SV_12DANDEG_SRV, &SV_13DANDEG_SRV, &SV_14DANDEG_SRV, &SV_15DANDEG_SRV,		//�p�x
		&SV_11DANPOS_SRV, &SV_12DANPOS_SRV, &SV_13DANPOS_SRV, &SV_14DANPOS_SRV, &SV_15DANPOS_SRV,		//�ʒu
		&SV_11DANPRS_SRV, &SV_12DANPRS_SRV, &SV_13DANPRS_SRV, &SV_14DANPRS_SRV, &SV_15DANPRS_SRV,		//�׏d
		&SV_11DANSPD_SRV, &SV_12DANSPD_SRV, &SV_13DANSPD_SRV, &SV_14DANSPD_SRV, &SV_15DANSPD_SRV,		//���x
		&SV_11DANTIM_SRV, &SV_12DANTIM_SRV, &SV_13DANTIM_SRV, &SV_14DANTIM_SRV, &SV_15DANTIM_SRV			//��~����
	},
	{
		/* 4�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_16DANDEG_SRV, &SV_17DANDEG_SRV, &SV_18DANDEG_SRV, &SV_19DANDEG_SRV, &SV_20DANDEG_SRV,		//�p�x
		&SV_16DANPOS_SRV, &SV_17DANPOS_SRV, &SV_18DANPOS_SRV, &SV_19DANPOS_SRV, &SV_20DANPOS_SRV,		//�ʒu
		&SV_16DANPRS_SRV, &SV_17DANPRS_SRV, &SV_18DANPRS_SRV, &SV_19DANPRS_SRV, &SV_20DANPRS_SRV,		//�׏d
		&SV_16DANSPD_SRV, &SV_17DANSPD_SRV, &SV_18DANSPD_SRV, &SV_19DANSPD_SRV, &SV_20DANSPD_SRV,		//���x
		&SV_16DANTIM_SRV, &SV_17DANTIM_SRV, &SV_18DANTIM_SRV, &SV_19DANTIM_SRV, &SV_20DANTIM_SRV			//��~����
	},
	{
		/* 5�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_21DANDEG_SRV, &SV_22DANDEG_SRV, &SV_23DANDEG_SRV, &SV_24DANDEG_SRV, &SV_25DANDEG_SRV,		//�p�x
		&SV_21DANPOS_SRV, &SV_22DANPOS_SRV, &SV_23DANPOS_SRV, &SV_24DANPOS_SRV, &SV_25DANPOS_SRV,		//�ʒu
		&SV_21DANPRS_SRV, &SV_22DANPRS_SRV, &SV_23DANPRS_SRV, &SV_24DANPRS_SRV, &SV_25DANPRS_SRV,		//�׏d
		&SV_21DANSPD_SRV, &SV_22DANSPD_SRV, &SV_23DANSPD_SRV, &SV_24DANSPD_SRV, &SV_25DANSPD_SRV,		//���x
		&SV_21DANTIM_SRV, &SV_22DANTIM_SRV, &SV_23DANTIM_SRV, &SV_24DANTIM_SRV, &SV_25DANTIM_SRV			//��~����
	},
	{
		/* 6�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_26DANDEG_SRV, &SV_27DANDEG_SRV, &SV_28DANDEG_SRV, &SV_29DANDEG_SRV, &SV_30DANDEG_SRV,		//�p�x
		&SV_26DANPOS_SRV, &SV_27DANPOS_SRV, &SV_28DANPOS_SRV, &SV_29DANPOS_SRV, &SV_30DANPOS_SRV,		//�ʒu
		&SV_26DANPRS_SRV, &SV_27DANPRS_SRV, &SV_28DANPRS_SRV, &SV_29DANPRS_SRV, &SV_30DANPRS_SRV,		//�׏d
		&SV_26DANSPD_SRV, &SV_27DANSPD_SRV, &SV_28DANSPD_SRV, &SV_29DANSPD_SRV, &SV_30DANSPD_SRV,		//���x
		&SV_26DANTIM_SRV, &SV_27DANTIM_SRV, &SV_28DANTIM_SRV, &SV_29DANTIM_SRV, &SV_30DANTIM_SRV			//��~����
	},
	{
		/* 7�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_31DANDEG_SRV, &SV_32DANDEG_SRV, &SV_33DANDEG_SRV, &SV_34DANDEG_SRV, &SV_35DANDEG_SRV,		//�p�x
		&SV_31DANPOS_SRV, &SV_32DANPOS_SRV, &SV_33DANPOS_SRV, &SV_34DANPOS_SRV, &SV_35DANPOS_SRV,		//�ʒu
		&SV_31DANPRS_SRV, &SV_32DANPRS_SRV, &SV_33DANPRS_SRV, &SV_34DANPRS_SRV, &SV_35DANPRS_SRV,		//�׏d
		&SV_31DANSPD_SRV, &SV_32DANSPD_SRV, &SV_33DANSPD_SRV, &SV_34DANSPD_SRV, &SV_35DANSPD_SRV,		//���x
		&SV_31DANTIM_SRV, &SV_32DANTIM_SRV, &SV_33DANTIM_SRV, &SV_34DANTIM_SRV, &SV_35DANTIM_SRV			//��~����
	},
	{
		/* 8�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_36DANDEG_SRV, &SV_37DANDEG_SRV, &SV_38DANDEG_SRV, &SV_39DANDEG_SRV, &SV_40DANDEG_SRV,		//�p�x
		&SV_36DANPOS_SRV, &SV_37DANPOS_SRV, &SV_38DANPOS_SRV, &SV_39DANPOS_SRV, &SV_40DANPOS_SRV,		//�ʒu
		&SV_36DANPRS_SRV, &SV_37DANPRS_SRV, &SV_38DANPRS_SRV, &SV_39DANPRS_SRV, &SV_40DANPRS_SRV,		//�׏d
		&SV_36DANSPD_SRV, &SV_37DANSPD_SRV, &SV_38DANSPD_SRV, &SV_39DANSPD_SRV, &SV_40DANSPD_SRV,		//���x
		&SV_36DANTIM_SRV, &SV_37DANTIM_SRV, &SV_38DANTIM_SRV, &SV_39DANTIM_SRV, &SV_40DANTIM_SRV			//��~����
	},
	{
		/* 9�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_41DANDEG_SRV, &SV_42DANDEG_SRV, &SV_43DANDEG_SRV, &SV_44DANDEG_SRV, &SV_45DANDEG_SRV,		//�p�x
		&SV_41DANPOS_SRV, &SV_42DANPOS_SRV, &SV_43DANPOS_SRV, &SV_44DANPOS_SRV, &SV_45DANPOS_SRV,		//�ʒu
		&SV_41DANPRS_SRV, &SV_42DANPRS_SRV, &SV_43DANPRS_SRV, &SV_44DANPRS_SRV, &SV_45DANPRS_SRV,		//�׏d
		&SV_41DANSPD_SRV, &SV_42DANSPD_SRV, &SV_43DANSPD_SRV, &SV_44DANSPD_SRV, &SV_45DANSPD_SRV,		//���x
		&SV_41DANTIM_SRV, &SV_42DANTIM_SRV, &SV_43DANTIM_SRV, &SV_44DANTIM_SRV, &SV_45DANTIM_SRV			//��~����
	},
	{
		/* 10�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_46DANDEG_SRV, &SV_47DANDEG_SRV, &SV_48DANDEG_SRV, &SV_49DANDEG_SRV, &SV_50DANDEG_SRV,		//�p�x
		&SV_46DANPOS_SRV, &SV_47DANPOS_SRV, &SV_48DANPOS_SRV, &SV_49DANPOS_SRV, &SV_50DANPOS_SRV,		//�ʒu
		&SV_46DANPRS_SRV, &SV_47DANPRS_SRV, &SV_48DANPRS_SRV, &SV_49DANPRS_SRV, &SV_50DANPRS_SRV,		//�׏d
		&SV_46DANSPD_SRV, &SV_47DANSPD_SRV, &SV_48DANSPD_SRV, &SV_49DANSPD_SRV, &SV_50DANSPD_SRV,		//���x
		&SV_46DANTIM_SRV, &SV_47DANTIM_SRV, &SV_48DANTIM_SRV, &SV_49DANTIM_SRV, &SV_50DANTIM_SRV			//��~����
	},
	{
		/* 11�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_51DANDEG_SRV, &SV_52DANDEG_SRV, &SV_53DANDEG_SRV, &SV_54DANDEG_SRV, &SV_55DANDEG_SRV,		//�p�x
		&SV_51DANPOS_SRV, &SV_52DANPOS_SRV, &SV_53DANPOS_SRV, &SV_54DANPOS_SRV, &SV_55DANPOS_SRV,		//�ʒu
		&SV_51DANPRS_SRV, &SV_52DANPRS_SRV, &SV_53DANPRS_SRV, &SV_54DANPRS_SRV, &SV_55DANPRS_SRV,		//�׏d
		&SV_51DANSPD_SRV, &SV_52DANSPD_SRV, &SV_53DANSPD_SRV, &SV_54DANSPD_SRV, &SV_55DANSPD_SRV,		//���x
		&SV_51DANTIM_SRV, &SV_52DANTIM_SRV, &SV_53DANTIM_SRV, &SV_54DANTIM_SRV, &SV_55DANTIM_SRV			//��~����
	},
	{
		/* 12�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_56DANDEG_SRV, &SV_57DANDEG_SRV, &SV_58DANDEG_SRV, &SV_59DANDEG_SRV, &SV_60DANDEG_SRV,		//�p�x
		&SV_56DANPOS_SRV, &SV_57DANPOS_SRV, &SV_58DANPOS_SRV, &SV_59DANPOS_SRV, &SV_60DANPOS_SRV,		//�ʒu
		&SV_56DANPRS_SRV, &SV_57DANPRS_SRV, &SV_58DANPRS_SRV, &SV_59DANPRS_SRV, &SV_60DANPRS_SRV,		//�׏d
		&SV_56DANSPD_SRV, &SV_57DANSPD_SRV, &SV_58DANSPD_SRV, &SV_59DANSPD_SRV, &SV_60DANSPD_SRV,		//���x
		&SV_56DANTIM_SRV, &SV_57DANTIM_SRV, &SV_58DANTIM_SRV, &SV_59DANTIM_SRV, &SV_60DANTIM_SRV			//��~����
	},
	{
		/* 13�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_61DANDEG_SRV, &SV_62DANDEG_SRV, &SV_63DANDEG_SRV, &SV_64DANDEG_SRV, &SV_65DANDEG_SRV,		//�p�x
		&SV_61DANPOS_SRV, &SV_62DANPOS_SRV, &SV_63DANPOS_SRV, &SV_64DANPOS_SRV, &SV_65DANPOS_SRV,		//�ʒu
		&SV_61DANPRS_SRV, &SV_62DANPRS_SRV, &SV_63DANPRS_SRV, &SV_64DANPRS_SRV, &SV_65DANPRS_SRV,		//�׏d
		&SV_61DANSPD_SRV, &SV_62DANSPD_SRV, &SV_63DANSPD_SRV, &SV_64DANSPD_SRV, &SV_65DANSPD_SRV,		//���x
		&SV_61DANTIM_SRV, &SV_62DANTIM_SRV, &SV_63DANTIM_SRV, &SV_64DANTIM_SRV, &SV_65DANTIM_SRV			//��~����
	},
	{
		/* 14�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_66DANDEG_SRV, &SV_67DANDEG_SRV, &SV_68DANDEG_SRV, &SV_69DANDEG_SRV, &SV_70DANDEG_SRV,		//�p�x
		&SV_66DANPOS_SRV, &SV_67DANPOS_SRV, &SV_68DANPOS_SRV, &SV_69DANPOS_SRV, &SV_70DANPOS_SRV,		//�ʒu
		&SV_66DANPRS_SRV, &SV_67DANPRS_SRV, &SV_68DANPRS_SRV, &SV_69DANPRS_SRV, &SV_70DANPRS_SRV,		//�׏d
		&SV_66DANSPD_SRV, &SV_67DANSPD_SRV, &SV_68DANSPD_SRV, &SV_69DANSPD_SRV, &SV_70DANSPD_SRV,		//���x
		&SV_66DANTIM_SRV, &SV_67DANTIM_SRV, &SV_68DANTIM_SRV, &SV_69DANTIM_SRV, &SV_70DANTIM_SRV			//��~����
	},
	{
		/* 15�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_71DANDEG_SRV, &SV_72DANDEG_SRV, &SV_73DANDEG_SRV, &SV_74DANDEG_SRV, &SV_75DANDEG_SRV,		//�p�x
		&SV_71DANPOS_SRV, &SV_72DANPOS_SRV, &SV_73DANPOS_SRV, &SV_74DANPOS_SRV, &SV_75DANPOS_SRV,		//�ʒu
		&SV_71DANPRS_SRV, &SV_72DANPRS_SRV, &SV_73DANPRS_SRV, &SV_74DANPRS_SRV, &SV_75DANPRS_SRV,		//�׏d
		&SV_71DANSPD_SRV, &SV_72DANSPD_SRV, &SV_73DANSPD_SRV, &SV_74DANSPD_SRV, &SV_75DANSPD_SRV,		//���x
		&SV_71DANTIM_SRV, &SV_72DANTIM_SRV, &SV_73DANTIM_SRV, &SV_74DANTIM_SRV, &SV_75DANTIM_SRV			//��~����
	},
	{
		/* 16�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_76DANDEG_SRV, &SV_77DANDEG_SRV, &SV_78DANDEG_SRV, &SV_79DANDEG_SRV, &SV_80DANDEG_SRV,		//�p�x
		&SV_76DANPOS_SRV, &SV_77DANPOS_SRV, &SV_78DANPOS_SRV, &SV_79DANPOS_SRV, &SV_80DANPOS_SRV,		//�ʒu
		&SV_76DANPRS_SRV, &SV_77DANPRS_SRV, &SV_78DANPRS_SRV, &SV_79DANPRS_SRV, &SV_80DANPRS_SRV,		//�׏d
		&SV_76DANSPD_SRV, &SV_77DANSPD_SRV, &SV_78DANSPD_SRV, &SV_79DANSPD_SRV, &SV_80DANSPD_SRV,		//���x
		&SV_76DANTIM_SRV, &SV_77DANTIM_SRV, &SV_78DANTIM_SRV, &SV_79DANTIM_SRV, &SV_80DANTIM_SRV			//��~����
	},
	{
		/* 17�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_81DANDEG_SRV, &SV_82DANDEG_SRV, &SV_83DANDEG_SRV, &SV_84DANDEG_SRV, &SV_85DANDEG_SRV,		//�p�x
		&SV_81DANPOS_SRV, &SV_82DANPOS_SRV, &SV_83DANPOS_SRV, &SV_84DANPOS_SRV, &SV_85DANPOS_SRV,		//�ʒu
		&SV_81DANPRS_SRV, &SV_82DANPRS_SRV, &SV_83DANPRS_SRV, &SV_84DANPRS_SRV, &SV_85DANPRS_SRV,		//�׏d
		&SV_81DANSPD_SRV, &SV_82DANSPD_SRV, &SV_83DANSPD_SRV, &SV_84DANSPD_SRV, &SV_85DANSPD_SRV,		//���x
		&SV_81DANTIM_SRV, &SV_82DANTIM_SRV, &SV_83DANTIM_SRV, &SV_84DANTIM_SRV, &SV_85DANTIM_SRV			//��~����
	},
	{
		/* 18�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_86DANDEG_SRV, &SV_87DANDEG_SRV, &SV_88DANDEG_SRV, &SV_89DANDEG_SRV, &SV_90DANDEG_SRV,		//�p�x
		&SV_86DANPOS_SRV, &SV_87DANPOS_SRV, &SV_88DANPOS_SRV, &SV_89DANPOS_SRV, &SV_90DANPOS_SRV,		//�ʒu
		&SV_86DANPRS_SRV, &SV_87DANPRS_SRV, &SV_88DANPRS_SRV, &SV_89DANPRS_SRV, &SV_90DANPRS_SRV,		//�׏d
		&SV_86DANSPD_SRV, &SV_87DANSPD_SRV, &SV_88DANSPD_SRV, &SV_89DANSPD_SRV, &SV_90DANSPD_SRV,		//���x
		&SV_86DANTIM_SRV, &SV_87DANTIM_SRV, &SV_88DANTIM_SRV, &SV_89DANTIM_SRV, &SV_90DANTIM_SRV			//��~����
	},
	{
		/* 19�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_91DANDEG_SRV, &SV_92DANDEG_SRV, &SV_93DANDEG_SRV, &SV_94DANDEG_SRV, &SV_95DANDEG_SRV,		//�p�x
		&SV_91DANPOS_SRV, &SV_92DANPOS_SRV, &SV_93DANPOS_SRV, &SV_94DANPOS_SRV, &SV_95DANPOS_SRV,		//�ʒu
		&SV_91DANPRS_SRV, &SV_92DANPRS_SRV, &SV_93DANPRS_SRV, &SV_94DANPRS_SRV, &SV_95DANPRS_SRV,		//�׏d
		&SV_91DANSPD_SRV, &SV_92DANSPD_SRV, &SV_93DANSPD_SRV, &SV_94DANSPD_SRV, &SV_95DANSPD_SRV,		//���x
		&SV_91DANTIM_SRV, &SV_92DANTIM_SRV, &SV_93DANTIM_SRV, &SV_94DANTIM_SRV, &SV_95DANTIM_SRV			//��~����
	},
	{
		/* 20�y�[�W��  1�`5�i���[�V�����f�[�^ */
		&SV_96DANDEG_SRV, &SV_97DANDEG_SRV, &SV_98DANDEG_SRV, &SV_99DANDEG_SRV, &SV_100DANDEG_SRV,		//�p�x
		&SV_96DANPOS_SRV, &SV_97DANPOS_SRV, &SV_98DANPOS_SRV, &SV_99DANPOS_SRV, &SV_100DANPOS_SRV,		//�ʒu
		&SV_96DANPRS_SRV, &SV_97DANPRS_SRV, &SV_98DANPRS_SRV, &SV_99DANPRS_SRV, &SV_100DANPRS_SRV,		//�׏d
		&SV_96DANSPD_SRV, &SV_97DANSPD_SRV, &SV_98DANSPD_SRV, &SV_99DANSPD_SRV, &SV_100DANSPD_SRV,		//���x
		&SV_96DANTIM_SRV, &SV_97DANTIM_SRV, &SV_98DANTIM_SRV, &SV_99DANTIM_SRV, &SV_100DANTIM_SRV			//��~����
	}
};
#endif


/*
********************************************************************************
*  Module Name:		dsp_Seisan
*  Function Name:	���Y�̊Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-04
********************************************************************************
*/
void	dsp_Seisan(void)
{
	UNs	*bf_p, i, j;
	UNs	bit;

	switch(disp_stg_sel) {

		case E_sstg_init:		//���Y[��{]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							CAR_mkssi_set();					//�P�ʐ؊�  V01u
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							sw34_gamen_01(KEY_DATA_CODE);		//���Y[��{]��SW3�4�̏���
							break;
						case E_key_sw4:			//key code SW4
							if( (SEQ_016_SV & BIT_12) || (SEQ_016_SV & BIT_14) ){	//ۯĶ���1/2�̔�\��
								sw34_gamen_01(KEY_DATA_CODE);	//���Y[��{]��SW3�4�̏���
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW3
							sw34_gamen_01(KEY_DATA_CODE);		//���Y[��{]��SW3�4�̏���
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_gamen_01(KEY_DATA_CODE);				//���Y[��{]��SW5�6�̏���
					break;
			}
			break;

		case E_sstg_set1:		//���Y[���Y�ݒ�1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(MIS_GAMEN_NON != 0xff){
								disp_stg_sel = E_sstg_set2;			//���Y[���Y�ݒ�2]��
								WINDOW_NO = 19;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
							disp_stg_sel = E_sstg_koud;			//���Y[�P�x�ݒ�]��
							WINDOW_NO = 2;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
#else
							if (SEQ_PAR_113 & BIT_9) { 			//�d�l�ݒ�No.135�uKOMTRAX�v& �@�\�I��1�u�^�ް��Ǘ��v	V06c
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
								WINDOW_NO = 23;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
#endif
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw7:			//key code SW7		//2016/03/18
							if (SV0_LFEED_SEL & BIT_0) {
								disp_stg_sel = E_sstg_lfeed;			//���Y[�t�B�[�_�ݒ�]��
								WINDOW_NO = 25;
								WIN_gamen_disp();						//�E�C���h�E��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//�s���ݒ�ӏ�				2014/09/08
								 (GMN_PAR077 != 0) ) {								//�J��Ԃ��@�\�L��

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
									bit = cBIT0;
									SV_EJECAM_ONR |= (bit << CSR_TBL_POS_NOW);
								}
								else {											//OFF�s��
									bit = cBIT0;
									SV_EJECAM_OFR |= (bit << CSR_TBL_POS_NOW);
								}
								//2020-09-01[2] SEI_test_out_sw5,6 sum���Z�Ώ�
								FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
								
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//�ް���ݼ� �׸� ���
								KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {
		 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_set2:		//���Y[���Y�ݒ�2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_sstg_set1;			//���Y[���Y�ݒ�1]��
								WINDOW_NO = 5;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
							disp_stg_sel = E_sstg_koud;			//���Y[�P�x�ݒ�]��
							WINDOW_NO = 2;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
#else
							if (SEQ_PAR_113 & BIT_9) { 			//�d�l�ݒ�No.135�uKOMTRAX�v& �@�\�I��1�u�^�ް��Ǘ��v	V06e
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
								WINDOW_NO = 23;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
#endif
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw5:			//key code SW5
							SW_FLG_CNT = 1;
							SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

							SWchg_ent();						//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//�s���ݒ�ӏ�				2014/09/08
								 (GMN_PAR077 != 0) ) {								//�J��Ԃ��@�\�L��

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
									bit = cBIT0;
									SV_MISCAM_ONR |= (bit << CSR_TBL_POS_NOW);
								}
								else {											//OFF�s��
									bit = cBIT0;
									SV_MISCAM_OFR |= (bit << CSR_TBL_POS_NOW);
								}
								//2020-09-01[2] SEI_test_out_sw5,6 sum���Z�Ώ�
								FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//�ް���ݼ� �׸� ���
								KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {
								SW_FLG_CNT = 2;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

								SWchg_ent();						//SW CHG �f�[�^ ENT
								KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O

								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_koud:		//���Y[�P�x�ݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode�i�Ȃ��j
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_window_02(KEY_DATA_CODE);		//���Y[�P�x�ݒ�]��SW5�6�̏���
					break;
			}
			break;

		case E_sstg_gaid:		//���Y[�K�C�_���X�\��]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode�i�Ȃ��j
//V01v				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode	//V01v
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_schk;			//���Y[�V�[�P���X�`�F�b�N]��
							WINDOW_NO = 4;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
						case E_key_sw4:			//key code SW4�i�Ȃ��j
							break;
						case E_key_sw5:			//key code SW5	//V01v�i�ǉ��j
//2014/09/02
////							disp_stg_sel = E_sstg_samp;			//���Y[�T���v�����O]��
////							if ( SEQ_024_SV & BIT_7 ) {			//�d�l�ݒ�136	�ȈՌ����鉻		V06l
////								GAMEN_NO = 67;					//�ȈՌ����鉻 �L��
////							}
////							else {
////								GAMEN_NO = 105;					//�ȈՌ����鉻 ����
////							}
////							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_samp;			//���Y[�T���v�����O]��
							if ( SEQ_024_SV & BIT_7 ) {			//�d�l�ݒ�136	�ȈՌ����鉻		V06l
								GAMEN_NO = 67;					//�ȈՌ����鉻 �L��
							}
							else {
								GAMEN_NO = 105;					//�ȈՌ����鉻 ����
							}
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw6:			//key code SW6	//V01v�i�ǉ��j
//2014/09/02							SEQ_PAR_056 |= BIT_12;					//�����ݸ޽���SW��ON
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6_down:	//key code SW6(������)	//V01v�i�ǉ��j
//2014/09/02							SEQ_PAR_056 &= ~BIT_12;					//�����ݸ޽���SW��OFF
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_schk:		//���Y[�V�[�P���X�`�F�b�N]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;
						case E_key_sw3:			//key code SW3�i�Ȃ��j
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
												// �f�o�b�O��ʂl�`�j�d shima
						case E_key_sw6:			//key code SW6
							if(SEQ_025_SV & BIT_14) {
								disp_stg_sel = E_sstg_deb;			//���Y[�f�o�b�O]��
								GAMEN_NO = 70;
								GAMEN_disp();						//��ʕ\��
							}
							break;
					}
					break;
			}
			break;

		case E_sstg_deb:		//���Y[�f�o�b�O]shima
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5:			//key code SW5	// V05i
//V05j							KJ_CHK_MEM_CLR();
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_sstg_his;			//���Y[�ُ헚��]��
							GAMEN_NO = 69;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_sstg_his:		//���Y[�ُ헚��]shima
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_sstg_mmon:		//���Y[���[�V�������j�^]

#if (mot100_test == 1)
			mmon_agl_ovbit_make();				//�ڕW�p���I�[�o�[���Ă���s�̃r�b�g�����쐬
			mmon_spd_ovbit_make();				//���x���I�[�o�[���Ă���s�̃r�b�g�����쐬
			mmon_spd_lmbit_make();				//���x���Ⴗ����s�̃r�b�g�����쐬
			mmon_act_step_bit_make();			//���[�V�������s�s���̃r�b�g�����쐬
#endif
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//�ݒ�l�̊m��
					mmon_sv_chg(i);								//�p�x&�ʒu�̐ݒ�l�ύX
#if (mot100_test == 1)
					SWchg_disp();								//�r�v�f�[�^���@�\��
#else
					mmon_tchk_disp(0x00);						//Ӱ��݉�ʗp���ð��ق�����&�\��
#endif
					mmon_trans_put();							//��]�����ɂ���ް��̊i�[
					mmon_f_off(j);								//��葬�x�ݒ�ر				2014/09/25
#if (mot100_test == 1)
					mmon_step_chg_disp();						//�s�����ύX������&�\��
					MOT_CHG_REQ(j);								//���[�V�����ύX�s���̑��M�v��
#endif
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4�iV01w(INS)�j
							if( (SEQ_050_SV & BIT_1) == 0) {		//���]�ȊO�H		2014/08/20
								disp_stg_sel = E_sstg_hos;			//���Y[�␳���j�^]��
								WINDOW_NO = 20;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							if( SEQ_PAR_107 & BIT_2 ) {			//�@�\�I��3(���Y���l�ݒ�@1:�L)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWð��ٌ�
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									SWchg_ent();								//SW CHG �f�[�^ ENT
									mmon_trans_put();							//��]�����ɂ���ް��̊i�[
								}
								SEI_test_out_sw5();								//���Y�ݒ�ýďo�͏���(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							if( SEQ_PAR_107 & BIT_2 ) {			//�@�\�I��3(���Y���l�ݒ�@1:�L)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//���ٔF���ԍ����̈ړ�����
											bf_p = SW_buff[j].DATA_ADR;				//�ް��i�[���ڽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//�ް��i�[��̕ύX�ޯĈʒu
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//���ٔF���ԍ����̈ړ�����
												SW_TBL_POS_NOW = j;					//�r�v�f�[�^�����I��
												break;
											}
										}
									}
									FURIKO_SW_del();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
									SWchg_move_ent();								//SW CHG�̈ړ� �ް�ENT
									SV0_MOT_FIX = 0;								//��葬�x�u���O�N���A			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//��]�����ɂ��ݒ�l �؊���
#if (mot100_test == 1)
									mmon_kaiten_chg();								//��]�����ɂ��ݒ�l �؊���
									SV_MOT_PAGE_INIT();
#endif
									FURIKO_SW_chk();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
//2014/08/20 �ĕ`�悵���Ⴆ�I
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6���i��׸�
										//��~�́uV�v����
										SWchg_mmon_ent();								//Ӱ��ݗp SW�ް� ENT
										mmon_trans_put();								//��]�����ɂ���ް��̊i�[
#if (mot100_test == 1)
										MOT_CHG_REQ(CSR_TBL_POS_NOW);					//���[�V�����ύX�s���̑��M�v��
#endif
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 99) {	//SW56up��ׁ����x�����ق͑��x		V06p
										//���x���ЯĒl����
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 97) {	//SW56up��ׁ����x�����ق͑��x		V06p
										//�p�x���ЯĒl����
										mmon_agl_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6���i��׸��ڕW�l		2015/01/15
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//�����^�׏d�ڕW�؊���
									}
								}
								/* V00m */
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
			 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
								}
							}
							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57) {
			 					SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//�d�l�ݒ�No.140
								disp_stg_sel = E_sstg_epm;			//�f�[�^�ݒ�[�d�̓��j�^]��
								GAMEN_NO = 102;
								GAMEN_disp();						//��ʕ\��
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		/* V01d */
		case E_sstg_mmon2:		//���Y[���[�V�������j�^6�`10]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//�ݒ�l�̊m��
					mmon_sv_chg(i);								//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);						//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();							//��]�����ɂ���ް��̊i�[
					mmon_f_off(j);								//��葬�x�ݒ�ر				2014/09/25
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4�iV01w(INS)�j
							if( (SEQ_050_SV & BIT_1) == 0) {		//���]�ȊO�H		2014/08/20
								disp_stg_sel = E_sstg_hos;			//���Y[�␳���j�^]��
								WINDOW_NO = 20;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							if( SEQ_PAR_107 & BIT_2 ) {			//�@�\�I��3(���Y���l�ݒ�@1:�L)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWð��ٌ�
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									SWchg_ent();								//SW CHG �f�[�^ ENT
									mmon_trans_put();							//��]�����ɂ���ް��̊i�[
								}
								SEI_test_out_sw5();								//���Y�ݒ�ýďo�͏���(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 58) {
		 						SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							}
							break;

						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							if( SEQ_PAR_107 & BIT_2 ) {			//�@�\�I��3(���Y���l�ݒ�@1:�L)
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//���ٔF���ԍ����̈ړ�����
											bf_p = SW_buff[j].DATA_ADR;				//�ް��i�[���ڽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//�ް��i�[��̕ύX�ޯĈʒu
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//���ٔF���ԍ����̈ړ�����
												SW_TBL_POS_NOW = j;					//�r�v�f�[�^�����I��
												break;
											}
										}
									}
									FURIKO_SW_del();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
									SWchg_move_ent();								//SW CHG�̈ړ� �ް�ENT
									SV0_MOT_FIX = 0;								//��葬�x�u���O�N���A			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//��]�����ɂ��ݒ�l �؊���
									FURIKO_SW_chk();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
//2014/08/20 �ĕ`�悵���Ⴆ�I
									disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
									GAMEN_NO = 3;
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6���i��׸�
										//��~�́uV�v����
										SWchg_mmon_ent();								//Ӱ��ݗp SW�ް� ENT
										mmon_trans_put();								//��]�����ɂ���ް��̊i�[
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 99) {	//SW56up��ׁ����x�����ق͑��x		V06p
										//���x���ЯĒl����
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 97) {	//SW56up��ׁ����x�����ق͑��x		V06p
										//�p�x���ЯĒl����
										mmon_agl_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6���i��׸��ڕW�l		2015/01/15
//2015/04/10										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//�����^�׏d�ڕW�؊���
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97+5);	//�����^�׏d�ڕW�؊���
									}
								}
								/* V00m */
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
			 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
								}
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//�d�l�ݒ�No.140
								disp_stg_sel = E_sstg_epm;			//�f�[�^�ݒ�[�d�̓��j�^]��
								GAMEN_NO = 102;
								GAMEN_disp();						//��ʕ\��
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_mcg:		//���Y[���[�V�����O���t]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3�i�Ȃ��j
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_024_SV & BIT_7) {
								disp_stg_sel = E_sstg_pvsmp;		//���Y[���[�V�����T���v�����O�\��]��	//V05o(�ǉ�)
								GAMEN_NO = 9;
								GAMEN_disp();						//��ʕ\��
								Dsp_Pvgraph_INIT();
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							if (SEQ_024_SV & BIT_7) {
								disp_stg_sel = E_sstg_pvtrd;		//���Y[���[�V�����g�����h�\��]��		//V05o(�ǉ�)
								GAMEN_NO = 10;
								SV_WAVE_PAGE = 0;					//V05o_a
								GAMEN_disp();						//��ʕ\��
								Dsp_Pvgraph_INIT();
							}
							break;
#endif
					}
					break;
			}
			break;

		case E_sstg_samp:		//���Y[�T���v�����O]	//V01v(�ǉ�)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode�i�Ȃ��j
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_trnd;			//���Y[�g�����h]��			//V01z(INS)
							if ( SEQ_024_SV & BIT_7 ) {			//�d�l�ݒ�136	�ȈՌ����鉻		V06l
								GAMEN_NO = 66;					//�ȈՌ����鉻 �L��
							}
							else {
								GAMEN_NO = 104;					//�ȈՌ����鉻 ����
							}
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw4:			//key code SW4
							break;
						case E_key_sw5:			//key code SW5
//V01z							if(CSR_FLG_CNT>2) {
//V05o							if(CSR_FLG_CNT<=4) {

							if(GAMEN_NO == 67) {					//V06l
								//���No. 67  �����ݸސݒ���  SIT�����鉻�ݒ�L��
//2014/09/02
////								if( (CSR_FLG_CNT==1) ||
////									(CSR_FLG_CNT==2) ||
////									(CSR_FLG_CNT==3) ||
////									(CSR_FLG_CNT==4) ||
////									(CSR_FLG_CNT==6) )
								if( (CSR_FLG_CNT==1) ||
									(CSR_FLG_CNT==2) ||
									(CSR_FLG_CNT==3) ||
									(CSR_FLG_CNT==5) ||
									(CSR_FLG_CNT==7) )
								{
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									SWchg_ent();							//SW CHG �f�[�^ ENT
									SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								}
							}
							else {
								//���No.105  �����ݸސݒ���  SIT�����鉻�ݒ薳��
								if(CSR_FLG_CNT<=4) {
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									SWchg_ent();							//SW CHG �f�[�^ ENT
									SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								}
							}

							break;
						case E_key_sw6:			//key code SW6
//V01z							if(CSR_FLG_CNT<3) {
//////								SW_FLG_CNT = 1;
//////							}
//////							else {
//////								SW_FLG_CNT = 2;
//////							}
//V05o							if( (CSR_FLG_CNT>=2) && (CSR_FLG_CNT<=4) ) {

							if(GAMEN_NO == 67) {					//V06l
								//���No. 67  �����ݸސݒ���  SIT�����鉻�ݒ�L��
//2014/09/02
////								if( (CSR_FLG_CNT==3) ||
////									(CSR_FLG_CNT==4) ||
////									(CSR_FLG_CNT==6) )
								if( (CSR_FLG_CNT==3) ||
									(CSR_FLG_CNT==5) ||
									(CSR_FLG_CNT==7) )
								{
									SW_FLG_CNT = 2;
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									SWchg_ent();							//SW CHG �f�[�^ ENT
									SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								}
//2014/09/02
////								else if( (CSR_FLG_CNT==5) ||
////										 (CSR_FLG_CNT==7) )
								else if( (CSR_FLG_CNT==4) ||
										 (CSR_FLG_CNT==6) ||
										 (CSR_FLG_CNT==8) )
								{
									SW_FLG_CNT = 1;
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									SWchg_ent();							//SW CHG �f�[�^ ENT
									SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								}
							}
							else {
								//���No.105  �����ݸސݒ���  SIT�����鉻�ݒ薳��
								if( (CSR_FLG_CNT>=2) && (CSR_FLG_CNT<=4) ) {
									SW_FLG_CNT = 2;
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									SWchg_ent();							//SW CHG �f�[�^ ENT
									SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								}
							}
















							break;
						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_trnd:		//���Y[�g�����h]	//V01z(�ǉ�)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode�i�Ȃ��j
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_samp;			//���Y[�T���v�����O]��
							if ( SEQ_024_SV & BIT_7 ) {			//�d�l�ݒ�136	�ȈՌ����鉻		V06l
								GAMEN_NO = 67;					//�ȈՌ����鉻 �L��
							}
							else {
								GAMEN_NO = 105;					//�ȈՌ����鉻 ����
							}
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							break;
						case E_key_sw5:			//key code SW5
							if(CSR_FLG_CNT<=1) {
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
								SWchg_ent();							//SW CHG �f�[�^ ENT
								SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;
						case E_key_sw6:			//key code SW6
							if(CSR_FLG_CNT<=1) {
								SW_FLG_CNT = 2;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
								SWchg_ent();							//SW CHG �f�[�^ ENT
								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else if(CSR_FLG_CNT<=3) {									//V05o(INS)
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
								SWchg_ent();							//SW CHG �f�[�^ ENT
								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}

							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB != 0) {								//2014/03/17
		 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							}
							break;
						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_hos:		//���Y[�␳���j�^]	//V01w(�ǉ�)
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					Key_Ent_sv();								//�ݒ�l�̊m��
					mmon_sv_chg(i);								//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);						//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();							//��]�����ɂ���ް��̊i�[
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
	 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_11) {				//�d�l�ݒ�No.140
								disp_stg_sel = E_sstg_epm;			//�f�[�^�ݒ�[�d�̓��j�^]��
								GAMEN_NO = 102;
								GAMEN_disp();						//��ʕ\��
								Dsp_EPM_INIT();
							}
							break;
#endif

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_pvsmp:		//���Y[���[�V�����T���v�����O�\��]	//V05o(�ǉ�)

			Dsp_PvSamp_Wave();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3�i�Ȃ��j
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4�i�Ȃ��j
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_pvtrd;		//���Y[���[�V�����g�����h�\��]��		//V05o(�ǉ�)
							GAMEN_NO = 10;
							SV_WAVE_PAGE = 0;					//V05o_a
							GAMEN_disp();						//��ʕ\��
							Dsp_Pvgraph_INIT();
							break;
#endif

						case E_key_sw6:			//key code SW6_SUB		//V06g  2011/07/28
							if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 257) {			//V06g 2011/07/28
	 							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							}
							break;

						case E_key_sw6_down:	//key code SW6(������)	//V06g  2011/07/28
							if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 257) {			//V06g 2011/07/28
								SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							}
							break;

					}
					break;
			}
			break;

		case E_sstg_pvtrd:		//���Y[���[�V�����g�����h�\��]		//V05o(�ǉ�)

			Dsp_PvTrnd_Wave();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3�i�Ȃ��j
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4�i�Ȃ��j
							disp_stg_sel = E_sstg_pvsmp;		//���Y[���[�V�����T���v�����O�\��]��
							GAMEN_NO = 9;
							GAMEN_disp();						//��ʕ\��
							Dsp_Pvgraph_INIT();
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif
					}
					break;
			}
			break;

		case E_sstg_epm:		//���Y[�d�̓��j�^]		V06

			Dsp_EPM_GRAPH();

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					if (CSR_FLG_CNT == 1)
					{
						i = EPM_TOTAL_INF;
						if (i == BIT_0)				i = BIT_1;
						else if (i == BIT_1)		i = BIT_2;
						else if (i == BIT_2)		i = BIT_0;
						EPM_TOTAL_INF = i;
						EPM_GAMEN_RIF = 1;							//�ĕ`��
					}
					else if (CSR_FLG_CNT == 4)
					{
						EPM_CLR_TIM = 1000;						//5sec
						EPM_CLR_FLG = 1;
					}
					else
					{
						Key_Ent_sv();								//�ݒ�l�̊m��
					}

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
							GAMEN_NO = 3;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_sstg_mcg;			//���Y[���[�V�����O���t]��
							GAMEN_NO = 4;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;

						case E_key_sw4:			//key code SW4�iV01w(INS)�j
							if( (SEQ_050_SV & BIT_1) == 0) {		//���]�ȊO�H		2014/08/20
								disp_stg_sel = E_sstg_hos;			//���Y[�␳���j�^]��
								WINDOW_NO = 20;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif

					}
					break;
			}

			if ( (CSR_FLG_CNT == 4) && (Key_Data_WK[0] & BIT_2 ) )			//V06a
			{
				if ( (EPM_CLR_TIM == 0) && (EPM_CLR_FLG == 1) )
				{
					EPM_MEM_CLR();
					EPM_CLR_FLG = 0;
					EPM_GAMEN_RIF = 1;						//�ĕ`��
				}
			}
			else
			{
				EPM_CLR_FLG = 0;
			}

			break;

		case E_sstg_seidou:		//���Y[��������WIN]		V06

			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
						case E_key_sw5:			//key code SW5
							break;

						case E_key_sw6:			//key code SW6
							SEQ_PAR_058 |= BIT_4;
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							break;
#endif

						case E_key_sw5_down:	//key code SW5(������)
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SEQ_PAR_058 &= ~BIT_4;
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

					}
					break;
			}
			break;

		case E_sstg_seikan:		//���Y[���Y�Ǘ�]	V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//��Ǝ҂���H
								disp_stg_sel = E_sstg_wkstr0;		//���Y[��ƊJ�n0]��
								WINDOW_NO = 51;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							else {
								disp_stg_sel = E_sstg_wkstr1;		//���Y[��ƊJ�n1]��
								WINDOW_NO = 52;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��

								SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//���܂ł̍�ƎҺ��ޑޔ�
								SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//���܂ł̒��Ժ��ޑޔ�
								SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//���܂ł̌v�搔�ޔ�
							}
							break;

						case E_key_sw7:			//key code SW7
							disp_stg_sel = E_sstg_wkstp0;		//���Y[��ƏI��]��
							WINDOW_NO = 58;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw5:			//key code SW5
							if (CSR_FLG_CNT == 2) {				//���ف��s�ǐ��H
								if (SV_BAD_CNT) {
									SV_BAD_CNT--;
									FRAM_csum_set();			//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
								}
								SVdata_disp();					//�ݒ�l���@�\��
							}
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;















						case E_key_sw6:			//key code SW6
							if (CSR_FLG_CNT == 2) {				//���ف��s�ǐ��H
								if (SV_BAD_CNT<99999999) {		//V06d�iLIMIT�ǉ��j
									SV_BAD_CNT++;
									FRAM_csum_set();			//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
									SVdata_disp();					//�ݒ�l���@�\��
								}
							}
							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr0:		//���Y[��ƊJ�n0]	V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
							WINDOW_NO = 23;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							SEI_Worker_STP();					//���Y�Ǘ���ƏI��

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_wkstr1;		//���Y[��ƊJ�n1]��
							WINDOW_NO = 52;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//���܂ł̍�ƎҺ��ޑޔ�
							SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//���܂ł̒��Ժ��ޑޔ�
							SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//���܂ł̌v�搔�ޔ�

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr1:		//���Y[��ƊJ�n1]��ƎҺ��ނ̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();						//�ݒ�l�̊m��

					disp_stg_sel = E_sstg_wkstr2;		//���Y[��ƊJ�n2]��
					WINDOW_NO = 53;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							disp_stg_sel = E_sstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 54;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr2:		//���Y[��ƊJ�n2]��ƎҺ��ނ̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_WORKER_COD = SV0_WORKER_COD_BAK;	//�O�ɖ߂�

							disp_stg_sel = E_sstg_wkstr1;		//���Y[��ƊJ�n1]��
							WINDOW_NO = 52;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_sstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 54;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr3:		//���Y[��ƊJ�n3]���Ժ��ނ̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��

					disp_stg_sel = E_sstg_wkstr4;		//���Y[��ƊJ�n4]��
					WINDOW_NO = 55;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							disp_stg_sel = E_sstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 56;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr4:		//���Y[��ƊJ�n4]���Ժ��ނ̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_ORDER_COD = SV0_ORDER_COD_BAK;	//�O�ɖ߂�

							disp_stg_sel = E_sstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 54;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_sstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 56;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr5:		//���Y[��ƊJ�n5]�v�搔�̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��

					disp_stg_sel = E_sstg_wkstr6;		//���Y[��ƊJ�n6]��
					WINDOW_NO = 57;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							SEI_Worker_SET();					//����ް��m��

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
							WINDOW_NO = 23;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��


							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstr6:		//���Y[��ƊJ�n6]�v�搔�̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_PLAN_CNT = SV0_PLAN_CNT_BAK;		//�O�ɖ߂�

							disp_stg_sel = E_sstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 56;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							SEI_Worker_SET();					//����ް��m��

							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
							WINDOW_NO = 23;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_wkstp0:		//���Y[��ƏI��]��ƏI���̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
//V06d							SEI_Worker_GET();
//////							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
//////							WINDOW_NO = 23;
//////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SEI_Worker_GET();
							disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
							WINDOW_NO = 23;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//��Ǝ҂���H
								SEI_Worker_STP();					//���Y�Ǘ���ƏI��
    
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
								WINDOW_NO = 23;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
    
								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_sstg_lfeed:		//���Y[�t�B�[�_�ݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_sstg_init;			//���Y[��{]��
							GAMEN_NO = 1;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Seisan_sel();						//���Y�ݒ�ւ̑J��(��ު��/н̨���)
							break;
						case E_key_sw3:			//key code SW3
							if (SEQ_PAR_113 & BIT_9) { 			//�d�l�ݒ�No.135�uKOMTRAX�v& �@�\�I��1�u�^�ް��Ǘ��v	V06c
								SEI_Worker_GET();
								disp_stg_sel = E_sstg_seikan;		//���Y[���Y�Ǘ�]��
								WINDOW_NO = 23;
								WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_sstg_gaid;			//���Y[�K�C�_���X�\��]��
							WINDOW_NO = 3;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

	}
}


/*
********************************************************************************
*  Module Name:		Seisan_sel
*  Function Name:	���Y�ݒ�ւ̑J��(��ު��/н̨���)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-20
********************************************************************************
*/
void	Seisan_sel(void)
{

	EJE_GAMEN_NON = 0;						//�G�W�F�N�^ �L
	if(00 == EJE_check()) {					//�G�W�F�N�^�L���`�F�b�N
		EJE_GAMEN_NON = 0xff;				//�G�W�F�N�^ ��
	}

	MIS_GAMEN_NON = 0;						//�~�X�t�B�[�h �L
	if(00 == MIS_check()){					//�~�X�t�B�[�h�L���`�F�b�N
		MIS_GAMEN_NON = 0xff;				//�~�X�t�B�[�h ��
	}

	if(EJE_GAMEN_NON == 0){
		disp_stg_sel = E_sstg_set1;			//���Y[���Y�ݒ�1]��
		WINDOW_NO = 5;
	}
	else if(MIS_GAMEN_NON == 0){
		disp_stg_sel = E_sstg_set2;			//���Y[���Y�ݒ�2]��
		WINDOW_NO = 19;
	}
	else{
		disp_stg_sel = E_sstg_set1;			//���Y[���Y�ݒ�1]��
		WINDOW_NO = 5;
	}
	WIN_gamen_disp();						//�E�C���h�E��ʕ\��
}


/*
********************************************************************************
*  Module Name:		sw34_gamen_01
*  Function Name:	���Y[��{]��SW3�4�̏���
*  Input	:		������(SW3/4)
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-13
********************************************************************************
*/
void	sw34_gamen_01(UNs k_code)
{

	if(k_code == E_key_sw3){	//SW3(�g�[�^���J�E���^)�H
		if(SW14_ON1_FLG == 2){								//���g�[�^���J�E���^�P��������Ă������H
			if(SEQ_PAR_107 & BIT_4){						//�@�\�I��5(���Ēl�C���@1:�L)
				SW14_ON1_FLG = 0x82;						//���g�[�^���J�E���^�P������

				COUNT_HOSEI_ADR = PV_buff[0].XY_POS;		//���]�A�h���X�f�[�^�Ҕ�
				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����

				SW56_upcara_disp(6, 5);						//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(5, 7);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(6, 8);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			}
			else{
				SW14_ON1_FLG = 0;							//�f�[�^�N���A

				SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
				CSR_disp_off();								//�J�[�\���\������
//2014/09/02
////				SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
////				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
////				SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_upcara_disp(266, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(76, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(77, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

				SW16data_onset(0x00, 3);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			}
		}
		else if(SW14_ON1_FLG == 0x82){
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//�����̃��[�h���H
			if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
				Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
			}
			SW14_ON1_FLG = 0;							//�f�[�^�N���A

			SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
			CSR_disp_off();								//�J�[�\���\������
//2014/09/02
////			SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
////			SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
////			SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			SW56_upcara_disp(266, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
			SW56_dncara_disp(76, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			SW56_dncara_disp(77, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

			SW16data_onset(0x00, 3);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
		}
		else{
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//�����̃��[�h���H
			if(SW14_ON1_FLG & 0x80){						//���J�E���^�␳�@�\���H
				if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
				}
			}
			SW14_ON1_FLG = 0x02;							//���g�[�^���J�E���^�P������

			CSR_FLG = 5;									//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;								//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 0;									//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;									//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, 00);							//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

			SW16data_onset(0xff, 3);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 4);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 9);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)	V01z(�ǉ�)
			SW16data_onset(0xff, 5);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
		}
	}
	else if(k_code == E_key_sw4){	//SW4(���b�g�J�E���^1 / 2)
		switch(SW14_ON1_FLG) {
			default:
				if(SW14_ON1_FLG & 0x80){						//���J�E���^�␳�@�\���H
					if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
					}
				}
				SW14_ON1_FLG = 0;
				SW14_ON1_FLG_BAK = 0;
			case 00:
//				if(SW14_ON1_FLG_BAK == 0){
					SW14_ON1_FLG = 0x03;							//���g�[�^���J�E���^�P������

					CSR_FLG = 5;									//�J�[�\���\���ʒu�w��
					CSR_FLG_CNT = 2;								//�J�[�\���ԍ��Z�b�g
					SV_FLG_CNT = 1;									//�ݒ�l�ԍ��Z�b�g
					SW_FLG_CNT = 1;									//�r�v�ԍ��Z�b�g
					CSR_move(CSR_FLG, 00);							//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

					SW16data_onset(0x00, 3);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0xff, 4);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0x00, 9);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)	V01z(�ǉ�)
					SW16data_onset(0xff, 5);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0xff, 6);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//				}
//				else{
//
//				}
				break;

			case 0x03:							//�O�񉽂��̃L�[�������ꂢ�����H
			case 0x04:							//�O�񉽂��̃L�[�������ꂢ�����H
				if(SEQ_PAR_107 & BIT_4){						//�@�\�I��5(���Ēl�C���@1:�L)
					if(SW14_ON1_FLG == 0x03){
						SW14_ON1_FLG = 0x83;						//�����b�g�J�E���^�P������
						COUNT_HOSEI_ADR = PV_buff[1].XY_POS;		//���]�A�h���X�f�[�^�Ҕ�
					}
					else{
						SW14_ON1_FLG = 0x84;						//�����b�g�J�E���^2������
						COUNT_HOSEI_ADR = PV_buff[2].XY_POS;		//���]�A�h���X�f�[�^�Ҕ�
					}
					Count_hosei_csr_on(COUNT_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����

					SW56_upcara_disp(6, 5);						//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
					SW56_dncara_disp(5, 7);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_dncara_disp(6, 8);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				}
				else{
					SW14_ON1_FLG_BAK = SW14_ON1_FLG;
					SW14_ON1_FLG = 0;							//�f�[�^�N���A

					SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
					CSR_disp_off();								//�J�[�\���\������
//2014/09/02
////					SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
////					SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
////					SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_upcara_disp(266, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
					SW56_dncara_disp(76, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_dncara_disp(77, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

					SW16data_onset(0x00, 4);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				}
				break;

			case 0x83:							//�O�񉽂��̃L�[�������ꂢ�����H
			case 0x84:							//�O�񉽂��̃L�[�������ꂢ�����H
//				SW56dn_clear(SW14_ON1_FLG & 0x7f);				//�����̃��[�h���H
				if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
				}

				SW14_ON1_FLG_BAK = SW14_ON1_FLG;
				SW14_ON1_FLG = 0;							//�f�[�^�N���A

				SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
				CSR_disp_off();								//�J�[�\���\������
//2024/09/02
////				SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
////				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
////				SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_upcara_disp(266, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(76, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(77, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

				SW16data_onset(0x00, 4);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
				break;
		}
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
	else if(k_code == E_key_sw7){	//SW7(�I�[�o���C�h)		/* V01z */
		if(SW14_ON1_FLG == 5){	//����ײ�ޏ������H
			SW14_ON1_FLG = 0;							//�f�[�^�N���A

			SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
			CSR_disp_off();								//�J�[�\���\������
//2014/09/02
////			SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
////			SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
////			SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			SW56_upcara_disp(266, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
			SW56_dncara_disp(76, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			SW56_dncara_disp(77, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

			SW16data_onset(0x00, 9);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
		}
		else {
			if(SW14_ON1_FLG & 0x80){						//���J�E���^�␳�@�\���H
				if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
				}
			}
			SW14_ON1_FLG = 0x05;							//���g�[�^���J�E���^�P������

			CSR_FLG = 5;									//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 4;								//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;									//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;									//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, 00);							//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

			SW16data_onset(0x00, 3);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 4);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 9);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
		}
	}
#endif
	Under_grph();											//���i�̃O���t�B�b�N�Z�b�g
	Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);		//�s�\��(LCD1)
	Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);		//�s�\��(LCD1)
	Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��(LCD2)
	Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��(LCD2)
}


//		if(SW14_ON1_FLG == 4){								//���b�g�J�E���^2��������Ă������H
///			if(SEQ_PAR_107 & BIT_4){						//�@�\�I��5(���Ēl�C���@1:�L)
//				SW14_ON1_FLG = 0x84;						//�����b�g�J�E���^2������
//
//				COUNT_HOSEI_ADR = PV_buff[2].XY_POS;		//���]�A�h���X�f�[�^�Ҕ�
//				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
//
//				SW56_upcara_disp(6, 5);						//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
//				SW56_dncara_disp(5, 7);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//				SW56_dncara_disp(6, 8);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//			}
//			else{
//				SW14_ON1_FLG = 0;							//�f�[�^�N���A
//
//				SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
//				CSR_disp_off();								//�J�[�\���\������
//				SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
//				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//				SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//
//				SW16data_onset(0x00, 4);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//				SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//				SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			}
//		}
//		else if(SW14_ON1_FLG == 0x84){						//���b�g�J�E���^2��������Ă������H
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//�����̃��[�h���H
//			if(SW14_ON1_FLG & 0x80){						//���J�E���^�␳�@�\���H
//				if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
//					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
//				}
//			}
//			SW14_ON1_FLG = 0x04;							//���g�[�^���J�E���^2������
//
//			CSR_FLG = 5;									//�J�[�\���\���ʒu�w��
//			CSR_FLG_CNT = 3;								//�J�[�\���ԍ��Z�b�g
//			SV_FLG_CNT = 1;									//�ݒ�l�ԍ��Z�b�g
//			SW_FLG_CNT = 1;									//�r�v�ԍ��Z�b�g
//			CSR_move(CSR_FLG, 00);							//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)
//
//			SW16data_onset(0x00, 3);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 4);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 5);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 6);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//		}
//		else if(SW14_ON1_FLG == 3){							//�����b�g�J�E���^�P��������Ă������H
//			if(SEQ_PAR_107 & BIT_4){						//�@�\�I��5(���Ēl�C���@1:�L)
//				SW14_ON1_FLG = 0x83;						//�����b�g�J�E���^�P������
//
//				COUNT_HOSEI_ADR = PV_buff[1].XY_POS;		//���]�A�h���X�f�[�^�Ҕ�
//				Count_hosei_csr_on(COUNT_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
//
//				SW56_upcara_disp(6, 5);						//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
//				SW56_dncara_disp(5, 7);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//				SW56_dncara_disp(6, 8);						//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//			}
//			else{
//				SW14_ON1_FLG = 0;							//�f�[�^�N���A
//
//				SVdata_disp_ent(SV_TBL_POS_NOW);			//�ݒ�r���̕��́A���ɖ߂�����
//				CSR_disp_off();								//�J�[�\���\������
//				SW56_upcara_disp(0xff, 5);					//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
//				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//				SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//
//				SW16data_onset(0x00, 4);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//				SW16data_onset(0x00, 5);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//				SW16data_onset(0x00, 6);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			}
//		}
//		else{
//			SW56dn_clear(SW14_ON1_FLG & 0x7f);				//�����̃��[�h���H
//			if(SW14_ON1_FLG & 0x80){						//���J�E���^�␳�@�\���H
//				if(COUNT_HOSEI_ADR != 00){					//���]�A�h���X�f�[�^�Ҕ�
//					Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
//				}
//			}
//			SW14_ON1_FLG = 0x03;							//���g�[�^���J�E���^�P������
//
//			CSR_FLG = 5;									//�J�[�\���\���ʒu�w��
//			CSR_FLG_CNT = 2;								//�J�[�\���ԍ��Z�b�g
//			SV_FLG_CNT = 1;									//�ݒ�l�ԍ��Z�b�g
//			SW_FLG_CNT = 1;									//�r�v�ԍ��Z�b�g
//			CSR_move(CSR_FLG, 00);							//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)
//
//			SW16data_onset(0x00, 3);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 4);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 5);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//			SW16data_onset(0xff, 6);						//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
//		}


/*
********************************************************************************
*  Module Name:		sw56_gamen_01
*  Function Name:	���Y[��{]��SW5�6�̏���
*  Input	:		������(SW5/6)
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-13
********************************************************************************
*/
void	sw56_gamen_01(UNs k_code)
{
	UNs		t_no;
	UNl		dat;

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//������?
		DANseq_sw56off(k_code);						//�i���p�V�[�P���X�n�e�e
		SEISAN_SW56_FLG = 0;

		SEQ_PAR_056 &= ~(cBIT12+cBIT15);			//2014/09/02

		return;
	}

	if(SW14_ON1_FLG == 2){							//�g�[�^���J�E���^��������Ă������H
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG �f�[�^ ENT
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
		}
		else{
			PV_TOTLC1_B3 = 0;						//�g�[�^���J�E���^�P�����l�N���A
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
		}
	}
	else if(SW14_ON1_FLG == 3){						//���b�g�J�E���^��������Ă������H
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG �f�[�^ ENT
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			if( 00 == (SEQ_032_SV & BIT_2)){
				SEQ_PAR_033 &= ~BIT_0;				//ۯĶ���1 ����UP(1:����UP)
			}
		}
		else{
			PV_LOTCT1_B4 = 0;						//���b�g�J�E���^�P�����l�N���A
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			SEQ_PAR_033 &= ~BIT_0;					//ۯĶ���1 ����UP(1:����UP)
		}
	}
	else if(SW14_ON1_FLG == 0x82){					//���g�[�^���J�E���^�i�J�E���^�␳�j��������Ă������H
		if(k_code == E_key_sw5){					//SW5? ���Z�H
			if(PV_TOTLC1_B3 != 00){
				PV_TOTLC1_B3 --;					//�g�[�^���J�E���^�P�����l���Z
				KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
			}
		}
		else{
			PV_TOTLC1_B3 ++;						//�g�[�^���J�E���^�P�����l���Z
			KAT_DATCHG_FLG = 0xff;					//�J�E���^�l�ύX�t���O
			if(0x00989680 <= PV_TOTLC1_B3 ){
				PV_TOTLC1_B3 --;
			}
		}
	}
	else if(SW14_ON1_FLG == 0x83){					//�����b�g�J�E���^�i�J�E���^�␳�j��������Ă������H
		if(k_code == E_key_sw5){					//SW5? ���Z�H
			PV_LOTCT1_B4 --;						//���b�g�J�E���^�P�����l���Z
			KAT_DATCHG_FLG = 0xff;					//�J�E���^�l�ύX�t���O
			if(SV_PUR1SV_B4 <= PV_LOTCT1_B4){
				PV_LOTCT1_B4 = 0;
				KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
			}
		}
		else{
			PV_LOTCT1_B4 ++;						//���b�g�J�E���^�P�����l���Z
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			if(SV_PUR1SV_B4 <= PV_LOTCT1_B4){
				PV_LOTCT1_B4 = SV_PUR1SV_B4;
				KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
			}
		}
		ROTTO_chk();								//ۯĶ��� ���� ����
	}
	else if(SW14_ON1_FLG == 4){						//���b�g�J�E���^��������Ă������H
		if(k_code == E_key_sw5){					//SW5?
			SWchg_ent();							//SW CHG �f�[�^ ENT
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			if( 00 == (SEQ_032_SV & BIT_3)){
				SEQ_PAR_033 &= ~BIT_1;				//ۯĶ���2 ����UP(1:����UP)
			}
		}
		else{
			PV_LOTCT2_B41 = 0;						//���b�g�J�E���^2�����l�N���A
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			SEQ_PAR_033 &= ~BIT_1;					//ۯĶ���2 ����UP(1:����UP)
		}
	}
	else if(SW14_ON1_FLG == 0x84){					//�����b�g�J�E���^�i�J�E���^�␳�j��������Ă������H
		if(k_code == E_key_sw5){					//SW5? ���Z�H
			PV_LOTCT2_B41 --;						//���b�g�J�E���^2�����l���Z
			KAT_DATCHG_FLG = 0xff;					//�J�E���^�l�ύX�t���O
			if(SV_PUR2SV_B41 <= PV_LOTCT2_B41){
				PV_LOTCT2_B41 = 0;
				KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
			}
		}
		else{
			PV_LOTCT2_B41 ++;						//���b�g�J�E���^2�����l���Z
			KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
			if(SV_PUR2SV_B41 <= PV_LOTCT2_B41){
				PV_LOTCT2_B41 = SV_PUR2SV_B41;
				KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
			}
		}
		ROTTO_chk();								//ۯĶ��� ���� ����
	}
	else if(SW14_ON1_FLG == 5){					//	V01w(INS)
		if(k_code == E_key_sw5){					//SW5?
			if ( (SV_OVERLIDE_COF-1) >= 1 ) {
				SV_OVERLIDE_COF--;
				dat = SV_OVERLIDE_COF;
				t_no = SV_TBL_POS_NOW;
				SVPV_data_disp(dat, &SV_buff[t_no], 0, 0);		//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
				SVSW_CHG_FLG |= 0x0004;
			}
		}
		else{
			if ( (SV_OVERLIDE_COF+1) <= 100 ) {
				SV_OVERLIDE_COF++;
				dat = SV_OVERLIDE_COF;
				t_no = SV_TBL_POS_NOW;
				SVPV_data_disp(dat, &SV_buff[t_no], 0, 0);		//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
				SVSW_CHG_FLG |= 0x0004;
			}
		}
	}
	else if(SW14_ON1_FLG == 0){						//2014/09/02
		if(k_code == E_key_sw5){					//SW5?
			SEQ_PAR_056 |= cBIT15;
		}
		else {
			SEQ_PAR_056 |= cBIT12;
		}
	}
	else{
		return;
	}

	FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	SW16data_onset(0xff, k_code+2 );						//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
	Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��
	Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��

}


/*
********************************************************************************
*  Module Name:		sw56_window_02
*  Function Name:	���Y[�P�x�ݒ�]��SW5�6�̏���
*  Input	:		������
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-05
********************************************************************************
*/
void	sw56_window_02(UNs k_code)
{

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//������?
		SW16data_onset(0x00, 7);						//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		SW16data_onset(0x00, 8);						//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
	}
	else{
		if(k_code == E_key_sw5){						//SW5?
			if(KIDO_FLG_SV != 0){
				KIDO_FLG_SV --;
			}
			SVdata_disp();								//�ݒ�l���@�\��
			SWchg_disp();								//�r�v�f�[�^���@�\��
			SW16data_onset(0xff, 7);					//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		}
		else{											//SW6
			KIDO_FLG_SV ++;

			SVdata_disp();								//�ݒ�l���@�\��
			SWchg_disp();								//�r�v�f�[�^���@�\��
			SW16data_onset(0xff, 8);					//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		}
		kido_data_set();								//�P�x�\�� & �f�[�^�쐬

		FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	}
	Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
}


/*
********************************************************************************
*  Module Name:		kido_data_set
*  Function Name:	�P�x�\�� & �f�[�^�쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-05
********************************************************************************
*/
void	kido_data_set(void)
{
	UNs	i,j;

	if(KIDO_FLG_SV > 15) {
		KIDO_FLG_SV = 15;
	}

	i = KIDO_FLG_SV + 1;
	for( j = 0 ; i > 0 ; i--){
		j <<= 1;
		j |= 0x0001;
	}
	KIDO_FLG_FLG = j;

	KIDO_FLG_PV = KIDO_FLG_SV + 1;

	Lcd_contrast_chage(KIDO_FLG_SV);				//LCD�P�x�ݒ�
}


/*
********************************************************************************
*  Module Name:		mmon_kaiten_chg
*  Function Name:	��]�����ɂ��ݒ�l �؊���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-10-07
********************************************************************************
*/
void	mmon_kaiten_chg(void)
{
	UNl		long_bf;
	UNs		t_no;

	mmon_trans_get();								//��]�����ɂ���ް��̎擾

	if( SV_CNT == 00 ){
		return;
	}

	if( SEQ_050_SV & BIT_1 ){						//���]�@�H
		t_no = grpno_sv_srch(86);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(87);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(88);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(89);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		t_no = grpno_sv_srch(90);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(107);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(108);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(109);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(110);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		/* V01d */
		t_no = grpno_sv_srch(111);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 54;

		// �����ݒ��\��  2014/08/20
		t_no = grpno_sv_srch(117);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��		����
		SV_buff[t_no].SUB_NO |= BIT_F;				//��\�����
		CSR_buff[4].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
		PV_buff[3].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�

		// �␳�ݒ��\��  2014/08/20
		t_no = grpno_sv_srch(118);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��		�␳
		SV_buff[t_no].SUB_NO |= BIT_F;				//��\�����
		CSR_buff[5].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
		SW_buff[4].SUB_NO |= BIT_F;					//������/�� ��\���̐ݒ�
		PV_buff[4].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�
	}
	else{
		t_no = grpno_sv_srch(86);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
//V01j		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(87);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//V01d		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO &= 0x8000;				//�ԈႦ�ĺ��Ăɂ��Ă��܂����̂𕜊�  V01h_b
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(88);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(89);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		t_no = grpno_sv_srch(90);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
//V01d		SV_buff[t_no].SUB_NO |= 55;
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(107);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(108);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(109);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(110);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 74;

		/* V01d */
		t_no = grpno_sv_srch(111);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
		SV_buff[t_no].SUB_NO &= 0x8000;				//���ٰ�ݔԍ�
		SV_buff[t_no].SUB_NO |= 74;

		// �����ݒ�\��  2014/08/20
		t_no = grpno_sv_srch(117);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��		����
		SV_buff[t_no].SUB_NO &= ~BIT_F;				//�\�����
		CSR_buff[4].TOK_NO &= ~BIT_0;				//���ٕ\���̐ݒ�
		PV_buff[3].SUB_NO &= ~BIT_F;				//�P�ʕ\���̐ݒ�

		// �␳�ݒ�\��  2014/08/20
		t_no = grpno_sv_srch(118);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��		�␳
		SV_buff[t_no].SUB_NO &= ~BIT_F;				//�\�����
		CSR_buff[5].TOK_NO &= ~BIT_0;				//���ٕ\���̐ݒ�
		SW_buff[4].SUB_NO &= ~BIT_F;				//������/�� �\���̐ݒ�
		PV_buff[4].SUB_NO &= ~BIT_F;				//�P�ʕ\���̐ݒ�
	}

	grpno_sv_open(85);								//�ݒ�l���ð��ق̕\�� �ݒ�(�ҋ@�p)
	grpno_sv_open(91);								//�ݒ�l���ð��ق̕\�� �ݒ�(�ҋ@�ʒu)

#if (mot100_test == 1)
#else
	csrno_sv_open(2);								//�ݒ�l���ð��ق̕\�� �ݒ�(�s��)	V06m
	CSR_opn_tokusyu(97, 92);						//1�i�ڒ�~���Ԃ̶��ٕ\��		V06m
	CSR_opn_tokusyu(102, 99);						//�߂葬�x�̶��ٕ\��			V06m
#endif

	mmon_tchk_disp(0xff);							//Ӱ��݉�ʗp���ð��ق�����&�\��


	if( SEQ_050_SV & (BIT_0 | BIT_3) ){				//��]�^�㉝���@�H
		grpno_sv_cls(85);							//�ݒ�l���ð��ق̔�\�� �ݒ�(�ҋ@�p)
		grpno_sv_cls(91);							//�ݒ�l���ð��ق̔�\�� �ݒ�(�ҋ@�ʒu)
	}

	if (SEQ_050_SV & BIT_2) {						//V06m
		if (GMN_PAR021 == 1) {
			csrno_sv_cls(2);						//�ݒ�l���ð��ق̔�\�� �ݒ�(�s��)
			CSR_cls_tokusyu(97, 92);				//1�i�ڒ�~���Ԃ̶��ٔ�\��
			CSR_cls_tokusyu(102, 99);				//�߂葬�x�̶��ٔ�\��
		}
	}

	mmon_trans_put();								//��]�����ɂ���ް��̊i�[

}


/*
********************************************************************************
*  Module Name:		mmon_taiki_chg
*  Function Name:	�ҋ@�p���͕ύX
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-30
********************************************************************************
*/
//void	mmon_taiki_chg(void)
//{
//	UNl		long_bf;
//	UNs		t_no;
//
//	if( SV_CNT == 00 ){
//		return;
//	}
//
//	if(SV_TAIKIKAKU_SRV != 0){
//		SV_TAIKIKAKU_SRV_BAK = SV_TAIKIKAKU_SRV;			//�ҋ@�p�̊i�[
//		SV_TAIKIPOS_SRV_BAK = SV_TAIKIPOS_SRV;				//�ҋ@�ʒu�̊i�[
//	}
//
//	if( SEQ_050_SV & (BIT_0 | BIT_3) ){						//��]�@�㉝���@�H
//
//		SV_TAIKIKAKU_SRV = 0;								//�ҋ@�p = 0
//		t_no = grpno_sv_srch(85);							//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//
//		long_bf = SV_TAIKIKAKU_SRV;							//�ҋ@�p�̕\��
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
//
//		mmon_sv_chg(t_no);									//�p�x&�ʒu�̐ݒ�l�ύX�i�ҋ@�ʒu�̕\���j
//
//		grpno_sv_cls(85);									//�ݒ�l���ð��ق̔�\�� �ݒ�(�ҋ@�p)
//		grpno_sv_cls(91);									//�ݒ�l���ð��ق̔�\�� �ݒ�(�ҋ@�ʒu)
//	}
//	else {													//NO
//		grpno_sv_open(85);									//�ݒ�l���ð��ق̕\�� �ݒ�(�ҋ@�p)
//		grpno_sv_open(91);									//�ݒ�l���ð��ق̕\�� �ݒ�(�ҋ@�ʒu)
//
//		SV_TAIKIKAKU_SRV = SV_TAIKIKAKU_SRV_BAK;			//�ҋ@�p�̕���
//		t_no = grpno_sv_srch(85);							//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		long_bf = SV_TAIKIKAKU_SRV;							//�ҋ@�p�̕\��
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
//
//		SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV_BAK;				//�ҋ@�ʒu����
//		t_no = grpno_sv_srch(91);							//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		long_bf = SV_TAIKIPOS_SRV;							//�ҋ@�ʒu�̕\��
//		SVPV_data_disp(long_bf, &SV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
//	}
//
//	if( SEQ_050_SV & BIT_1 ){							//���]�@�H
//		t_no = grpno_sv_srch(86);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(87);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(88);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(89);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 54;
//
//		t_no = grpno_sv_srch(90);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 54;
//	}
//	else{
//		t_no = grpno_sv_srch(86);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(87);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(88);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(89);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 55;
//
//		t_no = grpno_sv_srch(90);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
//		SV_buff[t_no].SUB_NO &= 0x8000;					//���ٰ�ݔԍ�
//		SV_buff[t_no].SUB_NO |= 55;
//	}
//
//}


/*
********************************************************************************
*  Module Name:		mmon_sv_chg
*  Function Name:	�p�x&�ʒu�̐ݒ�l�ύX
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:�p�x���ʒu�̐ݒ�l�ύX�A���� �ʒu���p�x�̐ݒ�l�ύX���s���B
*
*  �� ��	:FIT)�c�[		ON:2002-07-24
********************************************************************************
*/
void	mmon_sv_chg( UNs t_no )
{
	UNl		long_bf;
	UNs		i;
#if (mot100_test == 1)
	UNs		*deg, *inf, bit, step;
	UNl		*pos;
#endif

	if( SV_CNT == 00 ){
		return;
	}

	long_bf = 0;

	i = SV_buff[t_no].GRP_NO;											//��ٰ�ߔԍ�
	switch( i ) {
		case 85:				//Ӱ��݉�ʁ@�ҋ@�p
			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
			}
			SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)

			long_bf = SV_TAIKIPOS_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			break;

		case 86:				//Ӱ��݉�ʁ@�ڕW�p1
#if (mot100_test == 1)
			deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG1;
			pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS1;

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				*pos = DigRnaChange1(*deg);									//�p�x��mm�ϊ�

				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					*pos = *pos - SV_NEG_OFS_LNG;
				}

				*pos = cnv_mm_inch(*pos, 0);								//�P�ʐؑ�(mm��mm/INCH)
			}
#else
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_1DANPOS_SRV = DigRnaChange1(SV_1DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_1DANPOS_SRV = SV_1DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_1DANPOS_SRV	= cnv_mm_inch(SV_1DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}
#endif

#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 0;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {						//�ڕW�͈ʒu�H
				long_bf = *pos;					//�ʒu�X�V�i�ʒu�͊p�x�ύX�ɂĂ���čX�V���ꂽ����j

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();												//�ݒ�l���ٕ\��
			}
//2015/11/15			mmon_deg_chg_uphold1(t_no, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
			mmon_deg_chg_uphold100(step, deg, pos);
#else
//2015/01/15
////			long_bf = SV_1DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_0)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12

				long_bf = SV_1DANPOS_SRV;

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			mmon_deg_chg_uphold1(t_no, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
#endif
			break;

		case 87:				//Ӱ��݉�ʁ@�ڕW�p2
#if (mot100_test == 1)
			deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG2;
			pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS2;

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				*pos = DigRnaChange1(*deg);									//�p�x��mm�ϊ�

				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					*pos = *pos - SV_NEG_OFS_LNG;
				}

				*pos = cnv_mm_inch(*pos, 0);								//�P�ʐؑ�(mm��mm/INCH)
			}
#else
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_2DANPOS_SRV = DigRnaChange1(SV_2DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_2DANPOS_SRV = SV_2DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_2DANPOS_SRV	= cnv_mm_inch(SV_2DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}
#endif

#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 1;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {						//�ڕW�͈ʒu�H
				long_bf = *pos;					//�ʒu�X�V�i�ʒu�͊p�x�ύX�ɂĂ���čX�V���ꂽ����j

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();												//�ݒ�l���ٕ\��
			}
//2015/11/15			mmon_deg_chg_uphold1(t_no, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
			mmon_deg_chg_uphold100(step, deg, pos);
#else
//2015/01/15
////			long_bf = SV_2DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_1)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12

				long_bf = SV_2DANPOS_SRV;

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			mmon_deg_chg_uphold1(t_no, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
#endif
			break;

		case 88:				//Ӱ��݉�ʁ@�ڕW�p3
#if (mot100_test == 1)
			deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG3;
			pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS3;

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				*pos = DigRnaChange1(*deg);									//�p�x��mm�ϊ�

				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					*pos = *pos - SV_NEG_OFS_LNG;
				}

				*pos = cnv_mm_inch(*pos, 0);								//�P�ʐؑ�(mm��mm/INCH)
			}
#else
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_3DANPOS_SRV = DigRnaChange1(SV_3DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_3DANPOS_SRV = SV_3DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_3DANPOS_SRV	= cnv_mm_inch(SV_3DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}
#endif

#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 2;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {						//�ڕW�͈ʒu�H
				long_bf = *pos;					//�ʒu�X�V�i�ʒu�͊p�x�ύX�ɂĂ���čX�V���ꂽ����j

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();												//�ݒ�l���ٕ\��
			}
//2015/11/15			mmon_deg_chg_uphold1(t_no, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
			mmon_deg_chg_uphold100(step, deg, pos);
#else
//2015/01/15
////			long_bf = SV_3DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_2)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12

				long_bf = SV_3DANPOS_SRV;

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			mmon_deg_chg_uphold1(t_no, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
#endif
			break;

		case 89:				//Ӱ��݉�ʁ@�ڕW�p4
#if (mot100_test == 1)
			deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG4;
			pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS4;

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				*pos = DigRnaChange1(*deg);									//�p�x��mm�ϊ�

				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					*pos = *pos - SV_NEG_OFS_LNG;
				}

				*pos = cnv_mm_inch(*pos, 0);								//�P�ʐؑ�(mm��mm/INCH)
			}
#else
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_4DANPOS_SRV = DigRnaChange1(SV_4DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_4DANPOS_SRV = SV_4DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_4DANPOS_SRV	= cnv_mm_inch(SV_4DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}
#endif

#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 3;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {						//�ڕW�͈ʒu�H
				long_bf = *pos;					//�ʒu�X�V�i�ʒu�͊p�x�ύX�ɂĂ���čX�V���ꂽ����j

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();												//�ݒ�l���ٕ\��
			}
//2015/11/15			mmon_deg_chg_uphold1(t_no, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
			mmon_deg_chg_uphold100(step, deg, pos);
#else
//2015/01/15
////			long_bf = SV_4DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_3)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12

				long_bf = SV_4DANPOS_SRV;

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			mmon_deg_chg_uphold1(t_no, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
#endif
			break;

		case 90:				//Ӱ��݉�ʁ@�ڕW�p5
#if (mot100_test == 1)
			deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG5;
			pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS5;
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				*pos = DigRnaChange1(*deg);									//�p�x��mm�ϊ�

				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					*pos = *pos - SV_NEG_OFS_LNG;
				}

				*pos = cnv_mm_inch(*pos, 0);								//�P�ʐؑ�(mm��mm/INCH)
			}
#else
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_5DANPOS_SRV = DigRnaChange1(SV_5DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_5DANPOS_SRV = SV_5DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_5DANPOS_SRV	= cnv_mm_inch(SV_5DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}
#endif

#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 4;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {						//�ڕW�͈ʒu�H
				long_bf = *pos;					//�ʒu�X�V�i�ʒu�͊p�x�ύX�ɂĂ���čX�V���ꂽ����j

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();												//�ݒ�l���ٕ\��
			}
//2015/11/15			mmon_deg_chg_uphold1(t_no, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
			mmon_deg_chg_uphold100(step, deg, pos);
#else
//2015/01/15
////			long_bf = SV_5DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_4)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12

				long_bf = SV_5DANPOS_SRV;

				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			mmon_deg_chg_uphold1(t_no, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
#endif
			break;

		/* V01d */
		case 107:				//Ӱ��݉�ʁ@�ڕW�p6
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_6DANPOS_SRV = DigRnaChange1(SV_6DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_6DANPOS_SRV = SV_6DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_6DANPOS_SRV	= cnv_mm_inch(SV_6DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}

//2015/01/15
////			long_bf = SV_6DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_5)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12
				long_bf = SV_6DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}

			mmon_deg_chg_uphold2(t_no, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, 4);	/* V01d */
			break;

		/* V01d */
		case 108:				//Ӱ��݉�ʁ@�ڕW�p7
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_7DANPOS_SRV = DigRnaChange1(SV_7DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_7DANPOS_SRV = SV_7DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_7DANPOS_SRV	= cnv_mm_inch(SV_7DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}

//2015/01/15
////			long_bf = SV_7DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_6)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12
				long_bf = SV_7DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}

			mmon_deg_chg_uphold2(t_no, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, 3);	/* V01d */
			break;

		/* V01d */
		case 109:				//Ӱ��݉�ʁ@�ڕW�p8
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_8DANPOS_SRV = DigRnaChange1(SV_8DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_8DANPOS_SRV = SV_8DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_8DANPOS_SRV	= cnv_mm_inch(SV_8DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}

//2015/01/15
////			long_bf = SV_8DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_7)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12
				long_bf = SV_8DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}

			mmon_deg_chg_uphold2(t_no, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, 2);	/* V01d */
			break;

		/* V01d */
		case 110:				//Ӱ��݉�ʁ@�ڕW�p9
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_9DANPOS_SRV = DigRnaChange1(SV_9DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_9DANPOS_SRV = SV_9DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_9DANPOS_SRV	= cnv_mm_inch(SV_9DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}

//2015/01/15
////			long_bf = SV_9DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_8)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12
				long_bf = SV_9DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}

			mmon_deg_chg_uphold2(t_no, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, &SV_10DANDEG_SRV, &SV_10DANPOS_SRV, 1);	/* V01d */
			break;

		/* V01d */
		case 111:				//Ӱ��݉�ʁ@�ڕW�p10
			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_10DANPOS_SRV = DigRnaChange1(SV_10DANDEG_SRV);				//�p�x��mm�ϊ�

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					SV_10DANPOS_SRV = SV_10DANPOS_SRV - SV_NEG_OFS_LNG;
				}

				SV_10DANPOS_SRV	= cnv_mm_inch(SV_10DANPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
			}

//2015/01/15
////			long_bf = SV_10DANPOS_SRV;
////			SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			if ( ( (SEQ_050_SV & BIT_1)==0 ) || 
				 ( (SEQ_050_SV & BIT_1) && ((SV_MOTOBJ_INF1 & BIT_9)==0) ) ) {		//���]�ŖڕW�������̏ꍇ�͕\��	2014/03/12
				long_bf = SV_10DANPOS_SRV;
				SVPV_data_disp(long_bf, &SV_buff[t_no+1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				SV_csr_set();							//�ݒ�l���ٕ\��
			}
			break;

		case 91:				//Ӱ��݉�ʁ@�ҋ@�ʒu
			long_bf = cnv_inch_mm(SV_TAIKIPOS_SRV, 0);						//�P�ʐؑ�(mm/INCH��mm)

//koma 2014-08-11			/* V00m */
//koma 2014-08-11			if(SEQ_050_SV & BIT_1) {		//���]�@�H
//koma 2014-08-11				long_bf = long_bf + SV_NEG_OFS_LNG;
//koma 2014-08-11			}
//koma 2014-08-11			SV_TAIKIKAKU_SRV = RnaDigChange1(SV_TAIKIKAKU_SRV, long_bf);	//mm�ϊ����p�x

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
				SV_TAIKIKAKU_SRV = RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//2014-08-11 koma mm�ϊ����p�x
														//SV_DNAREA_JUDG�͂ǂ�Ȏ��ł����~�̈�(�E�����̐ݒ�)
														//
			}else{
				if(SEQ_050_SV & BIT_2) {//2014-08-19 �ӂ肱
					SV_TAIKIKAKU_SRV = RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm�ϊ����p�x[�ҋ@�_�͕K���E����]
				}else{
					SV_TAIKIKAKU_SRV = RnaDigChange1(SV_TAIKIKAKU_SRV, long_bf);	//mm�ϊ����p�x
				}
			
			}

			long_bf = SV_TAIKIKAKU_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			break;

		case 92:				//Ӱ��݉�ʁ@�ڕW�ʒu1 or �ڕW�׏d1
#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 0;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {												//�ڕW�ʒu�ύX�H
//2015/11/12
////				long_bf = cnv_inch_mm(SV_1DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)
				pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS1;
				long_bf = cnv_inch_mm(*pos, 0);									//�P�ʐؑ�(mm/INCH��mm)

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					long_bf = long_bf + SV_NEG_OFS_LNG;
				}

				deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG1;						//2015/11/12
				if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
//2015/11/12
////					SV_1DANDEG_SRV = RnaDigChange1(SV_1DANDEG_SRV, long_bf);	//mm�ϊ����p�x
					*deg = RnaDigChange1(*deg, long_bf);						//mm�ϊ����p�x
				}

//2015/11/12
////				long_bf = SV_1DANDEG_SRV;
				long_bf = *deg;
				SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

//2015/11/15				mmon_deg_chg_uphold1(t_no-1, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
				mmon_deg_chg_uphold100(step, deg, pos);
			}
#else
			long_bf = cnv_inch_mm(SV_1DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_1DANDEG_SRV = RnaDigChange1(SV_1DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_1DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold1(t_no-1, &SV_1DANDEG_SRV, &SV_1DANPOS_SRV, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, 9);	/* V01d */
#endif
			break;

		case 93:				//Ӱ��݉�ʁ@�ڕW�ʒu2 or �ڕW�׏d2
#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 1;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {												//�ڕW�ʒu�ύX�H
//2015/11/12
////				long_bf = cnv_inch_mm(SV_2DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)
				pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS2;
				long_bf = cnv_inch_mm(*pos, 0);									//�P�ʐؑ�(mm/INCH��mm)

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					long_bf = long_bf + SV_NEG_OFS_LNG;
				}

				deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG2;						//2015/11/12
				if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
//2015/11/12
////					SV_2DANDEG_SRV = RnaDigChange1(SV_2DANDEG_SRV, long_bf);	//mm�ϊ����p�x
					*deg = RnaDigChange1(*deg, long_bf);						//mm�ϊ����p�x
				}

//2015/11/12
////				long_bf = SV_2DANDEG_SRV;
				long_bf = *deg;
				SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

//2015/11/15				mmon_deg_chg_uphold1(t_no-1, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
				mmon_deg_chg_uphold100(step, deg, pos);
			}
#else
			long_bf = cnv_inch_mm(SV_2DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_2DANDEG_SRV = RnaDigChange1(SV_2DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_2DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold1(t_no-1, &SV_2DANDEG_SRV, &SV_2DANPOS_SRV, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, 8);	/* V01d */
#endif
			break;

		case 94:				//Ӱ��݉�ʁ@�ڕW�ʒu3 or �ڕW�׏d3
#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 2;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {												//�ڕW�ʒu�ύX�H
//2015/11/12
////				long_bf = cnv_inch_mm(SV_3DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)
				pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS3;
				long_bf = cnv_inch_mm(*pos, 0);									//�P�ʐؑ�(mm/INCH��mm)

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					long_bf = long_bf + SV_NEG_OFS_LNG;
				}

				deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG3;						//2015/11/12
				if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
//2015/11/12
////					SV_3DANDEG_SRV = RnaDigChange1(SV_3DANDEG_SRV, long_bf);	//mm�ϊ����p�x
					*deg = RnaDigChange1(*deg, long_bf);						//mm�ϊ����p�x
				}

//2015/11/12
////				long_bf = SV_3DANDEG_SRV;
				long_bf = *deg;
				SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

//2015/11/15				mmon_deg_chg_uphold1(t_no-1, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
				mmon_deg_chg_uphold100(step, deg, pos);
			}
#else
			long_bf = cnv_inch_mm(SV_3DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_3DANDEG_SRV = RnaDigChange1(SV_3DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_3DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold1(t_no-1, &SV_3DANDEG_SRV, &SV_3DANPOS_SRV, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, 7);	/* V01d */
#endif
			break;

		case 95:				//Ӱ��݉�ʁ@�ڕW�ʒu4 or �ڕW�׏d4
#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 3;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {												//�ڕW�ʒu�ύX�H
//2015/11/12
////				long_bf = cnv_inch_mm(SV_4DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)
				pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS4;
				long_bf = cnv_inch_mm(*pos, 0);									//�P�ʐؑ�(mm/INCH��mm)

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					long_bf = long_bf + SV_NEG_OFS_LNG;
				}

				deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG4;						//2015/11/12
				if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
//2015/11/12
////					SV_4DANDEG_SRV = RnaDigChange1(SV_4DANDEG_SRV, long_bf);	//mm�ϊ����p�x
					*deg = RnaDigChange1(*deg, long_bf);						//mm�ϊ����p�x
				}

//2015/11/12
////				long_bf = SV_4DANDEG_SRV;
				long_bf = *deg;
				SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

//2015/11/15				mmon_deg_chg_uphold1(t_no-1, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
				mmon_deg_chg_uphold100(step, deg, pos);
			}
#else
			long_bf = cnv_inch_mm(SV_4DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_4DANDEG_SRV = RnaDigChange1(SV_4DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_4DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold1(t_no-1, &SV_4DANDEG_SRV, &SV_4DANPOS_SRV, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, 6);	/* V01d */
#endif
			break;

		case 96:				//Ӱ��݉�ʁ@�ڕW�ʒu5 or �ڕW�׏d5
#if (mot100_test == 1)
			step = (SV_MOT_PAGE * 5) + 4;
			i = step_pos_prs_chk(step);
			if ( i == 0 ) {												//�ڕW�ʒu�ύX�H
//2015/11/12
////				long_bf = cnv_inch_mm(SV_5DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)
				pos = MOT_PAGE_DAT[SV_MOT_PAGE].POS5;
				long_bf = cnv_inch_mm(*pos, 0);									//�P�ʐؑ�(mm/INCH��mm)

				/* V00m */
				if(SEQ_050_SV & BIT_1) {		//���]�@�H
					long_bf = long_bf + SV_NEG_OFS_LNG;
				}

				deg = MOT_PAGE_DAT[SV_MOT_PAGE].DEG5;						//2015/11/12
				if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
//2015/11/12
////					SV_5DANDEG_SRV = RnaDigChange1(SV_5DANDEG_SRV, long_bf);	//mm�ϊ����p�x
					*deg = RnaDigChange1(*deg, long_bf);						//mm�ϊ����p�x
				}

//2015/11/12
////				long_bf = SV_5DANDEG_SRV;
				long_bf = *deg;
				SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

//2015//11/15				mmon_deg_chg_uphold1(t_no-1, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
				mmon_deg_chg_uphold100(step, deg, pos);
			}
#else
			long_bf = cnv_inch_mm(SV_5DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_5DANDEG_SRV = RnaDigChange1(SV_5DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_5DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold1(t_no-1, &SV_5DANDEG_SRV, &SV_5DANPOS_SRV, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, 5);	/* V01d */
#endif
			break;

		/* V01d */
		case 112:				//Ӱ��݉�ʁ@�ڕW�ʒu6
			long_bf = cnv_inch_mm(SV_6DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_6DANDEG_SRV = RnaDigChange1(SV_6DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_6DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold2(t_no-1, &SV_6DANDEG_SRV, &SV_6DANPOS_SRV, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, 4);	/* V01d */
			break;

		/* V01d */
		case 113:				//Ӱ��݉�ʁ@�ڕW�ʒu7
			long_bf = cnv_inch_mm(SV_7DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_7DANDEG_SRV = RnaDigChange1(SV_7DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_7DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold2(t_no-1, &SV_7DANDEG_SRV, &SV_7DANPOS_SRV, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, 3);	/* V01d */
			break;

		/* V01d */
		case 114:				//Ӱ��݉�ʁ@�ڕW�ʒu8
			long_bf = cnv_inch_mm(SV_8DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_8DANDEG_SRV = RnaDigChange1(SV_8DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_8DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold2(t_no-1, &SV_8DANDEG_SRV, &SV_8DANPOS_SRV, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, 2);	/* V01d */
			break;

		/* V01d */
		case 115:				//Ӱ��݉�ʁ@�ڕW�ʒu9
			long_bf = cnv_inch_mm(SV_9DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_9DANDEG_SRV = RnaDigChange1(SV_9DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_9DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)

			mmon_deg_chg_uphold2(t_no-1, &SV_9DANDEG_SRV, &SV_9DANPOS_SRV, &SV_10DANDEG_SRV, &SV_10DANPOS_SRV, 1);	/* V01d */
			break;

		/* V01d */
		case 116:				//Ӱ��݉�ʁ@�ڕW�ʒu10
			long_bf = cnv_inch_mm(SV_10DANPOS_SRV, 0);					//�P�ʐؑ�(mm/INCH��mm)

			/* V00m */
			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				long_bf = long_bf + SV_NEG_OFS_LNG;
			}

			if(MOTION_SV_CHG_CANCEL == 0) {			/* V01d */
				SV_10DANDEG_SRV = RnaDigChange1(SV_10DANDEG_SRV, long_bf);	//mm�ϊ����p�x
			}

			long_bf = SV_10DANDEG_SRV;
			SVPV_data_disp(long_bf, &SV_buff[t_no-1], 0, 0x01);			//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			break;
	}
	MOTION_SV_CHG_CANCEL = 0;	/* V01d */
	SV_csr_set();											//�ݒ�l���ٕ\��		2014/04/15
}


/*
********************************************************************************
*  Module Name:		mmon_deg_chg_uphold1
*  Function Name:	Ӱ���1�`5�p�x�̏㏸ΰ��ފp�x�������\��
*  Input	:		
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	: A.Shimamura		ON:2004-01-16
********************************************************************************
*/
void	mmon_deg_chg_uphold1(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt)
{
	UNl		long_bf1, long_bf2;
	UNs		i, b1;

//2014-04-16 koma	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
	{
//V01e		if(*nowdeg >= SV_UPHOLD_DIG)
		if(*nowdeg >= GMN_PAR003)
		{
			b1 = SV_DANSUU_SRV;
			if (b1 > 5)		b1 = 5;

			for(i=4; 0<cnt; cnt--,i+=4, nexdeg++, nexpos++)
			{
				if(*nexdeg < *nowdeg)
				{
					*nexdeg = *nowdeg;
					*nexpos = *nowpos;
					long_bf1 = *nexdeg;
					long_bf2 = *nexpos;
					if ( (10-cnt) < b1 )
					{
						SVPV_data_disp(long_bf1, &SV_buff[t_no+i], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
						SVPV_data_disp(long_bf2, &SV_buff[t_no+i+1], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
					}
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_deg_chg_uphold2
*  Function Name:	Ӱ���6�`10�p�x�̏㏸ΰ��ފp�x�������\��
*  Input	:		
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	: A.Shimamura		ON:2004-01-16
********************************************************************************
*/
void	mmon_deg_chg_uphold2(UNs t_no, UNs *nowdeg, UNl *nowpos, UNs *nexdeg, UNl *nexpos, UNs cnt)
{
	UNl		long_bf1, long_bf2;
	UNs		i, b1;

//2016-04-16	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma

	{
//V01e		if(*nowdeg >= SV_UPHOLD_DIG)
		if(*nowdeg >= GMN_PAR003)
		{
			b1 = SV_DANSUU_SRV - 5;

			for(i=4; 0<cnt; cnt--,i+=4, nexdeg++, nexpos++)
			{
				if(*nexdeg < *nowdeg)
				{
					*nexdeg = *nowdeg;
					*nexpos = *nowpos;
					long_bf1 = *nexdeg;
					long_bf2 = *nexpos;
					if ( (5-cnt) < b1 )
					{
						SVPV_data_disp(long_bf1, &SV_buff[t_no+i], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
						SVPV_data_disp(long_bf2, &SV_buff[t_no+i+1], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
					}
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_deg_chg_uphold1
*  Function Name:	Ӱ��݊p�x�̏㏸ΰ��ފp�x�������\��
*  Input	:		
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	: A.Shimamura		ON:2015/11/15
********************************************************************************
*/
void	mmon_deg_chg_uphold100(UNs step, UNs *deg, UNl *pos)
{
	UNl		pos0, pos1;
	UNs		deg0, deg1;

	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
	{
		if(*deg >= GMN_PAR003)
		{
			deg0 = *deg;
			pos0 = *pos;
			
			for(step++, deg++, pos++; step<SV_DANSUU_SRV; step++, deg++, pos++)
			{
				if(*deg < deg0)
				{
					*deg = deg0;
					*pos = pos0;
				}
			}
			SVdata_disp();
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_tchk_disp
*  Function Name:	Ӱ��݉�ʗp���ð��ق�����&�\��
*  Input	:		�׸ށF0���ʏ�\��
*						  0�������\��
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-02
********************************************************************************
*/
#if 0	/* V01d */
const	UNs	mmon_tchk_tbl[6][4]={				//�e�H���̏��ð��ق̸�ٰ�ߔԍ�
			{ 97, 86, 92,  6},
			{ 97, 86, 92,  6},						//�H���� 1
			{ 98, 87, 93,  7},						//�H���� 2
			{ 99, 88, 94,  8},						//�H���� 3
			{100, 89, 95,  9},						//�H���� 4
			{101, 90, 96, 10}						//�H���� 5
		};

void	mmon_tchk_disp(UNi flag)
{
	UNs		cnt, t_no, g_no;

	if( SV_CNT == 00 ){
		return;
	}

	if( SV_DANSUU_SRV  == 00 ){
		SV_DANSUU_SRV = 1;
	}
	else if( SV_DANSUU_SRV > 5 ){
		SV_DANSUU_SRV = 5;
	}

	if(SV_DANSUU_SRV != SV_DANSUU_SRV_BAK){			//�H���� �ω�����H
		if(SV_DANSUU_SRV > SV_DANSUU_SRV_BAK) {		//�H���� �ǉ��i�\���j
			t_no = SV_DANSUU_SRV_BAK + 1;
			for( cnt=SV_DANSUU_SRV_BAK ; cnt < SV_DANSUU_SRV ; cnt++, t_no++){
				g_no = mmon_tchk_tbl[t_no][0];						//���ð��ق̸�ٰ�ߔԍ�
				mmon_tbl_open(g_no);

				g_no = mmon_tchk_tbl[t_no][1];						//���ð��ق̸�ٰ�ߔԍ�
				grpno_sv_open(g_no);

				g_no = mmon_tchk_tbl[t_no][2];						//���ð��ق̸�ٰ�ߔԍ�
				grpno_sv_open(g_no);

				g_no = mmon_tchk_tbl[t_no][3];						//�s��
				Disp_line(GAMEN_NO, 0, 0, g_no);					//��ʕ\���p 1�s�\��
			}

//			SVdata_disp();							//�ݒ�l���@�\��
			flag = 0xff;							//�ݒ�l���@�\��
		}

		else{								//�H���� �폜�i�����j
			t_no = SV_DANSUU_SRV + 1;
			for( cnt=SV_DANSUU_SRV ; cnt < SV_DANSUU_SRV_BAK ; cnt++, t_no++){
				g_no = mmon_tchk_tbl[t_no][0];						//���ð��ق̸�ٰ�ߔԍ�
				mmon_tbl_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][1];						//���ð��ق̸�ٰ�ߔԍ�
				grpno_sv_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][2];						//���ð��ق̸�ٰ�ߔԍ�
				grpno_sv_cls(g_no);

				g_no = mmon_tchk_tbl[t_no][3];						//�s��
				g_no |= 0xa000;
				disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//�\���p�̈���w���ް��Őݒ�
				g_no &= 0x000f;
				Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//�\�s�\��
			}
		}

		SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;		//�H���� �Z�[�u
	}

	if(flag != 00){								//�\���H
		SVdata_disp();							//�ݒ�l���@�\��
	}

	SWCHG_DISP_ON_FLG = 0xff;					//�\��Ӱ��
	SWchg_disp();								//�r�v�f�[�^���@�\��
	SWCHG_DISP_ON_FLG = 0x00;					//��\��Ӱ��
}

#else

const	UNs	mmon_tchk_tbl1[7][4]={				//�e�H���̏��ð��ق̸�ٰ�ߔԍ�
			{ 97, 86, 92,  6},
			{ 97, 86, 92,  6},						//�H���� 1
			{ 98, 87, 93,  7},						//�H���� 2
			{ 99, 88, 94,  8},						//�H���� 3
			{100, 89, 95,  9},						//�H���� 4
			{101, 90, 96, 10},						//�H���� 5
			{102, 00, 00, 11}						//�H���� �߂�
		};

const	UNs	mmon_tchk_tbl2[7][4]={				//�e�H���̏��ð��ق̸�ٰ�ߔԍ�
			{ 97, 107, 112,  6},
			{ 97, 107, 112,  6},					//�H���� 6
			{ 98, 108, 113,  7},					//�H���� 7
			{ 99, 109, 114,  8},					//�H���� 8
			{100, 110, 115,  9},					//�H���� 9
			{101, 111, 116, 10},					//�H���� 10
			{102, 00, 00, 11}						//�H���� �߂�
		};

void	mmon_tchk_disp(UNi flag)
{
	UNs		cnt, t_no, g_no;
	UNs		dan;
	UNs		*tbl;

#if (mot100_test == 1)
	return;
#endif

	if( SV_CNT == 00 ){
		return;
	}

	if(SV_DANSUU_SRV != SV_DANSUU_SRV_BAK) {			//�H���� �ω�����H
		dan = SV_DANSUU_SRV;
		tbl = &mmon_tchk_tbl1[0][0];
		if( ((GAMEN_NO == 3) && (dan > 5))	||
			((GAMEN_NO == 28) && (dan > 5))		 )
		{
			dan = 5;
		}
		else if ( (GAMEN_NO == 6) || (GAMEN_NO == 30) )		// ���No.6 or ���No.30
		{
			if (dan > 5)	dan -= 5;
			else			dan = 0;
			tbl = &mmon_tchk_tbl2[0][0];
		}
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
		mmon_vabse_to_vmon2();						// ���[�V�������������[�N��
#endif
		for( cnt=0, t_no=1 ; cnt < dan ; cnt++, t_no++)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_open(g_no);
			g_no = *(tbl + (t_no * 4) + 1);
			grpno_sv_open(g_no);
			g_no = *(tbl + (t_no * 4) + 2);
			grpno_sv_open(g_no);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no = *(tbl + (t_no * 4) + 3);
			Disp_line(GAMEN_NO, 0, 0, g_no);					//��ʕ\���p 1�s�\��
#endif
		}
		for( ; cnt < 5 ; cnt++, t_no++)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 1);
			grpno_sv_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 2);
			grpno_sv_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 3);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no |= 0xa000;
			disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//�\���p�̈���w���ް��Őݒ�
			g_no &= 0x000f;
			Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//�\�s�\��
#else
			vmon2_line_erase(g_no);
#endif
		}

		if(	((GAMEN_NO == 3)  && (SV_DANSUU_SRV <= 5))	||
			((GAMEN_NO == 6)  && (SV_DANSUU_SRV > 5))	||
			((GAMEN_NO == 28) && (SV_DANSUU_SRV <= 5))	||
			((GAMEN_NO == 30) && (SV_DANSUU_SRV > 5))		)
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_open(g_no);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no = *(tbl + (t_no * 4) + 3);
			Disp_line(GAMEN_NO, 0, 0, g_no);					//��ʕ\���p 1�s�\��
#endif
		}
		else
		{
			g_no = *(tbl + (t_no * 4) + 0);
			mmon_tbl_cls(g_no);
			g_no = *(tbl + (t_no * 4) + 3);
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			g_no |= 0xa000;
			disp_memset(g_no, &LCD_WORK1[0][0][0], 0);			//�\���p�̈���w���ް��Őݒ�
			g_no &= 0x000f;
			Lcd_line(00, g_no, E_line_bf, &LCD_WORK1[0][0][0]);	//�\�s�\��
#else
//2015/01/15
////			vmon2_line_erase(g_no);
			if( (GAMEN_NO == 3) && (SV_DANSUU_SRV > 5) ) {
				vmon2_line_erase(g_no);								//�߂�s������
			}
			else if( (GAMEN_NO == 28) && (SV_DANSUU_SRV > 5) ) {
				disp_moji_s_paint(									//�߂�̉ӏ�������
					20,							//���p����
					320,						//X�n�_
					352-192,					//Y�n�_
					GAMENn_HEAD.scr_col,		//�h�ׂ��F
					0x0202,						//X2�{/Y2�{
					LCD_VMON2
					);
			}
#endif
		}

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
		if ( GGAMEN_DISP_FLG == 0 ) {
			mmon_vmon2_to_vram();						// ���[�V����������VRAM��
		}
#endif

		flag = 0xff;							//�ݒ�l���@�\��
		SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;		//�H���� �Z�[�u
	}

	if( (GAMEN_NO == 3) && (SV_DANSUU_SRV > 5) ) {
		SW_buff[16].SUB_NO |= BIT_F;			// �s�����\�����Ȃ�
	}
	else {
		SW_buff[16].SUB_NO &= ~BIT_F;			// �s�����\������B
	}

	if(flag != 00){								//�\���H
		if (SEQ_050_SV & BIT_0) {	//V06b
			//�ݒ�l�w�i�����i���͕s�j
			SV_col_chg(85, COL_BLACK, COL_WHITE, COL_WHITE);	//��]�̎��͏���p�̔w�i�𔒂ɂ���B	V06b
			SV_col_chg(91, COL_BLACK, COL_WHITE, COL_WHITE);	//��]�̎��͏���ʒu�̔w�i�𔒂ɂ���B	V06b
		}
		else{						//V06b
			//�ݒ�l�w�i�����F�i�ʏ�j
			SV_col_chg(85, COL_BLACK, COL_LBULE, COL_WHITE);	//���̑��͏���p�̔w�i�𐅐F�ɂ���B	V06b
			SV_col_chg(91, COL_BLACK, COL_LBULE, COL_WHITE);	//���̑��͏���ʒu�̔w�i�𐅐F�ɂ���B	V06b
		}

		if ( (SEQ_050_SV & BIT_2) && (GMN_PAR021==1) ) {	//V06m
			//�ݒ�l�w�i�����i���͕s�j
			SV_col_chg2( 2, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͍H���̔w�i�𔒂ɂ���B
			SV_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͂P�i�ڒ�~���Ԃ̔w�i�𔒂ɂ���B
			SV_col_chg2(27, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͖߂葬�x�̔w�i�𔒂ɂ���B
			SW_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͂P�i�ځu�u�v�̔w�i�𔒂ɂ���B

			CSR_cls_tokusyu(97, 92);							//1�i�ڒ�~���Ԃ̶��ٔ�\��
			if( ( (GAMEN_NO == 3) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO == 6) ||
				( (GAMEN_NO ==28) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO ==30) ) {		//V06p
				CSR_cls_tokusyu(102, 99);						//�߂葬�x�̶��ٔ�\��
			}
		}
		else{
			//�ݒ�l�w�i�����F�i�ʏ�j
			SV_col_chg2( 2, COL_BLACK, COL_LBULE, COL_WHITE);	//�U�q�̎��͍H���̔w�i�𐅐F�ɂ���B
			SV_col_chg2(10, COL_BLACK, COL_LBULE, COL_WHITE);	//�U�q�̎��͂P�i�ڒ�~���Ԃ̔w�i�𐅐F�ɂ���B
			SV_col_chg2(27, COL_BLACK, COL_LBULE, COL_WHITE);	//�U�q�̎��͖߂葬�x�̔w�i�𐅐F�ɂ���B
			SW_col_chg2(10, COL_BLACK, COL_LBULE, COL_WHITE);	//�U�q�̎��͂P�i�ځu�u�v�̔w�i�𔒂ɂ���B

			CSR_opn_tokusyu(97, 92);							//1�i�ڒ�~���Ԃ̶��ٕ\��
			if( ( (GAMEN_NO == 3) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO == 6) ||
				( (GAMEN_NO ==28) && (SV_DANSUU_SRV <= 5) ) || (GAMEN_NO ==30) ) {		//V06p
				CSR_opn_tokusyu(102, 99);						//�߂葬�x�̶��ٕ\��
			}
		}

//2014/08/20		SVdata_disp();							//�ݒ�l���@�\��
//2014/12/23		SVdata_disp1();							//�ݒ�l���@�\��
		SVdata_disp();							//�ݒ�l���@�\��

	}

//	�����ݒ�A�␳�ݒ�̕\���^��\��			2014/08/20
	Disp_Csr_Moji(4);							//�J�[�\���u�����v�\���^��\��
	Disp_Csr_Moji(5);							//�J�[�\���u�␳�v�\���^��\��
	Disp_SW(4);									//�X�C�b�`�u�␳��/�؁v�\���^�\��
	PVdata_disp1(3, 0);							//�����^�׏d�̒P�� �\���^�\��
	PVdata_disp1(4, 0);							//�␳�̒P�� �\���^�\��


	SWCHG_DISP_ON_FLG = 0xff;					//�\��Ӱ��
	SWchg_disp();								//�r�v�f�[�^���@�\��
	SWCHG_DISP_ON_FLG = 0x00;					//��\��Ӱ��
}
#endif


/*
********************************************************************************
*  Module Name:		mmon_sel_chk
*  Function Name:	Ӱ��݂̕����I������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-10-04
********************************************************************************
*/
void	mmon_sel_chk(void)
{
	UNi		j, k;
	UNs		i;

	k = 0;
	i = SEQ_050_SV;
	for( j=4 ; j > 0 ; j--, i>>=1 ) {
		if( i & BIT_0 ) {						//�����@����H
			k ++;								//�����@����{�P
		}
	}


	if( SEQ_050_SV & BIT_1 ) {					//�����I�������]�H
		if( 00 == (SEQ_024_SV & BIT_2) ) {		//���]�͗L��(0�F����)�H
			k = 0;								//�ُ�
		}
	}
	else if( SEQ_050_SV & BIT_2 ) {				//�����I�����������H
		if( 00 == (SEQ_023_SV & BIT_8) ) {		//�������͗L��(0�F����)�H
			k = 0;								//�ُ�
		}
	}
	else if( SEQ_050_SV & BIT_3 ) {				//�����I�����㉝���H
		if( 00 == (SEQ_023_SV & BIT_9) ) {		//�㉝���͗L��(0�F����)�H
			k = 0;								//�ُ�
		}
	}

	if( k == 0 || k >= 2 ) {					//�ُ�H
		SEQ_050_SV &= BIT_8;					//�����I���@�ر
		SEQ_050_SV |= BIT_0;					//�����I������]

		SVSW_CHG_FLG |= BIT_3;					//SEQ(���ݽ) �ް��i�[�׸޾��
	}
}


/*
********************************************************************************
*  Module Name:		mmon_trans_get
*  Function Name:	��]�����ɂ���ް��̎擾
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:��]�E���]�E�������E�㉝���@�̐ݒ�ɂ��F-RAM��ܰ� �ւ̓]��
*
*  �� ��	:FIT)�c�[		ON:2002-10-04
********************************************************************************
*/
void	mmon_trans_get(void)
{
	UNs		*dst_s, *src_s;
	UNl		*dst_l, *src_l;
	UNs		c;

	if( SEQ_050_SV & BIT_1 ) {								//���]�@�H

#if (mot100_test == 1)
		dst_s = &SV_1DANDEG_SRV;								//WORK
		src_s = &SV_MOTDEG1_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_1DANPOS_SRV;								//WORK
		src_l = &SV_MOTPOS1_001;								//FRAM
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_1DANSPD_SRV;								//WORK
		src_s = &SV_MOTSPD1_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_1DANTIM_SRV;								//WORK
		src_s = &SV_MOTTIM1_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_1DANPRS_SRV;								//WORK
		src_s = &SV_MOTPRS1_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		if (GMN_PAR048 != 1) {					//�׏d����L���H
			/* �׏d���䖳�� */
			SV_MOTTGT_INF0 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF1 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF2 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF3 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF4 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF5 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
			SV_MOTTGT_INF6 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		}
		else {
			dst_s = &SV_MOTTGT_INF0;								//WORK
			src_s = &SV_MOTTGT1_INF0;								//FRAM
			for (c=0; c<7; c++, dst_s++, src_s++) {
				*dst_s = *src_s;									/* �ڕW�ʒu�^�׏d�ؑ�BIT��� */
			}
		}

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD_INF0;									//WORK
		src_s = &SV_MOT_CSUD1_INF0;								//FRAM
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS_SRV	=	SV_1DANPOS1_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS1_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS1_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS1_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS1_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS1_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS1_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS1_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS1_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS1_SRV;				/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG1_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG1_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG1_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG1_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG1_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG1_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG1_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG1_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG1_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG1_SRV;				/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD1_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD1_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD1_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD1_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD1_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD1_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD1_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD1_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD1_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD1_SRV;				/* 10�i�ڈړ����x		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM1_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM1_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM1_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM1_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM1_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM1_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM1_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM1_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM1_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM1_SRV;				/* 10�i�ڒ�~����		*/
#endif
		SV_DANSUU_SRV	=	SV_DANSUU1_SRV;					/* �i��					*/

//2019-06-07		if (CB_SYS_PARAM045 == 1) {
//2019-06-07		}else {
//2019-06-07			SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU1_SRV;			/* �ҋ@�_�p�x			*/
//2019-06-07			SV_TAIKIPOS_SRV	=	SV_TAIKIPOS1_SRV;			/* �ҋ@�_�ʒu			*/
//2019-06-07		}
//koma 2019-06-07 ���]��param045�ɉe�����󂯂Ȃ�
		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU1_SRV;			/* �ҋ@�_�p�x			*/
		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS1_SRV;			/* �ҋ@�_�ʒu			*/



		SV_DAIHAITO_SRV	=	SV_DAIHAITO1_SRV;				/* �_�C�n�C�g			*/
		SV_HOASEI_SRV	=	SV_HOASEI1_SRV;					/* �␳�f�[�^			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD1_SRV;				/* ����x				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM1_SRV;				/* �ҋ@����				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN1_SRV;					/* �ҋ@�����͈�			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN1_SRV;					/* �ڕW�����͈�			*/

		SEQ_050_SV		&=	~BIT_8;							/* �␳�ر				*/
		SEQ_050_SV		|=	(SV_KAITEN1_SRV & BIT_8);		/* ��]����				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP1;					/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS1;						/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS1_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS1_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS1_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS1_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS1_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS1_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS1_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS1_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS1_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS1_SRV;				/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ_HAB	=	SV_KAJOBJ1_HAB;					/* �׏d�����͈�			*/

		SV0_MOT_UDSEL = 0;									//Ӱ��݉������I���@�\����	2016/04/19
	}

	else if( SEQ_050_SV & BIT_2 ) {							//�������@�H

#if (mot100_test == 1)
		dst_s = &SV_1DANDEG_SRV;								//WORK
		src_s = &SV_MOTDEG2_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_1DANPOS_SRV;								//WORK
		src_l = &SV_MOTPOS2_001;								//FRAM
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_1DANSPD_SRV;								//WORK
		src_s = &SV_MOTSPD2_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_1DANTIM_SRV;								//WORK
		src_s = &SV_MOTTIM2_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_1DANPRS_SRV;								//WORK
		src_s = &SV_MOTPRS2_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		SV_MOTTGT_INF0 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF1 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF2 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF3 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF4 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF5 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF6 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD_INF0;									//WORK
		src_s = &SV_MOT_CSUD2_INF0;								//FRAM
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS_SRV	=	SV_1DANPOS2_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS2_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS2_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS2_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS2_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS2_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS2_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS2_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS2_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS2_SRV;				/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG2_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG2_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG2_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG2_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG2_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG2_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG2_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG2_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG2_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG2_SRV;				/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD2_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD2_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD2_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD2_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD2_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD2_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD2_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD2_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD2_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD2_SRV;				/* 10�i�ڈړ����x		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM2_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM2_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM2_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM2_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM2_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM2_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM2_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM2_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM2_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM2_SRV;				/* 10�i�ڒ�~����		*/
#endif
		SV_DANSUU_SRV	=	SV_DANSUU2_SRV;					/* �i��					*/

//2019-06-07		if (CB_SYS_PARAM045 == 1) { 
//2019-06-07		}else {
//2019-06-07			SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU2_SRV;			/* �ҋ@�_�p�x			*/
//2019-06-07			SV_TAIKIPOS_SRV	=	SV_TAIKIPOS2_SRV;			/* �ҋ@�_�ʒu			*/
//2019-06-07		}
//koma 2019-06-07 �U�q��param045�ɉe�����󂯂Ȃ�

		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU2_SRV;			/* �ҋ@�_�p�x			*/
		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS2_SRV;			/* �ҋ@�_�ʒu			*/

		SV_DAIHAITO_SRV	=	SV_DAIHAITO2_SRV;				/* �_�C�n�C�g			*/
		SV_HOASEI_SRV	=	SV_HOASEI2_SRV;					/* �␳�f�[�^			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD2_SRV;				/* ����x				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM2_SRV;				/* �ҋ@����				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN2_SRV;					/* �ҋ@�����͈�			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN2_SRV;					/* �ڕW�����͈�			*/

		SEQ_050_SV		&=	~BIT_8;							/* �␳�ر				*/
		SEQ_050_SV		|=	(SV_KAITEN2_SRV & BIT_8);		/* ��]����				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP2;					/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS2;						/* �׏d�␳		V01m	*/

		if (GMN_PAR021 == 1) {						//V06m
			SV_DANSUU_SRV	= 1;					/* �i��					*/
			SV_1DANTIM_SRV	= 0;					/* 01�i�ڒ�~����		*/
			SV_TAIKSPD_SRV	= SV_1DANSPD_SRV;		/* �߂�ړ����x			*/
		}

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS2_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS2_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS2_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS2_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS2_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS2_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS2_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS2_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS2_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS2_SRV;				/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ_HAB	=	SV_KAJOBJ2_HAB;					/* �׏d�����͈�			*/

		SV0_MOT_UDSEL = 0;									//Ӱ��݉������I���@�\����	2016/04/19
	}

	else if( SEQ_050_SV & BIT_3 ) {							//�㉝���@�H

#if (mot100_test == 1)
		dst_s = &SV_1DANDEG_SRV;								//WORK
		src_s = &SV_MOTDEG3_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_1DANPOS_SRV;								//WORK
		src_l = &SV_MOTPOS3_001;								//FRAM
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_1DANSPD_SRV;								//WORK
		src_s = &SV_MOTSPD3_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_1DANTIM_SRV;								//WORK
		src_s = &SV_MOTTIM3_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_1DANPRS_SRV;								//WORK
		src_s = &SV_MOTPRS3_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		SV_MOTTGT_INF0 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF1 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF2 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF3 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF4 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF5 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF6 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD_INF0;									//WORK
		src_s = &SV_MOT_CSUD3_INF0;								//FRAM
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS_SRV	=	SV_1DANPOS3_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS3_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS3_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS3_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS3_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS3_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS3_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS3_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS3_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS3_SRV;				/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG3_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG3_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG3_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG3_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG3_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG3_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG3_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG3_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG3_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG3_SRV;				/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD3_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD3_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD3_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD3_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD3_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD3_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD3_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD3_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD3_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD3_SRV;				/* 10�i�ڈړ����x		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM3_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM3_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM3_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM3_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM3_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM3_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM3_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM3_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM3_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM3_SRV;				/* 10�i�ڒ�~����		*/
#endif
		SV_DANSUU_SRV	=	SV_DANSUU3_SRV;					/* �i��					*/
//		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS3_SRV;				/* �ҋ@�_�ʒu			*/
//		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU3_SRV;				/* �ҋ@�_�p�x			*/
		if (CB_SYS_PARAM045 == 1) { }	// V01i
		else {
			SV_TAIKIKAKU_SRV =	0;							/* �ҋ@�_�p�x			*/
//V06b			SV_TAIKIPOS_SRV	=	0;							/* �ҋ@�_�ʒu			*/
//2015/01/08			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);	//�p�x��mm�ϊ�
			SV_TAIKIPOS_SRV = cnv_mm_inch(DigRnaChange1(SV_TAIKIKAKU_SRV), 0);	//�p�x��mm�ϊ���inch�ϊ�
		}
		SV_DAIHAITO_SRV	=	SV_DAIHAITO3_SRV;				/* �_�C�n�C�g			*/
		SV_HOASEI_SRV	=	SV_HOASEI3_SRV;					/* �␳�f�[�^			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD3_SRV;				/* ����x				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM3_SRV;				/* �ҋ@����				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN3_SRV;					/* �ҋ@�����͈�			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN3_SRV;					/* �ڕW�����͈�			*/

		SEQ_050_SV		&=	~BIT_8;							/* �␳�ر				*/
		SEQ_050_SV		|=	(SV_KAITEN3_SRV & BIT_8);		/* ��]����				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP3;					/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS3;						/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS3_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS3_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS3_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS3_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS3_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS3_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS3_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS3_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS3_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS3_SRV;				/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ_HAB	=	SV_KAJOBJ3_HAB;					/* �׏d�����͈�			*/
	
		SV0_MOT_UDSEL = 0;									//Ӱ��݉������I���@�\����	2016/04/19
	}

	else {													//��]�@�H

#if (mot100_test == 1)
		dst_s = &SV_1DANDEG_SRV;								//WORK
		src_s = &SV_MOTDEG0_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_1DANPOS_SRV;								//WORK
		src_l = &SV_MOTPOS0_001;								//FRAM
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_1DANSPD_SRV;								//WORK
		src_s = &SV_MOTSPD0_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_1DANTIM_SRV;								//WORK
		src_s = &SV_MOTTIM0_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_1DANPRS_SRV;								//WORK
		src_s = &SV_MOTPRS0_001;								//FRAM
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		SV_MOTTGT_INF0 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF1 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF2 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF3 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF4 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF5 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
		SV_MOTTGT_INF6 = 0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD_INF0;									//WORK
		src_s = &SV_MOT_CSUD0_INF0;								//FRAM
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS_SRV	=	SV_1DANPOS0_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS_SRV	=	SV_2DANPOS0_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS_SRV	=	SV_3DANPOS0_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS_SRV	=	SV_4DANPOS0_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS_SRV	=	SV_5DANPOS0_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS_SRV	=	SV_6DANPOS0_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS_SRV	=	SV_7DANPOS0_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS_SRV	=	SV_8DANPOS0_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS_SRV	=	SV_9DANPOS0_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS_SRV	=	SV_10DANPOS0_SRV;				/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG_SRV	=	SV_1DANDEG0_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG_SRV	=	SV_2DANDEG0_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG_SRV	=	SV_3DANDEG0_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG_SRV	=	SV_4DANDEG0_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG_SRV	=	SV_5DANDEG0_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG_SRV	=	SV_6DANDEG0_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG_SRV	=	SV_7DANDEG0_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG_SRV	=	SV_8DANDEG0_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG_SRV	=	SV_9DANDEG0_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG_SRV	=	SV_10DANDEG0_SRV;				/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD_SRV	=	SV_1DANSPD0_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD_SRV	=	SV_2DANSPD0_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD_SRV	=	SV_3DANSPD0_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD_SRV	=	SV_4DANSPD0_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD_SRV	=	SV_5DANSPD0_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD_SRV	=	SV_6DANSPD0_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD_SRV	=	SV_7DANSPD0_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD_SRV	=	SV_8DANSPD0_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD_SRV	=	SV_9DANSPD0_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD_SRV	=	SV_10DANSPD0_SRV;				/* 10�i�ڈړ����x		*/

		SV_1DANTIM_SRV	=	SV_1DANTIM0_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM_SRV	=	SV_2DANTIM0_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM_SRV	=	SV_3DANTIM0_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM_SRV	=	SV_4DANTIM0_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM_SRV	=	SV_5DANTIM0_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM_SRV	=	SV_6DANTIM0_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM_SRV	=	SV_7DANTIM0_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM_SRV	=	SV_8DANTIM0_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM_SRV	=	SV_9DANTIM0_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM_SRV	=	SV_10DANTIM0_SRV;				/* 10�i�ڒ�~����		*/
#endif
		SV_DANSUU_SRV	=	SV_DANSUU0_SRV;					/* �i��					*/
//		SV_TAIKIPOS_SRV	=	SV_TAIKIPOS0_SRV;				/* �ҋ@�_�ʒu			*/
//		SV_TAIKIKAKU_SRV =	SV_TAIKIKAKU0_SRV;				/* �ҋ@�_�p�x			*/
		if (CB_SYS_PARAM045 == 1) { }	// V01i
		else {
			SV_TAIKIKAKU_SRV =	0;							/* �ҋ@�_�p�x			*/
//V06b			SV_TAIKIPOS_SRV	=	0;							/* �ҋ@�_�ʒu			*/
//2015/01/08			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);	//�p�x��mm�ϊ�
			SV_TAIKIPOS_SRV = cnv_mm_inch(DigRnaChange1(SV_TAIKIKAKU_SRV), 0);	//�p�x��mm�ϊ���inch�ϊ�
		}
		SV_DAIHAITO_SRV	=	SV_DAIHAITO0_SRV;				/* �_�C�n�C�g			*/
		SV_HOASEI_SRV	=	SV_HOASEI0_SRV;					/* �␳�f�[�^			*/

		SV_TAIKSPD_SRV	=	SV_TAIKSPD0_SRV;				/* ����x				*/
		SV_TAIKTIM_SRV	=	SV_TAIKTIM0_SRV;				/* �ҋ@����				*/
//		SV_TAIKAN_SRV	=	SV_TAIKAN0_SRV;					/* �ҋ@�����͈�			*/
		SV_MOKKAN_SRV	=	SV_MOKKAN0_SRV;					/* �ڕW�����͈�			*/

		SEQ_050_SV		&=	~BIT_8;							/* �␳�ر				*/
		SEQ_050_SV		|=	(SV_KAITEN0_SRV & BIT_8);		/* ��]����				*/

		SV_KAJYUU_OBJP = SV_KAJYUU_OBJP0;					/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS = SV_KAJYUU_PRS0;						/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS_SRV	=	SV_1DANPRS0_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS_SRV	=	SV_2DANPRS0_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS_SRV	=	SV_3DANPRS0_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS_SRV	=	SV_4DANPRS0_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS_SRV	=	SV_5DANPRS0_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS_SRV	=	SV_6DANPRS0_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS_SRV	=	SV_7DANPRS0_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS_SRV	=	SV_8DANPRS0_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS_SRV	=	SV_9DANPRS0_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS_SRV	=	SV_10DANPRS0_SRV;				/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ_HAB	=	SV_KAJOBJ0_HAB;					/* �׏d�����͈�			*/

		if (CB_SYS_PARAM375 == 2) {							//2016/04/19
			SV0_MOT_UDSEL = BIT_0;							//Ӱ��݉������I���@�\�L��
		}
		else {
			SV0_MOT_UDSEL = 0;								//Ӱ��݉������I���@�\����
		}
	}

#if (mot100_test == 1)
	SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;
#endif

	SVSW_CHG_FLG |= (BIT_2 | BIT_3);						//MOT(Ӱ���)/SEQ(���ݽ) �ް��i�[�׸޾��

}


/*
********************************************************************************
*  Module Name:		mmon_trans_put
*  Function Name:	��]�����ɂ���ް��̊i�[
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:��]�E���]�E�������E�㉝���@�̐ݒ�ɂ��ܰ���F-RAM �ւ̓]��
*
*  �� ��	:FIT)�c�[		ON:2002-10-04
********************************************************************************
*/
void	mmon_trans_put(void)
{
	UNs		*dst_s, *src_s;
	UNl		*dst_l, *src_l;
	UNs		c;

	if( SEQ_050_SV & BIT_0 ) {								//��]�@�H

#if (mot100_test == 1)
		dst_s = &SV_MOTDEG0_001;								//FRAM
		src_s = &SV_1DANDEG_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_MOTPOS0_001;								//FRAM
		src_l = &SV_1DANPOS_SRV;								//WORK
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_MOTSPD0_001;								//FRAM
		src_s = &SV_1DANSPD_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_MOTTIM0_001;								//FRAM
		src_s = &SV_1DANTIM_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_MOTPRS0_001;								//FRAM
		src_s = &SV_1DANPRS_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		dst_s = &SV_MOTTGT0_INF0;								//FRAM
		src_s = &SV_MOTTGT_INF0;								//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ڕW�ʒu�^�׏d�ؑ�BIT��� */
		}

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD0_INF0;								//FRAM
		src_s = &SV_MOT_CSUD_INF0;									//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS0_SRV		=	SV_1DANPOS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS0_SRV		=	SV_2DANPOS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS0_SRV		=	SV_3DANPOS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS0_SRV		=	SV_4DANPOS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS0_SRV		=	SV_5DANPOS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS0_SRV		=	SV_6DANPOS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS0_SRV		=	SV_7DANPOS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS0_SRV		=	SV_8DANPOS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS0_SRV		=	SV_9DANPOS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS0_SRV	=	SV_10DANPOS_SRV;			/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG0_SRV		=	SV_1DANDEG_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG0_SRV		=	SV_2DANDEG_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG0_SRV		=	SV_3DANDEG_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG0_SRV		=	SV_4DANDEG_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG0_SRV		=	SV_5DANDEG_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG0_SRV		=	SV_6DANDEG_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG0_SRV		=	SV_7DANDEG_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG0_SRV		=	SV_8DANDEG_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG0_SRV		=	SV_9DANDEG_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG0_SRV	=	SV_10DANDEG_SRV;			/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD0_SRV		=	SV_1DANSPD_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD0_SRV		=	SV_2DANSPD_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD0_SRV		=	SV_3DANSPD_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD0_SRV		=	SV_4DANSPD_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD0_SRV		=	SV_5DANSPD_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD0_SRV		=	SV_6DANSPD_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD0_SRV		=	SV_7DANSPD_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD0_SRV		=	SV_8DANSPD_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD0_SRV		=	SV_9DANSPD_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD0_SRV	=	SV_10DANSPD_SRV;			/* 10�i�ڈړ����x		*/

		SV_1DANTIM0_SRV		=	SV_1DANTIM_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM0_SRV		=	SV_2DANTIM_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM0_SRV		=	SV_3DANTIM_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM0_SRV		=	SV_4DANTIM_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM0_SRV		=	SV_5DANTIM_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM0_SRV		=	SV_6DANTIM_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM0_SRV		=	SV_7DANTIM_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM0_SRV		=	SV_8DANTIM_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM0_SRV		=	SV_9DANTIM_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM0_SRV	=	SV_10DANTIM_SRV;			/* 10�i�ڒ�~����		*/
#endif

		SV_DANSUU0_SRV		=	SV_DANSUU_SRV;				/* �i��					*/
		SV_DAIHAITO0_SRV	=	SV_DAIHAITO_SRV;			/* �_�C�n�C�g			*/
		SV_TAIKIPOS0_SRV	=	SV_TAIKIPOS_SRV;			/* �ҋ@�_�ʒu			*/
		SV_TAIKIKAKU0_SRV	=	SV_TAIKIKAKU_SRV;			/* �ҋ@�_�p�x			*/
		SV_HOASEI0_SRV		=	SV_HOASEI_SRV;				/* �␳�f�[�^			*/

		SV_TAIKSPD0_SRV		=	SV_TAIKSPD_SRV;				/* ����x				*/
		SV_TAIKTIM0_SRV		=	SV_TAIKTIM_SRV;				/* �ҋ@����				*/

//		SV_TAIKAN0_SRV		=	SV_TAIKAN_SRV;				/* �ҋ@�����͈�			*/
		SV_MOKKAN0_SRV		=	SV_MOKKAN_SRV;				/* �ڕW�����͈�			*/

		SV_KAITEN0_SRV 		=	SEQ_050_SV;					/* ��]����				*/

		SV_KAJYUU_OBJP0		=	SV_KAJYUU_OBJP;				/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS0		=	SV_KAJYUU_PRS;				/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS0_SRV		=	SV_1DANPRS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS0_SRV		=	SV_2DANPRS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS0_SRV		=	SV_3DANPRS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS0_SRV		=	SV_4DANPRS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS0_SRV		=	SV_5DANPRS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS0_SRV		=	SV_6DANPRS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS0_SRV		=	SV_7DANPRS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS0_SRV		=	SV_8DANPRS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS0_SRV		=	SV_9DANPRS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS0_SRV	=	SV_10DANPRS_SRV;			/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ0_HAB		=	SV_KAJOBJ_HAB;				/* �׏d�����͈�			*/
	}

	else if( SEQ_050_SV & BIT_1 ) {							//���]�@�H

#if (mot100_test == 1)
		dst_s = &SV_MOTDEG1_001;								//FRAM
		src_s = &SV_1DANDEG_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_MOTPOS1_001;								//FRAM
		src_l = &SV_1DANPOS_SRV;								//WORK
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_MOTSPD1_001;								//FRAM
		src_s = &SV_1DANSPD_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_MOTTIM1_001;								//FRAM
		src_s = &SV_1DANTIM_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_MOTPRS1_001;								//FRAM
		src_s = &SV_1DANPRS_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		dst_s = &SV_MOTTGT1_INF0;								//FRAM
		src_s = &SV_MOTTGT_INF0;								//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ڕW�ʒu�^�׏d�ؑ�BIT��� */
		}

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD1_INF0;								//FRAM
		src_s = &SV_MOT_CSUD_INF0;									//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS1_SRV		=	SV_1DANPOS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS1_SRV		=	SV_2DANPOS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS1_SRV		=	SV_3DANPOS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS1_SRV		=	SV_4DANPOS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS1_SRV		=	SV_5DANPOS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS1_SRV		=	SV_6DANPOS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS1_SRV		=	SV_7DANPOS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS1_SRV		=	SV_8DANPOS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS1_SRV		=	SV_9DANPOS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS1_SRV	=	SV_10DANPOS_SRV;			/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG1_SRV		=	SV_1DANDEG_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG1_SRV		=	SV_2DANDEG_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG1_SRV		=	SV_3DANDEG_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG1_SRV		=	SV_4DANDEG_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG1_SRV		=	SV_5DANDEG_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG1_SRV		=	SV_6DANDEG_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG1_SRV		=	SV_7DANDEG_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG1_SRV		=	SV_8DANDEG_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG1_SRV		=	SV_9DANDEG_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG1_SRV	=	SV_10DANDEG_SRV;			/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD1_SRV		=	SV_1DANSPD_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD1_SRV		=	SV_2DANSPD_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD1_SRV		=	SV_3DANSPD_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD1_SRV		=	SV_4DANSPD_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD1_SRV		=	SV_5DANSPD_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD1_SRV		=	SV_6DANSPD_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD1_SRV		=	SV_7DANSPD_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD1_SRV		=	SV_8DANSPD_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD1_SRV		=	SV_9DANSPD_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD1_SRV	=	SV_10DANSPD_SRV;			/* 10�i�ڈړ����x		*/

		SV_1DANTIM1_SRV		=	SV_1DANTIM_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM1_SRV		=	SV_2DANTIM_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM1_SRV		=	SV_3DANTIM_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM1_SRV		=	SV_4DANTIM_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM1_SRV		=	SV_5DANTIM_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM1_SRV		=	SV_6DANTIM_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM1_SRV		=	SV_7DANTIM_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM1_SRV		=	SV_8DANTIM_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM1_SRV		=	SV_9DANTIM_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM1_SRV	=	SV_10DANTIM_SRV;			/* 10�i�ڒ�~����		*/
#endif

		SV_DANSUU1_SRV		=	SV_DANSUU_SRV;				/* �i��					*/
		SV_DAIHAITO1_SRV	=	SV_DAIHAITO_SRV;			/* �_�C�n�C�g			*/
		SV_TAIKIPOS1_SRV	=	SV_TAIKIPOS_SRV;			/* �ҋ@�_�ʒu			*/
		SV_TAIKIKAKU1_SRV	=	SV_TAIKIKAKU_SRV;			/* �ҋ@�_�p�x			*/
		SV_HOASEI1_SRV		=	SV_HOASEI_SRV;				/* �␳�f�[�^			*/

		SV_TAIKSPD1_SRV		=	SV_TAIKSPD_SRV;				/* ����x				*/
		SV_TAIKTIM1_SRV		=	SV_TAIKTIM_SRV;				/* �ҋ@����				*/

//		SV_TAIKAN1_SRV		=	SV_TAIKAN_SRV;				/* �ҋ@�����͈�			*/
		SV_MOKKAN1_SRV		=	SV_MOKKAN_SRV;				/* �ڕW�����͈�			*/

		SV_KAITEN1_SRV 		=	SEQ_050_SV;					/* ��]����				*/

		SV_KAJYUU_OBJP1		=	SV_KAJYUU_OBJP;				/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS1		=	SV_KAJYUU_PRS;				/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS1_SRV		=	SV_1DANPRS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS1_SRV		=	SV_2DANPRS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS1_SRV		=	SV_3DANPRS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS1_SRV		=	SV_4DANPRS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS1_SRV		=	SV_5DANPRS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS1_SRV		=	SV_6DANPRS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS1_SRV		=	SV_7DANPRS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS1_SRV		=	SV_8DANPRS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS1_SRV		=	SV_9DANPRS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS1_SRV	=	SV_10DANPRS_SRV;			/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ1_HAB		=	SV_KAJOBJ_HAB;				/* �׏d�����͈�			*/
	}

	else if( SEQ_050_SV & BIT_2 ) {							//�������@�H

#if (mot100_test == 1)
		dst_s = &SV_MOTDEG2_001;								//FRAM
		src_s = &SV_1DANDEG_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_MOTPOS2_001;								//FRAM
		src_l = &SV_1DANPOS_SRV;								//WORK
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_MOTSPD2_001;								//FRAM
		src_s = &SV_1DANSPD_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_MOTTIM2_001;								//FRAM
		src_s = &SV_1DANTIM_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_MOTPRS2_001;								//FRAM
		src_s = &SV_1DANPRS_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		dst_s = &SV_MOTTGT2_INF0;								//FRAM
		src_s = &SV_MOTTGT_INF0;								//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ڕW�ʒu�^�׏d�ؑ�BIT��� */
		}

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD2_INF0;								//FRAM
		src_s = &SV_MOT_CSUD_INF0;									//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS2_SRV		=	SV_1DANPOS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS2_SRV		=	SV_2DANPOS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS2_SRV		=	SV_3DANPOS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS2_SRV		=	SV_4DANPOS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS2_SRV		=	SV_5DANPOS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS2_SRV		=	SV_6DANPOS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS2_SRV		=	SV_7DANPOS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS2_SRV		=	SV_8DANPOS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS2_SRV		=	SV_9DANPOS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS2_SRV	=	SV_10DANPOS_SRV;			/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG2_SRV		=	SV_1DANDEG_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG2_SRV		=	SV_2DANDEG_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG2_SRV		=	SV_3DANDEG_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG2_SRV		=	SV_4DANDEG_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG2_SRV		=	SV_5DANDEG_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG2_SRV		=	SV_6DANDEG_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG2_SRV		=	SV_7DANDEG_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG2_SRV		=	SV_8DANDEG_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG2_SRV		=	SV_9DANDEG_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG2_SRV	=	SV_10DANDEG_SRV;			/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD2_SRV		=	SV_1DANSPD_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD2_SRV		=	SV_2DANSPD_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD2_SRV		=	SV_3DANSPD_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD2_SRV		=	SV_4DANSPD_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD2_SRV		=	SV_5DANSPD_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD2_SRV		=	SV_6DANSPD_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD2_SRV		=	SV_7DANSPD_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD2_SRV		=	SV_8DANSPD_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD2_SRV		=	SV_9DANSPD_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD2_SRV	=	SV_10DANSPD_SRV;			/* 10�i�ڈړ����x		*/

		SV_1DANTIM2_SRV		=	SV_1DANTIM_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM2_SRV		=	SV_2DANTIM_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM2_SRV		=	SV_3DANTIM_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM2_SRV		=	SV_4DANTIM_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM2_SRV		=	SV_5DANTIM_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM2_SRV		=	SV_6DANTIM_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM2_SRV		=	SV_7DANTIM_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM2_SRV		=	SV_8DANTIM_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM2_SRV		=	SV_9DANTIM_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM2_SRV	=	SV_10DANTIM_SRV;			/* 10�i�ڒ�~����		*/
#endif

		SV_DANSUU2_SRV		=	SV_DANSUU_SRV;				/* �i��					*/
		SV_DAIHAITO2_SRV	=	SV_DAIHAITO_SRV;			/* �_�C�n�C�g			*/
		SV_TAIKIPOS2_SRV	=	SV_TAIKIPOS_SRV;			/* �ҋ@�_�ʒu			*/
		SV_TAIKIKAKU2_SRV	=	SV_TAIKIKAKU_SRV;			/* �ҋ@�_�p�x			*/
		SV_HOASEI2_SRV		=	SV_HOASEI_SRV;				/* �␳�f�[�^			*/

		SV_TAIKSPD2_SRV		=	SV_TAIKSPD_SRV;				/* ����x				*/
		SV_TAIKTIM2_SRV		=	SV_TAIKTIM_SRV;				/* �ҋ@����				*/

//		SV_TAIKAN2_SRV		=	SV_TAIKAN_SRV;				/* �ҋ@�����͈�			*/
		SV_MOKKAN2_SRV		=	SV_MOKKAN_SRV;				/* �ڕW�����͈�			*/

		SV_KAITEN2_SRV 		=	SEQ_050_SV;					/* ��]����				*/

		SV_KAJYUU_OBJP2		=	SV_KAJYUU_OBJP;				/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS2		=	SV_KAJYUU_PRS;				/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS2_SRV		=	SV_1DANPRS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS2_SRV		=	SV_2DANPRS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS2_SRV		=	SV_3DANPRS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS2_SRV		=	SV_4DANPRS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS2_SRV		=	SV_5DANPRS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS2_SRV		=	SV_6DANPRS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS2_SRV		=	SV_7DANPRS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS2_SRV		=	SV_8DANPRS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS2_SRV		=	SV_9DANPRS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS2_SRV	=	SV_10DANPRS_SRV;			/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ2_HAB		=	SV_KAJOBJ_HAB;				/* �׏d�����͈�			*/
	}

	else if( SEQ_050_SV & BIT_3 ) {							//�㉝���@�H

#if (mot100_test == 1)
		dst_s = &SV_MOTDEG3_001;								//FRAM
		src_s = &SV_1DANDEG_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�p */
		}
		dst_l = &SV_MOTPOS3_001;								//FRAM
		src_l = &SV_1DANPOS_SRV;								//WORK
		for (c=0; c<100; c++, dst_l++, src_l++) {
			*dst_l = *src_l;									/* 1�`100�i �ڕW�ʒu */
		}
		dst_s = &SV_MOTSPD3_001;								//FRAM
		src_s = &SV_1DANSPD_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ���x */
		}
		dst_s = &SV_MOTTIM3_001;								//FRAM
		src_s = &SV_1DANTIM_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i ��~���� */
		}
		dst_s = &SV_MOTPRS3_001;								//FRAM
		src_s = &SV_1DANPRS_SRV;								//WORK
		for (c=0; c<100; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* 1�`100�i �ڕW�׏d */
		}
		dst_s = &SV_MOTTGT3_INF0;								//FRAM
		src_s = &SV_MOTTGT_INF0;								//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ڕW�ʒu�^�׏d�ؑ�BIT��� */
		}

//2016/04/15 �ϑ����
		dst_s = &SV_MOT_CSUD3_INF0;								//FRAM
		src_s = &SV_MOT_CSUD_INF0;									//WORK
		for (c=0; c<7; c++, dst_s++, src_s++) {
			*dst_s = *src_s;									/* �ϑ� �O�^��BIT��� */
		}
#else
		SV_1DANPOS3_SRV		=	SV_1DANPOS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPOS3_SRV		=	SV_2DANPOS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPOS3_SRV		=	SV_3DANPOS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPOS3_SRV		=	SV_4DANPOS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPOS3_SRV		=	SV_5DANPOS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPOS3_SRV		=	SV_6DANPOS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPOS3_SRV		=	SV_7DANPOS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPOS3_SRV		=	SV_8DANPOS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPOS3_SRV		=	SV_9DANPOS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPOS3_SRV	=	SV_10DANPOS_SRV;			/* 10�i�ږڕW�ʒu		*/

		SV_1DANDEG3_SRV		=	SV_1DANDEG_SRV;				/* 01�i�ڊp�x�ʒu		*/
		SV_2DANDEG3_SRV		=	SV_2DANDEG_SRV;				/* 02�i�ڊp�x�ʒu		*/
		SV_3DANDEG3_SRV		=	SV_3DANDEG_SRV;				/* 03�i�ڊp�x�ʒu		*/
		SV_4DANDEG3_SRV		=	SV_4DANDEG_SRV;				/* 04�i�ڊp�x�ʒu		*/
		SV_5DANDEG3_SRV		=	SV_5DANDEG_SRV;				/* 05�i�ڊp�x�ʒu		*/
		SV_6DANDEG3_SRV		=	SV_6DANDEG_SRV;				/* 06�i�ڊp�x�ʒu		*/
		SV_7DANDEG3_SRV		=	SV_7DANDEG_SRV;				/* 07�i�ڊp�x�ʒu		*/
		SV_8DANDEG3_SRV		=	SV_8DANDEG_SRV;				/* 08�i�ڊp�x�ʒu		*/
		SV_9DANDEG3_SRV		=	SV_9DANDEG_SRV;				/* 09�i�ڊp�x�ʒu		*/
		SV_10DANDEG3_SRV	=	SV_10DANDEG_SRV;			/* 10�i�ڊp�x�ʒu		*/

		SV_1DANSPD3_SRV		=	SV_1DANSPD_SRV;				/* 01�i�ڈړ����x		*/
		SV_2DANSPD3_SRV		=	SV_2DANSPD_SRV;				/* 02�i�ڈړ����x		*/
		SV_3DANSPD3_SRV		=	SV_3DANSPD_SRV;				/* 03�i�ڈړ����x		*/
		SV_4DANSPD3_SRV		=	SV_4DANSPD_SRV;				/* 04�i�ڈړ����x		*/
		SV_5DANSPD3_SRV		=	SV_5DANSPD_SRV;				/* 05�i�ڈړ����x		*/
		SV_6DANSPD3_SRV		=	SV_6DANSPD_SRV;				/* 06�i�ڈړ����x		*/
		SV_7DANSPD3_SRV		=	SV_7DANSPD_SRV;				/* 07�i�ڈړ����x		*/
		SV_8DANSPD3_SRV		=	SV_8DANSPD_SRV;				/* 08�i�ڈړ����x		*/
		SV_9DANSPD3_SRV		=	SV_9DANSPD_SRV;				/* 09�i�ڈړ����x		*/
		SV_10DANSPD3_SRV	=	SV_10DANSPD_SRV;			/* 10�i�ڈړ����x		*/

		SV_1DANTIM3_SRV		=	SV_1DANTIM_SRV;				/* 01�i�ڒ�~����		*/
		SV_2DANTIM3_SRV		=	SV_2DANTIM_SRV;				/* 02�i�ڒ�~����		*/
		SV_3DANTIM3_SRV		=	SV_3DANTIM_SRV;				/* 03�i�ڒ�~����		*/
		SV_4DANTIM3_SRV		=	SV_4DANTIM_SRV;				/* 04�i�ڒ�~����		*/
		SV_5DANTIM3_SRV		=	SV_5DANTIM_SRV;				/* 05�i�ڒ�~����		*/
		SV_6DANTIM3_SRV		=	SV_6DANTIM_SRV;				/* 06�i�ڒ�~����		*/
		SV_7DANTIM3_SRV		=	SV_7DANTIM_SRV;				/* 07�i�ڒ�~����		*/
		SV_8DANTIM3_SRV		=	SV_8DANTIM_SRV;				/* 08�i�ڒ�~����		*/
		SV_9DANTIM3_SRV		=	SV_9DANTIM_SRV;				/* 09�i�ڒ�~����		*/
		SV_10DANTIM3_SRV	=	SV_10DANTIM_SRV;			/* 10�i�ڒ�~����		*/
#endif

		SV_DANSUU3_SRV		=	SV_DANSUU_SRV;				/* �i��					*/
		SV_DAIHAITO3_SRV	=	SV_DAIHAITO_SRV;			/* �_�C�n�C�g			*/
		SV_TAIKIPOS3_SRV	=	SV_TAIKIPOS_SRV;			/* �ҋ@�_�ʒu			*/
		SV_TAIKIKAKU3_SRV	=	SV_TAIKIKAKU_SRV;			/* �ҋ@�_�p�x			*/
		SV_HOASEI3_SRV		=	SV_HOASEI_SRV;				/* �␳�f�[�^			*/

		SV_TAIKSPD3_SRV		=	SV_TAIKSPD_SRV;				/* ����x				*/
		SV_TAIKTIM3_SRV		=	SV_TAIKTIM_SRV;				/* �ҋ@����				*/

//		SV_TAIKAN3_SRV		=	SV_TAIKAN_SRV;				/* �ҋ@�����͈�			*/
		SV_MOKKAN3_SRV		=	SV_MOKKAN_SRV;				/* �ڕW�����͈�			*/

		SV_KAITEN3_SRV 		=	SEQ_050_SV;					/* ��]����				*/

		SV_KAJYUU_OBJP3		=	SV_KAJYUU_OBJP;				/* �׏d�ڕW		V01m	*/
		SV_KAJYUU_PRS3		=	SV_KAJYUU_PRS;				/* �׏d�␳		V01m	*/

#if (mot100_test == 1)
#else
//2015/01/14
		SV_1DANPRS3_SRV		=	SV_1DANPRS_SRV;				/* 01�i�ږڕW�ʒu		*/
		SV_2DANPRS3_SRV		=	SV_2DANPRS_SRV;				/* 02�i�ږڕW�ʒu		*/
		SV_3DANPRS3_SRV		=	SV_3DANPRS_SRV;				/* 03�i�ږڕW�ʒu		*/
		SV_4DANPRS3_SRV		=	SV_4DANPRS_SRV;				/* 04�i�ږڕW�ʒu		*/
		SV_5DANPRS3_SRV		=	SV_5DANPRS_SRV;				/* 05�i�ږڕW�ʒu		*/
		SV_6DANPRS3_SRV		=	SV_6DANPRS_SRV;				/* 06�i�ږڕW�ʒu		*/
		SV_7DANPRS3_SRV		=	SV_7DANPRS_SRV;				/* 07�i�ږڕW�ʒu		*/
		SV_8DANPRS3_SRV		=	SV_8DANPRS_SRV;				/* 08�i�ږڕW�ʒu		*/
		SV_9DANPRS3_SRV		=	SV_9DANPRS_SRV;				/* 09�i�ږڕW�ʒu		*/
		SV_10DANPRS3_SRV	=	SV_10DANPRS_SRV;			/* 10�i�ږڕW�ʒu		*/
#endif
		SV_KAJOBJ3_HAB		=	SV_KAJOBJ_HAB;				/* �׏d�����͈�			*/
	}

	FRAM_csum_set_Spec();						//2020-09-1(_Spec) �׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	KAT_DATCHG_FLG = 0xff;									//�^�f�[�^�ύX�t���O
}


/*
********************************************************************************
*  Module Name:		mmon_spd_in
*  Function Name:	���x���~�b�g�l�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2013-02-16		V06p
********************************************************************************
*/
void	mmon_spd_in(void)
{
	UNs		t_no, i, bit;
	UNs		limit_spd;
	UNs		chg;

	chg = 0;
	bit = BIT_0;
	t_no = CSR_TBL_POS_NOW;

	if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon) ) || 			//���[�V�������j�^1-5���
		 ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset) ) ) {			//���[�V�����ݒ�1-5���

		if (CSR_buff[t_no].DATA_NO == 102) {
			if (PV0_CKSPD_LMBIT & BIT_15) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//�߂葬�x
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & BIT_15) {
#if (mot100_test == 1)									//2015/11/15
				limit_spd = PVP_CKLMT_SPD;				//�e�H�����x
#else
				limit_spd = PVP_CKLMT_MDSPD;			//�߂葬�x
#endif
				chg = 0xff;
			}
		}
		else {
			i = CSR_buff[t_no].DATA_NO - 97;
			bit<<=i;
			if (PV0_CKSPD_LMBIT & bit) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//�e�H�����x
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & bit) {
#if (mot100_test == 1)
				limit_spd = PVP_CKLMT_SPD;				//�e�H�����x
#else
				limit_spd = PVP_CKLMT_SPDTOP[i];		//�e�H�����x
#endif
				chg = 0xff;
			}
		}
	}
	else if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon2) ) || 			//���[�V�������j�^6-10���
			  ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset2) ) ) {			//���[�V�����ݒ�6-10���

		if (CSR_buff[t_no].DATA_NO == 102) {
			if (PV0_CKSPD_LMBIT & BIT_15) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//�߂葬�x
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & BIT_15) {
				limit_spd = PVP_CKLMT_MDSPD;			//�߂葬�x
				chg = 0xff;
			}
		}
		else {
			i = CSR_buff[t_no].DATA_NO - 97;
			i += 5;
			bit<<=i;
			if (PV0_CKSPD_LMBIT & bit) {				//2015/07/10
				limit_spd = GMN_PAR083*10;				//�e�H�����x
				chg = 0xff;
			}
			else if (PV0_CKSPD_OVBIT & bit) {
				limit_spd = PVP_CKLMT_SPDTOP[i];		//�e�H�����x
				chg = 0xff;
			}
		}
	}

	if (chg) {
		t_no = SV_TBL_POS_NOW;

		SV_DATA_CHG = 0x55;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
		SV_DISP_BUFF = HEX_BCD4(limit_spd);					//�ύX�f�[�^�o�b�t�@�N���A

		TENKEY_CNT = 0;

		SVPV_data_disp(SV_DISP_BUFF, &SV_buff[t_no], 0, 0x482);	//�ݒ�l�������l �\��(��ۻ��ڽ/���]�\��(�w�i��))
	}

}


/*
********************************************************************************
*  Module Name:		mmon_agl_in
*  Function Name:	�p�x���~�b�g�l�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2014-04-15
********************************************************************************
*/
void	mmon_agl_in(void)
{
	UNs		t_no, i, bit;
	UNs		limit_agl;
	UNl		limit_pos;
	UNs		chg;
	UNs		inf, step;

	chg = 0;
	bit = BIT_0;
	t_no = CSR_TBL_POS_NOW;

	if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon) ) || 			//���[�V�������j�^1-5���
		 ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset) ) ) {			//���[�V�����ݒ�1-5���

#if (mot100_test == 1)
////		step = SV_MOT_PAGE * 5;						//1�s�ڂ̍s��No.0�`99(=1�`100)
////		step += CSR_buff[t_no].DATA_NO - 97;
////		inf = PVP_CKAGL_OVBIT1[step/16];
////		bit <<= step % 16;
////		if (inf & bit) {							//�I�[�o�[BIT ON�H
////			limit_agl = PVP_CKLMT_AGLTOP1[step];	//�e�H���p�x
////			chg = 0xff;
////		}
		i = CSR_buff[t_no].DATA_NO - 97;
		bit<<=i;
		if (PV0_CKAGL_OVBIT & bit) {
			limit_agl = PVP_CKLMT_AGL;				//�e�H���p�x
			chg = 0xff;
		}
#else
		i = CSR_buff[t_no].DATA_NO - 97;
		bit<<=i;
		if (PVP_CKAGL_OVBIT & bit) {
			limit_agl = PVP_CKLMT_AGLTOP[i];		//�e�H���p�x
			chg = 0xff;
		}
#endif
	}
	else if ( ( (disp_stg == 0) && (disp_stg_sel == E_sstg_mmon2) ) || 			//���[�V�������j�^6-10���
			  ( (disp_stg == 2) && (disp_stg_sel == E_dstg_mset2) ) ) {			//���[�V�����ݒ�6-10���

		i = CSR_buff[t_no].DATA_NO - 97;
		i += 5;
		bit<<=i;
		if (PVP_CKAGL_OVBIT & bit) {
			limit_agl = PVP_CKLMT_AGLTOP[i];		//�e�H���p�x
			chg = 0xff;
		}
	}

	if (chg) {
		t_no = SV_TBL_POS_NOW;

		SV_DATA_CHG = 0xff;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
		SV_DISP_BUFF = HEX_BCD4(limit_agl/10);

		TENKEY_CNT = 0;

		SVPV_data_disp((UNl)limit_agl, &SV_buff[t_no], 0, 0x481);	//�ݒ�l�������l �\��(��ۻ��ڽ/���]�\��(�w�i��))
	}

}


/*
********************************************************************************
*  Function Name:	�����^�׏d�ڕW�؊���
*  Input	:		�H��No.0�`9�i1�`10�i�ڂ̈Ӗ��j
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2015/01/15
********************************************************************************
*/
void	mmon_pos_kaj_chg(UNs no)
{
	UNs		bit, cnt, t_no, sarch, t_no_tanni;
	UNl		*pos;
	UNs		*kaj, *inf;
	UNs		step;

	if ( (SEQ_050_SV & BIT_1) == 0 ) 		return;			//���]�H
	if ( (SEQ_PAR_151 & BIT_2) == 0 )		return;

	bit = BIT_0;

#if (mot100_test == 1)
	step = (SV_MOT_PAGE * 5) + no;
	inf = &SV_MOTTGT_INF0;
	inf += step / 16;
	bit <<= step % 16;
	*inf ^= bit;										//�ʒu�̉׏d �ؑ�

	mmon_trans_put();

	pos = &SV_1DANPOS_SRV;
	pos += step;
	kaj = &SV_1DANPRS_SRV;
	kaj += step;
#else
	bit <<= no;
	inf = &SV_MOTOBJ_INF1;
	*inf ^= bit;								//�ʒu�̉׏d �ؑ�

	FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	KAT_DATCHG_FLG = 0xff;								//�^�f�[�^�ύX�t���O

	pos = &SV_1DANPOS_SRV;
	pos += no;
	kaj = &SV_1DANPRS_SRV;
	kaj += no;
#endif

	if (no<5) {
		sarch = 92+no;									//1�`5�i�ڂ̌�������ݒ�l��ٰ��No.
		t_no_tanni = 5+no;								//1�`5�i�ڂ̒P�ʂ��ޯ̧���ڽ
	}
	else {
//2015/04/10		sarch = 112+no;									//6�`10�i�ڂ̌�������ݒ�l��ٰ��No.
////////////		t_no_tanni = 5+no;								//6�`10�i�ڂ̒P�ʂ��ޯ̧���ڽ
		sarch = 112+(no-5);									//6�`10�i�ڂ̌�������ݒ�l��ٰ��No.
		t_no_tanni = 5+(no-5);								//6�`10�i�ڂ̒P�ʂ��ޯ̧���ڽ
	}

	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == sarch) {				//��ٰ�ߔԍ� ���
			if (*inf & bit) {
				/* �ʒu -> �׏d*/
				SV_buff[t_no].DATA_ADR = kaj;			//�i�[����ڽ�ύX
				SV_buff[t_no].BYTE_NO = 2;				//�޲Ē��̕ύX
				SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;	//�����_�ʒu
				SV_buff[t_no].TOK_FLG = 0;				//�����׸�
				SV_buff[t_no].SUB_NO = 123;				//���ٰ��No.

#if (mot100_test == 1)
#else
				PV_buff[t_no_tanni].DATA_ADR = (UNs *)&CAR_KAJ_AREA;		//�P��
#endif
			}
			else {
				/* �׏d -> �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)pos;	//�i�[����ڽ�ύX
				SV_buff[t_no].BYTE_NO = 4;				//�޲Ē��̕ύX
				SV_buff[t_no].TEN_POS = SYO_LNG_CNT;	//�����_�ʒu
				SV_buff[t_no].TOK_FLG = 0x0400;			//�����׸ށi����10�{�j
				SV_buff[t_no].SUB_NO = 75;				//���ٰ��No.

#if (mot100_test == 1)
#else
				PV_buff[t_no_tanni].DATA_ADR = (UNs *)&CAR_LNG_AREA;		//�P��
#endif
			}
			break;
		}
	}
	SVdata_disp();							//�S�ݒ�l�\��
	SV_csr_set();							//�ݒ�l���ٕ\��

#if (mot100_test == 1)
	sarch = 97+no;
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == sarch) {				//��ٰ�ߔԍ� ���
			if(PV_buff[t_no].AKI2 == 1) {				//�ڕW�ʒu�P�� ���
				if (*inf & bit) {
					/* �ʒu -> �׏d*/
					PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;		//�P��
				}
				else {
					/* �׏d -> �ʒu */
					PV_buff[t_no].DATA_ADR = (UNs *)&CAR_LNG_AREA;		//�P��
				}
				break;
			}
		}
	}
#endif

#if (mot100_test == 1)
	PVdata_disp1(t_no, 0);					//�P�� �\��
#else
	PVdata_disp1(t_no_tanni, 0);			//�P�� �\��
#endif

	CSR_sw56_disp();						//SW56�����\��
}


/*
********************************************************************************
*  Module Name:		cnv_mi_mi
*  Function Name:	�P�ʐؑ�(mm/INCH��mm/INCH)
*  Input	:		mm/INCH
*  Return	: 		mm/INCH
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_mi_mi(UNl mm_bf)
{
	UNl		wk1;

	wk1 = mm_bf;
	if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
	}
	else{
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//�P�� �����x(1:�����x)
			wk1 /= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mi_mi_sur
*  Function Name:	�P�ʐؑ�(mm/INCH��mm/INCH)
*  Input	:		mm(�����_3��)/INCH(�����_3��)
*  Return	: 		mm(�����_1or2��)/INCH(�����_3��)
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2004-10-04	V01m
********************************************************************************
*/
UNl		cnv_mi_mi_sur(UNl mm_bf)
{
	UNl		wk1;

	wk1 = mm_bf;
	if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
	}
	else{
//2014/12/23
////		wk1 /= 10;
////		if (SV_POINT_A1 == 1) {
////			wk1 /= 10;
////		}
		if (SV_POINT_A1 == 0) {
			wk1 /= 1000;					//�����f�[�^�����_�ȉ�3���������_�ȉ�0���\��
		}
		else if (SV_POINT_A1 == 1) {
			wk1 /= 100;						//�����f�[�^�����_�ȉ�3���������_�ȉ�1���\��
		}
		else if (SV_POINT_A1 == 2) {
			wk1 /= 10;						//�����f�[�^�����_�ȉ�3���������_�ȉ�2���\��
		}
		else {
			wk1 /= 1;						//�����f�[�^�����_�ȉ�3���������_�ȉ�3���\��
		}

	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mm_inch
*  Function Name:	�P�ʐؑ�(mm��mm/INCH)
*  Input	:		mm(�����_ 3��)
*					0=�Ȃ��^1=10�{�^2=10��1�Ȃ�
*
*  Return	: 		mm/INCH
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:FIT)�c�[		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_mm_inch(UNl mm_bf, UNi flg)
{
	UNl		wk1;

	wk1 = mm_bf;

	if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		wk1 *=10;					//1 INCH = 25.4mm
		wk1 /=254;

		if(flg != 2) {
			if( SEQ_016_SV & BIT_7 ) {	//�P�� �����x(1:�����x)
				wk1 *=10;
			}
		}
	}
	else if(flg == 1){
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//�P�� �����x(1:�����x)
			wk1 /= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_inch_mm
*  Function Name:	�P�ʐؑ�(mm/INCH��mm)
*  Input	:		mm/INCH
*					0=�Ȃ��^1=10�{�^2=10��1�Ȃ�
*
*  Return	: 		mm(�����_ 3��)
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:FIT)�c�[		ON:2002-10-16
********************************************************************************
*/
UNl		cnv_inch_mm(UNl inch_bf, UNi flg)
{
	UNl		wk1;

	wk1 = inch_bf;

	if( SEQ_016_SV & BIT_6 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		wk1 *=254;							//1 INCH = 25.4mm
		wk1 /=10;

		if(flg != 2) {
			if( SEQ_016_SV & BIT_7 ) {			//�P�� �����x(1:�����x)
				wk1 /=10;
			}
		}
	}
	else if(flg == 1){
		if( 0 == (SEQ_016_SV & BIT_7) ) {	//�P�� �����x(1:�����x)
			wk1 *= 10;
		}
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_um_uinch
*  Function Name:	�P�ʐؑ�(um��um/uINCH)
*  Input	:		um(�����_�Ȃ�)
*
*  Return	: 		mm/INCH
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_um_uinch(UNl um_bf)
{
	UNl		wk1;

	wk1 = um_bf;

	if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		wk1 *=10;					//1uINCH = 2.5um�i�{����25.4um�j
		wk1 /=25;
	}
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_uinch_um
*  Function Name:	�P�ʐؑ�(um/uINCH��um)
*  Input	:		umm/uINCH
*
*  Return	: 		um(�����_�Ȃ�)
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_uinch_um(UNl uinch_bf)
{
	UNl		wk1;

	wk1 = uinch_bf;

	if( SEQ_016_SV & BIT_6 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		wk1 *=25;							//1uINCH = 2.5um�i�{����25.4um�j
		wk1 /=10;
	}
	
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_mm_inch2
*  Function Name:	�P�ʐؑ�(mm��INCH)
*  Input	:		mm(�����_ 3��)
*					0=�Ȃ��^1=10�{�^2=10��1�Ȃ�
*
*  Return	: 		INCH
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
UNl		cnv_mm_inch2(UNl mm_bf, UNi flg)
{
	UNl		wk1;

	wk1 = mm_bf;

	wk1 *=100;
	wk1 /=254;

	if( (SEQ_016_SV & BIT_7) == 0 ) {	//�P�� �����x(1:�����x)
		wk1 /=10;
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_inch_mm2
*  Function Name:	�P�ʐؑ�(INCH��mm)
*  Input	:		INCH
*					0=�Ȃ��^1=10�{�^2=10��1�Ȃ�
*
*  Return	: 		mm(�����_ 3��)
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
UNl		cnv_inch_mm2(UNl inch_bf, UNi flg)
{
	UNl		wk1;

	wk1 = inch_bf;

	wk1 *=254;							//1 INCH = 25.4mm
	wk1 /=10;

	if( SEQ_016_SV & BIT_7 ) {			//�P�� �����x(1:�����x)
		wk1 /=10;
	}

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_um_uinch2
*  Function Name:	�P�ʐؑ�(um��uINCH)
*  Input	:		um(�����_�Ȃ�)
*
*  Return	: 		uINCH
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_um_uinch2(UNl um_bf)
{
	UNl		wk1;

	wk1 = um_bf;

	wk1 *=10;					//1uINCH = 2.5um�i�{����25.4um�j
	wk1 /=25;

	return(wk1);
}


/*
********************************************************************************
*  Module Name:		cnv_uinch_um2
*  Function Name:	�P�ʐؑ�(uINCH��um)
*  Input	:		umm
*
*  Return	: 		um(�����_�Ȃ�)
*  Note		:�P�ʐؑ� mm/INCH���L�����A�ϊ�
*
*  �� ��	:A.Shimamura		ON:2014-12-23
********************************************************************************
*/
UNl		cnv_uinch_um2(UNl uinch_bf)
{
	UNl		wk1;

	wk1 = uinch_bf;

	wk1 *=25;							//1uINCH = 2.5um�i�{����25.4um�j
	wk1 /=10;
	
	return(wk1);
}


/*
********************************************************************************
*  Module Name:		SEI_csr_ichk(��:SEIDAN_CSR_BACK)
*  Function Name:	���Y�J�[�\���ʒu������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-27
********************************************************************************
*/
void	SEI_csr_ichk(void)
{
	UNs		bf, bf1;

	bf = SEQ_016_SV;
	bf &= (BIT_8 | BIT_12 | BIT_14);
	bf1 = SEI_ON1_LST;
	SEI_ON1_LST = bf;
	bf ^= bf1;

	if(bf != 0){
		bf1 = SW14_ON1_FLG & 0x0007;
		switch( bf1 ) {
			default:
				SW14_ON1_FLG = 0;
				break;

			case 0x0002:								//İ�ٶ���
				if( 00 == (SEQ_016_SV & BIT_8) ) {		//İ�ٶ����̔�\���H
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;

			case 0x0003:								//ۯĶ���1
				if( 00 == (SEQ_016_SV & BIT_12) ) {		//ۯĶ���1�̔�\���H
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;

			case 0x0004:								//ۯĶ���2
				if( 00 == (SEQ_016_SV & BIT_14) ) {		//ۯĶ���2�̔�\��
					SW14_ON1_FLG = 0;
					SW14_ON1_FLG_BAK = 0;
				}
				break;
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEI_csr_mng
*  Function Name:	���Y[��{]�̐�p�@�J�[�\���ړ��Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-30
********************************************************************************
*/
void	SEI_csr_mng(void)
{
	if(GAMEN_NO != 1){
		return;
	}

	if(WINDOW_NO != 00 ){
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//�J�[�\���ړ�
		return;
	}

	switch (CSR_FLG)
	{
		case E_key_up:
			if(SW14_ON1_FLG == 4 || SW14_ON1_FLG == 0x84){	//ۯĶ���2�������H
				if(SW14_ON1_FLG & 0x80){					//���J�E���^�␳�@�\���H
					if(COUNT_HOSEI_ADR != 00){				//���]�A�h���X�f�[�^�Ҕ�
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
					}
				}
				SW14_ON1_FLG = 0x03;						//ۯĶ���1

				CSR_FLG = 5;								//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = 2;							//�J�[�\���ԍ��Z�b�g
				SV_FLG_CNT = 1;								//�ݒ�l�ԍ��Z�b�g
				SW_FLG_CNT = 1;								//�r�v�ԍ��Z�b�g
				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//�J�[�\���ړ�(�߂�l�w��,�ړ�)
			}
			break;

		case E_key_down:
			if(SW14_ON1_FLG == 3 || SW14_ON1_FLG == 0x83){	//ۯĶ���1�������H
				if(SEQ_016_SV & BIT_14){						//ۯĶ���2�L��H
					if(SW14_ON1_FLG & 0x80){				//���J�E���^�␳�@�\���H
						if(COUNT_HOSEI_ADR != 00){			//���]�A�h���X�f�[�^�Ҕ�
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
						}
					}
					SW14_ON1_FLG = 0x04;					//ۯĶ���2

					CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
					CSR_FLG_CNT = 3;						//�J�[�\���ԍ��Z�b�g
					SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
					SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g
					CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�(�߂�l�w��,�ړ�)
				}
			}
			break;

//V01z		case E_key_left:
//////			if( (SW14_ON1_FLG == 2 || SW14_ON1_FLG == 0x82 ) ||		/* İ�ٶ����������H */
//////				(SW14_ON1_FLG == 3 || SW14_ON1_FLG == 0x83 ) ||		/* ۯĶ���1�������H */
//////				(SW14_ON1_FLG == 4 || SW14_ON1_FLG == 0x84) ) {		/* ۯĶ���2�������H */
//////
//////				if(SW14_ON1_FLG & 0x80){				//���J�E���^�␳�@�\���H
//////					if(COUNT_HOSEI_ADR != 00){			//���]�A�h���X�f�[�^�Ҕ�
//////						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
//////					}
//////				}
//////
//////				SW14_ON1_FLG_BAK3 = SW14_ON1_FLG;		//�O�̈ʒu�L��
//////				CSR_FLG_CNT_BAK3 = CSR_FLG_CNT;			//�O�̈ʒu�L��
//////
//////				SW14_ON1_FLG = 0x05;					//����ײ��
//////
//////				CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
//////				CSR_FLG_CNT = 4;						//�J�[�\���ԍ��Z�b�g
//////				SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
//////				SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g
//////				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�(�߂�l�w��,�ړ�)
//////			}
//////			break;
//////
//////		case E_key_right:
//////			if(SW14_ON1_FLG == 5){	//����ײ�ޏ������H
//////				SW14_ON1_FLG = SW14_ON1_FLG_BAK3;		//�O�̈ʒu�ɖ߂�
//////
//////				CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
//////				CSR_FLG_CNT = CSR_FLG_CNT_BAK3;			//�O�̈ʒu�ɖ߂�
//////				SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
//////				SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g
//////				CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�(�߂�l�w��,�ړ�)
//////			}
//////			break;

		default:
			break;
	}
}


/*
********************************************************************************
*  Module Name:		EPM_MEM_CLR
*  Function Name:	�d�̓��j�^�p���[�N�������N���A
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2010-10-26
********************************************************************************
*/
void EPM_MEM_CLR(void)
{

	memset_long(&EPM_SEC_2_MESMIN_ADD[0], 0x0000, (sizeof(EPM_SEC_2_MESMIN_ADD)/4));
	EPM_SEC_MESMIN_CNT = 0;

	memset_long(&EPM_05MIN_BUF[0][0], 0x0000, (sizeof(EPM_05MIN_BUF)/4));
	memset_long(&EPM_10MIN_BUF[0][0], 0x0000, (sizeof(EPM_10MIN_BUF)/4));
	memset_long(&EPM_15MIN_BUF[0][0], 0x0000, (sizeof(EPM_15MIN_BUF)/4));
	memset_long(&EPM_20MIN_BUF[0][0], 0x0000, (sizeof(EPM_20MIN_BUF)/4));
	memset_long(&EPM_25MIN_BUF[0][0], 0x0000, (sizeof(EPM_25MIN_BUF)/4));
	memset_long(&EPM_30MIN_BUF[0][0], 0x0000, (sizeof(EPM_30MIN_BUF)/4));
	memset_long(&EPM_35MIN_BUF[0][0], 0x0000, (sizeof(EPM_35MIN_BUF)/4));
	memset_long(&EPM_40MIN_BUF[0][0], 0x0000, (sizeof(EPM_40MIN_BUF)/4));
	memset_long(&EPM_45MIN_BUF[0][0], 0x0000, (sizeof(EPM_45MIN_BUF)/4));
	memset_long(&EPM_50MIN_BUF[0][0], 0x0000, (sizeof(EPM_50MIN_BUF)/4));
	memset_long(&EPM_55MIN_BUF[0][0], 0x0000, (sizeof(EPM_55MIN_BUF)/4));
	memset_long(&EPM_60MIN_BUF[0][0], 0x0000, (sizeof(EPM_60MIN_BUF)/4));

	EPM_05MIN_POI = 0;
	EPM_10MIN_POI = 0;
	EPM_15MIN_POI = 0;
	EPM_20MIN_POI = 0;
	EPM_25MIN_POI = 0;
	EPM_30MIN_POI = 0;
	EPM_35MIN_POI = 0;
	EPM_40MIN_POI = 0;
	EPM_45MIN_POI = 0;
	EPM_50MIN_POI = 0;
	EPM_55MIN_POI = 0;
	EPM_60MIN_POI = 0;

	memset_long(&EPM_05MON_BUF[0][0], 0x0000, (sizeof(EPM_05MON_BUF)/4));
	memset_long(&EPM_10MON_BUF[0][0], 0x0000, (sizeof(EPM_10MON_BUF)/4));
	memset_long(&EPM_15MON_BUF[0][0], 0x0000, (sizeof(EPM_15MON_BUF)/4));
	memset_long(&EPM_20MON_BUF[0][0], 0x0000, (sizeof(EPM_20MON_BUF)/4));
	memset_long(&EPM_25MON_BUF[0][0], 0x0000, (sizeof(EPM_25MON_BUF)/4));
	memset_long(&EPM_30MON_BUF[0][0], 0x0000, (sizeof(EPM_30MON_BUF)/4));
	memset_long(&EPM_35MON_BUF[0][0], 0x0000, (sizeof(EPM_35MON_BUF)/4));
	memset_long(&EPM_40MON_BUF[0][0], 0x0000, (sizeof(EPM_40MON_BUF)/4));
	memset_long(&EPM_45MON_BUF[0][0], 0x0000, (sizeof(EPM_45MON_BUF)/4));
	memset_long(&EPM_50MON_BUF[0][0], 0x0000, (sizeof(EPM_50MON_BUF)/4));
	memset_long(&EPM_55MON_BUF[0][0], 0x0000, (sizeof(EPM_55MON_BUF)/4));
	memset_long(&EPM_60MON_BUF[0][0], 0x0000, (sizeof(EPM_60MON_BUF)/4));

	EPM_05MON_POI = 0;
	EPM_10MON_POI = 0;
	EPM_15MON_POI = 0;
	EPM_20MON_POI = 0;
	EPM_25MON_POI = 0;
	EPM_30MON_POI = 0;
	EPM_35MON_POI = 0;
	EPM_40MON_POI = 0;
	EPM_45MON_POI = 0;
	EPM_50MON_POI = 0;
	EPM_55MON_POI = 0;
	EPM_60MON_POI = 0;
}


/*
********************************************************************************
*  Module Name:		SEI_Worker_GET
*  Function Name:	���Y�Ǘ��f�[�^�擾
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_GET(void)
{
	SV0_WORKER_COD	= SV_WORKER_COD	;	//��ƎҺ��ގ擾
	SV0_ORDER_COD	= SV_ORDER_COD	;	//���Ժ��ގ擾
	SV0_PLAN_CNT	= SV_PLAN_CNT	;	//�v�搔�擾
}

/*
********************************************************************************
*  Module Name:		SEI_Worker_SET
*  Function Name:	���Y�Ǘ��f�[�^�o�^
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_SET(void)
{
	SV_WORKER_COD	= SV0_WORKER_COD	;	//��ƎҺ��ފm��ޔ�
	SV_ORDER_COD	= SV0_ORDER_COD		;	//���Ժ��ފm��
	SV_PLAN_CNT		= SV0_PLAN_CNT		;	//�v�搔�m��
	SV_BAD_CNT = 0;							//�s�ǐ��ر

//2015/09/20	FRAM_csum_set();

	SV0SR_WORKER_COD	= SV0_WORKER_COD	;		//��ƊJ�n����ƎҺ���
	SV0SR_ORDER_COD		= HEX_BCD4(SV0_ORDER_COD);	//��ƊJ�n�����Ժ���
	SV0SR_PLAN_CNT		= SV0_PLAN_CNT		;		//��ƊJ�n���v�搔
	SV0SR_BAD_CNT		= SV_BAD_CNT		;		//��ƊJ�n���s�ǐ�
	SV0SR_KATA_NO		= PV_MLDNO1_F1		;		//��ƊJ�n���^�ԍ�
	memcpy_word(&SV0SR_KATA_NAME[0], &PV_MLDNO2_F1[0],7)	;	//��ƊJ�n���^����
	memcpy_word(&SV0SR_KATA_MEMO[0], &PV_MLDNO3_F1[0],7)	;	//��ƊJ�n���^����

	SV0_WORK_STR_FLG = 0x5AA5;			// C/B��

	SV_WORKER_ENT_FLG = 0x5AA5;			//��Ǝғo�^�L��

	FRAM_csum_set();						//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
}

/*
********************************************************************************
*  Module Name:		SEI_Worker_STP
*  Function Name:	���Y�Ǘ���ƏI��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2011-1-11		V06c
********************************************************************************
*/
void	SEI_Worker_STP(void)
{
	SV0SP_WORKER_COD	= SV_WORKER_COD	;		//��ƏI������ƎҺ��� SV0_WORKER_COD
	SV0SP_ORDER_COD		= HEX_BCD4(SV_ORDER_COD);	//��ƏI�������Ժ���SV0_ORDER_COD
	SV0SP_PLAN_CNT		= SV_PLAN_CNT		;		//��ƏI�����v�搔  SV0_PLAN_CNT
	SV0SP_BAD_CNT		= SV_BAD_CNT		;		//��ƏI�����s�ǐ�
	SV0SP_KATA_NO		= PV_MLDNO1_F1		;		//��ƏI�����^�ԍ�
	memcpy_word(&SV0SP_KATA_NAME[0], &PV_MLDNO2_F1[0],7)	;	//��ƏI�����^����
	memcpy_word(&SV0SP_KATA_MEMO[0], &PV_MLDNO3_F1[0],7)	;	//��ƏI�����^����

	SV0_WORK_STP_FLG = 0xA55A;			// C/B��

	SV_WORKER_ENT_FLG = 0;				//��Ǝғo�^����

	FRAM_csum_set();						//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
}













































/*
********************************************************************************
*  Module Name:		FURIKO_SW_del
*  Function Name:	�U�qSW�̕\���^��\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2013-2-19		V06p
********************************************************************************
*/
void	FURIKO_SW_del(void)
{
	if( CSR_TBL_POS_NOW == 0 ) {						//�J�[�\���͉�]�����̈ʒu
		if (SEQ_PAR_113 & BIT_15) {						//�U�q��\���w�߁iON=��\���j
			SW_buff[2].SUB_NO |= BIT_15;				//�U�q�̔�\���̐ݒ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		FURIKO_SW_chk
*  Function Name:	�U�qSW�̕\���^��\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2013-2-19		V06p
********************************************************************************
*/
void	FURIKO_SW_chk(void)
{
	if( CSR_TBL_POS_NOW == 0 ) {						//�J�[�\���͉�]�����̈ʒu
		if (SEQ_PAR_113 & BIT_15) {						//�U�q��\���w�߁iON=��\���j
			SW_buff[2].SUB_NO |= BIT_15;				//�U�q�̔�\���̐ݒ�
			disp_moji_s_paint(
				6,						//���p����
				368,					//X�n�_
				64,						//Y�n�_
				GAMENn_HEAD.scr_col,	//�h�ׂ��F
				0x0202,					//X2�{/Y2�{
				LCD_VRAM
				);
		}
		else {
			if (SEQ_023_SV & BIT_8) {					//�U�q�̎d�l�I��L���H
				SW_buff[2].SUB_NO &= ~BIT_15;			//�U�q�̔�\���̐ݒ�
				SWchg_disp_one(2);						//1�r�v�f�[�^���@�\��
			}
		}
	}
}


//;	*******************************************************************
//;	***																***
//;	***	�׏d�v�o�b�N�A�b�v�����s������v���O����					***	2007/10/05 V05i
//;	***																***
//;	*******************************************************************
void KJ_CHK_MEM_CLR(void)
{
	PV_OF_BAKL_X = PV_OF_BAKL;				//�I�t�Z�b�g�l��(1byte)				2007/10/30
	PV_OF_BAKR_X = PV_OF_BAKR;				//�I�t�Z�b�g�l�E(1byte)				2007/10/30

	PV_OF_AVE_BAKL_X = PV_OF_AVE_BAKL;		//�I�t�Z�b�g�␳��(1word)			2007/10/30
	PV_OF_AVE_BAKR_X = PV_OF_AVE_BAKR;		//�I�t�Z�b�g�␳�E(1word)			2007/10/30
	PV_OF_AVE_BAKT_X = PV_OF_AVE_BAKT;		//�I�t�Z�b�g�␳���v(1word)			2007/10/30

	PV_GAIN_BAK1L_X = PV_GAIN_BAK1L;		//�ő�c�݂Q�O�O�O���Q�C��(1word)	2007/10/30
	PV_GAIN_BAK1R_X = PV_GAIN_BAK1R;		//�ő�c�݂Q�O�O�O�E�Q�C��(1word)	2007/10/30
                      
	PV_GAIN_BAK2L_X = PV_GAIN_BAK2L;		//�ő�c�݂P�T�O�O���Q�C��(1word)	2007/10/30
	PV_GAIN_BAK2R_X = PV_GAIN_BAK2R;		//�ő�c�݂P�T�O�O�E�Q�C��(1word)	2007/10/30
                      
	PV_GAIN_BAK3L_X = PV_GAIN_BAK3L;		//�ő�c�݁@�W�O�O���Q�C��(1word)	2007/10/30
	PV_GAIN_BAK3R_X = PV_GAIN_BAK3R;		//�ő�c�݁@�W�O�O�E�Q�C��(1word)	2007/10/30
                      
	PV_GAIN_BAK4L_X = PV_GAIN_BAK4L;		//�ő�c�݁@�S�O�O���Q�C��(1word)	2007/10/30
	PV_GAIN_BAK4R_X = PV_GAIN_BAK4R;		//�ő�c�݁@�S�O�O�E�Q�C��(1word)	2007/10/30
                      
	PV_GAIN_BAK5L_X = PV_GAIN_BAK5L;		//�ő�c�݁@�Q�O�O���Q�C��(1word)	2007/10/30
	PV_GAIN_BAK5R_X = PV_GAIN_BAK5R;		//�ő�c�݁@�Q�O�O�E�Q�C��(1word)	2007/10/30

	KJ_CHK_CNT1		= 0;                /* �׏d�v�ޯ������ް�������������1 */
	KJ_CHK_CNT2		= 0;                /* �׏d�v�ޯ������ް�������������2 */
	KJ_CHK_CNT3		= 0;                /* �׏d�v�ޯ������ް�������������3 */
	KJ_CHK_CNT4		= 0;                /* �׏d�v�ޯ������ް�������������4 */
	KJ_CHK_CNT5		= 0;                /* �׏d�v�ޯ������ް�������������5 */
	KJ_CHK_CNT6		= 0;                /* �׏d�v�ޯ������ް�������������6 */
	KJ_CHK_CNT7		= 0;                /* �׏d�v�ޯ������ް�������������7 */
	KJ_CHK_CNT8		= 0;                /* �׏d�v�ޯ������ް�������������8 */
	KJ_CHK_CNT9		= 0;                /* �׏d�v�ޯ������ް�������������9 */
	KJ_CHK_CNT10	= 0;               /* �׏d�v�ޯ������ް�������������10 */
	KJ_CHK_CNT11	= 0;               /* �׏d�v�ޯ������ް�������������11 */
	KJ_CHK_CNT12	= 0;               /* �׏d�v�ޯ������ް�������������12 */
	KJ_CHK_CNT13	= 0;               /* �׏d�v�ޯ������ް�������������13 */
	KJ_CHK_CNT14	= 0;               /* �׏d�v�ޯ������ް�������������14 */
	KJ_CHK_CNT15	= 0;               /* �׏d�v�ޯ������ް�������������15 */
	KJ_CHK_DAT0		= 0;                /* �׏d�v�ޯ������ް����������ް�0 */
	KJ_CHK_DAT1		= 0;                /* �׏d�v�ޯ������ް����������ް�1 */
	KJ_CHK_DAT2		= 0;                /* �׏d�v�ޯ������ް����������ް�2 */
	KJ_CHK_DAT3		= 0;                /* �׏d�v�ޯ������ް����������ް�3 */
	KJ_CHK_DAT4		= 0;                /* �׏d�v�ޯ������ް����������ް�4 */
	KJ_CHK_DAT5		= 0;                /* �׏d�v�ޯ������ް����������ް�5 */
	KJ_CHK_DAT6		= 0;                /* �׏d�v�ޯ������ް����������ް�6 */
	KJ_CHK_DAT7		= 0;                /* �׏d�v�ޯ������ް����������ް�7 */
	KJ_CHK_DAT8		= 0;                /* �׏d�v�ޯ������ް����������ް�8 */
	KJ_CHK_DAT9		= 0;                /* �׏d�v�ޯ������ް����������ް�9 */
	KJ_CHK_DAT10	= 0;               /* �׏d�v�ޯ������ް����������ް�10 */
	KJ_CHK_DAT11	= 0;               /* �׏d�v�ޯ������ް����������ް�11 */
	KJ_CHK_DAT12	= 0;               /* �׏d�v�ޯ������ް����������ް�12 */
	KJ_CHK_DAT13	= 0;               /* �׏d�v�ޯ������ް����������ް�13 */
	KJ_CHK_DAT14	= 0;               /* �׏d�v�ޯ������ް����������ް�14 */
	KJ_CHK_DAT15	= 0;               /* �׏d�v�ޯ������ް����������ް�15 */
}


/*
********************************************************************************
*  Function Name:	��葬�x�ݒ�̃N���A
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2014/09/25
********************************************************************************
*/
void	mmon_f_off(UNs t_no)
{
	UNs		no, fbit;

	no = CSR_buff[t_no].DATA_NO;

	if ( (no >= 97) && (no <= 101) ) {
		no -= 97;
		if ( (GAMEN_NO == 3) || (GAMEN_NO == 28) ) {
			/* Ӱ���1�`5�i�ڐݒ� */
			fbit = cBIT0;
		}
		else {
			/* Ӱ���6�`10�i�ڐݒ� */
			fbit = cBIT5;
		}

		fbit <<= no;

//2014/10/09		SV_MOT_FIX &= ~fbit;
		if (SV0_MOT_FIX & fbit) {
			SV0_MOT_FIX = 0;
		}
	}
}


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	Ӱ��ݕ\���߰��(�i��)���ް������킹��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mot_page_dat_chg(void)
{
	UNs		cnt, t_no, step, bit, *inf;

	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {
		switch(SV_buff[t_no].GRP_NO) {
			default:
				break;
			case 86:
				/* 1�s�� �p�x */
				SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].DEG1;
				break;
			case 87:
				/* 2�s�� �p�x */
				SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].DEG2;
				break;
			case 88:
				/* 3�s�� �p�x */
				SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].DEG3;
				break;
			case 89:
				/* 4�s�� �p�x */
				SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].DEG4;
				break;
			case 90:
				/* 5�s�� �p�x */
				SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].DEG5;
				break;
			case 92:
				/* 1�s�� �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)MOT_PAGE_DAT[SV_MOT_PAGE].POS1;
				break;
			case 93:
				/* 2�s�� �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)MOT_PAGE_DAT[SV_MOT_PAGE].POS2;
				break;
			case 94:
				/* 3�s�� �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)MOT_PAGE_DAT[SV_MOT_PAGE].POS3;
				break;
			case 95:
				/* 4�s�� �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)MOT_PAGE_DAT[SV_MOT_PAGE].POS4;
				break;
			case 96:
				/* 5�s�� �ʒu */
				SV_buff[t_no].DATA_ADR = (UNs *)MOT_PAGE_DAT[SV_MOT_PAGE].POS5;
				break;
			case 97:
				if (SV_buff[t_no].AKI2 == 1) {
					/* 1�s�� ��~���� */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM1;
				}
				else {
					/* 1�s�� ���x */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].SPD1;
				}
				break;
			case 98:
				if (SV_buff[t_no].AKI2 == 1) {
					/* 2�s�� ��~���� */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM2;
				}
				else {
					/* 2�s�� ���x */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].SPD2;
				}
				break;
			case 99:
				if (SV_buff[t_no].AKI2 == 1) {
					/* 3�s�� ��~���� */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM3;
				}
				else {
					/* 3�s�� ���x */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].SPD3;
				}
				break;
			case 100:
				if (SV_buff[t_no].AKI2 == 1) {
					/* 4�s�� ��~���� */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM4;
				}
				else {
					/* 4�s�� ���x */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].SPD4;
				}
				break;
			case 101:
				if (SV_buff[t_no].AKI2 == 1) {
					/* 5�s�� ��~���� */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM5;
				}
				else {
					/* 5�s�� ���x */
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].SPD5;
				}
				break;
		}
	}

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {
		switch(SW_buff[t_no].GRP_NO) {
			default:
				break;
			case 97:
				/* 1�s�� ��~���� */
				if (SW_buff[t_no].CARA_NO == 35) {								//2016/04/15
					SW_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM1;
				}
				break;
			case 98:
				/* 2�s�� ��~���� */
				if (SW_buff[t_no].CARA_NO == 35) {								//2016/04/15
					SW_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM2;
				}
				break;
			case 99:
				/* 3�s�� ��~���� */
				if (SW_buff[t_no].CARA_NO == 35) {								//2016/04/15
					SW_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM3;
				}
				break;
			case 100:
				/* 4�s�� ��~���� */
				if (SW_buff[t_no].CARA_NO == 35) {								//2016/04/15
					SW_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM4;
				}
				break;
			case 101:
				/* 5�s�� ��~���� */
				if (SW_buff[t_no].CARA_NO == 35) {								//2016/04/15
					SW_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].TIM5;
				}
				break;
		}
	}

	step_chg_spd_make();				//�ϑ����쐬�i�Oor��j		2016/04/15
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	Ӱ��ݕ\���߰�ނ̖ڕW�ʒu��ڕW�׏d�ɕύX
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mot_page_kaj_chg(void)
{
	UNs		cnt, t_no, step, bit, *inf;

	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {
		switch(SV_buff[t_no].GRP_NO) {
			default:
				break;
			case 92:
				/* 1�s�� �ʒu->�׏d */
				step = (SV_MOT_PAGE * 5) + 0;
				step = step_pos_prs_chk(step);
				if ( step ) {													//�ڕW�׏d�H
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].PRS1;	//�i�[����ڽ�ύX
					SV_buff[t_no].BYTE_NO = 2;									//�޲Ē��̕ύX
					SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;						//�����_�ʒu
					SV_buff[t_no].TOK_FLG = 0;									//�����׸�
					SV_buff[t_no].SUB_NO = 123;									//���ٰ��No.
				}
				break;
			case 93:
				/* 2�s�� �ʒu->�׏d */
				step = (SV_MOT_PAGE * 5) + 1;
				step = step_pos_prs_chk(step);
				if ( step ) {													//�ڕW�׏d�H
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].PRS2;	//�i�[����ڽ�ύX
					SV_buff[t_no].BYTE_NO = 2;									//�޲Ē��̕ύX
					SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;						//�����_�ʒu
					SV_buff[t_no].TOK_FLG = 0;									//�����׸�
					SV_buff[t_no].SUB_NO = 123;									//���ٰ��No.
				}
				break;
			case 94:
				/* 3�s�� �ʒu->�׏d */
				step = (SV_MOT_PAGE * 5) + 2;
				step = step_pos_prs_chk(step);
				if ( step ) {													//�ڕW�׏d�H
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].PRS3;	//�i�[����ڽ�ύX
					SV_buff[t_no].BYTE_NO = 2;									//�޲Ē��̕ύX
					SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;						//�����_�ʒu
					SV_buff[t_no].TOK_FLG = 0;									//�����׸�
					SV_buff[t_no].SUB_NO = 123;									//���ٰ��No.
				}
				break;
			case 95:
				/* 4�s�� �ʒu->�׏d */
				step = (SV_MOT_PAGE * 5) + 3;
				step = step_pos_prs_chk(step);
				if ( step ) {													//�ڕW�׏d�H
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].PRS4;	//�i�[����ڽ�ύX
					SV_buff[t_no].BYTE_NO = 2;									//�޲Ē��̕ύX
					SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;						//�����_�ʒu
					SV_buff[t_no].TOK_FLG = 0;									//�����׸�
					SV_buff[t_no].SUB_NO = 123;									//���ٰ��No.
				}
				break;
			case 96:
				/* 5�s�� �ʒu->�׏d */
				step = (SV_MOT_PAGE * 5) + 4;
				step = step_pos_prs_chk(step);
				if ( step ) {													//�ڕW�׏d�H
					SV_buff[t_no].DATA_ADR = MOT_PAGE_DAT[SV_MOT_PAGE].PRS5;	//�i�[����ڽ�ύX
					SV_buff[t_no].BYTE_NO = 2;									//�޲Ē��̕ύX
					SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;						//�����_�ʒu
					SV_buff[t_no].TOK_FLG = 0;									//�����׸�
					SV_buff[t_no].SUB_NO = 123;									//���ٰ��No.
				}
				break;
		}
	}

	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {
		switch(PV_buff[t_no].GRP_NO) {
			default:
				break;
			case 97:
				/* 1�s�� �ʒu->�׏d */
				if(PV_buff[t_no].AKI2 == 1) {										//�ڕW�ʒu�P�� ���
					step = (SV_MOT_PAGE * 5) + 0;
					step = step_pos_prs_chk(step);
					if ( step ) {													//�ڕW�׏d�H
						PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;				//�P��
					}
				}
				break;
			case 98:
				/* 1�s�� �ʒu->�׏d */
				if(PV_buff[t_no].AKI2 == 1) {										//�ڕW�ʒu�P�� ���
					step = (SV_MOT_PAGE * 5) + 1;
					step = step_pos_prs_chk(step);
					if ( step ) {													//�ڕW�׏d�H
						PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;				//�P��
					}
				}
				break;
			case 99:
				/* 1�s�� �ʒu->�׏d */
				if(PV_buff[t_no].AKI2 == 1) {										//�ڕW�ʒu�P�� ���
					step = (SV_MOT_PAGE * 5) + 2;
					step = step_pos_prs_chk(step);
					if ( step ) {													//�ڕW�׏d�H
						PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;				//�P��
					}
				}
				break;
			case 100:
				/* 1�s�� �ʒu->�׏d */
				if(PV_buff[t_no].AKI2 == 1) {										//�ڕW�ʒu�P�� ���
					step = (SV_MOT_PAGE * 5) + 3;
					step = step_pos_prs_chk(step);
					if ( step ) {													//�ڕW�׏d�H
						PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;				//�P��
					}
				}
				break;
			case 101:
				/* 1�s�� �ʒu->�׏d */
				if(PV_buff[t_no].AKI2 == 1) {										//�ڕW�ʒu�P�� ���
					step = (SV_MOT_PAGE * 5) + 4;
					step = step_pos_prs_chk(step);
					if ( step ) {													//�ڕW�׏d�H
						PV_buff[t_no].DATA_ADR = (UNs *)&CAR_KAJ_AREA;				//�P��
					}
				}
				break;
		}
	}
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	�s�����ύX������&�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mmon_step_chg_disp(void)
{
	if (SV_DANSUU_SRV != SV_DANSUU_SRV_BAK) {			//�H���� �ω�����H
		SV_DANSUU_SRV_BAK = SV_DANSUU_SRV;
		SV_MOT_PAGE_INIT();
		GAMEN_disp();
	}
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	�w��s���̖ڕW�m�F�i�ʒuor�׏d�j
*  Input	:		�s��No.0�`99�i��1�`100�j
*  Return	: 		0���ڕW�ʒu  1���ڕW�׏d
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
UNs		step_pos_prs_chk(UNs step)
{
	UNs		ans, *inf, bit;

	inf = &SV_MOTTGT_INF0;
	inf += step / 16;								//�ʒu�^�׏d����̈�
	bit = BIT_0;
	bit <<= step % 16;								//�ʒu�^�׏d����BIT
	if (*inf & bit) {
		ans = 1;									//�ڕW�׏d
	}
	else {
		ans = 0;									//�ڕW�ʒu
	}
	return(ans);
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	�ڕW�p���I�[�o�[���Ă���s�̃r�b�g�����쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mmon_agl_ovbit_make(void)
{
	UNs		step, cnt, bit, inf, ovbit, onbit;
	
	step = SV_MOT_PAGE * 5;						//1�s�ڂ̍s��No.0�`99(=1�`100)
	ovbit = 0;
	onbit = cBIT0;

	for (cnt=0; cnt<5; cnt++, step++, onbit<<=1) {
		if (step < SV_DANSUU_SRV) {
			if (PVP_MOT_STS[step] & cBIT1) {		//�I�[�o�[BIT ON�H
				ovbit |= onbit;
			}
		}
	}
	PV0_CKAGL_OVBIT = ovbit;
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	���x���I�[�o�[���Ă���s�̃r�b�g�����쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mmon_spd_ovbit_make(void)
{
	UNs		step, cnt, bit, inf, ovbit, onbit, page;
	
	step = SV_MOT_PAGE * 5;						//1�s�ڂ̍s��No.0�`99(=1�`100)
	ovbit = 0;
	onbit = cBIT0;

	for (cnt=0; cnt<5; cnt++, step++, onbit<<=1) {
		if (step < SV_DANSUU_SRV) {
			if (PVP_MOT_STS[step] & cBIT0) {	//�I�[�o�[BIT ON�H
				ovbit |= onbit;
			}
		}
	}

	page = (SV_DANSUU_SRV -1 ) / 5;
	if (SV_MOT_PAGE == page) {					//�ŏI�y�[�W�H
		if (PVP_MOT_STS[99] & cBIT0) {			//�I�[�o�[BIT ON�H
			ovbit |= cBIT14+cBIT15;
		}
	}

	PV0_CKSPD_OVBIT = ovbit;
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	���x���Ⴗ����s�̃r�b�g�����쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mmon_spd_lmbit_make(void)
{
	UNs		step, cnt, bit, inf, lmbit, onbit, page;
	
	step = SV_MOT_PAGE * 5;						//1�s�ڂ̍s��No.0�`99(=1�`100)
	lmbit = 0;
	onbit = cBIT0;

	for (cnt=0; cnt<5; cnt++, step++, onbit<<=1) {
////		if (step < SV_DANSUU_SRV) {
////			inf = PVP_CKSPD_LMBIT1[step/16];
////			bit = cBIT0;
////			bit <<= step % 16;
////			if (inf & bit) {						//�I�[�o�[BIT ON�H
////				lmbit |= onbit;
////			}
////		}
		if (step < SV_DANSUU_SRV) {
			if (PVP_MOT_STS[step] & cBIT2) {	//�I�[�o�[BIT ON�H
				lmbit |= onbit;
			}
		}
	}

	page = (SV_DANSUU_SRV -1 ) / 5;
	if (SV_MOT_PAGE == page) {					//�ŏI�y�[�W�H
////		inf = PVP_CKSPD_LMBIT1[6];
////		if (inf & cBIT15) {
////			lmbit |= cBIT14+cBIT15;
////		}
		if (PVP_MOT_STS[99] & cBIT2) {			//�I�[�o�[BIT ON�H
			lmbit |= cBIT14+cBIT15;
		}
	}

	PV0_CKSPD_LMBIT = lmbit;
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	���[�V�������s�s���̃r�b�g�����쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2015-08-21
********************************************************************************
*/
void	mmon_act_step_bit_make(void)
{
	UNs		step, onbit, page;
	
	if (PVP_MOT_ACT_STEP == 0) {
		PV0_MOT_ACT_STEP = 0;
	}
	else if (PVP_MOT_ACT_STEP == 100) {
		page = (SV_DANSUU_SRV -1 ) / 5;
		if (SV_MOT_PAGE == page) {					//�ŏI�y�[�W�H
			PV0_MOT_ACT_STEP = cBIT5;				//�߂�s����
		}
	}
	else if (PVP_MOT_ACT_STEP > 100) {
		PV0_MOT_ACT_STEP = 0;
	}
	else {
		step = PVP_MOT_ACT_STEP - 1;
		page = step / 5;
		if (SV_MOT_PAGE == page) {					//���s�s���͕\���y�[�W�ɂ���H
			onbit = cBIT0;
			onbit <<= step % 5;
			PV0_MOT_ACT_STEP = onbit;				//1�`5�s�ڂ̍s����
		}
		else {
			PV0_MOT_ACT_STEP = 0;
		}
	}
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	���[�V�����ύX�s���̑��M�v��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shimamura		ON:2015/09/23
********************************************************************************
*/
void	MOT_CHG_REQ(UNs t_no)
{
	UNs		no, cnt;

	no = CSR_buff[t_no].DATA_NO;

	if ( (no >= 97) && (no <= 101) ) {
		no -= 97;
		no += 1;

		no = SV_MOT_PAGE * 5 + no;					//�ύX���������s��No.

		for (cnt=0; cnt<5; cnt++) {
			if (MOT_CHG_NO[cnt] == 0) {
				MOT_CHG_NO[cnt] = no;
				break;
			}
		}
	}
}
#endif


#if (mot100_test == 1)
/*
********************************************************************************
*  Function Name:	�w��s���̕ϑ��m�F�i�Oor��j
*  Input	:		�s��No.0�`99�i��1�`100�j
*  Return	: 		0���O  1����
*  Note		:
*
*  �� ��	:Shima		ON:2016/04/15
********************************************************************************
*/
UNs		step_chg_spd_chk(UNs step)
{
	UNs		ans, *inf, bit;

	inf = &SV_MOT_CSUD_INF0;
	inf += step / 16;								//�ʒu�^�׏d����̈�
	bit = BIT_0;
	bit <<= step % 16;								//�ʒu�^�׏d����BIT
	if (*inf & bit) {
		ans = 1;									//�ڕW�׏d
	}
	else {
		ans = 0;									//�ڕW�ʒu
	}
	return(ans);
}


/*
********************************************************************************
*  Function Name:	�w��s���̕ϑ��ݒ�i�Oor��j
*  Input	:		�s��No.0�`99�i��1�`100�j
*  Return	: 		0���O  1����
*  Note		:
*
*  �� ��	:Shima		ON:2016/04/15
********************************************************************************
*/
void	step_chg_spd_set(UNs step, UNs onof)
{
	UNs		ans, *inf, bit;

	inf = &SV_MOT_CSUD_INF0;
	inf += step / 16;								//�O�^�㔻��̈�
	bit = BIT_0;
	bit <<= step % 16;								//�O�^�㔻��BIT

	if (onof) {
		*inf |= bit;
	}
	else {
		*inf &= ~bit;
	}
}


/*
********************************************************************************
*  Function Name:	�ϑ����쐬�i�Oor��j
*  Input	:		����
*  Return	:		����
*  Note		:
*
*  �� ��	:Shima		ON:2016/04/15
********************************************************************************
*/
void	step_chg_spd_make(void)
{
	UNs		ans, *inf, bit, on, step, cnt;

	step = SV_MOT_PAGE * 5;						//1�s�ڂ̍s��No.0�`99(=1�`100)
	step += 4;

	inf = &SV_MOT_CSUD_INF0;
	inf += step / 16;								//�O�^�㔻��̈�
	bit = BIT_0;
	bit <<= step % 16;								//�O�^�㔻��BIT
	ans = 0;
	on = BIT_4;

	for (cnt=0; cnt<5; cnt++, bit>>=1, on>>=1) {
		if (bit == 0) {
			inf--;
			bit = BIT_15;
			break;
		}
		if (*inf & bit) {
			ans |= on;
		}
	}

	for ( ; cnt<5; cnt++, bit>>=1, on>>=1) {
		if (*inf & bit) {
			ans |= on;
		}
	}

	SV0_MOT_BFAF = ans;
}
#endif


/*** END ***/
