/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�J�E���g����			��`�t�@�C��				*/
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
#include	"dp_cpuab.h"

/*	�萔��` ****************************************************************/
#define		BIT_15		0x8000
#define		BIT_14		0x4000
#define		BIT_13		0x2000
#define		BIT_12		0x1000
#define		BIT_11		0x0800
#define		BIT_10		0x0400
#define		BIT_09		0x0200
#define		BIT_08		0x0100
#define		BIT_07		0x0080
#define		BIT_06		0x0040
#define		BIT_05		0x0020
#define		BIT_04		0x0010
#define		BIT_03		0x0008
#define		BIT_02		0x0004
#define		BIT_01		0x0002
#define		BIT_00		0x0001

#define		CNT_LIMIT	9999999					/* �������E�l �������� 0�ر	*/

/*	�O���Q�ƕϐ���` ********************************************************/
//	EXTRN	WORD		SEQ_PAR_016;			/* ���� �L/�� ����/�O��		*/
//	EXTRN	WORD		SEQ_PAR_032;			/* ���� ��/�� 				*/
//	EXTRN	WORD		SEQ_PAR_033;			/* ���� UP					*/
//	EXTRN	WORD		SEQ_PAR_102;			/* ���� UP�w��				*/
//	EXTRN	WORD		SEQ_PAR_160;			/* ���]/�t�]				*/

	EXTRN	WORD		ENCO_DATA_HEX;			/* �p�x�G���R�[�h�f�[�^		*/

	EXTRN	WORD		deg_OLD;				/* �p�x�O��l				*/
	EXTRN	WORD		count_bit_OLD[];		/* ���� UP�w���ޯđO��l	*/

	EXTRN	DWORD		COUNT_T;				/* ���� İ��				*/
	EXTRN	DWORD		COUNT_1;				/* ���� 1					*/
	EXTRN	DWORD		COUNT_2;				/* ���� 2					*/

/*	�O���Q�Ɗ֐���` ********************************************************/


/****************************************************************************/
