/************************************************************************************/
/*																					*/
/*		�R�}�c�Q�@�a�����@�r�h�s�|�S�@�g�l�h�v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�J���[�k�b�c�i640*480�j�\��												*/
/*																					*/
/************************************************************************************/
#include "cm_equ1.h"							//�e��̋��ʒ�`
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"


//#define		OLD_RIF									/* ���ޯ��	����ٕ`��	*/
#define		NEW_RIF									/* ���ޯ��	����ٕ`��	*/


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	GAM_INF_TBL(void);				//��ʕ\�����e�[�u��
extern	void	ALL_CHR_TBL(void);				//�\���L�����N�^�e�[�u��
extern	void	ALLTBL_CSTBL(void);				//�J�[�\��������e�[�u��
extern	void	ALLTBL_SVTBL(void);				//�ݒ�l������e�[�u��
extern	void	ALLTBL_PVTBL(void);				//�����l������e�[�u��
extern	void	ALLTBL_SWTBL(void);				//�r�v�|�k�`�l�o������e�[�u��
extern	void	ALLTBL_CHARTBL(void);
extern	void	disp_moji_s_color(UNs len, UNs x, UNs y, UNs c_col, UNs b_col, UNs size, UNs *g_adr_p, UNb Lcd_p[][PanelWidth]);
extern	void	disp_moji_s_paint(UNs len, UNs x, UNs y, UNs col, UNs size, UNb Lcd_p[][PanelWidth]);
//2014/09/02	extern	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth]);
extern	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth], UNs off);

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VMON1[6*16*2][PanelWidth];
extern	UNb		LCD_VMON2[6*16*2][PanelWidth];

/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	Gamen_Init(void);					//�C�j�V����
void	Gamenn_Disp_Init(void);				//��ʂm���D����\�����鎞�̃C�j�V����
void	Windown_Disp_Init(void);			//�E�B���h�E�m���D����\�����鎞�̃C�j�V����	���g�p
void	Gamenn_Disp_Moji(void);				//��ʂm���D���̕�����\��
void	CSR_disp_color(void);
void	Backgnd_Disp(U4b c_tbl_adr);		//�w�i�F�\��
void	Moji_Disp_Char(U4b c_tbl_adr);		//������\��
void	Gamenn_CSRtbl_set(void);
void	Gamenn_SVtbl_set(void);
void	Gamenn_PVtbl_set(void);
void	Gamenn_SWLtbl_set(void);

/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNs *	SW56_Cam_Name_Tbl[69];
extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs *	KAT_sv_memo_tbl[101];
extern	const	UNs		SPACE_ASCII_40[40];			// V05a


