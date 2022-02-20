/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ＤＰＲＡＭ ← ＦＲＡＭ	データ転送処理				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_wk_ext.h"

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		GMN_PAR020;

/* 外部参照関数定義 -------------------------------------------------- */
extern	void	DPB_SEND_2B(U2b *Src);
extern	void	DPB_SEND_4B(U4b *Src);


/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SRV	(void)
{
	S4b		ofs;

	SVP_RNADIR_SEL1		= SV_RNADIR_SEL1;				/* ﾘﾆｱｾﾝｻ極性			*/
	DPB_SEND_2B(&SVP_RNADIR_SEL1);
	SVP_INCDIR_SEL1		= SV_INCDIR_SEL1;				/* PG極性				*/
	DPB_SEND_2B(&SVP_INCDIR_SEL1);
	SVP_INCPLS_1REV		= SV_INCPLS_1REV;				/* PG1回転ﾊﾟﾙｽ選択		*/
	DPB_SEND_2B(&SVP_INCPLS_1REV);
	SVP_INCPLS_HOSN		= SV_INCPLS_HOSN;				/* PG補正N ﾓｰﾀN回		*/
	DPB_SEND_2B(&SVP_INCPLS_HOSN);
	SVP_INCPLS_HOSM		= SV_INCPLS_HOSM;				/* PG補正M ｸﾗﾝｸ角M		*/
	DPB_SEND_2B(&SVP_INCPLS_HOSM);
	SVP_MOTRPM_MAXM		= SV_MOTRPM_MAXM;				/* ﾓｰﾀ最大回転数		*/
	DPB_SEND_2B(&SVP_MOTRPM_MAXM);
	SVP_MOTMAX_FREQ		= SV_MOTMAX_FREQ;				/* ﾓｰﾀ最大指令周波数	*/
	DPB_SEND_4B((U4b *)&SVP_MOTMAX_FREQ);
//2002-10-16
//	SVP_RNAORG_POS1		= SV_RNAORG_POS1;				/* 機械原点入力			*/
//	SVP_RNAPOS_MAXP		= SV_RNAPOS_MAXP;				/* 機械上限				*/
//	SVP_RNAPOS_MINP		= SV_RNAPOS_MINP;				/* 機械下限				*/
//2014/12/11	SVP_RNAORG_POS1	= cnv_inch_mm(SV_RNAORG_POS1, 2);	/* 機械原点入力			*/
	SVP_RNAORG_POS1	= SV_RNAORG_POS1;					/* 機械原点入力	mm固定	*/
	DPB_SEND_4B((U4b *)&SVP_RNAORG_POS1);

//V06n
//	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV_RNAPOS_MAXP, 2);	/* 機械上限				*/
//	SVP_RNAPOS_MINP	= cnv_inch_mm(SV_RNAPOS_MINP, 2);	/* 機械下限				*/
//2014/12/11	SVP_RNAPOS_MAXP	= cnv_inch_mm(SV0_RNAPOS_MAXO, 2);	/* 機械上限				*/
	SVP_RNAPOS_MAXP	= SV0_RNAPOS_MAXO;					/* 機械上限		mm固定	*/
	DPB_SEND_4B(&SVP_RNAPOS_MAXP);
//2014/12/11	SVP_RNAPOS_MINP	= cnv_inch_mm(SV0_RNAPOS_MINO, 2);	/* 機械下限				*/
	SVP_RNAPOS_MINP	= SV0_RNAPOS_MINO;					/* 機械下限		mm固定	*/
	DPB_SEND_4B(&SVP_RNAPOS_MINP);

//V01 (MOV)	SVP_DNDINC_SPD1		= SV_DNDINC_SPD1;				/* 段取速度				*/
	SVP_UPAREA_SPD1		= SV_UPAREA_SPD1;				/* 待機点復帰速度		*/
	DPB_SEND_2B(&SVP_UPAREA_SPD1);
	SVP_STDINC_SPD1		= SV_STDINC_SPD1;				/* 寸動速度				*/
	DPB_SEND_2B(&SVP_STDINC_SPD1);
	SVP_REVDAT_SPD1		= SV_REVDAT_SPD1;				/* 予備速度１			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD1);
	SVP_REVDAT_SPD2		= SV_REVDAT_SPD2;				/* 予備速度２			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD2);
	SVP_REVDAT_SPD3		= SV_REVDAT_SPD3;				/* 予備速度３			*/
	DPB_SEND_2B(&SVP_REVDAT_SPD3);
	SVP_TEPDAT_SPD1		= SV_TEPDAT_SPD1;				/* 手動ﾊﾟﾙｻ速度			*/
	DPB_SEND_2B(&SVP_TEPDAT_SPD1);
	SVP_TEPLAT_DAT1		= SV_TEPLAT_DAT1;				/* 手動ﾊﾟﾙｻ低倍率		*/
	DPB_SEND_2B(&SVP_TEPLAT_DAT1);
	SVP_TEPLAT_DAT2		= SV_TEPLAT_DAT2;				/* 手動ﾊﾟﾙｻ高倍率		*/
	DPB_SEND_2B(&SVP_TEPLAT_DAT2);

	SVP_INCPOS_KP01		= SV_INCPOS_KP01;				/* PG位置比例ｹﾞｲﾝ		*/
	DPB_SEND_2B(&SVP_INCPOS_KP01);
	SVP_RNAPOS_KP01		= SV_RNAPOS_KP01;				/* ﾘﾆｱ位置比例ｹﾞｲﾝ		*/
	DPB_SEND_2B(&SVP_RNAPOS_KP01);
	SVP_ACCLAT_TIM1		= SV_ACCLAT__TIM1;				/* 加減速時間			*/
	DPB_SEND_2B(&SVP_ACCLAT_TIM1);
	SVP_SSCURV_TIM1		= SV_SSCURV_TIM1;				/* Ｓ字時間				*/
	DPB_SEND_2B(&SVP_SSCURV_TIM1);
//2002-10-16
//	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* 上死点ｲﾝﾎﾟｼﾞｼｮﾝ		*/
//	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* 下死点ｲﾝﾎﾟｼﾞｼｮﾝ		*/
//	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* 目標位置ｲﾝﾎﾟｼﾞｼｮﾝ	*/
/* V00m */
//	SVP_UPAREA_INP1	= cnv_inch_mm(SV_UPAREA_INP1, 2);	/* 上死点ｲﾝﾎﾟｼﾞｼｮﾝ		*/
//	SVP_DNAREA_INP1	= cnv_inch_mm(SV_DNAREA_INP1, 2);	/* 下死点ｲﾝﾎﾟｼﾞｼｮﾝ		*/
//	SVP_OBJARA_INP1	= cnv_inch_mm(SV_OBJARA_INP1, 2);	/* 目標位置ｲﾝﾎﾟｼﾞｼｮﾝ	*/
	SVP_UPAREA_INP1		= SV_UPAREA_INP1;				/* 予備		*/
	DPB_SEND_2B(&SVP_UPAREA_INP1);
	SVP_DNAREA_INP1		= SV_DNAREA_INP1;				/* 機械伸び量限界		*/
	DPB_SEND_2B(&SVP_DNAREA_INP1);
	SVP_OBJARA_INP1		= SV_OBJARA_INP1;				/* 回転･ｵｰﾌﾟﾝｲﾝﾎﾟｼﾞｼｮﾝ	*/
	DPB_SEND_2B(&SVP_OBJARA_INP1);

	SVP_INPPOS_TIM1		= SV_INPPOS_TIM1;				/* ｲﾝﾎﾟｼﾞｼｮﾝﾁｪｯｸ時間	*/
	DPB_SEND_2B(&SVP_INPPOS_TIM1);

//2002-10-16
//	SVP_ARACHK_LNG1		= SV_ARACHK_LNG1;				/* 上／下死点通過判定量	*/
//2014/12/11	SVP_ARACHK_LNG1	= cnv_inch_mm(SV_ARACHK_LNG1, 2);	/* 上／下死点通過判定量	*/
	SVP_ARACHK_LNG1	= SV_ARACHK_LNG1;				;	/* 上／下死点通過判定量		mm固定	*/
	DPB_SEND_2B(&SVP_ARACHK_LNG1);
	SVP_UPAREA_DIG1		= SV_UPAREA_DIG1; 				/* 回転時待機点(上死点)	*/
	DPB_SEND_2B(&SVP_UPAREA_DIG1);

	SVP_UPAREA_JUDG		= SV_UPAREA_JUDG;				/* 上死点判定範囲		*/
	DPB_SEND_4B(&SVP_UPAREA_JUDG);
	SVP_DNAREA_JUDG		= SV_DNAREA_JUDG;				/* 反転設定不可範囲		*/
	DPB_SEND_4B(&SVP_DNAREA_JUDG);
//2002-10-16
//2002-08-21:追加
//	SVP_RNA_STLORK		= SV_RNA_STLORK;				//ストローク設定(4)
//2014/12/11	SVP_RNA_STLORK	= cnv_inch_mm(SV_RNA_STLORK, 2);	//ストローク設定(4)
	SVP_RNA_STLORK	= SV_RNA_STLORK;					//ストローク設定(4)		mm固定
	DPB_SEND_4B((U4b *)&SVP_RNA_STLORK);
	SVP_OUTPLS_HOSA		= SV_OUTPLS_HOSA;				//出力ﾊﾟﾙｽ補正A(2)
	DPB_SEND_2B(&SVP_OUTPLS_HOSA);
	SVP_OUTPLS_HOSB		= SV_OUTPLS_HOSB;				//出力ﾊﾟﾙｽ補正B(2)
	DPB_SEND_2B(&SVP_OUTPLS_HOSB);
	SVP_UPHOLD_DIG		= SV_UPHOLD_DIG;				//上昇ﾎｰﾙﾄﾞ角度(2)
	DPB_SEND_2B(&SVP_UPHOLD_DIG);
	SVP_MACINE_SEL1		= SV_MACINE_SEL1;				//予備（機種選択１）(2)
	DPB_SEND_2B(&SVP_MACINE_SEL1);

	SVP_INCHEN_ELNG		= SV_INCHEN_ELNG;				/* PG偏差異常幅			*/
	DPB_SEND_2B(&SVP_INCHEN_ELNG);
	SVP_INCENC_ELNG		= SV_INCENC_ELNG;				/* PG-ENC一致量			*/
	DPB_SEND_2B(&SVP_INCENC_ELNG);
//2002-10-16
//	SVP_INCRNA_ELNG		= SV_INCRNA_ELNG;				/* PG-ﾘﾆｱ一致量			*/
//2014/12/11	SVP_INCRNA_ELNG	= cnv_inch_mm(SV_INCRNA_ELNG, 2);	/* PG-ﾘﾆｱ一致量			*/
	SVP_INCRNA_ELNG	= SV_INCRNA_ELNG;					/* PG-ﾘﾆｱ一致量		mm固定	*/
	DPB_SEND_2B(&SVP_INCRNA_ELNG);
	SVP_INCSTP_ELNG		= SV_INCSTP_ELNG;				/* PG停止異常量			*/
	DPB_SEND_2B(&SVP_INCSTP_ELNG);
//2002-10-16
//	SVP_RNASTP_ELNG		= SV_RNASTP_ELNG;				/* ﾘﾆｱ停止異常量		*/
//2014/12/11	SVP_RNASTP_ELNG	= cnv_inch_mm(SV_RNASTP_ELNG, 2);	/* ﾘﾆｱ停止異常量		*/
	SVP_RNASTP_ELNG	= SV_RNASTP_ELNG;					/* ﾘﾆｱ停止異常量	mm固定	*/
	DPB_SEND_2B(&SVP_RNASTP_ELNG);
	SVP_INCREV_ELNG		= SV_INCREV_ELNG;				/* PG逆転異常量			*/
	DPB_SEND_2B(&SVP_INCREV_ELNG);
//2002-10-16
//	SVP_RNAREV_ELNG		= SV_RNAREV_ELNG;				/* ﾘﾆｱ逆転異常量		*/
//	SVP_DAIHAI_LNG1		= SV_DAIHAI_LNG1;				/* ﾀﾞｲﾊｲﾄ補正比較値(小)	*/
//	SVP_DAIHAI_LNG2		= SV_DAIHAI_LNG2;				/* ﾀﾞｲﾊｲﾄ補正比較値(中)	*/
//	SVP_DAIHAI_LNG3		= SV_DAIHAI_LNG3;				/* ﾀﾞｲﾊｲﾄ補正比較値(大)	*/
//2014/12/11	SVP_RNAREV_ELNG	= cnv_inch_mm(SV_RNAREV_ELNG, 2);	/* ﾘﾆｱ逆転異常量		*/
	SVP_RNAREV_ELNG	= SV_RNAREV_ELNG;					/* ﾘﾆｱ逆転異常量	mm固定	*/
	DPB_SEND_2B(&SVP_RNAREV_ELNG);

//V06n
//	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV_DAIHAI_LNG1, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(小)	*/
//	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV_DAIHAI_LNG2, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(中)	*/
//2014/12/11	SVP_DAIHAI_LNG1	= cnv_inch_mm(SV0_DAIHAI_LNG1O, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(小)	*/
	SVP_DAIHAI_LNG1	= SV0_DAIHAI_LNG1O;					/* ﾀﾞｲﾊｲﾄ補正比較値(小)		mm固定	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG1);
//2014/12/11	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV0_DAIHAI_LNG2O, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(中)	*/
//2015/09/29	SVP_DAIHAI_LNG2	= cnv_inch_mm(SV0_DAIHAI_LNG2O, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(中)		mm固定	*/
	SVP_DAIHAI_LNG2	= SV0_DAIHAI_LNG2O;					/* ﾀﾞｲﾊｲﾄ補正比較値(中)		mm固定	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG2);

//2014/12/11	SVP_DAIHAI_LNG3	= cnv_inch_mm(SV_DAIHAI_LNG3, 2);	/* ﾀﾞｲﾊｲﾄ補正比較値(大)	*/
	SVP_DAIHAI_LNG3	= SV_DAIHAI_LNG3;					/* ﾀﾞｲﾊｲﾄ補正比較値(大)		mm固定	*/
	DPB_SEND_2B(&SVP_DAIHAI_LNG3);

	SVP_AMPERR_VLT1		= SV_AMPERR_VLT1;				/* 過負荷電圧1			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT1);
	SVP_AMPERR_TIM1		= SV_AMPERR_TIM1;				/* 過負荷時間1			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM1);
	SVP_AMPERR_VLT2		= SV_AMPERR_VLT2;				/* 過負荷電圧2			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT2);
	SVP_AMPERR_TIM2		= SV_AMPERR_TIM2;				/* 過負荷時間2			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM2);
	SVP_AMPERR_VLT3		= SV_AMPERR_VLT3;				/* 過負荷電圧3			*/
	DPB_SEND_2B(&SVP_AMPERR_VLT3);
	SVP_AMPERR_TIM3		= SV_AMPERR_TIM3;				/* 過負荷時間3			*/
	DPB_SEND_2B(&SVP_AMPERR_TIM3);

//2002-08-08:追加
//	SVP_BREAK_DIG		= SV_BRDIG_C1 * 10;				//ﾌﾞﾚｰｷ角度   0.1度
	SVP_BREAK_DIG		= SV_BRDIG_C1;					//ﾌﾞﾚｰｷ角度   0.1度
	DPB_SEND_2B(&SVP_BREAK_DIG);
	SVP_BREAK_TIM1		= SV_BRTIME_C1;					//ブレーキタイマ設定
	DPB_SEND_2B(&SVP_BREAK_TIM1);

	SVP_CNT_CNT			= SV_RNZRPM_A12;				//連続回転設定値
	DPB_SEND_2B(&SVP_CNT_CNT);
	SVP_CNT_TIM			= SV_RNZTIM_A12;				//連続タイマ設定値
	DPB_SEND_2B(&SVP_CNT_TIM);
	SVP_WT_DIG1			= SV_TAIKI1_A12;				//待機点選択1
	DPB_SEND_2B(&SVP_WT_DIG1);
	SVP_WT_DIG2			= SV_TAIKI2_A12;				//待機点選択2
	DPB_SEND_2B(&SVP_WT_DIG2);
	SVP_WT_DIG3			= SV_TAIKI3_A12;				//待機点選択3
	DPB_SEND_2B(&SVP_WT_DIG3);
	SVP_MOTWT_TIM		= SV_HOSTIM_A12;				//起動保証時間
	DPB_SEND_2B(&SVP_MOTWT_TIM);
	SVP_PSMOD_SEL		= SV_PSDIMD_A1;					//PSID　ﾓｰﾄﾞ選択
	DPB_SEND_2B(&SVP_PSMOD_SEL);

	/* V00m */
	SVP_NEG_OFS_LNG		= SV_NEG_OFS_LNG;				//反転下限距離
	DPB_SEND_4B((U4b *)&SVP_NEG_OFS_LNG);
	SVP_AMP100P_VLT		= SV_AMP100P_VLT;				//過負荷ﾓﾆﾀ100%電圧
	DPB_SEND_2B(&SVP_AMP100P_VLT);

	/* V01v */
	SVP_LSAABN_AGL1		= SV_LSAABN_AGL1;				//LSA異常検知の角度1
	DPB_SEND_4B(&SVP_LSAABN_AGL1);
	SVP_LSAABN_AGL2		= SV_LSAABN_AGL2;				//LSA異常検知の角度2
	DPB_SEND_4B(&SVP_LSAABN_AGL2);
	SVP_PLSALO_PLS		= SV_PLSALO_PLS;				//パルサ倍率低
	DPB_SEND_2B(&SVP_PLSALO_PLS);
	SVP_PLSAHI_PLS		= SV_PLSAHI_PLS;				//パルサ倍率高
	DPB_SEND_2B(&SVP_PLSAHI_PLS);
	SVP_MOADR0_SQH		= SV_MOADR0_SQH;				// モニタアドレス０　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR0_SQH);
	SVP_MOADR0_SQL		= SV_MOADR0_SQL;				// モニタアドレス０　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR0_SQL);
	SVP_MOADR1_SQH		= SV_MOADR1_SQH;				// モニタアドレス１　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR1_SQH);
	SVP_MOADR1_SQL		= SV_MOADR1_SQL;				// モニタアドレス１　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR1_SQL);
	SVP_MOADR2_SQH		= SV_MOADR2_SQH;				// モニタアドレス２　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR2_SQH);
	SVP_MOADR2_SQL		= SV_MOADR2_SQL;				// モニタアドレス２　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR2_SQL);
	SVP_MOADR3_SQH		= SV_MOADR3_SQH;				// モニタアドレス３　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR3_SQH);
	SVP_MOADR3_SQL		= SV_MOADR3_SQL;				// モニタアドレス３　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR3_SQL);
	SVP_MOADR4_SQH		= SV_MOADR4_SQH;				// モニタアドレス４　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR4_SQH);
	SVP_MOADR4_SQL		= SV_MOADR4_SQL;				// モニタアドレス４　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR4_SQL);
	SVP_MOADR5_SQH		= SV_MOADR5_SQH;				// モニタアドレス５　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR5_SQH);
	SVP_MOADR5_SQL		= SV_MOADR5_SQL;				// モニタアドレス５　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR5_SQL);
	SVP_MOADR6_SQH		= SV_MOADR6_SQH;				// モニタアドレス６　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR6_SQH);
	SVP_MOADR6_SQL		= SV_MOADR6_SQL;				// モニタアドレス６　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR6_SQL);
	SVP_MOADR7_SQH		= SV_MOADR7_SQH;				// モニタアドレス７　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR7_SQH);
	SVP_MOADR7_SQL		= SV_MOADR7_SQL;				// モニタアドレス７　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR7_SQL);
	SVP_MOADR8_SQH		= SV_MOADR8_SQH;				// モニタアドレス８　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR8_SQH);
	SVP_MOADR8_SQL		= SV_MOADR8_SQL;				// モニタアドレス８　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR8_SQL);
	SVP_MOADR9_SQH		= SV_MOADR9_SQH;				// モニタアドレス９　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR9_SQH);
	SVP_MOADR9_SQL		= SV_MOADR9_SQL;				// モニタアドレス９　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADR9_SQL);
	SVP_MOADRA_SQH		= SV_MOADRA_SQH;				// モニタアドレス１０　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRA_SQH);
	SVP_MOADRA_SQL		= SV_MOADRA_SQL;				// モニタアドレス１０　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRA_SQL);
	SVP_MOADRB_SQH		= SV_MOADRB_SQH;				// モニタアドレス１１　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRB_SQH);
	SVP_MOADRB_SQL		= SV_MOADRB_SQL;				// モニタアドレス１１　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRB_SQL);
	SVP_MOADRC_SQH		= SV_MOADRC_SQH;				// モニタアドレス１２　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRC_SQH);
	SVP_MOADRC_SQL		= SV_MOADRC_SQL;				// モニタアドレス１２　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRC_SQL);
	SVP_MOADRD_SQH		= SV_MOADRD_SQH;				// モニタアドレス１３　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRD_SQH);
	SVP_MOADRD_SQL		= SV_MOADRD_SQL;				// モニタアドレス１３　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRD_SQL);
	SVP_MOADRE_SQH		= SV_MOADRE_SQH;				// モニタアドレス１４　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRE_SQH);
	SVP_MOADRE_SQL		= SV_MOADRE_SQL;				// モニタアドレス１４　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRE_SQL);
	SVP_MOADRF_SQH		= SV_MOADRF_SQH;				// モニタアドレス１５　ｼｰｹﾝｽ上位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRF_SQH);
	SVP_MOADRF_SQL		= SV_MOADRF_SQL;				// モニタアドレス１５　ｼｰｹﾝｽ下位　V01v　060713
	DPB_SEND_2B(&SVP_MOADRF_SQL);

	/* COP2関係 */
	SVP_ORGSOK_PLS		= SV_ORGSOK_PLS;		//原点測定ﾊﾟﾙｽ
	DPB_SEND_4B(&SVP_ORGSOK_PLS);
	SVP_ORGCAL_DAT1		= SV_ORGCAL_DAT1;		//演算係数1
	DPB_SEND_4B(&SVP_ORGCAL_DAT1);
	SVP_ORGCAL_DAT2		= SV_ORGCAL_DAT2;		//演算係数2
	DPB_SEND_4B(&SVP_ORGCAL_DAT2);
	SVP_ORGCAL_DAT3		= SV_ORGCAL_DAT3;		//演算係数3
	DPB_SEND_4B(&SVP_ORGCAL_DAT3);
	SVP_ORGCAL_DAT4		= SV_ORGCAL_DAT4;		//演算係数4
	DPB_SEND_4B(&SVP_ORGCAL_DAT4);
	SVP_ORGCAL_DAT5		= SV_ORGCAL_DAT5;		//演算係数5
	DPB_SEND_4B(&SVP_ORGCAL_DAT5);
	SVP_ORGCAL_DAT6		= SV_ORGCAL_DAT6;		//演算係数6
	DPB_SEND_4B(&SVP_ORGCAL_DAT6);
	SVP_ORGSTRK_LEN1	= SV_ORGSTRK_LEN1;		//ｽﾄﾛｰｸ1
	DPB_SEND_4B(&SVP_ORGSTRK_LEN1);
	SVP_ORGSTRK_LEN2	= SV_ORGSTRK_LEN2;		//ｽﾄﾛｰｸ2
	DPB_SEND_4B(&SVP_ORGSTRK_LEN2);
	SVP_RNAORGMEM_LEG1	= SV_RNAORGMEM_LEG1;	//ﾘﾆｱ原点1軸記憶
	DPB_SEND_4B(&SVP_RNAORGMEM_LEG1);
////	SVP_RNAORG_PLS1		= SV_RNAORG_PLS1;		//ﾊﾞｯｸｱｯﾌﾟ実測
	SVP_RNAORGMEM_LEG2	= SV_RNAORGMEM_LEG2;	//ﾘﾆｱ原点2軸記憶
	DPB_SEND_4B(&SVP_RNAORGMEM_LEG2);
////	SVP_RNAORG_PLS2		= SV_RNAORG_PLS2;		//ﾊﾞｯｸｱｯﾌﾟ実測
////	SVP_RNAORG_SIN1		= SV_RNAORG_SIN1;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
////	SVP_RNAORG_SIN2		= SV_RNAORG_SIN2;		//ﾊﾞｯｸｱｯﾌﾟ実測符号
	SVP_ORGRUP_DEG		= SV_ORGRUP_DEG;		//原点右区間上
	DPB_SEND_2B(&SVP_ORGRUP_DEG);
	SVP_ORGRDN_DEG		= SV_ORGRDN_DEG;		//原点右区間下
	DPB_SEND_2B(&SVP_ORGRDN_DEG);
	SVP_ORGLUP_DEG		= SV_ORGLUP_DEG;		//原点左区間上
	DPB_SEND_2B(&SVP_ORGLUP_DEG);
	SVP_ORGLDN_DEG		= SV_ORGLDN_DEG;		//原点左区間下
	DPB_SEND_2B(&SVP_ORGLDN_DEG);
	SVP_ORGMEM_DEG1		= SV_ORGMEM_DEG1;		//角度1軸
	DPB_SEND_2B(&SVP_ORGMEM_DEG1);
	SVP_ORGMEM_DEGS1	= SV_ORGMEM_DEGS1;		//角度1軸　ON/OFF
	DPB_SEND_2B(&SVP_ORGMEM_DEGS1);
	SVP_ORGMEM_DEG2		= SV_ORGMEM_DEG2;		//角度2軸
	DPB_SEND_2B(&SVP_ORGMEM_DEG2);
	SVP_ORGMEM_DEGS2	= SV_ORGMEM_DEGS2;		//角度2軸　ON/OFF
	DPB_SEND_2B(&SVP_ORGMEM_DEGS2);
	SVP_ORGMPL_SEL1		= SV_ORGMPL_SEL1;		//手ﾊﾟﾙｻ選択1軸　ON/OFF
	DPB_SEND_2B(&SVP_ORGMPL_SEL1);
	SVP_ORGMPL_SEL2		= SV_ORGMPL_SEL2;		//手ﾊﾟﾙｻ選択2軸　ON/OFF
	DPB_SEND_2B(&SVP_ORGMPL_SEL2);
	SVP_HOSRAG_PLS1		= SV_HOSRAG_PLS1;		//軸間補正範囲１
	DPB_SEND_2B(&SVP_HOSRAG_PLS1);
	SVP_HOSRAG_PLS2		= SV_HOSRAG_PLS2;		//軸間補正範囲２
	DPB_SEND_2B(&SVP_HOSRAG_PLS2);
	SVP_HOSEI_SPD		= SV_HOSEI_SPD;			//補正速度
	DPB_SEND_2B(&SVP_HOSEI_SPD);
	SVP_MANSAM_LEN		= SV_MANSAM_LEN;		//手動時同期
	DPB_SEND_2B(&SVP_MANSAM_LEN);
	SVP_DANSAM_LEN		= SV_DANSAM_LEN;		//段取字同期
	DPB_SEND_2B(&SVP_DANSAM_LEN);
	SVP_RUNSAMER_LEN1	= SV_RUNSAMER_LEN1;		//運転同期異常１
	DPB_SEND_2B(&SVP_RUNSAMER_LEN1);
	SVP_RUNSAMER_LEN2	= SV_RUNSAMER_LEN2;		//運転同期異常２
	DPB_SEND_2B(&SVP_RUNSAMER_LEN2);
	SVP_MANSAMER_PLS	= SV_MANSAMER_PLS;		//手動同期異常
	DPB_SEND_2B(&SVP_MANSAMER_PLS);
	SVP_RUNSAMER_PLS	= SV_RUNSAMER_PLS;		//運転同期異常
	DPB_SEND_2B(&SVP_RUNSAMER_PLS);
	SVP_RNADIR_SEL2		= SV_RNADIR_SEL2;		/* ﾘﾆｱｾﾝｻ極性			*/
	DPB_SEND_2B(&SVP_RNADIR_SEL2);
	SVP_ORGMEM_DEG1A	= SV_ORGMEM_DEG1A;		//角度1軸
	DPB_SEND_4B(&SVP_ORGMEM_DEG1A);
	SVP_ORGMEM_DEG2A	= SV_ORGMEM_DEG2A;		//角度2軸
	DPB_SEND_4B(&SVP_ORGMEM_DEG2A);

//V05c
	SVP_FCLS_STR_DEG	= SV_FCLS_STR_DEG	;//ﾌﾙｸﾛ開始角度
	DPB_SEND_2B(&SVP_FCLS_STR_DEG);
	SVP_FCLS_STR_HENS	= SV_FCLS_STR_HENS	;//ﾌﾙｸﾛ開始偏差
	DPB_SEND_2B(&SVP_FCLS_STR_HENS);
	SVP_FCLS_ZIKI_SPD1	= SV_FCLS_ZIKI_SPD1	;//ﾌﾙｸﾛ自起動速度1
	DPB_SEND_2B(&SVP_FCLS_ZIKI_SPD1);
	SVP_FCLS_ZIKI_SPD2	= SV_FCLS_ZIKI_SPD2	;//ﾌﾙｸﾛ自起動速度2
	DPB_SEND_2B(&SVP_FCLS_ZIKI_SPD2);
	SVP_SYNC_ERR_DEGA	= SV_SYNC_ERR_DEGA	;//同期異常領域角度A
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGA);
	SVP_SYNC_ERR_DEGB	= SV_SYNC_ERR_DEGB	;//同期異常領域角度B
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGB);
	SVP_SYNC_ERR_DEGC	= SV_SYNC_ERR_DEGC	;//同期異常領域角度C
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGC);
	SVP_SYNC_ERR_DEGD	= SV_SYNC_ERR_DEGD	;//同期異常領域角度D
	DPB_SEND_2B(&SVP_SYNC_ERR_DEGD);
	SVP_SYNC_ERR_RNAA	= SV_SYNC_ERR_RNAA	;//ﾘﾆｱ同期異常A
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAA);
	SVP_SYNC_ERR_RNAB	= SV_SYNC_ERR_RNAB	;//ﾘﾆｱ同期異常B
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAB);
	SVP_SYNC_ERR_RNAC	= SV_SYNC_ERR_RNAC	;//ﾘﾆｱ同期異常C
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAC);
	SVP_SYNC_ERR_RNAD	= SV_SYNC_ERR_RNAD	;//ﾘﾆｱ同期異常D
	DPB_SEND_2B(&SVP_SYNC_ERR_RNAD);
	SVP_SYNC_ERR_PGA	= SV_SYNC_ERR_PGA	;//PG同期異常A
	DPB_SEND_2B(&SVP_SYNC_ERR_PGA);
	SVP_SYNC_ERR_PGB	= SV_SYNC_ERR_PGB	;//PG同期異常B
	DPB_SEND_2B(&SVP_SYNC_ERR_PGB);
	SVP_SYNC_ERR_PGC	= SV_SYNC_ERR_PGC	;//PG同期異常C
	DPB_SEND_2B(&SVP_SYNC_ERR_PGC);
	SVP_SYNC_ERR_PGD	= SV_SYNC_ERR_PGD	;//PG同期異常D
	DPB_SEND_2B(&SVP_SYNC_ERR_PGD);

