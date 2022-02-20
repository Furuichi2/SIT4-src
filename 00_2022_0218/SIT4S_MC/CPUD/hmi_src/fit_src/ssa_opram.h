/***********************************************************************/
/*																		*/
/*	僐儅僣嶻婡噴揳岦偗	俽俬俿亅俽僐儞僩儘乕儔							*/
/*																		*/
/*				僆僾僔儑儞俼俙俵丂掕媊									*/
/*																		*/
/***********************************************************************/
//;
//;	***	LOAD MONITOR IN	***
//;
extern	UNs		CLO_TRK_L[];			//DW	36	DUP(?)		; OVER TORUKU LEFT
extern	UNs		CLO_TRK_R[];			//DW	36	DUP(?)		; OVER TORUKU RIGHT
extern	UNs		CLO_TRK_T[];			//DW	36	DUP(?)		; OVER TORUKU TOTAL

extern	UNs		CLO_GAIN_BAK1L;			//DW	1	DUP(?)		; LEFT GAIN 2000
extern	UNs		CLO_GAIN_BAK1R;			//DW	1	DUP(?)		; RIGHT GAIN 2000
extern	UNs		CLO_GAIN_BAK2L;			//DW	1	DUP(?)		; LEFT GAIN 1500
extern	UNs		CLO_GAIN_BAK2R;			//DW	1	DUP(?)		; RIGHT GAIN 1500
extern	UNs		CLO_GAIN_BAK3L;			//DW	1	DUP(?)		; LEFT GAIN 800
extern	UNs		CLO_GAIN_BAK3R;			//DW	1	DUP(?)		; RIGHT GAIN 800
extern	UNs		CLO_GAIN_BAK4L;			//DW	1	DUP(?)		; LEFT GAIN 400
extern	UNs		CLO_GAIN_BAK4R;			//DW	1	DUP(?)		; RIGHT GAIN 400
extern	UNs		CLO_GAIN_BAK5L;			//DW	1	DUP(?)		; LEFT GAIN 200
extern	UNs		CLO_GAIN_BAK5R;			//DW	1	DUP(?)		; RIGHT GAIN 200
extern	UNb		CLO_OF_BAKL;			//DB	1	DUP(?)		; LEFT OFFSET
extern	UNb		CLO_OF_BAKR;			//DB	1	DUP(?)		; RIGHT OFFSET
extern	UNs		CLO_OF_AVE_BAKL;		//DW	1	DUP(?)		; LEFT OFFSET A/D AVERAGE
extern	UNs		CLO_OF_AVE_BAKR;		//DW	1	DUP(?)		; RIGHT OFFSET A/D AVERAGE
extern	UNs		CLO_OF_AVE_BAKT;		//DW	1	DUP(?)		; TOTAL OFFSET A/D AVERAGE

extern	UNs		CLO_STRAIN_L;			//DW	1	DUP(?)		; MAX STRAIN LEFT
extern	UNs		CLO_STRAIN_R;			//DW	1	DUP(?)		; MAX STRAIN RIGHT
extern	UNs		CLO_STRAIN_T;			//DW	1	DUP(?)		; MAX STRAIN TOTAL (NO USE)

extern	UNs		CLO_MAXLD_L;			//DW	1	DUP(?)		; MAX LOAD LEFT
extern	UNs		CLO_MAXLD_R;			//DW	1	DUP(?)		; MAX LOAD RIGHT
extern	UNs		CLO_MAXLD_T;			//DW	1	DUP(?)		; MAX LOAD TOTAL

extern	UNs		CLO_PROOF_L;			//DW	1	DUP(?)		; MAX PROOF LEFT
extern	UNs		CLO_PROOF_R;			//DW	1	DUP(?)		; MAX PROOF RIGHT
extern	UNs		CLO_PROOF_T;			//DW	1	DUP(?)		; MAX PROOF TOTAL

extern	UNb		CLO_PROOF_SEI;			//DB	1	DUP(?)		; PROOF SEIDO

