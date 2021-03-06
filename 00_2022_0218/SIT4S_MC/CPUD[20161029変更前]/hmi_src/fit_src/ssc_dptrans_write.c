/****************************************************************************/
/*																			*/
/*	R}cY@aü¯	rhs|rRg[								*/
/*																			*/
/*						coq`l © eq`l	f[^]§ä			*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned int

#include "ssc_ver1.h"							//eíÌ¤Êè`
#include	"cm_equ1.h"		//MCÉÄª£

#include	"ssc_def.h"
#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"
#include	"ssc_dpram_seq_ext.h"
#include	"ssc_wk_ext.h"

#define		BLK_SRV		0x0001						/* »°ÎÞ		ÌÞÛ¯¸		*/
#define		BLK_SYS		0x0002						/* ¼½Êß×	ÌÞÛ¯¸		*/
#define		BLK_MOT		0x0004						/* Ó°¼®Ý	ÌÞÛ¯¸		*/
#define		BLK_SEQ		0x0008						/* ¼°¹Ý½	ÌÞÛ¯¸		*/
#define		BLK_CAM		0x0020						/* ¶Ñ		ÌÞÛ¯¸		*/
#define		BLK_GEN		0x0100						/* ´_		ÌÞÛ¯¸		*/

EXTRN	WORD	SVSW_CHG_FLG;						/* vÌ×¸Þ			*/

EXTRN	void	DP_TRANS_SRV(void);					/* »°ÎÞ  ÌÞÛ¯¸]	*/
EXTRN	void	DP_TRANS_SYS(void);					/* ¼½Êß× ÌÞÛ¯¸]	*/
EXTRN	void	DP_TRANS_MOT(void);					/* Ó°¼®Ý ÌÞÛ¯¸]	*/
EXTRN	void	DP_TRANS_SEQ(void);					/* ¼°¹Ý½ ÌÞÛ¯¸]	*/
EXTRN	void	DP_TRANS_CAM(void);					/* ¶Ñ    ÌÞÛ¯¸]	*/
EXTRN	void	DP_TRANS_GEN(void);					/* ´_  ÌÞÛ¯¸]	*/
EXTRN	void	DP_GET_SENS	(void);					/* ØÆ±¾Ý»BACKUPl i[	*/
EXTRN	void	DP_BACK_SENS(void);					/* ØÆ±¾Ý»BACKUPl 	*/
                                   
/****************************************************************************/
/*																			*/
/*	f[^]tO§ä	F	coq`l © eq`l				*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_CHK	(void)
{
/*--------------------------------------------------------------------------*/
//2015/03/12 Vû®Ö
////	if ((SVSW_CHG_FLG &  BLK_SRV) != 0){			// «ÝvtOª§ÁÄ¢½ç
////		if ((HS_SVCHG_B_TO_A & BLK_SRV) == 0){		// «ÝtOknv¾Á½ç
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) == 0){	// ÇÝÝtOknv¾Á½ç
////				DP_TRANS_SRV();						// f[^]
////				HS_SVCHG_B_TO_A |= BLK_SRV;			// «ÝtOðghfgÉ·é
////			}
////		}
////		else{
////			if ((HS_SVCHG_A_TO_B & BLK_SRV) != 0){	// ÇÝÝtOghfg¾Á½ç
////				HS_SVCHG_B_TO_A ^= BLK_SRV;			// «ÝtOðknvÉ·é
////				SVSW_CHG_FLG	^= BLK_SRV;			// «ÝvtOðknvÉ·é
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
//2015/03/12 Vû®Ö
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
//2015/03/04 Vû®Ö
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
//2015/03/12 Vû®Ö
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
//2015/03/12 Vû®Ö
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
				// ´_ÏXÌÝAÇÝÝtOª§ÁÄ¢½ç
				DP_GET_SENS();						/* ´_Ì¾Ý»lði[	*/
				HS_SVCHG_B_TO_A ^= BLK_GEN;
				SVSW_CHG_FLG	^= BLK_GEN;
			}
		}
	}
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

