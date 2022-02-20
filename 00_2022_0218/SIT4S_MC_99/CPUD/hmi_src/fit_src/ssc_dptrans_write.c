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
//#include	"dp_cpuab.h"
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

void	DPB_SEND_2B(U2b *Src);
void	DPB_SEND_4B(U4b *Src);
U2b		DPB_GET_2B(U2b *Src);

                                   
/****************************************************************************/
/*																			*/
/*	データ転送処理フラグ制御処理	：	ＤＰＲＡＭ ← ＦＲＡＭ				*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CHK	(void)
{
	UNs		no, *srcW, datW;
	UNl		*srcL, datL;

/*--------------------------------------------------------------------------*/
//2015/03/12 新方式へ
////	if ((SVSW_CHG_FLG &  BLK_SRV) != 0){			// 書き込み要求フラグが立っていたら
////		if ((HS_SVCHG_B_TO_A & BLK_SRV) == 0){		// 書き込みフラグＬＯＷだったら
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) == 0){	// 読み込みフラグＬＯＷだったら
////				DP_TRANS_SRV();						// データ転送処理
////				HS_SVCHG_B_TO_A |= BLK_SRV;			// 書き込みフラグをＨＩＧＨにする
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){	// 読み込みフラグＨＩＧＨだったら
////				HS_SVCHG_B_TO_A ^= BLK_SRV;			// 書き込みフラグをＬＯＷにする
////				SVSW_CHG_FLG	^= BLK_SRV;			// 書き込み要求フラグをＬＯＷにする
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SRV) != 0){
		DP_TRANS_SRV();
		HS_SVCHG_B_TO_A |= BLK_SRV;
		SVSW_CHG_FLG	^= BLK_SRV;
	}
	if (HS_SVCHG_B_TO_A & BLK_SRV) {
		if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SRV;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 新方式へ
////	if ((SVSW_CHG_FLG &  BLK_SYS) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_SYS) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_SYS) == 0){
////				DP_TRANS_SYS();
////				HS_SVCHG_B_TO_A |= BLK_SYS;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_SYS;
////				SVSW_CHG_FLG	^= BLK_SYS;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SYS) != 0){
		DP_TRANS_SYS();
		HS_SVCHG_B_TO_A |= BLK_SYS;
		SVSW_CHG_FLG	^= BLK_SYS;
	}
	if (HS_SVCHG_B_TO_A & BLK_SYS) {
		if ((HS_SVCHG_A_TO_B & BLK_SYS) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SYS;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/04 新方式へ
////	if ((SVSW_CHG_FLG &  BLK_MOT) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_MOT) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_MOT) == 0){
////				DP_TRANS_MOT();
////				HS_SVCHG_B_TO_A |= BLK_MOT;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_MOT;
////				SVSW_CHG_FLG	^= BLK_MOT;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_MOT) != 0){
		DP_TRANS_MOT();
		HS_SVCHG_B_TO_A |= BLK_MOT;
		SVSW_CHG_FLG	^= BLK_MOT;
	}
	if (HS_SVCHG_B_TO_A & BLK_MOT) {
		if ((HS_SVCHG_A_TO_B & BLK_MOT) != 0){
			HS_SVCHG_B_TO_A ^= BLK_MOT;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 新方式へ
////	if ((SVSW_CHG_FLG &  BLK_SEQ) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_SEQ) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_SEQ) == 0){
////				DP_TRANS_SEQ();
////				HS_SVCHG_B_TO_A |= BLK_SEQ;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_SEQ;
////				SVSW_CHG_FLG	^= BLK_SEQ;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_SEQ) != 0){
		DP_TRANS_SEQ();
		HS_SVCHG_B_TO_A |= BLK_SEQ;
		SVSW_CHG_FLG	^= BLK_SEQ;
	}
	if (HS_SVCHG_B_TO_A & BLK_SEQ) {
		if ((HS_SVCHG_A_TO_B & BLK_SEQ) != 0){
			HS_SVCHG_B_TO_A ^= BLK_SEQ;
		}
	}
/*--------------------------------------------------------------------------*/
//2015/03/12 新方式へ
////	if ((SVSW_CHG_FLG &  BLK_CAM) != 0){
////		if ((HS_SVCHG_B_TO_A & BLK_CAM) == 0){
////			if ((HS_SVCHG_A_TO_B & BLK_CAM) == 0){
////				DP_TRANS_CAM();
////				HS_SVCHG_B_TO_A |= BLK_CAM;
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
////				HS_SVCHG_B_TO_A ^= BLK_CAM;
////				SVSW_CHG_FLG	^= BLK_CAM;
////			}
////		}
////	}
	if ((SVSW_CHG_FLG & BLK_CAM) != 0){
		DP_TRANS_CAM();
		HS_SVCHG_B_TO_A |= BLK_CAM;
		SVSW_CHG_FLG	^= BLK_CAM;
	}
	if (HS_SVCHG_B_TO_A & BLK_CAM) {
		if ((HS_SVCHG_A_TO_B & BLK_CAM) != 0){
			HS_SVCHG_B_TO_A ^= BLK_CAM;
		}
	}

//KOMA 2021-06-24(H2W:2020-08-11) A01v
	if(SVP_ATSLID_OBJ1==PVP_ATSLID_OBJ1){
		SEQ_PAR_058 |= BIT_6;
	}else{
		SEQ_PAR_058 &= ~BIT_6;
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

	/*-------------------------------------------------------*/
	/* １行程／１スキャン  モーション設定を送る（100段対応） */		//2015/09/23
	/*-------------------------------------------------------*/
#if (mot100_test == 1)
	if ( (GAMEN_NO == 3) || (GAMEN_NO == 28) ) {		//モーション画面表示中？
		SVP_MOT_PAGE = SV_MOT_PAGE + 1;					//ページ番号
		DPB_SEND_2B(&SVP_MOT_PAGE);

		datW = CSR_buff[CSR_TBL_POS_NOW].DATA_NO;
		if ( (datW >= 97) && (datW <= 101) ) {
			datW -= 97;
			datW += 1;
			SVP_MOT_CSR_STEP = SV_MOT_PAGE * 5 +datW;
		}
		else if (datW == 102) {
			SVP_MOT_CSR_STEP = 100;
		}
		else {
			SVP_MOT_CSR_STEP = 0;
		}
		DPB_SEND_2B(&SVP_MOT_CSR_STEP);
	}
	else {
		SVP_MOT_PAGE = 0;								//モーション画面非表示＝ページ0
		DPB_SEND_2B(&SVP_MOT_PAGE);

		SVP_MOT_CSR_STEP = 0;
		DPB_SEND_2B(&SVP_MOT_CSR_STEP);
	}

	if ( (SVP_MOT_SEND_REQ == 0) &&						//CPUA受信可能状態？
		 (DPB_GET_2B(&SVP_MOT_SEND_REQ) == 0) ) {		//CPUB受信可能状態？

		if (MOT_CHG_NO[0] == 0) {						//変更した行程有り？
			/* モーションのデータを順番に送る */
			no = MOT_SEND_NO;
			if (no==0) {
				no = 1;
			}
			MOT_SEND_NO++;
			if (MOT_SEND_NO > SV_DANSUU_SRV) {
				MOT_SEND_NO = 1;
			}
		}
		else {
			/* 変更した行程のモーション設定を送る */
			no = MOT_CHG_NO[0];
			MOT_CHG_NO[0] = MOT_CHG_NO[1];
			MOT_CHG_NO[1] = MOT_CHG_NO[2];
			MOT_CHG_NO[2] = MOT_CHG_NO[3];
			MOT_CHG_NO[3] = MOT_CHG_NO[4];
			MOT_CHG_NO[4] = 0;
		}
		no--;

		srcL = &SV_1DANPOS_SRV;
		datL = cnv_inch_mm(srcL[no], 0);
		if( SEQ_050_SV & BIT_1 ) {								//反転　？
			datL += SV_NEG_OFS_LNG;
		}
		SVP_OBJECT_PS = datL;									//行程ｎの目標位置
		DPB_SEND_4B((U4b *)&SVP_OBJECT_PS);

		srcW = &SV_1DANDEG_SRV;
		SVP_OBJECT_DG = srcW[no];								//行程ｎの目標角度
		DPB_SEND_2B(&SVP_OBJECT_DG);

		srcW = &SV_1DANSPD_SRV;
		SVP_OBJECT_SP = srcW[no];								//行程ｎの目標速度
		DPB_SEND_2B(&SVP_OBJECT_SP);

		srcW = &SV_1DANTIM_SRV;
		SVP_OBJECT_TM = srcW[no] * 10;							//行程ｎの停止時間
		DPB_SEND_2B(&SVP_OBJECT_TM);

		srcW = &SV_1DANPRS_SRV;;
		SVP_OBJECT_PRS = srcW[no];								//行程ｎの目標圧力
		DPB_SEND_2B(&SVP_OBJECT_PRS);

		datW = 0;
		if (step_pos_prs_chk(no)) {								//行程ｎ 目標位置／圧力
			datW |= cBIT0;
		}
		if (step_chg_spd_chk(no)) {								//行程ｎ 変速  前／後		2016/04/15
			datW |= cBIT1;
		}
		SVP_MOT_INF = datW;										//行程ｎ 情報
		DPB_SEND_2B(&SVP_MOT_INF);

		SVP_MOT_SEND_REQ = no + 1;
		DPB_SEND_2B(&SVP_MOT_SEND_REQ);
	}
#endif
}
/****************************************************************************/

extern	U2b		dpram_top;
extern	U2b		dpramB_top;

void	DPB_SEND_2B(
	U2b *Src
)
{
	U2b		*Dst;
	
	Dst  = (U2b *)&dpramB_top + (Src - (U2b *)&dpram_top);
	*Dst = *Src;
}

void	DPB_SEND_4B(
	U4b *Src
)
{
	U4b		*Dst;
	
	Dst  = (U4b *)&dpramB_top + (Src - (U4b *)&dpram_top);
	*Dst = *Src;
}

U2b		DPB_GET_2B(
	U2b *Src
)
{
	U2b		*Dst, dat;
	
	Dst = (U2b *)&dpramB_top + (Src - (U2b *)&dpram_top);
	dat = *Dst;

	return(dat);
}

