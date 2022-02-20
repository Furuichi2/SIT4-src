//	***********************************
//	***				***
//	***	SH4:4Kbyte		***
//	***				***
//	***				***
//	***********************************
//	高速化
//	***********************************
//	***	シーケンス		***
//	***********************************
	U2b	SQ_CBWK_TOP[70];		//

//	***************************
//	***	ハード入出力 	***
//	***************************
	U2b	di1_cb_ctl1[4];//+0:DI(使用)+1　+2()　+3(生) 運転釦(200.*)
	U2b	di2_cb_ctl2[4];//+0:DI(使用)+1　+2()　+3(生) LSA,WT1~3(201.*)
	U2b	di3_cb_inp1;//+0:EMG1,EMG2 BIT1,BIT0
	U2b	di4_cb_inp2;//+0:BIT10,BIT11,BIT12,BIT13(202.*)
	U2b	dq1_cb_out1;//+0:制御出力(203)

	U2b	di3_cb_inp1_dt;//制御に使用するのは_dt(相手側の遮光も)

	U2b	di1_cb_ctl1_dt;// ﾚﾍﾞﾙﾃﾞ-ﾀ
	U2b	di1_cb_ctl1_on;// onｴｯｼﾞ
	U2b	di1_cb_ctl1_of;// ofｴｯｼﾞ

	U2b	di2_cb_ctl2_dt;// 
	U2b	di2_cb_ctl2_on;// onｴｯｼﾞ
	U2b	di2_cb_ctl2_of;// ofｴｯｼﾞ
	
	U2b	CNT_STOP_CMD;//連続停止,ﾛｯﾄｶｳﾝﾀ,設定異常

//	***********************************
//	***	C/B　入力の加工処理	***
//	***	DI_LOAD			***
//	***********************************
	U2b	BTTN_FLG;	//BIT0:両手ﾌﾘ- BIT1:片手ON　BIT2:両手ON
	U2b	SFTY_IN_DAT;	//安全装置入力 BIT0:前安全　BIT1:後安全装置
				//[CPUA+CPUB]+安全装置有効/無効のみFACT,RACT
	U2b	SFTY_CTL_IN_DAT;

//	***************************
//	***	異常関係	***
//	***************************
	U2b	pass_err_flg1;//異常ﾙｰﾁﾝ
	U2b	pass_err_flg2;//制御ﾙｰﾁﾝ
	U2b	emg_lev_flg;//異常状態(生ﾃﾞｰﾀ)
	U2b	emg_err_flg;//異常ﾗｯﾁ
	U2b	exq_lev_flg;//急停止状態(生ﾃﾞｰﾀ)
	U2b	exq_err_flg;//exqﾗｯﾁ
	U2b	INPUT_MODE_SW;
	U2b	ELSE_ERR_FLG1;//非常停止(異常で1　正常で0)
	U2b	ELSE_ERR_FLG2;//BIT0:ﾓｰﾄﾞSW変更
	U2b	MOV_ERR_FLG1;//BIT0~BIT8

	U2b	CMP_ERR_TIM1;//二重回路異常
	U2b	MOV_DATA_ERR_FLG1;//反転時のﾃﾞｰﾀ異常
	U2b	CMP_STEP_ERR_TIM1;//工程二重回路

	U2b	ORG_ELSE_NOMAL_FLG1;//原点動作以外動作禁止 0:異常 1:OK
	U2b	ORG_DND_NOMAL_FLG1;//0:異常 1:正常(段取寸動可能)

//	***************************
//	***	リセット関係	***
//	***************************
	U2b	reset_flg;//
	U2b	reset_dly_tim;//20msec
	U2b	ORG_PRESET_TIM;

//	***********************************
//	***	ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ		***
//	***********************************
	U4b	STOPPING_VLVOFF_POS[2];//停止処理開始時点の位置
	U4b	STOPPING_STOP_POS[2];//停止処理測定位置
	U2b	STOPPING_TIM_FLG;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ用ﾌﾗｸﾞ BIT0測定開始 BIT6:停止中
	U2b	STOPPING_STOP_TIM;//停止を測定するタイマ
	U2b	STOPPING_TIM_PV1;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ
	U2b	STOPPING_TIM_PV2;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ


//	***********************************
//	***	ﾛｯﾄｶｳﾝﾀ処理		***
//	***********************************
//	最終工程で且つ165度より上(回転ならPV≧165 反転なら165≧PV)なら
//	ﾛｯﾄｶｳﾝﾀは連続・安一・ｵﾌﾟｼｮﾝでカウント
	U2b	LOT_CNT_FLG;//行程=1で0 最終工程で条件成立で=1()
	U2b	LOT_CNT_TO_MOD;
	U2b	LOT_CHK_FLG;
//	***********************************
//	***	C/B　RDY時の処理	***
//	***********************************
	U2b	DRV_ACT_FLG;	//運転動作ﾌﾗｸﾞ BIT0:運転中
	U2b	SAME_TIM;	//運転同時釦
	U2b	SET_UP_TIM;	//ｾｯﾄｱｯﾌﾟ

//	***************************
//	***	C/Bﾓｰﾄﾞ情報	***
//	***************************
	U2b	INP_MODE;	//入力　ﾘｾｯﾄ条件に使用 INP_MODE-->MODE_SEL
	U2b	MODE_SEL;	//ﾘｾｯﾄ時に決定
				//bit0:切 bit1寸動 bit2:安一(sgl,opt) bit3:連続 bit4:opt bit5:段取 bit6:待機点復帰
				//まずbit0~bit7のいずれかがonする　選択未は切(bit0)
				//bit8~bit15:詳細情報
				//optならbit8:一工程 bit9:連続寸動　bit10=連寸一
				//寸動ならbit8:寸一 
				//連続ならbit8 time,bit9 cnt
				//
	U2b	MRTION_SEL;	//回転/反転/往復上/往復下(起動時またはRESET時)
				//
	U2b	IN_RDY_FLG;	//内部準備完了(ANTIと同じﾚﾍﾞﾙ)
	U2b	STOP_LATCH;	//BIT0:ｽﾄｯﾌﾟ釦
	U2b	STOP_LATCH_B;	//BIT0:ｽﾄｯﾌﾟ釦

	U2b	UP_HOLD_STEP;	//上昇ﾎｰﾙﾄﾞを監視を開始するｽﾃｯﾌﾟ
	U2b	UP_HOLD_STEP1;	//
	U2b	UP_HOLD_STEP2;	//
	U2b	UP_HOLD_DIG;	//0.1度(165.0):ﾓｰﾀ軸ｴﾝｺｰﾀﾞ角度で比較
	U2b	UP_HOLD_FLG;	//BIT0=1 上昇ﾎｰﾙﾄﾞ状態(自動可能状態):ﾓｰｼｮﾝﾓｰﾄﾞでこの信号はON/OFFする
				//BIT1=1 上昇無効指令
				//
	U2b	CAM_CTL_STEP;//ｶﾑ・上昇ﾎｰﾙﾄﾞ用
	U2b	SW_DEV_MASK_FLG;//BIT1=BIT0=0 安全装置無効  BIT1=BIT0=1 安全装置有効
	U2b	FR_CYL_MASK_FLG;//上昇無効中"1"
	U2b	END_CMD_LATCH;

//	***********************************
//	***	1msecﾒｲﾝで作成		***
//	***********************************
	S4b	LINK_NOWROT_NUM_ZR		;//回転数
	S4b	LINK_NOWROT_NUMPLS_ZR[2];	//RL_OBJ_ABSPLS/nm = 回転数相当のﾊﾟﾙｽ
	S4b	LINK_NOWROT_OFSPLS;	//余り角度
	S4b	LINK_NOWROT_OFSPLS_P;	//余り角度の＋ﾃﾞｰﾀ

	S4b	INCENC_LINK_NOWROT_NUM_ZR;//回転数
	S4b	INCENC_LINK_NOWROT_NUMPLS_ZR[2];//RL_OBJ_ABSPLS/nm = 回転数相当のﾊﾟﾙｽ
	S4b	INCENC_LINK_NOWROT_OFSPLS;	//余り角度
	S4b	INC_LINK_NOWROT_OFSPLS_P;	//余り角度 +ﾃﾞｰﾀ
	S2b	M_LINK_AREASIG;	//BIT0:待機点範囲