//V05r
	SVP_BREAK_DIG_RAT	= SV_BRDIG_C2;		//ﾌﾞﾚｰｷ角度   割合
	DPB_SEND_2B(&SVP_BREAK_DIG_RAT);
	SVP_BREAK_TIM_RAT	= SV_BRTIME_C2;		//ブレーキタイマ	割合
	DPB_SEND_2B(&SVP_BREAK_TIM_RAT);

//V06
	SVP_EP_VOF		= SV_SRVPAR_B0;		// サーボパラメータB0　　電力用ｵﾌｾｯﾄ
	DPB_SEND_2B(&SVP_EP_VOF);
	SVP_EP_VMX		= SV_SRVPAR_B1;		// サーボパラメータB1　　電力用最大値
	DPB_SEND_2B(&SVP_EP_VMX);
	SVP_EP_TRQ		= SV_SRVPAR_B2;		// サーボパラメータB2　　電力用ﾄﾙｸ値
	DPB_SEND_2B(&SVP_EP_TRQ);
	SVP_EP_LTM		= SV_SRVPAR_B3;		// サーボパラメータB3　　ﾄﾙｸ側遅れ時間
	DPB_SEND_2B(&SVP_EP_LTM);
	SVP_EP_K1		= SV_SRVPAR_B4;		// サーボパラメータB4　　調整係数A
	DPB_SEND_2B(&SVP_EP_K1);
	SVP_EP_K2		= SV_SRVPAR_B5;		// サーボパラメータB5　　調整係数B
	DPB_SEND_2B(&SVP_EP_K2);
	SVP_EP_ADJSIN	= SV_SRVPAR_B6;		// サーボパラメータB6　　調整電力符号
	DPB_SEND_2B(&SVP_EP_ADJSIN);
	SVP_EP_ADJVAL	= SV_SRVPAR_B7;		// サーボパラメータB7　　調整電力
	DPB_SEND_2B(&SVP_EP_ADJVAL);
	SVP_ECOM_BASE	= SV_SRVPAR_B8;     // サーボパラメータB8　　エコメータ基準値
	DPB_SEND_2B(&SVP_ECOM_BASE);
	SVP_ECOM_SCAL	= SV_SRVPAR_B9;     // サーボパラメータB9　　エコメータスケール
	DPB_SEND_2B(&SVP_ECOM_SCAL);
	SVP_MOTRPM_MAXP	= SV_MOTRPM_MAXP;	// サーボパラメータBA.モータ最大回転数
	DPB_SEND_2B(&SVP_MOTRPM_MAXP);
	SVP_ACCLAT_TIMP	= SV_ACCLAT__TIMP;	// サーボパラメータBB.加減速時間
	DPB_SEND_2B(&SVP_ACCLAT_TIMP);

