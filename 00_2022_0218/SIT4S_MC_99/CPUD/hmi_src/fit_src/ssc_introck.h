/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						���Y�^����ۯ��\������	��`�t�@�C��				*/
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

/*	�萔��` ****************************************************************/
// #define	LANG_BIT		0x2000				/* ����ؑ��ޯ�				*/

#define		SEISAN_LNG		20					/* ���Y������		20BYTE	*/
#define		SEISAN_POS		0x3053				/* ���Y���\���ʒu���		*/
												/* 12BYTE, X=5���, Y=3���	*/

#define		INTROCK_MAX		7					/* ����ۯ���������			*/
#define		INTROCK_LNG		40					/* ����ۯ�������	40BYTE	*/
#define		INTROCK_POS1	0x78A0				/* ����ۯ��\���ʒu��� 1	*/
												/* 30BYTE, X=10���, Y=0���	*/
#define		INTROCK_POS2	0xA006				/* ����ۯ��\���ʒu��� 2	*/
												/* 40BYTE, X=0���, Y=6���	*/

/*	�O���Q�ƕϐ���` ********************************************************/
//	EXTRN	WORD		SEQ_PAR_100;			/* SEQ_RAM	Ӱ��SW�\��		*/
//	EXTRN	WORD		SEQ_PAR_120;			/* ����ۯ��I��	1			*/
//	EXTRN	WORD		SEQ_PAR_121;			/* ����ۯ��I��	2			*/
//	EXTRN	WORD		SEQ_PAR_122;			/* ����ۯ� �ޯĈ� TOP		*/

	EXTRN	WORD		WINDOW_NO;				/* ��ʔԍ��i����޳ ON/OFF�j*/
//	EXTRN	DWORD		language_chg;			/* ����ؑ֗p�I�t�Z�b�g�l	*/

	EXTRN	WORD		SEI_INF_FLG;			/* ���Y���t���O			*/
	EXTRN	WORD		SEI_INF_FLG_LAST;		/* ���Y���t���O�O��l		*/

	EXTRN	WORD		IROCK_NO	 [];		/* ����ۯ��\���ԍ���		*/
	EXTRN	WORD		IROCK_NO_LAST[];		/* ����ۯ��\���ԍ���O��l	*/


/*	�O���Q�Ɗ֐���` ********************************************************/
	EXTRN	void		Disp_moji(WORD,WORD*,WORD);		/* LCD������\��	*/

/****************************************************************************/
