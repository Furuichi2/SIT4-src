//	***********************************
//	***								***
//	***		ワークｒａｍ定義		***
//	***								***
//	***********************************
#include	"cm_equ1.h"
#include	"ssc_ver1.h"

#if(CB_CPU_SEL==CB_CPUA)		//2004-03-31追加cpu-b高速化

#pragma section	wkIRAM	
#include	"ssc_cbrmH.inc"

#else	//ｾｸｼｮﾝ切替

//#pragma section	wkram1	/* ｾｸｼｮﾝ=時はBwkram1 */
#pragma section	wkiram1	//2013-08-20

#include	"ssc_cbrmH.inc"

#endif

//
#pragma section	wkram1	/* ｾｸｼｮﾝ=時はBwkram1 */
#include	"ssc_cbrm.inc"


#pragma section	wkram1	/* ｾｸｼｮﾝ=時はBwkram1 */

//	***************************
//	***						***
//	***	2003-07-01			***
//	***		異常履歴/ﾄﾚﾝﾄﾞ	***
//	***************************
//	ｻﾝﾌﾟﾘﾝｸﾞは4倍まで行える

	S4b	WPV_CB_STS_DAT_TOP[CB_STS_BUF_MAX/4+4]	;//異常履歴ﾊﾞﾌｧ 128byte
	S4b	WPV_CB_TRD_DAT_TOP[CB_TRD_SMP_CNT*4+4]	;//ﾄﾚﾝﾄﾞﾊﾞﾌｧ 4CH分
	S4b	DUMMY_BUF[CB_TRD_SMP_CNT*4+4];
	S4b	TRD_SMP_DAT1[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT2[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT3[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT4[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT5[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT6[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT7[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT8[CB_TRD_SMP_CNT+4];


	S2b	TRD_SMP_POINT;
	S2b	TRD_EVENT_COD;
	S2b	TRD_EVENT_LATCH;//停止イベントラッチ,終了
	S2b	TRD_POINT_EVENT;//EVENTが発生したﾎﾟｲﾝﾄ
	S2b	TRD_POINT_END;//ここまでｻﾝﾌﾟﾘﾝｸﾞしたら完了
	S2b	TRD_CLR_CMD;//01 CLR
	S2b	TRD_LATE_SV;
	S2b	TRD_LATE_PV;
	S2b	TRD_SMP_FLG;

	S2b	TRD_DP_MOV_FLG;
	S2b	TRD_DP_MOV_CNT;
	

	S2b	WPV_CB_STS_POINT			;//最新値ﾎﾟｲﾝﾀの指示位置
	S2b	WPV_CB_TRD_POINT			;//有効なﾃﾞｰﾀ数
	S2b	WPV_POWER_ON_CNT			;//電源投入回数

	S2b	HIST_DAT_SEND_COM;//SPMILENG SOFT ==> SEND SOFT
	S2b	HIST_DAT_SEND_DIS;//1:DISENABLE 0:ENABLE
	S2b	HIST_EVENT_COD;
	S2b	HIST_KEP_SEND_COM;//保留ｺﾏﾝﾄﾞ〜ﾘｾｯﾄまでの間 異常履歴指令受付

	S2b	CB_SEQ_CB_COM345X;//2004-06-28

//	***************************
//	***		モニタ機能		***
//	***************************
	S2b	MONI_DISP_MOD	;//

//	***************************
//	***						***
//	***		モニタ機能		***
//	***		データトレンド	***
//	***						***
//	***************************
	S2b		CNT_GRF_I_DATA[(64/2)*500]	;//64byte*500=32000
	S2b		CNT_GRF_Y_DATA[(64/2)*500]	;//64byte*500=32000
	S2b		CNT_GRF_POINT;



	S4b	ROOT_MAIN_INP;
	S4b	ROOT_MAIN_OUT;




//	*******************************
//	***		2013-12-11[MC]		***
//	*******************************
//	起動時ﾊﾝﾄﾞｼｪｲｸ
	S2b	CPUD_HAND_CNT;
	S2b	CPUD_START_OK;

//	*******************************
//	***		CPUA				***
//	*******************************
	S2b	CPUBX_MEM1_RCVFLG;		//BIT0=1:REQ-ON有 BIT1=1:ACK-ON:
	S2b	CPUBX_MEM1_ENDFLG;		//BIT0:KIND=1()
	S2b	CPUBX_MEM1_BUF[512];	//KIND=1

//	*******************************
//	***		CPUA				***
//	*******************************
	S2b	CPUDX_MEM1_RCVFLG;		//BIT0=1:REQ-ON有 BIT1=1:ACK-ON:
	S2b	CPUDX_MEM1_ENDFLG;		//BIT0:KIND=1()

//	*******************************
//	***		CPUB				***
//	*******************************
	S4b	CPUBX_SEND_TOPADR;
	S4b	CPUBX_SEND_MAXCNT;
	S4b	CPUBX_SEND_NOWCNT;

	S2b	CPUBX_MEM1_SNDEVN;		//EVNT BIT0:KIND
	S2b	CPUBX_MEM1_SNDKND;		//KIND
	S2b	CPUBX_MEM1_SNDFLG;		//


//	*******************************************
//	***										***
//	***		フィーダ用 CPUBは本来不要		***
//	***										***
//	*******************************************

//	*******************************
//	***		CPUC				***
//	*******************************
//	2016-04-02
	S2b	COP2_FEED_USEFUL;

//	*******************************
//	***		CPUC				***
//	*******************************
//	2016-04-02
	S4b	PVPX_LFEED_POS			;//ﾌｨｰﾀﾞ現在位置表示
	S4b	PVPX_LFD_PVABSPOS1;//ﾌｨｰﾀﾞ現在位置1(ABS)
	S4b	PVPX_LFD_PVABSPOS2;//ﾌｨｰﾀﾞ現在位置2(ABS)
	S4b	PVPX_LFD_PVABSPLS1;//ﾌｨｰﾀﾞ現在位置PLS1(ABS)
	S4b	PVPX_LFD_PVABSPLS2;//ﾌｨｰﾀﾞ現在位置PLS2(ABS)

	S4b	PVPX_LFD_PVINCPOS1;//ﾌｨｰﾀﾞ現在位置1(INC)
	S4b	PVPX_LFD_PVINCPOS2;//ﾌｨｰﾀﾞ現在位置2(INC)
	S4b	PVPX_LFD_PVINCPLS1;//ﾌｨｰﾀﾞ現在位置PLS1(INC)
	S4b	PVPX_LFD_PVINCPLS2;//ﾌｨｰﾀﾞ現在位置PLS2(INC)

	S4b	PVPX_LFD_OBJABSPLS;//ﾌｨｰﾀﾞ現在位置1(ABS)
	S4b	PVPX_LFD_OBJINCPLS;//ﾌｨｰﾀﾞ現在位置PLS1(INC)

	S2b	PVPX_LFD_OBJSPD;//+/- PER
	S2b	PVPX_LFD_ENCSPD;//+/- PER

	S2b	CMD_LFD_SITMCN_SIG;


//	カム
	S2b	SET1_LFEED_STRNO	;//送り開始行程		
	S2b	SET1_LFEED_ENDNO	;//送り終了行程

	S2b	SET1X_LFEED_STRDEG	;//往路送り開始角度 0.1度
	S2b	SET1X_LFEED_ENDDEG	;//往路送り終了角度 0.1度
	S2b	SET1Y_LFEED_STRDEG	;//復路送り開始角度 0.1度
	S2b	SET1Y_LFEED_ENDDEG	;//復路送り終了角度 0.1度

	S2b	OBJ_ENC360OLD;
	S2b	FEED_POS_STEP_OLD;
