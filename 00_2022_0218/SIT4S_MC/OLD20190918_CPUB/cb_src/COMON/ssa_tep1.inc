;	***********************************
;	***				***
;	***	�蓮�p���T�R���g���[��	***
;	***				***
;	***********************************
;	����off�ŏI��
;	�����`�F���W
;	�����`�F���W�ɂ���~�w��
;	��~�҂�
;	
;	+�������쒆�ɶ�����"-1�ȉ�"�ɂȂ�����+���슮����"-"�ɖ߂��F�����̍X�V,0CLR�͍s�Ȃ�Ȃ�
;	-�������쒆�ɶ�����"+1�ȏ�"�ɂȂ�����-���슮����"+"�ɐi�߂�:
;
;	(1)DIRECTION�׸ނƶ������r����
;	(2-1)������������ٽ���������綳�����ʒu����LSI�ɑ�������.����=0�Ƃ���
;	(2-2)�t�����ɑ���������ٽ�����o����҂�
;BIT1	(>3-1)�c����ٽ=0�ɂȂ�����w�߂�OFF����B�F�F�F�ï�߼��ݽ�J�n
;BIT2	(>3-2)�ʒu���ߊ���������10msecWAIT����
;BIT6	(>3-3)�N�����Z���s�Ȃ�
;
;	TEP_STEP_FLG
;		.BIT0 ���o����
;		.BIT1 5msecWAIT
;		
;
;	plsData-->start-on
	.EXPORT	_TEP_FLG_CLR
	.EXPORT	_TEPA_START_CHK			;
	.EXPORT	_TEPA_PLSCNT_CLR		;
	.EXPORT	_TEPA_PLSCNT_CHK		;

	.IMPORT	_PAR_TEP_WATTIM		;3 1~50msec
	.IMPORT	_PAR_TEP_BEFPLS		;4 10pls
	.IMPORT	_PAR_TEP_MINSPD		;

;;;;�܂��g�ݍ��܂Ȃ�	.IMPORT	_SH4toSH2_TEPSIG	;
;;;;�܂��g�ݍ��܂Ȃ�	.IMPORT	_SH2toSH4_TEPSIG	;


_DND_TEP_STEP_CTRL:
	SUB_START

;	-------- 2013-06-05 -----------------------------
	DN_TIME LG=W,MEM_ADR=_TEP_CNTSMP_TIM,WKREG1=R1,WKREG2=R2	;�����


	FAR_JSR	#_TEP_ADD_PLS_MAK,R0		;

	MOV.L	#_TEP_STEP_FLG,R1		;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF DND_TEPSTEPCTL_020		;
	M_BRA	DND_TEPSTEPCTL_400		;
DND_TEPSTEPCTL_020:

	TST	#BIT0,R0			;
	TST_BIT_ON DND_TEPSTEPCTL_200		;

	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0	;
	FAR_JSR	#_LOD_POS_STS_REG,R1		;
	TST	#BIT2,R0			;��~?
	TST_BIT_OF DND_TEPSTEPCTL_180		;NO ��~��? 0:���o�� 1:��~ 


	FAR_JSR	#_TEP_REVPLS_LT_CLR,R0
;;�܂��g�ݍ��܂Ȃ�	FAR_JSR	#_TEP_CPUAB_HAND_CLR,R0		;

;	------ ILDE[0,0] 1�񂾂��ł͂Ȃ���I�I--------
	MOV.L	#_TEP_POS_ADD_CNT,R1						;
	MOV.L	@R1,R2								;
	TST	R2,R2								;
	TST_BIT_OF DND_TEPSTEPCTL_180						;
										;��ٽ�L��J��1
	FAR_JSR	#_INT_TEP_RESTART,R0						;2013-05-26
	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;[���̎��_����ٽ�ݒ肵�Ă��Ȃ�]

DND_TEPSTEPCTL_180:
	M_BRA	DND_TEPSTEPCTL_900		;

;	-------------- �����o���҂�------------
DND_TEPSTEPCTL_200:
	FAR_JSR	#_FWD_REV_STSIG_OFF_SPEC,R0					;
	FAR_JSR	#_LOD_POS_STS_REG,R1						;
	TST	#BIT2,R0							;��~?
	TST_BIT_OF DND_TEPSTEPCTL_220						;NO ��~��? 0:���o�� 1:��~ 

	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT1,WKREG=R1	;[�����o������ �J��2]
	FAR_JSR	#_TEP_REVPLS_LT_CLR,R0						;


;	------- 2013-06-05 ���o�����J�n�x��100ms--------
	MOV.L	#_TEP_STEP_SVWTTM1,R1						;//2013-06-05
	MOV.W	@R1,R2								;
	MOV.L	#_TEP_STEP_WTTM,R1						;
	MOV.W	R2,@R1								;
	M_BRA	DND_TEPSTEPCTL_900						;

DND_TEPSTEPCTL_220:								;
;	2013-05-20 ���쒆�̉��Z						;

	FAR_JSR	#_TEPA_ADD_LSI,R0					;

DND_TEPSTEPCTL_290:							;
	M_BRA	DND_TEPSTEPCTL_900					;


;	-------- �x���҂�--------
DND_TEPSTEPCTL_400:
	MOV.L	#_TEP_STEP_WTTM,R1				;
	MOV.W	@R1,R0						;
	TST	R0,R0						;
	TST_BIT_OF DND_TEPSTEPCTL_420				;
	ADD	#-1,R0						;
	MOV.W	R0,@R1						;

;;�܂��g�ݍ��܂Ȃ�	FAR_JSR	#_TEP_CPUAB_HAND_CLR,R0				;
	M_BRA	DND_TEPSTEPCTL_900				;


DND_TEPSTEPCTL_420:						;

;	---- ��ϒ�����ٽ���������B�ċN��[BIT1->BIT0]--------
	MOV.L	#_TEP_POS_ADD_CNT,R1						;
	MOV.L	@R1,R0								;
	TST	R0,R0								;
	TST_BIT_OF DND_TEPSTEPCTL_800						;

	FAR_JSR	#_INT_TEP_RESTART,R0						;
	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_STEP_FLG,LG=W,BIT=BIT0,WKREG=R1	;
	M_BRA	DND_TEPSTEPCTL_900						;


;	--------- ���S����ѱ���-------
DND_TEPSTEPCTL_800:
	FAR_JSR	#_TEP_START_INIT1,R0						;[�J��0]


DND_TEPSTEPCTL_900:
	NOP
DND_TEPSTEPCTL_EXT:
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	�N������		***
;	***				***
;	***********************************
_MN_TEP_START
	SUB_START
	FAR_JSR	#_TEP_START_INIT1,R0			;

;;;;;;2014-09-14	MOV.L	#_LINK_PV_ABSPLS,R4		;
;;;;;;2014-09-14	MOV.L	@R4+,R1					;
;;;;;;2014-09-14	MOV.L	@R4,R2					;

	MOV.L	#_LINK_RL_OBJ_ABSPLS,R4			;//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)
	MOV.L	@(0,R4),R1				;
	MOV.L	@(4,R4),R2				;
	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4			;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R4					;
	MOV.L	R2,@(1*4,R4)				;�ڕW�ʒu���
	FAR_JSR	#_NOW_INC_DIG_MAK,R0			;
	FAR_JSR	#_TEP_ADD_PLS_MAK,R0			;
;	--- �ʒu�f�[�^�����Ȃ�---- FAR_JSR #_TEP_SV_OBJ_MAK,R0


	FAR_JSR	#_DNDINC_SPD_SET,R4				;�Ƃ肠��������͐G��Ȃ�[]

;	---------- 2013-06-05
	XOR	R0,R0						;
	MOV.L	#_TEP_CNTSMP_TIM,R1				;
	MOV.W	R0,@R1						;
	MOV.L	#_TEP_STEP_WTTM,R1				;
	MOV.W	R0,@R1						;




	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	�ċN������		***
;	***				***
;	***********************************
;	<<<<<<<<<<<100msec�̑��x�œ��삳����>>>>>>>>>>
;
_INT_TEP_RESTART
	SUB_START


	XOR	R2,R2
	MOV.L	#_TEP_INPLS_FLG,R1		;//2013-06-20
	MOV.W	R2,@R1				;

;	--------- 2013-06-19 -----------------
	FAR_JSR	#_TEP_REVPLS_LT_CLR,R0
;;�܂��g�ݍ��܂Ȃ�	FAR_JSR	#_TEP_CPUAB_HAND_CLR,R0		;

;	--------- 2013-06-05 -----------------
	FAR_JSR	#_TEP_SPD_CALC1,R0			;
	FAR_JSR	#_TEP_SPD_SET,R0			;

;;;2013-06-05	FAR_JSR	#_DNDINC_SPD_SET,R4		;

;;;;;;	FAR_JSR	#_POS_LSI_START_INITAL,R0					;
	FAR_JSR	#_POS_LSI_START_INITAL_TEP,R0					;2013-06-13

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1						;�ڕW���x
	MOV.L	@R1,R2								;
	FAR_JSR	#_POS_LSI_TOP_SPEED_SET,R1					;
	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0					;

	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0					;
	FAR_JSR	#_POS_PLSOUT_SET_RETRY,R0					;(��~������̋N���̏ꍇ�̂ݗL���E����̂�)
	FAR_JSR	#_FWD_REV_START,R1						;�N��
	MEM1_BIT0_TO_BIT7_ORSET MEM=_INT_POS_CTL_FLAG,LG=W,BIT=BIT0,WKREG=R1	;
	FAR_JSR	#_BRK_ERR_WORK_CLR1,R0						;
	FAR_JSR	#_POS_CMP_1STEP_START_INI,R0					;
	FAR_JSR	#_TEP_START_INIT1,R0						;
	SUB_END
	M_RTS


;;;;;;;;2013-06-05�������g�p	***********************************
;;;;;;;;	***				***
;;;;;;;;	***	��ADD			***
;;;;;;;;	***				***
;;;;;;;;;	***********************************
;;;;;;;;_TEP_ADD_OBJMAK:
;;;;;;;;	SUB_START
;;;;;;;;	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0		;
;;;;;;;;	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0		;
;;;;;;;;	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;�ʒu����LSI����(������)
;;;;;;;;	FAR_JSR	#_TEP_START_INIT1,R0			;
;;;;;;;;	SUB_END
;;;;;;;;	M_RTS


_TEP_START_INIT1
	SUB_START

	MEM1_0CLR MEM=_TEP_STEP_FLG,LG=W,WKREG1=R1,CLRREG=R0		;
	MEM1_0CLR MEM=_TEP_POS_ADD_CNT,LG=L,WKREG1=R1,CLRREG=R0		;
;	2013-06-20
	MEM1_0CLR MEM=_TEP_INPLS_FLG,LG=W,WKREG1=R1,CLRREG=R0		;

;;;;;;;;2013-06-05	MEM1_0CLR MEM=_TEP_POS_ADD_CNTOLD,LG=L,WKREG1=R1,CLRREG=R0	;

	FAR_JSR	#_TEP_REVPLS_LT_CLR,R0	;2013-07-19

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***		�{��			***
;	***					***
;	*******************************************
;	Output R2:NEW CUNTER
;	Output R3:OLD CUNTER
;	�N������R2,R3�͎g�p���Ȃ�
_TEP_ADD_PLS_MAK:
	SUB_START

;	----------- DIRECT�쐬 2013-06-20--------
	MOV.L	#_TEP_IN_ADD,R4			;
	MOV.W	@R4,R2				;
	TST	R2,R2				;
	TST_BIT_OF TEP_ADD_PLSMK_030		;

	MOV.W	#BIT4,R0			;
	CMP/PZ	R2
	BT	TEP_ADD_PLSMK_020		;FWD
	MOV.W	#BIT5,R0			;REV
TEP_ADD_PLSMK_020:
	MOV.L	#_TEP_INPLS_FLG,R1		;//2013-06-20
	MOV.W	@R1,R2				;
	OR	R0,R2				;
	MOV.W	R2,@R1				;
TEP_ADD_PLSMK_030:
;	-----------------------------------------


	MOV.L	#_SET1_PLSALO_PLS,R3		;//�p���T�{����
	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
	MOV.W	@R1,R0				;
	TST	#BIT2,R0			;0:LOW 1:HIGH
	TST_BIT_OF TEP_ADD_PLSMK_050		;
	MOV.L	#_SET1_PLSAHI_PLS,R3		;�p���T�{����
TEP_ADD_PLSMK_050:
	MOV.W	@R3,R1				;
	MOV.W	#D'1000,R4			;
	CMP/HS	R1,R4				;
	BT	TEP_ADD_PLSMK_100		;
	MOV	R4,R1				;
TEP_ADD_PLSMK_100:				;
	TST	R1,R1				;
	TST_BIT_ON TEP_ADD_PLSMK_150		;
	MOV	#1,R1				;
TEP_ADD_PLSMK_150:				;

	XOR	R0,R0
	MOV.L	#_TEP_IN_ADD,R4			;
	MOV.W	@R4,R2				;
	MOV.W	R0,@R4				;0CLR
						;R2

	MULS.W	R2,R1				;
	STS	MACL,R2				;
	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	MOV.L	@R1,R3				;
	ADD	R3,R2				;
	MOV.L	R2,@R1				;R3:OLD R2:NEW
;;;;;;;2013-06-05	MOV.L	#_TEP_POS_ADD_CNTOLD,R1		;[[[[[[[[�g�p���Ă��Ȃ�]]]]]]]]]]]]]]]]
;;;;;;;2013-06-05	MOV.L	R3,@R1				;

	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	�ʒu���ߑ�			***
;	***	�N�����̈ʒu�쐬		***
;	***	�ċN�����̈ʒu�쐬		***
;	***					***
;	*******************************************
_TEP_1STEP_DATA_MAK1:
	SUB_START

	MOV.L	#_CPOS_CTL_MATH,R0		;
	MOV.W	@R0,R0				;
;;	TST	#_DMATH_CNTROT,R0		;
	TST	#(_DMATH_CNTROT+_DMATH_DNDRIV),R0	;[2009-10-07���U�q]
	TST_BIT_ON TEP_1STEP_DATMK1_080		;

	FAR_JSR	#_NEG_TEPA_AREA_CHK,R0		;���]���[�h�̃G���A
	TST	R0,R0				;
	TST_BIT_OF TEP_1STEP_DATMK1_080		;+/- OK

	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	MOV.L	@R1,R2				;
	CMP/PZ	R2				;
	BT	TEP_1STEP_DATMK1_050		;
;	------ "-" PLS�����Ă���----
	CMP/PZ	R0				;
	BT	TEP_1STEP_DATMK1_070		;+�̂݋���
	M_BRA	TEP_1STEP_DATMK1_080		;-:OK

;	------ + PLS----
TEP_1STEP_DATMK1_050:
	CMP/PL	R0				;"+"OK?
	BT	TEP_1STEP_DATMK1_080		;YES OK
TEP_1STEP_DATMK1_070:
	MOV.L	#_TEP_POS_ADD_CNT,R1		;
	XOR	R0,R0				;
	MOV.L	R0,@R1				;

;	-----------�ӂ肱�E��]�̒ʏ�@�y�є��]�̈ʒu�J�b�g��̏���------------
TEP_1STEP_DATMK1_080:
	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4					;
	MOV.L	@R4,R1							;
	MOV.L	@(1*4,R4),R2						;

	MOV.L	#_TEP_POS_ADD_CNT,R0					;�ʒu���ߑ��g�p�f�[�^
	MOV.L	@R0,R6							;
	EXTS_4B_TO_8B REG8B_H=R5,REG4B=R6				;
	ADD8B DT_REGH=R5,DT_REGL=R6,DT_ANS_REGH=R1,DT_ANS_REGL=R2	;R1,R2

;;	------2007-01-23 LIMIT R1,R2(OBJ) R5,R6(DELT):���]�̎�---------------
;;	MOV.L	#_CPOS_CTL_MATH,R0		;
;;	MOV.W	@R0,R0				;
;;	TST	#_DMATH_CNTROT,R0		;
;;	TST_BIT_ON TEP_1STEP_DATMK1_200		;
;;
;;	--(���])--
;;	MOV.L	#_TEP_POS_ADD_CNT,R0		;�ʒu���ߑ��g�p�f�[�^
;;	MOV.L	@R0,R0				;
;;	CMP/PZ	R0				;
;;	BT	TEP_1STEP_DATMK1_100		;
;;	----- MINAS LIMIT -------
;;
;;
;;TEP_1STEP_DATMK1_100:
;;	----- PLAS LIMIT -------
;;
;;
;;
;;
;;TEP_1STEP_DATMK1_200:
	MOV.L	#_LINK_SV_OBJ_ABSPLS,R4			;
	MOV.L	R1,@R4					;
	MOV.L	R2,@(1*4,R4)				;
	MOV.L	#_LINKX_SV_OBJ_ABSPLS,R4		;//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	MOV.L	R1,@R4					;
	MOV.L	R2,@(4,R4)				;

	MOV.L	#_LNGTH_ADD_DATA,R4			;//�����t��
	MOV.L	R5,@R4					;
	MOV.L	R6,@(4,R4)				;

	MOV.L	#_LT_LNGTH_ADD_DATA,R4			;//�����t��
	MOV.L	R5,@R4					;
	MOV.L	R6,@(4,R4)				;

	XOR	R3,R3					;
	CMP/PZ	R5					;
	BT	TEP_1STEP_DATMK1_100			;
	MOV.W	#BIT0,R3				;
