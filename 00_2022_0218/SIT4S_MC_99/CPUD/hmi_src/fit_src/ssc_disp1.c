/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			��@�ʁ@�\�@��															*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-29
*
*************************************************************************************/

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	DATA_svsw(UNs, UNs);					//
UNi		MIS_check(void);						//�~�X�t�B�[�h�L���`�F�b�N
UNi		ROT1_check(void);						//���[�^���J���P�`�W�L���`�F�b�N
UNi		ROT2_check(void);						//���[�^���J���X�`�P�U�L���`�F�b�N
UNi		ROT3_check(void);						//���[�^���J���P�V�`�Q�O�L���`�F�b�N
UNi		EJE_check(void);						//�G�W�F�N�^�L���`�F�b�N

void	DISP_cam_csr_name(void);				//�J���J�[�\�����̕\��

void	CAM_next_cls(UNs);						//�ݒ�l�̎��̃L�����N�^���X�y�[�X
void	LENG_svpv(UNs, UNs);					//�����_�̕ύX(�ݒ�l&�����l)
void	CSR_cls(UNs, UNs, UNs);					//���ُ��ð��ق̔�\�� �ݒ�
void	SV_cls(UNs, UNs, UNs);					//�ݒ�l���ð��ق̔�\�� �ݒ�
void	PV_cls(UNs, UNs, UNs);					//�����l���ð��ق̔�\�� �ݒ�
void	SW_cls(UNs, UNs, UNs);					//SW�ް����ð��ق̔�\�� �ݒ�
void	EJE_grp(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);	//��ު���p�ݒ�l���ð��ق̔�\�� �ݒ�
void	EJE_csr(UNs, UNs, UNs, UNs, UNs, UNs);	//��ު���p���ُ��ð��ق̐ݒ�l����������
void	EJE_sw(UNs, UNs, UNs);					//��ު���pSW�ް����ð��ق̏�������
void	ROT_cam_sv(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);		//۰�ضїp�ݒ�l���ð��ق̏�������
void	ROT_cam_sw(UNs, UNs, UNs, UNs, UNs);	//۰�ضїpSW�ް����ð��ق̏�������
void	ROT_cam_csr(UNs, UNs, UNs, UNs, UNs, UNs, UNs);			//۰�ضїp���ُ��ð��ق̏�������
void	MIS_sv(UNs, UNs, UNs);					//н̨��ޗp�ݒ�l���ð��ق̔�\�� �ݒ�
void	MIS_csr(UNs, UNs, UNs, UNs, UNs);		//н̨��ޗp���ُ��ð��ق̏�������
void	ATU_svpv(UNs, UNs);						//�ݒ�l���ð��ق̕ύX
void	DANsel_csr(UNs, UNs, UNs, UNs);			//н̨��ޗp���ُ��ð��ق̏�������
void	DAN_sel(UNs *, UNs, UNs, UNs);			//�i���p�@�e�I���̏�������
void	DAN_csr_set(void);						//�i���ʁ@�\���������J�E���^
void	KAT_cls(UNs, UNs, UNs, UNs);			//�^�ް��̎����l���ð��ق̔�\�� �ݒ�
void	MEMO_cls(UNs, UNs, UNs, UNs);			//�����̎����l���ð��ق̔�\�� �ݒ�
void	PVdata_non_sub(void);					//�����l���ð��ق̔�\�� �ݒ�
void	SCAN_kat_cls(void);						//
void	NAME_cls_sub(void);						//��ꌾ��@���ł̔�\��
void	MISS_swcara(void);						//н̨���SW�\����א؊����̔�\��
void	MISS56_swcara(void);						//н̨���SW�\����א؊����̔�\��
void	MISS_swcara_win(void);					//н̨���SW�\����א؊����̔�\��(����޳�p)

