;	*******************************************
;	***					***
;	***	�N�����N�p�x->�����N�p�x	***
;	***	�ݒ�p				***
;	***					***
;	*******************************************
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035S	;
	.DATA.W		1
	.INCLUDE	"cdig_35s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035H	;
	.DATA.W		2
	.INCLUDE	"cdig_35h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045S	;
	.DATA.W		3
	.INCLUDE	"cdig_45s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045H	;
	.DATA.W		4
	.INCLUDE	"cdig_45h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060S	;
	.DATA.W		5
	.INCLUDE	"cdig_60s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060H	;
	.DATA.W		6
	.INCLUDE	"cdig_60h.txt"		;�p�x->RNA
	.AENDI

;	===================================================
;	===						===
;	===================================================
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080S	;
	.DATA.W		7
	.INCLUDE	"cdig_80s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080H	;
	.DATA.W		8
	.INCLUDE	"cdig_80h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110S	;
	.DATA.W		17
	.INCLUDE	"cdig_A1s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110H	;
	.DATA.W		18
	.INCLUDE	"cdig_A1h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150S	;
	.DATA.W		19
	.INCLUDE	"cdig_A5s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150H	;
	.DATA.W		20
	.INCLUDE	"cdig_A5h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200S	;
	.DATA.W		21
	.INCLUDE	"cdig_B0s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200H	;
	.DATA.W		22
	.INCLUDE	"cdig_B0h.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250S	;
	.DATA.W		23
	.INCLUDE	"cdig_B5s.txt"		;�p�x->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250H	;
	.DATA.W		24
	.INCLUDE	"cdig_B5h.txt"		;�p�x->RNA
	.AENDI

;	===== 2006-06-10=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H630S	;K(27)
	.DATA.W		_MCN_TBL_H630S			;
	.INCLUDE	"cdig_63s.txt"			;�p�x
	.AENDI


;	===== 2007-06-19=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H110L	;M(29)
	.DATA.W		_MCN_TBL_H110L			;
	.INCLUDE	"cdig_A1l.txt"			;�p�x
	.AENDI


;	===== 2004-05-26(������ڽ)========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H470M	;O(31)
	.DATA.W		_MCN_TBL_H470M			;
	.INCLUDE	"cdig_D4m.txt"			;�p�x
	.AENDI

;	===== 2005-06-10()========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H630L	;P(32)
	.DATA.W		_MCN_TBL_H630L			;
	.INCLUDE	"cdig_63l.txt"			;�p�x
	.AENDI

;	===== 2005-07-14========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H920C	;Q(33)
	.DATA.W		_MCN_TBL_H920C			;
	.INCLUDE	"cdig_92c.txt"			;�p�x
	.AENDI

;	===== 2007-08-21========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W31	;T(36)
	.DATA.W		_MCN_TBL_H2W31			;
	.INCLUDE	"cdig_w31.txt"			;
	.AENDI

;	===== 2007-04-26========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W20	;U(37)
	.DATA.W		_MCN_TBL_H2W20			;
	.INCLUDE	"cdig_w20.txt"			;
	.AENDI

;	===== 2007-02-18========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W30	;V(38)
	.DATA.W		_MCN_TBL_H2W30			;
	.INCLUDE	"cdig_w30.txt"			;
	.AENDI

;	===== 2006-10-17========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2WCS	;X(40)
	.DATA.W		_MCN_TBL_H2WCS			;
	.INCLUDE	"cdig_cos.txt"			;
	.AENDI


;	===== 2004-05-26(��а���u)========
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H001S	;(39)
	.DATA.W		_MCN_TBL_H001S			;
	.INCLUDE	"cdig_01s.txt"			;�p�x
	.AENDI

