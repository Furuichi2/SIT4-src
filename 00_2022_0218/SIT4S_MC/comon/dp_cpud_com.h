//;	*******************************************************************
//;	***								***
//;	***								***
//;	***		CPUD<=>CPUA					***
//;	***		CPUD<=>CPUB					***
//;	***								***
//;	***								***
//;	***								***
//;	*******************************************************************

//#include	"cm_equ1.h"

//;	*******************************************
//;	***					***
//;	***	SH2��SH4�@���޼���		***
//;	***					***
//;	*******************************************
	extern	U4b	HS_SVCHG_B_TO_A;

//;	*******************************************
//;	***					***
//;	***	SH2��SH4�@���޼���		***
//;	***					***
//;	*******************************************
	extern	U4b	HS_SVCHG_A_TO_B;
	extern	U2b	HS_PVP_TAKIKI_FLG;//�ҋ@�_�ʉ��׸� 1��Ă�SH4�@0CLR��SH2(HMI��)
	extern	U2b	HS_PVP_LOTCNT_FLG;

	extern	U2b	KEEPRY_BKUP_FLG;	// �����ڰ��荞�݋����׸�

//;	==== 2003-07-09 ===
	extern	U2b	CMD_1CYCLE_DSP1	;//2003-07-09 1���ّ��x/���� 0:��\���@1:�\��
	extern	U2b	CMD_DAIPOS_DSP1	;//2003-07-09 ���Y�����ʒu�@ 0:��\���@1:�\��

//	=== 2006-12-05 ====
	extern	U2b	CMD_KJTECH_DSP1		;//2006-12-05 1:�׏d�␳��ð�ݸމ\

//;	*******************************************
//;	***									***
//;	***	�ް�ޮݱ����׸ޗ̈� SH2-->SH4	***
//;	***									***
//;	*******************************************
	extern	U4b	VUP_HSAREA_B_TO_A[32];

//;	*******************************************
//;	***									***
//;	***	�ް�ޮݱ����׸ޗ̈� SH2<--SH4	***
//;	***									***
//;	*******************************************
	extern	U4b	VUP_HSAREA_A_TO_B[32];




//;	***************************************************
//;	***						***
//;	***	HMI(SH2-->SH4) �ݒ�/���Ұ����̈�	***
//;	***	����ORG H'1000~ORG H'2FFF�̈��		***
//;	***	�ް�ޮݱ����ް��Ɏg�p�����		***
//;	***						***
//;	***************************************************
//;
//;	***************************************************
//;	***	���ݽKEEP RY �ޯ����ߕԂ��̈�		***
//;	***************************************************
	extern	U4b	VUP_DATA_ADR_OP1;//ROM�ް�(MAX8192�޲�)
//??????????????????????	extern	U2b	SVB_SEQKEP_DAT[128];//���ݽKEEP�̈�
				//;��̈�Ȃ�
//;	***************************************************
//;	***	4/2BYTE  �ޯ����ߕԂ��̈�(64b)		***
//;	***************************************************
	extern	S4b	SVB_RNAORG_PLS1;	//�Ʊ��ʒu��ٽ
					//�\��4byte�̈�
	extern	S4b	SVB_DYHITO_POS;	//2003-07-09 �޲ʲ�(�����ʒu)
	extern	S4b	SVB_SLIDE_POS;	//2003-07-09 ���Y�����ʒu

	extern	S4b	SVB_BAKORG_PLS1;//�Ʊ��ʒu��ٽ	COP2
	extern	S4b	SVB_BAKORG_PLS2;//�Ʊ��ʒu��ٽ	COP2

	extern	S4b	SVB_RENIA_BUP1;//360�p�x������ٽ1
	extern	S4b	SVB_RENIA_BUP2;//360�p�x������ٽ2
	extern	S4b	SVB_RENIA_BUP3;//360�p�x������ٽ�̔��](SUM1)
	extern	S4b	SVB_RENIA_BUP4;//360�p�x������ٽ�̔��](SUM2)

//;	---------- 2006-12-04 �׏d�␳�p�׏d(���ϒl�ޯ�����)----------
	extern	S2b	SVB_ARA1_KAJ_T2	;//��ԍő�׏dTOTAL�̂ݎg�p

//;	***************************************************
//;	***	2BYTE  ROM���Ұ��̈�			***
//;	***************************************************
	extern	U2b	SVP_RPARAM_TOP1[128];//ROM���Ұ��̈�
				//;
//;	***************************************************
//;	***	�������Ұ��̈�	4/2BYTE�̈�		***
//;	***************************************************
	extern	U2b	SVP_RNADIR_SEL1;//�Ʊ�ݻ�ɐ�
	extern	U2b	SVP_INCDIR_SEL1;//PG�ɐ�
	extern	U2b	SVP_INCPLS_1REV;//PG1��]����ٽ�I��
	extern	U2b	SVP_INCPLS_HOSN;//PG�␳N�@Ӱ�N��
	extern	U2b	SVP_INCPLS_HOSM;//PG�␳M�@��ݸ�p�xM
	extern	U2b	SVP_MOTRPM_MAXM;//Ӱ��ő��]��

	extern	S4b	SVP_MOTMAX_FREQ;//Ӱ��ő厞�w�ߎ��g��
	extern	S4b	SVP_RNAORG_POS1;//�@�B���_����
	extern	U4b	SVP_RNAPOS_MAXP;//�@�B���
	extern	U4b	SVP_RNAPOS_MINP;//�@�B����
	extern	U4b	SVP_UPAREA_JUDG;//�㎀�_����͈�
	extern	U4b	SVP_DNAREA_JUDG;//���]�ݒ�s�͈�



	extern	U2b	SVP_DNDINC_SPD1;		//�i�摬�x	
	extern	U2b	SVP_UPAREA_SPD1;		//�ҋ@�_���A���x	
	extern	U2b	SVP_STDINC_SPD1;		//�������x	
	extern	U2b	SVP_REVDAT_SPD1;		//�\�����x�P	
	extern	U2b	SVP_REVDAT_SPD2;		//�\�����x�Q	
	extern	U2b	SVP_REVDAT_SPD3;		//�\�����x�R	
	extern	U2b	SVP_TEPDAT_SPD1;		//�蓮��ٻ���x	
	extern	U2b	SVP_TEPLAT_DAT1;		//�蓮��ٻ��{��	
	extern	U2b	SVP_TEPLAT_DAT2;		//�蓮��ٻ���{��	

	extern	U2b	SVP_INCPOS_KP01;		//;PG�ʒu���޲�
	extern	U2b	SVP_RNAPOS_KP01;		//;�Ʊ�ʒu���޲�
	extern	U2b	SVP_ACCLAT_TIM1;		//;����������
	extern	U2b	SVP_SSCURV_TIM1;		//;�r������
	extern	U2b	SVP_UPAREA_INP1;		//;�㎀�_���߼޼��
	extern	U2b	SVP_DNAREA_INP1;		//;�����_���߼޼��
	extern	U2b	SVP_OBJARA_INP1;		//;�ڕW�ʒu���߼޼��
	extern	U2b	SVP_INPPOS_TIM1;		//;���߼޼����������
	extern	U2b	SVP_ARACHK_LNG1;		//;��^�����_�ʉߔ����
	extern	U2b	SVP_UPAREA_DIG1;		//;��]���ҋ@�_(�㎀�_)

	extern	U2b	SVP_INCHEN_ELNG;		//;PG�΍��ُ핝
	extern	U2b	SVP_INCENC_ELNG;		//;PG-ENC��v��
	extern	U2b	SVP_INCRNA_ELNG;		//;PG-�Ʊ��v��
	extern	U2b	SVP_INCSTP_ELNG;		//;PG��~�ُ��
	extern	U2b	SVP_RNASTP_ELNG;		//;�Ʊ��~�ُ��
	extern	U2b	SVP_INCREV_ELNG;		//;PG�t�]�ُ��
	extern	U2b	SVP_RNAREV_ELNG;		//;�Ʊ�t�]�ُ��
	extern	U2b	SVP_DAIHAI_LNG1;		//;�޲ʲĕ␳��r�l(��)
	extern	U2b	SVP_DAIHAI_LNG2;		//;�޲ʲĕ␳��r�l(��)
	extern	U2b	SVP_DAIHAI_LNG3;		//;�޲ʲĕ␳��r�l(��)

	extern	U2b	SVP_AMPERR_VLT1;		//;�ߕ��דd��1
	extern	U2b	SVP_AMPERR_TIM1;		//;�ߕ��׎���1
	extern	U2b	SVP_AMPERR_VLT2;		//;�ߕ��דd��2
	extern	U2b	SVP_AMPERR_TIM2;		//;�ߕ��׎���2
	extern	U2b	SVP_AMPERR_VLT3;		//;�ߕ��דd��3
	extern	U2b	SVP_AMPERR_TIM3;		//;�ߕ��׎���3

