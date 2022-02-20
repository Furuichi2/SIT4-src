/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�^�i��̑��상�C������													*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-06-21
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
typedef struct {
	UNs	*SADR;			//�I��
	UNs	S_ONOFF;		//�I��L���r�b�g
	UNs	*DADR;			//�ް��i�[���ڽ
	UNs	S_BIT1;			//���I��
	UNs	S_BIT2;			//���I��
	UNs	S_BIT3;			//��O�I��
	UNs	S_IAO;			//���S�O�I��
	UNs	AKI;			//��
	} DAN_TBL_TDEF;

typedef struct {
	UNs	*SADR;			//�d�l�L�����ڽ
	UNs	S_ONOFF;		//�d�l�L�������ޯ�
	UNs	*DADR;			//�o�͗̈���ڽ
	UNs	NSUU;			//�m�b�`��
	UNs	N_BIT1;			//�m�b�`�P�r�b�g
	UNs	N_BIT2;			//�m�b�`�Q�r�b�g
	UNs	N_BIT3;			//�m�b�`�R�r�b�g
	UNs	N_BIT4;			//�m�b�`�S�r�b�g
	UNs	N_BIT5;			//�m�b�`�T�r�b�g
	UNs	S_IAO1;			//���S�O�I��
	UNs	S_IAO2;			//���S�O�I��
	UNs	S_IAO3;			//��
	UNs	S_IAO4;			//��
	UNs	S_IAO5;			//��
	} ADC_SW2_TBL_TDEF;


/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	dsp_Dandori(void);						//�i��̊Ǘ�

void	sw56_gamen_07(UNs);						//�i��[��{]��SW5�6�̏���
void	sw234_gamen_07(UNs);					//�i��[��{]��SW2�3�4�̏���
void	DANseq_sw56off(UNs);					//�i���p���ݽOFF
void	DAN_select_ent(UNs);					//�i����ʑI�����ڃZ���N�g����

void	DANseq_alloff(void);					//�i���p�V�[�P���X�n�e�e
void	DAN_select_diap(void);					//�i���� �I�����ڃZ���N�g�\��
void	DAN_sel_cara(UNs);						//�i���I�����ڃL�����N�^�\��
void	DAN_SW14_no_set(void);					//�i���� SW14�F���ԍ��]��
void	DAN_dispseq_out(void);					//�i���� ���وʒu���ݽ�o��

void	DAN_csr_ichk(void);						//�i��J�[�\���ʒu������
void	DAN_csr_mng(void);						//�i��[��{]�̐�p�@�J�[�\���ړ��Ǘ�

void	SURA_sv_chg(void);						//�X���C�h�������߂r�u�ύX����
void	ADC_MAIN_MNG(void);						//�������^�����l�`�h�m����
void	ADC_GAMEN_CHG(void);					//�������^�����v�h�m��ʕύX����
void	ADC_WIN_DISP(UNs);						//�`�c�b �v�����������\��
void	ADC_STEP_DISP(void);					//�`�c�b�X�e�b�v�\������
void	ADC_STEP_CARA(UNs *);					//�`�c�b�X�e�b�v�L�����\��
void	ADC_STEP_ATR(UNs);						//�`�c�b�X�e�b�v�A�g���r���[�g
void	ADC_SW2_SELECT(void);					//�����r�v�Q�I����͏���
void	ADC_SW2_DISP(void);						//�����r�v�Q�I��\������
void	ADC_SW56DN_DISP(void);					/* �`�c�b�r�v�T�U���\���؊�		*/
void	ADC_SW5SEQ_OUT(void);					//�`�c�b�@�r�v�T�V�[�P���X�o��
void	ADC_SW6SEQ_OUT(void);					//�`�c�b�@�r�v�U�V�[�P���X�o��
void	ADC_NEXT_READ(void);					/* �`�c�b���^�ԍ��Ǎ�����		*/
void	ADC_GAMEN_END(void);					/* �`�c�b��ʖ߂菈��			*/
void	ADC_STEP_SHR(void);						/* �`�c�b�X�e�b�v���j�^�f�[�^����	*/
void	ADC_NEXTNAME_SET(void);					/* �`�c�b���^�ԍ����� 			*/
void	NEXT_READ_AFTER(void);					/* �����ǂݍ��݌�̍ĕ\�� 		*/
void	ADC_GRPH_DISP(void);					//�`�c�b��p�O���t�B�b�N�`��
void	ADC_SW56UP_DISP(void);					//�`�c�b�r�v�T�U��i���b�Z�[�W�\��
void	ADC_STEP_DISP1(void);					//�`�c�b�X�e�b�v���j�^�̕\��

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
const	DAN_TBL_TDEF	Dan_Sel_Tbl_07[15] = {
		{			/* �O�P�@�������^����		*/
			&SEQ_020_SV,		/* �I��		 */
			BIT_E,				/* �I��L���r�b�g	 */
			&SEQ_047_SV,		/* �f�[�^		 */
			BIT_5,				/* ���I��		 */
			BIT_6,				/* ���I��		 */
			BIT_7,				/* ��O�I��		 */
			10,					/* ���S�O�I��		 */
			0xff1f				/* ��		 */
		},
		{			/* �O�Q�@�X���C�h����	 */
			&SEQ_020_SV,		/* �I��		 */
			BIT_OFF,			/* �I��L���r�b�g	 */
			&SEQ_043_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_C,				/* ��O�I��		 */
			3,					/* �O�S��I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �O�R�@��^�N�����p�I��	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_5,				/* �I��L���r�b�g	 */
			&SEQ_041_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_3,				/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			1,					/* ���S�O�I��		 */
			0xffe3				/* ��		 */
		},
		{			/* �O�S�@���^�N�����p�I��	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_7,				/* �I��L���r�b�g	 */
			&SEQ_041_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_C,				/* ��O�I��		 */
			1,					/* ���S�O�I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �O�T�@�_�C���t�^�I��	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_9,				/* �I��L���r�b�g	 */
			&SEQ_042_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_3,				/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			1,					/* ���S�O�I��		 */
			0xffe3				/* ��		 */
		},
		{			/* �O�U�@�_�C�N�b�V�����I��	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_B,				/* �I��L���r�b�g	 */
			&SEQ_042_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_C,				/* ��O�I��		 */
			2,					/* ���S�E�I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �O�V�@�h���I��	 */
			&SEQ_020_SV,		/* �I��		 */
			BIT_2,				/* �I��L���r�b�g	 */
			&SEQ_043_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_3,				/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			3,					/* �O�S��I��		 */
			0xffe3				/* ��		 */
		},
		{			/* �O�W�@�l�a		 */
			&SEQ_021_SV,		/* �I��		 */
			BIT_0,				/* �I��L���r�b�g	 */
			&SEQ_043_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_C,				/* ��O�I��		 */
			5,					/* �O����I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �O�X�@�o�����T		*/
			0,				/* �I��		 */
			0,				/* �I��L���r�b�g	 */
			0,				/* �f�[�^		 */
			0,				/* ���I��		 */
			0,				/* ���I��		 */
			0,				/* ��O�I��		 */
			0,				/* ���S�O�I��		 */
			0				/* ��		 */
		},
		{			/* �P�O�@�_�C�N�b�V��������		*/
			&SEQ_019_SV,		/* �I��		 */
			0xb000,				/* �I��L���r�b�g	 */
			&SEQ_046_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_OFF,			/* ��O�I��		 */
			7,					/* �I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �P�P�@�X���C�h��������	 */
			&SEQ_020_SV,		/* �I��		 */
			BIT_6,				/* �I��L���r�b�g	 */
			&SEQ_044_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_3,				/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			4,					/* �O�S��I��		 */
			0xffe3				/* ��		 */
		},
		{			/* �P�Q�@�o�����T���͒���	 */
			&SEQ_020_SV,		/* �I��		 */
			BIT_B,				/* �I��L���r�b�g	 */
			&SEQ_044_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_OFF,			/* ��O�I��		 */
			6,					/* �O�S��I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �P�R�@�X�g���[�N����	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_E,				/* �I��L���r�b�g	 */
			&SEQ_045_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_OFF,			/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			9,					/* ���S�E�I��		 */
			0xffe3				/* ��		 */
		},
		{			/* �P�S�@�_�C�N�b�V������������	 */
			&SEQ_019_SV,		/* �I��		 */
			BIT_E,				/* �I��L���r�b�g	 */
			&SEQ_045_SV,		/* �f�[�^		 */
			BIT_A,				/* ���I��		 */
			BIT_B,				/* ���I��		 */
			BIT_C,				/* ��O�I��		 */
			2,					/* ���S�E�I��		 */
			0xe3ff				/* ��		 */
		},
		{			/* �P�T�@�_�C�N�b�V��������	 */
			&SEQ_020_SV,		/* �I��		 */
			BIT_0,				/* �I��L���r�b�g	 */
			&SEQ_046_SV,		/* �f�[�^		 */
			BIT_2,				/* ���I��		 */
			BIT_3,				/* ���I��		 */
			BIT_4,				/* ��O�I��		 */
			2,					/* ���S�E�I��		 */
			0xffe3				/* ��		 */
		}
	};

const	UNs		Dan_sel_cara_tbl[11][4] = {
		{ 0, 0, 0, 0},			//00
		{ 24, 25, 26, 0},		//01 ���S�O
		{ 27, 25, 28, 0},		//02 ���S�E
		{ 29, 25, 30, 0},		//03 �O�S��
		{ 31, 32, 33, 0},		//04 ���Y�E�i��P�E�Q
		{ 29, 43, 30, 0},		//05 �O����
		{ 44, 45, 0xff, 0},		//06 �ݒ舳�E���
		{ 46, 46, 0xff, 0},		//07 ���߁E����
		{ 47, 48, 0xff, 0},		//08 ��۰��E����
		{ 27, 0xff, 28, 0},		//09 ��  �E
		{ 53, 54, 55, 0}		//10 �����E�����E���o
	};


