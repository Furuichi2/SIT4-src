;	----------2015-09-30 100�i-------------
;//	***********************************
;//	***				***
;//	***	99�i�d�l		***
;//	***				***
;//	***				***
;//	***********************************
;	100�i�d�l�����ް��������܂ňُ�֘A�̒�~���K�v

	.EXPORT	_DTMAKE_100STEP_1MS
	.EXPORT	_DTMAKE_100STEP_MAIN_LOP


;//	***********************************
;//	***				***
;//	***	99�i�d�l		***
;//	***	1MS�Ŏ��s����		***
;//	***				***
;//	***********************************
_DTMAKE_100STEP_1MS
	SUB_START

	MOV.L	#_SYS_100STEP_USE,R1		;//100�i���޼����g�p����
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF DTMAKE_100STEP1MS_100	;

	FAR_JSR	#_DT_100STEP_SVLOAD,R0

DTMAKE_100STEP1MS_100

	SUB_END
	M_RTS

;//	***********************************
;//	***				***
;//	***	99�i�d�l		***
;//	***	���C���Ŏ��s����	***
;//	***				***
;//	***********************************
_DTMAKE_100STEP_MAIN_LOP
	SUB_START
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	dpram �ݒ��ް��Ǐo		***
;	***					***
;	*******************************************
;	dpram=>work ���̍ۂɈȉ�����������
;	�p�x,�ʒu�ް��ω�
;	��ς�0����0�ȊO�ɕω�,��ς�0�ȊO����0�ɕω�
;	DPRAM-�ر�1STEP�̈�->	_SVPX1_OBJECT_POS_TOP
;				_SVPX1_OBJECT_DIG_TOP
;				_SVPX1_OBJECT_SPD_TOP,R3
;				_SVPX1_OBJECT_TIM_TOP,R3
;
;
;	SVP_�͖{���̐�����,�����ȊO�ŎQ�Ƃ��邱�Ƃ͂Ȃ�
;	���l������SVPX1�ɂȂ�.�����ܰ��Ɏ󂯂Ďg�p���邱��
;	[]
;
_DT_100STEP_SVLOAD
	SUB_START
	MOV.L	#_SYS_100STEP_USE,R1	;//100�i���޼����g�p����
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_ON DT_100STEP_SVLD_010	;
	M_BRA	DT_100STEP_SVLD_EXT


DT_100STEP_SVLD_010
	MOV.L	#_SVP_MOT_SEND_REQ,R5	;Ӱ����ް����M�iNo.
	MOV.W	@R5,R0			;
	TST	R0,R0			;
	TST_BIT_ON DT_100STEP_SVLD_050	;
	M_BRA	DT_100STEP_SVLD_EXT	;

DT_100STEP_SVLD_050:
	MOV.W	#D'98,R4		;
	CMP/HS	R0,R4			;
	BT	DT_100STEP_SVLD_100	;DATA <= 98
	M_BRA	DT_100STEP_SVLD_900	;

DT_100STEP_SVLD_100
	XOR	R7,R7			;BIT0:�ʒu BIT1:�p�x BIT2:�^�C�}
	ADD	#-1,R0			;1�i��->DATA[0]�ɓ���
	SHLL	R0			;
	MOV	R0,R10			;OFFSET 2BYTE
	SHLL	R0			;
	MOV	R0,R11			;OFFSET 4BYTE


	MOV.L	#_SVP_OBJECT_PS,R1		;�ڕW�ʒu
	MOV.L	@R1,R2				;
	MOV.L	#_SVPX1_OBJECT_POS_TOP,R3	;
	ADD	R11,R3				;
	MOV.L	@R3,R4				;
	MOV.L	R2,@R3				;
	CMP/EQ	R4,R2				;�ް��͓���
	BT	DT_100STEP_SVLD_200
	MOV.B	#BIT0,R7		;
DT_100STEP_SVLD_200

	MOV.L	#_SVP_OBJECT_DG,R1	;�ڕW�p�x
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_DIG_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_100STEP_SVLD_300
	MOV.B	#BIT1,R7		;
DT_100STEP_SVLD_300

	MOV.L	#_SVP_OBJECT_SP,R1			;�ڕW���x
	MOV.W	@R1,R2						;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R3	;	//�ڕW���x
	ADD	R10,R3							;
	MOV.W	@R3,R4						;LOAD OLD<2019-02-05>
	MOV.W	R2,@R3						;

	CMP/EQ	R4,R2						;
	BT	DT_100STEP_SVLD_350				;

;	--------- 2019-04-10----------
	MOV.B	#BIT2,R7		;ERR
;	------------------------------------

;	--------- 2019-02-05 --------
	MOV.B	#1,R0						;
	MOV.L	#_INT_SPD_CHG_FLG,R1		;
	MOV.B	R0,@R1						;
	XOR		R0,R0						;
	MOV.L	#_MAIN_SPD_CHG_FLG,R1		;
	MOV.B	R0,@R1						;

DT_100STEP_SVLD_350


	MOV.L	#_SVP_OBJECT_TM,R1	;��~����
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_TIM_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_100STEP_SVLD_400	;

