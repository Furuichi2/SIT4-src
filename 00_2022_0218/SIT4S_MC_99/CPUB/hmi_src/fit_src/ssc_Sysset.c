/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�V�X�e���ݒ�̑��상�C������											*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-06-04
*
*************************************************************************************/

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_addr.h"							//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
/* �O���Q�ƕϐ���` -------------------------------------------------- */
/* �萔��` ---------------------------------------------------------- */
#define		E_MM		0x6d6d2020			//mm		����
#define		E_INCH		0x494e4348			//INCH

#define		E_TON		0x746f6e20			//ton		�d��
#define		E_KN		0x6b4e2020			//kN

#define		E_K			0x4b202020			//K			�d��
#define		E_PSI		0x50534920			//PSI
#define		E_MPA		0x4d506120			//MPa


/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	dsp_Sysset(void);						//�V�X�e���ݒ�̊Ǘ�
void	Sys_sel_dstg_mmon(void);				//�f�[�^�ݒ�[�����e�i���X���j�^]��
void	Sys_sel_dstg_ksel(void);				//�f�[�^�ݒ�[�@�\�I��]��
void	Sys_dsp_move(void);						//��ʂƊǗ��ð�ނ̈ړ�

void	CAR_mkssi_set(void);					//�P�ʐ؊��ް��i�[����

void	INI_data_set(void);						//�f�[�^������

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */



/*
********************************************************************************
*  Module Name:		dsp_Sysset
*  Function Name:	�V�X�e���ݒ�̊Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-04
********************************************************************************
*/
void	dsp_Sysset(void)
{

	switch(disp_stg_sel) {

		case E_ystg_init:		//���ѐݒ�[��{]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(�Ȃ�)
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
							break;
						case E_key_sw6:			//key code SW6
							Sys_dsp_move();						//��ʂƊǗ��ð�ނ̈ړ�
							break;
					}
					break;
			}
			break;

		case E_ystg_sys1:		//���ѐݒ�[�d�l�ݒ�1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					SWchg_ent();								//SW CHG �f�[�^ ENT
					ROTTO_chk();								//ۯĶ��� ���� ����
					CAR_mkssi_set();							//�P�ʐ؊��f�[�^�i�[����

					if(00 == (SEQ_016_SV & BIT_14)){			//ۯĶ���2�@����OFF��������Ȃ��H
						SWCHG_DISP_ON_FLG = 0x0FF;
						SWchg_disp();							//SW�ް����@�\��
						SWCHG_DISP_ON_FLG = 0;
					}
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_sys2;			//���ѐݒ�[�d�l�ݒ�2]��
							GAMEN_NO = 33;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_ystg_sys2:		//���ѐݒ�[�d�l�ݒ�2]
		case E_ystg_sys3:		//���ѐݒ�[�d�l�ݒ�3]
		case E_ystg_sys4:		//���ѐݒ�[�d�l�ݒ�4]
		case E_ystg_sys5:		//���ѐݒ�[�d�l�ݒ�5]
		case E_ystg_sys6:		//���ѐݒ�[�d�l�ݒ�6]
		case E_ystg_sys7:		//���ѐݒ�[�d�l�ݒ�7]
		case E_ystg_sys8:		//���ѐݒ�[�d�l�ݒ�8]
		case E_ystg_sys9:		//���ѐݒ�[�d�l�ݒ�9]			V06m
		case E_ystg_sysA:		//���ѐݒ�[�d�l�ݒ�10]			V06m
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					SWchg_ent();								//SW CHG �f�[�^ ENT
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5) {			//key code SW5
						disp_stg_sel --;
						if(disp_stg_sel == E_ystg_sys6){		//���ѐݒ�[�d�l�ݒ�6]?
							GAMEN_NO = 37;
						}
						else if(disp_stg_sel == E_ystg_sys8){		//���ѐݒ�[�d�l�ݒ�8]?			V06m
							GAMEN_NO = 56;
						}
						else{									//NO
							GAMEN_NO --;
						}
						GAMEN_disp();							//��ʕ\��
					}
					else if(KEY_DATA_CODE == E_key_sw6){		//key code SW6
//V06m						if (disp_stg_sel != E_ystg_sys8) {
						if (disp_stg_sel != E_ystg_sysA) {
							disp_stg_sel ++;
							if(disp_stg_sel == E_ystg_sys7){		//���ѐݒ�[�d�l�ݒ�7]?
								GAMEN_NO = 55;
							}
							else if(disp_stg_sel == E_ystg_sys9){		//���ѐݒ�[�d�l�ݒ�9]?		V06m
								GAMEN_NO = 106;
							}
							else{									//NO
								GAMEN_NO ++;
							}
							GAMEN_disp();							//��ʕ\��
						}
					}
					break;
			}
			break;

