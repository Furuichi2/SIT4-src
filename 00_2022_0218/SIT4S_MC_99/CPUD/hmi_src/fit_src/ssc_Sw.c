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
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		GMN_PAR035;						//��ݽ̧Ӱ��ݒ�~���� /* V01n */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR077;
/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	SWchg_ent(void);						//SW CHG �f�[�^ ENT
void	SWchg_move_ent(void);					//SW CHG�̈ړ� �ް�ENT
void	SWchg_mmon_ent(void);					//Ӱ��ݗp SW�ް� ENT

void	SWchg_bit_chk(void);					//�r�v�f�[�^���͎������I�����ۏ���
void	SWchg_disp_pv_any(void);				//SW�ް��@�����l �\��
void	SWchg_disp_pv(void);					//�r�v�b�g�f�f�[�^�\����������

void	SWchg_disp(void);						//�r�v�f�[�^���@�\��
void	SWchg_disp_gaibu(void);					//SW�ް����@�\��
void	SWchg_disp_one(UNi);					//1�r�v�f�[�^���@�\��
void	SWchg_set(UNi, UNs, UNs *);				//�r�v�L�����N�^�\������
void	SWchg_set_dan(UNi, UNs *);				//�r�v�L�����N�^�\������(�i���p)
void	SWchg_set_op(UNi, UNs *);				//�r�v�L�����N�^�\������(�I�t�Z�b�g���ߗp)
void	SWchg_dispset(UNi);						//�J�[�\�����]�\������
void	SWchg_dispset_dan(UNi);					//�J�[�\�����]�\������(�i���p)

void	Under_grph(void);						//���i�̃O���t�B�b�N�Z�b�g
void	WIN_grph(void);							//�E�C���h�E��ʏ�O���t�B�b�N�`��

void	SW16data_onset(UNs, UNi);				//�r�v�P�`�U�̔��]�w����s��
void	SW56_upcara_disp(UNs, UNs);				//�r�v�T�U��i�L�����N�^���r�v�̈�֊i�[
void	SW56_dncara_disp(UNs, UNs);				//SW56���i��׸���SW�̈�֊i�[
void	SW56dn_clear(UNs);						//SW��׸����ް��߰��ݸر

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNs *	SW56_Cam_Name_Tbl[69];
extern	const	UNs *	Camcsr_Name_Tbl1[16];

const	UNs	SW56_Up_Pos_Tbl[13]={
				0x002d,					//{2,13}	//00
				0x002d,					//{2,13}	//01
				0x008d,					//{8,13}	//02
				0x00ed,					//{14,13}	//03
				0x014d,					//{20,13}	//04
				0x01ad,					//{26,13}	//05
				0x020d,					//{32,13}	//06
				0x01ae,					//{26,14}	//07
				0x020e,					//{32,14}	//08
				0x002e,					//{2,14}	//09
				0x008e,					//{8,14}	//10
				0x00ee,					//{14,14}	//11
				0x014e					//{20,14}	//12
			};

const	UNs	SW56_Up_Pos_Tbl_color[15][2]={
			{  10,	416 },//00
			{  10,	416 },//01	SW1��i
			{ 100,	416 },//02	SW2��i
			{ 190,	416 },//03	SW3��i
			{ 280,	416 },//04	SW4��i
			{ 460,	416 },//05	SW5��i
			{ 550,	416 },//06	SW6��i
			{ 460,	448 },//07	SW5���i
			{ 550,	448 },//08	SW6���i
			{  10,	448 },//09	SW1���i
			{ 100,	448 },//10	SW2���i
			{ 190,	448 },//11	SW3���i
			{ 280,	448 },//12	SW4���i
			{ 370,	416 },//13	SW7��i			2014/09/09
			{ 370,	448 } //14	SW7���i			2014/09/09
			};

const	UNs	SPACE_ASCII_40[40]={
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 
			0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020
			};


/*
********************************************************************************
*  Module Name:		SWchg_ent
*  Function Name:	SW CHG �f�[�^ ENT
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	SWchg_ent(void)
{
	UNs		*bf_p, bit_d1, bit_d2, bit_d3, bit_d4;
	UNi		t_no;


	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//�r�v�f�[�^ �L��H
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWð��ٌ� �������Ƃ��͂r�v�����ł�߂�
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//�����׸� b1=���͏�������
		return;
	}

	bf_p = SW_buff[t_no].DATA_ADR;						//�ް��i�[���ڽ
	bit_d2 = bit_d1 = SW_buff[t_no].CHG_NO;				//�ް��i�[��̕ύX�ޯĈʒu
	bit_d4 = bit_d3 = *bf_p;

	bit_d2 = ~bit_d2;									//���]
	bit_d3 &= bit_d1;
	bit_d4 &= bit_d2;
	bit_d3 = ~bit_d3;									//���]
	bit_d3 &= bit_d1;
	bit_d4 |= bit_d3;
	*bf_p = bit_d4;										//�ύX��̃f�[�^���i�[����

	SWchg_bit_chk();									//�r�v�f�[�^���͎������I�����ۏ���
	ONOFF_FLG = 0;										//�����ł͎g�p���Ȃ����ߋ����N���A

	FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	bit_d1 = SW_buff[t_no].SAVE_NO;						//�i�[�׸�
	SVSW_CHG_FLG |= bit_d1;								//�f�[�^�`�F���W�t���O�Z�b�g

	SWchg_disp_one(t_no);								//1�r�v�f�[�^���@�\��

	WIN_grph();											//�E�C���h�E��ʏ�O���t�B�b�N�`��

	Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);	//��גP�ʕ\��
	Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��

}


/*
********************************************************************************
*  Module Name:		SWchg_move_ent
*  Function Name:	SW CHG�̈ړ� �ް�ENT
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-02
********************************************************************************
*/
void	SWchg_move_ent(void)
{
	UNs		t_no, c_no, c_max, sw_no;

	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//�r�v�f�[�^ �L��H
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWð��ٌ� �������Ƃ��͂r�v�����ł�߂�
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//�����׸� b1=���͏�������
		return;
	}

	SWchg_ent();										//SW CHG �f�[�^ ENT

	c_max = CSR_buff[CSR_TBL_POS_NOW].SW_MAX;
	if( c_max > 1 ){									//���ِ���1�ȏ�H
		c_no = SW_buff[t_no].CSR_NO;					//���̐ݒ�l�̑����鶰�ٔF���ԍ�
		sw_no = SW_buff[t_no].DSP_NO;					//���ٔF���ԍ����̈ړ�����

		do {
			sw_no ++;
			if( sw_no > c_max ){
				sw_no = 1;								//���ٔF���ԍ����̈ړ����� ��������
			}
			for( t_no=0 ;  t_no < SW_CNT ; t_no++ ){
				if(SW_buff[t_no].CSR_NO == c_no){		//���ٔF���ԍ�����v
					if(SW_buff[t_no].DSP_NO == sw_no){	//�ړ����ʂ���v
						SW_TBL_POS_NOW = t_no;			//���ʒu�̐ݒ�
						break;
					}
				}
			}
		} while( SW_buff[t_no].SUB_NO & BIT_F );		//SW�ް����g�p�H

		SWchg_ent();									//SW CHG �f�[�^ ENT
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_mmon_ent
*  Function Name:	Ӱ��ݗp SW�ް� ENT
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-31
********************************************************************************
*/
void	SWchg_mmon_ent(void)
{
	UNs		*bf_p, bit_d1;
	UNi		t_no;
	UNs		*degn, i, j, ww0;

	t_no = SW_TBL_POS_NOW;

	if( SW_CNT == 00 ||									//�r�v�f�[�^ �L��H
		CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 0 ||		//SWð��ٌ� �������Ƃ��͂r�v�����ł�߂�
		SW_buff[t_no].TOK_FLG & BIT_1 ){				//�����׸� b1=���͏�������
		return;
	}

/* V01n INS */
	if ( ((SEQ_024_SV & BIT_5) == BIT_5) && (CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 99))		// V01n(INS)
	{																						//Ӱ���3�i��
		j = SEQ_PAR_119 >> 12;
		if (j & 0x000F)
		{
			degn = &GMN_PAR035;
			for ( i=4 ; i>0 ; i--, j=j>>1, degn++)
			{
				if (j & BIT_0)
				{
					ww0 = *degn;
					break;
				}
			}
			if (ww0 != 0)
			{
				goto SWchg_mmon_et_EXT;
			}
		}
	}
/* END */

	bf_p = SW_buff[t_no].DATA_ADR;						//�ް��i�[���ڽ
	*bf_p = 0;											//�ύX��̃f�[�^���i�[����

//	FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	bit_d1 = SW_buff[t_no].SAVE_NO;						//�i�[�׸�
	SVSW_CHG_FLG |= bit_d1;								//�f�[�^�`�F���W�t���O�Z�b�g

	SWchg_disp_one(t_no);								//1�r�v�f�[�^���@�\��
	SV_csr_set();										//2014/09/25

	mmon_f_off(CSR_TBL_POS_NOW);						//��葬�x�ݒ�ر				2014/09/25

	Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);	//��גP�ʕ\��
//	Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��

SWchg_mmon_et_EXT:
	return;
}


