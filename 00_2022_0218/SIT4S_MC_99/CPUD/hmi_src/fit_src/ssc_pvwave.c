/************************************************************************************/
/*																					*/
/*																					*/
/*		コマツ産機㈱殿向け　ＳＩＴ－Ｓ　実測波形表示プログラム						*/
/*																					*/
/*		（ssc_graph.cからincludeしている）											*/
/*																					*/
/************************************************************************************/

#define		pvGRAPH_XSIZE		  500				/* ｸﾞﾗﾌ描画X軸ｻｲｽﾞ(dot)	*/
#define		pvGRAPH_YSIZE		  288				/* ｸﾞﾗﾌ描画Y軸ｻｲｽﾞ(dot)	*/
#define		pvGRAPH_XOPOS		  1*16				/* ｸﾞﾗﾌ描画X軸原点(X0の)絶対位置(dot)	*/
#define		pvGRAPH_YOPOS		  (12*32)-1				/* ｸﾞﾗﾌ描画Y軸原点(Y0の)絶対位置(dot)	*/


/* 外部参照関数定義 -------------------------------------------------- */

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		Key_Data_No[4];

/* 定数定義 ---------------------------------------------------------- */

/* データ型定義 ------------------------------------------------------ */

/* プロトタイプ宣言 -------------------------------------------------- */
void	Dsp_Pvgraph_Screen(void);
void	Dsp_Pv_Wave(UNs poi_old, UNs ydot, UNs ybak, UNs col);
void	Dsp_PvSamp_Csr(void);
void	Dsp_PvTrnd_Csr(void);
void	Dsp_EPM_Csr(void);				//V06
void	EPM_TOTAL_DISP(void);			//V06a
//V06b	void	GRAPH_DT_MAKE(UNl MON_BUF[][2], UNs MON_POI);//V06a
void	GRAPH_DT_MAKE(UNl ADD_BUF[][2], UNs ADD_POI, UNl MON_BUF[][2], UNs MON_POI);//V06b

/* 内部変数定義 ------------------------------------------------------ */

/* テーブル定義 ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		Dsp_Pvgraph_INIT
*  Function Name:	波形表示画面遷移時の初期処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pvgraph_INIT(void)
{
	WAVE_SAMP_DTP[1] = 0;					//実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ
	WAVE_TRND_DTP[1] = 0;					//実測ﾄﾚﾝﾄﾞ波形描画位置ﾎﾟｲﾝﾀ前回値をﾌﾟﾘｾｯﾄ

	if (CSR_PVSAMP[0] == 0) {				//ｶｰｿﾙ位置0はあり得ない。（電源投入して初めての場合だけ）
		CSR_PVSAMP[0] = 1;					//ｶｰｿﾙ位置ﾌﾟﾘｾｯﾄ
	}
	if (CSR_PVTRND[0] == 0) {				//ｶｰｿﾙ位置0はあり得ない。（電源投入して初めての場合だけ）
		CSR_PVTRND[0] = 1;					//ｶｰｿﾙ位置ﾌﾟﾘｾｯﾄ
	}
	CSR_PVSAMP[1]=0;						//ｶｰｿﾙ位置前回値強制初期化（画面切替り時に表示したいから）
	CSR_PVTRND[1]=0;						//ｶｰｿﾙ位置前回値強制初期化（画面切替り時に表示したいから）

	Dsp_Pvgraph_Screen();
}


/*
********************************************************************************
*  Module Name:		Dsp_Pvgraph_Screen
*  Function Name:	波形表示部の背景表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pvgraph_Screen(void)
{
	UNs		i;
	UNs		xcnt, ycnt;
	UNs		xdot, ydot;
	UNs		col;

	xdot = pvGRAPH_XOPOS;						//X軸原点位置
	for(xcnt=0; xcnt<pvGRAPH_XSIZE; xcnt++)		//XSIZE=500dot
	{
		ydot = pvGRAPH_YOPOS;					//Y軸原点位置
		for(ycnt=0; ycnt<pvGRAPH_YSIZE; ycnt++)	//XSIZE=288dot
		{
			if ( (xcnt == (pvGRAPH_XSIZE/5)*1-1) ||	//縦ﾗｲﾝ(100ﾄﾞｯﾄ目)：白
				 (xcnt == (pvGRAPH_XSIZE/5)*2-1) ||	//縦ﾗｲﾝ(200ﾄﾞｯﾄ目)：白
				 (xcnt == (pvGRAPH_XSIZE/5)*3-1) ||	//縦ﾗｲﾝ(300ﾄﾞｯﾄ目)：白
				 (xcnt == (pvGRAPH_XSIZE/5)*4-1) ||	//縦ﾗｲﾝ(400ﾄﾞｯﾄ目)：白
				 (ycnt == (pvGRAPH_YSIZE/2)*1-1) ) 	//横ﾗｲﾝ(144ﾄﾞｯﾄ目)：白
			{
				col = 7;							//ﾗｲﾝ：白
			}
			else
			{
				col = 0;								//背景色：黒
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
*  Function Name:	実測ｻﾝﾌﾟﾘﾝｸﾞ波形描画
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
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
////	if(SV_WAVE_SCL5D != 0) {			//ｻﾝﾌﾟﾘﾝｸﾞ画面  電力最小値設定符号		//V06a
////		PV0_EPMDAT_SIN |= BIT_0;
////	} else {
////		PV0_EPMDAT_SIN &= ~BIT_0;
////	}
////	if(PV0_SMPCSR_EP_SIN < 0) {			//ｻﾝﾌﾟﾘﾝｸﾞ画面  ｶｰｿﾙ位置の電力値符号	//V06a
////		PV0_EPMDAT_SIN |= BIT_1;
////	} else {
////		PV0_EPMDAT_SIN &= ~BIT_1;
////	}


	Dsp_PvSamp_Csr();						//ｶｰｿﾙ表示

	poi_new = WAVE_SAMP_DTP[0];
	poi_old = WAVE_SAMP_DTP[1];

	if (poi_new == poi_old)		return;

	if (poi_new < poi_old) 					//ﾎﾟｲﾝﾀ戻った？
	{
		Dsp_Pvgraph_Screen();
		poi_old = 0;
	}

	if (poi_new == 0)
	{
		WAVE_SAMP_DTP[1] = poi_new;
		return;
	}

	for ( ; poi_old < poi_new; poi_old++)			//最新のﾎﾟｲﾝﾀ位置まで描画する
	{
		/**************** 角度の波形描画 ******************/
		ulmw = 3599;								//ｸﾞﾗﾌの上限角度
		dlmw = 0;									//ｸﾞﾗﾌの下限角度
		dtw = WAVE_SAMP_DATA[poi_old+1].angle;		//実測
		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
			dtw = ulmw;
		}
		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
			dtw = dlmw;
		}
		lenw = ulmw - dlmw;							//
		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].angle = ydot;		//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].angle;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_ORANGE);

		/**************** ﾘﾆｱ1の波形描画 ******************/
