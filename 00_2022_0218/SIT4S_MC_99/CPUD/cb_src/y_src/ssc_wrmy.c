//	*******************************************
//	***					***
//	***	ワークｒａｍ定義		***
//	***					***
//	*******************************************
#include	"cm_equ1.h"
#include	"ssc_ver1.h"

#pragma section	wkram1	/* ｾｸｼｮﾝ=時はBwkram1 */
S4b	saito_c_ram_top;


U2b	TINT3_10MS_CNT;		//

//	***********************************
//	***	受信異常		***
//	***********************************
S2b	rcv2_err_hard_INTflg1;	// ﾊｰﾄﾞ異常
S2b	rcv2_err_hard_INTflg2;	// ﾊｰﾄﾞ異常
S2b	rcv2_err_hard_INTflg3;	// ﾊｰﾄﾞ異常
S2b	rcv2_err_data_flg1;	// ﾃﾞｰﾀ異常(未使用)
S2b	rcv2_err_hard_sts1;	// 詳細 異常内容
S2b	rcv2_err_hard_sts2;	// 詳細 異常内容
S2b	rcv2_err_hard_sts3;	// 
S2b	rcv2_err_data_sts1;	//(未使用)
S2b	rcv2_err_OverRunCnt;	//
S2b	rcv2_err_FRPRErrCnt;	//ﾌﾚｰﾑ・ﾊﾟﾘﾃｨ
S2b	rcv2_err_elseErrCnt;	//ﾌﾚｰﾑ・ﾊﾟﾘﾃｨ

//	***********************************
//	***	正常受信		***
//	***********************************
S2b	rcv2_data_INcnt;//受信ﾃﾞｰﾀ数 受信ﾊﾞﾌｧ→個数
S2b	rcv2_data_cnt;//処理すべきｶｳﾝﾀ数ﾘﾐｯﾄをかけたもんＰ
//S1b	rcv2_data_buf[32];
S2b	rcv2_data_buf[32];//境界線を偶数にしておく

//	***********************************
//	***	送信			***
//	***********************************
//S1b	send2_data_buf[32];
S2b	send2_data_buf[32];//境界線は偶数にしておく
//	***********************************
//	***	送受信管理		***
//	***********************************
S2b	rcv2_event_flg;	//main-->bit0=1  2ms:bit1(処理開始),bit7(完了)
S2b	send2_event_flg;//main-->bit0=1  2ms:bit1(処理開始),bit7(完了)




//	*** V_CTRLではDPRAMに定義していた ***
S4b	PV1_SCRW_POS[4];			//;@使用sh->H8 ->表示	[回送有り1CH のみ]

//	*** V_CTRLではWORKRAMに定義していた ***
S4b	PV0_SCRW_POS[4];			//;



//	*******************************************
//	***	異常関係のワークＲＡＭ		***
//	*******************************************

U2b	ERR_CHK_OK_FLG;			//;異常処理開始ﾌﾗｸﾞ

U2b	ER_SQRAM_WK1[12+8+10];	//
U2b	ER_SQRAM_WK2[12+8+10];	//
U2b	SH4_SQERRAM[12+8+10];	//
U2b	DBG_ERRCHK_NASI[12+8+10];	// ﾁｪｯｸなし

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
//	***	セルフチェック関係のワークＲＡＭ	***
//	***************************************************
U2b	SELF_CHK_FLG;		//;ｾﾙﾌﾁｪｯｸ中 CHECK
U2b	SELF_ACT_FLG;		//;ｾﾙﾌﾁｪｯｸ中 CHECK

U2b	SELF_HAND_FLG1;		//; 自分の状態ﾌﾗｸﾞ SRAM
U2b	SELF_HAND_FLG2;		//; 相手の状態ﾌﾗｸﾞ SRAM

U2b	SELF_FSTY_USE;		//;前安全装置チェックする・しない
U2b	SELF_RSTY_USE;		//;後安全装置チェックする・しない

U2b	SELF_CHK_TIMER;		//;セルフチェックタイマ


//;	*** AD CONVERTER WORK RAM ***
U2b	AD_CNV_DT0;			//; 8BIT A/D

U2b	AD_BUFCNT;			// 移動平均ﾊﾞｯﾌｧｶｳﾝﾀ
U2b	AD_AVG_BUF[8];		// 平均BAFTOP
U4b	AD_AVG_TOTAL;		// ８回分のﾃﾞｰﾀ
U2b	PV_AD_DATA;			// 移動平均とった後のAD DATA


//	-------- 2014-02-14 ----------
U2b	AD2_BUFCNT;			// 移動平均ﾊﾞｯﾌｧｶｳﾝﾀ
U2b	AD2_AVG_BUF[8];		// 平均BAFTOP
U4b	AD2_AVG_TOTAL;		// ８回分のﾃﾞｰﾀ
//2014-10-11 DPRAMに移動 U2b	PV_AD2_DATA;			// 移動平均とった後のAD DATA
U2b	AD2CNV_IN_DATA;


