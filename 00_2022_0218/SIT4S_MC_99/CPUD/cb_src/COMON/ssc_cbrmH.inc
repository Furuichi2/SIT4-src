//	***********************************
//	***				***
//	***	SH4:4Kbyte		***
//	***				***
//	***				***
//	***********************************
//	������
//	***********************************
//	***	�V�[�P���X		***
//	***********************************
	U2b	SQ_CBWK_TOP[70];		//

//	***************************
//	***	�n�[�h���o�� 	***
//	***************************
	U2b	di1_cb_ctl1[4];//+0:DI(�g�p)+1�@+2()�@+3(��) �^�]�t(200.*)
	U2b	di2_cb_ctl2[4];//+0:DI(�g�p)+1�@+2()�@+3(��) LSA,WT1~3(201.*)
	U2b	di3_cb_inp1;//+0:EMG1,EMG2 BIT1,BIT0
	U2b	di4_cb_inp2;//+0:BIT10,BIT11,BIT12,BIT13(202.*)
	U2b	dq1_cb_out1;//+0:����o��(203)

	U2b	di3_cb_inp1_dt;//����Ɏg�p����̂�_dt(���葤�̎Ռ���)

	U2b	di1_cb_ctl1_dt;// ������-�
	U2b	di1_cb_ctl1_on;// on����
	U2b	di1_cb_ctl1_of;// of����

	U2b	di2_cb_ctl2_dt;// 
	U2b	di2_cb_ctl2_on;// on����
	U2b	di2_cb_ctl2_of;// of����
	
	U2b	CNT_STOP_CMD;//�A����~,ۯĶ���,�ݒ�ُ�

//	***********************************
//	***	C/B�@���͂̉��H����	***
//	***	DI_LOAD			***
//	***********************************
	U2b	BTTN_FLG;	//BIT0:������- BIT1:�Ў�ON�@BIT2:����ON
	U2b	SFTY_IN_DAT;	//���S���u���� BIT0:�O���S�@BIT1:����S���u
				//[CPUA+CPUB]+���S���u�L��/�����̂�FACT,RACT
	U2b	SFTY_CTL_IN_DAT;

//	***************************
//	***	�ُ�֌W	***
//	***************************
	U2b	pass_err_flg1;//�ُ�ٰ��
	U2b	pass_err_flg2;//����ٰ��
	U2b	emg_lev_flg;//�ُ���(���ް�)
	U2b	emg_err_flg;//�ُ�ׯ�
	U2b	exq_lev_flg;//�}��~���(���ް�)
	U2b	exq_err_flg;//exqׯ�
	U2b	INPUT_MODE_SW;
	U2b	ELSE_ERR_FLG1;//����~(�ُ��1�@�����0)
	U2b	ELSE_ERR_FLG2;//BIT0:Ӱ��SW�ύX
	U2b	MOV_ERR_FLG1;//BIT0~BIT8

	U2b	CMP_ERR_TIM1;//��d��H�ُ�
	U2b	MOV_DATA_ERR_FLG1;//���]�����ް��ُ�
	U2b	CMP_STEP_ERR_TIM1;//�H����d��H

	U2b	ORG_ELSE_NOMAL_FLG1;//���_����ȊO����֎~ 0:�ُ� 1:OK
	U2b	ORG_DND_NOMAL_FLG1;//0:�ُ� 1:����(�i�搡���\)

//	***************************
//	***	���Z�b�g�֌W	***
//	***************************
	U2b	reset_flg;//
	U2b	reset_dly_tim;//20msec
	U2b	ORG_PRESET_TIM;

//	***********************************
//	***	�į��ݸ����		***
//	***********************************
	U4b	STOPPING_VLVOFF_POS[2];//��~�����J�n���_�̈ʒu
	U4b	STOPPING_STOP_POS[2];//��~��������ʒu
	U2b	STOPPING_TIM_FLG;//�į��ݸ���ϗp�׸� BIT0����J�n BIT6:��~��
	U2b	STOPPING_STOP_TIM;//��~�𑪒肷��^�C�}
	U2b	STOPPING_TIM_PV1;//�į��ݸ����
	U2b	STOPPING_TIM_PV2;//�į��ݸ����


//	***********************************
//	***	ۯĶ�������		***
//	***********************************
//	�ŏI�H���Ŋ���165�x����(��]�Ȃ�PV��165 ���]�Ȃ�165��PV)�Ȃ�
//	ۯĶ����͘A���E����E��߼�݂ŃJ�E���g
	U2b	LOT_CNT_FLG;//�s��=1��0 �ŏI�H���ŏ���������=1()
	U2b	LOT_CNT_TO_MOD;
	U2b	LOT_CHK_FLG;
//	***********************************
//	***	C/B�@RDY���̏���	***
//	***********************************
	U2b	DRV_ACT_FLG;	//�^�]�����׸� BIT0:�^�]��
	U2b	SAME_TIM;	//�^�]�����t
	U2b	SET_UP_TIM;	//��ı���

//	***************************
//	***	C/BӰ�ޏ��	***
//	***************************
	U2b	INP_MODE;	//���́@ؾ�ď����Ɏg�p INP_MODE-->MODE_SEL
	U2b	MODE_SEL;	//ؾ�Ď��Ɍ���
				//bit0:�� bit1���� bit2:����(sgl,opt) bit3:�A�� bit4:opt bit5:�i�� bit6:�ҋ@�_���A
				//�܂�bit0~bit7�̂����ꂩ��on����@�I�𖢂͐�(bit0)
				//bit8~bit15:�ڍ׏��
				//opt�Ȃ�bit8:��H�� bit9:�A�������@bit10=�A����
				//�����Ȃ�bit8:���� 
				//�A���Ȃ�bit8 time,bit9 cnt
				//
	U2b	MRTION_SEL;	//��]/���]/������/������(�N�����܂���RESET��)
				//
	U2b	IN_RDY_FLG;	//������������(ANTI�Ɠ�������)
	U2b	STOP_LATCH;	//BIT0:�į�ߖt
	U2b	STOP_LATCH_B;	//BIT0:�į�ߖt

	U2b	UP_HOLD_STEP;	//�㏸ΰ��ނ��Ď����J�n����ï��
	U2b	UP_HOLD_STEP1;	//
	U2b	UP_HOLD_STEP2;	//
	U2b	UP_HOLD_DIG;	//0.1�x(165.0):Ӱ����ݺ��ފp�x�Ŕ�r
	U2b	UP_HOLD_FLG;	//BIT0=1 �㏸ΰ��ޏ��(�����\���):Ӱ���Ӱ�ނł��̐M����ON/OFF����
				//BIT1=1 �㏸�����w��
				//
	U2b	CAM_CTL_STEP;//�сE�㏸ΰ��ޗp
	U2b	SW_DEV_MASK_FLG;//BIT1=BIT0=0 ���S���u����  BIT1=BIT0=1 ���S���u�L��
	U2b	FR_CYL_MASK_FLG;//�㏸������"1"
	U2b	END_CMD_LATCH;

//	***********************************
//	***	1msecҲ݂ō쐬		***
//	***********************************
	S4b	LINK_NOWROT_NUM_ZR		;//��]��
	S4b	LINK_NOWROT_NUMPLS_ZR[2];	//RL_OBJ_ABSPLS/nm = ��]����������ٽ
	S4b	LINK_NOWROT_OFSPLS;	//�]��p�x
	S4b	LINK_NOWROT_OFSPLS_P;	//�]��p�x�́{�ް�

	S4b	INCENC_LINK_NOWROT_NUM_ZR;//��]��
	S4b	INCENC_LINK_NOWROT_NUMPLS_ZR[2];//RL_OBJ_ABSPLS/nm = ��]����������ٽ
	S4b	INCENC_LINK_NOWROT_OFSPLS;	//�]��p�x
	S4b	INC_LINK_NOWROT_OFSPLS_P;	//�]��p�x +�ް�
	S2b	M_LINK_AREASIG;	//BIT0:�ҋ@�_�͈�

