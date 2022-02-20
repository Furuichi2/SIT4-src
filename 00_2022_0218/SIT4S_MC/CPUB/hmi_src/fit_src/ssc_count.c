/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						カウンタ制御処理									*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"								//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

#define		CNT_LIMIT	9999999					/* ｶｳﾝﾀ限界	超えたら0ｸﾘｱ	*/
#define		E_TIM_1H	360000*2				//5ms定周期(1時間=1*60*60*100*2)

EXTRN		WORD		deg_OLD [];				/* 角度前回値				*/
EXTRN		WORD		rbit_OLD[];				/* ﾘｾｯﾄ   指令ﾋﾞｯﾄ前回値	*/
EXTRN		WORD		cbit_OLD[];				/* ｶｳﾝﾀUP 指令ﾋﾞｯﾄ前回値	*/

/* ﾌﾟﾛﾄﾀｲﾌﾟ */
void		TIM_5MS_COUNT	 (void);			/* ｶｳﾝﾀﾒｲﾝ 処理 5ms			*/
void		Count_Check_IN	 (WORD);			/* 内部ｶｳﾝﾀ処理				*/
void		Count_Check_IN0	 (WORD);			/* 内部ｶｳﾝﾀ処理	角度対応	*/
void		Count_Check_OUT	 (WORD);			/* 外部ｶｳﾝﾀ処理				*/
void		Count_Check_RESET(WORD);			/* ｶｳﾝﾀﾘｾｯﾄ処理				*/
void		Count_Check_smp(UNs);				//内部ｶｳﾝﾀ処理 ﾌﾗｸﾞをｻﾝﾌﾟﾘﾝｸﾞ
void		TIM_mcn_smp(void);					//メンテナンス時間 処理