extern	UNs		CLO_OVER_L;				//DW	1	DUP(?)		; OVER LOAD LEFT
extern	UNs		CLO_OVER_R;				//DW	1	DUP(?)		; OVER LOAD RIGHT
extern	UNs		CLO_OVER_T;				//DW	1	DUP(?)		; OVER LOAD TOTAL

extern	UNs		CLO_LOWER_L;			//DW	1	DUP(?)		; LOWER LIMIT LEFT
extern	UNs		CLO_LOWER_R;			//DW	1	DUP(?)		; LOWER LIMIT RIGHT
extern	UNs		CLO_LOWER_T;			//DW	1	DUP(?)		; LOWER LIMIT TOTAL

extern	UNb		CSET_SET;				//DB	1	DUP(?)		; SYOKI SETTEITI

//;-------------------------------------------------------------------------------------2014/03/17
extern	UNs		CLO_OVER2_L	;			//DW	1	DUP(?)		; OVER LOAD LEFT	嵟彫抣
extern	UNs		CLO_OVER2_R	;			//DW	1	DUP(?)		; OVER LOAD RIGHT	嵟彫抣
extern	UNs		CLO_OVER2_T	;			//DW	1	DUP(?)		; OVER LOAD TOTAL	嵟彫抣
                            
extern	UNs		CLO_LOWER2_L;			//DW	1	DUP(?)		; LOWER LIMIT LEFT	嵟彫抣
extern	UNs		CLO_LOWER2_R;			//DW	1	DUP(?)		; LOWER LIMIT RIGHT	嵟彫抣
extern	UNs		CLO_LOWER2_T;			//DW	1	DUP(?)		; LOWER LIMIT TOTAL	嵟彫抣
                             
extern	UNs		CLO_OVER3_L	;			//DW	1	DUP(?)		; OVER LOAD LEFT	怳暆
extern	UNs		CLO_OVER3_R	;			//DW	1	DUP(?)		; OVER LOAD RIGHT	怳暆
extern	UNs		CLO_OVER3_T	;			//DW	1	DUP(?)		; OVER LOAD TOTAL	怳暆
                            
extern	UNs		CLO_LOWER3_L;			//DW	1	DUP(?)		; LOWER LIMIT LEFT	怳暆
extern	UNs		CLO_LOWER3_R;			//DW	1	DUP(?)		; LOWER LIMIT RIGHT	怳暆
extern	UNs		CLO_LOWER3_T;			//DW	1	DUP(?)		; LOWER LIMIT TOTAL	怳暆
//;-------------------------------------------------------------------------------------

//;
//;	***	POSITINER IN	***
//;
extern	UNl		CPOS_SET_POSI;			//DW	2	DUP(?)		; PO ITIGIME SET DATA
extern	UNl		CPOS_SET_TOPL;			//DW	2	DUP(?)		; TOP LIMIT SET DATA
extern	UNl		CPOS_SET_LOWL;			//DW	2	DUP(?)		; LOW LIMIT SET DATA
extern	UNl		CPOS_SET_MRE;			//DW	2	DUP(?)		; PO MRE SET DATA
extern	UNl		CPOS_SET_STD;			//DW	2	DUP(?)		; PO GENITI SET DATA
extern	UNb		CPOS_SET_UNIT;			//DB	1	DUP(?)		; PO UNIT SET DATA
extern	UNb		CPOS_SET_ALFA;			//DB	1	DUP(?)		; PO ALFA SET DATA
extern	UNb		CPOS_SET_BETA;			//DB	1	DUP(?)		; PO BETA SET DATA
extern	UNb		CPOS_SET_DELTA;			//DB	1	DUP(?)		; PO DELTA SET DATA
extern	UNb		CPOS_SET_GANMA;			//DB	1	DUP(?)		; PO GANMA SET DATA
extern	UNl		CPOS_STD_BAK;			//DD	1	DUP(?)

//;
//;	***	CALENDAR IN	***
//;
extern	UNb		CCALE_IN[];				//DB	16	DUP(?)		; CALENDAR