TEP_1STEP_DATMK1_100:
	MOV.L	#_POS_DRV_DIRECT,R1			;�N����(SV-LEVEL)
	MOV.W	R3,@R1					;

	MOV.L	#_POSLSI_DRIV_SHIN,R1			;
	MOV.W	@R1,R0					;
	AND	#LOW ~BIT0,R0				;
	OR	R3,R0					;
	MOV.W	R0,@R1					;

;	---------- 2013-06-20 ------------
	XOR	R0,R0				;
	MOV.L	#_TEP_INPLS_FLG,R1		;//2013-06-20
	MOV.W	R0,@R1				;

	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	�蓮�p���T�̔��]�̃��~�b�g	***
;	***	2007-01-23			***
;	*******************************************
;	0~165������͈͂Ƃ���
;	180~0~165�܂ł�+�����󂯕t����(=165~180�܂ł���׽����t���Ȃ�)
;	0~165~180�܂ł�-�����󂯕t����(=180~0�܂ł�ϲŽ����t���Ȃ�)
;	������0~165�͈̔͂�+/-�󂯕t����
;
;
;	180
;
;
;
;
;	MOV.L	#_INC_LINK_NOWROT_OFSPLS_P,R4			;������g�p���邩
;	MOV.L	@R4,R2						;
;
;	0(+/-)ok
;	1(+)ok
;	-1(-)ok
;
_TEP_DNPOS_HIS	.EQU	100	;10.0�x

