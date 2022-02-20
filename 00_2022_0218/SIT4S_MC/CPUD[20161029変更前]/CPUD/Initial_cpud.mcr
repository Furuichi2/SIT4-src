//////////////////////////////////////////////////////////////////////////////
//  �T���v���E�}�N���E�t�@�C���iSuperH�V���[�Y�j                    2001/12/27
//
//                                                           Computex Co.,LTD.
//////////////////////////////////////////////////////////////////////////////
//
// �EOutport(n1,n2,n3)
//   �w�肳�ꂽ�A�h���X�Ƀf�[�^���o�͂��܂��B
//   n1 �A�N�Z�X�o�X�����w�肵�܂��B 1=8bit 2=16bit 3=32bit
//   n2 �A�h���X
//   n3 �f�[�^
// �Ȃ��A��́A16�i���ƂȂ��Ă��܂��B
// �E//
//   �R�����g�ł��B// �̌�̕����񂪖����ɂȂ�܂��B
// ���̑��̃}�N���E�R�}���h�ɂ��Ă̓I�����C���E�}�j���A�����Q�Ƃ��Ă��������B
// 
// RM-01 MACRO CMND
// 2010/12/09 T.Akiba	Create
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------
// CPG Setting
//------------------------------------------------
Outport(2,FFFFFF86,A507)		// WTCSR
Outport(2,FFFFFF80,0112)		// FRQCR

//-----------------------------------------------
// BSC Setting
//------------------------------------------------
Outport(2,FFFFFF60,0008)		// BCR1
Outport(2,FFFFFF62,26E0)		// BCR2		SDRAM:32bit
Outport(2,FFFFFF64,bFF3)		// WCR1
Outport(2,FFFFFF66,B7DD)		// WCR2
Outport(1,FFFFE880,0000)		// SDMR		SDRAM:32bit
Outport(2,FFFFFF68,5224)		// MCR

Outport(2,FFFFFF72,A573)		// RTCOR
Outport(2,FFFFFF6E,A508)		// RTCSR


//;�o�e�b�֌W
//Outport(2,A4000100,5555)		// _PACR
//Outport(2,A4000120,0000)		// _PADR
//Outport(2,A4000102,AAAA)		// _PBCR
//Outport(2,A4000104,0000)		// _PCCR
//Outport(2,A4000106,2200)		// _PDDR
//Outport(2,A4000128,0010)		// _PEDR
//Outport(2,A4000108,4514)		// _PECR
//Outport(2,A400010A,AAAA)		// _PFCR
//Outport(2,A400010C,AAAA)		// _PGCR
//Outport(2,A400010E,2800)		// _PHCR
//Outport(2,A4000110,5544)		// _PJCR
//Outport(2,A4000112,5105)		// _PKCR
//Outport(2,A4000114,0000)		// _PLCR
//Outport(2,A4000118,5500)		// _PMCR
//Outport(1,A4000136,0001)		// _SCPDR
//Outport(2,A4000116,9555)		// _SCPCR






//;�h�m�s�b�֌W
Outport(2,FFFFFEE2,8760)		// _IPRA