/*
********************************************************************************
*  Module Name:		SWchg_bit_chk
*  Function Name:	�r�v�f�[�^���͎������I�����ۏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	SWchg_bit_chk(void)
{

	if(ONOFF_FLG != 0xff){
		ONOFF_FLG = 0;
	}
//SIT-S�Ȃ�
//	if( 00 == (SEQ_016_SV & BIT_7)){			//�ȈՋ@�\�I���H
//		if( SEQ_017_SV & 0xffc0 ){				//�G�W�F�N�^�P�i�p�{�G�W�F�N�^�Q�I��
//			SEQ_017_SV &= 0x003f;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_018_SV & 0xae3f ){
//			SEQ_018_SV &= 0x51c0;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_019_SV & 0xfeaf ){
//			SEQ_019_SV &= 0x0150;
//			ONOFF_FLG = 0xff;
//		}
//		if( SEQ_020_SV & 0x0957 ){
//			SEQ_020_SV &= 0xf6a8;
//			ONOFF_FLG = 0xff;
//		}
//	}
	if( 00 == (SEQ_016_SV & BIT_C)){			//���b�g�J�E���^�P�L��H
		if(SEQ_016_SV & BIT_E){					//���b�g�J�E���^�Q�I���H
			SEQ_016_SV &= ~BIT_E;
			ONOFF_FLG = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_pv_any
*  Function Name:	SW�ް��@�����l �\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	SWchg_disp_pv_any(void)
{
	UNi	cnt;
	UNs	*src_p;

	if( WINDOW_NO==4 || WINDOW_NO==11 ){			//�V�[�P���X�`�F�b�N���
	/* ���ݽ��ް��̐ݒ�	*/
		src_p = &SEQ_PAR_000;						//���ݽ�̈�̐擪���ڽ
		PV_SEQDT1_A91 = *(src_p + SV_SEQDT1_A91);	//���ݽ����ݒ�1
		PV_SEQDT2_A91 = *(src_p + SV_SEQDT2_A91);	//���ݽ����ݒ�2
		PV_SEQDT3_A91 = *(src_p + SV_SEQDT3_A91);	//���ݽ����ݒ�3
		PV_SEQDT4_A91 = *(src_p + SV_SEQDT4_A91);	//���ݽ����ݒ�4

