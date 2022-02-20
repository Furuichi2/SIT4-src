/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�c�o�q�`�l �� �e�q�`�l	�f�[�^�]������				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_def.h"							//�e��̋��ʒ�`
#include	"ssc_wk_ext.h"


extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	�f�[�^�]������		�F	�c�o�q�`�l �� �e�q�`�l							*/
/*																			*/
/****************************************************************************/


void	DP_TRANS_MOT	(void)
{

	UNl	wkl1;			/* V00m */

	U2b	posTimeLate;
	posTimeLate=10;//10:100msec  1:10msec 2014-05-30[R02R03]


//2002-10-16
//	SVP_OBJECT_PS01		= SV_1DANPOS_SRV;				/* 01�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS02		= SV_2DANPOS_SRV;				/* 02�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS03		= SV_3DANPOS_SRV;				/* 03�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS04		= SV_4DANPOS_SRV;				/* 04�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS05		= SV_5DANPOS_SRV;				/* 05�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS06		= SV_6DANPOS_SRV;				/* 06�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS07		= SV_7DANPOS_SRV;				/* 07�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS08		= SV_8DANPOS_SRV;				/* 08�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS09		= SV_9DANPOS_SRV;				/* 09�i�ږڕW�ʒu		*/
//	SVP_OBJECT_PS10		= SV_10DANPOS_SRV;				/* 10�i�ږڕW�ʒu		*/

	/* V00m */
	if( SEQ_050_SV & BIT_1 ) {								//���]�@�H
		SVP_OBJECT_PS01	= cnv_inch_mm(SV_1DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 01�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS01);
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 02�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS02);
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 03�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS03);
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 04�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS04);
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 05�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS05);
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 06�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS06);
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 07�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS07);
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 08�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS08);
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 09�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS09);
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0) + SV_NEG_OFS_LNG;	/* 10�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS10);
		SVP_OBJECT_PS11		= 0;							/* 11�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS11);
		SVP_OBJECT_PS12		= 0;							/* 12�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS12);
		SVP_OBJECT_PS13		= 0;							/* 13�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS13);
		SVP_OBJECT_PS14		= 0;							/* 14�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS14);
		SVP_OBJECT_PS15		= 0;							/* 15�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS15);
		SVP_OBJECT_PS16		= 0;							/* 16�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS16);
		SVP_OBJECT_PS17		= 0;							/* 17�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS17);
		SVP_OBJECT_PS18		= 0;							/* 18�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS18);
		SVP_OBJECT_PS19		= 0;							/* 19�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS19);
		SVP_OBJECT_PS20		= 0;							/* 20�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS20);
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0) - SV_NEG_OFS_LNG;		/* �_�C�n�C�g�������ʒu�|�������� */
		DPB_SEND_4B((U4b *)&SVP_DAIHAI_ORG0);
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* �ҋ@�_�ʒu */
		DPB_SEND_4B((U4b *)&SVP_UPAREA_POS0);
	}
	else {
		SVP_OBJECT_PS01	= cnv_inch_mm(SV_1DANPOS_SRV, 0);	/* 01�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS01);
		SVP_OBJECT_PS02	= cnv_inch_mm(SV_2DANPOS_SRV, 0);	/* 02�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS02);
		SVP_OBJECT_PS03	= cnv_inch_mm(SV_3DANPOS_SRV, 0);	/* 03�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS03);
		SVP_OBJECT_PS04	= cnv_inch_mm(SV_4DANPOS_SRV, 0);	/* 04�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS04);
		SVP_OBJECT_PS05	= cnv_inch_mm(SV_5DANPOS_SRV, 0);	/* 05�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS05);
		SVP_OBJECT_PS06	= cnv_inch_mm(SV_6DANPOS_SRV, 0);	/* 06�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS06);
		SVP_OBJECT_PS07	= cnv_inch_mm(SV_7DANPOS_SRV, 0);	/* 07�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS07);
		SVP_OBJECT_PS08	= cnv_inch_mm(SV_8DANPOS_SRV, 0);	/* 08�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS08);
		SVP_OBJECT_PS09	= cnv_inch_mm(SV_9DANPOS_SRV, 0);	/* 09�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS09);
		SVP_OBJECT_PS10	= cnv_inch_mm(SV_10DANPOS_SRV, 0);	/* 10�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS10);
		SVP_OBJECT_PS11		= 0;							/* 11�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS11);
		SVP_OBJECT_PS12		= 0;							/* 12�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS12);
		SVP_OBJECT_PS13		= 0;							/* 13�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS13);
		SVP_OBJECT_PS14		= 0;							/* 14�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS14);
		SVP_OBJECT_PS15		= 0;							/* 15�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS15);
		SVP_OBJECT_PS16		= 0;							/* 16�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS16);
		SVP_OBJECT_PS17		= 0;							/* 17�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS17);
		SVP_OBJECT_PS18		= 0;							/* 18�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS18);
		SVP_OBJECT_PS19		= 0;							/* 19�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS19);
		SVP_OBJECT_PS20		= 0;							/* 20�i�ږڕW�ʒu		*/
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS20);
		SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0);	/* �_�C�n�C�g			*/
		DPB_SEND_4B((U4b *)&SVP_DAIHAI_ORG0);
		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* �ҋ@�_�ʒu			*/
		DPB_SEND_4B((U4b *)&SVP_UPAREA_POS0);
	}

	SVP_OBJECT_DG01		= SV_1DANDEG_SRV;				/* 01�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG01);
	SVP_OBJECT_DG02		= SV_2DANDEG_SRV;				/* 02�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG02);
	SVP_OBJECT_DG03		= SV_3DANDEG_SRV;				/* 03�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG03);
	SVP_OBJECT_DG04		= SV_4DANDEG_SRV;				/* 04�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG04);
	SVP_OBJECT_DG05		= SV_5DANDEG_SRV;				/* 05�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG05);
	SVP_OBJECT_DG06		= SV_6DANDEG_SRV;				/* 06�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG06);
	SVP_OBJECT_DG07		= SV_7DANDEG_SRV;				/* 07�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG07);
	SVP_OBJECT_DG08		= SV_8DANDEG_SRV;				/* 08�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG08);
	SVP_OBJECT_DG09		= SV_9DANDEG_SRV;				/* 09�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG09);
	SVP_OBJECT_DG10		= SV_10DANDEG_SRV;				/* 10�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG10);
	SVP_OBJECT_DG11		= 0;							/* 11�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG11);
	SVP_OBJECT_DG12		= 0;							/* 12�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG12);
	SVP_OBJECT_DG13		= 0;							/* 13�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG13);
	SVP_OBJECT_DG14		= 0;							/* 14�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG14);
	SVP_OBJECT_DG15		= 0;							/* 15�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG15);
	SVP_OBJECT_DG16		= 0;							/* 16�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG16);
	SVP_OBJECT_DG17		= 0;							/* 17�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG17);
	SVP_OBJECT_DG18		= 0;							/* 18�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG18);
	SVP_OBJECT_DG19		= 0;							/* 19�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG19);
	SVP_OBJECT_DG20		= 0;							/* 20�i�ڊp�x�ʒu		*/
	DPB_SEND_2B(&SVP_OBJECT_DG20);

	SVP_OBJECT_SP01		= SV_1DANSPD_SRV;				/* 01�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP01);
	SVP_OBJECT_SP02		= SV_2DANSPD_SRV;				/* 02�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP02);
	SVP_OBJECT_SP03		= SV_3DANSPD_SRV;				/* 03�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP03);
	SVP_OBJECT_SP04		= SV_4DANSPD_SRV;				/* 04�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP04);
	SVP_OBJECT_SP05		= SV_5DANSPD_SRV;				/* 05�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP05);
	SVP_OBJECT_SP06		= SV_6DANSPD_SRV;				/* 06�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP06);
	SVP_OBJECT_SP07		= SV_7DANSPD_SRV;				/* 07�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP07);
	SVP_OBJECT_SP08		= SV_8DANSPD_SRV;				/* 08�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP08);
	SVP_OBJECT_SP09		= SV_9DANSPD_SRV;				/* 09�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP09);
	SVP_OBJECT_SP10		= SV_10DANSPD_SRV;				/* 10�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP10);
	SVP_OBJECT_SP11		= 0;							/* 11�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP11);
	SVP_OBJECT_SP12		= 0;							/* 12�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP12);
	SVP_OBJECT_SP13		= 0;							/* 13�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP13);
	SVP_OBJECT_SP14		= 0;							/* 14�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP14);
	SVP_OBJECT_SP15		= 0;							/* 15�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP15);
	SVP_OBJECT_SP16		= 0;							/* 16�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP16);
	SVP_OBJECT_SP17		= 0;							/* 17�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP17);
	SVP_OBJECT_SP18		= 0;							/* 18�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP18);
	SVP_OBJECT_SP19		= 0;							/* 19�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP19);
	SVP_OBJECT_SP20		= 0;							/* 20�i�ڈړ����x		*/
	DPB_SEND_2B(&SVP_OBJECT_SP20);

	SVP_OBJECT_TM01		= SV_1DANTIM_SRV*posTimeLate;				/* 01�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM01);
	SVP_OBJECT_TM02		= SV_2DANTIM_SRV*posTimeLate;				/* 02�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM02);
	SVP_OBJECT_TM03		= SV_3DANTIM_SRV*posTimeLate;				/* 03�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM03);
	SVP_OBJECT_TM04		= SV_4DANTIM_SRV*posTimeLate;				/* 04�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM04);
	SVP_OBJECT_TM05		= SV_5DANTIM_SRV*posTimeLate;				/* 05�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM05);
	SVP_OBJECT_TM06		= SV_6DANTIM_SRV*posTimeLate;				/* 06�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM06);
	SVP_OBJECT_TM07		= SV_7DANTIM_SRV*posTimeLate;				/* 07�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM07);
	SVP_OBJECT_TM08		= SV_8DANTIM_SRV*posTimeLate;				/* 08�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM08);
	SVP_OBJECT_TM09		= SV_9DANTIM_SRV*posTimeLate;				/* 09�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM09);
	SVP_OBJECT_TM10		= SV_10DANTIM_SRV*posTimeLate;				/* 10�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM10);

	SVP_OBJECT_TM11		= 0;							/* 11�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM11);
	SVP_OBJECT_TM12		= 0;							/* 12�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM12);
	SVP_OBJECT_TM13		= 0;							/* 13�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM13);
	SVP_OBJECT_TM14		= 0;							/* 14�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM14);
	SVP_OBJECT_TM15		= 0;							/* 15�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM15);
	SVP_OBJECT_TM16		= 0;							/* 16�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM16);
	SVP_OBJECT_TM17		= 0;							/* 17�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM17);
	SVP_OBJECT_TM18		= 0;							/* 18�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM18);
	SVP_OBJECT_TM19		= 0;							/* 19�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM19);
	SVP_OBJECT_TM20		= 0;							/* 20�i�ڒ�~����		*/
	DPB_SEND_2B(&SVP_OBJECT_TM20);

