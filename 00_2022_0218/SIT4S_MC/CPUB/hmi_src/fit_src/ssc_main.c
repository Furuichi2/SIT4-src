/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			��ʑ���̃��C������													*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-07
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
#include "dp_cpuab.h"							//DPRAM�Q�ƕϐ���`
#include "ssa_opram.h"							//OPRAM�Q�ƕϐ���`
#include "CPU_REG.h"							//SH7055 ڼ޽�
#include "ssc_ver1.h"
#include "ssc_addr.h"

/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void	IROCK_SHR(void);						//�C���^�[���b�N�f�[�^����
extern	void	IROCK_SHR_OUT(void);					//�C���^�[���b�N�f�[�^�����o��		2009/07/14
extern	void	SEISAN_INF_DISP(void);					//���Y��ʍs���\��
extern	void	RULET_GAMEN_DISP(void);					//���[���b�g��ʕ\��
extern	void	DEG_DISP(void);							//�p�x�\������

extern	void	DP_TRANS_SRV(void);
extern	void	DP_TRANS_SYS(void);
extern	void	DP_TRANS_MOT(void);
extern	void	DP_TRANS_SEQ(void);
extern	void	DP_TRANS_CAM(void);
extern	void	DP_TRANS_GEN(void);
extern	void	DP_GET_SENS	(void);
extern	void	DP_BACK_SENS(void);

extern	void	TIM_mcn_smp(void);

extern	void	COP1_MAIN_TLINK_DAT_REF();//2003-01-31

extern	void	KAT_ENB_GAMEN001_disp(void);			//GAMEN001�̎��Ɍ^�ް��Ǘ����L���ɂȂ����Ƃ��̉�ʍĕ\��
extern	void	Tlink1_mng(void);						//Tlink�ʐM����
extern	void	ADC_MAIN_MNG(void);						/* �������^�����l�`�h�m����		V01j */
extern	void	ADC_DATA_INI(void);						/* �`�c�b�f�[�^�C�j�V�������^�f�[�^�N���A����	SIT4 */

extern	UNs		swap_iw(void *);						//���ٌ`���̊i�[�ް����擾(word)

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
extern	void	Alltbl_set(void);
#else
extern	void	ASM_ALLTBL_SET_COL(void);
extern	void	Gamen_Init(void);
#endif

////extern	void	ASM_ET1_IP_BACK(void);					// V05j


/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	U2b	cop_enc_int_enb;
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		CB_SYS_PARAM279;				// /* V06m */
extern	UNs		GMN_PAR014;						// /* V01p */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNs		GMN_PAR011;						//�׏d�ڕW�ύX�㉺���l
extern	UNs		GMN_PAR040;						//�������\�����\�����		V05r
extern	UNs		GMN_PAR039;						//�������\��������������	V06h
extern	UNs		ALL_CHR_TBL;			//V06
extern	UNs		GAM_INF_TBL;			//V06
extern	UNs		GMN_PAR020;				//V06m
extern	UNs		SH2_MAIN_CLK;


/* �萔��` ---------------------------------------------------------- */
#define		E_DEBUG		0							//�f�o�b�O���[�h�w��(1:���ޯ��Ӱ��)
#define		E_DEBUG_1	0							//�f�o�b�O���[�h�w��

#define		BLK_MOT		0x0004						/* Ӱ���	��ۯ�		*/

/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	dsp_init1(void);						//�����݉����O1��
void	dsp_init2(void);						//�����݉�����1��
void	dsp_init3(void);						//�Ƽ���ް���M��1��
void	dsp_time_5ms(void);						//5ms���������

void	dsp_main(void);							//��ʕ\�����C�����[�`��
void	Mode_mng(void);							//�j�����R�[�h�ɂ�胂�[�h�Ǘ�
void	Any_mng(void);							//���X�L�����̌Œ菈��

void	keep_ry_smp(void);						//�L�[�v�����[�T���v�����O

void	GAIBU_cnt_rst(void);					//�O���J�E���^�N���A����
void	ONOFF_mng(void);						//�d�l �L�^�� �ɂ�鼰�ݽ����
void	ONOFF_sub(void);						//�d�l �L�^�� �ɂ����ؐ���
void	ROTTO_chk(void);						//ۯĶ��� ���� ����

void	CAMname_pon_read(void);					//�d���������̔ėp�і��̂̓Ǎ���
void	FRAM_csum_set(void);					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
void	FRAM_csum_chk(void);					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ�����
void	FRAM_KAT_csum_set(void);				//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬
void	FRAM_KAT_csum_chk(void);				//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ�����

void	Power_down(void);						//�p���[�_�E������
void	PV_CHANGE_hanten(void);					//���]�d�l���̂o�u�ϊ�
void	debug_dat_mng(void);					//���ޯ���ް��]������
void	his_dat_mng(void);						//�ُ헚���ް��]������
void	taikikaku_chg_mng(void);				//�ҋ@�p�ύX����
void	FURIKO_Cancel_mng(void);				// �U�q��\���w�߂̏���		/* V06p */
void	Gamen_Redisp_mng(void);					//��ʍĕ\������

void	Sampring_Disp(void);					//�T���v�����O�����\��
void	Trend_disp(void);						//�g�����h�����\��
void	Trend_stop(void);						//�g�����h�̒�~
void	KASIN_mark_Disp(void);					//���U������s���������\��
void	cop2_pvdata_sin(void);
void	real_kajyu_check(void);
void	SEIDOUSEINOU_mng(void);					// V05r
void	EcoMeter_Disp(void);					// V06
void	LANG_SEQ_OUT(void);						// V06m
void	HAN_MODE_SEQ_OUT(void);					// V06m
void	DIE_HEIGHT_OFFSET(void);				// V06m
void	FURIKO_SPEC_ON_OFF(void);				// V06m
void	SYSSET_SEQ_OUT(void);					// V06n
void 	EPM_data_rif(UNl ADD_BUF[][2], UNs *ADD_POI, UNl MON_BUF[][2], UNs *MON_POI, UNs tim);
void	kagen_disp(void);

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
extern	const	UNs *	Camcsr_Name_Tbl[20];
extern	const	UNs *	Camcsr_Name_Tbl1[16];
extern	const	UNs *	Camcsr_Name_TblSW[16];


/*
********************************************************************************
*  Module Name:		dsp_init1
*  Function Name:	�����݉����O1��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
//MC-KOMA void	dsp_init1(void)
//MC-KOMA{
//MC-KOMA	UNb	b1,b2;
//MC-KOMA	UNs	*poi, chk;
//MC-KOMA
//MC-KOMA	FRAM_csum_chk();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ�����
//MC-KOMA	FRAM_KAT_csum_chk();			//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ�����
//MC-KOMA
//MC-KOMA

//MC-KOMA	INTR_DAT_OFS = 0x140000;
//MC-KOMA	poi = (UNs *)E_INTROCK_PAT;
//MC-KOMA	poi += INTR_DAT_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		INTR_DAT_OFS = 0;
//MC-KOMA	}

//MC-KOMA	INIT_DAT_OFS = 0x140000;
//MC-KOMA	poi = (UNs *)E_FROM_INI_TOP;
//MC-KOMA	poi += INIT_DAT_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		INIT_DAT_OFS = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA	ALL_CHR_TBL_OFS = 0x140000;
//MC-KOMA	poi = &ALL_CHR_TBL;
//MC-KOMA	poi += ALL_CHR_TBL_OFS/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	if (chk == 0xffff) {
//MC-KOMA		ALL_CHR_TBL_OFS = 0;
//MC-KOMA	}

//MC-KOMA	GAM_INF_TBL_OFS = 0x140000 + 0x018000;
//MC-KOMA	poi = &GAM_INF_TBL;
//MC-KOMA	poi += GAM_INF_TBL_OFS/2;
//MC-KOMA	poi += 512/2;
//MC-KOMA	chk = *poi;
//MC-KOMA	chk &= 0xff00;
//MC-KOMA	if (chk != 0x5a00) {
//MC-KOMA		GAM_INF_TBL_OFS = 0;
//MC-KOMA	}
	// =============================================================
//MC-KOMA
//MC-KOMA
//MC-KOMA	EPM_TOTAL_INF = BIT_0;								//V06a
//MC-KOMA

//MC-KOMA#if ( SIT_TYPE_SEL == TYPE_SIT4)
//MC-KOMA	Gamen_Init();
//MC-KOMA#endif
//MC-KOMA
//MC-KOMA	OP_STATUS = OP_STATUS_REAL;							// V01e
//MC-KOMA	b1 = OP_STATUS_REAL;
//MC-KOMA	b2 = OP_STATUS_REAL;
//MC-KOMA	if ( (OP_STATUS != 0x55) && (OP_STATUS != 0x54) )
//MC-KOMA	{
//MC-KOMA		OP_STATUS = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA	MEM_ARI = MEM_ARI_REAL;								// V05h
//MC-KOMA	b1 = MEM_ARI_REAL;
//MC-KOMA	b2 = MEM_ARI_REAL;
//MC-KOMA	if ( MEM_ARI != 0xA5 )
//MC-KOMA	{
//MC-KOMA		MEM_ARI = 0;
//MC-KOMA	}
//MC-KOMA
//MC-KOMA}


void	dsp_init1(void)
{
	UNb	b1,b2;

	OP_STATUS = OP_STATUS_REAL;							// V01e
	b1 = OP_STATUS_REAL;
	b2 = OP_STATUS_REAL;
	if ( (OP_STATUS != 0x55) && (OP_STATUS != 0x54) )
	{
		OP_STATUS = 0;
	}

	MEM_ARI = MEM_ARI_REAL;								// V05h
	b1 = MEM_ARI_REAL;
	b2 = MEM_ARI_REAL;
	if ( MEM_ARI != 0xA5 )
	{
		MEM_ARI = 0;
	}

}


/*
********************************************************************************
*  Module Name:		dsp_init2
*  Function Name:	�����݉�����1��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	dsp_init2(void)
{
	UNs		sum_rem;

	sum_rem = 0;

//V06n
	SV0_RNAPOS_MINO = SV_RNAPOS_MINP;			//�@�B����
	SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP;			//�@�B���
	SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1;			//�_�C�n�C�g����
	SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2;			//�_�C�n�C�g���

	LANG_SEQ_OUT();									//V06m
	GENGO_chg(0xff);								//��Q�J����ؑւ�����

	SVSW_CHG_FLG = 0x0050;

	PODATA_SET_FLG = 0xff;
	OPdata_bak();									//��߼�݂̌��ʒu�ް��Ԋ�
	OPdata_set_kaku();								//��߼�� �ް��]������
	POSdata_set_kaku();								//�߼޼�Ű �ް��]������
	OPdata_sys_kaku();								//��߼�݂ɼ���ׂ��i�[

	ONOFF_sub();									//�d�l�L�薳���ɂ����ؐ���
	ROTTO_chk();									//ۯĶ��� ���� ����

	CAR_mkssi_set();								//�P�ʐ؊��f�[�^�i�[����
	CAMname_pon_read();								//�d���������̔ėp�і��̂̓Ǎ���

	mmon_sel_chk();									//Ӱ��݂̕����I������
	mmon_trans_get();								//��]�����ɂ���ް��̎擾

	taikikaku_chg_mng();							//�ҋ@�pGET		/* V01m_a */


	if ( (SV_LANGUAGE < 1) || (3 < SV_LANGUAGE) ) {	//V06n
		SV_LANGUAGE = 1;
		sum_rem = 0xff;
	}
	if ( 9 < SV_HAN_P ) {	//V06n
		SV_HAN_P = 0;
		sum_rem = 0xff;
	}
	if ( 9 < SV_HAN_S ) {	//V06n
		SV_HAN_S = 0;
		sum_rem = 0xff;
	}
	if ( (SV_KATTCH_SPD < 1) || (100 < SV_KATTCH_SPD) ) {	//V06p
		SV_KATTCH_SPD = 50;
		sum_rem = 0xff;
	}

	if (sum_rem) {
		FRAM_csum_set();
	}


	DP_TRANS_SRV();									/* ����  ��ۯ��]������	*/
	DP_TRANS_SYS();									/* ����� ��ۯ��]������	*/
	DP_TRANS_MOT();									/* Ӱ��� ��ۯ��]������	*/
	DP_TRANS_SEQ();									/* ���ݽ ��ۯ��]������	*/
	DP_TRANS_CAM();									/* ��    ��ۯ��]������	*/
	DP_TRANS_GEN();									/* ���_  ��ۯ��]������	*/

	DP_BACK_SENS();									/* �Ʊ�ݻBACKUP�l ����	*/

	SVSW_CHG_FLG	= 0x0000;						/* �v���׸� �ر			*/
	HS_SVCHG_B_TO_A	= 0x0000;						/* ���޼��� �����̈�ر	*/
	HS_SVCHG_A_TO_B	= 0x0000;						/* ���޼��� �Ǎ��̈�ر	*/

	SURA_CHG_LST = 0;								// V01l_c

/* V01  */
	SVB_DYHITO_POS = PV_DYHITO_POS;					// �����ʒu�ޯ����߂�C/B�֖߂�
	SVB_SLIDE_POS = PV_SLIDE_POS;					// ���Y�����ʒu�ޯ����߂�C/B�֖߂�

	SEQ_PAR_076 = PV_MLDNO1_F1;						// V05d

////	ASM_ET1_IP_BACK();								// V05j

}


/*
********************************************************************************
*  Module Name:		dsp_init3
*  Function Name:	�Ƽ���ް���M��1��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	dsp_init3(void)
{

#if	E_DEBUG								//�f�o�b�O���[�h�w��
	SEQ_PAR_101 = 0xff;					//���ޯ�ޗp
	SEQ_PAR_107 |= 0x01ff;				//���ޯ�ޗp
#endif

	kido_data_set();					//�P�x�\�� & �f�[�^�쐬

	CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
	disp_stg = 00;						//���Y���
	disp_stg_sel = E_sstg_init;			//���Y[��{]��
	GAMEN_NO = 1;
	GAMEN_disp();						//��ʕ\��

}


/*
********************************************************************************
*  Module Name:		dsp_time_5ms
*  Function Name:	5ms���������
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
#define		def_1min_cnt	12000	// = 60�b�^5ms
#define		def_1sec_cnt	200		// =  1�b�^5ms

//	"SIT4-MC��cpub�ł͌Ă΂�Ă��Ȃ�"
void	dsp_time_5ms(void)
{
	UNs		wk1,wk2;
	UNl		dwk1,dwk2;

	TIM_5MS_COUNT();						// ���b�g�J�E���^����

	TIM_mcn_smp();							//�����e�i���X���� ����

	ROTTO_chk();							//ۯĶ��� ���� ����

//2014-01	if(cop_enc_int_enb){//koma add
//2014-01		COP1_MAIN_TLINK_DAT_REF();//2003-01-31// SAITO 2004-05-21
//2014-01	}

	if(step_flick_cnt==0) {
		step_flick_cnt = 100;				// 500ms
		step_flick_flg ^= 0xffff;
	}
	else {
		step_flick_cnt--;
	}

//V01o	SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_T);		//�׏d�iTON�j(1word) �� �b�^�a			V01k
//V01p	SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_KEEP_T);		//�׏d�iTON�j(1word) �� �b�^�a			V01k
	if (GMN_PAR014 == 0)	//V01p
	{
		SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_T);		//�׏d�iTON�j(1word) �� �b�^�a
	}
	else
	{
		SVP_KAJYUU_PV1 = swap_iw(&CLO_LOAD_KEEP_T);		//�׏d�iTON�j(1word) �� �b�^�a
	}

	Dsp_PvWave_5ms();			//V05o


	/****************************************************/
	/*		�������\����			V05r				*/
	/****************************************************/
	if(sys_1min_cnt)	sys_1min_cnt--;
	if(sys_1min_cnt == 0)
	{
		sys_1min_cnt = def_1min_cnt;
		/* 1min ���� */

#if 0	//2011/09/12  �ύX  V06h
		if(PVTIM_seidouseinou_inter)	PVTIM_seidouseinou_inter--;			//�������\��������������
		if(PVTIM_seidouseinou_yokok)	PVTIM_seidouseinou_yokok--;			//�������\�����\�����
#endif
		if (SEQ_PAR_113 & BIT_0) {
			if(PV_INTER_TIM) {
				PV_INTER_TIM--;				//�������\��������������
			}
		}
	}

	/****************************************************/
	/*		�d�̓��j�^				V06					*/
	/****************************************************/
	if(sys_1sec_cnt)	sys_1sec_cnt--;
	if(sys_1sec_cnt == 0)
	{
		sys_1sec_cnt = def_1sec_cnt;
		/* 1sec ���� */

		EPM_SEC_2_MESMIN_ADD[0] += PVP_EPM_SYOHI;			//����d�͗� �ώZ(kWs)
		EPM_SEC_2_MESMIN_ADD[1] += PVP_EPM_KAISE;			//�񐶓d�͗� �ώZ(kWs)

		EPM_SEC_MESMIN_CNT += 1;

//V06b		if(EPM_SEC_MESMIN_CNT >= 60*5)					//5���ώZ�X�V
		if(EPM_SEC_MESMIN_CNT >= 60*1)					//1���ώZ�X�V
		{
			EPM_SEC_MESMIN_CNT = 0;

			EPM_data_rif(EPM_05MIN_BUF, &EPM_05MIN_POI, EPM_05MON_BUF, &EPM_05MON_POI, 05);
			EPM_data_rif(EPM_10MIN_BUF, &EPM_10MIN_POI, EPM_10MON_BUF, &EPM_10MON_POI, 10);
			EPM_data_rif(EPM_15MIN_BUF, &EPM_15MIN_POI, EPM_15MON_BUF, &EPM_15MON_POI, 15);
			EPM_data_rif(EPM_20MIN_BUF, &EPM_20MIN_POI, EPM_20MON_BUF, &EPM_20MON_POI, 20);
			EPM_data_rif(EPM_25MIN_BUF, &EPM_25MIN_POI, EPM_25MON_BUF, &EPM_25MON_POI, 25);
			EPM_data_rif(EPM_30MIN_BUF, &EPM_30MIN_POI, EPM_30MON_BUF, &EPM_30MON_POI, 30);
			EPM_data_rif(EPM_35MIN_BUF, &EPM_35MIN_POI, EPM_35MON_BUF, &EPM_35MON_POI, 35);
			EPM_data_rif(EPM_40MIN_BUF, &EPM_40MIN_POI, EPM_40MON_BUF, &EPM_40MON_POI, 40);
			EPM_data_rif(EPM_45MIN_BUF, &EPM_45MIN_POI, EPM_45MON_BUF, &EPM_45MON_POI, 45);
			EPM_data_rif(EPM_50MIN_BUF, &EPM_50MIN_POI, EPM_50MON_BUF, &EPM_50MON_POI, 50);
			EPM_data_rif(EPM_55MIN_BUF, &EPM_55MIN_POI, EPM_55MON_BUF, &EPM_55MON_POI, 55);
			EPM_data_rif(EPM_60MIN_BUF, &EPM_60MIN_POI, EPM_60MON_BUF, &EPM_60MON_POI, 60);

			EPM_SEC_2_MESMIN_ADD[0] = 0;							//����d�͗� 5�ώZ(kWs)�N���A
			EPM_SEC_2_MESMIN_ADD[1] = 0;							//�񐶓d�͗� 5�ώZ(kWs)�N���A

			EPM_GAMEN_RIF = 1;	//�����گ��			//V06b
		}
	}

	if(EPM_CLR_TIM)		EPM_CLR_TIM--;				//�d������ر����

}


