;	*******************************************************************
;	***								***
;	***								***
;	***								***
;	***	cpuA(sh4)-Servo-Cpu(sh4) I/F Dual Port RAM		***
;	***								***
;	***								***
;	***								***
;	*******************************************************************
;	���̃t�@�C����sh4�̃A�Z���u���\�[�X�ɃC���N���[�h����
;	���̒��ŁA���A�h���X������t����			
;	���̂ł�dpram�̃I�t�Z�b�g�A�h���X���`����
;	���̃t�@�C����extern�錾�Ƃ���
;	dp_.ext(�����חp)
;	dp_.h(c���꿰��p)
;

;	*******************************************
;	***					***
;	***					***
;	*******************************************
		.ORG	H'0000		;
_COP2DPRAM_TOP:

_COP2_CPUA_COD1		.SRES	4	;CPUA-->COP2 WR:12345678//COP2 0CLR
_COP2_CPUA_COD2		.SRES	4	;CPUA-->COP2 WR:9ABCEDF0//COP2 0CLR
_COP2_COP2_COD1		.SRES	4	;COP2-->CPUA WR:NOT 12345678
_COP2_COP2_COD2		.SRES	4	;COP2-->CPUA WR:NOT 9ABCDEF0

;	----------- 16byte 
_DEBUG_COP2_SIG1	.SRES	2	;
_DEBUG_COP2_SIG2	.SRES	2	;

_COP2_PLS_OUTF		.SRES	2	;
_COP2_CPUA_SV_STEP	.SRES	2	;
_COP2_CPUB_SV_STEP	.SRES	2	;
_COP2_CPUC_SV_STEP	.SRES	2	;

;	*******************************************
;	***					***
;	***	SH2<->SH4�@���޼���		***
;	***					***
;	*******************************************
		.ORG	H'0020
_COP2_HS_SVCHG_B_TO_A	.SRES	4	;
_COP2_HS_SVCHG_A_TO_B	.SRES	4	;

_COP2_HS_PVP_TAKIKI_FLG	.SRES	2	;
_COP2_HS_PVP_LOTCNT_FLG	.SRES	2	;

;	==== 2003-07-09 ===
_COP2_CMD_1CYCLE_DSP1	.SRES	2	;
_COP2_CMD_DAIPOS_DSP1	.SRES	2	;

	.ALIGN	4			;
_COP2_PSD_ORG_PLS1	.SRES	4	;ORIGIN DATA(FUNUC)
_COP2_PSD_ORG_PLS2	.SRES	4	;ORIGIN DATA(FUNUC)
_COP2_PSD_ORG_PLS_CMD1	.SRES	2	;
_COP2_PSD_ORG_PLS_CMD2	.SRES	2	;

;	==== 2013-01-10 =============
_COP2_PV_CH2_OUTPUTF	.SRES	2		;3C,3D
;3E,3F ����2BYTE�܂�


;	***************************************************
;	***	4/2BYTE  �ޯ����ߕԂ��̈�(64b)		***
;	***************************************************
		.ORG	H'0040
_COP2_SVB_RNAORG_PLS1	.SRES	4		;�Ʊ��ʒu��ٽ
						;�\��4byte�̈�
_COP2_SVB_DYHITO_POS	.SRES	4		;2003-07-09 �޲ʲ�(�����ʒu)
_COP2_SVB_SLIDE_POS	.SRES	4		;2003-07-09 ���Y�����ʒu

_COP2_SVB_BAKORG_PLS1	.SRES	4		;�Ʊ��ʒumm
_COP2_SVB_BAKORG_PLS2	.SRES	4		;�Ʊ��ʒumm

;	***************************************************
;	***	�������Ұ��̈�	4/2BYTE�̈�		***
;	***************************************************
		.ORG	H'0060
_COP2_SVP_RNADIR_SEL1		.SRES	2	;�Ʊ�ݻ�ɐ�
_COP2_SVP_INCDIR_SEL1		.SRES	2	;PG�ɐ�
_COP2_SVP_INCPLS_1REV		.SRES	2	;PG1��]����ٽ�I��
_COP2_SVP_INCPLS_HOSN		.SRES	2	;PG�␳N�@Ӱ�N��
_COP2_SVP_INCPLS_HOSM		.SRES	2	;PG�␳M�@��ݸ�p�xM
_COP2_SVP_MOTRPM_MAXM		.SRES	2	;Ӱ��ő��]��

	.ALIGN	4				;
_COP2_SVP_MOTMAX_FREQ		.SRES	4	;Ӱ��ő厞�w�ߎ��g��
_COP2_SVP_RNAORG_POS1		.SRES	4	;�@�B���_����
_COP2_SVP_RNAPOS_MAXP		.SRES	4	;�@�B���
_COP2_SVP_RNAPOS_MINP		.SRES	4	;�@�B����
_COP2_SVP_UPAREA_JUDG		.SRES	4	;�㎀�_����͈�
_COP2_SVP_DNAREA_JUDG		.SRES	4	;���]�ݒ�s�͈�



_COP2_SVP_DNDINC_SPD1		.SRES	2	;�i�摬�x	
_COP2_SVP_UPAREA_SPD1		.SRES	2	;�ҋ@�_���A���x	
_COP2_SVP_STDINC_SPD1		.SRES	2	;�������x	
_COP2_SVP_REVDAT_SPD1		.SRES	2	;�\�����x�P	(�N���[�v���x)
_COP2_SVP_REVDAT_SPD2		.SRES	2	;�\�����x�Q	(���N��INCHING)
_COP2_SVP_REVDAT_SPD3		.SRES	2	;�\�����x�R	
_COP2_SVP_TEPDAT_SPD1		.SRES	2	;�蓮��ٻ���x	
_COP2_SVP_TEPLAT_DAT1		.SRES	2	;�蓮��ٻ��{��	
_COP2_SVP_TEPLAT_DAT2		.SRES	2	;�蓮��ٻ���{��	

_COP2_SVP_INCPOS_KP01		.SRES	2	;PG�ʒu���޲�
_COP2_SVP_RNAPOS_KP01		.SRES	2	;�Ʊ�ʒu���޲�
_COP2_SVP_ACCLAT_TIM1		.SRES	2	;����������
_COP2_SVP_SSCURV_TIM1		.SRES	2	;�r������
_COP2_SVP_UPAREA_INP1		.SRES	2	;�㎀�_���߼޼��
_COP2_SVP_DNAREA_INP1		.SRES	2	;�����_���߼޼��
_COP2_SVP_OBJARA_INP1		.SRES	2	;�ڕW�ʒu���߼޼��
_COP2_SVP_INPPOS_TIM1		.SRES	2	;���߼޼����������
_COP2_SVP_ARACHK_LNG1		.SRES	2	;��^�����_�ʉߔ����
_COP2_SVP_UPAREA_DIG1		.SRES	2	;��]���ҋ@�_(�㎀�_)

_COP2_SVP_INCHEN_ELNG		.SRES	2	;PG�΍��ُ핝
_COP2_SVP_INCENC_ELNG		.SRES	2	;PG-ENC��v�� 0.1�x
_COP2_SVP_INCRNA_ELNG		.SRES	2	;PG-�Ʊ��v��
_COP2_SVP_INCSTP_ELNG		.SRES	2	;PG��~�ُ��
_COP2_SVP_RNASTP_ELNG		.SRES	2	;�Ʊ��~�ُ��
_COP2_SVP_INCREV_ELNG		.SRES	2	;PG�t�]�ُ��
_COP2_SVP_RNAREV_ELNG		.SRES	2	;�Ʊ�t�]�ُ��
_COP2_SVP_DAIHAI_LNG1		.SRES	2	;�޲ʲĕ␳��r�l(��)
_COP2_SVP_DAIHAI_LNG2		.SRES	2	;�޲ʲĕ␳��r�l(��)
_COP2_SVP_DAIHAI_LNG3		.SRES	2	;�޲ʲĕ␳��r�l(��)

_COP2_SVP_AMPERR_VLT1		.SRES	2	;�ߕ��דd��1
_COP2_SVP_AMPERR_TIM1		.SRES	2	;�ߕ��׎���1
_COP2_SVP_AMPERR_VLT2		.SRES	2	;�ߕ��דd��2
_COP2_SVP_AMPERR_TIM2		.SRES	2	;�ߕ��׎���2
_COP2_SVP_AMPERR_VLT3		.SRES	2	;�ߕ��דd��3
_COP2_SVP_AMPERR_TIM3		.SRES	2	;�ߕ��׎���3

;	==== 2002-08-08 ==
_COP2_SVP_CNT_TIM			.SRES	2	;�A���^�C�}
_COP2_SVP_CNT_CNT			.SRES	2	;�A���J�E���^
_COP2_SVP_BREAK_DIG			.SRES	2	;��ڰ��p�x   0.1�x
_COP2_SVP_BREAK_TIM1			.SRES	2	;�u���[�L�^�C�}�ݒ�
_COP2_SVP_WT_DIG1			.SRES	2	;�ҋ@�_�I��1
_COP2_SVP_WT_DIG2			.SRES	2	;�ҋ@�_�I��2
_COP2_SVP_WT_DIG3			.SRES	2	;�ҋ@�_�I��3
_COP2_SVP_MOTWT_TIM			.SRES	2	;�N���ۏ؎���
_COP2_SVP_PSMOD_SEL			.SRES	2	;PSID�@Ӱ�ޑI��

;	==== 2002-08-21 ==
	.ALIGN	4				;
_COP2_SVP_RNA_STLORK			.SRES	4	;
_COP2_SVP_OUTPLS_HOSA		.SRES	2	;
_COP2_SVP_OUTPLS_HOSB		.SRES	2	;
_COP2_SVP_UPHOLD_DIG			.SRES	2	;
_COP2_SVP_MACINE_SEL1		.SRES	2	;

;	==== 2003-01-27 ==
	.ALIGN	4				;
_COP2_SVP_NEG_OFS_LNG		.SRES	4	;���]��������(0.001mm �������Ұ�)
_COP2_SVP_AMP100P_VLT		.SRES	2	;AMP100%�������̓d���l 0~10.0v(�������Ұ�)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	.ALIGN	4				;
_COP2_SVP_LSAABN_AGL1		.SRES	4	;//LSA�ُ팟�m�̊p�x1
_COP2_SVP_LSAABN_AGL2		.SRES	4	;//LSA�ُ팟�m�̊p�x2
_COP2_SVP_PLSALO_PLS			.SRES	2	;//�p���T�{����
_COP2_SVP_PLSAHI_PLS			.SRES	2	;//�p���T�{����

;	***************************************************
;	***	�ׯ������ʐݒ�1 4/2BYTE�̈�		***
;	***************************************************
	.ALIGN	4				;
_COP2_SVP_OBJECT_POS_TOP:
_COP2_SVP_OBJECT_PS01		.SRES	4	;01�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS02		.SRES	4	;02�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS03		.SRES	4	;03�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS04		.SRES	4	;04�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS05		.SRES	4	;05�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS06		.SRES	4	;06�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS07		.SRES	4	;07�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS08		.SRES	4	;08�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS09		.SRES	4	;09�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS10		.SRES	4	;10�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS11		.SRES	4	;11�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS12		.SRES	4	;12�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS13		.SRES	4	;13�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS14		.SRES	4	;14�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS15		.SRES	4	;15�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS16		.SRES	4	;16�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS17		.SRES	4	;17�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS18		.SRES	4	;18�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS19		.SRES	4	;19�i�ږڕW�ʒu
_COP2_SVP_OBJECT_PS20		.SRES	4	;20�i�ږڕW�ʒu

_COP2_SVP_OBJECT_DIG_TOP:				;01�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG01		.SRES	2	;01�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG02		.SRES	2	;02�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG03		.SRES	2	;03�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG04		.SRES	2	;04�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG05		.SRES	2	;05�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG06		.SRES	2	;06�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG07		.SRES	2	;07�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG08		.SRES	2	;08�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG09		.SRES	2	;09�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG10		.SRES	2	;10�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG11		.SRES	2	;�\��11�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG12		.SRES	2	;�\��12�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG13		.SRES	2	;�\��13�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG14		.SRES	2	;�\��14�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG15		.SRES	2	;�\��15�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG16		.SRES	2	;�\��16�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG17		.SRES	2	;�\��17�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG18		.SRES	2	;�\��18�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG19		.SRES	2	;�\��19�i�ڊp�x�ʒu
_COP2_SVP_OBJECT_DG20		.SRES	2	;�\��20�i�ڊp�x�ʒu

_COP2_SVP_OBJECT_SPD_TOP:				;01�i�ڈړ����x
_COP2_SVP_OBJECT_SP01		.SRES	2	;01�i�ڈړ����x
_COP2_SVP_OBJECT_SP02		.SRES	2	;02�i�ڈړ����x
_COP2_SVP_OBJECT_SP03		.SRES	2	;03�i�ڈړ����x
_COP2_SVP_OBJECT_SP04		.SRES	2	;04�i�ڈړ����x
_COP2_SVP_OBJECT_SP05		.SRES	2	;05�i�ڈړ����x
_COP2_SVP_OBJECT_SP06		.SRES	2	;06�i�ڈړ����x
_COP2_SVP_OBJECT_SP07		.SRES	2	;07�i�ڈړ����x
_COP2_SVP_OBJECT_SP08		.SRES	2	;08�i�ڈړ����x
_COP2_SVP_OBJECT_SP09		.SRES	2	;09�i�ڈړ����x
_COP2_SVP_OBJECT_SP10		.SRES	2	;10�i�ڈړ����x
_COP2_SVP_OBJECT_SP11		.SRES	2	;�\��11�i�ڈړ����x
_COP2_SVP_OBJECT_SP12		.SRES	2	;�\��12�i�ڈړ����x
_COP2_SVP_OBJECT_SP13		.SRES	2	;�\��13�i�ڈړ����x
_COP2_SVP_OBJECT_SP14		.SRES	2	;�\��14�i�ڈړ����x
_COP2_SVP_OBJECT_SP15		.SRES	2	;�\��15�i�ڈړ����x
_COP2_SVP_OBJECT_SP16		.SRES	2	;�\��16�i�ڈړ����x
_COP2_SVP_OBJECT_SP17		.SRES	2	;�\��17�i�ڈړ����x
_COP2_SVP_OBJECT_SP18		.SRES	2	;�\��18�i�ڈړ����x
_COP2_SVP_OBJECT_SP19		.SRES	2	;�\��19�i�ڈړ����x
_COP2_SVP_OBJECT_SP20		.SRES	2	;�\��20�i�ڈړ����x

_COP2_SVP_OBJECT_TIM_TOP				;01�i�ڒ�~����
_COP2_SVP_OBJECT_TM01		.SRES	2	;01�i�ڒ�~����
_COP2_SVP_OBJECT_TM02		.SRES	2	;02�i�ڒ�~����
_COP2_SVP_OBJECT_TM03		.SRES	2	;03�i�ڒ�~����
_COP2_SVP_OBJECT_TM04		.SRES	2	;04�i�ڒ�~����
_COP2_SVP_OBJECT_TM05		.SRES	2	;05�i�ڒ�~����
_COP2_SVP_OBJECT_TM06		.SRES	2	;06�i�ڒ�~����
_COP2_SVP_OBJECT_TM07		.SRES	2	;07�i�ڒ�~����
_COP2_SVP_OBJECT_TM08		.SRES	2	;08�i�ڒ�~����
_COP2_SVP_OBJECT_TM09		.SRES	2	;09�i�ڒ�~����
_COP2_SVP_OBJECT_TM10		.SRES	2	;10�i�ڒ�~����
_COP2_SVP_OBJECT_TM11		.SRES	2	;11�i�ڒ�~����
_COP2_SVP_OBJECT_TM12		.SRES	2	;12�i�ڒ�~����
_COP2_SVP_OBJECT_TM13		.SRES	2	;13�i�ڒ�~����
_COP2_SVP_OBJECT_TM14		.SRES	2	;14�i�ڒ�~����
_COP2_SVP_OBJECT_TM15		.SRES	2	;15�i�ڒ�~����
_COP2_SVP_OBJECT_TM16		.SRES	2	;16�i�ڒ�~����
_COP2_SVP_OBJECT_TM17		.SRES	2	;17�i�ڒ�~����
_COP2_SVP_OBJECT_TM18		.SRES	2	;18�i�ڒ�~����
_COP2_SVP_OBJECT_TM19		.SRES	2	;19�i�ڒ�~����
_COP2_SVP_OBJECT_TM20		.SRES	2	;20�i�ڒ�~����

;	***************************************************
;	***	�ׯ������ʐݒ�2 4/2BYTE�̈�		***
;	***************************************************
	.ALIGN	4				;
_COP2_SVP_DAIHAI_ORG0		.SRES	4	;�_�C�n�C�g
_COP2_SVP_MRTION_SEL1		.SRES	2	;��]����
_COP2_SVP_MTSTEP_MAXM		.SRES	2	;�i��
	.ALIGN	4				;
_COP2_SVP_UPAREA_POS0		.SRES	4	;�ҋ@�_�ʒu
_COP2_SVP_UPAREA_DIG0		.SRES	2	;�ҋ@�_�p�x
_COP2_SVP_UPAREA_SPD0		.SRES	2	;����x
_COP2_SVP_UPAREA_TIM0		.SRES	2	;�ҋ@����
_COP2_SVP_DNAREA_INP0		.SRES	2	;�����_���߼޼��(2002-06-28)
_COP2_SVP_OBJARA_INP0		.SRES	2	;�ڕW�ʒu���߼޼��(2002-06-28)
_COP2_SVP_DAIHSA_LENG		.SRES	2	;�޲ʲĕ␳����

;	==== 2002-08-08======
	.ALIGN	4				;
_COP2_SVP_SLID_POS1		.SRES	4	;�ײ�ވʒu�@���Y
_COP2_SVP_SLID_POS2		.SRES	4	;�ײ�ވʒu�@�i��1
_COP2_SVP_SLID_POS3		.SRES	4	;�ײ�ވʒu�@�i��2

;	===== 2002-08-29==
	.ALIGN	4				;
_COP2_SVP_ATSLID_OBJ1	.SRES		4	; �X���C�h�������ߐݒ�l�i���ݓ��쒆�j0.001mm
_COP2_SVP_ATSLID_DNOBJ1	.SRES		2	; �X���C�h�������߁@���~��~ 0~99
_COP2_SVP_ATSLID_UPOBJ1	.SRES		2	; �X���C�h�������߁@�㏸��~ "
_COP2_SVP_ATSLID_BAKLNG	.SRES		2	; �X���C�h�������߁@�߂��   "
_COP2_SVP_ATSLID_COEF1	.SRES		2	; �X���C�h�������߁@���䐸�x "

;	===== 2004-06-08�@=====
_COP2_SVP_KAJYUU_PRS1	.SRES	2		;�׏d�␳ 1Kn (2004-06-08)
_COP2_SVP_KAJYUU_OBJP	.SRES	2		;�׏d�ڕW�l 1Kn(2004-07-01)
_COP2_SVP_KAJYUU_PV1		.SRES	2		;�ő�׏d(��߼�݂̎�����C/B�̐ݒ�Ƃ��ēn��)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
_COP2_PVP_KAJLIV_LFT		.SRES	2		;//�׏d���iTON�j(1word)
_COP2_PVP_KAJLIV_TTL		.SRES	2		;//�׏d���iTON�j(1word)
_COP2_PVP_KAJLIV_RIH		.SRES	2		;//�׏d���iTON�j(1word)


;	=====2006-07-24(����ײ��) ====
_COP2_SVP_OVERLIDE_COF	.SRES	2		;0,1~127%
_COP2_SVP_DND_STOPDIG1	.SRES	2		;�i���~�p�x 0~358.0
;;[]
;;[];	=====2006-07-24(�׏d�␳) ====
;;[]_COP2_SVP_KJSTR_STEP1	.SRES	2		;0,1~�H�� 
;;[]_COP2_SVP_KJSTR_DIG1		.SRES	2		;359.0
;;[]_COP2_SVP_KJEND_STEP1	.SRES	2		;0,1~�H��
;;[]_COP2_SVP_KJEND_DIG1		.SRES	2		;359.0
_COP2_PVP_ARA1_KAJ_R		.SRES	2		;OPTION ��ԍő�׏d
_COP2_PVP_ARA1_KAJ_L		.SRES	2		;OPTION ��ԍő�׏d
_COP2_PVP_ARA1_KAJ_T		.SRES	2		;OPTION ��ԍő�׏dTOTAL�̂ݎg�p

;	=====2006-10-13(COP2�֌W) ====
	.ALIGN	4
;;[]_COP2_PVP_ORGRNA_MOV1		.SRES	4		;�Ʊ�ړ��ʎ���1
;;[]_COP2_PVP_ORGRNA_MOV2		.SRES	4		;�Ʊ�ړ��ʎ���2
;;[]_COP2_PVP_ORGSTRK_LEG1		.SRES	4		;��۰�1����
;;[]_COP2_PVP_ORGSTRK_LEG2		.SRES	4		;��۰�2����
;;[]_COP2_PVP_BAKORG_PLS1		.SRES	4		;�ޯ����ߎ���
;;[]_COP2_PVP_BAKORG_PLS2		.SRES	4		;�ޯ����ߎ���
;;[]_COP2_PVP_RENIA_POS1		.SRES	4		;�Ʊ����1����
;;[]_COP2_PVP_RENIA_POS2		.SRES	4		;�Ʊ����2����
;;[]_COP2_PVP_360_DEG		.SRES	2		;360�x�ݺ��ފp�x
;;[]_COP2_PVP_PG_DEG1		.SRES	2		;PG�p�x1
;;[]_COP2_PVP_PG_DEG2		.SRES	2		;PG�p�x2
;;[]_COP2_PVP_ZURE_PLS		.SRES	2		;���Խ�ڎ���
;;[]_COP2_PVP_ZURE_RNA		.SRES	2		;���Խ���Ʊ

	.ALIGN	4
;;[]_COP2_SVP_ORGSOK_PLS		.SRES	4		;���_������ٽ
;;[]_COP2_SVP_ORGCAL_DAT1		.SRES	4		;���Z�W��1
;;[]_COP2_SVP_ORGCAL_DAT2		.SRES	4		;���Z�W��2
;;[]_COP2_SVP_ORGCAL_DAT3		.SRES	4		;���Z�W��3
;;[]_COP2_SVP_ORGCAL_DAT4		.SRES	4		;���Z�W��4
;;[]_COP2_SVP_ORGCAL_DAT5		.SRES	4		;���Z�W��5
;;[]_COP2_SVP_ORGCAL_DAT6		.SRES	4		;���Z�W��6
;;[]_COP2_SVP_ORGSTRK_LEN1		.SRES	4		;��۰�1
;;[]_COP2_SVP_ORGSTRK_LEN2		.SRES	4		;��۰�2
;;[]_COP2_SVP_RNAORGMEM_LEG1	.SRES	4		;�Ʊ���_1���L��
;;[]_COP2_SVP_RNAORG_PLS1		.SRES	4		;�ޯ����ߎ���
;;[]_COP2_SVP_RNAORGMEM_LEG2	.SRES	4		;�Ʊ���_2���L��
;;[]_COP2_SVP_RNAORG_PLS2		.SRES	4		;�ޯ����ߎ���
;;[]_COP2_SVP_RNAORG_SIN1		.SRES	2		;�ޯ����ߎ�������
;;[]_COP2_SVP_RNAORG_SIN2		.SRES	2		;�ޯ����ߎ�������
;;[]_COP2_SVP_ORGRUP_DEG		.SRES	2		;���_�E��ԏ�
;;[]_COP2_SVP_ORGRDN_DEG		.SRES	2		;���_�E��ԉ�
;;[]_COP2_SVP_ORGLUP_DEG		.SRES	2		;���_����ԏ�
;;[]_COP2_SVP_ORGLDN_DEG		.SRES	2		;���_����ԉ�
;;[]_COP2_SVP_ORGMEM_DEG1		.SRES	2		;�p�x1��
;;[]_COP2_SVP_ORGMEM_DEGS1		.SRES	2		;�p�x1���@ON/OFF
;;[]_COP2_SVP_ORGMEM_DEG2		.SRES	2		;�p�x2��
;;[]_COP2_SVP_ORGMEM_DEGS2		.SRES	2		;�p�x2���@ON/OFF
;;[]_COP2_SVP_ORGMPL_SEL1		.SRES	2		;����ٻ�I��1���@ON/OFF
;;[]_COP2_SVP_ORGMPL_SEL2		.SRES	2		;����ٻ�I��2���@ON/OFF
;;[]_COP2_SVP_HOSRAG_PLS1		.SRES	2		;���ԕ␳�͈͂P
;;[]_COP2_SVP_HOSRAG_PLS2		.SRES	2		;���ԕ␳�͈͂Q�i���шُ�j
;;[]_COP2_SVP_HOSEI_SPD		.SRES	2		;�␳���x
;;[]_COP2_SVP_MANSAM_LEN		.SRES	2		;�蓮������
;;[]_COP2_SVP_DANSAM_LEN		.SRES	2		;�i�掚����
;;[]_COP2_SVP_RUNSAMER_LEN1		.SRES	2		;�^�]�����ُ�P�@���g�p�ɕύX
;;[]_COP2_SVP_RUNSAMER_LEN2		.SRES	2		;�^�]�����ُ�Q
;;[]_COP2_SVP_MANSAMER_PLS		.SRES	2		;�蓮�����ُ�
;;[]_COP2_SVP_RUNSAMER_PLS		.SRES	2		;�^�]�����ُ�



;	*******************************************
;	***					***
;	***		�\��			***
;	***	�ʐM������ފ֌W			***
;	*******************************************
;	***************************
;	***	���ޯ����	***
;	***************************
	.ALIGN	4

;	*******************************************
;	***		���� 4/2BYTE�̈�	***
;	*******************************************
	.ALIGN	4
;;[]_COP2_PVP_RNAORG_PLS1		.SRES	4	;�Ʊ��ʒu��ٽ(�ޯ����ߐ�p)
;;[]_COP2_PVP_NOW_POSI000		.SRES	4	;�����_�����ʒu(�\���p ���_�����܂ł�ABS�l)
;;[]_COP2_PVP_RENIA_POSI0		.SRES	4	;���j�A�Z���T���݈ʒu(���\���p ABS�l �����g���Ă��Ȃ�?HMI��)
;;[]_COP2_PVP_NOW_ANGLE00		.SRES	2	;SH2->SH4�@360�x�ݺ���(CHEAK�p)
;;[]_COP2_PVP_CYCLE_TIME0		.SRES	2	;�T�C�N�����ԕ\���p
;;[];	----- �ǉ�2002/07/02 ---
;;[]_COP2_PVP_CYCLE_SPM1			.SRES	2	;�T�C�N�����x�\���p
;;[]_COP2_PVP_DISP_SPM2			.SRES	2	;�������`���h��Ԃ��ɂ���ׂ̑��x(�P�ʕs��)
;;[]_COP2_PVP_NOW_ANGLE_RNA		.SRES	2	;���݊p�x0.1�xHEX(�Ʊ���ق����1�x�P�� SH4->SH2)(��ʕ\���p)
;;[]_COP2_PVP_DYHITO_HOSLNG		.SRES	2	;�޲ʲĕ␳�� 1um(0.001mm) +/-
;;[]	.ALIGN	4				;
;;[]_COP2_PVP_DYHITO_POS			.SRES	4	;�޲ʲĎ��� ���Y������ʕ\���l 
;;[]						;2003-07-09 �����ʒu�̂܂�
;;[]_COP2_PVP_SLIDE_POS		.SRES	4	;�ײ�ވʒu�E�޲ʲĂ��܂߂��ʒu(�ׯ��͖��g�p)
;;[]						;2003-07-09 ���Y�����ʒu
;;[]_COP2_PVP_TAIKITEN_POS		.SRES	2	;�ҋ@�_�p�x�\���i�`��p�j
;;[]
;;[];	----- �ǉ�2002/08/01 ---
;;[]	.ALIGN	4				;
;;[]_COP2_PVP_RNA_STLORK			.SRES	4	;��۰�����
;;[]_COP2_PVP_STOP_TIM			.SRES	2	;�į��ݸ���� 1msec data
;;[]_COP2_PVP_BREAK_DIG			.SRES	2	;��ڰ��p�x   0.1�x
;;[]_COP2_PVP_BREAK_TIM1			.SRES	2	;
;;[]
;;[]
;;[];	========== 2003-01-27 �ߕ��׎����ǉ�====
;;[]_COP2_PVP_POWER_MONI		.SRES	2	;ADR=3854
;;[]
;	========= 2003-02-04 ======
_COP2_PVP_CPUA_TEPPLS		.SRES	2	;
_COP2_PVP_CPUA_ANAIN		.SRES	2	;

	.ALIGN	4			;
_COP2_PVP_ENC_PLS_SPD	.SRES	4	;SHIN
_COP2_PVP_OUT_PLS_SPD	.SRES	4	;SHIN
_COP2_PVP_ABS_ENC_SPD	.SRES	4	;ABS
_COP2_PVP_ABS_OUT_SPD	.SRES	4	;ABS
_COP2_PVP_ENC_SPD_PER	.SRES	2	;
_COP2_PVP_OUT_SPD_PER	.SRES	2	;
_COP2_PVP_BRK_ENC_SPD	.SRES	2	;
_COP2_PVP_BRK_OUT_SPD	.SRES	2	;
_COP2_PVP_ENC_SPD_DIR	.SRES	2	;
_COP2_PVP_OUT_SPD_DIR	.SRES	2	;


;	*******************************************
;	***					***
;	***	2002-08-29			***
;	***	�Œ����(�ް�ޮݕ\��)		***
;	*******************************************
	.ALIGN	4
_COP2_COP2_PVP_CB_A_VER		.SRES	2*6	;ASCII�ް� (1WORD�ŷ�׸����� 6char) SH4-->
_COP2_COP2_PVP_CB_B_VER		.SRES	2*6	;ASCII�ް� (6char) SH2-->

;	======= 2003-01-27 ���Ұ��ް�ޮݒǉ� =====
_COP2_PVP_PAR_A_VER		.SRES	2	;���Ұ��ް�ޮ� HEX data
_COP2_PVP_TBL_A_VER		.SRES	2	;�ݻ��ð��ٔԍ�1~99 HEX data
_COP2_PVP_PAR_A_CHAR		.SRES	2	;���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
_COP2_PVP_TBL_A_CHAR		.SRES	2	;�ݻ��ð��ٔԍ�()


;	=== 2004-01-27 ERR-INFO ===
_COP2_ERR_INFO_CPUA_FLG	.SRES	2	;CPUA=>WRITE 55AA CPUB=>0CLR
	.ALIGN	4						;
_COP2_ERR_INFO_CPUA_TOP	.SRES	_CB_ERR_INFO_MEM	;80	;(CPUA��DPRAM�o�R)<4�̔{��>

;	*******************************************
;	***					***
;	***	SH2��SH4�@���޼���		***
;	***					***
;	*******************************************
	.ALIGN	4
_COP2_PVX_RNA_INDAT		.SRES	4	;��	SH4-->SH2 ��
_COP2_PVX_RNA_POSD1		.SRES	4	;�ϊ�	SH4-->SH2 �ɐ��E�̾�ĕ�
_COP2_PVX_RNA_POSD2		.SRES	4	;�ϊ�	SH4-->SH2 0.5um->1mm+���_
_COP2_PVX_RNA_POSDT		.SRES	4	;����p
_COP2_PVX_RNA_DIGDT		.SRES	4	;�p�x	360.0�x���x RNA�ݻ���狁�܂�p�x
_COP2_PVX_RNA_PLS_P		.SRES	4	;RNA�ݻ���狁�܂�̾����ٽP

;	----------- 2007-02-16(���ʉ�)
_COP2_EMG_CPA_TO_CP2:		.SRES	2	;((((CPUA==>COP2))))
_COP2_EXQ_CPA_TO_CP2:		.SRES	2	;((((CPUA==>COP2))))

_COP2_EMG_CP2_TO_CPA:		.SRES	2	;((((COP2==>CPUA))))
_COP2_EXQ_CP2_TO_CPA:		.SRES	2	;((((COP2==>CPUA))))


_COP2_PVX_SH4_OUTPLS		.SRES	4*2	;8BYTE

_COP2_STEP_NO			.SRES	4	;�H����d��H�����p/ COP2=>CPUA
_COP2_STEP_NO_A			.SRES	4	;�H����d��H�����p/ CPUA=>COP2

_COP2_SH4_POS_STS1		.SRES	2	;��L�M�� SH4==> WRITE SH2 ==>BIT7 CLR
_COP2_SH2_POS_STS1		.SRES	2	;��L�M�� SH2==> WRITE SH4 ==>BIT7 CLR
_COP2_SH4_CMP_STS1		.SRES	2	;(��d���ُ�M�� 203���l      ��)
_COP2_SH2_CMP_STS1		.SRES	2	;(��d���ُ�M�� 273���l      ��)
_COP2_SH4_CMP_STS2		.SRES	2	;(��d���ُ�M�� BIT0�ʒu���� ��)
_COP2_SH2_CMP_STS2		.SRES	2	;(��d���ُ�M�� BIT0�ʒu���� ��)

;	====================================
_COP2_HD_CTRL_REDY	.SRES	2	;���������ɂ����� COP2-->CPUA
_COP2_HD_CTRL_REDY_A	.SRES	2	;���������ɂ����� CPUA-->COP2

_COP2_SH4_HD_CTRL_BUSY	.SRES	2	;NO USED(2008-02-16)
_COP2_SH2_HD_CTRL_BUSY	.SRES	2	;NO USED(2008-02-16)
_COP2_HD_POS_START	.SRES	2	;�N��������
_COP2_HD_POS_START_A	.SRES	2	;�N���������@CPUA==>CPUC

_COP2_HD_SFTY_AUTO	.SRES	2	;AUTO�ɂ�����/���S��H��,�A������[2013-04-14]
_COP2_HD_SFTY_AUTO_A	.SRES	2	;AUTO�ɂ�����/���S��H��,�A������[2013-04-14]
_COP2_HD_NEAR_ZERO	.SRES	2	;Ʊ��ۏ������s������(COP2)
_COP2_HD_NEAR_ZERO_A	.SRES	2	;Ʊ��ۏ������s������(���g�p)
_COP2_HD_CNT_STOP	.SRES	2	;COP2=>CPUA,CPUB  2013-04-14
_COP2_HD_CNT_STOP_A	.SRES	2	;CPUA,CPUB==>COP2 2013-04-14
_COP2_HD_STEP_END	.SRES	2	;�ʒu���ߊ����Ƃ�����(COP2)
_COP2_HD_STEP_END_A	.SRES	2	;�ʒu���ߊ����Ƃ�����(�g�p�ς�)
_COP2_HD_CNT_CNT	.SRES	2	;�A����~���Ȃ��Ŏ��ւ�����[2013-04-14]
_COP2_HD_CNT_CNT_A	.SRES	2	;�A����~���Ȃ��Ŏ��ւ�����[2013-04-14]

;	===== 2002-09-12 SAITO =====
;	SELF CHECK HAND SHAKE FLG
;	===== 2008-09-21 KOMA =====
_CPUA_COP2_SELF_REQ	.SRES	2	;START/CODE _COP2_CPUA_SELF_HAND_FLG; CPUA-->COP2
_CPUA_COP2_SELF_ANS	.SRES	2	;END _COP2_CPUB_SELF_HAND_FLG	    ; COP2-->CPUA

;	===================================
;	===	�e���ނ̽ð���쐬�p	===
;	===================================
;	�^�]�J�n
;	�P�H���J�n
;	�ŏI�H���J�n
;	�I��/
;	==== 2004-03-01 ������ڑ���p���� =====
_COP2_CPU_CTRL_CLK		.SRES	2	;(������ڑ�����ѽ����)


;	=========== 2006-04-10 =========
_COP2_CPUA_SELF2_STR		.SRES	2	;
_COP2_CPUA_SELF2_END		.SRES	2	;
_COP2_CPUA_SELF2_CD1		.SRES	2	;
_COP2_CPUA_SELF2_CD2		.SRES	2	;
_COP2_CPUA_SELF2_CD3		.SRES	2	;
_COP2_CPUA_SELF2_CD4		.SRES	2	;

_COP2_CPUB_SELF2_STR		.SRES	2	;
_COP2_CPUB_SELF2_END		.SRES	2	;
_COP2_CPUB_SELF2_CD1		.SRES	2	;
_COP2_CPUB_SELF2_CD2		.SRES	2	;
_COP2_CPUB_SELF2_CD3		.SRES	2	;
_COP2_CPUB_SELF2_CD4		.SRES	2	;



;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_SEQ_DP_024		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_028		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_029		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_032		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_033		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_050		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_056		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_109		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_340		.SRES	30*2		;CMD(C/B)340~369�@2007-04-05
_COP2_SEQ_DP_200		.SRES	70*2		;STS�F204�ȊO�g�p���Ă��Ȃ��A�ʏ��T�ݸ�̈�o�R


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	***		COP2->SIT4		***
;	***		������		***
;	***		RNA,PG,POS		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_CH1RNA_INDAT	.SRES	4			;��
_COP2_PG1_PLS		.SRES	4			;
_COP2_OUT1_PLS		.SRES	2			;���o�p���X

	.ALIGN	4					;
_COP2_CH2RNA_INDAT	.SRES	4			;��
_COP2_PG2_PLS		.SRES	4			;PG
_COP2_OUT2_PLS		.SRES	2			;���o�p���X


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		�t�B�[�_		***
;	***		�ݒ�E����		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
;	=== 2016-03-20 ����̨��ނ̈Ӗ���"LFEED"�œ��ꂷ��(�オALIGN 4������OK)=====
_COP2_SVP_LFEED_LNG1		.SRES	4	;���蒷���@0.01mm
_COP2_SVP_LFEED_STRPOS	.SRES	4	;����J�n�ʒu 0.001mm
_COP2_SVP_LFEED_STRDEG	.SRES	2	;����J�n�p�x 0.1�x
_COP2_SVP_LFEED_STRNO	.SRES	2	;����J�n�s��		
;	ALIGN4�s�v(�ʒu,�p�x,�s����3�_���)
_COP2_SVP_LFEED_ENDPOS	.SRES	4	;����I���ʒu 0.001mm
_COP2_SVP_LFEED_ENDDEG	.SRES	2	;����I���p�x 0.1�x
_COP2_SVP_LFEED_ENDNO	.SRES	2	;����I���s��
;	ALIGN4�s�v(�ʒu,�p�x,�s����3�_���)
_COP2_SVP_LFEED_SPD1		.SRES	2	;�ʏ�̑��葬�x1%
_COP2_SVP_LFEED_SPD2		.SRES	2	;�ᑬ�̑��葬�x1%
_COP2_SVP_LFEED_SELNO	.SRES	2	;�^���̑I��ԍ�
_COP2_SVP_LFEED_HOSIN	.SRES	2	;������(�ر�ݽ) ����
_COP2_SVP_LFEED_HOSOT	.SRES	2	;������(�ر�ݽ) �o��

_COP2_SVP_LFEED_GMNSQ1	.SRES	2	;���ݽ409
_COP2_SVP_LFEED_GMNSQ2	.SRES	2	;���ݽ410
_COP2_SVP_LFEED_GMNSQ3	.SRES	2	;���ݽ411
_COP2_SVP_LFEED_GMNSQ4	.SRES	2	;���ݽ412

	.ALIGN	4				;
_COP2_PVP_LFEED_POS	.SRES	4		;̨��ތ��݈ʒu�\��


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	***		SIT4->COP2		***
;	***		������		***
;	***		DI,360ENC		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_ENC360_INDT	.SRES	2			;WR/RD OK
_COP2_INT_SFY_INP_DAT	.SRES	2			;
_COP2_INT_STP_INP_DAT	.SRES	2			;
_COP2_PVX_SH4_SFTY_IN	.SRES	2			;
_COP2_di1_cb_ctl1	.SRES	2			;
_COP2_di2_cb_ctl2	.SRES	2			;
_COP2_di3_cb_inp1	.SRES	2			;
_COP2_di4_cb_inp2	.SRES	2			;
_COP2_REAL_INP1_DATA	.SRES	2			;
_COP2_FACT_IN_DATA	.SRES	2			;
_COP2_FDEV_IN_DATA	.SRES	2			;
_COP2_RACT_IN_DATA	.SRES	2			;
_COP2_RDEV_IN_DATA	.SRES	2			;





;	***************************************************
;	***						***
;	***						***
;	***						***
;	***************************************************
	.ALIGN	4					;
_COP2_PVP_LFD_PVABSPOS1		.SRES	4		;̨��ތ��݈ʒu1(ABS)
_COP2_PVP_LFD_PVABSPOS2		.SRES	4		;̨��ތ��݈ʒu2(ABS)
_COP2_PVP_LFD_PVABSPLS1		.SRES	4		;̨��ތ��݈ʒuPLS1(ABS)
_COP2_PVP_LFD_PVABSPLS2		.SRES	4		;̨��ތ��݈ʒuPLS2(ABS)

_COP2_PVP_LFD_PVINCPOS1		.SRES	4		;̨��ތ��݈ʒu1(INC)
_COP2_PVP_LFD_PVINCPOS2		.SRES	4		;̨��ތ��݈ʒu2(INC)
_COP2_PVP_LFD_PVINCPLS1		.SRES	4		;̨��ތ��݈ʒuPLS1(INC)
_COP2_PVP_LFD_PVINCPLS2		.SRES	4		;̨��ތ��݈ʒuPLS2(INC)

_COP2_PVP_LFD_OBJABSPLS		.SRES	4		;̨��ތ��݈ʒu1(ABS)
_COP2_PVP_LFD_OBJINCPLS		.SRES	4		;̨��ތ��݈ʒuPLS1(INC)

_COP2_PVP_LFD_OBJSPD		.SRES	2		;+/- PER
_COP2_PVP_LFD_ENCSPD		.SRES	2		;+/- PER

_COP2_LFD_SITMCN_SIG		.SRES	2		;470 ̨��ޓ���M�� BI0,BIT1,BIT2,BIT3


;	***************************************************
;	***												***
;	***			2017-06-29							***
;	***			COP3-CPUC�W����p					***
;	***			�����鉻�\���@�\					***
;	***			1ms�^�C�}							***
;	***												***
;	***************************************************
_COP23_1MS_CNT				.SRES	2	;
_COP23_CTL_ENC360			.SRES	2	;
_COP23_INC_ENC360			.SRES	2	;

	.ALIGN	4							;
_COP23_RNA_ABS_POS			.SRES	4	;RNA_ABS_POS 4BYTE
_COP23_RNA_CTL_POS1			.SRES	4	;
_COP23_RNA_ABS_MAXPOS		.SRES	4	;
_COP23_RNA_ABS_MINPOS		.SRES	4	;
_COP23_SHOT_MOST_DOWN_POS	.SRES	4	;
_COP23_LINK_RL_OBJ_ABSPLS	.SRES	8	;
_COP23_LINK_PV_ABSPLS		.SRES	8	;


;	---------- �����ݸސ�p----------------
_COP23_PV_OUT_SPD_PER		.SRES	2	;PV_OUT_SPD_PER 2BYTE 0.1
_COP23_PV_ENC_SPD_PER		.SRES	2	;PV_ENC_SPD_PER 2BYTE 0.1
_COP23_TRD_SMP_PV_SEQ		.SRES	2	;
_COP23_PVP_POWER_MONI		.SRES	2	;
_COP23_PV_IVW_DAT_DSP		.SRES	2	;[�P�ʐ؂�ւ��t��]
_COP23_MON_SV_IVW_USED		.SRES	2	;


_COP23_TRD_SEQMONI_01		.SRES	2*16	;ADR
_COP23_TRD_SMPTRG_CNT		.SRES	2		;

_COP2DPRAM_END:
;	------------07ffh�����Ȃ����璍��-----------------
