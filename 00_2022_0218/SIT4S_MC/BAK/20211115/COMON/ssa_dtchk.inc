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

_MOTION_DATASPD_CHK:
	SUB_START
	MOV.L	#_SETX_POS_CTL_MATH,R1			;
	MOV.W	@R1,R0					;
	TST	#_DMATH_DNDRIV,R0			;
	TST_BIT_ON MOTION_DATSPDCK_050			;


	MOV.L	#_SET1_ACCLAT_TIM1,R1			;
	MOV.W	@R1,R2					;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1					;
	M_BRA	MOTION_DATSPDCK_100

;	-------------- ふりこ------------
MOTION_DATSPDCK_050:
	MOV.L	#_ACCB_ACCLAT_TIM1,R1		;
	MOV.W	@R1,R2				;
	MOV.L	#_CHKSPDWORKTMAX,R1			;//ms
	MOV.L	R2,@R1				;
	M_BRA	MOTION_DATSPDCK_100



MOTION_DATSPDCK_100:
	MOV.L	#_LINK_MAX_SPD_PLS,R1	;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	MOV.L	@R1,R2			;
	MOV.L	#_CHKSPDWORKVMAX,R1	;//PLS/S
	MOV.L	R2,@R1			;

	XOR	R0,R0			;
	MOV.L	#_PVX_CKAGL_OVBIT,R1	;角度ｵｰﾊﾞ信号
	MOV.W	R0,@R1			;

	MOV.L	#_SETX_POS_STEP_MAX,R1			;
	MOV.W	@R1,R5					;設定1~10
	ADD	#1,R5					;1段の場合    2個の速度ﾁｪｯｸ
							;10段の場合  11個の速度ﾁｪｯｸ

	XOR	R7,R7			;速度ｵｰﾊﾞ信号 STEP演算結果
	MOV.W	#BIT0,R8		;

	XOR	R0,R0					;
	MOV.L	#_CHKSPDPOSOFS,R1			;
	MOV.W	R0,@R1					;//2014-06-10


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


MOTION_DATSPDCK_200LOP:
	MOV.W	#1,R4					;残数
	CMP/EQ	R4,R5					;残数=1 行程MAX
	BF	MOTION_DATSPDCK_220

;	------------- 最終段の演算----------------
;;;;;	MOV.L	#_SVP_UPAREA_SPD0,R1			;行程MAX時は戻り速度
;;;;;	MOV.W	@R1,R2					;
;;;;;	M_BRA	MOTION_DATSPDCK_240			;
	M_BRA	MOTION_DATSPDCK_800			;



MOTION_DATSPDCK_220
;	-------- 設定速度%-------------------
	MOV.W	@R13,R2					;
MOTION_DATSPDCK_240
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%

;	---------設定速度PLS/S---------------
	MOV.L	@(R0,R9),R2				;目標速度PLS/S
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;WORK=0 SPEED


;	---------設定角度PLS---------------
	MOV.L	@(R0,R11),R2				;目標位置
	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	R2,@R1					;




;;;;不要	MOV.L	@(R0,R10),R3				;
;;;;不要	TST	R3,R3					;tim != 0 停止行程
;;;;不要		TST_BIT_ON MOTION_DATSPDCK_500			;

	MOV.L	@(R0,R12),R2				;
	MOV.L	#_CHKSPDPOSINFO,R1			;
	MOV.W	R2,@R1					;INFO SAVE(BIT1=1逆転)

	MOV.W	#BIT0,R4				;
	TST	R4,R2					;
	TST_BIT_OF MOTION_DATSPDCK_500			;停止の行程(正→反,反転→正,ﾀｲﾏ有)

;;;;;逆転の行程も演算する	MOV.W	#BIT1,R4				;
;;;;;逆転の行程も演算する	TST	R4,R2					;
;;;;;逆転の行程も演算する	TST_BIT_ON MOTION_DATSPDCK_500			;逆転行程は演算しない



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
	M_BRA	MOTION_DATSPDCK_600	;