void EPM_data_rif(UNl ADD_BUF[][2], UNs *ADD_POI, UNl MON_BUF[][2], UNs *MON_POI, UNs tim)
{
	UNs		wk1, wk2;
	UNl		dwk1, dwk2;

	ADD_BUF[*ADD_POI][0] = EPM_SEC_2_MESMIN_ADD[0];		//����d�͗� 1���ώZ(kWs)�i�[
	ADD_BUF[*ADD_POI][1] = EPM_SEC_2_MESMIN_ADD[1];		//�񐶓d�͗� 1���ώZ(kWs)�i�[

	*ADD_POI += 1;

//V06b	if (*ADD_POI >= (tim/5))
	if (*ADD_POI >= tim)
	{
		*ADD_POI = 0;
//V06b		for (wk1=0,dwk1=0,dwk2=0; wk1<(tim/5); wk1++)
		for (wk1=0,dwk1=0,dwk2=0; wk1<tim; wk1++)
		{
			dwk1 += ADD_BUF[wk1][0];
			dwk2 += ADD_BUF[wk1][1];
		}
		MON_BUF[*MON_POI][0] = dwk1;
		MON_BUF[*MON_POI][1] = dwk2;
		*MON_POI += 1;
//V06b		if(*MON_POI >= 20)
		if(*MON_POI >= 19)
		{
			*MON_POI = 0;
		}
//V06b		if (tim == SV_EPMCSR_TIM)	EPM_GAMEN_RIF = 1;	//�����گ��
	}
}

/*
********************************************************************************
*  Module Name:		dsp_main
*  Function Name:	��ʕ\�����C�����[�`��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*  �� ��	:FIT)�c�[		ON:2002-05-20
********************************************************************************
*/
void	dsp_main(void)
{
	Key_mng();					/* �����͂̊m��	*/
	Mode_mng();					/* �j�����R�[�h�ɂ�胂�[�h�Ǘ� */

	Any_mng();					/* ���X�L�����̌Œ菈�� */
}


	extern	short	DSET_SW_FLG;		// 2006-07-22 SAITO �\�t�g���ʉ�

/*
********************************************************************************
*  Module Name:		Mode_mng
*  Function Name:	�j�����R�[�h�ɂ�胂�[�h�Ǘ�
*  Input	:		�j�d�x�Q�c�`�s�`�Q�l�n�c�d
*					�j�d�x�Q�c�`�s�`�Q�b�n�c�d
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-15
********************************************************************************
*/
void	Mode_mng(void)
{
//	if (SEQ_PAR_103 & BIT_11)		return;		// ��������WIN�\����		V06
	if (SEQ_PAR_103 & BIT_11)		goto	MODE_CHG_SKIP;		// ��������WIN�\����		V06

//2006-07-22 SAITO	if( (PDDR ^ SET_KEY_LST) & BIT_10 ) {		/* ���Y��ʁ@�����@�f�[�^�ݒ��ʁ@�̐ؑւ�	*/
//2006-07-22 SAITO		SET_KEY_LST = PDDR;
	if( (DSET_SW_FLG ^ SET_KEY_LST) & BIT_10 ) {	/* ���Y��ʁ@�����@�f�[�^�ݒ��ʁ@�̐ؑւ�	*/
		SET_KEY_LST = DSET_SW_FLG;					//2006-07-22 SAITO �\�t�g���ʉ�
		if(SET_KEY_LST & BIT_10) {					//�f�[�^�ݒ��ʁ@�H
			disp_stg = 02;							//�f�[�^�ݒ���
			disp_stg_sel = E_dstg_init;				//�f�[�^�ݒ�[��{]��
			GAMEN_NO = 17;
		}
		else {										//No
			SEI_csr_ichk();							//���Y�J�[�\���ʒu������
			CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
			disp_stg = 00;							//���Y���
			disp_stg_sel = E_sstg_init;				//���Y[��{]��
			GAMEN_NO = 1;
		}
		GAMEN_disp();								//��ʕ\��
	}
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	else if(KEY_DATA_MODE == E_key_sw7_mode){	/* ���Y��ʁ@�����@�^�i���ʁ@�̐ؑւ�	*/
		if(00 == (SET_KEY_LST & BIT_10)){			//���Y��ʁH
			if(disp_stg == 00){						//���Y���?
				DAN_csr_ichk();						//�i��J�[�\���ʒu������
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00){
					DAN_KEY_FLG = 0xff;				//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
					disp_stg = 01;					//�i����
					disp_stg_sel = E_kstg_init;		//�i��[��{]��
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10) {	// V01r
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//��ʕ\��
				}
			}
			else if(disp_stg == 01) {				//�^�i����?
				SEI_csr_ichk();						//���Y�J�[�\���ʒu������

				CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
				disp_stg = 00;						//���Y���
				disp_stg_sel = E_sstg_init;			//���Y[��{]��
				GAMEN_NO = 1;
				GAMEN_disp();							//��ʕ\��
			}
		}
		DAN_KEY_FLG = 0x00;						//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
	}
#else
	else if(00 == (SET_KEY_LST & BIT_10)){			//���Y��ʁH
		if ( 00 != (SEQ_PAR_101 & BIT_10) ) {
			if(disp_stg == 00){						//���Y���?
				DAN_csr_ichk();						//�i��J�[�\���ʒu������
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00){
					DAN_KEY_FLG = 0xff;				//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
					disp_stg = 01;					//�i����
					disp_stg_sel = E_kstg_init;		//�i��[��{]��
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10) {	// V01r
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//��ʕ\��
				}
				DAN_KEY_FLG = 0x00;						//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
			}
		}
		else {
			if(disp_stg == 01) {				//�^�i����?
				SEI_csr_ichk();						//���Y�J�[�\���ʒu������

				CSR_FLG = 0;						//�z�[���|�W�V�����Z�b�g
				disp_stg = 00;						//���Y���
				disp_stg_sel = E_sstg_init;			//���Y[��{]��
				GAMEN_NO = 1;
				GAMEN_disp();							//��ʕ\��
				DAN_KEY_FLG = 0x00;						//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
			}
		}
	}
#endif


MODE_CHG_SKIP:


//SIT4	else if(KEY_DATA_MODE == E_key_ten_mode)	//ten key mode?
	if(KEY_DATA_MODE == E_key_ten_mode)		//ten key mode?
	{
		Key_Ten_in(KEY_DATA_CODE);				//Ten KEY����
	}

	else if(KEY_DATA_MODE == E_key_csr_mode) {	//���� key mode?
		if( CSR_CNT != 00 ){
			CSR_FLG = KEY_DATA_CODE;

			switch(GAMEN_NO) {
				case 1:
					SEI_csr_mng();				//���Y[��{]�̐�p�@�J�[�\���ړ��Ǘ�
					break;
				case 7:			//�i����ʕ\�����͐�p�̃��[�`���𑖂�
					DAN_csr_mng();				//�i��[��{]�̐�p�@�J�[�\���ړ��Ǘ�
					break;
				case 8:			//�i����ʕ\�����͐�p�̃��[�`���𑖂�	//V01r
					DAN_csr_mng();				//�i��[��{]�̐�p�@�J�[�\���ړ��Ǘ�
					break;
				case 12:		//�J�����̓��͉��
				case 16:		//�^���̓��͉��
				case 23:		//�����f�[�^���͉��
					NAME_csr_mng();				//���̉�ʃJ�[�\������
					break;
				case 15:		//�^�f�[�^�ꗗ���
					if(PV_MLDMES_C1 == 0){						//���b�Z�[�W�\�����̓J�[�\�����ړ����Ȃ�
						CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);		//�܂��ړ��n�j
					}											//���b�Z�[�W�\�����͂m�f
					break;
				default:
					CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);	//�J�[�\���ړ�
					break;
			}

//?			CALL	SPATH_DISP			;/* ���Y�ݒ�̃~�X�t�B�[�h�\�����̃X�y�[�X�\��   */
			SV_csr_set();								//�ݒ�l�J�[�\��

			if(WINDOW_NO == 0){
				RULET_NOW_LST = 0xffff;
				DEG_DISP_LST = 0xffff;					/* �p�x�ް��ω�����H */
				STOPTIME_DISP_LST = 0xffff;				/* �p�x�ް��ω�����H */
			}
			else{
				Lcd_line(00, 6, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 7, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 8, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 9, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 10, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 11, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
				Lcd_line(00, 12, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)
			}
			Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);		//�s�\��(LCD1)
			Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);		//�s�\��(LCD1)
			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��(LCD2)
			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);		//�s�\��(LCD2)
		}
	}

/* V00p */
	else if(((SEQ_050_SV & BIT_1) && ((SEQ_PAR_101_BAK & BIT_9)==0) && (SEQ_PAR_101 & BIT_9)) ||
			((SEQ_050_SV & BIT_1) && (SEQ_PAR_101_BAK & BIT_9) && ((SEQ_PAR_101 & BIT_9)==0))) {		//���]�@�H
		disp_stg_sel_bak = disp_stg_sel;
		WINDOW_NO_bak = WINDOW_NO;
		if (RULET_DISP_FLG != 0x00) {
			GAMEN_disp();
			if (disp_stg_sel_bak != 0 ) {
				disp_stg_sel = disp_stg_sel_bak;
				WINDOW_NO = WINDOW_NO_bak;
				WIN_gamen_disp();					//�E�C���h�E��ʕ\��
			}
		}
	}

	else {
		switch(disp_stg) {
			case 0x00:				/* ���Y���	*/
				dsp_Seisan();
				break;

			case 0x01:				/* �i����	*/
				dsp_Dandori();
				break;

			case 0x02:				/* �f�[�^�ݒ���	*/
				dsp_Dataset();
				break;

			case 0x03:				/* �V�X�e���ݒ���	*/
				dsp_Sysset();
				break;

			default:
				break;
		}
	}

/* V00p */
	SEQ_PAR_101_BAK = SEQ_PAR_101;
}


/*
********************************************************************************
*  Module Name:		Any_mng
*  Function Name:	���X�L�����̌Œ菈��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	Any_mng(void)
{
	UNl		w1,w2;

/* V00t */
//	PV_DISP_CNT = PVdata_disp( PV_DISP_CNT, 0x00 );	//�����l���@�\��
	PVdata_disp_all();								//�S�@�����l���@�\��
/********/

	SWchg_disp_pv_any();							//SW�ް��@�����l �\��

	IROCK_SHR();									//�C���^�[���b�N�f�[�^����
	IROCK_SHR_OUT();								//�C���^�[���b�N�f�[�^�����o��		2009/07/14
	SEISAN_INF_DISP();								//���Y��ʍs���\��

	keep_ry_smp();									//�L�[�v�����[�T���v�����O

///////////////////////////////////////////////////////////////////////
#if	E_DEBUG											//�f�o�b�O���[�h�w��
	PVP_NOW_ANGLE_RNA	= (PVP_NOW_ANGLE00 * 10);	// �G���R�[�_�~�P�O
	HS_SVCHG_A_TO_B		= HS_SVCHG_B_TO_A;			// �n���h�V�F�C�N
#endif
///////////////////////////////////////////////////////////////////////

	RULET_GAMEN_DISP();								//���[���b�g��ʕ\��
	DEG_DISP();										//�p�x�\������
//	SPM_DISP();										//�r�o�l�\������


	GAIBU_cnt_rst();								//�O���J�E���^�N���A����
	ONOFF_mng();									//�d�l �L�^�� �ɂ�鼰�ݽ����

	DP_TRANS_CHK();									//DPRAM �� FRAM �ް��]������
	OPDP_trans_chk();								//OP-DPRAM �� FRAM �ް��]�� & ��������

	GENGO_SEQ_CHG();								/* ����؂芷���@�\		*/		/* V01x */
	GENGO_chg(0x00);								//��Q�J����ؑւ�����

	PV_CHANGE_hanten();								//���]�d�l���̂o�u�ϊ�

	debug_dat_mng();

/* V00s */
	SEQ_PAR_060 = SV_CAMNA0_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_061 = SV_CAMNA1_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_062 = SV_CAMNA2_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_063 = SV_CAMNA3_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_064 = SV_CAMNA4_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_065 = SV_CAMNA5_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_066 = SV_CAMNA6_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_067 = SV_CAMNA7_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_068 = SV_CAMNA8_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_069 = SV_CAMNA9_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_070 = SV_CAMNAA_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_071 = SV_CAMNAB_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_072 = SV_CAMNAC_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_073 = SV_CAMNAD_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_074 = SV_CAMNAE_C1;						//���[�^���J���ėp�o��
	SEQ_PAR_075 = SV_CAMNAF_C1;						//���[�^���J���ėp�o��

	PV_DYHITO_POS = PVP_DYHITO_POS;					// �����ʒu�ޯ�����			/* V01  */
	PV_SLIDE_POS = PVP_SLIDE_POS;					// ���Y�����ʒu�ޯ�����		/* V01  */

	his_dat_mng();									// �ُ헚���ް��]������		/* V01  */

	taikikaku_chg_mng();							// �ҋ@�p�ύX����			/* V01i */

	FURIKO_Cancel_mng();							// �U�q��\���w�߂̏���		/* V06p */

	Gamen_Redisp_mng();								// ��ʍĕ\������			/* V01i */

	KAT_ENB_GAMEN001_disp();						//GAMEN001�̎��Ɍ^�ް��Ǘ����L���ɂȂ����Ƃ��̉�ʍĕ\�� /* V01j */

	Tlink1_mng();									//Tlink�ʐM����		/* V01j */
	ADC_MAIN_MNG();									/* �������^�����l�`�h�m����		V01j */
	ADC_DATA_INI();									/* �`�c�b�f�[�^�C�j�V�������^�f�[�^�N���A����	SIT4 */

	Sampring_Disp();								/* �����ݸޒ��̕\�� */
	Trend_disp();									/* ����ޒ��̕\�� */
	Trend_stop();									/* ����ނ̒�~ */
	KASIN_mark_Disp();								//���U������s���������\��	V05r

	cop2_pvdata_sin();								/* COP2 */

	w1 = PV_LIFE_COUNT[1];							/* �ғ��� ���� */
	w2 = PV_LIFE_COUNT[0]<<16;						/* �ғ��� ��� */
	PVP_MENTE_CNT = w1 | w2;						// V02

	real_kajyu_check();								// V04

	SEQ_PAR_076 = PV_MLDNO1_F1;						// V05d

////	ASM_ET1_IP_BACK();								// V05j

	SEIDOUSEINOU_mng();								// V05r

	EcoMeter_Disp();								// V06

	LANG_SEQ_OUT();									// V06m
	HAN_MODE_SEQ_OUT();								// V06m
	DIE_HEIGHT_OFFSET();							// V06m
//	FURIKO_SPEC_ON_OFF();							// V06m		//V06p(DEL)
	SYSSET_SEQ_OUT();								// V06n

//	---2013-02-07 koma ���n�Ή�
	if(SV_PUR1SV_B4==0){//�ݒ�==0
		SEQ_PAR_098 |= cBIT0;
	}else{
		SEQ_PAR_098 &= ~cBIT0;
		
	}
	if(SV_PUR2SV_B41==0){//�ݒ�==0
		SEQ_PAR_098 |= cBIT1;
	}else{
		SEQ_PAR_098 &= ~cBIT1;
	}

//V06p
	PV0_CKSPD_OVBIT = PVP_CKSPD_OVBIT | ((PVP_CKSPD_OVBIT>>1) & BIT_14);
	if( ((GAMEN_NO == 3) && (SV_DANSUU_SRV > 5)) ||
		((GAMEN_NO == 28) && (SV_DANSUU_SRV > 5)) ) {
		PV0_CKSPD_OVBIT &= ~BIT_14;
	}

//V06p
	if (GAMEN_NO == 108) {							//�@��������
		SEQ_PAR_051 |= cBIT13;						//�\����
	}
	else {
		SEQ_PAR_051 &= ~cBIT13;
	}
		

	//�����������ʒu�\����گ��������
	SH2_MAIN_CLK ^= cBIT0;							//2013/07/23	����p
	kagen_disp();									//2013/07/22	����PV�\���̍�����

}


/*
********************************************************************************
*  Module Name:		kagen_disp
*  Function Name:	�����ʒu�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
********************************************************************************
*/
void	kagen_disp(void)
{
	if ( SEQ_PAR_341 & BIT_3 ) {						//2013/07/22	����PV�\���̍�����
		if ( (GAMEN_NO == 1) && (WINDOW_NO == 0) ) {
			PV_CHANGE_hanten();							//���]�d�l���̂o�u�ϊ�
			PVdata_disp( 7, 0x00ff );					//�����l���@�\��
		}
	}
}