//V06m
//		case E_ystg_sys8:		//���ѐݒ�[�d�l�ݒ�8]
//			switch(KEY_DATA_MODE) {
//				case E_key_ent_mode:		//ENT key mode
//					SWchg_ent();								//SW CHG �f�[�^ ENT
//					break;
//
//				case E_key_sw14_mode:		//SW1�`4 key mode
//					switch(KEY_DATA_CODE) {
//						case E_key_sw1:			//key code SW1
//							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
//							GAMEN_NO = 31;
//							GAMEN_disp();						//��ʕ\��
//							break;
//						case E_key_sw2:			//key code SW2
//							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
//							break;
//						case E_key_sw3:			//key code SW3
//							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
//							break;
//						case E_key_sw4:			//key code SW4(�Ȃ�)
//							break;
//					}
//					break;
//
//				case E_key_sw56_mode:		//SW5/6 key mode
//					if(KEY_DATA_CODE == E_key_sw5) {			//key code SW5
//						disp_stg_sel = E_ystg_sys7;				//���ѐݒ�[�d�l�ݒ�7]
//						GAMEN_NO = 55;
//						GAMEN_disp();							//��ʕ\��
//					}
//					break;
//			}
//			break;

		case E_ystg_cbs1:		//���ѐݒ�[C/B����1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();						//SW CHG �f�[�^ ENT

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_cbs2;			//���ѐݒ�[C/B����2]��
							GAMEN_NO = 51;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_cbs2:		//���ѐݒ�[C/B����2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(�Ȃ�)
					Key_Ent_sv();								//�ݒ�l�̊m��		V05 (INS)
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							SWchg_ent();						//SW CHG �f�[�^ ENT

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_cbs1;			//���ѐݒ�[C/B����1]��
							GAMEN_NO = 38;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_spr1:		//���ѐݒ�[�������Ұ�1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;

						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_spr2;			//���ѐݒ�[�������Ұ�2]��
							GAMEN_NO = 40;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_ystg_spr2:		//���ѐݒ�[�������Ұ�2]
		case E_ystg_spr3:		//���ѐݒ�[�������Ұ�3]
		case E_ystg_spr4:		//���ѐݒ�[�������Ұ�4]
		case E_ystg_spr5:		//���ѐݒ�[�������Ұ�5]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel --;					//���ѐݒ�[�������Ұ�1/2/3/4]��
							if(disp_stg_sel == E_ystg_spr2){
								GAMEN_NO = 40;
							}
							else{
								GAMEN_NO --;
							}
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6
							disp_stg_sel ++;					//���ѐݒ�[�������Ұ�3/4/5/6]��
							if(disp_stg_sel == E_ystg_spr3){
								GAMEN_NO = 57;
							}
							else{
								GAMEN_NO ++;
							}
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_ystg_spr6:		//���ѐݒ�[�������Ұ�6]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr5;			//���ѐݒ�[�������Ұ�5]��
							GAMEN_NO = 59;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6(�Ȃ�)
							disp_stg_sel = E_ystg_spr7;			//���ѐݒ�[�������Ұ�7]��	// V01v�ǉ�
							GAMEN_NO = 61;													// V01v�ǉ�
							GAMEN_disp();						//��ʕ\��					// V01v�ǉ�
							break;
					}
					break;
			}
			break;

		case E_ystg_spr7:		//���ѐݒ�[�������Ұ�7]			// V01v�ǉ�
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr6;			//���ѐݒ�[�������Ұ�6]��
							GAMEN_NO = 60;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6(COP2�Ή�)
							disp_stg_sel = E_ystg_spr8;			//���ѐݒ�[�������Ұ�8]��
							GAMEN_NO = 62;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_ystg_spr8:		//���ѐݒ�[�������Ұ�8]			// COP2�Ή�
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr7;			//���ѐݒ�[�������Ұ�7]��
							GAMEN_NO = 61;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6
