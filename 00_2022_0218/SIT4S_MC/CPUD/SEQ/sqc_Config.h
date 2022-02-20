/****************************************************************************************
*	File Name	:	ssc_Config.h
*	Function	:	シーケンス コンフィグレーション
*	Author		:	Designed by Y.Kobayashi, Coded by Y.Kobayashi
*	Date		:	2010-08-12 Y.Kobayashi
*	Update		:	2010-08-17 Y.Kobayashi(KOMTRAX用に変更)
****************************************************************************************/
#ifndef _SSC_CONFIG_H_
#define _SSC_CONFIG_H_


//----- Defines ---------------------------------------------------------------

// バージョン
#define HW_Ver					0x0001							// HWバージョン
#define SW_Ver					0x0001							// SWバージョン

// POUステップ数
#define SEQ_1STEP_MAX			15								// 1STEP当たり最大ワード数
#define SEQ_STEP_MAX1			4096							// POU1 ステップ数(標準 10ms)
#define SEQ_STEP_MAX2			4096							// POU2 ステップ数(低速 バックグラウンド)
#define SEQ_STEP_MAX3			256								// POU3 ステップ数(高速 1ms)

// メモリ領域サイズ
// ssa_Config.equにも同様の定義あり
#define SEQ_W0_SIZE				0								// W0領域サイズ(WORD) 
#define SEQ_X_SIZE				16								// X領域サイズ(WORD)
#define SEQ_Y_SIZE				16								// Y領域サイズ(WORD)
#define SEQ_M_SIZE				512								// M領域サイズ(WORD)
#define SEQ_L_SIZE				32								// L領域サイズ(WORD)
#define SEQ_T_SIZE				32								// T領域サイズ(WORD)
#define SEQ_C_SIZE				32								// C領域サイズ(WORD)
#define SEQ_TD_SIZE				SEQ_T_SIZE * 16					// Td領域サイズ(WORD)
#define SEQ_CD_SIZE				SEQ_C_SIZE * 16					// Cd領域サイズ(WORD)
#define SEQ_W1_SIZE				0								// W1領域サイズ(WORD)
#define SEQ_W2_SIZE				0								// W2領域サイズ(WORD)
#define SEQ_W3_SIZE				0								// W3領域サイズ(WORD)
#define SEQ_W4_SIZE				0								// W4領域サイズ(WORD)
#define SEQ_F_SIZE				136								// F領域サイズ(WORD)
#define SEQ_S_SIZE				1024							// S領域サイズ(WORD)
#define SEQ_A_SIZE				32								// A領域サイズ(WORD)
#define SEQ_CARD_MAX			3 * 1024						// メモリ空間サイズ(WORD)(基本的には上記の合計)


//----- Consts ----------------------------------------------------------------

extern const UB 				SeqStatTypeTbl[16];				// モジュール型式テーブル

#endif	/* _SSC_CONFIG_H_ */