_NEG_TEPA_AREA_CHK:
	SUB_START


	MOV.L	#_SETX_UPDN_CHK_DN_DIG,R4	;180.0�x(�����_�p�x 180.0)
	MOV.L	@R4,R1				;
;;;;	MOV.L	#_SETX_LINK_UP_POS_DN,R4	;�ݸ(�͈͔�r)
;;;;	MOV.W	@R4,R3				;�ҋ@�_-��

	MOV.L	#_SET1_UPAREA_DIG1,R4		;�ݸ(�͈͔�r)
	MOV.W	@R4,R3				;�ҋ@�_
	MOV.L	#_INC_ENC360,R4			;
	MOV.W	@R4,R2				;R1(180)~R3(0)�͈̔͂��H
	FAR_JSR	#_DIG_AREA_CHK1,R0		;ANS.R5=1(ϲŽ���󂯕t���Ȃ�)
	CMP/PZ	R5				;
	BT	NEG_TEPA_ARACHK200		;+�̂݉\


	MOV.L	#_SETX_DNAREA_JG_LNK,R4		;���]�ݒ�s�͈�LINK �x
	MOV.L	@R4,R1				;
	MOV.L	#_SETX_UPDN_CHK_DN_DIG,R4	;180.0�x(�����_�p�x 180.0)
	MOV.L	@R4,R3				;
	MOV.W	#_TEP_DNPOS_HIS,R0		;10.0
	ADD	R0,R3				;10.0��..
	MOV.L	#_INC_ENC360,R4			;
	MOV.W	@R4,R2				;R1(180)~R3(0)�͈̔͂��H
	FAR_JSR	#_DIG_AREA_CHK1,R0		;ANS.R5=1(+�󂯕t���Ȃ�)
	BT	NEG_TEPA_ARACHK100		;

	XOR	R0,R0				;
	M_BRA	NEG_TEPA_ARACHK300		;+/- OK

