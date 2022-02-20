/************************************************************************************/
/*																					*/
/*																					*/
/*		�R�}�c�Y�@���a�����@�r�h�s�|�r�@�����g�`�\���v���O����						*/
/*																					*/
/*		�issc_graph.c����include���Ă���j											*/
/*																					*/
/************************************************************************************/

#define		pvGRAPH_XSIZE		  500				/* ���̕`��X������(dot)	*/
#define		pvGRAPH_YSIZE		  288				/* ���̕`��Y������(dot)	*/
#define		pvGRAPH_XOPOS		  1*16				/* ���̕`��X�����_(X0��)��Έʒu(dot)	*/
#define		pvGRAPH_YOPOS		  (12*32)-1				/* ���̕`��Y�����_(Y0��)��Έʒu(dot)	*/


/* �O���Q�Ɗ֐���` -------------------------------------------------- */

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		Key_Data_No[4];

/* �萔��` ---------------------------------------------------------- */

/* �f�[�^�^��` ------------------------------------------------------ */

/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	Dsp_Pvgraph_Screen(void);
void	Dsp_Pv_Wave(UNs poi_old, UNs ydot, UNs ybak, UNs col);
void	Dsp_PvSamp_Csr(void);
void	Dsp_PvTrnd_Csr(void);
void	Dsp_EPM_Csr(void);				//V06
void	EPM_TOTAL_DISP(void);			//V06a
//V06b	void	GRAPH_DT_MAKE(UNl MON_BUF[][2], UNs MON_POI);//V06a
void	GRAPH_DT_MAKE(UNl ADD_BUF[][2], UNs ADD_POI, UNl MON_BUF[][2], UNs MON_POI);//V06b

/* �����ϐ���` ------------------------------------------------------ */

/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Dsp_Pvgraph_INIT
*  Function Name:	�g�`�\����ʑJ�ڎ��̏�������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pvgraph_INIT(void)
{
	WAVE_SAMP_DTP[1] = 0;					//���������ݸޔg�`�`��ʒu�߲���O��l����ؾ��
	WAVE_TRND_DTP[1] = 0;					//��������ޔg�`�`��ʒu�߲���O��l����ؾ��

	if (CSR_PVSAMP[0] == 0) {				//���وʒu0�͂��蓾�Ȃ��B�i�d���������ď��߂Ă̏ꍇ�����j
		CSR_PVSAMP[0] = 1;					//���وʒu��ؾ��
	}
	if (CSR_PVTRND[0] == 0) {				//���وʒu0�͂��蓾�Ȃ��B�i�d���������ď��߂Ă̏ꍇ�����j
		CSR_PVTRND[0] = 1;					//���وʒu��ؾ��
	}
	CSR_PVSAMP[1]=0;						//���وʒu�O��l�����������i��ʐؑւ莞�ɕ\������������j
	CSR_PVTRND[1]=0;						//���وʒu�O��l�����������i��ʐؑւ莞�ɕ\������������j

	Dsp_Pvgraph_Screen();
}


/*
********************************************************************************
*  Module Name:		Dsp_Pvgraph_Screen
*  Function Name:	�g�`�\�����̔w�i�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pvgraph_Screen(void)
{
	UNs		i;
	UNs		xcnt, ycnt;
	UNs		xdot, ydot;
	UNs		col;

	xdot = pvGRAPH_XOPOS;						//X�����_�ʒu
	for(xcnt=0; xcnt<pvGRAPH_XSIZE; xcnt++)		//XSIZE=500dot
	{
		ydot = pvGRAPH_YOPOS;					//Y�����_�ʒu
		for(ycnt=0; ycnt<pvGRAPH_YSIZE; ycnt++)	//XSIZE=288dot
		{
			if ( (xcnt == (pvGRAPH_XSIZE/5)*1-1) ||	//�cײ�(100�ޯĖ�)�F��
				 (xcnt == (pvGRAPH_XSIZE/5)*2-1) ||	//�cײ�(200�ޯĖ�)�F��
				 (xcnt == (pvGRAPH_XSIZE/5)*3-1) ||	//�cײ�(300�ޯĖ�)�F��
				 (xcnt == (pvGRAPH_XSIZE/5)*4-1) ||	//�cײ�(400�ޯĖ�)�F��
				 (ycnt == (pvGRAPH_YSIZE/2)*1-1) ) 	//��ײ�(144�ޯĖ�)�F��
			{
				col = 7;							//ײ݁F��
			}
			else
			{
				col = 0;								//�w�i�F�F��
			}
			LCD_VRAM[ydot][xdot] = col;
			ydot--;
		}
		xdot++;
	}

}


/*
********************************************************************************
*  Module Name:		Dsp_PvSamp_Wave
*  Function Name:	���������ݸޔg�`�`��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvSamp_Wave(void)
{
	UNs		poi_new, poi_old;
	UNs		dtw, dlmw, ulmw, lenw;
	UNl		dtl, dlml, ulml, lenl;
	UNs		pvdot, xdot, ydot;
	UNs		ydiff, ybak;
	UNs		i, j;
	long	s_dtl, s_ulml, s_dlml, s_lenl;


//2014/03/14
////	if(SV_WAVE_SCL5D != 0) {			//�����ݸމ��  �d�͍ŏ��l�ݒ蕄��		//V06a
////		PV0_EPMDAT_SIN |= BIT_0;
////	} else {
////		PV0_EPMDAT_SIN &= ~BIT_0;
////	}
////	if(PV0_SMPCSR_EP_SIN < 0) {			//�����ݸމ��  ���وʒu�̓d�͒l����	//V06a
////		PV0_EPMDAT_SIN |= BIT_1;
////	} else {
////		PV0_EPMDAT_SIN &= ~BIT_1;
////	}


	Dsp_PvSamp_Csr();						//���ٕ\��

	poi_new = WAVE_SAMP_DTP[0];
	poi_old = WAVE_SAMP_DTP[1];

	if (poi_new == poi_old)		return;

	if (poi_new < poi_old) 					//�߲���߂����H
	{
		Dsp_Pvgraph_Screen();
		poi_old = 0;
	}

	if (poi_new == 0)
	{
		WAVE_SAMP_DTP[1] = poi_new;
		return;
	}

	for ( ; poi_old < poi_new; poi_old++)			//�ŐV���߲���ʒu�܂ŕ`�悷��
	{
		/**************** �p�x�̔g�`�`�� ******************/
		ulmw = 3599;								//���̂̏���p�x
		dlmw = 0;									//���̂̉����p�x
		dtw = WAVE_SAMP_DATA[poi_old+1].angle;		//����
		if (dtw > ulmw){		//����Я�
			dtw = ulmw;
		}
		if (dtw < dlmw){		//�����Я�
			dtw = dlmw;
		}
		lenw = ulmw - dlmw;							//
		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].angle = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].angle;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_ORANGE);

		/**************** �Ʊ1�̔g�`�`�� ******************/
//		ulml = SV_RNAPOS_MAXP;						//���̂̏�����@�B���
//		dlml = SV_RNAPOS_MINP;						//���̂̉������@�B����
		ulml = SV_WAVE_SCL1U;						//���̂̏�����@�B���
		dlml = SV_WAVE_SCL1D;						//���̂̉������@�B����
		dtl = WAVE_SAMP_DATA[poi_old+1].renia1;		//����
		dtl = cnv_mm_inch(dtl, 0);					//mm��inch
		if (dtl > ulml){		//����Я�
			dtl = ulml;
		}
		if (dtl < dlml){		//�����Я�
			dtl = dlml;
		}
		lenl = ulml - dlml;							//
		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].renia1 = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].renia1;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_BLUE);

