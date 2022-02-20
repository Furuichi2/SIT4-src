//	*******************************************
//	***					***
//	***	ÉèÅ[ÉNÇíÇÅÇç ÇÖÇòÇîÇÖÇíÇé	***
//	***					***
//	*******************************************
	extern	S4b	seq_ram1_top;

	extern	U2b	SEQ_RUN1[SEQ_STEP_MAX*20+1000];	//; SEQUENCE RUN CODE AREA




	extern	S4b	seq_ram2_top;

//	extern	U2b	SEQ_CARD_RAM[SEQ_CARD_MAX+20];	//; SEQUENCE BIT AREA

//	========== DPRAM -> SDRAM ïœçX 2008-07-30 SAITO ==========
	extern		U2b	SEQ_CARD_RAM[SEQ_CARD_MAX];		//; SEQUENCE BIT AREA
//	==========================================================

//	extern	S4b	SEQ_TMR_DT_TOP;
	extern	U4b	SEQ_TMR_DATA[SEQ_TMR_MAX];	//
//	extern	S4b	SEQ_TMR_DT_END;

//	extern	S4b	SEQ_CTR_DT_TOP;
	extern	U4b	SEQ_CTR_DATA[SEQ_CTR_MAX];	//
//	extern	S4b	SEQ_CTR_DT_END;

	extern	U2b	SEQ_SR_FLG[SEQ_CARD_MAX];	//

	extern	U2b	SEQ_CMP_ERR;			//; CMP OK = BX:0000 , CMP NG = BX:FFFF
	extern	U2b	SEQ_ARG1_DATA;			//; ARG data load
	extern	U2b	SEQ_MRG1_DATA;			//; MRG data load
	extern	U2b	SEQ_NRG1_DATA;			//; NRG data load
	extern	U2b	SEQ_DRG1_DATA;			//; DATA REG data load

	extern	U4b	SEQ_CMP_ERR_ADR;		//;