//2002-10-16
//2002-08-08
//	SVP_DAIHAI_ORG0		= SV_DAIHAITO_SRV;				/* �_�C�n�C�g			*/
//	SVP_DAIHAI_ORG0		= SV_DAIHAITO_SRV * 10;			/* �_�C�n�C�g			*/


//V01m	if (SEQ_024_SV & BIT_4)							//�׏d�␳����H	V01k
//	{
//		SVP_KAJYUU_OBJP	= SV_DAIHAITO_SRV;				/* �ڕW�׏d�ݒ�l */
//	}
//	else
//	{
//		/* V00m */
//		if( SEQ_050_SV & BIT_1 ) {								//���]�@�H
//			SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0) - SV_NEG_OFS_LNG;		/* �_�C�n�C�g�������ʒu�|�������� */
//		}
//		else {
//			SVP_DAIHAI_ORG0	= cnv_inch_mm(SV_DAIHAITO_SRV, 0);	/* �_�C�n�C�g			*/
//		}
//	}
	SVP_KAJYUU_OBJP	= SV_KAJYUU_OBJP;				/* �ڕW�׏d�ݒ�l */
	DPB_SEND_2B(&SVP_KAJYUU_OBJP);


//2002-08-08
//	SVP_MRTION_SEL1		= SV_KAITEN_SRV;				/* ��]����				*/
	SVP_MTSTEP_MAXM		= SV_DANSUU_SRV;				/* �i��					*/
	DPB_SEND_2B(&SVP_MTSTEP_MAXM);

