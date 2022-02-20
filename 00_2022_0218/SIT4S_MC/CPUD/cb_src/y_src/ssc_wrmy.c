//	*******************************************
//	***					***
//	***	���[�N��������`		***
//	***					***
//	*******************************************
#include	"cm_equ1.h"
#include	"ssc_ver1.h"

#pragma section	wkram1	/* �����=����Bwkram1 */
S4b	saito_c_ram_top;


U2b	TINT3_10MS_CNT;		//

//	***********************************
//	***	��M�ُ�		***
//	***********************************
S2b	rcv2_err_hard_INTflg1;	// ʰ�ވُ�
S2b	rcv2_err_hard_INTflg2;	// ʰ�ވُ�
S2b	rcv2_err_hard_INTflg3;	// ʰ�ވُ�
S2b	rcv2_err_data_flg1;	// �ް��ُ�(���g�p)
S2b	rcv2_err_hard_sts1;	// �ڍ� �ُ���e
S2b	rcv2_err_hard_sts2;	// �ڍ� �ُ���e
S2b	rcv2_err_hard_sts3;	// 
S2b	rcv2_err_data_sts1;	//(���g�p)
S2b	rcv2_err_OverRunCnt;	//
S2b	rcv2_err_FRPRErrCnt;	//�ڰсE���è
S2b	rcv2_err_elseErrCnt;	//�ڰсE���è

//	***********************************
//	***	�����M		***
//	***********************************
S2b	rcv2_data_INcnt;//��M�ް��� ��M��̧����
S2b	rcv2_data_cnt;//�������ׂ��������ЯĂ�����������o
//S1b	rcv2_data_buf[32];
S2b	rcv2_data_buf[32];//���E���������ɂ��Ă���

//	***********************************
//	***	���M			***
//	***********************************
//S1b	send2_data_buf[32];
S2b	send2_data_buf[32];//���E���͋����ɂ��Ă���
//	***********************************
//	***	����M�Ǘ�		***
//	***********************************
S2b	rcv2_event_flg;	//main-->bit0=1  2ms:bit1(�����J�n),bit7(����)
S2b	send2_event_flg;//main-->bit0=1  2ms:bit1(�����J�n),bit7(����)




//	*** V_CTRL�ł�DPRAM�ɒ�`���Ă��� ***
S4b	PV1_SCRW_POS[4];			//;@�g�psh->H8 ->�\��	[�񑗗L��1CH �̂�]

//	*** V_CTRL�ł�WORKRAM�ɒ�`���Ă��� ***
S4b	PV0_SCRW_POS[4];			//;



//	*******************************************
//	***	�ُ�֌W�̃��[�N�q�`�l		***
//	*******************************************

U2b	ERR_CHK_OK_FLG;			//;�ُ폈���J�n�׸�

U2b	ER_SQRAM_WK1[12+8+10];	//
U2b	ER_SQRAM_WK2[12+8+10];	//
U2b	SH4_SQERRAM[12+8+10];	//
U2b	DBG_ERRCHK_NASI[12+8+10];	// �����Ȃ�

U2b	ER_SFTSW_CHG_OLD;	//

U4b	FROM_SUMCHK_CODE;		// FROM SUM CODE


U2b	SFTSW_ERR_TM;		//
U2b	BTNER_ERR_TM;		//
U2b	NCHSW_ERR_TM1;		//
U2b	NCHSW_ERR_TM2;		//
U2b	VLVER11_ERR_TM;		//
U2b	VLVER12_ERR_TM;		//
U2b	VLVER21_ERR_TM;		//
U2b	VLVER22_ERR_TM;		//
U2b	VLVER31_ERR_TM;		//
U2b	VLVER32_ERR_TM;		//
U2b	CMP2_ERR_TM2;		//
U2b	FSFT_TRERR_TM;		//
U2b	RSFT_TRERR_TM;		//



