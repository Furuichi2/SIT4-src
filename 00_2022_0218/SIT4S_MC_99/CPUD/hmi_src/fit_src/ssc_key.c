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
//#include "dp_cpuab.h"


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	UNl		DigRnaChange1(UNs);
extern	void	ADC_NEXTNAME_SET(void);			/* �`�c�b���^�ԍ����� 			*/
extern	void	ASM_KEY_2_SEQ(void);			//SIT4-MC	2014/08/24

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
extern	UNs		GMN_PAR049;						//���ް۰�ށA۱��ЯĂ̍��ƉE�̏��
extern	UNs		GMN_PAR050;						//���ް۰�ށA۱��ЯĂ̍��v�̏��
extern	UNs		KEY_INF_2_SEQ[2];				//SIT4-MC
extern	UNs		GMN_PAR069;						//�ҋ@���莞�ԏ���ݒ�̏���l
extern	UNs		GMN_PAR075;						//�i�p  �p�x���͏��							2014/09/01
extern	UNs		GMN_PAR076;						//�i�p  ���ԓ��͏��							2014/09/01
extern	UNs		GMN_PAR077;						//�J��Ԃ��񐔏��								2014/09/04
extern	S2b		GMN_PAR070;						//�����[�X�J���I�t�p�x:��],�ӂ肱
extern	S2b		GMN_PAR071;						//�����[�X�J���I�t�p�x����:���]
extern	S2b		GMN_PAR072;						//����J���I���p�x����:
extern	S2b		GMN_PAR073;						//�^�C���O�J���I���p�x����:
extern	S2b		GMN_PAR074;						//�^�C���O�J���I�t�p�x����:
extern	UNs		GMN_PAR080;						//�޲ʲĕ␳����Я�
extern	UNs		GMN_PAR081;						//�׏d�␳����Я�
extern	UNs		GMN_PAR046;						//Ӱ��ݖڕW�׏d���								2015/01/15
extern	UNs		GMN_PAR047;						//Ӱ��ݖڕW�׏d����								2015/01/15
extern	UNs		GMN_PAR083;						//�߂�s�����x�����l							2015/07/10
extern	UNs		GMN_PAR085;						//Ӱ��ݍő�i��									2015/10/21
extern	UNs		SYS_FEED_PAR0010;				//̨��ތ^���ԍ����								2016/03/23
extern	UNs		SYS_FEED_PAR0011;				//̨��ޒᑬ�����x���							2016/03/23
extern	UNs		GMN_PAR096;						//�U���񐔏��									2016/09/20
extern	UNs		GMN_PAR097;						//�U���񐔉���									2016/09/20
extern	UNs		GMN_PAR098;						//�߂�ʔ䗦�ݒ���							2016/09/20
extern	UNs		GMN_PAR100;						//���i�I���p�x����ݒ�							2016/09/30
extern	UNs		GMN_PAR101;						////���[�^���J��OFF�^�C�}���					2016/11/15

//2019-04-20 �׏d�I�[�o���[�h�̐ݒ����ǉ� �ݒ�㉺PARAM<�ő�׏d
extern	UNs		GMN_PAR106;						//2019-04-20 ����۰�ލ��E,۱�Яč��E,�U���̐ݒ���
extern	UNs		GMN_PAR107;						//2019-04-20 ����۰�ލ��v,۱�Яč��v,�U���̐ݒ���

extern	UNs		GMN_PAR111;						//�O���^�C�}����Q	2020/01/30 A01s

/* �萔��` ---------------------------------------------------------- */
#define		E_SUBE1_DN	0x00D0				//�㉺���f�[�^�|�C���^
#define		E_SUBE2_DN	4					//�㉺���f�[�^�|�C���^
#define		E_SUBE3_DN	8					//�㉺���f�[�^�|�C���^
#define		E_SUBE4_DN	12					//�㉺���f�[�^�|�C���^
#define		E_SUBE5_DN	16					//�㉺���f�[�^�|�C���^
#define		E_SUBE6_DN	20					//�㉺���f�[�^�|�C���^
#define		DigMaxMin1(dig)		if(dig<0){dig=0;}else{if(359<dig){dig=359;}}

/* �f�[�^�^��` ------------------------------------------------------ */

/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	Key_mng(void);							//�����͊m��
void	Key_Ten_in(UNs );						//Ten KEY����
void	Key_Ent_sv(void);						//�ݒ�l�̊m��
//2014/08/27	void	Key_sv_limt_chk(UNs, UNl *);			//�ݒ�l�̏㉺���`�F�b�N
UNs		Key_sv_limt_chk(UNs, UNl *);			//�ݒ�l�̏㉺���`�F�b�N
void	Key_sv_tokusyu_chk(UNs);				//�ݒ�l�̓��ꏈ��
void	dansuu_zero_set(void);					//�т̒i ����00�ݒ�
UNs kajyu_chk( UNl *Dst_p, UNl bf );
UNs kagen_chk( UNl *Dst_p, UNl bf );
void	KEY_FILTER(void);						//KEY�t�B���^����	V05q
void	RELEASE_POS_2_AGL_CAL(UNl bf);
void	SEND_POS_2_AGL_CAL(UNl bf);
UNl		CAM_AUTO_LIMIT(UNl bf);
void	REP_CAM_CLR(UNs dan);

S2b		DigAddDigUnit1(S2b dig1,S2b dig2);
S2b		TAIKIAREA_MAXMIN(S2b dig);
U2b		CAM_KOUTEI_SEARCH1(U2b sel,S2b dig);
U2b		CAM_KOUTEI_SEARCH2(U2b sel,S2b dig);

UNl motion_spd_limit1(UNl bf, UNs t_no);//2015/07/10
UNl motion_dig_limit0(UNl, UNs);
UNl motion_dig_limit1(UNl, UNs);
UNl motion_dig_limit2(UNl, UNs);
UNl motion_pos_limit0(UNl, UNs);
UNl motion_pos_limit1(UNl, UNs);
UNl motion_pos_limit2(UNl, UNs);

void	copy_mot100(void);						//���[�V�����f�[�^10�i�̈悩��100�i�̈�ɃR�s�[		2016/03/26


/* �����ϐ���` ------------------------------------------------------ */

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

		ASM_KEY_2_SEQ();						//KEY���𼰹ݽ�o�͗p�ɉ��H	SIT4-MC		2014/08/24
		SEQ_PAR_097 = KEY_INF_2_SEQ[0];
		SEQ_PAR_098 = (SEQ_PAR_098 & 0x00ff) | KEY_INF_2_SEQ[1];

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

	if (SV_buff[t_no].TOK_FLG & BIT_6) {					//�����ݒ��TEN������			2014/03/13
		return;
	}

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
	long	*Dst_Slp, cnv_Sbf;
	short	*Dst_Sp;
	UNs		sv_ref;

	sv_ref = 0;

	t_no = SV_TBL_POS_NOW;

	if (SV_buff[t_no].TOK_FLG & BIT_6) {					//�����ݒ��TEN������			2014/03/13 ----------------------------------

		cnt = (SV_buff[t_no+1].BYTE_NO & 0x000f);			//�ް��i�[����޲Ē�
		if(cnt == 4){										//long(4byte) ?
			Dst_Slp = (long *)SV_buff[t_no+1].DATA_ADR;		//�ް��i�[���ڽ
			cnv_Sbf = *Dst_Slp;
		}
		else{												//short(2byte)
			Dst_Sp = (short *)SV_buff[t_no+1].DATA_ADR;		//�ް��i�[���ڽ
			cnv_Sbf = (long)*Dst_Sp;
		}

		cnv_Sbf *= -1;
		Key_sv_limt_chk(t_no+1, (UNl *)&cnv_Sbf);				//�ݒ�l�̏㉺���`�F�b�N

		Dst_p = SV_buff[t_no].DATA_ADR;						//�ް��i�[���ڽ

		if (cnv_Sbf == 0) {									//2014/08/20
			if ( *Dst_p == 0x2b20 ) {
				*Dst_p = 0x2d20;								//[-]
				cnv_bf = 0x2d20;
			}
			else {
				*Dst_p = 0x2b20;								//[+]
				cnv_bf = 0x2b20;
			}
		}
		else {
			if ( cnv_Sbf >= 0 ) {
				*Dst_p = 0x2b20;								//[+]
				cnv_bf = 0x2b20;
			}
			else {
				*Dst_p = 0x2d20;								//[-]
				cnv_bf = 0x2d20;
			}
		}

		if(cnt == 4){										//long(4byte) ?
			*Dst_Slp = (UNl)cnv_Sbf;						//�ް��i�[
		}
		else{												//short(2byte)
			*Dst_Sp = (UNs)cnv_Sbf;						//�ް��i�[
		}

		FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], 0xff, 0x04);		//�����\��(��ۻ��ڽ����)

		if ( cnv_Sbf < 0 ) {
			cnv_Sbf *= -1;
		}
		cnv_bf = (UNs)cnv_Sbf;
		SVPV_data_disp(cnv_bf, &SV_buff[t_no+1], 0x00, 0x01);	//�ݒ�l�\��(��ۻ��ڽ�L��)

		SV_csr_set();										//�ݒ�l�J�[�\��

		CSR_MOVE_NON = 0xff;

		SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//�i�[�׸�			2016/03/21
	}														//-----------------------------------------------------------------------------


	if(SV_DATA_CHG != 00){
		SV_DATA_CHG = 00;									//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)

		cnv_bf = BCD_HEX4(SV_DISP_BUFF);					//BCD �� HEX �ϊ�

		if (SV_buff[t_no].TOK_FLG & BIT_5) {				//��Βl�\���H			2014/03/14
			Dst_p = SV_buff[t_no-1].DATA_ADR;				//�����i�[���ڽ
			if ( *Dst_p == 0x2d20 ) {						//�ް���ϲŽ
				cnv_bf = (long)cnv_bf * -1;					//�ް���ϲŽ��
			}
		}

//2014/08/27		Key_sv_limt_chk(t_no, &cnv_bf);						//�ݒ�l�̏㉺���`�F�b�N
		sv_ref = Key_sv_limt_chk(t_no, &cnv_bf);						//�ݒ�l�̏㉺���`�F�b�N

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

		if ( SV_buff[t_no].TOK_FLG & BIT_5 ) {				//��Βl�\���H		2014/03/14
			if ( (long)cnv_bf < 0 ) {
				cnv_bf = (long)cnv_bf * -1;
			}
		}

		if ((WINDOW_NO == 12) && (SV_buff[t_no].SUB_NO == 48)) {	// ADC�ï�������ʂ̎��^�ԍ��H		V01j
			flag |= BIT_9;
		}

		if (sv_ref) {										//2014/08/27
			SVdata_disp();
		}
		else {
			SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);		//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)
		}

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

	CSR_MOVE_NON = 0;										//2014/03/14

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
//2014/08/27	void	Key_sv_limt_chk(UNs t_no, UNl *wk_p)
//
//KOMA *wk_p�͐ݒ�l
//Dst_p	�͐ݒ��ް����ڽ(wk_p)
//bf	�͐ݒ��ް�(*wk_p)
//
//