//2002-10-16
//	SVP_UPAREA_POS0		= SV_TAIKIPOS_SRV;				/* �ҋ@�_�ʒu			*/

//V01m	/* V00m */
//	if( SEQ_050_SV & BIT_1 ) {								//���]�@�H
//		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0) + SV_NEG_OFS_LNG;			/* �ҋ@�_�ʒu */
//	}
//	else {
//		SVP_UPAREA_POS0	= cnv_inch_mm(SV_TAIKIPOS_SRV, 0);	/* �ҋ@�_�ʒu			*/
//	}

	SVP_UPAREA_DIG0		= SV_TAIKIKAKU_SRV;				/* �ҋ@�_�p�x			*/
	DPB_SEND_2B(&SVP_UPAREA_DIG0);

//2002-08-02
//	SVP_UPAREA_SPD0		= 0;							/* ����x				*/
	SVP_UPAREA_SPD0		= SV_TAIKSPD_SRV;				/* ����x				*/
	DPB_SEND_2B(&SVP_UPAREA_SPD0);

	SVP_UPAREA_TIM0		= SV_TAIKTIM_SRV*posTimeLate;	/* �ҋ@����				*/
	DPB_SEND_2B(&SVP_UPAREA_TIM0);

	/* �␳�ǉ� 2002.06.28 */
