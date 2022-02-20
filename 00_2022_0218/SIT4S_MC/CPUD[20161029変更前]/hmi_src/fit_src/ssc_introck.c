/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						���Y�^�C���^�[���b�N�\������						*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		ALL_DISP		0xFF				/* �S��ʕ\��				*/
#define		HALF_DISP		0x55				/* �E�B���h�E�\��			*/
#define		NO_DISP			0x00				/* �\�����Ȃ�				*/

#define		SEISAN_LNG		20					/* ���Y������		20BYTE	*/
#define		SEISAN_POS		0x3053				/* ���Y���\���ʒu���		*/
												/* 12BYTE, X=5���, Y=3���	*/
#define		INTROCK_LNG		40					/* ����ۯ�������	40BYTE	*/
#define		INTROCK_POS1	0x78A0				/* ����ۯ��\���ʒu��� 1	*/
												/* 30BYTE, X=10���, Y=0���	*/
#define		INTROCK_POS2	0xA006				/* ����ۯ��\���ʒu��� 2	*/
												/* 40BYTE, X=0���, Y=6���	*/

#define		INTROCK_XPOS1	160					/* ����ۯ��\���ʒu��� 1	*/
#define		INTROCK_YPOS1	0					/* ����ۯ��\���ʒu��� 1	*/
#define		INTROCK_LENG1	30					/* ����ۯ��\���ʒu��� 1	*/
#define		INTROCK_XPOS2	0					/* ����ۯ��\���ʒu��� 1	*/
#define		INTROCK_YPOS2	192					/* ����ۯ��\���ʒu��� 1	*/
#define		INTROCK_LENG2	40					/* ����ۯ��\���ʒu��� 1	*/


/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];

/* �������� */
void		SEISAN_INF_DISP	(void);				/* ���Y�s���\��				*/
void		IROCK_SHR		(void);				/* ����ۯ��\��				*/
void		IROCK_SHR_OUT	(void);				/* �����C���^�[���b�N�̃L�����N�^�f�[�^�o�͏���	*/	//2009/07/14

/****************************************************************************/
/*																			*/
/*	���Y�s���\��			�F	�S�{�p�����\���̏�ɐ��Y�H����\������B	*/
/*																			*/
/*		�V�[�P���T�̃��[�h�r�v�E�P�U�r�b�g��ǂ��							*/
/*		�ŏ��ɂP�ɂȂ��Ă��郂�[�h�����b�Z�[�W�\������B					*/
/*																			*/
/*		SEQ_PAR_100			�F	�V�[�P���T�E���[�h�r�v�\��					*/
/*		language_chg		�F	�������ڽ	����ؑ֗p�I�t�Z�b�g�l			*/
/*																			*/
/*		SEISAN_DISP_FLG		�F	���Y���\���t���O							*/
/*		SEI_INF_FLG			�F	���Y���t���O								*/
/*		SEI_INF_FLG_LAST	�F	���Y���t���O�O��l						*/
/*																			*/
/*		��ʐ؂�ւ����́A�O��l�ۑ��̈���N���A���邱�ƁB					*/
/*																			*/
/****************************************************************************/
void	SEISAN_INF_DISP	(void)
{
	WORD	i;
	WORD	chk;
	WORD	mode;
	WORD	temp;
	WORD*	addr;
	DWORD	calc;
	UNl		adr;
	UNs		*hrom;

	if (SEISAN_DISP_FLG != ALL_DISP)	return;		/* ���Y�\�����Ȃ�		*/

	mode = SEQ_PAR_100;								/* Ӱ��SW�Ǎ�			*/
	chk  = 0x0001;

	for (i=0; i<16; i++){							/* �ޯ�����				*/
		if ((mode & chk) != 0x0000)		break;		/* ����OK				*/
		chk = (chk << 1);							/* 1�ޯļ��				*/
	}												/*						*/

	/* ON�Ȃ��̏ꍇ i=16 �ŋ󔒕\���ɂȂ� */

	SEI_INF_FLG 	 = i;							/* ���Y����׸�			*/
	temp 			 = SEI_INF_FLG_LAST;			/* �O��l�Ǎ�			*/
	SEI_INF_FLG_LAST = SEI_INF_FLG;					/* �O��l�X�V			*/
	if (temp == SEI_INF_FLG)			return;		/* �O��Ɠ����A�`��Ȃ�	*/

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_CHAR_TOP + language_chg);			/* �������ڽ + ���ꔻ��	*/
	calc  = (E_CHAR_TOP + (language_chg*2));		/* �������ڽ + ���ꔻ��	*/
/********/
	calc += (SEI_INF_FLG * SEISAN_LNG);				/* �̾�Ēl���Z			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(SEISAN_POS,addr,0);					/* LCD������\��		*/
#else
	adr =  CHR_TABLE_ADR + ((i+1) * CHAR_MOJI_SIZE);	// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		10, 
		80, 
		96, 
		0,
		6, 
		0x0202, 
		hrom, 
		LCD_VRAM
		);
#endif
}
/****************************************************************************/
/*																			*/
/*	�C���^�[���b�N�f�[�^�\������											*/
/*																			*/
/*		�V�[�P���T�̃C���^�[���b�N�I���i�R�Q���[�h�j�ɉ������p�^�[����		*/
/*		�R�Q�O�r�b�g�̃C���^�[���b�N�\�����`�F�b�N����B					*/
/*		�`�F�b�N�p�^�[���́A���[�U��`�B									*/
/*		�A�h���X�����Ɍ������A��D��ŊY�����郁�b�Z�[�W��\������B		*/
/*		�\���́A��ʍŏ�s�ƃE�B���h�E�ɍs���B�i�ő匏�� INTROCK_MAX�j		*/
/*																			*/
/*		SEQ_PAR_120			�F	�V�[�P���T�E�C���^�[���b�N�I��	���16bit	*/
/*		SEQ_PAR_121			�F	�V�[�P���T�E�C���^�[���b�N�I��	����16bit	*/
/*		SEQ_PAR_122			�F	�V�[�P���T�E�C���^�[���b�N�r�b�g��擪		*/
/*																			*/
/*		language_chg		�F	�������ڽ	����ؑ֗p�I�t�Z�b�g�l			*/
/*		WINDOW_NO			�F	��ʔԍ��i�E�B���h�E�\���n�m�^�n�e�e�j		*/
/*		INTROCK_DISP_FLG	�F	�K�C�_���X�\���t���O						*/
/*																			*/
/*		IROCK_NO	 [INTROCK_MAX]	�F	�C���^�[���b�N�\���ԍ���			*/
/*		IROCK_NO_LAST[INTROCK_MAX]	�F	�C���^�[���b�N�\���ԍ���O��l		*/
/*																			*/
/*		��ʐ؂�ւ����́A�O��l�ۑ��̈���N���A���邱�ƁB					*/
/*																			*/
/****************************************************************************/
void	IROCK_SHR		(void)
{
	WORD	i,	t,	x;
	WORD	chk;
	WORD	pos, ypos, xpos;
	WORD	pat1;
	WORD	pat2;
	WORD*	intr;
	WORD*	addr;
	DWORD	chk2;
	DWORD	mode;
	DWORD	calc;
	WORD	nop[40];
	WORD	moji_col, back_col;

	if (INTROCK_DISP_FLG != ALL_DISP)	return;		/* �޲��ݽ�\�����Ȃ�	*/

	mode  = ((SEQ_PAR_121 << 16) & 0xFFFF0000);		/* ����ۯ�����ݑI��		*/
	mode |=  (SEQ_PAR_120        & 0x0000FFFF);		/* �ޯ�0 �D��			*/
	chk2  = 0x00000001;								/* ����݌���			*/

	for (i=0; i<32; i++){							/* �ޯ�����				*/
		if ((mode & chk2)!= 0x00000000)	break;		/* ����OK				*/
		chk2 = (chk2 << 1);							/* 1�ޯļ��				*/
	}												/*						*/
	if (i == 32)	i = 0;							/* ONż�Ȃ�擪���g�p	*/

	calc  = (DWORD)E_INTROCK_PAT;					/* ��������ݓo�^�ر�擪	*/
	calc += INTR_DAT_OFS;			//V06
	calc += (i * 20 * 2);							/* �̾�Ēl���Z			*/
	addr  = (WORD*)calc;							/*						*/

	intr  = &SEQ_PAR_122;							/* ����ۯ��ް��擪���ڽ	*/
	t	  = 0;										/* ð��� index �ر		*/
	x	  = 0;										/* ٰ�߶���				*/

IROCK_SEARCH:										/* �����J�n				*/
	chk  = 0x0001;									/*						*/
	pat1 = (*addr);									/* ����ۯ� �����ޯ�		*/
	pat2 = (*intr);									/* ����ۯ� ����ޯ�		*/
	if ((pat1 == 0)||(pat2 == 0))					/* ���� or ����ޯ� OFF	*/
		goto	IROCK_SEARCH_NEXT;					/* ����������			*/

	for (i=0; i<16; i++){							/* 16 BIT				*/
		if (((pat1 & chk)!=0)&&((pat2 & chk)!=0)){	/* ���� & ����ޯ� ON	*/
			IROCK_NO[t] = ((x * 16) + i);			/* ����ۯ��ԍ�			*/
			t++;									/* �ԍ�����ޯ���X�V	*/
			if (t >= INTROCK_MAX)					/*						*/
				goto	IROCK_SKIP;					/* �����I��				*/
		}											/*						*/
		chk = (chk << 1);							/* 1�ޯļ��				*/
	}												/*						*/

IROCK_SEARCH_NEXT:									/* ���������			*/
	addr ++;										/* ��������� �X�V		*/
	intr ++;										/* ���ݻ���ڽ�X�V		*/
	x    ++;										/*						*/
	if (x < 20)				goto	IROCK_SEARCH;	/* 20 WORD				*/

	for (i=t; i<INTROCK_MAX; i++)					/* ���g�p��ر			*/
		IROCK_NO[i] = 0xFFFF;						/* ����ۯ��ԍ��ر		*/

IROCK_SKIP:											/* ��������				*/
	for (i=0; i<20; i++)	nop[i]=0x2020;			/* NOP �ް��쐬			*/

//V05r	if (IROCK_NO[0] == IROCK_NO_LAST[0])			/* �ŏ�s�ω��Ȃ�		*/
//V05r		goto	IROCK_WIN_TOP;						/*						*/

	if (IROCK_NO[0] == 0xFFFF){						/* ����ۯ��Ȃ�			*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Disp_moji(INTROCK_POS1,nop,0);				/* LCD������\���E����	*/
#else
	disp_moji_s_color(
		INTROCK_LENG1,							/* ��׸��			*/
		INTROCK_XPOS1,							/* ���o��X�ʒu		*/
		INTROCK_YPOS1,							/* ���o��Y�ʒu		*/
		7,										/* �����F			*/
		GAMENn_HEAD.scr_col,					/* �w�i�F			*/
		0x0202,									/* ��������			*/
		&nop[0],								/* �����i�[���ڽ	*/
		LCD_VBASE								/* �\�����			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG1,							/* ��׸��			*/
		INTROCK_XPOS1,							/* ���o��X�ʒu		*/
		INTROCK_YPOS1,							/* ���o��Y�ʒu		*/
		0x0202									/* ��������			*/
		);
#endif
		goto	IROCK_WIN_TOP;						/*						*/
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_INTROCK_TOP + language_chg);			/* �������ڽ + ���ꔻ��	*/
	calc  = (E_INTROCK_TOP + (language_chg*2));		/* �������ڽ + ���ꔻ��	*/
/********/
	calc += (IROCK_NO[0] * 40);						/* �̾�Ēl���Z			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(INTROCK_POS1,(WORD*)addr,0);			/* LCD������\��		*/
#else
	calc = MES_TABLE_ADR + (IROCK_NO[0] * CHAR_MES_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	calc += 2;
	addr  = (WORD*)calc;							/*						*/
	moji_col = COL_WHITE;//white
	back_col = COL_RED;//red

////	<<< SIT-4 MC ROM��׎w��ɕύX	2014/02/06  >>>
////	if ( IROCK_NO[0]>89-1 ) {
////		moji_col = COL_BLACK;//black
////		back_col = GAMENn_SCR_COL;//��ʽ�ذݐF
////	}
	if ( (IROCK_NO[0] > IROCK_COL_CHG_NO) || (IROCK_COL_CHG_NO == 3465) ) {
		moji_col = COL_BLACK;//black
		back_col = GAMENn_SCR_COL;//��ʽ�ذݐF
	}

	if (SEQ_PAR_113 & BIT_2)			//�������\�������H			//V05r(INS)
	{
		moji_col = COL_BLACK;			//�������\�����F
		back_col = COL_YELLOW;			//�������\�w�i�F
	}
	
	disp_moji_s_color(
		INTROCK_LENG1,							/* ��׸��			*/
		INTROCK_XPOS1,							/* ���o��X�ʒu		*/
		INTROCK_YPOS1,							/* ���o��Y�ʒu		*/
		moji_col,								/* �����F			*/
		back_col,									/* �w�i�F			*/
		0x0202,									/* ��������			*/
		addr,									/* �����i�[���ڽ	*/
		LCD_VBASE								/* �\�����			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG1,							/* ��׸��			*/
		INTROCK_XPOS1,							/* ���o��X�ʒu		*/
		INTROCK_YPOS1,							/* ���o��Y�ʒu		*/
		0x0202									/* ��������			*/
		);
#endif

IROCK_WIN_TOP:										/* ����޳�\��			*/
	if ((WINDOW_NO != 3)&&(WINDOW_NO != 10))		/*						*/
		goto	IROCK_RET;							/* ��\��				*/

	pos = INTROCK_POS2;								/* ����ۯ��\���ʒu���	*/
	ypos = INTROCK_YPOS2;							/* ����ۯ��\���ʒu���	*/
	i	= 0;										/*						*/

IROCK_WIN_LOOP:										/* ����޳�\�� LOOP		*/
	if (IROCK_NO[i] == IROCK_NO_LAST[i])			/* �ω��Ȃ�				*/
		goto	IROCK_WIN_NEXT;						/*						*/

	if (IROCK_NO[i] == 0xFFFF){						/* ����ۯ��Ȃ�			*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Disp_moji(pos,nop,0);						/* LCD������\���E����	*/
#else
		disp_moji_s_color(
			INTROCK_LENG2,							/* ��׸��			*/
			INTROCK_XPOS2,							/* ���o��X�ʒu		*/
			ypos,									/* ���o��Y�ʒu		*/
			0,										/* �����F			*/
			GAMENn_HEAD.scr_col,					/* �w�i�F			*/
			0x0202,									/* ��������			*/
			&nop[0],								/* �����i�[���ڽ	*/
			LCD_VBASE								/* �\�����			*/
			);
		disp_moji_s_rif (
			INTROCK_LENG2,							/* ��׸��			*/
			INTROCK_XPOS2,							/* ���o��X�ʒu		*/
			ypos,									/* ���o��Y�ʒu		*/
			0x0202									/* ��������			*/
			);
#endif
		goto	IROCK_WIN_NEXT;						/*						*/
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/* V00s */
//	calc  = (E_INTROCK_TOP + language_chg);			/* �������ڽ + ���ꔻ��	*/
	calc  = (E_INTROCK_TOP + (language_chg*2));		/* �������ڽ + ���ꔻ��	*/
/********/
	calc += (IROCK_NO[i] * 40);						/* �̾�Ēl���Z			*/
	addr  = (WORD*)calc;							/*						*/
	Disp_moji(pos,addr,0);							/* LCD������\��		*/
#else
	calc = MES_TABLE_ADR + (IROCK_NO[i] * CHAR_MES_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	calc += 2;
	addr  = (WORD*)calc;							/*						*/
	disp_moji_s_color(
		INTROCK_LENG2,							/* ��׸��			*/
		INTROCK_XPOS2,							/* ���o��X�ʒu		*/
		ypos,									/* ���o��Y�ʒu		*/
		0,										/* �����F			*/
		GAMENn_HEAD.scr_col,					/* �w�i�F			*/
		0x0202,									/* ��������			*/
		addr,									/* �����i�[���ڽ	*/
		LCD_VBASE								/* �\�����			*/
		);
	disp_moji_s_rif (
		INTROCK_LENG2,							/* ��׸��			*/
		INTROCK_XPOS2,							/* ���o��X�ʒu		*/
		ypos,									/* ���o��Y�ʒu		*/
		0x0202									/* ��������			*/
		);
#endif

IROCK_WIN_NEXT:										/* ����޳�\�����s		*/
	pos ++;											/* �s��шʒu�X�V		*/
	ypos += (16*2);									/* �s��шʒu�X�V		*/
	i   ++;											/* �����				*/
	if (i < INTROCK_MAX)	goto  IROCK_WIN_LOOP;	/* 						*/

IROCK_WIN_END:										/* ����޳�\������		*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	for (i=0; i<40; i++)	nop[i] = 0xFFFF;		/* LINE �ް��쐬		*/
//V00m	Lcd_draw(0,0, 96,40,nop);						/* LINE �`��			*/
//V00o����
	Lcd_draw(0,0, 96,40,nop);						/* LINE �`��			*/
	nop[36] = 0xFF80;								/*						*/
//V00m	Lcd_draw(0,2,207,37,nop);						/*						*/
//V00o����
	Lcd_draw(0,2,207,37,nop);						/*						*/
#else
	for (i=0, xpos=0, ypos=192; i<640; i++, xpos++)	/* LINE �ް��쐬		*/
	{
		LCD_VBASE[ypos][xpos] = 0;
		LCD_VRAM[ypos][xpos] = 0;
	}
#endif

IROCK_RET:											/* �\������				*/
	for (i=0; i<INTROCK_MAX; i++)					/* �ԍ����O����߰	*/
		IROCK_NO_LAST[i] = IROCK_NO[i];				/*						*/
}


/****************************************************************************/
/*																			*/
/*	�����C���^�[���b�N�̃L�����N�^�f�[�^�o�͏���		2009/07/14			*/
/*																			*/
/*		�V�[�P���T�̃C���^�[���b�N�I���i�R�Q���[�h�j�ɉ������p�^�[����		*/
/*		�R�Q�O�r�b�g�̃C���^�[���b�N�\�����`�F�b�N����B					*/
/*		�`�F�b�N�p�^�[���́A���[�U��`�B									*/
/*		�A�h���X�����Ɍ������A��D��ŊY�����郁�b�Z�[�W��\������B		*/
/*		�\���́A��ʍŏ�s�ƃE�B���h�E�ɍs���B�i�ő匏�� 8�j				*/
/*																			*/
/*		SEQ_PAR_120			�F	�V�[�P���T�E�C���^�[���b�N�I��	���16bit	*/
/*		SEQ_PAR_121			�F	�V�[�P���T�E�C���^�[���b�N�I��	����16bit	*/
/*		SEQ_PAR_122			�F	�V�[�P���T�E�C���^�[���b�N�r�b�g��擪		*/
/*																			*/
/*		IROCK_OUT_NO	 [8]	�F	�C���^�[���b�N�����ԍ�					*/
/*		IROCK_OUT_NO_LAST[8][8]	�F	�C���^�[���b�N�����ԍ��ɑ΂���L�����N�^*/
/*																			*/
/****************************************************************************/
void	IROCK_SHR_OUT		(void)
{
	BYTE*	sadr;
	WORD	i,	t,	x;
	WORD	chk;
	WORD	pat1;
	WORD	pat2;
	WORD*	intr;
	WORD*	addr;
	DWORD	chk2;
	DWORD	mode;
	DWORD	calc;
	BYTE	nop[8];

	if ( (SEQ_024_SV & BIT_6) == 0 )	return;

	mode  = ((SEQ_PAR_121 << 16) & 0xFFFF0000);		/* ����ۯ�����ݑI��		*/
	mode |=  (SEQ_PAR_120        & 0x0000FFFF);		/* �ޯ�0 �D��			*/
	chk2  = 0x00000001;								/* ����݌���			*/

	for (i=0; i<32; i++){							/* �ޯ�����				*/
		if ((mode & chk2)!= 0x00000000)	break;		/* ����OK				*/
		chk2 = (chk2 << 1);							/* 1�ޯļ��				*/
	}												/*						*/
	if (i == 32)	i = 0;							/* ONż�Ȃ�擪���g�p	*/

	calc  = (DWORD)E_INTROCK_PAT;					/* ��������ݓo�^�ر�擪	*/
	calc += INTR_DAT_OFS;			//V06
	calc += (i * 20 * 2);							/* �̾�Ēl���Z			*/
	addr  = (WORD*)calc;							/*						*/

	intr  = &SEQ_PAR_122;							/* ����ۯ��ް��擪���ڽ	*/
	t	  = 0;										/* ð��� index �ر		*/
	x	  = 0;										/* ٰ�߶���				*/

IROCK_SCH_OUT:										/* �����J�n				*/
	chk  = 0x0001;									/*						*/
	pat1 = (*addr);									/* ����ۯ� �����ޯ�		*/
	pat2 = (*intr);									/* ����ۯ� ����ޯ�		*/
	if ((pat1 == 0)||(pat2 == 0))					/* ���� or ����ޯ� OFF	*/
		goto	IROCK_SCH_OUT_NEXT;					/* ����������			*/

	for (i=0; i<16; i++){							/* 16 BIT				*/
		if (((pat1 & chk)!=0)&&((pat2 & chk)!=0)){	/* ���� & ����ޯ� ON	*/
			IROCK_OUT_NO[t] = ((x * 16) + i);			/* ����ۯ��ԍ�			*/
			t++;									/* �ԍ�����ޯ���X�V	*/
			if (t >= 8)								/*						*/
				goto	IROCK_SCH_OUT_SKIP;			/* �����I��				*/
		}											/*						*/
		chk = (chk << 1);							/* 1�ޯļ��				*/
	}												/*						*/

IROCK_SCH_OUT_NEXT:									/* ���������			*/
	addr ++;										/* ��������� �X�V		*/
	intr ++;										/* ���ݻ���ڽ�X�V		*/
	x    ++;										/*						*/
	if (x < 20)				goto	IROCK_SCH_OUT;	/* 20 WORD				*/

	for (i=t; i<8; i++)								/* ���g�p��ر			*/
		IROCK_OUT_NO[i] = 0xFFFF;						/* ����ۯ��ԍ��ر		*/

IROCK_SCH_OUT_SKIP:											/* ��������				*/
	for (i=0; i<8; i++)	nop[i]=0x20;				/* NOP �ް��쐬			*/


	for (i=0; i<8; i++)
	{
		if (IROCK_OUT_NO[i] == 0xffff)
		{
			break;
		}
		else {
			calc  = E_INTROCK_CHAR;							/* �������ڽ	*/
			calc += INTR_DAT_OFS;			//V06
			calc += (IROCK_OUT_NO[i] * 8);						/* �̾�Ēl���Z			*/
			sadr  = (BYTE*)calc;							/*						*/
			for (t=0; t<8; t++)
			{
				IROCK_CHAR[i][t] = *sadr;
				sadr++;
			}
		}
	}

	for (; i<8; i++)
	{
		for (t=0; t<8; t++)
		{
			IROCK_CHAR[i][t] = nop[t];
		}
	}

}


/****************************************************************************/
