/****************************************************************************************
*	File Name	:	ssc_LoaderIf.c
*	Function	:	�V�[�P���X ���[�_�R�}���hI/F����
*	Author		:	Designed by Yoichi Kobayashi, Coded by Yoichi Kobayashi
*	Date		:	2009-11-20 Akiba
*	Update		:	2010-08-31 Y.Kobayashi(�R�[�h����)
****************************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include	<machine.h>

#include 	"sqc_CmnDef.h"
#include	"sqc_Config.h"
#include	"sqc_Mem.h"
#include	"sqc_LoaderIf.h"
//[koma]#include	"scif7619.h"


//----- Define ----------------------------------------------------------------

#define CODE_STX				0x5A			// STX
// �R�}���h
#define LD_ADR_RD				0x0000			// �A�h���X�Ǐo����
#define LD_1POU_RD				0x0002			// 1POU�Ǐo����
#define LD_RTC_RD				0x000D			// �J�����_�Ǐo����
#define LD_POU_File_RD			0x0010			// POU̧�ُ��Ǐo����
#define LD_ADR_WR				0x0100			// �A�h���X��������
#define LD_1POU_WR				0x0102			// 1POU��������
#define LD_RTC_WR				0x010D			// �J�����_�ݒ菈��
#define LD_MEM_CLR_WR			0x010F			// �f�[�^�������N���A����
#define LD_MONI_RD				0x0200			// ���j�^�Ǐo����
#define LD_Start_WR				0x0400			// �ꊇ�N������
#define LD_Stop_WR				0x0402			// �ꊇ��~����
#define LD_DownLoad_End			0x0506			// �_�E�����[�h�I���ʒm
#define LD_Data_chg_WR			0x0600			// �f�[�^�ύX����
#define LD_Set_WR				0x0601			// �����ݒ�o�^����
#define LD_Reset_WR				0x0602			// �����ݒ��������
#define LD_Statas_RD			0x03F0			// �X�e�[�^�X�Ǐo����
// �f�[�^�^
#define SeqDtTypB				0x04			// BIT
#define SeqDtTypW				0x00			// WARD
#define SeqDtTypL				0x08			// DWORDLong
// �����X�e�[�^�X
#define SeqRasCpuErr			0x10			// CPU�ُ�
#define SeqRasCpuRun			0x11			// CPU�^�]��
#define SeqRasNoCmd				0x20			// ����`�R�}���h
#define SeqRasParaErr			0x21			// �����p�����[�^�ُ�
#define SeqRasFlmErr			0x22			// �p�����[�^�ُ�
#define SeqRasDataTypErr		0x40			// �f�[�^�w��ُ�
#define SeqRasFromErr			0x42			// �������A�N�Z�X�ُ�
#define SeqRasMemAdrErr			0x44			// �������A�h���X�w��ُ�
#define SeqRasMemOver			0x45			// �������T�C�Y�I�[�o�[
#define SeqRasStepOver			0x47			// 1POU�X�e�b�v���I�[�o�[
#define SeqRasMoniOver			0x60			// ���j�^�o�^�G���[
// �V�X�e���萔
#define SER_CHN1				1				// �V���A���|�[�gCH
#define T1S						100				// �ʐM�^�C���A�E�g����(1�b)
#define SEQ_RCV_BUFF_SIZE		512				// ��M�o�b�t�@�T�C�Y
#define LD_FLM_MAX				512				// �t���[��MAX
#define LD_DATA_MAX_W			246				// �f�[�^�o�C�g��MAX(���[�h��)
#define LD_DATA_MAX_B			492				// �f�[�^�o�C�g��MAX(�o�C�g��)
#define DataChgMax				49				// �f�[�^�ύX�_��MAX
#define MoniMax					81				// ���j�^�_��MAX
#define POU1SizeMax				32752			// POU1�X�e�b�v��Max
#define POU2SizeMax				32752			// POU2�X�e�b�v��Max
#define POU3SizeMax				32752			// POU3�X�e�b�v��Max
#define SeqCmdCode1				0x12345678		// �V�[�P���X�R�}���h�R�[�h1
#define SeqCmdCode2				0x9ABCDEF0		// �V�[�P���X�R�}���h�R�[�h2


//----- Structs -------------------------------------------------------------------------

// �f�[�^���
typedef	union	{
	float			f_dat;
	long			l_dat;
	unsigned long	ul_dat;
	short			w_dat[2];
	unsigned short	uw_dat[2];
	char			b_dat[4];
	unsigned char	ub_dat[4];
} long_data_st;


//----- Variables -----------------------------------------------------------------------

// ����M�J��
U2b 			SeqScifStat;				// ����M�X�e�[�g(0:��M,1:���M)
U2b 			SeqLdWk[LD_FLM_MAX];		// ���[�N���
U2b 			SeqLdLOOP1;					// ���[�v�ϐ�
U2b 			SeqLdCMD;					// �����R�}���h�i�[���W�X�^
U2b 			SeqLdEnd;					// �I�����(0x00:�I��,0x01:�p��)
U2b 			SeqLdNo;					// �V�[�P���X�ԍ�(1�`255)
U2b 			SeqLdNoBak;					// �V�[�P���X�ԍ��o�b�N�A�b�v(1�`255)
U2b 			SeqLdByte;					// �f�[�^���o�C�g��
U2b				SeqRasFlg;					// RAS���t���O
U2b 			SeqRasCode;					// RAS���ފi�[���W�X�^
// ��M
SeqLdCmd_st		SeqRev;						// ��M�t���[��
U1b				SeqRevBuff[LD_FLM_MAX];		// ��M�p�t���[���o�b�t�@
U2b				SeqRevStat;					// ��M�X�e�[�g
U2b				SeqRevFlmCnt;				// ��M�t���[���J�E���^
U2b				SeqRevDataCnt;				// ��M�f�[�^���J�E���^
U2b				SeqRevBcc;					// BCC�Z�o�p���W�X�^(��M�p)
U2b				SeqRevEnd;					// ��M�����t���O(0:������,1:����)
U2b				SeqRevCnt;					// ��M���J�E���^
// ���M
SeqLdCmd_st		SeqSend;					// ���M�t���[��
U1b				SeqSendBuff[LD_FLM_MAX];	// ���M�p�t���[���o�b�t�@
U2b				SeqSendStat;				// ���M�X�e�[�g
U2b				SeqSendFlmCnt;				// ���M�t���[���J�E���^
U2b				SeqSendByte;				// �f�[�^���޲Đ��J�E���^
U2b				SeqSendBcc;					// BCC�Z�o�p���W�X�^(���M�p)
U2b				SeqSendCnt;					// ���M�o�C�g���J�E���^
U2b				SeqSendDcnt;				// �f�[�^���[�h���J�E���^
U2b				SeqSendMem;					// ���������i�[���W�X�^
U2b				SeqSendEndFlg;				// �������M�t���O(0:�������M�Ȃ�,1:�������M)
U2b				SeqSendDataCnt;				// 1POU���� �f�[�^�����J�E���^
U2b				SeqSendDataCntBak;			// 1POU���� �f�[�^�����J�E���^ �o�b�N�A�b�v
U2b				SeqSendFlmErr;				// ���M�t���[���G���[�t���O(0:����,1:�ُ�)
// �G���[
U2b				SeqLdErr;					// ����M�G���[�t���O(0:����,1:�ُ�)
// ���[�_�R�}���h����
U2b				SeqMKind[MoniMax+1];		// ���������(���ɂ��Ǐo�p��82�p�ӂ���)
U4b				SeqMAdr[MoniMax+1];			// �������A�h���X(���j�^�Ǐo�p��82�p�ӂ���)
U2b				SeqRdWdCnt;					// �Ǐo���[�h��
U2b				SeqRdWdCntBak;				// �Ǐo���[�h���o�b�N�A�b�v
U2b 			SeqWrData[LD_DATA_MAX];		// �����f�[�^(�ő发���� 492byte)
U2b				SeqPOU;						// POU�w��
U2b				SeqPOULpCnt;				// 1POU�Ǐo���[�v�J�E���^
U2b				SeqPouSize;					// POU�T�C�Y
U4b				SeqSptData;					// �⏕���
U2b				SeqTemSize;					// �e���|�����T�C�Y
U4b				SeqRtcData;					// �J�����_���
U2b				SeqKpX[32];					// �����ݒ�o�^�f�[�^(X�̈�Ɠ���)
U2b				SeqKpY[32];					// �����ݒ�o�^�f�[�^(Y�̈�Ɠ���)
U2b				SeqMoniCnt;					// ���j�^�_��
U2b				SeqDataTyp[82];				// �f�[�^�^
U2b				SeqBitData[82];				// �r�b�g�ԍ�
U2b				SeqBit;						// Bit
U2b				SeqKpData[82];				// �����ݒ���f�[�^
U2b				SeqChgDataCnt;				// �ύX�f�[�^�_��
U4b				SeqChgData[50];				// �����f�[�^(�ő发���� 49.2byte)
U2b				SeqKpOnX[32];				// �����ݒ�o�^�̈�(X�̈�Ɠ���)
U2b				SeqKpOnY[32];				// �����ݒ�o�^�̈�(Y�̈�Ɠ���)
U2b				SeqKpOffX[32];				// �����ݒ�����̈�(X�̈�Ɠ���)
U2b				SeqKpOffY[32];				// �����ݒ�����̈�(Y�̈�Ɠ���)

U2b				SeqMainStat;				// �V�[�P���X���C���X�e�[�g(0:��~,1:�N��,2:�ăR���p�C��)
U2b				SeqRunFlg;					// �V�[�P���X�N���t���O(0:��~,1:�N��)
U2b				SeqCmpFlg;					// �ăR���p�C���t���O(0:��~,1:�ăR���p�C��)
U2b				SeqCmpErrFlg;				// �R���p�C���G���[�t���O(0:����,1:�ُ�)
U2b				SeqCpuRun;					// �^�]�t���O(0:��~,1:�^�]��)
SeqPOUStat_st	SeqPOU1;					// POU1���
SeqPOUStat_st	SeqPOU2;					// POU2���
SeqPOUStat_st	SeqPOU3;					// POU3���
U2b				SeqPOURun1Flg;				// POU1�^�]�t���O(0:�^�]��,1:�^�]�s��)
U2b				SeqPOURun2Flg;				// POU2�^�]�t���O(0:�^�]��,1:�^�]�s��)
U2b				SeqPOURun3Flg;				// POU3�^�]�t���O(0:�^�]��,1:�^�]�s��)
SeqPOU_st		SeqPOUWtFlg;				// POU�����t���O(0:������,1:����)
U2b				SeqTimWtFlg;				// ���v��񏑍��t���O(0:������,1:����)
U2b				SeqPOUWtEnd;				// �_�E�����[�h�I���t���O

//extern UH		hwVersion;					// H/W�o�[�W����
//extern UH		swVersion;					// S/W�o�[�W����
UH		hwVersion;						// H/W�o�[�W����
UH		swVersion;						// S/W�o�[�W����
UH		seqVersion;						// SEQ�o�[�W����				10/09/29 Add Y.Kobayashi	


//----- Consts --------------------------------------------------------------------------

// ���M�t���[���t�H�[�}�b�g�e�[�u��
const unsigned char SeqSendFlmDataTbl[] = {
	0x5A,				// �X�^�[�g�R�[�h
	0x00,				// �f�[�^���J�E���^ L
	0x00,				// �f�[�^���J�E���^ H
	0x00,				// �����X�e�[�^�X
	0x7A,				// �ڑ�����
	0x00,				// �ڑ�ID L
	0x00,				// �ڑ�ID H
	0x11,				// �@��݊��R�[�h
	0x00,				// �`���C���^�[���b�N�R�[�h
	0x00,				// �p�X���[�h LL
	0x00,				// �p�X���[�h LH
	0x00,				// �p�X���[�h HL
	0x00,				// �p�X���[�h HH
	0x00,				// CMND
	0x00,				// MODE
	0x00,				// �I�����
	0x01,				// �V�[�P���X�ԍ�
	0x00,				// BYTEN L
	0x00,				// BYTEN H
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00,				// DATA
	0x00				// DATA
};

// BIT�e�[�u��
const unsigned short SeqBit16Tbl[] = {
	0x0001,				// Bit0
	0x0002,				// Bit1
	0x0004,				// Bit2
	0x0008,				// Bit3
	0x0010,				// Bit4
	0x0020,				// Bit5
	0x0040,				// Bit6
	0x0080,				// Bit7
	0x0100,				// Bit8
	0x0200,				// Bit9
	0x0400,				// Bit10
	0x0800,				// Bit11
	0x1000,				// Bit12
	0x2000,				// Bit13
	0x4000,				// Bit14
	0x8000				// Bit15
};

extern const U4b SeqLd_MKIND_TBL_TOP[];			// �������̈�TOP�A�h���X�e�[�u��
extern const U4b MKIND_TBL[];					// �������̈�e�[�u��


//----- ProtoType -----------------------------------------------------------------------

void SeqInitSerialDrv();						// �ر���ײ�ޏ���������
void SeqSerialMain();							// ��ް°� ����M����
void InitTmrCtrFlgClr();						// ��ρE��������ظر

static void SeqScifRev();						// ��M�ðď���
static void SeqScifSend();						// ���M�ðď���
static void SeqLdScifErr();						// ����������
static void SeqLdRevFlmChk();					// ��M�ڰѴװ���o����
static void SeqLdSendFlmChk();					// ���M�ڰѴװ���o����

static void SeqLdSendProg();					// �v������ޏ���
static void SeqLdAdrRd();						// ���ڽ�Ǐo����ޏ���
static void SeqLd1PouRd();						// 1POU�Ǐo����ޏ���
static void SeqLdRtcRd();						// ���v���Ǐo����ޏ���
static void SeqLdPouFileRd();					// POU̧�ُ��Ǐo����ޏ���
static void SeqLdAdrWr();						// ���ڽ��������ޏ���
static void SeqLd1PouWr();						// 1POU��������ޏ���
static void SeqLdRtcWr();						// ���v��񏑍�����ޏ���
static void SeqLdMemClrWr();					// ��ظر����ޏ���
static void SeqLdMoniRd();						// ����Ǐo����ޏ���
static void SeqLdStartWr();						// �ꊇ�N������ޏ���
static void SeqLdStopWr();						// �ꊇ��~����ޏ���
static void SeqLdDownLoadEnd();					// �޳�۰�ޏI���ʒm����ޏ���
static void SeqLdDataChgWr();					// �ް���������ޏ���
static void SeqLdSetWr();						// �����ݒ�o�^����ޏ���
static void SeqLdResetWr();						// �����ݒ��������ޏ���
static void SeqLdStatasRd();					// �ð���Ǐo����ޏ���

static void SeqSendFlmSet(unsigned short);		// ���M�ڰ�̫�ϯč쐬����
static void SeqLdSendBcc(unsigned short);		// BCC�쐬����


//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: �V���A���h���C�o�̏�����
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqInitSerialDrv()
{
	// �V���A���h���C�o�̏�����
//[koma]	SCIF_DrvInit(
//[koma]			SER_CHN1,					// ���� : 1(0:MODEM,1:LODER,2:NOT)
//[koma]			SCIF_DLEN_8,				// �ް��� : 8bit
//[koma]			SCIF_STPBIT_1,				// �į���ޯ� : 1bit
//[koma]			SCIF_PRT_EVEN,				// ���è�ޯ� : ����
//[koma]			SCIF_BRT_38400,				// �ްڰ� : 38400bps
//[koma]			0							// ���g�p
//[koma]			);

}

/********************************************************************
*	Function	: ���_�[�c�[������M����
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqSerialMain(void)
{
	switch(SeqScifStat){
		case	0:							// ��M�ð�
			SeqScifRev();
		break;
		
		case	1:							// ���M�ð�
			SeqScifSend();
		break;
		
		default:
			SeqScifStat = 0;				// ��M�ðĂ֑J��
		break;
	}
}

/********************************************************************
*	Function	: �^�C�}�E�J�E���g�̃������N���A
*	Param		: None
*	Return		: None
*	Date		: 10/18/31	M.Komatsu	Create
*	Update		: 
*	etc			: 
********************************************************************/
void InitTmrCtrFlgClr()
{
	S2b i;
	
	// �^�C�}�f�[�^
	for (i=0;i<SEQ_TD_SIZE;i++) {
		SEQ_TMR_DATA[i * 3 + 0] = 0;
		SEQ_TMR_DATA[i * 3 + 1] = 0;
		SEQ_TMR_DATA[i * 3 + 2] = 0;
	}
	
	// �J�E���^�f�[�^
	for (i = 0; i < SEQ_CD_SIZE; i++) {
		SEQ_CTR_DATA[i * 3 + 0]=0;
		SEQ_CTR_DATA[i * 3 + 1]=0;
		SEQ_CTR_DATA[i * 3 + 2]=0;
	}
	
	// �t���O
	for (i = 0; i < SEQ_CARD_MAX; i++) {
		SEQ_SR_FLG[i]=0;
	}
}

