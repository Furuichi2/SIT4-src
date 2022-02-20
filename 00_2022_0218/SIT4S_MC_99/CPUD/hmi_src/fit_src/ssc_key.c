/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			キー入力関係の処理														*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-07
*
*************************************************************************************/

#include "string.h"								//標準ライブラリ

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"


/* 外部参照関数定義 -------------------------------------------------- */
extern	UNl		DigRnaChange1(UNs);
extern	void	ADC_NEXTNAME_SET(void);			/* ＡＤＣ次型番号名称 			*/
extern	void	ASM_KEY_2_SEQ(void);			//SIT4-MC	2014/08/24

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		Key_Data_Flg;
extern	UNs		Key_Data_No[4];
extern	UNs		Key_Data_WK[4];	//V05q
extern	UNs		GMN_PAR001;						//補正下限値 /* V00r */
extern	UNs		GMN_PAR002;						//生産段取寸動上限 /* V01  */
extern	UNs		GMN_PAR003;						//連寸一行程時の目標角度上限 /* V01e */
extern	UNs		GMN_PAR004;						//待機点角度設定下限値 /* V01i */
extern	UNs		GMN_PAR005;						//待機点角度設定上限値 /* V01i */
extern	UNs		CB_SYS_PARAM045;				// /* V01i */
extern	UNs		GMN_PAR006;						//ﾓｰｼｮﾝ角度設定下限値 /* V01j */
extern	UNs		GMN_PAR007;						//ﾓｰｼｮﾝ角度設定上限値 /* V01j */
extern	UNs		GMN_PAR008;						//ﾓｰｼｮﾝ角度大小比較有効／無効 /* V01j */
extern	UNs		GMN_PAR009;						//ﾎﾟｼﾞｼｮﾅ(ｵﾌﾟｼｮﾝ)ﾋﾞｯﾄ飛び回数
extern	UNs		GMN_PAR010;						//荷重補正下限値 /* V01m */
extern	UNs		GMN_PAR011;						//荷重目標変更上下限値 /* V01m */
extern	UNs		GMN_PAR012;						//下限目標変更上下限値 /* V01m */
extern	UNs		GMN_PAR013;						//目標荷重下限値 /* V01m */
extern	UNs		GMN_PAR024;						//ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度 /* V01n */
extern	UNs		GMN_PAR035;						//ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間 /* V01n */
extern	UNs		GMN_PAR015;						//反転の上限角上限値 /* V05  */
extern	UNs		GMN_PAR016;						//振子の上限角上限設定 /* V06f */
extern	UNs		GMN_PAR017;						//ﾌﾞﾚｰｷ角度上限値（0～359度）V05n
extern	UNs		GMN_PAR018;						//ﾌﾞﾚｰｷﾀｲﾑ上限値（0～999ms）V05n
extern	UNs		GMN_PAR019;						//振子の上限角上限設定 /* V06f */
extern	UNs		GMN_PAR039;						//制動性能試験インターバルタイマ上限値	V05r
extern	UNs		GMN_PAR041;						//外部タイマ上限値	V05r
extern	UNs		CB_SYS_PARAM279;				// /* V06m */
extern	UNs		GMN_PAR021;						//振子ﾓｰｼｮﾝ設定制限		/* V06m */
extern	UNs		GMN_PAR042;						//反転ﾓｰﾄﾞP設定上限		/* V06n */
extern	UNs		GMN_PAR043;						//反転ﾓｰﾄﾞS設定上限		/* V06n */
extern	UNs		GMN_PAR020;						//V06n
extern	UNs		GMN_PAR044;						//段取速度下限		/* V06o */
extern	UNs		GMN_PAR049;						//ｵｰﾊﾞｰﾛｰﾄﾞ、ﾛｱｰﾘﾐｯﾄの左と右の上限
extern	UNs		GMN_PAR050;						//ｵｰﾊﾞｰﾛｰﾄﾞ、ﾛｱｰﾘﾐｯﾄの合計の上限
extern	UNs		KEY_INF_2_SEQ[2];				//SIT4-MC
extern	UNs		GMN_PAR069;						//待機判定時間上限設定の上限値
extern	UNs		GMN_PAR075;						//進角  角度入力上限							2014/09/01
extern	UNs		GMN_PAR076;						//進角  時間入力上限							2014/09/01
extern	UNs		GMN_PAR077;						//繰り返し回数上限								2014/09/04
extern	S2b		GMN_PAR070;						//リリースカムオフ角度:回転,ふりこ
extern	S2b		GMN_PAR071;						//リリースカムオフ角度差分:反転
extern	S2b		GMN_PAR072;						//送りカムオン角度差分:
extern	S2b		GMN_PAR073;						//タイングカムオン角度差分:
extern	S2b		GMN_PAR074;						//タイングカムオフ角度差分:
extern	UNs		GMN_PAR080;						//ﾀﾞｲﾊｲﾄ補正上限ﾘﾐｯﾀ
extern	UNs		GMN_PAR081;						//荷重補正上限ﾘﾐｯﾀ
extern	UNs		GMN_PAR046;						//ﾓｰｼｮﾝ目標荷重上限								2015/01/15
extern	UNs		GMN_PAR047;						//ﾓｰｼｮﾝ目標荷重下限								2015/01/15
extern	UNs		GMN_PAR083;						//戻り行程速度下限値							2015/07/10
extern	UNs		GMN_PAR085;						//ﾓｰｼｮﾝ最大段数									2015/10/21
extern	UNs		SYS_FEED_PAR0010;				//ﾌｨｰﾀﾞ型式番号上限								2016/03/23
extern	UNs		SYS_FEED_PAR0011;				//ﾌｨｰﾀﾞ低速時速度上限							2016/03/23
extern	UNs		GMN_PAR096;						//振動回数上限									2016/09/20
extern	UNs		GMN_PAR097;						//振動回数下限									2016/09/20
extern	UNs		GMN_PAR098;						//戻り量比率設定上限							2016/09/20
extern	UNs		GMN_PAR100;						//多段終了角度上限設定							2016/09/30
extern	UNs		GMN_PAR101;						////ロータリカムOFFタイマ上限					2016/11/15

//2019-04-20 荷重オーバロードの設定上限追加 設定上下PARAM<最大荷重
extern	UNs		GMN_PAR106;						//2019-04-20 ｵｰﾊﾞﾛｰﾄﾞ左右,ﾛｱﾘﾐｯﾄ左右,振幅の設定上限
extern	UNs		GMN_PAR107;						//2019-04-20 ｵｰﾊﾞﾛｰﾄﾞ合計,ﾛｱﾘﾐｯﾄ合計,振幅の設定上限

extern	UNs		GMN_PAR111;						//外部タイマ上限２	2020/01/30 A01s

/* 定数定義 ---------------------------------------------------------- */
#define		E_SUBE1_DN	0x00D0				//上下限データポインタ
#define		E_SUBE2_DN	4					//上下限データポインタ
#define		E_SUBE3_DN	8					//上下限データポインタ
#define		E_SUBE4_DN	12					//上下限データポインタ
#define		E_SUBE5_DN	16					//上下限データポインタ
#define		E_SUBE6_DN	20					//上下限データポインタ
#define		DigMaxMin1(dig)		if(dig<0){dig=0;}else{if(359<dig){dig=359;}}

/* データ型定義 ------------------------------------------------------ */

/* プロトタイプ宣言 -------------------------------------------------- */
void	Key_mng(void);							//ｷｰ入力確定
void	Key_Ten_in(UNs );						//Ten KEY入力
void	Key_Ent_sv(void);						//設定値の確定
//2014/08/27	void	Key_sv_limt_chk(UNs, UNl *);			//設定値の上下限チェック
UNs		Key_sv_limt_chk(UNs, UNl *);			//設定値の上下限チェック
void	Key_sv_tokusyu_chk(UNs);				//設定値の特殊処理
void	dansuu_zero_set(void);					//ｶﾑの段 強制00設定
UNs kajyu_chk( UNl *Dst_p, UNl bf );
UNs kagen_chk( UNl *Dst_p, UNl bf );
void	KEY_FILTER(void);						//KEYフィルタ処理	V05q
void	RELEASE_POS_2_AGL_CAL(UNl bf);
void	SEND_POS_2_AGL_CAL(UNl bf);
UNl		CAM_AUTO_LIMIT(UNl bf);
void	REP_CAM_CLR(UNs dan);

S2b		DigAddDigUnit1(S2b dig1,S2b dig2);
S2b		TAIKIAREA_MAXMIN(S2b dig);
U2b		CAM_KOUTEI_SEARCH1(U2b sel,S2b dig);
U2b		CAM_KOUTEI_SEARCH2(U2b sel,S2b dig);

UNl motion_spd_limit1(UNl bf, UNs t_no);//2015/07/10
UNl motion_dig_limit0(UNl, UNs);
UNl motion_dig_limit1(UNl, UNs);
UNl motion_dig_limit2(UNl, UNs);
UNl motion_pos_limit0(UNl, UNs);
UNl motion_pos_limit1(UNl, UNs);
UNl motion_pos_limit2(UNl, UNs);

void	copy_mot100(void);						//モーションデータ10段領域から100段領域にコピー		2016/03/26


/* 内部変数定義 ------------------------------------------------------ */