//H2W		/**************** �Ʊ2�̔g�`�`�� ******************/
//////		ulml = SV_RNAPOS_MAXP;						//���̂̏�����@�B���
//////		dlml = SV_RNAPOS_MINP;						//���̂̉������@�B����
////		ulml = SV_WAVE_SCL1U;						//���̂̏�����@�B���
////		dlml = SV_WAVE_SCL1D;						//���̂̉������@�B����
////		dtl = WAVE_SAMP_DATA[poi_old+1].renia2;		//����
////		dtl = cnv_mm_inch(dtl, 0);					//mm��inch
////		if (dtl > ulml){		//����Я�
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//�����Я�
////			dtl = dlml;
////		}
////		lenl = ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].renia2 = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_SAMP_DOT[poi_old].renia2;		//ydot�O��ʒu
////
////		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_BLUE);

		/**************** �׏d���v�̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL2D;						//���̂̉���
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuT;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuT = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuT;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL2D;						//���̂̉���
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuT;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuT = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].kajyuT;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_GREEN);

		/**************** �׏d���̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL2D;						//���̂̉���
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuL;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuL = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuL;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL2D;						//���̂̉���
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuL;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuL = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].kajyuL;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_YELLOW);

		/**************** �׏d�E�̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL2D;						//���̂̉���
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuR;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuR = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuR;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL2U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL2D;						//���̂̉���
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuR;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuR = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].kajyuR;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_PINK);

		/**************** �u���d�͂̔g�`�`�� ******************/	//V06
		if (SEQ_PAR_103 & BIT_12)
		{
//V06a			ulml = SV_WAVE_SCL5U;						//���̂̏�����@�B���
//////			dlml = SV_WAVE_SCL5D;						//���̂̉������@�B����
//////			dtl = WAVE_SAMP_DATA[poi_old+1].elepw;		//����
//////			if (dtl > ulml){		//����Я�
//////				dtl = ulml;
//////			}
//////			if (dtl < dlml){		//�����Я�
//////				dtl = dlml;
//////			}
//////			lenl = ulml - dlml;							//
//////			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
//////			ydot = pvGRAPH_YOPOS - pvdot;
//////			WAVE_SAMP_DOT[poi_old+1].elepw = ydot;		//ydot�ʒu�ۑ�
//////			ybak = WAVE_SAMP_DOT[poi_old].elepw;		//ydot�O��ʒu

			s_ulml = (long)SV_WAVE_SCL5U;						//���̂̏�����@�B���
//2014/03/14			s_dlml = (int)SV_WAVE_SCL5D * -1;					//���̂̉������@�B����
			s_dlml = (long)SV_WAVE_SCL5D;					//���̂̉������@�B����
			s_dtl = (long)WAVE_SAMP_DATA[poi_old+1].elepw;		//����
			if (s_dtl > s_ulml){		//����Я�
				s_dtl = s_ulml;
			}
			if (s_dtl < s_dlml){		//�����Я�
				s_dtl = s_dlml;
			}
			s_lenl = s_ulml - s_dlml;							//
//V06b			pvdot = ((UNs)(s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / (UNs)s_lenl;	//pv * ysize(max287dot) / ysize(max)
			pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_SAMP_DOT[poi_old+1].elepw = ydot;		//ydot�ʒu�ۑ�
			ybak = WAVE_SAMP_DOT[poi_old].elepw;		//ydot�O��ʒu
    
			Dsp_Pv_Wave(poi_old, ydot, ybak, COL_RED);
		}

		/**************** ���ݽbit0�̔g�`�`�� ******************/
		dtw = 16;
		if (WAVE_SAMP_DATA[poi_old+1].seq & BIT_0)	//����
		{
			dtw = dtw+16;
		}
		lenw = 287;							//
		pvdot = (dtw * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].seq1 = ydot;			//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].seq1;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_LBULE);

		/**************** ���ݽbit1�̔g�`�`�� ******************/
		dtw = 16+32;
		if (WAVE_SAMP_DATA[poi_old+1].seq & BIT_1)	//����
		{
			dtw = dtw+16;
		}
		lenw = 287;							//
		pvdot = (dtw * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].seq2 = ydot;			//ydot�ʒu�ۑ�
		ybak = WAVE_SAMP_DOT[poi_old].seq2;		//ydot�O��ʒu

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_LBULE);

	}

	WAVE_SAMP_DTP[1] = poi_new;
}


/*
********************************************************************************
*  Module Name:		Dsp_PvTrnd_Wave
*  Function Name:	��������ޔg�`�`��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvTrnd_Wave(UNs page)
{
	UNs		poi_new, poi_old;
	UNs		dpoi_n, dpoi_o, area_n, area_o;
	UNs		dtw, dlmw, ulmw, lenw;
	UNl		dtl, dlml, ulml, lenl;
	UNs		pvdot, xdot, ydot;
	UNs		ydiff, ybak;
	UNs		i, j;
	long	s_dtl, s_ulml, s_dlml, s_lenl;

	Dsp_PvTrnd_Csr();						//���ٕ\��

	poi_new = WAVE_TRND_DTP[0];				//�����߲���ʒu
	poi_old = WAVE_TRND_DTP[1];				//�O���߲���ʒu

	if (poi_new == 0)
	{
		WAVE_TRND_DTP[1] = poi_new;
		return;
	}

	if (poi_new == poi_old)		return;		//�߲���ʒu�ω����������H

	if ( SV_WAVE_PAGE == 0 )				//�\���߰��0�H
	{
		area_o = (poi_old-1)/500;				//�O���߲���ʒu�̕\���G���A
		area_n = (poi_new-1)/500;				//�����߲���ʒu�̕\���G���A

		if (area_o == area_n)					//�\���G���A�ς�����H
		{
			dpoi_o = poi_old % 500;				//�O��̕\���߲���ʒu		exp:502=2
			dpoi_n = poi_new % 500;				//���݂̕\���߲���ʒu		exp:999=499 / 1000=500
			if (dpoi_n==0)
			{
				dpoi_n = 500;
			}
		}
		else
		{	//�\���G���A�ύX
			Dsp_Pvgraph_Screen();
			dpoi_o = 0;
			dpoi_n = poi_new % 500;				//���݂̕\���߲���ʒu		exp:999=499 / 1000=500
			if (dpoi_n==0)
			{
				dpoi_n = 500;
			}
			poi_old = area_n*500;				//�߰�ނ̐擪�߲������ؾ��
		}
	}
	else
	{
		if(poi_old != 0)	return;
		Dsp_Pvgraph_Screen();					//V05o_a
		dpoi_o = 0;
		dpoi_n = 500;
		area_n = (poi_new-1)/500;				//�����߲���ʒu�̕\���G���A
		if (area_n >= SV_WAVE_PAGE)
		{
			poi_old = (area_n-SV_WAVE_PAGE)*500;	
		}
		else
		{
			poi_old = (10-(SV_WAVE_PAGE-area_n))*500;	
		}
	}

	for ( ; dpoi_o < dpoi_n; dpoi_o++, poi_old++)			//�ŐV���߲���ʒu�܂ŕ`�悷��
	{
		/**************** �Ʊ1�̔g�`�`�� ******************/
//		ulml = SV_RNAPOS_MAXP;						//���̂̏�����@�B���
//		dlml = SV_RNAPOS_MINP;						//���̂̉������@�B����
		ulml = SV_WAVE_SCL3U;						//���̂̏�����@�B���
		dlml = SV_WAVE_SCL3D;						//���̂̉������@�B����
		dtl = WAVE_TRND_DATA[poi_old+1].renia1;		//����
		dtl = cnv_mm_inch(dtl, 0);					//mm��inch
		if (dtl > ulml){		//����Я�
			dtl = ulml;
		}
		if (dtl < dlml){		//�����Я�
			dtl = dlml;
		}
		lenl = ulml - dlml;							//
		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].renia1 = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_TRND_DOT[poi_old].renia1;		//ydot�O��ʒu

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_BLUE);

