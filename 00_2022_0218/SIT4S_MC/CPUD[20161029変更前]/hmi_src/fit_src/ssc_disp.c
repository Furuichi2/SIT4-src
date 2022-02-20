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
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_addr.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//DPRAM�Q�ƕϐ���`

#include "ssa_opram.h"							//OPRAM�Q�ƕϐ���`
#include "ssc_wrmh.h"							//work ram �Q�ƕϐ���`


#define		Disp_Debug_YES	1
#define		Disp_Debug_NO	0
//#define		Disp_Debug		Disp_Debug_YES		//�o�׎�=NO
#define		Disp_Debug		Disp_Debug_NO		//�o�׎�=NO


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	RULET_GAMEN_INIT(void);			//ٰگĕ\���̏�����
//extern	void	GRAPH_INIT(void);				//�O���t�`�揉������
//extern	void	GRAPH_DISP(void);				//�O���t�`�揈��
extern	void	kag_to_kaj_sub_chg(void);		//�����ʒu���ڕW�׏d ���ٰ��No.�؊�

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		SV_SEQDT2_A91_INI;				//�V�[�P���X���j�^�ݒ�Q /* V00p */
extern	UNs		SV_INTER_VER2;					// ����۰�����ް�ޮ�	(121.15-140.0~15���Ԃ�) /* V00p */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		ET1_VER[4];						// ET1�ް�ޮ�		V05
extern	UNs		SV_SEQDT1_A91_INI;				//V06
extern	UNs		SV_INTER_VER1;					//V06
extern	UNs		GMN_PAR137;
extern	UNs		GMN_PAR021;						//V06m
extern	UNs		dpram_top;						//SIT4-MC
extern	UNs		dpramB_top;						//SIT4-MC
extern	UNs		GMN_PAR051;			//�����[�X����
extern	UNs		GMN_PAR052;			//�����[�X�J���I���s��
extern	UNs		GMN_PAR053;			//�����[�X�J���I���p�x
extern	UNs		GMN_PAR054;			//�����[�X�J���I�t�s��
extern	UNs		GMN_PAR055;			//�����[�X�J���I�t�p�x
extern	UNs		GMN_PAR056;			//�����[�X�J���ݒ�Ώ�
extern	UNs		GMN_PAR057;			//���荂��
extern	UNs		GMN_PAR058;			//����J���I���s��
extern	UNs		GMN_PAR059;			//����J���I���p�x
extern	UNs		GMN_PAR060;			//����J���I�t�s��
extern	UNs		GMN_PAR061;			//����J���I�t�p�x
extern	UNs		GMN_PAR062;			//����J���ݒ�Ώ�
extern	UNs		GMN_PAR063;			//�^�C�~���O�J���I���s��
extern	UNs		GMN_PAR064;			//�^�C�~���O�J���I���p�x
extern	UNs		GMN_PAR065;			//�^�C�~���O�J���I�t�s��
extern	UNs		GMN_PAR066;			//�^�C�~���O�J���I�t�p�x
extern	UNs		GMN_PAR067;			//�^�C�~���O�J���ݒ�Ώ�
extern	UNs		GMN_PAR068;			//�J���o�͎������Z�@�\�L��
extern	UNs		GMN_PAR078;			//�J���ԍ��ݒ�\
extern	UNs		GMN_PAR077;						//�J��Ԃ��񐔏��								2014/09/04
extern	UNs		GMN_PAR079;						//���̈�ݒ� �L���^����						2014/09/10

/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	GAMEN_disp(void);						//��ʕ\��
void	WIN_gamen_disp(void);					//����޳��ʕ\��
void	GAMEN_base_disp(void);					//�x�[�X��ʕ\��
void	GAMEN_no_chg(void);						//��ʂm���D�ύX
void	GAMEN_cls(void);						//��ʃf�[�^�N���A
void	WIN_gamen_cls(void);					//����޳��ʃf�[�^�N���A
void	DISP_after_csr(void);					//��ʕ\���̃J�[�\���㏈��
void	DISP_after(void);						//��ʕ\���̌㏈��
void	WIN_disp_after(void);					//����޳��ʕ\���̌㏈��
void	WIN_disp_after2(void);					//����޳��ʕ\���̌㏈��2
void	Alltbl_set(void);						//���ð��ق̍쐬
void	Wintbl_set(void);						//����޳��ʂ̏��ð��ق̍쐬
void	Disp_data_set(void);					//���ð��ق̔�\������(�쐬)
void	gamen_tbl_set(void);					//��ʂ̏��ð��ق̔�\������(�쐬)
void	win_tbl_set(void);						//����޳��ʂ̏��ð��ق̔�\������(�쐬)
void	motion_csr_clr(void);
void	EPM_TANI_CHG(void);
void	mot_type_SWset(UNs ktop);				//���[�V����TYPE�pSW�Z�b�g		V06p
U2b		MOT_INF_GET(void);						//���[�V�����ݒ���擾
void	mark_chg_no_disp(void);					//�����i�ʒu�^�׏d�j�ؑ֕\���Ȃ�
void	WIN_DISP_after_csr(void);				//��ʕ\���̌㏈��				//2016/04/22


/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNl *	CSCOUNT_Adr_tbl[70];
extern	const	CSR_TBL_TDEF *	CSTBL_Adr_tbl[70];
extern	const	UNl *	SVCOUNT_Adr_tbl[70];
extern	const	SV_TBL_TDEF *	SVTBL_Adr_tbl[70];
extern	const	UNl *	PVCOUNT_Adr_tbl[70];
extern	const	PV_TBL_TDEF *	PVTBL_Adr_tbl[70];
extern	const	UNl *	SWCOUNT_Adr_tbl[70];
extern	const	SW_TBL_TDEF *	SWTBL_Adr_tbl[70];

extern	const	UNl *	CSCOUNT_Win_Adr_tbl[30];
extern	const	CSR_TBL_TDEF *	CSTBL_Win_Adr_tbl[30];
extern	const	UNl *	SVCOUNT_Win_Adr_tbl[30];
extern	const	SV_TBL_TDEF *	SVTBL_Win_Adr_tbl[30];
extern	const	UNl	 *PVCOUNT_Win_Adr_tbl[30];
extern	const	PV_TBL_TDEF *	PVTBL_Win_Adr_tbl[30];
extern	const	UNl *	SWCOUNT_Win_Adr_tbl[30];
extern	const	SW_TBL_TDEF *	SWTBL_Win_Adr_tbl[30];

const	UNs *	Camcsr_Name_Tbl[20] = {
			&PV_CAMNA01_C1[0],		//00/* ���[�^���J���P���� */
			&PV_CAMNA02_C1[0],		//01/* ���[�^���J���Q���� */
			&PV_CAMNA03_C1[0],		//02/* ���[�^���J���R���� */
			&PV_CAMNA04_C1[0],		//03/* ���[�^���J���S���� */
			&PV_CAMNA05_C1[0],		//04/* ���[�^���J���T���� */
			&PV_CAMNA06_C1[0],		//05/* ���[�^���J���U���� */
			&PV_CAMNA07_C1[0],		//06/* ���[�^���J���V���� */
			&PV_CAMNA08_C1[0],		//07/* ���[�^���J���W���� */
			&PV_CAMNA09_C1[0],		//08/* ���[�^���J���X���� */
			&PV_CAMNA10_C1[0],		//09/* ���[�^���J���P�O���� */
			&PV_CAMNA11_C1[0],		//10/* ���[�^���J���P�P���� */
			&PV_CAMNA12_C1[0],		//11/* ���[�^���J���P�Q���� */
			&PV_CAMNA13_C1[0],		//12/* ���[�^���J���P�R���� */
			&PV_CAMNA14_C1[0],		//13/* ���[�^���J���P�S���� */
			&PV_CAMNA15_C1[0],		//14/* ���[�^���J���P�T���� */
			&PV_CAMNA16_C1[0],		//15/* ���[�^���J���P�U���� */
			&PV_CAMNA17_C1[0],		//16/* ���[�^���J���P�V���� */
			&PV_CAMNA18_C1[0],		//17/* ���[�^���J���P�W���� */
			&PV_CAMNA19_C1[0],		//18/* ���[�^���J���P�X���� */
			&PV_CAMNA20_C1[0]		//19/* ���[�^���J���Q�O���� */
		};

const	UNs *	Camcsr_Name_TblSV[20] = {
			&SV_CAMNA01_C1[0],		//00/* ���[�^���J���P���� */
			&SV_CAMNA02_C1[0],		//01/* ���[�^���J���Q���� */
			&SV_CAMNA03_C1[0],		//02/* ���[�^���J���R���� */
			&SV_CAMNA04_C1[0],		//03/* ���[�^���J���S���� */
			&SV_CAMNA05_C1[0],		//04/* ���[�^���J���T���� */
			&SV_CAMNA06_C1[0],		//05/* ���[�^���J���U���� */
			&SV_CAMNA07_C1[0],		//06/* ���[�^���J���V���� */
			&SV_CAMNA08_C1[0],		//07/* ���[�^���J���W���� */
			&SV_CAMNA09_C1[0],		//08/* ���[�^���J���X���� */
			&SV_CAMNA10_C1[0],		//09/* ���[�^���J���P�O���� */
			&SV_CAMNA11_C1[0],		//10/* ���[�^���J���P�P���� */
			&SV_CAMNA12_C1[0],		//11/* ���[�^���J���P�Q���� */
			&SV_CAMNA13_C1[0],		//12/* ���[�^���J���P�R���� */
			&SV_CAMNA14_C1[0],		//13/* ���[�^���J���P�S���� */
			&SV_CAMNA15_C1[0],		//14/* ���[�^���J���P�T���� */
			&SV_CAMNA16_C1[0],		//15/* ���[�^���J���P�U���� */
			&SV_CAMNA17_C1[0],		//16/* ���[�^���J���P�V���� */
			&SV_CAMNA18_C1[0],		//17/* ���[�^���J���P�W���� */
			&SV_CAMNA19_C1[0],		//18/* ���[�^���J���P�X���� */
			&SV_CAMNA20_C1[0]		//19/* ���[�^���J���Q�O���� */
		};

const	UNs *	Camcsr_Name_Tbl1[20] = {
			&SV_CAMNA0_C1,			//���[�^���J���P�ėp�I�����
			&SV_CAMNA1_C1,			//���[�^���J���Q�ėp�I�����
			&SV_CAMNA2_C1,			//���[�^���J���R�ėp�I�����
			&SV_CAMNA3_C1,			//���[�^���J���S�ėp�I�����
			&SV_CAMNA4_C1,			//���[�^���J���T�ėp�I�����
			&SV_CAMNA5_C1,			//���[�^���J���U�ėp�I�����
			&SV_CAMNA6_C1,			//���[�^���J���V�ėp�I�����
			&SV_CAMNA7_C1,			//���[�^���J���W�ėp�I�����
			&SV_CAMNA8_C1,			//���[�^���J���X�ėp�I�����
			&SV_CAMNA9_C1,			//���[�^���J���P�O�ėp�I�����
			&SV_CAMNAA_C1,			//���[�^���J���P�P�ėp�I�����
			&SV_CAMNAB_C1,			//���[�^���J���P�Q�ėp�I�����
			&SV_CAMNAC_C1,			//���[�^���J���P�R�ėp�I�����
			&SV_CAMNAD_C1,			//���[�^���J���P�S�ėp�I�����
			&SV_CAMNAE_C1,			//���[�^���J���P�T�ėp�I�����
			&SV_CAMNAF_C1,			//���[�^���J���P�U�ėp�I�����

			&SV_CAMNA_C1,			//���[�^���J���P�V�`�Q�O�p�_�~�[�̈�
			&SV_CAMNA_C1,			//���[�^���J���P�V�`�Q�O�p�_�~�[�̈�
			&SV_CAMNA_C1,			//���[�^���J���P�V�`�Q�O�p�_�~�[�̈�
			&SV_CAMNA_C1			//���[�^���J���P�V�`�Q�O�p�_�~�[�̈�
		};

const	UNs *	Camcsr_Name_TblSW[16] = {
			&PV_CAMNAM_C2[0],		//�ėp�o�͎��� BIT_0
			&PV_CAMSW1_C1[0],		//�ėp�o�͎��� BIT_1
			&PV_CAMSW2_C1[0],		//�ėp�o�͎��� BIT_2
			&PV_CAMSW3_C1[0],		//�ėp�o�͎��� BIT_3
			&PV_CAMSW4_C1[0],		//�ėp�o�͎��� BIT_4
			&PV_CAMSW5_C1[0],		//�ėp�o�͎��� BIT_5
			&PV_CAMSW6_C1[0],		//�ėp�o�͎��� BIT_6
			&PV_CAMSW7_C1[0],		//�ėp�o�͎��� BIT_7
			&PV_CAMSW8_C1[0],		//�ėp�o�͎��� BIT_8
			&PV_CAMSW9_C1[0],		//�ėp�o�͎��� BIT_9
			&PV_CAMSWA_C1[0],		//�ėp�o�͎��� BIT_A
			&PV_CAMSWB_C1[0],		//�ėp�o�͎��� BIT_B
			&PV_CAMSWC_C1[0],		//�ėp�o�͎��� BIT_C
			&PV_CAMSWD_C1[0],		//�ėp�o�͎��� BIT_D
			&PV_CAMSWE_C1[0],		//�ėp�o�͎��� BIT_E
			&PV_CAMSWF_C1[0],		//�ėp�o�͎��� BIT_F
		};


/*
********************************************************************************
*  Module Name:		GAMEN_disp
*  Function Name:	��ʕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	GAMEN_disp(void)
{
	GGAMEN_DISP_FLG = 0xff;					//��ʕ\�����䒆�t���O�n�m
	SVPV_LCD_FLG = 0xff;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

	Lcd_off();								//���OFF

	GAMEN_base_disp();						//�x�[�X��ʕ\��

	SVdata_disp();							//�ݒ�l���@�\��
	PVdata_disp_all();						//�S�@�����l���@�\��

	SWchg_disp();							//�r�v�f�[�^���@�\��

	Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

	DISP_after();							//��ʕ\���̌㏈��

	if(CSR_FLG == 5){
	}
	else{
		CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
	}
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�
	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g

	DISP_after_csr();						//��ʕ\���̃J�[�\���㏈��

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	WDT_Rifresh();							//�����ޯ����- ��گ��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��

	Lcd_on();								//���ON

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
	GGAMEN_DISP_FLG = 0x00;					//��ʕ\�����䒆�t���O�n�e�e

}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	GAMEN_disp(void)
{
	GGAMEN_DISP_FLG = 0xff;					//��ʕ\�����䒆�t���O�n�m
	SVPV_LCD_FLG = 0xff;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

	WDT_Rifresh();							//�����ޯ����- ��گ��	INS

	GAMEN_base_disp();						//�x�[�X��ʕ\��

	SEQ_PAR_051 &= ~cBIT14;					//���[�h�ύX�L��t���OOFF		V06n

	Gamenn_Disp_Csr(LCD_VBASE);					//��ʂm���D���̃J�[�\���L�����N�^�S�\��

	SVdata_disp();							//�ݒ�l���@�\��
	PVdata_disp_all();						//�S�@�����l���@�\��

	SWchg_disp();							//�r�v�f�[�^���@�\��

	WDT_Rifresh();							//�����ޯ����- ��گ��	INS

	Gamenn_Graphic(LCD_VBASE);					//��ʂm���D���̃O���t�B�b�N�S�\��

	DISP_after();							//��ʕ\���̌㏈��

	if(CSR_FLG == 5){
	}
	else{
		CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
	}

	DISP_after_csr();						//��ʕ\���̃J�[�\���㏈��

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�
	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g

	WDT_Rifresh();							//�����ޯ����- ��گ��

	if ( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30)	//���[�V�����̈�����[�N��   ��ނ�����
	{
		mmon_vabse_to_vmon1();
		SV_DANSUU_SRV_BAK = 0;
		mmon_tchk_disp(0);
		mmon_vmon2_to_vbase();
	}

	LCD_All_Disp();

	if ( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30)	//���[�V�����̈�����[�N��   ��ނ�����
	{
		mmon_vmon1_to_vbase();
	}

	WDT_Rifresh();							//�����ޯ����- ��گ��	INS

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
	GGAMEN_DISP_FLG = 0x00;					//��ʕ\�����䒆�t���O�n�e�e

	SEQ_PAR_058 &= ~cBIT2;					//�J���������Z���ʐݒ�s�N���A				2014/08/29
	PV0_CAMATCAL_MES1 = 0;					//���b�Z�[�W�N���A
	PV0_CAMATCAL_MES2 = 0;					//���b�Z�[�W�N���A
	PV0_CAMATCAL_MES3 = 0;					//���b�Z�[�W�N���A
	PV0_CAMATCAL_FLG  = 0;					//�J���o�͎����ݒ�t���O�N���A					2014/09/12
	PV0_FMOTSET_MES1 = 0;					//��葬�x�ݒ胁�b�Z�[�W�N���A					2014/10/09
}
#endif


/*
********************************************************************************
*  Module Name:		WIN_gamen_disp
*  Function Name:	����޳��ʕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	WIN_gamen_disp(void)
{
	UNs		i;

	SVPV_LCD_FLG = 0xff;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

	WIN_gamen_cls();						//����޳��ʃf�[�^�N���A

	WIN_disp_after();						//��ʕ\���̌㏈��

	i = 0x0001;
	if( WINDOW_NO == 6 ) {					//������޳��ʁ@�H
		i |= BIT_15;						//������޳ �׸� ON
	}
	if( (WINDOW_NO > 6) && (WINDOW_NO < 10) ) {		//������޳��ʁ@�H		V01j
		i |= BIT_15;						//������޳ �׸� ON
	}
	disp_all_s(WINDOW_NO, i, 0x00);			//�S��ʕ\���p�������ށ��ޯĕϊ�

	Wintbl_set();							//����޳��ʂ̏��ð��ق̍쐬

	SVdata_disp();							//�ݒ�l���@�\��
	PVdata_disp_all();						//�S�@�����l���@�\��
	SWchg_disp();							//�r�v�f�[�^���@�\��

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	WIN_disp_after2();						//����޳��ʕ\���̌㏈��2

	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

	Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

	WDT_Rifresh();							//�����ޯ����- ��گ��

	for( i=6 ; i < 15 ; i++ ) {
		Lcd_line(00, i, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
		Lcd_line(01, i, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)
	}

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	WIN_gamen_disp(void)
{
	UNs		i;

	SVPV_LCD_FLG = 0xff;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

	Windown_Disp_Init();

	WIN_gamen_cls();						//����޳��ʃf�[�^�N���A

	WIN_disp_after();						//��ʕ\���̌㏈��

	i = 0x0001;
	if( WINDOW_NO == 6 ) {					//������޳��ʁ@�H
		i |= BIT_15;						//������޳ �׸� ON
	}
	if( (WINDOW_NO > 6) && (WINDOW_NO < 10) ) {		//������޳��ʁ@�H		V01j
		i |= BIT_15;						//������޳ �׸� ON
	}

	disp_all_s_color(LCD_VBASE);		//�S��ʕ\���p�������ށ��ޯĕϊ�

	Wintbl_set();							//����޳��ʂ̏��ð��ق̍쐬

	Gamenn_Disp_Csr(LCD_VBASE);						//��ʂm���D���̃J�[�\���L�����N�^�S�\��

	SVdata_disp();							//�ݒ�l���@�\��
	PVdata_disp_all();						//�S�@�����l���@�\��

	SWchg_disp();							//�r�v�f�[�^���@�\��

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	WIN_disp_after2();						//����޳��ʕ\���̌㏈��2

	Gamenn_Graphic(LCD_VBASE);					//��ʂm���D���̃O���t�B�b�N�S�\��

	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

	WIN_DISP_after_csr();					//��ʕ\���̌㏈��				//2016/04/22

	WDT_Rifresh();							//�����ޯ����- ��گ��

	WIN_All_Disp();

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
}
#endif


/*
********************************************************************************
*  Module Name:		GAMEN_base_disp
*  Function Name:	�x�[�X��ʕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	GAMEN_base_disp(void)
{

	GAMEN_no_chg();						//��ʂm���D�ύX
	GAMEN_cls();						//��ʃf�[�^�N���A

	disp_all_s(GAMEN_NO, 0x00, 0x00);	//�S��ʕ\���p�������ށ��ޯĕϊ�

	WDT_Rifresh();						//�����ޯ����- ��گ��

	Alltbl_set();						//���ð��ق̍쐬
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	GAMEN_base_disp(void)
{
	Gamenn_Disp_Init();

	GAMEN_no_chg();						//��ʂm���D�ύX
	GAMEN_cls();						//��ʃf�[�^�N���A

	disp_all_s_color(LCD_VBASE);		//�S��ʕ\���p�������ށ��ޯĕϊ�

	if (SEQ_PAR_113 & BIT_2)			//�������\�������H			//V05r(INS)
	{
//		Disp_seidouseinou(1,LCD_VBASE);		//�������\�\��
		SEIDOU_SEQ_LST &= ~BIT_2;			//�������\�\��
	}

	WDT_Rifresh();						//�����ޯ����- ��گ��

	Alltbl_set();						//���ð��ق̍쐬
}
#endif


/*
********************************************************************************
*  Module Name:		GAMEN_no_chg
*  Function Name:	��ʂm���D�ύX
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	GAMEN_no_chg(void)
{

	if(GAMEN_NO == 2){				//���Y��ʁ@2�͖��g�p
		GAMEN_NO = 1;				//���Y��ʁ@��{
	}

	/* V01d */
////	else if(GAMEN_NO == 6){			//�i���ʁ@�ȈՕ\���@�Ȃ�
////		GAMEN_NO = 7;				//�i���ʁ@���@�\�\��
////	}

//	else if(GAMEN_NO == 11){		//�ݒ��ʁ@�ް��ݒ�
//SIT-S�Ȃ�		if(SEQ_016_SV & BIT_7){		//���@�\�I��(�ȈՌ^�^���@�\�^(1:���@�\))
//			GAMEN_NO == 17;			//�ݒ��ʁ@�ް��ݒ蒆�^
//		}
//	}

	else if(GAMEN_NO == 21){		//�ݒ��ʁ@۰�ض�1��ʁH
		if(ROT1_GAMEN_NON == 0xff){
			GAMEN_NO == 22;			//�ݒ��ʁ@۰�ض�2
		}
		if(ROT2_GAMEN_NON == 0xff){
			GAMEN_NO == 25;			//�ݒ��ʁ@۰�ض�3
		}
		if(ROT3_GAMEN_NON == 0xff){
			GAMEN_NO == 21;			//�ݒ��ʁ@۰�ض�1
		}
	}

//;/*********	2000-01-05	��^�N�����p�U��H�I�� V03a	**************/
//	CMP	GAMEN_NO,18			;
//	JNE	GAMNO_CHG_500			;
//;
//	TEST	SEQ_022_SV,BIT_5		;/* ��^����ߑI�����n�m�������炾�� */
//	JNZ	GAMNO_CHG_500			;
//	TEST	SEQ_026_SV,BIT_1		;/*  */
//	JZ	GAMNO_CHG_500			;
//;
//	MOV	GAMEN_NO,28			;
//	JMP	GAMNO_CHG_END			;
//;/****************************************************************************/
//GAMNO_CHG_500:
//;
//GAMNO_CHG_END:

}


/*
********************************************************************************
*  Module Name:		GAMEN_cls
*  Function Name:	��ʃf�[�^�N���A
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	GAMEN_cls(void)
{
	UNi	size;
	UNs	*dst1_p, *dst2_p;

	DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

	WDT_Rifresh();						//�����ޯ����- ��گ��

#if	( SIT_TYPE_SEL == TYPE_SIT3 )
	dst1_p= &LCD_WORK1[0][0][0];		//�̈�N���A(�\��ܰ��̈�LCD1)
	dst2_p= &LCD_WORK2[0][0][0];		//�̈�N���A(�\��ܰ��̈�LCD2)
	size = (sizeof(LCD_WORK1) >> 1);
	while(size--) {
		*dst1_p++ = 0x0000;				//�̈�R�s�[
		*dst2_p++ = 0x0000;				//�̈�R�s�[
	}
#else
	Gamenn_Screen(LCD_VBASE);						//��ذݐF�Ŗ��߂�
#endif

	WDT_Rifresh();						//�����ޯ����- ��گ��

	memset_word(&CSR_buff[0].XY_POS, 0x0000, (sizeof(CSR_buff)/2));		//�̈�N���A(�J�[�\�����e�[�u����`�̈�)
	memset_word(&SV_buff[0].XY_POS, 0x0000, (sizeof(SV_buff)/2));		//�̈�N���A(�ݒ�l���e�[�u����`�̈�)
	memset_word(&PV_buff[0].XY_POS, 0x0000, (sizeof(PV_buff)/2));		//�̈�N���A(�����l���e�[�u����`�̈�)
	memset_word(&SW_buff[0].XY_POS, 0x0000, (sizeof(SW_buff)/2));		//�̈�N���A(�r�v�f�[�^���e�[�u����`�̈�)

	CSR_CNT = 0;						/* �J�[�\���J�E���^ */
	CSR_CNT1 = 0;						/* �J�[�\���J�E���^ */
	SV_CNT = 0;							/* �ݒ�l�J�E���^ */
	PV_CNT = 0;							/* �����l�J�E���^ */
	SW_CNT = 0;							/* �r�v�f�[�^�J�E���^ */
	SW_CNT1 = 0;						/* �r�v�f�[�^�J�E���^ */

	CSR_TBL_POS_NOW = 0xff;
	SV_TBL_POS_NOW = 0xff;
	SW_TBL_POS_NOW = 0xff;

	CSR_MOVE_OK_FLG = 0;				//���وړ��׸�(00:�ړ��^FF:�֎~)
	CSR_MOVE_NON = 0;					//ENT KEY��̶��وړ��׸�(00:�ړ��^FF:�֎~)

	CSR_POS_LAST = 0xffff;				/* �O��J�[�\���|�W�V�����f�[�^�N���A */
	CSR_BAK_X_POS = 0xffff;				/* �O��J�[�\���|�W�V�����f�[�^�N���A */

	SV_DATA_CHG = 0x00;					//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
	CSR_ON_FLG = 0x00;					/* �J�[�\���\���t���O�n�e�e */
	SW14_ON_FLG = 0x00;

	RULET_DISP_FLG = 0;					//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
	DEG_DISP_FLG = 0;					//�p�x�\���t���O(00:�Ȃ��^FF:����)
	SEISAN_DISP_FLG = 0;				//���Y�̍s���\��(00:�Ȃ��^FF:����)
	INTROCK_DISP_FLG = 0;				//�K�C�_���X�\��(00:�Ȃ��^FF:����)

//	STOP_DISP_FLG = 0;					//�r�o�l�\��(00:�Ȃ��^FF:����)

	SEI_INF_FLG_LAST = 0x0FF;
//	IL_DISP_LAST = 0x0FF;

	IROCK_NO_LAST[0] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[1] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[2] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[3] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[4] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[5] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[6] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/

//	IL_DISP_FLG = 0x00;					/* �h�k�\���t���O���Z�b�g */

	WINDOW_NO = 0x00;					/* �E�C���h�E��ʔԍ��N���A */

	PV_DISP_CNT = 0x01;

	RULET_NOW_LST = 0x0FFFF;
	DEG_DISP_LST = 0x0FFFF;				/* �p�x�ް��ω�����H */
	STOPTIME_DISP_LST = 0x0FFFF;		/* �p�x�ް��ω�����H */

	SEISAN_SW56_FLG = 0x00;

//V06n	SEQ_PAR_051 = 0;
//2016/04/22	SEQ_PAR_052 = 0;
//2016/04/22	SEQ_PAR_054 = 0;

	RULET_HIGH_FLG = 0x055;				/* �������[���b�g�`��t���O�N���A */

	CSR_DAN_CSR_LST = 0x0FF;			/* �i�����SW56���ݽ��ݾٗp */

	SW56_MUSK_FLG = 0x0404;

	ADC_DISP_FLG = 0;			/* �`�c�b�E�C���h�E�\�����N���A */
	ADC_SW2_FLG = 0;			/* �r�v�R�S���n�m���Ă���Ύ󂯕t���Ȃ� */
	ADC_SW34_FLG = 0;			/* �r�v�R�S���n�m���Ă���Ύ󂯕t���Ȃ� */

	ADC_SW5_FLG = 0;			/* �r�v�T�o�̓V�[�P���X�N���A */
	ADC_SW6_FLG = 0;			/* �r�v�T�o�̓V�[�P���X�N���A */

	EPM_TANI_CHG();				//V06a
}


/*
********************************************************************************
*  Module Name:		WIN_gamen_cls
*  Function Name:	����޳��ʃf�[�^�N���A
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
void	WIN_gamen_cls(void)
{

	CSR_POS_LAST = 0xffff;				/* �O��J�[�\���|�W�V�����f�[�^�N���A */	//V06c
	CSR_BAK_X_POS = 0xffff;				/* �O��J�[�\���|�W�V�����f�[�^�N���A */	//V06c

	CSR_disp_off();						//�J�[�\���\������

#if	( SIT_TYPE_SEL == TYPE_SIT3 )
	memset_word(&LCD_WORK2[6][0][0], 0x0000, 9*16*40);	//����ʂ̃��[���b�g�\�������N���A����
#else
	Window_Screen(LCD_VBASE);					//��ذݐF�Ŗ��߂�
#endif

	CSR_TBL_POS_NOW = 0xff;
	SV_TBL_POS_NOW = 0xff;
	SW_TBL_POS_NOW = 0xff;

	CSR_MOVE_OK_FLG = 0;				//���وړ��׸�(00:�ړ��^FF:�֎~)

	SV_DATA_CHG = 0x00;					//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
	SW14_ON_FLG = 0x00;

//	IL_DISP_LAST = 0x0FF;

	IROCK_NO_LAST[0] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[1] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[2] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[3] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[4] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[5] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/
	IROCK_NO_LAST[6] = 0xffff;			/* ����ۯ��\���ԍ���O��l	*/

//	IL_DISP_FLG = 0x00;					/* �h�k�\���t���O���Z�b�g */
	RULET_NOW_LST = 0x0FFFF;

	SEISAN_SW56_FLG = 0x00;

	RULET_HIGH_FLG = 0x055;				/* �������[���b�g�`��t���O�N���A */
	CSR_DAN_CSR_LST = 0x0FF;			/* �i�����SW56���ݽ��ݾٗp */
	SW56_MUSK_FLG = 0x0404;

	ADC_DISP_FLG = 0;			/* �`�c�b�E�C���h�E�\�����N���A */
	ADC_SW2_FLG = 0;			/* �r�v�R�S���n�m���Ă���Ύ󂯕t���Ȃ� */
	ADC_SW34_FLG = 0;			/* �r�v�R�S���n�m���Ă���Ύ󂯕t���Ȃ� */

	ADC_SW5_FLG = 0;			/* �r�v�T�o�̓V�[�P���X�N���A */
	ADC_SW6_FLG = 0;			/* �r�v�T�o�̓V�[�P���X�N���A */

	EPM_TANI_CHG();				//V06a
}


/*
********************************************************************************
*  Module Name:		DISP_after_csr
*  Function Name:	��ʕ\���̃J�[�\���㏈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
void	DISP_after_csr(void)
{
	switch(GAMEN_NO) {
		default:
		case 2:			//���Y��ʁ@���^��{(���g�p)
		case 6:			//�i���ʁ@��{(��ʔԍ��U�r�v�P�`�S����)(���g�p)
			break;

		case 1:			//���Y��ʁ@��{(��ʔԍ��P�r�v�P�`�S����)
			if( 00 == (SEQ_016_SV & BIT_12) &&		//ۯĶ���1�̔�\��
				00 == (SEQ_016_SV & BIT_14) ) {		//ۯĶ���2�̔�\��
				SW56_dncara_disp(0xff, 4);			//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 12);			//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				Under_grph();						//���i�̃O���t�B�b�N�Z�b�g
			}

			SW14_ON1_FLG = 0;					//�J�[�\���ʒu�N���A	2014/09/02

			switch(SW14_ON1_FLG) {
				default:
					SW14_ON1_FLG = 0;
				case 0000:							//�O�񉽂��̃L�[�������ꂢ�����H
//2014/09/02
					SW56_upcara_disp(266, 5);			//SW56��i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
					SW56_dncara_disp(76, 7);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_dncara_disp(77, 8);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW16data_onset(0x00, 5);			//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
					Under_grph();						//���i�̃O���t�B�b�N�Z�b�g
					break;

				case 0x0002:						//��İ�ٶ���������
				case 0x0082:						//��İ�ٶ���������
					CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
					SV_FLG_CNT = 0;					//�ݒ�l�ԍ��Z�b�g
					SW_FLG_CNT = 1;					//�r�v�ԍ��Z�b�g
					CSR_move(05, 00);				//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

					SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
					SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

					if(SW14_ON1_FLG & 0x80){
						COUNT_HOSEI_ADR = PV_buff[0].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�
						Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
																//�J�E���^�␳,�r�v�T
						SW56_upcara_disp(06, 05);		//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
														//��,�r�v�T
						SW56_dncara_disp(05, 07);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
														//��,�r�v�U
						SW56_dncara_disp(06, 0x08);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					}
					Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
					break;

				case 0x0003:						//��ۯĶ���1������
				case 0x0083:						//��ۯĶ���1������
					if( SEQ_016_SV & BIT_12 ) {		//ۯĶ���1�̔�\���H
						CSR_FLG_CNT = 2;				//�J�[�\���ԍ��Z�b�g
						SV_FLG_CNT = 1;					//�ݒ�l�ԍ��Z�b�g
						SW_FLG_CNT = 1;					//�r�v�ԍ��Z�b�g
						CSR_move(05, 00);				//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

						SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

						if(SW14_ON1_FLG & 0x80){
							COUNT_HOSEI_ADR = PV_buff[1].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
														//�J�E���^�␳,�r�v�T
							SW56_upcara_disp(06, 05);	//�r�v�T�U��i�L�����N�^���r�v�̈�֊i�[(SW56��i��׸�,�\���ʒu)
														//��,�r�v�T
							SW56_dncara_disp(05, 07);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
														//��,�r�v�U
							SW56_dncara_disp(06, 0x08);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
						}
						Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
					}
					else{
						SW14_ON1_FLG = 0;
					}
					break;

				case 0x0004:						//��ۯĶ���2������
				case 0x0084:						//��ۯĶ���2������
					if( SEQ_016_SV & BIT_14 ) {		//ۯĶ���2�̔�\��
						CSR_FLG_CNT = 3;				//�J�[�\���ԍ��Z�b�g
						SV_FLG_CNT = 1;					//�ݒ�l�ԍ��Z�b�g
						SW_FLG_CNT = 1;					//�r�v�ԍ��Z�b�g
						CSR_move(05, 00);				//�J�[�\���ړ�(�߂�l�w��,�ړ�OK)

						SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

						if(SW14_ON1_FLG & 0x80){
							COUNT_HOSEI_ADR = PV_buff[2].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�
							Count_hosei_csr_on(COUNT_HOSEI_ADR);	//�J�E���^�␳�̎����l���]����
														//�J�E���^�␳,�r�v�T
							SW56_upcara_disp(06, 5);	//�r�v�T�U��i�L�����N�^���r�v�̈�֊i�[(SW56��i��׸�,�\���ʒu)
														//��,�r�v�T
							SW56_dncara_disp(05, 7);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
														//��,�r�v�U
							SW56_dncara_disp(06, 8);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
						}
						Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
					}
					else{
						SW14_ON1_FLG = 0;
					}
					break;

				case 5:						//������ײ�ނ�����		V01z(�ǉ�)
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
					break;

			}
			break;

//		case 3:			//���Y��ʁ@Ӱ��ݐݒ�
//		case 28:		//�ݒ��ʁ@Ӱ��ݐݒ�
//			mmon_kaiten_chg();							//��]�����ɂ��ݒ�l �؊���
//			break;

		case 7:			//�i���ʁ@���^��{(��ʔԍ��U�r�v�P�`�S����)
//			if(SW14_DISP7_NON == 0xff){
//				return;
//			}

//2016/02/25			if(SW14_ON6_FLG < 11){
			if(SW14_ON6_FLG <= 5){
				if(SW14_ON6_FLG == 0){				//�O�񉽂�������Ă��Ȃ��H
					CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
				}
				else{
					CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
					CSR_FLG_CNT = (SW14_ON6_FLG & 0x00ff);	//�J�[�\���ԍ��Z�b�g
					CSR_FLG_CNT --;
				}
			}
			else if (SW14_ON6_FLG == 16) {			//2016/02/25
				CSR_FLG = 5;						//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = 5;					//�J�[�\���ԍ��Z�b�g
			}
			else{
				CSR_FLG = 5;						//�J�[�\���\���ʒu�w��
//2016/02/25				CSR_FLG_CNT = CSR_FLG_CNT_LST;		//�J�[�\���ԍ��Z�b�g
				CSR_FLG_CNT = 1;					//�J�[�\���ԍ��Z�b�g
			}

//2016/02/25			SV_FLG_CNT = 0;							//�ݒ�l�ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 0;							//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

			SW16data_onset(0xff, 05);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			if(CSR_FLG_CNT == 1 &&		//�X���C�h����
				SEQ_020_SV & 0x0050){				//�E�C���h�E���o������
//				SEQ_020_SV & 0x0060){				//�E�C���h�E���o������
													//SW5
				SW56_dncara_disp(0xff, 7);			//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
													//SW6 �J��
				SW56_dncara_disp(16, 8);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();						//���i�̃O���t�B�b�N�Z�b�g
			}
			if(DAN_DAN_FLG != 0xff ||				//�E�B���h�E��ʂ܂Ŗ߂�����
				WINDOW_NO_BACK == 0 ){				//�i����ʂ֖߂�Ƃ��͂���Ȃ�
				return;
			}
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���̶݂��وʒu���Ǎ�
//			DAN_WIN_FLG = 0xff;

			CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g

			disp_stg_sel = E_kstg_scon;				//�i��[�X���C�h����]��
			WINDOW_NO = WINDOW_NO_BACK;				//�J��
			WIN_gamen_disp();						//����޳��ʕ\��

//			DAN_WIN_FLG = 0x00;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����

			CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

			G07_WIN_FLG = 0xff;
			break;

		case 8:			//�i���ʁ@���^��{(��ʔԍ��U�r�v�P�`�S����)  //V01r
//			if(SW14_DISP7_NON == 0xff){
//				return;
//			}

			if(SW14_ON6_FLG < 11){
				if(SW14_ON6_FLG == 0){				//�O�񉽂�������Ă��Ȃ��H
					CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
				}
				else{
					CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
					CSR_FLG_CNT = (SW14_ON6_FLG & 0x00ff);	//�J�[�\���ԍ��Z�b�g
//V01j					CSR_FLG_CNT --;
				}
			}
			else if (SW14_ON6_FLG == 16) {			//2016/02/25
				CSR_FLG = 5;						//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = 11;					//�J�[�\���ԍ��Z�b�g
			}
			else{
				CSR_FLG = 5;						//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = CSR_FLG_CNT_LST;		//�J�[�\���ԍ��Z�b�g
			}

//2016/02/25			SV_FLG_CNT = 0;							//�ݒ�l�ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 0;							//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

			SW16data_onset(0xff, 05);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			if(CSR_FLG_CNT == /*1 V01j*/2 &&		//�X���C�h����
				SEQ_020_SV & 0x0050){				//�E�C���h�E���o������
//				SEQ_020_SV & 0x0060){				//�E�C���h�E���o������
													//SW5
				SW56_dncara_disp(0xff, 7);			//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
													//SW6 �J��
				SW56_dncara_disp(16, 8);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();						//���i�̃O���t�B�b�N�Z�b�g
			}
			if(DAN_DAN_FLG != 0xff ||				//�E�B���h�E��ʂ܂Ŗ߂�����
				WINDOW_NO_BACK == 0 ){				//�i����ʂ֖߂�Ƃ��͂���Ȃ�
				return;
			}
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���̶݂��وʒu���Ǎ�
//			DAN_WIN_FLG = 0xff;

			CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g

//V01j			disp_stg_sel = E_kstg_scon;				//�i��[�X���C�h����]��
			WINDOW_NO = WINDOW_NO_BACK;				//�J��
			if (WINDOW_NO == 6) {					//V01j
				disp_stg_sel = E_kstg_scon;			//�i��[�X���C�h����]��
			}
			else if (WINDOW_NO == 7) {
				disp_stg_sel = E_kstg_bara;			//�i��[�o�����T���͒���]��
			}
			else if ( (WINDOW_NO == 8) || (WINDOW_NO == 9) ) {
				disp_stg_sel = E_kstg_daic;			//�i��[�_�C�N�b�V��������]��
			}
			else if ( (WINDOW_NO >= 12) || (WINDOW_NO <= 18) ) {
				disp_stg_sel = E_kstg_kana;			//�i��[�������^����]��
			}
			WIN_gamen_disp();						//����޳��ʕ\��

//			DAN_WIN_FLG = 0x00;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����

			CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = CSR_FLG_CNT_BACK;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;							//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

			G07_WIN_FLG = 0xff;
			break;
	}
}


/*
********************************************************************************
*  Module Name:		DISP_after
*  Function Name:	��ʕ\���̌㏈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
void	DISP_after(void)
{
	UNl		*adverwk;//test 2014
	UNl		verwk;//test 2014


	UNs		*bf_p, i, j;
	UNb		wk[8];
	UNs		xy_wk;
	UNs		ktop;

	GAMENn_SCR_COL = GAMENn_HEAD.scr_col;

	switch(GAMEN_NO) {
		default:
		case 2:			//���Y��ʁ@���^��{(���g�p)
		case 11:		//�ݒ��ʁ@�ް��ݒ�
		case 18:		//�ݒ��ʁ@�ް��ݒ�I�𒆌^
//2014/09/01		case 24:		//�ݒ��ʁ@н̨��޶с@NO/NC�ݒ�
//2014/09/01		case 25:		//�ݒ��ʁ@۰�ضс@17�`20�ݒ�
		case 27:		//�ݒ��ʁ@���ײݶѐݒ�
		case 42:		//���щ�ʁ@���x���B�ް��ݒ�
		case 46:		//���щ�ʁ@��߼�ݍ\���ް����
//V01j		case 47:		//���щ�ʁ@�޲����ݎ�������(��)
//V01j		case 48:		//���щ�ʁ@�޲����ݎ�������(�E)
//V01j		case 49:		//���щ�ʁ@���ݻ���͒���
//SIT4-MC		case 53:		//���щ�ʁ@���ײݎd�l�ݒ���
//2014/09/10		case 54:		//���щ�ʁ@�ް�۰�މ��
			break;

		case 1:			//���Y��ʁ@��{
			RULET_DISP_FLG = 0xff;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)
			SEISAN_DISP_FLG = 0xff;			//���Y�̍s���\��(00:�Ȃ��^FF:����)
			INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)

			RULET_GAMEN_INIT();				//ٰگĕ\���̏�����

			CSR_MOVE_OK_FLG = 0xff;			//���وړ��׸�(00:�ړ��^FF:�֎~)

//V06n			SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//���Y��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			break;

		case 3:			//���Y��ʁ@Ӱ��ݐݒ�
		case 28:		//�ݒ��ʁ@Ӱ��ݐݒ�
		case 6:			//���Y��ʁ@Ӱ��ݐݒ�6�`10		/* V01d */
		case 30:		//�ݒ��ʁ@Ӱ��ݐݒ�6�`10		/* V01d */
			CSR_FLG = 0;						//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;					//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;						//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;						//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 02);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			mmon_sel_chk();						//Ӱ��݂̕����I������

//V05f			fSV_DANSUU_SRV_BAK = 5;				//�����l
			SV_DANSUU_SRV_BAK = 0;				//�����l
			mmon_kaiten_chg();					//��]�����ɂ��ݒ�l �؊���

//			mmon_trans_get();					//��]�����ɂ���ް��̎擾
//
//			SV_TAIKIKAKU_SRV_BAK = SV_TAIKIKAKU_SRV;	//�ҋ@�p�̊i�[
//			SV_TAIKIPOS_SRV_BAK = SV_TAIKIPOS_SRV;		//�ҋ@�ʒu�̊i�[
//
//			SV_DANSUU_SRV_BAK = 5;				//�����l
//			mmon_tchk_disp();					//Ӱ��݉�ʗp���ð��ق�����&�\��

//V01d			if(GAMEN_NO == 3){		//���Y��ʁ@Ӱ��ݐݒ�
			if( (GAMEN_NO == 3) || (GAMEN_NO == 6) ){		//���Y��ʁ@Ӱ��ݐݒ�
				INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)

//V06n				SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//���Y��ʕ\��(1:�\����)
				SEQ_PAR_052 = 0;					//2016/04/22
				SEQ_PAR_054 = 0;					//2016/04/22

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//�@�\�I��3(���Y���l�ݒ�@1:�L)
					SV_CNT = 00;
//V01d					CSR_CNT = 00;
					CSR_CNT = 02;
				}
			}
			else{					//�ݒ��ʁ@Ӱ��ݐݒ�
//V06n				SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
				SEQ_PAR_052 = 0;					//2016/04/22
				SEQ_PAR_054 = 0;					//2016/04/22

				DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

				EJE_GAMEN_NON = 0;				//�G�W�F�N�^ �L
				if(00 == EJE_check()) {			//�G�W�F�N�^�L���`�F�b�N
					EJE_GAMEN_NON = 0xff;		//�G�W�F�N�^ ��
				}
				MIS_GAMEN_NON = 0;				//�~�X�t�B�[�h �L
				if(00 == MIS_check()){			//�~�X�t�B�[�h�L���`�F�b�N
					if ((SEQ_PAR_151 & cBIT8)==0) {		//�X���C�h�����ҋ@�@�\�L���`�F�b�N			SIT4-MC		2014/08/28
						MIS_GAMEN_NON = 0xff;	//�~�X�t�B�[�h ��
					}
				}
				ROT1_GAMEN_NON = 0;				//���[�^���J���P�`�W �L
				if( 00 == ROT1_check() ) {		//���[�^���J���P�`�W�L���`�F�b�N
					ROT1_GAMEN_NON = 0xff;		//���[�^���J���P�`�W ��
				}
				ROT2_GAMEN_NON = 0;				//���[�^���J���X�`�P�U �L
				if( 00 == ROT2_check() ) {		//���[�^���J���X�`�P�U�L���`�F�b�N
					ROT2_GAMEN_NON = 0xff;		//���[�^���J���X�`�P�U ��
				}

				ROT_GAMEN_NON = 0;				//���[�^���J�� �L
				if(ROT1_GAMEN_NON == 0xff) {	//���[�^���J���P�`�W ���@�H
					if(ROT2_GAMEN_NON == 0xff){	//���[�^���J���X�`�P�U ���@�H
						ROT_GAMEN_NON = 0xff;	//���[�^���J�� ��
					}
				}

				CAM_GAMEN_NON = 0;						//���ݸސݒ� �L
				if(EJE_GAMEN_NON == 0xff) {				//�G�W�F�N�^ ���@�H
					if(MIS_GAMEN_NON == 0xff){			//�~�X�t�B�[�h ���@�H
						if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
							CAM_GAMEN_NON = 0xff;		//���ݸސݒ� ��
							SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
							SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
							Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
						}
					}
				}

				if ( (GMN_PAR077 == 0) && (GMN_PAR079 != 1) ) {			//�J��Ԃ� or ���̈�				2014/09/10
													//�r�v�V��
					SW56_dncara_disp(0xff, 13);		//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
													//�r�v�V��
					SW56_dncara_disp(0xff, 14);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
				}
			}
			break;

		case 4:			//���Y��ʁ@����Ӱ���
		case 29:		//�ݒ��ʁ@����Ӱ���
			CSR_MOVE_OK_FLG = 0xff;			//���وړ��׸�(00:�ړ��^FF:�֎~)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			if(GAMEN_NO == 4){		//���Y��ʁ@����Ӱ���
				INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)
//V06n				SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_0;			//���Y��ʕ\��(1:�\����)
				SEQ_PAR_052 = 0;					//2016/04/22
				SEQ_PAR_054 = 0;					//2016/04/22

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//�@�\�I��3(���Y���l�ݒ�@1:�L)
					SV_CNT = 00;
					CSR_CNT = 00;
				}
			}
			else{					//�ݒ��ʁ@����Ӱ���
//				SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
				SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
				SEQ_PAR_052 = 0;					//2016/04/22
				SEQ_PAR_054 = 0;					//2016/04/22

				DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

				if(EJE_GAMEN_NON == 0xff) {				//�G�W�F�N�^ ���@�H
					if(MIS_GAMEN_NON == 0xff){			//�~�X�t�B�[�h ���@�H
						if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
							SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
							SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
							Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
						}
					}
				}

				if ( (GMN_PAR077 == 0) && (GMN_PAR079 != 1) ) {			//�J��Ԃ� or ���̈�				2014/09/10
													//�r�v�V��
					SW56_dncara_disp(0xff, 13);		//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
													//�r�v�V��
					SW56_dncara_disp(0xff, 14);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
				}
			}
			break;

		case 7:			//�i���ʁ@���^��{
			RULET_DISP_FLG = 0xff;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)
			SEISAN_DISP_FLG = 0xff;			//���Y�̍s���\��(00:�Ȃ��^FF:����)
			INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)

			RULET_GAMEN_INIT();				//ٰگĕ\���̏�����

			CSR_FLG = 0;

			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_1;			//�^�i���ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_1;			//�^�i���ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22
			break;

		case 8:			//�i���ʁ@���^��{		//V01r
			RULET_DISP_FLG = 0xff;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)
			SEISAN_DISP_FLG = 0xff;			//���Y�̍s���\��(00:�Ȃ��^FF:����)
			INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)

			RULET_GAMEN_INIT();				//ٰگĕ\���̏�����

			CSR_FLG = 0;

			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_1;			//�^�i���ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_1;			//�^�i���ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22
			break;

		case 12:		//�ݒ��ʁ@�і��̐ݒ�
		case 26:		//�ݒ��ʁ@۰�ضі��̓���
			NAME_CHG_FLG = 0;						//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;					//���̓J�E���^������

			SW16data_onset(0xff, 2);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;			//���݂̃J�[�\���ʒu�J�E���g
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//�ύX�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();							//�r�v�f�[�^���@�\��

			DATA_svsw(SEQ_PAR_101,BIT_0);			//�ް��ݒ�OK(1:OK)
//V06n			SEQ_PAR_051 = BIT_2;					//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22
			break;

		case 13:		//�ݒ��ʁ@����ݽ ���
			CSR_FLG = 0;					//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;					//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;					//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 2);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)
			break;

		case 14:		//�ݒ��ʁ@�@�\�I��
			CSR_FLG = 0;					//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;					//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;					//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)
			break;

		case 15:		//�ݒ��ʁ@�^�ް��Ǘ�
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

			MLD_100_FLG = 0;					//�^�Ǘ� 1�`10���L��
			if( SEQ_025_SV & BIT_15 ) {			//�^�ް�1�`100���L���@�H
				MLD_100_FLG = 0xaa;				//�^�Ǘ� 1�`100���L��
				if ( SEQ_026_SV & BIT_0 ) {		//�^�ް�101�`200���L���@�H		V06n
					MLD_100_FLG = 0xbb;			//�^�Ǘ� 1�`200���L��
				}
			}
												//�J�[�\���\���ʒu����
			if(CSR_POS_G15 == 0xff){			//�^�f�[�^�Ǘ���ʂ̃J�[�\���\���ʒu�͌��݂̌^�f�[�^�̏ꏊ
				CSR_FLG = 5;					//�J�[�\���\���ʒu�w��
				i = PV_MLDNO1_F1;				//���݂̌^�ԍ�

//V06n				if(MLD_100_FLG != 0xaa){		//�^�Ǘ� 1�`100���L���H
				if(MLD_100_FLG == 0){			//�^�Ǘ� 1�`10���L���H
					if( i > 10 ) {
						i = 1;
					}
				}
				else if(MLD_100_FLG == 0xaa) {	//�^�Ǘ� 1�`100���L���H		V06n
					if( i > 100 || i == 0 ) {
						i = 1;
					}
				}
				else if(MLD_100_FLG == 0xbb) {	//�^�Ǘ� 1�`200���L���H		V06n
					if( i > 200 || i == 0 ) {
						i = 1;
					}
				}
				j = (i % 10);
				i /= 10;
				if(j == 0){
					j = 10;
					i -= 1;
				}
				CSR_FLG_CNT = (j << 1);
				MLD_100_GNO = i;
			}
			else if(CSR_POS_G15 == 0xaa){
				CSR_FLG = 5;					//�J�[�\���\���ʒu�w��
				j = (PV_SEARCH_C15 % 10);		//�^�ԍ������i���o�[�Ǎ�
				if(j == 0){
					j = 10;
				}
				CSR_FLG_CNT = (j << 1);
			}
			else if(CSR_POS_G15 == 0x55){		//���̓o�^��ʂ���߂��ė������p
				CSR_FLG = 5;					//�J�[�\���\���ʒu�w��
				j = (PV_MLDNO1_F0 % 10);
				if(j == 0){
					j = 10;
				}
				CSR_FLG_CNT = (j << 1);
			}
			else{
				CSR_FLG = 5;				//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = 2;			//�J�[�\���ԍ��Z�b�g
			}

											//MLD100 �^�Ǘ��ԍ��\���f�[�^�쐬
			i = (MLD_100_GNO * 10);
			i ++;
			ktop = i;						//V06p(INS)
			PV_MLNO01_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO02_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO03_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO04_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO05_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO06_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO07_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO08_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO09_C15 = i++;			//�^�Ǘ������f�[�^
			PV_MLNO10_C15 = i;				//�^�Ǘ������f�[�^


			mot_type_SWset(ktop);			//���[�V����TYPE�pSW�Z�b�g


			PV_MLDMES_C1 = 0;
			SWchg_disp();					//�r�v�f�[�^���@�\��


			if(MLD_100_GNO == 0){
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

//V06n				if(MLD_100_FLG != 0xaa){		//�^�Ǘ� 1�`100���L���H
				if(MLD_100_FLG == 0){				//�^�Ǘ� 1�`100���L���H
					if ( (SEQ_PAR_151 & cBIT3) == 0 ) {		//�T���v���^�L���H		2014/04/17
						SW56_dncara_disp(0xff, 3);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
						SW56_dncara_disp(0xff, 11);			//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					}
				}
			}
//V06n			else if(MLD_100_GNO == 9){
			else if ( ( (MLD_100_FLG == 0xaa) && (MLD_100_GNO == 9) ) || 
					  ( (MLD_100_FLG == 0xbb) && (MLD_100_GNO ==19) ) ) {
				if ( (SEQ_PAR_151 & cBIT3) == 0 ) {			//�T���v���^�L���H		2014/04/17
					SW56_dncara_disp(0xff, 3);				//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_dncara_disp(0xff, 11);				//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				}
			}
			else if (MLD_100_GNO == 21) {					//2014/04/17
				SW56_dncara_disp(0xff, 3);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);					//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
			}
			Under_grph();						//���i�̃O���t�B�b�N�Z�b�g
			break;

		case 16:		//�ݒ��ʁ@�^�ް����̐ݒ�
		case 23:		//�ݒ��ʁ@�Ӗ��̓��͉��
			NAME_CHG_FLG = 0;				//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;			//���̓J�E���^������

			CSR_FLG = 5;					//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 2;				//�J�[�\���ԍ��Z�b�g

			SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)
			break;

		case 17:		//�ݒ��ʁ@�ް��ݒ蒆�^
			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;		//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			if(0==(SEQ_PAR_107 & BIT_0)){		//�@�\�I��1(�^�ް��Ǘ��@1:�L)
												//�r�v�R��
				SW56_dncara_disp(0xff, 03);		//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
												//�r�v�R��
				SW56_dncara_disp(0xff, 11);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
			}

			SEL_GAMEN_NON = 0;
			i = SEQ_019_SV & 0xeaa0;
			i |= SEQ_018_SV & BIT_7;			//���ײݐݒ�(1=�L)
			i |= SEQ_020_SV & BIT_0;			//�޲����݈��͒����I��(1=�L)
/**************	V03a ��^����߂U�I��ǉ�	*********************/
//			i |= SEQ_021_SV & BIT_1;
/***************************************************************************/

//2014/08/29  SIT4-MC
			i = GMN_PAR068;						//�J���o�͎������Z�@�\�L��		�Ƃ肠�������ײ݂͖����Ƃ���B

			if( i == 0 ){
				SEL_GAMEN_NON = 0xff;
				SW56_dncara_disp(0xff, 1);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 9);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();					//���i�̃O���t�B�b�N�Z�b�g
			}
			MLD_100_GNO = 0;					//�^�Ǘ���ʔԍ�������
			MLD_100_FLG = 0;					//�^�Ǘ��t���O������
			break;

		case 19:		//�ݒ��ʁ@��ު���^�������ѐݒ�
			GAMEN_NO_CAM = 19;			//�O��f�[�^�L��

			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

			if(MIS_GAMEN_NON == 0xff){		//�~�X�t�B�[�h ���@�H
				SW56_dncara_disp(0xff, 03);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
				SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 20:		//�ݒ��ʁ@н̨��޶ѐݒ�
			GAMEN_NO_CAM = 20;

			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//�G�W�F�N�^ ���@�H
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
				SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 24:		//�ݒ��ʁ@۰�ض�1�`8�ѐݒ�i�i�p�L�j			//2014/09/01
			GAMEN_NO_CAM = 24;
			goto	rot_cam_000;
		case 21:		//�ݒ��ʁ@۰�ض�1�`8�ѐݒ�
			GAMEN_NO_CAM = 21;
rot_cam_000:
			NAME_CHG_FLG = 0;			//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;		//���̓J�E���^������

			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//�ύX�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();								//�r�v�f�[�^���@�\��

			DATA_svsw(SEQ_PAR_101,BIT_0);				//�ް��ݒ�OK(1:OK)

//V06n			SEQ_PAR_051 = BIT_2;						//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			if(EJE_GAMEN_NON == 0xff) {		//�G�W�F�N�^ ���@�H
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(MIS_GAMEN_NON == 0xff){		//�~�X�t�B�[�h ���@�H
				SW56_dncara_disp(0xff, 03);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 25:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�i�i�p�L�j				//2014/09/01
			GAMEN_NO_CAM = 25;
			goto	rot_cam_100;
		case 22:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�
			GAMEN_NO_CAM = 22;
rot_cam_100:
			NAME_CHG_FLG = 0;			//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;		//���̓J�E���^������

			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			CSR_FLG_CNT_BAK = CSR_FLG_CNT;
			SV_FLG_CNT_BAK = SV_FLG_CNT;
			SW_FLG_CNT_BAK = SW_FLG_CNT;

			bf_p = Camcsr_Name_Tbl[CAM_NAME_NO];	//�ύX�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C1[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_TblSV[CAM_NAME_NO];	//�J�����̔ԍ��Ǎ�
			memcpy_word(&PV_CAMNAM_C2[0], bf_p, 4);	//�J�����̂����Ă���

			bf_p = Camcsr_Name_Tbl1[CAM_NAME_NO];
			PV_CAMNA1_C1 = *bf_p;

			SWchg_disp();								//�r�v�f�[�^���@�\��

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

//V06n			SEQ_PAR_051 = BIT_2;				//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			if(EJE_GAMEN_NON == 0xff) {		//�G�W�F�N�^ ���@�H
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(MIS_GAMEN_NON == 0xff){		//�~�X�t�B�[�h ���@�H
				SW56_dncara_disp(0xff, 03);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 31:		//���ѐݒ�@���
			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			//����ް�ޮ݁F�\����=4(ASCII�ް�)
			wk[0] = E_CPUC_VER1;								//CPU-C VER. No.
			wk[1] = E_CPUC_VER2;								//CPU-C VER. No.
			wk[2] = E_CPUC_VER3;								//CPU-C VER. No.
			wk[3] = E_CPUC_VER4;								//CPU-C VER. No.
			memcpy_word(&PV_GMNVER_A1[0], (UNs *)&wk[0], 2);	//����ް�ޮ݂��߰

			//����ץ�ް�ޮ݁F�\����=2(ASCII�ް�)(ROM�@���ݽ����Ұ��ɂČ���)
			//PV_SYSVER_A1       .SRES        2           ; �V�X�p���@�o�[�W����
			memset_word(&PV_SYSVER_A1, E_AS_SPSP, 1);

			//CPU-A C/B�ް�ޮ݁F�\����=6(ASCII�ް�)
			//PV_CBAVER_A1       .SRES        6           ; �b�o�t�|�`�@�o�[�W����
			wk[0] = PVP_CB_A_VER[0];							//CPU-A VER. No.
			wk[1] = PVP_CB_A_VER[1];
			wk[2] = PVP_CB_A_VER[2];
			wk[3] = PVP_CB_A_VER[3];
			wk[4] = PVP_CB_A_VER[4];
			wk[5] = PVP_CB_A_VER[5];
			memcpy_word(&PV_CBAVER_A1[0], (UNs *)&wk[0], 3);	//����ް�ޮ݂��߰

			//CPU-B C/B�ް�ޮ݁F�\����=6(ASCII�ް�)
			//PV_CBBVER_A1       .SRES        6           ; �b�o�t�|�a�@�o�[�W����
			bf_p = (UNs *)&PVP_CB_B_VER[0];					//SIT4-MC
			bf_p -= (UNl)&dpram_top/2; 
			bf_p += (UNl)&dpramB_top/2; 
			wk[0] = *bf_p;									//CPU-B VER. No.
			bf_p++;
			wk[1] = *bf_p;
			bf_p++;
			wk[2] = *bf_p;
			bf_p++;
			wk[3] = *bf_p;
			bf_p++;
			wk[4] = *bf_p;
			bf_p++;
			wk[5] = *bf_p;
			memcpy_word(&PV_CBBVER_A1[0], (UNs *)&wk[0], 3);	//����ް�ޮ݂��߰

			//��߼�ݥ�ް�ޮ݁F�\����=2(HEX�ް�)
			PV_OPCVER_A1[0] = OP_VER;								//Option Ver

			//�����l�ް�ޮ݁F�\����=2(HEX�ް�)		V06
			bf_p = &SV_SEQDT1_A91_INI;
			bf_p += INIT_DAT_OFS/2;
			PV0_DEFULT_VER1 = *bf_p;

			//����ۯ��ް�ޮ݁F�\����=2(HEX�ް�)		V06
			bf_p = &SV_INTER_VER1;
			bf_p += INTR_DAT_OFS/2;
			PV0_INTER_VER1 = *bf_p;

			//�������ް�ޮݷ�׸��F�\����=1(ASCII�ް�)
			PV0_PAR_A_CHAR = PVP_PAR_A_CHAR << 8;
//SIT4-MC			PV0_PAR_B_CHAR = PVP_PAR_B_CHAR << 8;
			bf_p = (UNs *)&PVP_PAR_B_CHAR;
			bf_p -= (UNl)&dpram_top/2; 
			bf_p += (UNl)&dpramB_top/2; 
			PV0_PAR_B_CHAR = *bf_p << 8;

			PV0_TBL_A_CHAR = PVP_TBL_A_CHAR << 8;
//SIT4-MC			PV0_TBL_B_CHAR = PVP_TBL_B_CHAR << 8;
			bf_p = (UNs *)&PVP_TBL_B_CHAR;
			bf_p -= (UNl)&dpram_top/2; 
			bf_p += (UNl)&dpramB_top/2; 
			PV0_TBL_B_CHAR = *bf_p << 8;

			PV0_SEQ_VER2 = SEQ_PAR_198 << 8;

//V06			PV0_DEFULT_VER2 = SV_SEQDT2_A91_INI << 8;
			bf_p = &SV_SEQDT2_A91_INI;
			bf_p += INIT_DAT_OFS/2;
			PV0_DEFULT_VER2 = *bf_p << 8;

//V06			PV0_INTER_VER2 = SV_INTER_VER2 << 8;
			bf_p = &SV_INTER_VER2;
			bf_p += INTR_DAT_OFS/2;
			PV0_INTER_VER2 = *bf_p << 8;

			//��߼��ET1�ް�ޮ݁F�\����=4(ASCII�ް�)				//V05
			if(MEM_ARI == 0xA5) {							//OP��(OK):A5H
				//wk[0] = ET1_VER[0];							//CPU-B VER. No.
				//wk[1] = ET1_VER[1];
				//wk[2] = ET1_VER[2];
				//wk[3] = ET1_VER[3];
				
				adverwk=(UNl *) ET1_VER;
				verwk=*adverwk;
				wk[3]= (verwk&0xff);	//
				verwk=verwk>>8;			//
				wk[2]= (verwk&0xff);
				verwk=verwk>>8;
				wk[1]= (verwk&0xff);
				verwk=verwk>>8;
				wk[0]= (verwk&0xff);

				
			}
			else{
				wk[0] = 0x20;							//CPU-B VER. No.
				wk[1] = 0x20;
				wk[2] = 0x20;
				wk[3] = 0x20;
			}
			memcpy_word(&PV_ET1VER_A1[0], (UNs *)&wk[0], 2);	//����ް�ޮ݂��߰

			break;

		case 38:		//���ѐݒ�@C/B���ђ萔			2016/02/25
		case 51:		//���ѐݒ�@C/B���ђ萔2		2016/02/25
			CSR_CNT = 00;
			SV_CNT = 00;
			SW_CNT = 00;
			break;


		case 32:		//���ѐݒ�@�d�l�ݒ�1
		case 33:		//���ѐݒ�@�d�l�ݒ�2
		case 34:		//���ѐݒ�@�d�l�ݒ�3
		case 35:		//���ѐݒ�@�d�l�ݒ�4
		case 36:		//���ѐݒ�@�d�l�ݒ�5
		case 37:		//���ѐݒ�@�d�l�ݒ�6
//2016/02/25		case 38:		//���ѐݒ�@C/B���ђ萔
		case 39:		//���ѐݒ�@�������Ұ�1
		case 40:		//���ѐݒ�@�������Ұ�2
		case 41:		//���ѐݒ�@���Ѷѐݒ�
		case 43:		//���ѐݒ�@�����ѥ��ϐݒ�
		case 44:		//���ѐݒ�@�׏d�v�ݒ�
		case 45:		//���ѐݒ�@�ײ�ގ����ݒ�
		case 47:		//���щ�ʁ@�޲����ݎ�������(��)	V01j
		case 48:		//���щ�ʁ@�޲����ݎ�������(�E)	V01j
		case 49:		//���щ�ʁ@���͒��ߐݒ�			V01j
		case 50:		//���ѐݒ�@�ޯ������ް��ݒ�
//2016/02/25		case 51:		//���ѐݒ�@C/B���ђ萔2
		case 55:		//���щ�ʁ@�d�l�ݒ�7
		case 56:		//���щ�ʁ@�d�l�ݒ�8
		case 57:		//���ѐݒ�@�������Ұ�3
		case 58:		//���ѐݒ�@�������Ұ�4
		case 59:		//���ѐݒ�@�������Ұ�5
		case 60:		//���ѐݒ�@�������Ұ�6
		case 61:		//���ѐݒ�@�������Ұ�7		//V01v

		case 62:		//���ѐݒ�@�������Ұ�8		//2012-03-28 copy,h2w V05
		case 63:		//���ѐݒ�@�������Ұ�9		//2012-03-28 copy,h2w V05
		case 64:		//���ѐݒ�@�������Ұ�10	//2012-03-28 copy,h2w V05
		case 103:		//���ѐݒ�@�������Ұ�B		//2012-03-28 copy,h2w V06
		case 106:		//���щ�ʁ@�d�l�ݒ�9		//V06m
		case 107:		//���щ�ʁ@�d�l�ݒ�10		//V06m
			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			DATA_svsw(SEQ_PAR_101,BIT_1);	//���ѐݒ�OK(1:OK)
			break;

		case 52:		//���ѐݒ�@�ް�������
			NAME_CHG_FLG = 0;				//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;			//���̓J�E���^������

			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)
//			if(MLD_100_CARD_FLG != 0xaa){	//�O���������L��H
//											//SW5��
				SW56_dncara_disp(0xff, 7);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
//			}
			break;

		/* V01d */
		case 68:		//�ݒ��ʁ@н̨��޶ѐݒ�5�`8
			GAMEN_NO_CAM = 68;

			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//�G�W�F�N�^ ���@�H
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
				SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 66:		//���Y��ʁ@�g�����h			//V01z
		case 104:		//���Y��ʁ@�g�����h			//V06l
			SW16data_onset(0xff, 3);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			break;
		case 67:		//���Y��ʁ@�T���v�����O		//V01z
		case 105:		//���Y��ʁ@�T���v�����O		//V06l
			SW16data_onset(0xff, 2);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 9:			//���Y��ʁ@�T���v�����O�g�`	//V05o
			SW16data_onset(0xff, 4);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			break;
		case 10:		//���Y��ʁ@�h�����h�g�`		//V05o
			SW16data_onset(0xff, 9);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 101:		//�f�[�^�ݒ��ʁ@���U�@�\�ݒ�	//V05r
			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 9);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)