/****************************************************************************/
/*																			*/
/*	カウント処理			：	定周期割り込みからコールされる	（５ｍｓ）	*/
/*																			*/
/*		ロットカウンタ１、２、トータルカウンタの更新を行う。				*/
/*		内部カウンタ時は、エンコーダ角度で									*/
/*		外部カウンタ時は、シーケンスデータで								*/
/*		カウンタＵＰを判断する。											*/
/*																			*/
/*		SEQ_PAR_016			：	カウンタ有／無、内部／外部指定				*/
/*		SEQ_PAR_032			：	カウンタ入／切指定							*/
/*																			*/
/*  履 歴	:																*/
/*			FIT)田端	ON:2002-08-08(ﾛｯﾄ2 ｶｳﾝﾀ / 機械総ｶｳﾝﾀ処理の追加)		*/
/*			FIT)田端	ON:2002-09-09(外部ｶｳﾝﾀ処理の追加による変更)			*/
/****************************************************************************/
void	TIM_5MS_COUNT	(void)
{
	UNs		i;

	Count_Check_IN (3);									//機械総ｶｳﾝﾀ処理

	if (((SEQ_016_SV & BIT_8) != 0) &&					/* ﾄｰﾀﾙｶｳﾝﾀ 有		*/
		((SEQ_032_SV & BIT_0) != 0) &&					/* ﾄｰﾀﾙｶｳﾝﾀ 入		*/
		((SEQ_PAR_102 & BIT_3) == 0)){					//ﾄｰﾀﾙｶｳﾝﾀ ﾘｾｯﾄ指令

		if ((SEQ_016_SV & BIT_9) == 0){					//ﾄｰﾀﾙｶｳﾝﾀ 外部ｶｳﾝﾄ
			Count_Check_IN (0);							/* 内部ｶｳﾝﾀ処理		*/
		}
		else{
			Count_Check_OUT(0);							/* 外部ｶｳﾝﾀ処理		*/
		}
	}
	else{
		Count_Check_smp(0);								//ﾄｰﾀﾙｶｳﾝﾀのｻﾝﾌﾟﾘﾝｸﾞ
	}

	if (((SEQ_016_SV & BIT_12) != 0) &&					/* ﾛｯﾄ1 ｶｳﾝﾀ 有		*/
		((SEQ_032_SV & BIT_2) != 0) &&					/* ﾛｯﾄ1 ｶｳﾝﾀ 入		*/
		((SEQ_PAR_033 & BIT_0) == 0) &&					//ﾛｯﾄ1 ｶｳﾝﾀ UP ?
		((SEQ_PAR_102 & BIT_11) == 0)){					//ﾛｯﾄ1 ｶｳﾝﾀ ﾘｾｯﾄ指令

		if ((SEQ_016_SV & BIT_13) == 0){				//ﾛｯﾄ1 ｶｳﾝﾀ 外部ｶｳﾝﾄ
			Count_Check_IN (1);							/* 内部ｶｳﾝﾀ処理		*/
		}
		else{
			Count_Check_OUT(1);							/* 外部ｶｳﾝﾀ処理		*/
		}
	}
	else{
		Count_Check_smp(1);								//ﾛｯﾄ1 ｶｳﾝﾀ のｻﾝﾌﾟﾘﾝｸﾞ
	}

	if (((SEQ_016_SV & BIT_14) != 0) &&					/* ﾛｯﾄ2 ｶｳﾝﾀ 有		*/
		((SEQ_032_SV & BIT_3) != 0) &&					/* ﾛｯﾄ2 ｶｳﾝﾀ 入		*/
		((SEQ_PAR_033 & BIT_1) == 0) &&				//ﾛｯﾄ2 ｶｳﾝﾀ UP ?
		((SEQ_PAR_102 & BIT_15) == 0)){					//ﾛｯﾄ2 ｶｳﾝﾀ ﾘｾｯﾄ指令

		if ((SEQ_016_SV & BIT_15) == 0){				//ﾛｯﾄ2 ｶｳﾝﾀ 外部ｶｳﾝﾄ
			Count_Check_IN (2);							/* 内部ｶｳﾝﾀ処理		*/
		}
		else{
			Count_Check_OUT(2);							/* 外部ｶｳﾝﾀ処理		*/
		}
	}
	else{
		Count_Check_smp(2);								//ﾛｯﾄ2 ｶｳﾝﾀ のｻﾝﾌﾟﾘﾝｸﾞ
	}


//DEL 13LINE : 2002-09-09
//	if ((SEQ_PAR_032 & BIT_00) != 0){					/* ﾄｰﾀﾙｶｳﾝﾀ 入		*/
//					Count_Check_IN (0);					/* 内部ｶｳﾝﾀ処理		*/
//	}													/*					*/
//
//	if ((SEQ_PAR_032 & BIT_02) != 0){					/* ﾛｯﾄ1 ｶｳﾝﾀ 入		*/
//					Count_Check_IN (1);					/* 内部ｶｳﾝﾀ処理		*/
//	}													/*					*/
//
////INS 4LINE : 2002-08-08
//	if ((SEQ_PAR_032 & BIT_03) != 0){					/* ﾛｯﾄ2 ｶｳﾝﾀ 入		*/
//					Count_Check_IN (2);					/* 内部ｶｳﾝﾀ処理		*/
//	}
//	Count_Check_IN (3);									// 機械総ｶｳﾝﾀ処理

//*	if (((SEQ_PAR_016 & BIT_08) != 0)&&					/* ﾄｰﾀﾙｶｳﾝﾀ 有		*/
//*		((SEQ_PAR_032 & BIT_00) != 0)){					/* ﾄｰﾀﾙｶｳﾝﾀ 入		*/
//*		if ((SEQ_PAR_016 & BIT_09) == 0)				/*					*/
//*					Count_Check_IN (0);					/* 内部ｶｳﾝﾀ処理		*/
//*		else		Count_Check_OUT(0);					/* 外部ｶｳﾝﾀ処理		*/
//*		Count_Check_RESET(0);							/* ｶｳﾝﾀﾘｾｯﾄ処理		*/
//*	}													/*					*/

//*	if (((SEQ_PAR_016 & BIT_12) != 0)&&					/* ﾛｯﾄ1 ｶｳﾝﾀ 有		*/
//*		((SEQ_PAR_032 & BIT_02) != 0)){					/* ﾛｯﾄ1 ｶｳﾝﾀ 入		*/
//*		if ((SEQ_PAR_016 & BIT_13) == 0)				/*					*/
//*					Count_Check_IN (1);					/* 内部ｶｳﾝﾀ処理		*/
//*		else		Count_Check_OUT(1);					/* 外部ｶｳﾝﾀ処理		*/
//*		Count_Check_RESET(2);							/* ｶｳﾝﾀﾘｾｯﾄ処理		*/
//*	}													/*					*/

//*	if (((SEQ_PAR_016 & BIT_14) != 0)&&					/* ﾛｯﾄ2 ｶｳﾝﾀ 有		*/
//*		((SEQ_PAR_032 & BIT_03) != 0)){					/* ﾛｯﾄ2 ｶｳﾝﾀ 入		*/
//*		if ((SEQ_PAR_016 & BIT_15) == 0)				/*					*/
//*					Count_Check_IN (2);					/* 内部ｶｳﾝﾀ処理		*/
//*		else		Count_Check_OUT(2);					/* 外部ｶｳﾝﾀ処理		*/
//*		Count_Check_RESET(2);							/* ｶｳﾝﾀﾘｾｯﾄ処理		*/
//*	}													/*					*/

/* V00t */
	i = GAIBU_RST_BAK;					//外部リセット指令立ち上がり？
	GAIBU_RST_BAK = SEQ_PAR_102;
	i ^= SEQ_PAR_102;
	i &= SEQ_PAR_102;
	if( i & BIT_3 ) {					//トータルカウンタ１リセット？
		PV_TOTLC1_B3 = 0;				//トータルカウンタ１クリア
		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
	}
	if( i & BIT_7 ) {					//トータルカウンタ２リセット？
		PV_TOTLC2_B31 = 0;				//トータルカウンタ２クリア
		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
	}
	if( i & BIT_B ) {					//ロットカウンタ１リセット？
		PV_LOTCT1_B4 = 0;				//ロットカウンタ１クリア
		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
		SEQ_PAR_033 &= ~BIT_0;			//ロットカウンタ１アップ　クリア
	}
	if( i & BIT_F ) {					//ロットカウンタ２リセット？
		PV_LOTCT2_B41 = 0;				//ロットカウンタ２クリア
		KAT_DATCHG_FLG = 0xff;			//カウンタ値変更フラグ
		SEQ_PAR_033 &= ~BIT_1;			//ロットカウンタ２アップ　クリア
	}
	if( SEQ_PAR_107 & BIT_6 ){						//ﾛｯﾄｶｳﾝﾀ減算式？
		PV_LOTCT1_B1 = (SV_PUR1SV_B4 - PV_LOTCT1_B4);
		PV_LOTCT2_B1 = (SV_PUR2SV_B41 - PV_LOTCT2_B41);
													//減算方式時ﾏｲﾅｽ表示対策
		if( PV_LOTCT1_B1 & 0x80000000 ) {
			PV_LOTCT1_B1 = 0;
		}
		if( PV_LOTCT2_B1 & 0x80000000 ) {
			PV_LOTCT2_B1 = 0;
		}
	}
	else{
		PV_LOTCT1_B1 = PV_LOTCT1_B4;
		PV_LOTCT2_B1 = PV_LOTCT2_B41;
	}
}