const	ADC_SW2_TBL_TDEF	ADC_SW2_TBL[6] = {
		{/******	�_�C�N�b�V��������E�C���h�E�P�R	***********/
			&SEQ_019_SV,			/* �d�l�L�� */
			BIT_11,					/* �d�l�L������ */
			&SEQ_042_SV,			/* �o�͗̈� */
			3,						/* �m�b�`�� */
			BIT_10,					/* �m�b�`�P�r�b�g */
			BIT_11,					/* �m�b�`�Q�r�b�g */
			BIT_12,					/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			27,						/* �� */
			25,						/* �S */
			28,						/* �E */
			0,						/* �\���S */
			0						/* �\���T */
		},
		{/******	�X���C�h���ߑ���E�C���h�E�P�S	***********/
			&SEQ_020_SV,			/* �d�l�L�� */
			BIT_4,					/* �d�l�L������ */
			&SEQ_053_SV,			/* �o�͗̈� */
			0,						/* �m�b�`�� */
			BIT_OFF,				/* �m�b�`�P�r�b�g */
			BIT_OFF,				/* �m�b�`�Q�r�b�g */
			BIT_OFF,				/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			0,						/* �� */
			0,						/* �S */
			0,						/* �E */
			0,						/* �\���S */
			0						/* �\���T */
		},
		{/******	�X���C�h�������ߊm�F�E�C���h�E�P�T	***********/
			&SEQ_020_SV,			/* �d�l�L�� */
			BIT_6,					/* �d�l�L������ */
			&SEQ_044_SV,			/* �o�͗̈� */
			3,						/* �m�b�`�� */
			BIT_2,					/* �m�b�`�P�r�b�g */
			BIT_3,					/* �m�b�`�Q�r�b�g */
			BIT_4,					/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			31,						/* ���Y */
			32,						/* �i��P */
			33,						/* �i��Q */
			0,						/* �\���S */
			0						/* �\���T */
		},
		{/******	�_�C�N�b�V��������E�C���h�E�P�U	***********/
			&SEQ_019_SV,			/* �d�l�L�� */
			BIT_14,					/* �d�l�L������ */
			&SEQ_045_SV,			/* �o�͗̈� */
			2,						/* �m�b�`�� */
			BIT_2,					/* �m�b�`�P�r�b�g */
			BIT_4,					/* �m�b�`�Q�r�b�g */
			0,						/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			27,						/* �� */
			28,						/* �E */
			0,						/* �\���R */
			0,						/* �\���S */
			0						/* �\���T */
		},
		{/******	�_�C�N�b�V�����������ߊm�F�E�C���h�E�P�V	***********/
			&SEQ_019_SV,			/* �d�l�L�� */
			BIT_14,					/* �d�l�L������ */
			&SEQ_045_SV,			/* �o�͗̈� */
			3,						/* �m�b�`�� */
			BIT_10,					/* �m�b�`�P�r�b�g */
			BIT_11,					/* �m�b�`�Q�r�b�g */
			BIT_12,					/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			27,						/* �� */
			25,						/* �S */
			28,						/* �E */
			0,						/* �\���S */
			0						/* �\���T */
		},
		{/******	�l�a����E�C���h�E�P�W	***********/
			&SEQ_021_SV,			/* �d�l�L�� */
			BIT_0,					/* �d�l�L������ */
			&SEQ_043_SV,			/* �o�͗̈� */
			2,						/* �m�b�`�� */
			BIT_10,					/* �m�b�`�P�r�b�g */
			BIT_12,					/* �m�b�`�Q�r�b�g */
			0,						/* �m�b�`�R�r�b�g */
			0,						/* �m�b�`�S�r�b�g */
			0,						/* �m�b�`�T�r�b�g */
			29,						/* �O */
			30,						/* �� */
			0,						/* �\���R */
			0,						/* �\���S */
			0						/* �\���T */
		}
	};

extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs	SPACE_ASCII_40[40];


/*
********************************************************************************
*  Module Name:		dsp_Dandori
*  Function Name:	�i��̊Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-21
********************************************************************************
*/
void	dsp_Dandori(void)
{

	switch(disp_stg_sel) {

		case E_kstg_init:		//�i��[��{]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(�Ȃ�)
					Key_Ent_sv();								//�ݒ�l�̊m��		//V06p
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//��^����ߥ���^����ߥ�޲����@�J�����׸޸ر
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SW�ް����@�\��
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = 0;
							WINDOW_NO_BACK = 0;

							disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
							WINDOW_NO = 10;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw2:			//key code SW2(�Ȃ�)
						case E_key_sw3:			//key code SW3(�Ȃ�)
						case E_key_sw4:			//key code SW4(�Ȃ�)
							KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O				/* V01j */
							DAN_select_ent(KEY_DATA_CODE);		//�i����ʑI�����ڃZ���N�g����	/* V01j */
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��			/* V01j */
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��			/* V01j */
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��			/* V01j */
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��			/* V01j */
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					sw56_gamen_07(KEY_DATA_CODE);				//�i��[��{]��SW5�6�̏���
					break;
			}
			break;

		case E_kstg_gaid:		//�i��[�K�C�_���X�\��]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode�i�Ȃ��j
				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							DAN_DAN_FLG = 0xff;
							disp_stg_sel = E_kstg_init;			//�i��[��{]��
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();						//��ʕ\��

							DAN_DAN_FLG = 0x00;
							break;
						case E_key_sw2:			//key code SW2�i�Ȃ��j
						case E_key_sw4:			//key code SW4�i�Ȃ��j
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_kstg_schk;			//�i��[�V�[�P���X�`�F�b�N]��
							WINDOW_NO = 11;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_kstg_schk:		//�i��[�V�[�P���X�`�F�b�N]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;
				case E_key_sw56_mode:		//SW5/6 key mode�i�Ȃ��j
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							DAN_DAN_FLG = 0xff;
							disp_stg_sel = E_kstg_init;			//�i��[��{]��
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();						//��ʕ\��

							DAN_DAN_FLG = 0x00;
							break;
						case E_key_sw2:			//key code SW2�i�Ȃ��j
						case E_key_sw3:			//key code SW3�i�Ȃ��j
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
							WINDOW_NO = 10;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_kstg_scon:		//�i��[�X���C�h����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��

					SURA_CHG_LST = 0;
					SURA_sv_chg();								//�X���C�h�������߂r�u�ύX����
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//��^����ߥ���^����ߥ�޲����@�J�����׸޸ر
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SW�ް����@�\��
							SWCHG_DISP_ON_FLG = 0;

//2014/09/09
////							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
////							WINDOW_NO_BACK = WINDOW_NO;
////
////							disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
////							WINDOW_NO = 10;
////							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							disp_stg_sel = E_kstg_init;					//�i��[��{]��
							GAMEN_NO = 7;
							if (SEQ_016_SV & BIT_10) {	// V01r
								GAMEN_NO = 8;
							}
							GAMEN_disp();								//��ʕ\��

							CSR_FLG = 5;								//�J�[�\���\���ʒu�w��
							CSR_FLG_CNT = CSR_FLG_CNT_LST;				//�J�[�\���ԍ��Z�b�g
							SV_FLG_CNT = 1;								//�ݒ�l�ԍ��Z�b�g
							SW_FLG_CNT = 1;								//�r�v�ԍ��Z�b�g
							CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//�J�[�\���ړ�(�߂�l�w��,�ړ�)

							autokana_sw56_bak = 0;						//

							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//�i����ʑI�����ڃZ���N�g����
							KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							if( CSR_FLG_CNT == 2 ){					//�J�[�\���������X�^�[�g�̈ʒu�̎������X�^�[�g����
								AUTO_sura_start();					//�ײ�ގ�����������
							}
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_kstg_bara:	/* V01j */	//�i��[�o�����T����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//��^����ߥ���^����ߥ�޲����@�J�����׸޸ر
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SW�ް����@�\��
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
							WINDOW_NO_BACK = WINDOW_NO;

							disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
							WINDOW_NO = 10;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//�i����ʑI�����ڃZ���N�g����
							KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_kstg_daic:	/* V01j */	//�i��[�_�C�N�b�V��������]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							SEQ_PAR_108 = 0;					//��^����ߥ���^����ߥ�޲����@�J�����׸޸ر
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

							SWCHG_DISP_ON_FLG = 0x0FF;
							SWchg_disp_gaibu();					//SW�ް����@�\��
							SWCHG_DISP_ON_FLG = 0;

							CSR_FLG_CNT_BACK = CSR_FLG_CNT;
							WINDOW_NO_BACK = WINDOW_NO;

							disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
							WINDOW_NO = 10;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
						case E_key_sw3:			//key code SW3
						case E_key_sw4:			//key code SW4
							DAN_select_ent(KEY_DATA_CODE);		//�i����ʑI�����ڃZ���N�g����
							KAT_DATCHG_FLG = 0xff;				//�J�E���^�l�ύX�t���O
							Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
							Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_kstg_kana:	/* V01j*/	//�i��[�������^����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					if (KEY_DATA_CODE == E_key_sw1)
					{
						SEQ_PAR_108 = 0;					//��^����ߥ���^����ߥ�޲����@�J�����׸޸ر
						DANseq_alloff();					//�i���p�V�[�P���X�n�e�e

						SWCHG_DISP_ON_FLG = 0x0FF;
						SWchg_disp_gaibu();					//SW�ް����@�\��
						SWCHG_DISP_ON_FLG = 0;

						CSR_FLG_CNT_BACK = CSR_FLG_CNT;
						WINDOW_NO_BACK = WINDOW_NO;

						disp_stg_sel = E_kstg_gaid;			//�i��[�K�C�_���X�\��]��
						WINDOW_NO = 10;
						WIN_gamen_disp();					//�E�C���h�E��ʕ\��

						autokana_sw56_bak = 0;				// V01j(INS)
					}
					switch(WINDOW_NO) {
						case 12:		//�`�c�b�X�e�b�v���j�^
							switch(KEY_DATA_CODE) {
								case E_key_sw2:			//key code SW2
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
								default:
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
							}
							break;
						case 13:		//�`�c�b�_�C�N�b�V����
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN13_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(������)
									SW16data_onset(0, 3);
									SEQ_PAR_042 &= ~BIT_8;			// ���~ SEQ OFF !
									goto	WIN13_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(������)
									SW16data_onset(0, 4);
									SEQ_PAR_042 &= ~BIT_9;			// �㏸ SEQ OFF !
									goto	WIN13_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN13_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_042 |= BIT_8;			// ���~ SEQ ON !
									SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN13_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_042 |= BIT_9;			// �㏸ SEQ ON !
									SW16data_onset(0xff, 4);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN13_SW24_EXIT;
WIN13_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 14:		//�`�c�b�X���C�h����
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN14_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(������)
									SW16data_onset(0, 3);
									SEQ_PAR_044 &= ~BIT_0;			// ���~ SEQ OFF !
									goto	WIN14_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(������)
									SW16data_onset(0, 4);
									SEQ_PAR_044 &= ~BIT_1;			// �㏸ SEQ OFF !
									goto	WIN14_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN14_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_044 |= BIT_0;			// ���~ SEQ ON !
									SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN14_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_044 |= BIT_1;			// �㏸ SEQ ON !
									SW16data_onset(0xff, 4);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN14_SW24_EXIT;
WIN14_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 15:		//�`�c�b�X���C�h��������
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN15_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN15_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN15_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 16:		//�`�c�b�_�C�N�b�V��������
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN16_SW24_EXIT;
								case E_key_sw3_down:	//key code SW3(������)
									SW16data_onset(0, 3);
									SEQ_PAR_045 &= ~BIT_0;			// ���~ SEQ OFF !
									goto	WIN16_SW24_EXIT;
								case E_key_sw4_down:	//key code SW4(������)
									SW16data_onset(0, 4);
									SEQ_PAR_045 &= BIT_1;			// �㏸ SEQ OFF !
									goto	WIN16_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN16_SW24_EXIT;
								case E_key_sw3:			//key code SW3
									SEQ_PAR_045 |= BIT_0;			// ���~ SEQ ON !
									SW16data_onset(0xff, 3);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN16_SW24_EXIT;
								case E_key_sw4:			//key code SW4
									SEQ_PAR_045 |= BIT_1;			// �㏸ SEQ ON 1
									SW16data_onset(0xff, 4);		//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
									ADC_SW34_FLG = 0xff;
									goto	WIN16_SW24_EXIT;
WIN16_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 17:		//�`�c�b�_�C�N�b�V������������
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN17_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN17_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN17_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						case 18:		//�l�a�I��
							switch(KEY_DATA_CODE) {
								case E_key_sw2_down:	//key code SW2(������)
									SW16data_onset(0, 2);
									goto	WIN18_SW24_EXIT;
								case E_key_sw2:			//key code SW2
									ADC_SW2_SELECT();			/* �����r�v�Q�I����͏���		*/
									KAT_DATCHG_FLG = 0xFF;		/* �J�E���^�l�ύX�t���O */
									goto	WIN18_SW24_EXIT;
								case E_key_sw3:			//key code SW3
								case E_key_sw4:			//key code SW4
									break;
WIN18_SW24_EXIT:
									Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
									Lcd_line( 01, 13, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��
									break;
								case E_key_sw5:			//key code SW5
									ADC_SW5SEQ_OUT();
									break;
								case E_key_sw6:			//key code SW6
									ADC_SW6SEQ_OUT();
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}
					switch(KEY_DATA_CODE) {
						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							ADC_SW5_ON_FLG = 0xff;					//2016/04/22
							break;
						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							ADC_SW6_ON_FLG = 0xff;					//2016/04/22
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();					//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							ADC_SW5_ON_FLG = 0;					//2016/04/22
							ADC_SW6_ON_FLG = 0;					//2016/04/22
							break;
					}
			}
	}
}


