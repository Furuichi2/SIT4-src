/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�f�[�^�ݒ�̑��상�C������												*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-06-04
*
*************************************************************************************/

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//DPRAM�Q�ƕϐ���`

/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	GRAPH_INIT(void);				//�O���t�`�揉������
extern	void	GRAPH_DISP(void);				//�O���t�`�揈��

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR068;						//�J���������Z�@�\ �L���^����
extern	UNs		GMN_PAR077;						//�J��Ԃ��񐔏��								2014/09/04
extern	UNs		GMN_PAR079;						//���̈�ݒ� �L���^����						2014/09/10
extern	UNs		GMN_PAR048;						//�׏d����L���^����							2015/01/15

/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	dsp_Dataset(void);						//�f�[�^�ݒ�̊Ǘ�

void	Data_sel_cam(void);						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)

void	SHARCH_gamen_15(void);					//�������͎��̉�ʈړ�
void	SW56_gamen_15(void);					//�^�ް���ʁ@SW56����

void	MEMO_data_write(void);					//�^�ް� �ӏ���
void	KAT_data_read(void);					//�^�ް� �Ǎ�
void	KAT_data_write(void);					//�^�ް� ����
void	KAT_read_sura_chk(void);				//�^�f�[�^�Ǎ��ݎ��X���C�h�ݒ�l�`�F�b�N

void	NAME_csr_mng(void);						//���̉�ʃJ�[�\������
void	KATname_inp(void);						//�^���� ���͏���
void	KATname_cls(void);						//�^���� ��������
void	KATname_ref(UNs, UNs *);				//�J�����̃��t���b�V��
void	CSR_disp_on(UNs);						//����ʔ��]
UNs		NAME_leng_chk(UNb *, UNs);				//���̂̓��͕��������`�F�b�N

void	CAMname_inp(void);						//�J������ ���͏���
void	CAMname_cls(void);						//�J������ ��������
UNi		CAMname_inp_chk(void);					//�J�����̓��͉`�F�b�N
void	CAMname_touroku(void);					//�J�����̓o�^
void	CAMname_sw_ent(void);					//�ėp�o�͑I��
void	CAM_name_ref(void);						//۰�ضєėp�I����ʂɑΉ������і��̂̍X�V
void	Cam_auto_copy(void);
UNs		Cam_auto_chk(void);
void	Make_Rep_Bit_Inf(void);
void	Dat_mm_inch_chg2(void);						//2015/01/28

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNs *	KAT_sv_name_tbl[101];
extern	const	UNs *	KAT_sv_memo_tbl[101];
extern	const	UNs *	Camcsr_Name_Tbl[20];
extern	const	UNs *	Camcsr_Name_TblSV[20];
extern	const	UNs *	Camcsr_Name_Tbl1[20];
extern	const	UNs *	Camcsr_Name_TblSW[16];


/*
********************************************************************************
*  Module Name:		dsp_Dataset
*  Function Name:	�f�[�^�ݒ�̊Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-04
********************************************************************************
*/
void	dsp_Dataset(void)
{
	UNs	*bf_p, i, j;
	UNs	bit;

	switch(disp_stg_sel) {

		case E_dstg_init:		//�f�[�^�ݒ�[��{]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					ROTTO_chk();								//ۯĶ��� ���� ����

//2��	MOV	SET_SPM_LST,0				;
//2��	CALL	SETSPM_SV_CHG		;/* ���Y�r�o�l�r�u�ύX���� 			*/
					SURA_CHG_LST = 0;
					SURA_sv_chg();								//�X���C�h�������߂r�u�ύX����

					mmon_trans_put();							//��]�����ɂ���ް��̊i�[

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(�Ȃ�)
//V06n							disp_stg_sel = E_dstg_Lang;		//�f�[�^�ݒ�[����ݒ�]��		V06m
//V06n							WINDOW_NO = 24;
//V06n							WIN_gamen_disp();				//�E�C���h�E��ʕ\��

//2014/08/27  SIT4-MC
							if (GMN_PAR068 == 1) {
								disp_stg_sel = E_dstg_CamAtCal;		//�f�[�^�ݒ�[�J���o�͎������Z]��
								GAMEN_NO = 109;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							CAR_mkssi_set();					//�P�ʐ؊�  V01u
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_PAR_107 & BIT_0){			//�@�\�I��1(�^�ް��Ǘ��@1:�L)
								disp_stg_sel = E_dstg_kata;		//�f�[�^�ݒ�[�^�ԍ�]��
								CSR_POS_G15 = 0xff;				//�J�[�\���\���ʒu�����݂̔ԍ��̈ʒu��
								GAMEN_NO = 15;
								GAMEN_disp();					//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��
							GAMEN_NO = 13;
							GAMEN_disp();						//��ʕ\��
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7	//V06b
							if (SEQ_PAR_107 & BIT_4) {
								SV0_TAL1_CNT = PV_TOTLC1_B3;
								SV0_LOT1_CNT = PV_LOTCT1_B1;
								SV0_LOT2_CNT = PV_LOTCT2_B1;
								disp_stg_sel = E_dstg_cntc;		//�f�[�^�ݒ�[���Ēl�C��]��
								WINDOW_NO = 22;
								WIN_gamen_disp();				//�E�C���h�E��ʕ\��
							}
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG �f�[�^ ENT
						KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
						ROTTO_chk();							//ۯĶ��� ���� ����

						mmon_trans_put();						//��]�����ɂ���ް��̊i�[

						SW16data_onset(0xff, 07);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

						SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else{									//key code SW5/SW6(������)
						SW16data_onset(0x00, 07);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0x00, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_mset:		//�f�[�^�ݒ�[���[�V�����ݒ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//�ݒ�l�̊m��
					mmon_sv_chg(i);								//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);						//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();							//��]�����ɂ���ް��̊i�[
					mmon_f_off(j);								//��葬�x�ݒ�ر				2014/09/25
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2(�Ȃ�)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_mcg;			//�f�[�^�ݒ�[���[�V�����O���t]��
							GAMEN_NO = 29;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
							break;
//2014/09/04
						case E_key_sw7:			//key code SW7
							if ( (GMN_PAR077 != 0) || (GMN_PAR079 == 1) ) {			//�J��Ԃ� or ���̈�
								disp_stg_sel = E_dstg_rep_fix;			//�f�[�^�ݒ�[�J��Ԃ��^���̈�]��
								GAMEN_NO = 54;
								GAMEN_disp();						//��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							if ( SEQ_PAR_058 & BIT_5 ) {						//�p�X���[�h��v		2017/11/06
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWð��ٌ�
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									SWchg_ent();								//SW CHG �f�[�^ ENT
									mmon_trans_put();							//��]�����ɂ���ް��̊i�[
								}
								SEI_test_out_sw5();								//���Y�ݒ�ýďo�͏���(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//���ٔF���ԍ����̈ړ�����
											bf_p = SW_buff[j].DATA_ADR;				//�ް��i�[���ڽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//�ް��i�[��̕ύX�ޯĈʒu
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//���ٔF���ԍ����̈ړ�����
												SW_TBL_POS_NOW = j;					//�r�v�f�[�^�����I��
												break;
											}
										}
									}
									FURIKO_SW_del();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
									SWchg_move_ent();								//SW CHG�̈ړ� �ް�ENT
									SV0_MOT_FIX = 0;								//��葬�x�u���O�N���A			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//��]�����ɂ��ݒ�l �؊���
									FURIKO_SW_chk();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
//2014/08/20 �ĕ`�悵���Ⴆ�I
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6���i��׸�
										SWchg_mmon_ent();								//Ӱ��ݗp SW�ް� ENT
										mmon_trans_put();								//��]�����ɂ���ް��̊i�[
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 74) {	//SW6���i��׸�		V06p
										//���x���ЯĒl����
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6���i��׸��ڕW�l		2015/01/15
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//�����^�׏d�ڕW�؊���
									}
								}
								/* V00m */
								else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
			 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
								}
							}
							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57) {
				 					SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		/* V01d */
		case E_dstg_mset2:		//�f�[�^�ݒ�[���[�V�����ݒ�6�`10]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					j = CSR_TBL_POS_NOW;						//2014/09/25
					Key_Ent_sv();								//�ݒ�l�̊m��
					mmon_sv_chg(i);								//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);						//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();							//��]�����ɂ���ް��̊i�[
					mmon_f_off(j);								//��葬�x�ݒ�ر				2014/09/25
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2(�Ȃ�)
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_mcg;			//�f�[�^�ݒ�[���[�V�����O���t]��
							GAMEN_NO = 29;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
							break;

//2014/09/04
						case E_key_sw7:			//key code SW7
							if ( (GMN_PAR077 != 0) || (GMN_PAR079 == 1) ) {			//�J��Ԃ� or ���̈�
								disp_stg_sel = E_dstg_rep_fix;			//�f�[�^�ݒ�[�J��Ԃ��^���̈�]��
								GAMEN_NO = 54;
								GAMEN_disp();						//��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX == 1 &&	//SWð��ٌ�
									CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 0 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									SWchg_ent();								//SW CHG �f�[�^ ENT
									mmon_trans_put();							//��]�����ɂ���ް��̊i�[
								}
								SEI_test_out_sw5();								//���Y�ݒ�ýďo�͏���(SW6)	V01m
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							/* V01d */
							if (CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 58) {
		 						SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)
							}
							break;

						case E_key_sw6:			//key code SW6
							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��

							if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
								if( CSR_buff[CSR_TBL_POS_NOW].SW_MAX > 1) {
									for( i = SW_CNT,j=0 ; i > 0 ; i--, j++) {
										if( SW_buff[j].CSR_NO == CSR_FLG_CNT ) {	//���ٔF���ԍ����̈ړ�����
											bf_p = SW_buff[j].DATA_ADR;				//�ް��i�[���ڽ
											if( *bf_p & SW_buff[j].CHG_NO ){		//�ް��i�[��̕ύX�ޯĈʒu
												SW_FLG_CNT = SW_buff[j].DSP_NO;		//���ٔF���ԍ����̈ړ�����
												SW_TBL_POS_NOW = j;					//�r�v�f�[�^�����I��
												break;
											}
										}
									}
									FURIKO_SW_del();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
									SWchg_move_ent();								//SW CHG�̈ړ� �ް�ENT
									SV0_MOT_FIX = 0;								//��葬�x�u���O�N���A			2014/10/09
//2014/08/20									mmon_kaiten_chg();								//��]�����ɂ��ݒ�l �؊���
									FURIKO_SW_chk();								//�������i�U�q�j�̔�\���Z�b�g		//V06p
//2014/08/20 �ĕ`�悵���Ⴆ�I
									disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
									GAMEN_NO = 28;
									GAMEN_disp();
								}