//	***********************************	//
//	***				***	//
//	***	待機設定範囲		***	//
//	***				***	//
//	***********************************	//
	S2b	WSVX_CLNK_UP_POS;	//ｸﾗﾝｸ設定
	S2b	WSVX_CLNK_UP_POS_UP;	//ｸﾗﾝｸ設定
	S2b	WSVX_CLNK_UP_POS_DN;	//ｸﾗﾝｸ設定
	S2b	SETX_LINK_UP_POS_UP;	//ｸﾗﾝｸ設定(範囲比較)
	S2b	SETX_LINK_UP_POS_DN;	//ｸﾗﾝｸ設定(範囲比較)


//	***********************************
//	***	1msecﾒｲﾝで作成		***
//	***********************************
	S4b	RNA_LINK_NOWROT_OFSPLS_P;	//余り角度 +ﾃﾞｰﾀ
	S4b	INC_ENC_MM_POS;//

//	***********************************
//	***	ﾘｾｯﾄ解除時に決定	***
//	***	以降			***
//	***********************************
	S4b	RESET_ROTNUM_ZR;//この時にﾘｾｯﾄが決定した
	S4b	RESET_ROTNUMPLS_ZR[2];//この時にﾘｾｯﾄが決定した

//	***********************************
//	***	位置/角度/実測		***
//	***********************************
//	***********************************
//	***	ハード入力360ｴﾝｺｰﾀﾞ 	***
//	***********************************
	U2b	ENC360_INOLD;//ﾋﾞｯﾄ化けを除いた本当の生
	U2b	ENC360_INDT;//生 BCD
	U2b	ENC360_HEX;//HEX data
	U2b	CTL_ENC360;//360.0度
	U2b	RNA_ENC360;//0~360.0
	U2b	INC_ENC360;//0~360.0
	U2b	DISP_ENC360;//0~360.0
	U2b	OBJ_ENC360;//0~360.0

//	***********************************
//	***	位置決め演算		***
//	***********************************
//	***********************************
//	***	位置決め演算		***
//	***********************************
	S2b	SETX_POS_MOD_FLG1;	//BIT0:回転-連続//BIT1:回転-寸動//BIT2:どっかで停止する運転か否か
	S2b	SETX_POS_CTL_MATH;	
	S2b	SETX_POS_STEP_MAX;	//設定+1 2~11

	S2b	CPOS_MOD_FLG1	;//BIT0:回転-連続//BIT1:回転-寸動//BIT2:どっかで停止する運転か否か
	S2b	CPOS_CTL_MATH;	
	S2b	CPOS_STEP_MAX;	//設定

//	***********************************
//	***				***
//	***	位置決め		***
//	***				***
//	***********************************
	S4b	LINK_RL_OFSET_PLS1[2];//位置ﾃﾞｰﾀ変換
	S4b	LINK_RL_OBJ_ABSPLS[2];//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)

//	***********************************
//	***				***
//	***	位置決め		***
//	***				***
//	***********************************
//	注意:8byte dataは割込で書換られるから:注意

//	==== I/F data
	S4b	LINK_SV_OBJ_ABSPLS[2];//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	S4b	LINK_SV_OBJ_SPDPLS;//目標速度
	U2b	POS_DRV_DIRECT;	//BIT0:DIR (BIT1:EQU)
					//上死点復帰では必要(どっちからはじめるか)
					//段取寸動は必要
					//往路・復路でも必要-->ｽﾃｯﾌﾟに組み込まれる
	S2b	SV_POS_CTL_STEP;	//1msec 制御上の見かけ　多分SV=

	S2b	POS_CTRL_SQ_STS;	//位置決めｽﾃｰﾀｽ

//	*********** 200usec の処理内でON/FF *********
	S2b	INT_POS_CTL_STEP;	//内部制御工程1~11
	S2b	INT_DND_CTL_STEP;	//

	S2b	INT_POS_CTL_FLAG;	//BIT0=1:ACTIVE BIT1=1:

	S2b	INT_POS_STEP_FLG;	//ｽﾃｯﾌﾟ、段取り共通
	S2b	INT_DND_STEP_FLG;	//(上死点復帰の工程管理)
	S2b	INT_CYC_DRV_STS;	//BIT0:CYCLE　END()
					//BIT6:位置決め完了
	S2b	INT_CLS_CTL_FLG;	//BIT0=1 START 起動時ｸﾘｱ
	S2b	INT_CLS_DYL_TIM;	//

	S2b	INT_DND_NEG_STEP;	//2003-01-27 _NEG_SPEC1 EQ _COMPILE_YES	;

