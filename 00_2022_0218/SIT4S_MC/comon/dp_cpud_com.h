//;	*******************************************************************
//;	***								***
//;	***								***
//;	***		CPUD<=>CPUA					***
//;	***		CPUD<=>CPUB					***
//;	***								***
//;	***								***
//;	***								***
//;	*******************************************************************

//#include	"cm_equ1.h"

//;	*******************************************
//;	***					***
//;	***	SH2→SH4　ﾊﾝﾄﾞｼｪｲｸ		***
//;	***					***
//;	*******************************************
	extern	U4b	HS_SVCHG_B_TO_A;

//;	*******************************************
//;	***					***
//;	***	SH2←SH4　ﾊﾝﾄﾞｼｪｲｸ		***
//;	***					***
//;	*******************************************
	extern	U4b	HS_SVCHG_A_TO_B;
	extern	U2b	HS_PVP_TAKIKI_FLG;//待機点通過ﾌﾗｸﾞ 1ｾｯﾄはSH4　0CLRはSH2(HMI部)
	extern	U2b	HS_PVP_LOTCNT_FLG;

	extern	U2b	KEEPRY_BKUP_FLG;	// ｷｰﾌﾟﾘﾚｰ取り込み許可ﾌﾗｸﾞ

//;	==== 2003-07-09 ===
	extern	U2b	CMD_1CYCLE_DSP1	;//2003-07-09 1ｻｲｸﾙ速度/時間 0:非表示　1:表示
	extern	U2b	CMD_DAIPOS_DSP1	;//2003-07-09 生産下限位置　 0:非表示　1:表示

//	=== 2006-12-05 ====
	extern	U2b	CMD_KJTECH_DSP1		;//2006-12-05 1:荷重補正のﾃｰﾁﾝｸﾞ可能

//;	*******************************************
//;	***									***
//;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾌﾗｸﾞ領域 SH2-->SH4	***
//;	***									***
//;	*******************************************
	extern	U4b	VUP_HSAREA_B_TO_A[32];

//;	*******************************************
//;	***									***
//;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾌﾗｸﾞ領域 SH2<--SH4	***
//;	***									***
//;	*******************************************
	extern	U4b	VUP_HSAREA_A_TO_B[32];




//;	***************************************************
//;	***						***
//;	***	HMI(SH2-->SH4) 設定/ﾊﾟﾗﾒｰﾀ等領域	***
//;	***	このORG H'1000~ORG H'2FFF領域は		***
//;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾃﾞｰﾀに使用される		***
//;	***						***
//;	***************************************************
//;
//;	***************************************************
//;	***	ｼｰｹﾝｽKEEP RY ﾊﾞｯｸｱｯﾌﾟ返し領域		***
//;	***************************************************
	extern	U4b	VUP_DATA_ADR_OP1;//ROMﾃﾞｰﾀ(MAX8192ﾊﾞｲﾄ)
//??????????????????????	extern	U2b	SVB_SEQKEP_DAT[128];//ｼｰｹﾝｽKEEP領域
				//;空領域なし
//;	***************************************************
//;	***	4/2BYTE  ﾊﾞｯｸｱｯﾌﾟ返し領域(64b)		***
//;	***************************************************
	extern	S4b	SVB_RNAORG_PLS1;	//ﾘﾆｱ基準位置ﾊﾟﾙｽ
					//予備4byte領域
	extern	S4b	SVB_DYHITO_POS;	//2003-07-09 ﾀﾞｲﾊｲﾄ(下限位置)
	extern	S4b	SVB_SLIDE_POS;	//2003-07-09 生産下限位置

	extern	S4b	SVB_BAKORG_PLS1;//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2
	extern	S4b	SVB_BAKORG_PLS2;//ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2

	extern	S4b	SVB_RENIA_BUP1;//360角度相当ﾊﾟﾙｽ1
	extern	S4b	SVB_RENIA_BUP2;//360角度相当ﾊﾟﾙｽ2
	extern	S4b	SVB_RENIA_BUP3;//360角度相当ﾊﾟﾙｽの反転(SUM1)
	extern	S4b	SVB_RENIA_BUP4;//360角度相当ﾊﾟﾙｽの反転(SUM2)

//;	---------- 2006-12-04 荷重補正用荷重(平均値ﾊﾞｯｸｱｯﾌﾟ)----------
	extern	S2b	SVB_ARA1_KAJ_T2	;//区間最大荷重TOTALのみ使用

//;	***************************************************
//;	***	2BYTE  ROMﾊﾟﾗﾒｰﾀ領域			***
//;	***************************************************
	extern	U2b	SVP_RPARAM_TOP1[128];//ROMﾊﾟﾗﾒｰﾀ領域
				//;
//;	***************************************************
//;	***	ｻｰﾎﾞﾊﾟﾗﾒｰﾀ領域	4/2BYTE領域		***
//;	***************************************************
	extern	U2b	SVP_RNADIR_SEL1;//ﾘﾆｱｾﾝｻ極性
	extern	U2b	SVP_INCDIR_SEL1;//PG極性
	extern	U2b	SVP_INCPLS_1REV;//PG1回転のﾊﾟﾙｽ選択
	extern	U2b	SVP_INCPLS_HOSN;//PG補正N　ﾓｰﾀN回
	extern	U2b	SVP_INCPLS_HOSM;//PG補正M　ｸﾗﾝｸ角度M
	extern	U2b	SVP_MOTRPM_MAXM;//ﾓｰﾀ最大回転数

	extern	S4b	SVP_MOTMAX_FREQ;//ﾓｰﾀ最大時指令周波数
	extern	S4b	SVP_RNAORG_POS1;//機械原点入力
	extern	U4b	SVP_RNAPOS_MAXP;//機械上限
	extern	U4b	SVP_RNAPOS_MINP;//機械下限
	extern	U4b	SVP_UPAREA_JUDG;//上死点判定範囲
	extern	U4b	SVP_DNAREA_JUDG;//反転設定不可範囲



	extern	U2b	SVP_DNDINC_SPD1;		//段取速度	
	extern	U2b	SVP_UPAREA_SPD1;		//待機点復帰速度	
	extern	U2b	SVP_STDINC_SPD1;		//寸動速度	
	extern	U2b	SVP_REVDAT_SPD1;		//予備速度１	
	extern	U2b	SVP_REVDAT_SPD2;		//予備速度２	
	extern	U2b	SVP_REVDAT_SPD3;		//予備速度３	
	extern	U2b	SVP_TEPDAT_SPD1;		//手動ﾊﾟﾙｻ速度	
	extern	U2b	SVP_TEPLAT_DAT1;		//手動ﾊﾟﾙｻ低倍率	
	extern	U2b	SVP_TEPLAT_DAT2;		//手動ﾊﾟﾙｻ高倍率	

	extern	U2b	SVP_INCPOS_KP01;		//;PG位置比例ｹﾞｲﾝ
	extern	U2b	SVP_RNAPOS_KP01;		//;ﾘﾆｱ位置比例ｹﾞｲﾝ
	extern	U2b	SVP_ACCLAT_TIM1;		//;加減速時間
	extern	U2b	SVP_SSCURV_TIM1;		//;Ｓ字時間
	extern	U2b	SVP_UPAREA_INP1;		//;上死点ｲﾝﾎﾟｼﾞｼｮﾝ
	extern	U2b	SVP_DNAREA_INP1;		//;下死点ｲﾝﾎﾟｼﾞｼｮﾝ
	extern	U2b	SVP_OBJARA_INP1;		//;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ
	extern	U2b	SVP_INPPOS_TIM1;		//;ｲﾝﾎﾟｼﾞｼｮﾝﾁｪｯｸ時間
	extern	U2b	SVP_ARACHK_LNG1;		//;上／下死点通過判定量
	extern	U2b	SVP_UPAREA_DIG1;		//;回転時待機点(上死点)

	extern	U2b	SVP_INCHEN_ELNG;		//;PG偏差異常幅
	extern	U2b	SVP_INCENC_ELNG;		//;PG-ENC一致量
	extern	U2b	SVP_INCRNA_ELNG;		//;PG-ﾘﾆｱ一致量
	extern	U2b	SVP_INCSTP_ELNG;		//;PG停止異常量
	extern	U2b	SVP_RNASTP_ELNG;		//;ﾘﾆｱ停止異常量
	extern	U2b	SVP_INCREV_ELNG;		//;PG逆転異常量
	extern	U2b	SVP_RNAREV_ELNG;		//;ﾘﾆｱ逆転異常量
	extern	U2b	SVP_DAIHAI_LNG1;		//;ﾀﾞｲﾊｲﾄ補正比較値(小)
	extern	U2b	SVP_DAIHAI_LNG2;		//;ﾀﾞｲﾊｲﾄ補正比較値(中)
	extern	U2b	SVP_DAIHAI_LNG3;		//;ﾀﾞｲﾊｲﾄ補正比較値(大)

	extern	U2b	SVP_AMPERR_VLT1;		//;過負荷電圧1
	extern	U2b	SVP_AMPERR_TIM1;		//;過負荷時間1
	extern	U2b	SVP_AMPERR_VLT2;		//;過負荷電圧2
	extern	U2b	SVP_AMPERR_TIM2;		//;過負荷時間2
	extern	U2b	SVP_AMPERR_VLT3;		//;過負荷電圧3
	extern	U2b	SVP_AMPERR_TIM3;		//;過負荷時間3

//;	==== 2002-08-08 ==
	extern	U2b	SVP_CNT_TIM		;//連続タイマ
	extern	U2b	SVP_CNT_CNT		;//連続カウンタ
	extern	U2b	SVP_BREAK_DIG		;//ﾌﾞﾚｰｷ角度   0.1度
	extern	U2b	SVP_BREAK_TIM1		;//ブレーキタイマ設定
	extern	U2b	SVP_WT_DIG1		;//待機点選択1
	extern	U2b	SVP_WT_DIG2		;//待機点選択2
	extern	U2b	SVP_WT_DIG3		;//待機点選択3
	extern	U2b	SVP_MOTWT_TIM		;//起動保証時間
	extern	U2b	SVP_PSMOD_SEL		;//PSID　ﾓｰﾄﾞ選択