//V01z								else if(CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97 ) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
								else if((CSR_buff[CSR_TBL_POS_NOW].DATA_NO >= 97) &&
										(CSR_buff[CSR_TBL_POS_NOW].DATA_NO <= 102)) {	//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
									if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 60) {		//SW6���i��׸�
										SWchg_mmon_ent();								//Ӱ��ݗp SW�ް� ENT
										mmon_trans_put();								//��]�����ɂ���ް��̊i�[
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 74) {	//SW6���i��׸�		V06p
										//���x���ЯĒl����
										mmon_spd_in();
									}
									else if (CSR_buff[CSR_TBL_POS_NOW].SW6_DN == 75) {	//SW6���i��׸��ڕW�l		2015/01/15
//2015/04/10										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97);	//�����^�׏d�ڕW�؊���
										mmon_pos_kaj_chg(CSR_buff[CSR_TBL_POS_NOW].DATA_NO-97+5);	//�����^�׏d�ڕW�؊���
									}
								}
							}
							/* V00m */
							else if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 56) {
		 						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_mcg:		//�f�[�^�ݒ�[���[�V�����O���t]��
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
							break;
//2014/09/04
						case E_key_sw7:			//key code SW7
							if ( (GMN_PAR077 != 0) || (GMN_PAR079 == 1) ) {			//�J��Ԃ� or ���̈�
								disp_stg_sel = E_dstg_rep_fix;			//�f�[�^�ݒ�[�J��Ԃ��^���̈�]��
								GAMEN_NO = 54;
								GAMEN_disp();						//��ʕ\��
							}
							break;

					}
					break;
			}
			break;

		case E_dstg_ksin:		//�f�[�^�ݒ�[���U�@�\�ݒ�]		V05r		======================================
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
									disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
									GAMEN_NO = 53;
								}
								else {
									if(SEQ_018_SV & 0x0700) {		// V05g
										disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
										GAMEN_NO = 20;
									}
									else {
										disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
										GAMEN_NO = 68;
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//���[�^���J���P�`�W �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
								}
								else{								//���[�^���J���X�`�P�U �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 25;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
									}
									else {
										GAMEN_NO = 22;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG �f�[�^ ENT
						KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

						SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

						SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else{									//key code SW5/SW6(������)
						SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_tms1:		//�f�[�^�ݒ�[�G�W�F�N�^]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
									disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
									GAMEN_NO = 53;
								}
								else {
									if(SEQ_018_SV & 0x0700) {		// V05g
										disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
										GAMEN_NO = 20;
									}
									else {
										disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
										GAMEN_NO = 68;
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//���[�^���J���P�`�W �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
								}
								else{								//���[�^���J���X�`�P�U �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 25;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
									}
									else {
										GAMEN_NO = 22;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5){			//key code SW5
						SWchg_ent();							//SW CHG �f�[�^ ENT
						KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

						SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6

						if ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) {		//�s���ݒ�ӏ�				2014/09/08

							if (GMN_PAR077 != 0) {								//�J��Ԃ��@�\�L��
								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
									bit = cBIT0;
									SV_EJECAM_ONR |= (bit << CSR_TBL_POS_NOW);
								}
								else {											//OFF�s��
									bit = cBIT0;
									SV_EJECAM_OFR |= (bit << CSR_TBL_POS_NOW);
								}
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//�ް���ݼ� �׸� ���
								KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {
								SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
						}
						else {
							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
						}
					}
					else{									//key code SW5/SW6(������)
						SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_tms2:		//�f�[�^�ݒ�[�~�X�t�B�[�h1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							/* V01d */
							if (SEQ_018_SV & BIT_11) {
								disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
								GAMEN_NO = 68;
								GAMEN_disp();						//��ʕ\��
							}
							else {
								if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
									disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
									GAMEN_NO = 53;
								}
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//���[�^���J���P�`�W �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
								}
								else{								//���[�^���J���X�`�P�U �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 25;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
									}
									else {
										GAMEN_NO = 22;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5�ް������ԍ�
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

								SWchg_ent();						//SW CHG �f�[�^ ENT
								KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O
							}
							else{
								SEI_test_out_sw5();					//���Y�ݒ�ýďo�͏���(SW5)
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//�s���ݒ�ӏ�				2014/09/08
								 (GMN_PAR077 != 0) ) {								//�J��Ԃ��@�\�L��

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
									bit = cBIT0;
									SV_MISCAM_ONR |= (bit << CSR_TBL_POS_NOW/2);
								}
								else {											//OFF�s��
									bit = cBIT0;
									SV_MISCAM_OFR |= (bit << CSR_TBL_POS_NOW/2);
								}
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//�ް���ݼ� �׸� ���
								KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {
								if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5�ް������ԍ�
									SW_FLG_CNT = 2;
								}
								else{
									SW_FLG_CNT = 1;
								}
								SVSW_tbl_enzan();						//�r�u�r�v�e�[�u���A�h���X���Z
								SWchg_ent();							//SW CHG �f�[�^ ENT
								KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		/* V01d */
		case E_dstg_tms3:		//�f�[�^�ݒ�[�~�X�t�B�[�h2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
								disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
								GAMEN_NO = 53;
								GAMEN_disp();						//��ʕ\��
							}
							else {
								if(SEQ_018_SV & 0x0700) {		// V05g
									disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
									GAMEN_NO = 20;
									GAMEN_disp();						//��ʕ\��
								}
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//���[�^���J���P�`�W �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
								}
								else{								//���[�^���J���X�`�P�U �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 25;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
									}
									else {
										GAMEN_NO = 22;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5�ް������ԍ�
								SW_FLG_CNT = 1;
								SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

								SWchg_ent();						//SW CHG �f�[�^ ENT
								KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O
							}
							else{
								SEI_test_out_sw5();					//���Y�ݒ�ýďo�͏���(SW5)
							}
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6

							if ( ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) &&		//�s���ݒ�ӏ�				2014/09/08
								 (GMN_PAR077 != 0) ) {								//�J��Ԃ��@�\�L��

								if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
									bit = cBIT4;
									SV_MISCAM_ONR |= (bit << CSR_TBL_POS_NOW/2);
								}
								else {											//OFF�s��
									bit = cBIT4;
									SV_MISCAM_OFR |= (bit << CSR_TBL_POS_NOW/2);
								}
								SWchg_disp();
								SVSW_CHG_FLG |= 0x0020;					//�ް���ݼ� �׸� ���
								KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {
								if(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB == 0){	//SW5�ް������ԍ�
									SW_FLG_CNT = 2;
								}
								else{
									SW_FLG_CNT = 1;
								}
								SVSW_tbl_enzan();						//�r�u�r�v�e�[�u���A�h���X���Z
								SWchg_ent();							//SW CHG �f�[�^ ENT
								KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

								SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_tms4:		//�f�[�^�ݒ�[���[�^���J��1]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
									disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
									GAMEN_NO = 53;
								}
								else {
									if(SEQ_018_SV & 0x0700) {		// V05g
										disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
										GAMEN_NO = 20;
									}
									else {
										disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
										GAMEN_NO = 68;
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT2_GAMEN_NON != 0xff){			//���[�^���J���X�`�P�U ���@�H
								if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
									GAMEN_NO = 25;
									disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
								}
								else {
									GAMEN_NO = 22;
									disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
								}
								GAMEN_disp();					//��ʕ\��
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
							ROTTO_chk();							//ۯĶ��� ���� ����

							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
//							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

							i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
							if( i < 0x80 || i >= 0x90 ){				//�J�����̉�ʈړ������H
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {										//YES
								if ( (SV_buff[SV_TBL_POS_NOW].GRP_NO >= 38) && 		//2014/09/01
									 (SV_buff[SV_TBL_POS_NOW].GRP_NO <= 39) ) {		//�i�p�ݒ�ӏ�

									if (SEQ_PAR_151 & cBIT11) {						//���Ԑi�p�L��
										if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 5) {
											csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB+0);	//SW6 �ް������ԍ�
										}
										else {
											csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB+1);	//SW6 �ް������ԍ�
										}
										SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
										Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
										Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
									}
									else {
										CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
										disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
										GAMEN_NO = 12;
										GAMEN_disp();						//��ʕ\��
									}
								}
								else if ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) {		//�s���ݒ�ӏ�				2014/09/01

									if (GMN_PAR077 != 0) {								//�J��Ԃ��@�\�L��
										if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
											bit = cBIT0;
											SV_ROTCAM_ONR |= (bit << CSR_TBL_POS_NOW);
										}
										else {											//OFF�s��
											bit = cBIT0;
											SV_ROTCAM_OFR |= (bit << CSR_TBL_POS_NOW);
										}
										SWchg_disp();
										SVSW_CHG_FLG |= 0x0020;				//�ް���ݼ� �׸� ���
										KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
										SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
										Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
										Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
									}
									else {
										CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
										disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
										GAMEN_NO = 12;
										GAMEN_disp();						//��ʕ\��
									}
								}
								else {
									CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
									disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
									GAMEN_NO = 12;
									GAMEN_disp();						//��ʕ\��
								}
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_tms5:		//�f�[�^�ݒ�[���[�^���J��2]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							if(MIS_GAMEN_NON != 0xff){
								if (SEQ_PAR_151 & cBIT8) {				//�ײ�ގ����ҋ@�@�\		2014/08/27		//SIT4-MC
									disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
									GAMEN_NO = 53;
								}
								else {
									if(SEQ_018_SV & 0x0700) {		// V05g
										disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
										GAMEN_NO = 20;
									}
									else {
										disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
										GAMEN_NO = 68;
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT1_GAMEN_NON != 0xff){
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;			//�f�[�^�ݒ�[���[�^���J��1]��
									}
									GAMEN_disp();						//��ʕ\��
							}
							break;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7		V05r
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#endif
						case E_key_sw5:			//key code SW5
							SWchg_ent();							//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
							ROTTO_chk();							//ۯĶ��� ���� ����
                            
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
//							SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

							i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
							if( i < 0x80 || i >= 0x90 ){				//�J�����̉�ʈړ������H
								SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
								Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							else {										//YES
								if ( (SV_buff[SV_TBL_POS_NOW].GRP_NO >= 40) && 		//2014/09/01
									 (SV_buff[SV_TBL_POS_NOW].GRP_NO <= 41) ) {		//�i�p�ݒ�ӏ�

									if (SEQ_PAR_151 & cBIT11) {						//���Ԑi�p�L��
										if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 5) {
											csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB+0);	//SW6 �ް������ԍ�
										}
										else {
											csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB+1);	//SW6 �ް������ԍ�
										}
										SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
										Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
										Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
									}
									else {
										CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
										disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
										GAMEN_NO = 12;
										GAMEN_disp();						//��ʕ\��
									}
								}
								else if ( SV_buff[SV_TBL_POS_NOW].SUB_NO == 53 ) {		//�s���ݒ�ӏ�			2014/09/01

									if (GMN_PAR077 != 0) {								//�J��Ԃ��@�\�L��
										if (SV_buff[SV_TBL_POS_NOW].DSP_NO == 1) {		//ON�s��
											bit = cBIT8;
											SV_ROTCAM_ONR |= (bit << CSR_TBL_POS_NOW);
										}
										else {											//OFF�s��
											bit = cBIT8;
											SV_ROTCAM_OFR |= (bit << CSR_TBL_POS_NOW);
										}
										SWchg_disp();
										SVSW_CHG_FLG |= 0x0020;				//�ް���ݼ� �׸� ���
										KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
										SW16data_onset(0xff, 0x08);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
										Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
										Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
									}
									else {
										CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
										disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
										GAMEN_NO = 12;
										GAMEN_disp();						//��ʕ\��
									}
								}
								else {
									CAM_NAME_NO = (i - 0x80);				//�ύX�J�����̔ԍ��Ǎ�
									disp_stg_sel = E_dstg_tms6;				//�f�[�^�ݒ�[���[�^���J������]��
									GAMEN_NO = 12;
									GAMEN_disp();						//��ʕ\��
								}
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_tms6:		//�f�[�^�ݒ�[���[�^���J������]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					CAMname_inp();								//�J������ ���͏���
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {

						case E_key_sw6:			//key code SW6
//							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
//							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							CAMname_touroku();						//�J�����̓o�^
//							break;
						case E_key_sw1:			//key code SW1
							CSR_FLG_CNT = CSR_FLG_CNT_BAK;			//���݂̃J�[�\���ʒu�J�E���g
							SV_FLG_CNT = SV_FLG_CNT_BAK;
							SW_FLG_CNT = SW_FLG_CNT_BAK;
							CSR_FLG = 5;

							GAMEN_NO = GAMEN_NO_CAM;
//2014/09/01							if(GAMEN_NO == 21){
							if( (GAMEN_NO == 21) || (GAMEN_NO == 24) ){
								disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
							}
							else{
								disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
							}
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2(�Ȃ�)
							break;
						case E_key_sw3:			//key code SW3(�Ȃ�)
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��
							GAMEN_NO = 13;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							if( 19 == CSR_buff[CSR_TBL_POS_NOW].SW5_DN ){		//�I���H
								CAMname_sw_ent();								//�ėp�o�͑I��
							}
							else if(20 == CSR_buff[CSR_TBL_POS_NOW].SW5_DN){	//�����H
								CAMname_cls();									//�J�����̒�������
								Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							}
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_kata:		//�f�[�^�ݒ�[�^�ԍ�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					if(SV_DATA_CHG == 0xff){					//�f�[�^�ύX�L��H
						CSR_MOVE_NON = 0xff;					//ENT KEY ���وړ��֎~
						Key_Ent_sv();							//�ݒ�l�̊m��
						CSR_MOVE_NON = 0x00;					//ENT KEY ���وړ�

						SHARCH_gamen_15();						//�������͎��̉�ʈړ�
					}
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if (MLD_100_GNO == 21) {					//�T���v���^�f�[�^�Ή�		2014/04/16
								MLD_100_GNO = 20;						//�T�u��ʃi���o�[�X�V
								CSR_POS_G15 = 0x00;						//�J�[�\���\���ʒu�𖼏̂̐擪��
								GAMEN_NO = 15;
								GAMEN_disp();							//��ʕ\��
							}
							else if (MLD_100_GNO == 20) {				//�T���v���^�f�[�^�Ή�
								if (MLD_100_FLG == 0xaa) {
									MLD_100_GNO = 9;					//�T�u��ʃi���o�[�X�V
								}
								else if (MLD_100_FLG == 0xbb) {
									MLD_100_GNO = 19;					//�T�u��ʃi���o�[�X�V
								}
								else {
									MLD_100_GNO = 0;					//�T�u��ʃi���o�[�X�V
								}
								CSR_POS_G15 = 0x00;						//�J�[�\���\���ʒu�𖼏̂̐擪��
								GAMEN_NO = 15;
								GAMEN_disp();							//��ʕ\��
							}
							else if(MLD_100_GNO != 00) {				//�^�Ǘ��f�[�^�߂菈��
								MLD_100_GNO--;							//�T�u��ʃi���o�[�X�V
								CSR_POS_G15 = 0x00;						//�J�[�\���\���ʒu�𖼏̂̐擪��
								GAMEN_NO = 15;
								GAMEN_disp();							//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
//V06n							if(MLD_100_GNO < 0x09 && MLD_100_FLG == 0xaa ) {	//�^�Ǘ��f�[�^�߂菈��
							if ( ( MLD_100_GNO <  9 && MLD_100_FLG == 0xaa ) ||
								 ( MLD_100_GNO < 19 && MLD_100_FLG == 0xbb ) )	 {	//�^�Ǘ��f�[�^�߂菈��
								MLD_100_GNO++;							//�T�u��ʃi���o�[�X�V
								CSR_POS_G15 = 0x00;						//�J�[�\���\���ʒu�𖼏̂̐擪��
								GAMEN_NO = 15;
								GAMEN_disp();							//��ʕ\��
							}
							else {										//�T���v���^�f�[�^�Ή�		2014/04/16
								if (SEQ_PAR_151 & cBIT3) {				//�T���v���^�L���H
									if (MLD_100_GNO < 20) {
										MLD_100_GNO = 20;				//�T�u��ʃi���o�[�X�V
										CSR_POS_G15 = 0x00;				//�J�[�\���\���ʒu�𖼏̂̐擪��
										GAMEN_NO = 15;
										GAMEN_disp();					//��ʕ\��
									}
									else if (MLD_100_GNO == 20) {
										MLD_100_GNO = 21;				//�T�u��ʃi���o�[�X�V
										CSR_POS_G15 = 0x00;				//�J�[�\���\���ʒu�𖼏̂̐擪��
										GAMEN_NO = 15;
										GAMEN_disp();					//��ʕ\��
									}
								}
							}
							break;
						case E_key_sw4:			//key code SW4
							CSR_FLG_CNT = 1;
							CSR_FLG = 5;
							CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);	//�J�[�\���ړ�
//?	CALL	SPATH_DISP			;/* ���Y�ݒ�̃~�X�t�B�[�h�\�����̃X�y�[�X�\��   */
							Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
							Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
							Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5:			//key code SW5
						case E_key_sw6:			//key code SW6
							SW56_gamen_15();					//�^�ް���ʁ@SW56����
							break;

						case E_key_sw7:
							if (SEQ_026_SV & cBIT4) {				//�d�l�ݒ�No.165		2014/08/22
								MLD_100_GNO = 20;
								CSR_POS_G15 = 0xaa;					//�J�[�\���\���ʒu�����݂̔ԍ��̈ʒu��

								GAMEN_NO = 15;
								GAMEN_disp();						//��ʕ\��
							}
							break;
					}
					break;
			}
			break;

		case E_dstg_name:		//�f�[�^�ݒ�[�^�ԍ�����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					KATname_inp();								//�^���� ���͏���
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							CSR_POS_G15 = 0x55;					//�J�[�\���\���ʒu�����݂̔ԍ��̈ʒu��
							disp_stg_sel = E_dstg_kata;			//�f�[�^�ݒ�[�^�ԍ�]��
							GAMEN_NO = 15;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2(�Ȃ�)
						case E_key_sw3:			//key code SW3(�Ȃ�)
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							KATname_cls();						//�^���� ��������

							SW16data_onset(0xff, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							KAT_data_write();					//�^�ް� ����

							disp_stg_sel = E_dstg_kata;			//�f�[�^�ݒ�[�^�ԍ�]��
							GAMEN_NO = 15;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
//						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
//							SW16data_onset(0x00, 8);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_memo:		//�f�[�^�ݒ�[�^�ԍ�����]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					KATname_inp();								//�^���� ���͏���
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_kata;			//�f�[�^�ݒ�[�^�ԍ�]��
							GAMEN_NO = 15;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2(�Ȃ�)
						case E_key_sw3:			//key code SW3(�Ȃ�)
						case E_key_sw4:			//key code SW4(�Ȃ�)
							break;

						case E_key_sw5:			//key code SW5
							KATname_cls();						//�^���� ��������

							SW16data_onset(0xff, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							MEMO_data_write();					//�^�ް� �ӏ���

							disp_stg_sel = E_dstg_kata;			//�f�[�^�ݒ�[�^�ԍ�]��
							GAMEN_NO = 15;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
//						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
//							SW16data_onset(0x00, 8);							//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_mmon:		//�f�[�^�ݒ�[�����e�i���X���j�^]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_ksel;			//�f�[�^�ݒ�[�@�\�I��]��
							GAMEN_NO = 14;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_PAR_051 & cBIT15) {			//V06n
								disp_stg = 03;						//�V�X�e���ݒ��ʂ�
								disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
								GAMEN_NO = 31;
								GAMEN_disp();						//��ʕ\��
							}
							break;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#else
						case E_key_sw7:			//key code SW7	//V06n
							disp_stg_sel = E_dstg_Lang;		//�f�[�^�ݒ�[����ݒ�]��
							WINDOW_NO = 24;
							WIN_gamen_disp();				//�E�C���h�E��ʕ\��
							break;
#endif
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw6_down) {	//key code SW6(������)
						SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else if(KEY_DATA_CODE == E_key_sw6){	//key code SW6
						SEI_test_out_sw6();						//���Y�ݒ�ýďo�͏���(SW6)

						SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_ksel:		//�f�[�^�ݒ�[�@�\�I��]��
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode(�Ȃ�)
					Key_Ent_sv();								//�ݒ�l�̊m��			// V05j
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��
							GAMEN_NO = 13;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3(�Ȃ�)
							break;
						case E_key_sw4:			//key code SW4
							if (SEQ_PAR_051 & cBIT15) {			//V06n
								disp_stg = 03;						//�V�X�e���ݒ��ʂ�
								disp_stg_sel = E_ystg_init;			//���ѐݒ�[��{]��
								GAMEN_NO = 31;
								GAMEN_disp();						//��ʕ\��
							}
							break;
					}
					break;

				case E_key_sw56_mode:		//SW5/6 key mode
					if(KEY_DATA_CODE == E_key_sw5_down ) {	//key code SW5(������)
						SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					else if(KEY_DATA_CODE == E_key_sw5){	//key code SW5
						SWchg_ent();							//SW CHG �f�[�^ ENT

						SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
						Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
					}
					break;
			}
			break;

		case E_dstg_cntc:		//�f�[�^�ݒ�[���Ēl�C��]	//V06b
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(�Ȃ�)
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							CAR_mkssi_set();					//�P�ʐ؊�  V01u
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_PAR_107 & BIT_0){			//�@�\�I��1(�^�ް��Ǘ��@1:�L)
								disp_stg_sel = E_dstg_kata;		//�f�[�^�ݒ�[�^�ԍ�]��
								CSR_POS_G15 = 0xff;				//�J�[�\���\���ʒu�����݂̔ԍ��̈ʒu��
								GAMEN_NO = 15;
								GAMEN_disp();					//��ʕ\��
							}
							break;
						case E_key_sw4:			//key code SW4
							disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��
							GAMEN_NO = 13;
							GAMEN_disp();						//��ʕ\��
							break;
					}
					break;
			}
			break;

		case E_dstg_Lang:		//�f�[�^�ݒ�[����ݒ�]			//V06m
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1(�Ȃ�)
//V06n							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
//V06n							GAMEN_NO = 17;
							disp_stg_sel = E_dstg_mmon;			//�f�[�^�ݒ�[�����e�i���X���j�^]��
							GAMEN_NO = 13;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							break;
						case E_key_sw3:			//key code SW3
							break;
						case E_key_sw4:			//key code SW4
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr1:		//���Y[��ƊJ�n1]��ƎҺ��ނ̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();						//�ݒ�l�̊m��

					disp_stg_sel = E_dstg_wkstr2;		//���Y[��ƊJ�n2]��
					WINDOW_NO = 43;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							disp_stg_sel = E_dstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 44;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr2:		//���Y[��ƊJ�n2]��ƎҺ��ނ̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_WORKER_COD = SV0_WORKER_COD_BAK;	//�O�ɖ߂�

							disp_stg_sel = E_dstg_wkstr1;		//���Y[��ƊJ�n1]��
							WINDOW_NO = 42;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_dstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 44;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr3:		//���Y[��ƊJ�n3]���Ժ��ނ̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��

					disp_stg_sel = E_dstg_wkstr4;		//���Y[��ƊJ�n4]��
					WINDOW_NO = 45;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							disp_stg_sel = E_dstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 46;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr4:		//���Y[��ƊJ�n4]���Ժ��ނ̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_ORDER_COD = SV0_ORDER_COD_BAK;	//�O�ɖ߂�

							disp_stg_sel = E_dstg_wkstr3;		//���Y[��ƊJ�n3]��
							WINDOW_NO = 44;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							disp_stg_sel = E_dstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 46;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr5:		//���Y[��ƊJ�n5]�v�搔�̓���		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��

					disp_stg_sel = E_dstg_wkstr6;		//���Y[��ƊJ�n6]��
					WINDOW_NO = 47;
					WIN_gamen_disp();					//�E�C���h�E��ʕ\��

					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//�����
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//��Ǝ҂���H
								SEI_Worker_STP();					//���Y�Ǘ���ƏI��
							}

							CSR_TBL_POS_NOW = KAT_RD_CSR_POS;
							KAT_data_read();					//�^�f�[�^�Ǎ�

							SEI_Worker_SET();					//����ް��m��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_wkstr6:		//���Y[��ƊJ�n6]�v�搔�̊m�F		V06c
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							SV0_PLAN_CNT = SV0_PLAN_CNT_BAK;		//�O�ɖ߂�

							disp_stg_sel = E_dstg_wkstr5;		//���Y[��ƊJ�n5]��
							WINDOW_NO = 46;
							WIN_gamen_disp();					//�E�C���h�E��ʕ\��

							SW16data_onset(0xff, 7);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6	//YES
							if (SV_WORKER_ENT_FLG == 0x5AA5) {		//��Ǝ҂���H
								SEI_Worker_STP();					//���Y�Ǘ���ƏI��
							}

							CSR_TBL_POS_NOW = KAT_RD_CSR_POS;
							KAT_data_read();					//�^�f�[�^�Ǎ�

							SEI_Worker_SET();					//����ް��m��

							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							DANseq_alloff();						//�i���p�V�[�P���X�n�e�e
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_CamAtCal:		//�f�[�^�ݒ�[�J���o�͎������Z]			SIT4-MC
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					i = SV_TBL_POS_NOW;
					Key_Ent_sv();								//�ݒ�l�̊m��
					if (SV_buff[i].SUB_NO==129) {
//2014/12/23						RELEASE_POS_2_AGL_CAL(SV0_RELE_POS);		//�������񉉎Z			2014/09/01
						RELEASE_POS_2_AGL_CAL(cnv_inch_mm(SV0_RELE_POS,0));		//�������񉉎Z			2014/12/23
					}
					else if (SV_buff[i].SUB_NO==131) {
//2014/12/23						SEND_POS_2_AGL_CAL(SV0_SEND_POS);			//�������񉉎Z			2014/09/01
						SEND_POS_2_AGL_CAL(cnv_inch_mm(SV0_SEND_POS,0));		//�������񉉎Z			2014/12/23
					}
					SEQ_PAR_058 &= ~cBIT2;						//�J���������Z���ʐݒ�s�N���A
					PV0_CAMATCAL_MES1 = 0;			//���b�Z�[�W�N���A
					PV0_CAMATCAL_MES2 = 0;			//���b�Z�[�W�N���A
					PV0_CAMATCAL_MES3 = 0;			//���b�Z�[�W�N���A
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;

						case E_key_sw2:			//key code SW2
							break;

						case E_key_sw3:			//key code SW3
							break;

						case E_key_sw4:			//key code SW4
							break;

						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5	//NO
							break;

						case E_key_sw6:			//key code SW6	//YES
							if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
								Cam_auto_copy();
							}
							SW16data_onset(0xff, 8);			//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_slatwt:		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��		SIT4-MC
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					Key_Ent_sv();								//�ݒ�l�̊m��
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2
							if(EJE_GAMEN_NON != 0xff){
								disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
								GAMEN_NO = 19;
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw3:			//key code SW3
							if(SEQ_018_SV & 0x0700) {
								disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
								GAMEN_NO = 20;
								GAMEN_disp();						//��ʕ\��
							}
							else {
								if(SEQ_018_SV & 0x0800) {
									disp_stg_sel = E_dstg_tms3;			//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
									GAMEN_NO = 68;
									GAMEN_disp();						//��ʕ\��
								}
							}
							break;
						case E_key_sw4:			//key code SW4
							if(ROT_GAMEN_NON != 0xff){
								if( ROT1_GAMEN_NON == 00 ) {		//���[�^���J���P�`�W �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 24;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
									else {
										GAMEN_NO = 21;
										disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
									}
								}
								else{								//���[�^���J���X�`�P�U �L
									if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
										GAMEN_NO = 25;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]��
									}
									else {
										GAMEN_NO = 22;
										disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
									}
								}
								GAMEN_disp();						//��ʕ\��
							}
							break;
						case E_key_sw7:			//key code SW7
							if (SEQ_024_SV & BIT_10) {				//�d�l�ݒ�No.139
								disp_stg_sel = E_dstg_ksin;			//�f�[�^�ݒ�[���U�@�\�ݒ�]��
								GAMEN_NO = 101;
								GAMEN_disp();						//��ʕ\��
							}
							break;

						case E_key_sw5:			//key code SW5
							break;

						case E_key_sw6:			//key code SW6
							SVSW_tbl_enzan();						//�r�u�r�v�e�[�u���A�h���X���Z
							SWchg_ent();							//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O

							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

		case E_dstg_rep_fix:		//�f�[�^�ݒ�[�J��Ԃ��^���̈�]
			switch(KEY_DATA_MODE) {
				case E_key_ent_mode:		//ENT key mode
					j = CSR_TBL_POS_NOW;						//2014/10/09
					Key_Ent_sv();								//�ݒ�l�̊m��
					Make_Rep_Bit_Inf();							//���s�[�g�s����BIT����
					if (j >= 1) {								//�J�[�\���ʒu�����̈�H				2014/10/09
						PV0_FMOTSET_MES1 = 0;					//���b�Z�[�W�N���A
					}
					break;

				case E_key_sw14_mode:		//SW1�`4 key mode
				case E_key_sw56_mode:		//SW5/6 key mode
					switch(KEY_DATA_CODE) {
						case E_key_sw1:			//key code SW1
							disp_stg_sel = E_dstg_init;			//�f�[�^�ݒ�[��{]��
							GAMEN_NO = 17;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw2:			//key code SW2(�Ȃ�)
							disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
							GAMEN_NO = 28;
							GAMEN_disp();						//��ʕ\��
							break;
						case E_key_sw3:			//key code SW3
							disp_stg_sel = E_dstg_mcg;			//�f�[�^�ݒ�[���[�V�����O���t]��
							GAMEN_NO = 29;
							GAMEN_disp();						//��ʕ\��

							GRAPH_INIT();						//�O���t�`�揉������
							GRAPH_DISP();						//�O���t�`�揈��
							break;
						case E_key_sw4:			//key code SW4
							Data_sel_cam();						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
							break;
						case E_key_sw7:			//key code SW7
							break;

						case E_key_sw5:			//key code SW5
							SEI_test_out_sw5();						//���Y�ݒ�ýďo�͏���(SW5)

							SW16data_onset(0xff, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6:			//key code SW6
							SVSW_tbl_enzan();						//�r�u�r�v�e�[�u���A�h���X���Z
							SWchg_ent();							//SW CHG �f�[�^ ENT
							KAT_DATCHG_FLG = 0xff;					//�^�f�[�^�ύX�t���O
							Make_Rep_Bit_Inf();						//���s�[�g�s����BIT����

							SW16data_onset(0xff, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw5_down:	//key code SW5(������)
							SW16data_onset(0x00, 7);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;

						case E_key_sw6_down:	//key code SW6(������)
							SW16data_onset(0x00, 8);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
							Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
							break;
					}
					break;
			}
			break;

	}
}


