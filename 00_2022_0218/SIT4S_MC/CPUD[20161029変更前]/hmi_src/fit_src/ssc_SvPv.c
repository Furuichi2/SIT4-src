/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			����/�ݒ�l/�����l/SW�ް��@�̏��ð��ي֌W								*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-22
*
*************************************************************************************/

#include "string.h"								//�W�����C�u����

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	U1b		LCD_VRAM[PanelHeight][PanelWidth];
extern	U1b		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		SH2_MAIN_CLK;
/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	SVdata_disp(void);						//�ݒ�l���@�\��
void	SVdata_disp_ent(UNs);					//�ݒ�r���̕��́A���ɖ߂�����
void	SV_csr_set(void);						//�ݒ�l�J�[�\��
void	SV_csr_reset(UNs);						//�ݒ�l�J�[�\��

void	PVdata_disp_all(void);					//�S�@�����l���@�\��
UNs		PVdata_disp(UNs, UNs );					//�����l���@�\��

void	SVPV_data_disp(UNl, void *, UNs, UNs);	//�ݒ�l�������l �\��
void	SVPV_data_NOdisp(void *);				//
void	Count_hosei_csr_on(UNs);				//�J�E���^�␳�̎����l���]����
void	SVSW_tbl_enzan(void);					//�r�u�r�v�e�[�u���A�h���X���Z
void	kyoutyou_set(UNs);						//���������ϊ�
void	Nextkno_Name_draw(UNs);					//
void	chk_kajyu_offset1(UNs, UNs);			//2015/05/19

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		SVdata_disp
*  Function Name:	�ݒ�l���@�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-22
********************************************************************************
*/
void	SVdata_disp(void)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;
	long	cnv_bf_s;

	if(SV_CNT == 00) {									//�ݒ�l�L��H
		return;											//�Ȃ�
	}
	i = SV_CNT;

	for( j = 0 ; i > 0 ; i--,j++ ) {
		if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {		//�ݒ�l�f�[�^���g�p�H

			cnv_bf = 0;									//�̈�N���A

			cnt = (SV_buff[j].BYTE_NO & 0x000f);		//�ް��i�[����޲Ē�
			if(cnt == 4){								//long(4byte) ?
				dst_lp = (UNl *)SV_buff[j].DATA_ADR;	//�ް��i�[���ڽ
				cnv_bf = *dst_lp;
				cnv_bf_s = (long)*dst_lp;				//2014/03/13
			}
			else{										//short(2byte)
				dst_p = SV_buff[j].DATA_ADR;			//�ް��i�[���ڽ
				cnv_bf = *dst_p;
				cnv_bf_s = (short)*dst_p;				//2014/03/13
			}

			flag = 0x02;								//BCD
			if( (SV_buff[j].TOK_FLG & BIT_0) == 0 ) {	//�����׸�b0 = BCD�ް��@�H
				flag = 0x01;							//HEX
			}

			if( SV_buff[j].TOK_FLG & BIT_7 ) {			//�����׸�b7 = ��ۻ��ڽ����@�H
				k = 0xff;
			}
			else{										//����
				k = 0x00;
			}

			if ( SV_buff[j].TOK_FLG & BIT_5 ) {			//��Βl�\���H		2014/03/13
				if ( cnv_bf_s < 0 ) {
					cnv_bf_s *= -1;
					cnv_bf = (UNs)cnv_bf_s;
				}
			}

			if ( SV_buff[j].TOK_FLG & BIT_6 ) {			//ASCII�\���H		2014/03/13
				flag = 0x04;							//ASCII
				k = 0xff;								//��ۻ��ڽ����
			}

			SVPV_data_disp(cnv_bf, &SV_buff[j], k, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
		}
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp_one
*  Function Name:	�ݒ�l���@�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l�̏��ð��ق���ɕ\������
*
*  �� ��	:A.Shimamura		ON:2014/09/05
********************************************************************************
*/
void	SVdata_disp_one(UNs t_no)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;
	long	cnv_bf_s;

	if(SV_CNT == 00) {									//�ݒ�l�L��H
		return;											//�Ȃ�
	}

	if( (SV_buff[t_no].SUB_NO & BIT_F) == 0 ) {		//�ݒ�l�f�[�^���g�p�H

		cnv_bf = 0;									//�̈�N���A

		cnt = (SV_buff[t_no].BYTE_NO & 0x000f);		//�ް��i�[����޲Ē�
		if(cnt == 4){								//long(4byte) ?
			dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;	//�ް��i�[���ڽ
			cnv_bf = *dst_lp;
			cnv_bf_s = (long)*dst_lp;				//2014/03/13
		}
		else{										//short(2byte)
			dst_p = SV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
			cnv_bf = *dst_p;
			cnv_bf_s = (short)*dst_p;				//2014/03/13
		}

		flag = 0x02;								//BCD
		if( (SV_buff[t_no].TOK_FLG & BIT_0) == 0 ) {	//�����׸�b0 = BCD�ް��@�H
			flag = 0x01;							//HEX
		}

		if( SV_buff[t_no].TOK_FLG & BIT_7 ) {			//�����׸�b7 = ��ۻ��ڽ����@�H
			k = 0xff;
		}
		else{										//����
			k = 0x00;
		}

		if ( SV_buff[t_no].TOK_FLG & BIT_5 ) {			//��Βl�\���H		2014/03/13
			if ( cnv_bf_s < 0 ) {
				cnv_bf_s *= -1;
				cnv_bf = (UNs)cnv_bf_s;
			}
		}

		if ( SV_buff[t_no].TOK_FLG & BIT_6 ) {			//ASCII�\���H		2014/03/13
			flag = 0x04;							//ASCII
			k = 0xff;								//��ۻ��ڽ����
		}

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], k, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp1
*  Function Name:	�ݒ�l���@�\�� (�ݒ�l���g�p�̏ꍇ���ް��F�œh�ׂ�)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l�̏��ð��ق���ɕ\������
*
*  �� ��	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void	SVdata_disp1(void)
{
	UNs		*dst_p, cnt, flag;
	UNl		*dst_lp, cnv_bf;
	UNi		i, j, k;

	if(SV_CNT == 00) {									//�ݒ�l�L��H
		return;											//�Ȃ�
	}
	i = SV_CNT;

	for( j = 0 ; i > 0 ; i--,j++ ) {
		if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {		//�ݒ�l�f�[�^���g�p�H

			cnv_bf = 0;									//�̈�N���A

			cnt = (SV_buff[j].BYTE_NO & 0x000f);		//�ް��i�[����޲Ē�
			if(cnt == 4){								//long(4byte) ?
				dst_lp = (UNl *)SV_buff[j].DATA_ADR;	//�ް��i�[���ڽ
				cnv_bf = *dst_lp;
			}
			else{										//short(2byte)
				dst_p = SV_buff[j].DATA_ADR;			//�ް��i�[���ڽ
				cnv_bf = *dst_p;
			}

			flag = 0x02;								//BCD
			if( (SV_buff[j].TOK_FLG & BIT_0) == 0 ) {	//�����׸�b0 = BCD�ް��@�H
				flag = 0x01;							//HEX
			}

			if( SV_buff[j].TOK_FLG & BIT_7 ) {			//�����׸�b7 = ��ۻ��ڽ����@�H
				k = 0xff;
			}
			else{										//����
				k = 0x00;
			}
			SVPV_data_disp(cnv_bf, &SV_buff[j], k, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
		}
		else {
			disp_moji_s_paint(
				SV_buff[j].M_LEN,		//���p����
				SV_buff[j].X_POS,		//X�n�_
				SV_buff[j].Y_POS,		//Y�n�_
				GAMENn_HEAD.scr_col,	//�h�ׂ��F
				SV_buff[j].SIZE,		//X/Y
				LCD_VRAM
				);
		}
	}
}


/*
********************************************************************************
*  Module Name:		SVdata_disp_ent
*  Function Name:	�ݒ�r���̕��́A���ɖ߂�����
*  Input	:		ð��ٔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
void	SVdata_disp_ent(UNs T_no)
{
	UNs		*dst_p, cnt, i, flag;
	UNl		*dst_lp, cnv_bf;

	if(SV_DATA_CHG != 00){									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
		SV_DATA_CHG = 0;									//�d�����ď��������Ȃ��悤��

		cnv_bf = 0;											//�̈�N���A

		cnt = (SV_buff[T_no].BYTE_NO & 0x000f);				//�ް��i�[����޲Ē�
		if(cnt == 4){										//long(4byte) ?
			dst_lp = (UNl *)SV_buff[T_no].DATA_ADR;			//�ް��i�[���ڽ
			cnv_bf = *dst_lp;
		}
		else{												//short(2byte)
			dst_p = SV_buff[T_no].DATA_ADR;					//�ް��i�[���ڽ
			cnv_bf = *dst_p;
		}

		flag = 0x02;									//BCD
		if( (SV_buff[T_no].TOK_FLG & BIT_0) == 0 ) {	//�����׸�b0 = BCD�ް��@�H
			flag = 0x01;								//HEX
		}

		if( SV_buff[T_no].TOK_FLG & BIT_7 ) {			//�����׸�b7 = ��ۻ��ڽ����@�H
			i = 0xff;
		}
		else{											//����
			i = 0x00;
		}
		SVPV_data_disp(cnv_bf, &SV_buff[T_no], i, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
	}

	SV_csr_reset(T_no);								//�ݒ�l�J�[�\��

}


/*
********************************************************************************
*  Module Name:		SV_csr_set
*  Function Name:	�ݒ�l�J�[�\���\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	SV_csr_set(void)
{
	UNs		xy_no, t_no, cnt;
	UNs		*Dst_p;

	if( SV_CNT != 00 &&										//�ݒ�l����
			SV_TBL_POS_NOW != 0xff ) {						//�ُ�R�[�h�łȂ�

		t_no = SV_TBL_POS_NOW;
		xy_no = SV_buff[t_no].XY_POS;						//���ق�X,Y��

		Dst_p = &LCD_WORK2[xy_no & 0x000f][15][(xy_no >> 4)&0x3f];	//�J�[�\���f�[�^���A�h���X���Z
		cnt = xy_no >> 10;									//������
		while(cnt --) {
			*Dst_p++ = 0x00ff;
		}
		Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);				//��גP�ʕ\��
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	SV_csr_set(void)
{
	UNs		t_no, xdot, ydot, size, leng, leng1;
	UNb		*Dst_p;

	if( SV_CNT != 00 &&										//�ݒ�l����
			SV_TBL_POS_NOW != 0xff ) {						//�ُ�R�[�h�łȂ�

		t_no = SV_TBL_POS_NOW;

		xdot = SV_buff[t_no].X_POS;
		ydot = SV_buff[t_no].Y_POS;
		size = SV_buff[t_no].SIZE;							// ���X�T�C�Y�A����Y�T�C�Y
		leng = SV_buff[t_no].M_LEN;

		ydot = ydot + ( (size & 0x0ff) * 16 ) - 1;			// �A���_�[�J�[�\���\���x�ʒu�Z�o
		leng = leng * 8 * (size >> 8);						// �J�[�\�������Z�o
		leng1 = leng;
		Dst_p = &LCD_VBASE[ydot][xdot];						// �\���u�q�`�l�Z�b�g
		while(leng --) {
			*Dst_p++ = SV_UNDER_COLOR;
		}
		Dst_p = &LCD_VRAM[ydot][xdot];						// �\���u�q�`�l�Z�b�g
		while(leng1 --) {
			*Dst_p++ = SV_UNDER_COLOR;
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SV_csr_reset
*  Function Name:	�ݒ�l�J�[�\������
*  Input	:		ð��ٔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	SV_csr_reset(UNs T_no)
{
	UNs		i, j, k;


	if(SV_CNT == 00 ||									//�ݒ�l�L��H
		T_no == 0xff ) {
		return;											//�Ȃ�
	}

	k = j = i = SV_buff[T_no].XY_POS;					//�ݒ�l�\����X,Y��
	i &= 0x000f;										//�s�̱��ڽ�@�Z�o
	j = ( j >> 4) & 0x003f;								//���̱��ڽ�@�Z�o
	k >>= 10;											//�������@�Z�o

	for( ; k > 0 ; k--, j++) {
		LCD_WORK2[i][15][j] &= 0x0000;					//�ر
	}

	Lcd_cr(01, SV_buff[T_no].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	SV_csr_reset(UNs T_no)
{
	UNs		xdot, ydot, size, leng, leng1;
	UNb		*Dst_p;

	if(SV_CNT == 00 ||									//�ݒ�l�L��H
		T_no == 0xff ) {
		return;											//�Ȃ�
	}

	xdot = SV_buff[T_no].X_POS;
	ydot = SV_buff[T_no].Y_POS;
	size = SV_buff[T_no].SIZE;							// ���X�T�C�Y�A����Y�T�C�Y
	leng = SV_buff[T_no].M_LEN;

	ydot = ydot + ( (size & 0x0ff) * 16 ) - 1;			// �A���_�[�J�[�\���\���x�ʒu�Z�o
	leng = leng * 8 * (size >> 8);						// �J�[�\�������Z�o
	leng1 = leng;
	Dst_p = &LCD_VBASE[ydot][xdot];						// �\���u�q�`�l�Z�b�g
	while(leng --) {
		*Dst_p++ = SV_buff[T_no].B_COL1;
	}
	Dst_p = &LCD_VRAM[ydot][xdot];						// �\���u�q�`�l�Z�b�g
	while(leng1 --) {
		*Dst_p++ = SV_buff[T_no].B_COL1;
	}
}
#endif


/*
********************************************************************************
*  Module Name:		PVdata_disp_all
*  Function Name:	�S�@�����l���@�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�S�����l�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	PVdata_disp_all(void)
{
	UNi		i, j;

	if ( (SEQ_PAR_341 & BIT_3) && (GAMEN_NO == 1) && (WINDOW_NO == 0) ) {		//2013/07/22
		//����PV�\���̍������Ή�
		for( j=1, i=PV_CNT ; i > 0 ; i-- ) {
			j = PVdata_disp( j, 0x00ff );					//�����l���@�\��

			if ( (i&0x03) == 0 ) {
				//�����������ʒu�\����گ��������
				SH2_MAIN_CLK ^= cBIT0;						//����p
				PV_CHANGE_hanten();							//�����ʒuGET
				PVdata_disp( 7, 0x00ff );					//�����ʒu�\��
			}
		}
	}
	else {
		for( j=1, i=PV_CNT ; i > 0 ; i-- ) {
			j = PVdata_disp( j, 0x00ff );					//�����l���@�\��
		}
	}

	PV_DISP_CNT = 1;									//�\�������l�J�E���^ ������

}


/*
********************************************************************************
*  Module Name:		PVdata_disp
*  Function Name:	�����l���@�\��
*  Input	:		�\��ð��ٔԍ�
*					�\�����(0�F�ʏ�^0xff�F�S�\��)
*
*  Return	: 		���\��ð��ٔԍ�
*  Note		:		�����l�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
UNs		PVdata_disp(UNs disp_no, UNs flag)
{
	UNs		*dst_p, cnt;
	UNl		*dst_lp, cnv_bf;
	UNi		t_no, j;
	UNs		xy_wk;
	UNs		c_wk[16];

	if(PV_CNT == 00) {									//�����l�L��H

		chk_kajyu_offset1(disp_no, 0x30);				//�̾�čZ���������������p�Ԋ|����۸���

		return;											//�Ȃ�
	}

	if( disp_no > PV_CNT ) {
		disp_no = 1;									//�\�� �ԍ�������
	}
	t_no = (disp_no - 1);									//�\�������l�e�[�u���ԍ�

	if ( (SVPV_LCD_FLG == 0) && (PV_buff[t_no].GRP_NO == 54) ) {	//�P�ʃf�[�^�H		For SIT4

		chk_kajyu_offset1(disp_no, 0x31);				//�̾�čZ���������������p�Ԋ|����۸���

		disp_no ++;										//���� �\�������l�J�E���^
		return(disp_no);
	}
	if ( (SVPV_LCD_FLG == 0) && (PV_buff[t_no].GRP_NO == 56) ) {	//�^�f�[�^�H		For SIT4

		chk_kajyu_offset1(disp_no, 0x32);				//�̾�čZ���������������p�Ԋ|����۸���

		disp_no ++;										//���� �\�������l�J�E���^
		return(disp_no);
	}

	if( (PV_buff[t_no].SUB_NO & BIT_F) ||					//�����l�f�[�^���g�p�H
		(flag == 0 && PV_buff[t_no].TOK_FLG & BIT_6) ) {	//�����׸�b6 = �P�ʁ��^�f�[�^�H

		chk_kajyu_offset1(disp_no, 0x33);				//�̾�čZ���������������p�Ԋ|����۸���

		disp_no ++;										//���� �\�������l�J�E���^
		return(disp_no);

//		if(PV_CNT == 1 || PVDATA_NON != 00){
//			return;
//		}
//		if( disp_no > PV_CNT ) {
//			disp_no = 1;								//�\�� �ԍ�������
//		}
//		t_no = (disp_no - 1);								//�\�������l�e�[�u���ԍ�
	}

	cnv_bf = 0;											//�̈�N���A

	cnt = (PV_buff[t_no].BYTE_NO & 0x000f);				//�ް��i�[����޲Ē�
	if(cnt == 4){										//long(4byte) ?
		dst_lp = (UNl *)PV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
		cnv_bf = *dst_lp;								//�f�[�^�Ǎ�
	}
	else{												//short(2byte)
		dst_p = PV_buff[t_no].DATA_ADR;					//�ް��i�[���ڽ
		cnv_bf = *dst_p;								//�f�[�^�Ǎ�
	}

	switch(PV_buff[t_no].SUB_NO & /*0x000f V01j*/0x001f) {				//���ٰ�ݔԍ� �擾
		default:
		case 0x00:				//���̂܂ܕ\��
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			break;

		case 0x01:				//�V�[�P���X�f�[�^	(?)
			cnv_bf = 0;										//�̈� 00 �N���A
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x02);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 0x02:				//�a�b�c�f�[�^
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x02);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			break;

		case 0x03:				//�Z���T�v���X�Ȃ�
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 0x04:				//�׏d�\��
			if( SEQ_PAR_385 & BIT_7) {								//�׏d���蒆(�\���Ȃ�)1:�׏d�\��
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//�ݒ�l�������l �\��
			}
			else {										//Yes
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x50);	//�ݒ�l�������l �\��
			}
			break;

		case 0x05:				//4�޲ĕ\��
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 0x06:				//ASCII�\��
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 0x07:				//����
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//�ݒ�l�������l �\��
			break;

		case 0x08:				//�X�g�b�s���O�^�C��
//			if( SEQ_PAR_084 & BIT_1) {					//�X�g�b�s���O�^�C�� �o���u�n�m���H
//				cnv_bf = 0xffff;						//��߰��@�̈�N���A
//				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x10);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
//			}
//			else {										//No
//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX �� BCD �ϊ�
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
//			}
			break;

		case 0x09:				//�Z���T�v���X�Ȃ�����
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x41);	//�ݒ�l�������l �\��
			break;

		case 0x0a:				//���YSPM�ݒ蒆
			if( SW14_ON1_FLG == 0x01) {					//�����Y�ݒ肪�����H
			}
			else {
//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX �� BCD �ϊ�
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			}
			break;

		case 11:				//�f�[�^��������(�|���́A���]�\��)
			if( cnv_bf & 0x80000000 ){								//�}�C�i�X�H
				cnv_bf *= -1;										//�\���f�[�^���Z�o

				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x81);	//�ݒ�l�������l �\��(��ۻ��ڽ����/���]�\��)
			}
			else{
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			}
			break;

		case 12:				//HEX�\��
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x101);	//HEX�\��(��ۻ��ڽ�Ȃ�)	shima
			break;

		/* V01 (INS) */
		case 13:				//�T�C�N���\��
			if (CMD_1CYCLE_DSP1) {
				/* ���̂܂ܕ\�� */
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			}
			else {
				/* �\������ */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(151);
				xy_wk = (6 << 10);			//�޲Đ�
				xy_wk |= (10 << 4);			//��
				xy_wk |= 6;					//�s
				Lcd_cr(00, xy_wk, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
#else
				disp_moji_s_paint(
					PV_buff[t_no].M_LEN,
					PV_buff[t_no].X_POS,
					PV_buff[t_no].Y_POS,
					GAMENn_HEAD.scr_col,
					PV_buff[t_no].SIZE,
					LCD_VRAM
					);
#endif
			}
			break;

		/* V01 (INS) */
		case 14:				//���Y�����^�����㍂���@�\��
			if (SEQ_PAR_200 & BIT_5) {						//�i�搡���H
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				xy_wk = (8 << 10);			//�޲Đ�
				xy_wk |= (11 << 4);			//��
				xy_wk |= 7;					//�s
				Lcd_cr(0, xy_wk, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
				xy_wk = (8 << 10);			//�޲Đ�
				xy_wk |= (3 << 4);			//��
				xy_wk |= 7;					//�s
				Lcd_cr(0, xy_wk, &LCD_WORK3[0][0][0]);		//��גP�ʕ\��
#else
				disp_moji_s_rif (				/* �u�����㍂�v�̕�����\�� */
					8, 
					160, 
					224, 
					0x0101
					);
				disp_moji_s_paint(				/* �u���Y�����v�̕��������� */
					8, 
					96, 
					224, 
					GAMENn_HEAD.scr_col,
					0x0101,
					LCD_VRAM
					);
#endif
				/* �u�����㍂�v���̂܂ܕ\�� */
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			}

			else {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				xy_wk = (8 << 10);			//�޲Đ�
				xy_wk |= (3 << 4);			//��
				xy_wk |= 7;					//�s
				Lcd_cr(0, xy_wk, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
				xy_wk = (8 << 10);			//�޲Đ�
				xy_wk |= (11 << 4);			//��
				xy_wk |= 7;					//�s
				Lcd_cr(0, xy_wk, &LCD_WORK3[0][0][0]);		//��גP�ʕ\��
#else
				disp_moji_s_paint (				/* �u�����㍂�v�̕��������� */
					8, 
					160, 
					224, 
					GAMENn_HEAD.scr_col,
					0x0101,
					LCD_VRAM
					);
				disp_moji_s_rif(				/* �u���Y�����v�̕�����\�� */
					8, 
					96, 
					224, 
					0x0101
					);
#endif
				if (CMD_DAIPOS_DSP1) {		//�\���H�i0=��\��  1=�\���j
					/* �u���Y�����v���̂܂ܕ\�� */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				}
				else {
					/* �u���Y�����v�����\������ */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
					CSR_CLS_FLG = 0xff;
					CSR_disp_cls(152);
					xy_wk = (12 << 10);			//�޲Đ�
					xy_wk |= (3 << 4);			//��
					xy_wk |= 8;					//�s
					Lcd_cr(00, xy_wk, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
#else
					disp_moji_s_paint(
						PV_buff[t_no].M_LEN,
						PV_buff[t_no].X_POS,
						PV_buff[t_no].Y_POS,
						GAMENn_HEAD.scr_col,
						PV_buff[t_no].SIZE,
						LCD_VRAM
						);
#endif
				}
			}
			break;

		case 15:				//ADC Window�̎��^No.�\���Z���T�v���X�Ȃ�	V01j
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x201);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 16:				//ADC Window�̖���ASCII�\��					V01j
			SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x204);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			break;

		case 17:				//Ӱ��ݕ␳(�׏d)�P��ASCII�\��				V01j
//V01m			if(SEQ_024_SV & BIT_4)		//�׏d�L��H
			if(SEQ_050_SV & BIT_9)		//�׏d�L��H
			{
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
			}
			break;

		case 18:				//�ײ�ގ����ҋ@�@�\  �ҋ@����ʒu �s�� �� --�\��
			if (SEQ_PAR_151 & cBIT9) {
				c_wk[0] = 0x2d2d;
				disp_moji_s_color (
					PV_buff[t_no].M_LEN, 
					PV_buff[t_no].X_POS, 
					PV_buff[t_no].Y_POS, 
					PV_buff[t_no].C_COL,
					PV_buff[t_no].B_COL1, 
					PV_buff[t_no].SIZE, 
					&c_wk[0], 
					LCD_VBASE
					);
				disp_moji_s_rif (
					PV_buff[t_no].M_LEN, 
					PV_buff[t_no].X_POS, 
					PV_buff[t_no].Y_POS, 
					PV_buff[t_no].SIZE
					);
			}
			else {
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
			}
			break;
	}

	chk_kajyu_offset1(disp_no, PV_buff[t_no].SUB_NO & 0x001f);	//�̾�čZ���������������p�Ԋ|����۸���


	disp_no ++;											//���� �\�������l�J�E���^

	return(disp_no);
}


