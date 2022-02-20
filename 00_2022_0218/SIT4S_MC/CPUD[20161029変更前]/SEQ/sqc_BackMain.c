/****************************************************************************************
*	File Name	:	ssa_BackMain.c
*	Function	:	�V�[�P���X �o�b�N�O���E���h����
*	Author		:	Designed by T.Akiba, Coded by T.Akiba
*	Date		:	2009-11-30 Akiba
*	Update		:	2010-08-31 Y.Kobayashi(�R�[�h����)
****************************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include	<machine.h>

#include	"sqc_CmnDef.h"
#include	"sqc_Config.h"
#include	"sqc_Mem.h"
#include	"sqc_LoaderIf.h"
//[[[[koma]]]#include	"from.h"


//----- Define ----------------------------------------------------------------

// ���
#define SEQ_STOP_STAT		0									// ��~���
#define SEQ_RUN_STAT		1									// �^�]���
#define SEQ_CMP_STAT		2									// �R���p�C�����
// POU�ԍ�
#define POU_NUM				3									// POU��
#define POUNO_1				0									// POU1
#define POUNO_2				1									// POU2
#define POUNO_3				2									// POU3
// ���̑�
#define SeqRasFromErr		0x42								// �����X�e�[�^�X(�������A�N�Z�X�ُ�)
#define SEQ_SIZE_MAX		65536								// �V�[�P���X�v���O�����i�[�o�C�g��


//----- Variables -------------------------------------------------------------

// ���ԃR�[�h�i�[��A�h���X
extern U4b					SEQ_COM1_TOP;						// POU1
extern U4b					SEQ_COM2_TOP;						// POU2
extern U4b 					SEQ_COM3_TOP;						// POU3


//----- Consts ----------------------------------------------------------------

extern const U4b 			SeqLd_MKIND_TBL_TOP[];				// ��������ʃe�[�u��(�A�h���X)
extern const U4b 			MKIND_TBL[];						// ��������ʃe�[�u��(��)


//----- ProtoType -------------------------------------------------------------

static void WritePouCodeToFROM(H pouNo);

extern void SEQ_RUN_MAIN2();
extern void SEQ_RUN_CHG1_MAIN();
extern void SEQ_RUN_CHG2_MAIN();
extern void SEQ_RUN_CHG3_MAIN();
extern void ClearWDT();
extern void ssc_InitSArea();
extern void ssc_SetSysTime(UW time);
extern UW ssc_GetSysTime();
extern void InitTmrCtrFlgClr();


//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: �V�[�P���X �o�b�N�O���E���h���C������
*	Param		: None
*	Return		: None
*	Date		: 09/11/30	T.Akiba		Create
*	Update		: 10/08/31	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
void SEQ_BACK_GROUND_MAIN(void)
{
	UW	loop1;
	UW	cnt;
	UW	*s_ptr1;
	UW	*d_ptr1;
	UH	*s_ptr2;
	UH	*d_ptr2;
	H	i;
	int	test;
	
	switch (SeqMainStat) {
		case SEQ_STOP_STAT:
		// ��~���
			
			if (SeqCmpFlg) {							// �R���p�C���v������H
				SeqMainStat = SEQ_CMP_STAT;				// �R���p�C���X�e�[�g�֑J��
				SeqCmpFlg = 0;
			}
			else {
				if (SeqRunFlg) {						// �^�]�v������H
					SeqMainStat = SEQ_RUN_STAT;			// �^�]��Ԃ֑J��
				}
			}
			
			SeqCpuRun = FALSE;							// CPU��� = ��~
			break;

		case SEQ_RUN_STAT:
		// �^�]���
			
			if (!SeqRunFlg) {							// �^�]�v���Ȃ��H
				SeqMainStat = SEQ_STOP_STAT;			// ��~��Ԃ֑J��
			}
			else {
				if (SEQ_CMP_START){						// �R���p�C�����
					SEQ_RUN_MAIN2();
				}
			}
			
			SeqCpuRun = TRUE;							// CPU��� = �^�]
			break;
			
		case SEQ_CMP_STAT:
		// �R���p�C�����
			
			if (SeqPOUWtEnd) {							// POU�_�E�����[�h�����H
				// FlashROM�p���[�N��������ɃR�s�[
				for (i = 0; i < POU_NUM; i++) {
					switch (i) {
						case 0:
						// POU1
							s_ptr1 = &SeqPOU1.Code1;
							d_ptr1 = &SEQ_COM1_TOP;
							break;
						case 1:
						// POU2
							s_ptr1 = &SeqPOU2.Code1;
							d_ptr1 = &SEQ_COM2_TOP;
							break;
						case 2:
						// POU3
							s_ptr1 = &SeqPOU3.Code1;
							d_ptr1 = &SEQ_COM3_TOP;
							break;
					}
					
					// �R�s�[(64KB)
					for (loop1 = 0; loop1 < sizeof(SeqPOUStat_st); loop1++, d_ptr1++, s_ptr1++) {
						*d_ptr1 = *s_ptr1;
					}
				}
				
				// �R���p�C������
				if (SeqPOU1.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG1_MAIN();				// POU1 �R���p�C�����s
					SeqPOURun1Flg = FALSE;				// POU1 �^�]�t���OOFF(0:�^�]��,1:�^�]�s��)
				}
				else {
					SeqPOURun1Flg = TRUE;				// POU1 �^�]�t���OON(0:�^�]��,1:�^�]�s��)
					SEQ_CMP_ERR1 = FALSE;
				}
				
				if (SeqPOU2.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG2_MAIN();				// POU2 �R���p�C�����s
					SeqPOURun2Flg = FALSE;				// POU2 �^�]�t���OOFF(0:�^�]��,1:�^�]�s��)
				}
				else {
					SeqPOURun2Flg = TRUE;				// POU2 �^�]�t���OON(0:�^�]��,1:�^�]�s��)
					SEQ_CMP_ERR2 = FALSE;
				}
				
				if (SeqPOU3.Size != 0) {
					SEQ_CMP_START = FALSE;
					SEQ_RUN_CHG3_MAIN();				// POU3 �R���p�C�����s
					SeqPOURun3Flg = FALSE;				// POU3 �^�]�t���OOFF(0:�^�]��,1:�^�]�s��)
				}
				else {
					SeqPOURun3Flg = TRUE;				// POU3 �^�]�t���OON(0:�^�]��,1:�^�]�s��)
					SEQ_CMP_ERR3 = FALSE;
				}
				
				// �R���p�C���ُ킠��H
				if (SEQ_CMP_ERR1 || SEQ_CMP_ERR2 || SEQ_CMP_ERR3) {
					SeqCmpErrFlg = TRUE;							// �R���p�C���G���[�t���OON(0:����,1:�ُ�)
					SeqSysStat = SeqSysStat | cBIT2;				// �X�e�[�^�X���쐬(�d�̏��ޯ�ON)
				}
				else {
					SEQ_CMP_START = TRUE;							// �R���p�C���J�n�I
					SeqCmpErrFlg = FALSE;							// �R���p�C���G���[�t���OOFF(0:����,1:�ُ�)
					SeqSysStat = SeqSysStat & ~(cBIT2 | cBIT0);		// �X�e�[�^�X���쐬(��~�r�b�gON)
					
					// �������̈�N���A
					// X�̈�AY�̈�AM�̈�
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoX];
					cnt = MKIND_TBL[MkindNoX] + MKIND_TBL[MkindNoY] + MKIND_TBL[MkindNoM];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++){
						*d_ptr2 = 0x0000;
					}
					
					// T�̈�AC�̈�
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoT];
					cnt = MKIND_TBL[MkindNoT] + MKIND_TBL[MkindNoC] + MKIND_TBL[MkindNoTd] + MKIND_TBL[MkindNoCd];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++) {
						*d_ptr2 = 0x0000;
					}
					
					// F�̈�AS�̈�AA�̈�
					d_ptr2 = (UH*)SeqLd_MKIND_TBL_TOP[MkindNoF];
					cnt = MKIND_TBL[MkindNoF] + MKIND_TBL[MkindNoS] + MKIND_TBL[MkindNoA];
					cnt = cnt / 2;
					for (loop1 = 0; loop1 < cnt; loop1++, *d_ptr2++) {
						*d_ptr2 = 0x0000;
					}
					
					InitTmrCtrFlgClr();								// �^�C�}�E�J�E���^�̃������N���A	10/08/31 Add Y.Kobayashi
					ssc_InitSArea();								// S�̈�̏�����
				}
				
				// �R���p�C������H
				if (SeqCmpErrFlg == FALSE) {
					// POU1����FROM�֏���
					for (i = 0; i < POU_NUM; i++) {
						WritePouCodeToFROM(i);
					}
					
					// ��~��Ԃ֑J��
					SeqMainStat = SEQ_STOP_STAT;
				}
				
				SeqPOUWtEnd = FALSE;								// POU�_�E�����[�h�����t���OOFF
				SeqRunFlg = 0;
				SeqCmpFlg = 0;
			}
			
			SeqCpuRun = FALSE;
			break;

		default:
		// ���̑�
			
			SeqMainStat = SEQ_STOP_STAT;
			SeqRunFlg = 0;
			SeqCmpFlg = 0;
			SeqCmpErrFlg = 0;
			SeqCpuRun = FALSE;
			break;
	}
	
	// 10/08/26 Modify Y.Kobayashi
//[[[koma]]]	if (SeqTimWtFlg) {
//[[[koma]]]		// ���v���Z�b�g
//[[[koma]]]		ssc_SetSysTime(SeqRtcData);
//[[[koma]]]		SeqTimWtFlg = FALSE;
//[[[koma]]]	}
//[[[koma]]]	else{
//[[[koma]]]		// ���v���擾
//[[[koma]]]		SeqRtcData = ssc_GetSysTime();
//[[[koma]]]	}

}

/********************************************************************
*	Function	: POU FROM��������
*	Param		: POU�ԍ�
*	Return		: None
*	Date		: 09/11/30	T.Akiba		Create
*	Update		: 10/08/11	Y.Kobayashi	Modify
*	etc			: 
********************************************************************/
static void WritePouCodeToFROM(H pouNo)
{
	UB	*pPouCode;
	int	bankNo;
	int	iRet;
	int	cnt;
	
	switch (pouNo) {
		case POUNO_1:
		// POU1
			pPouCode = (UB*)&SeqPOU1.Code1;
			bankNo = 16;
			break;
			
		case POUNO_2:
		// POU2
			pPouCode = (UB*)&SeqPOU2.Code1;
			bankNo = 17;
			break;
			
		case POUNO_3:
		// POU3
			pPouCode = (UB*)&SeqPOU3.Code1;
			bankNo = 18;
			break;
			
		default:
		// Other
			return;
	}
	
//[[[koma]]]	iRet = write_from_block(bankNo, pPouCode, SEQ_SIZE_MAX);
//[[[koma]]]	if (iRet != 0) {
//[[[koma]]]		// FROM write error !
//[[[koma]]]		SeqRasCode = SeqRasFromErr;					// �������A�N�Z�X�ُ�G���[
//[[[koma]]]		SeqRasFlg = TRUE;
//[[[koma]]]	}

}














