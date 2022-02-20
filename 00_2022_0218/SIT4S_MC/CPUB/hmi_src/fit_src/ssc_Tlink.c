/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			Ｔリンク通信処理														*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：Shima		ON:2004-05-28			V01j
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include "dp_cpuab.h"							//DPRAM参照変数定義
#include "ssa_opram.h"							//OPRAM参照変数定義

/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	Tlink1_mng(void);						//Tlink通信処理
void	Tlink_SV_tx(void);
void	Tlink_PV_rx(void);
void	Tlink_SVtx_PVrx(void);
void	PVmove_BK1_BL1(void);
void	SVmove_BK1_BL1(void);
void	SVmove_BK10_BL1(void);
void	SVmove_BK10_BL2(void);
void	SVmove_BK10_BL3(void);
void	SVmove_BK10_BL4(void);
void	SVmove_BK10_BL5(void);
void	SVmove_BK20_BL1(void);
void	Trink_error_sub(void);

/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Tlink1_mng
*  Function Name:	Tlink通信処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-28
********************************************************************************
*/
void	Tlink1_mng(void)
{
	UNs	w1;

	if ( (SEQ_020_SV & BIT_12) == 0)		return;				//V05l-a 2009/03/24

//	2009
//	SEQ_PAR_427_CHG = SEQ_PAR_427_BAK ^ SEQ_PAR_427;			// 変化
//	SEQ_PAR_427_ONE = SEQ_PAR_427_CHG & SEQ_PAR_427;			// ONｴｯｼﾞ
//	SEQ_PAR_427_OFE = SEQ_PAR_427_CHG & SEQ_PAR_427_BAK;		// OFFｴｯｼﾞ
//	SEQ_PAR_427_BAK = SEQ_PAR_427;

	w1=SEQ_PAR_427;
	SEQ_PAR_427_CHG = SEQ_PAR_427_BAK ^ w1;			// 変化
	SEQ_PAR_427_ONE = SEQ_PAR_427_CHG & w1;			// ONｴｯｼﾞ
	SEQ_PAR_427_OFE = SEQ_PAR_427_CHG & SEQ_PAR_427_BAK;		// OFFｴｯｼﾞ
	SEQ_PAR_427_BAK = w1;

	if (SEQ_PAR_427_ONE) {
		if (SEQ_PAR_427_ONE & BIT_0) {
			Tlink_SV_tx();							// PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを送信する。
			SEQ_PAR_497 |= BIT_0;					// 送信完了ON!
		}
		if (SEQ_PAR_427_ONE & BIT_1) {
			Tlink_PV_rx();							// PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを受信し格納する。
			SEQ_PAR_497 |= BIT_1;					// 受信完了ON!
		}
		if (SEQ_PAR_427_ONE & BIT_2) {
			Tlink_SVtx_PVrx();						// PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを送信する。
													// PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを受信し格納する。
			SEQ_PAR_497 |= BIT_2;					// 送受信完了ON!
		}
	}

	if (SEQ_PAR_427_OFE) {
		if (SEQ_PAR_427_OFE & BIT_0) {				// 送信要求OFFした？
			SEQ_PAR_497 &= ~BIT_0;					// 送信完了OFF!
		}
		if (SEQ_PAR_427_OFE & BIT_1) {				// 受信要求OFFした？
			SEQ_PAR_497 &= ~BIT_1;					// 受信完了OFF!
		}
		if (SEQ_PAR_427_OFE & BIT_2) {				// 送受信要求OFFした？
			SEQ_PAR_497 &= ~BIT_2;					// 送受信完了OFF!
		}
	}

}


/*
********************************************************************************
*  Module Name:		Tlink_SV_tx
*  Function Name:	PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを送信する。
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_SV_tx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ﾊﾞﾝｸNo.／ﾌﾞﾛｯｸNo.返信

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ﾊﾞﾝｸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ﾌﾞﾛｯｸNo.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** 送信ﾊﾞﾝｸ1／ﾌﾞﾛｯｸ1処理 ****/
					SVmove_BK1_BL1();
					break;

				default:
					break;
			}
			break;

		case 10:
			switch (bl1) {
				case 1:
					/**** 送信ﾊﾞﾝｸ10／ﾌﾞﾛｯｸ1処理 ****/
					SVmove_BK10_BL1();
					break;

				case 2:
					/**** 送信ﾊﾞﾝｸ10／ﾌﾞﾛｯｸ2処理 ****/
					SVmove_BK10_BL2();
					break;

				case 3:
					/**** 送信ﾊﾞﾝｸ10／ﾌﾞﾛｯｸ3処理 ****/
					SVmove_BK10_BL3();
					break;

				case 4:
					/**** 送信ﾊﾞﾝｸ10／ﾌﾞﾛｯｸ4処理 ****/
					SVmove_BK10_BL4();
					break;

				case 5:
					/**** 送信ﾊﾞﾝｸ10／ﾌﾞﾛｯｸ5処理 ****/
					SVmove_BK10_BL5();
					break;

				default:
					break;
			}
			break;

		case 20:
			switch (bl1) {
				case 1:
					/**** 送信ﾊﾞﾝｸ20／ﾌﾞﾛｯｸ1処理 ****/
					SVmove_BK20_BL1();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

}




