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
*		����(asm -> c)	�FFIT)�c�[		ON:2002-11-12
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

/* �O���Q�Ɗ֐���` -------------------------------------------------- */
/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		GMN_PAR009;						//�|�W�V���i�r�b�g��щ�		V01l_d

/* �萔��` ---------------------------------------------------------- */
#define		E_OPSTS_OK	0x55					//��߼�ݶ��ޗL��
#define		E_OPSTS_WDT	0x54					//��߼�ݶ��ޗL��(WDT-UP)
#define		E_OPSTS_NON	0x00					//��߼�ݶ��ނȂ�

#define		E_OPERR_CHK	0xff					//��߼�ݶ��� �װ ����

/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	OPDP_trans_chk(void);					//OP-DPRAM �� FRAM �ް��]�� & ��������

void	OPdata_set_kaku(void);					//��߼�� �ް��]������
void	OPdata_sys_kaku(void);					//��߼�݂ɼ���ׂ��i�[
void	OP_pvdata_smp(void);					//��߼�ݎ����l�ް������ݸޏ���
void	POSdata_set_kaku(void);					//�߼޼�Ű �ް��]������
void	OFF_set_start(void);					//�̾�Ē�������
void	OFF_set_start_mng(void);				//�̾�� ���ĕ\���Ǘ�
void	OPdata_offkan_smp(void);				//��߼�� �̾�Ċ������ް������ݸޏ���
void	KOUSEI_start(void);						//�Z������
void	KOUSEI_start_mng(void);					//�Z�����ĕ\���Ǘ�
void	OPdata_koukan_smp(void);				//��߼�ݍZ���������ް������ݸޏ���
void	AUTO_sura_seq_start(void);				//�ײ�ގ����������ݽ ����
void	AUTO_sura_start(void);					//�ײ�ގ�����������
void	SURA_auto_start_mng(void);				//�ײ�ގ����������ĕ\���Ǘ�
void	MAIN_op_seq(void);						//���ݽ���߼�݂֓]��
void	OPdata_bak_up(void);					//��߼�� �ޯ� ���ߏ���
void	SURA_select_mng(void);					//�ײ�ގ������ߑI��؂芷������
void	POJI_data_chk(void);					//�߼޼���ޯ����ߒl�Ď�

void	OPdata_bak(void);						//��߼�݂̌��ʒu�ް��Ԋ�

void	swap_ml(void *, UNl);					//���ٌ`�����ް����i�[(long)
void	swap_mw(void *, UNs);					//���ٌ`�����ް����i�[(word)
UNl		swap_il(void *);						//���ٌ`���̊i�[�ް����擾(long)
UNs		swap_iw(void *);						//���ٌ`���̊i�[�ް����擾(word)

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		OPDP_trans_chk
*  Function Name:	OP-DPRAM �� FRAM �ް��]�� & ��������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-01
********************************************************************************
*/
void	OPDP_trans_chk(void)
{

	if( OP_STATUS != E_OPSTS_NON ) {			//��߼�ݶ��ޗL��H		OP_STATUS �� E_OPSTS_NON(0) ����Ȃ���Ύn�߂͂n�o�������B

/**************** V05j *********************
		if( OP_STATUS == E_OPSTS_WDT ) {		//��߼�ݶ��ޗL��(WDT-UP)�H
			SEQ_PAR_079 |= BIT_10;				//��߼�� WDT�ُ�
		}
		if( OP_ERROR1 & E_OPERR_CHK ) {			//��߼�ݶ��� �װ�H
			SEQ_PAR_079 |= BIT_8;				//��߼�ُ݈�1(EPROM)
		}
		if( OP_ERROR2 & E_OPERR_CHK ) {			//��߼�ݶ��� �װ�H
			SEQ_PAR_079 |= BIT_9;				//��߼�ُ݈�1(RAM)
		}
*******************************************/
		if( OP_STATUS_REAL != E_OPSTS_OK ) {		//��߼�ݶ��ޗL��(WDT-UP)�H
			SEQ_PAR_079 |= BIT_10;					//��߼�� WDT�ُ�
		}
		if( OP_ERROR1 & E_OPERR_CHK ) {				//��߼�ݶ��� �װ�H
			SEQ_PAR_079 |= BIT_8;					//��߼�ُ݈�1(EPROM)
		}
		if( OP_ERROR2 & E_OPERR_CHK ) {				//��߼�ݶ��� �װ�H
			SEQ_PAR_079 |= BIT_9;					//��߼�ُ݈�1(RAM)
		}


//		if( OP_STATUS == E_OPSTS_WDT ) {		//��߼�ݶ��ޗL��(WDT-UP)�H
//			SEQ_PAR_079 |= BIT_10;				//��߼�� WDT�ُ�
//		}else{
//			SEQ_PAR_079 &= ~BIT_10;				//��߼�� WDT�ُ�
//		}
//		if( OP_ERROR1 & E_OPERR_CHK ) {			//��߼�ݶ��� �װ�H
//			SEQ_PAR_079 |= BIT_8;				//��߼�ُ݈�1(EPROM)
//		}else{
//			SEQ_PAR_079 &= ~BIT_8;				//��߼�ُ݈�1(EPROM)
//		}
//		if( OP_ERROR2 & E_OPERR_CHK ) {			//��߼�ݶ��� �װ�H
//			SEQ_PAR_079 |= BIT_9;				//��߼�ُ݈�1(RAM)
//		}else{
//			SEQ_PAR_079 &= ~BIT_9;				//��߼�ُ݈�1(RAM)
//		}

	}

	OPdata_set_kaku();							//�I�v�V�����[�f�[�^�]������
	POSdata_set_kaku();							//�|�W�V���i�[�f�[�^�]������

	OFF_set_start_mng();						//�̾�� ���ĕ\���Ǘ�
	KOUSEI_start_mng();							//�Z�����ĕ\���Ǘ�
	SURA_auto_start_mng();						//�ײ�ގ����������ĕ\���Ǘ�

	MAIN_op_seq();								//���ݽ���߼�݂֓]��

	AUTO_sura_seq_start();						//�ײ�ގ����������ݽ ����
	SURA_sv_chg();								//�ײ�ގ������߂r�u�ύX����

	OPdata_bak_up();							//��߼�� �ޯ� ���ߏ���

	SURA_select_mng();							//�ײ�ގ������ߑI��؂芷������
	POJI_data_chk();							//�߼޼���ޯ����ߒl�Ď�

}


