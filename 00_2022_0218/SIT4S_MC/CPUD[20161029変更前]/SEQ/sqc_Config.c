/****************************************************************************************
*	File Name	:	ssc_Config.c
*	Function	:	�V�[�P���X �R���t�B�O���[�V����
*	Author		:	Designed by Y.Kobayashi, Coded by Y.Kobayashi
*	Date		:	2010-08-11 Y.Kobayashi
*	Update		:	2010-08-17 Y.Kobayashi(KOMTRAX�p�ɕύX)
****************************************************************************************/

#include "sqc_CmnDef.h"


//----- Consts ----------------------------------------------------------------

// ���W���[���^���e�[�u��
// KMT-*-J-001
const UB SeqStatTypeTbl[16] = {
	0x4b,				// �uK�v
	0x4d,				// �uM�v
	0x54,				// �uT�v
	0x2d,				// �u-�v
	0x2a,				// �u*�v
	0x2d,				// �u-�v
	0x4a,				// �uJ�v
	0x2d,				// �u-�v
	0x30,				// �u0�v
	0x30,				// �u0�v
	0x31,				// �u1�v
	0x20,				// �u�v
	0x20,				// �u�v
	0x20,				// �u�v
	0x20,				// �u�v
	0x20				// �u�v
};

#if 0
const UB SeqStatTypeTbl[16] = {
	0x49,				// ���x�m �uI�v
	0x46,				//			�uF�v
	0x2D,				//			�u-�v
	0x50,				// PLC		�uP�v
	0x4C,				//			�uL�v
	0x43,				//			�uC�v
	0x2D,				//			�u-�v
	0x41,				// 7619 	�uA�v
	0x30,				// ������	�u0�v
	0x30,				// �_���g�p �u0�v
	0x30,				//			�u0�v
	0x2D,				//			�u-�v
	0x41,				// 7619 	�uA�v
	0x30,				// ������	�u0�v
	0x30,				// �_���g�p �u0�v
	0x30				//			�u0�v
};
#endif