//;	==== 2002-08-21 ==
	extern	S4b	SVP_RNA_STLORK	;//
	extern	U2b	SVP_OUTPLS_HOSA	;//
	extern	U2b	SVP_OUTPLS_HOSB	;//
	extern	U2b	SVP_UPHOLD_DIG	;//
	extern	U2b	SVP_MACINE_SEL1	;//

//;	=========== 2003-01-27 ======
	extern	S4b	SVP_NEG_OFS_LNG	;//反転下限距離(0.001mm ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
	extern	U2b	SVP_AMP100P_VLT	;//AMP100%相当時の電圧値 0~10.0v(ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
//===============================

//;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	extern	U4b	SVP_LSAABN_AGL1	;//LSA異常検知の角度1
	extern	U4b	SVP_LSAABN_AGL2	;//LSA異常検知の角度2
	extern	U2b	SVP_PLSALO_PLS	;//パルサ倍率低
	extern	U2b	SVP_PLSAHI_PLS	;//パルサ倍率高
	extern	U2b	SVP_SMPSTR_KAJ	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ荷重
	extern	U2b	SVP_SMPSTR_AGL	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ角度
	extern	U2b	SVP_SMPSTR_FUK	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ負荷率
	extern	U2b	SVP_SMPSTR_SEH	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（上位ｱﾄﾞﾚｽ）
	extern	U2b	SVP_SMPSTR_SQL	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（下位ｱﾄﾞﾚｽ）
	extern	U2b	SVP_SMPMAX_CNT	;// ｻﾝﾌﾟﾘﾝｸﾞ　最大個数
	extern	U2b	SVP_SMPTRG_CNT	;// ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数
	extern	U2b	SVP_SMPCYC_TIM	;// ｻﾝﾌﾟﾘﾝｸﾞ　周期
	extern	U2b	SVP_MOADR0_SQH  ;// モニタアドレス０　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR0_SQL  ;// モニタアドレス０　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR1_SQH  ;// モニタアドレス１　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR1_SQL  ;// モニタアドレス１　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR2_SQH  ;// モニタアドレス２　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR2_SQL  ;// モニタアドレス２　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR3_SQH  ;// モニタアドレス３　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR3_SQL  ;// モニタアドレス３　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR4_SQH  ;// モニタアドレス４　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR4_SQL  ;// モニタアドレス４　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR5_SQH  ;// モニタアドレス５　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR5_SQL  ;// モニタアドレス５　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR6_SQH  ;// モニタアドレス６　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR6_SQL  ;// モニタアドレス６　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR7_SQH  ;// モニタアドレス７　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR7_SQL  ;// モニタアドレス７　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR8_SQH  ;// モニタアドレス８　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR8_SQL  ;// モニタアドレス８　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADR9_SQH  ;// モニタアドレス９　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADR9_SQL  ;// モニタアドレス９　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRA_SQH  ;// モニタアドレス１０　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRA_SQL  ;// モニタアドレス１０　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRB_SQH  ;// モニタアドレス１１　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRB_SQL  ;// モニタアドレス１１　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRC_SQH  ;// モニタアドレス１２　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRC_SQL  ;// モニタアドレス１２　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRD_SQH  ;// モニタアドレス１３　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRD_SQL  ;// モニタアドレス１３　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRE_SQH  ;// モニタアドレス１４　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRE_SQL  ;// モニタアドレス１４　ｼｰｹﾝｽ下位　V01v　060713
	extern	U2b	SVP_MOADRF_SQH  ;// モニタアドレス１５　ｼｰｹﾝｽ上位　V01v　060713
	extern	U2b	SVP_MOADRF_SQL  ;// モニタアドレス１５　ｼｰｹﾝｽ下位　V01v　060713

//;	=== 2006-11-20 ===	SHIMA(HMI:V01z)
	extern	U2b	SVP_SMP_CNT		;//ｻﾝﾌﾟﾘﾝｸﾞ収集形式　毎
	extern	U2b	SVP_TRD_CNT		;//ﾄﾚﾝﾄﾞ収集形式　毎

//;	=== 2008-10-15 ===	SHIMA(HMI:V05l)
	extern	U2b	SVP_ATCOL_CYC       ;// 自動収集条件　周期
	extern	U2b	SVP_ATCOL_STNO      ;// 自動収集条件　収集範囲　開始行程
	extern	U2b	SVP_ATCOL_STAG      ;// 自動収集条件　収集範囲　開始角度
	extern	U2b	SVP_ATCOL_SPNO      ;// 自動収集条件　収集範囲　終了行程
	extern	U2b	SVP_ATCOL_SPAG      ;// 自動収集条件　収集範囲　終了角度

//;	=== 2009-08-26 ===	SHIMA(HMI:V05o)
	extern	U4b	SVP_TRDCSR_RNAU		;/* ｽﾗｲﾄﾞ上限検出位置	*/
	extern	U4b	SVP_TRDCSR_RNAD		;/* ｽﾗｲﾄﾞ上限検出位置	*/ 
	extern	U2b	SVP_SMPTRG_CNT1		;//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数（SIT用）

//;	=== 2009-10-05(多段の荷重設定) ====    HMI
	extern	U2b	SVP_OBJECT_PRS_TOP[10];
	extern	U2b	SVP_OBJECT_PRS01;
	extern	U2b	SVP_OBJECT_PRS02;
	extern	U2b	SVP_OBJECT_PRS03;
	extern	U2b	SVP_OBJECT_PRS04;
	extern	U2b	SVP_OBJECT_PRS05;
	extern	U2b	SVP_OBJECT_PRS06;
	extern	U2b	SVP_OBJECT_PRS07;
	extern	U2b	SVP_OBJECT_PRS08;
	extern	U2b	SVP_OBJECT_PRS09;
	extern	U2b	SVP_OBJECT_PRS10;

//;	=== 2010-08-12 ====    SHIMA(HMI:V05r)
	extern	U2b	SVP_BREAK_DIG_RAT	;//ﾌﾞﾚｰｷ角度   	割合
	extern	U2b	SVP_BREAK_TIM_RAT	;//ブレーキタイマ	割合
	extern	U2b	SVP_MAX_KJYU		;//最大荷重設定(ｵﾌﾟｼｮﾝにしかない)(2010-08-23 koma)
	extern	U2b	SVP_VIB_KJYU_TTL	;//vibration(振動)荷重(2010-08-23 koma)

//;	=== 2013-02-20 KOMA
	extern	U2b	SVP_KATTCH_SPD		;//金型タッチ速度