/*
********************************************************************************
*  Module Name:		OPdata_set_kaku
*  Function Name:	��߼�� �ް��]������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OPdata_set_kaku(void)
{

	if( 00 == (CSTATUS_C & 0x06) ) {					//�]���n�j�H (OP���ސݒ�l�]���ð���Ǎ�)
		if( SVSW_CHG_FLG & BIT_4 ) {					//�I�v�V�����f�[�^�`�F���W�t���O�Z�b�g
			SVSW_CHG_FLG &= ~BIT_4;						//�v���׸� �ر

			swap_ml(&CPOS_SET_POSI, SV_ATUOSU_D9);		//�X���C�h���������ݒ�l(2word)

//Sit-S �����_���͂Ȃ�
//	MOV	AL,SEQ_016_SV			;
//	AND	AL,BIT_6			;
//	SHR	AL,6				;
//	MOV	BL,SV_POINT_A1			;
//	DEC	BL				;
//	AND	BL,BIT_0			;
//	SHL	BL,1				;
//	OR	AL,BL				;
//	MOV	ES:CPOS_SET_UNIT,AL		;/* �P�ʁ������_�ʒu */
			CPOS_SET_UNIT = 0;							//�P�ʁ������_�ʒu(��а)

			swap_mw(&CLO_STRAIN_L, SV_MAXHIZ_A24);		//�ő�c�@�i���j(1word)
			swap_mw(&CLO_STRAIN_R, SV_MAXHI3_A24);		//�ő�c�@�i�E�j(1word)

			swap_mw(&CLO_MAXLD_L, SV_MAXKAJ_A24);		//�ő�׏d�i���j(1word)
			swap_mw(&CLO_MAXLD_T, SV_MAXKA2_A24);		//�ő�׏d�i�S�j(1word)
			swap_mw(&CLO_MAXLD_R, SV_MAXKA3_A24);		//�ő�׏d�i�E�j(1word)

			swap_mw(&CLO_PROOF_L, SV_KOUKAJ_A24);		//�Z���׏d�i���j(1word)
			swap_mw(&CLO_PROOF_T, SV_KOUKA2_A24);		//�Z���׏d�i�S�j(1word)
			swap_mw(&CLO_PROOF_R, SV_KOUKA3_A24);		//�Z���׏d�i�E�j(1word)

			CLO_PROOF_SEI = SV_KOUSEI_A24;				//�Z�����x(1byte)

			swap_mw(&CLO_OVER_L, SV_OVERE1_A26);		//���ް۰�ށi���j(1word)
			swap_mw(&CLO_OVER_T, SV_OVERE2_A26);		//���ް۰�ށi�S�j(1word)
			swap_mw(&CLO_OVER_R, SV_OVERE3_A26);		//���ް۰�ށi�E�j(1word)

			swap_mw(&CLO_LOWER_L, SV_ROALM1_A26);		//۱��Я�  �i���j(1word)
			swap_mw(&CLO_LOWER_T, SV_ROALM2_A26);		//۱��Я�  �i�S�j(1word)
			swap_mw(&CLO_LOWER_R, SV_ROALM3_A26);		//۱��Я�  �i�E�j(1word)

			OPdata_sys_kaku();							//��߼�݂ɼ���ׂ��i�[

			CSTATUS_C |= 0x06;							//�f�[�^�i�[�t���O�Z�b�g
		}
	}

	OP_pvdata_smp();									//��߼�ݎ����l�ް������ݸޏ���

}