;	--------- 停止行程[位置の演算を行う]------------
MOTION_DATSPDCK_500:

	PUSH_REG1 R0	;ADR
	FAR_JSR	#_CHGPOS_LIMIT_CALC,R0
	POP_REG1 R0			;ADR


;	--------- 速度は0からはじめる-----------
	XOR	R2,R2					;
	MOV.L	#_CHKSPDWORK2,R1			;次の演算には0から開始ｽﾙ
	MOV.L	R2,@R1					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%

MOTION_DATSPDCK_600:

	ADD	#4,R0					;
	MOV.L	#_CHKSPDPOSOFS,R1			;
	MOV.W	R0,@R1					;//2014-06-10

	ADD	#-1,R5					;
	TST	R5,R5					;
	TST_BIT_OF MOTION_DATSPDCK_700			;
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
	M_BRA	MOTION_DATSPDCK_200LOP			;

MOTION_DATSPDCK_700:
	M_BRA	MOTION_DATSPDCK_900

;	----------- 最終速度-----------
MOTION_DATSPDCK_800:
	MOV.L	#_SVP_UPAREA_SPD0,R1			;行程MAX時は戻り速度
	MOV.W	@R1,R2					;
	MOV.L	#_CHKSPDPERWORK2,R1			;
	MOV.W	R2,@R1					;0.1%
;	---------設定速度PLS/S---------------
	MOV.L	@(R0,R9),R2				;目標速度PLS/S
	MOV.L	#_CHKSPDWORK2,R1			;
	MOV.L	R2,@R1					;
;	---------設定角度PLS---------------
	MOV.L	@(R0,R11),R2				;目標位置
	MOV.L	#_CHKPOSWORK2,R1			;
	MOV.L	R2,@R1					;


	PUSH_REG1 R0	;ADR
	FAR_JSR	#_LASTSPD_LIMIT_CALC,R0
	POP_REG1 R0			;ADR




MOTION_DATSPDCK_900:

	MOV.L	#_PVX_CKSPD_OVBIT,R1			;赤表示(BIT0~BIT9 BIT15:戻速度)
	MOV.W	R7,@R1					;

MOTION_DATSPDCK_EXT:
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
;;;MOTION_DATSPDCK_CLR:
;;;	SUB_START
;;;	XOR	R0,R0			;
;;;	MOV.L	#_PVX_CKSPD_OVBIT,R1	;
;;;	MOV.W	R0,@R1
;;;	SUB_END
;;;	M_RTS



_MOTION_DATCK_MOVE:
	SUB_START

;	-------------------------------
	MOV.L	#_PVX_CKSPD_OVBIT,R1		;
	MOV.W	@R1,R0				;
	MOV.L	#_PVP_CKSPD_OVBIT,R1		;
	MOV.W	R0,@R1				;

;	-------------------------------
	MOV.L	#_PVX_CKAGL_OVBIT,R1			;角度ｵｰﾊﾞ信号
	MOV.W	@R1,R0				;
	MOV.L	#_PVP_CKAGL_OVBIT,R1		;
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

;	------ 減速----
	CMP/GT	R1,R2			;Vn < LIMIT
	BF	CHGSPD_LMT_CAL800	;NO! OK
	OR	R8,R7			;赤信号ｾｯﾄ
	M_BRA	CHGSPD_LMT_CAL800	;

CHGSPD_LMT_CAL600
;	----- 加速 -------

	CMP/GT	R2,R1			;LIMIT < Vn
	BF	CHGSPD_LMT_CAL800	;NO! OK
	OR	R8,R7			;赤信号ｾｯﾄ
CHGSPD_LMT_CAL800:


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


;	-------- α・Ｓ=R1*R2/R4 *R3 ------
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

	FMUL	FR1,FR2					;FR2：２・α・Ｓ
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