//	***********************************	//
//	***				***	//
//	***	�ҋ@�ݒ�͈�		***	//
//	***				***	//
//	***********************************	//
	S2b	WSVX_CLNK_UP_POS;	//��ݸ�ݒ�
	S2b	WSVX_CLNK_UP_POS_UP;	//��ݸ�ݒ�
	S2b	WSVX_CLNK_UP_POS_DN;	//��ݸ�ݒ�
	S2b	SETX_LINK_UP_POS_UP;	//��ݸ�ݒ�(�͈͔�r)
	S2b	SETX_LINK_UP_POS_DN;	//��ݸ�ݒ�(�͈͔�r)


//	***********************************
//	***	1msecҲ݂ō쐬		***
//	***********************************
	S4b	RNA_LINK_NOWROT_OFSPLS_P;	//�]��p�x +�ް�
	S4b	INC_ENC_MM_POS;//

//	***********************************
//	***	ؾ�ĉ������Ɍ���	***
//	***	�ȍ~			***
//	***********************************
	S4b	RESET_ROTNUM_ZR;//���̎���ؾ�Ă����肵��
	S4b	RESET_ROTNUMPLS_ZR[2];//���̎���ؾ�Ă����肵��

//	***********************************
//	***	�ʒu/�p�x/����		***
//	***********************************
//	***********************************
//	***	�n�[�h����360�ݺ��� 	***
//	***********************************
	U2b	ENC360_INOLD;//�ޯĉ������������{���̐�
	U2b	ENC360_INDT;//�� BCD
	U2b	ENC360_HEX;//HEX data
	U2b	CTL_ENC360;//360.0�x
	U2b	RNA_ENC360;//0~360.0
	U2b	INC_ENC360;//0~360.0
	U2b	DISP_ENC360;//0~360.0
	U2b	OBJ_ENC360;//0~360.0

//	***********************************
//	***	�ʒu���߉��Z		***
//	***********************************
//	***********************************
//	***	�ʒu���߉��Z		***
//	***********************************
	S2b	SETX_POS_MOD_FLG1;	//BIT0:��]-�A��//BIT1:��]-����//BIT2:�ǂ����Œ�~����^�]���ۂ�
	S2b	SETX_POS_CTL_MATH;	
	S2b	SETX_POS_STEP_MAX;	//�ݒ�+1 2~11

	S2b	CPOS_MOD_FLG1	;//BIT0:��]-�A��//BIT1:��]-����//BIT2:�ǂ����Œ�~����^�]���ۂ�
	S2b	CPOS_CTL_MATH;	
	S2b	CPOS_STEP_MAX;	//�ݒ�

//	***********************************
//	***				***
//	***	�ʒu����		***
//	***				***
//	***********************************
	S4b	LINK_RL_OFSET_PLS1[2];//�ʒu�ް��ϊ�
	S4b	LINK_RL_OBJ_ABSPLS[2];//ر���іڕW��Έʒu(�ޯ�ׯ��Ȃ�)

//	***********************************
//	***				***
//	***	�ʒu����		***
//	***				***
//	***********************************
//	����:8byte data�͊����ŏ������邩��:����

//	==== I/F data
	S4b	LINK_SV_OBJ_ABSPLS[2];//abs��~�ڕW�ʒu(�ݒ��ޯ�ׯ��Ȃ�)
	S4b	LINK_SV_OBJ_SPDPLS;//�ڕW���x
	U2b	POS_DRV_DIRECT;	//BIT0:DIR (BIT1:EQU)
					//�㎀�_���A�ł͕K�v(�ǂ�������͂��߂邩)
					//�i�搡���͕K�v
					//���H�E���H�ł��K�v-->�ï�߂ɑg�ݍ��܂��
	S2b	SV_POS_CTL_STEP;	//1msec �����̌������@����SV=

	S2b	POS_CTRL_SQ_STS;	//�ʒu���߽ð��

//	*********** 200usec �̏�������ON/FF *********
	S2b	INT_POS_CTL_STEP;	//��������H��1~11
	S2b	INT_DND_CTL_STEP;	//

	S2b	INT_POS_CTL_FLAG;	//BIT0=1:ACTIVE BIT1=1:

	S2b	INT_POS_STEP_FLG;	//�ï�߁A�i��苤��
	S2b	INT_DND_STEP_FLG;	//(�㎀�_���A�̍H���Ǘ�)
	S2b	INT_CYC_DRV_STS;	//BIT0:CYCLE�@END()
					//BIT6:�ʒu���ߊ���
	S2b	INT_CLS_CTL_FLG;	//BIT0=1 START �N�����ر
	S2b	INT_CLS_DYL_TIM;	//

	S2b	INT_DND_NEG_STEP;	//2003-01-27 _NEG_SPEC1 EQ _COMPILE_YES	;

//	===========================================
//	===		�����o���p���X�Z�o	===
//	===========================================
	S4b	LNGTH_ADD_DATA[2];//�����t��
	S4b	LNGTH_TOTAL_OUTPLS[2];//������ TOTAL=TOTAL+ADD ADD_DATA<=0
	S4b	POSLSI_CMP_DATA;//CMP_DATA=CMP_DATA+|ADD_DATA| (�����Ȃ�)
	S4b	POSLSI_DELT_POS;//�ω���
	S4b	INT_LINK_TOTAL_ABSPLS[2];
	S4b	LINK_PV_ABSPLS[2];//�ޯ�ׯ��␳��
	S4b	LINK_POS_OFFSET1[2];//�Ʊ���_����~�␳
	S4b	LINK_POS_OFFSET2[2];//

	S4b	OUTPLS_MOD;
	S4b	OUTPLS_DIV;
	
	S2b	POSLSI_DRIV_SHIN;//BIT0

	S4b	POSLSI_CHK_RESTPLS;
	
	S4b	POSLSI_OUTPUT_TOTAL_PLS[2];
	S4b	POSLSI_HENSA_LATCH[2];
	
	S2b	POSLSI_CHK_CNT;//UP CNT
	S2b	POSLSI_CHK_DLT;//�����t����
	S2b	POSLSI_CHK_STS;

//	*******************************************
//	***					***
//	***	2003-07-01			***
//	***	���x���o��			***
//	***					***
//	*******************************************

	S4b	ENCPLS_SPD_TOTAL;
	S4b	ENC_PLS_SPD;//+/- 1000,000HZ �ɐ����ς��Ƃ���0pls/s�ɂȂ�
	S4b	ABS_ENC_PLS_SPD;// 
	S2b	ENC_PLS_SPD_DIR;// ���� 0:"+", -1:"-"
	S2b	ENCPLS_DELT;//�����t
	S2b	ENCPLS_SPD_POINT;
	S2b	ENCPLS_POINT_SEL;//10msec
	S2b	ENCPLS_1000MSEC_LAT;//1000msec/10msec=100

	S4b	OUTPLS_SPD_TOTAL;
	S4b	OUT_PLS_SPD;//+/- 1000,000HZ �ɐ����ς��Ƃ���0pls/s�ɂȂ�
	S4b	ABS_OUT_PLS_SPD;// (MIN�@�\�L�� 1KHZ)
	S2b	OUT_PLS_SPD_DIR;// 
	S2b	OUTPLS_DELT;//�����t
	S2b	OUTPLS_SPD_POINT;
	S2b	OUTPLS_POINT_SEL;
	S2b	OUTPLS_1000MSEC_LAT;

	S2b	PV_ENC_SPD_PER;//0~110.00%
	S2b	PV_OUT_SPD_PER;//0~110.00%

	S2b	PVC_BRK_ENC_SPD;//0~110.00% MIN-LIMIT ��ڰ��ُ�Ɏg�p
	S2b	PVC_BRK_OUT_SPD;//0~110.00% MIN-LIMIT ��ڰ��ُ�Ɏg�p %MIN �@�\�L��

//	***********************************
//	***	�ʒu���߂k�r�h�J�E���^	***
//	***********************************
	S4b	POS_LSI_TOTAL_PLS[2];
	S4b	POS_LSI_ABSPLS[2];
	
	S4b	POS_LSI_OFFSET1[2];//��ٽ
	S4b	POS_LSI_OFFSET2[2];//�Ʊ/���_/���炭��␳
	S4b	POS_LSI_CTL_NOWPLS[2];//����
	S2b	POS_LSI_OLDCNT;

