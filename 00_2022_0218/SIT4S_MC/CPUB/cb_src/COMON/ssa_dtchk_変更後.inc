;	*******************************************
;	***					***
;	***					***
;	***		ﾓｰｼｮﾝﾃﾞｰﾀﾁｪｯｸ		***
;	***					***
;	***					***
;	*******************************************
;	MOV.L	#_SETX_POS_SDAT1_SPD,R12		;pls/s
;	MOV.L	#_SETX_POS_SDAT1_TIM,R13		;
;	MOV.L	#_SETX_POS_SDAT1_OFSPOS,R14		;+1回転を考慮した位置
;	前の段が停止行程だと０からの加速演算になるぞ！

_MOTION_DATA_CHK:
	SUB_START
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON MOTION_DATCK_050			;


	MOV.L	#_SET1_ACCLAT_TIM1,R1			;
	MOV.W	@R1,R2					;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1					;
	M_BRA	MOTION_DATCK_100

;	-------------- ふりこ------------
MOTION_DATCK_050:
	MOV.L	#_ACCB_ACCLAT_TIM1,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1				;
	M_BRA	MOTION_DATCK_100



MOTION_DATCK_100:
	MOV.L	#_LINK_MAX_SPD_PLS,R1	;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R1,R2			;
	MOV.L	#_CHKSPDWORKVMAX,R1	;//PLS/S
	MOV.L	R2,@R1			;


	MOV.L	#_SETX_POS_STEP_MAX,R1			;
	MOV.W	@R1,R5					;設定1~10
	ADD	#1,R5					;1段の場合    2個の速度ﾁｪｯｸ
							;10段の場合  11個の速度ﾁｪｯｸ

	XOR	R7,R7					;STEP演算結果
	MOV.W	#BIT0,R8				;

	XOR	R0,R0					;
	MOV.L	#_SETX_POS_SDAT1_SPD,R9			;
	MOV.L	#_SETX_POS_SDAT1_TIM,R10		;
	MOV.L	#_SETX_POS_SDAT1_OFSPOS,R11		;
	MOV.L	#_SETX_POS_SDAT1_INF1,R12		;
	MOV.L	#_SVP_OBJECT_SPD_TOP,R13		;0.1%
	MOV.L	#_PVP_CKLMT_SPDTOP,R14			;SAVE


;	-------- 初期速度=0 ---------
	XOR	R2,R2					;
	MOV.L	#_CHKSPDWORK1,R1			;PLS/S
	MOV.L	R2,@R1					;WORK=0 SPEED
	MOV.L	#_CHKSPDPERWORK1,R1			;//
	MOV.W	R2,@R1					;%


;	-------- 初期位置=待機点 ---------
	MOV.L	#_SETX_UPAREA_PLS,R1			;//4;待機点
	MOV.L	@R1,R2					;
	MOV.L	#_CHKPOSWORK1,R1			;
	MOV.L	R2,@R1					;


MOTION_DATCK_200LOP:
	MOV.W	#1,R4					;残数
	CMP/EQ	R4,R5					;残数=1 行程MAX
	BF	MOTION_DATCK_220
;;;2013-04-08	MOV.L	#_SVP_UPAREA_SPD0,R1			;行程MAX時は戻り速度
;;;2013-04-08		MOV.W	@R1,R2					;
	XOR	R2,R2
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;WORK=0 SPEED
	M_BRA	MOTION_DATCK_240			;

MOTION_DATCK_220
;	-------- 設定速度%-------------------
	MOV.W	@R13,R2					;
;;;2013-04-08	MOTION_DATCK_240
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%

;	---------設定速度PLS/S---------------
	MOV.L	@(R0,R9),R2				;目標速度PLS/S
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;WORK=0 SPEED

MOTION_DATCK_240

;	---------設定角度PLS---------------
	MOV.L	@(R0,R11),R2				;目標位置
	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	R2,@R1					;


;	========= タイマ停止は０速度として演算する=======-
	MOV.L	@(R0,R12),R2				;
	MOV.W	#BIT1,R4				;
	TST	R4,R2					;
	TST_BIT_ON MOTION_DATCK_500			;逆転行程は演算しない


	MOV.L	@(R0,R10),R3				;
	TST	R3,R3					;tim != 0 停止行程
	TST_BIT_ON MOTION_DATCK_300			;

	MOV.W	#BIT0,R4				;
	TST	R4,R2					;
	TST_BIT_OF MOTION_DATCK_300			;停止の行程(正→逆)
	M_BRA	MOTION_DATCK_350

MOTION_DATCK_300
	XOR	R2,R2					;
	MOV.L	#_CHKSPDWORK2,R1			;速度0として演算する
	MOV.L	R2,@R1					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%
MOTION_DATCK_350