void	mmon_tbl_cls(UNs);						//Ӱ��ݐݒ�@���ð��ق̔�\�� �ݒ�
void	mmon_tbl_open(UNs);						//Ӱ��ݐݒ�@���ð��ق̕\�� �ݒ�
void	grpno_sv_cls(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̔�\�� �ݒ�
void	grpno_sv_open(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̕\�� �ݒ�
UNs		grpno_sv_srch(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��

void	kag_to_kaj_sub_chg(void);				//�����ʒu���ڕW�׏d ���ٰ��No.�؊�


/* �����ϐ���` ------------------------------------------------------ */
UNs		SV_GENGO_KAT;

/* �e�[�u����` ------------------------------------------------------ */

const	UNs *	SW56_Cam_Name_Tbl[69]={
			&PV_CAMNA01_C1[0],		//80/* ���[�^���J���P���� */
			&PV_CAMNA02_C1[0],		//81/* ���[�^���J���Q���� */
			&PV_CAMNA03_C1[0],		//82/* ���[�^���J���R���� */
			&PV_CAMNA04_C1[0],		//83/* ���[�^���J���S���� */
			&PV_CAMNA05_C1[0],		//84/* ���[�^���J���T���� */
			&PV_CAMNA06_C1[0],		//85/* ���[�^���J���U���� */
			&PV_CAMNA07_C1[0],		//86/* ���[�^���J���V���� */
			&PV_CAMNA08_C1[0],		//87/* ���[�^���J���W���� */
			&PV_CAMNA09_C1[0],		//88/* ���[�^���J���X���� */
			&PV_CAMNA10_C1[0],		//89/* ���[�^���J���P�O���� */
			&PV_CAMNA11_C1[0],		//8A/* ���[�^���J���P�P���� */
			&PV_CAMNA12_C1[0],		//8B/* ���[�^���J���P�Q���� */
			&PV_CAMNA13_C1[0],		//8C/* ���[�^���J���P�R���� */
			&PV_CAMNA14_C1[0],		//8D/* ���[�^���J���P�S���� */
			&PV_CAMNA15_C1[0],		//8E/* ���[�^���J���P�T���� */
			&PV_CAMNA16_C1[0],		//8F/* ���[�^���J���P�U���� */
			&PV_CAMNAM_C1[0],		//90
			&SV_EJENAM01_C1[0],		//91/* �G�W�F�N�^�P */
			&SV_EJENAM02_C1[0],		//92/* �G�W�F�N�^�Q */
			&SV_EJENAM03_C1[0],		//93/* �G�W�F�N�^�R */
			&SV_EJENAM04_C1[0],		//94/* �G�W�F�N�^�S */
			&SV_EJENAM05_C1[0],		//95/* �G�W�F�N�^�T */
			&SV_EJENAM06_C1[0],		//96/* �G�W�F�N�^�U */
//			&PV_EJECT1_NAME,		//91/* �G�W�F�N�^�P */
//			&PV_EJECT2_NAME,		//92/* �G�W�F�N�^�P */
//			&PV_EJECT3_NAME,		//93/* �G�W�F�N�^�P */
//			&PV_EJECT4_NAME,		//94/* �G�W�F�N�^�P */
//			&PV_EJECT5_NAME,		//95/* �G�W�F�N�^�P */
//			&PV_EJECT6_NAME,		//96/* �G�W�F�N�^�P */
			&PV_KOUMOKU1_NAME[0],	//97/* ���ڔԍ��P�@ */
			&PV_KOUMOKU2_NAME[0],	//98/* ���ڔԍ��Q�@ */
			&PV_KOUMOKU3_NAME[0],	//99/* ���ڔԍ��R�@ */
			&PV_KOUMOKU4_NAME[0],	//9A/* ���ڔԍ��S�@ */
			&PV_CAMNA17_C1[0],		//9B/* ���[�^���J���P�V���� */
			&PV_CAMNA18_C1[0],		//9C/* ���[�^���J���P�W���� */
			&PV_CAMNA19_C1[0],		//9D/* ���[�^���J���P�X���� */
			&PV_CAMNA20_C1[0],		//9E/* ���[�^���J���Q�O���� */
			&PV_CAMNAM_C1[0],		//9F/* �\�� */
			&KAT_NAME_01[0],		//A0/* �^�f�[�^���̂P */
			&KAT_NAME_02[0],		//A1/* �^�f�[�^���̂Q */
			&KAT_NAME_03[0],		//A2/* �^�f�[�^���̂R */
			&KAT_NAME_04[0],		//A3/* �^�f�[�^���̂S */
			&KAT_NAME_05[0],		//A4/* �^�f�[�^���̂T */
			&KAT_NAME_06[0],		//A5/* �^�f�[�^���̂U */
			&KAT_NAME_07[0],		//A6/* �^�f�[�^���̂V */
			&KAT_NAME_08[0],		//A7/* �^�f�[�^���̂W */
			&KAT_NAME_09[0],		//A8/* �^�f�[�^���̂X */
			&KAT_NAME_10[0],		//A9/* �^�f�[�^����1�O */
			&PV_MLDNO2_F0[0],		//AA/* �^�ް� ���́������̌��ݕ\�� */
			&KAT_MEMO_01[0],		//AB/* �^�f�[�^�����P */
			&KAT_MEMO_02[0],		//AC/* �^�f�[�^�����Q */
			&KAT_MEMO_03[0],		//AD/* �^�f�[�^�����R */
			&KAT_MEMO_04[0],		//AE/* �^�f�[�^�����S */
			&KAT_MEMO_05[0],		//AF/* �^�f�[�^�����T */
			&KAT_MEMO_06[0],		//B0/* �^�f�[�^�����U */
			&KAT_MEMO_07[0],		//B1/* �^�f�[�^�����V */
			&KAT_MEMO_08[0],		//B2/* �^�f�[�^�����W */
			&KAT_MEMO_09[0],		//B3/* �^�f�[�^�����X */
			&KAT_MEMO_10[0],		//B4/* �^�f�[�^����1�O */
			&PV_KINOU01_NAE[0],		//B5/* �@�\�I�����ڂP �@*/
			&PV_KINOU02_NAE[0],		//B6/* �@�\�I�����ڂQ �@*/
			&PV_KINOU03_NAE[0],		//B7/* �@�\�I�����ڂR�@ */
			&PV_KINOU04_NAE[0],		//B8/* �@�\�I�����ڂS �@*/
			&PV_KINOU05_NAE[0],		//B9/* �@�\�I�����ڂT �@*/
			&PV_KINOU06_NAE[0],		//BA/* �@�\�I�����ڂU �@*/
			&PV_KINOU07_NAE[0],		//BB/* �@�\�I�����ڂV �@*/
			&PV_KINOU08_NAE[0],		//BC/* �@�\�I�����ڂW �@*/
			&PV_KINOU09_NAE[0],		//BD/* �@�\�I�����ڂX �@*/
			&PV_KINOU10_NAE[0],		//BE/* �@�\�I�����ڂP�O */
			&PV_KINOU11_NAE[0],		//BF/* �@�\�I�����ڂP�P */
			&PV_KINOU12_NAE[0],		//C0/* �@�\�I�����ڂP�Q */
			&PV_KINOU13_NAE[0],		//C1/* �@�\�I�����ڂP�R */
			&PV_KINOU14_NAE[0],		//C2/* �@�\�I�����ڂP�S */
			&PV_KINOU15_NAE[0],		//C3/* �@�\�I�����ڂP�T */
			&PV_KINOU16_NAE[0]		//C4/* �@�\�I�����ڂP�U */
		};

//�^�ް� ���̗̈�̱��ڽ�ð���
//const	UNs *	KAT_sv_name_tbl[101] = {
//const	UNs *	KAT_sv_name_tbl[201] = {		//V06n
const	UNs *	KAT_sv_name_tbl[221] = {		//2014/04/16	SIT-4 MC
		&KAT_NAME_01[0],			/* �_�~�[ */
		&KAT_NAME_01[0],			/* �^�f�[�^���̂P */
		&KAT_NAME_02[0],			/* �^�f�[�^���̂Q */
		&KAT_NAME_03[0],			/* �^�f�[�^���̂R */
		&KAT_NAME_04[0],			/* �^�f�[�^���̂S */
		&KAT_NAME_05[0],			/* �^�f�[�^���̂T */
		&KAT_NAME_06[0],			/* �^�f�[�^���̂U */
		&KAT_NAME_07[0],			/* �^�f�[�^���̂V */
		&KAT_NAME_08[0],			/* �^�f�[�^���̂W */
		&KAT_NAME_09[0],			/* �^�f�[�^���̂X */
		&KAT_NAME_10[0],			/* �^�f�[�^���̂P�O */
		&KAT_NAME_11[0],			/* �^�f�[�^���̂P�P */
		&KAT_NAME_12[0],			/* �^�f�[�^���̂P�Q */
		&KAT_NAME_13[0],			/* �^�f�[�^���̂P�R */
		&KAT_NAME_14[0],			/* �^�f�[�^���̂P�S */
		&KAT_NAME_15[0],			/* �^�f�[�^���̂P�T */
		&KAT_NAME_16[0],			/* �^�f�[�^���̂P�U */
		&KAT_NAME_17[0],			/* �^�f�[�^���̂P�V */
		&KAT_NAME_18[0],			/* �^�f�[�^���̂P�W */
		&KAT_NAME_19[0],			/* �^�f�[�^���̂P�X */
		&KAT_NAME_20[0],			/* �^�f�[�^���̂Q�O */
		&KAT_NAME_21[0],			/* �^�f�[�^���̂Q�P */
		&KAT_NAME_22[0],			/* �^�f�[�^���̂Q�Q */
		&KAT_NAME_23[0],			/* �^�f�[�^���̂Q�R */
		&KAT_NAME_24[0],			/* �^�f�[�^���̂Q�S */
		&KAT_NAME_25[0],			/* �^�f�[�^���̂Q�T */
		&KAT_NAME_26[0],			/* �^�f�[�^���̂Q�U */
		&KAT_NAME_27[0],			/* �^�f�[�^���̂Q�V */
		&KAT_NAME_28[0],			/* �^�f�[�^���̂Q�W */
		&KAT_NAME_29[0],			/* �^�f�[�^���̂Q�X */
		&KAT_NAME_30[0],			/* �^�f�[�^���̂R�O */
		&KAT_NAME_31[0],			/* �^�f�[�^���̂R�P */
		&KAT_NAME_32[0],			/* �^�f�[�^���̂R�Q */
		&KAT_NAME_33[0],			/* �^�f�[�^���̂R�R */
		&KAT_NAME_34[0],			/* �^�f�[�^���̂R�S */
		&KAT_NAME_35[0],			/* �^�f�[�^���̂R�T */
		&KAT_NAME_36[0],			/* �^�f�[�^���̂R�U */
		&KAT_NAME_37[0],			/* �^�f�[�^���̂R�V */
		&KAT_NAME_38[0],			/* �^�f�[�^���̂R�W */
		&KAT_NAME_39[0],			/* �^�f�[�^���̂R�X */
		&KAT_NAME_40[0],			/* �^�f�[�^���̂S�O */
		&KAT_NAME_41[0],			/* �^�f�[�^���̂S�P */
		&KAT_NAME_42[0],			/* �^�f�[�^���̂S�Q */
		&KAT_NAME_43[0],			/* �^�f�[�^���̂S�R */
		&KAT_NAME_44[0],			/* �^�f�[�^���̂S�S */
		&KAT_NAME_45[0],			/* �^�f�[�^���̂S�T */
		&KAT_NAME_46[0],			/* �^�f�[�^���̂S�U */
		&KAT_NAME_47[0],			/* �^�f�[�^���̂S�V */
		&KAT_NAME_48[0],			/* �^�f�[�^���̂S�W */
		&KAT_NAME_49[0],			/* �^�f�[�^���̂S�X */
		&KAT_NAME_50[0],			/* �^�f�[�^���̂T�O */
		&KAT_NAME_51[0],			/* �^�f�[�^���̂T�P */
		&KAT_NAME_52[0],			/* �^�f�[�^���̂T�Q */
		&KAT_NAME_53[0],			/* �^�f�[�^���̂T�R */
		&KAT_NAME_54[0],			/* �^�f�[�^���̂T�S */
		&KAT_NAME_55[0],			/* �^�f�[�^���̂T�T */
		&KAT_NAME_56[0],			/* �^�f�[�^���̂T�U */
		&KAT_NAME_57[0],			/* �^�f�[�^���̂T�V */
		&KAT_NAME_58[0],			/* �^�f�[�^���̂T�W */
		&KAT_NAME_59[0],			/* �^�f�[�^���̂T�X */
		&KAT_NAME_60[0],			/* �^�f�[�^���̂U�O */
		&KAT_NAME_61[0],			/* �^�f�[�^���̂U�P */
		&KAT_NAME_62[0],			/* �^�f�[�^���̂U�Q */
		&KAT_NAME_63[0],			/* �^�f�[�^���̂U�R */
		&KAT_NAME_64[0],			/* �^�f�[�^���̂U�S */
		&KAT_NAME_65[0],			/* �^�f�[�^���̂U�T */
		&KAT_NAME_66[0],			/* �^�f�[�^���̂U�U */
		&KAT_NAME_67[0],			/* �^�f�[�^���̂U�V */
		&KAT_NAME_68[0],			/* �^�f�[�^���̂U�W */
		&KAT_NAME_69[0],			/* �^�f�[�^���̂U�X */
		&KAT_NAME_70[0],			/* �^�f�[�^���̂V�O */
		&KAT_NAME_71[0],			/* �^�f�[�^���̂V�P */
		&KAT_NAME_72[0],			/* �^�f�[�^���̂V�Q */
		&KAT_NAME_73[0],			/* �^�f�[�^���̂V�R */
		&KAT_NAME_74[0],			/* �^�f�[�^���̂V�S */
		&KAT_NAME_75[0],			/* �^�f�[�^���̂V�T */
		&KAT_NAME_76[0],			/* �^�f�[�^���̂V�U */
		&KAT_NAME_77[0],			/* �^�f�[�^���̂V�V */
		&KAT_NAME_78[0],			/* �^�f�[�^���̂V�W */
		&KAT_NAME_79[0],			/* �^�f�[�^���̂V�X */
		&KAT_NAME_80[0],			/* �^�f�[�^���̂W�O */
		&KAT_NAME_81[0],			/* �^�f�[�^���̂W�P */
		&KAT_NAME_82[0],			/* �^�f�[�^���̂W�Q */
		&KAT_NAME_83[0],			/* �^�f�[�^���̂W�R */
		&KAT_NAME_84[0],			/* �^�f�[�^���̂W�S */
		&KAT_NAME_85[0],			/* �^�f�[�^���̂W�T */
		&KAT_NAME_86[0],			/* �^�f�[�^���̂W�U */
		&KAT_NAME_87[0],			/* �^�f�[�^���̂W�V */
		&KAT_NAME_88[0],			/* �^�f�[�^���̂W�W */
		&KAT_NAME_89[0],			/* �^�f�[�^���̂W�X */
		&KAT_NAME_90[0],			/* �^�f�[�^���̂X�O */
		&KAT_NAME_91[0],			/* �^�f�[�^���̂X�P */
		&KAT_NAME_92[0],			/* �^�f�[�^���̂X�Q */
		&KAT_NAME_93[0],			/* �^�f�[�^���̂X�R */
		&KAT_NAME_94[0],			/* �^�f�[�^���̂X�S */
		&KAT_NAME_95[0],			/* �^�f�[�^���̂X�T */
		&KAT_NAME_96[0],			/* �^�f�[�^���̂X�U */
		&KAT_NAME_97[0],			/* �^�f�[�^���̂X�V */
		&KAT_NAME_98[0],			/* �^�f�[�^���̂X�W */
		&KAT_NAME_99[0],			/* �^�f�[�^���̂X�X */
		&KAT_NAME_100[0],			/* �^�f�[�^���̂P�O�O */
		&KAT_NAME_101[0],			/* �^�f�[�^���̂P�O�P */
		&KAT_NAME_102[0],			/* �^�f�[�^���̂P�O�Q */
		&KAT_NAME_103[0],			/* �^�f�[�^���̂P�O�R */
		&KAT_NAME_104[0],			/* �^�f�[�^���̂P�O�S */
		&KAT_NAME_105[0],			/* �^�f�[�^���̂P�O�T */
		&KAT_NAME_106[0],			/* �^�f�[�^���̂P�O�U */
		&KAT_NAME_107[0],			/* �^�f�[�^���̂P�O�V */
		&KAT_NAME_108[0],			/* �^�f�[�^���̂P�O�W */
		&KAT_NAME_109[0],			/* �^�f�[�^���̂P�O�X */
		&KAT_NAME_110[0],			/* �^�f�[�^���̂P�P�O */
		&KAT_NAME_111[0],			/* �^�f�[�^���̂P�P�P */
		&KAT_NAME_112[0],			/* �^�f�[�^���̂P�P�Q */
		&KAT_NAME_113[0],			/* �^�f�[�^���̂P�P�R */
		&KAT_NAME_114[0],			/* �^�f�[�^���̂P�P�S */
		&KAT_NAME_115[0],			/* �^�f�[�^���̂P�P�T */
		&KAT_NAME_116[0],			/* �^�f�[�^���̂P�P�U */
		&KAT_NAME_117[0],			/* �^�f�[�^���̂P�P�V */
		&KAT_NAME_118[0],			/* �^�f�[�^���̂P�P�W */
		&KAT_NAME_119[0],			/* �^�f�[�^���̂P�P�X */
		&KAT_NAME_120[0],			/* �^�f�[�^���̂P�Q�O */
		&KAT_NAME_121[0],			/* �^�f�[�^���̂P�Q�P */
		&KAT_NAME_122[0],			/* �^�f�[�^���̂P�Q�Q */
		&KAT_NAME_123[0],			/* �^�f�[�^���̂P�Q�R */
		&KAT_NAME_124[0],			/* �^�f�[�^���̂P�Q�S */
		&KAT_NAME_125[0],			/* �^�f�[�^���̂P�Q�T */
		&KAT_NAME_126[0],			/* �^�f�[�^���̂P�Q�U */
		&KAT_NAME_127[0],			/* �^�f�[�^���̂P�Q�V */
		&KAT_NAME_128[0],			/* �^�f�[�^���̂P�Q�W */
		&KAT_NAME_129[0],			/* �^�f�[�^���̂P�Q�X */
		&KAT_NAME_130[0],			/* �^�f�[�^���̂P�R�O */
		&KAT_NAME_131[0],			/* �^�f�[�^���̂P�R�P */
		&KAT_NAME_132[0],			/* �^�f�[�^���̂P�R�Q */
		&KAT_NAME_133[0],			/* �^�f�[�^���̂P�R�R */
		&KAT_NAME_134[0],			/* �^�f�[�^���̂P�R�S */
		&KAT_NAME_135[0],			/* �^�f�[�^���̂P�R�T */
		&KAT_NAME_136[0],			/* �^�f�[�^���̂P�R�U */
		&KAT_NAME_137[0],			/* �^�f�[�^���̂P�R�V */
		&KAT_NAME_138[0],			/* �^�f�[�^���̂P�R�W */
		&KAT_NAME_139[0],			/* �^�f�[�^���̂P�R�X */
		&KAT_NAME_140[0],			/* �^�f�[�^���̂P�S�O */
		&KAT_NAME_141[0],			/* �^�f�[�^���̂P�S�P */
		&KAT_NAME_142[0],			/* �^�f�[�^���̂P�S�Q */
		&KAT_NAME_143[0],			/* �^�f�[�^���̂P�S�R */
		&KAT_NAME_144[0],			/* �^�f�[�^���̂P�S�S */
		&KAT_NAME_145[0],			/* �^�f�[�^���̂P�S�T */
		&KAT_NAME_146[0],			/* �^�f�[�^���̂P�S�U */
		&KAT_NAME_147[0],			/* �^�f�[�^���̂P�S�V */
		&KAT_NAME_148[0],			/* �^�f�[�^���̂P�S�W */
		&KAT_NAME_149[0],			/* �^�f�[�^���̂P�S�X */
		&KAT_NAME_150[0],			/* �^�f�[�^���̂P�T�O */
		&KAT_NAME_151[0],			/* �^�f�[�^���̂P�T�P */
		&KAT_NAME_152[0],			/* �^�f�[�^���̂P�T�Q */
		&KAT_NAME_153[0],			/* �^�f�[�^���̂P�T�R */
		&KAT_NAME_154[0],			/* �^�f�[�^���̂P�T�S */
		&KAT_NAME_155[0],			/* �^�f�[�^���̂P�T�T */
		&KAT_NAME_156[0],			/* �^�f�[�^���̂P�T�U */
		&KAT_NAME_157[0],			/* �^�f�[�^���̂P�T�V */
		&KAT_NAME_158[0],			/* �^�f�[�^���̂P�T�W */
		&KAT_NAME_159[0],			/* �^�f�[�^���̂P�T�X */
		&KAT_NAME_160[0],			/* �^�f�[�^���̂P�U�O */
		&KAT_NAME_161[0],			/* �^�f�[�^���̂P�U�P */
		&KAT_NAME_162[0],			/* �^�f�[�^���̂P�U�Q */
		&KAT_NAME_163[0],			/* �^�f�[�^���̂P�U�R */
		&KAT_NAME_164[0],			/* �^�f�[�^���̂P�U�S */
		&KAT_NAME_165[0],			/* �^�f�[�^���̂P�U�T */
		&KAT_NAME_166[0],			/* �^�f�[�^���̂P�U�U */
		&KAT_NAME_167[0],			/* �^�f�[�^���̂P�U�V */
		&KAT_NAME_168[0],			/* �^�f�[�^���̂P�U�W */
		&KAT_NAME_169[0],			/* �^�f�[�^���̂P�U�X */
		&KAT_NAME_170[0],			/* �^�f�[�^���̂P�V�O */
		&KAT_NAME_171[0],			/* �^�f�[�^���̂P�V�P */
		&KAT_NAME_172[0],			/* �^�f�[�^���̂P�V�Q */
		&KAT_NAME_173[0],			/* �^�f�[�^���̂P�V�R */
		&KAT_NAME_174[0],			/* �^�f�[�^���̂P�V�S */
		&KAT_NAME_175[0],			/* �^�f�[�^���̂P�V�T */
		&KAT_NAME_176[0],			/* �^�f�[�^���̂P�V�U */
		&KAT_NAME_177[0],			/* �^�f�[�^���̂P�V�V */
		&KAT_NAME_178[0],			/* �^�f�[�^���̂P�V�W */
		&KAT_NAME_179[0],			/* �^�f�[�^���̂P�V�X */
		&KAT_NAME_180[0],			/* �^�f�[�^���̂P�W�O */
		&KAT_NAME_181[0],			/* �^�f�[�^���̂P�W�P */
		&KAT_NAME_182[0],			/* �^�f�[�^���̂P�W�Q */
		&KAT_NAME_183[0],			/* �^�f�[�^���̂P�W�R */
		&KAT_NAME_184[0],			/* �^�f�[�^���̂P�W�S */
		&KAT_NAME_185[0],			/* �^�f�[�^���̂P�W�T */
		&KAT_NAME_186[0],			/* �^�f�[�^���̂P�W�U */
		&KAT_NAME_187[0],			/* �^�f�[�^���̂P�W�V */
		&KAT_NAME_188[0],			/* �^�f�[�^���̂P�W�W */
		&KAT_NAME_189[0],			/* �^�f�[�^���̂P�W�X */
		&KAT_NAME_190[0],			/* �^�f�[�^���̂P�X�O */
		&KAT_NAME_191[0],			/* �^�f�[�^���̂P�X�P */
		&KAT_NAME_192[0],			/* �^�f�[�^���̂P�X�Q */
		&KAT_NAME_193[0],			/* �^�f�[�^���̂P�X�R */
		&KAT_NAME_194[0],			/* �^�f�[�^���̂P�X�S */
		&KAT_NAME_195[0],			/* �^�f�[�^���̂P�X�T */
		&KAT_NAME_196[0],			/* �^�f�[�^���̂P�X�U */
		&KAT_NAME_197[0],			/* �^�f�[�^���̂P�X�V */
		&KAT_NAME_198[0],			/* �^�f�[�^���̂P�X�W */
		&KAT_NAME_199[0],			/* �^�f�[�^���̂P�X�X */
		&KAT_NAME_200[0],			/* �^�f�[�^���̂Q�O�O */
		&KAT_NAME_201[0],			/* �^�f�[�^���̂Q�O�P */
		&KAT_NAME_202[0],			/* �^�f�[�^���̂Q�O�Q */
		&KAT_NAME_203[0],			/* �^�f�[�^���̂Q�O�R */
		&KAT_NAME_204[0],			/* �^�f�[�^���̂Q�O�S */
		&KAT_NAME_205[0],			/* �^�f�[�^���̂Q�O�T */
		&KAT_NAME_206[0],			/* �^�f�[�^���̂Q�O�U */
		&KAT_NAME_207[0],			/* �^�f�[�^���̂Q�O�V */
		&KAT_NAME_208[0],			/* �^�f�[�^���̂Q�O�W */
		&KAT_NAME_209[0],			/* �^�f�[�^���̂Q�O�X */
		&KAT_NAME_210[0],			/* �^�f�[�^���̂Q�P�O */
		&KAT_NAME_211[0],			/* �^�f�[�^���̂Q�P�P */
		&KAT_NAME_212[0],			/* �^�f�[�^���̂Q�P�Q */
		&KAT_NAME_213[0],			/* �^�f�[�^���̂Q�P�R */
		&KAT_NAME_214[0],			/* �^�f�[�^���̂Q�P�S */
		&KAT_NAME_215[0],			/* �^�f�[�^���̂Q�P�T */
		&KAT_NAME_216[0],			/* �^�f�[�^���̂Q�P�U */
		&KAT_NAME_217[0],			/* �^�f�[�^���̂Q�P�V */
		&KAT_NAME_218[0],			/* �^�f�[�^���̂Q�P�W */
		&KAT_NAME_219[0],			/* �^�f�[�^���̂Q�P�X */
		&KAT_NAME_220[0]			/* �^�f�[�^���̂Q�Q�O */
	};

//�^�ް� �����̈�̱��ڽ�ð���
//const	UNs *	KAT_sv_memo_tbl[101] = {
//const	UNs *	KAT_sv_memo_tbl[201] = {		//V06n
const	UNs *	KAT_sv_memo_tbl[221] = {		//2014/04/16	SIT-4 MC
		&KAT_MEMO_01[0],			/* �_�~�[ */
		&KAT_MEMO_01[0],			/* �^�f�[�^�����P */
		&KAT_MEMO_02[0],			/* �^�f�[�^�����Q */
		&KAT_MEMO_03[0],			/* �^�f�[�^�����R */
		&KAT_MEMO_04[0],			/* �^�f�[�^�����S */
		&KAT_MEMO_05[0],			/* �^�f�[�^�����T */
		&KAT_MEMO_06[0],			/* �^�f�[�^�����U */
		&KAT_MEMO_07[0],			/* �^�f�[�^�����V */
		&KAT_MEMO_08[0],			/* �^�f�[�^�����W */
		&KAT_MEMO_09[0],			/* �^�f�[�^�����X */
		&KAT_MEMO_10[0],			/* �^�f�[�^�����P�O */
		&KAT_MEMO_11[0],			/* �^�f�[�^�����P�P */
		&KAT_MEMO_12[0],			/* �^�f�[�^�����P�Q */
		&KAT_MEMO_13[0],			/* �^�f�[�^�����P�R */
		&KAT_MEMO_14[0],			/* �^�f�[�^�����P�S */
		&KAT_MEMO_15[0],			/* �^�f�[�^�����P�T */
		&KAT_MEMO_16[0],			/* �^�f�[�^�����P�U */
		&KAT_MEMO_17[0],			/* �^�f�[�^�����P�V */
		&KAT_MEMO_18[0],			/* �^�f�[�^�����P�W */
		&KAT_MEMO_19[0],			/* �^�f�[�^�����P�X */
		&KAT_MEMO_20[0],			/* �^�f�[�^�����Q�O */
		&KAT_MEMO_21[0],			/* �^�f�[�^�����Q�P */
		&KAT_MEMO_22[0],			/* �^�f�[�^�����Q�Q */
		&KAT_MEMO_23[0],			/* �^�f�[�^�����Q�R */
		&KAT_MEMO_24[0],			/* �^�f�[�^�����Q�S */
		&KAT_MEMO_25[0],			/* �^�f�[�^�����Q�T */
		&KAT_MEMO_26[0],			/* �^�f�[�^�����Q�U */
		&KAT_MEMO_27[0],			/* �^�f�[�^�����Q�V */
		&KAT_MEMO_28[0],			/* �^�f�[�^�����Q�W */
		&KAT_MEMO_29[0],			/* �^�f�[�^�����Q�X */
		&KAT_MEMO_30[0],			/* �^�f�[�^�����R�O */
		&KAT_MEMO_31[0],			/* �^�f�[�^�����R�P */
		&KAT_MEMO_32[0],			/* �^�f�[�^�����R�Q */
		&KAT_MEMO_33[0],			/* �^�f�[�^�����R�R */
		&KAT_MEMO_34[0],			/* �^�f�[�^�����R�S */
		&KAT_MEMO_35[0],			/* �^�f�[�^�����R�T */
		&KAT_MEMO_36[0],			/* �^�f�[�^�����R�U */
		&KAT_MEMO_37[0],			/* �^�f�[�^�����R�V */
		&KAT_MEMO_38[0],			/* �^�f�[�^�����R�W */
		&KAT_MEMO_39[0],			/* �^�f�[�^�����R�X */
		&KAT_MEMO_40[0],			/* �^�f�[�^�����S�O */
		&KAT_MEMO_41[0],			/* �^�f�[�^�����S�P */
		&KAT_MEMO_42[0],			/* �^�f�[�^�����S�Q */
		&KAT_MEMO_43[0],			/* �^�f�[�^�����S�R */
		&KAT_MEMO_44[0],			/* �^�f�[�^�����S�S */
		&KAT_MEMO_45[0],			/* �^�f�[�^�����S�T */
		&KAT_MEMO_46[0],			/* �^�f�[�^�����S�U */
		&KAT_MEMO_47[0],			/* �^�f�[�^�����S�V */
		&KAT_MEMO_48[0],			/* �^�f�[�^�����S�W */
		&KAT_MEMO_49[0],			/* �^�f�[�^�����S�X */
		&KAT_MEMO_50[0],			/* �^�f�[�^�����T�O */
		&KAT_MEMO_51[0],			/* �^�f�[�^�����T�P */
		&KAT_MEMO_52[0],			/* �^�f�[�^�����T�Q */
		&KAT_MEMO_53[0],			/* �^�f�[�^�����T�R */
		&KAT_MEMO_54[0],			/* �^�f�[�^�����T�S */
		&KAT_MEMO_55[0],			/* �^�f�[�^�����T�T */
		&KAT_MEMO_56[0],			/* �^�f�[�^�����T�U */
		&KAT_MEMO_57[0],			/* �^�f�[�^�����T�V */
		&KAT_MEMO_58[0],			/* �^�f�[�^�����T�W */
		&KAT_MEMO_59[0],			/* �^�f�[�^�����T�X */
		&KAT_MEMO_60[0],			/* �^�f�[�^�����U�O */
		&KAT_MEMO_61[0],			/* �^�f�[�^�����U�P */
		&KAT_MEMO_62[0],			/* �^�f�[�^�����U�Q */
		&KAT_MEMO_63[0],			/* �^�f�[�^�����U�R */
		&KAT_MEMO_64[0],			/* �^�f�[�^�����U�S */
		&KAT_MEMO_65[0],			/* �^�f�[�^�����U�T */
		&KAT_MEMO_66[0],			/* �^�f�[�^�����U�U */
		&KAT_MEMO_67[0],			/* �^�f�[�^�����U�V */
		&KAT_MEMO_68[0],			/* �^�f�[�^�����U�W */
		&KAT_MEMO_69[0],			/* �^�f�[�^�����U�X */
		&KAT_MEMO_70[0],			/* �^�f�[�^�����V�O */
		&KAT_MEMO_71[0],			/* �^�f�[�^�����V�P */
		&KAT_MEMO_72[0],			/* �^�f�[�^�����V�Q */
		&KAT_MEMO_73[0],			/* �^�f�[�^�����V�R */
		&KAT_MEMO_74[0],			/* �^�f�[�^�����V�S */
		&KAT_MEMO_75[0],			/* �^�f�[�^�����V�T */
		&KAT_MEMO_76[0],			/* �^�f�[�^�����V�U */
		&KAT_MEMO_77[0],			/* �^�f�[�^�����V�V */
		&KAT_MEMO_78[0],			/* �^�f�[�^�����V�W */
		&KAT_MEMO_79[0],			/* �^�f�[�^�����V�X */
		&KAT_MEMO_80[0],			/* �^�f�[�^�����W�O */
		&KAT_MEMO_81[0],			/* �^�f�[�^�����W�P */
		&KAT_MEMO_82[0],			/* �^�f�[�^�����W�Q */
		&KAT_MEMO_83[0],			/* �^�f�[�^�����W�R */
		&KAT_MEMO_84[0],			/* �^�f�[�^�����W�S */
		&KAT_MEMO_85[0],			/* �^�f�[�^�����W�T */
		&KAT_MEMO_86[0],			/* �^�f�[�^�����W�U */
		&KAT_MEMO_87[0],			/* �^�f�[�^�����W�V */
		&KAT_MEMO_88[0],			/* �^�f�[�^�����W�W */
		&KAT_MEMO_89[0],			/* �^�f�[�^�����W�X */
		&KAT_MEMO_90[0],			/* �^�f�[�^�����X�O */
		&KAT_MEMO_91[0],			/* �^�f�[�^�����X�P */
		&KAT_MEMO_92[0],			/* �^�f�[�^�����X�Q */
		&KAT_MEMO_93[0],			/* �^�f�[�^�����X�R */
		&KAT_MEMO_94[0],			/* �^�f�[�^�����X�S */
		&KAT_MEMO_95[0],			/* �^�f�[�^�����X�T */
		&KAT_MEMO_96[0],			/* �^�f�[�^�����X�U */
		&KAT_MEMO_97[0],			/* �^�f�[�^�����X�V */
		&KAT_MEMO_98[0],			/* �^�f�[�^�����X�W */
		&KAT_MEMO_99[0],			/* �^�f�[�^�����X�X */
		&KAT_MEMO_100[0],			/* �^�f�[�^�����P�O�O */
		&KAT_MEMO_101[0],			/* �^�f�[�^�����P�O�P */
		&KAT_MEMO_102[0],			/* �^�f�[�^�����P�O�Q */
		&KAT_MEMO_103[0],			/* �^�f�[�^�����P�O�R */
		&KAT_MEMO_104[0],			/* �^�f�[�^�����P�O�S */
		&KAT_MEMO_105[0],			/* �^�f�[�^�����P�O�T */
		&KAT_MEMO_106[0],			/* �^�f�[�^�����P�O�U */
		&KAT_MEMO_107[0],			/* �^�f�[�^�����P�O�V */
		&KAT_MEMO_108[0],			/* �^�f�[�^�����P�O�W */
		&KAT_MEMO_109[0],			/* �^�f�[�^�����P�O�X */
		&KAT_MEMO_110[0],			/* �^�f�[�^�����P�P�O */
		&KAT_MEMO_111[0],			/* �^�f�[�^�����P�P�P */
		&KAT_MEMO_112[0],			/* �^�f�[�^�����P�P�Q */
		&KAT_MEMO_113[0],			/* �^�f�[�^�����P�P�R */
		&KAT_MEMO_114[0],			/* �^�f�[�^�����P�P�S */
		&KAT_MEMO_115[0],			/* �^�f�[�^�����P�P�T */
		&KAT_MEMO_116[0],			/* �^�f�[�^�����P�P�U */
		&KAT_MEMO_117[0],			/* �^�f�[�^�����P�P�V */
		&KAT_MEMO_118[0],			/* �^�f�[�^�����P�P�W */
		&KAT_MEMO_119[0],			/* �^�f�[�^�����P�P�X */
		&KAT_MEMO_120[0],			/* �^�f�[�^�����P�Q�O */
		&KAT_MEMO_121[0],			/* �^�f�[�^�����P�Q�P */
		&KAT_MEMO_122[0],			/* �^�f�[�^�����P�Q�Q */
		&KAT_MEMO_123[0],			/* �^�f�[�^�����P�Q�R */
		&KAT_MEMO_124[0],			/* �^�f�[�^�����P�Q�S */
		&KAT_MEMO_125[0],			/* �^�f�[�^�����P�Q�T */
		&KAT_MEMO_126[0],			/* �^�f�[�^�����P�Q�U */
		&KAT_MEMO_127[0],			/* �^�f�[�^�����P�Q�V */
		&KAT_MEMO_128[0],			/* �^�f�[�^�����P�Q�W */
		&KAT_MEMO_129[0],			/* �^�f�[�^�����P�Q�X */
		&KAT_MEMO_130[0],			/* �^�f�[�^�����P�R�O */
		&KAT_MEMO_131[0],			/* �^�f�[�^�����P�R�P */
		&KAT_MEMO_132[0],			/* �^�f�[�^�����P�R�Q */
		&KAT_MEMO_133[0],			/* �^�f�[�^�����P�R�R */
		&KAT_MEMO_134[0],			/* �^�f�[�^�����P�R�S */
		&KAT_MEMO_135[0],			/* �^�f�[�^�����P�R�T */
		&KAT_MEMO_136[0],			/* �^�f�[�^�����P�R�U */
		&KAT_MEMO_137[0],			/* �^�f�[�^�����P�R�V */
		&KAT_MEMO_138[0],			/* �^�f�[�^�����P�R�W */
		&KAT_MEMO_139[0],			/* �^�f�[�^�����P�R�X */
		&KAT_MEMO_140[0],			/* �^�f�[�^�����P�S�O */
		&KAT_MEMO_141[0],			/* �^�f�[�^�����P�S�P */
		&KAT_MEMO_142[0],			/* �^�f�[�^�����P�S�Q */
		&KAT_MEMO_143[0],			/* �^�f�[�^�����P�S�R */
		&KAT_MEMO_144[0],			/* �^�f�[�^�����P�S�S */
		&KAT_MEMO_145[0],			/* �^�f�[�^�����P�S�T */
		&KAT_MEMO_146[0],			/* �^�f�[�^�����P�S�U */
		&KAT_MEMO_147[0],			/* �^�f�[�^�����P�S�V */
		&KAT_MEMO_148[0],			/* �^�f�[�^�����P�S�W */
		&KAT_MEMO_149[0],			/* �^�f�[�^�����P�S�X */
		&KAT_MEMO_150[0],			/* �^�f�[�^�����P�T�O */
		&KAT_MEMO_151[0],			/* �^�f�[�^�����P�T�P */
		&KAT_MEMO_152[0],			/* �^�f�[�^�����P�T�Q */
		&KAT_MEMO_153[0],			/* �^�f�[�^�����P�T�R */
		&KAT_MEMO_154[0],			/* �^�f�[�^�����P�T�S */
		&KAT_MEMO_155[0],			/* �^�f�[�^�����P�T�T */
		&KAT_MEMO_156[0],			/* �^�f�[�^�����P�T�U */
		&KAT_MEMO_157[0],			/* �^�f�[�^�����P�T�V */
		&KAT_MEMO_158[0],			/* �^�f�[�^�����P�T�W */
		&KAT_MEMO_159[0],			/* �^�f�[�^�����P�T�X */
		&KAT_MEMO_160[0],			/* �^�f�[�^�����P�U�O */
		&KAT_MEMO_161[0],			/* �^�f�[�^�����P�U�P */
		&KAT_MEMO_162[0],			/* �^�f�[�^�����P�U�Q */
		&KAT_MEMO_163[0],			/* �^�f�[�^�����P�U�R */
		&KAT_MEMO_164[0],			/* �^�f�[�^�����P�U�S */
		&KAT_MEMO_165[0],			/* �^�f�[�^�����P�U�T */
		&KAT_MEMO_166[0],			/* �^�f�[�^�����P�U�U */
		&KAT_MEMO_167[0],			/* �^�f�[�^�����P�U�V */
		&KAT_MEMO_168[0],			/* �^�f�[�^�����P�U�W */
		&KAT_MEMO_169[0],			/* �^�f�[�^�����P�U�X */
		&KAT_MEMO_170[0],			/* �^�f�[�^�����P�V�O */
		&KAT_MEMO_171[0],			/* �^�f�[�^�����P�V�P */
		&KAT_MEMO_172[0],			/* �^�f�[�^�����P�V�Q */
		&KAT_MEMO_173[0],			/* �^�f�[�^�����P�V�R */
		&KAT_MEMO_174[0],			/* �^�f�[�^�����P�V�S */
		&KAT_MEMO_175[0],			/* �^�f�[�^�����P�V�T */
		&KAT_MEMO_176[0],			/* �^�f�[�^�����P�V�U */
		&KAT_MEMO_177[0],			/* �^�f�[�^�����P�V�V */
		&KAT_MEMO_178[0],			/* �^�f�[�^�����P�V�W */
		&KAT_MEMO_179[0],			/* �^�f�[�^�����P�V�X */
		&KAT_MEMO_180[0],			/* �^�f�[�^�����P�W�O */
		&KAT_MEMO_181[0],			/* �^�f�[�^�����P�W�P */
		&KAT_MEMO_182[0],			/* �^�f�[�^�����P�W�Q */
		&KAT_MEMO_183[0],			/* �^�f�[�^�����P�W�R */
		&KAT_MEMO_184[0],			/* �^�f�[�^�����P�W�S */
		&KAT_MEMO_185[0],			/* �^�f�[�^�����P�W�T */
		&KAT_MEMO_186[0],			/* �^�f�[�^�����P�W�U */
		&KAT_MEMO_187[0],			/* �^�f�[�^�����P�W�V */
		&KAT_MEMO_188[0],			/* �^�f�[�^�����P�W�W */
		&KAT_MEMO_189[0],			/* �^�f�[�^�����P�W�X */
		&KAT_MEMO_190[0],			/* �^�f�[�^�����P�X�O */
		&KAT_MEMO_191[0],			/* �^�f�[�^�����P�X�P */
		&KAT_MEMO_192[0],			/* �^�f�[�^�����P�X�Q */
		&KAT_MEMO_193[0],			/* �^�f�[�^�����P�X�R */
		&KAT_MEMO_194[0],			/* �^�f�[�^�����P�X�S */
		&KAT_MEMO_195[0],			/* �^�f�[�^�����P�X�T */
		&KAT_MEMO_196[0],			/* �^�f�[�^�����P�X�U */
		&KAT_MEMO_197[0],			/* �^�f�[�^�����P�X�V */
		&KAT_MEMO_198[0],			/* �^�f�[�^�����P�X�W */
		&KAT_MEMO_199[0],			/* �^�f�[�^�����P�X�X */
		&KAT_MEMO_200[0],			/* �^�f�[�^�����Q�O�O */
		&KAT_MEMO_201[0],			/* �^�f�[�^�����P�W�P */
		&KAT_MEMO_202[0],			/* �^�f�[�^�����P�W�Q */
		&KAT_MEMO_203[0],			/* �^�f�[�^�����P�W�R */
		&KAT_MEMO_204[0],			/* �^�f�[�^�����P�W�S */
		&KAT_MEMO_205[0],			/* �^�f�[�^�����P�W�T */
		&KAT_MEMO_206[0],			/* �^�f�[�^�����P�W�U */
		&KAT_MEMO_207[0],			/* �^�f�[�^�����P�W�V */
		&KAT_MEMO_208[0],			/* �^�f�[�^�����P�W�W */
		&KAT_MEMO_209[0],			/* �^�f�[�^�����P�W�X */
		&KAT_MEMO_210[0],			/* �^�f�[�^�����P�X�O */
		&KAT_MEMO_211[0],			/* �^�f�[�^�����P�X�P */
		&KAT_MEMO_212[0],			/* �^�f�[�^�����P�X�Q */
		&KAT_MEMO_213[0],			/* �^�f�[�^�����P�X�R */
		&KAT_MEMO_214[0],			/* �^�f�[�^�����P�X�S */
		&KAT_MEMO_215[0],			/* �^�f�[�^�����P�X�T */
		&KAT_MEMO_216[0],			/* �^�f�[�^�����P�X�U */
		&KAT_MEMO_217[0],			/* �^�f�[�^�����P�X�V */
		&KAT_MEMO_218[0],			/* �^�f�[�^�����P�X�W */
		&KAT_MEMO_219[0],			/* �^�f�[�^�����P�X�X */
		&KAT_MEMO_220[0]			/* �^�f�[�^�����Q�O�O */
	};


/*
********************************************************************************
*  Module Name:		DATA_svsw
*  Function Name:
*  Input	:		�ް�
*					�ޯ������
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
void	DATA_svsw(UNs data,UNs bit)
{
	if( 0 == (data & bit) ) {
		SV_CNT = 0;
		SW_CNT = 0;
		CSR_CNT = 0;
	}
}


/*
********************************************************************************
*  Module Name:		MIS_check
*  Function Name:	�~�X�t�B�[�h�L���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00:����
*					��00:����
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	MIS_check(void)
{

//	return(SEQ_018_SV & 0x0f00);		//н̨���1,2,6,8(1:�L)
//V05g	return(SEQ_018_SV & 0x0700);		//н̨���1,2,6(1:�L)
	return(SEQ_018_SV & 0x0F00);		//н̨���1,2,4,6(1:�L)

}


/*
********************************************************************************
*  Module Name:		ROT1_check
*  Function Name:	���[�^���J���P�`�W�L���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00:����
*					��00:����
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	ROT1_check(void)
{

	return(SEQ_018_SV & 0x5000);		//۰�ض�1�`4,5�`8(1:�L)

}


/*
********************************************************************************
*  Module Name:		ROT2_check
*  Function Name:	���[�^���J���X�`�P�U�L���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00:����
*					��00:����
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	ROT2_check(void)
{

	return(SEQ_019_SV & 0x0005);		//۰�ض�9�`12,13�`16(1:�L)

}

/*
********************************************************************************
*  Module Name:		ROT3_check
*  Function Name:	���[�^���J���P�V�`�Q�O�L���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00:����
*					��00:����
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	ROT3_check(void)
{

	return(SEQ_018_SV & BIT_6);			//۰�ض�17�`20(1:�L)

}


/*
********************************************************************************
*  Module Name:		EJE_check
*  Function Name:	�G�W�F�N�^�L���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00:����
*					��00:����
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	EJE_check(void)
{
	UNs		i;

	i = SEQ_017_SV & 0x2490;			//��ު��1,2,3,4(1:�L)
	i |= SEQ_018_SV & 0x0009;			//��ު��5,6(1:�L)

	return( i );
}


/*
********************************************************************************
*  Module Name:		DISP_cam_csr_name
*  Function Name:	�J���J�[�\�����̕\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	DISP_cam_csr_name(void)
{
	UNs	c_no, cnt, *g_p, xy_no;
	UNi	t_no;

	if(CSR_CNT1 == 0 ){
		return;
	}
	for( cnt=CSR_CNT1, t_no=0 ; cnt > 0 ; cnt--, t_no++ ) {

		c_no = CSR_buff[t_no].SW56_UP;							//SW56��i��׸�
		if( c_no >= 0x80 && c_no < 0xc5 ) {						//0x80 �� ��i��׸� �� 0xc5
			if( 0 == (CSR_buff[t_no].TOK_NO & BIT_0)) {			//����ԍ�(B0:���ٖ���)
				g_p = SW56_Cam_Name_Tbl[c_no - 0x80];
				if( (c_no >= 0xa0) && (c_no < 0xb5) &&			//���݂̖��̕\�������H  CSR_SW56_UP=0AAH
					 (c_no != 0xaa) && (MLD_100_GNO != 0) ) {	//�P�P�`�P�O�O�^�̖��́������\��

					if( c_no < 0xab ){							//�^�Ǘ��ԍ����P�O�{���Č^�Ǘ��ԍ����׍H����
						c_no -= 0xa0;							//���̕\��
						g_p = KAT_sv_name_tbl[c_no+(MLD_100_GNO*10)+1];
					}
					else{
						c_no -= 0xab;							//�����\��
						g_p = KAT_sv_memo_tbl[c_no+(MLD_100_GNO*10)+1];
					}
				}

				//���̃��t���b�V��
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				disp_moji_s(CSR_buff[t_no].XY_POS, g_p, &LCD_WORK1[0][0][0], 0x00);
#else
				disp_moji_s_color(
					CSR_buff[t_no].M_LEN,					/* ��׸��			*/
					CSR_buff[t_no].X_POS,					/* ���o��X�ʒu		*/
					CSR_buff[t_no].Y_POS,					/* ���o��Y�ʒu		*/
					CSR_buff[t_no].C_COL,					/* �����F			*/
					CSR_buff[t_no].B_COL1,					/* �w�i�F			*/
					CSR_buff[t_no].SIZE,					/* ��������			*/
					g_p,									/* �����i�[���ڽ	*/
					LCD_VBASE								/* �\�����			*/
					);
				disp_moji_s_rif(
					CSR_buff[t_no].M_LEN,					/* ��׸��			*/
					CSR_buff[t_no].X_POS,					/* ���o��X�ʒu		*/
					CSR_buff[t_no].Y_POS,					/* ���o��Y�ʒu		*/
					CSR_buff[t_no].SIZE					/* ��������			*/
					);
#endif
			}
		}
	}
	
