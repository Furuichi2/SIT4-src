/****************************************************************************************
*	File Name	:	ssc_LoaderIf.c
*	Function	:	シーケンス ローダコマンドI/F処理
*	Author		:	Designed by Yoichi Kobayashi, Coded by Yoichi Kobayashi
*	Date		:	2009-11-20 Akiba
*	Update		:	2010-08-31 Y.Kobayashi(コード整理)
****************************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include	<machine.h>

#include 	"sqc_CmnDef.h"
#include	"sqc_Config.h"
#include	"sqc_Mem.h"
#include	"sqc_LoaderIf.h"
//[koma]#include	"scif7619.h"


//----- Define ----------------------------------------------------------------

#define CODE_STX				0x5A			// STX
// コマンド
#define LD_ADR_RD				0x0000			// アドレス読出処理
#define LD_1POU_RD				0x0002			// 1POU読出処理
#define LD_RTC_RD				0x000D			// カレンダ読出処理
#define LD_POU_File_RD			0x0010			// POUﾌｧｲﾙ情報読出処理
#define LD_ADR_WR				0x0100			// アドレス書込処理
#define LD_1POU_WR				0x0102			// 1POU書込処理
#define LD_RTC_WR				0x010D			// カレンダ設定処理
#define LD_MEM_CLR_WR			0x010F			// データメモリクリア処理
#define LD_MONI_RD				0x0200			// モニタ読出処理
#define LD_Start_WR				0x0400			// 一括起動処理
#define LD_Stop_WR				0x0402			// 一括停止処理
#define LD_DownLoad_End			0x0506			// ダウンロード終了通知
#define LD_Data_chg_WR			0x0600			// データ変更処理
#define LD_Set_WR				0x0601			// 強制設定登録処理
#define LD_Reset_WR				0x0602			// 強制設定解除処理
#define LD_Statas_RD			0x03F0			// ステータス読出処理
// データ型
#define SeqDtTypB				0x04			// BIT
#define SeqDtTypW				0x00			// WARD
#define SeqDtTypL				0x08			// DWORDLong
// 処理ステータス
#define SeqRasCpuErr			0x10			// CPU異常
#define SeqRasCpuRun			0x11			// CPU運転中
#define SeqRasNoCmd				0x20			// 未定義コマンド
#define SeqRasParaErr			0x21			// 分割パラメータ異常
#define SeqRasFlmErr			0x22			// パラメータ異常
#define SeqRasDataTypErr		0x40			// データ指定異常
#define SeqRasFromErr			0x42			// メモリアクセス異常
#define SeqRasMemAdrErr			0x44			// メモリアドレス指定異常
#define SeqRasMemOver			0x45			// メモリサイズオーバー
#define SeqRasStepOver			0x47			// 1POUステップ数オーバー
#define SeqRasMoniOver			0x60			// モニタ登録エラー
// システム定数
#define SER_CHN1				1				// シリアルポートCH
#define T1S						100				// 通信タイムアウト時間(1秒)
#define SEQ_RCV_BUFF_SIZE		512				// 受信バッファサイズ
#define LD_FLM_MAX				512				// フレームMAX
#define LD_DATA_MAX_W			246				// データバイト部MAX(ワード数)
#define LD_DATA_MAX_B			492				// データバイト部MAX(バイト数)
#define DataChgMax				49				// データ変更点数MAX
#define MoniMax					81				// モニタ点数MAX
#define POU1SizeMax				32752			// POU1ステップ数Max
#define POU2SizeMax				32752			// POU2ステップ数Max
#define POU3SizeMax				32752			// POU3ステップ数Max
#define SeqCmdCode1				0x12345678		// シーケンスコマンドコード1
#define SeqCmdCode2				0x9ABCDEF0		// シーケンスコマンドコード2


//----- Structs -------------------------------------------------------------------------

// データ情報
typedef	union	{
	float			f_dat;
	long			l_dat;
	unsigned long	ul_dat;
	short			w_dat[2];
	unsigned short	uw_dat[2];
	char			b_dat[4];
	unsigned char	ub_dat[4];
} long_data_st;


//----- Variables -----------------------------------------------------------------------

// 送受信遷移
U2b 			SeqScifStat;				// 送受信ステート(0:受信,1:送信)
U2b 			SeqLdWk[LD_FLM_MAX];		// ワーク情報
U2b 			SeqLdLOOP1;					// ループ変数
U2b 			SeqLdCMD;					// 処理コマンド格納レジスタ
U2b 			SeqLdEnd;					// 終了情報(0x00:終了,0x01:継続)
U2b 			SeqLdNo;					// シーケンス番号(1～255)
U2b 			SeqLdNoBak;					// シーケンス番号バックアップ(1～255)
U2b 			SeqLdByte;					// データ部バイト数
U2b				SeqRasFlg;					// RAS情報フラグ
U2b 			SeqRasCode;					// RASｺｰﾄﾞ格納レジスタ
// 受信
SeqLdCmd_st		SeqRev;						// 受信フレーム
U1b				SeqRevBuff[LD_FLM_MAX];		// 受信用フレームバッファ
U2b				SeqRevStat;					// 受信ステート
U2b				SeqRevFlmCnt;				// 受信フレームカウンタ
U2b				SeqRevDataCnt;				// 受信データ数カウンタ
U2b				SeqRevBcc;					// BCC算出用レジスタ(受信用)
U2b				SeqRevEnd;					// 受信完了フラグ(0:未完了,1:完了)
U2b				SeqRevCnt;					// 受信数カウンタ
// 送信
SeqLdCmd_st		SeqSend;					// 送信フレーム
U1b				SeqSendBuff[LD_FLM_MAX];	// 送信用フレームバッファ
U2b				SeqSendStat;				// 送信ステート
U2b				SeqSendFlmCnt;				// 送信フレームカウンタ
U2b				SeqSendByte;				// データ部ﾊﾞｲﾄ数カウンタ
U2b				SeqSendBcc;					// BCC算出用レジスタ(送信用)
U2b				SeqSendCnt;					// 送信バイト数カウンタ
U2b				SeqSendDcnt;				// データワード数カウンタ
U2b				SeqSendMem;					// メモリ数格納レジスタ
U2b				SeqSendEndFlg;				// 分割送信フラグ(0:分割送信なし,1:分割送信)
U2b				SeqSendDataCnt;				// 1POU書込 データ書込カウンタ
U2b				SeqSendDataCntBak;			// 1POU書込 データ書込カウンタ バックアップ
U2b				SeqSendFlmErr;				// 送信フレームエラーフラグ(0:正常,1:異常)
// エラー
U2b				SeqLdErr;					// 送受信エラーフラグ(0:正常,1:異常)
// ローダコマンド処理
U2b				SeqMKind[MoniMax+1];		// メモリ種別(もにた読出用に82個用意する)
U4b				SeqMAdr[MoniMax+1];			// メモリアドレス(モニタ読出用に82個用意する)
U2b				SeqRdWdCnt;					// 読出ワード数
U2b				SeqRdWdCntBak;				// 読出ワード数バックアップ
U2b 			SeqWrData[LD_DATA_MAX];		// 書込データ(最大書込数 492byte)
U2b				SeqPOU;						// POU指定
U2b				SeqPOULpCnt;				// 1POU読出ループカウンタ
U2b				SeqPouSize;					// POUサイズ
U4b				SeqSptData;					// 補助情報
U2b				SeqTemSize;					// テンポラリサイズ
U4b				SeqRtcData;					// カレンダ情報
U2b				SeqKpX[32];					// 強制設定登録データ(X領域と同じ)
U2b				SeqKpY[32];					// 強制設定登録データ(Y領域と同じ)
U2b				SeqMoniCnt;					// モニタ点数
U2b				SeqDataTyp[82];				// データ型
U2b				SeqBitData[82];				// ビット番号
U2b				SeqBit;						// Bit
U2b				SeqKpData[82];				// 強制設定情報データ
U2b				SeqChgDataCnt;				// 変更データ点数
U4b				SeqChgData[50];				// 書込データ(最大書込数 49.2byte)
U2b				SeqKpOnX[32];				// 強制設定登録領域(X領域と同じ)
U2b				SeqKpOnY[32];				// 強制設定登録領域(Y領域と同じ)
U2b				SeqKpOffX[32];				// 強制設定解除領域(X領域と同じ)
U2b				SeqKpOffY[32];				// 強制設定解除領域(Y領域と同じ)

U2b				SeqMainStat;				// シーケンスメインステート(0:停止,1:起動,2:再コンパイル)
U2b				SeqRunFlg;					// シーケンス起動フラグ(0:停止,1:起動)
U2b				SeqCmpFlg;					// 再コンパイルフラグ(0:停止,1:再コンパイル)
U2b				SeqCmpErrFlg;				// コンパイルエラーフラグ(0:正常,1:異常)
U2b				SeqCpuRun;					// 運転フラグ(0:停止,1:運転中)
SeqPOUStat_st	SeqPOU1;					// POU1情報
SeqPOUStat_st	SeqPOU2;					// POU2情報
SeqPOUStat_st	SeqPOU3;					// POU3情報
U2b				SeqPOURun1Flg;				// POU1運転フラグ(0:運転可,1:運転不可)
U2b				SeqPOURun2Flg;				// POU2運転フラグ(0:運転可,1:運転不可)
U2b				SeqPOURun3Flg;				// POU3運転フラグ(0:運転可,1:運転不可)
SeqPOU_st		SeqPOUWtFlg;				// POU書込フラグ(0:未書込,1:書込)
U2b				SeqTimWtFlg;				// 時計情報書込フラグ(0:未書込,1:書込)
U2b				SeqPOUWtEnd;				// ダウンロード終了フラグ

//extern UH		hwVersion;					// H/Wバージョン
//extern UH		swVersion;					// S/Wバージョン
UH		hwVersion;						// H/Wバージョン
UH		swVersion;						// S/Wバージョン
UH		seqVersion;						// SEQバージョン				10/09/29 Add Y.Kobayashi	


//----- Consts --------------------------------------------------------------------------

// 送信フレームフォーマットテーブル
const unsigned char SeqSendFlmDataTbl[] = {
	0x5A,				// スタートコード
	0x00,				// データ数カウンタ L
	0x00,				// データ数カウンタ H
	0x00,				// 処理ステータス
	0x7A,				// 接続方式
	0x00,				// 接続ID L
	0x00,				// 接続ID H
	0x11,				// 機種互換コード
	0x00,				// 伝送インターロックコード
	0x00,				// パスワード LL
	0x00,				// パスワード LH
	0x00,				// パスワード HL
	0x00,				// パスワード HH
	0x00,				// CMND
	0x00,				// MODE
	0x00,				// 終了情報
	0x01,				// シーケンス番号
	0x00,				// BYTEN L
	0x00,				// BYTEN H
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00				// DATA
};

// BITテーブル
const unsigned short SeqBit16Tbl[] = {
	0x0001,				// Bit0
	0x0002,				// Bit1
	0x0004,				// Bit2
	0x0008,				// Bit3
	0x0010,				// Bit4
	0x0020,				// Bit5
	0x0040,				// Bit6
	0x0080,				// Bit7
	0x0100,				// Bit8
	0x0200,				// Bit9
	0x0400,				// Bit10
	0x0800,				// Bit11
	0x1000,				// Bit12
	0x2000,				// Bit13
	0x4000,				// Bit14
	0x8000				// Bit15
};

extern const U4b SeqLd_MKIND_TBL_TOP[];			// メモリ領域TOPアドレステーブル
extern const U4b MKIND_TBL[];					// メモリ領域テーブル


//----- ProtoType -----------------------------------------------------------------------

void SeqInitSerialDrv();						// ｼﾘｱﾙﾄﾞﾗｲﾊﾞ初期化処理
void SeqSerialMain();							// ﾗﾀﾞｰﾂｰﾙ 送受信処理
void InitTmrCtrFlgClr();						// ﾀｲﾏ・ｶｳﾝﾀのﾒﾓﾘｸﾘｱ

static void SeqScifRev();						// 受信ｽﾃｰﾄ処理
static void SeqScifSend();						// 送信ｽﾃｰﾄ処理
static void SeqLdScifErr();						// 初期化処理
static void SeqLdRevFlmChk();					// 受信ﾌﾚｰﾑｴﾗｰ検出処理
static void SeqLdSendFlmChk();					// 送信ﾌﾚｰﾑｴﾗｰ検出処理

static void SeqLdSendProg();					// 要求ｺﾏﾝﾄﾞ処理
static void SeqLdAdrRd();						// ｱﾄﾞﾚｽ読出ｺﾏﾝﾄﾞ処理
static void SeqLd1PouRd();						// 1POU読出ｺﾏﾝﾄﾞ処理
static void SeqLdRtcRd();						// 時計情報読出ｺﾏﾝﾄﾞ処理
static void SeqLdPouFileRd();					// POUﾌｧｲﾙ情報読出ｺﾏﾝﾄﾞ処理
static void SeqLdAdrWr();						// ｱﾄﾞﾚｽ書込ｺﾏﾝﾄﾞ処理
static void SeqLd1PouWr();						// 1POU書込ｺﾏﾝﾄﾞ処理
static void SeqLdRtcWr();						// 時計情報書込ｺﾏﾝﾄﾞ処理
static void SeqLdMemClrWr();					// ﾒﾓﾘｸﾘｱｺﾏﾝﾄﾞ処理
static void SeqLdMoniRd();						// ﾓﾆﾀ読出ｺﾏﾝﾄﾞ処理
static void SeqLdStartWr();						// 一括起動ｺﾏﾝﾄﾞ処理
static void SeqLdStopWr();						// 一括停止ｺﾏﾝﾄﾞ処理
static void SeqLdDownLoadEnd();					// ﾀﾞｳﾝﾛｰﾄﾞ終了通知ｺﾏﾝﾄﾞ処理
static void SeqLdDataChgWr();					// ﾃﾞｰﾀ書換ｺﾏﾝﾄﾞ処理
static void SeqLdSetWr();						// 強制設定登録ｺﾏﾝﾄﾞ処理
static void SeqLdResetWr();						// 強制設定解除ｺﾏﾝﾄﾞ処理
static void SeqLdStatasRd();					// ｽﾃｰﾀｽ読出ｺﾏﾝﾄﾞ処理

static void SeqSendFlmSet(unsigned short);		// 送信ﾌﾚｰﾑﾌｫｰﾏｯﾄ作成処理
static void SeqLdSendBcc(unsigned short);		// BCC作成処理


//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: シリアルドライバの初期化
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqInitSerialDrv()
{
	// シリアルドライバの初期化
//[koma]	SCIF_DrvInit(
//[koma]			SER_CHN1,					// ﾁｬﾈﾙ : 1(0:MODEM,1:LODER,2:NOT)
//[koma]			SCIF_DLEN_8,				// ﾃﾞｰﾀ長 : 8bit
//[koma]			SCIF_STPBIT_1,				// ｽﾄｯﾌﾟﾋﾞｯﾄ : 1bit
//[koma]			SCIF_PRT_EVEN,				// ﾊﾟﾘﾃｨﾋﾞｯﾄ : 偶数
//[koma]			SCIF_BRT_38400,				// ﾎﾞｰﾚｰﾄ : 38400bps
//[koma]			0							// 未使用
//[koma]			);

}

/********************************************************************
*	Function	: ラダーツール送受信処理
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqSerialMain(void)
{
	switch(SeqScifStat){
		case	0:							// 受信ｽﾃｰﾄ
			SeqScifRev();
		break;
		
		case	1:							// 送信ｽﾃｰﾄ
			SeqScifSend();
		break;
		
		default:
			SeqScifStat = 0;				// 受信ｽﾃｰﾄへ遷移
		break;
	}
}

/********************************************************************
*	Function	: タイマ・カウントのメモリクリア
*	Param		: None
*	Return		: None
*	Date		: 10/18/31	M.Komatsu	Create
*	Update		: 
*	etc			: 
********************************************************************/
void InitTmrCtrFlgClr()
{
	S2b i;
	
	// タイマデータ
	for (i=0;i<SEQ_TD_SIZE;i++) {
		SEQ_TMR_DATA[i * 3 + 0] = 0;
		SEQ_TMR_DATA[i * 3 + 1] = 0;
		SEQ_TMR_DATA[i * 3 + 2] = 0;
	}
	
	// カウンタデータ
	for (i = 0; i < SEQ_CD_SIZE; i++) {
		SEQ_CTR_DATA[i * 3 + 0]=0;
		SEQ_CTR_DATA[i * 3 + 1]=0;
		SEQ_CTR_DATA[i * 3 + 2]=0;
	}
	
	// フラグ
	for (i = 0; i < SEQ_CARD_MAX; i++) {
		SEQ_SR_FLG[i]=0;
	}
}

