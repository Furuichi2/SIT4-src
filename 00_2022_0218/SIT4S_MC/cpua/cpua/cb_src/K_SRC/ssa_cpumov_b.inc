;	*******************************************
;	***					***
;	***		CPUB���̑��M�\�t�g	***
;	***					***
;	*******************************************
	.GLOBAL		_CPUBTOA_DAT1_REQADR	;TOP-ADR 2013-12[MC]
	.GLOBAL		_CPUBTOA_DAT1_REQKND	;���	2013-12[MC]
	.GLOBAL		_CPUBTOA_DAT1_REQCNT	;��	2013-12[MC]
	.GLOBAL		_CPUBTOA_DAT1_REQCOD	;WR	2013-12[MC]
	.GLOBAL		_CPUBTOA_DAT1_ACKCOD	;ACK	2013-12[MC]
	.GLOBAL		_CPUBTOA_DAT1_DATTOP	;256BYTE(128W)	2013-12[MC]

;	*******************************************
;	***					***
;	***	�Ƃ肠����ROM���Ұ����M,��M	***
;	***	CPUB==>CPUA			***
;	*******************************************
_SND_BTOA_CPUBMEMX_KND1REQ:
	SUB_START

	MOV.W	#BIT0,R0
	MOV.L	#_CPUBX_MEM1_SNDEVN,R1;		//EVNT BIT0:KIND
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***					***
;	***		CPUB����Ҳ�		***
;	***					***
;	*******************************************
_SND_BTOA_CPUBMEMX:
	SUB_START
	MOV.L	#_CPUBX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON SND_BTOA_BMEMX100		;

	MOV.L	#_CPUBX_MEM1_SNDEVN,R4		;//EVNT BIT0:KIND
	MOV.W	@R4,R2				;
	TST	R2,R2				;
	TST_BIT_ON SND_BTOA_BMEMX050		;
	M_BRA	SND_BTOA_BMEMXEXT		;

SND_BTOA_BMEMX050

	MOV.L	#_CPUBX_MEM1_SNDEVN,R1		;//EVNT BIT0:KIND
	MOV.W	@R1,R0				;
	MOV.L	#_CPUBX_MEM1_SNDKND,R1		;//KIND
	MOV.W	R0,@R1				;

	MOV.L	#_W_PARAM_TOP,R0		;
	MOV.L	#_CPUBX_SEND_TOPADR,R1		;
	MOV.L	R0,@R1				;

	MOV.W	#D'512,R0			;
	MOV.L	#_CPUBX_SEND_MAXCNT,R1		;
	MOV.L	R0,@R1				;

	XOR	R0,R0
	MOV.L	#_CPUBX_SEND_NOWCNT,R1		;
	MOV.L	R0,@R1				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUBX_MEM1_SNDFLG,LG=W,BIT=BIT0,WKREG=R1	;
SND_BTOA_BMEMX100


	MOV.L	#_CPUBX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;BIT0:ACTIVE BIT1:OF->ON(�ް����) BIT2:ON->OF BIT6:

	TST	#BIT2,R0			;
	TST_BIT_ON SND_BTOA_BMEMX400		;OFF�҂�

	TST	#BIT1,R0			;
	TST_BIT_ON SND_BTOA_BMEMX300		;ON�҂�

;	------- �ް����----------

	FAR_JSR	#_SND_BTOA_BMEM_DSET,R0

	MOV.W	#BIT15,R4		;
	TST	R4,R7			;
	TST_BIT_OF SND_BTOA_BMEMX150	;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUBX_MEM1_SNDFLG,LG=W,BIT=BIT6,WKREG=R1	;

SND_BTOA_BMEMX150

;	--------------------------
	MOV.W	#_START_REQ_COD,R0		;
	MOV.L	#_CPUBTOA_DAT1_REQCOD,R6	;���޼���ON
	MOV.W	R0,@R6				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUBX_MEM1_SNDFLG,LG=W,BIT=BIT1,WKREG=R1	;
	M_BRA	SND_BTOA_BMEMXEXT						;

SND_BTOA_BMEMX300
;	------- ���葤��ON�҂�-----
	MOV.L	#_CPUBTOA_DAT1_ACKCOD,R6	;
	MOV.W	@R6,R0				;
	MOV.W	#_START_ACK_COD,R4		;
	CMP/EQ	R4,R0				;
	BF	SND_BTOA_BMEMXEXT		;���葤����ON? NO

	XOR	R0,R0				;
	MOV.L	#_CPUBTOA_DAT1_REQCOD,R6	;���޼�������OFF
	MOV.W	R0,@R6				;

	MEM1_BIT0_TO_BIT7_ORSET MEM=_CPUBX_MEM1_SNDFLG,LG=W,BIT=BIT2,WKREG=R1	;
	M_BRA	SND_BTOA_BMEMXEXT						;
