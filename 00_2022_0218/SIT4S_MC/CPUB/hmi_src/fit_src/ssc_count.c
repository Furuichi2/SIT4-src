/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�J�E���^���䏈��									*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"								//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		CNT_LIMIT	9999999					/* �������E	��������0�ر	*/
#define		E_TIM_1H	360000*2				//5ms�����(1����=1*60*60*100*2)

EXTRN		WORD		deg_OLD [];				/* �p�x�O��l				*/
EXTRN		WORD		rbit_OLD[];				/* ؾ��   �w���ޯđO��l	*/
EXTRN		WORD		cbit_OLD[];				/* ����UP �w���ޯđO��l	*/

/* �������� */
void		TIM_5MS_COUNT	 (void);			/* ����Ҳ� ���� 5ms			*/
void		Count_Check_IN	 (WORD);			/* ������������				*/
void		Count_Check_IN0	 (WORD);			/* ������������	�p�x�Ή�	*/
void		Count_Check_OUT	 (WORD);			/* �O����������				*/
void		Count_Check_RESET(WORD);			/* ����ؾ�ď���				*/
void		Count_Check_smp(UNs);				//������������ �׸ނ�����ݸ�
void		TIM_mcn_smp(void);					//�����e�i���X���� ����

/****************************************************************************/
/*																			*/
/*	�J�E���g����			�F	��������荞�݂���R�[�������	�i�T�����j	*/
/*																			*/
/*		���b�g�J�E���^�P�A�Q�A�g�[�^���J�E���^�̍X�V���s���B				*/
/*		�����J�E���^���́A�G���R�[�_�p�x��									*/
/*		�O���J�E���^���́A�V�[�P���X�f�[�^��								*/
/*		�J�E���^�t�o�𔻒f����B											*/
/*																			*/
/*		SEQ_PAR_016			�F	�J�E���^�L�^���A�����^�O���w��				*/
/*		SEQ_PAR_032			�F	�J�E���^���^�؎w��							*/
/*																			*/
/*  �� ��	:																*/
/*			FIT)�c�[	ON:2002-08-08(ۯ�2 ���� / �@�B�����������̒ǉ�)		*/
/*			FIT)�c�[	ON:2002-09-09(�O�����������̒ǉ��ɂ��ύX)			*/
/****************************************************************************/
void	TIM_5MS_COUNT	(void)
{
	UNs		i;

	Count_Check_IN (3);									//�@�B����������

	if (((SEQ_016_SV & BIT_8) != 0) &&					/* İ�ٶ��� �L		*/
		((SEQ_032_SV & BIT_0) != 0) &&					/* İ�ٶ��� ��		*/
		((SEQ_PAR_102 & BIT_3) == 0)){					//İ�ٶ��� ؾ�Ďw��

		if ((SEQ_016_SV & BIT_9) == 0){					//İ�ٶ��� �O������
			Count_Check_IN (0);							/* ������������		*/
		}
		else{
			Count_Check_OUT(0);							/* �O����������		*/
		}
	}
	else{
		Count_Check_smp(0);								//İ�ٶ����̻����ݸ�
	}

	if (((SEQ_016_SV & BIT_12) != 0) &&					/* ۯ�1 ���� �L		*/
		((SEQ_032_SV & BIT_2) != 0) &&					/* ۯ�1 ���� ��		*/
		((SEQ_PAR_033 & BIT_0) == 0) &&					//ۯ�1 ���� UP ?
		((SEQ_PAR_102 & BIT_11) == 0)){					//ۯ�1 ���� ؾ�Ďw��

		if ((SEQ_016_SV & BIT_13) == 0){				//ۯ�1 ���� �O������
			Count_Check_IN (1);							/* ������������		*/
		}
		else{
			Count_Check_OUT(1);							/* �O����������		*/
		}
	}
	else{
		Count_Check_smp(1);								//ۯ�1 ���� �̻����ݸ�
	}

	if (((SEQ_016_SV & BIT_14) != 0) &&					/* ۯ�2 ���� �L		*/
		((SEQ_032_SV & BIT_3) != 0) &&					/* ۯ�2 ���� ��		*/
		((SEQ_PAR_033 & BIT_1) == 0) &&				//ۯ�2 ���� UP ?
		((SEQ_PAR_102 & BIT_15) == 0)){					//ۯ�2 ���� ؾ�Ďw��

		if ((SEQ_016_SV & BIT_15) == 0){				//ۯ�2 ���� �O������
			Count_Check_IN (2);							/* ������������		*/
		}
		else{
			Count_Check_OUT(2);							/* �O����������		*/
		}
	}
	else{
		Count_Check_smp(2);								//ۯ�2 ���� �̻����ݸ�
	}


//DEL 13LINE : 2002-09-09
//	if ((SEQ_PAR_032 & BIT_00) != 0){					/* İ�ٶ��� ��		*/
//					Count_Check_IN (0);					/* ������������		*/
//	}													/*					*/
//
//	if ((SEQ_PAR_032 & BIT_02) != 0){					/* ۯ�1 ���� ��		*/
//					Count_Check_IN (1);					/* ������������		*/
//	}													/*					*/
//
////INS 4LINE : 2002-08-08
//	if ((SEQ_PAR_032 & BIT_03) != 0){					/* ۯ�2 ���� ��		*/
//					Count_Check_IN (2);					/* ������������		*/
//	}
//	Count_Check_IN (3);									// �@�B����������

//*	if (((SEQ_PAR_016 & BIT_08) != 0)&&					/* İ�ٶ��� �L		*/
//*		((SEQ_PAR_032 & BIT_00) != 0)){					/* İ�ٶ��� ��		*/
//*		if ((SEQ_PAR_016 & BIT_09) == 0)				/*					*/
//*					Count_Check_IN (0);					/* ������������		*/
//*		else		Count_Check_OUT(0);					/* �O����������		*/
//*		Count_Check_RESET(0);							/* ����ؾ�ď���		*/
//*	}													/*					*/

//*	if (((SEQ_PAR_016 & BIT_12) != 0)&&					/* ۯ�1 ���� �L		*/
//*		((SEQ_PAR_032 & BIT_02) != 0)){					/* ۯ�1 ���� ��		*/
//*		if ((SEQ_PAR_016 & BIT_13) == 0)				/*					*/
//*					Count_Check_IN (1);					/* ������������		*/
//*		else		Count_Check_OUT(1);					/* �O����������		*/
//*		Count_Check_RESET(2);							/* ����ؾ�ď���		*/
//*	}													/*					*/

//*	if (((SEQ_PAR_016 & BIT_14) != 0)&&					/* ۯ�2 ���� �L		*/
//*		((SEQ_PAR_032 & BIT_03) != 0)){					/* ۯ�2 ���� ��		*/
//*		if ((SEQ_PAR_016 & BIT_15) == 0)				/*					*/
//*					Count_Check_IN (2);					/* ������������		*/
//*		else		Count_Check_OUT(2);					/* �O����������		*/
//*		Count_Check_RESET(2);							/* ����ؾ�ď���		*/
//*	}													/*					*/

/* V00t */
	i = GAIBU_RST_BAK;					//�O�����Z�b�g�w�ߗ����オ��H
	GAIBU_RST_BAK = SEQ_PAR_102;
	i ^= SEQ_PAR_102;
	i &= SEQ_PAR_102;
	if( i & BIT_3 ) {					//�g�[�^���J�E���^�P���Z�b�g�H
		PV_TOTLC1_B3 = 0;				//�g�[�^���J�E���^�P�N���A
		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
	}
	if( i & BIT_7 ) {					//�g�[�^���J�E���^�Q���Z�b�g�H
		PV_TOTLC2_B31 = 0;				//�g�[�^���J�E���^�Q�N���A
		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
	}
	if( i & BIT_B ) {					//���b�g�J�E���^�P���Z�b�g�H
		PV_LOTCT1_B4 = 0;				//���b�g�J�E���^�P�N���A
		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
		SEQ_PAR_033 &= ~BIT_0;			//���b�g�J�E���^�P�A�b�v�@�N���A
	}
	if( i & BIT_F ) {					//���b�g�J�E���^�Q���Z�b�g�H
		PV_LOTCT2_B41 = 0;				//���b�g�J�E���^�Q�N���A
		KAT_DATCHG_FLG = 0xff;			//�J�E���^�l�ύX�t���O
		SEQ_PAR_033 &= ~BIT_1;			//���b�g�J�E���^�Q�A�b�v�@�N���A
	}
	if( SEQ_PAR_107 & BIT_6 ){						//ۯĶ������Z���H
		PV_LOTCT1_B1 = (SV_PUR1SV_B4 - PV_LOTCT1_B4);
		PV_LOTCT2_B1 = (SV_PUR2SV_B41 - PV_LOTCT2_B41);
													//���Z������ϲŽ�\���΍�
		if( PV_LOTCT1_B1 & 0x80000000 ) {
			PV_LOTCT1_B1 = 0;
		}
		if( PV_LOTCT2_B1 & 0x80000000 ) {
			PV_LOTCT2_B1 = 0;
		}
	}
	else{
		PV_LOTCT1_B1 = PV_LOTCT1_B4;
		PV_LOTCT2_B1 = PV_LOTCT2_B41;
	}
}