UNs		Key_sv_limt_chk(UNs t_no, UNl *wk_p)
{
	UNl		wl0, wl1, bf, *Dst_p, *Src_p;
	UNl		kagen_mm, jyogen_mm;
	UNs		i , j, ww0, ww1;
//2016/02/24	UNl		*Dst_p_w, long_bf, *posn, *posb;
	UNl		*Dst_lp;
	UNs		*Dst_wp;

	UNs		*degn, *degb;
	S4b		ofs, dat;
	UNs		sv_ref;
	UNs		*spd;

	S2b		wk_S2b;				//2016/03/24

	sv_ref = 0;

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
			if (SLDTUN_RNA_SEL != 0x5a) {
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
			}
			else {												//2014/06/04
				/* �Ʊ���قɂ��ײ�ޒ��� */
				if( SEQ_016_SV & BIT_6 ) {							//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)	2014/12/22
					bf = cnv_inch_mm(bf, 0);
					wl0 = 1;//�����_�R���ݒ�
				}
				else {
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
				}

				//2014-08-11 koma if ( (bf * wl0) > SV_RNAPOS_MAXP ) {
				//2014-08-11 koma 	*Dst_p = SV_RNAPOS_MAXP / wl0;
				//2014-08-11 koma }
				//2014-08-11 koma if ( (bf * wl0) < SV_RNAPOS_MINP ) {
				//2014-08-11 koma 	*Dst_p = SV_RNAPOS_MINP / wl0;
				//2014-08-11 koma }

				//2014-08-11 ���Y�A�i��P�A�i��Q�̏㉺�����I�t�Z�b�g�w�ߍ��݂ōs��
				//2014-08-18 SV0_RNAPOS_MAXO[19]-> SV0_DAIHAI_LNG2O �_�C�n�C�g���[58]
				//2014-08-18 SV0_RNAPOS_MINO[20]-> SV0_DAIHAI_LNG1O �_�C�n�C�g����[57]

				if ( (bf * wl0) > (SV0_DAIHAI_LNG2O*100) ) {//�@�B���[Sno.19]0.001mm->�_�C�n�C�g���[58]0.1mm*100
//2014/12/22					*Dst_p = (SV0_DAIHAI_LNG2O*100) / wl0;
					*Dst_p = cnv_mm_inch(SV0_DAIHAI_LNG2O*100, 0) / wl0;
				}
				if ( (bf * wl0) < (SV0_DAIHAI_LNG1O*100) ) {//�@�B����[Sno.20]0.001mm->�_�C�n�C�g����[57]0.1mm*100
//2014/12/22					*Dst_p = (SV0_DAIHAI_LNG1O*100) / wl0;
					*Dst_p = cnv_mm_inch(SV0_DAIHAI_LNG1O*100, 0) / wl0;
				}
				
			}
			break;

		case 21:				//�I�[�o�[���[�h�i���j�@�l�`�w�`�F�b�N
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��E,۱�Яč��E,�U���̐ݒ���
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKAJ_A24 ) {		//�ő�׏d�i���ȉ��j
						*Dst_p = SV_MAXKAJ_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR049 ) {				//�ő�׏d�i���ȉ��j
					*Dst_p = GMN_PAR049;
				}
			}
			break;

		case 35:				//�Z���׏d  �ő�׏d�i���j�ȉ��@�l�`�w�`�F�b�N
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
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��v,۱�Яč��v,�U���̐ݒ���
					if(GMN_PAR107){
						if(bf > GMN_PAR107){
							bf=GMN_PAR107;
							*Dst_p=bf;
						}
					}
				
					if( bf > SV_MAXKA2_A24 ) {		//�ő�׏d�i���v�ȉ��j
						*Dst_p = SV_MAXKA2_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR050 ) {				//�ő�׏d�i���v�ȉ��j
					*Dst_p = GMN_PAR050;
				}
			}
			break;

		case 36:				//�Z���׏d  �ő�׏d�i���v�j�ȉ��@�l�`�w�`�F�b�N
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
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��E,۱�Яč��E,�U���̐ݒ���
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA3_A24 ) {		//�ő�׏d�i�E�ȉ��j
						*Dst_p = SV_MAXKA3_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR049 ) {				//�ő�׏d�i�E�ȉ��j
					*Dst_p = GMN_PAR049;
				}
			}
			break;

		case 37:				//�Z���׏d  �ő�׏d�i�E�j�ȉ��@�l�`�w�`�F�b�N
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {		//�ő�׏d�i�E�ȉ��j
					*Dst_p = SV_MAXKA3_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 24:				//���A�[���~�b�g�i���j�@�l�`�w�`�F�b�N
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��E,۱�Яč��E,�U���̐ݒ���
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKAJ_A24 ) {			//�ő�׏d�i���ȉ��j
						*Dst_p = SV_MAXKAJ_A24;
					}
//2014/06/03					else if( bf > SV_OVERE1_A26 ) {	//�I�[�o�[���[�h�i���ȉ��j
////////////						*Dst_p = SV_OVERE1_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR049 ) {				//�ő�׏d�i���ȉ��j
					*Dst_p = GMN_PAR049;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE1_A27 ) {			//�ŏ��l�I�[�o�[���[�h�i���ȉ��j
					*Dst_p = SV_OVERE1_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE1_A28 ) {			//�U���I�[�o�[���[�h�i���ȉ��j
					*Dst_p = SV_OVERE1_A28;
				}
			}
			else {
				if( bf > SV_OVERE1_A26 ) {			//�ő�l�I�[�o�[���[�h�i���ȉ��j
					*Dst_p = SV_OVERE1_A26;
				}
			}
			break;

		case 25:				//���A�[���~�b�^�i���v�j�@�l�`�w�`�F�b�N
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��v,۱�Яč��v,�U���̐ݒ���
					if(GMN_PAR107){
						if(bf > GMN_PAR107){
							bf=GMN_PAR107;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA2_A24 ) {			//�ő�׏d�i���v�ȉ��j
						*Dst_p = SV_MAXKA2_A24;
					}
//2014/06/03					else if( bf > SV_OVERE2_A26 ) {		//�I�[�o�[���[�h�i���v�ȉ��j
////////////						*Dst_p = SV_OVERE2_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR050 ) {				//�ő�׏d�i���v�ȉ��j
					*Dst_p = GMN_PAR050;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE2_A27 ) {			//�ŏ��l�I�[�o�[���[�h�i���v�ȉ��j
					*Dst_p = SV_OVERE2_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE2_A28 ) {			//�U���I�[�o�[���[�h�i���v�ȉ��j
					*Dst_p = SV_OVERE2_A28;
				}
			}
			else {
				if( bf > SV_OVERE2_A26 ) {			//�ő�l�I�[�o�[���[�h�i���v�ȉ��j
					*Dst_p = SV_OVERE2_A26;
				}
			}
			break;

		case 26:				//���A�[���~�b�^�i�E�j�@�l�`�w�`�F�b�N
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*�u�ő�l�v�܂��́u�U���v*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ����۰�ލ��E,۱�Яč��E,�U���̐ݒ���
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA3_A24 ) {			//�ő�׏d�i�E�ȉ��j
						*Dst_p = SV_MAXKA3_A24;
					}