//;	***************************************************
//;	***	ｸﾗｯﾁ制御画面設定1 4/2BYTE領域		***
//;	***************************************************
	extern	U4b	SVP_OBJECT_POS_TOP[20];		//01段目目標位置
	extern	U4b	SVP_OBJECT_PS01;		//01段目目標位置
	extern	U4b	SVP_OBJECT_PS02;		//02段目目標位置
	extern	U4b	SVP_OBJECT_PS03;		//03段目目標位置
	extern	U4b	SVP_OBJECT_PS04;		//04段目目標位置
	extern	U4b	SVP_OBJECT_PS05;		//05段目目標位置
	extern	U4b	SVP_OBJECT_PS06;		//06段目目標位置
	extern	U4b	SVP_OBJECT_PS07;		//07段目目標位置
	extern	U4b	SVP_OBJECT_PS08;		//08段目目標位置
	extern	U4b	SVP_OBJECT_PS09;		//09段目目標位置
	extern	U4b	SVP_OBJECT_PS10;		//10段目目標位置
	extern	U4b	SVP_OBJECT_PS11;		//11段目目標位置
	extern	U4b	SVP_OBJECT_PS12;		//12段目目標位置
	extern	U4b	SVP_OBJECT_PS13;		//13段目目標位置
	extern	U4b	SVP_OBJECT_PS14;		//14段目目標位置
	extern	U4b	SVP_OBJECT_PS15;		//15段目目標位置
	extern	U4b	SVP_OBJECT_PS16;		//16段目目標位置
	extern	U4b	SVP_OBJECT_PS17;		//17段目目標位置
	extern	U4b	SVP_OBJECT_PS18;		//18段目目標位置
	extern	U4b	SVP_OBJECT_PS19;		//19段目目標位置
	extern	U4b	SVP_OBJECT_PS20;		//20段目目標位置
                                                 
	extern	U2b	SVP_OBJECT_DIG_TOP[20]	;//01段目角度位置
	extern	U2b	SVP_OBJECT_DG01		;//01段目角度位置
	extern	U2b	SVP_OBJECT_DG02		;//02段目角度位置
	extern	U2b	SVP_OBJECT_DG03		;//03段目角度位置
	extern	U2b	SVP_OBJECT_DG04		;//04段目角度位置
	extern	U2b	SVP_OBJECT_DG05		;//05段目角度位置
	extern	U2b	SVP_OBJECT_DG06		;//06段目角度位置
	extern	U2b	SVP_OBJECT_DG07		;//07段目角度位置
	extern	U2b	SVP_OBJECT_DG08		;//08段目角度位置
	extern	U2b	SVP_OBJECT_DG09		;//09段目角度位置
	extern	U2b	SVP_OBJECT_DG10		;//10段目角度位置
	extern	U2b	SVP_OBJECT_DG11		;//予備11段目角度位置
	extern	U2b	SVP_OBJECT_DG12		;//予備12段目角度位置
	extern	U2b	SVP_OBJECT_DG13		;//予備13段目角度位置
	extern	U2b	SVP_OBJECT_DG14		;//予備14段目角度位置
	extern	U2b	SVP_OBJECT_DG15		;//予備15段目角度位置
	extern	U2b	SVP_OBJECT_DG16		;//予備16段目角度位置
	extern	U2b	SVP_OBJECT_DG17		;//予備17段目角度位置
	extern	U2b	SVP_OBJECT_DG18		;//予備18段目角度位置
	extern	U2b	SVP_OBJECT_DG19		;//予備19段目角度位置
	extern	U2b	SVP_OBJECT_DG20		;//予備20段目角度位置

	extern	U2b	SVP_OBJECT_SPD_TOP[20]	;//01段目移動速度
	extern	U2b	SVP_OBJECT_SP01		;//01段目移動速度
	extern	U2b	SVP_OBJECT_SP02		;//02段目移動速度
	extern	U2b	SVP_OBJECT_SP03		;//03段目移動速度
	extern	U2b	SVP_OBJECT_SP04		;//04段目移動速度
	extern	U2b	SVP_OBJECT_SP05		;//05段目移動速度
	extern	U2b	SVP_OBJECT_SP06		;//06段目移動速度
	extern	U2b	SVP_OBJECT_SP07		;//07段目移動速度
	extern	U2b	SVP_OBJECT_SP08		;//08段目移動速度
	extern	U2b	SVP_OBJECT_SP09		;//09段目移動速度
	extern	U2b	SVP_OBJECT_SP10		;//10段目移動速度
	extern	U2b	SVP_OBJECT_SP11		;//予備11段目移動速度
	extern	U2b	SVP_OBJECT_SP12		;//予備12段目移動速度
	extern	U2b	SVP_OBJECT_SP13		;//予備13段目移動速度
	extern	U2b	SVP_OBJECT_SP14		;//予備14段目移動速度
	extern	U2b	SVP_OBJECT_SP15		;//予備15段目移動速度
	extern	U2b	SVP_OBJECT_SP16		;//予備16段目移動速度
	extern	U2b	SVP_OBJECT_SP17		;//予備17段目移動速度
	extern	U2b	SVP_OBJECT_SP18		;//予備18段目移動速度
	extern	U2b	SVP_OBJECT_SP19		;//予備19段目移動速度
	extern	U2b	SVP_OBJECT_SP20		;//予備20段目移動速度

	extern	U2b	SVP_OBJECT_TIM_TOP[20]	;//01段目停止時間
	extern	U2b	SVP_OBJECT_TM01		;//01段目停止時間
	extern	U2b	SVP_OBJECT_TM02		;//02段目停止時間
	extern	U2b	SVP_OBJECT_TM03		;//03段目停止時間
	extern	U2b	SVP_OBJECT_TM04		;//04段目停止時間
	extern	U2b	SVP_OBJECT_TM05		;//05段目停止時間
	extern	U2b	SVP_OBJECT_TM06		;//06段目停止時間
	extern	U2b	SVP_OBJECT_TM07		;//07段目停止時間
	extern	U2b	SVP_OBJECT_TM08		;//08段目停止時間
	extern	U2b	SVP_OBJECT_TM09		;//09段目停止時間
	extern	U2b	SVP_OBJECT_TM10		;//10段目停止時間
	extern	U2b	SVP_OBJECT_TM11		;//11段目停止時間
	extern	U2b	SVP_OBJECT_TM12		;//12段目停止時間
	extern	U2b	SVP_OBJECT_TM13		;//13段目停止時間
	extern	U2b	SVP_OBJECT_TM14		;//14段目停止時間
	extern	U2b	SVP_OBJECT_TM15		;//15段目停止時間
	extern	U2b	SVP_OBJECT_TM16		;//16段目停止時間
	extern	U2b	SVP_OBJECT_TM17		;//17段目停止時間
	extern	U2b	SVP_OBJECT_TM18		;//18段目停止時間
	extern	U2b	SVP_OBJECT_TM19		;//19段目停止時間
	extern	U2b	SVP_OBJECT_TM20		;//20段目停止時間

//;	***************************************************
//;	***	ｸﾗｯﾁ制御画面設定2 4/2BYTE領域		***
//;	***************************************************
	extern	U4b	SVP_DAIHAI_ORG0		;//ダイハイト
//(本当はU4Bで0.001mm設定)
//現状はU2Bで0.01mm設定 とりあえず、現物あわせ
	extern	U2b	SVP_MRTION_SEL1		;//回転方式
	extern	U2b	SVP_MTSTEP_MAXM		;//段数

	extern	U4b	SVP_UPAREA_POS0		;//待機点位置
	extern	U2b	SVP_UPAREA_DIG0		;//待機点角度
	extern	U2b	SVP_UPAREA_SPD0		;//基準速度
	extern	U2b	SVP_UPAREA_TIM0		;//待機時間
	extern	U2b	SVP_DNAREA_INP0		;//下死点ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
	extern	U2b	SVP_OBJARA_INP0		;//目標位置ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
	extern	U2b	SVP_DAIHSA_LENG		;//ﾀﾞｲﾊｲﾄ補正距離

//;	==== 2002-08-08======
	extern	U4b	SVP_SLID_POS1;//ｽﾗｲﾄﾞ位置　生産
	extern	U4b	SVP_SLID_POS2;//ｽﾗｲﾄﾞ位置　段取1
	extern	U4b	SVP_SLID_POS3;//ｽﾗｲﾄﾞ位置　段取2

	extern	U2b	SVP_GMNSEQ_CNT01	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_CNT02	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_CNT03	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_CNT04	;//予備
	extern	U2b	SVP_GMNSEQ_CNT05	;//予備
	extern	U2b	SVP_GMNSEQ_CNT06	;//予備
	extern	U2b	SVP_GMNSEQ_CNT07	;//予備
	extern	U2b	SVP_GMNSEQ_CNT08	;//予備

	extern	U2b	SVP_GMNSEQ_TIM01	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_TIM02	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_TIM03	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	SVP_GMNSEQ_TIM04	;//予備
	extern	U2b	SVP_GMNSEQ_TIM05	;//予備
	extern	U2b	SVP_GMNSEQ_TIM06	;//予備
	extern	U2b	SVP_GMNSEQ_TIM07	;//予備
	extern	U2b	SVP_GMNSEQ_TIM08	;//予備

//;	==== 2002-08-26======
	extern	U2b	SVP_CAMFUN_SEL_TOP[16];
	extern	U2b	SVP_CAMFUN_SEL00;
	extern	U2b	SVP_CAMFUN_SEL01;
	extern	U2b	SVP_CAMFUN_SEL02;
	extern	U2b	SVP_CAMFUN_SEL03;
	extern	U2b	SVP_CAMFUN_SEL04;
	extern	U2b	SVP_CAMFUN_SEL05;
	extern	U2b	SVP_CAMFUN_SEL06;
	extern	U2b	SVP_CAMFUN_SEL07;
	extern	U2b	SVP_CAMFUN_SEL08;
	extern	U2b	SVP_CAMFUN_SEL09;
	extern	U2b	SVP_CAMFUN_SEL0A;
	extern	U2b	SVP_CAMFUN_SEL0B;
	extern	U2b	SVP_CAMFUN_SEL0C;
	extern	U2b	SVP_CAMFUN_SEL0D;
	extern	U2b	SVP_CAMFUN_SEL0E;
	extern	U2b	SVP_CAMFUN_SEL0F;

//;	===== 2002-08-29==
	extern	U4b	SVP_ATSLID_OBJ1		;// スライド自動調節設定値（現在動作中）
	extern	U2b	SVP_ATSLID_DNOBJ1	;// スライド自動調節　下降停止
	extern	U2b	SVP_ATSLID_UPOBJ1	;// スライド自動調節　上昇停止
	extern	U2b	SVP_ATSLID_BAKLNG	;// スライド自動調節　戻り量
	extern	U2b	SVP_ATSLID_COEF1	;// スライド自動調節　制御精度

//;	***********************************
//;	***		異常履歴	2003-07-09 	***
//;************************************
	extern	U2b	SVP_MONALM_S01		;
	extern	U2b	SVP_MONALM_S02		;
	extern	U2b	SVP_MONALM_S03		;
	extern	U2b	SVP_MONALM_S04		;

//;	===== 2004-06-08==
	extern	U2b	SVP_KAJYUU_PRS1	;//荷重
	extern	U2b	SVP_KAJYUU_PRS1	;//荷重補正 1Kn (2004-06-08)
	extern	U2b	SVP_KAJYUU_OBJP	;//荷重目標値 1Kn(2004-07-01)
	extern	U2b	SVP_KAJYUU_PV1	;//最大荷重(ｵﾌﾟｼｮﾝの実測をC/Bの設定として渡す)

//;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	extern	U2b	PVP_KAJLIV_LFT	;//荷重生（TON）(1word)
	extern	U2b	PVP_KAJLIV_TTL	;//荷重生（TON）(1word)
	extern	U2b	PVP_KAJLIV_RIH	;//荷重生（TON）(1word)

//;	=====2006-07-24(ｵｰﾊﾞﾗｲﾄﾞ) ====
	extern	U2b	SVP_OVERLIDE_COF	;//0,1~127%

//;	=====2006-07-24(段取) ====
	extern	U2b	SVP_DND_STOPDIG1	;//段取停止角度 0~358.0

//;	=====2006-07-24(荷重補正) ====
	extern	U2b	SVP_KJSTR_STEP1		;//0,1~工程 
	extern	U2b	SVP_KJSTR_DIG1		;//359.0
	extern	U2b	SVP_KJEND_STEP1		;//0,1~工程
	extern	U2b	SVP_KJEND_DIG1		;//359.0
	extern	U2b	PVP_ARA1_KAJ_R		;//OPTION 区間最大荷重
	extern	U2b	PVP_ARA1_KAJ_L		;//OPTION 区間最大荷重
	extern	U2b	PVP_ARA1_KAJ_T		;//OPTION 区間最大荷重TOTALのみ使用

//;	=====2006-07-24(表示) ====
	extern	U2b	PVP_1ROT_CALSPM	;//予想運転速度