//V06d
	if (SEQ_PAR_113 & cBIT10) {			//＋オフセット		2013/09/27
		SVP_VOLST_L	= SV_SRVPAR_BC+(GMN_PAR020*100);		// サーボパラメータBC　　電力用ｵﾌｾｯﾄ
		DPB_SEND_4B(&SVP_VOLST_L);
	}
	else if (SEQ_PAR_113 & cBIT11) {	//－オフセット
		ofs = SV_SRVPAR_BC - (GMN_PAR020*100);
		if (ofs<0) {
			ofs = 0;
		}
		SVP_VOLST_L	= ofs;									// サーボパラメータBC　　電力用ｵﾌｾｯﾄ
		DPB_SEND_4B(&SVP_VOLST_L);
	}
	else {
		SVP_VOLST_L	= SV_SRVPAR_BC;							// サーボパラメータBC　　電力用ｵﾌｾｯﾄ
		DPB_SEND_4B(&SVP_VOLST_L);
	}

	SVP_SLIDE_S		= SV_SRVPAR_BD;		// サーボパラメータBD　　電力用最大値
	DPB_SEND_4B(&SVP_SLIDE_S);
	SVP_RAD			= SV_SRVPAR_BE;		// サーボパラメータBE　　電力用ﾄﾙｸ値
	DPB_SEND_4B(&SVP_RAD);
	SVP_ORGREV_AGL	= SV_SRVPAR_BF;		// サーボパラメータBF　　ﾄﾙｸ側遅れ時間
	DPB_SEND_4B(&SVP_ORGREV_AGL);
	SVP_ORGFWD_AGL	= SV_SRVPAR_BG;		// サーボパラメータBG　　調整係数A
	DPB_SEND_4B(&SVP_ORGFWD_AGL);

