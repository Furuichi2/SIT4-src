/****************************************************************************************
*	File Name	:	ssc_Mem.c
*	Function	:	�V�[�P���X ���[�N�̈��`
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-09 Y.Kobayashi
****************************************************************************************/

#include	"sqc_CmnDef.h"
#include	"sqc_Config.h"


//----- Variables -------------------------------------------------------------

// �V�[�P���X ���[�N�̈�
#pragma section	_seqram1

S4b		seq_ram1_top;								// ���[�N�̈�1 TOP

// �� �V�[�P���X���s�R�[�h�̈�-----------------------------
// POU1
S4b		SEQ_RUN1_TOP;								// TOP
U2b		SEQ_RUN1[SEQ_STEP_MAX1 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
S4b		SEQ_RUN1_END;								// END
// POU2
S4b		SEQ_RUN2_TOP;								// TOP
U2b		SEQ_RUN2[SEQ_STEP_MAX2 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
S4b		SEQ_RUN2_END;								// END
// POU3
S4b		SEQ_RUN3_TOP;								// TOP
U2b		SEQ_RUN3[SEQ_STEP_MAX3 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
S4b		SEQ_RUN3_END;								// END

// �� �R���p�C����� --------------------------------------
S4b		seq_ram2_top;								// ���[�N�̈�2 TOP
U2b		SEQ_CARD_RAM[SEQ_CARD_MAX];					// SEQUENCE BIT AREA
U2b		SEQ_CMP_ERR1;								// POU1 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR1;							// POU1 �R���p�C���ُ�A�h���X
U2b		SEQ_CMP_ERR2;								// POU2 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR2;							// POU2 �R���p�C���ُ�A�h���X
U2b		SEQ_CMP_ERR3;								// POU3 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
U4b		SEQ_CMP_ERR_ADR3;							// POU3 �R���p�C���ُ�A�h���X

// �� ���[�N ----------------------------------------------
U2b		DI_X_TOP1[SEQ_X_SIZE];						// X�̈惏�[�N������1
U2b		DI_X_TOP2[SEQ_X_SIZE];						// X�̈惏�[�N������2(�����o�^/����SET���)
U2b		DO_Y_TOP1[SEQ_Y_SIZE];						// Y�̈惏�[�N������1
U2b		DO_Y_TOP2[SEQ_Y_SIZE];						// Y�̈惏�[�N������2(�����o�^/����SET���)
U2b		X_PUSH_TOP1[SEQ_X_SIZE];					// X�̈�ޔ�p���[�N������1
U2b		X_PUSH_TOP2[SEQ_X_SIZE];					// X�̈�ޔ�p���[�N������2

U2b		SEQ_CMP_START;								// �R���p�C����/�ُ� = 0 , �R���p�C������ = 1
U2b		SeqSysStat;									// �X�e�[�^�X���
													// 0bit : �N���r�b�g	(0:��~,1:�N��)
													// 1bit : ��~�r�b�g	(0:�N��,1:��~)
													// 2bit : �d�̏�r�b�g	(0:�ُ�Ȃ�,1:�d�̏�)
													// 3bit : �y�̏�r�b�g	(0:�ُ�Ȃ�,1:�y�̏�)

U2b		SEQ_LD_TIMOUT;								// ���_�[�c�[���ʐM�^�C���A�E�g
U2b		SEQ_TIM_WK100M;								// 100ms�^�C�}�N���p���[�N
U2b		SEQ_TIM_WK1000M;							// 1000ms�^�C�}�N���p���[�N

U4b		SEQ_TMR_DATA[3 * SEQ_TD_SIZE];				// �^�C�}�f�[�^
U4b		SEQ_CTR_DATA[3 * SEQ_CD_SIZE];				// �J�E���^�f�[�^
U2b		SEQ_SR_FLG[SEQ_CARD_MAX];					// SR�f�[�^

// �� ���s�����W�X�^ --------------------------------------
// POU1
U2b		SEQ_ARG1_DATA;								// ARG data load
U2b		SEQ_MRG1_DATA;								// MRG data load
U2b		SEQ_NRG1_DATA;								// NRG data load
U4b		SEQ_DRG1_DATA;								// DATA REG data load
// POU2
U2b		SEQ_ARG2_DATA;								// ARG data load
U2b		SEQ_MRG2_DATA;								// MRG data load
U2b		SEQ_NRG2_DATA;								// NRG data load
U4b		SEQ_DRG2_DATA;								// DATA REG data load
// POU3
U2b		SEQ_ARG3_DATA;								// ARG data load
U2b		SEQ_MRG3_DATA;								// MRG data load
U2b		SEQ_NRG3_DATA;								// NRG data load
U4b		SEQ_DRG3_DATA;								// DATA REG data load

U2b		SEQ_TSK1_DATA;								// 0(1msec):1(10msec):�ޯ�������2(100msec)

// �� �R���p�C���ُ� --------------------------------------
U2b		PVP_SQ_COM_ERR;								// �R���p�C���ُ�L��^����
U2b		PVP_SQ_COM_ADR;								// �R���p�C���ُ�A�h���X

//	�V�[�P���X�p�̃��[�N������(?)
USHORT	SeqMemM[32];					// �V�[�P���X�p�⏕������
