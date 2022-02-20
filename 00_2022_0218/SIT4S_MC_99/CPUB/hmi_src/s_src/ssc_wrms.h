//;	***************************************************
//;	***												***
//;	***		ŠO•”‚r‚q‚`‚l’è‹`						***
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
//;	***	S_SRC‚¾‚¯					***
//;	***********************************
	extern	U2b		KEY_SCAN;
	extern	U2b		GAMEN_ON_FLG;
	extern	U2b		kan_bank_dat;
	extern	U2b		hmi2_test_wk1;
	extern	U2b		hmi2_test_wk2;
	extern	U2b		hmi2_test_type;

//;	***********************************
//;	***	HMI							***
//;	***	S_SRC‚¾‚¯					***
//;	***********************************
	extern	U2b		kata_no_sv;
	extern	U2b		kata_no_ld;
	extern	U2b		*kata_adr_sv;
	extern	U2b		*kata_adr_ld;

//;	***********************************
//;	***		HMI						***
//;	***		S_SRC‚¾‚¯				***
//;	***********************************
	extern	U2b		aLCD_NO;
	extern	U2b		aLCD_WR_ADR;
	extern	U2b		aLCD_MOZI_SUU;
	extern	U2b		*aLCD_BUFF;

	extern	U2b		STACK_CHK_FLG;			// V05


