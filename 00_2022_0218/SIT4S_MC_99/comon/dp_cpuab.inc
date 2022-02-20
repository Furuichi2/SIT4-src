;	*******************************************************************
;	***								***
;	***								***
;	***		CPUA<=>CPUB					***
;	***								***
;	***								***
;	***								***
;	*******************************************************************
;
;	*******************************************
;	***					***
;	***	SH2��SH4�@���޼���		***
;	***					***
;	*******************************************
		.ORG	H'0000
_CPUB_START_COD		.SRES	2		;2013-12-11[mc]
;	*******************************************
;	***					***
;	***	SH2��SH4�@���޼���		***
;	***		(2010-12-08)		***
;	*******************************************
		.ORG	H'0040
_DP_COP_CB_LD_MONI_SIG		.SRES	2	;SH4-->SH2�֓n��
_SH4_ORG_DIR_REV		.SRES	2	;EC ���_���A����(2014-08-09)
_DP_DBG_CPUAB_DRV_START		.SRES	2	;201500408(2015-03-31):�^�]TEST�p[]�o�׎�����۸��ё����͂���

;	--- 2015-07-14[���޲��� WDT] ----
_WDT_A_TO_B_REQ		.SRES	2	;
_WDT_A_TO_B_ANS		.SRES	2	;
_WDT_B_TO_A_REQ		.SRES	2	;
_WDT_B_TO_A_ANS		.SRES	2	;
_CPUA_PLS_OUTF		.SRES	2	;
_CPUB_PLS_OUTF		.SRES	2	;

	.ALIGN	4			;2015-07-14�ǉ�
_HD_CMP_PLS_A1		.SRES	4	;0:00CC=0:0204
_HD_CMP_PLS_B1		.SRES	4	;0:00D0=0:0208

;	*******************************************
;	***					***
;	***	SH2��SH4�@���޼���		***
;	***					***
;	*******************************************
		.ORG	H'0080

	.ALIGN	4			;
_SH4_GPOINT_LNG		.SRES	4	;����������CPU-B�ɋ�����CPU-B�͂���ɂ��킹��(�A����)
_SH2_GPOINT_LNG		.SRES	4	;����������CPU-B�ɋ�����CPU-B�͂���ɂ��킹��(�A����)
_SH4_GPOINT_LNGDSP	.SRES	4	;�\���p2004-12-20
_SH2_GPOINT_LNGDSP	.SRES	4	;�\���p
_SH4_GPOINT_SPDDSP	.SRES	4	;�\���p2004-12-20
_SH2_GPOINT_SPDDSP	.SRES	4	;�\���p

;	----- 2013-06-19----------
_SH4toSH2_TEPSIG	.SRES	2	;EE
_SH2toSH4_TEPSIG	.SRES	2	;F0





;--------------- �ǉ�[[[[2013-12-02 MC???]]]
_DPPVP_KAJLIV_LFT		.SRES	2		;//�׏d���iTON�j(1word)
_DPPVP_KAJLIV_TTL		.SRES	2		;//�׏d���iTON�j(1word)
_DPPVP_KAJLIV_RIH		.SRES	2		;//�׏d���iTON�j(1word)
_DPPVP_ARA1_KAJ_R		.SRES	2		;OPTION ��ԍő�׏d
_DPPVP_ARA1_KAJ_L		.SRES	2		;OPTION ��ԍő�׏d
_DPPVP_ARA1_KAJ_T		.SRES	2		;OPTION ��ԍő�׏dTOTAL�̂ݎg�p
_DPPVP_ARA1_KAJ_T2		.SRES	2		;OPTION ��ԍő�׏dTOTAL�̂ݎg�p


;	======= 2004-03-08 origin �ǉ�(��d��H�΍�) ===========
;;;;;;;;;[[[��2013-12-02]]]		.ORG	H'3B00
	.ALIGN	4			;
_SH4_CNT_REST_PLS	.SRES	4	;�A���̐ؑ֎��c��p���X
_SH4_LNGH_ADD_SR	.SRES	4	;���S��s��,��s�� �N�����ړ���
_SH4_REST_PLS_SR	.SRES	4	;���S��s��,��s�� �N�����c��ٽ
_SH4_REST_PLS_RL	.SRES	4	;���S��s��,��s�� REAL-TIME�c��ٽ
_SH4_BAS_FRQ_SV		.SRES	4	;�ް����g���ݒ�
_SH4_TOP_FRQ_SV		.SRES	4	;TOP���g���ݒ�
_SH4_NOW_FRQ_PV		.SRES	4	;TOP���g������
_SH4_PLSI_ACCS		.SRES	2	;�������x
_SH4_PLSI_LATE		.SRES	2	;24
_SH4_LOT_CNT_A		.SRES	2	;��L���ް��������ݎ��̉�]���b�g��
_SH4_LOT_STEP_A		.SRES	2	;��L���ް��������ݎ��̽ï�ߐ�
_SH4_REST_SR_HF		.SRES	2	;���޼����׸� SH4=>SH2 ��������!�N�����ړ���
_SH4_REST_RL_HF		.SRES	2	;���޼����׸� SH4=>SH2 ��������!�c����ٽ
_SH4_CNT_REST_HF	.SRES	2	;�A���̐؂�ւ����c����ٽ��������!�׸�

	.ALIGN	4			;