//V06f
	SVP_RISE_ZWID	= (U2b)SV_SRVPAR_BH;		// サーボパラメータBH　　上昇監視ｾﾞﾛ幅
	DPB_SEND_2B(&SVP_RISE_ZWID);
	SVP_RISE_CMP1	= (U2b)SV_SRVPAR_BI;		// サーボパラメータBI　　上昇監視比較1
	DPB_SEND_2B(&SVP_RISE_CMP1);
	SVP_RISE_CMP2	= (U2b)SV_SRVPAR_BJ;		// サーボパラメータBJ　　上昇監視比較2
	DPB_SEND_2B(&SVP_RISE_CMP2);
	SVP_RISE_CMP3	= (U2b)SV_SRVPAR_BK;		// サーボパラメータBK　　上昇監視比較予備
	DPB_SEND_2B(&SVP_RISE_CMP3);
	SVP_RISE_DLY1	= (U2b)SV_SRVPAR_BL;		// サーボパラメータBL　　監視遅延1
	DPB_SEND_2B(&SVP_RISE_DLY1);
	SVP_RISE_DLY2	= (U2b)SV_SRVPAR_BM;		// サーボパラメータBM　　監視遅延2
	DPB_SEND_2B(&SVP_RISE_DLY2);

}
/****************************************************************************/
