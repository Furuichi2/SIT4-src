;	*******************************************************************
;	***								***
;	***								***
;	***		CPUD<=>CPUA��p					***
;	***								***
;	***								***
;	***								***
;	*******************************************************************

;	***********************************************************
;	***							***
;	***	���ݽ ���o��MEMORY MAP�̈� SH2<-->SH4(SEQ)	***
;	***							***
;	***********************************************************
	.org	h'2000
_SEQ_DP_TOP:					;��Ԃ�
		.INCLUDE	"ssc_dpram_seq.inc"		; real data define 1000word


;	*******************************************
;	***					***
;	***	�\��	SHIMA(HMI:V01v)		***
;	***	�T���v�����O			***
;	*******************************************
;;;;;;;;;[[[��2013-12-02]]]		.ORG	H'2400
	.ALIGN	4				;
_HMI2CB_LDCMD_FLG		.SRES	2	; HMI->C/B ۰�޺���޾����׸�
_HMI2CB_LDCMD_DAT		.SRES	540	; HMI->C/B ۰�޺����
_CB2HMI_LDCMD_FLG		.SRES	2	; C/B->HMI ۰�޺���޾����׸�
_CB2HMI_LDCMD_DAT		.SRES	540	; C/B->HMI ۰�޺����



;	*******************************************
;	***					***
;	***		��ʕ`��������ޯ�	***
;	***					***
;	*******************************************
;;;;;;;;;[[[��2013-12-02]]]		.ORG	H'2840
	.ALIGN	4				;
_CPA_SMPDAT2		.SRES	24*4	;24byte*4block=96(2010-09-21 USED�@24byte)
_CPA_SHTDAT2		.SRES	20*1	;20byte*1block=20(2010-09-21 USED�@16byte)
_HND_SMPCNT_FLG2	.SRES	2	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
_HND_SHTCNT_FLG2	.SRES	2	;0,1	   (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)


;	===========================================
;	===		ET1 TOREND DATA		===
;	===========================================
	.ALIGN	4					;
_CPUA_SND_INI_ET1	.SRES	4			;INITAL CODE REQ
_CPUA_RCV_INI_ET1	.SRES	4			;INITAL CODE ACK
;	--------------------------------------------------
_CPUA_SND_REQ_ET1	.SRES	4			;H'12345678(req)
_CPUA_RCV_ACK_ET1	.SRES	4			;H'87654321(ack)
;	---------------------------------------------------
_CPUA_SND_REQ_ADR	.SRES	4			;TOPADRESS (192K+32K 256Kbyte)
_CPUA_SND_REQ_CNT	.SRES	4			;1~128��
	.ALIGN	4					;
_CPUA_SND_DAT		.SRES	_ET1_CPUAB_BUF_MAX	;(256byte MAX)
_CPUA_SND_END		.SRES	2			;341C

;	===========================================
;	===	ET1==>CPUA(�Ǐo 32BYTE)	�ð��RD	===
;	===	2008-10-20			===
;	===========================================
;--0F4E
_CPUA_RD_REQ		.SRES	2			;CPUA-->ET1 READ REQ
_CPUA_RD_ACK		.SRES	2			;ET1-->CPUA data SET ACK
_CPUA_RD_CNT		.SRES	2			;�Ǐo��
	.ALIGN	4					;
_CPUA_RD_ADR		.SRES	4			;�Ǐo���ڽ
_CPUA_RD_BUF		.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
;	===========================================
;	===	CPUA==>����2(32byte)	�ð��WR	===
;	===	2008-10-20			===
;	===========================================
	.ALIGN	4					;
_CPUA_WR2_ADR	.SRES	4			;STS WR LINE
_CPUA_WR2_BUF	.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
_CPUA_WR2_REQ	.SRES	2			;
_CPUA_WR2_ACK	.SRES	2			;
_CPUA_WR2_CNT	.SRES	2			;cpub(FA0,FA1)et1(3A0,3A1)

;	===========================================
;	===		ET1 TOREND DATA2	===
;	===	2008-10-20 �Ǐo,����2�ǉ�	===
;	===					===
;	===========================================



;	*******************************************
;	***					***
;	***	CPUD=>CPUA			***
;	***	�ů�߼�����̧			***
;	***	�ů��:KIND=2[]			***
;	***					***
;	*******************************************
;	[480*640*2byte => 614,400�޲�]��[480*640*1byte=307,200�޲�]�ɂ���
	.ALIGN	4			;
_CPUDTOA_DAT1_REQADR	.SRES	4	;OFS WORD
_CPUDTOA_DAT1_REQKND	.SRES	2	;���[BIT15=1:END <-//-> BIT7~BIT0 KIND]
_CPUDTOA_DAT1_REQCNT	.SRES	2	;WORD��
_CPUDTOA_DAT1_REQCOD	.SRES	2	;WR
_CPUDTOA_DAT1_ACKCOD	.SRES	2	;ACK
	.ALIGN	4			;
_CPUDTOA_DAT1_DATTOP	.SRES	2*512	;1024byte



;	*******************************************
;	***					***
;	***	CPUA=>CPUD			***
;	***	KOMTRAX �M���p			***
;	***	2014-09-29			***
;	*******************************************
_CPUATOD_1CYCL_SIG	.SRES	2	;BIT0=0/BIT0=1 ���CPUA CLR CPUD

;	*******************************************
;	***					***
;	***	2014-10-12			***
;	***					***
;	***	CPUD=>A	AD2�`AD4		***
;	***					***
;	*******************************************
_CPUD_PV_AD2		.SRES	2		;�ړ�����8���
_CPUD_PV_AD3		.SRES	2		;�ړ�����8���
_CPUD_PV_AD4		.SRES	2		;�ړ�����8���
_CPUD_AD_INF		.SRES	2		;



;	*******************************************
;	***					***
;	***	2015-10-01			***
;	***	100�i�d�l�\��			***
;	***					***
;	*******************************************
_PVP_MOT_ACT_STEP	.sres	2	;���s���̍s��No.�@�s������

_PVP_MOT_STS		.sres	100*2	;�\���ð��
_PVP_CKLMT_AGL		.sres	2	;�p�x�ЯĒl(���وʒu��)�@�p�x�Ԋێ���
_PVP_CKLMT_SPD		.sres	2	;���x�ЯĒl(���وʒu��)�@���x�Ԋ�

;-----------------------����̧�ق̍ŏI�s�ɂ���@MAP�m�F�p�@3FFA�����E---------------------
_CPUA_DP_SIZEHCK_END:
