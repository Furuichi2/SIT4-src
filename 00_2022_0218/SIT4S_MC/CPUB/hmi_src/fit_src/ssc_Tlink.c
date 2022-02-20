/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�s�����N�ʐM����														*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FShima		ON:2004-05-28			V01j
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
/* �萔��` ---------------------------------------------------------- */
/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	Tlink1_mng(void);						//Tlink�ʐM����
void	Tlink_SV_tx(void);
void	Tlink_PV_rx(void);
void	Tlink_SVtx_PVrx(void);
void	PVmove_BK1_BL1(void);
void	SVmove_BK1_BL1(void);
void	SVmove_BK10_BL1(void);
void	SVmove_BK10_BL2(void);
void	SVmove_BK10_BL3(void);
void	SVmove_BK10_BL4(void);
void	SVmove_BK10_BL5(void);
void	SVmove_BK20_BL1(void);
void	Trink_error_sub(void);

/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Tlink1_mng
*  Function Name:	Tlink�ʐM����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-28
********************************************************************************
*/
void	Tlink1_mng(void)
{
	UNs	w1;

	if ( (SEQ_020_SV & BIT_12) == 0)		return;				//V05l-a 2009/03/24

//	2009
//	SEQ_PAR_427_CHG = SEQ_PAR_427_BAK ^ SEQ_PAR_427;			// �ω�
//	SEQ_PAR_427_ONE = SEQ_PAR_427_CHG & SEQ_PAR_427;			// ON����
//	SEQ_PAR_427_OFE = SEQ_PAR_427_CHG & SEQ_PAR_427_BAK;		// OFF����
//	SEQ_PAR_427_BAK = SEQ_PAR_427;

	w1=SEQ_PAR_427;
	SEQ_PAR_427_CHG = SEQ_PAR_427_BAK ^ w1;			// �ω�
	SEQ_PAR_427_ONE = SEQ_PAR_427_CHG & w1;			// ON����
	SEQ_PAR_427_OFE = SEQ_PAR_427_CHG & SEQ_PAR_427_BAK;		// OFF����
	SEQ_PAR_427_BAK = w1;

	if (SEQ_PAR_427_ONE) {
		if (SEQ_PAR_427_ONE & BIT_0) {
			Tlink_SV_tx();							// PLC����v���̂�������ݸ�^��ۯ��𑗐M����B
			SEQ_PAR_497 |= BIT_0;					// ���M����ON!
		}
		if (SEQ_PAR_427_ONE & BIT_1) {
			Tlink_PV_rx();							// PLC����v���̂�������ݸ�^��ۯ�����M���i�[����B
			SEQ_PAR_497 |= BIT_1;					// ��M����ON!
		}
		if (SEQ_PAR_427_ONE & BIT_2) {
			Tlink_SVtx_PVrx();						// PLC����v���̂�������ݸ�^��ۯ��𑗐M����B
													// PLC����v���̂�������ݸ�^��ۯ�����M���i�[����B
			SEQ_PAR_497 |= BIT_2;					// ����M����ON!
		}
	}

	if (SEQ_PAR_427_OFE) {
		if (SEQ_PAR_427_OFE & BIT_0) {				// ���M�v��OFF�����H
			SEQ_PAR_497 &= ~BIT_0;					// ���M����OFF!
		}
		if (SEQ_PAR_427_OFE & BIT_1) {				// ��M�v��OFF�����H
			SEQ_PAR_497 &= ~BIT_1;					// ��M����OFF!
		}
		if (SEQ_PAR_427_OFE & BIT_2) {				// ����M�v��OFF�����H
			SEQ_PAR_497 &= ~BIT_2;					// ����M����OFF!
		}
	}

}


/*
********************************************************************************
*  Module Name:		Tlink_SV_tx
*  Function Name:	PLC����v���̂�������ݸ�^��ۯ��𑗐M����B
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_SV_tx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ��ݸNo.�^��ۯ�No.�ԐM

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ��ݸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ��ۯ�No.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** ���M��ݸ1�^��ۯ�1���� ****/
					SVmove_BK1_BL1();
					break;

				default:
					break;
			}
			break;

		case 10:
			switch (bl1) {
				case 1:
					/**** ���M��ݸ10�^��ۯ�1���� ****/
					SVmove_BK10_BL1();
					break;

				case 2:
					/**** ���M��ݸ10�^��ۯ�2���� ****/
					SVmove_BK10_BL2();
					break;

				case 3:
					/**** ���M��ݸ10�^��ۯ�3���� ****/
					SVmove_BK10_BL3();
					break;

				case 4:
					/**** ���M��ݸ10�^��ۯ�4���� ****/
					SVmove_BK10_BL4();
					break;

				case 5:
					/**** ���M��ݸ10�^��ۯ�5���� ****/
					SVmove_BK10_BL5();
					break;

				default:
					break;
			}
			break;

		case 20:
			switch (bl1) {
				case 1:
					/**** ���M��ݸ20�^��ۯ�1���� ****/
					SVmove_BK20_BL1();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

}




