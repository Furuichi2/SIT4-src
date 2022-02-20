/****************************************************************************************
*	File Name	:	ssc_LoaderIf.h
*	Function	:	シーケンス ローダーコマンドI/F
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-11 Y.Kobayashi(コード整理)
****************************************************************************************/
#ifndef _SEQ_LODERRM_H_
#define _SEQ_LODERRM_H_


//----- Defines -----------------------------------------------------

#define	LD_FLM_MAX			512				// フレームサイズMAX
#define	LD_DATA_MAX			512				// データバイト部MAX(データ部MAXは492 + bcc)


//----- Structs ---------------------------------------------------------------

// ローダーコマンド格納構造体
typedef struct {
	U1b		sSCodeFlg;				// スタートコード受信フラグ
	U1b		datacnt[2];				// データ数カウンタ L,H
	U1b		procStatus;				// 処理ステータス
	U1b		conectMode;				// 接続方式
	U1b		tmId[2];				// 接続ID L,H
	U1b		kindCode;				// 機種互換コード(0x11)
	U1b		tmILCode;				// 伝送インタロックコード
	U1b		passwd[4];				// パスワード LL,LH,HL,HH
	U1b		CMND;					// コマンド
	U1b		MODE;					// モード
	U1b		endInfo;				// 終了情報
	U1b		seqNumber;				// シーケンス番号
	U1b		BYTEN[2];				// BYTEN L,H
	U1b		data[LD_DATA_MAX];		// コマンドデータ
} SeqLdCmd_st;

// POU情報(size = 64KB)
typedef struct {
	U4b		Code1;					// 固定コード1
	U4b		SwVer[2];				// ソフトウェアバージョン
	U2b		Size;					// サイズ
	U2b		nop1;					// 予約
	U4b		Spt;					// 補助情報
	U2b		Tem;					// テンポラリサイズ
	U2b		nop2;					// 予約
	U2b		Cmd[32768-16];			// プログラム(32752ワード)
	U4b		Sum;					// プログラムSUM
	U4b		Code2;					// 固定コード2
} SeqPOUStat_st;

// POU書込情報
typedef struct {
	U2b		POU1;					// POU1フラグ
	U2b		POU2;					// POU2フラグ
	U2b		POU3;					// POU3フラグ
} SeqPOU_st;


//----- Variables -------------------------------------------------------------