//V06p
	if ( (CSR_buff[0].SW56_UP == 0x88) && (SEQ_019_SV & BIT_0) && (SEQ_PAR_113 & BIT_14) ) {	//۰�ض�9-12�L���^۰�ض�9�������Ռ�
		g_p = &PV_CAMSWD_C1[0];							//�����Ռ��Ƃ���B
		disp_moji_s_color(
			CSR_buff[0].M_LEN,					/* ��׸��			*/
			CSR_buff[0].X_POS,					/* ���o��X�ʒu		*/
			CSR_buff[0].Y_POS,					/* ���o��Y�ʒu		*/
			CSR_buff[0].C_COL,					/* �����F			*/
			CSR_buff[0].B_COL1,					/* �w�i�F			*/
			CSR_buff[0].SIZE,					/* ��������			*/
			g_p,									/* �����i�[���ڽ	*/
			LCD_VBASE								/* �\�����			*/
			);
		disp_moji_s_rif(
			CSR_buff[0].M_LEN,					/* ��׸��			*/
			CSR_buff[0].X_POS,					/* ���o��X�ʒu		*/
			CSR_buff[0].Y_POS,					/* ���o��Y�ʒu		*/
			CSR_buff[0].SIZE					/* ��������			*/
			);
	}

}


#if (mot100_test == 1)
/*
********************************************************************************
*  Module Name:		DISP_step_csr_name
*  Function Name:	���[�V�����s��No.�J�[�\���\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shima		ON:2015-08-24
********************************************************************************
*/
void	DISP_step_csr_name(void)
{
	UNs		c_no, cnt, *g_p, xy_no;
	UNs		c_wk[16], w_bf;
	UNi		i, j, k, t_no;
	UNb		wk[16];
	UNl		bcd_d;
	UNs		dan, d_no, end_page;

	if ( (GAMEN_NO != 3) && (GAMEN_NO != 28) ) {
		return;
	}

	if(CSR_CNT1 == 0 ){
		return;
	}

	memset(&wk[0], E_AS_SP, 16);					//�̈� ��߰� �ر

	dan = 5;
	end_page = (SV_DANSUU_SRV - 1) / 5;
	if (SV_MOT_PAGE >= end_page) {
		dan = SV_DANSUU_SRV % 5;			//�\���i��
		if (dan==0) {
			dan = 5;
		}
	}
	d_no = 97;

	for (; dan>0; dan--, d_no++) {
		for( cnt=CSR_CNT1, t_no=0 ; cnt > 0 ; cnt--, t_no++ ) {
			if (CSR_buff[t_no].DATA_NO == d_no) {
				bcd_d = SV0_DISP_STEP_NO[d_no-97];
				bcd_d = HEX_BCD4(bcd_d);					//HEX �� BCD �ϊ�
				BCD_ASCII(bcd_d, &wk[0]);					//BCD��ASCII �ϊ�

				i = CSR_buff[t_no].XY_POS >> 10;			//BYTE -> WORD �ɕϊ�
				for( j=0 ; i > 0 ; i--, j++ ){
					w_bf = wk[i-1];
					w_bf <<= 8;
					if(i <= 1){
						w_bf |= (UNb)E_AS_SP;				//�X�y�[�X�mASCII���ށn
					}
					else{
						i--;
						w_bf |= wk[i-1];
					}
					c_wk[j] = w_bf;
				}

				//���̃��t���b�V��
				disp_moji_s_color(
					2,										/* ��׸��			CSR_buff[t_no].M_LEN */
					CSR_buff[t_no].X_POS,					/* ���o��X�ʒu		*/
					CSR_buff[t_no].Y_POS,					/* ���o��Y�ʒu		*/
					CSR_buff[t_no].C_COL,					/* �����F			*/
					CSR_buff[t_no].B_COL1,					/* �w�i�F			*/
					CSR_buff[t_no].SIZE,					/* ��������			*/
					&c_wk[0],								/* �����i�[���ڽ	*/
					LCD_VBASE								/* �\�����			*/
					);
//				disp_moji_s_rif(
//					CSR_buff[t_no].M_LEN,					/* ��׸��			*/
//					CSR_buff[t_no].X_POS,					/* ���o��X�ʒu		*/
//					CSR_buff[t_no].Y_POS,					/* ���o��Y�ʒu		*/
//					CSR_buff[t_no].SIZE					/* ��������			*/
//					);
				break;
			}
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		CAM_next_cls
*  Function Name:	�ݒ�l�̎��̃L�����N�^���X�y�[�X����
*  Input	:		���ð��ق̔ԍ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	CAM_next_cls(UNs t_no)
{
	UNs		xy_no, xy_no2;

	xy_no2 = xy_no = SV_buff[t_no].XY_POS;
	xy_no &= 0x03ff;									//����׸��ʒu�̎Z�o
	xy_no2 >>= 6;
	xy_no2 &= 0x03f0;
	xy_no += xy_no2;
	xy_no &= 0x03ff;
	xy_no |= 0x0400;									//���ْ� 1��ݒ�
	disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�

}


/*
********************************************************************************
*  Module Name:		LENG_svpv
*  Function Name:	�����_�̕ύX(�ݒ�l&�����l)
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					���ð��ق̏����_�ʒu
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	LENG_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].TEN_POS = ten_pos;				//�����_�̈ʒu �ύX
		}
	}

															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			PV_buff[t_no].TEN_POS = ten_pos;				//�����_�̈ʒu �ύX
		}
	}
}


/*
********************************************************************************
*  Module Name:		kag_to_kaj_sub_chg
*  Function Name:	�����ʒu���ڕW�׏d ���ٰ��No.�؊�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-07-05		V01k
********************************************************************************
*/
void	kag_to_kaj_sub_chg(void)
{
	UNs		cnt, t_no;
	UNs		xy_no, *g_p;
	UNl		adr;

//V01m	if (SEQ_024_SV & BIT_4)								//�׏d�␳����H
	if (SEQ_050_SV & BIT_9)								//�׏d�␳����H
	{
		/*�u�����v���u�׏d�v*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		xy_no = 3;							// 3�s��
		xy_no |= /*32 V01k*/23<<4;			// 32���� -> 23����
		xy_no |= /*4 V01k*/6<<10;			// 4���� -> 6����
		g_p = mess_adr_shr(7);				//���b�Z�[�W��ʃL�����N�^�A�h���X����
		g_p += 66*5;						//��׸�No.10�{
		disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
#else
		for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
			if(CSR_buff[t_no].DATA_NO == 117)				//��ٰ�ߔԍ� ���
			{
				CSR_buff[t_no].CARA_NO = 510;
			}
		}
#endif
		for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
			if(SV_buff[t_no].GRP_NO == 117)				//��ٰ�ߔԍ� ���
			{
				SV_buff[t_no].DATA_ADR = &SV_KAJYUU_OBJP;	//�i�[����ڽ�ύX	V01m(INS)
				SV_buff[t_no].TOK_FLG = 0;					//�����׸ނ̕ύX
				SV_buff[t_no].BYTE_NO = 2;					//�޲Ē��̕ύX
			}
		}
		for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		// V01m(INS)
			if(SV_buff[t_no].GRP_NO == 118)				//��ٰ�ߔԍ� ���
			{
				SV_buff[t_no].DATA_ADR = &SV_KAJYUU_PRS;	//�i�[����ڽ�ύX
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_cls
*  Function Name:	���ُ��ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	CSR_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SV_cls
*  Function Name:	�ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	SV_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		PV_cls
*  Function Name:	�����l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	PV_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				PV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_cls
*  Function Name:	SW�ް����ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	SW_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//SW�ް����e�[�u��
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				SW_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_cls_disp
*  Function Name:	SW�ް����ð��ق̔�\��/�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2014/03/17
********************************************************************************
*/
void	SW_cls_disp(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				SW_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
			}
			else {
				SW_buff[t_no].SUB_NO &= ~BIT_15;			//�\���̐ݒ�
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EJE_grp
*  Function Name:	��ު���p�ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�(�J�n)
*					���ð��ق̸�ٰ�ߔԍ�(�I��)
*					��ު����� ��r�ޯ�
*					��ު�� ��r�ް�
*					��ު�� ��r�ޯ�
*					��ު���i�p�̸�ٰ�ߔԍ�
*					��ު���i�p ��r�ް�
*					��ު���i�p ��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	EJE_grp(UNs grp_sno, UNs grp_eno, UNs ejet_bit,
				 UNs eje_data, UNs eje_bit, UNs ejek_grp, UNs ejek_data, UNs ejek_bit, UNs eje_csr)
{
	UNs	cnt, t_no, t_no2, t_no3, t_no4;

	CSR_CLS_FLG = 0;
													//�ݒ�l���e�[�u��
	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//��ު��J�n ���(�ё�)
		if(SV_buff[t_no].GRP_NO == grp_sno) {		//��ٰ�ߔԍ� ���
			goto EJ1;
		}
	}
	goto EJ11;

EJ1:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//��ު��J�n ���(�ё�)
		if(SV_buff[t_no2].GRP_NO == grp_sno) {		//��ٰ�ߔԍ� ���
			goto EJ2;
		}
	}
	goto EJ11;

EJ2:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//��ު��J�n ���(��ϰ��)
		if(SV_buff[t_no3].GRP_NO == grp_sno) {		//��ٰ�ߔԍ� ���
			goto EJ3;
		}
	}
	goto EJ11;

EJ3:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//��ު��J�n ���(��ϰ��)
		if(SV_buff[t_no4].GRP_NO == grp_sno) {		//��ٰ�ߔԍ� ���
			goto EJ4;
		}
	}
	goto EJ11;

EJ4:
	if( eje_data & eje_bit ){						//�d�l�����H
		if(SEQ_034_SV & ejet_bit){					//��ϑI������H
			SV_buff[t_no].SUB_NO |= BIT_15;			//��\���̐ݒ�
			SV_buff[t_no2].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no3].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
			SV_buff[t_no4].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		}
		else{										//�Ȃ�
			SV_buff[t_no4].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no3].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no2].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
			SV_buff[t_no].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		}
	}
	else{											//����
		SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
		SV_buff[t_no2].SUB_NO |= BIT_15;			//��\���̐ݒ�
		SV_buff[t_no3].SUB_NO |= BIT_15;			//��\���̐ݒ�
		SV_buff[t_no4].SUB_NO |= BIT_15;			//��\���̐ݒ�
		CSR_CLS_FLG = 0xff;
	}


	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//��ު��I�� ���(�ё�)
		if(SV_buff[t_no].GRP_NO == grp_eno) {		//��ٰ�ߔԍ� ���
			goto EJ6;
		}
	}
	goto EJ11;

