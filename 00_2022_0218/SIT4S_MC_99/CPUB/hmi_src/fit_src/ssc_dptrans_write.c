/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ＤＰＲＡＭ ← ＦＲＡＭ	データ転送処理制御			*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned int

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離
#include	"ssc_def.h"
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_wk_ext.h"

#define		BLK_SRV		0x0001						/* ｻｰﾎﾞ		ﾌﾞﾛｯｸ		*/
#define		BLK_SYS		0x0002						/* ｼｽﾊﾟﾗ	ﾌﾞﾛｯｸ		*/
#define		BLK_MOT		0x0004						/* ﾓｰｼｮﾝ	ﾌﾞﾛｯｸ		*/
#define		BLK_SEQ		0x0008						/* ｼｰｹﾝｽ	ﾌﾞﾛｯｸ		*/
#define		BLK_CAM		0x0020						/* ｶﾑ		ﾌﾞﾛｯｸ		*/
#define		BLK_GEN		0x0100						/* 原点		ﾌﾞﾛｯｸ		*/

EXTRN	WORD	SVSW_CHG_FLG;						/* 書込要求ﾌﾗｸﾞ			*/

EXTRN	void	DP_TRANS_SRV(void);					/* ｻｰﾎﾞ  ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_TRANS_SYS(void);					/* ｼｽﾊﾟﾗ ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_TRANS_MOT(void);					/* ﾓｰｼｮﾝ ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_TRANS_SEQ(void);					/* ｼｰｹﾝｽ ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_TRANS_CAM(void);					/* ｶﾑ    ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_TRANS_GEN(void);					/* 原点  ﾌﾞﾛｯｸ転送処理	*/
EXTRN	void	DP_GET_SENS	(void);					/* ﾘﾆｱｾﾝｻBACKUP値 格納	*/
EXTRN	void	DP_BACK_SENS(void);					/* ﾘﾆｱｾﾝｻBACKUP値 復旧	*/
                                   
/****************************************************************************/
/*																			*/
/*	データ転送処理フラグ制御処理	：	ＤＰＲＡＭ ← ＦＲＡＭ				*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CHK	(void)
{
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SRV) != 0){			// 書き込み要求フラグが立っていたら
		if ((HS_SVCHG_B_TO_A & BLK_SRV) == 0){		// 書き込みフラグＬＯＷだったら
			if ((HS_SVCHG_A_TO_B & BLK_SRV) == 0){	// 読み込みフラグＬＯＷだったら
				DP_TRANS_SRV();						// データ転送処理
				HS_SVCHG_B_TO_A |= BLK_SRV;			// 書き込みフラグをＨＩＧＨにする
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){	// 読み込みフラグＨＩＧＨだったら
				HS_SVCHG_B_TO_A ^= BLK_SRV;			// 書き込みフラグをＬＯＷにする
				SVSW_CHG_FLG	^= BLK_SRV;			// 書き込み要求フラグをＬＯＷにする
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SYS) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_SYS) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_SYS) == 0){
				DP_TRANS_SYS();
				HS_SVCHG_B_TO_A |= BLK_SYS;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
				HS_SVCHG_B_TO_A ^= BLK_SYS;
				SVSW_CHG_FLG	^= BLK_SYS;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_MOT) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_MOT) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_MOT) == 0){
				DP_TRANS_MOT();
				HS_SVCHG_B_TO_A |= BLK_MOT;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
				HS_SVCHG_B_TO_A ^= BLK_MOT;
				SVSW_CHG_FLG	^= BLK_MOT;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_SEQ) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_SEQ) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_SEQ) == 0){
				DP_TRANS_SEQ();
				HS_SVCHG_B_TO_A |= BLK_SEQ;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
				HS_SVCHG_B_TO_A ^= BLK_SEQ;
				SVSW_CHG_FLG	^= BLK_SEQ;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_CAM) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_CAM) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_CAM) == 0){
				DP_TRANS_CAM();
				HS_SVCHG_B_TO_A |= BLK_CAM;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
				HS_SVCHG_B_TO_A ^= BLK_CAM;
				SVSW_CHG_FLG	^= BLK_CAM;
			}
		}
	}
/*--------------------------------------------------------------------------*/
	if ((SVSW_CHG_FLG &  BLK_GEN) != 0){
		if ((HS_SVCHG_B_TO_A & BLK_GEN) == 0){
			if ((HS_SVCHG_A_TO_B & BLK_GEN) == 0){
				DP_TRANS_GEN();
				HS_SVCHG_B_TO_A |= BLK_GEN;
			}
		}
		else{
			if ((HS_SVCHG_A_TO_B & BLK_GEN) != 0){
				// 原点変更時のみ、読み込みフラグが立っていたら
				DP_GET_SENS();						/* 原点時のｾﾝｻ値を格納	*/
				HS_SVCHG_B_TO_A ^= BLK_GEN;
				SVSW_CHG_FLG	^= BLK_GEN;
			}
		}
	}
}
/****************************************************************************/