/*
********************************************************************************
*  Module Name:		sw56_gamen_07
*  Function Name:	�i��[��{]��SW5�6�̏���
*  Input	:		������(SW5/6)
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-27
********************************************************************************
*/
void	sw56_gamen_07(UNs k_code)
{
	UNs		i, seq_bit;

	if(k_code == E_key_sw5_down || k_code == E_key_sw6_down ){	//������?
		DANseq_sw56off(k_code);						//�i���p���ݽOFF
		return;
	}

	if ( SW14_ON6_FLG == 1 ) {						//�������^����			/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//�J�[�\���ԍ��Z�b�g
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�

			disp_stg_sel = E_kstg_kana;				//�i��[�������^����]��
			seq_bit = SEQ_PAR_115 & 0x007f;
			ADC_WIN_DISP(seq_bit);					/* �`�c�b�E�C���h�E��ʕ\�� 		*/

			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
		}
	}

	else if( SW14_ON6_FLG == 2 ) {						//�X���C�h��������
		i = (SEQ_020_SV & 0x0070);
		if( i == BIT_4 ){							//�X���C�h���߂̂ݑI��
			goto	SW56_G07_310;
		}
		else if(k_code == E_key_sw6){				//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//�J�[�\���ԍ��Z�b�g
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�
//			DAN_WIN_FLG = 0xff;

			disp_stg_sel = E_kstg_scon;				//�i��[�X���C�h����]��
			WINDOW_NO = 6;
			WIN_gamen_disp();						//�E�C���h�E��ʕ\��

//			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
		}
	}

	else if( SW14_ON6_FLG <= /*5 V01j*/ 8 ) {		//��^����ߥ���^����ߥ�޲���  +  �޲����ݥ�h���l�a
SW56_G07_310:
		if(k_code == E_key_sw5){					//SW5?
			SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
		}
		else{
			SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
		}
		SW16data_onset(0xff, k_code+2 );						//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��
	}

	else if ( SW14_ON6_FLG == 9 ) {					//���ݻ����				/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//�J�[�\���ԍ��Z�b�g
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�

			disp_stg_sel = E_kstg_bara;				//�i��[�o�����T����]��
			WINDOW_NO = 7;
			WIN_gamen_disp();						//�E�C���h�E��ʕ\��

			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
		}
	}

	else if ( SW14_ON6_FLG == 10 ) {				//�޲����ݒ���			/* V01j */
		if(k_code == E_key_sw6){					//SW6?
			CSR_FLG_CNT_LST = CSR_FLG_CNT;			//�J�[�\���ԍ��Z�b�g
			SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�

			disp_stg_sel = E_kstg_daic;				//�i��[�_�C�N�b�V��������]��
			if (SEQ_PAR_046 & BIT_11)	WINDOW_NO = 9;
			else						WINDOW_NO = 8;
			WIN_gamen_disp();						//�E�C���h�E��ʕ\��

			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
		}
	}

}


