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

//;	***********************************
//;	***		HMI						***
//;	***		S_SRCだけ				***
//;	***********************************
U2b		aLCD_NO;
U2b		aLCD_WR_ADR;
U2b		aLCD_MOZI_SUU;
U2b		*aLCD_BUFF;

U2b		STACK_CHK_FLG;			// V05

//;	***********************************
//;	***		OPE通信用				***
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

//;	******** 2014/08/24 *********** SIT4-MC
U2b		KEY_INF_2_SEQ[2];

//;	******** 周辺機連動機能追加仕様 ***********		2016/04/22
U2b		SEQ_043_SV_WK;			//PUSH	MB(前/全/後)選択、防護柵(前/全/後)選択
U2b		SEQ_044_SV_WK;			//PUSH	バランサ調圧(設定圧/基準圧)選択、スライド自動調節(生産/段取1/段取2)選択
U2b		SEQ_045_SV_WK;			//PUSH	ダイクッション調節(左/右)選択
U2b		SEQ_046_SV_WK;			//PUSH	ダイクッション調節(ｽﾄﾛｰｸ／圧力)
U2b		SEQ_047_SV_WK;			//PUSH	ADC(搬入/交換/搬出)