/*
********************************************************************************
*  Module Name:		Tlink_PV_rx
*  Function Name:	PLC����v���̂�������ݸ�^��ۯ�����M���i�[����B
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_PV_rx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ��ݸNo.�^��ۯ�No.�ԐM

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ��ݸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ��ۯ�No.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** ��M��ݸ1�^��ۯ�1���� ****/
					PVmove_BK1_BL1();
					break;

				default:
					Trink_error_sub();
					break;
			}
			break;

		default:
			Trink_error_sub();
			break;
	}

}


/*
********************************************************************************
*  Module Name:		OPdata_set_kaku
*  Function Name:	PLC����v���̂�������ݸ�^��ۯ��𑗐M����B
					PLC����v���̂�������ݸ�^��ۯ�����M���i�[����B
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_SVtx_PVrx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ��ݸNo.�^��ۯ�No.�ԐM

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ��ݸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ��ۯ�No.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** ���M��ݸ1�^��ۯ�1���� ****/
					SVmove_BK1_BL1();
					/**** ��M��ݸ1�^��ۯ�1���� ****/
					PVmove_BK1_BL1();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

}




/*
***********************************************************************
*
*  Module Name:		PVmove_BK1_BL1
*  Function Name:	�����l��M�o���N�P�E�u���b�N�P
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	PVmove_BK1_BL1(void) {

		UNl	d1,d2;

		PV_BARANS_C27 = SEQ_PAR_412;		/* �o�����T�� �@�Q�o�C�g*/
		PV_DAITY1_C27 = SEQ_PAR_413;		/* �_�C�N�b�V�������͍� �@�Q�o�C�g*/
		PV_DAITY2_C27 = SEQ_PAR_414;		/* �_�C�N�b�V�������͉E �@�Q�o�C�g*/

		d1 = ((UNl)SEQ_PAR_416<<16) & 0xffff0000;
		d2 = (UNl)SEQ_PAR_415 & 0x0000ffff;
		PV_DAIKA1_C27 = d1 | d2;			/* �_�C�N�b�V�������ߍ��@�S�o�C�g */

		d1 = ((UNl)SEQ_PAR_418<<16) & 0xffff0000;
		d2 = (UNl)SEQ_PAR_417 & 0x0000ffff;
		PV_DAIKA2_C27 = d1 | d2;			/* �_�C�N�b�V�������߉E�@�S�o�C�g*/

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK1_BL1
*  Function Name:	�ݒ�l���M�o���N�P�E�u���b�N�P
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK1_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_482 = SV_BARANS_C27;		/* �o�����T�� �@�Q�o�C�g*/
		SEQ_PAR_483 = SV_DAITY1_C27;		/* �_�C�N�b�V�������͍� �@�Q�o�C�g*/
		SEQ_PAR_484 = SV_DAITY2_C27;		/* �_�C�N�b�V�������͉E �@�Q�o�C�g*/

		SEQ_PAR_485 = (UNs)(SV_DAIKA1_C27 & 0x0000ffff);
		SEQ_PAR_486 = (UNs)((SV_DAIKA1_C27>>16) & 0x0000ffff);		/* �_�C�N�b�V�������ߍ��@�S�o�C�g */

		SEQ_PAR_487 = (UNs)(SV_DAIKA2_C27 & 0x0000ffff);
		SEQ_PAR_488 = (UNs)((SV_DAIKA2_C27>>16) & 0x0000ffff);		/* �_�C�N�b�V�������߉E�@�S�o�C�g*/

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL1
*  Function Name:	�ݒ�l���M�o���N�P�O�E�u���b�N�P
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_MLDNO2_F1[0];		/* �^���� */
		SEQ_PAR_482 = PV_MLDNO2_F1[1];		/* �^���� */
		SEQ_PAR_483 = PV_MLDNO2_F1[2];		/* �^���� */
		SEQ_PAR_484 = PV_MLDNO2_F1[3];		/* �^���� */
		SEQ_PAR_485 = PV_MLDNO2_F1[4];		/* �^���� */
		SEQ_PAR_486 = PV_MLDNO2_F1[5];		/* �^���� */
		SEQ_PAR_487 = PV_MLDNO2_F1[6];		/* �^���� */
		SEQ_PAR_488 = 0;					/* �_�~�[ */
		SEQ_PAR_489 = PV_MLDNO3_F1[0];		/* ���� */
		SEQ_PAR_490 = PV_MLDNO3_F1[1];		/* ���� */
		SEQ_PAR_491 = PV_MLDNO3_F1[2];		/* ���� */
		SEQ_PAR_492 = PV_MLDNO3_F1[3];		/* ���� */
		SEQ_PAR_493 = PV_MLDNO3_F1[4];		/* ���� */
		SEQ_PAR_494 = PV_MLDNO3_F1[5];		/* ���� */
		SEQ_PAR_495 = PV_MLDNO3_F1[6];		/* ���� */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL2
