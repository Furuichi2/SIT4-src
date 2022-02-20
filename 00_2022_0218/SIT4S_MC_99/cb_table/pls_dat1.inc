;	***********************************
;	***				***
;	***	リニア->角度		***
;	***	下降テーブル		***
;	***				***
;	***********************************

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035S	;
	.DATA.W		1
	.INCLUDE	"ps35dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035H	;
	.DATA.W		2
	.INCLUDE	"ph35dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045S	;
	.DATA.W		3
	.INCLUDE	"ps45dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045H	;
	.DATA.W		4
	.INCLUDE	"ph45dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060S	;
	.DATA.W		5
	.INCLUDE	"ps60dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060H	;
	.DATA.W		6
	.INCLUDE	"ph60dat1.txt"		;
	.AENDI

;	===================================================
;	===						===
;	===================================================
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080S	;
	.DATA.W		7
	.INCLUDE	"ps80dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080H	;
	.DATA.W		8
	.INCLUDE	"ph80dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110S	;
	.DATA.W		17
	.INCLUDE	"psA1dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110H	;
	.DATA.W		18
	.INCLUDE	"phA1dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150S	;
	.DATA.W		19
	.INCLUDE	"psA5dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150H	;
	.DATA.W		20
	.INCLUDE	"phA5dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200S	;
	.DATA.W		21
	.INCLUDE	"psB0dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200H	;
	.DATA.W		22
	.INCLUDE	"phB0dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250S	;
	.DATA.W		23
	.INCLUDE	"psB5dat1.txt"		;
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250H	;
	.DATA.W		24
	.INCLUDE	"phB5dat1.txt"		;
	.AENDI

;	===== 2006-06-10=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H630S	;K(27)
	.DATA.W		_MCN_TBL_H630S			;
	.INCLUDE	"ps63dat1.txt"			;
	.AENDI

;	===== 2007-06-19=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H110L	;M(29)
	.DATA.W		_MCN_TBL_H110L			;
	.INCLUDE	"plA1dat1.txt"			;
	.AENDI

;	===== 2004-05-26(ｻｰﾎﾞﾌﾟﾚｽ)========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H470M	;O(31)
	.DATA.W		_MCN_TBL_H470M			;
	.INCLUDE	"pmD4dat1.txt"			;
	.AENDI

;	===== 2005-06-10()========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H630L	;P(32)
	.DATA.W		_MCN_TBL_H630L			;
	.INCLUDE	"pl63dat1.txt"			;
	.AENDI

;	===== 2005-07-14========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H920C	;Q(33)
	.DATA.W		_MCN_TBL_H920C			;
	.INCLUDE	"pc92dat1.txt"			;
	.AENDI

;	===== 2007-08-21========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W31	;T(36)
	.DATA.W		_MCN_TBL_H2W31			;
	.INCLUDE	"pw31dat1.txt"			;
	.AENDI

;	===== 2007-04-26========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W20	;U(37)
	.DATA.W		_MCN_TBL_H2W20			;
	.INCLUDE	"pw20dat1.txt"			;
	.AENDI

;	===== 2007-02-18========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W30	;V(38)
	.DATA.W		_MCN_TBL_H2W30			;
	.INCLUDE	"pw30dat1.txt"			;
	.AENDI

;	===== 2006-10-17========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2WCS	;X(40)
	.DATA.W		_MCN_TBL_H2WCS			;
	.INCLUDE	"cosdat1.txt"			;
	.AENDI


;	===== 2004-05-26(ﾀﾞﾐｰ装置)========
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H001S	;(39)
	.DATA.W		_MCN_TBL_H001S			;
	.INCLUDE	"ps01dat1.txt"			;
	.AENDI