//	===========================================
//	===		払い出しパルス算出	===
//	===========================================
	S4b	LNGTH_ADD_DATA[2];//符号付き
	S4b	LNGTH_TOTAL_OUTPLS[2];//符号つき TOTAL=TOTAL+ADD ADD_DATA<=0
	S4b	POSLSI_CMP_DATA;//CMP_DATA=CMP_DATA+|ADD_DATA| (符号なし)
	S4b	POSLSI_DELT_POS;//変化分
	S4b	INT_LINK_TOTAL_ABSPLS[2];
	S4b	LINK_PV_ABSPLS[2];//ﾊﾞｯｸﾗｯｼ補正後
	S4b	LINK_POS_OFFSET1[2];//ﾘﾆｱ原点非常停止補正
	S4b	LINK_POS_OFFSET2[2];//

	S4b	OUTPLS_MOD;
	S4b	OUTPLS_DIV;
	
	S2b	POSLSI_DRIV_SHIN;//BIT0

	S4b	POSLSI_CHK_RESTPLS;
	
	S4b	POSLSI_OUTPUT_TOTAL_PLS[2];
	S4b	POSLSI_HENSA_LATCH[2];
	
	S2b	POSLSI_CHK_CNT;//UP CNT
	S2b	POSLSI_CHK_DLT;//符号付差分
	S2b	POSLSI_CHK_STS;

//	*******************************************
//	***					***
//	***	2003-07-01			***
//	***	速度検出部			***
//	***					***
//	*******************************************

	S4b	ENCPLS_SPD_TOTAL;
	S4b	ENC_PLS_SPD;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
	S4b	ABS_ENC_PLS_SPD;// 
	S2b	ENC_PLS_SPD_DIR;// 符号 0:"+", -1:"-"
	S2b	ENCPLS_DELT;//符号付
	S2b	ENCPLS_SPD_POINT;
	S2b	ENCPLS_POINT_SEL;//10msec
	S2b	ENCPLS_1000MSEC_LAT;//1000msec/10msec=100

	S4b	OUTPLS_SPD_TOTAL;
	S4b	OUT_PLS_SPD;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
	S4b	ABS_OUT_PLS_SPD;// (MIN機能有り 1KHZ)
	S2b	OUT_PLS_SPD_DIR;// 
	S2b	OUTPLS_DELT;//符号付
	S2b	OUTPLS_SPD_POINT;
	S2b	OUTPLS_POINT_SEL;
	S2b	OUTPLS_1000MSEC_LAT;

	S2b	PV_ENC_SPD_PER;//0~110.00%
	S2b	PV_OUT_SPD_PER;//0~110.00%

	S2b	PVC_BRK_ENC_SPD;//0~110.00% MIN-LIMIT ﾌﾞﾚｰｷ異常に使用
	S2b	PVC_BRK_OUT_SPD;//0~110.00% MIN-LIMIT ﾌﾞﾚｰｷ異常に使用 %MIN 機能有り

//	***********************************
//	***	位置決めＬＳＩカウンタ	***
//	***********************************
	S4b	POS_LSI_TOTAL_PLS[2];
	S4b	POS_LSI_ABSPLS[2];
	
	S4b	POS_LSI_OFFSET1[2];//ﾊﾟﾙｽ
	S4b	POS_LSI_OFFSET2[2];//ﾘﾆｱ/原点/からくる補正
	S4b	POS_LSI_CTL_NOWPLS[2];//実測
	S2b	POS_LSI_OLDCNT;

//	======= 待機点復帰確定ﾃﾞｰﾀ ====
	S4b	RNA_ABS_ORGWORK[2];//待機点検出用ﾜｰｸ
	S4b	INC_ABS_ORGWORK[2];//ﾘﾆｱを記憶時のｲﾝｸﾘﾒﾝﾀﾙ角度


