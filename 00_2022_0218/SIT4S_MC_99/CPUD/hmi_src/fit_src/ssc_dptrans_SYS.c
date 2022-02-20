/****************************************************************************/
/*																			*/
/*	コマツ産機㈱殿向け	ＳＩＴ－Ｓコントローラ								*/
/*																			*/
/*						ＤＰＲＡＭ ← ＦＲＡＭ	データ転送処理				*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#include	"ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include	"ssc_addr.h"
#include	"ssc_fram_ext.h"
#include	"ssc_dpram_seq_ext.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

/* 外部参照関数定義 -------------------------------------------------- */
extern	void	DPB_SEND_2B(U2b *Src);

/****************************************************************************/
/*																			*/
/*	データ転送処理		：	ＤＰＲＡＭ ← ＦＲＡＭ							*/
/*																			*/
/****************************************************************************/
void	DP_TRANS_SYS	(void)
{
	SEQ_PAR_016		= SEQ_016_SV;			/* 初期回路設定シーケンス１６	*/
	DPB_SEND_2B(&SEQ_PAR_016);
	SEQ_PAR_017		= SEQ_017_SV;			/* 初期回路設定シーケンス１７	*/
	DPB_SEND_2B(&SEQ_PAR_017);
	SEQ_PAR_018		= SEQ_018_SV;			/* 初期回路設定シーケンス１８	*/
	DPB_SEND_2B(&SEQ_PAR_018);
	SEQ_PAR_019		= SEQ_019_SV;			/* 初期回路設定シーケンス１９	*/
	DPB_SEND_2B(&SEQ_PAR_019);
	SEQ_PAR_020		= SEQ_020_SV;			/* 初期回路設定シーケンス２０	*/
	DPB_SEND_2B(&SEQ_PAR_020);
	SEQ_PAR_021		= SEQ_021_SV;			/* 初期回路設定シーケンス２１	*/
	DPB_SEND_2B(&SEQ_PAR_021);
	SEQ_PAR_022		= SEQ_022_SV;			/* 初期回路設定シーケンス２２	*/
	DPB_SEND_2B(&SEQ_PAR_022);
	SEQ_PAR_023		= SEQ_023_SV;			/* 初期回路設定シーケンス２３	*/
	DPB_SEND_2B(&SEQ_PAR_023);
	SEQ_PAR_024		= SEQ_024_SV;			/* 初期回路設定シーケンス２４	*/
	DPB_SEND_2B(&SEQ_PAR_024);
	SEQ_PAR_025		= SEQ_025_SV;			/* 初期回路設定シーケンス２５	*/
	DPB_SEND_2B(&SEQ_PAR_025);
	SEQ_PAR_026		= SEQ_026_SV;			/* 初期回路設定シーケンス２６	*/
	DPB_SEND_2B(&SEQ_PAR_026);
	SEQ_PAR_027		= SEQ_027_SV;			/* 初期回路設定シーケンス２７	*/
	DPB_SEND_2B(&SEQ_PAR_027);
	SEQ_PAR_028		= SEQ_028_SV;			/* 初期回路設定シーケンス２８	*/
	DPB_SEND_2B(&SEQ_PAR_028);
	SEQ_PAR_029		= SEQ_029_SV;			/* 初期回路設定シーケンス２９	*/
	DPB_SEND_2B(&SEQ_PAR_029);
	SEQ_PAR_030		= SEQ_030_SV;			/* 初期回路設定シーケンス３０	*/
	DPB_SEND_2B(&SEQ_PAR_030);

}
/****************************************************************************/