//V01m	if (SEQ_024_SV & BIT_4)							//�׏d�␳����H	V01j
//	{
//		SVP_KAJYUU_PRS1	= SV_HOASEI_SRV;				/* �׏d�␳�f�[�^		*/
//	}
//	else
//	{
//		SVP_DAIHSA_LENG	= SV_HOASEI_SRV;				/* �␳�f�[�^			*/
//	}
	SVP_KAJYUU_PRS1	= SV_KAJYUU_PRS;				/* �׏d�␳�f�[�^		*/
	DPB_SEND_2B(&SVP_KAJYUU_PRS1);

//2014/12/23
////	SVP_DAIHSA_LENG	= SV_HOASEI_SRV;				/* �␳�f�[�^			*/
	SVP_DAIHSA_LENG	= cnv_uinch_um(SV_HOASEI_SRV);		/* �␳�f�[�^			*/
	DPB_SEND_2B(&SVP_DAIHSA_LENG);


//	SVP_DNAREA_INP0		= SV_TAIKAN_SRV;				/* �ҋ@�����͈�			*/
//2002-10-16
//	SVP_OBJARA_INP0		= SV_MOKKAN_SRV;				/* �ڕW�����͈�			*/
	SVP_OBJARA_INP0	= cnv_inch_mm(SV_MOKKAN_SRV, 0);	/* �ڕW�����͈�			*/
	DPB_SEND_2B(&SVP_OBJARA_INP0);

//2002-10-17
//2002-08-08:�ǉ�
//	SVP_SLID_POS1		= SV_ATUOS0_D9 * 10;			//�X���C�h�������߁@���Y�ݒ�
//	SVP_SLID_POS2		= SV_ATUOS1_D9 * 10;			//�X���C�h�������߁@�i���P�ݒ�
//	SVP_SLID_POS3		= SV_ATUOS2_D9 * 10;			//�X���C�h�������߁@�i���Q�ݒ�

	if( SEQ_016_SV & BIT_6 ) {							//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		SVP_SLID_POS1		= cnv_inch_mm(SV_ATUOS0_D9, 0);	//�X���C�h�������߁@���Y�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS1);
		SVP_SLID_POS2		= cnv_inch_mm(SV_ATUOS1_D9, 0);	//�X���C�h�������߁@�i��P�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS2);
		SVP_SLID_POS3		= cnv_inch_mm(SV_ATUOS2_D9, 0);	//�X���C�h�������߁@�i���Q�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS3);

		SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9, 0);	//�X���C�h��������  ���Y�ݒ�/�i���P/�i��Q		2014/06/03
		DPB_SEND_4B(&SVP_ATSLID_OBJ1);
	}
	else {
		if (SV_POINT_A1 == 0) {
			wkl1 = 1000;
		}
		else if (SV_POINT_A1 == 1) {
			wkl1 = 100;
		}
		else if (SV_POINT_A1 == 2) {
			wkl1 = 10;
		}
		else {
			wkl1 = 1;
		}
		SVP_SLID_POS1		= cnv_inch_mm(SV_ATUOS0_D9 * wkl1, 0);	//�X���C�h�������߁@���Y�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS1);
		SVP_SLID_POS2		= cnv_inch_mm(SV_ATUOS1_D9 * wkl1, 0);	//�X���C�h�������߁@�i��P�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS2);
		SVP_SLID_POS3		= cnv_inch_mm(SV_ATUOS2_D9 * wkl1, 0);	//�X���C�h�������߁@�i���Q�ݒ�
		DPB_SEND_4B(&SVP_SLID_POS3);

		SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9 * wkl1, 0);	//�X���C�h��������  ���Y�ݒ�/�i���P/�i��Q		2014/06/03
		DPB_SEND_4B(&SVP_ATSLID_OBJ1);
	}