;;;;2013-04-08
;;;;2013-04-08	MOV.L	@(R0,R10),R3				;
;;;;2013-04-08	TST	R3,R3					;tim != 0 停止行程
;;;;2013-04-08	TST_BIT_ON MOTION_DATCK_500			;
;;;;2013-04-08
;;;;2013-04-08	MOV.L	@(R0,R12),R2				;
;;;;2013-04-08	MOV.W	#BIT1,R4				;
;;;;2013-04-08	TST	R4,R2					;
;;;;2013-04-08	TST_BIT_ON MOTION_DATCK_500			;逆転行程は演算しない
;;;;2013-04-08
;;;;2013-04-08	MOV.W	#BIT0,R4				;
;;;;2013-04-08	TST	R4,R2					;
;;;;2013-04-08	TST_BIT_OF MOTION_DATCK_500			;停止の行程(正→逆)


	PUSH_REG1 R0	;ADR

;;	PUSH_REG1 R5	;CNT
;;	PUSH_REG1 R7	;出力ﾌﾗｸﾞ
;;	PUSH_REG1 R8	;BIT0~BIT9,BIT15
;;	PUSH_REG1 R9	;TOP
;;	PUSH_REG1 R10	;TOP
;;	PUSH_REG1 R11	;TOP
;;	PUSH_REG1 R12	;TOP

	FAR_JSR	#_CHGSPD_LIMIT_CALC,R0

;;	POP_REG1 R12	;TOP
;;	POP_REG1 R11	;TOP
;;	POP_REG1 R10	;TOP
;;	POP_REG1 R9	;TOP
;;	POP_REG1 R8	;BIT0~BIT9,BIT15
;;	POP_REG1 R7	;出力ﾌﾗｸﾞ
;;	POP_REG1 R5	;CNT

	POP_REG1 R0			;ADR
	M_BRA	MOTION_DATCK_600	;


;	--------- 停止行程------------
MOTION_DATCK_500:
	XOR	R2,R2					;
	MOV.L	#_CHKSPDWORK2,R1			;次の演算には0から開始ｽﾙ
	MOV.L	R2,@R1					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%


MOTION_DATCK_600:

	ADD	#4,R0					;
	ADD	#-1,R5					;
	TST	R5,R5					;
	TST_BIT_OF MOTION_DATCK_900			;
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	@R1,R2					;WORK=0 SPEED
	MOV.L	#_CHKSPDWORK1,R1			;
	MOV.L	R2,@R1					;

	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	@R1,R2					;
	MOV.L	#_CHKPOSWORK1,R1			;
	MOV.L	R2,@R1					;

	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	@R1,R2					;0.1%
	MOV.L	#_CHKSPDPERWORK1,R1			;
	MOV.W	R2,@R1					;0.1%

	SHLL	R8					;
	ADD	#2,R13					;
	ADD	#2,R14					;
	M_BRA	MOTION_DATCK_200LOP			;


MOTION_DATCK_900:

	MOV.L	#_PVX_CKSPD_OVBIT,R1			;赤表示(BIT0~BIT9 BIT15:戻速度)
	MOV.W	R7,@R1					;

MOTION_DATCK_EXT:
	FAR_JSR	#_MOTION_DATCK_MOVE,R0				;

	SUB_END
	M_RTS

;
;
;	.GLOBAL	_CHKSPDWORK1;
;	.GLOBAL	_CHKSPDWORK2;
;
;
;
MOTION_DATCK_CLR:
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_PVX_CKSPD_OVBIT,R1	;
	MOV.W	R0,@R1
	SUB_END
	M_RTS



_MOTION_DATCK_MOVE:
	SUB_START

	MOV.L	#_PVX_CKSPD_OVBIT,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_PVP_CKSPD_OVBIT,R1		;
	MOV.W	R0,@R1				;



	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***				***
;	***				***
;	***********************************
_CHGSPD_LIMIT		.EQU	2000	;
_CHGSPD_HIS		.EQU	20	;2.0%

_CHGSPD_LIMIT_CALC:
	SUB_START

	PUSH_REG1 R14

	FAR_JSR	#_FPU_CALC_SPD,R0		;LIMIT演算 R0~R4,R6,FPU ANS=R2 100.00%

	MOV.L	#_CHKSPDPERWORK1,R4	;//0.1
	MOV.W	@R4,R6			;Vn_1
	MOV.L	#_CHKSPDPERWORK2,R4	;//0.1
	MOV.W	@R4,R1			;Vn


	MOV.W	#1,R4			;
	CMP/EQ	R4,R5			;残"1"[戻り]
	BF	CHGSPD_LMT_CAL300	;

	MOV.L	#_PVP_CKLMT_MDSPD,R14	;戻り速度　ANS
	MOV.W	#BIT15,R8		;戻りBIT15

CHGSPD_LMT_CAL300:

	CMP/EQ	R1,R6				;同じ速度
	BT	CHGSPD_LMT_CAL900		;問題なし
	CMP/GT	R6,R1				;加速
	BT	CHGSPD_LMT_CAL600		;YES

