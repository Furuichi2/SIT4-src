//;	***************************************************
//;	***		SH7727 ڼ޽?							***
//;	***************************************************

	extern	U4b	INTEVT2		; // .SRES	4			; A4000000
	extern	U2b	IRR0		; // .SRES	2			; A4000004
	extern	U2b	IRR1		; // .SRES	2			; A4000006
	extern	U2b	IRR2		; // .SRES	2			; A4000008
	extern	U2b	ICR1		; // .SRES	2			; A4000010
	extern	U2b	ICR2		; // .SRES	2			; A4000012
	extern	U2b	PINTER		; // .SRES	2			; A4000014
	extern	U2b	IPRC		; // .SRES	2			; A4000016
	extern	U2b	IPRD		; // .SRES	2			; A4000018
	extern	U2b	IPRE		; // .SRES	2			; A400001A
	extern	U4b	SAR0		; // .SRES	4			; A4000020
	extern	U4b	DAR0		; // .SRES	4			; A4000024
	extern	U4b	DMATCR0		; // .SRES	4			; A4000028
	extern	U4b	CHCR0		; // .SRES	4			; A400002C
	extern	U4b	SAR1		; // .SRES	4			; A4000030
	extern	U4b	DAR1		; // .SRES	4			; A4000034
	extern	U4b	DMATCR1		; // .SRES	4			; A4000038
	extern	U4b	CHCR1		; // .SRES	4			; A400003C
	extern	U4b	SAR2		; // .SRES	4			; A4000040
	extern	U4b	DAR2		; // .SRES	4			; A4000044
	extern	U4b	DMATCR2		; // .SRES	4			; A4000048
	extern	U4b	CHCR2		; // .SRES	4			; A400004C
	extern	U4b	SAR3		; // .SRES	4			; A4000050
	extern	U4b	DAR3		; // .SRES	4			; A4000054
	extern	U4b	DMATCR3		; // .SRES	4			; A4000058
	extern	U4b	CHCR3		; // .SRES	4			; A400005C
	extern	U2b	DMAOR		; // .SRES	2			; A4000060
	extern	U2b	CMSTR		; // .SRES	2			; A4000070
	extern	U2b	CMCSR		; // .SRES	2			; A4000072
	extern	U2b	CMCNT		; // .SRES	2			; A4000074
	extern	U2b	CMCOR		; // .SRES	2			; A4000076
	extern	U1b	ADDRAH		; // .SRES	1			; A4000080
	extern	U1b	ADDRAL		; // .SRES	1			; A4000082
	extern	U1b	ADDRBH		; // .SRES	1			; A4000084
	extern	U1b	ADDRBL		; // .SRES	1			; A4000086
	extern	U1b	ADDRCH		; // .SRES	1			; A4000088
	extern	U1b	ADDRCL		; // .SRES	1			; A400008A
	extern	U1b	ADDRDH		; // .SRES	1			; A400008C
	extern	U1b	ADDRDL		; // .SRES	1			; A400008E
	extern	U1b	ADCSR		; // .SRES	1			; A4000090
	extern	U1b	ADCR		; // .SRES	1			; A4000092
	extern	U1b	DADR0		; // .SRES	1			; A40000A0
	extern	U1b	DADR1		; // .SRES	1			; A40000A2
	extern	U1b	DACR1		; // .SRES	1			; A40000A4
	extern	U4b	CCR2		; // .SRES	4			; A40000B0
	extern	U2b	SIMDR		; // .SRES	2			; A40000C0
	extern	U2b	SISCR		; // .SRES	2			; A40000C2
	extern	U2b	SITDAR		; // .SRES	2			; A40000C4
	extern	U2b	SIRDAR		; // .SRES	2			; A40000C6
	extern	U2b	SICDAR		; // .SRES	2			; A40000C8
	extern	U2b	SICTR		; // .SRES	2			; A40000CC
	extern	U2b	SIFCTR		; // .SRES	2			; A40000D0
	extern	U2b	SISTR		; // .SRES	2			; A40000D4
	extern	U2b	SIIER		; // .SRES	2			; A40000D6
	extern	U4b	SITDR		; // .SRES	4			; A40000E0
	extern	U4b	SIRDR		; // .SRES	4			; A40000E4
	extern	U4b	SITCR		; // .SRES	4			; A40000E8
	extern	U4b	SIRCR		; // .SRES	4			; A40000EC
	extern	U2b	SITMR		; // .SRES	2			; A40000FC
	extern	U2b	SIFPR		; // .SRES	2			; A40000FE
	extern	U2b	PACR		; // .SRES	2			; A4000100
	extern	U2b	PBCR		; // .SRES	2			; A4000102
	extern	U2b	PCCR		; // .SRES	2			; A4000104
	extern	U2b	PDCR		; // .SRES	2			; A4000106
	extern	U2b	PECR		; // .SRES	2			; A4000108
	extern	U2b	PFCR		; // .SRES	2			; A400010A
	extern	U2b	PGCR		; // .SRES	2			; A400010C
	extern	U2b	PHCR		; // .SRES	2			; A400010E
	extern	U2b	PJCR		; // .SRES	2			; A4000110
	extern	U2b	PKCR		; // .SRES	2			; A4000112
	extern	U2b	PLCR		; // .SRES	2			; A4000114
	extern	U2b	SCPCR		; // .SRES	2			; A4000116
	extern	U2b	PMCR		; // .SRES	2			; A4000118
	extern	U1b	PADR		; // .SRES	1			; A4000120
	extern	U1b	PBDR		; // .SRES	1			; A4000122
	extern	U1b	PCDR		; // .SRES	1			; A4000124
	extern	U1b	PDDR		; // .SRES	1			; A4000126
	extern	U1b	PEDR		; // .SRES	1			; A4000128
	extern	U1b	PFDR		; // .SRES	1			; A400012A
	extern	U1b	PGDR		; // .SRES	1			; A400012C
	extern	U1b	PHDR		; // .SRES	1			; A400012E
	extern	U1b	PJDR		; // .SRES	1			; A4000130
	extern	U1b	PKDR		; // .SRES	1			; A4000132
	extern	U1b	PLDR		; // .SRES	1			; A4000134
	extern	U1b	SCPDR		; // .SRES	1			; A4000136
	extern	U1b	PMDR		; // .SRES	1			; A4000138
	extern	U1b	SCSMR2		; // .SRES	1			; A4000150
	extern	U1b	SCBRR2		; // .SRES	1			; A4000152
	extern	U1b	SCSCR2		; // .SRES	1			; A4000154
	extern	U1b	SCFTDR2		; // .SRES	1			; A4000156
	extern	U2b	SCSSR2		; // .SRES	2			; A4000158
	extern	U1b	SCFRDR2		; // .SRES	1			; A400015A
	extern	U1b	SCFCR2		; // .SRES	1			; A400015C
	extern	U2b	SCFDR2		; // .SRES	2			; A400015E
	extern	U1b	PCC0ISR		; // .SRES	1			; A4000160
	extern	U1b	PCC0GCR		; // .SRES	1			; A4000162
	extern	U1b	PCC0CSCR	; // .SRES	1			; A4000164
	extern	U1b	PCC0CSCIER	; // .SRES	1			; A4000166
	extern	U2b	ACTR1		; // .SRES	2			; A4000180
	extern	U2b	ACTR2		; // .SRES	2			; A4000182
	extern	U2b	ASTR1		; // .SRES	2			; A4000184
	extern	U2b	ASTR2		; // .SRES	2			; A4000186
	extern	U2b	MRCR		; // .SRES	2			; A4000188
	extern	U2b	MPCR		; // .SRES	2			; A400018A
	extern	U2b	DPNQ		; // .SRES	2			; A400018C
	extern	U2b	RCNT		; // .SRES	2			; A400018E
	extern	U2b	ACDR		; // .SRES	2			; A4000190
	extern	U2b	ASDR		; // .SRES	2			; A4000192
	extern	U2b	TDFP		; // .SRES	2			; A4000194
	extern	U2b	RDFP		; // .SRES	2			; A4000198
	extern	U2b	SDIR		; // .SRES	2			; A4000200
	extern	U4b	SDDR_SDDRH	; // .SRES	4			; A4000208
	extern	U2b	SDDRL		; // .SRES	2			; A400020A
	extern	U2b	IPRF		; // .SRES	2			; A4000220
	extern	U2b	IPRG		; // .SRES	2			; A4000222
	extern	U2b	IPR3		; // .SRES	2			; A4000224
	extern	U2b	IPR4		; // .SRES	2			; A4000226
	extern	U2b	ICR3		; // .SRES	2			; A4000228
	extern	U2b	CHRAR		; // .SRES	2			; A400022A
	extern	U1b	STBCR3		; // .SRES	1			; A4000230
	extern	U1b	SRSTR		; // .SRES	1			; A4000232
	extern	U2b	EXPFC		; // .SRES	2			; A4000234
	extern	U1b	EXCPGCR		; // .SRES	1			; A4000236
	extern	U1b	CKIO2CR		; // .SRES	1			; A400023A
	extern	U1b	USBIFR0		; // .SRES	1			; A4000240
	extern	U1b	USBIFR1		; // .SRES	1			; A4000241
	extern	U1b	USBEPDR0I	; // .SRES	1			; A4000242
	extern	U1b	USBEPDR0O	; // .SRES	1			; A4000243
	extern	U1b	USBTFG		; // .SRES	1			; A4000244
	extern	U1b	USBFCLR		; // .SRES	1			; A4000245
	extern	U1b	USBEPSZ0O	; // .SRES	1			; A4000246
	extern	U1b	USBEPDR0S	; // .SRES	1			; A4000247
	extern	U1b	USBDASTS	; // .SRES	1			; A4000248
	extern	U1b	USBEPDR2	; // .SRES	1			; A4000249
	extern	U1b	USBISR0		; // .SRES	1			; A400024A
	extern	U1b	USBEPSTL	; // .SRES	1			; A400024B
	extern	U1b	USBIER0		; // .SRES	1			; A400024C
	extern	U1b	USBIER1		; // .SRES	1			; A400024D
	extern	U1b	USBEPDR1	; // .SRES	1			; A400024E
	extern	U1b	USBEPSZ1	; // .SRES	1			; A400024F
	extern	U1b	USBISR1		; // .SRES	1			; A4000250
	extern	U1b	USBDMA		; // .SRES	1			; A4000251
	extern	U1b	USBEPDR3	; // .SRES	1			; A4000252
	extern	U4b	USBHR		; // .SRES	4			; A4000400
	extern	U4b	USBHC		; // .SRES	4			; A4000404
	extern	U4b	USBHCS		; // .SRES	4			; A4000408
	extern	U4b	USBHIS		; // .SRES	4			; A400040C
	extern	U4b	USBHIE		; // .SRES	4			; A4000410
	extern	U4b	USBHID		; // .SRES	4			; A4000414
	extern	U4b	USBHHCCA	; // .SRES	4			; A4000418
	extern	U4b	USBHPCED	; // .SRES	4			; A400041C
	extern	U4b	USBHCHED	; // .SRES	4			; A4000420
	extern	U4b	USBHCCED	; // .SRES	4			; A4000424
	extern	U4b	USBHBHED	; // .SRES	4			; A4000428
	extern	U4b	USBHBCED	; // .SRES	4			; A400042C
	extern	U4b	USBHDHED	; // .SRES	4			; A4000430
	extern	U4b	USBHFI		; // .SRES	4			; A4000434
	extern	U4b	USBHFR		; // .SRES	4			; A4000438
	extern	U4b	USBHFN		; // .SRES	4			; A400043C
	extern	U4b	USBHPS		; // .SRES	4			; A4000440
	extern	U4b	USBHLST		; // .SRES	4			; A4000444
	extern	U4b	USBHRDA		; // .SRES	4			; A4000448
	extern	U4b	USBHRDB		; // .SRES	4			; A400044C
	extern	U4b	USBHRS		; // .SRES	4			; A4000450
	extern	U4b	USBHRPS1	; // .SRES	4			; A4000454
	extern	U4b	USBHRPS2	; // .SRES	4			; A4000458
	extern	U4b	LDPR00[256]	; // .SRES	4			; A4000800
	extern	U2b	LDICKR		; // .SRES	2			; A4000C00
	extern	U2b	LDMTR		; // .SRES	2			; A4000C02
	extern	U2b	LDDFR		; // .SRES	2			; A4000C04
	extern	U2b	LDSMR		; // .SRES	2			; A4000C06
	extern	U4b	LDSARU		; // .SRES	4			; A4000C08
	extern	U4b	LDSARL		; // .SRES	4			; A4000C0C
	extern	U2b	LDLAOR		; // .SRES	2			; A4000C10
	extern	U2b	LDPALCR		; // .SRES	2			; A4000C12
	extern	U2b	LDHCNR		; // .SRES	2			; A4000C14
	extern	U2b	LDHSYNR		; // .SRES	2			; A4000C16
	extern	U2b	LDVDLNR		; // .SRES	2			; A4000C18
	extern	U2b	LDVTLNR		; // .SRES	2			; A4000C1A
	extern	U2b	LDVSYNR		; // .SRES	2			; A4000C1C
	extern	U2b	LDACLNR		; // .SRES	2			; A4000C1E
	extern	U2b	LDINTR		; // .SRES	2			; A4000C20
	extern	U2b	LDPMMR		; // .SRES	2			; A4000C24
	extern	U2b	LDPSPR		; // .SRES	2			; A4000C26
	extern	U2b	LDCNTR		; // .SRES	2			; A4000C28
	extern	U1b	SMR0		; // .SRES	1			; FFFFFE80
	extern	U1b	BRR0		; // .SRES	1			; FFFFFE82
	extern	U1b	SCR0		; // .SRES	1			; FFFFFE84
	extern	U1b	TDR0		; // .SRES	1			; FFFFFE86
	extern	U1b	SSR0		; // .SRES	1			; FFFFFE88
	extern	U1b	RDR0		; // .SRES	1			; FFFFFE8A
	extern	U1b	SCSCMR		; // .SRES	1			; FFFFFE8C
	extern	U1b	TSTR		; // .SRES	1			; FFFFFE92
	extern	U4b	TCOR0		; // .SRES	4			; FFFFFE94
	extern	U4b	TCNT0		; // .SRES	4			; FFFFFE98
	extern	U2b	TCR0		; // .SRES	2			; FFFFFE9C
	extern	U4b	TCOR1		; // .SRES	4			; FFFFFEA0
	extern	U4b	TCNT1		; // .SRES	4			; FFFFFEA4
	extern	U2b	TCR1		; // .SRES	2			; FFFFFEA8
	extern	U4b	TCOR2		; // .SRES	4			; FFFFFEAC
	extern	U4b	TCNT2		; // .SRES	4			; FFFFFEB0
	extern	U2b	TCR2		; // .SRES	2			; FFFFFEB4
	extern	U1b	R64CNT		; // .SRES	1			; FFFFFEC0
	extern	U1b	RSECCNT		; // .SRES	1			; FFFFFEC2
	extern	U1b	RMINCNT		; // .SRES	1			; FFFFFEC4
	extern	U1b	RHRCNT		; // .SRES	1			; FFFFFEC6
	extern	U1b	RWKCNT		; // .SRES	1			; FFFFFEC8
	extern	U1b	RDAYCNT		; // .SRES	1			; FFFFFECA
	extern	U1b	RMONCNT		; // .SRES	1			; FFFFFECC
	extern	U1b	RYRCNT		; // .SRES	1			; FFFFFECE
	extern	U1b	RSECAR		; // .SRES	1			; FFFFFED0
	extern	U1b	RMINAR		; // .SRES	1			; FFFFFED2
	extern	U1b	RHRAR		; // .SRES	1			; FFFFFED4
	extern	U1b	RWKAR		; // .SRES	1			; FFFFFED6
	extern	U1b	RDAYAR		; // .SRES	1			; FFFFFED8
	extern	U1b	RMONAR		; // .SRES	1			; FFFFFEDA
	extern	U1b	RCR1		; // .SRES	1			; FFFFFEDC
	extern	U1b	RCR2		; // .SRES	1			; FFFFFEDE
	extern	U2b	ICR0		; // .SRES	2			; FFFFFEE0
	extern	U2b	IPRA		; // .SRES	2			; FFFFFEE2
	extern	U2b	IPRB		; // .SRES	2			; FFFFFEE4
	extern	U2b	BCR1		; // .SRES	2			; FFFFFF60
	extern	U2b	BCR2		; // .SRES	2			; FFFFFF62
	extern	U2b	WCR1		; // .SRES	2			; FFFFFF64
	extern	U2b	WCR2		; // .SRES	2			; FFFFFF66
	extern	U2b	MCR			; // .SRES	2			; FFFFFF68
	extern	U2b	PCR			; // .SRES	2			; FFFFFF6C
	extern	U2b	RTCSR		; // .SRES	2			; FFFFFF6E
	extern	U2b	RTCNT		; // .SRES	2			; FFFFFF70
	extern	U2b	RTCOR		; // .SRES	2			; FFFFFF72
	extern	U2b	RFCR		; // .SRES	2			; FFFFFF74
	extern	U2b	FRQCR		; // .SRES	2			; FFFFFF80
	extern	U1b	STBCR		; // .SRES	1			; FFFFFF82
	extern	U1b	WTCNT		; // .SRES	1			; FFFFFF84
	extern	U1b	WTCSR		; // .SRES	1			; FFFFFF86
	extern	U1b	STBCR2		; // .SRES	1			; FFFFFF88
	extern	U4b	BDRB		; // .SRES	4			; FFFFFF90
	extern	U4b	BDMRB		; // .SRES	4			; FFFFFF94
	extern	U4b	BRCR		; // .SRES	4			; FFFFFF98
	extern	U2b	BETR		; // .SRES	2			; FFFFFF9C
	extern	U4b	BARB		; // .SRES	4			; FFFFFFA0
	extern	U4b	BAMRB		; // .SRES	4			; FFFFFFA4
	extern	U2b	BBRB		; // .SRES	2			; FFFFFFA8
	extern	U4b	BRSR		; // .SRES	4			; FFFFFFAC
	extern	U4b	BARA		; // .SRES	4			; FFFFFFB0
	extern	U4b	BAMRA		; // .SRES	4			; FFFFFFB4
	extern	U2b	BBRA		; // .SRES	2			; FFFFFFB8
	extern	U4b	BRDR		; // .SRES	4			; FFFFFFBC
	extern	U4b	TRA			; // .SRES	4			; FFFFFFD0
	extern	U4b	EXPEVT		; // .SRES	4			; FFFFFFD4
	extern	U4b	INTEVT		; // .SRES	4			; FFFFFFD8
	extern	U4b	MMUCR		; // .SRES	4			; FFFFFFE0
	extern	U1b	BASRA		; // .SRES	1			; FFFFFFE4
	extern	U1b	BASRB		; // .SRES	1			; FFFFFFE8
	extern	U4b	CCR			; // .SRES	4			; FFFFFFEC
	extern	U4b	PTEH		; // .SRES	4			; FFFFFFF0
	extern	U4b	PTEL		; // .SRES	4			; FFFFFFF4
	extern	U4b	TTB			; // .SRES	4			; FFFFFFF8
	extern	U4b	TEA			; // .SRES	4			; FFFFFFFC
