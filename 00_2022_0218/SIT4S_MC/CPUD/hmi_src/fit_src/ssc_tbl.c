
#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							// DPRAM参照変数定義

#include "ssc_wk_ext.h"							//参照変数定義
#include "ssc_ver1.h"


#if ( SIT_TYPE_SEL == TYPE_SIT3 )

	extern	UNs	SV_SEQDT1_A91_INI;				//シーケンスモニタ設定１ /* V00m */
	extern	UNs	SV_INTER_VER1;					// ｲﾝﾀｰﾛｰｯｸのﾊﾞｰｼﾞｮﾝ	(121.15-141.0~15をつぶす) /* V00m */

#include "ssc_tbl_inc.c"

#else



#endif



