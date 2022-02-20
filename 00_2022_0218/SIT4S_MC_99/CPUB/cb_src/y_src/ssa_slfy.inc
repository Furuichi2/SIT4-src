	.IMPORT	_dio_top1



;	***************************************************
;	***						***
;	***						***
;	***		セルフチェックソフト		***
;	***						***
;	***						***
;	***************************************************
;	ssa_self.srcからINCLUDEする

_STEP00	.EQU	0	;
_STEP01	.EQU	1	;
_STEP02	.EQU	2	;
_STEP03	.EQU	3	;
_STEP04	.EQU	4	;
_STEP05	.EQU	5	;
_STEP06	.EQU	6	;
_STEP07	.EQU	7	;
_STEP08	.EQU	8	;
_STEP09	.EQU	9	;
_STEP10	.EQU	10	;
_STEP11	.EQU	11	;
_STEP12	.EQU	12	;
_STEP13	.EQU	13	;
_STEP14	.EQU	14	;
_STEP15	.EQU	15	;

;	======================================== SAITO INS 2002-09-12
;	==== ｾﾙﾌﾁｪｯｸ実処理 ====
	.EXPORT	_SLF_HNDFLG_LOAD	; CPUA,B FLG入れ替えLOAD
	.EXPORT	_SELF_CHECK_ACT		; セルフチェック実処理
	.EXPORT	_SLF_HNDFLG_STORE	; CPUA,B FLG入れ替えSTORE
;	========================================

	.IMPORT	_CPUA_SELF_HAND_FLG		; 自分の状態ﾌﾗｸﾞDPRAM
	.IMPORT	_CPUB_SELF_HAND_FLG		; 相手の状態ﾌﾗｸﾞDPRAM

	.LIST	OFF
;;	.INCLUDE	"ssa_ver1.equ"		; //
;;;;;	.INCLUDE	"ssa_out1.mac"		; //
	.INCLUDE	"ssa_wrmy.ext"		; 
	.include	"ssa_seq1.equ"
	.INCLUDE	"ssa_wram.ext"		; 
	.INCLUDE	"ssa_had1.equ"		; 
	.LIST	ON

	.IMPORT	_dio_top2			;
;;	.IMPORT	_SEQ_CARD_RAM			; ｺﾒﾝﾄｱｳﾄ 2008-07-30 SAITO
	.IMPORT	_SEQAB_DP_TOP			; 2008-07-30 SAITO

	.IMPORT	_FRCYCL_ON			; *FCYCL,RCYCL ON 有効
	.IMPORT	_FRCYCL_OF			; *FCYCL,RCYCL ON 無効

	.IMPORT	_RESET_OUT			; RST ON
	.IMPORT	_RESET_END_OUT			; RST OFF

	.IMPORT	_EMG_STOP			; 非常停止にする

;	--------2014-09-14----------
;;	.IMPORT	_MONI_SELF_STS1;
;;	.IMPORT	_MONI_SELF_STS2;


;	*******************************************
;	***	DPRAM SELF HAND FLG STORE	***
;	*******************************************
;	_SELF_CHECK_ACTの後でCALL
;	*******************************************
;	***	DPRAM SELF HAND FLG LOAD	***
;	*******************************************
;	_SELF_CHECK_ACTの前でCALL
;
_SLF_HNDFLG_LOAD:
	SUB_START
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;	=== CPUA ===
;;;意味無し		MOV.L	#_CPUA_SELF_HAND_FLG,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;意味無し		MOV.W	@R1,R2				;
	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	@R3,R4				;

;;;意味無し		MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;意味無し		MOV.W	R2,@R1				;
	MOV.L	#_SELF_HAND_FLG2,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	R4,@R3				;

	.AELSE
;	=== CPUB ===
	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	@R1,R2				;
;;;意味無し	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;意味無し	MOV.W	@R3,R4				;

;;;意味無し	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;意味無し	MOV.W	R4,@R1				;
	MOV.L	#_SELF_HAND_FLG2,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	R2,@R3				;

	.AENDI

	SUB_END
	M_RTS

;	*******************************************
;	***	DPRAM SELF HAND FLG STORE	***
;	*******************************************
;	_SELF_CHECK_ACTの後でCALL
;
_SLF_HNDFLG_STORE:
	SUB_START
	.AIF	_CB_CPU_SEL EQ	_CB_CPUA
;	=== CPUA ===
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	@R1,R2				;
;;;;;ﾁｮﾝﾎﾞ	MOV.L	#_SELF_HAND_FLG2,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;;;ﾁｮﾝﾎﾞ	MOV.W	@R3,R4				;

	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	R2,@R1				;
;;;;;ﾁｮﾝﾎﾞ	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;;;ﾁｮﾝﾎﾞ	MOV.W	R4,@R3				;

	.AELSE
;	=== CPUB ===
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	@R1,R2				;
;;;;;ﾁｮﾝﾎﾞ	MOV.L	#_SELF_HAND_FLG2,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;;;ﾁｮﾝﾎﾞ	MOV.W	@R3,R4				;

;;;;;	MOV.L	#_CPUA_SELF_HAND_FLG,R1		; 自分の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
;;;;;	MOV.W	R4,@R1				;
	MOV.L	#_CPUB_SELF_HAND_FLG,R3		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	R2,@R3				;

	.AENDI

	SUB_END
	M_RTS