//V06n			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			if(EJE_GAMEN_NON == 0xff) {		//�G�W�F�N�^ ���@�H
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(MIS_GAMEN_NON == 0xff){		//�~�X�t�B�[�h ���@�H
				SW56_dncara_disp(0xff, 03);	//SW56���i��׸���SW�̈�֊i�[(SW56��i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			if(ROT_GAMEN_NON == 0xff) {		//���[�^���J�� ���@�H
				SW56_dncara_disp(0xff, 4);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff,12);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				Under_grph();				//���i�̃O���t�B�b�N�Z�b�g
			}
			break;

		case 102:		//���Y��ʁ@�d�̓��j�^	//V06
			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 9);					//SW1�`6�̔��]�w����s��(������ް�,SW�ʒu)

			break;

		case 109:		//�ް��ݒ��ʁ@�яo�͎������Z���				2014/08/28	SIT4-MC
			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			break;

		case 53:		//�ް��ݒ��ʁ@�ײ�ގ����ҋ@�@�\���			2014/08/28	SIT4-MC
			GAMEN_NO_CAM = 53;

			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 5);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 6);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			SEQ_PAR_051 = (SEQ_PAR_051 & 0xFFE0) | BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			SEQ_PAR_052 = 0;					//2016/04/22
			SEQ_PAR_054 = 0;					//2016/04/22

			DATA_svsw(SEQ_PAR_101,BIT_0);		//�ް��ݒ�OK(1:OK)

			break;

		case 54:		//�J��Ԃ��^���̈� �ݒ���			2014/09/10
			SW16data_onset(0xff, 9);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;
	}

	/*--- ��ʋ��� 2016/04/25 ---*/
	if( SEQ_025_SV & BIT_15 ) {			//�^�ް�1�`100���L���@�H
		MLD_100_FLG = 0xaa;				//�^�Ǘ� 1�`100���L��
		if ( SEQ_026_SV & BIT_0 ) {		//�^�ް�101�`200���L���@�H		V06n
			MLD_100_FLG = 0xbb;			//�^�Ǘ� 1�`200���L��
		}
	}
	else {
		MLD_100_FLG = 0;				//�^�Ǘ� 1�`10���L��
	}
}


/*
********************************************************************************
*  Module Name:		WIN_disp_after
*  Function Name:	����޳��ʕ\���̌㏈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
void	WIN_disp_after(void)
{
	UNs		i;

	switch(WINDOW_NO) {
		default:
//V01r		case 1:			//���Y��ʁ@���Y�ݒ�
//V01r		case 8:			//�i���ʁ@�޲����ݒ���
//V01r		case 9:			//�i���ʁ@�޲����݈��͒���
//V01j		case 12:		//�i���ʁ@�ï�����
//V01r		case 13:		//�i���ʁ@�޲����ݑ���
//V01r		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
//V01r		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
//V01r		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
//V01r		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
//V01r		case 18:		//�i���ʁ@MB�I�𑀍�
			break;

		case 1:			//���Y��ʁ@���Y�ݒ�				//V01r
		case 8:			//�i���ʁ@�޲����ݒ���			//V01r
		case 9:			//�i���ʁ@�޲����݈��͒���		//V01r
//2016/04/22		case 13:		//�i���ʁ@�޲����ݑ���			//V01r
//2016/04/22		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���			//V01r
//2016/04/22		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F		//V01r
//2016/04/22		case 16:		//�i���ʁ@�޲����ݒ��ߑ���		//V01r
//2016/04/22		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F	//V01r
//2016/04/22		case 18:		//�i���ʁ@MB�I�𑀍�				//V01r
		case 02:		//���Y��ʁ@�P�x�ݒ�
		case 03:		//���Y��ʁ@�޲��ݽ�\��
		case 04:		//���Y��ʁ@���ݽ����
		case 05:		//���Y��ʁ@���Y�ݒ蒆�^
		case 07:		//�i���ʁ@���ݻ���͒���
		case 10:		//�i���ʁ@�޲��ݽ�\��
		case 11:		//�i���ʁ@���ݽ����
		case 19:		//���Y��ʁ@���Y�ݒ�2
		case 21:		//���Y��ʁ@��������WIN				//V06
			RULET_DISP_FLG = 0x55;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)
			break;

		case 06:		//�i���ʁ@�ײ�ޒ���
			RULET_DISP_FLG = 0x55;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)

			i = SEQ_019_SV & 0x0550;		//��^�N�����p����h���܂ł̑I�����ڃ`�F�b�N
			i |= SEQ_020_SV & BIT_1;
			SW14_DISP7_DANNON = i;
			break;

		case 12:	/*V01j*/	//�i���ʁ@�ï�����
			RULET_DISP_FLG = 0x55;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)	V01r
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)						V01r

			ADC_STEP_NO_LAST[0] = 0xffff;
			ADC_STEP_NO_LAST[1] = 0xffff;
			ADC_STEP_NO_LAST[2] = 0xffff;
			ADC_STEP_NO_LAST[3] = 0xffff;

			ADC_NEXTNAME_SET();				//2016/04/22
			break;

		case 13:		//�i���ʁ@�޲����ݑ���			//2016/04/22
		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���			//2016/04/22
		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F		//2016/04/22
		case 16:		//�i���ʁ@�޲����ݒ��ߑ���		//2016/04/22
		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F	//2016/04/22
		case 18:		//�i���ʁ@MB�I�𑀍�				//2016/04/22
			ADC_NEXTNAME_SET();
			break;

	}
}


/*
********************************************************************************
*  Module Name:		WIN_disp_after2(��:WIN_DISP_AFTER_A)
*  Function Name:	����޳��ʕ\���̌㏈��2
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
void	WIN_disp_after2(void)
{
	UNs		*Dst_p, dot_d, i;
	UNi		cnt;

	switch(WINDOW_NO) {
		default:
		case 1:			//���Y��ʁ@���Y�ݒ�
//V01j		case 8:			//�i���ʁ@�޲����ݒ���
//V01j		case 9:			//�i���ʁ@�޲����݈��͒���
//V01j		case 12:		//�i���ʁ@�ï�����
//V01j		case 13:		//�i���ʁ@�޲����ݑ���
//V01j		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
//V01j		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
//V01j		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
//V01j		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
//V01j		case 18:		//�i���ʁ@MB�I�𑀍�
			break;

		case 2:			//���Y��ʁ@�P�x�ݒ�
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 3:			//���Y��ʁ@�޲��ݽ�\��
		case 10:		//�i���ʁ@�޲��ݽ�\��
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 4:			//���Y��ʁ@���ݽ����
			if(SEQ_025_SV & BIT_14) {			//shima
				SW56_dncara_disp(64, 8);						//SW56���i��׸���SW�̈�֊i�[
			}
		case 11:		//�i���ʁ@���ݽ����
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 5:			//���Y��ʁ@���Y�ݒ蒆�^
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {		//�@�\�I��3(���Y���l�ݒ�@1:�L)
				SV_CNT = 00;
				for(i=0 ; i < 12 ; i++){			//���Y�ݒ�֎~��������r�u�J�E���g�l�`�w���O�ɂ���
													//��������Ȃ��Ɠ�񉟂��Ȃ��ƉE�Ɉړ����Ȃ�
					CSR_buff[i].SV_MAX = 0x00;		//�ݒ�lð��ٌ�
				}
			}
//V01l			if(00 == EJE_check()) {					//�G�W�F�N�^�L���`�F�b�N
			if( (00 == EJE_check() ) &&
					(00 == SEQ_016_SV & BIT_2) ) {	//�G�W�F�N�^�L���`�F�b�N
				CSR_CNT = 00;						//�G�W�F�N�^ ��
			}
			SW16data_onset(0xff, 02);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 6:			//�i���ʁ@�ײ�ޒ���
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//�@�\�I��4(�i�搔�l�ݒ�@1:�L)
				SV_CNT = 00;
			}
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 7:			//�i���ʁ@���ݻ���͒���
		case 8:			//�i���ʁ@�޲����ݒ���			/* V01j */
		case 9:			//�i���ʁ@�޲����݈��͒���		/* V01j */
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//�@�\�I��4(�i�搔�l�ݒ�@1:�L)
				SV_CNT = 00;
			}
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 12:		//�i���ʁ@�ï�����				/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 13:		//�i���ʁ@�޲����ݑ���			/* V01j */
		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���			/* V01j */
		case 16:		//�i���ʁ@�޲����ݒ��ߑ���		/* V01j */
		case 18:		//�i���ʁ@MB�I�𑀍�				/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			ADC_SW2_DISP();
			break;

		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F		/* V01j */
		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F	/* V01j */
			ADC_GRPH_DISP();
			ADC_SW56UP_DISP();
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//�@�\�I��4(�i�搔�l�ݒ�@1:�L)
				SV_CNT = 00;
			}
			ADC_SW2_DISP();
			break;

		case 19:		//���Y��ʁ@���Y�ݒ�2
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {		//�@�\�I��3(���Y���l�ݒ�@1:�L)
				SV_CNT = 00;
			}
//V01l			if(00 == MIS_check()){					//�~�X�t�B�[�h�L���`�F�b�N
			if( (00 == MIS_check() ) &&
					(00 == SEQ_016_SV & BIT_2) ) {	//�~�X�t�B�[�h�L���`�F�b�N
				CSR_CNT = 00;						//�~�X�t�B�[�h ��
			}
			SW16data_onset(0xff, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 20:		//���Y��ʁ@�␳���j�^		/* V01w */
//2016/02/26			if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//�@�\�I��3(���Y���l�ݒ�@1:�L)		//V05g
			if( 00 == (SEQ_PAR_151 & BIT_5) ) {	//�␳���j�^���͋���
				CSR_CNT = 00;
				SV_CNT = 00;
				SW_CNT = 00;
			}
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xFF, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 22:		//�f�[�^�ݒ��ʁ@���Ēl�C��	/* V06b */
			SW16data_onset(0xff, 9);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 23:		//���Y��ʁ@���Y�Ǘ�		/* V06c */
		case 51:		//���Y��ʁ@��ƊJ�n0		/* V06c */
		case 52:		//���Y��ʁ@��ƊJ�n1		/* V06c */
		case 53:		//���Y��ʁ@��ƊJ�n2		/* V06c */
		case 54:		//���Y��ʁ@��ƊJ�n3		/* V06c */
		case 55:		//���Y��ʁ@��ƊJ�n4		/* V06c */
		case 56:		//���Y��ʁ@��ƊJ�n5		/* V06c */
		case 57:		//���Y��ʁ@��ƊJ�n6		/* V06c */
		case 58:		//���Y��ʁ@��ƏI��0		/* V06c */
			SW16data_onset(0xff, 3);		//�r�v�R�̔��]�w����s��(������ް�,SW�ʒu)
			break;

	}

	if(WINDOW_NO < 6 || (WINDOW_NO != 20 && WINDOW_NO >= 10) ){	//�i���E�C���h�E�H
		Dst_p = &LCD_WORK1[6][0][0];				//����ʃE�C���h�E�̏�i�̘g������
		dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
		cnt = E_line;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}
	}
	else{
		Dst_p = &LCD_WORK1[6][0][0];				//����ʃE�C���h�E�̏�i�̘g������
		dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
		cnt = 23;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}

		Dst_p = &LCD_WORK1[6][0][22];				//�i���E�C���h�E�̏c�g������
		dot_d = BIT_0;								//�h�b�g�p�^�[���Z�b�g
		cnt = 16*7;
		while(cnt--) {
			*Dst_p |= dot_d;
			Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
		}
	}
}


/*
********************************************************************************
*  Module Name:		WIN_DISP_after_csr
*  Function Name:	��ʕ\���̌㏈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2016/04/22
********************************************************************************
*/
void	WIN_DISP_after_csr(void)
{
	switch(WINDOW_NO) {
		default:
			break;

		case 12:			//�X�e�b�v���j�^���
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0x8100;
			break;

		case 13:			//�_�C�N�b�V����������
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0x8200;
			break;

		case 14:			//�X���C�h���ߑ�����
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0x8400;
			break;

		case 15:			//�X���C�h�������ߊm�F���
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0x8800;
			break;

		case 16:			//�_�C�N�b�V�������ߑ�����
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0x9000;
			break;

		case 17:			//�_�C�N�b�V�����������ߊm�F���
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0xa000;
			break;

		case 18:			//�l�a�I�𑀍���
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = 0;
			SEQ_PAR_054 = 0xc000;
			break;

		case 20:			//
			SEQ_PAR_051 = BIT_1;
			SEQ_PAR_052 = BIT_0;
			SEQ_PAR_054 = 0;
			break;
	}
}