#if	E_DEBUG_1											//�f�o�b�O���[�h�w��

//ANY_MNG		PROC	FAR
//
//OK			CALL	SEQ_CB1_DTST			; SEQ DATA SET
//OK			CALL	SEQ_SVDATA_SET			;/* �r�d�p�̂r�u�f�[�^�i�[ */
//OK			CALL	GAM_SV_DTST			; GAMEN DATA SET

//OK(Sit-S�Ȃ�)	CALL	PV_DATA_SMP			;/* �����l�T���v�����O */

//OK			CALL	PVDATA_DISP			;/* �����l�\�� */
//OK			CALL	SWCHG_DISP_PV_ANY		;/* �r�v�b�g�f�f�[�^�\���������� */
//OK			CALL	IROCK_SHR			;/* �C���^�[���b�N�f�[�^����	*/
//OK			CALL	SEISAN_INF_DISP			;/* ���Y��ʍs���\��            */

//	CALL	ERR_MONI_CHK			;/* �ُ�`�F�b�N���j�^�[�f�[�^���C�N */

//�ă`�F�b�N	CALL	OPDATA_SET_KAKU			;/* �I�v�V�����[�f�[�^�]������*/
//�ă`�F�b�N	CALL	POSDATA_SET_KAKU		;/* �|�W�V���i�[�f�[�^�]������	*/
//�ă`�F�b�N	CALL	OFF_SET_START_MNG		;/* �I�t�Z�b�g �X�^�[�g�\���Ǘ�	*/
//�ă`�F�b�N	CALL	KOUSEI_START_MNG		;/* �Z���X�^�[�g�\���Ǘ�*/
//�ă`�F�b�N	CALL	SURA_AUTO_START_MNG		;/* �X���C�h���������X�^�[�g�\���Ǘ�*/

//OK			CALL	ONOFF_MNG			;/* �d�l�L�薳���ɂ����ؐ��� 	*/

//OK			CALL	KEEP_RY_SMP			;V02 /* �L�[�v�����[�T���v�����O */

//�ă`�F�b�N	CALL	MAIN_OP_SEQ			;V03 /* �V�[�P���X���I�v�V�����֓]�� */

//�ă`�F�b�N	CALL	AUTO_SURA_SEQ_START		;/* �X���C�h���������V�[�P���X�X�^�[�g */
//�ă`�F�b�N	CALL	SURA_SV_CHG			;/* �X���C�h�������߂r�u�ύX���� */

//OK			CALL	SEIDAN_CSR_BACK			;/* ���Y�E�i��߂�J�[�\���ʒu������		*/
//OK			CALL	RULET_TBL_SET			;/* ���[���b�g�\���e�[�u������ */
//OK			CALL	RULET_GAMEN_DISP		;/* ���[���b�g��ʕ\�� 	*/

//OK			CALL	SET_KEY_MNG			;/* �ݒ�f�[�^�L�[�ύX���� */

//OK			CALL	DEG_DISP			;/* �p�x�\������     	*/
//OK(Sit-S�Ȃ�)	CALL	SPM_DISP			;/* �r�o�l�\������     	*/
//OK			CALL	GAIBU_CNT_RST			;/* �O���J�E���^�N���A���� 			*/

//�ă`�F�b�N			CALL	OPDATA_BAK_UP			;/* �I�v�V�����o�b�N�A�b�v����	*/

//Sit-S�Ȃ�		CALL	SETSPM_SV_CHG			;/* ���Y�r�o�l�r�u�ύX���� 			*/

//Sit-S�Ȃ�		CALL	GENGO_SEQ_CHG			;V06/* ����؂芷���@�\		*/
//OK			CALL	GENGO_CHG			;/* ���O����؊�����	*/


//Sit-S�Ȃ�		CALL	ADC_MAIN_MNG			;/* �������^�����l�`�h�m����		*/
//Sit-S�Ȃ�		CALL	ADC_DATA_INI			;/* �`�c�b�f�[�^�C�j�V�������^�f�[�^�N���A����	*/

//�ă`�F�b�N		CALL	SURA_SELECT_MNG			;V03k/* �X���C�h�������ߑI��؂芷������	*/
//�ă`�F�b�N		CALL	POJI_DATA_CHK			;V05 2000-09-11/* �|�W�V���i�o�b�N�A�b�v�l�Ď� */

//Sit-S�Ȃ�		CALL	SEI_GAIBU_MNG			;V06/* ���Y���x�O���؂芷���@�\ */
//Sit-S�Ȃ�		CALL	TLINK_NEXT_READ			;V06/* �s�|�k�h�m�j�O���^�ԍ��Ǎ�����	 */

//	RET					;
//;
//ANY_MNG		ENDP

#endif

/*
********************************************************************************
*  Module Name:		keep_ry_smp
*  Function Name:	�L�[�v�����[�T���v�����O
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-12
********************************************************************************
*/
void	keep_ry_smp(void)
{

//;
//;sit-s		MOV_SEQB(SEQ_PAR_312,SEQ_BAK_312)
//;sit-s		MOV_SEQB(SEQ_PAR_313,SEQ_BAK_313)
//;sit-s		MOV_SEQB(SEQ_PAR_314,SEQ_BAK_314)
//;sit-s		MOV_SEQB(SEQ_PAR_315,SEQ_BAK_315)
//;sit-s		MOV_SEQB(SEQ_PAR_316,SEQ_BAK_316)
//;sit-s		MOV_SEQB(SEQ_PAR_317,SEQ_BAK_317)
//;sit-s		MOV_SEQB(SEQ_PAR_318,SEQ_BAK_318)
//;sit-s		MOV_SEQB(SEQ_PAR_319,SEQ_BAK_319)
//;

}