//;	=====2006-10-13(COP2関係) ====
	extern	U4b	PVP_ORGRNA_MOV1	;//ﾘﾆｱ移動量実測1
	extern	U4b	PVP_ORGRNA_MOV2	;//ﾘﾆｱ移動量実測2
	extern	U4b	PVP_ORGSTRK_LEG1	;//ｽﾄﾛｰｸ1実測
	extern	U4b	PVP_ORGSTRK_LEG2	;//ｽﾄﾛｰｸ2実測
	extern	U4b	PVP_BAKORG_PLS1	;//ﾊﾞｯｸｱｯﾌﾟ実測
	extern	U4b	PVP_BAKORG_PLS2	;//ﾊﾞｯｸｱｯﾌﾟ実測
	extern	U4b	PVP_RENIA_POS1		;//ﾘﾆｱｽｹｰﾙ1実測
	extern	U4b	PVP_RENIA_POS2		;//ﾘﾆｱｽｹｰﾙ2実測
	extern	U2b	PVP_360_DEG		;//360度ｴﾝｺｰﾀﾞ角度
	extern	U2b	PVP_PG_DEG1		;//PG角度1
	extern	U2b	PVP_PG_DEG2		;//PG角度2
	extern	U2b	PVP_ZURE_PLS		;//軸間ｽﾞﾚ実測
	extern	U2b	PVP_ZURE_RNA		;//軸間ｽﾞﾚﾘﾆｱ

	extern	U4b	SVP_ORGSOK_PLS		;//原点測定ﾊﾟﾙｽ
	extern	U4b	SVP_ORGCAL_DAT1		;//演算係数1
	extern	U4b	SVP_ORGCAL_DAT2		;//演算係数2
	extern	U4b	SVP_ORGCAL_DAT3		;//演算係数3
	extern	U4b	SVP_ORGCAL_DAT4		;//演算係数4
	extern	U4b	SVP_ORGCAL_DAT5		;//演算係数5
	extern	U4b	SVP_ORGCAL_DAT6		;//演算係数6
	extern	U4b	SVP_ORGSTRK_LEN1	;//ｽﾄﾛｰｸ1
	extern	U4b	SVP_ORGSTRK_LEN2	;//ｽﾄﾛｰｸ2
	extern	U4b	SVP_RNAORGMEM_LEG1	;//ﾘﾆｱ原点1軸記憶
	extern	U4b	SVP_RNAORG_PLS1		;//ﾊﾞｯｸｱｯﾌﾟ実測
	extern	U4b	SVP_RNAORGMEM_LEG2	;//ﾘﾆｱ原点2軸記憶
	extern	U4b	SVP_RNAORG_PLS2		;//ﾊﾞｯｸｱｯﾌﾟ実測
	extern	U2b	SVP_RNAORG_SIN1		;//ﾊﾞｯｸｱｯﾌﾟ実測符号
	extern	U2b	SVP_RNAORG_SIN2		;//ﾊﾞｯｸｱｯﾌﾟ実測符号
	extern	U2b	SVP_ORGRUP_DEG		;//原点右区間上
	extern	U2b	SVP_ORGRDN_DEG		;//原点右区間下
	extern	U2b	SVP_ORGLUP_DEG		;//原点左区間上
	extern	U2b	SVP_ORGLDN_DEG		;//原点左区間下
	extern	U2b	SVP_ORGMEM_DEG1		;//角度1軸
	extern	U2b	SVP_ORGMEM_DEGS1	;//角度1軸　ON/OFF
	extern	U2b	SVP_ORGMEM_DEG2		;//角度2軸
	extern	U2b	SVP_ORGMEM_DEGS2	;//角度2軸　ON/OFF
	extern	U2b	SVP_ORGMPL_SEL1		;//手ﾊﾟﾙｻ選択1軸　ON/OFF
	extern	U2b	SVP_ORGMPL_SEL2		;//手ﾊﾟﾙｻ選択2軸　ON/OFF
	extern	U2b	SVP_HOSRAG_PLS1		;//軸間補正範囲１
	extern	U2b	SVP_HOSRAG_PLS2		;//軸間補正範囲２
	extern	U2b	SVP_HOSEI_SPD		;//補正速度
	extern	U2b	SVP_MANSAM_LEN		;//手動時同期
	extern	U2b	SVP_DANSAM_LEN		;//段取字同期
	extern	U2b	SVP_RUNSAMER_LEN1	;//運転同期異常１
	extern	U2b	SVP_RUNSAMER_LEN2	;//運転同期異常２
	extern	U2b	SVP_MANSAMER_PLS	;//手動同期異常
	extern	U2b	SVP_RUNSAMER_PLS	;//運転同期異常

	extern	U2b	SVP_RNADIR_SEL2		;//ﾘﾆｱｾﾝｻ極性
	extern	U4b	SVP_ORGMEM_DEG1A	;//角度1軸
	extern	U4b	SVP_ORGMEM_DEG2A	;//角度2軸

	extern	U4b	PVP_RENIA_BUP1		;//360角度相当ﾊﾟﾙｽ1
	extern	U4b	PVP_RENIA_BUP2		;//360角度相当ﾊﾟﾙｽ2
	extern	U4b	PVP_RENIA_BUP3		;//360角度相当ﾊﾟﾙｽの反転(SUM1)
	extern	U4b	PVP_RENIA_BUP4		;//360角度相当ﾊﾟﾙｽの反転(SUM2)
	extern	U2b	PVP_RNABUP_ENB		;//バックアップ有効／無効

//;	=====2006-11-20 ====	SHIMA(HMI:V01z)
	extern	U2b	PVP_ARA1_KAJ_T2		;//OPTION 区間最大荷重TOTALのみ使用

//;	==== 2006-12-01 =====
	extern	U4b	PVP_MENTE_CNT		;//2006-12-01 MAIN-->C/B

//;	==== 2007-02-13(CPO2関係 2軸ｻｰﾎﾞﾊﾟﾗﾒｰﾀ) =====
	extern	U4b	PVP_PG_DEG1X		;//PG角度1
	extern	U4b	PVP_PG_DEG2X		;//PG角度2
	extern	U4b	PVP_PG_PLS1			;//PG1実測ﾊﾟﾙｽ
	extern	U4b	PVP_PG_PLS2			;//PG2実測ﾊﾟﾙｽ
	extern	U4b	PVP_PG12_DEG1		;//PG1-2角度
	extern	U2b	SVP_FCLS_STR_DEG	;//ﾌﾙｸﾛ開始角度
	extern	U2b	SVP_FCLS_STR_HENS	;//ﾌﾙｸﾛ開始偏差
	extern	U2b	SVP_FCLS_ZIKI_SPD1	;//ﾌﾙｸﾛ自起動速度1
	extern	U2b	SVP_FCLS_ZIKI_SPD2	;//ﾌﾙｸﾛ自起動速度2
	extern	U2b	SVP_SYNC_ERR_DEGA	;//同期異常領域角度A
	extern	U2b	SVP_SYNC_ERR_DEGB	;//同期異常領域角度B
	extern	U2b	SVP_SYNC_ERR_DEGC	;//同期異常領域角度C
	extern	U2b	SVP_SYNC_ERR_DEGD	;//同期異常領域角度D
	extern	U2b	SVP_SYNC_ERR_RNAA	;//ﾘﾆｱ同期異常A
	extern	U2b	SVP_SYNC_ERR_RNAB	;//ﾘﾆｱ同期異常B
	extern	U2b	SVP_SYNC_ERR_RNAC	;//ﾘﾆｱ同期異常C
	extern	U2b	SVP_SYNC_ERR_RNAD	;//ﾘﾆｱ同期異常D
	extern	U2b	SVP_SYNC_ERR_PGA	;//PG同期異常A
	extern	U2b	SVP_SYNC_ERR_PGB	;//PG同期異常B
	extern	U2b	SVP_SYNC_ERR_PGC	;//PG同期異常C
	extern	U2b	SVP_SYNC_ERR_PGD	;//PG同期異常D

//;	==== 2010-09-15 =====
	extern	U2b	SVP_EP_VOF			;//サーボパラメータB0　　電力用ｵﾌｾｯﾄ
	extern	U2b	SVP_EP_VMX			;//サーボパラメータB1　　電力用最大値
	extern	U2b	SVP_EP_TRQ			;//サーボパラメータB2　　電力用ﾄﾙｸ値
	extern	U2b	SVP_EP_LTM			;//サーボパラメータB3　　ﾄﾙｸ側遅れ時間
	extern	U2b	SVP_EP_K1			;//サーボパラメータB4　　調整係数A
	extern	U2b	SVP_EP_K2			;//サーボパラメータB5　　調整係数B
	extern	U2b	SVP_EP_ADJSIN		;//サーボパラメータB6　　調整電力符号
	extern	U2b	SVP_EP_ADJVAL		;//サーボパラメータB7　　調整電力
	extern	U2b	SVP_ECOM_BASE		;//サーボパラメータB8　　エコメータ基準値
	extern	U2b	SVP_ECOM_SCAL		;//サーボパラメータB9　　エコメータスケール
	extern	U2b	SVP_MOTRPM_MAXP		;//サーボパラメータBA.モータ最大回転数
	extern	U2b	SVP_ACCLAT_TIMP		;//サーボパラメータBB.加減速時間

//;	==== 2010-12-06 =====
	extern	U2b	SVP_ONESTR_SPD2		;//反転時自起動速度

//;	==== 2011-03-22 =====
	extern	U4b	SVP_VOLST_L			;//サーボパラメータBC　　電力用ｵﾌｾｯﾄ
	extern	U4b	SVP_SLIDE_S			;//サーボパラメータBD　　電力用最大値
	extern	U4b	SVP_RAD				;//サーボパラメータBE　　電力用ﾄﾙｸ値
	extern	U4b	SVP_ORGREV_AGL		;//サーボパラメータBF　　ﾄﾙｸ側遅れ時間
	extern	U4b	SVP_ORGFWD_AGL		;//サーボパラメータBG　　調整係数A

