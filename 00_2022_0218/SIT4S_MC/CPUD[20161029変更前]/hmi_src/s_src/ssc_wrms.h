//;	***************************************************
//;	***												***
//;	***		Orq`lè`						***
//;	***												***
//;	***************************************************
	extern	S4b		shima_sram_top;

	extern	U2b		cpuab_hs_out0;//2002

//;	***********************************
//;	***	HMI							***
//;	***	FIT_SRC <- S_SRC			***
//;	***********************************
	extern	U2b	Key_Data_Flg;
	extern	U2b	Key_Data_No[4];
	extern	U2b	Key_Data_WK[4];	//V05q

//;	***********************************
//;	***	HMI							***
//;	***	FIT_SRC -> S_SRC			***
//;	***********************************
	extern	U2b	Lcd_Contrast;
//	extern	U2b	LCD_WORK1[15][16][40];
//	extern	U2b	LCD_WORK2[15][16][40];

//;	***********************************
//;	***	HMI							***
//;	***	S_SRC¾¯					***
//;	***********************************
	extern	U2b		KEY_SCAN;
	extern	U2b		GAMEN_ON_FLG;
	extern	U2b		kan_bank_dat;
	extern	U2b		hmi2_test_wk1;
	extern	U2b		hmi2_test_wk2;
	extern	U2b		hmi2_test_type;

//;	***********************************
//;	***	HMI							***
//;	***	S_SRC¾¯					***
//;	***********************************
	extern	U2b		kata_no_sv;
	extern	U2b		kata_no_ld;
	extern	U2b		*kata_adr_sv;
	extern	U2b		*kata_adr_ld;

//;	***********************************
//;	***		HMI						***
//;	***		S_SRC¾¯				***
//;	***********************************
	extern	U2b		aLCD_NO;
	extern	U2b		aLCD_WR_ADR;
	extern	U2b		aLCD_MOZI_SUU;
	extern	U2b		*aLCD_BUFF;

	extern	U2b		STACK_CHK_FLG;			// V05

//;	***********************************
//;	***		OPEÊMp				***
//;	***		SIT4-MC					***
//;	***********************************
	extern	U2b		OPE_RX_TIM;
	extern	U1b		OPE_LED_DAT[8];
	extern	U1b		OPE_TX_BUF[16];
	extern	U1b		OPE_RX_BUF[16];
	extern	U1b		OPE_SCI_MODE;
	extern	U1b		OPE_TX_POI;
	extern	U1b		OPE_RX_POI;
	extern	U1b		OPE_TX_LEN;
	extern	U1b		OPE_RX_BYTE;
	extern	U1b		OPE_RX_END;

//;	******** 2014/08/24 *********** SIT4-MC
	extern	U2b		KEY_INF_2_SEQ[2];

//;	******** üÓ@A®@\ÇÁdl ***********		2016/04/22
	extern	U2b		SEQ_043_SV_WK;			//PUSH	MB(O/S/ã)IðAhìò(O/S/ã)Ið
	extern	U2b		SEQ_044_SV_WK;			//PUSH	oT²³(Ýè³/î³)IðAXCh©®²ß(¶Y/iæ1/iæ2)Ið
	extern	U2b		SEQ_045_SV_WK;			//PUSH	_CNbV²ß(¶/E)Ið
	extern	U2b		SEQ_046_SV_WK;			//PUSH	_CNbV²ß(½ÄÛ°¸^³Í)
	extern	U2b		SEQ_047_SV_WK;			//PUSH	ADC(Àü/ð·/Ào)

