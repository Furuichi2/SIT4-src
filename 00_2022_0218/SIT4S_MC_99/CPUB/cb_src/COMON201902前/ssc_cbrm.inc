//	*******************************************
//	***					***
//	***					***
//	***	ｓｒａｍ			***
//	***					***
//	*******************************************
	U2b	CB_INT_START_OK;//
	U2b	MAIN_START_OK;
	U2b	BASE_TIM010MS;
	U2b	BASE_TIM100MS;
	U2b	TABLE_ERR_FLG;
	
//	***************************
//	***	ハード入出力 	***
//	***************************
//2013-08-20[高速MEM]	U2b	di1_cb_ctl1[4];//+0:DI(使用)+1　+2()　+3(生) 運転釦(200.*)
//2013-08-20[高速MEM]	U2b	di2_cb_ctl2[4];//+0:DI(使用)+1　+2()　+3(生) LSA,WT1~3(201.*)
//2013-08-20[高速MEM]	U2b	di3_cb_inp1;//+0:EMG1,EMG2 BIT1,BIT0
//2013-08-20[高速MEM]	U2b	di4_cb_inp2;//+0:BIT10,BIT11,BIT12,BIT13(202.*)
//2013-08-20[高速MEM]	U2b	dq1_cb_out1;//+0:制御出力(203)
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	U2b	di3_cb_inp1_dt;//制御に使用するのは_dt(相手側の遮光も)
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	U2b	di1_cb_ctl1_dt;// ﾚﾍﾞﾙﾃﾞ-ﾀ
//2013-08-20[高速MEM]	U2b	di1_cb_ctl1_on;// onｴｯｼﾞ
//2013-08-20[高速MEM]	U2b	di1_cb_ctl1_of;// ofｴｯｼﾞ
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	U2b	di2_cb_ctl2_dt;// 
//2013-08-20[高速MEM]	U2b	di2_cb_ctl2_on;// onｴｯｼﾞ
//2013-08-20[高速MEM]	U2b	di2_cb_ctl2_of;// ofｴｯｼﾞ
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]	U2b	CNT_STOP_CMD;//連続停止,ﾛｯﾄｶｳﾝﾀ,設定異常
//	***********************************
//	***	設定特殊/ﾊﾝﾄﾞｼｪｲｸ 	***
//	***********************************
	U4b	CPU_SV_HAND_IN;
	U4b	CPU_SV_HAND_IN_ON;
	U4b	CPU_SV_HAND_OUT;
	U4b	OLD_RNAORG_POS1;

//	***********************************
//	***	ハード入力360ｴﾝｺｰﾀﾞ 	***
//	***********************************
//2013-08-20[高速MEM]	U2b	ENC360_INOLD;//ﾋﾞｯﾄ化けを除いた本当の生
//2013-08-20[高速MEM]	U2b	ENC360_INDT;//生 BCD
//2013-08-20[高速MEM]	U2b	ENC360_HEX;//HEX data
//2013-08-20[高速MEM]	U2b	CTL_ENC360;//360.0度
//2013-08-20[高速MEM]	U2b	RNA_ENC360;//0~360.0
//2013-08-20[高速MEM]	U2b	INC_ENC360;//0~360.0
//2013-08-20[高速MEM]	U2b	DISP_ENC360;//0~360.0
//2013-08-20[高速MEM]	U2b	OBJ_ENC360;//0~360.0



//	***********************************
//	***	ﾘﾆｱ	ERR		***
//	***********************************
	S2b	RNA_COM_ERR_CNT;//通信失敗ｶｳﾝﾀ
	S2b	RNA_COM_NML_CNT;//正常ｶｳﾝﾀ

//20060930ADD
	S2b	RNA_RESET_FLG;//RESET-BOTTON ---SET
	S2b	RNA_RESET_TIM;//1sec
	S2b	ENC_SYSRST_CMD	;//RESET・COMMAND
	S2b	ENC_TIMEXT_FLG	;//ﾀｲﾑｱｳﾄを見ない
	S2b	RNA_CMD_SND_CNT;//ｺﾏﾝﾄﾞ送信回数ｶｳﾝﾀ
	S2b	RNA_CMD_RD_CNT;//ｺﾏﾝﾄﾞ受信回数ｶｳﾝﾀ


//	***********************************
//	***	360度ｴﾝｺｰﾀﾞ	ERR	***
//	***********************************
	S2b	ENC360_BITFLW_CNT;//ﾋﾞｯﾄ化けの発生した回数
	S2b	ENC360_BITERR_CNT;//ﾋﾞｯﾄ飛びの発生した回数
	S2b	ENC360_BITNML_CNT;//正常

//	***********************************
//	***	C/B　入力の加工処理	***
//	***	DI_LOAD			***
//	***********************************
//2013-09-27[高速MEM]	U2b	BTTN_FLG;	//BIT0:両手ﾌﾘ- BIT1:片手ON　BIT2:両手ON
//2013-09-27[高速MEM]	U2b	SFTY_IN_DAT;	//安全装置入力 BIT0:前安全　BIT1:後安全装置
//2013-09-27[高速MEM]				//[CPUA+CPUB]+安全装置有効/無効のみFACT,RACT
//2013-09-27[高速MEM]	U2b	SFTY_CTL_IN_DAT;



//	***************************
//	***	異常関係	***
//	***************************
//2013-08-20[高速MEM]	U2b	pass_err_flg1;//異常ﾙｰﾁﾝ
//2013-08-20[高速MEM]	U2b	pass_err_flg2;//制御ﾙｰﾁﾝ
//2013-08-20[高速MEM]	U2b	emg_lev_flg;//異常状態(生ﾃﾞｰﾀ)
//2013-08-20[高速MEM]	U2b	emg_err_flg;//異常ﾗｯﾁ
//2013-08-20[高速MEM]	U2b	exq_lev_flg;//急停止状態(生ﾃﾞｰﾀ)
//2013-08-20[高速MEM]	U2b	exq_err_flg;//exqﾗｯﾁ
//2013-09-27[高速MEM]	U2b	INPUT_MODE_SW;
//2013-09-27[高速MEM]	U2b	ELSE_ERR_FLG1;//非常停止(異常で1　正常で0)
//2013-09-27[高速MEM]	U2b	ELSE_ERR_FLG2;//BIT0:ﾓｰﾄﾞSW変更
//2013-09-27[高速MEM]	U2b	MOV_ERR_FLG1;//BIT0~BIT8
//2013-09-27[高速MEM]	U2b	CMP_ERR_TIM1;//二重回路異常
//2013-09-27[高速MEM]	U2b	MOV_DATA_ERR_FLG1;//反転時のﾃﾞｰﾀ異常
//2013-09-27[高速MEM]	U2b	CMP_STEP_ERR_TIM1;//工程二重回路
//2013-09-27[高速MEM]	U2b	ORG_ELSE_NOMAL_FLG1;//原点動作以外動作禁止 0:異常 1:OK
//2013-09-27[高速MEM]	U2b	ORG_DND_NOMAL_FLG1;//0:異常 1:正常(段取寸動可能)

//	***************************
//	***	リセット関係	***
//	***************************
//2013-09-27[高速MEM]	U2b	reset_flg;//
//2013-09-27[高速MEM]	U2b	reset_dly_tim;//20msec
//2013-09-27[高速MEM]	U2b	ORG_PRESET_TIM;

//	***************************
//	***	ｾﾙﾌﾁｪｯｸ関係	***
//	***************************
	U2b	SELF_FLG;//BIT0:ｾﾙﾌﾁｪｯｸ中 //BIT7
	U2b	SELF_COM;//BIT0:ｾﾙﾌﾁｪｯｸ指令
	U2b	SELF_START_WAIT_TM;
	U2b	SELF_CHK_SEL;	//BIT0=0 ｾﾙﾌﾁｪｯｸしない          BIT0=1ｾﾙﾌﾁｪｯｸを行う(非常停止時)
				//BIT1=0 運転終了時ｾﾙﾌﾁｪｯｸしないBIT1=1ｾﾙﾌﾁｪｯｸを行う(運転終了時)
	
//	***************************
//	***	C/Bﾓｰﾄﾞ情報	***
//	***************************
//2013-08-20[高速MEM]	U2b	INP_MODE;	//入力　ﾘｾｯﾄ条件に使用 INP_MODE-->MODE_SEL
//2013-08-20[高速MEM]	U2b	MODE_SEL;	//ﾘｾｯﾄ時に決定
//2013-08-20[高速MEM]				//bit0:切 bit1寸動 bit2:安一(sgl,opt) bit3:連続 bit4:opt bit5:段取 bit6:待機点復帰
//2013-08-20[高速MEM]				//まずbit0~bit7のいずれかがonする　選択未は切(bit0)
//2013-08-20[高速MEM]				//bit8~bit15:詳細情報
//2013-08-20[高速MEM]				//optならbit8:一工程 bit9:連続寸動　bit10=連寸一
//2013-08-20[高速MEM]				//寸動ならbit8:寸一 
//2013-08-20[高速MEM]			//連続ならbit8 time,bit9 cnt
//2013-08-20[高速MEM]				//
//2013-08-20[高速MEM]	U2b	MRTION_SEL;	//回転/反転/往復上/往復下(起動時またはRESET時)
//2013-08-20[高速MEM]				//
//2013-08-20[高速MEM]	U2b	IN_RDY_FLG;	//内部準備完了(ANTIと同じﾚﾍﾞﾙ)
//2013-08-20[高速MEM]	U2b	STOP_LATCH;	//BIT0:ｽﾄｯﾌﾟ釦
//2013-08-20[高速MEM]	U2b	STOP_LATCH_B;	//BIT0:ｽﾄｯﾌﾟ釦
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	U2b	UP_HOLD_STEP;	//上昇ﾎｰﾙﾄﾞを監視を開始するｽﾃｯﾌﾟ
//2013-08-20[高速MEM]	U2b	UP_HOLD_STEP1;	//
//2013-08-20[高速MEM]	U2b	UP_HOLD_STEP2;	//
//2013-08-20[高速MEM]	U2b	UP_HOLD_DIG;	//0.1度(165.0):ﾓｰﾀ軸ｴﾝｺｰﾀﾞ角度で比較
//2013-08-20[高速MEM]	U2b	UP_HOLD_FLG;	//BIT0=1 上昇ﾎｰﾙﾄﾞ状態(自動可能状態):ﾓｰｼｮﾝﾓｰﾄﾞでこの信号はON/OFFする
//2013-08-20[高速MEM]				//BIT1=1 上昇無効指令
//2013-08-20[高速MEM]				//
//2013-08-20[高速MEM]	U2b	CAM_CTL_STEP;//ｶﾑ・上昇ﾎｰﾙﾄﾞ用
//2013-08-20[高速MEM]	U2b	SW_DEV_MASK_FLG;//BIT1=BIT0=0 安全装置無効  BIT1=BIT0=1 安全装置有効
//2013-08-20[高速MEM]	U2b	FR_CYL_MASK_FLG;//上昇無効中"1"
//2013-08-20[高速MEM]	U2b	END_CMD_LATCH;

//	***********************************
//	***	ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ		***
//	***********************************
//2013-09-27[高速MEM]	U4b	STOPPING_VLVOFF_POS[2];//停止処理開始時点の位置
//2013-09-27[高速MEM]	U4b	STOPPING_STOP_POS[2];//停止処理測定位置
//2013-09-27[高速MEM]	U2b	STOPPING_TIM_FLG;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ用ﾌﾗｸﾞ BIT0測定開始 BIT6:停止中
//2013-09-27[高速MEM]	U2b	STOPPING_STOP_TIM;//停止を測定するタイマ
//2013-09-27[高速MEM]	U2b	STOPPING_TIM_PV1;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ
//2013-09-27[高速MEM]	U2b	STOPPING_TIM_PV2;//ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ


//	***********************************
//	***	ﾛｯﾄｶｳﾝﾀ処理		***
//	***********************************
//	最終工程で且つ165度より上(回転ならPV≧165 反転なら165≧PV)なら
//	ﾛｯﾄｶｳﾝﾀは連続・安一・ｵﾌﾟｼｮﾝでカウント
//2013-09-27[高速MEM]	U2b	LOT_CNT_FLG;//行程=1で0 最終工程で条件成立で=1()
//2013-09-27[高速MEM]	U2b	LOT_CNT_TO_MOD;
//2013-09-27[高速MEM]	U2b	LOT_CHK_FLG;
//	***********************************
//	***	C/B　RDY時の処理	***
//	***********************************
//2013-09-27[高速MEM]	U2b	DRV_ACT_FLG;	//運転動作ﾌﾗｸﾞ BIT0:運転中
//2013-09-27[高速MEM]	U2b	SAME_TIM;	//運転同時釦
//2013-09-27[高速MEM]	U2b	SET_UP_TIM;	//ｾｯﾄｱｯﾌﾟ

//	***********************************
//	***				***
//	***	二重回路対策		***
//	***				***
//	***********************************
	U2b	CMPSTEP_CTRL_REDY;//準備完了にしたい
	U2b	CMPSTEP_CTRL_BUSY;//準備未完了にしたい
	U2b	CMPSTEP_POS_START;//起動したい
	U2b	CMPSTEP_SFTY_AUTO;//AUTOにしたい/安全一工程,連続ｶｳﾝﾀ
	U2b	CMPSTEP_NEAR_ZERO;//ﾆｱｾﾞﾛ処理を行いたい
	U2b	CMPSTEP_CNT_STOP;//連続停止
	U2b	CMPSTEP_STEP_END;//位置決め完了としたい
	U2b	NEAR_IN_FLG;



//	***********************************
//	***	1msecﾒｲﾝで作成		***
//	***********************************
//2013-09-27[高速MEM]	S4b	LINK_NOWROT_NUM_ZR		;//回転数
//2013-09-27[高速MEM]	S4b	LINK_NOWROT_NUMPLS_ZR[2];	//RL_OBJ_ABSPLS/nm = 回転数相当のﾊﾟﾙｽ
//2013-09-27[高速MEM]	S4b	LINK_NOWROT_OFSPLS;	//余り角度
//2013-09-27[高速MEM]	S4b	LINK_NOWROT_OFSPLS_P;	//余り角度の＋ﾃﾞｰﾀ

//2013-09-27[高速MEM]	S4b	INCENC_LINK_NOWROT_NUM_ZR;//回転数
//2013-09-27[高速MEM]	S4b	INCENC_LINK_NOWROT_NUMPLS_ZR[2];//RL_OBJ_ABSPLS/nm = 回転数相当のﾊﾟﾙｽ
//2013-09-27[高速MEM]	S4b	INCENC_LINK_NOWROT_OFSPLS;	//余り角度
//2013-09-27[高速MEM]	S4b	INC_LINK_NOWROT_OFSPLS_P;	//余り角度 +ﾃﾞｰﾀ
//2013-09-27[高速MEM]	S2b	M_LINK_AREASIG;	//BIT0:待機点範囲

//	***********************************	//
//	***				***	//
//	***	待機設定範囲		***	//
//	***				***	//
//	***********************************	//
//2013-09-27[高速MEM]	S2b	WSVX_CLNK_UP_POS;	//ｸﾗﾝｸ設定
//2013-09-27[高速MEM]	S2b	WSVX_CLNK_UP_POS_UP;	//ｸﾗﾝｸ設定
//2013-09-27[高速MEM]	S2b	WSVX_CLNK_UP_POS_DN;	//ｸﾗﾝｸ設定
//2013-09-27[高速MEM]	S2b	SETX_LINK_UP_POS_UP;	//ｸﾗﾝｸ設定(範囲比較)
//2013-09-27[高速MEM]	S2b	SETX_LINK_UP_POS_DN;	//ｸﾗﾝｸ設定(範囲比較)


//	***********************************
//	***	1msecﾒｲﾝで作成		***
//	***********************************
//2013-09-27[高速MEM]	S4b	RNA_LINK_NOWROT_OFSPLS_P;	//余り角度 +ﾃﾞｰﾀ
//2013-09-27[高速MEM]	S4b	INC_ENC_MM_POS;//

//	***********************************
//	***	ﾘｾｯﾄ解除時に決定	***
//	***	以降			***
//	***********************************
//2013-09-27[高速MEM]	S4b	RESET_ROTNUM_ZR;//この時にﾘｾｯﾄが決定した
//2013-09-27[高速MEM]	S4b	RESET_ROTNUMPLS_ZR[2];//この時にﾘｾｯﾄが決定した