/*
********************************************************************************
*  Module Name:		OPdata_sys_kaku
*  Function Name:	��߼�݂ɼ���ׂ��i�[
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OPdata_sys_kaku(void)
{
	UNs	i;

	V25_OP_0 = SV_APARAD_A24;			//�Œ�\���׏d (1byte)

	i = (SEQ_020_SV & 0x01e0);
	i >>= 1;
	V25_OP_1 = i;						//(1byte)

	V25_OP_4 = (UNb)GMN_PAR009;			// �|�W�V���i�r�b�g��щ�		V01l_d



//	MOV	AX,SEQ_ROM			;V01c/* �X���C�h�p�x���G���R�[�_�r�b�g��щ񐔂̂q�n�l�p�����]�� */
//	MOV	ES,AX				;V01c
//	MOV	SI,SYS_OPBIT_B1			;V01c
//	MOV	BL,ES:[SI]			;V01c
//	MOV	SI,SYS_OPSUR_B1			;V01c
//	MOV	AX,ES:[SI]			;V01c
//	MOV	DX,OP_AREA			;V01c
//	MOV	ES,DX				;V01c
//	MOV	ES:V25_OP_2,AL			;V01c
//	MOV	ES:V25_OP_3,AH			;V01c
//	MOV	ES:V25_OP_4,BL			;V01c

//	MOV	AX,SEQ_ROM			;V07/* �X���C�h�������߁@�ُ팟�m�V�X�p�� */
//	MOV	ES,AX				;V07
//	MOV	SI,SYS_OP_SU_TIME		;V07
//	MOV	AX,ES:[SI]			;V07
//	MOV	SI,SYS_OP_SU_POS		;V07
//	MOV	BX,ES:[SI]			;V07
//	MOV	SI,SYS_OP_SU_POS1		;V07
//	MOV	CX,ES:[SI]			;V07
//	MOV	DX,OP_AREA			;V07
//	MOV	ES,DX				;V07
//	MOV	ES:V25_OP_10,AX			;V07
//	MOV	ES:V25_OP_11,BX			;V07
//	MOV	ES:V25_OP_12,CX			;V07

}


/*
********************************************************************************
*  Module Name:		OP_pvdata_smp
*  Function Name:	��߼�ݎ����l�ް������ݸޏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-01
********************************************************************************
*/
void	OP_pvdata_smp(void)
{

//	if( OP_STATUS_DT == 0x55 ) {					//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {					//��߼�ݶ��ޗL��?

		PV_LAMPDT_A23 = swap_iw(&CLO_OFAD_L);		//�I�t�Z�b�g������(1word)
		PV_RAMPDT_A23 = swap_iw(&CLO_OFAD_R);		//�I�t�Z�b�g�����E(1word)
		PV_AMPDAT_A23 = swap_iw(&CLO_OFAD_T);		//�I�t�Z�b�g�������v(1word)

//2011-01-18 koma		PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_L);		//�׏d�iTON�j(1word)
//2011-01-18 koma		PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_T);		//�׏d�iTON�j(1word)
//2011-01-18 koma		PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_R);		//�׏d�iTON�j(1word)
//	���ݽ�ɂ��\�����e��؂�ւ���
		if( SEQ_PAR_113 & BIT_8 ) {
			PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_KEEP_L);	//�׏d�iTON�j(1word)
			PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_KEEP_T);	//�׏d�iTON�j(1word)
			PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_KEEP_R);	//�׏d�iTON�j(1word)
		}
		else {
			PV_KAJYU1_A24 = swap_iw(&CLO_LOAD_L);		//�׏d�iTON�j(1word)
			PV_KAJYU2_A24 = swap_iw(&CLO_LOAD_T);		//�׏d�iTON�j(1word)
			PV_KAJYU3_A24 = swap_iw(&CLO_LOAD_R);		//�׏d�iTON�j(1word)
		}


		PV_DAIHAI_B5 = swap_il(&CPOS_NOW_MM);		//�޲ʲ�(2word)

/**************** V05j *********************
		if( PVGENNITI_FLG != 0xff ) {				//�ޯ����߉�ʂɂČ��ʒu�f�[�^��ύX���Ă���h�m�F�h��������閘�����ݸނ��Ȃ�
			PV_GENITI_B2 = swap_il(&CPOS_STD);		//���ʒu(2word)
		}
*******************************************/
	}

	if( SEQ_021_SV & BIT_2 ) {						//�ײ�ގ��������ӂ̎��͐ݒ�l��}��
		PV_DAIHAI_B5 = SV_ATUOS0_D9;				//�޲ʲ�(2word)
	}

}


