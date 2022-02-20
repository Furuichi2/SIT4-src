;	***********************************
;	***				***
;	***	角度->リニア		***
;	***	データテーブル		***
;	***				***
;	***********************************
;	<IF分で当面切替>

;	===========  Sｼﾘｰｽﾞ ====
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035S	;
	.DATA.W		1
	.INCLUDE	"dg35s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H035H	;
	.DATA.W		2
	.INCLUDE	"dg35h_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045S	;
	.DATA.W		3
	.INCLUDE	"dg45s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H045H	;
	.DATA.W		4
	.INCLUDE	"dg45h_mm.txt"		;角度->RNA
	.AENDI


	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060S	;
	.DATA.W		5
	.INCLUDE	"dg60s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H060H	;
	.DATA.W		6
	.INCLUDE	"dg60h_mm.txt"		;角度->RNA
	.AENDI

;	===================================================
;	===						===
;	===================================================
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080S	;
	.DATA.W		7
	.INCLUDE	"dg80s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H080H	;
	.DATA.W		8
	.INCLUDE	"dg80h_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110S	;
	.DATA.W		17
	.INCLUDE	"dgA1s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H110H	;
	.DATA.W		18
	.INCLUDE	"dgA1h_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150S	;
	.DATA.W		19
	.INCLUDE	"dgA5s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H150H	;
	.DATA.W		20
	.INCLUDE	"dgA5h_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200S	;
	.DATA.W		21
	.INCLUDE	"dgB0s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H200H	;
	.DATA.W		22
	.INCLUDE	"dgB0h_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250S	;
	.DATA.W		23
	.INCLUDE	"dgB5s_mm.txt"		;角度->RNA
	.AENDI

	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H250H	;
	.DATA.W		24
	.INCLUDE	"dgB5h_mm.txt"		;角度->RNA
	.AENDI

;	===== 2006-06-10=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H630S	;K(27)
	.DATA.W		_MCN_TBL_H630S			;
	.INCLUDE	"dg63s_mm.txt"			;角度->RNA
	.AENDI

;	===== 2007-06-19=====
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H110L	;M(29)
	.DATA.W		_MCN_TBL_H110L			;
	.INCLUDE	"dgA1l_mm.txt"			;角度->RNA
	.AENDI

;	===== 2004-05-26(ｻｰﾎﾞﾌﾟﾚｽ)========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H470M	;O(31)
	.DATA.W		_MCN_TBL_H470M			;
	.INCLUDE	"dgD4m_mm.txt"			;角度->RNA
	.AENDI

;	===== 2005-06-10()========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H630L	;P(32)
	.DATA.W		_MCN_TBL_H630L			;
	.INCLUDE	"dg63l_mm.txt"			;角度->RNA
	.AENDI


;	===== 2005-07-14========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H920C	;Q(33)
	.DATA.W		_MCN_TBL_H920C			;
	.INCLUDE	"dg92c_mm.txt"			;角度->RNA
	.AENDI

;	===== 2007-08-21========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W31	;T(36)
	.DATA.W		_MCN_TBL_H2W31			;
	.INCLUDE	"dgw31_mm.txt"			;
	.AENDI

;	===== 2007-04-26========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W20	;U(37)
	.DATA.W		_MCN_TBL_H2W20			;
	.INCLUDE	"dgw20_mm.txt"			;
	.AENDI

;	===== 2007-02-18========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2W30	;V(38)
	.DATA.W		_MCN_TBL_H2W30			;
	.INCLUDE	"dgw30_mm.txt"			;
	.AENDI


;	===== 2006-10-17========
	.AIF	_MACINE_TBL_SEL	EQ	_MCN_TBL_H2WCS	;X(40)
	.DATA.W		_MCN_TBL_H2WCS			;
	.INCLUDE	"dgcosmm.txt"			;
	.AENDI


;	===== 2004-05-26(ﾀﾞﾐｰ装置)========
	.AIF	_MACINE_TBL_SEL	EQ _MCN_TBL_H001S	;(39)
	.DATA.W		_MCN_TBL_H001S			;
	.INCLUDE	"dg01s_mm.txt"		;角度->RNA
	.AENDI
