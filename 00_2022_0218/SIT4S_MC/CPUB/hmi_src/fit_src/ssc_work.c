
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`


#pragma section	wkram1	// 2010-09-21 wdt-up�΍� �����=����Bwkram1

/*==========================================================================*/
/*		�e�X�g�p�̉���`													*/
/*==========================================================================*/
//UNs		OP_STATUS_DT;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H

/*==========================================================================*/
/*		�V���[�N�̈��`�iSit-S�j											*/
/*==========================================================================*/
UNi		SVPV_LCD_FLG;							//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
UNs		SV_DANSUU_SRV_BAK;						//�H���� �Z�[�u
//UNs		SV_TAIKIKAKU_SRV_BAK;					//�ҋ@�p�̊i�[
//UNl		SV_TAIKIPOS_SRV_BAK;					//�ҋ@�ʒu�̊i�[

UNl		SV_TAIKIPOS_SRV;            /* �ҋ@�ʒu */
UNs		SV_KAITEN_SRV;              /* ��]���� */
UNs		SV_DANSUU_SRV;              /* �i�� */
UNs		SV_TAIKIKAKU_SRV;           /* �ҋ@�p */
UNs		SV_TAIKSPD_SRV;             /* ����x */
UNl		SV_DAIHAITO_SRV;            /* �_�C�n�C�g */
UNs		SV_HOASEI_SRV;              /* �␳�f�[�^ */
UNs		SV_TAIKTIM_SRV;             /* �ҋ@���� */
UNs		SV_1DANDEG_SRV;             /* 1�i�ږڕW�p�x */
UNs		SV_2DANDEG_SRV;             /* 2�i�ږڕW�p�x */
UNs		SV_3DANDEG_SRV;             /* 3�i�ږڕW�p�x */
UNs		SV_4DANDEG_SRV;             /* 4�i�ږڕW�p�x */
UNs		SV_5DANDEG_SRV;             /* 5�i�ږڕW�p�x */
UNs		SV_6DANDEG_SRV;             /* 6�i�ږڕW�p�x */
UNs		SV_7DANDEG_SRV;             /* 7�i�ږڕW�p�x */
UNs		SV_8DANDEG_SRV;             /* 8�i�ږڕW�p�x */
UNs		SV_9DANDEG_SRV;             /* 9�i�ږڕW�p�x */
UNs		SV_10DANDEG_SRV;            /* 10�i�ږڕW�p�x */
UNl		SV_1DANPOS_SRV;             /* 1�i�ږڕW�ʒu */
UNl		SV_2DANPOS_SRV;             /* 2�i�ږڕW�ʒu */
UNl		SV_3DANPOS_SRV;             /* 3�i�ږڕW�ʒu */
UNl		SV_4DANPOS_SRV;             /* 4�i�ږڕW�ʒu */
UNl		SV_5DANPOS_SRV;             /* 5�i�ږڕW�ʒu */
UNl		SV_6DANPOS_SRV;             /* 6�i�ږڕW�ʒu */
UNl		SV_7DANPOS_SRV;             /* 7�i�ږڕW�ʒu */
UNl		SV_8DANPOS_SRV;             /* 8�i�ږڕW�ʒu */
UNl		SV_9DANPOS_SRV;             /* 9�i�ږڕW�ʒu */
UNl		SV_10DANPOS_SRV;            /* 10�i�ږڕW�ʒu */
UNs		SV_1DANSPD_SRV;             /* 1�i�ڈړ����x */
UNs		SV_2DANSPD_SRV;             /* 2�i�ڈړ����x */
UNs		SV_3DANSPD_SRV;             /* 3�i�ڈړ����x */
UNs		SV_4DANSPD_SRV;             /* 4�i�ڈړ����x */
UNs		SV_5DANSPD_SRV;             /* 5�i�ڈړ����x */
UNs		SV_6DANSPD_SRV;             /* 6�i�ڈړ����x */
UNs		SV_7DANSPD_SRV;             /* 7�i�ڈړ����x */
UNs		SV_8DANSPD_SRV;             /* 8�i�ڈړ����x */
UNs		SV_9DANSPD_SRV;             /* 9�i�ڈړ����x */
UNs		SV_10DANSPD_SRV;            /* 10�i�ڈړ����x */
UNs		SV_1DANTIM_SRV;             /* 1�i�ڒ�~���� */
UNs		SV_2DANTIM_SRV;             /* 2�i�ڒ�~���� */
UNs		SV_3DANTIM_SRV;             /* 3�i�ڒ�~���� */
UNs		SV_4DANTIM_SRV;             /* 4�i�ڒ�~���� */
UNs		SV_5DANTIM_SRV;             /* 5�i�ڒ�~���� */
UNs		SV_6DANTIM_SRV;             /* 6�i�ڒ�~���� */
UNs		SV_7DANTIM_SRV;             /* 7�i�ڒ�~���� */
UNs		SV_8DANTIM_SRV;             /* 8�i�ڒ�~���� */
UNs		SV_9DANTIM_SRV;             /* 9�i�ڒ�~���� */
UNs		SV_10DANTIM_SRV;            /* 10�i�ڒ�~���� */
//UNs		SV_CYCTIM_SRV;              /* �T�C�N���^�C�� */
//UNs		SV_TAIKAN_SRV;              /* �ҋ@�����͈� */
UNs		SV_MOKKAN_SRV;              /* �ڕW�����͈� */
UNs		SV_KAJYUU_PRS;				/* �׏d�␳ V01m*/
UNs		SV_KAJYUU_OBJP;				/* �׏d�ڕW V01m*/

UNs		disp_stg, disp_stg_sel;
UNl		language_chg;

UNs		PV_STPTIM_B2;							/* ssc_tbl.c �ɂĎg�p		*/

//UNs		PV_KOUTEI1_NO;							/*                      	*/
//UNs		PV_KOUTEI2_NO;							/*                      	*/
//UNs		PV_KOUTEI3_NO;							/*                      	*/
//UNs		PV_KOUTEI4_NO;							/*                      	*/
//UNs		PV_KOUTEI5_NO;							/*                      	*/

UNs		PV_STPTM_OLD;							/*                      	*/
UNs		PV_MLNO01_C15;							/*                      	*/
UNs		PV_MLNO02_C15;							/*                      	*/
UNs		PV_MLNO03_C15;							/*                      	*/
UNs		PV_MLNO04_C15;							/*                      	*/
UNs		PV_MLNO05_C15;							/*                      	*/
UNs		PV_MLNO06_C15;							/*                      	*/
UNs		PV_MLNO07_C15;							/*                      	*/
UNs		PV_MLNO08_C15;							/*                      	*/
UNs		PV_MLNO09_C15;							/*                      	*/
UNs		PV_MLNO10_C15;							/*                      	*/

UNs		PV_MLDNO2_F11[8];		//DB 16 DUP(?)	;	/* V01j */

//UNl		PVB_RNAORG_PLS1;						/*							*/
//UNl		SV_GENITI_CHK;							/*							*/

UNs		PV_CAMNA1_C1;							/*                      	*/
UNs		PV_MLDMES_C1;							/*							*/
UNs		PV_OFFSET_A1;							/*							*/
UNs		PV_DATINI_A1;							/*							*/
UNs		PV_KAJYUU_A1;							/*							*/
UNs		PV_GAIBU_A1;							/*							*/
UNs		PV_BACKDA_A1;							/*							*/

//2002-08-08
//UNs		deg_OLD	[ 3 ];							/* �p�x�O��l				*/
UNs		deg_OLD	[ 4 ];							/* �p�x�O��l				*/
UNs		rbit_OLD[ 3 ];							/* ؾ��   �w���ޯđO��l	*/
UNs		cbit_OLD[ 3 ];							/* ����UP �w���ޯđO��l	*/

UNs		TAIKI_ZEN_MOD;							/* ���[���b�g�O��`�����	*/
UNs		TAIKITEN_DIRECT;						/* �ҋ@�_�f�[�^�i�N���b�`�j	*/

UNs		SEISAN_DISP_FLG;						// ���Y�s���\��	 (00:�Ȃ��^FF:����)
UNs		INTROCK_DISP_FLG;						// �K�C�_���X�\��(00:�Ȃ��^FF:����)

UNs		IROCK_NO	 [ INTROCK_MAX ];			/* ����ۯ��\���ԍ���		*/
UNs		IROCK_NO_LAST[ INTROCK_MAX ];			/* ����ۯ��\���ԍ���O��l	*/

/*==========================================================================*/
/*		�L�[���͗p�̃��[�N�̈��`											*/
/*==========================================================================*/
UNs		KEY_DATA_CODE, KEY_DATA_MODE;

UNs		Key_up[4],Key_dn[4],Key_last[4];

/*==========================================================================*/
/*		�����[�N�̈��`(Sit-2���)											*/
/*==========================================================================*/
/***	�\���p�̃��[�N�̈��`		***/
UNs		GAMEN_NO;					//DW ?	;/* ��ʃR�[�h */
UNs		GAMEN_CODE;					//DB ?	;/* ��ʃR�[�h */
UNs		WINDOW_NO;					//DW ?	;/* ��ʃR�[�h */
UNs		CSR_FLG;					//DB ?	;/* �J�[�\���L���ʃt���O */

UNs		CSR_CNT;					/* �J�[�\���J�E���^ */
UNs		CSR_CNT1;					/* �J�[�\���J�E���^ */
UNs		SV_CNT;						/* �ݒ�l�J�E���^ */
UNs		PV_CNT;						/* �����l�J�E���^ */
UNs		SW_CNT;						/* �r�v�f�[�^�J�E���^ */
UNs		SW_CNT1;					/* �r�v�f�[�^�J�E���^ */

//UNs		CSR_CNT2;				/* �J�[�\���J�E���^ */
//UNs		SV_CNT2;				/* �ݒ�l�J�E���^ */
//UNs		PV_CNT2;				/* �����l�J�E���^ */
//UNs		SW_CNT2;				/* �r�v�f�[�^�J�E���^ */

CSR_TBL_TDEF	CSR_buff[110];		/* �J�[�\�����e�[�u����`�̈�	*/
SV_TBL_TDEF		SV_buff[80];		/* �ݒ�l���e�[�u����`�̈�	*/
PV_TBL_TDEF		PV_buff[40];		/* �����l���e�[�u����`�̈�	*/
SW_TBL_TDEF		SW_buff[70];		/* �r�v�f�[�^���e�[�u����`�̈�	*/

UNs		PV_DISP_CNT;				/* �\�������l�J�E���^ */
UNs		SW_DISP_CNT;				//����\���r�v�f�[�^�J�E���^

UNs		LCD_WORK1[15][16][40];		/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */
UNs		LCD_WORK2[15][16][40];		/* �\��ܰ��̈�LCD2[���s���ޯĖډ�������] */
UNs		LCD_WORK3[15][16][40];		/* �\��ܰ��̈�LCD3[���s���ޯĖډ�������] */ /* V01  */
//UNs		LCD_WIN1[9][16][40];	/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */
//UNs		LCD_WIN2[9][16][40];	/* �\��ܰ��̈�LCD2[���s���ޯĖډ�������] */

UNs		CSR_FLG_CNT;				//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		SV_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */
UNs		SW_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */

UNs		CSR_POS;					//DW ?	;/* �J�[�\���|�W�V�����f�[�^�Ǎ� */
UNs		CSR_POS_LAST;				//DW ?	;/* �O��J�[�\���|�W�V�����f�[�^�Ǎ� */
UNs		CSR_ON_FLG;					//DB ?	;/* �J�[�\���\���t���O�n�m */

UNs		SWDATA_DISP_CNT;			//DW ?	;/* �r�v�f�[�^�\���p���[�v�J�E���g */
UNs		SVSW_CHG_FLG;				//DB ?	;/* �f�[�^�`�F���W�t���O�Z�b�g */

//UNs		SV_DISP_BUFF[20];			//DB 20 DUP(?)	;/* �ݒ�l���ԃo�b�t�@�i�`�r�b�h�h�j */
UNl		SV_DISP_BUFF;				//DB 20 DUP(?)	;/* �ݒ�l���ԃo�b�t�@�i�`�r�b�h�h�j */

UNs		SV_DATA_CHG;				//DB ?	;//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
UNs		CSR_TBL_POS_NOW;			//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		SV_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		SW_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		DISP_CHG_FLG;				//DB ?	;/* �\�����]�t���O�Z�b�g */

UNs		SV_DISP_CNT;				//DB ?	;/* �ݒ�l�\���������͏����� */
UNs		SV_ENT_CNT;					//DB ?
UNs		TENKEY_CNT;					//DB ?	;/* ���̓I�[�o�[�H */
UNs		NO_SUPRESU;					//DB ?
UNs		INTER_ROCK_FLG;				//DB ?	;/* �C���^�[���b�N�L��H */
UNs		PATH_WORD_CNT;				//DB ?		;