//;
//;	***	GAMEN IN	***
//;
extern	UNb		CPOS_RQE;				//DB	1	DUP(?)		; SET RQE
extern	UNb		CLO_RQE;				//DB	1	DUP(?)		; RQE
//;
//;	***	SEQ IN	***
//;
extern	UNb		CTLINK_C_OP[];			//DB	64	DUP(?)		; T LINK DATA
//;
//;	***	STATUS IN	***
//;
extern	UNb		CSTATUS_C;				//DB	1	DUP(?)		; LOAD MONITOR STATUS

extern	UNb		CLO_DEG_MRD;			//DB	1	DUP(?)		; CPU-B LOAD DEG DATA READING FLAG 2000-09-04
//;
//;	***	LOAD MONITOR OUT	***
//;
extern	UNs		CLO_DEG_L[];			//DW	151	DUP(?)		; DEG(50~200) GOTO LOAD LEFT
extern	UNs		CLO_DEG_R[];			//DW	151	DUP(?)		; DEG(50~200) GOTO LOAD RIGHT
extern	UNs		CLO_DEG_T[];			//DW	151	DUP(?)		; DEG(50~200) GOTO LOAD TOTAL

extern	UNs		CLO_GAIN_SET1L;			//DW	1	DUP(?)		; LEFT GAIN 2000
extern	UNs		CLO_GAIN_SET1R;			//DW	1	DUP(?)		; RIGHT GAIN 2000
extern	UNs		CLO_GAIN_SET2L;			//DW	1	DUP(?)		; LEFT GAIN 1500
extern	UNs		CLO_GAIN_SET2R;			//DW	1	DUP(?)		; RIGHT GAIN 1500
extern	UNs		CLO_GAIN_SET3L;			//DW	1	DUP(?)		; LEFT GAIN 800
extern	UNs		CLO_GAIN_SET3R;			//DW	1	DUP(?)		; RIGHT GAIN 800
extern	UNs		CLO_GAIN_SET4L;			//DW	1	DUP(?)		; LEFT GAIN 400
extern	UNs		CLO_GAIN_SET4R;			//DW	1	DUP(?)		; RIGHT GAIN 400
extern	UNs		CLO_GAIN_SET5L;			//DW	1	DUP(?)		; LEFT GAIN 200
extern	UNs		CLO_GAIN_SET5R;			//DW	1	DUP(?)		; RIGHT GAIN 200
extern	UNb		CLO_OF_SETL;			//DB	1	DUP(?)		; LEFT OFFSET
extern	UNb		CLO_OF_SETR;			//DB	1	DUP(?)		; RIGHT OFFSET
extern	UNs		CLO_OF_AVE_SETL;		//DW	1	DUP(?)		; LEFT OFFSET A/D AVERAGE
extern	UNs		CLO_OF_AVE_SETR;		//DW	1	DUP(?)		; RIGHT OFFSET A/D AVERAGE
extern	UNs		CLO_OF_AVE_SETT;		//DW	1	DUP(?)		; TOTAL OFFSET A/D AVERAGE

extern	UNs		CLO_OFAD_L;				//DW	1	DUP(?)		; OFFSET DURING A/D DATA LEFT
extern	UNs		CLO_OFAD_R;				//DW	1	DUP(?)		; OFFSET DURING A/D DATA RIGHT
extern	UNs		CLO_OFAD_T;				//DW	1	DUP(?)		; OFFSET DURING A/D DATA TOTAL

extern	UNs		CLO_LOAD_L;				//DW	1	DUP(?)		; LOAD LEFT
extern	UNs		CLO_LOAD_R;				//DW	1	DUP(?)		; LOAD RIGHT
extern	UNs		CLO_LOAD_T;				//DW	1	DUP(?)		; LOAD TOTAL

extern	UNs		CLO_LOAD_KEEP_L;				//嵍		/* V01o */
extern	UNs		CLO_LOAD_KEEP_R;				//塃		/* V01o */
extern	UNs		CLO_LOAD_KEEP_T;				//崌寁		/* V01o */

extern	UNs		CLO_LOAD_LIVE_L;				//嵍		/* V01v */
extern	UNs		CLO_LOAD_LIVE_R;				//塃		/* V01v */
extern	UNs		CLO_LOAD_LIVE_T;				//崌寁		/* V01v */