//	***********************************
//	***	ﾘﾆｱｽｹｰﾙ原点		***
//	***********************************
	S4b	RNA_POS_OFFSET1;//ﾊﾞｯｸｱｯﾌﾟ
	S4b	RNA_POS_OFFSET2;//原点設定
	S4b	RNA_ABS_POS;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
	S4b	RNA_ABS_MEMORG;//最大高さ記憶ﾃﾞｰﾀ原点だし時：原点時のﾀﾞｲﾊｲﾄ


	S4b	RNA_STLORK;//設定
	S4b	PVX_RNA_STLORK;//実測
	S4b	PVX_DAI_POS0;//基準 ﾀﾞｲﾊｲﾄ(手動調整前)
	S4b	PVX_DAI_POS1;//表示値 ﾀﾞｲﾊｲﾄ(手動調整後)
	S4b	RNA_ABS_MD_DT0;//
	S4b	RNA_ABS_MD_DT1;//
	S4b	RNA_CTL_POS0;//制御位置(旧制御値相当) 2003-01-27 追加
	S4b	RNA_CTL_POS1;//制御位置()
	S4b	PVX_DYHITO_POS;//表示
	S4b	RNA_HOS_DELT;//ﾀﾞｲﾊｲﾄ実測-ﾀﾞｲﾊｲﾄ設定 2003-01-27

	S2b	DAI_HOSEI1_FLG;//ﾀﾞｲﾊｲﾄ手動調整

//	***************************
//	***	ｼｰｹﾝｽ入出力	***
//	***************************
	U2b	CB_SEQ_SW_SEL022;//SEQ 22[仕様設定]
	U2b	CB_SEQ_SW_SEL024;//SEQ 24[仕様設定]
	U2b	CB_SEQ_SW_SEL028;//SEQ 28[ｼｽﾊﾟﾗ設定]
	U2b	CB_SEQ_SW_SEL029;//SEQ 29[ｼｽﾊﾟﾗ設定]
	U2b	CB_SEQ_CB_COM340;
	U2b	CB_SEQ_CB_SEL341;
	U2b	CB_SEQ_CB_SEL342;
	U2b	CB_SEQ_CB_COM345;//20030709
	U2b	CB_SEQ_CB_COM346;//20030524
	U2b	CB_SEQ_CB_COM347;//200500117
	U2b	CB_SEQ_CB_COM348;//20060728 DEBUG
	U2b	CB_SEQ_CB_COM349;//20100820 
	U2b	CB_SEQ_CB_COM350;//20121005
	U2b	CB_SEQ_CB_COM351;//20121005 
	U2b	CB_SEQ_CB_COM352;//20140220

//;;;;2016-04-16	U2b	ERR_CHK_SW_SEL029;//SEQ 29

//	***************************
//	***	カム		***
//	***************************
	U2b	CB_SEQ_CAM_SEL038;//入/霧 38.0~38.15
	U2b	CB_SEQ_CAM_SEL036;//入/切 36.0~36.7+常時
	U2b	CB_SEQ_CAM_SEL034;//入/切 34.0~34.8+ｴｼﾞｪｸﾀ 
	U2b	CAM_OUT_ENB1P;//出力ENB 38.0~38.15+ﾓｰﾄﾞ条件 ﾛｰﾀﾘｶﾑ
	U2b	CAM_OUT_ENB2P;//出力ENB 36.0~36.7+常時+ﾓｰﾄﾞ ﾌｨｰﾄﾞ,内部ｶﾑ
	U2b	CAM_OUT_ENB3P;//出力ENB 34.0~34.8+ｴｼﾞｪｸﾀ
	U2b	CAM_OUT_ENB3T;//出力ENB 34.0~34.8+ｴｼﾞｪｸﾀ
	U2b	CAM_POS_STEP_END_FLG1;//各工程の
	U2b	CAM_POS_STEP_END_FLG2;//各工程の

//	===================================
//	===				===
//	===	荷重計カム処理(CPUB)	===
//	===	2006-07-28		===
//	===================================
	S2b	SET1_KJSTR_STEP1;	//0,1~工程 
	S2b	SET1_KJSTR_DIG1;	//359.0
	S2b	SET1_KJEND_STEP1;	//0,1~工程
	S2b	SET1_KJEND_DIG1;	//359.0
	S2b	KJ_AREA_SIG;//BIT4:AREA-ON BIT5:END
	S2b	KJ_AREA_BT0_OLD;//2013-06-19