//		ulml = SV_RNAPOS_MAXP;						//ｸﾞﾗﾌの上限＝機械上限
//		dlml = SV_RNAPOS_MINP;						//ｸﾞﾗﾌの下限＝機械下限
		ulml = SV_WAVE_SCL1U;						//ｸﾞﾗﾌの上限＝機械上限
		dlml = SV_WAVE_SCL1D;						//ｸﾞﾗﾌの下限＝機械下限
		dtl = WAVE_SAMP_DATA[poi_old+1].renia1;		//実測
		dtl = cnv_mm_inch(dtl, 0);					//mm→inch
		if (dtl > ulml){		//上限ﾘﾐｯﾀ
			dtl = ulml;
		}
		if (dtl < dlml){		//下限ﾘﾐｯﾀ
			dtl = dlml;
		}
		lenl = ulml - dlml;							//
		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].renia1 = ydot;		//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].renia1;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_BLUE);

//H2W		/**************** ﾘﾆｱ2の波形描画 ******************/
//////		ulml = SV_RNAPOS_MAXP;						//ｸﾞﾗﾌの上限＝機械上限
//////		dlml = SV_RNAPOS_MINP;						//ｸﾞﾗﾌの下限＝機械下限
////		ulml = SV_WAVE_SCL1U;						//ｸﾞﾗﾌの上限＝機械上限
////		dlml = SV_WAVE_SCL1D;						//ｸﾞﾗﾌの下限＝機械下限
////		dtl = WAVE_SAMP_DATA[poi_old+1].renia2;		//実測
////		dtl = cnv_mm_inch(dtl, 0);					//mm→inch
////		if (dtl > ulml){		//上限ﾘﾐｯﾀ
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//下限ﾘﾐｯﾀ
////			dtl = dlml;
////		}
////		lenl = ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].renia2 = ydot;		//ydot位置保存
////		ybak = WAVE_SAMP_DOT[poi_old].renia2;		//ydot前回位置
////
////		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_BLUE);

		/**************** 荷重合計の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuT;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuT = ydot;		//ydot位置保存
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuT;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuT;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuT = ydot;		//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].kajyuT;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_GREEN);

		/**************** 荷重左の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuL;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuL = ydot;		//ydot位置保存
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuL;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuL;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuL = ydot;		//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].kajyuL;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_YELLOW);

		/**************** 荷重右の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_SAMP_DATA[poi_old+1].kajyuR;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_SAMP_DOT[poi_old+1].kajyuR = ydot;		//ydot位置保存
////		ybak = WAVE_SAMP_DOT[poi_old].kajyuR;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL2U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL2D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_SAMP_DATA[poi_old+1].kajyuR;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].kajyuR = ydot;		//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].kajyuR;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_PINK);

		/**************** 瞬時電力の波形描画 ******************/	//V06
		if (SEQ_PAR_103 & BIT_12)
		{
//V06a			ulml = SV_WAVE_SCL5U;						//ｸﾞﾗﾌの上限＝機械上限
//////			dlml = SV_WAVE_SCL5D;						//ｸﾞﾗﾌの下限＝機械下限
//////			dtl = WAVE_SAMP_DATA[poi_old+1].elepw;		//実測
//////			if (dtl > ulml){		//上限ﾘﾐｯﾀ
//////				dtl = ulml;
//////			}
//////			if (dtl < dlml){		//下限ﾘﾐｯﾀ
//////				dtl = dlml;
//////			}
//////			lenl = ulml - dlml;							//
//////			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
//////			ydot = pvGRAPH_YOPOS - pvdot;
//////			WAVE_SAMP_DOT[poi_old+1].elepw = ydot;		//ydot位置保存
//////			ybak = WAVE_SAMP_DOT[poi_old].elepw;		//ydot前回位置

			s_ulml = (long)SV_WAVE_SCL5U;						//ｸﾞﾗﾌの上限＝機械上限
//2014/03/14			s_dlml = (int)SV_WAVE_SCL5D * -1;					//ｸﾞﾗﾌの下限＝機械下限
			s_dlml = (long)SV_WAVE_SCL5D;					//ｸﾞﾗﾌの下限＝機械下限
			s_dtl = (long)WAVE_SAMP_DATA[poi_old+1].elepw;		//実測
			if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
				s_dtl = s_ulml;
			}
			if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
				s_dtl = s_dlml;
			}
			s_lenl = s_ulml - s_dlml;							//
//V06b			pvdot = ((UNs)(s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / (UNs)s_lenl;	//pv * ysize(max287dot) / ysize(max)
			pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_SAMP_DOT[poi_old+1].elepw = ydot;		//ydot位置保存
			ybak = WAVE_SAMP_DOT[poi_old].elepw;		//ydot前回位置
    
			Dsp_Pv_Wave(poi_old, ydot, ybak, COL_RED);
		}

		/**************** ｼｰｹﾝｽbit0の波形描画 ******************/
		dtw = 16;
		if (WAVE_SAMP_DATA[poi_old+1].seq & BIT_0)	//実測
		{
			dtw = dtw+16;
		}
		lenw = 287;							//
		pvdot = (dtw * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].seq1 = ydot;			//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].seq1;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_LBULE);

		/**************** ｼｰｹﾝｽbit1の波形描画 ******************/
		dtw = 16+32;
		if (WAVE_SAMP_DATA[poi_old+1].seq & BIT_1)	//実測
		{
			dtw = dtw+16;
		}
		lenw = 287;							//
		pvdot = (dtw * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_SAMP_DOT[poi_old+1].seq2 = ydot;			//ydot位置保存
		ybak = WAVE_SAMP_DOT[poi_old].seq2;		//ydot前回位置

		Dsp_Pv_Wave(poi_old, ydot, ybak, COL_LBULE);

	}

	WAVE_SAMP_DTP[1] = poi_new;
}


/*
********************************************************************************
*  Module Name:		Dsp_PvTrnd_Wave
*  Function Name:	実測ﾄﾚﾝﾄﾞ波形描画
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
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

	Dsp_PvTrnd_Csr();						//ｶｰｿﾙ表示

	poi_new = WAVE_TRND_DTP[0];				//現在ﾎﾟｲﾝﾀ位置
	poi_old = WAVE_TRND_DTP[1];				//前回ﾎﾟｲﾝﾀ位置

	if (poi_new == 0)
	{
		WAVE_TRND_DTP[1] = poi_new;
		return;
	}

	if (poi_new == poi_old)		return;		//ﾎﾟｲﾝﾀ位置変化あったか？

	if ( SV_WAVE_PAGE == 0 )				//表示ﾍﾟｰｼﾞ0？
	{
		area_o = (poi_old-1)/500;				//前回ﾎﾟｲﾝﾀ位置の表示エリア
		area_n = (poi_new-1)/500;				//現在ﾎﾟｲﾝﾀ位置の表示エリア

		if (area_o == area_n)					//表示エリア変わった？
		{
			dpoi_o = poi_old % 500;				//前回の表示ﾎﾟｲﾝﾀ位置		exp:502=2
			dpoi_n = poi_new % 500;				//現在の表示ﾎﾟｲﾝﾀ位置		exp:999=499 / 1000=500
			if (dpoi_n==0)
			{
				dpoi_n = 500;
			}
		}
		else
		{	//表示エリア変更
			Dsp_Pvgraph_Screen();
			dpoi_o = 0;
			dpoi_n = poi_new % 500;				//現在の表示ﾎﾟｲﾝﾀ位置		exp:999=499 / 1000=500
			if (dpoi_n==0)
			{
				dpoi_n = 500;
			}
			poi_old = area_n*500;				//ﾍﾟｰｼﾞの先頭ﾎﾟｲﾝﾀにﾌﾟﾘｾｯﾄ
		}
	}
	else
	{
		if(poi_old != 0)	return;
		Dsp_Pvgraph_Screen();					//V05o_a
		dpoi_o = 0;
		dpoi_n = 500;
		area_n = (poi_new-1)/500;				//現在ﾎﾟｲﾝﾀ位置の表示エリア
		if (area_n >= SV_WAVE_PAGE)
		{
			poi_old = (area_n-SV_WAVE_PAGE)*500;	
		}
		else
		{
			poi_old = (10-(SV_WAVE_PAGE-area_n))*500;	
		}
	}

	for ( ; dpoi_o < dpoi_n; dpoi_o++, poi_old++)			//最新のﾎﾟｲﾝﾀ位置まで描画する
	{
		/**************** ﾘﾆｱ1の波形描画 ******************/