_SELF_CHK_TM	.EQU	D'20000		; 2S

	.IMPORT	_PDDR

;	*******************************************
;	***	セルフチェック実処理ソフト	***
;	*******************************************
_SELF_CHECK_ACT:
	SUB_START
;	===== 2006-04-10(2種類のｾﾙﾌﾁｪｯｸを行うためここでは終らせない) =====
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7ｾﾙﾌﾁｪｯｸ正常完了
	MOV.W	@R1,R0					;

	MOV.L	#_SELF_FLG,R1				;
	MOV.W	@R1,R4					;
	OR	R4,R0					;

	MOV.W	#BIT7,R4				;
	TST	R4,R0					;
	TST_BIT_OF SELF_CHECKACT_STR00			;
	M_BRA _SELF_CHK_ACT_EXIT			; 何もしない

SELF_CHECKACT_STR00:
;		-----------------------------------------

	MOV.L	#_SELF_FLG,R1			; BIT0:ｾﾙﾌﾁｪｯｸ開始指令
	MOV.W	@R1,R0				;
	CMP/EQ	#BIT0,R0			;
	BF	_SELF_CHECK_ACT_CMDCHK020	; 指令ONじゃない THEN JUMP

;	======== ｺﾏﾂ追加<2003-01-28> ===
;;	.IMPORT	_SELF_START_WAIT_TM		;ｾﾙﾌﾁｪｯｸ開始時のWAIT
	MOV.L	#_SELF_START_WAIT_TM,R3		;ｾﾙﾌﾁｪｯｸ開始時のWAIT
	MOV.W	@R3,R2				;
	TST	R2,R2				;
	TST_BIT_OF _SELF_CHECK_ACT_CMDCHK010	;
	M_BRA _SELF_CHK_ACT_EXIT		; 何もしない
_SELF_CHECK_ACT_CMDCHK010:			;

;	------------------ 2014-09-14 KOMA ----------
	XOR	R3,R3
	MOV.L	#_MONI_SELF_STS1,R2		;
	MOV.W	R3,@R2				;
	MOV.L	#_MONI_SELF_STS2,R2		;
	MOV.W	R3,@R2				;
;	-----------------------------------------------

	MOV.W	#BIT0,R3			;
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	R3,@R2				; セルフチェック中セット
	M_BRA	_SELF_CHECK_ACT_CMDCHK100	; 指令ONじゃない THEN JUMP
_SELF_CHECK_ACT_CMDCHK020:
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	@R2,R3				; セルフチェック中 CHECK
	MOV.W	#BIT0,R4			;
	CMP/EQ	R4,R3				;
	BT	_SELF_CHECK_ACT_CMDCHK040	; セルフチェック中 THEN JUMP

	MOV.W	#BIT6,R4			; 異常処理中（中断中）
	CMP/EQ	R4,R3				;
	BT	_SELF_CHECK_ACT_CMDCHK100	;

	M_BRA _SELF_CHK_ACT_EXIT		; 何もしていない THEN EXIT

_SELF_CHECK_ACT_CMDCHK040:
	MOV.W	#BIT6,R3			;
	MOV.L	#_SELF_ACT_FLG,R2		;
	MOV.W	R3,@R2				; 中断中SET

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常処理するよ SET
	MOV.W	R0,@R1				;

_SELF_CHECK_ACT_CMDCHK100:

;;;;;	MOV.L	#_SELF_FLG,R1			; BIT0:ｾﾙﾌﾁｪｯｸ開始指令
;;;;;	MOV.W	@R1,R0				;
;;;;;	MOV.W	#H'003F,R2			;
;;;;;	TST	R2,R0				;
;;;;;	TST_BIT_ON _SELF_CHK_ACT020		;
;;;;;	M_BRA _SELF_CHK_ACT_EXIT		; 指令ON、ﾁｪｯｸ中じゃない THEN EXIT

_SELF_CHK_ACT020:
;	*** 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ ***
	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞ異常STEPになったかﾁｪｯｸ
	MOV.W	@R1,R0				;
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_ACT100		; 異常になっていない THEN JUMP

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ異常処理するよ SET
	MOV.W	R0,@R1				;

_SELF_CHK_ACT100:
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;

;	*** セルフ工程０  セルフチェックやるよ！ ***
_SELF_CHK_STEP00:
	MOV.W	#_STEP00,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP01		; STEP=0 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP00,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP00_020		;

	MOV.W	#_STEP01,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP00_EXT		;

_SELF_CHK_STEP00_020:

	MOV.W	#_STEP01,R0			; STEP <- 1
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ1SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP00_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程１ 相手待ち ***
_SELF_CHK_STEP01:
	MOV.W	#_STEP01,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP02		; STEP=1 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP01,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP01_020		;

	MOV.W	#_STEP02,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP01_EXT		;
_SELF_CHK_STEP01_020:

	MOV.W	#_STEP02,R0			; STEP <- 2
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ2SET セルフチェックＯＮチェック開始
	MOV.W	R0,@R1				;

_SELF_CHK_STEP01_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程２ ***
_SELF_CHK_STEP02:
	MOV.W	#_STEP02,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP03		; STEP=2 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP02,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP02_020		;

	MOV.W	#_STEP03,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP02_EXT		;