//2014/06/03					else if( bf > SV_OVERE3_A26 ) {		//�I�[�o�[���[�h�i�E�ȉ��j
////////////						*Dst_p = SV_OVERE3_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*�u�ŏ��l�v*/
				if( bf > GMN_PAR049 ) {				//�ő�׏d�i�E�ȉ��j
					*Dst_p = GMN_PAR049;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE3_A27 ) {			//�ŏ��l�I�[�o�[���[�h�i�E�ȉ��j
					*Dst_p = SV_OVERE3_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE3_A28 ) {			//�U���I�[�o�[���[�h�i�E�ȉ��j
					*Dst_p = SV_OVERE3_A28;
				}
			}
			else {
				if( bf > SV_OVERE3_A26 ) {			//�ő�l�I�[�o�[���[�h�i�E�ȉ��j
					*Dst_p = SV_OVERE3_A26;
				}
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
					if (SEQ_PAR_151 & cBIT3) {				//�T���v���^�L���H		2014/04/17
						if ( (bf < 201) || (bf > 220) ) {
							*Dst_p = 100;
						}
					}
					else {
						*Dst_p = 100;
					}
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else if ( MLD_100_FLG == 0xbb ) {		//V06n
				if(bf > 200){
					if (SEQ_PAR_151 & cBIT3) {				//�T���v���^�L���H		2014/04/17
						if (bf > 220) {
							*Dst_p = 200;
						}
					}
					else {
						*Dst_p = 200;
					}
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else {
				if(bf > 10){
					if (SEQ_PAR_151 & cBIT3) {				//�T���v���^�L���H		2014/04/17
						if ( (bf < 201) || (bf > 220) ) {
							*Dst_p = 10;
						}
					}
					else {
						*Dst_p = 10;
					}
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
			else if ( MLD_100_FLG == 0xbb ) {		//2016/04/22
				if(bf > 200){
					*Dst_p = 200;
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
#if (mot100_test == 1)								//2015/10/21
			wl0 = 10;
			if (GMN_PAR085) {						//Ӱ��ݍő�i��
				wl0 = GMN_PAR085;
			}
#else
			wl0 = 5;
			if (SEQ_024_SV & BIT_3) {				//10�i�d�l�L��		/* V01d */
				wl0 = 10;
			}
#endif
			if( bf > wl0 ) {
				*Dst_p = wl0;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
#if (mot100_test == 1)
#else
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
#endif
			SV0_MOT_FIX = 0;							//��葬�x�u���O�N���A			2014/10/09
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
			REP_CAM_CLR(bf);
			break;

		case 54:				//0 �` ���]�ݒ�s�͈́@(�ݒ�l���~10�{)
			bf *= 10;									//�~10�{
			if( bf > SV_DNAREA_JUDG ) {//���]�A�ӂ肱����
				bf = SV_DNAREA_JUDG;
			}
			if( SV_buff[t_no].GRP_NO == 85 ) {				//����p�̐ݒ�		V06k (INS)
				if( SEQ_050_SV & BIT_1 ) {					//���]���̏���p�̍ő�l���~�b�g		V05 (INS)
					if( bf > GMN_PAR015 ) {//�ő�
						bf = GMN_PAR015;
					}

					//2014-08-11 koma ���]���̏���̍ŏ��l���~�b�g�ǉ� �������40�㎀�_�͈�
					if(bf<SV_UPAREA_JUDG+10){	//�ŏ�+1.0�x
						bf=SV_UPAREA_JUDG+10;	//�ŏ�+1.0�x
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
//2014/12/17
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
////
////			if( bf > wl0 ) {
////				*Dst_p = wl0;
////				bf = wl0;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//�X�g���[�N�ݒ�mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}


			if( SEQ_050_SV & BIT_1 ) {					//���]���̏���ʒu�̍ő�l		V05 (INS)
				wl0 = DigRnaChange1(GMN_PAR015);		//�p�x��mm�ϊ�
				wl0 = wl0-SV_NEG_OFS_LNG;				//2014-08-11 koma add�s�
				if( bf < wl0 ) {
//2014/12/17
////					*Dst_p = wl0;
////					bf = wl0;
					bf = wl0;								//�X�g���[�N�ݒ�mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}

				//2014-08-11 koma ���]���̏���̍ŏ��l���~�b�g�ǉ� �������40�㎀�_�͈�
				wl0 = DigRnaChange1(SV_UPAREA_JUDG+10);//�ŏ�+1.0�x
				wl0 = wl0-SV_NEG_OFS_LNG;				//
				if( bf > wl0 ) {
//2014/12/17
////					*Dst_p = wl0;
////					bf = wl0;
					bf = wl0;								//�X�g���[�N�ݒ�mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}
			}
			else if ( SEQ_050_SV & BIT_2 ) {			//�U�q�̏���ʒu		V06f (INS)
				wl0 = DigRnaChange1(GMN_PAR016);		//�p�x��mm�ϊ�
				if( bf < wl0 ) {
//2014/12/17
////					*Dst_p = wl0;						//�ŏ����~�b�g
////					bf = wl0;
					bf = wl0;								//�X�g���[�N�ݒ�mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}
				wl0 = DigRnaChange1(GMN_PAR019);		//�p�x��mm�ϊ�
				if( bf > wl0 ) {
//2014/12/17
////					*Dst_p = wl0;						//�ő僊�~�b�g
////					bf = wl0;
					bf = wl0;								//�X�g���[�N�ݒ�mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
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

//2015/07/10	���[�V�����C���^�[���b�N�d�l
			bf = *Dst_p;
			*Dst_p = motion_spd_limit1(bf, t_no);					//�ŏI�s���i�߂�s���̑O�j�̑��x��������

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
				if(bf > GMN_PAR081) {				//2014/09/12
					bf = GMN_PAR081;
					*Dst_p = GMN_PAR081;			//�׏d�␳����Я�
				}
			}
			else
			{
				bf = cnv_uinch_um(bf);				//uinch -> um			2014/12/23
				if(bf < GMN_PAR001) {
					bf = GMN_PAR001;
//2014/12/23					*Dst_p = GMN_PAR001;			//�����␳�����Я�
					*Dst_p = cnv_um_uinch(GMN_PAR001);			//�����␳�����Я�
				}
				if(bf > GMN_PAR080) {				//2014/09/11
					bf = GMN_PAR080;
//2014/12/23					*Dst_p = GMN_PAR080;			//�����␳����Я�
					*Dst_p = cnv_um_uinch(GMN_PAR080);			//�����␳����Я�
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
//2014/12/17
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
////
////			if( bf > wl0 ) {
////				*Dst_p = wl0;							//�X�g���[�N�ݒ�
////			}

			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//�X�g���[�N�ݒ�mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
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
			bf = cnv_uinch_um(bf);				//uinch -> um			2014/12/23
			if(bf < GMN_PAR001) {				//um�Ŕ�r
				bf = GMN_PAR001;
//2014/12/23				*Dst_p = GMN_PAR001;			//�����␳�����Я�
				*Dst_p = cnv_um_uinch(GMN_PAR001);			//�����␳�����Я�
			}
			if(bf > GMN_PAR080) {				//2014/09/11
				bf = GMN_PAR080;
//2014/12/23				*Dst_p = GMN_PAR080;			//�����␳����Я�
				*Dst_p = cnv_um_uinch(GMN_PAR080);			//�����␳����Я�
			}
			break;

		case 87:				//�׏d�␳�̉�������		//V01w(INS)
			if(bf < GMN_PAR010) {
				*Dst_p = GMN_PAR010;			//�׏d�␳�Я�
			}
			if(bf > GMN_PAR081) {				//2014/09/12
				bf = GMN_PAR081;
				*Dst_p = GMN_PAR081;			//�׏d�␳����Я�
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
//2014-08-11 koma			wl0 = SV_RNAPOS_MAXP;						//�@�B���(�����_ 3��)
			wl0 = SV0_RNAPOS_MAXO;						//�@�B���(�����_ 3��)	mm
			wl1 = SV_WAVE_SCL1D;						//�T���v�����O�g�`�̽��ى���	mm/inch

			if( GAMEN_NO == 10 ) {						//�g�����h�g�`���							2015/05/12
				wl1 = SV_WAVE_SCL3D;					//�g�����h�g�`�̽��ى���	mm/inch
			}

//2014/12/18
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
////			if( bf > wl0 ) {
////				*Dst_p = wl0;							//�@�B���
////			}
////			else if( bf < wl1 ) {
////				*Dst_p = wl1;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {							//��������imm�Ŕ�r�j
				bf = wl0;
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			if( *Dst_p < wl1 ) {						//���������imm/inch�Ŕ�r�j
				*Dst_p = wl1;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 99:				//�g�`�X���C�h�ʒu�X�P�[���ŏ�	//V05o(INS)
//2014-08-11 KOMA			wl0 = SV_RNAPOS_MINP;		//�@�B���(�����_ 3��)
			wl0 = SV0_RNAPOS_MINO;						//���ى��� koma
			wl1 = SV_WAVE_SCL1U;						//�T���v�����O�g�`�̽��ُ��

			if( GAMEN_NO == 10 ) {						//�g�����h�g�`���							2015/05/12
				wl1 = SV_WAVE_SCL3U;					//�g�����h�g�`�̽��ُ��	mm/inch
			}

//2014/12/18
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
////			if( bf < wl0 ) {
////				*Dst_p = wl0;							//�@�B����
////			}
////			else if( bf > wl1 ) {
////				*Dst_p = wl1;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf < wl0 ) {							//���������imm�Ŕ�r�j
				bf = wl0;
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			if( *Dst_p > wl1 ) {						//��������imm/inch�Ŕ�r�j
				*Dst_p = wl1;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 100:				//�g�`�׏d�X�P�[���ő�			//V05o(INS)
//2015/05/15
////			if( (short)bf > (short)SV_MAXKA2_A24 ) {			//2014/03/14 �����L���
////				*Dst_p = SV_MAXKA2_A24;
////			}
////			else if( (short)bf <= (short)SV_WAVE_SCL2D ) {
////				*Dst_p = (short)SV_WAVE_SCL2D + 1;
////			}
			if( (long)bf > (short)SV_MAXKA2_A24 ) {
				bf = SV_MAXKA2_A24;
				*Dst_p = bf;
			}
			else if( (long)bf <= (short)SV_WAVE_SCL2D ) {
				bf = (short)SV_WAVE_SCL2D + 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 101:				//�g�`�׏d�X�P�[���ŏ�			//V05o(INS)
//2015/05/15
////			if( (short)bf >= (short)SV_WAVE_SCL2U ) {					//2014/03/14 �����L���
////				*Dst_p = (short)SV_WAVE_SCL2U - 1;
////			}
			if( (long)bf < -32767 ) {
				bf = -32767;
				*Dst_p = bf;
			}
			if( (long)bf >= (short)SV_WAVE_SCL2U ) {
				bf = (short)SV_WAVE_SCL2U - 1;
				*Dst_p = bf;
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
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

//2014/12/22
////			if( bf > wl0 ) {								//mm�Ŕ�r
////				*Dst_p = wl0;							//�޲ʲď��
////			}
////			else if( bf < wl1 ) {
////				*Dst_p = wl1;
////			}
			if( bf > wl0 ) {								//mm�Ŕ�r
				bf = wl0;
				*Dst_p = cnv_mm_inch(wl0,0);				//�޲ʲď��
			}
			if( *Dst_p < wl1 ) {							//mm/inch�Ŕ�r
				*Dst_p = wl1;
			}

			break;

		case 105:				//�ײ�މ������o�ʒu		//V05o(INS)
			wl0 = SV_DAIHAI_LNG1*100;					//�޲ʲĉ���(�����_ 1��)
			wl1 = SV_TRDCSR_RNAU;						//�ײ�ޏ�����o
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

//2014/12/22
////			if( bf < wl0 ) {
////				*Dst_p = wl0;							//�޲ʲĉ���
////			}
////			else if( bf > wl1 ) {
////				*Dst_p = wl1;
////			}
			if( bf < wl0 ) {							//mm�Ŕ�r
				bf = wl0;
				*Dst_p = cnv_mm_inch(wl0,0);			//�޲ʲĉ���
			}
			if( *Dst_p > wl1 ) {						//mm/inch�Ŕ�r
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
			//2020-01-30 A01s���ݽ�ł̊O����Ϗ���ؑ� GMN_PAR111�ǉ� <=>GMN_PAR041
			if(SEQ_PAR_154&BIT_0){
				if( bf > GMN_PAR111 ) {
					*Dst_p = GMN_PAR111;
				}
			}else{
				if( bf > GMN_PAR041 ) {
					*Dst_p = GMN_PAR041;
				}
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
			if( (long)bf <= (long)SV_WAVE_SCL5D ) {					//�����L���		2014/03/14
				bf = (long)SV_WAVE_SCL5D + 1;
			}
			*Dst_p = bf;

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

		case 123:				//Ӱ��ݖڕW�׏d�̏㉺��		2015/01/15
			if( bf > GMN_PAR046 ) {
				bf = GMN_PAR046;
				*Dst_p = bf;
			}
			else if(bf < GMN_PAR047) {
				bf = GMN_PAR047;
				*Dst_p = bf;
			}
			break;

		case 124:				//����ޔg�`�׏d�X�P�[���ő�		//2014/03/14
//2015/05/12
////			if( (short)bf > (short)SV_MAXKA2_A24 ) {
////				*Dst_p = SV_MAXKA2_A24;
////			}
////			else if( (short)bf <= (short)SV_WAVE_SCL4D ) {
////				*Dst_p = (short)SV_WAVE_SCL4D + 1;
////			}
			if( (long)bf > (short)SV_MAXKA2_A24 ) {
				bf = SV_MAXKA2_A24;
				*Dst_p = bf;
			}
			else if( (long)bf <= (short)SV_WAVE_SCL4D ) {
				bf = (short)SV_WAVE_SCL4D + 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 125:				//����ޔg�`�׏d�X�P�[���ŏ�		//2014/03/14
//2015/05/12
////			if( (short)bf >= (short)SV_WAVE_SCL4U ) {
////				*Dst_p = (short)SV_WAVE_SCL4U - 1;
////			}
			if( (long)bf < -32767 ) {
				bf = -32767;
				*Dst_p = bf;
			}
			if( (long)bf >= (short)SV_WAVE_SCL4U ) {
				bf = (short)SV_WAVE_SCL4U - 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 126:				//�����ݸނ̓d�͉���		//2014/03/14
			if( (long)bf >= (long)SV_WAVE_SCL5U ) {
				bf = (long)SV_WAVE_SCL5U - 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 127:				//����ޔg�`�̓d�͏��		//2014/03/14
			if( (long)bf <= (long)SV_WAVE_SCL6D ) {
				bf = (long)SV_WAVE_SCL6D + 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 128:				//����ޔg�`�̓d�͉���		//2014/03/14
			if( (long)bf >= (long)SV_WAVE_SCL6U ) {
				bf = (long)SV_WAVE_SCL6U - 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��(�ĕ`�悳����)
			break;

		case 129:				//�яo�͎������Z �����[�X �ʒu					2014/08/26
			wl0 = SV_TAIKIPOS_SRV;						//����ʒu(mm/inch)
//2014/12/23
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

			PV0_CAMATCAL_FLG |= cBIT0;					//�����[�X�������̓t���O�n�m			2014/09/12

//2014/09/01 �ړ�
////			RELEASE_POS_2_AGL_CAL(bf);					//�������񉉎Z
			break;

		case 130:				//�яo�͎������Z �����[�X �J��No.				2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 131:				//�яo�͎������Z ���� �ʒu						2014/08/26
			wl0 = SV_TAIKIPOS_SRV;						//����ʒu(mm/inch)
//2014/12/23
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

			PV0_CAMATCAL_FLG |= cBIT1;					//���荂�����̓t���O�n�m			2014/09/12

//2014/09/01 �ړ�
////			SEND_POS_2_AGL_CAL(bf);					//�������񉉎Z
			break;

		case 132:				//�яo�͎������Z ���� �J��No.					2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 133:				//�яo�͎������Z ���ݸ� �J��No.					2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 134:				//0 �` �s����+1(�߂�s��)						2014/08/26
//2014/08/30
//			if (bf == 0) {
//				bf = 1;
//				*Dst_p = bf;
//			}
			if (bf > (SV_DANSUU_SRV+1)) {
				bf = SV_DANSUU_SRV+1;
				*Dst_p = bf;
			}
			break;

		case 135:				//�����E�ʒu  �p�x							2014/08/26
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//�~10�{
			*Dst_p = bf;
//2014/12/22			bf = DigRnaChange1(bf);	//�p�x��mm�ϊ�
			bf = cnv_mm_inch(DigRnaChange1(bf),0);	//�p�x��mm�ϊ���mm/inch
			SV_INTLIM_POS = bf;
			sv_ref = 0xff;
			break;

		case 136:				//�����E�ʒu  �ʒu							2014/08/26
//2014/09/01
////			if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////				bf *= 10;							//�����_ 2�� -> 3��
////				*Dst_p = bf;
////			}

			wl0 = SV_TAIKIPOS_SRV;						//����ʒu(�����_ 3��)

//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/08/30			bf = RnaDigChange1(SV_INTLIM_AGL, bf);		//mm�ϊ����p�x
//2014/12/22			bf = RnaDigChange1(SV_DNAREA_JUDG, bf);		//mm�ϊ����p�x
			bf = RnaDigChange1(SV_DNAREA_JUDG, cnv_inch_mm(bf,0));		//mm�ϊ����p�x
			SV_INTLIM_AGL = bf;
			sv_ref = 0xff;
			break;

		case 137:				//�ҋ@���莞�ԏ��								2014/08/30
			if( bf > GMN_PAR069 ) {
				bf = GMN_PAR069;
				*Dst_p = bf;
			}
			break;

		case 138:				//�i�p  �p�x���͏��							2014/09/01
			if( bf > GMN_PAR075 ) {
				bf = GMN_PAR075;
				*Dst_p = bf;
			}
			break;

		case 139:				//�i�p  ���ԓ��͏��							2014/09/01
			if( bf > GMN_PAR076 ) {
				bf = GMN_PAR076;
				*Dst_p = bf;
			}
			break;

		case 140:				//1 �` 500										2014/09/03
			if( bf > 500 ) {
				*Dst_p = 500;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 141:				//���s�[�g�J�n�s�� �P �` �ő�s��				2014/09/04
			if (bf == 0) {
				bf = 1;
				*Dst_p = bf;
			}
			if (bf > SV_DANSUU_SRV) {
				bf = SV_DANSUU_SRV;
				*Dst_p = bf;
			}
			break;

		case 142:				//���s�[�g�I���s��	�J�n�s�� �` �ő�s��		2014/09/04
			if (bf < SV_MOTREP_STGS) {
				bf = SV_MOTREP_STGS;
				*Dst_p = bf;
			}
			if (bf > SV_DANSUU_SRV) {
				bf = SV_DANSUU_SRV;
				*Dst_p = bf;
			}
			break;

		case 143:				// �` �J��Ԃ��񐔏��							2014/09/04
			if (bf > GMN_PAR077) {
				bf = GMN_PAR077;
				*Dst_p = bf;
			}
			break;

		case 144:				// ���̈�J�n�p�x								2014/09/11
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//�~10�{
			*Dst_p = bf;
//2014/12/22			SV0_FIXARA_POSS = DigRnaChange1(bf);		//�p�x��mm�ϊ�
			SV0_FIXARA_POSS = cnv_mm_inch(DigRnaChange1(bf),0);		//�p�x��mm�ϊ���mm/inch
			ww0 = CAM_KOUTEI_SEARCH2(0, bf/10);			//�p�x���s��No.
			if (ww0 <= 1) {
				/* �P�i�ڂ��O�̑��x�͖����H */
				// 2014-10-06 KOMAPV0_FIXBF_SPD = 0;						//��葬�x�J�n�O���x
				PV0_FIXBF_SPD = SV_1DANSPD_SRV;		//��葬�x�J�n�O���x:�P�i�ڑ��x2014-10-06 koma
			}
			else {
				/* �Q�i�ڂ���O�̑��x�����݂���H */
				spd = &SV_1DANSPD_SRV;
				PV0_FIXBF_SPD = spd[ww0-2];				//��葬�x�J�n�O���x
			}
			sv_ref = 0xff;
			break;

		case 145:				// ���̈�J�n�ʒu								2014/09/11
			wl0 = SV_TAIKIPOS_SRV;						//����ʒu(�����_ 3��)
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/12/22			bf = RnaDigChange1(SV0_FIXARA_AGLS, bf);		//mm�ϊ����p�x
			bf = RnaDigChange1(SV0_FIXARA_AGLS, cnv_inch_mm(bf,0));		//mm�ϊ����p�x
			SV0_FIXARA_AGLS = bf;
			sv_ref = 0xff;
			break;

		case 146:				// ���̈�I���p�x								2014/09/11
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//�~10�{
			*Dst_p = bf;
//2014/12/22			SV0_FIXARA_POSE = DigRnaChange1(bf);		//�p�x��mm�ϊ�
			SV0_FIXARA_POSE = cnv_mm_inch(DigRnaChange1(bf),0);		//�p�x��mm�ϊ���mm/inch
			sv_ref = 0xff;
			break;

		case 147:				// ���̈�I���ʒu								2014/09/11
			wl0 = SV_TAIKIPOS_SRV;						//����ʒu(�����_ 3��)
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//�P�� �����x(1:�����x)
////					wl0 *= 10;							//�����_ 3�� -> 4��
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
////					bf *= 10;							//�����_ 2�� -> 3��
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/12/22			bf = RnaDigChange1(SV0_FIXARA_AGLE, bf);		//mm�ϊ����p�x
			bf = RnaDigChange1(SV0_FIXARA_AGLE, cnv_inch_mm(bf,0));		//mm�ϊ����p�x
			SV0_FIXARA_AGLE = bf;
			sv_ref = 0xff;
			break;

		case 148:				// �ʒu���ߊ����͈�								2014/12/22
			if (bf > 32767) {
				bf = 32767;
				*Dst_p = bf;
			}
			if( (SEQ_016_SV & BIT_6) == 0) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0) {			//�P�� �����x(1:�����x)
					*Dst_p *= 10;
				}
			}
			break;

		case 149:				// �@�B���_����						2016/02/24
			if (SV0_RNAORG_ENB1 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 150:				// �@��								2016/02/24
			if (SV0_ORGCAL_ENB2 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 151:				// �@��								2016/02/24
			if (SV0_ORGCAL_ENB1 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//�ް��i�[���ڽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 152:				// �p�x�l�ؑ�						2016/02/24
			if (SV0_MACINE_ENB1 != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( bf > 0xffff ) {
					*Dst_p = 0xffff;
				}

				if (bf == 9870) {								//�f�[�^10�i��100�i�Ή�		2016/03/26
					copy_mot100();								//���[�V�����f�[�^10�i�̈悩��100�i�̈�ɃR�s�[
					*Dst_p = 0;
				}
			}
			break;

		case 153:				// �ő�c							2016/02/24
			if (SV0_MAXHIZ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			else {
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
			}
			break;

		case 154:				// �ő�׏d							2016/02/24
			if (SV0_MAXKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			break;

		case 155:				//�Z���׏d  �ő�׏d�i���j�ȉ��@�l�`�w�`�F�b�N		2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKAJ_A24 ) {		//�ő�׏d�i���ȉ��j
						*Dst_p = SV_MAXKAJ_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 156:				//�Z���׏d  �ő�׏d�i���v�j�ȉ��@�l�`�w�`�F�b�N	2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKA2_A24 ) {		//�ő�׏d�i���v�ȉ��j
						*Dst_p = SV_MAXKA2_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 157:				//�Z���׏d  �ő�׏d�i�E�j�ȉ��@�l�`�w�`�F�b�N		2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKA3_A24 ) {		//�ő�׏d�i�E�ȉ��j
						*Dst_p = SV_MAXKA3_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 158:				//���x���t�B�[�_�^���ԍ�			2016/03/23
			if (bf < 1) {
				bf = 1;
			}
			if (bf > SYS_FEED_PAR0010) {
				bf = SYS_FEED_PAR0010;
			}
			*Dst_p = bf;

			Get_LFEED_SYS_PARA(bf);			//���x���t�B�[�_��ROM�p���擾
			break;

		case 159:				//���x���t�B�[�_�����ʓ���			2016/03/23
			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSIDN];		//���� *.**mm
			if (SEQ_016_SV & BIT_6) {								//�d�l�ݒ�No.7  inch�I��
				//�����l��inch��
				if (dat < 0) {										//�����}�C�i�X�H
					dat *= -1;										//��Βl��
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf < dat) {
				bf = dat;
			}

			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSIUP];		//��� *.**mm
			if (SEQ_016_SV & BIT_6) {								//�d�l�ݒ�No.7  inch�I��
				//����l��inch��
				if (dat < 0) {										//�����}�C�i�X�H
					dat *= -1;										//��Βl��
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf > dat) {
				bf = dat;
			}

			*Dst_p = bf;
			break;

		case 160:				//���x���t�B�[�_�����ʏo��			2016/03/23
			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSODN];		//���� *.**mm
			if (SEQ_016_SV & BIT_6) {								//�d�l�ݒ�No.7  inch�I��
				//�����l��inch��
				if (dat < 0) {										//�����}�C�i�X�H
					dat *= -1;										//��Βl��
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf < dat) {
				bf = dat;
			}

			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSOUP];		//��� *.**mm
			if (SEQ_016_SV & BIT_6) {								//�d�l�ݒ�No.7  inch�I��
				//����l��inch��
				if (dat < 0) {										//����}�C�i�X�H
					dat *= -1;										//��Βl��
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf > dat) {
				bf = dat;
			}

			*Dst_p = bf;
			break;

		case 161:				//���x���t�B�[�_�ᑬ�����葬�x		2016/03/23
			if (bf > SYS_FEED_PAR0011) {
				*Dst_p = SYS_FEED_PAR0011;
			}
			break;

		case 162:				//���x���t�B�[�_����ʒu�^�����[�X�ʒu		2016/03/23
			wl0 = SV_RNA_STLORK;						//�X�g���[�N�ݒ�(�����_ 3��)

			if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//�P�� �����x(1:�����x)
					bf *= 10;							//�����_ 2�� -> 3��
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//�X�g���[�N�ݒ�mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			break;

		case 163:				//���i���[�V�����ݒ����p					2016/09/20
//2016/10/04
////			if ( (SEQ_PAR_151 & BIT_6) == 0 ) {			//�U�q����
////				bf = 0;
////			}
////			else {
////				bf *= 10;								//�~10�{
////				if (bf > GMN_PAR016) {					//�U�q�̏���p����ݒ�
////					bf = GMN_PAR016;
////				}
////				if (bf < GMN_PAR019) {					//�U�q�̏���p�����ݒ�
////					bf = GMN_PAR019;
////				}
////			}
			bf *= 10;								//�~10�{
			if (bf > GMN_PAR016) {					//�U�q�̏���p����ݒ�
				bf = GMN_PAR016;
			}
			*Dst_p = bf;
			break;

		case 164:				//���i���[�V�����ݒ����ʒu				2016/09/20
//2016/10/04
////			if ( (SEQ_PAR_151 & BIT_6) == 0 ) {					//�U�q����
////				bf = DigRnaChange1(0);							//0�x��mm�ϊ�
////			}
////			else {
////				bf *= 10;
////				wl0 = DigRnaChange1(GMN_PAR016);				//�p�x��mm�ϊ�
////				if( bf < wl0 ) {
////					bf = wl0;									//
////				}
////				wl0 = DigRnaChange1(GMN_PAR019);				//�p�x��mm�ϊ�
////				if( bf > wl0 ) {
////					bf = wl0;									//
////				}
////			}
			bf *= 10;
			wl0 = DigRnaChange1(GMN_PAR016);				//�p�x��mm�ϊ�
			if( bf < wl0 ) {
				bf = wl0;									//
			}
			wl0 = DigRnaChange1(0);							//�p�x��mm�ϊ�
			if( bf > wl0 ) {
				bf = wl0;									//
			}
			*Dst_p = bf;
			break;

		case 165:				//���i���[�V�����ݒ葽�i�J�n�p�x			2016/09/20
			bf *= 10;								//�~10�{
//2016/10/04
////			if (bf > GMN_PAR016) {					//�U�q�̏���p����ݒ�
////				bf = GMN_PAR016;
////			}
			if (bf > GMN_PAR100) {					//����ݒ�
				bf = GMN_PAR100;
			}
			if (bf < SV_TAIKIKAKU_SRV) {			//����p�Ń��~�b�g
				bf = SV_TAIKIKAKU_SRV;
			}
			*Dst_p = bf;
			break;

		case 166:				//���i���[�V�����ݒ葽�i�J�n�ʒu			2016/09/20
			bf *= 10;									//�����_ 2�� -> 3��
//2016/10/04
////			wl0 = DigRnaChange1(GMN_PAR016);				//�p�x��mm�ϊ�
			wl0 = DigRnaChange1(GMN_PAR100);				//�p�x��mm�ϊ�
			if( bf < wl0 ) {
				bf = wl0;									//
			}
			if( bf > SV_TAIKIPOS_SRV ) {
				bf = SV_TAIKIPOS_SRV;						//
			}
			*Dst_p = bf;
			break;

		case 167:				//���i���[�V�����ݒ葽�i�I���p�x			2016/09/30
			bf *= 10;								//�~10�{
//2016/09/30
////			if (bf > GMN_PAR016) {					//�U�q�̏���p����ݒ�
////				bf = GMN_PAR016;
////			}
			if (bf > GMN_PAR100) {					//����ݒ�
				bf = GMN_PAR100;
			}
			if (bf < SV_TAIKIKAKU_SRV) {			//����p�Ń��~�b�g
				bf = SV_TAIKIKAKU_SRV;
			}
			if (bf < SV_MSSTAT_AGL) {				//���i�J�n�p�x�Ń��~�b�g	2016/10/04
				bf = SV_MSSTAT_AGL;
			}
			*Dst_p = bf;
			break;

		case 168:				//���i���[�V�����ݒ葽�i�I���ʒu			2016/09/30
			bf *= 10;									//�����_ 2�� -> 3��
//2016/09/30
////			wl0 = DigRnaChange1(GMN_PAR016);			//�p�x��mm�ϊ�
			wl0 = DigRnaChange1(GMN_PAR100);			//�p�x��mm�ϊ�
			if( bf < wl0 ) {
				bf = wl0;								//
			}
			if( bf > SV_TAIKIPOS_SRV ) {
				bf = SV_TAIKIPOS_SRV;					//
			}
			if( bf > SV_MSSTAT_POS ) {					//���i�J�n�ʒu�Ń��~�b�g	2016/10/04
				bf = SV_MSSTAT_POS;						//
			}
			*Dst_p = bf;
			break;

		case 169:				//���i���[�V�����ݒ葽�i��				2016/09/20
			if (bf > GMN_PAR096) {
				bf = GMN_PAR096;
			}
			if (bf < GMN_PAR097) {
				bf = GMN_PAR097;
			}
			*Dst_p = bf;
			break;

		case 170:				//���i���[�V�����ݒ�߂��ʔ䗦				2016/09/20
			if (bf > GMN_PAR098) {
				bf = GMN_PAR098;
			}
			*Dst_p = bf;
			break;

		case 171:				//���i���[�V�����ݒ����x				2016/09/20
			if( bf > 1000 ) {
				bf = 1000;
			}
			else if(bf < 1) {
				bf = 1;
			}
			*Dst_p = bf;
			break;

		case 172:				//���[�^���J��OFF�^�C�}						2016/11/15
			if (bf > GMN_PAR101) {
				bf = GMN_PAR101;
			}
			*Dst_p = bf;
			break;

	}

	return(sv_ref);
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
////	wl0 /= 10;								//�����_ 3�� -> 2��
////	wl1 /= 10;								//�����_ 3�� -> 2��
////	if( bf > wl1 ) {
////		*Dst_p = wl1;						//�@�B���
////	}
////	else if(bf < wl0) {						//�@�B����
////		*Dst_p = wl0;
////	}
	if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		bf = cnv_inch_mm(bf, 0);				//2014/12/17
	}
	else{
		if (SV_POINT_A1 == 0) {					//2014/12/23
			bf *= 1000;							//�����_ 0�� -> 3���i�����f�[�^�͏����_�ȉ�3���j
		}
		else if (SV_POINT_A1 == 1) {
			bf *= 100;							//�����_ 1�� -> 3���i�����f�[�^�͏����_�ȉ�3���j
		}
		else if (SV_POINT_A1 == 2) {			//2014/12/23
			bf *= 10;							//�����_ 2�� -> 3���i�����f�[�^�͏����_�ȉ�3���j
		}
		else {
			bf *= 1;							//�����_ 2�� -> 3���i�����f�[�^�͏����_�ȉ�3���j
		}
		*Dst_p = bf;
	}

	if( bf > wl1 ) {							//�@�B���
//2014/12/17
////		*Dst_p = wl1;
////		bf = *Dst_p;
		bf = wl1;								//mm
		*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
	}
	else if(bf < wl0) {							//�@�B����
//2014/12/17
////		*Dst_p = wl0;
////		bf = *Dst_p;
		bf = wl0;								//mm
		*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
	}

//2014/12/17
		//�ω��ʊm�F
////	wl1 = SV_DAIHAITO_SRV + (UNl)GMN_PAR012;
////	if (wl1 < bf )								// �ύX�傫�����H
////	{
////		ww0 = 0xff;
////	}
////	wl1 = SV_DAIHAITO_SRV - (UNl)GMN_PAR012;
////	if(wl1 & 0x8000000)
////	{
////		wl1 = 0;
////	}
////	if (wl1 > bf )								// �ύX�傫�����H
////	{
////		ww0 = 0xff;
////	}

		//�ω��ʊm�F
	wl1 = cnv_inch_mm(SV_DAIHAITO_SRV, 0) - bf;
	if ( (long)wl1 < 0 ) {
		wl1 = (long)wl1 * -1;						//�ω���
	}
	if (wl1 > (UNl)GMN_PAR012) {					//�ω��ʔ���l
		ww0 = 0xff;									//�ω��傫�����I
	}

	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// �␳�����^�]���H
		{
			ww0 = 0;
//2014/12/17
////			bf = SV_DAIHAITO_SRV;
////			*Dst_p = bf;
			*Dst_p = SV_DAIHAITO_SRV;
		}
	}
//2014/12/17	if ( bf != SV_DAIHAITO_SRV )				// �ύX�L��H		//V01w(INS)
	if ( *Dst_p != SV_DAIHAITO_SRV )				// �ύX�L��H		//V01w(INS)
	{
		PV0_KAGENHOS_BAK = SV_DAIHAITO_SRV;		// �ύX�L��Ȃ�O��l�Ƃ��ċL��
	}
	return(ww0);
}


/*
********************************************************************************
*  Module Name:		motion_spd_limit1
*  Function Name:	���x��������
*  Input	: 		�ݒ�l
*  Return	: 		�������ް�
*  Note		:
*
*  �� ��	: Shima		ON:2015-07-10
********************************************************************************
*/
UNl		motion_spd_limit1(UNl bf, UNs t_no)
{
	UNs		i, chk, bit;
	UNs		step;

	chk = 0;
	bit = BIT_0;

#if (mot100_test == 1)
	if (SV_buff[t_no].GRP_NO == 102) {						//�߂�s���̑��x�H
		if (PVP_MOT_STS[99] & cBIT3) {						//���~�b�g�L��H
			chk = 0xff;
		}
	}
	else {
		step = SV_MOT_PAGE * 5;								//1�s�ڂ̍s��No.0�`99(=1�`100)
		i = SV_buff[t_no].GRP_NO - 97;
		if (PVP_MOT_STS[step+i] & cBIT3) {					//���~�b�g�L��H
			chk = 0xff;
		}
	}
#else
	if (SV_buff[t_no].GRP_NO == 102) {						//�߂�s���̑��x�H
		if (PVP_CKSPD_STPBT & cBIT15) {
			chk = 0xff;
		}
	}
	else {
		i = SV_buff[t_no].GRP_NO - 97;
		if ( (GAMEN_NO == 6) || (GAMEN_NO == 30) ) {
			i += 5;
		}
		bit<<=i;
		if (PVP_CKSPD_STPBT & bit) {						//���̍s���̓��~�b�g�L��H
			chk = 0xff;
		}
	}
#endif

	if (chk) {
		if (GMN_PAR083 != 0) {							//�߂�s�����x�����l�̐ݒ�L��H
			if (bf < (GMN_PAR083*10)) {					//�����`�F�b�N
				bf = GMN_PAR083*10;						//�������~�b�g
			}
		}
	}

	return(bf);
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

//2016-04-16 koma	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
//2016-04-16 ��],�U�q(50.0or50.2)�� �A����s��28.12�܂��͘A����s��28.11 koma
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
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

//2016-04-16 koma	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//��]�H �A����s���H
//2016-04-16 ��],�U�q(50.0or50.2)�� �A����s��28.12�܂��͘A����s��28.11 koma
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
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
UNl		motion_pos_limit1(UNl wl0, UNs t_no)
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
			wl0 = cnv_mm_inch(wl0, 0);			//mm/inch				2014/12/17
			*deg = GMN_PAR007;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()��mm���p�x�͂��Ȃ��ėǂ���I
		}
		else if (chg < GMN_PAR006) {
			wl0 = DigRnaChange1(GMN_PAR006);	//�p�x��mm�ϊ�
			wl0 = cnv_mm_inch(wl0, 0);			//mm/inch				2014/12/17
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


/*
********************************************************************************
*  Function Name:	�яo�͎������Z
*  Input	:		bf:�ذ��ʒu0.001mm
*  Return	: 		�Ȃ�
*  Note		:		�ذ��ʒu����p�x���Z�o
*
*  �� ��	:		ON:2014/08/26
********************************************************************************
*/
void	RELEASE_POS_2_AGL_CAL(UNl bf)
{
	UNl		long_bf;
	S2b	dig1,dig2,dig3,dig4,dig5,taikidig;;


    taikidig=SV_TAIKIKAKU_SRV/10;	//�ҋ@�_

//	SV0_RELE_SNO0	= 2;				//�����[�X�J���I���s��
//	SV0_RELE_AGL0	= 100;				//�����[�X�J���I���p�x
//	SV0_RELE_SNO1	= 2;				//�����[�X�J���I�t�s��
//	SV0_RELE_AGL1	= 110;				//�����[�X�J���I�t�p�x
//	SV0_TIMING_SNO0	= 2;				//�^�C�~���O�J���I���s��
//	SV0_TIMING_AGL0	= 150;				//�^�C�~���O�J���I���p�x
//	SV0_TIMING_SNO1	= 2;				//�^�C�~���O�J���I�t�s��
//	SV0_TIMING_AGL1	= 160;				//�^�C�~���O�J���I�t�p�x


	//�ذ�on�p�x
	if(SEQ_050_SV & BIT_1) {//���]
		long_bf = bf + SV_NEG_OFS_LNG;
	}else{
		long_bf=bf;
	}
	dig1=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm�ϊ����p�x:0~180.0�x
	dig1=dig1/10;
	SV0_RELE_AGL0=dig1;				//�����[�X�J���I���p�x 1�x�P��


	//�ذ�off�p�x
	if(SEQ_050_SV & BIT_1) {//���]
		long_bf=SV_NEG_OFS_LNG;
		dig2=RnaDigChange1(SV_DNAREA_JUDG, long_bf);
		dig2=(dig2/10)+GMN_PAR071;	// +/-data :�ʏ��"-"
	}else{
		dig2=GMN_PAR070;			//��],�ӂ肱
	}
	DigMaxMin1(dig2);
	SV0_RELE_AGL1	= dig2;			//�����[�X�J���I�t�p�x 1�x�P��

	//�����on�p�x
	dig3=DigAddDigUnit1(SV0_RELE_AGL0,GMN_PAR072);		//�����[�X�J���I���p�x 1�x�P��+����J���I���p�x����
	SV0_SEND_AGL0	= TAIKIAREA_MAXMIN(dig3);			//����J���I���p�x

	//���ݸ޶�on�p�x
	dig4=DigAddDigUnit1(SV0_RELE_AGL0,GMN_PAR073);		//�����[�X�J���I���p�x+�^�C�C���O�J���I������
	SV0_TIMING_AGL0	= TAIKIAREA_MAXMIN(dig4);			//�^�C�~���O�J���I���p�x

	//���ݸ޶�off�p�x
	dig5=DigAddDigUnit1(SV0_TIMING_AGL0,GMN_PAR074);	//�^�C�~���O�J���I���p�x�p�x+�^�C���O�J���I�t����
	SV0_TIMING_AGL1	= TAIKIAREA_MAXMIN(dig5);			//�^�C�~���O�J���I�t�p�x

	SV0_RELE_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_RELE_AGL0);//0:�ŏ� �����[�X�J���I���s��
	SV0_RELE_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_RELE_AGL1);//1:�Ō� �����[�X�J���I�t�s��
	SV0_TIMING_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_TIMING_AGL0);//0:�ŏ� �^�C�~���O�J���I���s��
	SV0_TIMING_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_TIMING_AGL1);//0:�Ō� �^�C�~���O�J���I�t�s��

	SV0_SEND_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_SEND_AGL0);//0:�ŏ� ����J���I���s��


}

/*
********************************************************************************
*  Function Name:	�яo�͎������Z
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		����ʒu����p�x���Z�o
*
*  �� ��	:		ON:2014/08/26
********************************************************************************
*/
void	SEND_POS_2_AGL_CAL(UNl bf)
{
	UNl		long_bf;
	S2b		dig1,taikidig;
	S2b		maxdig,mindig;


	taikidig=SV_TAIKIKAKU_SRV/10;	//�ҋ@�_�ł͂Ȃ��̂�?
	//����J��off�p�x
	if(SEQ_050_SV & BIT_1) {//���]
		long_bf = bf + SV_NEG_OFS_LNG;
		dig1=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm�ϊ����p�x:0~180.0�x
		dig1=dig1/10;
		maxdig=180;
		mindig=taikidig;	//�ҋ@�_�ł��傤
    }else{
        long_bf=bf;
		dig1=RnaDigChange1(2700, long_bf);	//mm�ϊ����p�x:180.0~359.9�x
		dig1=dig1/10;
		if(SEQ_050_SV & BIT_2) {//�ӂ肱
			maxdig=360-taikidig;	//�ҋ@�_ 180-taikidig+180=3600-taikidig
			mindig=190;//190~
		}else{
			if(dig1==0){
				dig1=359;
			}
			maxdig=359;
			mindig=180;
		}
	}
	if(maxdig<dig1){
		dig1=maxdig;
	}
	if(dig1<mindig){
		dig1=mindig;
	}
	SV0_SEND_AGL1	=dig1;				//����J���I�t�p�x
	SV0_SEND_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_SEND_AGL1);//1:�Ō� ����J���I�t�s��

//	SV0_SEND_SNO0	= 3;				//����J���I���s��
//	SV0_SEND_AGL0	= 200;				//����J���I���p�x
//	SV0_SEND_SNO1	= 3;				//����J���I�t�s��
//	SV0_SEND_AGL1	= 210;				//����J���I�t�p�x

//	SV0_TIMING_SNO0	= 3;				//�^�C�~���O�J���I���s��
//	SV0_TIMING_AGL0	= 250;				//�^�C�~���O�J���I���p�x
//	SV0_TIMING_SNO1	= 3;				//�^�C�~���O�J���I�t�s��
//	SV0_TIMING_AGL1	= 260;				//�^�C�~���O�J���I�t�p�x
}



//	***************************************************
//	***												***
//	***		�p�x1(1�x�P��)+�p�x����2���Ԃ��l		***
//	***		0~359			+/-359		0~359		***
//	***												***
//	***************************************************
//	
S2b	DigAddDigUnit1(S2b dig1,S2b dig2){
	S2b ansdig;

	if(	(-359<=dig2)	&&	(dig2<=359)	){
		ansdig=dig1+dig2;
	}else{
		ansdig=dig1;//dig2:�ް��ُ�
	}
	if(ansdig<0){
		ansdig=ansdig+360;//-1�x �� 359�x
	}else{
		if(359<ansdig){
			ansdig=ansdig-360;	//360��0�x 361��1�x
		}
	}


	return(ansdig);
}


//	*******************************************************
//	***													***
//	***		�ҋ@�_�A�ҋ@�̈���܂߂�����͈̓`�F�b�N	***
//	***													***
//	*******************************************************
//	���],�ӂ肱�A��]�̃��[�h����L��

S2b	TAIKIAREA_MAXMIN(S2b dig)
{
	S2b taikidig,areadig,maxdig,mindig;
	UNl	long_bf;

	areadig=SV_UPAREA_JUDG/10+1;		//NO.40 �㎀�_����͈�
	taikidig=SV_TAIKIKAKU_SRV/10;		//�ҋ@�_0.1�x

	mindig=taikidig+areadig;
	if(360<=mindig){
		mindig=mindig-360;
	}

	DigMaxMin1(dig);
	if(SEQ_050_SV & BIT_1) {//���]
		long_bf = SV_NEG_OFS_LNG;
		maxdig=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm�ϊ����p�x:0~180.0�x
		maxdig=maxdig/10;
		if(maxdig<dig){//��
			dig=maxdig;
		}
    }else{
		if(SEQ_050_SV & BIT_2) {//�ӂ肱
			maxdig=360-taikidig-areadig;	//180-taiki+180
		}else{//��]
			maxdig=taikidig-areadig;	//180-taiki+180
			if(maxdig<0){
				maxdig=maxdig+360;
			}
		}
	}
	if(dig<mindig){//��
		dig=mindig;
	}
	if(maxdig<dig){//��
		dig=maxdig;
	}
	return(dig);
}



//	***************************************************
//	***												***
//	***		�ݒ�p�x�����؂�ŏ��̍s���̌���		***
//	***		�ݒ�p�x�����؂�Ō�̍s���̌���		***
//	***												***
//	***************************************************
//	sel==0:�Ԃ��l�͍ŏ��̍s��
//	sel!=0:�Ԃ��l�͍Ō�̍s��
//	���݂��Ȃ��ꍇ�͕Ԃ��l=0
//	����:SV_1DANDEG_SRV~SV_10DANDEG_SRV�͘A�����ĕ���ł��邱��(0.1�x�P��)
//UNs		SV_DANSUU_SRV;              /* �i�� */
//UNs		SV_TAIKIKAKU_SRV;           /* �ҋ@�p */
//UNs		SV_1DANDEG_SRV;             /* 1�i�ږڕW�p�x */
//UNs		SV_2DANDEG_SRV;             /* 2�i�ږڕW�p�x */
//UNs		SV_3DANDEG_SRV;             /* 3�i�ږڕW�p�x */
//UNs		SV_4DANDEG_SRV;             /* 4�i�ږڕW�p�x */
//UNs		SV_5DANDEG_SRV;             /* 5�i�ږڕW�p�x */
//UNs		SV_6DANDEG_SRV;             /* 6�i�ږڕW�p�x */
//UNs		SV_7DANDEG_SRV;             /* 7�i�ږڕW�p�x */
//UNs		SV_8DANDEG_SRV;             /* 8�i�ږڕW�p�x */
//UNs		SV_9DANDEG_SRV;             /* 9�i�ږڕW�p�x */
//UNs		SV_10DANDEG_SRV;            /* 10�i�ږڕW�p�x */
//	���[�h�ōŌ�̓��������Ⴄ


U2b CAM_KOUTEI_SEARCH1(U2b sel,S2b dig){
	U2b	stepmax;
	U2b	ansstep=0;
	U2b	objdig;
	U2b	dig_n1,dig_n,dig_last;
	U2b	firststep=0,laststep=0;
	U2b	dir=0;
	U2b	*srv;
	int	i;

	return(0);							//2014/09/10

	dig_n1	= SV_TAIKIKAKU_SRV;	//���Ēn�_
	dig_n	= SV_TAIKIKAKU_SRV;	//
	stepmax	= SV_DANSUU_SRV+1;
	if((1<stepmax)&&(stepmax<=SYSPOS_STEP_MAX+1)){//1~10[98] 2015-11-20
		if(SEQ_050_SV & BIT_1) {//���]
			dig_last=dig_n1;//�ҋ@�_�ɖ߂�
	    }else{
			if(SEQ_050_SV & BIT_2) {//�ӂ肱
				dig_last=3600-dig_n1;	//180.0-taiki+180.0
			}else{//��]
				dig_last=dig_n1+3600;	//370.0�x�ł��ǂ�
			}
		}
		objdig	=dig*10;//0.1�x
		srv		= &SV_1DANDEG_SRV;	//

		for(i=0;i<stepmax;i++){
			dig_n1	=dig_n;
			if(i==(stepmax-1)){//�Ō�
				dig_n	=dig_last;
			}else{
				dig_n	=srv[i];
			}
			if(dig_n1!=dig_n){
				if(dig_n1<dig_n){
					dir=0;//���]
					if((dig_n1<=objdig) && (objdig<dig_n) ){//50.0(n1)<=dig<100.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
				}else{
					dir=1;//�t�]
					if((dig_n1>=objdig) && (objdig>dig_n)  ){//100.0(n1) >= dig > 50.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
					
				}
			}
		}
	
		if(sel==0){//sel=0 first
			ansstep=firststep;
		}else{
			ansstep=laststep;
		}
	}

	return(ansstep);//
}


//	***************************************************
//	***												***
//	***		�ݒ�p�x�����؂�ŏ��̍s���̌���		***
//	***		�ݒ�p�x�����؂�Ō�̍s���̌���		***
//	***												***
//	***************************************************
//	sel==0:�Ԃ��l�͍ŏ��̍s��
//	sel!=0:�Ԃ��l�͍Ō�̍s��
//	���݂��Ȃ��ꍇ�͕Ԃ��l=0
//	����:SV_1DANDEG_SRV~SV_10DANDEG_SRV�͘A�����ĕ���ł��邱��(0.1�x�P��)
//UNs		SV_DANSUU_SRV;              /* �i�� */
//UNs		SV_TAIKIKAKU_SRV;           /* �ҋ@�p */
//UNs		SV_1DANDEG_SRV;             /* 1�i�ږڕW�p�x */
//UNs		SV_2DANDEG_SRV;             /* 2�i�ږڕW�p�x */
//UNs		SV_3DANDEG_SRV;             /* 3�i�ږڕW�p�x */
//UNs		SV_4DANDEG_SRV;             /* 4�i�ږڕW�p�x */
//UNs		SV_5DANDEG_SRV;             /* 5�i�ږڕW�p�x */
//UNs		SV_6DANDEG_SRV;             /* 6�i�ږڕW�p�x */
//UNs		SV_7DANDEG_SRV;             /* 7�i�ږڕW�p�x */
//UNs		SV_8DANDEG_SRV;             /* 8�i�ږڕW�p�x */
//UNs		SV_9DANDEG_SRV;             /* 9�i�ږڕW�p�x */
//UNs		SV_10DANDEG_SRV;            /* 10�i�ږڕW�p�x */
//	���[�h�ōŌ�̓��������Ⴄ
U2b CAM_KOUTEI_SEARCH2(U2b sel,S2b dig){
	U2b	stepmax;
	U2b	ansstep=0;
	U2b	objdig;
	U2b	dig_n1,dig_n,dig_last;
	U2b	firststep=0,laststep=0;
	U2b	dir=0;
	U2b	*srv;
	int	i;

	dig_n1	= SV_TAIKIKAKU_SRV;	//���Ēn�_
	dig_n	= SV_TAIKIKAKU_SRV;	//
	stepmax	= SV_DANSUU_SRV+1;
	if((1<stepmax)&&(stepmax<=SYSPOS_STEP_MAX+1)){//1~10��2~11 2015-11-20
		if(SEQ_050_SV & BIT_1) {//���]
			dig_last=dig_n1;//�ҋ@�_�ɖ߂�
	    }else{
			if(SEQ_050_SV & BIT_2) {//�ӂ肱
				dig_last=3600-dig_n1;	//180.0-taiki+180.0
			}else{//��]
				dig_last=dig_n1+3600;	//370.0�x�ł��ǂ�
			}
		}
		objdig	=dig*10;//0.1�x
		srv		= &SV_1DANDEG_SRV;	//

		for(i=0;i<stepmax;i++){
			dig_n1	=dig_n;
			if(i==(stepmax-1)){//�Ō�
				dig_n	=dig_last;
			}else{
				dig_n	=srv[i];
			}
			if(dig_n1!=dig_n){
				if(dig_n1<dig_n){
					dir=0;//���]
					if((dig_n1<=objdig) && (objdig<dig_n) ){//50.0(n1)<=dig<100.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
				}else{
					dir=1;//�t�]
					if((dig_n1>=objdig) && (objdig>dig_n)  ){//100.0(n1) >= dig > 50.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
					
				}
			}
		}
	
		if(sel==0){//sel=0 first
			ansstep=firststep;
		}else{
			ansstep=laststep;
		}
	}

	return(ansstep);//
}


/*
********************************************************************************
*  Function Name:	�яo�͎������Z
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�ذ��с^����с^���ݸ޶ѐݒ�̏������
*
*  �� ��	:		ON:2014/08/26
********************************************************************************
*/
UNl		CAM_AUTO_LIMIT(UNl bf)
{
	UNl		lim;

	if (SEQ_018_SV & cBIT12) {						//�d�l�ݒ�No.45�i۰�ض�1�`4�j
		if (SEQ_018_SV & cBIT14) {					//�d�l�ݒ�No.47�i۰�ض�5�`8�j
			if (SEQ_019_SV & cBIT0) {				//�d�l�ݒ�No.49�i۰�ض�9�`12�j
				if (SEQ_019_SV & cBIT2) {			//�d�l�ݒ�No.51�i۰�ض�13�`16�j
					if (SEQ_PAR_113 & cBIT6) {
						lim = 15;
					}
					else {
						lim = 16;
					}
				}
				else {
					if (SEQ_PAR_113 & cBIT6) {
						lim = 11;
					}
					else {
						lim = 12;
					}
				}
			}
			else {
				lim = 8;
			}
		}
		else {
			lim = 4;
		}
	}
	else {
		lim = 0;
	}
	
	if (bf > lim) {
		bf = lim;
	}

	return(bf);
}


/*
********************************************************************************
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		�J���s���J��Ԃ��߂�ݒ������
*
*  �� ��	:		ON:2014/09/05
********************************************************************************
*/
void	REP_CAM_CLR(UNs dan)
{
	UNs		bit;

	if ( (GAMEN_NO == 21) || (GAMEN_NO == 24) ) {				//���[�^���J��1�`8
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_ROTCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_ROTCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_ONR &= ~bit;
			}
		}
	}
	else if ( (GAMEN_NO == 22) || (GAMEN_NO == 25) ) {			//���[�^���J��9�`16
		if (SV_FLG_CNT == 1) {
			bit = cBIT8 << CSR_TBL_POS_NOW;
			SV_ROTCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT8 << CSR_TBL_POS_NOW;
			SV_ROTCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_ONR &= ~bit;
			}
		}
	}
	else if ( (GAMEN_NO == 19) || (WINDOW_NO == 5) ) {			//�G�W�F�N�^�^������
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_EJECAM_ONR &= ~bit;
			if (dan == 0) {
				SV_EJECAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_EJECAM_OFR &= ~bit;
			if (dan == 0) {
				SV_EJECAM_ONR &= ~bit;
			}
		}
	}
	else if ( GAMEN_NO == 20 ) {								//�~�X�t�B�[�h1�`4
		if ( (CSR_TBL_POS_NOW == 0) || 
			 (CSR_TBL_POS_NOW == 2) || 
			 (CSR_TBL_POS_NOW == 4) || 
			 (CSR_TBL_POS_NOW == 6) ) {

			if (SV_FLG_CNT == 1) {
				bit = cBIT0 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_ONR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_OFR &= ~bit;
				}
			}
			else if (SV_FLG_CNT == 3) {
				bit = cBIT0 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_OFR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_ONR &= ~bit;
				}
			}
		}
	}
	else if ( GAMEN_NO == 68 ) {								//�~�X�t�B�[�h5�`6
		if ( (CSR_TBL_POS_NOW == 0) || 
			 (CSR_TBL_POS_NOW == 2) ) {

			if (SV_FLG_CNT == 1) {
				bit = cBIT4 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_ONR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_OFR &= ~bit;
				}
			}
			else if (SV_FLG_CNT == 3) {
				bit = cBIT4 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_OFR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_ONR &= ~bit;
				}
			}
		}
	}
	else if ( WINDOW_NO == 19 ) {								//�~�X�t�B�[�h1�`6(WINDOW)
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_MISCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_MISCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_MISCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_MISCAM_ONR &= ~bit;
			}
		}
	}
}


/*
********************************************************************************
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:		���[�V�����f�[�^10�i�̈悩��100�i�̈�ɃR�s�[
*
*  �� ��	:		ON:2015/03/26
********************************************************************************
*/
void	copy_mot100(void)
{
	UNs		*Dst_w, *Src_w, i, j, k;
	UNl		cnt;

	/*--- ��]���[�h  �p�x ---*/
	Src_w = &SV_1DANDEG0_SRV;
	Dst_w = &SV_MOTDEG0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ���]���[�h  �p�x ---*/
	Src_w = &SV_1DANDEG1_SRV;
	Dst_w = &SV_MOTDEG1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �U�q���[�h  �p�x ---*/
	Src_w = &SV_1DANDEG2_SRV;
	Dst_w = &SV_MOTDEG2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �㉝�����[�h  �p�x ---*/
	Src_w = &SV_1DANDEG3_SRV;
	Dst_w = &SV_MOTDEG3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ��]���[�h  �ʒu ---*/
	Src_w = (UNs *)&SV_1DANPOS0_SRV;
	Dst_w = (UNs *)&SV_MOTPOS0_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ���]���[�h  �ʒu ---*/
	Src_w = (UNs *)&SV_1DANPOS1_SRV;
	Dst_w = (UNs *)&SV_MOTPOS1_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �U�q���[�h  �ʒu ---*/
	Src_w = (UNs *)&SV_1DANPOS2_SRV;
	Dst_w = (UNs *)&SV_MOTPOS2_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �㉝�����[�h  �ʒu ---*/
	Src_w = (UNs *)&SV_1DANPOS3_SRV;
	Dst_w = (UNs *)&SV_MOTPOS3_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ��]���[�h  ���x ---*/
	Src_w = &SV_1DANSPD0_SRV;
	Dst_w = &SV_MOTSPD0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ���]���[�h  ���x ---*/
	Src_w = &SV_1DANSPD1_SRV;
	Dst_w = &SV_MOTSPD1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �U�q���[�h  ���x ---*/
	Src_w = &SV_1DANSPD2_SRV;
	Dst_w = &SV_MOTSPD2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �㉝�����[�h  ���x ---*/
	Src_w = &SV_1DANSPD3_SRV;
	Dst_w = &SV_MOTSPD3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ��]���[�h  ��~���� ---*/
	Src_w = &SV_1DANTIM0_SRV;
	Dst_w = &SV_MOTTIM0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ���]���[�h  ��~���� ---*/
	Src_w = &SV_1DANTIM1_SRV;
	Dst_w = &SV_MOTTIM1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �U�q���[�h  ��~���� ---*/
	Src_w = &SV_1DANTIM2_SRV;
	Dst_w = &SV_MOTTIM2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �㉝�����[�h  ��~���� ---*/
	Src_w = &SV_1DANTIM3_SRV;
	Dst_w = &SV_MOTTIM3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ��]���[�h  �׏d ---*/
	Src_w = &SV_1DANPRS0_SRV;
	Dst_w = &SV_MOTPRS0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ���]���[�h  �׏d ---*/
	Src_w = &SV_1DANPRS1_SRV;
	Dst_w = &SV_MOTPRS1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �U�q���[�h  �׏d ---*/
	Src_w = &SV_1DANPRS2_SRV;
	Dst_w = &SV_MOTPRS2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- �㉝�����[�h  �׏d ---*/
	Src_w = &SV_1DANPRS3_SRV;
	Dst_w = &SV_MOTPRS3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- ��]���[�h  �ڕW�ʒu�^�׏d�ؑ�BIT��� ---*/
	Src_w = &SV_MOTOBJ_INF0;
	Dst_w = &SV_MOTTGT0_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- ���]���[�h  �ڕW�ʒu�^�׏d�ؑ�BIT��� ---*/
	Src_w = &SV_MOTOBJ_INF1;
	Dst_w = &SV_MOTTGT1_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- �U�q���[�h  �ڕW�ʒu�^�׏d�ؑ�BIT��� ---*/
	Src_w = &SV_MOTOBJ_INF2;
	Dst_w = &SV_MOTTGT2_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- �㉝�����[�h  �ڕW�ʒu�^�׏d�ؑ�BIT��� ---*/
	Src_w = &SV_MOTOBJ_INF3;
	Dst_w = &SV_MOTTGT3_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}

	for (i=1; i<=220; i++) {
		kata_load(i, &kata_mot010_work[0]);			//�^�f�[�^��FROM����Ǎ���

		/*--- ��]���[�h�p�x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ���]���[�h�p�x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �U�q���[�h�p�x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �㉝�����[�h�p�x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ��]���[�h�ʒu Ӱ���10�i��100�i ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ���]���[�h�ʒu Ӱ���10�i��100�i ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �U�q���[�h�ʒu Ӱ���10�i��100�i ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �㉝�����[�h�ʒu Ӱ���10�i��100�i ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ��]���[�h���x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ���]���[�h���x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �U�q���[�h���x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �㉝�����[�h���x Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ��]���[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ���]���[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �U�q���[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �㉝�����[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ��]���[�h�׏d Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ���]���[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �U�q���[�h���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- �㉝�����[�h ���� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- ��]���[�h �ڕW�ʒu�^�׏d�ؑ�BIT��� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF0 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT0_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- ���]���[�h �ڕW�ʒu�^�׏d�ؑ�BIT��� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF1 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT1_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- �U�q���[�h �ڕW�ʒu�^�׏d�ؑ�BIT��� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF2 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT2_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- �㉝�����[�h �ڕW�ʒu�^�׏d�ؑ�BIT��� Ӱ���10�i��100�i ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF3 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT3_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		kata_save2(i, &kata_mot100_work[0]);				//�^�f�[�^(100�i���[�V����)��FROM�֊i�[
	}
}


/*** END ***/
