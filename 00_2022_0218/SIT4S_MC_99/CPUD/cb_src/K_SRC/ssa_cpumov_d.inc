;	*******************************************
;	***					***
;	***		CPUD側の送信ソフト	***
;	***					***
;	*******************************************
	.GLOBAL		_CPUDTOA_DAT1_REQADR	;TOP-ADR 2013-12[MC]
	.GLOBAL		_CPUDTOA_DAT1_REQKND	;種別	2013-12[MC]
	.GLOBAL		_CPUDTOA_DAT1_REQCNT	;個数	2013-12[MC]
	.GLOBAL		_CPUDTOA_DAT1_REQCOD	;WR	2013-12[MC]
	.GLOBAL		_CPUDTOA_DAT1_ACKCOD	;ACK	2013-12[MC]
	.GLOBAL		_CPUDTOA_DAT1_DATTOP	;256BYTE(128W)	2013-12[MC]

;	*******************************************
;	***					***
;	***	とりあえずｽﾅｯﾌﾟ送信,受信	***
;	***	CPUD==>CPUA			***
;	*******************************************
	.IMPORT		_GAM_COPY_STS		;

_SND_DTOA_EVENT_CHK:
	SUB_START

	MOV.L	#_GAM_COPY_STS,R5		;
	MOV.W	@R5,R0				;
	MOV.W	#BIT1,R4			;
	TST	R4,R0				;
	TST_BIT_OF SND_DTOA_EVENTCHK_EXT	;
	NOT	R4,R4				;
	AND	R4,R0				;
	MOV.W	R0,@R5				;

	MOV.W	#BIT0,R0
	MOV.L	#_CPUDX_MEM1_SNDEVN,R1;		//EVNT BIT0:KIND
	MOV.W	R0,@R1				;

SND_DTOA_EVENTCHK_EXT:

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***		CPUB側のﾒｲﾝ		***
;	***					***
;	*******************************************
_SND_DTOA_CPUDMEMX:
	SUB_START
	MOV.L	#_CPUDX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON SND_DTOA_DMEMX100		;

	MOV.L	#_CPUDX_MEM1_SNDEVN,R4		;//EVNT BIT0:KIND
	MOV.W	@R4,R2				;
	TST	R2,R2				;
	TST_BIT_ON SND_DTOA_DMEMX050		;

	FAR_JSR	#_SND_DTOA_EVENT_CHK,R0

	M_BRA	SND_DTOA_DMEMXEXT		;

SND_DTOA_DMEMX050

	MOV.L	#_CPUDX_MEM1_SNDEVN,R1		;//EVNT BIT0:KIND
	MOV.W	@R1,R0				;
	MOV.L	#_CPUDX_MEM1_SNDKND,R1		;//KIND
	MOV.W	R0,@R1				;

;;;;;;;;;	MOV.L	#_W_PARAM_TOP,R0	;
	MOV.L	#H'AC300000,R0			;固定ｱﾄﾞﾚｽ
	MOV.L	#_CPUDX_SEND_TOPADR,R1		;
	MOV.L	R0,@R1				;

	MOV.L	#(640*480)/2,R0			;
	MOV.L	#_CPUDX_SEND_MAXCNT,R1		;WORD個数
	MOV.L	R0,@R1				;

	XOR	R0,R0
	MOV.L	#_CPUDX_SEND_NOWCNT,R1		;
	MOV.L	R0,@R1				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUDX_MEM1_SNDFLG,LG=W,BIT=BIT0,WKREG=R1	;
SND_DTOA_DMEMX100


	MOV.L	#_CPUDX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;BIT0:ACTIVE BIT1:OF->ON(ﾃﾞｰﾀｾｯﾄ) BIT2:ON->OF BIT6:

	TST	#BIT2,R0			;
	TST_BIT_ON SND_DTOA_DMEMX400		;OFF待ち

	TST	#BIT1,R0			;
	TST_BIT_ON SND_DTOA_DMEMX300		;ON待ち

;	------- ﾃﾞｰﾀｾｯﾄ----------

	FAR_JSR	#_SND_DTOA_DMEM_DSET,R0

	MOV.W	#BIT15,R4		;
	TST	R4,R7			;
	TST_BIT_OF SND_DTOA_DMEMX150	;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUDX_MEM1_SNDFLG,LG=W,BIT=BIT6,WKREG=R1	;

SND_DTOA_DMEMX150

;	--------------------------
	MOV.W	#_START_REQ_COD,R0		;
	MOV.L	#_CPUDTOA_DAT1_REQCOD,R6	;ﾊﾝﾄﾞｼｪｲｸON
	MOV.W	R0,@R6				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUDX_MEM1_SNDFLG,LG=W,BIT=BIT1,WKREG=R1	;
	M_BRA	SND_DTOA_DMEMXEXT						;

SND_DTOA_DMEMX300
;	------- 相手側のON待ち-----
	MOV.L	#_CPUDTOA_DAT1_ACKCOD,R6	;
	MOV.W	@R6,R0				;
	MOV.W	#_START_ACK_COD,R4		;
	CMP/EQ	R4,R0				;
	BF	SND_DTOA_DMEMXEXT		;相手側ｺｰﾄﾞON? NO

	XOR	R0,R0				;
	MOV.L	#_CPUDTOA_DAT1_REQCOD,R6	;ﾊﾝﾄﾞｼｪｲｸ自分OFF
	MOV.W	R0,@R6				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUDX_MEM1_SNDFLG,LG=W,BIT=BIT2,WKREG=R1	;
	M_BRA	SND_DTOA_DMEMXEXT						;
SND_DTOA_DMEMX400

;	------- 相手側のOFF待ち------
	MOV.L	#_CPUDTOA_DAT1_ACKCOD,R6	;
	MOV.W	@R6,R0				;
	TST	R0,R0
	TST_BIT_ON SND_DTOA_DMEMXEXT		;相手側ｺｰﾄﾞOFF?  NO

;	-----------------------------
	MOV.L	#_CPUDX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;BIT0:ACTIVE BIT1:OF->ON(ﾃﾞｰﾀｾｯﾄ) BIT2:ON->OF BIT6:
	TST	#BIT6,R0			;最後のﾃﾞｰﾀだったか?
	TST_BIT_ON SND_DTOA_DMEMX500		;YES

	AND	#BIT0,R0			;BIT0以外:OFF
	MOV.W	R0,@R1				;NEXT
	M_BRA	SND_DTOA_DMEMXEXT		;


;	------------- 終了------------
SND_DTOA_DMEMX500
	XOR	R0,R0
	MOV.L	#_CPUDX_MEM1_SNDFLG,R1		;
	MOV.W	R0,@R1				;

	MOV.L	#_CPUDTOA_DAT1_REQCNT,R6	;
	MOV.W	R0,@R6				;

	MOV.L	#_CPUDTOA_DAT1_REQKND,R6	;
	MOV.W	R0,@R6

	MOV.L	#_CPUDTOA_DAT1_REQADR,R6	;
	MOV.L	R0,@R6				;

	MOV.L	#_CPUDTOA_DAT1_REQCOD,R6	;ﾊﾝﾄﾞｼｪｲｸ
	MOV.W	R0,@R6				;

	XOR	R0,R0
	MOV.L	#_CPUDX_MEM1_SNDEVN,R1		;//EVNT BIT0:KIND
	MOV.W	R0,@R1				;

SND_DTOA_DMEMXEXT
	SUB_END
	M_RTS



;
;
;
;
;	ANS R7
_SND_DTOA_DMEM_DSET:
	SUB_START

	XOR	R7,R7

	MOV.L	#_CPUDX_SEND_MAXCNT,R1		;
	MOV.L	@R1,R2				;

	MOV.L	#_CPUDX_SEND_NOWCNT,R1		;ﾜｰﾄﾞ個数
	MOV.L	@R1,R3				;
	SUB	R3,R2				;
	CMP/PL	R2				;
	BT	SND_DTOA_DMEMDSET_100		;
	XOR	R2,R2				;DATA 無し[0]個でﾊﾝﾄﾞｼｪｲｸ
	MOV.W	#BIT15,R7			;END
	M_BRA	SND_DTOA_DMEMDSET_150		;


SND_DTOA_DMEMDSET_100:
	MOV.L	#_CPUDTOA_DAT1_REQADR,R6	;
	MOV.L	R3,@R6				;前回のﾃﾞｰﾀがTOP+ﾜｰﾄﾞｱﾄﾞﾚｽ


	MOV.W	#BIT15,R7			;END
;;;	MOV.W	#D'128,R4			;BUFF-128WORD
	MOV.W	#D'512,R4			;BUFF-512WORD
	CMP/HS	R2,R4				;R4 >= R2
	BT	SND_DTOA_DMEMDSET_150		;
	MOV	R4,R2				;LIMIT
	XOR	R7,R7				;まだ残りがあるよ!
SND_DTOA_DMEMDSET_150:

	MOV.L	#_CPUDTOA_DAT1_REQCNT,R6	;送信個数
	MOV.W	R2,@R6				;MAX 128WORD

	MOV.L	#_CPUDX_SEND_NOWCNT,R1		;ﾜｰﾄﾞ個数+送信個数
	MOV.L	@R1,R3				;
	ADD	R2,R3				;
	MOV.L	R3,@R1				;

	MOV.L	#_CPUDX_MEM1_SNDKND,R1		;//KIND
	MOV.W	@R1,R0				;
	OR	R7,R0				;
	MOV.L	#_CPUDTOA_DAT1_REQKND,R6	;種別[BIT15=1:END <-//-> BIT7~BIT0 KIND]
	MOV.W	R0,@R6				;



;	---------------------------------------
	MOV.L	#_CPUDX_SEND_TOPADR,R8		;
	MOV.L	@R8,R5
	MOV.L	#_CPUDTOA_DAT1_DATTOP,R6	;

SND_DTOA_DMEMDSET_200LOP:

	TST	R2,R2				;個数=0
	TST_BIT_OF SND_DTOA_DMEMDSET_300	;終了

	MOV.W	@R5+,R0				;
	MOV.W	R0,@R6				;
	ADD	#2,R6				;
	ADD	#-1,R2				;
	M_BRA	SND_DTOA_DMEMDSET_200LOP	;

SND_DTOA_DMEMDSET_300:				;
	MOV.L	R5,@R8				;NEXT-ADRｾｯﾄ



	SUB_END
	M_RTS