;	***************************************************
;	***						***
;	***		モーション停止位置チェック	***
;	***						***
;	***************************************************
;	今の速度で停止可能かをチェックする。
;	V^2= 2･α･S
;	S= V^2/(2･α)
;	R2(SPD)*R2(SPD)
;	正転(S2>S1) S2-S ≧S1 ･･･ok　 S2-S<S1　then S1=S2-S
;	逆転(S2<S1) S2+S ≧S1 ･･･ok　 S2+S<S1　then S1=S2+S
;
_DCHKDIGHOS	.EQU	20	

_CHGPOS_LIMIT_CALC:
	SUB_START

	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_CALCPOS_ZERO			;[時間0なのでどんな加減速も可能]


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	CMP/PZ	R3					;
	BT	FPU_CALCPOS_050				;
	NEG	R3,R3					;
FPU_CALCPOS_050:					;


;	-------- α=R1*R2/R4  ------
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

	TST	R0,R0					;
	TST_BIT_OF FPU_CALCPOS_ZERO			;α=0 演算不可

;	--------- FR2=2α --------------
	FADD	FR2,FR2					;FR2*2：FR2=2*α


;	----------------------------
;;;[[[2014-0808]]]	MOV.L	#_CHKSPDWORK2,R0			;//PLS/S
;;;[[[2014-0808]]]	MOV.L	@R0,R1					;Vn
	MOV.L	#_CHKSPDWORK1,R0			;//PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1:V^2


	FDIV	FR2,FR1					;FR1(V^2)/FR2(2α)
	FTRC	FR1,FPUL				;
	STS	FPUL,R2					;R2=FR1:距離


	CMP/GE	R2,R3					;R2(演算距離)=<R3(設定)
	BT	FPU_CALCPOS_500				;
							;正常位置

	MOV	R8,R4
	SHLR	R4					;
	MOV.L	#_PVX_CKAGL_OVBIT,R1			;角度ｵｰﾊﾞ信号
	MOV.W	@R1,R0					;
	OR	R4,R0					;ﾁｪｯｸしている1個前
	MOV.W	R0,@R1					;

;	"R2":距離
	MOV.L	#_CHKPOSWORK2,R1			;//PLS
	MOV.L	@R1,R4					;

	ADD	#_DCHKDIGHOS,R2				;20PLS

	MOV.L	#_CHKSPDPOSINFO,R1			;
	MOV.W	@R1,R0					;
	TST	#BIT1,R0				;
	TST_BIT_OF FPU_CALCPOS_100			;正

	NEG	R2,R2					;

FPU_CALCPOS_100:
	SUB	R2,R4					;R4:

	MOV	R4,R2					;R2=S2-LNGTH

;	-- ﾊﾟﾙｽ----
	MOV.L	#_CHKPOSWORKANS,R1				;//PLS(2014-06-10位置ﾁｪｯｸ用)
	MOV.L	R2,@R1						;

	MOV.L	#_SETY_INCPLS_HOSM01X,R0			;//0.1度
	MOV.L	@R0,R1						;
	MOV.L	#_CALC_MEM_1REV_MUL_NROT,R0			;
	MOV.L	@R0,R4						;R2:X回転
	CMP/GE	R2,R4						;R2 <= R4
	BT	FPU_CALCPOS_150
	SUB	R4,R2						;
FPU_CALCPOS_150:
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;R2*1REV*HOSN/HOSM



	FAR_JSR	#_PV_LINK_DG_CHG_CLNK_DG1,R0			;R0,R1,R2のみ使用

	MOV.L	#_CHKPOSANSDIG,R1				;
	MOV.W	R2,@R1						;

	MOV.L	#_CHKSPDPOSOFS,R1				;
	MOV.W	@R1,R0						;
	TST	R0,R0
	TST_BIT_OF FPU_CALCPOS_EXT				;
	ADD	#-4,R0						;
	SHLR	R0						;1/2
	MOV.L	#_PVP_CKLMT_AGLTOP,R1				;
	ADD	R0,R1						;
	MOV.W	R2,@R1						;

