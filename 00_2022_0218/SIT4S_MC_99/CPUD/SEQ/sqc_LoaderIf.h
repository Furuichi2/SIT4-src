/****************************************************************************************
*	File Name	:	ssc_LoaderIf.h
*	Function	:	�V�[�P���X ���[�_�[�R�}���hI/F
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-20 T.Akiba
*	Update		:	2010-08-11 Y.Kobayashi(�R�[�h����)
****************************************************************************************/
#ifndef _SEQ_LODERRM_H_
#define _SEQ_LODERRM_H_


//----- Defines -----------------------------------------------------

#define	LD_FLM_MAX			512				// �t���[���T�C�YMAX
#define	LD_DATA_MAX			512				// �f�[�^�o�C�g��MAX(�f�[�^��MAX��492 + bcc)


//----- Structs ---------------------------------------------------------------

// ���[�_�[�R�}���h�i�[�\����
typedef struct {
	U1b		sSCodeFlg;				// �X�^�[�g�R�[�h��M�t���O
	U1b		datacnt[2];				// �f�[�^���J�E���^ L,H
	U1b		procStatus;				// �����X�e�[�^�X
	U1b		conectMode;				// �ڑ�����
	U1b		tmId[2];				// �ڑ�ID L,H
	U1b		kindCode;				// �@��݊��R�[�h(0x11)
	U1b		tmILCode;				// �`���C���^���b�N�R�[�h
	U1b		passwd[4];				// �p�X���[�h LL,LH,HL,HH
	U1b		CMND;					// �R�}���h
	U1b		MODE;					// ���[�h
	U1b		endInfo;				// �I�����
	U1b		seqNumber;				// �V�[�P���X�ԍ�
	U1b		BYTEN[2];				// BYTEN L,H
	U1b		data[LD_DATA_MAX];		// �R�}���h�f�[�^
} SeqLdCmd_st;

// POU���(size = 64KB)
typedef struct {
	U4b		Code1;					// �Œ�R�[�h1
	U4b		SwVer[2];				// �\�t�g�E�F�A�o�[�W����
	U2b		Size;					// �T�C�Y
	U2b		nop1;					// �\��
	U4b		Spt;					// �⏕���
	U2b		Tem;					// �e���|�����T�C�Y
	U2b		nop2;					// �\��
	U2b		Cmd[32768-16];			// �v���O����(32752���[�h)
	U4b		Sum;					// �v���O����SUM
	U4b		Code2;					// �Œ�R�[�h2
} SeqPOUStat_st;

// POU�������
typedef struct {
	U2b		POU1;					// POU1�t���O
	U2b		POU2;					// POU2�t���O
	U2b		POU3;					// POU3�t���O
} SeqPOU_st;


//----- Variables -------------------------------------------------------------