/*
********************************************************************************
*  Module Name:		POSdata_set_kaku
*  Function Name:	�߼޼�Ű �ް��]������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	POSdata_set_kaku(void)
{

	if( 00 == (CSTATUS_C & BIT_0) ) {				//�]���n�j�H (OP���ސݒ�l�]���ð���Ǎ�)
		if( SVSW_CHG_FLG & BIT_6 ) {				//�߼޼�Ű �ް� ��ݼ��׸޾�āH
			SVSW_CHG_FLG &= ~BIT_6;					//�v���׸� �ر

//Sit-S�Ȃ�	%MOV_OP_2W(SV_KANDO_A21,CPOS_SET_MRE)	;/* ���x */
//Sit-S�Ȃ�	%MOV_OP_2W(SV_UPDATA_A21,CPOS_SET_TOPL)	;/* ��� */
//Sit-S�Ȃ�	%MOV_OP_2W(SV_DNDATA_A21,CPOS_SET_LOWL)	;/* ���� */
//Sit-S�Ȃ�	%MOV_OP_2W(SV_GENITI_A21,CPOS_SET_STD)	;/* ���ʒu */


			swap_ml(&CPOS_SET_MRE, SV_KANDO_A21);		//���x		V01j
			swap_ml(&CPOS_SET_TOPL, SV_UPDATA_A21);		//���		V01j
			swap_ml(&CPOS_SET_LOWL, SV_DNDATA_A21);		//����		V01j
			swap_ml(&CPOS_SET_STD, SV_GENITI_A21);		//���ʒu	V01j


			CPOS_SET_DELTA = SV_MODORI_A21;			//�߂��(1byte)
			CPOS_SET_ALFA = SV_DNSTOP_A21;			//���~��~(1byte)
			CPOS_SET_BETA = SV_UPSTOP_A21;			//�㏸��~(1byte)
			CPOS_SET_GANMA = SV_SSEIDO_A21;			//���䐸�x(1byte)

			CSTATUS_C |= BIT_0;						//�f�[�^�i�[�t���O�Z�b�g

			PODATA_SET_FLG = 0;
		}
	}
}


/*
********************************************************************************
*  Module Name:		OFF_set_start
*  Function Name:	�̾�Ē�������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
void	OFF_set_start(void)
{

	SEQ_PAR_451 |= BIT_0;				//�׏d�v �̾�Ē�������(1:����)
	OFF_SET_MNG_LAST = 0;				//V05j

}


/*
********************************************************************************
*  Module Name:		OFF_set_start_mng
*  Function Name:	�̾�� ���ĕ\���Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OFF_set_start_mng(void)
{
	UNs	bf1, bf2;

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//��߼�ݶ��ޗL��?			V05j
		return;
	}

/**************** V05j *********************
	bf1 = (SEQ_PAR_385 & BIT_0);			//�̾�ďI��(1:�������́A�ُ�)
	bf2 = OFF_SET_MNG_LAST;
	OFF_SET_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){							//�I�t�Z�b�g�����I���H
		SEQ_PAR_451 &= ~BIT_0;				//�׏d�v �̾�Ē�������(1:����)
		OPdata_offkan_smp();				//��߼�� �̾�Ċ������ް������ݸޏ���
	}
*******************************************/

	bf1 = (SEQ_PAR_382 & BIT_1);			//�̾�Ē����\���ް��쐬
	bf1 >>= 1;
	PV_OFFSET_A1 = bf1;
}


/*
********************************************************************************
*  Module Name:		OPdata_offkan_smp
*  Function Name:	��߼�� �̾�Ċ������ް������ݸޏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OPdata_offkan_smp(void)
{
//	if( OP_STATUS_DT == 0x55 ) {						//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {						//��߼�ݶ��ޗL��?

		PV_OF_BAKL = CLO_OF_SETL;						//�I�t�Z�b�g�l��(1byte)
		PV_OF_BAKR = CLO_OF_SETR;						//�I�t�Z�b�g�l�E(1byte)

		PV_OF_AVE_BAKL = swap_iw(&CLO_OF_AVE_SETL);		//�I�t�Z�b�g�␳��(1word)
		PV_OF_AVE_BAKR = swap_iw(&CLO_OF_AVE_SETR);		//�I�t�Z�b�g�␳�E(1word)
		PV_OF_AVE_BAKT = swap_iw(&CLO_OF_AVE_SETT);		//�I�t�Z�b�g�␳���v(1word)

/**************** V05j *********************
		KJ_CHK_CNT4++;						//V05i

		PV_OF_BAKL_X = CLO_OF_SETL;						//�I�t�Z�b�g�l��(1byte)		V05i
		PV_OF_BAKR_X = CLO_OF_SETR;						//�I�t�Z�b�g�l�E(1byte)		V05i

		PV_OF_AVE_BAKL_X = swap_iw(&CLO_OF_AVE_SETL);	//�I�t�Z�b�g�␳��(1word)	V05i
		PV_OF_AVE_BAKR_X = swap_iw(&CLO_OF_AVE_SETR);	//�I�t�Z�b�g�␳�E(1word)	V05i
		PV_OF_AVE_BAKT_X = swap_iw(&CLO_OF_AVE_SETT);	//�I�t�Z�b�g�␳���v(1word)	V05i
*******************************************/
	}
}