//;	==== 2011-07-05 =====
	extern	U2b	SVP_RISE_ZWID		;//サーボパラメータBH　　上昇監視ｾﾞﾛ幅
	extern	U2b	SVP_RISE_CMP1		;//サーボパラメータBI　　上昇監視比較1
	extern	U2b	SVP_RISE_CMP2		;//サーボパラメータBJ　　上昇監視比較2
	extern	U2b	SVP_RISE_CMP3		;//サーボパラメータBK　　上昇監視比較予備
	extern	U2b	SVP_RISE_DLY1		;//サーボパラメータBL　　監視遅延1
	extern	U2b	SVP_RISE_DLY2		;//サーボパラメータBM　　監視遅延2

//;	==== 2011-07-28 =====
	extern	U2b	PVP_MOTINS_DAN		;//モーション挿入(C/B->HMI) 段数(1～9)
	extern	U2b	PVP_MOTINS_AGL		;//モーション挿入(C/B->HMI) 角度(少数点1桁データ)
	extern	U4b	PVP_MOTINS_POS		;//モーション挿入(C/B->HMI) 位置(少数点3桁データ)

//;	==== 2011-10-19 =====
	extern	U4b	PVP_MOTINS_PS2		;//2012-10-19追加 挿入位置2[ﾀｯﾁ位置]
	extern	U2b	PVP_MOTINS_AG2		;//2012-10-19追加 挿入角度2[ﾀｯﾁ角度]

//;	==== 2013-02-20 KOMA 挿入角度3===
	extern	U2b	PVP_MOTINS_AG3		;//
	extern	U4b	PVP_MOTINS_PS3		;//
	extern	U2b	PVP_MOTINS_INF		;//BIT0~BIT2:挿入情報


	extern	U2b	PVP_CKSPD_OVBIT				;//赤表示(BIT0~BIT9 BIT15:戻速度)
	extern	U2b	PVP_CKLMT_MDSPD				;//戻り速度

	extern	U2b	PVP_CKLMT_SPDTOP[10]		;//
	extern	U2b	PVP_CKLMT_SPD01				;//1段目
	extern	U2b	PVP_CKLMT_SPD02				;//2段目
	extern	U2b	PVP_CKLMT_SPD03				;//3段目
	extern	U2b	PVP_CKLMT_SPD04				;//4段目
	extern	U2b	PVP_CKLMT_SPD05				;//5段目
	extern	U2b	PVP_CKLMT_SPD06				;//6段目
	extern	U2b	PVP_CKLMT_SPD07				;//7段目
	extern	U2b	PVP_CKLMT_SPD08				;//8段目
	extern	U2b	PVP_CKLMT_SPD09				;//9段目
	extern	U2b	PVP_CKLMT_SPD10				;//10段目

	extern	U2b	PVP_MOTINS_DANBEF			;//0:有効な段数無し 1~9:金型ﾀｯﾁ減速挿入段数
	extern	U2b	PVP_MOTINS_DANAFT			;//0:有効な段数無し 1~9:金型ﾀｯﾁ後挿入段数