;	-------- -���󂯕t����=====
NEG_TEPA_ARACHK100:
	MOV	#-1,R0				;
	M_BRA	NEG_TEPA_ARACHK300		;

;	-------- +���󂯕t����=====
NEG_TEPA_ARACHK200:
	MOV	#1,R0				;
NEG_TEPA_ARACHK300:


	SUB_END
	M_RTS



;	***********************************
;	***				***
;	***	�蓮�p���T�t���O	***
;	***				***
;	***********************************
_TEP_FLG_CLR
	SUB_START
	XOR	R0,R0
	MOV.L	#_TEP_MODE_DRV,R1	;//�N�����ɔ���
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

_TEP_FLG_START
	SUB_START
	MOV.W	#BIT0,R0
	MOV.L	#_TEP_MODE_DRV,R1	;//�N�����ɔ���
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	�蓮�p���T�N������	***
;	***	�N��=1			***
;	***				***
;	***********************************
;------------ 341.1ON���Ў�ON����p�̏��ʂɕύX����2011-07-04
;
_TEPA_START_CHK:
	SUB_START

	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04��p����
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON TEPA_STARTCHK_NG		;��p����ɂȂ���

	MOV.L	#_BTTN_FLG,R1			;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_OF TEPA_STARTCHK_NG		;

	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	@R1,R2				;
	CMP/PZ	R2				;
	BT	TEPA_STARTCHK_050		;
	NEG	R2,R2				;