/*
********************************************************************************
*  Module Name:		Alltbl_set
*  Function Name:	���ð��ق̍쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
void	Alltbl_set(void)
{
CSR_TBL_TDEF	*csr_tp, *csr_p, *d1_p;
SV_TBL_TDEF		*sv_tp, *sv_p, *d2_p;
PV_TBL_TDEF		*pv_tp, *pv_p, *d3_p;
SW_TBL_TDEF		*sw_tp, *sw_p, *d4_p;
UNl		cnt, i;


	csr_tp = CSTBL_Adr_tbl[GAMEN_NO];				//�e��ʂ̏��ð��ق̱��ڽ���擾
	cnt = *CSCOUNT_Adr_tbl[GAMEN_NO];				//�J�[�\���J�E���^
	CSR_CNT1 = CSR_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d1_p = &CSR_buff[i];						//�i�[�|�C���^�Z�b�g
		csr_p = &csr_tp[i];							//�i�[�|�C���^�Z�b�g

		d1_p->XY_POS = csr_p->XY_POS;				//���ق�X,Y��
		d1_p->DATA_NO = csr_p->DATA_NO;				//���َ�ʔԍ�
		d1_p->SV_MAX = csr_p->SV_MAX;				//�ݒ�lð��ٌ�
		d1_p->SW_MAX = csr_p->SW_MAX;				//SWð��ٌ�
		d1_p->CARA_NO = csr_p->CARA_NO;				//���ٕ\����׎�ʁi���g�p�j
		d1_p->MOVE_NO = csr_p->MOVE_NO;				//��ʈړ��ԍ�
		d1_p->TOK_NO = csr_p->TOK_NO;				//����ԍ�(B0:���ٖ���)
		d1_p->YOBI1 = csr_p->YOBI1;					//�\���P
		d1_p->YOBI2 = csr_p->YOBI2;					//�\���Q
		d1_p->SW56_UP = csr_p->SW56_UP;				//SW56��i��׸�
		d1_p->SW5_DN = csr_p->SW5_DN;				//SW5���i��׸�
		d1_p->SW6_DN = csr_p->SW6_DN;				//SW6���i��׸�
		d1_p->SW5_SUB = csr_p->SW5_SUB;				//SW5�ް������ԍ�
		d1_p->SW6_SUB = csr_p->SW6_SUB;				//SW6�ް������ԍ�
		d1_p->YOBI3 = csr_p->YOBI3;					//�\���R
		d1_p->AKI = csr_p->AKI;						//��
		i++;
	}

	sv_tp = SVTBL_Adr_tbl[GAMEN_NO];
	cnt = *SVCOUNT_Adr_tbl[GAMEN_NO];				//�J�[�\���J�E���^
	SV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d2_p = &SV_buff[i];							//�i�[�|�C���^�Z�b�g
		sv_p = &sv_tp[i];							//�i�[�|�C���^�Z�b�g

		d2_p->XY_POS = sv_p->XY_POS;				//���ق�X,Y��
		d2_p->AKI = sv_p->AKI;						//��
		d2_p->DATA_ADR = sv_p->DATA_ADR;			//�ް��i�[���ڽ
		d2_p->SUB_NO = sv_p->SUB_NO;				//���ٰ�ݔԍ�
		d2_p->GRP_NO = sv_p->GRP_NO;				//��ٰ�ߔԍ�
		d2_p->TOK_FLG = sv_p->TOK_FLG;				//�����׸�
		d2_p->BYTE_NO = sv_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d2_p->TEN_POS = sv_p->TEN_POS;				//�����_�̈ʒu
		d2_p->CSR_NO = sv_p->CSR_NO;				//���ٔF���ԍ�
		d2_p->DSP_NO = sv_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
		d2_p->SAVE_NO = sv_p->SAVE_NO;				//�i�[�׸�
		d2_p->YOBI_NO = sv_p->YOBI_NO;				//�\��
		d2_p->AKI2 = sv_p->AKI2;					//��
		i++;
	}

	pv_tp = PVTBL_Adr_tbl[GAMEN_NO];
	cnt = *PVCOUNT_Adr_tbl[GAMEN_NO];				//�J�[�\���J�E���^
	PV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d3_p = &PV_buff[i];							//�i�[�|�C���^�Z�b�g
		pv_p = &pv_tp[i];							//�i�[�|�C���^�Z�b�g

		d3_p->XY_POS = pv_p->XY_POS;				//���ق�X,Y��
		d3_p->AKI = pv_p->AKI;						//��
		d3_p->DATA_ADR = pv_p->DATA_ADR;			//�ް��i�[���ڽ
		d3_p->SUB_NO = pv_p->SUB_NO;				//���ٰ�ݔԍ�
		d3_p->GRP_NO = pv_p->GRP_NO;				//��ٰ�ߔԍ�
		d3_p->TOK_FLG = pv_p->TOK_FLG;				//�����׸�
		d3_p->BYTE_NO = pv_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d3_p->TEN_POS = pv_p->TEN_POS;				//�����_�̈ʒu
		d3_p->YOBI1 = pv_p->YOBI1;					//�\���P
		d3_p->YOBI2 = pv_p->YOBI2;					//�\���Q
		d3_p->AKI2 = pv_p->AKI2;					//��
		i++;
	}

	sw_tp = SWTBL_Adr_tbl[GAMEN_NO];
	cnt = *SWCOUNT_Adr_tbl[GAMEN_NO];				//�J�[�\���J�E���^
	SW_CNT1 = SW_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d4_p = &SW_buff[i];							//�i�[�|�C���^�Z�b�g
		sw_p = &sw_tp[i];							//�i�[�|�C���^�Z�b�g

		d4_p->XY_POS = sw_p->XY_POS;				//���ق�X,Y��
		d4_p->AKI = sw_p->AKI;						//��
		d4_p->DATA_ADR = sw_p->DATA_ADR;			//�ް��i�[���ڽ
		d4_p->SUB_NO = sw_p->SUB_NO;				//���ٰ�ݔԍ�
		d4_p->GRP_NO = sw_p->GRP_NO;				//��ٰ�ߔԍ�
		d4_p->TOK_FLG = sw_p->TOK_FLG;				//�����׸�
		d4_p->CHG_NO = sw_p->CHG_NO;				//�ް��i�[��̕ύX�ޯĈʒu
		d4_p->CSR_NO = sw_p->CSR_NO;				//���̐ݒ�l�̑����鶰�ٔF���ԍ�
		d4_p->DSP_NO = sw_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
		d4_p->CARA_NO = sw_p->CARA_NO;				//���ٕ\����׎��
		d4_p->KAN_NO = sw_p->KAN_NO;				//�֘A�޲�
		d4_p->KAN_ADR = sw_p->KAN_ADR;				//�֘A���ڽ
		d4_p->SAVE_NO = sw_p->SAVE_NO;				//�i�[�׸�
		d4_p->YOBI2 = sw_p->YOBI2;					//�\���Q
		i++;
	}

	Disp_data_set();								//���ð��ق̔�\������(�쐬)
}
#else
void	Alltbl_set(void)
{
	Gamenn_CSRtbl_set();
	Gamenn_SVtbl_set();
	Gamenn_PVtbl_set();
	Gamenn_SWLtbl_set();
	Disp_data_set();								//���ð��ق̔�\������(�쐬)
}
#endif

/*
********************************************************************************
*  Module Name:		Wintbl_set
*  Function Name:	����޳��ʂ̏��ð��ق̍쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
void	Wintbl_set(void)
{
CSR_TBL_TDEF	*csr_tp, *csr_p, *d1_p;
SV_TBL_TDEF		*sv_tp, *sv_p, *d2_p;
PV_TBL_TDEF		*pv_tp, *pv_p, *d3_p;
SW_TBL_TDEF		*sw_tp, *sw_p, *d4_p;
UNl		cnt, i;


	csr_tp = CSTBL_Win_Adr_tbl[WINDOW_NO];				//�e��ʂ̏��ð��ق̱��ڽ���擾
	cnt = *CSCOUNT_Win_Adr_tbl[WINDOW_NO];				//�J�[�\���J�E���^
	CSR_CNT1 = CSR_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d1_p = &CSR_buff[i];						//�i�[�|�C���^�Z�b�g
		csr_p = &csr_tp[i];							//�i�[�|�C���^�Z�b�g

		d1_p->XY_POS = csr_p->XY_POS + 6;			//���ق�X,Y�� (�\���s�����E�C���h�E��ʂɉ�킹��)
		d1_p->DATA_NO = csr_p->DATA_NO;				//���َ�ʔԍ�
		d1_p->SV_MAX = csr_p->SV_MAX;				//�ݒ�lð��ٌ�
		d1_p->SW_MAX = csr_p->SW_MAX;				//SWð��ٌ�
		d1_p->CARA_NO = csr_p->CARA_NO;				//���ٕ\����׎�ʁi���g�p�j
		d1_p->MOVE_NO = csr_p->MOVE_NO;				//��ʈړ��ԍ�
		d1_p->TOK_NO = csr_p->TOK_NO;				//����ԍ�(B0:���ٖ���)
		d1_p->YOBI1 = csr_p->YOBI1;					//�\���P
		d1_p->YOBI2 = csr_p->YOBI2;					//�\���Q
		d1_p->SW56_UP = csr_p->SW56_UP;				//SW56��i��׸�
		d1_p->SW5_DN = csr_p->SW5_DN;				//SW5���i��׸�
		d1_p->SW6_DN = csr_p->SW6_DN;				//SW6���i��׸�
		d1_p->SW5_SUB = csr_p->SW5_SUB;				//SW5�ް������ԍ�
		d1_p->SW6_SUB = csr_p->SW6_SUB;				//SW6�ް������ԍ�
		d1_p->YOBI3 = csr_p->YOBI3;					//�\���R
		d1_p->AKI = csr_p->AKI;						//��
		i++;
	}

	sv_tp = SVTBL_Win_Adr_tbl[WINDOW_NO];
	cnt = *SVCOUNT_Win_Adr_tbl[WINDOW_NO];				//�J�[�\���J�E���^
	SV_CNT = (UNs)cnt;
	i = 0;
	while( cnt-- ) {
		d2_p = &SV_buff[i];							//�i�[�|�C���^�Z�b�g
		sv_p = &sv_tp[i];							//�i�[�|�C���^�Z�b�g

		d2_p->XY_POS = sv_p->XY_POS + 6;			//���ق�X,Y�� (�\���s�����E�C���h�E��ʂɉ�킹��)
		d2_p->AKI = sv_p->AKI;						//��
		d2_p->DATA_ADR = sv_p->DATA_ADR;			//�ް��i�[���ڽ
		d2_p->SUB_NO = sv_p->SUB_NO;				//���ٰ�ݔԍ�
		d2_p->GRP_NO = sv_p->GRP_NO;				//��ٰ�ߔԍ�
		d2_p->TOK_FLG = sv_p->TOK_FLG;				//�����׸�
		d2_p->BYTE_NO = sv_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d2_p->TEN_POS = sv_p->TEN_POS;				//�����_�̈ʒu
		d2_p->CSR_NO = sv_p->CSR_NO;				//���ٔF���ԍ�
		d2_p->DSP_NO = sv_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
		d2_p->SAVE_NO = sv_p->SAVE_NO;				//�i�[�׸�
		d2_p->YOBI_NO = sv_p->YOBI_NO;				//�\��
		d2_p->AKI2 = sv_p->AKI2;					//��
		i++;
	}

	pv_tp = PVTBL_Win_Adr_tbl[WINDOW_NO];
	cnt = *PVCOUNT_Win_Adr_tbl[WINDOW_NO];				//�J�[�\���J�E���^
	PV_CNT = (UNs)cnt;
	i = 0;
//	if(GAMEN_NO == 1){
//		PV_CNT++;
//		i++;
//	}
	while( cnt-- ) {
		d3_p = &PV_buff[i];							//�i�[�|�C���^�Z�b�g
		pv_p = &pv_tp[i];							//�i�[�|�C���^�Z�b�g

		d3_p->XY_POS = pv_p->XY_POS + 6;			//���ق�X,Y��(�\���s�����E�C���h�E��ʂɉ�킹��)
		d3_p->AKI = pv_p->AKI;						//��
		d3_p->DATA_ADR = pv_p->DATA_ADR;			//�ް��i�[���ڽ
		d3_p->SUB_NO = pv_p->SUB_NO;				//���ٰ�ݔԍ�
		d3_p->GRP_NO = pv_p->GRP_NO;				//��ٰ�ߔԍ�
		d3_p->TOK_FLG = pv_p->TOK_FLG;				//�����׸�
		d3_p->BYTE_NO = pv_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d3_p->TEN_POS = pv_p->TEN_POS;				//�����_�̈ʒu
		d3_p->YOBI1 = pv_p->YOBI1;					//�\���P
		d3_p->YOBI2 = pv_p->YOBI2;					//�\���Q
		d3_p->AKI2 = pv_p->AKI2;					//��
		i++;
	}

	if(WINDOW_NO < 6 || WINDOW_NO >= 10) {				//�i���p�E�C���h�E��ʁH
		sw_tp = SWTBL_Win_Adr_tbl[WINDOW_NO];
		cnt = *SWCOUNT_Win_Adr_tbl[WINDOW_NO];				//�J�[�\���J�E���^
		SW_CNT1 = SW_CNT = (UNs)cnt;
		i = 0;
		while( cnt-- ) {
			d4_p = &SW_buff[i];							//�i�[�|�C���^�Z�b�g
			sw_p = &sw_tp[i];							//�i�[�|�C���^�Z�b�g

			d4_p->XY_POS = sw_p->XY_POS + 6;			//���ق�X,Y��(�\���s�����E�C���h�E��ʂɉ�킹��)
			d4_p->AKI = sw_p->AKI;						//��
			d4_p->DATA_ADR = sw_p->DATA_ADR;			//�ް��i�[���ڽ
			d4_p->SUB_NO = sw_p->SUB_NO;				//���ٰ�ݔԍ�
			d4_p->GRP_NO = sw_p->GRP_NO;				//��ٰ�ߔԍ�
			d4_p->TOK_FLG = sw_p->TOK_FLG;				//�����׸�
			d4_p->CHG_NO = sw_p->CHG_NO;				//�ް��i�[��̕ύX�ޯĈʒu
			d4_p->CSR_NO = sw_p->CSR_NO;				//���̐ݒ�l�̑����鶰�ٔF���ԍ�
			d4_p->DSP_NO = sw_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
			d4_p->CARA_NO = sw_p->CARA_NO;				//���ٕ\����׎��
			d4_p->KAN_NO = sw_p->KAN_NO;				//�֘A�޲�
			d4_p->KAN_ADR = sw_p->KAN_ADR;				//�֘A���ڽ
			d4_p->SAVE_NO = sw_p->SAVE_NO;				//�i�[�׸�
			d4_p->YOBI2 = sw_p->YOBI2;					//�\���Q
			i++;
		}
	}
	Disp_data_set();									//���ð��ق̔�\������(�쐬)

}
#else
void	Wintbl_set(void)
{
	Gamenn_CSRtbl_set();
	Gamenn_SVtbl_set();
	Gamenn_PVtbl_set();
	Gamenn_SWLtbl_set();
	Disp_data_set();									//���ð��ق̔�\������(�쐬)
}
#endif


/*
********************************************************************************
*  Module Name:		Disp_data_set
*  Function Name:	���ð��ق̔�\������(�쐬)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-07-10
********************************************************************************
*/
void	Disp_data_set(void)
{

	CSR_CLS_FLG = 0;						//����������

	if(WINDOW_NO == 0){						//�E�C���h�E��ʕ\�����H
		gamen_tbl_set();
	}
	else{									//YES
		win_tbl_set();
	}

	PVdata_non_sub();
}