U2b	WPAR1_SFTSWER_TM;	//
U2b	WPAR1_BTNER_TM;		//
U2b	WPAR1_MODSER_TM1;	//
U2b	WPAR1_MODSER_TM2;	//
U2b	WPAR1_VLVER11_TM1;	//
U2b	WPAR1_VLVER12_TM1;	//
U2b	WPAR1_VLVER21_TM1;	//
U2b	WPAR1_VLVER22_TM1;	//
U2b	WPAR1_VLVER31_TM1;	//
U2b	WPAR1_VLVER32_TM1;	//
U2b	WPAR1_CMPER2_TM;	//
U2b	WPAR1_FSFTTRER_TM;	//
U2b	WPAR1_RSFTTRER_TM;	//



U2b	REMOTE_ERR_CHKTM;	//


U2b ROM_SYSPAR_ERRADR;	//


//	***************************************************
//	***	�Z���t�`�F�b�N�֌W�̃��[�N�q�`�l	***
//	***************************************************
U2b	SELF_CHK_FLG;		//;��������� CHECK
U2b	SELF_ACT_FLG;		//;��������� CHECK

U2b	SELF_HAND_FLG1;		//; �����̏���׸� SRAM
U2b	SELF_HAND_FLG2;		//; ����̏���׸� SRAM

U2b	SELF_FSTY_USE;		//;�O���S���u�`�F�b�N����E���Ȃ�
U2b	SELF_RSTY_USE;		//;����S���u�`�F�b�N����E���Ȃ�

U2b	SELF_CHK_TIMER;		//;�Z���t�`�F�b�N�^�C�}


//;	*** AD CONVERTER WORK RAM ***
U2b	AD_CNV_DT0;			//; 8BIT A/D

U2b	AD_BUFCNT;			// �ړ������ޯ̧����
U2b	AD_AVG_BUF[8];		// ����BAFTOP
U4b	AD_AVG_TOTAL;		// �W�񕪂��ް�
U2b	PV_AD_DATA;			// �ړ����ςƂ������AD DATA


//	-------- 2014-02-14 ----------
U2b	AD2_BUFCNT;			// �ړ������ޯ̧����
U2b	AD2_AVG_BUF[8];		// ����BAFTOP
U4b	AD2_AVG_TOTAL;		// �W�񕪂��ް�
//2014-10-11 DPRAM�Ɉړ� U2b	PV_AD2_DATA;			// �ړ����ςƂ������AD DATA
U2b	AD2CNV_IN_DATA;


U2b	AD3_BUFCNT;			// �ړ������ޯ̧����
U2b	AD3_AVG_BUF[8];		// ����BAFTOP
U4b	AD3_AVG_TOTAL;		// �W�񕪂��ް�
//2014-10-11 DPRAM�Ɉړ� U2b	PV_AD3_DATA;			// �ړ����ςƂ������AD DATA
U2b	AD3CNV_IN_DATA;

U2b	AD4_BUFCNT;			// �ړ������ޯ̧����
U2b	AD4_AVG_BUF[8];		// ����BAFTOP
U4b	AD4_AVG_TOTAL;		// �W�񕪂��ް�
//2014-10-11 DPRAM�Ɉړ� U2b	PV_AD4_DATA;			// �ړ����ςƂ������AD DATA
U2b	AD4CNV_IN_DATA;

U2b	ADCNV_SEL;



//	***************************************
//	***	��d��H�ُ�֌W�̃��[�N�q�`�l	***
//	***************************************
U2b	CPUN_2CMP_DATA;		// ����b�o�t�̔�r�f�[�^
U2b	CMP2_ERR_FIRST;		// ���߂ē�d��H�ُ픭��

U2b	CPUN_2CMP_LATCH2;	// �����d��H�ُ��ް�ׯ�
U2b	CPUN_2CMP_LATCH1;	// ������d��H�ُ��ް�ׯ�






//	*** ���S���u�֌W ***

U2b	FACT_IN_DATA;		//
U2b	RACT_IN_DATA;		//
U2b	FDEV_IN_DATA;		//
U2b	RDEV_IN_DATA;		//


