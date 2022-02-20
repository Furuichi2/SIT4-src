;	----------2015-09-30 100段-------------
;//	***********************************
;//	***				***
;//	***	99段仕様		***
;//	***				***
;//	***				***
;//	***********************************
;	100段仕様時にﾃﾞｰﾀが揃うまで異常関連の停止が必要

	.EXPORT	_DTMAKE_100STEP_1MS
	.EXPORT	_DTMAKE_100STEP_MAIN_LOP


;//	***********************************
;//	***				***
;//	***	99段仕様		***
;//	***	1MSで実行する		***
;//	***				***
;//	***********************************
_DTMAKE_100STEP_1MS
	SUB_START

	MOV.L	#_SYS_100STEP_USE,R1		;//100段ﾊﾝﾄﾞｼｪｲｸ使用する
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_OF DTMAKE_100STEP1MS_100	;

	FAR_JSR	#_DT_100STEP_SVLOAD,R0

DTMAKE_100STEP1MS_100

	SUB_END
	M_RTS

;//	***********************************
;//	***				***
;//	***	99段仕様		***
;//	***	メインで実行する	***
;//	***				***
;//	***********************************
_DTMAKE_100STEP_MAIN_LOP
	SUB_START
	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	dpram 設定ﾃﾞｰﾀ読出		***
;	***					***
;	*******************************************
;	dpram=>work この際に以下をﾁｪｯｸする
;	角度,位置ﾃﾞｰﾀ変化
;	ﾀｲﾏが0から0以外に変化,ﾀｲﾏが0以外から0に変化
;	DPRAM-ｼﾘｱﾙ1STEP領域->	_SVPX1_OBJECT_POS_TOP
;				_SVPX1_OBJECT_DIG_TOP
;				_SVPX1_OBJECT_SPD_TOP,R3
;				_SVPX1_OBJECT_TIM_TOP,R3
;
;
_DT_100STEP_SVLOAD
	SUB_START
	MOV.L	#_SYS_100STEP_USE,R1	;//100段ﾊﾝﾄﾞｼｪｲｸ使用する
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_ON DT_100STEP_SVLD_010	;
	M_BRA	DT_100STEP_SVLD_EXT


DT_100STEP_SVLD_010
	MOV.L	#_SVP_MOT_SEND_REQ,R5	;ﾓｰｼｮﾝﾃﾞｰﾀ送信段No.
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
	XOR	R7,R7			;BIT0:位置 BIT1:角度 BIT2:タイマ
	ADD	#-1,R0			;1段目->DATA[0]に入る
	SHLL	R0			;
	MOV	R0,R10			;OFFSET 2BYTE
	SHLL	R0			;
	MOV	R0,R11			;OFFSET 4BYTE


	MOV.L	#_SVP_OBJECT_PS,R1		;目標位置
	MOV.L	@R1,R2				;
	MOV.L	#_SVPX1_OBJECT_POS_TOP,R3	;
	ADD	R11,R3				;
	MOV.L	@R3,R4				;
	MOV.L	R2,@R3				;
	CMP/EQ	R4,R2				;ﾃﾞｰﾀは同じ
	BT	DT_100STEP_SVLD_200
	MOV.B	#BIT0,R7		;
DT_100STEP_SVLD_200

	MOV.L	#_SVP_OBJECT_DG,R1	;目標角度
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_DIG_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_100STEP_SVLD_300
	MOV.B	#BIT1,R7		;
DT_100STEP_SVLD_300

	MOV.L	#_SVP_OBJECT_SP,R1	;目標速度
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R3;	//目標速度
	ADD	R10,R3			;
	MOV.W	R2,@R3			;

	MOV.L	#_SVP_OBJECT_TM,R1	;停止時間
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_TIM_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_100STEP_SVLD_400	;

;[工夫]