/*
********************************************************************************
*  Module Name:		Tlink_PV_rx
*  Function Name:	PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを受信し格納する。
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_PV_rx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ﾊﾞﾝｸNo.／ﾌﾞﾛｯｸNo.返信

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ﾊﾞﾝｸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ﾌﾞﾛｯｸNo.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** 受信ﾊﾞﾝｸ1／ﾌﾞﾛｯｸ1処理 ****/
					PVmove_BK1_BL1();
					break;

				default:
					Trink_error_sub();
					break;
			}
			break;

		default:
			Trink_error_sub();
			break;
	}

}


/*
********************************************************************************
*  Module Name:		OPdata_set_kaku
*  Function Name:	PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを送信する。
					PLCから要求のあったﾊﾞﾝｸ／ﾌﾞﾛｯｸを受信し格納する。
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
********************************************************************************
*/
void	Tlink_SVtx_PVrx(void)
{
	UNs		bk1, bl1, st1;

	SEQ_PAR_496 = SEQ_PAR_426;						// ﾊﾞﾝｸNo.／ﾌﾞﾛｯｸNo.返信

	bk1 = (SEQ_PAR_426>>8) & 0x0ff;					// ﾊﾞﾝｸNo.
	bl1 = SEQ_PAR_426 & 0x0ff;						// ﾌﾞﾛｯｸNo.

	switch (bk1) {
		case 1:
			switch (bl1) {
				case 1:
					/**** 送信ﾊﾞﾝｸ1／ﾌﾞﾛｯｸ1処理 ****/
					SVmove_BK1_BL1();
					/**** 受信ﾊﾞﾝｸ1／ﾌﾞﾛｯｸ1処理 ****/
					PVmove_BK1_BL1();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

}




/*
***********************************************************************
*
*  Module Name:		PVmove_BK1_BL1
*  Function Name:	実測値受信バンク１・ブロック１
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	PVmove_BK1_BL1(void) {

		UNl	d1,d2;

		PV_BARANS_C27 = SEQ_PAR_412;		/* バランサ圧 　２バイト*/
		PV_DAITY1_C27 = SEQ_PAR_413;		/* ダイクッション圧力左 　２バイト*/
		PV_DAITY2_C27 = SEQ_PAR_414;		/* ダイクッション圧力右 　２バイト*/

		d1 = ((UNl)SEQ_PAR_416<<16) & 0xffff0000;
		d2 = (UNl)SEQ_PAR_415 & 0x0000ffff;
		PV_DAIKA1_C27 = d1 | d2;			/* ダイクッション調節左　４バイト */

		d1 = ((UNl)SEQ_PAR_418<<16) & 0xffff0000;
		d2 = (UNl)SEQ_PAR_417 & 0x0000ffff;
		PV_DAIKA2_C27 = d1 | d2;			/* ダイクッション調節右　４バイト*/

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK1_BL1
*  Function Name:	設定値送信バンク１・ブロック１
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK1_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_482 = SV_BARANS_C27;		/* バランサ圧 　２バイト*/
		SEQ_PAR_483 = SV_DAITY1_C27;		/* ダイクッション圧力左 　２バイト*/
		SEQ_PAR_484 = SV_DAITY2_C27;		/* ダイクッション圧力右 　２バイト*/

		SEQ_PAR_485 = (UNs)(SV_DAIKA1_C27 & 0x0000ffff);
		SEQ_PAR_486 = (UNs)((SV_DAIKA1_C27>>16) & 0x0000ffff);		/* ダイクッション調節左　４バイト */

		SEQ_PAR_487 = (UNs)(SV_DAIKA2_C27 & 0x0000ffff);
		SEQ_PAR_488 = (UNs)((SV_DAIKA2_C27>>16) & 0x0000ffff);		/* ダイクッション調節右　４バイト*/

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL1
*  Function Name:	設定値送信バンク１０・ブロック１
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_MLDNO2_F1[0];		/* 型名称 */
		SEQ_PAR_482 = PV_MLDNO2_F1[1];		/* 型名称 */
		SEQ_PAR_483 = PV_MLDNO2_F1[2];		/* 型名称 */
		SEQ_PAR_484 = PV_MLDNO2_F1[3];		/* 型名称 */
		SEQ_PAR_485 = PV_MLDNO2_F1[4];		/* 型名称 */
		SEQ_PAR_486 = PV_MLDNO2_F1[5];		/* 型名称 */
		SEQ_PAR_487 = PV_MLDNO2_F1[6];		/* 型名称 */
		SEQ_PAR_488 = 0;					/* ダミー */
		SEQ_PAR_489 = PV_MLDNO3_F1[0];		/* メモ */
		SEQ_PAR_490 = PV_MLDNO3_F1[1];		/* メモ */
		SEQ_PAR_491 = PV_MLDNO3_F1[2];		/* メモ */
		SEQ_PAR_492 = PV_MLDNO3_F1[3];		/* メモ */
		SEQ_PAR_493 = PV_MLDNO3_F1[4];		/* メモ */
		SEQ_PAR_494 = PV_MLDNO3_F1[5];		/* メモ */
		SEQ_PAR_495 = PV_MLDNO3_F1[6];		/* メモ */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL2
*  Function Name:	設定値送信バンク１０・ブロック２
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL2(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_SPDSET_B11;							/* プレス速度　設定値 */
		SEQ_PAR_482 = PV_TLINKSMP_DAT;							/* プレス速度　実測値 */
		SEQ_PAR_483 = (UNs)(PV_TOTLC1_B3 & 0x0000ffff);			/* トータルカウンタ１実測値 下位 */
		SEQ_PAR_484 = (UNs)((PV_TOTLC1_B3>>16) & 0x0000ffff);	/* トータルカウンタ１実測値 上位 */
		SEQ_PAR_485 = (UNs)(SV_PUR1SV_B4 & 0x0000ffff);			/* ロットカウンタ１　設定値 下位 */
		SEQ_PAR_486 = (UNs)((SV_PUR1SV_B4>>16) & 0x0000ffff);	/* ロットカウンタ１　設定値 上位 */
		SEQ_PAR_487 = (UNs)(PV_LOTCT1_B4 & 0x0000ffff);			/* ロットカウンタ１　実測値 下位 */
		SEQ_PAR_488 = (UNs)((PV_LOTCT1_B4>>16) & 0x0000ffff);	/* ロットカウンタ１　実測値 上位 */
		SEQ_PAR_489 = (UNs)(SV_PUR2SV_B41 & 0x0000ffff);		/* ロットカウンタ２　設定値 下位 */
		SEQ_PAR_490 = (UNs)((SV_PUR2SV_B41>>16) & 0x0000ffff);	/* ロットカウンタ２　設定値 上位 */
		SEQ_PAR_491 = (UNs)(PV_LOTCT2_B41 & 0x0000ffff);		/* ロットカウンタ２　実測値 下位 */
		SEQ_PAR_492 = (UNs)((PV_LOTCT2_B41>>16) & 0x0000ffff);	/* ロットカウンタ２　実測値 上位 */
		SEQ_PAR_493 = PV_MLDNO1_F1;								/* 型番号 */
		SEQ_PAR_494 = ENCO_DATA_HEX;							/* 角度データ */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL3
*  Function Name:	設定値送信バンク１０・ブロック３
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL3(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = SV_OVERE1_A26;		/* オーバーロード　左 */
		SEQ_PAR_482 = SV_OVERE2_A26;		/* オーバーロード　合計 */
		SEQ_PAR_483 = SV_OVERE3_A26;		/* オーバーロード　右 */
		SEQ_PAR_484 = SV_ROALM1_A26;		/* ロアリミット　左 */
		SEQ_PAR_485 = SV_ROALM2_A26;		/* ロアリミット　合計 */
		SEQ_PAR_486 = SV_ROALM3_A26;		/* ロアリミット　右 */
		SEQ_PAR_487 = PV_KAJYU1_A24;		/* 荷重計実測　左 */
		SEQ_PAR_489 = PV_KAJYU2_A24;		/* 荷重計実測　合計 */
		SEQ_PAR_490 = PV_KAJYU3_A24;		/* 荷重計実測　右 */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL4
*  Function Name:	設定値送信バンク１０・ブロック４
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL4(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = PV_LIFE_COUNT[1];							/* 稼働回数 下位 */
		SEQ_PAR_482 = PV_LIFE_COUNT[0];							/* 稼働回数 上位 */
		SEQ_PAR_483 = (UNs)(MCN_MENT_TIM1 & 0x0000ffff);		/* 稼働時間 下位 */
		SEQ_PAR_484 = (UNs)((MCN_MENT_TIM1>>16) & 0x0000ffff);	/* 稼働時間 上位 */
		SEQ_PAR_485 = (UNs)(MCN_MENT_CNT1 & 0x0000ffff);		/* クラッチＯＮ回数 下位 */
		SEQ_PAR_486 = (UNs)((MCN_MENT_CNT1>>16) & 0x0000ffff);	/* クラッチＯＮ回数 上位 */
		SEQ_PAR_487 = (UNs)(MCN_MENT_TIM2 & 0x0000ffff);		/* クラッチＯＮ時間 下位 */
		SEQ_PAR_488 = (UNs)((MCN_MENT_TIM2>>16) & 0x0000ffff);	/* クラッチＯＮ時間 上位 */
		SEQ_PAR_489 = (UNs)(MCN_MENT_CNT2 & 0x0000ffff);		/* 運転釦ＯＮ回数 下位 */
		SEQ_PAR_490 = (UNs)((MCN_MENT_CNT2>>16) & 0x0000ffff);	/* 運転釦ＯＮ回数 上位 */
		SEQ_PAR_491 = (UNs)(MCN_MENT_TIM3 & 0x0000ffff);		/* メインモータＯＮ時間 下位 */
		SEQ_PAR_492 = (UNs)((MCN_MENT_TIM3>>16) & 0x0000ffff);	/* メインモータＯＮ時間 上位 */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK10_BL5
*  Function Name:	設定値送信バンク１０・ブロック５
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK10_BL5(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = (UNs)(MCN_MENT_CNT3 & 0x0000ffff);		/* エジェクタ１回数 下位 */
		SEQ_PAR_482 = (UNs)((MCN_MENT_CNT3>>16) & 0x0000ffff);	/* エジェクタ１回数 上位 */
		SEQ_PAR_483 = (UNs)(MCN_MENT_CNT6 & 0x0000ffff);		/* 自動化１回数 下位 */
		SEQ_PAR_484 = (UNs)((MCN_MENT_CNT6>>16) & 0x0000ffff);	/* 自動化１回数 上位 */
		SEQ_PAR_485 = (UNs)(MCN_MENT_CNT4 & 0x0000ffff);		/* エジェクタ２回数 下位 */
		SEQ_PAR_486 = (UNs)((MCN_MENT_CNT4>>16) & 0x0000ffff);	/* エジェクタ２回数 上位 */
		SEQ_PAR_487 = (UNs)(MCN_MENT_CNT7 & 0x0000ffff);		/* 自動化２回数 下位 */
		SEQ_PAR_488 = (UNs)((MCN_MENT_CNT7>>16) & 0x0000ffff);	/* 自動化２回数 上位 */
		SEQ_PAR_489 = (UNs)(MCN_MENT_CNT5 & 0x0000ffff);		/* エジェクタ３回数 下位 */
		SEQ_PAR_490 = (UNs)((MCN_MENT_CNT5>>16) & 0x0000ffff);	/* エジェクタ３回数 上位 */
		SEQ_PAR_491 = (UNs)(MCN_MENT_CNT8 & 0x0000ffff);		/* 自動化３回数 下位 */
		SEQ_PAR_492 = (UNs)((MCN_MENT_CNT8>>16) & 0x0000ffff);	/* 自動化３回数 上位 */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK20_BL1
*  Function Name:	設定値送信バンク２０・ブロック１
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	SVmove_BK20_BL1(void) {

		UNs	d1,d2;

		SEQ_PAR_481 = IROCK_NO[0];				/* インターロックデータ１ */
		SEQ_PAR_482 = IROCK_NO[1];				/* インターロックデータ２ */
		SEQ_PAR_483 = IROCK_NO[2];				/* インターロックデータ３ */
		SEQ_PAR_484 = IROCK_NO[3];				/* インターロックデータ４ */
		SEQ_PAR_485 = IROCK_NO[4];				/* インターロックデータ５ */
		SEQ_PAR_486 = IROCK_NO[5];				/* インターロックデータ６ */
		SEQ_PAR_487 = IROCK_NO[6];				/* インターロックデータ７ */

		SEQ_PAR_497 &= ~BIT_8;				// 異常ビットOFF!
}


/*
***********************************************************************
*
*  Module Name:		SVmove_BK20_BL1
*  Function Name:	設定値送信バンク２０・ブロック１
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-05-31
***********************************************************************
*/
void	Trink_error_sub(void) {
		SEQ_PAR_497 |= BIT_8;					// 異常ビットON!
}


/*** END ***/