/********************************************************************
*	Function	: �o�b�N�O�����h�^�X�N
*	Param		: Non
*	Return		: Non
*	Date		: 09/11/18	Y.Kobayashi		Create
*	Update		: 
*	etc			: 
********************************************************************/
void Tsk_BackGround()
{
//	SeqInitSerialDrv();					// �V���A���h���C�o����������
//	SEQ_BACK_GROUND_INIT();				// �V�[�P���X�C�j�V�����������s
//	
//	while (1) {							// ���������N�Œ�ɂ��Ė������[�v�ɂĎ��s
//		SeqSerialMain();				// ���[�_�R�}���hI/F����
//		SEQ_BACK_GROUND_MAIN();			// �V�[�P���X �o�b�N�O�����h���C������
//	}
//	
}

//----- Functions -------------------------------------------------------------

/********************************************************************
*	Function	: �V�X�e���̈�̏�����
*	Param		: None
*	Return		: None
*	Date		: 10/08/18	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_InitSArea()
{
//	UB	*pDst = (UB *)SeqLd_MKIND_TBL_TOP[MkindNoS];
//	
//	// �V�X�p���̓]��
//	memcpy(pDst, &sysParam[SYSP_USR0], S_SYSP_SIZE);
}

/********************************************************************
*	Function	: �V�X�e���̈�̍X�V
*	Param		: None
*	Return		: None
*	Date		: 10/08/18	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_UpdateSArea()
{
//	UH	*pDst;
//	H	size;
//	H	i;
//	
//	// �� Ethernet ----------------------------------------
//	
//	pDst = (UH *)(SeqLd_MKIND_TBL_TOP[MkindNoS] + S_ETH_ADDR);
//	
//	// �n���h�V�F�C�N����H
//	if (IsHandshakeNg() == FALSE) {
//		// DI���
//		*pDst = exDiState[0];
//		pDst++;
//		
//		// AI���
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = exAiState[i];
//		}
//		
//		// ���u�R�[�h�E���ۃR�[�h
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memcpy(pDst, exMacCode, size);
//		pDst += (size / 2);
//		
//		// ���Օi �����f�[�^�E�i�� �����f�[�^
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memcpy(pDst, exConsCode, size);
//	}
//	else {
//		// DI���
//		*pDst = 0;
//		pDst++;
//		
//		// AI���
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = 0;
//		}
//		
//		// ���u�R�[�h�E���ۃR�[�h
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memset(pDst, 0, size);
//		pDst += (size / 2);
//		
//		// ���Օi �����f�[�^�E�i�� �����f�[�^
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memset(pDst, 0, size);
//	}
//	
//	
//	// �� SIT ---------------------------------------------
//	
//	pDst = (UH *)(SeqLd_MKIND_TBL_TOP[MkindNoS] + S_SIT_ADDR);
//	
//	// SIT�o�X����H
//	if (IsSitBusNg() == FALSE) {
//		// DI���
//		*pDst = sitMem[SITMEM_DI0];
//		
//		// AI���
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = sitMem[SITMEM_AI0 + i];
//		}
//		
//		// ���u�R�[�h�E���ۃR�[�h
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memcpy(pDst, &sitMem[SITMEM_MCODE_H], size);
//		pDst += (size / 2);
//
//	}
//	else {
//		// DI���
//		*pDst = 0;
//		
//		// AI���
//		for (i = 0; i < AI_NUM; i++, pDst++) {
//			*pDst = 0;
//		}
//		
//		// ���u�R�[�h�E���ۃR�[�h
//		size = sizeof(exMacCode) + sizeof(exAlmCode);
//		memset(pDst, 0, size);
//		pDst += (size / 2);
//		
//		// ���Օi �����f�[�^�E�i�� �����f�[�^
//		size = sizeof(exConsCode) + sizeof(exPrdNoCode);
//		memset(pDst, 0, size);
//	}

}

/********************************************************************
*	Function	: �V�X�e�������̐ݒ�
*	Param		: �V�X�e������
*	Return		: None
*	Date		: 10/08/26	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
void ssc_SetSysTime(UW time)
{
}

/********************************************************************
*	Function	: �V�X�e�������̎擾
*	Param		: None
*	Return		: �V�X�e������
*	Date		: 10/08/26	Y.Kobayashi	Create
*	Update		: 
*	etc			: 
********************************************************************/
UW ssc_GetSysTime()
{
}