/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Key_mng(旧：KEY_SWMNG)
*  Function Name:	ｷｰ入力確定
*  Input	: 		なし
*  Return	: 		なし
*  Note		:Ｋｅｙデータ読込＆データ確定
*			ＯＵＴ＝ＫＥＹ＿ＤＡＴＡ＿ＭＯＤＥ
*			ＯＵＴ＝ＫＥＹ＿ＤＡＴＡ＿ＣＯＤＥ
*
*  履 歴	:FIT)田端		ON:2002-05-20
********************************************************************************
*/
void	Key_mng(void)
{
	UNs	wk1[5];


	KEY_DATA_MODE = 0;							/* ﾓｰﾄﾞｸﾘｱ	*/
	KEY_DATA_CODE = 0;							/* ｺｰﾄﾞｸﾘｱ	*/

	if( Key_Data_Flg == 0xff ) {

		KEY_FILTER();							//V05q
		//これ以降の Key_Data_No -> Key_Data_WK

		wk1[0] = Key_Data_WK[0] ^ Key_last[0];	/* key状態の変化を検出	*/
		wk1[1] = Key_Data_WK[1] ^ Key_last[1];
		wk1[2] = Key_Data_WK[2] ^ Key_last[2];
		wk1[3] = Key_Data_WK[3] ^ Key_last[3];

		Key_up[0]  = wk1[0] & Key_Data_WK[0];	/* 立ち上がりデータ格納 */
		Key_up[1]  = wk1[1] & Key_Data_WK[1];	/* 立ち上がりデータ格納 */
		Key_up[2]  = wk1[2] & Key_Data_WK[2];	/* 立ち上がりデータ格納 */
		Key_up[3]  = wk1[3] & Key_Data_WK[3];	/* 立ち上がりデータ格納 */

		Key_dn[0] = wk1[0] & Key_last[0];		/* 立ち下がりデータ格納 */
		Key_dn[1] = wk1[1] & Key_last[1];		/* 立ち下がりデータ格納 */
		Key_dn[2] = wk1[2] & Key_last[2];		/* 立ち下がりデータ格納 */
		Key_dn[3] = wk1[3] & Key_last[3];		/* 立ち下がりデータ格納 */
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		Key_dn[0] &= 0x0002;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[1] &= 0x0002;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[2] &= 0x0006;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[3] &= 0x0004;					/* 不用データマスク　ＳＷだけ残す */
#else
		Key_dn[0] &= 0x0002;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[1] &= 0x0006;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[2] &= 0x0006;					/* 不用データマスク　ＳＷだけ残す */
//V01z		Key_dn[3] &= 0x0002;					/* 不用データマスク　ＳＷだけ残す */
		Key_dn[3] &= 0x0006;					/* 不用データマスク　ＳＷだけ残す */
#endif

		Key_last[0] = Key_Data_WK[0];
		Key_last[1] = Key_Data_WK[1];
		Key_last[2] = Key_Data_WK[2];
		Key_last[3] = Key_Data_WK[3];

		ASM_KEY_2_SEQ();						//KEY情報をｼｰｹﾝｽ出力用に加工	SIT4-MC		2014/08/24
		SEQ_PAR_097 = KEY_INF_2_SEQ[0];
		SEQ_PAR_098 = (SEQ_PAR_098 & 0x00ff) | KEY_INF_2_SEQ[1];

		Key_Data_Flg = 0;						/* Ｋｅｙデータフラグクリア */

		if( (Key_up[0] != 00) || (Key_up[1] != 00) ||		/* Ｋｅｙ立ち上がり あり？	*/
			(Key_up[2] != 00) || (Key_up[3] != 00) ) {		/* Ｋｅｙ立ち上がり あり？	*/
/************	テンキー受付処理	*********************************/
			if( ((Key_up[0] & 0x0038) != 00) || ((Key_up[2] & 0x0038) != 00) ||
				((Key_up[1] & 0x0038) != 00) || ((Key_up[3] & 0x0038) != 00) ) {
				KEY_DATA_MODE = E_key_ten_mode;		/* テンキーモードセット */

				if( Key_up[0] & 0x0008 ) {
					KEY_DATA_CODE = E_key_0;		/* 0ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x08 ) {
					KEY_DATA_CODE = E_key_1;			/* 1ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x10 ) {
					KEY_DATA_CODE = E_key_2;			/* 2ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x20 ) {
					KEY_DATA_CODE = E_key_3;			/* 3ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x08 ) {
					KEY_DATA_CODE = E_key_4;			/* 4ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x0010 ) {
					KEY_DATA_CODE = E_key_5;			/* 5ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x0020 ) {
					KEY_DATA_CODE = E_key_6;			/* 6ＫＥＹコードセット */
				}
				else if( Key_up[3] & 0x08 ) {
					KEY_DATA_CODE = E_key_7;			/* 7ＫＥＹコードセット */
				}
				else if( Key_up[3] & 0x10 ) {
					KEY_DATA_CODE = E_key_8;			/* 8ＫＥＹコードセット */
				}
				else if( Key_up[3] & 0x20 ) {
					KEY_DATA_CODE = E_key_9;			/* 9ＫＥＹコードセット */
				}
				else if( Key_up[0] & 0x0010 ) {
					KEY_DATA_CODE = E_key_ten;			/* ．ＫＥＹコードセット */
				}
				else if( Key_up[0] & 0x0020 ) {
					KEY_DATA_CODE = E_key_cl;			/* CL ＫＥＹコードセット */
				}
			}
/************	ＥＮＴキー受付処理	*********************************/
			else if( Key_up[0] & 0x0004 ) {
				KEY_DATA_MODE = E_key_ent_mode;		/* ＥＮＴ　モードセット */
				KEY_DATA_CODE = E_key_ent;			/* ＥＮＴ　ＫＥＹコードセット */
			}
/************	カーソルキー受付処理	*********************************/
			else if( ((Key_up[0] & 0x01) != 00) || ((Key_up[2] & 0x01) != 00) ||
					((Key_up[1] & 0x01) != 00) || ((Key_up[3] & 0x01) != 00) ) {
				KEY_DATA_MODE = E_key_csr_mode;		/* カーソル　モードセット */

				if( Key_up[0] & 0x0001 ) {
					KEY_DATA_CODE = E_key_left;		/* ←　ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x01 ) {
					KEY_DATA_CODE = E_key_right;	/* →　ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x0001 ) {
					KEY_DATA_CODE = E_key_down;		/* ↓　ＫＥＹコードセット */
				}
				else if( Key_up[3] & 0x01 ) {
					KEY_DATA_CODE = E_key_up;		/* ↑　ＫＥＹコードセット */
				}
			}
/************	ＳＷ１～ＳＷ４キー受付処理	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_up[0] & 0x02) != 00) || ((Key_up[2] & 0x02) != 00) ||
					((Key_up[1] & 0x02) != 00) || ((Key_up[3] & 0x02) != 00) ) {
				KEY_DATA_MODE = E_key_sw14_mode;		/* ＳＷ　モードセット */

				if( Key_up[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1;		/* ＳＷ１　ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2;			/* ＳＷ２　ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3;			/* ＳＷ３　ＫＥＹコードセット */
				}
				else if( Key_up[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4;			/* ＳＷ４　ＫＥＹコードセット */
				}
			}
#else
			else if( ((Key_up[0] & 0x02) != 00) || ((Key_up[2] & 0x02) != 00) ||
					((Key_up[1] & 0x02) != 00) || ((Key_up[3] & 0x02) != 00) ||
					((Key_up[3] & 0x04) != 00) ) {										/* V01z */
				KEY_DATA_MODE = E_key_sw14_mode;		/* ＳＷ　モードセット */

				if( Key_up[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1;		/* ＳＷ１　ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2;			/* ＳＷ２　ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3;			/* ＳＷ３　ＫＥＹコードセット */
				}
				else if( Key_up[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4;			/* ＳＷ４　ＫＥＹコードセット */
				}
				else if( Key_up[3] & 0x04 ) {			/* V01z */
					KEY_DATA_CODE = E_key_sw7;			/* ＳＷ７　ＫＥＹコードセット */
				}
			}
#endif
/************	ＳＷ５～ＳＷ６操作キー受付処理	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_up[2] & 0x04) != 00) || ((Key_up[3] & 0x04) != 00) ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* 操作　モードセット */

				if( Key_up[3] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5;			/* ＳＷ５　ＫＥＹコードセット */
				}
				else if( Key_up[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6;			/* ＳＷ６　ＫＥＹコードセット */
				}
			}
#else
			else if( ((Key_up[2] & 0x04) != 00) || ((Key_up[1] & 0x04) != 00) ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* 操作　モードセット */

				if( Key_up[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5;			/* ＳＷ５　ＫＥＹコードセット */
				}
				else if( Key_up[1] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6;			/* ＳＷ６　ＫＥＹコードセット */
				}
			}
#endif
/************	ＳＷ７型段取りキー受付処理	*********************************/
			else {
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				if( Key_up[1] & 0x04 ) {
					KEY_DATA_MODE = E_key_sw7_mode;		/* モードセット */
					KEY_DATA_CODE = E_key_sw7;			/* ＳＷ７　ＫＥＹコードセット */
				}
#else
#endif
			}
		}

/* 立ち下がりデータ検出処理へ	*/
		else if( (Key_dn[0] != 00) || (Key_dn[2] != 00) ||		/* Ｋｅｙ立ち下がり あり？	*/
			(Key_dn[1] != 00) || (Key_dn[3] != 00) ) {
/************	ＳＷ５～ＳＷ６操作キー受付処理	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			if( (Key_dn[2] & 0x04) != 00 || (Key_dn[3] & 0x04) != 00 ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* 操作　モードセット */

				if( Key_dn[3] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5_down;			/* ＳＷ５　ＫＥＹコードセット */
				}
				else if( Key_dn[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6_down;			/* ＳＷ６　ＫＥＹコードセット */
				}
			}
#else
			if( (Key_dn[2] & 0x04) != 00 || (Key_dn[1] & 0x04) != 00 ) {
				KEY_DATA_MODE = E_key_sw56_mode;		/* 操作　モードセット */

				if( Key_dn[2] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw5_down;			/* ＳＷ５　ＫＥＹコードセット */
				}
				else if( Key_dn[1] & 0x04 ) {
					KEY_DATA_CODE = E_key_sw6_down;			/* ＳＷ６　ＫＥＹコードセット */
				}
			}
#endif
/************	ＳＷ１～ＳＷ４キー受付処理	*********************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
			else if( ((Key_dn[0] & 0x02) != 00) || ((Key_dn[2] & 0x02) != 00) ||
					((Key_dn[1] & 0x02) != 00) || ((Key_dn[3] & 0x02) != 00) ) {
				KEY_DATA_MODE = E_key_sw14_mode;		/* ＳＷ　モードセット */

				if( Key_dn[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1_down;		/* ＳＷ１　ＫＥＹコードセット */
				}
				else if( Key_dn[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2_down;		/* ＳＷ２　ＫＥＹコードセット */
				}
				else if( Key_dn[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3_down;		/* ＳＷ３　ＫＥＹコードセット */
				}
				else if( Key_dn[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4_down;		/* ＳＷ４　ＫＥＹコードセット */
				}
			}
#else
			else if( ((Key_dn[0] & 0x02) != 00) || ((Key_dn[2] & 0x02) != 00) ||
					((Key_dn[1] & 0x02) != 00) || ((Key_dn[3] & 0x02) != 00) ||
					((Key_dn[3] & 0x04) != 00) ) {									/* V01z */
				KEY_DATA_MODE = E_key_sw14_mode;		/* ＳＷ　モードセット */

				if( Key_dn[3] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw1_down;		/* ＳＷ１　ＫＥＹコードセット */
				}
				else if( Key_dn[2] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw2_down;		/* ＳＷ２　ＫＥＹコードセット */
				}
				else if( Key_dn[1] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw3_down;		/* ＳＷ３　ＫＥＹコードセット */
				}
				else if( Key_dn[0] & 0x02 ) {
					KEY_DATA_CODE = E_key_sw4_down;		/* ＳＷ４　ＫＥＹコードセット */
				}
				else if( Key_dn[3] & 0x04 ) {			/* V01z */
					KEY_DATA_CODE = E_key_sw7_down;		/* ＳＷ７　ＫＥＹコードセット */
				}
			}
#endif
		}
	}
}


/*
********************************************************************************
*  Module Name:		Key_Ten_in(旧：TENKEY_INP)
*  Function Name:	Ten KEY入力
*  Input	: 		入力ｷｰ･ｺｰﾄﾞ
*
*  Return	: 		なし
*  Note		:		0～9/．/CL　ｷｰ入力処理
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	Key_Ten_in(UNs k_code)
{
	UNs		t_no, i;
	UNl		d_bf;

	if(CSR_CNT == 00 || SV_TBL_POS_NOW == 0xff ) {			//カーソル位置に設定値なし
		return;
	}

	t_no = SV_TBL_POS_NOW;

	if (SV_buff[t_no].TOK_FLG & BIT_6) {					//符号設定はTENｷｰ無効			2014/03/13
		return;
	}

	if(k_code == E_key_cl) {								//CL Key ?
		SV_DATA_CHG = 0xff;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
		SV_DISP_BUFF = 0;									//変更データバッファクリア

		TENKEY_CNT = SV_buff[t_no].XY_POS;					//設定値表示のX,Y軸
		TENKEY_CNT >>= 10;									//ｶｰｿﾙ長　設定

		if(SV_buff[t_no].TOK_FLG & BIT_2) {					//特殊ﾌﾗｸﾞ(全角データ？)
			TENKEY_CNT >>= 1;								//全角
		}
		if(SV_buff[t_no].TEN_POS != 00 ) {					//小数点有りデータ？
			TENKEY_CNT--;									//Yes
			TENKEY_CNT -= SV_buff[t_no].TEN_POS;			//小数以下の入力を無効にする
		}
	}
	else if(k_code == E_key_ten) {							//'.' Key ?
		if (SV_DATA_CHG == 0x55) {
			//既に.(TEN)受付済								// 2013/02/04 V06o
			return;
		}
		else {
			TENKEY_CNT = SV_buff[t_no].TEN_POS;					//小数以下の入力を有効にする
			SV_DATA_CHG = 0x55;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
		}
	}
	else{													//0～9 Key入力
		if(SV_DATA_CHG == 00) {								//設定ﾃﾞｰﾀ変更 有り？
			SV_DATA_CHG = 0xff;								//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
			SV_DISP_BUFF = 0;								//変更データバッファクリア

			TENKEY_CNT = SV_buff[t_no].XY_POS;				//設定値表示のX,Y軸
			TENKEY_CNT >>= 10;								//ｶｰｿﾙ長　設定

			if(SV_buff[t_no].TOK_FLG & BIT_2) {				//特殊ﾌﾗｸﾞ(全角データ？)
				TENKEY_CNT >>= 1;							//全角
			}
			if(SV_buff[t_no].TEN_POS != 00 ) {				//小数点有りデータ？
				TENKEY_CNT--;								//Yes
				TENKEY_CNT -= SV_buff[t_no].TEN_POS;		//小数以下の入力を無効にする
			}
		}

		if( TENKEY_CNT == 00 ) {							//入力オーバー？
			return;											//Yes
		}
		else{
			d_bf = k_code & 0x000f;
			TENKEY_CNT--;									//-1
			if(SV_DATA_CHG == 0x55){						//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
				for(i=TENKEY_CNT ; i > 0 ; i--){			//桁の整列
					d_bf <<= 4;
				}
				SV_DISP_BUFF |= d_bf;						//ＫＥＹコードセット
			}
			else{
				for(i=SV_buff[t_no].TEN_POS ; i > 0 ; i--){	//桁の整列
					d_bf <<= 4;
				}
				SV_DISP_BUFF <<= 4;							//変更データバッファクリア
				SV_DISP_BUFF |= d_bf;						//ＫＥＹコードセット
			}
		}
	}

	if( SV_buff[t_no].TOK_FLG & BIT_7 ) {					//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
		i = 0xff;
	}
	else{													//あり
		i = 0x00;
	}
	SVPV_data_disp(SV_DISP_BUFF, &SV_buff[t_no], i, 0x82);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/反転表示)

//	if( SV_DISP_BUFF == 0 ) {
//		TENKEY_CNT = SV_buff[t_no].XY_POS;					//設定値表示のX,Y軸
//		TENKEY_CNT >>= 10;									//ｶｰｿﾙ長　設定
//
//		if(SV_buff[t_no].TOK_FLG & BIT_2) {					//特殊ﾌﾗｸﾞ(全角データ？)
//			TENKEY_CNT >>= 1;								//全角
//		}
//		if(SV_buff[t_no].TEN_POS != 00 ) {					//小数点有りデータ？
//			TENKEY_CNT--;									//Yes
//			TENKEY_CNT -= SV_buff[t_no].TEN_POS;			//小数以下の入力を無効にする
//		}
//	}
}


/*
********************************************************************************
*  Module Name:		Key_Ent_sv(旧：SVDATA_ENT)
*  Function Name:	設定値の確定
*  Input	: 		なし
*  Return	: 		なし
*  Note		:		ENT　ｷｰ入力処理
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	Key_Ent_sv(void)
{
	UNs		t_no, z_f, *Dst_p, cnt, flag;
	UNl		cnv_bf, *Dst_lp;
	long	*Dst_Slp, cnv_Sbf;
	short	*Dst_Sp;
	UNs		sv_ref;

	sv_ref = 0;

	t_no = SV_TBL_POS_NOW;

	if (SV_buff[t_no].TOK_FLG & BIT_6) {					//符号設定はTENｷｰ無効			2014/03/13 ----------------------------------

		cnt = (SV_buff[t_no+1].BYTE_NO & 0x000f);			//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		if(cnt == 4){										//long(4byte) ?
			Dst_Slp = (long *)SV_buff[t_no+1].DATA_ADR;		//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_Sbf = *Dst_Slp;
		}
		else{												//short(2byte)
			Dst_Sp = (short *)SV_buff[t_no+1].DATA_ADR;		//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			cnv_Sbf = (long)*Dst_Sp;
		}

		cnv_Sbf *= -1;
		Key_sv_limt_chk(t_no+1, (UNl *)&cnv_Sbf);				//設定値の上下限チェック

		Dst_p = SV_buff[t_no].DATA_ADR;						//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ

		if (cnv_Sbf == 0) {									//2014/08/20
			if ( *Dst_p == 0x2b20 ) {
				*Dst_p = 0x2d20;								//[-]
				cnv_bf = 0x2d20;
			}
			else {
				*Dst_p = 0x2b20;								//[+]
				cnv_bf = 0x2b20;
			}
		}
		else {
			if ( cnv_Sbf >= 0 ) {
				*Dst_p = 0x2b20;								//[+]
				cnv_bf = 0x2b20;
			}
			else {
				*Dst_p = 0x2d20;								//[-]
				cnv_bf = 0x2d20;
			}
		}

		if(cnt == 4){										//long(4byte) ?
			*Dst_Slp = (UNl)cnv_Sbf;						//ﾃﾞｰﾀ格納
		}
		else{												//short(2byte)
			*Dst_Sp = (UNs)cnv_Sbf;						//ﾃﾞｰﾀ格納
		}

		FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], 0xff, 0x04);		//符号表示(ｾﾞﾛｻﾌﾟﾚｽ無し)

		if ( cnv_Sbf < 0 ) {
			cnv_Sbf *= -1;
		}
		cnv_bf = (UNs)cnv_Sbf;
		SVPV_data_disp(cnv_bf, &SV_buff[t_no+1], 0x00, 0x01);	//設定値表示(ｾﾞﾛｻﾌﾟﾚｽ有り)

		SV_csr_set();										//設定値カーソル

		CSR_MOVE_NON = 0xff;

		SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//格納ﾌﾗｸﾞ			2016/03/21
	}														//-----------------------------------------------------------------------------


	if(SV_DATA_CHG != 00){
		SV_DATA_CHG = 00;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)

		cnv_bf = BCD_HEX4(SV_DISP_BUFF);					//BCD → HEX 変換

		if (SV_buff[t_no].TOK_FLG & BIT_5) {				//絶対値表示？			2014/03/14
			Dst_p = SV_buff[t_no-1].DATA_ADR;				//符号格納ｱﾄﾞﾚｽ
			if ( *Dst_p == 0x2d20 ) {						//ﾃﾞｰﾀはﾏｲﾅｽ
				cnv_bf = (long)cnv_bf * -1;					//ﾃﾞｰﾀをﾏｲﾅｽに
			}
		}

//2014/08/27		Key_sv_limt_chk(t_no, &cnv_bf);						//設定値の上下限チェック
		sv_ref = Key_sv_limt_chk(t_no, &cnv_bf);						//設定値の上下限チェック

		if(SV_buff[t_no].TOK_FLG & BIT_0){					//特殊ﾌﾗｸﾞ(BCD ?)
			cnv_bf = HEX_BCD4(cnv_bf);						//HEX → BCD 変換
		}
		cnt = (SV_buff[t_no].BYTE_NO & 0x000f);				//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
		if(cnt == 4){										//long(4byte) ?
			Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			*Dst_lp = cnv_bf;
		}
		else{												//short(2byte)
			Dst_p = SV_buff[t_no].DATA_ADR;					//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			*Dst_p = (UNs)cnv_bf;
		}

		FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

		flag = 0x02;										//BCD
		if(0 == (SV_buff[t_no].TOK_FLG & BIT_0) ){			//特殊ﾌﾗｸﾞ(HEX ?)
			flag = 0x01;									//HEX
		}

		if( SV_buff[t_no].TOK_FLG & BIT_7 ) {				//特殊ﾌﾗｸﾞb7 = ｾﾞﾛｻﾌﾟﾚｽあり　？
			z_f = 0xff;
		}
		else {												//あり
			z_f = 0x00;
		}

		if ( SV_buff[t_no].TOK_FLG & BIT_5 ) {				//絶対値表示？		2014/03/14
			if ( (long)cnv_bf < 0 ) {
				cnv_bf = (long)cnv_bf * -1;
			}
		}

		if ((WINDOW_NO == 12) && (SV_buff[t_no].SUB_NO == 48)) {	// ADCｽﾃｯﾌﾟﾓﾆﾀ画面の次型番号？		V01j
			flag |= BIT_9;
		}

		if (sv_ref) {										//2014/08/27
			SVdata_disp();
		}
		else {
			SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);		//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)
		}

		WIN_grph();											//ウインドウ画面上グラフィック描画

		Key_sv_tokusyu_chk(t_no);							//設定値特殊処理

		TENKEY_CNT = 0;
		SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//格納ﾌﾗｸﾞ
	}

	if( CSR_MOVE_NON != 0xff ) {							//カーソルは動かない？

		CSR_FLG = 2;										//→ポジションセット

//V01d		if( GAMEN_NO != 3 && GAMEN_NO != 28 ){
		if( GAMEN_NO != 3 && GAMEN_NO != 28 && GAMEN_NO != 6 && GAMEN_NO != 30 ){
			if(SV_buff[t_no].DSP_NO >=							//ｶｰｿﾙ認識番号内の移動順位
				CSR_buff[CSR_TBL_POS_NOW].SV_MAX) {				//設定値ﾃｰﾌﾞﾙ個数
				CSR_FLG = 3;									//↓ポジションセット
			}
		}
		CSR_move(CSR_FLG, CSR_MOVE_OK_FLG);					//カーソル移動(戻り値指定,移動)
		SV_csr_set();										//設定値カーソル

		Lcd_line( 00, 13, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
		Lcd_line( 00, 14, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
	}

	CSR_MOVE_NON = 0;										//2014/03/14

	if(WINDOW_NO == 0) {
//		Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);		//全表示
	}
	else{
		Lcd_line( 00, 6, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 7, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 8, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 9, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 10, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 11, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
//		Lcd_line( 00, 12, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
	}
	if(WINDOW_NO == 12) {
		ADC_NEXTNAME_SET();		/* ＡＤＣ次型番号名称 */
		WIN_gamen_disp();		/* 再表示 */
		ADC_DISP_FLG = 0x0FF;					/* ＡＤＣウインドウ表示中 */
		ADC_CHG_LST1 = 0;
		ADC_CHG_LST2 = 0;
		ADC_CHG_LST2_2 = 0;
	}

}


/*
********************************************************************************
*  Module Name:		Key_sv_limt_chk(旧：MIN_MAX_CHK)
*  Function Name:	設定値の上下限チェック
*  Input	: 		設定値情報ﾃｰﾌﾞﾙの番号
*					ﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ
*
*  Return	: 		なし
*  Note		:		設定値情報ﾃｰﾌﾞﾙで指定された値のチェックを行う。
*
*  履 歴	:FIT)田端		ON:2002-05-31
********************************************************************************
*/
//2014/08/27	void	Key_sv_limt_chk(UNs t_no, UNl *wk_p)
//
//KOMA *wk_pは設定値
//Dst_p	は設定ﾃﾞｰﾀｱﾄﾞﾚｽ(wk_p)
//bf	は設定ﾃﾞｰﾀ(*wk_p)
//
//

UNs		Key_sv_limt_chk(UNs t_no, UNl *wk_p)
{
	UNl		wl0, wl1, bf, *Dst_p, *Src_p;
	UNl		kagen_mm, jyogen_mm;
	UNs		i , j, ww0, ww1;
//2016/02/24	UNl		*Dst_p_w, long_bf, *posn, *posb;
	UNl		*Dst_lp;
	UNs		*Dst_wp;

	UNs		*degn, *degb;
	S4b		ofs, dat;
	UNs		sv_ref;
	UNs		*spd;

	S2b		wk_S2b;				//2016/03/24

	sv_ref = 0;

	Dst_p = wk_p;
	bf = *wk_p;

	switch( SV_buff[t_no].SUB_NO ) {							//ｻﾌﾞﾙｰﾁﾝ番号への遷移
		default:
		case 00:				//ﾁｪｯｸなし
			break;

		case 01:				//0 ～ 9
			if( bf > 9 ) {
				*Dst_p = 9;
			}
			break;

		case 02:				//0 ～ 100
			if( bf > 100 ) {
				*Dst_p = 100;
			}
			break;

		case 03:				//90 ～ 270
			if( bf > 270 ) {
				*Dst_p = 270;
			}
			else if(bf < 90) {
				*Dst_p = 90;
			}
			break;

		case 04:				//0 ～ 300
			if( bf > 300 ) {
				*Dst_p = 300;
			}
			break;

		case 05:				//0 ～ 359
			if( bf > 359 ) {
				*Dst_p = 359;
			}
			break;

		case 06:				//0 ～ 99
		case 28:				//0 ～ 99
			if( bf > 99 ) {
				*Dst_p = 99;
			}
			break;

		case 07:				//270 ～ 359
			if( bf > 359 ) {
				*Dst_p = 359;
			}
			else if(bf < 270) {
				*Dst_p = 270;
			}
			break;

		case 8:					//上限データ(現位置＞上限＞下限)
			if( INI_POS_ERR_FLG != 0xff ) {					//イニシャル時ポジショナー設定値異常？
				if( bf >= SV_GENITI_A21 ){					//上限＜現位置
					*Dst_p = SV_UPDATA_A21;
				}
				else if( bf <= SV_DNDATA_A21 ) {			//上限＞下限
					*Dst_p = SV_UPDATA_A21;
				}
			}
			break;

		case 9:					//下限データ(上限＞下限，下限＞現位置－感度)
			if( INI_POS_ERR_FLG != 0xff ) {					//イニシャル時ポジショナー設定値異常？
				if( SV_GENITI_A21 >= SV_KANDO_A21 ) {
					wl0 = (SV_GENITI_A21 - SV_KANDO_A21);
					if( bf <= wl0) {							//下限＞現位置－感度
						*Dst_p = SV_DNDATA_A21;
					}
					else if(bf >= SV_UPDATA_A21) {				//下限＜上限
						*Dst_p = SV_DNDATA_A21;
					}
				}
				else{
					if( bf >= SV_UPDATA_A21) {					//下限＜上限
						*Dst_p = SV_DNDATA_A21;
					}
				}
			}
			break;

		case 10:				//最大歪データチェック
			if( bf > 1500 ) {				//１５００より上？
				*Dst_p = 2000;
			}
			else if(bf <= 200) {			//２００以下？
				*Dst_p = 200;
			}
			else if(bf <= 400) {			//４００以下？
				*Dst_p = 400;
			}
			else if(bf <= 800) {			//８００以下？
				*Dst_p = 800;
			}
			else {							//１５００以下？
				*Dst_p = 1500;
			}
			break;

		case 11:				//すべり量１　上下限チェック
//?			Src_p = E_SUBE1_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 12:				//すべり量2　上下限チェック
//?			Src_p = E_SUBE2_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 13:				//すべり量3　上下限チェック
//?			Src_p = E_SUBE3_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 14:				//すべり量4　上下限チェック
//?			Src_p = E_SUBE4_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 15:				//すべり量5　上下限チェック
//?			Src_p = E_SUBE5_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 16:				//すべり量6　上下限チェック
//?			Src_p = E_SUBE6_DN;					//上下限データポインタ
//			if( bf[1] == 00 ) {
//				if( bf[0] < *Src_p ) {
//					*Dst_p = *Src_p;
//				}
//				else if( bf[0] != *Src_p ) {
//					if( bf[0] > *Src_p+2 ) {
//						*Dst_p = *Src_p+2;
//					}
//				}
//			}
//			else {
//				*Dst_p++ = *Src_p+2;
//				*Dst_p = 00;
//			}
			break;

		case 17:				//0 ～ 511
			if( bf > 511 ) {
				*Dst_p = 511;
			}
			break;

		case 18:				//現位置チェック(現位置＞上限、現位置＜感度＋下限)
			if( INI_POS_ERR_FLG != 0xff ) {					//イニシャル時ポジショナー設定値異常？
				if( bf <= SV_UPDATA_A21 ) {
					*Dst_p = SV_GENITI_A21;
				}
				else if(bf > SV_UPDATA_A21 ) {
					wl0 = SV_KANDO_A21;					//感度
					wl0 += SV_DNDATA_A21;
					if( bf >= wl0 ){						//現位置＜感度＋下限
						*Dst_p = SV_GENITI_A21;
					}
				}
			}
			break;

		case 19:				//感度データ(感度＞現位置－下限)
			if( INI_POS_ERR_FLG != 0xff ) {					//イニシャル時ポジショナー設定値異常？
				if( SV_GENITI_A21 >= SV_DNDATA_A21 ) {
					wl0 =(SV_GENITI_A21 - SV_DNDATA_A21);
					if( bf <= wl0) {							//感度＞現位置－下限
						*Dst_p = SV_KANDO_A21;
					}
				}
			}
			break;

		case 20:				//設定値データ(上限≧設定値≧下限)
			if (SLDTUN_RNA_SEL != 0x5a) {
				if( INI_POS_ERR_FLG != 0xff ) {					//イニシャル時ポジショナー設定値異常？
					if( bf > SV_UPDATA_A21 ) {					//設定値≦上限
						Src_p = (UNl *)SV_buff[SV_TBL_POS_NOW].DATA_ADR;	//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
						*Dst_p = *Src_p;
					}
					else if( bf < SV_DNDATA_A21 ) {				//現位置≧下限
						Src_p = (UNl *)SV_buff[SV_TBL_POS_NOW].DATA_ADR;	//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
						*Dst_p = *Src_p;
					}
				}
			}
			else {												//2014/06/04
				/* ﾘﾆｱｽｹｰﾙによるｽﾗｲﾄﾞ調節 */
				if( SEQ_016_SV & BIT_6 ) {							//単位切替 mm/INCH 単位系(1:INCH)	2014/12/22
					bf = cnv_inch_mm(bf, 0);
					wl0 = 1;//小数点３桁設定
				}
				else {
					if (SV_POINT_A1 == 0) {//設定ﾃﾞｰﾀ小数点無し *1000 =>小数点３桁
						wl0 = 1000;
					}
					else if (SV_POINT_A1 == 1) {//設定ﾃﾞｰﾀ小数点1桁 *100 =>小数点３桁
						wl0 = 100;
					}
					else if (SV_POINT_A1 == 2) {//設定ﾃﾞｰﾀ小数点2桁 *10  =>小数点３桁
						wl0 = 10;
					}
					else {
						wl0 = 1;//小数点３桁設定
					}
				}

				//2014-08-11 koma if ( (bf * wl0) > SV_RNAPOS_MAXP ) {
				//2014-08-11 koma 	*Dst_p = SV_RNAPOS_MAXP / wl0;
				//2014-08-11 koma }
				//2014-08-11 koma if ( (bf * wl0) < SV_RNAPOS_MINP ) {
				//2014-08-11 koma 	*Dst_p = SV_RNAPOS_MINP / wl0;
				//2014-08-11 koma }

				//2014-08-11 生産、段取１、段取２の上下限をオフセット指令込みで行う
				//2014-08-18 SV0_RNAPOS_MAXO[19]-> SV0_DAIHAI_LNG2O ダイハイト上限[58]
				//2014-08-18 SV0_RNAPOS_MINO[20]-> SV0_DAIHAI_LNG1O ダイハイト下限[57]

				if ( (bf * wl0) > (SV0_DAIHAI_LNG2O*100) ) {//機械上限[Sno.19]0.001mm->ダイハイト上限[58]0.1mm*100
//2014/12/22					*Dst_p = (SV0_DAIHAI_LNG2O*100) / wl0;
					*Dst_p = cnv_mm_inch(SV0_DAIHAI_LNG2O*100, 0) / wl0;
				}
				if ( (bf * wl0) < (SV0_DAIHAI_LNG1O*100) ) {//機械下限[Sno.20]0.001mm->ダイハイト下限[57]0.1mm*100
//2014/12/22					*Dst_p = (SV0_DAIHAI_LNG1O*100) / wl0;
					*Dst_p = cnv_mm_inch(SV0_DAIHAI_LNG1O*100, 0) / wl0;
				}
				
			}
			break;

		case 21:				//オーバーロード（左）　ＭＡＸチェック
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ左右,ﾛｱﾘﾐｯﾄ左右,振幅の設定上限
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKAJ_A24 ) {		//最大荷重（左以下）
						*Dst_p = SV_MAXKAJ_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR049 ) {				//最大荷重（左以下）
					*Dst_p = GMN_PAR049;
				}
			}
			break;

		case 35:				//校正荷重  最大荷重（左）以下　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKAJ_A24 ) {		//最大荷重（左以下）
					*Dst_p = SV_MAXKAJ_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 22:				//オーバーロード（合計）　ＭＡＸチェック
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ合計,ﾛｱﾘﾐｯﾄ合計,振幅の設定上限
					if(GMN_PAR107){
						if(bf > GMN_PAR107){
							bf=GMN_PAR107;
							*Dst_p=bf;
						}
					}
				
					if( bf > SV_MAXKA2_A24 ) {		//最大荷重（合計以下）
						*Dst_p = SV_MAXKA2_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR050 ) {				//最大荷重（合計以下）
					*Dst_p = GMN_PAR050;
				}
			}
			break;

		case 36:				//校正荷重  最大荷重（合計）以下　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA2_A24 ) {		//最大荷重（合計以下）
					*Dst_p = SV_MAXKA2_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 23:				//オーバーロード（右）　ＭＡＸチェック
			if (SV_OVLD_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ左右,ﾛｱﾘﾐｯﾄ左右,振幅の設定上限
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA3_A24 ) {		//最大荷重（右以下）
						*Dst_p = SV_MAXKA3_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR049 ) {				//最大荷重（右以下）
					*Dst_p = GMN_PAR049;
				}
			}
			break;

		case 37:				//校正荷重  最大荷重（右）以下　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {		//最大荷重（右以下）
					*Dst_p = SV_MAXKA3_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 24:				//ロアーリミット（左）　ＭＡＸチェック
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ左右,ﾛｱﾘﾐｯﾄ左右,振幅の設定上限
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKAJ_A24 ) {			//最大荷重（左以下）
						*Dst_p = SV_MAXKAJ_A24;
					}
//2014/06/03					else if( bf > SV_OVERE1_A26 ) {	//オーバーロード（左以下）
////////////						*Dst_p = SV_OVERE1_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR049 ) {				//最大荷重（左以下）
					*Dst_p = GMN_PAR049;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE1_A27 ) {			//最小値オーバーロード（左以下）
					*Dst_p = SV_OVERE1_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE1_A28 ) {			//振幅オーバーロード（左以下）
					*Dst_p = SV_OVERE1_A28;
				}
			}
			else {
				if( bf > SV_OVERE1_A26 ) {			//最大値オーバーロード（左以下）
					*Dst_p = SV_OVERE1_A26;
				}
			}
			break;

		case 25:				//ロアーリミッタ（合計）　ＭＡＸチェック
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ合計,ﾛｱﾘﾐｯﾄ合計,振幅の設定上限
					if(GMN_PAR107){
						if(bf > GMN_PAR107){
							bf=GMN_PAR107;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA2_A24 ) {			//最大荷重（合計以下）
						*Dst_p = SV_MAXKA2_A24;
					}
//2014/06/03					else if( bf > SV_OVERE2_A26 ) {		//オーバーロード（合計以下）
////////////						*Dst_p = SV_OVERE2_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR050 ) {				//最大荷重（合計以下）
					*Dst_p = GMN_PAR050;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE2_A27 ) {			//最小値オーバーロード（合計以下）
					*Dst_p = SV_OVERE2_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE2_A28 ) {			//振幅オーバーロード（合計以下）
					*Dst_p = SV_OVERE2_A28;
				}
			}
			else {
				if( bf > SV_OVERE2_A26 ) {			//最大値オーバーロード（合計以下）
					*Dst_p = SV_OVERE2_A26;
				}
			}
			break;

		case 26:				//ロアーリミッタ（右）　ＭＡＸチェック
			if (SV_LWLM_SEL != 1) {										//2014/06/03
				/*「最大値」または「振幅」*/
				if( (bf & 0xffff0000) == 00 ) {
					//2019-04-20 koma ｵｰﾊﾞﾛｰﾄﾞ左右,ﾛｱﾘﾐｯﾄ左右,振幅の設定上限
					if(GMN_PAR106){
						if(bf > GMN_PAR106){
							bf=GMN_PAR106;
							*Dst_p=bf;
						}
					}
					if( bf > SV_MAXKA3_A24 ) {			//最大荷重（右以下）
						*Dst_p = SV_MAXKA3_A24;
					}
//2014/06/03					else if( bf > SV_OVERE3_A26 ) {		//オーバーロード（右以下）
////////////						*Dst_p = SV_OVERE3_A26;
////////////					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			else {
				/*「最小値」*/
				if( bf > GMN_PAR049 ) {				//最大荷重（右以下）
					*Dst_p = GMN_PAR049;
				}
			}

			if (SV_LWLM_SEL == 1) {
				if( bf > SV_OVERE3_A27 ) {			//最小値オーバーロード（右以下）
					*Dst_p = SV_OVERE3_A27;
				}
			}
			else if (SV_LWLM_SEL == 2) {
				if( bf > SV_OVERE3_A28 ) {			//振幅オーバーロード（右以下）
					*Dst_p = SV_OVERE3_A28;
				}
			}
			else {
				if( bf > SV_OVERE3_A26 ) {			//最大値オーバーロード（右以下）
					*Dst_p = SV_OVERE3_A26;
				}
			}
			break;

		case 27:				//0 ～ 330
			if( bf > 330 ) {
				*Dst_p = 330;
			}
			break;

		case 29:				//0 ～ 0xffff
			if( bf > 0xffff ) {
				*Dst_p = 0xffff;
			}
//V05j			if ( GAMEN_NO == 50 ) {			// V05i
//////				KJ_CHK_CNT8++;
//////			}
			break;

		case 30:				//仕様MAX速度以下
			if( bf >= SV_SYUMAX_A14 ) {							//仕様速度以下
				*Dst_p = SV_SYUMAX_A14;							//最高速度以下
			}
			break;

		case 31:				//0 ～ 600
			if( bf > 600 ) {
				*Dst_p = 600;
			}
			break;

		case 32:				//0 ～ 255
			if( bf > 255 ) {
				*Dst_p = 255;
			}
//V05j			if ( GAMEN_NO == 50 ) {			// V05i
//////				KJ_CHK_CNT8++;
//////			}
			break;

		case 33:				//1 ～ 2(スライド自動の位置ﾃﾞｰﾀ桁数)
//SIT-Sなし			if( SEQ_016_SV & BIT_6 ) {				//単位切替　INCH(1:有り)
//				*Dst_p = 3;
//			}
//			else {
//				if( bf > 2 ) {
//					*Dst_p = 2;
//				}
//				else if(bf == 0 ){
//					*Dst_p = 1;
//				}
//			}
			break;

		case 34:				//ﾁｪｯｸ無 現位置PV入力用
			PVGENNITI_FLG = 0xff;
			break;

		case 38:				//最高速度以下
			if( bf >= SV_MAXSPM_A14 ) {							//最高速度以下
				*Dst_p = SV_MAXSPM_A14;							//最高速度以下
			}
			break;

		case 39:				//+-設定
			
			break;

		case 40:				//0 ～ 65535 / 0 ～ 32767
			i = CSR_FLG_CNT;									//カーソル位置読込
			if( i == 0 ) {
				if( bf > 65535 ) {
					*Dst_p = 65535;
				}
			}
			else {
				i --;
				j = 1;
				j <<= i;
				if( SV_CILMAI_A50 & j ) {						//ﾏｲﾅｽ有無フラグ
					if( bf > 0x7fff ) {
						*Dst_p = 0x7fff;
					}
				}
				else {
					if( bf > 65535 ) {
						*Dst_p = 65535;
					}
				}
			}
			break;

		case 41:				//0 ～ 5
			if( bf > 5 ) {
				*Dst_p = 5;
			}
			break;

		case 42: /*V01l_a*/				//ﾀﾞｲｸｯｼｮﾝ自動左上限
			if(bf != SV_UPDATA_A47) {			//上限≧設定
				if(bf > SV_UPDATA_A47) {		//上限≧設定
					*Dst_p = SV_UPDATA_A47;
				}
				else if(bf < SV_DNDATA_A47) {		//設定≧下限
					*Dst_p = SV_DNDATA_A47;
				}
			}
			break;

		case 43: /*V01l_a*/				//ﾀﾞｲｸｯｼｮﾝ自動右上限
			if(bf != SV_UPDATA_A48) {			//上限≧設定
				if(bf > SV_UPDATA_A48) {		//上限≧設定
					*Dst_p = SV_UPDATA_A48;
				}
				else if(bf < SV_DNDATA_A48) {		//設定≧下限
					*Dst_p = SV_DNDATA_A48;
				}
			}
			break;

		case 44:				//ﾊﾞﾗﾝｻ上限(上限≧設定値≧下限)
			if(bf != SV_BARAUP_A49) {			//上限≧設定
				if(bf > SV_BARAUP_A49) {		//上限≧設定
					*Dst_p = SV_BARAUP_A49;
				}
				else if(bf < SV_BARADN_A49) {		//設定≧下限
					*Dst_p = SV_BARADN_A49;
				}
			}
			break;

		case 45: /*V01l_a*/		//ﾀﾞｲｸｯｼｮﾝ自動調整左
			if(bf != SV_DAILUP_A49) {			//上限≧設定
				if(bf > SV_DAILUP_A49) {		//上限≧設定
					*Dst_p = SV_DAILUP_A49;
				}
				else if(bf < SV_DAILDN_A49) {		//設定≧下限
					*Dst_p = SV_DAILDN_A49;
				}
			}
			break;

		case 46: /*V01l_a*/		//ﾀﾞｲｸｯｼｮﾝ自動調整右
			if(bf != SV_DAIRUP_A49) {			//上限≧設定
				if(bf > SV_DAIRUP_A49) {		//上限≧設定
					*Dst_p = SV_DAIRUP_A49;
				}
				else if(bf < SV_DAIRDN_A49) {		//設定≧下限
					*Dst_p = SV_DAIRDN_A49;
				}
			}
			break;

		case 47:				//1 ～ 100 又は、1 ～ 10	(型ﾃﾞｰﾀ)
			if( MLD_100_FLG == 0xaa ) {
				if(bf > 100){
					if (SEQ_PAR_151 & cBIT3) {				//サンプル型有効？		2014/04/17
						if ( (bf < 201) || (bf > 220) ) {
							*Dst_p = 100;
						}
					}
					else {
						*Dst_p = 100;
					}
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else if ( MLD_100_FLG == 0xbb ) {		//V06n
				if(bf > 200){
					if (SEQ_PAR_151 & cBIT3) {				//サンプル型有効？		2014/04/17
						if (bf > 220) {
							*Dst_p = 200;
						}
					}
					else {
						*Dst_p = 200;
					}
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else {
				if(bf > 10){
					if (SEQ_PAR_151 & cBIT3) {				//サンプル型有効？		2014/04/17
						if ( (bf < 201) || (bf > 220) ) {
							*Dst_p = 10;
						}
					}
					else {
						*Dst_p = 10;
					}
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			break;

		case 48:				//型ﾃﾞｰﾀﾀｲﾄﾙ
			if( MLD_100_FLG == 0xaa ) {
				if(bf > 100){
					*Dst_p = 100;
				}
			}
			else if ( MLD_100_FLG == 0xbb ) {		//2016/04/22
				if(bf > 200){
					*Dst_p = 200;
				}
			}
			else {
				if(bf > 10){
					*Dst_p = 10;
				}
			}
			break;

		case 49:				//0 ～ 599->999
/* V00p */
			if( bf > /*599*/ 999 ) {
				*Dst_p = /*599*/ 999;
			}
			break;

		case 50:				//1 ～ 6
			if( (bf & 0xffff0000) != 00 ) {
				*Dst_p = SV_UPDANO_MAX;
			}
			else {
				if( bf == 0 ) {
					*Dst_p = 1;
				}
				else if(bf > SV_UPDANO_MAX) {
					*Dst_p = SV_UPDANO_MAX;
				}
			}
			break;

		case 51:				//1 ～ 5 (段数)
#if (mot100_test == 1)								//2015/10/21
			wl0 = 10;
			if (GMN_PAR085) {						//ﾓｰｼｮﾝ最大段数
				wl0 = GMN_PAR085;
			}
#else
			wl0 = 5;
			if (SEQ_024_SV & BIT_3) {				//10段仕様有無		/* V01d */
				wl0 = 10;
			}
#endif
			if( bf > wl0 ) {
				*Dst_p = wl0;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
#if (mot100_test == 1)
#else
			if ((GAMEN_NO == 6) && (*Dst_p <= 5)) {		/*V01e*/
				disp_stg_sel = E_sstg_mmon;				//生産[モーションモニタ6～10]へ
				GAMEN_NO = 3;
				GAMEN_disp();							//画面表示
			}
			if ((GAMEN_NO == 30) && (*Dst_p <= 5)) {	/*V01e*/
				disp_stg_sel = E_dstg_mset;				//データ設定[モーションモニタ6～10]へ
				GAMEN_NO = 28;
				GAMEN_disp();							//画面表示
			}
#endif
			SV0_MOT_FIX = 0;							//一定速度ブラグクリア			2014/10/09
			break;

		case 52:				//0 ～ 1000
			if( bf > 1000 ) {
				*Dst_p = 1000;
			}
			break;

		case 53:				//0 ～ 工程数 + 最終工程（工程数ﾁｪｯｸ）
			if( bf > (SV_DANSUU_SRV + 1) ) {
				*Dst_p = SV_DANSUU_SRV + 1;
			}
			else if( bf == 0 ){	//段＝00？
				dansuu_zero_set();				//ｶﾑの段 00設定
			}
			REP_CAM_CLR(bf);
			break;

		case 54:				//0 ～ 反転設定不可範囲　(設定値を×10倍)
			bf *= 10;									//×10倍
			if( bf > SV_DNAREA_JUDG ) {//反転、ふりこ共通
				bf = SV_DNAREA_JUDG;
			}
			if( SV_buff[t_no].GRP_NO == 85 ) {				//上限角の設定		V06k (INS)
				if( SEQ_050_SV & BIT_1 ) {					//反転時の上限角の最大値リミット		V05 (INS)
					if( bf > GMN_PAR015 ) {//最大
						bf = GMN_PAR015;
					}

					//2014-08-11 koma 反転時の上限の最小値リミット追加 ｻｰﾎﾞﾊﾟﾗ40上死点範囲
					if(bf<SV_UPAREA_JUDG+10){	//最小+1.0度
						bf=SV_UPAREA_JUDG+10;	//最小+1.0度
					}

				}
				else if ( SEQ_050_SV & BIT_2 ) {			//振子の上限角の最大/最小値リミット		V06f (INS)
					if( bf > GMN_PAR016 ) {
						bf = GMN_PAR016;					//最大リミット
					}
					if( bf < GMN_PAR019 ) {
						bf = GMN_PAR019;					//最小リミット
					}
				}
			}
			*Dst_p = bf;
			break;

		case 55:				//0 ～ 359　(設定値を×10倍)
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//×10倍
			*Dst_p = bf;
			break;

		case 56:				//上限位置
			wl0 = SV_RNA_STLORK;						//ストローク設定(小数点 3桁)
//2014/12/17
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
////
////			if( bf > wl0 ) {
////				*Dst_p = wl0;
////				bf = wl0;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//ストローク設定mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}


			if( SEQ_050_SV & BIT_1 ) {					//反転時の上限位置の最大値		V05 (INS)
				wl0 = DigRnaChange1(GMN_PAR015);		//角度→mm変換
				wl0 = wl0-SV_NEG_OFS_LNG;				//2014-08-11 koma add不具合
				if( bf < wl0 ) {
//2014/12/17
////					*Dst_p = wl0;
////					bf = wl0;
					bf = wl0;								//ストローク設定mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}

				//2014-08-11 koma 反転時の上限の最小値リミット追加 ｻｰﾎﾞﾊﾟﾗ40上死点範囲
				wl0 = DigRnaChange1(SV_UPAREA_JUDG+10);//最小+1.0度
				wl0 = wl0-SV_NEG_OFS_LNG;				//
				if( bf > wl0 ) {
//2014/12/17
////					*Dst_p = wl0;
////					bf = wl0;
					bf = wl0;								//ストローク設定mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}
			}
			else if ( SEQ_050_SV & BIT_2 ) {			//振子の上限位置		V06f (INS)
				wl0 = DigRnaChange1(GMN_PAR016);		//角度→mm変換
				if( bf < wl0 ) {
//2014/12/17
////					*Dst_p = wl0;						//最小リミット
////					bf = wl0;
					bf = wl0;								//ストローク設定mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}
				wl0 = DigRnaChange1(GMN_PAR019);		//角度→mm変換
				if( bf > wl0 ) {
//2014/12/17
////					*Dst_p = wl0;						//最大リミット
////					bf = wl0;
					bf = wl0;								//ストローク設定mm
					*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
				}
			}

			break;

		case 57:				//機械下限 ～ 機械上限
			wl0 = SV_RNAPOS_MINP;						//機械下限(小数点 3桁)
			wl1 = SV_RNAPOS_MAXP;						//機械上限(小数点 3桁)
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
					wl1 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl1 ) {
				*Dst_p = wl1;							//機械上限
			}
			else if(bf < wl0) {							//機械下限
				*Dst_p = wl0;
			}
			break;

		case 58:				//ﾀﾞｲﾊｲﾄ補正比較値(小) ～ ﾀﾞｲﾊｲﾄ補正比較値(中)
//			wl0 = SV_DAIHAI_LNG1 * 1000;				//ﾀﾞｲﾊｲﾄ補正比較値(小) 小数点 0桁 -> 3桁
//			wl1 = SV_DAIHAI_LNG2 * 1000;				//ﾀﾞｲﾊｲﾄ補正比較値(中) 小数点 0桁 -> 3桁
			wl0 = SV_DAIHAI_LNG1 * 100;					//ﾀﾞｲﾊｲﾄ補正比較値(小) 小数点 1桁 -> 3桁
			wl1 = SV_DAIHAI_LNG2 * 100;					//ﾀﾞｲﾊｲﾄ補正比較値(中) 小数点 1桁 -> 3桁
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if(	SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
					wl1 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl1 ) {
				*Dst_p = wl1;							//ﾀﾞｲﾊｲﾄ補正比較値(中)
			}
			else if(bf < wl0) {
				*Dst_p = wl0;							//ﾀﾞｲﾊｲﾄ補正比較値(小)
			}
			break;

		case 60:				//0 ～ 1
			if( bf > 1 ) {
				*Dst_p = 1;
			}
			break;

		case 61:				//0 ～ 2->3				//2009/11/04 V05p
			if( bf > 3 ) {
				*Dst_p = 3;
			}
			break;

		case 62:				//1 ～ 32767
			if( bf > 32767 ) {
				*Dst_p = 32767;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 63:				//1 ～ 2000000
			if( bf > 2000000 ) {
				*Dst_p = 2000000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 64:				//0 ～ 1000000
			if( bf > 1000000 ) {
				*Dst_p = 1000000;
			}
			break;

		case 65:				//0 ～ 10000
			if( bf > 10000 ) {
				*Dst_p = 10000;
			}
			break;

		case 66:				//1 ～ 10000
			if( bf > 10000 ) {
				*Dst_p = 10000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 67:				//0 ～ 32767
			if( bf > 32767 ) {
				*Dst_p = 32767;
			}
			break;

		case 68:				//1 ～ 3599
			if( bf > 3599 ) {
				*Dst_p = 3599;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 69:				//デバッグアドレス  shima
//V01l_e			*Dst_p &= 0xfffe;
			*Dst_p &= 0xFFFFE;
			break;

		/* V00m */
		case 70:				//1～1000
			if( bf > 1000 ) {
				*Dst_p = 1000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}

			if ( ((SEQ_024_SV & BIT_5) == BIT_5) && (CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 99))		// V01n(INS)
			{																						//ﾓｰｼｮﾝ3段目
				j = SEQ_PAR_119;
				if (j & 0x07FF)
				{
					degn = &GMN_PAR024;
					for ( i=11 ; i>0 ; i--, j=j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww0 = ww1 = *degn;
							i--;
							j=j>>1;
							degn++;
							break;
						}
					}
					for ( ; i>0 ; i--, j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww1 = *degn;
							break;
						}
					}
					if (ww1 <= *Dst_p)
					{
						*Dst_p = ww1;
					}
					else
					{
						*Dst_p = ww0;
					}
				}
			}

//2015/07/10	モーションインターロック仕様
			bf = *Dst_p;
			*Dst_p = motion_spd_limit1(bf, t_no);					//最終行程（戻り行程の前）の速度下限ﾁｪｯｸ

			break;

		/* V00m */
		case 71:				//ﾊﾞｯｸｱｯﾌﾟ原点ﾃﾞｰﾀABS設定(上下限ﾁｪｯｸ無し)によるリニアセンサ基準位置パルス変更
			if (SV_RNAORG_SIN) {
				PV_RNAORG_PLS1 = *Dst_p * -1;
			}
			else {
				PV_RNAORG_PLS1 = *Dst_p;
			}
			break;

		/* V00r */
		case 72:				//補正値の下限ﾁｪｯｸ
//V01m			if(bf < GMN_PAR001) {
//				*Dst_p = GMN_PAR001;
//			}
			if (SEQ_050_SV & BIT_9)								//荷重補正あり？
			{
				if(bf < GMN_PAR010) {
					*Dst_p = GMN_PAR010;			//荷重補正ﾘﾐｯﾀ
				}
				if(bf > GMN_PAR081) {				//2014/09/12
					bf = GMN_PAR081;
					*Dst_p = GMN_PAR081;			//荷重補正上限ﾘﾐｯﾀ
				}
			}
			else
			{
				bf = cnv_uinch_um(bf);				//uinch -> um			2014/12/23
				if(bf < GMN_PAR001) {
					bf = GMN_PAR001;
//2014/12/23					*Dst_p = GMN_PAR001;			//下限補正下限ﾘﾐｯﾀ
					*Dst_p = cnv_um_uinch(GMN_PAR001);			//下限補正下限ﾘﾐｯﾀ
				}
				if(bf > GMN_PAR080) {				//2014/09/11
					bf = GMN_PAR080;
//2014/12/23					*Dst_p = GMN_PAR080;			//下限補正上限ﾘﾐｯﾀ
					*Dst_p = cnv_um_uinch(GMN_PAR080);			//下限補正上限ﾘﾐｯﾀ
				}
			}
			break;

		/* V01  */
		case 73:				//段取速度の上限ﾁｪｯｸ
			if(bf > GMN_PAR002) {
				bf = GMN_PAR002;
				*Dst_p = bf;
			}
			if(bf < GMN_PAR044) {	//下限ﾁｪｯｸ		2013/02/04 V06o
				bf = GMN_PAR044;
				*Dst_p = bf;
			}
			break;

		/* V01d */
		case 74:				//ﾓｰｼｮﾝ1～10角度の上限ﾁｪｯｸ
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//×10倍

			bf = motion_dig_limit1(bf, t_no);			//回転ﾓｰｼｮﾝ位置上下限ﾁｪｯｸ  V01j(INS)
			bf = motion_dig_limit2(bf, t_no);			//回転ﾓｰｼｮﾝ角度上下限ﾁｪｯｸ（前段角度より大きいかﾁｪｯｸ）V01j(INS)

			bf = motion_dig_limit0(bf, t_no);			//回転／連寸一工程の時のﾓｰｼｮﾝ角度上下限ﾁｪｯｸ
			*Dst_p = bf;
			break;

		/* V01d */
		case 75:				//ﾓｰｼｮﾝ1～10位置の上限ﾁｪｯｸ
			wl0 = SV_RNA_STLORK;						//ストローク設定(小数点 3桁)
//2014/12/17
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
////
////			if( bf > wl0 ) {
////				*Dst_p = wl0;							//ストローク設定
////			}

			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//ストローク設定mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}


			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit1(wl0, t_no);		//回転ﾓｰｼｮﾝ位置上下限ﾁｪｯｸ  V01j(INS)
			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit2(wl0, t_no);		//回転ﾓｰｼｮﾝ位置上下限ﾁｪｯｸ（前段位置より大きいかﾁｪｯｸ） V01j(INS)

			wl0 = *Dst_p;
			*Dst_p = motion_pos_limit0(wl0, t_no);		//回転／連寸一工程の時のﾓｰｼｮﾝ位置上下限ﾁｪｯｸ

			break;

		/* V01i */
		case 76:				//待機点角度の上下限ﾁｪｯｸ
			bf *= 10;
			*Dst_p = bf;								//V01n ﾊﾞｸﾞ修正
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*下限*/ > GMN_PAR005/*上限*/) {
					/* ex : 270(下限)～90(上限) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(下限)～90(上限) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (SEQ_PAR_201 & BIT_4) {
					SV_TAIKIKAKU_SRV = *Dst_p;
					SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

					if(SEQ_050_SV & BIT_1) {		//反転　？
						SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
					}
					SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
				break;

		/* V01i */
		case 77:				//待機点角度の上下限ﾁｪｯｸ
			bf *= 10;
			*Dst_p = bf;								//V01n ﾊﾞｸﾞ修正
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*下限*/ > GMN_PAR005/*上限*/) {
					/* ex : 270(下限)～90(上限) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(下限)～90(上限) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (CB_SYS_PARAM279 != 1) {							// 待機点２無効				V06m	2012/09/24
					if (SEQ_PAR_201 & BIT_5) {
						SV_TAIKIKAKU_SRV = *Dst_p;
						SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

						if(SEQ_050_SV & BIT_1) {		//反転　？
							SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
						}
						SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)
					}
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
			break;

		/* V01i */
		case 78:				//待機点角度の上下限ﾁｪｯｸ
			bf *= 10;
			*Dst_p = bf;								//V01n ﾊﾞｸﾞ修正
			if (CB_SYS_PARAM045 == 1) {
				if(GMN_PAR004/*下限*/ > GMN_PAR005/*上限*/) {
					/* ex : 270(下限)～90(上限) */
					if( ((GMN_PAR004 <= bf) && (bf < 3600)) || ((0 <= bf) && (bf <= GMN_PAR005)) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				else {
					/* ex : 10(下限)～90(上限) */
					if( (GMN_PAR004 <= bf) && (bf <= GMN_PAR005) ) { }
					else {
						bf = SV_UPAREA_DIG1;
					}
				}
				*Dst_p = bf;

				if (SEQ_PAR_201 & BIT_6) {
					SV_TAIKIKAKU_SRV = *Dst_p;
					SV_TAIKIPOS_SRV = DigRnaChange1(SV_TAIKIKAKU_SRV);			//角度→mm変換

					if(SEQ_050_SV & BIT_1) {		//反転　？
						SV_TAIKIPOS_SRV = SV_TAIKIPOS_SRV - SV_NEG_OFS_LNG;
					}
					SV_TAIKIPOS_SRV	= cnv_mm_inch(SV_TAIKIPOS_SRV, 0);			//単位切替(mm→mm/INCH)
				}
			}
			else {
				if( bf > 3599 ) {
					bf = 3599;
					*Dst_p = bf;
				}
			}
			break;

		/* V01k */
		case 79:				//目標荷重設定上下限ﾁｪｯｸ　（V01mで未使用にした。）
//V01m			if(SV_MAXKA2_A24 < bf)				//上限（最大荷重）
//			{
//				*Dst_p = SV_MAXKA2_A24;
//			}
//			if(GMN_PAR009 > bf)					//下限（パラメータ）
///			{
//				*Dst_p = GMN_PAR009;
//			}
			break;

		case 80: /* V01l_c */			//下限目標／荷重目標　設定
			if (SEQ_050_SV & BIT_9) {					//荷重補正あり？
				ww0 = kajyu_chk( Dst_p, bf );
			}
			else {
				ww0 = kagen_chk( Dst_p, bf );
			}
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// 変更大きすぎず小さすぎず
			}
			SVSW_CHG_FLG |= 0x0008;				//格納ﾌﾗｸﾞ
			break;

		case 81: /* V01n */			//ﾓｰｼｮﾝ3段目速度設定
			if ( ((SEQ_024_SV & BIT_5) == BIT_5) && (CSR_buff[CSR_TBL_POS_NOW].DATA_NO == 99))		// V01n(INS)
			{																						//ﾓｰｼｮﾝ3段目
				j = SEQ_PAR_119 >> 12;
				if (j & 0x000F)
				{
					degn = &GMN_PAR035;
					for ( i=4 ; i>0 ; i--, j=j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww0 = ww1 = *degn;
							i--;
							j=j>>1;
							degn++;
							break;
						}
					}
					for ( ; i>0 ; i--, j=j>>1, degn++)
					{
						if (j & BIT_0)
						{
							ww1 = *degn;
							break;
						}
					}
					if (ww1 <= *Dst_p)
					{
						*Dst_p = ww1;
					}
					else
					{
						*Dst_p = ww0;
					}
				}
			}
			break;

		case 82:				//0 ～ 15
			if( bf > 15 ) {
				*Dst_p = 15;
			}
			break;

		case 83:				//1 ～ 100		//V01w(INS)
			if( bf > 100 ) {
				*Dst_p = 100;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 84:				//下限目標ﾁｪｯｸ		//V01w(INS)
			ww0 = kagen_chk( Dst_p, bf );
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// 変更大きすぎず小さすぎず
			}
			SVSW_CHG_FLG |= 0x0008;				//格納ﾌﾗｸﾞ
			break;

		case 85:				//荷重目標ﾁｪｯｸ		//V01w(INS)
			ww0 = kajyu_chk( Dst_p, bf );
			if (ww0 != 0) {
				SEQ_050_SV |= BIT_10;
			}
			else {
				SEQ_050_SV &= ~BIT_10;							// 変更大きすぎず小さすぎず
			}
			SVSW_CHG_FLG |= 0x0008;				//格納ﾌﾗｸﾞ
			break;

		case 86:				//下限補正の下限ﾁｪｯｸ		//V01w(INS)
			bf = cnv_uinch_um(bf);				//uinch -> um			2014/12/23
			if(bf < GMN_PAR001) {				//umで比較
				bf = GMN_PAR001;
//2014/12/23				*Dst_p = GMN_PAR001;			//下限補正下限ﾘﾐｯﾀ
				*Dst_p = cnv_um_uinch(GMN_PAR001);			//下限補正下限ﾘﾐｯﾀ
			}
			if(bf > GMN_PAR080) {				//2014/09/11
				bf = GMN_PAR080;
//2014/12/23				*Dst_p = GMN_PAR080;			//下限補正上限ﾘﾐｯﾀ
				*Dst_p = cnv_um_uinch(GMN_PAR080);			//下限補正上限ﾘﾐｯﾀ
			}
			break;

		case 87:				//荷重補正の下限ﾁｪｯｸ		//V01w(INS)
			if(bf < GMN_PAR010) {
				*Dst_p = GMN_PAR010;			//荷重補正ﾘﾐｯﾀ
			}
			if(bf > GMN_PAR081) {				//2014/09/12
				bf = GMN_PAR081;
				*Dst_p = GMN_PAR081;			//荷重補正上限ﾘﾐｯﾀ
			}
			break;

		/* COP2 */
		case 88:				//0 ～ 180
			if( bf > 359999 ) {
				*Dst_p = 359999;
			}
			break;

		/* COP2 */
		case 89:				//ﾊﾞｯｸｱｯﾌﾟ原点ﾃﾞｰﾀABS設定(上下限ﾁｪｯｸ無し)によるリニアセンサ基準位置パルス変更
			if (SV_RNAORG_SIN1) {
				PV_BAKORG_PLS1 = *Dst_p * -1;
			}
			else {
				PV_BAKORG_PLS1 = *Dst_p;
			}
			break;

		/* COP2 */
		case 90:				//ﾊﾞｯｸｱｯﾌﾟ原点ﾃﾞｰﾀABS設定(上下限ﾁｪｯｸ無し)によるリニアセンサ基準位置パルス変更
			if (SV_RNAORG_SIN2) {
				PV_BAKORG_PLS2 = *Dst_p * -1;
			}
			else {
				PV_BAKORG_PLS2 = *Dst_p;
			}
			break;

		case 91:				//1 ～ 5000		//V01z(INS)
			if( bf > 5000 ) {
				*Dst_p = 5000;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 92:				//0 ～ 5000		//V01z(INS)
			if( bf > 5000 ) {
				*Dst_p = 5000;
			}
			break;

		case 96:				//ブレーキ角度	//V05n(INS)
			if (GMN_PAR017 == 0) {
				if( bf > 359 ) {
					bf = 359;
				}
			}
			else {
				if( bf > GMN_PAR017 ) {
					bf = GMN_PAR017;
				}
			}
			bf *= 10;	//×10倍
			*Dst_p = bf;
			break;

		case 97:				//ブレーキタイム	//V05n(INS)
			if (GMN_PAR018 == 0) {
				if( bf > 1000 ) {
					*Dst_p = 1000;
				}
			}
			else {
				if( bf > GMN_PAR018 ) {
					*Dst_p = GMN_PAR018;
				}
			}
			break;

		case 98:				//波形スライド位置スケール最大	//V05o(INS)
//2014-08-11 koma			wl0 = SV_RNAPOS_MAXP;						//機械上限(小数点 3桁)
			wl0 = SV0_RNAPOS_MAXO;						//機械上限(小数点 3桁)	mm
			wl1 = SV_WAVE_SCL1D;						//サンプリング波形のｽｹｰﾙ下限	mm/inch

			if( GAMEN_NO == 10 ) {						//トレンド波形画面							2015/05/12
				wl1 = SV_WAVE_SCL3D;					//トレンド波形のｽｹｰﾙ下限	mm/inch
			}

//2014/12/18
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
////			if( bf > wl0 ) {
////				*Dst_p = wl0;							//機械上限
////			}
////			else if( bf < wl1 ) {
////				*Dst_p = wl1;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {							//上限ﾁｪｯｸ（mmで比較）
				bf = wl0;
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			if( *Dst_p < wl1 ) {						//下限ﾁｪｯｸ（mm/inchで比較）
				*Dst_p = wl1;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 99:				//波形スライド位置スケール最小	//V05o(INS)
//2014-08-11 KOMA			wl0 = SV_RNAPOS_MINP;		//機械上限(小数点 3桁)
			wl0 = SV0_RNAPOS_MINO;						//ｽｹｰﾙ下限 koma
			wl1 = SV_WAVE_SCL1U;						//サンプリング波形のｽｹｰﾙ上限

			if( GAMEN_NO == 10 ) {						//トレンド波形画面							2015/05/12
				wl1 = SV_WAVE_SCL3U;					//トレンド波形のｽｹｰﾙ上限	mm/inch
			}

//2014/12/18
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
////			if( bf < wl0 ) {
////				*Dst_p = wl0;							//機械下限
////			}
////			else if( bf > wl1 ) {
////				*Dst_p = wl1;
////			}

			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf < wl0 ) {							//下限ﾁｪｯｸ（mmで比較）
				bf = wl0;
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			if( *Dst_p > wl1 ) {						//上限ﾁｪｯｸ（mm/inchで比較）
				*Dst_p = wl1;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 100:				//波形荷重スケール最大			//V05o(INS)
//2015/05/15
////			if( (short)bf > (short)SV_MAXKA2_A24 ) {			//2014/03/14 符号有りへ
////				*Dst_p = SV_MAXKA2_A24;
////			}
////			else if( (short)bf <= (short)SV_WAVE_SCL2D ) {
////				*Dst_p = (short)SV_WAVE_SCL2D + 1;
////			}
			if( (long)bf > (short)SV_MAXKA2_A24 ) {
				bf = SV_MAXKA2_A24;
				*Dst_p = bf;
			}
			else if( (long)bf <= (short)SV_WAVE_SCL2D ) {
				bf = (short)SV_WAVE_SCL2D + 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 101:				//波形荷重スケール最小			//V05o(INS)
//2015/05/15
////			if( (short)bf >= (short)SV_WAVE_SCL2U ) {					//2014/03/14 符号有りへ
////				*Dst_p = (short)SV_WAVE_SCL2U - 1;
////			}
			if( (long)bf < -32767 ) {
				bf = -32767;
				*Dst_p = bf;
			}
			if( (long)bf >= (short)SV_WAVE_SCL2U ) {
				bf = (short)SV_WAVE_SCL2U - 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 102:				//0 ～ 9
			if( bf > 9 ) {
				*Dst_p = 9;
			}
			WAVE_TRND_DTP[1] = 0;				//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 103:				//1 ～ 30
			if( bf > 30 ) {
				*Dst_p = 30;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 104:				//ｽﾗｲﾄﾞ上限検出位置		//V05o(INS)
			wl0 = SV_DAIHAI_LNG2*100;					//ﾀﾞｲﾊｲﾄ上限(小数点 1桁)
			wl1 = SV_TRDCSR_RNAD;						//ｽﾗｲﾄﾞ下限検出
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

//2014/12/22
////			if( bf > wl0 ) {								//mmで比較
////				*Dst_p = wl0;							//ﾀﾞｲﾊｲﾄ上限
////			}
////			else if( bf < wl1 ) {
////				*Dst_p = wl1;
////			}
			if( bf > wl0 ) {								//mmで比較
				bf = wl0;
				*Dst_p = cnv_mm_inch(wl0,0);				//ﾀﾞｲﾊｲﾄ上限
			}
			if( *Dst_p < wl1 ) {							//mm/inchで比較
				*Dst_p = wl1;
			}

			break;

		case 105:				//ｽﾗｲﾄﾞ下限検出位置		//V05o(INS)
			wl0 = SV_DAIHAI_LNG1*100;					//ﾀﾞｲﾊｲﾄ下限(小数点 1桁)
			wl1 = SV_TRDCSR_RNAU;						//ｽﾗｲﾄﾞ上限検出
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

//2014/12/22
////			if( bf < wl0 ) {
////				*Dst_p = wl0;							//ﾀﾞｲﾊｲﾄ下限
////			}
////			else if( bf > wl1 ) {
////				*Dst_p = wl1;
////			}
			if( bf < wl0 ) {							//mmで比較
				bf = wl0;
				*Dst_p = cnv_mm_inch(wl0,0);			//ﾀﾞｲﾊｲﾄ下限
			}
			if( *Dst_p > wl1 ) {						//mm/inchで比較
				*Dst_p = wl1;
			}

			break;

		case 106:				//0 ～ 500
			if( bf > 500 ) {
				*Dst_p = 500;
			}
			break;

		case 107:				//1 ～ 999		V05r
			if( bf > 999 ) {
				*Dst_p = 999;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 108:				//制動性能試験インターバルタイマ	V05r
			if( bf > GMN_PAR039 ) {
				*Dst_p = GMN_PAR039;
			}
			break;

		case 109:				//外部タイマ	V05r
			//2020-01-30 A01sｼｰｹﾝｽでの外部ﾀｲﾏ上限切替 GMN_PAR111追加 <=>GMN_PAR041
			if(SEQ_PAR_154&BIT_0){
				if( bf > GMN_PAR111 ) {
					*Dst_p = GMN_PAR111;
				}
			}else{
				if( bf > GMN_PAR041 ) {
					*Dst_p = GMN_PAR041;
				}
			}

			break;

		case 110:				//電力モニタ単位時間	V06
			if( bf > 30 ) {
				bf = 30;
				*Dst_p = bf;
			}
			else if( bf < 5 ){
				bf = 5;
				*Dst_p = bf;
			}
			ww0 = bf % 5;
			if ( ww0 != 0 ){
				bf = (bf / 5) * 5;
				*Dst_p = bf;
			}

			break;

		case 111:				//0 ～ 65535
			if( bf > 65535 ) {
				*Dst_p = 65535;
			}
			break;

		case 112:				//ｻﾝﾌﾟﾘﾝｸﾞ、ﾄﾚﾝﾄﾞの電力上下限		//V06b
			if( (long)bf <= (long)SV_WAVE_SCL5D ) {					//符号有りへ		2014/03/14
				bf = (long)SV_WAVE_SCL5D + 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 113:				//ﾄﾀｰﾙｶｳﾝﾀ修正		//V06b
			PV_TOTLC1_B3 = bf;
			break;

		case 114:				//ﾛｯﾄｶｳﾝﾀ1修正		//V06b
			if( SEQ_PAR_107 & BIT_6 ){						//ﾛｯﾄｶｳﾝﾀ減算式？
				PV_LOTCT1_B4 = (SV_PUR1SV_B4 - bf);
			}
			else{
				PV_LOTCT1_B4 = bf;
			}
			break;

		case 115:				//ﾛｯﾄｶｳﾝﾀ2修正		//V06b
			if( SEQ_PAR_107 & BIT_6 ){						//ﾛｯﾄｶｳﾝﾀ減算式？
				PV_LOTCT2_B41 = (SV_PUR2SV_B41 - bf);
			}
			else{
				PV_LOTCT2_B41 = bf;
			}
			break;

		case 116:				//言語設定			//V06n
			if( bf > 3 ) {
				bf = 3;
				*Dst_p = bf;
			}
			else if( bf < 1 ){
				bf = 1;
				*Dst_p = bf;
			}
			break;

		case 117:				//反転ﾓｰﾄﾞP設定上限			//V06n
			if( bf > GMN_PAR042 ) {
				bf = GMN_PAR042;
				*Dst_p = bf;
			}
			break;

		case 118:				//反転ﾓｰﾄﾞS設定上限			//V06n
			if( bf > GMN_PAR043 ) {
				bf = GMN_PAR043;
				*Dst_p = bf;
			}
			break;

		case 119:				//機械下限					//V06n
			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//小数点3桁へ
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;

			if (SEQ_PAR_113 & cBIT10) {			//＋オフセット
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//－オフセット
				dat -= ofs;
				if (dat < 1000) {
					dat = 1000;
				}
			}
			SV0_RNAPOS_MINO = dat;		//機械下限(制御値)
			break;

		case 120:				//機械上限					//V06n
			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//小数点3桁へ
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;

			if (SEQ_PAR_113 & cBIT10) {			//＋オフセット
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//－オフセット
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_RNAPOS_MAXO = dat;		//機械上限(制御値)
			break;

		case 121:				//ダイハイト下限			//V06n
			if( bf > 32767 ) {
				bf = 32767;
				*Dst_p = bf;
			}
			else if(bf < 1) {
				bf = 1;
				*Dst_p = bf;
			}

			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//小数点3桁へ
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;
			dat *= 100;						//小数点3桁へ

			if (SEQ_PAR_113 & cBIT10) {			//＋オフセット
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//－オフセット
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_DAIHAI_LNG1O = dat / 100;		//ダイハイト下限(制御値)
			break;

		case 122:				//ダイハイト上限			//V06n
			if( bf > 32767 ) {
				bf = 32767;
				*Dst_p = bf;
			}
			else if(bf < 1) {
				bf = 1;
				*Dst_p = bf;
			}

			ofs = (S4b)GMN_PAR020;
			ofs *= 1000;					//小数点3桁へ
			ofs = cnv_mm_inch(ofs, 2);
			dat = bf;
			dat *= 100;						//小数点3桁へ

			if (SEQ_PAR_113 & cBIT10) {			//＋オフセット
				dat += ofs;
			}
			else if (SEQ_PAR_113 & cBIT11) {	//－オフセット
				dat -= ofs;
				if (dat < (S4b)SV0_RNAPOS_MINO) {
					dat = (S4b)SV0_RNAPOS_MINO;
				}
			}
			SV0_DAIHAI_LNG2O = dat / 100;		//ダイハイト上限(制御値)
			break;

		case 123:				//ﾓｰｼｮﾝ目標荷重の上下限		2015/01/15
			if( bf > GMN_PAR046 ) {
				bf = GMN_PAR046;
				*Dst_p = bf;
			}
			else if(bf < GMN_PAR047) {
				bf = GMN_PAR047;
				*Dst_p = bf;
			}
			break;

		case 124:				//ﾄﾚﾝﾄﾞ波形荷重スケール最大		//2014/03/14
//2015/05/12
////			if( (short)bf > (short)SV_MAXKA2_A24 ) {
////				*Dst_p = SV_MAXKA2_A24;
////			}
////			else if( (short)bf <= (short)SV_WAVE_SCL4D ) {
////				*Dst_p = (short)SV_WAVE_SCL4D + 1;
////			}
			if( (long)bf > (short)SV_MAXKA2_A24 ) {
				bf = SV_MAXKA2_A24;
				*Dst_p = bf;
			}
			else if( (long)bf <= (short)SV_WAVE_SCL4D ) {
				bf = (short)SV_WAVE_SCL4D + 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 125:				//ﾄﾚﾝﾄﾞ波形荷重スケール最小		//2014/03/14
//2015/05/12
////			if( (short)bf >= (short)SV_WAVE_SCL4U ) {
////				*Dst_p = (short)SV_WAVE_SCL4U - 1;
////			}
			if( (long)bf < -32767 ) {
				bf = -32767;
				*Dst_p = bf;
			}
			if( (long)bf >= (short)SV_WAVE_SCL4U ) {
				bf = (short)SV_WAVE_SCL4U - 1;
				*Dst_p = bf;
			}


			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 126:				//ｻﾝﾌﾟﾘﾝｸﾞの電力下限		//2014/03/14
			if( (long)bf >= (long)SV_WAVE_SCL5U ) {
				bf = (long)SV_WAVE_SCL5U - 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 127:				//ﾄﾚﾝﾄﾞ波形の電力上限		//2014/03/14
			if( (long)bf <= (long)SV_WAVE_SCL6D ) {
				bf = (long)SV_WAVE_SCL6D + 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 128:				//ﾄﾚﾝﾄﾞ波形の電力下限		//2014/03/14
			if( (long)bf >= (long)SV_WAVE_SCL6U ) {
				bf = (long)SV_WAVE_SCL6U - 1;
			}
			*Dst_p = bf;

			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 129:				//ｶﾑ出力自動演算 リリース 位置					2014/08/26
			wl0 = SV_TAIKIPOS_SRV;						//上限位置(mm/inch)
//2014/12/23
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

			PV0_CAMATCAL_FLG |= cBIT0;					//リリース高さ入力フラグＯＮ			2014/09/12

//2014/09/01 移動
////			RELEASE_POS_2_AGL_CAL(bf);					//小松さん演算
			break;

		case 130:				//ｶﾑ出力自動演算 リリース カムNo.				2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 131:				//ｶﾑ出力自動演算 送り 位置						2014/08/26
			wl0 = SV_TAIKIPOS_SRV;						//上限位置(mm/inch)
//2014/12/23
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

			PV0_CAMATCAL_FLG |= cBIT1;					//送り高さ入力フラグＯＮ			2014/09/12

//2014/09/01 移動
////			SEND_POS_2_AGL_CAL(bf);					//小松さん演算
			break;

		case 132:				//ｶﾑ出力自動演算 送り カムNo.					2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 133:				//ｶﾑ出力自動演算 ﾀｲﾐﾝｸﾞ カムNo.					2014/08/26
			bf = CAM_AUTO_LIMIT(bf);
			*Dst_p = bf;
			break;

		case 134:				//0 ～ 行程数+1(戻り行程)						2014/08/26
//2014/08/30
//			if (bf == 0) {
//				bf = 1;
//				*Dst_p = bf;
//			}
			if (bf > (SV_DANSUU_SRV+1)) {
				bf = SV_DANSUU_SRV+1;
				*Dst_p = bf;
			}
			break;

		case 135:				//干渉限界位置  角度							2014/08/26
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//×10倍
			*Dst_p = bf;
//2014/12/22			bf = DigRnaChange1(bf);	//角度→mm変換
			bf = cnv_mm_inch(DigRnaChange1(bf),0);	//角度→mm変換→mm/inch
			SV_INTLIM_POS = bf;
			sv_ref = 0xff;
			break;

		case 136:				//干渉限界位置  位置							2014/08/26
//2014/09/01
////			if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////				bf *= 10;							//小数点 2桁 -> 3桁
////				*Dst_p = bf;
////			}

			wl0 = SV_TAIKIPOS_SRV;						//上限位置(小数点 3桁)

//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/08/30			bf = RnaDigChange1(SV_INTLIM_AGL, bf);		//mm変換→角度
//2014/12/22			bf = RnaDigChange1(SV_DNAREA_JUDG, bf);		//mm変換→角度
			bf = RnaDigChange1(SV_DNAREA_JUDG, cnv_inch_mm(bf,0));		//mm変換→角度
			SV_INTLIM_AGL = bf;
			sv_ref = 0xff;
			break;

		case 137:				//待機判定時間上限								2014/08/30
			if( bf > GMN_PAR069 ) {
				bf = GMN_PAR069;
				*Dst_p = bf;
			}
			break;

		case 138:				//進角  角度入力上限							2014/09/01
			if( bf > GMN_PAR075 ) {
				bf = GMN_PAR075;
				*Dst_p = bf;
			}
			break;

		case 139:				//進角  時間入力上限							2014/09/01
			if( bf > GMN_PAR076 ) {
				bf = GMN_PAR076;
				*Dst_p = bf;
			}
			break;

		case 140:				//1 ～ 500										2014/09/03
			if( bf > 500 ) {
				*Dst_p = 500;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
			break;

		case 141:				//リピート開始行程 １ ～ 最大行程				2014/09/04
			if (bf == 0) {
				bf = 1;
				*Dst_p = bf;
			}
			if (bf > SV_DANSUU_SRV) {
				bf = SV_DANSUU_SRV;
				*Dst_p = bf;
			}
			break;

		case 142:				//リピート終了行程	開始行程 ～ 最大行程		2014/09/04
			if (bf < SV_MOTREP_STGS) {
				bf = SV_MOTREP_STGS;
				*Dst_p = bf;
			}
			if (bf > SV_DANSUU_SRV) {
				bf = SV_DANSUU_SRV;
				*Dst_p = bf;
			}
			break;

		case 143:				// ～ 繰り返し回数上限							2014/09/04
			if (bf > GMN_PAR077) {
				bf = GMN_PAR077;
				*Dst_p = bf;
			}
			break;

		case 144:				// 一定領域開始角度								2014/09/11
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//×10倍
			*Dst_p = bf;
//2014/12/22			SV0_FIXARA_POSS = DigRnaChange1(bf);		//角度→mm変換
			SV0_FIXARA_POSS = cnv_mm_inch(DigRnaChange1(bf),0);		//角度→mm変換→mm/inch
			ww0 = CAM_KOUTEI_SEARCH2(0, bf/10);			//角度→行程No.
			if (ww0 <= 1) {
				/* １段目より前の速度は無い？ */
				// 2014-10-06 KOMAPV0_FIXBF_SPD = 0;						//一定速度開始前速度
				PV0_FIXBF_SPD = SV_1DANSPD_SRV;		//一定速度開始前速度:１段目速度2014-10-06 koma
			}
			else {
				/* ２段目から前の速度が存在する？ */
				spd = &SV_1DANSPD_SRV;
				PV0_FIXBF_SPD = spd[ww0-2];				//一定速度開始前速度
			}
			sv_ref = 0xff;
			break;

		case 145:				// 一定領域開始位置								2014/09/11
			wl0 = SV_TAIKIPOS_SRV;						//上限位置(小数点 3桁)
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/12/22			bf = RnaDigChange1(SV0_FIXARA_AGLS, bf);		//mm変換→角度
			bf = RnaDigChange1(SV0_FIXARA_AGLS, cnv_inch_mm(bf,0));		//mm変換→角度
			SV0_FIXARA_AGLS = bf;
			sv_ref = 0xff;
			break;

		case 146:				// 一定領域終了角度								2014/09/11
			if( bf > 359 ) {
				bf = 359;
			}
			bf *= 10;									//×10倍
			*Dst_p = bf;
//2014/12/22			SV0_FIXARA_POSE = DigRnaChange1(bf);		//角度→mm変換
			SV0_FIXARA_POSE = cnv_mm_inch(DigRnaChange1(bf),0);		//角度→mm変換→mm/inch
			sv_ref = 0xff;
			break;

		case 147:				// 一定領域終了位置								2014/09/11
			wl0 = SV_TAIKIPOS_SRV;						//上限位置(小数点 3桁)
//2014/12/22
////			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
////				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
////					wl0 *= 10;							//小数点 3桁 -> 4桁
////				}
////			}
////			else{
////				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
////					bf *= 10;							//小数点 2桁 -> 3桁
////					*Dst_p = bf;
////				}
////			}
			if( (SEQ_016_SV & BIT_6) == 0 ) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0 ) {			//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}


			if( bf > wl0 ) {
				bf = wl0;
				*Dst_p = bf;
			}

//2014/12/22			bf = RnaDigChange1(SV0_FIXARA_AGLE, bf);		//mm変換→角度
			bf = RnaDigChange1(SV0_FIXARA_AGLE, cnv_inch_mm(bf,0));		//mm変換→角度
			SV0_FIXARA_AGLE = bf;
			sv_ref = 0xff;
			break;

		case 148:				// 位置決め完了範囲								2014/12/22
			if (bf > 32767) {
				bf = 32767;
				*Dst_p = bf;
			}
			if( (SEQ_016_SV & BIT_6) == 0) {				//単位切替 mm/INCH 単位系(1:INCH)
				if( (SEQ_016_SV & BIT_7) == 0) {			//単位 高精度(1:高精度)
					*Dst_p *= 10;
				}
			}
			break;

		case 149:				// 機械原点入力						2016/02/24
			if (SV0_RNAORG_ENB1 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 150:				// 機番								2016/02/24
			if (SV0_ORGCAL_ENB2 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 151:				// 機種								2016/02/24
			if (SV0_ORGCAL_ENB1 != 1) {
				Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_lp;
			}
			break;

		case 152:				// 角度値切替						2016/02/24
			if (SV0_MACINE_ENB1 != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( bf > 0xffff ) {
					*Dst_p = 0xffff;
				}

				if (bf == 9870) {								//データ10段→100段対応		2016/03/26
					copy_mot100();								//モーションデータ10段領域から100段領域にコピー
					*Dst_p = 0;
				}
			}
			break;

		case 153:				// 最大歪							2016/02/24
			if (SV0_MAXHIZ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( bf > 1500 ) {				//１５００より上？
					*Dst_p = 2000;
				}
				else if(bf <= 200) {			//２００以下？
					*Dst_p = 200;
				}
				else if(bf <= 400) {			//４００以下？
					*Dst_p = 400;
				}
				else if(bf <= 800) {			//８００以下？
					*Dst_p = 800;
				}
				else {							//１５００以下？
					*Dst_p = 1500;
				}
			}
			break;

		case 154:				// 最大荷重							2016/02/24
			if (SV0_MAXKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			break;

		case 155:				//校正荷重  最大荷重（左）以下　ＭＡＸチェック		2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKAJ_A24 ) {		//最大荷重（左以下）
						*Dst_p = SV_MAXKAJ_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 156:				//校正荷重  最大荷重（合計）以下　ＭＡＸチェック	2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKA2_A24 ) {		//最大荷重（合計以下）
						*Dst_p = SV_MAXKA2_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 157:				//校正荷重  最大荷重（右）以下　ＭＡＸチェック		2016/02/24
			if (SV0_KOUKAJ_ENB != 1) {
				Dst_wp = SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
				*Dst_p = *Dst_wp;
			}
			else {
				if( (bf & 0xffff0000) == 00 ) {
					if( bf > SV_MAXKA3_A24 ) {		//最大荷重（右以下）
						*Dst_p = SV_MAXKA3_A24;
					}
				}
				else{
					*Dst_p = bf >> 16;
				}
			}
			break;

		case 158:				//レベラフィーダ型式番号			2016/03/23
			if (bf < 1) {
				bf = 1;
			}
			if (bf > SYS_FEED_PAR0010) {
				bf = SYS_FEED_PAR0010;
			}
			*Dst_p = bf;

			Get_LFEED_SYS_PARA(bf);			//レベラフィーダのROMパラ取得
			break;

		case 159:				//レベラフィーダ矯正量入口			2016/03/23
			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSIDN];		//下限 *.**mm
			if (SEQ_016_SV & BIT_6) {								//仕様設定No.7  inch選択
				//下限値をinchへ
				if (dat < 0) {										//下限マイナス？
					dat *= -1;										//絶対値へ
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf < dat) {
				bf = dat;
			}

			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSIUP];		//上限 *.**mm
			if (SEQ_016_SV & BIT_6) {								//仕様設定No.7  inch選択
				//上限値をinchへ
				if (dat < 0) {										//下限マイナス？
					dat *= -1;										//絶対値へ
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf > dat) {
				bf = dat;
			}

			*Dst_p = bf;
			break;

		case 160:				//レベラフィーダ矯正量出口			2016/03/23
			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSODN];		//下限 *.**mm
			if (SEQ_016_SV & BIT_6) {								//仕様設定No.7  inch選択
				//下限値をinchへ
				if (dat < 0) {										//下限マイナス？
					dat *= -1;										//絶対値へ
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf < dat) {
				bf = dat;
			}

			dat = (S2b)SYS0_FEED_PAR_BLK[def_FORM_FED_HSOUP];		//上限 *.**mm
			if (SEQ_016_SV & BIT_6) {								//仕様設定No.7  inch選択
				//上限値をinchへ
				if (dat < 0) {										//上限マイナス？
					dat *= -1;										//絶対値へ
					dat = cnv_mm_inch2(dat*10, 0);
					dat *= -1;
				}
				else {
					dat = cnv_mm_inch2(dat*10, 0);
				}
			}
			if ((S4b)bf > dat) {
				bf = dat;
			}

			*Dst_p = bf;
			break;

		case 161:				//レベラフィーダ低速時送り速度		2016/03/23
			if (bf > SYS_FEED_PAR0011) {
				*Dst_p = SYS_FEED_PAR0011;
			}
			break;

		case 162:				//レベラフィーダ送り位置／リリース位置		2016/03/23
			wl0 = SV_RNA_STLORK;						//ストローク設定(小数点 3桁)

			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				bf = cnv_inch_mm(bf, 1);
			}
			else {
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				bf = wl0;								//ストローク設定mm
				*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
			}
			break;

		case 163:				//多段モーション設定上限角					2016/09/20
//2016/10/04
////			if ( (SEQ_PAR_151 & BIT_6) == 0 ) {			//振子無効
////				bf = 0;
////			}
////			else {
////				bf *= 10;								//×10倍
////				if (bf > GMN_PAR016) {					//振子の上限角上限設定
////					bf = GMN_PAR016;
////				}
////				if (bf < GMN_PAR019) {					//振子の上限角下限設定
////					bf = GMN_PAR019;
////				}
////			}
			bf *= 10;								//×10倍
			if (bf > GMN_PAR016) {					//振子の上限角上限設定
				bf = GMN_PAR016;
			}
			*Dst_p = bf;
			break;

		case 164:				//多段モーション設定上限位置				2016/09/20
//2016/10/04
////			if ( (SEQ_PAR_151 & BIT_6) == 0 ) {					//振子無効
////				bf = DigRnaChange1(0);							//0度→mm変換
////			}
////			else {
////				bf *= 10;
////				wl0 = DigRnaChange1(GMN_PAR016);				//角度→mm変換
////				if( bf < wl0 ) {
////					bf = wl0;									//
////				}
////				wl0 = DigRnaChange1(GMN_PAR019);				//角度→mm変換
////				if( bf > wl0 ) {
////					bf = wl0;									//
////				}
////			}
			bf *= 10;
			wl0 = DigRnaChange1(GMN_PAR016);				//角度→mm変換
			if( bf < wl0 ) {
				bf = wl0;									//
			}
			wl0 = DigRnaChange1(0);							//角度→mm変換
			if( bf > wl0 ) {
				bf = wl0;									//
			}
			*Dst_p = bf;
			break;

		case 165:				//多段モーション設定多段開始角度			2016/09/20
			bf *= 10;								//×10倍
//2016/10/04
////			if (bf > GMN_PAR016) {					//振子の上限角上限設定
////				bf = GMN_PAR016;
////			}
			if (bf > GMN_PAR100) {					//上限設定
				bf = GMN_PAR100;
			}
			if (bf < SV_TAIKIKAKU_SRV) {			//上限角でリミット
				bf = SV_TAIKIKAKU_SRV;
			}
			*Dst_p = bf;
			break;

		case 166:				//多段モーション設定多段開始位置			2016/09/20
			bf *= 10;									//小数点 2桁 -> 3桁
//2016/10/04
////			wl0 = DigRnaChange1(GMN_PAR016);				//角度→mm変換
			wl0 = DigRnaChange1(GMN_PAR100);				//角度→mm変換
			if( bf < wl0 ) {
				bf = wl0;									//
			}
			if( bf > SV_TAIKIPOS_SRV ) {
				bf = SV_TAIKIPOS_SRV;						//
			}
			*Dst_p = bf;
			break;

		case 167:				//多段モーション設定多段終了角度			2016/09/30
			bf *= 10;								//×10倍
//2016/09/30
////			if (bf > GMN_PAR016) {					//振子の上限角上限設定
////				bf = GMN_PAR016;
////			}
			if (bf > GMN_PAR100) {					//上限設定
				bf = GMN_PAR100;
			}
			if (bf < SV_TAIKIKAKU_SRV) {			//上限角でリミット
				bf = SV_TAIKIKAKU_SRV;
			}
			if (bf < SV_MSSTAT_AGL) {				//多段開始角度でリミット	2016/10/04
				bf = SV_MSSTAT_AGL;
			}
			*Dst_p = bf;
			break;

		case 168:				//多段モーション設定多段終了位置			2016/09/30
			bf *= 10;									//小数点 2桁 -> 3桁
//2016/09/30
////			wl0 = DigRnaChange1(GMN_PAR016);			//角度→mm変換
			wl0 = DigRnaChange1(GMN_PAR100);			//角度→mm変換
			if( bf < wl0 ) {
				bf = wl0;								//
			}
			if( bf > SV_TAIKIPOS_SRV ) {
				bf = SV_TAIKIPOS_SRV;					//
			}
			if( bf > SV_MSSTAT_POS ) {					//多段開始位置でリミット	2016/10/04
				bf = SV_MSSTAT_POS;						//
			}
			*Dst_p = bf;
			break;

		case 169:				//多段モーション設定多段回数				2016/09/20
			if (bf > GMN_PAR096) {
				bf = GMN_PAR096;
			}
			if (bf < GMN_PAR097) {
				bf = GMN_PAR097;
			}
			*Dst_p = bf;
			break;

		case 170:				//多段モーション設定戻し量比率				2016/09/20
			if (bf > GMN_PAR098) {
				bf = GMN_PAR098;
			}
			*Dst_p = bf;
			break;

		case 171:				//多段モーション設定基準速度				2016/09/20
			if( bf > 1000 ) {
				bf = 1000;
			}
			else if(bf < 1) {
				bf = 1;
			}
			*Dst_p = bf;
			break;

		case 172:				//ロータリカムOFFタイマ						2016/11/15
			if (bf > GMN_PAR101) {
				bf = GMN_PAR101;
			}
			*Dst_p = bf;
			break;

	}

	return(sv_ref);
}


/*
********************************************************************************
*  Module Name:		kajyu_chk
*  Function Name:	荷重の上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		ﾁｪｯｸﾌﾗｸﾞ
*
*  履 歴	: Shima		ON:2004-01-10
********************************************************************************
*/
UNs kajyu_chk( UNl *Dst_p, UNl bf )
{
	UNs		ww0, ww1;
	ww0 = 0;

	if(SV_MAXKA2_A24 < bf)						//上限（最大荷重）
	{
		*Dst_p = SV_MAXKA2_A24;
		bf = *Dst_p;
	}
	else if(GMN_PAR013 > bf)					//下限（パラメータ）
	{
		*Dst_p = GMN_PAR013;
		bf = *Dst_p;
	}
//V01z	ww1 = SV_KAJYUU_OBJP + GMN_PAR011;
	ww1 = PVP_ARA1_KAJ_T2 + GMN_PAR011;
	if (ww1 < bf )				// 変更大きすぎ？
	{
		ww0 = 0xff;
	}
//V01z	ww1 = SV_KAJYUU_OBJP - GMN_PAR011;
	ww1 = PVP_ARA1_KAJ_T2 - GMN_PAR011;
	if(ww1 & 0x8000)
	{
		ww1 = 0;
	}
	if (ww1 > bf )				// 変更小さすぎ？
	{
		ww0 = 0xff;
	}
	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// 補正入＆運転中？
		{
			ww0 = 0;
			bf = SV_KAJYUU_OBJP;
			*Dst_p = bf;
		}
	}
	if ( bf != SV_KAJYUU_OBJP )					// 変更有り？		//V01w(INS)
	{
		PV0_KAJYUHOS_BAK = SV_KAJYUU_OBJP;		// 変更有りなら前回値として記憶
	}
	return(ww0);
}


/*
********************************************************************************
*  Module Name:		kagen_chk
*  Function Name:	下限の上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		ﾁｪｯｸﾌﾗｸﾞ
*
*  履 歴	: Shima		ON:2004-01-10
********************************************************************************
*/
UNs kagen_chk( UNl *Dst_p, UNl bf )
{
	UNs		ww0, ww1;
	UNl		wl0, wl1;
	ww0 = 0;

	wl0 = SV_RNAPOS_MINP;					//機械下限(小数点 3桁)
	wl1 = SV_RNAPOS_MAXP;					//機械上限(小数点 3桁)

//V01m
////	wl0 /= 10;								//小数点 3桁 -> 2桁
////	wl1 /= 10;								//小数点 3桁 -> 2桁
////	if( bf > wl1 ) {
////		*Dst_p = wl1;						//機械上限
////	}
////	else if(bf < wl0) {						//機械下限
////		*Dst_p = wl0;
////	}
	if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
		bf = cnv_inch_mm(bf, 0);				//2014/12/17
	}
	else{
		if (SV_POINT_A1 == 0) {					//2014/12/23
			bf *= 1000;							//小数点 0桁 -> 3桁（内部データは小数点以下3桁）
		}
		else if (SV_POINT_A1 == 1) {
			bf *= 100;							//小数点 1桁 -> 3桁（内部データは小数点以下3桁）
		}
		else if (SV_POINT_A1 == 2) {			//2014/12/23
			bf *= 10;							//小数点 2桁 -> 3桁（内部データは小数点以下3桁）
		}
		else {
			bf *= 1;							//小数点 2桁 -> 3桁（内部データは小数点以下3桁）
		}
		*Dst_p = bf;
	}

	if( bf > wl1 ) {							//機械上限
//2014/12/17
////		*Dst_p = wl1;
////		bf = *Dst_p;
		bf = wl1;								//mm
		*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
	}
	else if(bf < wl0) {							//機械下限
//2014/12/17
////		*Dst_p = wl0;
////		bf = *Dst_p;
		bf = wl0;								//mm
		*Dst_p = cnv_mm_inch(bf, 0);			//mm/inch
	}

//2014/12/17
		//変化量確認
////	wl1 = SV_DAIHAITO_SRV + (UNl)GMN_PAR012;
////	if (wl1 < bf )								// 変更大きすぎ？
////	{
////		ww0 = 0xff;
////	}
////	wl1 = SV_DAIHAITO_SRV - (UNl)GMN_PAR012;
////	if(wl1 & 0x8000000)
////	{
////		wl1 = 0;
////	}
////	if (wl1 > bf )								// 変更大きすぎ？
////	{
////		ww0 = 0xff;
////	}

		//変化量確認
	wl1 = cnv_inch_mm(SV_DAIHAITO_SRV, 0) - bf;
	if ( (long)wl1 < 0 ) {
		wl1 = (long)wl1 * -1;						//変化量
	}
	if (wl1 > (UNl)GMN_PAR012) {					//変化量判定値
		ww0 = 0xff;									//変化大きすぎ！
	}

	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// 補正入＆運転中？
		{
			ww0 = 0;
//2014/12/17
////			bf = SV_DAIHAITO_SRV;
////			*Dst_p = bf;
			*Dst_p = SV_DAIHAITO_SRV;
		}
	}
//2014/12/17	if ( bf != SV_DAIHAITO_SRV )				// 変更有り？		//V01w(INS)
	if ( *Dst_p != SV_DAIHAITO_SRV )				// 変更有り？		//V01w(INS)
	{
		PV0_KAGENHOS_BAK = SV_DAIHAITO_SRV;		// 変更有りなら前回値として記憶
	}
	return(ww0);
}


/*
********************************************************************************
*  Module Name:		motion_spd_limit1
*  Function Name:	速度下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2015-07-10
********************************************************************************
*/
UNl		motion_spd_limit1(UNl bf, UNs t_no)
{
	UNs		i, chk, bit;
	UNs		step;

	chk = 0;
	bit = BIT_0;

#if (mot100_test == 1)
	if (SV_buff[t_no].GRP_NO == 102) {						//戻り行程の速度？
		if (PVP_MOT_STS[99] & cBIT3) {						//リミット有り？
			chk = 0xff;
		}
	}
	else {
		step = SV_MOT_PAGE * 5;								//1行目の行程No.0～99(=1～100)
		i = SV_buff[t_no].GRP_NO - 97;
		if (PVP_MOT_STS[step+i] & cBIT3) {					//リミット有り？
			chk = 0xff;
		}
	}
#else
	if (SV_buff[t_no].GRP_NO == 102) {						//戻り行程の速度？
		if (PVP_CKSPD_STPBT & cBIT15) {
			chk = 0xff;
		}
	}
	else {
		i = SV_buff[t_no].GRP_NO - 97;
		if ( (GAMEN_NO == 6) || (GAMEN_NO == 30) ) {
			i += 5;
		}
		bit<<=i;
		if (PVP_CKSPD_STPBT & bit) {						//この行程はリミット有り？
			chk = 0xff;
		}
	}
#endif

	if (chk) {
		if (GMN_PAR083 != 0) {							//戻り行程速度下限値の設定有り？
			if (bf < (GMN_PAR083*10)) {					//下限チェック
				bf = GMN_PAR083*10;						//下限リミット
			}
		}
	}

	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit0
*  Function Name:	回転／連寸一工程の時のﾓｰｼｮﾝ角度上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-01-10
********************************************************************************
*/
UNl motion_dig_limit0(UNl bf, UNs t_no)
{
	UNl		*posn, *posb;
	UNs		*degn, *degb;

//2016-04-16 koma	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
//2016-04-16 回転,振子(50.0or50.2)で 連寸一行程28.12または連続一行程28.11 koma
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(bf);					// V01j(ins)
				break;
			case 87:						// 行程2目標角度
				degb = &SV_1DANDEG_SRV;		// 前段目標角度
				posb = &SV_1DANPOS_SRV;		// 前段目標位置
				posn = &SV_2DANPOS_SRV;		// 現在目標位置
				break;
			case 88:						// 行程3目標角度
				degb = &SV_2DANDEG_SRV;		// 前段目標角度
				posb = &SV_2DANPOS_SRV;		// 前段目標位置
				posn = &SV_3DANPOS_SRV;		// 現在目標位置
				break;
			case 89:						// 行程4目標角度
				degb = &SV_3DANDEG_SRV;		// 前段目標角度
				posb = &SV_3DANPOS_SRV;		// 前段目標位置
				posn = &SV_4DANPOS_SRV;		// 現在目標位置
				break;
			case 90:						// 行程5目標角度
				degb = &SV_4DANDEG_SRV;		// 前段目標角度
				posb = &SV_4DANPOS_SRV;		// 前段目標位置
				posn = &SV_5DANPOS_SRV;		// 現在目標位置
				break;
			case 107:						// 行程6目標角度
				degb = &SV_5DANDEG_SRV;		// 前段目標角度
				posb = &SV_5DANPOS_SRV;		// 前段目標位置
				posn = &SV_6DANPOS_SRV;		// 現在目標位置
				break;
			case 108:						// 行程7目標角度
				degb = &SV_6DANDEG_SRV;		// 前段目標角度
				posb = &SV_6DANPOS_SRV;		// 前段目標位置
				posn = &SV_7DANPOS_SRV;		// 現在目標位置
				break;
			case 109:						// 行程8目標角度
				degb = &SV_7DANDEG_SRV;		// 前段目標角度
				posb = &SV_7DANPOS_SRV;		// 前段目標位置
				posn = &SV_8DANPOS_SRV;		// 現在目標位置
				break;
			case 110:						// 行程9目標角度
				degb = &SV_8DANDEG_SRV;		// 前段目標角度
				posb = &SV_8DANPOS_SRV;		// 前段目標位置
				posn = &SV_9DANPOS_SRV;		// 現在目標位置
				break;
			case 111:						// 行程10目標角度
				degb = &SV_9DANDEG_SRV;		// 前段目標角度
				posb = &SV_9DANPOS_SRV;		// 前段目標位置
				posn = &SV_10DANPOS_SRV;		// 現在目標位置
				break;
		}

//V01e		if(*degb >= SV_UPHOLD_DIG)			// 前段角度は上昇ﾎｰﾙﾄﾞ角度以上？
		if(*degb >= GMN_PAR003)				// 前段角度は上昇ﾎｰﾙﾄﾞ角度以上？
		{
			if( bf < *degb )				// 前段角度より小さい？
			{
				bf = *degb;					// 前段角度でﾘﾐｯﾄ
				*posn = *posb;				// 前段位置でﾘﾐｯﾄ
				MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()で角度→mmはやらなくて良いよ！
			}
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit1
*  Function Name:	回転時のﾓｰｼｮﾝ位置上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_dig_limit1(UNl bf, UNs t_no)
{
	if(SEQ_050_SV & BIT_0) {				//回転？
		if( bf > GMN_PAR007 ) {					// V01j
			bf = GMN_PAR007;					//上限値
		}
		else if (bf < GMN_PAR006) {
			bf = GMN_PAR006;					//下限値
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_dig_limit2
*  Function Name:	回転ﾓｰｼｮﾝ角度上下限ﾁｪｯｸ（前段角度より大きいかﾁｪｯｸ）
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_dig_limit2(UNl bf, UNs t_no)
{
	UNl		*posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (GMN_PAR008==1) )		//回転？ 大小比較有効？
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(bf);					// V01j(ins)
				break;
			case 87:						// 行程2目標角度
				degb = &SV_1DANDEG_SRV;		// 前段目標角度
				posb = &SV_1DANPOS_SRV;		// 前段目標位置
				posn = &SV_2DANPOS_SRV;		// 現在目標位置
				break;
			case 88:						// 行程3目標角度
				degb = &SV_2DANDEG_SRV;		// 前段目標角度
				posb = &SV_2DANPOS_SRV;		// 前段目標位置
				posn = &SV_3DANPOS_SRV;		// 現在目標位置
				break;
			case 89:						// 行程4目標角度
				degb = &SV_3DANDEG_SRV;		// 前段目標角度
				posb = &SV_3DANPOS_SRV;		// 前段目標位置
				posn = &SV_4DANPOS_SRV;		// 現在目標位置
				break;
			case 90:						// 行程5目標角度
				degb = &SV_4DANDEG_SRV;		// 前段目標角度
				posb = &SV_4DANPOS_SRV;		// 前段目標位置
				posn = &SV_5DANPOS_SRV;		// 現在目標位置
				break;
			case 107:						// 行程6目標角度
				degb = &SV_5DANDEG_SRV;		// 前段目標角度
				posb = &SV_5DANPOS_SRV;		// 前段目標位置
				posn = &SV_6DANPOS_SRV;		// 現在目標位置
				break;
			case 108:						// 行程7目標角度
				degb = &SV_6DANDEG_SRV;		// 前段目標角度
				posb = &SV_6DANPOS_SRV;		// 前段目標位置
				posn = &SV_7DANPOS_SRV;		// 現在目標位置
				break;
			case 109:						// 行程8目標角度
				degb = &SV_7DANDEG_SRV;		// 前段目標角度
				posb = &SV_7DANPOS_SRV;		// 前段目標位置
				posn = &SV_8DANPOS_SRV;		// 現在目標位置
				break;
			case 110:						// 行程9目標角度
				degb = &SV_8DANDEG_SRV;		// 前段目標角度
				posb = &SV_8DANPOS_SRV;		// 前段目標位置
				posn = &SV_9DANPOS_SRV;		// 現在目標位置
				break;
			case 111:						// 行程10目標角度
				degb = &SV_9DANDEG_SRV;		// 前段目標角度
				posb = &SV_9DANPOS_SRV;		// 前段目標位置
				posn = &SV_10DANPOS_SRV;		// 現在目標位置
				break;
		}

		if( bf < *degb )				// 前段角度より小さい？
		{
			bf = *degb;					// 前段角度でﾘﾐｯﾄ
			*posn = *posb;				// 前段位置でﾘﾐｯﾄ
			MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()で角度→mmはやらなくて良いよ！
		}
	}
	return(bf);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit0
*  Function Name:	回転／連寸一工程の時のﾓｰｼｮﾝ位置上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-01-10
********************************************************************************
*/
UNl motion_pos_limit0(UNl wl0, UNs t_no)
{
	UNs		i;
	UNl		long_bf, *posn, *posb;
	UNs		*degn, *degb;

//2016-04-16 koma	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
//2016-04-16 回転,振子(50.0or50.2)で 連寸一行程28.12または連続一行程28.11 koma
	if( ( SEQ_050_SV & (BIT_2|BIT_0) ) && ( SEQ_028_SV & (BIT_12|BIT_11) ) )		//2016-04-16 koma
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(wl0);				// V01j(ins)
				break;
			case 93:	// 行程2目標位置
				degb = &SV_1DANDEG_SRV;		// 前段目標角度
				posb = &SV_1DANPOS_SRV;		// 前段目標位置
				degn = &SV_2DANDEG_SRV;		// 現在目標角度
				break;
			case 94:	// 行程3目標位置
				degb = &SV_2DANDEG_SRV;		// 前段目標角度
				posb = &SV_2DANPOS_SRV;		// 前段目標位置
				degn = &SV_3DANDEG_SRV;		// 現在目標角度
				break;
			case 95:	// 行程4目標位置
				degb = &SV_3DANDEG_SRV;		// 前段目標角度
				posb = &SV_3DANPOS_SRV;		// 前段目標位置
				degn = &SV_4DANDEG_SRV;		// 現在目標角度
				break;
			case 96:	// 行程5目標位置
				degb = &SV_4DANDEG_SRV;		// 前段目標角度
				posb = &SV_4DANPOS_SRV;		// 前段目標位置
				degn = &SV_5DANDEG_SRV;		// 現在目標角度
				break;
			case 112:	// 行程6目標位置
				degb = &SV_5DANDEG_SRV;		// 前段目標角度
				posb = &SV_5DANPOS_SRV;		// 前段目標位置
				degn = &SV_6DANDEG_SRV;		// 現在目標角度
				break;
			case 113:	// 行程7目標位置
				degb = &SV_6DANDEG_SRV;		// 前段目標角度
				posb = &SV_6DANPOS_SRV;		// 前段目標位置
				degn = &SV_7DANDEG_SRV;		// 現在目標角度
				break;
			case 114:	// 行程8目標位置
				degb = &SV_7DANDEG_SRV;		// 前段目標角度
				posb = &SV_7DANPOS_SRV;		// 前段目標位置
				degn = &SV_8DANDEG_SRV;		// 現在目標角度
				break;
			case 115:	// 行程9目標位置
				degb = &SV_8DANDEG_SRV;		// 前段目標角度
				posb = &SV_8DANPOS_SRV;		// 前段目標位置
				degn = &SV_9DANDEG_SRV;		// 現在目標角度
				break;
			case 116:	// 行程10目標位置
				degb = &SV_9DANDEG_SRV;		// 前段目標角度
				posb = &SV_9DANPOS_SRV;		// 前段目標位置
				degn = &SV_10DANDEG_SRV;	// 現在目標角度
				break;
		}

//V01e		if(*degb >= SV_UPHOLD_DIG)			// 前段角度は上昇ﾎｰﾙﾄﾞ角度以上？
		if(*degb >= GMN_PAR003)					// 前段角度は上昇ﾎｰﾙﾄﾞ角度以上？
		{
			long_bf = cnv_inch_mm(wl0, 0);		//単位切替(mm/INCH→mm)
			i = *degn;
			i = RnaDigChange1(i, long_bf);		//mm変換→角度

			if( i < *degb )						// 前段角度より小さい？
			{
				wl0 = *posb;					// 前段位置でﾘﾐｯﾄ
				*degn = *degb;					// 前段角度でﾘﾐｯﾄ
				MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()でmm→角度はやらなくて良いよ！
			}
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit1
*  Function Name:	回転時のﾓｰｼｮﾝ位置上下限ﾁｪｯｸ
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl		motion_pos_limit1(UNl wl0, UNs t_no)
{
	UNl	long_bf;
	UNs	*deg, i, chg;

	if(SEQ_050_SV & BIT_0) {				//回転？
		long_bf = cnv_inch_mm(wl0, 0);		//単位切替(mm/INCH→mm)
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
			case 92:	// 行程1目標位置
				deg = &SV_1DANDEG_SRV;		// 前段目標角度
				break;
			case 93:	// 行程2目標位置
				deg = &SV_2DANDEG_SRV;		// 前段目標角度
				break;
			case 94:	// 行程3目標位置
				deg = &SV_3DANDEG_SRV;		// 前段目標角度
				break;
			case 95:	// 行程4目標位置
				deg = &SV_4DANDEG_SRV;		// 前段目標角度
				break;
			case 96:	// 行程5目標位置
				deg = &SV_5DANDEG_SRV;		// 前段目標角度
				break;
			case 112:	// 行程6目標位置
				deg = &SV_6DANDEG_SRV;		// 前段目標角度
				break;
			case 113:	// 行程7目標位置
				deg = &SV_7DANDEG_SRV;		// 前段目標角度
				break;
			case 114:	// 行程8目標位置
				deg = &SV_8DANDEG_SRV;		// 前段目標角度
				break;
			case 115:	// 行程9目標位置
				deg = &SV_9DANDEG_SRV;		// 前段目標角度
				break;
			case 116:	// 行程10目標位置
				deg = &SV_10DANDEG_SRV;		// 前段目標角度
				break;
		}

		i = *deg;
		chg = RnaDigChange1(i, long_bf);		//mm変換→角度

		if( chg > GMN_PAR007 ) {
			wl0 = DigRnaChange1(GMN_PAR007);	//角度→mm変換
			wl0 = cnv_mm_inch(wl0, 0);			//mm/inch				2014/12/17
			*deg = GMN_PAR007;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()でmm→角度はやらなくて良いよ！
		}
		else if (chg < GMN_PAR006) {
			wl0 = DigRnaChange1(GMN_PAR006);	//角度→mm変換
			wl0 = cnv_mm_inch(wl0, 0);			//mm/inch				2014/12/17
			*deg = GMN_PAR006;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()でmm→角度はやらなくて良いよ！
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		motion_pos_limit2
*  Function Name:	回転ﾓｰｼｮﾝ位置上下限ﾁｪｯｸ（前段位置より大きいかﾁｪｯｸ）
*  Input	: 		設定値
*  Return	: 		上下限後ﾃﾞｰﾀ
*  Note		:
*
*  履 歴	: Shima		ON:2004-07-01
********************************************************************************
*/
UNl motion_pos_limit2(UNl wl0, UNs t_no)
{
	UNs		i;
	UNl		long_bf, *posn, *posb;
	UNs		*degn, *degb;

	if( (SEQ_050_SV & BIT_0) && (GMN_PAR008==1) )		//回転？ 大小比較有効？
	{
		switch(SV_buff[t_no].GRP_NO)
		{
			default:
				return(wl0);				// V01j(ins)
				break;
			case 93:	// 行程2目標位置
				degb = &SV_1DANDEG_SRV;		// 前段目標角度
				posb = &SV_1DANPOS_SRV;		// 前段目標位置
				degn = &SV_2DANDEG_SRV;		// 現在目標角度
				break;
			case 94:	// 行程3目標位置
				degb = &SV_2DANDEG_SRV;		// 前段目標角度
				posb = &SV_2DANPOS_SRV;		// 前段目標位置
				degn = &SV_3DANDEG_SRV;		// 現在目標角度
				break;
			case 95:	// 行程4目標位置
				degb = &SV_3DANDEG_SRV;		// 前段目標角度
				posb = &SV_3DANPOS_SRV;		// 前段目標位置
				degn = &SV_4DANDEG_SRV;		// 現在目標角度
				break;
			case 96:	// 行程5目標位置
				degb = &SV_4DANDEG_SRV;		// 前段目標角度
				posb = &SV_4DANPOS_SRV;		// 前段目標位置
				degn = &SV_5DANDEG_SRV;		// 現在目標角度
				break;
			case 112:	// 行程6目標位置
				degb = &SV_5DANDEG_SRV;		// 前段目標角度
				posb = &SV_5DANPOS_SRV;		// 前段目標位置
				degn = &SV_6DANDEG_SRV;		// 現在目標角度
				break;
			case 113:	// 行程7目標位置
				degb = &SV_6DANDEG_SRV;		// 前段目標角度
				posb = &SV_6DANPOS_SRV;		// 前段目標位置
				degn = &SV_7DANDEG_SRV;		// 現在目標角度
				break;
			case 114:	// 行程8目標位置
				degb = &SV_7DANDEG_SRV;		// 前段目標角度
				posb = &SV_7DANPOS_SRV;		// 前段目標位置
				degn = &SV_8DANDEG_SRV;		// 現在目標角度
				break;
			case 115:	// 行程9目標位置
				degb = &SV_8DANDEG_SRV;		// 前段目標角度
				posb = &SV_8DANPOS_SRV;		// 前段目標位置
				degn = &SV_9DANDEG_SRV;		// 現在目標角度
				break;
			case 116:	// 行程10目標位置
				degb = &SV_9DANDEG_SRV;		// 前段目標角度
				posb = &SV_9DANPOS_SRV;		// 前段目標位置
				degn = &SV_10DANDEG_SRV;	// 現在目標角度
				break;
		}

		long_bf = cnv_inch_mm(wl0, 0);		//単位切替(mm/INCH→mm)
		i = *degn;
		i = RnaDigChange1(i, long_bf);		//mm変換→角度

		if( i < *degb )						// 前段角度より小さい？
		{
			wl0 = *posb;					// 前段位置でﾘﾐｯﾄ
			*degn = *degb;					// 前段角度でﾘﾐｯﾄ
			MOTION_SV_CHG_CANCEL = 0xff;	// mmon_sv_chg()でmm→角度はやらなくて良いよ！
		}
	}
	return(wl0);
}


/*
********************************************************************************
*  Module Name:		Key_sv_tokusyu_chk(旧：TOKUSYU_CHK)
*  Function Name:	設定値の特殊処理
*  Input	: 		設定値情報ﾃｰﾌﾞﾙの番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-20
********************************************************************************
*/
void	Key_sv_tokusyu_chk(UNs t_no)
{

	switch( SV_buff[t_no].YOBI_NO ) {

		case 0:			//処理なし
		case 1:			//MAX演算ﾃﾞｰﾀ			(Sit-Sなし)
		case 3:			//上型ｸﾗﾝﾊﾟ６選択仕様	(Sit-Sなし)
			break;

		case 2:			//型ﾃﾞｰﾀ設定変更
			KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ
			break;

		case 4:			//ﾓｰｼｮﾝ1段目速度		//V06m
			KAT_DATCHG_FLG = 0xff;				//型データ変更フラグ

			if ( (SEQ_050_SV & BIT_2) && (GMN_PAR021==1) ) {
				SV_TAIKSPD_SRV = SV_1DANSPD_SRV;								//戻り速度 <- 1段目速度
				SVPV_data_disp((UNl)SV_TAIKSPD_SRV, &SV_buff[25], 0, 1);		//戻り速度表示
			}
			break;
	}
}


/*
********************************************************************************
*  Module Name:		dansuu_zero_set
*  Function Name:	ｶﾑの段 00設定
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-09-12
********************************************************************************
*/
void	dansuu_zero_set(void)
{
	UNi	cnt, t_no;
	UNs	csr_no, dsp_no, *dst_p;
	UNl	cnv_bf;

	csr_no = CSR_FLG_CNT;
	dsp_no = SV_FLG_CNT;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){

		if( (SV_buff[t_no].SUB_NO == 53) &&					//ｻﾌﾞﾙｰﾁﾝ番号 ｻｰﾁ
			(SV_buff[t_no].CSR_NO == csr_no) &&				//ｶｰｿﾙ認識番号 同じ
			(SV_buff[t_no].DSP_NO != dsp_no) ) {			//ｶｰｿﾙ認識番号内の移動順位が違う

			dst_p = SV_buff[t_no].DATA_ADR;					//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
			*dst_p = 0;
			SVPV_data_disp(00, &SV_buff[t_no], 00, 0x01);	//設定値＆実測値 表示
			break;											//終了
		}
	}
}


/*
********************************************************************************
*  Module Name:		KEY_FILTER
*  Function Name:	KEYフィルタ処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:		KEYの2個同時ON対策、KEYの同時ONｴｯｼﾞOFFｴｯｼﾞ対策
*
*  履 歴	:FIT)田端		ON:2010/07/07	V05q
********************************************************************************
*/
void	KEY_FILTER(void)
{
	UNs	oncnt;
	UNs	kcnt, bcnt, bit, p;
	UNs	KeyWK[4];

	KeyWK[0] = Key_Data_No[0];
	KeyWK[1] = Key_Data_No[1];
	KeyWK[2] = Key_Data_No[2];
	KeyWK[3] = Key_Data_No[3];

	oncnt = 0;
	for(kcnt=4, p=0; kcnt>0; kcnt--, p++)					//Key_Data_WK(4ワード分)
	{
		for(bcnt=6, bit=0x0001; bcnt>0; bcnt--, bit<<=1)	//6bit分チェック
		{
			if(KeyWK[p] & bit)
			{
				oncnt++;									//ONしている数を数える
			}
		}
	}
	if(oncnt >= 2)					//ONが2個以上あるか？
	{
		//2個以上押されていれば強制全OFF
		KeyWK[0] = 0;
		KeyWK[1] = 0;
		KeyWK[2] = 0;
		KeyWK[3] = 0;
	}

	kcnt = KeyWK[0] + KeyWK[1] + KeyWK[2] + KeyWK[3];
	if(kcnt != 0)					//押されているKEYがあるか？
	{
		//ここに来る場合は必ずどれか1個のKEYが押されている状態
		bcnt = Key_Data_WK[0] + Key_Data_WK[1] + Key_Data_WK[2] + Key_Data_WK[3];
		if( bcnt == 0 )
		{
			/* 前回値が全OFFだから今回1個のONｴｯｼﾞが発生した＝OK */
		}
		else if( (KeyWK[0]==Key_Data_WK[0]) &&
				 (KeyWK[1]==Key_Data_WK[1]) &&
				 (KeyWK[2]==Key_Data_WK[2]) &&
				 (KeyWK[3]==Key_Data_WK[3]) )
		{
			/* 前回値と同じだから1個KEYを押し続けている＝OK */
		}
		else
		{
			/* 上記以外はONｴｯｼﾞとOFFｴｯｼﾞが同時発生したといこと */
			KeyWK[0] = 0;
			KeyWK[1] = 0;
			KeyWK[2] = 0;
			KeyWK[3] = 0;
		}
	}

	Key_Data_WK[0] = KeyWK[0];
	Key_Data_WK[1] = KeyWK[1];
	Key_Data_WK[2] = KeyWK[2];
	Key_Data_WK[3] = KeyWK[3];
}


/*
********************************************************************************
*  Function Name:	ｶﾑ出力自動演算
*  Input	:		bf:ﾘﾘｰｽ位置0.001mm
*  Return	: 		なし
*  Note		:		ﾘﾘｰｽ位置から角度を算出
*
*  履 歴	:		ON:2014/08/26
********************************************************************************
*/
void	RELEASE_POS_2_AGL_CAL(UNl bf)
{
	UNl		long_bf;
	S2b	dig1,dig2,dig3,dig4,dig5,taikidig;;


    taikidig=SV_TAIKIKAKU_SRV/10;	//待機点

//	SV0_RELE_SNO0	= 2;				//リリースカムオン行程
//	SV0_RELE_AGL0	= 100;				//リリースカムオン角度
//	SV0_RELE_SNO1	= 2;				//リリースカムオフ行程
//	SV0_RELE_AGL1	= 110;				//リリースカムオフ角度
//	SV0_TIMING_SNO0	= 2;				//タイミングカムオン行程
//	SV0_TIMING_AGL0	= 150;				//タイミングカムオン角度
//	SV0_TIMING_SNO1	= 2;				//タイミングカムオフ行程
//	SV0_TIMING_AGL1	= 160;				//タイミングカムオフ角度


	//ﾘﾘｰｽon角度
	if(SEQ_050_SV & BIT_1) {//反転
		long_bf = bf + SV_NEG_OFS_LNG;
	}else{
		long_bf=bf;
	}
	dig1=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm変換→角度:0~180.0度
	dig1=dig1/10;
	SV0_RELE_AGL0=dig1;				//リリースカムオン角度 1度単位


	//ﾘﾘｰｽoff角度
	if(SEQ_050_SV & BIT_1) {//反転
		long_bf=SV_NEG_OFS_LNG;
		dig2=RnaDigChange1(SV_DNAREA_JUDG, long_bf);
		dig2=(dig2/10)+GMN_PAR071;	// +/-data :通常は"-"
	}else{
		dig2=GMN_PAR070;			//回転,ふりこ
	}
	DigMaxMin1(dig2);
	SV0_RELE_AGL1	= dig2;			//リリースカムオフ角度 1度単位

	//送りｶﾑon角度
	dig3=DigAddDigUnit1(SV0_RELE_AGL0,GMN_PAR072);		//リリースカムオン角度 1度単位+送りカムオン角度差分
	SV0_SEND_AGL0	= TAIKIAREA_MAXMIN(dig3);			//送りカムオン角度

	//ﾀｲﾐﾝｸﾞｶﾑon角度
	dig4=DigAddDigUnit1(SV0_RELE_AGL0,GMN_PAR073);		//リリースカムオン角度+タイイングカムオン差分
	SV0_TIMING_AGL0	= TAIKIAREA_MAXMIN(dig4);			//タイミングカムオン角度

	//ﾀｲﾐﾝｸﾞｶﾑoff角度
	dig5=DigAddDigUnit1(SV0_TIMING_AGL0,GMN_PAR074);	//タイミングカムオン角度角度+タイングカムオフ差分
	SV0_TIMING_AGL1	= TAIKIAREA_MAXMIN(dig5);			//タイミングカムオフ角度

	SV0_RELE_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_RELE_AGL0);//0:最初 リリースカムオン行程
	SV0_RELE_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_RELE_AGL1);//1:最後 リリースカムオフ行程
	SV0_TIMING_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_TIMING_AGL0);//0:最初 タイミングカムオン行程
	SV0_TIMING_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_TIMING_AGL1);//0:最後 タイミングカムオフ行程

	SV0_SEND_SNO0	=CAM_KOUTEI_SEARCH1(0,SV0_SEND_AGL0);//0:最初 送りカムオン行程


}

/*
********************************************************************************
*  Function Name:	ｶﾑ出力自動演算
*  Input	:		なし
*  Return	: 		なし
*  Note		:		送り位置から角度を算出
*
*  履 歴	:		ON:2014/08/26
********************************************************************************
*/
void	SEND_POS_2_AGL_CAL(UNl bf)
{
	UNl		long_bf;
	S2b		dig1,taikidig;
	S2b		maxdig,mindig;


	taikidig=SV_TAIKIKAKU_SRV/10;	//待機点ではないのか?
	//送りカムoff角度
	if(SEQ_050_SV & BIT_1) {//反転
		long_bf = bf + SV_NEG_OFS_LNG;
		dig1=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm変換→角度:0~180.0度
		dig1=dig1/10;
		maxdig=180;
		mindig=taikidig;	//待機点でしょう
    }else{
        long_bf=bf;
		dig1=RnaDigChange1(2700, long_bf);	//mm変換→角度:180.0~359.9度
		dig1=dig1/10;
		if(SEQ_050_SV & BIT_2) {//ふりこ
			maxdig=360-taikidig;	//待機点 180-taikidig+180=3600-taikidig
			mindig=190;//190~
		}else{
			if(dig1==0){
				dig1=359;
			}
			maxdig=359;
			mindig=180;
		}
	}
	if(maxdig<dig1){
		dig1=maxdig;
	}
	if(dig1<mindig){
		dig1=mindig;
	}
	SV0_SEND_AGL1	=dig1;				//送りカムオフ角度
	SV0_SEND_SNO1	=CAM_KOUTEI_SEARCH1(1,SV0_SEND_AGL1);//1:最後 送りカムオフ行程

//	SV0_SEND_SNO0	= 3;				//送りカムオン行程
//	SV0_SEND_AGL0	= 200;				//送りカムオン角度
//	SV0_SEND_SNO1	= 3;				//送りカムオフ行程
//	SV0_SEND_AGL1	= 210;				//送りカムオフ角度

//	SV0_TIMING_SNO0	= 3;				//タイミングカムオン行程
//	SV0_TIMING_AGL0	= 250;				//タイミングカムオン角度
//	SV0_TIMING_SNO1	= 3;				//タイミングカムオフ行程
//	SV0_TIMING_AGL1	= 260;				//タイミングカムオフ角度
}



//	***************************************************
//	***												***
//	***		角度1(1度単位)+角度距離2→返し値		***
//	***		0~359			+/-359		0~359		***
//	***												***
//	***************************************************
//	
S2b	DigAddDigUnit1(S2b dig1,S2b dig2){
	S2b ansdig;

	if(	(-359<=dig2)	&&	(dig2<=359)	){
		ansdig=dig1+dig2;
	}else{
		ansdig=dig1;//dig2:ﾃﾞｰﾀ異常
	}
	if(ansdig<0){
		ansdig=ansdig+360;//-1度 → 359度
	}else{
		if(359<ansdig){
			ansdig=ansdig-360;	//360→0度 361→1度
		}
	}


	return(ansdig);
}


//	*******************************************************
//	***													***
//	***		待機点、待機領域を含めた動作範囲チェック	***
//	***													***
//	*******************************************************
//	反転,ふりこ、回転のモード判定有り

S2b	TAIKIAREA_MAXMIN(S2b dig)
{
	S2b taikidig,areadig,maxdig,mindig;
	UNl	long_bf;

	areadig=SV_UPAREA_JUDG/10+1;		//NO.40 上死点判定範囲
	taikidig=SV_TAIKIKAKU_SRV/10;		//待機点0.1度

	mindig=taikidig+areadig;
	if(360<=mindig){
		mindig=mindig-360;
	}

	DigMaxMin1(dig);
	if(SEQ_050_SV & BIT_1) {//反転
		long_bf = SV_NEG_OFS_LNG;
		maxdig=RnaDigChange1(SV_DNAREA_JUDG, long_bf);	//mm変換→角度:0~180.0度
		maxdig=maxdig/10;
		if(maxdig<dig){//大
			dig=maxdig;
		}
    }else{
		if(SEQ_050_SV & BIT_2) {//ふりこ
			maxdig=360-taikidig-areadig;	//180-taiki+180
		}else{//回転
			maxdig=taikidig-areadig;	//180-taiki+180
			if(maxdig<0){
				maxdig=maxdig+360;
			}
		}
	}
	if(dig<mindig){//小
		dig=mindig;
	}
	if(maxdig<dig){//大
		dig=maxdig;
	}
	return(dig);
}



//	***************************************************
//	***												***
//	***		設定角度を横切る最初の行程の検索		***
//	***		設定角度を横切る最後の行程の検索		***
//	***												***
//	***************************************************
//	sel==0:返し値は最初の行程
//	sel!=0:返し値は最後の行程
//	存在しない場合は返し値=0
//	注意:SV_1DANDEG_SRV~SV_10DANDEG_SRVは連続して並んでいること(0.1度単位)
//UNs		SV_DANSUU_SRV;              /* 段数 */
//UNs		SV_TAIKIKAKU_SRV;           /* 待機角 */
//UNs		SV_1DANDEG_SRV;             /* 1段目目標角度 */
//UNs		SV_2DANDEG_SRV;             /* 2段目目標角度 */
//UNs		SV_3DANDEG_SRV;             /* 3段目目標角度 */
//UNs		SV_4DANDEG_SRV;             /* 4段目目標角度 */
//UNs		SV_5DANDEG_SRV;             /* 5段目目標角度 */
//UNs		SV_6DANDEG_SRV;             /* 6段目目標角度 */
//UNs		SV_7DANDEG_SRV;             /* 7段目目標角度 */
//UNs		SV_8DANDEG_SRV;             /* 8段目目標角度 */
//UNs		SV_9DANDEG_SRV;             /* 9段目目標角度 */
//UNs		SV_10DANDEG_SRV;            /* 10段目目標角度 */
//	モードで最後の動きだけ違う


U2b CAM_KOUTEI_SEARCH1(U2b sel,S2b dig){
	U2b	stepmax;
	U2b	ansstep=0;
	U2b	objdig;
	U2b	dig_n1,dig_n,dig_last;
	U2b	firststep=0,laststep=0;
	U2b	dir=0;
	U2b	*srv;
	int	i;

	return(0);							//2014/09/10

	dig_n1	= SV_TAIKIKAKU_SRV;	//ｽﾀｰﾄ地点
	dig_n	= SV_TAIKIKAKU_SRV;	//
	stepmax	= SV_DANSUU_SRV+1;
	if((1<stepmax)&&(stepmax<=SYSPOS_STEP_MAX+1)){//1~10[98] 2015-11-20
		if(SEQ_050_SV & BIT_1) {//反転
			dig_last=dig_n1;//待機点に戻る
	    }else{
			if(SEQ_050_SV & BIT_2) {//ふりこ
				dig_last=3600-dig_n1;	//180.0-taiki+180.0
			}else{//回転
				dig_last=dig_n1+3600;	//370.0度でも良い
			}
		}
		objdig	=dig*10;//0.1度
		srv		= &SV_1DANDEG_SRV;	//

		for(i=0;i<stepmax;i++){
			dig_n1	=dig_n;
			if(i==(stepmax-1)){//最後
				dig_n	=dig_last;
			}else{
				dig_n	=srv[i];
			}
			if(dig_n1!=dig_n){
				if(dig_n1<dig_n){
					dir=0;//正転
					if((dig_n1<=objdig) && (objdig<dig_n) ){//50.0(n1)<=dig<100.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
				}else{
					dir=1;//逆転
					if((dig_n1>=objdig) && (objdig>dig_n)  ){//100.0(n1) >= dig > 50.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
					
				}
			}
		}
	
		if(sel==0){//sel=0 first
			ansstep=firststep;
		}else{
			ansstep=laststep;
		}
	}

	return(ansstep);//
}


//	***************************************************
//	***												***
//	***		設定角度を横切る最初の行程の検索		***
//	***		設定角度を横切る最後の行程の検索		***
//	***												***
//	***************************************************
//	sel==0:返し値は最初の行程
//	sel!=0:返し値は最後の行程
//	存在しない場合は返し値=0
//	注意:SV_1DANDEG_SRV~SV_10DANDEG_SRVは連続して並んでいること(0.1度単位)
//UNs		SV_DANSUU_SRV;              /* 段数 */
//UNs		SV_TAIKIKAKU_SRV;           /* 待機角 */
//UNs		SV_1DANDEG_SRV;             /* 1段目目標角度 */
//UNs		SV_2DANDEG_SRV;             /* 2段目目標角度 */
//UNs		SV_3DANDEG_SRV;             /* 3段目目標角度 */
//UNs		SV_4DANDEG_SRV;             /* 4段目目標角度 */
//UNs		SV_5DANDEG_SRV;             /* 5段目目標角度 */
//UNs		SV_6DANDEG_SRV;             /* 6段目目標角度 */
//UNs		SV_7DANDEG_SRV;             /* 7段目目標角度 */
//UNs		SV_8DANDEG_SRV;             /* 8段目目標角度 */
//UNs		SV_9DANDEG_SRV;             /* 9段目目標角度 */
//UNs		SV_10DANDEG_SRV;            /* 10段目目標角度 */
//	モードで最後の動きだけ違う
U2b CAM_KOUTEI_SEARCH2(U2b sel,S2b dig){
	U2b	stepmax;
	U2b	ansstep=0;
	U2b	objdig;
	U2b	dig_n1,dig_n,dig_last;
	U2b	firststep=0,laststep=0;
	U2b	dir=0;
	U2b	*srv;
	int	i;

	dig_n1	= SV_TAIKIKAKU_SRV;	//ｽﾀｰﾄ地点
	dig_n	= SV_TAIKIKAKU_SRV;	//
	stepmax	= SV_DANSUU_SRV+1;
	if((1<stepmax)&&(stepmax<=SYSPOS_STEP_MAX+1)){//1~10→2~11 2015-11-20
		if(SEQ_050_SV & BIT_1) {//反転
			dig_last=dig_n1;//待機点に戻る
	    }else{
			if(SEQ_050_SV & BIT_2) {//ふりこ
				dig_last=3600-dig_n1;	//180.0-taiki+180.0
			}else{//回転
				dig_last=dig_n1+3600;	//370.0度でも良い
			}
		}
		objdig	=dig*10;//0.1度
		srv		= &SV_1DANDEG_SRV;	//

		for(i=0;i<stepmax;i++){
			dig_n1	=dig_n;
			if(i==(stepmax-1)){//最後
				dig_n	=dig_last;
			}else{
				dig_n	=srv[i];
			}
			if(dig_n1!=dig_n){
				if(dig_n1<dig_n){
					dir=0;//正転
					if((dig_n1<=objdig) && (objdig<dig_n) ){//50.0(n1)<=dig<100.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
				}else{
					dir=1;//逆転
					if((dig_n1>=objdig) && (objdig>dig_n)  ){//100.0(n1) >= dig > 50.0(n)
						laststep=i+1;
						if(firststep==0){
							firststep=laststep;
						}
					}
					
				}
			}
		}
	
		if(sel==0){//sel=0 first
			ansstep=firststep;
		}else{
			ansstep=laststep;
		}
	}

	return(ansstep);//
}


/*
********************************************************************************
*  Function Name:	ｶﾑ出力自動演算
*  Input	:		なし
*  Return	: 		なし
*  Note		:		ﾘﾘｰｽｶﾑ／送りｶﾑ／ﾀｲﾐﾝｸﾞｶﾑ設定の上限ﾁｪｯｸ
*
*  履 歴	:		ON:2014/08/26
********************************************************************************
*/
UNl		CAM_AUTO_LIMIT(UNl bf)
{
	UNl		lim;

	if (SEQ_018_SV & cBIT12) {						//仕様設定No.45（ﾛｰﾀﾘｶﾑ1～4）
		if (SEQ_018_SV & cBIT14) {					//仕様設定No.47（ﾛｰﾀﾘｶﾑ5～8）
			if (SEQ_019_SV & cBIT0) {				//仕様設定No.49（ﾛｰﾀﾘｶﾑ9～12）
				if (SEQ_019_SV & cBIT2) {			//仕様設定No.51（ﾛｰﾀﾘｶﾑ13～16）
					if (SEQ_PAR_113 & cBIT6) {
						lim = 15;
					}
					else {
						lim = 16;
					}
				}
				else {
					if (SEQ_PAR_113 & cBIT6) {
						lim = 11;
					}
					else {
						lim = 12;
					}
				}
			}
			else {
				lim = 8;
			}
		}
		else {
			lim = 4;
		}
	}
	else {
		lim = 0;
	}
	
	if (bf > lim) {
		bf = lim;
	}

	return(bf);
}


/*
********************************************************************************
*  Input	:		なし
*  Return	: 		なし
*  Note		:		カム行程繰り返し戻り設定を解除
*
*  履 歴	:		ON:2014/09/05
********************************************************************************
*/
void	REP_CAM_CLR(UNs dan)
{
	UNs		bit;

	if ( (GAMEN_NO == 21) || (GAMEN_NO == 24) ) {				//ロータリカム1～8
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_ROTCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_ROTCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_ONR &= ~bit;
			}
		}
	}
	else if ( (GAMEN_NO == 22) || (GAMEN_NO == 25) ) {			//ロータリカム9～16
		if (SV_FLG_CNT == 1) {
			bit = cBIT8 << CSR_TBL_POS_NOW;
			SV_ROTCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT8 << CSR_TBL_POS_NOW;
			SV_ROTCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_ROTCAM_ONR &= ~bit;
			}
		}
	}
	else if ( (GAMEN_NO == 19) || (WINDOW_NO == 5) ) {			//エジェクタ／自動化
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_EJECAM_ONR &= ~bit;
			if (dan == 0) {
				SV_EJECAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_EJECAM_OFR &= ~bit;
			if (dan == 0) {
				SV_EJECAM_ONR &= ~bit;
			}
		}
	}
	else if ( GAMEN_NO == 20 ) {								//ミスフィード1～4
		if ( (CSR_TBL_POS_NOW == 0) || 
			 (CSR_TBL_POS_NOW == 2) || 
			 (CSR_TBL_POS_NOW == 4) || 
			 (CSR_TBL_POS_NOW == 6) ) {

			if (SV_FLG_CNT == 1) {
				bit = cBIT0 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_ONR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_OFR &= ~bit;
				}
			}
			else if (SV_FLG_CNT == 3) {
				bit = cBIT0 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_OFR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_ONR &= ~bit;
				}
			}
		}
	}
	else if ( GAMEN_NO == 68 ) {								//ミスフィード5～6
		if ( (CSR_TBL_POS_NOW == 0) || 
			 (CSR_TBL_POS_NOW == 2) ) {

			if (SV_FLG_CNT == 1) {
				bit = cBIT4 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_ONR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_OFR &= ~bit;
				}
			}
			else if (SV_FLG_CNT == 3) {
				bit = cBIT4 << (CSR_TBL_POS_NOW/2);
				SV_MISCAM_OFR &= ~bit;
				if (dan == 0) {
					SV_MISCAM_ONR &= ~bit;
				}
			}
		}
	}
	else if ( WINDOW_NO == 19 ) {								//ミスフィード1～6(WINDOW)
		if (SV_FLG_CNT == 1) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_MISCAM_ONR &= ~bit;
			if (dan == 0) {
				SV_MISCAM_OFR &= ~bit;
			}
		}
		else if (SV_FLG_CNT == 3) {
			bit = cBIT0 << CSR_TBL_POS_NOW;
			SV_MISCAM_OFR &= ~bit;
			if (dan == 0) {
				SV_MISCAM_ONR &= ~bit;
			}
		}
	}
}


/*
********************************************************************************
*  Input	:		なし
*  Return	: 		なし
*  Note		:		モーションデータ10段領域から100段領域にコピー
*
*  履 歴	:		ON:2015/03/26
********************************************************************************
*/
void	copy_mot100(void)
{
	UNs		*Dst_w, *Src_w, i, j, k;
	UNl		cnt;

	/*--- 回転モード  角度 ---*/
	Src_w = &SV_1DANDEG0_SRV;
	Dst_w = &SV_MOTDEG0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 反転モード  角度 ---*/
	Src_w = &SV_1DANDEG1_SRV;
	Dst_w = &SV_MOTDEG1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 振子モード  角度 ---*/
	Src_w = &SV_1DANDEG2_SRV;
	Dst_w = &SV_MOTDEG2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 上往復モード  角度 ---*/
	Src_w = &SV_1DANDEG3_SRV;
	Dst_w = &SV_MOTDEG3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 回転モード  位置 ---*/
	Src_w = (UNs *)&SV_1DANPOS0_SRV;
	Dst_w = (UNs *)&SV_MOTPOS0_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 反転モード  位置 ---*/
	Src_w = (UNs *)&SV_1DANPOS1_SRV;
	Dst_w = (UNs *)&SV_MOTPOS1_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 振子モード  位置 ---*/
	Src_w = (UNs *)&SV_1DANPOS2_SRV;
	Dst_w = (UNs *)&SV_MOTPOS2_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 上往復モード  位置 ---*/
	Src_w = (UNs *)&SV_1DANPOS3_SRV;
	Dst_w = (UNs *)&SV_MOTPOS3_001;
	for (i=0; i<10*2; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 回転モード  速度 ---*/
	Src_w = &SV_1DANSPD0_SRV;
	Dst_w = &SV_MOTSPD0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 反転モード  速度 ---*/
	Src_w = &SV_1DANSPD1_SRV;
	Dst_w = &SV_MOTSPD1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 振子モード  速度 ---*/
	Src_w = &SV_1DANSPD2_SRV;
	Dst_w = &SV_MOTSPD2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 上往復モード  速度 ---*/
	Src_w = &SV_1DANSPD3_SRV;
	Dst_w = &SV_MOTSPD3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 回転モード  停止時間 ---*/
	Src_w = &SV_1DANTIM0_SRV;
	Dst_w = &SV_MOTTIM0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 反転モード  停止時間 ---*/
	Src_w = &SV_1DANTIM1_SRV;
	Dst_w = &SV_MOTTIM1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 振子モード  停止時間 ---*/
	Src_w = &SV_1DANTIM2_SRV;
	Dst_w = &SV_MOTTIM2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 上往復モード  停止時間 ---*/
	Src_w = &SV_1DANTIM3_SRV;
	Dst_w = &SV_MOTTIM3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 回転モード  荷重 ---*/
	Src_w = &SV_1DANPRS0_SRV;
	Dst_w = &SV_MOTPRS0_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 反転モード  荷重 ---*/
	Src_w = &SV_1DANPRS1_SRV;
	Dst_w = &SV_MOTPRS1_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 振子モード  荷重 ---*/
	Src_w = &SV_1DANPRS2_SRV;
	Dst_w = &SV_MOTPRS2_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 上往復モード  荷重 ---*/
	Src_w = &SV_1DANPRS3_SRV;
	Dst_w = &SV_MOTPRS3_001;
	for (i=0; i<10; i++, Dst_w++, Src_w++) {
		*Dst_w = *Src_w;
	}
	for (; i<100; i++, Dst_w++) {
		*Dst_w = 0;
	}

	/*--- 回転モード  目標位置／荷重切替BIT情報 ---*/
	Src_w = &SV_MOTOBJ_INF0;
	Dst_w = &SV_MOTTGT0_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- 反転モード  目標位置／荷重切替BIT情報 ---*/
	Src_w = &SV_MOTOBJ_INF1;
	Dst_w = &SV_MOTTGT1_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- 振子モード  目標位置／荷重切替BIT情報 ---*/
	Src_w = &SV_MOTOBJ_INF2;
	Dst_w = &SV_MOTTGT2_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}
	
	/*--- 上往復モード  目標位置／荷重切替BIT情報 ---*/
	Src_w = &SV_MOTOBJ_INF3;
	Dst_w = &SV_MOTTGT3_INF0;
	*Dst_w = *Src_w & 0x03ff;
	Dst_w++;
	for (i=1; i<7; i++, Dst_w++) {
		*Dst_w = 0;
	}

	for (i=1; i<=220; i++) {
		kata_load(i, &kata_mot010_work[0]);			//型データをFROMから読込み

		/*--- 回転モード角度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 反転モード角度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 振子モード角度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 上往復モード角度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANDEG3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTDEG3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 回転モード位置 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 反転モード位置 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 振子モード位置 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 上往復モード位置 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = (UNs *)&kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPOS3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = (UNs *)&kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPOS3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10*2; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 回転モード速度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 反転モード速度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 振子モード速度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 上往復モード速度 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANSPD3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTSPD3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 回転モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 反転モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 振子モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 上往復モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANTIM3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTIM3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 回転モード荷重 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS0_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS0_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 反転モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS1_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS1_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 振子モード時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS2_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS2_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 上往復モード 時間 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_1DANPRS3_SRV - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTPRS3_001 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		for(j=0; j<10; j++, Src_w++, Dst_w++) {
			*Dst_w = *Src_w;
		}

		/*--- 回転モード 目標位置／荷重切替BIT情報 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF0 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT0_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- 反転モード 目標位置／荷重切替BIT情報 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF1 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT1_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- 振子モード 目標位置／荷重切替BIT情報 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF2 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT2_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		/*--- 上往復モード 目標位置／荷重切替BIT情報 ﾓｰｼｮﾝ10段→100段 ---*/
		Src_w = &kata_mot010_work[0];
		cnt   = (UNs *)&SV_MOTOBJ_INF3 - (UNs *)&FRAM_KAT_TOP;
		Src_w += cnt;

		Dst_w = &kata_mot100_work[0];
		cnt   = (UNs *)&SV_MOTTGT3_INF0 - (UNs *)&SV_MOTDEG0_001;
		Dst_w += cnt;

		*Dst_w = *Src_w & 0x03ff;

		kata_save2(i, &kata_mot100_work[0]);				//型データ(100段モーション)をFROMへ格納
	}
}


/*** END ***/