extern	UNs		CLO_LOAD_L2;					//嵍		/* V01w */
extern	UNs		CLO_LOAD_R2;					//塃		/* V01w */
extern	UNs		CLO_LOAD_T2;					//崌寁		/* V01w */


//;
//;	***	POSITINER OUT	***
//;
extern	UNl		CPOS_NOW_MM;			//DW	2	DUP(?)		; CPU <= NOW POSITION DATA
extern	UNl		CPOS_STD;				//DW	2	DUP(?)		; CPU <= PO GENITI DATA

//;
//;	***	CALENDAR OUT	***
//;
extern	UNb		CCALE_OUT[];			//DB	16	DUP(?)		; 

//;
//;	***	GAMEN OUT	***
//;
extern	UNb		CPOS_CONDI;				//DB	1	DUP(?)		; CPU <= PO CONDITION FLG
extern	UNb		CPOS_ORDER;				//DB	1	DUP(?)		; CPU <= PO TOP,LOW ORDER

extern	UNb		CLO_CONDI;				//DB	1	DUP(?)		; LOAD MONITOR CONDITION
extern	UNb		CLO_LIMERR;				//DB	1	DUP(?)		; OVER LOAD,LOWER LIMIT ERROR
extern	UNb		CLO_SATURATE;			//DB	1	DUP(?)		; VOLTAGE SATURATE

//;
//;	***	SEQ OUT	***
//;
extern	UNb		CTLINK_OP_C[];			//DB	64	DUP(?)		; T LINK DATA OP => CPU

//;
//;	***	STATUS OUT	***
//;
extern	UNb		CCTRL_OP_LO;			//DB	1	DUP(?)		; LOAD MONITOR STATUS
extern	UNb		CCTRL_OP_PO;			//DB	1	DUP(?)		; POSITIONER STATUS
extern	UNb		CCTRL_OP_CALE;			//DB	1	DUP(?)		; CALENDER STATUS
extern	UNb		CCTRL_OP_GAMEN;			//DB	1	DUP(?)		; GAMEN STATUS
extern	UNb		CCTRL_OP_TLINK;			//DB	1	DUP(?)		; TLINK STATUS

extern	UNb		OP_GENITI_READ;			//DB	1	DUP(?)		;'98-07-13/* 尰埵抲僨乕僞撉崬姰椆僼儔僌丂侽俥俥俫亖姰椆 */

extern	UNs		CLO_DEG_CNT;			//DW	1	DUP(?)		;LOAD CHANGE CNT 2000-09-04
extern	UNb		CLO_DEG_OPWR;			//DB	1	DUP(?)		;OP LOAD DEG DATA WRITEING FLAG 2000-09-04

//;
//;	***	ERROR DATA	***
//;
extern	UNb		CPUC_ROM_ER;			//DB	1	DUP(?)		; CPU-C ROM err       (00=OK)
extern	UNb		CPUC_RAM_ER;			//DB	1	DUP(?)		; CPU-C RAM err       (00=OK)
extern	UNb		CPUC_CB1_ER;			//DB	1	DUP(?)		; CPU-C DPRAM1 err    (00=OK)
extern	UNb		CPUC_CB2_ER;			//DB	1	DUP(?)		; CPU-C DPRAM2 err    (00=OK)
extern	UNb		CPUC_OP_ER;				//DB	1	DUP(?)		; CPU-C OP-DPRAM err  (00=OK)
extern	UNb		CPUC_CMP_ER;			//DB	1	DUP(?)		; CPU-C COMPILE err   (00=OK)
extern	UNb		CPUC_PDN_ER;			//DB	1	DUP(?)		; CPU-C POWER DOWN err(00=OK)
extern	UNb		CPUC_079_ER;			//DB	1	DUP(?)		; CPU-C SEQ_079       (00=OK)
extern	UNb		CPUC_077_ER;			//DB	1	DUP(?)		; CPU-C SEQ_077       (00=OK)
extern	UNb		CPUC_160_DT;			//DB	1	DUP(?)		; CPU-C SEQ_160