_SELF_CHK_STEP02_020:

	FAR_JSR	#_SELF_ONCHECK_INIT,R0		; セルフＯＮチェックイニシャル

	MOV.W	#_STEP03,R0			; STEP <- 3
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ3SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP02_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程３ ＯＮチェック ***
_SELF_CHK_STEP03:
	MOV.W	#_STEP03,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP04		; STEP=3 NO THEN JUMP

	MOV.L	#_REAL_INP1_DATA,R1		; 
	MOV.W	@R1,R1				;
	MOV.W	#BIT3,R2			;
	AND	R2,R1				;
	TST	R1,R1				; *CHK OFF THEN WAIT
	BT	_SELF_CHK_STEP03_010		; ON THEN JUMP

	FAR_JSR	#_SELF_ONCHECK_INIT,R0		; セルフＯＮチェックイニシャル
	M_BRA	_SELF_CHK_STEP03_EXT		;

_SELF_CHK_STEP03_010:
	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP03,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP03_020		;

	MOV.W	#_STEP04,R2			; 相手がすでに進んでいてもチェック続行
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP03_EXT		;
_SELF_CHK_STEP03_020:

	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	@R1,R1				;
	TST	R1,R1				;
	TST_BIT_OF _SELF_CHK_STEP03_ERR		; SELF CHECK TIMER UP THEN ERR

	FAR_JSR	#_SELF_ON_CHECK,R0		; セルフＯＮチェック
;	---------- 2014-09-14 調査-------
	MOV.L	#_MONI_SELF_STS1,R0		;
	MOV.W	R10,@R0				;
;	---------------------------------

	MOV.W	#(BIT2+BIT1+BIT0),R0		;
	CMP/EQ	R0,R10				; チェック完了CHECK
	BF	_SELF_CHK_STEP03_EXT		; 未完了 THEN JUMP

	MOV.W	#_STEP04,R0			; STEP <- 4
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ4SET
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_STEP03_EXT		;

_SELF_CHK_STEP03_ERR:
	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ10SET NEXT 異常処理
	MOV.W	R0,@R1				;

	MOV.L	#(_SQ_CBWK_TOP+_SQCB217),R1	;
	MOV.W	@R1,R0				;
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				; ERR SEQ WK RAM SET

	MOV.W	#H'2176,R4			;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			; 非常停止にする

	M_BRA	_SELF_CHK_ACT_EXIT		;

_SELF_CHK_STEP03_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;


;	*** セルフ工程４ ＯＮチェック終了相手待ち ***
_SELF_CHK_STEP04:
	MOV.W	#_STEP04,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP05		; STEP=4 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP04,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP04_020		;

	MOV.W	#_STEP05,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP04_EXT		;
_SELF_CHK_STEP04_020:

	MOV.W	#_STEP05,R0			; STEP <- 5
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ セルフチェックＯＦＦチェック開始
	MOV.W	R0,@R1				;

_SELF_CHK_STEP04_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程５ セルフチェックＯＦＦチェック開始 ***
_SELF_CHK_STEP05:
	MOV.W	#_STEP05,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP06		; STEP=5 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP05,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP05_020		;

	MOV.W	#_STEP06,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP05_EXT		;
_SELF_CHK_STEP05_020:

	FAR_JSR	#_SELF_OFCHECK_INIT,R0		; セルフＯＦＦチェックイニシャル

	MOV.W	#_STEP06,R0			; STEP <- 6
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ3SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP05_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程６ ＯＦＦチェック開始相手待ち ***
_SELF_CHK_STEP06:
	MOV.W	#_STEP06,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP07		; STEP=6 NO THEN JUMP

	MOV.L	#_REAL_INP1_DATA,R1		; 
	MOV.W	@R1,R1				;
	MOV.W	#BIT3,R2			;
	AND	R2,R1				;
	TST	R1,R1				; CHK ON THEN WAIT
	BF	_SELF_CHK_STEP06_010		; OFF THEN JUMP

	FAR_JSR	#_SELF_OFCHECK_INIT,R0		; セルフOFFチェックイニシャル
	M_BRA	_SELF_CHK_STEP06_EXT		;

_SELF_CHK_STEP06_010:

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP06,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP06_020		;

	MOV.W	#_STEP07,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP06_EXT		;
_SELF_CHK_STEP06_020:

	MOV.W	#_STEP07,R0			; STEP <- 7
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ ＯＦＦチェック中
	MOV.W	R0,@R1				;

_SELF_CHK_STEP06_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程７ セルフＯＦＦチェック ***
_SELF_CHK_STEP07:
	MOV.W	#_STEP07,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP08		; STEP=7 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP07,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP07_020		;

	MOV.W	#_STEP08,R2			; 相手がすでに進んでいてもチェックする
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP07_EXT		;
_SELF_CHK_STEP07_020:

	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	@R1,R1				;
	TST	R1,R1				;
	TST_BIT_OF _SELF_CHK_STEP07_ERR		; SELF CHECK TIMER UP THEN ERR

	FAR_JSR	#_SELF_OF_CHECK,R0		; セルフＯＦＦチェック
;	---------- 2014-09-14 調査-------
	MOV.L	#_MONI_SELF_STS2,R0		;
	MOV.W	R10,@R0				;
;	---------------------------------

	MOV.W	#(BIT2+BIT1+BIT0),R0		;
	CMP/EQ	R0,R10				; チェック完了CHECK
	BF	_SELF_CHK_STEP07_EXT		; 未完了 THEN JUMP

	FAR_JSR	#_RESET_OUT,R0			; RST ON

	MOV.W	#_STEP08,R0			; STEP <- 8
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ7SET
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_STEP07_EXT		;