DT_100STEP_SVLD_400

	MOV.L	#_SVP_OBJECT_PRS,R1	;目標圧力
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_PRS_TOP,R3	;//目標圧力
	ADD	R10,R3			;
	MOV.W	R2,@R3			;

	MOV.L	#_SVP_MOT_INF,R1	;ﾓｰｼｮﾝ情報(位置/圧)
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_MOT_INF,R3	;ﾓｰｼｮﾝ情報bit0(位置/荷重)
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_100STEP_SVLD_500




DT_100STEP_SVLD_500

;;	MOV.L	#_SVP_FED_DEG,R1	;ﾌｨｰﾀﾞ角度(予備)
;;	MOV.W	@R1,R2			;
;;	MOV.L	#_SVP_FED_POS,R1	;ﾌｨｰﾀﾞ位置(予備)
;;	MOV.L	@R1,R2			;


	TST	R7,R7			;
	TST_BIT_OF DT_100STEP_SVLD_900	;

	MOV.L	#_SV_CHG_FLG2,R1	;
	MOV.L	@R1,R0			;
	OR	#BIT2,R0		;
	MOV.L	R0,@R1			;

DT_100STEP_SVLD_900
	XOR	R0,R0			;
	MOV.W	R0,@R5			;REQ
DT_100STEP_SVLD_EXT
	SUB_END
	M_RTS










;	*******************************************
;	***					***
;	***	dpram 設定ﾃﾞｰﾀ読出		***
;	***					***
;	*******************************************
;	10段仕様
;
_DT_10STEP_SVLOAD
	SUB_START

	MOV.L	#_SYS_100STEP_USE,R1	;//100段ﾊﾝﾄﾞｼｪｲｸ使用する
	MOV.W	@R1,R0			;
	TST	R0,R0			;
	TST_BIT_OF DT_10STEP_SVLD_010	;
	M_BRA	DT_10STEP_SVLD_EXT

DT_10STEP_SVLD_010




	MOV.W	#D'10,R14		;10,9,,,,1
	XOR	R7,R7			;BIT0:位置 BIT1:角度 BIT2:タイマ


DT_10STEP_SVLD_LOP
	MOV	R14,R0			;
	ADD	#-1,R0			;1段目->DATA[0]に入る
	SHLL	R0			;
	MOV	R0,R10			;OFFSET 2BYTE
	SHLL	R0			;
	MOV	R0,R11			;OFFSET 4BYTE


	MOV.L	#_SVP_OBJECT_POS_TOP,R1	;目標位置
	ADD	R11,R1			;
	MOV.L	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_POS_TOP,R3	;
	ADD	R11,R3			;
	MOV.L	@R3,R4			;
	MOV.L	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_10STEP_SVLD_200
	MOV.B	#BIT0,R7		;
DT_10STEP_SVLD_200

	MOV.L	#_SVP_OBJECT_DIG_TOP,R1	;目標角度
	ADD	R10,R1			;
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_DIG_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_10STEP_SVLD_300
	MOV.B	#BIT1,R7		;
DT_10STEP_SVLD_300

	MOV.L	#_SVP_OBJECT_SPD_TOP,R1	;目標速度
	ADD	R10,R1			;
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_SPD_TOP,R3;	//目標速度
	ADD	R10,R3			;
	MOV.W	R2,@R3			;

	MOV.L	#_SVP_OBJECT_TIM_TOP,R1	;停止時間
	ADD	R10,R1			;
	MOV.W	@R1,R2			;
	MOV.L	#_SVPX1_OBJECT_TIM_TOP,R3	;
	ADD	R10,R3			;
	MOV.W	@R3,R4			;
	MOV.W	R2,@R3			;
	CMP/EQ	R4,R2			;ﾃﾞｰﾀは同じ
	BT	DT_10STEP_SVLD_400	;



DT_10STEP_SVLD_400

	MOV.L	#_SVP_OBJECT_PRS_TOP,R1		;目標圧力
	ADD	R10,R1				;
	MOV.W	@R1,R2				;
	MOV.L	#_SVPX1_OBJECT_PRS_TOP,R3	;//目標圧力
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
