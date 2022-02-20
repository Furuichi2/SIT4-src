;以下、本当は小林ツールで作るソースレベルの制御情報テーブル

	.include	"ssc_fram.ext"				;//参照変数定義
	.IMPORT		_PV0_KAGEN_POSITIONER
	.IMPORT		_PV0_NOWPOSI_SLIDE
	.IMPORT		_DEBUG_CNT

	.DATA.W		3,	2,	12,	3
	.DATA.B		h'5A,	H'0

	.ALIGN 4
_ALLTBL_CSTBL:				; カーソル制御情報テーブル
;001
	.DATA.W		0,	0,	0,	1,	0,	H'FFFF
	.DATA.W		0,	0,	2,	3,	4,	0,	8,	0,	2,	0
;002
	.DATA.W		0,	50,	1,	1,	0,	H'FFFF
	.DATA.W		0,	0,	3,	3,	4,	0,	10,	0,	4,	0
;003
	.DATA.W		0,	51,	1,	1,	0,	H'ffff
	.DATA.W		0,	0,	0,	3,	4,	0,	11,	0,	5,	0

	.DATA.B		h'5A,	H'0

	.ALIGN 4
_ALLTBL_SVTBL:				; 設定値制御情報テーブル
;001
	.DATA.W		0,	0
	.DATA.L		_SV_PUR1SV_B4
	.DATA.W		0,	50,	H'0004,	4,	0,	2,	1,	0,	2,	0
;002
	.DATA.W		0,	0
	.DATA.L		_SV_PUR2SV_B41
	.DATA.W		0,	51,	H'0004,	4,	0,	3,	1,	0,	2,	0

	.DATA.B		h'5A,	H'0

	.ALIGN 4
_ALLTBL_PVTBL:				; 実測値制御情報テーブル
;001
	.DATA.W		0,	0
	.DATA.L		_PV_TOTLC1_B3
	.DATA.W		7,	0,	H'0084,	4,	0,	0,	0,	0
;002
	.DATA.W		0,	0
	.DATA.L		_PV_LOTCT1_B1
	.DATA.W		7,	50,	H'0084,	4,	0,	0,	0,	0
;003
	.DATA.W		0,	0
	.DATA.L		_PV_LOTCT2_B1
	.DATA.W		7,	51,	H'0084,	4,	0,	0,	0,	0
;004
	.DATA.W		0,	0
	.DATA.L		_PV0_KAGEN_POSITIONER
	.DATA.W		7,	52,	H'0004,	4,	2,	0,	0,	0
;005
	.DATA.W		0,	0
	.DATA.L		_PV_KAJYU1_A24
	.DATA.W		4,	53,	H'0004,	2,	0,	0,	0,	0
;006
	.DATA.W		0,	0
	.DATA.L		_PV_KAJYU2_A24
	.DATA.W		4,	53,	H'0004,	2,	0,	0,	0,	0
;007
	.DATA.W		0,	0
	.DATA.L		_PV_KAJYU3_A24
	.DATA.W		4,	53,	H'0004,	2,	0,	0,	0,	0
;008
	.DATA.W		0,	0
	.DATA.L		_PVP_CYCLE_SPM1
	.DATA.W		13,	0,	H'0084,	2,	0,	0,	0,	0
;009
	.DATA.W		0,	0
	.DATA.L		_PV0_NOWPOSI_SLIDE
	.DATA.W		14,	19,	H'0084,	4,	2,	0,	0,	0
;010
	.DATA.W		0,	0
	.DATA.L		_PVP_STOP_TIM
	.DATA.W		0,	68,	0,	2,	0,	0,	0,	0
;011
	.DATA.W		H'0,	H'0
	.DATA.L		_DEBUG_CNT
	.DATA.W		D'0,	D'0,	H'0000,	D'4,	D'0,	D'0,	D'0,	D'0
;012
	.DATA.W		H'0,	H'0
	.DATA.L		_DEBUG_CNT
	.DATA.W		D'0,	D'0,	H'0004,	D'4,	D'0,	D'0,	D'0,	D'0

	.DATA.B		h'5A,	H'0

	.ALIGN 4
_ALLTBL_SWTBL:				; ＳＷ－ＬＡＭＰ制御情報テーブル
;001
	.DATA.W		0,	0
	.DATA.L		_SEQ_032_SV
	.DATA.W		0,	0,	H'0001,	H'0001,	1,	1,	1,	0
	.DATA.L		0
	.DATA.W		H'0008,	D'0
;002
	.DATA.W		0,	0
	.DATA.L		_SEQ_032_SV
	.DATA.W		0,	50,	H'0001,	H'0004,	2,	1,	1,	0
	.DATA.L		0
	.DATA.W		H'0008,	D'0
;003
	.DATA.W		0,	0
	.DATA.L		_SEQ_032_SV
	.DATA.W		0,	51,	H'0001,	H'0008,	3,	1,	1,	0
	.DATA.L		0
	.DATA.W		H'0008,	D'0

	.DATA.B		h'5A,	H'0