extern	UNb		V25_OP_0;				//DB	1	DUP(?)		; V25 -> Option(0)
extern	UNb		V25_OP_1;				//DB	1	DUP(?)		; V25 -> Option(1)
extern	UNb		V25_OP_2;				//DB	1	DUP(?)		; V25 -> Option(2)
extern	UNb		V25_OP_3;				//DB	1	DUP(?)		; V25 -> Option(3)
extern	UNb		V25_OP_4;				//DB	1	DUP(?)		; V25 -> Option(4)
extern	UNb		V25_OP_5;				//DB	1	DUP(?)		; V25 -> Option(5)
extern	UNb		V25_OP_6;				//DB	1	DUP(?)		; V25 -> Option(6)
extern	UNb		V25_OP_7;				//DB	1	DUP(?)		; V25 -> Option(7)

extern	UNs		V25_OP_10;				//DW	1	DUP(?)		;V07 /* 僗儔僀僪帺摦挷愡丂堎忢専抦丂堦掕帪娫 */
extern	UNs		V25_OP_11;				//DW	1	DUP(?)		;V07 /* 僗儔僀僪帺摦挷愡丂堎忢専抦丂堦掕嫍棧 */
extern	UNs		V25_OP_12;				//DW	1	DUP(?)		;V07 /* 僗儔僀僪帺摦挷愡丂堎忢専抦丂堦掕梊旛 */

extern	UNb		OP_ERROR1;				//DB	1	DUP(?)		; Option ERROR1	      (00=OK)
extern	UNb		OP_ERROR2;				//DB	1	DUP(?)		; Option ERROR2	      (00=OK)

extern	UNb		OP_VER;					//DB	1	DUP(?)		; Option Ver
extern	UNb		OP_V25_0;				//DB	1	DUP(?)		; Option -> V25(0)
extern	UNb		OP_V25_1;				//DB	1	DUP(?)		; Option -> V25(1)
extern	UNb		OP_V25_2;				//DB	1	DUP(?)		; Option -> V25(2)
extern	UNb		OP_V25_3;				//DB	1	DUP(?)		; Option -> V25(3)
extern	UNb		OP_V25_4;				//DB	1	DUP(?)		; Option -> V25(4)
extern	UNb		OP_V25_5;				//DB	1	DUP(?)		; Option -> V25(5)
extern	UNb		OP_V25_6;				//DB	1	DUP(?)		; Option -> V25(6)
extern	UNb		OP_V25_7;				//DB	1	DUP(?)		; Option -> V25(7)

//;
//;	***	ENCORDER DEG DATA	***
//;
extern	UNs		CENC_DEG;				//DW	1	DUP(?)		; ENCORDER DEG DATA

//;
//;	***	INTERRUPT	***
//;
extern	UNb		RAMOP_C_INT;			//DB	1	DUP(?)		; NO USE

extern	UNb		RAMC_OP_INT;			//DB	1	DUP(?)		; CPU CARD => OP INT ADR

//;	***************************************************
//;	**********	Option CARD STATUS       **********
//;	***************************************************
//;
//;	***	Option status area	***
//;
//V01e	extern	UNb		OP_STATUS;				//DB	1	DUP(?)	; OP偶:00H,OP必(OK):55H,OP必(WDTup):54H
extern	UNb		OP_STATUS_REAL;				//DB	1	DUP(?)	; OP偶:00H,OP必(OK):55H,OP必(WDTup):54H
//;														; Bit7~1:0101010,Bit0:*WDUP
//V05h	extern	UNb		MEM_ARI;				//DB ?			;
extern	UNb		MEM_ARI_REAL;				//DB ?			;

extern	UNb		MEM_BNK_ADR1;			//DB ?			;/*  */

extern	UNb		MEM_BNK_ADR2;			//DB ?			;/*  */

extern	UNb		MEM_DAT_ADR1[];			//DB 512 DUP(?)		;/*  */

extern	UNb		MEM_DAT_ADR2[];			//DB 512 DUP(?)		;/*  */