/*
********************************************************************************
*  Module Name:		gamen_tbl_set
*  Function Name:	��ʂ̏��ð��ق̔�\������(�쐬)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-07-10
********************************************************************************
*/
void	gamen_tbl_set(void)
{
	UNs		wk2b, Tcnt, cnt, t_no, sarch, *kaj;

	switch(GAMEN_NO) {
		default:
		case 2:			//���Y��ʁ@���^��{(���g�p)
//V01d		case 6:			//�i���ʁ@��{
		case 11:		//�ݒ��ʁ@�ް��ݒ�
		case 14:		//�ݒ��ʁ@�@�\�I��
//V06p		case 15:		//�ݒ��ʁ@�^�ް��Ǘ�
		case 18:		//�ݒ��ʁ@�ް��ݒ�I�𒆌^
//2014/09/01		case 24:		//�ݒ��ʁ@н̨��޶с@NO/NC�ݒ�
//2014/09/01		case 25:		//�ݒ��ʁ@۰�ضс@17�`20�ݒ�
		case 27:		//�ݒ��ʁ@���ײݶѐݒ�
		case 32:		//���ѐݒ�@�d�l�ݒ�1
		case 33:		//���ѐݒ�@�d�l�ݒ�2
		case 34:		//���ѐݒ�@�d�l�ݒ�3
		case 35:		//���ѐݒ�@�d�l�ݒ�4
		case 36:		//���ѐݒ�@�d�l�ݒ�5
		case 37:		//���ѐݒ�@�d�l�ݒ�6
		case 38:		//���ѐݒ�@C/B���ђ萔
		case 39:		//���ѐݒ�@�������Ұ�1
		case 40:		//���ѐݒ�@�������Ұ�2
		case 41:		//���ѐݒ�@���Ѷѐݒ�
		case 42:		//���щ�ʁ@���x���B�ް��ݒ�
		case 43:		//���ѐݒ�@�����ѥ��ϐݒ�
//V01r		case 44:		//���ѐݒ�@�׏d�v�ݒ�
		case 46:		//���щ�ʁ@��߼�ݍ\���ް����
		case 47:		//���щ�ʁ@�޲����ݎ�������(��)
		case 48:		//���щ�ʁ@�޲����ݎ�������(�E)
		case 49:		//���щ�ʁ@���ݻ���͒���
		case 50:		//���ѐݒ�@�ޯ������ް��ݒ�
		case 51:		//���ѐݒ�@C/B���ђ萔2
		case 52:		//���ѐݒ�@�ް�������
//2014/12/22		case 53:		//���щ�ʁ@���ײݎd�l�ݒ���
//2014/09/22		case 54:		//���щ�ʁ@�ް�۰�މ��
		case 55:		//���щ�ʁ@�d�l�ݒ�7
		case 56:		//���щ�ʁ@�d�l�ݒ�8
		case 57:		//���ѐݒ�@�������Ұ�3
		case 58:		//���ѐݒ�@�������Ұ�4
		case 59:		//���ѐݒ�@�������Ұ�5
		case 60:		//���ѐݒ�@�������Ұ�6
		case 106:		//���щ�ʁ@�d�l�ݒ�9		//V06m
		case 107:		//���щ�ʁ@�d�l�ݒ�10		//V06m
			break;

		case 1:			//���Y��ʁ@��{
//V01m			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_SUR_CNT);							//�����_�̕ύX(�ݒ�l&�����l)

			SV_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			PV_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			SW_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ۯĶ���1�̔�\��
			CSR_disp_cls(1);										//ۯĶ���1�̶���
			CSR_disp_cls(2);										//ۯĶ���1�̐ݒ蕶��

			SV_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			PV_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			SW_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ۯĶ���2�̔�\��
			CSR_disp_cls(3);										//ۯĶ���2�̶���
			CSR_disp_cls(4);										//ۯĶ���2�̐ݒ蕶��

//V01m			LENG_svpv(52, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(52, SYO_LNG_SUR_CNT);							//�����_�̕ύX(�ݒ�l&�����l)

			PV_cls(52, SEQ_020_SV, BIT_5);							//�޲ʲĎ����̔�\��
			PV_cls(54, SEQ_020_SV, BIT_5);							//�޲ʲĎ����̔�\��
			CSR_disp_cls(5);										//�޲ʲĂ̕���

			PV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�����̔�\��
			CSR_disp_cls(6);										//�׏d�v�̕���

			PV_cls(68, SEQ_016_SV, BIT_3);							//�į��ݸ���ώ����̔�\��
			CSR_disp_cls(79);										//�į��ݸ���ς̕���
			CSR_disp_cls(80);										//�į��ݸ���ς̕���

			SCAN_kat_cls();											//

			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r

//			SV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_disp_cls(93);										//VS�d�l�̶���

			PV_cls(124, SEQ_PAR_113, BIT_3);						//�����������������ώ����̔�\��	V06h

			break;

		case 6:			//���Y��ʁ@Ӱ��ݐݒ�	/* V01d */
		case 30:		//�ݒ��ʁ@Ӱ��ݐݒ�	/* V01d */
		case 3:			//���Y��ʁ@Ӱ��ݐݒ�
		case 28:		//�ݒ��ʁ@Ӱ��ݐݒ�
			kag_to_kaj_sub_chg();					//�����ʒu���ڕW�׏d ���ٰ��No.�؊�		V01k

			LENG_svpv(91, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(92, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(93, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(94, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(95, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(96, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(112, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(113, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(114, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(115, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(116, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(117, SYO_LNG_KAJ_CNT);						//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//�����_�̕ύX(�ݒ�l&�����l) V05r

			SW_cls(62, SEQ_023_SV, BIT_8);							//�������̔�\��
			CSR_disp_cls(136);										//�������̶���

			if ( (SEQ_050_SV & BIT_2) == 0 ) {							//V06p
				SW_cls(62, ~SEQ_PAR_113, BIT_15);					//�������̔�\��
			}

			SW_cls(63, SEQ_023_SV, BIT_9);							//�㉝���̔�\��
			CSR_disp_cls(137);										//�㉝���̶���
			SW_cls(64, SEQ_024_SV, BIT_2);							//���]�̔�\��
			CSR_disp_cls(150);										//���]�̶���

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

			motion_csr_clr();										//��ݽ̧Ӱ��ݑΉ�	/* V01n */

			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//���ח������̔�\��	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//�d�͗ʎ����̔�\��	//V06

			if (SEQ_050_SV & BIT_0) {	//V06b
				//�ݒ�l�w�i�����i���͕s�j
				SV_col_chg(85, COL_BLACK, COL_WHITE, COL_WHITE);	//��]�̎��͏���p�̔w�i�𔒂ɂ���B	V06b
				SV_col_chg(91, COL_BLACK, COL_WHITE, COL_WHITE);	//��]�̎��͏���ʒu�̔w�i�𔒂ɂ���B	V06b
			}
			
			if (SEQ_050_SV & BIT_2) {	//V06m
				if (GMN_PAR021 == 1) {
					//�ݒ�l�w�i�����i���͕s�j
					SV_col_chg2( 2, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͍H���̔w�i�𔒂ɂ���B
					SV_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͂P�i�ڒ�~���Ԃ̔w�i�𔒂ɂ���B
					SV_col_chg2(27, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͖߂葬�x�̔w�i�𔒂ɂ���B
					SW_col_chg2(10, COL_BLACK, COL_WHITE, COL_WHITE);	//�U�q�̎��͂P�i�ځu�u�v�̔w�i�𔒂ɂ���B
				}
			}

//			���[�V������~���Ԃ̏����_�ʒu�ύX		�����_�ȉ�2�� �� 1��	2014/04/14
			for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
				if(SV_buff[t_no].AKI2 == 1) {						//��ٰ�ߔԍ� ���
					SV_buff[t_no].TEN_POS = 1;						//�����_�̈ʒu �ύX
				}
			}

//			�����^�␳�̔�\������	R01����ڐA				2014/08/20
			if( SEQ_050_SV & BIT_1 ) {						//���]�H
				// �����ݒ��\��  2014/03/10
				wk2b = grpno_sv_srch(117);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
				SV_buff[wk2b].SUB_NO |= BIT_F;				//��\�����
				CSR_buff[4].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
				PV_buff[3].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�

				// �␳�ݒ��\��  2014/03/10
				wk2b = grpno_sv_srch(118);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
				SV_buff[wk2b].SUB_NO |= BIT_F;				//��\�����
				CSR_buff[5].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
				SW_buff[4].SUB_NO |= BIT_F;					//������/�� ��\���̐ݒ�
				PV_buff[4].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�

				// �e�H���̖ڕW�l�ؑւ��\��  2015/01/15
				if ( (SEQ_PAR_151 & BIT_2) == 0 ) {
					mark_chg_no_disp();						//�����i�ʒu�^�׏d�j�ؑ֕\���Ȃ�
				}
			}
			else {
				// �e�H���̖ڕW�l�ؑւ��\��  2015/01/15
				mark_chg_no_disp();							//�����i�ʒu�^�׏d�j�ؑ֕\���Ȃ�
			}

			if ( (GAMEN_NO == 28) || (GAMEN_NO == 30) ) {	//2014/08/20
				if ( (SEQ_050_SV & (cBIT0+cBIT2)) != 0 ) {	//��]�^�U�q�H
					//�ʒu���ߊ����͈͔�\��
//2015/01/15 �׏d�����͈͂�ǉ��������߁A�����B
////					CSR_buff[28].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
////					CSR_buff[29].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
////					CSR_buff[30].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
////					SV_buff[27].SUB_NO |= BIT_F;			//��\�����
////					SV_buff[28].SUB_NO |= BIT_F;			//��\�����
////					SV_buff[29].SUB_NO |= BIT_F;			//��\�����
////					PV_buff[10].SUB_NO |= BIT_F;			//�P�ʕ\���̐ݒ�
					CSR_buff[28+1].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
					CSR_buff[29+1].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
					CSR_buff[30+1].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
					SV_buff[27+1].SUB_NO |= BIT_F;			//��\�����
					SV_buff[28+1].SUB_NO |= BIT_F;			//��\�����
					SV_buff[29+1].SUB_NO |= BIT_F;			//��\�����
					PV_buff[10+1].SUB_NO |= BIT_F;			//�P�ʕ\���̐ݒ�
				}
			}

//2015/01/15	�e�i�̖ڕW�l���׏d�̏ꍇ�̒P�ʐؑցimm��kN�j
			if ( (GAMEN_NO == 3) || (GAMEN_NO == 28) ) {	//1�`5�i���
				if (SEQ_050_SV & BIT_1) {
					wk2b = SV_MOTOBJ_INF1;
				}
				else {
					break;
				}
				sarch = 92;									//1�`5�i�ڂ̌�������ݒ�l��ٰ��No.
				kaj = &SV_1DANPRS_SRV;
			}
			else {											//6�`10�i���
				if (SEQ_050_SV & BIT_1) {
					wk2b = SV_MOTOBJ_INF1 >> 5;
				}
				else {
					break;
				}
				sarch = 112;								//6�`10�i�ڂ̌�������ݒ�l��ٰ��No.
				kaj = &SV_6DANPRS_SRV;
			}
			for (Tcnt=0; Tcnt<5; Tcnt++, wk2b>>=1, sarch++, kaj++) {
				for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
					if(SV_buff[t_no].GRP_NO == sarch) {				//��ٰ�ߔԍ� ���
						if (wk2b & BIT_0) {
							/* �ʒu -> �׏d*/
							SV_buff[t_no].DATA_ADR = kaj;			//�i�[����ڽ�ύX
							SV_buff[t_no].BYTE_NO = 2;				//�޲Ē��̕ύX
							SV_buff[t_no].TEN_POS = SYO_KAJ_CNT;	//�����_�ʒu
							SV_buff[t_no].TOK_FLG = 0;				//�����׸�
							SV_buff[t_no].SUB_NO = 123;				//���ٰ��No.

							PV_buff[5+Tcnt].DATA_ADR = (UNs *)&CAR_KAJ_AREA;		//�P��
						}
						break;
					}
				}
			}

			break;

		case 4:			//���Y��ʁ@����Ӱ���
		case 29:		//�ݒ��ʁ@����Ӱ���
			kag_to_kaj_sub_chg();					//�����ʒu���ڕW�׏d ���ٰ��No.�؊�		V01k

			LENG_svpv(91, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(117, SYO_LNG_KAJ_CNT);						//�����_�̕ύX(�ݒ�l&�����l) V01k
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//�����_�̕ύX(�ݒ�l&�����l) V05r

			SW_cls(62, SEQ_023_SV, BIT_8);							//�������̔�\��
			CSR_disp_cls(136);										//�������̶���
			SW_cls(63, SEQ_023_SV, BIT_9);							//�㉝���̔�\��
			CSR_disp_cls(137);										//�㉝���̶���
			SW_cls(64, SEQ_024_SV, BIT_2);							//���]�̔�\��
			CSR_disp_cls(150);										//���]�̶���

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//���ח������̔�\��	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//�d�͗ʎ����̔�\��	//V06

//			�����^�␳�̔�\������	R01����ڐA				2014/08/20
			if( SEQ_050_SV & BIT_1 ) {						//���]�H
				// �����ݒ��\��  2014/03/10
				wk2b = grpno_sv_srch(117);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
				SV_buff[wk2b].SUB_NO |= BIT_F;				//��\�����
				CSR_buff[4].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
				PV_buff[3].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�

				// �␳�ݒ��\��  2014/03/10
				wk2b = grpno_sv_srch(118);					//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
				SV_buff[wk2b].SUB_NO |= BIT_F;				//��\�����
				CSR_buff[5].TOK_NO |= BIT_0;				//���ٔ�\���̐ݒ�
				SW_buff[4].SUB_NO |= BIT_F;					//������/�� ��\���̐ݒ�
				PV_buff[4].SUB_NO |= BIT_F;					//�P�ʕ\���̐ݒ�
			}

			if (GAMEN_NO == 29) {							//2014/08/20
				if ( (SEQ_050_SV & (cBIT0+cBIT2)) != 0 ) {	//��]�^�U�q�H
					//�ʒu���ߊ����͈͔�\��
					CSR_buff[6].TOK_NO |= BIT_0;			//���ٔ�\���̐ݒ�
					SV_buff[5].SUB_NO |= BIT_F;				//��\�����
					PV_buff[6].SUB_NO |= BIT_F;				//�P�ʕ\���̐ݒ�
				}
			}

			break;

		case 7:			//�i���ʁ@���^��{
//			DANsel_csr(83, SEQ_020_SV, BIT_14, 118);				//���^��������		V01j
			DANsel_csr(67, SEQ_020_SV, BIT_4 | BIT_6, 119-1);			//�X���C�h����

//2014/03/13
////			DANsel_csr(62, SEQ_019_SV, BIT_4, 120-1);					//��^�N�����p
////			DANsel_csr(63, SEQ_019_SV, BIT_6, 121-1);					//���^�N�����p
////			DANsel_csr(64, SEQ_019_SV, BIT_8, 122-1);					//�_�C���t�^
			DANsel_csr(62, SEQ_PAR_152, BIT_0, 120-1);					//��^�N�����p
			DANsel_csr(63, SEQ_PAR_152, BIT_1, 121-1);					//���^�N�����p
			DANsel_csr(64, SEQ_PAR_152, BIT_2, 122-1);					//�_�C���t�^

//			DANsel_csr(65, SEQ_019_SV, BIT_10,123);					//�_�C�N�b�V����	V01j
//			DANsel_csr(66, SEQ_020_SV, BIT_1, 124);					//�h���			V01j
//			DANsel_csr(80, SEQ_020_SV, BIT_15,125);					//�l�a				V01j
//			DANsel_csr(81, SEQ_020_SV, BIT_11,126);					//�o�����T
//			DANsel_csr(82, SEQ_019_SV, BIT_12 | BIT_13 | BIT_15,127);	//�޲����ݒ���

//2014/03/13
////			SW_cls(30, SEQ_019_SV, BIT_4);							//��^�N�����p�̔�\��
////			SW_cls(31, SEQ_019_SV, BIT_6);							//���^�N�����p�̔�\��
////			SW_cls(32, SEQ_019_SV, BIT_8);							//�_�C���t�^�̔�\��
			SW_cls(30, SEQ_PAR_152, BIT_0);							//��^�N�����p�̔�\��
			SW_cls(31, SEQ_PAR_152, BIT_1);							//���^�N�����p�̔�\��
			SW_cls(32, SEQ_PAR_152, BIT_2);							//�_�C���t�^�̔�\��

//			SW_cls(33, SEQ_019_SV, BIT_10);							//�_�C�N�b�V������\��	V01j
//			SW_cls(34, SEQ_020_SV, BIT_1);							//�h���̔�\��		V01j
//			SW_cls(35, SEQ_020_SV, BIT_15);							//�l�a�̔�\��			V01j

			DAN_csr_set();											//�i���ʁ@�\���������J�E���^

			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(52, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			PV_cls(68, SEQ_016_SV, BIT_3);							//�X�g�b�s���O�\��
			CSR_disp_cls(79);
			CSR_disp_cls(80);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 81);					//�^�ԍ�
			KAT_cls(56, SEQ_PAR_107, BIT_0, 61);					//�^�ԍ�
			MEMO_cls(69, SEQ_PAR_107,BIT_0, 83);					//����

//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l
//			CSR_disp_cls(93);
			break;

		case 8:			//�i���ʁ@���^��{		//V01r
			DANsel_csr(83, SEQ_020_SV, BIT_14, 118);				//���^��������		V01j
			DANsel_csr(67, SEQ_020_SV, BIT_4 | BIT_6, 119);			//�X���C�h����

//2014/03/13
////			DANsel_csr(62, SEQ_019_SV, BIT_4, 120);					//��^�N�����p
////			DANsel_csr(63, SEQ_019_SV, BIT_6, 121);					//���^�N�����p
////			DANsel_csr(64, SEQ_019_SV, BIT_8, 122);					//�_�C���t�^
			DANsel_csr(62, SEQ_PAR_152, BIT_0, 120);					//��^�N�����p
			DANsel_csr(63, SEQ_PAR_152, BIT_1, 121);					//���^�N�����p
			DANsel_csr(64, SEQ_PAR_152, BIT_2, 122);					//�_�C���t�^

			DANsel_csr(65, SEQ_019_SV, BIT_10,123);					//�_�C�N�b�V����	V01j
			DANsel_csr(66, SEQ_020_SV, BIT_1, 124);					//�h���			V01j
			DANsel_csr(80, SEQ_020_SV, BIT_15,125);					//�l�a				V01j
			DANsel_csr(81, SEQ_020_SV, BIT_11,126);					//�o�����T
			DANsel_csr(82, SEQ_019_SV, BIT_12 | BIT_13 | BIT_15,127);	//�޲����ݒ���

//2014/03/13
////			SW_cls(30, SEQ_019_SV, BIT_4);							//��^�N�����p�̔�\��
////			SW_cls(31, SEQ_019_SV, BIT_6);							//���^�N�����p�̔�\��
////			SW_cls(32, SEQ_019_SV, BIT_8);							//�_�C���t�^�̔�\��
			SW_cls(30, SEQ_PAR_152, BIT_0);							//��^�N�����p�̔�\��
			SW_cls(31, SEQ_PAR_152, BIT_1);							//���^�N�����p�̔�\��
			SW_cls(32, SEQ_PAR_152, BIT_2);							//�_�C���t�^�̔�\��

			SW_cls(33, SEQ_019_SV, BIT_10);							//�_�C�N�b�V������\��	V01j
			SW_cls(34, SEQ_020_SV, BIT_1);							//�h���̔�\��		V01j
			SW_cls(35, SEQ_020_SV, BIT_15);							//�l�a�̔�\��			V01j

			DAN_csr_set();											//�i���ʁ@�\���������J�E���^

			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			PV_cls(68, SEQ_016_SV, BIT_3);							//�X�g�b�s���O�\��
			CSR_disp_cls(79);
			CSR_disp_cls(80);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 81);					//�^�ԍ�
			KAT_cls(56, SEQ_PAR_107, BIT_0, 61);					//�^�ԍ�
			MEMO_cls(69, SEQ_PAR_107,BIT_0, 83);					//����

//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l
//			CSR_disp_cls(93);
			break;

		case 12:		//�ݒ��ʁ@�і��̐ݒ�
		case 16:		//�ݒ��ʁ@�^�ް����̐ݒ�
		case 23:		//�ݒ��ʁ@�Ӗ��̓��͉��
		case 26:		//�ݒ��ʁ@۰�ضі��̓���
			NAME_cls_sub();
			CSR_disp_cls(96);
			CSR_disp_cls(97);
			CSR_disp_cls(98);
			break;

		case 13:		//�ݒ��ʁ@����ݽ ���
//			PV_cls(68, SEQ_016_SV, BIT_3);							//�į��ݸނ̔�\��
//			SV_cls(68, SEQ_016_SV, BIT_3);							//�į��ݸނ̔�\��
//			CSR_disp_cls(88);
//			CSR_disp_cls(89);
//			CSR_disp_cls(90);
//			CSR_cls(68, SEQ_016_SV, BIT_3);							//�į��ݸނ̔�\��
			break;

		case 17:		//�ݒ��ʁ@�ް��ݒ蒆�^
			kag_to_kaj_sub_chg();					//�����ʒu���ڕW�׏d ���ٰ��No.�؊�		V01r

//V01m			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_SUR_CNT);							//�����_�̕ύX(�ݒ�l&�����l)

//			ATU_svpv(21, SYO_ATU_CNT);								//�ݒ�l���ð��ق̕ύX

			SV_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			PV_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			SW_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ۯĶ���1�̔�\��
			CSR_disp_cls(7);										//ۯĶ���1��1�s

			SV_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			PV_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			SW_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ۯĶ���2�̔�\��
			CSR_disp_cls(8);										//ۯĶ���2��1�s

			SV_cls(19, SEQ_020_SV, BIT_6);							//�޲ʲĂ̔�\��
			PV_cls(54, SEQ_020_SV, BIT_6);							//�޲ʲĂ̔�\��
			CSR_cls(54, SEQ_020_SV, BIT_6);							//�޲ʲĂ̔�\��
			CSR_disp_cls(14);
			CSR_disp_cls(15);
			CSR_disp_cls(16);
			CSR_disp_cls(17);

//			SV_cls(21, SEQ_020_SV, BIT_11);							//���ݻ���͂̔�\��
//			PV_cls(55, SEQ_020_SV, BIT_11);							//���ݻ���͂̔�\��
//			CSR_cls(55, SEQ_020_SV, BIT_11);						//���ݻ���͂̔�\��
//			CSR_disp_cls(18);

//2014/03/14	--------------------------------------------------------------------------------------------
			t_no = grpno_sv_srch(128);								//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
			if (SV_OVLD_SEL == 1) {								//���ް۰�ލŏ��l
				wk2b = BIT_1;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A27;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A27;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A27;
			}
			else if (SV_OVLD_SEL == 2) {							//���ް۰�ސU��
				wk2b = BIT_2;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A28;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A28;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A28;
			}
			else {													//���ް۰�ލő�l
				wk2b = BIT_0;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A26;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A26;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A26;
			}
			if ((SEQ_020_SV & BIT_8)== 0) {
				wk2b = 0;
			}
			SW_cls(128, wk2b, BIT_0);								//�׏d�v����۰�ލő�l
			SW_cls(129, wk2b, BIT_1);								//�׏d�v����۰�ލŏ��l
			SW_cls(130, wk2b, BIT_2);								//�׏d�v����۰�ސU��
			SV_cls(128, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			SV_cls(129, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			SV_cls(130, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
	
			t_no = grpno_sv_srch(131);								//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��
			if (SV_LWLM_SEL == 1) {									//۱��Яčŏ��l
				wk2b = BIT_1;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A27;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A27;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A27;
			}
			else if (SV_LWLM_SEL == 2) {							//۱��ЯĐU��
				wk2b = BIT_2;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A28;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A28;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A28;
			}
			else {													//۱��Яčő�l
				wk2b = BIT_0;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A26;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A26;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A26;
			}
			if ((SEQ_020_SV & BIT_8)== 0) {
				wk2b = 0;
			}
			SW_cls(131, wk2b, BIT_0);								//�׏d�v۱��Яčő�l
			SW_cls(132, wk2b, BIT_1);								//�׏d�v۱��Яčŏ��l
			SW_cls(133, wk2b, BIT_2);								//�׏d�v۱��ЯĐU��
			SV_cls(131, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			SV_cls(132, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			SV_cls(133, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
//--------------------------------------------------------------------------------------------------------------

			SV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			PV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			CSR_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			CSR_disp_cls(9);
			CSR_disp_cls(10);
			CSR_disp_cls(11);
			CSR_disp_cls(12);
			CSR_disp_cls(13);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r
			LENG_svpv(118, SYO_HOS_KAJ_CNT);						//�����_�̕ύX(�ݒ�l&�����l) V05r

			KAJ_svpv(128, SYO_KAJ_CNT);								//�׏d�v����۰�ލő�l		2016/03/17
			KAJ_svpv(129, SYO_KAJ_CNT);								//�׏d�v����۰�ލŏ��l		2016/03/17
			KAJ_svpv(130, SYO_KAJ_CNT);								//�׏d�v����۰�ސU��		2016/03/17
			KAJ_svpv(131, SYO_KAJ_CNT);								//�׏d�v۱��Яčő�l		2016/03/17
			KAJ_svpv(132, SYO_KAJ_CNT);								//�׏d�v۱��Яčŏ��l		2016/03/17
			KAJ_svpv(133, SYO_KAJ_CNT);								//�׏d�v۱��ЯĐU��			2016/03/17

//			SV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_disp_cls(94);										//VS�d�l�̶���
			break;

		case 19:		//�ݒ��ʁ@��ު���^�������ѐݒ�
			if( SV_CNT != 00 ) {
				EJE_grp(1, 2, BIT_8, SEQ_017_SV, BIT_4, 32, SEQ_017_SV, BIT_6, 19);			//�G�W�F�N�^�P
				EJE_grp(22, 23, BIT_9, SEQ_017_SV, BIT_7, 33, SEQ_017_SV, BIT_9, 20);		//�G�W�F�N�^�Q
				EJE_grp(24, 25, BIT_10, SEQ_017_SV, BIT_10, 34, SEQ_017_SV, BIT_12, 21);	//�G�W�F�N�^�R
				EJE_grp(26, 27, BIT_11, SEQ_017_SV, BIT_13, 35, SEQ_017_SV, BIT_15, 22);	//�G�W�F�N�^�S
				EJE_grp(28, 29, BIT_12, SEQ_018_SV, BIT_0, 36, SEQ_018_SV, BIT_2, 23);		//�G�W�F�N�^�T
				EJE_grp(30, 31, BIT_13, SEQ_018_SV, BIT_3, 37, SEQ_018_SV, BIT_5, 24);		//�G�W�F�N�^�U

				EJE_sw(19, SEQ_017_SV, BIT_4);						//�G�W�F�N�^�P
				EJE_sw(20, SEQ_017_SV, BIT_7);						//�G�W�F�N�^�Q
				EJE_sw(21, SEQ_017_SV, BIT_10);						//�G�W�F�N�^�R
				EJE_sw(22, SEQ_017_SV, BIT_13);						//�G�W�F�N�^�S
				EJE_sw(23, SEQ_018_SV, BIT_0);						//�G�W�F�N�^�T
				EJE_sw(24, SEQ_018_SV, BIT_3);						//�G�W�F�N�^�U

				if( CSR_CNT != 00 ) {
					EJE_csr(0x91, SEQ_017_SV, BIT_4, SEQ_017_SV, BIT_6, 25);				//�G�W�F�N�^1
					EJE_csr(0x92, SEQ_017_SV, BIT_7, SEQ_017_SV, BIT_9, 26);				//�G�W�F�N�^2
					EJE_csr(0x93, SEQ_017_SV, BIT_10, SEQ_017_SV, BIT_12, 27);				//�G�W�F�N�^3
					EJE_csr(0x94, SEQ_017_SV, BIT_13, SEQ_017_SV, BIT_15, 28);				//�G�W�F�N�^4
					EJE_csr(0x95, SEQ_018_SV, BIT_0, SEQ_018_SV, BIT_2, 29);				//�G�W�F�N�^5
					EJE_csr(0x96, SEQ_018_SV, BIT_3, SEQ_018_SV, BIT_5, 30);				//�G�W�F�N�^6
				}
			}
			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�
			break;

		case 20:		//�ݒ��ʁ@н̨��޶ѐݒ�
			SYS_MISSEL_SV = SEQ_024_SV;								//н̨���7�`8 �ێ�/�r�o�@����߰
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//н̨���1�`6 �ێ�/�r�o�@����߰

			MIS_sv(46, SEQ_018_SV, BIT_8);							//�~�X�t�B�[�h�P
			MIS_sv(47, SEQ_018_SV, BIT_9);							//�~�X�t�B�[�h�Q
			MIS_sv(48, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�R
			MIS_sv(49, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�S

			EJE_sw(25, SEQ_018_SV, BIT_8);							//�~�X�t�B�[�h�P
			EJE_sw(26, SEQ_018_SV, BIT_9);							//�~�X�t�B�[�h�Q
			EJE_sw(27, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�R
			EJE_sw(28, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�S

			MIS_csr(15, SEQ_018_SV, BIT_8, 31, 138);				//�~�X�t�B�[�h�P
			MIS_csr(16, SEQ_018_SV, BIT_9, 32, 139);				//�~�X�t�B�[�h�Q
			MIS_csr(17, SEQ_018_SV, BIT_10,33, 140);				//�~�X�t�B�[�h�R
			MIS_csr(18, SEQ_018_SV, BIT_10,34, 141);				//�~�X�t�B�[�h�S

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

			MISS_swcara();
			break;

		case 68:		//�ݒ��ʁ@н̨��޶ѐݒ�	// V01r(INS)
			SYS_MISSEL_SV = SEQ_024_SV;								//н̨���7�`8 �ێ�/�r�o�@����߰
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//н̨���1�`6 �ێ�/�r�o�@����߰

			MIS_sv(103, SEQ_018_SV, BIT_11);						//�~�X�t�B�[�h�T
			MIS_sv(104, SEQ_018_SV, BIT_11);						//�~�X�t�B�[�h�U

			EJE_sw(57, SEQ_018_SV, BIT_11);							//�~�X�t�B�[�h�T
			EJE_sw(58, SEQ_018_SV, BIT_11);							//�~�X�t�B�[�h�U

			MIS_csr(79, SEQ_018_SV, BIT_11,66, 0);					//�~�X�t�B�[�h�T
			MIS_csr(80, SEQ_018_SV, BIT_11,67, 0);					//�~�X�t�B�[�h�U

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

			MISS56_swcara();
			break;

		case 24:		//�ݒ��ʁ@۰�ض�1�`8�ѐݒ�(�i�p�L)					2014/09/01
			/*********	�ėp�J���̐i�p�̊p�x�^���Ԑؑ֏���		*************/
			wk2b = cBIT0;
			for(cnt=0; cnt<8; cnt++, wk2b<<=1) {
				/* ON�i�p */
				if ((SEQ_PAR_151 & cBIT11)==0) {				//���Ԑi�p�@�\
					/*�p�x�ݒ�*/
					SV_buff[cnt*8+4].SUB_NO &= ~BIT_15;			//�\���̐ݒ�
					SV_buff[cnt*8+5].SUB_NO |= BIT_15;			//��\���̐ݒ�
				}
				else {
					if(SEQ_055_SV & wk2b){						//�i�p��ϑI������H
						/*��ϐݒ�*/
						SV_buff[cnt*8+4].SUB_NO |= BIT_15;		//��\���̐ݒ�
						SV_buff[cnt*8+5].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
					}
					else {
						/*�p�x�ݒ�*/
						SV_buff[cnt*8+4].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
						SV_buff[cnt*8+5].SUB_NO |= BIT_15;		//��\���̐ݒ�
					}
				}
				if (PV0_SINKAKU_UPDN1 & wk2b) {				//�i�p���������͈͂ɂ��邩�H
					SV_buff[cnt*8+4].B_COL1 = COL_RED;		//�i�p�̔w�i�F����
					SV_buff[cnt*8+5].B_COL1 = COL_RED;		//�i�p(���)�̔w�i�F����
				}
				else {
					SV_buff[cnt*8+4].B_COL1 = COL_LBULE;		//�i�p�̔w�i�F�����F
					SV_buff[cnt*8+5].B_COL1 = COL_LBULE;		//�i�p(���)�̔w�i�F�����F
				}

				/* OFF�i�p */
				if ((SEQ_PAR_151 & cBIT11)==0) {				//���Ԑi�p�@�\
					/*�p�x�ݒ�*/
					SV_buff[cnt*8+6].SUB_NO &= ~BIT_15;			//�\���̐ݒ�
					SV_buff[cnt*8+7].SUB_NO |= BIT_15;			//��\���̐ݒ�
				}
				else {
					if(SEQ_059_SV & wk2b){						//�i�p��ϑI������H
						/*��ϐݒ�*/
						SV_buff[cnt*8+6].SUB_NO |= BIT_15;		//��\���̐ݒ�
						SV_buff[cnt*8+7].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
					}
					else {
						/*�p�x�ݒ�*/
						SV_buff[cnt*8+6].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
						SV_buff[cnt*8+7].SUB_NO |= BIT_15;		//��\���̐ݒ�
					}
				}
				if (PV0_SINKAKU_UPDN2 & wk2b) {				//�i�p���������͈͂ɂ��邩�H
					SV_buff[cnt*8+6].B_COL1 = COL_RED;		//�i�p�̔w�i�F����
					SV_buff[cnt*8+7].B_COL1 = COL_RED;		//�i�p(���)�̔w�i�F����
				}
				else {
					SV_buff[cnt*8+6].B_COL1 = COL_LBULE;		//�i�p�̔w�i�F�����F
					SV_buff[cnt*8+7].B_COL1 = COL_LBULE;		//�i�p(���)�̔w�i�F�����F
				}
			}

			/*********	�ėp�J���̔ėp�o�͑I�����̐i�p�����J�[�\���ݒ�l���ύX����		*************/
			if ((SEQ_018_SV & cBIT13)==0) {					//۰�ض�1�`4�i�p�L��
				CSR_buff[0].SV_MAX = 4;
				CSR_buff[1].SV_MAX = 4;
				CSR_buff[2].SV_MAX = 4;
				CSR_buff[3].SV_MAX = 4;
			}
			if ((SEQ_018_SV & cBIT15)==0) {					//۰�ض�5�`8�i�p�L��
				CSR_buff[4].SV_MAX = 4;
				CSR_buff[5].SV_MAX = 4;
				CSR_buff[6].SV_MAX = 4;
				CSR_buff[7].SV_MAX = 4;
			}

			/*********	���[�V�����̐ݒ�����ɂ���Đi�p�ւ̃J�[�\���ړ����֎~���鏈��		*************/
			PV0_MOTION_INF = MOT_INF_GET();
			if (PV0_MOTION_INF) {
				for(cnt=0; cnt<8; cnt++) {
					CSR_buff[cnt].SV_MAX = 4;					//�ݒ�l��4�Ɍ��炷
					SV_buff[cnt*8+4].B_COL1 = COL_WHITE;		//ON�i�p�w�i�F����
					SV_buff[cnt*8+5].B_COL1 = COL_WHITE;		//ON�i�p(���)�w�i�F����
					SV_buff[cnt*8+6].B_COL1 = COL_WHITE;		//OFF�i�p�w�i�F����
					SV_buff[cnt*8+7].B_COL1 = COL_WHITE;		//OFF�i�p(���)�w�i�F����
				}
			}

		case 21:		//�ݒ��ʁ@۰�ض�1�`8�ѐݒ�
						/*********	�ėp�J���̔ėp�o�͑I�����̐ݒ�l��������		*************/
			ROT_cam_sv(1, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 35);	//۰�ض�1
			CSR_disp_cls(142);
			ROT_cam_sv(2, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 36);	//۰�ض�2
			CSR_disp_cls(143);
			ROT_cam_sv(3, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 37);	//۰�ض�3
			CSR_disp_cls(144);
			ROT_cam_sv(4, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12, 38, BIT_13, 38);	//۰�ض�4
			CSR_disp_cls(145);
			ROT_cam_sv(5, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 39);	//۰�ض�5
			CSR_disp_cls(146);
			ROT_cam_sv(6, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 40);	//۰�ض�6
			CSR_disp_cls(147);
			ROT_cam_sv(7, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 41);	//۰�ض�7
			CSR_disp_cls(148);
			ROT_cam_sv(8, BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14, 39, BIT_15, 42);	//۰�ض�8
			CSR_disp_cls(149);

						/*********	�ėp�J���̔ėp�o�͑I�����̂r�v�f�[�^��������		*************/
			ROT_cam_sw(3, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12);		//۰�ض�1
			ROT_cam_sw(4, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12);		//۰�ض�2
			ROT_cam_sw(5, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12);		//۰�ض�3
			ROT_cam_sw(6, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12);		//۰�ض�4
			ROT_cam_sw(7, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14);		//۰�ض�5
			ROT_cam_sw(8, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14);		//۰�ض�6
			ROT_cam_sw(9, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14);		//۰�ض�7
			ROT_cam_sw(10,BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14);		//۰�ض�8

						/*********	�ėp�J���̔ėp�o�͑I�����̃J�[�\���f�[�^��������		*************/
			ROT_cam_csr(0x80, BIT_0, SV_CAMNA0_C1, SEQ_018_SV, BIT_12, BIT_13, 43);	//۰�ض�1
			ROT_cam_csr(0x81, BIT_0, SV_CAMNA1_C1, SEQ_018_SV, BIT_12, BIT_13, 44);	//۰�ض�2
			ROT_cam_csr(0x82, BIT_0, SV_CAMNA2_C1, SEQ_018_SV, BIT_12, BIT_13, 45);	//۰�ض�3
			ROT_cam_csr(0x83, BIT_0, SV_CAMNA3_C1, SEQ_018_SV, BIT_12, BIT_13, 46);	//۰�ض�4
			ROT_cam_csr(0x84, BIT_0, SV_CAMNA4_C1, SEQ_018_SV, BIT_14, BIT_15, 47);	//۰�ض�5
			ROT_cam_csr(0x85, BIT_0, SV_CAMNA5_C1, SEQ_018_SV, BIT_14, BIT_15, 48);	//۰�ض�6
			ROT_cam_csr(0x86, BIT_0, SV_CAMNA6_C1, SEQ_018_SV, BIT_14, BIT_15, 49);	//۰�ض�7
			ROT_cam_csr(0x87, BIT_0, SV_CAMNA7_C1, SEQ_018_SV, BIT_14, BIT_15, 50);	//۰�ض�8

			if (GAMEN_NO == 24) {										//2014/09/02
				for(cnt=0; cnt<8; cnt++) {
					if ( (SV_buff[cnt*8+4].SUB_NO & BIT_15) &&
						 (SV_buff[cnt*8+5].SUB_NO & BIT_15) ) {			//ON�i�p�ݒ�l����\���ݒ�H
						SW_buff[cnt*3+1].SUB_NO |= BIT_15;				//ON�i�p�̒P��(���^ms)���\��
						SW_buff[cnt*3+2].SUB_NO |= BIT_15;				//OFF�i�p�̒P��(���^ms)���\��
					}
				}
			}

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//�^�ԍ�
			break;

		case 25:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�(�i�p�L)					2014/09/01
			/*********	�ėp�J���̐i�p�̊p�x�^���Ԑؑ֏���		*************/
			wk2b = cBIT8;
			for(cnt=0; cnt<8; cnt++, wk2b<<=1) {
				/* ON�i�p */
				if ((SEQ_PAR_151 & cBIT11)==0) {				//���Ԑi�p�@�\
					/*�p�x�ݒ�*/
					SV_buff[cnt*8+4].SUB_NO &= ~BIT_15;			//�\���̐ݒ�
					SV_buff[cnt*8+5].SUB_NO |= BIT_15;			//��\���̐ݒ�
				}
				else {
					if(SEQ_055_SV & wk2b){						//�i�p��ϑI������H
						/*��ϐݒ�*/
						SV_buff[cnt*8+4].SUB_NO |= BIT_15;		//��\���̐ݒ�
						SV_buff[cnt*8+5].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
					}
					else {
						/*�p�x�ݒ�*/
						SV_buff[cnt*8+4].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
						SV_buff[cnt*8+5].SUB_NO |= BIT_15;		//��\���̐ݒ�
					}
				}
				if (PV0_SINKAKU_UPDN1 & wk2b) {					//�i�p���������͈͂ɂ��邩�H
					SV_buff[cnt*8+4].B_COL1 = COL_RED;			//�i�p�̔w�i�F����
					SV_buff[cnt*8+5].B_COL1 = COL_RED;			//�i�p(���)�̔w�i�F����
				}
				else {
					SV_buff[cnt*8+4].B_COL1 = COL_LBULE;		//�i�p�̔w�i�F�����F
					SV_buff[cnt*8+5].B_COL1 = COL_LBULE;		//�i�p(���)�̔w�i�F�����F
				}

				/* OFF�i�p */
				if ((SEQ_PAR_151 & cBIT11)==0) {				//���Ԑi�p�@�\
					/*�p�x�ݒ�*/
					SV_buff[cnt*8+6].SUB_NO &= ~BIT_15;			//�\���̐ݒ�
					SV_buff[cnt*8+7].SUB_NO |= BIT_15;			//��\���̐ݒ�
				}
				else {
					if(SEQ_059_SV & wk2b){						//�i�p��ϑI������H
						/*��ϐݒ�*/
						SV_buff[cnt*8+6].SUB_NO |= BIT_15;		//��\���̐ݒ�
						SV_buff[cnt*8+7].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
					}
					else {
						/*�p�x�ݒ�*/
						SV_buff[cnt*8+6].SUB_NO &= ~BIT_15;		//�\���̐ݒ�
						SV_buff[cnt*8+7].SUB_NO |= BIT_15;		//��\���̐ݒ�
					}
				}
				if (PV0_SINKAKU_UPDN2 & wk2b) {					//�i�p���������͈͂ɂ��邩�H
					SV_buff[cnt*8+6].B_COL1 = COL_RED;			//�i�p�̔w�i�F����
					SV_buff[cnt*8+7].B_COL1 = COL_RED;			//�i�p(���)�̔w�i�F����
				}
				else {
					SV_buff[cnt*8+6].B_COL1 = COL_LBULE;		//�i�p�̔w�i�F�����F
					SV_buff[cnt*8+7].B_COL1 = COL_LBULE;		//�i�p(���)�̔w�i�F�����F
				}
			}

			/*********	�ėp�J���̔ėp�o�͑I�����̐i�p�����J�[�\���ݒ�l���ύX����		*************/
			if ((SEQ_019_SV & cBIT1)==0) {					//۰�ض�9�`12�i�p�L��
				CSR_buff[0].SV_MAX = 4;
				CSR_buff[1].SV_MAX = 4;
				CSR_buff[2].SV_MAX = 4;
				CSR_buff[3].SV_MAX = 4;
			}
			if ((SEQ_019_SV & cBIT3)==0) {					//۰�ض�13�`16�i�p�L��
				CSR_buff[4].SV_MAX = 4;
				CSR_buff[5].SV_MAX = 4;
				CSR_buff[6].SV_MAX = 4;
				CSR_buff[7].SV_MAX = 4;
			}

			/*********	���[�V�����̐ݒ�����ɂ���Đi�p�ւ̃J�[�\���ړ����֎~���鏈��		*************/
			PV0_MOTION_INF = MOT_INF_GET();
			if (PV0_MOTION_INF) {
				for(cnt=0; cnt<8; cnt++) {
					CSR_buff[cnt].SV_MAX = 4;					//�ݒ�l��4�Ɍ��炷
					SV_buff[cnt*8+4].B_COL1 = COL_WHITE;		//ON�i�p�w�i�F����
					SV_buff[cnt*8+5].B_COL1 = COL_WHITE;		//ON�i�p(���)�w�i�F����
					SV_buff[cnt*8+6].B_COL1 = COL_WHITE;		//OFF�i�p�w�i�F����
					SV_buff[cnt*8+7].B_COL1 = COL_WHITE;		//OFF�i�p(���)�w�i�F����
				}
			}

		case 22:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�
						/*********	�ėp�J���̔ėp�o�͑I�����̐ݒ�l��������		*************/
			ROT_cam_sv(1, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 35);	//۰�ض�9
			CSR_disp_cls(142);
//V06p
			ROT_cam_sv(1, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14, 40, BIT_1, 35);	//۰�ض�9
			CSR_disp_cls(142);

			ROT_cam_sv(2, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 36);	//۰�ض�10
			CSR_disp_cls(143);
			ROT_cam_sv(3, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 37);	//۰�ض�11
			CSR_disp_cls(144);

			ROT_cam_sv(4, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 38);	//۰�ض�12
			CSR_disp_cls(145);
//V06p
			ROT_cam_sv(4, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6, 40, BIT_1, 38);	//۰�ض�12
			CSR_disp_cls(145);

			ROT_cam_sv(5, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 39);	//۰�ض�13
			CSR_disp_cls(146);
			ROT_cam_sv(6, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 40);	//۰�ض�14
			CSR_disp_cls(147);
			ROT_cam_sv(7, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 41);	//۰�ض�15
			CSR_disp_cls(148);
			ROT_cam_sv(8, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2, 41, BIT_3, 42);	//۰�ض�16
			CSR_disp_cls(149);

						/*********	�ėp�J���̔ėp�o�͑I�����̂r�v�f�[�^��������		*************/
			ROT_cam_sw(11, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0);		//۰�ض�9
//V06p
			ROT_cam_sw(11, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14);		//۰�ض�9

			ROT_cam_sw(12, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0);		//۰�ض�10
			ROT_cam_sw(13, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0);		//۰�ض�11

			ROT_cam_sw(14, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0);		//۰�ض�12
//V06p
			ROT_cam_sw(14, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6);		//۰�ض�12

			ROT_cam_sw(15, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2);		//۰�ض�13
			ROT_cam_sw(16, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2);		//۰�ض�14
			ROT_cam_sw(17, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2);		//۰�ض�15
			ROT_cam_sw(18, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2);		//۰�ض�16

						/*********	�ėp�J���̔ėp�o�͑I�����̃J�[�\���f�[�^��������		*************/
			ROT_cam_csr(0x88, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, BIT_1, 43);	//۰�ض�9
//V06p
			ROT_cam_csr(0x88, BIT_0, SV_CAMNA8_C1, ~SEQ_PAR_113, BIT_14, BIT_1, 43);	//۰�ض�9

			ROT_cam_csr(0x89, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, BIT_1, 44);	//۰�ض�10
			ROT_cam_csr(0x8A, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, BIT_1, 45);	//۰�ض�11

			ROT_cam_csr(0x8B, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, BIT_1, 46);	//۰�ض�12
//V06p
			ROT_cam_csr(0x8B, BIT_0, SV_CAMNAB_C1, ~SEQ_PAR_113, BIT_6, BIT_1, 46);	//۰�ض�12

			ROT_cam_csr(0x8C, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2, BIT_3, 47);	//۰�ض�13
			ROT_cam_csr(0x8D, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2, BIT_3, 48);	//۰�ض�14
			ROT_cam_csr(0x8E, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2, BIT_3, 49);	//۰�ض�15
			ROT_cam_csr(0x8F, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2, BIT_3, 50);	//۰�ض�16

			if (GAMEN_NO == 25) {										//2014/09/02
				for(cnt=0; cnt<8; cnt++) {
					if ( (SV_buff[cnt*8+4].SUB_NO & BIT_15) &&
						 (SV_buff[cnt*8+5].SUB_NO & BIT_15) ) {			//ON�i�p�ݒ�l����\���ݒ�H
						SW_buff[cnt*3+1].SUB_NO |= BIT_15;				//ON�i�p�̒P��(���^ms)���\��
						SW_buff[cnt*3+2].SUB_NO |= BIT_15;				//OFF�i�p�̒P��(���^ms)���\��
					}
				}
			}

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//�^�ԍ�
			break;

		case 31:		//���ѐݒ�@���
//			if(OP_STATUS_DT == 00) {						//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
//				PV_cls(73, OP_STATUS_DT, 0xff);
/*** V01j
			if(OP_STATUS == 00) {							//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
				PV_cls(73, OP_STATUS, 0xff);
				CSR_disp_cls(95);
			}
********/
			if(OP_STATUS != 0x55) {							//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
				PV_cls(73, 0, 0);
				CSR_disp_cls(95);
			}
			if(MEM_ARI != 0xA5) {							//OP��(OK):A5H			V05 (INS)
				PV_cls(119, 0, 0);
			}

			if (SEQ_PAR_113 & BIT_7) {						//���ѐݒ�1-15��\���w��		V06p
				CSR_cls(126, ~SEQ_PAR_113, BIT_7);			//���ѐݒ�1-15�̔�\��
			}
			break;

		case 45:		//���ѐݒ�@�ײ�ގ����ݒ�
			if( 00 == (SEQ_PAR_101 & BIT_1) ) {				//���ѐݒ�OK�H(1:OK)
			 	SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[
			}

//2016/02/25  �o�^�{�^������
////			for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//2014/04/14
////				CSR_buff[t_no].SW6_DN = 0xff;						//��\���̐ݒ�
////				CSR_buff[t_no].SW6_SUB = 0;							//���������̐ݒ�
////			}

			break;

		case 9:			//���Y��ʁ@�T���v�����O�g�`	//V05o
		case 10:		//���Y��ʁ@�h�����h�g�`		//V05o
			LENG_svpv(120, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V06

			SV_cls(122, SEQ_PAR_103, BIT_12);						//�d�͂̔�\��		V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//�d�͂̔�\��		V06
			CSR_cls(122, SEQ_PAR_103, BIT_12);						//�d�͂̔�\��		V06
			SW_cls(122, SEQ_PAR_103, BIT_12);						//�d�͂̔�\��		V06a

			SV_cls(125, ~SEQ_PAR_103, BIT_10);						//�^�b�`�ʒu�������o��\��		V06p
			CSR_cls(125, ~SEQ_PAR_103, BIT_10);						//�^�b�`�ʒu�������o��\��		V06p

			LENG_svpv(127, SYO_LNG_CNT);				//�����_�̕ύX(�ݒ�l&�����l)  �ײ�ޏ���^����	V06p(INS)
			SV_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			PV_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			CSR_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			SW_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)

			break;

		case 44:		//���ѐݒ�@�׏d�v�ݒ�			//V05r
			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r
			break;

		case 66:		//���Y��ʁ@�g�����h			//V05o
		case 104:		//���Y��ʁ@�g�����h			//V06l
			LENG_svpv(120, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			LENG_svpv(127, SYO_LNG_CNT);				//�����_�̕ύX(�ݒ�l&�����l)  �ײ�ޏ���^����	V06p(INS)
			SV_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			PV_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			CSR_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)
			SW_cls(127, ~SEQ_PAR_113, BIT_5);			//�ײ�ޏ���^����	V06p(INS)

//2014/03/14	--------------------------------------------------------------------------------------------
			if (SV_KAJAREA_SEL == 1) {								//�ŏ��l
				wk2b = BIT_1;
			}
			else if (SV_KAJAREA_SEL == 2) {							//�U��
				wk2b = BIT_2;
			}
			else {													//�ő�l
				wk2b = BIT_0;
			}
			SW_cls(134, wk2b, BIT_0);								//�׏d�v����۰�ލő�l
			SW_cls(135, wk2b, BIT_1);								//�׏d�v����۰�ލŏ��l
			SW_cls(136, wk2b, BIT_2);								//�׏d�v����۰�ސU��
//--------------------------------------------------------------------------------------------------------------
			
			break;

		case 67:		//���Y��ʁ@�T���v�����O		//V05r
		case 105:		//���Y��ʁ@�T���v�����O		//V06l
			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r
			break;

		case 101:		//�f�[�^�ݒ��ʁ@���U�@�\�ݒ�	//V05r
			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r
			break;

		case 15:		//�ݒ��ʁ@�^�ް��Ǘ�		//V06p
			for(wk2b=1; wk2b<41; wk2b++) {
				SW_buff[wk2b].SUB_NO |= BIT_15;						//��]/���]/�U�q/�㉝���͈�U�S�Ĕ�\���Ƃ���B
			}
			break;

		case 108:		//�@��������ݒ���		//V06p
			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX
			break;

		case 109:		//�J���o�͎������Z���		//SIT4-MC		2014/08/26
//2015/01/26			SV0_RELE_POS	= GMN_PAR051*10;		//�����[�X����
			SV0_RELE_POS	= cnv_mm_inch(GMN_PAR051*10, 0);		//�����[�X����
			SV0_RELE_SNO0	= GMN_PAR052;			//�����[�X�J���I���s��
			SV0_RELE_AGL0	= GMN_PAR053;			//�����[�X�J���I���p�x
			SV0_RELE_SNO1	= GMN_PAR054;			//�����[�X�J���I�t�s��
			SV0_RELE_AGL1	= GMN_PAR055;			//�����[�X�J���I�t�p�x
			SV0_RELE_CAM	= GMN_PAR056;			//�����[�X�J���ݒ�Ώ�

//2015/01/26			SV0_SEND_POS	= GMN_PAR057*10;		//���荂��
			SV0_SEND_POS	= cnv_mm_inch(GMN_PAR057*10, 0);		//���荂��
			SV0_SEND_SNO0	= GMN_PAR058;			//����J���I���s��
			SV0_SEND_AGL0	= GMN_PAR059;			//����J���I���p�x
			SV0_SEND_SNO1	= GMN_PAR060;			//����J���I�t�s��
			SV0_SEND_AGL1	= GMN_PAR061;			//����J���I�t�p�x
			SV0_SEND_CAM	= GMN_PAR062;			//����J���ݒ�Ώ�

			SV0_TIMING_SNO0	= GMN_PAR063;			//�^�C�~���O�J���I���s��
			SV0_TIMING_AGL0	= GMN_PAR064;			//�^�C�~���O�J���I���p�x
			SV0_TIMING_SNO1	= GMN_PAR065;			//�^�C�~���O�J���I�t�s��
			SV0_TIMING_AGL1	= GMN_PAR066;			//�^�C�~���O�J���I�t�p�x
			SV0_TIMING_CAM	= GMN_PAR067;			//�^�C�~���O�J���ݒ�Ώ�

			if (GMN_PAR078 != 0) {							//�J���ԍ��ݒ�\�i0�F�A1�F�s�j
				for (wk2b=0; wk2b<SV_CNT; wk2b++) {
					if (SV_buff[wk2b].GRP_NO == 137) {		//�J���ݒ�
						SV_buff[wk2b].SUB_NO |= BIT_15;		//�J���ݒ��\��
					}
				}
				for (wk2b=0; wk2b<3; wk2b++) {
					CSR_buff[wk2b].SV_MAX--;				//�ݒ�l�������炷
				}
			}
			else {
				for (wk2b=0; wk2b<PV_CNT; wk2b++) {
					if (PV_buff[wk2b].GRP_NO == 137) {		//�J���l��\��
						PV_buff[wk2b].SUB_NO |= BIT_15;		//
					}
				}
			}

			LENG_svpv(141, SYO_LNG_CNT);					//�����_�̕ύX(�ݒ�l&�����l)			2014/12/23

			break;

		case 54:		//�J��Ԃ��^���̈� �ݒ���			2014/09/22
			SV_cls(138, SV0_REP_FIX_FLG, BIT_0);			//Ӱ��݌J��Ԃ�
			PV_cls(138, SV0_REP_FIX_FLG, BIT_0);			//Ӱ��݌J��Ԃ�
			CSR_cls(138, SV0_REP_FIX_FLG, BIT_0);			//Ӱ��݌J��Ԃ�
			SW_cls(138, SV0_REP_FIX_FLG, BIT_0);			//Ӱ��݌J��Ԃ�

			SV_cls(139, SV0_REP_FIX_FLG, BIT_1);			//��葬�x�̈�
			PV_cls(139, SV0_REP_FIX_FLG, BIT_1);			//��葬�x�̈�
			CSR_cls(139, SV0_REP_FIX_FLG, BIT_1);			//��葬�x�̈�
			SW_cls(139, SV0_REP_FIX_FLG, BIT_1);			//��葬�x�̈�

//2014/12/22
			for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {
				if(SV_buff[t_no].GRP_NO == 139) {				//��ٰ�ߔԍ� ���
					if( (SV_buff[t_no].SUB_NO == 145) || (SV_buff[t_no].SUB_NO == 147) ) {	//���ٰ�ݔԍ� ���
						SV_buff[t_no].TEN_POS = SYO_LNG_CNT;				//�����_�̈ʒu �ύX
					}
				}
			}

			break;

		case 53:		//�X���C�h�����ҋ@					//2014/12/22
			LENG_svpv(140, SYO_LNG_CNT);					//�����_�̕ύX(�ݒ�l&�����l)
			break;

	}
}


/*
********************************************************************************
*  Module Name:		win_tbl_set
*  Function Name:	����޳��ʂ̏��ð��ق̔�\������(�쐬)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-07-10
********************************************************************************
*/
void	win_tbl_set(void)
{
	UNs	wk2b;

	switch(WINDOW_NO) {
		default:
		case 1:			//���Y��ʁ@���Y�ݒ�
		case 2:			//���Y��ʁ@�P�x�ݒ�
		case 3:			//���Y��ʁ@�޲��ݽ�\��
		case 4:			//���Y��ʁ@���ݽ����
		case 7:			//�i���ʁ@���ݻ���͒���
//2014/12/23		case 8:			//�i���ʁ@�޲����ݒ���
		case 9:			//�i���ʁ@�޲����݈��͒���
		case 10:		//�i���ʁ@�޲��ݽ�\��
		case 11:		//�i���ʁ@���ݽ����
//2016/04/22		case 12:		//�i���ʁ@�ï�����
//2016/04/22		case 13:		//�i���ʁ@�޲����ݑ���
//V01m		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
//V01m		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
//2016/04/22		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
//2016/04/22		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
//2016/04/22		case 18:		//�i���ʁ@MB�I�𑀍�
			break;

		case 05:		//���Y��ʁ@���Y�ݒ蒆�^
			EJE_grp(1,  2,  BIT_8,  SEQ_017_SV, BIT_4, 32, SEQ_017_SV, BIT_6, 0);	//�G�W�F�N�^�P
			EJE_grp(22, 23, BIT_9,  SEQ_017_SV, BIT_7, 33, SEQ_017_SV, BIT_9, 0);	//�G�W�F�N�^�Q
			EJE_grp(24, 25, BIT_10, SEQ_017_SV, BIT_10,34, SEQ_017_SV, BIT_12,0);	//�G�W�F�N�^�R
			EJE_grp(26, 27, BIT_11, SEQ_017_SV, BIT_13,35, SEQ_017_SV, BIT_15,0);	//�G�W�F�N�^�S
			EJE_grp(28, 29, BIT_12, SEQ_018_SV, BIT_0, 36, SEQ_018_SV, BIT_2, 0);	//�G�W�F�N�^�T
			EJE_grp(30, 31, BIT_13, SEQ_018_SV, BIT_3, 37, SEQ_018_SV, BIT_5, 0);	//�G�W�F�N�^�U

			EJE_sw(19, SEQ_017_SV, BIT_4);						//�G�W�F�N�^�P
			EJE_sw(20, SEQ_017_SV, BIT_7);						//�G�W�F�N�^�Q
			EJE_sw(21, SEQ_017_SV, BIT_10);						//�G�W�F�N�^�R
			EJE_sw(22, SEQ_017_SV, BIT_13);						//�G�W�F�N�^�S
			EJE_sw(23, SEQ_018_SV, BIT_0);						//�G�W�F�N�^�T
			EJE_sw(24, SEQ_018_SV, BIT_3);						//�G�W�F�N�^�U

			EJE_csr(0x91, SEQ_017_SV, BIT_4, SEQ_017_SV, BIT_6, 62);				//�G�W�F�N�^1
			EJE_csr(0x92, SEQ_017_SV, BIT_7, SEQ_017_SV, BIT_9, 63);				//�G�W�F�N�^2
			EJE_csr(0x93, SEQ_017_SV, BIT_10,SEQ_017_SV, BIT_12,64);				//�G�W�F�N�^3
			EJE_csr(0x94, SEQ_017_SV, BIT_13,SEQ_017_SV, BIT_15,65);				//�G�W�F�N�^4
			EJE_csr(0x95, SEQ_018_SV, BIT_0, SEQ_018_SV, BIT_2, 66);				//�G�W�F�N�^5
			EJE_csr(0x96, SEQ_018_SV, BIT_3, SEQ_018_SV, BIT_5, 67);				//�G�W�F�N�^6

			MIS_csr(14, SEQ_016_SV, BIT_2, 91, 0);				//�I�[�o�[���[�h���~�b�g	/* V01l */

			break;

		case 06:		//�i���ʁ@�ײ�ޒ���
//V01m			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_SUR_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(52, SYO_LNG_SUR_CNT);								//�����_�̕ύX(�ݒ�l&�����l) V01m(INS)

			DANsel_csr(67, SEQ_020_SV, BIT_4, 78);					//�X���C�h����

			if(0x0030 == (SEQ_020_SV & 0x0070)){					//�ײ�ގ������߂������Žײ�ޗL���޲ʲĕ\���L��
				DANsel_csr(70, SEQ_020_SV, BIT_6, 84);				//�X���C�h��������
				PV_cls(54, SEQ_020_SV, BIT_6);						//�_�C�n�C�g�P��
				SV_cls(19, SEQ_020_SV, BIT_6);						//�_�C�n�C�g�ݒ�l
				CSR_disp_cls(85);
				CSR_disp_cls(86);
				CSR_disp_cls(87);
			}
			break;

		case 8:			//�i���ʁ@�޲����ݒ���			2014/12/23
			LENG_svpv(76, SYOD_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			break;

		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���			V01m
		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F		V01m
			ADC_NEXT_cls();									//2016/04/22
			LENG_svpv(19, SYO_LNG_SUR_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			break;

		case 19:		//���Y��ʁ@���Y�ݒ�2
			SYS_MISSEL_SV = SEQ_024_SV;								//н̨���7�`8 �ێ�/�r�o�@����߰
			SYS_MISSEL_SV <<= 6;
			SYS_MISSEL_SV |= (SEQ_023_SV >> 10);					//н̨���1�`6 �ێ�/�r�o�@����߰

			MIS_sv(46, SEQ_018_SV, BIT_8);							//�~�X�t�B�[�h�P
			MIS_sv(47, SEQ_018_SV, BIT_9);							//�~�X�t�B�[�h�Q
			MIS_sv(48, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�R
			MIS_sv(49, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�S
			MIS_sv(103, SEQ_018_SV, BIT_11);						//�~�X�t�B�[�h�T	/* V01d */
			MIS_sv(104, SEQ_018_SV, BIT_11);						//�~�X�t�B�[�h�U	/* V01d */

			EJE_sw(25, SEQ_018_SV, BIT_8);							//�~�X�t�B�[�h�P
			EJE_sw(26, SEQ_018_SV, BIT_9);							//�~�X�t�B�[�h�Q
			EJE_sw(27, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�R
			EJE_sw(28, SEQ_018_SV, BIT_10);							//�~�X�t�B�[�h�S
			EJE_sw(57, SEQ_018_SV, BIT_11);							//�~�X�t�B�[�h�T	/* V01d */
			EJE_sw(58, SEQ_018_SV, BIT_11);							//�~�X�t�B�[�h�U	/* V01d */

			MIS_csr(15, SEQ_018_SV, BIT_8, 68, 0);					//�~�X�t�B�[�h�P
			MIS_csr(16, SEQ_018_SV, BIT_9, 69, 0);					//�~�X�t�B�[�h�Q
			MIS_csr(17, SEQ_018_SV, BIT_10,70, 0);					//�~�X�t�B�[�h�R
			MIS_csr(18, SEQ_018_SV, BIT_10,71, 0);					//�~�X�t�B�[�h�S
			MIS_csr(79, SEQ_018_SV, BIT_11,66, 0);					//�~�X�t�B�[�h�T	/* V01d */
			MIS_csr(80, SEQ_018_SV, BIT_11,67, 0);					//�~�X�t�B�[�h�U	/* V01d */

			MIS_csr(14, SEQ_016_SV, BIT_2, 91, 0);				//�I�[�o�[���[�h���~�b�g	/* V01l */

			MISS_swcara_win();										//�~�X�t�B�[�h�r�v�\���L�����؂芷��
			break;

		case 20:		//���Y��ʁ@�␳���j�^		/* V01w */
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			
//2014/12/23			LENG_svpv(117, SYO_LNG_CNT);							//�����_�̕ύX(�ݒ�l&�����l) V05h
			LENG_svpv(117, SYO_LNG_SUR_CNT);						//�����_�̕ύX(�ݒ�l&�����l)

			KAJ_svpv(53, SYO_KAJ_CNT);								//�׏d�̏����_�ύX	V05r

//2010/09/23			PV_cls(121, SEQ_PAR_107, BIT_7);						//���ח������̔�\��	//V06
//2010/09/23			wk2b = ~SEQ_PAR_107;
//2010/09/23			PV_cls(122, wk2b, BIT_7);								//�d�͗ʎ����̔�\��	//V06
			PV_cls(121, ~SEQ_PAR_103, BIT_12);						//���ח������̔�\��	//V06
			PV_cls(122, SEQ_PAR_103, BIT_12);						//�d�͗ʎ����̔�\��	//V06
			break;

		case 22:		//�f�[�^�ݒ��ʁ@���Ēl�C��	/* V06b */
			SV_cls(50, SEQ_016_SV, BIT_12);							//ۯĶ���1�̔�\��
			CSR_cls(50, SEQ_016_SV, BIT_12);						//ۯĶ���1�̔�\��
			SV_cls(51, SEQ_016_SV, BIT_14);							//ۯĶ���2�̔�\��
			CSR_cls(51, SEQ_016_SV, BIT_14);						//ۯĶ���2�̔�\��
			break;

		case 23:		//���Y��ʁ@���Y�Ǘ�		/* V06c */
			wk2b = 0;
			if (SV_WORKER_ENT_FLG == 0x5aa5) {
				wk2b = BIT_0;
			}
			PV_cls(123, wk2b, BIT_0);						//��ƎҺ��ނ̔�\��
			break;

		case 12:		//�i���ʁ@�ï�����						//2016/04/22
		case 13:		//�i���ʁ@�޲����ݑ���					//2016/04/22
		case 18:		//�i���ʁ@MB�I�𑀍�						//2016/04/22
			ADC_NEXT_cls();
			break;

		case 16:		//�i���ʁ@�޲����ݒ��ߑ���				//2016/04/22
			ADC_NEXT_cls();
			LENG_svpv(76, SYOD_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			if((SEQ_019_SV & BIT_14) == 0) {
				/* �E�ݒ�l�������l�폜	 */
				PV_buff[3].SUB_NO |= BIT_15;
				PV_buff[5].SUB_NO |= BIT_15;
				CSR_disp_cls(130);
			}
			break;

		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F			//2016/04/22
			ADC_NEXT_cls();
			LENG_svpv(76, SYOD_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			if((SEQ_019_SV & BIT_14) == 0) {
				/* �E�ݒ�l�������l�폜	 */
				CSR_buff[0].SV_MAX = 1;
				SV_buff[3].SUB_NO |= BIT_15;
				PV_buff[6].SUB_NO |= BIT_15;
				PV_buff[7].SUB_NO |= BIT_15;
				CSR_disp_cls(130);
				CSR_disp_cls(131);
			}
			break;
	}
}

/*
********************************************************************************
*  Module Name:		motion_csr_clr
*  Function Name:	��ݽ̧Ӱ��ݑΉ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		Ӱ��݂̂R�i�ڂ����ɶ��ق������悤�ɂ���
*
*  �� ��	:A.Shimamura		ON:2004-11-26 V01n
********************************************************************************
*/
void	motion_csr_clr(void)
{
	UNs		cnt, no;

	if (SEQ_024_SV & BIT_5)
	{														// �L���H
		for(cnt = CSR_CNT, no=0 ; cnt > 0 ; cnt--, no++ )
		{
			if(CSR_buff[no].DATA_NO != 99 )
			{												//�R�i�ځH
				CSR_buff[no].TOK_NO |= BIT_0;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EPM_TANI_CHG
*  Function Name:	�d�͗ʒP�ʐ؊���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		
*
*  �� ��	:A.Shimamura		ON:2010-10-26
********************************************************************************
*/
void	EPM_TANI_CHG(void)
{
	if (SEQ_PAR_103 & BIT_12)	//0�F���ח��^1�F�d�͗�			V06a
	{
		if (GMN_PAR137 == 1)
		{
//			SV0_EP_AVE &= ~BIT_0;		//����މ�ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE |=  BIT_1;		//����މ�ʂ̓d�͗ʂ̒P�� : Wh
//			SV0_EP_AVE &= ~BIT_4;		//Ӱ��������ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE |=  BIT_5;		//Ӱ��������ʂ̓d�͗ʂ̒P�� : Wh
			SV0_EP_AVE = BIT_1 + BIT_5;
		}
		else
		{
//			SV0_EP_AVE |=  BIT_0;		//����މ�ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE &= ~BIT_1;		//����މ�ʂ̓d�͗ʂ̒P�� : Wh
//			SV0_EP_AVE |=  BIT_4;		//Ӱ��������ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE &= ~BIT_5;		//Ӱ��������ʂ̓d�͗ʂ̒P�� : Wh
			SV0_EP_AVE = BIT_0 + BIT_4;
		}
	}
	else
	{
//		SV0_EP_AVE &= ~(BIT_4 + BIT_5);	//Ӱ��������ʂ̓d�͗ʂ̒P�ʏ����i���ח���%��\���j
		if (GMN_PAR137 == 1)
		{
//			SV0_EP_AVE &= ~BIT_0;		//����މ�ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE |=  BIT_1;		//����މ�ʂ̓d�͗ʂ̒P�� : Wh
			SV0_EP_AVE = BIT_1;
		}
		else
		{
//			SV0_EP_AVE |=  BIT_0;		//����މ�ʂ̓d�͗ʂ̒P�� : kW
//			SV0_EP_AVE &= ~BIT_1;		//����މ�ʂ̓d�͗ʂ̒P�� : Wh
			SV0_EP_AVE = BIT_0;
		}
	}
}


/*
********************************************************************************
*  Module Name:		mot_type_SWset
*  Function Name:	���[�V����TYPE�pSW�Z�b�g
*  Input	:		�擪�^No.
*  Return	: 		�Ȃ�
*  Note		:		
*
*  �� ��	:A.Shimamura		ON:2013-02-18		V06p
********************************************************************************
*/
void	mot_type_SWset(UNs ktop)
{
	UNl		adr;
	UNs		i, *type, bit;

	adr = KATA_DATA_ADR_TOP;
	if (ktop>100) {
		adr += 0x180000;					//�^No.101����TOP�A�h���X�ς��B
		ktop -= 100;
	}
	adr = adr + (ktop-1) * 0x800;
	adr += (0x534-0x500);						//��]�������i�[����Ă���A�h���X
	bit = BIT_0;
	PV0_KATRD_BIT = 0;

	for (i=0; i<10; i++, bit<<=1) {
		type = (UNs *)adr;
		if (*type & BIT_0) {
			/* ��] */
			SW_buff[1+i*4+0].SUB_NO &= ~BIT_15;		//��]�\���Z�b�g
		}
		else if (*type & BIT_1) {
			/* ���] */
			SW_buff[1+i*4+1].SUB_NO &= ~BIT_15;		//���]�\���Z�b�g
			if ((SEQ_024_SV & BIT_2) ==0) {		//���]�d�lOFF�H
				PV0_KATRD_BIT |= bit;			//���]�\���̔w�i�ύX�i�ǂ߂Ȃ���B�j
			}
		}
		else if (*type & BIT_2) {
			/* �U�q */
			SW_buff[1+i*4+2].SUB_NO &= ~BIT_15;		//�U�q�\���Z�b�g
			if ( ((SEQ_023_SV & BIT_8) ==0) || (SEQ_PAR_113 & BIT_15) ) {		//�U�q�d�lOFF�H or �U�q��\���w��ON
				PV0_KATRD_BIT |= bit;			//�U�q�\���̔w�i�ύX�i�ǂ߂Ȃ���B�j
			}
		}
		else if (*type & BIT_3) {
			/* �㉝�� */
			SW_buff[1+i*4+3].SUB_NO &= ~BIT_15;		//�㉝���\���Z�b�g
			if ((SEQ_023_SV & BIT_9) ==0) {		//�㉝���d�lOFF�H
				PV0_KATRD_BIT |= bit;			//�㉝���\���̔w�i�ύX�i�ǂ߂Ȃ���B�j
			}
		}
		adr += 0x800;
	}
}


//	***********************************************************
//	***														***
//	***			�i�p���Z�\�^�s�\						***
//	***	��]�E�ӂ肱�őҋ@�_�ȊO�Œ�~����(�t�]�܂�)		***
//	***	���]�őҋ@�_�ȊO�A�Ŏ��_�ȊO�Œ�~����(�t�]�܂�)	***
//	***														***
//	***********************************************************
//	0:�i�p���Z�\
//	1:�s�\
U2b		MOT_INF_GET(void)
{
	U2b	*srvdeg;
	U2b	*srvtim;

	U2b	stepmax;
	U2b	dig_n1,dig_n,dig_last;
	U2b	dir=0;
	U2b	olddir=0;
	U2b	tim_n;

	U2b	stopcnt=0;
	U2b	stopcntmax;
	U2b	ans=0;
	int	i;

	dig_n1	= SV_TAIKIKAKU_SRV;	//���Ēn�_
	dig_n	= SV_TAIKIKAKU_SRV;	//

	stepmax	= SV_DANSUU_SRV+1;
	if((1<stepmax)&&(stepmax<=11)){//1~10��2~11
		if(SEQ_050_SV & BIT_1) {//���]
			dig_last	=dig_n1;//�ҋ@�_�ɖ߂�
			stopcntmax	=1;	//���]�̏ꍇ�P��͕K�����݂���
	    }else{
			if(SEQ_050_SV & BIT_2) {//�ӂ肱
				dig_last=3600-dig_n1;	//180.0-taiki+180.0
			}else{//��]
				dig_last=dig_n1+3600;	//370.0�x�ł��ǂ�
			}
			stopcntmax	=0;	//��]�E�ӂ肱�ł͑��݂��Ȃ�
		}

		srvdeg	= &SV_1DANDEG_SRV;	//
		srvtim	= &SV_1DANTIM_SRV;
		tim_n	=0;			//�ŏ��̍s����0�Ƃ��� 2�s���̂Ƃ���1�s������ς�1��2�s���̕�����]������

		for(i=0;i<stepmax;i++){
			dig_n1	=dig_n;
			if(i==(stepmax-1)){//�Ō�
				dig_n	=dig_last;
			}else{
				dig_n	=srvdeg[i];
			}
			if(dig_n1!=dig_n){//�p�x���قȂ�
				if(dig_n1<dig_n){
					dir=0;//���]
				}else{
					dir=1;//�t�]
				}
			}
			if((olddir!=dir)||(tim_n!=0)){//��ς�0�ȊO�@�܂��́@�ɐ�������
				stopcnt++;
			}
			olddir	=dir;
			tim_n	=srvtim[i];//�߂�s������ς͕]������Ȃ�
		}
	}

	if(stopcntmax<stopcnt){
		ans=1;//��~�L��=>�i�p�ݒ�s��
	}

	return(ans);//


}


/*
********************************************************************************
*  Function Name:	�����i�ʒu�^�׏d�j�ؑ֕\���Ȃ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		
*
*  �� ��	:A.Shimamura		ON:2015-01-15
********************************************************************************
*/
void	mark_chg_no_disp(void)
{
	UNs		cnt, t_no;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].AKI == 100) {				//��ٰ�ߔԍ� ���
			CSR_buff[t_no].SW56_UP = 98;			//�ڕW�ʒu
			CSR_buff[t_no].SW6_DN  = 0xff;
		}
		if(CSR_buff[t_no].AKI == 101) {				//��ٰ�ߔԍ� ���
			CSR_buff[t_no].TOK_NO |= BIT_0;			//�׏d�����͈� ���ٔ�\���̐ݒ�
		}
	}
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].AKI2 == 101) {				//��ٰ�ߔԍ� ���
			SV_buff[t_no].SUB_NO |= BIT_F;			//�׏d�����͈� ��\�����
		}
	}
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].AKI2 == 101) {				//��ٰ�ߔԍ� ���
			PV_buff[t_no].SUB_NO |= BIT_F;			//�׏d�����͈� ��\�����
		}
	}
}


/*** END ***/