//	***********************************
//	***	SH2 荷重測定ソフト	***
//	***********************************
	S2b	COP_DIG_SIG_FLG;//どの方向で横切ったか
	
	S2b	COP_CB_LD_MONI_SIG;//荷重測定用信号 2003-01-31

	U2b	WPAR_COP_CNTROT_ZDG1;//
	U2b	WPAR_COP_CNTROT_ZDG2;//
	U2b	WPAR_COP_CNTROT_SDG1;//
	U2b	WPAR_COP_CNTROT_SDG2;//

	U2b	WPAR_COP_REVRSE_ZDG1;//
	U2b	WPAR_COP_REVRSE_ZDG2;//
	U2b	WPAR_COP_REVRSE_SDG1;//
	U2b	WPAR_COP_REVRSE_SDG2;//

	U2b	WPAR_COP_ZDG1;//
	U2b	WPAR_COP_ZDG2;//
	U2b	WPAR_COP_SDG1;//
	U2b	WPAR_COP_SDG2;//

//2013-06-18 未使用	U2b	COP_ENC3600;
	U2b	COP_OLD_ENC3600;

//;	*******************************************
//;	***	内部設定相当データ		***
//;	*******************************************
	U4b	LINK_MAX_SPD_PLS;	//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	U4b	SET1_UPAREA_POS1;	//待機角度(角度とﾃｰﾌﾞﾙから)
	U4b	SETX_UPAREA_PLS;	//4;待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ)
	U4b	SETX_UPAREA_RNA;	//4;待機点位置ﾘﾆｱ位置
	U2b	SETX_UPAREA_DIG;	//4;待機点位置角度
	U4b	POS_FRQ_SPDMAX;//500KHZ
	U4b	POS_LSI_SPDMAX;
	U4b	POS_LSI_SPDBAS;
	U2b	POS_LSI_SPDLAT;
	U2b	POS_LSI_ACCLT1;
	U2b	POS_LSI_ACCLT2;

	S4b	ORG_FIRST_OBJPLS;
	S4b	ORG_SECOND_OBJPLS;


//	===================================== //
	S4b	SETX_UPDN_CHK_UP_DIG	;//312.2度(上死点角度 0.1度)
	S4b	SETX_UPDN_CHK_DN_DIG	;//180.0度(下死点角度 180.0)
	S4b	SETX_UPDN_CHK_UP_PLS	;//312.2度相当のﾊﾟﾙｽ(上死点角度)
	S4b	SETX_UPDN_CHK_DN_PLS	;//180.0度相当のﾊﾟﾙｽ(下死点角度)
	

	S2b	ORGIN_END_FLG1;	//電源投入の１回ON:OFFはない

//	***********************************
//	***	設定			***
//	***********************************
	S4b	LINK_OBJROT_NUM_ZR;//今回目標とする ROTATION 番号 (次の起動時用演算時に+1する)
	S4b	LINK_OBJROT_NUMPLS_ZR[2];//同 ROTATION番号相当のﾊﾟﾙｽ    8BYTE
	S4b	LINK_PV_ENC_ABSPLS[2];//PG　絶対位置

//	S4b	LINK_POSS_PLS[2];//開始待機点ﾊﾟﾙｽ ABS 起動時
//	S4b	LINK_POSE_PLS[2];//目標待機点ﾊﾟﾙｽ ABS 起動時
	S4b	LINK_1ROT_PLS;	//1回転ﾊﾟﾙｽ(設定ﾚﾍﾞﾙ)

	S4b	SDAT_WAIT_PVTIM;
	U4b	CPOS_UPAREA_PLS;	//待機点ﾗｯﾁ

	U4b	CLS_RNA_MOST_DOWN_POS;//ﾌﾙｸﾛｰｽﾞ開始時~終了までの最下死点
	U4b	CLS_INC_MOST_DOWN_PLS;//ﾌﾙｸﾛｰｽﾞ開始時~終了までの最下死点
	U2b	CYCL_START_CNT;