FPU_CALCPOS_500:
FPU_CALCPOS_ZERO:
FPU_CALCPOS_EXT:

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	最終速度（戻り速度）		***
;	***					***
;	*******************************************
;	Vn^2 > α・S＋Vn_1^2/2なら速度異常で
;	ﾘﾐｯﾄ速度=√(α・S＋Vn_1^2/2)

_LASTSPD_LIMIT_CALC:
	SUB_START

	PUSH_REG1 R14

;	-----------------------------------------------
;	-----------------------------------------------
;	-----------------------------------------------
	MOV.L	#_CHKSPDWORKTMAX,R0			;//
	MOV.L	@R0,R4					;
	TST	R4,R4					;
	TST_BIT_OF FPU_LASTCALCSPD_ZERO			;


	MOV.L	#_CHKSPDWORKVMAX,R0			;//PLS/S
	MOV.L	@R0,R2					;
	MOV.L	#D'1000,R1				;

	MOV.L	#_CHKPOSWORK2,R0			;//PLS
	MOV.L	@R0,R3					;
	MOV.L	#_CHKPOSWORK1,R0			;//PLS/
	MOV.L	@R0,R6					;
	SUB	R6,R3					;
	TST	R3,R3
	TST_BIT_ON FPU_LASTCALCSPD_030			;
	M_BRA	FPU_LASTCALCSPD_ZERO			;距離=0　異常 ありえない

FPU_LASTCALCSPD_030:					;
	CMP/PZ	R3					;
	BT	FPU_LASTCALCSPD_050			;
	NEG	R3,R3					;
FPU_LASTCALCSPD_050:					;


;	-------- α・Ｓ=R1*R2/R4 *R3 ------
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

	LDS	R3,FPUL					;
	FLOAT	FPUL,FR1				;FR1(R3)*FR2(R1*R2)

	FMUL	FR1,FR2					;FR2：α・Ｓ

;	----------------------------

	MOV.L	#_CHKSPDWORK1,R0			;//Vn_1:PLS/S
	MOV.L	@R0,R1					;

	LDS	R1,FPUL					;
	FLOAT	FPUL,FR1				;
	FMUL	FR1,FR1					;FR1*FR1==FR2

	MOV.W	#2,R4
	LDS	R4,FPUL					;
	FLOAT	FPUL,FR4				;
	FDIV	FR4,FR1					;

;	FR1 =      Vn_1^2 /2 = FR1*FR1/FR4

	FADD	FR1,FR2					;FR2:α×S+Vn_1^2/2
	FSQRT	FR2					;
	FTRC	FR2,FPUL				;
	STS	FPUL,R2					;
	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	R2,@R0					;R2=√(α×S+Vn_1^2/2)

;	---------------- ﾘﾐｯﾄ速度演算----------------

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
	BT	FPU_LASTCALCSPD_EXT			;
	MOV	R4,R2					;
	M_BRA	FPU_LASTCALCSPD_EXT			;0.1%

FPU_LASTCALCSPD_ZERO:
	MOV.L	#0,R2					;0.1%

FPU_LASTCALCSPD_EXT:
	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	R2,@R0					;0~100.0%data 下1桁は.0

;	-----------------------------------------------
;	-----------------------------------------------
;	-----------------------------------------------
	MOV.L	#_PVP_CKLMT_MDSPD,R14	;戻り速度　ANS
	MOV.W	#BIT15,R8		;戻りBIT15

	MOV.L	#_CHKSPDWORKANS,R0			;//PLS/S
	MOV.L	@R0,R2					;R2=√(α×S+Vn_1^2/2)

	MOV.L	#_CHKSPDWORK2,R0	;//PLS/S
	MOV.L	@R0,R1			;速度

	CMP/GT	R2,R1			;LIMIT < Vn
	BF	LASTSPD_LMT_CAL800	;NO! OK
	OR	R8,R7			;赤信号ｾｯﾄ