/*
********************************************************************************
*  Module Name:		PVdata_disp1
*  Function Name:	�����l���@�\��
*  Input	:		�\��ð��ٔԍ�
*					�\�����(0�F�ʏ�^0xff�F�S�\��)
*
*  Return	: 		���\��ð��ٔԍ�
*  Note		:		�����l�̏��ð��ق���ɕ\������
*
*  �� ��	:A.Shimamura		ON:2014/08/20
********************************************************************************
*/
void		PVdata_disp1(UNs t_no, UNs flag)
{
	UNs		*dst_p, cnt;
	UNl		*dst_lp, cnv_bf;
	UNi		j;
	UNs		xy_wk;


	if( (PV_buff[t_no].SUB_NO & BIT_F) ||					//�����l�f�[�^���g�p�H
		(flag == 0 && PV_buff[t_no].TOK_FLG & BIT_6) ) {	//�����׸�b6 = �P�ʁ��^�f�[�^�H

		disp_moji_s_paint(
			PV_buff[t_no].M_LEN,		//���p����
			PV_buff[t_no].X_POS,		//X�n�_
			PV_buff[t_no].Y_POS,		//Y�n�_
			GAMENn_HEAD.scr_col,	//�h�ׂ��F
			PV_buff[t_no].SIZE,		//X/Y
			LCD_VRAM
			);
	}
	else {
		cnv_bf = 0;											//�̈�N���A

		cnt = (PV_buff[t_no].BYTE_NO & 0x000f);				//�ް��i�[����޲Ē�
		if(cnt == 4){										//long(4byte) ?
			dst_lp = (UNl *)PV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
			cnv_bf = *dst_lp;								//�f�[�^�Ǎ�
		}
		else{												//short(2byte)
			dst_p = PV_buff[t_no].DATA_ADR;					//�ް��i�[���ڽ
			cnv_bf = *dst_p;								//�f�[�^�Ǎ�
		}

		switch(PV_buff[t_no].SUB_NO & /*0x000f V01j*/0x001f) {				//���ٰ�ݔԍ� �擾
			default:
			case 0x00:				//���̂܂ܕ\��
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				break;
	
			case 0x01:				//�V�[�P���X�f�[�^	(?)
				cnv_bf = 0;										//�̈� 00 �N���A
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x02);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 0x02:				//�a�b�c�f�[�^
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x02);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				break;
	
			case 0x03:				//�Z���T�v���X�Ȃ�
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 0x04:				//�׏d�\��
				if( SEQ_PAR_385 & BIT_7) {								//�׏d���蒆(�\���Ȃ�)1:�׏d�\��
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//�ݒ�l�������l �\��
				}
				else {										//Yes
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x50);	//�ݒ�l�������l �\��
				}
				break;
	
			case 0x05:				//4�޲ĕ\��
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 0x06:				//ASCII�\��
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 0x07:				//����
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x41);	//�ݒ�l�������l �\��
				break;
	
			case 0x08:				//�X�g�b�s���O�^�C��
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 0x09:				//�Z���T�v���X�Ȃ�����
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x41);	//�ݒ�l�������l �\��
				break;
	
			case 0x0a:				//���YSPM�ݒ蒆
				if( SW14_ON1_FLG == 0x01) {					//�����Y�ݒ肪�����H
				}
				else {
	//				cnv_bf = HEX_BCD4(cnv_bf);				//HEX �� BCD �ϊ�
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				}
				break;
	
			case 11:				//�f�[�^��������(�|���́A���]�\��)
				if( cnv_bf & 0x80000000 ){								//�}�C�i�X�H
					cnv_bf *= -1;										//�\���f�[�^���Z�o
	
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x81);	//�ݒ�l�������l �\��(��ۻ��ڽ����/���]�\��)
				}
				else{
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				}
				break;
	
			case 12:				//HEX�\��
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x101);	//HEX�\��(��ۻ��ڽ�Ȃ�)	shima
				break;
	
			/* V01 (INS) */
			case 13:				//�T�C�N���\��
				if (CMD_1CYCLE_DSP1) {
					/* ���̂܂ܕ\�� */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				}
				else {
					/* �\������ */
					disp_moji_s_paint(
						PV_buff[t_no].M_LEN,
						PV_buff[t_no].X_POS,
						PV_buff[t_no].Y_POS,
						GAMENn_HEAD.scr_col,
						PV_buff[t_no].SIZE,
						LCD_VRAM
						);
				}
				break;
	
			/* V01 (INS) */
			case 14:				//���Y�����^�����㍂���@�\��
				if (SEQ_PAR_200 & BIT_5) {						//�i�搡���H
					disp_moji_s_rif (				/* �u�����㍂�v�̕�����\�� */
						8, 
						160, 
						224, 
						0x0101
						);
					disp_moji_s_paint(				/* �u���Y�����v�̕��������� */
						8, 
						96, 
						224, 
						GAMENn_HEAD.scr_col,
						0x0101,
						LCD_VRAM
						);
					/* �u�����㍂�v���̂܂ܕ\�� */
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
				}
	
				else {
					disp_moji_s_paint (				/* �u�����㍂�v�̕��������� */
						8, 
						160, 
						224, 
						GAMENn_HEAD.scr_col,
						0x0101,
						LCD_VRAM
						);
					disp_moji_s_rif(				/* �u���Y�����v�̕�����\�� */
						8, 
						96, 
						224, 
						0x0101
						);
					if (CMD_DAIPOS_DSP1) {		//�\���H�i0=��\��  1=�\���j
						/* �u���Y�����v���̂܂ܕ\�� */
						SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0, 0x01);	//�ݒ�l�������l �\��(��ۻ��ڽ����/����\��)
					}
					else {
						/* �u���Y�����v�����\������ */
						disp_moji_s_paint(
							PV_buff[t_no].M_LEN,
							PV_buff[t_no].X_POS,
							PV_buff[t_no].Y_POS,
							GAMENn_HEAD.scr_col,
							PV_buff[t_no].SIZE,
							LCD_VRAM
							);
					}
				}
				break;
	
			case 15:				//ADC Window�̎��^No.�\���Z���T�v���X�Ȃ�	V01j
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x201);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 16:				//ADC Window�̖���ASCII�\��					V01j
				SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x204);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				break;
	
			case 17:				//Ӱ��ݕ␳(�׏d)�P��ASCII�\��				V01j
				if(SEQ_050_SV & BIT_9)		//�׏d�L��H
				{
					SVPV_data_disp(cnv_bf, &PV_buff[t_no], 0xff, 0x04);	//�ݒ�l�������l �\��(��ۻ��ڽ�Ȃ�/����\��)
				}
				break;

		}
	}
}


