;	*******************************************************************
;	***								***
;	***								***
;	***	et1	()						***
;	***	cpu-b	(B500,0C00~B500,0FFF 1024byte)			***
;	***								***
;	***								***
;	*******************************************************************
;	===========================================
;	===		ET1 SV DATA		===
;	===========================================
	.ALIGN	4					;
;	--------------------------------------------------
_ET_CPUB_SND_INI_ET1	.SRES	4			;[PON.CLR]INITAL CODE REQ CPUB->KMT
_ET_CPUB_RCV_INI_ET1	.SRES	4			;[PON.CLR*不要]INITAL CODE ACK

;	===========================================
;	===		ET1 TOREND DATA		===
;	===========================================
	.ALIGN	4					;
;	--------------------------------------------------
_ET_CPUA_SND_INI_ET1	.SRES	4			;[PON.CLR]INITAL CODE REQ CPUA->KMT
_ET_CPUA_RCV_INI_ET1	.SRES	4			;[PON.CLR*不要]INITAL CODE ACK

_ET_CPUA_SND_REQ_ET1	.SRES	4			;[PON.CLR]H'12345678(req)
_ET_CPUA_RCV_ACK_ET1	.SRES	4			;[PON.CLR]H'87654321(ack)
;	---------------------------------------------------
_ET_CPUA_SND_REQ_ADR	.SRES	4			;TOPADRESS (192K+32K 256Kbyte)
_ET_CPUA_SND_REQ_CNT	.SRES	4			;[PON.CLR]1~128個
		.ALIGN	4					;
_ET_CPUA_SND_DAT	.SRES	_ET1_CPUAB_BUF_MAX	;(256byte MAX)
_ET_CPUA_SND_END	.SRES	4			;[[[[[[[[[[[[[[[[[(未使用)]]]]]]]]]]]]]]]]]]]]


;	===================================================
;	===		ET1 loder cmd DATA		===
;	===================================================
;	2006-12-01
	.ALIGN	4					;
_ET_LDCMND_AREA		.SRES	512			;LdCmnd set area
_ET_LDCMND_REQ		.SRES	2			;[PON.CLR]LdCmnd Request Flag
_ET_LDCMND_RES		.SRES	2			;[PON.CLR]LdCmnd Response Flag
_ET1_VER		.SRES	4			;ET1 VERSION	V05

;	===== HMI V05j 2007/12/07 =====
_ET1_IPS_ENT		.SRES	2			;[PON.CLR]IPｱﾄﾞﾚｽ確定
_ET1_IPS_ADR0		.SRES	2			;IPｱﾄﾞﾚｽ
_ET1_IPS_ADR1		.SRES	2			;IPｱﾄﾞﾚｽ
_ET1_IPS_ADR2		.SRES	2			;IPｱﾄﾞﾚｽ
_ET1_IPS_ADR3		.SRES	2			;IPｱﾄﾞﾚｽ
_ET1_SUB_NET0		.SRES	2			;ｻﾌﾞﾈｯﾄﾏｽｸ
_ET1_SUB_NET1		.SRES	2			;ｻﾌﾞﾈｯﾄﾏｽｸ
_ET1_SUB_NET2		.SRES	2			;ｻﾌﾞﾈｯﾄﾏｽｸ
_ET1_SUB_NET3		.SRES	2			;ｻﾌﾞﾈｯﾄﾏｽｸ
_ET1_DEF_GAT0		.SRES	2			;ﾃﾞﾌｫﾙﾄｹﾞｰﾄｳｪｲ
_ET1_DEF_GAT1		.SRES	2			;ﾃﾞﾌｫﾙﾄｹﾞｰﾄｳｪｲ
_ET1_DEF_GAT2		.SRES	2			;ﾃﾞﾌｫﾙﾄｹﾞｰﾄｳｪｲ
_ET1_DEF_GAT3		.SRES	2			;ﾃﾞﾌｫﾙﾄｹﾞｰﾄｳｪｲ
_ET1_IPM_ADR0		.SRES	2			;IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
_ET1_IPM_ADR1		.SRES	2			;IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
_ET1_IPM_ADR2		.SRES	2			;IPｱﾄﾞﾚｽ(ﾓﾆﾀ)
_ET1_IPM_ADR3		.SRES	2			;IPｱﾄﾞﾚｽ(ﾓﾆﾀ)

;	===================================================
;	===	ET1==>CPUA(読出 32BYTE)	ｽﾃｰﾀｽRD		===
;	===	2008-10-20				===
;	===	ﾊﾟｿｺﾝからのWRﾃﾞｰﾀをCPUAが読み出す	===
;	===================================================
;--0F4E
_ET_CPUA_RD_REQ		.SRES	2			;[PON.CLR]①CPUA-->ET1 READ REQ
_ET_CPUA_RD_ACK		.SRES	2			;[PON.CLR]ET1-->CPUA data SET ACK
_ET_CPUA_RD_CNT		.SRES	2			;[PON.CLR]読出個数
	.ALIGN	4					;
_ET_CPUA_RD_ADR		.SRES	4			;読出ｱﾄﾞﾚｽ
_ET_CPUA_RD_BUF		.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
;	===========================================
;	===	CPUA==>書込2(32byte)	ｽﾃｰﾀｽWR	===
;	===	2008-10-20			===
;	===========================================
	.ALIGN	4					;
_ET_CPUA_WR2_ADR	.SRES	4			;STS WR LINE
_ET_CPUA_WR2_BUF	.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
_ET_CPUA_WR2_REQ	.SRES	2			;[PON.CLR]①CPUA-->ET1
_ET_CPUA_WR2_ACK	.SRES	2			;[PON.CLR]
_ET_CPUA_WR2_CNT	.SRES	2			;[PON.CLR]0FA0,FA1

;;;	===========================================
;;;	===	2009-06-19 komtrax(ET2)対応	===
;;;	===========================================
;;;_ET2_SEQ_IDT01		.sres	2			;FA2,3 seq-->et2
;;;_ET2_SEQ_IDT02		.sres	2			;FA4,5 
;;;_ET2_SEQ_QDT01		.sres	2			;FA6,7 et2-->seq
;;;_ET2_SEQ_QDT02		.sres	2			;FA8,9 
;	============== 使用付加(2009-06-19)　後はﾊﾞﾝｸだけ============
;	===========================================
;	===	2009-07-24 komtrax(ET2)対応	===
;	===========================================
;	------------(KOMTRAX空間に対して SIT_MEM)
							;ADR-2byte　ﾃﾞｰﾀ数1個　ﾃﾞｰﾀ長2byte　ﾒﾓﾘ種別32種類
_ET2_SITM_ADR		.SRES	2			;FA2,3 SIT4->ET1  R/W ADR
_ET2_SITM_REQ		.SRES	1			;[PON.CLR]FA4   SIT4->ET1  HND=BIT7 R/W=BIT6(BIT5~BIT0は空間)
_ET2_SITM_ACK		.SRES	1			;[PON.CLR]FA5   SIT4<-ET1
	.ALIGN	2					;
_ET2_SITM_WRDT		.SRES	2			;FA6,7 SIT4->ET1  WR data
_ET2_SITM_RDDT		.SRES	2			;FA8,9(SIT4<-ET1) RD data

_ET2_SEQ_IDT01		.sres	2			;[PON.CLR]FAA,B seq(SQ149)-->et2
_ET2_SEQ_QDT01		.sres	2			;[PON.CLR]FAC,D et2-->seq(SQ86)

;	---cpubはFFAまでで使用不可・・・・後はﾊﾞﾝｸ切替で対応(CPUB hmi_src\fitsrc\ssa_opram.src)---