U2b	AD3_BUFCNT;			// 移動平均ﾊﾞｯﾌｧｶｳﾝﾀ
U2b	AD3_AVG_BUF[8];		// 平均BAFTOP
U4b	AD3_AVG_TOTAL;		// ８回分のﾃﾞｰﾀ
//2014-10-11 DPRAMに移動 U2b	PV_AD3_DATA;			// 移動平均とった後のAD DATA
U2b	AD3CNV_IN_DATA;

U2b	AD4_BUFCNT;			// 移動平均ﾊﾞｯﾌｧｶｳﾝﾀ
U2b	AD4_AVG_BUF[8];		// 平均BAFTOP
U4b	AD4_AVG_TOTAL;		// ８回分のﾃﾞｰﾀ
//2014-10-11 DPRAMに移動 U2b	PV_AD4_DATA;			// 移動平均とった後のAD DATA
U2b	AD4CNV_IN_DATA;

U2b	ADCNV_SEL;



//	***************************************
//	***	二重回路異常関係のワークＲＡＭ	***
//	***************************************
U2b	CPUN_2CMP_DATA;		// 相手ＣＰＵの比較データ
U2b	CMP2_ERR_FIRST;		// 初めて二重回路異常発生

U2b	CPUN_2CMP_LATCH2;	// 相手二重回路異常ﾃﾞｰﾀﾗｯﾁ
U2b	CPUN_2CMP_LATCH1;	// 自分二重回路異常ﾃﾞｰﾀﾗｯﾁ






//	*** 安全装置関係 ***

U2b	FACT_IN_DATA;		//
U2b	RACT_IN_DATA;		//
U2b	FDEV_IN_DATA;		//
U2b	RDEV_IN_DATA;		//


//	小松追加 2002-12-17
U2b	CPUBA_HD_INDT1;

//	通信関連 2004-04-14
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

S2b	RNA_CMD_VERIFY_CNT;//00,01以外が発生
S2b	RNA_CMD_VERIFY_DAT;//異常時の最新ﾃﾞｰﾀ
S2b	RNA_STS_SYSERR_CNT;//BIT0=1
S2b	RNA_STS_REQERR_CNT;//BIT2=1
S2b	RNA_STS_ERR_DAT;//異常時の最新ﾃﾞｰﾀ
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
S2b	RNA_REF1_CNT;//処理が正常に動作しているか
S2b	RNA_REF2_CNT;//処理が正常に動作しているか

S2b	RNA_CRC_ERR_CNT;
S2b	RNA_CRC_ERR_DAT;//CNCの演算値
S2b	RNA_CRC_CAL_DAT;//自分の演算値
S2b	RNA_ERR_FLAME_BUF1[16];//CRC異常時のﾌﾚｰﾑ
S2b	RNA_ERR_FLAME_BUF2[16];//
S2b	RNA_ERR_FLAME_BUF3[16];//


U2b	DSET_SW_FLG;



//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//	*******************************************
//	***										***
//	***		ＣＰＵＢ側ワークｒａｍ定義		***
//	***										***
//	*******************************************

//2013-08-20　KOMA 高速のため移動U2b	SQ_CBWK_TOP[70];		//
U2b	CPUA_EMG_IN_FLG;		//



//	*******************************************
//	***	入力関係のワークＲＡＭ		***
//	*******************************************

//;	*** INP1 PORT ***
U2b	REAL_INP1_DATA;			//; 今回値	
U2b	REAL_INP1_DT_OLD1;		//; 1回前		
U2b	REAL_INP1_DT_OLD2;		//; 2回前		

//;	*** PB PORT ***
U2b	PB_PORT_CTL_DATA;		//; 今回値	
U2b	PB_INDT_OLD1;			//; 1回前		
U2b	PB_INDT_OLD2;			//; 2回前		

//;	*** PJ PORT ***
U2b	PJ_PORT_CTL_DATA;		//; 今回値	
U2b	PJ_INDT_OLD1;			//; 1回前		
U2b	PJ_INDT_OLD2;			//; 2回前		

//;	*** PK PORT ***
U2b	PK_PORT_CTL_DATA;		//; 今回値	
U2b	PK_INDT_OLD1;			//; 1回前		
U2b	PK_INDT_OLD2;			//; 2回前		

//;	*** PL PORT ***
U2b	PL_PORT_CTL_DATA;		//; 今回値	
U2b	PL_INDT_OLD1;			//; 1回前		
U2b	PL_INDT_OLD2;			//; 2回前		




//	*******************************************
//	***	異常関係のワークＲＡＭ		***
//	*******************************************

//20060725 SAITO	U2b	ERR_CHK_OK_FLG;			//;異常処理開始ﾌﾗｸﾞ