_SH2_CNT_REST_PLS	.SRES	4	;
_SH2_LNGH_ADD_SR	.SRES	4	;���S��s��,��s�� �N�����ړ���
_SH2_REST_PLS_SR	.SRES	4	;���S��s��,��s�� �N�����c��ٽ
_SH2_REST_PLS_RL	.SRES	4	;���S��s��,��s�� REAL-TIME�c��ٽ
_SH2_BAS_FRQ_SV		.SRES	4	;�ް����g���ݒ�
_SH2_TOP_FRQ_SV		.SRES	4	;TOP���g���ݒ�
_SH2_NOW_FRQ_PV		.SRES	4	;TOP���g������
_SH2_PLSI_ACCS		.SRES	2	;�������x
_SH2_PLSI_LATE		.SRES	2	;24
_SH2_LOT_CNT_A		.SRES	2	;��L���ް��������ݎ��̉�]���b�g��
_SH2_LOT_STEP_A		.SRES	2	;��L���ް��������ݎ��̽ï�ߐ�
_SH2_REST_SR_HF		.SRES	2	;���޼����׸� SH2=>SH4 ��������!�N�����ړ���
_SH2_REST_RL_HF		.SRES	2	;���޼����׸� SH2=>SH4 ��������!�c����ٽ
_SH2_CNT_REST_HF	.SRES	2	;(���g�p�@�ر�̂�)



;	======= �A���̓�����񃂃j�^�p ====
	.ALIGN	4			;
_SH4_STEP1_SV_PLS	.SRES	4	;
_SH4_STEP2_SV_PLS	.SRES	4	;
_SH4_STEP3_SV_PLS	.SRES	4	;
_SH4_STEP4_SV_PLS	.SRES	4	;
_SH4_STEP5_SV_PLS	.SRES	4	;
_SH4_STEP1_PV_PLS	.SRES	4	;
_SH4_STEP2_PV_PLS	.SRES	4	;
_SH4_STEP3_PV_PLS	.SRES	4	;
_SH4_STEP4_PV_PLS	.SRES	4	;
_SH4_STEP5_PV_PLS	.SRES	4	;
_SH4_STEP1_REST_P	.SRES	4	;
_SH4_STEP2_REST_P	.SRES	4	;
_SH4_STEP3_REST_P	.SRES	4	;
_SH4_STEP4_REST_P	.SRES	4	;
_SH4_STEP5_REST_P	.SRES	4	;
_SH4_STEP1_FRQ		.SRES	2	;
_SH4_STEP2_FRQ		.SRES	2	;
_SH4_STEP3_FRQ		.SRES	2	;
_SH4_STEP4_FRQ		.SRES	2	;
_SH4_STEP5_FRQ		.SRES	2	;
_SH4_STEP1_TIM		.SRES	2	;
_SH4_STEP2_TIM		.SRES	2	;
_SH4_STEP3_TIM		.SRES	2	;
_SH4_STEP4_TIM		.SRES	2	;
_SH4_STEP5_TIM		.SRES	2	;
	.ALIGN	4			;
_SH4_TOTAL_PLS		.SRES	4	;
_SH4_ADD_PLS		.SRES	4	;

_SH4_STEP_SV_PLS	.SRES	4	;
_SH4_STEP_PV_PLS	.SRES	4	;
_SH4_STEP_REST_P	.SRES	4	;
_SH4_STEP_FRQ		.SRES	2	;
_SH4_STEP_TIM		.SRES	2	;
_SH4_NOW_STEP		.SRES	2	;

	.ALIGN	4			;
