//	***********************************
//	***								***
//	***		���[�N��������`		***
//	***								***
//	***********************************
#include	"cm_equ1.h"
#include	"ssc_ver1.h"

#if(CB_CPU_SEL==CB_CPUA)		//2004-03-31�ǉ�cpu-b������

#pragma section	wkIRAM	
#include	"ssc_cbrmH.inc"

#else	//����ݐؑ�

//#pragma section	wkram1	/* �����=����Bwkram1 */
#pragma section	wkiram1	//2013-08-20

#include	"ssc_cbrmH.inc"

#endif

//
#pragma section	wkram1	/* �����=����Bwkram1 */
#include	"ssc_cbrm.inc"


#pragma section	wkram1	/* �����=����Bwkram1 */

//	***************************
//	***						***
//	***	2003-07-01			***
//	***		�ُ헚��/�����	***
//	***************************
//	�����ݸނ�4�{�܂ōs����

	S4b	WPV_CB_STS_DAT_TOP[CB_STS_BUF_MAX/4+4]	;//�ُ헚����̧ 128byte
	S4b	WPV_CB_TRD_DAT_TOP[CB_TRD_SMP_CNT*4+4]	;//�������̧ 4CH��
	S4b	DUMMY_BUF[CB_TRD_SMP_CNT*4+4];
	S4b	TRD_SMP_DAT1[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT2[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT3[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT4[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT5[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT6[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT7[CB_TRD_SMP_CNT+4];
	S4b	TRD_SMP_DAT8[CB_TRD_SMP_CNT+4];


	S2b	TRD_SMP_POINT;
	S2b	TRD_EVENT_COD;
	S2b	TRD_EVENT_LATCH;//��~�C�x���g���b�`,�I��
	S2b	TRD_POINT_EVENT;//EVENT�����������߲��
	S2b	TRD_POINT_END;//�����܂Ż����ݸނ����犮��
	S2b	TRD_CLR_CMD;//01 CLR
	S2b	TRD_LATE_SV;
	S2b	TRD_LATE_PV;
	S2b	TRD_SMP_FLG;

	S2b	TRD_DP_MOV_FLG;
	S2b	TRD_DP_MOV_CNT;
	

	S2b	WPV_CB_STS_POINT			;//�ŐV�l�߲���̎w���ʒu
	S2b	WPV_CB_TRD_POINT			;//�L�����ް���
	S2b	WPV_POWER_ON_CNT			;//�d��������

	S2b	HIST_DAT_SEND_COM;//SPMILENG SOFT ==> SEND SOFT
	S2b	HIST_DAT_SEND_DIS;//1:DISENABLE 0:ENABLE
	S2b	HIST_EVENT_COD;
	S2b	HIST_KEP_SEND_COM;//�ۗ�����ށ`ؾ�Ă܂ł̊� �ُ헚���w�ߎ�t

	S2b	CB_SEQ_CB_COM345X;//2004-06-28

//	***************************
//	***		���j�^�@�\		***
//	***************************
	S2b	MONI_DISP_MOD	;//

//	***************************
//	***						***
//	***		���j�^�@�\		***
//	***		�f�[�^�g�����h	***
//	***						***
//	***************************
	S2b		CNT_GRF_I_DATA[(64/2)*500]	;//64byte*500=32000
	S2b		CNT_GRF_Y_DATA[(64/2)*500]	;//64byte*500=32000
	S2b		CNT_GRF_POINT;











	S4b	ROOT_MAIN_INP;
	S4b	ROOT_MAIN_OUT;

//	*******************************
//	***		CPUD				***
//	*******************************
	S4b	CPUDX_SEND_TOPADR;
	S4b	CPUDX_SEND_MAXCNT;
	S4b	CPUDX_SEND_NOWCNT;

	S2b	CPUDX_MEM1_SNDEVN;		//EVNT BIT0:KIND
	S2b	CPUDX_MEM1_SNDKND;		//KIND
	S2b	CPUDX_MEM1_SNDFLG;		//
	

//	*******************************
//	***		CPUD				***
//	*******************************
//	2017-06-16
	S2b	MAIN_SCAN_CNT;	//

//	*******************************
//	***		CPUD				***
//	*******************************
	S2b	OLD_SVP_MONALM_S04;		//