//20060725 SAITO	U2b	ER_SQRAM_WK1[12+8+10];	//
//20060725 SAITO	U2b	ER_SQRAM_WK2[12+8+10];	//
//20060725 SAITO	U2b	SH4_SQERRAM[12+8+10];	//
//20060725 SAITO	U2b	DBG_ERRCHK_NASI[12+8+10];	// ﾁｪｯｸなし

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
//	***	セルフチェック関係のワークＲＡＭ	***
//	***************************************************
//20060725 SAITO	U2b	SELF_CHK_FLG;		//;ｾﾙﾌﾁｪｯｸ中 CHECK
//20060725 SAITO	U2b	SELF_ACT_FLG;		//;ｾﾙﾌﾁｪｯｸ中 CHECK

//20060725 SAITO	U2b	SELF_HAND_FLG1;		//; 自分の状態ﾌﾗｸﾞ SRAM
//20060725 SAITO	U2b	SELF_HAND_FLG2;		//; 相手の状態ﾌﾗｸﾞ SRAM

//20060725 SAITO	U2b	SELF_FSTY_USE;		//;前安全装置チェックする・しない
//20060725 SAITO	U2b	SELF_RSTY_USE;		//;後安全装置チェックする・しない

//20060725 SAITO	U2b	SELF_CHK_TIMER;		//;セルフチェックタイマ


//;	*** AD CONVERTER WORK RAM ***
//20060725 SAITO	U2b	AD_CNV_DT0;				//; 8BIT A/D

//20060725 SAITO	U2b	AD_BUFCNT;			// 移動平均ﾊﾞｯﾌｧｶｳﾝﾀ
//20060725 SAITO	U2b	AD_AVG_BUF[8];			// 平均BAFTOP
//20060725 SAITO	U4b	AD_AVG_TOTAL;			// ８回分のﾃﾞｰﾀ
//20060725 SAITO	U2b	PV_AD_DATA;			// 移動平均とった後のAD DATA




//	***************************************
//	***	二重回路異常関係のワークＲＡＭ	***
//	***************************************
//20060725 SAITO	U2b	CPUN_2CMP_DATA;		// 相手ＣＰＵの比較データ

//20060725 SAITO	U2b	CMP2_ERR_FIRST;		// 初めて二重回路異常発生

//20060725 SAITO	U2b	CPUN_2CMP_LATCH2;	// 相手二重回路異常ﾃﾞｰﾀﾗｯﾁ
//20060725 SAITO	U2b	CPUN_2CMP_LATCH1;	// 自分二重回路異常ﾃﾞｰﾀﾗｯﾁ



//	*** 安全装置関係 ***

//20060725 SAITO	U2b	FACT_IN_DATA;		//
//20060725 SAITO	U2b	RACT_IN_DATA;		//
//20060725 SAITO	U2b	FDEV_IN_DATA;		//
//20060725 SAITO	U2b	RDEV_IN_DATA;		//


//	IOGA	関係　ＳＩＴ－４用 2006-07-16

//;	*** IO-GA WORK ***
U2b	IOGA1_CTRL_DAT1[8];	//.SRES	2*8		; GA-PA,PB,PC,PD,PE 入力PORT
						//;    PF,PG,PH 出力PORT
U2b	IOGA2_CTRL_DAT1[8];	//.SRES	2*8		; GA-PA,PB,PC,PD,PE 入力PORT
						//;    PF,PG,PH 出力PORT
//;	*** IOGA INPUT WORK RAM ***
U2b	IOGA1_PA_DT_OLD1;	// 1回前
U2b	IOGA1_PB_DT_OLD1;	// 1回前
U2b	IOGA1_PC_DT_OLD1;	// 1回前
U2b	IOGA1_PD_DT_OLD1;	// 1回前
U2b	IOGA1_PE_DT_OLD1;	// 1回前

U2b	IOGA1_PA_DT_OLD2;	// 2回前
U2b	IOGA1_PB_DT_OLD2;	// 2回前
U2b	IOGA1_PC_DT_OLD2;	// 2回前
U2b	IOGA1_PD_DT_OLD2;	// 2回前
U2b	IOGA1_PE_DT_OLD2;	// 2回前

U2b	IOGA2_PA_DT_OLD1;	// 1回前
U2b	IOGA2_PB_DT_OLD1;	// 1回前
U2b	IOGA2_PC_DT_OLD1;	// 1回前
U2b	IOGA2_PD_DT_OLD1;	// 1回前
U2b	IOGA2_PE_DT_OLD1;	// 1回前

U2b	IOGA2_PA_DT_OLD2;	// 2回前
U2b	IOGA2_PB_DT_OLD2;	// 2回前
U2b	IOGA2_PC_DT_OLD2;	// 2回前
U2b	IOGA2_PD_DT_OLD2;	// 2回前
U2b	IOGA2_PE_DT_OLD2;	// 2回前


//20060725 SAITO	U2b	DSET_SW_FLG;


//	*******************************************
//	***										***
//	***		2011-03-18						***
//	***										***
//	*******************************************
S2b	ADCNV_IN_DATA;
