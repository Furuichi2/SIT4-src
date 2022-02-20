;	*******************************************************************
;	***								***
;	***								***
;	***		CPUD<=>CPUB					***
;	***		cpub専用					***
;	***								***
;	***		[ﾜｰﾄﾞｱｸｾｽのみ]					***
;	*******************************************************************
;	2000~3fff 2000hex=8k
	.EXPORT	_CPUD_COP1_DP_TOP
	.EXPORT	_CPUD_ET1_DP_TOP

	.org	h'2000
_CPUD_COP1_DP_TOP:			;2KBYTE

	.org	h'2800
_CPUD_ET1_DP_TOP:			;1KBYTE+(予備1Kﾊﾞｲﾄ ﾊﾞﾝｸの場合もう1K使用可能)
	.INCLUDE	"dp_et1.inc"	;2013-12-12 実体ではない [実体はCPUB-OPRAM]

;	----------------------------------
	.org	h'3000
_KEY_USE_SEL	.SRES	2	;0:ﾊﾟﾈﾙ釦 1:
_KEY_DT_CPUB	.sres	2*8	;// cpub=>cpud key
_DSET_SW_CPUB	.sres	2	;// cpub=>cpud sw

_PANEL_LED_DAT	.SRES	2	;ﾊﾟﾈﾙLED SQ->CPUB->
_PANEL_FRQ_DAT	.SRES	2	;調節    SQ->CPUB->1~249,255

_OPTION_COP_ARI	.SRES	2	;005A CPUB-->CPUD
_OPTION_ET1_ARI	.SRES	2	;005A CPUB-->CPUD

_COP_SET_CLRF	.SRES	2	;CPUD=>CPUB 2014-01-05

;	-------------2014-09-28--------------------
_ET2_WORD_SITM_REQ	.SRES	2	;CPUD/B間はﾜｰﾄﾞで行う ET2_SITM_REQ
_ET2_WORD_SITM_ACK	.SRES	2	;CPUD/B間はﾜｰﾄﾞで行う ET2_SITM_ACK
