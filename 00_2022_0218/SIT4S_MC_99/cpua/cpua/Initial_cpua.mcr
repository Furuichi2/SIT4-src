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
///////////////////////////////////////////////////////////////////////////////

Outport(2,ffc00000,0E13)		// FRQCR

Outport(3,ff800000,00000008)		// BCR1
Outport(2,ff800004,AAE5)		// BCR2

Outport(3,ff800008,44444444)		// WCR1
Outport(3,ff80000c,BE7644DF)		// WCR2
Outport(3,ff800010,06666666)		// WCR3

Outport(3,ff800014,48122194)		// MCR
Outport(2,ff800018,0)			// PCR
Outport(1,ff94008c,0)			// SDMR2

Outport(2,ff800020,A500)		// RTCNT
Outport(2,ff800024,A510)		// RTCOR
Outport(2,ff800028,A400)		// RFCR
Outport(2,ff80001c,A508)		// RTCSR


//Outport(3,ff800014,48122194)		// MCR
//Outport(1,ff94008c,0)			// SDMR2
//Outport(2,ff80001c,A510)		// RTCSR