_SH2_STEP1_SV_PLS	.SRES	4	;
_SH2_STEP2_SV_PLS	.SRES	4	;
_SH2_STEP3_SV_PLS	.SRES	4	;
_SH2_STEP4_SV_PLS	.SRES	4	;
_SH2_STEP5_SV_PLS	.SRES	4	;
_SH2_STEP1_PV_PLS	.SRES	4	;
_SH2_STEP2_PV_PLS	.SRES	4	;
_SH2_STEP3_PV_PLS	.SRES	4	;
_SH2_STEP4_PV_PLS	.SRES	4	;
_SH2_STEP5_PV_PLS	.SRES	4	;
_SH2_STEP1_REST_P	.SRES	4	;
_SH2_STEP2_REST_P	.SRES	4	;
_SH2_STEP3_REST_P	.SRES	4	;
_SH2_STEP4_REST_P	.SRES	4	;
_SH2_STEP5_REST_P	.SRES	4	;
_SH2_STEP1_FRQ		.SRES	2	;
_SH2_STEP2_FRQ		.SRES	2	;
_SH2_STEP3_FRQ		.SRES	2	;
_SH2_STEP4_FRQ		.SRES	2	;
_SH2_STEP5_FRQ		.SRES	2	;
_SH2_STEP1_TIM		.SRES	2	;
_SH2_STEP2_TIM		.SRES	2	;
_SH2_STEP3_TIM		.SRES	2	;
_SH2_STEP4_TIM		.SRES	2	;
_SH2_STEP5_TIM		.SRES	2	;
	.ALIGN	4			;

_SH2_TOTAL_PLS		.SRES	4	;
_SH2_ADD_PLS		.SRES	4	;

_SH2_STEP_SV_PLS	.SRES	4	;
_SH2_STEP_PV_PLS	.SRES	4	;
_SH2_STEP_REST_P	.SRES	4	;
_SH2_STEP_FRQ		.SRES	2	;
_SH2_STEP_TIM		.SRES	2	;
_SH2_NOW_STEP		.SRES	2	;

;	============== 20060919 DBG=====================
	.ALIGN	4			;
_SH_POSCTL_SV_SPD	.SRES	4*2	;[+0:SH4 +4:SH2]
_SH_POSCTL_RL_SPD	.SRES	4*2	;[+0:SH4 +4:SH2]
_SH_POSCTL_ACC		.SRES	4*2	;
_SH_POSCTL_OFS		.SRES	4*2	;
_SH_POSCTL_SV_ABSPLS	.SRES	8*2	;
_SH_POSCTL_RL_ABSPLS	.SRES	8*2	;
_SH_POSCTL_PV_ABSPLS	.SRES	8*2	;
_SH_POSCTL_REST_PLS	.SRES	4*2	;
_SH_POSCTL_CAL_REST	.SRES	4*2	;���Z(SV-PV)
_SH_POSCTL_HENSA	.SRES	4*2	;���Z(SV-PV)
_SH_POSCTL_LSIFREQ	.SRES	4*2	;LSI

;	===========  20070302	===============
_SH_SQ200_IN		.SRES	2*2	;
_SH_CNTSTOP_FLG		.SRES	2*2	;
_SH_OUTPLS_DELT		.SRES	2*2	;

;	*******************************************
;	***					***
;	***	SH2��SH4�@���޼���		***
;	***					***
;	*******************************************
;;;;;;;;;[[[��2013-12-02]]]		.ORG	H'3F00
_PVX_RNA_INDAT		.SRES	4	;��	SH4-->SH2 ��
_PVX_RNA_POSD1		.SRES	4	;�ϊ�	SH4-->SH2 �ɐ��E�̾�ĕ�
_PVX_RNA_POSD2		.SRES	4	;�ϊ�	SH4-->SH2 0.5um->1mm+���_
_PVX_RNA_POSDT		.SRES	4	;����p
_PVX_RNA_DIGDT		.SRES	4	;�p�x	360.0�x���x RNA�ݻ���狁�܂�p�x
_PVX_SH4_SFTY_IN	.SRES	2+2	;���S���u(2byte)
_PVX_RNA_PLS_P		.SRES	4	;RNA�ݻ���狁�܂�̾����ٽP
;	-------- 2015-07-14 �ύX �̈�ς��Ȃ�---------
;;_EMG_SH4_TO_SH2		.SRES	2+2	;
;;_EMG_SH2_TO_SH4		.SRES	2+2	;
_EMG_SH4_TO_SH2		.SRES	2	;
_EXQ_SH4_TO_SH2		.SRES	2	;2015-07-14
_EMG_SH2_TO_SH4		.SRES	2	;
_EXQ_SH2_TO_SH4		.SRES	2	;2015-07-14