//	�����ǉ� 2002-12-17
U2b	CPUBA_HD_INDT1;

//	�ʐM�֘A 2004-04-14
S2b	WK_RCV_SCLSR2;//2004-04-12
S2b	WK_RCV_SCFSR2;//2004-04-12
S2b	WK_RCV_SCFDR2	;//2004-04-12

//	===================
//	===				===
//	===================
//	=== 2004-04-14 ====
S2b	IN_RNA_REF_ERR_FLG1;//BIT0,BIT1,BIT2(HARD),BIT3CMD,BIT4(RNA-SYS),BIT5(RNA-FORM),,
S2b	IN_RNA_REF_ERR_FLG2;//BIT0~BIT7 ALM.BIT8
S2b	RNA_REF_ERR_FLG1;//BIT0,BIT1,BIT2(HARD),BIT3CMD,BIT4(RNA-SYS),BIT5(RNA-FORM),,
S2b	RNA_REF_ERR_FLG2;//BIT0~BIT7 ALM.BIT8
S2b	LT_RNA_REF_ERR_FLG1;//BIT0,BIT1,BIT2(HARD),BIT3CMD,BIT4(RNA-SYS),BIT5(RNA-FORM),,
S2b	LT_RNA_REF_ERR_FLG2;//BIT0~BIT7 ALM.BIT8

S2b	RNA_CMD_VERIFY_CNT;//00,01�ȊO������
S2b	RNA_CMD_VERIFY_DAT;//�ُ펞�̍ŐV�ް�
S2b	RNA_STS_SYSERR_CNT;//BIT0=1
S2b	RNA_STS_REQERR_CNT;//BIT2=1
S2b	RNA_STS_ERR_DAT;//�ُ펞�̍ŐV�ް�
S2b	RNA_ALM_BIT0_CNT;//
S2b	RNA_ALM_BIT1_CNT;//
S2b	RNA_ALM_BIT2_CNT;//
S2b	RNA_ALM_BIT3_CNT;//
S2b	RNA_ALM_BIT4_CNT;//
S2b	RNA_ALM_BIT5_CNT;//
S2b	RNA_ALM_BIT6_CNT;//
S2b	RNA_ALM_BIT7_CNT;//
S2b	RNA_ALM_CNT;//
S2b	RNA_ALM_DAT;//
S2b	RNA_REF1_CNT;//����������ɓ��삵�Ă��邩
S2b	RNA_REF2_CNT;//����������ɓ��삵�Ă��邩

S2b	RNA_CRC_ERR_CNT;
S2b	RNA_CRC_ERR_DAT;//CNC�̉��Z�l
S2b	RNA_CRC_CAL_DAT;//�����̉��Z�l
S2b	RNA_ERR_FLAME_BUF1[16];//CRC�ُ펞���ڰ�
S2b	RNA_ERR_FLAME_BUF2[16];//
S2b	RNA_ERR_FLAME_BUF3[16];//


U2b	DSET_SW_FLG;



//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//	*******************************************
//	***										***
//	***		�b�o�t�a�����[�N��������`		***
//	***										***
//	*******************************************

//2013-08-20�@KOMA �����̂��߈ړ�U2b	SQ_CBWK_TOP[70];		//
U2b	CPUA_EMG_IN_FLG;		//



//	*******************************************
//	***	���͊֌W�̃��[�N�q�`�l		***
//	*******************************************

//;	*** INP1 PORT ***
U2b	REAL_INP1_DATA;			//; ����l	
U2b	REAL_INP1_DT_OLD1;		//; 1��O		
U2b	REAL_INP1_DT_OLD2;		//; 2��O		

//;	*** PB PORT ***
U2b	PB_PORT_CTL_DATA;		//; ����l	
U2b	PB_INDT_OLD1;			//; 1��O		
U2b	PB_INDT_OLD2;			//; 2��O		

//;	*** PJ PORT ***
U2b	PJ_PORT_CTL_DATA;		//; ����l	
U2b	PJ_INDT_OLD1;			//; 1��O		
U2b	PJ_INDT_OLD2;			//; 2��O		

