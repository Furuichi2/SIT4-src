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
#include	"dp_cpuab.h"
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
                                   
/****************************************************************************/
/*																			*/
/*	�f�[�^�]�������t���O���䏈��	�F	�c�o�q�`�l �� �e�q�`�l				*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CHK	(void)
{
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SRV) != 0){			// �������ݗv���t���O�������Ă�����
		if ((HS_SVCHG_B_TO_A & BLK_SRV) == 0){		// �������݃t���O�k�n�v��������
			if ((HS_SVCHG_A_TO_B & BLK_SRV) == 0){	// �ǂݍ��݃t���O�k�n�v��������
				DP_TRANS_SRV();						// �f�[�^�]������
				HS_SVCHG_B_TO_A |= BLK_SRV;			// �������݃t���O���g�h�f�g�ɂ���
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){	// �ǂݍ��݃t���O�g�h�f�g��������
				HS_SVCHG_B_TO_A ^= BLK_SRV;			// �������݃t���O���k�n�v�ɂ���
				SVSW_CHG_FLG	^= BLK_SRV;			// �������ݗv���t���O���k�n�v�ɂ���
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SYS) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_SYS) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_SYS) == 0){
				DP_TRANS_SYS();
				HS_SVCHG_B_TO_A |= BLK_SYS;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
				HS_SVCHG_B_TO_A ^= BLK_SYS;
				SVSW_CHG_FLG	^= BLK_SYS;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_MOT) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_MOT) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_MOT) == 0){
				DP_TRANS_MOT();
				HS_SVCHG_B_TO_A |= BLK_MOT;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
				HS_SVCHG_B_TO_A ^= BLK_MOT;
				SVSW_CHG_FLG	^= BLK_MOT;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SEQ) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_SEQ) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_SEQ) == 0){
				DP_TRANS_SEQ();
				HS_SVCHG_B_TO_A |= BLK_SEQ;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
				HS_SVCHG_B_TO_A ^= BLK_SEQ;
				SVSW_CHG_FLG	^= BLK_SEQ;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_CAM) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_CAM) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_CAM) == 0){
				DP_TRANS_CAM();
				HS_SVCHG_B_TO_A |= BLK_CAM;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
				HS_SVCHG_B_TO_A ^= BLK_CAM;
				SVSW_CHG_FLG	^= BLK_CAM;
			}
		}
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
}
/****************************************************************************/
