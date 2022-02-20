;	*******************************************
;	***					***
;	***	ƒŠƒ“ƒNŠp“x->ƒNƒ‰ƒ“ƒNŠp“x	***
;	***	‘½•ª•\Ž¦—p‚Ì‚Ý			***
;	***					***
;	*******************************************
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035S	;
	.DATA.W		1
	.INCLUDE	"ldig_35s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035H	;
	.DATA.W		2
	.INCLUDE	"ldig_35h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045S	;
	.DATA.W		3
	.INCLUDE	"ldig_45s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045H	;
	.DATA.W		4
	.INCLUDE	"ldig_45h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060S	;
	.DATA.W		5
	.INCLUDE	"ldig_60s.txt"		;Šp“x->RNA
	.AENDI


	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060H	;
	.DATA.W		6
	.INCLUDE	"ldig_60h.txt"		;Šp“x->RNA
	.AENDI
	
;	===================================================
;	===						===
;	===================================================
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080S	;
	.DATA.W		7
	.INCLUDE	"ldig_80s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080H	;
	.DATA.W		8
	.INCLUDE	"ldig_80h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110S	;
	.DATA.W		17
	.INCLUDE	"ldig_A1s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110H	;
	.DATA.W		18
	.INCLUDE	"ldig_A1h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150S	;
	.DATA.W		19
	.INCLUDE	"ldig_A5s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150H	;
	.DATA.W		20
	.INCLUDE	"ldig_A5h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200S	;
	.DATA.W		21
	.INCLUDE	"ldig_B0s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200H	;
	.DATA.W		22
	.INCLUDE	"ldig_B0h.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250S	;
	.DATA.W		23
	.INCLUDE	"ldig_B5s.txt"		;Šp“x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250H	;
	.DATA.W		24
	.INCLUDE	"ldig_B5h.txt"		;Šp“x->RNA
	.AENDI

;	===== 2006-06-10=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H630S	;K(27)
	.DATA.W		_MCN_TBL_H630S			;
	.INCLUDE	"ldig_63s.txt"			;Šp“x
	.AENDI

;	===== 2007-06-19=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H110L	;M(29)
	.DATA.W		_MCN_TBL_H110L			;
	.INCLUDE	"ldig_A1l.txt"			;Šp“x
	.AENDI

;	===== 2004-05-26(»°ÎÞÌßÚ½)========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H470M	;O(31)
	.DATA.W		_MCN_TBL_H470M			;
	.INCLUDE	"ldig_D4m.txt"			;Šp“x
	.AENDI

;	===== 2005-06-10()========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H630L	;P(32)
	.DATA.W		_MCN_TBL_H630L			;
	.INCLUDE	"ldig_63l.txt"			;Šp“x
	.AENDI


;	===== 2005-07-14========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H920C	;Q(33)
	.DATA.W		_MCN_TBL_H920C			;
	.INCLUDE	"ldig_92c.txt"			;Šp“x
	.AENDI

;	===== 2007-08-21========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W31	;T(36)
	.DATA.W		_MCN_TBL_H2W31			;
	.INCLUDE	"ldig_w31.txt"			;
	.AENDI

;	===== 2007-04-26========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W20	;U(37)
	.DATA.W		_MCN_TBL_H2W20			;
	.INCLUDE	"ldig_w20.txt"			;
	.AENDI

;	===== 2007-02-18========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W30	;V(38)
	.DATA.W		_MCN_TBL_H2W30			;
	.INCLUDE	"ldig_w30.txt"			;
	.AENDI

;	===== 2006-10-17========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2WCS	;X(40)
	.DATA.W		_MCN_TBL_H2WCS			;
	.INCLUDE	"ldig_cos.txt"			;
	.AENDI


;	===== 2004-05-26(ÀÞÐ°‘•’u)========
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H001S	;(39)
	.DATA.W		_MCN_TBL_H001S			;
	.INCLUDE	"ldig_01s.txt"			;Šp“x
	.AENDI