//		ulml = SV_RNAPOS_MAXP;						//ｸﾞﾗﾌの上限＝機械上限
//		dlml = SV_RNAPOS_MINP;						//ｸﾞﾗﾌの下限＝機械下限
		ulml = SV_WAVE_SCL3U;						//ｸﾞﾗﾌの上限＝機械上限
		dlml = SV_WAVE_SCL3D;						//ｸﾞﾗﾌの下限＝機械下限
		dtl = WAVE_TRND_DATA[poi_old+1].renia1;		//実測
		dtl = cnv_mm_inch(dtl, 0);					//mm→inch
		if (dtl > ulml){		//上限ﾘﾐｯﾀ
			dtl = ulml;
		}
		if (dtl < dlml){		//下限ﾘﾐｯﾀ
			dtl = dlml;
		}
		lenl = ulml - dlml;							//
		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].renia1 = ydot;		//ydot位置保存
		ybak = WAVE_TRND_DOT[poi_old].renia1;		//ydot前回位置

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_BLUE);

//H2W		/**************** ﾘﾆｱ2の波形描画 ******************/
//////		ulml = SV_RNAPOS_MAXP;						//ｸﾞﾗﾌの上限＝機械上限
//////		dlml = SV_RNAPOS_MINP;						//ｸﾞﾗﾌの下限＝機械下限
////		ulml = SV_WAVE_SCL3U;						//ｸﾞﾗﾌの上限＝機械上限
////		dlml = SV_WAVE_SCL3D;						//ｸﾞﾗﾌの下限＝機械下限
////		dtl = WAVE_TRND_DATA[poi_old+1].renia2;		//実測
////		dtl = cnv_mm_inch(dtl, 0);					//mm→inch
////		if (dtl > ulml){		//上限ﾘﾐｯﾀ
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//下限ﾘﾐｯﾀ
////			dtl = dlml;
////		}
////		lenl = ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].renia2 = ydot;		//ydot位置保存
////		ybak = WAVE_TRND_DOT[poi_old].renia2;		//ydot前回位置
////
////		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_BLUE);

		/**************** 荷重合計の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuT;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuT = ydot;		//ydot位置保存
////		ybak = WAVE_TRND_DOT[poi_old].kajyuT;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuT;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuT = ydot;		//ydot位置保存
		ybak = WAVE_TRND_DOT[poi_old].kajyuT;		//ydot前回位置

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_GREEN);

		/**************** 荷重左の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuL;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuL = ydot;		//ydot位置保存
////		ybak = WAVE_TRND_DOT[poi_old].kajyuL;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuL;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuL = ydot;		//ydot位置保存
		ybak = WAVE_TRND_DOT[poi_old].kajyuL;		//ydot前回位置

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_YELLOW);

		/**************** 荷重右の波形描画 ******************/
//2014/03/14
////		ulmw = SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
////		dlmw = SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
////		dtw = WAVE_TRND_DATA[poi_old+1].kajyuR;		//実測
////		if (dtw > ulmw){		//上限ﾘﾐｯﾀ
////			dtw = ulmw;
////		}
////		if (dtw < dlmw){		//下限ﾘﾐｯﾀ
////			dtw = dlmw;
////		}
////		lenw = ulmw - dlmw;							//
////		pvdot = ((dtw-dlmw) * (pvGRAPH_YSIZE-1)) / lenw;	//pv * ysize(max287dot) / ysize(max荷重)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].kajyuR = ydot;		//ydot位置保存
////		ybak = WAVE_TRND_DOT[poi_old].kajyuR;		//ydot前回位置

		s_ulml = (short)SV_WAVE_SCL4U;						//ｸﾞﾗﾌの上限＝最大荷重合計
		s_dlml = (short)SV_WAVE_SCL4D;						//ｸﾞﾗﾌの下限
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].kajyuR;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}
		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].kajyuR = ydot;		//ydot位置保存
		ybak = WAVE_TRND_DOT[poi_old].kajyuR;		//ydot前回位置

		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_PINK);

		/**************** 1ｻｲｸﾙ電力量の波形描画 ******************/	//V06