//;	==== 2002-08-08 ==
	extern	U2b	SVP_CNT_TIM		;//�A���^�C�}
	extern	U2b	SVP_CNT_CNT		;//�A���J�E���^
	extern	U2b	SVP_BREAK_DIG		;//��ڰ��p�x   0.1�x
	extern	U2b	SVP_BREAK_TIM1		;//�u���[�L�^�C�}�ݒ�
	extern	U2b	SVP_WT_DIG1		;//�ҋ@�_�I��1
	extern	U2b	SVP_WT_DIG2		;//�ҋ@�_�I��2
	extern	U2b	SVP_WT_DIG3		;//�ҋ@�_�I��3
	extern	U2b	SVP_MOTWT_TIM		;//�N���ۏ؎���
	extern	U2b	SVP_PSMOD_SEL		;//PSID�@Ӱ�ޑI��
//;	==== 2002-08-21 ==
	extern	S4b	SVP_RNA_STLORK	;//
	extern	U2b	SVP_OUTPLS_HOSA	;//
	extern	U2b	SVP_OUTPLS_HOSB	;//
	extern	U2b	SVP_UPHOLD_DIG	;//
	extern	U2b	SVP_MACINE_SEL1	;//

//;	=========== 2003-01-27 ======
	extern	S4b	SVP_NEG_OFS_LNG	;//���]��������(0.001mm �������Ұ�)
	extern	U2b	SVP_AMP100P_VLT	;//AMP100%�������̓d���l 0~10.0v(�������Ұ�)
//===============================

//;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	extern	U4b	SVP_LSAABN_AGL1	;//LSA�ُ팟�m�̊p�x1
	extern	U4b	SVP_LSAABN_AGL2	;//LSA�ُ팟�m�̊p�x2
	extern	U2b	SVP_PLSALO_PLS	;//�p���T�{����
	extern	U2b	SVP_PLSAHI_PLS	;//�p���T�{����
	extern	U2b	SVP_SMPSTR_KAJ	;// �����ݸށ@�ضމ׏d
	extern	U2b	SVP_SMPSTR_AGL	;// �����ݸށ@�ضފp�x
	extern	U2b	SVP_SMPSTR_FUK	;// �����ݸށ@�ضޕ��ח�
	extern	U2b	SVP_SMPSTR_SEH	;// �����ݸށ@�ض޼��ݽ�i��ʱ��ڽ�j
	extern	U2b	SVP_SMPSTR_SQL	;// �����ݸށ@�ض޼��ݽ�i���ʱ��ڽ�j
	extern	U2b	SVP_SMPMAX_CNT	;// �����ݸށ@�ő��
	extern	U2b	SVP_SMPTRG_CNT	;// �����ݸށ@����ضތ�
	extern	U2b	SVP_SMPCYC_TIM	;// �����ݸށ@����
	extern	U2b	SVP_MOADR0_SQH  ;// ���j�^�A�h���X�O�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR0_SQL  ;// ���j�^�A�h���X�O�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR1_SQH  ;// ���j�^�A�h���X�P�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR1_SQL  ;// ���j�^�A�h���X�P�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR2_SQH  ;// ���j�^�A�h���X�Q�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR2_SQL  ;// ���j�^�A�h���X�Q�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR3_SQH  ;// ���j�^�A�h���X�R�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR3_SQL  ;// ���j�^�A�h���X�R�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR4_SQH  ;// ���j�^�A�h���X�S�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR4_SQL  ;// ���j�^�A�h���X�S�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR5_SQH  ;// ���j�^�A�h���X�T�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR5_SQL  ;// ���j�^�A�h���X�T�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR6_SQH  ;// ���j�^�A�h���X�U�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR6_SQL  ;// ���j�^�A�h���X�U�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR7_SQH  ;// ���j�^�A�h���X�V�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR7_SQL  ;// ���j�^�A�h���X�V�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR8_SQH  ;// ���j�^�A�h���X�W�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR8_SQL  ;// ���j�^�A�h���X�W�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADR9_SQH  ;// ���j�^�A�h���X�X�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADR9_SQL  ;// ���j�^�A�h���X�X�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRA_SQH  ;// ���j�^�A�h���X�P�O�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRA_SQL  ;// ���j�^�A�h���X�P�O�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRB_SQH  ;// ���j�^�A�h���X�P�P�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRB_SQL  ;// ���j�^�A�h���X�P�P�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRC_SQH  ;// ���j�^�A�h���X�P�Q�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRC_SQL  ;// ���j�^�A�h���X�P�Q�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRD_SQH  ;// ���j�^�A�h���X�P�R�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRD_SQL  ;// ���j�^�A�h���X�P�R�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRE_SQH  ;// ���j�^�A�h���X�P�S�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRE_SQL  ;// ���j�^�A�h���X�P�S�@���ݽ���ʁ@V01v�@060713
	extern	U2b	SVP_MOADRF_SQH  ;// ���j�^�A�h���X�P�T�@���ݽ��ʁ@V01v�@060713
	extern	U2b	SVP_MOADRF_SQL  ;// ���j�^�A�h���X�P�T�@���ݽ���ʁ@V01v�@060713

//;	=== 2006-11-20 ===	SHIMA(HMI:V01z)
	extern	U2b	SVP_SMP_CNT		;//�����ݸގ��W�`���@��
	extern	U2b	SVP_TRD_CNT		;//����ގ��W�`���@��

//;	=== 2008-10-15 ===	SHIMA(HMI:V05l)
	extern	U2b	SVP_ATCOL_CYC       ;// �������W�����@����
	extern	U2b	SVP_ATCOL_STNO      ;// �������W�����@���W�͈́@�J�n�s��
	extern	U2b	SVP_ATCOL_STAG      ;// �������W�����@���W�͈́@�J�n�p�x
	extern	U2b	SVP_ATCOL_SPNO      ;// �������W�����@���W�͈́@�I���s��
	extern	U2b	SVP_ATCOL_SPAG      ;// �������W�����@���W�͈́@�I���p�x

//;	=== 2009-08-26 ===	SHIMA(HMI:V05o)
	extern	U4b	SVP_TRDCSR_RNAU		;/* �ײ�ޏ�����o�ʒu	*/
	extern	U4b	SVP_TRDCSR_RNAD		;/* �ײ�ޏ�����o�ʒu	*/ 
	extern	U2b	SVP_SMPTRG_CNT1		;//  �����ݸށ@����ضތ��iSIT�p�j

//;	=== 2009-10-05(���i�̉׏d�ݒ�) ====    HMI
	extern	U2b	SVP_OBJECT_PRS_TOP[10];
	extern	U2b	SVP_OBJECT_PRS01;
	extern	U2b	SVP_OBJECT_PRS02;
	extern	U2b	SVP_OBJECT_PRS03;
	extern	U2b	SVP_OBJECT_PRS04;
	extern	U2b	SVP_OBJECT_PRS05;
	extern	U2b	SVP_OBJECT_PRS06;
	extern	U2b	SVP_OBJECT_PRS07;
	extern	U2b	SVP_OBJECT_PRS08;
	extern	U2b	SVP_OBJECT_PRS09;
	extern	U2b	SVP_OBJECT_PRS10;

//;	=== 2010-08-12 ====    SHIMA(HMI:V05r)
	extern	U2b	SVP_BREAK_DIG_RAT	;//��ڰ��p�x   	����
	extern	U2b	SVP_BREAK_TIM_RAT	;//�u���[�L�^�C�}	����
	extern	U2b	SVP_MAX_KJYU		;//�ő�׏d�ݒ�(��߼�݂ɂ����Ȃ�)(2010-08-23 koma)
	extern	U2b	SVP_VIB_KJYU_TTL	;//vibration(�U��)�׏d(2010-08-23 koma)

//;	=== 2013-02-20 KOMA
	extern	U2b	SVP_KATTCH_SPD		;//���^�^�b�`���x

//;	***************************************************
//;	***	�ׯ������ʐݒ�1 4/2BYTE�̈�		***
//;	***************************************************
	extern	U4b	SVP_OBJECT_POS_TOP[20];		//01�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS01;		//01�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS02;		//02�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS03;		//03�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS04;		//04�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS05;		//05�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS06;		//06�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS07;		//07�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS08;		//08�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS09;		//09�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS10;		//10�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS11;		//11�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS12;		//12�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS13;		//13�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS14;		//14�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS15;		//15�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS16;		//16�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS17;		//17�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS18;		//18�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS19;		//19�i�ږڕW�ʒu
	extern	U4b	SVP_OBJECT_PS20;		//20�i�ږڕW�ʒu
                                                 
	extern	U2b	SVP_OBJECT_DIG_TOP[20]	;//01�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG01		;//01�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG02		;//02�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG03		;//03�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG04		;//04�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG05		;//05�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG06		;//06�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG07		;//07�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG08		;//08�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG09		;//09�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG10		;//10�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG11		;//�\��11�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG12		;//�\��12�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG13		;//�\��13�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG14		;//�\��14�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG15		;//�\��15�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG16		;//�\��16�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG17		;//�\��17�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG18		;//�\��18�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG19		;//�\��19�i�ڊp�x�ʒu
	extern	U2b	SVP_OBJECT_DG20		;//�\��20�i�ڊp�x�ʒu

	extern	U2b	SVP_OBJECT_SPD_TOP[20]	;//01�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP01		;//01�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP02		;//02�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP03		;//03�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP04		;//04�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP05		;//05�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP06		;//06�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP07		;//07�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP08		;//08�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP09		;//09�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP10		;//10�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP11		;//�\��11�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP12		;//�\��12�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP13		;//�\��13�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP14		;//�\��14�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP15		;//�\��15�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP16		;//�\��16�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP17		;//�\��17�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP18		;//�\��18�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP19		;//�\��19�i�ڈړ����x
	extern	U2b	SVP_OBJECT_SP20		;//�\��20�i�ڈړ����x

	extern	U2b	SVP_OBJECT_TIM_TOP[20]	;//01�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM01		;//01�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM02		;//02�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM03		;//03�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM04		;//04�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM05		;//05�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM06		;//06�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM07		;//07�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM08		;//08�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM09		;//09�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM10		;//10�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM11		;//11�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM12		;//12�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM13		;//13�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM14		;//14�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM15		;//15�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM16		;//16�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM17		;//17�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM18		;//18�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM19		;//19�i�ڒ�~����
	extern	U2b	SVP_OBJECT_TM20		;//20�i�ڒ�~����

//;	***************************************************
//;	***	�ׯ������ʐݒ�2 4/2BYTE�̈�		***
//;	***************************************************
	extern	U4b	SVP_DAIHAI_ORG0		;//�_�C�n�C�g
//(�{����U4B��0.001mm�ݒ�)
//�����U2B��0.01mm�ݒ� �Ƃ肠�����A�������킹
	extern	U2b	SVP_MRTION_SEL1		;//��]����
	extern	U2b	SVP_MTSTEP_MAXM		;//�i��

	extern	U4b	SVP_UPAREA_POS0		;//�ҋ@�_�ʒu
	extern	U2b	SVP_UPAREA_DIG0		;//�ҋ@�_�p�x
	extern	U2b	SVP_UPAREA_SPD0		;//����x
	extern	U2b	SVP_UPAREA_TIM0		;//�ҋ@����
	extern	U2b	SVP_DNAREA_INP0		;//�����_���߼޼��(2002-06-28)
	extern	U2b	SVP_OBJARA_INP0		;//�ڕW�ʒu���߼޼��(2002-06-28)
	extern	U2b	SVP_DAIHSA_LENG		;//�޲ʲĕ␳����

//;	==== 2002-08-08======
	extern	U4b	SVP_SLID_POS1;//�ײ�ވʒu�@���Y
	extern	U4b	SVP_SLID_POS2;//�ײ�ވʒu�@�i��1
	extern	U4b	SVP_SLID_POS3;//�ײ�ވʒu�@�i��2

	extern	U2b	SVP_GMNSEQ_CNT01	;//����������->���ݽ
	extern	U2b	SVP_GMNSEQ_CNT02	;//����������->���ݽ
	extern	U2b	SVP_GMNSEQ_CNT03	;//����������->���ݽ
	extern	U2b	SVP_GMNSEQ_CNT04	;//�\��
	extern	U2b	SVP_GMNSEQ_CNT05	;//�\��
	extern	U2b	SVP_GMNSEQ_CNT06	;//�\��
	extern	U2b	SVP_GMNSEQ_CNT07	;//�\��
	extern	U2b	SVP_GMNSEQ_CNT08	;//�\��

	extern	U2b	SVP_GMNSEQ_TIM01	;//������ʶ��������ݽ
	extern	U2b	SVP_GMNSEQ_TIM02	;//������ʶ��������ݽ
	extern	U2b	SVP_GMNSEQ_TIM03	;//������ʶ��������ݽ
	extern	U2b	SVP_GMNSEQ_TIM04	;//�\��
	extern	U2b	SVP_GMNSEQ_TIM05	;//�\��
	extern	U2b	SVP_GMNSEQ_TIM06	;//�\��
	extern	U2b	SVP_GMNSEQ_TIM07	;//�\��
	extern	U2b	SVP_GMNSEQ_TIM08	;//�\��

//;	==== 2002-08-26======
	extern	U2b	SVP_CAMFUN_SEL_TOP[16];
	extern	U2b	SVP_CAMFUN_SEL00;
	extern	U2b	SVP_CAMFUN_SEL01;
	extern	U2b	SVP_CAMFUN_SEL02;
	extern	U2b	SVP_CAMFUN_SEL03;
	extern	U2b	SVP_CAMFUN_SEL04;
	extern	U2b	SVP_CAMFUN_SEL05;
	extern	U2b	SVP_CAMFUN_SEL06;
	extern	U2b	SVP_CAMFUN_SEL07;
	extern	U2b	SVP_CAMFUN_SEL08;
	extern	U2b	SVP_CAMFUN_SEL09;
	extern	U2b	SVP_CAMFUN_SEL0A;
	extern	U2b	SVP_CAMFUN_SEL0B;
	extern	U2b	SVP_CAMFUN_SEL0C;
	extern	U2b	SVP_CAMFUN_SEL0D;
	extern	U2b	SVP_CAMFUN_SEL0E;
	extern	U2b	SVP_CAMFUN_SEL0F;

//;	===== 2002-08-29==
	extern	U4b	SVP_ATSLID_OBJ1		;// �X���C�h�������ߐݒ�l�i���ݓ��쒆�j
	extern	U2b	SVP_ATSLID_DNOBJ1	;// �X���C�h�������߁@���~��~
	extern	U2b	SVP_ATSLID_UPOBJ1	;// �X���C�h�������߁@�㏸��~
	extern	U2b	SVP_ATSLID_BAKLNG	;// �X���C�h�������߁@�߂��
	extern	U2b	SVP_ATSLID_COEF1	;// �X���C�h�������߁@���䐸�x

//;	***********************************
//;	***		�ُ헚��	2003-07-09 	***
//;************************************
	extern	U2b	SVP_MONALM_S01		;
	extern	U2b	SVP_MONALM_S02		;
	extern	U2b	SVP_MONALM_S03		;
	extern	U2b	SVP_MONALM_S04		;

//;	===== 2004-06-08==
	extern	U2b	SVP_KAJYUU_PRS1	;//�׏d
	extern	U2b	SVP_KAJYUU_PRS1	;//�׏d�␳ 1Kn (2004-06-08)
	extern	U2b	SVP_KAJYUU_OBJP	;//�׏d�ڕW�l 1Kn(2004-07-01)
	extern	U2b	SVP_KAJYUU_PV1	;//�ő�׏d(��߼�݂̎�����C/B�̐ݒ�Ƃ��ēn��)

//;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	extern	U2b	PVP_KAJLIV_LFT	;//�׏d���iTON�j(1word)
	extern	U2b	PVP_KAJLIV_TTL	;//�׏d���iTON�j(1word)
	extern	U2b	PVP_KAJLIV_RIH	;//�׏d���iTON�j(1word)

//;	=====2006-07-24(����ײ��) ====
	extern	U2b	SVP_OVERLIDE_COF	;//0,1~127%

//;	=====2006-07-24(�i��) ====
	extern	U2b	SVP_DND_STOPDIG1	;//�i���~�p�x 0~358.0

//;	=====2006-07-24(�׏d�␳) ====
	extern	U2b	SVP_KJSTR_STEP1		;//0,1~�H�� 
	extern	U2b	SVP_KJSTR_DIG1		;//359.0
	extern	U2b	SVP_KJEND_STEP1		;//0,1~�H��
	extern	U2b	SVP_KJEND_DIG1		;//359.0
	extern	U2b	PVP_ARA1_KAJ_R		;//OPTION ��ԍő�׏d
	extern	U2b	PVP_ARA1_KAJ_L		;//OPTION ��ԍő�׏d
	extern	U2b	PVP_ARA1_KAJ_T		;//OPTION ��ԍő�׏dTOTAL�̂ݎg�p

//;	=====2006-07-24(�\��) ====
	extern	U2b	PVP_1ROT_CALSPM	;//�\�z�^�]���x