UNs		SEI_INF_BUFF[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_INF_BUFF1[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_INF_BUFF2[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_WRT_POS;				//DW ?	;/* �\���ʒu */
UNs		SEI_WRT_CNT;				//DW ?		;/* �\�������� */
UNs		SEI_WRT_ADR;				//DW ?		;/* �\�������� */
UNs		IROCK_BUFF[40];				//DW 40 DUP(?)	;
UNs		IROCK_BUFF01[320/2];		//DB 320 DUP(?)	;
UNs		SEI_INF_FLG;				//DB ?
UNs		SEI_INF_FLG_LAST;			//DB ?		;

UNs		GAMEN_WRITE_CNT;			//DB ?		;
//UNs		SEQ_056_WORK[30/2];				//DB 30 DUP(?)	;
UNs		SEQ_044_WORK[30/2];				//DB 30 DUP(?)	;
//UNs		IROCK_NO01;					//DW ?;
//UNs		IROCK_NO02;					//DW ?;
//UNs		IROCK_NO03;					//DW ?;
//UNs		IROCK_NO04;					//DW ?;
//UNs		IROCK_NO05;					//DW ?;
//UNs		IROCK_NO06;					//DW ?;
//UNs		IROCK_NO07;					//DW ?;
//UNs		IROCK_NO08;					//DW ?;
//UNs		IROCK_NO09;					//DW ?;
//UNs		IROCK_NO010;				//DW ?;
//UNs		IROCK_NO011;				//DW ?;
//UNs		IROCK_NO012;				//DW ?;

//UNs		IROCK_NO1_LAST;				//DW ?
//UNs		IROCK_NO01_LAST[30];		//DW 30 DUP(?)	;
UNs		IROC_CHG_FLG;				//DW ?	;
UNs		IROC_CHG_FLG1;				//DW ?	;
UNs		IL_DISP_LAST;				//DB ?
UNs		GAMEN_NO_IROCK;				//DW ?
UNs		SEISAN_FLG;					//DB ?	;
UNs		SEISAN_FLG_LAST;			//DB ?	;
UNs		IROCK_SHR_LAST;				//DB ?
UNs		SVPV_DATA_FLG;				//DB ?
UNs		SOUSA_LEFT_FLG;				//DB ?
UNs		ERR_MONI_LAST1;				//DW ?
UNs		ERR_MONI_LAST2;				//DW ?
UNs		ERR_MONI_LAST3;				//DW ?
UNs		DAN_SOUSA_DAT;				//DW ?
UNs		RULET_DIG_TBL_ADR;			//DW ?
UNs		SEI_COUNT_LAST1;			//DB ?;
UNs		SEI_COUNT_LAST2;			//DB ?;
UNs		SEI_COUNT_LAST3;			//DB ?;
UNs		SEI_COUNT_LAST4;			//DB ?;

//UNs		GAMEN_ON_FLG;				//DB ?
UNs		IL_DISP_FLG;				//DB ?		;/* �h�k�\���t���O���Z�b�g */
UNs		INI_FLG	;					//DB ?
//UNs		SEQ_020_SV_BUFF;			//DB ?
UNs		SEQ_018_SV_BUFF;			//DB ?
UNs		BASE_CLS_CNT;				//DW ?
UNs		SEI_INF_SPATH_CNT;			//DW ?
UNs		SUM_CHK_ERR;				//DB ?
UNs		DAN_NON_GAMEN;				//DB ?
UNs		SV_CHK_ERR;					//DB ?
UNs		SV_CMP_ERR;					//DB ?
UNs		SV_SUM1_ERR;				//DB ?
UNs		SV_SUM2_ERR;				//DB ?
UNs		SV_DPRAM_ERR;				//DB ?

UNs		INCH_DATA_FLG;				//DB ?	;/* INCH�����t���O */

UNs		OP_MESS_DISP_LAST1;			//DB ?	;
UNs		OP_MESS_DISP_LAST2;			//DB ?	;
UNs		OP_MESS_DISP_LAST3;			//DB ?	;

UNs		OFF_SET_MNG_LAST;			//DB ?	;
UNs		OFF_SET_MNG_LAST1;			//DB ?	;
UNs		KOUSEI_MNG_LAST;			//DB ?	;
UNs		KOUSEI_MNG_LAST1;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST1;		//DB ?	;
UNs		SURA_AUTO_MNG_LAST2;		//DB ?	;

UNs		SEIGAMEN_CNT;				//DB ?	;
UNs		SEGAMEN_ADR;				//DW ?	;

UNs		OFF_SET_MNG_LAST2;			//DB ?	;
UNs		OFF_SET_MNG_LAST3;			//DB ?	;
UNs		OFF_SET_MNG_LASTX;			//DB ?	;
UNs		KOUSEI_MNG_LAST2;			//DB ?	;
UNs		YOUBI_LAST;					//DB ?

UNs		PODATA_SET_FLG;				//DB ?	;

UNs		ONOFF_FLG;					//DB ?	;
UNs		ONOFF_LAST1;				//DB ?	;
UNs		ONOFF_LAST2;				//DB ?	;
UNs		ONOFF_LAST3;				//DB ?	;
UNs		ONOFF_LAST4;				//DB ?	;
UNs		ONOFF_LAST5;				//DB ?	;
UNs		ONOFF_LAST6;				//DB ?	;
//UNs		ONOFF_LAST7;				//DB ?	;
//UNs		ONOFF_LAST8;				//DB ?	;
//UNs		ONOFF_LAST9;				//DB ?	;
//UNs		ONOFF_LAST10;				//DB ?	;

UNs		GAMEN_B6_NON_FLG;			//DB ?	;

UNs		INI_POS_ERR_FLG;			//DB ?	;

UNs		PV_ADBAKD_A14;				//DW ?	;

UNs		ENCO_DATA_BCD;				//DW ?	;
UNs		ENCO_DATA_HEX;				//DW ?	;

UNs		OFFSET_END_FLG;				//DB ?	;/* �I�t�Z�b�g���������H */

UNs		MCN_SEQ_LAST1;				//DB ?		;
UNs		MCN_SEQ_LAST2;				//DB ?		;
UNs		MCN_SEQ_LAST3;				//DB ?		;
UNs		MCN_SEQ_LAST4;				//DB ?		;
UNs		MCN_SEQ_LAST5;				//DB ?		;

UNs		MCN_DATA_NO1;				//DB ?		;
UNs		MCN_DATA_NO2;				//DB ?		;
UNs		MCN_DATA_NO3;				//DB ?		;
UNs		MCN_DATA_NO4;				//DB ?		;
UNs		MCN_DATA_NO5;				//DB ?		;

UNs		MCN_REC_FLG;				//DB ?		;

//UNs		GAMEN_DISP_FLG;				//DB ?	;
UNs		GGAMEN_DISP_FLG;			//DB ?	;

UNs		CARA_CHG_FLG;				//DB ?	;
UNs		YOKOBAI_CNT;				//DW ?	;/* ���{�J�E���^ */
UNs		YOKOBAI_ADR;				//DW ?	;/* ���{�A�h���X */
UNs		YOKO_BAI_WORK[32*16];		//DB 32*16 DUP(?)	;/* �f�[�^�����[�N�̈�֓]�� */

UNs		KAN_BANK_NO;				//DB ?		;V05

UNs		GENGO_CHG_LAST;				//DB ?		;
//UNs		GENGO_CHG_LAST1;			//DB ?		;
UNs		WORK_BUFF_NAME[20];			//DW 20 DUP(?);

UNs		BASE_WORK;					//DW ?		;

UNs		KT_DUMMY_01;				//DW ?	;
UNs		KT_DUMMY_02;				//DB ?	;

UNs		DAI_SVDATA_FLG;				//DB ?	;/* �_�C�n�C�g�����L���H */
//UNs		SEQ_030_WK;					//DB ?	;
UNs		SEQ_023_WK;					//DB ?	;

UNs		AUTO_SEQ_LST;				//DB ?	;

UNs		SV_0401_FLG;				//DB 	?	;
UNs		SV_1101_FLG;				//DB ?	;
UNs		SW_1101_FLG;				//DB ?	;
UNs		SW_1102_FLG;				//DB ?	;
UNs		SW_1103_FLG;				//DB ?	;

UNs		CSR_MLD_WORK[32/2];			//DB 32 DUP(?)	;/* �J�[�\�����ړ�����ƕ����� */

UNs		SIT_MOLD3_RCV_BUFF[50];		//DW	50	DUP(?)	;

UNs		TAIKITEN_DAT;				//DW ?	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */	EXTRN	TAIKITEN_DAT		: WORD	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */
UNs		RULET_NOW_LST;				//DW ?	;
UNs		DEG_DISP_LST;				//DW ?	;/* �p�x�ް��ω�����H */
UNl		DEG_DISP_DATA[2];			//DD	?	;
									//DD	?	;

UNs		DEG_LCD_BUFF[32*12];		//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

UNs		STOPTIME_DISP_LST;			//DW ?	;/* �p�x�ް��ω�����H */
UNl		STOPTIME_DISP_DATA[2];		//DD	?	;
									//DD	?	;

UNs		STOPTIME_LCD_BUFF[32*12];	//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

UNs		PFOUT_DATA_BAK;				//DB ?	;

UNs		DAT_LCD_KAN_BAK;			//DB ?	;

UNs		DEG_DISP_FLG;				//DB ?	;
//UNs		STOP_DISP_FLG;				//DB ?	;
UNs		RULET_DISP_FLG;				//DB ?	;/* ���[���b�g�\���n�j */
//UNs		RULET_NON_FLG;				//DB ?	;
UNs		CSR_MOVE_OK_FLG;			//DB ?	;/* �J�[�\���ړ��֎~ */

UNs		SW14_ON_FLG;				//DB ?	;
UNs		SW14_ON_CNT;				//DB ?	;
UNs		SET_KEY_LST;				//DB ?	;

UNs		KIDO_FLG_FLG;				//DB 2 DUP(?)	;/* �P�x�f�[�^�Ǎ����i�[ */
UNs		KIDO_FLG_PV;				//DB ?		;/* �P�x�f�[�^�Ǎ����i�[ */

UNs		GAIBU_RST_LAST;				//DB ?	;
//UNs		GAIBU_RST_LAST1;			//DB ?	;
UNs		GAIBU_RST_LAST2;			//DB ?	;
UNs		GAIBU_RST_LAST3;			//DB ?	;
//UNs		GAIBU_RST_LAST4;			//DB ?	;
//UNs		GAIBU_RST_LAST5;			//DB ?	;
//UNs		GAIBU_RST_LAST6;			//DB ?	;
//UNs		GAIBU_RST_LAST7;			//DB ?	;
//UNs		GAIBU_RST_LAST8;			//DB ?	;

//UNs		GAIBU_CHG_FLG;				//DB ?	;

UNs		TAIKITEN_FLG;				//DB ?	;
UNs		TAIKITEN_LAST;				//DB ?
UNs		TAIKITEN_DATA;				//DW ?
UNs		TAIKI_NOW_POS;				//DW ?	;
UNs		TAIKI_ZEN_POS;				//DW ?	;

UNs		COUNT_HOSEI_ADR;			//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */
UNs		SURA_HOSEI_ADR;				//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */

UNs		SWCHG_DISP_ON_FLG;			//DB ?	;
UNs		SEISAN_SW56_FLG;			//DB ?	;
UNs		SEISAN_SW56_TIM;			//DW ?	;
UNs		OPBAK_UP_LST;				//DB ?	;
UNs		OPBAK_UP_LST1;				//DB ?	;

UNs		SW14_ON1_FLG;				//DB ?	;
UNs		SW14_ON6_FLG;				//DB ?	;
UNs		SW14_ON1_FLG_BAK2;			//DB ?	;
UNs		SW14_ON1_FLG_BAK3;			//DB ?	;
UNs		SW14_ON1_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BACK;			//DB ?	;

UNs		TAIKI_LST;					//DW ?	;

UNs		CAMNAME_INP_CNT;			//DB ?	;
UNs		NAME_CHG_FLG;				//DB ?	;/* ���̕ύX���H */
UNs		CAM_NAME_NO;				//DB ?	;/* �ύX�J�����̔ԍ��Ǎ� */
UNs		SUOERTH_BUFF[3];			//DW 3 DUP(?)	;

UNs		CSR_FLG_CNT_BAK;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		CSR_FLG_CNT_BAK3;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		SV_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */
UNs		SW_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */

UNs		CAMOUT_MUSK;				//DW ?	;/* �ėp�o�̓}�X�N�r�b�g */
UNs		CAMOUT_BIT;					//DW ?	;/* �ėp�o�̓r�b�g */

UNs		GAMEN_NO_CAM;				//DW ?	;
UNs		DAN_WIN_FLG;				//DB ?	;	V01j(INS)
UNs		DAN_CSR_LST;				//DB ?	;

//UNs		SW14_DISP7_NON;				//DB ?	;

UNs		SET_SPM_LST;				//DB ?	;
UNs		KATNAME_INP_CNT;			//DB ?	;/* ���̓J�E���^�[�P */

//UNs		PV_MLDNO1_F0[16];			//DB 16 DUP(?)	;
UNs		PV_MLDNO1_F0;				//DB 16 DUP(?)	;
UNs		PV_MLDNO2_F0[16];			//DB 16 DUP(?)	;

UNs		SINCAM_LST;					//DB ?	;	
UNs		TAIKITEN_FLG_FLG;			//DB ?	;/* ���łɃt���O�𗧂ĂĂ������� */

UNs		CSR_CLS_FLG;				//DB ?	;
UNs		PVCNT_DISP_CNT;				//DB ?	;
UNs		PVALL_FLG;					//DB ?	;
UNs		PVGENNITI_FLG;				//DB ?	;

UNs		CSR_FLG_BUF;				//DW ?	;/*  */
UNs		SV_FLG_BUF;					//DW ?	;/*  */

UNs		ENCO_DATA_HEX1;				//DW ?	;

UNs		RULET_GAKU_FLG;				//DW ?	;
UNs		RULET_GAKU_LST;				//DB ?	;

UNs		SEI_ON6_LST1;				//DB ?	;
UNs		SEI_ON6_LST2;				//DB ?	;
UNs		SEI_ON6_LST3;				//DB ?	;
UNs		SEI_ON6_LST4;				//DB ?	;
UNs		SEI_ON1_LST;				//DB ?	;

UNs		DAN_GAMEN_NON;				//DB ?	;
UNs		SEL_GAMEN_NON;				//DB ?	;
UNs		CAM_GAMEN_NON;				//DB ?	;
UNs		EJE_GAMEN_NON;				//DB ?	;
UNs		MIS_GAMEN_NON;				//DB ?	;
UNs		ROT_GAMEN_NON;				//DB ?	;

UNs		ROT1_GAMEN_NON;				//DB ?	;
UNs		ROT2_GAMEN_NON;				//DB ?	;
UNs		ROT3_GAMEN_NON;				//DB ?	;

UNs		CSR_FLG_CNT_LST;			//DW ?	;/* �J�[�\���ԍ��Z�b�g */

UNs		POWRE_OK_FLG;				//DW ?	;

UNs		PVDATA_NON;					//DB ?	;

UNs		CAR_ROM_SEG;				//DW ?	;

UNs		PV_SUM_CHK;					//DW ?	;
UNs		EE_SUM_CHK;					//DW ?	;

UNs		POWER_DOWN_FLG;				//DB ?	;

UNs		SW56_UPTOP_FLG;				//DB ?	;'98-08-05

//V01u	UNs		KAT_DATCHG_FLG;				//DB ?	;
UNs		KAT_DATCHG_FLG_DUMMY;				//DB ?	;
UNs		KAT_CNTCHG_FLG;				//DB ?	;

UNs		SW14_DISP7_DANNON;			//DB ?	;'98-08-31/*�X���C�h�ȊO�Ȃ��Ƃ��̓W�����v  */
//UNs		OP_NON_FLG;					//DB ?	;

UNs		SYS_HIGHSPM_B1;				//DW ?	;V01a
UNs		SYS_LOWSPM_B1;				//DW ?	;V01a
UNs		RULET_HIGH_FLG;				//DB ?	;/* �������[���b�g�`��t���O�Z�b�g */
UNs		RULET_HIGH_LST;				//DB ?	;
UNs		CB1_SPMDAT_PVV;				//DW ?	;/* �ǂݍ��� */

UNs		PV_TLINKSMP_DAT;			//DW ?	;V03j

UNs		ENC_SPD_CNT;				//DW ?		;
UNl		ENCSPD_ADD;					//DD	?		;
UNs		ENCSPD_BF[20];				//DW	10	DUP (?)	;
									//DW	10	DUP (?)	;

UNs		CSR_DAN_CSR_LST;			//DW ?		;V01a/* �i�����SW56���ݽ��ݾٗp */

UNs		SW56_MUSK_FLG;				//DW ?		;V01b

UNs		MLD_100_GNO;				//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
//UNs		MLD_100_NO;					//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
UNs		MLD_100_FLG;				//DB ?		;MLD100/* �^�Ǘ��t���O������ */
//UNs		MLD_100_CARD_FLG;			//DB ?		;MLD100/*  */

UNs		MEM_ADR;					//DW ?	;
UNs		MEM_BNK;					//DW ?	;
UNs		MLD_WRITE_BNK;				//DB ?	;

UNs		CSR_POS_G15;				//DB ?	;/*  */

UNs		CSR_MOVE_NON;				//DB ?	;/* �J�[�\���͓����Ȃ��H */

UNs		MLD100_INI_FLG;				//DB ?	;

UNs		DAN_DAN_FLG;				//DB ?	;

UNs		CSR_FLG_CNT_BACK;			//DW ?		;
UNs		WINDOW_NO_BACK;				//DW ? 		;

UNs		DAN_KEY_FLG;				//DB ?		;

UNs		G07_WIN_FLG;				//DB ?		;

UNs		FILCK_CNT;					//DW ?			;
UNs		FILCK_STEP1_FLG;			//DB ?			;
UNs		FILCK_STEP2_FLG;			//DB ?			;
UNs		FILCK_STEP3_FLG;			//DB ?			;

UNs		NEXT_READ_NO;				//DW ?	;/* ���^�ԍ��ݒ�l */

UNs		KEY_DOWN14_FLG;				//DB ?	;/* �j�d�x����������t���O���Z�b�g */
UNs		SW14_MUSK_FLG;				//DW ?	;

UNs		SW14_MUSK_FLG_SW2;			//DW ?	;

UNs		CSR_G07_NO1;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */
UNs		CSR_G07_NO2;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */

UNs		SYS_SPMPM_B1P;				//DW ?	;
UNs		SYS_SPMPM_B1M;				//DW ?	;

//UNs		SEQ_022_FLG;				//DB ?	;
UNs		SEQ_019_FLG;				//DB ?	;

UNs		SYS_MISSEL_SV;				//DB ?		;

UNs		SURA_SEL_LST;				//DB ?	;

UNs		DAN_CLS_CNT;				//DW ?		;2000-07-04/* �\���������J�E���^ */

UNs		SEI_GAI_LST;				//DB ?
UNs		GENG_SEQ_LST;				//DB ?
UNs		NEXT_MLDSEQ_FLG;			//DB ?		;2001-08-07 /*�V�[�P���X�p���^�f�[�^�ǂݍ��݃t���O�n�m*/

UNs		PV_CAMSW1_C1[4];		//DB 8 DUP(?)	;BIT_1
UNs		PV_CAMSW2_C1[4];		//DB 8 DUP(?)	;BIT_2
UNs		PV_CAMSW3_C1[4];		//DB 8 DUP(?)	;BIT_3
UNs		PV_CAMSW4_C1[4];		//DB 8 DUP(?)	;BIT_4
UNs		PV_CAMSW5_C1[4];		//DB 8 DUP(?)	;BIT_5
UNs		PV_CAMSW6_C1[4];		//DB 8 DUP(?)	;BIT_6
UNs		PV_CAMSW7_C1[4];		//DB 8 DUP(?)	;BIT_7
UNs		PV_CAMSW8_C1[4];		//DB 8 DUP(?)	;BIT_8
UNs		PV_CAMSW9_C1[4];		//DB 8 DUP(?)	;BIT_9
UNs		PV_CAMSWA_C1[4];		//DB 8 DUP(?)	;BIT_A
UNs		PV_CAMSWB_C1[4];		//DB 8 DUP(?)	;BIT_B
UNs		PV_CAMSWC_C1[4];		//DB 8 DUP(?)	;BIT_C
UNs		PV_CAMSWD_C1[4];		//DB 8 DUP(?)	;BIT_D
UNs		PV_CAMSWE_C1[4];		//DB 8 DUP(?)	;BIT_E
UNs		PV_CAMSWF_C1[4];		//DB 8 DUP(?)	;BIT_F

UNs		PV_CAMNA01_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P���� */
UNs		PV_CAMNA02_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q���� */
UNs		PV_CAMNA03_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���R���� */
UNs		PV_CAMNA04_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���S���� */
UNs		PV_CAMNA05_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���T���� */
UNs		PV_CAMNA06_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���U���� */
UNs		PV_CAMNA07_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���V���� */
UNs		PV_CAMNA08_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���W���� */
UNs		PV_CAMNA09_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���X���� */
UNs		PV_CAMNA10_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�O���� */
UNs		PV_CAMNA11_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�P���� */
UNs		PV_CAMNA12_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�Q���� */
UNs		PV_CAMNA13_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�R���� */
UNs		PV_CAMNA14_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�S���� */
UNs		PV_CAMNA15_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�T���� */
UNs		PV_CAMNA16_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�U���� */
UNs		PV_CAMNA17_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�V���� */
UNs		PV_CAMNA18_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�W���� */
UNs		PV_CAMNA19_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�X���� */
UNs		PV_CAMNA20_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q�O���� */

//UNs		PV_EJECT1_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT2_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT3_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT4_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT5_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT6_NAME[4];		//DB 10 DUP(?)   ;

UNs		PV_KOUMOKU1_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU2_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU3_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU4_NAME[8];	//DB 16 DUP(?)	;

UNs		PV_KINOU01_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU02_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU03_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU04_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU05_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU06_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU07_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU08_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU09_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU10_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU11_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU12_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU13_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU14_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU15_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU16_NAE[8];		//DB 16 DUP(?)	;


UNs		SEQ_PAR_101_BAK;		/* V00p */
UNs		disp_stg_sel_bak;		/* V00p */
UNs		WINDOW_NO_bak;			/* V00p */
UNs		PV0_PAR_A_CHAR;			/* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
UNs		PV0_PAR_B_CHAR;			/* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
UNs		PV0_TBL_A_CHAR;			/* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
UNs		PV0_TBL_B_CHAR;			/* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
UNs		PV0_INTER_VER2;			/* V00p */    /* ����ۯ��ް�ޮ� ������׸� ASCII */
UNs		PV0_DEFULT_VER2;		/* V00p */    /* �����l�ް��ް�ޮ� ������׸� ASCII */
UNs		PV0_SEQ_VER2;			/* V00p */    /* ���ݽ�ް�ޮ� ������׸� ASCII */
UNl		PV0_NOW_POSI000;		/* V00q */    /* �����㍂��PV */
UNl		PV0_DYHITO_POS;			/* V00q */    /* �����ʒuPV */
UNl		PV0_SLIDE_POS;			/* V01  */    /* ���Y����PV */
UNl		PV0_NOWPOSI_SLIDE;		/* V01  */    /* ���Y����or�����㍂PV */

UNs		GAIBU_RST_BAK;			/* V00t */

UNs		PV0_MONALM_P01;
UNs		PV0_MONALM_P02;
UNs		PV0_MONALM_P03;
UNs		PV0_MONALM_P04;
UNs		PV0_MONALM_A01;
UNs		PV0_MONALM_A02;
UNs		PV0_MONALM_A03;
UNs		PV0_MONALM_A04;
UNs		PV0_MONALM_A05;
UNs		PV0_MONALM_A06;
UNs		PV0_MONALM_A07;
UNs		PV0_MONALM_A08;
UNs		PV0_MONALM_B01;
UNs		PV0_MONALM_B02;
UNs		PV0_MONALM_B03;
UNs		PV0_MONALM_B04;
UNs		PV0_MONALM_B05;
UNs		PV0_MONALM_B06;
UNs		PV0_MONALM_B07;
UNs		PV0_MONALM_B08;
UNl		PV0_MONALM_C01;
UNl		PV0_MONALM_C02;
UNl		PV0_MONALM_C03;
UNl		PV0_MONALM_C04;
UNl		PV0_MONALM_C05;
UNl		PV0_MONALM_C06;
UNl		PV0_MONALM_C07;
UNl		PV0_MONALM_C08;
UNs		PV0_MONALM_B01_SIGN;
UNs		PV0_MONALM_B02_SIGN;
UNs		PV0_MONALM_B03_SIGN;
UNs		PV0_MONALM_B04_SIGN;
UNs		PV0_MONALM_B05_SIGN;
UNs		PV0_MONALM_B06_SIGN;
UNs		PV0_MONALM_B07_SIGN;
UNs		PV0_MONALM_B08_SIGN;
UNs		PV0_MONALM_C01_SIGN;
UNs		PV0_MONALM_C02_SIGN;
UNs		PV0_MONALM_C03_SIGN;
UNs		PV0_MONALM_C04_SIGN;
UNs		PV0_MONALM_C05_SIGN;
UNs		PV0_MONALM_C06_SIGN;
UNs		PV0_MONALM_C07_SIGN;
UNs		PV0_MONALM_C08_SIGN;

UNs		MOTION_SV_CHG_CANCEL;			/* V01d */

UNs		TAIKIKAKU_CHG_FLG;				/* V01i */
UNs		GAMNE_REDISP_COD;				/* V01i */

UNs		SEQ_PAR_107_BAK;				/* V01j */
UNs		SEQ_PAR_427_CHG;				/* V01j */
UNs		SEQ_PAR_427_ONE;				/* V01j */
UNs		SEQ_PAR_427_OFE;				/* V01j */
UNs		SEQ_PAR_427_BAK;				/* V01j */
UNs		autokana_sw56_bak;				/* V01j */
UNs		ADC_DISP_FLG;					/* V01j */
UNs		ADC_CHG_LST;					/* V01j */
UNs		ADC_CHG_LST1;					/* V01j */
UNs		ADC_CHG_LST2;					/* V01j */
UNs		ADC_CHG_LST3;					/* V01j */
UNs		ADC_CHG_LST4;					/* V01j */
UNs		ADC_CHG_LST5;					/* V01j */
UNs		ADC_CHG_LST2_2;					/* V01j */
UNs		ADC_MODE_FLG;					/* V01j */
UNs		ADC_STEP_FLG;					/* V01j */
UNs		ADC_STPCHG_FLG;					/* V01j */
UNs		ADC_FILCK_LST;					/* V01j */
UNs		ADC_SW2_FLG;					/* V01j */
UNs		ADC_SW34_FLG;					/* V01j */
UNs		ADC_SW5_FLG;					/* V01j */
UNs		ADC_SW6_FLG;					/* V01j */
UNs		SW14_DISP7_NON;					/* V01j */
UNs		ADC_STEP_NO[4];					/* V01j */
UNs		ADC_STEP_NO_LAST[4];			/* V01j */
UNs		step_flick_flg;					/* V01j */
UNs		step_flick_flg_bak;				/* V01j */
UNs		step_flick_cnt;					/* V01j */

UNl		CAR_LNG_KAJ_AREA;				/* V01k */
UNs		SYO_LNG_KAJ_CNT;				/* V01k */

UNl		PV0_KAGEN_POSITIONER;				/* V01l_b */

UNs		SYO_LNG_SUR_CNT;				/* V01m */

UNs		DEB_WORD_FLG1;					/* V01n_b */
UNs		DEB_WORD_FLG2;					/* V01n_b */
UNs		DEB_WORD_FLG3;					/* V01n_b */
UNs		DEB_WORD_FLG4;					/* V01n_b */
UNs		DEB_WORD_FLG5;					/* V01n_b */
UNs		DEB_WORD_FLG6;					/* V01n_b */
UNs		DEB_WORD_FLG7;					/* V01n_b */
UNs		DEB_WORD_FLG8;					/* V01n_b */
UNs		DEB_WORD_FLG9;					/* V01n_b */
UNs		DEB_WORD_FLG10;					/* V01n_b */
UNs		DEB_WORD_FLG11;					/* V01n_b */
UNs		DEB_WORD_FLG12;					/* V01n_b */
UNs		DEB_WORD_FLG13;					/* V01n_b */
UNs		DEB_WORD_FLG14;					/* V01n_b */
UNs		DEB_WORD_FLG15;					/* V01n_b */
UNs		DEB_WORD_FLG16;					/* V01n_b */

//��������������	�ȉ��A�r�h�s�|�S�Œǉ�		��������������
UNl		DEBUG_CNT;

UNs		CSR_BAK_M_LEN;	
UNs		CSR_BAK_X_POS;	
UNs		CSR_BAK_Y_POS;	
UNs		CSR_BAK_C_COL;	
UNs		CSR_BAK_B_COL;	
UNs		CSR_BAK_SIZE;	
UNs		*CSR_BAK_G_P;	

GAMENn_HEAD_st	GAMENn_HEAD;
DISP_INFO_st	DISP_INFO;

UNl		CHR_TABLE_ADR;			// �L�����N�^�e�[�u���̕�����L�����N�^�擪�A�h���X
UNl		CSR_TABLE_ADR;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^�擪�A�h���X
UNl		SWL_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^�擪�A�h���X
UNl		S56_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^�擪�A�h���X
UNl		MES_TABLE_ADR;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^�擪�A�h���X
UNl		S56U_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U��i�L�����N�^�擪�A�h���X
UNl		SPE_TABLE_ADR;			// �L�����N�^�e�[�u���̓��ʃL�����N�^�擪�A�h���X

UNl		GAMENN_MOJ_INF_ADR;		// ��ʂ��̕�������̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_CSR_INF_ADR;		// ��ʂ��̃J�[�\�����̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_SVP_INF_ADR;		// ��ʂ��̐ݒ�l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_PVP_INF_ADR;		// ��ʂ��̎����l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_SWL_INF_ADR;		// ��ʂ��̂r�v�|�k�`�l�o�̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_GRP_INF_ADR;		// ��ʂ��̃O���t�B�b�N���̐擪�A�h���X	�i��ʂ���\������Ƃ��ɎZ�o�j

UNs		CHRTBL_CHR_CNT;			// �L�����N�^�e�[�u���̕�����L�����N�^��
UNs		CHRTBL_CSR_CNT;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^��
UNs		CHRTBL_SWL_CNT;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^��
UNs		CHRTBL_S56_CNT;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
UNs		CHRTBL_MES_CNT;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^��
UNs		CHRTBL_S56U_CNT;		// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
UNs		CHRTBL_SPE_CNT;			// �L�����N�^�e�[�u���̓��ʃL�����N�^��

UNs		GAMENn_SCR_COL;			//��ʂ̽�ذݐF�iWindow��\�����ĕς��Ȃ����Ɓj

UNs		PVW_ZURE_PLS_SIN;		//���Խ�ڎ�������
UNs		PVW_ZURE_RNA_SIN;		//���Խ���Ʊ����
UNs		PVW_ZURE_PLS;			//���Խ�ڎ���
UNs		PVW_ZURE_RNA;			//���Խ���Ʊ
UNs		PVW_BAKORG_SIN1;		//�ޯ����ߎ�������
UNs		PVW_BAKORG_SIN2;		//�ޯ����ߎ�������
UNl		SVBW_BAKORG_PLS1;		//�Ʊ��ʒu��ٽ	COP2
UNl		SVBW_BAKORG_PLS2;		//�Ʊ��ʒu��ٽ	COP2

UNs		GAM_CHG_WIN_NO_BAK;		/* V04a */

UNb		OP_STATUS;				//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H		//V01e
UNb		OP_STATUS_DUM;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H		//V01e

UNb		MEM_ARI;				//DB	?		; OP��:A5H		//V05h

UNs		PV0_CB_C_VER[6];		//ASCII�ް� (1WORD�ŷ�׸����� 6char) SH4-->
UNs		PV0_PAR_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
UNs		PV0_TBL_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)

//;	******** 2007/12/12 ***********
UNs		PV0_IPM_ADR0;			//IP���ڽ(���)
UNs		PV0_IPM_ADR1;			//IP���ڽ(���)
UNs		PV0_IPM_ADR2;			//IP���ڽ(���)
UNs		PV0_IPM_ADR3;			//IP���ڽ(���)

//;	******** 2009/07/14 ***********
UNs		IROCK_OUT_NO[8];			/* ����ۯ������ԍ�		*/
UNb		IROCK_CHAR[8][8];			/* ����ۯ������ԍ��ɑ΂��鷬׸�����		*/

//;	******** 2009/08/-- *********** V05o(INS)	�����g�`�\���p
UNs		WAVE_SAMP_DTP[2];					//���������ݸޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
UNs		WAVE_TRND_DTP[2];					//��������ޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
WAVE_SAMP_DATA_ST	WAVE_SAMP_DATA[501];	//���������ݸޔg�`�p�ް�
WAVE_TRND_DATA_ST	WAVE_TRND_DATA[5001];	//��������ޔg�`�p�ް�
WAVE_SAMP_DOT_ST	WAVE_SAMP_DOT[501];		//���������ݸޔg�`�p�ް�
WAVE_TRND_DOT_ST	WAVE_TRND_DOT[5001];	//��������ޔg�`�p�ް�
UNs		CSR_PVSAMP[2];						//���������ݸޔg�`��ʂ̶��وʒu	+0:�ŐV  +1:�O��l
UNs		CSR_PVTRND[2];						//��������ޔg�`��ʂ̶��وʒu		+0:�ŐV  +1:�O��l
UNs		PW_Key_up[4];						//�����g�`��ʗp�������ω�	(5ms�����݂ŊĎ�)
UNs		PW_Key_dn[4];						//�����g�`��ʗp��������ω�	(5ms�����݂ŊĎ�)
UNs		PW_Key_last[4];						//�����g�`��ʗp���O��l		(5ms�����݂ŊĎ�)
UNs		PW_Key_tim02[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
UNs		PW_Key_tim30[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
UNs		PV0_SMPCSR_KJT;						//���وʒu�̍��v�׏d
UNs		PV0_SMPCSR_KJL;						//���وʒu�̍��׏d
UNs		PV0_SMPCSR_KJR;						//���وʒu�̉E�׏d
UNs		PV0_SMPCSR_AGL;						//���وʒu�̊p�x
UNl		PV0_SMPCSR_RNA1;					//���وʒu�̽ײ�ވʒu
UNl		PV0_SMPCSR_RNA2;					//���وʒu�̽ײ�ވʒu
UNs		PV0_SMPCSR_SEQ0;					//���وʒu�̼��ݽ
UNs		PV0_SMPCSR_SEQ1;					//���وʒu�̼��ݽ
UNs		PV0_SMPCSR_TIM;						//���وʒu�̎���
UNs		PV0_SMPCSR_POS;						//���وʒu���߲��
UNl		PV0_TRDCSR_RNAU;					//�ײ�ޏ�����o�ʒu
UNl		PV0_TRDCSR_RNAD;					//�ײ�މ������o�ʒu
UNs		PV0_TRDCSR_KJT;						//���وʒu�̍��v�׏d
UNs		PV0_TRDCSR_KJL;						//���وʒu�̍��׏d
UNs		PV0_TRDCSR_KJR;						//���وʒu�̉E�׏d
UNl		PV0_TRDCSR_RNA1;					//���وʒu�̽ײ�ވʒu
UNl		PV0_TRDCSR_RNA2;					//���وʒu�̽ײ�ވʒu
UNs		PV0_TRDCSR_TIM;						//���وʒu�̎���
UNs		PV0_TRDCSR_POS;						//���وʒu���߲��
UNs		PV0_TRDCSR_POSL;					//�-�͈ٔ�
UNs		PV0_TRDCSR_POSR;					//�-�͈ٔ�

//;	******** 2010/08/10~ *********** V05r(INS)
UNs		SEIDOU_SEQ_LST;						//
UNs		sys_1min_cnt;						//1min����
//UNs		PVTIM_seidouseinou_inter;			//�������\��������������(1min�޸�������)
//UNs		PVTIM_seidouseinou_yokok;			//�������\�����\�����(1min�޸�������)
UNs		SYO_HOS_KAJ_CNT;
UNs		PV0_INTER_TIM;						//�������\��������������(1h�޸�������)

//;	******** 2010/08/31~ *********** V06 (INS)
UNl		INTR_DAT_OFS;
UNl		INIT_DAT_OFS;
UNl		ALL_CHR_TBL_OFS;
UNl		GAM_INF_TBL_OFS;
UNs		EcoMeter_bit;
UNs		PV0_EPMCSR_HOR;						//�d�̓��j�^�J�[�\���ʒu�̎���
UNs		PV0_EPMCSR_MIN;						//�d�̓��j�^�J�[�\���ʒu�̕�
UNl		PV0_EPMCSR_UEP;						//�d�̓��j�^�J�[�\���ʒu�̏���d�͗�
UNl		PV0_EPMCSR_KEP;						//�d�̓��j�^�J�[�\���ʒu�̉񐶓d�͗�
UNl		PV0_EPMCSR_TEP;						//�d�̓��j�^�J�[�\���ʒu�̗݌v�l
UNl		PV0_EPML_SCRH;						//�d�̓��j�^�O���t���チ����
UNl		PV0_EPML_SCRM;						//�d�̓��j�^�O���t����������
UNl		PV0_EPML_SCRL;						//�d�̓��j�^�O���t����������
UNl		PV0_EPMR_SCRH;						//�d�̓��j�^�O���t�E�チ����
UNl		PV0_EPMR_SCRM;						//�d�̓��j�^�O���t�E��������
UNl		PV0_EPMR_SCRL;						//�d�̓��j�^�O���t�E��������
UNl		PV0_EPM_KWH[20][3];					//�d�̓��j�^�p�O���t�f�[�^
UNs		EPM_CSR[2];							//�d�̓��j�^�p�J�[�\���ʒu
UNs		EPM_TIM_BAK;						//�P�ʎ���
UNl		EPM_GRP_MXL;						//�_�O���t�ő�l�ς�����H
UNl		EPM_GRP_MXR;						//�܂���O���t�ő�l�ς�����H
UNs		sys_1sec_cnt;						//1sec����

//UNl		EPM_SEC_60ADD[2];					//����d�͗� 60sec�ώZ(kWs)
//UNs		EPM_SEC_60CNT;
//UNl		EPM_HOR_BUF[24*60][2];				//����d�͗� 1440��(kWs)
//UNs		EPM_HOR_POI;
UNs		EPM_GAMEN_RIF;						//�d�̓��j�^��ʃ��t���b�V���t���O

UNl		PV0_SMPCSR_EP;						//�����ݸޔg�`��ʶ��وʒu�̏u���d��
int		PV0_SMPCSR_EP_SIN;					//�����ݸޔg�`��ʶ��وʒu�̏u���d��		//V06a
UNl		PV0_TRDCSR_EP;						//����ޔg�`���   ���وʒu�̓d�͗�

UNs		SEIDOU_DSP_LST;

UNs		PV0_INTER_VER1;						/* ����ۯ��ް�ޮ� ���l */
UNs		PV0_DEFULT_VER1;					/* �����l�ް��ް�ޮ� ���l */

UNs		PV0_EPMDAT_SIN;						//�����ݸޔg�`��ʂ̓d�͒l����BIT			//V06a
UNs		EPM_TOTAL_INF;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
UNs		EPM_TLINF_BAK;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
UNs		EPM_CLR_TIM;						//�d����������ް��ر���						//V06a
UNs		EPM_CLR_FLG;						//�d������ر��t�׸�						//V06a
UNs		EPM_GAMRIF_CNT;						//�d����������گ�����ݸ޶ݳ�				//V06a

UNs		SV0_EP_AVE;


UNl		EPM_SEC_2_MESMIN_ADD[2];
UNs		EPM_SEC_MESMIN_CNT;

//V06b	UNl		EPM_05MIN_BUF[5/5][2] ;
//////	UNl		EPM_10MIN_BUF[10/5][2];
//////	UNl		EPM_15MIN_BUF[15/5][2];
//////	UNl		EPM_20MIN_BUF[20/5][2];
//////	UNl		EPM_25MIN_BUF[25/5][2];
//////	UNl		EPM_30MIN_BUF[30/5][2];
//////	UNl		EPM_35MIN_BUF[35/5][2];
//////	UNl		EPM_40MIN_BUF[40/5][2];
//////	UNl		EPM_45MIN_BUF[45/5][2];
//////	UNl		EPM_50MIN_BUF[50/5][2];
//////	UNl		EPM_55MIN_BUF[55/5][2];
//////	UNl		EPM_60MIN_BUF[60/5][2];
UNl		EPM_05MIN_BUF[5][2] ;
UNl		EPM_10MIN_BUF[10][2];
UNl		EPM_15MIN_BUF[15][2];
UNl		EPM_20MIN_BUF[20][2];
UNl		EPM_25MIN_BUF[25][2];
UNl		EPM_30MIN_BUF[30][2];
UNl		EPM_35MIN_BUF[35][2];
UNl		EPM_40MIN_BUF[40][2];
UNl		EPM_45MIN_BUF[45][2];
UNl		EPM_50MIN_BUF[50][2];
UNl		EPM_55MIN_BUF[55][2];
UNl		EPM_60MIN_BUF[60][2];

UNs		EPM_05MIN_POI;
UNs		EPM_10MIN_POI;
UNs		EPM_15MIN_POI;
UNs		EPM_20MIN_POI;
UNs		EPM_25MIN_POI;
UNs		EPM_30MIN_POI;
UNs		EPM_35MIN_POI;
UNs		EPM_40MIN_POI;
UNs		EPM_45MIN_POI;
UNs		EPM_50MIN_POI;
UNs		EPM_55MIN_POI;
UNs		EPM_60MIN_POI;

UNl		EPM_05MON_BUF[20][2];
UNl		EPM_10MON_BUF[20][2];
UNl		EPM_15MON_BUF[20][2];
UNl		EPM_20MON_BUF[20][2];
UNl		EPM_25MON_BUF[20][2];
UNl		EPM_30MON_BUF[20][2];
UNl		EPM_35MON_BUF[20][2];
UNl		EPM_40MON_BUF[20][2];
UNl		EPM_45MON_BUF[20][2];
UNl		EPM_50MON_BUF[20][2];
UNl		EPM_55MON_BUF[20][2];
UNl		EPM_60MON_BUF[20][2];

UNs		EPM_05MON_POI;
UNs		EPM_10MON_POI;
UNs		EPM_15MON_POI;
UNs		EPM_20MON_POI;
UNs		EPM_25MON_POI;
UNs		EPM_30MON_POI;
UNs		EPM_35MON_POI;
UNs		EPM_40MON_POI;
UNs		EPM_45MON_POI;
UNs		EPM_50MON_POI;
UNs		EPM_55MON_POI;
UNs		EPM_60MON_POI;

//;	******** 2010/12/06 *********** V06b (INS)
UNs		rulet_taiki_pos1;			//���]�A�U��q���̑ҋ@�_
UNs		rulet_taiki_pos2;			//		�U��q���̑ҋ@�_
UNl		SV0_TAL1_CNT;				//İ�ٶ����C���l
UNl		SV0_LOT1_CNT;				//ۯĶ���1�C���l
UNl		SV0_LOT2_CNT;				//ۯĶ���2�C���l

//;	******** 2011/01/02 *********** V06c (INS)
UNs		SV0_WORKER_COD_BAK	;		//��ƎҺ��ޑޔ�
UNl		SV0_ORDER_COD_BAK	;		//���Ժ��ޑޔ�
UNl		SV0_PLAN_CNT_BAK	;		//�v�搔�ޔ�
UNs		SV0_WORKER_COD		;		//��ƎҺ���
UNl		SV0_ORDER_COD		;		//���Ժ���
UNl		SV0_PLAN_CNT		;		//�v�搔

UNs		SV0_WORK_STR_FLG		;	//��ƊJ�n�׸ށito C/B�p�j
UNs		SV0SP_WORKER_COD	;		//��ƊJ�n����ƎҺ���
UNl		SV0SP_ORDER_COD		;		//��ƊJ�n�����Ժ���
UNl		SV0SP_PLAN_CNT		;		//��ƊJ�n���v�搔
UNl		SV0SP_BAD_CNT		;		//��ƊJ�n���s�ǐ�
UNs		SV0SP_KATA_NO		;		//��ƊJ�n���^�ԍ�
UNs		SV0SP_KATA_NAME[7]	;		//��ƊJ�n���^����
UNs		SV0SP_KATA_MEMO[7]	;		//��ƊJ�n���^����

UNs		SV0_WORK_STP_FLG		;	//��ƏI���׸ށito C/B�p�j
UNs		SV0SR_WORKER_COD	;		//��ƏI������ƎҺ���
UNl		SV0SR_ORDER_COD		;		//��ƏI�������Ժ���
UNl		SV0SR_PLAN_CNT		;		//��ƏI�����v�搔
UNl		SV0SR_BAD_CNT		;		//��ƏI�����s�ǐ�
UNs		SV0SR_KATA_NO		;		//��ƏI�����^�ԍ�
UNs		SV0SR_KATA_NAME[7]	;		//��ƏI�����^����
UNs		SV0SR_KATA_MEMO[7]	;		//��ƏI�����^����

UNs		KAT_RD_CSR_POS	;			//�^�Ǐo������CSR_TBL_POS_NOW

//;	******** 2012/09/24 *********** V06m (INS)
UNs		DIEH_OFS_FLG;
UNs		FURIKO_FLG;

//;	******** 2012/10/15 *********** V06n (INS)
UNl		SV0_RNAPOS_MAXO;
UNl		SV0_RNAPOS_MINO;
UNs		SV0_DAIHAI_LNG1O;
UNs		SV0_DAIHAI_LNG2O;
UNs		MOT_MODE_BAK;

//;	******** 2013/02/18 *********** V06p (INS)
UNs		PV0_CKSPD_OVBIT;
UNs		PV0_KATRD_BIT;
UNs		TEST_SEQ;
UNs		FURIKO_SEQ_LST;


/***	END		***/