//2014/03/14
////		ulml = SV_WAVE_SCL6U;						//ｸﾞﾗﾌの上限＝電力最大
////		dlml = SV_WAVE_SCL6D;						//ｸﾞﾗﾌの下限
////		dtl = WAVE_TRND_DATA[poi_old+1].elepw;		//実測
////		if (dtl > ulml){		//上限ﾘﾐｯﾀ
////			dtl = ulml;
////		}
////		if (dtl < dlml){		//下限ﾘﾐｯﾀ
////			dtl = dlml;
////		}
////
////		if ((SEQ_PAR_103 & BIT_12) == 0)	dtl = 0;	//電力量なしなら電力量=0
////
////		lenl= ulml - dlml;							//
////		pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max電力)
////		ydot = pvGRAPH_YOPOS - pvdot;
////		WAVE_TRND_DOT[poi_old+1].elepw = ydot;		//ydot位置保存
////		ybak = WAVE_TRND_DOT[poi_old].elepw;		//ydot前回位置

		s_ulml = (long)SV_WAVE_SCL6U;						//ｸﾞﾗﾌの上限＝機械上限
		s_dlml = (long)SV_WAVE_SCL6D;					//ｸﾞﾗﾌの下限＝機械下限
		s_dtl = (short)WAVE_TRND_DATA[poi_old+1].elepw;		//実測
		if (s_dtl > s_ulml){		//上限ﾘﾐｯﾀ
			s_dtl = s_ulml;
		}
		if (s_dtl < s_dlml){		//下限ﾘﾐｯﾀ
			s_dtl = s_dlml;
		}

		if ((SEQ_PAR_103 & BIT_12) == 0)	s_dtl = 0;	//電力量なしなら電力量=0

		s_lenl = s_ulml - s_dlml;							//
		pvdot = ((s_dtl-s_dlml) * (pvGRAPH_YSIZE-1)) / s_lenl;		//pv * ysize(max287dot) / ysize(max)
		ydot = pvGRAPH_YOPOS - pvdot;
		WAVE_TRND_DOT[poi_old+1].elepw = ydot;		//ydot位置保存
		ybak = WAVE_TRND_DOT[poi_old].elepw;		//ydot前回位置
    
		Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_ORANGE);

		/**************** 上限検出位置の波形描画 ******************/
		if ( (SEQ_PAR_113 & cBIT5) == 0 ) {				//V06p 条件追加
			ulml = SV_WAVE_SCL3U;						//ｸﾞﾗﾌの上限＝機械上限
			dlml = SV_WAVE_SCL3D;						//ｸﾞﾗﾌの下限＝機械下限
			dtl = SV_TRDCSR_RNAU;						//実測
			if (dtl > ulml){		//上限ﾘﾐｯﾀ
				dtl = ulml;
			}
			if (dtl < dlml){		//下限ﾘﾐｯﾀ
				dtl = dlml;
			}
			lenl = ulml - dlml;							//
			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_TRND_DOT[poi_old+1].rnaupl = ydot;		//ydot位置保存
			ybak = WAVE_TRND_DOT[poi_old].rnaupl;		//ydot前回位置

			Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_RED);
		}

		/**************** 下限検出位置の波形描画 ******************/
		if ( (SEQ_PAR_113 & cBIT5) == 0 ) {				//V06p 条件追加
			ulml = SV_WAVE_SCL3U;						//ｸﾞﾗﾌの上限＝機械上限
			dlml = SV_WAVE_SCL3D;						//ｸﾞﾗﾌの下限＝機械下限
			dtl = SV_TRDCSR_RNAD;						//実測
			if (dtl > ulml){		//上限ﾘﾐｯﾀ
				dtl = ulml;
			}
			if (dtl < dlml){		//下限ﾘﾐｯﾀ
				dtl = dlml;
			}
			lenl = ulml - dlml;							//
			pvdot = ((dtl-dlml) * (pvGRAPH_YSIZE-1)) / lenl;	//pv * ysize(max287dot) / ysize(max)
			ydot = pvGRAPH_YOPOS - pvdot;
			WAVE_TRND_DOT[poi_old+1].rnadnl = ydot;		//ydot位置保存
			ybak = WAVE_TRND_DOT[poi_old].rnadnl;		//ydot前回位置

			Dsp_Pv_Wave(dpoi_o, ydot, ybak, COL_RED);
		}
	}

	WAVE_TRND_DTP[1] = poi_new;
}


/*
********************************************************************************
*  Module Name:		Dsp_Pv_Wave
*  Function Name:	実測波形斜め線(直線補間)描画
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_Pv_Wave(UNs poi_old, UNs ydot, UNs ybak, UNs col)
{
	UNs		ydiff, xdot;
	UNs		i;

	if (poi_old == 0)							//波形描き始め
	{
		xdot = pvGRAPH_XOPOS + poi_old;
		LCD_VRAM[ydot][xdot] = col;					//青波形
	}

	else if (ybak >= ydot)
	{
		/* 斜め上線 */
		ydiff = ybak - ydot;
//		if (ydiff < 2)							//前回とのdot差が2ﾄﾞｯﾄ未満？  未満なら直線補間は不要
//		{
//			xdot = pvGRAPH_XOPOS + poi_old;
//			LCD_VRAM[ydot][xdot] = col;					//青波形
//		}
//		else
//		{
			//斜め上に直線補間
			ydiff = ydiff / 2;
			xdot = pvGRAPH_XOPOS + poi_old;
			for (i=0; i<ydiff; i++)
			{
				LCD_VRAM[ybak-1][xdot-1] = col;			//青波形
				ybak--;
			}
			for ( ; ybak>=ydot; ybak--)
			{
				LCD_VRAM[ybak][xdot] = col;				//青波形
			}
//		}
	}
	else
	{
		/* 斜め下線 */
		ydiff = ydot - ybak;
//		if (ydiff < 2)							//前回とのdot差が2ﾄﾞｯﾄ未満？  未満なら直線補間は不要
//		{
//			xdot = pvGRAPH_XOPOS + poi_old;
//			LCD_VRAM[ydot][xdot] = col;					//青波形
//		}
//		else
//		{
			//斜め下に直線補間
			ydiff = ydiff / 2;
			xdot = pvGRAPH_XOPOS + poi_old;
			for (i=0; i<ydiff; i++)
			{
				LCD_VRAM[ybak+1][xdot-1] = col;			//青波形
				ybak++;
			}
			for ( ; ybak<=ydot; ybak++)
			{
				LCD_VRAM[ybak][xdot] = col;				//青波形
			}
//		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_PvSamp_Csr
*  Function Name:	実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面のｶｰｿﾙ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
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


	if ( csr_n <= WAVE_SAMP_DTP[0])		//ｶｰｿﾙ位置にﾃﾞｰﾀはあるか？
	{
//2014/03/14
////		PV0_SMPCSR_KJT  = WAVE_SAMP_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
////		PV0_SMPCSR_KJL  = WAVE_SAMP_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
////		PV0_SMPCSR_KJR  = WAVE_SAMP_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_2;
			PV0_SMPCSR_KJT  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_2;
			PV0_SMPCSR_KJT  = dat * -1;
		}

		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_3;
			PV0_SMPCSR_KJL  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_3;
			PV0_SMPCSR_KJL  = dat * -1;
		}

		dat = (short)WAVE_SAMP_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_4;
			PV0_SMPCSR_KJR  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_4;
			PV0_SMPCSR_KJR  = dat * -1;
		}

		PV0_SMPCSR_AGL  = WAVE_SAMP_DATA[csr_n].angle;			//ｶｰｿﾙ位置の角度
		PV0_SMPCSR_RNA1 = WAVE_SAMP_DATA[csr_n].renia1;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
		PV0_SMPCSR_RNA2 = WAVE_SAMP_DATA[csr_n].renia2;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置

		if (WAVE_SAMP_DATA[csr_n].seq & BIT_0) {
			PV0_SMPCSR_SEQ0 = 1;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		}else{
			PV0_SMPCSR_SEQ0 = 0;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		}
		if (WAVE_SAMP_DATA[csr_n].seq & BIT_1) {
			PV0_SMPCSR_SEQ1 = 1;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		}else{
			PV0_SMPCSR_SEQ1 = 0;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		}