// 送受信遷移
extern U2b 				SeqScifStat;				// 送受信ステート(0:受信,1:送信)
extern U2b 				SeqLdWk[LD_FLM_MAX];		// ワーク情報
extern U2b 				SeqLdLOOP1;					// ループ変数
extern U2b 				SeqLdCMD;					// 処理コマンド格納レジスタ
extern U2b 				SeqLdEnd;					// 終了情報(0x00:終了,0x01:継続)
extern U2b 				SeqLdNo;					// シーケンス番号(1～255)
extern U2b 				SeqLdNoBak;					// シーケンス番号バックアップ(1～255)
extern U2b 				SeqLdByte;					// データ部バイト数
extern U2b				SeqRasFlg;					// RAS情報フラグ
extern U2b 				SeqRasCode;					// RASｺｰﾄﾞ格納レジスタ
// 受信
extern SeqLdCmd_st		SeqRev;						// 受信フレーム
extern U1b				SeqRevBuff[LD_FLM_MAX];		// 受信用フレームバッファ
extern U2b				SeqRevStat;					// 受信ステート
extern U2b				SeqRevFlmCnt;				// 受信フレームカウンタ
extern U2b				SeqRevDataCnt;				// 受信データ数カウンタ
extern U2b				SeqRevBcc;					// BCC算出用レジスタ(受信用)
extern U2b				SeqRevEnd;					// 受信完了フラグ(0:未完了,1:完了)
extern U2b				SeqRevCnt;					// 受信数カウンタ
// 送信
extern SeqLdCmd_st		SeqSend;					// 送信フレーム
extern U1b				SeqSendBuff[LD_FLM_MAX];	// 送信用フレームバッファ
extern U2b				SeqSendStat;				// 送信ステート
extern U2b				SeqSendFlmCnt;				// 送信フレームカウンタ
extern U2b				SeqSendByte;				// データ部ﾊﾞｲﾄ数カウンタ
extern U2b				SeqSendBcc;					// BCC算出用レジスタ(送信用)
extern U2b				SeqSendCnt;					// 送信バイト数カウンタ
extern U2b				SeqSendDcnt;				// データワード数カウンタ
extern U2b				SeqSendMem;					// メモリ数格納レジスタ
extern U2b				SeqSendEndFlg;				// 分割送信フラグ(0:分割送信なし,1:分割送信)
extern U2b				SeqSendDataCnt;				// 1POU書込 データ書込カウンタ
extern U2b				SeqSendDataCntBak;			// 1POU書込 データ書込カウンタ バックアップ
extern U2b				SeqSendFlmErr;				// 送信フレームエラーフラグ(0:正常,1:異常)
// エラー
extern U2b				SeqLdErr;					// 送受信エラーフラグ(0:正常,1:異常)
// ローダコマンド処理
extern U2b				SeqMKind[82];				// メモリ種別(もにた読出用に82個用意する)
extern U4b				SeqMAdr[82];				// メモリアドレス(モニタ読出用に82個用意する)
extern U2b				SeqRdWdCnt;					// 読出ワード数
extern U2b				SeqRdWdCntBak;				// 読出ワード数バックアップ
extern U2b 				SeqWrData[LD_DATA_MAX];		// 書込データ(最大書込数 492byte)
extern U2b				SeqPOU;						// POU指定
extern U2b				SeqPOULpCnt;				// 1POU読出ループカウンタ
extern U2b				SeqPouSize;					// POUサイズ
extern U4b				SeqSptData;					// 補助情報
extern U2b				SeqTemSize;					// テンポラリサイズ
extern U4b				SeqRtcData;					// カレンダ情報
extern U2b				SeqKpX[32];					// 強制設定登録データ(X領域と同じ)
extern U2b				SeqKpY[32];					// 強制設定登録データ(Y領域と同じ)
extern U2b				SeqMoniCnt;					// モニタ点数
extern U2b				SeqDataTyp[82];				// データ型
extern U2b				SeqBitData[82];				// ビット番号
extern U2b				SeqBit;						// Bit
extern U2b				SeqKpData[82];				// 強制設定情報データ
extern U2b				SeqChgDataCnt;				// 変更データ点数
extern U4b				SeqChgData[50];				// 書込データ(最大書込数 49.2byte)
extern U2b				SeqKpOnX[32];				// 強制設定登録領域(X領域と同じ)
extern U2b				SeqKpOnY[32];				// 強制設定登録領域(Y領域と同じ)
extern U2b				SeqKpOffX[32];				// 強制設定解除領域(X領域と同じ)
extern U2b				SeqKpOffY[32];				// 強制設定解除領域(Y領域と同じ)

extern U2b				SeqMainStat;				// シーケンスメインステート(0:停止,1:起動,2:再コンパイル)
extern U2b				SeqRunFlg;					// シーケンス起動フラグ(0:停止,1:起動)
extern U2b				SeqCmpFlg;					// 再コンパイルフラグ(0:停止,1:再コンパイル)
extern U2b				SeqCmpErrFlg;				// コンパイルエラーフラグ(0:正常,1:異常)
extern U2b				SeqCpuRun;					// 運転フラグ(0:停止,1:運転中)
extern SeqPOUStat_st	SeqPOU1;					// POU1情報
extern SeqPOUStat_st	SeqPOU2;					// POU2情報
extern SeqPOUStat_st	SeqPOU3;					// POU3情報
extern U2b				SeqPOURun1Flg;				// POU1運転フラグ(0:運転可,1:運転不可)
extern U2b				SeqPOURun2Flg;				// POU2運転フラグ(0:運転可,1:運転不可)
extern U2b				SeqPOURun3Flg;				// POU3運転フラグ(0:運転可,1:運転不可)
extern SeqPOU_st		SeqPOUWtFlg;				// POU書込フラグ(0:未書込,1:書込)
extern U2b				SeqTimWtFlg;				// 時計情報書込フラグ(0:未書込,1:書込)
extern U2b				SeqPOUWtEnd;				// ダウンロード終了フラグ

#endif	/* _SEQ_LODERRM_H_ */
