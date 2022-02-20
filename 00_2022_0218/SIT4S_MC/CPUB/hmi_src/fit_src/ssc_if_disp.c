/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�\�@���@�ց@��															*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-21
*
*************************************************************************************/

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_addr.h"							//�Q�ƕϐ���`
#include "ssc_ver1.h"
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
/* �O���Q�ƕϐ���` -------------------------------------------------- */
/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	GENGO_chg(UNi);							//��Q�J����ؑւ�����

void	Disp_line(UNs, UNs, UNs, UNs);			//��ʕ\���p 1�s�\��
void	Disp_moji(UNs, UNs *, UNs);				//�����\��
void	Disp_char(UNs, UNs, UNs, UNs *, UNs);	//�ޯĕ\��

void	disp_all_s(UNs, UNs, UNs);				//�S��ʕ\���p�������ށ��ޯĕϊ�
void	disp_line_s(UNs, UNs *, UNs *);			//1�s�\���p�������ށ��ޯĕϊ�

void	disp_memset(UNs, UNs *, UNs);			//�\���p�̈���w���ް��Őݒ�
UNi		disp_memnot(UNs, UNs *);				//�\���p�̈�̎w���ް��𔽓]
void	disp_moji_s(UNs , UNs *, UNs *, UNi);	//�����\���p�������ށ��ޯĕϊ�

UNi		code_dot_cnv(UNs, UNb *, UNi);			//�������ށ��ޯĕϊ�

UNs *	disp_adr_shr(UNs, UNs, UNs);			//��ʂ̷�׸����ڽ�̎Z�o
void	disp_char_cpy(UNs, UNs, UNs, UNs *, UNs);	//��ʂ̷�׸��̺�߰
UNs *	mess_adr_shr(UNi);						//���b�Z�[�W��ʃL�����N�^�A�h���X����

void	BCD_ASCII(UNl, UNb *);					//BCD��ASCII�@�ϊ�
void	HEX_ASCII(UNl, UNb *);					//HEX��ASCII�@�ϊ�	shima
UNl		BCD_HEX4(UNl);							//BCD��HEX�@�ϊ�
UNl		HEX_BCD4(UNl);							//HEX��BCD�@�ϊ�
void	Ascii_Sjis(UNs, UNb *, UNs *);			//Ascii���� �� �S�pS-Jis���ށ@�ϊ�
UNs		jiscnv(UNs);							//�V�t�g�i�h�r���i�h�r�ϊ�

void	memset_word(UNs *, UNs, UNs);			//�w��̈���w���ް��ɂ�ܰ�ޒP�ʂŐݒ�
void	memcpy_word(UNs *, UNs *, UNs);			//�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNs	Han_MPtn_Table[256][16];		//���p�����p�^�[���@�e�[�u��



/*
********************************************************************************
*  Module Name:		GENGO_chg
*  Function Name:	����؂芷���@�\
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2006-09-01	V01x
********************************************************************************
*/
void	GENGO_SEQ_CHG(void)
{
	UNs		seq_chg, seq_bit, seq_one ;

//V06m	seq_chg = seq_bit = SEQ_PAR_103 & (BIT_4+BIT_5);		// new
	seq_chg = seq_bit = (SEQ_PAR_103 & (BIT_4+BIT_5)) | (SEQ_PAR_113 & BIT_12);		// new

	seq_chg ^= GENG_SEQ_LST;								// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	GENG_SEQ_LST = seq_bit;

//V06m
//	if ( seq_one & BIT_4 )
//	{
//		SEQ_020_SV &= ~BIT_13;
//	}
//	if ( seq_one & BIT_5 )
//	{
//		SEQ_020_SV |= BIT_13;
//	}
	if ( seq_one & BIT_4 )
	{
//V06n		SV_LANGUAGE = 0;
		SV_LANGUAGE = 1;
		FRAM_csum_set();
	}
	else if ( seq_one & BIT_5 )
	{
//V06n		SV_LANGUAGE = 1;
		SV_LANGUAGE = 2;
		FRAM_csum_set();
	}
	else if ( seq_one & BIT_12 )
	{
//V06n		SV_LANGUAGE = 2;
		SV_LANGUAGE = 3;
		FRAM_csum_set();
	}

}