//;	=====2006-10-13(COP2�֌W) ====
	extern	U4b	PVP_ORGRNA_MOV1	;//�Ʊ�ړ��ʎ���1
	extern	U4b	PVP_ORGRNA_MOV2	;//�Ʊ�ړ��ʎ���2
	extern	U4b	PVP_ORGSTRK_LEG1	;//��۰�1����
	extern	U4b	PVP_ORGSTRK_LEG2	;//��۰�2����
	extern	U4b	PVP_BAKORG_PLS1	;//�ޯ����ߎ���
	extern	U4b	PVP_BAKORG_PLS2	;//�ޯ����ߎ���
	extern	U4b	PVP_RENIA_POS1		;//�Ʊ����1����
	extern	U4b	PVP_RENIA_POS2		;//�Ʊ����2����
	extern	U2b	PVP_360_DEG		;//360�x�ݺ��ފp�x
	extern	U2b	PVP_PG_DEG1		;//PG�p�x1
	extern	U2b	PVP_PG_DEG2		;//PG�p�x2
	extern	U2b	PVP_ZURE_PLS		;//���Խ�ڎ���
	extern	U2b	PVP_ZURE_RNA		;//���Խ���Ʊ

	extern	U4b	SVP_ORGSOK_PLS		;//���_������ٽ
	extern	U4b	SVP_ORGCAL_DAT1		;//���Z�W��1
	extern	U4b	SVP_ORGCAL_DAT2		;//���Z�W��2
	extern	U4b	SVP_ORGCAL_DAT3		;//���Z�W��3
	extern	U4b	SVP_ORGCAL_DAT4		;//���Z�W��4
	extern	U4b	SVP_ORGCAL_DAT5		;//���Z�W��5
	extern	U4b	SVP_ORGCAL_DAT6		;//���Z�W��6
	extern	U4b	SVP_ORGSTRK_LEN1	;//��۰�1
	extern	U4b	SVP_ORGSTRK_LEN2	;//��۰�2
	extern	U4b	SVP_RNAORGMEM_LEG1	;//�Ʊ���_1���L��
	extern	U4b	SVP_RNAORG_PLS1		;//�ޯ����ߎ���
	extern	U4b	SVP_RNAORGMEM_LEG2	;//�Ʊ���_2���L��
	extern	U4b	SVP_RNAORG_PLS2		;//�ޯ����ߎ���
	extern	U2b	SVP_RNAORG_SIN1		;//�ޯ����ߎ�������
	extern	U2b	SVP_RNAORG_SIN2		;//�ޯ����ߎ�������
	extern	U2b	SVP_ORGRUP_DEG		;//���_�E��ԏ�
	extern	U2b	SVP_ORGRDN_DEG		;//���_�E��ԉ�
	extern	U2b	SVP_ORGLUP_DEG		;//���_����ԏ�
	extern	U2b	SVP_ORGLDN_DEG		;//���_����ԉ�
	extern	U2b	SVP_ORGMEM_DEG1		;//�p�x1��
	extern	U2b	SVP_ORGMEM_DEGS1	;//�p�x1���@ON/OFF
	extern	U2b	SVP_ORGMEM_DEG2		;//�p�x2��
	extern	U2b	SVP_ORGMEM_DEGS2	;//�p�x2���@ON/OFF
	extern	U2b	SVP_ORGMPL_SEL1		;//����ٻ�I��1���@ON/OFF
	extern	U2b	SVP_ORGMPL_SEL2		;//����ٻ�I��2���@ON/OFF
	extern	U2b	SVP_HOSRAG_PLS1		;//���ԕ␳�͈͂P
	extern	U2b	SVP_HOSRAG_PLS2		;//���ԕ␳�͈͂Q
	extern	U2b	SVP_HOSEI_SPD		;//�␳���x
	extern	U2b	SVP_MANSAM_LEN		;//�蓮������
	extern	U2b	SVP_DANSAM_LEN		;//�i�掚����
	extern	U2b	SVP_RUNSAMER_LEN1	;//�^�]�����ُ�P
	extern	U2b	SVP_RUNSAMER_LEN2	;//�^�]�����ُ�Q
	extern	U2b	SVP_MANSAMER_PLS	;//�蓮�����ُ�
	extern	U2b	SVP_RUNSAMER_PLS	;//�^�]�����ُ�

	extern	U2b	SVP_RNADIR_SEL2		;//�Ʊ�ݻ�ɐ�
	extern	U4b	SVP_ORGMEM_DEG1A	;//�p�x1��
	extern	U4b	SVP_ORGMEM_DEG2A	;//�p�x2��

	extern	U4b	PVP_RENIA_BUP1		;//360�p�x������ٽ1
	extern	U4b	PVP_RENIA_BUP2		;//360�p�x������ٽ2
	extern	U4b	PVP_RENIA_BUP3		;//360�p�x������ٽ�̔��](SUM1)
	extern	U4b	PVP_RENIA_BUP4		;//360�p�x������ٽ�̔��](SUM2)
	extern	U2b	PVP_RNABUP_ENB		;//�o�b�N�A�b�v�L���^����

//;	=====2006-11-20 ====	SHIMA(HMI:V01z)
	extern	U2b	PVP_ARA1_KAJ_T2		;//OPTION ��ԍő�׏dTOTAL�̂ݎg�p

//;	==== 2006-12-01 =====
	extern	U4b	PVP_MENTE_CNT		;//2006-12-01 MAIN-->C/B

//;	==== 2007-02-13(CPO2�֌W 2���������Ұ�) =====
	extern	U4b	PVP_PG_DEG1X		;//PG�p�x1
	extern	U4b	PVP_PG_DEG2X		;//PG�p�x2
	extern	U4b	PVP_PG_PLS1			;//PG1������ٽ
	extern	U4b	PVP_PG_PLS2			;//PG2������ٽ
	extern	U4b	PVP_PG12_DEG1		;//PG1-2�p�x
	extern	U2b	SVP_FCLS_STR_DEG	;//�ٸۊJ�n�p�x
	extern	U2b	SVP_FCLS_STR_HENS	;//�ٸۊJ�n�΍�
	extern	U2b	SVP_FCLS_ZIKI_SPD1	;//�ٸێ��N�����x1
	extern	U2b	SVP_FCLS_ZIKI_SPD2	;//�ٸێ��N�����x2
	extern	U2b	SVP_SYNC_ERR_DEGA	;//�����ُ�̈�p�xA
	extern	U2b	SVP_SYNC_ERR_DEGB	;//�����ُ�̈�p�xB
	extern	U2b	SVP_SYNC_ERR_DEGC	;//�����ُ�̈�p�xC
	extern	U2b	SVP_SYNC_ERR_DEGD	;//�����ُ�̈�p�xD
	extern	U2b	SVP_SYNC_ERR_RNAA	;//�Ʊ�����ُ�A
	extern	U2b	SVP_SYNC_ERR_RNAB	;//�Ʊ�����ُ�B
	extern	U2b	SVP_SYNC_ERR_RNAC	;//�Ʊ�����ُ�C
	extern	U2b	SVP_SYNC_ERR_RNAD	;//�Ʊ�����ُ�D
	extern	U2b	SVP_SYNC_ERR_PGA	;//PG�����ُ�A
	extern	U2b	SVP_SYNC_ERR_PGB	;//PG�����ُ�B
	extern	U2b	SVP_SYNC_ERR_PGC	;//PG�����ُ�C
	extern	U2b	SVP_SYNC_ERR_PGD	;//PG�����ُ�D

//;	==== 2010-09-15 =====
	extern	U2b	SVP_EP_VOF			;//�T�[�{�p�����[�^B0�@�@�d�͗p�̾��
	extern	U2b	SVP_EP_VMX			;//�T�[�{�p�����[�^B1�@�@�d�͗p�ő�l
	extern	U2b	SVP_EP_TRQ			;//�T�[�{�p�����[�^B2�@�@�d�͗p�ٸ�l
	extern	U2b	SVP_EP_LTM			;//�T�[�{�p�����[�^B3�@�@�ٸ���x�ꎞ��
	extern	U2b	SVP_EP_K1			;//�T�[�{�p�����[�^B4�@�@�����W��A
	extern	U2b	SVP_EP_K2			;//�T�[�{�p�����[�^B5�@�@�����W��B
	extern	U2b	SVP_EP_ADJSIN		;//�T�[�{�p�����[�^B6�@�@�����d�͕���
	extern	U2b	SVP_EP_ADJVAL		;//�T�[�{�p�����[�^B7�@�@�����d��
	extern	U2b	SVP_ECOM_BASE		;//�T�[�{�p�����[�^B8�@�@�G�R���[�^��l
	extern	U2b	SVP_ECOM_SCAL		;//�T�[�{�p�����[�^B9�@�@�G�R���[�^�X�P�[��
	extern	U2b	SVP_MOTRPM_MAXP		;//�T�[�{�p�����[�^BA.���[�^�ő��]��
	extern	U2b	SVP_ACCLAT_TIMP		;//�T�[�{�p�����[�^BB.����������

//;	==== 2010-12-06 =====
	extern	U2b	SVP_ONESTR_SPD2		;//���]�����N�����x

//;	==== 2011-03-22 =====
	extern	U4b	SVP_VOLST_L			;//�T�[�{�p�����[�^BC�@�@�d�͗p�̾��
	extern	U4b	SVP_SLIDE_S			;//�T�[�{�p�����[�^BD�@�@�d�͗p�ő�l
	extern	U4b	SVP_RAD				;//�T�[�{�p�����[�^BE�@�@�d�͗p�ٸ�l
	extern	U4b	SVP_ORGREV_AGL		;//�T�[�{�p�����[�^BF�@�@�ٸ���x�ꎞ��
	extern	U4b	SVP_ORGFWD_AGL		;//�T�[�{�p�����[�^BG�@�@�����W��A

//;	==== 2011-07-05 =====
	extern	U2b	SVP_RISE_ZWID		;//�T�[�{�p�����[�^BH�@�@�㏸�Ď���ە�
	extern	U2b	SVP_RISE_CMP1		;//�T�[�{�p�����[�^BI�@�@�㏸�Ď���r1
	extern	U2b	SVP_RISE_CMP2		;//�T�[�{�p�����[�^BJ�@�@�㏸�Ď���r2
	extern	U2b	SVP_RISE_CMP3		;//�T�[�{�p�����[�^BK�@�@�㏸�Ď���r�\��
	extern	U2b	SVP_RISE_DLY1		;//�T�[�{�p�����[�^BL�@�@�Ď��x��1
	extern	U2b	SVP_RISE_DLY2		;//�T�[�{�p�����[�^BM�@�@�Ď��x��2