/*
********************************************************************************
*  Module Name:		SVPV_data_disp
*  Function Name:	�ݒ�l�������l�k�b�c�\��
*  Input	:		�ް�(long)
*					���ð��ِ擪���ڽ
*					��ۻ��ڽ(00:����^ff�F�Ȃ�)
*					�t���O�FB0 = 1:HEX�ް�
*							B1 = 1:BCD�ް�
*							B2 = 1:ASCII�ް�
*							B4 = 1:��߰��\��
*							B6 = 0:�ʏ�\���^1:�����\��
*							B7 = 0:����\���^1:���]�\��
*							B8 = 1:HEX�\��	shima
*							B9 = 1:��ԏ��Dot��`��
*							B10= 1:���]�\�����w�i�ΐF			V06p
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-22
********************************************************************************
*/
void	SVPV_data_disp(UNl bcd_d, void *tbl_p, UNs flag, UNs flag_2)
{
	SV_TBL_TDEF	*t_p;
	UNi		i, j, k;
	UNs		c_wk[16], w_bf;
	UNb		wk[16], wk1[16], *byte_p;
	UNs		*dst_p, *src_p;

	t_p = tbl_p;
	memset(&wk[0], E_AS_SP, 16);					//�̈� ��߰� �ر

	if(flag_2 & BIT_1){								//B1 = 1:BCD�ް� ?
		BCD_ASCII(bcd_d, &wk[0]);					//BCD��ASCII �ϊ�
	}
	else if(flag_2 & BIT_2){						//B2 = 1:ASCII�ް� ?
		i = (t_p->XY_POS >> 10);					//
		i &= 0x000f;
		i ++;
		i >>= 1;
		dst_p = &c_wk[0];
		src_p = t_p->DATA_ADR;						//�ް��i�[���ڽ
		while(i--) {
			*dst_p++ = *src_p++;
		}
	}
	else if(flag_2 & BIT_4){						//B4 = 1:��߰��\�� ?
	}
	else if(flag_2 & BIT_8){						//B8 = 1:HEX�\�� ?	shima
		HEX_ASCII(bcd_d, &wk[0]);					//HEX��ASCII �ϊ�	shima
	}
	else{											//B0 = 1:HEX�ް� ?
		if( t_p->TOK_FLG & BIT_8 ) {				//�����׸�(B8=1:�l��1/10���ĕ\��)
			bcd_d /= 10;
		}
		else if(t_p->TOK_FLG & BIT_9){				//�����׸�(B9=1:mm-> mm/INCH�\��)
			bcd_d = cnv_mm_inch(bcd_d, 1);			//�P�ʐؑ�(mm��mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_10){				//�����׸�(B10=1:mm-> mm/INCH�\��)
			bcd_d = cnv_mi_mi(bcd_d);				//�P�ʐؑ�(mm/INCH��mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_11){				//�����׸�(B11=1:mm-> mm/INCH�\��)
			bcd_d = cnv_mm_inch(bcd_d, 2);			//�P�ʐؑ�(mm��mm/INCH)
		}
		else if(t_p->TOK_FLG & BIT_12){				//�����׸�(B12=1:mm/INCH-> mm/INCH�\��)		V01m
			bcd_d = cnv_mi_mi_sur(bcd_d);			//�P�ʐؑ�(mm/INCH��mm/INCH)	�ײ�ގ������ߗp
		}
		bcd_d = HEX_BCD4(bcd_d);					//HEX �� BCD �ϊ�
		BCD_ASCII(bcd_d, &wk[0]);					//BCD��ASCII �ϊ�
	}

	if(00 == (flag_2 & BIT_2)) {					//B2 = 1:ASCII�ް� ?
		j = i = (t_p->TEN_POS & 0x0007);				//�����_�̈ʒu�̎擾
		j = 8 - i;										//�ړ����̎Z�o
		byte_p = &wk[7];								//�ޯ̧�̍ŏI���ڽ�Z�o
		if( i != 00 ){									//�����_ ����H
			while(j--) {
				*(byte_p+1) = *byte_p;
				byte_p--;
			}
			wk[i] = E_AS_TEN;							//�h.�h�@ �mASCII���ށn�����_�̑}��
		}

		if( flag == 0x00 ) {							//�����׸�b7 = ��ۻ��ڽ����@�H
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
		}

		i = (t_p->XY_POS >> 10);						//BYTE -> WORD �ɕϊ�
		if( t_p->TOK_FLG & BIT_2 ) {					//�����׸�b2 = �S�p�w��@�H
			i >>= 1;
			k = i;
			for( j=0 ; i > 0 ; i--, j++ ){
				wk1[j] = wk[i-1];
			}
			Ascii_Sjis(k, &wk1[0], &c_wk[0]);			//ASCII -> S-JIS �ϊ�
		}
		else{
			for( j=0 ; i > 0 ; i--, j++ ){
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
		}
	}

	if(flag_2 & BIT_7){								//B7=0:����\���^1:���]�\��
		w_bf = 0xff;								//���]�\��
		if (flag_2 & BIT_10) {
			w_bf = 0x55;							//���]���̔w�i�͗ΐF
		}
	}
	else{
		w_bf = 0x00;								//����\��
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_moji_s(t_p->XY_POS, &c_wk[0], &LCD_WORK1[0][0][0], w_bf);	//�����\���p�������ށ��ޯĕϊ�
#else
	if (w_bf == 0) {
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			t_p->B_COL1, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
	else if (w_bf == 0x55) {				//V06p
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			COL_GREEN, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
	else {
		disp_moji_s_color (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->C_COL,
			t_p->B_COL2, 
			t_p->SIZE, 
			&c_wk[0], 
			LCD_VBASE
			);
	}
#endif


	w_bf = t_p->XY_POS;
	if( 12 == (w_bf & 0x000f) ) {					//�s�̎擾
		dst_p = &LCD_WORK1[12][15][2];				//���i�̱��ްײ݂̱��ڽ�Z�o(12�s��15�ޯĖڂ�2�޲Ė�)
		i = (40-4);
		while(i--) {
			*dst_p++ |= 0x00ff;
		}
		*dst_p |= 0x0080;							//�Ō�̂P�h�b�g
	}

//	if( WINDOW_NO != 0 && 6 == (w_bf & 0x000f) ) {	//�s�̎擾
//		i = (w_bf >> 4);							//
//		i &= 0x003f;
//		dst_p = &LCD_WORK1[6][0][i];				//����ʃE�C���h�E�̏�i�̘g������
//		i = (w_bf >> 10);							//
//		while(i--) {
//			*dst_p++ |= 0x00ff;
//		}
//	}

	if(flag_2 & BIT_6){								//B6 = 0:�ʏ�\���^1:�����\��
		kyoutyou_set(w_bf);							//���������ϊ�
	}

	if(flag_2 & BIT_9){								//B9 = 0:�ʏ�\���^1:�ŏ��DOT�ɕ`��	V01j
		Nextkno_Name_draw(w_bf);					//
	}

	if( SVPV_LCD_FLG == 00 ) {						//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Lcd_cr(00, w_bf, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
#else
		disp_moji_s_rif (
			t_p->M_LEN, 
			t_p->X_POS, 
			t_p->Y_POS, 
			t_p->SIZE
			);
#endif
	}

}


void	SVPV_data_NOdisp(void *tbl_p)
{
	SV_TBL_TDEF	*t_p;
	UNs		w_bf;
	t_p = tbl_p;
	w_bf = t_p->XY_POS;
	Lcd_cr(00, w_bf, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��

}


/*
********************************************************************************
*  Module Name:		Count_hosei_csr_on
*  Function Name:	�J�E���^�␳�̎����l���]����
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-29
********************************************************************************
*/
void	Count_hosei_csr_on(UNs xy_no)
{
	if(00 != xy_no){
		disp_memnot(xy_no, &LCD_WORK2[0][0][0]);	//�\���p�̈�̎w���ް��𔽓]
		Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);		//��גP�ʕ\��
	}
}


/*
********************************************************************************
*  Module Name:		SVSW_tbl_enzan
*  Function Name:	�r�u�r�v�e�[�u���A�h���X���Z
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
void	SVSW_tbl_enzan(void)
{
	UNs		i, j;

	CSR_TBL_POS_NOW = CSR_FLG_CNT - 1;							//�J�[�\���ԍ�����

	if( SV_CNT == 00 ) {										//�ݒ�l�Ȃ�
		SV_TBL_POS_NOW = 0xff;									//�ُ�R�[�h�Z�b�g
	}
	else {
		SV_TBL_POS_NOW = 0xff;									//�ُ�R�[�h�Z�b�g
		for( i = SV_CNT,j=0 ; i > 0 ; i--, j++) {
			if( (SV_buff[j].SUB_NO & BIT_F) == 0 ) {			//�ݒ�l�f�[�^���g�p�H
				if(SV_buff[j].CSR_NO == CSR_FLG_CNT &&			//���ٔF���ԍ�
					SV_buff[j].DSP_NO == SV_FLG_CNT ) {			//���ٔF���ԍ����̈ړ�����

					SV_TBL_POS_NOW = j;							//�ݒ�l�f�[�^�����I��
					break;
				}
			}
		}
	}

	if( SW_CNT == 00 ) {										//�r�v�f�[�^�Ȃ�
		SW_TBL_POS_NOW = 0xff;									//�ُ�R�[�h�Z�b�g
	}
	else {
		SW_TBL_POS_NOW = 0xff;									//�ُ�R�[�h�Z�b�g
		for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
			if(SW_buff[j].CSR_NO == CSR_FLG_CNT &&				//���ٔF���ԍ�
				SW_buff[j].DSP_NO == SW_FLG_CNT ) {				//���ٔF���ԍ����̈ړ�����

				SW_TBL_POS_NOW = j;								//�r�v�f�[�^�����I��
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		kyoutyou_set
*  Function Name:	���������ϊ�
*  Input	:		�\���ʒu���
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-18
********************************************************************************
*/
void	kyoutyou_set(UNs xy_no)
{
	UNi		i, j;
	UNs		*dst_p, *dst_p1, cy_flg, wk;

	i = xy_no & 0x000f;						//�s�̱��ڽ�@�Z�o
	j = ( xy_no >> 4) & 0x003f;				//���̱��ڽ�@�Z�o
	dst_p1 = &LCD_WORK1[i][0][j];			//LCD�\���̈�̱��ڽ�ݒ�

	for( i=16 ; i > 0 ; i-- ) {
		dst_p = dst_p1;
		cy_flg = 0;
		j = ( xy_no >> 10);					//�������@�Z�o
		while(j--){
			wk = *dst_p;
			if(wk & 0x0001){				//���̕����֔��f����邩�H
				wk >>= 1;
				wk |= cy_flg;
				cy_flg = 0x0080;
			}
			else{							//No
				wk >>= 1;
				wk |= cy_flg;
				cy_flg = 0x0000;
			}
			*dst_p++ |= wk;
		}
		dst_p1 += E_next_dot;				//1�����̎�dot�ʒu��
	}
}


/*
********************************************************************************
*  Module Name:		Nextkno_Name_draw
*  Function Name:	�ŏ��DOT�ɕ`��
*  Input	:		�\���ʒu���
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-06-01			V01j
********************************************************************************
*/
void	Nextkno_Name_draw(UNs xy_no)
{
	UNi		i, j, k;

	i = xy_no & 0x000f;						//�s
	j = ( xy_no >> 4) & 0x003f;				//��
	k = ( xy_no >> 10) & 0x003f;			//������

	for( ; k > 0 ; k--, j++ ) {
		LCD_WORK1[i][0][j] = 0xff;			//
	}
}


/*
********************************************************************************
*  Function Name:	�Ԋ|��
*
*  �� ��	:Shima		ON:2015-05-19
********************************************************************************
*/
void	chk_kajyu_offset1(UNs disp_no, UNs code)
{
	if (GAMEN_NO == 44) {
		if ( (disp_no >= 1) && (disp_no <= 3) ) {
			chk_kjofs_dat[disp_no-1] = code+1;
		}
	}
}


/*** END ***/