_PVX_SH4_OUTPLS		.SRES	4*2	;8BYTE
_SH4_STEP_NO		.SRES	4	;�H����d��H�����p
_SH2_STEP_NO		.SRES	4	;�H����d��H�����p
_SH4_POS_STS1		.SRES	2	;��L�M�� SH4==> WRITE SH2 ==>BIT7 CLR
_SH2_POS_STS1		.SRES	2	;��L�M�� SH2==> WRITE SH4 ==>BIT7 CLR
_SH4_CMP_STS1		.SRES	2	;(��d���ُ�M�� 203���l      ��)
_SH2_CMP_STS1		.SRES	2	;(��d���ُ�M�� 273���l      ��)
_SH4_CMP_STS2		.SRES	2	;(��d���ُ�M�� BIT0�ʒu���� ��)
_SH2_CMP_STS2		.SRES	2	;(��d���ُ�M�� BIT0�ʒu���� ��)

;	====================================
_SH4_HD_CTRL_REDY	.SRES	2	;���������ɂ�����
_SH2_HD_CTRL_REDY	.SRES	2	;���������ɂ�����
_SH4_HD_CTRL_BUSY	.SRES	2	;�����������ɂ�����
_SH2_HD_CTRL_BUSY	.SRES	2	;�����������ɂ�����
_SH4_HD_POS_START	.SRES	2	;�N��������
_SH2_HD_POS_START	.SRES	2	;�N��������
_SH4_HD_SFTY_AUTO	.SRES	2	;1:AUTO���܂߂Ē�~����/���S��H��,�A������
_SH2_HD_SFTY_AUTO	.SRES	2	;1:AUTO���܂߂Ē�~����/���S��H��,�A������
_SH4_HD_NEAR_ZERO	.SRES	2	;Ʊ��ۏ������s������(�g�p�ς�)
_SH2_HD_NEAR_ZERO	.SRES	2	;Ʊ��ۏ������s������(�g�p�ς�)
_SH4_HD_CNT_STOP	.SRES	2	;�A����~(�g�p�ς�)
_SH2_HD_CNT_STOP	.SRES	2	;�A����~(�g�p�ς�)
_SH4_HD_STEP_END	.SRES	2	;�ʒu���ߊ����Ƃ�����(�g�p�ς�)
_SH2_HD_STEP_END	.SRES	2	;�ʒu���ߊ����Ƃ�����(�g�p�ς�)
_SH4_HD_CNT_CNT		.SRES	2	;�A����~���Ȃ��Ŏ��ւ�����
_SH2_HD_CNT_CNT		.SRES	2	;�A����~���Ȃ��Ŏ��ւ�����

;	===== 2002-09-12 SAITO =====
;	SELF CHECK HAND SHAKE FLG
_CPUA_SELF_HAND_FLG	.SRES	2	; CPUA�̏���׸�
_CPUB_SELF_HAND_FLG	.SRES	2	; CPUB�̏���׸�

;	===================================
;	===	�e���ނ̽ð���쐬�p	===
;	===================================
;	�^�]�J�n
;	�P�H���J�n
;	�ŏI�H���J�n
;	�I��/
;	==== 2004-03-01 ������ڑ���p���� =====
_CPU_CTRL_CLK		.SRES	2	;(������ڑ�����ѽ����)

_CPUA_IRQ_ERR_INT_CNT1	.SRES	2	;[IRQ-ERR]
_CPUA_IRQ_ERR_INT_CNT2	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT3	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT4	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT5	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT6	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT7	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT8	.SRES	2	;
_CPUA_IRQ_ERR_INT_CNT9	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT1	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT2	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT3	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT4	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT5	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT6	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT7	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT8	.SRES	2	;
_CPUB_IRQ_ERR_INT_CNT9	.SRES	2	;

;	=========== 2006-04-10 =========
_CPUA_SELF2_STR		.SRES	2	;
_CPUA_SELF2_END		.SRES	2	;
_CPUA_SELF2_CD1		.SRES	2	;
_CPUA_SELF2_CD2		.SRES	2	;
_CPUA_SELF2_CD3		.SRES	2	;
_CPUA_SELF2_CD4		.SRES	2	;