//2002-10-07:�폜
//	SVP_GMNSEQ_CNT01	= SV_COUNT1_A1;					//�����J�E���^�P
//	SVP_GMNSEQ_CNT02	= SV_COUNT2_A1;					//�����J�E���^�Q
//	SVP_GMNSEQ_CNT03	= SV_COUNT3_A1;					//�����J�E���^�R
//	SVP_GMNSEQ_CNT04	= 0;							//�\��
//	SVP_GMNSEQ_CNT05	= 0;							//�\��
//	SVP_GMNSEQ_CNT06	= 0;							//�\��
//	SVP_GMNSEQ_CNT07	= 0;							//�\��
//	SVP_GMNSEQ_CNT08	= 0;							//�\��
//
//	SVP_GMNSEQ_TIM01	= SV_TIMER1_A1;					//�����^�C�}�P
//	SVP_GMNSEQ_TIM02	= SV_TIMER2_A1;					//�����^�C�}�Q
//	SVP_GMNSEQ_TIM03	= SV_TIMER3_A1;					//�����^�C�}�R
//	SVP_GMNSEQ_TIM04	= 0;							//�\��
//	SVP_GMNSEQ_TIM05	= 0;							//�\��
//	SVP_GMNSEQ_TIM06	= 0;							//�\��
//	SVP_GMNSEQ_TIM07	= 0;							//�\��
//	SVP_GMNSEQ_TIM08	= 0;							//�\��

//2002-08-29:�ǉ�
//2002-10-17
//	SVP_ATSLID_OBJ1		= SV_ATUOSU_D9 * 10;			//�X���C�h�������ߐݒ�l�i���ݓ��쒆�j
//2014/06/03	SVP_ATSLID_OBJ1		= cnv_inch_mm(SV_ATUOSU_D9, 0);	//�X���C�h�������ߐݒ�l�i���ݓ��쒆�j
////////////	DPB_SEND_4B(&SVP_ATSLID_OBJ1);

	SVP_ATSLID_DNOBJ1	= SV_DNSTOP_A21;				//�X���C�h�������߁@���~��~
	DPB_SEND_2B(&SVP_ATSLID_DNOBJ1);
	SVP_ATSLID_UPOBJ1	= SV_UPSTOP_A21;				//�X���C�h�������߁@�㏸��~
	DPB_SEND_2B(&SVP_ATSLID_UPOBJ1);
	SVP_ATSLID_BAKLNG	= SV_MODORI_A21;				//�X���C�h�������߁@�߂��
	DPB_SEND_2B(&SVP_ATSLID_BAKLNG);
	SVP_ATSLID_COEF1	= SV_SSEIDO_A21;				//�X���C�h�������߁@���䐸�x
	DPB_SEND_2B(&SVP_ATSLID_COEF1);

//V01 (INS)
	SVP_DNDINC_SPD1		= SV_SPDDAN_B1;					/* �i�摬�x				*/
	DPB_SEND_2B(&SVP_DNDINC_SPD1);

//V01w(INS)
	SVP_OVERLIDE_COF	= SV_OVERLIDE_COF;				/* ����ײ�ޔ䗦				*/
	DPB_SEND_2B(&SVP_OVERLIDE_COF);
	SVP_DND_STOPDIG1	= SV_DND_STOPDIG1;				/* �i���~�p�x				*/
	DPB_SEND_2B(&SVP_DND_STOPDIG1);
	SVP_KJSTR_STEP1		= SV_KJSTR_STEP1;				//0,1~�H�� 
	DPB_SEND_2B(&SVP_KJSTR_STEP1);
	SVP_KJSTR_DIG1		= SV_KJSTR_DIG1	;				//359.0
	DPB_SEND_2B(&SVP_KJSTR_DIG1);
	SVP_KJEND_STEP1		= SV_KJEND_STEP1;				//0,1~�H��
	DPB_SEND_2B(&SVP_KJEND_STEP1);
	SVP_KJEND_DIG1		= SV_KJEND_DIG1	;				//359.0
	DPB_SEND_2B(&SVP_KJEND_DIG1);