/*
********************************************************************************
*  Module Name:		GENGO_chg
*  Function Name:	��Q�J����ؑւ�����
*  Input	:		�׸ށF0:�ʏ폈���^0xff:��������
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-17
********************************************************************************
*/
void	GENGO_chg(UNi flag)
{
	UNs	*g_p, bf1, bf2;

//V06m	bf1 = (SEQ_020_SV & BIT_D);						//���J���� �ؑւ��L��(1:�p��)
	bf1 = (SEQ_PAR_050 & (BIT_12+BIT_13+BIT_14));

	bf2 = GENGO_CHG_LAST;
	GENGO_CHG_LAST = bf1;
	bf1 ^= bf2;

	if( 00 != bf1 ) {								//�ω��L��H

//V06m
//		if(SEQ_020_SV & BIT_D){						//���J���� �ؑւ��L��(1:�p��)�H
//			g_p = (UNs *)E_GAMEN_TOP2;				//���J���� ��{�����ڽ
//
//			if( 0x0000 == *g_p || 0xffff == *g_p ){	//���J���� ��ʃL�����N�^�L��H
//				language_chg = 00;					//�̾�ı��ڽ�̐ݒ�(���{��)
//			}
//			else{									//YES
//				language_chg = E_2language;			//�̾�ı��ڽ�̐ݒ�(�p��)
//			}
//		}
//		else {										//���{��
//			language_chg = 00;						//�̾�ı��ڽ�̐ݒ�(���{��)
//		}
		if (SEQ_PAR_050 & BIT_12) {
			language_chg = E_2language * 0;			//�̾�ı��ڽ�̐ݒ�(���{��)
		}
		else if (SEQ_PAR_050 & BIT_13) {
			language_chg = E_2language * 1;			//�̾�ı��ڽ�̐ݒ�(�p��)
		}
		else if (SEQ_PAR_050 & BIT_14) {
			language_chg = E_2language * 2;			//�̾�ı��ڽ�̐ݒ�(������)
		}
		else {
			language_chg = E_2language * 0;			//�̾�ı��ڽ�̐ݒ�(���{��)
		}


#if (SIT_TYPE_SEL == TYPE_SIT3)
#else
		Gamen_Init();							//��ʕ\��
		CAMname_pon_read();						//
#endif
		if( flag == 0 )								//�ʏ폈���H
		{
			GAM_CHG_WIN_NO_BAK = WINDOW_NO;

			GAMEN_disp();							//��ʕ\��

			if ( (GAMEN_NO == 4) || (GAMEN_NO == 29) )	// V04a
			{
				GRAPH_INIT();						//�O���t�`�揉������
				GRAPH_DISP();						//�O���t�`�揈��
			}

			WINDOW_NO = GAM_CHG_WIN_NO_BAK;
			if (WINDOW_NO != 0)							// V04a
			{
				WIN_gamen_disp();					//��ʕ\��
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Disp_line
*  Function Name:	��ʕ\���p 1�s�\��
*  Input	:		��ʔԍ�
*					0:�ʏ��ʁ^1:����޳���
*					LCDܰ��̑I��(0:LCD_WORK1/1:LCD_WORK2)
*					�\���s��
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-25
********************************************************************************
*/
void	Disp_line(UNs g_no, UNs g_sel, UNs l_no, UNs line_no)
{
	UNs	*g_adr_p, *dst_p;

	if( g_sel == 0 ){								//�ʏ��ʁH
		g_no --;
		g_no &= 0x003f;								//��ʔԍ���63�ȉ��ɐݒ�
		g_adr_p = (UNs *)E_GAMEN_TOP;				//��ʃL�����N�^�̃A�h���X�Z�o
		g_adr_p += g_no * (0x280/2);
		g_adr_p += language_chg;					//��Q�J����ؑւ�
		g_adr_p += line_no * (E_line/2);			//��ʃL�����N�^�̃A�h���X�@�X�V
	}
	else{											//����޳���
		if( g_no != 00 ) {
			g_no --;
		}
		g_no &= 0x001f;								//��ʔԍ���31�ȉ��ɐݒ�
		g_adr_p = (UNs *)E_WINDOW_TOP;				//�E�C���h�E��ʂ̃A�h���X�Z�o
		g_adr_p += g_no * (0x180/2);
		g_adr_p += language_chg;					//��Q�J����ؑւ�
		g_adr_p += (line_no-6) * (E_line/2);		//��ʃL�����N�^�̃A�h���X�@�X�V
	}

	if(l_no == 0){									//LCDܰ��̑I�� 0:LCD_WORK1 ?
		dst_p = &LCD_WORK1[0][0][0];
	}
	else{
		dst_p = &LCD_WORK2[0][0][0];
	}

	disp_line_s(line_no, g_adr_p, dst_p);			//1�s�\���p�������ށ��ޯĕϊ�
	Lcd_line(00, line_no, E_line_bf, dst_p);		//�\�s�\��

}


/*
********************************************************************************
*  Module Name:		Disp_moji
*  Function Name:	�����\��
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�������ޥ�i�[���ڽ
*					�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-20
********************************************************************************
*/
void	Disp_moji(UNs xy_no, UNs *g_adr_p, UNs flg )
{

	disp_moji_s(xy_no, g_adr_p, &LCD_WORK1[0][0][0], flg);	//�����\���p�������ށ��ޯĕϊ�

	Lcd_cr(00, xy_no, &LCD_WORK1[0][0][0]);					//��גP�ʕ\��

}


/*
********************************************************************************
*  Module Name:		Disp_char
*  Function Name:	�ޯĕ\��
*  Input	:		x_no �F�\�� X��(0�`39)�m���n
*					Y_no �F�\�� Y��(0�`14)�m�s�n
*					c_cnt�F��ѐ�(1�`40)�m�������n
*					*src_p�F�\���ް���i�[���ڽ
*					flg�F�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-05
********************************************************************************
*/
void	Disp_char(UNs x_no, UNs y_no, UNs c_cnt, UNs *src_p, UNs flg)
{
	UNs		y, i, wk[40], *dst_p;

	if(flg == 0x00 ) {									//����\���H
		y = (y_no << 4);								//Y��(0�`14)�m�s�n* 16 = Y���ޯĈʒu
		dst_p = src_p;
		for(i = 16; i > 0 ; i--, y++) {
			Lcd_draw(00, x_no, y, c_cnt, src_p);		//�ޯĕ\��
			dst_p += (c_cnt << 1);						//���ް��i�[���ڽ
		}
	}
	else {												//���]�\��
		y = (c_cnt << 4);
		dst_p = &wk[0];
		while(y--){
			*dst_p++ = ~(*src_p++);						//�ް����]
		}

		y = (y_no << 4);								//Y��(0�`14)�m�s�n* 16 = Y���ޯĈʒu
		dst_p = &wk[0];
		for(i = 16; i > 0 ; i--, y++) {
			Lcd_draw(00, x_no, y, c_cnt, dst_p);		//�ޯĕ\��
			dst_p += (c_cnt << 1);						//���ް��i�[���ڽ
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
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	disp_all_s(UNs g_no, UNs g_sel, UNs l_no)
{
	UNs	*g_adr_p, *dst_p, xy_no;
	UNi	i;

	if(l_no == 0){									//LCDܰ��̑I�� 0:LCD_WORK1 ?
		dst_p = &LCD_WORK1[0][0][0];
	}
	else{
		dst_p = &LCD_WORK2[0][0][0];
	}

	if( g_sel == 0 ){								//�ʏ��ʁH
		g_no --;
//shima		g_no &= 0x003f;								//��ʔԍ���63�ȉ��ɐݒ�
		g_adr_p = (UNs *)E_GAMEN_TOP;				//��ʃL�����N�^�̃A�h���X�Z�o
		g_adr_p += g_no * (0x280/2);
		g_adr_p += language_chg;					//��Q�J����ؑւ�
		i = 0;										//�s�̐ݒ�

		for( ; i < 15 ; i++ ) {						//1��ʕ��\���ް��̺�߰
			disp_line_s( i, g_adr_p, dst_p);		//1�s�\���p�������ށ��ޯĕϊ�
			g_adr_p += (E_line/2);					//��ʃL�����N�^�̃A�h���X�@�X�V
		}
	}
	else{											//����޳���
		if( g_no != 00 ) {
			g_no --;
		}
		g_no &= 0x001f;								//��ʔԍ���31�ȉ��ɐݒ�
		g_adr_p = (UNs *)E_WINDOW_TOP;				//�E�C���h�E��ʂ̃A�h���X�Z�o
		g_adr_p += g_no * (0x180/2);
		g_adr_p += language_chg;					//��Q�J����ؑւ�

		xy_no = 0xa000;								//���ْ���40����
		if( g_sel & BIT_15 ) {
			xy_no = 0x5800;							//���ْ���22����
		}

		for( i = 6 ; i < 15 ; i++ ) {				//1��ʕ��\���ް��̺�߰(�s�̐ݒ�)
			xy_no &= 0xfc00;
			xy_no |= (i & 0x000f);
			disp_moji_s(xy_no, g_adr_p, dst_p, 0x00);	//�����\���p�������ށ��ޯĕϊ�
			g_adr_p += (E_line/2);						//��ʃL�����N�^�̃A�h���X�@�X�V
		}
	}
}


/*
********************************************************************************
*  Module Name:		disp_line_s
*  Function Name:	1�s�\���p�������ށ��ޯĕϊ�
*  Input	:		�\���s��
*			:		�������ޥ�i�[���ڽ
*					�i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	disp_line_s(UNs l_no, UNs *g_adr_p, UNs *Lcd_p)
{
	UNs		xy_no;

	xy_no = (l_no & 0x000f);
	xy_no |= 0xa000;								//���ْ���40����
	disp_moji_s(xy_no, g_adr_p, Lcd_p, 0x00);		//�����\���p�������ށ��ޯĕϊ�

}


/*
********************************************************************************
*  Module Name:		disp_memset
*  Function Name:	�\���p�̈���w���ް��Őݒ�
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�i�[�ޯ̧���ڽ
*			:		�ݒ��ް�
*
*  Return	: 		�Ȃ�
*  Note		:	�w�肳�ꂽ�\���p�̈�̐擪����A�w���ް����w�蕶�������ݒ肷��
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	disp_memset(UNs xy_no, UNs *Lcd_p, UNs s_dt )
{
	UNi	i, j, k;
	UNs	*Dst_p;

	i = xy_no & 0x000f;						//�s�̱��ڽ�@�Z�o
	i *= E_line_size;
	j = ( xy_no >> 4) & 0x003f;				//���̱��ڽ�@�Z�o
	Lcd_p += i + j;							//LCD�\���̈�̱��ڽ�ݒ�

	i = 16;
	while(i--) {
		Dst_p = Lcd_p;
		k = ( xy_no >> 10);						//�������@�Z�o
		while(k--) {
			*Dst_p++ = (s_dt & 0x00ff);			//�w���ް����w�蕶�������ݒ�
		}
		Lcd_p += E_next_dot;					//1�����̎�dot�ʒu��
	}
}


/*
********************************************************************************
*  Module Name:		disp_memnot
*  Function Name:	�\���p�̈�̎w���ް��𔽓]
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		LCD�i�[�ޯ̧���ڽ
*
*  Return	: 		00:����I���^ff�F�ُ�I��
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
UNi	disp_memnot(UNs xy_no, UNs *Lcd_p)
{
	UNi	i, j, k;
	UNs	*Dst_p, wk;

	i = xy_no & 0x000f;							//�s�̱��ڽ�@�Z�o
	i *= E_line_size;
	j = ( xy_no >> 4) & 0x003f;					//���̱��ڽ�@�Z�o
	Lcd_p += i + j;								//LCD�\���̈�̱��ڽ�ݒ�

	k = ( xy_no >> 10);							//�������@�Z�o
	if( k == 00){
		return(0xff);
	}
	else {
		i = 16;
		while(i--) {
			Dst_p = Lcd_p;
			k = ( xy_no >> 10);					//�������@�Z�o
			while(k--) {						//�w���ް����w�蕶�������ݒ�
				wk = ~(*Dst_p);					//�ް��̔��]
				*Dst_p++ = (wk & 0x00ff);
			}
			Lcd_p += E_next_dot;				//1�����̎�dot�ʒu��
		}
	}
	return(0x00);
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
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	disp_moji_s(UNs xy_no, UNs *g_adr_p, UNs *Lcd_p, UNi flg)
{
	UNi	i, j, size;
	UNs	cnt, cnv_wk, *Dst_p;
	UNb	moji[E_line], dot_wk[32];

	cnt = xy_no >> 10;									//�������@�Z�o
	for( i=0 ; i < cnt ; i += 2 ) {						//ܰ�ށ��޲ĒP�ʱ����\�̈�ɺ�߰
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	i = xy_no & 0x000f;									//�s�̱��ڽ�@�Z�o
	i *= E_line_size;
	j = (xy_no >> 4) & 0x003f;							//���̱��ڽ�@�Z�o
	Lcd_p += (i + j);									//LCD�\���̈�̱��ڽ�ݒ�

	for( i=0 ; i < cnt ; i++ ){
		cnv_wk = moji[i+1];								//�������ނ̐ݒ�
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//�������ށ��ޯĕϊ�
															//���p
			j = 0;
			size = 16;
			Dst_p = Lcd_p;
			while(size--) {
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*Dst_p = cnv_wk;
				Dst_p += E_next_dot;						//1�����̎�dot�ʒu��
			}
			Lcd_p ++;										//�i�[�ޯ̧����ڽ�@�X�V
		}
		else {												//�S�p
			j = 0;
			size = 16;
			Dst_p = Lcd_p;
			while(size--) {
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*Dst_p = cnv_wk;
				cnv_wk = (dot_wk[j++] & 0x00ff);
				*(Dst_p+1) = cnv_wk;
				Dst_p += E_next_dot;						//1�����̎�dot�ʒu��
			}
			Lcd_p ++;										//�i�[�ޯ̧����ڽ�@�X�V
			Lcd_p ++;
			i++;											//+1
		}
	}
}


/*
********************************************************************************
*  Module Name:		code_dot_cnv	(���FCARA_ONE_SET)
*  Function Name:	�������ށ��ޯĕϊ�
*
*  Input	:		��������
*			:		�i�[�ޯ̧����ڽ(�޲ı����̈�)
*					�t���O�F�i0x00=����\���^0xff:���]�\���j
*
*  Return	: 		0:���p
*					1:�S�p
*
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-20
********************************************************************************
*/
UNi		code_dot_cnv(UNs d_cara, UNb *Dst_p, UNi flg)
{
#if (SIT_TYPE_SEL == TYPE_SIT3)
	UNb	*Src_p;
	UNb	*Dst_px;
#else
	UNs	*Src_p;
	UNs	*Dst_px;
#endif
	UNb	code1;
	UNs	*Srcw_p, d_cara_swap, dat;
	UNi	type, r_wk, size;

#if (SIT_TYPE_SEL == TYPE_SIT3)
	Dst_px = Dst_p;
#else
	Dst_px = (UNs *)Dst_p;
#endif

	code1 = d_cara & 0x00ff;
	if( code1 < 0x80 ) {						//���p�R�[�h�H
		type = 00;								//Yes
	}
	else if(code1 < 0xA0) {						//�S�p�R�[�h�H
		type = 01;								//Yes
	}
	else if(code1 < 0xE0) {						//���p�R�[�h�H
		type = 00;								//Yes
	}
	else {
		type = 01;								//�S�p�R�[�h
	}

	d_cara_swap = ((d_cara<<8)&0xff00) | ((d_cara>>8)&0x0ff);	//swap
	if(0x0f040 <= d_cara_swap && d_cara_swap <= 0x0f594) {	//�O���R�[�h�H		V01l
		type = 02;								//Yes
	}


	if(type == 01) {							//�S�p�R�[�h ?
	/**************** �����R�[�h�h�b�g�ϊ����� ***************/
#if (SIT_TYPE_SEL == TYPE_SIT3)
		Src_p = kan_rom_set(jiscnv(d_cara));	//�V�t�g�i�h�r���i�h�r�ϊ��������q�n�l�A�h���X�Z�b�g
#else
		Src_p = (UNs *)kan_rom_set(jiscnv(d_cara));	//�V�t�g�i�h�r���i�h�r�ϊ��������q�n�l�A�h���X�Z�b�g
#endif

#if (SIT_TYPE_SEL == TYPE_SIT3)
			size = 32;						/* �ް�Copy */
#else
			size = 16;						/* �ް�Copy */
#endif
		if(flg == 0xff ) {					//���]�\���H
			while( size-- ) {
//				*Dst_p++ = ~(*Src_p++);		//�ޯĔ��]
				*Dst_px++ = ~(*Src_p++);		//�ޯĔ��]
			}
		}
		else {								//����\��
			while( size-- ) {
//				*Dst_p++ = *Src_p++;
				*Dst_px++ = *Src_p++;
			}
		}
		r_wk = 1;							//�S�p����
	}

	else if(type == 02) {
	/**************** �O���R�[�h�h�b�g�ϊ����� ***************/		//V01l
		Srcw_p = (UNs *)E_GAIZI_TOP;		//��ʃL�����N�^�̃A�h���X�Z�o
		Srcw_p += (d_cara_swap-0xf040)*16;

		if(flg == 0xff ) {					//���]�\���H
			size = 16;						/* �ް�Copy */
			while( size-- ) {
				dat = ~(*Srcw_p++);			//�ޯĔ��]
				*Dst_p++ = (dat>>8) & 0xff;
				*Dst_p++ = dat & 0xff;
			}
		}
		else {								//����\��
			size = 16;						/* �ް�Copy */
			while( size-- ) {
				dat = *Srcw_p++;
				*Dst_p++ = (dat>>8) & 0xff;
				*Dst_p++ = dat & 0xff;
			}
		}
		r_wk = 1;							//�S�p����
	}

	else {										//���p�R�[�h
	/**************** ���p�R�[�h�h�b�g�ϊ����� ***************/
		Srcw_p = &Han_MPtn_Table[code1][0];	//���p���������ð��� ���ڽ�Z�o

		if(flg == 0xff ) {					//���]�\���H
			size = 16;						/* �ް�Copy */
			while( size-- ) {
				*Dst_p++ = ~(*Srcw_p++);	//�ޯĔ��]
			}
		}
		else {								//����\��
			size = 16;						/* �ް�Copy */
			while( size-- ) {
				*Dst_p++ = *Srcw_p++;
			}
		}
		r_wk = 0;							//���p����
	}

	return (r_wk);
}


/*
********************************************************************************
*  Module Name:		disp_adr_shr
*  Function Name:	��ʂ̷�׸����ڽ�̎Z�o
*  Input	:		��ʔԍ�
*					�s
*					��(��͕s��)
*
*  Return	: 		��ʂ̷�׸��̐擪���ڽ
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-22
********************************************************************************
*/
UNs *	disp_adr_shr(UNs g_no, UNs l_no, UNs k_no)
{
	UNs	*g_p;

	g_no --;
	g_no &= 0x003f;							//��ʔԍ���63�ȉ��ɐݒ�
	g_p = (UNs *)E_GAMEN_TOP;				//��ʃL�����N�^�̃A�h���X�Z�o
	g_p += g_no * (0x280/2);
	g_p += language_chg;					//��Q�J����ؑւ�
	g_p += l_no * (E_line/2);				//��ʃL�����N�^�̃A�h���X�@�X�V
	g_p += (k_no >> 1);						//��ʃL�����N�^�̃A�h���X�@�X�V

	return(g_p);
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	��ʂ̷�׸��̺�߰
*  Input	:		��ʔԍ�
*					�s
*					��
*					�i�[���ڽ
*					�]��ܰ�ސ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-22
********************************************************************************
*/
void	disp_char_cpy(UNs g_no, UNs l_no, UNs k_no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;

	g_p = disp_adr_shr(g_no, l_no, k_no);	//��ʂ̷�׸����ڽ�̎Z�o(��ʔԍ�, �s, ��(��͕s��))

	if(k_no & 0x0001){						//� ���H
		for( ; w_cnt > 0 ; w_cnt-- ) {
			wk_bf = *g_p++;
			wk_bf <<= 8;
			wk_bf |= (*g_p >> 8);
			*bf_p++ = wk_bf;
		}
	}
	else{									//����
		memcpy_word(bf_p, g_p, w_cnt);		//��ʂ̷�׸��̺�߰
	}
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	��ʂ̷�׸��̺�߰
*  Input	:		��ʔԍ�
*					�s
*					��
*					�i�[���ڽ
*					�]��ܰ�ސ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-22
********************************************************************************
*/
void	disp_char_SWcpy(UNl no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;
	UNl		adr;

	adr =  SWL_TABLE_ADR + ((no-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	g_p = (UNs *)adr;
	g_p++;

	memcpy_word(bf_p, g_p, w_cnt);		//��ʂ̷�׸��̺�߰
}


/*
********************************************************************************
*  Module Name:		disp_char_cpy
*  Function Name:	��ʂ̷�׸��̺�߰
*  Input	:		��ʔԍ�
*					�s
*					��
*					�i�[���ڽ
*					�]��ܰ�ސ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-22
********************************************************************************
*/
void	disp_char_CSRcpy(UNl no, UNs *bf_p, UNs w_cnt)
{
	UNs	*g_p, wk_bf;
	UNl		adr;

	adr =  CSR_TABLE_ADR + ((no-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	g_p = (UNs *)adr;
	g_p++;

	memcpy_word(bf_p, g_p, w_cnt);		//��ʂ̷�׸��̺�߰
}


/*
********************************************************************************
*  Module Name:		mess_adr_shr
*  Function Name:	���b�Z�[�W��ʃL�����N�^�A�h���X����
*  Input	:		���b�Z�[�W�ԍ�
*
*  Return	: 		���b�Z�[�W�擪�A�h���X
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
UNs *	mess_adr_shr(UNi m_no)
{
	UNs	*g_p;

	if(m_no >= /*15 V01j*/20) {
		g_p = (UNs *)E_INTROCK_TOP;					//�K�C�_���X��ʃf�[�^
	}
	else{
		if(m_no != 0){
			m_no --;
		}
		g_p = (UNs *)E_CHAR_TOP;					//�L�����N�^��ʃf�[�^
		g_p += m_no * (0x258/2);
	}
	g_p += language_chg;							//��Q�J����ؑւ�
	return(g_p);
}


/*
********************************************************************************
*  Module Name:		BCD_ASCII
*  Function Name:	BCD��ASCII �ϊ�
*  Input	:		BCD data(long)
*					ASCII �i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:	4Byte BCD DATA(8��) -> 8Byte ASCII DATA
*
*  �� ��	:FIT)�c�[		ON:2002-05-22
********************************************************************************
*/
void	BCD_ASCII(UNl bcd_d, UNb *dst_p)
{
	UNi		Size;

	Size = 8;
	while(Size--) {
		*dst_p++ = (UNs)((bcd_d & 0x000f) + '0');
		bcd_d >>= 4;
	}
}


/*
********************************************************************************
*  Module Name:		HEX_ASCII
*  Function Name:	HEX��ASCII �ϊ�
*  Input	:		HEX data(long)
*					ASCII �i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:	4Byte HEX DATA(8��) -> 8Byte ASCII DATA
*
*  �� ��	:shima		ON:2002-11-12
********************************************************************************
*/
void	HEX_ASCII(UNl bcd_d, UNb *dst_p)
{
	UNi		Size;

	Size = 8;
	while(Size--) {
		if ((bcd_d & 0x000f) > 9 ) {
			*dst_p++ = (UNs)(((bcd_d & 0x000f)-0x0a) + 'A');
		}
		else {
			*dst_p++ = (UNs)((bcd_d & 0x000f) + '0');
		}
		bcd_d >>= 4;
	}
}


/*
********************************************************************************
*  Module Name:		BCD_HEX4
*  Function Name:	BCD��HEX�@�ϊ�
*  Input	:		BCD DATA(long)
*
*  Return	: 		HEX DATA(long)
*  Note		:		BCD 8�� -> 4Byte HEX DATA
*
*  �� ��	:FIT)�c�[		ON:2002-06-11
********************************************************************************
*/
//BCD -> HEX �ϊ�ð���
const UNl bhex_cnvtbl2[10] = { 00,10,      20,      30,      40,      50,      60,      70,      80,      90 };
const UNl bhex_cnvtbl3[10] = { 00,100,     200,     300,     400,     500,     600,     700,     800,     900 };
const UNl bhex_cnvtbl4[10] = { 00,1000,    2000,    3000,    4000,    5000,    6000,    7000,    8000,    9000 };
const UNl bhex_cnvtbl5[10] = { 00,10000,   20000,   30000,   40000,   50000,   60000,   70000,   80000,   90000 };
const UNl bhex_cnvtbl6[10] = { 00,100000,  200000,  300000,  400000,  500000,  600000,  700000,  800000,  900000 };
const UNl bhex_cnvtbl7[10] = { 00,1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000 };
const UNl bhex_cnvtbl8[10] = { 00,10000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000 };

UNl		BCD_HEX4(UNl bcd_d)
{
	UNl		cnv, i;

	cnv = 0;
	cnv = bcd_d & 0x000f;		//1��

	i = bcd_d >> 4;				//10��
	i &= 0x000f;
	cnv += bhex_cnvtbl2[i];

	i = bcd_d >> 8;				//100��
	i &= 0x000f;
	cnv += bhex_cnvtbl3[i];

	i = bcd_d >> 12;			//1000��
	i &= 0x000f;
	cnv += bhex_cnvtbl4[i];

	i = bcd_d >> 16;			//10000��
	i &= 0x000f;
	cnv += bhex_cnvtbl5[i];

	i = bcd_d >> 20;			//100000��
	i &= 0x000f;
	cnv += bhex_cnvtbl6[i];

	i = bcd_d >> 24;			//1000000��
	i &= 0x000f;
	cnv += bhex_cnvtbl7[i];

	i = bcd_d >> 28;			//10000000��
	i &= 0x000f;
	cnv += bhex_cnvtbl8[i];

	return(cnv);
}


/*
********************************************************************************
*  Module Name:		HEX_BCD4
*  Function Name:	Hex��BCD�@�ϊ�
*  Input	:		HEX data(long)
*
*  Return	: 		BCD data(long)
*  Note		:	4Byte HEX DATA -> 4Byte BCD DATA(8��)
*
*  �� ��	:FIT)�c�[		ON:2002-05-22
********************************************************************************
*/
UNl		HEX_BCD4(UNl hex_bf)
{
	UNl		i, bcd_bf;
	UNl		j;

	bcd_bf = 0;
	i = hex_bf;
	if(i > 99999999 ) {			//����`�F�b�N
		i = 99999999;
	}
//							8��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10000000 ) {
			i -= 10000000;
		}
		else {
			break;
		}
	}
	bcd_bf = (j << 28);

//							7��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1000000 ) {
			i -= 1000000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 24);

//							6��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 100000 ) {
			i -= 100000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 20);

//							5��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10000 ) {
			i -= 10000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 16);

//							4��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1000 ) {
			i -= 1000;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 12);

//							3��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 100 ) {
			i -= 100;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 8);

//							2��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 10 ) {
			i -= 10;
		}
		else {
			break;
		}
	}
	bcd_bf |= (j << 4);

//							1��
	for( j=0 ; j<10 ; j++ ) {
		if( i >= 1 ) {
			i -= 1;
		}
		else {
			break;
		}
	}
	bcd_bf |= j;

	return(bcd_bf);
}


/*
********************************************************************************
*  Module Name:		ASCII_SJIS
*  Function Name:	Ascii���� �� �S�pS-Jis���ށ@�ϊ�
*  Input	:		�ϊ����޲Đ�
*					Ascii���ޗ̈�̱��ڽ
*					�S�pS-Jis���ޗ̈�̱��ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-26
********************************************************************************
*/
void	Ascii_Sjis(UNs size, UNb *code_p, UNs *dst_p)
{
	/* ���p�R�[�h���S�p�r�i�h�r�R�[�h�ϊ��e�[�u�� */
	/* �����R�[�h�\�i���p�����j�ɑΉ� */
const unsigned short code_chg_tbl[158] =
	{0x8140,0x8149,0x818d,0x8194,0x8190,0x8193,0x8195,0x818c,0x8169,0x816a,0x8196,0x817b,0x8143,0x817c,0x8144,0x815e
	,0x824f,0x8250,0x8251,0x8252,0x8253,0x8254,0x8255,0x8256,0x8257,0x8258,0x8146,0x8147,0x8183,0x8181,0x8184,0x8148
	,0x8197,0x8260,0x8261,0x8262,0x8263,0x8264,0x8265,0x8266,0x8267,0x8268,0x8269,0x826a,0x826b,0x826c,0x826d,0x826e
	,0x826f,0x8270,0x8271,0x8272,0x8273,0x8274,0x8275,0x8276,0x8277,0x8278,0x8279,0x816d,0x818f,0x816e,0x81c8,0x8151
	,0x8140,0x8281,0x8282,0x8283,0x8284,0x8285,0x8286,0x8287,0x8288,0x8289,0x828a,0x828b,0x828c,0x828d,0x828e,0x828f
	,0x8290,0x8291,0x8292,0x8293,0x8294,0x8295,0x8296,0x8297,0x8298,0x8299,0x829a,0x816f,0x8162,0x8170,0x8150
	,0x8142,0x8175,0x8176,0x8141,0x8140,0x8392,0x8340,0x8342,0x8344,0x8346,0x8348,0x8383,0x8385,0x8387,0x8362
	,0x815b,0x8341,0x8343,0x8345,0x8347,0x8349,0x834a,0x834c,0x834e,0x8350,0x8352,0x8354,0x8356,0x8358,0x835a,0x835c
	,0x835e,0x8360,0x8363,0x8365,0x8367,0x8369,0x836a,0x836b,0x836c,0x836d,0x836e,0x8371,0x8374,0x8377,0x837a,0x837d
	,0x837e,0x8380,0x8381,0x8382,0x8384,0x8386,0x8388,0x8389,0x838a,0x838b,0x838c,0x838d,0x838f,0x8393,0x814a,0x814b};


	while(size--) {
		*dst_p++ = code_chg_tbl[(*code_p) - 0x20];		//ASCII�R�[�h��SJIS�R�[�h�ɕϊ�
		code_p++;
	}
}


/*
********************************************************************************
*  Module Name:		jiscnv
*  Function Name:	�V�t�g�i�h�r���i�h�r�ϊ�
*  Input	:		�V�t�gJIS�R�[�h
*  Return	: 		JIS�R�[�h
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-20
********************************************************************************
*/
UNs	jiscnv(UNs d_cara)
{
	UNs	k;
	UNb	i,j;

//	i = d_cara >> 8;
	i = (UNb)(d_cara & 0x00ff);
	if( i >= 0xe0) {
		i -= 0x40;
	}
	if( i < 0x81 ) {
		i -= 0x81;
		i <<= 1;
		i |= 0x01;
	}
	else{
		i -= 0x81;
		i <<= 1;
	}
		i += 0x21;

//	j = d_cara;
	j = d_cara >> 8;
	if(j >= 0x80) {
		j --;
	}
	if(j >= 0x9e) {
		i ++;
		j -= 0x7d;
	}
	else{
		j -= 0x1f;
	}

	k = i;
	k <<= 8;
	k |= j;
	return (k);
}


/*
********************************************************************************
*  Module Name:		memset_word
*  Function Name:	�w��̈���w���ް��ɂ�ܰ�ޒP�ʂŐݒ�
*  Input	:		�i�[�ޯ̧���ڽ
*			:		�ݒ��ް�
*			:		���ށiܰ�ސ��j
*
*  Return	: 		�Ȃ�
*  Note		:	�w�肳�ꂽ�̈�̐擪����A�w���ް����w�萔���ݒ肷��
*
*  �� ��	:FIT)�c�[		ON:2002-06-26
********************************************************************************
*/
void	memset_word(UNs *dst_p, UNs dta, UNs size)
{

	while(size--) {
		*dst_p++ = dta;				//�̈�R�s�[
	}

}


/*
********************************************************************************
*  Module Name:		memset_long
*  Function Name:	�w��̈���w���ް��ɂ��ݸޒP�ʂŐݒ�
*  Input	:		�i�[�ޯ̧���ڽ
*			:		�ݒ��ް�
*			:		���ށi�ݸސ��j
*
*  Return	: 		�Ȃ�
*  Note		:	�w�肳�ꂽ�̈�̐擪����A�w���ް����w�萔���ݒ肷��
*
*  �� ��	:Shimamura		ON:2010-10-19
********************************************************************************
*/
void	memset_long(UNl *dst_p, UNl dta, UNs size)
{

	while(size--) {
		*dst_p++ = dta;				//�̈�R�s�[
	}

}


/*
********************************************************************************
*  Module Name:		memcpy_word
*  Function Name:	�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[
*  Input	:		�i�[���ޯ̧���ڽ
*			:		�i�[���ޯ̧���ڽ
*			:		���ށiܰ�ސ��j
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-26
********************************************************************************
*/
void	memcpy_word(UNs *dst_p, UNs *src_p, UNs size)
{

	while(size--) {
		*dst_p++ = *src_p++;			//�̈�R�s�[
	}
}


/*** END ***/