//V06a		PV0_SMPCSR_EP = WAVE_SAMP_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の瞬時電力	V06
//2014/03/14
////		PV0_SMPCSR_EP_SIN = (int)WAVE_SAMP_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の瞬時電力
////		if(PV0_SMPCSR_EP_SIN < 0)
////		{
////			PV0_SMPCSR_EP = (UNs)(PV0_SMPCSR_EP_SIN * -1);				//ｶｰｿﾙ位置の瞬時電力
////		}
////		else
////		{
////			PV0_SMPCSR_EP = WAVE_SAMP_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の瞬時電力
////		}

		datL = (long)WAVE_SAMP_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の瞬時電力
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
		PV0_SMPCSR_KJT  = 0;		//ｶｰｿﾙ位置の合計荷重
		PV0_SMPCSR_KJL  = 0;		//ｶｰｿﾙ位置の左荷重
		PV0_SMPCSR_KJR  = 0;		//ｶｰｿﾙ位置の右荷重
		PV0_SMPCSR_AGL  = 0;		//ｶｰｿﾙ位置の角度
		PV0_SMPCSR_RNA1 = 0;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
		PV0_SMPCSR_RNA2 = 0;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
		PV0_SMPCSR_SEQ0 = 0;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		PV0_SMPCSR_SEQ1 = 0;		//ｶｰｿﾙ位置のｼｰｹﾝｽ
		PV0_SMPCSR_EP   = 0;		//ｶｰｿﾙ位置の瞬時電力	V06

		PV0_EPMDAT_SIN &= ~(BIT_1+BIT_2+BIT_3+BIT_4);		//2014/03/14
	}
//2014/09/09
////	PV0_SMPCSR_TIM  = SV_SMPCYC_TIM * csr_n;				//ｶｰｿﾙ位置の時間
	PV0_SMPCSR_TIM  = SV_SMPCYC_TIM2 * csr_n;				//ｶｰｿﾙ位置の時間
	PV0_SMPCSR_POS  = csr_n;								//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ


	if (csr_n == csr_o)			return;

	CSR_PVSAMP[1] = csr_n;					//新ｶｰｿﾙ位置保存

	/* 前の位置をｽﾍﾟｰｽで消す */
	xdot = csr_o + 7;
	csr_mark = 0x8140;//ｽﾍﾟｰｽ	S-JISｺｰﾄﾞ
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
	
	/* 今の位置を表示 */
	xdot = csr_n + 7;
	csr_mark = 0x81A5;//▼		S-JISｺｰﾄﾞ
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
*  Function Name:	実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面のｶｰｿﾙ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvTrnd_Csr(void)
{
	UNs		csr_n, csr_o, xdot;
	UNs		csr_mark;
	UNs		i;
	short	dat;
	long	datL;

	/***** カーソル位置の実測値作成 *****/
	csr_n = WAVE_TRND_DTP[0];							//現在ﾎﾟｲﾝﾀ位置
	csr_n = (csr_n-1)/500;								//前回ﾎﾟｲﾝﾀ位置の表示エリア
	if (csr_n >= SV_WAVE_PAGE)
	{
		csr_n = CSR_PVTRND[0]+((csr_n-SV_WAVE_PAGE)*500);	
	}
	else
	{
		csr_n = CSR_PVTRND[0]+((10-(SV_WAVE_PAGE-csr_n))*500);	
	}

	if (SV_WAVE_PAGE == 0) {
		if ( CSR_PVTRND[0] <= (WAVE_TRND_DTP[0]%500) )		//ｶｰｿﾙ位置にﾃﾞｰﾀはあるか？
		{
//2014/03/14
////			PV0_TRDCSR_KJT  = WAVE_TRND_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
////			PV0_TRDCSR_KJL  = WAVE_TRND_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
////			PV0_TRDCSR_KJR  = WAVE_TRND_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
			dat = (short)WAVE_TRND_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_5;
				PV0_TRDCSR_KJT  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_5;
				PV0_TRDCSR_KJT  = dat * -1;
			}

			dat = (short)WAVE_TRND_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_6;
				PV0_TRDCSR_KJL  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_6;
				PV0_TRDCSR_KJL  = dat * -1;
			}

			dat = (short)WAVE_TRND_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
			if (dat >= 0) {
				PV0_EPMDAT_SIN &= ~BIT_7;
				PV0_TRDCSR_KJR  = dat;
			}
			else {
				PV0_EPMDAT_SIN |= BIT_7;
				PV0_TRDCSR_KJR  = dat * -1;
			}

			PV0_TRDCSR_RNA1 = WAVE_TRND_DATA[csr_n].renia1;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
			PV0_TRDCSR_RNA2 = WAVE_TRND_DATA[csr_n].renia2;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置

//2014/03/14
////			PV0_TRDCSR_EP   = WAVE_TRND_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の1ｻｲｸﾙ電力量		V06
			datL = (short)WAVE_TRND_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の瞬時電力
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
			PV0_TRDCSR_KJT  = 0;		//ｶｰｿﾙ位置の合計荷重
			PV0_TRDCSR_KJL  = 0;		//ｶｰｿﾙ位置の左荷重
			PV0_TRDCSR_KJR  = 0;		//ｶｰｿﾙ位置の右荷重
			PV0_TRDCSR_RNA1 = 0;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
			PV0_TRDCSR_RNA2 = 0;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
			PV0_TRDCSR_EP   = 0;		//ｶｰｿﾙ位置の1ｻｲｸﾙ電力量		V06

			PV0_EPMDAT_SIN &= ~(BIT_5+BIT_6+BIT_7+BIT_8);
		}
	}
	else
	{
//2014/03/14
////		PV0_TRDCSR_KJT  = WAVE_TRND_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
////		PV0_TRDCSR_KJL  = WAVE_TRND_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
////		PV0_TRDCSR_KJR  = WAVE_TRND_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
		dat = (short)WAVE_TRND_DATA[csr_n].kajyuT;		//ｶｰｿﾙ位置の合計荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_5;
			PV0_TRDCSR_KJT  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_5;
			PV0_TRDCSR_KJT  = dat * -1;
		}

		dat = (short)WAVE_TRND_DATA[csr_n].kajyuL;		//ｶｰｿﾙ位置の左荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_6;
			PV0_TRDCSR_KJL  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_6;
			PV0_TRDCSR_KJL  = dat * -1;
		}

		dat = (short)WAVE_TRND_DATA[csr_n].kajyuR;		//ｶｰｿﾙ位置の右荷重
		if (dat >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_7;
			PV0_TRDCSR_KJR  = dat;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_7;
			PV0_TRDCSR_KJR  = dat * -1;
		}

		PV0_TRDCSR_RNA1 = WAVE_TRND_DATA[csr_n].renia1;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置
		PV0_TRDCSR_RNA2 = WAVE_TRND_DATA[csr_n].renia2;		//ｶｰｿﾙ位置のｽﾗｲﾄﾞ位置

//2014/03/14
////		PV0_TRDCSR_EP   = WAVE_TRND_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の1ｻｲｸﾙ電力量		V06
		datL = (short)WAVE_TRND_DATA[csr_n].elepw;		//ｶｰｿﾙ位置の1ｻｲｸﾙ電力量
		if (datL >= 0) {
			PV0_EPMDAT_SIN &= ~BIT_8;
			PV0_TRDCSR_EP  = datL;
		}
		else {
			PV0_EPMDAT_SIN |= BIT_8;
			PV0_TRDCSR_EP  = datL * -1;
		}

	}