//V06p(INS)
	SVP_KATTCH_SPD		= SV_KATTCH_SPD *100;			//�^�b�`�ʒu���o���x
	DPB_SEND_2B(&SVP_KATTCH_SPD);

//2014/04/14
	SVP_KATTCH_SAG		= SV_KATTCH_SAG;				//�^�b�`�ʒu���o�p�x
	DPB_SEND_2B(&SVP_KATTCH_SAG);
	SVP_KATTCH_EAG		= SV_KATTCH_EAG;				//�^�b�`�ʒu���o�p�x
	DPB_SEND_2B(&SVP_KATTCH_EAG);

//2014/04/14
	SVP_KANDO_A21	= SV_KANDO_A21;			//���x
	SVP_UPDATA_A21	= SV_UPDATA_A21;		//���
	SVP_DNDATA_A21	= SV_DNDATA_A21;		//����
	SVP_GENITI_A21	= SV_GENITI_A21;		//���ʒu
	SVP_MODORI_A21	= SV_MODORI_A21;		//�߂��
	SVP_DNSTOP_A21	= SV_DNSTOP_A21;		//���~��~
	SVP_UPSTOP_A21	= SV_UPSTOP_A21;		//�㏸��~
//2014/06/03	SVP_SSEIDO_A21	= SV_SSEIDO_A21;		//���䐸�x
	SVP_SL_TENPOS	= SV_POINT_A1;			//�X���C�h��������  �����_�ʒu						2014/06/03
	SVP_SLPOS_DIR	= SV_SLPOS_DIR;			//�ʒu���ߕ���

//2014/06/03
//;	-------------- �ő�l�I���� ����۰��,۱�Я� ��,���v,�E
	SVP_OVERE1_A26	= SV_OVERE1_A26;		// �׏d�v�@�I�[�o�[���[�h�P
	DPB_SEND_2B(&SVP_OVERE1_A26);
	SVP_ROALM1_A26	= SV_ROALM1_A26;		// �׏d�v�@���A�[���b�~�g�P
	DPB_SEND_2B(&SVP_ROALM1_A26);
	SVP_OVERE2_A26	= SV_OVERE2_A26;		// �׏d�v�@�I�[�o�[���[�h�Q
	DPB_SEND_2B(&SVP_OVERE2_A26);
	SVP_ROALM2_A26	= SV_ROALM2_A26;		// �׏d�v�@���A�[���b�~�g�Q
	DPB_SEND_2B(&SVP_ROALM2_A26);
	SVP_OVERE3_A26	= SV_OVERE3_A26;		// �׏d�v�@�I�[�o�[���[�h�R
	DPB_SEND_2B(&SVP_OVERE3_A26);
	SVP_ROALM3_A26	= SV_ROALM3_A26;		// �׏d�v�@���A�[���b�~�g�R
	DPB_SEND_2B(&SVP_ROALM3_A26);

//;	-------------- �ŏ�(ϲŽ�ő�)�I���� ����۰��,۱�Я� ��,���v,�E
	SVP_OVERE1_A27	= SV_OVERE1_A27;		// �׏d�v�@�I�[�o�[���[�h�P �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_OVERE1_A27);
	SVP_ROALM1_A27	= SV_ROALM1_A27;		// �׏d�v�@���A�[���b�~�g�P  �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_ROALM1_A27);
	SVP_OVERE2_A27	= SV_OVERE2_A27;		// �׏d�v�@�I�[�o�[���[�h�Q  �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_OVERE2_A27);
	SVP_ROALM2_A27	= SV_ROALM2_A27;		// �׏d�v�@���A�[���b�~�g�Q  �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_ROALM2_A27);
	SVP_OVERE3_A27	= SV_OVERE3_A27;		// �׏d�v�@�I�[�o�[���[�h�R  �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_OVERE3_A27);
	SVP_ROALM3_A27	= SV_ROALM3_A27;		// �׏d�v�@���A�[���b�~�g�R  �@�i�ŏ��l�j
	DPB_SEND_2B(&SVP_ROALM3_A27);