_SELF_CHK_STEP07_ERR:
	MOV.L	#(_SQ_CBWK_TOP+_SQCB217),R1	;
	MOV.W	@R1,R0				;
	MOV.W	#BIT6,R2			;
	OR	R2,R0				;
	MOV.W	R0,@R1				; ERR SEQ WK RAM SET

	MOV.W	#H'2176,R4			;2010-12-21
	FAR_JSR	#_EMG_STOP,R0			; 非常停止にする

	M_BRA	_SELF_CHK_STEP07_EXT		;

	MOV.W	#_STEP10,R0			; STEP <- 10
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ10SET NEXT 異常処理
	MOV.W	R0,@R1				;
	M_BRA	_SELF_CHK_ACT_EXIT		;

_SELF_CHK_STEP07_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程８ ＯＦＦチェック終了相手待ち ***
_SELF_CHK_STEP08:
	MOV.W	#_STEP08,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP09		; STEP=8 NO THEN JUMP

;	=== STPA,STPB CHECK 2003-01-26 ===
;	********** SIT3_CPUB PROGRAM **********
	.AIF	_SIT_CPU_SEL	EQ	_SIT3_CPUB
	MOV.L	#_PDDR,R1	;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT12+BIT11),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;

;	********** SIT4_CPUA PROGRAM **********
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUA
	MOV.L	#_dio_top1+_IOGA_PDR2,R1		;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
;	********** SIT4_CPUB PROGRAM **********
	.AELIF	_SIT_CPU_SEL	EQ	_SIT4_CPUB
	MOV.L	#_dio_top1+_IOGA_PDR2,R1		;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3			;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
;	********** SIT3_CPUA PROGRAM **********
	.AELSE
	MOV.L	#(_IOGA1_CTRL_DAT1+_IOGAi_PC),R1	;
	MOV.W	@R1,R0					;
	MOV.W	#(BIT3+BIT2),R3				;
	AND	R3,R0					;
	TST	R0,R0					;
	BF	_SELF_CHK_STEP08_EXT			;
	.AENDI

	FAR_JSR	#_RESET_END_OUT,R1			; RST OFF

;	==================================

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP08,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP08_020		;

	MOV.W	#_STEP09,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP08_EXT		;
_SELF_CHK_STEP08_020:

	MOV.W	#_STEP09,R0			; STEP <- 09
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ 正常終了するよ
	MOV.W	R0,@R1				;

_SELF_CHK_STEP08_EXT:

	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程９ ***
_SELF_CHK_STEP09:
	MOV.W	#_STEP09,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP10		; STEP=9 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP09,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP09_020		;

	MOV.W	#_STEP15,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP09_EXT		;
_SELF_CHK_STEP09_020:

	FAR_JSR	#_SELF_CHK_NMLEND,R0		; セルフチェック正常終了処理

	MOV.W	#_STEP15,R0			; STEP <- 15
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ15SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP09_EXT:
	M_BRA	_SELF_CHK_ACT_NML_EXIT		;

;	*** セルフ工程１０ 異常終了するよ ***
_SELF_CHK_STEP10:
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP11		; STEP=10 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP10,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP10_020		;

	MOV.W	#_STEP11,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP10_EXT		;
_SELF_CHK_STEP10_020:

	FAR_JSR	#_FRCYCL_OF,R0			; *FCYCL,RCYCL ON 無効

	MOV.W	#_STEP11,R0			; STEP <- 11
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ 異常終了処理
	MOV.W	R0,@R1				;

_SELF_CHK_STEP10_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** セルフ工程１１ ***
_SELF_CHK_STEP11:
	MOV.W	#_STEP11,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP12		; STEP=11 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP11,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP11_020		;

	MOV.W	#_STEP14,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP11_EXT		;
_SELF_CHK_STEP11_020:

	FAR_JSR	#_SELF_CHK_ERREND,R0		; セルフチェック異常終了処理

	MOV.W	#_STEP14,R0			; STEP <- 14
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ14SET
	MOV.W	R0,@R1				;

_SELF_CHK_STEP11_EXT:

	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** セルフ工程１２ ***
_SELF_CHK_STEP12:
	MOV.W	#D'12,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP13		; STEP=12 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP12,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP12_020		;

	MOV.W	#_STEP13,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP12_EXT		;
_SELF_CHK_STEP12_020:

_SELF_CHK_STEP12_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** セルフ工程１３ ***
_SELF_CHK_STEP13:
	MOV.W	#13,R2				;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP14		; STEP=13 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP13,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP13_020		;

	MOV.W	#_STEP14,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP13_EXT		;
_SELF_CHK_STEP13_020:

_SELF_CHK_STEP13_EXT:

	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** セルフ工程１４ 異常終了完了***
_SELF_CHK_STEP14:
	MOV.W	#_STEP14,R2			;
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP15		; STEP=14 NO THEN JUMP

	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP14,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP14_020		;

	MOV.W	#_STEP00,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP14_EXT		;
_SELF_CHK_STEP14_020:

	MOV.W	#_STEP00,R0			; STEP <- 0
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ15SET
	MOV.W	R0,@R1				;