//;	*******************************************
//;	***	カム設定 2BYTE領域		***
//;	*******************************************
	extern	U2b	SVP_RCAMON_POS_TOP;
	extern	U2b	SVP_RCAMON_P000		;//位置ｶﾑ000　ＯＮ工程
	extern	U2b	SVP_RCAMON_D000		;//位置ｶﾑ000　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P000		;//位置ｶﾑ000　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D000		;//位置ｶﾑ000　ＯＦ角度
	extern	U2b	SVP_RCAMON_P001		;//位置ｶﾑ001　ＯＮ工程
	extern	U2b	SVP_RCAMON_D001		;//位置ｶﾑ001　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P001		;//位置ｶﾑ001　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D001		;//位置ｶﾑ001　ＯＦ角度
	extern	U2b	SVP_RCAMON_P002		;//位置ｶﾑ002　ＯＮ工程
	extern	U2b	SVP_RCAMON_D002		;//位置ｶﾑ002　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P002		;//位置ｶﾑ002　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D002		;//位置ｶﾑ002　ＯＦ角度
	extern	U2b	SVP_RCAMON_P003		;//位置ｶﾑ003　ＯＮ工程
	extern	U2b	SVP_RCAMON_D003		;//位置ｶﾑ003　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P003		;//位置ｶﾑ003　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D003		;//位置ｶﾑ003　ＯＦ角度
	extern	U2b	SVP_RCAMON_P004		;//位置ｶﾑ004　ＯＮ工程
	extern	U2b	SVP_RCAMON_D004		;//位置ｶﾑ004　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P004		;//位置ｶﾑ004　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D004		;//位置ｶﾑ004　ＯＦ角度
	extern	U2b	SVP_RCAMON_P005		;//位置ｶﾑ005　ＯＮ工程
	extern	U2b	SVP_RCAMON_D005		;//位置ｶﾑ005　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P005		;//位置ｶﾑ005　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D005		;//位置ｶﾑ005　ＯＦ角度
	extern	U2b	SVP_RCAMON_P006		;//位置ｶﾑ006　ＯＮ工程
	extern	U2b	SVP_RCAMON_D006		;//位置ｶﾑ006　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P006		;//位置ｶﾑ006　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D006		;//位置ｶﾑ006　ＯＦ角度
	extern	U2b	SVP_RCAMON_P007		;//位置ｶﾑ007　ＯＮ工程
	extern	U2b	SVP_RCAMON_D007		;//位置ｶﾑ007　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P007		;//位置ｶﾑ007　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D007		;//位置ｶﾑ007　ＯＦ角度
	extern	U2b	SVP_RCAMON_P008		;//位置ｶﾑ008　ＯＮ工程
	extern	U2b	SVP_RCAMON_D008		;//位置ｶﾑ008　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P008		;//位置ｶﾑ008　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D008		;//位置ｶﾑ008　ＯＦ角度
	extern	U2b	SVP_RCAMON_P009		;//位置ｶﾑ009　ＯＮ工程
	extern	U2b	SVP_RCAMON_D009		;//位置ｶﾑ009　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P009		;//位置ｶﾑ009　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D009		;//位置ｶﾑ009　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00A		;//位置ｶﾑ00A　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00A		;//位置ｶﾑ00A　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00A		;//位置ｶﾑ00A　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00A		;//位置ｶﾑ00A　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00B		;//位置ｶﾑ00B　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00B		;//位置ｶﾑ00B　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00B		;//位置ｶﾑ00B　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00B		;//位置ｶﾑ00B　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00C		;//位置ｶﾑ00C　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00C		;//位置ｶﾑ00C　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00C		;//位置ｶﾑ00C　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00C		;//位置ｶﾑ00C　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00D		;//位置ｶﾑ00D　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00D		;//位置ｶﾑ00D　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00D		;//位置ｶﾑ00D　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00D		;//位置ｶﾑ00D　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00E		;//位置ｶﾑ00E　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00E		;//位置ｶﾑ00E　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00E		;//位置ｶﾑ00E　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00E		;//位置ｶﾑ00E　ＯＦ角度
	extern	U2b	SVP_RCAMON_P00F		;//位置ｶﾑ00F　ＯＮ工程
	extern	U2b	SVP_RCAMON_D00F		;//位置ｶﾑ00F　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P00F		;//位置ｶﾑ00F　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D00F		;//位置ｶﾑ00F　ＯＦ角度
	extern	U2b	SVP_RCAMON_P010		;//位置ｶﾑ010　ＯＮ工程
	extern	U2b	SVP_RCAMON_D010		;//位置ｶﾑ010　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P010		;//位置ｶﾑ010　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D010		;//位置ｶﾑ010　ＯＦ角度
	extern	U2b	SVP_RCAMON_P011		;//位置ｶﾑ011　ＯＮ工程
	extern	U2b	SVP_RCAMON_D011		;//位置ｶﾑ011　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P011		;//位置ｶﾑ011　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D011		;//位置ｶﾑ011　ＯＦ角度
	extern	U2b	SVP_RCAMON_P012		;//位置ｶﾑ012　ＯＮ工程
	extern	U2b	SVP_RCAMON_D012		;//位置ｶﾑ012　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P012		;//位置ｶﾑ012　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D012		;//位置ｶﾑ012　ＯＦ角度
	extern	U2b	SVP_RCAMON_P013		;//位置ｶﾑ013　ＯＮ工程
	extern	U2b	SVP_RCAMON_D013		;//位置ｶﾑ013　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P013		;//位置ｶﾑ013　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D013		;//位置ｶﾑ013　ＯＦ角度
	extern	U2b	SVP_RCAMON_P014		;//位置ｶﾑ014　ＯＮ工程
	extern	U2b	SVP_RCAMON_D014		;//位置ｶﾑ014　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P014		;//位置ｶﾑ014　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D014		;//位置ｶﾑ014　ＯＦ角度
	extern	U2b	SVP_RCAMON_P015		;//位置ｶﾑ015　ＯＮ工程
	extern	U2b	SVP_RCAMON_D015		;//位置ｶﾑ015　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P015		;//位置ｶﾑ015　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D015		;//位置ｶﾑ015　ＯＦ角度
	extern	U2b	SVP_RCAMON_P016		;//位置ｶﾑ016　ＯＮ工程
	extern	U2b	SVP_RCAMON_D016		;//位置ｶﾑ016　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P016		;//位置ｶﾑ016　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D016		;//位置ｶﾑ016　ＯＦ角度
	extern	U2b	SVP_RCAMON_P017		;//位置ｶﾑ017　ＯＮ工程
	extern	U2b	SVP_RCAMON_D017		;//位置ｶﾑ017　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P017		;//位置ｶﾑ017　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D017		;//位置ｶﾑ017　ＯＦ角度
	extern	U2b	SVP_RCAMON_P018		;//位置ｶﾑ018　ＯＮ工程
	extern	U2b	SVP_RCAMON_D018		;//位置ｶﾑ018　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P018		;//位置ｶﾑ018　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D018		;//位置ｶﾑ018　ＯＦ角度
	extern	U2b	SVP_RCAMON_P019		;//位置ｶﾑ019　ＯＮ工程
	extern	U2b	SVP_RCAMON_D019		;//位置ｶﾑ019　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P019		;//位置ｶﾑ019　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D019		;//位置ｶﾑ019　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01A		;//位置ｶﾑ01A　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01A		;//位置ｶﾑ01A　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01A		;//位置ｶﾑ01A　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01A		;//位置ｶﾑ01A　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01B		;//位置ｶﾑ01B　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01B		;//位置ｶﾑ01B　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01B		;//位置ｶﾑ01B　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01B		;//位置ｶﾑ01B　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01C		;//位置ｶﾑ01C　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01C		;//位置ｶﾑ01C　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01C		;//位置ｶﾑ01C　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01C		;//位置ｶﾑ01C　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01D		;//位置ｶﾑ01D　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01D		;//位置ｶﾑ01D　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01D		;//位置ｶﾑ01D　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01D		;//位置ｶﾑ01D　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01E		;//位置ｶﾑ01E　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01E		;//位置ｶﾑ01E　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01E		;//位置ｶﾑ01E　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01E		;//位置ｶﾑ01E　ＯＦ角度
	extern	U2b	SVP_RCAMON_P01F		;//位置ｶﾑ01F　ＯＮ工程
	extern	U2b	SVP_RCAMON_D01F		;//位置ｶﾑ01F　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P01F		;//位置ｶﾑ01F　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D01F		;//位置ｶﾑ01F　ＯＦ角度
	extern	U2b	SVP_RCAMON_P020		;//位置ｶﾑ020　ＯＮ工程
	extern	U2b	SVP_RCAMON_D020		;//位置ｶﾑ020　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P020		;//位置ｶﾑ020　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D020		;//位置ｶﾑ020　ＯＦ角度
	extern	U2b	SVP_RCAMON_P021		;//位置ｶﾑ021　ＯＮ工程
	extern	U2b	SVP_RCAMON_D021		;//位置ｶﾑ021　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P021		;//位置ｶﾑ021　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D021		;//位置ｶﾑ021　ＯＦ角度
	extern	U2b	SVP_RCAMON_P022		;//位置ｶﾑ022　ＯＮ工程
	extern	U2b	SVP_RCAMON_D022		;//位置ｶﾑ022　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P022		;//位置ｶﾑ022　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D022		;//位置ｶﾑ022　ＯＦ角度
	extern	U2b	SVP_RCAMON_P023		;//位置ｶﾑ023　ＯＮ工程
	extern	U2b	SVP_RCAMON_D023		;//位置ｶﾑ023　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P023		;//位置ｶﾑ023　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D023		;//位置ｶﾑ023　ＯＦ角度
	extern	U2b	SVP_RCAMON_P024		;//位置ｶﾑ024　ＯＮ工程
	extern	U2b	SVP_RCAMON_D024		;//位置ｶﾑ024　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P024		;//位置ｶﾑ024　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D024		;//位置ｶﾑ024　ＯＦ角度
	extern	U2b	SVP_RCAMON_P025		;//位置ｶﾑ025　ＯＮ工程
	extern	U2b	SVP_RCAMON_D025		;//位置ｶﾑ025　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P025		;//位置ｶﾑ025　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D025		;//位置ｶﾑ025　ＯＦ角度
	extern	U2b	SVP_RCAMON_P026		;//位置ｶﾑ026　ＯＮ工程
	extern	U2b	SVP_RCAMON_D026		;//位置ｶﾑ026　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P026		;//位置ｶﾑ026　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D026		;//位置ｶﾑ026　ＯＦ角度
	extern	U2b	SVP_RCAMON_P027		;//位置ｶﾑ027　ＯＮ工程
	extern	U2b	SVP_RCAMON_D027		;//位置ｶﾑ027　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P027		;//位置ｶﾑ027　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D027		;//位置ｶﾑ027　ＯＦ角度
	extern	U2b	SVP_RCAMON_P028		;//位置ｶﾑ028　ＯＮ工程
	extern	U2b	SVP_RCAMON_D028		;//位置ｶﾑ028　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P028		;//位置ｶﾑ028　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D028		;//位置ｶﾑ028　ＯＦ角度
	extern	U2b	SVP_RCAMON_P029		;//位置ｶﾑ029　ＯＮ工程
	extern	U2b	SVP_RCAMON_D029		;//位置ｶﾑ029　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P029		;//位置ｶﾑ029　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D029		;//位置ｶﾑ029　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02A		;//位置ｶﾑ02A　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02A		;//位置ｶﾑ02A　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02A		;//位置ｶﾑ02A　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02A		;//位置ｶﾑ02A　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02B		;//位置ｶﾑ02B　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02B		;//位置ｶﾑ02B　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02B		;//位置ｶﾑ02B　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02B		;//位置ｶﾑ02B　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02C		;//位置ｶﾑ02C　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02C		;//位置ｶﾑ02C　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02C		;//位置ｶﾑ02C　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02C		;//位置ｶﾑ02C　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02D		;//位置ｶﾑ02D　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02D		;//位置ｶﾑ02D　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02D		;//位置ｶﾑ02D　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02D		;//位置ｶﾑ02D　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02E		;//位置ｶﾑ02E　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02E		;//位置ｶﾑ02E　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02E		;//位置ｶﾑ02E　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02E		;//位置ｶﾑ02E　ＯＦ角度
	extern	U2b	SVP_RCAMON_P02F		;//位置ｶﾑ02F　ＯＮ工程
	extern	U2b	SVP_RCAMON_D02F		;//位置ｶﾑ02F　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P02F		;//位置ｶﾑ02F　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D02F		;//位置ｶﾑ02F　ＯＦ角度
	extern	U2b	SVP_RCAMON_TIM_TOP;
	extern	U2b	SVP_RCAMON_P100		;//タイマｶﾑ000　ＯＮ工程
	extern	U2b	SVP_RCAMON_D100		;//タイマｶﾑ000　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P100		;//タイマｶﾑ000　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D100		;//タイマｶﾑ000　OF時間・角度
	extern	U2b	SVP_RCAMON_P101		;//タイマｶﾑ001　ＯＮ工程
	extern	U2b	SVP_RCAMON_D101		;//タイマｶﾑ001　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P101		;//タイマｶﾑ001　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D101		;//タイマｶﾑ001　OF時間・角度
	extern	U2b	SVP_RCAMON_P102		;//タイマｶﾑ002　ＯＮ工程
	extern	U2b	SVP_RCAMON_D102		;//タイマｶﾑ002　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P102		;//タイマｶﾑ002　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D102		;//タイマｶﾑ002　OF時間・角度
	extern	U2b	SVP_RCAMON_P103		;//タイマｶﾑ003　ＯＮ工程
	extern	U2b	SVP_RCAMON_D103		;//タイマｶﾑ003　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P103		;//タイマｶﾑ003　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D103		;//タイマｶﾑ003　OF時間・角度
	extern	U2b	SVP_RCAMON_P104		;//タイマｶﾑ004　ＯＮ工程
	extern	U2b	SVP_RCAMON_D104		;//タイマｶﾑ004　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P104		;//タイマｶﾑ004　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D104		;//タイマｶﾑ004　OF時間・角度
	extern	U2b	SVP_RCAMON_P105		;//タイマｶﾑ005　ＯＮ工程
	extern	U2b	SVP_RCAMON_D105		;//タイマｶﾑ005　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P105		;//タイマｶﾑ005　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D105		;//タイマｶﾑ005　OF時間・角度
	extern	U2b	SVP_RCAMON_P106		;//タイマｶﾑ006　ＯＮ工程
	extern	U2b	SVP_RCAMON_D106		;//タイマｶﾑ006　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P106		;//タイマｶﾑ006　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D106		;//タイマｶﾑ006　OF時間・角度
	extern	U2b	SVP_RCAMON_P107		;//タイマｶﾑ007　ＯＮ工程
	extern	U2b	SVP_RCAMON_D107		;//タイマｶﾑ007　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P107		;//タイマｶﾑ007　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D107		;//タイマｶﾑ007　OF時間・角度
	extern	U2b	SVP_RCAMON_P108		;//タイマｶﾑ008　ＯＮ工程
	extern	U2b	SVP_RCAMON_D108		;//タイマｶﾑ008　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P108		;//タイマｶﾑ008　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D108		;//タイマｶﾑ008　OF時間・角度
	extern	U2b	SVP_RCAMON_P109		;//タイマｶﾑ009　ＯＮ工程
	extern	U2b	SVP_RCAMON_D109		;//タイマｶﾑ009　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P109		;//タイマｶﾑ009　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D109		;//タイマｶﾑ009　OF時間・角度
	extern	U2b	SVP_RCAMON_P10A		;//タイマｶﾑ00A　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10A		;//タイマｶﾑ00A　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10A		;//タイマｶﾑ00A　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10A		;//タイマｶﾑ00A　OF時間・角度
	extern	U2b	SVP_RCAMON_P10B		;//タイマｶﾑ00B　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10B		;//タイマｶﾑ00B　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10B		;//タイマｶﾑ00B　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10B		;//タイマｶﾑ00B　OF時間・角度
	extern	U2b	SVP_RCAMON_P10C		;//タイマｶﾑ00C　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10C		;//タイマｶﾑ00C　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10C		;//タイマｶﾑ00C　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10C		;//タイマｶﾑ00C　OF時間・角度
	extern	U2b	SVP_RCAMON_P10D		;//タイマｶﾑ00D　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10D		;//タイマｶﾑ00D　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10D		;//タイマｶﾑ00D　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10D		;//タイマｶﾑ00D　OF時間・角度
	extern	U2b	SVP_RCAMON_P10E		;//タイマｶﾑ00E　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10E		;//タイマｶﾑ00E　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10E		;//タイマｶﾑ00E　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10E		;//タイマｶﾑ00E　OF時間・角度
	extern	U2b	SVP_RCAMON_P10F		;//タイマｶﾑ00F　ＯＮ工程
	extern	U2b	SVP_RCAMON_D10F		;//タイマｶﾑ00F　ＯＮ角度
	extern	U2b	SVP_RCAMOF_P10F		;//タイマｶﾑ00F　ＯＦ工程
	extern	U2b	SVP_RCAMOF_D10F		;//タイマｶﾑ00F　ＯＦ時間・角
                                                 
