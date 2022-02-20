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

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "dp_cpuab.h"							//DPRAM�Q�ƕϐ���`
#include "ssa_opram.h"							//OPRAM�Q�ƕϐ���`
#include "ssc_wrmh.h"							//work ram �Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	RULET_GAMEN_INIT(void);			//ٰگĕ\���̏�����
//extern	void	GRAPH_INIT(void);				//�O���t�`�揉������
//extern	void	GRAPH_DISP(void);				//�O���t�`�揈��

/* �O���Q�ƕϐ���` -------------------------------------------------- */
	extern	UNs	SV_SEQDT2_A91_INI;				//�V�[�P���X���j�^�ݒ�Q /* V00p */
	extern	UNs	SV_INTER_VER2;					// ����۰�����ް�ޮ�	(121.15-140.0~15���Ԃ�) /* V00p */

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
void	GAMEN_disp(void)
{
	GGAMEN_DISP_FLG = 0xff;					//��ʕ\�����䒆�t���O�n�m
	SVPV_LCD_FLG = 0xff;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

//	Lcd_off();								//���OFF

	GAMEN_base_disp();						//�x�[�X��ʕ\��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	SVdata_disp();							//�ݒ�l���@�\��
	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	PVdata_disp_all();						//�S�@�����l���@�\��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	SWchg_disp();							//�r�v�f�[�^���@�\��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	DISP_after();							//��ʕ\���̌㏈��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	if(CSR_FLG == 5){
	}
	else{
		CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
	}
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�
	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	DISP_after_csr();						//��ʕ\���̃J�[�\���㏈��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��	deb
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��	deb

	WDT_Rifresh();							//�����ޯ����- ��گ��

	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
	Lcd_all(01, E_gmen_bf, &LCD_WORK2[0][0][0]);	//�S�\��

	Lcd_on();								//���ON

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
	GGAMEN_DISP_FLG = 0x00;					//��ʕ\�����䒆�t���O�n�e�e

}


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
	disp_all_s(WINDOW_NO, i, 0x00);			//�S��ʕ\���p�������ށ��ޯĕϊ�

	Wintbl_set();							//����޳��ʂ̏��ð��ق̍쐬

	SVdata_disp();							//�ݒ�l���@�\��
	PVdata_disp_all();						//�S�@�����l���@�\��
	SWchg_disp();							//�r�v�f�[�^���@�\��

	DISP_cam_csr_name();					//�J���J�[�\�����̕\��

	WIN_disp_after2();						//����޳��ʕ\���̌㏈��2

	CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

