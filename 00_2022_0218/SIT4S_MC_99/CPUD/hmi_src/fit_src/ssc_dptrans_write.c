/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�c�o�q�`�l �� �e�q�`�l	�f�[�^�]����������			*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned int

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_def.h"
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_wk_ext.h"

#define		BLK_SRV		0x0001						/* ����		��ۯ�		*/
#define		BLK_SYS		0x0002						/* �����	��ۯ�		*/
#define		BLK_MOT		0x0004						/* Ӱ���	��ۯ�		*/
#define		BLK_SEQ		0x0008						/* ���ݽ	��ۯ�		*/
#define		BLK_CAM		0x0020						/* ��		��ۯ�		*/
#define		BLK_GEN		0x0100						/* ���_		��ۯ�		*/

EXTRN	WORD	SVSW_CHG_FLG;						/* �����v���׸�			*/

EXTRN	void	DP_TRANS_SRV(void);					/* ����  ��ۯ��]������	*/
EXTRN	void	DP_TRANS_SYS(void);					/* ����� ��ۯ��]������	*/
EXTRN	void	DP_TRANS_MOT(void);					/* Ӱ��� ��ۯ��]������	*/
EXTRN	void	DP_TRANS_SEQ(void);					/* ���ݽ ��ۯ��]������	*/
EXTRN	void	DP_TRANS_CAM(void);					/* ��    ��ۯ��]������	*/
EXTRN	void	DP_TRANS_GEN(void);					/* ���_  ��ۯ��]������	*/
EXTRN	void	DP_GET_SENS	(void);					/* �Ʊ�ݻBACKUP�l �i�[	*/
EXTRN	void	DP_BACK_SENS(void);					/* �Ʊ�ݻBACKUP�l ����	*/

void	DPB_SEND_2B(U2b *Src);
void	DPB_SEND_4B(U4b *Src);
U2b		DPB_GET_2B(U2b *Src);

                                   
/****************************************************************************/
/*																			*/
/*	�f�[�^�]�������t���O���䏈��	�F	�c�o�q�`�l �� �e�q�`�l				*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CHK	(void)
{
	UNs		no, *srcW, datW;
	UNl		*srcL, datL;

/*--------------------------------------------------------------------------*/
//2015/03/12 �V������
////	if ((SVSW_CHG_FLG &  BLK_SRV) != 0){			// �������ݗv���t���O�������Ă�����
////		if ((HS_SVCHG_B_TO_A & BLK_SRV) == 0){		// �������݃t���O�k�n�v��������
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) == 0){	// �ǂݍ��݃t���O�k�n�v��������
////				DP_TRANS_SRV();						// �f�[�^�]������
////				HS_SVCHG_B_TO_A |= BLK_SRV;			// �������݃t���O���g�h�f�g�ɂ���
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){	// �ǂݍ��݃t���O�g�h�f�g��������
////				HS_SVCHG_B_TO_A ^= BLK_SRV;			// �������݃t���O���k�n�v�ɂ���
////				SVSW_CHG_FLG	^= BLK_SRV;			// �������ݗv���t���O���k�n�v�ɂ���
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SRV) != 0){
		DP_TRANS_SRV();
		HS_SVCHG_B_TO_A |= BLK_SRV;
		SVSW_CHG_FLG	^= BLK_SRV;
	}
	if (HS_SVCHG_B_TO_A & BLK_SRV) {
		if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SRV;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 �V������
////	if ((SVSW_CHG_FLG &  BLK_SYS) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_SYS) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_SYS) == 0){
////				DP_TRANS_SYS();
////				HS_SVCHG_B_TO_A |= BLK_SYS;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_SYS;
////				SVSW_CHG_FLG	^= BLK_SYS;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SYS) != 0){
		DP_TRANS_SYS();
		HS_SVCHG_B_TO_A |= BLK_SYS;
		SVSW_CHG_FLG	^= BLK_SYS;
	}
	if (HS_SVCHG_B_TO_A & BLK_SYS) {
		if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SYS;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/04 �V������
////	if ((SVSW_CHG_FLG &  BLK_MOT) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_MOT) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_MOT) == 0){
////				DP_TRANS_MOT();
////				HS_SVCHG_B_TO_A |= BLK_MOT;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_MOT;
////				SVSW_CHG_FLG	^= BLK_MOT;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_MOT) != 0){
		DP_TRANS_MOT();
		HS_SVCHG_B_TO_A |= BLK_MOT;
		SVSW_CHG_FLG	^= BLK_MOT;
	}
	if (HS_SVCHG_B_TO_A & BLK_MOT) {
		if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
			HS_SVCHG_B_TO_A ^= BLK_MOT;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 �V������
////	if ((SVSW_CHG_FLG &  BLK_SEQ) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_SEQ) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_SEQ) == 0){
////				DP_TRANS_SEQ();
////				HS_SVCHG_B_TO_A |= BLK_SEQ;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_SEQ;
////				SVSW_CHG_FLG	^= BLK_SEQ;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SEQ) != 0){
		DP_TRANS_SEQ();
		HS_SVCHG_B_TO_A |= BLK_SEQ;
		SVSW_CHG_FLG	^= BLK_SEQ;
	}
	if (HS_SVCHG_B_TO_A & BLK_SEQ) {
		if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SEQ;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 �V������
////	if ((SVSW_CHG_FLG &  BLK_CAM) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_CAM) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_CAM) == 0){
////				DP_TRANS_CAM();
////				HS_SVCHG_B_TO_A |= BLK_CAM;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_CAM;
////				SVSW_CHG_FLG	^= BLK_CAM;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_CAM) != 0){
		DP_TRANS_CAM();
		HS_SVCHG_B_TO_A |= BLK_CAM;
		SVSW_CHG_FLG	^= BLK_CAM;
	}
	if (HS_SVCHG_B_TO_A & BLK_CAM) {
		if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
			HS_SVCHG_B_TO_A ^= BLK_CAM;
		}
	}