//;	-------------- �U���I���� ����۰��,۱�Я� ��,���v,�E
	SVP_OVERE1_A28	= SV_OVERE1_A28;		// �׏d�v�@�I�[�o�[���[�h�P �@�i�U���j
	DPB_SEND_2B(&SVP_OVERE1_A28);
	SVP_ROALM1_A28	= SV_ROALM1_A28;		// �׏d�v�@���A�[���b�~�g�P  �@�i�U���j
	DPB_SEND_2B(&SVP_ROALM1_A28);
	SVP_OVERE2_A28	= SV_OVERE2_A28;		// �׏d�v�@�I�[�o�[���[�h�Q  �@�i�U���j
	DPB_SEND_2B(&SVP_OVERE2_A28);
	SVP_ROALM2_A28	= SV_ROALM2_A28;		// �׏d�v�@���A�[���b�~�g�Q  �@�i�U���j
	DPB_SEND_2B(&SVP_ROALM2_A28);
	SVP_OVERE3_A28	= SV_OVERE3_A28;		// �׏d�v�@�I�[�o�[���[�h�R  �@�i�U���j
	DPB_SEND_2B(&SVP_OVERE3_A28);
	SVP_ROALM3_A28	= SV_ROALM3_A28;		// �׏d�v�@���A�[���b�~�g�R  �@�i�U���j
	DPB_SEND_2B(&SVP_ROALM3_A28);

//2014/08/27
	SVP_INTLIM_SNO = SV_INTLIM_SNO;				//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�s��
	DPB_SEND_2B(&SVP_INTLIM_SNO);
	SVP_INTLIM_AGL = SV_INTLIM_AGL;				//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�p�x
	DPB_SEND_2B(&SVP_INTLIM_AGL);
	SVP_INTLIM_POS = SV_INTLIM_POS;				//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�ʒu
	DPB_SEND_4B(&SVP_INTLIM_POS);
	SVP_WTTIM_MAX = SV_WTTIM_MAX;				//�ײ�ގ����ҋ@�@�\  �ҋ@���ԏ��
	DPB_SEND_2B(&SVP_WTTIM_MAX);

//2014/09/04
	SVP_MOTREP_STGS		= SV_MOTREP_STGS;		//�J��Ԃ��J�n�s��
	DPB_SEND_2B(&SVP_MOTREP_STGS);
	SVP_MOTREP_STGE		= SV_MOTREP_STGE;		//�J��Ԃ��I���s��
	DPB_SEND_2B(&SVP_MOTREP_STGE);
	SVP_MOTREP_SPD		= SV_MOTREP_SPD;		//�J��Ԃ��߂葬�x
	DPB_SEND_2B(&SVP_MOTREP_SPD);
	SVP_MOTREP_CNT		= SV_MOTREP_CNT;		//�J��Ԃ���
	DPB_SEND_2B(&SVP_MOTREP_CNT);

//2014/09/04
//2014/10/09	SVP_MOT_FIX			= SV_MOT_FIX;			//��葬�x�̈� �s��BIT���
	SVP_MOT_FIX			= SV0_MOT_FIX;			//��葬�x�̈� �s��BIT���
	DPB_SEND_2B(&SVP_MOT_FIX);

//2015/01/14
	SVP_OBJECT_PRS01	= SV_1DANPRS_SRV;				//�H��1 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS01);
	SVP_OBJECT_PRS02	= SV_2DANPRS_SRV;				//�H��2 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS02);
	SVP_OBJECT_PRS03	= SV_3DANPRS_SRV;				//�H��3 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS03);
	SVP_OBJECT_PRS04	= SV_4DANPRS_SRV;				//�H��4 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS04);
	SVP_OBJECT_PRS05	= SV_5DANPRS_SRV;				//�H��5 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS05);
	SVP_OBJECT_PRS06	= SV_6DANPRS_SRV;				//�H��6 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS06);
	SVP_OBJECT_PRS07	= SV_7DANPRS_SRV;				//�H��7 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS07);
	SVP_OBJECT_PRS08	= SV_8DANPRS_SRV;				//�H��8 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS08);
	SVP_OBJECT_PRS09	= SV_9DANPRS_SRV;				//�H��9 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS09);
	SVP_OBJECT_PRS10	= SV_10DANPRS_SRV;				//�H��10 �׏d�ڕW
	DPB_SEND_2B(&SVP_OBJECT_PRS10);
	SVP_KAJOBJ_HAB		= SV_KAJOBJ_HAB;				//�׏d�����͈�
	DPB_SEND_2B(&SVP_KAJOBJ_HAB);
}
/****************************************************************************/