//	WIN_disp_after_csr();					//��ʕ\���̃J�[�\���㏈���@(Sit-S�ł͕K�v�Ȃ�)

	Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

	WDT_Rifresh();							//�����ޯ����- ��گ��

	for( i=6 ; i < 15 ; i++ ) {
		Lcd_line(00, i, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
		Lcd_line(01, i, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)
	}

	SVPV_LCD_FLG = 0x00;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)

}


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
void	GAMEN_base_disp(void)
{

	GAMEN_no_chg();						//��ʂm���D�ύX
	GAMEN_cls();						//��ʃf�[�^�N���A

	disp_all_s(GAMEN_NO, 0x00, 0x00);	//�S��ʕ\���p�������ށ��ޯĕϊ�

	WDT_Rifresh();						//�����ޯ����- ��گ��

	Alltbl_set();						//���ð��ق̍쐬

}


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

	dst1_p= &LCD_WORK1[0][0][0];		//�̈�N���A(�\��ܰ��̈�LCD1)
	dst2_p= &LCD_WORK2[0][0][0];		//�̈�N���A(�\��ܰ��̈�LCD2)
	size = (sizeof(LCD_WORK1) >> 1);
	while(size--) {
		*dst1_p++ = 0x0000;				//�̈�R�s�[
		*dst2_p++ = 0x0000;				//�̈�R�s�[
	}

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

	SEQ_PAR_051 = 0;
	SEQ_PAR_052 = 0;
	SEQ_PAR_054 = 0;

	RULET_HIGH_FLG = 0x055;				/* �������[���b�g�`��t���O�N���A */

	CSR_DAN_CSR_LST = 0x0FF;			/* �i�����SW56���ݽ��ݾٗp */

	SW56_MUSK_FLG = 0x0404;
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

	CSR_disp_off();						//�J�[�\���\������

	memset_word(&LCD_WORK2[6][0][0], 0x0000, 9*16*40);	//����ʂ̃��[���b�g�\�������N���A����

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
			switch(SW14_ON1_FLG) {
				default:
					SW14_ON1_FLG = 0;
				case 0000:							//�O�񉽂��̃L�[�������ꂢ�����H
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
			if(SW14_ON6_FLG < 11){
				if(SW14_ON6_FLG == 0){				//�O�񉽂�������Ă��Ȃ��H
					CSR_FLG_CNT = 1;				//�J�[�\���ԍ��Z�b�g
				}
				else{
					CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
					CSR_FLG_CNT = (SW14_ON6_FLG & 0x00ff);	//�J�[�\���ԍ��Z�b�g
					CSR_FLG_CNT --;
				}
			}
			else{
				CSR_FLG = 5;						//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = CSR_FLG_CNT_LST;		//�J�[�\���ԍ��Z�b�g
			}

			SV_FLG_CNT = 0;							//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 0;							//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�J�[�\���ړ�

			SW16data_onset(0xff, 05);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			if(CSR_FLG_CNT == 1 &&					//�X���C�h����
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
	UNs		*bf_p, i, j;
	UNb		wk[8];
	UNs		xy_wk;

	switch(GAMEN_NO) {
		default:
		case 2:			//���Y��ʁ@���^��{(���g�p)
		case 11:		//�ݒ��ʁ@�ް��ݒ�
		case 18:		//�ݒ��ʁ@�ް��ݒ�I�𒆌^
		case 24:		//�ݒ��ʁ@н̨��޶с@NO/NC�ݒ�
		case 25:		//�ݒ��ʁ@۰�ضс@17�`20�ݒ�
		case 27:		//�ݒ��ʁ@���ײݶѐݒ�
		case 42:		//���щ�ʁ@���x���B�ް��ݒ�
		case 46:		//���щ�ʁ@��߼�ݍ\���ް����
		case 47:		//���щ�ʁ@�޲����ݎ�������(��)
		case 48:		//���щ�ʁ@�޲����ݎ�������(�E)
		case 49:		//���щ�ʁ@���ݻ���͒���
		case 53:		//���щ�ʁ@���ײݎd�l�ݒ���
		case 54:		//���щ�ʁ@�ް�۰�މ��
			break;

		case 1:			//���Y��ʁ@��{
			RULET_DISP_FLG = 0xff;			//���[���b�g�\��(00:�Ȃ��^55:����޳�\���^FF:�ʏ�\��)
			DEG_DISP_FLG = 0xff;			//�p�x�\���t���O(00:�Ȃ��^FF:����)
			SEISAN_DISP_FLG = 0xff;			//���Y�̍s���\��(00:�Ȃ��^FF:����)
			INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)

			RULET_GAMEN_INIT();				//ٰگĕ\���̏�����

			CSR_MOVE_OK_FLG = 0xff;			//���وړ��׸�(00:�ړ��^FF:�֎~)

			SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)

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

			SV_DANSUU_SRV_BAK = 5;				//�����l
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

				SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//�@�\�I��3(���Y���l�ݒ�@1:�L)
					SV_CNT = 00;
//V01d					CSR_CNT = 00;
					CSR_CNT = 02;
				}
			}
			else{					//�ݒ��ʁ@Ӱ��ݐݒ�
				SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)

				DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

				EJE_GAMEN_NON = 0;				//�G�W�F�N�^ �L
				if(00 == EJE_check()) {			//�G�W�F�N�^�L���`�F�b�N
					EJE_GAMEN_NON = 0xff;		//�G�W�F�N�^ ��
				}
				MIS_GAMEN_NON = 0;				//�~�X�t�B�[�h �L
				if(00 == MIS_check()){			//�~�X�t�B�[�h�L���`�F�b�N
					MIS_GAMEN_NON = 0xff;		//�~�X�t�B�[�h ��
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
			}
			break;

		case 4:			//���Y��ʁ@����Ӱ���
		case 29:		//�ݒ��ʁ@����Ӱ���
			CSR_MOVE_OK_FLG = 0xff;			//���وړ��׸�(00:�ړ��^FF:�֎~)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			if(GAMEN_NO == 4){		//���Y��ʁ@����Ӱ���
				INTROCK_DISP_FLG = 0xff;		//�K�C�_���X�\��(00:�Ȃ��^FF:����)
				SEQ_PAR_051 = BIT_0;			//���Y��ʕ\��(1:�\����)

				if( 00 == (SEQ_PAR_107 & BIT_2) ) {	//�@�\�I��3(���Y���l�ݒ�@1:�L)
					SV_CNT = 00;
					CSR_CNT = 00;
				}
			}
			else{					//�ݒ��ʁ@����Ӱ���
				SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)

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

			SEQ_PAR_051 = BIT_1;			//�^�i���ʕ\��(1:�\����)
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
			SEQ_PAR_051 = BIT_2;					//�ް��ݒ��ʕ\��(1:�\����)
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

			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)

			MLD_100_FLG = 0;					//�^�Ǘ� 1�`10���L��
			if( SEQ_025_SV & BIT_15 ) {			//�^�ް�1�`100���L���@�H
				MLD_100_FLG = 0xaa;				//�^�Ǘ� 1�`100���L��
			}
												//�J�[�\���\���ʒu����
			if(CSR_POS_G15 == 0xff){			//�^�f�[�^�Ǘ���ʂ̃J�[�\���\���ʒu�͌��݂̌^�f�[�^�̏ꏊ
				CSR_FLG = 5;					//�J�[�\���\���ʒu�w��
				i = PV_MLDNO1_F1;				//���݂̌^�ԍ�

				if(MLD_100_FLG != 0xaa){		//�^�Ǘ� 1�`100���L���H
					if( i > 10 ) {
						i = 1;
					}
				}
				if( i > 100 || i == 0 ) {
					i = 1;
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

			PV_MLDMES_C1 = 0;
			SWchg_disp();					//�r�v�f�[�^���@�\��

											//MLD100 �^�Ǘ��ԍ��\���f�[�^�쐬
			i = (MLD_100_GNO * 10);
			i ++;
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

			if(MLD_100_GNO == 0){
				SW56_dncara_disp(0xff, 2);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 10);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)

				if(MLD_100_FLG != 0xaa){		//�^�Ǘ� 1�`100���L���H
					SW56_dncara_disp(0xff, 3);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
					SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				}
			}
			else if(MLD_100_GNO == 9){
				SW56_dncara_disp(0xff, 3);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
				SW56_dncara_disp(0xff, 11);	//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
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

			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)
			DATA_svsw(SEQ_PAR_101,BIT_0);	//�ް��ݒ�OK(1:OK)
			break;

		case 17:		//�ݒ��ʁ@�ް��ݒ蒆�^
			CSR_FLG = 0;				//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = 1;			//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;				//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;				//�r�v�ԍ��Z�b�g

			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)

			SEQ_PAR_051 = BIT_2;		//�ް��ݒ��ʕ\��(1:�\����)

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

			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)

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

			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)

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

		case 21:		//�ݒ��ʁ@۰�ض�1�`8�ѐݒ�
			GAMEN_NO_CAM = 21;

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

			SEQ_PAR_051 = BIT_2;						//�ް��ݒ��ʕ\��(1:�\����)

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

		case 22:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�
			GAMEN_NO_CAM = 22;

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

			SEQ_PAR_051 = BIT_2;				//�ް��ݒ��ʕ\��(1:�\����)

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
			wk[0] = PVP_CB_B_VER[0];							//CPU-B VER. No.
			wk[1] = PVP_CB_B_VER[1];
			wk[2] = PVP_CB_B_VER[2];
			wk[3] = PVP_CB_B_VER[3];
			wk[4] = PVP_CB_B_VER[4];
			wk[5] = PVP_CB_B_VER[5];
			memcpy_word(&PV_CBBVER_A1[0], (UNs *)&wk[0], 3);	//����ް�ޮ݂��߰

			//��߼�ݥ�ް�ޮ݁F�\����=2(HEX�ް�)
			PV_OPCVER_A1[0] = OP_VER;								//Option Ver