//;	*******************************
//;	***							***
//;	***		予備				***
//;	***	通信やﾄﾚﾝﾄﾞ関係			***
//;	*******************************
	extern	U4b	SVP_DEB_ADR0		; 
	extern	U4b	SVP_DEB_ADR1		; 
	extern	U4b	SVP_DEB_ADR2		; 
	extern	U4b	SVP_DEB_ADR3		; 
	extern	U4b	SVP_DEB_ADR4		; 

	extern	U2b	SVP_DEB_SEL0		; 
	extern	U2b	SVP_DEB_SEL1		; 
	extern	U2b	SVP_DEB_SEL2		; 
	extern	U2b	SVP_DEB_SEL3		; 
	extern	U2b	SVP_DEB_SEL4		; 

	extern	U2b	PVP_DEB_DAT0		; 
	extern	U2b	PVP_DEB_DAT1		; 
	extern	U2b	PVP_DEB_DAT2		; 
	extern	U2b	PVP_DEB_DAT3		; 
	extern	U2b	PVP_DEB_DAT4		; 
	extern	U2b	PVP_DEB_DAT5		; 
	extern	U2b	PVP_DEB_DAT6		; 
	extern	U2b	PVP_DEB_DAT7		; 
	extern	U2b	PVP_DEB_DAT8		; 
	extern	U2b	PVP_DEB_DAT9		; 

//;	***********************************
//;	***		異常履歴	2003-07-09 	***
//;************************************

	extern	U2b	PVP_MONALM_P01	;//
	extern	U2b	PVP_MONALM_P02	;//
	extern	U2b	PVP_MONALM_P03	;//
	extern	U2b	PVP_MONALM_P04	;//


	extern	S4b	PVP_MONALM_C01	;//A/B/Cは連続した空間である事
	extern	S4b	PVP_MONALM_C02	;//
	extern	S4b	PVP_MONALM_C03	;//
	extern	S4b	PVP_MONALM_C04	;//
	extern	S4b	PVP_MONALM_C05	;//
	extern	S4b	PVP_MONALM_C06	;//
	extern	S4b	PVP_MONALM_C07	;//
	extern	S4b	PVP_MONALM_C08	;//
	extern	U2b	PVP_MONALM_A01	;//
	extern	U2b	PVP_MONALM_A02	;//
	extern	U2b	PVP_MONALM_A03	;//
	extern	U2b	PVP_MONALM_A04	;//
	extern	U2b	PVP_MONALM_A05	;//
	extern	U2b	PVP_MONALM_A06	;//
	extern	U2b	PVP_MONALM_A07	;//
	extern	U2b	PVP_MONALM_A08	;//
	extern	S2b	PVP_MONALM_B01	;//
	extern	S2b	PVP_MONALM_B02	;//
	extern	S2b	PVP_MONALM_B03	;//
	extern	S2b	PVP_MONALM_B04	;//
	extern	S2b	PVP_MONALM_B05	;//
	extern	S2b	PVP_MONALM_B06	;//
	extern	S2b	PVP_MONALM_B07	;//
	extern	S2b	PVP_MONALM_B08	;//


//;	*******************************
//;	***		実測 4/2BYTE領域	***
//;	*******************************
	extern	S4b	PVP_RNAORG_PLS1		;//ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
	extern	S4b	PVP_NOW_POSI000		;//現在位置(補正後のリニアセンサ位置)
	extern	S4b	PVP_RENIA_POSI0		;//リニアセンサ現在位置(生表示用)
	extern	U2b	PVP_NOW_ANGLE00		;//現在角度
	extern	U2b	PVP_CYCLE_TIME0		;//サイクル時間

//;	----- 追加2002/07/02 ---
	extern	S2b	PVP_CYCLE_SPM1		;//サイクル速度表示用
	extern	S2b	PVP_DISP_SPM2		;//高速時描画を塗りつぶしにする為の速度(単位不明)
	extern	S2b	PVP_NOW_ANGLE_RNA	;//現在角度0.1度HEX(ﾘﾆｱｽｹｰﾙからの1度単位 SH4->SH2)
	extern	S2b	PVP_DYHITO_HOSLNG	;//ﾀﾞｲﾊｲﾄ補正量 1um(0.001mm) +/-
	extern	S4b	PVP_DYHITO_POS		;//ﾀﾞｲﾊｲﾄ実測前回値(?) 生産初期画面
	extern	S4b	PVP_SLIDE_POS		;//ｽﾗｲﾄﾞ位置・ﾀﾞｲﾊｲﾄを含めた位置
	extern	S2b	PVP_TAIKITEN_POS	;//

//;	----- 追加2002/08/01 ---
	extern	S4b	PVP_RNA_STLORK		;//ｽﾄﾛｰｸ実測
	extern	U2b	PVP_STOP_TIM		;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ 1msec data
	extern	U2b	PVP_BREAK_DIG		;//ﾌﾞﾚｰｷ角度   0.1度
	extern	U2b	PVP_COM_ERR		;//ｺﾝﾊﾟｲﾙ異常有り／無し
	extern	U2b	PVP_COM_ADR		;//ｺﾝﾊﾟｲﾙ異常ｱﾄﾞﾚｽ
	extern	U2b	PVP_SEQ_ERR		;//ｺﾝﾊﾟｲﾙ異常割込orﾒｲﾝ

//;	----- 追加2002/08/08-----
	extern	U2b	PVP_BREAK_TIM1		;//
	extern	U2b	PVP_GMNSEQ_CNT01	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_CNT02	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_CNT03	;//内部画面ﾀｲﾏ->ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_CNT04	;//予備
	extern	U2b	PVP_GMNSEQ_CNT05	;//予備
	extern	U2b	PVP_GMNSEQ_CNT06	;//予備
	extern	U2b	PVP_GMNSEQ_CNT07	;//予備
	extern	U2b	PVP_GMNSEQ_CNT08	;//予備

	extern	U2b	PVP_GMNSEQ_TIM01	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_TIM02	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_TIM03	;//内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
	extern	U2b	PVP_GMNSEQ_TIM04	;//予備
	extern	U2b	PVP_GMNSEQ_TIM05	;//予備
	extern	U2b	PVP_GMNSEQ_TIM06	;//予備
	extern	U2b	PVP_GMNSEQ_TIM07	;//予備
	extern	U2b	PVP_GMNSEQ_TIM08	;//予備

//;	========== 2003-01-27 ﾊﾟﾜｰﾓﾆﾀ実測追加====
	extern	U2b	PVP_POWER_MONI		;//

//;	========= 2003-02-04 ======
	extern	U2b	PVP_CPUA_TEPPLS		;//
	extern	U2b	PVP_CPUB_TEPPLS		;//
	extern	U2b	PVP_CPUA_ANAIN		;//
	extern	U2b	PVP_CPUB_ANAIN		;//


//;	========== 2010-09-01 電力量追加 ============
	extern	U2b	PVP_ECO_METER		;
	extern	U2b	PVP_POWER_KWH		;
	extern	U2b	PVP_EPM_SYOHI		;
	extern	U2b	PVP_EPM_KAISE		;

	extern	U2b	PVP_IVW_DOT			;//0:小数点2桁 5A:小数点1桁 CPUA->CPUB



//	=========================================

	extern	U2b	PVP_CB_A_VER[6]		;//(1WORDでｷｬﾗｸﾀする 6char) SH4-->
	extern	U2b	PVP_CB_B_VER[6]		;//(6char) SH2-->

//;	======= 2003-01-27 ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ追加 =====
	extern	U2b	PVP_PAR_A_VER		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
	extern	U2b	PVP_PAR_B_VER		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
	extern	U2b	PVP_TBL_A_VER		;//ｾﾝｻのﾃｰﾌﾞﾙ番号1~99 HEX data
	extern	U2b	PVP_TBL_B_VER		;//ｾﾝｻのﾃｰﾌﾞﾙ番号1~99 HEX data
//	=========================================
	extern	U2b	PVP_PAR_A_CHAR		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
	extern	U2b	PVP_PAR_B_CHAR		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
	extern	U2b	PVP_TBL_A_CHAR		;//ｾﾝｻのﾃｰﾌﾞﾙ番号()
	extern	U2b	PVP_TBL_B_CHAR		;//ｾﾝｻのﾃｰﾌﾞﾙ番号()

//;	======= V05j 2007-11-14 COP2ﾊﾞｰｼﾞｮﾝ追加 =====
	extern	U2b	PVP_CB_C_VER[6]		;//ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
	extern	U2b	PVP_PAR_C_VER		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
	extern	U2b	PVP_PAR_C_CHAR		;//ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
	extern	U2b	PVP_TBL_C_VER		;//ﾃｰﾌﾞﾙﾊﾞｰｼﾞｮﾝ HEX data（未使用）
	extern	U2b	PVP_TBL_C_CHAR		;//ﾃｰﾌﾞﾙﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)

//;	*******************************************
//;	***					***
//;	***	SH2←SH4　ﾊﾝﾄﾞｼｪｲｸ		***
//;	***					***
//;	*******************************************

//;	*******************************************
//;	***					***
//;	***					***
//;	***					***
//;	*******************************************

//;	***********************************************************
//;	***		2014年 3月以降の追加はここ		***
//;	***********************************************************
//;	=== 2014/03/17 ===	SHIMA
	extern	U2b	SVP_KAJAREA_SNO		;//荷重測定範囲 開始工程No.
	extern	U2b	SVP_KAJAREA_SAG		;//荷重測定範囲 開始角度
	extern	U2b	SVP_KAJAREA_ENO		;//荷重測定範囲 終了工程No.
	extern	U2b	SVP_KAJAREA_EAG		;//荷重測定範囲 終了角度
	extern	U2b	SVP_KAJAREA_SEL		;//記録荷重選択