//;	==== 2011-07-28 =====
	extern	U2b	PVP_MOTINS_DAN		;//���[�V�����}��(C/B->HMI) �i��(1�`9)
	extern	U2b	PVP_MOTINS_AGL		;//���[�V�����}��(C/B->HMI) �p�x(�����_1���f�[�^)
	extern	U4b	PVP_MOTINS_POS		;//���[�V�����}��(C/B->HMI) �ʒu(�����_3���f�[�^)

//;	==== 2011-10-19 =====
	extern	U4b	PVP_MOTINS_PS2		;//2012-10-19�ǉ� �}���ʒu2[����ʒu]
	extern	U2b	PVP_MOTINS_AG2		;//2012-10-19�ǉ� �}���p�x2[����p�x]

//;	==== 2013-02-20 KOMA �}���p�x3===
	extern	U2b	PVP_MOTINS_AG3		;//
	extern	U4b	PVP_MOTINS_PS3		;//
	extern	U2b	PVP_MOTINS_INF		;//BIT0~BIT2:�}�����


	extern	U2b	PVP_CKSPD_OVBIT				;//�ԕ\��(BIT0~BIT9 BIT15:�ߑ��x)
	extern	U2b	PVP_CKLMT_MDSPD				;//�߂葬�x

	extern	U2b	PVP_CKLMT_SPDTOP[10]		;//
	extern	U2b	PVP_CKLMT_SPD01				;//1�i��
	extern	U2b	PVP_CKLMT_SPD02				;//2�i��
	extern	U2b	PVP_CKLMT_SPD03				;//3�i��
	extern	U2b	PVP_CKLMT_SPD04				;//4�i��
	extern	U2b	PVP_CKLMT_SPD05				;//5�i��
	extern	U2b	PVP_CKLMT_SPD06				;//6�i��
	extern	U2b	PVP_CKLMT_SPD07				;//7�i��
	extern	U2b	PVP_CKLMT_SPD08				;//8�i��
	extern	U2b	PVP_CKLMT_SPD09				;//9�i��
	extern	U2b	PVP_CKLMT_SPD10				;//10�i��

	extern	U2b	PVP_MOTINS_DANBEF			;//0:�L���Ȓi������ 1~9:���^��������}���i��
	extern	U2b	PVP_MOTINS_DANAFT			;//0:�L���Ȓi������ 1~9:���^�����}���i��


//;	*******************************************
//;	***	�J���ݒ� 2BYTE�̈�		***
//;	*******************************************
	extern	U2b	SVP_RCAMON_POS_TOP;
	extern	U2b	SVP_RCAMON_P000		;//�ʒu��000�@�n�m�H��
	extern	U2b	SVP_RCAMON_D000		;//�ʒu��000�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P000		;//�ʒu��000�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D000		;//�ʒu��000�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P001		;//�ʒu��001�@�n�m�H��
	extern	U2b	SVP_RCAMON_D001		;//�ʒu��001�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P001		;//�ʒu��001�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D001		;//�ʒu��001�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P002		;//�ʒu��002�@�n�m�H��
	extern	U2b	SVP_RCAMON_D002		;//�ʒu��002�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P002		;//�ʒu��002�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D002		;//�ʒu��002�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P003		;//�ʒu��003�@�n�m�H��
	extern	U2b	SVP_RCAMON_D003		;//�ʒu��003�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P003		;//�ʒu��003�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D003		;//�ʒu��003�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P004		;//�ʒu��004�@�n�m�H��
	extern	U2b	SVP_RCAMON_D004		;//�ʒu��004�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P004		;//�ʒu��004�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D004		;//�ʒu��004�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P005		;//�ʒu��005�@�n�m�H��
	extern	U2b	SVP_RCAMON_D005		;//�ʒu��005�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P005		;//�ʒu��005�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D005		;//�ʒu��005�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P006		;//�ʒu��006�@�n�m�H��
	extern	U2b	SVP_RCAMON_D006		;//�ʒu��006�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P006		;//�ʒu��006�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D006		;//�ʒu��006�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P007		;//�ʒu��007�@�n�m�H��
	extern	U2b	SVP_RCAMON_D007		;//�ʒu��007�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P007		;//�ʒu��007�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D007		;//�ʒu��007�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P008		;//�ʒu��008�@�n�m�H��
	extern	U2b	SVP_RCAMON_D008		;//�ʒu��008�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P008		;//�ʒu��008�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D008		;//�ʒu��008�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P009		;//�ʒu��009�@�n�m�H��
	extern	U2b	SVP_RCAMON_D009		;//�ʒu��009�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P009		;//�ʒu��009�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D009		;//�ʒu��009�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00A		;//�ʒu��00A�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00A		;//�ʒu��00A�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00A		;//�ʒu��00A�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00A		;//�ʒu��00A�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00B		;//�ʒu��00B�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00B		;//�ʒu��00B�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00B		;//�ʒu��00B�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00B		;//�ʒu��00B�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00C		;//�ʒu��00C�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00C		;//�ʒu��00C�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00C		;//�ʒu��00C�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00C		;//�ʒu��00C�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00D		;//�ʒu��00D�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00D		;//�ʒu��00D�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00D		;//�ʒu��00D�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00D		;//�ʒu��00D�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00E		;//�ʒu��00E�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00E		;//�ʒu��00E�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00E		;//�ʒu��00E�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00E		;//�ʒu��00E�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P00F		;//�ʒu��00F�@�n�m�H��
	extern	U2b	SVP_RCAMON_D00F		;//�ʒu��00F�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P00F		;//�ʒu��00F�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D00F		;//�ʒu��00F�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P010		;//�ʒu��010�@�n�m�H��
	extern	U2b	SVP_RCAMON_D010		;//�ʒu��010�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P010		;//�ʒu��010�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D010		;//�ʒu��010�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P011		;//�ʒu��011�@�n�m�H��
	extern	U2b	SVP_RCAMON_D011		;//�ʒu��011�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P011		;//�ʒu��011�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D011		;//�ʒu��011�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P012		;//�ʒu��012�@�n�m�H��
	extern	U2b	SVP_RCAMON_D012		;//�ʒu��012�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P012		;//�ʒu��012�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D012		;//�ʒu��012�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P013		;//�ʒu��013�@�n�m�H��
	extern	U2b	SVP_RCAMON_D013		;//�ʒu��013�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P013		;//�ʒu��013�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D013		;//�ʒu��013�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P014		;//�ʒu��014�@�n�m�H��
	extern	U2b	SVP_RCAMON_D014		;//�ʒu��014�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P014		;//�ʒu��014�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D014		;//�ʒu��014�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P015		;//�ʒu��015�@�n�m�H��
	extern	U2b	SVP_RCAMON_D015		;//�ʒu��015�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P015		;//�ʒu��015�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D015		;//�ʒu��015�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P016		;//�ʒu��016�@�n�m�H��
	extern	U2b	SVP_RCAMON_D016		;//�ʒu��016�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P016		;//�ʒu��016�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D016		;//�ʒu��016�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P017		;//�ʒu��017�@�n�m�H��
	extern	U2b	SVP_RCAMON_D017		;//�ʒu��017�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P017		;//�ʒu��017�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D017		;//�ʒu��017�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P018		;//�ʒu��018�@�n�m�H��
	extern	U2b	SVP_RCAMON_D018		;//�ʒu��018�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P018		;//�ʒu��018�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D018		;//�ʒu��018�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P019		;//�ʒu��019�@�n�m�H��
	extern	U2b	SVP_RCAMON_D019		;//�ʒu��019�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P019		;//�ʒu��019�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D019		;//�ʒu��019�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01A		;//�ʒu��01A�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01A		;//�ʒu��01A�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01A		;//�ʒu��01A�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01A		;//�ʒu��01A�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01B		;//�ʒu��01B�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01B		;//�ʒu��01B�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01B		;//�ʒu��01B�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01B		;//�ʒu��01B�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01C		;//�ʒu��01C�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01C		;//�ʒu��01C�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01C		;//�ʒu��01C�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01C		;//�ʒu��01C�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01D		;//�ʒu��01D�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01D		;//�ʒu��01D�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01D		;//�ʒu��01D�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01D		;//�ʒu��01D�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01E		;//�ʒu��01E�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01E		;//�ʒu��01E�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01E		;//�ʒu��01E�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01E		;//�ʒu��01E�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P01F		;//�ʒu��01F�@�n�m�H��
	extern	U2b	SVP_RCAMON_D01F		;//�ʒu��01F�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P01F		;//�ʒu��01F�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D01F		;//�ʒu��01F�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P020		;//�ʒu��020�@�n�m�H��
	extern	U2b	SVP_RCAMON_D020		;//�ʒu��020�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P020		;//�ʒu��020�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D020		;//�ʒu��020�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P021		;//�ʒu��021�@�n�m�H��
	extern	U2b	SVP_RCAMON_D021		;//�ʒu��021�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P021		;//�ʒu��021�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D021		;//�ʒu��021�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P022		;//�ʒu��022�@�n�m�H��
	extern	U2b	SVP_RCAMON_D022		;//�ʒu��022�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P022		;//�ʒu��022�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D022		;//�ʒu��022�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P023		;//�ʒu��023�@�n�m�H��
	extern	U2b	SVP_RCAMON_D023		;//�ʒu��023�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P023		;//�ʒu��023�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D023		;//�ʒu��023�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P024		;//�ʒu��024�@�n�m�H��
	extern	U2b	SVP_RCAMON_D024		;//�ʒu��024�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P024		;//�ʒu��024�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D024		;//�ʒu��024�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P025		;//�ʒu��025�@�n�m�H��
	extern	U2b	SVP_RCAMON_D025		;//�ʒu��025�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P025		;//�ʒu��025�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D025		;//�ʒu��025�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P026		;//�ʒu��026�@�n�m�H��
	extern	U2b	SVP_RCAMON_D026		;//�ʒu��026�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P026		;//�ʒu��026�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D026		;//�ʒu��026�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P027		;//�ʒu��027�@�n�m�H��
	extern	U2b	SVP_RCAMON_D027		;//�ʒu��027�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P027		;//�ʒu��027�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D027		;//�ʒu��027�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P028		;//�ʒu��028�@�n�m�H��
	extern	U2b	SVP_RCAMON_D028		;//�ʒu��028�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P028		;//�ʒu��028�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D028		;//�ʒu��028�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P029		;//�ʒu��029�@�n�m�H��
	extern	U2b	SVP_RCAMON_D029		;//�ʒu��029�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P029		;//�ʒu��029�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D029		;//�ʒu��029�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02A		;//�ʒu��02A�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02A		;//�ʒu��02A�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02A		;//�ʒu��02A�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02A		;//�ʒu��02A�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02B		;//�ʒu��02B�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02B		;//�ʒu��02B�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02B		;//�ʒu��02B�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02B		;//�ʒu��02B�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02C		;//�ʒu��02C�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02C		;//�ʒu��02C�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02C		;//�ʒu��02C�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02C		;//�ʒu��02C�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02D		;//�ʒu��02D�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02D		;//�ʒu��02D�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02D		;//�ʒu��02D�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02D		;//�ʒu��02D�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02E		;//�ʒu��02E�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02E		;//�ʒu��02E�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02E		;//�ʒu��02E�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02E		;//�ʒu��02E�@�n�e�p�x
	extern	U2b	SVP_RCAMON_P02F		;//�ʒu��02F�@�n�m�H��
	extern	U2b	SVP_RCAMON_D02F		;//�ʒu��02F�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P02F		;//�ʒu��02F�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D02F		;//�ʒu��02F�@�n�e�p�x
	extern	U2b	SVP_RCAMON_TIM_TOP;
	extern	U2b	SVP_RCAMON_P100		;//�^�C�}��000�@�n�m�H��
	extern	U2b	SVP_RCAMON_D100		;//�^�C�}��000�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P100		;//�^�C�}��000�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D100		;//�^�C�}��000�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P101		;//�^�C�}��001�@�n�m�H��
	extern	U2b	SVP_RCAMON_D101		;//�^�C�}��001�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P101		;//�^�C�}��001�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D101		;//�^�C�}��001�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P102		;//�^�C�}��002�@�n�m�H��
	extern	U2b	SVP_RCAMON_D102		;//�^�C�}��002�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P102		;//�^�C�}��002�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D102		;//�^�C�}��002�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P103		;//�^�C�}��003�@�n�m�H��
	extern	U2b	SVP_RCAMON_D103		;//�^�C�}��003�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P103		;//�^�C�}��003�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D103		;//�^�C�}��003�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P104		;//�^�C�}��004�@�n�m�H��
	extern	U2b	SVP_RCAMON_D104		;//�^�C�}��004�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P104		;//�^�C�}��004�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D104		;//�^�C�}��004�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P105		;//�^�C�}��005�@�n�m�H��
	extern	U2b	SVP_RCAMON_D105		;//�^�C�}��005�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P105		;//�^�C�}��005�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D105		;//�^�C�}��005�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P106		;//�^�C�}��006�@�n�m�H��
	extern	U2b	SVP_RCAMON_D106		;//�^�C�}��006�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P106		;//�^�C�}��006�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D106		;//�^�C�}��006�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P107		;//�^�C�}��007�@�n�m�H��
	extern	U2b	SVP_RCAMON_D107		;//�^�C�}��007�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P107		;//�^�C�}��007�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D107		;//�^�C�}��007�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P108		;//�^�C�}��008�@�n�m�H��
	extern	U2b	SVP_RCAMON_D108		;//�^�C�}��008�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P108		;//�^�C�}��008�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D108		;//�^�C�}��008�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P109		;//�^�C�}��009�@�n�m�H��
	extern	U2b	SVP_RCAMON_D109		;//�^�C�}��009�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P109		;//�^�C�}��009�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D109		;//�^�C�}��009�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10A		;//�^�C�}��00A�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10A		;//�^�C�}��00A�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10A		;//�^�C�}��00A�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10A		;//�^�C�}��00A�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10B		;//�^�C�}��00B�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10B		;//�^�C�}��00B�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10B		;//�^�C�}��00B�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10B		;//�^�C�}��00B�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10C		;//�^�C�}��00C�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10C		;//�^�C�}��00C�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10C		;//�^�C�}��00C�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10C		;//�^�C�}��00C�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10D		;//�^�C�}��00D�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10D		;//�^�C�}��00D�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10D		;//�^�C�}��00D�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10D		;//�^�C�}��00D�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10E		;//�^�C�}��00E�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10E		;//�^�C�}��00E�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10E		;//�^�C�}��00E�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10E		;//�^�C�}��00E�@OF���ԁE�p�x
	extern	U2b	SVP_RCAMON_P10F		;//�^�C�}��00F�@�n�m�H��
	extern	U2b	SVP_RCAMON_D10F		;//�^�C�}��00F�@�n�m�p�x
	extern	U2b	SVP_RCAMOF_P10F		;//�^�C�}��00F�@�n�e�H��
	extern	U2b	SVP_RCAMOF_D10F		;//�^�C�}��00F�@�n�e���ԁE�p
                                                 
