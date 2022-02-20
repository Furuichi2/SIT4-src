/****************************************************************************************
*	File Name	:	ssa_BackMain.c
*	Function	:	シーケンス バックグラウンド処理
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-30 Akiba
*	Update		:	2010-08-31 Y.Kobayashi(コード整理)
****************************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include	<machine.h>

#include	"sqc_CmnDef.h"
#include	"sqc_Config.h"
#include	"sqc_Mem.h"
#include	"sqc_LoaderIf.h"
//[[[[koma]]]#include	"from.h"


//----- Define ----------------------------------------------------------------

// 状態
#define SEQ_STOP_STAT		0									// 停止状態
#define SEQ_RUN_STAT		1									// 運転状態
#define SEQ_CMP_STAT		2									// コンパイル状態
// POU番号
#define POU_NUM				3									// POU数
#define POUNO_1				0									// POU1
#define POUNO_2				1									// POU2
#define POUNO_3				2									// POU3
// その他
#define SeqRasFromErr		0x42								// 処理ステータス(メモリアクセス異常)
#define SEQ_SIZE_MAX		65536								// シーケンスプログラム格納バイト数


//----- Variables -------------------------------------------------------------

// 中間コード格納先アドレス
extern U4b					SEQ_COM1_TOP;						// POU1
extern U4b					SEQ_COM2_TOP;						// POU2
extern U4b 					SEQ_COM3_TOP;						// POU3


//----- Consts ----------------------------------------------------------------

extern const U4b 			SeqLd_MKIND_TBL_TOP[];				// メモリ種別テーブル(アドレス)
extern const U4b 			MKIND_TBL[];						// メモリ種別テーブル(個数)


//----- ProtoType -------------------------------------------------------------

static void WritePouCodeToFROM(H pouNo);

extern void SEQ_RUN_MAIN2();
extern void SEQ_RUN_CHG1_MAIN();
extern void SEQ_RUN_CHG2_MAIN();
extern void SEQ_RUN_CHG3_MAIN();
extern void ClearWDT();
extern void ssc_InitSArea();
extern void ssc_SetSysTime(UW time);
extern UW ssc_GetSysTime();
extern void InitTmrCtrFlgClr();


//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: シーケンス バックグラウンドメイン処理
*	Param		: None
*	Return		: None
*	Date		: 09/11/30	T.Akiba		Create
*	Update		: 10/08/31	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SEQ_BACK_GROUND_MAIN(void)
{
	UW	loop1;
	UW	cnt;
	UW	*s_ptr1;
	UW	*d_ptr1;
	UH	*s_ptr2;
	UH	*d_ptr2;
	H	i;
	int	test;
	
	switch (SeqMainStat) {
		case SEQ_STOP_STAT:
		// 停止状態
			
			if (SeqCmpFlg) {							// コンパイル要求あり？
				SeqMainStat = SEQ_CMP_STAT;				// コンパイルステートへ遷移
				SeqCmpFlg = 0;
			}
			else {
				if (SeqRunFlg) {						// 運転要求あり？
					SeqMainStat = SEQ_RUN_STAT;			// 運転状態へ遷移
				}
			}
			
			SeqCpuRun = FALSE;							// CPU状態 = 停止
			break;

		case SEQ_RUN_STAT:
		// 運転状態
			
			if (!SeqRunFlg) {							// 運転要求なし？
				SeqMainStat = SEQ_STOP_STAT;			// 停止状態へ遷移
			}
			else {
				if (SEQ_CMP_START){						// コンパイル状態
					SEQ_RUN_MAIN2();
				}
			}
			
			SeqCpuRun = TRUE;							// CPU状態 = 運転
			break;
			
		case SEQ_CMP_STAT:
		// コンパイル状態
			
			if (SeqPOUWtEnd) {							// POUダウンロード完了？
				// FlashROM用ワークメモリ上にコピー
				for (i = 0; i < POU_NUM; i++) {
					switch (i) {
						case 0:
						// POU1
							s_ptr1 = &SeqPOU1.Code1;
							d_ptr1 = &SEQ_COM1_TOP;
							break;
						case 1:
						// POU2
							s_ptr1 = &SeqPOU2.Code1;
							d_ptr1 = &SEQ_COM2_TOP;
							break;
						case 2:
						// POU3
							s_ptr1 = &SeqPOU3.Code1;
							d_ptr1 = &SEQ_COM3_TOP;
							break;
					}
					
					// コピー(64KB)
					for (loop1 = 0; loop1 < sizeof(SeqPOUStat_st); loop1++, d_ptr1++, s_ptr1++) {
						*d_ptr1 = *s_ptr1;
					}
				}
				
				// コンパイル処理
				if (SeqPOU1.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG1_MAIN();				// POU1 コンパイル実行
					SeqPOURun1Flg = FALSE;				// POU1 運転フラグOFF(0:運転可,1:運転不可)
				}
				else {
					SeqPOURun1Flg = TRUE;				// POU1 運転フラグON(0:運転可,1:運転不可)
					SEQ_CMP_ERR1 = FALSE;
				}
				
				if (SeqPOU2.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG2_MAIN();				// POU2 コンパイル実行
					SeqPOURun2Flg = FALSE;				// POU2 運転フラグOFF(0:運転可,1:運転不可)
				}
				else {
					SeqPOURun2Flg = TRUE;				// POU2 運転フラグON(0:運転可,1:運転不可)
					SEQ_CMP_ERR2 = FALSE;
				}
				
				if (SeqPOU3.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG3_MAIN();				// POU3 コンパイル実行
					SeqPOURun3Flg = FALSE;				// POU3 運転フラグOFF(0:運転可,1:運転不可)
				}
				else {
					SeqPOURun3Flg = TRUE;				// POU3 運転フラグON(0:運転可,1:運転不可)
					SEQ_CMP_ERR3 = FALSE;
				}
				
				// コンパイル異常あり？
				if (SEQ_CMP_ERR1 || SEQ_CMP_ERR2 || SEQ_CMP_ERR3) {
					SeqCmpErrFlg = TRUE;							// コンパイルエラーフラグON(0:正常,1:異常)
					SeqSysStat = SeqSysStat | cBIT2;				// ステータス情報作成(重故障ﾋﾞｯﾄON)
				}
				else {
					SEQ_CMP_START = TRUE;							// コンパイル開始！
					SeqCmpErrFlg = FALSE;							// コンパイルエラーフラグOFF(0:正常,1:異常)
					SeqSysStat = SeqSysStat & ~(cBIT2 | cBIT0);		// ステータス情報作成(停止ビットON)
					
					// メモリ領域クリア
					// X領域、Y領域、M領域
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoX];
					cnt = MKIND_TBL[MkindNoX] + MKIND_TBL[MkindNoY] + MKIND_TBL[MkindNoM];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++){
						*d_ptr2 = 0x0000;
					}
					
					// T領域、C領域
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoT];
					cnt = MKIND_TBL[MkindNoT] + MKIND_TBL[MkindNoC] + MKIND_TBL[MkindNoTd] + MKIND_TBL[MkindNoCd];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++) {
						*d_ptr2 = 0x0000;
					}
					
					// F領域、S領域、A領域
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoF];
					cnt = MKIND_TBL[MkindNoF] + MKIND_TBL[MkindNoS] + MKIND_TBL[MkindNoA];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++) {
						*d_ptr2 = 0x0000;
					}
					
					InitTmrCtrFlgClr();								// タイマ・カウンタのメモリクリア	10/08/31 Add Y.Kobayashi
					ssc_InitSArea();								// S領域の初期化
				}
				
				// コンパイル正常？
				if (SeqCmpErrFlg == FALSE) {
					// POU1情報をFROMへ書込
					for (i = 0; i < POU_NUM; i++) {
						WritePouCodeToFROM(i);
					}
					
					// 停止状態へ遷移
					SeqMainStat = SEQ_STOP_STAT;
				}
				
				SeqPOUWtEnd = FALSE;								// POUダウンロード完了フラグOFF
				SeqRunFlg = 0;
				SeqCmpFlg = 0;
			}
			
			SeqCpuRun = FALSE;
			break;

		default:
		// その他
			
			SeqMainStat = SEQ_STOP_STAT;
			SeqRunFlg = 0;
			SeqCmpFlg = 0;
			SeqCmpErrFlg = 0;
			SeqCpuRun = FALSE;
			break;
	}
	
	// 10/08/26 Modify Y.Kobayashi
//[[[koma]]]	if (SeqTimWtFlg) {
//[[[koma]]]		// 時計情報セット
//[[[koma]]]		ssc_SetSysTime(SeqRtcData);
//[[[koma]]]		SeqTimWtFlg = FALSE;
//[[[koma]]]	}
//[[[koma]]]	else{
//[[[koma]]]		// 時計情報取得
//[[[koma]]]		SeqRtcData = ssc_GetSysTime();
//[[[koma]]]	}

}

/********************************************************************
*	Function	: POU FROM書込処理
*	Param		: POU番号
*	Return		: None
*	Date		: 09/11/30	T.Akiba		Create
*	Update		: 10/08/11	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
static void WritePouCodeToFROM(H pouNo)
{
	UB	*pPouCode;
	int	bankNo;
	int	iRet;
	int	cnt;
	
	switch (pouNo) {
		case POUNO_1:
		// POU1
			pPouCode = (UB*)&SeqPOU1.Code1;
			bankNo = 16;
			break;
			
		case POUNO_2:
		// POU2
			pPouCode = (UB*)&SeqPOU2.Code1;
			bankNo = 17;
			break;
			
		case POUNO_3:
		// POU3
			pPouCode = (UB*)&SeqPOU3.Code1;
			bankNo = 18;
			break;
			
		default:
		// Other
			return;
	}
	
//[[[koma]]]	iRet = write_from_block(bankNo, pPouCode, SEQ_SIZE_MAX);
//[[[koma]]]	if (iRet != 0) {
//[[[koma]]]		// FROM write error !
//[[[koma]]]		SeqRasCode = SeqRasFromErr;					// メモリアクセス異常エラー
//[[[koma]]]		SeqRasFlg = TRUE;
//[[[koma]]]	}

}














/********************************************************************
*	Function	: バックグランドタスク
*	Param		: Non
*	Return		: Non
*	Date		: 09/11/18	Y.Kobayashi		Create
*	Update		: 
*	etc			: 
********************************************************************/
void Tsk_BackGround()
{
//	SeqInitSerialDrv();					// シリアルドライバ初期化処理
//	SEQ_BACK_GROUND_INIT();				// シーケンスイニシャル処理実行
//	
//	while (1) {							// 割込ランク最低にして無限ループにて実行
//		SeqSerialMain();				// ローダコマンドI/F処理
//		SEQ_BACK_GROUND_MAIN();			// シーケンス バックグランドメイン処理
//	}
//	
}

