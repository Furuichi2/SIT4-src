;	***************************************************
;	***						***
;	***						***
;	***	ハードの違いを補うソフト		***
;	***						***
;	***						***
;	***************************************************
;	*******************************************
;	***					***
;	***	位置決めLSI現在ｶｳﾝﾀﾗｯﾁ		***
;	***					***
;	*******************************************
	.IMPORT	_PDTRB
	.IMPORT	_PV1_SCRW_POS				
	.ALIGN	4						;
_POS_LSI_DT_LATCH:				;
	SUB_START

	FAR_JSR	#_POS_LSI_DT_LATCH_OF,R0	;


	FAR_JSR	#_POS_LSI_DT_LATCH_ON,R0	;


	FAR_JSR	#_POS_LSI_DT_LATCH_OF,R0	;

;;	DI_PUSH_SR_SHn	WK_REG1=R5,WK_REG2=R6					;
;;	MOV.L	#_PDTRB,R1			; PORT17
;;	MOV.W	@R1,R0
;;	MOV	#BIT1,R3
;;	OR	R3,R0
;;	MOV.W	R0,@R1
;;	NOP
;;	NOP
;;	NOT	R3,R3	;
;;	AND	R3,R0	;
;;	MOV.W	R0,@R1
;;	EI_POP_SR_SHn 								;

	SUB_END					;
	M_RTS					;


_POS_LSI_DT_LATCH_ON:				;
	SUB_START

	MOV.L	#_PDTRB,R1			; PORT17
	MOV.W	@R1,R0
	MOV	#BIT1,R3
	OR	R3,R0
	MOV.W	R0,@R1

	SUB_END					;
	M_RTS					;


_POS_LSI_DT_LATCH_OF:				;
	SUB_START

	MOV.L	#_PDTRB,R1			; PORT17
	MOV.W	@R1,R0
	MOV	#BIT1,R3
	NOT	R3,R3
	AND	R3,R0
	MOV.W	R0,@R1

	SUB_END					;
	M_RTS					;