/*
********************************************************************************
*
*	�C�j�V����
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamen_Init(void)
{
	U2b		*adr;
	U4b		i;

	i = (U4b)&ALL_CHR_TBL;
	i += ALL_CHR_TBL_OFS;			//V06
	i += language_chg;
	adr = (U2b *)i;
	CHRTBL_CHR_CNT = *adr++;
	CHRTBL_CSR_CNT = *adr++;
	CHRTBL_SWL_CNT = *adr++;
	CHRTBL_S56_CNT = *adr++;
	CHRTBL_MES_CNT = *adr++;
	CHRTBL_S56U_CNT = *adr++;
	CHRTBL_SPE_CNT = *adr++;

//V06r	CHR_TABLE_ADR = (U4b)&ALL_CHR_TBL + language_chg + All_chr_head_size;	// �L�����N�^�e�[�u���̕�����L�����N�^�擪�A�h���X
	CHR_TABLE_ADR = (U4b)&ALL_CHR_TBL + ALL_CHR_TBL_OFS + language_chg + All_chr_head_size;	// �L�����N�^�e�[�u���̕�����L�����N�^�擪�A�h���X

	CSR_TABLE_ADR = CHR_TABLE_ADR + (CHRTBL_CHR_CNT * CHAR_MOJI_SIZE) +2;	// �L�����N�^�e�[�u���̃J�[�\���L�����N�^�擪�A�h���X
	SWL_TABLE_ADR = CSR_TABLE_ADR + (CHRTBL_CSR_CNT * CHAR_CSR_SIZE) +2;	// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^�擪�A�h���X
	S56_TABLE_ADR = SWL_TABLE_ADR + (CHRTBL_SWL_CNT * CHAR_SWL_SIZE) +2;	// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^�擪�A�h���X
	MES_TABLE_ADR = S56_TABLE_ADR + (CHRTBL_S56_CNT * CHAR_S56_SIZE) +2;	// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^�擪�A�h���X
	S56U_TABLE_ADR = MES_TABLE_ADR + (CHRTBL_MES_CNT * CHAR_MES_SIZE) +2;	// �L�����N�^�e�[�u���̂r�v�T�E�U��i�L�����N�^�擪�A�h���X
	SPE_TABLE_ADR = S56U_TABLE_ADR + (CHRTBL_S56U_CNT * CHAR_S56U_SIZE) +2;	// �L�����N�^�e�[�u���̓��ʃL�����N�^�擪�A�h���X
}


/*
********************************************************************************
*
*	��ʂm���D����\�����鎞�̃C�j�V����	���g�p
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_Disp_Init(void)
{
	U4b		i, g_top, adr, gn_top;
	U4b		*g_top2;
	U2b		*hrom, *hram;
	U1b		*vram;

	g_top = (GAMEN_NO-1) * 4 + (U4b)&GAM_INF_TBL;
	g_top += GAM_INF_TBL_OFS;							//V06
	g_top2 = (U4b *)g_top;
	gn_top = *g_top2;
	gn_top += (U4b)&GAM_INF_TBL;
	gn_top += GAM_INF_TBL_OFS;							//V06
	gn_top += 514;

	hrom = (U2b *)gn_top;
	adr	= (U4b)&GAMENn_HEAD;
	hram = (U2b *)adr;

	for (i=0; i<GAMENn_HEAD_SIZE/2; i++,hrom++,hram++)		//��ʂ��̃w�b�_�[�����q�`�l�ɃR�s�[
	{
		*hram = *hrom;
	}

	GAMENN_MOJ_INF_ADR = gn_top + GAMENn_HEAD_SIZE;										//��������̐擪�A�h���X
	GAMENN_CSR_INF_ADR = GAMENn_HEAD.chr_cnt * DISP_INFO_SIZE + GAMENN_MOJ_INF_ADR;		//�J�[�\�����̐擪�A�h���X
	GAMENN_SVP_INF_ADR = GAMENn_HEAD.csr_cnt * DISP_INFO_SIZE + GAMENN_CSR_INF_ADR;		//�ݒ�l���̐擪�A�h���X
	GAMENN_PVP_INF_ADR = GAMENn_HEAD.svp_cnt * DISP_INFO_SIZE + GAMENN_SVP_INF_ADR;		//�����l���̐擪�A�h���X
	GAMENN_SWL_INF_ADR = GAMENn_HEAD.pvp_cnt * DISP_INFO_SIZE + GAMENN_PVP_INF_ADR;		//SW-LAMP���̐擪�A�h���X
	GAMENN_GRP_INF_ADR = GAMENn_HEAD.swl_cnt * DISP_INFO_SIZE + GAMENN_SWL_INF_ADR;		//�O���b�t�B�N���̐擪�A�h���X
}


/*
********************************************************************************
*
*	�E�B���h�E�m���D����\�����鎞�̃C�j�V����	���g�p
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Windown_Disp_Init(void)
{
	U4b		i, g_top, adr, gn_top;
	U4b		*g_top2;
	U2b		*hrom, *hram;
	U1b		*vram;

	g_top = (WINDOW_NO+70-1) * 4 + (U4b)&GAM_INF_TBL;
	g_top += GAM_INF_TBL_OFS;							//V06
	g_top2 = (U4b *)g_top;
	gn_top = *g_top2;
	gn_top += (U4b)&GAM_INF_TBL;
	gn_top += GAM_INF_TBL_OFS;							//V06
	gn_top += 514;

	hrom = (U2b *)gn_top;
	adr	= (U4b)&GAMENn_HEAD;
	hram = (U2b *)adr;

	for (i=0; i<GAMENn_HEAD_SIZE/2; i++,hrom++,hram++)		//��ʂ��̃w�b�_�[�����q�`�l�ɃR�s�[
	{
		*hram = *hrom;
	}

	GAMENN_MOJ_INF_ADR = gn_top + GAMENn_HEAD_SIZE;										//��������̐擪�A�h���X
	GAMENN_CSR_INF_ADR = GAMENn_HEAD.chr_cnt * DISP_INFO_SIZE + GAMENN_MOJ_INF_ADR;		//�J�[�\�����̐擪�A�h���X
	GAMENN_SVP_INF_ADR = GAMENn_HEAD.csr_cnt * DISP_INFO_SIZE + GAMENN_CSR_INF_ADR;		//�ݒ�l���̐擪�A�h���X
	GAMENN_PVP_INF_ADR = GAMENn_HEAD.svp_cnt * DISP_INFO_SIZE + GAMENN_SVP_INF_ADR;		//�����l���̐擪�A�h���X
	GAMENN_SWL_INF_ADR = GAMENn_HEAD.pvp_cnt * DISP_INFO_SIZE + GAMENN_PVP_INF_ADR;		//SW-LAMP���̐擪�A�h���X
	GAMENN_GRP_INF_ADR = GAMENn_HEAD.swl_cnt * DISP_INFO_SIZE + GAMENN_SWL_INF_ADR;		//�O���b�t�B�N���̐擪�A�h���X
}


/*
********************************************************************************
*
*	��ʂm���D���̃X�N���[���F��\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_Screen( UNb Lcd_p[][PanelWidth] )
{
	UNl		cnt, col, wk;
	UNl		*vram;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	vram = (UNl *)&Lcd_p[0][0];
	cnt = (PanelWidth * PanelHeight) / 4;
	
	while (cnt--)
	{
		*vram++ = col;
	}
}


/*
********************************************************************************
*
*	�E�B���h�E�m���D���̃X�N���[���F��\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Window_Screen( UNb Lcd_p[][PanelWidth] )
{
	UNl		cnt, col, wk;
	UNl		*vram;
	UNs		xdot, ydot;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	if( (42 <= WINDOW_NO) && (WINDOW_NO <= 47) )		//V06c
	{	//��ƊJ�n/�I��WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-Window2Height][0];
		cnt = (PanelWidth * Window2Height) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}

	else if( (51 <= WINDOW_NO) && (WINDOW_NO <= 58) )		//V06c
	{	//��ƊJ�n/�I��WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-Window2Height][0];
		cnt = (PanelWidth * Window2Height) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}

	else if( (6 <= WINDOW_NO) && (WINDOW_NO <= 9) )
	{	//�i��WINDOW
		for(ydot=PanelHeight-WindowHeight; ydot<PanelHeight; ydot++)
		{
			for(xdot=0; xdot<PanelDANWidth; xdot++)
			{
				Lcd_p[ydot][xdot] = (UNb)col;
			}
		}
	}
	else
	{	//�ʏ�WINDOW
		vram = (UNl *)&Lcd_p[PanelHeight-WindowHeight][0];
		cnt = (PanelWidth * WindowHeight) / 4;
	
		while (cnt--)
		{
			*vram++ = col;
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_all_s
*  Function Name:	�S��ʕ\���p�������ށ��ޯĕϊ�
*  Input	:		��ʔԍ�
*					0:�ʏ��ʁ^1:����޳���(BIT_15=1:������޳���)
*					LCDܰ��̑I��(0:LCD_WORK1/1:LCD_WORK2)
*
*  Return	: 		�Ȃ�
*  Note		:
*
********************************************************************************
*/
void	disp_all_s_color( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr, adr1;
	U2b		*hrom, *hram;
	U2b		ccnt, len;
	U2b		dat, bit;
	U4b		*c_adr;
	U2b		*c_adr1;

	if (GAMENn_HEAD.chr_cnt == 0)	return;						// �����񂠂�H

	ccnt = GAMENn_HEAD.chr_cnt;									// �������
	g_top = GAMENN_MOJ_INF_ADR;									// ������\�����擪���ڽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		if ( DISP_INFO.chr_no != 0 )
		{
			if (DISP_INFO.link_no == 0)
			{
				adr = CHR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (U2b *)adr;

				len = *hrom++;
				len >>= 8;

				if(len > MOJI_DATA_SIZE)					// V04a
				{
					len = MOJI_DATA_SIZE;
				}

				disp_moji_s_color(
					len, 
					DISP_INFO.bgn_xdot, 
					DISP_INFO.bgn_ydot, 
					DISP_INFO.chr_col,
					DISP_INFO.bgnd1_col, 
					DISP_INFO.chr_size, 
					hrom, 
					Lcd_p
					);
			}
			else
			{
				adr = adr1 = (DISP_INFO.link_no-1) * CTL_CHR_TBL_SIZE + (U4b)&ALLTBL_CHARTBL;
				adr1 += 4;

				c_adr	= (U4b *)adr;
				adr		= *c_adr;
				c_adr1	= (U2b *)adr;
				dat		= *c_adr1;
	
				c_adr1	= (U2b *)adr1;
				bit		= *c_adr1;

				// V06 ���_���Ή� =================================
				adr1 += 2;
				c_adr1	= (U2b *)adr1;
				if (*c_adr1 == 1)
				{
					dat = ~dat;
				}
				//=================================================

				if (dat & bit)
				{
					adr =  CHR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
					hrom = (U2b *)adr;
	
					len = *hrom++;
					len >>= 8;

					if(len > MOJI_DATA_SIZE)					// V04a
					{
						len = MOJI_DATA_SIZE;
					}

					disp_moji_s_color(
						len, 
						DISP_INFO.bgn_xdot, 
						DISP_INFO.bgn_ydot, 
						DISP_INFO.chr_col,
						DISP_INFO.bgnd1_col, 
						DISP_INFO.chr_size, 
						hrom, 
						Lcd_p
						);
				}
			}
		}
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	��ʂm���D���̃J�[�\���L�����N�^�S�\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_Disp_Csr( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, len, t_no;

	if (GAMENn_HEAD.csr_cnt == 0)	return;						// �����񂠂�H

	ccnt = GAMENn_HEAD.csr_cnt;									// �������
	g_top = GAMENN_CSR_INF_ADR;									// ������\�����擪���ڽ

	t_no = 0;
	while (ccnt--)
	{
		if ((CSR_buff[t_no].TOK_NO & BIT_0) == 0)				//��\���̐ݒ�H  bit0=1 then ��\��
		{
			hrom = (U2b *)g_top;
			adr	= (U4b)&DISP_INFO;
			hram = (U2b *)adr;

			for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
			{
				*hram = *hrom;
			}

			adr =  CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
			hrom = (U2b *)adr;

			len = *hrom++;
			len >>= 8;

			if(len > CSR_DATA_SIZE)					// V04a
			{
				len = CSR_DATA_SIZE;
			}

			disp_moji_s_color(
				len, 
				DISP_INFO.bgn_xdot, 
				DISP_INFO.bgn_ydot, 
				DISP_INFO.chr_col,
				DISP_INFO.bgnd1_col, 
				DISP_INFO.chr_size, 
				hrom, 
				Lcd_p
				);
		}
		t_no++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	�w��J�[�\��No.�̕�����\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
*	�� ��	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	Disp_Csr_Moji(UNs t_no)
{
	U4b		adr;
	U2b		*hrom;
	U2b		len;

	if ((CSR_buff[t_no].TOK_NO & BIT_0) == 0)				//��\���̐ݒ�H  bit0=1 then ��\��
	{
		adr =  CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (U2b *)adr;

		len = *hrom++;
		len >>= 8;

		if(len > CSR_DATA_SIZE)					// V04a
		{
			len = CSR_DATA_SIZE;
		}

		disp_moji_s_color(
			len, 
			CSR_buff[t_no].X_POS, 
			CSR_buff[t_no].Y_POS, 
			CSR_buff[t_no].C_COL,
			CSR_buff[t_no].B_COL1, 
			CSR_buff[t_no].SIZE, 
			hrom, 
			LCD_VRAM
			);
	}
	else {
		disp_moji_s_paint(
			CSR_buff[t_no].M_LEN,		//���p����
			CSR_buff[t_no].X_POS,		//X�n�_
			CSR_buff[t_no].Y_POS,		//Y�n�_
			GAMENn_HEAD.scr_col,		//�h�ׂ��F
			CSR_buff[t_no].SIZE,		//X2�{/Y2�{
			LCD_VRAM
			);
	}
}


/*
********************************************************************************
*
*	��ʂm���D���̃O���t�B�b�N�S�\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_Graphic( UNb Lcd_p[][PanelWidth] )
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;
	U2b		xdot, ydot;

	if (GAMENn_HEAD.grp_cnt == 0)	return;						// �O���t�B�b�N����H

	ccnt = GAMENn_HEAD.grp_cnt;									// �O���t�B�b�N��
	g_top = GAMENN_GRP_INF_ADR;									// �O���t�B�b�N�\�����擪���ڽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		switch(DISP_INFO.parts_no)
		{
			case 0:		//����
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				if( DISP_INFO.chr_no == 0 )		// �w�����O�H
				{		//�c��
					k = DISP_INFO.chr_size;							// �x����
					while(k--) {
						Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
						ydot++;
					}
				}
				else if( DISP_INFO.chr_size == 0 )		// �x�����O�H
				{		//����
					k = DISP_INFO.chr_no;							// �w����
					while(k--) {
						Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
						xdot++;
					}
				}
				else
				{		//�΂ߐ�
				}
				break;

			case 1:		//�a�n�w
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				//�c��
				k = DISP_INFO.chr_size;							// �x����
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					ydot++;
				}
				//����
				k = DISP_INFO.chr_no;							// �w����
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					xdot++;
				}
				//�c��
				k = DISP_INFO.chr_size;							// �x����
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					ydot--;
				}
				//����
				k = DISP_INFO.chr_no;							// �w����
				while(k--) {
					Lcd_p[ydot][xdot] = DISP_INFO.chr_col;
					xdot--;
				}
				break;

			default :
				break;
		}

		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	��ʂm���D���̃O���t�B�b�N�S�\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_Graphic_All(void)
{
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;
	U2b		xdot, ydot;

	if (GAMENn_HEAD.grp_cnt == 0)	return;						// �O���t�B�b�N����H

	ccnt = GAMENn_HEAD.grp_cnt;									// �O���t�B�b�N��
	g_top = GAMENN_GRP_INF_ADR;									// �O���t�B�b�N�\�����擪���ڽ

	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		switch(DISP_INFO.parts_no)
		{
			case 0:		//����
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				if( DISP_INFO.chr_no == 0 )		// �w�����O�H
				{		//�c��
					k = DISP_INFO.chr_size;							// �x����
					while(k--) {
						LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
						LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
						ydot++;
					}
				}
				else if( DISP_INFO.chr_size == 0 )		// �x�����O�H
				{		//����
					k = DISP_INFO.chr_no;							// �w����
					while(k--) {
						LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
						LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
						xdot++;
					}
				}
				else
				{		//�΂ߐ�
				}
				break;

			case 1:		//�a�n�w
				xdot = DISP_INFO.bgn_xdot;
				ydot = DISP_INFO.bgn_ydot;
				//�c��
				k = DISP_INFO.chr_size;							// �x����
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					ydot++;
				}
				//����
				k = DISP_INFO.chr_no;							// �w����
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					xdot++;
				}
				//�c��
				k = DISP_INFO.chr_size;							// �x����
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					ydot--;
				}
				//����
				k = DISP_INFO.chr_no;							// �w����
				while(k--) {
					LCD_VBASE[ydot][xdot] = DISP_INFO.chr_col;
					LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
					xdot--;
				}
				break;

			default :
				break;
		}

		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	�w�i�F�\��
*
*	Input	: �n�_X�A�n�_Y�A������(�޲Ē�)�A�w�i�F�A��������(���X,����Y)
*	Return	: �Ȃ�
*
********************************************************************************
*/
void	Backgnd_Disp(U4b c_tbl_adr)
{
#ifdef	OLD_RIF
	U2b		x_dot_leng, y_dot_leng;
	U2b		xcnt, ycnt;
	U2b		xdot, ydot;
	U4b		adr;
	U2b		cnt, *Dst_p;

	adr = c_tbl_adr + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	Dst_p = (U2b *)adr;

	cnt = *Dst_p++;
	cnt = (cnt>>8) & 0x0ff;								// ������

	x_dot_leng = ((DISP_INFO.chr_size>>8) & 0x0ff) * cnt * 8;			// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = (DISP_INFO.chr_size & 0x0ff) * 16;						// ���� �~ 16dot�^1����

	xdot = DISP_INFO.bgn_xdot;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X�����{�P�ޯ�
	{
		ydot = DISP_INFO.bgn_ydot;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			LCD_VRAM[ydot][xdot] = DISP_INFO.bgnd1_col;
		}
	}
#endif
}


/*
********************************************************************************
*
*	������L�����^�N�\���i�������ް������JIS�j
*
*	Input	: �n�_X�A�n�_Y�A��׸�No.�A�����F�A��������(���X,����Y)
*	Return	: �Ȃ�
*
********************************************************************************
*/
void	Moji_Disp_Char(U4b c_tbl_adr)
{
#ifdef	OLD_RIF
	U4b		adr, flg;
	U2b		cnt, cnv_wk, *Dst_p, xcnt, ycnt;
	U2b		xdot, ydot, xsize, ysize, xdot_bak;
	U4b		i, j, k, l;
	U1b		moji[M_char], dot_wk[32], wk1b;

	flg = 0;
	xdot = DISP_INFO.bgn_xdot;
	ydot = DISP_INFO.bgn_ydot;
	xsize = (DISP_INFO.chr_size>>8) & 0x0ff;					// X�̻���
	ysize = DISP_INFO.chr_size & 0x0ff;							// Y�̻���

	adr = c_tbl_adr + ((DISP_INFO.chr_no-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	Dst_p = (U2b *)adr;

	cnt = *Dst_p++;
	cnt = (cnt>>8) & 0x0ff;								// ������

	for( i=0 ; i < cnt ; i += 2 ) {						// ܰ�ށ��޲ĒP�ʱ����\�̈�ɺ�߰
		cnv_wk = *Dst_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//�������ނ̐ݒ�
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//�������ށ��ޯĕϊ�
															//���p
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = DISP_INFO.bgn_ydot;
		}
		else {												//�S�p
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					//�S�p����
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					//�S�p�E��
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k+1] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = DISP_INFO.chr_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k += 2;
			}
			i++;
			xdot_bak += xsize * 2 * 8;
			xdot = xdot_bak;
			ydot = DISP_INFO.bgn_ydot;
		}
	}
#endif
}


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	�����\���p�������ށ��ޯĕϊ�
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�������ޥ�i�[���ڽ
*					LCD�i�[�ޯ̧���ڽ
*					�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		�Ȃ�
*  Note		:
*
********************************************************************************
*/
void	disp_moji_s_color(
			UNs len,
			UNs x,
			UNs y,
			UNs c_col, 
			UNs b_col, 
			UNs size, 
			UNs *g_adr_p, 
			UNb Lcd_p[][PanelWidth]
			)
{
	UNi		i, j, k, l, flg;
	UNs		cnt, cnv_wk;
	UNs		xdot, ydot, xdot_bak, ydot_bak;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNb		moji[E_line], dot_wk[32], wk1b;
	UNl		*Src_p, *Dst_p, wkl;

	flg = 0;

	cnt = len;											//�������@�Z�o
	xsize = (size>>8) & 0x0ff;					// X�̻���
	ysize = size & 0x0ff;						// Y�̻���

	/******** �w�i�F�h��ׂ� *********/
#ifdef	OLD_RIF
	x_dot_leng = xsize * cnt * 8;				// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = ysize * 16;					// ���� �~ 16dot�^1����
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
#endif
#ifdef	NEW_RIF
	x_dot_leng = (xsize * cnt * 8);				// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = (ysize * 16);					// ���� �~ 16dot�^1����
	xdot = x;
	wkl = b_col;
	wkl |= wkl<<8;
	wkl |= wkl<<16;
	
	xcnt = ((~xdot+1) & 0x03);
	x_dot_leng -= xcnt;
	for ( ; xcnt>0; xcnt--,xdot++)				// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
	for ( xcnt=x_dot_leng; xcnt>3; xcnt-=4,xdot+=4 )			// X�����{�P�ޯ�
	{
		ydot = y;
		Dst_p = (UNl *)&Lcd_p[ydot][xdot];
		for (ycnt=y_dot_leng;  ycnt>0; ycnt-- )		// Y�����h��ׂ�
		{
			*Dst_p = wkl ;
			Dst_p += (PanelWidth/4);
		}
	}
	for ( ; xcnt>0; xcnt--,xdot++)				// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			Lcd_p[ydot][xdot] = b_col;
		}
	}
#endif

	/******** �����\�� *********/
	xdot = x;
	ydot = y;

	for( i=0 ; i < cnt ; i += 2 ) {						//ܰ�ށ��޲ĒP�ʱ����\�̈�ɺ�߰
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//�������ނ̐ݒ�
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//�������ށ��ޯĕϊ�
															//���p
			for ( l=0, k=0; l<16; l++ ) {
				switch (xsize)
				{
					case 1:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=1;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					case 2:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=2;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					case 4:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
									Lcd_p[ydot][xdot++] = c_col;
								}
								else {
									xdot+=4;
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;

					default:
						for ( ycnt=0; ycnt<ysize; ycnt++) {
							for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
								if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
									for ( xcnt=0; xcnt<xsize; xcnt++ ) {
										Lcd_p[ydot][xdot] = c_col;
										xdot++;
									}
								}
								else {
									for ( xcnt=0; xcnt<xsize; xcnt++ ) {
										xdot++;
									}
								}
							}
							xdot = xdot_bak;
							ydot++;
						}
						break;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
		else {												//�S�p
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					//�S�p����
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								Lcd_p[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					//�S�p�E��
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k+1] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								Lcd_p[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k += 2;
			}
			i++;
			xdot_bak += xsize * 2 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	�����\���p�������ށ��ޯĕϊ�
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�������ޥ�i�[���ڽ
*					LCD�i�[�ޯ̧���ڽ
*					�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		�Ȃ�
*  Note		:
*
********************************************************************************
*/
#ifdef	OLD_RIF
void	disp_moji_s_rif(
			UNs len,
			UNs x,
			UNs y,
			UNs size
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;

	xsize = (size>>8) & 0x0ff;					// X�̻���
	ysize = size & 0x0ff;						// Y�̻���

	/******** �w�i�F�h��ׂ� *********/
	x_dot_leng = xsize * len * 8;				// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = ysize * 16;					// ���� �~ 16dot�^1����
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			LCD_VRAM[ydot][xdot] = LCD_VBASE[ydot][xdot];
		}
	}
}
#endif

#ifdef	NEW_RIF
void	disp_moji_s_rif(
			UNs len,
			UNs x,
			UNs y,
			UNs size
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNl		*Src_p, *Dst_p;

	xsize = (size>>8) & 0x0ff;					// X�̻���
	ysize = size & 0x0ff;						// Y�̻���

	x_dot_leng = (xsize * len * 8);				// ���� �~ �޲Ē� �~ 8�ޯ�
	y_dot_leng = (ysize * 16);						// ���� �~ 16dot�^1����
	xdot = x;

	xcnt = ((~xdot+1) & 0x03);
	x_dot_leng -= xcnt;
	for ( ; xcnt>0; xcnt--,xdot++)				// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			LCD_VRAM[ydot][xdot] = LCD_VRAM[ydot][xdot];
		}
	}
	for ( xcnt=x_dot_leng; xcnt>3; xcnt-=4,xdot+=4 )			// X�����{�P�ޯ�
	{
		ydot = y;
		Src_p = (UNl *)&LCD_VBASE[ydot][xdot];
		Dst_p = (UNl *)&LCD_VRAM[ydot][xdot];
		for (ycnt=y_dot_leng;  ycnt>0; ycnt-- )		// Y�����h��ׂ�
		{
			*Dst_p = *Src_p ;
			Src_p += (PanelWidth/4);
			Dst_p += (PanelWidth/4);
		}
	}
	for ( ; xcnt>0; xcnt--,xdot++)				// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			LCD_VRAM[ydot][xdot] = LCD_VRAM[ydot][xdot];
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		disp_moji_s
*  Function Name:	�����\���p�������ށ��ޯĕϊ�
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�������ޥ�i�[���ڽ
*					LCD�i�[�ޯ̧���ڽ
*					�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		�Ȃ�
*  Note		:
*
********************************************************************************
*/
void	disp_moji_s_paint(
			UNs len,
			UNs x,
			UNs y,
			UNs col,
			UNs size,
			UNb Lcd_p[][PanelWidth]
			)
{
	UNs		xdot, ydot;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;

	xsize = (size>>8) & 0x0ff;					// X�̻���
	ysize = size & 0x0ff;						// Y�̻���

	/******** �w��F�h��ׂ� *********/
	x_dot_leng = xsize * len * 8;				// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = ysize * 16;					// ���� �~ 16dot�^1����
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			Lcd_p[ydot][xdot] = col;
		}
	}
}


/*
********************************************************************************
*
*	�J�[�\���̐�����e�[�u���Z�b�g
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_CSRtbl_set(void)
{
	CSR_TBL_TDEF	*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k, wk;

	CSR_CNT = CSR_CNT1 = GAMENn_HEAD.csr_cnt;

	if (GAMENn_HEAD.csr_cnt == 0)	return;						// �J�[�\������H

	ccnt = GAMENn_HEAD.csr_cnt;									// �J�[�\����
	g_top = GAMENN_CSR_INF_ADR;									// �J�[�\���\�����擪���ڽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		d_p = &CSR_buff[k];													//�i�[�|�C���^�Z�b�g
		adr = (DISP_INFO.link_no-1) * CTL_CSR_TBL_SIZE + (U4b)&ALLTBL_CSTBL;
		v_p = (CSR_TBL_TDEF *)adr;

//		d_p->XY_POS		= v_p->XY_POS;				//���ق�X,Y��
		d_p->DATA_NO	= v_p->DATA_NO;				//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
		d_p->SV_MAX		= v_p->SV_MAX;				//�ݒ�lð��ٌ�
		d_p->SW_MAX		= v_p->SW_MAX;				//SWð��ٌ�
		d_p->CARA_NO	= DISP_INFO.chr_no;			//���ٕ\����׎�ʁi���g�p�j
		d_p->MOVE_NO	= v_p->MOVE_NO;				//��ʈړ��ԍ�
		d_p->TOK_NO		= v_p->TOK_NO;				//����ԍ�(B0:���ٖ���)
		d_p->YOBI1		= v_p->YOBI1;				//�\���P
		d_p->YOBI2		= v_p->YOBI2;				//�\���Q
		d_p->SW56_UP	= v_p->SW56_UP;				//SW56��i��׸�
		d_p->SW5_DN		= v_p->SW5_DN;				//SW5���i��׸�
		d_p->SW6_DN		= v_p->SW6_DN;				//SW6���i��׸�
		d_p->SW5_SUB	= v_p->SW5_SUB;				//SW5�ް������ԍ�
		d_p->SW6_SUB	= v_p->SW6_SUB;				//SW6�ް������ԍ�
		d_p->YOBI3		= v_p->YOBI3;				//�\���R
		d_p->AKI		= v_p->AKI;					//��
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//�\��X�ޯĈʒu
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//�\��Y�ޯĈʒu
		d_p->SIZE		= DISP_INFO.chr_size;		//�����T�C�Y
		d_p->C_COL		= DISP_INFO.chr_col;		//�����F
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//�w�i�F
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//�w�i�F

		adr = CSR_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (U2b *)adr;
		wk = *hrom;
		wk = (wk>>8) & 0x0ff;					// ������
		d_p->M_LEN		= wk;					//�\��������(���p��)
		d_p->XY_POS		= wk<<10;				//�\��������(���p��)
		d_p->XY_POS		|= (d_p->X_POS/8)<<4;	//�\����(���p��)
		d_p->XY_POS		|= d_p->Y_POS/16;		//�\���s(���p��)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	�ݒ�l�̐�����e�[�u���Z�b�g
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_SVtbl_set(void)
{
	SV_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;

	SV_CNT = GAMENn_HEAD.svp_cnt;

	if (GAMENn_HEAD.svp_cnt == 0)	return;						// �J�[�\������H

	ccnt = GAMENn_HEAD.svp_cnt;									// �J�[�\����
	g_top = GAMENN_SVP_INF_ADR;									// �J�[�\���\�����擪���ڽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		d_p = &SV_buff[k];													//�i�[�|�C���^�Z�b�g
		adr = (DISP_INFO.link_no-1) * CTL_SVP_TBL_SIZE + (U4b)&ALLTBL_SVTBL;
		v_p = (SV_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//�ݒ�l�\����X,Y��
		d_p->AKI		= v_p->AKI;					//��
		d_p->DATA_ADR	= v_p->DATA_ADR;			//�ް��i�[���ڽ
		d_p->SUB_NO		= v_p->SUB_NO;				//���ٰ�ݔԍ�
		d_p->GRP_NO		= v_p->GRP_NO;				//��ٰ�ߔԍ�
		d_p->TOK_FLG	= v_p->TOK_FLG;				//�����׸�
		d_p->BYTE_NO	= v_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d_p->TEN_POS	= v_p->TEN_POS;				//�����_�̈ʒu
		d_p->CSR_NO		= v_p->CSR_NO;				//���ٔF���ԍ�
		d_p->DSP_NO		= v_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
		d_p->SAVE_NO	= v_p->SAVE_NO;				//�i�[�׸�
		d_p->YOBI_NO	= v_p->YOBI_NO;				//�\��
		d_p->AKI2		= v_p->AKI2;				//��
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//�\��X�ޯĈʒu
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//�\��Y�ޯĈʒu
		d_p->M_LEN		= DISP_INFO.chr_no;			//�\��������(���p��)
		d_p->SIZE		= DISP_INFO.chr_size;		//�����T�C�Y
		d_p->C_COL		= DISP_INFO.chr_col;		//�����F
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//�w�i�F
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//�w�i�F

		d_p->TOK_FLG	= ( d_p->TOK_FLG & ~BIT_2 ) | (( DISP_INFO.option << 2 ) & BIT_2 );		//��߼�݁i���p�^�S�p�j

		d_p->XY_POS		= DISP_INFO.chr_no<<10;		//�\��������(���p��)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	�����l�̐�����e�[�u���Z�b�g
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_PVtbl_set(void)
{
	PV_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k;

	PV_CNT = GAMENn_HEAD.pvp_cnt;

	if (GAMENn_HEAD.pvp_cnt == 0)	return;						// �J�[�\������H

	ccnt = GAMENn_HEAD.pvp_cnt;									// �J�[�\����
	g_top = GAMENN_PVP_INF_ADR;									// �J�[�\���\�����擪���ڽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		d_p = &PV_buff[k];													//�i�[�|�C���^�Z�b�g
		adr = (DISP_INFO.link_no-1) * CTL_PVP_TBL_SIZE + (U4b)&ALLTBL_PVTBL;
		v_p = (PV_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//���ق�X,Y��
		d_p->AKI		= v_p->AKI;					//��
		d_p->DATA_ADR	= v_p->DATA_ADR;			//�ް��i�[���ڽ
		d_p->SUB_NO		= v_p->SUB_NO;				//���ٰ�ݔԍ�
		d_p->GRP_NO		= v_p->GRP_NO;				//��ٰ�ߔԍ�
		d_p->TOK_FLG	= v_p->TOK_FLG;				//�����׸�
		d_p->BYTE_NO	= v_p->BYTE_NO;				//�ް��i�[����޲Ē�
		d_p->TEN_POS	= v_p->TEN_POS;				//�����_�̈ʒu
		d_p->YOBI1		= v_p->YOBI1;				//�\���P
		d_p->YOBI2		= v_p->YOBI2;				//�\���Q
		d_p->AKI2		= v_p->AKI2;				//��
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//�\��X�ޯĈʒu
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//�\��Y�ޯĈʒu
		d_p->M_LEN		= DISP_INFO.chr_no;			//�\��������(���p��)
		d_p->SIZE		= DISP_INFO.chr_size;		//�����T�C�Y
		d_p->C_COL		= DISP_INFO.chr_col;		//�����F
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//�w�i�F
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//�w�i�F

		d_p->TOK_FLG	= ( d_p->TOK_FLG & ~BIT_2 ) | (( DISP_INFO.option << 2 ) & BIT_2 );		//��߼�݁i���p�^�S�p�j

		d_p->XY_POS		= DISP_INFO.chr_no<<10;		//�\��������(���p��)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*
*	�r�v�|�k�`�l�o�̐�����e�[�u���Z�b�g
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
********************************************************************************
*/
void	Gamenn_SWLtbl_set(void)
{
	SW_TBL_TDEF		*v_p, *d_p;
	U4b		i, g_top, adr;
	U2b		*hrom, *hram;
	U2b		ccnt, k, wk;

	SW_CNT = SW_CNT1 = GAMENn_HEAD.swl_cnt;

	if (GAMENn_HEAD.swl_cnt == 0)	return;						// �J�[�\������H

	ccnt = GAMENn_HEAD.swl_cnt;									// �J�[�\����
	g_top = GAMENN_SWL_INF_ADR;									// �J�[�\���\�����擪���ڽ

	k = 0;
	while (ccnt--)
	{
		hrom = (U2b *)g_top;
		adr	= (U4b)&DISP_INFO;
		hram = (U2b *)adr;

		for (i=0; i<DISP_INFO_SIZE/2; i++,hrom++,hram++)		//������������q�`�l�ɃR�s�[
		{
			*hram = *hrom;
		}

		d_p = &SW_buff[k];													//�i�[�|�C���^�Z�b�g
		adr = (DISP_INFO.link_no-1) * CTL_SWL_TBL_SIZE + (U4b)&ALLTBL_SWTBL;
		v_p = (SW_TBL_TDEF *)adr;

		d_p->XY_POS		= v_p->XY_POS;				//�����l�\����X,Y��
		d_p->AKI		= v_p->AKI;					//��
		d_p->DATA_ADR	= v_p->DATA_ADR;			//�ް��i�[���ڽ
		d_p->SUB_NO		= v_p->SUB_NO;				//���ٰ�ݔԍ�
		d_p->GRP_NO		= v_p->GRP_NO;				//��ٰ�ߔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
		d_p->TOK_FLG	= v_p->TOK_FLG;				//�����׸�
		d_p->CHG_NO		= v_p->CHG_NO;				//�ް��i�[��̕ύX�ޯĈʒu
		d_p->CSR_NO		= v_p->CSR_NO;				//���̐ݒ�l�̑����鶰�ٔF���ԍ�
		d_p->DSP_NO		= v_p->DSP_NO;				//���ٔF���ԍ����̈ړ�����
		d_p->CARA_NO	= DISP_INFO.chr_no;			//�\���p��׸��ԍ�
		d_p->KAN_NO		= v_p->KAN_NO;				//�֘A�޲�
		d_p->KAN_ADR	= v_p->KAN_ADR;				//�֘A���ڽ
		d_p->SAVE_NO	= v_p->SAVE_NO;				//�i�[�׸�
		d_p->YOBI2		= v_p->YOBI2;				//�\���Q
		d_p->X_POS		= DISP_INFO.bgn_xdot;		//�\��X�ޯĈʒu
		d_p->Y_POS		= DISP_INFO.bgn_ydot;		//�\��Y�ޯĈʒu
		d_p->SIZE		= DISP_INFO.chr_size;		//�����T�C�Y
		d_p->C_COL		= DISP_INFO.chr_col;		//�����F
		d_p->B_COL1		= DISP_INFO.bgnd1_col;		//�w�i�F
		d_p->B_COL2		= DISP_INFO.bgnd2_col;		//�w�i�F

		adr = SWL_TABLE_ADR + ((DISP_INFO.chr_no-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (U2b *)adr;
		wk = *hrom;
		wk = (wk>>8) & 0x0ff;					// ������
		d_p->M_LEN		= wk;					//�\��������(���p��)
		d_p->XY_POS		= wk<<10;				//�\��������(���p��)

		k++;
		g_top += DISP_INFO_SIZE;
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set
*  Function Name:	�r�v�L�����N�^�\������
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*					�\���p��׸��ԍ�
*					�i�[�ޯ̧���ڽ
*  Return	: 		�Ȃ�
*  Note		:
********************************************************************************
*/
//2014/09/02	void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth])
void	SWchg_set_color(UNi T_no, UNs c_no, UNb Lcd_p[][PanelWidth], UNs off)
{
	UNs		j, *buff_p, *g_p, len, b_col;
	U4b		adr;

	adr =  SWL_TABLE_ADR + ((c_no-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	g_p = (U2b *)adr;
	
	len = *g_p++;
	len >>= 8;

	buff_p = SW_buff[T_no].DATA_ADR;				//�ް��i�[���ڽ
	j = SW_buff[T_no].CHG_NO;						//�ް��i�[��̕ύX�ޯĈʒu

	if(off) {										//����OFF�\��		2014/09/02
		j=0;
	}

	if(*buff_p & j) {								//�n�m��ԁH
		g_p += (8/2);
		b_col = SW_buff[T_no].B_COL2;
	}
	else {
		b_col = SW_buff[T_no].B_COL1;
	}
	disp_moji_s_color(
		len, 
		SW_buff[T_no].X_POS, 
		SW_buff[T_no].Y_POS, 
		SW_buff[T_no].C_COL,
		b_col,
		SW_buff[T_no].SIZE, 
		g_p, 
		Lcd_p
		);
	if ( SVPV_LCD_FLG == 0) {
		disp_moji_s_rif (
			SW_buff[T_no].M_LEN, 
			SW_buff[T_no].X_POS, 
			SW_buff[T_no].Y_POS, 
			SW_buff[T_no].SIZE
			);
	}
}


/*
********************************************************************************
*
*	�w��X�C�b�`No.�̕�����\��
*
*	Input	:		�Ȃ�
*	Return	: 		�Ȃ�
*
*	�� ��	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	Disp_SW(UNi t_no)
{
	UNs		j, *buff_p, *g_p, len, b_col;
	U4b		adr;

	adr =  SWL_TABLE_ADR + ((SW_buff[t_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	g_p = (U2b *)adr;
	
	len = *g_p++;
	len >>= 8;

	if ( ( SW_buff[t_no].SUB_NO & BIT_F) == 0 ) {
		buff_p = SW_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
		j = SW_buff[t_no].CHG_NO;						//�ް��i�[��̕ύX�ޯĈʒu

		if(*buff_p & j) {								//�n�m��ԁH
			g_p += (8/2);
			b_col = SW_buff[t_no].B_COL2;
		}
		else {
			b_col = SW_buff[t_no].B_COL1;
		}
		disp_moji_s_color(
			len, 
			SW_buff[t_no].X_POS, 
			SW_buff[t_no].Y_POS, 
			SW_buff[t_no].C_COL,
			b_col,
			SW_buff[t_no].SIZE, 
			g_p, 
			LCD_VRAM
			);
	}
	else {
		disp_moji_s_paint(
			SW_buff[t_no].M_LEN,		//���p����
			SW_buff[t_no].X_POS,		//X�n�_
			SW_buff[t_no].Y_POS,		//Y�n�_
			GAMENn_HEAD.scr_col,		//�h�ׂ��F
			SW_buff[t_no].SIZE,			//X2�{/Y2�{
			LCD_VRAM
			);
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set_dan
*  Function Name:	�r�v�L�����N�^�\������(�i���p)
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*					�i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		: V05a MAKE
********************************************************************************
*/
void	SWchg_set_dan_color(UNi T_no, UNb Lcd_p[][PanelWidth])
{
	UNs		j, k, *buff_p;
	UNs		len, col;
	UNl		adr;
	UNs		*hrom;

	adr =  SWL_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	hrom = (UNs *)adr;
	len = *hrom++;
	len >>= 8;
	col = SW_buff[T_no].B_COL1;						/* �w�i�F			*/

	buff_p = SW_buff[T_no].DATA_ADR;				//�ް��i�[���ڽ
	j = SW_buff[T_no].CHG_NO;						//�ް��i�[��̕ύX�ޯĈʒu
	k = *buff_p;									//�K�v�ȃr�b�g�����𒊏o
	k &= j;

	if(k==0 || k==j ) {								//�O���X�y�[�X || �R���X�y�[�X
		hrom = &SPACE_ASCII_40[0];
		col = GAMENn_HEAD.scr_col;
	}
	else{
		j &= 0x00aa;
		if( k & j) {
			hrom += SWL_DATA_SIZE/2;				//�n�m�̎��͑S�p�S���ɗL��̂�
			col = SW_buff[T_no].B_COL2;				/* �w�i�F			*/
		}
	}

	disp_moji_s_color(
		len,									/* ��׸��			*/
		SW_buff[T_no].X_POS,					/* ���o��X�ʒu		*/
		SW_buff[T_no].Y_POS,					/* ���o��Y�ʒu		*/
		SW_buff[T_no].C_COL,					/* �����F			*/
		col,									/* �w�i�F			*/
		SW_buff[T_no].SIZE,						/* ��������			*/
		hrom,									/* �����i�[���ڽ	*/
		LCD_VBASE								/* �\�����			*/
		);
	disp_moji_s_rif (
		len,									/* ��׸��			*/
		SW_buff[T_no].X_POS,					/* ���o��X�ʒu		*/
		SW_buff[T_no].Y_POS,					/* ���o��Y�ʒu		*/
		SW_buff[T_no].SIZE						/* ��������			*/
		);
}


/*
********************************************************************************
*  Module Name:		CSR_disp
*  Function Name:	�J�[�\���\��
*  Input	:		
*  Return	: 		�Ȃ�
*  Note		:
********************************************************************************
*/
void	CSR_disp_color(void)
{
	UNs		t_no, c_no;
	UNl		adr;
	UNs		*g_p;

	t_no = CSR_TBL_POS_NOW;

	if( (CSR_BAK_X_POS == CSR_buff[t_no].X_POS) &&
			 (CSR_BAK_Y_POS == CSR_buff[t_no].Y_POS) ) {	//�J�[�\���|�W�V�����f�[�^�X�V ?
		return;												//�J�[�\���ʒu���ꏏ�̏ꍇ�͏I��
	}

	if( CSR_BAK_X_POS != 0xffff &&							//�O��J�[�\���|�W�V�����f�[�^�Ȃ�
			00 == (CSR_buff[t_no].TOK_NO & BIT_0) &&		//����ԍ�(B0:���ٖ���)
			00 != CSR_BAK_M_LEN ) {							//���ْ�=�O�H

		disp_moji_s_color(
			CSR_BAK_M_LEN,
			CSR_BAK_X_POS,
			CSR_BAK_Y_POS,
			CSR_BAK_C_COL,
			CSR_BAK_B_COL,
			CSR_BAK_SIZE,
			CSR_BAK_G_P,
			LCD_VBASE
			);
		disp_moji_s_rif(
			CSR_BAK_M_LEN,
			CSR_BAK_X_POS,
			CSR_BAK_Y_POS,
			CSR_BAK_SIZE
			);
	}

	if( 00 != CSR_buff[t_no].M_LEN ) {					//���ْ�=�O�H
		if( 0 == (CSR_buff[t_no].TOK_NO & BIT_0)) {			//����ԍ�(B0:���ٖ���)

			c_no = CSR_buff[t_no].SW56_UP;							//SW56��i��׸�
			if( c_no >= 0x80 && c_no < 0xc5 ) {						//0x80 �� ��i��׸� �� 0xc5
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
			}
			else
			{
				adr = CSR_TABLE_ADR + ((CSR_buff[t_no].CARA_NO-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				adr += CSR_HEAD_SIZE;
				g_p = (U2b *)adr;
			}

			CSR_BAK_M_LEN	= CSR_buff[t_no].M_LEN;
			CSR_BAK_X_POS	= CSR_buff[t_no].X_POS;
			CSR_BAK_Y_POS	= CSR_buff[t_no].Y_POS;
			CSR_BAK_C_COL	= CSR_buff[t_no].C_COL;
			CSR_BAK_B_COL	= CSR_buff[t_no].B_COL2;
			CSR_BAK_SIZE	= CSR_buff[t_no].SIZE;
			CSR_BAK_G_P = g_p;
			disp_moji_s_color(
				CSR_BAK_M_LEN,
				CSR_BAK_X_POS,
				CSR_BAK_Y_POS,
				CSR_BAK_C_COL,
				CSR_BAK_B_COL,
				CSR_BAK_SIZE,
				CSR_BAK_G_P,
				LCD_VBASE
				);
			disp_moji_s_rif(
				CSR_BAK_M_LEN,
				CSR_BAK_X_POS,
				CSR_BAK_Y_POS,
				CSR_BAK_SIZE
				);
			CSR_BAK_B_COL	= CSR_buff[t_no].B_COL1;
		}
	}
}

void	LCD_All_Disp(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[0][0];
	Dis_p = (UNl *)&LCD_VRAM[0][0];

	cnt =(PanelWidth * PanelHeight) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
//		Src_p++;
//		Dis_p++;
	}
}


void	WIN_All_Disp(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	if( (42 <= WINDOW_NO) && (WINDOW_NO <= 47) )		//V06c
	{	//��ƊJ�n/�I��WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-Window2Height][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-Window2Height][0];
		cnt =(PanelWidth * Window2Height) / 4;
	}

	else if( (51 <= WINDOW_NO) && (WINDOW_NO <= 58) )		//V06c
	{	//��ƊJ�n/�I��WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-Window2Height][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-Window2Height][0];
		cnt =(PanelWidth * Window2Height) / 4;
	}

	else
	{	//�ʏ�WINDOW
		Src_p = (UNl *)&LCD_VBASE[PanelHeight-WindowHeight][0];
		Dis_p = (UNl *)&LCD_VRAM[PanelHeight-WindowHeight][0];
		cnt =(PanelWidth * WindowHeight) / 4;
	}

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vabse_to_vmon1
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����ݒ蕔�̕\���u�a�`�r�d�����[�N�P�֑ޔ�
*					�i���[�V������ʂ�\������Ƃ��̏��׍H�i����������j�j
********************************************************************************
*/
void	mmon_vabse_to_vmon1(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[6*16*2][0];
	Dis_p = (UNl *)&LCD_VMON1[0][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}

/*
********************************************************************************
*  Module Name:		mmon_vmon1_to_vbase
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����ݒ蕔�̕\�����[�N�P���u�q�`�l�֖߂�
*					�i���[�V������ʂ�\������Ƃ��̏��׍H�i����������j�j
********************************************************************************
*/
void	mmon_vmon1_to_vbase(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON1[0][0];
	Dis_p = (UNl *)&LCD_VBASE[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vmon2_to_vbase
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����ݒ蕔�̕\�����[�N�����u�a�`�r�d�֖߂�
*					�i���[�V������ʂ�\������Ƃ��̏��׍H�i����������j�j
********************************************************************************
*/
void	mmon_vmon2_to_vbase(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON2[0][0];
	Dis_p = (UNl *)&LCD_VBASE[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vabse_to_vmon2
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����ݒ蕔�̕\���u�a�`�r�d�����[�N�Q��
*					�i���[�V������ʎ��A�s������ύX�����Ƃ��̕\���p�j
********************************************************************************
*/
void	mmon_vabse_to_vmon2(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VBASE[6*16*2][0];
	Dis_p = (UNl *)&LCD_VMON2[0][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		mmon_vmon2_to_vram
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����ݒ蕔�̕\�����[�N�Q���u�q�`�l��
*					�i���[�V������ʎ��A�s������ύX�����Ƃ��Ƀ��[�N�ŕҏW���\���u�q�`�l�̈�ցj
********************************************************************************
*/
void	mmon_vmon2_to_vram(void)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt;

	Src_p = (UNl *)&LCD_VMON2[0][0];
	Dis_p = (UNl *)&LCD_VRAM[6*16*2][0];

	cnt = (PanelWidth * (6*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = *Src_p++;
	}
}


/*
********************************************************************************
*  Module Name:		vmon2_line_erase
*  Function Name:	
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V������ʎ��A�s�v�s���s���폜
********************************************************************************
*/
void	vmon2_line_erase(UNs line_no)
{
	UNl		*Src_p, *Dis_p;
	UNl		cnt, col, wk;

	col = wk = (U4b)GAMENn_HEAD.scr_col;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;
	wk <<= 8;
	col |= wk;

	Dis_p = (UNl *)&LCD_VMON2[(line_no-6)*16*2][0];

	cnt = (PanelWidth * (1*16*2)) / 4;

	while(cnt--)
	{
		*Dis_p++ = col;
	}
}


/*
********************************************************************************
*  Module Name:		Disp_seidouseinou
*  Function Name:	�������\�L�����N�^�\��
*  Input	:		�ʏ핶���\�� or �������\�����\��
*					LCD�i�[�ޯ̧���ڽ
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
void	Disp_seidouseinou( UNs inf, UNb Lcd_p[][PanelWidth] )
{
	U4b		g_top, adr;
	U2b		*hrom, *hram;
	U2b		i, len;

	if (inf==0)
	{
		disp_moji_s_rif (
			10,									/* ��׸��			*/
			0,									/* ���o��X�ʒu		*/
			0,									/* ���o��Y�ʒu		*/
			0x202								/* ��������			*/
			);
	}
	else
	{
		adr = CHR_TABLE_ADR + ((372-1) * CHAR_MOJI_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (U2b *)adr;
		len = *hrom++;
		len >>= 8;

		disp_moji_s_color(
			10,									/* ��׸��			*/
			0,									/* ���o��X�ʒu		*/
			0,									/* ���o��Y�ʒu		*/
			COL_BLACK,							/* �����F			*/
			COL_GREEN,							/* �w�i�F			*/
			0x202,								/* ��������			*/
			hrom,								/* �����i�[���ڽ	*/
			Lcd_p								/* �\�����			*/
			);
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_sikaku1
*  Function Name:	�g�t���l�p�\���i������E�ցA�ォ�牺�ցA�`�悷��j
*  Input	:		�����o��X�ʒu
*					�����o��Y�ʒu
*					X����
*					Y����
*					�g�̐F
*					���̐F
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2010-09-10	V06
********************************************************************************
*/
void	Dsp_sikaku1 (UNs startX, UNs startY, UNs lngX, UNs lngY, UNs col_waku, UNs col_naka)
{
	UNs	xdot, ydot;
	UNs	xcnt, ycnt;

	ydot = startY;

	for (ycnt=0; ycnt<lngY; ycnt++, ydot++)
	{
		xdot = startX;

		if ( (ycnt==0) || (ycnt==(lngY-1)) )
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				LCD_VRAM[ydot][xdot] = col_waku;
			}
		}
		else
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				if ( (xcnt==0) || (xcnt==(lngX-1)) )
				{
					LCD_VRAM[ydot][xdot] = col_waku;
				}
				else
				{
					LCD_VRAM[ydot][xdot] = col_naka;
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_sikaku2
*  Function Name:	�g�t���l�p�\���i������E�ցA�������ցA�`�悷��j
*  Input	:		�����o��X�ʒu
*					�����o��Y�ʒu
*					X����
*					Y����
*					�g�̐F
*					���̐F
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2010-09-10	V06
********************************************************************************
*/
void	Dsp_sikaku2 (UNl startX, UNl startY, UNl lngX, UNl lngY, UNs col_waku, UNs col_naka, UNl Ylim)
{
	UNs	xdot, ydot;
	UNs	xcnt, ycnt;

	ydot = startY;

	for (ycnt=0; ycnt<lngY; ycnt++, ydot--)
	{
		xdot = startX;

		if (ydot < Ylim)		break;

		if ( (ycnt==0) || (ycnt==(lngY-1)) )
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				LCD_VRAM[ydot][xdot] = col_waku;
			}
		}
		else
		{
			for (xcnt=0; xcnt<lngX; xcnt++, xdot++)
			{
				if ( (xcnt==0) || (xcnt==(lngX-1)) )
				{
					LCD_VRAM[ydot][xdot] = col_waku;
				}
				else
				{
					LCD_VRAM[ydot][xdot] = col_naka;
				}
			}
		}
	}
}


/****************************************************************************/
/*																			*/
/*	�h�b�g�f�[�^�Z�b�g		�F	�O���t�p�h�b�g�f�[�^���Z�b�g����B			*/
/*																			*/
/*		�w�|�x���W�Q�_�Ŏ�����郉�C���i�h�b�g�f�[�^�j��`�悷��B			*/
/*																			*/
/****************************************************************************/
void	Disp_Line	(UNl X1, UNl Y1, UNl X2, UNl Y2, UNs col)
{
	UNs		i;
	UNs		bt;
	UNs		xb,		yb;
	UNs		cnt,	db;
	UNs		wb,		zb;
	UNs		tb,		nb,		hb;
	UNs		x_dif,	y_dif;
	UNs		minus;
	UNs		temp;
	UNs		rate_0;
	UNl		wkl;


//	�擪�̃o�C�g�ʒu�A�r�b�g�ʒu���Z�o ///////////////////////////////////////
	yb = Y1;
	xb = X1;
	bt = col;

//	�^�e���A���R������ ///////////////////////////////////////////////////////
	if (X1 == X2){									/* �Ð� X�������ω��Ȃ�	*/
		if (Y1 == Y2){								/* Y�������ω��Ȃ�		*/
			LCD_VRAM[yb][xb] = bt;						/* 1 �ޯč��W ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y�� �������ω�		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				LCD_VRAM[yb+nb][xb] = bt;			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}else{										/* Y�� ������ω�		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				LCD_VRAM[yb-nb][xb] |= bt;			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 �Ή��Ȃ�		*/

	if (Y1 == Y2){									/* ֺ�� Y�������ω��Ȃ�	*/
		for (i=X1; i<=X2; i++){						/* X�����ޯĐ��J��Ԃ�	*/
			LCD_VRAM[yb][xb] = bt;					/* ��ײ� �ޯč��W ON	*/
			xb += 1;								/* ���޲Ăֈړ�			*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	�ʏ�̐��i�ȂȂߐ��j�`�揈�� /////////////////////////////////////////////
	if (Y1 < Y2){									/* �`����������߂�		*/
		y_dif = (Y2 - Y1);				/* 600�{�ŉ��Z����		*/
		x_dif = (X2 - X1);				/* X�����ޯĕω����Z�o	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<X2; )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				yb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<X2; )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					yb++;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
	else
	{											/* max 95 * 600 = 57000	*/
		y_dif = (Y1 - Y2);				/* 600�{�ŉ��Z����		*/
		x_dif = (X2 - X1);				/* X�����ޯĕω����Z�o	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<X2; )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				yb--;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<X2; )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					yb--;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb--)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
}


/****************************************************************************/
/*																			*/
/*	�h�b�g�f�[�^�Z�b�g		�F	�O���t�p�h�b�g�f�[�^���Z�b�g����B			*/
/*																			*/
/*		�w�|�x���W�Q�_�Ŏ�����郉�C���i�h�b�g�f�[�^�j��`�悷��B			*/
/*																			*/
/****************************************************************************/
void	Disp_Line_Box	(UNs X1, UNs Y1, UNs X2, UNs Y2, UNs col)
{
	UNs		i;
	UNs		xb, yb;

	yb = Y1;
	xb = X1;

	for (i=X2; i!=0; i--, xb++)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 �ޯč��W ON		*/
	}
	for (i=Y2; i!=0; i--, yb++)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 �ޯč��W ON		*/
	}
	for (i=X2; i!=0; i--, xb--)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 �ޯč��W ON		*/
	}
	for (i=Y2; i!=0; i--, yb--)
	{
		LCD_VRAM[yb][xb] = col;						/* 1 �ޯč��W ON		*/
	}

}


