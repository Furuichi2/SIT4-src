//	*******************************************
//	***					***
//	***	ÉèÅ[ÉNÇíÇÅÇçíËã`		***
//	***					***
//	*******************************************
#include	"cm_equ1.h"

//#define		SEQ_STEP_MAX	8000	//; 8000STEP
#define		SEQ_STEP_MAX	6000	//; 8000STEP 4K

//#define		SEQ_CARD_MAX	800	//;
#define		SEQ_CARD_MAX	1000	//;2008-08-01(é¿ç€Ç…ÇÕ800wordÇ≈OK)

#define		SEQ_CTR_MAX	32	//;
#define		SEQ_TMR_MAX	96	//;


#pragma section	seqram1	/* æ∏ºÆ›=éûÇÕBwkram1 */
S4b	seq_ram1_top;

S4b	SEQ_RUN1_TOP;
U2b	SEQ_RUN1[SEQ_STEP_MAX*20+1000];	//; SEQUENCE RUN CODE AREA
//	U2b	SEQ_RUN1[8000];	//; SEQUENCE RUN CODE AREA
S4b	SEQ_RUN1_END;				//; 8000STEP*20BYTE+ó]óÕ
						//; 0C0A8000H ~ 0C0D3F20H




#pragma section	seqram2	/* æ∏ºÆ›=éûÇÕBwkram1 */
S4b	seq_ram2_top;

//S4b	SEQ_CARD_RAM_TOP;
//	U2b	SEQ_CARD_RAM[SEQ_CARD_MAX+20];		//; SEQUENCE BIT AREA ÇcÇoÇqÇ`ÇlÇ…Ç∆Ç¡ÇΩ
//S4b	SEQ_CARD_RAM_END;			//;

//	========== DPRAM -> SDRAM ïœçX 2008-07-30 SAITO ==========
	U2b	SEQ_CARD_RAM[SEQ_CARD_MAX];		//; SEQUENCE BIT AREA ÇcÇoÇqÇ`ÇlÇ…Ç∆Ç¡ÇΩ
//	==========================================================

//S4b	SEQ_TMR_DT_TOP;
	U4b	SEQ_TMR_DATA[SEQ_TMR_MAX];	//
//S4b	SEQ_TMR_DT_END;

//S4b	SEQ_CTR_DT_TOP;
	U4b	SEQ_CTR_DATA[SEQ_CTR_MAX];	//
//S4b	SEQ_CTR_DT_END;



	U2b	SEQ_SR_FLG[SEQ_CARD_MAX];	//


	U2b	SEQ_CMP_ERR;			//; CMP OK = BX:0000 , CMP NG = BX:FFFF
	U2b	SEQ_ARG1_DATA;			//; ARG data load
	U2b	SEQ_MRG1_DATA;			//; MRG data load
	U2b	SEQ_NRG1_DATA;			//; NRG data load
	U2b	SEQ_DRG1_DATA;			//; DATA REG data load

	U4b	SEQ_CMP_ERR_ADR;		//;