EJ6:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//��ު��I�� ���(�ё�)
		if(SV_buff[t_no2].GRP_NO == grp_eno) {		//��ٰ�ߔԍ� ���
			goto EJ7;
		}
	}
	goto EJ11;

EJ7:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//��ު��I�� ���(��ϰ��)
		if(SV_buff[t_no3].GRP_NO == grp_eno) {		//��ٰ�ߔԍ� ���
			goto EJ8;
		}
	}
	goto EJ11;

EJ8:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//��ު��I�� ���(��ϰ��)
		if(SV_buff[t_no4].GRP_NO == grp_eno) {		//��ٰ�ߔԍ� ���
			goto EJ9;
		}
	}
	goto EJ11;

EJ9:
	if( eje_data & eje_bit ){						//�d�l�����H
		if(SEQ_034_SV & ejet_bit){					//��ϑI������H
			SV_buff[t_no].SUB_NO |= BIT_15;			//��\���̐ݒ�
			SV_buff[t_no2].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no3].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
			SV_buff[t_no4].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		}
		else{										//�Ȃ�
			SV_buff[t_no4].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no3].SUB_NO |= BIT_15;		//��\���̐ݒ�
			SV_buff[t_no2].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
			SV_buff[t_no].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		}
	}
	else{											//����
		SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
		SV_buff[t_no2].SUB_NO |= BIT_15;			//��\���̐ݒ�
		SV_buff[t_no3].SUB_NO |= BIT_15;			//��\���̐ݒ�
		SV_buff[t_no4].SUB_NO |= BIT_15;			//��\���̐ݒ�
		CSR_CLS_FLG = 0xff;
	}

