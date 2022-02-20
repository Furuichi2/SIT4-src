;	*******************************************
;	***					***
;	***	クラッチ信号のバックアップ	***
;	***					***
;	*******************************************

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
;//	*** 	CPUA専用ﾊﾞｯｸｱｯﾌﾟ*API関数	***
;//	***	2011-09-14			***
;//	***					***
;//	*******************************************
__CBSTSBAKUP_COD	.EQU	H'5AA5
	.ALIGN	4		;
_CBA_STS_BKUP_SAVE:
	SUB_START


	MOV.L	#_CBSTS_SAVE_DAT,R5		;//
	MOV.L	#_CPUATOB_STS_SAVEDAT1,R6	;DPRAM-data1
	MOV.W	@R5+,R0				;
	MOV.W	R0,@R6				;
	ADD	#2,R6				;
	MOV.W	@R5+,R0				;
	MOV.W		R0,@R6				;
	ADD	#2,R6				;
	MOV.W	@R5+,R0				;
	MOV.W	R0,@R6				;


	MOV.L	#_CPUATOB_STS_SAVECMD,R5	;
	MOV.W	@R5,R0				;DPRAM LOAD
		MOV.W	#__CBSTSBAKUP_COD,R4		;
		CMP/EQ	R4,R0				;
	BF	CBA_STS_BKUPSV_100		;規定したコード１か NO-JUMP[規定したコードを書く]
	NOT	R4,R4				;YES コード２を書く
CBA_STS_BKUPSV_100:				;
	MOV.W	R4,@R5				;ﾊﾞｯｸｱｯﾌﾟしろ


CBA_STS_BKUPSV_EXT:
	SUB_END
	M_RTS


;//	*******************************************
;//	***					***
;//	*** 	CPUA専用ﾊﾞｯｸｱｯﾌﾟ戻し		***
;//	***	2011-09-14			***
;//	***					***
;//	*******************************************
	.ALIGN	4		;
_CBA_STS_BKUP_LOAD:
	SUB_START
	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON CBA_STS_BKUP_LD_EXT		;完了

	MOV.L	#_CPUBTOA_STS_LOADSTS,R1	;
	MOV.W	@R1,R0				;
	MOV.W	#__CBSTSBAKUP_COD,R4		;
	CMP/EQ	R4,R0				;
	BF	CBA_STS_BKUP_LD_EXT		;待ち

	MOV.L	#_CPUBTOA_STS_LOADDAT1,R5	;BAKUP DATA1
	MOV.L	#_CBSTS_SAVE_DAT,R6		;//
	MOV.W	@R5+,R0
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	@R5+,R0
	MOV.W	R0,@R6
	ADD	#2,R6
	MOV.W	@R5+,R0
	MOV.W	R0,@R6
	ADD	#2,R6

	XOR	R4,R4				;
	MOV.L	#_CPUBTOA_STS_LOADSTS,R1	;ｽﾃｰﾀｽは消しておく[まさかの不具合のため]
	MOV.W	R4,@R1				;

	MOV.W	#BIT0,R0			;
	MOV.L	#_CBSTS_LOAD_FLG,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_CBA_BKUPLOD_END_PROC,R0	;

CBA_STS_BKUP_LD_EXT:
	SUB_END
	M_RTS