/*
********************************************************************************
*  Module Name:		Data_sel_cam
*  Function Name:	���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-06
********************************************************************************
*/
void	Data_sel_cam(void)
{
	UNs		i;

	i = GAMEN_NO_CAM;

	if(CAM_GAMEN_NON == 00){					//���ݸސݒ� �L ?
//2014/08/28		if( i <= 19 || i >= 23 ){				//�O��f�[�^�L��
//2014/09/01		if( ( i != 53 ) && ( i <= 19 || i >= 23 ) ) {		//�O��f�[�^�L��
		if( ( i != 24 ) && ( i != 25 ) && ( i != 53 ) && ( i <= 19 || i >= 23 ) ) {		//�O��f�[�^�L��
			if(00 != EJE_check()){				//�G�W�F�N�^�L���`�F�b�N
				i = 19;
				disp_stg_sel = E_dstg_tms1;		//�f�[�^�ݒ�[�G�W�F�N�^]��
				goto DATA_SEL_800;
			}
		}
		else if( i == 53 ){						//2014/08/28	SIT4-MC
			if(SEQ_PAR_151 & cBIT8){			//�X���C�h�����ҋ@�@�\�L���`�F�b�N
				i = 53;
				disp_stg_sel = E_dstg_slatwt;	//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
				goto DATA_SEL_800;
			}
		}
		else if( i == 20 ){
 			if(00 != MIS_check()){				//�~�X�t�B�[�h�L���`�F�b�N
				i = 20;
				disp_stg_sel = E_dstg_tms2;		//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
				goto DATA_SEL_800;
			}
		}
		else{
			if( 00 != ROT1_check() ) {			//���[�^���J���P�`�W�L���`�F�b�N
				if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
					i = 24;
				}
				else {
					i = 21;
				}
				disp_stg_sel = E_dstg_tms4;		//�f�[�^�ݒ�[���[�^���J��1]��
				goto DATA_SEL_800;

			}
			else if( 00 != ROT2_check() ) {		//���[�^���J���X�`�P�U�L���`�F�b�N
				if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
					i = 25;
				}
				else {
					i = 22;
				}
				disp_stg_sel = E_dstg_tms5;		//�f�[�^�ݒ�[���[�^���J��2]
				goto DATA_SEL_800;
			}
		}

//�J��(��ު��/н̨���/۰�ض�)
		if(00 != EJE_check()){					//�G�W�F�N�^�L���`�F�b�N
			i = 19;
			disp_stg_sel = E_dstg_tms1;			//�f�[�^�ݒ�[�G�W�F�N�^]��
		}
		else if(SEQ_PAR_151 & cBIT8){			//�X���C�h�����ҋ@�@�\�L���`�F�b�N			2014/08/28	SIT4-MC
			i = 53;
			disp_stg_sel = E_dstg_slatwt;		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��
		}
 		else if(00 != MIS_check()){				//�~�X�t�B�[�h�L���`�F�b�N
			i = 20;
			disp_stg_sel = E_dstg_tms2;			//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
		}
		else if( 00 != ROT1_check() ) {			//���[�^���J���P�`�W�L���`�F�b�N
			if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
				i = 24;
			}
			else {
				i = 21;
			}
			disp_stg_sel = E_dstg_tms4;			//�f�[�^�ݒ�[���[�^���J��1]��
		}
		else if( 00 != ROT2_check() ) {			//���[�^���J���X�`�P�U�L���`�F�b�N
			if (SEQ_PAR_151 & cBIT10) {			//�i�p�L						2014/09/01
				i = 25;
			}
			else {
				i = 22;
			}
			disp_stg_sel = E_dstg_tms5;			//�f�[�^�ݒ�[���[�^���J��2]
		}
		else{
			return;
		}

DATA_SEL_800:
		GAMEN_NO = i;
		GAMEN_disp();						//��ʕ\��
	}
}


/*
********************************************************************************
*  Module Name:		SHARCH_gamen_15
*  Function Name:	�������͎��̉�ʈړ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-05
********************************************************************************
*/
void	SHARCH_gamen_15(void)
{
	UNs		i, j;

//V06n	if( PV_SEARCH_C15 < 11 ||
//V06n		MLD_100_FLG == 0xaa ) {				//�^�Ǘ� 1�`100���L��
	if( PV_SEARCH_C15 < 11 ||
		MLD_100_FLG != 0 ) {				//�^�Ǘ� 1�`100���L��

		i = PV_SEARCH_C15 / 10;
		j = PV_SEARCH_C15 % 10;
		if(j == 0){							//���܂肪�O�̎��͂P���Ȃ���ʔԍ��ł��B
			i --;
		}
		MLD_100_GNO = i;
		CSR_POS_G15 = 0xaa;					//�J�[�\���\���ʒu�����݂̔ԍ��̈ʒu��

		GAMEN_NO = 15;
		GAMEN_disp();						//��ʕ\��
	}
}