EJ11:
	t_no = 0;										//�_�~�[

/* �i�p�f�[�^�L���Ǘ� */
//	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//��ު���i�p ���
//		if(SV_buff[t_no].GRP_NO == ejek_grp) {				//��ٰ�ߔԍ� ���
//			if(00 == (eje_data & eje_bit) ||				//�d�l�����H
//				00 == (ejek_data & ejek_bit)) {
//
//				SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
//				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(eje_csr);
//			}
//		}
//	}

}


/*
********************************************************************************
*  Module Name:		EJE_csr
*  Function Name:	��ު���p���ُ��ð��ق̐ݒ�l����������
*  Input	:		���ð��ق�SW56��i��׸�
*					��ު�� ��r�ް�
*					��ު�� ��r�ޯ�
*					��ު���i�p ��r�ް�
*					��ު���i�p ��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	EJE_csr(UNs sw56_up, UNs eje_data, UNs eje_bit, UNs ejek_data, UNs ejek_bit, UNs eje_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//��ު�� ���
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56��i��׸�
//			if(00 == (ejek_data & ejek_bit)) {				//�i�p�����݂��Ȃ��Ƃ��͔�\��
//				CSR_buff[t_no].SV_MAX = 2;					//�ݒ�lð��ٌ�
//			}
			if(00 == (eje_data & eje_bit)){					//�d�l�����H
				CSR_buff[t_no].SV_MAX = 0;					//�ݒ�lð��ٌ�
				CSR_buff[t_no].SW_MAX = 0;					//SWð��ٌ�
				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(eje_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EJE_sw
*  Function Name:	��ު���pSW�ް����ð��ق̏�������
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	EJE_sw(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				SW_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				SW_buff[t_no].TOK_FLG &= ~BIT_0;			//ON���]�\���̸ر
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_grp
*  Function Name:	۰�ضїp�ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�(�J�n)
*					���ð��ق̸�ٰ�ߔԍ�(�I��)
*					��ު����� ��r�ޯ�
*					��ު�� ��r�ް�
*					��ު�� ��r�ޯ�
*					��ު���i�p�̸�ٰ�ߔԍ�
*					��ު���i�p ��r�ް�
*					��ު���i�p ��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2016/11/15
********************************************************************************
*/
void	ROT_cam_tim(UNs grp_no, UNs rct_bit)
{
	UNs	cnt, t_no, t_no2, t_no3, t_no4, t_no5, t_no6, t_no7, t_no8;

	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//۰�ضъJ�n ���(�ё�)
		if(SV_buff[t_no].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC1;
		}
	}
	goto RC11;