//H2W		/**************** �Ʊ2�̔g�`�`�� ******************/
//////		ulml = SV_RNAPOS_MAXP;						//���̂̏�����@�B���
//////		dlml = SV_RNAPOS_MINP;						//���̂̉������@�B����
////		ulml = SV_WAVE_SCL3U;						//���̂̏�����@�B���
////		dlml = SV_WAVE_SCL3D;						//���̂̉������@�B����
////		dtl = WAVE_TRND_DATA[poi_old+1].renia2;		//����
////		dtl = cnv_mm_inch(dtl, 0);					//mm��inch
////		if (dtl > ulml){		//����Я�
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//�����Я�
////			dtl = dlml;
////		}
////		lenl = ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].renia2 = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_TRND_DOT[poi_old].renia2;		//ydot�O��ʒu
////
////		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_BLUE);

		/**************** �׏d���v�̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL4D;						//���̂̉���
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuT;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuT = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_TRND_DOT[poi_old].kajyuT;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL4D;						//���̂̉���
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuT;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuT = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_TRND_DOT[poi_old].kajyuT;		//ydot�O��ʒu

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_GREEN);

		/**************** �׏d���̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL4D;						//���̂̉���
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuL;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuL = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_TRND_DOT[poi_old].kajyuL;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL4D;						//���̂̉���
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuL;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuL = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_TRND_DOT[poi_old].kajyuL;		//ydot�O��ʒu

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_YELLOW);

		/**************** �׏d�E�̔g�`�`�� ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
////		dlmw = SV_WAVE_SCL4D;						//���̂̉���
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuR;		//����
////		if (dtw > ulmw){		//����Я�
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//�����Я�
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max�׏d)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuR = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_TRND_DOT[poi_old].kajyuR;		//ydot�O��ʒu

		s_ulml = (short)SV_WAVE_SCL4U;						//���̂̏�����ő�׏d���v
		s_dlml = (short)SV_WAVE_SCL4D;						//���̂̉���
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuR;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuR = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_TRND_DOT[poi_old].kajyuR;		//ydot�O��ʒu

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_PINK);

		/**************** 1���ٓd�͗ʂ̔g�`�`�� ******************/	//V06
//2014/03/14
////		ulml = SV_WAVE_SCL6U;						//���̂̏�����d�͍ő�
////		dlml = SV_WAVE_SCL6D;						//���̂̉���
////		dtl = WAVE_TRND_DATA[poi_old+1].elepw;		//����
////		if (dtl > ulml){		//����Я�
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//�����Я�
////			dtl = dlml;
////		}
////
////		if ((SEQ_PAR_103 & BIT_12) == 0)	dtl = 0;	//�d�͗ʂȂ��Ȃ�d�͗�=0
////
////		lenl= ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max�d��)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].elepw = ydot;		//ydot�ʒu�ۑ�
////		ybak = WAVE_TRND_DOT[poi_old].elepw;		//ydot�O��ʒu

		s_ulml = (long)SV_WAVE_SCL6U;						//���̂̏�����@�B���
		s_dlml = (long)SV_WAVE_SCL6D;					//���̂̉������@�B����
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].elepw;		//����
		if (s_dtl > s_ulml){		//����Я�
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//�����Я�
			s_dtl = s_dlml;
		}

		if ((SEQ_PAR_103 & BIT_12) == 0)	s_dtl = 0;	//�d�͗ʂȂ��Ȃ�d�͗�=0

		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].elepw = ydot;		//ydot�ʒu�ۑ�
		ybak = WAVE_TRND_DOT[poi_old].elepw;		//ydot�O��ʒu
    
		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_ORANGE);

		/**************** ������o�ʒu�̔g�`�`�� ******************/
		if ( (SEQ_PAR_113 & cBIT5) == 0 ) {				//V06p �����ǉ�
			ulml = SV_WAVE_SCL3U;						//���̂̏�����@�B���
			dlml = SV_WAVE_SCL3D;						//���̂̉������@�B����
			dtl = SV_TRDCSR_RNAU;						//����
			if (dtl > ulml){		//����Я�
				dtl = ulml;
			}
			if (dtl < dlml){		//�����Я�
				dtl = dlml;
			}
			lenl = ulml - dlml;							//
			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_TRND_DOT[poi_old+1].rnaupl = ydot;		//ydot�ʒu�ۑ�
			ybak = WAVE_TRND_DOT[poi_old].rnaupl;		//ydot�O��ʒu

			Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_RED);
		}

		/**************** �������o�ʒu�̔g�`�`�� ******************/
		if ( (SEQ_PAR_113 & cBIT5) == 0 ) {				//V06p �����ǉ�
			ulml = SV_WAVE_SCL3U;						//���̂̏�����@�B���
			dlml = SV_WAVE_SCL3D;						//���̂̉������@�B����
			dtl = SV_TRDCSR_RNAD;						//����
			if (dtl > ulml){		//����Я�
				dtl = ulml;
			}
			if (dtl < dlml){		//�����Я�
				dtl = dlml;
			}
			lenl = ulml - dlml;							//
			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_TRND_DOT[poi_old+1].rnadnl = ydot;		//ydot�ʒu�ۑ�
			ybak = WAVE_TRND_DOT[poi_old].rnadnl;		//ydot�O��ʒu

			Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_RED);
		}
	}

	WAVE_TRND_DTP[1] = poi_new;
}


/*
********************************************************************************
*  Module Name:		Dsp_Pv_Wave
*  Function Name:	�����g�`�΂ߐ�(�������)�`��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pv_Wave(UNs poi_old, UNs ydot, UNs ybak, UNs col)
{
	UNs		ydiff, xdot;
	UNs		i;

	if (poi_old == 0)							//�g�`�`���n��
	{
		xdot = pvGRAPH_XOPOS + poi_old;
		LCD_VRAM[ydot][xdot] = col;					//�g�`
	}

	else if (ybak >= ydot)
	{
		/* �΂ߏ�� */
		ydiff = ybak - ydot;
//		if (ydiff < 2)							//�O��Ƃ�dot����2�ޯĖ����H  �����Ȃ璼����Ԃ͕s�v
//		{
//			xdot = pvGRAPH_XOPOS + poi_old;
//			LCD_VRAM[ydot][xdot] = col;					//�g�`
//		}
//		else
//		{
			//�΂ߏ�ɒ������
			ydiff = ydiff / 2;
			xdot = pvGRAPH_XOPOS + poi_old;
			for (i=0; i<ydiff; i++)
			{
				LCD_VRAM[ybak-1][xdot-1] = col;			//�g�`
				ybak--;
			}
			for ( ; ybak>=ydot; ybak--)
			{
				LCD_VRAM[ybak][xdot] = col;				//�g�`
			}