SND_BTOA_BMEMX400

;	------- ���葤��OFF�҂�------
	MOV.L	#_CPUBTOA_DAT1_ACKCOD,R6	;
	MOV.W	@R6,R0				;
	TST	R0,R0
	TST_BIT_ON SND_BTOA_BMEMXEXT		;���葤����OFF?  NO

;	-----------------------------
	MOV.L	#_CPUBX_MEM1_SNDFLG,R1		;
	MOV.W	@R1,R0				;BIT0:ACTIVE BIT1:OF->ON(�ް����) BIT2:ON->OF BIT6:
	TST	#BIT6,R0			;�Ō���ް���������?
	TST_BIT_ON SND_BTOA_BMEMX500		;YES

	AND	#BIT0,R0			;BIT0�ȊO:OFF
	MOV.W	R0,@R1				;NEXT
	M_BRA	SND_BTOA_BMEMXEXT		;


;	------------- �I��------------
SND_BTOA_BMEMX500
	XOR	R0,R0
	MOV.L	#_CPUBX_MEM1_SNDFLG,R1		;
	MOV.W	R0,@R1				;

	MOV.L	#_CPUBTOA_DAT1_REQCNT,R6	;
	MOV.W	R0,@R6				;

	MOV.L	#_CPUBTOA_DAT1_REQKND,R6	;
	MOV.W	R0,@R6

	MOV.L	#_CPUBTOA_DAT1_REQADR,R6	;
	MOV.L	R0,@R6				;

	MOV.L	#_CPUBTOA_DAT1_REQCOD,R6	;���޼���
	MOV.W	R0,@R6				;

	XOR	R0,R0
	MOV.L	#_CPUBX_MEM1_SNDEVN,R1		;//EVNT BIT0:KIND
	MOV.W	R0,@R1				;

SND_BTOA_BMEMXEXT
	SUB_END
	M_RTS



;
;
;
;
;	ANS R7
_SND_BTOA_BMEM_DSET:
	SUB_START

	XOR	R7,R7

	MOV.L	#_CPUBX_SEND_MAXCNT,R1		;
	MOV.L	@R1,R2				;

	MOV.L	#_CPUBX_SEND_NOWCNT,R1		;ܰ�ތ�
	MOV.L	@R1,R3				;
	SUB	R3,R2				;
	CMP/PL	R2				;
	BT	SND_BTOA_BMEMDSET_100		;
	XOR	R2,R2				;DATA ����[0]�����޼���
	MOV.W	#BIT15,R7			;END
	M_BRA	SND_BTOA_BMEMDSET_150		;


SND_BTOA_BMEMDSET_100:
	MOV.L	#_CPUBTOA_DAT1_REQADR,R6	;
	MOV.L	R3,@R6				;�O����ް���TOP+ܰ�ޱ��ڽ


	MOV.W	#BIT15,R7			;END
	MOV.W	#D'128,R4			;BUFF-128WORD
	CMP/HS	R2,R4				;R4 >= R2
	BT	SND_BTOA_BMEMDSET_150		;
	MOV	R4,R2				;LIMIT
	XOR	R7,R7				;�܂��c�肪�����!
SND_BTOA_BMEMDSET_150:

	MOV.L	#_CPUBTOA_DAT1_REQCNT,R6	;���M��
	MOV.W	R2,@R6				;MAX 128WORD

	MOV.L	#_CPUBX_SEND_NOWCNT,R1		;ܰ�ތ�+���M��
	MOV.L	@R1,R3				;
	ADD	R2,R3				;
	MOV.L	R3,@R1				;

	MOV.L	#_CPUBX_MEM1_SNDKND,R1		;//KIND
	MOV.W	@R1,R0				;
	OR	R7,R0				;
	MOV.L	#_CPUBTOA_DAT1_REQKND,R6	;���[BIT15=1:END <-//-> BIT7~BIT0 KIND]
	MOV.W	R0,@R6				;



;	---------------------------------------
	MOV.L	#_CPUBX_SEND_TOPADR,R8		;
	MOV.L	@R8,R5
	MOV.L	#_CPUBTOA_DAT1_DATTOP,R6	;

SND_BTOA_BMEMDSET_200LOP:

	TST	R2,R2				;��=0
	TST_BIT_OF SND_BTOA_BMEMDSET_300	;�I��

	MOV.W	@R5+,R0				;
	MOV.W	R0,@R6				;
	ADD	#2,R6				;
	ADD	#-1,R2				;
	M_BRA	SND_BTOA_BMEMDSET_200LOP	;

SND_BTOA_BMEMDSET_300:				;
	MOV.L	R5,@R8				;NEXT-ADR���



	SUB_END
	M_RTS



