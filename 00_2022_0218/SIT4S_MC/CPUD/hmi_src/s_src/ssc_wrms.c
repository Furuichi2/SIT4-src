#include	"cm_equ1.h"

//;	***************************************************
//;	***												***
//;	***		Orq`lè`						***
//;	***												***
//;	***************************************************
#pragma section	wkram1	/* ¾¸¼®Ý=ÍBwkram1 */
S4b		shima_sram_top;

U2b		cpuab_hs_out0;

//;	***********************************
//;	***	HMI							***
//;	***	FIT_SRC <- S_SRC			***
//;	***********************************
U2b		Key_Data_Flg;
U2b		Key_Data_No[4];
U2b		Key_Data_WK[4];	//V05q

//;	***********************************
//;	***	HMI							***
//;	***	FIT_SRC -> S_SRC			***
//;	***********************************
//U2b		LCD_WORK1[15][16][40];
//U2b		LCD_WORK2[15][16][40];

//;	***********************************
//;	***	HMI							***
//;	***	S_SRC¾¯					***
//;	***********************************
U2b		KEY_SCAN;
U2b		GAMEN_ON_FLG;
U2b		kan_bank_dat;
U2b		hmi2_test_wk1;
U2b		hmi2_test_wk2;
U2b		hmi2_test_type;

//;	***********************************
//;	***		HMI						***
//;	***		S_SRC¾¯				***
//;	***********************************
U2b		kata_no_sv;
U2b		kata_no_ld;
U2b		*kata_adr_sv;
U2b		*kata_adr_ld;

//;	***************************************
//;	***									***
//;	***			R}c					***
//;	***									***
//;	***************************************
U2b		cop_enc_int_enb;
U2b		cop_wait_tim;//2002-12-16 
U2b		sq_to_cop_com1;//2003-01-31

//;	***********************************
//;	***		HMI						***
//;	***		S_SRC¾¯				***
//;	***********************************
U2b		aLCD_NO;
U2b		aLCD_WR_ADR;
U2b		aLCD_MOZI_SUU;
U2b		*aLCD_BUFF;

U2b		STACK_CHK_FLG;			// V05

//;	***********************************
//;	***		OPEÊMp				***
//;	***		SIT4-MC					***
//;	***********************************
U2b		OPE_RX_TIM;
U1b		OPE_LED_DAT[8];
U1b		OPE_TX_BUF[16];
U1b		OPE_RX_BUF[16];
U1b		OPE_SCI_MODE;
U1b		OPE_TX_POI;
U1b		OPE_RX_POI;
U1b		OPE_TX_LEN;
U1b		OPE_RX_BYTE;
U1b		OPE_RX_END;


//	***************************************
//	***									***
//	***		2014-1-5[mc]				***
//	***									***
//	***************************************
U2b		cop_set_event_flg;

//;	*******************************************************************
//;	***																***
//;	***	×dvobNAbv»¯sï²¸pvO				***	2007/10/05 V05i
//;	***																***
//;	*******************************************************************
U2b		PV_GAIN_BAK1L_INI;		//ÅåcÝQOOO¶QC(1word)
U2b		PV_GAIN_BAK1R_INI;		//ÅåcÝQOOOEQC(1word)
U2b		PV_GAIN_BAK2L_INI;		//ÅåcÝPTOO¶QC(1word)
U2b		PV_GAIN_BAK2R_INI;		//ÅåcÝPTOOEQC(1word)
U2b		PV_GAIN_BAK3L_INI;		//ÅåcÝ@WOO¶QC(1word)
U2b		PV_GAIN_BAK3R_INI;		//ÅåcÝ@WOOEQC(1word)
U2b		PV_GAIN_BAK4L_INI;		//ÅåcÝ@SOO¶QC(1word)
U2b		PV_GAIN_BAK4R_INI;		//ÅåcÝ@SOOEQC(1word)
U2b		PV_GAIN_BAK5L_INI;		//ÅåcÝ@QOO¶QC(1word)
U2b		PV_GAIN_BAK5R_INI;		//ÅåcÝ@QOOEQC(1word)
U2b		PV_OF_BAKL_INI;			//ItZbgl¶(1byte)
U2b		PV_OF_BAKR_INI;			//ItZbglE(1byte)
U2b		PV_OF_AVE_BAKL_INI;		//ItZbgâ³¶(1word)
U2b		PV_OF_AVE_BAKR_INI;		//ItZbgâ³E(1word)
U2b		PV_OF_AVE_BAKT_INI;		//ItZbgâ³v(1word)
U2b		KJ_INI_CHK_WAIT;		//

//;	******** 2014/08/24 *********** SIT4-MC
U2b		KEY_INF_2_SEQ[2];

//;	******** üÓ@A®@\ÇÁdl ***********		2016/04/22
U2b		SEQ_043_SV_WK;			//PUSH	MB(O/S/ã)IðAhìò(O/S/ã)Ið
U2b		SEQ_044_SV_WK;			//PUSH	oT²³(Ýè³/î³)IðAXCh©®²ß(¶Y/iæ1/iæ2)Ið
U2b		SEQ_045_SV_WK;			//PUSH	_CNbV²ß(¶/E)Ið
U2b		SEQ_046_SV_WK;			//PUSH	_CNbV²ß(½ÄÛ°¸^³Í)
U2b		SEQ_047_SV_WK;			//PUSH	ADC(Àü/ð·/Ào)