//;	*** PK PORT ***
U2b	PK_PORT_CTL_DATA;		//; ����l	
U2b	PK_INDT_OLD1;			//; 1��O		
U2b	PK_INDT_OLD2;			//; 2��O		

//;	*** PL PORT ***
U2b	PL_PORT_CTL_DATA;		//; ����l	
U2b	PL_INDT_OLD1;			//; 1��O		
U2b	PL_INDT_OLD2;			//; 2��O		




//	*******************************************
//	***	�ُ�֌W�̃��[�N�q�`�l		***
//	*******************************************

//20060725 SAITO	U2b	ERR_CHK_OK_FLG;			//;�ُ폈���J�n�׸�

//20060725 SAITO	U2b	ER_SQRAM_WK1[12+8+10];	//
//20060725 SAITO	U2b	ER_SQRAM_WK2[12+8+10];	//
//20060725 SAITO	U2b	SH4_SQERRAM[12+8+10];	//
//20060725 SAITO	U2b	DBG_ERRCHK_NASI[12+8+10];	// �����Ȃ�

//20060725 SAITO	U2b	ER_SFTSW_CHG_OLD;	//

//20060725 SAITO	U2b	SFTSW_ERR_TM;		//
//20060725 SAITO	U2b	BTNER_ERR_TM;		//
//20060725 SAITO	U2b	NCHSW_ERR_TM1;		//
//20060725 SAITO	U2b	NCHSW_ERR_TM2;		//
//20060725 SAITO	U2b	VLVER11_ERR_TM;		//
//20060725 SAITO	U2b	VLVER12_ERR_TM;		//
//20060725 SAITO	U2b	VLVER21_ERR_TM;		//
//20060725 SAITO	U2b	VLVER22_ERR_TM;		//
//20060725 SAITO	U2b	VLVER31_ERR_TM;		//
//20060725 SAITO	U2b	VLVER32_ERR_TM;		//
//20060725 SAITO	U2b	CMP2_ERR_TM2;		//
//20060725 SAITO	U2b	FSFT_TRERR_TM;		//
//20060725 SAITO	U2b	RSFT_TRERR_TM;		//


//20060725 SAITO	U2b	WPAR1_SFTSWER_TM;	//
//20060725 SAITO	U2b	WPAR1_BTNER_TM;		//
//20060725 SAITO	U2b	WPAR1_MODSER_TM1;	//
//20060725 SAITO	U2b	WPAR1_MODSER_TM2;	//
//20060725 SAITO	U2b	WPAR1_VLVER11_TM1;	//
//20060725 SAITO	U2b	WPAR1_VLVER12_TM1;	//
//20060725 SAITO	U2b	WPAR1_VLVER21_TM1;	//
//20060725 SAITO	U2b	WPAR1_VLVER22_TM1;	//
//20060725 SAITO	U2b	WPAR1_VLVER31_TM1;	//
//20060725 SAITO	U2b	WPAR1_VLVER32_TM1;	//
//20060725 SAITO	U2b	WPAR1_CMPER2_TM;	//
//20060725 SAITO	U2b	WPAR1_FSFTTRER_TM;	//
//20060725 SAITO	U2b	WPAR1_RSFTTRER_TM;	//




U2b	KEEPRY_BKUP_ERR;	//



//	***************************************************
//	***	�Z���t�`�F�b�N�֌W�̃��[�N�q�`�l	***
//	***************************************************
//20060725 SAITO	U2b	SELF_CHK_FLG;		//;��������� CHECK
//20060725 SAITO	U2b	SELF_ACT_FLG;		//;��������� CHECK

//20060725 SAITO	U2b	SELF_HAND_FLG1;		//; �����̏���׸� SRAM
//20060725 SAITO	U2b	SELF_HAND_FLG2;		//; ����̏���׸� SRAM