//V05c							disp_stg_sel = E_ystg_spr9;			//���ѐݒ�[�������Ұ�9]��
//V05c							GAMEN_NO = 63;
//V05c							GAMEN_disp();						//��ʕ\��

							disp_stg_sel = E_ystg_sprB;			//���ѐݒ�[�������Ұ�B]��		V06
							GAMEN_NO = 103;
							GAMEN_disp();						//��ʕ\��

							break;
					}
					break;
			}
			break;

		case E_ystg_spr9:		//���ѐݒ�[�������Ұ�9]			// COP2�Ή�
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
//V05c							disp_stg_sel = E_ystg_spr8;			//���ѐݒ�[�������Ұ�8]��
//V05c							GAMEN_NO = 62;
//V05c							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6
							disp_stg_sel = E_ystg_sprA;			//���ѐݒ�[�������Ұ�10]��
							GAMEN_NO = 64;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_ystg_sprA:		//���ѐݒ�[�������Ұ�10]			// COP2�Ή�
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr9;			//���ѐݒ�[�������Ұ�9]��
							GAMEN_NO = 63;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6(�Ȃ�)
							break;
					}
					break;
			}
			break;

		case E_ystg_sprB:		//���ѐݒ�[�������Ұ�B]			// V06
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							disp_stg_sel = E_ystg_spr8;			//���ѐݒ�[�������Ұ�8]��
							GAMEN_NO = 62;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw6:			//key code SW6
							break;
					}
					break;
			}
			break;

		case E_ystg_scm:		//���ѐݒ�[���Ѷѐݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(�Ȃ�)
					break;
			}
			break;

		case E_ystg_tmct:		//���ѐݒ�[���/����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(�Ȃ�)
					break;
			}
			break;

		case E_ystg_kjyu:		//���ѐݒ�[�׏d�v�ݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;

						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							SEI_test_out_sw6();					//���Y�ݒ�ýďo�͏���(SW6)

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_sura:		//���ѐݒ�[�ײ�ސݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
//Sit-S�Ȃ�			CAR_mkssi_set();							//�P�ʐ؊��f�[�^�i�[����
					CAR_mkssi_set();							//�P�ʐ؊��f�[�^�i�[����	V01m
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//���ѐݒ�OK(1:OK)
								PODATA_SET_FLG = 0xff;
								POSdata_set_kaku();					//�m�F���ɂ���߼޼�Ű�ݒ��ް��i�[(��߼�ݗ̈���ް���]��)
								SEQ_PAR_450 |= BIT_0;
								PVGENNITI_FLG = 00;					//�ޯ����߉�ʂɂČ��ʒu�f�[�^��ύX���Ă���h�m�F�h��������閘�����ݸނ��Ȃ�

								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

								PV_DEB_WORD_WK3 = PV_DEB_WORD_WK3 + 1;			/* V01n_b */
							}
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							SEQ_PAR_450 &= ~BIT_0;
							break;
					}
					break;
			}
			break;

		case E_ystg_dbak:			//���ѐݒ�[�ޯ������ް��ݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode(�Ȃ�)
					break;
			}
			break;

		case E_ystg_dini:		//���ѐݒ�[�ް�������]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(�Ȃ�)
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
//							if(SEQ_PAR_101 & BIT_4 ){			//�ް�������OK(1:OK)�H
//Sit-S�Ȃ�						&& MLD_100_CARD_FLG == 0xAA){		//�O���������L��H
//
//								PV_GAIBU_A1 = 6;				//�O���f�[�^�Ǎ��ݒ�
//
//								SWCHG_DISP_ON_FLG = 0x0FF;
//								SWchg_disp_gaibu();				//SW�ް����@�\��
//								SWCHG_DISP_ON_FLG = 0;
//
//2��								MLD100_ini();					//�P�O�O�^�f�[�^�C�j�V����
//								PV_GAIBU_A1 = 7;				//�O���f�[�^�ǂݍ��݊���
//
//								SWchg_disp();					//�r�v�f�[�^���@�\��
//							}
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_4){			//�ް�������OK(1:OK)�H

								PV_DATINI_A1 = 3;

								SWCHG_DISP_ON_FLG = 0x0FF;
								SWchg_disp_gaibu();				//SW�ް����@�\��
								SWCHG_DISP_ON_FLG = 0;

								INI_data_set();					//�f�[�^������
								PV_DATINI_A1 = 4;

								SWCHG_DISP_ON_FLG = 0x0FF;
								SWchg_disp();					//�r�v�f�[�^���@�\��
								SWCHG_DISP_ON_FLG = 0;
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_dail:	/* V01j */	//���ѐݒ�[�޲����ݒ��ߍ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//���ѐݒ�OK(1:OK)
								SEI_test_out_sw6();					//���Y�ݒ�ýďo�͏���(SW6)
								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_dair:	/* V01j */	//���ѐݒ�[�޲����ݒ��߉E]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//���ѐݒ�OK(1:OK)
								SEI_test_out_sw6();					//���Y�ݒ�ýďo�͏���(SW6)
								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_atuc:	/* V01j */	//���ѐݒ�[���͒��ߐݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							if(SEQ_PAR_101 & BIT_1){				//���ѐݒ�OK(1:OK)
								SEI_test_out_sw6();					//���Y�ݒ�ýďo�͏���(SW6)
								SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_ystg_kchg:		//���ѐݒ�[�@��������ݒ�]��		/* V06p */
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
							GAMEN_NO = 31;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							Sys_sel_dstg_mmon();				//�f�[�^�ݒ�[�����e�i���X���j�^]��
							break;
						case E_key_sw3:			//key code SW3
							Sys_sel_dstg_ksel();				//�f�[�^�ݒ�[�@�\�I��]��
							break;
						case E_key_sw4:			//key code SW4(�Ȃ�)
						case E_key_sw5:			//key code SW5(�Ȃ�)
						case E_key_sw5_down:	//key code SW5(������)(�Ȃ�)
							break;

						case E_key_sw6:			//key code SW6
							SWchg_ent();						//SW CHG �f�[�^ ENT
							SEI_test_out_sw6();					//���Y�ݒ�ýďo�͏���(SW6)

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(1, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;
	}
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dstg_mmon
*  Function Name:	�f�[�^�ݒ�[�����e�i���X���j�^]��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-06
********************************************************************************
*/
void	Sys_sel_dstg_mmon(void)
{
	disp_stg = 02;						//�f�[�^�ݒ��ʂ�
	disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��

	GAMEN_NO = 13;
	GAMEN_disp();						//��ʕ\��
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dstg_ksel
*  Function Name:	�f�[�^�ݒ�[�@�\�I��]��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-06
********************************************************************************
*/
void	Sys_sel_dstg_ksel(void)
{
	disp_stg = 02;						//�f�[�^�ݒ��ʂ�
	disp_stg_sel = E_dstg_ksel;			//�f�[�^�ݒ�[�@�\�I��]��

	GAMEN_NO = 14;
	GAMEN_disp();						//��ʕ\��
}


/*
********************************************************************************
*  Module Name:		Sys_sel_dsp�i��:GAMEN_MOVE�j
*  Function Name:	��ʂƊǗ��ð�ނ̈ړ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:�J�[�\�����e�[�u���̉�ʈړ��ԍ��ɂ���ʂƊǗ��ð�ނ̈ړ�
*
*  �� ��	:FIT)�c�[		ON:2002-06-06
********************************************************************************
*/
void	Sys_dsp_move(void)
{
	UNs		i;

	i = CSR_buff[CSR_TBL_POS_NOW].MOVE_NO;				//��ʈړ��ԍ�
	i &= 0x00ff;
	if( i == 0 || i == 0xff){
//		nop();
	}
	else{
		if( i == 32 ){
			disp_stg_sel = E_ystg_sys1;		//���ѐݒ�[�d�l�ݒ�1]
		}
		else if( i == 38 ){
			disp_stg_sel = E_ystg_cbs1;		//���ѐݒ�[C/B����1]��
		}
		else if( i == 39 ){
			disp_stg_sel = E_ystg_spr1;		//���ѐݒ�[�������Ұ�1]��
		}
		else if( i == 41 ){
			disp_stg_sel = E_ystg_scm;		//���ѐݒ�[���Ѷѐݒ�]��
		}
		else if( i == 43 ){
			disp_stg_sel = E_ystg_tmct;		//���ѐݒ�[���/����]��
		}
		else if( i == 44 ){
			disp_stg_sel = E_ystg_kjyu;		//���ѐݒ�[�׏d�v�ݒ�]��
		}
		else if( i == 45 ){
			disp_stg_sel = E_ystg_sura;		//���ѐݒ�[�ײ�ސݒ�]��
		}
		else if( i == 47 ){					// V01j
			disp_stg_sel = E_ystg_dail;		//���ѐݒ�[�޲����ݒ��ߍ�]��
		}
		else if( i == 48 ){					// V01j
			disp_stg_sel = E_ystg_dair;		//���ѐݒ�[�޲����ݒ��߉E]��
		}
		else if( i == 49 ){					// V01j
			disp_stg_sel = E_ystg_atuc;		//���ѐݒ�[���͒��ߐݒ�]��
		}
		else if( i == 50 ){
			disp_stg_sel = E_ystg_dbak;		//���ѐݒ�[�ޯ������ް��ݒ�]��
		}
		else if( i == 52 ){
			disp_stg_sel = E_ystg_dini;		//���ѐݒ�[�ް�������]��
		}
		else if( i == 63 ){		// V05c
			disp_stg_sel = E_ystg_spr9;		//���ѐݒ�[�������Ұ�9]��
		}
		else if( i == 108 ){		// V06p
			disp_stg_sel = E_ystg_kchg;		//���ѐݒ�[�@��������ݒ�]��
		}
		else{
			i = 31;
		}
		GAMEN_NO = i;
		GAMEN_disp();						//��ʕ\��
	}
}


/*
********************************************************************************
*  Module Name:		CAR_mkssi_set
*  Function Name:	�P�ʐ؊��ް��i�[����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-17
********************************************************************************
*/
void	CAR_mkssi_set(void)
{
//SIT-S�V�K

	if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		CAR_LNG_AREA = E_INCH;			//INCH
		CAR_KAJ_AREA = E_TON;			//ton
		CAR_ATU_AREA = E_PSI;			//PSI

		if( SEQ_016_SV & BIT_7 ) {	//�P�� �����x(1:�����x)
			SYO_LNG_CNT = 4;			//�����_�ʒu
			SYOD_LNG_CNT = 4;			//�����_�ʒu
			SYO_LNG_SUR_CNT = 4;		//�����_�ʒu
		}
		else{
			SYO_LNG_CNT = 3;			//�����_�ʒu
			SYOD_LNG_CNT = 3;			//�����_�ʒu
			SYO_LNG_SUR_CNT = 3;		//�����_�ʒu
		}
		SYO_ATU_CNT = 0;				//���͂͏����_����
		SYOD_ATU_CNT = 0;
		SYO_KAJ_CNT = 0;				//�����_����	V05r
	}
	else{								//SI�P�ʌn(��̫��)
		CAR_LNG_AREA = E_MM;			//mm						(6line 2002-12-11:�ύX)
		CAR_KAJ_AREA = E_KN;			//kN
		CAR_ATU_AREA = E_MPA;			//MPa

		if( SEQ_016_SV & BIT_7 ) {	//�P�� �����x(1:�����x)
			SYO_LNG_CNT = 3;			//�����_�ʒu
			SYOD_LNG_CNT = 3;			//�����_�ʒu
			if (SV_POINT_A1 == 0) {
				SYO_LNG_SUR_CNT = 3;			//�����_�ʒu
			}
			else {
				SYO_LNG_SUR_CNT = (UNs)SV_POINT_A1+1;		//�����_�ʒu
			}
		}
		else{
			SYO_LNG_CNT = 2;			//�����_�ʒu
			SYOD_LNG_CNT = 2;			//�����_�ʒu
			if (SV_POINT_A1 == 0) {
				SYO_LNG_SUR_CNT = 2;			//�����_�ʒu
			}
			else {
				SYO_LNG_SUR_CNT = (UNs)SV_POINT_A1;		//�����_�ʒu
			}
		}
		SYO_ATU_CNT = 0;				//���͂͏����_����
		SYOD_ATU_CNT = 0;
		SYO_KAJ_CNT = 0;				//�����_����	V05r
	}

	if (SEQ_024_SV & BIT_9)			//�׏d�P�ʐؑ֗L��H�i�d�l�ݒ�No.138�j			//V05r
	{
		if( SEQ_016_SV & BIT_5 ) {			//�P�ʐؑ� kN/ton	�i�d�l�ݒ�No.6�j
			CAR_KAJ_AREA = E_TON;			//ton
			SYO_KAJ_CNT = 1;				//�����_1��
		}
		else{								//
			CAR_KAJ_AREA = E_KN;			//kN
			SYO_KAJ_CNT = 0;				//�����_����
		}
	}


//SIT-S�ł́A�Ȃ�
//
//	if(SV_POINT_A1 == 0 ||				//�ײ�ޒ��߁@�����_�ʒu
//		SV_POINT_A1 > 2 ) {
//		SV_POINT_A1 = 1;				//�ײ�ޒ��߁@�����_�ʒu(��̫��)
//	}
//	if(SV_POINT_A47 == 0 ||				//�޲����ݎ������ߍ��@�����_�ʒu
//		SV_POINT_A47 > 2 ) {
//		SV_POINT_A47 = 1;				//�޲����ݎ������ߍ��@�����_�ʒu(��̫��)
//	}
//	if(SV_POINT_A48 == 0 ||				//�޲����ݎ������߉E�@�����_�ʒu
//		SV_POINT_A48 > 2 ) {
//		SV_POINT_A48 = 1;				//�޲����ݎ������߉E�@�����_�ʒu(��̫��)
//	}
//
//	if( SEQ_016_SV & BIT_4 ) {			//�P�ʐؑ� MKS�P�ʌn(1:�L)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = '  K ';			//K
//
//		SYO_LNG_CNT = SV_POINT_A1;		//�����_�ʒu
//		SYOD_LNG_CNT = SV_POINT_A47;	//�����_�ʒu
//
//		SYO_ATU_CNT = 0;				//���͂͏����_����
//		SYOD_ATU_CNT = 0;
//	}
//	else if( SEQ_016_SV & BIT_5 ) {		//�P�ʐؑ� SI�P�ʌn(1:�L)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' kN ';			//kN
//		CAR_ATU_AREA = 'MPa ';			//MPa
//
//		SYO_LNG_CNT = SV_POINT_A1;		//�����_�ʒu
//		SYOD_LNG_CNT = SV_POINT_A47;	//�����_�ʒu
//
//		SYO_ATU_CNT = 2;				//���͂͏����_�Q��
//		SYOD_ATU_CNT = 2;
//	}
//	else if( SEQ_016_SV & BIT_6 ) {		//�P�ʐؑ� INCH�P�ʌn(1:�L)
//		CAR_LNG_AREA = 'INCH';			//INCH
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = ' PSI';			//PSI
//
//		SYO_LNG_CNT = 3;				//�����_�ʒu
//		SYOD_LNG_CNT = 3;				//�����_�ʒu
//
//		SYO_ATU_CNT = 0;				//���͂͏����_����
//		SYOD_ATU_CNT = 0;
//	}
//	else{								//MKS�P�ʌn(��̫��)
//		CAR_LNG_AREA = 'mm  ';			//mm
//		CAR_KAJ_AREA = ' ton';			//ton
//		CAR_ATU_AREA = '  K ';			//K
//
//		SYO_LNG_CNT = 1;				//�����_�ʒu
//		SYOD_LNG_CNT = 1;				//�����_�ʒu
//
//		SYO_ATU_CNT = 0;				//���͂͏����_����
//		SYOD_ATU_CNT = 0;
//	}

	/* ���[�V������ʂ̉����ݒ�P�ʂ��׏d�ݒ�P�ʂɕύX���� */
//V01m	if (SEQ_024_SV & BIT_4)						//�׏d�␳����H	V01k
	if (SEQ_050_SV & BIT_9)						//�׏d�␳����H	V01k
	{
		if (SEQ_024_SV & BIT_9)					//�׏d�P�ʐؑ֗L��H�i�d�l�ݒ�No.138�j			//V05r
		{
			if( SEQ_016_SV & BIT_5 ) {				//�P�ʐؑ� kN/ton	�i�d�l�ݒ�No.6�j
				CAR_LNG_KAJ_AREA = E_TON;			//ton
				SYO_LNG_KAJ_CNT = 1;				//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 1;				//�␳�̏����_�ʒu		V05r
			}
			else {
				CAR_LNG_KAJ_AREA = E_KN;			//kN
				SYO_LNG_KAJ_CNT = 0;				//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 0;				//�␳�̏����_�ʒu		V05r
			}
		}
		else
		{
			if( SEQ_016_SV & BIT_6 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				CAR_LNG_KAJ_AREA = E_TON;			//ton
			}
			else {
				CAR_LNG_KAJ_AREA = E_KN;			//kN
			}
			SYO_LNG_KAJ_CNT = 0;					//�����^�׏d�̏����_�ʒu
			SYO_HOS_KAJ_CNT = 0;					//�␳�̏����_�ʒu		V05r
		}
	}
	else {
		if( SEQ_016_SV & BIT_6 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
			CAR_LNG_KAJ_AREA = E_INCH;			//INCH

			if( SEQ_016_SV & BIT_7 ) {			//�P�� �����x(1:�����x)
				SYO_LNG_KAJ_CNT = 4;			//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 0;			//�␳�̏����_�ʒu		V05r
			}
			else{
				SYO_LNG_KAJ_CNT = 3;			//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 0;			//�␳�̏����_�ʒu		V05r
			}
		}
		else {
			CAR_LNG_KAJ_AREA = E_MM;			//mm

			if( SEQ_016_SV & BIT_7 ) {		//�P�� �����x(1:�����x)
//V01m				SYO_LNG_KAJ_CNT = 3;			//�����^�׏d�̏����_�ʒu
				SYO_LNG_KAJ_CNT = SYO_LNG_SUR_CNT;	//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 0;				//�␳�̏����_�ʒu		V05r
			}
			else{
//V01m				SYO_LNG_KAJ_CNT = 2;			//�����^�׏d�̏����_�ʒu
				SYO_LNG_KAJ_CNT = SYO_LNG_SUR_CNT;	//�����^�׏d�̏����_�ʒu
				SYO_HOS_KAJ_CNT = 0;				//�␳�̏����_�ʒu		V05r
			}
		}
	}

}


/*
********************************************************************************
*  Module Name:		INI_data_set
*  Function Name:	�f�[�^������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-09-10
********************************************************************************
*/
void	INI_data_set(void)
{
	UNs		*src_p, cnt, i;


	cnt = (UNs *)&PV_TOTLC1_B3 - &SEQ_016_SV;		//�׼�RAM�̈�̐ݒ�l END���ڽ - į�߱��ڽ
	src_p = (UNs *)E_FROM_INI_TOP;					//�ݒ�l�����ް����ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&SEQ_016_SV, src_p, cnt);

/*V00p*/
	cnt = (UNs *)&SV_RNZRPM_A12 - &SEQ_016_SV;		//
	src_p = (UNs *)E_FROM_INI_TOP;					//�ݒ�l�����ް����ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//�ׯ��ROM�̘A����]�ݒ�l
	SV_RNZRPM_A12 = *src_p;							//
/*V00p*/
	cnt = (UNs *)&SV_RNZTIM_A12 - &SEQ_016_SV;		//
	src_p = (UNs *)E_FROM_INI_TOP;					//�ݒ�l�����ް����ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//�ׯ��ROM�̘A���^�C�}�ݒ�l
	SV_RNZTIM_A12 = *src_p;							//

/*V05b*/
	cnt = (UNs *)&SV_SMPSTR_KAJ - &SEQ_016_SV;		//�׼�RAM�̈�̐ݒ�l END���ڽ - į�߱��ڽ
	src_p = (UNs *)E_FROM_INI_TOP;					//�ݒ�l�����ް����ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	src_p = src_p + cnt;							//�ׯ��ROM�̘A����]�ݒ�l
	memcpy_word(&SV_SMPSTR_KAJ, src_p, 10);


	FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬


	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];		//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ
	src_p = (UNs *)E_FROM_INI_TOP2;					//�ݒ�l�����ް��^���̱��ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&KAT_NAME_01[0], src_p, cnt);

//V06n
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];		//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ
	src_p = (UNs *)E_FROM_INI_TOP3;					//�ݒ�l�����ް��^���̱��ڽ
	src_p += INIT_DAT_OFS/2;					//V06
	memcpy_word(&KAT_NAME_101[0], src_p, cnt);

	FRAM_KAT_csum_set();							//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬

	SVSW_CHG_FLG = 0x013f;
	ONOFF_sub();									//�d�l�L�薳���ɂ����ؐ���

	mmon_sel_chk();									//Ӱ��݂̕����I������
	mmon_trans_get();								//��]�����ɂ���ް��̎擾

	CAR_mkssi_set();								//�P�ʐ؊��f�[�^�i�[����
	CAMname_pon_read();								//�d���������̔ėp�і��̂̓Ǎ���
	SURA_sv_chg();									//�ײ�ގ������߂r�u�ύX����
	SEI_ON6_LST1 = 0xff;							//�d���������K���i���̍��ڗL���`�F�b�N�����邽�߁B

	PV_MLDNO1_F1 = 1;									//�^�f�[�^�̏����l��}��
	memcpy_word(&PV_MLDNO2_F1[0], &KAT_NAME_01[0], 8);	//�^�f�[�^���̂P��}��
	memcpy_word(&PV_MLDNO3_F1[0], &KAT_MEMO_01[0], 8);	//�^�f�[�^�����P��}��

	FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬


//V06n	for(cnt=100, i=1 ; cnt > 0 ; cnt--, i++){
	for(cnt=200, i=1 ; cnt > 0 ; cnt--, i++){
		WDT_Rifresh();								//�����ޯ����- ��گ��

		kata_save(i, &FRAM_KAT_TOP);				//�^�f�[�^��FROM�֊i�[
	}


	SURA_CHG_LST = 0;								//�^�f�[�^��ǂ񂾌�ɐ���ɓ��삵�Ȃ�
	SET_SPM_LST = 0;

	MCN_MENT_CNT1 = 0;								//�����e�i���X�J�E���^�P
	MCN_MENT_CNT2 = 0;								//�����e�i���X�J�E���^�Q
	MCN_MENT_CNT3 = 0;								//�����e�i���X�J�E���^�R
	MCN_MENT_CNT4 = 0;								//�����e�i���X�J�E���^�S
	MCN_MENT_CNT5 = 0;								//�����e�i���X�J�E���^�T
	MCN_MENT_CNT6 = 0;								//�����e�i���X�J�E���^�U
	MCN_MENT_CNT7 = 0;								//�����e�i���X�J�E���^�V
	MCN_MENT_CNT8 = 0;								//�����e�i���X�J�E���^�W
	MCN_MENT_TIM1 = 0;								//�����e�i���X���ԂP�i1sec�J�E���^�j
	MCN_MENT_TIM1_10 = 0;							//�����e�i���X���ԂP�i10msec�J�E���^�j
	MCN_MENT_TIM2 = 0;								//�����e�i���X���ԂQ�i1sec�J�E���^�j
	MCN_MENT_TIM2_10 = 0;							//�����e�i���X���ԂQ�i10msec�J�E���^�j
	MCN_MENT_TIM3 = 0;								//�����e�i���X���ԂR�i1sec�J�E���^�j
	MCN_MENT_TIM3_10 = 0;							//�����e�i���X���ԂR�i10msec�J�E���^�j

	PV_LIFE_COUNT[0] = 0;							//�@�B���J�E���^
	PV_LIFE_COUNT[1] = 0;							//�@�B���J�E���^
	PV_LIFE_COUNT[2] = 0;							//�@�B���J�E���^
	PV_LIFE_TIME_10 = 0;							//�@�B�����ԁi10msec�J�E���^�j
	PV_LIFE_TIME = 0;								//�@�B�����ԁi1sec�J�E���^�j

	PV_GAIN_BAK1L = 0;								//�ő�c�݂Q�O�O�O���Q�C��
	PV_GAIN_BAK1R = 0;								//�ő�c�݂Q�O�O�O�E�Q�C��
	PV_GAIN_BAK2L = 0;								//�ő�c�݂P�T�O�O���Q�C��
	PV_GAIN_BAK2R = 0;								//�ő�c�݂P�T�O�O�E�Q�C��
	PV_GAIN_BAK3L = 0;								//�ő�c�݁@�W�O�O���Q�C��
	PV_GAIN_BAK3R = 0;								//�ő�c�݁@�W�O�O�E�Q�C��
	PV_GAIN_BAK4L = 0;								//�ő�c�݁@�S�O�O���Q�C��
	PV_GAIN_BAK4R = 0;								//�ő�c�݁@�S�O�O�E�Q�C��
	PV_GAIN_BAK5L = 0;								//�ő�c�݁@�Q�O�O���Q�C��
	PV_GAIN_BAK5R = 0;								//�ő�c�݁@�Q�O�O�E�Q�C��
	PV_OF_BAKL = 0;									//�I�t�Z�b�g�l��
	PV_OF_BAKR = 0;									//�I�t�Z�b�g�l�E
	PV_OF_AVE_BAKL = 0;								//�I�t�Z�b�g�␳��
	PV_OF_AVE_BAKR = 0;								//�I�t�Z�b�g�␳�E
	PV_OF_AVE_BAKT = 0;								//�I�t�Z�b�g�␳���v
	PV_GENITI_B2 = 0;								//���ʒu�f�[�^

}



/*** END ***/