//;	=== 2014/04/14 ===	SHIMA
	extern	U2b	SVP_KATTCH_SAG		;//タッチ位置検出角度
	extern	U2b	SVP_KATTCH_EAG		;//タッチ位置検出角度

//;	=== 2014/04/14 ===	SHIMA
	extern	U4b	SVP_KANDO_A21		;//感度
	extern	U4b	SVP_UPDATA_A21		;//上限
	extern	U4b	SVP_DNDATA_A21		;//下限
	extern	U4b	SVP_GENITI_A21		;//現位置
	extern	U2b	SVP_MODORI_A21		;//戻り量
	extern	U2b	SVP_DNSTOP_A21		;//下降停止
	extern	U2b	SVP_UPSTOP_A21		;//上昇停止
	extern	U2b	SVP_SSEIDO_A21		;//制御精度
	extern	U2b	SVP_SL_TENPOS		;//スライド自動調整の小数点位置
	extern	U2b	SVP_SLPOS_DIR		;//位置決め方向


//;	-------------- 最大値選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	extern	U2b	SVP_OVERE1_A26	;// 荷重計　オーバーロード１
	extern	U2b	SVP_ROALM1_A26	;// 荷重計　ロアーリッミト１
	extern	U2b	SVP_OVERE2_A26	;// 荷重計　オーバーロード２
	extern	U2b	SVP_ROALM2_A26	;// 荷重計　ロアーリッミト２
	extern	U2b	SVP_OVERE3_A26	;// 荷重計　オーバーロード３
	extern	U2b	SVP_ROALM3_A26	;// 荷重計　ロアーリッミト３

//;	-------------- 最小(ﾏｲﾅｽ最大)選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	extern	U2b	SVP_OVERE1_A27	;// 荷重計　オーバーロード１ 　（最小値）
	extern	U2b	SVP_ROALM1_A27	;// 荷重計　ロアーリッミト１  　（最小値）
	extern	U2b	SVP_OVERE2_A27	;// 荷重計　オーバーロード２  　（最小値）
	extern	U2b	SVP_ROALM2_A27	;// 荷重計　ロアーリッミト２  　（最小値）
	extern	U2b	SVP_OVERE3_A27	;// 荷重計　オーバーロード３  　（最小値）
	extern	U2b	SVP_ROALM3_A27	;// 荷重計　ロアーリッミト３  　（最小値）

//;	-------------- 振幅選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
	extern	U2b	SVP_OVERE1_A28	;// 荷重計　オーバーロード１ 　（振幅）
	extern	U2b	SVP_ROALM1_A28	;// 荷重計　ロアーリッミト１  　（振幅）
	extern	U2b	SVP_OVERE2_A28	;// 荷重計　オーバーロード２  　（振幅）
	extern	U2b	SVP_ROALM2_A28	;// 荷重計　ロアーリッミト２  　（振幅）
	extern	U2b	SVP_OVERE3_A28	;// 荷重計　オーバーロード３  　（振幅）
	extern	U2b	SVP_ROALM3_A28	;// 荷重計　ロアーリッミト３  　（振幅）



//;	=== 2014-06-09(2014/03/12) ===
	extern	U2b	SVP_KAJOBJ_HAB		;//荷重完了範囲

//;	=== 2014/08/27 ===	SHIMA
	extern	U2b	SVP_INTLIM_SNO		;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　行程
	extern	U2b	SVP_INTLIM_AGL		;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　角度
	extern	U4b	SVP_INTLIM_POS		;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　位置
	extern	U2b	SVP_WTTIM_MAX		;//ｽﾗｲﾄﾞ自動待機機能  待機時間上限

//;	=== 2014/09/02 ===	SHIMA
	extern	U2b	SVP_RCAMON_SA00;				/* ロータリカム０１  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST00;				/* ロータリカム０１  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA00;				/* ロータリカム０１  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST00;				/* ロータリカム０１  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA01;				/* ロータリカム０２  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST01;				/* ロータリカム０２  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA01;				/* ロータリカム０２  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST01;				/* ロータリカム０２  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA02;				/* ロータリカム０３  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST02;				/* ロータリカム０３  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA02;				/* ロータリカム０３  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST02;				/* ロータリカム０３  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA03;				/* ロータリカム０４  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST03;				/* ロータリカム０４  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA03;				/* ロータリカム０４  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST03;				/* ロータリカム０４  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA04;				/* ロータリカム０５  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST04;				/* ロータリカム０５  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA04;				/* ロータリカム０５  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST04;				/* ロータリカム０５  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA05;				/* ロータリカム０６  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST05;				/* ロータリカム０６  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA05;				/* ロータリカム０６  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST05;				/* ロータリカム０６  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA06;				/* ロータリカム０７  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST06;				/* ロータリカム０７  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA06;				/* ロータリカム０７  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST06;				/* ロータリカム０７  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA07;				/* ロータリカム０８  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST07;				/* ロータリカム０８  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA07;				/* ロータリカム０８  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST07;				/* ロータリカム０８  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA08;				/* ロータリカム０９  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST08;				/* ロータリカム０９  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA08;				/* ロータリカム０９  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST08;				/* ロータリカム０９  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA09;				/* ロータリカム１０  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST09;				/* ロータリカム１０  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA09;				/* ロータリカム１０  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST09;				/* ロータリカム１０  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA10;				/* ロータリカム１１  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST10;				/* ロータリカム１１  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA10;				/* ロータリカム１１  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST10;				/* ロータリカム１１  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA11;				/* ロータリカム１２  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST11;				/* ロータリカム１２  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA11;				/* ロータリカム１２  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST11;				/* ロータリカム１２  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA12;				/* ロータリカム１３  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST12;				/* ロータリカム１３  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA12;				/* ロータリカム１３  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST12;				/* ロータリカム１３  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA13;				/* ロータリカム１４  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST13;				/* ロータリカム１４  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA13;				/* ロータリカム１４  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST13;				/* ロータリカム１４  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA14;				/* ロータリカム１５  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST14;				/* ロータリカム１５  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA14;				/* ロータリカム１５  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST14;				/* ロータリカム１５  OFF進角  時間	*/
	extern	U2b	SVP_RCAMON_SA15;				/* ロータリカム１６  ON進角  角度	*/
	extern	U2b	SVP_RCAMON_ST15;				/* ロータリカム１６  ON進角  時間	*/
	extern	U2b	SVP_RCAMOF_SA15;				/* ロータリカム１６  OFF進角  角度	*/
	extern	U2b	SVP_RCAMOF_ST15;				/* ロータリカム１６  OFF進角  時間	*/

	extern	U2b	SVP_SMPMAX_CNT2		;// ｻﾝﾌﾟﾘﾝｸﾞ　最大個数(SIT)
	extern	U2b	SVP_SMPCYC_TIM2		;// ｻﾝﾌﾟﾘﾝｸﾞ　周期(SIT)

	extern	U2b	SVP_MOTREP_STGS			;//繰り返し開始行程
	extern	U2b	SVP_MOTREP_STGE			;//繰り返し終了行程
	extern	U2b	SVP_MOTREP_SPD			;//繰り返し戻り速度
	extern	U2b	SVP_MOTREP_CNT			;//繰り返し回数

	extern	U2b	SVP_ROTCAM_ONR			;//ﾛｰﾀﾘｶﾑ ON行程 ﾘﾋﾟｰﾄ戻り
	extern	U2b	SVP_ROTCAM_OFR			;//ﾛｰﾀﾘｶﾑ OFF行程 ﾘﾋﾟｰﾄ戻り
	extern	U2b	SVP_EJECAM_ONR			;//ｴｼﾞｪｸﾀ ON行程 ﾘﾋﾟｰﾄ戻り
	extern	U2b	SVP_EJECAM_OFR			;//ｴｼﾞｪｸﾀ OFF行程 ﾘﾋﾟｰﾄ戻り
	extern	U2b	SVP_MISCAM_ONR			;//ﾐｽﾌｨｰﾄﾞ  ON行程 ﾘﾋﾟｰﾄ戻り
	extern	U2b	SVP_MISCAM_OFR			;//ﾐｽﾌｨｰﾄﾞ  OFF行程 ﾘﾋﾟｰﾄ戻り

	extern	U2b	SVP_MOT_FIX				;//一定速度領域 行程BIT情報


//;	***********************************************************
//;	***		実測関連				***
//;	***********************************************************

//;	=== 2014/04/16 SHIMA ===
	extern	U2b	PVP_CKAGL_OVBIT	;//赤表示(BIT0~BIT9)
	extern	U2b	PVP_CKLMT_AGLTOP[10]		;//

//;	=== 2014/08/27 ===	SHIMA
	extern	U2b	PVP_WTJUD_SNO		;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（行程）
	extern	U2b	PVP_WTJUD_AGL		;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（角度）
	extern	U4b	PVP_WTJUD_POS		;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（位置）

//;	=== 2014/09/02 ===	SHIMA
	extern	U2b	PVP_SINKAKU_UPDN1	;//BITn：1=ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。
	extern	U2b	PVP_SINKAKU_UPDN2	;//BITn：1=ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。

//;	==== 2015/07/03[速度ﾘﾐｯﾄ青●表示] ====
//;	==== 2015/07/07[速度ﾘﾐｯﾄ対象行程] ====
	extern	U2b	PVP_CKSPD_LMBIT;			//青●表示(BIT0~BIT9 BIT15:戻速度)
	extern	U2b	PVP_CKSPD_STPBT;				//速度ﾘﾐｯﾄ対象行程 BIT0~BIT9,BIT15(ﾁｪｯｸ対象行程)


//;	=== 2021-06-24[H2W-CE3:2020-08-11 ﾀﾞｲﾊｲﾄANSﾊﾞｯｸ]=======
	extern	U4b	PVP_ATSLID_OBJ1		;// スライド自動調節設定値（現在動作中）0.001mmのANSﾊﾞｯｸ [1A28]