LASTSPD_LMT_CAL800:

	MOV.L	#_CHKSPDANSPER,R0			;
	MOV.W	@R0,R2					;0~100.0%data 下1桁は.0
	MOV.W	R2,@R14					;LIMIT SET

LASTSPD_LMT_CAL900:
	POP_REG1 R14

	SUB_END
	M_RTS








;	*******************************************
;	***					***
;	***					***
;	***	戻り速度指定異常		***
;	***	戻り1個前角度指定異常		***
;	***	2015-07-07			***
;	***	[h2w 2015-05-15~]		***
;	***					***
;	*******************************************
;	<>234.0,234.1信号=0,青丸=0,行程ﾁｪｯｸ=0 [反転,ふりこ]
;	<>234.0,234.1信号=*,青丸=*,行程ﾁｪｯｸ=* [回転-段取,原点,連続,寸動,安一]
;	運転ﾓｰﾄﾞの判定はｼｰｹﾝｽにて行う
;	ﾘｾｯﾄ中はOFFする
;
;
;
;;;;;	_PVP_CKSPD_LMBIT	;
;;;;;	_PVP_CKSPD_STEP		;速度ﾘﾐｯﾄ対象行程 0:無し 1:1以上の行程,,,10(10行程と戻り),11(戻り)
;;;;;
;;[1]運転方式 回転,反転,振子
;;

	.IMPORT	_WORD_BIT_TBL0	;


_SPD_POS_SET_ERRCHK1
	SUB_START


	MOV.L	#_SET1_MRTION_SEL1,R1	;[_SEQ_DP_TOP+50*2]
	MOV.W	@R1,R0
	TST	#_DMATH_CNTROT,R0		;
	TST_BIT_ON SPD_SET_ERCK1_020		;回転

;	---- 反転,振子 -----
	FAR_JSR	#_SPD_CKSIG_ALL_CLR,R0		;
	M_BRA	SPDPOS_SET_ERCK1_END		;

SPD_SET_ERCK1_020				;

;R7:234,0/234.1
;R8:ﾁｪｯｸ対象行程




;	-------------------------------------------------------------------
;	---		速度の異常検知処理開始				---
;	-------------------------------------------------------------------
	MOV.L	#(_PAR_MODORI_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R6							;1%(R6は0.1%ﾃﾞｰﾀでこの関数間はKEEP)
	TST	R6,R6							;
	TST_BIT_ON SPD_SET_ERCK1_100					;ﾁｪｯｸする

;	----速度制限無し-----
	FAR_JSR	#_SPD_CKSIG_ALL_CLR,R0					;
	M_BRA	SPDPOS_SET_ERCK1_END					;


;	-------------------------------------------------------------------
;	---	戻り行程速度ﾁｪｯｸ INPUT R6(速度1%ﾃﾞｰﾀ),R7(異常ANS=0)	---
;	-------------------------------------------------------------------
;	R8:異常検出行程
;	R9:青丸印
SPD_SET_ERCK1_100
	XOR	R7,R7					;
	MOV.W	#BIT15,R8				;戻り行程
	XOR	R9,R9					;青丸

	REG_MUL10 DAT_REG=R6,WKREG1=R0			;ROMﾊﾟﾗ=R6 0.1%

	MOV.L	#_SVP_UPAREA_SPD0,R1			;戻速度
	MOV.W	@R1,R2					;0.1%~100.0%
	CMP/HS	R6,R2					;R6(ROMﾊﾟﾗ*10)
	BT	SPD_SET_ERCK1_200			;ROM <= SV_SPD THEN OK
	MOV.W	#BIT0,R0				;
	OR	R0,R7					;234.0:ERR-SET
	MOV.W	#BIT15,R0				;
	OR	R0,R9					;青丸:戻り行程