//		}
	}
	else
	{
		/* �΂߉��� */
		ydiff = ydot - ybak;
//		if (ydiff < 2)							//�O��Ƃ�dot����2�ޯĖ����H  �����Ȃ璼����Ԃ͕s�v
//		{
//			xdot = pvGRAPH_XOPOS + poi_old;
//			LCD_VRAM[ydot][xdot] = col;					//�g�`
//		}
//		else
//		{
			//�΂߉��ɒ������
			ydiff = ydiff / 2;
			xdot = pvGRAPH_XOPOS + poi_old;
			for (i=0; i<ydiff; i++)
			{
				LCD_VRAM[ybak+1][xdot-1] = col;			//�g�`
				ybak++;
			}
			for ( ; ybak<=ydot; ybak++)
			{
				LCD_VRAM[ybak][xdot] = col;				//�g�`
			}
//		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_PvSamp_Csr
*  Function Name:	���������ݸޔg�`��ʂ̶��ٕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvSamp_Csr(void)
{
	UNs		csr_n, csr_o, xdot;
	UNs		csr_mark;
	UNs		i;
	short	dat;
	long	datL;

	csr_n = CSR_PVSAMP[0];
	csr_o = CSR_PVSAMP[1];


	if ( csr_n <= WAVE_SAMP_DTP[0])		//���وʒu���ް��͂��邩�H
	{
//2014/03/14
////		PV0_SMPCSR_KJT  = WAVE_SAMP_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
////		PV0_SMPCSR_KJL  = WAVE_SAMP_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
////		PV0_SMPCSR_KJR  = WAVE_SAMP_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_2;
			PV0_SMPCSR_KJT  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_2;
			PV0_SMPCSR_KJT  = dat * -1;
		}

		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_3;
			PV0_SMPCSR_KJL  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_3;
			PV0_SMPCSR_KJL  = dat * -1;
		}

		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_4;
			PV0_SMPCSR_KJR  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_4;
			PV0_SMPCSR_KJR  = dat * -1;
		}

		PV0_SMPCSR_AGL  = WAVE_SAMP_DATA[csr_n].angle;			//���وʒu�̊p�x
		PV0_SMPCSR_RNA1 = WAVE_SAMP_DATA[csr_n].renia1;		//���وʒu�̽ײ�ވʒu
		PV0_SMPCSR_RNA2 = WAVE_SAMP_DATA[csr_n].renia2;		//���وʒu�̽ײ�ވʒu

		if (WAVE_SAMP_DATA[csr_n].seq & BIT_0) {
			PV0_SMPCSR_SEQ0 = 1;		//���وʒu�̼��ݽ
		}else{
			PV0_SMPCSR_SEQ0 = 0;		//���وʒu�̼��ݽ
		}
		if (WAVE_SAMP_DATA[csr_n].seq & BIT_1) {
			PV0_SMPCSR_SEQ1 = 1;		//���وʒu�̼��ݽ
		}else{
			PV0_SMPCSR_SEQ1 = 0;		//���وʒu�̼��ݽ
		}
//V06a		PV0_SMPCSR_EP = WAVE_SAMP_DATA[csr_n].elepw;		//���وʒu�̏u���d��	V06
//2014/03/14
////		PV0_SMPCSR_EP_SIN = (int)WAVE_SAMP_DATA[csr_n].elepw;		//���وʒu�̏u���d��
////		if(PV0_SMPCSR_EP_SIN < 0)
////		{
////			PV0_SMPCSR_EP = (UNs)(PV0_SMPCSR_EP_SIN * -1);				//���وʒu�̏u���d��
////		}
////		else
////		{
////			PV0_SMPCSR_EP = WAVE_SAMP_DATA[csr_n].elepw;		//���وʒu�̏u���d��
////		}

		datL = (long)WAVE_SAMP_DATA[csr_n].elepw;		//���وʒu�̏u���d��
		if (datL >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_1;
			PV0_SMPCSR_EP  = datL;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_1;
			PV0_SMPCSR_EP  = datL * -1;
		}
	}
	else
	{
		PV0_SMPCSR_KJT  = 0;		//���وʒu�̍��v�׏d
		PV0_SMPCSR_KJL  = 0;		//���وʒu�̍��׏d
		PV0_SMPCSR_KJR  = 0;		//���وʒu�̉E�׏d
		PV0_SMPCSR_AGL  = 0;		//���وʒu�̊p�x
		PV0_SMPCSR_RNA1 = 0;		//���وʒu�̽ײ�ވʒu
		PV0_SMPCSR_RNA2 = 0;		//���وʒu�̽ײ�ވʒu
		PV0_SMPCSR_SEQ0 = 0;		//���وʒu�̼��ݽ
		PV0_SMPCSR_SEQ1 = 0;		//���وʒu�̼��ݽ
		PV0_SMPCSR_EP   = 0;		//���وʒu�̏u���d��	V06

		PV0_EPMDAT_SIN &= ~(BIT_1+BIT_2+BIT_3+BIT_4);		//2014/03/14
	}
//2014/09/09
////	PV0_SMPCSR_TIM  = SV_SMPCYC_TIM * csr_n;				//���وʒu�̎���
	PV0_SMPCSR_TIM  = SV_SMPCYC_TIM2 * csr_n;				//���وʒu�̎���
	PV0_SMPCSR_POS  = csr_n;								//���وʒu���߲��


	if (csr_n == csr_o)			return;

	CSR_PVSAMP[1] = csr_n;					//�V���وʒu�ۑ�

	/* �O�̈ʒu���߰��ŏ��� */
	xdot = csr_o + 7;
	csr_mark = 0x8140;//��߰�	S-JIS����
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		xdot,					/*t_p->X_POS,*/
		80,						/*t_p->Y_POS,*/
		COL_RED,				/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&csr_mark, 
		LCD_VRAM
		);
	
	/* ���̈ʒu��\�� */
	xdot = csr_n + 7;
	csr_mark = 0x81A5;//��		S-JIS����
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		xdot,					/*t_p->X_POS,*/
		80,						/*t_p->Y_POS,*/
		COL_RED,				/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&csr_mark, 
		LCD_VRAM
		);

}


/*
********************************************************************************
*  Module Name:		Dsp_PvTrnd_Csr
*  Function Name:	���������ݸޔg�`��ʂ̶��ٕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvTrnd_Csr(void)
{
	UNs		csr_n, csr_o, xdot;
	UNs		csr_mark;
	UNs		i;
	short	dat;
	long	datL;

	/***** �J�[�\���ʒu�̎����l�쐬 *****/
	csr_n = WAVE_TRND_DTP[0];							//�����߲���ʒu
	csr_n = (csr_n-1)/500;								//�O���߲���ʒu�̕\���G���A
	if (csr_n >= SV_WAVE_PAGE)
	{
		csr_n = CSR_PVTRND[0]+((csr_n-SV_WAVE_PAGE)*500);	
	}
	else
	{
		csr_n = CSR_PVTRND[0]+((10-(SV_WAVE_PAGE-csr_n))*500);	
	}

	if (SV_WAVE_PAGE == 0) {
		if ( CSR_PVTRND[0] <= (WAVE_TRND_DTP[0]%500) )		//���وʒu���ް��͂��邩�H
		{
//2014/03/14
////			PV0_TRDCSR_KJT  = WAVE_TRND_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
////			PV0_TRDCSR_KJL  = WAVE_TRND_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
////			PV0_TRDCSR_KJR  = WAVE_TRND_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
			dat = (short)WAVE_TRND_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_5;
				PV0_TRDCSR_KJT  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_5;
				PV0_TRDCSR_KJT  = dat * -1;
			}

			dat = (short)WAVE_TRND_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_6;
				PV0_TRDCSR_KJL  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_6;
				PV0_TRDCSR_KJL  = dat * -1;
			}

			dat = (short)WAVE_TRND_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_7;
				PV0_TRDCSR_KJR  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_7;
				PV0_TRDCSR_KJR  = dat * -1;
			}

			PV0_TRDCSR_RNA1 = WAVE_TRND_DATA[csr_n].renia1;		//���وʒu�̽ײ�ވʒu
			PV0_TRDCSR_RNA2 = WAVE_TRND_DATA[csr_n].renia2;		//���وʒu�̽ײ�ވʒu

//2014/03/14
////			PV0_TRDCSR_EP   = WAVE_TRND_DATA[csr_n].elepw;		//���وʒu��1���ٓd�͗�		V06
			datL = (short)WAVE_TRND_DATA[csr_n].elepw;		//���وʒu�̏u���d��
			if (datL >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_8;
				PV0_TRDCSR_EP  = datL;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_8;
				PV0_TRDCSR_EP  = datL * -1;
			}
		}
		else
		{
			PV0_TRDCSR_KJT  = 0;		//���وʒu�̍��v�׏d
			PV0_TRDCSR_KJL  = 0;		//���وʒu�̍��׏d
			PV0_TRDCSR_KJR  = 0;		//���وʒu�̉E�׏d
			PV0_TRDCSR_RNA1 = 0;		//���وʒu�̽ײ�ވʒu
			PV0_TRDCSR_RNA2 = 0;		//���وʒu�̽ײ�ވʒu
			PV0_TRDCSR_EP   = 0;		//���وʒu��1���ٓd�͗�		V06

			PV0_EPMDAT_SIN &= ~(BIT_5+BIT_6+BIT_7+BIT_8);
		}
	}
	else
	{
//2014/03/14
////		PV0_TRDCSR_KJT  = WAVE_TRND_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
////		PV0_TRDCSR_KJL  = WAVE_TRND_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
////		PV0_TRDCSR_KJR  = WAVE_TRND_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
		dat = (short)WAVE_TRND_DATA[csr_n].kajyuT;		//���وʒu�̍��v�׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_5;
			PV0_TRDCSR_KJT  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_5;
			PV0_TRDCSR_KJT  = dat * -1;
		}

		dat = (short)WAVE_TRND_DATA[csr_n].kajyuL;		//���وʒu�̍��׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_6;
			PV0_TRDCSR_KJL  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_6;
			PV0_TRDCSR_KJL  = dat * -1;
		}

		dat = (short)WAVE_TRND_DATA[csr_n].kajyuR;		//���وʒu�̉E�׏d
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_7;
			PV0_TRDCSR_KJR  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_7;
			PV0_TRDCSR_KJR  = dat * -1;
		}

		PV0_TRDCSR_RNA1 = WAVE_TRND_DATA[csr_n].renia1;		//���وʒu�̽ײ�ވʒu
		PV0_TRDCSR_RNA2 = WAVE_TRND_DATA[csr_n].renia2;		//���وʒu�̽ײ�ވʒu