/*
********************************************************************************
*  Module Name:		GAIBU_cnt_rst
*  Function Name:	�O���J�E���^�N���A����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-03
********************************************************************************
*/
void	GAIBU_cnt_rst(void)
{
	UNs		i, chg_flg;

	chg_flg = 0;

	i = GAIBU_RST_LAST;					//�O�����Z�b�g�w�ߗ����オ��H
	GAIBU_RST_LAST = SEQ_PAR_102;
	i ^= SEQ_PAR_102;
	i &= SEQ_PAR_102;

/* V00t */
//	if( i & BIT_3 ) {					//�g�[�^���J�E���^�P���Z�b�g�H
//		PV_TOTLC1_B3 = 0;				//�g�[�^���J�E���^�P�N���A
//		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
//	}
//	if( i & BIT_7 ) {					//�g�[�^���J�E���^�Q���Z�b�g�H
//		PV_TOTLC2_B31 = 0;				//�g�[�^���J�E���^�Q�N���A
//		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
//	}
//	if( i & BIT_B ) {					//���b�g�J�E���^�P���Z�b�g�H
//		PV_LOTCT1_B4 = 0;				//���b�g�J�E���^�P�N���A
//		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
//		SEQ_PAR_033 &= ~BIT_0;			//���b�g�J�E���^�P�A�b�v�@�N���A
//	}
//	if( i & BIT_F ) {					//���b�g�J�E���^�Q���Z�b�g�H
//		PV_LOTCT2_B41 = 0;				//���b�g�J�E���^�Q�N���A
//		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
//		SEQ_PAR_033 &= ~BIT_1;			//���b�g�J�E���^�Q�A�b�v�@�N���A
//	}
/********/

	if( SEQ_017_SV & BIT_1 ){			//�J�E���^�O�� ���^�؁@�d�l�L��(1:�L)
		if( i & 0x0033 ){
			if(SEQ_016_SV & BIT_8){		//�g�[�^���J�E���^ �L��(1:�L)�H 
				if(i & BIT_0){			//�g�[�^���J�E���^ �؎w��(1:��) �����H 
					SEQ_032_SV &= ~BIT_0;	//�g�[�^���J�E���^ ��
					chg_flg |= BIT_0;
				}
				if(i & BIT_1){			//�g�[�^���J�E���^ ���w��(1:��) �����H
					SEQ_032_SV |= BIT_0;	//�g�[�^���J�E���^ ��
					chg_flg |= BIT_0;
				}
			}
//GAIBU_CNT_RST_450:
		}
//GAIBU_CNT_RST_500:
		if( i & 0x3300){
			if(SEQ_016_SV & BIT_C){		//���b�g�J�E���^1 �L��(1:�L)�H 
				if(i & BIT_8){			//���b�g�J�E���^1 �؎w��(1:��) �����H 
					SEQ_032_SV &= ~BIT_2;	//���b�g�J�E���^1 ��
					chg_flg |= BIT_0;
				}
				if(i & BIT_9){			//���b�g�J�E���^1 ���w��(1:��) �����H
					SEQ_032_SV |= BIT_2;	//���b�g�J�E���^1 ��
					chg_flg |= BIT_0;
				}
			}
			if(SEQ_016_SV & BIT_E){		//���b�g�J�E���^2 �L��(1:�L)�H 
				if(i & BIT_C){			//���b�g�J�E���^2 �؎w��(1:��) �����H 
					SEQ_032_SV &= ~BIT_3;	//���b�g�J�E���^2 ��
					chg_flg |= BIT_0;
				}
				if(i & BIT_D){			//���b�g�J�E���^2 ���w��(1:��) �����H
					SEQ_032_SV |= BIT_3;	//���b�g�J�E���^2 ��
					chg_flg |= BIT_0;
				}
			}
			ROTTO_chk();							//ۯĶ��� ���� ����
		}
	}
//GAIBU_CNT_RST_700:
	if( SEQ_017_SV & BIT_2 ){			//�G�W�F�N�^�O�� ���^�؁@�d�l�L��(1:�L)
		i = GAIBU_RST_LAST2;			//�O�����Z�b�g�w�ߗ����オ��H
		GAIBU_RST_LAST2 = SEQ_PAR_104;
		i ^= SEQ_PAR_104;
		i &= SEQ_PAR_104;
		if( i & 0x0fff ){					//�G�W�F�N�^�P�`�U�����オ��H

			if(SEQ_017_SV & BIT_4){			//�G�W�F�N�^�P �L��(1:�L)�H 
				if(i & BIT_0){				//�G�W�F�N�^�P �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_0;	//�G�W�F�N�^�P ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_1){				//�G�W�F�N�^�P ���w��(1:��) �����H
					SEQ_034_SV |= BIT_0;	//�G�W�F�N�^�P ��
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_7){			//�G�W�F�N�^2 �L��(1:�L)�H 
				if(i & BIT_2){				//�G�W�F�N�^2 �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_1;	//�G�W�F�N�^2 ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_3){				//�G�W�F�N�^2 ���w��(1:��) �����H
					SEQ_034_SV |= BIT_1;	//�G�W�F�N�^2 ��
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_10){		//�G�W�F�N�^3 �L��(1:�L)�H 
				if(i & BIT_4){				//�G�W�F�N�^3 �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_2;	//�G�W�F�N�^3 ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_5){				//�G�W�F�N�^3 ���w��(1:��) �����H
					SEQ_034_SV |= BIT_2;	//�G�W�F�N�^3 ��
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_017_SV & BIT_13){		//�G�W�F�N�^4 �L��(1:�L)�H 
				if(i & BIT_6){				//�G�W�F�N�^4 �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_3;	//�G�W�F�N�^4 ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_7){				//�G�W�F�N�^4 ���w��(1:��) �����H
					SEQ_034_SV |= BIT_3;	//�G�W�F�N�^4 ��
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_018_SV & BIT_0){			//�G�W�F�N�^5 �L��(1:�L)�H 
				if(i & BIT_8){				//�G�W�F�N�^5 �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_4;	//�G�W�F�N�^5 ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_9){				//�G�W�F�N�^5 ���w��(1:��) �����H
					SEQ_034_SV |= BIT_4;	//�G�W�F�N�^5 ��
					chg_flg |= BIT_1;
				}
			}
			if(SEQ_018_SV & BIT_3){			//�G�W�F�N�^6 �L��(1:�L)�H 
				if(i & BIT_10){				//�G�W�F�N�^6 �؎w��(1:��) �����H 
					SEQ_034_SV &= ~BIT_5;	//�G�W�F�N�^6 ��
					chg_flg |= BIT_1;
				}
				if(i & BIT_11){				//�G�W�F�N�^6 ���w��(1:��) �����H
					SEQ_034_SV |= BIT_5;	//�G�W�F�N�^6 ��
					chg_flg |= BIT_1;
				}
			}
		}
	}
//GAIBU_CNT_RST_800:
	if( SEQ_017_SV & BIT_3 ){			//�~�X�t�B�[�h�O�� ���^�؁@�d�l�L��(1:�L)
		i = GAIBU_RST_LAST3;			//�O�����Z�b�g�w�ߗ����オ��H
		GAIBU_RST_LAST3 = SEQ_PAR_105;
		i ^= SEQ_PAR_105;
		i &= SEQ_PAR_105;
		if( i & 0xffff ){					//�~�X�t�B�[�h1�`8�����オ��H

			if(SEQ_018_SV & BIT_8){			//�~�X�t�B�[�h1 �L��(1:�L)�H 
				if(i & BIT_0){				//�~�X�t�B�[�h1 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_0;	//�~�X�t�B�[�h1 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_1){				//�~�X�t�B�[�h1 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_0;	//�~�X�t�B�[�h1 ��
					chg_flg |= BIT_2;
				}
			}
			if(SEQ_018_SV & BIT_9){			//�~�X�t�B�[�h2 �L��(1:�L)�H 
				if(i & BIT_2){				//�~�X�t�B�[�h2 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_1;	//�~�X�t�B�[�h2 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_3){				//�~�X�t�B�[�h2 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_1;	//�~�X�t�B�[�h2 ��
					chg_flg |= BIT_2;
				}
			}
			if(SEQ_018_SV & BIT_10){		//�~�X�t�B�[�h3�`4 �L��(1:�L)�H 
				if(i & BIT_4){				//�~�X�t�B�[�h3 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_2;	//�~�X�t�B�[�h3 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_5){				//�~�X�t�B�[�h3 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_2;	//�~�X�t�B�[�h3 ��
					chg_flg |= BIT_2;
				}

				if(i & BIT_6){				//�~�X�t�B�[�h4 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_3;	//�~�X�t�B�[�h4 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_7){				//�~�X�t�B�[�h4 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_3;	//�~�X�t�B�[�h4 ��
					chg_flg |= BIT_2;
				}

/*** V01d
				if(i & BIT_8){				//�~�X�t�B�[�h5 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_4;	//�~�X�t�B�[�h5 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_9){				//�~�X�t�B�[�h5 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_4;	//�~�X�t�B�[�h5 ��
					chg_flg |= BIT_2;
				}

				if(i & BIT_10){				//�~�X�t�B�[�h6 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_5;	//�~�X�t�B�[�h6 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_11){				//�~�X�t�B�[�h6 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_5;	//�~�X�t�B�[�h6 ��
					chg_flg |= BIT_2;
				}
***/
			}
			if(SEQ_018_SV & BIT_11){		//�~�X�t�B�[�h5�`8 �L��(1:�L)�H 

				/* V01d */
				if(i & BIT_8){				//�~�X�t�B�[�h5 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_4;	//�~�X�t�B�[�h5 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_9){				//�~�X�t�B�[�h5 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_4;	//�~�X�t�B�[�h5 ��
					chg_flg |= BIT_2;
				}

				/* V01d */
				if(i & BIT_10){				//�~�X�t�B�[�h6 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_5;	//�~�X�t�B�[�h6 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_11){				//�~�X�t�B�[�h6 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_5;	//�~�X�t�B�[�h6 ��
					chg_flg |= BIT_2;
				}

				if(i & BIT_12){				//�~�X�t�B�[�h7 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_6;	//�~�X�t�B�[�h7 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_13){				//�~�X�t�B�[�h7 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_6;	//�~�X�t�B�[�h7 ��
					chg_flg |= BIT_2;
				}

				if(i & BIT_14){				//�~�X�t�B�[�h8 �؎w��(1:��) �����H 
					SEQ_036_SV &= ~BIT_7;	//�~�X�t�B�[�h8 ��
					chg_flg |= BIT_2;
				}
				if(i & BIT_15){				//�~�X�t�B�[�h8 ���w��(1:��) �����H
					SEQ_036_SV |= BIT_7;	//�~�X�t�B�[�h8 ��
					chg_flg |= BIT_2;
				}
			}
		}
	}
//GAIBU_CNT_RST_900:
	if( chg_flg & 0x0007 ){
		SVSW_CHG_FLG |= BIT_3;
		SVSW_CHG_FLG |= BIT_5;

		i = 0xff;
		if(chg_flg & BIT_0){
			if(GAMEN_NO == 1 || GAMEN_NO == 17){
				i = 0;
			}
		}
		if(chg_flg & BIT_1){
			if(GAMEN_NO == 19 || WINDOW_NO == 5){
				i = 0;
			}
		}
		if(chg_flg & BIT_2){
			if(GAMEN_NO == 20 || WINDOW_NO == 19){
				i = 0;
			}
		}

		if( i == 0 ){
			SWCHG_DISP_ON_FLG = 0x0FF;
			SWchg_disp_gaibu();					//SW�ް����@�\��
			SWCHG_DISP_ON_FLG = 0;
		}
		FRAM_csum_set();							//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	}

/* V00t */
////GAIBU_CNT_RST_1000:
//	if( SEQ_PAR_107 & BIT_6 ){						//ۯĶ������Z���H
//		PV_LOTCT1_B1 = (SV_PUR1SV_B4 - PV_LOTCT1_B4);
//		PV_LOTCT2_B1 = (SV_PUR2SV_B41 - PV_LOTCT2_B41);
//													//���Z������ϲŽ�\���΍�
//		if( PV_LOTCT1_B1 & 0x80000000 ) {
//			PV_LOTCT1_B1 = 0;
//		}
//		if( PV_LOTCT2_B1 & 0x80000000 ) {
//			PV_LOTCT2_B1 = 0;
//		}
//	}
//	else{
//		PV_LOTCT1_B1 = PV_LOTCT1_B4;
//		PV_LOTCT2_B1 = PV_LOTCT2_B41;
//	}
/********/
}


/*
********************************************************************************
*  Module Name:		ONOFF_mng
*  Function Name:	�d�l �L�^�� �ɂ�鼰�ݽ����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-05
********************************************************************************
*/
void	ONOFF_mng(void)
{
	UNs		bf, i, j;

	bf = SEQ_016_SV & 0x5500;
	j = ONOFF_LAST1;
	ONOFF_LAST1 = bf;
	bf ^= j;
	bf &= j;

	i = SEQ_017_SV & 0x6db0;
	j = ONOFF_LAST2;
	ONOFF_LAST2 = i;
	i ^= j;
	i &= j;
	bf |= i;

	i = SEQ_018_SV & 0x5f1b;
	j = ONOFF_LAST3;
	ONOFF_LAST3 = i;
	i ^= j;
	i &= j;
	bf |= i;

	i = SEQ_019_SV & 0xfaa5;
	j = ONOFF_LAST4;
	ONOFF_LAST4 = i;
	i ^= j;
	bf |= i;

	i = SEQ_020_SV & 0x4045;
	j = ONOFF_LAST5;
	ONOFF_LAST5 = i;
	i ^= j;
	bf |= i;

	i = SEQ_021_SV & 0x00f3;
	j = ONOFF_LAST6;
	ONOFF_LAST6 = i;
	i ^= j;
	bf |= i;

	if(bf != 00){
		ONOFF_sub();						//�d�l�L�薳���ɂ����ؐ���
	}
}


/*
********************************************************************************
*  Module Name:		ONOFF_sub
*  Function Name:	�d�l �L�^�� �ɂ����ؐ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-06
********************************************************************************
*/
void	ONOFF_sub(void)
{

	ONOFF_FLG = 0;

	if(00 == (SEQ_016_SV & BIT_8) &&		//�g�[�^���J�E���^����
		SEQ_032_SV & BIT_0 ){				//�g�[�^���J�E���^����

		SEQ_032_SV &= ~BIT_0;
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_016_SV & BIT_12) &&		//���b�g�J�E���^�P����
		SEQ_032_SV & BIT_2 ){				//���b�g�J�E���^�P����

		SEQ_032_SV &= ~BIT_2;
		ROTTO_chk();						//ۯĶ��� ���� ����
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_016_SV & BIT_14) &&		//���b�g�J�E���^�Q����
		SEQ_032_SV & BIT_3 ){				//���b�g�J�E���^�Q����

		SEQ_032_SV &= ~BIT_3;
		ROTTO_chk();						//ۯĶ��� ���� ����
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_018_SV & BIT_8)){			//н̨���1 ����
		SEQ_037_SV &= ~BIT_8;				//н̨���1 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_0){				//н̨���1 ����
			SEQ_036_SV &= ~BIT_0;			//н̨���1 ���^��
			SEQ_036_SV &= ~BIT_8;			//н̨���1 ���^�A
			SEQ_037_SV &= ~BIT_0;			//н̨���1 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_9)){			//н̨���2 ����
		SEQ_037_SV &= ~BIT_9;				//н̨���2 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_1){				//н̨���2 ����
			SEQ_036_SV &= ~BIT_1;			//н̨���2 ���^��
			SEQ_036_SV &= ~BIT_9;			//н̨���2 ���^�A
			SEQ_037_SV &= ~BIT_1;			//н̨���2 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_10)){		//н̨���3 ����
		SEQ_037_SV &= ~BIT_10;				//н̨���3 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_2){				//н̨���3 ����
			SEQ_036_SV &= ~BIT_2;			//н̨���3 ���^��
			SEQ_036_SV &= ~BIT_10;			//н̨���3 ���^�A
			SEQ_037_SV &= ~BIT_2;			//н̨���3 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_10)){		//н̨���4 ����
		SEQ_037_SV &= ~BIT_11;				//н̨���4 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_3){				//н̨���4 ����
			SEQ_036_SV &= ~BIT_3;			//н̨���4 ���^��
			SEQ_036_SV &= ~BIT_11;			//н̨���4 ���^�A
			SEQ_037_SV &= ~BIT_3;			//н̨���4 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

//V01d	if(00 == (SEQ_018_SV & BIT_10)){		//н̨���5 ����
	if(00 == (SEQ_018_SV & BIT_11)){		//н̨���5 ����
		SEQ_037_SV &= ~BIT_12;				//н̨���5 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_4){				//н̨���5 ����
			SEQ_036_SV &= ~BIT_4;			//н̨���5 ���^��
			SEQ_036_SV &= ~BIT_12;			//н̨���5 ���^�A
			SEQ_037_SV &= ~BIT_4;			//н̨���5 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

//V01d	if(00 == (SEQ_018_SV & BIT_10)){		//н̨���6 ����
	if(00 == (SEQ_018_SV & BIT_11)){		//н̨���6 ����
		SEQ_037_SV &= ~BIT_13;				//н̨���6 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_5){				//н̨���6 ����
			SEQ_036_SV &= ~BIT_5;			//н̨���6 ���^��
			SEQ_036_SV &= ~BIT_13;			//н̨���6 ���^�A
			SEQ_037_SV &= ~BIT_5;			//н̨���6 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_11)){		//н̨���7 ����
		SEQ_037_SV &= ~BIT_14;				//н̨���7 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_6){				//н̨���7 ����
			SEQ_036_SV &= ~BIT_6;			//н̨���7 ���^��
			SEQ_036_SV &= ~BIT_14;			//н̨���7 ���^�A
			SEQ_037_SV &= ~BIT_6;			//н̨���7 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}

	if(00 == (SEQ_018_SV & BIT_11)){		//н̨���8 ����
		SEQ_037_SV &= ~BIT_15;				//н̨���8 �ڐG�^�ێ�
		ONOFF_FLG = 0xff;
		if(SEQ_036_SV & BIT_7){				//н̨���8 ����
			SEQ_036_SV &= ~BIT_7;			//н̨���8 ���^��
			SEQ_036_SV &= ~BIT_15;			//н̨���8 ���^�A
			SEQ_037_SV &= ~BIT_7;			//н̨���8 N.O�^N.C
			ONOFF_FLG = 0xff;
		}
	}


	if(00 == (SEQ_018_SV & BIT_12) &&		//۰�ض� 1�`4����
		SEQ_038_SV & 0x000f ){				//RCLS 1�`4����

		SEQ_038_SV &= 0xfff0;				//RCLS 1�`4 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_14) &&		//۰�ض� 5�`8����
		SEQ_038_SV & 0x00f0 ){				//RCLS 5�`8����

		SEQ_038_SV &= 0xff0f;				//RCLS 5�`8 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_019_SV & BIT_0) &&		//۰�ض� 9�`12����
		SEQ_038_SV & 0x0f00 ){				//RCLS 9�`12����

		SEQ_038_SV &= 0xf0ff;				//RCLS 9�`12 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_019_SV & BIT_2) &&		//۰�ض� 13�`16����
		SEQ_038_SV & 0xf000 ){				//RCLS 13�`16����

		SEQ_038_SV &= 0x0fff;				//RCLS 13�`16 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_6) &&		//۰�ض� 17�`20����
		SEQ_039_SV & 0x000f ){				//RCLS 17�`20����

		SEQ_039_SV &= 0xfff0;				//RCLS 17�`20 ��
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_017_SV & BIT_4) &&		//��ު��1 ����
		SEQ_034_SV & BIT_0 ){				//��ު��1 ����

		SEQ_034_SV &= ~BIT_0;				//��ު��1 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_7) &&		//��ު��2 ����
		SEQ_034_SV & BIT_1 ){				//��ު��2 ����

		SEQ_034_SV &= ~BIT_1;				//��ު��2 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_10) &&		//��ު��3 ����
		SEQ_034_SV & BIT_2 ){				//��ު��3 ����

		SEQ_034_SV &= ~BIT_2;				//��ު��3 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_13) &&		//��ު��4 ����
		SEQ_034_SV & BIT_3 ){				//��ު��4 ����

		SEQ_034_SV &= ~BIT_3;				//��ު��4 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_0) &&		//��ު��5 ����
		SEQ_034_SV & BIT_4 ){				//��ު��5 ����

		SEQ_034_SV &= ~BIT_4;				//��ު��5 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_3) &&		//��ު��6 ����
		SEQ_034_SV & BIT_5 ){				//��ު��6 ����

		SEQ_034_SV &= ~BIT_5;				//��ު��6 ��
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_5) &&		//��ު��1 ��� ����
		SEQ_034_SV & BIT_8 ){				//��ު��1 ��� �I��

		SEQ_034_SV &= ~BIT_8;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_8) &&		//��ު��2 ��� ����
		SEQ_034_SV & BIT_9 ){				//��ު��2 ��� �I��

		SEQ_034_SV &= ~BIT_9;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_11) &&		//��ު��3 ��� ����
		SEQ_034_SV & BIT_10 ){				//��ު��3 ��� �I��

		SEQ_034_SV &= ~BIT_10;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_017_SV & BIT_14) &&		//��ު��4 ��� ����
		SEQ_034_SV & BIT_11 ){				//��ު��4 ��� �I��

		SEQ_034_SV &= ~BIT_11;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_1) &&		//��ު��5 ��� ����
		SEQ_034_SV & BIT_12 ){				//��ު��5 ��� �I��

		SEQ_034_SV &= ~BIT_12;
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_018_SV & BIT_4) &&		//��ު��6 ��� ����
		SEQ_034_SV & BIT_13 ){				//��ު��6 ��� �I��

		SEQ_034_SV &= ~BIT_13;
		ONOFF_FLG = 0xff;
	}


	if(00 == (SEQ_021_SV & BIT_4) &&		//���ڔԍ�01 ����
		SEQ_040_SV & BIT_0 ){				//���ڔԍ�01 ����

		SEQ_040_SV &= ~BIT_0;				//���ڔԍ�01 �؂�
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_5) &&		//���ڔԍ�02 ����
		SEQ_040_SV & BIT_1 ){				//���ڔԍ�02 ����

		SEQ_040_SV &= ~BIT_1;				//���ڔԍ�02 �؂�
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_6) &&		//���ڔԍ�03 ����
		SEQ_040_SV & BIT_2 ){				//���ڔԍ�03 ����

		SEQ_040_SV &= ~BIT_2;				//���ڔԍ�03 �؂�
		ONOFF_FLG = 0xff;
	}

	if(00 == (SEQ_021_SV & BIT_7) &&		//���ڔԍ�04 ����
		SEQ_040_SV & BIT_3 ){				//���ڔԍ�04 ����

		SEQ_040_SV &= ~BIT_3;				//���ڔԍ�04 �؂�
		ONOFF_FLG = 0xff;
	}


											//�i���M�������n�e�e
	SEQ_041_SV &= 0x1cfc;
	SEQ_042_SV &= 0x1c1c;
	SEQ_043_SV &= 0x1c1c;
	SEQ_044_SV &= 0x0c1c;
	SEQ_045_SV &= 0x1c14;
	SEQ_046_SV &= 0x0c1c;
	DANseq_alloff();						//�i���p�V�[�P���X�n�e�e

	DAN_sel(&SEQ_041_SV, SEQ_019_SV, BIT_5, 0x00);	//��^�N�����p�I��
	DAN_sel(&SEQ_041_SV, SEQ_019_SV, BIT_7, 0x01);	//���^�N�����p�I��
	DAN_sel(&SEQ_042_SV, SEQ_019_SV, BIT_9, 0x00);	//�_�C���t�^�I��
	DAN_sel(&SEQ_044_SV, SEQ_020_SV, BIT_6, 0x00);	//�X���C�h�����I��

	SWchg_bit_chk();						//�r�v�f�[�^���͎������I�����ۏ���

	FRAM_csum_set();						//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	if(ONOFF_FLG == 0xff){
		SVSW_CHG_FLG |= 0x002f;				//�f�[�^�i�[�t���u�Z�b�g
	}
}


/*
********************************************************************************
*  Module Name:		ROTTO_chk
*  Function Name:	ۯĶ��� ���� ����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-14
********************************************************************************
*/
void	ROTTO_chk(void)
{
//	UNs		wk;
	UNl		wk;			//V06j 2012/03/23

//V06e
//	if( 0 == (SEQ_016_SV & BIT_C) ||			//ۯĶ���1(1:�L)
//		0 == (SEQ_032_SV & BIT_2) ||			//ۯĶ���1���^��(1:��)
//		SEQ_PAR_102 & BIT_B ||					//ۯĶ���1 ؾ�Ďw��(1:ؾ��)
//		SV_PUR1SV_B4 > PV_LOTCT1_B4 ) {
//
//		SEQ_PAR_033 &= ~BIT_0;					//ۯĶ���1 ����UP(1:����UP)
//	}
//	else{
//		SEQ_PAR_033 |= BIT_0;					//ۯĶ���1 ����UP(1:����UP)
//	}
//
//	if( 0 == (SEQ_016_SV & BIT_E) ||			//ۯĶ���2(1:�L)
//		0 == (SEQ_032_SV & BIT_3) ||			//ۯĶ���2���^��(1:��)
//			SEQ_PAR_102 & BIT_F ||				//ۯĶ���2 ؾ�Ďw��(1:ؾ��)
//			SV_PUR2SV_B41 > PV_LOTCT2_B41) {
//
//		SEQ_PAR_033 &= ~BIT_1;					//ۯĶ���2 ����UP(1:����UP)
//	}
//	else{
//		SEQ_PAR_033 |= BIT_1;					//ۯĶ���2 ����UP(1:����UP)
//	}

	if( 0 == (SEQ_016_SV & BIT_C) ||			//ۯĶ���1(1:�L)
		0 == (SEQ_032_SV & BIT_2) ||			//ۯĶ���1���^��(1:��)
		SEQ_PAR_102 & BIT_B ) {					//ۯĶ���1 ؾ�Ďw��(1:ؾ��)

		SEQ_PAR_033 &= ~BIT_0;					//ۯĶ���1 ����UP(1:����UP)
		SEQ_PAR_033 &= ~BIT_4;					//ۯĶ���1 ����UP(1:����UP)
	}
	else {
		if ( SV_PUR1SV_B4 > PV_LOTCT1_B4 ) {

			SEQ_PAR_033 &= ~BIT_0;					//ۯĶ���1 ����UP(1:����UP)
		}
		else{
			SEQ_PAR_033 |= BIT_0;					//ۯĶ���1 ����UP(1:����UP)
		}

		wk = SV_PUR1SV_B4;
		if (wk) {
			wk = wk - 1;
		}
		if ( wk > PV_LOTCT1_B4 ) {

			SEQ_PAR_033 &= ~BIT_4;					//ۯĶ���1 ����UP(1:����UP)
		}
		else{
			SEQ_PAR_033 |= BIT_4;					//ۯĶ���1 ����UP(1:����UP)
		}
	}

	if( 0 == (SEQ_016_SV & BIT_E) ||			//ۯĶ���2(1:�L)
		0 == (SEQ_032_SV & BIT_3) ||			//ۯĶ���2���^��(1:��)
			SEQ_PAR_102 & BIT_F ) {				//ۯĶ���2 ؾ�Ďw��(1:ؾ��)

		SEQ_PAR_033 &= ~BIT_1;					//ۯĶ���2 ����UP(1:����UP)
		SEQ_PAR_033 &= ~BIT_5;					//ۯĶ���2 ����UP(1:����UP)
	}
	else {
		if (SV_PUR2SV_B41 > PV_LOTCT2_B41) {

			SEQ_PAR_033 &= ~BIT_1;					//ۯĶ���2 ����UP(1:����UP)
		}
		else{
			SEQ_PAR_033 |= BIT_1;					//ۯĶ���2 ����UP(1:����UP)
		}

		wk = SV_PUR2SV_B41;
		if (wk) {
			wk = wk - 1;
		}
		if ( wk > PV_LOTCT2_B41 ) {

			SEQ_PAR_033 &= ~BIT_5;					//ۯĶ���2 ����UP(1:����UP)
		}
		else{
			SEQ_PAR_033 |= BIT_5;					//ۯĶ���2 ����UP(1:����UP)
		}
	}

}