/*
********************************************************************************
*  Module Name:		SW56_gamen_15
*  Function Name:	�^�ް���ʁ@SW56����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-05
********************************************************************************
*/
void	SW56_gamen_15(void)
{
	UNs		i, j, *bf_p;
	UNs		bit;

//SW56_G15_100:
	if(CSR_CNT != 00){							//���ق��Ȃ��Ƃ��͏������Ȃ�

		if( CSR_FLG_CNT == 1 ) {				//����Ӱ�ށH
			return;								//Yes
		}


//V06p
		i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
		if ( (0xa0 <= i) && (i <= 0xa9) ) {
			i &= 0x000f;
			bit = BIT_0;
		}
		else if ( (0xab <= i) && (i <= 0xb4) ) {
			i -= 0xab;
			i &= 0x000f;
			bit = BIT_0;
		}
		else {
			bit = 0;
		}
		if (bit) {
			bit<<=i;
			if (PV0_KATRD_BIT & bit) {					//��]�����s��v
				return;
			}
		}


		if(KEY_DATA_CODE == E_key_sw5) {		//key code SW5
			i = CSR_buff[CSR_TBL_POS_NOW].XY_POS;
			i >>= 4;
			i &= 0x003f;
			if( i >= 20 ){								//�������̓��[�h�H
//SW56_G15_150:											//��������
				i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
				i -= 0xab;
				i += 1;										//0ABH�`0A4H = 1�`�P�O�ɑΉ����Ă��邩��
				i += (MLD_100_GNO * 10);					//�^�Ǘ��ԍ����P�O�{���Č^�Ǘ��ԍ����׍H����

				if ( (i<201) || (SEQ_PAR_151 & cBIT4) ) {		//2014/04/17
					if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
						PV_MLDNO1_F0 = i;							//�^�ް� ������ʗp�̌^�ԍ�
	
						bf_p = KAT_sv_memo_tbl[i];					//�^�ް� �����̈�̱��ڽ�ð���
						memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//�^�ް� ������ʗp�̌^����
	
						disp_stg_sel = E_dstg_memo;					//�f�[�^�ݒ�[�^�ԍ�����]��
						GAMEN_NO = 23;
						GAMEN_disp();								//��ʕ\��
					}
				}
			}
			else if(PV_MLDMES_C1 == 00){					//���b�Z�[�W�\����
//SW56_G15_110:
				i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
				i &= 0x000f;
				i += 1;										//0A0H�`0A9H = 1�`�P�O�ɑΉ����Ă��邩��
				i += (MLD_100_GNO * 10);					//�^�Ǘ��ԍ����P�O�{���Č^�Ǘ��ԍ����׍H����

				if ( (i<201) || (SEQ_PAR_151 & cBIT4) ) {		//2014/04/17
					if ( SEQ_PAR_058 & BIT_5 ) {							//�p�X���[�h��v		2017/11/06
						PV_MLDNO1_F0 = i;							//�^�ް� ������ʗp�̌^�ԍ�
	
						bf_p = KAT_sv_name_tbl[i];					//�^�ް� ���̗̈�̱��ڽ�ð���
						memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//�^�ް� ������ʗp�̌^����
	
						disp_stg_sel = E_dstg_name;					//�f�[�^�ݒ�[�^�ԍ�����]��
						GAMEN_NO = 16;
						GAMEN_disp();								//��ʕ\��
					}
				}
			}
			else{											//YES �K���Ǎ�����
//SW56_G15_320:
				if (SEQ_PAR_113 & BIT_9) {					//�d�l�ݒ�No.135�uKOMTRAX�v&& �@�\�I��1�u�^�ް��Ǘ��v		V06c
					KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

					SEI_Worker_GET();
					disp_stg_sel = E_dstg_wkstr1;			//���Y[��ƊJ�n1]��
					WINDOW_NO = 42;
					WIN_gamen_disp();						//�E�C���h�E��ʕ\��

					SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//���܂ł̍�ƎҺ��ޑޔ�
					SV0_ORDER_COD_BAK	= SV0_ORDER_COD;		//���܂ł̒��Ժ��ޑޔ�
					SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//���܂ł̌v�搔�ޔ�
				}
				else {
					KAT_data_read();							//�^�f�[�^�Ǎ�
				}
			}
		}
//SW56_G15_200:
		else{									//key code SW6
			i = CSR_buff[CSR_TBL_POS_NOW].XY_POS;
			i >>= 4;
			i &= 0x003f;
			if( i < 20 ){								//�^�f�[�^�@���[�h�H
				if(PV_MLDMES_C1 == 00 &&				//���b�Z�[�W�\����
					00 == (SEQ_PAR_107 & BIT_9) ) {		//�Ǎ����̎��������@�\�L��

					if(KAT_DATCHG_FLG != 0){			//�ް��ύX�L��H
//SW56_G15_220:
						PV_MLDMES_C1 = 5;				//���b�Z�[�W�\��
						SWchg_disp();					//�r�v�f�[�^���@�\��
						SW56_dncara_disp(37, 7);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
						SW56_dncara_disp(38, 8);		//SW56���i��׸���SW�̈�֊i�[(SW56���i��׸�,�\���ʒu)
						Under_grph();											//���i�̃O���t�B�b�N�Z�b�g
						Lcd_line(00, 12, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
						Lcd_line(01, 12, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
						Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
					}
					else{
//SW56_G15_320:
						if (SEQ_PAR_113 & BIT_9) {					//�d�l�ݒ�No.135�uKOMTRAX�v&& �@�\�I��1�u�^�ް��Ǘ��v		V06c
							KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

							SEI_Worker_GET();
							disp_stg_sel = E_dstg_wkstr1;			//���Y[��ƊJ�n1]��
							WINDOW_NO = 42;
							WIN_gamen_disp();						//�E�C���h�E��ʕ\��

							SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//���܂ł̍�ƎҺ��ޑޔ�
							SV0_ORDER_COD_BAK	= SV0_ORDER_COD;		//���܂ł̒��Ժ��ޑޔ�
							SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//���܂ł̌v�搔�ޔ�
						}
						else {
							KAT_data_read();					//�^�f�[�^�Ǎ�
						}
					}
				}
				else{								//�^�ް��������݁��Ǎ���
//SW56_G15_300:
					if ( (PV_MLDNO1_F1<201) || (SEQ_PAR_151 & cBIT4) ) {		//2014/04/17
						PV_MLDNO1_F0 = PV_MLDNO1_F1;				//�^�ް� ������ʗp�̌^�ԍ�
						bf_p = KAT_sv_name_tbl[PV_MLDNO1_F0];		//�^�ް� ���̗̈�̱��ڽ�ð���
						memcpy_word(&PV_MLDNO2_F0[0], bf_p, 8);		//�^�ް� ������ʗp�̌^����

						KAT_data_write();							//�^�ް� ����
//SW56_G15_320:
						if (SEQ_PAR_113 & BIT_9) {					//�d�l�ݒ�No.135�uKOMTRAX�v&& �@�\�I��1�u�^�ް��Ǘ��v		V06c
							KAT_RD_CSR_POS = CSR_TBL_POS_NOW;

							SEI_Worker_GET();
							disp_stg_sel = E_dstg_wkstr1;			//���Y[��ƊJ�n1]��
							WINDOW_NO = 42;
							WIN_gamen_disp();						//�E�C���h�E��ʕ\��

							SV0_WORKER_COD_BAK	= SV0_WORKER_COD;	//���܂ł̍�ƎҺ��ޑޔ�
							SV0_ORDER_COD_BAK	= SV0_ORDER_COD;	//���܂ł̒��Ժ��ޑޔ�
							SV0_PLAN_CNT_BAK	= SV0_PLAN_CNT;		//���܂ł̌v�搔�ޔ�
						}
						else {
							KAT_data_read();							//�^�f�[�^�Ǎ�
						}
					}
				}
			}
//SW56_G15_500:
//SW56_G15_900:
			SW16data_onset(0xff, KEY_DATA_CODE+2);				//�r�v�P�`�U�̔��]�w����s��(������ް�,SW�ʒu)
			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
		}
	}
//SW56_G15_END:
	return;
}


/*
********************************************************************************
*  Module Name:		MEMO_data_write
*  Function Name:	�^�ް� �ӏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	MEMO_data_write(void)
{
	UNs		*bf_p;
	UNi		i;

	i = PV_MLDNO1_F0;
	bf_p = KAT_sv_memo_tbl[i];					//�^�ް� �����̈�̱��ڽ�ð���
	memcpy_word(bf_p, &PV_MLDNO2_F0[0], 8);		//�^�ް� ������ʗp�̌^����
	if (i == PV_MLDNO1_F1) {									//�ӓo�^�͌��^�H	2015/11/26 if���ǉ�
		memcpy_word(&KAT_MEMO_CHR[0], &PV_MLDNO2_F0[0], 8);		//�^�ް� ������ʗp�̌^����			�^�ް����ɕۑ�		2014/09/03
	}

	FRAM_csum_set();							//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	FRAM_KAT_csum_set();						//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬

}


/*
********************************************************************************
*  Module Name:		KAT_data_read
*  Function Name:	�^�ް� �Ǎ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-05
********************************************************************************
*/
UNs		KAT_data_read_com(UNs no)				//2016/04/22
{
	UNs		i, *bf_p;
	UNs		err;

	err = 0xff;
	i = no;

	kata_load(i, &FRAM_KAT_TOP);				//�^�f�[�^��FROM����Ǎ���

	if(00 == (SEQ_PAR_078 & BIT_0 ) ){			//�^�ް��@BCC����H

		err = 0;

		Dat_mm_inch_chg2();						//2015/01/28

		if ( 9 < SV_HAN_P ) {	//V06n
			SV_HAN_P = 0;
		}
		if ( 9 < SV_HAN_S ) {	//V06n
			SV_HAN_S = 0;
		}

		if ( 2 < SV_OVLD_SEL ) {					//2014/06/03
			SV_OVLD_SEL = 0;
		}

		if ( 2 < SV_LWLM_SEL ) {					//2014/06/03
			SV_LWLM_SEL = 0;
		}

		SV0_MOT_FIX = 0;							//��葬�x�u���O�N���A			2014/10/09

		if (GMN_PAR048 != 1) {					//�׏d����L���H			2015/01/15
			/* �׏d���䖳�� */
			SV_MOTOBJ_INF1		= 0;
			SV_1DANPRS_SRV		= 0;            /* 1�i�ږڕW�׏d */
			SV_2DANPRS_SRV		= 0;            /* 2�i�ږڕW�׏d */
			SV_3DANPRS_SRV		= 0;            /* 3�i�ږڕW�׏d */
			SV_4DANPRS_SRV		= 0;            /* 4�i�ږڕW�׏d */
			SV_5DANPRS_SRV		= 0;            /* 5�i�ږڕW�׏d */
			SV_6DANPRS_SRV		= 0;            /* 6�i�ږڕW�׏d */
			SV_7DANPRS_SRV		= 0;            /* 7�i�ږڕW�׏d */
			SV_8DANPRS_SRV		= 0;            /* 8�i�ږڕW�׏d */
			SV_9DANPRS_SRV		= 0;            /* 9�i�ږڕW�׏d */
			SV_10DANPRS_SRV		= 0;            /* 10�i�ږڕW�׏d */
			SV_KAJOBJ_HAB		= 0;			/* �׏d�����͈� */
		}

		PV_TOTLC1_B3 = PV_TOTLC1_B3_KAT;			//�g�[�^���J�E���^�P�����l���R�s�[
		PV_LOTCT1_B4 = PV_LOTCT1_B4_KAT;			//���b�g�J�E���^�P�����l���R�s�[
		PV_TOTLC2_B31 = PV_TOTLC2_B31_KAT;			//���g�p
		PV_LOTCT2_B41 = PV_LOTCT2_B41_KAT;			//���b�g�J�E���^�Q�����l���R�s�[

		bf_p = KAT_sv_name_tbl[i];					//�^�ް� ���̗̈�̱��ڽ�ð���
		memcpy_word(bf_p, &KAT_NAME_CHR[0], 8);		//�^�ް� ������ʗp�̌^����				�^�ް����̌^���̂��g�p		2014/09/03
		memcpy_word(&PV_MLDNO2_F1[0], bf_p, 8);		//�^�ް� ������ʗp�̌^����

		bf_p = KAT_sv_memo_tbl[i];					//�^�ް� �����̈�̱��ڽ�ð���
		memcpy_word(bf_p, &KAT_MEMO_CHR[0], 8);		//�^�ް� ������ʗp�̌^����				�^�ް����̌^�������g�p		2014/09/03
		memcpy_word(&PV_MLDNO3_F1[0], bf_p, 8);		//�^�ް� ������ʗp�̌^����

		PV_MLDNO1_F1 = i;							//�^�ް� ������ʗp�̌^�ԍ�

//		MOV	SVSW_CHG_FLG,10111111B			;
		SVSW_CHG_FLG = 0xff;
		ONOFF_sub();								//�d�l�L�薳���ɂ����ؐ���

		mmon_sel_chk();								//Ӱ��݂̕����I������
		mmon_trans_get();							//��]�����ɂ���ް��̎擾

		ROTTO_chk();								//ۯĶ��� ���� ����

		SURA_CHG_LST = 0;							//�^�f�[�^��ǂ񂾌�ɐ���ɓ��삵�Ȃ�
		SET_SPM_LST = 0;							//

		CAM_name_ref();								//۰�ضєėp�I����ʂɑΉ������і��̂̍X�V

		KAT_read_sura_chk();						//�^�f�[�^�Ǎ��ݎ��X���C�h�ݒ�l�`�F�b�N

		FRAM_csum_set();							//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
		FRAM_KAT_csum_set();						//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬

		KAT_DATCHG_FLG = 0;							//�^�f�[�^�Ǎ���̓f�[�^�ύX�t���O�N���A
	}

	return(err);
}

void	KAT_data_read(void)
{
	UNs		i, *bf_p;
	UNs		err;

	i = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
	i &= 0x000f;
	i += 1;										//0A0H�`0A9H = 1�`�P�O�ɑΉ����Ă��邩��
	i += (MLD_100_GNO * 10);					//�^�Ǘ��ԍ����P�O�{���Č^�Ǘ��ԍ����׍H����

	err = KAT_data_read_com(i);						//�^�f�[�^�Ǎ���

	if (err==0) {
		disp_stg_sel = E_dstg_init;					//�f�[�^�ݒ�[��{]��
		GAMEN_NO = 17;
		GAMEN_disp();								//�^�f�[�^�Ǎ���̓f�[�^�ݒ��ʂ͎����I�ɖ߂�	
	}

}


/*
********************************************************************************
*  Module Name:		KAT_data_write
*  Function Name:	�^�ް� ����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-06
********************************************************************************
*/
void	KAT_data_write(void)
{
	UNs		i, *bf_p;
	UNs		name[8], memo[8];

	i = PV_MLDNO1_F0;							//���݂̌^�ԍ� ����

	bf_p = KAT_sv_name_tbl[i];					//�^�ް� ���̗̈�̱��ڽ�ð���
	memcpy_word(bf_p, &PV_MLDNO2_F0[0], 8);		//�^�ް� ������ʗp�̌^����

	if (i == PV_MLDNO1_F1) {									//�����݂͌��^�H	2015/11/26 if���ǉ�
		memcpy_word(&KAT_NAME_CHR[0], &PV_MLDNO2_F0[0], 8);		//�^�ް� ������ʗp�̌^����			�^�ް����ɕۑ�		2014/09/03
		bf_p = KAT_sv_memo_tbl[i];								//�^�ް� �����̈�̱��ڽ�ð���
		memcpy_word(&KAT_MEMO_CHR[0], bf_p, 8);					//�^�ް� ������ʗp�̌^����
	}
	else {											//2015/11/26
		memcpy_word(name, &KAT_NAME_CHR[0], 8);					//���^�̖��̂���
		memcpy_word(memo, &KAT_MEMO_CHR[0], 8);					//���^�̃�������
		memcpy_word(&KAT_NAME_CHR[0], &PV_MLDNO2_F0[0], 8);		//�^�ް� ������ʗp�̌^����
		bf_p = KAT_sv_memo_tbl[i];								//�^�ް� �����̈�̱��ڽ�ð���
		memcpy_word(&KAT_MEMO_CHR[0], bf_p, 8);					//�^�ް� ������ʗp�̌^����
	}

	PV_TOTLC1_B3_KAT = PV_TOTLC1_B3;			//�g�[�^���J�E���^�P�����l���R�s�[
	PV_LOTCT1_B4_KAT = PV_LOTCT1_B4;			//���b�g�J�E���^�P�����l���R�s�[
	PV_TOTLC2_B31_KAT = PV_TOTLC2_B31;			//���g�p
	PV_LOTCT2_B41_KAT = PV_LOTCT2_B41;			//���b�g�J�E���^�Q�����l���R�s�[

	kata_save(i, &FRAM_KAT_TOP);				//�^�f�[�^��FROM�֊i�[

	if (i != PV_MLDNO1_F1) {						//2015/11/26
		memcpy_word(&KAT_NAME_CHR[0], name, 8);		//���^�̖��̂���		2015/11/26
		memcpy_word(&KAT_MEMO_CHR[0], memo, 8);		//���^�̃�������		2015/11/26
	}

	FRAM_csum_set();							//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	FRAM_KAT_csum_set();						//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬

	KAT_DATCHG_FLG = 0;							//�^�f�[�^������̓f�[�^�ύX�t���O�N���A

}


/*
********************************************************************************
*  Module Name:		KAT_read_sura_chk
*  Function Name:	�^�f�[�^�Ǎ��ݎ��X���C�h�ݒ�l�`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-06
********************************************************************************
*/
void	KAT_read_sura_chk(void)
{

U4b	wl0,bf;//2014-08-11 koma

	if(SLDTUN_RNA_SEL != 0x5a){//2014-08-11 koma �Ʊ�ײ�ޒ����ł͎g�p���Ȃ�

		if(SEQ_024_SV & BIT_6){						//�ײ�ގ������߂�������������Ȃ�

			//�������ݒ�l(�X���C�h�������߁@���Y�ݒ�)�����
			if( SV_ATUOS0_D9 > SV_UPDATA_A21 ||		//�ݒ�l > ��� �H
				SV_ATUOS0_D9 < SV_DNDATA_A21 ) {	//�ݒ�l < ���� �H

				SV_ATUOS0_D9 = SV_UPDATA_A21;		//�ݒ�l = ���
			}

			//�������ݒ�l(�X���C�h�������߁@�i���P�ݒ�)�����
			if( SV_ATUOS1_D9 > SV_UPDATA_A21 ||		//�ݒ�l > ��� �H
				SV_ATUOS1_D9 < SV_DNDATA_A21 ) {	//�ݒ�l < ���� �H

				SV_ATUOS1_D9 = SV_UPDATA_A21;		//�ݒ�l = ���
			}

			//�������ݒ�l(�X���C�h�������߁@�i���Q�ݒ�)�����
			if( SV_ATUOS2_D9 > SV_UPDATA_A21 ||		//�ݒ�l > ��� �H
				SV_ATUOS2_D9 < SV_DNDATA_A21 ) {	//�ݒ�l < ���� �H	

				SV_ATUOS2_D9 = SV_UPDATA_A21;		//�ݒ�l = ���
			}
		}
	}else{
		//2014-08-11 �Ʊ�ײ�ޒ����ł�������......
			if (SV_POINT_A1 == 0) {//�ݒ��ް������_���� *1000 =>�����_�R��
				wl0 = 1000;
			}
			else if (SV_POINT_A1 == 1) {//�ݒ��ް������_1�� *100 =>�����_�R��
				wl0 = 100;
			}
			else if (SV_POINT_A1 == 2) {//�ݒ��ް������_2�� *10  =>�����_�R��
				wl0 = 10;
			}
			else {
				wl0 = 1;//�����_�R���ݒ�
			}

//	koma 2014-08-18
//			bf=SV_ATUOS0_D9*wl0;			
//			if ( (bf > SV0_RNAPOS_MAXO) || (bf < SV0_RNAPOS_MINO) ) {//�@�B���,�@�B�����ȊO
//				SV_ATUOS0_D9 = SV0_RNAPOS_MAXO / wl0;
//			}
//			bf=SV_ATUOS1_D9*wl0;
//			if ( (bf > SV0_RNAPOS_MAXO) || (bf < SV0_RNAPOS_MINO) ) {//�@�B���,�@�B�����ȊO
//				SV_ATUOS1_D9 = SV0_RNAPOS_MAXO / wl0;
//			}
//			bf=SV_ATUOS2_D9*wl0;
//			if ( (bf > SV0_RNAPOS_MAXO) || (bf < SV0_RNAPOS_MINO) ) {//�@�B���,�@�B�����ȊO
//				SV_ATUOS2_D9 = SV0_RNAPOS_MAXO / wl0;
//			}

			//2014-08-18 �@�B����A��������_�C�n�C�g����A�����ɕύX
			if( SEQ_016_SV & BIT_6 ) {							//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)	2015/03/05
				bf = cnv_inch_mm(SV_ATUOS0_D9, 0);
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS0_D9 = cnv_mm_inch(SV0_DAIHAI_LNG2O*100, 0);
				}
				bf = cnv_inch_mm(SV_ATUOS1_D9, 0);
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS1_D9 = cnv_mm_inch(SV0_DAIHAI_LNG2O*100, 0);
				}
				bf = cnv_inch_mm(SV_ATUOS2_D9, 0);
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS2_D9 = cnv_mm_inch(SV0_DAIHAI_LNG2O*100, 0);
				}
			}
			else {
				bf=SV_ATUOS0_D9*wl0;
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS0_D9 = SV0_DAIHAI_LNG2O*100 / wl0;
				}
				bf=SV_ATUOS1_D9*wl0;
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS1_D9 = SV0_DAIHAI_LNG2O*100 / wl0;
				}
				bf=SV_ATUOS2_D9*wl0;
				if ( (bf > (SV0_DAIHAI_LNG2O*100)) || (bf < (SV0_DAIHAI_LNG1O*100)) ) {//�_�C�n�C�g���,�_�C�n�C�g�����ȊO
					SV_ATUOS2_D9 = SV0_DAIHAI_LNG2O*100 / wl0;
				}
			}
	}
}


