
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							// DPRAM�Q�ƕϐ���`

#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "ssc_ver1.h"


#if ( SIT_TYPE_SEL == TYPE_SIT3 )

	extern	UNs	SV_SEQDT1_A91_INI;				//�V�[�P���X���j�^�ݒ�P /* V00m */
	extern	UNs	SV_INTER_VER1;					// ����۰�����ް�ޮ�	(121.15-141.0~15���Ԃ�) /* V00m */

#include "ssc_tbl_inc.c"

#else



#endif