SPD_SET_ERCK1_200:					;

	MOV.L	#_SET1_OVERLIDE_COF,R0			;
	MOV.W	@R0,R1					;ｵｰﾊﾞﾗｲﾄﾞ比率
	MOV.W	#_OVRLIDE_LATE_MAX,R4				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;R2(戻り速度)*ｵｰﾊﾞﾗｲﾄﾞ

	CMP/HS	R6,R2					;R6(ROMﾊﾟﾗ*10)
	BT	SPD_SET_ERCK1_300			;ROM <= SV_SPD' THEN OK
	MOV.W	#BIT1,R0				;
	OR	R0,R7					;234.1:ALM-SET
SPD_SET_ERCK1_300:					;



;	-------------------------------------------------------------------
;	---		角度の異常検知処理開始				---
;	-------------------------------------------------------------------
	MOV.L	#(_PAR_LAST_MAXDIG-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R6							;1度
	TST	R6,R6							;
	TST_BIT_ON POS_SET_ERCK1_100					;

	FAR_JSR	#_SPD_CKSIG_SET1,R0					;角度でのﾁｪｯｸは無し:戻り行程のみﾁｪｯｸ対象

	M_BRA	SPDPOS_SET_ERCK1_END					;


;	---------------------------------------------------------------------------
;	---	角度ﾁｪｯｸ INPUT R6(1度ﾃﾞｰﾀ:ｸﾗﾝｸ),R7(異常ANS input BIT0,BIT1)	---
;	---------------------------------------------------------------------------
;	戻り行程は評価済み
;
;	ANS R7:234.0(ERR) 234.1(ALM) 234.2(ERR) 234.3(ALM)
;	ANS R8:評価すべき行程
;	ANS R9:青丸
;
;
POS_SET_ERCK1_100

	REG_MUL10	DAT_REG=R6,WKREG1=R0			;ROMﾊﾟﾗ=R6 0.1度

	MOV.L	#_SETX_POS_STEP_MAX,R1				;//設定=1~10(2~11)
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_OF POS_SET_ERCK1_400				;

	MOV.L	#_WORD_BIT_TBL0,R14
	ADD	R0,R14
	ADD	R0,R14
	MOV.W	@R14,R14					;BITn 
								;MAX=1行程  =BIT0,
								;MAX=2行程  =BIT1
								;MAX=10行程 =BIT9
	MOV	R0,R3						;LOOP-CNT(R3)
	ADD	#-1,R0
	SHLL	R0						;*2 BYTE
	MOV.L	#_SVP_OBJECT_DIG_TOP,R10			;
	ADD	R0,R10						;
	MOV.L	#_SVP_OBJECT_TIM_TOP,R11			;01段目停止時間
	ADD	R0,R11						;
	MOV.L	#_SVP_OBJECT_SPD_TOP,R12			;01段目移動速度
	ADD	R0,R12						;
	MOV.L	#H'7FFFFFFF,R2					;初期値:R2=MAX角度

	MOV.L	#(_PAR_MODORI_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R13							;1%(R13は0.1%ﾃﾞｰﾀでこの関数間はKEEP)
	REG_MUL10 DAT_REG=R13,WKREG1=R0					;ROMﾊﾟﾗ=R13 0.1%


POS_SET_ERCK1_150LOP

	MOV.W	@R11,R1						;TIMER
	TST	R1,R1						;
	TST_BIT_ON POS_SET_ERCK1_400				;停止有り[EXIT]

	MOV	R2,R1						;
	MOV.W	@R10,R2						;0.1度ﾃﾞｰﾀ
	CMP/HI	R1,R2						;R1 < R2(戻った)
	BT	POS_SET_ERCK1_400				;停止有り

	MOV	R3,R0						;
	CMP/EQ	#1,R0						;1行程?
	BT	POS_SET_ERCK1_160				;YES

	MOV	R10,R4						;
	ADD	#-2,R4						;
	MOV.W	@R4,R4						;
	CMP/HI	R2,R4						;R2(2段目)<R4(1段目):
	BT	POS_SET_ERCK1_400				;今回逆転です