/*
********************************************************************************
*  Module Name:		KOUSEI_start
*  Function Name:	�Z������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
void	KOUSEI_start(void)
{

	SEQ_PAR_451 |= BIT_1;				//�׏d�v �׏d�Z������(1:����)
	KOUSEI_MNG_LAST = 0;				//V05j

}


/*
********************************************************************************
*  Module Name:		KOUSEI_start_mng
*  Function Name:	�Z�����ĕ\���Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	KOUSEI_start_mng(void)
{
	UNs	bf1, bf2;

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//��߼�ݶ��ޗL��?			V05j
		return;
	}

/**************** V05j *********************
	bf1 = (SEQ_PAR_385 & BIT_1);			//�׏d�Z���I��(1:�������́A�ُ�)
	bf2 = KOUSEI_MNG_LAST;
	KOUSEI_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_451 &= ~BIT_1;				//�׏d�v �׏d�Z������(1:����)
		OPdata_koukan_smp();				//��߼�ݍZ���������ް������ݸޏ���
	}
*******************************************/

	bf1 = (SEQ_PAR_382 & BIT_3);			//�׏d�v �׏d�Z������
	bf1 >>= 2;
	PV_KAJYUU_A1 = bf1;
}


/*
********************************************************************************
*  Module Name:		OPdata_koukan_smp
*  Function Name:	��߼�ݍZ���������ް������ݸޏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OPdata_koukan_smp(void)
{
//	if( OP_STATUS_DT == 0x55 ) {						//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK ) {						//��߼�ݶ��ޗL��?

		PV_GAIN_BAK1L = swap_iw(&CLO_GAIN_SET1L);		//�ő�c�݂Q�O�O�O���Q�C��(1word)
		PV_GAIN_BAK1R = swap_iw(&CLO_GAIN_SET1R);		//�ő�c�݂Q�O�O�O�E�Q�C��(1word)

		PV_GAIN_BAK2L = swap_iw(&CLO_GAIN_SET2L);		//�ő�c�݂P�T�O�O���Q�C��(1word)
		PV_GAIN_BAK2R = swap_iw(&CLO_GAIN_SET2R);		//�ő�c�݂P�T�O�O�E�Q�C��(1word)

		PV_GAIN_BAK3L = swap_iw(&CLO_GAIN_SET3L);		//�ő�c�݁@�W�O�O���Q�C��(1word)
		PV_GAIN_BAK3R = swap_iw(&CLO_GAIN_SET3R);		//�ő�c�݁@�W�O�O�E�Q�C��(1word)

		PV_GAIN_BAK4L = swap_iw(&CLO_GAIN_SET4L);		//�ő�c�݁@�S�O�O���Q�C��(1word)
		PV_GAIN_BAK4R = swap_iw(&CLO_GAIN_SET4R);		//�ő�c�݁@�S�O�O�E�Q�C��(1word)

		PV_GAIN_BAK5L = swap_iw(&CLO_GAIN_SET5L);		//�ő�c�݁@�Q�O�O���Q�C��(1word)
		PV_GAIN_BAK5R = swap_iw(&CLO_GAIN_SET5R);		//�ő�c�݁@�Q�O�O�E�Q�C��(1word)

/**************** V05j *********************
		KJ_CHK_CNT5++;						//V05i

		PV_GAIN_BAK1L_X = swap_iw(&CLO_GAIN_SET1L);		//�ő�c�݂Q�O�O�O���Q�C��(1word)	V05i
		PV_GAIN_BAK1R_X = swap_iw(&CLO_GAIN_SET1R);		//�ő�c�݂Q�O�O�O�E�Q�C��(1word)	V05i

		PV_GAIN_BAK2L_X = swap_iw(&CLO_GAIN_SET2L);		//�ő�c�݂P�T�O�O���Q�C��(1word)	V05i
		PV_GAIN_BAK2R_X = swap_iw(&CLO_GAIN_SET2R);		//�ő�c�݂P�T�O�O�E�Q�C��(1word)	V05i

		PV_GAIN_BAK3L_X = swap_iw(&CLO_GAIN_SET3L);		//�ő�c�݁@�W�O�O���Q�C��(1word)	V05i
		PV_GAIN_BAK3R_X = swap_iw(&CLO_GAIN_SET3R);		//�ő�c�݁@�W�O�O�E�Q�C��(1word)	V05i

		PV_GAIN_BAK4L_X = swap_iw(&CLO_GAIN_SET4L);		//�ő�c�݁@�S�O�O���Q�C��(1word)	V05i
		PV_GAIN_BAK4R_X = swap_iw(&CLO_GAIN_SET4R);		//�ő�c�݁@�S�O�O�E�Q�C��(1word)	V05i

		PV_GAIN_BAK5L_X = swap_iw(&CLO_GAIN_SET5L);		//�ő�c�݁@�Q�O�O���Q�C��(1word)	V05i
		PV_GAIN_BAK5R_X = swap_iw(&CLO_GAIN_SET5R);		//�ő�c�݁@�Q�O�O�E�Q�C��(1word)	V05i
*******************************************/

	}
}


