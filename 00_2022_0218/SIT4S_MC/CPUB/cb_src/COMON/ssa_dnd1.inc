;	***********************************
;	***				***
;	***	�i�搡���R���g���[��	***
;	***				***
;	***********************************
;	***********************************
;	***				***
;	***	Ӱ��ݑS�H��		***
;	***				***
;	***********************************
;	======== ��~�҂�(���x�ύX)	0000,0000	====
;	======== ��όv�� 		BIT0		====
;	======== �ċN��/�I��		BIT1		====
;	======== BIT6;�I��
_DND_NEG_STEP_CTRL:
	SUB_START

	MOV.L	#_INT_DND_STEP_FLG,R1		;�i��苤��
	MOV.W	@R1,R0				;
	TST	#(BIT1+BIT0),R0			;
	TST_BIT_OF DND_NEGSTEPCTL_100		;BIT0:��ϐ���J�n
	M_BRA	DND_NEGSTEPCTL_300		;BIT1:���̉�]�N��

DND_NEGSTEPCTL_100:
	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0	;

	FAR_JSR	#_LOD_POS_STS_REG,R1	;
	TST	#BIT2,R0		;��~?
	TST_BIT_ON DND_NEGSTEPCTL_200	;YES ��~�� 1:��~ 0:���o��
	M_BRA	DND_NEGSTEPCTL_900	;

;	===========================
;	===	���o��~	===
;	===	��]��		===
;	===========================
DND_NEGSTEPCTL_200:
;	--------�����o������----------

;	------------ 2021-11-11-------------
	MOV.L	#_NEG_DND_STOP_POS_END_F,R1			;
	MOV.B	@R1,R0								;
	TST		R0,R0								;
	TST_BIT_ON DND_NEGSTEPCTL_900				;

;	------------ 2021-11-11-------------
	FAR_JSR	#_DND_NEG_STOP_SVCHK,R0				;

	MOV.L	#_NEG_DND_STOP_USE_F,R1				;	//�㎀�_(0)<��~<170�̎� On
	MOV.B	@R1,R0								;
	TST		R0,R0								;
	TST_BIT_OF DND_NEGSTEPCTL_250				;

	FAR_JSR	#_DND_NEG_LNK_STEP_CHANGE2,R0		;

	MOV.B	#BIT0,R0
	MOV.L	#_NEG_DND_STOP_POS_END_F,R1			;
	MOV.B	R0,@R1								;

	M_BRA	DND_NEGSTEPCTL_900					;


DND_NEGSTEPCTL_250:
;	-----------------------------------

;	>>>> �ؑ���Ͼ�� <<<<
;	===============================================
;;;2014-05-30	MOV.L	#_PAR_START_WAIT_DND,R1					;�i�掞�ؑ�WAIT����
	MOV.L	#(_PAR_START_WAIT_DND-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;�i�掞�ؑ�WAIT����
	MOV.W	@R1,R1					;
	MOV.L	#_SDAT_WAIT_PVTIM,R4						;
	MOV.L	R1,@R4								;
;	FLG=(BIT0):���								;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_DND_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;��ϋN��
	M_BRA	DND_NEGSTEPCTL_900						;

DND_NEGSTEPCTL_300:
	TST	#BIT1,R0		;
	TST_BIT_ON DND_NEGSTEPCTL_400	;

;	===== �ؑ���ϑ҂� ====

	DN_TIME LG=L,MEM_ADR=_SDAT_WAIT_PVTIM	,WKREG1=R1,WKREG2=R4	;2014-05-30


	MOV.L	#_SDAT_WAIT_PVTIM,R4	;
	MOV.L	@R4,R1			;
	TST	R1,R1			;
	TST_BIT_OF DND_NEGSTEPCTL_320	;
	M_BRA	DND_NEGSTEPCTL_900	;

DND_NEGSTEPCTL_320:
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_DND_STEP_FLG,LG=W,BIT=BIT1,WKREG=R1 ;TIME UP
	M_BRA	DND_NEGSTEPCTL_900		;


;	======= ���̋N�� =====
DND_NEGSTEPCTL_400:
;	===================================
;	===	��d��H�΍�		===
;	===	�H������		===
;	===================================
	FAR_JSR	#_CMPAB_STEP_END_PROC,R0	;
	TST	R0,R0				;
	TST_BIT_ON DND_NEGSTEPCTL_420		;
	M_BRA	DND_NEGSTEPCTL_900		;

DND_NEGSTEPCTL_420:				;
	FAR_JSR	#_CMPSTP_STEP_END_CLR,R0	;//�ʒu���ߊ����Ƃ�����

;;2021-11-11;	====  ���̓���̉��Z =====
;;2021-11-11	MOV.L	#_INT_DND_NEG_STEP,R5		;
;;2021-11-11	MOV.W	@R5,R0				;
;;2021-11-11	CMP/EQ	#1,R0				;
;;2021-11-11	BF	DND_NEGSTEPCTL_440		;����0or2�Ȃ�ҋ@�_�Ȃ̂�1�֑J��
;;2021-11-11	MOV	#2,R0				;����1(�ڕW�ʒu�ւ̓���)�Ȃ�2�ցi�ҋ@�_�j
;;2021-11-11	M_BRA	DND_NEGSTEPCTL_460		;
;;2021-11-11DND_NEGSTEPCTL_440:				;
;;2021-11-11	MOV	#1,R0				;����0or2(�ҋ@�_�ւ̓���)�Ȃ�1
;;2021-11-11DND_NEGSTEPCTL_460:				;
;;2021-11-11	MOV.W	R0,@R5				;
;;2021-11-11	FAR_JSR	#_DND_LNK_STEP_CHECK1,R0	;<<>>
;;2021-11-11	FAR_JSR	#_DND_LNKPLS_OBJMAK1,R1		;�ï�߂ɉ����đҋ@�_1/�ڕW�ʒu/�ҋ@�_2 _POS_DRV_DIRECT
;;2021-11-11

	FAR_JSR	#_DND_NEG_LNK_STEP_CHANGE0,R0				;
	FAR_JSR	#_DND_LNKPLS_OBJMAK1,R1					;�ï�߂ɉ����đҋ@�_1/�ڕW�ʒu/�ҋ@�_2 _POS_DRV_DIRECT

;	===================
;	===	�N��	===
;	===================
DND_NEGSTEPCTL_580:
	FAR_JSR	#_DND_1STEP_DATA_MAK1,R0	;_LNGTH,SHIN,SPEED
	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0	;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0	;�ʒu����LSI����(������)
	FAR_JSR	#_FWD_REV_START,R1		;�N��
	XOR	R0,R0				;
	MOV.L	#_INT_DND_STEP_FLG,R1		;//�ï��,�i��苤��
	MOV.W	R0,@R1				;Q
	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0	;

DND_NEGSTEPCTL_900:
	SUB_END
	M_RTS