POS_SET_ERCK1_160





	CMP/HS	R2,R6						;R2<=R6 NOMAL
	BT	POS_SET_ERCK1_400				;POS<=ROM THEN OK(もうこれより若い段数はチェック不要)

;	-----評価対象行程------
	OR	R14,R8						;

;	----------------------
	MOV.W	@R12,R1						;速度
	CMP/HS	R13,R1						;最小値(R13)=< R1
	BT	POS_SET_ERCK1_180				;

;	-----評価結果青丸------
	OR	R14,R9						;
	MOV.W	#BIT0,R0					;
	OR	R0,R7						;234.0

POS_SET_ERCK1_180:						;
	PUSH_REG1 R2
	MOV.L	#_SET1_OVERLIDE_COF,R0				;
	MOV.W	@R0,R2						;ｵｰﾊﾞﾗｲﾄﾞ比率
	MOV.W	#_OVRLIDE_LATE_MAX,R4				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;R1(戻り速度)*ｵｰﾊﾞﾗｲﾄﾞ(R2)
	
	CMP/HS	R13,R2						;最小値(R13)=< R1
	BT	POS_SET_ERCK1_190				;

;	-----評価結果ｵｰﾊﾞﾗｲﾄﾞ------
	MOV.W	#BIT1,R0					;
	OR	R0,R7						;234.1　WARINING

POS_SET_ERCK1_190						;
	POP_REG1 R2


POS_SET_ERCK1_200:						;
	SHLR	R14						;
	ADD	#-1,R3						;
	ADD	#-2,R10						;角度
	ADD	#-2,R11						;ﾀｲﾏ
	ADD	#-2,R12						;速度

	TST	R3,R3
	TST_BIT_OF POS_SET_ERCK1_400				;
	M_BRA	POS_SET_ERCK1_150LOP				;


POS_SET_ERCK1_390:						;
POS_SET_ERCK1_400:						;

	FAR_JSR	#_SPD_CKSIG_SET1,R0



SPDPOS_SET_ERCK1_END:

	SUB_END
	M_RTS


;
;	2015-07-07
;
;
_SPD_CKSIG_ALL_CLR
	SUB_START

;;;;	XOR	R0,R0				;
;;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB234,R1	;
;;;;	MOV.W	R0,@R1				;

;	-------- 2015-08-19----------
	MEM1_BIT0_F_ADCLR MEM=_SQ_CBWK_TOP+_WKSQCB234,LG=W,BIT=~(BIT3+BIT2+BIT1+BIT0),WKRG1=R1,WKRG2=R4
	XOR	R0,R0				;

	MOV.L	#_PVP_CKSPD_LMBIT,R1
	MOV.W	R0,@R1				;

	MOV.L	#_PVP_CKSPD_STPBT,R1		;速度ﾘﾐｯﾄ対象行程 BIT0~BIT9,BIT15(ﾁｪｯｸ対象行程)
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS

_SPD_CKSIG_SET1
	SUB_START
;;;;	MOV.L	#_SQ_CBWK_TOP+_WKSQCB234,R1	;
;;;;	MOV.W	R7,@R1				;

;	--------- 2015-08-19-----------
	MOV.W	#(BIT3+BIT2+BIT1+BIT0),R4
	MOV.L	#_SQ_CBWK_TOP+_WKSQCB234,R1	;実際の仕様はBIT0,BIT1だがBIT2,BIT3を予約
	MOV.W	@R1,R0				;
	AND	R4,R7				;
	NOT	R4,R4
	AND	R4,R0				;
	OR	R0,R7
	MOV.W	R7,@R1				;


	MOV.L	#_PVP_CKSPD_STPBT,R1		;速度ﾘﾐｯﾄ対象行程 BIT0~BIT9,BIT15(ﾁｪｯｸ対象行程)
	MOV.W	R8,@R1				;

	MOV.L	#_PVP_CKSPD_LMBIT,R1
	MOV.W	R9,@R1				;

	SUB_END
	M_RTS

