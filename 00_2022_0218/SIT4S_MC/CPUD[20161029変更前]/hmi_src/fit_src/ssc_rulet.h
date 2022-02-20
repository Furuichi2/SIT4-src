/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						���[���b�g�\������		��`�t�@�C��				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned int

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_def.h"
#include	"ssc_wk_ext.h"
#include	"dp_cpuab.h"

/*	�萔��` ****************************************************************/
#define		BIT_06		0x0040

/*	�O���Q�ƕϐ���` ********************************************************/
//	EXTRN	WORD		SEQ_PAR_101;			/* SEQ_RAM					*/
//	EXTRN	WORD		SEQ_PAR_222;			/* SEQ_RAM					*/

	EXTRN	WORD		RULET_DISP_FLG;			/* ���[���b�g�\���t���O		*/
	EXTRN	WORD		RULET_HIGH_FLG;			/* �����`��t���O			*/

	EXTRN	WORD		TAIKI_ZEN_POS;			/* ���[���b�g�O��`��ʒu	*/
	EXTRN	WORD		TAIKI_ZEN_MOD;			/* ���[���b�g�O��`�����	*/

	EXTRN	WORD		DEG_DISP_FLG;			/* �p�x�\���t���u			*/
	EXTRN	WORD		DEG_DISP_LST;			/* �p�x�f�[�^�O��l 		*/

	EXTRN	WORD		ENCO_DATA_BCD;			/* �p�x�G���R�[�h�f�[�^		*/
	EXTRN	WORD		ENCO_DATA_HEX;			/* �p�x�G���R�[�h�f�[�^		*/

	EXTRN	WORD		TAIKITEN_DIRECT;		/* �ҋ@�_�f�[�^�i�N���b�`�j	*/
	EXTRN	WORD		TAIKITEN_DAT;			/* �ҋ@�_�f�[�^�i�P�^�P�O�j	*/

//	EXTRN	WORD		CB1_SPMDAT_PV;			/* �r�o�l�f�[�^				*/
	EXTRN	WORD		SYS_HIGHSPM_B1;			/* �����`��J�n�r�o�l�l		*/
	EXTRN	WORD		SYS_LOWSPM_B1;			/* �����`���~�r�o�l�l		*/

	EXTRN	WORD		SEISAN_FLG;				/*							*/
	EXTRN	WORD		TAIKITEN_FLG;			/*							*/
	EXTRN	WORD		TAIKITEN_FLG_FLG;		/*							*/

	EXTRN	DWORD		DEG_DISP_TBL	  [];	/* 4�{�p�ް��擪���ڽ�z��	*/
	EXTRN	DWORD		RULET_TBL_BASE	  [];	/* ���[���b�g���\���f�[�^	*/
	EXTRN	DWORD		RULET_TBL_BASE_00 [];	/* ���[���b�g���\���f�[�^	*/
	EXTRN	DWORD		RULET_BASE_TBL_TBL[];	/* ���[���b�g�g�\���f�[�^	*/

	EXTRN	DWORD		HAN_RULET_TBL_BASE_00 [];	/* ���[���b�g���\���f�[�^	*/
	EXTRN	DWORD		HAN_RULET_BASE_TBL_TBL[];	/* ���[���b�g�g�\���f�[�^	*/

/*	�O���Q�Ɗ֐���` ********************************************************/
	EXTRN	void		Lcd_draw(WORD,WORD,WORD,WORD,WORD*);	/* 1ײݕ\��	*/

/****************************************************************************/
