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
#include "dp_cpuab.h"


/* 外部参照関数定義 -------------------------------------------------- */
extern	UNl		DigRnaChange1(UNs);
extern	void	ADC_NEXTNAME_SET(void);					/* ＡＤＣ次型番号名称 			*/

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

/* 定数定義 ---------------------------------------------------------- */
#define		E_SUBE1_DN	0x00D0				//上下限データポインタ
#define		E_SUBE2_DN	4					//上下限データポインタ
#define		E_SUBE3_DN	8					//上下限データポインタ
#define		E_SUBE4_DN	12					//上下限データポインタ
#define		E_SUBE5_DN	16					//上下限データポインタ
#define		E_SUBE6_DN	20					//上下限データポインタ

/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	Key_mng(void);							//ｷｰ入力確定
void	Key_Ten_in(UNs );						//Ten KEY入力
void	Key_Ent_sv(void);						//設定値の確定
void	Key_sv_limt_chk(UNs, UNl *);			//設定値の上下限チェック
void	Key_sv_tokusyu_chk(UNs);				//設定値の特殊処理
void	dansuu_zero_set(void);					//ｶﾑの段 強制00設定
UNs kajyu_chk( UNl *Dst_p, UNl bf );
UNs kagen_chk( UNl *Dst_p, UNl bf );
void	KEY_FILTER(void);						//KEYフィルタ処理	V05q