;;	===== 2006-04-10(2種類のｾﾙﾌﾁｪｯｸを行うためここでは終らせない) =====
;;	MOV.W	#(BIT7+BIT6),R0			;
;;	MOV.L	#_SELF_FLG,R1			; BIT7ｾﾙﾌﾁｪｯｸ異常完了
;;	MOV.W	R0,@R1				;
;;
;;	XOR	R0,R0				;
;;	MOV.L	#_SELF_COM,R1			;//BIT0:ｾﾙﾌﾁｪｯｸ指令 CLEAR
;;	MOV.W	R0,@R1				;
;;
;	======== FIRST SELF END==========
	MOV.W	#(BIT7+BIT6),R0				;
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7ｾﾙﾌﾁｪｯｸ正常完了
	MOV.W	R0,@R1					;

	XOR	R0,R0				;
	MOV.L	#_SELF_ACT_FLG,R1		;
	MOV.W	R0,@R1				;

	FAR_JSR	#_RESET_END_OUT,R1		; RST OFF

_SELF_CHK_STEP14_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;

;	*** セルフ工程１５ 正常終了完了 ***
_SELF_CHK_STEP15:
	MOV.L	#_SELF_HAND_FLG2,R1		; 相手の状態ﾌﾗｸﾞLOAD
	MOV.W	@R1,R0				;
	MOV.W	#_STEP15,R2			;
	CMP/EQ	R2,R0				;
	BT	_SELF_CHK_STEP15_020		;

	MOV.W	#_STEP00,R2			; 相手がすでに進んでいたら自分も次に進む
	CMP/EQ	R2,R0				;
	BF	_SELF_CHK_STEP15_EXT		;
_SELF_CHK_STEP15_020:

	MOV.W	#_STEP00,R0			; STEP <- 0
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ15SET
	MOV.W	R0,@R1				;

;;	===== 2006-04-10(2種類のｾﾙﾌﾁｪｯｸを行うためここでは終らせない) =====
;;	MOV.W	#BIT7,R0			;
;;	MOV.L	#_SELF_FLG,R1			; BIT7ｾﾙﾌﾁｪｯｸ正常完了
;;	MOV.W	R0,@R1				;
;;
;;	XOR	R0,R0				;
;;	MOV.L	#_SELF_COM,R1			;//BIT0:ｾﾙﾌﾁｪｯｸ指令 CLEAR
;;	MOV.W	R0,@R1				;

;	======== FIRST SELF END==========
	MOV.W	#BIT7,R0				;
	MOV.L	#_SELF_FIRST_END_FLG,R1			; BIT7ｾﾙﾌﾁｪｯｸ正常完了
	MOV.W	R0,@R1					;

	XOR	R0,R0					;ADD 2006-04-10
	MOV.L	#_SELF_ACT_FLG,R1			;
	MOV.W	R0,@R1					;

	FAR_JSR	#_RESET_END_OUT,R1		; RST OFF

_SELF_CHK_STEP15_EXT:
	M_BRA	_SELF_CHK_ACT_EXIT		;


_SELF_CHK_ACT_NML_EXIT:
;;;;;	MOV.L	#_emg_lev_flg,R1		;//異常状態(生ﾃﾞｰﾀ)
	MOV.L	#_emg_err_flg,R1		;//異常ﾗｯﾁ
	MOV.W	@R1,R0				; セルフチェック中に非常停止ならセルフチェック異常終了
	TST	R0,R0				;
	TST_BIT_OF _SELF_CHK_NML_ACT_EX_020	;
	M_BRA	_SELF_CHK_NML_ACT_EX_040

_SELF_CHK_NML_ACT_EX_020:
	MOV.L	#_exq_err_flg,R1		;//異常ﾗｯﾁ
	MOV.W	@R1,R0				; セルフチェック中に急停止ならセルフチェック異常終了
	TST	R0,R0				;
	TST_BIT_OF _SELF_CHK_ACT_EXIT		;

_SELF_CHK_NML_ACT_EX_040:
	MOV.W	#_STEP10,R2			;
	MOV.L	#_SELF_HAND_FLG1,R1		; 自分の状態ﾌﾗｸﾞ 異常終了処理するよ
	MOV.W	R2,@R1				;

_SELF_CHK_ACT_EXIT:

	SUB_END
	M_RTS







;	************************************
;	*** セルフＯＮチェックイニシャル ***
;	************************************
_SELF_ONCHECK_INIT:
	SUB_START

	XOR	R0,R0				;
	MOV.L	#_SELF_FSTY_USE,R1		;
	MOV.W	R0,@R1				;
	MOV.L	#_SELF_RSTY_USE,R1		;
	MOV.W	R0,@R1				;

;	*** CH信号ON ***
;	*CHK,CH0,1,2
;;;;;	_MC_CH0_ON_WK1	R1,R2,R3		; VSER
;;;;;	_MC_CHK_ON_WK1	R1,R2,R3		;

	MOV.W	#(BIT7+BIT0),R11		; シーケンスON 208.7,208.0

;;;;;	_MC_CH1_OF_WK1	R1,R2,R3		;
;;;;;	_MC_CH2_OF_WK1	R1,R2,R3		;

;	================= 2012-12-05 不具合修正=====
	FAR_JSR	#_SELFCHK_SFTY_CONFCHK,R0	;

	TST	R0,R0
	TST_BIT_OF _SELF_ONCHK_INIT_010		;今までと同じ条件
	CMP/EQ	#1,R0				;有効
	BT	_SELF_ONCHK_INIT_015		;LABEL追加　2012-12-05
	M_BRA	_SELF_ONCHK_INIT_040		;-1無効