/*
********************************************************************************
*  Module Name:		CAMname_pon_read
*  Function Name:	�d���������̔ėp�і��̂̓Ǎ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-22
********************************************************************************
*/
void	CAMname_pon_read(void)
{
	UNs		*src_p, *dst_p, b_d0, b_d1;
	UNi		cnt, cnt2, cnt3;

	//�ėp�o�͑I��SW ���̂�̈�փR�s�[
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(12,  8, 11, &PV_CAMSW1_C1[0], 4);				//�ėp�o�͑I�� SW1���߰
	disp_char_cpy(12,  8, 21, &PV_CAMSW2_C1[0], 4);				//�ėp�o�͑I�� SW2���߰
	disp_char_cpy(12,  8, 31, &PV_CAMSW3_C1[0], 4);				//�ėp�o�͑I�� SW3���߰
	disp_char_cpy(12,  9,  1, &PV_CAMSW4_C1[0], 4);				//�ėp�o�͑I�� SW4���߰
	disp_char_cpy(12,  9, 11, &PV_CAMSW5_C1[0], 4);				//�ėp�o�͑I�� SW5���߰
	disp_char_cpy(12,  9, 21, &PV_CAMSW6_C1[0], 4);				//�ėp�o�͑I�� SW6���߰
	disp_char_cpy(12,  9, 31, &PV_CAMSW7_C1[0], 4);				//�ėp�o�͑I�� SW7���߰
	disp_char_cpy(12, 10,  1, &PV_CAMSW8_C1[0], 4);				//�ėp�o�͑I�� SW8���߰
	disp_char_cpy(12, 10, 11, &PV_CAMSW9_C1[0], 4);				//�ėp�o�͑I�� SW9���߰
	disp_char_cpy(12, 10, 21, &PV_CAMSWA_C1[0], 4);				//�ėp�o�͑I�� SW10���߰
	disp_char_cpy(12, 10, 31, &PV_CAMSWB_C1[0], 4);				//�ėp�o�͑I�� SW11���߰
	disp_char_cpy(12, 11,  1, &PV_CAMSWC_C1[0], 4);				//�ėp�o�͑I�� SW12���߰
	disp_char_cpy(12, 11, 11, &PV_CAMSWD_C1[0], 4);				//�ėp�o�͑I�� SW13���߰
	disp_char_cpy(12, 11, 21, &PV_CAMSWE_C1[0], 4);				//�ėp�o�͑I�� SW14���߰
	disp_char_cpy(12, 11, 31, &PV_CAMSWF_C1[0], 4);				//�ėp�o�͑I�� SW15���߰
#else
	disp_char_SWcpy(199, &PV_CAMSW1_C1[0], 4);				//�ėp�o�͑I�� SW1���߰
	disp_char_SWcpy(200, &PV_CAMSW2_C1[0], 4);				//�ėp�o�͑I�� SW2���߰
	disp_char_SWcpy(201, &PV_CAMSW3_C1[0], 4);				//�ėp�o�͑I�� SW3���߰
	disp_char_SWcpy(202, &PV_CAMSW4_C1[0], 4);				//�ėp�o�͑I�� SW4���߰
	disp_char_SWcpy(203, &PV_CAMSW5_C1[0], 4);				//�ėp�o�͑I�� SW5���߰
	disp_char_SWcpy(204, &PV_CAMSW6_C1[0], 4);				//�ėp�o�͑I�� SW6���߰
	disp_char_SWcpy(205, &PV_CAMSW7_C1[0], 4);				//�ėp�o�͑I�� SW7���߰
	disp_char_SWcpy(206, &PV_CAMSW8_C1[0], 4);				//�ėp�o�͑I�� SW8���߰
	disp_char_SWcpy(207, &PV_CAMSW9_C1[0], 4);				//�ėp�o�͑I�� SW9���߰
	disp_char_SWcpy(208, &PV_CAMSWA_C1[0], 4);				//�ėp�o�͑I�� SW10���߰
	disp_char_SWcpy(209, &PV_CAMSWB_C1[0], 4);				//�ėp�o�͑I�� SW11���߰
	disp_char_SWcpy(210, &PV_CAMSWC_C1[0], 4);				//�ėp�o�͑I�� SW12���߰
	disp_char_SWcpy(211, &PV_CAMSWD_C1[0], 4);				//�ėp�o�͑I�� SW13���߰
	disp_char_SWcpy(212, &PV_CAMSWE_C1[0], 4);				//�ėp�o�͑I�� SW14���߰
	disp_char_SWcpy(213, &PV_CAMSWF_C1[0], 4);				//�ėp�o�͑I�� SW15���߰
#endif

	//�ėp�o�͑I���r�v���`�F�b�N�i���������Ă�����j
	for(cnt=0 ; cnt < 16 ; cnt++){
		src_p = Camcsr_Name_Tbl1[cnt];
		b_d0 = *src_p;
		b_d1 = BIT_0;
		for(cnt2=16, cnt3=0 ; cnt2 > 0 ; cnt2--){
			if( b_d0 & b_d1 ){
				cnt3 ++;
			}
			b_d1 <<= 1;
		}
		if(cnt3 != 1){
			*src_p = BIT_0;
		}
	}

//���[�^���J�� ���̂�̈�փR�s�[
	CAM_name_ref();										//۰�ضєėp�I����ʂɑΉ������і��̂̍X�V

//���[�^���J�� ���̂�Ή��܂ł̃f�o�b�O���[�h
//	disp_char_cpy(21,  4, 0, &PV_CAMNA01_C1[0], 4);
//	disp_char_cpy(21,  5, 0, &PV_CAMNA02_C1[0], 4);
//	disp_char_cpy(21,  6, 0, &PV_CAMNA03_C1[0], 4);
//	disp_char_cpy(21,  7, 0, &PV_CAMNA04_C1[0], 4);
//	disp_char_cpy(21,  8, 0, &PV_CAMNA05_C1[0], 4);
//	disp_char_cpy(21,  9, 0, &PV_CAMNA06_C1[0], 4);
//	disp_char_cpy(21, 10, 0, &PV_CAMNA07_C1[0], 4);
//	disp_char_cpy(21, 11, 0, &PV_CAMNA08_C1[0], 4);
//	disp_char_cpy(22,  4, 0, &PV_CAMNA09_C1[0], 4);
//	disp_char_cpy(22,  5, 0, &PV_CAMNA10_C1[0], 4);
//	disp_char_cpy(22,  6, 0, &PV_CAMNA11_C1[0], 4);
//	disp_char_cpy(22,  7, 0, &PV_CAMNA12_C1[0], 4);
//	disp_char_cpy(22,  8, 0, &PV_CAMNA13_C1[0], 4);
//	disp_char_cpy(22,  9, 0, &PV_CAMNA14_C1[0], 4);
//	disp_char_cpy(22, 10, 0, &PV_CAMNA15_C1[0], 4);
//	disp_char_cpy(22, 11, 0, &PV_CAMNA16_C1[0], 4);
//���[�^���J�� ���̂�Ή��܂ł̃f�o�b�O���[�h


//�G�W�F�N�^ ���̂�̈�փR�s�[
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(33,  2,  4, &SV_EJENAM01_C1[0], 4);		//��ު������1���߰
	disp_char_cpy(33,  5,  4, &SV_EJENAM02_C1[0], 4);		//��ު������2���߰
	disp_char_cpy(33,  8,  4, &SV_EJENAM03_C1[0], 4);		//��ު������3���߰
	disp_char_cpy(33, 11,  4, &SV_EJENAM04_C1[0], 4);		//��ު������4���߰
	disp_char_cpy(33,  4, 24, &SV_EJENAM05_C1[0], 4);		//��ު������5���߰
	disp_char_cpy(33,  7, 24, &SV_EJENAM06_C1[0], 4);		//��ު������6���߰
#else
	disp_char_CSRcpy(67, &SV_EJENAM01_C1[0], 4);		//��ު������1���߰
	disp_char_CSRcpy(70, &SV_EJENAM02_C1[0], 4);		//��ު������2���߰
	disp_char_CSRcpy(73, &SV_EJENAM03_C1[0], 4);		//��ު������3���߰
	disp_char_CSRcpy(76, &SV_EJENAM04_C1[0], 4);		//��ު������4���߰
	disp_char_CSRcpy(79, &SV_EJENAM05_C1[0], 4);		//��ު������5���߰
	disp_char_CSRcpy(82, &SV_EJENAM06_C1[0], 4);		//��ު������6���߰
#endif

	FRAM_csum_set();										//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

//���ڔԍ� ���̂�̈�փR�s�[
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(36, 6, 4, &PV_KOUMOKU1_NAME[0], 8);		//���ڔԍ�1���߰
	disp_char_cpy(36, 7, 4, &PV_KOUMOKU2_NAME[0], 8);		//���ڔԍ�2���߰
	disp_char_cpy(36, 8, 4, &PV_KOUMOKU3_NAME[0], 8);		//���ڔԍ�3���߰
	disp_char_cpy(36, 9, 4, &PV_KOUMOKU4_NAME[0], 8);		//���ڔԍ�4���߰
#else
	disp_char_CSRcpy(131, &PV_KOUMOKU1_NAME[0], 8);		//���ڔԍ�1���߰
	disp_char_CSRcpy(132, &PV_KOUMOKU2_NAME[0], 8);		//���ڔԍ�2���߰
	disp_char_CSRcpy(133, &PV_KOUMOKU3_NAME[0], 8);		//���ڔԍ�3���߰
	disp_char_CSRcpy(134, &PV_KOUMOKU4_NAME[0], 8);		//���ڔԍ�4���߰
#endif

//�@�\�I�� ���̂�̈�փR�s�[
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	disp_char_cpy(14, 2,  3, &PV_KINOU01_NAE[0], 8);		//�@�\�I������1���߰
	disp_char_cpy(14, 3,  3, &PV_KINOU02_NAE[0], 8);		//�@�\�I������2���߰
	disp_char_cpy(14, 4,  3, &PV_KINOU03_NAE[0], 8);		//�@�\�I������3���߰
	disp_char_cpy(14, 5,  3, &PV_KINOU04_NAE[0], 8);		//�@�\�I������4���߰
	disp_char_cpy(14, 6,  3, &PV_KINOU05_NAE[0], 8);		//�@�\�I������5���߰
	disp_char_cpy(14, 7,  3, &PV_KINOU06_NAE[0], 8);		//�@�\�I������6���߰
	disp_char_cpy(14, 8,  3, &PV_KINOU07_NAE[0], 8);		//�@�\�I������7���߰
	disp_char_cpy(14, 9,  3, &PV_KINOU08_NAE[0], 8);		//�@�\�I������8���߰
	disp_char_cpy(14, 2, 23, &PV_KINOU09_NAE[0], 8);		//�@�\�I������9���߰
	disp_char_cpy(14, 3, 23, &PV_KINOU10_NAE[0], 8);		//�@�\�I������10���߰
	disp_char_cpy(14, 4, 23, &PV_KINOU11_NAE[0], 8);		//�@�\�I������11���߰
	disp_char_cpy(14, 5, 23, &PV_KINOU12_NAE[0], 8);		//�@�\�I������12���߰
	disp_char_cpy(14, 6, 23, &PV_KINOU13_NAE[0], 8);		//�@�\�I������13���߰
	disp_char_cpy(14, 7, 23, &PV_KINOU14_NAE[0], 8);		//�@�\�I������14���߰
	disp_char_cpy(14, 8, 23, &PV_KINOU15_NAE[0], 8);		//�@�\�I������15���߰
	disp_char_cpy(14, 9, 23, &PV_KINOU16_NAE[0], 8);		//�@�\�I������16���߰
#else
	disp_char_CSRcpy(310, &PV_KINOU01_NAE[0], 8);		//�@�\�I������1���߰
	disp_char_CSRcpy(311, &PV_KINOU02_NAE[0], 8);		//�@�\�I������2���߰
	disp_char_CSRcpy(312, &PV_KINOU03_NAE[0], 8);		//�@�\�I������3���߰
	disp_char_CSRcpy(313, &PV_KINOU04_NAE[0], 8);		//�@�\�I������4���߰
	disp_char_CSRcpy(314, &PV_KINOU05_NAE[0], 8);		//�@�\�I������5���߰
	disp_char_CSRcpy(315, &PV_KINOU06_NAE[0], 8);		//�@�\�I������6���߰
	disp_char_CSRcpy(316, &PV_KINOU07_NAE[0], 8);		//�@�\�I������7���߰
	disp_char_CSRcpy(317, &PV_KINOU08_NAE[0], 8);		//�@�\�I������8���߰
	disp_char_CSRcpy(318, &PV_KINOU09_NAE[0], 8);		//�@�\�I������9���߰
	disp_char_CSRcpy(319, &PV_KINOU10_NAE[0], 8);		//�@�\�I������10���߰
	disp_char_CSRcpy(320, &PV_KINOU11_NAE[0], 8);		//�@�\�I������11���߰
	disp_char_CSRcpy(321, &PV_KINOU12_NAE[0], 8);		//�@�\�I������12���߰
	disp_char_CSRcpy(322, &PV_KINOU13_NAE[0], 8);		//�@�\�I������13���߰
	disp_char_CSRcpy(323, &PV_KINOU14_NAE[0], 8);		//�@�\�I������14���߰
	disp_char_CSRcpy(324, &PV_KINOU15_NAE[0], 8);		//�@�\�I������15���߰
	disp_char_CSRcpy(325, &PV_KINOU16_NAE[0], 8);		//�@�\�I������16���߰
#endif

}


/*
********************************************************************************
*  Module Name:		FRAM_csum_set(��:SUM_CHK_SET)
*  Function Name:	�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-23
********************************************************************************
*/
void	FRAM_csum_set(void)
{
	UNl		*src_p, scode;
	UNi		cnt;

	scode = 0;									//�ر
	src_p = (UNl *)&SEQ_016_SV;					//�׼�RAM�̈�̐ݒ�l į�߱��ڽ
	cnt = &PV_TOTLC1_B3 - (UNl *)&SEQ_016_SV;	//�׼�RAM�̈�̐ݒ�l END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

	SUM_CHK = scode;							//�ݒ�l�T���`�F�b�N�R�[�h

}


/*
********************************************************************************
*  Module Name:		FRAM_csum_chk(��:SUM_CHK_CHK)
*  Function Name:	�׼�RAM�̈�̐ݒ�l�������ѥ���ނ�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-23
********************************************************************************
*/
void	FRAM_csum_chk(void)
{
	UNl		*src_p, scode;
	UNi		cnt;

	scode = 0;									//�ر
	src_p = (UNl *)&SEQ_016_SV;					//�׼�RAM�̈�̐ݒ�l į�߱��ڽ
	cnt = &PV_TOTLC1_B3 - (UNl *)&SEQ_016_SV;	//�׼�RAM�̈�̐ݒ�l END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

	if(SUM_CHK != scode ){						//�ݒ�l�T���`�F�b�N�R�[�h �`�F�b�N
		SEQ_PAR_079 |= BIT_0;					//�ݒ�l�����шُ�
	}
}


/*
********************************************************************************
*  Module Name:		FRAM_KAT_csum_set(��:SUM_CHK_SET)
*  Function Name:	�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-23
********************************************************************************
*/
void	FRAM_KAT_csum_set(void)
{
	UNs		*src_p, scode;
	UNi		cnt;

	scode = 0;									//�ر
	src_p = &KAT_NAME_01[0];					//�׼�RAM�̈�̌^�ް� ���́����� į�߱��ڽ
	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];	//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

//V06n
	src_p = &KAT_NAME_101[0];					//�׼�RAM�̈�̌^�ް� ���́����� į�߱��ڽ
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];	//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

	SUM_CHK_KAT = scode;						//�^�ް� ���́����� �T���`�F�b�N�R�[�h

}


/*
********************************************************************************
*  Module Name:		FRAM_KAT_csum_chk(��:SUM_CHK_CHK)
*  Function Name:	�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ�����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-23
********************************************************************************
*/
void	FRAM_KAT_csum_chk(void)
{
	UNs		*src_p, scode;
	UNi		cnt;

	scode = 0;									//�ر
	src_p = &KAT_NAME_01[0];					//�׼�RAM�̈�̌^�ް� ���́����� į�߱��ڽ
	cnt = &KAT_NAME_END[0] - &KAT_NAME_01[0];	//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

//V06n
	src_p = &KAT_NAME_101[0];					//�׼�RAM�̈�̌^�ް� ���́����� į�߱��ڽ
	cnt = &KAT_NAME_END2[0] - &KAT_NAME_101[0];	//�׼�RAM�̈�̌^�ް� ���́����� END���ڽ - į�߱��ڽ

	while(cnt --){								//BCC�쐬
		scode += *src_p++;
	}

	if(SUM_CHK_KAT != scode ){					//�^�ް� ���́����� �T���`�F�b�N�R�[�h
		SEQ_PAR_079 |= BIT_0;					//�ݒ�l�����шُ�
	}

}


/*
********************************************************************************
*  Module Name:		Power_down
*  Function Name:	�p���[�_�E������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-10-07
********************************************************************************
*/
void	Power_down(void)
{

	FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	FRAM_KAT_csum_set();			//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬

	GAMEN_NO = 5;					//�u����
	GAMEN_disp();					//��ʕ\��

}


/*
********************************************************************************
*  Module Name:		PV_CHANGE_hanten
*  Function Name:	���]�d�l���̂o�u�ϊ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2003-02-04
********************************************************************************
*/


void	PV_CHANGE_hanten(void)
{
	UNl		cnv_bf1,cnv_bf2,cnv_bf3;

	cnv_bf1 = PVP_NOW_POSI000;								//�����㍂��PV
	cnv_bf2 = PVP_DYHITO_POS;								//�����ʒuPV
	cnv_bf3 = PVP_SLIDE_POS;								//���Y����PV

	if( SEQ_050_SV & BIT_1 ) {								//���]�@�H

		cnv_bf1 = cnv_bf1 - SV_NEG_OFS_LNG;					//�����㍂��PV�������_�����|��������
		if( cnv_bf1 & 0x80000000 ) cnv_bf1 = 0;				//�}�C�i�X�Ȃ�O

		cnv_bf2 = cnv_bf2 + SV_NEG_OFS_LNG;					//�����ʒuPV���޲ʲ�PV�{��������

		/* V01  */
		cnv_bf3 = cnv_bf3 + SV_NEG_OFS_LNG;					//���Y����PV���޲ʲ�PV�{��������

	}

	PV0_NOW_POSI000 = cnv_bf1;
	PV0_DYHITO_POS = cnv_bf2;
	PV0_SLIDE_POS = cnv_bf3;

//V01m	/* V01  */
//	if (SEQ_PAR_200 & BIT_5) {						//�i�搡���H
//		PV0_NOWPOSI_SLIDE = PV0_NOW_POSI000;		//�i�搡�����͉����㍂��PV��\��
//	}
//	else {
//		PV0_NOWPOSI_SLIDE = PV0_SLIDE_POS;			//����ȊO�͐��Y����PV��\��
//	}
	if (SEQ_PAR_200 & BIT_5) {						//�i�搡���H
		cnv_bf2 = cnv_mm_inch(PV0_NOW_POSI000, 1);	//�P�ʐؑ�(mm��mm/INCH)
	}
	else {
		cnv_bf2 = cnv_mm_inch(PV0_SLIDE_POS, 1);	//�P�ʐؑ�(mm��mm/INCH)
	}
	if( SEQ_016_SV & BIT_6 ) { }					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
	else {
		if (SV_POINT_A1 == 1) {
			cnv_bf2 /= 10;
		}
	}
	PV0_NOWPOSI_SLIDE = cnv_bf2;				//�i�搡�����͉����㍂��PV��\��

//V01m	if( SEQ_PAR_107 & BIT_13 ){						//���Y��ʂ̉������Ƀ|�W�V���i�\���H	/* V01l_b */
//		PV0_KAGEN_POSITIONER = PV_DAIHAI_B5*10;		//�|�W�V���i
//	}
//	else {
//		PV0_KAGEN_POSITIONER = PV0_DYHITO_POS;		//����
//	}
	if( SEQ_PAR_107 & BIT_13 ){						//���Y��ʂ̉������Ƀ|�W�V���i�\���H
		PV0_KAGEN_POSITIONER = PV_DAIHAI_B5;		//�|�W�V���i
	}
	else {
		cnv_bf2 = cnv_mm_inch(PV0_DYHITO_POS, 1);		//�P�ʐؑ�(mm��mm/INCH)
		if( SEQ_016_SV & BIT_6 ) { }					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		else {
			if (SV_POINT_A1 == 1) {
				cnv_bf2 /= 10;
			}
		}
		PV0_KAGEN_POSITIONER = cnv_bf2;				//����
	}



}