_CPUB_SELF2_STR		.SRES	2	;
_CPUB_SELF2_END		.SRES	2	;
_CPUB_SELF2_CD1		.SRES	2	;
_CPUB_SELF2_CD2		.SRES	2	;
_CPUB_SELF2_CD3		.SRES	2	;
_CPUB_SELF2_CD4		.SRES	2	;

;	**********************COP2�Ή�*************
	.ALIGN	4			;
_CPUA_OP_PG1_PLS	.SRES	4	;
_CPUA_OP_OUT1_PLS	.SRES	2	;
_PVOP2_WAIT_CODA	.SRES	2	;OP->CPUA
_PVOP2_WAIT_CODB	.SRES	2	;OP->CPUB
_SVOP2_WAIT_ANSA	.SRES	2	;CPUA->OP
_SVOP2_WAIT_ANSB	.SRES	2	;CPUB->OP

;	--------- 2007-05-30 ----------
_PVOP2_STEP1_CODA	.SRES	2	;OP->CPUA
_PVOP2_STEP1_CODB	.SRES	2	;OP->CPUB
_SVOP2_STEP1_ANSA	.SRES	2	;CPUA->OP
_SVOP2_STEP1_ANSB	.SRES	2	;CPUB->OP
_PVOP2_STEP2_CODA	.SRES	2	;OP->CPUA
_PVOP2_STEP2_CODB	.SRES	2	;OP->CPUB
_SVOP2_STEP2_ANSA	.SRES	2	;CPUA->OP
_SVOP2_STEP2_ANSB	.SRES	2	;CPUB->OP

_CPUB_STEP_INFO1	.SRES	2	;[3FC2]

;	--------- 2008-03-25 ----------
_HD_SYNCHOS_LT_FLG	.SRES	2	;
	.ALIGN	4			;
_HD_SYNCHOS_LT_OBJ	.SRES	4*2



;	=============== 2014-05-30===============
_PVPAB_SH2_AD_DATA	.SRES	2
_PVPAB_SH2_AD_DAT2	.SRES	2	;
_PVPAB_SH2_AD_DAT3	.SRES	2	;
_PVPAB_SH2_AD_DAT4	.SRES	2	;
_PVPAB_DBG_KYUIN1	.SRES	2	;(��:���ޯ��p����̫��)
_PVPAB_DBG_KYUIN2	.SRES	2	;(���v:���ޯ��p����̫��)
_PVPAB_DBG_KYUIN3	.SRES	2	;(�E:���ޯ��p����̫��)


;	---------- 2014-02-05-------------
;	CPUB����ɍŏ��׏d������ݸ�
;	CPUA�͍X�V�y�ѕK�v�����ݸނ�CPUB�ɋ�����
;	H'336
;
;	------------- �S���(����۰��,۱�Яėp)---------------
_ATOB_KJYUALL_SMPCLR	.SRES	2	;CPUA=>CPUB 1: CPUB=0CLR CPUB��0�ر����
_ATOB_KJYUALL_SMPSTART	.SRES	2	;CPUA= 0->1 1->0         CPUB�͎Q�Ƃ̂�

;	------------- ��� ����ޗp---------------
_ATOB_KJYUTRD_SMPCLR	.SRES	2	;CPUA=>CPUB 1: CPUB=0CLR CPUB��0�ر����
_ATOB_KJYUTRD_SMPSTART	.SRES	2	;CPUA= 0->1 1->0         CPUB�͎Q�Ƃ̂�

;	----------------- ���׏d�����t��(COP1Z)--------------
	.ALIGN	4			;
_PVPAB_KAJLIV_LFT	.SRES	4
_PVPAB_KAJLIV_RIH	.SRES	4
_PVPAB_KAJLIV_TTL	.SRES	4

;	-----------------��ԍő�׏d(COP1Z)�׏d�␳�p---------------
_PVPAB_ARA1_KAJ_L	.SRES	4
_PVPAB_ARA1_KAJ_R	.SRES	4
_PVPAB_ARA1_KAJ_T	.SRES	4

;	--------�S���(����۰��,��Яėp)-------------------
_BTOA_LFT_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
_BTOA_LFT_MIN		.SRES	4	;
_BTOA_LFT_HAB		.SRES	4	;

_BTOA_RIH_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
_BTOA_RIH_MIN		.SRES	4	;
_BTOA_RIH_HAB		.SRES	4	;

_BTOA_TTL_MAX		.SRES	4	;(����͎g�p���Ȃ��\��,�׏d�v������Ă��邩��)
_BTOA_TTL_MIN		.SRES	4	;
_BTOA_TTL_HAB		.SRES	4	;