//	======= �ҋ@�_���A�m���ް� ====
	S4b	RNA_ABS_ORGWORK[2];//�ҋ@�_���o�pܰ�
	S4b	INC_ABS_ORGWORK[2];//�Ʊ���L�����̲ݸ����يp�x


//	***********************************
//	***	�Ʊ���ٌ��_		***
//	***********************************
	S4b	RNA_POS_OFFSET1;//�ޯ�����
	S4b	RNA_POS_OFFSET2;//���_�ݒ�
	S4b	RNA_ABS_POS;//��ٽ��ʍ���(��Έʒu)
	S4b	RNA_ABS_MEMORG;//�ő卂���L���ް����_�������F���_�����޲ʲ�


	S4b	RNA_STLORK;//�ݒ�
	S4b	PVX_RNA_STLORK;//����
	S4b	PVX_DAI_POS0;//� �޲ʲ�(�蓮�����O)
	S4b	PVX_DAI_POS1;//�\���l �޲ʲ�(�蓮������)
	S4b	RNA_ABS_MD_DT0;//
	S4b	RNA_ABS_MD_DT1;//
	S4b	RNA_CTL_POS0;//����ʒu(������l����) 2003-01-27 �ǉ�
	S4b	RNA_CTL_POS1;//����ʒu()
	S4b	PVX_DYHITO_POS;//�\��
	S4b	RNA_HOS_DELT;//�޲ʲĎ���-�޲ʲĐݒ� 2003-01-27

	S2b	DAI_HOSEI1_FLG;//�޲ʲĎ蓮����

//	***************************
//	***	���ݽ���o��	***
//	***************************
	U2b	CB_SEQ_SW_SEL024;//SEQ 24[�d�l�ݒ�]
	U2b	CB_SEQ_SW_SEL028;//SEQ 28[����אݒ�]
	U2b	CB_SEQ_SW_SEL029;//SEQ 29[����אݒ�]
	U2b	CB_SEQ_CB_COM340;
	U2b	CB_SEQ_CB_SEL341;
	U2b	CB_SEQ_CB_SEL342;
	U2b	CB_SEQ_CB_COM345;//20030709
	U2b	CB_SEQ_CB_COM346;//20030524
	U2b	CB_SEQ_CB_COM347;//200500117
	U2b	CB_SEQ_CB_COM348;//20060728 DEBUG
	U2b	CB_SEQ_CB_COM349;//20100820 
	U2b	CB_SEQ_CB_COM350;//20121005
	U2b	CB_SEQ_CB_COM351;//20121005 

	U2b	ERR_CHK_SW_SEL029;//SEQ 29

//	***************************
//	***	�J��		***
//	***************************
	U2b	CB_SEQ_CAM_SEL038;//��/�� 38.0~38.15
	U2b	CB_SEQ_CAM_SEL036;//��/�� 36.0~36.7+�펞
	U2b	CB_SEQ_CAM_SEL034;//��/�� 34.0~34.8+��ު�� 
	U2b	CAM_OUT_ENB1P;//�o��ENB 38.0~38.15+Ӱ�ޏ��� ۰�ض�
	U2b	CAM_OUT_ENB2P;//�o��ENB 36.0~36.7+�펞+Ӱ�� ̨���,������
	U2b	CAM_OUT_ENB3P;//�o��ENB 34.0~34.8+��ު��
	U2b	CAM_OUT_ENB3T;//�o��ENB 34.0~34.8+��ު��
	U2b	CAM_POS_STEP_END_FLG1;//�e�H����
	U2b	CAM_POS_STEP_END_FLG2;//�e�H����

//	===================================
//	===				===
//	===	�׏d�v�J������(CPUB)	===
//	===	2006-07-28		===
//	===================================
	S2b	SET1_KJSTR_STEP1;	//0,1~�H�� 
	S2b	SET1_KJSTR_DIG1;	//359.0
	S2b	SET1_KJEND_STEP1;	//0,1~�H��
	S2b	SET1_KJEND_DIG1;	//359.0
	S2b	KJ_AREA_SIG;//BIT4:AREA-ON BIT5:END
	S2b	KJ_AREA_BT0_OLD;//2013-06-19

