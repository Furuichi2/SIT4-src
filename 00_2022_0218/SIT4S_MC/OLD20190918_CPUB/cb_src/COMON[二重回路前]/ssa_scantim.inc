;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	max
;	SET-UPÅ@⁄ÕﬁŸ+RESET

	.IMPORT	_IDO_BUF_SRC2B_TOTAL_4B_CAL
	.IMPORT	_SH2_MAIN_CLK
	.IMPORT	_SH2_SCAN_REALMAX	;F2
	.IMPORT	_SH2_SCAN_AVLMAX	;F4
	.IMPORT	_SH2_SCAN_AVLPV		;F6
	
_CPU_MAIN_SCAN_CALC:
	SUB_START

	MOV.L	#_SCAN_TIM_IN,R1		;
	MOV.W	@R1,R0				;
	ADD	#1,R0				;
	MOV.W	R0,@R1				;


	MOV.L	#_SH2_MAIN_CLK,R5		;CPUB
;;;;;	MOV.L	#_MAIN_CLK,R5			;CPUA

	MOV.W	@R5,R0				;
	MOV.L	#_CHK_CLK_SIG,R6		;
	MOV.W	@R6,R2				;
	MOV.W	R0,@R6				;

	XOR	R2,R0				;
	TST	#BIT0,R0			;
	TST_BIT_OF CPU_MAIN_SCANCAL300		;

	MOV.L	#_SCAN_TIM_IN,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_WPV_SCAN_TIM_REAL,R3		;[REAL]
	MOV.W	R2,@R3				;
	XOR	R0,R0				;
	MOV.W	R0,@R1				;TIM CLR

	MOV.L	#_SCAN_TIM_TOTAL,R5		;
	MOV.L	#_SCAN_TIM_IDOBUF,R0		;//
	MOV.L	#_SCAN_TIM_POINT,R3		;
	MOV.W	#D'10,R4			;ïΩãœå¬êî MAX
	FAR_JSR	#_IDO_BUF_SRC2B_TOTAL_4B_CAL,R1	;
	MOV.L	#_WPV_SCAN_TIM_AVL,R1		;[AVL]
	MOV.W	R2,@R1				;



	MOV.L	#_WPV_SCAN_TIM_REAL,R1		;[REAL]
	MOV.W	@R1,R2				;
	MOV.L	#_WPV_SCAN_MAX01,R1		;
	MOV.W	@R1,R0				;
	CMP/HS	R2,R0				;R2=<R0
	BT	CPU_MAIN_SCANCAL100		;
	MOV.W	R2,@R1				;
CPU_MAIN_SCANCAL100:

	MOV.L	#_WPV_SCAN_TIM_AVL,R1		;[AVL]
	MOV.W	@R1,R2				;
	MOV.L	#_WPV_SCAN_MAX10,R1		;
	MOV.W	@R1,R0				;
	CMP/HS	R2,R0				;R2=<R0
	BT	CPU_MAIN_SCANCAL200		;
	MOV.W	R2,@R1				;
CPU_MAIN_SCANCAL200:
	NOP
CPU_MAIN_SCANCAL300:

	MOV.L	#_di1_cb_ctl1_on,R1			;//
	MOV.W	@R1,R0					;(¥ØºﬁÇÃèÍçá,Ç‹Çæº∞π›ΩÇ©ÇÁÇÃEMGéwóﬂÇÕOFFÇµÇ»Ç¢)
	MOV.W	#_W1RST,R4				;ÿæØƒñt
	TST	R4,R0					;
	TST_BIT_OF CPU_MAIN_SCANCAL400			;

	XOR	R0,R0				;
	MOV.L	#_WPV_SCAN_MAX01,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_WPV_SCAN_MAX10,R1		;
	MOV.W	R0,@R1				;



CPU_MAIN_SCANCAL400:

	MOV.L	#_WPV_SCAN_MAX01,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_SH2_SCAN_REALMAX,R1		;
	MOV.W	R2,@R1				;

	MOV.L	#_WPV_SCAN_MAX10,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_SH2_SCAN_AVLMAX,R1		;F4
	MOV.W	R2,@R1				;

	MOV.L	#_WPV_SCAN_TIM_AVL,R1		;[AVL]
	MOV.W	@R1,R2				;
	MOV.L	#_SH2_SCAN_AVLPV,R1		;F6
	MOV.W	R2,@R1				;

;	------------- DEBUG ----------
	MOV.L	#_CHK_CLK_SIG,R6		;
	MOV.W	@R6,R2				;
	MOV.L	#(_SQ_CBWK_TOP+_WKSQCB240),R6	;
	MOV.W	R2,@R6				; SEQ SET

	SUB_END
	M_RTS