//	PV0_TRDCSR_TIM  = SV_TRDCYC_TIM * csr_n;				//ｶｰｿﾙ位置の時間
//	PV0_TRDCSR_POS  = csr_n;								//ｶｰｿﾙ位置のﾎﾟｲﾝﾄ
	PV0_TRDCSR_POS  = CSR_PVTRND[0];						//window内のｶｰｿﾙ位置
	PV0_TRDCSR_POSL = 0;									//何入れる？
	PV0_TRDCSR_POSR = 0;									//何入れる？

	if( 0 == (SEQ_016_SV & BIT_6) ) {				//単位切替 mm/INCH 単位系(1:INCH)
		if( 0 == (SEQ_016_SV & BIT_7) ) {			//単位 高精度(1:高精度)
			PV0_TRDCSR_RNAU = SV_TRDCSR_RNAU/10;
			PV0_TRDCSR_RNAD = SV_TRDCSR_RNAD/10;
		}
	}
	else{
			PV0_TRDCSR_RNAU = SV_TRDCSR_RNAU;
			PV0_TRDCSR_RNAD = SV_TRDCSR_RNAD;
	}


	/***** カーソル位置の▼マーク表示 *****/
	csr_n = CSR_PVTRND[0];
	csr_o = CSR_PVTRND[1];

	if (csr_n == csr_o)			return;

	CSR_PVTRND[1] = csr_n;					//新ｶｰｿﾙ位置保存

	/* 前の位置をｽﾍﾟｰｽで消す */
	xdot = csr_o + 7;
	csr_mark = 0x8140;//ｽﾍﾟｰｽ	S-JISｺｰﾄﾞ
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
	
	/* 今の位置を表示 */
	xdot = csr_n + 7;
	csr_mark = 0x81A5;//▼		S-JISｺｰﾄﾞ
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
*  Function Name:	電力モニタ画面グラフ表示の初期処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2010/09			V06
********************************************************************************
*/
#define		EPM_GRAPH_ORGX			64
#define		EPM_GRAPH_ORGY			112			//96->112
#define		EPM_GRAPH_LNGX			500						//グラフＸ長さ
#define		EPM_GRAPH_LNGY			240			//256->240	//グラフＹ長さ

#define		BOGRP_ORGY				EPM_GRAPH_ORGY+EPM_GRAPH_LNGY		//左下を原点としたグラフ原点Ｙ絶対位置
#define		BOGRP_LNGX1				25						//棒グラフ間隔
#define		BOGRP_LNGX2				19						//棒グラフＸ幅

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

	EPM_TIM_BAK = SV_EPMCSR_TIM;	//単位時間
	EPM_GRP_MXL = SV_EPMGRP_MXL;	//棒グラフ最大値
	EPM_GRP_MXR = SV_EPMGRP_MXR;	//折れ線グラフ最大値

	gmin = SV_EPMCSR_TIM;					//棒ｸﾞﾗﾌ1本分の分（最大60分）
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

	if (EPM_CSR[0] == 0) {				//ｶｰｿﾙ位置0はあり得ない。（電源投入して初めての場合だけ）
		EPM_CSR[0] = 1;					//ｶｰｿﾙ位置ﾌﾟﾘｾｯﾄ
	}
	EPM_CSR[1]=0;						//ｶｰｿﾙ位置前回値強制初期化（画面切替り時に表示したいから）

	PV0_EPML_SCRH = SV_EPMGRP_MXL*10;	//電力モニタグラフ左上メモリ
	PV0_EPML_SCRM = PV0_EPML_SCRH/2;	//電力モニタグラフ左中メモリ
	PV0_EPML_SCRL = 0;					//電力モニタグラフ左下メモリ

	PV0_EPMR_SCRH = SV_EPMGRP_MXR*10;	//電力モニタグラフ右上メモリ
	PV0_EPMR_SCRM = PV0_EPMR_SCRH/2;	//電力モニタグラフ右中メモリ
	PV0_EPMR_SCRL = 0;					//電力モニタグラフ右下メモリ

	gX = EPM_GRAPH_ORGX + ((BOGRP_LNGX1-BOGRP_LNGX2) / 2);

	for (gcnt=0; gcnt<20; gcnt++)
	{
		/* 消費電力量の棒グラフ */
		gY = BOGRP_ORGY;							// 実測kWhに対する棒グラフ書き出しY位置
		wX = PV0_EPML_SCRH - PV0_EPML_SCRL;			// 長さkWh
		wY = EPM_GRAPH_LNGY;						// 長さDOT
		wP = PV0_EPM_KWH[gcnt][0];					// 実測kWh(少数点無し)
		wA = (wP * wY) / wX;						// 実測kWhに対する棒グラフ長さ
		Ylim = EPM_GRAPH_ORGY;

		Dsp_sikaku2(gX, gY, BOGRP_LNGX2, wA+1, COL_BLACK, COL_BLUE, Ylim+1);		//消費電力量の棒グラフ描画

		/* 回生電力量の棒グラフ */
		gY -= wA;									// 実測kWhに対する棒グラフ書き出しY位置
		wX = PV0_EPML_SCRH - PV0_EPML_SCRL;			// 長さkWh
		wY = EPM_GRAPH_LNGY;						// 長さDOT
		wP = PV0_EPM_KWH[gcnt][1];					// 実測kWh(少数点無し)
		wA = (wP * wY) / wX;						// 実測kWhに対する棒グラフ長さ

		Dsp_sikaku2(gX, gY, BOGRP_LNGX2, wA+1, COL_BLACK, COL_GREEN, Ylim+1);		//回生電力量の棒グラフ描画

		gX += BOGRP_LNGX1;
	}

	gX = EPM_GRAPH_ORGX + (BOGRP_LNGX1 / 2) + 1;

	for (gcnt=0; gcnt<20; gcnt++)
	{
		/* 累計の折れ線グラフ ドット */
		gY = BOGRP_ORGY;							// 実測kWhに対する棒グラフ書き出しY位置
		wX = PV0_EPMR_SCRH - PV0_EPMR_SCRL;			// 長さkWh
		wY = EPM_GRAPH_LNGY;						// 長さDOT
		wP = PV0_EPM_KWH[gcnt][2];					// 実測kWh(少数点無し)
		wA = (wP * wY) / wX;						// 実測kWhに対するdot高さ
		Ylim = EPM_GRAPH_ORGY;

		gYas = (int)gY-(int)wA;
		if (gYas < EPM_GRAPH_ORGY)
		{
			gYas = EPM_GRAPH_ORGY;
		}

		Dsp_sikaku2(gX-3-1, (UNl)gYas+3, 7, 7, COL_ORANGE, COL_ORANGE, Ylim-3);		//消費電力量の棒グラフ描画

		/* 累計の折れ線グラフ 直線補間 */
		if (gcnt<19)
		{
			wP = PV0_EPM_KWH[gcnt+1][2];			// 実測kWh(少数点無し)
			wB = (wP * wY) / wX;					// 実測kWhに対する棒グラフ長さ

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

//V06b	for (xcnt=0; xcnt<20; xcnt++)				//20本分のﾃﾞｰﾀを積算
	for (xcnt=0; xcnt<19; xcnt++)				//1本目～19本目のﾃﾞｰﾀを作成
	{
		ep1 = MON_BUF[MON_POI][0];			//消費電力量[kWs]積算
		ep2 = MON_BUF[MON_POI][1];			//回生電力量[kWs]積算

		MON_POI += 1;
//V06b		if (MON_POI>=20)	MON_POI = 0;
		if (MON_POI>=19)	MON_POI = 0;

		ep1 = ep1/3600;
		PV0_EPM_KWH[xcnt][0] = ep1;			//消費電力量[kWh]
		ep2 = ep2/3600;
		PV0_EPM_KWH[xcnt][1] = ep2;			//回生電力量[kWh]

		if (xcnt == 0)
		{
			if (EPM_TOTAL_INF == BIT_0) 
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0];	//累計(消費)
			}
			else if  (EPM_TOTAL_INF == BIT_1)
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][1];	//累計(回生)
			}
			else
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt][1];	//累計(消費＋回生)
			}
		}
		else
		{
			if (EPM_TOTAL_INF == BIT_0) 
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt-1][2];	//累計(消費)
			}
			else if  (EPM_TOTAL_INF == BIT_1)
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][1] + PV0_EPM_KWH[xcnt-1][2];	//累計(回生)
			}
			else
			{
				PV0_EPM_KWH[xcnt][2] = PV0_EPM_KWH[xcnt][0] + PV0_EPM_KWH[xcnt][1] + PV0_EPM_KWH[xcnt-1][2];	//累計(消費＋回生)
			}
		}
	}