//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: システム領域の初期化
*	Param		: None
*	Return		: None
*	Date		: 10/08/18	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_InitSArea()
{
//	UB	*pDst = (UB *)SeqLd_MKIND_TBL_TOP[MkindNoS];
//	
//	// シスパラの転送
//	memcpy(pDst, &sysParam[SYSP_USR0], S_SYSP_SIZE);
}

/********************************************************************
*	Function	: システム領域の更新
*	Param		: None
*	Return		: None
*	Date		: 10/08/18	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_UpdateSArea()
{
//	UH	*pDst;
//	H	size;
//	H	i;
//	
//	// ■ Ethernet ----------------------------------------
//	
//	pDst = (UH *)(SeqLd_MKIND_TBL_TOP[MkindNoS] + S_ETH_ADDR);
//	
//	// ハンドシェイク正常？
//	if (IsHandshakeNg() == FALSE) {
//		// DI状態
//		*pDst = exDiState[0];
//		pDst++;
//		
//		// AI状態
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = exAiState[i];
//		}
//		
//		// 装置コード・現象コード
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memcpy(pDst, exMacCode, size);
//		pDst += (size / 2);
//		
//		// 消耗品 属性データ・品番 属性データ
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memcpy(pDst, exConsCode, size);
//	}
//	else {
//		// DI状態
//		*pDst = 0;
//		pDst++;
//		
//		// AI状態
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = 0;
//		}
//		
//		// 装置コード・現象コード
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memset(pDst, 0, size);
//		pDst += (size / 2);
//		
//		// 消耗品 属性データ・品番 属性データ
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memset(pDst, 0, size);
//	}
//	
//	
//	// ■ SIT ---------------------------------------------
//	
//	pDst = (UH *)(SeqLd_MKIND_TBL_TOP[MkindNoS] + S_SIT_ADDR);
//	
//	// SITバス正常？
//	if (IsSitBusNg() == FALSE) {
//		// DI状態
//		*pDst = sitMem[SITMEM_DI0];
//		
//		// AI状態
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = sitMem[SITMEM_AI0 + i];
//		}
//		
//		// 装置コード・現象コード
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memcpy(pDst, &sitMem[SITMEM_MCODE_H], size);
//		pDst += (size / 2);
//
//	}
//	else {
//		// DI状態
//		*pDst = 0;
//		
//		// AI状態
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = 0;
//		}
//		
//		// 装置コード・現象コード
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memset(pDst, 0, size);
//		pDst += (size / 2);
//		
//		// 消耗品 属性データ・品番 属性データ
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memset(pDst, 0, size);
//	}

}

/********************************************************************
*	Function	: システム時刻の設定
*	Param		: システム時刻
*	Return		: None
*	Date		: 10/08/26	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_SetSysTime(UW time)
{
}

/********************************************************************
*	Function	: システム時刻の取得
*	Param		: None
*	Return		: システム時刻
*	Date		: 10/08/26	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
UW ssc_GetSysTime()
{
}