/*
********************************************************************************
*  Module Name:		debug_dat_mng
*  Function Name:	���ޯ�ޥ�������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2002-11-12
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define		SH2_DPRMTOP		0x00600000
#define		SH2_SRAMTOP		0x00400000
#define		SH2_FROMTOP		0x00500000
#define		SH2_FRAMTOP		0x00800000
#define		SH2_OPRMTOP		0x00870000
#else
#define		SH2_DPRMTOP		0xB8000000
#define		SH2_SRAMTOP		0xAC090000
#define		SH2_FROMTOP		0xB9000000
#define		SH2_FRAMTOP		0xB4000000
#define		SH2_OPRMTOP		0xB5000000
#endif
void	debug_dat_mng(void)
{
	UNs	*bf_p;

	if (GAMEN_NO == 70) {

		SVP_DEB_SEL0 = SV_DEB_SEL0;					//�̈�I�� 0
		SVP_DEB_ADR0 = (SV_DEB_ADR0 & 0xfffffffe);	//���α��ڽ 0
		SVP_DEB_SEL1 = SV_DEB_SEL1;					//�̈�I�� 1
		SVP_DEB_ADR1 = (SV_DEB_ADR1 & 0xfffffffe);	//���α��ڽ 1
		SVP_DEB_SEL2 = SV_DEB_SEL2;					//�̈�I�� 2
		SVP_DEB_ADR2 = (SV_DEB_ADR2 & 0xfffffffe);	//���α��ڽ 2
		SVP_DEB_SEL3 = SV_DEB_SEL3;					//�̈�I�� 3
		SVP_DEB_ADR3 = (SV_DEB_ADR3 & 0xfffffffe);	//���α��ڽ 3
		SVP_DEB_SEL4 = SV_DEB_SEL4;					//�̈�I�� 4
		SVP_DEB_ADR4 = (SV_DEB_ADR4 & 0xfffffffe);	//���α��ڽ 4

		if ( SVP_DEB_SEL0 < 9 ) {
			switch(SVP_DEB_SEL0) {
				case 0:								//SH2-DPRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_DPRMTOP);
					break;
				case 1:								//SH2-SRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_SRAMTOP);
					break;
				case 2:								//SH2-FROM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_FROMTOP);
					break;
				case 3:								//SH2-FRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_FRAMTOP);
					break;
				case 4:								//SH2-OPRAM
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR0 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR0 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT0 = *bf_p++;
			PVP_DEB_DAT1 = *bf_p;
		}
		if ( SVP_DEB_SEL1 < 9 ) {
			switch(SVP_DEB_SEL1) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR1 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR1 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT2 = *bf_p++;
			PVP_DEB_DAT3 = *bf_p;
		}
		if ( SVP_DEB_SEL2 < 9 ) {
			switch(SVP_DEB_SEL2) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR2 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR2 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT4 = *bf_p++;
			PVP_DEB_DAT5 = *bf_p;
		}
		if ( SVP_DEB_SEL3 < 9 ) {
			switch(SVP_DEB_SEL3) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR3 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR3 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT6 = *bf_p++;
			PVP_DEB_DAT7 = *bf_p;
		}
		if ( SVP_DEB_SEL4 < 9 ) {
			switch(SVP_DEB_SEL4) {
				case 0:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x600000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_DPRMTOP);
					break;
				case 1:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_SRAMTOP);
					break;
				case 2:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x500000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_FROMTOP);
					break;
				case 3:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x800000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_FRAMTOP);
					break;
				case 4:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x870000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_OPRMTOP);
					break;
				default:
//SIT4					bf_p =(UNs *)(SVP_DEB_ADR4 + 0x400000);
					bf_p =(UNs *)(SVP_DEB_ADR4 + SH2_SRAMTOP);
					break;
			}
			PVP_DEB_DAT8 = *bf_p++;
			PVP_DEB_DAT9 = *bf_p;
		}
	}
}



/*
********************************************************************************
*  Module Name:		his_dat_mng
*  Function Name:	�ُ헚���ް��]������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2003-07-09
********************************************************************************
*/
void	his_dat_mng(void)
{
	UNs	w2b;
	UNl	w4b;

	SVP_MONALM_S01 = SV_MONALM_S01;
	SVP_MONALM_S02 = SV_MONALM_S02;
	SVP_MONALM_S03 = SV_MONALM_S03;
	SVP_MONALM_S04 = SV_MONALM_S04;

	if (GAMEN_NO == 69) {
		PV0_MONALM_P01 = PVP_MONALM_P01;
		PV0_MONALM_P02 = PVP_MONALM_P02;
		PV0_MONALM_P03 = PVP_MONALM_P03;
		PV0_MONALM_P04 = PVP_MONALM_P04;
		PV0_MONALM_A01 = PVP_MONALM_A01;
		PV0_MONALM_A02 = PVP_MONALM_A02;
		PV0_MONALM_A03 = PVP_MONALM_A03;
		PV0_MONALM_A04 = PVP_MONALM_A04;
		PV0_MONALM_A05 = PVP_MONALM_A05;
		PV0_MONALM_A06 = PVP_MONALM_A06;
		PV0_MONALM_A07 = PVP_MONALM_A07;
		PV0_MONALM_A08 = PVP_MONALM_A08;

		PV0_MONALM_B01 = PVP_MONALM_B01;
		PV0_MONALM_B01_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B01 & 0x8000) != 0 ) {
			PV0_MONALM_B01 = 0 - PV0_MONALM_B01;
			PV0_MONALM_B01_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B02 = PVP_MONALM_B02;
		PV0_MONALM_B02_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B02 & 0x8000) != 0 ) {
			PV0_MONALM_B02 = 0 - PV0_MONALM_B02;
			PV0_MONALM_B02_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B03 = PVP_MONALM_B03;
		PV0_MONALM_B03_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B03 & 0x8000) != 0 ) {
			PV0_MONALM_B03 = 0 - PV0_MONALM_B03;
			PV0_MONALM_B03_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B04 = PVP_MONALM_B04;
		PV0_MONALM_B04_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B04 & 0x8000) != 0 ) {
			PV0_MONALM_B04 = 0 - PV0_MONALM_B04;
			PV0_MONALM_B04_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B05 = PVP_MONALM_B05;
		PV0_MONALM_B05_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B05 & 0x8000) != 0 ) {
			PV0_MONALM_B05 = 0 - PV0_MONALM_B05;
			PV0_MONALM_B05_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B06 = PVP_MONALM_B06;
		PV0_MONALM_B06_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B06 & 0x8000) != 0 ) {
			PV0_MONALM_B06 = 0 - PV0_MONALM_B06;
			PV0_MONALM_B06_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B07 = PVP_MONALM_B07;
		PV0_MONALM_B07_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B07 & 0x8000) != 0 ) {
			PV0_MONALM_B07 = 0 - PV0_MONALM_B07;
			PV0_MONALM_B07_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_B08 = PVP_MONALM_B08;
		PV0_MONALM_B08_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_B08 & 0x8000) != 0 ) {
			PV0_MONALM_B08 = 0 - PV0_MONALM_B08;
			PV0_MONALM_B08_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C01 = PVP_MONALM_C01;
		PV0_MONALM_C01_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C01 & 0x80000000) != 0 ) {
			PV0_MONALM_C01 = 0 - PV0_MONALM_C01;
			PV0_MONALM_C01_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C02 = PVP_MONALM_C02;
		PV0_MONALM_C02_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C02 & 0x80000000) != 0 ) {
			PV0_MONALM_C02 = 0 - PV0_MONALM_C02;
			PV0_MONALM_C02_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C03 = PVP_MONALM_C03;
		PV0_MONALM_C03_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C03 & 0x80000000) != 0 ) {
			PV0_MONALM_C03 = 0 - PV0_MONALM_C03;
			PV0_MONALM_C03_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C04 = PVP_MONALM_C04;
		PV0_MONALM_C04_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C04 & 0x80000000) != 0 ) {
			PV0_MONALM_C04 = 0 - PV0_MONALM_C04;
			PV0_MONALM_C04_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C05 = PVP_MONALM_C05;
		PV0_MONALM_C05_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C05 & 0x80000000) != 0 ) {
			PV0_MONALM_C05 = 0 - PV0_MONALM_C05;
			PV0_MONALM_C05_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C06 = PVP_MONALM_C06;
		PV0_MONALM_C06_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C06 & 0x80000000) != 0 ) {
			PV0_MONALM_C06 = 0 - PV0_MONALM_C06;
			PV0_MONALM_C06_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C07 = PVP_MONALM_C07;
		PV0_MONALM_C07_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C07 & 0x80000000) != 0 ) {
			PV0_MONALM_C07 = 0 - PV0_MONALM_C07;
			PV0_MONALM_C07_SIGN = DISP_MN << 8;
		}

		PV0_MONALM_C08 = PVP_MONALM_C08;
		PV0_MONALM_C08_SIGN = DISP_PL << 8;
		if ( (PV0_MONALM_C08 & 0x80000000) != 0 ) {
			PV0_MONALM_C08 = 0 - PV0_MONALM_C08;
			PV0_MONALM_C08_SIGN = DISP_MN << 8;
		}
	}
}


/*
********************************************************************************
*  Module Name:		taikikaku_chg_mng
*  Function Name:	�ҋ@�p�ύX����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2004-05-19		V01i
********************************************************************************
*/
void	taikikaku_chg_mng(void)
{
	UNs		w2b;
	UNs		*w2b_p;
	UNs		seq;
	
	seq = SEQ_PAR_201;

	if (CB_SYS_PARAM279 == 1) {							// �ҋ@�_�Q����				V06m	2012/09/24
		seq &= ~cBIT5;
	}

	if (CB_SYS_PARAM045 == 1) {
		w2b = 0;
		if ( seq & (BIT_4+BIT_5+BIT_6) ) {
			if(seq & BIT_4) {							// �ҋ@�p�x�P�I���H
				w2b =1;
				w2b_p = &SV_TAIKI1_A12;
			}
			else if(seq & BIT_5) {						// �ҋ@�p�x�Q�I���H
				w2b =2;
				w2b_p = &SV_TAIKI2_A12;
			}
			else if(seq & BIT_6) {						// �ҋ@�p�x�R�I���H
				w2b =3;
				w2b_p = &SV_TAIKI3_A12;
			}
			else {
				w2b_p = &SV_TAIKI1_A12;					// DUMMY
			}

			SV_TAIKIKAKU_SRV = *w2b_p;
			SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

			if(SEQ_050_SV & BIT_1) {		//���]�@�H
				SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
			}
			SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)

			SVP_UPAREA_DIG0		= SV_TAIKIKAKU_SRV;				/* �ҋ@�_�p�x			*/
			if( SEQ_050_SV & BIT_1 ) {								//���]�@�H
				SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* �ҋ@�_�ʒu */
			}
			else {
				SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* �ҋ@�_�ʒu			*/
			}

			if (TAIKIKAKU_CHG_FLG != w2b)
			{											// �ҋ@�p�x�I��ς�����H
				TAIKIKAKU_CHG_FLG = w2b;
//V01m_a				SV_TAIKIKAKU_SRV = *w2b_p;

//V01m_a				SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

//V01m_a				if(SEQ_050_SV & BIT_1) {		//���]�@�H
//V01m_a					SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
//V01m_a				}
//V01m_a				SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)

				SVSW_CHG_FLG |=  BLK_MOT;
				if ( (GAMEN_NO == 3) || (GAMEN_NO == 4) || (GAMEN_NO == 6) ||
					 (GAMEN_NO == 28) || (GAMEN_NO == 29) || (GAMEN_NO == 30) ) {
					GAMNE_REDISP_COD = 0xff;								//��ʍĕ\���v��
				}
			}
		}
	}
}



/*
********************************************************************************
*  Module Name:		FURIKO_Cancel_mng
*  Function Name:	�U�q��\���w�߂̏���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2013-02-22		V06p
********************************************************************************
*/
void	FURIKO_Cancel_mng(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= FURIKO_SEQ_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & FURIKO_SEQ_LST;				// chg & old = ofe
	FURIKO_SEQ_LST = seq_bit;

	if( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30 ) {
		if ( (seq_one & BIT_15) || (seq_ofe & BIT_15) ) {
			if ( (SEQ_050_SV & BIT_2) == 0 ) {
				GAMNE_REDISP_COD = 0xff;
			}
		}
	}

}


/*
********************************************************************************
*  Module Name:		Gamen_Redisp_mng
*  Function Name:	��ʍĕ\������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:����		ON:2004-05-19		V01i
********************************************************************************
*/
void	Gamen_Redisp_mng(void)
{
// 2005-08-26 V01s ���f�w�߂̍ĕ`�����ۯ��͂���	if (CB_SYS_PARAM045 == 1) {
		if (GAMNE_REDISP_COD != 0) {
			GAMNE_REDISP_COD = 0;
			GAMEN_disp();								//��ʍĕ\��
		}
//	}
}


/*
********************************************************************************
*  Module Name:		KAT_ENB_GAMEN001_disp
*  Function Name:	GAMEN001�̎��Ɍ^�ް��Ǘ����L���ɂȂ����Ƃ��̉�ʍĕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�d���������ɉ��001��\���������A�^�ԍ������̂��\�����Ȃ��s��΍�
*					�����͕\�����鎞�ɁA�܂����ݽ�����S�ɓ����Ă��Ȃ��̂ŁASEQ_107��BIT_0
*					��ON���Ă��Ȃ����߁B
*
*  �� ��	:Shima		ON:2004-05-26			V01j
********************************************************************************
*/
void	KAT_ENB_GAMEN001_disp(void)
{
	UNs		xy_no;

	if (SEQ_PAR_107_BAK & BIT_0) { /*���ɗL���Ȃ牽�����Ȃ�*/ }		// �^�ް��Ǘ����ɗL���H
	else{
		if (SEQ_PAR_107 & BIT_0)					// �^�ް��Ǘ��L���ɂȂ����H
		{											// �͂�
			SEQ_PAR_107_BAK = SEQ_PAR_107;
			if (GAMEN_NO == 1)
			{
//SIT4				disp_all_s(GAMEN_NO, 0x00, 0x00);	//�S��ʕ\���p�������ށ��ޯĕϊ�
//				WDT_Rifresh();						//�����ޯ����- ��گ��
//				Alltbl_set();						//���ð��ق̍쐬
//				Under_grph();						//���i�̃O���t�B�b�N�Z�b�g		/* V01w */
//				xy_no = 1 | (21<<4) | (6<<10);		// 1�s��/21���ڂ���6�����\��
//				Lcd_cr(0, xy_no, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��
//				xy_no = 2 | (21<<4) | (4<<10);		// 2�s��/21���ڂ���6�����\��
//				Lcd_cr(0, xy_no, &LCD_WORK1[0][0][0]);		//��גP�ʕ\��

				GAMEN_disp();								//��ʍĕ\��
				
			}
			if ( (GAMEN_NO == 11) || (GAMEN_NO == 17) )		//V01h_c
			{
//SIT4				disp_all_s(GAMEN_NO, 0x00, 0x00);	//�S��ʕ\���p�������ށ��ޯĕϊ�
//				WDT_Rifresh();						//�����ޯ����- ��گ��
//				Alltbl_set();						//���ð��ق̍쐬
//				Lcd_line(00, 1, E_line_bf, &LCD_WORK1[0][0][0]);		//�s�\��(LCD1)

				GAMEN_disp();								//��ʍĕ\��

			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		Sampring_Disp
*  Function Name:	�����ݸޒ����������\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�����ݸޒ����������\��
*
*  �� ��	:Shima		ON:2006-07-13			V01v
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	Sampring_Disp(void)
{
	U1b	*src_p;
	U2b	*dst_p;
	U2b	k;

	if (GAMEN_NO != 1){
		return;
	}
	if (SEQ_PAR_101 & BIT_13) {
		src_p = kan_rom_set(0x217c);				//"��"(0x217c) JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[1][0][0];
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p = dst_p+39;
		}
	}
	else {
		src_p = kan_rom_set(0x2121);				//"�@"(0x2121) JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[1][0][0];
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p = dst_p+39;
		}
	}
	Lcd_cr(00, 0x0801, &LCD_WORK1[0][0][0]);					//1�s��,0����,2������\������B
}
#else
void	Sampring_Disp(void)
{
	UNs		MARU, col;

	MARU  = 0x819C;	//��

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_101 & BIT_13) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//��߰�
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		0,						/*t_p->X_POS,*/
		32,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
	disp_moji_s_rif (
		2,				/*t_p->M_LEN,*/
		0,				/*t_p->X_POS,*/
		32,				/*t_p->Y_POS,*/
		0x0101			/*t_p->SIZE,*/
		);
}
#endif

/*
********************************************************************************
*  Module Name:		Trend_disp
*  Function Name:	����ތv�������������\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����ތv�������������\��
*
*  �� ��	:Shima
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	Trend_disp(void)
{
}

void	Trend_stop(void)
{
}

#else

void	Trend_disp(void)
{
	UNs		MARU, col;

	MARU  = 0x81a1;	//��

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_101 & BIT_12) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//��߰�
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		0,						/*t_p->X_POS,*/
		48,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VBASE
		);
	disp_moji_s_rif (
		2,				/*t_p->M_LEN,*/
		0,				/*t_p->X_POS,*/
		48,				/*t_p->Y_POS,*/
		0x0101			/*t_p->SIZE,*/
		);
}