/*
********************************************************************************
*  Module Name:		DANseq_sw56off
*  Function Name:	�i���p���ݽOFF
*  Input	:		������
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-14
********************************************************************************
*/
void	DANseq_sw56off(UNs k_code)
{

	if(k_code == E_key_sw5_down){	//key code SW5(������)

		SEQ_PAR_035 = 0;				//��ު��1�`6 ý�(1:ýĒ�)
		SEQ_PAR_041 &= 0xfefe;			//��^����߁C���^����߁@��SW(1:SW ON)
		SEQ_PAR_042 &= 0xfefe;			//�޲����C�޲����݁@���~SW(1:SW ON)
		SEQ_PAR_043 &= 0xfefe;			//�h���@���~SW�C�l�a�@��SW�@(1:SW ON)
		SEQ_PAR_044 &= 0xbfbe;			//�ײ�ޒ��߁C���ݻ����
		SEQ_PAR_045 &= 0xbffe;			//�޲����ݒ���
		SEQ_PAR_046 &= 0xffbf;			//�޲����ݒ���
		SEQ_PAR_047 &= 0xfffc;			//ADC SW(1:SW ON)

		SW16data_onset(0x00, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
	}
	else if(k_code == E_key_sw6_down){	//key code SW6(������)

		SEQ_PAR_035 = 0;				//��ު��1�`6 ý�(1:ýĒ�)
		SEQ_PAR_041 &= 0xfdfd;			//��^����߁C���^����߁@�JSW(1:SW ON)
		SEQ_PAR_042 &= 0xfdfd;			//�޲����C�޲����݁@�㏸SW(1:SW ON)
		SEQ_PAR_043 &= 0xfdfd;			//�h���@�㏸SW�C�l�a�@�oSW�@(1:SW ON)
		SEQ_PAR_044 &= 0xbfbd;			//�ײ�ޒ��߁C���ݻ����
		SEQ_PAR_045 &= 0xbffd;			//�޲����ݒ���
		SEQ_PAR_046 &= 0xffbf;			//�޲����ݒ���
		SEQ_PAR_047 &= 0xffe3;			//ADC SW(1:SW ON)

		SW16data_onset(0x00, 8);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
		Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
	}
}


/*
********************************************************************************
*  Module Name:		DAN_select_ent
*  Function Name:	�i����ʑI�����ڃZ���N�g����
*  Input	:		���ͷ�����
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	DAN_select_ent(UNs k_code)
{
	UNs		bit_d, s_no, *adr_p;

	if(SW14_ON6_FLG == 00 || SW14_ON6_FLG >= 16){
		return;
	}

	if(SW14_ON6_FLG == 10)		/* �_�C�N�b�V�������� */		/* V01q (ins) */
	{
		if(k_code == E_key_sw2) {					//key code SW2
			if (SEQ_019_SV & BIT_13) {				// ��۰����ߑI�����ڗL�H
				SEQ_046_SV &= ~(BIT_10+BIT_11);
				SEQ_046_SV |= BIT_10;

				SVSW_CHG_FLG |= 0x000c;					//�f�[�^�`�F���W�t���O�Z�b�g
				DAN_select_diap();						//�i���� �I�����ڃZ���N�g�\��
				Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

				FRAM_csum_set();						//FeRAM�̈�̐ݒ�l�������ѥ���ނ��쐬	V06i(INS)
			}
		}
		else if(k_code == E_key_sw3) {				//key code SW2
			if (SEQ_019_SV & BIT_15) {				// ���͒��ߑI�����ڗL�H
				SEQ_046_SV &= ~(BIT_10+BIT_11);
				SEQ_046_SV |= BIT_11;

				SVSW_CHG_FLG |= 0x000c;					//�f�[�^�`�F���W�t���O�Z�b�g
				DAN_select_diap();						//�i���� �I�����ڃZ���N�g�\��
				Under_grph();							//���i�̃O���t�B�b�N�Z�b�g
			}

				FRAM_csum_set();						//FeRAM�̈�̐ݒ�l�������ѥ���ނ��쐬	V06i(INS)
		}
	}
	else
	{
		s_no = (SW14_ON6_FLG - 1);
		adr_p = Dan_Sel_Tbl_07[s_no].SADR;				//�I��
		bit_d = Dan_Sel_Tbl_07[s_no].S_ONOFF;			//�I��L���r�b�g
		if(*adr_p & bit_d){								//�I�����ږ���?
			if(k_code == E_key_sw2) {					//key code SW2
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT1;	//���I��
			}
			else if(k_code == E_key_sw3){				//key code SW3
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT2;	//���I��
			}
			else{										//key code SW4
				bit_d =  Dan_Sel_Tbl_07[s_no].S_BIT3;	//��O�I��
			}

			if(bit_d != 00){
				adr_p = Dan_Sel_Tbl_07[s_no].DADR;		//�ް��i�[���ڽ
				*adr_p &= Dan_Sel_Tbl_07[s_no].AKI;		//�I���f�[�^������
				*adr_p |= bit_d;

//2014-08-08koma ����				SVSW_CHG_FLG |= 0x000c;					//�f�[�^�`�F���W�t���O�Z�b�g
				SVSW_CHG_FLG |= 0x0008;					//�f�[�^�`�F���W�t���O�Z�b�g 2014-08-08koma ����
				DAN_select_diap();						//�i���� �I�����ڃZ���N�g�\��
				Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

				FRAM_csum_set();						//FeRAM�̈�̐ݒ�l�������ѥ���ނ��쐬	V06i(INS)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DANseq_alloff
*  Function Name:	�i���p�V�[�P���X�n�e�e
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	DANseq_alloff(void)
{
	SEQ_PAR_035 = 0;				//��ު��1�`6 ý�(1:ýĒ�)
	SEQ_PAR_041 &= 0xfcfc;			//��^����߁C���^����߁@�JSW(1:SW ON)
	SEQ_PAR_042 &= 0xfcfc;			//�޲����C�޲����݁@���~ �㏸SW(1:SW ON)
	SEQ_PAR_043 &= 0xfcfc;			//�h���@���~ �㏸SW�C�l�a�@�� �oSW�@(1:SW ON)
	SEQ_PAR_044 &= 0xbfbc;			//�ײ�ޒ��߁C���ݻ����
	SEQ_PAR_045 &= 0xbffc;			//�޲����ݒ���
	SEQ_PAR_046 &= 0xffbf;			//�޲����ݒ���
	SEQ_PAR_047 &= 0xffe0;			//ADC SW(1:SW ON)
}


/*
********************************************************************************
*  Module Name:		DAN_select_diap
*  Function Name:	�i���� �I�����ڃZ���N�g�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	DAN_select_diap(void)
{
	UNs		*sel_p, *dt_p, i;
	UNs		sel_bit, bit_s1, bit_s2, bit_s3, sel_us, aki_d;


//V01r	if( GAMEN_NO != 7 )						//���^�i����
	if( GAMEN_NO != 7 && GAMEN_NO != 8 )		//���^�i����
//			GAMEN_NO != 18 )					//���^�f�[�^�ݒ�I�����
	{
		return;
	}
//	if((WINDOW_NO != 0 && WINDOW_NO < 6) || WINDOW_NO >= 10) {
//		return;
//	}
//V01j	if( WINDOW_NO != 6 ) {
//V01j		return;
//V01j	}
	if((WINDOW_NO != 0 && WINDOW_NO < 6) || WINDOW_NO >= 10) {
		return;
	}

	SW56_dncara_disp(0xff, 2);					//SW56���i��׸���SW�̈�֊i�[(SW2��)
	SW56_dncara_disp(0xff, 3);					//SW56���i��׸���SW�̈�֊i�[(SW3��)
	SW56_dncara_disp(0xff, 4);					//SW56���i��׸���SW�̈�֊i�[(SW4��)

	SW56_dncara_disp(0xff, 10);					//SW56���i��׸���SW�̈�֊i�[(SW2��)
	SW56_dncara_disp(0xff, 11);					//SW56���i��׸���SW�̈�֊i�[(SW3��)
	SW56_dncara_disp(0xff, 12);					//SW56���i��׸���SW�̈�֊i�[(SW4��)

	SW16data_onset(0x00, 2);					//SW1�`6�̔��]�w����s��
	SW16data_onset(0x00, 3);					//SW1�`6�̔��]�w����s��
	SW16data_onset(0x00, 4);					//SW1�`6�̔��]�w����s��

	if(SW14_ON6_FLG == 00 || SW14_ON6_FLG >= 16){
		return;
	}

	i = SW14_ON6_FLG - 1;

	sel_p = Dan_Sel_Tbl_07[i].SADR;				//�I��
	sel_bit = Dan_Sel_Tbl_07[i].S_ONOFF;		//�I��L���r�b�g
	dt_p = Dan_Sel_Tbl_07[i].DADR;				//�ް��i�[���ڽ
	bit_s1 = Dan_Sel_Tbl_07[i].S_BIT1;			//���I��
	bit_s2 = Dan_Sel_Tbl_07[i].S_BIT2;			//���I��
	bit_s3 = Dan_Sel_Tbl_07[i].S_BIT3;			//��O�I��
	sel_us = Dan_Sel_Tbl_07[i].S_IAO;			//���S�O�I��
	aki_d = Dan_Sel_Tbl_07[i].AKI;				//��

	if(*sel_p & sel_bit) {						//�I��L������
		DAN_sel_cara(sel_us);					//�i���I�����ڃL�����N�^�\��

		if(*dt_p & bit_s1) {					//���I��
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 2);			//SW1�`6�̔��]�w����s��
////#else
////			i = Dan_sel_cara_tbl[sel_us][0];
////			SW56_dncara_disp_color(i, 10, 11);	//SW56���i��׸���SW�̈�֊i�[(SW2��)
////#endif
			SW16data_onset(0xff, 2);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0x00, 3);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0x00, 4);			//SW1�`6�̔��]�w����s��
		}

		else if(*dt_p & bit_s2){				//���I��
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 3);			//SW1�`6�̔��]�w����s��
////#else
////			i = Dan_sel_cara_tbl[sel_us][1];
////			SW56_dncara_disp_color(i, 11, 11);	//SW56���i��׸���SW�̈�֊i�[(SW2��)
////#endif
			SW16data_onset(0x00, 2);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0xff, 3);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0x00, 4);			//SW1�`6�̔��]�w����s��
		}
		else if(*dt_p & bit_s3){				//��O�I��
//2016/04/22
////#if ( SIT_TYPE_SEL == TYPE_SIT3 )
////			SW16data_onset(0xff, 4);			//SW1�`6�̔��]�w����s��
////#else
////			i = Dan_sel_cara_tbl[sel_us][2];
////			SW56_dncara_disp_color(i, 12, 11);	//SW56���i��׸���SW�̈�֊i�[(SW2��)
////#endif
			SW16data_onset(0x00, 2);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0x00, 3);			//SW1�`6�̔��]�w����s��
			SW16data_onset(0xff, 4);			//SW1�`6�̔��]�w����s��
		}
		else{									//�I�����ږ���
			return;
		}

		if(SW14_ON6_FLG == 10){					//�޲����ݒ��߂�SW2,3 ��������
			if(00 == (SEQ_019_SV & (/*BIT_12 | V01q*/ BIT_13))){
				SW56_dncara_disp(0xff, 2);		//SW56���i��׸���SW�̈�֊i�[(SW2��)
				SW56_dncara_disp(0xff, 10);		//SW56���i��׸���SW�̈�֊i�[(SW2��)
			}
			if(00 == (SEQ_019_SV & BIT_15)){
				SW56_dncara_disp(0xff, 3);		//SW56���i��׸���SW�̈�֊i�[(SW3��)
				SW56_dncara_disp(0xff, 11);		//SW56���i��׸���SW�̈�֊i�[(SW3��)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_sel_cara
*  Function Name:	�i���I�����ڃL�����N�^�\��
*  Input	:		�I������
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	DAN_sel_cara(UNs c_no)
{
	UNs		i;

	if(c_no == 7){							//���ʂɂV�̎��͏�i���L�����N�^������
		i = Dan_sel_cara_tbl[8][0];
		SW56_dncara_disp(i, 2);				//SW56���i��׸���SW�̈�֊i�[(SW2��)

		i = Dan_sel_cara_tbl[8][1];
		SW56_dncara_disp(i, 3);				//SW56���i��׸���SW�̈�֊i�[(SW3��)

		i = Dan_sel_cara_tbl[8][2];
		SW56_dncara_disp(i, 4);				//SW56���i��׸���SW�̈�֊i�[(SW4��)
	}

	i = Dan_sel_cara_tbl[c_no][0];
	SW56_dncara_disp(i, 10);				//SW56���i��׸���SW�̈�֊i�[(SW2��)

	i = Dan_sel_cara_tbl[c_no][1];
	SW56_dncara_disp(i, 11);				//SW56���i��׸���SW�̈�֊i�[(SW3��)

	i = Dan_sel_cara_tbl[c_no][2];
	SW56_dncara_disp(i, 12);				//SW56���i��׸���SW�̈�֊i�[(SW4��)
}


/*
********************************************************************************
*  Module Name:		DAN_SW14_no_set(��:SW14_no_set)
*  Function Name:	�i���� SW14�F���ԍ��]��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-28
********************************************************************************
*/
void	DAN_SW14_no_set(void)
{
//V01r	if( (GAMEN_NO == 7 && SW14_ON6_FLG == 0) ||				//�O�̎��͕K���Z�b�g����
//V01r			(GAMEN_NO == 18) )							//�i���I����ʂ͕K���Z�b�g����
	if( ((GAMEN_NO == 7 || GAMEN_NO == 8) && SW14_ON6_FLG == 0) ||				//�O�̎��͕K���Z�b�g����
			(GAMEN_NO == 18) )							//�i���I����ʂ͕K���Z�b�g����
	{
		SW14_ON6_FLG = CSR_buff[CSR_TBL_POS_NOW].YOBI2;		//�\���Q
	}
//V01r	if( DAN_DAN_FLG != 0xff &&								//�E�C���h�E��ʂ���߂�Ƃ��̓Z�b�g���Ȃ�
//V01r		GGAMEN_DISP_FLG != 0xff &&							//��ʕ\�����䒆�t���O�n�m
//V01r		WINDOW_NO != 11 && GAMEN_NO == 7 )					//���@�\�i����ʂŃV�[�P���X�`�F�b�N���o������ɃJ�[�\���ʒu������������Ă��܂�
	if( DAN_DAN_FLG != 0xff &&								//�E�C���h�E��ʂ���߂�Ƃ��̓Z�b�g���Ȃ�
		GGAMEN_DISP_FLG != 0xff &&							//��ʕ\�����䒆�t���O�n�m
		WINDOW_NO != 11 && (GAMEN_NO == 7 || GAMEN_NO == 8) )					//���@�\�i����ʂŃV�[�P���X�`�F�b�N���o������ɃJ�[�\���ʒu������������Ă��܂�
	{
		SW14_ON6_FLG = CSR_buff[CSR_TBL_POS_NOW].YOBI2;		//�\���Q
	}

	if(DAN_KEY_FLG == 0xff) {
		if(SW14_ON6_FLG == 11) {							//�X���C�h����
			SW14_ON6_FLG = 2;
		}
		else if(SW14_ON6_FLG == 12) {						//�o�����T��
			SW14_ON6_FLG = 9;
		}
		else if(SW14_ON6_FLG >= 13 && SW14_ON6_FLG < 16) {	//�޲����ݒ���
			SW14_ON6_FLG = 10;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_dispseq_out
*  Function Name:	�i���ʶ��وʒu���ݽ�o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-28
********************************************************************************
*/
void	DAN_dispseq_out(void)
{
	UNs		i, bitp1, bitp2;

//V01r	if( GAMEN_NO != 7 || WINDOW_NO >= 10 || CSR_CNT == 0 )
	if( (GAMEN_NO != 7 && GAMEN_NO != 8) || WINDOW_NO >= 10 || CSR_CNT == 0 )
	{
		return;
	}

	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;
	bitp1 = bitp2 = 0;

	if(i == 27){									//��^�N�����p
		bitp1 = BIT_0;
	}
	else if(i == 28){								//���^�N�����p
		bitp1 = BIT_1;
	}
	else if(i == 29){								//�_�C���t�^
		bitp1 = BIT_2;
	}
	else if(i == 46){								//�_�C�N�b�V����
		bitp1 = BIT_3;
	}
	else if(i == 47){								//�h���
		bitp1 = BIT_4;
	}
	else if(i == 48){								//�X���C�h��������
		bitp2 = BIT_5;
	}
	else if(i == 58){								//�X���C�h����
		bitp1 = BIT_6;
	}
	else if(i == 89){								//�l�a
		bitp1 = BIT_5;
	}
	else if(i == 84){								//�o�����T
		bitp1 = BIT_7;
	}
	else if(i == 85){								//�޲����ݒ���
		bitp2 = BIT_0;
	}
	else if(i == 86){								//�X�g���[�N����
		bitp2 = BIT_1;
	}
	else if(i == 59){								//�X�g���[�N��������
		bitp2 = BIT_2;
	}
	else if(i == 87){								//���͒���
		bitp2 = BIT_3;
	}
	else if(i == 88){								//�������^����
		bitp2 = BIT_6;
	}

	SEQ_PAR_052 = bitp1;
	SEQ_PAR_054 = bitp2;

}


/*
********************************************************************************
*  Module Name:		DAN_csr_ichk(��:SEIDAN_CSR_BACK)
*  Function Name:	�i��J�[�\���ʒu������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_ichk(void)
{
	UNs		bf, bf1, bf2, bf3;

	bf = SEQ_019_SV;
	bf &= (BIT_4 | BIT_6 | BIT_8);
	bf2 = SEI_ON6_LST1;
	SEI_ON6_LST1 = bf;
	bf3 = bf;
	bf ^= bf2;

	bf1 = SEQ_020_SV;
	bf1 &= (BIT_4 | BIT_6);
	bf2 = SEI_ON6_LST2;
	SEI_ON6_LST2 = bf1;
	bf3 |= bf1;
	bf1 ^= bf2;
	bf |= bf1;

	if(bf != 0){
		SW14_ON6_FLG = 0;				//�i���ʃJ�[�\�����[�h������

		DAN_GAMEN_NON = 0;
		if( bf3 == 0){
			DAN_GAMEN_NON = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_csr_mng
*  Function Name:	�i��[��{]�̐�p�@�J�[�\���ړ��Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_mng(void)
{
	UNs		i;

//V01r	if(GAMEN_NO != 7)
	if(GAMEN_NO != 7 && GAMEN_NO != 8)
	{						//�i��[��{]�H
		return;
	}

	if(WINDOW_NO == 00 ){
		if(DAN_CLS_CNT <= 1 ){				//�\�����P��	?
			return;
		}

		if(CSR_FLG == E_key_up){						//key code �� ?
			if(CSR_FLG_CNT == CSR_G07_NO1){				//�J�[�\���擪�ʒu�Ɠ����H
				CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = CSR_G07_NO2;				//�J�[�\���Ō�ʒu
			}
		}
		else if(CSR_FLG == E_key_down){					//key code �� ?
			if(CSR_FLG_CNT == CSR_G07_NO2){				//�J�[�\���Ō�ʒu�Ɠ����H
				CSR_FLG = 5;							//�J�[�\���\���ʒu�w��
				CSR_FLG_CNT = CSR_G07_NO1;				//�J�[�\���擪�ʒu
			}
		}

		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//�J�[�\���ړ�(�߂�l�w��,�ړ�)

		i = (SEQ_020_SV & 0x0070);						//�E�C���h�E���o������
		if (GAMEN_NO == 7)				// V01r
		{
			if( (CSR_FLG_CNT == 1) && (i & 0x0060) ) {		//�X���C�h����
				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW5��)��߰�
				SW56_dncara_disp(16, 8);					//SW56���i��׸���SW�̈�֊i�[(SW6��) �J��
				Under_grph();								//���i�̃O���t�B�b�N�Z�b�g
			}
		}
		else
		{
			if( (CSR_FLG_CNT == /*1 V01j*/2) && (i & 0x0060) ) {		//�X���C�h����
				SW56_dncara_disp(0xff, 7);					//SW56���i��׸���SW�̈�֊i�[(SW5��)��߰�
				SW56_dncara_disp(16, 8);					//SW56���i��׸���SW�̈�֊i�[(SW6��) �J��
				Under_grph();								//���i�̃O���t�B�b�N�Z�b�g
			}
		}
	}
//DAN_CSR_900:
	else{									//����޳�p
		if( CSR_FLG_CNT == 1 &&								//�E�C���h�E�̍ŏ㕔�ɃJ�[�\���L��H
			CSR_FLG == E_key_up &&							//key code �� ?
			SV_FLG_CNT == 1 &&								//�ݒ�l�̐擪�H
			WINDOW_NO != 11 ) {								//���ݽ������ʁH
			goto	DAN_CSR_970;
		}
//DAN_CSR_950:
		if( SW14_ON6_FLG == 11 ) {							//�X���C�h�������߂ŃX���C�h���߂������Ƃ�
			if( SEQ_020_SV & BIT_4 ||
				CSR_FLG != E_key_up ){							//��ړ��H
				goto	DAN_CSR_960;
			}
			else if(SV_FLG_CNT == 1){							//�ݒ�l�̐擪�H
				goto	DAN_CSR_970;
			}
			else {
				goto	DAN_CSR_960;
			}
		}
//DAN_CSR_955:
		else if(SW14_ON6_FLG == 14){						//�X�g���[�N�������߂ŃX�g���[�N�������Ƃ�
			if( SEQ_019_SV & BIT_12 ||
				CSR_FLG != E_key_up ){							//��ړ��H
				goto	DAN_CSR_960;
			}
			else if(SV_FLG_CNT == 1){							//�ݒ�l�̐擪�H
				goto	DAN_CSR_970;
			}
			else {
				goto	DAN_CSR_960;
			}
		}
DAN_CSR_960:
		if( CSR_FLG != E_key_up){ 							//key code �� ?
//DAN_CSR_962:
			if(CSR_FLG == E_key_down){						//key code ��
				if(SV_FLG_CNT < CSR_buff[CSR_TBL_POS_NOW].SV_MAX){
					CSR_FLG = E_key_right;					//key code ��
				}
			}
		}
		else if( SV_FLG_CNT != 1 ){
			CSR_FLG = E_key_left;							//key code ��
		}
//DAN_CSR_968:
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);				//�J�[�\���ړ�(�߂�l�w��,�ړ�)
		goto	DAN_CSR_END;

DAN_CSR_970:
//		if(ADC_DISP_FLG != 0xff){						//�`�c�b�\�����͂��̑���Ŗ߂�Ȃ�
			disp_stg_sel = E_kstg_init;					//�i��[��{]��
			GAMEN_NO = 7;
			if (SEQ_016_SV & BIT_10) {	// V01r
				GAMEN_NO = 8;
			}
			GAMEN_disp();								//��ʕ\��
//			SW14_DISP7_NON = 0;

			CSR_FLG = 5;								//�J�[�\���\���ʒu�w��
			CSR_FLG_CNT = CSR_FLG_CNT_LST;				//�J�[�\���ԍ��Z�b�g
			SV_FLG_CNT = 1;								//�ݒ�l�ԍ��Z�b�g
			SW_FLG_CNT = 1;								//�r�v�ԍ��Z�b�g
			CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//�J�[�\���ړ�(�߂�l�w��,�ړ�)

			i = (SEQ_020_SV & 0x0070);					//�E�C���h�E���o������
			if (GAMEN_NO == 7)				// V01r
			{
				if( (CSR_FLG_CNT == 1) && (i & 0x0060) ) {	//�X���C�h����
					SW56_dncara_disp(0xff, 7);				//SW56���i��׸���SW�̈�֊i�[(SW5��)��߰�
					SW56_dncara_disp(16, 8);				//SW56���i��׸���SW�̈�֊i�[(SW6��) �J��
					Under_grph();							//���i�̃O���t�B�b�N�Z�b�g
				}
			}
			else
			{
				if( (CSR_FLG_CNT == /*1 V01j*/2) && (i & 0x0060) ) {	//�X���C�h����
					SW56_dncara_disp(0xff, 7);				//SW56���i��׸���SW�̈�֊i�[(SW5��)��߰�
					SW56_dncara_disp(16, 8);				//SW56���i��׸���SW�̈�֊i�[(SW6��) �J��
					Under_grph();							//���i�̃O���t�B�b�N�Z�b�g
				}
			}
			autokana_sw56_bak = 0;						// V01j(INS)
//		}
	}
DAN_CSR_END:
	return;
}