//KOMA 2021-06-24(H2W:2020-08-11) A01v
	if(SVP_ATSLID_OBJ1==PVP_ATSLID_OBJ1){
		SEQ_PAR_058 |= BIT_6;
	}else{
		SEQ_PAR_058 &= ~BIT_6;
	}

/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_GEN) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_GEN) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_GEN) == 0){
				DP_TRANS_GEN();
				HS_SVCHG_B_TO_A |= BLK_GEN;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_GEN) != 0){
				// ���_�ύX���̂݁A�ǂݍ��݃t���O�������Ă�����
				DP_GET_SENS();						/* ���_���̾ݻ�l���i�[	*/
				HS_SVCHG_B_TO_A ^= BLK_GEN;
				SVSW_CHG_FLG	^= BLK_GEN;
			}
		}
	}

	/*-------------------------------------------------------*/
	/* �P�s���^�P�X�L����  ���[�V�����ݒ�𑗂�i100�i�Ή��j */		//2015/09/23
	/*-------------------------------------------------------*/
#if (mot100_test == 1)
	if ( (GAMEN_NO == 3) || (GAMEN_NO == 28) ) {		//���[�V������ʕ\�����H
		SVP_MOT_PAGE = SV_MOT_PAGE + 1;					//�y�[�W�ԍ�
		DPB_SEND_2B(&SVP_MOT_PAGE);

		datW = CSR_buff[CSR_TBL_POS_NOW].DATA_NO;
		if ( (datW >= 97) && (datW <= 101) ) {
			datW -= 97;
			datW += 1;
			SVP_MOT_CSR_STEP = SV_MOT_PAGE * 5 +datW;
		}
		else if (datW == 102) {
			SVP_MOT_CSR_STEP = 100;
		}
		else {
			SVP_MOT_CSR_STEP = 0;
		}
		DPB_SEND_2B(&SVP_MOT_CSR_STEP);
	}
	else {
		SVP_MOT_PAGE = 0;								//���[�V������ʔ�\�����y�[�W0
		DPB_SEND_2B(&SVP_MOT_PAGE);

		SVP_MOT_CSR_STEP = 0;
		DPB_SEND_2B(&SVP_MOT_CSR_STEP);
	}

	if ( (SVP_MOT_SEND_REQ == 0) &&						//CPUA��M�\��ԁH
		 (DPB_GET_2B(&SVP_MOT_SEND_REQ) == 0) ) {		//CPUB��M�\��ԁH

		if (MOT_CHG_NO[0] == 0) {						//�ύX�����s���L��H
			/* ���[�V�����̃f�[�^�����Ԃɑ��� */
			no = MOT_SEND_NO;
			if (no==0) {
				no = 1;
			}
			MOT_SEND_NO++;
			if (MOT_SEND_NO > SV_DANSUU_SRV) {
				MOT_SEND_NO = 1;
			}
		}
		else {
			/* �ύX�����s���̃��[�V�����ݒ�𑗂� */
			no = MOT_CHG_NO[0];
			MOT_CHG_NO[0] = MOT_CHG_NO[1];
			MOT_CHG_NO[1] = MOT_CHG_NO[2];
			MOT_CHG_NO[2] = MOT_CHG_NO[3];
			MOT_CHG_NO[3] = MOT_CHG_NO[4];
			MOT_CHG_NO[4] = 0;
		}
		no--;

		srcL = &SV_1DANPOS_SRV;
		datL = cnv_inch_mm(srcL[no], 0);
		if( SEQ_050_SV & BIT_1 ) {								//���]�@�H
			datL += SV_NEG_OFS_LNG;
		}
		SVP_OBJECT_PS = datL;									//�s�����̖ڕW�ʒu
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS);

		srcW = &SV_1DANDEG_SRV;
		SVP_OBJECT_DG = srcW[no];								//�s�����̖ڕW�p�x
		DPB_SEND_2B(&SVP_OBJECT_DG);

		srcW = &SV_1DANSPD_SRV;
		SVP_OBJECT_SP = srcW[no];								//�s�����̖ڕW���x
		DPB_SEND_2B(&SVP_OBJECT_SP);

		srcW = &SV_1DANTIM_SRV;
		SVP_OBJECT_TM = srcW[no] * 10;							//�s�����̒�~����
		DPB_SEND_2B(&SVP_OBJECT_TM);

		srcW = &SV_1DANPRS_SRV;;
		SVP_OBJECT_PRS = srcW[no];								//�s�����̖ڕW����
		DPB_SEND_2B(&SVP_OBJECT_PRS);

		datW = 0;
		if (step_pos_prs_chk(no)) {								//�s���� �ڕW�ʒu�^����
			datW |= cBIT0;
		}
		if (step_chg_spd_chk(no)) {								//�s���� �ϑ�  �O�^��		2016/04/15
			datW |= cBIT1;
		}
		SVP_MOT_INF = datW;										//�s���� ���
		DPB_SEND_2B(&SVP_MOT_INF);

		SVP_MOT_SEND_REQ = no + 1;
		DPB_SEND_2B(&SVP_MOT_SEND_REQ);
	}
#endif
}
/****************************************************************************/

extern	U2b		dpram_top;
extern	U2b		dpramB_top;

void	DPB_SEND_2B(
	U2b *Src
)
{
	U2b		*Dst;
	
	Dst  = (U2b *)&dpramB_top + (Src - (U2b *)&dpram_top);
	*Dst = *Src;
}

void	DPB_SEND_4B(
	U4b *Src
)
{
	U4b		*Dst;
	
	Dst  = (U4b *)&dpramB_top + (Src - (U4b *)&dpram_top);
	*Dst = *Src;
}

U2b		DPB_GET_2B(
	U2b *Src
)
{
	U2b		*Dst, dat;
	
	Dst = (U2b *)&dpramB_top + (Src - (U2b *)&dpram_top);
	dat = *Dst;

	return(dat);
}