void	Trend_stop(void)
{
	UNs		MARU, col;

	if (SEQ_PAR_101 & BIT_11)				//�g�����h��~�H
	{
		if (SEQ_056_SV & BIT_11)			//�g�����h���n�m��
		{
			SEQ_056_SV &= ~BIT_11;			//�g�����h������
			if (GAMEN_NO == 66)				//�g�����h��ʕ\�����H
			{
				GAMEN_disp();				//��ʍĕ\��
			}
			SVSW_CHG_FLG |= 0x0008;
		}
	}
}
#endif

/*
********************************************************************************
*  Module Name:		KASIN_mark_Disp
*  Function Name:	���U������s���������\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���U������s���������\��
*
*  �� ��	:Shima		ON:2010/08/30	V05r
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	KASIN_mark_Disp(void)
{
}

#else

void	KASIN_mark_Disp(void)
{
	UNs		MARU, col;

	MARU  = 0x819F;	//��

	if (GAMEN_NO != 1){
		return;
	}

	if (SEQ_PAR_113 & BIT_4) {
		col = 1;
	}
	else
	{
		col = GAMENn_SCR_COL;
		MARU  = 0x2121;	//��߰�
	}
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		16,						/*t_p->X_POS,*/
		32,						/*t_p->Y_POS,*/
		col,					/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&MARU, 
		LCD_VRAM
		);
}


#endif


void cop2_pvdata_sin(void)
{
	if ( (PVP_ZURE_PLS & 0x8000) == 0) {
		PVW_ZURE_PLS_SIN = 0;
		PVW_ZURE_PLS = PVP_ZURE_PLS;
	}
	else {
		PVW_ZURE_PLS_SIN = 1;
		PVW_ZURE_PLS = PVP_ZURE_PLS * -1;
	}

	if ( (PVP_ZURE_RNA & 0x8000) == 0) {
		PVW_ZURE_RNA_SIN = 0;
		PVW_ZURE_RNA = PVP_ZURE_RNA;
	}
	else {
		PVW_ZURE_RNA_SIN = 1;
		PVW_ZURE_RNA = PVP_ZURE_RNA * -1;
	}

	if ( (SVB_BAKORG_PLS1 & 0x80000000) == 0) {
		PVW_BAKORG_SIN1 = 0;
		SVBW_BAKORG_PLS1 = SVB_BAKORG_PLS1;
	}
	else {
		PVW_BAKORG_SIN1 = 1;
		SVBW_BAKORG_PLS1 = SVB_BAKORG_PLS1 * -1;
	}

	if ( (SVB_BAKORG_PLS2 & 0x80000000) == 0) {
		PVW_BAKORG_SIN2 = 0;
		SVBW_BAKORG_PLS2 = SVB_BAKORG_PLS2;
	}
	else {
		PVW_BAKORG_SIN2 = 1;
		SVBW_BAKORG_PLS2 = SVB_BAKORG_PLS2 * -1;
	}

	if ( PVP_RNABUP_ENB == 1 )
	{
		PV_RENIA_BUP1	=	PVP_RENIA_BUP1;//���j�A�X�P�[���o�b�N�A�b�v�p
		PV_RENIA_BUP2	=	PVP_RENIA_BUP2;//���j�A�X�P�[���o�b�N�A�b�v�p
		PV_RENIA_BUP3	=	PVP_RENIA_BUP3;//���j�A�X�P�[���o�b�N�A�b�v�p
		PV_RENIA_BUP4	=	PVP_RENIA_BUP4;//���j�A�X�P�[���o�b�N�A�b�v�p
	}

	if ( CMD_KJTECH_DSP1 != 0 )			// V02a
	{
		PV_ARA1_KAJ_T2	=	PVP_ARA1_KAJ_T2;
	}
}