/*
********************************************************************************
*  Module Name:		SURA_sv_chg
*  Function Name:	�X���C�h�������߂r�u�ύX����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	SURA_sv_chg(void)
{
	UNs	i, j;

	i = (SEQ_PAR_109 & 0x001c);
	j = SURA_CHG_LST;
	SURA_CHG_LST = i;
	j ^= i;
	if( i & j ){
		if( i & BIT_2 ){
			SV_ATUOSU_D9 = SV_ATUOS0_D9;			//�X���C�h�������߁@���Y�ݒ�
		}
		else if( i & BIT_3 ){
			SV_ATUOSU_D9 = SV_ATUOS1_D9;			//�X���C�h�������߁@�i���P�ݒ�
		}
		else if( i & BIT_4 ){
			SV_ATUOSU_D9 = SV_ATUOS2_D9;			//�X���C�h�������߁@�i���Q�ݒ�
		}
		SVSW_CHG_FLG |= BIT_2;						//Ӱ���(MOT)�v��
		SVSW_CHG_FLG |= BIT_4;						//OP�ް��]���v��	/* V01j */

		FRAM_csum_set();							//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	}
}


/*
********************************************************************************
*  Module Name:		ADC_MAIN_MNG
*  Function Name:	�������^�����l�`�h�m����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_MAIN_MNG (void) {
	ADC_GAMEN_CHG();			/* �������^�����v�h�m��ʕύX����	*/
	ADC_STEP_DISP();			/* �`�c�b�X�e�b�v�\������	 	*/
	ADC_SW56DN_DISP();			/* �`�c�b�r�v�T�U���\���؊�		*/
	ADC_NEXT_READ();			/* �`�c�b���^�ԍ��Ǎ�����		*/
	ADC_GAMEN_END();			/* �`�c�b��ʖ߂菈��			*/
	ADC_STEP_SHR();				/* �`�c�b�X�e�b�v���j�^�f�[�^����	*/
}