//	***********************************
//	***	位置決め演算		***
//	***********************************
//	段取では下のｽﾃｯﾌﾟﾃﾞｰﾀは使用しない
	S4b	SETX_POS_SDAT1_OFSPOS[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	往路
	S4b	SETX_POS_SDAT1_SPD[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	往路
	S4b	SETX_POS_SDAT1_TIM[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	往路
	S4b	SETX_POS_SDAT1_CNTSTEP[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	往路
	S4b	SETX_POS_SDAT1_INF1[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	往路
	S4b	SETX_POS_SDAT2_OFSPOS[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	復路
	S4b	SETX_POS_SDAT2_INF1[100+10];	//(ﾒｲﾝｽｷｬﾝで動作停止状態で作成)	復路


//2013-08-20[高速MEM]	S2b	SETX_POS_MOD_FLG1;	//BIT0:回転-連続//BIT1:回転-寸動//BIT2:どっかで停止する運転か否か
//2013-08-20[高速MEM]	S2b	SETX_POS_CTL_MATH;	
//2013-08-20[高速MEM]	S2b	SETX_POS_STEP_MAX;	//設定+1 2~11
//

	S4b	CPOS_SDAT1_OFSPOS[100+10];		//SETX-->起動時COPY
	S4b	CPOS_SDAT1_SPD[100+10];		//SETX-->起動時COPY
	S4b	CPOS_SDAT1_TIM[100+10];		//SETX-->起動時COPY
	S4b	CPOS_SDAT1_CNTSTEP[100+10];		//SETX-->起動時COPY
	S4b	CPOS_SDAT1_INF1[100+10];		//SETX-->起動時COPY
	S4b	CPOS_SDAT1_NUM[100+10];		//起動時,その他で演算 4byte
	S4b	CPOS_SDAT1_CHGAPOS[2*(100+10)];		//起動時,その他で演算 8byte data
	S4b	CPOS_SDAT1_STPAPOS[2*(100+10)];		//起動時,その他で演算 8byte data


	S4b	CPOS_SDAT1_UP_OFSPOS;//2014-09-20 上死点 繰返に開始側の待機点も必要
	S4b	CPOS_SDAT1_UP_POS[2];//2014-09-20 上死点 繰返に開始側の待機点も必要

//2013-08-20[高速MEM]		S2b	CPOS_MOD_FLG1	;//BIT0:回転-連続//BIT1:回転-寸動//BIT2:どっかで停止する運転か否か
//2013-08-20[高速MEM]		S2b	CPOS_CTL_MATH;	
//2013-08-20[高速MEM]		S2b	CPOS_STEP_MAX;	//設定


//2013-09-27[高速MEM]	S4b	LINK_OBJROT_NUM_ZR;//今回目標とする ROTATION 番号 (次の起動時用演算時に+1する)
//2013-09-27[高速MEM]	S4b	LINK_OBJROT_NUMPLS_ZR[2];//同 ROTATION番号相当のﾊﾟﾙｽ    8BYTE
//2013-09-27[高速MEM]	S4b	LINK_PV_ENC_ABSPLS[2];//PG　絶対位置

//2013-09-27[高速MEM]	S4b	LINK_POSS_PLS[2];//開始待機点ﾊﾟﾙｽ ABS 起動時
//2013-09-27[高速MEM]	S4b	LINK_POSE_PLS[2];//目標待機点ﾊﾟﾙｽ ABS 起動時

//2013-08-20[高速MEM]	S4b	LINK_1ROT_PLS;	//1回転ﾊﾟﾙｽ(設定ﾚﾍﾞﾙ)
//2013-08-20[高速MEM]	S4b	SDAT_WAIT_PVTIM;
//2013-08-20[高速MEM]	U4b	CPOS_UPAREA_PLS;	//待機点ﾗｯﾁ

//2013-08-20[高速MEM]	U4b	CLS_RNA_MOST_DOWN_POS;//ﾌﾙｸﾛｰｽﾞ開始時~終了までの最下死点
//2013-08-20[高速MEM]	U4b	CLS_INC_MOST_DOWN_PLS;//ﾌﾙｸﾛｰｽﾞ開始時~終了までの最下死点
//2013-08-20[高速MEM]	U2b	CYCL_START_CNT;


//	***********************************
//	***	C/B 位置決めｲﾝﾀｰﾌｪｲｽ	***
//	***********************************
//2013-09-27[高速MEM]//	C/B ==> 位置決め
//2013-09-27[高速MEM]	U2b	MNWR_POS_CMD;	//0000,0000,0000,0000  :ﾊﾟﾙｽ払出即停止
//2013-09-27[高速MEM]				//BIT0:起動
//2013-09-27[高速MEM]				//BIT1:減速停止
//2013-09-27[高速MEM]				//BIT2:待機点停止ｺﾏﾝﾄﾞﾗｯﾁ(連続運転の停止ボタン時)
//2013-09-27[高速MEM]				//
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	U2b	STR_ENC3600_DIG;	//運転開始時の360.0角度
//2013-09-27[高速MEM]	U2b	STR_ENC3600_DIG_LNG;	//
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	U2b	DND_CALC_WORK;

//	***********************************
//	***				***
//	***	位置決め		***
//	***	ﾊﾞｯｸﾙﾌﾟ			***
//	***********************************
//2013-09-27[高速MEM]	S4b	M_LINK_RL_OBJ_ABSPLS[2];//MAIN用

//	***********************************
//	***				***
//	***	位置決め		***
//	***				***
//	***********************************
//2013-08-20[高速MEM]	S4b	LINK_RL_OFSET_PLS1[2];//位置ﾃﾞｰﾀ変換
//2013-08-20[高速MEM]	S4b	LINK_RL_OBJ_ABSPLS[2];//ﾘｱﾙﾀｲﾑ目標絶対位置(ﾊﾞｯｸﾗｯｼなし)

//	***********************************
//	***				***
//	***	位置決め		***
//	***				***
//	***********************************
//	注意:8byte dataは割込で書換られるから:注意

//	==== I/F data
//2013-08-20[高速MEM]	S4b	LINK_SV_OBJ_ABSPLS[2];//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
//2013-08-20[高速MEM]	S4b	LINK_SV_OBJ_SPDPLS;//目標速度
//2013-08-20[高速MEM]	U2b	POS_DRV_DIRECT;	//BIT0:DIR (BIT1:EQU)
					//上死点復帰では必要(どっちからはじめるか)
					//段取寸動は必要
					//往路・復路でも必要-->ｽﾃｯﾌﾟに組み込まれる
//2013-08-20[高速MEM]	S2b	SV_POS_CTL_STEP;	//1msec 制御上の見かけ　多分SV=
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S2b	POS_CTRL_SQ_STS;	//位置決めｽﾃｰﾀｽ

//	*********** 200usec の処理内でON/FF *********
//2013-08-20[高速MEM]	S2b	INT_POS_CTL_STEP;	//内部制御工程1~11
//2013-08-20[高速MEM]	S2b	INT_DND_CTL_STEP;	//
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S2b	INT_POS_CTL_FLAG;	//BIT0=1:ACTIVE BIT1=1:
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S2b	INT_POS_STEP_FLG;	//ｽﾃｯﾌﾟ、段取り共通
//2013-08-20[高速MEM]	S2b	INT_DND_STEP_FLG;	//(上死点復帰の工程管理)
//2013-08-20[高速MEM]	S2b	INT_CYC_DRV_STS;	//BIT0:CYCLE　END()
//2013-08-20[高速MEM]					//BIT6:位置決め完了
//2013-08-20[高速MEM]	S2b	INT_CLS_CTL_FLG;	//BIT0=1 START 起動時ｸﾘｱ
//2013-08-20[高速MEM]	S2b	INT_CLS_DYL_TIM;	//
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S2b	INT_DND_NEG_STEP;	//2003-01-27 _NEG_SPEC1 EQ _COMPILE_YES	;
//2013-08-20[高速MEM]
//	===========================================
//	===		払い出しパルス算出	===
//	===========================================
//2013-08-20[高速MEM]	S4b	LNGTH_ADD_DATA[2];//符号付き
//2013-08-20[高速MEM]	S4b	LNGTH_TOTAL_OUTPLS[2];//符号つき TOTAL=TOTAL+ADD ADD_DATA<=0
//2013-08-20[高速MEM]	S4b	POSLSI_CMP_DATA;//CMP_DATA=CMP_DATA+|ADD_DATA| (符号なし)
//2013-08-20[高速MEM]	S4b	POSLSI_DELT_POS;//変化分
//2013-08-20[高速MEM]	S4b	INT_LINK_TOTAL_ABSPLS[2];
//2013-08-20[高速MEM]	S4b	LINK_PV_ABSPLS[2];//ﾊﾞｯｸﾗｯｼ補正後
//2013-08-20[高速MEM]	S4b	LINK_POS_OFFSET1[2];//ﾘﾆｱ原点非常停止補正
//2013-08-20[高速MEM]	S4b	LINK_POS_OFFSET2[2];//
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S4b	OUTPLS_MOD;
//2013-08-20[高速MEM]	S4b	OUTPLS_DIV;
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]	S2b	POSLSI_DRIV_SHIN;//BIT0
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	S4b	POSLSI_CHK_RESTPLS;
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]	S4b	POSLSI_OUTPUT_TOTAL_PLS[2];
//2013-08-20[高速MEM]	S4b	POSLSI_HENSA_LATCH[2];
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]	S2b	POSLSI_CHK_CNT;//UP CNT
//2013-08-20[高速MEM]	S2b	POSLSI_CHK_DLT;//符号付差分
//2013-08-20[高速MEM]	S2b	POSLSI_CHK_STS;

//	***********************************
//	***	異常			***
//	***********************************
	S4b	HENSA_OVR_OUTPLS[2];//偏差ｵｰﾊﾞ用OUTPUT_LATCHdata
	S4b	HENSA_OVR_ENCPOS[2];//BIT0

	S4b	STOP_LATCH_OUTPLS[2];
	S4b	STOP_LATCH_ENCPOS[2];
	S4b	STOP_LATCH_RNAPOS[2];//BIT
	S2b	STOP_LATCH_CHK_TIM;//位置決め完了後の遅延時間

	S4b	REV_LATCH_OUTPLS[2];//偏差ｵｰﾊﾞ用OUTPUT_LATCHdata
	S4b	REV_LATCH_ENCPOS[2];
	S4b	REV_LATCH_RNAPOS[2];//

	S2b	RST_ERR_CHK_FLG;//QST=1 :00
	S2b	RST_ERR_CHK_ERR;//

	U2b	CMP_ERR_CHK_STSA;
	U2b	CMP_ERR_CHK_STSB;
	U2b	CMP_ERR_STSA_INF1;
	U2b	CMP_ERR_STSA_INF2;
	U2b	CMP_ERR_STSA_INF3;
	U2b	CMP_ERR_STSA_INF4;
	U2b	CMP_ERR_STEP_A;//
	U2b	CMP_ERR_STEP_B;//

//	***********************************
//	***				***
//	***	演算の簡略化定数	***
//	***				***
//	***********************************
	//演算簡略化の為シスパラで演算途中を作成しておく
//2013-08-20[高速MEM]	U4b	CALC_MEM_1REV_MUL_NROT;//1回転パルス(8192)*Ｎ回転(32)=4byte
//2013-08-20[高速MEM]	U4b	CALC_MEM_1REV_ML_NROT_ML36;//1回転パルス(8192)*Ｎ回転(32)*3600=4byte

//	***********************************
//	***	位置決めＬＳＩカウンタ	***
//	***********************************
//2013-08-20[高速MEM]		S4b	POS_LSI_TOTAL_PLS[2];
//2013-08-20[高速MEM]		S4b	POS_LSI_ABSPLS[2];
//2013-08-20[高速MEM]		
//2013-08-20[高速MEM]		S4b	POS_LSI_OFFSET1[2];//ﾊﾟﾙｽ
//2013-08-20[高速MEM]		S4b	POS_LSI_OFFSET2[2];//ﾘﾆｱ/原点/からくる補正
//2013-08-20[高速MEM]		S4b	POS_LSI_CTL_NOWPLS[2];//実測
//2013-08-20[高速MEM]		S2b	POS_LSI_OLDCNT;
//2013-08-20[高速MEM]	
//	======= 待機点復帰確定ﾃﾞｰﾀ ====
//2013-08-20[高速MEM]		S4b	RNA_ABS_ORGWORK[2];//待機点検出用ﾜｰｸ
//2013-08-20[高速MEM]		S4b	INC_ABS_ORGWORK[2];//ﾘﾆｱを記憶時のｲﾝｸﾘﾒﾝﾀﾙ角度

//	***********************************
//	***	ﾘﾆｱｽｹｰﾙ原点		***
//	***********************************
//2013-08-20[高速MEM]		S4b	RNA_POS_OFFSET1;//ﾊﾞｯｸｱｯﾌﾟ
//2013-08-20[高速MEM]		S4b	RNA_POS_OFFSET2;//原点設定
//2013-08-20[高速MEM]		S4b	RNA_ABS_POS;//ﾎﾞﾙｽﾀ面高さ(絶対位置)
//2013-08-20[高速MEM]		S4b	RNA_ABS_MEMORG;//最大高さ記憶ﾃﾞｰﾀ原点だし時：原点時のﾀﾞｲﾊｲﾄ
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]		S4b	RNA_STLORK;//設定
//2013-08-20[高速MEM]		S4b	PVX_RNA_STLORK;//実測
//2013-08-20[高速MEM]		S4b	PVX_DAI_POS0;//基準 ﾀﾞｲﾊｲﾄ(手動調整前)
//2013-08-20[高速MEM]		S4b	PVX_DAI_POS1;//表示値 ﾀﾞｲﾊｲﾄ(手動調整後)
//2013-08-20[高速MEM]		S4b	RNA_ABS_MD_DT0;//
//2013-08-20[高速MEM]		S4b	RNA_ABS_MD_DT1;//
//2013-08-20[高速MEM]		S4b	RNA_CTL_POS0;//制御位置(旧制御値相当) 2003-01-27 追加
//2013-08-20[高速MEM]		S4b	RNA_CTL_POS1;//制御位置()
//2013-08-20[高速MEM]		S4b	PVX_DYHITO_POS;//表示
//2013-08-20[高速MEM]		S4b	RNA_HOS_DELT;//ﾀﾞｲﾊｲﾄ実測-ﾀﾞｲﾊｲﾄ設定 2003-01-27
//2013-08-20[高速MEM]	
//2013-08-20[高速MEM]		S2b	DAI_HOSEI1_FLG;//ﾀﾞｲﾊｲﾄ手動調整

//	*******************************************
//	***	ダイハイト比較&運転時補正	***
//	*******************************************
	S4b	RNA_ABS_WKMINPOS;//ｻﾝﾌﾟﾘﾝｸﾞﾜｰｸ起動前RNA_ABS_POS
	S4b	RNA_ABS_WKMAXPOS;//ｻﾝﾌﾟﾘﾝｸﾞﾜｰｸ起動前RNA_ABS_POS
	S4b	RNA_ABS_MINPOS;//最下死点--ﾓｰﾄﾞ起動前RNA_ABS_POS
	S4b	RNA_ABS_MAXPOS;//最上死点--ﾓｰﾄﾞ起動前RNA_ABS_POS(ﾓｰｼｮﾝ運転時はﾀﾞｲﾊｲﾄ)
	S2b	DAI_CMP_SMPSTART;//BIT0:ｻﾝﾌﾟﾘﾝｸﾞ開始
						//BIT1:ｻﾝﾌﾟﾘﾝｸﾞEND

//	*******************************************
//	***	上記の方法の変更時発生WORK	***
//	*******************************************
	U2b	WPAR_DRVHOS_SEL1;//運転中の補正制御選択=0:旧 =1:下限による補正制御
	U2b	WPAR_DRVHOS_DIG1;//360ｴﾝｺｰﾀﾞ角度上 170.0度(ｻﾝﾌﾟﾘﾝｸﾞ開始可能な角度) 170~359<ｻﾝﾌﾟﾘﾝｸﾞ可>
	U2b	WPAR_DRVHOS_DIG2;//
	U2b	WPAR_DRVHOS_WAITCNT;//初回のｶｳﾝﾄ開始待ち回数
	U2b	WPAR_DRVHOS_AVLCNT;//移動平均の元データ回数
	U2b	WPAR_DRVHOS_NO_USE;//読み飛ばしデータ回数 上限側

	U2b	DRVHOS_USE_FLG;//BIT1=1,BIT0=1 補正ﾃﾞｰﾀを使用してもいい
	U2b	DRVHOS_WAIT_CNT_PV;//
	U2b	DRVHOS_DEF_CNT_PV;//移動平均回数と一致
	U2b	DRVHOS_IDO_POINT;//ﾊﾞｯﾌｧ管理ﾎﾟｲﾝﾀ
//;	==== 2003-07-14 ==
	U2b	DRVHOS_IDO_CNT;//移動平均回数をｶｳﾝﾄし1個,2個,,,でも平均を出せるようにする
//;	==================

	S4b	RNA_ABS_DRVHOS_DT;//補正ﾃﾞｰﾀ 2003-01-31
	S4b	DRVHOS_DEF_RNA_POS;//最下死点の初期値
	S4b	DRVHOS_CAL_RNA_POS;//最下死点の演算値
	S4b	DRVHOS_MOST_DN_RNAPOS;//最下死点のWORK(175~359) 175度でﾃﾞﾌｫﾙﾄを作成

	S4b	DRVHOS_IDO_TOTAL;//
	S4b	DRVHOS_IDO_BUF[100];//
	S4b	DRVHOS_WORK_BUF[100];//

	S4b	DEF_DAI_POS_PV;//2003-07-14

//	***********************************
//	***				***
//	***	荷重補正でのﾀﾞｲﾊｲﾄ補正	***
//	***				***
//	***********************************
//	2004-07-06
	S2b	KJPHOS_USE_FLG;	//BIT0=1 ｲﾆｼｬﾙ完了
				//BIT1=1 初期ﾃﾞｰﾀ作成中
				//BIT2=1 初期ｻﾝﾌﾟﾘﾝｸﾞ完了=通常ｻﾝﾌﾟﾘﾝｸﾞ中
				//BIT3
				//BIT4=1/0(測定ｴﾘｱ)
				//BIT5
				//BIT6=1 ｻﾝﾌﾟﾘﾝｸﾞ有効:回転で且つﾓｰｼｮﾝﾓｰﾄﾞ,,
				//BIT7
				//
	U2b	KJPHOS_IDO_POINT;//ﾊﾞｯﾌｧ管理ﾎﾟｲﾝﾀ
	U2b	KJPHOS_IDO_CNT;//移動平均回数をｶｳﾝﾄし1個,2個,,,でも平均を出せるようにする

	U2b	KJPHOS_WAIT_CNT_PV;	//;初期回数←_WPAR_DRVHOS_WAITCNT (BIT0=0→1時にｾｯﾄ)
	U2b	KJPHOS_DEF_CNT_PV;	//;平均回数←_WPAR_DRVHOS_AVLCNT (BIT1=0→1時にｾｯﾄ)

	S4b	KJPHOS_IDO_TOTAL;//
	S4b	KJPHOS_IDO_BUF[100];//

	S4b	KJYUU_IN_DAT_PV;//(DPRAM)2byte->4byte(WORK)
	S4b	KJYUU_DEF_DAT_PV;//4byte
	S4b	KJYUU_NEW_DAT_PV;//4byte
	S4b	KJPHOS_CAL_PRS;//ﾃﾞﾊﾞｯｸ用








//	***************************
//	***	表示用 I/F	***
//	***************************
	S4b	CYCLE_TIME_DAT;//(起動時0　ﾌﾗｸﾞON中ｶｳﾝﾄ　ﾌﾗｸﾞOFF中保持)
	S4b	CYCLE_TIME_PV;
	S2b	CYCLE_TIME_FLG;//(ﾌﾗｸﾞON)
	S2b	DISP_RE_VIEW_FLG;//非常停止解除(ｻｲｸﾙ運転),1CYCLEND,


//	***************************
//	***	ｼｰｹﾝｽ入出力	***
//	***************************
//2013-08-20[高速MEM]	U2b	CB_SEQ_SW_SEL024;//SEQ 24[仕様設定]
//2013-08-20[高速MEM]	U2b	CB_SEQ_SW_SEL028;//SEQ 28[ｼｽﾊﾟﾗ設定]
//2013-08-20[高速MEM]	U2b	CB_SEQ_SW_SEL029;//SEQ 29[ｼｽﾊﾟﾗ設定]
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM340;
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_SEL341;
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_SEL342;
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM345;//20030709
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM346;//20030524
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM347;//200500117
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM348;//20060728 DEBUG
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM349;//20100820 
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM350;//20121005
//2013-08-20[高速MEM]	U2b	CB_SEQ_CB_COM351;//20121005 
//2013-08-20[高速MEM]
//2013-08-20[高速MEM]	U2b	ERR_CHK_SW_SEL029;//SEQ 29

//	***************************
//	***	カム		***
//	***************************
//2013-08-20[高速MEM]		U2b	CB_SEQ_CAM_SEL038;//入/霧 38.0~38.15
//2013-08-20[高速MEM]		U2b	CB_SEQ_CAM_SEL036;//入/切 36.0~36.7+常時
//2013-08-20[高速MEM]		U2b	CB_SEQ_CAM_SEL034;//入/切 34.0~34.8+ｴｼﾞｪｸﾀ 
//2013-08-20[高速MEM]		U2b	CAM_OUT_ENB1P;//出力ENB 38.0~38.15+ﾓｰﾄﾞ条件 ﾛｰﾀﾘｶﾑ
//2013-08-20[高速MEM]		U2b	CAM_OUT_ENB2P;//出力ENB 36.0~36.7+常時+ﾓｰﾄﾞ ﾌｨｰﾄﾞ,内部ｶﾑ
//2013-08-20[高速MEM]		U2b	CAM_OUT_ENB3P;//出力ENB 34.0~34.8+ｴｼﾞｪｸﾀ
//2013-08-20[高速MEM]		U2b	CAM_OUT_ENB3T;//出力ENB 34.0~34.8+ｴｼﾞｪｸﾀ
//2013-08-20[高速MEM]		U2b	CAM_POS_STEP_END_FLG1;//各工程の
//2013-08-20[高速MEM]		U2b	CAM_POS_STEP_END_FLG2;//各工程の


//;	*******************************************
//;	***	内部設定相当データ		***
//;	*******************************************
//2013-09-27[高速MEM]	U4b	LINK_MAX_SPD_PLS;	//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
//2013-09-27[高速MEM]	U4b	SET1_UPAREA_POS1;	//待機角度(角度とﾃｰﾌﾞﾙから)
//2013-09-27[高速MEM]	U4b	SETX_UPAREA_PLS;	//4;待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ)
//2013-09-27[高速MEM]	U4b	SETX_UPAREA_RNA;	//4;待機点位置ﾘﾆｱ位置
//2013-09-27[高速MEM]	U2b	SETX_UPAREA_DIG;	//4;待機点位置角度
//2013-09-27[高速MEM]	U4b	POS_FRQ_SPDMAX;//500KHZ
//2013-09-27[高速MEM]	U4b	POS_LSI_SPDMAX;
//2013-09-27[高速MEM]	U4b	POS_LSI_SPDBAS;
//2013-09-27[高速MEM]	U2b	POS_LSI_SPDLAT;
//2013-09-27[高速MEM]	U2b	POS_LSI_ACCLT1;
//2013-09-27[高速MEM]	U2b	POS_LSI_ACCLT2;
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S4b	ORG_FIRST_OBJPLS;
//2013-09-27[高速MEM]	S4b	ORG_SECOND_OBJPLS;


//	===================================== //
//2013-09-27[高速MEM]	S4b	SETX_UPDN_CHK_UP_DIG	;//312.2度(上死点角度 0.1度)
//2013-09-27[高速MEM]	S4b	SETX_UPDN_CHK_DN_DIG	;//180.0度(下死点角度 180.0)
//2013-09-27[高速MEM]	S4b	SETX_UPDN_CHK_UP_PLS	;//312.2度相当のﾊﾟﾙｽ(上死点角度)
//2013-09-27[高速MEM]	S4b	SETX_UPDN_CHK_DN_PLS	;//180.0度相当のﾊﾟﾙｽ(下死点角度)
	

//2013-09-27[高速MEM]	S2b	ORGIN_END_FLG1;	//電源投入の１回ON:OFFはない

//	***********************************
//	***	フルクローズ関連	***
//	***********************************
	U4b	POS_LSI_CLS_SPDBAS;//ﾌﾙｸﾛｰｽﾞ時の自起動
	U4b	POS_LSI_CLSINC_SPDBAS;//ｲﾝﾁﾝｸﾞ時
	
	U4b	SETX_FULCLS_AREA_DIG;//180.0+80.0=260.0
	U4b	SETX_FULCLS_AREA_PLS;//260.0==>PLS
	U4b	FULL_CLS_OBJ_MM;//使用しない

	S4b	SDATCLS_OBJPLS[100];//目標ﾊﾟﾙｽ(+だけ)
	S4b	SDATCLS_OBJMM[100];//目標ﾊﾟﾙｽから算出されるmm
	S4b	SDATCLS_OBJ_NEAR_UPDNPLS[100*2];//+0*4:UP +1*4 DN
	S4b	SDATCLS_UPOBJ_PLS;//待機点
	U2b	SDATCLS_TRG_STEP;//連続の最後のｽﾃｯﾌﾟ
//	*******************************************
//	***					***
//	***		実測ﾜｰｸ			***
//	***					***
//	*******************************************

//	*******************************************
//	***					***
//	***		設定値ﾜｰｸ		***
//	***					***
//	*******************************************
	U4b	SET1_CNT_TIM;
	U4b	CONT_MOD_TIM_PV;//連続ﾓｰﾄﾞ・ﾀｲﾏ
	U2b	SET1_CNT_CNT;
	U2b	CONT_MOD_CNT_PV;//連続ﾓｰﾄﾞ・ｶｳﾝﾀ

//;	***************************************************
//;	***	2BYTE  ROMﾊﾟﾗﾒｰﾀ領域			***
//;	***************************************************

	U2b	SET1_RPARAM_TOP1[128]		;//;ROMﾊﾟﾗﾒｰﾀ領域
//;	***************************************************
//;	***	ｻｰﾎﾞﾊﾟﾗﾒｰﾀ領域	4/2BYTE領域		***
//;	***************************************************
//2013-09-27[高速MEM]	U4b	SET1_INCPLS_1REV		;//	2	;PG1回転のﾊﾟﾙｽ選択
//2013-09-27[高速MEM]	U2b	SET1_RNADIR_SEL1		;//	2	;ﾘﾆｱｾﾝｻ極性
//2013-09-27[高速MEM]	U2b	SET1_INCDIR_SEL1		;//	2	;PG極性
//2013-09-27[高速MEM]	U2b	SET1_INCPLS_HOSN		;//	2	;PG補正N　ﾓｰﾀN回
//2013-09-27[高速MEM]	U2b	SET1_INCPLS_HOSM		;//	2	;PG補正M　ｸﾗﾝｸ角度M<設定0.1度>
//2013-09-27[高速MEM]	U2b	SETX_INCPLS_HOSM		;//1度
//2013-09-27[高速MEM]	U4b	SETY_INCPLS_HOSM1XX		;//1度
//2013-09-27[高速MEM]	U4b	SETY_INCPLS_HOSM01X		;//0.1度
//2013-09-27[高速MEM]	U4b	SETY_INCPLS_HOSM001		;//0.01度
//2013-09-27[高速MEM]	U4b	SETY_INCPLS_HOSM0001		;//0.001度
//2013-09-27[高速MEM]	U2b	SET1_MOTRPM_MAXM		;//	2	;ﾓｰﾀ最大回転数
//2013-09-27[高速MEM]	U2b	SETX_OUTPLS_HOSA	;//出力ﾊﾟﾙｽ補正A
//2013-09-27[高速MEM]	U2b	SETX_OUTPLS_HOSB	;//出力ﾊﾟﾙｽ補正B  INC*A/B-->Output pls


	U4b	SET1_MOTMAX_FREQ		;//	4	;ﾓｰﾀ最大時指令周波数
	S4b	SET1_RNAORG_POS1		;//	4	;機械原点入力
	S4b	SET1_RNAPOS_MAXP		;//	4	;機械上限
	S4b	SET1_RNAPOS_MINP		;//	4	;機械下限
	S4b	SET1_UPAREA_JUDG		;//	4	;上死点判定範囲
	S4b	SET1_DNAREA_JUDG		;//	4	;反転設定不可範囲0.1度設定
	S4b	SETX_DNAREA_JG_LNK		;//	4	;反転設定不可範囲0.1度ﾘﾝｸ
	S4b	SETX_DNAREA_JG_PLS		;//	4	;反転設定不可範囲ﾊﾟﾙｽ

	S4b	SETX_DAIPOS_MAXP		;//	4	;ダイハイト上限
	S4b	SETX_DAIPOS_MINP		;//	4	;ダイハイト下限


	U4b	SET1_DNDINC_SPD1		;//	4	;段取速度	
	U4b	SET1_UPAREA_SPD1		;//	4	;待機点復帰速度	
	U4b	SET1_STDINC_SPD1		;//	4	;寸動速度	
	U4b	SET1_REVDAT_SPD1		;//	4	;予備速度１	
	U4b	SET1_UPCLEEP_SPD		;

	U4b	SET1_REVDAT_SPD2		;//	4	;予備速度２	
	U4b	SET1_REVDAT_SPD3		;//	4	;予備速度３	
//	U4b	SET1_TEPDAT_SPD1		;//	4	;手動ﾊﾟﾙｻ速度	
	U2b	SET1_TEPLAT_DAT1		;//	2	;手動ﾊﾟﾙｻ低倍率	
	U2b	SET1_TEPLAT_DAT2		;//	2	;手動ﾊﾟﾙｻ高倍率	

	U2b	SET1_INCPOS_KP01		;//	2	;PG位置比例ｹﾞｲﾝ
	U2b	SET1_RNAPOS_KP01		;//	2	;ﾘﾆｱ位置比例ｹﾞｲﾝ
	U2b	SET1_ACCLAT_TIM1		;//	2	;加減速時間
	U2b	SET1_SSCURV_TIM1		;//	2	;Ｓ字時間
	U2b	SET1_UPAREA_INPX		;//	2	;上死点ｲﾝﾎﾟｼﾞｼｮﾝ
	U2b	SET1_DNAREA_INPX		;//	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ
	U2b	SET1_OBJARA_INPX		;//	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ
	U2b	SET1_UPAREA_INPXPLS		;//	2	;上死点ｲﾝﾎﾟｼﾞｼｮﾝ
	U2b	SET1_DNAREA_INPXPLS		;//	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ
	U2b	SET1_OBJARA_INPXPLS		;//	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ

	U2b	SET1_OBJARA_INPXPSX		;//	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ(ふりこ2009-10-07)

	U2b	SET1_INPPOS_TIM1		;//	2	;ｲﾝﾎﾟｼﾞｼｮﾝﾁｪｯｸ時間
	U2b	PVX_INPPOS_TIM1			;//測定時間

	U2b	SET1_ARACHK_LNG1		;//	2	;上／下死点通過判定量
	U2b	SET1_UPAREA_DIG1		;//	2	;回転時待機点(上死点)角度
	U2b	SET1_ENC360_HOS1		;//	2	;==>上記ﾃﾞｰﾀは単なる360度ｴﾝｺｰﾀﾞの補正
	U2b	SET1_INCHEN_ELNG		;//	2	;PG偏差異常幅
	U2b	SET1_INCENC_ELNG		;//	2	;PG-ENC一致量
	U2b	SET1_INCRNA_ELNG		;//	2	;PG-ﾘﾆｱ一致量
	U2b	SET1_INCSTP_ELNG		;//	2	;PG停止異常量
	U2b	SET1_RNASTP_ELNG		;//	2	;ﾘﾆｱ停止異常量
	U2b	SET1_INCREV_ELNG		;//	2	;PG逆転異常量
	U2b	SET1_RNAREV_ELNG		;//	2	;ﾘﾆｱ逆転異常量
	U2b	SET1_DAIHAI_LNG1		;//	2	;ﾀﾞｲﾊｲﾄ補正比較値(小)
	U2b	SET1_DAIHAI_LNG2		;//	2	;ﾀﾞｲﾊｲﾄ補正比較値(中)
	U2b	SET1_DAIHAI_LNG3		;//	2	;ﾀﾞｲﾊｲﾄ補正比較値(大)

	U2b	SET1_FULCLS_MXPLS;
	U4b	CALC_FULCLS_MXPLS;	//2B->4B 2012-10-05

//;	==== 2003-01-27 ====
	U4b	SET1_NEG_OFS_LNG		;//反転下限距離(0.001mm ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
	U2b	SET1_AMP100P_VLT		;//AMP100%相当時の電圧値 0~10.0v(ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
//;	====================

	U2b	PVX_AMPERR_TIM1		;//	2	;過負荷時間1
	U2b	PVX_AMPERR_TIM2		;//	2	;過負荷時間2
	U2b	PVX_AMPERR_TIM3		;//	2	;過負荷時間3
	U2b	PVX_IAMP_VLT;//0~10.0 10.0=10V()


//;	***************************************************
//;	***	ｸﾗｯﾁ制御画面設定1 4/2BYTE領域		***
//;	***************************************************
	S4b	SET1_DAIHAI_ORG0		;//	4	;ダイハイト
	S4b	SET1_DAIORG0_CMP1UP		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP1DN		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP2UP		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP2DN		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP3UP		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP3DN		;//	4	;ダイハイト()

//;;	.AIF	_PRG_CHG20030127 EQ _COMPILE_YES	;ﾌﾟﾛｸﾞﾗﾑ変更箇所(反転仕様以外の標準に入れる変更)
	S4b	SET1_DAIORG0_CMP4UP		;//	4	;ダイハイト()
	S4b	SET1_DAIORG0_CMP4DN		;//	4	;ダイハイト()
//;;	.AENDI

	U2b	SET1_MRTION_SEL1		;//	2	;回転方式
	U2b	SET1_MTSTEP_MAXM		;//	2	;段数

//	2015-09-29 
	S4b	SET1_UPAREA_POS0		;//4	;待機点位置(ﾘﾆｱｽｹｰﾙ)
	S4b	SET1_OBJECT_POS_TOP[100]	;//40=>100 4BYTE SET1_OBJECT_PS01;01段目目標位置~

	S4b	SET1_UPAREA_PLS0		;//4	;待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ)
	S4b	SET1_UPAREA_PLS1		;//4	;上死亡
	S4b	SET1_OBJECT_PLS_TOP[100]	;//40=>100 4BYTE SET1_OBJECT_PS01;01段目目標位置~


	U4b	SET1_UPAREA_TIM0		;//4	;待機時間
//2015-10-25	U4b	CHK_OBJECT_TIM_TOP[100]		;//40=>100 4BYTE SET1_OBJECT_TM01;01段目停止時間 99.99*10=1msec
	U4b	SET1_OBJECT_TIM_TOP[100]	;//40=>100 4BYTE SET1_OBJECT_TM01;01段目停止時間 99.99*10=1msec
	U4b	WK_OBJECT_TIM_TOP[100]		;//40=>100 4BYTE SET1_OBJECT_TM01;01段目停止時間 99.99*10=1msec

	U4b	SET1_UPAREA_SPD0		;//2	;基準速度
	U4b	SET1_OBJECT_SPD_TOP[100]	;//40=>100 *BYTE SET1_OBJECT_SP01;01段目移動速度 2BYTE-->4BYTE


	U2b	SET1_UPAREA_DIG0		;//2	;待機点角度(何かにつかうかもいれない程度)
	U2b	SET1_OBJECT_DIG_TOP[100]	;//40=>100 2BYTE SET1_OBJECT_DG01;01段目角度
						//[カムにも使用している]


//;	====== 0クランク設定 ===
	U2b	SVPX_UPAREA_DIG1;

//;	==== 2003-02-21 ===
	U4b	DBG_REVMOD_OBJPLS;
	U4b	DBG_REVMOD_CTLPLS;
	U4b	DBG_REVMOD_UPPLS;
	U4b	DBG_REVMOD_DNPLS;
	U4b	REV_CALC_WORK0;
	U4b	REV_CALC_WORK1;
	U4b	REV_CALC_WORK2;
//	===================================
//	===	ﾘﾆｱ/ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ動作	===
//	===================================
	S4b	STOPCHK_RNA_POS;//(下位4BYTEのみ)
	S4b	STOPCHK_INC_POS;//(下位4BYTEのみ)
	U2b	PVCK_STOP_SMPTIM;//ﾘﾆｱｾﾝｻ/ｴﾝｺｰﾀﾞの停止判定用ｻﾝﾌﾟﾘﾝｸﾞ時間 200msec
	S2b	RNA_STOP_CNT;//ﾌｨﾙﾀ回数
	S2b	INC_STOP_CNT;//ﾌｨﾙﾀ回数  -N(4)~0~+N(4)




//	***********************************
//	***				***
//	***	カム処理		***
//	***				***
//	***********************************
//;	*******************************************
//;	***	カム設定 2BYTE領域		***
//;	*******************************************
//2015-11-20	U2b	SET1_OBJ_CAM_DIG_TOP[40*2]	;//+0　方向 +1目標位置１,,,,,方向、待機点
//	1段当2個(+0方向,+1目標角度)98+1=99段
	U2b	SET1_OBJ_CAM_DIG_TOP[100*2]	;//+0　方向 +1目標位置１,,,,,方向、待機点
	
	U2b	SET1_RCAMON_POS_TOP[10*16*3]	;//後から考える
//2016-11-15	U2b	SET1_RCAMON_TIM_TOP[10*16]	;//1つの構造はON工程/ON角度/ON方向/OF工程/OF角度/OF方向
//ﾀｲﾏｶﾑ16点追加
	U2b	SET1_RCAMON_TIM_TOP[10*16*2]	;//1つの構造はON工程/ON角度/ON方向/OF工程/OF角度/OF方向
						
	U2b	CAM_OUTPUT_SW[8];//0,1,2(POS),3(TIM)
	U2b	CAM_SELECT_SW[8];//0,1,2     ,3
	U2b	CAM_OUTPUT_DT[8];//0,1
	U2b	CAM_START_FLG;
	U2b	CAM_START_MODE;
	U2b	CAM_STEP_NO;
	U2b	CAM_STEP_NO_OLD;
	U2b	CAM_STEP_MAX;
	U2b	CAM_NOW_DIG;
	U2b	CAM_OLD_DIG;
	S2b	CAM_POS_CTL_STEP;	//内部制御工程1~11
	S2b	CAM_CNT_CHG_FLG;	//連続が１ｽﾃｯﾌﾟになった


//	***********************************
//	***	進角演算		***
//	***********************************
	S2b	SINKAKU_INF;		//BIT0:1:ｼｰｹﾝｽ              BIT0=1
					//BIT1:1:停止行程が存在する
	S2b	SINKAKU_USESEL_ON_INF;	//ﾛｰﾀﾘｶﾑ1~16 ON行程  1:不可
	S2b	SINKAKU_USESEL_OF_INF;	//ﾛｰﾀﾘｶﾑ1~16 OFF行程
	S2b	SINKAKU_ROTCAM_ENBSEL_WK;	//BIT0=1 CH1:ENB
	S2b	SINKAKU_ROTCAM_ENBSEL;	//BIT0=1 CH1:ENB

	//
	S2b	SIN_RCAM_ON_DIG[16];//使用レベル(360ｴﾝｺｰﾀﾞ演算結果0.1)
	S2b	SIN_RCAM_OF_DIG[16];//使用レベル(360ｴﾝｺｰﾀﾞ演算結果0.1)

//
	S2b	WK_SIN_RCAM_ON_DIG[16];//設定レベル－ON角度(360ｴﾝｺｰﾀﾞ演算結果0.1)
	S2b	WK_SIN_RCAM_OF_DIG[16];//設定レベル－OFF角度(360ｴﾝｺｰﾀﾞ演算結果0.1)


	S2b	SINWK_CALC_SCAN;//0~15

	S2b	WK_SIN_RCAM_ON_KOUTEI[16];	//設定レベル 設定が0以外あれば設定、00位置の場合算出
	S2b	WK_SIN_RCAM_ON_SPD[16];		//設定レベル

	S2b	WK_SIN_RCAM_OF_KOUTEI[16];	//設定レベル
	S2b	WK_SIN_RCAM_OF_SPD[16];		//設定レベル


	S4b	SETD_DEGSPD_MAX;//最大速度で1秒間に何度動作しますか 0.1度/SEC

	S2b	WK_SIN_RCAM_SQON1;//設定レベル－ON角度(360ｴﾝｺｰﾀﾞ演算結果0.1)
	S2b	WK_SIN_RCAM_SQOF1;//設定レベル－OFF角度(360ｴﾝｺｰﾀﾞ演算結果0.1)

	S2b	WK_SIN_RCAMON_SW1;//
	S2b	WK_SIN_RCAMOF_SW1;//

	S2b	SIN_RCAMON_SW1;//
	S2b	SIN_RCAMOF_SW1;//

	S2b	SIN_RCAM_ON_ERR1;
	S2b	SIN_RCAM_OF_ERR1;



//	***********************************
//	***				***
//	***	表示			***
//	***				***
//	***********************************
	S4b DISP_SV_DG_DAT;
	S4b DISP_SV_MM_DAT;

	S2b DRAW_CHK_XDOT[30];
	S2b DRAW_CHK_YDOT[30];
	S2b DRAW_CHKFLG;
	S2b DRAW_POINT;
	S2b DRAW_CNT;

	S4b	SV_CHG_FLG1;//ﾘｾｯﾄ=0
	S4b	SV_CHG_FLG2;//ﾘｾｯﾄ=0 2003-07-14(TIMER 定周期用)
	S2b	SV_DAT_ERR1;//ﾘｾｯﾄに関係なくON/OFF 
	S2b	DUM_UPAREA_DIG0;
	S2b	DUM_MTSTEP_MAXM;
	S2b	DUM_MRTION_SEL1;
	S2b	DUM_SET1_DIG_TOP[100];


//	***********************************
//	***	SH2 荷重測定ソフト	***
//	***********************************
//2013-09-27[高速MEM]	S2b	COP_DIG_SIG_FLG;//どの方向で横切ったか
	
//2013-09-27[高速MEM]	S2b	COP_CB_LD_MONI_SIG;//荷重測定用信号 2003-01-31

//2013-09-27[高速MEM]	U2b	WPAR_COP_CNTROT_ZDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_CNTROT_ZDG2;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_CNTROT_SDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_CNTROT_SDG2;//

//2013-09-27[高速MEM]	U2b	WPAR_COP_REVRSE_ZDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_REVRSE_ZDG2;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_REVRSE_SDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_REVRSE_SDG2;//

//2013-09-27[高速MEM]	U2b	WPAR_COP_ZDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_ZDG2;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_SDG1;//
//2013-09-27[高速MEM]	U2b	WPAR_COP_SDG2;//

//2013-06-18 未使用	U2b	COP_ENC3600;
//2013-09-27[高速MEM]	U2b	COP_OLD_ENC3600;

//	*******************************************
//	***	2003-04				***
//	***	オーバラン異常			***
//	***	/逆転異常/反転異常		***
//	*******************************************
	U2b	START_FLG_AFTER_EMG;//

//	*******************************************
//	***	2003-05-12			***
//	***	2003-05-24			***
//	***	オーバラン異常			***
//	***	/逆転異常/反転異常		***
//	***	遮光停止２204.4(exq)		***
//	*******************************************
	U2b	WPAR_INCOVER_LNG	;//LNG1/LNG2
	U2b	WPAR_INCOVER_LNG1	;//PGｵｰﾊﾞﾗﾝ回転仕様
	U2b	WPAR_INCOVER_LNG2	;//PGｵｰﾊﾞﾗﾝ反転仕様
	U2b	WPAR_INCREV_EDYTM	;//遅延時間

	U2b	WPAR_INCSTP_EDYTM1	;//遅延時間
	U2b	WPAR_INCSTP_EDYTM2	;//遅延時間
	U2b	WPAR_INCSTP_EDYTM	;//遅延時間

	U2b	WPAR_RNA_SFTY_LNG1	;//安全装置２
	U2b	PLS_OUTPUT_FLG		;//0払い出し停止 1払出中

	S4b	SFTYCHK_RNA_POS		;//_RNA_ABS_POS((通信-原点)×符号)=>0.001mm換算のﾃﾞｰﾀを使用する

//	*******************************************
//	***	2003-06-13			***
//	***	ニアゼロタイムアウト		***
//	*******************************************
	S2b	NZ_TIM_OUT_SV1		;//運転中止(寸動部分)
	S2b	NZ_TIM_OUT_SV2		;//異常(機能は入れない)
	S2b	NZ_TIM_OUT_PV1		;//運転中止(寸動部分)
	S2b	NZ_TIM_OUT_PV2		;//異常(機能は入れない)

//	*******************************************
//	***					***
//	***	2003-07-01			***
//	***	実速度算出/ﾌﾞﾚｰｷ異常		***
//	*******************************************
	S2b	WPAR_ZERO_SPD			;//34 実速度算出用　周波数
	S2b	WPAR_BRK_SEL_SPD		;//35 ﾌﾞﾚｰｷ異常見ない速度 10.00%
	S2b	WPAR_BRK1_DLYTM			;//36 msec
	S2b	WPAR_BRK1_ACCTM			;//37 msec
	S2b	WPAR_BRK2_ACCTM			;//38 msec

	S2b	WPAR_ILNGERR_LNG		;//40 移動量異常ｵｰﾊﾞ許容値
	S2b	WPAR_ILNGERR_DIG		;//41 270.0度異常検知開始角度

	S2b	BRK_CHK_COM;//ﾌﾞﾚｰｷﾁｪｯｸ開始ｺﾏﾝﾄﾞ BIT0(BRK1) BIT4(BRK2)
	S2b	BRK_CHK_FLG;//BIT0:BRK1during BIT4 BRK2during

	S2b	BRK1_CHKDLY_TM;//開始から10msec
	S2b	BRK2_CHKDLY_TM;//開始から10msec

	S2b	BRK1_GEN_SV_FRQ1;//WORK 減速開始時の周波数のﾌｨﾙﾀ後の速度
	S2b	BRK1_GEN_SV_FRQ2;//WORK 周波数のﾌｨﾙﾀ後の速度T1経過
	S2b	BRK1_GEN_SV_DLYTM;//WORK 時間T1
	S2b	BRK1_GEN_SV_ACCTM;//WORK 時間T2
	S2b	BRK1_GEN_PV_DLYTM;//WORK 時間T1
	S2b	BRK1_GEN_PV_ACCTM;//WORK 時間T2

	S4b	BRK1_SV_DN_ACC;//目標加速度((PLS/1000)/S/S)
	S4b	BRK1_CAL_DN_ACC;//OVER LIDE 含む
	S4b	BRK2_SV_DN_ACC;//目標加速度((PLS/1000)/S/S)


//	*******************************************
//	***					***
//	***	2003-07-01			***
//	***	速度検出部			***
//	***					***
//	*******************************************
	S2b	ENCPLS_SPD_AVL_TOP[100];
	S2b	OUTPLS_SPD_AVL_TOP[100];

//2013-09-27[高速MEM]	S4b	ENCPLS_SPD_TOTAL;
//2013-09-27[高速MEM]	S4b	ENC_PLS_SPD;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
//2013-09-27[高速MEM]	S4b	ABS_ENC_PLS_SPD;// 
//2013-09-27[高速MEM]	S2b	ENC_PLS_SPD_DIR;// 符号 0:"+", -1:"-"
//2013-09-27[高速MEM]	S2b	ENCPLS_DELT;//符号付
//2013-09-27[高速MEM]	S2b	ENCPLS_SPD_POINT;
//2013-09-27[高速MEM]	S2b	ENCPLS_POINT_SEL;//10msec
//2013-09-27[高速MEM]	S2b	ENCPLS_1000MSEC_LAT;//1000msec/10msec=100
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S4b	OUTPLS_SPD_TOTAL;
//2013-09-27[高速MEM]	S4b	OUT_PLS_SPD;//+/- 1000,000HZ 極性が変わるときは0pls/sになる
//2013-09-27[高速MEM]	S4b	ABS_OUT_PLS_SPD;// (MIN機能有り 1KHZ)
//2013-09-27[高速MEM]	S2b	OUT_PLS_SPD_DIR;// 
//2013-09-27[高速MEM]	S2b	OUTPLS_DELT;//符号付
//2013-09-27[高速MEM]	S2b	OUTPLS_SPD_POINT;
//2013-09-27[高速MEM]	S2b	OUTPLS_POINT_SEL;
//2013-09-27[高速MEM]	S2b	OUTPLS_1000MSEC_LAT;
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S2b	PV_ENC_SPD_PER;//0~110.00%
//2013-09-27[高速MEM]	S2b	PV_OUT_SPD_PER;//0~110.00%
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S2b	PVC_BRK_ENC_SPD;//0~110.00% MIN-LIMIT ﾌﾞﾚｰｷ異常に使用
//2013-09-27[高速MEM]	S2b	PVC_BRK_OUT_SPD;//0~110.00% MIN-LIMIT ﾌﾞﾚｰｷ異常に使用 %MIN 機能有り

//	*******************************************
//	***					***
//	***	2003-07-09			***
//	***	原点復帰			***
//	***					***
//	*******************************************
	S2b	ORG_DRV_CNT_PV	;//0:1回 0なら最後のｽﾃｯﾌﾟにいく
	S2b	ORG_RDY_CTL_FLG;//不本意ながらﾌﾗｸﾞ 起動でBIT0=1 終了でBIT1=1で終了ｺﾏﾝﾄﾞを位置決めへ投げる

//	*******************************************
//	***					***
//	***	2003-07-09			***
//	***	サイクル表示			***
//	***	生産下限表示			***
//	***					***
//	*******************************************
	S2b	CYCL_DSP_DISENB;//0:表示 1:非表示 => 反転して出力
	S2b	CYCL_DSP_CNT_PV;//非表示ｶｳﾝﾀ 2->1->0(表示)
	S2b	LOT_CHK_DBG_CNT1;//END1
	S2b	LOT_CHK_DBG_CNT2;//END2

//	*******************************************
//	***					***
//	***	2003-07-09			***
//	***	ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ比較			***
//	***	すべり角度比較			***
//	***					***
//	*******************************************
	S4b	SET1_BREAK_TIM1		;//ブレーキタイマ設定10msec
	S2b	STOP_ERR_LATCH		;// BIT0:TIM BIT1:POS
	S2b	SET1_BREAK_DIG		;//0.1度
	S2b	VALV_OFF_DIG_CLANK	;
	S2b	LINK_CLANK_PV;//0.1度
//	*******************************************
//	***					***
//	***	2003-07-09			***
//	***	生産下限			***
//	***					***
//	*******************************************
	S4b	PRD_DAI_POS0;//生産下限(生)
	S4b	PRD_DAI_POS1;//生産下限 制御値(10回平均後のﾃﾞｰﾀ)->手動補正ﾃﾞｰﾀは上死点のものを使用
	S2b	PRD_DAI_CMP_ENB;//BIT0=1:比較 比較不可


//_SVB_SLIDE_POS		.SRES	4		;2003-07-09 生産下限位置

//	***************************************************
//	***	異常履歴に伴い通常でも使えるﾃﾞｰﾀ	***
//	***************************************************
//	2004-01-28 ADD

	S4b	LT_LINK_SV_OBJ_ABSPLS[2];//abs停止目標位置(設定ﾊﾞｯｸﾗｯｼなし)
	S4b	LT_INT_LINK_RL_OBJ_ABSPLS[2];//(ﾌﾙｸﾛｰｽﾞ時は対象を変える)
	S4b	LT_LNGTH_ADD_DATA[2];//符号付き
	S4b	LT_LNGTH_TOTAL_OUTPLS[2];//符号つき TOTAL=TOTAL+ADD ADD_DATA<=0
//      === ｵﾘｼﾞﾅﾙ
	S4b	FREQ_SV_SPD;
	S2b	SV_OBJ360;//


//	***************************************************
//	***	10段仕様+連続寸動一行程			***
//	***************************************************
//	2004-01-26
	S2b	WFSYS_OPT_CNT_SEL	;//SEL=1 連寸一、連続一行程有効
//;;;2015-10-25	S2b	WFSYS_MAX_STEP_SEL	;
	S2b	CCS_BTTN_OFF		;//下降中は停止ｺﾏﾝﾄﾞ発行,上昇中は運転釦を見ず停止ﾗｯﾁ
					//上昇中でMAINは1:の時は停止ｺﾏﾝﾄﾞ発行
					//

//	*******************************************
//	***					***
//	***	オーバラン不具合検索ソフト	***
//	***	2004-01-28			***
//	*******************************************
	S4b	ACCESS_ERR1[10];	//_PLS_OutPposLにｱｸｾｽに行ったらこれに切り替える 0~4は全て0のはず
	S4b	WK_ERR_INFO_CPU_TOP[50];//80/4=20


	S4b	LSI_LOAD_DAT;
	S2b	ERR_INFO_DLY_TIM;
	S2b	ERR_INFO_SAVE_FLG;
	S2b	ERR_INFO_SAVE_LATCH;

//	===== OVER - RUN
	S2b	ENC360_OVER_FLG;
	S2b	ENC360_OVER_ENC;

	S2b	SVX_OVER_ERR_DIG;//待機点+５度   5
	S2b	SVX_OVER_JGSTR_DIG;//待機点-度 355

//	*******************************************
//	***	位置決めＬＳＩ	ｺﾏﾝﾄﾞﾊﾞﾌｧ	***
//	*******************************************
	S4b	LSI_BUF_PLS_BitComdL;//

//	*******************************************
//	***	位置決めＬＳＩ異常		***
//	*******************************************
	S2b	LSI_PLSCLR_RETRY_CNT1;//CLR処理そのもの
	S2b	LSI_PLSSET_RETRY_CNT1;//

	S2b	POS_LSI_ACS_ERR_FLG1;//異常ﾌﾗｸﾞ
	S2b	POS_CALC_ERR_FLG1;//異常ﾌﾗｸﾞ
	S2b	POS_CALC_ERR_FLG2;//異常ﾌﾗｸﾞ

	S2b	POS_LSI_ACS_ERR_INF1;//異常ﾌﾗｸﾞ
	S2b	POS_CALC_ERR_INF1;//異常ﾌﾗｸﾞ
	S2b	POS_CALC_ERR_INF2;//異常ﾌﾗｸﾞ

	S2b	LSI_PLSCMP_RETRY_CNT1;//二重化ﾘﾄﾗｲ
	S2b	LSI_PLSCMP_NG_CNT1;//二重化ﾘﾄﾗｲ
	S2b	LSI_PLSCMP_AC_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用

	S2b	LSI_PLSRD_NG_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用

//	ﾄｰﾀﾙｶｳﾝﾀ ﾓﾆﾀ用
	S4b	LSI_PLSCLR_AC_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSCLR_NG_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSCLR_NG_CNT2;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSSET_AC_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSSET_AC_CNT2;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSSET_NG_CNT1;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSSET_NG_CNT2;//TOTALｶｳﾝﾀ ﾁｪｯｸ用
	S4b	LSI_PLSSET_NG_CNT3;//TOTALｶｳﾝﾀ ﾁｪｯｸ用

//	2004-03-04
	S4b	LSI_CMPCPUAB_POS_RL;//CPUA-B間の残りﾊﾟﾙｽの差
	S4b	LSI_CMPCPUAB_POSMAX;//CPUA-B間の残りﾊﾟﾙｽの差 最大(1回転)
	S4b	NEW_POSLSI_RESTPLS;
	S2b	POSLSI_DRV_FRQ;

//
	S4b	FREQ_PLSI_MAX_FRQ;
	S4b	FREQ_BAS_SV_SPD;
	S2b	CMP2_BAS_TOTAL_NG_CNT;
	S2b	CMP2_TOP_TOTAL_NG_CNT;
	S2b	CMP2_LAT_TOTAL_NG_CNT;
	S2b	CMP2_ACC_TOTAL_NG_CNT;
	S2b	CMP2_NOW_TOTAL_NG_CNT;

	S2b	CMP2_BAS_NG_CNT;
	S2b	CMP2_TOP_NG_CNT;
	S2b	CMP2_LAT_NG_CNT;
	S2b	CMP2_ACC_NG_CNT;
	S2b	CMP2_NOW_NG_CNT;


//	***********************************
//	***				***
//	***	割り込み停止		***
//	***				***
//	***********************************
	S2b	IRQ_EMG_FLG;
	S2b	IRQ_EMG_CNT;
	S2b	IRQ_SFY_FLG;
	S2b	IRQ_SFY_CNT;
	S2b	IRQ_STP_FLG;
	S2b	IRQ_STP_CNT;

	S2b	INT_SFY_INP_DAT;//(停止要因 FACT/RACT)
	S2b	INT_STP_INP_DAT;//(停止要因 EMG/)
	S2b	INT_STP_INP_DAT1;//
	S2b	INT_STP_INP_DAT2;//
	S2b	INT_STP_INP_DAT3;//

//	*********************************
	S2b	ENC360_LINK_AREASIG;	//BIT0:待機点範囲 BIT1:下降

	
//	================================
	S4b	WXPV_ERR_DISP[64/4*8+4];//64byte *8 page

//	***********************************
//	***				***
//	***	中型処理		***
//	***				***
//	***********************************
	S4b	LSI_SET_SPD_SV;
	S4b	LSI_SET_SPD_MAXLMT;
	S4b	LSI_SET_SPD_MINLMT;
	S2b	ORIGN_OBJ_CTL_FLG;	//

//	***********************************
//	***				***
//	***	回転・連続		***
//	***	2004-12-20		***
//	***********************************
	S2b	SETX_BANK_USELFUL	;
	S2b	CPOS_BANK_USELFUL	;
	S2b	CNT_STOP_CTRL_FLG	;//BIT0,BIT1:差し引き終了
	S4b	CPOS_SDAT1_CHGAPOS2[2*(100+10)];//WORK 8byte*16段
	S4b	CPOS_SDAT1_STPAPOS2[2*(100+10)];//WORK 
	S4b	BANK1_LK_END_OBJ_ABSPLS[2];//待機点1 未使用
	S4b	BANK2_LK_END_OBJ_ABSPLS[2];//待機点2 未使用
	S4b	LINKX_SV_OBJ_ABSPLS[2];//
	S4b	CNT_STOP_LNGTH;//差引量
	S4b	BANK2_LINK_OBJROT_NUM_ZR	;//NOW ROTATION 番号
	S4b	BANK2_LINK_OBJROT_NUMPLS_ZR[2]	;//NOW ROTATION番号相当のﾊﾟﾙｽ
	S4b	BANK1_CALC_ROT_NUM_ZR;
	S4b	CONT_STOP_END_SUBPLS;	//+ data
	S2b	CNT_BANK_CALC_ERR;

//	***********************************
//	***				***
//	***	残りﾊﾟﾙｽ補正		***
//	***				***
//	***********************************
	S4b	CNT_REST_SPD_HOSEI_DAT;
	S2b	CNT_REST_SPD_HOSEI_FLG;



//	===================================================
//	===	対策ソフト部分 2005-04-14-E(4/18)	===
//	===================================================
	S2b	CMP_LNGTH_AD_ERR_CNT;
	S2b	CMP_RESTP_SR_ERR_CNT;

//	===================================
//	===	運転釦フィルタ		===
//	===	2005-10-03		===
//	===================================
	S2b	BTTN_ON_TIME;

//	===================================
//	===	セルフチェック改善	===
//	===================================
	S2b	SELF_FIRST_END_FLG;//first(_SELF_CHECK_ACT set)
	S2b	SELF_TIMING_SIG;//0:ﾘｾｯﾄからのｾﾙﾌ 1:運転終了からのｾﾙﾌ
	S2b	SELF_CHK_MATHED;//emg(BIT1,0) DRV(BIT5,4)
	S2b	SELF_BRK_LOCK;

	S2b	SELF_SECOND_ACT_FLG;
	S2b	SELF_SECOND_STEP;
	S2b	SELF_AD_LATCH;

	S4b	SELF_START_POS_LATCH[2];
	S4b	SELF_MOV_LENGTH;// PLS(換算値)
	S4b	SELF_MOV_SPEED;//  PLS(換算値)

//	===================================
//	===				===
//	===	準備完了状態での遮光	===
//	===				===
//	===================================
	S2b	RDY_SFTY_LOCK;//BIT0:LOCK
	S2b	RDY_SFTY_WAIT_TIM;//

//	===================================
//	===				===
//	===	LSA FILTER		===
//	===	2006-07-16		===
//	===================================
	S2b	LSA_ENC_DIG;//
	S2b	LSA_ENC_MOV_LNG1A;//角度の加算
	S2b	LSA_ENC_MOV_LNG1B;//角度の加算
	S2b	LSA_ENC_MOV_LNG2;//角度の加算
	S2b	LSA_SIG_DT;//
	S2b	LSA_SIG_OLD_DT;//
	S2b	LSA_SIG_OLD_WRK;//
	S2b	LSA1_FILETR_TIM;//
	S2b	LSA2_FILETR_TIM;//
	S2b	WPAR_LSA_FILTIM;
	S2b	SET1_LSAABN_AGL1;	//360ENCの距離
	S2b	SET1_LSAABN_AGL2;	//360ENCの距離
	S2b	LSA_ERR_SIG;//
	S2b	LSA_CHK_DELAY_TM;


//	===================================
//	===				===
//	===	荷重計カム処理		===
//	===	2006-07-28		===
//	===================================
//2013-09-27[高速MEM]	S2b	SET1_KJSTR_STEP1;	//0,1~工程 
//2013-09-27[高速MEM]	S2b	SET1_KJSTR_DIG1;	//359.0
//2013-09-27[高速MEM]	S2b	SET1_KJEND_STEP1;	//0,1~工程
//2013-09-27[高速MEM]	S2b	SET1_KJEND_DIG1;	//359.0
//2013-09-27[高速MEM]	S2b	KJ_AREA_SIG;//BIT4:AREA-ON BIT5:END
//2013-09-27[高速MEM]	S2b	KJ_AREA_BT0_OLD;//2013-06-19


//	===================================
//	===				===
//	===	段取一旦停止機能	===
//	===	2006-07-28		===
//	===================================
	S2b	SET1_DND_STOP_SW;//どこにとめるか 0(non,stop),BIT0(上),BIT1(SV1),BIT2(SV2) MAX:3STEP
	S2b	SET1_DND_STOPDIG_UP;//上死点
	S2b	SET1_DND_DIGTOP[4];//+0,上死点 +1:段取停止角度 0~358.0
	S4b	SET1_DND_PLSTOP[4];//上死点
	S4b	SET1_DND_UPPLS[4];

//	-------- 制御ﾃﾞｰﾀ--------
	S2b	DNDINC_CTRL_STEP;//非常停止時のみクリア段取の初回起動及び入・切で再度演算
				//本当は非常停止ではなく他のモードで動かされたら状態
				//ROTでは1,2のみ
				//NEGでは1(下降),2(途中),3(上) ﾀｲﾏとはｽﾃｯﾌﾟを分ける
				//手動パルサも使用する
	S2b	CPOS_DND_STOP_SW;
	S2b	CPOS_DND_STOP_SWOLD;
	S2b	CPOS_DND_STOP_DIRECTOLD;
	S2b	CPOS_DND_DIGTOP[4];//+0,上死点 +1:段取停止角度 0~358.0
	S4b	CPOS_DND_PLSTOP[4];//上死点

//	===================================
//	===				===
//	===	演算MISS		===
//	===	2006-07-28		===
//	===================================
	S2b	CALC_MISS_FLG1;//

//	===================================
//	===				===
//	===	手動ぱるさ		===
//	===	2006-07-28		===
//	===================================
	S2b	SET1_PLSALO_PLS;//パルサ倍率低
	S2b	SET1_PLSAHI_PLS;//パルサ倍率高

//	===================================
//	===				===
//	===	手動パルサ		===
//	===	2006-07-28		===
//	===================================
	S4b	SET1_TEPCTL_SPD1;//手動ﾊﾟﾙｻ速度(段取速度)
	S4b	TEP_POS_ADD_CNT;//
//2013-06-05 未使用;;;;;;;;	S4b	TEP_POS_ADD_CNTOLD;//
	S2b	TEP_IN_ADD;//入力側で作成起動時0にする
	S2b	NEW_TEP_CNT;//
	S2b	TEP_MODE_DRV;//起動時に判定
	S2b	TEP_STEP_FLG;	//STEP 管理
	S2b	TEP_STEP_WTTM;	//WAIT

	S2b	TEP_STEP_SVWTTM1;//2013-06-05
	S2b	TEP_STEP_SVSMPTM;//
	S2b	TEP_ADDCHK_SVPLS;//2013-06-13
	S4b	TEP_MIN_SPD_PLS;
	S4b	TEP_MIN_SPD_FRQ;//自起動速度
	S4b	TEP_CHG_SPD1;
	S4b	TEP_CHG_SPD2;

	S2b	TEP_INPLS_FLG;//2013-06-20


//	===================================
//	===				===
//	===	原点復帰2段式		===
//	===	2006-07-28(07-31)	===
//	===================================
	S2b	WPAR_ORGMOD2_TIM;//SV
	S2b	ORGIN_MOD2_SEL;//0:ｻｰﾁ動作 1:待機点動作
	S2b	ORGIN_MOD2_CHKTIM;//2.0sec
	S2b	ORGIN_MOD2_START_FLG;//起動管理

//	===================================
//	===				===
//	===	2006-09-19		===
//	===	ｵｰﾊﾞﾗｲﾄﾞ		===
//	===				===
//	===================================
//2013-09-27[高速MEM]	S4b	POSCTL_SV_PLS[2];//設定位置
//2013-09-27[高速MEM]	S4b	POSCTL_RL_PLS[2];//ﾘｱﾙﾀｲﾑ位置
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S4b	POSCTL_SET_SPD;//目標速度(PLS/S)設定
//2013-09-27[高速MEM]	S4b	POSCTL_SV_SPD;//目標速度(PLS/S)ｵｰﾊﾞﾗｲﾄﾞを含む
//2013-09-27[高速MEM]	S4b	POSCTL_RL_SPD;//内部演算リアルタイム速度(PLS/S)
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S4b	POSCTL_SV_UP_ACC;//目標加速度((PLS/1000)/S/S)
//2013-09-27[高速MEM]	S4b	POSCTL_SV_DN_ACC;//目標加速度((PLS/1000)/S/S)
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S4b	POSCTL_SV_OFS_SPD;//自起動 PLS/S
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]	S2b	POSCTL_STEP_CMD;//0:EMG停止(速度=0) 1:起動ｺﾏﾝﾄﾞ 2:(減速停止)
//2013-09-27[高速MEM]	S2b	POSCTL_STEP_FLG;//0(IDLE) 1:起動 FF:END
//2013-09-27[高速MEM]	S2b	POSCTL_CALC_ERR;//BIT0(停止しない状態での起動),BIT1(符号)
//2013-09-27[高速MEM]
//2013-09-27[高速MEM]//	--------- 速度をきちんと扱うために--------
//2013-09-27[高速MEM]	S4b	SET_CLS_SPDBAS_PLS;//PLS/S
//2013-09-27[高速MEM]	S4b	SET_SPDBAS_PLS;//PLS/S
//2013-09-27[高速MEM]	S4b	SET_CLSINC_SPDBAS_PLS;//PLS/S


//	***********************************
//	***				***
//	***	オーバライド処理	***
//	***	SEQ			***
//	***********************************
	S2b	OVER_RIDE_LATE_FLG;//
	S2b	OVER_RIDE_LATE_REQ;//1~127% OVER-RIDE無効時100%
	S2b	OVER_RIDE_LATE_ANS;//1~127% OVER-RIDE無効時100%
	S2b	SET_SEQ_SPD_OVRLIDE;
	S2b	SET_SEQ_ACC_OVRLIDE;

//	***********************************
//	***				***
//	***	オーバライド処理	***
//	***	画面			***
//	***********************************
	S2b	WPAR_OVRLIDE_GMN;//"1"画面ｵｰﾊﾞﾗｲﾄﾞ有効
	S2b	OVERLIDE_DT_SEL;
	S2b	SET1_OVERLIDE_COF;//1%
	S2b	SET_GMN_SPD_OVRLIDE;
	S2b	SET_GMN_ACC_OVRLIDE;

//	***********************************
//	***				***
//	***	オーバライド処理	***
//	***	選択			***
//	***********************************
	S2b	SET_SPD_OVRLIDE;
	S2b	SET_ACC_OVRLIDE;
//	***********************************
//	***				***
//	***	加減速時間ｵｰﾊﾞﾗｲﾄﾞ	***
//	***	1~127=時間*100/(1~127	***
//	***	運転釦ON時のみ演算	***
//	***	(一旦停止では変えない)	***
//	***	2005-01-17		***
//	***********************************
	S2b	OVER_RIDE_USEFUL;	//1~127
	U2b	CMP_POS_LSI_ACCLT1;
	S2b	OVER_UPDN_DBGCNT;


//	--------- ｵｰﾊﾞﾗｲﾄﾞ機能----------
	S4b	OVER_LIDE_ANS_TIM;//LATE (100*100)/(OVER*OVER) ﾃﾞﾊﾞｯｸ用
	S4b	SET_UP_ACC_LATE;//目標加速度(PLS/S/S)
	S4b	SET_DN_ACC_LATE;//目標加速度(PLS/S/S)
	S2b	POSCTL_OVER_SPD_LAT;//1~127% 1CYCLE 反映値(画面ﾃﾞｰﾀはﾘｱﾙﾀｲﾑ)
	S2b	POSCTL_OVER_ACC_LAT;//1~127% 1CYCLE 反映値(画面･ｼｰｹﾝｽとも1回転)

//	***********************************
//	***				***
//	***	新型補正		***
//	***				***
//	***********************************
	S4b	MONI_CPUAB_PLSDELT[2];//
	S2b	CNT_SYNC_ERR_FLG;
	S4b	CNT_SYNC_HOS_DAT1;//補正
	S4b	CNT_SYNC_HOS_DAT2;//生
	S2b	CNT_SYNC_HOS_FLAG;
	S2b	CNT_SYNC_CHK_CNT1;
	S2b	CNT_SYNC_CHK_CNT2;
	S2b	CNT_SYNC_HOS_CNT1;

//	*******************************************
//	***	同期ズレ 調査機能		***
//	*******************************************
	S2b	CNT_SYNC_STS_FLG;
	S2b	CNT_PLSOUT_STOP_CNT;
//	*******************************************
//	***	同期ズレ 対策			***
//	*******************************************
	S4b	HENSA_OVER_MOVE_CNT;
	S4b	HENSA_OVER_STOP_CNT;
	S4b	SV_CONST_SUB_PV;
	S4b	SV_REAL_PLS[2];
	S4b	SV_REAL_SUB_PV;
	S2b	CPUy_RESTPLS_LTFLG;


//	*******************************************
//	***	PARAM				***
//	*******************************************
//;	========2006-09-30 MONITOR=================
	S2b	WPAR_ANAIN_SEL	;//0:0~10V:X%(SIT3-TYPE) 1:-100%~(0)5~10V(100%):
//;	========2006-09-30(ｵｰﾊﾞﾗｲﾄﾞ加減速時間)=========
	S2b	WPAR_ACCTYP_SEL	;//0:加速距離一定(SIT3ｴｸｾﾃﾞｨ) 1:加速度一定 2:加速時間一定 


//	*******************************************
//	***	ANALOG				***
//	*******************************************
	S2b	WPV_AD_DATA;// +/- AD DATA
	S2b	WPV_ABS_AD_DATA;// ABS
	S2b	WPV_POWER_MONI	;// ﾊﾟﾜｰﾓﾆﾀ(0~300%)orTRQ

//	*******************************************
//	***					***
//	***	バイトアクセス可能ｒａｍ	***
//	***	ｓｒａｍ			***
//	***	(sh2内臓/sh4　sdram)		***
//	*******************************************

//	*******************************************
//	***					***
//	***					***
//	***		位置決め部		***
//	***					***
//	*******************************************


//	*******************************************
//	***					***
//	***	dualportram			***
//	***	大文字				***
//	***					***
//	*******************************************
//	=== 減速ﾎﾟｲﾝﾄ対策 2004-04-16 ===
	S4b	IN_POS_GPOINT_POS;//生
	S4b	POS_GPOINT_POS;//基準値()


//	***************************************************
//	***	(上昇無効解除からのLOCKｿﾌﾄの遅延)	***
//	***	2006-11-21				***
//	***************************************************
	S2b	SFTY_LOCK_DLYTM;

//	*******************************************
//	***					***
//	*******************************************
	S2b	PRD_KJP_CMP_ENB;//

//	*******************************************
//	***	2006-12-06			***
//	*******************************************
	S2b	SELF_LOCK_FLG;

//	***************************************************
//	***	2007-01-16				***
//	***************************************************
	S2b	DRV_START_KEEP;

//	***************************************************
//	***	2007-03-02				***
//	***************************************************
	S2b	CMP_RECOVER_FLG;

//	***************************************************
//	***	2007-11-26				***
//	***************************************************
	S4b	CHK_LSI_LOAD_POS_CNT;//
	S4b	CHK_LSI_LOAD_OUT_CNT;

//	***************************************************
//	***	2007-12-12				***
//	***************************************************
	S4b	SHOT_MOST_DOWN_POSWK;
	S4b	SHOT_MOST_DOWN_POS;

//	***************************************************
//	***	2008-04-30				***
//	***************************************************
	S2b	ORIGN_180ARA_FLG;


//	*******************************************
//	***	2008-11-11	H2Wからの移植	***
//	*******************************************
//	***************************
//	***	2008-05-10	***
//	***************************
//	***************************
//	***	2008-06-10	***
//	***************************
//	***************************
//	***	2008-01-26	***
//	***************************
	S2b	SQ_RNA_ALMRST_OLD;
	S2b	IN_PARAM_RNA_CHK;
	S2b	RNA_PROTOCOL_SEL;//0 1:NEW
//;	------------ 2015-10-13-------------------
	S2b	RNA_PROTOCOL_X		;//"1"X社製ﾌﾟﾛﾄｺﾙ

//	***************************
//	***	2009-03-11	***
//	***************************
	S2b	WPAR_MCNRNA_SEL		;//1:機械でﾘﾆｱｽｹｰﾙを使用しない構造･･原点復帰
	S2b	WPAR_CUPCHK_SEL		;//1:SIT2用ｶｯﾌﾟﾘﾝｸﾞﾁｪｯｸ
	S2b	WPAR_360STP_HAB		;//0:未使用 2:停止中2度は許容する 358-359-0度-1-2

	S2b	CTL_ENC360_OLD		;//
	S2b	UP360_CHK_LIST		;//進行方向で原点位置が見えたか?


	S2b	SET360_UPAREA_DIG1	;//1度単位　23.4-->23.0
	S4b	SET360_UPAREA_PLS1	;//pls

//	***********************************
//	***	2009-03-11		***
//	***	SIT4のメカのLSAの移植	***
//	***				***
//	***********************************
	S2b	LSA_SIG_DT2		;//
	S2b	DIR_FLG			;//
	S2b	VALV_ON_FLG		;//

//	*******************************************
//	***	2009-03-11			***
//	***	360ｴﾝｺｰﾀﾞ停止なのに動いた異常	***
//	***					***
//	*******************************************
	S2b	STOP_360ENC_DIG;



//	***************************************************
//	***						***
//	***		ふり子　戻り			***
//	***						***
//	***		_DMATH_DNDRIV			***
//	***	2009-10-07(2007-04-02)			***
//	***						***
//	***************************************************
//	222.6と_PVP_TAIKITEN_POSで描画を行う
//
//	--->STOP(まだ　DIR=0)
//	--->DIR=1:起動() 
//	EMG SET_FLG=0
//	EXQ SET_FLG=keep
//	--------- 処理注意-------
//	MOTION
//	ERR
//	AREA-SIG
//	CAM
//

	S4b	DNM_SET1_UPAREA_PLS0		;//4B待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ)
	S4b	DNM_SET1_OBJECT_PLS_TOP[100]	;//4BYTE SET1_OBJECT_PS01;01段目目標位置~
	U2b	DNM_SET1_UPAREA_DIG0		;//待機点
	U2b	DNM_SET1_OBJECT_DIG_TOP[100]	;//2BYTE SET1_OBJECT_DG01;01段目角度
	S2b	DNM_DIR_SET_FLG		;//2BYTE 0:往路 1:復路(動作中保証：停止時に切り替わり)
	S2b	DNM_DIR_NOW_FLG		;//
	S2b	DNM_DIR_SAM_FLG		;//2BYTE 0:往路 1:復路(動作中保証：停止時に切り替わり)
	S2b	DNM_DIR_CHG_FLG		;//各ｿﾌﾄ(CAM,ERR検知)にDIRが変わったことを通知する
	S2b	DNM_DIR_CHG_TIM		;//10scanｶｳﾝﾀ
	S2b	DNM_CTL_INC3600		;//

	U4b	DNM_SETX_UPAREA_PLS	;//4;待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ):上死点
	U2b	DNM_SETX_UPAREA_DIG	;//2;回転/反転時待機点
	U2b	DNM_WSVX_CLNK_UP_POS	;//
	U2b	DNM_WSVX_CLNK_UP_POS_UP	;//
	U2b	DNM_WSVX_CLNK_UP_POS_DN	;//
	S2b	DNM_SETX_LINK_UP_POS_UP	;//ｸﾗﾝｸ設定(範囲比較)
	S2b	DNM_SETX_LINK_UP_POS_DN	;//ｸﾗﾝｸ設定(範囲比較)

//	===========入れ替え有り===========
	U4b	SETXY_UPAREA_PLS	;//4;待機点位置(ｲﾝｸﾘﾒﾝﾀﾙ):上死点
	U2b	SETXY_UPAREA_DIG	;//2;回転/反転時待機点
	U2b	WSVXY_CLNK_UP_POS	;//
	U2b	WSVXY_CLNK_UP_POS_UP	;//
	U2b	WSVXY_CLNK_UP_POS_DN	;//
	S2b	SETXY_LINK_UP_POS_UP	;//ｸﾗﾝｸ設定(範囲比較)
	S2b	SETXY_LINK_UP_POS_DN	;//ｸﾗﾝｸ設定(範囲比較)

//	==============荷重関係でふりこによる追加================
//	==============2007-09-06　ふりこ ===========
	S2b	WPARX_COP_DNDRV1_ZDG1;//ふりこ往路
	S2b	WPARX_COP_DNDRV1_ZDG2;
	S2b	WPARX_COP_DNDRV1_SDG1;
	S2b	WPARX_COP_DNDRV1_SDG2;
	S2b	WPARX_COP_DNDRV2_ZDG1;//ふりこ復路
	S2b	WPARX_COP_DNDRV2_ZDG2;
	S2b	WPARX_COP_DNDRV2_SDG1;
	S2b	WPARX_COP_DNDRV2_SDG2;

	S2b	SETX_KJSTR_DIG1;//往路
	S2b	SETX_KJEND_DIG1;//往路
	S2b	SETY_KJSTR_DIG1;//復路
	S2b	SETY_KJEND_DIG1;//復路

	S2b	SETC_KJSTR_DIG1;//演算
	S2b	SETC_KJEND_DIG1;//演算

	S2b	DNM_DIR_FLG_OLD;

//	===================================
//	===				===
//	===		2010-08-20 	===
//	===				===
//	===================================
	S2b	WPAR_BRKTOUT_SPD;//2;
	S2b	WPAR_BRKTCHK_SPD;//2;
	S2b	WPAR_SFYOPT_USEL;//2;0[現行]:1[上昇無効にしない]:2[上昇無効にする]

//	--------- 制動試験------
	S2b	BRKTST_MOD_FLG;//
	S4b	BRKTST_OUTSPD_PLS;//
	S4b	BRKTST_CHKSPD_PLS;//

//	----- 制動試験追加 2011-09-14---
	S2b	BRKTST_INPUT_CMD;//BIT0:制動試験指令[349.0の替わり],BIT1:制動試験停止指令
	S2b	WPARX_BRKTST_STPDEGX	;//360ｴﾝｺｰﾀﾞ上角度
	S4b	WPARX_BRKTST_STPPLS	;//
	S4b	WPARX_BRKTST_STPLNG	;//相対ﾊﾟﾙｽ
	S4b	BRKTST_STP_ABSPLS[2]	;//
	S2b	BRKTST_STR_FLG		;//
	S2b	BRKTST_SW_IN		;

//待機点
	S2b	BRKTST_AREA_SIG		;//BIT0/BIT4[待機点]
	S2b	BRKTST_CLNK_UP_POS_UP;	//ｸﾗﾝｸ設定[0.1DIG]
	S2b	BRKTST_CLNK_UP_POS_DN;	//ｸﾗﾝｸ設定[0.1DIG]
	S2b	BRKTST_LINK_UP_POS_UP;	//LINK設定[0.1DIG](範囲比較)
	S2b	BRKTST_LINK_UP_POS_DN;	//LINK設定[0.1DIG](範囲比較)

	S2b	BRKTST_BAKUP_FLG_SV1	;//ﾊﾞｯｸｱｯﾌﾟﾌﾗｸﾞBAKUP戻し
	S2b	BRKTST_BAKUP_FLG_SV2	;//ﾊﾞｯｸｱｯﾌﾟﾌﾗｸﾞBAKUP戻し
	S2b	BRKTST_BAKUP_FLG_PV1	;//ﾊﾞｯｸｱｯﾌﾟﾌﾗｸﾞBAKUPﾃﾞｰﾀ
	S2b	BRKTST_BAKUP_FLG_PV2	;//ﾊﾞｯｸｱｯﾌﾟﾌﾗｸﾞBAKUPﾃﾞｰﾀ

//	===================================
//	===				===
//	===		2010-08-20 	===
//	===				===
//	===================================
//	--------- ブレーキチェック----
	S2b	SETX_BREAK_DIG2;//0.1度
	S2b	SETX_BREAK_TIM2;//1msec


//	------ 加振動制御 ------
	S4b	KAJLIV_TTL_TOTAL;
	S2b	WPAR_KJYU_STOPTBL[12];//
	S2b	KAJLIV_TTL_POINT;
	S2b	KAJLIV_TTL_IDOBUF[20];//
	S2b	WPVX_KAJLIV_TTL;//
	S2b	SET1_VIB_KJYU_TTL;//
	S2b	SET1_MAX_KJYU;//最大荷重設定(ｵﾌﾟｼｮﾝにしかない)(2010-08-23 koma)


	S2b	VIB_STEP_FLG;//BIT0:停止ラッチ BIT6:ﾀｲﾑｱｯﾌﾟ
	S2b	VIB_STEP_COM;//1:払い出し中 0:停止中
	S2b	VIB_GET_SET_TIM;
	S2b	VIB_USE_SET_TIM;//
	S2b	VIB_PV_UP_TIM;//
	S2b	VIB_DLY_TIM;


//	***************************************************
//	***	2010-10-07	待機点0度対策		***
//	***************************************************
	S4b	LINK_2ROT_PLS		;
	S4b	LINK_3ROT_PLS		;
	S4b	LINK_4ROT_PLS		;

	S4b	LINK_1000ROT_PLS[2]	;



//
	S2b	WPAR_STOPING_TIM	;//予備、ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ,ﾌﾞﾚｰｷﾀｲﾏ用時間(2010-08-20以前は50ms固定)
	S2b	WPAR_ACC_MATHED		;


//	***************************************************
//	***	2010-10-21				***
//	***************************************************
	S2b	cbsys_tbl_err		;//
					//bit0=1:cbsysの加速度ﾃｰﾌﾞﾙ異常



//	表示関連に使用する最大速度(本当の最大速度)
	U4b	SETD_LINK_MAX_SPD_PLS	;//ｲﾝｸﾘﾒﾝﾀﾙｴﾝｺｰﾀﾞ換算値　pls/s
	U2b	SETD_MOTRPM_MAXM	;//	2	;ﾓｰﾀ最大回転数

	U2b	SVX_DNM_MAXSPM		;//ふりこの最大速度

//	-------[]
	U4b	TBL_USE_POS0		;//待機点の距離
	U2b	TBL_ANS_ACCTIM		;
	U2b	TBL_ANS_MAXSPM		;
	U2b	TBL_ANS_ACC_SEL		;//(0,1),2[TBL2],3[TBL3]



//	*******************************************
//	***	ふりこ追加による異常追加	***
//	*******************************************
	U4b	CHK_ADD_DATA_LATCH[2]	;
	U2b	DND_OVERCHK_DIG		;

//	***********************************
//	***				***
//	***	ふりこ加速に関して	***
//	***	通常演算の簡略化	***
//	***	2010-09-22		***
//	***	(ACC演算はCPUAだけ)	***
//	***				***
//	***********************************
	S4b	ACC_REST_ABS_PLS[2]	;//目標-現在位置　残り距離
	S2b	ACC_REST_FLG		;//0:減速ﾁｪｯｸしなくていい(500,000*30sec以上距離がある)
	S2b	DNM_ACC_CALFLG		;//0/1

	S4b	ACC_MONITOR_DAT1	;
	S4b	ACC_MONITOR_DAT2	;
	S4b	ACC_MONITOR_DAT3	;
	S4b	ACC_MONITOR_DAT4	;
	S4b	ACC_MONITOR_DAT5	;
	S4b	ACC_MONITOR_DAT6	;
	S4b	ACC_MONITOR_DAT7	;
	S4b	ACC_MONITOR_DAT8	;
	

//	***********************************
//	***				***
//	***	スキャン分割		***
//	***	2010-12-08		***
//	***				***
//	***********************************
	S2b	INT1MS_SCAN_02MS	;
	S2b	INT1MS_SCAN_03MS	;//時間に関係ない処理
	S2b	INT1MS_SCAN_05MS1	;
	S2b	INT1MS_SCAN_05MS2	;
	S2b	INT1MS_SCAN_10MS	;


//	-----------ｽｷｬﾝ分割したことによる弊害
	S2b	ERR_LEV_IN2	;
	S2b	ERR_LEV_IN3	;
	S2b	ERR_LEV_IN4	;
	S2b	ERR_LEV_IN5	;
	S2b	ERR_LEV_IN6	;

//	***********************************
//	***				***
//	***	時間データ		***
//	***	2010-12-08		***
//	***				***
//	***********************************
	S2b	WPAR_CMP_ERR_TIM1	;//PG,_EQ_追加 2003-01-28
	S2b	WPAR_CMP_ERR_TIM2	;//PG,_EQ_追加 2003-01-28


//	***************************************************
//	***						***
//	***	2011-01-18(2010-12-27)			***
//	***	荷重表示切替のためのサイクル速度比較	***
//	***						***
//	***************************************************
	S2b	CYCLE_SPD_CMP_FLG1	;//BIT0
	S2b	CYCLE_SPD_CMP_PV_DAT	;//実測
	S2b	WPAR_COP_DISP_SPM1	;//2010-12-27 荷重切替サイクル速度比較1spm単位


//	***************************************************
//	***						***
//	***	2011-01-18(2010-12-27)			***
//	***	反転のインチングの手前減速		***
//	***						***
//	***************************************************
	S4b	NEG_CTRL_BEFOR_OBJ_PLS;//目標－手前
	S4b	NEG_CTRL_BEFOR_SLW_PLS;//目標－手前－速度減速

	S4b	NEG_CTL_OBJ_POS_PUSH[2];//2011-05-11


//	***************************************************
//	***						***
//	***	2011-03-22				***
//	***						***
//	***************************************************
	S2b	WPAR_ORGDRV_MD2		;//
	S2b	ORGIN2_STEP_FLG		;//


//	***************************************************
//	***						***
//	***	2011-03-22				***
//	***						***
//	***************************************************
	S4b	RNA_STLORK_HALF;//設定(半径)

	S4b	RNA_ABS_ORGWORK2;//待機点検出用ﾜｰｸ
	S4b	RNA_ABS_ORGWORK2A;//待機点検出用ﾜｰｸ
	S4b	INC_ABS_ORGWORK2[2];//ﾘﾆｱを記憶時のｲﾝｸﾘﾒﾝﾀﾙ角度
	S4b	INC_ABS_ORGWORK2A[2];//ﾘﾆｱを記憶時のｲﾝｸﾘﾒﾝﾀﾙ角度
	S4b	INC_OFS_ORGWORK2A;//

	S4b	RNA_ABS_MD2_C1;//
	S4b	RNA_ABS_MD2_C1A;//
	S4b	RNA_ABS_MD2_C2;//

	S4b	DAIHAI_CALC_WORK1[2];
	S4b	DAIHAI_CALC_WORK2[2];
	S4b	DAIHAI_CALC_WORK3[2];
	S4b	DAIHAI_CALC_WORK4[2];
	S4b	DAIHAI_CALC_WORK5[2];
	S4b	DAIHAI_CALC_WORK6[2];
	S4b	DAIHAI_CALC_WORK7X[4];//
	S4b	DAIHAI_CALC_WORK8[2];
	S4b	DAIHAI_CALC_WORK9X[4];//DEBUG
	S4b	DAIHAI_CALC_WORK10[2];//DEBUG

	S4b	DAIHAI_CALC_WORK11[2];//DEBUG
	S4b	DAIHAI_CALC_WORK12[2];//DEBUG
	S4b	DAIHAI_CALC_WORK13X[4];//DEBUG


	S2b	WPAR_DAIHAI_SEL		;//2;//手動ﾀﾞｲﾊｲﾄの演算方法の変更1:2011-03-22ﾀｲﾌﾟ

//	***************************************************
//	***						***
//	***	2011-03-22				***
//	***	ｽﾗｲﾄﾞ調整時のｽﾗｲﾄﾞ停止検出		***
//	***************************************************
	S2b	WPAR_SLDALM_LNG		;//ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動量 2011-03-22[ｸﾗﾝｸ機構MC　H1F]
	S2b	WPAR_SLDALM_TIM		;//ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動測定時間2011-03-22[ｸﾗﾝｸ機構MC　H1F]

	S2b	SLIDALM_CHK_FLG		;//
	S2b	SLIDALM_CHK_TIM		;//計測時間
	S4b	SLIDALM_CHK_POS		;//計測時間後の位置
	S4b	SLIDALM_POS_PULAS	;//最大位置
	S4b	SLIDALM_POS_MINAS	;//最小位置

//	***************************************************
//	***						***
//	***	2011-03-22				***
//	***	位置決め原点復帰時の誤差検出		***
//	***************************************************
	S4b	ORGPOS_LATCH1_INC_OFFSET_PLS;	//位置決め完了時
	S4b	ORGPOS_LATCH1_RNA_ABS_DAT;	//位置決め完了時 RNA
	S4b	ORGPOS_SERCH_RNA_ABS_DAT;	//ｻｰﾁﾀｲﾌﾟの原点出の下限位置の基準
	S2b	WPAR_ORGPOS_LNG1	;//比較距離

//	***************************************************
//	***						***
//	***	2011-05-05				***
//	***	ロットカウント１回前信号		***
//	***						***
//	***************************************************
	S2b	CNT_STOP_CMD_BEF1	;//減速が長い時のロットカウンタの１回転オーバを防ぐ


//	***********************************************************
//	***							***
//	***	2011-05-11	制動試験用原点復帰完了角度	***
//	***							***
//	***********************************************************
	S4b	WPARX_BRKTST_ORGPLS	;//
	S2b	WPAR_BRKTST_ORGDEG	;//制動試験時の原点復帰完了角度 270.0度
	S2b	WPARX_BRKTST_ORGDEGX	;//


//	***************************************************
//	***						***
//	***************************************************
	S2b	TEPA_PLS_ZERO_TIM;	//

//	***************************************************
//	***	加速度測定2011-07-04			***
//	***************************************************
	S4b	BBN_MESURE_SPOS_BUF[30*2];	//8byte 30msec指定
	S4b	BBN_MESURE_SSPD_BUF[30];	//4byte
	S4b	BBN_MESURE_SSPD;	//4byte


	S4b	BBN_MESURE_PPOS_BUF[30*2];	//8byte
	S4b	BBN_MESURE_PSPD_BUF[30];	//4byte
	S4b	BBN_MESURE_PSPD;	//4byte

	S4b	BBN_MEUSRE_SV_ACC_SRC;
	S4b	BBN_MEUSRE_PV_ACC_SRC;

	S4b	BBN_MEUSRE_SV_ACC;
	S4b	BBN_MEUSRE_PV_ACC;

	S2b	BBN_MESURE_POINT;
	S2b	BBN_SET_TIME;//MAX20msec


	S4b	BBN_MESURE_SSPD_DLYBUF[110*2];//8byte2011-08-29
	S4b	BBN_MESURE_DLY_SSPD;//4byte2011-08-29
	S2b	BBN_MESURE_DLY_POINT;//3byte2011-08-29

//	***************************************************
//	***	加速度異常2011-07-04			***
//	***************************************************
	S4b	SETX_MAX_ACC_LATE;	//最大周波数*1000/時間
//2014-10-23	S4b	SETX_ACCERR_ZEROHAB;
//2014-10-23	S4b	SETX_ACCERR_ERR1DAT;
//2014-10-23	S4b	SETX_ACCERR_ERR2DAT;
	S4b	SETX_ACCERR_ERR3DAT;//BK
	S4b	ACCERR_ACC_PV;
	S4b	ACCERR_ACC_OBJ;
	S4b	ACCERR_ACC_HENSA;
	S2b	ACCERR_ERR_CNT;
	S2b	SETX_ACCERR_DLY1;//加速度=0時の異常遅延
//2014-10-23	S2b	SETX_ACCERR_DLY2;//加速度>0時の異常遅延

	S2b	SETX_ACCERR_SEL;//2011-07-11

//2014-10-23	S2b	SETX_ACCERR2_DLY1;//加速度=0時の異常遅延
	S2b	ACCERR_DLY_PV_TIM;

//	*** 2011-09-01
	S4b	SETX_UPERR_ERRCMPDAT;
	S2b	SETX_HOLD_CMP1_DEG;
	S2b	DNM_SETX_HOLD_CMP1_DEG;//2014-10-23

//	***************************************************
//	***						***
//	***************************************************
	S2b	LSI_CHK_DBG_CNT1;
	S2b	LSI_CHK_DBG_CNT2;
	S2b	LSI_CHK_DBG_CNT3;
	S2b	LSI_CHK_DBG_CNT4;



//	***************************************************
//	***		金型タッチ位置[加速度算出]	***
//	***************************************************
	S4b	RNA_BBN_MESURE_SPOS_BUF[50];//0.01mm
	S4b	RNA_BBN_MESURE_SSPD_BUF[50];//0.01mm /1msec
	S4b	RNA_BBN_MESURE_SSPD;
	S4b	RNA_BBN_MEUSRE_ACC_SRC;//0.01mm

	S4b	RNA_BBN_MEUSRE_ACC;//****.**mm/s/s
	S2b	RNA_BBN_SET_TIME;//MAX20msec
	S2b	RNA_BBN_MESURE_POINT;
	S2b	RNA_OLD_STEP;

//	***********************************************************
//	***							***
//	***		1回転で範囲内に入ったら１回チェック	***
//	***							***
//	***********************************************************
	S4b	RNA_TECH_POSBUF[4*100];
	S4b	SETX_RNA_ACC_CHKPOS;	// ****.**mm /S/S 100.00mm-> 10000.00mm/s/s
	S2b	RNA_TECH_POINT;
	S2b	RNA_INSERT_CHKFLG;	//BIT0	起動
					//BIT1	範囲内
					//BIT6=1 演算完了
	S2b	SETX_RNA_ACC_BEFTIM;



//	***************************************************
//	***		金型タッチ位置-実荷重		***
//	***************************************************
//	2012-10-18
	S4b	TECH2_KJYU_LT1KN;//FIRST  KN
	S4b	TECH2_KJYU_LT1PLS[2];//
	S4b	TECH2_KJYU_LT1PLS_OFS;//
	
	S4b	TECH2_KJYU_LT2KN;//SECOND KN
	S4b	TECH2_KJYU_LT2PLS[2];//
	S4b	TECH2_KJYU_LT2PLS_OFS;//
	
	S4b	TECH2_KJYU_LNG;//演算ｼﾌﾄ+ｼｽﾊﾟﾗｽﾌﾄ
	S4b	TECH2_KJYU_PLS;//ﾀｯﾁ位置-ｼﾌﾄ
	S2b	TECH2_KJYU_DIG;//0.1度
	S2b	TECH2_KN_FLG;//BIT0(FIRST),BIT1(SECOND),BIT6(END)

//	***************************************************
//	***		金型タッチ位置実測		***
//	***************************************************
//	==== 2011-07-28,2013-02-20 =====
	S4b	PVX_MOTINS_PS2;	
	S4b	PVX_MOTINS_POS;	
	S4b	PVX_MOTINS_PS3;	

	S2b	PVX_MOTINS_AG2;	
	S2b	PVX_MOTINS_AG2X;

	S2b	PVX_MOTINS_AGL;	
	S2b	PVX_MOTINS_AGLX;

	S2b	PVX_MOTINS_AG3;	
	S2b	PVX_MOTINS_AG3X;


	S2b	PVX_MOTINS_DANBEF;
	S2b	PVX_MOTINS_DAN;
	S2b	PVX_MOTINS_DANAFT;
	S2b	PVX_MOTINS_INF;

//	演算ﾁｪｯｸ兼ﾜｰｸ
	S4b	TECH_WK_PLS1;
	S2b	TECH_WK_DIG1;
	S2b	TECH_WK_DIG2;
	S2b	TECH_WK_DIG3;
	S2b	TECH_WK_DIG4;

	S4b	SET1_KATTCH_SPD		;//金型タッチ速度
	S2b	TECH_USED_F;//

//	***************************************************
//	***						***
//	***	ROMﾊﾟﾗﾒｰﾀをﾜｰｸにCOPYする		***
//	***	ｺｰﾄﾞがおかしい場合0とする		***
//	***	2011-09-14				***
//	***************************************************
	U2b	W_PARAM_TOP[512];	//

//	*******************************************
//	***					***
//	*** 	CPUA,B共通ﾊﾞｯｸｱｯﾌﾟ用ﾜｰｸ		***
//	***	2011-09-14			***
//	***					***
//	*******************************************
	S2b	CBSTS_LOAD_FLG;

//	*******************************************
//	***					***
//	*** 	CPUB専用ﾊﾞｯｸｱｯﾌﾟ用ﾜｰｸ		***
//	***	2011-09-14			***
//	***					***
//	*******************************************
	S2b	CBSTS_SAVE_CMDWK;

//	*******************************************
//	***					***
//	*** 	CPUA専用ﾊﾞｯｸｱｯﾌﾟ用ﾜｰｸ		***
//	***	2011-09-14			***
//	***					***
//	*******************************************
	S2b	CBSTS_SAVE_DAT[4];//


//	***************************************************
//	***						***
//	***	2011-09-20				***
//	***						***
//	***************************************************
	S4b	WPARX_BRKTST_DNDLMT	;//100.00%->PLS/S






//	***************************************************
//	***		インポジション			***
//	***		2012-03-06			***
//	***************************************************
	S2b	INP_ERR_FLG;

//	***************************************************
//	***		逆転異常 2012-02-22[H2W]	***
//	***		2012-03-06			***
//	***************************************************
	S2b	REV_ERR_WAIT_TIMPV;
	S2b	REVCHK_DRIV_SHIN;//BIT0
	S2b	REVCHK_MASK_PVTIM;//
	S2b	ERRCHK_ENC360;
	S2b	REVMOD_REVDN_DIG;//反転設定＋不可範囲

//	***************************************************
//	***		制動試験監視２			***
//	***		2012-03-06			***
//	***************************************************
//	加速度算出
	S4b	BKTMCL_SPDBUF[60]	;
	S4b	BKTMCL_ACCDAT;
	S4b	BKTMCL_ACCDAT_UNIT;// PLS/S/S

	S2b	BKTMCL_ACCPOINT		;
	S2b	BKTMCL_POINTMAX		;//0,1~50 0=1

//	方向判別
	S4b	BKTMCL_OLD_PLSPOS[2]	;//0.1度
	S2b	BKTMCL_ENC_DIR		;//BIT0=0,BIT1=0:停止 BIT0=1,BIT1=0:下降 BIT0=1,BIT1=1:上昇
							

//
	S2b	BKTMCL_TMSTEP_FLG	;//ｽﾃｯﾌﾟ管理
	S2b	BKTMCL_TMSTEP_STS	;//2012-03-19[]

	S2b	BKTMCL_TOTAL_TIMPV	;//
	S2b	BKTMCL_STOP_TIMPV	;//
	S2b	BKTMCL_BBNFLT_TIMPV	;//演算時Td測定
	S2b	BKTMCL_TMDEF_PV		;//固定時
	S2b	BKTMCL_SETX_TMDEF	;//T0演算に使用(計算結果または固定)

//
	S4b	WPAR_BKTMCL_ACCCK	;//pls/s/s 加速度

	S4b	BKTMCL_STOP_SPD		;//PLS/S停止開始速度
	S4b	BKTMCL_BRKSTR_SPD	;//PLS/Sブレーキ制動開始速度
	S4b	BKTMCL_BRKSTX_SPD	;//2段目速度2012-03-26

	S4b	BKTMCL_BRKSTP_SPD	;//PLS/Sブレーキ制動停止速度2012-03-19
	S2b	BKTMCL_BRK_TIMPV	;//最大速度時のﾌﾞﾚｰｷ時間

	S2b	BKTMCL_BRKSTX_TIMPV	;//2段目時間2012-03-26
	S2b	BKTMCL_BRKSTX_TIMSV	;//2段目時間2012-03-26

//	-----2013-11-05 -----
	S2b	BKTMCL_BRX_AREA_IN	;//生
	S2b	BKTMCL_BRX_AREA_INLT	;//停止時のｴﾘｱ信号 INのﾗｯﾁ

//	----------------------------------------
	S2b	DEBUG_ENC360_STS	;//2012-05-07
	S2b	DEBUG_ENC360_STS2	;//2012-05-07

	S2b	DURING_TIM_FX		;//タイマ一旦停止からの動作(反転+全ﾓｰﾄﾞ)

//	----------------------------------------
	S2b	FUL_CLS_DLYTM_SV	;
	S2b	FUL_CLS_MAXOVER_F	;
	
//	----------------------------------------


//	--------------2012-09-25----------
	S2b	UPMSK2_MOD		;//0:参照しない 1:参照する
	S2b	UPMSK2_MOD_IN_SW	;//0,1(生　待機点2)
	S2b	UPMAK2_MOD_USE_SW	;//0,1(反映ﾀｲﾐﾝｸﾞ後)
	S2b	UPMSK2_MATH		;//0:参照しない 1:参照する 2012-10-15
	S2b	UPMSK2_DRVSEL		;//2013-02-23
	S2b	UPMSK2_MOD_IN_SWOLD	;//2014-02-20

//	--------------2012-09-25----------
	S4b	SETX_OVERH_LNGTH	;//1mm Main->OVERH SOFT
	S4b	SETX_OVERH_AMP		;//OVERH->AMP閾値
	S2b	OVERH_MODE_SEL		;//0[回転]/1[反転]/2[ふりこ]/3[ふりこ]
	S2b	SQ_OVERH_CMP		;//OVERH-> MAIN
	S2b	OVERH_CALC_USE;//MODE,


//	---------------- 2012-10-01 反転ﾃﾞﾊﾞｯｸ用------------
	S2b	NEG_DEBUG_SIG;
	S2b	NEG_EXITTIM;//針の穴を通すタイマ(追い込み失敗の遅延)  2012-10-05

//	2012-10-19 CHECK
	S2b	OBJDIG_CLANK;

//	------------------- 2012-10-19 -------
	S4b	WPARX_ELSE_ORGPLS	;//
	S2b	WPARX_ELSE_ORGDEGX	;//349.5復活 制動試験とは別の目的


//	-------- 2012-12-15 
	S2b	DNM_DEBUG_STS1;
	S2b	DNM_DEBUG_CNT;

//	-----------------------------------
//	---	2013-02-05		---
//	-----------------------------------
	S2b	SVCHK_SCAN	;//

//	-----------------------------------
//	---	2013-02-05		---
//	-----------------------------------
	S2b	PVX_DNMOD_DLYTIM	;//

//	-------------------------------------------
//	---	2013-02-15	寸動速度制限	---
//	-------------------------------------------
	S4b	UPLIMIT_SV_SPD;//(上限共通DATA)
	S2b	UPLIMIT_START_F;//BIT0:寸動からの指令

//	-------------------------------------------
//	---	2013-02-15	ﾐｭｰﾃﾝｸﾞ方式	---
//	-------------------------------------------
	S2b	MYUTING_MOD_STOPSEL;//1:いつでも遮光有効(ﾐｭｰﾃﾝｸﾞ無効)



//	-------------------------------------------
//	---	2013-02-20			---
//	-------------------------------------------
	U2b	PVX_CKSPD_OVBIT				;//赤表示(BIT0~BIT9 BIT15:戻速度)

//
	S4b	CHKSPDWORK1;//前行程PLS/S
	S4b	CHKSPDWORK2;//評価する現行程PLS/

	S4b	CHKPOSWORK1;//前行程PLS
	S4b	CHKPOSWORK2;//評価する現行程PLS

	S4b	CHKSPDWORKANS;//PLS/S
	S4b	CHKSPDWORKVMAX;//PLS/S
	S4b	CHKSPDWORKTMAX;//ms
	S4b	CHKPOSWORKANS;//PLS(2014-06-10位置ﾁｪｯｸ用)

	S2b	CHKSPDANSPER;//0.1%単位ﾃﾞｰﾀ 100
	S2b	CHKSPDPERWORK1;//前行程0.1
	S2b	CHKSPDPERWORK2;//評価する現行程0.1

	S2b	CHKPOSANSDIG;//ｸﾗﾝｸ角度
	S2b	CHKSPDPOSINFO;
	S2b	CHKSPDPOSOFS;

//	位置ﾁｪｯｸ
	U2b	PVX_CKAGL_OVBIT;


//	------2016-04-19 前前段情報--------------
	S4b	CHKSPDWORK0;	//前前行程PLS/S
	S4b	CHKPOSWORK0;	//前前行程PLS
	S2b	CHKSPDPERWORK0;	//前前行程0.1
//	-----2016-04-19 前/後加速情報--------
	S2b	CHKACCINF0;
	S2b	CHKACCINF1;
	S2b	CHKACCINF2;

//	純粋なワーク
	S4b	CALSPDWORK1;//前行程PLS/S
	S4b	CALSPDWORK2;//評価する現行程PLS/
	S4b	CALPOSWORK1;//前行程PLS
	S4b	CALPOSWORK2;//評価する現行程PLS
	S4b	CALSPDWORKANS;//PLS/S
	S2b	CALSPDANSPER;//0.1%単位ﾃﾞｰﾀ 100
	S4b	CALPOSANSLNG;

	S4b	CALPOSLNWORK;//



//	-----------------------------------
//	---	2013-02-25		---
//	-----------------------------------
	S4b	DNM_MAX_GENSOK_LENGTH	;//100%時→0時の減速距離
	
//	-----------------------------------
//	---	2013-04-14		---
//	-----------------------------------
	S2b	PLS_OUT_END_STS;

//	-----------------------------------
//	---	2013-05-26		---
//	-----------------------------------
	S4b	TEP_DND_SPD_PLS;
	S2b	TEP_CNTSMP_TIM;
	S2b	TEP_REVPLS_LT_FLG;

//	-----------------------------------
//	---	2013-07-18		---
//	-----------------------------------
	S4b	SCAN_TIM_TOTAL		;
	S2b	SCAN_TIM_IDOBUF[10]	;
	S2b	SCAN_TIM_POINT		;

	S2b	MAIN_CLK		;
	S2b	CHK_CLK_SIG		;
	S2b	SCAN_TIM_IN		;
	S2b	WPV_SCAN_TIM_REAL	;//[REAL]
	S2b	WPV_SCAN_TIM_AVL	;

	S2b	SCAN_SMP_SIG		;
	S2b	WPV_SCAN_MAX10		;
	S2b	WPV_SCAN_MAX01		;



//	***********************************
//	***				***
//	***	2013-07-22		***
//	***				***
//	***********************************
	S2b	EMG_SCANCUT_FLG		;

//	***********************************
//	***	2013-07-25		***
//	***********************************
	S2b	SCAN_DBG_CNT;

//	***********************************
//	***				***
//	***	2013-09-30		***
//	***	EPﾁｪｯｸ機能		***
//	***				***
//	***********************************
//[[[[]]]]	S2b	EP_BRKVALV_ON;
//[[[[]]]]	S2b	EPSENCER_SIG;
//[[[[]]]]	S2b	EPSENCER_CHK_FLG;//BIT0,1,2,3,4 BIT6=1 END
//[[[[]]]]	S2b	EPSENCER_TIMPV;

//	***********************************
//	***				***
//	***	2013-09-30		***
//	***				***
//	***				***
//	***********************************
//	(1)運転釦OFF記憶ﾌﾞﾚｰｷOFF
//	(2)運転釦ON記憶ﾌﾞﾚｰｷON
//	(3)ON->OFF運転釦OFF記憶
//	(4)ｴﾝﾄﾞｰﾀﾞ停止
//	(5)遅延時間ｽﾀｰﾄ
//	(6)ﾌﾞﾚｰｷOFF
//	EPのﾌﾞﾚｰｷ開放指令は本信号がOFFでも開放できる
//
	S2b	BVLV_CTL_FLG;//
	S2b	BVLV_CTL_ON;	//ﾌﾞﾚｰｷON(開放)　ON=1ならON ：開放側に対して >340.1=1>本信号
				//ﾌﾞﾚｰｷOFF(ﾛｯｸ)  ON=0ならOFF :ﾛｯｸ側に対して  EP開放(0)>本信号(0)>340.1=0
//2015-09-06	S2b	BVLV_CTL_SVTIM;//ﾓｰﾄﾞ
//2015-09-06	S2b	BVLV_CTL_PVTIM;//
	S2b	BVLV_START_IN;	//2014-08- DRV_ACT_FLGだけではカバーできない部分

//	***********************************
//	***	2014-03-14		***
//	***	荷重制御		***
//	***********************************

	S4b	W4_PV_FLT_KJYU_TTL		;//ﾌｨﾙﾀ値 +/-
	S4b	W4_PV_FLT_KJYU_TTL_P		;//ﾌｨﾙﾀ値[ﾌﾟﾗｽのみ]
	S4b	W4_PV_CTL_KJYU_TTL_P		;//制御値=ﾌｨﾙﾀ値予定
//	-------------------------------
	S4b	KJYUCLS_OBJ_KN;		//各段の荷重目標
	S4b	KJYUCLS_KN_HENSA;	//荷重の偏差
	S4b	KJYUCLS_KN_HENSA_PLS;	//荷重の偏差相当のパルス

	//
	S4b	SETX_KJYUCLS_OBJ[100];
	S4b	CPOS_KJYUCLS_OBJ[100];


	S2b	FULCLS_MATHED;//0:位置 1:荷重
	S2b	SETX_FULCLS_MATEHD_SW;
	S2b	CPOS_FULCLS_MATEHD_SW;
	S2b	KJYU_CHK_NEARSIG;
	S2b	FULCLS_TIM_SETFLG;//BIT0:SET BIT1:ﾀｲﾑｱｯﾌﾟ()
//	2015-03-15[R01:2014-08-20]
	S2b	FULCLS_ELSE_STS;	//BIT0=0->1:初めての荷重制御開始

//


//	***********************************
//	***				***
//	***	外部起動釦処理		***
//	***				***
//	***********************************
	S2b	CB_IN_HANYO;//BIT8,9,10,11,12,13 6点(SQ004相当)
	S2b	EXTDRV_BTTN_USE;//SYSPARAM+各条件
	S2b	EXTDRV_UTINUKI_FLG;//打抜記憶

//	-----------------釦---------------
	S2b	EXT_BTTN_FLG;

//	---------------- 異常-------------
	S2b	EXTDRV_BTTN_ERR_TIM;
	





//	===================================
//	===				===
//	===	ﾄﾚﾝﾄﾞ用荷重ｶﾑ処理	===
//	===				===
//	===================================
	S2b	SET1_KAJAREA_SNO;
	S2b	SET1_KAJAREA_ENO;

	S2b	SET1_KJSTR_DIG2;	//359.0
	S2b	SET1_KJEND_DIG2;	//359.0

	S2b	SETX_KJSTR_DIG2;//往路
	S2b	SETX_KJEND_DIG2;//往路
	S2b	SETY_KJSTR_DIG2;//復路
	S2b	SETY_KJEND_DIG2;//復路
	S2b	SETC_KJSTR_DIG2;//演算
	S2b	SETC_KJEND_DIG2;//演算



	S2b	KJ_AREATRD_SIG;
	S2b	KJ_AREATRD_SIG_OLD;//2013-06-19
	S2b	SET1_KAJAREA_SEL;//ﾄﾚﾝﾄﾞ荷重表示選択0:(最大),1:(最小),2(幅)

//	===================================
//	===				===
//	===	型タッチ		===
//	===				===
//	===================================
	S2b	SET1_KATTCH_SAG;
	S2b	SET1_KATTCH_EAG;



//	===================================
//	===				===
//	===	荷重比較		===
//	===				===
//	===================================
	S2b	KJYU_CMP_CMD;		//BIT0=1 :ｵｰﾊﾞﾛｰﾄﾞ比較(区間内) BIT1=1ﾛｱﾘﾐｯﾄ比較(区間過)
//	S2b	KJYU_CMP_SELSW1;	//ｵｰﾊﾞﾛｰﾄﾞ項目選択
//	S2b	KJYU_CMP_SELSW2;	//ﾛｱﾘﾐｯﾄ項目選択
	S2b	CB_SEQ_SW_SEL058;

	S2b	KJYU_CMP_SEQMINS;	//最小値(ﾏｲﾅｽ側) ｵｰﾊﾞBIT0(左),BIT1(右),BIT2(合計)
					//最小値(ﾏｲﾅｽ側) ﾛｱ  BIT3(左),BIT4(右),BIT5(合計)
	S2b	KJYU_CMP_SEQHABA;	//幅             ｵｰﾊﾞBIT0(左),BIT1(右),BIT2(合計)
					//幅             ﾛｱ  BIT3(左),BIT4(右),BIT5(合計)

//cpuaのみ使用
	#include	"ssc_cop1psrm.inc"


//	===================================
//	===				===
//	===	EPｾﾝｻﾁｪｯｸ		===
//	===				===
//	===================================
	S2b	EPCHK_COM;//
	S2b	EPCHK_FLG;//BIT7=1 完了
	S2b	EPCHK_STEP;//
	S2b	EPCHK_DLY_TIM;//
	S2b	EPCHK_ERR_TIM;//
	S2b	EPCHK_RETRY_CNT;
	S2b	EPCHK_STS;
	S2b	EPCHK_FORCE_VONCMD;






//	===================================
//	===				===
//	===	ｽﾗｲﾄﾞ自動待機		===
//	===	2014-08-30		===
//	===================================
	S4b	POS_HLDSTOP1_CHKTIM;	//
	S2b	POS_HLDSTOP1_FLG;	//位置決め状態、準備未完了状態にて行う
					//BIT0=1:ﾎｰﾙﾄﾞ停止受付[自分停止ON または相手停止ON]
					//BIT1=1:停止完了(ﾀｲﾏ計測開始)
					//BIT2=1:
	S2b	POS_HLDSTOP1_SIG1TIM;	//20msecだけ再起動をONする
	S2b	POS_HLDSTOP1_SIG2TIM;	//20msecだけ通過時もしくは再起動時ONする[2015-02-20]
	//
	S2b	SET1_INTLIM_AGL;	//
	S2b	SET2_INTLIM_AGL;	//


	S4b	SET1_INTLIM_PLS;
	S4b	SET2_INTLIM_PLS;
	S4b	SETX_SDAT1_INTLIMOFS;//往路,回転,反転
	S4b	SETX_SDAT2_INTLIMOFS;//復路

	S4b	SETY_SDAT1_INTLIMOFS;//往路,回転,反転	[補正後の停止目標位置]
	S4b	SETY_SDAT2_INTLIMOFS;//復路		[補正後の停止目標位置]


//
	S4b	POSHLD1_STOPSPDWK[(100+10)];//ｽﾃｯﾌﾟ速度
	S2b	POSHLD1_STOP_STEPWK[(100+10)];//11個
	S2b	POSHLD1_STOP_STEP[(100+10)];//11個
//
	S4b	POSHLD1_GENSKPOSWK[(100+10)];//目標角度
	S4b	POSHLD1_SDAT1_HOLDPOS[2];//停止位置
	S4b	POSHLD1_SDAT2_HOLDPOS[2];//停止位置

	S2b	POSHLD1_GENSK_STEP;//表示用
	S2b	POSHLD1_CHKLST_FLG;//1:終了

	//
	S2b	POSHLD1_STOPLATCH;//停止前、停止中に停止釦相当が発生したか?

	//	--------2014-09-12-----------
	S4b	POSHLD_SET_DN_ACC;//位置決めキャンセル減速

//	===========================================
//	===	ｽﾗｲﾄﾞ自動待機を含めたhold処理	===
//	===========================================
	S2b	POS_HOLD_RESTARTCMD;
	S2b	POS_HOLD_CMD;
	S2b	POS_HOLD_FLG;
	S2b	POS_HOLD_RDY_EXITF;//しょうがない
	S2b	POS_HOLD_RDY_EXITF2;//しょうがない


//	===========================================
//	===					===
//	===========================================
	S2b	POS_HOLDABS_CALCF;




//	===========================================
//	===	調査用				===
//	===========================================
	S2b	MONI_RESET_STEP;
	S2b	MONI_RDY_STEP;
	S2b	MONI_SELF_STS1;
	S2b	MONI_SELF_STS2;


//	===================================================
//	===	異常後はじめての起動=位置プリセット	===
//	===================================================
	S2b	ERR_FIRST_ST;//異常時0000(RESET)


//	===========================
//	===	ｽﾌﾟｰﾙ異常	===
//	===	2014-09-16	===
//	===========================
	S2b	SPLCHK_FLG;//BIT0:ONﾗｯﾁ BIT1:OFFﾗｯﾁ
	S2b	SPLCHK_TIM;//ﾀｲﾏ

//	===========================================
//	===	ふりこ　どこからでも起動	===
//	===========================================
	S2b	DNM_RESET_AREA;//BIT7(左)/BIT4(右側)

//	===========================================
//	===	繰り返し工程			===
//	===========================================
	S2b	SET1_MOTREP_USEFUL	;//ROMﾊﾟﾗ及びSWの入/切(ROMPARAM,繰返回数,入/切)
					//非常停止時のみ設定変更が有効
	S2b	SET1_MOTREP_STGS	;//繰り返し開始行程 0,1~11,"*"
	S2b	SET1_MOTREP_STGE	;//繰り返し終了行程[この工程は停止工程とする]
	S2b	SET1_MOTREP_CNT		;//繰り返し回数


	S2b	REP_CAMOBJ_DIG		;//ｶﾑ用の戻り目標角度
	
	S4b	SET1_MOTREP_SPD		;//繰り返し戻り速度 PLS/S



//	===========================================
//	===	繰り返し工程カム		===
//	===========================================
	S2b	SET1_ROTCAM_ONR		;//ﾛｰﾀﾘｶﾑ ON行程 ﾘﾋﾟｰﾄ戻り
	S2b	SET1_ROTCAM_OFR		;//ﾛｰﾀﾘｶﾑ OFF行程 ﾘﾋﾟｰﾄ戻り
	S2b	SET1_EJECAM_ONR		;//ｴｼﾞｪｸﾀ ON行程 ﾘﾋﾟｰﾄ戻り
	S2b	SET1_EJECAM_OFR		;//ｴｼﾞｪｸﾀ OFF行程 ﾘﾋﾟｰﾄ戻り
	S2b	SET1_MISCAM_ONR		;//ﾐｽﾌｨｰﾄﾞON行程 ﾘﾋﾟｰﾄ戻り
	S2b	SET1_MISCAM_OFR		;//ﾐｽﾌｨｰﾄﾞOFF行程 ﾘﾋﾟｰﾄ戻り

//	---------------ﾓｰｼｮﾝ(MOT)繰り返し機能(REP)-----------------------
	S2b	SETX_MOTREP_DIR		;//設定上どっちの方向　  1:-1
	S2b	DNM_SETX_MOTREP_DIR	;//設定上どっちの方向　  1:-1
	S2b	NOW_MOTREP_DIR		;//動作                0:(非動作)1:(正転)-1:(逆転)

	S2b	MOT_REP_F		;//BIT0(ﾘﾋﾟｰﾄ動作
	S2b	MOT_REP_CNT		;//


//	===========================================
//	===	速度一定			===
//	===========================================
//	画面での変更

//	===========================================
//	===	寸動どこからでも起動		===
//	===	2014-09-25			===
//	===========================================
	S2b	INC_RESET_STEP;	//0,1 ->
	S2b	INC_RESET_USE_F;//STEPを参照して!


//	-------2014-11-07----------------------------
	S2b	MOVE_MODE_MATH_LATCH;	//0:(ふりこ以外 または 段取・原点モード)1:(ふりこでﾓｰｼｮﾝしていた)
	S2b	DNM_DIR_FLG_INC_LATCH;	//ふりこの場合の前回までの動作方向

//	***********************************
//	***				***
//	***	2016-11-16		***
//	***				***
//	***********************************
	S2b	CAM_DNM_USE_DIR_FLG;	//カムとしての動作方向



//	***********************************
//	***	cpud,cpub正常動作ﾁｪｯｸ	***
//	***	2015-01-21		***
//	***********************************
	S2b	CPUD_CHK_OLDCNT;
	S2b	CPUD_CHK_TIME;

	S2b	RM1_CHK_OLDSTS;
	S2b	RM1_CHK_TIME;

	S2b	RM2_CHK_OLDSTS;
	S2b	RM2_CHK_TIME;

	S2b	CPUABD_WDTOK_FLG;


//	*******************************************
//	***					***
//	***	2015-02-10			***
//	***					***
//	*******************************************
	S2b	SPL_ERR_INIT_WAIT_TIM;


//	荷重
	S4b	W4_PVP_KAJLIV_TTL		;//荷重生（TON）(2word)





//	*******************************************
//	***					***
//	***	2015-04-08			***
//	***	ﾃﾞﾊﾞｯｸﾓｰﾄﾞ			***
//	***					***
//	*******************************************
	S2b	DEBUG_MOD_CODE;	//5AA5

	S2b	DBG_ATO_DRV_START_FLG;
	S2b	DBG_ATO_DRV_TIME_PV;
	S2b	DBG_ATO_DRV_TIME_SV;

//	2016-10-31
//	_PROC_CMPERR_CHG2016

	S2b	DBG_ATO_DRV_TIME_PV2;//2016-07-15
	S2b	DBG_ATO_DRV_TIME_SV2;//2016-07-15



//	*******************************************
//	***					***
//	***	2015-04-08			***
//	***	寸動含む工程終了ﾊﾝﾄﾞｼｪｲｸ	***
//	***					***
//	*******************************************
	S2b	ENDHAND_TIMOUT_PV;


//	*******************************************
//	***	2015-05-20			***
//	*******************************************
	S2b	INSERT_MOT_SV_CHGF;
//2015-10-26	S2b	DUM_SET1_SPD_TOP[100];


//	-----------2015-06-22----------
	S2b	SETX_KJYU_INCPOS_KP01	;

//	==========2015-07-14=======================
//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***					***
//	*******************************************
	S2b	PON_ERR_WAIT_TIM;//5秒

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***					***
//	*******************************************
//	CPUAはCPUCを
//	CPUCはCPUAを
	S2b	DPCHK_ERR_SIG;			//BIT0(WDT),BIT1(DI)
	S2b	DPCHK_CPU_ERR_TIM;		//
	S2b	DPCHK_WR_COD;			//


//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***					***
//	*******************************************
	S2b	DPCHK_DI_ERR_TIM;		//二重回路２ 10msec


//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	CPUC側ﾊﾟﾗﾒｰﾀSEND		***
//	***					***
//	*******************************************
	S2b	CPUX_PARAM_SEND_FLG;//1~512:512まで送ったら終了
	S2b	CPUX_PARAM_SEND_NO;//1~512

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	CPUA側受信			***
//	***					***
//	*******************************************
//	送信ﾜｰﾄﾞ毎にﾍﾞﾘﾌｧｲﾁｪｯｸする
	S2b	CPUC_PARAM_ERR_NO;//ﾍﾞﾘﾌｧｲ異常
	S2b	CPUB_PARAM_ERR_NO;//ﾍﾞﾘﾌｧｲ異常

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	不一致				***
//	***					***
//	*******************************************
	S4b	LSI_LOAD_PLS;

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	遮光停止３			***
//	***					***
//	*******************************************
	S2b	SFTYCHK_CLANK_DEG;
	S4b	SFTYCHK_LINK_PLS;

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	パルス停止			***
//	***					***
//	*******************************************
//	モーション運転
//		最終行程の払出完了時のエンコーダ値記憶
//
	S4b	PLSOUTEND_PVPLS[2];	//
	S2b	PLSOUTEND_SHIN;		//
	S2b	PLSOUTEND_FLG;		//BIT6=1:停止監視状態 (BIT0=1:払出有)

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	終了時のﾓｰﾀ停止までの遅延	***
//	***	PAR_MYU_BRK_SEL==1		***
//	***					***
//	*******************************************
	S2b	POS_END_WAIT_TIM;


//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	終了時				***
//	***	PAR_MYU_BRK_SEL==0		***
//	***					***
//	*******************************************
	S2b	POS_END_MYUTIG_STOPTIM;//終了後この時間であれば動力遮断する時間
	S2b	POS_END_MYUTIG_KEEPTIM;//終了後上昇無効を継続する時間


//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***					***
//	*******************************************
	U2b	UPHOLD_SPDERR_OK_FLG;

//	*******************************************
//	***					***
//	***	2015-07-14			***
//	***	逆転異常2			***
//	***					***
//	*******************************************
	U2b	REV_ERR_FLG;		//BIT0=1:上昇ﾎｰﾙﾄﾞにて起動
					//BIT1=1:ｲﾝﾎﾟｼﾞｼｮﾝに入った
					//BIT4=0(正)/1(逆) 方向
	U4b	REV_ERR_LT_PGPOS[2];	//
	U4b	REV_ERR_LT_SVPOS[2];	//





//	***********************************
//	***		2015-05-19	***
//	***********************************
	U2b	EPCHK_STOP_DISENB;




//	***********************************
//	***				***
//	***	2015-08-12 ﾃﾞﾊﾞｯｸﾓﾆﾀ	***
//	***				***
//	***********************************
	U2b	WK_DBG2B_B_MONI[8];	//

//	***********************************
//	***				***
//	***	2015-08-12 CPUD ANALOG	***
//	***				***
//	***********************************
//_CPUD_PV_AD2		.SRES	2		;移動平均8回後
//_CPUD_PV_AD3		.SRES	2		;移動平均8回後
//_CPUD_PV_AD4		.SRES	2		;移動平均8回後
	U2b	PVX_CPUD_AD2;//補正
	U2b	PVX_CPUD_AD3;//補正
	U2b	PVX_CPUD_AD4;//補正



//	***********************************
//	***				***
//	***	2015-09-30		***
//	***	100段数仕様(98段)	***
//	***				***
//	***********************************
//	dpramを一旦受ける
	U2b	SYS_STEP_MAX;		//10,11~98

	U2b	SYS_100STEP_USE;	//100段ﾊﾝﾄﾞｼｪｲｸ使用する
	U2b	SYS_100STEP_DNM_SEL;	//100段時の振子

	U4b	SVPX1_OBJECT_POS_TOP[100];	//目標位置
	U2b	SVPX1_OBJECT_DIG_TOP[100];	//目標角度
	U2b	SVPX1_OBJECT_SPD_TOP[100];	//目標速度
	U2b	SVPX1_OBJECT_TIM_TOP[100];	//停止時間
	U2b	SVPX1_OBJECT_PRS_TOP[100];	//目標圧力
	U2b	SVPX1_MOT_INF[100];		//ﾓｰｼｮﾝ情報bit0(位置/荷重)
	U2b	SVPX1_FED_DEG[100];		//ﾌｨｰﾀﾞ角度(予備)
	U4b	SVPX1_FED_POS[100];		//ﾌｨｰﾀﾞ位置(予備)



//	*******************************************
//	***					***
//	***		2015-10-22		***
//	***					***
//	*******************************************
//	方式,段数,位置,タイマ＝０／０以外 ->EMG有り
//	速度				  ->EMG無し
//	タイマ				  ->EMG無し
//	オーバライド設定変更		  ->EMG無し
//	***********************************
//	***				***
//	***	2015-09-30		***
//	***	100段数仕様(98段)	***
//	***	リミット表示		***
//	***				***
//	***********************************
	U2b	MOTION_CHK_START_FLG;		//2:ﾃﾞｰﾀCHK開始 0:ﾃﾞｰﾀﾁｪｯｸ終了

	U2b	xxxxxxx;
	U2b	PVPX1_CKLMT_AGLTOP[100];	//cpua=>cpud 角度ﾘﾐｯﾄ [0:1段目]
	U2b	PVPX1_CKLMT_SPDTOP[100];	//cpua=>cpud 速度ﾘﾐｯﾄ [0:1段目]
	U2b	WK_PVP_MOT_STS[100];		//[0:1段目]
						//BIT0:速度赤丸　CKSPD_OVBT
						//BIT1:角度赤丸　CKAGL_OVBT
						//BIT2:青丸表示　LMBIT
						//BIT3:青丸入力制限を行って CKSPD_STPBT









//	***********************************
//	***				***
//	***	2015-09-30		***
//	***	100段数仕様(98段)	***
//	***	(CPUA,B共通処理)	***
//	***				***
//	***********************************







//	***********************************
//	***				***
//	***	2015-10-14		***
//	***	MTS温度読み出し		***
//	***				***
//	***********************************
//	
	U2b	X_PROTCOL_TMP_FLG;	//
	U2b	X_PROTCOL_TMP_PV2;	//通信ﾃﾞｰﾀ1ﾊﾞｲﾄ
	S2b	X_PROTCOL_TMP_SVLNG;	//補正量設定+/-
	S2b	X_PROTCOL_TMP_PVLNG;	//補正量
	U4b	X_PROTCOL_TMP_LNG_SVTM;	//補正測定時間SV
	U4b	X_PROTCOL_TMP_LNG_PVTM;	//補正測定時間PV

//
	U2b	X_PROTCOL_TMP_EVENTCNT;	//
	U2b	X_PROTCOL_TMP_TIME_PV;	//(ﾀｲﾑｱｳﾄ)

//	-------- 通信部側--------------
	U2b	X_PROTCOL_TMP_REQ;	//REQ:1:START
	U2b	X_PROTCOL_TMP_ANS;	//ANS:1:END(nomaL) -1:END(err)
	U2b	X_PROTCOL_TMP_PV1;	//通信ﾃﾞｰﾀ1ﾊﾞｲﾄ

	U2b	TMP_SCI_DEBUG[16];



//	***************************
//	***	2015-10-26	***
//	***************************
//	データ変更に対するイベント発生を一元化
//	DUMはﾃﾞｰﾀ変更,CHKは異常検出
	S2b	DUM_SET1_UPAREA_SPD0;
	S2b	DUM_SET1_SPD_TOP[100];
	S2b	DUM_OVERLIDE_COF		;

	U2b	CHK_SET1_UPAREA_TIM0		;//4	;待機時間
	U4b	CHK_OBJECT_TIM_TOP[100]		;//40=>100 4BYTE SET1_OBJECT_TM01;01段目停止時間 99.99*10=1msec




//	***********************************
//	***				***
//	***	2015-11-17		***
//	***	低速優先		***
//	***				***
//	***********************************
//	(ﾒﾓﾘは各段指定と共通化しない)
	S4b	ACCLW_SET_SPD;		//INPUT モーション演算部からの速度 (オーバライド前)
	S4b	ACCLW_REAL_SPD1MS;	//
	S2b	ACCLW_USE_CONF;		//BIT0:非運転中に決定される条件
					//

	S2b	ACCLW_CALC_FLG;		//BIT0:起動[API]
					//BIT1:
					//BIT6:[減速開始]
					//BIT7:演算完了[停止行程まで演算不要：もう低速設定がない]
	S2b	ACCLW_GET_STEP_NO;	//BIT1=1時の対象行程
	S4b	ACCLW_GET_SET_SPD;	//BIT1=1時の対象速度
	S4b	ACCLW_OUT_SET_SPD;	//出力速度
	S4b	ACCLW_GEN_MAX_LNG;	//最大速度時減速距離+最大速度/1000

//	***********************************
//	***				***
//	***	2016-04-18		***
//	***	各段加減速方式指定	***
//	***				***
//	***********************************
//	(ﾒﾓﾘは低速優先と共通化しない)
	S4b	ACCST_SET_SPD;		//INPUT モーション演算部からの速度 (オーバライド前)
	S4b	ACCST_REAL_SPD1MS;	//

	S2b	ACCST_USE_CONF;		//BIT0:非運転中に決定される条件
	S2b	ACCST_CALC_FLG;		//BIT0:起動[API]
					//BIT1:
					//BIT6:[減速開始]
					//BIT7:演算完了[停止行程まで演算不要：もう低速設定がない]
	S2b	ACCST_GET_STEP_NO;	//BIT1=1時の対象行程
	S2b	ACCST_ACC_MATH_SEL;	//BIT0=0(後変則)/1(前変則)
					//BIT1=0(加速)/1(減速):設定レベル
	S4b	ACCST_GET_SET_SPD;	//BIT1=1時の対象速度
	S4b	ACCST_OUT_SET_SPD;	//出力速度
	S4b	ACCST_GEN_MAX_LNG;	//最大速度時減速距離+最大速度/1000
	





//	*******************************************
//	***					***
//	***	2016-04-16 段取速度指定		***
//	***					***
//	*******************************************
	U2b	CB_SEQ_CB_COM356;//


//	*******************************************
//	***					***
//	*******************************************
	U2b	SET1_MOT_INF[100];		//ﾓｰｼｮﾝ情報bit0(位置/荷重)
	U2b	MOTION_SPD_CHKCNT;





//	*******************************************
//	***					***
//	***	2016-04-15			***
//	***	2016-01-10			***
//	***	行程二重回路のリカバー		***
//	***	ハンドシェイク時の行程のみ実行	***
//	***					***
//	*******************************************
	S2b	EXQ_LT_GET_FLG;	//
	S2b	EXQ_LT_CMPSTEP_STEP_END;//HAND_STEP2_FLG;	//STEP2ﾗｯﾁ
	S2b	EXQ_LT_PROC_CNT1;
	S2b	EXQ_LT_PROC_CNT2;
	S2b	EXQ_LT_PROC_CNT3;
	S2b	EXQ_LT_PROC_CNT4;

//	2016-10-31
//	_PROC_CMPERR_CHG2016
//	***************************************************
//	***						***
//	***	2016-10-31(2016-05-08)			***
//	***	位置決めキャンセルによる行程リカバー	***
//	***						***
//	***************************************************
	S2b	POSCANSEL_CMD;//
	S2b	DNM_RST_SPEC_AREASIG;//2016-10-31(2016-06-21)


//	***************************************************
//	***						***
//	***	2016-10-31(2016-06-13)			***
//	***	振り子処理調査				***
//	***						***
//	***************************************************
	S2b	DBG_DNM_STR_CNT;
	S2b	DBG_DNM_END_CNT;
	S2b	DBG_DNM_CLR_CNT;

//	***************************************************
//	***						***
//	***	2016-10-31(2016-06-21)			***
//	***	行程２重回路調査			***
//	***						***
//	***************************************************
	S2b	STEP_CMPERR_TIMX1;


//	***************************************************
//	***	2016-10-31(2016-08-11)			***
//	***	連続停止釦対策				***
//	***************************************************
	S2b	CNT_STOP_WAIT_TIM;
	S2b	CNT_STOP_DBG_CNT;//2016-08-22 CHECK


//	*******************************************
//	***			2018-02-10 ﾃﾞﾊﾞｯｸ			***
//	*******************************************
	S2b		DEBUG_STS_CNT1;
	S2b		DEBUG_STS_CNT2;