*  Function Name:	�ݒ�l���M�o���N�P�O�E�u���b�N�Q
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL2(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_SPDSET_B11;							/* �v���X���x�@�ݒ�l */
		SEQ_PAR_482 = PV_TLINKSMP_DAT;							/* �v���X���x�@�����l */
		SEQ_PAR_483 = (UNs)(PV_TOTLC1_B3 & 0x0000ffff);			/* �g�[�^���J�E���^�P�����l ���� */
		SEQ_PAR_484 = (UNs)((PV_TOTLC1_B3>>16) & 0x0000ffff);	/* �g�[�^���J�E���^�P�����l ��� */
		SEQ_PAR_485 = (UNs)(SV_PUR1SV_B4 & 0x0000ffff);			/* ���b�g�J�E���^�P�@�ݒ�l ���� */
		SEQ_PAR_486 = (UNs)((SV_PUR1SV_B4>>16) & 0x0000ffff);	/* ���b�g�J�E���^�P�@�ݒ�l ��� */
		SEQ_PAR_487 = (UNs)(PV_LOTCT1_B4 & 0x0000ffff);			/* ���b�g�J�E���^�P�@�����l ���� */
		SEQ_PAR_488 = (UNs)((PV_LOTCT1_B4>>16) & 0x0000ffff);	/* ���b�g�J�E���^�P�@�����l ��� */
		SEQ_PAR_489 = (UNs)(SV_PUR2SV_B41 & 0x0000ffff);		/* ���b�g�J�E���^�Q�@�ݒ�l ���� */
		SEQ_PAR_490 = (UNs)((SV_PUR2SV_B41>>16) & 0x0000ffff);	/* ���b�g�J�E���^�Q�@�ݒ�l ��� */
		SEQ_PAR_491 = (UNs)(PV_LOTCT2_B41 & 0x0000ffff);		/* ���b�g�J�E���^�Q�@�����l ���� */
		SEQ_PAR_492 = (UNs)((PV_LOTCT2_B41>>16) & 0x0000ffff);	/* ���b�g�J�E���^�Q�@�����l ��� */
		SEQ_PAR_493 = PV_MLDNO1_F1;								/* �^�ԍ� */
		SEQ_PAR_494 = ENCO_DATA_HEX;							/* �p�x�f�[�^ */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL3
*  Function Name:	�ݒ�l���M�o���N�P�O�E�u���b�N�R
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL3(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = SV_OVERE1_A26;		/* �I�[�o�[���[�h�@�� */
		SEQ_PAR_482 = SV_OVERE2_A26;		/* �I�[�o�[���[�h�@���v */
		SEQ_PAR_483 = SV_OVERE3_A26;		/* �I�[�o�[���[�h�@�E */
		SEQ_PAR_484 = SV_ROALM1_A26;		/* ���A���~�b�g�@�� */
		SEQ_PAR_485 = SV_ROALM2_A26;		/* ���A���~�b�g�@���v */
		SEQ_PAR_486 = SV_ROALM3_A26;		/* ���A���~�b�g�@�E */
		SEQ_PAR_487 = PV_KAJYU1_A24;		/* �׏d�v�����@�� */
		SEQ_PAR_489 = PV_KAJYU2_A24;		/* �׏d�v�����@���v */
		SEQ_PAR_490 = PV_KAJYU3_A24;		/* �׏d�v�����@�E */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL4
*  Function Name:	�ݒ�l���M�o���N�P�O�E�u���b�N�S
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL4(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_LIFE_COUNT[1];							/* �ғ��� ���� */
		SEQ_PAR_482 = PV_LIFE_COUNT[0];							/* �ғ��� ��� */
		SEQ_PAR_483 = (UNs)(MCN_MENT_TIM1 & 0x0000ffff);		/* �ғ����� ���� */
		SEQ_PAR_484 = (UNs)((MCN_MENT_TIM1>>16) & 0x0000ffff);	/* �ғ����� ��� */
		SEQ_PAR_485 = (UNs)(MCN_MENT_CNT1 & 0x0000ffff);		/* �N���b�`�n�m�� ���� */
		SEQ_PAR_486 = (UNs)((MCN_MENT_CNT1>>16) & 0x0000ffff);	/* �N���b�`�n�m�� ��� */
		SEQ_PAR_487 = (UNs)(MCN_MENT_TIM2 & 0x0000ffff);		/* �N���b�`�n�m���� ���� */
		SEQ_PAR_488 = (UNs)((MCN_MENT_TIM2>>16) & 0x0000ffff);	/* �N���b�`�n�m���� ��� */
		SEQ_PAR_489 = (UNs)(MCN_MENT_CNT2 & 0x0000ffff);		/* �^�]�t�n�m�� ���� */
		SEQ_PAR_490 = (UNs)((MCN_MENT_CNT2>>16) & 0x0000ffff);	/* �^�]�t�n�m�� ��� */
		SEQ_PAR_491 = (UNs)(MCN_MENT_TIM3 & 0x0000ffff);		/* ���C�����[�^�n�m���� ���� */
		SEQ_PAR_492 = (UNs)((MCN_MENT_TIM3>>16) & 0x0000ffff);	/* ���C�����[�^�n�m���� ��� */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL5
*  Function Name:	�ݒ�l���M�o���N�P�O�E�u���b�N�T
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL5(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = (UNs)(MCN_MENT_CNT3 & 0x0000ffff);		/* �G�W�F�N�^�P�� ���� */
		SEQ_PAR_482 = (UNs)((MCN_MENT_CNT3>>16) & 0x0000ffff);	/* �G�W�F�N�^�P�� ��� */
		SEQ_PAR_483 = (UNs)(MCN_MENT_CNT6 & 0x0000ffff);		/* �������P�� ���� */
		SEQ_PAR_484 = (UNs)((MCN_MENT_CNT6>>16) & 0x0000ffff);	/* �������P�� ��� */
		SEQ_PAR_485 = (UNs)(MCN_MENT_CNT4 & 0x0000ffff);		/* �G�W�F�N�^�Q�� ���� */
		SEQ_PAR_486 = (UNs)((MCN_MENT_CNT4>>16) & 0x0000ffff);	/* �G�W�F�N�^�Q�� ��� */
		SEQ_PAR_487 = (UNs)(MCN_MENT_CNT7 & 0x0000ffff);		/* �������Q�� ���� */
		SEQ_PAR_488 = (UNs)((MCN_MENT_CNT7>>16) & 0x0000ffff);	/* �������Q�� ��� */
		SEQ_PAR_489 = (UNs)(MCN_MENT_CNT5 & 0x0000ffff);		/* �G�W�F�N�^�R�� ���� */
		SEQ_PAR_490 = (UNs)((MCN_MENT_CNT5>>16) & 0x0000ffff);	/* �G�W�F�N�^�R�� ��� */
		SEQ_PAR_491 = (UNs)(MCN_MENT_CNT8 & 0x0000ffff);		/* �������R�� ���� */
		SEQ_PAR_492 = (UNs)((MCN_MENT_CNT8>>16) & 0x0000ffff);	/* �������R�� ��� */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK20_BL1
*  Function Name:	�ݒ�l���M�o���N�Q�O�E�u���b�N�P
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK20_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = IROCK_NO[0];				/* �C���^�[���b�N�f�[�^�P */
		SEQ_PAR_482 = IROCK_NO[1];				/* �C���^�[���b�N�f�[�^�Q */
		SEQ_PAR_483 = IROCK_NO[2];				/* �C���^�[���b�N�f�[�^�R */
		SEQ_PAR_484 = IROCK_NO[3];				/* �C���^�[���b�N�f�[�^�S */
		SEQ_PAR_485 = IROCK_NO[4];				/* �C���^�[���b�N�f�[�^�T */
		SEQ_PAR_486 = IROCK_NO[5];				/* �C���^�[���b�N�f�[�^�U */
		SEQ_PAR_487 = IROCK_NO[6];				/* �C���^�[���b�N�f�[�^�V */

		SEQ_PAR_497 &= ~BIT_8;				// �ُ�r�b�gOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK20_BL1
*  Function Name:	�ݒ�l���M�o���N�Q�O�E�u���b�N�P
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-05-31
***********************************************************************
*/
void	Trink_error_sub(void) {
		SEQ_PAR_497 |= BIT_8;					// �ُ�r�b�gON!
}


/*** END ***/
