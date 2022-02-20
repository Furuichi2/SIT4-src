/****************************************************************************************
*	File Name	:	ssc_Config.h
*	Function	:	�V�[�P���X �R���t�B�O���[�V����
*	Author		:	Designed by Y.Kobayashi, Coded by Y.Kobayashi
*	Date		:	2010-08-12 Y.Kobayashi
*	Update		:	2010-08-17 Y.Kobayashi(KOMTRAX�p�ɕύX)
****************************************************************************************/
#ifndef _SSC_CONFIG_H_
#define _SSC_CONFIG_H_


//----- Defines ---------------------------------------------------------------

// �o�[�W����
#define HW_Ver					0x0001							// HW�o�[�W����
#define SW_Ver					0x0001							// SW�o�[�W����

// POU�X�e�b�v��
#define SEQ_1STEP_MAX			15								// 1STEP������ő像�[�h��
#define SEQ_STEP_MAX1			4096							// POU1 �X�e�b�v��(�W�� 10ms)
#define SEQ_STEP_MAX2			4096							// POU2 �X�e�b�v��(�ᑬ �o�b�N�O���E���h)
#define SEQ_STEP_MAX3			256								// POU3 �X�e�b�v��(���� 1ms)

// �������̈�T�C�Y
// ssa_Config.equ�ɂ����l�̒�`����
#define SEQ_W0_SIZE				0								// W0�̈�T�C�Y(WORD) 
#define SEQ_X_SIZE				16								// X�̈�T�C�Y(WORD)
#define SEQ_Y_SIZE				16								// Y�̈�T�C�Y(WORD)
#define SEQ_M_SIZE				512								// M�̈�T�C�Y(WORD)
#define SEQ_L_SIZE				32								// L�̈�T�C�Y(WORD)
#define SEQ_T_SIZE				32								// T�̈�T�C�Y(WORD)
#define SEQ_C_SIZE				32								// C�̈�T�C�Y(WORD)
#define SEQ_TD_SIZE				SEQ_T_SIZE * 16					// Td�̈�T�C�Y(WORD)
#define SEQ_CD_SIZE				SEQ_C_SIZE * 16					// Cd�̈�T�C�Y(WORD)
#define SEQ_W1_SIZE				0								// W1�̈�T�C�Y(WORD)
#define SEQ_W2_SIZE				0								// W2�̈�T�C�Y(WORD)
#define SEQ_W3_SIZE				0								// W3�̈�T�C�Y(WORD)
#define SEQ_W4_SIZE				0								// W4�̈�T�C�Y(WORD)
#define SEQ_F_SIZE				136								// F�̈�T�C�Y(WORD)
#define SEQ_S_SIZE				1024							// S�̈�T�C�Y(WORD)
#define SEQ_A_SIZE				32								// A�̈�T�C�Y(WORD)
#define SEQ_CARD_MAX			3 * 1024						// ��������ԃT�C�Y(WORD)(��{�I�ɂ͏�L�̍��v)


//----- Consts ----------------------------------------------------------------

extern const UB 				SeqStatTypeTbl[16];				// ���W���[���^���e�[�u��

#endif	/* _SSC_CONFIG_H_ */