TEPA_STARTCHK_050:
	MOV.W	#D'1,R1				;1�ŗǂ���
	CMP/GE	R1,R2				;
	BT	TEPA_STARTCHK_OK		;
TEPA_STARTCHK_NG:
	XOR	R0,R0				;
	M_BRA	TEPA_STARTCHK_END		;

TEPA_STARTCHK_OK:
	FAR_JSR	#_TEP_FLG_START,R0		;
	MOV	#1,R0				;
TEPA_STARTCHK_END:

	SUB_END
	M_RTS

;;;	------------ 341.1ON���Ў�ON����p�̏��ʂɕύX����2011-07-04
;;;_TEPA_START_CHK:
;;;	SUB_START
;;;
;;;	MOV.L	#_CB_SEQ_CB_SEL341,R1		;341
;;;	MOV.W	@R1,R0				;
;;;	TST	#BIT1,R0			;
;;;	TST_BIT_OF TEPA_STARTCHK_NG		;����
;;;
;;;	MOV.L	#_TEP_IN_ADD,R1			;
;;;	MOV.W	@R1,R2				;
;;;	CMP/PZ	R2				;
;;;	BT	TEPA_STARTCHK_050		;
;;;	NEG	R2,R2				;
;;;TEPA_STARTCHK_050:
;;;	MOV.W	#D'1,R1				;1�ŗǂ���
;;;	CMP/GE	R1,R2				;
;;;	BT	TEPA_STARTCHK_OK		;
;;;TEPA_STARTCHK_NG:
;;;	XOR	R0,R0				;
;;;	M_BRA	TEPA_STARTCHK_END		;
;;;
;;;TEPA_STARTCHK_OK:
;;;	FAR_JSR	#_TEP_FLG_START,R0		;
;;;	MOV	#1,R0				;
;;;TEPA_STARTCHK_END:
;;;
;;;	SUB_END
;;;	M_RTS

;	***********************************
;	***				***
;	***	�蓮�p���T�J�ڎ���	***
;	***	�p���X�N���A		***
;	***				***
;	***********************************
	.IMPORT		_PVP_CPUA_TEPPLS
	.IMPORT		_PVP_CPUB_TEPPLS

_TEPA_PLSCNT_CLR
	SUB_START

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_PVP_CPUA_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AELSE
	MOV.L	#_PVP_CPUB_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AENDI

	MOV.L	#_NEW_TEP_CNT,R1		;
	MOV.W	R2,@R1				;

	XOR	R2,R2
	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	R2,@R1				;

	MOV.L	#_TEP_POS_ADD_CNT,R1		;�ʒu���ߑ��g�p�f�[�^
	MOV.L	R2,@R1				;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	�蓮��ٻ�̑�������	***
;	***				***
;	***				***
;	***********************************
_TEPA_PLSCNT_CHK:
	SUB_START

	.AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
	MOV.L	#_PVP_CPUA_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AELSE
	MOV.L	#_PVP_CPUB_TEPPLS,R1		;
	MOV.W	@R1,R2				;
	.AENDI

	MOV.L	#_NEW_TEP_CNT,R1		;
	MOV.W	@R1,R3				;
	MOV.W	R2,@R1				;
	SUB	R3,R2				;
	MOV.L	#_TEP_IN_ADD,R1			;
	MOV.W	R2,@R1				;

