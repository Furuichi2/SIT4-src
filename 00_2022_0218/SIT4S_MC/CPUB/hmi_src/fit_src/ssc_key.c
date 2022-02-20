/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�L�[���͊֌W�̏���														*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-07
*
*************************************************************************************/

#include "string.h"								//�W�����C�u����

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include "dp_cpuab.h"


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	UNl		DigRnaChange1(UNs);
extern	void	ADC_NEXTNAME_SET(void);					/* �`�c�b���^�ԍ����� 			*/

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		Key_Data_Flg;
extern	UNs		Key_Data_No[4];
extern	UNs		Key_Data_WK[4];	//V05q
extern	UNs		GMN_PAR001;						//�␳�����l /* V00r */
extern	UNs		GMN_PAR002;						//���Y�i�搡����� /* V01  */
extern	UNs		GMN_PAR003;						//�A����s�����̖ڕW�p�x��� /* V01e */
extern	UNs		GMN_PAR004;						//�ҋ@�_�p�x�ݒ艺���l /* V01i */
extern	UNs		GMN_PAR005;						//�ҋ@�_�p�x�ݒ����l /* V01i */
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		GMN_PAR006;						//Ӱ��݊p�x�ݒ艺���l /* V01j */
extern	UNs		GMN_PAR007;						//Ӱ��݊p�x�ݒ����l /* V01j */
extern	UNs		GMN_PAR008;						//Ӱ��݊p�x�召��r�L���^���� /* V01j */
extern	UNs		GMN_PAR009;						//�߼޼��(��߼��)�ޯĔ�щ�
extern	UNs		GMN_PAR010;						//�׏d�␳�����l /* V01m */
extern	UNs		GMN_PAR011;						//�׏d�ڕW�ύX�㉺���l /* V01m */
extern	UNs		GMN_PAR012;						//�����ڕW�ύX�㉺���l /* V01m */
extern	UNs		GMN_PAR013;						//�ڕW�׏d�����l /* V01m */
extern	UNs		GMN_PAR024;						//��ݽ̧Ӱ��ݑ��x /* V01n */
extern	UNs		GMN_PAR035;						//��ݽ̧Ӱ��ݒ�~���� /* V01n */
extern	UNs		GMN_PAR015;						//���]�̏���p����l /* V05  */
extern	UNs		GMN_PAR016;						//�U�q�̏���p����ݒ� /* V06f */
extern	UNs		GMN_PAR017;						//��ڰ��p�x����l�i0�`359�x�jV05n
extern	UNs		GMN_PAR018;						//��ڰ���я���l�i0�`999ms�jV05n
extern	UNs		GMN_PAR019;						//�U�q�̏���p����ݒ� /* V06f */
extern	UNs		GMN_PAR039;						//�������\�����C���^�[�o���^�C�}����l	V05r
extern	UNs		GMN_PAR041;						//�O���^�C�}����l	V05r
extern	UNs		CB_SYS_PARAM279;				// /* V06m */
extern	UNs		GMN_PAR021;						//�U�qӰ��ݐݒ萧��		/* V06m */
extern	UNs		GMN_PAR042;						//���]Ӱ��P�ݒ���		/* V06n */
extern	UNs		GMN_PAR043;						//���]Ӱ��S�ݒ���		/* V06n */
extern	UNs		GMN_PAR020;						//V06n
extern	UNs		GMN_PAR044;						//�i�摬�x����		/* V06o */

/* �萔��` ---------------------------------------------------------- */
#define		E_SUBE1_DN	0x00D0				//�㉺���f�[�^�|�C���^
#define		E_SUBE2_DN	4					//�㉺���f�[�^�|�C���^
#define		E_SUBE3_DN	8					//�㉺���f�[�^�|�C���^
#define		E_SUBE4_DN	12					//�㉺���f�[�^�|�C���^
#define		E_SUBE5_DN	16					//�㉺���f�[�^�|�C���^
#define		E_SUBE6_DN	20					//�㉺���f�[�^�|�C���^

/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	Key_mng(void);							//�����͊m��
void	Key_Ten_in(UNs );						//Ten KEY����
void	Key_Ent_sv(void);						//�ݒ�l�̊m��
void	Key_sv_limt_chk(UNs, UNl *);			//�ݒ�l�̏㉺���`�F�b�N
void	Key_sv_tokusyu_chk(UNs);				//�ݒ�l�̓��ꏈ��
void	dansuu_zero_set(void);					//�т̒i ����00�ݒ�
UNs kajyu_chk( UNl *Dst_p, UNl bf );
UNs kagen_chk( UNl *Dst_p, UNl bf );
void	KEY_FILTER(void);						//KEY�t�B���^����	V05q

/* �����ϐ���` ------------------------------------------------------ */
UNl motion_dig_limit0(UNl, UNs);
UNl motion_dig_limit1(UNl, UNs);
UNl motion_dig_limit2(UNl, UNs);
UNl motion_pos_limit0(UNl, UNs);
UNl motion_pos_limit1(UNl, UNs);
UNl motion_pos_limit2(UNl, UNs);

/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Key_mng(���FKEY_SWMNG)
*  Function Name:	�����͊m��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:�j�����f�[�^�Ǎ����f�[�^�m��
*			�n�t�s���j�d�x�Q�c�`�s�`�Q�l�n�c�d
*			�n�t�s���j�d�x�Q�c�`�s�`�Q�b�n�c�d
*
*  �� ��	:FIT)�c�[		ON:2002-05-20
********************************************************************************
*/
void	Key_mng(void)
{
	UNs	wk1[5];


	KEY_DATA_MODE = 0;							/* Ӱ�޸ر	*/
	KEY_DATA_CODE = 0;							/* ���޸ر	*/

	if( Key_Data_Flg == 0xff ) {

		KEY_FILTER();							//V05q
		//����ȍ~�� Key_Data_No -> Key_Data_WK

		wk1[0] = Key_Data_WK[0] ^ Key_last[0];	/* key��Ԃ̕ω������o	*/
		wk1[1] = Key_Data_WK[1] ^ Key_last[1];
		wk1[2] = Key_Data_WK[2] ^ Key_last[2];
		wk1[3] = Key_Data_WK[3] ^ Key_last[3];

		Key_up[0]  = wk1[0] & Key_Data_WK[0];	/* �����オ��f�[�^�i�[ */
		Key_up[1]  = wk1[1] & Key_Data_WK[1];	/* �����オ��f�[�^�i�[ */
		Key_up[2]  = wk1[2] & Key_Data_WK[2];	/* �����オ��f�[�^�i�[ */
		Key_up[3]  = wk1[3] & Key_Data_WK[3];	/* �����オ��f�[�^�i�[ */

		Key_dn[0] = wk1[0] & Key_last[0];		/* ����������f�[�^�i�[ */
		Key_dn[1] = wk1[1] & Key_last[1];		/* ����������f�[�^�i�[ */
		Key_dn[2] = wk1[2] & Key_last[2];		/* ����������f�[�^�i�[ */
		Key_dn[3] = wk1[3] & Key_last[3];		/* ����������f�[�^�i�[ */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Key_dn[0] &= 0x0002;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[1] &= 0x0002;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[2] &= 0x0006;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[3] &= 0x0004;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
#else
		Key_dn[0] &= 0x0002;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[1] &= 0x0006;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[2] &= 0x0006;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
//V01z		Key_dn[3] &= 0x0002;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
		Key_dn[3] &= 0x0006;					/* �s�p�f�[�^�}�X�N�@�r�v�����c�� */
#endif

		Key_last[0] = Key_Data_WK[0];
		Key_last[1] = Key_Data_WK[1];
		Key_last[2] = Key_Data_WK[2];
		Key_last[3] = Key_Data_WK[3];

		Key_Data_Flg = 0;						/* �j�����f�[�^�t���O�N���A */

		if( (Key_up[0] != 00) || (Key_up[1] != 00) ||		/* �j���������オ�� ����H	*/
			(Key_up[2] != 00) || (Key_up[3] != 00) ) {		/* �j���������オ�� ����H	*/
/************	�e���L�[��t����	*********************************/
			if( ((Key_up[0] & 0x0038) != 00) || ((Key_up[2] & 0x0038) != 00) ||
				((Key_up[1] & 0x0038) != 00) || ((Key_up[3] & 0x0038) != 00) ) {
				KEY_DATA_MODE = E_key_ten_mode;		/* �e���L�[���[�h�Z�b�g */

				if( Key_up[0] & 0x0008 ) {
					KEY_DATA_CODE = E_key_0;		/* 0�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x08 ) {
					KEY_DATA_CODE = E_key_1;			/* 1�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x10 ) {
					KEY_DATA_CODE = E_key_2;			/* 2�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x20 ) {
					KEY_DATA_CODE = E_key_3;			/* 3�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x08 ) {
					KEY_DATA_CODE = E_key_4;			/* 4�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x0010 ) {
					KEY_DATA_CODE = E_key_5;			/* 5�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x0020 ) {
					KEY_DATA_CODE = E_key_6;			/* 6�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[3] & 0x08 ) {
					KEY_DATA_CODE = E_key_7;			/* 7�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[3] & 0x10 ) {
					KEY_DATA_CODE = E_key_8;			/* 8�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[3] & 0x20 ) {
					KEY_DATA_CODE = E_key_9;			/* 9�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[0] & 0x0010 ) {
					KEY_DATA_CODE = E_key_ten;			/* �D�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[0] & 0x0020 ) {
					KEY_DATA_CODE = E_key_cl;			/* CL �j�d�x�R�[�h�Z�b�g */
				}
			}
/************	�d�m�s�L�[��t����	*********************************/
			else if( Key_up[0] & 0x0004 ) {
				KEY_DATA_MODE = E_key_ent_mode;		/* �d�m�s�@���[�h�Z�b�g */
				KEY_DATA_CODE = E_key_ent;			/* �d�m�s�@�j�d�x�R�[�h�Z�b�g */
			}
/************	�J�[�\���L�[��t����	*********************************/
			else if( ((Key_up[0] & 0x01) != 00) || ((Key_up[2] & 0x01) != 00) ||
					((Key_up[1] & 0x01) != 00) || ((Key_up[3] & 0x01) != 00) ) {
				KEY_DATA_MODE = E_key_csr_mode;		/* �J�[�\���@���[�h�Z�b�g */

				if( Key_up[0] & 0x0001 ) {
					KEY_DATA_CODE = E_key_left;		/* ���@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x01 ) {
					KEY_DATA_CODE = E_key_right;	/* ���@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x0001 ) {
					KEY_DATA_CODE = E_key_down;		/* ���@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[3] & 0x01 ) {
					KEY_DATA_CODE = E_key_up;		/* ���@�j�d�x�R�[�h�Z�b�g */
				}
			}
/************	�r�v�P�`�r�v�S�L�[��t����	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_up[0] & 0x02) != 00) || ((Key_up[2] & 0x02) != 00) ||
					((Key_up[1] & 0x02) != 00) || ((Key_up[3] & 0x02) != 00) ) {
				KEY_DATA_MODE = E_key_sw14_mode;		/* �r�v�@���[�h�Z�b�g */

				if( Key_up[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1;		/* �r�v�P�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2;			/* �r�v�Q�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3;			/* �r�v�R�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4;			/* �r�v�S�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#else
			else if( ((Key_up[0] & 0x02) != 00) || ((Key_up[2] & 0x02) != 00) ||
					((Key_up[1] & 0x02) != 00) || ((Key_up[3] & 0x02) != 00) ||
					((Key_up[3] & 0x04) != 00) ) {										/* V01z */
				KEY_DATA_MODE = E_key_sw14_mode;		/* �r�v�@���[�h�Z�b�g */

				if( Key_up[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1;		/* �r�v�P�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2;			/* �r�v�Q�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3;			/* �r�v�R�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4;			/* �r�v�S�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[3] & 0x04 ) {			/* V01z */
					KEY_DATA_CODE = E_key_sw7;			/* �r�v�V�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#endif
/************	�r�v�T�`�r�v�U����L�[��t����	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_up[2] & 0x04) != 00) || ((Key_up[3] & 0x04) != 00) ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* ����@���[�h�Z�b�g */

				if( Key_up[3] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5;			/* �r�v�T�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6;			/* �r�v�U�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#else
			else if( ((Key_up[2] & 0x04) != 00) || ((Key_up[1] & 0x04) != 00) ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* ����@���[�h�Z�b�g */

				if( Key_up[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5;			/* �r�v�T�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_up[1] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6;			/* �r�v�U�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#endif
/************	�r�v�V�^�i���L�[��t����	*********************************/
			else {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				if( Key_up[1] & 0x04 ) {
					KEY_DATA_MODE = E_key_sw7_mode;		/* ���[�h�Z�b�g */
					KEY_DATA_CODE = E_key_sw7;			/* �r�v�V�@�j�d�x�R�[�h�Z�b�g */
				}
#else
#endif
			}
		}

/* ����������f�[�^���o������	*/
		else if( (Key_dn[0] != 00) || (Key_dn[2] != 00) ||		/* �j�������������� ����H	*/
			(Key_dn[1] != 00) || (Key_dn[3] != 00) ) {
/************	�r�v�T�`�r�v�U����L�[��t����	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			if( (Key_dn[2] & 0x04) != 00 || (Key_dn[3] & 0x04) != 00 ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* ����@���[�h�Z�b�g */

				if( Key_dn[3] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5_down;			/* �r�v�T�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6_down;			/* �r�v�U�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#else
			if( (Key_dn[2] & 0x04) != 00 || (Key_dn[1] & 0x04) != 00 ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* ����@���[�h�Z�b�g */

				if( Key_dn[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5_down;			/* �r�v�T�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[1] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6_down;			/* �r�v�U�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#endif
/************	�r�v�P�`�r�v�S�L�[��t����	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_dn[0] & 0x02) != 00) || ((Key_dn[2] & 0x02) != 00) ||
					((Key_dn[1] & 0x02) != 00) || ((Key_dn[3] & 0x02) != 00) ) {
				KEY_DATA_MODE = E_key_sw14_mode;		/* �r�v�@���[�h�Z�b�g */

				if( Key_dn[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1_down;		/* �r�v�P�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2_down;		/* �r�v�Q�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3_down;		/* �r�v�R�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4_down;		/* �r�v�S�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#else
			else if( ((Key_dn[0] & 0x02) != 00) || ((Key_dn[2] & 0x02) != 00) ||
					((Key_dn[1] & 0x02) != 00) || ((Key_dn[3] & 0x02) != 00) ||
					((Key_dn[3] & 0x04) != 00) ) {									/* V01z */
				KEY_DATA_MODE = E_key_sw14_mode;		/* �r�v�@���[�h�Z�b�g */

				if( Key_dn[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1_down;		/* �r�v�P�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2_down;		/* �r�v�Q�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3_down;		/* �r�v�R�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4_down;		/* �r�v�S�@�j�d�x�R�[�h�Z�b�g */
				}
				else if( Key_dn[3] & 0x04 ) {			/* V01z */
					KEY_DATA_CODE = E_key_sw7_down;		/* �r�v�V�@�j�d�x�R�[�h�Z�b�g */
				}
			}
#endif
		}
	}
}


/*
********************************************************************************
*  Module Name:		Key_Ten_in(���FTENKEY_INP)
*  Function Name:	Ten KEY����
*  Input	: 		���ͷ������
*
*  Return	: 		�Ȃ�
*  Note		:		0�`9/�D/CL�@�����͏���
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	Key_Ten_in(UNs k_code)
{
	UNs		t_no, i;
	UNl		d_bf;

	if(CSR_CNT == 00 || SV_TBL_POS_NOW == 0xff ) {			//�J�[�\���ʒu�ɐݒ�l�Ȃ�
		return;
	}

	t_no = SV_TBL_POS_NOW;

	if(k_code == E_key_cl) {								//CL Key ?
		SV_DATA_CHG = 0xff;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
		SV_DISP_BUFF = 0;									//�ύX�f�[�^�o�b�t�@�N���A

		TENKEY_CNT = SV_buff[t_no].XY_POS;					//�ݒ�l�\����X,Y��
		TENKEY_CNT >>= 10;									//���ْ��@�ݒ�

		if(SV_buff[t_no].TOK_FLG & BIT_2) {					//�����׸�(�S�p�f�[�^�H)
			TENKEY_CNT >>= 1;								//�S�p
		}
		if(SV_buff[t_no].TEN_POS != 00 ) {					//�����_�L��f�[�^�H
			TENKEY_CNT--;									//Yes
			TENKEY_CNT -= SV_buff[t_no].TEN_POS;			//�����ȉ��̓��͂𖳌��ɂ���
		}
	}
	else if(k_code == E_key_ten) {							//'.' Key ?
		if (SV_DATA_CHG == 0x55) {
			//����.(TEN)��t��								// 2013/02/04 V06o
			return;
		}
		else {
			TENKEY_CNT = SV_buff[t_no].TEN_POS;					//�����ȉ��̓��͂�L���ɂ���
			SV_DATA_CHG = 0x55;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
		}
	}
	else{													//0�`9 Key����
		if(SV_DATA_CHG == 00) {								//�ݒ��ް��ύX �L��H
			SV_DATA_CHG = 0xff;								//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
			SV_DISP_BUFF = 0;								//�ύX�f�[�^�o�b�t�@�N���A

			TENKEY_CNT = SV_buff[t_no].XY_POS;				//�ݒ�l�\����X,Y��
			TENKEY_CNT >>= 10;								//���ْ��@�ݒ�

			if(SV_buff[t_no].TOK_FLG & BIT_2) {				//�����׸�(�S�p�f�[�^�H)
				TENKEY_CNT >>= 1;							//�S�p
			}
			if(SV_buff[t_no].TEN_POS != 00 ) {				//�����_�L��f�[�^�H
				TENKEY_CNT--;								//Yes
				TENKEY_CNT -= SV_buff[t_no].TEN_POS;		//�����ȉ��̓��͂𖳌��ɂ���
			}
		}

		if( TENKEY_CNT == 00 ) {							//���̓I�[�o�[�H
			return;											//Yes
		}
		else{
			d_bf = k_code & 0x000f;
			TENKEY_CNT--;									//-1
			if(SV_DATA_CHG == 0x55){						//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
				for(i=TENKEY_CNT ; i > 0 ; i--){			//���̐���
					d_bf <<= 4;
				}
				SV_DISP_BUFF |= d_bf;						//�j�d�x�R�[�h�Z�b�g
			}
			else{
				for(i=SV_buff[t_no].TEN_POS ; i > 0 ; i--){	//���̐���
					d_bf <<= 4;
				}
				SV_DISP_BUFF <<= 4;							//�ύX�f�[�^�o�b�t�@�N���A
				SV_DISP_BUFF |= d_bf;						//�j�d�x�R�[�h�Z�b�g
			}
		}
	}

	if( SV_buff[t_no].TOK_FLG & BIT_7 ) {					//�����׸�b7 = ��ۻ��ڽ����@�H
		i = 0xff;
	}
	else{													//����
		i = 0x00;
	}
	SVPV_data_disp(SV_DISP_BUFF, &SV_buff[t_no], i, 0x82);	//�ݒ�l�������l �\��(��ۻ��ڽ/���]�\��)

//	if( SV_DISP_BUFF == 0 ) {
//		TENKEY_CNT = SV_buff[t_no].XY_POS;					//�ݒ�l�\����X,Y��
//		TENKEY_CNT >>= 10;									//���ْ��@�ݒ�
//
//		if(SV_buff[t_no].TOK_FLG & BIT_2) {					//�����׸�(�S�p�f�[�^�H)
//			TENKEY_CNT >>= 1;								//�S�p
//		}
//		if(SV_buff[t_no].TEN_POS != 00 ) {					//�����_�L��f�[�^�H
//			TENKEY_CNT--;									//Yes
//			TENKEY_CNT -= SV_buff[t_no].TEN_POS;			//�����ȉ��̓��͂𖳌��ɂ���
//		}
//	}
}


/*
********************************************************************************
*  Module Name:		Key_Ent_sv(���FSVDATA_ENT)
*  Function Name:	�ݒ�l�̊m��
*  Input	: 		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		ENT�@�����͏���
*
*  �� ��	:FIT)�c�[		ON:2002-05-30
********************************************************************************
*/
void	Key_Ent_sv(void)
{
	UNs		t_no, z_f, *Dst_p, cnt, flag;
	UNl		cnv_bf, *Dst_lp;
	long	*Dst_Slp, cnv_bf_s;
	short	*Dst_Sp;

	t_no = SV_TBL_POS_NOW;

	if(SV_DATA_CHG != 00){
		SV_DATA_CHG = 00;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)

		cnv_bf = BCD_HEX4(SV_DISP_BUFF);					//BCD �� HEX �ϊ�

		Key_sv_limt_chk(t_no, &cnv_bf);						//�ݒ�l�̏㉺���`�F�b�N

		if(SV_buff[t_no].TOK_FLG & BIT_0){					//�����׸�(BCD ?)
			cnv_bf = HEX_BCD4(cnv_bf);						//HEX �� BCD �ϊ�
		}
		cnt = (SV_buff[t_no].BYTE_NO & 0x000f);				//�ް��i�[����޲Ē�
		if(cnt == 4){										//long(4byte) ?
			Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
			*Dst_lp = cnv_bf;
		}
		else{												//short(2byte)
			Dst_p = SV_buff[t_no].DATA_ADR;					//�ް��i�[���ڽ
			*Dst_p = (UNs)cnv_bf;
		}

		FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

		flag = 0x02;										//BCD
		if(0 == (SV_buff[t_no].TOK_FLG & BIT_0) ){			//�����׸�(HEX ?)
			flag = 0x01;									//HEX
		}

		if( SV_buff[t_no].TOK_FLG & BIT_7 ) {				//�����׸�b7 = ��ۻ��ڽ����@�H
			z_f = 0xff;
		}
		else {												//����
			z_f = 0x00;
		}

		if ((WINDOW_NO == 12) && (SV_buff[t_no].SUB_NO == 48)) {	// ADC�ï�������ʂ̎��^�ԍ��H		V01j
			flag |= BIT_9;
		}

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);		//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)

		WIN_grph();											//�E�C���h�E��ʏ�O���t�B�b�N�`��

		Key_sv_tokusyu_chk(t_no);							//�ݒ�l���ꏈ��

		TENKEY_CNT = 0;
		SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//�i�[�׸�
	}

	if( CSR_MOVE_NON != 0xff ) {							//�J�[�\���͓����Ȃ��H

		CSR_FLG = 2;										//���|�W�V�����Z�b�g

//V01d		if( GAMEN_NO != 3 && GAMEN_NO != 28 ){
		if( GAMEN_NO != 3 && GAMEN_NO != 28 && GAMEN_NO != 6 && GAMEN_NO != 30 ){
			if(SV_buff[t_no].DSP_NO >=							//���ٔF���ԍ����̈ړ�����
				CSR_buff[CSR_TBL_POS_NOW].SV_MAX) {				//�ݒ�lð��ٌ�
				CSR_FLG = 3;									//���|�W�V�����Z�b�g
			}
		}
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);					//�J�[�\���ړ�(�߂�l�w��,�ړ�)
		SV_csr_set();										//�ݒ�l�J�[�\��

		Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
		Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
	}

	if(WINDOW_NO == 0) {
//		Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);		//�S�\��
	}
	else{
		Lcd_line( 00, 6, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 8, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 10, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
//		Lcd_line( 00, 12, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
	}
	if(WINDOW_NO == 12) {
		ADC_NEXTNAME_SET();		/* �`�c�b���^�ԍ����� */
		WIN_gamen_disp();		/* �ĕ\�� */
		ADC_DISP_FLG = 0x0FF;					/* �`�c�b�E�C���h�E�\���� */
		ADC_CHG_LST1 = 0;
		ADC_CHG_LST2 = 0;
		ADC_CHG_LST2_2 = 0;
	}

}


/*
********************************************************************************
*  Module Name:		Key_sv_limt_chk(���FMIN_MAX_CHK)
*  Function Name:	�ݒ�l�̏㉺���`�F�b�N
*  Input	: 		�ݒ�l���ð��ق̔ԍ�
*					�ޯ̧�̐擪���ڽ
*
*  Return	: 		�Ȃ�
*  Note		:		�ݒ�l���ð��قŎw�肳�ꂽ�l�̃`�F�b�N���s���B
*
*  �� ��	:FIT)�c�[		ON:2002-05-31
********************************************************************************
*/
void	Key_sv_limt_chk(UNs t_no, UNl *wk_p)
{
	UNl		wl0, wl1, bf, *Dst_p, *Src_p;
	UNl		kagen_mm, jyogen_mm;
	UNs		i , j, ww0, ww1;
	UNl		*Dst_p_w, long_bf, *posn, *posb;
	UNs		*degn, *degb;
	S4b		ofs, dat;

	Dst_p = wk_p;
	bf = *wk_p;

	switch( SV_buff[t_no].SUB_NO ) {							//���ٰ�ݔԍ��ւ̑J��
		default:
		case 00:				//�����Ȃ�
			break;

		case 01:				//0 �` 9
			if( bf > 9 ) {
				*Dst_p = 9;
			}
			break;

		case 02:				//0 �` 100
			if( bf > 100 ) {
				*Dst_p = 100;
			}
			break;

		case 03:				//90 �` 270
			if( bf > 270 ) {
				*Dst_p = 270;
			}
			else if(bf < 90) {
				*Dst_p = 90;
			}
			break;

		case 04:				//0 �` 300
			if( bf > 300 ) {
				*Dst_p = 300;
			}
			break;

		case 05:				//0 �` 359
			if( bf > 359 ) {
				*Dst_p = 359;
			}
			break;

		case 06:				//0 �` 99
		case 28:				//0 �` 99
			if( bf > 99 ) {
				*Dst_p = 99;
			}
			break;

		case 07:				//270 �` 359
			if( bf > 359 ) {
				*Dst_p = 359;
			}
			else if(bf < 270) {
				*Dst_p = 270;
			}
			break;

		case 8:					//����f�[�^(���ʒu�����������)
			if( INI_POS_ERR_FLG != 0xff ) {					//�C�j�V�������|�W�V���i�[�ݒ�l�ُ�H
				if( bf >= SV_GENITI_A21 ){					//��������ʒu
					*Dst_p = SV_UPDATA_A21;
				}
				else if( bf <= SV_DNDATA_A21 ) {			//���������
					*Dst_p = SV_UPDATA_A21;
				}
			}
			break;

		case 9:					//�����f�[�^(����������C���������ʒu�|���x)
			if( INI_POS_ERR_FLG != 0xff ) {					//�C�j�V�������|�W�V���i�[�ݒ�l�ُ�H
				if( SV_GENITI_A21 >= SV_KANDO_A21 ) {
					wl0 = (SV_GENITI_A21 - SV_KANDO_A21);
					if( bf <= wl0) {							//���������ʒu�|���x
						*Dst_p = SV_DNDATA_A21;
					}
					else if(bf >= SV_UPDATA_A21) {				//���������
						*Dst_p = SV_DNDATA_A21;
					}
				}
				else{
					if( bf >= SV_UPDATA_A21) {					//���������
						*Dst_p = SV_DNDATA_A21;
					}
				}
			}
			break;

		case 10:				//�ő�c�f�[�^�`�F�b�N
			if( bf > 1500 ) {				//�P�T�O�O����H
				*Dst_p = 2000;
			}
			else if(bf <= 200) {			//�Q�O�O�ȉ��H
				*Dst_p = 200;
			}
			else if(bf <= 400) {			//�S�O�O�ȉ��H
				*Dst_p = 400;
			}
			else if(bf <= 800) {			//�W�O�O�ȉ��H
				*Dst_p = 800;
			}
			else {							//�P�T�O�O�ȉ��H
				*Dst_p = 1500;
			}
			break;

		case 11:				//���ׂ�ʂP�@�㉺���`�F�b�N
//?			Src_p = E_SUBE1_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 12:				//���ׂ��2�@�㉺���`�F�b�N
//?			Src_p = E_SUBE2_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 13:				//���ׂ��3�@�㉺���`�F�b�N
//?			Src_p = E_SUBE3_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 14:				//���ׂ��4�@�㉺���`�F�b�N
//?			Src_p = E_SUBE4_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 15:				//���ׂ��5�@�㉺���`�F�b�N
//?			Src_p = E_SUBE5_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 16:				//���ׂ��6�@�㉺���`�F�b�N
//?			Src_p = E_SUBE6_DN;					//�㉺���f�[�^�|�C���^
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 17:				//0 �` 511
			if( bf > 511 ) {
				*Dst_p = 511;
			}
			break;

		case 18:				//���ʒu�`�F�b�N(���ʒu������A���ʒu�����x�{����)
			if( INI_POS_ERR_FLG != 0xff ) {					//�C�j�V�������|�W�V���i�[�ݒ�l�ُ�H
				if( bf <= SV_UPDATA_A21 ) {
					*Dst_p = SV_GENITI_A21;
				}
				else if(bf > SV_UPDATA_A21 ) {
					wl0 = SV_KANDO_A21;					//���x
					wl0 += SV_DNDATA_A21;
					if( bf >= wl0 ){						//���ʒu�����x�{����
						*Dst_p = SV_GENITI_A21;
					}
				}
			}
			break;

		case 19:				//���x�f�[�^(���x�����ʒu�|����)
			if( INI_POS_ERR_FLG != 0xff ) {					//�C�j�V�������|�W�V���i�[�ݒ�l�ُ�H
				if( SV_GENITI_A21 >= SV_DNDATA_A21 ) {
					wl0 =(SV_GENITI_A21 - SV_DNDATA_A21);
					if( bf <= wl0) {							//���x�����ʒu�|����
						*Dst_p = SV_KANDO_A21;
					}
				}
			}
			break;

		case 20:				//�ݒ�l�f�[�^(������ݒ�l������)
			if( INI_POS_ERR_FLG != 0xff ) {					//�C�j�V�������|�W�V���i�[�ݒ�l�ُ�H
				if( bf > SV_UPDATA_A21 ) {					//�ݒ�l�����
					Src_p = (UNl *)SV_buff[SV_TBL_POS_NOW].DATA_ADR;	//�ް��i�[���ڽ
					*Dst_p = *Src_p;
				}
				else if( bf < SV_DNDATA_A21 ) {				//���ʒu������
					Src_p = (UNl *)SV_buff[SV_TBL_POS_NOW].DATA_ADR;	//�ް��i�[���ڽ
					*Dst_p = *Src_p;
				}
			}
			break;

		case 21:				//�I�[�o�[���[�h�i���j�@�l�`�w�`�F�b�N
		case 35:				//�ő�׏d�i���j�ȉ��@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKAJ_A24 ) {		//�ő�׏d�i���ȉ��j
					*Dst_p = SV_MAXKAJ_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 22:				//�I�[�o�[���[�h�i���v�j�@�l�`�w�`�F�b�N
		case 36:				//�ő�׏d�i���v�j�ȉ��@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA2_A24 ) {		//�ő�׏d�i���v�ȉ��j
					*Dst_p = SV_MAXKA2_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 23:				//�I�[�o�[���[�h�i�E�j�@�l�`�w�`�F�b�N
		case 37:				//�ő�׏d�i�E�j�ȉ��@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {		//�ő�׏d�i�E�ȉ��j
					*Dst_p = SV_MAXKA3_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 24:				//�I�[�o�[���[�h�i���j�@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKAJ_A24 ) {			//�ő�׏d�i���ȉ��j
					*Dst_p = SV_MAXKAJ_A24;
				}
				else if( bf > SV_OVERE1_A26 ) {	//�I�[�o�[���[�h�i���ȉ��j
					*Dst_p = SV_OVERE1_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 25:				//���A�[���~�b�^�i���v�j�@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA2_A24 ) {			//�ő�׏d�i���v�ȉ��j
					*Dst_p = SV_MAXKA2_A24;
				}
				else if( bf > SV_OVERE2_A26 ) {		//�I�[�o�[���[�h�i���v�ȉ��j
					*Dst_p = SV_OVERE2_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 26:				//���A�[���~�b�^�i���j�@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {			//�ő�׏d�i�E�ȉ��j
					*Dst_p = SV_MAXKA3_A24;
				}
				else if( bf > SV_OVERE3_A26 ) {		//�I�[�o�[���[�h�i�E�ȉ��j
					*Dst_p = SV_OVERE3_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 27:				//0 �` 330
			if( bf > 330 ) {
				*Dst_p = 330;
			}
			break;

		case 29:				//0 �` 0xffff
			if( bf > 0xffff ) {
				*Dst_p = 0xffff;
			}
//V05j			if ( GAMEN_NO == 50 ) {			// V05i
//////				KJ_CHK_CNT8++;
//////			}
			break;

		case 30:				//�d�lMAX���x�ȉ�
			if( bf >= SV_SYUMAX_A14 ) {							//�d�l���x�ȉ�
				*Dst_p = SV_SYUMAX_A14;							//�ō����x�ȉ�
			}
			break;

		case 31:				//0 �` 600
			if( bf > 600 ) {
				*Dst_p = 600;
			}
			break;

		case 32:				//0 �` 255
			if( bf > 255 ) {
				*Dst_p = 255;
			}
//V05j			if ( GAMEN_NO == 50 ) {			// V05i
//////				KJ_CHK_CNT8++;
//////			}
			break;

		case 33:				//1 �` 2(�X���C�h�����̈ʒu�ް�����)
//SIT-S�Ȃ�			if( SEQ_016_SV & BIT_6 ) {				//�P�ʐؑց@INCH(1:�L��)
//				*Dst_p = 3;
//			}
//			else {
//				if( bf > 2 ) {
//					*Dst_p = 2;
//				}
//				else if(bf == 0 ){
//					*Dst_p = 1;
//				}
//			}
			break;

		case 34:				//������ ���ʒuPV���͗p
			PVGENNITI_FLG = 0xff;
			break;

		case 38:				//�ō����x�ȉ�
			if( bf >= SV_MAXSPM_A14 ) {							//�ō����x�ȉ�
				*Dst_p = SV_MAXSPM_A14;							//�ō����x�ȉ�
			}
			break;

		case 39:				//+-�ݒ�
			
			break;

		case 40:				//0 �` 65535 / 0 �` 32767
			i = CSR_FLG_CNT;									//�J�[�\���ʒu�Ǎ�
			if( i == 0 ) {
				if( bf > 65535 ) {
					*Dst_p = 65535;
				}
			}
			else {
				i --;
				j = 1;
				j <<= i;
				if( SV_CILMAI_A50 & j ) {						//ϲŽ�L���t���O
					if( bf > 0x7fff ) {
						*Dst_p = 0x7fff;
					}
				}
				else {
					if( bf > 65535 ) {
						*Dst_p = 65535;
					}
				}
			}
			break;

		case 41:				//0 �` 5
			if( bf > 5 ) {
				*Dst_p = 5;
			}
			break;

		case 42: /*V01l_a*/				//�޲����ݎ��������
			if(bf != SV_UPDATA_A47) {			//������ݒ�
				if(bf > SV_UPDATA_A47) {		//������ݒ�
					*Dst_p = SV_UPDATA_A47;
				}
				else if(bf < SV_DNDATA_A47) {		//�ݒ聆����
					*Dst_p = SV_DNDATA_A47;
				}
			}
			break;

		case 43: /*V01l_a*/				//�޲����ݎ����E���
			if(bf != SV_UPDATA_A48) {			//������ݒ�
				if(bf > SV_UPDATA_A48) {		//������ݒ�
					*Dst_p = SV_UPDATA_A48;
				}
				else if(bf < SV_DNDATA_A48) {		//�ݒ聆����
					*Dst_p = SV_DNDATA_A48;
				}
			}
			break;

		case 44:				//���ݻ���(������ݒ�l������)
			if(bf != SV_BARAUP_A49) {			//������ݒ�
				if(bf > SV_BARAUP_A49) {		//������ݒ�
					*Dst_p = SV_BARAUP_A49;
				}
				else if(bf < SV_BARADN_A49) {		//�ݒ聆����
					*Dst_p = SV_BARADN_A49;
				}
			}
			break;

		case 45: /*V01l_a*/		//�޲����ݎ���������
			if(bf != SV_DAILUP_A49) {			//������ݒ�
				if(bf > SV_DAILUP_A49) {		//������ݒ�
					*Dst_p = SV_DAILUP_A49;
				}
				else if(bf < SV_DAILDN_A49) {		//�ݒ聆����
					*Dst_p = SV_DAILDN_A49;
				}
			}
			break;

		case 46: /*V01l_a*/		//�޲����ݎ��������E
			if(bf != SV_DAIRUP_A49) {			//������ݒ�
				if(bf > SV_DAIRUP_A49) {		//������ݒ�
					*Dst_p = SV_DAIRUP_A49;
				}
				else if(bf < SV_DAIRDN_A49) {		//�ݒ聆����
					*Dst_p = SV_DAIRDN_A49;
				}
			}
			break;

		case 47:				//1 �` 100 ���́A1 �` 10	(�^�ް�)
			if( MLD_100_FLG == 0xaa ) {
				if(bf > 100){
					*Dst_p = 100;
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else if ( MLD_100_FLG == 0xbb ) {		//V06n
				if(bf > 200){
					*Dst_p = 200;
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else {
				if(bf > 10){
					*Dst_p = 10;
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			break;

		case 48:				//�^�ް�����
			if( MLD_100_FLG == 0xaa ) {
				if(bf > 100){
					*Dst_p = 100;
				}
			}
			else {
				if(bf > 10){
					*Dst_p = 10;
				}
			}
			break;

		case 49:				//0 �` 599->999
/* V00p */
			if( bf > /*599*/ 999 ) {
				*Dst_p = /*599*/ 999;
			}
			break;

		case 50:				//1 �` 6
			if( (bf & 0xffff0000) != 00 ) {
				*Dst_p = SV_UPDANO_MAX;
			}
			else {
				if( bf == 0 ) {
					*Dst_p = 1;
				}
				else if(bf > SV_UPDANO_MAX) {
					*Dst_p = SV_UPDANO_MAX;
				}
			}
			break;

		case 51:				//1 �` 5 (�i��)
			wl0 = 5;
			if (SEQ_024_SV & BIT_3) {				/* V01d */
				wl0 = 10;
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			if ((GAMEN_NO == 6) && (*Dst_p <= 5)) {		/*V01e*/
				disp_stg_sel = E_sstg_mmon;				//���Y[���[�V�������j�^6�`10]��
				GAMEN_NO = 3;
				GAMEN_disp();							//��ʕ\��
			}
			if ((GAMEN_NO == 30) && (*Dst_p <= 5)) {	/*V01e*/
				disp_stg_sel = E_dstg_mset;				//�f�[�^�ݒ�[���[�V�������j�^6�`10]��
				GAMEN_NO = 28;
				GAMEN_disp();							//��ʕ\��
			}
			break;

		case 52:				//0 �` 1000
			if( bf > 1000 ) {
				*Dst_p = 1000;
			}
			break;

		case 53:				//0 �` �H���� + �ŏI�H���i�H���������j
			if( bf > (SV_DANSUU_SRV + 1) ) {
				*Dst_p = SV_DANSUU_SRV + 1;
			}
			else if( bf == 0 ){	//�i��00�H
				dansuu_zero_set();				//�т̒i 00�ݒ�
			}
			break;

		case 54:				//0 �` ���]�ݒ�s�͈́@(�ݒ�l���~10�{)
			bf *= 10;									//�~10�{
			if( bf > SV_DNAREA_JUDG ) {
				bf = SV_DNAREA_JUDG;
			}
			if( SV_buff[t_no].GRP_NO == 85 ) {				//����p�̐ݒ�		V06k (INS)
				if( SEQ_050_SV & BIT_1 ) {					//���]���̏���p�̍ő�l���~�b�g		V05 (INS)
					if( bf > GMN_PAR015 ) {
						bf = GMN_PAR015;
					}
				}
				else if ( SEQ_050_SV & BIT_2 ) {			//�U�q�̏���p�̍ő�/�ŏ��l���~�b�g		V06f (INS)
					if( bf > GMN_PAR016 ) {
						bf = GMN_PAR016;					//�ő僊�~�b�g
					}
					if( bf < GMN_PAR019 ) {
						bf = GMN_PAR019;					//�ŏ����~�b�g
					}
				}
			}
			*Dst_p = bf;
			break;

		case 55:				//0 �` 359�@(�ݒ�l���~10�{)
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//�~10�{
			*Dst_p = bf;
			break;

		case 56:				//����ʒu
			wl0 = SV_RNA_STLORK;						//�X�g���[�N�ݒ�(�����_ 3��)
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				*Dst_p = wl0;							//�X�g���[�N�ݒ�
				bf = wl0;
			}

			if( SEQ_050_SV & BIT_1 ) {					//���]���̏���ʒu		V05 (INS)
				wl0 = DigRnaChange1(GMN_PAR015);		//�p�x��mm�ϊ�
				if( bf < wl0 ) {
					*Dst_p = wl0;
					bf = wl0;
				}
			}
			else if ( SEQ_050_SV & BIT_2 ) {			//�U�q�̏���ʒu		V06f (INS)
				wl0 = DigRnaChange1(GMN_PAR016);		//�p�x��mm�ϊ�
				if( bf < wl0 ) {
					*Dst_p = wl0;						//�ŏ����~�b�g
					bf = wl0;
				}
				wl0 = DigRnaChange1(GMN_PAR019);		//�p�x��mm�ϊ�
				if( bf > wl0 ) {
					*Dst_p = wl0;						//�ő僊�~�b�g
					bf = wl0;
				}
			}

			break;

		case 57:				//�@�B���� �` �@�B���
			wl0 = SV_RNAPOS_MINP;						//�@�B����(�����_ 3��)
			wl1 = SV_RNAPOS_MAXP;						//�@�B���(�����_ 3��)
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
					wl1 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl1 ) {
				*Dst_p = wl1;							//�@�B���
			}
			else if(bf < wl0) {							//�@�B����
				*Dst_p = wl0;
			}
			break;

		case 58:				//�޲ʲĕ␳��r�l(��) �` �޲ʲĕ␳��r�l(��)
//			wl0 = SV_DAIHAI_LNG1 * 1000;				//�޲ʲĕ␳��r�l(��) �����_ 0�� -> 3��
//			wl1 = SV_DAIHAI_LNG2 * 1000;				//�޲ʲĕ␳��r�l(��) �����_ 0�� -> 3��
			wl0 = SV_DAIHAI_LNG1 * 100;					//�޲ʲĕ␳��r�l(��) �����_ 1�� -> 3��
			wl1 = SV_DAIHAI_LNG2 * 100;					//�޲ʲĕ␳��r�l(��) �����_ 1�� -> 3��
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if(	SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
					wl1 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl1 ) {
				*Dst_p = wl1;							//�޲ʲĕ␳��r�l(��)
			}
			else if(bf < wl0) {
				*Dst_p = wl0;							//�޲ʲĕ␳��r�l(��)
			}
			break;

		case 60:				//0 �` 1
			if( bf > 1 ) {
				*Dst_p = 1;
			}
			break;

		case 61:				//0 �` 2->3				//2009/11/04 V05p
			if( bf > 3 ) {
				*Dst_p = 3;
			}
			break;

		case 62:				//1 �` 32767
			if( bf > 32767 ) {
				*Dst_p = 32767;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 63:				//1 �` 2000000
			if( bf > 2000000 ) {
				*Dst_p = 2000000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 64:				//0 �` 1000000
			if( bf > 1000000 ) {
				*Dst_p = 1000000;
			}
			break;

		case 65:				//0 �` 10000
			if( bf > 10000 ) {
				*Dst_p = 10000;
			}
			break;

		case 66:				//1 �` 10000
			if( bf > 10000 ) {
				*Dst_p = 10000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 67:				//0 �` 32767
			if( bf > 32767 ) {
				*Dst_p = 32767;
			}
			break;

		case 68:				//1 �` 3599
			if( bf > 3599 ) {
				*Dst_p = 3599;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 69:				//�f�o�b�O�A�h���X  shima
//V01l_e			*Dst_p &= 0xfffe;
			*Dst_p &= 0xFFFFE;
			break;

		/* V00m */
		case 70:				//1�`1000
			if( bf > 1000 ) {
				*Dst_p = 1000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}

			if ( ((SEQ_024_SV & BIT_5) == BIT_5) && (CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 99))		// V01n(INS)
			{																						//Ӱ���3�i��
				j = SEQ_PAR_119;
				if (j & 0x07FF)
				{
					degn = &GMN_PAR024;
					for ( i=11 ; i>0 ; i--, j=j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww0 = ww1 = *degn;
							i--;
							j=j>>1;
							degn++;
							break;
						}
					}
					for ( ; i>0 ; i--, j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww1 = *degn;
							break;
						}
					}
					if (ww1 <= *Dst_p)
					{
						*Dst_p = ww1;
					}
					else
					{
						*Dst_p = ww0;
					}
				}
			}

			break;

		/* V00m */
		case 71:				//�ޯ����ߌ��_�ް�ABS�ݒ�(�㉺����������)�ɂ�郊�j�A�Z���T��ʒu�p���X�ύX
			if (SV_RNAORG_SIN) {
				PV_RNAORG_PLS1 = *Dst_p * -1;
			}
			else {
				PV_RNAORG_PLS1 = *Dst_p;
			}
			break;

		/* V00r */
		case 72:				//�␳�l�̉�������
//V01m			if(bf < GMN_PAR001) {
//				*Dst_p = GMN_PAR001;
//			}
			if (SEQ_050_SV & BIT_9)								//�׏d�␳����H
			{
				if(bf < GMN_PAR010) {
					*Dst_p = GMN_PAR010;			//�׏d�␳�Я�
				}
			}
			else
			{
				if(bf < GMN_PAR001) {
					*Dst_p = GMN_PAR001;			//�����␳�Я�
				}
			}
			break;

		/* V01  */
		case 73:				//�i�摬�x�̏������
			if(bf > GMN_PAR002) {
				bf = GMN_PAR002;
				*Dst_p = bf;
			}
			if(bf < GMN_PAR044) {	//��������		2013/02/04 V06o
				bf = GMN_PAR044;
				*Dst_p = bf;
			}
			break;

		/* V01d */
		case 74:				//Ӱ���1�`10�p�x�̏������
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//�~10�{

			bf = motion_dig_limit1(bf, t_no);			//��]Ӱ��݈ʒu�㉺������  V01j(INS)
			bf = motion_dig_limit2(bf, t_no);			//��]Ӱ��݊p�x�㉺�������i�O�i�p�x���傫���������jV01j(INS)

			bf = motion_dig_limit0(bf, t_no);			//��]�^�A����H���̎���Ӱ��݊p�x�㉺������
			*Dst_p = bf;
			break;

		/* V01d */
		case 75:				//Ӱ���1�`10�ʒu�̏������
			wl0 = SV_RNA_STLORK;						//�X�g���[�N�ݒ�(�����_ 3��)
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				*Dst_p = wl0;							//�X�g���[�N�ݒ�
			}

			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit1(wl0, t_no);		//��]Ӱ��݈ʒu�㉺������  V01j(INS)
			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit2(wl0, t_no);		//��]Ӱ��݈ʒu�㉺�������i�O�i�ʒu���傫���������j V01j(INS)

			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit0(wl0, t_no);		//��]�^�A����H���̎���Ӱ��݈ʒu�㉺������

			break;

		/* V01i */
		case 76:				//�ҋ@�_�p�x�̏㉺������
			bf *= 10;
			*Dst_p = bf;								//V01n �޸ޏC��
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*����*/ > GMN_PAR005/*���*/) {
					/* ex : 270(����)�`90(���) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(����)�`90(���) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (SEQ_PAR_201 & BIT_4) {
					SV_TAIKIKAKU_SRV = *Dst_p;
					SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

					if(SEQ_050_SV & BIT_1) {		//���]�@�H
						SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
					}
					SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
				break;

		/* V01i */
		case 77:				//�ҋ@�_�p�x�̏㉺������
			bf *= 10;
			*Dst_p = bf;								//V01n �޸ޏC��
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*����*/ > GMN_PAR005/*���*/) {
					/* ex : 270(����)�`90(���) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(����)�`90(���) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (CB_SYS_PARAM279 != 1) {							// �ҋ@�_�Q����				V06m	2012/09/24
					if (SEQ_PAR_201 & BIT_5) {
						SV_TAIKIKAKU_SRV = *Dst_p;
						SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

						if(SEQ_050_SV & BIT_1) {		//���]�@�H
							SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
						}
						SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
					}
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
			break;

		/* V01i */
		case 78:				//�ҋ@�_�p�x�̏㉺������
			bf *= 10;
			*Dst_p = bf;								//V01n �޸ޏC��
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*����*/ > GMN_PAR005/*���*/) {
					/* ex : 270(����)�`90(���) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(����)�`90(���) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (SEQ_PAR_201 & BIT_6) {
					SV_TAIKIKAKU_SRV = *Dst_p;
					SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//�p�x��mm�ϊ�

					if(SEQ_050_SV & BIT_1) {		//���]�@�H
						SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
					}
					SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//�P�ʐؑ�(mm��mm/INCH)
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
			break;

		/* V01k */
		case 79:				//�ڕW�׏d�ݒ�㉺�������@�iV01m�Ŗ��g�p�ɂ����B�j
//V01m			if(SV_MAXKA2_A24 < bf)				//����i�ő�׏d�j
//			{
//				*Dst_p = SV_MAXKA2_A24;
//			}
//			if(GMN_PAR009 > bf)					//�����i�p�����[�^�j
///			{
//				*Dst_p = GMN_PAR009;
//			}
			break;

		case 80: /* V01l_c */			//�����ڕW�^�׏d�ڕW�@�ݒ�
			if (SEQ_050_SV & BIT_9) {					//�׏d�␳����H
				ww0 = kajyu_chk( Dst_p, bf );
			}
			else {
				ww0 = kagen_chk( Dst_p, bf );
			}
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// �ύX�傫����������������
			}
			SVSW_CHG_FLG |= 0x0008;				//�i�[�׸�
			break;

		case 81: /* V01n */			//Ӱ���3�i�ڑ��x�ݒ�
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
							ww0 = ww1 = *degn;
							i--;
							j=j>>1;
							degn++;
							break;
						}
					}
					for ( ; i>0 ; i--, j=j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww1 = *degn;
							break;
						}
					}
					if (ww1 <= *Dst_p)
					{
						*Dst_p = ww1;
					}
					else
					{
						*Dst_p = ww0;
					}
				}
			}
			break;

		case 82:				//0 �` 15
			if( bf > 15 ) {
				*Dst_p = 15;
			}
			break;

		case 83:				//1 �` 100		//V01w(INS)
			if( bf > 100 ) {
				*Dst_p = 100;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 84:				//�����ڕW����		//V01w(INS)
			ww0 = kagen_chk( Dst_p, bf );
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// �ύX�傫����������������
			}
			SVSW_CHG_FLG |= 0x0008;				//�i�[�׸�
			break;

		case 85:				//�׏d�ڕW����		//V01w(INS)
			ww0 = kajyu_chk( Dst_p, bf );
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// �ύX�傫����������������
			}
			SVSW_CHG_FLG |= 0x0008;				//�i�[�׸�
			break;

		case 86:				//�����␳�̉�������		//V01w(INS)
			if(bf < GMN_PAR001) {
				*Dst_p = GMN_PAR001;			//�����␳�Я�
			}
			break;

		case 87:				//�׏d�␳�̉�������		//V01w(INS)
			if(bf < GMN_PAR010) {
				*Dst_p = GMN_PAR010;			//�׏d�␳�Я�
			}
			break;

		/* COP2 */
		case 88:				//0 �` 180
			if( bf > 359999 ) {
				*Dst_p = 359999;
			}
			break;

		/* COP2 */
		case 89:				//�ޯ����ߌ��_�ް�ABS�ݒ�(�㉺����������)�ɂ�郊�j�A�Z���T��ʒu�p���X�ύX
			if (SV_RNAORG_SIN1) {
				PV_BAKORG_PLS1 = *Dst_p * -1;
			}
			else {
				PV_BAKORG_PLS1 = *Dst_p;
			}
			break;

		/* COP2 */
		case 90:				//�ޯ����ߌ��_�ް�ABS�ݒ�(�㉺����������)�ɂ�郊�j�A�Z���T��ʒu�p���X�ύX
			if (SV_RNAORG_SIN2) {
				PV_BAKORG_PLS2 = *Dst_p * -1;
			}
			else {
				PV_BAKORG_PLS2 = *Dst_p;
			}
			break;

		case 91:				//1 �` 5000		//V01z(INS)
			if( bf > 5000 ) {
				*Dst_p = 5000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 92:				//0 �` 5000		//V01z(INS)
			if( bf > 5000 ) {
				*Dst_p = 5000;
			}
			break;

		case 96:				//�u���[�L�p�x	//V05n(INS)
			if (GMN_PAR017 == 0) {
				if( bf > 359 ) {
					bf = 359;
				}
			}
			else {
				if( bf > GMN_PAR017 ) {
					bf = GMN_PAR017;
				}
			}
			bf *= 10;	//�~10�{
			*Dst_p = bf;
			break;

		case 97:				//�u���[�L�^�C��	//V05n(INS)
			if (GMN_PAR018 == 0) {
				if( bf > 1000 ) {
					*Dst_p = 1000;
				}
			}
			else {
				if( bf > GMN_PAR018 ) {
					*Dst_p = GMN_PAR018;
				}
			}
			break;

		case 98:				//�g�`�X���C�h�ʒu�X�P�[���ő�	//V05o(INS)
			wl0 = SV_RNAPOS_MAXP;						//�@�B���(�����_ 3��)
			wl1 = SV_WAVE_SCL1D;						//���ى���
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;							//�@�B���
			}
			else if( bf < wl1 ) {
				*Dst_p = wl1;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 99:				//�g�`�X���C�h�ʒu�X�P�[���ŏ�	//V05o(INS)
			wl0 = SV_RNAPOS_MINP;						//�@�B���(�����_ 3��)
			wl1 = SV_WAVE_SCL1U;						//���ى���
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}
			if( bf < wl0 ) {
				*Dst_p = wl0;							//�@�B����
			}
			else if( bf > wl1 ) {
				*Dst_p = wl1;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 100:				//�g�`�׏d�X�P�[���ő�			//V05o(INS)
			if( bf > SV_MAXKA2_A24 ) {
				*Dst_p = SV_MAXKA2_A24;
			}
			else if( bf < SV_WAVE_SCL2D ) {
				*Dst_p = SV_WAVE_SCL2D;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 101:				//�g�`�׏d�X�P�[���ŏ�			//V05o(INS)
			if( bf > SV_WAVE_SCL2U ) {
				*Dst_p = SV_WAVE_SCL2U;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 102:				//0 �` 9
			if( bf > 9 ) {
				*Dst_p = 9;
			}
			WAVE_TRND_DTP[1] = 0;				//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 103:				//1 �` 30
			if( bf > 30 ) {
				*Dst_p = 30;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 104:				//�ײ�ޏ�����o�ʒu		//V05o(INS)
			wl0 = SV_DAIHAI_LNG2*100;					//�޲ʲď��(�����_ 1��)
			wl1 = SV_TRDCSR_RNAD;						//�ײ�މ������o
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;							//�޲ʲď��
			}
			else if( bf < wl1 ) {
				*Dst_p = wl1;
			}
			break;

		case 105:				//�ײ�މ������o�ʒu		//V05o(INS)
			wl0 = SV_DAIHAI_LNG1*100;					//�޲ʲĉ���(�����_ 1��)
			wl1 = SV_TRDCSR_RNAU;						//�ײ�ޏ�����o
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
					wl0 *= 10;							//�����_ 3�� -> 4��
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}
			if( bf < wl0 ) {
				*Dst_p = wl0;							//�޲ʲĉ���
			}
			else if( bf > wl1 ) {
				*Dst_p = wl1;
			}
			break;

		case 106:				//0 �` 500
			if( bf > 500 ) {
				*Dst_p = 500;
			}
			break;

		case 107:				//1 �` 999		V05r
			if( bf > 999 ) {
				*Dst_p = 999;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 108:				//�������\�����C���^�[�o���^�C�}	V05r
			if( bf > GMN_PAR039 ) {
				*Dst_p = GMN_PAR039;
			}
			break;

		case 109:				//�O���^�C�}	V05r
			if( bf > GMN_PAR041 ) {
				*Dst_p = GMN_PAR041;
			}
			break;

		case 110:				//�d�̓��j�^�P�ʎ���	V06
			if( bf > 30 ) {
				bf = 30;
				*Dst_p = bf;
			}
			else if( bf < 5 ){
				bf = 5;
				*Dst_p = bf;
			}
			ww0 = bf % 5;
			if ( ww0 != 0 ){
				bf = (bf / 5) * 5;
				*Dst_p = bf;
			}

			break;

		case 111:				//0 �` 65535
			if( bf > 65535 ) {
				*Dst_p = 65535;
			}
			break;

		case 112:				//�����ݸށA����ނ̓d�͏㉺��		//V06b
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 113:				//���ٶ����C��		//V06b
			PV_TOTLC1_B3 = bf;
			break;

		case 114:				//ۯĶ���1�C��		//V06b
			if( SEQ_PAR_107 & BIT_6 ){						//ۯĶ������Z���H
				PV_LOTCT1_B4 = (SV_PUR1SV_B4 - bf);
			}
			else{
				PV_LOTCT1_B4 = bf;
			}
			break;

		case 115:				//ۯĶ���2�C��		//V06b
			if( SEQ_PAR_107 & BIT_6 ){						//ۯĶ������Z���H
				PV_LOTCT2_B41 = (SV_PUR2SV_B41 - bf);
			}
			else{
				PV_LOTCT2_B41 = bf;
			}
			break;

		case 116:				//����ݒ�			//V06n
			if( bf > 3 ) {
				bf = 3;
				*Dst_p = bf;
			}
			else if( bf < 1 ){
				bf = 1;
				*Dst_p = bf;
			}
			break;

		case 117:				//���]Ӱ��P�ݒ���			//V06n
			if( bf > GMN_PAR042 ) {
				bf = GMN_PAR042;
				*Dst_p = bf;
			}
			break;

		case 118:				//���]Ӱ��S�ݒ���			//V06n
			if( bf > GMN_PAR043 ) {
				bf = GMN_PAR043;
				*Dst_p = bf;
			}
			break;

		case 119:				//�@�B����					//V06n
			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//�����_3����
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;

			if (SEQ_PAR_113 & cBIT10) {			//�{�I�t�Z�b�g
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//�|�I�t�Z�b�g
				dat -= ofs;
				if (dat < 1000) {
					dat = 1000;
				}
			}
			SV0_RNAPOS_MINO = dat;		//�@�B����(����l)
			break;

		case 120:				//�@�B���					//V06n
			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//�����_3����
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;

			if (SEQ_PAR_113 & cBIT10) {			//�{�I�t�Z�b�g
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//�|�I�t�Z�b�g
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_RNAPOS_MAXO = dat;		//�@�B���(����l)
			break;

		case 121:				//�_�C�n�C�g����			//V06n
			if( bf > 32767 ) {
				bf = 32767;
				*Dst_p = bf;
			}
			else if(bf < 1) {
				bf = 1;
				*Dst_p = bf;
			}

			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//�����_3����
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;
			dat *= 100;						//�����_3����

			if (SEQ_PAR_113 & cBIT10) {			//�{�I�t�Z�b�g
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//�|�I�t�Z�b�g
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_DAIHAI_LNG1O = dat / 100;		//�_�C�n�C�g����(����l)
			break;

		case 122:				//�_�C�n�C�g���			//V06n
			if( bf > 32767 ) {
				bf = 32767;
				*Dst_p = bf;
			}
			else if(bf < 1) {
				bf = 1;
				*Dst_p = bf;
			}

			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//�����_3����
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;
			dat *= 100;						//�����_3����

			if (SEQ_PAR_113 & cBIT10) {			//�{�I�t�Z�b�g
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//�|�I�t�Z�b�g
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_DAIHAI_LNG2O = dat / 100;		//�_�C�n�C�g���(����l)
			break;
	}
}


/*
********************************************************************************
*  Module Name:		kajyu_chk
*  Function Name:	�׏d�̏㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�����׸�
*
*  �� ��	: Shima		ON:2004-01-10
********************************************************************************
*/
UNs kajyu_chk( UNl *Dst_p, UNl bf )
{
	UNs		ww0, ww1;
	ww0 = 0;

	if(SV_MAXKA2_A24 < bf)						//����i�ő�׏d�j
	{
		*Dst_p = SV_MAXKA2_A24;
		bf = *Dst_p;
	}
	else if(GMN_PAR013 > bf)					//�����i�p�����[�^�j
	{
		*Dst_p = GMN_PAR013;
		bf = *Dst_p;
	}
//V01z	ww1 = SV_KAJYUU_OBJP + GMN_PAR011;
	ww1 = PVP_ARA1_KAJ_T2 + GMN_PAR011;
	if (ww1 < bf )				// �ύX�傫�����H
	{
		ww0 = 0xff;
	}
//V01z	ww1 = SV_KAJYUU_OBJP - GMN_PAR011;
	ww1 = PVP_ARA1_KAJ_T2 - GMN_PAR011;
	if(ww1 & 0x8000)
	{
		ww1 = 0;
	}
	if (ww1 > bf )				// �ύX���������H
	{
		ww0 = 0xff;
	}
	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// �␳�����^�]���H
		{
			ww0 = 0;
			bf = SV_KAJYUU_OBJP;
			*Dst_p = bf;
		}
	}
	if ( bf != SV_KAJYUU_OBJP )					// �ύX�L��H		//V01w(INS)
	{
		PV0_KAJYUHOS_BAK = SV_KAJYUU_OBJP;		// �ύX�L��Ȃ�O��l�Ƃ��ċL��
	}
	return(ww0);
}


/*
********************************************************************************
*  Module Name:		kagen_chk
*  Function Name:	�����̏㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�����׸�
*
*  �� ��	: Shima		ON:2004-01-10
********************************************************************************
*/
UNs kagen_chk( UNl *Dst_p, UNl bf )
{
	UNs		ww0, ww1;
	UNl		wl0, wl1;
	ww0 = 0;

	wl0 = SV_RNAPOS_MINP;					//�@�B����(�����_ 3��)
	wl1 = SV_RNAPOS_MAXP;					//�@�B���(�����_ 3��)
//V01m
//	wl0 /= 10;								//�����_ 3�� -> 2��
//	wl1 /= 10;								//�����_ 3�� -> 2��
//	if( bf > wl1 ) {
//		*Dst_p = wl1;						//�@�B���
//	}
//	else if(bf < wl0) {						//�@�B����
//		*Dst_p = wl0;
//	}
	if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
	}
	else{
		if (SV_POINT_A1 == 1) {
			bf *= 100;							//�����_ 1�� -> 3��
		}
		else {
			bf *= 10;							//�����_ 2�� -> 3��
		}
		*Dst_p = bf;
	}
	if( bf > wl1 ) {
		*Dst_p = wl1;							//�@�B���
		bf = *Dst_p;
	}
	else if(bf < wl0) {							//�@�B����
		*Dst_p = wl0;
		bf = *Dst_p;
	}
	wl1 = SV_DAIHAITO_SRV + (UNl)GMN_PAR012;
	if (wl1 < bf )					// �ύX�傫�����H
	{
		ww0 = 0xff;
	}
	wl1 = SV_DAIHAITO_SRV - (UNl)GMN_PAR012;
	if(wl1 & 0x8000000)
	{
		wl1 = 0;
	}
	if (wl1 > bf )					// �ύX���������H
	{
		ww0 = 0xff;
	}
	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// �␳�����^�]���H
		{
			ww0 = 0;
			bf = SV_DAIHAITO_SRV;
			*Dst_p = bf;
		}
	}
	if ( bf != SV_DAIHAITO_SRV )				// �ύX�L��H		//V01w(INS)
	{
		PV0_KAGENHOS_BAK = SV_DAIHAITO_SRV;		// �ύX�L��Ȃ�O��l�Ƃ��ċL��
	}
	return(ww0);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit0
*  Function Name:	��]�^�A����H���̎���Ӱ��݊p�x�㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-01-10
********************************************************************************
*/
UNl motion_dig_limit0(UNl bf, UNs t_no)
{
	UNl		*posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(bf);					// V01j(ins)
				break;
			case 87:						// �s��2�ڕW�p�x
				degb = &SV_1DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_1DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_2DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 88:						// �s��3�ڕW�p�x
				degb = &SV_2DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_2DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_3DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 89:						// �s��4�ڕW�p�x
				degb = &SV_3DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_3DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_4DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 90:						// �s��5�ڕW�p�x
				degb = &SV_4DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_4DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_5DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 107:						// �s��6�ڕW�p�x
				degb = &SV_5DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_5DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_6DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 108:						// �s��7�ڕW�p�x
				degb = &SV_6DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_6DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_7DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 109:						// �s��8�ڕW�p�x
				degb = &SV_7DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_7DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_8DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 110:						// �s��9�ڕW�p�x
				degb = &SV_8DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_8DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_9DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 111:						// �s��10�ڕW�p�x
				degb = &SV_9DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_9DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_10DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
		}

//V01e		if(*degb >= SV_UPHOLD_DIG)			// �O�i�p�x�͏㏸ΰ��ފp�x�ȏ�H
		if(*degb >= GMN_PAR003)				// �O�i�p�x�͏㏸ΰ��ފp�x�ȏ�H
		{
			if( bf < *degb )				// �O�i�p�x��菬�����H
			{
				bf = *degb;					// �O�i�p�x���Я�
				*posn = *posb;				// �O�i�ʒu���Я�
				MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()�Ŋp�x��mm�͂��Ȃ��ėǂ���I
			}
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit1
*  Function Name:	��]����Ӱ��݈ʒu�㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_dig_limit1(UNl bf, UNs t_no)
{
	if(SEQ_050_SV & BIT_0) {				//��]�H
		if( bf > GMN_PAR007 ) {					// V01j
			bf = GMN_PAR007;					//����l
		}
		else if (bf < GMN_PAR006) {
			bf = GMN_PAR006;					//�����l
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit2
*  Function Name:	��]Ӱ��݊p�x�㉺�������i�O�i�p�x���傫���������j
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_dig_limit2(UNl bf, UNs t_no)
{
	UNl		*posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (GMN_PAR008==1) )		//��]�H �召��r�L���H
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(bf);					// V01j(ins)
				break;
			case 87:						// �s��2�ڕW�p�x
				degb = &SV_1DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_1DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_2DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 88:						// �s��3�ڕW�p�x
				degb = &SV_2DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_2DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_3DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 89:						// �s��4�ڕW�p�x
				degb = &SV_3DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_3DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_4DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 90:						// �s��5�ڕW�p�x
				degb = &SV_4DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_4DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_5DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 107:						// �s��6�ڕW�p�x
				degb = &SV_5DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_5DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_6DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 108:						// �s��7�ڕW�p�x
				degb = &SV_6DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_6DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_7DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 109:						// �s��8�ڕW�p�x
				degb = &SV_7DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_7DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_8DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 110:						// �s��9�ڕW�p�x
				degb = &SV_8DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_8DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_9DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
			case 111:						// �s��10�ڕW�p�x
				degb = &SV_9DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_9DANPOS_SRV;		// �O�i�ڕW�ʒu
				posn = &SV_10DANPOS_SRV;		// ���ݖڕW�ʒu
				break;
		}

		if( bf < *degb )				// �O�i�p�x��菬�����H
		{
			bf = *degb;					// �O�i�p�x���Я�
			*posn = *posb;				// �O�i�ʒu���Я�
			MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()�Ŋp�x��mm�͂��Ȃ��ėǂ���I
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit0
*  Function Name:	��]�^�A����H���̎���Ӱ��݈ʒu�㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-01-10
********************************************************************************
*/
UNl motion_pos_limit0(UNl wl0, UNs t_no)
{
	UNs		i;
	UNl		long_bf, *posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(wl0);				// V01j(ins)
				break;
			case 93:	// �s��2�ڕW�ʒu
				degb = &SV_1DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_1DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_2DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 94:	// �s��3�ڕW�ʒu
				degb = &SV_2DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_2DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_3DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 95:	// �s��4�ڕW�ʒu
				degb = &SV_3DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_3DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_4DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 96:	// �s��5�ڕW�ʒu
				degb = &SV_4DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_4DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_5DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 112:	// �s��6�ڕW�ʒu
				degb = &SV_5DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_5DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_6DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 113:	// �s��7�ڕW�ʒu
				degb = &SV_6DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_6DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_7DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 114:	// �s��8�ڕW�ʒu
				degb = &SV_7DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_7DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_8DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 115:	// �s��9�ڕW�ʒu
				degb = &SV_8DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_8DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_9DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 116:	// �s��10�ڕW�ʒu
				degb = &SV_9DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_9DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_10DANDEG_SRV;	// ���ݖڕW�p�x
				break;
		}

//V01e		if(*degb >= SV_UPHOLD_DIG)			// �O�i�p�x�͏㏸ΰ��ފp�x�ȏ�H
		if(*degb >= GMN_PAR003)					// �O�i�p�x�͏㏸ΰ��ފp�x�ȏ�H
		{
			long_bf = cnv_inch_mm(wl0, 0);		//�P�ʐؑ�(mm/INCH��mm)
			i = *degn;
			i = RnaDigChange1(i, long_bf);		//mm�ϊ����p�x

			if( i < *degb )						// �O�i�p�x��菬�����H
			{
				wl0 = *posb;					// �O�i�ʒu���Я�
				*degn = *degb;					// �O�i�p�x���Я�
				MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()��mm���p�x�͂��Ȃ��ėǂ���I
			}
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit1
*  Function Name:	��]����Ӱ��݈ʒu�㉺������
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_pos_limit1(UNl wl0, UNs t_no)
{
	UNl	long_bf;
	UNs	*deg, i, chg;

	if(SEQ_050_SV & BIT_0) {				//��]�H
		long_bf = cnv_inch_mm(wl0, 0);		//�P�ʐؑ�(mm/INCH��mm)
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
			case 92:	// �s��1�ڕW�ʒu
				deg = &SV_1DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 93:	// �s��2�ڕW�ʒu
				deg = &SV_2DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 94:	// �s��3�ڕW�ʒu
				deg = &SV_3DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 95:	// �s��4�ڕW�ʒu
				deg = &SV_4DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 96:	// �s��5�ڕW�ʒu
				deg = &SV_5DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 112:	// �s��6�ڕW�ʒu
				deg = &SV_6DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 113:	// �s��7�ڕW�ʒu
				deg = &SV_7DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 114:	// �s��8�ڕW�ʒu
				deg = &SV_8DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 115:	// �s��9�ڕW�ʒu
				deg = &SV_9DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
			case 116:	// �s��10�ڕW�ʒu
				deg = &SV_10DANDEG_SRV;		// �O�i�ڕW�p�x
				break;
		}

		i = *deg;
		chg = RnaDigChange1(i, long_bf);		//mm�ϊ����p�x

		if( chg > GMN_PAR007 ) {
			wl0 = DigRnaChange1(GMN_PAR007);	//�p�x��mm�ϊ�
			*deg = GMN_PAR007;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()��mm���p�x�͂��Ȃ��ėǂ���I
		}
		else if (chg < GMN_PAR006) {
			wl0 = DigRnaChange1(GMN_PAR006);	//�p�x��mm�ϊ�
			*deg = GMN_PAR006;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()��mm���p�x�͂��Ȃ��ėǂ���I
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit2
*  Function Name:	��]Ӱ��݈ʒu�㉺�������i�O�i�ʒu���傫���������j
*  Input	: 		�ݒ�l
*  Return	: 		�㉺�����ް�
*  Note		:
*
*  �� ��	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_pos_limit2(UNl wl0, UNs t_no)
{
	UNs		i;
	UNl		long_bf, *posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (GMN_PAR008==1) )		//��]�H �召��r�L���H
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(wl0);				// V01j(ins)
				break;
			case 93:	// �s��2�ڕW�ʒu
				degb = &SV_1DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_1DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_2DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 94:	// �s��3�ڕW�ʒu
				degb = &SV_2DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_2DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_3DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 95:	// �s��4�ڕW�ʒu
				degb = &SV_3DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_3DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_4DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 96:	// �s��5�ڕW�ʒu
				degb = &SV_4DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_4DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_5DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 112:	// �s��6�ڕW�ʒu
				degb = &SV_5DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_5DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_6DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 113:	// �s��7�ڕW�ʒu
				degb = &SV_6DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_6DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_7DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 114:	// �s��8�ڕW�ʒu
				degb = &SV_7DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_7DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_8DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 115:	// �s��9�ڕW�ʒu
				degb = &SV_8DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_8DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_9DANDEG_SRV;		// ���ݖڕW�p�x
				break;
			case 116:	// �s��10�ڕW�ʒu
				degb = &SV_9DANDEG_SRV;		// �O�i�ڕW�p�x
				posb = &SV_9DANPOS_SRV;		// �O�i�ڕW�ʒu
				degn = &SV_10DANDEG_SRV;	// ���ݖڕW�p�x
				break;
		}

		long_bf = cnv_inch_mm(wl0, 0);		//�P�ʐؑ�(mm/INCH��mm)
		i = *degn;
		i = RnaDigChange1(i, long_bf);		//mm�ϊ����p�x

		if( i < *degb )						// �O�i�p�x��菬�����H
		{
			wl0 = *posb;					// �O�i�ʒu���Я�
			*degn = *degb;					// �O�i�p�x���Я�
			MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()��mm���p�x�͂��Ȃ��ėǂ���I
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		Key_sv_tokusyu_chk(���FTOKUSYU_CHK)
*  Function Name:	�ݒ�l�̓��ꏈ��
*  Input	: 		�ݒ�l���ð��ق̔ԍ�
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-20
********************************************************************************
*/
void	Key_sv_tokusyu_chk(UNs t_no)
{

	switch( SV_buff[t_no].YOBI_NO ) {

		case 0:			//�����Ȃ�
		case 1:			//MAX���Z�ް�			(Sit-S�Ȃ�)
		case 3:			//��^����߂U�I���d�l	(Sit-S�Ȃ�)
			break;

		case 2:			//�^�ް��ݒ�ύX
			KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O
			break;

		case 4:			//Ӱ���1�i�ڑ��x		//V06m
			KAT_DATCHG_FLG = 0xff;				//�^�f�[�^�ύX�t���O

			if ( (SEQ_050_SV & BIT_2) && (GMN_PAR021==1) ) {
				SV_TAIKSPD_SRV = SV_1DANSPD_SRV;								//�߂葬�x <- 1�i�ڑ��x
				SVPV_data_disp((UNl)SV_TAIKSPD_SRV, &SV_buff[25], 0, 1);		//�߂葬�x�\��
			}
			break;
	}
}


/*
********************************************************************************
*  Module Name:		dansuu_zero_set
*  Function Name:	�т̒i 00�ݒ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-09-12
********************************************************************************
*/
void	dansuu_zero_set(void)
{
	UNi	cnt, t_no;
	UNs	csr_no, dsp_no, *dst_p;
	UNl	cnv_bf;

	csr_no = CSR_FLG_CNT;
	dsp_no = SV_FLG_CNT;
															//�ݒ�l���e�[�u��
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){

		if( (SV_buff[t_no].SUB_NO == 53) &&					//���ٰ�ݔԍ� ���
			(SV_buff[t_no].CSR_NO == csr_no) &&				//���ٔF���ԍ� ����
			(SV_buff[t_no].DSP_NO != dsp_no) ) {			//���ٔF���ԍ����̈ړ����ʂ��Ⴄ

			dst_p = SV_buff[t_no].DATA_ADR;					//�ް��i�[���ڽ
			*dst_p = 0;
			SVPV_data_disp(00, &SV_buff[t_no], 00, 0x01);	//�ݒ�l�������l �\��
			break;											//�I��
		}
	}
}


/*
********************************************************************************
*  Module Name:		KEY_FILTER
*  Function Name:	KEY�t�B���^����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		KEY��2����ON�΍�AKEY�̓���ON����OFF���ޑ΍�
*
*  �� ��	:FIT)�c�[		ON:2010/07/07	V05q
********************************************************************************
*/
void	KEY_FILTER(void)
{
	UNs	oncnt;
	UNs	kcnt, bcnt, bit, p;
	UNs	KeyWK[4];

	KeyWK[0] = Key_Data_No[0];
	KeyWK[1] = Key_Data_No[1];
	KeyWK[2] = Key_Data_No[2];
	KeyWK[3] = Key_Data_No[3];

	oncnt = 0;
	for(kcnt=4, p=0; kcnt>0; kcnt--, p++)					//Key_Data_WK(4���[�h��)
	{
		for(bcnt=6, bit=0x0001; bcnt>0; bcnt--, bit<<=1)	//6bit���`�F�b�N
		{
			if(KeyWK[p] & bit)
			{
				oncnt++;									//ON���Ă��鐔�𐔂���
			}
		}
	}
	if(oncnt >= 2)					//ON��2�ȏ゠�邩�H
	{
		//2�ȏ㉟����Ă���΋����SOFF
		KeyWK[0] = 0;
		KeyWK[1] = 0;
		KeyWK[2] = 0;
		KeyWK[3] = 0;
	}

	kcnt = KeyWK[0] + KeyWK[1] + KeyWK[2] + KeyWK[3];
	if(kcnt != 0)					//������Ă���KEY�����邩�H
	{
		//�����ɗ���ꍇ�͕K���ǂꂩ1��KEY��������Ă�����
		bcnt = Key_Data_WK[0] + Key_Data_WK[1] + Key_Data_WK[2] + Key_Data_WK[3];
		if( bcnt == 0 )
		{
			/* �O��l���SOFF�����獡��1��ON���ނ�����������OK */
		}
		else if( (KeyWK[0]==Key_Data_WK[0]) &&
				 (KeyWK[1]==Key_Data_WK[1]) &&
				 (KeyWK[2]==Key_Data_WK[2]) &&
				 (KeyWK[3]==Key_Data_WK[3]) )
		{
			/* �O��l�Ɠ���������1��KEY�����������Ă��遁OK */
		}
		else
		{
			/* ��L�ȊO��ON���ނ�OFF���ނ��������������Ƃ����� */
			KeyWK[0] = 0;
			KeyWK[1] = 0;
			KeyWK[2] = 0;
			KeyWK[3] = 0;
		}
	}

	Key_Data_WK[0] = KeyWK[0];
	Key_Data_WK[1] = KeyWK[1];
	Key_Data_WK[2] = KeyWK[2];
	Key_Data_WK[3] = KeyWK[3];
}



/*** END ***/