//;	*******************************
//;	***							***
//;	***		�\��				***
//;	***	�ʐM������ފ֌W			***
//;	*******************************
	extern	U4b	SVP_DEB_ADR0		; 
	extern	U4b	SVP_DEB_ADR1		; 
	extern	U4b	SVP_DEB_ADR2		; 
	extern	U4b	SVP_DEB_ADR3		; 
	extern	U4b	SVP_DEB_ADR4		; 

	extern	U2b	SVP_DEB_SEL0		; 
	extern	U2b	SVP_DEB_SEL1		; 
	extern	U2b	SVP_DEB_SEL2		; 
	extern	U2b	SVP_DEB_SEL3		; 
	extern	U2b	SVP_DEB_SEL4		; 

	extern	U2b	PVP_DEB_DAT0		; 
	extern	U2b	PVP_DEB_DAT1		; 
	extern	U2b	PVP_DEB_DAT2		; 
	extern	U2b	PVP_DEB_DAT3		; 
	extern	U2b	PVP_DEB_DAT4		; 
	extern	U2b	PVP_DEB_DAT5		; 
	extern	U2b	PVP_DEB_DAT6		; 
	extern	U2b	PVP_DEB_DAT7		; 
	extern	U2b	PVP_DEB_DAT8		; 
	extern	U2b	PVP_DEB_DAT9		; 

//;	***********************************
//;	***		�ُ헚��	2003-07-09 	***
//;************************************

	extern	U2b	PVP_MONALM_P01	;//
	extern	U2b	PVP_MONALM_P02	;//
	extern	U2b	PVP_MONALM_P03	;//
	extern	U2b	PVP_MONALM_P04	;//


	extern	S4b	PVP_MONALM_C01	;//A/B/C�͘A��������Ԃł��鎖
	extern	S4b	PVP_MONALM_C02	;//
	extern	S4b	PVP_MONALM_C03	;//
	extern	S4b	PVP_MONALM_C04	;//
	extern	S4b	PVP_MONALM_C05	;//
	extern	S4b	PVP_MONALM_C06	;//
	extern	S4b	PVP_MONALM_C07	;//
	extern	S4b	PVP_MONALM_C08	;//
	extern	U2b	PVP_MONALM_A01	;//
	extern	U2b	PVP_MONALM_A02	;//
	extern	U2b	PVP_MONALM_A03	;//
	extern	U2b	PVP_MONALM_A04	;//
	extern	U2b	PVP_MONALM_A05	;//
	extern	U2b	PVP_MONALM_A06	;//
	extern	U2b	PVP_MONALM_A07	;//
	extern	U2b	PVP_MONALM_A08	;//
	extern	S2b	PVP_MONALM_B01	;//
	extern	S2b	PVP_MONALM_B02	;//
	extern	S2b	PVP_MONALM_B03	;//
	extern	S2b	PVP_MONALM_B04	;//
	extern	S2b	PVP_MONALM_B05	;//
	extern	S2b	PVP_MONALM_B06	;//
	extern	S2b	PVP_MONALM_B07	;//
	extern	S2b	PVP_MONALM_B08	;//