;	------ 2011-07-04 �ǉ��@�^�]�t����--
	TST	R2,R2				;�ω�����?
	TST_BIT_OF TEPA_PLSCNTCHK_100		;

	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04��p����
	MOV.W	@R1,R0				;
	TST	R0,R0
	TST_BIT_ON TEPA_PLSCNTCHK_050		;

	MOV.L	#_BTTN_FLG,R1			;
	MOV.W	@R1,R0				;
	TST	#BIT1,R0			;
	TST_BIT_ON TEPA_PLSCNTCHK_100		;

TEPA_PLSCNTCHK_050:

	MOV.W	#D'51,R0			;50*10=0.5�b
	MOV.L	#_TEPA_PLS_ZERO_TIM,R1		;2011-07-04��p����
	MOV.W	R0,@R1				;

TEPA_PLSCNTCHK_100:
	

	SUB_END
	M_RTS


;	*******************************************
;	***					***
;	***	2013-05-26			***
;	***					***
;	*******************************************
;	10��ٽ,��������----���C���K�v
_TEPA_ADD_LSI:
	SUB_START

;;�܂��g�ݍ��܂Ȃ� .AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH4toSH2_TEPSIG,R5	;[�����̃C���^�[���b�N]
;;�܂��g�ݍ��܂Ȃ� .AELSE
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH2toSH4_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ� .AENDI

	MOV.L	#_TEP_REVPLS_LT_FLG,R5	; 
	MOV.W	@R5,R0				;
	TST	R0,R0				;
	TST_BIT_ON TEPA_ADDLSI_025		;��~

;	---------- 2013-06-20 ------------
	XOR	R2,R2
	MOV.L	#_TEP_INPLS_FLG,R1		;//2013-06-20
	MOV.W	@R1,R0				;
	MOV.W	R2,@R1				;

	TST	R0,R0					;
	TST_BIT_OF TEPA_ADDLSI_030			;

	MOV.L	#_POS_DRV_DIRECT,R1			;�N����(SV-LEVEL)
	MOV.W	@R1,R2					;
	MOV.B	#BIT0,R4				;
	TST	R4,R2					;DIRCT +
	TST_BIT_ON TEPA_ADDLSI_010			;

	TST	#BIT5,R0				;�t�]�L��?
	TST_BIT_ON TEPA_ADDLSI_020			;�L��
	M_BRA	TEPA_ADDLSI_030				;


TEPA_ADDLSI_010:
	TST	#BIT4,R0				;���]�L��?
	TST_BIT_ON TEPA_ADDLSI_020			;�L��
	M_BRA	TEPA_ADDLSI_030				;

TEPA_ADDLSI_020:
	FAR_JSR	#_TEP_SPD_CALC3,R0			;
	FAR_JSR	#_TEP_SPD_SET_CHG,R0			;
;;�܂��g�ݍ��܂Ȃ�FAR_JSR	#_TEP_CPUAB_HAND_STOP,R0		;2013-06-19
	MEM1_BIT0_TO_BIT7_ORSET MEM=_TEP_REVPLS_LT_FLG,LG=W,BIT=BIT0,WKREG=R1	;
	
TEPA_ADDLSI_025:
	M_BRA	TEPA_ADDLSI_EXT				;

;	---------------------------------------------------
TEPA_ADDLSI_030
;	----------- ���� 2013-06-05--------
	MOV.L	#_TEP_CNTSMP_TIM,R1		;
	MOV.W	@R1,R0				;
	TST	R0,R0				;
	TST_BIT_ON TEPA_ADDLSI_EXT		;

;	-----------------------------------
	MOV.L	#_TEP_STEP_SVSMPTM,R0		;
	MOV.W	@R0,R2				;
	MOV.W	R2,@R1				;
;	-----------------------------------
	MOV.L	#_TEP_POS_ADD_CNT,R1			;
	MOV.L	@R1,R0					;
	TST	R0,R0					;
	TST_BIT_OF TEPA_ADDLSI_EXT			;


	FAR_JSR	#_LOAD_REST_PLS,R0					;LOAD PLS

	MOV.L	#_TEP_ADDCHK_SVPLS,R1					;SYS_PARA 10PLS
	MOV.W	@R1,R4

	CMP/HI	R0,R4							;10pls�ȉ� R0<10
	BT	TEPA_ADDLSI_EXT						;"��d��HHAND�Ώ�"
									;���

;	---------�p���X���Z���� 2013-06-05 --------------
	FAR_JSR	#_TEP_SPD_CALC2,R0			;
	FAR_JSR	#_TEP_SPD_SET_CHG,R0			;

	FAR_JSR	#_TEP_1STEP_DATA_MAK1,R0		;CNT=0 CLR,�ڕW�ύX
	FAR_JSR	#_POS_LENGTH_ADD_DATA,R0		;
	FAR_JSR	#_POS_PLS_OUTPUT_DATA,R0		;�ʒu����LSI����(������)

	XOR	R0,R0
	MOV.L	#_TEP_POS_ADD_CNT,R1
	MOV.L	R0,@R1


TEPA_ADDLSI_EXT:

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	���N�����̃G���A�쐬	***
;	***				***
;	***********************************
;;2013-05-26 _DNDTEP_STEP_MAKE:
;;2013-05-26	SUB_START
;;2013-05-26	SUB_END
;;2013-05-26	M_RTS

;	***********************************
;	***				***
;	***	�H������̖ڕW�ʒu�쐬	***
;	***				***
;	***********************************
;;2013-05-26_DNDTEP_MAKE_OBJPOS:
;;2013-05-26	SUB_START
;;2013-05-26
;;2013-05-26
;;2013-05-26	SUB_END
;;2013-05-26	M_RTS

_TEP_SPD_CALC1:
	SUB_START
	MOV.L	#_TEP_STEP_SVWTTM1,R3	;//2013-06-05
	MOV.W	@R3,R4			;
	FAR_JSR	#_TEP_SPD_CALC_COM,R0	;ANS=TEP1

	MOV.L	#_TEP_CHG_SPD1,R1	;�N������SPD1,SPD2�Ƃ��������x
	MOV.L	@R1,R2			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;SPD2�����ۂɎg�p���鑬�x

	SUB_END
	M_RTS

_TEP_SPD_CALC2:
	SUB_START

	MOV.L	#_TEP_CHG_SPD1,R1	;�N������SPD1,SPD2�Ƃ��������x
	MOV.L	@R1,R2			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;SPD2�����ۂɎg�p���鑬�x

	MOV.L	#_TEP_STEP_SVSMPTM,R3
	MOV.W	@R3,R4			;
	FAR_JSR	#_TEP_SPD_CALC_COM,R0	;
	SUB_END
	M_RTS


_TEP_SPD_CALC_COM
	SUB_START

	MOV.L	#_TEP_POS_ADD_CNT,R3		;
	MOV.L	@R3,R2				;
	CMP/PZ	R2
	BT	TEP_SPD_CALCCOM_100			;
	NEG	R2,R2					;
TEP_SPD_CALCCOM_100

	MOV.W	#D'1000,R1				;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0		;10PLS:100msec

	TST	R2,R2					;
	TST_BIT_ON TEP_SPD_CALCCOM_200			;
	MOV.W	#1,R2					;
TEP_SPD_CALCCOM_200


	MOV.L	#_SET1_DNDINC_SPD1,R1	;
	MOV.L	@R1,R3			;

;	-----------MAX LIMIT----------
	CMP/HS	R2,R3
	BT	TEP_SPD_CALCCOM_300	
	MOV	R3,R2			;
TEP_SPD_CALCCOM_300


;	---------- MIN LIMIT -------------
	MOV.L	#_TEP_MIN_SPD_PLS,R1	;
	MOV.L	@R1,R3			;PLS/S

	CMP/HS	R3,R2
	BT	TEP_SPD_CALCCOM_400	
	MOV	R3,R2			;
TEP_SPD_CALCCOM_400

	MOV.L	#_TEP_CHG_SPD1,R1	;
	MOV.L	R2,@R1			;

	SUB_END
	M_RTS

;	-----------------------------------
_TEP_SPD_CALC3:
	SUB_START
	MOV.L	#_SET1_DNDINC_SPD1,R1	;
	MOV.L	@R1,R2			;
	MOV.L	#_TEP_CHG_SPD1,R1	;
	MOV.L	R2,@R1			;
	MOV.L	#_TEP_CHG_SPD2,R1	;
	MOV.L	R2,@R1			;
	SUB_END
	M_RTS



_TEP_SPD_SET:
	SUB_START

	MOV.L	#_TEP_CHG_SPD1,R1			;
	MOV.L	@R1,R2					;

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1			;//�ڕW���x
	MOV.L	R2,@R1					;

	SUB_END
	M_RTS

_TEP_SPD_SET_CHG:
	SUB_START

;;;;	MOV.L	#_TEP_CHG_SPD1,R1			;
;;;;	MOV.L	@R1,R2					;

	MOV.L	#_TEP_CHG_SPD2,R1			;
	MOV.L	@R1,R2					;

	MOV.L	#_LINK_SV_OBJ_SPDPLS,R1			;//�ڕW���x
	MOV.L	R2,@R1					;

	FAR_JSR	#_POS_LSI_TOP_SPEED_SETX,R1		;input R2

	SUB_END
	M_RTS




;	***************************************************
;	***						***
;	***						***
;	***						***
;	***						***
;	***************************************************
	.EXPORT	_TEP_DTMAK
_TEP_DTMAK:
	SUB_START

;	------------------------------------
	MOV.L	#(_PAR_TEP_BEFPLS-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R4							;
	MOV.W	#D'10,R0						;MIN PLS
	CMP/HS	R0,R4							;R4(10PLS)=< R0
	BT	TEP_SYS_SET080						;
	MOV	R0,R4							;
TEP_SYS_SET080:
	MOV.L	#_TEP_ADDCHK_SVPLS,R1
	MOV.W	R4,@R1			

;	--------------2013-06-05 -----------
	MOV.W	#D'100,R2						;DEF 100msec
	MOV.L	#(_PAR_TEP_WATTIM-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R0							;
	TST	R0,R0							;
	TST_BIT_OF TEP_SYS_SET100					;
	MOV	R0,R2							;
TEP_SYS_SET100:
	MOV.L	#_TEP_STEP_SVWTTM1,R1	;//2013-06-05
	MOV.W	R2,@R1			;

	MOV.L	#_TEP_STEP_SVWTTM1,R1	;//2013-06-05
	MOV.W	@R1,R2			;
	SHLR	R2			;
	MOV.L	#_TEP_STEP_SVSMPTM,R1	;
	MOV.W	R2,@R1			;1/2����

;	---------- �ŏ����x�����N�����x
	MOV.L	#(_PAR_TEP_MINSPD-_CB_SYS_PARAM000+_W_PARAM_TOP),R1	;
	MOV.W	@R1,R2							;
	TST	R2,R2							;
	TST_BIT_ON TEP_SYS_SET200					;
	MOV.W	#1,R2							;0.01%
TEP_SYS_SET200:								;
	FAR_JSR	#_CYCLE_SPD1,R0						;
	MOV.L	#_TEP_MIN_SPD_PLS,R1					;
	MOV.L	R2,@R1							;PLS/S

	MOV.L	#_POS_LSI_SPDMAX,R0				;
	MOV.L	@R0,R1						;
	MOV.L	#_POS_FRQ_SPDMAX,R0				;500KHZ(500000PLS/S)
	MOV.L	@R0,R4						;
	FAR_JSR	#_FPU_R2_MUL_R1_DIV_R4,R0			;
	MOV.L	#_TEP_MIN_SPD_FRQ,R1				;//���N�����x
	MOV.L	R2,@R1						;


	SUB_END
	M_RTS

;
;;�܂��g�ݍ��܂Ȃ�_TEP_CPUAB_HAND
;;�܂��g�ݍ��܂Ȃ�	SUB_START
;;�܂��g�ݍ��܂Ȃ�	XOR	R0,R0
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH4toSH2_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ�	MOV.W	@R5,R1			;
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH2toSH4_TEPSIG,R6	;
;;�܂��g�ݍ��܂Ȃ�	MOV.W	@R6,R2			;
;;�܂��g�ݍ��܂Ȃ�	CMP/EQ	R1,R2			;
;;�܂��g�ݍ��܂Ȃ�	BF	TEP_CPUAB_HDEXT		;
;;�܂��g�ݍ��܂Ȃ�	MOV.B	#BIT0,R0			;
;;�܂��g�ݍ��܂Ȃ�TEP_CPUAB_HDEXT
;;�܂��g�ݍ��܂Ȃ�
;;�܂��g�ݍ��܂Ȃ�	SUB_END
;;�܂��g�ݍ��܂Ȃ�	M_RTS

;;�܂��g�ݍ��܂Ȃ�_TEP_CPUAB_HAND_CLR
;;�܂��g�ݍ��܂Ȃ�	SUB_START
;;�܂��g�ݍ��܂Ȃ�	XOR	R0,R0
;;�܂��g�ݍ��܂Ȃ�
;;�܂��g�ݍ��܂Ȃ� .AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH4toSH2_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ� .AELSE
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH2toSH4_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ� .AENDI
;;�܂��g�ݍ��܂Ȃ�	MOV.W	R0,@R5
;;�܂��g�ݍ��܂Ȃ�
;;�܂��g�ݍ��܂Ȃ�	SUB_END
;;�܂��g�ݍ��܂Ȃ�	M_RTS


;*******************************************

;;�܂��g�ݍ��܂Ȃ�_TEP_CPUAB_HAND_STOP
;;�܂��g�ݍ��܂Ȃ�	SUB_START
;;�܂��g�ݍ��܂Ȃ�	MOV.B	#BIT0,R0		;
;;�܂��g�ݍ��܂Ȃ�
;;�܂��g�ݍ��܂Ȃ� .AIF	_CB_CPU_SEL EQ	_CB_CPUA	;
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH4toSH2_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ� .AELSE
;;�܂��g�ݍ��܂Ȃ�	MOV.L	#_SH2toSH4_TEPSIG,R5	;
;;�܂��g�ݍ��܂Ȃ� .AENDI
;;�܂��g�ݍ��܂Ȃ�	MOV.W	R0,@R5
;;�܂��g�ݍ��܂Ȃ�
;;�܂��g�ݍ��܂Ȃ�	SUB_END
;;�܂��g�ݍ��܂Ȃ�	M_RTS


;	*******************************************
;	***					***
;	***	��~������M���̃N���A		***
;	***					***
;	*******************************************
;
_TEP_REVPLS_LT_CLR
	SUB_START
	XOR	R0,R0			;
	MOV.L	#_TEP_REVPLS_LT_FLG,R1	;
	MOV.W	R0,@R1			;
	SUB_END
	M_RTS

;	*******************************************
;	***					***
;	***	Input R2			***
;	***	�ݸ(��������)��ٽ		***
;	***	Input R0 DIRECT			***
;	***	�����Œ�			***
;	***					***
;	*******************************************
;	MOV.L	#_SETX_DNAREA_JG_PLS,R4			;���]�ݒ�s�͈�LINK-PLS
;	MOV.L	@R4,R2					;
;
