/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						���[���b�g�\������									*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long


//#define		DEBUG_AUTO
#define		DEG_ZENKAKU
#define		DEG_DISP_NEW


// #define	SUMILATE
#ifdef		SUMILATE
#include	<stdio.h>
#include	<stdlib.h>
#endif

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		BIT_06		0x0040

#define		ALL_DISP	0xFF					/* �S��ʕ\��				*/
#define		HALF_DISP	0x55					/* �E�B���h�E�\��			*/
#define		NO_DISP		0x00					/* �\�����Ȃ�				*/

EXTRN		DWORD		DEG_DISP_TBL	  [];	/* 4�{�p�ް��擪���ڽ�z��	*/
EXTRN		DWORD		RULET_TBL_BASE	  [];	/* ���[���b�g���\���f�[�^	*/
EXTRN		DWORD		RULET_TBL_BASE_00 [];	/* ���[���b�g���\���f�[�^	*/
EXTRN		DWORD		HAN_RULET_TBL_BASE_00 [];	/* ���[���b�g���\���f�[�^ 2003-01-24 */
EXTRN		DWORD		RULET_BASE_TBL_TBL[];	/* ���[���b�g�g�\���f�[�^	*/
EXTRN		DWORD		HAN_RULET_BASE_TBL_TBL[];	/* ���[���b�g�g�\���f�[�^ 2003-01-24 */

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
EXTRN		DWORD		DEG4_DISP_TBL	  [];	/* 4�{�p�ް��擪���ڽ�z��	*/
#endif

/* �������� */
void		DEG_DISP		(void);				/* �p�x�S�{�p�\������		*/
void		RULET_GAMEN_DISP(void);				/* ���[���b�g��ʕ\��		*/
void		RULET_GAMEN_INIT(void);				/* ���[���b�g�����ݒ�		*/
void		RULET_GAMEN_ALL	(void);				/* ���[���b�g���S�`��		*/
void		RULET_GAMEN_CLR	(void);				/* ���[���b�g���S�N���A		*/
void		RULET_DISP_SUB	(WORD);				/* ���`��T�u���[�`��		*/
void		RULET_CLEAR_SUB	(WORD);				/* �������T�u���[�`��		*/
void		RULET_CLEAR_SUB2(WORD);				/* �������T�u���[�`���Q		*/

#if ( SIT_TYPE_SEL == TYPE_SIT4 )
#include	"ssc_rulet_pos.c"
#endif


/****************************************************************************/
/*																			*/
/*	�p�x�����\������		�F	�S�{�p�����\��								*/
/*																			*/
/*		�G���R�[�_�̊p�x�f�[�^���ω�������A�p�x�i�����R���j��\������B	*/
/*		�k�b�c�P�ɁA�P�������\���~�R����s���B							*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	�F	�p�x�f�[�^		�i�����_�P�� 0�`3599�܂Łj	*/
/*																			*/
/*		ENCO_DATA_BCD		�F	�p�x�f�[�^���i�[����						*/
/*		DEG_DISP_FLG		�F	�p�x�\���t���O								*/
/*		DEG_DISP_LST		�F	�O��l�ۑ��̈�								*/
/*		DEG_DISP_TBL		�F	�S�{�p�f�[�^�̃A�h���X�e�[�u��				*/
/*																			*/
/*		��ʐ؂�ւ����́A�O��l�ۑ��̈���N���A���邱�ƁB					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	DEG_DISP		(void)
{
	WORD	i,		t,		x;
	WORD	C1,		C2;
	WORD	disp,	indx;
	WORD	keta,	line;
	WORD	data[3];
	WORD	buff[4];
	BYTE*	addr;
	DWORD	calc;

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* �p�x�\�����Ȃ�		*/

//	C1 = PVP_NOW_ANGLE00;							/* BCD�ް��쐬			*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCD�ް��쐬			*/

	C2 = (C1 % 10);
	ENCO_DATA_BCD = C2;
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 4);
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 8);						/* �ۑ�					*/

	if (ENCO_DATA_BCD == DEG_DISP_LST)	return;		/* �p�x�ް��ω��Ȃ�		*/
	DEG_DISP_LST = ENCO_DATA_BCD;					/* �O��l�ۑ�			*/

	data[2] = (ENCO_DATA_BCD & 0x0F00) >> 8;		/* �\���p�ް��i�[		*/
	data[1] = (ENCO_DATA_BCD & 0x00F0) >> 4;		/*						*/
	data[0] = (ENCO_DATA_BCD & 0x000F);				/*						*/

	if (data[2] ==  0){								/* ���ݸ�\��CHECK		*/
		data[2] =  10;								/* 10 �����ݸ�\��		*/
		if (data[1] ==  0)							/*						*/
			data[1] =  10;							/*						*/
	}

	for(i=0; i<3; i++){								/* �R����				*/
		disp  = (2 - i);							/* �p�x���l 2�`0��		*/
		keta  = (4 + (4 * i));						/* �\�����ʒu			*/
		line  = (4 * 16);							/* �\���s4��іڂ���		*/
													/*						*/
		indx  = data[disp];							/* �\������				*/
		calc  = DEG_DISP_TBL[indx];					/* �\��ð��ِ擪���ڽ	*/
		addr  = (BYTE*)calc;						/* �\���ް��擪���ڽ	*/

		for(t=0; t<32; t++){						/* �c2��ѕ� 32bit		*/
			for(x=0; x<4; x++){						/* �\���ް��i�[			*/
				buff[x] = ((*addr) & 0x00FF);		/*						*/
				addr ++;							/*						*/
			}										/*						*/
			Lcd_draw(1,keta,line,4,buff);			/* LCD1 1Line(1dot)�\��	*/
			line ++;								/*						*/
		}											/*						*/
	}
}
#else
#ifdef DEG_DISP_NEW
/*������������������	�r�h�s�|�S�p�i�V�j	������������������*/
void	DEG_DISP		(void)
{
	WORD	C1, C2, xdot, ydot, startx, starty, wk2b;
	WORD	i, t, x, j;
	WORD	disp,	indx;
	WORD	keta,	line;
	WORD	data[3];
	WORD	buff;
	WORD*	addr;
	DWORD	calc;

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* �p�x�\�����Ȃ�		*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCD�ް��쐬			*/
#ifdef	DEBUG_AUTO
	C1 = (DEBUG_CNT / 10);					/* BCD�ް��쐬			*/
#endif

	C2 = (C1 % 10);
	ENCO_DATA_BCD = C2;
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 4);
	C1 = (C1 / 10);
	C2 = (C1 % 10);
	ENCO_DATA_BCD |= (C2 << 8);						/* �ۑ�					*/

	if (ENCO_DATA_BCD == DEG_DISP_LST)	return;		/* �p�x�ް��ω��Ȃ�		*/
	DEG_DISP_LST = ENCO_DATA_BCD;					/* �O��l�ۑ�			*/

	data[2] = (ENCO_DATA_BCD & 0x0F00) >> 8;		/* �\���p�ް��i�[		*/
	data[1] = (ENCO_DATA_BCD & 0x00F0) >> 4;		/*						*/
	data[0] = (ENCO_DATA_BCD & 0x000F);				/*						*/

	if (data[2] ==  0){								/* ���ݸ�\��CHECK		*/
		data[2] =  10;								/* 10 �����ݸ�\��		*/
		if (data[1] ==  0)							/*						*/
			data[1] =  10;							/*						*/
	}

	/* 100���� */
	startx = 64;
	starty = 128;
	indx  = data[2];							/* �\������				*/
	calc  = DEG4_DISP_TBL[indx];				/* �\��ð��ِ擪���ڽ	*/
	addr  = (WORD*)calc;						/* �\���ް��擪���ڽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* �c64bit				*/
		for(x=0; x<4; x++){						/* �\���ް��i�[			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dot�f�[�^���ޯĂ������Ă���H
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	/* 010���� */
	startx = 64+64;
	starty = 128;
	indx  = data[1];							/* �\������				*/
	calc  = DEG4_DISP_TBL[indx];				/* �\��ð��ِ擪���ڽ	*/
	addr  = (WORD*)calc;						/* �\���ް��擪���ڽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* �c64bit				*/
		for(x=0; x<4; x++){						/* �\���ް��i�[			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dot�f�[�^���ޯĂ������Ă���H
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	/* 001���� */
	startx = 64+64+64;
	starty = 128;
	indx  = data[0];							/* �\������				*/
	calc  = DEG4_DISP_TBL[indx];				/* �\��ð��ِ擪���ڽ	*/
	addr  = (WORD*)calc;						/* �\���ް��擪���ڽ	*/
	xdot = startx;
	ydot = starty;
	for(t=0; t<64; t++){						/* �c64bit				*/
		for(x=0; x<4; x++){						/* �\���ް��i�[			*/
			buff = *addr;						/*						*/
			addr ++;							/*						*/
			for ( j=0,wk2b=0x8000; j<16; j++,wk2b>>=1 ) {
				if ( buff & wk2b ) {					// dot�f�[�^���ޯĂ������Ă���H
					LCD_VBASE[ydot][xdot++] = 0;
				}
				else {
					LCD_VBASE[ydot][xdot++] = GAMENn_SCR_COL;
				}
			}
		}
		xdot = startx;
		starty++;
		ydot = starty;
	}

	disp_moji_s_rif (
		6,		/*t_p->M_LEN,*/
		8*8,	/*t_p->X_POS,*/
		8*16,	/*t_p->Y_POS,*/
		0x0404	/*t_p->SIZE,*/
		);
}
#else
/*������������������	�r�h�s�|�S�p�i���j	������������������*/
void	DEG_DISP		(void)
{
	WORD	C1;
	UNi		i, j, k;
	UNb		wk[16], wk1[16];
	UNs		c_wk[16], w_bf, bcd_d;
	char	c_wk1[16];

	if (DEG_DISP_FLG  != ALL_DISP)		return;		/* �p�x�\�����Ȃ�		*/
	C1 = (PVP_NOW_ANGLE_RNA / 10);					/* BCD�ް��쐬			*/
#ifdef	DEBUG_AUTO
	C1 = (DEBUG_CNT / 10);					/* BCD�ް��쐬			*/
#endif

	memset(&wk[0], E_AS_SP, 16);					//�̈� ��߰� �ر

	bcd_d = HEX_BCD4(C1);					//HEX �� BCD �ϊ�
	BCD_ASCII(bcd_d, &wk[0]);					//BCD��ASCII �ϊ�

	for(i = 7; i > 0 ; i--) {
		if( wk[i-1] == E_AS_TEN){				//�h.�h�@ �mASCII���ށn
			break;
		}
		else if(wk[i] == '0' || wk[i] == E_AS_SP) {
			wk[i] = E_AS_SP;					//�X�y�[�X�mASCII���ށn
		}
		else {
			break;
		}
	}
	for( j=0,i=3 ; i > 0 ; i--, j++ ){
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

#ifdef	DEG_ZENKAKU
	i = 3;
	k = i;
	for( j=0 ; i > 0 ; i--, j++ ){
		wk1[j] = wk[i-1];
	}
	Ascii_Sjis(k, &wk1[0], &c_wk[0]);			//ASCII -> S-JIS �ϊ�
#endif

	disp_moji_s_color (
		6,					/*t_p->M_LEN,*/
		8*8,				/*t_p->X_POS,*/
		8*16,				/*t_p->Y_POS,*/
		0,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,		/*t_p->B_COL1,*/
		0x0404,				/*t_p->SIZE,*/
		&c_wk[0], 
		LCD_VBASE
		);

	disp_moji_s_rif (
		6,		/*t_p->M_LEN,*/
		8*8,	/*t_p->X_POS,*/
		8*16,	/*t_p->Y_POS,*/
		0x0404	/*t_p->SIZE,*/
		);
}
#endif
#endif


/****************************************************************************/
/*																			*/
/*	���[���b�g��ʕ\��														*/
/*																			*/
/*		�G���R�[�_�̊p�x�ɉ����āA�k�b�c�Q�Ɂ���`�悷��B					*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	�F	�p�x�f�[�^		�i�����_�P�� 0�`3599�܂Łj	*/
/*		PVP_TAIKITEN_POS	�F	�ҋ@�_�f�[�^	�i�����_�P�� 0�`3599�܂Łj	*/
/*		HS_PVP_TAKIKI_FLG	�F	�ҋ@�_�ʉ߃t���O�i�ʉ߁��P�j				*/
/*																			*/
/*		SEQ_PAR_101			�F	�V�[�P���T�E�������[���b�g�\������			*/
/*		SEQ_PAR_222			�F	�V�[�P���T�E���]�^�t�]						*/
/*																			*/
/*		CB1_SPMDAT_PV		�F	�r�o�l���ݒl								*/
/*		SYS_HIGHSPM_B1		�F	�����`��J�n�r�o�l�l						*/
/*		SYS_LOWSPM_B1		�F	�����`���~�r�o�l�l						*/
/*																			*/
/*		TAIKITEN_DAT		�F	�O��ҋ@�_�f�[�^�i�P�^�P�O�j				*/
/*		TAIKI_ZEN_POS		�F	�O��`��ʒu	�i�P�^�P�O�j				*/
/*		TAIKI_ZEN_MOD		�F	�O��`�����	�i���]���O�^�t�]���O�j		*/
/*																			*/
/*		RULET_DISP_FLG		�F	���[���b�g�\���t���O�i����޳�\������0x55�j	*/
/*		RULET_HIGH_FLG		�F	�����`��t���O								*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_DISP(void)
{
	WORD	i,		t;
	WORD	real_deg;
	WORD	real_tik;
	WORD	temp;
	WORD	deg0,	deg1;
	WORD	tk_0,	tk_1;
	WORD	md_0,	md_1;
	WORD	wk_0,	wk_1;
	WORD	cnt;

	if (RULET_DISP_FLG == NO_DISP)		return;		/* ٰگĕ\�����Ȃ�		*/

//	�����`��i�h��Ԃ��j���� ///////////////////////////////////////////////
//	if ((SEQ_PAR_101 & BIT_06) != 0){				/* ٰگč����\�����H	*/
//		if (RULET_HIGH_FLG == 0){					/* ����ٰگĕ`��łȂ�	*/
//			if (CB1_SPMDAT_PV > SYS_HIGHSPM_B1)		/* SPM HIGH����l�ȏ�H	*/
//				RULET_HIGH_FLG = ALL_DISP;			/* ����ٰگĕ`��ON		*/
//		}											/*						*/
//		else{										/*						*/
//			if (CB1_SPMDAT_PV <= SYS_LOWSPM_B1)		/* SPM LOW����l�ȉ��H	*/
//				RULET_HIGH_FLG = NO_DISP;			/* ����ٰگĕ`��OFF		*/
//				TAIKI_ZEN_POS  = TAIKITEN_DAT;		/* �O�ʒu��ҋ@�_�ɂ���	*/
//		}											/*						*/
//		if (RULET_HIGH_FLG == ALL_DISP){			/* ����ٰگĕ`��ON		*/
//			RULET_GAMEN_ALL();						/* �S�`��				*/
//			return;									/*						*/
//		}											/*						*/
//	}												/*						*/
//	else											/*						*/
//		RULET_HIGH_FLG = 0;							/* ����ٰگĕ`��OFF		*/

	RULET_HIGH_FLG = 0;								/* DEBUG				*/

//	�O��l�^����l�ݒ� ///////////////////////////////////////////////////////
	real_deg = (PVP_NOW_ANGLE_RNA / 10);			/* �p�x�ް��擾			*/
#ifdef	DEBUG_AUTO
	real_deg = (DEBUG_CNT / 10);			/* �p�x�ް��擾			*/
#endif
	deg1	 = (real_deg / 10);						/* �ݺ��ޒl	1/10		*/
	temp	 = (real_deg % 10);						/*						*/
	if (temp >=  5)					deg1 ++;		/* �l�̌ܓ�				*/
	if (deg1 >= 36)					deg1 = 0;		/* 360�x = 0�x			*/
	deg0		  = TAIKI_ZEN_POS;					/* �O��`��ʒu			*/
	TAIKI_ZEN_POS = deg1;							/*						*/

	real_tik = (PVP_TAIKITEN_POS / 10);				/* �ҋ@�_�ް��擾		*/
	tk_1	 = (real_tik / 10);						/* �ҋ@�_�l	1/10		*/
	temp	 = (real_tik % 10);						/*						*/
	if (temp >=  5)					tk_1 ++;		/* �l�̌ܓ�				*/
	if (tk_1 >= 36)					tk_1 = 0;		/* 360�x = 0�x			*/
	tk_0		  = TAIKITEN_DAT;					/* �O��ҋ@�_			*/
	TAIKITEN_DAT  = tk_1;							/* �ҋ@�_�ۑ�			*/

	md_1 = (SEQ_PAR_222 & BIT_06) ^ BIT_06;			/* ��]����				*/ //2009-10-07 SHIMA �U��q
//	md_1 = 0xFFFF;									/* DEBUG	���]�Œ�	*/
//	md_1 = 0x0000;									/* DEBUG	�t�]�Œ�	*/
	md_0		  = TAIKI_ZEN_MOD;					/* �O��]����			*/
	TAIKI_ZEN_MOD = md_1;							/* ����]�����ۑ�		*/

//	����`�攻�� /////////////////////////////////////////////////////////////
	if ((tk_0 != tk_1)	||							/* �ҋ@�_�ω���			*/
		(md_0 != md_1)	||							/* ��]�����ω���		*/
		(HS_PVP_TAKIKI_FLG != 0)){					/* �ҋ@�_�ʉߎ�			*/
													/*						*/
		RULET_GAMEN_CLR();							/* ���S�ر				*/
													/*						*/
		if(md_1 != 0){								/* ���]����				*/
			if(deg1 >= tk_1)	cnt =  deg1;		/* ��������				*/
			else				cnt = (deg1 + 36);	/*						*/
			cnt -= tk_1;							/*						*/
			cnt += 1;								/* �`���				*/
			t    = tk_1;							/* �`��J�n�ʒu			*/
		}											/*						*/
		else{										/* �t�]����				*/
			if(tk_1 >= deg1)	cnt =  tk_1;		/* ��������				*/
			else				cnt = (tk_1 + 36);	/*						*/
			cnt -= deg1;							/*						*/
			cnt += 1;								/* �`���				*/
			t    = deg1;							/* �`��J�n�ʒu			*/
		}											/*						*/
		for(i=0; i<cnt; i++){						/*						*/
			RULET_DISP_SUB(t);						/* �`����ٰ��			*/
			t++;									/*						*/
			if (t >= 36)	t = 0;					/*						*/
		}											/*						*/
													/*						*/
		HS_PVP_TAKIKI_FLG = 0;						/* �ҋ@�_�ʉ��׸޸ر	*/
		return;										/*						*/
	}												/*						*/

	if	(deg1 == tk_1){								/* �ҋ@�_�ƈ�v��		*/
		if (deg0 != deg1)	RULET_GAMEN_CLR();		/* ���S�ر				*/
		RULET_DISP_SUB (tk_1);						/* �`����ٰ��			*/
		TAIKITEN_FLG = 0;							/* �ҋ@�_�ʉ��׸޸ر	*/
		return;										/*						*/
	}												/*						*/

	if (deg1 == deg0)								/* �p�x�ω��Ȃ��̏ꍇ	*/
		return;										/* �Ȃɂ����Ȃ�			*/

//	�ʏ�`�揈�� /////////////////////////////////////////////////////////////
	if (md_1 != 0){									/* ���]����				*/
		if (deg0 >= tk_1)	wk_0 =  deg0;			/* �O�ʒu�O�␳			*/
		else				wk_0 = (deg0 + 36);		/*						*/
		if (deg1 >= tk_1)	wk_1 =  deg1;			/* ���ʒu�O�␳			*/
		else				wk_1 = (deg1 + 36);		/*						*/
		wk_0 -= tk_1;								/* �ҋ@�_����̑��ΐ�	*/
		wk_1 -= tk_1;								/*						*/
													/*						*/
		if (wk_1 >= wk_0){							/* �`��					*/
			cnt	= (wk_1 - wk_0) + 1;				/* ��������				*/
			t	= deg0;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_DISP_SUB(t);					/* �`����ٰ��			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
		else{										/* �ر					*/
			cnt = (wk_0 - wk_1);					/* ��������				*/
			t	= (deg1 + 1);						/*						*/
			if (t >= 36)		t = 0;				/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_CLEAR_SUB(t);					/* �ر���ٰ��			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
	}
	else{											/* �t�]����				*/
		if (deg0 > tk_1)	wk_0 =  deg0;			/* �O�ʒu�O�␳			*/
		else				wk_0 = (deg0 + 36);		/*						*/
		if (deg1 > tk_1)	wk_1 =  deg1;			/* ���ʒu�O�␳			*/
		else				wk_1 = (deg1 + 36);		/*						*/
		wk_0 -= tk_1;								/* �ҋ@�_����̑��ΐ�	*/
		wk_1 -= tk_1;								/*						*/
													/*						*/
		if (wk_0 >= wk_1){							/* �`��					*/
			cnt = (wk_0 - wk_1) + 1;				/* ��������				*/
			t	= deg1;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_DISP_SUB(t);					/* �`����ٰ��			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
		else{										/* �ر					*/
			cnt	= (wk_1 - wk_0);					/* ��������				*/
			t	= deg0;								/*						*/
			for(i=0; i<cnt; i++){					/*						*/
				RULET_CLEAR_SUB(t);					/* �ر���ٰ��			*/
				t++;								/*						*/
				if (t >= 36)	t = 0;				/*						*/
			}										/*						*/
		}											/*						*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	���[���b�g��ʏ����ݒ�	�F	�ŏ��ɂP��R�[�����邱�ƁB					*/
/*																			*/
/*		�k�b�c�P�Ƀ��[���b�g�̘g�ƂS�����̔��k�L����\������B				*/
/*		�k�b�c�Q�Ɂ��̃N���A�f�[�^��\�����Ă����B							*/
/*																			*/
/*		RURET_BASE_TBL_TBL	�F	�g�\���f�[�^�̃A�h���X�e�[�u��				*/
/*		RULET_TBL_BASE_00	�F	���\���f�[�^�̃A�h���X�e�[�u��				*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	RULET_GAMEN_INIT(void)
{
	WORD	i,		t,		x;
	WORD	keta,	line,	cnt;
	WORD	gyou,	dotl;
	WORD	buff[20];
	WORD	temp;
	WORD*	addr;
	BYTE*	bitd;
	DWORD	calc;

	for(i=0; i<20; i++){							/* �g�~�Q�O��			*/
		/* V00m */
		if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H
			calc  = HAN_RULET_BASE_TBL_TBL[i];		/* �\��ð��ِ擪���ڽ	*/  /* �ē��쐬 2003-01-24 */
		}
		else {
			calc  = RULET_BASE_TBL_TBL[i];			/* �\��ð��ِ擪���ڽ	*/
		}
		addr  = (WORD*)calc;						/* �\���ް��擪���ڽ	*/
													/*						*/
		line  = ((*addr) / 40);						/* �\���s�ʒu			*/
		addr++;										/*						*/
		keta  =  (*addr);							/* �\�����ʒu			*/
		addr++;										/*						*/
		cnt   = ((*addr) - keta + 1);				/* �\����ѐ�			*/
		addr++;										/*						*/
		addr++;										/* SKIP					*/
		bitd  = (BYTE*)addr;						/* �޲ı����p			*/

		for(t=0; t<16; t++){							/* �c1��ѕ� 16bit		*/
			gyou	 = (line / 16);						/* �s�ʒu�Z�o			*/
			dotl	 = (line % 16);						/* �[���h�b�g			*/
			for(x=0; x<cnt; x++){						/* �\���ް��i�[			*/
				buff[x] = ((*bitd) & 0x00FF);			/* �^�ϊ�				*/
				bitd++;									/* �޲ı��ڽ�X�V		*/
				LCD_WORK1[gyou][dotl][keta+x]=buff[x];	/* �\���ް��i�[			*/
			}											/*						*/
			Lcd_draw(0,keta,line,cnt,buff);				/* LCD1 1Line(1dot)�\��	*/
			line ++;									/*						*/
		}
	}

	for(i=0; i<4; i++){								/* ���~�S��				*/
		/* V00m */
		if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H
			calc  = HAN_RULET_TBL_BASE_00[i];		/* �\��ð��ِ擪���ڽ	*/  /* �ē��쐬 2003-01-24 */
		}
		else {
			calc  = RULET_TBL_BASE_00[i];			/* �\��ð��ِ擪���ڽ	*/
		}
		addr  = (WORD*)calc;						/* �\���ް��擪���ڽ	*/
													/*						*/
		line  = ((*addr) / 40);						/* �\���s�ʒu			*/
		keta  = ((*addr) % 40);						/* �\�����ʒu			*/
		addr++;										/*						*/

		for(t=0; t<8; t++){								/* �c1/2��ѕ� 8bit	*/
			gyou	 = (line / 16);						/* �s�ʒu�Z�o		*/
			dotl	 = (line % 16);						/* �[���h�b�g		*/
			buff[0]  = LCD_WORK1[gyou][dotl][keta  ];	/* ���ݕ\���ް�		*/
			buff[1]  = LCD_WORK1[gyou][dotl][keta+1];	/*					*/
			buff[0] |= (((*addr) & 0xFF00) >> 8);		/* ���ް����㏑��	*/
			buff[1] |=  ((*addr) & 0x00FF);				/*					*/
			Lcd_draw(0,keta,line,2,buff);				/* LCD1 1Line�\��	*/
			addr ++;									/*					*/
			line ++;									/*					*/
			LCD_WORK1[gyou][dotl][keta  ] = buff[0];	/* �\���ް��i�[		*/
			LCD_WORK1[gyou][dotl][keta+1] = buff[1];	/*					*/
		}												/*					*/
	}

	TAIKI_ZEN_POS	= TAIKITEN_DAT;					/* �`��O�ʒu��ҋ@�_��	*/
	temp			= RULET_DISP_FLG;				/* �ꎞ�ۑ�				*/
	RULET_DISP_FLG	= ALL_DISP;						/* �S��ʕ\��			*/
	RULET_GAMEN_CLR	();								/* LCD2 �� �ر			*/
	RULET_DISP_FLG	= temp;							/*						*/
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	RULET_GAMEN_INIT(void)
{
	WORD	temp;
	UNb		*rulet_t1;

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H	V01y
#include "ssc_circleHAN.c"
	}
	else {
#include "ssc_circle.c"
	}

	TAIKI_ZEN_POS	= TAIKITEN_DAT;					/* �`��O�ʒu��ҋ@�_��	*/
	temp			= RULET_DISP_FLG;				/* �ꎞ�ۑ�				*/
	RULET_DISP_FLG	= ALL_DISP;						/* �S��ʕ\��			*/
	RULET_GAMEN_CLR	();								/* LCD2 �� �ر			*/
	RULET_DISP_FLG	= temp;							/*						*/
}
#endif
/****************************************************************************/
/*																			*/
/*	���[���b�g�S�`��	�i���g�p�j											*/
/*																			*/
/*		�k�b�c�Q�́��̈��S�ĕ`�悷��B�`��T�u���[�`�����R�[������B		*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_ALL	(void)
{
	WORD	i;
	for(i=0; i<36; i++){							/* ���~�R�U��			*/
		RULET_DISP_SUB	(i);						/* �`����ٰ��			*/
	}
}
/****************************************************************************/
/*																			*/
/*	���[���b�g�S�N���A														*/
/*																			*/
/*		�k�b�c�Q�́��̈��S�ăN���A����B�N���A�T�u���[�`���Q���R�[������B*/
/*																			*/
/****************************************************************************/
void	RULET_GAMEN_CLR	(void)
{
	WORD	i;
	for(i=0; i<36; i++){							/* ���~�R�U��			*/
		RULET_CLEAR_SUB2(i);						/* �ر���ٰ��			*/
	}
}
/****************************************************************************/
/*																			*/
/*	���[���b�g�`��T�u���[�`��												*/
/*																			*/
/*		�k�b�c�Q�́��̈��`�悷��B										*/
/*																			*/
/*		RULET_DISP_FLG	�F	���[���b�g�\���t���O�i����޳�\���� = 0x55�j		*/
/*		RULET_TBL_BASE	�F	���\���f�[�^�̃A�h���X�e�[�u��					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	RULET_DISP_SUB	(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD DRAW  �� %d \n",i);
	return;
#endif

	/* V00m */
	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H
		if (i > 18)	return;							/* �`�潷���			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 9)&&(i <= 27))	return;			/* �`�潷���			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[i];					/* �\��ð��ِ擪���ڽ	*/
	addr	= (WORD*)calc;							/* �\���ް��擪���ڽ	*/

	line	= ((*addr) / 40);						/* �\���s�ʒu			*/
	keta	= ((*addr) % 40);						/* �\�����ʒu			*/
	addr++;											/*						*/

	for(t=0; t<8; t++){								/* �c1/2��ѕ� 8bit		*/
		gyou	 = (line / 16);						/* �s�ʒu�Z�o			*/
		dotl	 = (line % 16);						/* �[���h�b�g			*/
													/*						*/
		buff[0]  = LCD_WORK2[gyou][dotl][keta  ];	/* ���ݕ\���ް�			*/
		buff[1]  = LCD_WORK2[gyou][dotl][keta+1];	/*						*/
		buff[0] |= (((*addr) & 0xFF00) >> 8);		/* ���ް����㏑��		*/
		buff[1] |=  ((*addr) & 0x00FF);				/*						*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)�\��	*/
		addr ++;									/*						*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* �\���ް��i�[			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	RULET_DISP_SUB	(WORD i)
{
	UNs		MARU, col;

	MARU = 0x819C;	//��

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H	V01y
		if (i > 18)	return;							/* �`�潷���			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 10)&&(i <= 26))	return;			/* �`�潷���			*/
	}												/*						*/

	col = COL_YELLOW;//YELLOW
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = COL_RED;//RED
	}

	if (SEQ_050_SV & BIT_1) {						//���]�@�H	V06b
		if (i==rulet_taiki_pos1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//�������@�H	V06b
		if ((i==rulet_taiki_pos1) || (i==rulet_taiki_pos2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,							/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],		/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],		/*t_p->Y_POS,*/
		col,						/*t_p->C_COL,*/
		GAMENn_SCR_COL,				/*t_p->B_COL1,*/
		0x0101,						/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}
#endif
/****************************************************************************/
/*																			*/
/*	���[���b�g�`��N���A�T�u���[�`��										*/
/*																			*/
/*		�k�b�c�Q�́��̈���N���A����B										*/
/*																			*/
/*		RULET_DISP_FLG	�F	���[���b�g�\���t���O�i����޳�\���� = 0x55�j		*/
/*		RULET_TBL_BASE	�F	���\���f�[�^�̃A�h���X�e�[�u��					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	RULET_CLEAR_SUB	(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD CLEAR �� %d \n",i);
	return;
#endif

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 9)&&(i <= 27))	return;			/* �`�潷���			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[ i ];					/* �\��ð��ِ擪���ڽ	*/
	addr	= (WORD*)calc;							/* �\���ް��擪���ڽ	*/

	line	= ((*addr) / 40);						/* �\���s�ʒu			*/
	keta	= ((*addr) % 40);						/* �\�����ʒu			*/
	addr++;											/*						*/

	for(t=0; t<8; t++){								/* �c1/2��ѕ� 8bit		*/
		gyou	 = (line / 16);						/* �s�ʒu�Z�o			*/
		dotl	 = (line % 16);						/* �[���h�b�g			*/
													/*						*/
		buff[0]  = LCD_WORK2[gyou][dotl][keta  ];	/* ���ݕ\���ް�			*/
		buff[1]  = LCD_WORK2[gyou][dotl][keta+1];	/*						*/
		buff[0] &= (~(((*addr) & 0xFF00) >> 8));	/* ���ް�������			*/
		buff[1] &= (~ ((*addr) & 0x00FF));			/*						*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)�\��	*/
		addr ++;									/*						*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* �\���ް��i�[			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	RULET_CLEAR_SUB(WORD i)
{
	UNs		MARU, col;

	MARU = 0x819C;	//��

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H	V01y
		if (i > 18)	return;							/* �`�潷���			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 10)&&(i <= 26))	return;			/* �`�潷���			*/
	}												/*						*/

	col = GAMENn_SCR_COL;
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = 11;
	}

	if (SEQ_050_SV & BIT_1) {						//���]�@�H	V06b
		if (i==rulet_taiki_pos1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//�������@�H	V06b
		if ((i==rulet_taiki_pos1) || (i==rulet_taiki_pos2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}
#endif
/****************************************************************************/
/*																			*/
/*	���[���b�g�`��N���A�T�u���[�`��										*/
/*																			*/
/*		�k�b�c�Q�́��̈���N���A����B			�i�C�j�V�����A�S�N���A�p�j	*/
/*																			*/
/*		RULET_DISP_FLG	�F	���[���b�g�\���t���O�i����޳�\���� = 0x55�j		*/
/*		RULET_TBL_BASE	�F	���\���f�[�^�̃A�h���X�e�[�u��					*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	RULET_CLEAR_SUB2(WORD i)
{
	WORD	t;
	WORD	keta,	line;
	WORD	gyou,	dotl;
	WORD	buff[2];
	WORD*	addr;
	DWORD	calc;

#ifdef		SUMILATE
	printf("* LCD CLEAR2 �� %d \n",i);
	return;
#endif

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 9)&&(i <= 27))	return;			/* �`�潷���			*/
	}												/*						*/

	calc	= RULET_TBL_BASE[ i ];					/* �\��ð��ِ擪���ڽ	*/
	addr	= (WORD*)calc;							/* �\���ް��擪���ڽ	*/

	line	= ((*addr) / 40);						/* �\���s�ʒu			*/
	keta	= ((*addr) % 40);						/* �\�����ʒu			*/
													/*						*/
	buff[0] = 0;									/*						*/
	buff[1] = 0;									/*						*/

	for(t=0; t<8; t++){								/* �c1/2��ѕ� 8bit		*/
		gyou	 = (line / 16);						/* �s�ʒu�Z�o			*/
		dotl	 = (line % 16);						/* �[���h�b�g			*/
													/*						*/
		Lcd_draw(1,keta,line,2,buff);				/* LCD2 1Line(1dot)�\��	*/
		line ++;									/*						*/
													/*						*/
		LCD_WORK2[gyou][dotl][keta  ] = buff[0];	/* �\���ް��i�[			*/
		LCD_WORK2[gyou][dotl][keta+1] = buff[1];	/*						*/
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	RULET_CLEAR_SUB2(WORD i)
{
	UNs		MARU, col;
	UNs		tmaru1, tamar1, tmaru2, tamar2;

	MARU = 0x819C;	//��

	if((SEQ_050_SV & BIT_1) && (SEQ_PAR_101 & BIT_9)) {		//���]�@�H	V01y
		if (i > 18)	return;							/* �`�潷���			*/
	}

	if (RULET_DISP_FLG == HALF_DISP){				/* ����޳�\����			*/
		if ((i >= 10)&&(i <= 26))	return;			/* �`�潷���			*/
	}												/*						*/

	col = GAMENn_SCR_COL;
	if ( i==0 || i==9 || i==18 || i==27 ) {
		col = COL_GRAY4;
	}

	if (SEQ_050_SV & BIT_1) {						//���]�@�H	V06b
		tmaru1 = SV_TAIKIKAKU_SRV / 100;
		tamar1 = SV_TAIKIKAKU_SRV % 100;
		if (tamar1 >= 50) {
			tmaru1 = tmaru1+1;
			if (tmaru1 >= 36) {
				tmaru1 = 0;
			}
		}
		rulet_taiki_pos1 = tmaru1;
		if (i==tmaru1) {
			col = COL_PINK;
		}
	}
	else if (SEQ_050_SV & BIT_2) {					//�������@�H	V06b
		tmaru1 = SV_TAIKIKAKU_SRV / 100;
		tamar1 = SV_TAIKIKAKU_SRV % 100;
		if (tamar1 >= 50) {
			tmaru1 = tmaru1+1;
			if (tmaru1 >= 36) {
				tmaru1 = 0;
			}
		}

//V06d		tmaru2 = ((1800-SV_TAIKIKAKU_SRV)+1800) / 100;
//////		tamar2 = ((1800-SV_TAIKIKAKU_SRV)+1800) % 100;
//////		if (tamar2 >= 50) {
//////			tmaru2 = tmaru2+1;
//////			if (tmaru2 >= 36) {
//////				tmaru2 = 0;
//////			}
//////		}
		tmaru2 = (18-tmaru1)+18;
		if (tmaru2 >= 36) {
			tmaru2 = 0;
		}

		rulet_taiki_pos1 = tmaru1;
		rulet_taiki_pos2 = tmaru2;
		if ((i==tmaru1)||(i==tmaru2)) {
			col = COL_PINK;
		}
	}

	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		RULET_XYPOS_TBL[i][1],	/*t_p->X_POS,*/
		RULET_XYPOS_TBL[i][0],	/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
}
#endif


/****************************************************************************/