RC1:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//۰�ضъJ�n ���(�ё�)
		if(SV_buff[t_no2].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC2;
		}
	}
	goto RC11;

RC2:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//۰�ضъJ�n ���(�ё�)
		if(SV_buff[t_no3].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC3;
		}
	}
	goto RC11;

RC3:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//۰�ضъJ�n ���(�ё�)
		if(SV_buff[t_no4].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC4;
		}
	}
	goto RC11;

RC4:
	t_no5 = t_no4;
	for( t_no5++ ; cnt > 0 ; cnt--, t_no5++){		//۰�ضъJ�n ���(��ϰ��)
		if(SV_buff[t_no5].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC5;
		}
	}
	goto RC11;

RC5:
	t_no6 = t_no5;
	for( t_no6++ ; cnt > 0 ; cnt--, t_no6++){		//۰�ضъJ�n ���(��ϰ��)
		if(SV_buff[t_no6].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC6;
		}
	}
	goto RC11;

RC6:
	t_no7 = t_no6;
	for( t_no7++ ; cnt > 0 ; cnt--, t_no7++){		//۰�ضъJ�n ���(��ϰ��)
		if(SV_buff[t_no7].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC7;
		}
	}
	goto RC11;

RC7:
	t_no8 = t_no7;
	for( t_no8++ ; cnt > 0 ; cnt--, t_no8++){		//۰�ضъJ�n ���(��ϰ��)
		if(SV_buff[t_no8].GRP_NO == grp_no) {		//��ٰ�ߔԍ� ���
			goto RC8;
		}
	}
	goto RC11;

RC8:
	if(SEQ_039_SV & rct_bit){					//��ϑI������H
		SV_buff[t_no].SUB_NO |= BIT_15;			//��\���̐ݒ�
		SV_buff[t_no2].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no3].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no4].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no5].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no6].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no7].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no8].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
	}
	else{										//�Ȃ�
		SV_buff[t_no].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no2].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no3].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no4].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
		SV_buff[t_no5].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no6].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no7].SUB_NO |= BIT_15;		//��\���̐ݒ�
		SV_buff[t_no8].SUB_NO |= BIT_15;		//��\���̐ݒ�
	}

RC11:
	t_no = 0;										//�_�~�[

}


