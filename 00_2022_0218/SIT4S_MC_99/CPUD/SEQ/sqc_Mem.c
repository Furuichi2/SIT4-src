/****************************************************************************************
*	File Name	:	ssc_Mem.c
*	Function	:	シーケンス ワーク領域定義
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-09 Y.Kobayashi
****************************************************************************************/

#include	"sqc_CmnDef.h"
#include	"sqc_Config.h"


//----- Variables -------------------------------------------------------------

// シーケンス ワーク領域
#pragma section	_seqram1

S4b		seq_ram1_top;								// ワーク領域1 TOP

// ■ シーケンス実行コード領域-----------------------------
// POU1
S4b		SEQ_RUN1_TOP;								// TOP
U2b		SEQ_RUN1[SEQ_STEP_MAX1 * SEQ_1STEP_MAX];	// シーケンス実行コード領域
S4b		SEQ_RUN1_END;								// END
// POU2
S4b		SEQ_RUN2_TOP;								// TOP
U2b		SEQ_RUN2[SEQ_STEP_MAX2 * SEQ_1STEP_MAX];	// シーケンス実行コード領域
S4b		SEQ_RUN2_END;								// END
// POU3
S4b		SEQ_RUN3_TOP;								// TOP
U2b		SEQ_RUN3[SEQ_STEP_MAX3 * SEQ_1STEP_MAX];	// シーケンス実行コード領域
S4b		SEQ_RUN3_END;								// END

// ■ コンパイル状態 --------------------------------------
S4b		seq_ram2_top;								// ワーク領域2 TOP
U2b		SEQ_CARD_RAM[SEQ_CARD_MAX];					// SEQUENCE BIT AREA
U2b		SEQ_CMP_ERR1;								// POU1 コンパイル状態(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR1;							// POU1 コンパイル異常アドレス
U2b		SEQ_CMP_ERR2;								// POU2 コンパイル状態(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR2;							// POU2 コンパイル異常アドレス
U2b		SEQ_CMP_ERR3;								// POU3 コンパイル状態(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR3;							// POU3 コンパイル異常アドレス

// ■ ワーク ----------------------------------------------
U2b		DI_X_TOP1[SEQ_X_SIZE];						// X領域ワークメモリ1
U2b		DI_X_TOP2[SEQ_X_SIZE];						// X領域ワークメモリ2(強制登録/解除SET情報)
U2b		DO_Y_TOP1[SEQ_Y_SIZE];						// Y領域ワークメモリ1
U2b		DO_Y_TOP2[SEQ_Y_SIZE];						// Y領域ワークメモリ2(強制登録/解除SET情報)
U2b		X_PUSH_TOP1[SEQ_X_SIZE];					// X領域退避用ワークメモリ1
U2b		X_PUSH_TOP2[SEQ_X_SIZE];					// X領域退避用ワークメモリ2

U2b		SEQ_CMP_START;								// コンパイル中/異常 = 0 , コンパイル正常 = 1
U2b		SeqSysStat;									// ステータス情報
													// 0bit : 起動ビット	(0:停止,1:起動)
													// 1bit : 停止ビット	(0:起動,1:停止)
													// 2bit : 重故障ビット	(0:異常なし,1:重故障)
													// 3bit : 軽故障ビット	(0:異常なし,1:軽故障)

U2b		SEQ_LD_TIMOUT;								// ラダーツール通信タイムアウト
U2b		SEQ_TIM_WK100M;								// 100msタイマ起動用ワーク
U2b		SEQ_TIM_WK1000M;							// 1000msタイマ起動用ワーク

U4b		SEQ_TMR_DATA[3 * SEQ_TD_SIZE];				// タイマデータ
U4b		SEQ_CTR_DATA[3 * SEQ_CD_SIZE];				// カウンタデータ
U2b		SEQ_SR_FLG[SEQ_CARD_MAX];					// SRデータ

// ■ 実行時レジスタ --------------------------------------
// POU1
U2b		SEQ_ARG1_DATA;								// ARG data load
U2b		SEQ_MRG1_DATA;								// MRG data load
U2b		SEQ_NRG1_DATA;								// NRG data load
U4b		SEQ_DRG1_DATA;								// DATA REG data load
// POU2
U2b		SEQ_ARG2_DATA;								// ARG data load
U2b		SEQ_MRG2_DATA;								// MRG data load
U2b		SEQ_NRG2_DATA;								// NRG data load
U4b		SEQ_DRG2_DATA;								// DATA REG data load
// POU3
U2b		SEQ_ARG3_DATA;								// ARG data load
U2b		SEQ_MRG3_DATA;								// MRG data load
U2b		SEQ_NRG3_DATA;								// NRG data load
U4b		SEQ_DRG3_DATA;								// DATA REG data load

U2b		SEQ_TSK1_DATA;								// 0(1msec):1(10msec):ﾊﾞｯｸｸﾞﾗﾝﾄﾞ2(100msec)

// ■ コンパイル異常 --------------------------------------
U2b		PVP_SQ_COM_ERR;								// コンパイル異常有り／無し
U2b		PVP_SQ_COM_ADR;								// コンパイル異常アドレス

//	シーケンス用のワークメモリ(?)
USHORT	SeqMemM[32];					// シーケンス用補助メモリ