/*
********************************************************************************
*  Module Name:		ADC_DATA_INI
*  Function Name:	�`�c�b�f�[�^�C�j�V��������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2006-08-28
********************************************************************************
*/
void	ADC_DATA_INI (void) {
	UNs		seq_chg, seq_bit, seq_old, seq_one ;
	UNs		i, *adr;

	if(SEQ_020_SV & BIT_14 == 0 )	{ return; }		//�������^�����d�l����H

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_5;		// new
	seq_old = ADC_CHG_LST5;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST5 = seq_bit;

	if(seq_one == 0)	{ return; }					//�����G�b�W�Ȃ��H

	SV_NEXTNO_D1 = 0;
	SEQ_047_SV |= BIT_15;
	FRAM_csum_set();								//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
	
	adr = &PV_MLDNO2_F11[0];
	for(i=0; i<7; i++, adr++) {
		*adr = 0x2020;
	}

	if (WINDOW_NO == 12) {
		NEXT_READ_AFTER();								/* �����ǂݍ��݌�̍ĕ\�� 		*/
	}
}


/*
********************************************************************************
*  Module Name:		ADC_GAMEN_CHG
*  Function Name:	�������^�����v�h�m��ʕύX����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GAMEN_CHG(void) {

	UNs		seq_chg, seq_bit;

	if (ADC_DISP_FLG != 0xff)	{return;}

	seq_chg = seq_bit = SEQ_PAR_115 & 0x007f;
	seq_chg ^= ADC_CHG_LST;
	ADC_CHG_LST = seq_bit;
	if (seq_chg) {
		ADC_WIN_DISP(seq_bit);
	}
}


/*
********************************************************************************
*  Module Name:		ADC_WIN_DISP
*  Function Name:	�`�c�b �v�����������\��
*  Input	:		���ݽ115
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_WIN_DISP (UNs seq_bit)
{
	UNs		win_no;

	win_no = 12;
	if (seq_bit == BIT_1) 		{ win_no = 13; }
	else if (seq_bit == BIT_2)	{ win_no = 14; }
	else if (seq_bit == BIT_3)	{ win_no = 15; }
	else if (seq_bit == BIT_4)	{ win_no = 16; }
	else if (seq_bit == BIT_5)	{ win_no = 17; }
	else if (seq_bit == BIT_6)	{ win_no = 18; }

	if (WINDOW_NO != win_no) {
		WINDOW_NO = win_no;
		WIN_gamen_disp();						//�E�C���h�E��ʕ\��

		ADC_DISP_FLG = 0x0FF;					/* �`�c�b�E�C���h�E�\���� */
		ADC_CHG_LST1 = 0;
		ADC_CHG_LST2 = 0;
		ADC_CHG_LST2_2 = 0;
	}
}


/*
********************************************************************************
*  Module Name:		ADC_GRPH_DISP
*  Function Name:	�`�c�b��p�O���t�B�b�N�`��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GRPH_DISP(void) {

	UNs		*Dst_p, dot_d, line_no, dot_no;
	UNi		cnt;

	Dst_p = &LCD_WORK1[7][8][16];				//(7�s��8�ޯĖڂ�16�޲Ė�)
	dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
	cnt = (40-16);
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}

	line_no = 7;
	dot_no = 8;
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	for ( ; line_no<13; line_no++) {
		for ( ; dot_no<16; dot_no++) {
			LCD_WORK1[line_no][dot_no][16] |= dot_d;
		}
		dot_no = 0;
	}
}

/*
********************************************************************************
*  Module Name:		ADC_SW56UP_DISP
*  Function Name:	�`�c�b�r�v�T�U��i���b�Z�[�W�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW56UP_DISP(void) {

	UNs		xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	if(SEQ_047_SV & BIT_5)		{ ADC_MODE_FLG = 0; }
	else if(SEQ_047_SV & BIT_6)	{ ADC_MODE_FLG = 1; }
	else if(SEQ_047_SV & BIT_7)	{ ADC_MODE_FLG = 2; }
	else 						{ ADC_MODE_FLG = 3; }

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	g_p = mess_adr_shr( 14 );						//���b�Z�[�W��ʃL�����N�^�A�h���X����
	g_p += ADC_MODE_FLG*10;							//�Q�O�{
	xy_no = 13;										//�P�R�s��
	xy_no |= ((40-2-12) << 4);						//(40-2-12=26)����
	xy_no |= (12 << 10);							//�������P�Q
	disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
#else
	xdot = 30*8*2;			// 30���ځ~8�ޯā~2�{�p
	ydot = 13*16*2;			// 13�s�ځ~16�ޯā~2�{�p
	adr = CHR_TABLE_ADR + ((271+ADC_MODE_FLG-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		8,						/* ��׸��			*/
		xdot,					/* ���o��X�ʒu		*/
		ydot,					/* ���o��Y�ʒu		*/
		0,						/* �����F			*/
		GAMENn_HEAD.scr_col,	/* �w�i�F			*/
		0x0202,					/* ��������			*/
		hrom,					/* �����i�[���ڽ	*/
		LCD_VBASE				/* �\�����			*/
		);
	disp_moji_s_rif(
		8,						/* ��׸��			*/
		xdot,					/* ���o��X�ʒu		*/
		ydot,					/* ���o��Y�ʒu		*/
		0x0202					/* ��������			*/
		);
#endif
}