//	***********************************
//	***	SH2 �׏d����\�t�g	***
//	***********************************
	S2b	COP_DIG_SIG_FLG;//�ǂ̕����ŉ��؂�����
	
	S2b	COP_CB_LD_MONI_SIG;//�׏d����p�M�� 2003-01-31

	U2b	WPAR_COP_CNTROT_ZDG1;//
	U2b	WPAR_COP_CNTROT_ZDG2;//
	U2b	WPAR_COP_CNTROT_SDG1;//
	U2b	WPAR_COP_CNTROT_SDG2;//

	U2b	WPAR_COP_REVRSE_ZDG1;//
	U2b	WPAR_COP_REVRSE_ZDG2;//
	U2b	WPAR_COP_REVRSE_SDG1;//
	U2b	WPAR_COP_REVRSE_SDG2;//

	U2b	WPAR_COP_ZDG1;//
	U2b	WPAR_COP_ZDG2;//
	U2b	WPAR_COP_SDG1;//
	U2b	WPAR_COP_SDG2;//

//2013-06-18 ���g�p	U2b	COP_ENC3600;
	U2b	COP_OLD_ENC3600;

//;	*******************************************
//;	***	�����ݒ葊���f�[�^		***
//;	*******************************************
	U4b	LINK_MAX_SPD_PLS;	//�ݸ����ٴݺ��ފ��Z�l�@pls/s
	U4b	SET1_UPAREA_POS1;	//�ҋ@�p�x(�p�x��ð��ق���)
	U4b	SETX_UPAREA_PLS;	//4;�ҋ@�_�ʒu(�ݸ�����)
	U4b	SETX_UPAREA_RNA;	//4;�ҋ@�_�ʒu�Ʊ�ʒu
	U2b	SETX_UPAREA_DIG;	//4;�ҋ@�_�ʒu�p�x
	U4b	POS_FRQ_SPDMAX;//500KHZ
	U4b	POS_LSI_SPDMAX;
	U4b	POS_LSI_SPDBAS;
	U2b	POS_LSI_SPDLAT;
	U2b	POS_LSI_ACCLT1;
	U2b	POS_LSI_ACCLT2;

	S4b	ORG_FIRST_OBJPLS;
	S4b	ORG_SECOND_OBJPLS;


//	===================================== //
	S4b	SETX_UPDN_CHK_UP_DIG	;//312.2�x(�㎀�_�p�x 0.1�x)
	S4b	SETX_UPDN_CHK_DN_DIG	;//180.0�x(�����_�p�x 180.0)
	S4b	SETX_UPDN_CHK_UP_PLS	;//312.2�x��������ٽ(�㎀�_�p�x)
	S4b	SETX_UPDN_CHK_DN_PLS	;//180.0�x��������ٽ(�����_�p�x)
	

	S2b	ORGIN_END_FLG1;	//�d�������̂P��ON:OFF�͂Ȃ�

//	***********************************
//	***	�ݒ�			***
//	***********************************
	S4b	LINK_OBJROT_NUM_ZR;//����ڕW�Ƃ��� ROTATION �ԍ� (���̋N�����p���Z����+1����)
	S4b	LINK_OBJROT_NUMPLS_ZR[2];//�� ROTATION�ԍ���������ٽ    8BYTE
	S4b	LINK_PV_ENC_ABSPLS[2];//PG�@��Έʒu

	S4b	LINK_POSS_PLS[2];//�J�n�ҋ@�_��ٽ ABS �N����
	S4b	LINK_POSE_PLS[2];//�ڕW�ҋ@�_��ٽ ABS �N����
	S4b	LINK_1ROT_PLS;	//1��]��ٽ(�ݒ�����)

	S4b	SDAT_WAIT_PVTIM;
	U4b	CPOS_UPAREA_PLS;	//�ҋ@�_ׯ�

	U4b	CLS_RNA_MOST_DOWN_POS;//�ٸ۰�ފJ�n��~�I���܂ł̍ŉ����_
	U4b	CLS_INC_MOST_DOWN_PLS;//�ٸ۰�ފJ�n��~�I���܂ł̍ŉ����_
	U2b	CYCL_START_CNT;