/*
********************************************************************************
*  Module Name:		NAME_csr_mng
*  Function Name:	���̉�ʃJ�[�\������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	NAME_csr_mng(void)
{
	UNs	csr_pos;

	if(GAMEN_NO == 12){							//�J�����̓��͉�ʁH
		if( PV_CAMNA1_C1 & BIT_0 ) {			//�J�����̑I��
			if(NAME_CHG_FLG != 0xff){			//���̕ύX���H
				goto NAME_500;					//���̏�Ԃł͉����ł��ړ���
			}
		}
		else{									//�ėp�o�͑I�𒆂͈ړ����Ȃ�
			return;
		}
	}
//NAME_CSR_200:
	csr_pos = CSR_buff[CSR_TBL_POS_NOW].XY_POS;	//���ق�X,Y��

	if( CSR_FLG == E_key_up ) {					//key code �� �H
		if( 3 == (csr_pos & 0x000f) ) {			//���݂̃J�[�\���ʒu���R�s�ڂ��������ɂ͈ړ����Ȃ�
			return;
		}
	}
	else if( CSR_FLG == E_key_left ) {			//key code ��
		if( 0x13 == (csr_pos & 0x03ff) ) {		//���݂̃J�[�\���ʒu��??�ړ����Ȃ�
			return;
		}
	}
NAME_500:
	CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);			//�J�[�\���ړ�

}


/*
********************************************************************************
*  Module Name:		KATname_inp
*  Function Name:	�^���� ���͏���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	KATname_inp(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[16], *wk_p;


	wk_p = &wk[0];
	dst_p = &PV_MLDNO2_F0[0];
	xy_no = CSR_buff[0].XY_POS;

	if(NAME_CHG_FLG != 0xff){						//���̕ύX���H
		memset_word(dst_p, E_AS_SPSP, 8);			//�J�����̃G���A�W���N���A
		NAME_CHG_FLG = 0xff;						//���̕ύX��
		KATNAME_INP_CNT = 0;						//���̓J�E���^������

													//���ٕ\��(���])
		CSR_disp_on(xy_no);							//����ʔ��]
	}

	if(KATNAME_INP_CNT < 14){						//���̓J�E���^�I�[�o�H
		memcpy_word((UNs *)&wk[0], dst_p, 8);		//�J�����̃G���A �R�s�[(��۰בΉ�)

		wk_p += KATNAME_INP_CNT;					//�f�[�^�i�[
		*wk_p = CSR_buff[CSR_TBL_POS_NOW].YOBI1;	//�J�����̃L�����N�^�R�[�h�Ǎ�

		memcpy_word(dst_p, (UNs *)&wk[0], 8);		//�J�����̃G���A �R�s�[(��۰בΉ�)

		KATNAME_INP_CNT++;							//���̓J�E���^�{�P
		KATname_ref(xy_no, dst_p);					//�J�����̃��t���b�V��
	}
}


/*
********************************************************************************
*  Module Name:		KATname_cls
*  Function Name:	�^���� ��������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	KATname_cls(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[16], *wk_p;


	wk_p = &wk[0];
	dst_p = &PV_MLDNO2_F0[0];
	xy_no = CSR_buff[0].XY_POS;

	memcpy_word((UNs *)&wk[0], dst_p, 8);			//�J�����̃G���A �R�s�[(��۰בΉ�)

	if(NAME_CHG_FLG != 0xff){						//���̕ύX���H
													//���ٕ\��(���])
		CSR_disp_on(xy_no);							//����ʔ��]

		NAME_CHG_FLG = 0xff;						//���̕ύX��
		KATNAME_INP_CNT = NAME_leng_chk(wk_p, 14);	//���̂̓��͕��������`�F�b�N
	}

	if(KATNAME_INP_CNT != 00){
		KATNAME_INP_CNT --;							//���̓J�E���^-1
	}

	wk_p += KATNAME_INP_CNT;						//�O���͂��߰��ر
	*wk_p = E_AS_SP;
	memcpy_word(dst_p, (UNs *)&wk[0], 8);			//�J�����̃G���A �R�s�[(��۰בΉ�)

	KATname_ref(xy_no, dst_p);						//�J�����̃��t���b�V��

}


/*
********************************************************************************
*  Module Name:		KATname_ref
*  Function Name:	�J�����̃��t���b�V��
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*			:		�������ޥ�i�[���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	KATname_ref(UNs xy_no, UNs *g_adr_p)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	Disp_moji(xy_no, g_adr_p, 0 );				//�����\��
#else
	disp_moji_s_color(
		CSR_buff[0].M_LEN,						/* ��׸��			*/
		CSR_buff[0].X_POS,						/* ���o��X�ʒu		*/
		CSR_buff[0].Y_POS,						/* ���o��Y�ʒu		*/
		CSR_buff[0].C_COL,						/* �����F			*/
		CSR_buff[0].B_COL2,						/* �w�i�F			*/
		CSR_buff[0].SIZE,						/* ��������			*/
		g_adr_p,									/* �����i�[���ڽ	*/
		LCD_VRAM								/* �\�����			*/
		);