_SELF_ONCHK_INIT_010:
;	------------------2012-12-05挿入---------------

	MOV.L	#(_SEQAB_DP_TOP+_SQ200),R1	; DPRAM 2008-07-30 SAITO
	MOV.W	@R1,R0				;
	MOV.W	#(BIT13+BIT12),R2		;
	AND	R2,R0				;
	MOV.W	#BIT13,R2			;
	CMP/EQ	R0,R2				;
	BF	_SELF_ONCHK_INIT_040		; 無効 THEN JUMP

_SELF_ONCHK_INIT_015:				;LABEL追加　2012-12-05

	MOV.L	#(_SEQAB_DP_TOP+_SQ028),R1	; DPRAM 2008-07-30 SAITO
	MOV.W	@R1,R0				;
	MOV.W	#BIT0,R2			;
	TST	R2,R0				;
	TST_BIT_OF _SELF_ONCHK_INIT_020		; セルフチェック選択なし THEN JUMP
;;;;;	_MC_CH1_ON_WK1	R1,R2,R3		; FSFTY
	MOV.W	#BIT2,R2			;
	OR	R2,R11				; シーケンスON 208.2
	FAR_JSR	#_FRCYCL_ON,R0			; *FCYCL,RCYCL OF 有効
	MOV.W	#H'FFFF,R0			;
	MOV.L	#_SELF_FSTY_USE,R1		;
	MOV.W	R0,@R1				; 前安全装置チェック有効

_SELF_ONCHK_INIT_020:
	MOV.L	#(_SEQAB_DP_TOP+_SQ028),R1	; DPRAM 2008-07-30 SAITO
	MOV.W	@R1,R0				;
	MOV.W	#BIT7,R2			;
	TST	R2,R0				;
	TST_BIT_OF _SELF_ONCHK_INIT_040		; セルフチェック選択なし THEN JUMP
;;;;;	_MC_CH2_ON_WK1	R1,R2,R3		; RSFTY
	MOV.W	#BIT3,R2			;
	OR	R2,R11				; シーケンスON 208.3
	FAR_JSR	#_FRCYCL_ON,R0			; *FCYCL,RCYCL OF 有効
	MOV.W	#H'FFFF,R0			;
	MOV.L	#_SELF_RSTY_USE,R1		;
	MOV.W	R0,@R1				; 後安全装置チェック有効
_SELF_ONCHK_INIT_040:

;;;;;	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;	*** シーケンスON ***
;	*CHK,CH0,1,2
	MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
	MOV.W	R11,@R1				; SEQ WK RAM SET


	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	#_SELF_CHK_TM,R2		;
	MOV.W	R2,@R1				; SELF CHECK TIMER SET

	SUB_END
	M_RTS



;
;		2012-12-05
;	=== 安全装置入力を制動試験に使用する場合がある
;	0:安全装置入力で使用(1以外) 1:制動試験に使用する
;78 _PAR_FSWFUN_SEL		.DATA.W		1		;1以外:安全装置有効無効SW／1:制動試験モードSW
;79 _PAR_FSWSEL_MASK	.DATA.W		0		;1以外:安全装置有効固定/1:安全装置無効
;	78 ,79
;	0  , *    -->現行のSWに従う
;       1  , 0    -->やる固定
;       1  , 1    -->やらない固定
;	ANS
;	OUTPUT R0=0 今までと同じ　ＳＷ参照
;	OUTPUT R0=1 ＳＷは参照しないが有効
;	OUTPUT R0=-1 無効

_SELFCHK_SFTY_CONFCHK
	SUB_START

	MOV.L	#_PAR_FSWFUN_SEL,R1		;
	MOV.W	@R1,R0				;SWの意味が異なる?
	CMP/EQ	#1,R0				;
	BF	SELF_CYCLON_INF100		;1以外(0)

	MOV.L	#_PAR_FSWSEL_MASK,R1		;1以外:安全装置有効固定/1:安全装置無効
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	SELF_CYCLON_INF200		;1ではない(0)だ。有効

	MOV.W	#-1,R0				;
	M_BRA	SELF_CYCLON_INFEND		;


SELF_CYCLON_INF100
	XOR	R0,R0				;今までのソフト
	M_BRA	SELF_CYCLON_INFEND		;

SELF_CYCLON_INF200
	MOV.W	#1,R0				;
SELF_CYCLON_INFEND

	SUB_END
	M_RTS

;	**************************
;	*** セルフＯＮチェック ***
;	**************************
;	VSERがでること、遮光が見えること
_SELF_ON_CHECK:
	SUB_START

	XOR	R10,R10					;
;	*** VSER CHECK ***
	MOV.L	#_PB_PORT_CTL_DATA,R1			; 今のﾃﾞｰﾀ
	MOV.W	@R1,R1					;
	MOV.W	#BIT15,R2				;
	EXTU.W	R2,R2					;
	TST	R2,R1					; VSER CHK
	TST_BIT_OF _SELF_ON_CHK_EXIT			; VSERがおきない THEN EXIT
	MOV.W	#BIT0,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

;	*** 前安全装置遮光チェック ***
_SELF_ON_CHK_FSFT:
	MOV.L	#_SELF_FSTY_USE,R1			;
	MOV.W	@R1,R0					; 前安全装置チェック有りチェック
	TST	R0,R0					;
	TST_BIT_ON _SELF_ON_CHK_FSFT020			; チェック有り THEN JUMP
	MOV.W	#BIT1,R0				; チェックなしならOK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET
	M_BRA	_SELF_ON_CHK_RSFT			;