//		cnt = (SW_CNT >> 1);					//1/2
		cnt = (SW_CNT >> 2);					//1/4
	}
	else{										//No
		cnt = 1;
	}
	while(cnt--){
		SWchg_disp_pv();						//�r�v�b�g�f�f�[�^�\����������
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_pv
*  Function Name:	�r�v�b�g�f�f�[�^�\����������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	SWchg_disp_pv(void)
{
	UNi		t_no;

	if(SW_CNT == 00) {									//�r�v�f�[�^ �L��H
		return;											//�Ȃ�
	}

	if(SW_DISP_CNT > SW_CNT ){							//�r�v�f�[�^�����l
		SW_DISP_CNT = 1;
	}
	t_no = (SW_DISP_CNT - 1);

	if( 00 == (SW_buff[t_no].SUB_NO & BIT_F) ) {		//�r�v�f�[�^���g�p�H
		if( SW_buff[t_no].TOK_FLG & BIT_1 ) {			//�r�v�\���L��H
			if(00 == (SW_buff[t_no].TOK_FLG & BIT_6)){	//��񂾂��\���H

				SWchg_disp_one(t_no);					//1�r�v�f�[�^���@�\��

				Lcd_cr(00, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
				if( SW_buff[t_no].TOK_FLG & BIT_0 ) {						//���]�\���L��H
					Lcd_cr(01, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��
				}
			}
		}
	}
	SW_DISP_CNT ++;										//����\���r�v�f�[�^�J�E���^
}


/*
********************************************************************************
*  Module Name:		SWchg_disp
*  Function Name:	�r�v�f�[�^���@�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�r�v�f�[�^�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	SWchg_disp(void)
{
	UNi		i, j;

	if(SW_CNT == 00) {									//�r�v�f�[�^ �L��H
		return;											//�Ȃ�
	}
	i = SW_CNT;
	j = 0;

//	if( SW_buff[j].SUB_NO & BIT_F ) {					//�r�v�f�[�^���g�p�H
//		j ++;											//�� ���ð���
//		i --;
//	}
	for( ; i > 0 ; i --,j++ ) {

		if( 00 == (SW_buff[j].SUB_NO & BIT_F) ) {			//�r�v�f�[�^���g�p�H

			SWchg_disp_one(j);								//1�r�v�f�[�^���@�\��

			if( SWCHG_DISP_ON_FLG == 0xff ) {
				Lcd_cr(00, SW_buff[j].XY_POS, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��

				if( SW_buff[j].TOK_FLG & BIT_0 ) {			//���]�\���L��H
					Lcd_cr(01, SW_buff[j].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_gaibu
*  Function Name:	SW�ް����@�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		SW�ް��̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-07-17
********************************************************************************
*/
void	SWchg_disp_gaibu(void)
{
	UNi		cnt, t_no;

	if(SW_CNT1 == 00) {									//�r�v�f�[�^ �L��H
		return;											//�Ȃ�
	}
	cnt = SW_CNT1;
	t_no = 0;

//	if( SW_buff[t_no].SUB_NO & BIT_F ) {				//�r�v�f�[�^���g�p�H
//		t_no ++;										//�� ���ð���
//		cnt --;
//	}
	for( ; cnt > 0 ; cnt--,t_no++ ) {

		if( 00 == (SW_buff[t_no].SUB_NO & BIT_F) ) {		//�r�v�f�[�^���g�p�H

			SWchg_disp_one(t_no);							//1�r�v�f�[�^���@�\��

			if( SWCHG_DISP_ON_FLG == 0xff ) {
				Lcd_cr(0, SW_buff[t_no].XY_POS, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��

				if( SW_buff[t_no].TOK_FLG & BIT_0 ) {						//���]�\���L��H
					Lcd_cr(1, SW_buff[t_no].XY_POS, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��
				}
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SWchg_disp_one
*  Function Name:	1�r�v�f�[�^���@�\��
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:		�w�肳�ꂽ�r�v�f�[�^�̏��ð��ق���ɕ\������
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	SWchg_disp_one(UNi T_no)
{
	UNs		*Src_p, i, j;

	i = SW_buff[T_no].SUB_NO;							//���ٰ�ݔԍ� �擾
	if( i & BIT_F ) {									//�r�v�f�[�^���g�p�H
		i = 1;
	}
//2014/09/04
////	else{												//No
////		i &= 0x0007;
////	}

	switch( i ) {
		default:
		case 0x0000:				//�ʏ�̂Q�m�b�`�r�v
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//�r�v�L�����N�^�\������
			SWchg_dispset(T_no);								//�J�[�\�����]�\������
#else
//2014/09/02			SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//�r�v�L�����N�^�\������
			SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�\������
#endif
			break;

		case 0x0001:				//�d�l������ʗp�x�[�X�L�����N�^�̔��]�I��
			if(GAMEN_NO != 18) {						//�f�[�^�ݒ�I���Ŕ��]���Ă��܂�
				SWchg_dispset(T_no);					//�J�[�\�����]�\������
			}
			break;

		case 0x0002:				//�i����ʕJ���̃V�[�P���X�o�b�N����
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_set_dan(T_no, &LCD_WORK1[0][0][0]);			//�r�v�L�����N�^�\������(�i���p)
			SWchg_dispset_dan(T_no);					//�J�[�\�����]�\������(�i���p)
#else
			SWchg_set_dan_color(T_no, LCD_VBASE);			//�r�v�L�����N�^�\������(�i���p)	//V05a
#endif
			break;

		case 0x0003:				//�J�����̔ėp�o�͔��]����
			SWchg_dispset(T_no);						//�J�[�\�����]�\������
			break;

		case 0x0004:				//�f�[�^�ݒ�i���^�j��ʑI��\������
			Src_p = SW_buff[T_no].KAN_ADR;							//�֘A���ڽ
			i = SW_buff[T_no].KAN_NO;								//�֘A�޲�

			if( *Src_p & i ) {										//�I��L��H
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//�r�v�L�����N�^�\������
				SWchg_dispset(T_no);								//�J�[�\�����]�\������
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//�r�v�L�����N�^�\������
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�\������
#endif
			}
			else{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, 0x0000, &LCD_WORK1[0][0][0]);				//�r�v�L�����N�^�\������
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//�r�v�L�����N�^�\������
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�\������
#endif
			}
			break;

		case 0x0005:				//�I�t�Z�b�g����&�׏d�\�����b�Z�[�W�\��
			SWchg_set_op(T_no, &LCD_WORK1[0][0][0]);				//�r�v�L�����N�^�\������(�I�t�Z�b�g���ߗp)
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			SWchg_dispset(T_no);						//�J�[�\�����]�\������
#endif
			break;
//		case 0x0006:				//��^����߂U�I��		SIT-S�ł́A�@�\�Ȃ�
//			break;

		case 0x0006:				//Ӱ��ݐݒ�@��~����
			Src_p = SW_buff[T_no].DATA_ADR;							//�ް��i�[���ڽ
			if( *Src_p == 00 ) {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				SWchg_set(T_no, SW_buff[T_no].CARA_NO, &LCD_WORK1[0][0][0]);	//�r�v�L�����N�^�\������
#else
//2014/09/02				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE);	//�r�v�L�����N�^�\������
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�\������
#endif
			}
			break;

		case 7:						//�i�p�̒P��			2014/09/02
			if ((SEQ_PAR_151 & BIT_11)==0) {				//���Ԑi�p�@�\
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 1);	//�r�v OFF�L�����N�^�\������
			}
			else {
				SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�\������
			}
			break;

		case 8:						//���[�^���J���A�G�W�F�N�^�A�~�X�t�H�[�h�̍s���u�q�v�\��		//2014/09/04
			if (GMN_PAR077 != 0) {
				Src_p = SW_buff[T_no].DATA_ADR;							//�ް��i�[���ڽ
				j = SW_buff[T_no].CHG_NO;								//�ް��i�[��̕ύX�ޯĈʒu
				if(*Src_p & j) {										//�n�m��ԁH
					SWchg_set_color(T_no, SW_buff[T_no].CARA_NO, LCD_VBASE, 0);	//�r�v�L�����N�^�u�q�v�\������
					SV_csr_set();
				}
			}
			break;


	}
}


/*
********************************************************************************
*  Module Name:		SWchg_set
*  Function Name:	�r�v�L�����N�^�\������
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*					�\���p��׸��ԍ�
*					�i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
void	SWchg_set(UNi T_no, UNs c_no, UNs *Dst_p)
{
	UNs		i, j, *buff_p, *g_p;

//	i = SW_buff[T_no].CARA_NO;						//�\���p��׸��ԍ�
	i = c_no;										//�\���p��׸��ԍ�
	i *= 10;										//��L�����N�^�̃O���[�v�͑S�p�P�O�����Ƃ���̂łQ�O�{

	buff_p = SW_buff[T_no].DATA_ADR;				//�ް��i�[���ڽ
	j = SW_buff[T_no].CHG_NO;						//�ް��i�[��̕ύX�ޯĈʒu
	if(*buff_p & j) {								//�n�m��ԁH
		i += 5;										//�n�m�̎��͑S�p�S���ɗL��̂�
	}

	g_p = mess_adr_shr( 10 );								//���b�Z�[�W��ʃL�����N�^�A�h���X����
	g_p += i;												//���b�Z�[�W��ʃL�����N�^�A�h���X�Z�o
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, 0x00);	//�����\���p�������ށ��ޯĕϊ�

}


/*
********************************************************************************
*  Module Name:		SWchg_set_dan
*  Function Name:	�r�v�L�����N�^�\������(�i���p)
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*					�i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-24
********************************************************************************
*/
void	SWchg_set_dan(UNi T_no, UNs *Dst_p)
{
	UNs		i, j, k, *buff_p, *g_p;


	i = SW_buff[T_no].CARA_NO;						//�\���p��׸��ԍ�
	i *= 10;										//��L�����N�^�̃O���[�v�͑S�p�P�O�����Ƃ���̂łQ�O�{

	buff_p = SW_buff[T_no].DATA_ADR;				//�ް��i�[���ڽ
	j = SW_buff[T_no].CHG_NO;						//�ް��i�[��̕ύX�ޯĈʒu
	k = *buff_p;									//�K�v�ȃr�b�g�����𒊏o
	k &= j;

	if(k==0 || k==j ) {								//�O���X�y�[�X || �R���X�y�[�X
		i = 0;
	}
	else{
		j &= 0x00aa;
		if( k & j) {
			i += 5;									//�n�m�̎��͑S�p�S���ɗL��̂�
		}
	}
	g_p = mess_adr_shr( 10 );								//���b�Z�[�W��ʃL�����N�^�A�h���X����
	g_p += i;												//���b�Z�[�W��ʃL�����N�^�A�h���X�Z�o
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, 0x00);	//�����\���p�������ށ��ޯĕϊ�

}


/*
********************************************************************************
*  Module Name:		SWchg_set_op
*  Function Name:	�r�v�L�����N�^�\������(�I�t�Z�b�g���ߗp)
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*					�i�[�ޯ̧���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-24
********************************************************************************
*/
void	SWchg_set_op(UNi T_no, UNs *Dst_p)
{
	UNs		i, *g_p, *buff_p;
	UNi		flg;
	UNs		len, col;
	UNl		adr;
	UNs		*hrom;

	buff_p = SW_buff[T_no].DATA_ADR;				//�ް��i�[���ڽ
	i = *buff_p;									//��׸��ԍ�
	if(i == 0) {
		flg = 0;									//����\��
	}
	else{
		flg = 0xff;									//���]�\��
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	i *= 20;										//��L�����N�^�̃O���[�v�͑S�p�Q�O�����Ƃ���̂łS�O�{
	g_p = mess_adr_shr( 13 );								//���b�Z�[�W��ʃL�����N�^�A�h���X����
	g_p += i;												//���b�Z�[�W��ʃL�����N�^�A�h���X�Z�o
	disp_moji_s(SW_buff[T_no].XY_POS, g_p, Dst_p, flg);		//�����\���p�������ށ��ޯĕϊ�
#else
	adr = SPE_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SPE_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	hrom = (UNs *)adr;
	len = *hrom++;
	len >>= 8;
	if ( i == 0 ) {
		hrom = &SPACE_ASCII_40[0];
		col = SW_buff[T_no].B_COL1;					/* �w�i�F			*/
	}
	else {
		adr = SPE_TABLE_ADR + ((i-1) * CHAR_SPE_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (UNs *)adr;
		hrom++;
		col = SW_buff[T_no].B_COL2;					/* �w�i�F			*/
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
#endif
}


/*
********************************************************************************
*  Module Name:		SWchg_dispset
*  Function Name:	�J�[�\�����]�\������
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-23
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	SWchg_dispset(UNi T_no )
{
	UNs		j, *buff_p;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {								//�n�m���]����H
		/*** �܂��ʏ�̂n�e�e���	***/
		disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0x00 );		//�\���p�̈���w���ް��Őݒ�

		/***	�w�肪�n�m��Ԃ̎��͔��]������	***/
		buff_p = SW_buff[T_no].DATA_ADR;							//�ް��i�[���ڽ
		j = SW_buff[T_no].CHG_NO;									//�ް��i�[��̕ύX�ޯĈʒu

		if(*buff_p & j) {											//�n�m��ԁH
			disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0xff );	//�\���p�̈���w���ް��Őݒ�
		}
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	SWchg_dispset(UNi T_no )
{
	UNs		j, *buff_p;
	UNl		adr;
	UNs		*hrom, len;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {								//�n�m���]����H

		/*** �܂��ʏ�̂n�e�e���	***/
		adr =  SWL_TABLE_ADR + ((SW_buff[T_no].CARA_NO-1) * CHAR_SWL_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (UNs *)adr;
		len = *hrom++;
		len >>= 8;
		disp_moji_s_color(
			len,									/* ��׸��			*/
			SW_buff[T_no].X_POS,					/* ���o��X�ʒu		*/
			SW_buff[T_no].Y_POS,					/* ���o��Y�ʒu		*/
			SW_buff[T_no].C_COL,					/* �����F			*/
			SW_buff[T_no].B_COL1,					/* �w�i�F			*/
			SW_buff[T_no].SIZE,						/* ��������			*/
			hrom,									/* �����i�[���ڽ	*/
			LCD_VBASE								/* �\�����			*/
			);

		/***	�w�肪�n�m��Ԃ̎��͔��]������	***/
		buff_p = SW_buff[T_no].DATA_ADR;							//�ް��i�[���ڽ
		j = SW_buff[T_no].CHG_NO;									//�ް��i�[��̕ύX�ޯĈʒu

		if(*buff_p & j) {											//�n�m��ԁH
			hrom += (8/2);
			disp_moji_s_color(
				len,									/* ��׸��			*/
				SW_buff[T_no].X_POS,					/* ���o��X�ʒu		*/
				SW_buff[T_no].Y_POS,					/* ���o��Y�ʒu		*/
				SW_buff[T_no].C_COL,					/* �����F			*/
				SW_buff[T_no].B_COL2,					/* �w�i�F			*/
				SW_buff[T_no].SIZE,						/* ��������			*/
				hrom,									/* �����i�[���ڽ	*/
				LCD_VBASE								/* �\�����			*/
				);
		}

		disp_moji_s_rif (
			len,									/* ��׸��			*/
			SW_buff[T_no].X_POS,					/* ���o��X�ʒu		*/
			SW_buff[T_no].Y_POS,					/* ���o��Y�ʒu		*/
			SW_buff[T_no].SIZE						/* ��������			*/
			);
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SWchg_dispset_dan
*  Function Name:	�J�[�\�����]�\������(�i���p)
*  Input	:		�r�v�f�[�^���ð��ق̔ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-24
********************************************************************************
*/
void	SWchg_dispset_dan(UNi T_no )
{
	UNs		i, j, *buff_p;

	if(SW_buff[T_no].TOK_FLG & BIT_0) {									//�n�m���]����H
		/*** �܂��ʏ�̂n�e�e���	***/
		disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0x00 );	//�\���p�̈���w���ް��Őݒ�

		/***	�w�肪�n�m��Ԃ̎��͔��]������	***/
		buff_p = SW_buff[T_no].DATA_ADR;								//�ް��i�[���ڽ
		j = SW_buff[T_no].CHG_NO;										//�ް��i�[��̕ύX�ޯĈʒu
		i = *buff_p;													//�K�v�ȃr�b�g�����𒊏o

		i &= j;															//�s�K�v�ȃr�b�g���}�X�N����B
		if( i != j ) {													//�����̃r�b�g�������Ă����甽�]���Ȃ�
			j &= 0x00aa;												//���]�\���r�b�g���쐬�i�Q�r�b�g�̍������n�m�\���j
			if( i & j) {												//�n�m��ԁH
				disp_memset(SW_buff[T_no].XY_POS, &LCD_WORK2[0][0][0], 0xff );	//�\���p�̈���w���ް��Őݒ�
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Under_grph
*  Function Name:	���i�̃O���t�B�b�N�Z�b�g
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-24
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	Under_grph(void)
{
	UNs		*Dst_p, dot_d;
	UNi		cnt;

	Dst_p = &LCD_WORK1[12][15][2];				//���i�̱��ްײ݂̱��ڽ�Z�o(12�s��15�ޯĖڂ�2�޲Ė�)
	dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
	cnt = (40-4);
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}
	*Dst_p |= 0x0080;							//�Ō�̂P�h�b�g

	//���x�ݒ蕔���̉���
	Dst_p = &LCD_WORK1[13][15][26];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s��15�ޯĖڂ�26�޲Ė�)
	dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
	cnt = 12;
	while(cnt--) {
		*Dst_p++ |= dot_d;
	}

	//���i�̏c���C���P
	Dst_p = &LCD_WORK1[13][0][2];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�2�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C���Q
	Dst_p = &LCD_WORK1[13][0][8];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�8�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C���R
	Dst_p = &LCD_WORK1[13][0][14];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�14�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C��4
	Dst_p = &LCD_WORK1[13][0][20];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�20�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C��5
	Dst_p = &LCD_WORK1[13][0][26];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�26�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C��7
	Dst_p = &LCD_WORK1[13][0][38];				//���i�̱��ްײ݂̱��ڽ�Z�o(13�s�ڂ�38�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 32;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//���i�̏c���C���W����
	Dst_p = &LCD_WORK1[14][0][32];				//���i�̱��ްײ݂̱��ڽ�Z�o(14�s�ڂ�32�޲Ė�)
	dot_d = 0x0080;								//�h�b�g�p�^�[���Z�b�g
	cnt = 16;
	while(cnt--) {
		*Dst_p |= dot_d;
		Dst_p += E_next_dot;					//1�����̎�dot�ʒu��
	}

	//��ʐ擪���p�P�O�������̔��]
	disp_memset(0x2800, &LCD_WORK2[0][0][0], 0xff );	//0�s��0���ڂ���10����

}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
const	UNs	UNDER_GRAP_TBL[8][4] = {
		{   0, 416,  91,  64 },
		{  91, 416,  91,  64 },
		{ 182, 416,  91,  64 },
		{ 273, 416,  91,  64 },
		{ 364, 416,  92,  64 },
		{ 456, 416, 184,  32 },
		{ 456, 448,  92,  32 },
		{ 548, 448,  92,  32 }
		};

void	Under_grph(void)
{
	UNs		k, i, xdot, ydot;

	for (i=0; i<8; i++)
	{
		xdot = UNDER_GRAP_TBL[i][0];
		ydot = UNDER_GRAP_TBL[i][1];

		//�c��
		k = UNDER_GRAP_TBL[i][3];;							// �x����
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			ydot++;
		}
		//����
		k = UNDER_GRAP_TBL[i][2];;							// �x����
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			xdot++;
		}
		//�c��
		k = UNDER_GRAP_TBL[i][3];;							// �x����
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			ydot--;
		}
		//����
		k = UNDER_GRAP_TBL[i][2];;							// �x����
		while(k--) {
			LCD_VRAM[ydot][xdot] = 0;
			LCD_VBASE[ydot][xdot] = 0;
			xdot--;
		}
	}
}
#endif

/*
********************************************************************************
*  Module Name:		WIN_grph(��:WIN_GRPH_WRITE)
*  Function Name:	�E�C���h�E��ʏ�O���t�B�b�N�`��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	WIN_grph(void)
{
	UNs		*Dst_p, dot_d;
	UNi		cnt;

	if(WINDOW_NO == 5 || WINDOW_NO == 19){

		Dst_p = &LCD_WORK1[6][0][0];				//����ʃE�C���h�E�̏�i�̘g������
		dot_d = 0x00ff;								//�h�b�g�p�^�[���Z�b�g
		cnt = 40;
		while(cnt--) {
			*Dst_p++ = dot_d;
		}
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	WIN_grph(void)
{
	UNs		i, xpos, ypos;

	if(WINDOW_NO == 5 || WINDOW_NO == 19 || WINDOW_NO == 20){
		for (i=0, xpos=0, ypos=PanelHeight-WindowHeight; i<PanelWidth; i++, xpos++)	/* LINE �ް��쐬		*/
		{
			LCD_VBASE[ypos][xpos] = 0;
			LCD_VRAM[ypos][xpos] = 0;
		}
	}
	else if( (6 <= WINDOW_NO) && (WINDOW_NO <= 9) ) {
		for (i=0, xpos=0, ypos=PanelHeight-WindowHeight; i<PanelDANWidth; i++, xpos++)	/* LINE �ް��쐬		*/
		{
			LCD_VBASE[ypos][xpos] = 0;
			LCD_VRAM[ypos][xpos] = 0;
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SW16data_onset
*  Function Name:	�r�v�P�`�U�̔��]�w����s��
*  Input	:		������ް��̎w��
*					SW�ʒu�F1=SW1,2=SW2,3=SW3,4=SW4,
*							5=SW5��,6=SW6��,7=SW5��,8=SW6��
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-28
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
typedef struct {
	UNs	*ADDR;			//�ް��i�[���ڽ
	UNi	CNT1;
	UNi	CNT2;
	} SW14_TBL_TDEF;

const	SW14_TBL_TDEF	SW14data_Pos_Tbl[9] = {
				{&LCD_WORK2[13][0][2], 06, 32},			//00[SW1]
				{&LCD_WORK2[13][0][2], 06, 32},			//01[SW1]
				{&LCD_WORK2[13][0][8], 06, 32},			//02[SW2]
				{&LCD_WORK2[13][0][14], 06, 32},		//03[SW3]
				{&LCD_WORK2[13][0][20], 06, 32},		//04[SW4]
				{&LCD_WORK2[13][0][26], 06, 15},		//05[SW5��]
				{&LCD_WORK2[13][0][32], 06, 15},		//06[SW6��]
//				{&LCD_WORK2[13][0][26], 06, 16},		//05[SW5��]
//				{&LCD_WORK2[13][0][32], 06, 16},		//06[SW6��]
				{&LCD_WORK2[14][0][26], 06, 16},		//07[SW5��]
				{&LCD_WORK2[14][0][32], 06, 16} };		//08[SW6��]

void	SW16data_onset(UNs d_ptn, UNi sw_no)
{
	UNs	*bf_p, *dst_p;
	UNi	cnt1, cnt2, i;

	bf_p = SW14data_Pos_Tbl[sw_no].ADDR;				//LCD�p�ޯ̧����ڽ
	cnt1 = SW14data_Pos_Tbl[sw_no].CNT1;				//����
	cnt2 = SW14data_Pos_Tbl[sw_no].CNT2;				//����

	for( ; cnt2 > 0 ; cnt2--) {
		dst_p = bf_p;
		i = cnt1;
		if( sw_no != 06) {							//�r�v�U�N���A�H
			i--;									//�ŏ��̃��[�h�͔��]����Əc���������邩��΍�
			*dst_p++ = d_ptn & 0x007f;
		}
		while(i--){
			*dst_p++ = d_ptn & 0x00ff;
		}
		bf_p += E_next_dot;							//1�����̎�dot�ʒu��
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/		//V01y
////		{   0, 416,  91,  64 },
////		{  91, 416,  91,  64 },
////		{ 182, 416,  91,  64 },
////		{ 273, 416,  91,  64 },
////		{ 364, 416,  92,  64 },
////		{ 456, 416, 184,  32 },
////		{ 456, 448,  92,  32 },
////		{ 548, 448,  92,  32 }
typedef struct {
	UNs	stat_xdot;			// x�J�n�ʒu
	UNs	stat_ydot;			// y�J�n�ʒu
	UNs	leng_xdot;			// x����
	UNs	leng_ydot;			// y����
	UNs	back_col;			// ���]�F
	} SW14_TBL_TDEF;

const	SW14_TBL_TDEF	SW14data_Pos_Tbl[10] = {
				{ 01, 417,  90, 63, 11},					//00[SW1]
				{ 01, 417,  90, 63, 11},					//01[SW1]
				{ 92, 417,  90, 63, 11},					//02[SW2]
				{183, 417,  90, 63, 11},					//03[SW3]
				{274, 417,  90, 63, 11},					//04[SW4]
				{457, 417, 183, 31, 11},					//05[SW56��]
				{457, 417, 183, 31, 11},					//06[SW56��]
				{457, 449,  91, 31, 11},					//07[SW5��]
				{549, 449,  91, 31, 11},					//08[SW6��]
				{365, 417,  91, 63, 11}						//09[SW7]	V01z(�ǉ�)
		};

void	SW16data_onset(UNs d_ptn, UNi sw_no)
{
	UNs	dx, dy;
	UNs	lx, ly, col;

	dx = SW14data_Pos_Tbl[sw_no].stat_xdot;				// X���Ĉʒu
	dy = SW14data_Pos_Tbl[sw_no].stat_ydot;				// Y���Ĉʒu

	if ( d_ptn == 0 ) {
		col = GAMENn_HEAD.scr_col;						// �w�i�F
	}
	else {
		col = SW14data_Pos_Tbl[sw_no].back_col;			// �w�i�F
	}

	ly = SW14data_Pos_Tbl[sw_no].leng_ydot;				// Y����
	for ( ; ly>0; ly-- )
	{
		lx = SW14data_Pos_Tbl[sw_no].leng_xdot;			// X����
		for ( ; lx>0; lx-- )
		{
			if( LCD_VBASE[dy][dx] != 0 )					// dot�F�����H�i���͕����F�ƌ��߂����A���ȊO��w�i�F�Ƃ���j
			{
				LCD_VBASE[dy][dx] = col;				// �w�i�F�ύX
			}
			LCD_VRAM[dy][dx] = LCD_VBASE[dy][dx];		// �O�̂���VBASE�ɺ�߰
			dx++;
		}
		dx = SW14data_Pos_Tbl[sw_no].stat_xdot;				// X���Ĉʒu
		dy = dy + 1;										// Y���Ĉʒu
	}
}
#endif


/*
********************************************************************************
*  Module Name:		SW56_upcara_disp
*  Function Name:	�r�v�T�U��i�L�����N�^���r�v�̈�֊i�[
*  Input	:		SW56��i��׸�
*					�\���ʒu��ð��ٔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	SW56_upcara_disp(UNs cr_no, UNs p_no)
{
	UNi		s_no, up_flg;
	UNs		xy_no, *g_p, s_bf[3];


	if(cr_no == 00) {		//�T�U�̃L�����N�^�ԍ����O�̎��͏����Ȃ�
		return;
	}
	if(cr_no == 0xff) {		//�T�U�̃L�����N�^�ԍ����O�e�e�g�̎��̓X�y�[�X������
		cr_no = 0;
	}
	xy_no = SW56_Up_Pos_Tbl[p_no];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)

	up_flg = 00;
	if(cr_no < 0x80 ) {
		s_no = 0;								//�ʏ�
	}
	else if(cr_no < 0x9f) {
		s_no = 1;								//�J�����̑Ή�
	}
	else if(cr_no < 0xb5) {
		s_no = 2;								//�@�\�I�𖼏̑Ή�
	}
	else if(cr_no >= 0xc5) {
		s_no = 2;								//�@�\�I�𖼏̑Ή�
	}
	else {
		up_flg = 0xff;							//�@�\�I���̕����͂P�Q��ו\������
		s_no = 1;
	}

	switch(s_no) {
		case 0x0000:
			g_p = mess_adr_shr( 2 );						//���b�Z�[�W��ʃL�����N�^�A�h���X����
			g_p += cr_no*10;								//�Q�O�{
			xy_no |= (12 << 10);							//������
			disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�
			break;

		case 0x0001:
			g_p = SW56_Cam_Name_Tbl[cr_no - 0x80];
			if(up_flg == 0x00 ){
				s_bf[0] = 0x2020;								//�X�y�[�X��������
				s_bf[1] = 0x2020;								//�X�y�[�X��������
				xy_no |= (1 << 10);								//������
				disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//�����\���p�������ށ��ޯĕϊ�

				xy_no += 0x0010;							//�� ��
				xy_no &= 0x03ff;
				xy_no |= (8 << 10);							//������
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);	//�����\���p�������ށ��ޯĕϊ�
				xy_no += 0x0080;							//�� ��

				xy_no &= 0x03ff;
				xy_no |= (3 << 10);							//������
				disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//�����\���p�������ށ��ޯĕϊ�
			}
			else{											//�@�\�I���̕����͂P�Q��ו\������
				xy_no |= (12 << 10);						//������
				disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);	//�����\���p�������ށ��ޯĕϊ�
				xy_no += 0x00c0;							//�� ��
			}
			break;

		case 0x0002:			//���̔ԍ��̓x�[�X�̃L�����N�^�̂܂܂Ƃ���H
			break;
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	SW56_upcara_disp(UNs cr_no, UNs p_no)
{
	UNi		s_no, up_flg;
	UNs		xy_no, *g_p, s_bf[8];
	UNs		x_dot, y_dot, len;
	UNl		adr;
	UNs		*hrom;

	if(cr_no == 00) {		//�T�U�̃L�����N�^�ԍ����O�̎��͏����Ȃ�
		return;
	}
	if(cr_no == 0xff) {		//�T�U�̃L�����N�^�ԍ����O�e�e�g�̎��̓X�y�[�X������
		cr_no = 0;
	}
	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)

	up_flg = 00;
	if( (cr_no >= 256) && (cr_no <= 511) ) {	//V06c
		s_no = 0;								//�ʏ�
	}
	else if(cr_no < 0x80 ) {
		s_no = 0;								//�ʏ�
	}
	else if(cr_no < 0x9f) {
		s_no = 1;								//�J�����̑Ή�
	}
	else if(cr_no < 0xb5) {
		s_no = 2;								//�@�\�I�𖼏̑Ή�
	}
	else if(cr_no >= 0xc5) {
		s_no = 2;								//�@�\�I�𖼏̑Ή�
	}
	else {
		up_flg = 0xff;							//�@�\�I���̕����͂P�Q��ו\������
		s_no = 1;
	}

	switch(s_no) {
		case 0x0000:
			if(cr_no==0)
			{
				s_bf[0] = 0x2020;								//�X�y�[�X��������
				s_bf[1] = 0x2020;								//�X�y�[�X��������
				s_bf[2] = 0x2020;								//�X�y�[�X��������
				s_bf[3] = 0x2020;								//�X�y�[�X��������
				s_bf[4] = 0x2020;								//�X�y�[�X��������
				s_bf[5] = 0x2020;								//�X�y�[�X��������
				hrom = &s_bf[0];
			}
			else
			{
				adr =  S56U_TABLE_ADR + ((cr_no-1) * CHAR_S56U_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
			}
			len = 12;
			disp_moji_s_color(
				len,					/* ��׸��			*/
				x_dot,					/* ���o��X�ʒu		*/
				y_dot,					/* ���o��Y�ʒu		*/
				0,						/* �����F			*/
				GAMENn_HEAD.scr_col,	/* �w�i�F			*/
				0x0202,					/* ��������			*/
				hrom,					/* �����i�[���ڽ	*/
				LCD_VBASE				/* �\�����			*/
				);
			disp_moji_s_rif(
				len,					/* ��׸��			*/
				x_dot,					/* ���o��X�ʒu		*/
				y_dot,					/* ���o��Y�ʒu		*/
				0x0202					/* ��������			*/
				);
			break;

		case 0x0001:
			g_p = SW56_Cam_Name_Tbl[cr_no - 0x80];
			if(up_flg == 0x00 ){
				s_bf[0] = 0x2020;								//�X�y�[�X��������
				len = 1;
				disp_moji_s_color(
					len,					/* ��׸��			*/
					x_dot,					/* ���o��X�ʒu		*/
					y_dot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					&s_bf[0],				/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
				len = 8;
				disp_moji_s_color(
					len,					/* ��׸��			*/
					x_dot+(8*2*1),			/* ���o��X�ʒu		*/
					y_dot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					g_p,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
				len = 9;
				disp_moji_s_rif(
					len,					/* ��׸��			*/
					x_dot,					/* ���o��X�ʒu		*/
					y_dot,					/* ���o��Y�ʒu		*/
					0x0202					/* ��������			*/
					);
			}
			else{											//�@�\�I���̕����͂P�Q��ו\������
				adr = CSR_TABLE_ADR + ((CSR_buff[CSR_TBL_POS_NOW].CARA_NO-1) * CHAR_CSR_SIZE);	// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
				hrom = (UNs *)adr;
				hrom++;
				len = 12;
				disp_moji_s_color(
					len,					/* ��׸��			*/
					x_dot,					/* ���o��X�ʒu		*/
					y_dot,					/* ���o��Y�ʒu		*/
					0,						/* �����F			*/
					GAMENn_HEAD.scr_col,	/* �w�i�F			*/
					0x0202,					/* ��������			*/
					hrom,					/* �����i�[���ڽ	*/
					LCD_VBASE				/* �\�����			*/
					);
				disp_moji_s_rif(
					len,					/* ��׸��			*/
					x_dot,					/* ���o��X�ʒu		*/
					y_dot,					/* ���o��Y�ʒu		*/
					0x0202					/* ��������			*/
					);
			}
			break;

		case 0x0002:			//���̔ԍ��̓x�[�X�̃L�����N�^�̂܂܂Ƃ���H
			break;
	}
	SW16data_onset(0xff, 5);			//V01y
}
#endif


/*
********************************************************************************
*  Module Name:		SW56_dncara_disp
*  Function Name:	SW56���i��׸���SW�̈�֊i�[
*  Input	:		SW56���i��׸�
*					�\���ʒu��ð��ٔԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
void	SW56_dncara_disp(UNs cr_no, UNs p_no)
{
	UNs		xy_no, *g_p, s_bf[3], i;

	if(cr_no == 00) {		//�T�U�̃L�����N�^�ԍ����O�̎��͏����Ȃ�
		return;
	}
	if(cr_no == 0xff) {		//�T�U�̃L�����N�^�ԍ����O�e�e�g�̎��̓X�y�[�X������
		cr_no = 0;
	}
	xy_no = SW56_Up_Pos_Tbl[p_no];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)

//	if(cr_no < 60) {							//�U�O���z������A�h���X�ύX
		g_p = mess_adr_shr( 7 );				//���b�Z�[�W��ʃL�����N�^�A�h���X����
//	}
//	else{
//		g_p = mess_adr_shr( 14 );				//���b�Z�[�W��ʃL�����N�^�A�h���X����
//		cr_no -= 60;
//	}
	g_p += cr_no*5;									//10�{
	xy_no |= (6 << 10);								//������
	disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//�����\���p�������ށ��ޯĕϊ�

	//�ėp�o�͂̔ėp�I�������^�؂��폜
	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;			//SW56��i��׸�
	if((p_no == 7) && (0x80 <= i) && (i < 0x90)){	//�r�v�T���H
		xy_no &= 0x03ff;
		g_p = Camcsr_Name_Tbl1[i - 0x80];
		if( 00 == (*g_p & BIT_0) ) {				//�J���o�͑I���H
			s_bf[0] = 0x2020;								//�X�y�[�X��������
			s_bf[1] = 0x2020;								//�X�y�[�X��������
			s_bf[2] = 0x2020;								//�X�y�[�X��������
			xy_no |= (6 << 10);								//������
			disp_moji_s(xy_no, &s_bf[0], &LCD_WORK1[0][0][0], 0x00);	//�����\���p�������ށ��ޯĕϊ�
		}
	}
}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
void	SW56_dncara_disp(UNs cr_no, UNs p_no)
{
	UNs		s_bf[4];
	UNs		x_dot, y_dot;
	UNl		adr;
	UNs		*hrom, len;
	UNs		*cam_p, bit;

	if(cr_no == 00) {		//�T�U�̃L�����N�^�ԍ����O�̎��͏����Ȃ�
		return;
	}
	if(cr_no == 0xff) {		//�T�U�̃L�����N�^�ԍ����O�e�e�g�̎��̓X�y�[�X������
		cr_no = 0;
	}

	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
	if (cr_no != 0)
	{
		if (p_no == 8) {										//SW6����
////			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//���[�^���J�����					2014/09/01
////				 (GAMEN_NO == 24) || (GAMEN_NO == 25) ||		//���[�^���J���i�p�t���
////				 (GAMEN_NO == 19) || (WINDOW_NO == 5) || 		//�G�W�F�N�^���
////				 (WINDOW_NO == 19) )							//�~�X�t�B�[�h���

////			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//���[�^���J�����					2016/03/24�i���Y�ݒ�win��Ɨ��j
////				 (GAMEN_NO == 24) || (GAMEN_NO == 25) ||		//���[�^���J���i�p�t���
////				 (GAMEN_NO == 19) ) 							//�G�W�F�N�^���

			if ( (GAMEN_NO == 21) || (GAMEN_NO == 22) ||		//���[�^���J�����					2016/11/15�i�G�W�F�N�^��ʂ�Ɨ��j
				 (GAMEN_NO == 24) || (GAMEN_NO == 25) )		//���[�^���J���i�p�t���
			{
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//���Ԑi�p�L��
						cr_no = 12;								//SW6�̕������u��/��ρv�̐ؑ�
					}
				}
////				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {		//2016/11/15�i1/3�Ɨ��j
				else if ( SV_FLG_CNT == 1 ) {
					if ( (GAMEN_NO == 21) || (GAMEN_NO == 24) ) {	//���[�^���J�����1
						cam_p = &SV_CAMNA0_C1;
					}
					else {
						cam_p = &SV_CAMNA8_C1;
					}
					cam_p += CSR_TBL_POS_NOW;
					if (*cam_p & BIT_0) {						//���[�U�[�J��
						if (GMN_PAR077 != 0) {					//�J��Ԃ��@�\�L��
							cr_no = 78;							//SW6�̕������u�w��v�̐ؑ�
						}
					}
				}
				else if ( SV_FLG_CNT == 3 ) {
					if (GMN_PAR077 != 0) {						//�J��Ԃ��@�\�L��
						cr_no = 78;								//SW6�̕������u�w��v�̐ؑ�
					}
				}
				else if ( SV_FLG_CNT == 4 ) {					//2016/11/15
					if (SEQ_022_SV & BIT_D) {					//�J���^�C�}�d�l�L��
						cr_no = 12;								//SW6�̕������u��/��ρv�̐ؑ�
					}
				}
			}
			else if ( GAMEN_NO == 19 ) {					//�G�W�F�N�^���					2016/11/15
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//���Ԑi�p�L��
						cr_no = 12;								//SW6�̕������u��/��ρv�̐ؑ�
					}
				}
				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
					if (GMN_PAR077 != 0) {						//�J��Ԃ��@�\�L��
						cr_no = 78;								//SW6�̕������u�w��v�̐ؑ�
					}
				}
			}
			else if ( (WINDOW_NO == 5) || (WINDOW_NO == 19) )	//���Y�ݒ�							2016/03/24
			{
				if ( (SV_FLG_CNT == 5) || (SV_FLG_CNT == 6) ) {
					if (SEQ_PAR_151 & BIT_11) {					//���Ԑi�p�L��
						cr_no = 12;								//SW6�̕������u��/��ρv�̐ؑ�
					}
				}
				else if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
					if (GMN_PAR077 != 0) {						//�J��Ԃ��@�\�L��
						if (SEQ_PAR_107 & BIT_2) {				//���Y���l�ݒ�L��
							cr_no = 78;							//SW6�̕������u�w��v�̐ؑ�
						}
					}
				}
			}
			else if ( (GAMEN_NO == 20) || (GAMEN_NO == 68) )	//�~�X�t�B�[�h���					2014/09/08
			{
				if ( (CSR_TBL_POS_NOW == 0) || (CSR_TBL_POS_NOW == 2) ||
					 (CSR_TBL_POS_NOW == 4) || (CSR_TBL_POS_NOW == 6) ) {
					if ( (SV_FLG_CNT == 1) || (SV_FLG_CNT == 3) ) {
						if (GMN_PAR077 != 0) {						//�J��Ԃ��@�\�L��
							cr_no = 78;								//SW6�̕������u�w��v�̐ؑ�
						}
					}
				}
			}
		}

		adr =  S56_TABLE_ADR + ((cr_no-1) * CHAR_S56_SIZE);	// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (UNs *)adr;
		hrom++;
		len = 5;
		disp_moji_s_color(
			len,					/* ��׸��			*/
			x_dot,					/* ���o��X�ʒu		*/
			y_dot,					/* ���o��Y�ʒu		*/
			0,						/* �����F			*/
			GAMENn_HEAD.scr_col,	/* �w�i�F			*/
			0x0202, 				/* ��������			*/
			hrom,					/* �����i�[���ڽ	*/
			LCD_VBASE				/* �\�����			*/
			);
	}
	else
	{
		s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
		len = 5;
		disp_moji_s_color(
			len,					/* ��׸��			*/
			x_dot,					/* ���o��X�ʒu		*/
			y_dot,					/* ���o��Y�ʒu		*/
			0,						/* �����F			*/
			GAMENn_HEAD.scr_col,	/* �w�i�F			*/
			0x0202, 				/* ��������			*/
			&s_bf[0],				/* �����i�[���ڽ	*/
			LCD_VBASE				/* �\�����			*/
			);
	}
}

void	SW56_dncara_disp_color(UNs cr_no, UNs p_no, UNs b_col)
{
	UNs		s_bf[4];
	UNs		x_dot, y_dot;
	UNl		adr;
	UNs		*hrom, len;

	if(cr_no == 00) {		//�T�U�̃L�����N�^�ԍ����O�̎��͏����Ȃ�
		return;
	}
	if(cr_no == 0xff) {		//�T�U�̃L�����N�^�ԍ����O�e�e�g�̎��̓X�y�[�X������
		cr_no = 0;
	}

	x_dot = SW56_Up_Pos_Tbl_color[p_no][0];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
	y_dot = SW56_Up_Pos_Tbl_color[p_no][1];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
	if (cr_no != 0)
	{
		adr =  S56_TABLE_ADR + ((cr_no-1) * CHAR_S56_SIZE);	// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		hrom = (UNs *)adr;
		hrom++;
		len = 5;
		disp_moji_s_color(
			len,					/* ��׸��			*/
			x_dot,					/* ���o��X�ʒu		*/
			y_dot,					/* ���o��Y�ʒu		*/
			0,						/* �����F			*/
			b_col,					/* �w�i�F			*/
			0x0202, 				/* ��������			*/
			hrom,					/* �����i�[���ڽ	*/
			LCD_VBASE				/* �\�����			*/
			);
	}
	else
	{
		s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
		len = 5;
		disp_moji_s_color(
			len,					/* ��׸��			*/
			x_dot,					/* ���o��X�ʒu		*/
			y_dot,					/* ���o��Y�ʒu		*/
			0,						/* �����F			*/
			GAMENn_HEAD.scr_col,	/* �w�i�F			*/
			0x0202, 				/* ��������			*/
			&s_bf[0],				/* �����i�[���ڽ	*/
			LCD_VBASE				/* �\�����			*/
			);
	}
}
#endif

/*
********************************************************************************
*  Module Name:		SW56dn_clear
*  Function Name:	SW��׸����ް��߰��ݸر
*  Input	:		�\���ʒu��ð��ٔԍ�-1
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-14
********************************************************************************
*/
void	SW56dn_clear(UNs p_no)
{
	if(p_no != 00){
		SW16data_onset(0x00, p_no + 1);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
	}
}



/*** END ***/