/****************************************************************************/
/*																			*/
/*	�����J�E���g����		�F	�����_�ʉ߃t���O�ŃJ�E���^�t�o�𔻒f����B	*/
/*																			*/
/*		HS_PVP_LOTCNT_FLG	�F	�����_�ʉ߃t���O							*/
/*		deg_OLD				�F	�O��l�ۑ�									*/
/*																			*/
/****************************************************************************/
void	Count_Check_IN	(WORD i)
{
	UNl	*bf_p;

	if (HS_PVP_LOTCNT_FLG != 0){						/* �����_�ʉ�		*/
		if (deg_OLD[i] == 0){							/* �O��OFF	�����	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3 ++;
						if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
						break;

			  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						  	PV_LOTCT1_B4 ++;
						if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
						break;

			  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
			  			  	PV_LOTCT2_B41++;
						if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
						break;

//INS 10LINE : 2002-08-08
			  case 3:
						bf_p = (UNl *)&PV_LIFE_COUNT[0];
						if(*bf_p == 0xffffffff){
							*bf_p += 1;
							PV_LIFE_COUNT[2] += 1;
						}
						else{
							*bf_p += 1;
						}
						break;

			  default:	break;
			}
			deg_OLD[i] = 1;								/* �O��l ON		*/
		}
		else{
			deg_OLD[i] = 0;								/* �O��l OFF		*/
			if( i == 3 ){
				HS_PVP_LOTCNT_FLG = 0;					/* �����_�ʉ߸ر	*/
			}
		}
	}
	else	deg_OLD[i] = 0;								/* �O��l OFF		*/
}
/****************************************************************************/
/*																			*/
/*	�����J�E���g����		�F	�p�x�ŃJ�E���^�t�o�𔻒f����B				*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	�F	�p�x�f�[�^		�i�����_�P�� 0�`3599�܂Łj	*/
/*		SEQ_PAR_222			�F	���]�^�t�]									*/
/*		deg_OLD				�F	�p�x�O��l									*/
/*																			*/
/****************************************************************************/
void	Count_Check_IN0	(WORD i)
{
	WORD	real_deg;
	WORD	deg_min;
	WORD	deg_max;

//	if ((SEQ_PAR_160 & BIT_00) != 0){					/* �p�x�͈�			*/
//	if ((SEQ_PAR_222 & BIT_06) != 0){					/* �p�x�͈�			*/
	if (1){												/* DEBUG			*/
			deg_min = 180;								/* ���]��			*/
			deg_max = 270;								/*					*/
	}else{												/*					*/
			deg_min =  90;								/* �t��]��			*/
			deg_max = 180;								/*					*/
	}													/*					*/

	real_deg = (PVP_NOW_ANGLE_RNA / 10);				/* �p�x�ް��擾		*/

	if (((real_deg >=deg_min)&&(real_deg <=deg_max))&&	/* ����l = �͈͓�	*/
		((deg_OLD[i]<deg_min)||(deg_OLD[i]>deg_max))){	/* �O��l = �͈͊O	*/
		switch (i){
		  case 0:	PV_TOTLC1_B3 ++;
					if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
					break;
		  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						PV_LOTCT1_B4 ++;
					if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
					break;
		  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
						PV_LOTCT2_B41++;
					if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
					break;
		  default:	break;
		}
	}
	deg_OLD[i] = real_deg;								/* �ۑ�				*/
}
/****************************************************************************/
/*																			*/
/*	�O���J�E���g����		�F	�V�[�P���X�f�[�^�ŃJ�E���^�t�o�𔻒f����B	*/
/*																			*/
/*		SEQ_PAR_102			�F	�J�E���^�w��								*/
/*		cbit_OLD			�F	�J�E���^�w�߃r�b�g�O��l					*/
/*																			*/
/****************************************************************************/
void	Count_Check_OUT	(WORD i)
{
	WORD	count_bit;

	switch (i){											/* �����ޯĎw��		*/
		case 0:		count_bit	= BIT_02;		break;
		case 1:		count_bit	= BIT_10;		break;
		case 2:		count_bit	= BIT_14;		break;
		default:	count_bit	= 0;			break;
	}

	if ((SEQ_PAR_102 & count_bit) != 0){				/* �����w�� ON		*/
		if (cbit_OLD[i] == 0){							/* �O��OFF	�����	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3 ++;
						if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
						break;
			  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						  	PV_LOTCT1_B4 ++;
						if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
						break;
			  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
			  			  	PV_LOTCT2_B41++;
						if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
						break;
			  default:	break;
			}
		}
			cbit_OLD[i] = 1;							/* �O��l ON		*/
	}
	else	cbit_OLD[i] = 0;							/* �O��l OFF		*/
}
/****************************************************************************/
/*																			*/
/*	�J�E���^���Z�b�g����	�F	�V�[�P���X�f�[�^�ŃJ�E���^���Z�b�g����B	*/
/*																			*/
/*		SEQ_PAR_102			�F	�J�E���^�w��								*/
/*		rbit_OLD			�F	���Z�b�g�w�߃r�b�g�O��l					*/
/*																			*/
/****************************************************************************/
void	Count_Check_RESET	(WORD i)
{
	WORD	reset_bit;

	switch (i){											/* �����ޯĎw��		*/
		case 0:		reset_bit	= BIT_03;		break;
		case 1:		reset_bit	= BIT_11;		break;
		case 2:		reset_bit	= BIT_15;		break;
		default:	reset_bit	= 0;			break;
	}

	if ((SEQ_PAR_102 & reset_bit) != 0){				/* ����ؾ�Ďw�� ON	*/
		if (rbit_OLD[i] == 0){							/* �O��OFF	�����	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3	= 0;	break;
			  case 1:	PV_LOTCT1_B4	= 0;	break;
			  case 2:	PV_LOTCT2_B41	= 0;	break;
			  default:							break;
			}
		}
			rbit_OLD[i] = 1;							/* �O��l ON		*/
	}
	else	rbit_OLD[i] = 0;							/* �O��l OFF		*/
}


/*
********************************************************************************
*  Module Name:		Count_Check_smp
*  Function Name:	�����J�E���g����	�����_�ʉ߃t���O������ݸ�
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*				HS_PVP_LOTCNT_FLG	�F	�����_�ʉ߃t���O
*				deg_OLD				�F	�O��l�ۑ�
*				cbit_OLD			�F	�J�E���^�w�߃r�b�g�O��l
*
*  �� ��	:FIT)�c�[		ON:2002-09-09
********************************************************************************
*/
void	Count_Check_smp(UNs i)
{
	UNs	count_bit;

	switch (i){												/* �����ޯĎw��		*/
		case 0:	count_bit = (SEQ_016_SV & BIT_9);	break;	//İ�ٶ��� �O������
		case 1:	count_bit = (SEQ_016_SV & BIT_13);	break;	//ۯ�1 ���� �O������
		case 2:	count_bit = (SEQ_016_SV & BIT_15);	break;	//ۯ�2 ���� �O������
		default: count_bit	= 0;					break;
	}

	if(count_bit == 00 ){
		if (HS_PVP_LOTCNT_FLG != 0){						/* �����_�ʉ�		*/
			if (deg_OLD[i] == 0){							/* �O��OFF	�����	*/
				deg_OLD[i] = 1;								/* �O��l ON		*/
			}
			else{
				deg_OLD[i] = 0;								/* �O��l OFF		*/
			}
		}
		else{
			deg_OLD[i] = 0;									/* �O��l OFF		*/
		}
	}
	else{
		switch (i){											/* �����ޯĎw��		*/
			case 0:		count_bit	= BIT_02;		break;
			case 1:		count_bit	= BIT_10;		break;
			case 2:		count_bit	= BIT_14;		break;
			default:	count_bit	= 0;			break;
		}

		if ((SEQ_PAR_102 & count_bit) != 0){				/* �����w�� ON		*/
				cbit_OLD[i] = 1;							/* �O��l ON		*/
		}
		else	cbit_OLD[i] = 0;							/* �O��l OFF		*/
	}

}

/*
********************************************************************************
*  Module Name:		TIM_mcn_smp
*  Function Name:	�����e�i���X���� ����
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-08-08
********************************************************************************
*/
void	TIM_mcn_smp(void)
{
	UNs	bf, bf1;

//���춳�� ����
	bf = SEQ_PAR_111 & 0x00ff;			//�����オ��f�[�^�쐬
	bf1 = MCN_SEQ_LAST1;
	MCN_SEQ_LAST1 = bf;
	bf1 ^= bf;
	bf1 &= bf;
	if( bf1 != 00 ){
		if(bf1 & BIT_0){				//���춳��1(C/B ON)[1:����]
			MCN_MENT_CNT1 ++;
		}
		if(bf1 & BIT_1){				//���춳��2(�^�]�t)[1:����]
			MCN_MENT_CNT2 ++;
		}
		if(bf1 & BIT_2){				//���춳��3(��ު��1)[1:����]
			MCN_MENT_CNT3 ++;
		}
		if(bf1 & BIT_3){				//���춳��4(��ު��2)[1:����]
			MCN_MENT_CNT4 ++;
		}
		if(bf1 & BIT_4){				//���춳��5(��ު��3)[1:����]
			MCN_MENT_CNT5 ++;
		}
		if(bf1 & BIT_5){				//���춳��6(������1)[1:����]
			MCN_MENT_CNT6 ++;
		}
		if(bf1 & BIT_6){				//���춳��7(������2)[1:����]
			MCN_MENT_CNT7 ++;
		}
		if(bf1 & BIT_7){				//���춳��4(������3)[1:����]
			MCN_MENT_CNT8 ++;
		}
	}

//���쎞�� ����
	bf1 = SEQ_PAR_111;
	if(bf1 & BIT_8){						//���쎞��(�ғ�����)[1:����]
		MCN_MENT_TIM1_10 ++;				//5ms ����+1
		if(E_TIM_1H <= MCN_MENT_TIM1_10){	//��ϰ���߁H
			MCN_MENT_TIM1_10 = 0;			//�ر
			MCN_MENT_TIM1 ++;				//1���� ����+1
		}
	}
	if(bf1 & BIT_9){						//���쎞��(C/B ON)[1:����]
		MCN_MENT_TIM2_10 ++;				//5ms ����+1
		if(E_TIM_1H <= MCN_MENT_TIM2_10){	//��ϰ���߁H
			MCN_MENT_TIM2_10 = 0;			//�ر
			MCN_MENT_TIM2 ++;				//1���� ����+1
		}
	}
	if(bf1 & BIT_10){						//���쎞��(Ҳ�Ӱ�)[1:����]
		MCN_MENT_TIM3_10 ++;				//5ms ����+1
		if(E_TIM_1H <= MCN_MENT_TIM3_10){	//��ϰ���߁H
			MCN_MENT_TIM3_10 = 0;			//�ر
			MCN_MENT_TIM3 ++;				//1���� ����+1
		}
	}

}


/****************************************************************************/