_SELF_ON_CHK_FSFT020:
	FAR_JSR	#_SLF_FSTY_CHK,R0			; 遮光チェック
	MOV.W	#H'00FF,R1				;
	CMP/EQ	R1,R0					;
	BF	_SELF_ON_CHK_EXIT			; 遮光じゃない THEN EXIT
	MOV.W	#BIT1,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

_SELF_ON_CHK_RSFT:
	MOV.L	#_SELF_RSTY_USE,R1			;
	MOV.W	@R1,R0					; 前安全装置チェック有りチェック
	TST	R0,R0					;
	TST_BIT_ON _SELF_ON_CHK_RSFT020			; チェック有り THEN JUMP
	MOV.W	#BIT2,R0				; チェックなしならOK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET
	M_BRA	_SELF_ON_CHK_EXIT			;

_SELF_ON_CHK_RSFT020:
	FAR_JSR	#_SLF_RSTY_CHK,R0			; 遮光チェック
	MOV.W	#H'00FF,R1				;
	CMP/EQ	R1,R0					;
	BF	_SELF_ON_CHK_EXIT			; 遮光じゃない THEN EXIT
	MOV.W	#BIT2,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

_SELF_ON_CHK_EXIT:			;
	SUB_END
	M_RTS


;	**************************************
;	*** セルフＯＦＦチェックイニシャル ***
;	**************************************
_SELF_OFCHECK_INIT:
	SUB_START

;	*** CH信号OFF ***
;	*CHK,CH0,1,2
;;;;;	_MC_CHK_OF_WK1	R1,R2,R3		; 2003-01-23
;;;;;	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
;;;;;	_MC_CH1_OF_WK1	R1,R2,R3		; 2003-01-23
;;;;;	_MC_CH2_OF_WK1	R1,R2,R3		; 2003-01-23
;;;;;	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

	FAR_JSR	#_FRCYCL_OF,R0			; *FCYCL,RCYCL ON 無効


	MOV.L	#_SELF_CHK_TIMER,R1		;
	MOV.W	#_SELF_CHK_TM,R2		;
	MOV.W	R2,@R1				; SELF CHECK TIMER SET

	SUB_END
	M_RTS


;	****************************
;	*** セルフＯＦＦチェック ***
;	****************************
_SELF_OF_CHECK:
	SUB_START

	XOR	R10,R10					;
;	*** VSER CHECK ***
	MOV.L	#_PB_PORT_CTL_DATA,R1			;
	MOV.W	@R1,R1					;
	MOV.W	#BIT15,R2				;
	EXTU.W	R2,R2					;
	TST	R2,R1					; VSER CHK
	TST_BIT_ON _SELF_OF_CHK_EXIT			; VSERがおきない THEN EXIT
	MOV.W	#BIT0,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

;	*** 前安全装置遮光チェック ***
_SELF_OF_CHK_FSFT:
	MOV.L	#_SELF_FSTY_USE,R1			;
	MOV.W	@R1,R0					; 前安全装置チェック有りチェック
	TST	R0,R0					;
	TST_BIT_ON _SELF_OF_CHK_FSFT020			; チェック有り THEN JUMP
	MOV.W	#BIT1,R0				; チェックなしならOK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET
	M_BRA	_SELF_OF_CHK_RSFT			;

_SELF_OF_CHK_FSFT020:
	FAR_JSR	#_SLF_FSTY_CHK,R0			; 遮光チェック
;;;;;	MOV.W	#H'000F,R1				;
	MOV.W	#H'0000,R1				; 2003-01-23 SAITO
	CMP/EQ	R1,R0					;
	BF	_SELF_OF_CHK_EXIT			; 遮光じゃない THEN EXIT
	MOV.W	#BIT1,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

_SELF_OF_CHK_RSFT:
	MOV.L	#_SELF_RSTY_USE,R1			;
	MOV.W	@R1,R0					; 前安全装置チェック有りチェック
	TST	R0,R0					;
	TST_BIT_ON _SELF_OF_CHK_RSFT020			; チェック有り THEN JUMP
	MOV.W	#BIT2,R0				; チェックなしならOK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET
	M_BRA	_SELF_OF_CHK_EXIT			;

_SELF_OF_CHK_RSFT020:
	FAR_JSR	#_SLF_RSTY_CHK,R0			; 遮光チェック
;;;;;	MOV.W	#H'000F,R1				;
	MOV.W	#H'0000,R1				; 2003-01-23 SAITO
	CMP/EQ	R1,R0					;
	BF	_SELF_OF_CHK_EXIT			; 遮光じゃない THEN EXIT
	MOV.W	#BIT2,R0				; OK CODE SET
	OR	R0,R10					; チェックなしならOK CODE SET

_SELF_OF_CHK_EXIT:

	SUB_END
	M_RTS


;	**********************************
;	*** セルフチェック正常終了処理 ***
;	**********************************
_SELF_CHK_NMLEND:
	SUB_START