//V06b	最初の20本目のﾃﾞｰﾀを作成
	for (xcnt=0,ep1=0,ep2=0; xcnt<ADD_POI; xcnt++)
	{
		ep1 += ADD_BUF[0][0];			//消費電力量[kWs]積算
		ep2 += ADD_BUF[0][1];			//回生電力量[kWs]積算
	}
	ep1 = ep1/3600;
	PV0_EPM_KWH[19][0] = ep1;			//消費電力量[kWh]
	ep2 = ep2/3600;
	PV0_EPM_KWH[19][1] = ep2;			//回生電力量[kWh]

	if (EPM_TOTAL_INF == BIT_0) 
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][0] + PV0_EPM_KWH[19-1][2];	//累計(消費)
	}
	else if  (EPM_TOTAL_INF == BIT_1)
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][1] + PV0_EPM_KWH[19-1][2];	//累計(回生)
	}
	else
	{
		PV0_EPM_KWH[19][2] = PV0_EPM_KWH[19][0] + PV0_EPM_KWH[19][1] + PV0_EPM_KWH[19-1][2];	//累計(消費＋回生)
	}

}

/*
********************************************************************************
*  Module Name:		Dsp_EPM_GRAPH
*  Function Name:	電力モニタグラフ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08				V06
********************************************************************************
*/
void	Dsp_EPM_GRAPH(void)
{
	if ( (EPM_TIM_BAK != SV_EPMCSR_TIM) ||		//単位時間変わった？
		 (EPM_GRP_MXL != SV_EPMGRP_MXL) ||		//棒グラフ最大値変わった？
		 (EPM_GRP_MXR != SV_EPMGRP_MXR) ||		//折れ線グラフ最大値変わった？
		 (EPM_GAMEN_RIF == 1) )					//再描画指令？
	{
		/* 再描画 */
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
*  Function Name:	実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面のｶｰｿﾙ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08				V06
********************************************************************************
*/
void	Dsp_EPM_Csr(void)
{
	UNs		csr_n, csr_o, xdot;
	UNs		csr_mark;
	UNs		wkt;

	/***** カーソル位置の実測値作成 *****/
	PV0_EPMCSR_UEP = PV0_EPM_KWH[EPM_CSR[0]-1][0];	//電力モニタカーソル位置の消費電力量
	PV0_EPMCSR_KEP = PV0_EPM_KWH[EPM_CSR[0]-1][1];	//電力モニタカーソル位置の回生電力量
	PV0_EPMCSR_TEP = PV0_EPM_KWH[EPM_CSR[0]-1][2];	//電力モニタカーソル位置の累計値

	wkt = SV_EPMCSR_TIM * (20 - EPM_CSR[0]);
	PV0_EPMCSR_HOR = wkt / 60;						//電力モニタカーソル位置の時間
	PV0_EPMCSR_MIN = wkt % 60;						//電力モニタカーソル位置の分

	/***** カーソル位置の▲マーク表示 *****/
	csr_n = EPM_CSR[0];
	csr_o = EPM_CSR[1];

	if (csr_n == csr_o)			return;

	EPM_CSR[1] = csr_n;					//新ｶｰｿﾙ位置保存

	/* 前の位置をｽﾍﾟｰｽで消す */
	if (csr_o != 0) 
	{
		xdot = ((csr_o-1) * BOGRP_LNGX1) + (EPM_GRAPH_ORGX+(BOGRP_LNGX1/2)-8);
		csr_mark = 0x8140;//ｽﾍﾟｰｽ	S-JISｺｰﾄﾞ
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
	
	/* 今の位置を表示 */
	if (csr_n >= 1) 
	{
		xdot = ((csr_n-1) * BOGRP_LNGX1) + (EPM_GRAPH_ORGX+(BOGRP_LNGX1/2)-8);
		csr_mark = 0x81A3;//▲		S-JISｺｰﾄﾞ
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
/*	電力モニタ累計値切替表示	(消費)/(回生)/(合計)	3ノッチ				*/
/*																			*/
/*		EPM_TOTAL_INF		：	3ノッチ情報									*/
/*																			*/
/****************************************************************************/
void	EPM_TOTAL_DISP	(void)
{
	UNs		i;
	UNs		chk;
	UNs		mode;
	UNl		adr;
	UNs		*hrom;

	mode = EPM_TOTAL_INF;							/* ﾓｰﾄﾞSW読込			*/
	chk  = 0x0001;

	for (i=0; i<3; i++){							/* ﾋﾞｯﾄﾁｪｯｸ				*/
		if ((mode & chk) != 0x0000)		break;		/* 検索OK				*/
		chk = (chk << 1);							/* 1ﾋﾞｯﾄｼﾌﾄ				*/
	}												/*						*/

	if (EPM_TLINF_BAK == i)				return;
	EPM_TLINF_BAK = i;

	adr =  CHR_TABLE_ADR + ((i+413-1) * CHAR_MOJI_SIZE);	// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
	hrom = (UNs *)adr;
	hrom++;
	disp_moji_s_color(
		6, 					/* ｷｬﾗｸ長			*/
		544, 				/* 書出しX位置		*/
		48, 				/* 書出しY位置		*/
		COL_BLACK,			/* 文字色			*/
		COL_ORANGE,			/* 背景色			*/
		0x0101, 			/* 文字ｻｲｽﾞ			*/
		hrom, 				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
		LCD_VRAM			/* 表示ﾒﾓﾘ			*/
		);
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

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
		/**************** ﾘﾆｱ1の波形描画 ******************/
		WAVE_SAMP_DATA[poi].renia1 = WAVE_SAMP_DATA[poi-1].renia1 +1000;		//+1.000mm

		/**************** 角度の波形描画 ******************/
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

		/**************** 荷重の波形描画 ******************/
		WAVE_SAMP_DATA[poi].kajyuL = (short)WAVE_SAMP_DATA[poi-1].kajyuL +20;
		if ((short)WAVE_SAMP_DATA[poi].kajyuL > 1000) {
			WAVE_SAMP_DATA[poi].kajyuL = -1000;
		}
		WAVE_SAMP_DATA[poi].kajyuR = (short)WAVE_SAMP_DATA[poi-1].kajyuR +40;
		if ((short)WAVE_SAMP_DATA[poi].kajyuR > 1000) {
			WAVE_SAMP_DATA[poi].kajyuR = 0;
		}
		WAVE_SAMP_DATA[poi].kajyuT = (short)WAVE_SAMP_DATA[poi].kajyuL + (short)WAVE_SAMP_DATA[poi].kajyuR;

		/**************** 瞬時電力の波形描画 ******************/
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
		/**************** ﾘﾆｱ1の波形描画 ******************/
		WAVE_TRND_DATA[poi].renia1 = WAVE_TRND_DATA[poi-1].renia1 +100;			//+0.100mm

		/**************** 荷重の波形描画 ******************/
		WAVE_TRND_DATA[poi].kajyuL = (short)WAVE_TRND_DATA[poi-1].kajyuL +10;
		if ((short)WAVE_TRND_DATA[poi].kajyuL > 1000) {
			WAVE_TRND_DATA[poi].kajyuL = -1000;
		}
		WAVE_TRND_DATA[poi].kajyuR = (short)WAVE_TRND_DATA[poi-1].kajyuR +20;
		if ((short)WAVE_TRND_DATA[poi].kajyuR > 1000) {
			WAVE_TRND_DATA[poi].kajyuR = -1000;
		}
		WAVE_TRND_DATA[poi].kajyuT = (short)WAVE_TRND_DATA[poi].kajyuL + (short)WAVE_TRND_DATA[poi].kajyuR;

		/**************** 1ｻｲｸﾙ電力量の波形描画 ******************/
		WAVE_TRND_DATA[poi].elepw = (short)WAVE_TRND_DATA[poi-1].elepw +100;
		if ((short)WAVE_TRND_DATA[poi].elepw > 10000) {
			WAVE_TRND_DATA[poi].elepw = -5000;
		}
	}
}


/*
********************************************************************************
*  Module Name:		Dsp_PvWave_5ms
*  Function Name:	実測波形描画5ms割込み処理
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura	ON:2009/08
********************************************************************************
*/
void	Dsp_PvWave_5ms(void)
{
	UNs	wk1[5];
	UNs	*poiwk, poimx;

//V06	if( (GAMEN_NO==9) || (GAMEN_NO==10) )
	if( (GAMEN_NO==9) || (GAMEN_NO==10) || (GAMEN_NO==102) )
	{
		wk1[0] = Key_Data_No[0] ^ PW_Key_last[0];	/* key状態の変化を検出	*/
		wk1[1] = Key_Data_No[1] ^ PW_Key_last[1];
		wk1[2] = Key_Data_No[2] ^ PW_Key_last[2];
		wk1[3] = Key_Data_No[3] ^ PW_Key_last[3];

		PW_Key_up[0] = wk1[0] & Key_Data_No[0];		/* 立ち上がりデータ格納 */
		PW_Key_up[1] = wk1[1] & Key_Data_No[1];		/* 立ち上がりデータ格納 */
		PW_Key_up[2] = wk1[2] & Key_Data_No[2];		/* 立ち上がりデータ格納 */
		PW_Key_up[3] = wk1[3] & Key_Data_No[3];		/* 立ち上がりデータ格納 */

		PW_Key_dn[0] = wk1[0] & PW_Key_last[0];		/* 立ち下がりデータ格納 */
		PW_Key_dn[1] = wk1[1] & PW_Key_last[1];		/* 立ち下がりデータ格納 */
		PW_Key_dn[2] = wk1[2] & PW_Key_last[2];		/* 立ち下がりデータ格納 */
		PW_Key_dn[3] = wk1[3] & PW_Key_last[3];		/* 立ち下がりデータ格納 */

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

		if ( PW_Key_up[2] & 0x0004 )					/* ＳＷ５　ＫＥＹ  左移動 */
		{
			if (*poiwk > 1)
			{
				(*poiwk)--;
			}
			PW_Key_tim02[0] = 0;						//0.2sec計測用		5ms毎にｶｳﾝﾄ   40ｶｳﾝﾄで0.2秒
			PW_Key_tim30[0] = 0;						//3.0sec計測用		5ms毎にｶｳﾝﾄ  600ｶｳﾝﾄで3.0秒
		}

		else if( PW_Key_up[1] & 0x0004 )				/* ＳＷ６　ＫＥＹ  右移動 */
		{
			if (*poiwk < poimx)
			{
				(*poiwk)++;
			}
			PW_Key_tim02[1] = 0;						//0.2sec計測用		5ms毎にｶｳﾝﾄ   40ｶｳﾝﾄで0.2秒
			PW_Key_tim30[1] = 0;						//3.0sec計測用		5ms毎にｶｳﾝﾄ  600ｶｳﾝﾄで3.0秒
		}

		if (PW_Key_tim02[0]>=40)					/* 押し０．２秒  左移動 */
		{
			PW_Key_tim02[0] = 0;
			if (PW_Key_tim30[0]>=600)				//長押し３秒以上？
			{
				if (*poiwk >= 11)
				{
					*poiwk = *poiwk - 10;		//10づつ減少
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
					(*poiwk)--;						//1づつ減少
				}
			}
		}

		else if (PW_Key_tim02[1]>=40)					/* 押し０．２秒  右移 */
		{
			PW_Key_tim02[1] = 0;
			if (PW_Key_tim30[1]>=600)					//長押し３秒以上？
			{
				if (*poiwk <= (poimx-10))
				{
					*poiwk = *poiwk + 10;		//10づつ増加
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
					(*poiwk)++;						//１づつ増加
				}
			}
		}


		if (Key_Data_No[2] & 0x0004) {
			if (PW_Key_tim02[0]<1000) {
				PW_Key_tim02[0]++;						//0.2sec計測用		5ms毎にｶｳﾝﾄ   40ｶｳﾝﾄで0.2秒
			}
			if (PW_Key_tim30[0]<1000) {
				PW_Key_tim30[0]++;						//3.0sec計測用		5ms毎にｶｳﾝﾄ  600ｶｳﾝﾄで3.0秒
			}
		}
		else if (Key_Data_No[1] & 0x0004) {
			if (PW_Key_tim02[1]<1000) {
				PW_Key_tim02[1]++;						//0.2sec計測用		5ms毎にｶｳﾝﾄ   40ｶｳﾝﾄで0.2秒
			}
			if (PW_Key_tim30[1]<1000) {
				PW_Key_tim30[1]++;						//3.0sec計測用		5ms毎にｶｳﾝﾄ  600ｶｳﾝﾄで3.0秒
			}
		}
		
	}


//debug	Pv_Graph_Deb();

}