void real_kajyu_check(void)
{
	UNs		ww0, ww1;

	ww0 = 0;
	if ( CMD_KJTECH_DSP1 != 0 )
	{
		ww1 = PVP_ARA1_KAJ_T2 + GMN_PAR011;
		if (ww1 < SV_KAJYUU_OBJP )				// �ύX�傫�����H
		{
			ww0 = 0xff;
		}
		ww1 = PVP_ARA1_KAJ_T2 - GMN_PAR011;
		if(ww1 & 0x8000)
		{
			ww1 = 0;
		}
		if (ww1 > SV_KAJYUU_OBJP )				// �ύX���������H
		{
			ww0 = 0xff;
		}
		if (ww0 != 0) {
			SEQ_PAR_050 |= BIT_11;
		}
		else {
			SEQ_PAR_050 &= ~BIT_11;							// �ύX�傫����������������
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEIDOUSEINOU_mng
*  Function Name:	�������\�����؊���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
void	SEIDOUSEINOU_mng(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;

	seq_chg = seq_bit = SEQ_PAR_113 & (BIT_2+BIT_1+BIT_0);		// new
	seq_chg ^= SEIDOU_SEQ_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & SEIDOU_SEQ_LST;				// chg & old = ofe
	SEIDOU_SEQ_LST = seq_bit;

	/*** �\���؊������� ***/
	if (seq_one & BIT_2)		Disp_seidouseinou(1, LCD_VRAM);		//�������\�\��
	if (seq_ofe & BIT_2)		Disp_seidouseinou(0, LCD_VRAM);		//�ʏ�\��


#if 0	//2011/09/12  �ύX  V06h
	/*** �������\�������������Ϗ��� ***/
	if (seq_one & BIT_0)	PVTIM_seidouseinou_inter = SV_INTER_TIM * 60;		//�����ؾ��(min)
	if (seq_bit & BIT_0)
	{
		if (PVTIM_seidouseinou_inter == 0)
		{
			SEQ_PAR_058 |= BIT_0;
		}
	}
	if (seq_ofe & BIT_0)	SEQ_PAR_058 &= ~BIT_0;
	
	/*** �������\�����\����Ϗ��� ***/
//V06	if (seq_one & BIT_1)	PVTIM_seidouseinou_yokok = GMN_PAR040 * 60;			//�����ؾ��(min)
	if (seq_one & BIT_1)	PVTIM_seidouseinou_yokok = (SV_INTER_TIM - GMN_PAR040) * 60;			//�����ؾ��(min)
	if (seq_bit & BIT_1)
	{
		if (PVTIM_seidouseinou_yokok == 0)
		{
			SEQ_PAR_058 |= BIT_1;
		}
	}
	if (seq_ofe & BIT_1)	SEQ_PAR_058 &= ~BIT_1;
#endif

	/*** �������\�������������Ϗ��� ***/
	if (seq_one & BIT_1) {
		PV_INTER_TIM = GMN_PAR039 * 60;		//�����ؾ��(min)
	}
	if (PV_INTER_TIM == 0) {
		SEQ_PAR_058 |= BIT_0;
	}
	else {
		SEQ_PAR_058 &= ~BIT_0;
	}

	/*** �������\�����\����Ϗ��� ***/
	if ( PV_INTER_TIM <= (GMN_PAR040 * 60) ) {
		SEQ_PAR_058 |= BIT_1;
	}
	else {
		SEQ_PAR_058 &= ~BIT_1;
	}

	PV0_INTER_TIM = PV_INTER_TIM / 60;


	/*** �������\��������޳�\������ ***/
	seq_chg = seq_bit = SEQ_PAR_103 & BIT_11;		// new
	seq_chg ^= SEIDOU_DSP_LST;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & SEIDOU_DSP_LST;				// chg & old = ofe
	SEIDOU_DSP_LST = seq_bit;

	if (seq_bit & BIT_11)
	{
		if (seq_one & BIT_11)
		{
			if (GAMEN_NO != 1) 
			{
				SEI_csr_ichk();							//���Y�J�[�\���ʒu������
				CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
				disp_stg = 00;							//���Y���
				disp_stg_sel = E_sstg_init;				//���Y[��{]��
				GAMEN_NO = 1;
				GAMEN_disp();						//��ʕ\��
			}
			disp_stg_sel = E_sstg_seidou;			//���Y[��������WIN]��
			WINDOW_NO = 21;
			WIN_gamen_disp();						//�E�C���h�E��ʕ\��
		}
	}
	else
	{
		SEQ_PAR_058 &= ~BIT_4;

		if (seq_ofe & BIT_11)
		{
			if( DSET_SW_FLG & BIT_10 ) 
			{
				disp_stg = 02;							//�f�[�^�ݒ���
				disp_stg_sel = E_dstg_init;				//�f�[�^�ݒ�[��{]��
				GAMEN_NO = 17;
				GAMEN_disp();						//��ʕ\��
			}
			else if( 00 != (SEQ_PAR_101 & BIT_10) )
			{
				DAN_csr_ichk();						//�i��J�[�\���ʒu������
				if(SEQ_PAR_101 & BIT_5 ||
					DAN_GAMEN_NON == 0x00 )
				{
					DAN_KEY_FLG = 0xff;				//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
					disp_stg = 01;					//�i����
					disp_stg_sel = E_kstg_init;		//�i��[��{]��
					GAMEN_NO = 7;
					if (SEQ_016_SV & BIT_10)
					{
						GAMEN_NO = 8;
					}
					GAMEN_disp();							//��ʕ\��
				}
				else
				{
					SEI_csr_ichk();							//���Y�J�[�\���ʒu������
					CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
					disp_stg = 00;							//���Y���
					disp_stg_sel = E_sstg_init;				//���Y[��{]��
					GAMEN_NO = 1;
					GAMEN_disp();								//��ʕ\��
				}
				DAN_KEY_FLG = 0x00;						//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
			}
			else{
				SEI_csr_ichk();							//���Y�J�[�\���ʒu������
				CSR_FLG = 0;							//�z�[���|�W�V�����Z�b�g
				disp_stg = 00;							//���Y���
				disp_stg_sel = E_sstg_init;				//���Y[��{]��
				GAMEN_NO = 1;
				GAMEN_disp();								//��ʕ\��
				DAN_KEY_FLG = 0x00;						//�^�i��L�[�ɂč��@�\�^��ʈړ����̏���
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SEIDOUSEINOU_mng
*  Function Name:	�������\�����؊���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2010-08-11	V05r
********************************************************************************
*/
#define		Meter_start_Xdot	16*6+3	// 96dot
#define		Meter_start_Ydot	16*5	// 80dot
#define		OneMeter_Xleg		16		// 16dot
#define		OneMeter_Yleg		16		// 16dot
void	EcoMeter_Disp(void)
{
	UNs	bit, xcnt, ycnt, Mcnt;
	UNs	xdot, ydot;

	UNl	bg_adr;
	UNb	*bg_col, Eco_col;

	if ((SEQ_PAR_103 & BIT_12) == 0)		return;
	if (GAMEN_NO != 1)						return;

	bg_adr = (UNl)&GAM_INF_TBL;
	bg_adr += GAM_INF_TBL_OFS;
	bg_adr += 514;
	bg_adr += 6;						//���Y��ʂ̽�ذݐF���i�[����Ă�����ڽ
	bg_col = (UNb *)bg_adr;

	bit = PVP_ECO_METER;

	for (Mcnt=0; Mcnt<8; Mcnt++, bit=bit>>1)
	{
		ydot = Meter_start_Ydot;				//Y����dot
		xdot = Meter_start_Xdot;
		xdot += Mcnt * (OneMeter_Xleg-1);		//n�ڂ�X����dot

		if (bit & BIT_0) {					//Ұ��F�\���H
			Eco_col = COL_EcoM0 + Mcnt;
		}
		else {
			Eco_col = *bg_col;
		}

		Dsp_sikaku1(xdot, ydot, OneMeter_Xleg, OneMeter_Yleg, COL_BLACK, Eco_col);
	}
}


/*
********************************************************************************
*  Module Name:		LANG_SEQ_OUT
*  Function Name:	�\��������r�b�g�łr�d�p�֏o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	LANG_SEQ_OUT(void)
{
	UNs		dt, seq, cnt;

//V06n	dt = SV_LANGUAGE;
	dt = SV_LANGUAGE - 1;
	if (dt > 2) {
//V06n		seq = 0;
		seq = BIT_12;
	}
	else {
		seq = BIT_12;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_050 = (SEQ_PAR_050 & ~(BIT_12+BIT_13+BIT_14)) | seq;
}


/*
********************************************************************************
*  Module Name:		HAN_MODE_SEQ_OUT
*  Function Name:	���]���[�h �o�^�r�ݒ���r�b�g�łr�d�p�֏o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	HAN_MODE_SEQ_OUT(void)
{
	UNs		dt, seq, cnt;

	dt = SV_HAN_P;
	if (dt > 9) {
//V06n		seq = 0;
		seq = 0x0001;
	}
	else {
		seq = 0x0001;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_048 = (SEQ_PAR_048 & ~0x3ff) | seq;

	dt = SV_HAN_S;
	if (dt > 9) {
//V06n		seq = 0;
		seq = 0x0001;
	}
	else {
		seq = 0x0001;
		for (cnt=0; cnt<dt; cnt++) {
			seq<<=1;
		}
	}
	SEQ_PAR_049 = (SEQ_PAR_049 & ~0x3ff) | seq;
}


/*
********************************************************************************
*  Module Name:		DIE_HEIGHT_OFFSET
*  Function Name:	�_�C�n�C�g�I�t�Z�b�g
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2012-09-24	V06m, V06n
********************************************************************************
*/
void	DIE_HEIGHT_OFFSET(void)
{
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;
	S4b		ofs;
	S4b		sWK1, sWK2, sWK3, sWK4;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= DIEH_OFS_FLG;						// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & DIEH_OFS_FLG;				// chg & old = ofe
	DIEH_OFS_FLG = seq_bit;

	if (seq_one & cBIT10) {				//�{�I�t�Z�b�g�w��
		ofs = (S4b)GMN_PAR020;
		ofs *= 1000;					//�����_3����
		ofs = cnv_mm_inch(ofs, 2);
		SV0_RNAPOS_MINO = SV_RNAPOS_MINP + ofs;			//�@�B����
		SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP + ofs;			//�@�B���

		ofs = (S4b)GMN_PAR020;
		ofs *= 10;						//�����_1����
		ofs = cnv_mm_inch(ofs, 2);
		SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1 + ofs;			//�_�C�n�C�g����
		SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2 + ofs;			//�_�C�n�C�g���

		SVSW_CHG_FLG |= 0x0001;
	}

	if (seq_one & cBIT11) {				//�|�I�t�Z�b�g�w��
		ofs = (S4b)GMN_PAR020;
		ofs *= 1000;					//�����_3����
		ofs = cnv_mm_inch(ofs, 2);

		sWK1 = (S4b)SV_RNAPOS_MINP;		//�@�B����
		sWK1 -= ofs;
		if (sWK1 < 1000) {
			sWK1 = 1000;
		}
		sWK2 = (S4b)SV_RNAPOS_MAXP;		//�@�B���
		sWK2 -= ofs;
		if (sWK2 < sWK1) {
			sWK2 = sWK1;
		}

		ofs = (S4b)GMN_PAR020;
		ofs *= 10;						//�����_1����
		ofs = cnv_mm_inch(ofs, 2);

		sWK3 = (S4b)SV_DAIHAI_LNG1;		//�_�C�n�C�g����
		sWK3 -= ofs;
		sWK3 *= 100;
		if (sWK3 < sWK1) {
			sWK3 = sWK1;
		}
		sWK4 = (S4b)SV_DAIHAI_LNG2;		//�_�C�n�C�g���
		sWK4 -= ofs;
		sWK4 *= 100;
		if (sWK4 < sWK1) {
			sWK4 = sWK1;
		}

		SV0_RNAPOS_MINO = sWK1;			//�@�B����
		SV0_RNAPOS_MAXO = sWK2;			//�@�B���
		SV0_DAIHAI_LNG1O = sWK3 / 100;	//�_�C�n�C�g����
		SV0_DAIHAI_LNG2O = sWK4 / 100;	//�_�C�n�C�g���

		SVSW_CHG_FLG |= 0x0001;
	}

	if ( (seq_ofe & cBIT10) || (seq_ofe & cBIT11) ) {
		SV0_RNAPOS_MINO = SV_RNAPOS_MINP;			//�@�B����
		SV0_RNAPOS_MAXO = SV_RNAPOS_MAXP;			//�@�B���
		SV0_DAIHAI_LNG1O = SV_DAIHAI_LNG1;			//�_�C�n�C�g����
		SV0_DAIHAI_LNG2O = SV_DAIHAI_LNG2;			//�_�C�n�C�g���

		SVSW_CHG_FLG |= 0x0001;
	}
}


/*
********************************************************************************
*  Module Name:		FURIKO_SPEC_ON_OFF
*  Function Name:	�U�q(������)�d�lON/OFF
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2012-09-24	V06m
********************************************************************************
*/
void	FURIKO_SPEC_ON_OFF(void)
{
#if 0	//V06p(DEL)
	UNs		seq_chg, seq_bit, seq_one, seq_ofe;
	UNs		gam_chg;

	if (disp_stg == 1)		return;

	gam_chg = 0;

	seq_chg = seq_bit = SEQ_PAR_113;				// new
	seq_chg ^= FURIKO_FLG;							// new ^ old = chg
	seq_one = seq_chg & seq_bit;					// chg & new = one
	seq_ofe = seq_chg & FURIKO_FLG;				// chg & old = ofe
	FURIKO_FLG = seq_bit;

	if (seq_one & cBIT14) {				//�d�l�ݒ�ON�w��
		if (SEQ_023_SV & BIT_8) {
			//����ON�Ȃ牽�����Ȃ��B
		}
		else {
			SEQ_023_SV |= BIT_8;			//�d�l�ݒ�121(������)  0N
			FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
			
			gam_chg = 1;
		}
	}

	if (seq_one & cBIT15) {				//�d�l�ݒ�OFF�w��
		if (SEQ_023_SV & BIT_8) {
			SEQ_023_SV &= ~BIT_8;			//�d�l�ݒ�121(������)  0FF
			FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

			gam_chg = 1;
		}
		else {
			//����OFF�Ȃ牽�����Ȃ��B
		}
	}

	if (gam_chg) {
		MOT_MODE_BAK = SEQ_050_SV;				//V06n
		if (disp_stg == 0) {
			disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
			CAR_mkssi_set();					//�P�ʐ؊�
			GAMEN_NO = 3;
			GAMEN_disp();						//��ʕ\��
			SEQ_PAR_051 |= BIT_14;				//��ʑJ�ڗL��		V06n
		}
		else if (disp_stg == 2) {
			disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
			CAR_mkssi_set();					//�P�ʐ؊�
			GAMEN_NO = 28;
			GAMEN_disp();						//��ʕ\��
			SEQ_PAR_051 |= BIT_14;				//��ʑJ�ڗL��		V06n
		}
		else if (disp_stg == 3) {
			disp_stg = 2;						//�f�[�^�ݒ��ʂ�
			disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�����ݒ�]��
			CAR_mkssi_set();					//�P�ʐ؊�
			GAMEN_NO = 28;
			GAMEN_disp();						//��ʕ\��
			SEQ_PAR_051 |= BIT_14;				//��ʑJ�ڗL��		V06n
		}
	}
#endif
}


/*
********************************************************************************
*  Module Name:		SYSSET_SEQ_OUT
*  Function Name:	�V�X�e���ݒ��ʂւ̑J�ډ^�s���r�b�g�łr�d�p�֏o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2012-10-14	V06n
********************************************************************************
*/
void	SYSSET_SEQ_OUT(void)
{
	if (SEQ_PAR_101 & cBIT1) {					//�V�X�e���ݒ�ύX��
		SEQ_PAR_051 |= cBIT15;					//�V�X�e���ݒ��ʂւ̑J�ډ�
	}
	else {
		if (SEQ_PAR_113 & cBIT13) {				//�V�X�e���ݒ��ʂւ̑J�ڋ���
			SEQ_PAR_051 |= cBIT15;				//�J�ډ�
		}
		else {
			SEQ_PAR_051 &= ~cBIT15;				//�J�ڕs��
		}
	}
	
}


/*** END ***/



#if	E_DEBUG_1											//�f�o�b�O���[�h�w��

;/***************************************************************/
;/*								*/
;/*		�d�Q�o�q�n�l�@�o�b�N�A�b�v�f�[�^�`�F�b�N	*/
;/*		�i�d�Q�o�Q�q�n�l�Q�c�s�Q�b�g�j�j		*/
;/*								*/
;/*				�����@�@�@�@��������		*/
;/*								*/
;/***************************************************************/
E2_DATA_SET		PROC	NEAR
;
;
;
;
	CALL	SV_EEPROM_CHK			;/* �ݒ�l�d�d�o�q�n�l�f�[�^�`�F�b�N*/
	CALL	CB_V55_H8_HND1			;/* �C�j�V�����n���h�V�F�C�N���� */
;
;
	PUSH	ES				;
	MOV	AX,SEQ_RAM			;
	MOV	ES,AX				;
;
	MOV	AL,SEQ_016_SV			;/* �����[�g�h�^�n�L���Z�b�g */
	AND	AL,00000001B			;
	MOV	ES:SEQ_RIO_STS,AL		;
	POP	ES				;
;
;
	MOV	TAIKI_LST,0FFFFH		;
;
;
;
	MOV 	AX,ENCO_DATA_HEX	; NOW DEG --> DX
;
	PUSH	ES			;
	MOV	BX,SEQ_RAM		;
	MOV	ES,BX			;
	MOV	BX,165			;
	MOV	DX,165+30		;
	TEST	ES:SEQ_PAR_222,01000000B;
	POP	ES			;
	JZ	COUNT_DEC_0100		;
	MOV	BX,165-30		;
	MOV	DX,165			;
;
COUNT_DEC_0100:
;
	CMP	AX,BX			;
	JNB	COUNT_DEC_010		;
	JMP	COUNT_DEC_170		;
COUNT_DEC_010:
	CMP	AX,DX			;
	JB	COUNT_DEC_020		;

;




	JMP	COUNT_DEC_170		;
COUNT_DEC_020:
;
	TEST	SEQ_017_SV,BIT_1		;/* �g�[�^���J�E���g�P�@�O���J�E���g�H */
	JNZ	COUNT_DEC_110			;YES
	TEST	SEQ_017_SV,BIT_0		;/* �g�[�^���J�E���^�P�L��H */
	JZ	COUNT_DEC_110			;NO
	TEST	SEQ_038_SV,BIT_0		;/* �g�[�^���J�E���^�P�� */
	JZ	COUNT_DEC_110			;NO
;
;
	SUB	PV_TOTLC1_B3,1 			;/* �g�[�^���J�E���^�P */
	SBB	PV_TOTLC1_B3+2,0		;/* �g�[�^���J�E���^�P */
COUNT_DEC_110:
COUNT_DEC_120:
;
	PUSH	ES				;
	MOV	AX,SEQ_RAM			;
	MOV	ES,AX				;
;
;
	TEST	SEQ_017_SV,BIT_5		;/* ���b�g�J�E���g�P�@�O���J�E���g�H */
	JNZ	COUNT_DEC_130			;YES
	TEST	SEQ_017_SV,BIT_4		;/* ���b�g�J�E���g�P�@�L��H */
	JZ	COUNT_DEC_130			;NO
	TEST	SEQ_038_SV,BIT_2		;/* ���b�g�J�E���g�P�@����H */
	JZ	COUNT_DEC_130			;NO
	TEST	ES:SEQ_PAR_039,BIT_0		;/* ���b�g�J�E���g�P�@�t�o�H */
	JNZ	COUNT_DEC_130			;YES
;
	MOV	AX,SV_PUR1SV_B4			;
	MOV	DX,SV_PUR1SV_B4+2		;
	CMP	PV_LOTCT1_B4+2,DX		;
	JC	COUNT_DEC_125			;
	JNZ	COUNT_DEC_130			;
	CMP	PV_LOTCT1_B4,AX			;
	JA	COUNT_DEC_130			;
COUNT_DEC_125:					;
;
	SUB	PV_LOTCT1_B4,1 			;/* ���b�g�J�E���^�P */
	SBB	PV_LOTCT1_B4+2,0		;/* ���b�g�J�E���^�P */
;
COUNT_DEC_130:					;
;
;
	TEST	SEQ_017_SV,BIT_7		;/* ���b�g�J�E���g�Q�@�O���J�E���g�H */
	JNZ	COUNT_DEC_140			;YES
	TEST	SEQ_017_SV,BIT_6		;/* ���b�g�J�E���g�Q�@�L��H */
	JZ	COUNT_DEC_140			;NO
	TEST	SEQ_038_SV,BIT_3		;/* ���b�g�J�E���g�Q�@����H */
	JZ	COUNT_DEC_140			;NO
	TEST	ES:SEQ_PAR_039,BIT_1		;/* ���b�g�J�E���g�Q�@�t�o�H */
	JNZ	COUNT_DEC_140			;YES
;
	MOV	AX,SV_PUR2SV_B41		;
	MOV	DX,SV_PUR2SV_B41+2		;
	CMP	PV_LOTCT2_B41+2,DX		;
	JC	COUNT_DEC_135			;
	JNZ	COUNT_DEC_140			;
	CMP	PV_LOTCT2_B41,AX		;
	JA	COUNT_DEC_140			;
COUNT_DEC_135:					;
;
;
;
;sit-2		TEST	SEQ_020_SV,BIT_2		;
;sit-2		JNZ	COUNT_DEC_140			;
;
	SUB	PV_LOTCT2_B41,1			;/* ���b�g�J�E���^�Q */
	SBB	PV_LOTCT2_B41+2,0		;/* ���b�g�J�E���^�Q */
;
COUNT_DEC_140:					;
;
;
	POP	ES				;
;
	SUB	PV_LIFE_COUNT,1			;
	SBB	PV_LIFE_COUNT+2,0		;
	SBB	PV_LIFE_COUNT+4,0		;
;V02	SBB	PV_LIFE_COUNT+6,0		;
;
COUNT_DEC_170:					;
;
;
	JMP	COUNT_DEC_END			;
;
;
;
;
COUNT_DEC_END:

;
	RET					;
;
E2_DATA_SET		ENDP

//;/***************************************************************/
//;/*								*/
//;/* 		�ݒ�l�d�d�o�q�n�l�f�[�^�`�F�b�N		*/
//;/*		�i�r�u�Q�d�d�o�q�n�l�Q�b�g�j�j			*/
//;/*								*/
//;/*			�n�t�s���a�j�t�o�Q�q�`�l�Q�d�q�q	*/
//;/*			�@�@�@���r�u�Q�b�g�j�Q�d�q�q		*/
//;/*								*/
//;/*				�����@�@�@�@��������		*/
//;/*								*/
//;/***************************************************************/
//SV_EEPROM_CHK	PROC	FAR
//;
//	PUSH	DS				;
//	PUSH	ES				;
//;
//	CALL	FAR PTR WDT_RESET		;V05
//;
//	CALL	FAR PTR SUM_CHK_CHK		;/* �ݒ�l�T���`�F�b�N�R�[�h�`�F�b�N	*/
//;
//	MOV	AX,BAK_RAM			;
//	MOV	DS,AX				;
//	MOV	AX,DAT_RAM			;
//	MOV	ES,AX				;
//;
//	MOV	DI,OFFSET SV_TOP		;/* �d�Q�o�q�n�l���f�[�^�Ǎ� */
//	MOV	SI,DI				;
//	MOV	CX,OFFSET SV_END		;/*  */
//	MOV	CX,2000H/2			;
//;
//	SUB	SI,SV_OFFSET			;
//	CLD					;
//	REP	MOVSW				;
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	MOV	SI,OFFSET PV_TOTLC1_B3 		;
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,40H				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	SI,OFFSET PV_CB1_MAXSPD		;
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,4				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	SI,OFFSET MCN_MENT_CNT1		;/* �@�B���R�[�_�Ǎ� */
//	MOV	DI,SI				;
//	SUB	SI,SV_OFFSET			;
//	MOV	CX,64				;
//	CLD					;
//	REP	MOVSB				;
//;
//	MOV	AX,DAT_RAM			;
//	MOV	DS,AX				;
//;
//	MOV	POWRE_OK_FLG,9876H		;
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	SYS_CBDATA_READ			;V05/* �V�X�p�����N���b�`�ݒ�f�[�^�ǂݍ��� */
//;
//	CALL	KEEP_RY_BAK			;/*V02 �L�[�v�����[�f�[�^�ԋp	 		*/
//;
//SV_EEPROM_CHK_500:
//	PUSH	ES				;
//	MOV	AX,SEQ_ROM			;
//	MOV	ES,AX				;
//	XOR	AH,AH				;
//	MOV	AL,ES:ROM1_PAR_PSMOD_SEL	;
//	MOV	SV_PSDIMD_A1,AX			;/* PSDI MODE No. */
//	POP	ES				;
//;
//	CMP	SV_CHK_ERR,0			;/* �ݒ�l�ُ�L��H */
//	JNE	SV_EEPROM_CHK_600		; YES
//;
//	MOV	SVSW_CHG_FLG,10111111B		;
//	CALL	GAM_SV_DTST			;/* �b�^�a�̂r�u�f�[�^�i�[ */
//;
//SV_EEPROM_CHK_600:
//;
//;
//;/*************		�d�l�l�l�`�w�f�[�^�`�F�b�N�@'95-04-27	*************/
//;
//	CMP	SV_MAXSPM_A14,330		;
//	JBE	E2_DATA_SET_000			;
//	MOV	SV_MAXSPM_A14,330		;
//;
//E2_DATA_SET_000:
//;
//;/***************************************************************************/
//;
//	MOV	AL,SEQ_025_SV			;/* ���O����؊��L��H */
//	AND	AL,BIT_5			;
//	MOV	GENGO_CHG_LAST,AL		;
//	CALL	GENGO_SEG_SET			;'98-07-17/* ����Z�O�����g�m�� */
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	SEQ_SVDATA_SET			;/* �r�d�p�̂r�u�f�[�^�i�[ */
//;
//	MOV	PODATA_SET_FLG,0FFH		;
//	CALL	OPDATA_BAK			;/* �I�v�V�����̌��ʒu�f�[�^�Ԋ� */
//	CALL	OPDATA_SET_KAKU			;/* �I�v�V�����[�f�[�^�]������*/
//	CALL	FAR PTR WDT_RESET		;sit-2
//	CALL	POSDATA_SET_KAKU		;/* �|�W�V���i�[�f�[�^�]������*/
//	CALL	OPDATA_SYS_KAKU			;/* �I�v�V�����ɃV�X�p���i�[  �u�O�R */
//;
//	PUSH	ES				;/* �i�p�ݒ�f�[�^�������݃t���O�Z�b�g */
//	MOV	AX,SEQ_RAM			;
//	MOV	ES,AX				;
//	MOV	ES:ENTFLG,0FFH			;
//	POP	ES				;
//;
//	CMP	SV_CHK_ERR,0			;/* �S�s���ɂĈُ햳���H */
//	JE	SV_EEPROM_CHK_700		; YES
//;
//	MOV	AX,SEQ_RAM			;
//	MOV	ES,AX				;
//;
//	MOV	ES:BKUP_RAM_ERR,0FFH		;
//	MOV	AL,SV_SUM1_ERR			;
//	OR	AL,SV_SUM2_ERR			;
//	OR	AL,SV_DPRAM_ERR			;/* �b�^�a�c�D�o�D�q�`�l�ƍ��ُ�t���O�Z�b�g */
//	MOV	ES:SEQ_PAR_078,AL		;
//;
//SV_EEPROM_CHK_700:
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	FAR PTR INI_POSTION_CHK			;/* �|�W�V���i�[�f�[�^�@�C�j�V�����`�F�b�N����	*/
//;
//	CALL	FAR PTR ONOFF_SUB			;/* �d�l�L�薳���ɂ����ؐ��� */
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//	CALL	KIDO_DATA_SET			;/* �P�x�\���p�f�[�^�쐬 */
//	CALL	CAMNAME_PON_READ		;/* �d���������̔ėp�J�����̃f�[�^�Ǎ�	*/
//	CALL	CAR_MKSSI_SET			;/* �P�ʐ؊��f�[�^�i�[����			*/
//;
//	CALL	FAR PTR WDT_RESET		;sit-2
//;
//;V02/*********	  �o�[�W�����m���D�Z�b�g  	******************************/
//;
//	MOV	PV_GMNVER_A1,CPUC_VER1		;/* �b�o�t�|�b�o�[�W�����m���D�Z�b�g */
//	MOV	PV_GMNVER_A1+1,CPUC_VER2	;/* �b�o�t�|�b�o�[�W�����m���D�Z�b�g */
//	MOV	PV_GMNVER_A1+2,CPUC_VER3	;/* �b�o�t�|�b�o�[�W�����m���D�Z�b�g */
//	MOV	PV_GMNVER_A1+3,CPUC_VER4	;/* �b�o�t�|�b�o�[�W�����m���D�Z�b�g */
//;
//;
//;V02/*************************************************************************/
//
//;
//;/*********	  �o�[�W�����m���D�Z�b�g  	******************************/
//	PUSH	DS				;
//	PUSH	ES				;
//	MOV	AX,SYS_ROM2
//	MOV	DS,AX				; ES = DATA RAM SEG
//	MOV	AX,DAT_RAM
//	MOV	ES,AX				; ES = DATA RAM SEG
//;
//	MOV	SI,OFFSET ROM_VERTION_DISP	;
//	MOV	DI,OFFSET PV_CBBVER_A1+5	;V02/* �o�[�W�����m���D */
//	MOV	CX,6				;
//SV_EEPROM_CHK_800:
//	MOV	AL,DS:[SI]			;
//	MOV	ES:[DI],AL			;
//	INC	SI				;
//	DEC	DI				;
//	LOOP	SV_EEPROM_CHK_800		;
//;
//;
//	MOV	AX,SEQ_ROM			;
//	MOV	DS,AX				;
//	MOV	DI,OFFSET PV_SYSVER_A1+1	;'98-09-01/* �V�X�p���o�[�W���� */
//	MOV	SI,OFFSET SYS_ROM_VER		;
//	MOV	CX,2				;
//SV_EEPROM_CHK_810:
//	MOV	AL,DS:[SI]			;
//	MOV	ES:[DI],AL			;
//	INC	SI				;
//	DEC	DI				;
//	LOOP	SV_EEPROM_CHK_810		;
//;
//	POP	ES				;
//	POP	DS				
//;/***************************************************************************/
//	MOV	SEI_ON6_LST1,0FFH		;/* �d���������K���i���̍��ڗL���`�F�b�N�����邽�߁B */
//;
//	CALL	ROTTO_CHK			;/* ���b�g�J�E���^�A�b�v�`�F�b�N		*/
//;
//	CALL	MLD100_NAMEREAD_INI		;MLD100/* �d���������P�O�O�^���́������f�[�^�Ǎ����� 	*/
//	CALL	ADC_NEXTNAME_SET		;/* �`�c�b���^�ԍ����� 			*/
//;
//;
//SV_EEPROM_CHK_END:
//;
//	POP	ES				;
//	POP	DS				;
//	RET					;
//;
//SV_EEPROM_CHK	ENDP
//;

#endif