#endif
}


/*
********************************************************************************
*  Module Name:		CSR_disp_on(��:CSR_DISP_ON�CCSR_DISP_ON_OFF)
*  Function Name:	����ʔ��]
*  Input	:		�\����(b0�`b3:�s,b4�`b9:��,b10�`b15:������)
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
void	CSR_disp_on(UNs xy_no )
{

	disp_memnot(xy_no, &LCD_WORK2[0][0][0]);	//�\���p�̈�̎w���ް��𔽓]
	Lcd_cr(1, xy_no, &LCD_WORK2[0][0][0]);		//��גP�ʕ\��

}


/*
********************************************************************************
*  Module Name:		NAME_leng_chk
*  Function Name:	���̂̓��͕��������`�F�b�N
*  Input	:		�����ޯ̧����ڽ
*					������
*
*  Return	: 		�����̌��ʒ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-21
********************************************************************************
*/
UNs		NAME_leng_chk(UNb *dst_p, UNs len)
{
	UNs	i;

	i = len;
	dst_p += len;
	dst_p --;

	for( ; len > 0 ; len-- ){
		if(*dst_p == E_AS_SP){
			dst_p--;
			i--;
		}
		else{
			break;
		}
	}

	return(i);
}


/*
********************************************************************************
*  Module Name:		CAMname_inp
*  Function Name:	�J������ ���͏���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-26
********************************************************************************
*/
void	CAMname_inp(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[10], *wk_p;

	wk_p = &wk[0];
	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	if(CSR_buff[CSR_TBL_POS_NOW].YOBI1 != 0xff){			//�ŏ㕔�J�[�\���R�[�h?

		if(00 == CAMname_inp_chk() ){						//�J�����̓��͉`�F�b�N
			if(NAME_CHG_FLG != 0xff){						//���̕ύX���H
				memset_word(dst_p, E_AS_SPSP, 4);			//�J�����̃G���A�W���N���A
				NAME_CHG_FLG = 0xff;						//���̕ύX��
				CAMNAME_INP_CNT = 0;						//���̓J�E���^������

															//���ٕ\��(���])
				CSR_disp_on(xy_no);							//����ʔ��]
			}
			if(CAMNAME_INP_CNT < 8){						//���̓J�E���^�I�[�o�H

				memcpy_word((UNs *)&wk[0], dst_p, 4);		//�J�����̃G���A �R�s�[(��۰בΉ�)

				wk_p += CAMNAME_INP_CNT;					//�f�[�^�i�[
				*wk_p = CSR_buff[CSR_TBL_POS_NOW].YOBI1;	//�J�����̃L�����N�^�R�[�h�Ǎ�

				memcpy_word(dst_p, (UNs *)&wk[0], 4);		//�J�����̃G���A �R�s�[(��۰בΉ�)

				CAMNAME_INP_CNT++;							//���̓J�E���^�{�P

				KATname_ref(xy_no, dst_p);					//�J�����̃��t���b�V��

			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CAMname_cls
*  Function Name:	�J������ ��������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-26
********************************************************************************
*/
void	CAMname_cls(void)
{
	UNs		*dst_p, xy_no;
	UNb		wk[10], *wk_p;

	wk_p = &wk[0];
	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	if(00 == CAMname_inp_chk() ){						//�J�����̓��͉`�F�b�N
		memcpy_word((UNs *)&wk[0], dst_p, 4);			//�J�����̃G���A �R�s�[(��۰בΉ�)

		if(NAME_CHG_FLG != 0xff){						//���̕ύX���H
														//���ٕ\��(���])
			CSR_disp_on(xy_no);							//����ʔ��]

			NAME_CHG_FLG = 0xff;						//���̕ύX��
			CAMNAME_INP_CNT = NAME_leng_chk(wk_p, 8);	//���̂̓��͕��������`�F�b�N
		}

		if(CAMNAME_INP_CNT != 00){
			CAMNAME_INP_CNT --;							//���̓J�E���^-1
		}

		wk_p += CAMNAME_INP_CNT;						//�O���͂��߰��ر
		*wk_p = E_AS_SP;
		memcpy_word(dst_p, (UNs *)&wk[0], 4);			//�J�����̃G���A �R�s�[(��۰בΉ�)

		KATname_ref(xy_no, dst_p);					//�J�����̃��t���b�V��
	}
}


/*
********************************************************************************
*  Module Name:		CAMname_inp_chk
*  Function Name:	�J�����̓��͉`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		00 �� ����
					00 �� �ُ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-26
********************************************************************************
*/
UNi		CAMname_inp_chk(void)
{
	UNs		i;
	UNi		ref;

	ref = 0;							//����
	i = PV_CAMNA1_C1;

	if( i & 0xfffe ){					//�J���o�͐���ȊO�������Ă��邩
		ref = 0xff;						//�ُ�
	}
	else if( 00 == (i & 0x0001) ){		//�J���o�͐��䂪�I�΂�Ă��邩�H
		ref = 0xff;						//�ُ�
	}

	return(ref);
}


/*
********************************************************************************
*  Module Name:		CAMname_touroku
*  Function Name:	�J�����̓o�^
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-26
********************************************************************************
*/
void	CAMname_touroku(void)
{
	UNs		*bf_p;
	UNi		i;

	CAMNAME_INP_CNT = 0;							//���̓J�E���^������

	i = CAM_NAME_NO;								//�ύX�J�����̔ԍ��Ǎ�
	bf_p = Camcsr_Name_Tbl[i];						//���[�^���J�����̱̂��ڽ�ð���
	memcpy_word(bf_p, &PV_CAMNAM_C1[0], 4);			//�J������

	if(NAME_CHG_FLG == 0xff){						//���̕ύX
		memcpy_word(&PV_CAMNAM_C2[0], &PV_CAMNAM_C1[0], 4);		//�J������

		bf_p = Camcsr_Name_TblSV[i];				//���[�^���J�����̱̂��ڽ�ð���
		memcpy_word(bf_p, &PV_CAMNAM_C1[0], 4);		//�J������

	}

	bf_p = Camcsr_Name_Tbl1[i];						//���[�^���J���P�ėp�I����ʂ̱��ڽ�ð���
	*bf_p = PV_CAMNA1_C1;

	FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	KAT_DATCHG_FLG = 0xff;							//�^�f�[�^�ύX�t���O
	SVSW_CHG_FLG |= BIT_5;							//���ް�(CAM)�v��
	NAME_CHG_FLG = 0;								//���̕ύX���N���A
}


/*
********************************************************************************
*  Module Name:		CAMname_sw_ent
*  Function Name:	�ėp�o�͑I��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-26
********************************************************************************
*/
void	CAMname_sw_ent(void)
{
	UNi 	cnt, cnt2;
	UNs		*dst_p, *src_p, xy_no, b_d0;

	dst_p = &PV_CAMNAM_C1[0];
	xy_no = CSR_buff[0].XY_POS;

	CAMNAME_INP_CNT = 0;								//���̓J�E���^������

	//�ėp�o�͑I���r�v���`�F�b�N�i���������Ă�����j
	PV_CAMNA1_C1 <<= 1;									//�ړ�
	b_d0 = BIT_0;
	for(cnt=16, cnt2=0 ; cnt > 0 ; cnt--){
		if( PV_CAMNA1_C1 & b_d0 ){
			cnt2 ++;
		}
		b_d0 <<= 1;
	}
	if(cnt2 != 1){
		PV_CAMNA1_C1 = BIT_0;
	}

	//�ėp���I�΂�Ă�����̂����ėp�L�����N�^��]��
	b_d0 = BIT_0;
	for(cnt=0 ; cnt < 16 ; cnt++){
		if( PV_CAMNA1_C1 & b_d0 ){
			src_p = Camcsr_Name_TblSW[cnt];
			memcpy_word(dst_p, src_p, 4);				//�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[
			KATname_ref(xy_no, dst_p);					//�J�����̃��t���b�V��

			NAME_CHG_FLG = 0;							//���̕ύX���N���A
			CAMNAME_INP_CNT = 0;						//���̓J�E���^������

			CSR_sw56_disp();							//�r�v�T�U�L�����N�^�\��
			Under_grph();								//���i�̃O���t�B�b�N�Z�b�g

			cnt = SW_CNT;
			while(cnt--){
				SWchg_disp_pv();						//�r�v�b�g�f�f�[�^�\����������
			}
			Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
			Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��
			break;
		}
		b_d0 <<= 1;
	}
}


/*
********************************************************************************
*  Module Name:		CAM_name_ref(��:KATA_READ_CAMNAME)
*  Function Name:	۰�ضєėp�I����ʂɑΉ������і��̂̍X�V
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-30
********************************************************************************
*/
void	CAM_name_ref(void)
{
	UNs		*src_p, *dst_p, b_d0, b_d1;
	UNi		cnt, cnt2;

	for(cnt=0 ; cnt < 16 ; cnt++){						//۰�ض�1�`16
		src_p = Camcsr_Name_Tbl1[cnt];
		b_d0 = *src_p;
		if(b_d0 == BIT_0){								//�ёI���H
			dst_p = Camcsr_Name_Tbl[cnt];				//YES
			src_p = Camcsr_Name_TblSV[cnt];
			memcpy_word(dst_p, src_p, 4);				//�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[
		}
		else{											//�ėp���I�΂�Ă�����̂����ėp�L�����N�^��]��
			b_d1 = BIT_0;								//�єėp�I���������
			for(cnt2=0 ; cnt2 < 16 ; cnt2++){
				if( b_d0 & b_d1 ){
					dst_p = Camcsr_Name_Tbl[cnt];
					src_p = Camcsr_Name_TblSW[cnt2];
					memcpy_word(dst_p, src_p, 4);		//�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[
					break;
				}
				b_d1 <<= 1;
			}
		}
	}
}


/*
********************************************************************************
*  Function Name:	�J���o�͎������Z���ʂ��J���ݒ�ɔ��f����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:		ON:2014/08/27
********************************************************************************
*/
void	Cam_auto_copy(void)
{
	UNs		*src;
	UNs		chk, cambit;

	chk = Cam_auto_chk();
	if (chk) {
		SEQ_PAR_058 |= cBIT2;			//�ݒ�s��
		PV0_CAMATCAL_MES1 = 10;			//���b�Z�[�W�\��
		PV0_CAMATCAL_MES2 = 11;			//���b�Z�[�W�\��
		PV0_CAMATCAL_MES3 = 0;			//���b�Z�[�W�\��
		return;
	}

	if (SV0_RELE_CAM) {
		src = &SV_RCLSTA11_C17;
		src += (SV0_RELE_CAM-1) * 4;

		*src = SV0_RELE_SNO0;			//�����[�X�J���I���s��
		src++;
		*src = SV0_RELE_AGL0;			//�����[�X�J���I���p�x
		src++;
		*src = SV0_RELE_SNO1;			//�����[�X�J���I�t�s��
		src++;
		*src = SV0_RELE_AGL1;			//�����[�X�J���I�t�p�x

		cambit = cBIT0;					//2014/09/01
		cambit <<= (SV0_RELE_CAM-1);
		SEQ_038_SV |= cambit;			//�ΏۃJ������ɐݒ�
	}
	
	if (SV0_SEND_CAM) {
		src = &SV_RCLSTA11_C17;
		src += (SV0_SEND_CAM-1) * 4;

		*src = SV0_SEND_SNO0;			//����J���I���s��
		src++;
		*src = SV0_SEND_AGL0;			//����J���I���p�x
		src++;
		*src = SV0_SEND_SNO1;			//����J���I�t�s��
		src++;
		*src = SV0_SEND_AGL1;			//����J���I�t�p�x

		cambit = cBIT0;					//2014/09/01
		cambit <<= (SV0_SEND_CAM-1);
		SEQ_038_SV |= cambit;			//�ΏۃJ������ɐݒ�
	}
	
	if (SV0_TIMING_CAM) {
		src = &SV_RCLSTA11_C17;
		src += (SV0_TIMING_CAM-1) * 4;

		*src = SV0_TIMING_SNO0;			//�^�C�~���O�J���I���s��
		src++;
		*src = SV0_TIMING_AGL0;			//�^�C�~���O�J���I���p�x
		src++;
		*src = SV0_TIMING_SNO1;			//�^�C�~���O�J���I�t�s��
		src++;
		*src = SV0_TIMING_AGL1;			//�^�C�~���O�J���I�t�p�x

		cambit = cBIT0;					//2014/09/01
		cambit <<= (SV0_TIMING_CAM-1);
		SEQ_038_SV |= cambit;			//�ΏۃJ������ɐݒ�
	}

	PV0_CAMATCAL_MES1 = 0;				//���b�Z�[�W�\��
	PV0_CAMATCAL_MES2 = 0;				//���b�Z�[�W�\��
	PV0_CAMATCAL_MES2 = 12;				//���b�Z�[�W�\��

	FRAM_csum_set();								//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	KAT_DATCHG_FLG = 0xff;							//�^�f�[�^�ύX�t���O
	SVSW_CHG_FLG |= (BIT_5+BIT_3);					//���ް�(CAM)�v��
}


/*
********************************************************************************
*  Function Name:	�J���o�͎������Z���ʂ𔽉f����J���ݒ���`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:		ON:2014/08/27
********************************************************************************
*/
UNs		Cam_auto_chk(void)
{
	UNs		chk, no;
	UNs		agl0, agl1, CamAgl;

	chk = 0;

	//�J���ݒ�d���`�F�b�N
	if ( (SV0_RELE_CAM == SV0_SEND_CAM) ||
		 (SV0_RELE_CAM == SV0_TIMING_CAM) ||
		 (SV0_SEND_CAM == SV0_TIMING_CAM) ) {

		chk = 0xff;
	}

	//�J���ݒ����`�F�b�N
	no = CAM_AUTO_LIMIT(SV0_RELE_CAM);
	if (no != SV0_RELE_CAM) {
		chk = 0xff;
	}
	no = CAM_AUTO_LIMIT(SV0_SEND_CAM);
	if (no != SV0_SEND_CAM) {
		chk = 0xff;
	}
	no = CAM_AUTO_LIMIT(SV0_TIMING_CAM);
	if (no != SV0_TIMING_CAM) {
		chk = 0xff;
	}

	//�������Z�������ʂ��X���C�h����͈͓����`�F�b�N
	if( SEQ_050_SV & (cBIT1+cBIT2) ) {						//���]�@�U�q�@�H
		agl0 = SV_TAIKIKAKU_SRV;							//�ҋ@�_
		if( SEQ_050_SV & BIT_1 ) {							//���]�@�H
			agl1 = SV_DNAREA_JUDG;
		}
		else {												//�U�q�@�H
			agl1 = (1800 - SV_TAIKIKAKU_SRV) + 1800;
		}

		CamAgl = SV0_RELE_AGL0 * 10;						//�����[�X�J���I���p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
		CamAgl = SV0_RELE_AGL1 * 10;						//�����[�X�J���I�t�p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
		CamAgl = SV0_SEND_AGL0 * 10;						//����J���I���p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
		CamAgl = SV0_SEND_AGL1 * 10;						//����J���I�t�p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
		CamAgl = SV0_TIMING_AGL0 * 10;						//�^�C�~���O�J���I���p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
		CamAgl = SV0_TIMING_AGL1 * 10;						//�^�C�~���O�J���I�t�p�x
		if ( (CamAgl < agl0) || (agl1 < CamAgl) ) {
			chk = 0xff;
		}
	}

	if ( PV0_CAMATCAL_FLG != (cBIT0+cBIT1) ) {				//�����[�X�����A���荂���̐ݒ���͂��邩�H			2014/09/12
		chk = 0xff;
	}

	return(chk);
}


/*
********************************************************************************
*  Function Name:	���s�[�g�s����BIT����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:		ON:2014/09/04
********************************************************************************
*/
void	Make_Rep_Bit_Inf(void)
{
	UNs		rep_bit, cnt, wbit;

	if ( (SV_MOTREP_STGS > 10) || (SV_MOTREP_STGE > 10) )	return;

	if ( (SV_MOTREP_STGS == 0) ||						//�J�n�s��=0
		 (SV_MOTREP_STGS > SV_MOTREP_STGE) ||			//�J�n�s��>�I���s��
		 ((SEQ_032_SV & cBIT13) == 0) ) {				//�J��Ԃ��u�؁v
		/* �J�n�s�� = 0 */
		/* �J�n�s�� > �I���s�� */
		SV0_MOT_REP = 0;
	}
	else {
		if (SV_MOTREP_STGS == SV_MOTREP_STGE) {
			/* �J�n�s�� = �I���s�� */
			rep_bit = cBIT0 << (SV_MOTREP_STGS-1);
			SV0_MOT_REP = rep_bit;					//REP�s��BIT���
		}
		else {
			/* �J�n�s�� < �I���s�� */
			wbit = cBIT0 << (SV_MOTREP_STGS-1);
			rep_bit = 0;
			for (cnt=0; cnt<=(SV_MOTREP_STGE - SV_MOTREP_STGS); cnt++, wbit<<=1) {
				rep_bit |= wbit;
			}
			SV0_MOT_REP = rep_bit;					//REP�s��BIT���
		}
	}


}


/*
********************************************************************************
*  Function Name:	�f�[�^�ؑցimm��inch�j
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura		ON:2015/01/20
********************************************************************************
*/
void	Dat_mm_inch_chg2(void)
{
	if (SEQ_016_SV & BIT_6) {						//�d�l�ݒ�No.7  inch�I��
		if (SV_KAT_MM_INCH == 1) {					//�Ǎ��񂾃f�[�^��inch�ʏ�f�[�^�H
			if (SEQ_016_SV & BIT_7) {				//�d�l�ݒ�No.8  �����x
				KAT_keta_up();						//inch3 -> inch4
			}
			else {
				//�d�l�ݒ�inch�ʏ큁�f�[�^inch�ʏ�
				//�������Ȃ��ėǂ�
			}
		}
		else if (SV_KAT_MM_INCH == 2) {				//�Ǎ��񂾃f�[�^��inch�����x�f�[�^�H
			if (SEQ_016_SV & BIT_7) {				//�d�l�ݒ�No.8  �����x
				//�d�l�ݒ�inch�����x���f�[�^inch�����x
				//�������Ȃ��ėǂ�
			}
			else {
				KAT_keta_down();					//inch4 -> inch3
			}
		}
		else {										//�Ǎ��񂾃f�[�^��mm
			KAT_mm_2_inch_all();					//mm -> inch3
			if (SEQ_016_SV & BIT_7) {				//�d�l�ݒ�No.8  �����x
				KAT_keta_up();						//inch3 -> inch4
			}
		}
	}
	else {											//�d�l�ݒ�No.7  mm�I��
		if (SV_KAT_MM_INCH == 1) {					//�Ǎ��񂾃f�[�^��inch�ʏ�f�[�^�H
			KAT_inch_2_mm_all();					//inch -> mm
		}
		else if (SV_KAT_MM_INCH == 2) {				//�Ǎ��񂾃f�[�^��inch�����x�f�[�^�H
			KAT_inch_2_mm_all();					//inch -> mm
			KAT_keta_down();						//�����_�ȉ�4�� -> 3��
		}
		else {										//�Ǎ��񂾃f�[�^��mm�f�[�^�̂Ƃ�
			//�d�l�ݒ�mm���f�[�^mm
			//�������Ȃ��ėǂ�
		}
	}
}


/*** END ***/
