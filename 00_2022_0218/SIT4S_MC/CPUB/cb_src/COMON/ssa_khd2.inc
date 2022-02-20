;	***************************************************
;	***						***
;	***						***
;	***	�n�[�h�̈Ⴂ��₤�\�t�g		***
;	***						***
;	***						***
;	***************************************************
;	*******************************************
;	***					***
;	***	�ʒu����LSI���ݶ���ׯ�		***
;	***					***
;	*******************************************
	.AIF	_SIT_CPU_SEL	EQ	_SIT3_CPUB
	.IMPORT	_PDDR
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUB
	.IMPORT	_PJDR
	.AENDI

_POS_LSI_DT_LATCH:				;
	SUB_START

;	***** SIT3_CPUA SIT4_CPUA PROGRAM �̓R���p�C�����Ȃ� *****
	.AIF	_SIT_CPU_SEL	EQ	_SIT3_CPUA
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUA
	.AELSE

;	***** SIT3_CPUB SIT4_CPUB PROGRAM *****
	DI_PUSH_SR_SHn	WK_REG1=R5,WK_REG2=R6					;

;	***** SIT3_CPUB PROGRAM *****
	.AIF	_SIT_CPU_SEL	EQ	_SIT3_CPUB
	MOV.L	#_PDDR,R1			; PORT17
	MOV.W	@R1,R0
	MOV.W	#BIT13,R3			;
	OR	R0,R3				;
	MOV.W	R3,@R1				;
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	MOV.W	R0,@R1

;	***** SIT4_CPUB PROGRAM *****
	.AELSE
	MOV.L	#_PJDR,R1			;
	MOV.B	@R1,R0
	MOV.W	#BIT5,R3			;
	OR	R0,R3				;
	MOV.B	R3,@R1				;
	NOP
	NOP
	NOP
	NOP
	NOP
;;;;;	MOV.W	#BIT5,R3			;
;;;;;	NOT	R3,R3				;���̂܂܂͂��߂ł�
;;;;;	AND	R3,R0				;����͂���łn�j�ł��B
	NOP
	MOV.B	R0,@R1
	.AENDI

	EI_POP_SR_SHn 								;

	.AENDI

	SUB_END					;
	M_RTS					;