/* 内部変数定義 ------------------------------------------------------ */
UNl motion_dig_limit0(UNl, UNs);
UNl motion_dig_limit1(UNl, UNs);
UNl motion_dig_limit2(UNl, UNs);
UNl motion_pos_limit0(UNl, UNs);
UNl motion_pos_limit1(UNl, UNs);
UNl motion_pos_limit2(UNl, UNs);

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
	long	*Dst_Slp, cnv_bf_s;
	short	*Dst_Sp;

	t_no = SV_TBL_POS_NOW;

	if(SV_DATA_CHG != 00){
		SV_DATA_CHG = 00;									//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)

		cnv_bf = BCD_HEX4(SV_DISP_BUFF);					//BCD → HEX 変換

		Key_sv_limt_chk(t_no, &cnv_bf);						//設定値の上下限チェック

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

		if ((WINDOW_NO == 12) && (SV_buff[t_no].SUB_NO == 48)) {	// ADCｽﾃｯﾌﾟﾓﾆﾀ画面の次型番号？		V01j
			flag |= BIT_9;
		}

		SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);		//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)

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
void	Key_sv_limt_chk(UNs t_no, UNl *wk_p)
{
	UNl		wl0, wl1, bf, *Dst_p, *Src_p;
	UNl		kagen_mm, jyogen_mm;
	UNs		i , j, ww0, ww1;
	UNl		*Dst_p_w, long_bf, *posn, *posb;
	UNs		*degn, *degb;
	S4b		ofs, dat;

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
			break;

		case 21:				//オーバーロード（左）　ＭＡＸチェック
		case 35:				//最大荷重（左）以下　ＭＡＸチェック
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
		case 36:				//最大荷重（合計）以下　ＭＡＸチェック
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
		case 37:				//最大荷重（右）以下　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {		//最大荷重（右以下）
					*Dst_p = SV_MAXKA3_A24;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 24:				//オーバーロード（左）　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKAJ_A24 ) {			//最大荷重（左以下）
					*Dst_p = SV_MAXKAJ_A24;
				}
				else if( bf > SV_OVERE1_A26 ) {	//オーバーロード（左以下）
					*Dst_p = SV_OVERE1_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 25:				//ロアーリミッタ（合計）　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA2_A24 ) {			//最大荷重（合計以下）
					*Dst_p = SV_MAXKA2_A24;
				}
				else if( bf > SV_OVERE2_A26 ) {		//オーバーロード（合計以下）
					*Dst_p = SV_OVERE2_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
			}
			break;

		case 26:				//ロアーリミッタ（左）　ＭＡＸチェック
			if( (bf & 0xffff0000) == 00 ) {
				if( bf > SV_MAXKA3_A24 ) {			//最大荷重（右以下）
					*Dst_p = SV_MAXKA3_A24;
				}
				else if( bf > SV_OVERE3_A26 ) {		//オーバーロード（右以下）
					*Dst_p = SV_OVERE3_A26;
				}
			}
			else{
				*Dst_p = bf >> 16;
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
					*Dst_p = 100;
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else if ( MLD_100_FLG == 0xbb ) {		//V06n
				if(bf > 200){
					*Dst_p = 200;
				}
				else if(bf == 00){
					*Dst_p = 1;
				}
			}
			else {
				if(bf > 10){
					*Dst_p = 10;
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
			wl0 = 5;
			if (SEQ_024_SV & BIT_3) {				/* V01d */
				wl0 = 10;
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;
			}
			else if(bf < 1) {
				*Dst_p = 1;
			}
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
			break;

		case 54:				//0 ～ 反転設定不可範囲　(設定値を×10倍)
			bf *= 10;									//×10倍
			if( bf > SV_DNAREA_JUDG ) {
				bf = SV_DNAREA_JUDG;
			}
			if( SV_buff[t_no].GRP_NO == 85 ) {				//上限角の設定		V06k (INS)
				if( SEQ_050_SV & BIT_1 ) {					//反転時の上限角の最大値リミット		V05 (INS)
					if( bf > GMN_PAR015 ) {
						bf = GMN_PAR015;
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
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				*Dst_p = wl0;							//ストローク設定
				bf = wl0;
			}

			if( SEQ_050_SV & BIT_1 ) {					//反転時の上限位置		V05 (INS)
				wl0 = DigRnaChange1(GMN_PAR015);		//角度→mm変換
				if( bf < wl0 ) {
					*Dst_p = wl0;
					bf = wl0;
				}
			}
			else if ( SEQ_050_SV & BIT_2 ) {			//振子の上限位置		V06f (INS)
				wl0 = DigRnaChange1(GMN_PAR016);		//角度→mm変換
				if( bf < wl0 ) {
					*Dst_p = wl0;						//最小リミット
					bf = wl0;
				}
				wl0 = DigRnaChange1(GMN_PAR019);		//角度→mm変換
				if( bf > wl0 ) {
					*Dst_p = wl0;						//最大リミット
					bf = wl0;
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
			}
			else
			{
				if(bf < GMN_PAR001) {
					*Dst_p = GMN_PAR001;			//下限補正ﾘﾐｯﾀ
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
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}

			if( bf > wl0 ) {
				*Dst_p = wl0;							//ストローク設定
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
			if(bf < GMN_PAR001) {
				*Dst_p = GMN_PAR001;			//下限補正ﾘﾐｯﾀ
			}
			break;

		case 87:				//荷重補正の下限ﾁｪｯｸ		//V01w(INS)
			if(bf < GMN_PAR010) {
				*Dst_p = GMN_PAR010;			//荷重補正ﾘﾐｯﾀ
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
			wl0 = SV_RNAPOS_MAXP;						//機械上限(小数点 3桁)
			wl1 = SV_WAVE_SCL1D;						//ｽｹｰﾙ下限
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;							//機械上限
			}
			else if( bf < wl1 ) {
				*Dst_p = wl1;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 99:				//波形スライド位置スケール最小	//V05o(INS)
			wl0 = SV_RNAPOS_MINP;						//機械上限(小数点 3桁)
			wl1 = SV_WAVE_SCL1U;						//ｽｹｰﾙ下限
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}
			if( bf < wl0 ) {
				*Dst_p = wl0;							//機械下限
			}
			else if( bf > wl1 ) {
				*Dst_p = wl1;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 100:				//波形荷重スケール最大			//V05o(INS)
			if( bf > SV_MAXKA2_A24 ) {
				*Dst_p = SV_MAXKA2_A24;
			}
			else if( bf < SV_WAVE_SCL2D ) {
				*Dst_p = SV_WAVE_SCL2D;
			}
			Dsp_Pvgraph_Screen();
			WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ(再描画させる)
			break;

		case 101:				//波形荷重スケール最小			//V05o(INS)
			if( bf > SV_WAVE_SCL2U ) {
				*Dst_p = SV_WAVE_SCL2U;
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
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}
			if( bf > wl0 ) {
				*Dst_p = wl0;							//ﾀﾞｲﾊｲﾄ上限
			}
			else if( bf < wl1 ) {
				*Dst_p = wl1;
			}
			break;

		case 105:				//ｽﾗｲﾄﾞ下限検出位置		//V05o(INS)
			wl0 = SV_DAIHAI_LNG1*100;					//ﾀﾞｲﾊｲﾄ下限(小数点 1桁)
			wl1 = SV_TRDCSR_RNAU;						//ｽﾗｲﾄﾞ上限検出
			if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
				if( SEQ_016_SV & BIT_7 ) {				//単位 高精度(1:高精度)
					wl0 *= 10;							//小数点 3桁 -> 4桁
				}
			}
			else{
				if(0 == (SEQ_016_SV & BIT_7) ) {		//単位 高精度(1:高精度)
					bf *= 10;							//小数点 2桁 -> 3桁
					*Dst_p = bf;
				}
			}
			if( bf < wl0 ) {
				*Dst_p = wl0;							//ﾀﾞｲﾊｲﾄ下限
			}
			else if( bf > wl1 ) {
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
			if( bf > GMN_PAR041 ) {
				*Dst_p = GMN_PAR041;
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
	}
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
//	wl0 /= 10;								//小数点 3桁 -> 2桁
//	wl1 /= 10;								//小数点 3桁 -> 2桁
//	if( bf > wl1 ) {
//		*Dst_p = wl1;						//機械上限
//	}
//	else if(bf < wl0) {						//機械下限
//		*Dst_p = wl0;
//	}
	if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
	}
	else{
		if (SV_POINT_A1 == 1) {
			bf *= 100;							//小数点 1桁 -> 3桁
		}
		else {
			bf *= 10;							//小数点 2桁 -> 3桁
		}
		*Dst_p = bf;
	}
	if( bf > wl1 ) {
		*Dst_p = wl1;							//機械上限
		bf = *Dst_p;
	}
	else if(bf < wl0) {							//機械下限
		*Dst_p = wl0;
		bf = *Dst_p;
	}
	wl1 = SV_DAIHAITO_SRV + (UNl)GMN_PAR012;
	if (wl1 < bf )					// 変更大きすぎ？
	{
		ww0 = 0xff;
	}
	wl1 = SV_DAIHAITO_SRV - (UNl)GMN_PAR012;
	if(wl1 & 0x8000000)
	{
		wl1 = 0;
	}
	if (wl1 > bf )					// 変更小さすぎ？
	{
		ww0 = 0xff;
	}
	if (ww0 != 0)
	{
		if ( (SEQ_050_SV & BIT_8) && (SEQ_PAR_101 & BIT_15) )		// 補正入＆運転中？
		{
			ww0 = 0;
			bf = SV_DAIHAITO_SRV;
			*Dst_p = bf;
		}
	}
	if ( bf != SV_DAIHAITO_SRV )				// 変更有り？		//V01w(INS)
	{
		PV0_KAGENHOS_BAK = SV_DAIHAITO_SRV;		// 変更有りなら前回値として記憶
	}
	return(ww0);
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

	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
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

	if( (SEQ_050_SV & BIT_0) && (SEQ_028_SV & BIT_12) )		//回転？ 連寸一行程？
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
UNl motion_pos_limit1(UNl wl0, UNs t_no)
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
			*deg = GMN_PAR007;
			MOTION_SV_CHG_CANCEL = 0xff;		// mmon_sv_chg()でmm→角度はやらなくて良いよ！
		}
		else if (chg < GMN_PAR006) {
			wl0 = DigRnaChange1(GMN_PAR006);	//角度→mm変換
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



/*** END ***/