// ����M�J��
extern U2b 				SeqScifStat;				// ����M�X�e�[�g(0:��M,1:���M)
extern U2b 				SeqLdWk[LD_FLM_MAX];		// ���[�N���
extern U2b 				SeqLdLOOP1;					// ���[�v�ϐ�
extern U2b 				SeqLdCMD;					// �����R�}���h�i�[���W�X�^
extern U2b 				SeqLdEnd;					// �I�����(0x00:�I��,0x01:�p��)
extern U2b 				SeqLdNo;					// �V�[�P���X�ԍ�(1�`255)
extern U2b 				SeqLdNoBak;					// �V�[�P���X�ԍ��o�b�N�A�b�v(1�`255)
extern U2b 				SeqLdByte;					// �f�[�^���o�C�g��
extern U2b				SeqRasFlg;					// RAS���t���O
extern U2b 				SeqRasCode;					// RAS���ފi�[���W�X�^
// ��M
extern SeqLdCmd_st		SeqRev;						// ��M�t���[��
extern U1b				SeqRevBuff[LD_FLM_MAX];		// ��M�p�t���[���o�b�t�@
extern U2b				SeqRevStat;					// ��M�X�e�[�g
extern U2b				SeqRevFlmCnt;				// ��M�t���[���J�E���^
extern U2b				SeqRevDataCnt;				// ��M�f�[�^���J�E���^
extern U2b				SeqRevBcc;					// BCC�Z�o�p���W�X�^(��M�p)
extern U2b				SeqRevEnd;					// ��M�����t���O(0:������,1:����)
extern U2b				SeqRevCnt;					// ��M���J�E���^
// ���M
extern SeqLdCmd_st		SeqSend;					// ���M�t���[��
extern U1b				SeqSendBuff[LD_FLM_MAX];	// ���M�p�t���[���o�b�t�@
extern U2b				SeqSendStat;				// ���M�X�e�[�g
extern U2b				SeqSendFlmCnt;				// ���M�t���[���J�E���^
extern U2b				SeqSendByte;				// �f�[�^���޲Đ��J�E���^
extern U2b				SeqSendBcc;					// BCC�Z�o�p���W�X�^(���M�p)
extern U2b				SeqSendCnt;					// ���M�o�C�g���J�E���^
extern U2b				SeqSendDcnt;				// �f�[�^���[�h���J�E���^
extern U2b				SeqSendMem;					// ���������i�[���W�X�^
extern U2b				SeqSendEndFlg;				// �������M�t���O(0:�������M�Ȃ�,1:�������M)
extern U2b				SeqSendDataCnt;				// 1POU���� �f�[�^�����J�E���^
extern U2b				SeqSendDataCntBak;			// 1POU���� �f�[�^�����J�E���^ �o�b�N�A�b�v
extern U2b				SeqSendFlmErr;				// ���M�t���[���G���[�t���O(0:����,1:�ُ�)
// �G���[
extern U2b				SeqLdErr;					// ����M�G���[�t���O(0:����,1:�ُ�)
// ���[�_�R�}���h����
extern U2b				SeqMKind[82];				// ���������(���ɂ��Ǐo�p��82�p�ӂ���)
extern U4b				SeqMAdr[82];				// �������A�h���X(���j�^�Ǐo�p��82�p�ӂ���)
extern U2b				SeqRdWdCnt;					// �Ǐo���[�h��
extern U2b				SeqRdWdCntBak;				// �Ǐo���[�h���o�b�N�A�b�v
extern U2b 				SeqWrData[LD_DATA_MAX];		// �����f�[�^(�ő发���� 492byte)
extern U2b				SeqPOU;						// POU�w��
extern U2b				SeqPOULpCnt;				// 1POU�Ǐo���[�v�J�E���^
extern U2b				SeqPouSize;					// POU�T�C�Y
extern U4b				SeqSptData;					// �⏕���
extern U2b				SeqTemSize;					// �e���|�����T�C�Y
extern U4b				SeqRtcData;					// �J�����_���
extern U2b				SeqKpX[32];					// �����ݒ�o�^�f�[�^(X�̈�Ɠ���)
extern U2b				SeqKpY[32];					// �����ݒ�o�^�f�[�^(Y�̈�Ɠ���)
extern U2b				SeqMoniCnt;					// ���j�^�_��
extern U2b				SeqDataTyp[82];				// �f�[�^�^
extern U2b				SeqBitData[82];				// �r�b�g�ԍ�
extern U2b				SeqBit;						// Bit
extern U2b				SeqKpData[82];				// �����ݒ���f�[�^
extern U2b				SeqChgDataCnt;				// �ύX�f�[�^�_��
extern U4b				SeqChgData[50];				// �����f�[�^(�ő发���� 49.2byte)
extern U2b				SeqKpOnX[32];				// �����ݒ�o�^�̈�(X�̈�Ɠ���)
extern U2b				SeqKpOnY[32];				// �����ݒ�o�^�̈�(Y�̈�Ɠ���)
extern U2b				SeqKpOffX[32];				// �����ݒ�����̈�(X�̈�Ɠ���)
extern U2b				SeqKpOffY[32];				// �����ݒ�����̈�(Y�̈�Ɠ���)

extern U2b				SeqMainStat;				// �V�[�P���X���C���X�e�[�g(0:��~,1:�N��,2:�ăR���p�C��)
extern U2b				SeqRunFlg;					// �V�[�P���X�N���t���O(0:��~,1:�N��)
extern U2b				SeqCmpFlg;					// �ăR���p�C���t���O(0:��~,1:�ăR���p�C��)
extern U2b				SeqCmpErrFlg;				// �R���p�C���G���[�t���O(0:����,1:�ُ�)
extern U2b				SeqCpuRun;					// �^�]�t���O(0:��~,1:�^�]��)
extern SeqPOUStat_st	SeqPOU1;					// POU1���
extern SeqPOUStat_st	SeqPOU2;					// POU2���
extern SeqPOUStat_st	SeqPOU3;					// POU3���
extern U2b				SeqPOURun1Flg;				// POU1�^�]�t���O(0:�^�]��,1:�^�]�s��)
extern U2b				SeqPOURun2Flg;				// POU2�^�]�t���O(0:�^�]��,1:�^�]�s��)
extern U2b				SeqPOURun3Flg;				// POU3�^�]�t���O(0:�^�]��,1:�^�]�s��)
extern SeqPOU_st		SeqPOUWtFlg;				// POU�����t���O(0:������,1:����)
extern U2b				SeqTimWtFlg;				// ���v��񏑍��t���O(0:������,1:����)
extern U2b				SeqPOUWtEnd;				// �_�E�����[�h�I���t���O

#endif	/* _SEQ_LODERRM_H_ */
