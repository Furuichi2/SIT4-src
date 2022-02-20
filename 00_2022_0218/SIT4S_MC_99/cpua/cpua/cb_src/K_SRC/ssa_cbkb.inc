;	*******************************************
;	***					***
;	***	クラッチ信号のバックアップ	***
;	***					***
;	*******************************************
;	---2011-09-14----- ｸﾗｯﾁ信号記憶[FERAM]----
	.import		_FRAM_CBSTS_SQCOD1	;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	.import		_FRAM_CBSTS_SQDAT1	;*data1
	.import		_FRAM_CBSTS_SQDAT1_SUM	;data1の反転
	.import		_FRAM_CBSTS_SQDAT2	;*data2
	.import		_FRAM_CBSTS_SQDAT2_SUM	;data2の反転
	.import		_FRAM_CBSTS_SQDAT3	;*data3
	.import		_FRAM_CBSTS_SQDAT3_SUM	;data3

;	---2011-09-14 [16ﾊﾞｲﾄ] [DPRAM] -----
	.import		_CPUATOB_STS_SAVECMD	;5AA5 or A55A
	.import		_CPUATOB_STS_SAVEDAT1	;BAKUP DATA1
	.import		_CPUATOB_STS_SAVEDAT2	;BAKUP DATA2
	.import		_CPUATOB_STS_SAVEDAT3	;BAKUP DATA3

	.import		_CPUBTOA_STS_LOADSTS	;5AA5 or A55A
	.import		_CPUBTOA_STS_LOADDAT1	;BAKUP DATA1
	.import		_CPUBTOA_STS_LOADDAT2	;BAKUP DATA2 
	.import		_CPUBTOA_STS_LOADDAT3	;BAKUP DATA3 3DFE,3DFF もうここには隙間なし

;	---------------------------------------
;//	*******************************************
;//	***					***
;//	*** 	CPUB専用ﾊﾞｯｸｱｯﾌﾟ		***
;//	***	2011-09-14			***
;//	***					***
;//	*******************************************
__CBSTSBAKUP_COD	.EQU	H'5AA5
	.ALIGN	4		;
_CBB_STS_BKUP_SAVE:
	SUB_START

	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF CBB_STS_BKUPSV_EXT		;

	MOV.L	#_CPUATOB_STS_SAVECMD,R5	;
	MOV.W	@R5,R0				;DPRAM LOAD
	MOV.L	#_CBSTS_SAVE_CMDWK,R6		;
	MOV.W	@R6,R2				;WORKRAM LOAD
	CMP/EQ	R0,R2				;
	BT	CBB_STS_BKUPSV_EXT		;ｺﾏﾝﾄﾞはない

	MOV.W	#__CBSTSBAKUP_COD,R4			;
	CMP/EQ	R4,R0				;
	BT	CBB_STS_BKUPSV_100		;
	NOT	R4,R4
	CMP/EQ	R4,R0				;
	BF	CBB_STS_BKUPSV_EXT		;
CBB_STS_BKUPSV_100:				;
	MOV.W	R0,@R6				;SAVE CMD


	MOV.L	#_CPUATOB_STS_SAVEDAT1,R5	;DPRAM-data1
	MOV.L	#_FRAM_CBSTS_SQDAT1,R6		;FERAM-data1

;----------[1個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
;----------[2個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
;----------[3個]----
	MOV.W	@R5+,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;
	NOT	R2,R2				;
	MOV.W	R2,@R6				;
	ADD	#2,R6				;

	MOV.L	#_FRAM_CBSTS_SQCOD1,R1		;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	MOV.W	R0,@R1				;有効なデータがある

CBB_STS_BKUPSV_EXT:
	SUB_END
	M_RTS


;//	*******************************************
;//	***					***
;//	*** 	CPUB専用ﾊﾞｯｸｱｯﾌﾟ戻し		***
;//	***	2011-09-14			***
;//	***					***
;//	*******************************************
_CBB_STS_BKUP_LOAD:
	SUB_START
	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON CBB_STS_BKUP_LD_EXT		;

	MOV.L	#_FRAM_CBSTS_SQCOD1,R1		;*USEFUL DATA 5AA5またはA55Aならﾊﾞｯｸｱｯﾌﾟ有
	MOV.W	@R1,R0				;有効なデータがある
	MOV.W	#__CBSTSBAKUP_COD,R4			;
	CMP/EQ	R4,R0				;
	BT	CBB_STS_BKUP_LD_100		;
	NOT	R4,R4				;
	CMP/EQ	R4,R0				;
	BF	CBB_STS_BKUP_LD_400		;
CBB_STS_BKUP_LD_100:
	MOV.L	#_FRAM_CBSTS_SQDAT1,R5		;FERAM-data1
	MOV.L	#_CPUBTOA_STS_LOADDAT1,R6	;DPRAM-data1
	MOV.W	#D'3,R3				;


CBB_STS_BKUP_LD_200LOP:
	TST	R3,R3				;
	TST_BIT_OF CBB_STS_BKUP_LD_500		;
	MOV.W	@R5+,R0				;NOMAL DATA
	MOV.W	@R5+,R1				;NOT DATA
	NOT	R1,R1				;
	CMP/EQ	R1,R0				;
	BF	CBB_STS_BKUP_LD_400		;ERR
	MOV.W	R0,@R6				;
	ADD	#2,R6				;
	ADD	#-1,R3				;
	M_BRA	CBB_STS_BKUP_LD_200LOP		;

;----異常あり-----------
CBB_STS_BKUP_LD_400:
	XOR	R0,R0
	MOV.L	#_CPUBTOA_STS_LOADDAT1,R6	;BAKUP DATA1
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	R0,@R6
CBB_STS_BKUP_LD_500:
	MOV.W	#__CBSTSBAKUP_COD,R4
	MOV.L	#_CPUBTOA_STS_LOADSTS,R1	;
	MOV.W	R4,@R1				;

	MOV.W	#BIT0,R0		;
	MOV.L	#_CBSTS_LOAD_FLG,R1	;
	MOV.W	R0,@R1			;

CBB_STS_BKUP_LD_EXT:
	SUB_END
	M_RTS