//2014/03/14
////		PV0_TRDCSR_EP   = WAVE_TRND_DATA[csr_n].elepw;		//���وʒu��1���ٓd�͗�		V06
		datL = (short)WAVE_TRND_DATA[csr_n].elepw;		//���وʒu��1���ٓd�͗�
		if (datL >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_8;
			PV0_TRDCSR_EP  = datL;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_8;
			PV0_TRDCSR_EP  = datL * -1;
		}

	}
//	PV0_TRDCSR_TIM  = SV_TRDCYC_TIM * csr_n;				//���وʒu�̎���
//	PV0_TRDCSR_POS  = csr_n;								//���وʒu���߲��
	PV0_TRDCSR_POS  = CSR_PVTRND[0];						//window���̶��وʒu
	PV0_TRDCSR_POSL = 0;									//�������H
	PV0_TRDCSR_POSR = 0;									//�������H

	if( 0 == (SEQ_016_SV & BIT_6) ) {				//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		if( 0 == (SEQ_016_SV & BIT_7) ) {			//�P�� �����x(1:�����x)
			PV0_TRDCSR_RNAU = SV_TRDCSR_RNAU/10;
			PV0_TRDCSR_RNAD = SV_TRDCSR_RNAD/10;
		}
	}
	else{
			PV0_TRDCSR_RNAU = SV_TRDCSR_RNAU;
			PV0_TRDCSR_RNAD = SV_TRDCSR_RNAD;
	}


	/***** �J�[�\���ʒu�́��}�[�N�\�� *****/
	csr_n = CSR_PVTRND[0];
	csr_o = CSR_PVTRND[1];

	if (csr_n == csr_o)			return;

	CSR_PVTRND[1] = csr_n;					//�V���وʒu�ۑ�

	/* �O�̈ʒu���߰��ŏ��� */
	xdot = csr_o + 7;
	csr_mark = 0x8140;//��߰�	S-JIS����
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		xdot,					/*t_p->X_POS,*/
		80,						/*t_p->Y_POS,*/
		COL_RED,				/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&csr_mark, 
		LCD_VRAM
		);
	
	/* ���̈ʒu��\�� */
	xdot = csr_n + 7;
	csr_mark = 0x81A5;//��		S-JIS����
	disp_moji_s_color (
		2,						/*t_p->M_LEN,*/
		xdot,					/*t_p->X_POS,*/
		80,						/*t_p->Y_POS,*/
		COL_RED,				/*t_p->C_COL,*/
		GAMENn_SCR_COL,			/*t_p->B_COL1,*/
		0x0101,					/*t_p->SIZE,*/
		&csr_mark, 
		LCD_VRAM
		);

}


/*
********************************************************************************
*  Module Name:		Dsp_EPM_INIT
*  Function Name:	�d�̓��j�^��ʃO���t�\���̏�������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2010/09			V06
********************************************************************************
*/
#define		EPM_GRAPH_ORGX			64
#define		EPM_GRAPH_ORGY			112			//96->112
#define		EPM_GRAPH_LNGX			500						//�O���t�w����
#define		EPM_GRAPH_LNGY			240			//256->240	//�O���t�x����

#define		BOGRP_ORGY				EPM_GRAPH_ORGY+EPM_GRAPH_LNGY		//���������_�Ƃ����O���t���_�x��Έʒu
#define		BOGRP_LNGX1				25						//�_�O���t�Ԋu
#define		BOGRP_LNGX2				19						//�_�O���t�w��

void	Dsp_EPM_INIT(void)
{
	UNs		gcnt;
	UNl		wX, wY, wP, wA, wB;
	UNl		gX, gY, Ylim;
	UNs		xdot, ydot;
	UNs		xcnt, ycnt;
	UNs		gsec, gmin;
	UNl		gtotal, gpoi, ep1, ep2;

	int		gYas, gYbs;

	EPM_GAMEN_RIF = 0;
	EPM_TLINF_BAK = 0xff;
	EPM_GAMRIF_CNT = 0;

	EPM_TIM_BAK = SV_EPMCSR_TIM;	//�P�ʎ���
	EPM_GRP_MXL = SV_EPMGRP_MXL;	//�_�O���t�ő�l
	EPM_GRP_MXR = SV_EPMGRP_MXR;	//�܂���O���t�ő�l

	gmin = SV_EPMCSR_TIM;					//�_����1�{���̕��i�ő�60���j
	if(gmin > 30)
	{
		gmin = 30;
	}

//V06b	if			(gmin == 5)		GRAPH_DT_MAKE(EPM_05MON_BUF, EPM_05MON_POI);
//////	else if		(gmin ==10)		GRAPH_DT_MAKE(EPM_10MON_BUF, EPM_10MON_POI);
//////	else if		(gmin ==15)		GRAPH_DT_MAKE(EPM_15MON_BUF, EPM_15MON_POI);
//////	else if		(gmin ==20)		GRAPH_DT_MAKE(EPM_20MON_BUF, EPM_20MON_POI);
//////	else if		(gmin ==25)		GRAPH_DT_MAKE(EPM_25MON_BUF, EPM_25MON_POI);
//////	else if		(gmin ==30)		GRAPH_DT_MAKE(EPM_30MON_BUF, EPM_30MON_POI);
//////	else if		(gmin ==35)		GRAPH_DT_MAKE(EPM_35MON_BUF, EPM_35MON_POI);
//////	else if		(gmin ==40)		GRAPH_DT_MAKE(EPM_40MON_BUF, EPM_40MON_POI);
//////	else if		(gmin ==45)		GRAPH_DT_MAKE(EPM_45MON_BUF, EPM_45MON_POI);
//////	else if		(gmin ==50)		GRAPH_DT_MAKE(EPM_50MON_BUF, EPM_50MON_POI);
//////	else if		(gmin ==55)		GRAPH_DT_MAKE(EPM_55MON_BUF, EPM_55MON_POI);
//////	else if		(gmin ==60)		GRAPH_DT_MAKE(EPM_60MON_BUF, EPM_60MON_POI);
	if			(gmin == 5)		GRAPH_DT_MAKE(EPM_05MIN_BUF, EPM_05MIN_POI, EPM_05MON_BUF, EPM_05MON_POI);
	else if		(gmin ==10)		GRAPH_DT_MAKE(EPM_10MIN_BUF, EPM_10MIN_POI, EPM_10MON_BUF, EPM_10MON_POI);
	else if		(gmin ==15)		GRAPH_DT_MAKE(EPM_15MIN_BUF, EPM_15MIN_POI, EPM_15MON_BUF, EPM_15MON_POI);
	else if		(gmin ==20)		GRAPH_DT_MAKE(EPM_20MIN_BUF, EPM_20MIN_POI, EPM_20MON_BUF, EPM_20MON_POI);
	else if		(gmin ==25)		GRAPH_DT_MAKE(EPM_25MIN_BUF, EPM_25MIN_POI, EPM_25MON_BUF, EPM_25MON_POI);
	else if		(gmin ==30)		GRAPH_DT_MAKE(EPM_30MIN_BUF, EPM_30MIN_POI, EPM_30MON_BUF, EPM_30MON_POI);
	else if		(gmin ==35)		GRAPH_DT_MAKE(EPM_35MIN_BUF, EPM_35MIN_POI, EPM_35MON_BUF, EPM_35MON_POI);
	else if		(gmin ==40)		GRAPH_DT_MAKE(EPM_40MIN_BUF, EPM_40MIN_POI, EPM_40MON_BUF, EPM_40MON_POI);
	else if		(gmin ==45)		GRAPH_DT_MAKE(EPM_45MIN_BUF, EPM_45MIN_POI, EPM_45MON_BUF, EPM_45MON_POI);
	else if		(gmin ==50)		GRAPH_DT_MAKE(EPM_50MIN_BUF, EPM_50MIN_POI, EPM_50MON_BUF, EPM_50MON_POI);
	else if		(gmin ==55)		GRAPH_DT_MAKE(EPM_55MIN_BUF, EPM_55MIN_POI, EPM_55MON_BUF, EPM_55MON_POI);
	else if		(gmin ==60)		GRAPH_DT_MAKE(EPM_60MIN_BUF, EPM_60MIN_POI, EPM_60MON_BUF, EPM_60MON_POI);

	if (EPM_CSR[0] == 0) {				//���وʒu0�͂��蓾�Ȃ��B�i�d���������ď��߂Ă̏ꍇ�����j
		EPM_CSR[0] = 1;					//���وʒu��ؾ��
	}
	EPM_CSR[1]=0;						//���وʒu�O��l�����������i��ʐؑւ莞�ɕ\������������j

	PV0_EPML_SCRH = SV_EPMGRP_MXL*10;	//�d�̓��j�^�O���t���チ����
	PV0_EPML_SCRM = PV0_EPML_SCRH/2;	//�d�̓��j�^�O���t����������
	PV0_EPML_SCRL = 0;					//�d�̓��j�^�O���t����������

	PV0_EPMR_SCRH = SV_EPMGRP_MXR*10;	//�d�̓��j�^�O���t�E�チ����
	PV0_EPMR_SCRM = PV0_EPMR_SCRH/2;	//�d�̓��j�^�O���t�E��������
	PV0_EPMR_SCRL = 0;					//�d�̓��j�^�O���t�E��������

	gX = EPM_GRAPH_ORGX + ((BOGRP_LNGX1-BOGRP_LNGX2) / 2);

	for (gcnt=0; gcnt<20; gcnt++)
	{
		/* ����d�͗ʂ̖_�O���t */
		gY = BOGRP_ORGY;							// ����kWh�ɑ΂���_�O���t�����o��Y�ʒu
		wX = PV0_EPML_SCRH - PV0_EPML_SCRL;			// ����kWh
		wY = EPM_GRAPH_LNGY;						// ����DOT
		wP = PV0_EPM_KWH[gcnt][0];					// ����kWh(�����_����)
		wA = (wP * wY) / wX;						// ����kWh�ɑ΂���_�O���t����
		Ylim = EPM_GRAPH_ORGY;

		Dsp_sikaku2(gX, gY, BOGRP_LNGX2, wA+1, COL_BLACK, COL_BLUE, Ylim+1);		//����d�͗ʂ̖_�O���t�`��

		/* �񐶓d�͗ʂ̖_�O���t */
		gY -= wA;									// ����kWh�ɑ΂���_�O���t�����o��Y�ʒu
		wX = PV0_EPML_SCRH - PV0_EPML_SCRL;			// ����kWh
		wY = EPM_GRAPH_LNGY;						// ����DOT
		wP = PV0_EPM_KWH[gcnt][1];					// ����kWh(�����_����)
		wA = (wP * wY) / wX;						// ����kWh�ɑ΂���_�O���t����

		Dsp_sikaku2(gX, gY, BOGRP_LNGX2, wA+1, COL_BLACK, COL_GREEN, Ylim+1);		//�񐶓d�͗ʂ̖_�O���t�`��

		gX += BOGRP_LNGX1;
	}

	gX = EPM_GRAPH_ORGX + (BOGRP_LNGX1 / 2) + 1;

	for (gcnt=0; gcnt<20; gcnt++)
	{
		/* �݌v�̐܂���O���t �h�b�g */
		gY = BOGRP_ORGY;							// ����kWh�ɑ΂���_�O���t�����o��Y�ʒu
		wX = PV0_EPMR_SCRH - PV0_EPMR_SCRL;			// ����kWh
		wY = EPM_GRAPH_LNGY;						// ����DOT
		wP = PV0_EPM_KWH[gcnt][2];					// ����kWh(�����_����)
		wA = (wP * wY) / wX;						// ����kWh�ɑ΂���dot����
		Ylim = EPM_GRAPH_ORGY;

		gYas = (int)gY-(int)wA;
		if (gYas < EPM_GRAPH_ORGY)
		{
			gYas = EPM_GRAPH_ORGY;
		}

		Dsp_sikaku2(gX-3-1, (UNl)gYas+3, 7, 7, COL_ORANGE, COL_ORANGE, Ylim-3);		//����d�͗ʂ̖_�O���t�`��

		/* �݌v�̐܂���O���t ������� */
		if (gcnt<19)
		{
			wP = PV0_EPM_KWH[gcnt+1][2];			// ����kWh(�����_����)
			wB = (wP * wY) / wX;					// ����kWh�ɑ΂���_�O���t����

			gYbs = (int)gY-(int)wB;
			if (gYbs < EPM_GRAPH_ORGY)
			{
				gYbs = EPM_GRAPH_ORGY;
			}

			Disp_Line(gX, (UNl)gYas, gX+BOGRP_LNGX1, (UNl)gYbs, COL_ORANGE/*, EPM_GRAPH_ORGY, BOGRP_ORGY*/);

			gX += BOGRP_LNGX1;
		}
	}

}


//V06b	void	GRAPH_DT_MAKE(UNl MON_BUF[][2], UNs MON_POI)
void	GRAPH_DT_MAKE(UNl ADD_BUF[][2], UNs ADD_POI, UNl MON_BUF[][2], UNs MON_POI)
{
	UNs		xcnt, ycnt;
	UNl		ep1, ep2;

//V06b	for (xcnt=0; xcnt<20; xcnt++)				//20�{�����ް���ώZ
	for (xcnt=0; xcnt<19; xcnt++)				//1�{�ځ`19�{�ڂ��ް����쐬
	{
		ep1 = MON_BUF[MON_POI][0];			//����d�͗�[kWs]�ώZ
		ep2 = MON_BUF[MON_POI][1];			//�񐶓d�͗�[kWs]�ώZ

		MON_POI += 1;
//V06b		if (MON_POI>=20)	MON_POI = 0;
		if (MON_POI>=19)	MON_POI = 0;

		ep1 = ep1/3600;
		PV0_EPM_KWH[xcnt][0] = ep1;			//����d�͗�[kWh]
		ep2 = ep2/3600;
		PV0_EPM_KWH[xcnt][1] = ep2;			//�񐶓d�͗�[kWh]

		if (xcnt == 0)
		{
			if (EPM_TOTAL_INF == BIT_0) 
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0];	//�݌v(����)
			}
			else if  (EPM_TOTAL_INF == BIT_1)
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][1];	//�݌v(��)
			}
			else
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt][1];	//�݌v(����{��)
			}
		}
		else
		{
			if (EPM_TOTAL_INF == BIT_0) 
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt-1][2];	//�݌v(����)
			}
			else if  (EPM_TOTAL_INF == BIT_1)
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][1] + PV0_EPM_KWH[xcnt-1][2];	//�݌v(��)
			}
			else
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt][1] + PV0_EPM_KWH[xcnt-1][2];	//�݌v(����{��)
			}
		}
	}

//V06b	�ŏ���20�{�ڂ��ް����쐬
	for (xcnt=0,ep1=0,ep2=0; xcnt<ADD_POI; xcnt++)
	{
		ep1 += ADD_BUF[0][0];			//����d�͗�[kWs]�ώZ
		ep2 += ADD_BUF[0][1];			//�񐶓d�͗�[kWs]�ώZ
	}
	ep1 = ep1/3600;
	PV0_EPM_KWH[19][0] = ep1;			//����d�͗�[kWh]
	ep2 = ep2/3600;
	PV0_EPM_KWH[19][1] = ep2;			//�񐶓d�͗�[kWh]

	if (EPM_TOTAL_INF == BIT_0) 
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][0] + PV0_EPM_KWH[19-1][2];	//�݌v(����)
	}
	else if  (EPM_TOTAL_INF == BIT_1)
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][1] + PV0_EPM_KWH[19-1][2];	//�݌v(��)
	}
	else
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][0] + PV0_EPM_KWH[19][1] + PV0_EPM_KWH[19-1][2];	//�݌v(����{��)
	}

}