/****************************************************************************/
/*																			*/
/*	内部カウント処理		：	下死点通過フラグでカウンタＵＰを判断する。	*/
/*																			*/
/*		HS_PVP_LOTCNT_FLG	：	下死点通過フラグ							*/
/*		deg_OLD				：	前回値保存									*/
/*																			*/
/****************************************************************************/
void	Count_Check_IN	(WORD i)
{
	UNl	*bf_p;

	if (HS_PVP_LOTCNT_FLG != 0){						/* 下死点通過		*/
		if (deg_OLD[i] == 0){							/* 前回OFF	立上り	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3 ++;
						if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
						break;

			  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						  	PV_LOTCT1_B4 ++;
						if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
						break;

			  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
			  			  	PV_LOTCT2_B41++;
						if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
						break;

//INS 10LINE : 2002-08-08
			  case 3:
						bf_p = (UNl *)&PV_LIFE_COUNT[0];
						if(*bf_p == 0xffffffff){
							*bf_p += 1;
							PV_LIFE_COUNT[2] += 1;
						}
						else{
							*bf_p += 1;
						}
						break;

			  default:	break;
			}
			deg_OLD[i] = 1;								/* 前回値 ON		*/
		}
		else{
			deg_OLD[i] = 0;								/* 前回値 OFF		*/
			if( i == 3 ){
				HS_PVP_LOTCNT_FLG = 0;					/* 下死点通過ｸﾘｱ	*/
			}
		}
	}
	else	deg_OLD[i] = 0;								/* 前回値 OFF		*/
}
/****************************************************************************/
/*																			*/
/*	内部カウント処理		：	角度でカウンタＵＰを判断する。				*/
/*																			*/
/*		PVP_NOW_ANGLE_RNA	：	角度データ		（小数点１位 0～3599まで）	*/
/*		SEQ_PAR_222			：	正転／逆転									*/
/*		deg_OLD				：	角度前回値									*/
/*																			*/
/****************************************************************************/
void	Count_Check_IN0	(WORD i)
{
	WORD	real_deg;
	WORD	deg_min;
	WORD	deg_max;

//	if ((SEQ_PAR_160 & BIT_00) != 0){					/* 角度範囲			*/
//	if ((SEQ_PAR_222 & BIT_06) != 0){					/* 角度範囲			*/
	if (1){												/* DEBUG			*/
			deg_min = 180;								/* 正転時			*/
			deg_max = 270;								/*					*/
	}else{												/*					*/
			deg_min =  90;								/* 逆回転時			*/
			deg_max = 180;								/*					*/
	}													/*					*/

	real_deg = (PVP_NOW_ANGLE_RNA / 10);				/* 角度ﾃﾞｰﾀ取得		*/

	if (((real_deg >=deg_min)&&(real_deg <=deg_max))&&	/* 今回値 = 範囲内	*/
		((deg_OLD[i]<deg_min)||(deg_OLD[i]>deg_max))){	/* 前回値 = 範囲外	*/
		switch (i){
		  case 0:	PV_TOTLC1_B3 ++;
					if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
					break;
		  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						PV_LOTCT1_B4 ++;
					if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
					break;
		  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
						PV_LOTCT2_B41++;
					if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
					break;
		  default:	break;
		}
	}
	deg_OLD[i] = real_deg;								/* 保存				*/
}
/****************************************************************************/
/*																			*/
/*	外部カウント処理		：	シーケンスデータでカウンタＵＰを判断する。	*/
/*																			*/
/*		SEQ_PAR_102			：	カウンタ指令								*/
/*		cbit_OLD			：	カウンタ指令ビット前回値					*/
/*																			*/
/****************************************************************************/
void	Count_Check_OUT	(WORD i)
{
	WORD	count_bit;

	switch (i){											/* ﾁｪｯｸﾋﾞｯﾄ指定		*/
		case 0:		count_bit	= BIT_02;		break;
		case 1:		count_bit	= BIT_10;		break;
		case 2:		count_bit	= BIT_14;		break;
		default:	count_bit	= 0;			break;
	}

	if ((SEQ_PAR_102 & count_bit) != 0){				/* ｶｳﾝﾀ指令 ON		*/
		if (cbit_OLD[i] == 0){							/* 前回OFF	立上り	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3 ++;
						if (PV_TOTLC1_B3 > CNT_LIMIT)	PV_TOTLC1_B3 = 0;
						break;
			  case 1:	if (PV_LOTCT1_B4 < SV_PUR1SV_B4)
						  	PV_LOTCT1_B4 ++;
						if (PV_LOTCT1_B4 > CNT_LIMIT)	PV_LOTCT1_B4 = 0;
						break;
			  case 2:	if (PV_LOTCT2_B41< SV_PUR2SV_B41)
			  			  	PV_LOTCT2_B41++;
						if (PV_LOTCT2_B41> CNT_LIMIT)	PV_LOTCT2_B41= 0;
						break;
			  default:	break;
			}
		}
			cbit_OLD[i] = 1;							/* 前回値 ON		*/
	}
	else	cbit_OLD[i] = 0;							/* 前回値 OFF		*/
}
/****************************************************************************/
/*																			*/
/*	カウンタリセット処理	：	シーケンスデータでカウンタリセットする。	*/
/*																			*/
/*		SEQ_PAR_102			：	カウンタ指令								*/
/*		rbit_OLD			：	リセット指令ビット前回値					*/
/*																			*/
/****************************************************************************/
void	Count_Check_RESET	(WORD i)
{
	WORD	reset_bit;

	switch (i){											/* ﾁｪｯｸﾋﾞｯﾄ指定		*/
		case 0:		reset_bit	= BIT_03;		break;
		case 1:		reset_bit	= BIT_11;		break;
		case 2:		reset_bit	= BIT_15;		break;
		default:	reset_bit	= 0;			break;
	}

	if ((SEQ_PAR_102 & reset_bit) != 0){				/* ｶｳﾝﾀﾘｾｯﾄ指令 ON	*/
		if (rbit_OLD[i] == 0){							/* 前回OFF	立上り	*/
			switch (i){
			  case 0:	PV_TOTLC1_B3	= 0;	break;
			  case 1:	PV_LOTCT1_B4	= 0;	break;
			  case 2:	PV_LOTCT2_B41	= 0;	break;
			  default:							break;
			}
		}
			rbit_OLD[i] = 1;							/* 前回値 ON		*/
	}
	else	rbit_OLD[i] = 0;							/* 前回値 OFF		*/
}


/*
********************************************************************************
*  Module Name:		Count_Check_smp
*  Function Name:	内部カウント処理	下死点通過フラグをｻﾝﾌﾟﾘﾝｸﾞ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*				HS_PVP_LOTCNT_FLG	：	下死点通過フラグ
*				deg_OLD				：	前回値保存
*				cbit_OLD			：	カウンタ指令ビット前回値
*
*  履 歴	:FIT)田端		ON:2002-09-09
********************************************************************************
*/
void	Count_Check_smp(UNs i)
{
	UNs	count_bit;

	switch (i){												/* ﾁｪｯｸﾋﾞｯﾄ指定		*/
		case 0:	count_bit = (SEQ_016_SV & BIT_9);	break;	//ﾄｰﾀﾙｶｳﾝﾀ 外部ｶｳﾝﾄ
		case 1:	count_bit = (SEQ_016_SV & BIT_13);	break;	//ﾛｯﾄ1 ｶｳﾝﾀ 外部ｶｳﾝﾄ
		case 2:	count_bit = (SEQ_016_SV & BIT_15);	break;	//ﾛｯﾄ2 ｶｳﾝﾀ 外部ｶｳﾝﾄ
		default: count_bit	= 0;					break;
	}

	if(count_bit == 00 ){
		if (HS_PVP_LOTCNT_FLG != 0){						/* 下死点通過		*/
			if (deg_OLD[i] == 0){							/* 前回OFF	立上り	*/
				deg_OLD[i] = 1;								/* 前回値 ON		*/
			}
			else{
				deg_OLD[i] = 0;								/* 前回値 OFF		*/
			}
		}
		else{
			deg_OLD[i] = 0;									/* 前回値 OFF		*/
		}
	}
	else{
		switch (i){											/* ﾁｪｯｸﾋﾞｯﾄ指定		*/
			case 0:		count_bit	= BIT_02;		break;
			case 1:		count_bit	= BIT_10;		break;
			case 2:		count_bit	= BIT_14;		break;
			default:	count_bit	= 0;			break;
		}

		if ((SEQ_PAR_102 & count_bit) != 0){				/* ｶｳﾝﾀ指令 ON		*/
				cbit_OLD[i] = 1;							/* 前回値 ON		*/
		}
		else	cbit_OLD[i] = 0;							/* 前回値 OFF		*/
	}

}

/*
********************************************************************************
*  Module Name:		TIM_mcn_smp
*  Function Name:	メンテナンス時間 処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-08
********************************************************************************
*/
void	TIM_mcn_smp(void)
{
	UNs	bf, bf1;

//動作ｶｳﾝﾀ 処理
	bf = SEQ_PAR_111 & 0x00ff;			//立ち上がりデータ作成
	bf1 = MCN_SEQ_LAST1;
	MCN_SEQ_LAST1 = bf;
	bf1 ^= bf;
	bf1 &= bf;
	if( bf1 != 00 ){
		if(bf1 & BIT_0){				//動作ｶｳﾝﾀ1(C/B ON)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT1 ++;
		}
		if(bf1 & BIT_1){				//動作ｶｳﾝﾀ2(運転釦)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT2 ++;
		}
		if(bf1 & BIT_2){				//動作ｶｳﾝﾀ3(ｴｼﾞｪｸﾀ1)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT3 ++;
		}
		if(bf1 & BIT_3){				//動作ｶｳﾝﾀ4(ｴｼﾞｪｸﾀ2)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT4 ++;
		}
		if(bf1 & BIT_4){				//動作ｶｳﾝﾀ5(ｴｼﾞｪｸﾀ3)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT5 ++;
		}
		if(bf1 & BIT_5){				//動作ｶｳﾝﾀ6(自動化1)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT6 ++;
		}
		if(bf1 & BIT_6){				//動作ｶｳﾝﾀ7(自動化2)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT7 ++;
		}
		if(bf1 & BIT_7){				//動作ｶｳﾝﾀ4(自動化3)[1:ｶｳﾝﾄ]
			MCN_MENT_CNT8 ++;
		}
	}

//動作時間 処理
	bf1 = SEQ_PAR_111;
	if(bf1 & BIT_8){						//動作時間(稼動時間)[1:ｶｳﾝﾄ]
		MCN_MENT_TIM1_10 ++;				//5ms ｶｳﾝﾀ+1
		if(E_TIM_1H <= MCN_MENT_TIM1_10){	//ﾀｲﾏｰｱｯﾌﾟ？
			MCN_MENT_TIM1_10 = 0;			//ｸﾘｱ
			MCN_MENT_TIM1 ++;				//1時間 ｶｳﾝﾀ+1
		}
	}
	if(bf1 & BIT_9){						//動作時間(C/B ON)[1:ｶｳﾝﾄ]
		MCN_MENT_TIM2_10 ++;				//5ms ｶｳﾝﾀ+1
		if(E_TIM_1H <= MCN_MENT_TIM2_10){	//ﾀｲﾏｰｱｯﾌﾟ？
			MCN_MENT_TIM2_10 = 0;			//ｸﾘｱ
			MCN_MENT_TIM2 ++;				//1時間 ｶｳﾝﾀ+1
		}
	}
	if(bf1 & BIT_10){						//動作時間(ﾒｲﾝﾓｰﾀ)[1:ｶｳﾝﾄ]
		MCN_MENT_TIM3_10 ++;				//5ms ｶｳﾝﾀ+1
		if(E_TIM_1H <= MCN_MENT_TIM3_10){	//ﾀｲﾏｰｱｯﾌﾟ？
			MCN_MENT_TIM3_10 = 0;			//ｸﾘｱ
			MCN_MENT_TIM3 ++;				//1時間 ｶｳﾝﾀ+1
		}
	}

}


/****************************************************************************/