//20060725 SAITO	U2b	SELF_FSTY_USE;		//;�O���S���u�`�F�b�N����E���Ȃ�
//20060725 SAITO	U2b	SELF_RSTY_USE;		//;����S���u�`�F�b�N����E���Ȃ�

//20060725 SAITO	U2b	SELF_CHK_TIMER;		//;�Z���t�`�F�b�N�^�C�}


//;	*** AD CONVERTER WORK RAM ***
//20060725 SAITO	U2b	AD_CNV_DT0;				//; 8BIT A/D

//20060725 SAITO	U2b	AD_BUFCNT;			// �ړ������ޯ̧����
//20060725 SAITO	U2b	AD_AVG_BUF[8];			// ����BAFTOP
//20060725 SAITO	U4b	AD_AVG_TOTAL;			// �W�񕪂��ް�
//20060725 SAITO	U2b	PV_AD_DATA;			// �ړ����ςƂ������AD DATA




//	***************************************
//	***	��d��H�ُ�֌W�̃��[�N�q�`�l	***
//	***************************************
//20060725 SAITO	U2b	CPUN_2CMP_DATA;		// ����b�o�t�̔�r�f�[�^

//20060725 SAITO	U2b	CMP2_ERR_FIRST;		// ���߂ē�d��H�ُ픭��

//20060725 SAITO	U2b	CPUN_2CMP_LATCH2;	// �����d��H�ُ��ް�ׯ�
//20060725 SAITO	U2b	CPUN_2CMP_LATCH1;	// ������d��H�ُ��ް�ׯ�



//	*** ���S���u�֌W ***

//20060725 SAITO	U2b	FACT_IN_DATA;		//
//20060725 SAITO	U2b	RACT_IN_DATA;		//
//20060725 SAITO	U2b	FDEV_IN_DATA;		//
//20060725 SAITO	U2b	RDEV_IN_DATA;		//


//	IOGA	�֌W�@�r�h�s�|�S�p 2006-07-16

//;	*** IO-GA WORK ***
U2b	IOGA1_CTRL_DAT1[8];	//.SRES	2*8		; GA-PA,PB,PC,PD,PE ����PORT
						//;    PF,PG,PH �o��PORT
U2b	IOGA2_CTRL_DAT1[8];	//.SRES	2*8		; GA-PA,PB,PC,PD,PE ����PORT
						//;    PF,PG,PH �o��PORT
//;	*** IOGA INPUT WORK RAM ***
U2b	IOGA1_PA_DT_OLD1;	// 1��O
U2b	IOGA1_PB_DT_OLD1;	// 1��O
U2b	IOGA1_PC_DT_OLD1;	// 1��O
U2b	IOGA1_PD_DT_OLD1;	// 1��O
U2b	IOGA1_PE_DT_OLD1;	// 1��O

U2b	IOGA1_PA_DT_OLD2;	// 2��O
U2b	IOGA1_PB_DT_OLD2;	// 2��O
U2b	IOGA1_PC_DT_OLD2;	// 2��O
U2b	IOGA1_PD_DT_OLD2;	// 2��O
U2b	IOGA1_PE_DT_OLD2;	// 2��O

U2b	IOGA2_PA_DT_OLD1;	// 1��O
U2b	IOGA2_PB_DT_OLD1;	// 1��O
U2b	IOGA2_PC_DT_OLD1;	// 1��O
U2b	IOGA2_PD_DT_OLD1;	// 1��O
U2b	IOGA2_PE_DT_OLD1;	// 1��O

U2b	IOGA2_PA_DT_OLD2;	// 2��O
U2b	IOGA2_PB_DT_OLD2;	// 2��O
U2b	IOGA2_PC_DT_OLD2;	// 2��O
U2b	IOGA2_PD_DT_OLD2;	// 2��O
U2b	IOGA2_PE_DT_OLD2;	// 2��O


//20060725 SAITO	U2b	DSET_SW_FLG;


//	*******************************************
//	***										***
//	***		2011-03-18						***
//	***										***
//	*******************************************
S2b	ADCNV_IN_DATA;
