/****************************************************************************************
*	File Name	:	ssc_Mem.h
*	Function	:	�V�[�P���X ���[�N�̈��`
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-11 Y.Kobayashi(�R�[�h����)
****************************************************************************************/
#ifndef _SSC_MEM_H_
#define _SSC_MEM_H_


//----- Variables -------------------------------------------------------------

extern S4b		seq_ram1_top;								// ���[�N�̈�1 TOP

// �� �V�[�P���X���s�R�[�h�̈�-----------------------------
// POU1
extern S4b		SEQ_RUN1_TOP;								// TOP
extern U2b		SEQ_RUN1[SEQ_STEP_MAX1 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
extern S4b		SEQ_RUN1_END;								// END
// POU2
extern S4b		SEQ_RUN2_TOP;								// TOP
extern U2b		SEQ_RUN2[SEQ_STEP_MAX2 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
extern S4b		SEQ_RUN2_END;								// END
// POU3
extern S4b		SEQ_RUN3_TOP;								// TOP
extern U2b		SEQ_RUN3[SEQ_STEP_MAX3 * SEQ_1STEP_MAX];	// �V�[�P���X���s�R�[�h�̈�
extern S4b		SEQ_RUN3_END;								// END

// �� �R���p�C����� --------------------------------------
extern S4b		seq_ram2_top;								// ���[�N�̈�2 TOP
extern U2b		SEQ_CARD_RAM[SEQ_CARD_MAX];					// SEQUENCE BIT AREA
extern U2b		SEQ_CMP_ERR1;								// POU1 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
extern U4b		SEQ_CMP_ERR_ADR1;							// POU1 �R���p�C���ُ�A�h���X
extern U2b		SEQ_CMP_ERR2;								// POU2 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
extern U4b		SEQ_CMP_ERR_ADR2;							// POU2 �R���p�C���ُ�A�h���X
extern U2b		SEQ_CMP_ERR3;								// POU3 �R���p�C�����(CMP OK = BX:0000, CMP NG = BX:FFFF)
extern U4b		SEQ_CMP_ERR_ADR3;							// POU3 �R���p�C���ُ�A�h���X

// �� ���[�N ----------------------------------------------
extern U2b		DI_X_TOP1[SEQ_X_SIZE];						// X�̈惏�[�N������1
extern U2b		DI_X_TOP2[SEQ_X_SIZE];						// X�̈惏�[�N������2(�����o�^/����SET���)
extern U2b		DO_Y_TOP1[SEQ_Y_SIZE];						// Y�̈惏�[�N������1
extern U2b		DO_Y_TOP2[SEQ_Y_SIZE];						// Y�̈惏�[�N������2(�����o�^/����SET���)
extern U2b		X_PUSH_TOP1[SEQ_X_SIZE];					// X�̈�ޔ�p���[�N������1
extern U2b		X_PUSH_TOP2[SEQ_X_SIZE];					// X�̈�ޔ�p���[�N������2

extern U2b		SEQ_CMP_START;								// �R���p�C����/�ُ� = 0 , �R���p�C������ = 1
extern U2b		SeqSysStat;									// �X�e�[�^�X���

extern U2b		SEQ_LD_TIMOUT;								// ���_�[�c�[���ʐM�^�C���A�E�g
extern U2b		SEQ_TIM_WK100M;								// 100ms�^�C�}�N���p���[�N
extern U2b		SEQ_TIM_WK1000M;							// 1000ms�^�C�}�N���p���[�N

extern U4b		SEQ_TMR_DATA[3 * SEQ_TD_SIZE];				// �^�C�}�f�[�^
extern U4b		SEQ_CTR_DATA[3 * SEQ_CD_SIZE];				// �J�E���^�f�[�^
extern U2b		SEQ_SR_FLG[SEQ_CARD_MAX];					// SR�f�[�^

// �� ���s�����W�X�^ --------------------------------------
// POU1
extern U2b		SEQ_ARG1_DATA;								// ARG data load
extern U2b		SEQ_MRG1_DATA;								// MRG data load
extern U2b		SEQ_NRG1_DATA;								// NRG data load
extern U4b		SEQ_DRG1_DATA;								// DATA REG data load
// POU2
extern U2b		SEQ_ARG2_DATA;								// ARG data load
extern U2b		SEQ_MRG2_DATA;								// MRG data load
extern U2b		SEQ_NRG2_DATA;								// NRG data load
extern U4b		SEQ_DRG2_DATA;								// DATA REG data load
// POU3
extern U2b		SEQ_ARG3_DATA;								// ARG data load
extern U2b		SEQ_MRG3_DATA;								// MRG data load
extern U2b		SEQ_NRG3_DATA;								// NRG data load
extern U4b		SEQ_DRG3_DATA;								// DATA REG data load

extern U2b		SEQ_TSK1_DATA;								// 0(1msec):1(10msec):�ޯ�������2(100msec)

// �� �R���p�C���ُ� --------------------------------------
extern U2b		PVP_SQ_COM_ERR;								// �R���p�C���ُ�L��^����
extern U2b		PVP_SQ_COM_ADR;								// �R���p�C���ُ�A�h���X


extern USHORT	SeqMemM[32];					// �V�[�P���X�p�⏕������

#endif	/* _SSC_MEM_H_ */