/*
********************************************************************************
*  Module Name:		ADC_STEP_DISP
*  Function Name:	�`�c�b�X�e�b�v�\������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	ADC_STEP_DISP(void)
{
	UNs		seq_bit, seq_old, seq_bt, xy_no, *g_p;

	if (ADC_DISP_FLG != 0xff)	{return;}

	ADC_STPCHG_FLG = seq_bit = SEQ_PAR_114 & 0x3f00;			// new
	seq_old = ADC_CHG_LST1;								// old
	ADC_STPCHG_FLG ^= seq_old;									// new ^ old = chg
	ADC_CHG_LST1 = seq_bit;

	if (ADC_STPCHG_FLG) {

		if (ADC_STPCHG_FLG & 0x0300) {					//�ï��1�ω��H
			FILCK_STEP1_FLG = 0;
			seq_bt = seq_bit & 0x0300;
			if (seq_bt == 0) {							// ����Ӱ�ށH
				xy_no = 7;									//�V�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else if (seq_bt == 0x0100) {				// ���]Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//�V�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//�����\���p�������ށ��ޯĕϊ�
			}
			else if (seq_bt == 0x0200) {				// �_��Ӱ�ށH
				FILCK_STEP1_FLG = 0xff;
			}
			else if (seq_bt == 0x0300) {				// �_��Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//�V�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}

		if (ADC_STPCHG_FLG & 0x0c00) {					//�ï��2�ω��H
			FILCK_STEP2_FLG = 0;
			seq_bt = seq_bit & 0x0c00;
			if (seq_bt == 0) {							// ����Ӱ�ށH
				xy_no = 9;									//�X�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else if (seq_bt == 0x0400) {				// ���]Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//�X�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//�����\���p�������ށ��ޯĕϊ�
			}
			else if (seq_bt == 0x0800) {				// �_��Ӱ�ށH
				FILCK_STEP2_FLG = 0xff;
			}
			else if (seq_bt == 0x0c00) {				// �_��Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//�X�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}

		if (ADC_STPCHG_FLG & 0x3000) {					//�ï��3�ω��H
			FILCK_STEP3_FLG = 0;
			seq_bt = seq_bit & 0x3000;
			if (seq_bt == 0) {							// ����Ӱ�ށH
				xy_no = 11;									//�P�P�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else if (seq_bt == 0x1000) {				// ���]Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//�P�P�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0xff);		//�����\���p�������ށ��ޯĕϊ�
			}
			else if (seq_bt == 0x2000) {				// �_��Ӱ�ށH
				FILCK_STEP3_FLG = 0xff;
			}
			else if (seq_bt == 0x3000) {				// �_��Ӱ�ށH
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//�P�P�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}
	}

	/***************�@�t���b�J�[���� *************/
	if(step_flick_flg != step_flick_flg_bak) {
		step_flick_flg_bak = step_flick_flg;

		if(FILCK_STEP1_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 7;									//�V�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else {
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				xy_no = 7;									//�V�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}

		if(FILCK_STEP2_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 9;									//�X�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else {
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 1*10;
				xy_no = 9;									//�X�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}

		if(FILCK_STEP3_FLG == 0xff) {
			if(step_flick_flg == 0) {
				xy_no = 11;									//�P�P�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else {
				g_p = mess_adr_shr( 14 );					//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += 8*10;								//mess14��8��זڐ擪���ڽ
				g_p += ADC_MODE_FLG*4*10;
				g_p += 2*10;
				xy_no = 11;									//�P�P�s��
				xy_no |= (2 << 4);							//�Q����
				xy_no |= (12 << 10);						//�������P�Q
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	ADC_STEP_DISP(void)
{
	UNs		seq_bit, seq_old, seq_bt, xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	if (ADC_DISP_FLG != 0xff)	{return;}

	ADC_STPCHG_FLG = seq_bit = SEQ_PAR_114 & 0x3f00;			// new
	seq_old = ADC_CHG_LST1;								// old
	ADC_STPCHG_FLG ^= seq_old;									// new ^ old = chg
	ADC_CHG_LST1 = seq_bit;

	if (ADC_STPCHG_FLG) {

		if (ADC_STPCHG_FLG & 0x0300) {					//�ï��1�ω��H
			FILCK_STEP1_FLG = 0;
			seq_bt = seq_bit & 0x0300;
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 7*16*2;			// 7�s�ځ~16�ޯā~2�{�p
			if (seq_bt == 0) {							// ����Ӱ�ށH
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x0100) {				// ���]Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					11,						/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x0200) {				// �_��Ӱ�ށH
				FILCK_STEP1_FLG = 0xff;
			}
			else if (seq_bt == 0x0300) {				// �_��Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}

		if (ADC_STPCHG_FLG & 0x0c00) {					//�ï��2�ω��H
			FILCK_STEP2_FLG = 0;
			seq_bt = seq_bit & 0x0c00;
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 9*16*2;			// 9�s�ځ~16�ޯā~2�{�p
			if (seq_bt == 0) {							// ����Ӱ�ށH
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x0400) {				// ���]Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					11,						/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x0800) {				// �_��Ӱ�ށH
				FILCK_STEP2_FLG = 0xff;
			}
			else if (seq_bt == 0x0c00) {				// �_��Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}

		if (ADC_STPCHG_FLG & 0x3000) {					//�ï��3�ω��H
			FILCK_STEP3_FLG = 0;
			seq_bt = seq_bit & 0x3000;
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 11*16*2;			// 11�s�ځ~16�ޯā~2�{�p
			if (seq_bt == 0) {							// ����Ӱ�ށH
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x1000) {				// ���]Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					11,						/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else if (seq_bt == 0x2000) {				// �_��Ӱ�ށH
				FILCK_STEP3_FLG = 0xff;
			}
			else if (seq_bt == 0x3000) {				// �_��Ӱ�ށH
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}
	}

	/***************�@�t���b�J�[���� *************/
	if(step_flick_flg != step_flick_flg_bak) {
		step_flick_flg_bak = step_flick_flg;

		if(FILCK_STEP1_FLG == 0xff) {
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 7*16*2;			// 7�s�ځ~16�ޯā~2�{�p
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+0-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}

		if(FILCK_STEP2_FLG == 0xff) {
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 9*16*2;			// 9�s�ځ~16�ޯā~2�{�p
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+1-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}

		if(FILCK_STEP3_FLG == 0xff) {
			xdot = 2*8*2;			// 2���ځ~8�ޯā~2�{�p
			ydot = 11*16*2;			// 11�s�ځ~16�ޯā~2�{�p
			if(step_flick_flg == 0) {
				hrom = &SPACE_ASCII_40[0];
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			else {
				adr = CHR_TABLE_ADR + ((275+(ADC_MODE_FLG*4)+2-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				disp_moji_s_color(
					12,						/* ��׸��			*/
					xdot,					/* ���o��X�ʒu		*/
					ydot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
			}
			disp_moji_s_rif(
				12,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		ADC_STEP_CARA
*  Function Name:	�`�c�b�X�e�b�v�L�����\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_CARA(UNs *top_adr)
{
}

/*
********************************************************************************
*  Module Name:		ADC_STEP_ATR
*  Function Name:	�`�c�b�X�e�b�v�A�g���r���[�g
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_ATR(UNs atr)
{
	if(ADC_STEP_FLG == 1) {
//		CSR_ENZAN(0x3817);
	}
	else if(ADC_STEP_FLG == 2) {
//		CSR_ENZAN(0x3819);
	}
	else if(ADC_STEP_FLG == 3) {
//		CSR_ENZAN(0x381b);
	}
}


/*
********************************************************************************
*  Module Name:		ADC_SW2_SELECT
*  Function Name:	�����r�v�Q�I����͏���
*  Input	:		���ͷ�����
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW2_SELECT(void)
{
	UNs		bit_d, s_no, *adr_p, onbit, ofbit, i;

	if (SEQ_PAR_114 & BIT_15 == 0)	{ return; }
//V01r	if (GAMEN_NO != 7)	{ return; }
	if (GAMEN_NO != 7 && GAMEN_NO != 8)	{ return; }
	if (WINDOW_NO < 13 || WINDOW_NO > 18)	{ return; }

	s_no = WINDOW_NO - 13;
	adr_p = ADC_SW2_TBL[s_no].SADR;				//�d�l
	bit_d = ADC_SW2_TBL[s_no].S_ONOFF;			//�d�l�L���r�b�g
	if(*adr_p & bit_d == 0)	{ return; }			//�d�l�ږ���?

	i = ADC_SW2_TBL[s_no].NSUU;					//�m�b�`��
//2016/04/22	adr_p = Dan_Sel_Tbl_07[s_no].DADR;			//�ް��i�[���ڽ
	adr_p = ADC_SW2_TBL[s_no].DADR;			//�ް��i�[���ڽ
	bit_d = *adr_p;

	if (i == 0) {								//�m�b�`���O�H
		ofbit = 0xffff;							//
		onbit = ADC_SW2_TBL[s_no].N_BIT1;		//�m�b�`�P�r�b�g
	}
	else if (i == 2) {									//�m�b�`���Q�H
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//���m�b�`�P�H
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT1;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT2;			//���̓m�b�`�Q�r�b�g
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//���m�b�`�Q�H
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT2;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//���̓m�b�`�P�r�b�g
		}
		else {
			ofbit = 0xffff;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//���̓m�b�`�P�r�b�g
		}
	}
	else if (i == 3) {									//�m�b�`���R�H
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//���m�b�`�P�H
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT1;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT2;			//���̓m�b�`�Q�r�b�g
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//���m�b�`�Q�H
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT2;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT3;			//���̓m�b�`�R�r�b�g
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT3){		//���m�b�`�R�H
			ofbit = ~ADC_SW2_TBL[s_no].N_BIT3;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//���̓m�b�`�P�r�b�g
		}
		else {
			ofbit = 0xffff;			//
			onbit = ADC_SW2_TBL[s_no].N_BIT1;			//���̓m�b�`�P�r�b�g
		}
	}
	if(WINDOW_NO == 16)	{ ofbit = 0xffe3; }			//
	if(WINDOW_NO == 18)	{ ofbit = 0xe3ff; }			//

	bit_d &= ofbit;
	bit_d |= onbit;
	*adr_p = bit_d;

	SVSW_CHG_FLG |= BIT_3;					/* �f�[�^�`�F���W�t���O�Z�b�g */

	ADC_SW2_DISP();
	Under_grph();

	SW16data_onset(0xff, 2);				//SW1�`6�̔��]�w����s��

	ADC_SW2_FLG = 0xFF;						/* �r�v�Q���n�m���Ă���Ύ󂯕t���Ȃ� */
}


/*
********************************************************************************
*  Module Name:		ADC_SW2_DISP
*  Function Name:	�����r�v�Q�I��\������
*  Input	:		���ͷ�����
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW2_DISP(void) {

	UNs		bit_d, s_no, *adr_p, ch, i;

//V01r	if (GAMEN_NO != 7)	{ return; }
	if (GAMEN_NO != 7 && GAMEN_NO != 8)	{ return; }
	if (WINDOW_NO < 13 || WINDOW_NO > 18)	{ return; }

	SW56_dncara_disp(0xff, 2);				//SW56���i��׸���SW�̈�֊i�[(SW2��)
	SW56_dncara_disp(0xff, 10);				//SW56���i��׸���SW�̈�֊i�[(SW2��)
	SW16data_onset(0, 2);					//SW1�`6�̔��]�w����s��

	s_no = WINDOW_NO - 13;
	adr_p = ADC_SW2_TBL[s_no].SADR;				//�d�l
	bit_d = ADC_SW2_TBL[s_no].S_ONOFF;			//�d�l�L���r�b�g
	if(*adr_p & bit_d == 0)	{ return; }			//�d�l�ږ���?

	i = ADC_SW2_TBL[s_no].NSUU;					//�m�b�`��
//2016/04/22	adr_p = Dan_Sel_Tbl_07[s_no].DADR;			//�ް��i�[���ڽ
	adr_p = ADC_SW2_TBL[s_no].DADR;			//�ް��i�[���ڽ
	bit_d = *adr_p;

	if (i == 0) {								//�m�b�`���O�H
		return;
	}
	else if (i == 2) {									//�m�b�`���Q�H
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//���m�b�`�P�H
			ch = ADC_SW2_TBL[s_no].S_IAO1;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//���m�b�`�Q�H
			ch = ADC_SW2_TBL[s_no].S_IAO2;
		}
		else {return;}
	}
	else if (i == 3) {									//�m�b�`���R�H
		if (bit_d & ADC_SW2_TBL[s_no].N_BIT1){			//���m�b�`�P�H
			ch = ADC_SW2_TBL[s_no].S_IAO1;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT2){		//���m�b�`�Q�H
			ch = ADC_SW2_TBL[s_no].S_IAO2;
		}
		else if (bit_d & ADC_SW2_TBL[s_no].N_BIT3){		//���m�b�`�R�H
			ch = ADC_SW2_TBL[s_no].S_IAO3;
		}
		else {return;}
	}
	SW56_dncara_disp(ch, 10);				//SW56���i��׸���SW�̈�֊i�[(SW2��)
}


/*
********************************************************************************
*  Module Name:		ADC_SW56DN_DISP
*  Function Name:	�`�c�b�r�v�T�U���\���؊�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW56DN_DISP(void)
{
	UNs		Sbit, w1, sw5_ch, sw6_ch;

	if(ADC_DISP_FLG != 0xff)	{ return;}

	Sbit = SEQ_PAR_114 & 0x001f;
	w1 = Sbit & 0x0003;
	sw5_ch = 0xff;
	ADC_SW5_FLG &= ~(BIT_0+BIT_1);
	if (w1 == BIT_0) {
		sw5_ch = 52;
		ADC_SW5_FLG |= BIT_0;
	}
	else if (w1 == BIT_1) {
		sw5_ch = 51;
		ADC_SW5_FLG |= BIT_1;
	}

	w1 = Sbit & 0x001c;
	sw6_ch = 0xff;
	ADC_SW6_FLG &= ~(BIT_2+BIT_3+BIT_4);
	if (w1 == BIT_2) {
		sw6_ch = 50;
		ADC_SW6_FLG |= BIT_2;
	}
	else if (w1 == BIT_3) {
		sw6_ch = 49;
		ADC_SW6_FLG |= BIT_3;
	}
	else if (w1 == BIT_4) {
		sw6_ch = 23;
		ADC_SW6_FLG |= BIT_4;
	}

	SW56_dncara_disp(sw5_ch, 7);			//SW56���i��׸���SW�̈�֊i�[(SW5��)
	SW56_dncara_disp(sw6_ch, 8);			//SW56���i��׸���SW�̈�֊i�[(SW6��)
	Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

//2016/04/22
	if(ADC_SW5_ON_FLG == 0xff) {
		SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
	}
	if(ADC_SW6_ON_FLG == 0xff) {
		SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
	}

	Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��			/* V01j */
	Lcd_line( 01, 14, E_line_bf, &LCD_WORK2[0][0][0] );	//�s�\��			/* V01j */
}


/*
********************************************************************************
*  Module Name:		ADC_SW5SEQ_OUT
*  Function Name:	�`�c�b�@�r�v�T�V�[�P���X�o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW5SEQ_OUT(void) {
	UNs		i;
	i = SEQ_PAR_047 & ~0x0003;
	i |= ADC_SW5_FLG & 0x0003;
	SEQ_PAR_047 = i;
}


/*
********************************************************************************
*  Module Name:		ADC_SW6SEQ_OUT
*  Function Name:	�`�c�b�@�r�v�U�V�[�P���X�o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_SW6SEQ_OUT(void) {
	UNs		i;
	i = SEQ_PAR_047 & ~0x001c;
	i |= ADC_SW6_FLG & 0x001c;
	SEQ_PAR_047 = i;
}


/*
********************************************************************************
*  Module Name:		ADC_NEXT_READ
*  Function Name:	�`�c�b���^�ԍ��Ǎ�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_NEXT_READ(void)
{
	UNs		seq_chg, seq_bit, seq_old, seq_one ;

	if(SEQ_020_SV & BIT_14 == 0 )	{ return; }		//�������^�����d�l����H

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_7;		// new
	seq_old = ADC_CHG_LST3;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST3 = seq_bit;

	if(seq_one == 0)	{ return; }					//�����G�b�W�Ȃ��H

//2016/04/22	if(SV_NEXTNO_D1 == 0 || SV_NEXTNO_D1 > 100)	{ return; }
	if(SV_NEXTNO_D1 == 0 || SV_NEXTNO_D1 > 200)	{ return; }

//2016/04/22
////	kata_load(SV_NEXTNO_D1, &FRAM_KAT_TOP);				//�^�f�[�^��FROM����Ǎ���
////
////	if(SEQ_PAR_078 & BIT_0)	{ return; }				// �^�ް��шُ�Ȃ牽�����Ȃ��ŏI���B
////
////	Dat_mm_inch_chg2();						//2015/01/28
////
////	if ( 9 < SV_HAN_P ) {	//V06n
////		SV_HAN_P = 0;
////	}
////	if ( 9 < SV_HAN_S ) {	//V06n
////		SV_HAN_S = 0;
////	}
////
////	SV0_MOT_FIX = 0;								//��葬�x�u���O�N���A			2014/10/09

	KAT_data_read_com(SV_NEXTNO_D1);


	SV_NEXTNO_D1 = 0;
	SEQ_047_SV |= BIT_15;
	FRAM_csum_set();								//�ݒ�l�������ѥ���ނ��쐬		2015/09/20
	
	ADC_NEXTNAME_SET();								/* �`�c�b���^�ԍ����� 			*/
	NEXT_READ_AFTER();								/* �����ǂݍ��݌�̍ĕ\�� 		*/
}


/*
********************************************************************************
*  Module Name:		NEXT_DATA_READ
*  Function Name:	�����^�f�[�^�Ǎ�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2016/04/22
********************************************************************************
*/
void	NEXT_DATA_READ(UNs KatNo)
{
	KAT_data_read_com(KatNo);
}


/*
********************************************************************************
*  Module Name:		ADC_NEXTNAME_SET
*  Function Name:	�`�c�b���^�ԍ�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_NEXTNAME_SET(void)
{
	UNs		*adr, i;

	if(SV_NEXTNO_D1 == 0) {
		adr = &PV_MLDNO2_F11[0];
		for(i=0; i<7; i++, adr++) {
			*adr = 0x2020;
		}
		SEQ_047_SV |= BIT_15;
		SVSW_CHG_FLG |= BIT_3;					//�f�[�^�]���V�[�P���X		2016/05/10
	}
//2016/04/22	else if(SV_NEXTNO_D1 <= 100) {
	else if(SV_NEXTNO_D1 <= 200) {
		adr = KAT_sv_name_tbl[SV_NEXTNO_D1];				//�^�ް� ���̗̈�̱��ڽ�ð���
		memcpy_word(&PV_MLDNO2_F11[0], adr, 8);				//�^�ް� ������ʗp�̌^����
		SEQ_047_SV &= ~BIT_15;
		SVSW_CHG_FLG |= BIT_3;					//�f�[�^�]���V�[�P���X		2016/05/10
	}
}


/*
********************************************************************************
*  Module Name:		NEXT_READ_AFTER
*  Function Name:	�����ǂݍ��݌�̍ĕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	NEXT_READ_AFTER(void)
{
	UNs		win_no;

	if(WINDOW_NO != 0) {
		CSR_FLG_CNT_BACK = CSR_FLG_CNT;
		WINDOW_NO_BACK = WINDOW_NO;
//		SURA_HOSEI_ADR = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���]�A�h���X�f�[�^�Ҕ�
	}
	win_no = WINDOW_NO;			// push
	WINDOW_NO = 0;
	GAMEN_disp();
	WINDOW_NO = win_no;			// pop

	if(WINDOW_NO != 0) {
		CSR_FLG = 5;
		CSR_FLG_CNT = CSR_FLG_CNT_BACK;
		SV_FLG_CNT = 1;
		SW_FLG_CNT = 1;
		
		if (WINDOW_NO >= 6 && WINDOW_NO >= 10) {
			DAN_WIN_FLG = 0xff;
		}
		WINDOW_NO = WINDOW_NO_BACK;
		WIN_gamen_disp();

//2016/05/12		if (WINDOW_NO >= 12 && WINDOW_NO >= 18) {
		if (WINDOW_NO >= 12 && WINDOW_NO <= 18) {
			ADC_DISP_FLG = 0xFF;
			ADC_CHG_LST1 = 0;
			ADC_CHG_LST2 = 0;
		}
//V01r		if (GAMEN_NO == 7)
		if ( GAMEN_NO == 7 || GAMEN_NO == 8)
		{
			DAN_WIN_FLG = 0;
			Count_hosei_csr_on(SURA_HOSEI_ADR);		//�J�E���^�␳�̎����l���]����
		}
	}
}

/*
********************************************************************************
*  Module Name:		ADC_GAMEN_END
*  Function Name:	�`�c�b��ʖ߂菈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_GAMEN_END(void)
{
	UNs		seq_chg, seq_bit, seq_old, seq_one ;

	if(ADC_DISP_FLG != 0xff)	{ return; }

	seq_chg = seq_bit = SEQ_PAR_114 & BIT_6;		// new
	seq_old = ADC_CHG_LST4;							// old
	seq_chg ^= seq_old;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	ADC_CHG_LST4 = seq_bit;

	if(seq_one == 0)	{ return; }					//�����G�b�W�Ȃ��H

	CSR_FLG = 5;
	CSR_FLG_CNT = CSR_FLG_CNT_LST;
	SV_FLG_CNT = 1;
	SW_FLG_CNT = 1;
	disp_stg_sel = E_kstg_init;						//�i��[��{]��		2016/04/22
	GAMEN_NO = 7;
	if (SEQ_016_SV & BIT_10) {	// V01r
		GAMEN_NO = 8;
	}
	GAMEN_disp();
	SW14_DISP7_NON = 0;

	CSR_FLG = 5;
	CSR_FLG_CNT = CSR_FLG_CNT_LST;
	SV_FLG_CNT = 1;
	SW_FLG_CNT = 1;
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//�J�[�\���ړ�(�߂�l�w��,�ړ�)
}


/*
********************************************************************************
*  Module Name:		ADC_STEP_SHR
*  Function Name:	�`�c�b�X�e�b�v���j�^�f�[�^����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
void	ADC_STEP_SHR(void)
{
	UNs		Sbit, i, cnt, no;

	if (WINDOW_NO != 12)	{ return; }			// �X�e�b�v���j�^�\�����H

	ADC_STEP_NO[0] = 0xffff;
	ADC_STEP_NO[1] = 0xffff;
	ADC_STEP_NO[2] = 0xffff;
	ADC_STEP_NO[3] = 0xffff;

	no = 0;
	cnt = 0;
	Sbit = SEQ_PAR_116;
	for (i=0; i<16; i++, no++, Sbit>>=1) {
		if (Sbit & BIT_0) {
			ADC_STEP_NO[cnt] = no;				// �X�e�b�v���j�^�m���D�i�[
			cnt++;
			if(cnt >= 4) {
				goto	ADC_STEPSHR_500;
			}
		}
	}
	Sbit = SEQ_PAR_117;
	for (i=0; i<14; i++, no++, Sbit>>=1) {
		if (Sbit & BIT_0) {
			ADC_STEP_NO[cnt] = no;				// �X�e�b�v���j�^�m���D�i�[
			cnt++;
			if(cnt >= 4) {
				goto	ADC_STEPSHR_500;
			}
		}
	}

ADC_STEPSHR_500:

	ADC_STEP_DISP1();

}


/*
********************************************************************************
*  Module Name:		ADC_STEP_DISP1
*  Function Name:	�`�c�b�X�e�b�v���j�^�̕\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima			ON:2004-06-01			V01j
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	ADC_STEP_DISP1(void) {

	UNs		no, cnt;
	UNs		xy_no, *g_p;

	for (cnt=0; cnt<4; cnt++) {
		if (ADC_STEP_NO[cnt] != ADC_STEP_NO_LAST[cnt]) {

			ADC_STEP_NO_LAST[cnt] = ADC_STEP_NO[cnt];

			if (ADC_STEP_NO[cnt] == 0xffff) {
				xy_no = cnt+8;									//���s��
				xy_no |= (18 << 4);								//�P�W����
				xy_no |= (20 << 10);							//�������Q�O
				disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
			}
			else {
				g_p = mess_adr_shr( 15 );						//���b�Z�[�W��ʃL�����N�^�A�h���X����
				g_p += ADC_STEP_NO[cnt] *10;					//�Q�O�{
				xy_no = cnt+8;									//���s��
				xy_no |= (18 << 4);								//�P�W����
				xy_no |= (20 << 10);							//�������Q�O
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			}
			Lcd_line( 00,cnt+8, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		}
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	ADC_STEP_DISP1(void) {

	UNs		no, cnt;
	UNs		xy_no, *g_p;
	UNs		xdot, ydot, *hrom;
	UNl		adr;

	for (cnt=0; cnt<4; cnt++) {
		if (ADC_STEP_NO[cnt] != ADC_STEP_NO_LAST[cnt]) {

			ADC_STEP_NO_LAST[cnt] = ADC_STEP_NO[cnt];
			xdot = 288;
			ydot = 256 + (cnt * 32);

			if (ADC_STEP_NO[cnt] == 0xffff) {
				hrom = &SPACE_ASCII_40[0];
			}
			else {
				adr = CHR_TABLE_ADR + ((ADC_STEP_NO[cnt]+287-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
			}
			disp_moji_s_color(
				16,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0,						/* �����F			*/
				GAMENn_HEAD.scr_col,	/* �w�i�F			*/
				0x0202,					/* ��������			*/
				hrom,					/* �����i�[���ڽ	*/
				LCD_VBASE				/* �\�����			*/
				);
			disp_moji_s_rif(
				16,						/* ��׸��			*/
				xdot,					/* ���o��X�ʒu		*/
				ydot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
		}
	}
}
#endif


/*** END ***/