;	--------   �g�����h�p-------------------
_BTOA_LFT_TRDMAX	.SRES	4	;()
_BTOA_LFT_TRDMIN	.SRES	4	;
_BTOA_LFT_TRDHAB	.SRES	4	;

_BTOA_RIH_TRDMAX	.SRES	4	;
_BTOA_RIH_TRDMIN	.SRES	4	;
_BTOA_RIH_TRDHAB	.SRES	4	;

_BTOA_TTL_TRDMAX	.SRES	4	;
_BTOA_TTL_TRDMIN	.SRES	4	;
_BTOA_TTL_TRDHAB	.SRES	4	;0039C


;	-------------���ɒǉ�----------
	.ALIGN	2			;�ײ�ގ����ҋ@�w�� 2014-08-30(340.12)
_SH4_HD_HLDSTOP1	.SRES	2	;1:�ײ�ޑҋ@�w�߂Œ�~�ɂ��� 1��0:�ċN������ /exq,emg �ʏ펞��0
_SH2_HD_HLDSTOP1	.SRES	2	;1:�ײ�ޑҋ@�w�߂Œ�~�ɂ��� 1��0:�ċN������ /exq,emg �ʏ펞��0

_SH4_HD_HLDSTOP2	.SRES	2	;2014-09-11 �ײ�ޑҋ@�̉������M��
_SH2_HD_HLDSTOP2	.SRES	2	;

					;2014-09-13
_SH4_VLV_SIG		.SRES	2	;209.6(��ٽ����),206.0(ACT)
_SH2_VLV_SIG		.SRES	2	;209.6(��ٽ����),206.0(ACT)

;	-------- 2015-03-15 ���
_SH2_OBJ_ENC360		.SRES	2	;��� 2015-03-15
_SH2_PV_OUT_SPD_PER	.SRES	2	;
_SH2_PV_ENC_SPD_PER	.SRES	2	;

;	------- 2015-03-15 �ӂ肱���Z------
_SH4_DNM_CALC_INFO	.SRES	2	;SH4 TO SH2
_SH2_DNM_CALC_INFO	.SRES	2	;SH2 TO SH4

;	------- 2016-04-16-----------------
_CPUA_SV_STEP		.SRES	2	;
_CPUB_SV_STEP		.SRES	2	;
_CPUA_DNM_DIR_SET	.SRES	2	;
_CPUA_DNM_DIR_NOW	.SRES	2	;
_CPUB_DNM_DIR_SET	.SRES	2	;
_CPUB_DNM_DIR_NOW	.SRES	2	;

;_PROC_CMPERR_CHG2016
;------2016-10-31---------
_CPUA_LOT_CHK_FLG	.SRES	2	;2016-07-18CHECK
_CPUB_LOT_CHK_FLG	.SRES	2	;2016-07-18CHECK
_CPUA_LOT_CNT_FLG	.SRES	2	;
_CPUB_LOT_CNT_FLG	.SRES	2	;
_CPUA_CONT_MOD_CNT_PV	.SRES	2	;
_CPUB_CONT_MOD_CNT_PV	.SRES	2	;
_CPUB_DBG_MONI_STP	.SRES	2	;2016-08-12
_CPUB_DBG_MONI_CNT	.SRES	2	;2016-08-22
;	----------------------------------------

;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		2013-12-02MC�ǉ�	***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ORG	H'1000			;
	.ALIGN	4			;
_SEQAB_DP_TOP	.SRES	1600		;MAX 2K

;	*******************************************
;	***					***
;	***	CPUB=>CPUA			***
;	***	ROM���:KIND=1			***
;	***					***
;	*******************************************
	.ORG	H'1800			;
	.ALIGN	4			;
_CPUBTOA_DAT1_REQADR	.SRES	4	;OFS WORD
_CPUBTOA_DAT1_REQKND	.SRES	2	;���[BIT15=1:END <-//-> BIT7~BIT0 KIND]
_CPUBTOA_DAT1_REQCNT	.SRES	2	;WORD��
_CPUBTOA_DAT1_REQCOD	.SRES	2	;WR
_CPUBTOA_DAT1_ACKCOD	.SRES	2	;ACK
	.ALIGN	4			;
_CPUBTOA_DAT1_DATTOP	.SRES	2*128	;256BYTE(128W)


;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ORG	H'2000			;
	.ALIGN	4			;