/*
********************************************************************************
*  Module Name:		ROT_cam_sv
*  Function Name:	۰�ضїp�ݒ�l���ð��ق̏�������
*  Input	:		���ð��ق̶��ٔF���ԍ�
*					۰�ضёI����ʔ�r�ޯ�
*					۰�ضёI����ʔ�r�ް�
*					۰�ض� ��r�ް�
*					۰�ض� ��r�ޯ�
*					���ð��ق̸�ٰ�ߔԍ�
*					۰�ضѐi�p ��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_sv(UNs csr_no, UNs rot_bit, UNs rot_data,
				 UNs seq_data, UNs seq_bit, UNs grp_no, UNs rotk_bit, UNs rot_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//���ٔF���ԍ� ���
			if(00 == (rot_data & rot_bit) ||				//۰�ضёI�����
				00 == (seq_data & seq_bit) ){				//۰�ضїL��
				SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
//				CAM_next_cls(t_no);							//�ݒ�l�̎��̃L�����N�^���X�y�[�X����
				CSR_CLS_FLG = 0xff;
			}
		}
	}

/* �i�p�������̏��� */										//2014/09/01
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & rotk_bit)) {				//۰�ضїL��
				SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(rot_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_sw
*  Function Name:	۰�ضїpSW�ް����ð��ق̏�������
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					۰�ضёI����ʔ�r�ޯ�
*					۰�ضёI����ʔ�r�ް�
*					۰�ض� ��r�ް�
*					۰�ض� ��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_sw(UNs grp_no, UNs rot_bit, UNs rot_data, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (rot_data & rot_bit) ||				//۰�ضёI�����
				00 == (seq_data & seq_bit) ){				//۰�ضїL��
				SW_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				SW_buff[t_no].TOK_FLG &= ~BIT_0;			//ON���]�\���̸ر
			}
//2014/09/08			break;
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_csr
*  Function Name:	۰�ضїp���ُ��ð��ق̏�������
*  Input	:		���ð��ق�SW56��i��׸�
*					۰�ضёI����ʔ�r�ޯ�
*					۰�ضёI����ʔ�r�ް�
*					۰�ض� ��r�ް�
*					۰�ض� ��r�ޯ�
*					۰�ضѐi�p ��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_csr(UNs sw56_up, UNs rot_bit, UNs rot_data,
				 UNs seq_data, UNs seq_bit, UNs rotk_bit, UNs rot_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//۰�ض� ���
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56��i��׸�
			if(00 == (rot_data & rot_bit)) {				//�d�l�����H
				CSR_buff[t_no].SV_MAX = 0;					//�ݒ�lð��ٌ�
				CSR_buff[t_no].SW_MAX = 0;					//SWð��ٌ�
			}
			break;
		}
	}
//	if(00 == (seq_data & rotk_bit)) {						//�i�p�����݂��Ȃ��Ƃ�
//		CSR_buff[t_no].SV_MAX = 2;							//�ݒ�lð��ٌ�
//	}

	if(00 == (seq_data & seq_bit)) {						//�d�l����
		CSR_buff[t_no].SV_MAX = 0;							//�ݒ�lð��ٌ�
		CSR_buff[t_no].SW_MAX = 0;							//SWð��ٌ�
		CSR_buff[t_no].TOK_NO |= BIT_0;						//��\���̐ݒ�
		CSR_CLS_FLG = 0xff;
		CSR_disp_cls(rot_csr);
	}
}


/*
********************************************************************************
*  Module Name:		MIS_sv
*  Function Name:	н̨��ޗp�ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	MIS_sv(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H

				SV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
//				CAM_next_cls(t_no);							//�ݒ�l�̎��̃L�����N�^���X�y�[�X����
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MIS_csr
*  Function Name:	н̨��ޗp���ُ��ð��ق̏�������
*  Input	:		���ð��ق�SW56��i��׸�
*					��r�ް�
*					��r�ޯ�
*					���ُ����ʒu���
*					���ُ����ʒu���2
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	MIS_csr(UNs sw56_up, UNs seq_data, UNs seq_bit, UNs mis_csr, UNs mis_csr2)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//۰�ض� ���
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56��i��׸�

			if(00 == (seq_data & seq_bit)) {				//�d�l����
				CSR_buff[t_no].SV_MAX = 0;					//�ݒ�lð��ٌ�
				CSR_buff[t_no].SW_MAX = 0;					//SWð��ٌ�
				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�

				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(mis_csr);
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(mis_csr2);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ATU_svpv
*  Function Name:	�ݒ�l���ð��ق̕ύX
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					���ð��ق̏����_�ʒu
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	ATU_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no, xy_no;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].TEN_POS = ten_pos;				//�����_�̈ʒu �ύX

			if(ten_pos == 00){
				xy_no = SV_buff[t_no].XY_POS;				//�ݒ�l�\����X,Y��
				xy_no &= 0x03ff;							//�J�[�\�����ύX
				xy_no |= 0x0c00;							//���p�R��
				xy_no += 0x0010;							//�\���ʒu
				SV_buff[t_no].XY_POS = xy_no;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		KAJ_svpv
*  Function Name:	�����_�̕ύX(�ݒ�l&�����l)
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					���ð��ق̏����_�ʒu
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shima		ON:2010-08-12		V05r
********************************************************************************
*/
void	KAJ_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].TEN_POS = ten_pos;				//�����_�̈ʒu �ύX
		}
	}
	
															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			PV_buff[t_no].TEN_POS = ten_pos;				//�����_�̈ʒu �ύX
		}
	}
}


/*
********************************************************************************
*  Module Name:		DANsel_csr
*  Function Name:	н̨��ޗp���ُ��ð��ق̏�������
*  Input	:		���ð��ق�SW56��i��׸�
*					��r�ް�
*					��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	DANsel_csr(UNs grp_no, UNs seq_data, UNs seq_bit, UNs dan_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {	//۰�ض� ���
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)) {				//�d�l�����H
				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(dan_csr);
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_sel
*  Function Name:	�i���p�@�e�I���̏�������
*  Input	:		���ݽ �ް�����ڽ
*					��r�ް�
*					��r�ޯ�
*					�׸�:0=b0�`b7 / 1=b8�`b15
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-06
********************************************************************************
*/
void	DAN_sel(UNs *seq_no, UNs seq_data, UNs seq_bit, UNs flag)
{
	UNs		data;

	data = *seq_no;

	if(flag == 00){							//b0�`b7
		if(seq_data & seq_bit){
			data &= 0x001c;
			if( data != BIT_2 &&
				data != BIT_3 &&
				data != BIT_4 ) {

				*seq_no &= 0xff00;
				*seq_no |= BIT_2;
				ONOFF_FLG = 0xff;
			}
		}
		else if(data & 0x001c){
			*seq_no &= 0xff00;
			ONOFF_FLG = 0xff;
		}
	}
	else{									//b8�`b15
		if(seq_data & seq_bit){
			data &= 0x1c00;
			if( data != BIT_10 &&
				data != BIT_11 &&
				data != BIT_12 ) {

				*seq_no &= 0x00ff;
				*seq_no |= BIT_10;
				ONOFF_FLG = 0xff;
			}
		}
		else if(data & 0x1c00){
			*seq_no &= 0x00ff;
			ONOFF_FLG = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_csr_set(��:CSR_G07_SET)
*  Function Name:	�i���ʁ@�\���������J�E���^
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_set(void)
{
	UNs		cnt;

	CSR_G07_NO1 = 0;					//�J�[�\���擪�ʒu
	CSR_G07_NO2 = 0;					//�J�[�\���ŏI�ʒu
	DAN_CLS_CNT = 0;					//�\���������J�E���^

	cnt = 1;

	if (GAMEN_NO == 8)				//V01r
	{
		if(SEQ_020_SV & BIT_14){			//���^��������
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

	cnt ++;
	}

	if(SEQ_020_SV & (BIT_6 | BIT_4)){	//�X���C�h����
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_4){				//��^�N�����p
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_6){				//���^�N�����p
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_8){				//�_�C���t�^
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	if (GAMEN_NO == 8)				//V01r
	{
		cnt ++;
		if(SEQ_019_SV & BIT_10){			//�_�C�N�b�V����	V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_1){				//�h���		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_15){			//�l�a			V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_11){			//�o�����T		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_019_SV & (BIT_12 | BIT_13 | BIT_15)){	//�޲����ݒ���		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}
	}

//V06p
	DAN_CLS_CNT ++;
	cnt ++;
	CSR_G07_NO2 = cnt;			//�i�摬�x

}


/*
********************************************************************************
*  Module Name:		KAT_cls
*  Function Name:	�^�ް��̎����l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	KAT_cls(UNs grp_no, UNs seq_data, UNs seq_bit, UNs kat_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				PV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(kat_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MEMO_cls
*  Function Name:	�����̎����l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*					��r�ް�
*					��r�ޯ�
*					���ُ����ʒu���
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	MEMO_cls(UNs grp_no, UNs seq_data, UNs seq_bit, UNs memo_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(00 == (seq_data & seq_bit)){					//�d�l�����H
				PV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(memo_csr);
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		PVdata_non_sub
*  Function Name:	�����l���ð��ق̔�\�� �ݒ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-16
********************************************************************************
*/
void	PVdata_non_sub(void)
{
	UNs	i, j, k;

	PVDATA_NON = 0;

	for( i=0,j=0, k=PV_CNT ; k > 0 ; i++,k-- ) {
		if( PV_buff[i].SUB_NO & BIT_15 ) {				//�����l�f�[�^���g�p�H
			j ++;
		}
		else if( PV_buff[i].TOK_FLG & BIT_6 ) {			//�P�ʁ��^�f�[�^�H
			j ++;
		}
	}
	if( j >= PV_CNT ) {
		PVDATA_NON = 0xff;
	}
}


/*
********************************************************************************
*  Module Name:		SCAN_kat_cls
*  Function Name:
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-16
********************************************************************************
*/
void	SCAN_kat_cls(void)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == 56 &&					//�^�ް��H
			00 == (SEQ_PAR_107 & BIT_0)){					//�d�l�����H
			PV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
			CSR_CLS_FLG = 0xff;
			CSR_disp_cls(81);
			goto KAT_CLS_130;
		}
	}
	goto KAT_CLS_200;

KAT_CLS_130:
	for(t_no++ ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == 56 &&					//�^�ް��H
			00 == (SEQ_PAR_107 & BIT_0)){					//�d�l�����H
			PV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
			CSR_CLS_FLG = 0xff;
			CSR_disp_cls(61);
			break;
		}
	}

KAT_CLS_200:
	CSR_CLS_FLG = 0;
//	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
//		if(PV_buff[t_no].GRP_NO == 57){						//������ѕ\���H
//			if(SEQ_020_SV & BIT_3){							//������ѕ\���H
//				t_no++;
//				PV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
//				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(61);
//			}
//			else{
//				PV_buff[t_no].SUB_NO |= BIT_15;				//��\���̐ݒ�
//				CSR_CLS_FLG = 0xff;
//			}
//			break;
//		}
//	}

}


/*
********************************************************************************
*  Module Name:		ADC_NEXT_cls
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2016/04/22
********************************************************************************
*/
void	ADC_NEXT_cls(void)
{
	if(WINDOW_NO == 12)
	{
		if(SEQ_047_SV & BIT_7)
		{
			CSR_CNT = 0;					/* ���o���I�΂�ăX�e�b�v���j�^��ʂ�\������ꍇ�̓J�[�\����\�����Ȃ� */
			CSR_MOVE_OK_FLG = 0xff;			/* �J�[�\���ړ��m�f */
			SV_buff[0].SUB_NO |= BIT_15;	/* ���^�ԍ����� */
			PV_buff[0].SUB_NO |= BIT_15;	/* ���^�ԍ����� */

			CSR_CLS_FLG = 0xff;
//V00iM			CSR_disp_cls(129);
			disp_moji_s_paint(			/* �E�u�ݒ�l�v��������	*/
				40,						/* ��׸��(���p��)	*/
				0,						/* ���o��X�ʒu		*/
				192,					/* ���o��Y�ʒu		*/
				GAMENn_HEAD.scr_col,	/* �h��ׂ��F		*/
				0x0202,					/* ��������			*/
				LCD_VBASE				/* �\�����			*/
				);
			CSR_buff[0].TOK_NO |= BIT_0;			// V00iM
		}
	}
	else
	{
		if(SEQ_047_SV & BIT_7)
		{
			CSR_CNT = 0;					/* ���o���I�΂�ăX�e�b�v���j�^��ʂ�\������ꍇ�̓J�[�\����\�����Ȃ� */
			CSR_MOVE_OK_FLG = 0xff;			/* �J�[�\���ړ��m�f */
			PV_buff[0].SUB_NO |= BIT_15;	/* ���^�ԍ����� */
			PV_buff[1].SUB_NO |= BIT_15;	/* ���^�ԍ����� */

			CSR_CLS_FLG = 0xff;
//V00iM			CSR_disp_cls(129);
			disp_moji_s_paint(			/* �E�u�ݒ�l�v��������	*/
				40,						/* ��׸��(���p��)	*/
				0,						/* ���o��X�ʒu		*/
				192,					/* ���o��Y�ʒu		*/
				GAMENn_HEAD.scr_col,	/* �h��ׂ��F		*/
				0x0202,					/* ��������			*/
				LCD_VBASE				/* �\�����			*/
				);
		}
	}
}


/*
********************************************************************************
*  Module Name:		NAME_cls_sub
*  Function Name:	��ꌾ��@���ł̔�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-16
********************************************************************************
*/
void	NAME_cls_sub(void)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){

		if(CSR_buff[t_no].DATA_NO == 74) {					//���̑�񍑂ō폜�H
			if(SV_GENGO_KAT == 1 ||							//��ꌾ��J�^�J�i�s�v(1:���ŕs�v)
				language_chg != 00) {						//���{��H

				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS_swcara
*  Function Name:	н̨���SW�\����א؊����̔�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-16
********************************************************************************
*/
void	MISS_swcara(void)
{
	UNs	s_bit;
	UNi	cnt, t_no;
															//���ُ��e�[�u��
	s_bit = SYS_MISSEL_SV;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].SW6_DN == 58 ||					//SW6���i��׸�(�\���p��׸��ԍ� ���)
			CSR_buff[t_no].SW6_DN == 59){					//SW6���i��׸�(�\���p��׸��ԍ� ���)
			if( s_bit & BIT_0 ){
				CSR_buff[t_no].SW6_DN = 59;					//�\���p��׸��ԍ� �ύX(�ځ^�r)
			}
			s_bit >>= 1;
		}
	}

															//SW�ް����e�[�u��
	s_bit = SYS_MISSEL_SV;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CARA_NO == 22 ||					//�\���p��׸��ԍ� ���
			SW_buff[t_no].CARA_NO == 23) {					//�\���p��׸��ԍ� ���
			if( s_bit & BIT_0 ){
				SW_buff[t_no].CARA_NO = 23;					//�\���p��׸��ԍ� �ύX
			}
			s_bit >>= 1;
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS56_swcara
*  Function Name:	н̨���SW�\����א؊����̔�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2005-04-28	V01r
********************************************************************************
*/
void	MISS56_swcara(void)
{
	UNs	s_bit;
	UNi	cnt, t_no;
															//���ُ��e�[�u��
	s_bit = SYS_MISSEL_SV;
	s_bit >>= 4;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].SW6_DN == 58 ||					//SW6���i��׸�(�\���p��׸��ԍ� ���)
			CSR_buff[t_no].SW6_DN == 59){					//SW6���i��׸�(�\���p��׸��ԍ� ���)
			if( s_bit & BIT_0 ){
				CSR_buff[t_no].SW6_DN = 59;					//�\���p��׸��ԍ� �ύX(�ځ^�r)
			}
			s_bit >>= 1;
		}
	}

															//SW�ް����e�[�u��
	s_bit = SYS_MISSEL_SV;
	s_bit >>= 4;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CARA_NO == 22 ||					//�\���p��׸��ԍ� ���
			SW_buff[t_no].CARA_NO == 23) {					//�\���p��׸��ԍ� ���
			if( s_bit & BIT_0 ){
				SW_buff[t_no].CARA_NO = 23;					//�\���p��׸��ԍ� �ύX
			}
			s_bit >>= 1;
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS_swcara_win
*  Function Name:	н̨���SW�\����א؊����̔�\��(����޳�p)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-19
********************************************************************************
*/
const	UNs	MISS_win_Tbl[9][4]={
		{15, BIT_8, BIT_0, 1},			//SW56��i��׸�, �ޯĈʒu, �ޯĈʒu, �\��2
		{16, BIT_9, BIT_1, 2},
		{17, BIT_10,BIT_2, 3},
		{18, BIT_11,BIT_3, 4},
		{79, BIT_12,BIT_4, 5},
		{80, BIT_13,BIT_5, 6},
		{81, BIT_14,BIT_6, 7},
		{82, BIT_15,BIT_7, 8},
		{0xff, 0x00, 0x00, 0xff}
	};

void	MISS_swcara_win(void)
{
	UNi	cnt, t_no, tp_no;
	UNs	s_bit;

															//���ُ��e�[�u��
	s_bit = SYS_MISSEL_SV;
	tp_no = 0;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if( CSR_buff[t_no].SW56_UP == MISS_win_Tbl[tp_no][0] ){
			if(00 == (SEQ_037_SV & MISS_win_Tbl[tp_no][1])){
				CSR_buff[t_no].SW5_DN = 61;					//�؁^��
			}
			else{
				if(00 == (s_bit & MISS_win_Tbl[tp_no][2])){
					CSR_buff[t_no].SW5_DN = 62;				//�؁^��
				}
				else{
					CSR_buff[t_no].SW5_DN = 63;				//�؁^�r
				}
			}
			tp_no++;
		}
	}

															//SW�ް����e�[�u��
	s_bit = SYS_MISSEL_SV;
	tp_no = 0;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if( SW_buff[t_no].YOBI2 == MISS_win_Tbl[tp_no][3] ){
			if(00 == (SEQ_037_SV & MISS_win_Tbl[tp_no][1])){
				SW_buff[t_no].CARA_NO = 24;					//�؁^��
			}
			else{
				if(00 == (s_bit & MISS_win_Tbl[tp_no][2])){
					SW_buff[t_no].CARA_NO = 25;				//�؁^��
				}
				else{
					SW_buff[t_no].CARA_NO = 26;				//�؁^�r
				}
			}
			tp_no++;
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_tbl_cls
*  Function Name:	Ӱ��ݐݒ�@���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	mmon_tbl_cls(UNs grp_no)
{
	UNs	cnt, t_no;

															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			CSR_buff[t_no].TOK_NO |= BIT_0;					//��\���̐ݒ�
		}
	}

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
		}
	}

															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			PV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
		}
	}

															//SW�ް����e�[�u��
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SW_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
		}
	}

}


/*
********************************************************************************
*  Module Name:		mmon_tbl_open
*  Function Name:	Ӱ��ݐݒ�@���ð��ق̕\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	mmon_tbl_open(UNs grp_no)
{
	UNs	cnt, t_no;

															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			CSR_buff[t_no].TOK_NO &= ~BIT_0;				//�\���̐ݒ�
		}
	}

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//�\���̐ݒ�
		}
	}

															//�����l���e�[�u��
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			PV_buff[t_no].SUB_NO &= ~BIT_15;				//�\���̐ݒ�
		}
	}

															//SW�ް����e�[�u��
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SW_buff[t_no].SUB_NO &= ~BIT_15;				//�\���̐ݒ�
		}
	}

}


/*
********************************************************************************
*  Module Name:		grpno_sv_cls
*  Function Name:	��ٰ�ߔԍ� �ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	grpno_sv_cls(UNs grp_no)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_cls
*  Function Name:	��ٰ�ߔԍ� �ݒ�l���ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	csrno_sv_cls(UNs csr_no)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO |= BIT_15;					//��\���̐ݒ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_open
*  Function Name:	��ٰ�ߔԍ� �ݒ�l���ð��ق̕\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	grpno_sv_open(UNs grp_no)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//�\���̐ݒ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_open
*  Function Name:	��ٰ�ߔԍ� �ݒ�l���ð��ق̕\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	csrno_sv_open(UNs csr_no)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//�\���̐ݒ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_srch
*  Function Name:	��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*
*  Return	: 		�ݒ�l�̏��ð��ق̔ԍ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-02
********************************************************************************
*/
UNs		grpno_sv_srch(UNs grp_no)
{
	UNs	cnt, t_no;

															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
			return(t_no);
		}
	}
	return(0xffff);
}


/*
********************************************************************************
*  Module Name:		SV_col_chg
*  Function Name:	�d�l�ɂ��w�i�F�̕ύX
*  Input	:		�폜�ԍ�
*  Return	: 		�Ȃ�
*  Note		:		�O���[�v�ԍ����猟��
*
*  �� ��	:A.Shimamura		ON:2010-12-06		V06b
********************************************************************************
*/
void	SV_col_chg(UNs grp_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//��ٰ�ߔԍ� ���
				SV_buff[t_no].C_COL  = MOJI_COL;			//�����F�̕ύX
				SV_buff[t_no].B_COL1 = BAK_COL1;			//�w�i�F�̕ύX
				SV_buff[t_no].B_COL2 = BAK_COL2;			//�w�i�F�̕ύX
		}
	}
}


/*
********************************************************************************
*  Module Name:		SV_col_chg2
*  Function Name:	�d�l�ɂ��w�i�F�̕ύX
*  Input	:		�폜�ԍ�
*  Return	: 		�Ȃ�
*  Note		:		�J�[�\�����ʔԍ����猟��
*
*  �� ��	:A.Shimamura		ON:2010-12-06		V06m
********************************************************************************
*/
void	SV_col_chg2(UNs csr_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//��ٰ�ߔԍ� ���
				SV_buff[t_no].C_COL  = MOJI_COL;			//�����F�̕ύX
				SV_buff[t_no].B_COL1 = BAK_COL1;			//�w�i�F�̕ύX
				SV_buff[t_no].B_COL2 = BAK_COL2;			//�w�i�F�̕ύX
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_col_chg2
*  Function Name:	�d�l�ɂ��w�i�F�̕ύX
*  Input	:		�폜�ԍ�
*  Return	: 		�Ȃ�
*  Note		:		�J�[�\�����ʔԍ����猟��
*
*  �� ��	:A.Shimamura		ON:2010-12-06		V06m
********************************************************************************
*/
void	SW_col_chg2(UNs csr_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//�ݒ�l���e�[�u��
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CSR_NO == csr_no) {				//��ٰ�ߔԍ� ���
				SW_buff[t_no].C_COL  = MOJI_COL;			//�����F�̕ύX
				SW_buff[t_no].B_COL1 = BAK_COL1;			//�w�i�F�̕ύX
				SW_buff[t_no].B_COL2 = BAK_COL2;			//�w�i�F�̕ύX
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_cls_tokusyu
*  Function Name:	���ُ��ð��ق̔�\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*  Input	:		���ð��ق�SW56��׸��ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	CSR_cls_tokusyu(UNs grp_no, UNs sw56_up)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(CSR_buff[t_no].SW56_UP == sw56_up) {			//SW56��i�ԍ� ���
				CSR_buff[t_no].TOK_NO |= BIT_0;				//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_opn_tokusyu
*  Function Name:	���ُ��ð��ق̕\�� �ݒ�
*  Input	:		���ð��ق̸�ٰ�ߔԍ�
*  Input	:		���ð��ق�SW56��׸��ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-12
********************************************************************************
*/
void	CSR_opn_tokusyu(UNs grp_no, UNs sw56_up)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//���ُ��e�[�u��
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//��ٰ�ߔԍ� ���
			if(CSR_buff[t_no].SW56_UP == sw56_up) {			//SW56��i�ԍ� ���
				CSR_buff[t_no].TOK_NO &= ~BIT_0;			//��\���̐ݒ�
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*** END ***/