//;	*******************************
//;	***		���� 4/2BYTE�̈�	***
//;	*******************************
	extern	S4b	PVP_RNAORG_PLS1		;//�Ʊ��ʒu��ٽ(�ޯ����ߐ�p)
	extern	S4b	PVP_NOW_POSI000		;//���݈ʒu(�␳��̃��j�A�Z���T�ʒu)
	extern	S4b	PVP_RENIA_POSI0		;//���j�A�Z���T���݈ʒu(���\���p)
	extern	U2b	PVP_NOW_ANGLE00		;//���݊p�x
	extern	U2b	PVP_CYCLE_TIME0		;//�T�C�N������

//;	----- �ǉ�2002/07/02 ---
	extern	S2b	PVP_CYCLE_SPM1		;//�T�C�N�����x�\���p
	extern	S2b	PVP_DISP_SPM2		;//�������`���h��Ԃ��ɂ���ׂ̑��x(�P�ʕs��)
	extern	S2b	PVP_NOW_ANGLE_RNA	;//���݊p�x0.1�xHEX(�Ʊ���ق����1�x�P�� SH4->SH2)
	extern	S2b	PVP_DYHITO_HOSLNG	;//�޲ʲĕ␳�� 1um(0.001mm) +/-
	extern	S4b	PVP_DYHITO_POS		;//�޲ʲĎ����O��l(?) ���Y�������
	extern	S4b	PVP_SLIDE_POS		;//�ײ�ވʒu�E�޲ʲĂ��܂߂��ʒu
	extern	S2b	PVP_TAIKITEN_POS	;//

//;	----- �ǉ�2002/08/01 ---
	extern	S4b	PVP_RNA_STLORK		;//��۰�����
	extern	U2b	PVP_STOP_TIM		;//�į��ݸ���� 1msec data
	extern	U2b	PVP_BREAK_DIG		;//��ڰ��p�x   0.1�x
	extern	U2b	PVP_COM_ERR		;//���߲وُ�L��^����
	extern	U2b	PVP_COM_ADR		;//���߲وُ���ڽ
	extern	U2b	PVP_SEQ_ERR		;//���߲وُ튄��orҲ�

//;	----- �ǉ�2002/08/08-----
	extern	U2b	PVP_BREAK_TIM1		;//
	extern	U2b	PVP_GMNSEQ_CNT01	;//����������->���ݽ
	extern	U2b	PVP_GMNSEQ_CNT02	;//����������->���ݽ
	extern	U2b	PVP_GMNSEQ_CNT03	;//����������->���ݽ
	extern	U2b	PVP_GMNSEQ_CNT04	;//�\��
	extern	U2b	PVP_GMNSEQ_CNT05	;//�\��
	extern	U2b	PVP_GMNSEQ_CNT06	;//�\��
	extern	U2b	PVP_GMNSEQ_CNT07	;//�\��
	extern	U2b	PVP_GMNSEQ_CNT08	;//�\��

	extern	U2b	PVP_GMNSEQ_TIM01	;//������ʶ��������ݽ
	extern	U2b	PVP_GMNSEQ_TIM02	;//������ʶ��������ݽ
	extern	U2b	PVP_GMNSEQ_TIM03	;//������ʶ��������ݽ
	extern	U2b	PVP_GMNSEQ_TIM04	;//�\��
	extern	U2b	PVP_GMNSEQ_TIM05	;//�\��
	extern	U2b	PVP_GMNSEQ_TIM06	;//�\��
	extern	U2b	PVP_GMNSEQ_TIM07	;//�\��
	extern	U2b	PVP_GMNSEQ_TIM08	;//�\��

//;	========== 2003-01-27 ��ܰ��������ǉ�====
	extern	U2b	PVP_POWER_MONI		;//

//;	========= 2003-02-04 ======
	extern	U2b	PVP_CPUA_TEPPLS		;//
	extern	U2b	PVP_CPUB_TEPPLS		;//
	extern	U2b	PVP_CPUA_ANAIN		;//
	extern	U2b	PVP_CPUB_ANAIN		;//


//;	========== 2010-09-01 �d�͗ʒǉ� ============
	extern	U2b	PVP_ECO_METER		;
	extern	U2b	PVP_POWER_KWH		;
	extern	U2b	PVP_EPM_SYOHI		;
	extern	U2b	PVP_EPM_KAISE		;

	extern	U2b	PVP_IVW_DOT			;//0:�����_2�� 5A:�����_1�� CPUA->CPUB



//	=========================================

	extern	U2b	PVP_CB_A_VER[6]		;//(1WORD�ŷ�׸����� 6char) SH4-->
	extern	U2b	PVP_CB_B_VER[6]		;//(6char) SH2-->

//;	======= 2003-01-27 ���Ұ��ް�ޮݒǉ� =====
	extern	U2b	PVP_PAR_A_VER		;//���Ұ��ް�ޮ� HEX data
	extern	U2b	PVP_PAR_B_VER		;//���Ұ��ް�ޮ� HEX data
	extern	U2b	PVP_TBL_A_VER		;//�ݻ��ð��ٔԍ�1~99 HEX data
	extern	U2b	PVP_TBL_B_VER		;//�ݻ��ð��ٔԍ�1~99 HEX data
//	=========================================
	extern	U2b	PVP_PAR_A_CHAR		;//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
	extern	U2b	PVP_PAR_B_CHAR		;//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
	extern	U2b	PVP_TBL_A_CHAR		;//�ݻ��ð��ٔԍ�()
	extern	U2b	PVP_TBL_B_CHAR		;//�ݻ��ð��ٔԍ�()

//;	======= V05j 2007-11-14 COP2�ް�ޮݒǉ� =====
	extern	U2b	PVP_CB_C_VER[6]		;//ASCII�ް� (1WORD�ŷ�׸����� 6char) SH4-->
	extern	U2b	PVP_PAR_C_VER		;//���Ұ��ް�ޮ� HEX data
	extern	U2b	PVP_PAR_C_CHAR		;//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
	extern	U2b	PVP_TBL_C_VER		;//ð����ް�ޮ� HEX data�i���g�p�j
	extern	U2b	PVP_TBL_C_CHAR		;//ð����ް�ޮ� ������׸� ASCII(2BYTE)

//;	*******************************************
//;	***					***
//;	***	SH2��SH4�@���޼���		***
//;	***					***
//;	*******************************************

//;	*******************************************
//;	***					***
//;	***					***
//;	***					***
//;	*******************************************

//;	***********************************************************
//;	***		2014�N 3���ȍ~�̒ǉ��͂���		***
//;	***********************************************************
//;	=== 2014/03/17 ===	SHIMA
	extern	U2b	SVP_KAJAREA_SNO		;//�׏d����͈� �J�n�H��No.
	extern	U2b	SVP_KAJAREA_SAG		;//�׏d����͈� �J�n�p�x
	extern	U2b	SVP_KAJAREA_ENO		;//�׏d����͈� �I���H��No.
	extern	U2b	SVP_KAJAREA_EAG		;//�׏d����͈� �I���p�x
	extern	U2b	SVP_KAJAREA_SEL		;//�L�^�׏d�I��

//;	=== 2014/04/14 ===	SHIMA
	extern	U2b	SVP_KATTCH_SAG		;//�^�b�`�ʒu���o�p�x
	extern	U2b	SVP_KATTCH_EAG		;//�^�b�`�ʒu���o�p�x

//;	=== 2014/04/14 ===	SHIMA
	extern	U4b	SVP_KANDO_A21		;//���x
	extern	U4b	SVP_UPDATA_A21		;//���
	extern	U4b	SVP_DNDATA_A21		;//����
	extern	U4b	SVP_GENITI_A21		;//���ʒu
	extern	U2b	SVP_MODORI_A21		;//�߂��
	extern	U2b	SVP_DNSTOP_A21		;//���~��~
	extern	U2b	SVP_UPSTOP_A21		;//�㏸��~
	extern	U2b	SVP_SSEIDO_A21		;//���䐸�x
	extern	U2b	SVP_SL_TENPOS		;//�X���C�h���������̏����_�ʒu
	extern	U2b	SVP_SLPOS_DIR		;//�ʒu���ߕ���


//;	-------------- �ő�l�I���� ����۰��,۱�Я� ��,���v,�E
	extern	U2b	SVP_OVERE1_A26	;// �׏d�v�@�I�[�o�[���[�h�P
	extern	U2b	SVP_ROALM1_A26	;// �׏d�v�@���A�[���b�~�g�P
	extern	U2b	SVP_OVERE2_A26	;// �׏d�v�@�I�[�o�[���[�h�Q
	extern	U2b	SVP_ROALM2_A26	;// �׏d�v�@���A�[���b�~�g�Q
	extern	U2b	SVP_OVERE3_A26	;// �׏d�v�@�I�[�o�[���[�h�R
	extern	U2b	SVP_ROALM3_A26	;// �׏d�v�@���A�[���b�~�g�R