;[�H�v]
;	--------- 2019-02-05 --------
	MOV.B	#1,R0
	MOV.L	#_INT_TIM_CHG_FLG,R1		;
	MOV.B	R0,@R1						;
	XOR		R0,R0						;
	MOV.L	#_MAIN_TIM_CHG_FLG,R1		;
	MOV.B	R0,@R1						;


DT_100STEP_SVLD_400

	MOV.L	#_SVP_OBJECT_PRS,R1	;�ڕW����
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_PRS_TOP,R3	;//�ڕW����
	ADD	R10,R3			;
	MOV.W	R2,@R3			;

	MOV.L	#_SVP_MOT_INF,R1	;Ӱ��ݏ��(�ʒu/��)
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_MOT_INF,R3	;Ӱ��ݏ��bit0(�ʒu/�׏d)
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_100STEP_SVLD_500

	MOV.B	#BIT3,R7		;�ύX���ُ� 2016-04-18

DT_100STEP_SVLD_500

;;	MOV.L	#_SVP_FED_DEG,R1	;̨��ފp�x(�\��)
;;	MOV.W	@R1,R2			;
;;	MOV.L	#_SVP_FED_POS,R1	;̨��ވʒu(�\��)
;;	MOV.L	@R1,R2			;


	TST	R7,R7			;
	TST_BIT_OF DT_100STEP_SVLD_900	;

	MOV.L	#_SV_CHG_FLG2,R1	;
	MOV.L	@R1,R0			;
	OR	#BIT2,R0		;
	MOV.L	R0,@R1			;
	
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA					;
	FAR_JSR	#_API_DATA_CHK_CALC_START,R0	;2016-04-18
	.AENDI

DT_100STEP_SVLD_900
	MOV.L	#_SVP_MOT_SEND_REQ,R5	;Ӱ����ް����M�iNo.
	XOR	R0,R0			;
	MOV.W	R0,@R5			;REQ
DT_100STEP_SVLD_EXT
	SUB_END
	M_RTS










;	*******************************************
;	***					***
;	***	dpram �ݒ��ް��Ǐo		***
;	***					***
;	*******************************************
;	10�i�d�l
;
_DT_10STEP_SVLOAD
	SUB_START

	MOV.L	#_SYS_100STEP_USE,R1	;//100�i���޼����g�p����
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF DT_10STEP_SVLD_010	;
	M_BRA	DT_10STEP_SVLD_EXT

DT_10STEP_SVLD_010




	MOV.W	#D'10,R14		;10,9,,,,1
	XOR	R7,R7			;BIT0:�ʒu BIT1:�p�x BIT2:�^�C�}


DT_10STEP_SVLD_LOP
	MOV	R14,R0			;
	ADD	#-1,R0			;1�i��->DATA[0]�ɓ���
	SHLL	R0			;
	MOV	R0,R10			;OFFSET 2BYTE
	SHLL	R0			;
	MOV	R0,R11			;OFFSET 4BYTE


	MOV.L	#_SVP_OBJECT_POS_TOP,R1	;�ڕW�ʒu
	ADD	R11,R1			;
	MOV.L	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_POS_TOP,R3	;
	ADD	R11,R3			;
	MOV.L	@R3,R4			;
	MOV.L	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_10STEP_SVLD_200
	MOV.B	#BIT0,R7		;
DT_10STEP_SVLD_200

	MOV.L	#_SVP_OBJECT_DIG_TOP,R1	;�ڕW�p�x
	ADD	R10,R1			;
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_DIG_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_10STEP_SVLD_300
	MOV.B	#BIT1,R7		;
DT_10STEP_SVLD_300

	MOV.L	#_SVP_OBJECT_SPD_TOP,R1	;�ڕW���x
	ADD	R10,R1							;
	MOV.W	@R1,R2						;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R3	;	//�ڕW���x
	ADD	R10,R3							;
;;;2019-04-10	MOV.W	R2,@R3						;
;	------------------------------------------------
	MOV.W	@R3,R4						;2019-04-10
	MOV.W	R2,@R3						;
	BT	DT_10STEP_SVLD_350				
	MOV.B	#BIT2,R7					;
DT_10STEP_SVLD_350
;	----------------------------------------------

	MOV.L	#_SVP_OBJECT_TIM_TOP,R1	;��~����
	ADD	R10,R1			;
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_TIM_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;�ް��͓���
	BT	DT_10STEP_SVLD_400	;



DT_10STEP_SVLD_400

	MOV.L	#_SVP_OBJECT_PRS_TOP,R1		;�ڕW����
	ADD	R10,R1				;
	MOV.W	@R1,R2				;
	MOV.L	#_SVPX1_OBJECT_PRS_TOP,R3	;//�ڕW����
	ADD	R10,R3				;
	MOV.W	R2,@R3				;


	TST	R7,R7			;
	TST_BIT_OF DT_10STEP_SVLD_900	;

	MOV.L	#_SV_CHG_FLG2,R1	;
	MOV.L	@R1,R0			;
	OR	#BIT2,R0		;
	MOV.L	R0,@R1			;

DT_10STEP_SVLD_900
	ADD	#-1,R14
	TST	R14,R14			;
	TST_BIT_OF DT_10STEP_SVLD_EXT	;
	M_BRA	DT_10STEP_SVLD_LOP	;

DT_10STEP_SVLD_EXT
	SUB_END
	M_RTS