/********************************************************************
*	Function	: ��M
*	Param		: None
*	Return		: 0�FOK  -1�FNG
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqScifRev(void)
{
	unsigned char	chBuff[LD_FLM_MAX];
	ER				ercd;
	unsigned short	loop1;
	long_data_st	data;
	unsigned char	*s_ptr,*d_ptr;

	unsigned short	*test;				// �ʐM�װ�m�F�p
	unsigned short	ii;

	// �f�[�^��M�҂�

//[koma]	ercd = SCIF_RecvDataNBlock(SER_CHN1, chBuff, sizeof(chBuff));

	// ����M�ڰэ쐬
	if(!SeqRevEnd){											// ��M�����m�F
		if(ercd){											// ��M�ް������鎞
			SEQ_LD_TIMOUT = T1S;							// ��ް°� �ʐM��ѱ�Ķ����ݒ�(1�b)
			// ��M�ڰэ쐬����
			for(loop1 = 0 ; loop1 < ercd; loop1++){			// ��M�ް�����������
															// ��M�ް�����������
				if(SeqRevStat == 0){						// ���ĺ��ޑ҂�
					if(chBuff[loop1] == CODE_STX){			// ���ĺ��ފm�F
						SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];	// ��M�ڰт֊i�[
						SeqRevFlmCnt++;						// ��M�ڰѶ����X�V
						SeqLdErr = FALSE;					// �ʐM��-�׸�OFF
						SeqRevDataCnt = 0;					// ��M�ް��������ر
						SeqRevBcc = 0;						// BCC���Zڼ޽��ر ADD 091203akiba
						SeqRevStat = 1;						// 
					}
				}else if(SeqRevStat == 1){					// ��M�ް����҂�
					if(SeqRevFlmCnt == 1){					// ��M�ް�������(L)�̎�
						SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];
															// ��M�ڰт֊i�[
					}else if(SeqRevFlmCnt == 2){			// ��M�ް�������(H)�̎�
						SeqRevBuff[SeqRevFlmCnt] = data.ub_dat[0] = chBuff[loop1];
															// �ް��i�[
						data.ub_dat[1] = SeqRevBuff[(SeqRevFlmCnt - 1)];
						SeqRevDataCnt = data.uw_dat[0];		// ��M�ް��������֊i�[
						SeqRevStat = 2;						// BCC�҂��֑J��
					}else{
						SeqLdErr = TRUE;					// �ʐM��-�׸�ON
						break;
					}
					SeqRevFlmCnt++;							// ��M�ڰѶ����X�V
					SeqRevBcc += chBuff[loop1];				// BCC�ް����Z ADD 091203akiba
				}else if(SeqRevStat == 2){					// BCC�҂�
					SeqRevBuff[SeqRevFlmCnt] = chBuff[loop1];	// ��M�ڰт֊i�[
					if(SeqRevDataCnt > 1){					// ��M�ް����m�F
						SeqRevFlmCnt++;						// ��M�ڰѶ����X�V
						SeqRevBcc += chBuff[loop1];			// BCC�ް����Z
						SeqRevDataCnt --;					// ��M�ް��������X�V
					}else{
						SeqRevBcc = (0x00 - SeqRevBcc) & 0x00FF;
															// BCC�Z�o
						if(SeqRevBcc == chBuff[loop1]){		// BCC����
							SeqRevEnd = TRUE;				// ��M���튮��
							SeqLdErr = FALSE;				// �ʐM��-�׸�OFF
							// add 091218 akiba
							d_ptr = &(SeqRev.sSCodeFlg);	// �i�[�擪���ڽ�i�[
							for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++){
								*d_ptr = SeqRevBuff[loop1];	// �ް��i�[
							}
							SeqLdRevFlmChk();				// ��M�ڰ�ͯ�ޕ��m�F
						}else{
#if	1
							// �ʐM�G���[�J�E���g ADD 091221 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
							*test = *test + 1;
#else
#if	1
							// �ʐM�G���[�J�E���g ADD 091221 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
							test = test + 1;
							*test = *test + 1;
							// �ʐM�G���[�J�E���g ADD 100105 akiba
							test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoM];
							for(loop1 = 0 ; loop1 < 256; loop1++){
								data.ub_dat[0] = SeqRevBuff[(ii + 0)];
								data.ub_dat[1] = SeqRevBuff[(ii + 1)];
								*test = data.uw_dat[0];
								test ++;
								ii = ii + 2;
							}
#endif
#endif

							SeqRevEnd = FALSE;				// ��M�ُ튮��
							SeqLdErr = TRUE;				// �ʐM��-�׸�ON

						}
						SeqRevStat = 0;						// ���ĺ��ޑ҂��֑J��
						SeqRevFlmCnt = 0;					// ��M�ڰѶ��ĸر
						SeqRevDataCnt = 0;					// ��M�ް��������֊i�[
						SeqRevBcc = 0;						// BCC���Zڼ޽��ر
						break;
					}
				}else{
					SeqRevStat = 0;							// ���ĺ��ޑ҂��֑J��
				}
			}
		}

		if(SEQ_LD_TIMOUT == 0){								// ��ް°� �ʐM��ѱ�Ċm�F(1�b)
			SeqLdErr = TRUE;								// �ʐM��-�׸�ON
#if	0
			// �ʐM�G���[�J�E���g ADD 091221 akiba
			test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
			*test = *test + 1;
#endif
		}

		if(SeqLdErr){										// �ʐM�װ�m�F
			SeqLdScifErr();									// ����M��񏉊�������
		}
	}else{
		if(SeqSendStat == 0){								// ��M�ޯ̧��߰/�v������ލ쐬
#if	0
			d_ptr = &(SeqRev.sSCodeFlg);					// �i�[�擪���ڽ�i�[
			for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++){
				*d_ptr = SeqRevBuff[loop1];					// �ް��i�[
			}

			SeqLdRevFlmChk();								// ��M�ڰ�ͯ�ޕ��m�F
#endif
			SeqLdCMD = (((unsigned short)SeqRev.CMND << 8) | (unsigned short)SeqRev.MODE);
															// �v������ގZ�o
			SeqLdEnd = SeqRev.endInfo;						// �I�����
			SeqLdNo = SeqRev.seqNumber;						// ���ݽ�ԍ�
			data.ub_dat[1] = SeqRev.BYTEN[0];
			data.ub_dat[0] = SeqRev.BYTEN[1];
			SeqLdByte = data.uw_dat[0];						// �Ǐoܰ�ސ�
			SeqSendStat = 1;								// ��M�ް����/������/���M�ڰэ쐬�֑J��
		}else if(SeqSendStat == 1){							// ��M�ް����/������/���M�ڰэ쐬����
			SeqLdSendProg();								// ��M�ް����/������/���M�ڰэ쐬�������s
			SeqSendStat = 2;								// ���M�ޯ̧�쐬�����֑J��
		}else if(SeqSendStat == 2){							// ���M�ޯ̧�쐬����
			d_ptr = &(SeqSendBuff[0]);						// �i�[�������ڽ�i�[
			s_ptr = &(SeqSend.sSCodeFlg);					// �i�[�擪���ڽ�i�[
			for(loop1 = 0 ; loop1 < LD_FLM_MAX; loop1++, d_ptr++, s_ptr++){
				*d_ptr = *s_ptr;							// �ް��i�[
			}
			SeqSendStat = 0;								// ��M�ޯ̧��߰/�v������ލ쐬�֑J��
			SeqScifStat = 1;								// ���M�ðĂ֑J��
		}else{
			SeqSendStat = 0;								// ��M�ޯ̧��߰/�v������ލ쐬�֑J��
		}
	}
}

/********************************************************************
*	Function	: ���M
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqScifSend(void)
{
	UB				chBuff[LD_FLM_MAX];
	ER				ercd;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	unsigned short	*test;									// �ʐM�װ�m�F�p

	SeqLdSendFlmChk();										// ���M�ڰ�ͯ�ޕ��m�F add 091229 akiba

	if(!SeqSendFlmErr){
		s_ptr = &SeqSendBuff[0];
		d_ptr = &chBuff[0];
		for(loop1 = 0; loop1 < SeqSendCnt; loop1++, *s_ptr++, *d_ptr++){
			*d_ptr = *s_ptr;
		}
//[koma]		ercd = SCIF_SendData(SER_CHN1, chBuff, SeqSendCnt);	// ���M

//		// ���M������(0�͖����M)
//		if(ercd <= 0){
//			SeqLdErr = TRUE;								// �ʐM��-�׸�ON
//		}

		SeqSendCnt -= ercd;
		if(SeqSendCnt == 0){
			SeqLdScifErr();									// ����M��񏉊�������
		}else{
			SeqLdErr = TRUE;								// �ʐM��-�׸�ON
#if	1
			// �m�F�p���� add 091229 akiba
			test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
			test = test + 3;
			*test ++;
#endif
		}
	}else{
#if	1
		// �m�F�p���� add 091229 akiba
		test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
		test = test + 4;
		*test ++;
#endif
		SeqSendFlmErr = FALSE;
		SeqLdErr = TRUE;
	}

	SeqScifStat = 0;										// ��M�ðĂ֑J��
	if(SeqLdErr){
		SeqLdScifErr();										// ����M��񏉊�������
	}
}


/********************************************************************
*	Function	: ����M��񏉊�������
*	Param		: None
*	Return		: None
*	Date		: 09/11/19	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdScifErr(void)
{
	unsigned short	loop1;
	unsigned char	*d_ptr1;
	unsigned char	*d_ptr2;
	unsigned short	*d_ptr3;
	unsigned char	*d_ptr4;
	unsigned char	*d_ptr5;

#if	0
	for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++){	// �ޯ̧��ظر
		SeqRevBuff[loop1] = 0x00;
		SeqSendBuff[loop1] = 0x00;
		SeqLdWk[loop1] = 0x00;
	}
#else
	d_ptr1 = &SeqRevBuff[0];
	d_ptr2 = &SeqSendBuff[0];
	d_ptr3 = &SeqLdWk[0];
	d_ptr4 = &(SeqRev.sSCodeFlg);
	d_ptr5 = &(SeqSend.sSCodeFlg);
	for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++, *d_ptr1++, *d_ptr2++, *d_ptr3++, *d_ptr4++, *d_ptr5++){
		*d_ptr1 = *d_ptr2 = *d_ptr4 = *d_ptr5 = 0x00;
		*d_ptr3 = 0x0000;							// �ޯ̧��ظر
	}
#endif

	SeqScifStat = 0;								// ��M�ðĂ֑J��
	SeqRevStat = 0;									// ���ĺ��ޑ҂��֑J��
	SeqRevFlmCnt = 0;								// ��M�ڰѶ��ĸر
	SeqRevDataCnt = 0;								// ��M�ް��������֊i�[
	SeqRevEnd = FALSE;								// ��M������
	SeqRevBcc = 0;									// BCC���Zڼ޽��ر
	SeqLdErr = FALSE;								// �ʐM��-�׸�OFF
	SeqSendStat = 0;								// ��M�ޯ̧��߰�֑J��
	SeqSendFlmCnt = 0;								// ��M�ڰѶ��ĸر
	SeqSendByte = 0;								// �ް����޲Đ������ر
	SeqSendBcc = 0;									// BCC�Z�o�pڼ޽��ر
	SeqSendCnt = 0;									// ���M�޲Đ������ر
	SeqSendDcnt = 0;								// �ް�ܰ�ސ������ر
	SeqSendMem = 0;									// ��ؐ��i�[ڼ޽�
	SeqLdCMD = 0;									// ��������ފi�[ڼ޽��ر
//	SeqLdTmOutCnt = 0;								// ��ѱ�Č��o�����ر
	SEQ_LD_TIMOUT = 100;							// ��ް°� �ʐM��ѱ�Ķ����ݒ�(1�b)
	SeqLdEnd = 0;									// �I�����ر
	SeqLdNo = 0;									// ���ݽ�ԍ�������
	SeqBit = 0;										// Bit�ر
}


/********************************************************************
*	Function	: ��M�t���[���G���[�`�F�b�N
*	Param		: None
*	Return		: None
*	Date		: 09/12/15	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRevFlmChk(void)
{

	long_data_st	data;

	if(SeqRev.sSCodeFlg != CODE_STX){			// ���ĺ�������(0x5A�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[1] = SeqRev.datacnt[0];			// �ް������� L
	data.ub_dat[0] = SeqRev.datacnt[1];			// �ް������� H
	if(data.uw_dat[0] > (LD_FLM_MAX - 3)){		// ����(�ő�509�޲Ĉȉ�������)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.procStatus != 0xFF){				// �����ð������(0xFF�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.conectMode != 0x7A){				// �ڑ���������(0x7A�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[1] = SeqRev.tmId[0];			// �ڑ�ID L
	data.ub_dat[0] = SeqRev.tmId[1];			// �ڑ�ID H
	if(data.uw_dat[0] != 0x0000){				// �ڑ�ID ����(0x0000�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.kindCode != 0x11){				// �@��݊���������(0x11�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.tmILCode != 0x00){				// �`������ۯ���������(0x00�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	data.ub_dat[3] = SeqRev.passwd[0];			// �߽ܰ�� LL
	data.ub_dat[2] = SeqRev.passwd[1];			// �߽ܰ�� LH
	data.ub_dat[1] = SeqRev.passwd[2];			// �߽ܰ�� HL
	data.ub_dat[0] = SeqRev.passwd[3];			// �߽ܰ�� HH
	if(data.ul_dat != 0x00000000){				// �߽ܰ�� ����(0x00000000�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.endInfo > 0x01){					// �I���������(0x00,0x01�̂ݐ���)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}

	if(SeqRev.seqNumber == 0x00){				// ���ݽ�ԍ�����(0x00�ȊO����)
		SeqRasCode = SeqRasFlmErr;
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: ���M�t���[���G���[�`�F�b�N
*	Param		: None
*	Return		: None
*	Date		: 09/12/29	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendFlmChk(void)
{

	long_data_st	data;

	if(SeqSendBuff[0] != CODE_STX){				// ���ĺ�������(0x5A�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[1] = SeqSendBuff[1];			// �ް������� L
	data.ub_dat[0] = SeqSendBuff[2];			// �ް������� H
	if(data.uw_dat[0] > (LD_FLM_MAX - 3)){		// ����(�ő�509�޲Ĉȉ�������)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[3] == 0xFF){					// �����ð������(0xFF�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[4] != 0x7A){					// �ڑ���������(0x7A�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[1] = SeqSendBuff[5];			// �ڑ�ID L
	data.ub_dat[0] = SeqSendBuff[6];			// �ڑ�ID H
	if(data.uw_dat[0] != 0x0000){				// �ڑ�ID ����(0x0000�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[7] != 0x11){					// �@��݊���������(0x11�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[8] != 0x00){					// �`������ۯ���������(0x00�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	data.ub_dat[3] = SeqSendBuff[9];			// �߽ܰ�� LL
	data.ub_dat[2] = SeqSendBuff[10];			// �߽ܰ�� LH
	data.ub_dat[1] = SeqSendBuff[11];			// �߽ܰ�� HL
	data.ub_dat[0] = SeqSendBuff[12];			// �߽ܰ�� HH
	if(data.ul_dat != 0x00000000){				// �߽ܰ�� ����(0x00000000�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[15] > 0x01){					// �I���������(0x00,0x01�̂ݐ���)
		SeqSendFlmErr = TRUE;
	}

	if(SeqSendBuff[16] == 0x00){				// ���ݽ�ԍ�����(0x00�ȊO����)
		SeqSendFlmErr = TRUE;
	}
}


/********************************************************************
*	Function	: �v���R�}���h�����^���M�t���[���쐬
*	Param		: None
*	Return		: None
*	Date		: 09/11/21	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendProg(void)
{

	unsigned short	loop1;
	unsigned char	*d_ptr;

	unsigned short	*test;				// �ʐM�װ�m�F�p

	switch(SeqLdCMD){
		case LD_ADR_RD:
			SeqLdAdrRd();					// ���ڽ�Ǐo����
			break;

		case LD_1POU_RD:
			SeqLd1PouRd();					// 1POU�Ǐo����
			break;

		case LD_RTC_RD:
			SeqLdRtcRd();					// ����ޓǏo����
			break;

		case LD_POU_File_RD:
			SeqLdPouFileRd();				// POU̧�ُ��Ǐo����
			break;

		case LD_ADR_WR:
			SeqLdAdrWr();					// ���ڽ��������
			break;

		case LD_1POU_WR:
			SeqLd1PouWr();					// 1POU��������
			break;

		case LD_RTC_WR:
			SeqLdRtcWr();					// ����ސݒ菈��
			break;

		case LD_MEM_CLR_WR:
			SeqLdMemClrWr();				// �ް���ظر����
			break;

		case LD_MONI_RD:
			SeqLdMoniRd();					// ����Ǐo����
			break;

		case LD_Start_WR:
			SeqLdStartWr();					// �ꊇ�N������
			break;

		case LD_Stop_WR:
			SeqLdStopWr();					// �ꊇ��~����
			break;

		case LD_DownLoad_End:
			SeqLdDownLoadEnd();				// �޳�۰�ޏI���ʒm����
			break;

		case LD_Data_chg_WR:
			SeqLdDataChgWr();				// �ް��ύX����
			break;

		case LD_Set_WR:
			SeqLdSetWr();					// �����ݒ�o�^����
			break;

		case LD_Reset_WR:
			SeqLdResetWr();					// �����ݒ��������
			break;

		case LD_Statas_RD:
			SeqLdStatasRd();				// �ð���Ǐo����
			break;

		default:
			SeqRasCode = SeqRasNoCmd;		// ����`����޴װ
			SeqRasFlg = TRUE;
			break;
	}

	if(SeqRasFlg){
		d_ptr = &(SeqSend.sSCodeFlg);
		for(loop1 = 0; loop1 <= LD_FLM_MAX; loop1++, *d_ptr++){
			*d_ptr = 0x00;					// �ޯ̧��ظر
		}
		SeqSendFlmSet(SeqLdCMD);			// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		SeqSend.procStatus = SeqRasCode;	// �����ð���i�[(����`�����)
//		data.uw_dat[0] = 0;					// �ް����޲Đ��i�[
		SeqLdSendBcc(0);					// ���M�pBCC/�ް��������i�[�������s
		SeqRasFlg = SeqRasCode = 0;

#if	1
		// �ʐM�G���[�J�E���g ADD 091221 akiba
		test = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoL];
		test = test + 2;
		*test = *test + 1;
#endif

	}

}


/********************************************************************
*	Function	: �A�h���X�Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdAdrRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ��؎��
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[1];
	data.ub_dat[2] = SeqRev.data[2];
	data.ub_dat[1] = SeqRev.data[3];
	SeqMAdr[0] = data.ul_dat;								// ��ر��ڽ
	data.ub_dat[1] = SeqRev.data[4];
	data.ub_dat[0] = SeqRev.data[5];
	SeqRdWdCnt = data.uw_dat[0];							// �Ǐoܰ�ސ�

	if(SeqMKind[0] <= MkindNoMax){
		if(SeqRdWdCnt > (LD_DATA_MAX_W - 3)){				// �Ǐoܰ�ސ����ް�m�F
			SeqRdWdCnt = (LD_DATA_MAX_W - 3);
		}
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		d_ptr += SeqMAdr[0];								// �w����ڽ�i�[
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++, *d_ptr++){
			data.uw_dat[0] = *d_ptr;						// �ް����o��
			SeqLdWk[wk1] = data.ub_dat[1];
			SeqLdWk[wk1 + 1] = data.ub_dat[0];
			wk1 = wk1 + 2;
		}

		SeqSendFlmSet(LD_ADR_RD);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		SeqSend.data[0] = SeqMKind[0];						// ��؎�ʊi�[
		data.ul_dat = SeqMAdr[0];							// ��ر��ڽ�i�[
		SeqSend.data[1] = data.ub_dat[3];
		SeqSend.data[2] = data.ub_dat[2];
		SeqSend.data[3] = data.ub_dat[1];
		SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++){		// �Ǐo�ް��i�[
			SeqSend.data[(SeqSendFlmCnt + 6)] = SeqLdWk[wk1];
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqLdWk[wk1 + 1];
			SeqSendFlmCnt = SeqSendFlmCnt + 2;
			wk1 = wk1 + 2;
			SeqSendDcnt ++;
		}
		data.uw_dat[0] = SeqSendDcnt;						// �Ǐoܰ�ސ��i�[
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
		data.uw_dat[0] = 6 + (SeqSendDcnt * 2);				// �ް����޲Đ��i�[
		// 6 = (��؎�� + ��ر��ڽ + �Ǐoܰ�ސ�)
		// * 2 = ܰ�ސ� �� �޲Đ�
		SeqLdSendBcc(data.uw_dat[0]);						// ���M�pBCC/�ް��������i�[�������s

	}else{
		SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: �P�o�n�t�Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLd1PouRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqPOU = data.uw_dat[0];								// POU�w��
	data.ub_dat[1] = SeqRev.data[2];
	data.ub_dat[0] = SeqRev.data[3];
	SeqRdWdCnt = data.uw_dat[0];							// �Ǐoܰ�ސ�

	if(SeqPOU == 1){
		SeqPouSize = SeqPOU1.Size;
		SeqSptData = SeqPOU1.Spt;
		SeqTemSize = SeqPOU1.Tem;
	}else if(SeqPOU == 2){
		SeqPouSize = SeqPOU2.Size;
		SeqSptData = SeqPOU2.Spt;
		SeqTemSize = SeqPOU2.Tem;
	}else if(SeqPOU == 3){
		SeqPouSize = SeqPOU3.Size;
		SeqSptData = SeqPOU3.Spt;
		SeqTemSize = SeqPOU3.Tem;
	}else{
		SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
		SeqRasFlg = TRUE;
	}
	if(!SeqRasFlg){
		if(SeqLdNo == 1){
			SeqRdWdCntBak = 0;
			if(SeqPouSize < (LD_DATA_MAX_W - 5)){
				SeqPOULpCnt = SeqPouSize;
				SeqRdWdCntBak = 0;
				SeqLdEnd = 0;
			}else{
				SeqRdWdCntBak = SeqPouSize - (LD_DATA_MAX_W - 5);
				SeqPOULpCnt = (LD_DATA_MAX_W - 5);
				SeqLdEnd = 1;
			}
		}else{
			if(SeqRdWdCntBak < LD_DATA_MAX_W){
				SeqPOULpCnt = SeqRdWdCntBak;
				SeqRdWdCntBak = 0;
				SeqLdEnd = 0;
			}else{
				SeqRdWdCntBak = SeqRdWdCntBak - LD_DATA_MAX_W;
				SeqPOULpCnt = LD_DATA_MAX_W;
				SeqLdEnd = 1;
			}
		}
		if(SeqPOU == 1){
			d_ptr = &SeqPOU1.Cmd[0];						// POU1 Top���ڽ�i�[
		}else if(SeqPOU == 2){
			d_ptr = &SeqPOU2.Cmd[0];						// POU2 Top���ڽ�i�[
		}else if(SeqPOU == 3){
			d_ptr = &SeqPOU3.Cmd[0];						// POU3 Top���ڽ�i�[
		}
		if(SeqLdNo > 1){
			d_ptr += ((LD_DATA_MAX_W * (SeqLdNo - 2)) + (LD_DATA_MAX_W - 5));
		}
		wk1 = 0;
		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++, *d_ptr++){
			data.uw_dat[0] = *d_ptr;						// �ް����o��
			SeqLdWk[wk1] = data.ub_dat[0];					// add 091204akiba
			SeqLdWk[wk1 + 1] = data.ub_dat[1];				// add 091204akiba
			wk1 = wk1 + 2;
		}

		SeqSendFlmSet(LD_1POU_RD);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		if(SeqLdNo == 1){
			data.uw_dat[0] = SeqPOU;						// POU�w��i�[
			SeqSend.data[0] = data.ub_dat[1];
			SeqSend.data[1] = data.ub_dat[0];
			data.uw_dat[0] = SeqPouSize;					// ���ފi�[
			SeqSend.data[2] = data.ub_dat[1];
			SeqSend.data[3] = data.ub_dat[0];
			data.ul_dat = SeqSptData;						// �⏕���i�[
			SeqSend.data[4] = data.ub_dat[3];
			SeqSend.data[5] = data.ub_dat[2];
			SeqSend.data[6] = data.ub_dat[1];
			SeqSend.data[7] = data.ub_dat[0];
			data.uw_dat[0] = SeqTemSize;					// �����ػ��ފi�[
			SeqSend.data[8] = data.ub_dat[1];
			SeqSend.data[9] = data.ub_dat[0];
			SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
			for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){		// �Ǐo�ް��i�[
				SeqSend.data[(SeqSendFlmCnt + 10)] = SeqLdWk[wk1];
				SeqSend.data[(SeqSendFlmCnt + 11)] = SeqLdWk[wk1 + 1];
				SeqSendFlmCnt += 2;
				wk1 += 2;
				SeqSendDcnt ++;
			}
		}else{
			SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
			for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){		// �Ǐo�ް��i�[
				SeqSend.data[(SeqSendFlmCnt + 0)] = SeqLdWk[wk1];
				SeqSend.data[(SeqSendFlmCnt + 1)] = SeqLdWk[wk1 + 1];
				SeqSendFlmCnt += 2;
				wk1 += 2;
				SeqSendDcnt ++;
			}
		}
		if(SeqLdNo <= 1){
			data.uw_dat[0] = 10 + (SeqSendDcnt * 2);		// �ް����޲Đ��i�[
			// 10 = (POU�w�� + ���� + �⏕��� + �����ػ���)
			// * 2 = ܰ�ސ� �� �޲Đ�
		}else{
			data.uw_dat[0] = (SeqSendDcnt * 2);				// �ް����޲Đ��i�[
		}
		SeqLdSendBcc(data.uw_dat[0]);						// ���M�pBCC/�ް��������i�[�������s
	}
}


/********************************************************************
*	Function	: �J�����_�Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRtcRd(void)
{

	long_data_st	data;

	SeqSendFlmSet(LD_RTC_RD);					// ���M�ڰѺ����ͯ�ޕ��쐬�������s
	data.ul_dat = SeqRtcData;					// ����ޏ���߰
	SeqSend.data[0] = data.ub_dat[3];
	SeqSend.data[1] = data.ub_dat[2];
	SeqSend.data[2] = data.ub_dat[1];
	SeqSend.data[3] = data.ub_dat[0];
//	data.uw_dat[0] = 4;							// �ް����޲Đ��i�[
	// 4 = ����ޏ��
	SeqLdSendBcc(4);							// ���M�pBCC/�ް��������i�[�������s
}


/********************************************************************
*	Function	: �o�n�t�t�@�C�����Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdPouFileRd(void)
{

	long_data_st	data;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqPOU = data.uw_dat[0];							// POU�w��

	SeqSendFlmSet(LD_POU_File_RD);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s
	SeqSendDcnt = SeqSendFlmCnt = 0;
	if((SeqPOU1.Code1 == SeqCmdCode1) && (SeqPOU1.Code2 == SeqCmdCode2) && (SeqPOU1.Size != 0)){
		SeqSend.data[2] = 1;							// POU�w��i�[
		SeqSend.data[3] = 0;
		data.uw_dat[0] = SeqPOU1.Size;					// ���ފi�[
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
		data.ul_dat = SeqPOU1.Spt;						// �⏕���i�[
		SeqSend.data[6] = data.ub_dat[3];
		SeqSend.data[7] = data.ub_dat[2];
		SeqSend.data[8] = data.ub_dat[1];
		SeqSend.data[9] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU1.Tem;					// �����ػ��ފi�[
		SeqSend.data[10] = data.ub_dat[1];
		SeqSend.data[11] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	if((SeqPOU2.Code1 == SeqCmdCode1) && (SeqPOU2.Code2 == SeqCmdCode2) && (SeqPOU2.Size != 0)){
		SeqSend.data[(SeqSendFlmCnt + 2)] = 2;			// POU�w��i�[
		SeqSend.data[(SeqSendFlmCnt + 3)] = 0;
		data.uw_dat[0] = SeqPOU2.Size;					// ���ފi�[
		SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[0];
		data.ul_dat = SeqPOU2.Spt;						// �⏕���i�[
		SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[3];
		SeqSend.data[(SeqSendFlmCnt + 7)] = data.ub_dat[2];
		SeqSend.data[(SeqSendFlmCnt + 8)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 9)] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU2.Tem;					// �����ػ��ފi�[
		SeqSend.data[(SeqSendFlmCnt + 10)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 11)] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	if((SeqPOU3.Code1 == SeqCmdCode1) && (SeqPOU3.Code2 == SeqCmdCode2) && (SeqPOU3.Size != 0)){
		SeqSend.data[(SeqSendFlmCnt + 2)] = 3;			// POU�w��i�[
		SeqSend.data[(SeqSendFlmCnt + 3)] = 0;
		data.uw_dat[0] = SeqPOU3.Size;					// ���ފi�[
		SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[0];
		data.ul_dat = SeqPOU3.Spt;						// �⏕���i�[
		SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[3];
		SeqSend.data[(SeqSendFlmCnt + 7)] = data.ub_dat[2];
		SeqSend.data[(SeqSendFlmCnt + 8)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 9)] = data.ub_dat[0];
		data.uw_dat[0] = SeqPOU3.Tem;					// �����ػ��ފi�[
		SeqSend.data[(SeqSendFlmCnt + 10)] = data.ub_dat[1];
		SeqSend.data[(SeqSendFlmCnt + 11)] = data.ub_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
		SeqSendDcnt ++;
	}
	data.uw_dat[0] = SeqSendDcnt;						// �o�n�t���i�[
	SeqSend.data[0] = data.ub_dat[1];
	SeqSend.data[1] = data.ub_dat[0];
	data.uw_dat[0] = 2 + (SeqSendDcnt * 10);			// �ް����޲Đ��i�[
	// 2 = �Ǐo̧�ِ�
	// 10 = ̧�ُ��
	SeqLdSendBcc(data.uw_dat[0]);						// ���M�pBCC/�ް��������i�[�������s
}


/********************************************************************
*	Function	: �A�h���X�����R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdAdrWr(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ��؎��
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[1];
	data.ub_dat[2] = SeqRev.data[2];
	data.ub_dat[1] = SeqRev.data[3];
	SeqMAdr[0] = data.ul_dat;								// ��ر��ڽ
	data.ub_dat[1] = SeqRev.data[4];
	data.ub_dat[0] = SeqRev.data[5];
	SeqRdWdCnt = data.uw_dat[0];							// ����ܰ�ސ�
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++){			// �����ް�
		data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
		data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 7)];
		SeqWrData[loop1] = data.uw_dat[0];
		SeqSendFlmCnt = SeqSendFlmCnt + 2;
	}

	if(SeqMKind[0] <= MkindNoMax){
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		d_ptr += SeqMAdr[0];								// �w����ڽ�i�[
		SeqSendDcnt = 0;
		for(loop1 = 0; loop1 < SeqRdWdCnt; loop1++, *d_ptr++){
			*d_ptr = SeqWrData[loop1];						// �ް�����
			SeqSendDcnt ++;
		}

		SeqSendFlmSet(LD_ADR_WR);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		SeqSend.data[0] = SeqMKind[0];						// ��؎�ʊi�[
		data.ul_dat = SeqMAdr[0];							// ��ر��ڽ�i�[
		SeqSend.data[1] = data.ub_dat[3];
		SeqSend.data[2] = data.ub_dat[2];
		SeqSend.data[3] = data.ub_dat[1];
		data.uw_dat[0] = SeqSendDcnt;						// ����ܰ�ސ��i�[
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = data.ub_dat[0];
//		data.uw_dat[0] = 6;									// �ް����޲Đ��i�[
		// 6 = (��؎�� + ��ر��ڽ + ����ܰ�ސ�)
		SeqLdSendBcc(6);									// ���M�pBCC/�ް��������i�[�������s
	}else{
		SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: �P�o�n�t�����R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLd1PouWr(void)
{

	long_data_st	data;
	unsigned long	*d_ptr_L;
	unsigned short	*d_ptr_W;
	unsigned short	loop1;

	if(SeqCpuRun){
		SeqRasCode = SeqRasCpuRun;							// CPU�^�]���װ
		SeqRasFlg = TRUE;
	}
	if(SeqLdNoBak == SeqLdNo){
		SeqSendDataCnt = SeqSendDataCntBak;
	}else if((SeqLdNoBak + 1) == SeqLdNo){
	}else{
		SeqRasCode = SeqRasParaErr;							// �������Ұ��ُ�װ
		SeqRasFlg = TRUE;
	}
	SeqLdNoBak = SeqLdNo;
	if(SeqLdNo == 1){
		data.ub_dat[1] = SeqRev.data[0];
		data.ub_dat[0] = SeqRev.data[1];					// POU�ԍ�
		data.ub_dat[3] = SeqRev.data[2];
		data.ub_dat[2] = SeqRev.data[3];					// ����
		if(data.uw_dat[0] == 1){
			if(data.uw_dat[1] > POU1SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POU�ï�ߐ����ް�װ
				SeqRasFlg = TRUE;
			}
		}else if(data.uw_dat[0] == 2){
			if(data.uw_dat[1] > POU2SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POU�ï�ߐ����ް�װ
				SeqRasFlg = TRUE;
			}
		}else if(data.uw_dat[0] == 3){
			if(data.uw_dat[1] > POU3SizeMax){
				SeqRasCode = SeqRasStepOver;				// 1POU�ï�ߐ����ް�װ
				SeqRasFlg = TRUE;
			}
		}else{
			SeqRasCode = SeqRasDataTypErr;					// �ް��w��ُ�װ
			SeqRasFlg = TRUE;
		}
	}

	if(!SeqRasFlg){
		if(SeqLdNo == 1){
			data.ub_dat[1] = SeqRev.data[0];
			data.ub_dat[0] = SeqRev.data[1];
			SeqPOU = data.uw_dat[0];						// POU�w��
			data.ub_dat[1] = SeqRev.data[2];
			data.ub_dat[0] = SeqRev.data[3];
			SeqPouSize = data.uw_dat[0];					// ���ފi�[
			data.ub_dat[3] = SeqRev.data[4];
			data.ub_dat[2] = SeqRev.data[5];
			data.ub_dat[1] = SeqRev.data[6];
			data.ub_dat[0] = SeqRev.data[7];
			SeqSptData = data.ul_dat;						// �⏕���i�[
			data.ub_dat[1] = SeqRev.data[8];
			data.ub_dat[0] = SeqRev.data[9];
			SeqTemSize = data.uw_dat[0];					// �����ػ��ފi�[
			if(SeqPOU == 1){
				d_ptr_L = &SeqPOU1.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU1.Code1 = SeqCmdCode1;
				SeqPOU1.Size = SeqPouSize;
				SeqPOU1.Spt = SeqSptData;
				SeqPOU1.Tem = SeqTemSize;
			}else if(SeqPOU == 2){
				d_ptr_L = &SeqPOU2.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU2.Code1 = SeqCmdCode1;
				SeqPOU2.Size = SeqPouSize;
				SeqPOU2.Spt = SeqSptData;
				SeqPOU2.Tem = SeqTemSize;
			}else if(SeqPOU == 3){
				d_ptr_L = &SeqPOU3.Code1;
				for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
					*d_ptr_L = 0x00000000;
				}
				SeqPOU3.Code1 = SeqCmdCode1;
				SeqPOU3.Size = SeqPouSize;
				SeqPOU3.Spt = SeqSptData;
				SeqPOU3.Tem = SeqTemSize;
			}
			SeqPOULpCnt = ((SeqLdByte - 10) / 2);
			SeqSendFlmCnt = 0;
			for(loop1 = 0;loop1 < SeqPOULpCnt; loop1++){		// �����ް�
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 10)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 11)];
				SeqWrData[loop1] = data.uw_dat[0];
				SeqSendFlmCnt = SeqSendFlmCnt + 2;
			}
		}else{
			SeqPOULpCnt = (SeqLdByte / 2);
			SeqSendFlmCnt = 0;
			for(loop1 = 0;loop1 < SeqPOULpCnt; loop1++){		// �����ް�
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 0)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 1)];
				SeqWrData[loop1] = data.uw_dat[0];
				SeqSendFlmCnt = SeqSendFlmCnt + 2;
			}
		}

		if(SeqPOU == 1){
			d_ptr_W = &SeqPOU1.Cmd[0];						// POU1 Top���ڽ�i�[
			d_ptr_L = &SeqPOU1.Sum;
		}else if(SeqPOU == 2){
			d_ptr_W = &SeqPOU2.Cmd[0];						// POU2 Top���ڽ�i�[
			d_ptr_L = &SeqPOU2.Sum;
		}else if(SeqPOU == 3){
			d_ptr_W = &SeqPOU3.Cmd[0];						// POU3 Top���ڽ�i�[
			d_ptr_L = &SeqPOU3.Sum;
		}

		d_ptr_W += SeqSendDataCnt;

		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++, *d_ptr_W++){
			*d_ptr_W = SeqWrData[loop1];
			SeqSendDcnt ++;
		}
		for(loop1 = 0; loop1 < SeqPOULpCnt; loop1++){
			*d_ptr_L += SeqWrData[loop1];
		}
		SeqSendDataCntBak = SeqSendDataCnt;
		SeqSendDataCnt += SeqPOULpCnt;

		if(!SeqLdEnd){
			SeqCmpFlg = TRUE;
			if(SeqPOU == 1){
				SeqPOU1.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU1 = TRUE;
			}else if(SeqPOU == 2){
				SeqPOU2.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU2 = TRUE;
			}else if(SeqPOU == 3){
				SeqPOU3.Code2 = SeqCmdCode2;
				SeqPOUWtFlg.POU3 = TRUE;
			}
			SeqLdNoBak = 0;
			SeqSendDataCnt = 0;
			SeqSendDataCntBak = 0;
		}

		SeqSendFlmSet(LD_1POU_WR);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		data.uw_dat[0] = SeqPOU;							// POU�w��i�[
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		data.uw_dat[0] = SeqSendDcnt;						// �����ް����i�[
		SeqSend.data[2] = data.ub_dat[1];
		SeqSend.data[3] = data.ub_dat[0];
//		data.uw_dat[0] = 4;									// �ް����޲Đ��i�[
		// 4 = POU�w�� + �����ް���
		SeqLdSendBcc(4);									// ���M�pBCC/�ް��������i�[�������s
	}
}


/********************************************************************
*	Function	: �J�����_�ݒ�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdRtcWr(void)
{

	long_data_st	data;


	data.ub_dat[3] = SeqRev.data[0];
	data.ub_dat[2] = SeqRev.data[1];
	data.ub_dat[1] = SeqRev.data[2];
	data.ub_dat[0] = SeqRev.data[3];
	SeqRtcData = data.ul_dat;					// �J�����_���i�[

	SeqTimWtFlg = TRUE;							// ���v��񏑍��׸�ON(0:������,1:����)

	SeqSendFlmSet(LD_RTC_WR);					// ���M�ڰѺ����ͯ�ޕ��쐬�������s
//	data.uw_dat[0] = 0;							// �ް����޲Đ��i�[
	SeqLdSendBcc(0);							// ���M�pBCC/�ް��������i�[�������s
}

/********************************************************************
*	Function	: �f�[�^�������N���A�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 10/08/31	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SeqLdMemClrWr(void)
{
	unsigned short	loop1;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];									// ��؎��
	
	if (SeqMKind[0] == 0xFF) {
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[MkindNoM];
		SeqSendMem = MKIND_TBL[MkindNoM] + MKIND_TBL[MkindNoL];		// ��؎�ʴر�i�[
		SeqSendMem = SeqSendMem / 2;
	}
	else if ((SeqMKind[0] == MkindNoM) || (SeqMKind[0] == MkindNoL)) {
		d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[0]];
		SeqSendMem = MKIND_TBL[SeqMKind[0]];						// ��؎�ʴر�i�[
		SeqSendMem = SeqSendMem / 2;
	}
	else{
		SeqRasCode = SeqRasDataTypErr;								// �ް��w��ُ�װ
		SeqRasFlg = TRUE;
	}

	if (!SeqRasFlg) {
		for (loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++) {	// �̈��ް��ر
			*d_ptr = 0x0000;
		}
		
		InitTmrCtrFlgClr();											// ��ρE��������ظر	10/08/31 Add Y.Kobayashi
		
		SeqSendFlmSet(LD_MEM_CLR_WR);								// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		SeqSend.data[0] = SeqMKind[0];								// ��؎�ʊi�[
//		data.uw_dat[0] = 1;											// �ް����޲Đ��i�[
		// 1 = ��؎��
		SeqLdSendBcc(1);											// ���M�pBCC/�ް��������i�[�������s
	}
}

/********************************************************************
*	Function	: ���j�^�Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdMoniRd(void)
{

	long_data_st	data;
	unsigned short	wk1 = 0;
	unsigned short	loop1;
	unsigned short	*d_ptr;
	unsigned short	*s_ptr1;
	unsigned short	*s_ptr2;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqMoniCnt = data.uw_dat[0];									// ����_��
	if(SeqMoniCnt > MoniMax){
		SeqRasCode = SeqRasMoniOver;								// ����o�^�װ
		SeqRasFlg = TRUE;
	}
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
		SeqMKind[loop1] = SeqRev.data[(SeqSendFlmCnt + 2)];			// ��؎��
		if(SeqMKind[0] <= MkindNoMax){
			data.ub_dat[0] = 0x00;
			data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 4)];
			data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 5)];
			data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
			SeqMAdr[loop1] = data.ul_dat;							// ��ر��ڽ
			SeqBitData[loop1] = SeqRev.data[(SeqSendFlmCnt + 7)];	// Bit�ԍ�
			SeqDataTyp[loop1] = SeqRev.data[(SeqSendFlmCnt + 3)];	// �ް��^
			if((SeqDataTyp[loop1] != SeqDtTypB)
				&& (SeqDataTyp[loop1] != SeqDtTypW)
					&& (SeqDataTyp[loop1] != SeqDtTypL)){
				SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
				SeqRasFlg = TRUE;
			}
			SeqSendFlmCnt = SeqSendFlmCnt + 6;;
		}else{
			SeqRasCode = SeqRasDataTypErr;							// �ް��w��ُ�װ
			SeqRasFlg = TRUE;
		}
	}

	if(!SeqRasFlg){
#if	0
		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
			d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
			d_ptr += SeqMAdr[loop1];								// �w����ڽ�i�[
			switch(SeqDataTyp[loop1]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
					SeqBit = data.uw_dat[0] & SeqBit;
					if(SeqBit){
						SeqBit = 0x0001;
					}
					SeqLdWk[wk1] = SeqBit;							// �w������ް��Ǐo(bit�ް�)
					SeqLdWk[wk1 + 1] = 0;
					SeqLdWk[wk1 + 2] = 0;
					SeqLdWk[wk1 + 3] = 0;
					break;
				case	SeqDtTypW:
					data.uw_dat[0] = *d_ptr;
					SeqLdWk[wk1] = data.ub_dat[1];					// �w������ް��Ǐo(ward�ް�)
					SeqLdWk[wk1 + 1] = data.ub_dat[0];
					SeqLdWk[wk1 + 2] = 0;
					SeqLdWk[wk1 + 3] = 0;
					break;
				case	SeqDtTypL:
					data.uw_dat[1] = *d_ptr;
					d_ptr ++;
					data.uw_dat[0] = *d_ptr;
					SeqLdWk[wk1] = data.ub_dat[3];					// �w������ް��Ǐo(long�ް�)
					SeqLdWk[wk1 + 1] = data.ub_dat[2];
					SeqLdWk[wk1 + 2] = data.ub_dat[1];
					SeqLdWk[wk1 + 3] = data.ub_dat[0];
					break;
				default:
					break;
			}
			wk1 = wk1 + 4;
		}
#else
		d_ptr = &SeqKpX[0];
		s_ptr1 = &SeqKpOnX[0];
		s_ptr2 = &SeqKpOffX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++, *s_ptr1++, *s_ptr2++){
			*d_ptr = *s_ptr1;
			*d_ptr |= *s_ptr2;
		}

		d_ptr = &SeqKpY[0];
		s_ptr1 = &SeqKpOnY[0];
		s_ptr2 = &SeqKpOffY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++, *s_ptr1++, *s_ptr2++){
			*d_ptr = *s_ptr1;
			*d_ptr |= *s_ptr2;
		}

		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
			if((SeqMKind[loop1] == MkindNoX) || (SeqMKind[loop1] == MkindNoY)){
				d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
				d_ptr += SeqMAdr[loop1];								// �w����ڽ�i�[
				switch(SeqDataTyp[loop1]){
					case	SeqDtTypB:
						data.uw_dat[0] = *d_ptr;
						SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
						SeqBit = data.uw_dat[0] & SeqBit;
						if(SeqBit){
							SeqBit = 0x0001;
						}
						SeqLdWk[wk1] = SeqBit;							// �w������ް��Ǐo(bit�ް�)
						SeqLdWk[wk1 + 1] = 0;
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						if((SeqMKind[loop1] == MkindNoX)){
							data.uw_dat[0] = SeqKpX[SeqMAdr[loop1]];
							SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
							SeqBit = data.uw_dat[0] & SeqBit;
							if(SeqBit){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							data.uw_dat[0] = SeqKpY[SeqMAdr[loop1]];
							SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
							SeqBit = data.uw_dat[0] & SeqBit;
							if(SeqBit){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					case	SeqDtTypW:
						data.uw_dat[0] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[1];					// �w������ް��Ǐo(ward�ް�)
						SeqLdWk[wk1 + 1] = data.ub_dat[0];
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						if((SeqMKind[loop1] == MkindNoX)){
							if(SeqKpX[SeqMAdr[loop1]]){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							if(SeqKpY[SeqMAdr[loop1]]){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					case	SeqDtTypL:
						data.uw_dat[0] = *d_ptr;
						d_ptr ++;
						data.uw_dat[1] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[3];					// �w������ް��Ǐo(long�ް�)
						SeqLdWk[wk1 + 1] = data.ub_dat[2];
						SeqLdWk[wk1 + 2] = data.ub_dat[1];
						SeqLdWk[wk1 + 3] = data.ub_dat[0];
						if((SeqMKind[loop1] == MkindNoX)){
							data.uw_dat[1] = SeqKpX[SeqMAdr[loop1]];
							data.uw_dat[0] = SeqKpX[SeqMAdr[loop1 + 1]];
							if(data.ul_dat){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}else if(SeqMKind[loop1] == MkindNoY){
							data.uw_dat[1] = SeqKpY[SeqMAdr[loop1]];
							data.uw_dat[0] = SeqKpY[SeqMAdr[loop1 + 1]];
							if(data.ul_dat){
								SeqKpData[loop1] = cBIT6;
							}else{
								SeqKpData[loop1] = 0x0000;
							}
						}
						break;
					default:
						break;
				}
				wk1 = wk1 + 4;
			}else{
				d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
				d_ptr += SeqMAdr[loop1];								// �w����ڽ�i�[
				switch(SeqDataTyp[loop1]){
					case	SeqDtTypB:
						data.uw_dat[0] = *d_ptr;
						SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
						SeqBit = data.uw_dat[0] & SeqBit;
						if(SeqBit){
							SeqBit = 0x0001;
						}
						SeqLdWk[wk1] = SeqBit;							// �w������ް��Ǐo(bit�ް�)
						SeqLdWk[wk1 + 1] = 0;
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						SeqKpData[loop1] = 0x0000;
						break;
					case	SeqDtTypW:
						data.uw_dat[0] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[1];					// �w������ް��Ǐo(ward�ް�)
						SeqLdWk[wk1 + 1] = data.ub_dat[0];
						SeqLdWk[wk1 + 2] = 0;
						SeqLdWk[wk1 + 3] = 0;
						SeqKpData[loop1] = 0x0000;
						break;
					case	SeqDtTypL:
						data.uw_dat[0] = *d_ptr;
						d_ptr ++;
						data.uw_dat[1] = *d_ptr;
						SeqLdWk[wk1] = data.ub_dat[3];					// �w������ް��Ǐo(long�ް�)
						SeqLdWk[wk1 + 1] = data.ub_dat[2];
						SeqLdWk[wk1 + 2] = data.ub_dat[1];
						SeqLdWk[wk1 + 3] = data.ub_dat[0];
						SeqKpData[loop1] = 0x0000;
						break;
					default:
						break;
				}
				wk1 = wk1 + 4;
			}
		}
#endif

		SeqSendFlmSet(LD_MONI_RD);									// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		data.uw_dat[0] = SeqMoniCnt;								// ����_���i�[
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		SeqSendDcnt = SeqSendFlmCnt = wk1 = 0;
		for(loop1 = 0; loop1 < SeqMoniCnt; loop1++){
//			SeqSend.data[(SeqSendFlmCnt + 2)] = cBIT7;				// �׸ޏ��i�[	add 7bit�쐬
			SeqSend.data[(SeqSendFlmCnt + 2)] = (cBIT7 | SeqKpData[loop1]);	// �׸ޏ��i�[	add 6bit�쐬
			SeqSend.data[(SeqSendFlmCnt + 3)] = 0;					// ���g�p
			SeqSend.data[(SeqSendFlmCnt + 4)] = SeqLdWk[wk1];		// �ް� LL�i�[
			SeqSend.data[(SeqSendFlmCnt + 5)] = SeqLdWk[wk1 + 1];	// �ް� LH�i�[
			SeqSend.data[(SeqSendFlmCnt + 6)] = SeqLdWk[wk1 + 2];	// �ް� HL�i�[
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqLdWk[wk1 + 3];	// �ް� HH�i�[
			SeqSendFlmCnt = SeqSendFlmCnt + 6;
			wk1 = wk1 + 4;
			SeqSendDcnt++;
		}
		data.uw_dat[0] = 2 + (SeqSendDcnt * 6);						// �ް����޲Đ��i�[
		// 2 = ����_��
		// 6 = ����ް����e
		SeqLdSendBcc(data.uw_dat[0]);								// ���M�pBCC/�ް��������i�[�������s
	}
}


/********************************************************************
*	Function	: �ꊇ�N���R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdStartWr(void)
{

	unsigned short	wk1 = 0;

	wk1 = SeqSysStat & cBIT2;							// �d�̏��񒊏o
	if(wk1 != cBIT2){
		SeqSysStat = SeqSysStat & ~(cBIT2 | cBIT1);		// �^�]�J�n���i�[
		SeqSysStat = SeqSysStat | cBIT0;
		SeqRunFlg = TRUE;

		SeqSendFlmSet(LD_Start_WR);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s
//		data.uw_dat[0] = 0;								// �ް����޲Đ��i�[
		SeqLdSendBcc(0);								// ���M�pBCC/�ް��������i�[�������s
	}else{
		SeqRasCode = SeqRasCpuErr;						// CPU�ُ�װ
		SeqRasFlg = TRUE;
	}
}


/********************************************************************
*	Function	: �ꊇ��~�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdStopWr(void)
{


	SeqSysStat = SeqSysStat & ~cBIT0;		// �^�]��~���i�[
	SeqSysStat = SeqSysStat | cBIT1;
	SeqRunFlg = FALSE;

	SeqSendFlmSet(LD_Stop_WR);				// ���M�ڰѺ����ͯ�ޕ��쐬�������s
//	data.uw_dat[0] = 0;						// �ް����޲Đ��i�[
	SeqLdSendBcc(0);						// ���M�pBCC/�ް��������i�[�������s
}


/********************************************************************
*	Function	: �_�E�����[�h�I���ʒm�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdDownLoadEnd(void)
{
	unsigned long	*d_ptr_L;
	unsigned short	loop1;

	if(SeqPOUWtFlg.POU1 == FALSE){
		d_ptr_L = &SeqPOU1.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;						// �ް��ر
		}
		SeqPOU1.Code1 = SeqCmdCode1;
		SeqPOU1.Code2 = SeqCmdCode2;
	}
	if(SeqPOUWtFlg.POU2 == FALSE){
		d_ptr_L = &SeqPOU2.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;					// �ް��ر
		}
		SeqPOU2.Code1 = SeqCmdCode1;
		SeqPOU2.Code2 = SeqCmdCode2;
	}
	if(SeqPOUWtFlg.POU3 == FALSE){
		d_ptr_L = &SeqPOU3.Code1;
		for(loop1 = 0; loop1 < 0x4000; loop1++, *d_ptr_L++){
			*d_ptr_L = 0x00000000;					// �ް��ر
		}
		SeqPOU3.Code1 = SeqCmdCode1;
		SeqPOU3.Code2 = SeqCmdCode2;
	}
	SeqPOUWtFlg.POU1 = FALSE;
	SeqPOUWtFlg.POU2 = FALSE;
	SeqPOUWtFlg.POU3 = FALSE;
	SeqPOUWtEnd = TRUE;

	SeqSendFlmSet(LD_DownLoad_End);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s
//	data.uw_dat[0] = 0;									// �ް����޲Đ��i�[
	SeqLdSendBcc(0);									// ���M�pBCC/�ް��������i�[�������s

}


/********************************************************************
*	Function	: �f�[�^�ύX�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdDataChgWr(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	data.ub_dat[1] = SeqRev.data[0];
	data.ub_dat[0] = SeqRev.data[1];
	SeqChgDataCnt = data.uw_dat[0];								// �ύX�ް��_��
	if(SeqChgDataCnt > DataChgMax){
		SeqRasCode = SeqRasMoniOver;							// ����o�^�װ
		SeqRasFlg = TRUE;
	}
	SeqSendFlmCnt = 0;
	for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
		SeqMKind[loop1] = SeqRev.data[(SeqSendFlmCnt + 2)];		// ��؎��
		if(SeqMKind[0] > MkindNoMax){
			SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
			SeqRasFlg = TRUE;
			break;
		}
		SeqDataTyp[loop1] = SeqRev.data[(SeqSendFlmCnt + 3)];	// �ް��^
		data.ub_dat[0] = 0x00;
		data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 4)];
		data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 5)];
		data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 6)];
		SeqMAdr[loop1] = data.ul_dat;							// ��ر��ڽ
		SeqBitData[loop1] = SeqRev.data[(SeqSendFlmCnt + 7)];	// Bit�ԍ�
		switch(SeqDataTyp[loop1]){								// �ύX�ް�
			case	SeqDtTypB:
				SeqChgData[loop1] = SeqRev.data[(SeqSendFlmCnt + 8)];
				break;
			case	SeqDtTypW:
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 8)];
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 9)];
				SeqChgData[loop1] = data.uw_dat[0];
				break;
			case	SeqDtTypL:
				data.ub_dat[3] = SeqRev.data[(SeqSendFlmCnt + 8)];
				data.ub_dat[2] = SeqRev.data[(SeqSendFlmCnt + 9)];
				data.ub_dat[1] = SeqRev.data[(SeqSendFlmCnt + 10)];
				data.ub_dat[0] = SeqRev.data[(SeqSendFlmCnt + 11)];
				SeqChgData[loop1] = data.ul_dat;
				break;
			default:
				SeqRasCode = SeqRasDataTypErr;				// �ް��w��ُ�װ
				SeqRasFlg = TRUE;
				break;
		}
		SeqSendFlmCnt = SeqSendFlmCnt + 10;
	}

	if(!SeqRasFlg){
		for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
			d_ptr = (unsigned short *)SeqLd_MKIND_TBL_TOP[SeqMKind[loop1]];
			d_ptr += SeqMAdr[loop1];						// �w����ڽ�i�[
			switch(SeqDataTyp[loop1]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[loop1]];
					if(SeqChgData[loop1]){
						SeqBit = data.uw_dat[0] | SeqBit;
					}else{
						SeqBit = data.uw_dat[0] & ~SeqBit;
					}
					*d_ptr = SeqBit;						// �w������ް�����(bit�ް�)
					break;
				case	SeqDtTypW:
					*d_ptr = SeqChgData[loop1];				// �w������ް�����(ward�ް�)
					break;
				case	SeqDtTypL:
					data.ul_dat = SeqChgData[loop1];		// �w������ް�����(long�ް�)
					*d_ptr = data.uw_dat[0];
					d_ptr ++;
					*d_ptr = data.uw_dat[1];
					break;
				default:
					break;
			}
		}

		SeqSendFlmSet(LD_Data_chg_WR);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		data.uw_dat[0] = SeqChgDataCnt;						// �ύX�ް��_���i�[
		SeqSend.data[0] = data.ub_dat[1];
		SeqSend.data[1] = data.ub_dat[0];
		SeqSendDcnt = SeqSendFlmCnt = 0;
		for(loop1 = 0; loop1 < SeqChgDataCnt; loop1++){
			SeqSend.data[(SeqSendFlmCnt + 2)] = SeqMKind[loop1];	// ��؎�ʊi�[
			SeqSend.data[(SeqSendFlmCnt + 3)] = SeqDataTyp[loop1];	// �ް��^�i�[
			data.ul_dat = SeqMAdr[loop1];					// ��ر��ڽ�i�[
			SeqSend.data[(SeqSendFlmCnt + 4)] = data.ub_dat[3];
			SeqSend.data[(SeqSendFlmCnt + 5)] = data.ub_dat[2];
			SeqSend.data[(SeqSendFlmCnt + 6)] = data.ub_dat[1];
			SeqSend.data[(SeqSendFlmCnt + 7)] = SeqBitData[loop1];	// Bit�ԍ��i�[
			SeqSend.data[(SeqSendFlmCnt + 8)] = cBIT7;				// �����ð��
			SeqSend.data[(SeqSendFlmCnt + 9)] = 0x00;
			SeqSend.data[(SeqSendFlmCnt + 10)] = 0x00;
			SeqSend.data[(SeqSendFlmCnt + 11)] = 0x00;
			SeqSendFlmCnt = SeqSendFlmCnt + 10;
			SeqSendDcnt = SeqSendDcnt + 10;
		}
		data.uw_dat[0] = 2 + SeqSendDcnt;					// �ް����޲Đ��i�[
		// 2 = �ύX�ް��_��
		SeqLdSendBcc(data.uw_dat[0]);						// ���M�pBCC/�ް��������i�[�������s
	}
}


/********************************************************************
*	Function	: �����ݒ�o�^�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSetWr(void)
{

	long_data_st	data;
	unsigned short	*d_ptr;

	SeqMKind[0] = SeqRev.data[0];							// ��؎��
	SeqDataTyp[0] = SeqRev.data[1];							// �ް��^
	data.ub_dat[0] = 0x00;
	data.ub_dat[3] = SeqRev.data[2];
	data.ub_dat[2] = SeqRev.data[3];
	data.ub_dat[1] = SeqRev.data[4];
	SeqMAdr[0] = data.ul_dat;								// ��ر��ڽ
	SeqBitData[0] = SeqRev.data[5];							// Bit�ԍ�
	if((SeqMKind[0] != MkindNoX) && (SeqMKind[0] != MkindNoY)){
		SeqRasCode = SeqRasDataTypErr;						// �ް��w��ُ�װ
		SeqRasFlg = TRUE;
	}
	switch(SeqDataTyp[0]){
		case	SeqDtTypB:
			SeqChgData[0] = SeqRev.data[6];					// �����ް�
			break;
		case	SeqDtTypW:
			data.ub_dat[1] = SeqRev.data[6];
			data.ub_dat[0] = SeqRev.data[7];
			SeqChgData[0] = data.uw_dat[0];					// �����ް�
			break;
		case	SeqDtTypL:
			data.ub_dat[3] = SeqRev.data[6];
			data.ub_dat[2] = SeqRev.data[7];
			data.ub_dat[1] = SeqRev.data[8];
			data.ub_dat[0] = SeqRev.data[9];
			SeqChgData[0] = data.ul_dat;					// �����ް�
			break;
		default:
			SeqRasCode = SeqRasDataTypErr;					// �ް��w��ُ�װ
			SeqRasFlg = TRUE;
			break;
	}

	if(!SeqRasFlg){
		// ON���쐬
		if(SeqMKind[0] == MkindNoX){
			d_ptr = &SeqKpOnX[0];
		}else if(SeqMKind[0] == MkindNoY){
			d_ptr = &SeqKpOnY[0];
		}
		d_ptr += SeqMAdr[0];								// �w����ڽ�i�[
		switch(SeqDataTyp[0]){
			case	SeqDtTypB:
				SeqBit = SeqBit16Tbl[SeqBitData[0]];
				if(SeqChgData[0]){
					*d_ptr |= SeqBit;						// �w������ް�����(bit�ް�)
				}else{
					*d_ptr &= ~SeqBit;						// �w������ް�����(bit�ް�)
				}
				break;
			case	SeqDtTypW:
				if(SeqChgData[0]){
					*d_ptr |= SeqChgData[0];				// �w������ް�����(bit�ް�)
				}else{
					*d_ptr &= ~SeqChgData[0];				// �w������ް�����(bit�ް�)
				}
				break;
			case	SeqDtTypL:
				data.ul_dat = SeqChgData[0];
				if(SeqChgData[0]){
					*d_ptr |= data.uw_dat[0];
					d_ptr ++;
					*d_ptr |= data.uw_dat[1];				// �w������ް�����(long�ް�)
				}else{
					*d_ptr &= ~data.uw_dat[0];
					d_ptr ++;
					*d_ptr &= ~data.uw_dat[1];				// �w������ް�����(long�ް�)
				}
				break;
			default:
				break;
		}

		// OFF���쐬
		if(SeqMKind[0] == MkindNoX){
			d_ptr = &SeqKpOffX[0];
		}else if(SeqMKind[0] == MkindNoY){
			d_ptr = &SeqKpOffY[0];
		}
		d_ptr += SeqMAdr[0];								// �w����ڽ�i�[
		switch(SeqDataTyp[0]){
			case	SeqDtTypB:
				SeqBit = SeqBit16Tbl[SeqBitData[0]];
				if(SeqChgData[0]){
					*d_ptr &= ~SeqBit;						// �w������ް�����(bit�ް�)
				}else{
					*d_ptr |= SeqBit;						// �w������ް�����(bit�ް�)
				}
				break;
			case	SeqDtTypW:
				if(SeqChgData[0]){
					*d_ptr &= ~SeqChgData[0];				// �w������ް�����(bit�ް�)
				}else{
					*d_ptr |= SeqChgData[0];				// �w������ް�����(bit�ް�)
				}
				break;
			case	SeqDtTypL:
				data.ul_dat = SeqChgData[0];
				if(SeqChgData[0]){
					*d_ptr &= ~data.uw_dat[0];
					d_ptr ++;
					*d_ptr &= ~data.uw_dat[1];				// �w������ް�����(long�ް�)
				}else{
					*d_ptr |= data.uw_dat[0];
					d_ptr ++;
					*d_ptr |= data.uw_dat[1];				// �w������ް�����(long�ް�)
				}
				break;
			default:
				break;
		}

		SeqSendFlmSet(LD_Set_WR);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		SeqSend.data[0] = SeqMKind[0];						// ��؎�ʊi�[
		SeqSend.data[1] = SeqDataTyp[0];					// �ް��^�i�[
		data.ul_dat = SeqMAdr[0];							// ��ر��ڽ�i�[
		SeqSend.data[2] = data.ub_dat[3];
		SeqSend.data[3] = data.ub_dat[2];
		SeqSend.data[4] = data.ub_dat[1];
		SeqSend.data[5] = SeqBitData[0];					// Bit�ԍ��i�[
		data.uw_dat[0] = 6;									// �ް����޲Đ��i�[
		// 6 = (��؎�� + �ް��^ + ��ر��ڽ + Bit�ԍ�)
		SeqLdSendBcc(data.uw_dat[0]);						// ���M�pBCC/�ް��������i�[�������s
	}
}


/********************************************************************
*	Function	: �����ݒ�����R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdResetWr(void)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned short	*d_ptr;

	if(SeqLdByte){
		SeqMKind[0] = SeqRev.data[0];						// ��؎��
		SeqDataTyp[0] = SeqRev.data[1];						// �ް��^
		data.ub_dat[0] = 0x00;
		data.ub_dat[3] = SeqRev.data[2];
		data.ub_dat[2] = SeqRev.data[3];
		data.ub_dat[1] = SeqRev.data[4];
		SeqMAdr[0] = data.ul_dat;							// ��ر��ڽ
		SeqBitData[0] = SeqRev.data[5];						// Bit�ԍ�
		if((SeqMKind[0] != MkindNoX) && (SeqMKind[0] != MkindNoY)){
			SeqRasCode = SeqRasDataTypErr;					// �ް��w��ُ�װ
			SeqRasFlg = TRUE;
		}

		if(!SeqRasFlg){
			if(SeqMKind[0] == MkindNoX){
				d_ptr = &SeqKpOnX[0];
			}else if(SeqMKind[0] == MkindNoY){
				d_ptr = &SeqKpOnY[0];
			}
			d_ptr += SeqMAdr[0];							// �w����ڽ�i�[
			switch(SeqDataTyp[0]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[0]];
					*d_ptr = data.uw_dat[0] & ~SeqBit;	// �w������ް�����(bit�ް�)
					break;
				case	SeqDtTypW:
					*d_ptr = 0x0000;						// �w������ް�����(ward�ް�)
					break;
				case	SeqDtTypL:
					*d_ptr = 0x0000;
					d_ptr ++;
					*d_ptr = 0x0000;					// �w������ް�����(long�ް�)
					break;
				default:
					SeqRasCode = SeqRasDataTypErr;			// �ް��w��ُ�װ
					SeqRasFlg = TRUE;
					break;
			}
			if(SeqMKind[0] == MkindNoX){
				d_ptr = &SeqKpOffX[0];
			}else if(SeqMKind[0] == MkindNoY){
				d_ptr = &SeqKpOffY[0];
			}
			d_ptr += SeqMAdr[0];							// �w����ڽ�i�[
			switch(SeqDataTyp[0]){
				case	SeqDtTypB:
					data.uw_dat[0] = *d_ptr;
					SeqBit = SeqBit16Tbl[SeqBitData[0]];
					*d_ptr = data.uw_dat[0] & ~SeqBit;	// �w������ް�����(bit�ް�)
					break;
				case	SeqDtTypW:
					*d_ptr = 0x0000;						// �w������ް�����(ward�ް�)
					break;
				case	SeqDtTypL:
					*d_ptr = 0x0000;
					d_ptr ++;
					*d_ptr = 0x0000;						// �w������ް�����(long�ް�)
					break;
				default:
					break;
			}

			SeqSendFlmSet(LD_Reset_WR);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s
			SeqSend.data[0] = SeqMKind[0];					// ��؎�ʊi�[
			SeqSend.data[1] = SeqDataTyp[0];				// �ް��^�i�[
			data.ul_dat = SeqMAdr[0];						// ��ر��ڽ�i�[
			SeqSend.data[2] = data.ub_dat[3];
			SeqSend.data[3] = data.ub_dat[2];
			SeqSend.data[4] = data.ub_dat[1];
			SeqSend.data[5] = SeqBitData[0];				// Bit�ԍ��i�[
			data.uw_dat[0] = 6;								// �ް����޲Đ��i�[
			// 6 = (��؎�� + �ް��^ + ��ر��ڽ + Bit�ԍ�)
		}
	}else{
		d_ptr = &SeqKpOnX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// �̈��ް��ر
		}
		d_ptr = &SeqKpOnY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// �̈��ް��ر
		}
		d_ptr = &SeqKpOffX[0];
		SeqSendMem = MKIND_TBL[MkindNoX];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// �̈��ް��ر
		}
		d_ptr = &SeqKpOffY[0];
		SeqSendMem = MKIND_TBL[MkindNoY];
		SeqSendMem = SeqSendMem / 2;
		for(loop1 = 0; loop1 < SeqSendMem; loop1++, *d_ptr++){
			*d_ptr = 0x0000;								// �̈��ް��ر
		}

		SeqSendFlmSet(LD_Reset_WR);							// ���M�ڰѺ����ͯ�ޕ��쐬�������s
		data.uw_dat[0] = 0;									// �ް����޲Đ��i�[
	}
	SeqLdSendBcc(data.uw_dat[0]);							// ���M�pBCC/�ް��������i�[�������s
}


/********************************************************************
*	Function	: �X�e�[�^�X�Ǐo�R�}���h����
*	Param		: None
*	Return		: None
*	Date		: 09/12/14	T.Akiba		Create
*	Update		: 10/08/26	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SeqLdStatasRd(void)
{

	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	SeqSendFlmSet(LD_Statas_RD);						// ���M�ڰѺ����ͯ�ޕ��쐬�������s

	s_ptr = &SeqStatTypeTbl[0];							// �i�[���擪���ڽ�i�[
	d_ptr = &(SeqSend.data[0]);							// �i�[��擪���ڽ�i�[
	for(loop1 = 0; loop1 < 16; loop1++, *s_ptr++, *d_ptr++){
		*d_ptr = *s_ptr;								// Ӽޭ�ٌ^��������i�[
	}
	
//	data.uw_dat[0] = HW_Ver;							// HW�ް�ޮ݊i�[
	data.uw_dat[0] = hwVersion;							// HW�ް�ޮ݊i�[
	SeqSend.data[16] = data.ub_dat[1];
	SeqSend.data[17] = data.ub_dat[0];
//	data.uw_dat[0] = SW_Ver;							// SW�ް�ޮ݊i�[
	data.uw_dat[0] = swVersion;							// SW�ް�ޮ݊i�[
	SeqSend.data[18] = data.ub_dat[1];
	SeqSend.data[19] = data.ub_dat[0];
	SeqSend.data[20] = SeqSysStat;						// �ð�����i�[
	SeqSend.data[21] = 0x00;							// �\���i�[
//	data.uw_dat[0] = 22;								// �ް����޲Đ��i�[
	// 22 = (Ӽޭ�ٌ^�������� + HW�ް�ޮ� + SW�ް�ޮ� + �ð�� + �\��)
	SeqLdSendBcc(22);									// ���M�pBCC/�ް��������i�[�������s

}


/********************************************************************
*	Function	: ���M�ڰѺ����ͯ�ޕ��쐬����
*	Param		: None
*	Return		: None
*	Date		: 09/11/23	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqSendFlmSet(unsigned short CM_MD)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr,*d_ptr;

	s_ptr = &SeqSendFlmDataTbl[0];						// �i�[���擪���ڽ�i�[
	d_ptr = &(SeqSend.sSCodeFlg);						// �i�[��擪���ڽ�i�[
	for(loop1 = 0; loop1 <= 18; loop1++, s_ptr++, d_ptr++){
		*d_ptr = *s_ptr;								// ���M�ڰ�̫�ϯēǏo
	}
	data.uw_dat[0] = CM_MD;								// CMND/MODE�i�[
	SeqSend.CMND = data.ub_dat[0];
	SeqSend.MODE = data.ub_dat[1];
	SeqSend.endInfo = SeqLdEnd;							// �I�����i�[
	SeqSend.seqNumber = SeqLdNo;						// ���ݽ�ԍ��i�[
}

/********************************************************************
*	Function	: ���M�pBCC/�ް��������i�[����
*	Param		: None
*	Return		: None
*	Date		: 09/11/23	T.Akiba		Create
*	Update		: 
*	etc			: 
********************************************************************/
void SeqLdSendBcc(unsigned short dcnt)
{
	long_data_st	data;
	unsigned short	loop1;
	unsigned char	*s_ptr;

	data.uw_dat[0] = dcnt;							// �ް����޲Đ��i�[
	SeqSend.BYTEN[0] = data.ub_dat[1];
	SeqSend.BYTEN[1] = data.ub_dat[0];

	data.uw_dat[1] = dcnt + ((19 - 3) + 1);			// �ް��������i�[
													// �ް������� = ((�`��ͯ�ޕ� + �����ͯ�ޕ� + ������ް���) - �`��ͯ�ޕ� + BCC)
	SeqSend.datacnt[0] = data.ub_dat[3];
	SeqSend.datacnt[1] = data.ub_dat[2];

	SeqSendFlmCnt = dcnt + 19;

	SeqSendBcc = 0;
	s_ptr = &(SeqSend.sSCodeFlg);					// �i�[���擪���ڽ�i�[
	for(loop1 = 0; loop1 < SeqSendFlmCnt; loop1++, *s_ptr++){
		SeqSendBcc += *s_ptr;
	}
	SeqSendBcc = SeqSendBcc - CODE_STX;				// ���ĺ��ނ��폜
	SeqSendBcc = (0x00 - SeqSendBcc) & 0x00FF;		// BCC�Z�o
//	SeqSend.data[(SeqSendFlmCnt - 19)] = SeqSendBcc;	// BCC�i�[
	SeqSend.data[dcnt] = SeqSendBcc;				// BCC�i�[

	SeqSendCnt = SeqSendFlmCnt + 1;					// ���M�޲Đ��ݒ�(���M�֐��p)
}