/*
********************************************************************************
*  Module Name:		Dsp_EPM_GRAPH
*  Function Name:	�d�̓��j�^�O���t�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08				V06
********************************************************************************
*/
void	Dsp_EPM_GRAPH(void)
{
	if ( (EPM_TIM_BAK != SV_EPMCSR_TIM) ||		//�P�ʎ��ԕς�����H
		 (EPM_GRP_MXL != SV_EPMGRP_MXL) ||		//�_�O���t�ő�l�ς�����H
		 (EPM_GRP_MXR != SV_EPMGRP_MXR) ||		//�܂���O���t�ő�l�ς�����H
		 (EPM_GAMEN_RIF == 1) )					//�ĕ`��w�߁H
	{
		/* �ĕ`�� */
		Dsp_sikaku1 ( EPM_GRAPH_ORGX-4, EPM_GRAPH_ORGY-4,
					  EPM_GRAPH_LNGX+8, EPM_GRAPH_LNGY+8,
					  GAMENn_HEAD.scr_col, GAMENn_HEAD.scr_col );

		Disp_Line_Box (EPM_GRAPH_ORGX, EPM_GRAPH_ORGY, EPM_GRAPH_LNGX, EPM_GRAPH_LNGY, COL_BLACK);

		Dsp_EPM_INIT();
	}

	Dsp_EPM_Csr();
	EPM_TOTAL_DISP();
}


/*
********************************************************************************
*  Module Name:		Dsp_EPM_Csr
*  Function Name:	���������ݸޔg�`��ʂ̶��ٕ\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08				V06
********************************************************************************
*/
void	Dsp_EPM_Csr(void)
{
	UNs		csr_n, csr_o, xdot;
	UNs		csr_mark;
	UNs		wkt;

	/***** �J�[�\���ʒu�̎����l�쐬 *****/
	PV0_EPMCSR_UEP = PV0_EPM_KWH[EPM_CSR[0]-1][0];	//�d�̓��j�^�J�[�\���ʒu�̏���d�͗�
	PV0_EPMCSR_KEP = PV0_EPM_KWH[EPM_CSR[0]-1][1];	//�d�̓��j�^�J�[�\���ʒu�̉񐶓d�͗�
	PV0_EPMCSR_TEP = PV0_EPM_KWH[EPM_CSR[0]-1][2];	//�d�̓��j�^�J�[�\���ʒu�̗݌v�l

	wkt = SV_EPMCSR_TIM * (20 - EPM_CSR[0]);
	PV0_EPMCSR_HOR = wkt / 60;						//�d�̓��j�^�J�[�\���ʒu�̎���
	PV0_EPMCSR_MIN = wkt % 60;						//�d�̓��j�^�J�[�\���ʒu�̕�

	/***** �J�[�\���ʒu�́��}�[�N�\�� *****/
	csr_n = EPM_CSR[0];
	csr_o = EPM_CSR[1];

	if (csr_n == csr_o)			return;

	EPM_CSR[1] = csr_n;					//�V���وʒu�ۑ�

	/* �O�̈ʒu���߰��ŏ��� */
	if (csr_o != 0) 
	{
		xdot = ((csr_o-1) * BOGRP_LNGX1) + (EPM_GRAPH_ORGX+(BOGRP_LNGX1/2)-8);
		csr_mark = 0x8140;//��߰�	S-JIS����
		disp_moji_s_color (
			2,						/*t_p->M_LEN,*/
			xdot,					/*t_p->X_POS,*/
			BOGRP_ORGY+8,			/*t_p->Y_POS,*/
			COL_RED,				/*t_p->C_COL,*/
			GAMENn_SCR_COL,			/*t_p->B_COL1,*/
			0x0101,					/*t_p->SIZE,*/
			&csr_mark, 
			LCD_VRAM
			);
	}
	
	/* ���̈ʒu��\�� */
	if (csr_n >= 1) 
	{
		xdot = ((csr_n-1) * BOGRP_LNGX1) + (EPM_GRAPH_ORGX+(BOGRP_LNGX1/2)-8);
		csr_mark = 0x81A3;//��		S-JIS����
		disp_moji_s_color (
			2,						/*t_p->M_LEN,*/
			xdot,					/*t_p->X_POS,*/
			BOGRP_ORGY+8,			/*t_p->Y_POS,*/
			COL_RED,				/*t_p->C_COL,*/
			GAMENn_SCR_COL,			/*t_p->B_COL1,*/
			0x0101,					/*t_p->SIZE,*/
			&csr_mark, 
			LCD_VRAM
			);
	}
}


/****************************************************************************/
/*																			*/
/*	�d�̓��j�^�݌v�l�ؑ֕\��	(����)/(��)/(���v)	3�m�b�`				*/
/*																			*/
/*		EPM_TOTAL_INF		�F	3�m�b�`���									*/
/*																			*/
/****************************************************************************/
void	EPM_TOTAL_DISP	(void)
{
	UNs		i;
	UNs		chk;
	UNs		mode;
	UNl		adr;
	UNs		*hrom;

	mode = EPM_TOTAL_INF;							/* Ӱ��SW�Ǎ�			*/
	chk  = 0x0001;

	for (i=0; i<3; i++){							/* �ޯ�����				*/
		if ((mode & chk) != 0x0000)		break;		/* ����OK				*/
		chk = (chk << 1);							/* 1�ޯļ��				*/
	}												/*						*/

	if (EPM_TLINF_BAK == i)				return;
	EPM_TLINF_BAK = i;

	adr =  CHR_TABLE_ADR + ((i+413-1) * CHAR_MOJI_SIZE);	// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		6, 					/* ��׸��			*/
		544, 				/* ���o��X�ʒu		*/
		48, 				/* ���o��Y�ʒu		*/
		COL_BLACK,			/* �����F			*/
		COL_ORANGE,			/* �w�i�F			*/
		0x0101, 			/* ��������			*/
		hrom, 				/* �����i�[���ڽ	*/
		LCD_VRAM			/* �\�����			*/
		);
}


//������������������������������������������������������������������������������������������������������������������������

void	Pv_Graph_Deb(void)
{
	UNs		poi;

	WAVE_SAMP_DTP[0]++;
	if (WAVE_SAMP_DTP[0] > 500) {
		WAVE_SAMP_DTP[0] = 1;
	}

	poi = WAVE_SAMP_DTP[0];
	if (poi == 1)
	{
		WAVE_SAMP_DATA[poi].renia1 = 0;
		WAVE_SAMP_DATA[poi].angle = 0;
		WAVE_SAMP_DATA[poi].kajyuL = 0;
		WAVE_SAMP_DATA[poi].kajyuR = 0;
		WAVE_SAMP_DATA[poi].kajyuT = 0;
		WAVE_SAMP_DATA[poi].elepw = (UNl)-5000;
	}
	else
	{
		/**************** �Ʊ1�̔g�`�`�� ******************/
		WAVE_SAMP_DATA[poi].renia1 = WAVE_SAMP_DATA[poi-1].renia1 +1000;		//+1.000mm

		/**************** �p�x�̔g�`�`�� ******************/
		if (WAVE_SAMP_DATA[poi-1].angle == 3599)
		{
			WAVE_SAMP_DATA[poi].angle = 0;
		}
		else
		{
			WAVE_SAMP_DATA[poi].angle = WAVE_SAMP_DATA[poi-1].angle +100;
			if (WAVE_SAMP_DATA[poi].angle > 3599) {
				WAVE_SAMP_DATA[poi].angle = 3599;
			}
		}

		/**************** �׏d�̔g�`�`�� ******************/
		WAVE_SAMP_DATA[poi].kajyuL = (short)WAVE_SAMP_DATA[poi-1].kajyuL +20;
		if ((short)WAVE_SAMP_DATA[poi].kajyuL > 1000) {
			WAVE_SAMP_DATA[poi].kajyuL = -1000;
		}
		WAVE_SAMP_DATA[poi].kajyuR = (short)WAVE_SAMP_DATA[poi-1].kajyuR +40;
		if ((short)WAVE_SAMP_DATA[poi].kajyuR > 1000) {
			WAVE_SAMP_DATA[poi].kajyuR = 0;
		}
		WAVE_SAMP_DATA[poi].kajyuT = (short)WAVE_SAMP_DATA[poi].kajyuL + (short)WAVE_SAMP_DATA[poi].kajyuR;

		/**************** �u���d�͂̔g�`�`�� ******************/
		WAVE_SAMP_DATA[poi].elepw = (int)WAVE_SAMP_DATA[poi-1].elepw +200;
		if ((int)WAVE_SAMP_DATA[poi].elepw > 10000) {
			WAVE_SAMP_DATA[poi].elepw = (UNl)-5000;
		}
	}

//	-----------------------------------------------------------------------------------

	WAVE_TRND_DTP[0]++;
	if (WAVE_TRND_DTP[0] > 5000) {
		WAVE_TRND_DTP[0] = 1;
	}

	poi = WAVE_TRND_DTP[0];
	if (poi == 1)
	{
		WAVE_TRND_DATA[poi].renia1 = 0;
		WAVE_TRND_DATA[poi].kajyuL = 0;
		WAVE_TRND_DATA[poi].kajyuR = 0;
		WAVE_TRND_DATA[poi].kajyuT = 0;
		WAVE_TRND_DATA[poi].elepw = 0;
	}
	else
	{
		/**************** �Ʊ1�̔g�`�`�� ******************/
		WAVE_TRND_DATA[poi].renia1 = WAVE_TRND_DATA[poi-1].renia1 +100;			//+0.100mm

		/**************** �׏d�̔g�`�`�� ******************/
		WAVE_TRND_DATA[poi].kajyuL = (short)WAVE_TRND_DATA[poi-1].kajyuL +10;
		if ((short)WAVE_TRND_DATA[poi].kajyuL > 1000) {
			WAVE_TRND_DATA[poi].kajyuL = -1000;
		}
		WAVE_TRND_DATA[poi].kajyuR = (short)WAVE_TRND_DATA[poi-1].kajyuR +20;
		if ((short)WAVE_TRND_DATA[poi].kajyuR > 1000) {
			WAVE_TRND_DATA[poi].kajyuR = -1000;
		}
		WAVE_TRND_DATA[poi].kajyuT = (short)WAVE_TRND_DATA[poi].kajyuL + (short)WAVE_TRND_DATA[poi].kajyuR;

		/**************** 1���ٓd�͗ʂ̔g�`�`�� ******************/
		WAVE_TRND_DATA[poi].elepw = (short)WAVE_TRND_DATA[poi-1].elepw +100;
		if ((short)WAVE_TRND_DATA[poi].elepw > 10000) {
			WAVE_TRND_DATA[poi].elepw = -5000;
		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_PvWave_5ms
*  Function Name:	�����g�`�`��5ms�����ݏ���
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvWave_5ms(void)
{
	UNs	wk1[5];
	UNs	*poiwk, poimx;

//V06	if( (GAMEN_NO==9) || (GAMEN_NO==10) )
	if( (GAMEN_NO==9) || (GAMEN_NO==10) || (GAMEN_NO==102) )
	{
		wk1[0] = Key_Data_No[0] ^ PW_Key_last[0];	/* key��Ԃ̕ω������o	*/
		wk1[1] = Key_Data_No[1] ^ PW_Key_last[1];
		wk1[2] = Key_Data_No[2] ^ PW_Key_last[2];
		wk1[3] = Key_Data_No[3] ^ PW_Key_last[3];

		PW_Key_up[0] = wk1[0] & Key_Data_No[0];		/* �����オ��f�[�^�i�[ */
		PW_Key_up[1] = wk1[1] & Key_Data_No[1];		/* �����オ��f�[�^�i�[ */
		PW_Key_up[2] = wk1[2] & Key_Data_No[2];		/* �����オ��f�[�^�i�[ */
		PW_Key_up[3] = wk1[3] & Key_Data_No[3];		/* �����オ��f�[�^�i�[ */

		PW_Key_dn[0] = wk1[0] & PW_Key_last[0];		/* ����������f�[�^�i�[ */
		PW_Key_dn[1] = wk1[1] & PW_Key_last[1];		/* ����������f�[�^�i�[ */
		PW_Key_dn[2] = wk1[2] & PW_Key_last[2];		/* ����������f�[�^�i�[ */
		PW_Key_dn[3] = wk1[3] & PW_Key_last[3];		/* ����������f�[�^�i�[ */

		PW_Key_last[0] = Key_Data_No[0];
		PW_Key_last[1] = Key_Data_No[1];
		PW_Key_last[2] = Key_Data_No[2];
		PW_Key_last[3] = Key_Data_No[3];

		if( GAMEN_NO==9 )
		{
			if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 257) {			//V06g 2011/07/28
				return;
			}
			poiwk = &CSR_PVSAMP[0];
			poimx = 500;
		}
		else if (GAMEN_NO==10)
		{
			poiwk = &CSR_PVTRND[0];
			poimx = 500;
		}
		else if (GAMEN_NO==102)				//V06
		{
			poiwk = &EPM_CSR[0];
			poimx = 20;
		}

		if ( PW_Key_up[2] & 0x0004 )					/* �r�v�T�@�j�d�x  ���ړ� */
		{
			if (*poiwk > 1)
			{
				(*poiwk)--;
			}
			PW_Key_tim02[0] = 0;						//0.2sec�v���p		5ms���ɶ���   40���Ă�0.2�b
			PW_Key_tim30[0] = 0;						//3.0sec�v���p		5ms���ɶ���  600���Ă�3.0�b
		}

		else if( PW_Key_up[1] & 0x0004 )				/* �r�v�U�@�j�d�x  �E�ړ� */
		{
			if (*poiwk < poimx)
			{
				(*poiwk)++;
			}
			PW_Key_tim02[1] = 0;						//0.2sec�v���p		5ms���ɶ���   40���Ă�0.2�b
			PW_Key_tim30[1] = 0;						//3.0sec�v���p		5ms���ɶ���  600���Ă�3.0�b
		}

		if (PW_Key_tim02[0]>=40)					/* �����O�D�Q�b  ���ړ� */
		{
			PW_Key_tim02[0] = 0;
			if (PW_Key_tim30[0]>=600)				//�������R�b�ȏ�H
			{
				if (*poiwk >= 11)
				{
					*poiwk = *poiwk - 10;		//10�Â���
				}
				else
				{
					*poiwk = 1;
				}
			}
			else
			{
				if (*poiwk > 1)
				{
					(*poiwk)--;						//1�Â���
				}
			}
		}

		else if (PW_Key_tim02[1]>=40)					/* �����O�D�Q�b  �E�� */
		{
			PW_Key_tim02[1] = 0;
			if (PW_Key_tim30[1]>=600)					//�������R�b�ȏ�H
			{
				if (*poiwk <= (poimx-10))
				{
					*poiwk = *poiwk + 10;		//10�Â���
				}
				else
				{
					*poiwk = poimx;
				}
			}
			else
			{
				if (*poiwk < poimx)
				{
					(*poiwk)++;						//�P�Â���
				}
			}
		}


		if (Key_Data_No[2] & 0x0004) {
			if (PW_Key_tim02[0]<1000) {
				PW_Key_tim02[0]++;						//0.2sec�v���p		5ms���ɶ���   40���Ă�0.2�b
			}
			if (PW_Key_tim30[0]<1000) {
				PW_Key_tim30[0]++;						//3.0sec�v���p		5ms���ɶ���  600���Ă�3.0�b
			}
		}
		else if (Key_Data_No[1] & 0x0004) {
			if (PW_Key_tim02[1]<1000) {
				PW_Key_tim02[1]++;						//0.2sec�v���p		5ms���ɶ���   40���Ă�0.2�b
			}
			if (PW_Key_tim30[1]<1000) {
				PW_Key_tim30[1]++;						//3.0sec�v���p		5ms���ɶ���  600���Ă�3.0�b
			}
		}
		
	}


//debug	Pv_Graph_Deb();

}