/********************************************************************
*	Function	: 受信
*	Param		: None
*	Return		: 0：OK  -1：NG
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqScifRev(void)
{
	unsigned char	chBuff[LD_FLM_MAX];
	ER				ercd;
	unsigned short	loop1;
	long_data_st	data;
	unsigned char	*s_ptr,*d_ptr;

	unsigned short	*test;				// 通信ｴﾗｰ確認用
	unsigned short	ii;

	// データ受信待ち

//[koma]	ercd = SCIF_RecvDataNBlock(SER_CHN1, chBuff, sizeof(chBuff));

	// 送受信ﾌﾚｰﾑ作成
	if(!SeqRevEnd){											// 受信完了確認
		if(ercd){											// 受信ﾃﾞｰﾀがある時
			SEQ_LD_TIMOUT = T1S;							// ﾗﾀﾞｰﾂｰﾙ 通信ﾀｲﾑｱｳﾄｶｳﾝﾀ設定(1秒)
			// 受信ﾌﾚｰﾑ作成処理
			for(loop1 = 0 ; loop1 < ercd; loop1++){			// 受信ﾃﾞｰﾀ分処理する
															// 受信ﾃﾞｰﾀ分処理する
				if(SeqRevStat == 0){						// ｽﾀｰﾄｺｰﾄﾞ待ち
					if(chBuff[loop1] == CODE_STX){			// ｽﾀｰﾄｺｰﾄﾞ確認
						SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];	// 受信ﾌﾚｰﾑへ格納
						SeqRevFlmCnt++;						// 受信ﾌﾚｰﾑｶｳﾝﾀ更新
						SeqLdErr = FALSE;					// 通信ｴﾗ-ﾌﾗｸﾞOFF
						SeqRevDataCnt = 0;					// 受信ﾃﾞｰﾀ数ｶｳﾝﾀｸﾘｱ
						SeqRevBcc = 0;						// BCC演算ﾚｼﾞｽﾀｸﾘｱ ADD 091203akiba
						SeqRevStat = 1;						// 
					}
				}else if(SeqRevStat == 1){					// 受信ﾃﾞｰﾀ数待ち
					if(SeqRevFlmCnt == 1){					// 受信ﾃﾞｰﾀ数ｶｳﾝﾀ(L)の時
						SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];
															// 受信ﾌﾚｰﾑへ格納
					}else if(SeqRevFlmCnt == 2){			// 受信ﾃﾞｰﾀ数ｶｳﾝﾀ(H)の時
						SeqRevBuff[SeqRevFlmCnt] = data.ub_dat[0] = chBuff[loop1];
															// ﾃﾞｰﾀ格納
						data.ub_dat[1] = SeqRevBuff[(SeqRevFlmCnt - 1)];
						SeqRevDataCnt = data.uw_dat[0];		// 受信ﾃﾞｰﾀ数ｶｳﾝﾀへ格納
						SeqRevStat = 2;						// BCC待ちへ遷移
					}else{
						SeqLdErr = TRUE;					// 通信ｴﾗ-ﾌﾗｸﾞON
						break;
					}
					SeqRevFlmCnt++;							// 受信ﾌﾚｰﾑｶｳﾝﾀ更新
					SeqRevBcc += chBuff[loop1];				// BCCﾃﾞｰﾀ演算 ADD 091203akiba
				}else if(SeqRevStat == 2){					// BCC待ち
					SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];	// 受信ﾌﾚｰﾑへ格納
					if(SeqRevDataCnt > 1){					// 受信ﾃﾞｰﾀ数確認
						SeqRevFlmCnt++;						// 受信ﾌﾚｰﾑｶｳﾝﾀ更新
						SeqRevBcc += chBuff[loop1];			// BCCﾃﾞｰﾀ演算
						SeqRevDataCnt --;					// 受信ﾃﾞｰﾀ数ｶｳﾝﾀ更新
					}else{
						SeqRevBcc = (0x00 - SeqRevBcc) & 0x00FF;
															// BCC算出
						if(SeqRevBcc == chBuff[loop1]){		// BCCﾁｪｯｸ
							SeqRevEnd = TRUE;				// 受信正常完了
							SeqLdErr = FALSE;				// 通信ｴﾗ-ﾌﾗｸﾞOFF
							// add 091218 akiba
							d_ptr = &(SeqRev.sSCodeFlg);	// 格納先頭ｱﾄﾞﾚｽ格納
							for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++){
								*d_ptr = SeqRevBuff[loop1];	// ﾃﾞｰﾀ格納
							}
							SeqLdRevFlmChk();				// 受信ﾌﾚｰﾑﾍｯﾀﾞ部確認
						}else{
#if	1
							// 通信エラーカウント ADD 091221 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
							*test = *test + 1;
#else
#if	1
							// 通信エラーカウント ADD 091221 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
							test = test + 1;
							*test = *test + 1;
							// 通信エラーカウント ADD 100105 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoM];
							for(loop1 = 0 ; loop1 < 256; loop1++){
								data.ub_dat[0] = SeqRevBuff[(ii + 0)];
								data.ub_dat[1] = SeqRevBuff[(ii + 1)];
								*test = data.uw_dat[0];
								test ++;
								ii = ii + 2;
							}
#endif
#endif

							SeqRevEnd = FALSE;				// 受信異常完了
							SeqLdErr = TRUE;				// 通信ｴﾗ-ﾌﾗｸﾞON

						}
						SeqRevStat = 0;						// ｽﾀｰﾄｺｰﾄﾞ待ちへ遷移
						SeqRevFlmCnt = 0;					// 受信ﾌﾚｰﾑｶｳﾝﾄｸﾘｱ
						SeqRevDataCnt = 0;					// 受信ﾃﾞｰﾀ数ｶｳﾝﾀへ格納
						SeqRevBcc = 0;						// BCC演算ﾚｼﾞｽﾀｸﾘｱ
						break;
					}
				}else{
					SeqRevStat = 0;							// ｽﾀｰﾄｺｰﾄﾞ待ちへ遷移
				}
			}
		}

		if(SEQ_LD_TIMOUT == 0){								// ﾗﾀﾞｰﾂｰﾙ 通信ﾀｲﾑｱｳﾄ確認(1秒)
			SeqLdErr = TRUE;								// 通信ｴﾗ-ﾌﾗｸﾞON
#if	0
			// 通信エラーカウント ADD 091221 akiba
			test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
			*test = *test + 1;
#endif
		}

		if(SeqLdErr){										// 通信ｴﾗｰ確認
			SeqLdScifErr();									// 送受信情報初期化処理
		}
	}else{
		if(SeqSendStat == 0){								// 受信ﾊﾞｯﾌｧｺﾋﾟｰ/要求ｺﾏﾝﾄﾞ作成
#if	0
			d_ptr = &(SeqRev.sSCodeFlg);					// 格納先頭ｱﾄﾞﾚｽ格納
			for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++){
				*d_ptr = SeqRevBuff[loop1];					// ﾃﾞｰﾀ格納
			}

			SeqLdRevFlmChk();								// 受信ﾌﾚｰﾑﾍｯﾀﾞ部確認
#endif
			SeqLdCMD = (((unsigned short)SeqRev.CMND << 8) | (unsigned short)SeqRev.MODE);
															// 要求ｺﾏﾝﾄﾞ算出
			SeqLdEnd = SeqRev.endInfo;						// 終了情報
			SeqLdNo = SeqRev.seqNumber;						// ｼｰｹﾝｽ番号
			data.ub_dat[1] = SeqRev.BYTEN[0];
			data.ub_dat[0] = SeqRev.BYTEN[1];
			SeqLdByte = data.uw_dat[0];						// 読出ﾜｰﾄﾞ数
			SeqSendStat = 1;								// 受信ﾃﾞｰﾀ解読/実処理/送信ﾌﾚｰﾑ作成へ遷移
		}else if(SeqSendStat == 1){							// 受信ﾃﾞｰﾀ解読/実処理/送信ﾌﾚｰﾑ作成処理
			SeqLdSendProg();								// 受信ﾃﾞｰﾀ解読/実処理/送信ﾌﾚｰﾑ作成処理実行
			SeqSendStat = 2;								// 送信ﾊﾞｯﾌｧ作成処理へ遷移
		}else if(SeqSendStat == 2){							// 送信ﾊﾞｯﾌｧ作成処理
			d_ptr = &(SeqSendBuff[0]);						// 格納元頭ｱﾄﾞﾚｽ格納
			s_ptr = &(SeqSend.sSCodeFlg);					// 格納先頭ｱﾄﾞﾚｽ格納
			for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++, s_ptr++){
				*d_ptr = *s_ptr;							// ﾃﾞｰﾀ格納
			}
			SeqSendStat = 0;								// 受信ﾊﾞｯﾌｧｺﾋﾟｰ/要求ｺﾏﾝﾄﾞ作成へ遷移
			SeqScifStat = 1;								// 送信ｽﾃｰﾄへ遷移
		}else{
			SeqSendStat = 0;								// 受信ﾊﾞｯﾌｧｺﾋﾟｰ/要求ｺﾏﾝﾄﾞ作成へ遷移
		}
	}
}

/********************************************************************
*	Function	: 送信
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqScifSend(void)
{
	UB				chBuff[LD_FLM_MAX];
	ER				ercd;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	unsigned short	*test;									// 通信ｴﾗｰ確認用

	SeqLdSendFlmChk();										// 送信ﾌﾚｰﾑﾍｯﾀﾞ部確認 add 091229 akiba

	if(!SeqSendFlmErr){
		s_ptr = &SeqSendBuff[0];
		d_ptr = &chBuff[0];
		for(loop1 = 0; loop1 < SeqSendCnt; loop1++, *s_ptr++, *d_ptr++){
			*d_ptr = *s_ptr;
		}
//[koma]		ercd = SCIF_SendData(SER_CHN1, chBuff, SeqSendCnt);	// 送信

//		// 送信数ﾁｪｯｸ(0は未送信)
//		if(ercd <= 0){
//			SeqLdErr = TRUE;								// 通信ｴﾗ-ﾌﾗｸﾞON
//		}

		SeqSendCnt -= ercd;
		if(SeqSendCnt == 0){
			SeqLdScifErr();									// 送受信情報初期化処理
		}else{
			SeqLdErr = TRUE;								// 通信ｴﾗ-ﾌﾗｸﾞON
#if	1
			// 確認用処理 add 091229 akiba
			test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
			test = test + 3;
			*test ++;
#endif
		}
	}else{
#if	1
		// 確認用処理 add 091229 akiba
		test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
		test = test + 4;
		*test ++;
#endif
		SeqSendFlmErr = FALSE;
		SeqLdErr = TRUE;
	}

	SeqScifStat = 0;										// 受信ｽﾃｰﾄへ遷移
	if(SeqLdErr){
		SeqLdScifErr();										// 送受信情報初期化処理
	}
}


/********************************************************************
*	Function	: 送受信情報初期化処理
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdScifErr(void)
{
	unsigned short	loop1;
	unsigned char	*d_ptr1;
	unsigned char	*d_ptr2;
	unsigned short	*d_ptr3;
	unsigned char	*d_ptr4;
	unsigned char	*d_ptr5;

#if	0
	for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++){	// ﾊﾞｯﾌｧﾒﾓﾘｸﾘｱ
		SeqRevBuff[loop1] = 0x00;
		SeqSendBuff[loop1] = 0x00;
		SeqLdWk[loop1] = 0x00;
	}
#else
	d_ptr1 = &SeqRevBuff[0];
	d_ptr2 = &SeqSendBuff[0];
	d_ptr3 = &SeqLdWk[0];
	d_ptr4 = &(SeqRev.sSCodeFlg);
	d_ptr5 = &(SeqSend.sSCodeFlg);
	for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++, *d_ptr1++, *d_ptr2++, *d_ptr3++, *d_ptr4++, *d_ptr5++){
		*d_ptr1 = *d_ptr2 = *d_ptr4 = *d_ptr5 = 0x00;
		*d_ptr3 = 0x0000;							// ﾊﾞｯﾌｧﾒﾓﾘｸﾘｱ
	}
#endif

	SeqScifStat = 0;								// 受信ｽﾃｰﾄへ遷移
	SeqRevStat = 0;									// ｽﾀｰﾄｺｰﾄﾞ待ちへ遷移
	SeqRevFlmCnt = 0;								// 受信ﾌﾚｰﾑｶｳﾝﾄｸﾘｱ
	SeqRevDataCnt = 0;								// 受信ﾃﾞｰﾀ数ｶｳﾝﾀへ格納
	SeqRevEnd = FALSE;								// 受信未完了
	SeqRevBcc = 0;									// BCC演算ﾚｼﾞｽﾀｸﾘｱ
	SeqLdErr = FALSE;								// 通信ｴﾗ-ﾌﾗｸﾞOFF
	SeqSendStat = 0;								// 受信ﾊﾞｯﾌｧｺﾋﾟｰへ遷移
	SeqSendFlmCnt = 0;								// 受信ﾌﾚｰﾑｶｳﾝﾄｸﾘｱ
	SeqSendByte = 0;								// ﾃﾞｰﾀ部ﾊﾞｲﾄ数ｶｳﾝﾀｸﾘｱ
	SeqSendBcc = 0;									// BCC算出用ﾚｼﾞｽﾀｸﾘｱ
	SeqSendCnt = 0;									// 送信ﾊﾞｲﾄ数ｶｳﾝﾀｸﾘｱ
	SeqSendDcnt = 0;								// ﾃﾞｰﾀﾜｰﾄﾞ数ｶｳﾝﾀｸﾘｱ
	SeqSendMem = 0;									// ﾒﾓﾘ数格納ﾚｼﾞｽﾀ
	SeqLdCMD = 0;									// 処理ｺﾏﾝﾄﾞ格納ﾚｼﾞｽﾀｸﾘｱ
//	SeqLdTmOutCnt = 0;								// ﾀｲﾑｱｳﾄ検出ｶｳﾝﾀｸﾘｱ
	SEQ_LD_TIMOUT = 100;							// ﾗﾀﾞｰﾂｰﾙ 通信ﾀｲﾑｱｳﾄｶｳﾝﾀ設定(1秒)
	SeqLdEnd = 0;									// 終了情報ｸﾘｱ
	SeqLdNo = 0;									// ｼｰｹﾝｽ番号初期化
	SeqBit = 0;										// Bitｸﾘｱ
}


/********************************************************************
*	Function	: 受信フレームエラーチェック
*	Param		: None
*	Return		: None
*	Date		: 09/12/15	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRevFlmChk(void)
{

	long_data_st	data;

	if(SeqRev.sSCodeFlg != CODE_STX){			// ｽﾀｰﾄｺｰﾄﾞﾁｪｯｸ(0x5Aのみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[1] = SeqRev.datacnt[0];			// ﾃﾞｰﾀ数ｶｳﾝﾀ L
	data.ub_dat[0] = SeqRev.datacnt[1];			// ﾃﾞｰﾀ数ｶｳﾝﾀ H
	if(data.uw_dat[0] > (LD_FLM_MAX - 3)){		// ﾁｪｯｸ(最大509ﾊﾞｲﾄ以下が正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.procStatus != 0xFF){				// 処理ｽﾃｰﾀｽﾁｪｯｸ(0xFFのみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.conectMode != 0x7A){				// 接続方式ﾁｪｯｸ(0x7Aのみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[1] = SeqRev.tmId[0];			// 接続ID L
	data.ub_dat[0] = SeqRev.tmId[1];			// 接続ID H
	if(data.uw_dat[0] != 0x0000){				// 接続ID ﾁｪｯｸ(0x0000のみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.kindCode != 0x11){				// 機種互換ｺｰﾄﾞﾁｪｯｸ(0x11のみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.tmILCode != 0x00){				// 伝送ｲﾝﾀｰﾛｯｸｺｰﾄﾞﾁｪｯｸ(0x00のみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[3] = SeqRev.passwd[0];			// ﾊﾟｽﾜｰﾄﾞ LL
	data.ub_dat[2] = SeqRev.passwd[1];			// ﾊﾟｽﾜｰﾄﾞ LH
	data.ub_dat[1] = SeqRev.passwd[2];			// ﾊﾟｽﾜｰﾄﾞ HL
	data.ub_dat[0] = SeqRev.passwd[3];			// ﾊﾟｽﾜｰﾄﾞ HH
	if(data.ul_dat != 0x00000000){				// ﾊﾟｽﾜｰﾄﾞ ﾁｪｯｸ(0x00000000のみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.endInfo > 0x01){					// 終了情報ﾁｪｯｸ(0x00,0x01のみ正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.seqNumber == 0x00){				// ｼｰｹﾝｽ番号ﾁｪｯｸ(0x00以外正常)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: 送信フレームエラーチェック
*	Param		: None
*	Return		: None
*	Date		: 09/12/29	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendFlmChk(void)
{

	long_data_st	data;

	if(SeqSendBuff[0] != CODE_STX){				// ｽﾀｰﾄｺｰﾄﾞﾁｪｯｸ(0x5Aのみ正常)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[1] = SeqSendBuff[1];			// ﾃﾞｰﾀ数ｶｳﾝﾀ L
	data.ub_dat[0] = SeqSendBuff[2];			// ﾃﾞｰﾀ数ｶｳﾝﾀ H
	if(data.uw_dat[0] > (LD_FLM_MAX - 3)){		// ﾁｪｯｸ(最大509ﾊﾞｲﾄ以下が正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[3] == 0xFF){					// 処理ｽﾃｰﾀｽﾁｪｯｸ(0xFFのみ正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[4] != 0x7A){					// 接続方式ﾁｪｯｸ(0x7Aのみ正常)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[1] = SeqSendBuff[5];			// 接続ID L
	data.ub_dat[0] = SeqSendBuff[6];			// 接続ID H
	if(data.uw_dat[0] != 0x0000){				// 接続ID ﾁｪｯｸ(0x0000のみ正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[7] != 0x11){					// 機種互換ｺｰﾄﾞﾁｪｯｸ(0x11のみ正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[8] != 0x00){					// 伝送ｲﾝﾀｰﾛｯｸｺｰﾄﾞﾁｪｯｸ(0x00のみ正常)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[3] = SeqSendBuff[9];			// ﾊﾟｽﾜｰﾄﾞ LL
	data.ub_dat[2] = SeqSendBuff[10];			// ﾊﾟｽﾜｰﾄﾞ LH
	data.ub_dat[1] = SeqSendBuff[11];			// ﾊﾟｽﾜｰﾄﾞ HL
	data.ub_dat[0] = SeqSendBuff[12];			// ﾊﾟｽﾜｰﾄﾞ HH
	if(data.ul_dat != 0x00000000){				// ﾊﾟｽﾜｰﾄﾞ ﾁｪｯｸ(0x00000000のみ正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[15] > 0x01){					// 終了情報ﾁｪｯｸ(0x00,0x01のみ正常)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[16] == 0x00){				// ｼｰｹﾝｽ番号ﾁｪｯｸ(0x00以外正常)
		SeqSendFlmErr = TRUE;
	}
}


/********************************************************************
*	Function	: 要求コマンド処理／送信フレーム作成
*	Param		: None
*	Return		: None
*	Date		: 09/11/21	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendProg(void)
{

	unsigned short	loop1;
	unsigned char	*d_ptr;

	unsigned short	*test;				// 通信ｴﾗｰ確認用

	switch(SeqLdCMD){
		case LD_ADR_RD:
			SeqLdAdrRd();					// ｱﾄﾞﾚｽ読出処理
			break;

		case LD_1POU_RD:
			SeqLd1PouRd();					// 1POU読出処理
			break;

		case LD_RTC_RD:
			SeqLdRtcRd();					// ｶﾚﾝﾀﾞ読出処理
			break;

		case LD_POU_File_RD:
			SeqLdPouFileRd();				// POUﾌｧｲﾙ情報読出処理
			break;

		case LD_ADR_WR:
			SeqLdAdrWr();					// ｱﾄﾞﾚｽ書込処理
			break;

		case LD_1POU_WR:
			SeqLd1PouWr();					// 1POU書込処理
			break;

		case LD_RTC_WR:
			SeqLdRtcWr();					// ｶﾚﾝﾀﾞ設定処理
			break;

		case LD_MEM_CLR_WR:
			SeqLdMemClrWr();				// ﾃﾞｰﾀﾒﾓﾘｸﾘｱ処理
			break;

		case LD_MONI_RD:
			SeqLdMoniRd();					// ﾓﾆﾀ読出処理
			break;

		case LD_Start_WR:
			SeqLdStartWr();					// 一括起動処理
			break;

		case LD_Stop_WR:
			SeqLdStopWr();					// 一括停止処理
			break;

		case LD_DownLoad_End:
			SeqLdDownLoadEnd();				// ﾀﾞｳﾝﾛｰﾄﾞ終了通知処理
			break;

		case LD_Data_chg_WR:
			SeqLdDataChgWr();				// ﾃﾞｰﾀ変更処理
			break;

		case LD_Set_WR:
			SeqLdSetWr();					// 強制設定登録処理
			break;

		case LD_Reset_WR:
			SeqLdResetWr();					// 強制設定解除処理
			break;

		case LD_Statas_RD:
			SeqLdStatasRd();				// ｽﾃｰﾀｽ読出処理
			break;

		default:
			SeqRasCode = SeqRasNoCmd;		// 未定義ｺﾏﾝﾄﾞｴﾗｰ
			SeqRasFlg = TRUE;
			break;
	}

	if(SeqRasFlg){
		d_ptr = &(SeqSend.sSCodeFlg);
		for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++, *d_ptr++){
			*d_ptr = 0x00;					// ﾊﾞｯﾌｧﾒﾓﾘｸﾘｱ
		}
		SeqSendFlmSet(SeqLdCMD);			// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		SeqSend.procStatus = SeqRasCode;	// 処理ｽﾃｰﾀｽ格納(未定義ｺﾏﾝﾄﾞ)
//		data.uw_dat[0] = 0;					// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		SeqLdSendBcc(0);					// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
		SeqRasFlg = SeqRasCode = 0;

#if	1
		// 通信エラーカウント ADD 091221 akiba
		test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
		test = test + 2;
		*test = *test + 1;
#endif

	}

}


/********************************************************************
*	Function	: アドレス読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdAdrRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ﾒﾓﾘ種別
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[1];
	data.ub_dat[2] = SeqRev.data[2];
	data.ub_dat[1] = SeqRev.data[3];
	SeqMAdr[0] = data.ul_dat;								// ﾒﾓﾘｱﾄﾞﾚｽ
	data.ub_dat[1] = SeqRev.data[4];
	data.ub_dat[0] = SeqRev.data[5];
	SeqRdWdCnt = data.uw_dat[0];							// 読出ﾜｰﾄﾞ数

	if(SeqMKind[0] <= MkindNoMax){
		if(SeqRdWdCnt > (LD_DATA_MAX_W - 3)){				// 読出ﾜｰﾄﾞ数ｵｰﾊﾞｰ確認
			SeqRdWdCnt = (LD_DATA_MAX_W - 3);
		}
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		d_ptr += SeqMAdr[0];								// 指定ｱﾄﾞﾚｽ格納
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++, *d_ptr++){
			data.uw_dat[0] = *d_ptr;						// ﾃﾞｰﾀ取り出し
			SeqLdWk[wk1] = data.ub_dat[1];
			SeqLdWk[wk1 + 1] = data.ub_dat[0];
			wk1 = wk1 + 2;
		}

		SeqSendFlmSet(LD_ADR_RD);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		SeqSend.data[0] = SeqMKind[0];						// ﾒﾓﾘ種別格納
		data.ul_dat = SeqMAdr[0];							// ﾒﾓﾘｱﾄﾞﾚｽ格納
		SeqSend.data[1] = data.ub_dat[3];
		SeqSend.data[2] = data.ub_dat[2];
		SeqSend.data[3] = data.ub_dat[1];
		SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++){		// 読出ﾃﾞｰﾀ格納
			SeqSend.data[(SeqSendFlmCnt + 6)] = SeqLdWk[wk1];
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqLdWk[wk1 + 1];
			SeqSendFlmCnt = SeqSendFlmCnt + 2;
			wk1 = wk1 + 2;
			SeqSendDcnt ++;
		}
		data.uw_dat[0] = SeqSendDcnt;						// 読出ﾜｰﾄﾞ数格納
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
		data.uw_dat[0] = 6 + (SeqSendDcnt * 2);				// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 6 = (ﾒﾓﾘ種別 + ﾒﾓﾘｱﾄﾞﾚｽ + 読出ﾜｰﾄﾞ数)
		// * 2 = ﾜｰﾄﾞ数 → ﾊﾞｲﾄ数
		SeqLdSendBcc(data.uw_dat[0]);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行

	}else{
		SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: １ＰＯＵ読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLd1PouRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqPOU = data.uw_dat[0];								// POU指定
	data.ub_dat[1] = SeqRev.data[2];
	data.ub_dat[0] = SeqRev.data[3];
	SeqRdWdCnt = data.uw_dat[0];							// 読出ﾜｰﾄﾞ数

	if(SeqPOU == 1){
		SeqPouSize = SeqPOU1.Size;
		SeqSptData = SeqPOU1.Spt;
		SeqTemSize = SeqPOU1.Tem;
	}else if(SeqPOU == 2){
		SeqPouSize = SeqPOU2.Size;
		SeqSptData = SeqPOU2.Spt;
		SeqTemSize = SeqPOU2.Tem;
	}else if(SeqPOU == 3){
		SeqPouSize = SeqPOU3.Size;
		SeqSptData = SeqPOU3.Spt;
		SeqTemSize = SeqPOU3.Tem;
	}else{
		SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	if(!SeqRasFlg){
		if(SeqLdNo == 1){
			SeqRdWdCntBak = 0;
			if(SeqPouSize < (LD_DATA_MAX_W - 5)){
				SeqPOULpCnt = SeqPouSize;
				SeqRdWdCntBak = 0;
				SeqLdEnd = 0;
			}else{
				SeqRdWdCntBak = SeqPouSize - (LD_DATA_MAX_W - 5);
				SeqPOULpCnt = (LD_DATA_MAX_W - 5);
				SeqLdEnd = 1;
			}
		}else{
			if(SeqRdWdCntBak < LD_DATA_MAX_W){
				SeqPOULpCnt = SeqRdWdCntBak;
				SeqRdWdCntBak = 0;
				SeqLdEnd = 0;
			}else{
				SeqRdWdCntBak = SeqRdWdCntBak - LD_DATA_MAX_W;
				SeqPOULpCnt = LD_DATA_MAX_W;
				SeqLdEnd = 1;
			}
		}
		if(SeqPOU == 1){
			d_ptr = &SeqPOU1.Cmd[0];						// POU1 Topｱﾄﾞﾚｽ格納
		}else if(SeqPOU == 2){
			d_ptr = &SeqPOU2.Cmd[0];						// POU2 Topｱﾄﾞﾚｽ格納
		}else if(SeqPOU == 3){
			d_ptr = &SeqPOU3.Cmd[0];						// POU3 Topｱﾄﾞﾚｽ格納
		}
		if(SeqLdNo > 1){
			d_ptr += ((LD_DATA_MAX_W * (SeqLdNo - 2)) + (LD_DATA_MAX_W - 5));
		}
		wk1 = 0;
		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++, *d_ptr++){
			data.uw_dat[0] = *d_ptr;						// ﾃﾞｰﾀ取り出し
			SeqLdWk[wk1] = data.ub_dat[0];					// add 091204akiba
			SeqLdWk[wk1 + 1] = data.ub_dat[1];				// add 091204akiba
			wk1 = wk1 + 2;
		}

		SeqSendFlmSet(LD_1POU_RD);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		if(SeqLdNo == 1){
			data.uw_dat[0] = SeqPOU;						// POU指定格納
			SeqSend.data[0] = data.ub_dat[1];
			SeqSend.data[1] = data.ub_dat[0];
			data.uw_dat[0] = SeqPouSize;					// ｻｲｽﾞ格納
			SeqSend.data[2] = data.ub_dat[1];
			SeqSend.data[3] = data.ub_dat[0];
			data.ul_dat = SeqSptData;						// 補助情報格納
			SeqSend.data[4] = data.ub_dat[3];
			SeqSend.data[5] = data.ub_dat[2];
			SeqSend.data[6] = data.ub_dat[1];
			SeqSend.data[7] = data.ub_dat[0];
			data.uw_dat[0] = SeqTemSize;					// ﾃﾝﾎﾟﾗﾘｻｲｽﾞ格納
			SeqSend.data[8] = data.ub_dat[1];
			SeqSend.data[9] = data.ub_dat[0];
			SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
			for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){		// 読出ﾃﾞｰﾀ格納
				SeqSend.data[(SeqSendFlmCnt + 10)] = SeqLdWk[wk1];
				SeqSend.data[(SeqSendFlmCnt + 11)] = SeqLdWk[wk1 + 1];
				SeqSendFlmCnt += 2;
				wk1 += 2;
				SeqSendDcnt ++;
			}
		}else{
			SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
			for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){		// 読出ﾃﾞｰﾀ格納
				SeqSend.data[(SeqSendFlmCnt + 0)] = SeqLdWk[wk1];
				SeqSend.data[(SeqSendFlmCnt + 1)] = SeqLdWk[wk1 + 1];
				SeqSendFlmCnt += 2;
				wk1 += 2;
				SeqSendDcnt ++;
			}
		}
		if(SeqLdNo <= 1){
			data.uw_dat[0] = 10 + (SeqSendDcnt * 2);		// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
			// 10 = (POU指定 + ｻｲｽﾞ + 補助情報 + ﾃﾝﾎﾟﾗﾘｻｲｽﾞ)
			// * 2 = ﾜｰﾄﾞ数 → ﾊﾞｲﾄ数
		}else{
			data.uw_dat[0] = (SeqSendDcnt * 2);				// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		}
		SeqLdSendBcc(data.uw_dat[0]);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}


/********************************************************************
*	Function	: カレンダ読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRtcRd(void)
{

	long_data_st	data;

	SeqSendFlmSet(LD_RTC_RD);					// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
	data.ul_dat = SeqRtcData;					// ｶﾚﾝﾀﾞ情報ｺﾋﾟｰ
	SeqSend.data[0] = data.ub_dat[3];
	SeqSend.data[1] = data.ub_dat[2];
	SeqSend.data[2] = data.ub_dat[1];
	SeqSend.data[3] = data.ub_dat[0];
//	data.uw_dat[0] = 4;							// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	// 4 = ｶﾚﾝﾀﾞ情報
	SeqLdSendBcc(4);							// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
}


/********************************************************************
*	Function	: ＰＯＵファイル情報読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdPouFileRd(void)
{

	long_data_st	data;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqPOU = data.uw_dat[0];							// POU指定

	SeqSendFlmSet(LD_POU_File_RD);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
	SeqSendDcnt = SeqSendFlmCnt = 0;
	if((SeqPOU1.Code1 == SeqCmdCode1) && (SeqPOU1.Code2 == SeqCmdCode2) && (SeqPOU1.Size != 0)){
		SeqSend.data[2] = 1;							// POU指定格納
		SeqSend.data[3] = 0;
		data.uw_dat[0] = SeqPOU1.Size;					// ｻｲｽﾞ格納
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
		data.ul_dat = SeqPOU1.Spt;						// 補助情報格納
		SeqSend.data[6] = data.ub_dat[3];
		SeqSend.data[7] = data.ub_dat[2];
		SeqSend.data[8] = data.ub_dat[1];
		SeqSend.data[9] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU1.Tem;					// ﾃﾝﾎﾟﾗﾘｻｲｽﾞ格納
		SeqSend.data[10] = data.ub_dat[1];
		SeqSend.data[11] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	if((SeqPOU2.Code1 == SeqCmdCode1) && (SeqPOU2.Code2 == SeqCmdCode2) && (SeqPOU2.Size != 0)){
		SeqSend.data[(SeqSendFlmCnt + 2)] = 2;			// POU指定格納
		SeqSend.data[(SeqSendFlmCnt + 3)] = 0;
		data.uw_dat[0] = SeqPOU2.Size;					// ｻｲｽﾞ格納
		SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[0];
		data.ul_dat = SeqPOU2.Spt;						// 補助情報格納
		SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[3];
		SeqSend.data[(SeqSendFlmCnt + 7)] = data.ub_dat[2];
		SeqSend.data[(SeqSendFlmCnt + 8)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 9)] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU2.Tem;					// ﾃﾝﾎﾟﾗﾘｻｲｽﾞ格納
		SeqSend.data[(SeqSendFlmCnt + 10)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 11)] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	if((SeqPOU3.Code1 == SeqCmdCode1) && (SeqPOU3.Code2 == SeqCmdCode2) && (SeqPOU3.Size != 0)){
		SeqSend.data[(SeqSendFlmCnt + 2)] = 3;			// POU指定格納
		SeqSend.data[(SeqSendFlmCnt + 3)] = 0;
		data.uw_dat[0] = SeqPOU3.Size;					// ｻｲｽﾞ格納
		SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[0];
		data.ul_dat = SeqPOU3.Spt;						// 補助情報格納
		SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[3];
		SeqSend.data[(SeqSendFlmCnt + 7)] = data.ub_dat[2];
		SeqSend.data[(SeqSendFlmCnt + 8)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 9)] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU3.Tem;					// ﾃﾝﾎﾟﾗﾘｻｲｽﾞ格納
		SeqSend.data[(SeqSendFlmCnt + 10)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 11)] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	data.uw_dat[0] = SeqSendDcnt;						// ＰＯＵ数格納
	SeqSend.data[0] = data.ub_dat[1];
	SeqSend.data[1] = data.ub_dat[0];
	data.uw_dat[0] = 2 + (SeqSendDcnt * 10);			// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	// 2 = 読出ﾌｧｲﾙ数
	// 10 = ﾌｧｲﾙ情報
	SeqLdSendBcc(data.uw_dat[0]);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
}


/********************************************************************
*	Function	: アドレス書込コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdAdrWr(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ﾒﾓﾘ種別
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[1];
	data.ub_dat[2] = SeqRev.data[2];
	data.ub_dat[1] = SeqRev.data[3];
	SeqMAdr[0] = data.ul_dat;								// ﾒﾓﾘｱﾄﾞﾚｽ
	data.ub_dat[1] = SeqRev.data[4];
	data.ub_dat[0] = SeqRev.data[5];
	SeqRdWdCnt = data.uw_dat[0];							// 書込ﾜｰﾄﾞ数
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++){			// 書込ﾃﾞｰﾀ
		data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
		data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 7)];
		SeqWrData[loop1] = data.uw_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 2;
	}

	if(SeqMKind[0] <= MkindNoMax){
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		d_ptr += SeqMAdr[0];								// 指定ｱﾄﾞﾚｽ格納
		SeqSendDcnt = 0;
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++, *d_ptr++){
			*d_ptr = SeqWrData[loop1];						// ﾃﾞｰﾀ書込
			SeqSendDcnt ++;
		}

		SeqSendFlmSet(LD_ADR_WR);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		SeqSend.data[0] = SeqMKind[0];						// ﾒﾓﾘ種別格納
		data.ul_dat = SeqMAdr[0];							// ﾒﾓﾘｱﾄﾞﾚｽ格納
		SeqSend.data[1] = data.ub_dat[3];
		SeqSend.data[2] = data.ub_dat[2];
		SeqSend.data[3] = data.ub_dat[1];
		data.uw_dat[0] = SeqSendDcnt;						// 書込ﾜｰﾄﾞ数格納
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
//		data.uw_dat[0] = 6;									// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 6 = (ﾒﾓﾘ種別 + ﾒﾓﾘｱﾄﾞﾚｽ + 書込ﾜｰﾄﾞ数)
		SeqLdSendBcc(6);									// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}else{
		SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: １ＰＯＵ書込コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLd1PouWr(void)
{

	long_data_st	data;
	unsigned long	*d_ptr_L;
	unsigned short	*d_ptr_W;
	unsigned short	loop1;

	if(SeqCpuRun){
		SeqRasCode = SeqRasCpuRun;							// CPU運転中ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	if(SeqLdNoBak == SeqLdNo){
		SeqSendDataCnt = SeqSendDataCntBak;
	}else if((SeqLdNoBak + 1) == SeqLdNo){
	}else{
		SeqRasCode = SeqRasParaErr;							// 分割ﾊﾟﾗﾒｰﾀ異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	SeqLdNoBak = SeqLdNo;
	if(SeqLdNo == 1){
		data.ub_dat[1] = SeqRev.data[0];
		data.ub_dat[0] = SeqRev.data[1];					// POU番号
		data.ub_dat[3] = SeqRev.data[2];
		data.ub_dat[2] = SeqRev.data[3];					// ｻｲｽﾞ
		if(data.uw_dat[0] == 1){
			if(data.uw_dat[1] > POU1SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POUｽﾃｯﾌﾟ数ｵｰﾊﾞｰｴﾗｰ
				SeqRasFlg = TRUE;
			}
		}else if(data.uw_dat[0] == 2){
			if(data.uw_dat[1] > POU2SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POUｽﾃｯﾌﾟ数ｵｰﾊﾞｰｴﾗｰ
				SeqRasFlg = TRUE;
			}
		}else if(data.uw_dat[0] == 3){
			if(data.uw_dat[1] > POU3SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POUｽﾃｯﾌﾟ数ｵｰﾊﾞｰｴﾗｰ
				SeqRasFlg = TRUE;
			}
		}else{
			SeqRasCode = SeqRasDataTypErr;					// ﾃﾞｰﾀ指定異常ｴﾗｰ
			SeqRasFlg = TRUE;
		}
	}

	if(!SeqRasFlg){
		if(SeqLdNo == 1){
			data.ub_dat[1] = SeqRev.data[0];
			data.ub_dat[0] = SeqRev.data[1];
			SeqPOU = data.uw_dat[0];						// POU指定
			data.ub_dat[1] = SeqRev.data[2];
			data.ub_dat[0] = SeqRev.data[3];
			SeqPouSize = data.uw_dat[0];					// ｻｲｽﾞ格納
			data.ub_dat[3] = SeqRev.data[4];
			data.ub_dat[2] = SeqRev.data[5];
			data.ub_dat[1] = SeqRev.data[6];
			data.ub_dat[0] = SeqRev.data[7];
			SeqSptData = data.ul_dat;						// 補助情報格納
			data.ub_dat[1] = SeqRev.data[8];
			data.ub_dat[0] = SeqRev.data[9];
			SeqTemSize = data.uw_dat[0];					// ﾃﾝﾎﾟﾗﾘｻｲｽﾞ格納
			if(SeqPOU == 1){
				d_ptr_L = &SeqPOU1.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU1.Code1 = SeqCmdCode1;
				SeqPOU1.Size = SeqPouSize;
				SeqPOU1.Spt = SeqSptData;
				SeqPOU1.Tem = SeqTemSize;
			}else if(SeqPOU == 2){
				d_ptr_L = &SeqPOU2.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU2.Code1 = SeqCmdCode1;
				SeqPOU2.Size = SeqPouSize;
				SeqPOU2.Spt = SeqSptData;
				SeqPOU2.Tem = SeqTemSize;
			}else if(SeqPOU == 3){
				d_ptr_L = &SeqPOU3.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU3.Code1 = SeqCmdCode1;
				SeqPOU3.Size = SeqPouSize;
				SeqPOU3.Spt = SeqSptData;
				SeqPOU3.Tem = SeqTemSize;
			}
			SeqPOULpCnt = ((SeqLdByte - 10) / 2);
			SeqSendFlmCnt = 0;
			for(loop1 = 0;loop1 < SeqPOULpCnt; loop1++){		// 書込ﾃﾞｰﾀ
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 10)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 11)];
				SeqWrData[loop1] = data.uw_dat[0];
				SeqSendFlmCnt = SeqSendFlmCnt + 2;
			}
		}else{
			SeqPOULpCnt = (SeqLdByte / 2);
			SeqSendFlmCnt = 0;
			for(loop1 = 0;loop1 < SeqPOULpCnt; loop1++){		// 書込ﾃﾞｰﾀ
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 0)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 1)];
				SeqWrData[loop1] = data.uw_dat[0];
				SeqSendFlmCnt = SeqSendFlmCnt + 2;
			}
		}

		if(SeqPOU == 1){
			d_ptr_W = &SeqPOU1.Cmd[0];						// POU1 Topｱﾄﾞﾚｽ格納
			d_ptr_L = &SeqPOU1.Sum;
		}else if(SeqPOU == 2){
			d_ptr_W = &SeqPOU2.Cmd[0];						// POU2 Topｱﾄﾞﾚｽ格納
			d_ptr_L = &SeqPOU2.Sum;
		}else if(SeqPOU == 3){
			d_ptr_W = &SeqPOU3.Cmd[0];						// POU3 Topｱﾄﾞﾚｽ格納
			d_ptr_L = &SeqPOU3.Sum;
		}

		d_ptr_W += SeqSendDataCnt;

		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++, *d_ptr_W++){
			*d_ptr_W = SeqWrData[loop1];
			SeqSendDcnt ++;
		}
		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){
			*d_ptr_L += SeqWrData[loop1];
		}
		SeqSendDataCntBak = SeqSendDataCnt;
		SeqSendDataCnt += SeqPOULpCnt;

		if(!SeqLdEnd){
			SeqCmpFlg = TRUE;
			if(SeqPOU == 1){
				SeqPOU1.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU1 = TRUE;
			}else if(SeqPOU == 2){
				SeqPOU2.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU2 = TRUE;
			}else if(SeqPOU == 3){
				SeqPOU3.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU3 = TRUE;
			}
			SeqLdNoBak = 0;
			SeqSendDataCnt = 0;
			SeqSendDataCntBak = 0;
		}

		SeqSendFlmSet(LD_1POU_WR);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		data.uw_dat[0] = SeqPOU;							// POU指定格納
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		data.uw_dat[0] = SeqSendDcnt;						// 書込ﾃﾞｰﾀ数格納
		SeqSend.data[2] = data.ub_dat[1];
		SeqSend.data[3] = data.ub_dat[0];
//		data.uw_dat[0] = 4;									// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 4 = POU指定 + 書込ﾃﾞｰﾀ数
		SeqLdSendBcc(4);									// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}


/********************************************************************
*	Function	: カレンダ設定コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRtcWr(void)
{

	long_data_st	data;


	data.ub_dat[3] = SeqRev.data[0];
	data.ub_dat[2] = SeqRev.data[1];
	data.ub_dat[1] = SeqRev.data[2];
	data.ub_dat[0] = SeqRev.data[3];
	SeqRtcData = data.ul_dat;					// カレンダ情報格納

	SeqTimWtFlg = TRUE;							// 時計情報書込ﾌﾗｸﾞON(0:未書込,1:書込)

	SeqSendFlmSet(LD_RTC_WR);					// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
//	data.uw_dat[0] = 0;							// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	SeqLdSendBcc(0);							// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
}

/********************************************************************
*	Function	: データメモリクリアコマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 10/08/31	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SeqLdMemClrWr(void)
{
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];									// ﾒﾓﾘ種別
	
	if (SeqMKind[0] == 0xFF) {
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoM];
		SeqSendMem = MKIND_TBL[MkindNoM] + MKIND_TBL[MkindNoL];		// ﾒﾓﾘ種別ｴﾘｱ格納
		SeqSendMem = SeqSendMem / 2;
	}
	else if ((SeqMKind[0] == MkindNoM) || (SeqMKind[0] == MkindNoL)) {
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		SeqSendMem = MKIND_TBL[SeqMKind[0]];						// ﾒﾓﾘ種別ｴﾘｱ格納
		SeqSendMem = SeqSendMem / 2;
	}
	else{
		SeqRasCode = SeqRasDataTypErr;								// ﾃﾞｰﾀ指定異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}

	if (!SeqRasFlg) {
		for (loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++) {	// 領域ﾃﾞｰﾀｸﾘｱ
			*d_ptr = 0x0000;
		}
		
		InitTmrCtrFlgClr();											// ﾀｲﾏ・ｶｳﾝﾀのﾒﾓﾘｸﾘｱ	10/08/31 Add Y.Kobayashi
		
		SeqSendFlmSet(LD_MEM_CLR_WR);								// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		SeqSend.data[0] = SeqMKind[0];								// ﾒﾓﾘ種別格納
//		data.uw_dat[0] = 1;											// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 1 = ﾒﾓﾘ種別
		SeqLdSendBcc(1);											// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}

/********************************************************************
*	Function	: モニタ読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdMoniRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;
	unsigned short	*s_ptr1;
	unsigned short	*s_ptr2;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqMoniCnt = data.uw_dat[0];									// ﾓﾆﾀ点数
	if(SeqMoniCnt > MoniMax){
		SeqRasCode = SeqRasMoniOver;								// ﾓﾆﾀ登録ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
		SeqMKind[loop1] = SeqRev.data[(SeqSendFlmCnt + 2)];			// ﾒﾓﾘ種別
		if(SeqMKind[0] <= MkindNoMax){
			data.ub_dat[0] = 0x00;
			data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 4)];
			data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 5)];
			data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
			SeqMAdr[loop1] = data.ul_dat;							// ﾒﾓﾘｱﾄﾞﾚｽ
			SeqBitData[loop1] = SeqRev.data[(SeqSendFlmCnt + 7)];	// Bit番号
			SeqDataTyp[loop1] = SeqRev.data[(SeqSendFlmCnt + 3)];	// ﾃﾞｰﾀ型
			if((SeqDataTyp[loop1] != SeqDtTypB)
				&& (SeqDataTyp[loop1] != SeqDtTypW)
					&& (SeqDataTyp[loop1] != SeqDtTypL)){
				SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
				SeqRasFlg = TRUE;
			}
			SeqSendFlmCnt = SeqSendFlmCnt + 6;;
		}else{
			SeqRasCode = SeqRasDataTypErr;							// ﾃﾞｰﾀ指定異常ｴﾗｰ
			SeqRasFlg = TRUE;
		}
	}

	if(!SeqRasFlg){
#if	0
		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
			d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
			d_ptr += SeqMAdr[loop1];								// 指定ｱﾄﾞﾚｽ格納
			switch(SeqDataTyp[loop1]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
					SeqBit = data.uw_dat[0] & SeqBit;
					if(SeqBit){
						SeqBit = 0x0001;
					}
					SeqLdWk[wk1] = SeqBit;							// 指定ﾒﾓﾘﾃﾞｰﾀ読出(bitﾃﾞｰﾀ)
					SeqLdWk[wk1 + 1] = 0;
					SeqLdWk[wk1 + 2] = 0;
					SeqLdWk[wk1 + 3] = 0;
					break;
				case	SeqDtTypW:
					data.uw_dat[0] = *d_ptr;
					SeqLdWk[wk1] = data.ub_dat[1];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(wardﾃﾞｰﾀ)
					SeqLdWk[wk1 + 1] = data.ub_dat[0];
					SeqLdWk[wk1 + 2] = 0;
					SeqLdWk[wk1 + 3] = 0;
					break;
				case	SeqDtTypL:
					data.uw_dat[1] = *d_ptr;
					d_ptr ++;
					data.uw_dat[0] = *d_ptr;
					SeqLdWk[wk1] = data.ub_dat[3];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(longﾃﾞｰﾀ)
					SeqLdWk[wk1 + 1] = data.ub_dat[2];
					SeqLdWk[wk1 + 2] = data.ub_dat[1];
					SeqLdWk[wk1 + 3] = data.ub_dat[0];
					break;
				default:
					break;
			}
			wk1 = wk1 + 4;
		}
#else
		d_ptr = &SeqKpX[0];
		s_ptr1 = &SeqKpOnX[0];
		s_ptr2 = &SeqKpOffX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++, *s_ptr1++, *s_ptr2++){
			*d_ptr = *s_ptr1;
			*d_ptr |= *s_ptr2;
		}

		d_ptr = &SeqKpY[0];
		s_ptr1 = &SeqKpOnY[0];
		s_ptr2 = &SeqKpOffY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++, *s_ptr1++, *s_ptr2++){
			*d_ptr = *s_ptr1;
			*d_ptr |= *s_ptr2;
		}

		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
			if((SeqMKind[loop1] == MkindNoX) || (SeqMKind[loop1] == MkindNoY)){
				d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
				d_ptr += SeqMAdr[loop1];								// 指定ｱﾄﾞﾚｽ格納
				switch(SeqDataTyp[loop1]){
					case	SeqDtTypB:
						data.uw_dat[0] = *d_ptr;
						SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
						SeqBit = data.uw_dat[0] & SeqBit;
						if(SeqBit){
							SeqBit = 0x0001;
						}
						SeqLdWk[wk1] = SeqBit;							// 指定ﾒﾓﾘﾃﾞｰﾀ読出(bitﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = 0;
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						if((SeqMKind[loop1] == MkindNoX)){
							data.uw_dat[0] = SeqKpX[SeqMAdr[loop1]];
							SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
							SeqBit = data.uw_dat[0] & SeqBit;
							if(SeqBit){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							data.uw_dat[0] = SeqKpY[SeqMAdr[loop1]];
							SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
							SeqBit = data.uw_dat[0] & SeqBit;
							if(SeqBit){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					case	SeqDtTypW:
						data.uw_dat[0] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[1];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(wardﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = data.ub_dat[0];
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						if((SeqMKind[loop1] == MkindNoX)){
							if(SeqKpX[SeqMAdr[loop1]]){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							if(SeqKpY[SeqMAdr[loop1]]){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					case	SeqDtTypL:
						data.uw_dat[0] = *d_ptr;
						d_ptr ++;
						data.uw_dat[1] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[3];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(longﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = data.ub_dat[2];
						SeqLdWk[wk1 + 2] = data.ub_dat[1];
						SeqLdWk[wk1 + 3] = data.ub_dat[0];
						if((SeqMKind[loop1] == MkindNoX)){
							data.uw_dat[1] = SeqKpX[SeqMAdr[loop1]];
							data.uw_dat[0] = SeqKpX[SeqMAdr[loop1 + 1]];
							if(data.ul_dat){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							data.uw_dat[1] = SeqKpY[SeqMAdr[loop1]];
							data.uw_dat[0] = SeqKpY[SeqMAdr[loop1 + 1]];
							if(data.ul_dat){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					default:
						break;
				}
				wk1 = wk1 + 4;
			}else{
				d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
				d_ptr += SeqMAdr[loop1];								// 指定ｱﾄﾞﾚｽ格納
				switch(SeqDataTyp[loop1]){
					case	SeqDtTypB:
						data.uw_dat[0] = *d_ptr;
						SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
						SeqBit = data.uw_dat[0] & SeqBit;
						if(SeqBit){
							SeqBit = 0x0001;
						}
						SeqLdWk[wk1] = SeqBit;							// 指定ﾒﾓﾘﾃﾞｰﾀ読出(bitﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = 0;
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						SeqKpData[loop1] = 0x0000;
						break;
					case	SeqDtTypW:
						data.uw_dat[0] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[1];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(wardﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = data.ub_dat[0];
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						SeqKpData[loop1] = 0x0000;
						break;
					case	SeqDtTypL:
						data.uw_dat[0] = *d_ptr;
						d_ptr ++;
						data.uw_dat[1] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[3];					// 指定ﾒﾓﾘﾃﾞｰﾀ読出(longﾃﾞｰﾀ)
						SeqLdWk[wk1 + 1] = data.ub_dat[2];
						SeqLdWk[wk1 + 2] = data.ub_dat[1];
						SeqLdWk[wk1 + 3] = data.ub_dat[0];
						SeqKpData[loop1] = 0x0000;
						break;
					default:
						break;
				}
				wk1 = wk1 + 4;
			}
		}
#endif

		SeqSendFlmSet(LD_MONI_RD);									// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		data.uw_dat[0] = SeqMoniCnt;								// ﾓﾆﾀ点数格納
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
//			SeqSend.data[(SeqSendFlmCnt + 2)] = cBIT7;				// ﾌﾗｸﾞ情報格納	add 7bit作成
			SeqSend.data[(SeqSendFlmCnt + 2)] = (cBIT7 | SeqKpData[loop1]);	// ﾌﾗｸﾞ情報格納	add 6bit作成
			SeqSend.data[(SeqSendFlmCnt + 3)] = 0;					// 未使用
			SeqSend.data[(SeqSendFlmCnt + 4)] = SeqLdWk[wk1];		// ﾃﾞｰﾀ LL格納
			SeqSend.data[(SeqSendFlmCnt + 5)] = SeqLdWk[wk1 + 1];	// ﾃﾞｰﾀ LH格納
			SeqSend.data[(SeqSendFlmCnt + 6)] = SeqLdWk[wk1 + 2];	// ﾃﾞｰﾀ HL格納
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqLdWk[wk1 + 3];	// ﾃﾞｰﾀ HH格納
			SeqSendFlmCnt = SeqSendFlmCnt + 6;
			wk1 = wk1 + 4;
			SeqSendDcnt++;
		}
		data.uw_dat[0] = 2 + (SeqSendDcnt * 6);						// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 2 = ﾓﾆﾀ点数
		// 6 = ﾓﾆﾀﾃﾞｰﾀ内容
		SeqLdSendBcc(data.uw_dat[0]);								// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}


/********************************************************************
*	Function	: 一括起動コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdStartWr(void)
{

	unsigned short	wk1 = 0;

	wk1 = SeqSysStat & cBIT2;							// 重故障情報抽出
	if(wk1 != cBIT2){
		SeqSysStat = SeqSysStat & ~(cBIT2 | cBIT1);		// 運転開始情報格納
		SeqSysStat = SeqSysStat | cBIT0;
		SeqRunFlg = TRUE;

		SeqSendFlmSet(LD_Start_WR);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
//		data.uw_dat[0] = 0;								// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		SeqLdSendBcc(0);								// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}else{
		SeqRasCode = SeqRasCpuErr;						// CPU異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: 一括停止コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdStopWr(void)
{


	SeqSysStat = SeqSysStat & ~cBIT0;		// 運転停止情報格納
	SeqSysStat = SeqSysStat | cBIT1;
	SeqRunFlg = FALSE;

	SeqSendFlmSet(LD_Stop_WR);				// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
//	data.uw_dat[0] = 0;						// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	SeqLdSendBcc(0);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
}


/********************************************************************
*	Function	: ダウンロード終了通知コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdDownLoadEnd(void)
{
	unsigned long	*d_ptr_L;
	unsigned short	loop1;

	if(SeqPOUWtFlg.POU1 == FALSE){
		d_ptr_L = &SeqPOU1.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;						// ﾃﾞｰﾀｸﾘｱ
		}
		SeqPOU1.Code1 = SeqCmdCode1;
		SeqPOU1.Code2 = SeqCmdCode2;
	}
	if(SeqPOUWtFlg.POU2 == FALSE){
		d_ptr_L = &SeqPOU2.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;					// ﾃﾞｰﾀｸﾘｱ
		}
		SeqPOU2.Code1 = SeqCmdCode1;
		SeqPOU2.Code2 = SeqCmdCode2;
	}
	if(SeqPOUWtFlg.POU3 == FALSE){
		d_ptr_L = &SeqPOU3.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;					// ﾃﾞｰﾀｸﾘｱ
		}
		SeqPOU3.Code1 = SeqCmdCode1;
		SeqPOU3.Code2 = SeqCmdCode2;
	}
	SeqPOUWtFlg.POU1 = FALSE;
	SeqPOUWtFlg.POU2 = FALSE;
	SeqPOUWtFlg.POU3 = FALSE;
	SeqPOUWtEnd = TRUE;

	SeqSendFlmSet(LD_DownLoad_End);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
//	data.uw_dat[0] = 0;									// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	SeqLdSendBcc(0);									// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行

}


/********************************************************************
*	Function	: データ変更コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdDataChgWr(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqChgDataCnt = data.uw_dat[0];								// 変更ﾃﾞｰﾀ点数
	if(SeqChgDataCnt > DataChgMax){
		SeqRasCode = SeqRasMoniOver;							// ﾓﾆﾀ登録ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
		SeqMKind[loop1] = SeqRev.data[(SeqSendFlmCnt + 2)];		// ﾒﾓﾘ種別
		if(SeqMKind[0] > MkindNoMax){
			SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
			SeqRasFlg = TRUE;
			break;
		}
		SeqDataTyp[loop1] = SeqRev.data[(SeqSendFlmCnt + 3)];	// ﾃﾞｰﾀ型
		data.ub_dat[0] = 0x00;
		data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 4)];
		data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 5)];
		data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
		SeqMAdr[loop1] = data.ul_dat;							// ﾒﾓﾘｱﾄﾞﾚｽ
		SeqBitData[loop1] = SeqRev.data[(SeqSendFlmCnt + 7)];	// Bit番号
		switch(SeqDataTyp[loop1]){								// 変更ﾃﾞｰﾀ
			case	SeqDtTypB:
				SeqChgData[loop1] = SeqRev.data[(SeqSendFlmCnt + 8)];
				break;
			case	SeqDtTypW:
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 8)];
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 9)];
				SeqChgData[loop1] = data.uw_dat[0];
				break;
			case	SeqDtTypL:
				data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 8)];
				data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 9)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 10)];
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 11)];
				SeqChgData[loop1] = data.ul_dat;
				break;
			default:
				SeqRasCode = SeqRasDataTypErr;				// ﾃﾞｰﾀ指定異常ｴﾗｰ
				SeqRasFlg = TRUE;
				break;
		}
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
	}

	if(!SeqRasFlg){
		for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
			d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
			d_ptr += SeqMAdr[loop1];						// 指定ｱﾄﾞﾚｽ格納
			switch(SeqDataTyp[loop1]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
					if(SeqChgData[loop1]){
						SeqBit = data.uw_dat[0] | SeqBit;
					}else{
						SeqBit = data.uw_dat[0] & ~SeqBit;
					}
					*d_ptr = SeqBit;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
					break;
				case	SeqDtTypW:
					*d_ptr = SeqChgData[loop1];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(wardﾃﾞｰﾀ)
					break;
				case	SeqDtTypL:
					data.ul_dat = SeqChgData[loop1];		// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
					*d_ptr = data.uw_dat[0];
					d_ptr ++;
					*d_ptr = data.uw_dat[1];
					break;
				default:
					break;
			}
		}

		SeqSendFlmSet(LD_Data_chg_WR);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		data.uw_dat[0] = SeqChgDataCnt;						// 変更ﾃﾞｰﾀ点数格納
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		SeqSendDcnt = SeqSendFlmCnt = 0;
		for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
			SeqSend.data[(SeqSendFlmCnt + 2)] = SeqMKind[loop1];	// ﾒﾓﾘ種別格納
			SeqSend.data[(SeqSendFlmCnt + 3)] = SeqDataTyp[loop1];	// ﾃﾞｰﾀ型格納
			data.ul_dat = SeqMAdr[loop1];					// ﾒﾓﾘｱﾄﾞﾚｽ格納
			SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[3];
			SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[2];
			SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[1];
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqBitData[loop1];	// Bit番号格納
			SeqSend.data[(SeqSendFlmCnt + 8)] = cBIT7;				// 書込ｽﾃｰﾀｽ
			SeqSend.data[(SeqSendFlmCnt + 9)] = 0x00;
			SeqSend.data[(SeqSendFlmCnt + 10)] = 0x00;
			SeqSend.data[(SeqSendFlmCnt + 11)] = 0x00;
			SeqSendFlmCnt = SeqSendFlmCnt + 10;
			SeqSendDcnt = SeqSendDcnt + 10;
		}
		data.uw_dat[0] = 2 + SeqSendDcnt;					// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 2 = 変更ﾃﾞｰﾀ点数
		SeqLdSendBcc(data.uw_dat[0]);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}


/********************************************************************
*	Function	: 強制設定登録コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSetWr(void)
{

	long_data_st	data;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ﾒﾓﾘ種別
	SeqDataTyp[0] = SeqRev.data[1];							// ﾃﾞｰﾀ型
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[2];
	data.ub_dat[2] = SeqRev.data[3];
	data.ub_dat[1] = SeqRev.data[4];
	SeqMAdr[0] = data.ul_dat;								// ﾒﾓﾘｱﾄﾞﾚｽ
	SeqBitData[0] = SeqRev.data[5];							// Bit番号
	if((SeqMKind[0] != MkindNoX) && (SeqMKind[0] != MkindNoY)){
		SeqRasCode = SeqRasDataTypErr;						// ﾃﾞｰﾀ指定異常ｴﾗｰ
		SeqRasFlg = TRUE;
	}
	switch(SeqDataTyp[0]){
		case	SeqDtTypB:
			SeqChgData[0] = SeqRev.data[6];					// 書込ﾃﾞｰﾀ
			break;
		case	SeqDtTypW:
			data.ub_dat[1] = SeqRev.data[6];
			data.ub_dat[0] = SeqRev.data[7];
			SeqChgData[0] = data.uw_dat[0];					// 書込ﾃﾞｰﾀ
			break;
		case	SeqDtTypL:
			data.ub_dat[3] = SeqRev.data[6];
			data.ub_dat[2] = SeqRev.data[7];
			data.ub_dat[1] = SeqRev.data[8];
			data.ub_dat[0] = SeqRev.data[9];
			SeqChgData[0] = data.ul_dat;					// 書込ﾃﾞｰﾀ
			break;
		default:
			SeqRasCode = SeqRasDataTypErr;					// ﾃﾞｰﾀ指定異常ｴﾗｰ
			SeqRasFlg = TRUE;
			break;
	}

	if(!SeqRasFlg){
		// ON情報作成
		if(SeqMKind[0] == MkindNoX){
			d_ptr = &SeqKpOnX[0];
		}else if(SeqMKind[0] == MkindNoY){
			d_ptr = &SeqKpOnY[0];
		}
		d_ptr += SeqMAdr[0];								// 指定ｱﾄﾞﾚｽ格納
		switch(SeqDataTyp[0]){
			case	SeqDtTypB:
				SeqBit = SeqBit16Tbl[SeqBitData[0]];
				if(SeqChgData[0]){
					*d_ptr |= SeqBit;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}else{
					*d_ptr &= ~SeqBit;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}
				break;
			case	SeqDtTypW:
				if(SeqChgData[0]){
					*d_ptr |= SeqChgData[0];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}else{
					*d_ptr &= ~SeqChgData[0];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}
				break;
			case	SeqDtTypL:
				data.ul_dat = SeqChgData[0];
				if(SeqChgData[0]){
					*d_ptr |= data.uw_dat[0];
					d_ptr ++;
					*d_ptr |= data.uw_dat[1];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
				}else{
					*d_ptr &= ~data.uw_dat[0];
					d_ptr ++;
					*d_ptr &= ~data.uw_dat[1];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
				}
				break;
			default:
				break;
		}

		// OFF情報作成
		if(SeqMKind[0] == MkindNoX){
			d_ptr = &SeqKpOffX[0];
		}else if(SeqMKind[0] == MkindNoY){
			d_ptr = &SeqKpOffY[0];
		}
		d_ptr += SeqMAdr[0];								// 指定ｱﾄﾞﾚｽ格納
		switch(SeqDataTyp[0]){
			case	SeqDtTypB:
				SeqBit = SeqBit16Tbl[SeqBitData[0]];
				if(SeqChgData[0]){
					*d_ptr &= ~SeqBit;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}else{
					*d_ptr |= SeqBit;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}
				break;
			case	SeqDtTypW:
				if(SeqChgData[0]){
					*d_ptr &= ~SeqChgData[0];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}else{
					*d_ptr |= SeqChgData[0];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
				}
				break;
			case	SeqDtTypL:
				data.ul_dat = SeqChgData[0];
				if(SeqChgData[0]){
					*d_ptr &= ~data.uw_dat[0];
					d_ptr ++;
					*d_ptr &= ~data.uw_dat[1];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
				}else{
					*d_ptr |= data.uw_dat[0];
					d_ptr ++;
					*d_ptr |= data.uw_dat[1];				// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
				}
				break;
			default:
				break;
		}

		SeqSendFlmSet(LD_Set_WR);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		SeqSend.data[0] = SeqMKind[0];						// ﾒﾓﾘ種別格納
		SeqSend.data[1] = SeqDataTyp[0];					// ﾃﾞｰﾀ型格納
		data.ul_dat = SeqMAdr[0];							// ﾒﾓﾘｱﾄﾞﾚｽ格納
		SeqSend.data[2] = data.ub_dat[3];
		SeqSend.data[3] = data.ub_dat[2];
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = SeqBitData[0];					// Bit番号格納
		data.uw_dat[0] = 6;									// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
		// 6 = (ﾒﾓﾘ種別 + ﾃﾞｰﾀ型 + ﾒﾓﾘｱﾄﾞﾚｽ + Bit番号)
		SeqLdSendBcc(data.uw_dat[0]);						// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
	}
}


/********************************************************************
*	Function	: 強制設定解除コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdResetWr(void)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	if(SeqLdByte){
		SeqMKind[0] = SeqRev.data[0];						// ﾒﾓﾘ種別
		SeqDataTyp[0] = SeqRev.data[1];						// ﾃﾞｰﾀ型
		data.ub_dat[0] = 0x00;
		data.ub_dat[3] = SeqRev.data[2];
		data.ub_dat[2] = SeqRev.data[3];
		data.ub_dat[1] = SeqRev.data[4];
		SeqMAdr[0] = data.ul_dat;							// ﾒﾓﾘｱﾄﾞﾚｽ
		SeqBitData[0] = SeqRev.data[5];						// Bit番号
		if((SeqMKind[0] != MkindNoX) && (SeqMKind[0] != MkindNoY)){
			SeqRasCode = SeqRasDataTypErr;					// ﾃﾞｰﾀ指定異常ｴﾗｰ
			SeqRasFlg = TRUE;
		}

		if(!SeqRasFlg){
			if(SeqMKind[0] == MkindNoX){
				d_ptr = &SeqKpOnX[0];
			}else if(SeqMKind[0] == MkindNoY){
				d_ptr = &SeqKpOnY[0];
			}
			d_ptr += SeqMAdr[0];							// 指定ｱﾄﾞﾚｽ格納
			switch(SeqDataTyp[0]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[0]];
					*d_ptr = data.uw_dat[0] & ~SeqBit;	// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
					break;
				case	SeqDtTypW:
					*d_ptr = 0x0000;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(wardﾃﾞｰﾀ)
					break;
				case	SeqDtTypL:
					*d_ptr = 0x0000;
					d_ptr ++;
					*d_ptr = 0x0000;					// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
					break;
				default:
					SeqRasCode = SeqRasDataTypErr;			// ﾃﾞｰﾀ指定異常ｴﾗｰ
					SeqRasFlg = TRUE;
					break;
			}
			if(SeqMKind[0] == MkindNoX){
				d_ptr = &SeqKpOffX[0];
			}else if(SeqMKind[0] == MkindNoY){
				d_ptr = &SeqKpOffY[0];
			}
			d_ptr += SeqMAdr[0];							// 指定ｱﾄﾞﾚｽ格納
			switch(SeqDataTyp[0]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[0]];
					*d_ptr = data.uw_dat[0] & ~SeqBit;	// 指定ﾒﾓﾘﾃﾞｰﾀ書込(bitﾃﾞｰﾀ)
					break;
				case	SeqDtTypW:
					*d_ptr = 0x0000;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(wardﾃﾞｰﾀ)
					break;
				case	SeqDtTypL:
					*d_ptr = 0x0000;
					d_ptr ++;
					*d_ptr = 0x0000;						// 指定ﾒﾓﾘﾃﾞｰﾀ書込(longﾃﾞｰﾀ)
					break;
				default:
					break;
			}

			SeqSendFlmSet(LD_Reset_WR);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
			SeqSend.data[0] = SeqMKind[0];					// ﾒﾓﾘ種別格納
			SeqSend.data[1] = SeqDataTyp[0];				// ﾃﾞｰﾀ型格納
			data.ul_dat = SeqMAdr[0];						// ﾒﾓﾘｱﾄﾞﾚｽ格納
			SeqSend.data[2] = data.ub_dat[3];
			SeqSend.data[3] = data.ub_dat[2];
			SeqSend.data[4] = data.ub_dat[1];
			SeqSend.data[5] = SeqBitData[0];				// Bit番号格納
			data.uw_dat[0] = 6;								// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
			// 6 = (ﾒﾓﾘ種別 + ﾃﾞｰﾀ型 + ﾒﾓﾘｱﾄﾞﾚｽ + Bit番号)
		}
	}else{
		d_ptr = &SeqKpOnX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// 領域ﾃﾞｰﾀｸﾘｱ
		}
		d_ptr = &SeqKpOnY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// 領域ﾃﾞｰﾀｸﾘｱ
		}
		d_ptr = &SeqKpOffX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// 領域ﾃﾞｰﾀｸﾘｱ
		}
		d_ptr = &SeqKpOffY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// 領域ﾃﾞｰﾀｸﾘｱ
		}

		SeqSendFlmSet(LD_Reset_WR);							// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行
		data.uw_dat[0] = 0;									// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	}
	SeqLdSendBcc(data.uw_dat[0]);							// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行
}


/********************************************************************
*	Function	: ステータス読出コマンド処理
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 10/08/26	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SeqLdStatasRd(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	SeqSendFlmSet(LD_Statas_RD);						// 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理実行

	s_ptr = &SeqStatTypeTbl[0];							// 格納元先頭ｱﾄﾞﾚｽ格納
	d_ptr = &(SeqSend.data[0]);							// 格納先先頭ｱﾄﾞﾚｽ格納
	for(loop1 = 0; loop1 < 16; loop1++, *s_ptr++, *d_ptr++){
		*d_ptr = *s_ptr;								// ﾓｼﾞｭｰﾙ型式文字列格納
	}
	
//	data.uw_dat[0] = HW_Ver;							// HWﾊﾞｰｼﾞｮﾝ格納
	data.uw_dat[0] = hwVersion;							// HWﾊﾞｰｼﾞｮﾝ格納
	SeqSend.data[16] = data.ub_dat[1];
	SeqSend.data[17] = data.ub_dat[0];
//	data.uw_dat[0] = SW_Ver;							// SWﾊﾞｰｼﾞｮﾝ格納
	data.uw_dat[0] = swVersion;							// SWﾊﾞｰｼﾞｮﾝ格納
	SeqSend.data[18] = data.ub_dat[1];
	SeqSend.data[19] = data.ub_dat[0];
	SeqSend.data[20] = SeqSysStat;						// ｽﾃｰﾀｽ情報格納
	SeqSend.data[21] = 0x00;							// 予備格納
//	data.uw_dat[0] = 22;								// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	// 22 = (ﾓｼﾞｭｰﾙ型式文字列 + HWﾊﾞｰｼﾞｮﾝ + SWﾊﾞｰｼﾞｮﾝ + ｽﾃｰﾀｽ + 予備)
	SeqLdSendBcc(22);									// 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理実行

}


/********************************************************************
*	Function	: 送信ﾌﾚｰﾑｺﾏﾝﾄﾞﾍｯﾀﾞ部作成処理
*	Param		: None
*	Return		: None
*	Date		: 09/11/23	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqSendFlmSet(unsigned short CM_MD)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	s_ptr = &SeqSendFlmDataTbl[0];						// 格納元先頭ｱﾄﾞﾚｽ格納
	d_ptr = &(SeqSend.sSCodeFlg);						// 格納先先頭ｱﾄﾞﾚｽ格納
	for(loop1 = 0; loop1 <= 18; loop1++, s_ptr++, d_ptr++){
		*d_ptr = *s_ptr;								// 送信ﾌﾚｰﾑﾌｫｰﾏｯﾄ読出
	}
	data.uw_dat[0] = CM_MD;								// CMND/MODE格納
	SeqSend.CMND = data.ub_dat[0];
	SeqSend.MODE = data.ub_dat[1];
	SeqSend.endInfo = SeqLdEnd;							// 終了情報格納
	SeqSend.seqNumber = SeqLdNo;						// ｼｰｹﾝｽ番号格納
}

/********************************************************************
*	Function	: 送信用BCC/ﾃﾞｰﾀ数ｶｳﾝﾀ格納処理
*	Param		: None
*	Return		: None
*	Date		: 09/11/23	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendBcc(unsigned short dcnt)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr;

	data.uw_dat[0] = dcnt;							// ﾃﾞｰﾀ部ﾊﾞｲﾄ数格納
	SeqSend.BYTEN[0] = data.ub_dat[1];
	SeqSend.BYTEN[1] = data.ub_dat[0];

	data.uw_dat[1] = dcnt + ((19 - 3) + 1);			// ﾃﾞｰﾀ数ｶｳﾝﾀ格納
													// ﾃﾞｰﾀｶｳﾝﾀ数 = ((伝送ﾍｯﾀﾞ部 + ｺﾏﾝﾄﾞﾍｯﾀﾞ部 + ｺﾏﾝﾄﾞﾃﾞｰﾀ部) - 伝送ﾍｯﾀﾞ部 + BCC)
	SeqSend.datacnt[0] = data.ub_dat[3];
	SeqSend.datacnt[1] = data.ub_dat[2];

	SeqSendFlmCnt = dcnt + 19;

	SeqSendBcc = 0;
	s_ptr = &(SeqSend.sSCodeFlg);					// 格納元先頭ｱﾄﾞﾚｽ格納
	for(loop1 = 0; loop1 < SeqSendFlmCnt; loop1++, *s_ptr++){
		SeqSendBcc += *s_ptr;
	}
	SeqSendBcc = SeqSendBcc - CODE_STX;				// ｽﾀｰﾄｺｰﾄﾞを削除
	SeqSendBcc = (0x00 - SeqSendBcc) & 0x00FF;		// BCC算出
//	SeqSend.data[(SeqSendFlmCnt - 19)] = SeqSendBcc;	// BCC格納
	SeqSend.data[dcnt] = SeqSendBcc;				// BCC格納

	SeqSendCnt = SeqSendFlmCnt + 1;					// 送信ﾊﾞｲﾄ数設定(送信関数用)
}