//	***********************************
//	***	C/B 位置決めｲﾝﾀｰﾌｪｲｽ	***
//	***********************************
//	C/B ==> 位置決め
	U2b	MNWR_POS_CMD;	//0000,0000,0000,0000  :ﾊﾟﾙｽ払出即停止
				//BIT0:起動
				//BIT1:減速停止
				//BIT2:待機点停止ｺﾏﾝﾄﾞﾗｯﾁ(連続運転の停止ボタン時)
				//

	U2b	STR_ENC3600_DIG;	//運転開始時の360.0角度
	U2b	STR_ENC3600_DIG_LNG;	//

	U2b	DND_CALC_WORK;

//	***********************************
//	***				***
//	***	位置決め		***
//	***	ﾊﾞｯｸﾙﾌﾟ			***
//	***********************************
	S4b	M_LINK_RL_OBJ_ABSPLS[2];//MAIN用

//	===================================
//	===				===
//	===	2006-09-19		===
//	===	ｵｰﾊﾞﾗｲﾄﾞ		===
//	===				===
//	===================================
	S4b	POSCTL_SV_PLS[2];//設定位置
	S4b	POSCTL_RL_PLS[2];//ﾘｱﾙﾀｲﾑ位置

	S4b	POSCTL_SET_SPD;//目標速度(PLS/S)設定
	S4b	POSCTL_SV_SPD;//目標速度(PLS/S)ｵｰﾊﾞﾗｲﾄﾞを含む
	S4b	POSCTL_RL_SPD;//内部演算リアルタイム速度(PLS/S)

	S4b	POSCTL_SV_UP_ACC;//目標加速度((PLS/1000)/S/S)
	S4b	POSCTL_SV_DN_ACC;//目標加速度((PLS/1000)/S/S)

	S4b	POSCTL_SV_OFS_SPD;//自起動 PLS/S

	S2b	POSCTL_STEP_CMD;//0:EMG停止(速度=0) 1:起動ｺﾏﾝﾄﾞ 2:(減速停止)
	S2b	POSCTL_STEP_FLG;//0(IDLE) 1:起動 FF:END
	S2b	POSCTL_CALC_ERR;//BIT0(停止しない状態での起動),BIT1(符号)

//	--------- 速度をきちんと扱うために--------
	S4b	SET_CLS_SPDBAS_PLS;//PLS/S
	S4b	SET_SPDBAS_PLS;//PLS/S
	S4b	SET_CLSINC_SPDBAS_PLS;//PLS/S

//	***********************************
//	***				***
//	***	演算の簡略化定数	***
//	***				***
//	***********************************
	//演算簡略化の為シスパラで演算途中を作成しておく
	U4b	CALC_MEM_1REV_MUL_NROT;//1回転パルス(8192)*Ｎ回転(32)=4byte
	U4b	CALC_MEM_1REV_ML_NROT_ML36;//1回転パルス(8192)*Ｎ回転(32)*3600=4byte

//;	***************************************************
//;	***	ｻｰﾎﾞﾊﾟﾗﾒｰﾀ領域	4/2BYTE領域		***
//;	***************************************************
	U4b	SET1_INCPLS_1REV		;//	2	;PG1回転のﾊﾟﾙｽ選択
	U2b	SET1_RNADIR_SEL1		;//	2	;ﾘﾆｱｾﾝｻ極性
	U2b	SET1_INCDIR_SEL1		;//	2	;PG極性
	U2b	SET1_INCPLS_HOSN		;//	2	;PG補正N　ﾓｰﾀN回
	U2b	SET1_INCPLS_HOSM		;//	2	;PG補正M　ｸﾗﾝｸ角度M<設定0.1度>
	U2b	SETX_INCPLS_HOSM		;//1度
	U4b	SETY_INCPLS_HOSM1XX		;//1度
	U4b	SETY_INCPLS_HOSM01X		;//0.1度
	U4b	SETY_INCPLS_HOSM001		;//0.01度
	U4b	SETY_INCPLS_HOSM0001		;//0.001度
	
	U2b	SET1_MOTRPM_MAXM		;//	2	;ﾓｰﾀ最大回転数

	U2b	SETX_OUTPLS_HOSA	;//出力ﾊﾟﾙｽ補正A
	U2b	SETX_OUTPLS_HOSB	;//出力ﾊﾟﾙｽ補正B  INC*A/B-->Output pls