;;;;;	_MC_CHK_OF_WK1	R1,R2,R3		; 
;;;;;	_MC_CH0_OF_WK1	R1,R2,R3		; 2003-01-23
;;;;;	_MC_CH1_OF_WK1	R1,R2,R3		;
;;;;;	_MC_CH2_OF_WK1	R1,R2,R3		;
;;;;;	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;;;;2006-04-26	XOR	R5,R5				;
;;;;	MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
;;;;	MOV.W	R5,@R1				; SEQ WK RAM CLEAR

	SUB_END
	M_RTS



;	**********************************
;	*** セルフチェック異常終了処理 ***
;	**********************************
_SELF_CHK_ERREND:
	SUB_START

;;;;;	_MC_CHK_OF_WK1	R1,R2,R3		; 
;;;;;	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
;;;;;	_MC_CH1_OF_WK1	R1,R2,R3		;
;;;;;	_MC_CH2_OF_WK1	R1,R2,R3		;

;;;;;	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

	XOR	R5,R5				;
	MOV.L	#(_SQ_CBWK_TOP+_SQCB208),R1	;
	MOV.W	R5,@R1				; SEQ WK RAM CLEAR

	SUB_END
	M_RTS






;	***********************************
;	***	前安全装置入力		***
;	***********************************
;	R0=00H 	FACT=FDEV=通光
;	R0=0FH	FACT:遮光 FEDV=通光
;	R0=F0H  FACT:通行 FDEV=遮光 有り得ない
;	R0=FFH	FACT=FDEV=遮光
_SLF_FSTY_CHK:
	SUB_START

	XOR	R0,R0			;

	MOV.L	#_FACT_IN_DATA,R1			;
	MOV.W	@R1,R2					; FACT生ﾃﾞｰﾀ
	MOV.L	#_FDEV_IN_DATA,R1			;
	MOV.W	@R1,R3					; FDEV生ﾃﾞｰﾀ
	SHLL2	R3					;
	SHLL2	R3					;
	OR	R3,R2					;
	MOV.W	#(BIT4+BIT0),R4				;
	AND	R4,R2					;
	MOV.W	#0,R4					;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK020			;

	MOV.W	#H'00FF,R0				; FACT=FDEV=L THEN 遮光
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK020:
	MOV.W	#BIT0,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK040			;

	MOV.W	#H'00F0,R0				; FACT=通光、FDEV=遮光 ありえない組み合わせ
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK040:
	MOV.W	#BIT4,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK060			;

	MOV.W	#H'000F,R0				; FACT=遮光、FDEV=通光
	M_BRA	_SLF_FSTY_CHK_EXIT			;

_SLF_FSTY_CHK060:
	MOV.W	#(BIT4+BIT0),R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_FSTY_CHK080			;

	M_BRA	_SLF_FSTY_CHK_EXIT			; FACT=FDEV=通光

_SLF_FSTY_CHK080:
_SLF_FSTY_CHK_EXIT:
	SUB_END
	M_RTS

;	***********************************
;	***	前安全装置入力		***
;	***********************************
;	R0=00H 	FACT=FDEV=通光
;	R0=0FH	FACT:遮光 FEDV=通光
;	R0=F0H  FACT:通行 FDEV=遮光 有り得ない
;	R0=FFH	FACT=FDEV=遮光
_SLF_RSTY_CHK:
	SUB_START

	XOR	R0,R0			;

	MOV.L	#_RACT_IN_DATA,R1			;
	MOV.W	@R1,R2					; RACT生ﾃﾞｰﾀ
	MOV.L	#_RDEV_IN_DATA,R1			;
	MOV.W	@R1,R3					; RDEV生ﾃﾞｰﾀ
	SHLL2	R3					;
	SHLL2	R3					;
	OR	R3,R2					;
	MOV.W	#(BIT4+BIT0),R4				;
	AND	R4,R2					;
	MOV.W	#0,R4					;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK020			;

	MOV.W	#H'00FF,R0				; RACT=RDEV=L THEN 遮光
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK020:
	MOV.W	#BIT0,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK040			;

	MOV.W	#H'00F0,R0				; RACT=通光、RDEV=遮光 ありえない組み合わせ
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK040:
	MOV.W	#BIT4,R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK060			;

	MOV.W	#H'000F,R0				; RACT=遮光、RDEV=通光
	M_BRA	_SLF_RSTY_CHK_EXIT			;

_SLF_RSTY_CHK060:
	MOV.W	#(BIT4+BIT0),R4				;
	CMP/EQ	R4,R2					;
	BF	_SLF_RSTY_CHK080			;

	M_BRA	_SLF_RSTY_CHK_EXIT			; RACT=RDEV=通光

_SLF_RSTY_CHK080:
_SLF_RSTY_CHK_EXIT:
	SUB_END
	M_RTS


;	********************************************* 2003-01-23 SH2は処理なし
;	*** セルフチェック信号 全ＯＦＦ CHK,CH0~2 ***
;	*** セルフチェックを非常停止により中断時  ***
;	*********************************************
_STP_SELF_OUT_OFF:
	SUB_START

;	===== 2003-01-20 SAITO =====

;;;;;	_MC_CHK_OF_WK1	R1,R2,R3		; 
;;;;;	_MC_CH0_OF_WK1	R1,R2,R3		; VSER
;;;;;	_MC_CH1_OF_WK1	R1,R2,R3		;
;;;;;	_MC_CH2_OF_WK1	R1,R2,R3		;

;;;;;	_MC_GA2PF_OUT1	R1,R2,R3		; OUT

;	============================

	SUB_END
	M_RTS

;;;;;;	.AENDI


