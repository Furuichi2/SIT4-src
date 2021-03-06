#include	"cm_equ1.h"

//;	***************************************************
//;	***												***
//;	***		外部ＳＲＡＭ定義						***
//;	***												***
//;	***************************************************
#pragma section	wkram1	/* ｾｸｼｮﾝ=時はBwkram1 */
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
//;	***	S_SRCだけ					***
//;	***********************************
U2b		KEY_SCAN;
U2b		GAMEN_ON_FLG;
U2b		kan_bank_dat;
U2b		hmi2_test_wk1;
U2b		hmi2_test_wk2;
U2b		hmi2_test_type;

//;	***********************************
//;	***		HMI						***
//;	***		S_SRCだけ				***
//;	***********************************
U2b		kata_no_sv;
U2b		kata_no_ld;
U2b		*kata_adr_sv;
U2b		*kata_adr_ld;

//;	***************************************
//;	***									***
//;	***			コマツ					***
//;	***									***
//;	***************************************
U2b		cop_enc_int_enb;
U2b		cop_wait_tim;//2002-12-16 
U2b		sq_to_cop_com1;//2003-01-31

//	***************************************
//	***									***
//	***		2013-12-25[mc]				***
//	***									***
//	***************************************
//U2b		cop_init_endf;
U2b		cop_set_event_flg;

//;	***********************************
//;	***		HMI						***
//;	***		S_SRCだけ				***
//;	***********************************
U2b		aLCD_NO;
U2b		aLCD_WR_ADR;
U2b		aLCD_MOZI_SUU;
U2b		*aLCD_BUFF;

U2b		STACK_CHK_FLG;			// V05

//;	*******************************************************************
//;	***																***
//;	***	荷重計バックアップ化け不具合調査用プログラム				***	2007/10/05 V05i
//;	***																***
//;	*******************************************************************
U2b		PV_GAIN_BAK1L_INI;		//最大歪み２０００左ゲイン(1word)
U2b		PV_GAIN_BAK1R_INI;		//最大歪み２０００右ゲイン(1word)
U2b		PV_GAIN_BAK2L_INI;		//最大歪み１５００左ゲイン(1word)
U2b		PV_GAIN_BAK2R_INI;		//最大歪み１５００右ゲイン(1word)
U2b		PV_GAIN_BAK3L_INI;		//最大歪み　８００左ゲイン(1word)
U2b		PV_GAIN_BAK3R_INI;		//最大歪み　８００右ゲイン(1word)
U2b		PV_GAIN_BAK4L_INI;		//最大歪み　４００左ゲイン(1word)
U2b		PV_GAIN_BAK4R_INI;		//最大歪み　４００右ゲイン(1word)
U2b		PV_GAIN_BAK5L_INI;		//最大歪み　２００左ゲイン(1word)
U2b		PV_GAIN_BAK5R_INI;		//最大歪み　２００右ゲイン(1word)
U2b		PV_OF_BAKL_INI;			//オフセット値左(1byte)
U2b		PV_OF_BAKR_INI;			//オフセット値右(1byte)
U2b		PV_OF_AVE_BAKL_INI;		//オフセット補正左(1word)
U2b		PV_OF_AVE_BAKR_INI;		//オフセット補正右(1word)
U2b		PV_OF_AVE_BAKT_INI;		//オフセット補正合計(1word)
U2b		KJ_INI_CHK_WAIT;		//