/* V00p */
			//�������ް�ޮݷ�׸��F�\����=1(ASCII�ް�)
			PV0_PAR_A_CHAR = PVP_PAR_A_CHAR << 8;
			PV0_PAR_B_CHAR = PVP_PAR_B_CHAR << 8;
			PV0_TBL_A_CHAR = PVP_TBL_A_CHAR << 8;
			PV0_TBL_B_CHAR = PVP_TBL_B_CHAR << 8;
			PV0_DEFULT_VER2 = SV_SEQDT2_A91_INI << 8;
			PV0_INTER_VER2 = SV_INTER_VER2 << 8;
			PV0_SEQ_VER2 = SEQ_PAR_198 << 8;

			break;

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
		case 43:		//���ѐݒ�@�����ѥ��ϐݒ�
		case 44:		//���ѐݒ�@�׏d�v�ݒ�
		case 45:		//���ѐݒ�@�ײ�ގ����ݒ�
		case 50:		//���ѐݒ�@�ޯ������ް��ݒ�
		case 51:		//���ѐݒ�@C/B���ђ萔2
		case 55:		//���щ�ʁ@�d�l�ݒ�7
		case 56:		//���щ�ʁ@�d�l�ݒ�8
		case 57:		//���ѐݒ�@�������Ұ�3
		case 58:		//���ѐݒ�@�������Ұ�4
		case 59:		//���ѐݒ�@�������Ұ�5
		case 60:		//���ѐݒ�@�������Ұ�6
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

			SEQ_PAR_051 = BIT_2;			//�ް��ݒ��ʕ\��(1:�\����)

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
		case 1:			//���Y��ʁ@���Y�ݒ�
		case 8:			//�i���ʁ@�޲����ݒ���
		case 9:			//�i���ʁ@�޲����݈��͒���
		case 12:		//�i���ʁ@�ï�����
		case 13:		//�i���ʁ@�޲����ݑ���
		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
		case 18:		//�i���ʁ@MB�I�𑀍�
			break;

		case 02:		//���Y��ʁ@�P�x�ݒ�
		case 03:		//���Y��ʁ@�޲��ݽ�\��
		case 04:		//���Y��ʁ@���ݽ����
		case 05:		//���Y��ʁ@���Y�ݒ蒆�^
		case 07:		//�i���ʁ@���ݻ���͒���
		case 10:		//�i���ʁ@�޲��ݽ�\��
		case 11:		//�i���ʁ@���ݽ����
		case 19:		//���Y��ʁ@���Y�ݒ�2
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
		case 8:			//�i���ʁ@�޲����ݒ���
		case 9:			//�i���ʁ@�޲����݈��͒���
		case 12:		//�i���ʁ@�ï�����
		case 13:		//�i���ʁ@�޲����ݑ���
		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
		case 18:		//�i���ʁ@MB�I�𑀍�
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
			if(00 == EJE_check()) {					//�G�W�F�N�^�L���`�F�b�N
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
			if( 00 == (SEQ_PAR_107 & BIT_3) ) {		//�@�\�I��4(�i�搔�l�ݒ�@1:�L)
				SV_CNT = 00;
			}
			SW16data_onset(0x00, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 03);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0x00, 04);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			break;

		case 19:		//���Y��ʁ@���Y�ݒ�2
			if( 00 == (SEQ_PAR_107 & BIT_2) ) {		//�@�\�I��3(���Y���l�ݒ�@1:�L)
				SV_CNT = 00;
			}
			if(00 == MIS_check()){					//�~�X�t�B�[�h�L���`�F�b�N
				CSR_CNT = 00;						//�~�X�t�B�[�h ��
			}
			SW16data_onset(0xff, 02);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 05);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			SW16data_onset(0xff, 06);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
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
*  Module Name:		Alltbl_set
*  Function Name:	���ð��ق̍쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����/�ݒ�l/�����l/SW�ް��@�̏��ð��ق��쐬����
*
*  �� ��	:FIT)�c�[		ON:2002-06-07
********************************************************************************
*/
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

	switch(GAMEN_NO) {
		default:
		case 2:			//���Y��ʁ@���^��{(���g�p)
//V01d		case 6:			//�i���ʁ@��{
		case 11:		//�ݒ��ʁ@�ް��ݒ�
		case 14:		//�ݒ��ʁ@�@�\�I��
		case 15:		//�ݒ��ʁ@�^�ް��Ǘ�
		case 18:		//�ݒ��ʁ@�ް��ݒ�I�𒆌^
		case 24:		//�ݒ��ʁ@н̨��޶с@NO/NC�ݒ�
		case 25:		//�ݒ��ʁ@۰�ضс@17�`20�ݒ�
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
		case 44:		//���ѐݒ�@�׏d�v�ݒ�
		case 46:		//���щ�ʁ@��߼�ݍ\���ް����
		case 47:		//���щ�ʁ@�޲����ݎ�������(��)
		case 48:		//���щ�ʁ@�޲����ݎ�������(�E)
		case 49:		//���щ�ʁ@���ݻ���͒���
		case 50:		//���ѐݒ�@�ޯ������ް��ݒ�
		case 51:		//���ѐݒ�@C/B���ђ萔2
		case 52:		//���ѐݒ�@�ް�������
		case 53:		//���щ�ʁ@���ײݎd�l�ݒ���
		case 54:		//���щ�ʁ@�ް�۰�މ��
		case 55:		//���щ�ʁ@�d�l�ݒ�7
		case 56:		//���щ�ʁ@�d�l�ݒ�8
		case 57:		//���ѐݒ�@�������Ұ�3
		case 58:		//���ѐݒ�@�������Ұ�4
		case 59:		//���ѐݒ�@�������Ұ�5
		case 60:		//���ѐݒ�@�������Ұ�6
			break;

		case 1:			//���Y��ʁ@��{
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

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

			LENG_svpv(52, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			PV_cls(52, SEQ_020_SV, BIT_5);							//�޲ʲĎ����̔�\��
			PV_cls(54, SEQ_020_SV, BIT_5);							//�޲ʲĎ����̔�\��
			CSR_disp_cls(5);										//�޲ʲĂ̕���

			PV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�����̔�\��
			CSR_disp_cls(6);										//�׏d�v�̕���

			PV_cls(68, SEQ_016_SV, BIT_3);							//�į��ݸ���ώ����̔�\��
			CSR_disp_cls(79);										//�į��ݸ���ς̕���
			CSR_disp_cls(80);										//�į��ݸ���ς̕���

			SCAN_kat_cls();											//

//			SV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			PV_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_cls(72, SEQ_016_SV, BIT_1);							//VS�d�l�̔�\��
//			CSR_disp_cls(93);										//VS�d�l�̶���
			break;

		case 6:			//���Y��ʁ@Ӱ��ݐݒ�	/* V01d */
		case 30:		//�ݒ��ʁ@Ӱ��ݐݒ�	/* V01d */
		case 3:			//���Y��ʁ@Ӱ��ݐݒ�
		case 28:		//�ݒ��ʁ@Ӱ��ݐݒ�
			LENG_svpv(91, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(92, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(93, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(94, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(95, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(96, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			SW_cls(62, SEQ_023_SV, BIT_8);							//�������̔�\��
			CSR_disp_cls(136);										//�������̶���
			SW_cls(63, SEQ_023_SV, BIT_9);							//�㉝���̔�\��
			CSR_disp_cls(137);										//�㉝���̶���
			SW_cls(64, SEQ_024_SV, BIT_2);							//���]�̔�\��
			CSR_disp_cls(150);										//���]�̶���

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�
			break;

		case 4:			//���Y��ʁ@����Ӱ���
		case 29:		//�ݒ��ʁ@����Ӱ���
			LENG_svpv(91, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)

			SW_cls(62, SEQ_023_SV, BIT_8);							//�������̔�\��
			CSR_disp_cls(136);										//�������̶���
			SW_cls(63, SEQ_023_SV, BIT_9);							//�㉝���̔�\��
			CSR_disp_cls(137);										//�㉝���̶���
			SW_cls(64, SEQ_024_SV, BIT_2);							//���]�̔�\��
			CSR_disp_cls(150);										//���]�̶���

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�
			break;

		case 7:			//�i���ʁ@���^��{
//			DANsel_csr(83, SEQ_020_SV, BIT_14, 118);				//���^��������
			DANsel_csr(67, SEQ_020_SV, BIT_4 | BIT_6, 119);			//�X���C�h����
			DANsel_csr(62, SEQ_019_SV, BIT_4, 120);					//��^�N�����p
			DANsel_csr(63, SEQ_019_SV, BIT_6, 121);					//���^�N�����p
			DANsel_csr(64, SEQ_019_SV, BIT_8, 122);					//�_�C���t�^
//			DANsel_csr(65, SEQ_019_SV, BIT_10,123);					//�_�C�N�b�V����
//			DANsel_csr(66, SEQ_020_SV, BIT_1, 124);					//�h���
//			DANsel_csr(80, SEQ_020_SV, BIT_15,125);					//�l�a
//			DANsel_csr(81, SEQ_020_SV, BIT_11,126);					//�o�����T
//			DANsel_csr(82, SEQ_019_SV, BIT_12 | BIT_13 | BIT_15,127);	//�޲����ݒ���

			SW_cls(30, SEQ_019_SV, BIT_4);							//��^�N�����p�̔�\��
			SW_cls(31, SEQ_019_SV, BIT_6);							//���^�N�����p�̔�\��
			SW_cls(32, SEQ_019_SV, BIT_8);							//�_�C���t�^�̔�\��

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
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
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

			SV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			PV_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			CSR_cls(53, SEQ_020_SV, BIT_8);							//�׏d�v�̔�\��
			CSR_disp_cls(9);
			CSR_disp_cls(10);
			CSR_disp_cls(11);
			CSR_disp_cls(12);
			CSR_disp_cls(13);

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);					//�^�ԍ�

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

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//�^�ԍ�
			break;

		case 22:		//�ݒ��ʁ@۰�ض�9�`16�ѐݒ�
						/*********	�ėp�J���̔ėp�o�͑I�����̐ݒ�l��������		*************/
			ROT_cam_sv(1, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 35);	//۰�ض�9
			CSR_disp_cls(142);
			ROT_cam_sv(2, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 36);	//۰�ض�10
			CSR_disp_cls(143);
			ROT_cam_sv(3, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 37);	//۰�ض�11
			CSR_disp_cls(144);
			ROT_cam_sv(4, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, 40, BIT_1, 38);	//۰�ض�12
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
			ROT_cam_sw(12, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0);		//۰�ض�10
			ROT_cam_sw(13, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0);		//۰�ض�11
			ROT_cam_sw(14, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0);		//۰�ض�12
			ROT_cam_sw(15, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2);		//۰�ض�13
			ROT_cam_sw(16, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2);		//۰�ض�14
			ROT_cam_sw(17, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2);		//۰�ض�15
			ROT_cam_sw(18, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2);		//۰�ض�16

						/*********	�ėp�J���̔ėp�o�͑I�����̃J�[�\���f�[�^��������		*************/
			ROT_cam_csr(0x88, BIT_0, SV_CAMNA8_C1, SEQ_019_SV, BIT_0, BIT_1, 43);	//۰�ض�9
			ROT_cam_csr(0x89, BIT_0, SV_CAMNA9_C1, SEQ_019_SV, BIT_0, BIT_1, 44);	//۰�ض�10
			ROT_cam_csr(0x8A, BIT_0, SV_CAMNAA_C1, SEQ_019_SV, BIT_0, BIT_1, 45);	//۰�ض�11
			ROT_cam_csr(0x8B, BIT_0, SV_CAMNAB_C1, SEQ_019_SV, BIT_0, BIT_1, 46);	//۰�ض�12
			ROT_cam_csr(0x8C, BIT_0, SV_CAMNAC_C1, SEQ_019_SV, BIT_2, BIT_3, 47);	//۰�ض�13
			ROT_cam_csr(0x8D, BIT_0, SV_CAMNAD_C1, SEQ_019_SV, BIT_2, BIT_3, 48);	//۰�ض�14
			ROT_cam_csr(0x8E, BIT_0, SV_CAMNAE_C1, SEQ_019_SV, BIT_2, BIT_3, 49);	//۰�ض�15
			ROT_cam_csr(0x8F, BIT_0, SV_CAMNAF_C1, SEQ_019_SV, BIT_2, BIT_3, 50);	//۰�ض�16

			KAT_cls(56, SEQ_PAR_107, BIT_0, 82);						//�^�ԍ�
			break;

		case 31:		//���ѐݒ�@���
//			if(OP_STATUS_DT == 00) {						//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
//				PV_cls(73, OP_STATUS_DT, 0xff);
			if(OP_STATUS == 00) {							//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
				PV_cls(73, OP_STATUS, 0xff);
				CSR_disp_cls(95);
			}
			break;

		case 45:		//���ѐݒ�@�ײ�ގ����ݒ�
			if( 00 == (SEQ_PAR_101 & BIT_1) ) {				//���ѐݒ�OK�H(1:OK)
			 	SW56_dncara_disp(0xff, 8);					//SW56���i��׸���SW�̈�֊i�[
			}
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
	switch(WINDOW_NO) {
		default:
		case 1:			//���Y��ʁ@���Y�ݒ�
		case 2:			//���Y��ʁ@�P�x�ݒ�
		case 3:			//���Y��ʁ@�޲��ݽ�\��
		case 4:			//���Y��ʁ@���ݽ����
		case 7:			//�i���ʁ@���ݻ���͒���
		case 8:			//�i���ʁ@�޲����ݒ���
		case 9:			//�i���ʁ@�޲����݈��͒���
		case 10:		//�i���ʁ@�޲��ݽ�\��
		case 11:		//�i���ʁ@���ݽ����
		case 12:		//�i���ʁ@�ï�����
		case 13:		//�i���ʁ@�޲����ݑ���
		case 14:		//�i���ʁ@�ײ�ޒ��ߑ���
		case 15:		//�i���ʁ@�ײ�ގ������ߊm�F
		case 16:		//�i���ʁ@�޲����ݒ��ߑ���
		case 17:		//�i���ʁ@�޲����ݎ������ߊm�F
		case 18:		//�i���ʁ@MB�I�𑀍�
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
			break;

		case 06:		//�i���ʁ@�ײ�ޒ���
			LENG_svpv(19, SYO_LNG_CNT);								//�����_�̕ύX(�ݒ�l&�����l)
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

			MISS_swcara_win();										//�~�X�t�B�[�h�r�v�\���L�����؂芷��
			break;
	}
}



/*** END ***/