//;	-------------- �ŏ�(ϲŽ�ő�)�I���� ����۰��,۱�Я� ��,���v,�E
	extern	U2b	SVP_OVERE1_A27	;// �׏d�v�@�I�[�o�[���[�h�P �@�i�ŏ��l�j
	extern	U2b	SVP_ROALM1_A27	;// �׏d�v�@���A�[���b�~�g�P  �@�i�ŏ��l�j
	extern	U2b	SVP_OVERE2_A27	;// �׏d�v�@�I�[�o�[���[�h�Q  �@�i�ŏ��l�j
	extern	U2b	SVP_ROALM2_A27	;// �׏d�v�@���A�[���b�~�g�Q  �@�i�ŏ��l�j
	extern	U2b	SVP_OVERE3_A27	;// �׏d�v�@�I�[�o�[���[�h�R  �@�i�ŏ��l�j
	extern	U2b	SVP_ROALM3_A27	;// �׏d�v�@���A�[���b�~�g�R  �@�i�ŏ��l�j

//;	-------------- �U���I���� ����۰��,۱�Я� ��,���v,�E
	extern	U2b	SVP_OVERE1_A28	;// �׏d�v�@�I�[�o�[���[�h�P �@�i�U���j
	extern	U2b	SVP_ROALM1_A28	;// �׏d�v�@���A�[���b�~�g�P  �@�i�U���j
	extern	U2b	SVP_OVERE2_A28	;// �׏d�v�@�I�[�o�[���[�h�Q  �@�i�U���j
	extern	U2b	SVP_ROALM2_A28	;// �׏d�v�@���A�[���b�~�g�Q  �@�i�U���j
	extern	U2b	SVP_OVERE3_A28	;// �׏d�v�@�I�[�o�[���[�h�R  �@�i�U���j
	extern	U2b	SVP_ROALM3_A28	;// �׏d�v�@���A�[���b�~�g�R  �@�i�U���j



//;	=== 2014-06-09(2014/03/12) ===
	extern	U2b	SVP_KAJOBJ_HAB		;//�׏d�����͈�

//;	=== 2014/08/27 ===	SHIMA
	extern	U2b	SVP_INTLIM_SNO		;//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�s��
	extern	U2b	SVP_INTLIM_AGL		;//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�p�x
	extern	U4b	SVP_INTLIM_POS		;//�ײ�ގ����ҋ@�@�\  �����E�ʒu�ݒ�@�ʒu
	extern	U2b	SVP_WTTIM_MAX		;//�ײ�ގ����ҋ@�@�\  �ҋ@���ԏ��

//;	=== 2014/09/02 ===	SHIMA
	extern	U2b	SVP_RCAMON_SA00;				/* ���[�^���J���O�P  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST00;				/* ���[�^���J���O�P  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA00;				/* ���[�^���J���O�P  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST00;				/* ���[�^���J���O�P  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA01;				/* ���[�^���J���O�Q  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST01;				/* ���[�^���J���O�Q  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA01;				/* ���[�^���J���O�Q  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST01;				/* ���[�^���J���O�Q  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA02;				/* ���[�^���J���O�R  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST02;				/* ���[�^���J���O�R  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA02;				/* ���[�^���J���O�R  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST02;				/* ���[�^���J���O�R  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA03;				/* ���[�^���J���O�S  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST03;				/* ���[�^���J���O�S  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA03;				/* ���[�^���J���O�S  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST03;				/* ���[�^���J���O�S  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA04;				/* ���[�^���J���O�T  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST04;				/* ���[�^���J���O�T  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA04;				/* ���[�^���J���O�T  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST04;				/* ���[�^���J���O�T  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA05;				/* ���[�^���J���O�U  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST05;				/* ���[�^���J���O�U  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA05;				/* ���[�^���J���O�U  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST05;				/* ���[�^���J���O�U  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA06;				/* ���[�^���J���O�V  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST06;				/* ���[�^���J���O�V  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA06;				/* ���[�^���J���O�V  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST06;				/* ���[�^���J���O�V  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA07;				/* ���[�^���J���O�W  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST07;				/* ���[�^���J���O�W  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA07;				/* ���[�^���J���O�W  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST07;				/* ���[�^���J���O�W  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA08;				/* ���[�^���J���O�X  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST08;				/* ���[�^���J���O�X  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA08;				/* ���[�^���J���O�X  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST08;				/* ���[�^���J���O�X  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA09;				/* ���[�^���J���P�O  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST09;				/* ���[�^���J���P�O  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA09;				/* ���[�^���J���P�O  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST09;				/* ���[�^���J���P�O  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA10;				/* ���[�^���J���P�P  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST10;				/* ���[�^���J���P�P  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA10;				/* ���[�^���J���P�P  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST10;				/* ���[�^���J���P�P  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA11;				/* ���[�^���J���P�Q  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST11;				/* ���[�^���J���P�Q  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA11;				/* ���[�^���J���P�Q  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST11;				/* ���[�^���J���P�Q  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA12;				/* ���[�^���J���P�R  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST12;				/* ���[�^���J���P�R  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA12;				/* ���[�^���J���P�R  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST12;				/* ���[�^���J���P�R  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA13;				/* ���[�^���J���P�S  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST13;				/* ���[�^���J���P�S  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA13;				/* ���[�^���J���P�S  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST13;				/* ���[�^���J���P�S  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA14;				/* ���[�^���J���P�T  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST14;				/* ���[�^���J���P�T  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA14;				/* ���[�^���J���P�T  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST14;				/* ���[�^���J���P�T  OFF�i�p  ����	*/
	extern	U2b	SVP_RCAMON_SA15;				/* ���[�^���J���P�U  ON�i�p  �p�x	*/
	extern	U2b	SVP_RCAMON_ST15;				/* ���[�^���J���P�U  ON�i�p  ����	*/
	extern	U2b	SVP_RCAMOF_SA15;				/* ���[�^���J���P�U  OFF�i�p  �p�x	*/
	extern	U2b	SVP_RCAMOF_ST15;				/* ���[�^���J���P�U  OFF�i�p  ����	*/

	extern	U2b	SVP_SMPMAX_CNT2		;// �����ݸށ@�ő��(SIT)
	extern	U2b	SVP_SMPCYC_TIM2		;// �����ݸށ@����(SIT)

	extern	U2b	SVP_MOTREP_STGS			;//�J��Ԃ��J�n�s��
	extern	U2b	SVP_MOTREP_STGE			;//�J��Ԃ��I���s��
	extern	U2b	SVP_MOTREP_SPD			;//�J��Ԃ��߂葬�x
	extern	U2b	SVP_MOTREP_CNT			;//�J��Ԃ���

	extern	U2b	SVP_ROTCAM_ONR			;//۰�ض� ON�s�� ��߰Ė߂�
	extern	U2b	SVP_ROTCAM_OFR			;//۰�ض� OFF�s�� ��߰Ė߂�
	extern	U2b	SVP_EJECAM_ONR			;//��ު�� ON�s�� ��߰Ė߂�
	extern	U2b	SVP_EJECAM_OFR			;//��ު�� OFF�s�� ��߰Ė߂�
	extern	U2b	SVP_MISCAM_ONR			;//н̨���  ON�s�� ��߰Ė߂�
	extern	U2b	SVP_MISCAM_OFR			;//н̨���  OFF�s�� ��߰Ė߂�

	extern	U2b	SVP_MOT_FIX				;//��葬�x�̈� �s��BIT���


//;	***********************************************************
//;	***		�����֘A				***
//;	***********************************************************

//;	=== 2014/04/16 SHIMA ===
	extern	U2b	PVP_CKAGL_OVBIT	;//�ԕ\��(BIT0~BIT9)
	extern	U2b	PVP_CKLMT_AGLTOP[10]		;//

//;	=== 2014/08/27 ===	SHIMA
	extern	U2b	PVP_WTJUD_SNO		;//�ײ�ގ����ҋ@�@�\  �ҋ@����ʒu�i�s���j
	extern	U2b	PVP_WTJUD_AGL		;//�ײ�ގ����ҋ@�@�\  �ҋ@����ʒu�i�p�x�j
	extern	U4b	PVP_WTJUD_POS		;//�ײ�ގ����ҋ@�@�\  �ҋ@����ʒu�i�ʒu�j

//;	=== 2014/09/02 ===	SHIMA
	extern	U2b	PVP_SINKAKU_UPDN1	;//BITn�F1=۰�ض�n��ON�i�p���������͈͂ɂ���B
	extern	U2b	PVP_SINKAKU_UPDN2	;//BITn�F1=۰�ض�n��ON�i�p���������͈͂ɂ���B

//;	==== 2015/07/03[���x�ЯĐ��\��] ====
//;	==== 2015/07/07[���x�ЯđΏۍs��] ====
	extern	U2b	PVP_CKSPD_LMBIT;			//���\��(BIT0~BIT9 BIT15:�ߑ��x)
	extern	U2b	PVP_CKSPD_STPBT;				//���x�ЯđΏۍs�� BIT0~BIT9,BIT15(�����Ώۍs��)


//;	=== 2021-06-24[H2W-CE3:2020-08-11 �޲ʲ�ANS�ޯ�]=======
	extern	U4b	PVP_ATSLID_OBJ1		;// �X���C�h�������ߐݒ�l�i���ݓ��쒆�j0.001mm��ANS�ޯ� [1A28]