//	***********************************
//	***	C/B �ʒu���߲���̪��	***
//	***********************************
//	C/B ==> �ʒu����
	U2b	MNWR_POS_CMD;	//0000,0000,0000,0000  :��ٽ���o����~
				//BIT0:�N��
				//BIT1:������~
				//BIT2:�ҋ@�_��~�����ׯ�(�A���^�]�̒�~�{�^����)
				//

	U2b	STR_ENC3600_DIG;	//�^�]�J�n����360.0�p�x
	U2b	STR_ENC3600_DIG_LNG;	//

	U2b	DND_CALC_WORK;

//	***********************************
//	***				***
//	***	�ʒu����		***
//	***	�ޯ����			***
//	***********************************
	S4b	M_LINK_RL_OBJ_ABSPLS[2];//MAIN�p

//	===================================
//	===				===
//	===	2006-09-19		===
//	===	����ײ��		===
//	===				===
//	===================================
	S4b	POSCTL_SV_PLS[2];//�ݒ�ʒu
	S4b	POSCTL_RL_PLS[2];//ر���шʒu

	S4b	POSCTL_SET_SPD;//�ڕW���x(PLS/S)�ݒ�
	S4b	POSCTL_SV_SPD;//�ڕW���x(PLS/S)����ײ�ނ��܂�
	S4b	POSCTL_RL_SPD;//�������Z���A���^�C�����x(PLS/S)

	S4b	POSCTL_SV_UP_ACC;//�ڕW�����x((PLS/1000)/S/S)
	S4b	POSCTL_SV_DN_ACC;//�ڕW�����x((PLS/1000)/S/S)

	S4b	POSCTL_SV_OFS_SPD;//���N�� PLS/S

	S2b	POSCTL_STEP_CMD;//0:EMG��~(���x=0) 1:�N������� 2:(������~)
	S2b	POSCTL_STEP_FLG;//0(IDLE) 1:�N�� FF:END
	S2b	POSCTL_CALC_ERR;//BIT0(��~���Ȃ���Ԃł̋N��),BIT1(����)

//	--------- ���x��������ƈ������߂�--------
	S4b	SET_CLS_SPDBAS_PLS;//PLS/S
	S4b	SET_SPDBAS_PLS;//PLS/S
	S4b	SET_CLSINC_SPDBAS_PLS;//PLS/S

//	***********************************
//	***				***
//	***	���Z�̊ȗ����萔	***
//	***				***
//	***********************************
	//���Z�ȗ����̈׃V�X�p���ŉ��Z�r�����쐬���Ă���
	U4b	CALC_MEM_1REV_MUL_NROT;//1��]�p���X(8192)*�m��](32)=4byte
	U4b	CALC_MEM_1REV_ML_NROT_ML36;//1��]�p���X(8192)*�m��](32)*3600=4byte

//;	***************************************************
//;	***	�������Ұ��̈�	4/2BYTE�̈�		***
//;	***************************************************
	U4b	SET1_INCPLS_1REV		;//	2	;PG1��]����ٽ�I��
	U2b	SET1_RNADIR_SEL1		;//	2	;�Ʊ�ݻ�ɐ�
	U2b	SET1_INCDIR_SEL1		;//	2	;PG�ɐ�
	U2b	SET1_INCPLS_HOSN		;//	2	;PG�␳N�@Ӱ�N��
	U2b	SET1_INCPLS_HOSM		;//	2	;PG�␳M�@��ݸ�p�xM<�ݒ�0.1�x>
	U2b	SETX_INCPLS_HOSM		;//1�x
	U4b	SETY_INCPLS_HOSM1XX		;//1�x
	U4b	SETY_INCPLS_HOSM01X		;//0.1�x
	U4b	SETY_INCPLS_HOSM001		;//0.01�x
	U4b	SETY_INCPLS_HOSM0001		;//0.001�x
	
	U2b	SET1_MOTRPM_MAXM		;//	2	;Ӱ��ő��]��

	U2b	SETX_OUTPLS_HOSA	;//�o����ٽ�␳A
	U2b	SETX_OUTPLS_HOSB	;//�o����ٽ�␳B  INC*A/B-->Output pls