/*
********************************************************************************
*  Module Name:		AUTO_sura_seq_start
*  Function Name:	�ײ�ގ����������ݽ ����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	AUTO_sura_seq_start(void)
{
	UNs	i, j;

	i = (SEQ_PAR_109 & BIT_6);		//�ײ�ގ������� ����(1:����) 0 �� 1�@�H
	j = AUTO_SEQ_LST;
	AUTO_SEQ_LST = i;
	j ^= i;
	if( i & j ){
		AUTO_sura_start();			//�ײ�ގ�����������
	}

}


/*
********************************************************************************
*  Module Name:		AUTO_sura_start
*  Function Name:	�ײ�ގ�����������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-23
********************************************************************************
*/
void	AUTO_sura_start(void)
{

	if(00 == (SEQ_PAR_109 & BIT_7)) {			//�ײ�ގ������� ��~(1:��~)
		if(00 == (SEQ_PAR_385 & BIT_2)){		//�ʒu���ߏI���̐M�����n�m�̎��͍ăX�^�[�g���Ȃ�
			if(00 == (SEQ_021_SV & BIT_2)){		//�ײ�ގ������߃����@�\�L��̏ꍇ�̓X�^�[�g�����Ȃ�
				SEQ_PAR_450 |= BIT_1;			//�ײ�ގ������� ����(1:����)
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SURA_auto_start_mng
*  Function Name:	�ײ�ގ����������ĕ\���Ǘ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	SURA_auto_start_mng(void)
{
	UNs	bf1, bf2;

	bf1 = (SEQ_PAR_385 & BIT_2);			//�ʒu���ߏI��(1:�������́A�ُ�)
	bf2 = SURA_AUTO_MNG_LAST;
	SURA_AUTO_MNG_LAST = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_450 &= ~BIT_1;				//�ײ�ގ������� ����(1:����)
	}

/*************	�X���C�h�������ߒ��~�M�������オ��H     ************/
	bf1 = (SEQ_PAR_109 & BIT_7);			//�ײ�ގ������� ��~�H
	bf2 = SURA_AUTO_MNG_LAST1;
	SURA_AUTO_MNG_LAST1 = bf1;
	bf2 ^= bf1;

	if(bf2 & bf1){
		SEQ_PAR_450 &= ~BIT_1;				//�ײ�ގ������� ����(1:����)
	}
}


/*
********************************************************************************
*  Module Name:		MAIN_op_seq
*  Function Name:	���ݽ���߼�݂֓]��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	MAIN_op_seq(void)
{
	UNs	i, j;

	i = (SEQ_020_SV >> 5);				//�׏d�v۱��ЯČ��o
	j = (SEQ_020_SV >> 7);				//�׏d�v���ް۰�ތ��o
	i &= BIT_4;
	j &= BIT_3;
	i |= j;
	i |= (SEQ_PAR_451 & 0x00e7);
	SEQ_PAR_451 = i;

	SEQ_PAR_452 = ((SEQ_PAR_109 >> 8) & 0x009f);

/***********	109.13-->450.2   109.14-->450.3	****************/
	i = (SEQ_PAR_109 & 0x6003);
	j = (i >> 11);
	j |= (i << 4);
	j |= (SEQ_PAR_450 & 0xffc3);
	SEQ_PAR_450 = j;

}


/*
********************************************************************************
*  Module Name:		OPdata_bak_up
*  Function Name:	��߼�� �ޯ� ���ߏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-05
********************************************************************************
*/
void	OPdata_bak_up(void)
{
	UNs	bf1, bf2;

/**************** V05j *********************
	bf1 = (SEQ_PAR_382 & 0x000a);
	bf2 = OPBAK_UP_LST;
	OPBAK_UP_LST = bf1;
	bf2 ^= bf1;
	if( 00 == (bf2 & bf1) ) {
		bf1 = OP_GENITI_READ;				//���ʒu�f�[�^�Ǎ������t���O�@�O�e�e�g������
		OP_GENITI_READ = 0;
		bf2 = OPBAK_UP_LST1;
		OPBAK_UP_LST1 = bf1;
		bf2 ^= bf1;
		if( 00 == (bf2 & bf1) ) {
			return;
		}
	}

//	if( OP_STATUS_DT == 0x55 )				//OPż:00H,OP��(OK):55H,OP��(WDTup):54H
	if( OP_STATUS == E_OPSTS_OK )			//��߼�ݶ��ޗL��?
	{										
											//�O�̂��߂ɍēx�T���v�����O���Ă���
		OPdata_koukan_smp();				//��߼�ݍZ���������ް������ݸޏ���
		OP_pvdata_smp();					//��߼�ݎ����l�ް������ݸޏ���
		OPdata_offkan_smp();				//��߼�� �̾�Ċ������ް������ݸޏ���

		FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
	}
*******************************************/

	if( (OP_STATUS != E_OPSTS_OK) ||
		(OP_STATUS_REAL != E_OPSTS_OK) )
	{											//��߼�ݶ��ޗL��?
		return;
	}

	/*** �I�t�Z�b�g�����I������ ***/
	bf1 = SEQ_PAR_382 & (BIT_1+BIT_2+BIT_5);			//�̾�ďI��(bit1:����I���Abit2,5:�ُ�I��)
	bf2 = OFF_SET_MNG_LAST;
	OFF_SET_MNG_LAST = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if(bf2)										//�I���ɕω������H
	{
		if ( SEQ_PAR_451 & BIT_0 )				//�I�t�Z�b�g�����X�^�[�g���Ă��H
		{
			if (bf2 & BIT_1)					//����I���H
			{
				OPdata_offkan_smp();			//��߼�� �̾�Ċ������ް������ݸޏ���
				FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
			}
		}
		SEQ_PAR_451 &= ~BIT_0;				//�׏d�v �̾�Ē�������(1:����)
	}

	/*** �׏d�Z���I������ ***/
	bf1 = SEQ_PAR_382 & (BIT_3+BIT_4);			//�Z���I��(bit3:����I���Abit4:�ُ�I��)
	bf2 = KOUSEI_MNG_LAST;
	KOUSEI_MNG_LAST = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if(bf2)										//�I���ɕω������H
	{
		if ( SEQ_PAR_451 & BIT_1 )				//�Z���X�^�[�g���Ă��H
		{
			if (bf2 & BIT_3)					//����I���H
			{
				OPdata_koukan_smp();			//��߼�ݍZ���������ް������ݸޏ���
				FRAM_csum_set();				//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
			}
		}
		SEQ_PAR_451 &= ~BIT_1;				//�׏d�v �׏d�Z������(1:����)
	}

	/*** �|�W�V���i���ʒu�f�[�^�o�^���� ***/
	bf1 = OP_GENITI_READ;					//���ʒu�f�[�^�Ǎ������t���O�@�O�e�e�g������
	OP_GENITI_READ = 0;
	bf2 = OPBAK_UP_LST1;
	OPBAK_UP_LST1 = bf1;
	bf2 ^= bf1;
	bf2 &= bf1;

	if( bf2 )								//�I���ɕω������H
	{
		if ( SEQ_PAR_450 & BIT_0 )			//���ʒu�o�^�X�^�[�g���Ă��H
		{
			if( 0xff == bf2 )				//����I���H
			{
				PV_GENITI_B2 = swap_il(&CPOS_STD);		//���ʒu(2word)
				FRAM_csum_set();						//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
			}
		}
		SEQ_PAR_450 &= ~BIT_0;				//���ʒu�o�^(1:�o�^)
	}
}


/*
********************************************************************************
*  Module Name:		SURA_select_mng
*  Function Name:	�ײ�ގ������ߑI��؂芷������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-07
********************************************************************************
*/
void	SURA_select_mng(void)
{
//sit-2��SEQ_PAR_168�ɑΉ������Asit-s�̗̈悪�Ȃ��̂ŁA�폜

//	UNs	bf1, bf2;
//
//	bf1 = (SEQ_PAR_168 & 0x0007);
//	bf2 = SURA_SEL_LST;
//	SURA_SEL_LST = bf1;
//
//	bf2 ^= bf1;
//	if(bf2 & bf1){
//		bf1 <<= 2;
//		SEQ_044_SV &= 0xffe3;
//		SEQ_044_SV |= bf1;
//
//		SVSW_CHG_FLG |= BIT_3;				//���ݽ(SEQ)�]���v��
//		FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
//
//		if(WINDOW_NO == 6){					//�i��@�ײ�ޒ���
//
//			DAN_select_diap();				//�i���� �I�����ڃZ���N�g�\��
//
//			Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
//			Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��
//		}
//	}
}


/*
********************************************************************************
*  Module Name:		POJI_data_chk
*  Function Name:	�߼޼���ޯ����ߒl�Ď�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-07
********************************************************************************
*/
void	POJI_data_chk(void)
{

	if( SEQ_020_SV & BIT_6 ) {					//�ײ�ގ�������(1�F�L)�H

		if( PV_GENITI_B2 != SV_GENITI_CHK ) {
			SEQ_PAR_078 |= BIT_6;				//�߼޼���ޯ����ߒl�ƍ��ُ�
		}
	}
}


/*
********************************************************************************
*  Module Name:		OPdata_bak
*  Function Name:	��߼�݂̌��ʒu�ް��Ԋ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
void	OPdata_bak(void)
{

	swap_ml(&CPOS_STD_BAK, PV_GENITI_B2);			//���ʒu(2word)

	swap_mw(&CLO_GAIN_BAK1L, PV_GAIN_BAK1L);		//(1word)
	swap_mw(&CLO_GAIN_BAK1R, PV_GAIN_BAK1R);		//(1word)
	swap_mw(&CLO_GAIN_BAK2L, PV_GAIN_BAK2L);		//(1word)
	swap_mw(&CLO_GAIN_BAK2R, PV_GAIN_BAK2R);		//(1word)
	swap_mw(&CLO_GAIN_BAK3L, PV_GAIN_BAK3L);		//(1word)
	swap_mw(&CLO_GAIN_BAK3R, PV_GAIN_BAK3R);		//(1word)
	swap_mw(&CLO_GAIN_BAK4L, PV_GAIN_BAK4L);		//(1word)
	swap_mw(&CLO_GAIN_BAK4R, PV_GAIN_BAK4R);		//(1word)
	swap_mw(&CLO_GAIN_BAK5L, PV_GAIN_BAK5L);		//(1word)
	swap_mw(&CLO_GAIN_BAK5R, PV_GAIN_BAK5R);		//(1word)

	CLO_OF_BAKL = PV_OF_BAKL;						//(1byte)
	CLO_OF_BAKR = PV_OF_BAKR;						//(1byte)

	swap_mw(&CLO_OF_AVE_BAKL, PV_OF_AVE_BAKL);		//(1word)
	swap_mw(&CLO_OF_AVE_BAKR, PV_OF_AVE_BAKR);		//(1word)
	swap_mw(&CLO_OF_AVE_BAKT, PV_OF_AVE_BAKT);		//(1word)

}


/*
********************************************************************************
*  Module Name:		swap_ml
*  Function Name:	���ٌ`�����ް����i�[(long)
*  Input	:		�]������ڽ[���ٌ`��]
*					�]�����ް�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
void	swap_ml(void *dst_p, UNl src_d)
{
	UNb	*wk_p;

	wk_p = dst_p;

	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p++ = (src_d & 0x000000ff);
	src_d >>= 8;
	*wk_p = (src_d & 0x000000ff);

}

/*
********************************************************************************
*  Module Name:		swap_mw
*  Function Name:	���ٌ`�����ް����i�[(word)
*  Input	:		�]������ڽ[���ٌ`��]
*					�]�����ް�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
void	swap_mw(void *dst_p, UNs src_d)
{
	UNb	*wk_p;

	wk_p = dst_p;

	*wk_p++ = (src_d & 0x00ff);
	src_d >>= 8;
	*wk_p = (src_d & 0x00ff);

}


/*
********************************************************************************
*  Module Name:		swap_il
*  Function Name:	���ٌ`���̊i�[�ް����擾(long)
*  Input	:		�]�������ڽ[���ٌ`��]
*  Return	: 		�擾�ް�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
UNl		swap_il(void *src_p)
{
	UNb	*wk_p;
	UNl	wk;

	wk_p = src_p;

	wk = *(wk_p+3);
	wk <<= 24;
	wk |= (*(wk_p+2) << 16);
	wk |= (*(wk_p+1) << 8);
	wk |= *wk_p;

	return(wk);
}


/*
********************************************************************************
*  Module Name:		swap_iw
*  Function Name:	���ٌ`���̊i�[�ް����擾(word)
*  Input	:		�]�������ڽ[���ٌ`��]
*  Return	: 		�擾�ް�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-11-12
********************************************************************************
*/
UNs		swap_iw(void *src_p)
{
	UNb	*wk_p;
	UNs	wk;

	wk_p = src_p;

	wk = *(wk_p+1);
	wk <<= 8;
	wk |= *wk_p;

	return(wk);
}


/*** END ***/