;;;;NO-CHK	MOV.W	#_CHGSPD_HIS,R4		;
;;;;NO-CHK	ADD	R4,R2			;2.0%
;	------ 減速----
	CMP/GT	R1,R2			;Vn < LIMIT
	BF	CHGSPD_LMT_CAL800	;NO! OK
	OR	R8,R7			;赤信号ｾｯﾄ
	M_BRA	CHGSPD_LMT_CAL800	;

CHGSPD_LMT_CAL600
;	----- 加速 -------
;;;;NO-CHK	MOV.W	#_CHGSPD_HIS,R4		;
;;;;NO-CHK	SUB	R4,R2			;2.0%

	CMP/GT	R2,R1			;LIMIT < Vn
	BF	CHGSPD_LMT_CAL800	;NO! OK
	OR	R8,R7			;赤信号ｾｯﾄ
CHGSPD_LMT_CAL800:

;;;;NO-CHK	CMP/PZ	R2
;;;;NO-CHK	BT	CHGSPD_LMT_CAL850	;
;;;;NO-CHK	XOR	R0,R0			;
;;;;NO-CHKCHGSPD_LMT_CAL850:			;
;;;;NO-CHK	MOV.W	#D'1001,R4		;
;;;;NO-CHK	CMP/GT	R2,R4			;
;;;;NO-CHK	BT	CHGSPD_LMT_CAL900	;
;;;;NO-CHK	MOV	R4,R2			;
;;;;NO-CHKCHGSPD_LMT_CAL900:			;

	MOV.W	R2,@R14			;LIMIT SET

CHGSPD_LMT_CAL900:
	POP_REG1 R14

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***				***
;	***				***
;	***				***
;	***				***
;	***********************************
;	.GLOBAL	_CHKSPDWORK1;//PLS/S
;	.GLOBAL	_CHKSPDWORK2;//PLS/
;	.GLOBAL	_CHKPOSWORK;//PLS
;	.GLOBAL	_CHKSPDWORKANS;//PLS/S
;	.GLOBAL	_CHKSPDWORKVMAX;//PLS/S
;	.GLOBAL	_CHKSPDWORKTMAX;//ms
;	.GLOBAL	_CHKSPDANSPER;// 1%単位ﾃﾞｰﾀ 100.00
;
;
;
_FPU_CALC_SPD
	SUB_START

	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_CALCSPD_ZERO			;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	CMP/PZ	R3					;
	BT	FPU_CALCSPD_050				;
	NEG	R3,R3					;
FPU_CALCSPD_050:					;


;;;	-------- R1*R2*R3/R4 ------
;;;	LDS	R2,FPUL					;
;;;	FLOAT	FPUL,FR2				;
;;;
;;;	LDS	R1,FPUL					;
;;;	FLOAT	FPUL,FR1				;
;;;
;;;	LDS	R4,FPUL					;
;;;	FLOAT	FPUL,FR4				;
;;;
;;;	FMUL	FR1,FR2					;FR1*FR2==FR2
;;;
;;;	LDS	R3,FPUL					;
;;;	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)
;;;
;;;	FMUL	FR1,FR2					;FR2
;;;	FADD	FR2,FR2					;FR2*2
;;;	FDIV	FR4,FR2					;
;;;	----------------------------

;	-------- R1*R2/R4 *R3 ------
	LDS	R2,FPUL					;
	FLOAT	FPUL,FR2				;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1*FR2=>FR2

	FDIV	FR4,FR2					;

	FTRC	FR2,FPUL				;
	STS	FPUL,R0					;小数点削除
	LDS	R0,FPUL					;
	FLOAT	FPUL,FR2				;


	FADD	FR2,FR2					;FR2*2

	LDS	R3,FPUL					;
	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)

	FMUL	FR1,FR2					;FR2
;	----------------------------

	MOV.L	#_CHKSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1==FR2

	MOV.L	#_CHKSPDWORK2,R0			;//PLS/S
	MOV.L	@R0,R2					;
	CMP/HS	R1,R2					;
	BF	FPU_CALCSPD_100				;

	FADD	FR1,FR2					;加速
	M_BRA	FPU_CALCSPD_200				;

FPU_CALCSPD_100:					;
	FNEG	FR2
	FADD	FR1,FR2					;減速
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	CMP/PL	R2					;
	BF	FPU_CALCSPD_ZERO			;
FPU_CALCSPD_200:					;
	FSQRT	FR2					;
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;

	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	R2,@R0					;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R4					;
	MOV.L	#D'1000,R1				;100.0%


	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;

	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;

	FMUL	FR1,FR2					;FR1(1000)*FR2(pls/s)/(VMAX)
	FDIV	FR4,FR2					;


	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.W	#_CHGSPD_LIMIT,R4			;200.0%
	CMP/HS	R2,R4					;
	BT	FPU_CALCSPD_EXT				;
	MOV	R4,R2					;
	M_BRA	FPU_CALCSPD_EXT				;0.1%

FPU_CALCSPD_ZERO:
	MOV.L	#0,R2					;0.1%

FPU_CALCSPD_EXT:
	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data 下1桁は.0

	SUB_END
	M_RTS





