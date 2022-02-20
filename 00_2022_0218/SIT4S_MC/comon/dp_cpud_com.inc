;	*******************************************************************
;	***								***
;	***								***
;	***		CPUD<=>CPUA					***
;	***		CPUD<=>CPUB					***
;	***								***
;	***								***
;	***								***
;	*******************************************************************
;
;	*******************************************
;	***					***
;	***	SH2→SH4　ﾊﾝﾄﾞｼｪｲｸ		***
;	***					***
;	*******************************************
		.ORG	H'0000
_HS_SVCHG_B_TO_A	.SRES	4
_SH2_PDOWN_FLG		.SRES	2	;
_SH2_AD_DATA		.SRES	2	;
_SH2_MAIN_CLK		.SRES	2	;
_CPUD_START_COD		.SRES	2	;CPUD=>H'9876 CPUA,CPUB=H'4321 2013-12-10 [MC]

	.ALIGN	4			;
_SH2_DBG_KAGEN		.SRES	4	;

;	*******************************************
;	***					***
;	***	SH2←SH4　ﾊﾝﾄﾞｼｪｲｸ		***
;	***		(2010-12-08)		***
;	*******************************************
		.ORG	H'0040
;;;;;;;;;[[[仮2013-12-02]]]_DP_COP_CB_LD_MONI_SIG	.SRES	2	;SH4-->SH2へ渡す

;	*******************************************
;	***					***
;	***	SH2←SH4　ﾊﾝﾄﾞｼｪｲｸ		***
;	***					***
;	*******************************************
		.ORG	H'0080
_HS_SVCHG_A_TO_B	.SRES	4
_HS_PVP_TAKIKI_FLG	.SRES	2	;//待機点通過ﾌﾗｸﾞ 1ｾｯﾄはSH4　0CLRはSH2(HMI部)
_HS_PVP_LOTCNT_FLG	.SRES	2	;

_KEEPRY_BKUP_FLG	.SRES	2	; ｷｰﾌﾟﾘﾚｰ取り込み許可ﾌﾗｸﾞ
_SH4_PDOWN_FLG		.SRES	2	;2003-01-27
_CB_STS_SAVE_FLG	.SRES	2	;2003-07-01
_CB_TRD_SAVE_FLG	.SRES	2	;2003-07-01 1234=>WR SH4 CLR SH2

;	==== 2003-07-09 ===
_CMD_1CYCLE_DSP1	.SRES	2	;2003-07-09 1ｻｲｸﾙ速度/時間 0:非表示　1:表示
_CMD_DAIPOS_DSP1	.SRES	2	;2003-07-09 生産下限位置　 0:非表示　1:表示
	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_GPOINT_LNG		.SRES	4	;減速距離をCPU-Bに教えるCPU-Bはこれにあわせる(連続時)
;;;;;;;;;[[[仮2013-12-02]]]_SH2_GPOINT_LNG		.SRES	4	;減速距離をCPU-Bに教えるCPU-Bはこれにあわせる(連続時)
;;;;;;;;;[[[仮2013-12-02]]]_SH4_GPOINT_LNGDSP	.SRES	4	;表示用2004-12-20
;;;;;;;;;[[[仮2013-12-02]]]_SH2_GPOINT_LNGDSP	.SRES	4	;表示用
;;;;;;;;;[[[仮2013-12-02]]]_SH4_GPOINT_SPDDSP	.SRES	4	;表示用2004-12-20
;;;;;;;;;[[[仮2013-12-02]]]_SH2_GPOINT_SPDDSP	.SRES	4	;表示用

_CMD_KJTECH_DSP1	.SRES	2	;2006-12-05 1:荷重補正のﾃｰﾁﾝｸﾞ可能

	.ALIGN	4			;2007-03-18
_PSD_ORG_PLS1		.SRES	4	;ORIGIN DATA(FUNUC)
_PSD_ORG_PLS2		.SRES	4	;ORIGIN DATA(FUNUC)
_PSD_ORG_PLS_CMD1	.SRES	2	;
_PSD_ORG_PLS_CMD2	.SRES	2	;

	.ALIGN	4			;2007-0-18
_HD_CMP_RNA_A1		.SRES	4	;0:00BC=0:0188
_HD_CMP_RNA_B1		.SRES	4	;0:00C0=0:0192
_HD_CMP_RNA_C1		.SRES	4	;0:00C4=0:0196
_HD_CMP_RNA_C2		.SRES	4	;0:00C8=0:0200
_XHD_CMP_PLS_A1		.SRES	4	;0:00CC=0:0204
_XHD_CMP_PLS_B1		.SRES	4	;0:00D0=0:0208
_HD_CMP_PLS_C1		.SRES	4	;0:00D4=0:0212
_HD_CMP_PLS_C2		.SRES	4	;0:00D8=0:0216
_HD_CMP_TRQ_A1		.SRES	4	;0:00DC=0:0220 
_HD_CMP_TRQ_B1		.SRES	4	;0:00E0=0:0224
_HD_CMP_TRQ_C1		.SRES	4	;0:00E4=0:0228 OK
_HD_CMP_TRQ_C2		.SRES	4	;0:00E8=0:0232 OK

;---- 2012-12-10 ふりこ加速時間=> 2013-02-08 未使用なので内部原点復帰に変更---
_aaa			.SRES	2	;EC 原点復帰方向


;;;;;;;;;[[[仮2013-12-02]]];	----- 2013-06-19----------
;;;;;;;;;[[[仮2013-12-02]]]_SH4toSH2_TEPSIG	.SRES	2	;EE
;;;;;;;;;[[[仮2013-12-02]]]_SH2toSH4_TEPSIG	.SRES	2	;F0

;	----- 2013-07-18----------
_SH2_SCAN_REALMAX	.SRES	2	;F2
_SH2_SCAN_AVLMAX	.SRES	2	;F4
_SH2_SCAN_AVLPV		.SRES	2	;F6

;	*******************************************
;	***					***
;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾌﾗｸﾞ領域 SH2-->SH4	***
;	***					***
;	*******************************************
		.ORG	H'0100
_VUP_HSAREA_B_TO_A		.SRES	4*32

;	*******************************************
;	***					***
;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾌﾗｸﾞ領域 SH2<--SH4	***
;	***					***
;	*******************************************
		.ORG	H'0200
_VUP_HSAREA_A_TO_B		.SRES	4*32

;	***************************************************
;	***						***
;	***	HMI(SH2-->SH4) 設定/ﾊﾟﾗﾒｰﾀ等領域	***
;	***	このORG H'1000~ORG H'2FFF領域は		***
;	***	ﾊﾞｰｼﾞｮﾝｱｯﾌﾟﾃﾞｰﾀに使用される		***
;	***						***
;	***************************************************
;
;	***************************************************
;	***	ｼｰｹﾝｽKEEP RY ﾊﾞｯｸｱｯﾌﾟ返し領域		***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]].ORG	H'1000
		.ORG	H'300
_VUP_DATA_ADR_OP1					;H'2000(ﾊﾞｰｼﾞｮﾝｱｯﾌﾟ領域として共用で仕様)
;	***************************************************
;	***	4/2BYTE  ﾊﾞｯｸｱｯﾌﾟ返し領域(64b)		***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'1080
	.ALIGN	4
_SVB_RNAORG_PLS1	.SRES	4		;ﾘﾆｱ基準位置ﾊﾟﾙｽ
						;予備4byte領域
_SVB_DYHITO_POS		.SRES	4		;2003-07-09 ﾀﾞｲﾊｲﾄ(下限位置)
_SVB_SLIDE_POS		.SRES	4		;2003-07-09 生産下限位置

_SVB_BAKORG_PLS1	.SRES	4		;ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2BAKUP
_SVB_BAKORG_PLS2	.SRES	4		;ﾘﾆｱ基準位置ﾊﾟﾙｽ	COP2BAKUP
						;2006-10-22
_SVB_RENIA_BUP1		.SRES	4		;//360角度相当ﾊﾟﾙｽ1
_SVB_RENIA_BUP2		.SRES	4		;//360角度相当ﾊﾟﾙｽ2
_SVB_RENIA_BUP3		.SRES	4		;//360角度相当ﾊﾟﾙｽの反転(SUM1)
_SVB_RENIA_BUP4		.SRES	4		;//360角度相当ﾊﾟﾙｽの反転(SUM2)

;	---------- 2006-12-05 荷重補正用荷重(平均値ﾊﾞｯｸｱｯﾌﾟ)----------
_SVB_ARA1_KAJ_T2	.SRES	2		;区間最大荷重TOTALのみ使用


;	***************************************************
;	***	2BYTE  ROMﾊﾟﾗﾒｰﾀ領域			***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'1100
	.ALIGN	4
_SVP_RPARAM_TOP1		.SRES	256	;ROMﾊﾟﾗﾒｰﾀ領域
						;
;	***************************************************
;	***	ｻｰﾎﾞﾊﾟﾗﾒｰﾀ領域	4/2BYTE領域		***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'1200
	.ALIGN	4
_SVP_RNADIR_SEL1		.SRES	2	;NO.10 ﾘﾆｱｾﾝｻ極性
_SVP_INCDIR_SEL1		.SRES	2	;NO.11 PG極性
_SVP_INCPLS_1REV		.SRES	2	;NO.12 PG1回転のﾊﾟﾙｽ選択
_SVP_INCPLS_HOSN		.SRES	2	;NO.13 PG補正N　ﾓｰﾀN回
_SVP_INCPLS_HOSM		.SRES	2	;NO.14 PG補正M　ｸﾗﾝｸ角度M
_SVP_MOTRPM_MAXM		.SRES	2	;NO.15 ﾓｰﾀ最大回転数

	.ALIGN	4				;
_SVP_MOTMAX_FREQ		.SRES	4	;NO.16 ﾓｰﾀ最大時指令周波数(ふりこの目標位置ｲﾝﾎﾟｼﾞｼｮﾝ　2009)
_SVP_RNAORG_POS1		.SRES	4	;NO.17 機械原点入力
_SVP_RNAPOS_MAXP		.SRES	4	;NO.19 機械上限
_SVP_RNAPOS_MINP		.SRES	4	;NO.1A 機械下限
_SVP_UPAREA_JUDG		.SRES	4	;NO.40 上死点判定範囲
_SVP_DNAREA_JUDG		.SRES	4	;NO.41 反転設定不可範囲



_SVP_DNDINC_SPD1		.SRES	2	;NO.20 段取速度()
_SVP_UPAREA_SPD1		.SRES	2	;NO.21待機点復帰速度	
_SVP_STDINC_SPD1		.SRES	2	;NO.22寸動速度→ﾌﾞﾚｰｷﾁｪｯｸの移動速度[2006-04-10]
_SVP_REVDAT_SPD1		.SRES	2	;NO.23予備速度１	(クリープ速度)
_SVP_REVDAT_SPD2		.SRES	2	;NO.24予備速度２	(自起動)
_SVP_REVDAT_SPD3		.SRES	2	;NO.25予備速度３	(ﾌﾙｸﾛｰｽﾞ時のｲﾝﾁﾝｸﾞ)
_SVP_TEPDAT_SPD1		.SRES	2	;手動ﾊﾟﾙｻ速度	
_SVP_TEPLAT_DAT1		.SRES	2	;手動ﾊﾟﾙｻ低倍率	→ﾌﾞﾚｰｷ遅延時間
_SVP_TEPLAT_DAT2		.SRES	2	;手動ﾊﾟﾙｻ高倍率	→ﾌﾞﾚｰｷ加速時間

_SVP_INCPOS_KP01		.SRES	2	;NO.30 PG位置比例ｹﾞｲﾝ
_SVP_RNAPOS_KP01		.SRES	2	;NO.31 ﾘﾆｱ位置比例ｹﾞｲﾝ
_SVP_ACCLAT_TIM1		.SRES	2	;NO.32 加減速時間
_SVP_SSCURV_TIM1		.SRES	2	;NO.34 33?Ｓ字時間
_SVP_UPAREA_INP1		.SRES	2	;NO.33 34?上死点ｲﾝﾎﾟｼﾞｼｮﾝ→ﾌﾞﾚｰｷｾﾙﾌﾁｪｯｸの移動距離[2006-4-10]
_SVP_DNAREA_INP1		.SRES	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ(追い込み量に変更)
_SVP_OBJARA_INP1		.SRES	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ
_SVP_INPPOS_TIM1		.SRES	2	;ｲﾝﾎﾟｼﾞｼｮﾝﾁｪｯｸ時間
_SVP_ARACHK_LNG1		.SRES	2	;上／下死点通過判定量
_SVP_UPAREA_DIG1		.SRES	2	;回転時待機点(上死点)

_SVP_INCHEN_ELNG		.SRES	2	;PG偏差異常幅
_SVP_INCENC_ELNG		.SRES	2	;PG-ENC一致量 0.1度
_SVP_INCRNA_ELNG		.SRES	2	;PG-ﾘﾆｱ一致量
_SVP_INCSTP_ELNG		.SRES	2	;PG停止異常量
_SVP_RNASTP_ELNG		.SRES	2	;ﾘﾆｱ停止異常量
_SVP_INCREV_ELNG		.SRES	2	;PG逆転異常量
_SVP_RNAREV_ELNG		.SRES	2	;ﾘﾆｱ逆転異常量
_SVP_DAIHAI_LNG1		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(小)
_SVP_DAIHAI_LNG2		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(中)
_SVP_DAIHAI_LNG3		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(大)

_SVP_AMPERR_VLT1		.SRES	2	;過負荷電圧1
_SVP_AMPERR_TIM1		.SRES	2	;過負荷時間1
_SVP_AMPERR_VLT2		.SRES	2	;過負荷電圧2
_SVP_AMPERR_TIM2		.SRES	2	;過負荷時間2
_SVP_AMPERR_VLT3		.SRES	2	;過負荷電圧3
_SVP_AMPERR_TIM3		.SRES	2	;過負荷時間3

;	==== 2002-08-08 ==
_SVP_CNT_TIM			.SRES	2	;連続タイマ
_SVP_CNT_CNT			.SRES	2	;連続カウンタ
_SVP_BREAK_DIG			.SRES	2	;ﾌﾞﾚｰｷ角度   0.1度
_SVP_BREAK_TIM1			.SRES	2	;ブレーキタイマ設定
_SVP_WT_DIG1			.SRES	2	;待機点選択1
_SVP_WT_DIG2			.SRES	2	;待機点選択2
_SVP_WT_DIG3			.SRES	2	;待機点選択3
_SVP_MOTWT_TIM			.SRES	2	;起動保証時間
_SVP_PSMOD_SEL			.SRES	2	;PSID　ﾓｰﾄﾞ選択

;	==== 2002-08-21 ==
	.ALIGN	4				;
_SVP_RNA_STLORK			.SRES	4	;
_SVP_OUTPLS_HOSA		.SRES	2	;NO.44 出力パルス補正0or1->2011-02-19[反転制御]
_SVP_OUTPLS_HOSB		.SRES	2	;NO.45 出力パルス補正0or1->2011-02-19[反転制御]→未使用
_SVP_UPHOLD_DIG			.SRES	2	;NO.46上昇ホールド
_SVP_MACINE_SEL1		.SRES	2	;NO.47機種

;	==== 2003-01-27 ==
	.ALIGN	4				;
_SVP_NEG_OFS_LNG		.SRES	4	;反転下限距離(0.001mm ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
_SVP_AMP100P_VLT		.SRES	2	;AMP100%相当時の電圧値 0~10.0v(ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	.ALIGN	4				;
_SVP_LSAABN_AGL1		.SRES	4	;//LSA異常検知の角度1
_SVP_LSAABN_AGL2		.SRES	4	;//LSA異常検知の角度2
_SVP_PLSALO_PLS			.SRES	2	;//パルサ倍率低
_SVP_PLSAHI_PLS			.SRES	2	;//パルサ倍率高
_SVP_SMPSTR_KAJ			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ荷重
_SVP_SMPSTR_AGL			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ角度
_SVP_SMPSTR_FUK			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞ負荷率
_SVP_SMPSTR_SEH			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（上位ｱﾄﾞﾚｽ）
_SVP_SMPSTR_SQL			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾄﾘｶﾞｼｰｹﾝｽ（下位ｱﾄﾞﾚｽ）
_SVP_SMPMAX_CNT			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　最大個数
_SVP_SMPTRG_CNT			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数
_SVP_SMPCYC_TIM			.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　周期
_SVP_MOADR0_SQH      .SRES        2           ; モニタアドレス０　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR0_SQL      .SRES        2           ; モニタアドレス０　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR1_SQH      .SRES        2           ; モニタアドレス１　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR1_SQL      .SRES        2           ; モニタアドレス１　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR2_SQH      .SRES        2           ; モニタアドレス２　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR2_SQL      .SRES        2           ; モニタアドレス２　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR3_SQH      .SRES        2           ; モニタアドレス３　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR3_SQL      .SRES        2           ; モニタアドレス３　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR4_SQH      .SRES        2           ; モニタアドレス４　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR4_SQL      .SRES        2           ; モニタアドレス４　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR5_SQH      .SRES        2           ; モニタアドレス５　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR5_SQL      .SRES        2           ; モニタアドレス５　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR6_SQH      .SRES        2           ; モニタアドレス６　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR6_SQL      .SRES        2           ; モニタアドレス６　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR7_SQH      .SRES        2           ; モニタアドレス７　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR7_SQL      .SRES        2           ; モニタアドレス７　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR8_SQH      .SRES        2           ; モニタアドレス８　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR8_SQL      .SRES        2           ; モニタアドレス８　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADR9_SQH      .SRES        2           ; モニタアドレス９　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADR9_SQL      .SRES        2           ; モニタアドレス９　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRA_SQH      .SRES        2           ; モニタアドレス１０　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRA_SQL      .SRES        2           ; モニタアドレス１０　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRB_SQH      .SRES        2           ; モニタアドレス１１　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRB_SQL      .SRES        2           ; モニタアドレス１１　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRC_SQH      .SRES        2           ; モニタアドレス１２　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRC_SQL      .SRES        2           ; モニタアドレス１２　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRD_SQH      .SRES        2           ; モニタアドレス１３　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRD_SQL      .SRES        2           ; モニタアドレス１３　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRE_SQH      .SRES        2           ; モニタアドレス１４　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRE_SQL      .SRES        2           ; モニタアドレス１４　ｼｰｹﾝｽ下位　V01v　060713
_SVP_MOADRF_SQH      .SRES        2           ; モニタアドレス１５　ｼｰｹﾝｽ上位　V01v　060713
_SVP_MOADRF_SQL      .SRES        2           ; モニタアドレス１５　ｼｰｹﾝｽ下位　V01v　060713

;	=== 2006-11-20 ===	SHIMA(HMI:V01z)
_SVP_SMP_CNT		.SRES	2		;ｻﾝﾌﾟﾘﾝｸﾞ収集形式　毎
_SVP_TRD_CNT		.SRES	2		;ﾄﾚﾝﾄﾞ収集形式　毎

;	=== 2008-10-15 ===	SHIMA(HMI:V05l)
_SVP_ATCOL_CYC       .SRES        2           ; 自動収集条件　周期
_SVP_ATCOL_STNO      .SRES        2           ; 自動収集条件　収集範囲　開始行程
_SVP_ATCOL_STAG      .SRES        2           ; 自動収集条件　収集範囲　開始角度
_SVP_ATCOL_SPNO      .SRES        2           ; 自動収集条件　収集範囲　終了行程
_SVP_ATCOL_SPAG      .SRES        2           ; 自動収集条件　収集範囲　終了角度

;	=== 2009-08-26 ===	SHIMA(HMI:V05o)
	.ALIGN 4
_SVP_TRDCSR_RNAU		.SRES	4		;/* ｽﾗｲﾄﾞ上限検出位置	*/
_SVP_TRDCSR_RNAD		.SRES	4		;/* ｽﾗｲﾄﾞ上限検出位置	*/ 
_SVP_SMPTRG_CNT1		.SRES	2		;//  ｻﾝﾌﾟﾘﾝｸﾞ　ﾌﾟﾘﾄﾘｶﾞ個数（SIT用）

;	=== 2009-10-05(多段の荷重設定) ====    HMI
_SVP_OBJECT_PRS_TOP:
_SVP_OBJECT_PRS01	.SRES	2	;
_SVP_OBJECT_PRS02	.SRES	2	;
_SVP_OBJECT_PRS03	.SRES	2	;
_SVP_OBJECT_PRS04	.SRES	2	;
_SVP_OBJECT_PRS05	.SRES	2	;
_SVP_OBJECT_PRS06	.SRES	2	;
_SVP_OBJECT_PRS07	.SRES	2	;
_SVP_OBJECT_PRS08	.SRES	2	;
_SVP_OBJECT_PRS09	.SRES	2	;
_SVP_OBJECT_PRS10	.SRES	2	;

;	=== 2010-08-12 ====    SHIMA(HMI:V05r)
_SVP_BREAK_DIG_RAT		.SRES	2	;ﾌﾞﾚｰｷ角度   	割合
_SVP_BREAK_TIM_RAT		.SRES	2	;ブレーキタイマ	割合

_SVP_MAX_KJYU			.SRES	2	;最大荷重設定(ｵﾌﾟｼｮﾝにしかない)(2010-08-23 koma)
_SVP_VIB_KJYU_TTL		.SRES	2	;vibration(振動)荷重(2010-08-23 koma)

;	=== 2013-02-20 KOMA
_SVP_KATTCH_SPD			.SRES	2	;金型タッチ速度



;	***************************************************
;	***	ｸﾗｯﾁ制御画面設定1 4/2BYTE領域		***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'1600
	.ALIGN	4				;
_SVP_OBJECT_POS_TOP:
_SVP_OBJECT_PS01		.SRES	4	;01段目目標位置
_SVP_OBJECT_PS02		.SRES	4	;02段目目標位置
_SVP_OBJECT_PS03		.SRES	4	;03段目目標位置
_SVP_OBJECT_PS04		.SRES	4	;04段目目標位置
_SVP_OBJECT_PS05		.SRES	4	;05段目目標位置
_SVP_OBJECT_PS06		.SRES	4	;06段目目標位置
_SVP_OBJECT_PS07		.SRES	4	;07段目目標位置
_SVP_OBJECT_PS08		.SRES	4	;08段目目標位置
_SVP_OBJECT_PS09		.SRES	4	;09段目目標位置
_SVP_OBJECT_PS10		.SRES	4	;10段目目標位置
_SVP_OBJECT_PS11		.SRES	4	;11段目目標位置
_SVP_OBJECT_PS12		.SRES	4	;12段目目標位置
_SVP_OBJECT_PS13		.SRES	4	;13段目目標位置
_SVP_OBJECT_PS14		.SRES	4	;14段目目標位置
_SVP_OBJECT_PS15		.SRES	4	;15段目目標位置
_SVP_OBJECT_PS16		.SRES	4	;16段目目標位置
_SVP_OBJECT_PS17		.SRES	4	;17段目目標位置
_SVP_OBJECT_PS18		.SRES	4	;18段目目標位置
_SVP_OBJECT_PS19		.SRES	4	;19段目目標位置
_SVP_OBJECT_PS20		.SRES	4	;20段目目標位置

_SVP_OBJECT_DIG_TOP:				;01段目角度位置
_SVP_OBJECT_DG01		.SRES	2	;01段目角度位置
_SVP_OBJECT_DG02		.SRES	2	;02段目角度位置
_SVP_OBJECT_DG03		.SRES	2	;03段目角度位置
_SVP_OBJECT_DG04		.SRES	2	;04段目角度位置
_SVP_OBJECT_DG05		.SRES	2	;05段目角度位置
_SVP_OBJECT_DG06		.SRES	2	;06段目角度位置
_SVP_OBJECT_DG07		.SRES	2	;07段目角度位置
_SVP_OBJECT_DG08		.SRES	2	;08段目角度位置
_SVP_OBJECT_DG09		.SRES	2	;09段目角度位置
_SVP_OBJECT_DG10		.SRES	2	;10段目角度位置
_SVP_OBJECT_DG11		.SRES	2	;予備11段目角度位置
_SVP_OBJECT_DG12		.SRES	2	;予備12段目角度位置
_SVP_OBJECT_DG13		.SRES	2	;予備13段目角度位置
_SVP_OBJECT_DG14		.SRES	2	;予備14段目角度位置
_SVP_OBJECT_DG15		.SRES	2	;予備15段目角度位置
_SVP_OBJECT_DG16		.SRES	2	;予備16段目角度位置
_SVP_OBJECT_DG17		.SRES	2	;予備17段目角度位置
_SVP_OBJECT_DG18		.SRES	2	;予備18段目角度位置
_SVP_OBJECT_DG19		.SRES	2	;予備19段目角度位置
_SVP_OBJECT_DG20		.SRES	2	;予備20段目角度位置

_SVP_OBJECT_SPD_TOP:				;01段目移動速度
_SVP_OBJECT_SP01		.SRES	2	;01段目移動速度
_SVP_OBJECT_SP02		.SRES	2	;02段目移動速度
_SVP_OBJECT_SP03		.SRES	2	;03段目移動速度
_SVP_OBJECT_SP04		.SRES	2	;04段目移動速度
_SVP_OBJECT_SP05		.SRES	2	;05段目移動速度
_SVP_OBJECT_SP06		.SRES	2	;06段目移動速度
_SVP_OBJECT_SP07		.SRES	2	;07段目移動速度
_SVP_OBJECT_SP08		.SRES	2	;08段目移動速度
_SVP_OBJECT_SP09		.SRES	2	;09段目移動速度
_SVP_OBJECT_SP10		.SRES	2	;10段目移動速度
_SVP_OBJECT_SP11		.SRES	2	;予備11段目移動速度
_SVP_OBJECT_SP12		.SRES	2	;予備12段目移動速度
_SVP_OBJECT_SP13		.SRES	2	;予備13段目移動速度
_SVP_OBJECT_SP14		.SRES	2	;予備14段目移動速度
_SVP_OBJECT_SP15		.SRES	2	;予備15段目移動速度
_SVP_OBJECT_SP16		.SRES	2	;予備16段目移動速度
_SVP_OBJECT_SP17		.SRES	2	;予備17段目移動速度
_SVP_OBJECT_SP18		.SRES	2	;予備18段目移動速度
_SVP_OBJECT_SP19		.SRES	2	;予備19段目移動速度
_SVP_OBJECT_SP20		.SRES	2	;予備20段目移動速度

_SVP_OBJECT_TIM_TOP				;01段目停止時間
_SVP_OBJECT_TM01		.SRES	2	;01段目停止時間
_SVP_OBJECT_TM02		.SRES	2	;02段目停止時間
_SVP_OBJECT_TM03		.SRES	2	;03段目停止時間
_SVP_OBJECT_TM04		.SRES	2	;04段目停止時間
_SVP_OBJECT_TM05		.SRES	2	;05段目停止時間
_SVP_OBJECT_TM06		.SRES	2	;06段目停止時間
_SVP_OBJECT_TM07		.SRES	2	;07段目停止時間
_SVP_OBJECT_TM08		.SRES	2	;08段目停止時間
_SVP_OBJECT_TM09		.SRES	2	;09段目停止時間
_SVP_OBJECT_TM10		.SRES	2	;10段目停止時間
_SVP_OBJECT_TM11		.SRES	2	;11段目停止時間
_SVP_OBJECT_TM12		.SRES	2	;12段目停止時間
_SVP_OBJECT_TM13		.SRES	2	;13段目停止時間
_SVP_OBJECT_TM14		.SRES	2	;14段目停止時間
_SVP_OBJECT_TM15		.SRES	2	;15段目停止時間
_SVP_OBJECT_TM16		.SRES	2	;16段目停止時間
_SVP_OBJECT_TM17		.SRES	2	;17段目停止時間
_SVP_OBJECT_TM18		.SRES	2	;18段目停止時間
_SVP_OBJECT_TM19		.SRES	2	;19段目停止時間
_SVP_OBJECT_TM20		.SRES	2	;20段目停止時間

;	***************************************************
;	***	ｸﾗｯﾁ制御画面設定2 4/2BYTE領域		***
;	***************************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'1800
	.ALIGN	4				;
_SVP_DAIHAI_ORG0		.SRES	4	;ダイハイト
_SVP_MRTION_SEL1		.SRES	2	;回転方式
_SVP_MTSTEP_MAXM		.SRES	2	;段数

	.ALIGN	4				;
_SVP_UPAREA_POS0		.SRES	4	;待機点位置
_SVP_UPAREA_DIG0		.SRES	2	;待機点角度
_SVP_UPAREA_SPD0		.SRES	2	;基準速度(戻速度)
_SVP_UPAREA_TIM0		.SRES	2	;待機時間
_SVP_DNAREA_INP0		.SRES	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
_SVP_OBJARA_INP0		.SRES	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
_SVP_DAIHSA_LENG		.SRES	2	;ﾀﾞｲﾊｲﾄ補正距離

;	==== 2002-08-08======
	.ALIGN	4				;
_SVP_SLID_POS1		.SRES	4	;ｽﾗｲﾄﾞ位置　生産
_SVP_SLID_POS2		.SRES	4	;ｽﾗｲﾄﾞ位置　段取1
_SVP_SLID_POS3		.SRES	4	;ｽﾗｲﾄﾞ位置　段取2

_SVP_GMNSEQ_CNT01	.SRES	2	;内部画面ﾀｲﾏ->ｼｰｹﾝｽ
_SVP_GMNSEQ_CNT02	.SRES	2	;内部画面ﾀｲﾏ->ｼｰｹﾝｽ
_SVP_GMNSEQ_CNT03	.SRES	2	;内部画面ﾀｲﾏ->ｼｰｹﾝｽ
_SVP_GMNSEQ_CNT04	.SRES	2	;予備
_SVP_GMNSEQ_CNT05	.SRES	2	;予備
_SVP_GMNSEQ_CNT06	.SRES	2	;予備
_SVP_GMNSEQ_CNT07	.SRES	2	;予備
_SVP_GMNSEQ_CNT08	.SRES	2	;予備

_SVP_GMNSEQ_TIM01	.SRES	2	;内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
_SVP_GMNSEQ_TIM02	.SRES	2	;内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
_SVP_GMNSEQ_TIM03	.SRES	2	;内部画面ｶｳﾝﾀ→ｼｰｹﾝｽ
_SVP_GMNSEQ_TIM04	.SRES	2	;予備
_SVP_GMNSEQ_TIM05	.SRES	2	;予備
_SVP_GMNSEQ_TIM06	.SRES	2	;予備
_SVP_GMNSEQ_TIM07	.SRES	2	;予備
_SVP_GMNSEQ_TIM08	.SRES	2	;予備

;	==== 2002-08-26======
_SVP_CAMFUN_SEL_TOP			;
_SVP_CAMFUN_SEL00	.SRES	2
_SVP_CAMFUN_SEL01	.SRES	2
_SVP_CAMFUN_SEL02	.SRES	2
_SVP_CAMFUN_SEL03	.SRES	2
_SVP_CAMFUN_SEL04	.SRES	2
_SVP_CAMFUN_SEL05	.SRES	2
_SVP_CAMFUN_SEL06	.SRES	2
_SVP_CAMFUN_SEL07	.SRES	2
_SVP_CAMFUN_SEL08	.SRES	2
_SVP_CAMFUN_SEL09	.SRES	2
_SVP_CAMFUN_SEL0A	.SRES	2
_SVP_CAMFUN_SEL0B	.SRES	2
_SVP_CAMFUN_SEL0C	.SRES	2
_SVP_CAMFUN_SEL0D	.SRES	2
_SVP_CAMFUN_SEL0E	.SRES	2
_SVP_CAMFUN_SEL0F	.SRES	2

;	===== 2002-08-29==
	.ALIGN	4				;
_SVP_ATSLID_OBJ1	.SRES		4	; スライド自動調節設定値（現在動作中）0.001mm
_SVP_ATSLID_DNOBJ1	.SRES		2	; スライド自動調節　下降停止 0~99
_SVP_ATSLID_UPOBJ1	.SRES		2	; スライド自動調節　上昇停止 "
_SVP_ATSLID_BAKLNG	.SRES		2	; スライド自動調節　戻り量   "
_SVP_ATSLID_COEF1	.SRES		2	; スライド自動調節　制御精度 "

;	*******************************************
;	***	異常履歴	2003-07-09 	***
;	*******************************************
_SVP_MONALM_S01		.SRES	2	
_SVP_MONALM_S02		.SRES	2	
_SVP_MONALM_S03		.SRES	2	
_SVP_MONALM_S04		.SRES	2	

;	===== 2004-06-08　=====
_SVP_KAJYUU_PRS1	.SRES	2		;荷重補正 1Kn (2004-06-08)
_SVP_KAJYUU_OBJP	.SRES	2		;荷重目標値 1Kn(2004-07-01)
_SVP_KAJYUU_PV1		.SRES	2		;最大荷重(ｵﾌﾟｼｮﾝの実測をC/Bの設定として渡す)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
_PVP_KAJLIV_LFT		.SRES	2		;//荷重生（TON）(1word)
_PVP_KAJLIV_TTL		.SRES	2		;//荷重生（TON）(1word)
_PVP_KAJLIV_RIH		.SRES	2		;//荷重生（TON）(1word)


;	=====2006-07-24(ｵｰﾊﾞﾗｲﾄﾞ) ====
_SVP_OVERLIDE_COF	.SRES	2		;0,1~127%

;	=====2006-07-24(段取) ====
_SVP_DND_STOPDIG1	.SRES	2		;段取停止角度 0~358.0

;	=====2006-07-24(荷重補正) ====
_SVP_KJSTR_STEP1	.SRES	2		;0,1~工程 
_SVP_KJSTR_DIG1		.SRES	2		;359.0
_SVP_KJEND_STEP1	.SRES	2		;0,1~工程
_SVP_KJEND_DIG1		.SRES	2		;359.0
_PVP_ARA1_KAJ_R		.SRES	2		;OPTION 区間最大荷重
_PVP_ARA1_KAJ_L		.SRES	2		;OPTION 区間最大荷重
_PVP_ARA1_KAJ_T		.SRES	2		;OPTION 区間最大荷重TOTALのみ使用

;	=====2006-07-24(表示) ====
_PVP_1ROT_CALSPM	.SRES	2		;予想運転速度

;	=====2006-10-13(COP2関係) ====
	.ALIGN	4
_PVP_ORGRNA_MOV1	.SRES	4		;ﾘﾆｱ移動量実測1
_PVP_ORGRNA_MOV2	.SRES	4		;ﾘﾆｱ移動量実測2
_PVP_ORGSTRK_LEG1	.SRES	4		;ｽﾄﾛｰｸ1実測
_PVP_ORGSTRK_LEG2	.SRES	4		;ｽﾄﾛｰｸ2実測
_PVP_BAKORG_PLS1	.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
_PVP_BAKORG_PLS2	.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
_PVP_RENIA_POS1		.SRES	4		;ﾘﾆｱｽｹｰﾙ1実測
_PVP_RENIA_POS2		.SRES	4		;ﾘﾆｱｽｹｰﾙ2実測
_PVP_360_DEG		.SRES	2		;360度ｴﾝｺｰﾀﾞ角度
_PVP_PG_DEG1		.SRES	2		;PG角度1
_PVP_PG_DEG2		.SRES	2		;PG角度2
_PVP_ZURE_PLS		.SRES	2		;軸間ｽﾞﾚ実測
_PVP_ZURE_RNA		.SRES	2		;軸間ｽﾞﾚﾘﾆｱ
	.ALIGN	4
_SVP_ORGSOK_PLS		.SRES	4		;原点測定ﾊﾟﾙｽ
_SVP_ORGCAL_DAT1	.SRES	4		;演算係数1(→機種コード)
_SVP_ORGCAL_DAT2	.SRES	4		;演算係数2(→機種番号)
_SVP_ORGCAL_DAT3	.SRES	4		;演算係数3
_SVP_ORGCAL_DAT4	.SRES	4		;演算係数4
_SVP_ORGCAL_DAT5	.SRES	4		;演算係数5
_SVP_ORGCAL_DAT6	.SRES	4		;演算係数6
_SVP_ORGSTRK_LEN1	.SRES	4		;ｽﾄﾛｰｸ1
_SVP_ORGSTRK_LEN2	.SRES	4		;ｽﾄﾛｰｸ2
_SVP_RNAORGMEM_LEG1	.SRES	4		;ﾘﾆｱ原点1軸記憶:原点設定
_SVP_RNAORG_PLS1	.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測(画面入力時)
_SVP_RNAORGMEM_LEG2	.SRES	4		;ﾘﾆｱ原点2軸記憶:原点設定
_SVP_RNAORG_PLS2	.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測(画面入力時)
_SVP_RNAORG_SIN1	.SRES	2		;ﾊﾞｯｸｱｯﾌﾟ実測符号(画面入力時)
_SVP_RNAORG_SIN2	.SRES	2		;ﾊﾞｯｸｱｯﾌﾟ実測符号(画面入力時)
_SVP_ORGRUP_DEG		.SRES	2		;原点右区間上
_SVP_ORGRDN_DEG		.SRES	2		;原点右区間下
_SVP_ORGLUP_DEG		.SRES	2		;原点左区間上
_SVP_ORGLDN_DEG		.SRES	2		;原点左区間下
_SVP_ORGMEM_DEG1	.SRES	2		;角度1軸
_SVP_ORGMEM_DEGS1	.SRES	2		;角度1軸　ON/OFF
_SVP_ORGMEM_DEG2	.SRES	2		;角度2軸
_SVP_ORGMEM_DEGS2	.SRES	2		;角度2軸　ON/OFF
_SVP_ORGMPL_SEL1	.SRES	2		;手ﾊﾟﾙｻ選択1軸　ON/OFF
_SVP_ORGMPL_SEL2	.SRES	2		;手ﾊﾟﾙｻ選択2軸　ON/OFF
_SVP_HOSRAG_PLS1	.SRES	2		;軸間補正範囲１
_SVP_HOSRAG_PLS2	.SRES	2		;軸間補正範囲２
_SVP_HOSEI_SPD		.SRES	2		;補正速度
_SVP_MANSAM_LEN		.SRES	2		;手動時同期
_SVP_DANSAM_LEN		.SRES	2		;段取字同期
_SVP_RUNSAMER_LEN1	.SRES	2		;運転同期異常１
_SVP_RUNSAMER_LEN2	.SRES	2		;運転同期異常２
_SVP_MANSAMER_PLS	.SRES	2		;手動同期異常
_SVP_RUNSAMER_PLS	.SRES	2		;運転同期異常
_SVP_RNADIR_SEL2	.SRES	2		;ﾘﾆｱｾﾝｻ極性　2006-10-22
	.ALIGN	4
_SVP_ORGMEM_DEG1A	.SRES	4		;角度1軸
_SVP_ORGMEM_DEG2A	.SRES	4		;角度2軸

_PVP_RENIA_BUP1		.SRES	4		;360角度相当ﾊﾟﾙｽ1
_PVP_RENIA_BUP2		.SRES	4		;360角度相当ﾊﾟﾙｽ2
_PVP_RENIA_BUP3		.SRES	4		;360角度相当ﾊﾟﾙｽの反転(SUM1)
_PVP_RENIA_BUP4		.SRES	4		;360角度相当ﾊﾟﾙｽの反転(SUM2)
_PVP_RNABUP_ENB		.SRES	2		;バックアップ有効／無効

;	=====2006-11-20 ====	SHIMA(HMI:V01z)
_PVP_ARA1_KAJ_T2	.SRES	2		;OPTION 区間最大荷重TOTALのみ使用

;	==== 2006-12-01 =====
	.ALIGN	4
_PVP_MENTE_CNT		.SRES	4		;

;	==== 2007-02-13(CPO2関係 2軸ｻｰﾎﾞﾊﾟﾗﾒｰﾀ) =====
_PVP_PG_DEG1X		.SRES	4		;PG角度1
_PVP_PG_DEG2X		.SRES	4		;PG角度2
_PVP_PG_PLS1		.SRES	4		;PG1実測ﾊﾟﾙｽ
_PVP_PG_PLS2		.SRES	4		;PG2実測ﾊﾟﾙｽ
_PVP_PG12_DEG1		.SRES	4		;PG1-2角度
_SVP_FCLS_STR_DEG	.SRES	2		;ﾌﾙｸﾛ開始角度
_SVP_FCLS_STR_HENS	.SRES	2		;ﾌﾙｸﾛ開始偏差
_SVP_FCLS_ZIKI_SPD1	.SRES	2		;ﾌﾙｸﾛ自起動速度1
_SVP_FCLS_ZIKI_SPD2	.SRES	2		;ﾌﾙｸﾛ自起動速度2
_SVP_SYNC_ERR_DEGA	.SRES	2		;同期異常領域角度A
_SVP_SYNC_ERR_DEGB	.SRES	2		;同期異常領域角度B
_SVP_SYNC_ERR_DEGC	.SRES	2		;同期異常領域角度C
_SVP_SYNC_ERR_DEGD	.SRES	2		;同期異常領域角度D
_SVP_SYNC_ERR_RNAA	.SRES	2		;ﾘﾆｱ同期異常A
_SVP_SYNC_ERR_RNAB	.SRES	2		;ﾘﾆｱ同期異常B
_SVP_SYNC_ERR_RNAC	.SRES	2		;ﾘﾆｱ同期異常C
_SVP_SYNC_ERR_RNAD	.SRES	2		;ﾘﾆｱ同期異常D
_SVP_SYNC_ERR_PGA	.SRES	2		;PG同期異常A
_SVP_SYNC_ERR_PGB	.SRES	2		;PG同期異常B
_SVP_SYNC_ERR_PGC	.SRES	2		;PG同期異常C
_SVP_SYNC_ERR_PGD	.SRES	2		;PG同期異常D

;	==== 2010-09-15 =====
_SVP_EP_VOF		.SRES	2		;サーボパラメータB0　　電力用ｵﾌｾｯﾄ
_SVP_EP_VMX		.SRES	2		;サーボパラメータB1　　電力用最大値
_SVP_EP_TRQ		.SRES	2		;サーボパラメータB2　　電力用ﾄﾙｸ値
_SVP_EP_LTM		.SRES	2		;サーボパラメータB3　　ﾄﾙｸ側遅れ時間
_SVP_EP_K1		.SRES	2		;サーボパラメータB4　　調整係数A
_SVP_EP_K2		.SRES	2		;サーボパラメータB5　　調整係数B
_SVP_EP_ADJSIN		.SRES	2		;サーボパラメータB6　　調整電力符号
_SVP_EP_ADJVAL		.SRES	2		;サーボパラメータB7　　調整電力
_SVP_ECOM_BASE		.SRES	2		;サーボパラメータB8　　エコメータ基準値(0.1KW)
_SVP_ECOM_SCAL		.SRES	2		;サーボパラメータB9　　エコメータスケール
_SVP_MOTRPM_MAXP	.SRES	2		;サーボパラメータBA.モータ最大回転数
_SVP_ACCLAT_TIMP	.SRES	2		;サーボパラメータBB.加減速時間　未使用(2011-02-18ｺﾒﾝﾄ)
						;2011-07-04 異常を見ない時間使用ｰ>ﾀｯﾁ干補正時間
;	==== 2010-12-06 =====
_SVP_ONESTR_SPD2	.SRES	2		;NO.29??? 反転時自起動速度

;	==== 2011-03-22 =====
	.ALIGN	4
_SVP_VOLST_L		.SRES	4		;サーボパラメータBC　　ﾎﾞｽﾙﾀ面
_SVP_SLIDE_S		.SRES	4		;サーボパラメータBD　　中心
_SVP_RAD		.SRES	4		;サーボパラメータBE　　半径->金型ﾀｯﾁ加速度
_SVP_ORGREV_AGL		.SRES	4		;サーボパラメータBF　　逆転
_SVP_ORGFWD_AGL		.SRES	4		;サーボパラメータBG　　正転

;	==== 2011-07-05 =====
_SVP_RISE_ZWID		.SRES	2		;サーボパラメータBH　　上昇監視ｾﾞﾛ幅
_SVP_RISE_CMP1		.SRES	2		;サーボパラメータBI　　上昇監視比較1
_SVP_RISE_CMP2		.SRES	2		;サーボパラメータBJ　　上昇監視比較2
_SVP_RISE_CMP3		.SRES	2		;サーボパラメータBK　　上昇監視比較予備
_SVP_RISE_DLY1		.SRES	2		;サーボパラメータBL　　監視遅延1
_SVP_RISE_DLY2		.SRES	2		;サーボパラメータBM　　監視遅延2

;	==== 2011-07-28 ===== 金型ﾀｯﾁﾓｰｼｮﾝ挿入===
_PVP_MOTINS_DAN		.SRES	2		;0:有効な段数無し 1~9:金型ﾀｯﾁ挿入段数
_PVP_MOTINS_AGL		.SRES	2		;挿入2 ﾀｯﾁ角度0.1度
	.ALIGN	4
_PVP_MOTINS_POS		.SRES	4		;挿入2 ﾀｯﾁ位置0.001mm
_PVP_MOTINS_PS2		.SRES	4		;挿入1 減速0.001mm
_PVP_MOTINS_AG2		.SRES	2		;挿入1 減速角度0.1度

;	==== 2013-02-20 KOMA 挿入角度3===
_PVP_MOTINS_AG3		.SRES	2		;挿入3 金型ﾀｯﾁ後角度0.1度(ふりこ,回転は180)
	.ALIGN	4				;
_PVP_MOTINS_PS3		.SRES	4		;挿入3 金型ﾀｯﾁ後位置0.001mm(ふりこ,回転は0)
_PVP_MOTINS_INF		.SRES	2		;1:異常

;	=== 2013-02-30 KOMA 減速ﾁｪｯｸ===
_PVP_CKSPD_OVBIT	.SRES	2		;赤表示(BIT0~BIT9 BIT15:戻速度)
_PVP_CKLMT_MDSPD	.SRES	2		;戻り速度

_PVP_CKLMT_SPDTOP				;
_PVP_CKLMT_SPD01	.SRES	2		;1段目
_PVP_CKLMT_SPD02	.SRES	2		;2段目
_PVP_CKLMT_SPD03	.SRES	2		;3段目
_PVP_CKLMT_SPD04	.SRES	2		;4段目
_PVP_CKLMT_SPD05	.SRES	2		;5段目
_PVP_CKLMT_SPD06	.SRES	2		;6段目
_PVP_CKLMT_SPD07	.SRES	2		;7段目
_PVP_CKLMT_SPD08	.SRES	2		;8段目
_PVP_CKLMT_SPD09	.SRES	2		;9段目
_PVP_CKLMT_SPD10	.SRES	2		;10段目

;	----------2013-02-20 ----------
_PVP_MOTINS_DANBEF	.SRES	2		;0:有効な段数無し 1~9:金型ﾀｯﾁ減速挿入段数
_PVP_MOTINS_DANAFT	.SRES	2		;0:有効な段数無し 1~9:金型ﾀｯﾁ後挿入段数

;	*******************************************
;	***	カム設定 2BYTE領域		***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'2000
	.ALIGN	4				;
_SVP_RCAMON_POS_TOP:
_SVP_RCAMON_P000		.SRES	2	;位置ｶﾑ000　ＯＮ工程 ロータリカム１
_SVP_RCAMON_D000		.SRES	2	;位置ｶﾑ000　ＯＮ角度
_SVP_RCAMOF_P000		.SRES	2	;位置ｶﾑ000　ＯＦ工程
_SVP_RCAMOF_D000		.SRES	2	;位置ｶﾑ000　ＯＦ角度
_SVP_RCAMON_P001		.SRES	2	;位置ｶﾑ001　ＯＮ工程
_SVP_RCAMON_D001		.SRES	2	;位置ｶﾑ001　ＯＮ角度
_SVP_RCAMOF_P001		.SRES	2	;位置ｶﾑ001　ＯＦ工程
_SVP_RCAMOF_D001		.SRES	2	;位置ｶﾑ001　ＯＦ角度
_SVP_RCAMON_P002		.SRES	2	;位置ｶﾑ002　ＯＮ工程
_SVP_RCAMON_D002		.SRES	2	;位置ｶﾑ002　ＯＮ角度
_SVP_RCAMOF_P002		.SRES	2	;位置ｶﾑ002　ＯＦ工程
_SVP_RCAMOF_D002		.SRES	2	;位置ｶﾑ002　ＯＦ角度
_SVP_RCAMON_P003		.SRES	2	;位置ｶﾑ003　ＯＮ工程
_SVP_RCAMON_D003		.SRES	2	;位置ｶﾑ003　ＯＮ角度
_SVP_RCAMOF_P003		.SRES	2	;位置ｶﾑ003　ＯＦ工程
_SVP_RCAMOF_D003		.SRES	2	;位置ｶﾑ003　ＯＦ角度
_SVP_RCAMON_P004		.SRES	2	;位置ｶﾑ004　ＯＮ工程
_SVP_RCAMON_D004		.SRES	2	;位置ｶﾑ004　ＯＮ角度
_SVP_RCAMOF_P004		.SRES	2	;位置ｶﾑ004　ＯＦ工程
_SVP_RCAMOF_D004		.SRES	2	;位置ｶﾑ004　ＯＦ角度
_SVP_RCAMON_P005		.SRES	2	;位置ｶﾑ005　ＯＮ工程
_SVP_RCAMON_D005		.SRES	2	;位置ｶﾑ005　ＯＮ角度
_SVP_RCAMOF_P005		.SRES	2	;位置ｶﾑ005　ＯＦ工程
_SVP_RCAMOF_D005		.SRES	2	;位置ｶﾑ005　ＯＦ角度
_SVP_RCAMON_P006		.SRES	2	;位置ｶﾑ006　ＯＮ工程
_SVP_RCAMON_D006		.SRES	2	;位置ｶﾑ006　ＯＮ角度
_SVP_RCAMOF_P006		.SRES	2	;位置ｶﾑ006　ＯＦ工程
_SVP_RCAMOF_D006		.SRES	2	;位置ｶﾑ006　ＯＦ角度
_SVP_RCAMON_P007		.SRES	2	;位置ｶﾑ007　ＯＮ工程
_SVP_RCAMON_D007		.SRES	2	;位置ｶﾑ007　ＯＮ角度
_SVP_RCAMOF_P007		.SRES	2	;位置ｶﾑ007　ＯＦ工程
_SVP_RCAMOF_D007		.SRES	2	;位置ｶﾑ007　ＯＦ角度ロータリカム８
_SVP_RCAMON_P008		.SRES	2	;位置ｶﾑ008　ＯＮ工程
_SVP_RCAMON_D008		.SRES	2	;位置ｶﾑ008　ＯＮ角度
_SVP_RCAMOF_P008		.SRES	2	;位置ｶﾑ008　ＯＦ工程
_SVP_RCAMOF_D008		.SRES	2	;位置ｶﾑ008　ＯＦ角度
_SVP_RCAMON_P009		.SRES	2	;位置ｶﾑ009　ＯＮ工程
_SVP_RCAMON_D009		.SRES	2	;位置ｶﾑ009　ＯＮ角度
_SVP_RCAMOF_P009		.SRES	2	;位置ｶﾑ009　ＯＦ工程
_SVP_RCAMOF_D009		.SRES	2	;位置ｶﾑ009　ＯＦ角度
_SVP_RCAMON_P00A		.SRES	2	;位置ｶﾑ00A　ＯＮ工程
_SVP_RCAMON_D00A		.SRES	2	;位置ｶﾑ00A　ＯＮ角度
_SVP_RCAMOF_P00A		.SRES	2	;位置ｶﾑ00A　ＯＦ工程
_SVP_RCAMOF_D00A		.SRES	2	;位置ｶﾑ00A　ＯＦ角度
_SVP_RCAMON_P00B		.SRES	2	;位置ｶﾑ00B　ＯＮ工程
_SVP_RCAMON_D00B		.SRES	2	;位置ｶﾑ00B　ＯＮ角度
_SVP_RCAMOF_P00B		.SRES	2	;位置ｶﾑ00B　ＯＦ工程
_SVP_RCAMOF_D00B		.SRES	2	;位置ｶﾑ00B　ＯＦ角度
_SVP_RCAMON_P00C		.SRES	2	;位置ｶﾑ00C　ＯＮ工程
_SVP_RCAMON_D00C		.SRES	2	;位置ｶﾑ00C　ＯＮ角度
_SVP_RCAMOF_P00C		.SRES	2	;位置ｶﾑ00C　ＯＦ工程
_SVP_RCAMOF_D00C		.SRES	2	;位置ｶﾑ00C　ＯＦ角度
_SVP_RCAMON_P00D		.SRES	2	;位置ｶﾑ00D　ＯＮ工程
_SVP_RCAMON_D00D		.SRES	2	;位置ｶﾑ00D　ＯＮ角度
_SVP_RCAMOF_P00D		.SRES	2	;位置ｶﾑ00D　ＯＦ工程
_SVP_RCAMOF_D00D		.SRES	2	;位置ｶﾑ00D　ＯＦ角度
_SVP_RCAMON_P00E		.SRES	2	;位置ｶﾑ00E　ＯＮ工程
_SVP_RCAMON_D00E		.SRES	2	;位置ｶﾑ00E　ＯＮ角度
_SVP_RCAMOF_P00E		.SRES	2	;位置ｶﾑ00E　ＯＦ工程
_SVP_RCAMOF_D00E		.SRES	2	;位置ｶﾑ00E　ＯＦ角度
_SVP_RCAMON_P00F		.SRES	2	;位置ｶﾑ00F　ＯＮ工程
_SVP_RCAMON_D00F		.SRES	2	;位置ｶﾑ00F　ＯＮ角度
_SVP_RCAMOF_P00F		.SRES	2	;位置ｶﾑ00F　ＯＦ工程
_SVP_RCAMOF_D00F		.SRES	2	;位置ｶﾑ00F　ＯＦ角度
_SVP_RCAMON_P010		.SRES	2	;位置ｶﾑ010　ＯＮ工程　フィード?内部カム
_SVP_RCAMON_D010		.SRES	2	;位置ｶﾑ010　ＯＮ角度
_SVP_RCAMOF_P010		.SRES	2	;位置ｶﾑ010　ＯＦ工程
_SVP_RCAMOF_D010		.SRES	2	;位置ｶﾑ010　ＯＦ角度
_SVP_RCAMON_P011		.SRES	2	;位置ｶﾑ011　ＯＮ工程
_SVP_RCAMON_D011		.SRES	2	;位置ｶﾑ011　ＯＮ角度
_SVP_RCAMOF_P011		.SRES	2	;位置ｶﾑ011　ＯＦ工程
_SVP_RCAMOF_D011		.SRES	2	;位置ｶﾑ011　ＯＦ角度
_SVP_RCAMON_P012		.SRES	2	;位置ｶﾑ012　ＯＮ工程
_SVP_RCAMON_D012		.SRES	2	;位置ｶﾑ012　ＯＮ角度
_SVP_RCAMOF_P012		.SRES	2	;位置ｶﾑ012　ＯＦ工程
_SVP_RCAMOF_D012		.SRES	2	;位置ｶﾑ012　ＯＦ角度
_SVP_RCAMON_P013		.SRES	2	;位置ｶﾑ013　ＯＮ工程
_SVP_RCAMON_D013		.SRES	2	;位置ｶﾑ013　ＯＮ角度
_SVP_RCAMOF_P013		.SRES	2	;位置ｶﾑ013　ＯＦ工程
_SVP_RCAMOF_D013		.SRES	2	;位置ｶﾑ013　ＯＦ角度
_SVP_RCAMON_P014		.SRES	2	;位置ｶﾑ014　ＯＮ工程
_SVP_RCAMON_D014		.SRES	2	;位置ｶﾑ014　ＯＮ角度
_SVP_RCAMOF_P014		.SRES	2	;位置ｶﾑ014　ＯＦ工程
_SVP_RCAMOF_D014		.SRES	2	;位置ｶﾑ014　ＯＦ角度
_SVP_RCAMON_P015		.SRES	2	;位置ｶﾑ015　ＯＮ工程
_SVP_RCAMON_D015		.SRES	2	;位置ｶﾑ015　ＯＮ角度
_SVP_RCAMOF_P015		.SRES	2	;位置ｶﾑ015　ＯＦ工程
_SVP_RCAMOF_D015		.SRES	2	;位置ｶﾑ015　ＯＦ角度
_SVP_RCAMON_P016		.SRES	2	;位置ｶﾑ016　ＯＮ工程
_SVP_RCAMON_D016		.SRES	2	;位置ｶﾑ016　ＯＮ角度
_SVP_RCAMOF_P016		.SRES	2	;位置ｶﾑ016　ＯＦ工程
_SVP_RCAMOF_D016		.SRES	2	;位置ｶﾑ016　ＯＦ角度
_SVP_RCAMON_P017		.SRES	2	;位置ｶﾑ017　ＯＮ工程
_SVP_RCAMON_D017		.SRES	2	;位置ｶﾑ017　ＯＮ角度
_SVP_RCAMOF_P017		.SRES	2	;位置ｶﾑ017　ＯＦ工程
_SVP_RCAMOF_D017		.SRES	2	;位置ｶﾑ017　ＯＦ角度
_SVP_RCAMON_P018		.SRES	2	;位置ｶﾑ018　ＯＮ工程
_SVP_RCAMON_D018		.SRES	2	;位置ｶﾑ018　ＯＮ角度
_SVP_RCAMOF_P018		.SRES	2	;位置ｶﾑ018　ＯＦ工程
_SVP_RCAMOF_D018		.SRES	2	;位置ｶﾑ018　ＯＦ角度
_SVP_RCAMON_P019		.SRES	2	;位置ｶﾑ019　ＯＮ工程
_SVP_RCAMON_D019		.SRES	2	;位置ｶﾑ019　ＯＮ角度
_SVP_RCAMOF_P019		.SRES	2	;位置ｶﾑ019　ＯＦ工程
_SVP_RCAMOF_D019		.SRES	2	;位置ｶﾑ019　ＯＦ角度
_SVP_RCAMON_P01A		.SRES	2	;位置ｶﾑ01A　ＯＮ工程
_SVP_RCAMON_D01A		.SRES	2	;位置ｶﾑ01A　ＯＮ角度
_SVP_RCAMOF_P01A		.SRES	2	;位置ｶﾑ01A　ＯＦ工程
_SVP_RCAMOF_D01A		.SRES	2	;位置ｶﾑ01A　ＯＦ角度
_SVP_RCAMON_P01B		.SRES	2	;位置ｶﾑ01B　ＯＮ工程
_SVP_RCAMON_D01B		.SRES	2	;位置ｶﾑ01B　ＯＮ角度
_SVP_RCAMOF_P01B		.SRES	2	;位置ｶﾑ01B　ＯＦ工程
_SVP_RCAMOF_D01B		.SRES	2	;位置ｶﾑ01B　ＯＦ角度
_SVP_RCAMON_P01C		.SRES	2	;位置ｶﾑ01C　ＯＮ工程
_SVP_RCAMON_D01C		.SRES	2	;位置ｶﾑ01C　ＯＮ角度
_SVP_RCAMOF_P01C		.SRES	2	;位置ｶﾑ01C　ＯＦ工程
_SVP_RCAMOF_D01C		.SRES	2	;位置ｶﾑ01C　ＯＦ角度
_SVP_RCAMON_P01D		.SRES	2	;位置ｶﾑ01D　ＯＮ工程
_SVP_RCAMON_D01D		.SRES	2	;位置ｶﾑ01D　ＯＮ角度
_SVP_RCAMOF_P01D		.SRES	2	;位置ｶﾑ01D　ＯＦ工程
_SVP_RCAMOF_D01D		.SRES	2	;位置ｶﾑ01D　ＯＦ角度
_SVP_RCAMON_P01E		.SRES	2	;位置ｶﾑ01E　ＯＮ工程
_SVP_RCAMON_D01E		.SRES	2	;位置ｶﾑ01E　ＯＮ角度
_SVP_RCAMOF_P01E		.SRES	2	;位置ｶﾑ01E　ＯＦ工程
_SVP_RCAMOF_D01E		.SRES	2	;位置ｶﾑ01E　ＯＦ角度
_SVP_RCAMON_P01F		.SRES	2	;位置ｶﾑ01F　ＯＮ工程
_SVP_RCAMON_D01F		.SRES	2	;位置ｶﾑ01F　ＯＮ角度
_SVP_RCAMOF_P01F		.SRES	2	;位置ｶﾑ01F　ＯＦ工程
_SVP_RCAMOF_D01F		.SRES	2	;位置ｶﾑ01F　ＯＦ角度
_SVP_RCAMON_P020		.SRES	2	;位置ｶﾑ020　ＯＮ工程 エジェクタ
_SVP_RCAMON_D020		.SRES	2	;位置ｶﾑ020　ＯＮ角度
_SVP_RCAMOF_P020		.SRES	2	;位置ｶﾑ020　ＯＦ工程
_SVP_RCAMOF_D020		.SRES	2	;位置ｶﾑ020　ＯＦ角度
_SVP_RCAMON_P021		.SRES	2	;位置ｶﾑ021　ＯＮ工程
_SVP_RCAMON_D021		.SRES	2	;位置ｶﾑ021　ＯＮ角度
_SVP_RCAMOF_P021		.SRES	2	;位置ｶﾑ021　ＯＦ工程
_SVP_RCAMOF_D021		.SRES	2	;位置ｶﾑ021　ＯＦ角度
_SVP_RCAMON_P022		.SRES	2	;位置ｶﾑ022　ＯＮ工程
_SVP_RCAMON_D022		.SRES	2	;位置ｶﾑ022　ＯＮ角度
_SVP_RCAMOF_P022		.SRES	2	;位置ｶﾑ022　ＯＦ工程
_SVP_RCAMOF_D022		.SRES	2	;位置ｶﾑ022　ＯＦ角度
_SVP_RCAMON_P023		.SRES	2	;位置ｶﾑ023　ＯＮ工程
_SVP_RCAMON_D023		.SRES	2	;位置ｶﾑ023　ＯＮ角度
_SVP_RCAMOF_P023		.SRES	2	;位置ｶﾑ023　ＯＦ工程
_SVP_RCAMOF_D023		.SRES	2	;位置ｶﾑ023　ＯＦ角度
_SVP_RCAMON_P024		.SRES	2	;位置ｶﾑ024　ＯＮ工程
_SVP_RCAMON_D024		.SRES	2	;位置ｶﾑ024　ＯＮ角度
_SVP_RCAMOF_P024		.SRES	2	;位置ｶﾑ024　ＯＦ工程
_SVP_RCAMOF_D024		.SRES	2	;位置ｶﾑ024　ＯＦ角度
_SVP_RCAMON_P025		.SRES	2	;位置ｶﾑ025　ＯＮ工程
_SVP_RCAMON_D025		.SRES	2	;位置ｶﾑ025　ＯＮ角度
_SVP_RCAMOF_P025		.SRES	2	;位置ｶﾑ025　ＯＦ工程
_SVP_RCAMOF_D025		.SRES	2	;位置ｶﾑ025　ＯＦ角度
_SVP_RCAMON_P026		.SRES	2	;位置ｶﾑ026　ＯＮ工程
_SVP_RCAMON_D026		.SRES	2	;位置ｶﾑ026　ＯＮ角度
_SVP_RCAMOF_P026		.SRES	2	;位置ｶﾑ026　ＯＦ工程
_SVP_RCAMOF_D026		.SRES	2	;位置ｶﾑ026　ＯＦ角度
_SVP_RCAMON_P027		.SRES	2	;位置ｶﾑ027　ＯＮ工程
_SVP_RCAMON_D027		.SRES	2	;位置ｶﾑ027　ＯＮ角度
_SVP_RCAMOF_P027		.SRES	2	;位置ｶﾑ027　ＯＦ工程
_SVP_RCAMOF_D027		.SRES	2	;位置ｶﾑ027　ＯＦ角度
_SVP_RCAMON_P028		.SRES	2	;位置ｶﾑ028　ＯＮ工程
_SVP_RCAMON_D028		.SRES	2	;位置ｶﾑ028　ＯＮ角度
_SVP_RCAMOF_P028		.SRES	2	;位置ｶﾑ028　ＯＦ工程
_SVP_RCAMOF_D028		.SRES	2	;位置ｶﾑ028　ＯＦ角度
_SVP_RCAMON_P029		.SRES	2	;位置ｶﾑ029　ＯＮ工程
_SVP_RCAMON_D029		.SRES	2	;位置ｶﾑ029　ＯＮ角度
_SVP_RCAMOF_P029		.SRES	2	;位置ｶﾑ029　ＯＦ工程
_SVP_RCAMOF_D029		.SRES	2	;位置ｶﾑ029　ＯＦ角度
_SVP_RCAMON_P02A		.SRES	2	;位置ｶﾑ02A　ＯＮ工程
_SVP_RCAMON_D02A		.SRES	2	;位置ｶﾑ02A　ＯＮ角度
_SVP_RCAMOF_P02A		.SRES	2	;位置ｶﾑ02A　ＯＦ工程
_SVP_RCAMOF_D02A		.SRES	2	;位置ｶﾑ02A　ＯＦ角度
_SVP_RCAMON_P02B		.SRES	2	;位置ｶﾑ02B　ＯＮ工程
_SVP_RCAMON_D02B		.SRES	2	;位置ｶﾑ02B　ＯＮ角度
_SVP_RCAMOF_P02B		.SRES	2	;位置ｶﾑ02B　ＯＦ工程
_SVP_RCAMOF_D02B		.SRES	2	;位置ｶﾑ02B　ＯＦ角度
_SVP_RCAMON_P02C		.SRES	2	;位置ｶﾑ02C　ＯＮ工程
_SVP_RCAMON_D02C		.SRES	2	;位置ｶﾑ02C　ＯＮ角度
_SVP_RCAMOF_P02C		.SRES	2	;位置ｶﾑ02C　ＯＦ工程
_SVP_RCAMOF_D02C		.SRES	2	;位置ｶﾑ02C　ＯＦ角度
_SVP_RCAMON_P02D		.SRES	2	;位置ｶﾑ02D　ＯＮ工程
_SVP_RCAMON_D02D		.SRES	2	;位置ｶﾑ02D　ＯＮ角度
_SVP_RCAMOF_P02D		.SRES	2	;位置ｶﾑ02D　ＯＦ工程
_SVP_RCAMOF_D02D		.SRES	2	;位置ｶﾑ02D　ＯＦ角度
_SVP_RCAMON_P02E		.SRES	2	;位置ｶﾑ02E　ＯＮ工程
_SVP_RCAMON_D02E		.SRES	2	;位置ｶﾑ02E　ＯＮ角度
_SVP_RCAMOF_P02E		.SRES	2	;位置ｶﾑ02E　ＯＦ工程
_SVP_RCAMOF_D02E		.SRES	2	;位置ｶﾑ02E　ＯＦ角度
_SVP_RCAMON_P02F		.SRES	2	;位置ｶﾑ02F　ＯＮ工程
_SVP_RCAMON_D02F		.SRES	2	;位置ｶﾑ02F　ＯＮ角度
_SVP_RCAMOF_P02F		.SRES	2	;位置ｶﾑ02F　ＯＦ工程
_SVP_RCAMOF_D02F		.SRES	2	;位置ｶﾑ02F　ＯＦ角度
_SVP_RCAMON_TIM_TOP:
_SVP_RCAMON_P100		.SRES	2	;タイマｶﾑ000　ＯＮ工程
_SVP_RCAMON_D100		.SRES	2	;タイマｶﾑ000　ＯＮ角度
_SVP_RCAMOF_P100		.SRES	2	;タイマｶﾑ000　ＯＦ工程
_SVP_RCAMOF_D100		.SRES	2	;タイマｶﾑ000　OF時間・角度
_SVP_RCAMON_P101		.SRES	2	;タイマｶﾑ001　ＯＮ工程
_SVP_RCAMON_D101		.SRES	2	;タイマｶﾑ001　ＯＮ角度
_SVP_RCAMOF_P101		.SRES	2	;タイマｶﾑ001　ＯＦ工程
_SVP_RCAMOF_D101		.SRES	2	;タイマｶﾑ001　OF時間・角度
_SVP_RCAMON_P102		.SRES	2	;タイマｶﾑ002　ＯＮ工程
_SVP_RCAMON_D102		.SRES	2	;タイマｶﾑ002　ＯＮ角度
_SVP_RCAMOF_P102		.SRES	2	;タイマｶﾑ002　ＯＦ工程
_SVP_RCAMOF_D102		.SRES	2	;タイマｶﾑ002　OF時間・角度
_SVP_RCAMON_P103		.SRES	2	;タイマｶﾑ003　ＯＮ工程
_SVP_RCAMON_D103		.SRES	2	;タイマｶﾑ003　ＯＮ角度
_SVP_RCAMOF_P103		.SRES	2	;タイマｶﾑ003　ＯＦ工程
_SVP_RCAMOF_D103		.SRES	2	;タイマｶﾑ003　OF時間・角度
_SVP_RCAMON_P104		.SRES	2	;タイマｶﾑ004　ＯＮ工程
_SVP_RCAMON_D104		.SRES	2	;タイマｶﾑ004　ＯＮ角度
_SVP_RCAMOF_P104		.SRES	2	;タイマｶﾑ004　ＯＦ工程
_SVP_RCAMOF_D104		.SRES	2	;タイマｶﾑ004　OF時間・角度
_SVP_RCAMON_P105		.SRES	2	;タイマｶﾑ005　ＯＮ工程
_SVP_RCAMON_D105		.SRES	2	;タイマｶﾑ005　ＯＮ角度
_SVP_RCAMOF_P105		.SRES	2	;タイマｶﾑ005　ＯＦ工程
_SVP_RCAMOF_D105		.SRES	2	;タイマｶﾑ005　OF時間・角度
_SVP_RCAMON_P106		.SRES	2	;タイマｶﾑ006　ＯＮ工程
_SVP_RCAMON_D106		.SRES	2	;タイマｶﾑ006　ＯＮ角度
_SVP_RCAMOF_P106		.SRES	2	;タイマｶﾑ006　ＯＦ工程
_SVP_RCAMOF_D106		.SRES	2	;タイマｶﾑ006　OF時間・角度
_SVP_RCAMON_P107		.SRES	2	;タイマｶﾑ007　ＯＮ工程
_SVP_RCAMON_D107		.SRES	2	;タイマｶﾑ007　ＯＮ角度
_SVP_RCAMOF_P107		.SRES	2	;タイマｶﾑ007　ＯＦ工程
_SVP_RCAMOF_D107		.SRES	2	;タイマｶﾑ007　OF時間・角度
_SVP_RCAMON_P108		.SRES	2	;タイマｶﾑ008　ＯＮ工程
_SVP_RCAMON_D108		.SRES	2	;タイマｶﾑ008　ＯＮ角度
_SVP_RCAMOF_P108		.SRES	2	;タイマｶﾑ008　ＯＦ工程
_SVP_RCAMOF_D108		.SRES	2	;タイマｶﾑ008　OF時間・角度
_SVP_RCAMON_P109		.SRES	2	;タイマｶﾑ009　ＯＮ工程
_SVP_RCAMON_D109		.SRES	2	;タイマｶﾑ009　ＯＮ角度
_SVP_RCAMOF_P109		.SRES	2	;タイマｶﾑ009　ＯＦ工程
_SVP_RCAMOF_D109		.SRES	2	;タイマｶﾑ009　OF時間・角度
_SVP_RCAMON_P10A		.SRES	2	;タイマｶﾑ00A　ＯＮ工程
_SVP_RCAMON_D10A		.SRES	2	;タイマｶﾑ00A　ＯＮ角度
_SVP_RCAMOF_P10A		.SRES	2	;タイマｶﾑ00A　ＯＦ工程
_SVP_RCAMOF_D10A		.SRES	2	;タイマｶﾑ00A　OF時間・角度
_SVP_RCAMON_P10B		.SRES	2	;タイマｶﾑ00B　ＯＮ工程
_SVP_RCAMON_D10B		.SRES	2	;タイマｶﾑ00B　ＯＮ角度
_SVP_RCAMOF_P10B		.SRES	2	;タイマｶﾑ00B　ＯＦ工程
_SVP_RCAMOF_D10B		.SRES	2	;タイマｶﾑ00B　OF時間・角度
_SVP_RCAMON_P10C		.SRES	2	;タイマｶﾑ00C　ＯＮ工程
_SVP_RCAMON_D10C		.SRES	2	;タイマｶﾑ00C　ＯＮ角度
_SVP_RCAMOF_P10C		.SRES	2	;タイマｶﾑ00C　ＯＦ工程
_SVP_RCAMOF_D10C		.SRES	2	;タイマｶﾑ00C　OF時間・角度
_SVP_RCAMON_P10D		.SRES	2	;タイマｶﾑ00D　ＯＮ工程
_SVP_RCAMON_D10D		.SRES	2	;タイマｶﾑ00D　ＯＮ角度
_SVP_RCAMOF_P10D		.SRES	2	;タイマｶﾑ00D　ＯＦ工程
_SVP_RCAMOF_D10D		.SRES	2	;タイマｶﾑ00D　OF時間・角度
_SVP_RCAMON_P10E		.SRES	2	;タイマｶﾑ00E　ＯＮ工程
_SVP_RCAMON_D10E		.SRES	2	;タイマｶﾑ00E　ＯＮ角度
_SVP_RCAMOF_P10E		.SRES	2	;タイマｶﾑ00E　ＯＦ工程
_SVP_RCAMOF_D10E		.SRES	2	;タイマｶﾑ00E　OF時間・角度
_SVP_RCAMON_P10F		.SRES	2	;タイマｶﾑ00F　ＯＮ工程
_SVP_RCAMON_D10F		.SRES	2	;タイマｶﾑ00F　ＯＮ角度
_SVP_RCAMOF_P10F		.SRES	2	;タイマｶﾑ00F　ＯＦ工程
_SVP_RCAMOF_D10F		.SRES	2	;タイマｶﾑ00F　ＯＦ時間・角


;	*******************************************
;	***					***
;	***	予備	SHIMA(HMI:V01v)		***
;	***	サンプリング			***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'2400
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4				;
;;;;;;;;;[[[仮2013-12-02]]]_HMI2CB_LDCMD_FLG		.SRES	2	; HMI->C/B ﾛｰﾀﾞｺﾏﾝﾄﾞｾｯﾄﾌﾞﾗｸﾞ
;;;;;;;;;[[[仮2013-12-02]]]_HMI2CB_LDCMD_DAT		.SRES	540	; HMI->C/B ﾛｰﾀﾞｺﾏﾝﾄﾞ
;;;;;;;;;[[[仮2013-12-02]]]_CB2HMI_LDCMD_FLG		.SRES	2	; C/B->HMI ﾛｰﾀﾞｺﾏﾝﾄﾞｾｯﾄﾌﾞﾗｸﾞ
;;;;;;;;;[[[仮2013-12-02]]]_CB2HMI_LDCMD_DAT		.SRES	540	; C/B->HMI ﾛｰﾀﾞｺﾏﾝﾄﾞ



;	*******************************************
;	***					***
;	***		画面描画ﾄﾚﾝﾄﾞﾄﾞｯﾄ	***
;	***					***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'2840
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4				;
;;;;;;;;;[[[仮2013-12-02]]]_CPA_SMPDAT2		.SRES	24*4	;24byte*4block=96(2010-09-21 USED　24byte)
;;;;;;;;;[[[仮2013-12-02]]]_CPA_SHTDAT2		.SRES	20*1	;20byte*1block=20(2010-09-21 USED　16byte)
;;;;;;;;;[[[仮2013-12-02]]]_HND_SMPCNT_FLG2	.SRES	2	;0,1,2,3,4 (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)
;;;;;;;;;[[[仮2013-12-02]]]_HND_SHTCNT_FLG2	.SRES	2	;0,1	   (BIT15=1:NEXT START)(CPUA:SET CPUB:CLR)

;	*******************************************
;	***					***
;	***		ここはあいてる ~2FFF	***
;	***					***
;	*******************************************
	.ALIGN	4			;
_DEBUG_MONI_ABS_POS	.SRES	4	;
_DEBUG_MONI_MD_DT0	.SRES	4
_DEBUG_MONI_MD_DT1	.SRES	4
_DEBUG_MONI_C1		.SRES	4
_DEBUG_MONI_C2		.SRES	4


_DEBUG_MONI_WORK1	.SRES	8
_DEBUG_MONI_WORK2	.SRES	8
_DEBUG_MONI_WORK3	.SRES	8
_DEBUG_MONI_WORK4	.SRES	8
_DEBUG_MONI_WORK5	.SRES	8
_DEBUG_MONI_WORK6	.SRES	8




;	*******************************************
;	***					***
;	***		予備			***
;	***	通信やﾄﾚﾝﾄﾞ関係			***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3000
;	***************************
;	***	ﾃﾞﾊﾞｯｸ画面	***
;	***************************
	.ALIGN	4
_SVP_DEB_ADR0			.SRES	4	; 
_SVP_DEB_ADR1			.SRES	4	; 
_SVP_DEB_ADR2			.SRES	4	; 
_SVP_DEB_ADR3			.SRES	4	; 
_SVP_DEB_ADR4			.SRES	4	; 

_SVP_DEB_SEL0			.SRES	2	; 
_SVP_DEB_SEL1			.SRES	2	; 
_SVP_DEB_SEL2			.SRES	2	; 
_SVP_DEB_SEL3			.SRES	2	; 
_SVP_DEB_SEL4			.SRES	2	; 

_PVP_DEB_DAT0			.SRES	2	; 
_PVP_DEB_DAT1			.SRES	2	; 
_PVP_DEB_DAT2			.SRES	2	; 
_PVP_DEB_DAT3			.SRES	2	; 
_PVP_DEB_DAT4			.SRES	2	; 
_PVP_DEB_DAT5			.SRES	2	; 
_PVP_DEB_DAT6			.SRES	2	; 
_PVP_DEB_DAT7			.SRES	2	; 
_PVP_DEB_DAT8			.SRES	2	; 
_PVP_DEB_DAT9			.SRES	2	; 

;	*******************************************
;	***	ﾄﾚﾝﾄﾞ/異常履歴	2003-07-01 	***
;	*******************************************
	.ALIGN	4
_PV_CB_STS_DAT_TOP	.SRES	_CB_STS_BUF_MAX		;ﾊﾞｯﾌｧ 64BYTE*8=512(128BYTE CPUA-USED)
_PV_CB_TRD_DAT_TOP	.SRES	_CB_TRD_BUF_DP_MAX	;128byte
_PV_CB_STS_POINT	.SRES	2			;
_PV_CB_TRD_POINT	.SRES	2			;
_PV_POWER_ON_CNT	.SRES	2			;

;	*******************************************
;	***	異常履歴	2003-07-09 	***
;	*******************************************
_PVP_MONALM_P01		.SRES	2
_PVP_MONALM_P02		.SRES	2
_PVP_MONALM_P03		.SRES	2
_PVP_MONALM_P04		.SRES	2


	.ALIGN	4				;LONG/WORD ｱｸｾｽ A01/B01/C01
_PVP_MONALM1_TOP				;2018-11-11
_PVP_MONALM_C01		.SRES	4		;A/B/Cは連続した空間である事
_PVP_MONALM_C02		.SRES	4
_PVP_MONALM_C03		.SRES	4
_PVP_MONALM_C04		.SRES	4
_PVP_MONALM_C05		.SRES	4
_PVP_MONALM_C06		.SRES	4
_PVP_MONALM_C07		.SRES	4
_PVP_MONALM_C08		.SRES	4
_PVP_MONALM_A01		.SRES	2
_PVP_MONALM_A02		.SRES	2
_PVP_MONALM_A03		.SRES	2
_PVP_MONALM_A04		.SRES	2
_PVP_MONALM_A05		.SRES	2
_PVP_MONALM_A06		.SRES	2
_PVP_MONALM_A07		.SRES	2
_PVP_MONALM_A08		.SRES	2
_PVP_MONALM_B01		.SRES	2
_PVP_MONALM_B02		.SRES	2
_PVP_MONALM_B03		.SRES	2
_PVP_MONALM_B04		.SRES	2
_PVP_MONALM_B05		.SRES	2
_PVP_MONALM_B06		.SRES	2
_PVP_MONALM_B07		.SRES	2
_PVP_MONALM_B08		.SRES	2

;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]];	===		ET1 TOREND DATA		===
;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4					;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_INI_ET1	.SRES	4			;INITAL CODE REQ
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RCV_INI_ET1	.SRES	4			;INITAL CODE ACK
;;;;;;;;;[[[仮2013-12-02]]];	--------------------------------------------------
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_REQ_ET1	.SRES	4			;H'12345678(req)
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RCV_ACK_ET1	.SRES	4			;H'87654321(ack)
;;;;;;;;;[[[仮2013-12-02]]];	---------------------------------------------------
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_REQ_ADR	.SRES	4			;TOPADRESS (192K+32K 256Kbyte)
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_REQ_CNT	.SRES	4			;1~128個
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4					;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_DAT		.SRES	_ET1_CPUAB_BUF_MAX	;(256byte MAX)
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_SND_END		.SRES	2			;341C

;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]];	===	ET1==>CPUA(読出 32BYTE)	ｽﾃｰﾀｽRD	===
;;;;;;;;;[[[仮2013-12-02]]];	===	2008-10-20			===
;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]];--0F4E
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RD_REQ		.SRES	2			;CPUA-->ET1 READ REQ
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RD_ACK		.SRES	2			;ET1-->CPUA data SET ACK
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RD_CNT		.SRES	2			;読出個数
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4					;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RD_ADR		.SRES	4			;読出ｱﾄﾞﾚｽ
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_RD_BUF		.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]];	===	CPUA==>書込2(32byte)	ｽﾃｰﾀｽWR	===
;;;;;;;;;[[[仮2013-12-02]]];	===	2008-10-20			===
;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4					;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_WR2_ADR	.SRES	4			;STS WR LINE
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_WR2_BUF	.SRES	_ET1_RDWR2_BUFMAX	;32byte(16w)
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_WR2_REQ	.SRES	2			;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_WR2_ACK	.SRES	2			;
;;;;;;;;;[[[仮2013-12-02]]]_CPUA_WR2_CNT	.SRES	2			;cpub(FA0,FA1)et1(3A0,3A1)
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]];	===========================================
;;;;;;;;;[[[仮2013-12-02]]];	===		ET1 TOREND DATA2	===
;;;;;;;;;[[[仮2013-12-02]]];	===	2008-10-20 読出,書込2追加	===
;;;;;;;;;[[[仮2013-12-02]]];	===					===
;;;;;;;;;[[[仮2013-12-02]]];	===========================================

;	*******************************************
;	***		実測 4/2BYTE領域	***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3800
	.ALIGN	4				;
_PVP_RNAORG_PLS1		.SRES	4	;ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
_PVP_NOW_POSI000		.SRES	4	;下死点高さ位置(表示用 原点完了まではABS値)
_PVP_RENIA_POSI0		.SRES	4	;リニアセンサ現在位置(生表示用 ABS値 何も使っていない?HMIで)
_PVP_NOW_ANGLE00		.SRES	2	;SH2->SH4　360度ｴﾝｺｰﾀﾞ(CHEAK用)
_PVP_CYCLE_TIME0		.SRES	2	;サイクル時間表示用
;	----- 追加2002/07/02 ---
_PVP_CYCLE_SPM1			.SRES	2	;サイクル速度表示用
_PVP_DISP_SPM2			.SRES	2	;高速時描画を塗りつぶしにする為の速度(単位不明)
_PVP_NOW_ANGLE_RNA		.SRES	2	;現在角度0.1度HEX(ﾘﾆｱｽｹｰﾙからの1度単位 SH4->SH2)(画面表示用)
_PVP_DYHITO_HOSLNG		.SRES	2	;ﾀﾞｲﾊｲﾄ補正量 1um(0.001mm) +/-
	.ALIGN	4				;
_PVP_DYHITO_POS			.SRES	4	;ﾀﾞｲﾊｲﾄ実測 生産初期画面表示値 
						;2003-07-09 下限位置のまま
_PVP_SLIDE_POS			.SRES	4	;ｽﾗｲﾄﾞ位置・ﾀﾞｲﾊｲﾄを含めた位置(ｸﾗｯﾁは未使用)
						;2003-07-09 生産下限位置
_PVP_TAIKITEN_POS		.SRES	2	;待機点角度表示（描画用）

;	----- 追加2002/08/01 ---
	.ALIGN	4				;
_PVP_RNA_STLORK			.SRES	4	;ｽﾄﾛｰｸ実測
_PVP_STOP_TIM			.SRES	2	;ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ 1msec data
_PVP_BREAK_DIG			.SRES	2	;ﾌﾞﾚｰｷ角度   0.1度
_PVP_COM_ERR			.SRES	2	;ｺﾝﾊﾟｲﾙ異常有り／無し
_PVP_COM_ADR			.SRES	2	;ｺﾝﾊﾟｲﾙ異常ｱﾄﾞﾚｽ
_PVP_SEQ_ERR			.SRES	2	;ｺﾝﾊﾟｲﾙ異常 異常時ﾒｲﾝSEQか割込SEQかの判断(今回未使用)
;	----- 追加2002/08/08-----
_PVP_BREAK_TIM1			.SRES	2	;

_PVP_GMNSEQ_CNT01	.SRES	2	;内部画面ﾀｲﾏ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_CNT02	.SRES	2	;内部画面ﾀｲﾏ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_CNT03	.SRES	2	;内部画面ﾀｲﾏ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_CNT04	.SRES	2	;予備
_PVP_GMNSEQ_CNT05	.SRES	2	;予備
_PVP_GMNSEQ_CNT06	.SRES	2	;予備
_PVP_GMNSEQ_CNT07	.SRES	2	;予備
_PVP_GMNSEQ_CNT08	.SRES	2	;予備

_PVP_GMNSEQ_TIM01	.SRES	2	;内部画面ｶｳﾝﾀ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_TIM02	.SRES	2	;内部画面ｶｳﾝﾀ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_TIM03	.SRES	2	;内部画面ｶｳﾝﾀ<=ｼｰｹﾝｽ
_PVP_GMNSEQ_TIM04	.SRES	2	;予備
_PVP_GMNSEQ_TIM05	.SRES	2	;予備
_PVP_GMNSEQ_TIM06	.SRES	2	;予備
_PVP_GMNSEQ_TIM07	.SRES	2	;予備
_PVP_GMNSEQ_TIM08	.SRES	2	;予備

;	========== 2003-01-27 過負荷実測追加====
_PVP_POWER_MONI		.SRES	2	;ADR=3854

;	========= 2003-02-04 ======
_PVP_CPUA_TEPPLS	.SRES	2	;
_PVP_CPUB_TEPPLS	.SRES	2	;
_PVP_CPUA_ANAIN		.SRES	2	;
_PVP_CPUB_ANAIN		.SRES	2	;

	.ALIGN	4			;
_PVP_ENC_PLS_SPD	.SRES	4	;SHIN
_PVP_OUT_PLS_SPD	.SRES	4	;SHIN
_PVP_ABS_ENC_SPD	.SRES	4	;ABS
_PVP_ABS_OUT_SPD	.SRES	4	;ABS
_PVP_ENC_SPD_PER	.SRES	2	;
_PVP_OUT_SPD_PER	.SRES	2	;
_PVP_BRK_ENC_SPD	.SRES	2	;
_PVP_BRK_OUT_SPD	.SRES	2	;
_PVP_ENC_SPD_DIR	.SRES	2	;
_PVP_OUT_SPD_DIR	.SRES	2	;

_PVP_A_LOT_CNT1		.SRES	2	;
_PVP_B_LOT_CNT1		.SRES	2	;
_PVP_A_LOT_CNT2		.SRES	2	;
_PVP_B_LOT_CNT2		.SRES	2	;
_PVP_A_LOT_CNT3		.SRES	2	;
_PVP_B_LOT_CNT3		.SRES	2	;
_PVP_A_LOT_CNT4		.SRES	2	;
_PVP_B_LOT_CNT4		.SRES	2	;
_PVP_A_LOT_CNT5		.SRES	2	;
_PVP_B_LOT_CNT5		.SRES	2	;

;	========== 2010-09-01 電力量追加 ============
_PVP_ECO_METER		.SRES	2	;
_PVP_POWER_KWH		.SRES	2	;
_PVP_EPM_SYOHI		.SRES	2	;
_PVP_EPM_KAISE		.SRES	2	;

_PVP_IVW_DOT		.SRES	2	;0:小数点2桁 5A:小数点1桁 CPUA->CPUB


;	======= 2004-03-08 origin 追加(二重回路対策) ===========
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3B00
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_CNT_REST_PLS	.SRES	4	;連続の切替時残りパルス
;;;;;;;;;[[[仮2013-12-02]]]_SH4_LNGH_ADD_SR	.SRES	4	;安全一行程,一行程 起動時移動量
;;;;;;;;;[[[仮2013-12-02]]]_SH4_REST_PLS_SR	.SRES	4	;安全一行程,一行程 起動時残ﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH4_REST_PLS_RL	.SRES	4	;安全一行程,一行程 REAL-TIME残ﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH4_BAS_FRQ_SV		.SRES	4	;ﾍﾞｰｽ周波数設定
;;;;;;;;;[[[仮2013-12-02]]]_SH4_TOP_FRQ_SV		.SRES	4	;TOP周波数設定
;;;;;;;;;[[[仮2013-12-02]]]_SH4_NOW_FRQ_PV		.SRES	4	;TOP周波数実測
;;;;;;;;;[[[仮2013-12-02]]]_SH4_PLSI_ACCS		.SRES	2	;加減速度
;;;;;;;;;[[[仮2013-12-02]]]_SH4_PLSI_LATE		.SRES	2	;24
;;;;;;;;;[[[仮2013-12-02]]]_SH4_LOT_CNT_A		.SRES	2	;上記のﾃﾞｰﾀ書き込み時の回転ロット数
;;;;;;;;;[[[仮2013-12-02]]]_SH4_LOT_STEP_A		.SRES	2	;上記のﾃﾞｰﾀ書き込み時のｽﾃｯﾌﾟ数
;;;;;;;;;[[[仮2013-12-02]]]_SH4_REST_SR_HF		.SRES	2	;ﾊﾝﾄﾞｼｪｲｸﾌﾗｸﾞ SH4=>SH2 書いたぞ!起動時移動量
;;;;;;;;;[[[仮2013-12-02]]]_SH4_REST_RL_HF		.SRES	2	;ﾊﾝﾄﾞｼｪｲｸﾌﾗｸﾞ SH4=>SH2 書いたぞ!残りﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH4_CNT_REST_HF	.SRES	2	;連続の切り替え時残りﾊﾟﾙｽかいたぞ!ﾌﾗｸﾞ
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_CNT_REST_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_LNGH_ADD_SR	.SRES	4	;安全一行程,一行程 起動時移動量
;;;;;;;;;[[[仮2013-12-02]]]_SH2_REST_PLS_SR	.SRES	4	;安全一行程,一行程 起動時残ﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH2_REST_PLS_RL	.SRES	4	;安全一行程,一行程 REAL-TIME残ﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH2_BAS_FRQ_SV		.SRES	4	;ﾍﾞｰｽ周波数設定
;;;;;;;;;[[[仮2013-12-02]]]_SH2_TOP_FRQ_SV		.SRES	4	;TOP周波数設定
;;;;;;;;;[[[仮2013-12-02]]]_SH2_NOW_FRQ_PV		.SRES	4	;TOP周波数実測
;;;;;;;;;[[[仮2013-12-02]]]_SH2_PLSI_ACCS		.SRES	2	;加減速度
;;;;;;;;;[[[仮2013-12-02]]]_SH2_PLSI_LATE		.SRES	2	;24
;;;;;;;;;[[[仮2013-12-02]]]_SH2_LOT_CNT_A		.SRES	2	;上記のﾃﾞｰﾀ書き込み時の回転ロット数
;;;;;;;;;[[[仮2013-12-02]]]_SH2_LOT_STEP_A		.SRES	2	;上記のﾃﾞｰﾀ書き込み時のｽﾃｯﾌﾟ数
;;;;;;;;;[[[仮2013-12-02]]]_SH2_REST_SR_HF		.SRES	2	;ﾊﾝﾄﾞｼｪｲｸﾌﾗｸﾞ SH2=>SH4 書いたぞ!起動時移動量
;;;;;;;;;[[[仮2013-12-02]]]_SH2_REST_RL_HF		.SRES	2	;ﾊﾝﾄﾞｼｪｲｸﾌﾗｸﾞ SH2=>SH4 書いたぞ!残りﾊﾟﾙｽ
;;;;;;;;;[[[仮2013-12-02]]]_SH2_CNT_REST_HF	.SRES	2	;(未使用　ｸﾘｱのみ)
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]];	======= 連続の内部情報モニタ用 ====
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP1_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP2_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP3_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP4_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP5_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP1_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP2_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP3_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP4_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP5_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP1_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP2_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP3_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP4_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP5_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP1_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP2_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP3_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP4_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP5_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP1_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP2_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP3_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP4_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP5_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_TOTAL_PLS		.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_ADD_PLS		.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_STEP_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH4_NOW_STEP		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP1_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP2_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP3_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP4_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP5_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP1_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP2_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP3_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP4_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP5_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP1_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP2_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP3_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP4_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP5_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP1_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP2_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP3_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP4_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP5_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP1_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP2_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP3_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP4_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP5_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]_SH2_TOTAL_PLS		.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_ADD_PLS		.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP_SV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP_PV_PLS	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP_REST_P	.SRES	4	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP_FRQ		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_STEP_TIM		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH2_NOW_STEP		.SRES	2	;
;;;;;;;;;[[[仮2013-12-02]]]
;;;;;;;;;[[[仮2013-12-02]]];	============== 20060919 DBG=====================
;;;;;;;;;[[[仮2013-12-02]]]	.ALIGN	4			;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_SV_SPD	.SRES	4*2	;[+0:SH4 +4:SH2]
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_RL_SPD	.SRES	4*2	;[+0:SH4 +4:SH2]
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_ACC		.SRES	4*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_OFS		.SRES	4*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_SV_ABSPLS	.SRES	8*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_RL_ABSPLS	.SRES	8*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_PV_ABSPLS	.SRES	8*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_REST_PLS	.SRES	4*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_CAL_REST	.SRES	4*2	;演算(SV-PV)
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_HENSA	.SRES	4*2	;演算(SV-PV)
;;;;;;;;;[[[仮2013-12-02]]]_SH_POSCTL_LSIFREQ	.SRES	4*2	;LSI
;;;;;;;;;[[[仮2013-12-02]]]
;	===========  20070302	===============
;;;;;;;;;[[[仮2013-12-02]]]_SH_SQ200_IN		.SRES	2*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_CNTSTOP_FLG		.SRES	2*2	;
;;;;;;;;;[[[仮2013-12-02]]]_SH_OUTPLS_DELT		.SRES	2*2	;

;	======= 2003-02-03 ORIGN 追加(ｸﾗｯﾁAﾃﾞﾊﾞｯｸ用) =====
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3D80
	.ALIGN	4				;
_PVP_MONALM2_TOP				;2018-11-11
_DBG4_MONI_A00		.SRES	4
_DBG4_MONI_A01		.SRES	4
_DBG4_MONI_A02		.SRES	4
_DBG4_MONI_A03		.SRES	4
_DBG4_MONI_A04		.SRES	4
_DBG4_MONI_A05		.SRES	4
_DBG4_MONI_A06		.SRES	4
_DBG4_MONI_A07		.SRES	4
_DBG2_MONI_A00		.SRES	2
_DBG2_MONI_A01		.SRES	2
_DBG2_MONI_A02		.SRES	2	;3DA4=15780
_DBG2_MONI_A03		.SRES	2	;3DA6=15782
_DBG2_MONI_A04		.SRES	2	;3DA8=15784
_DBG2_MONI_A05		.SRES	2	;3DAA=15786
_DBG2_MONI_A06		.SRES	2	;3DAC=15788
_DBG2_MONI_A07		.SRES	2	;3DAE=15790
;	======= 2003-02-03 ORIGN 追加(ｸﾗｯﾁBﾃﾞﾊﾞｯｸ用) =====
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3DC0
	.ALIGN	4				;
_DBG4_MONI_B00		.SRES	4
_DBG4_MONI_B01		.SRES	4
_DBG4_MONI_B02		.SRES	4
_DBG4_MONI_B03		.SRES	4
_DBG4_MONI_B04		.SRES	4
_DBG4_MONI_B05		.SRES	4
_DBG4_MONI_B06		.SRES	4
_DBG4_MONI_B07		.SRES	4
_DBG2_MONI_B00		.SRES	2
_DBG2_MONI_B01		.SRES	2
_DBG2_MONI_B02		.SRES	2	;3DE4=15844
_DBG2_MONI_B03		.SRES	2	;3DE6=15846
_DBG2_MONI_B04		.SRES	2	;3DE8=15848
_DBG2_MONI_B05		.SRES	2	;3DEA=15850
_DBG2_MONI_B06		.SRES	2	;3DEC=15852
_DBG2_MONI_B07		.SRES	2	;3DEE=15854,3DEF

;	---2011-09-14 [16ﾊﾞｲﾄ]  -----
_CPUATOB_STS_SAVECMD	.SRES	2	;5AA5 or A55A
_CPUATOB_STS_SAVEDAT1	.SRES	2	;BAKUP DATA1
_CPUATOB_STS_SAVEDAT2	.SRES	2	;BAKUP DATA2
_CPUATOB_STS_SAVEDAT3	.SRES	2	;BAKUP DATA3

_CPUBTOA_STS_LOADSTS	.SRES	2	;5AA5
_CPUBTOA_STS_LOADDAT1	.SRES	2	;BAKUP DATA1
_CPUBTOA_STS_LOADDAT2	.SRES	2	;BAKUP DATA2 
_CPUBTOA_STS_LOADDAT3	.SRES	2	;BAKUP DATA3 3DFE,3DFF もうここには隙間なし

;	*******************************************
;	***					***
;	***	2002-08-29			***
;	***	固定実測(ﾊﾞｰｼﾞｮﾝ表示)		***
;	*******************************************
;;;;;;;;;[[[仮2013-12-02]]]		.ORG	H'3E00
	.ALIGN	4				;
_PVP_CB_A_VER		.SRES	2*6	;ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
_PVP_CB_B_VER		.SRES	2*6	;ASCIIﾃﾞｰﾀ (6char) SH2-->

;	======= 2003-01-27 ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ追加 =====
_PVP_PAR_A_VER		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
_PVP_PAR_B_VER		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
_PVP_TBL_A_VER		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号1~99 HEX data
_PVP_TBL_B_VER		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号1~99 HEX data

;	======= 2003-02-03 ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ追加 =====
_PVP_PAR_A_CHAR		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
_PVP_PAR_B_CHAR		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
_PVP_TBL_A_CHAR		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号()
_PVP_TBL_B_CHAR		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号()


;	=== 2004-01-27 ERR-INFO ===
_ERR_INFO_CPUA_FLG	.SRES	2	;CPUA=>WRITE 55AA CPUB=>0CLR
	.ALIGN	4						;
_ERR_INFO_CPUA_TOP	.SRES	_CB_ERR_INFO_MEM	;80	;(CPUAはDPRAM経由)<4の倍数>

;	======= V05j 2007-12-07 COP2ﾊﾞｰｼﾞｮﾝ追加 =====
_PVP_CB_C_VER		.SRES	2*6	;ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
_PVP_PAR_C_VER		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
_PVP_PAR_C_CHAR		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
_PVP_TBL_C_VER		.SRES	2	;ﾃｰﾌﾞﾙﾊﾞｰｼﾞｮﾝ HEX data（未使用）
_PVP_TBL_C_CHAR		.SRES	2	;ﾃｰﾌﾞﾙﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)


;	***********************************************************
;	***		2014年 3月以降の追加はここ		***
;	***********************************************************


	.ORG	H'1000					;
;	***********************************************************
;	***		設定関連				***
;	***********************************************************
;	=== 2014/03/17 ===	SHIMA
_SVP_KAJAREA_SNO		.SRES	2	;荷重測定範囲 開始工程No.
_SVP_KAJAREA_SAG		.SRES	2	;荷重測定範囲 開始角度　　0.1度単位0.0~359.0
_SVP_KAJAREA_ENO		.SRES	2	;荷重測定範囲 終了工程No.
_SVP_KAJAREA_EAG		.SRES	2	;荷重測定範囲 終了角度
_SVP_KAJAREA_SEL		.SRES	2	;記録荷重選択

;	=== 2014/04/14 ===	SHIMA
_SVP_KATTCH_SAG			.SRES	2	;タッチ位置検出角度
_SVP_KATTCH_EAG			.SRES	2	;タッチ位置検出角度
	.ALIGN	4
_SVP_KANDO_A21			.SRES	4	;感度
_SVP_UPDATA_A21			.SRES	4	;上限
_SVP_DNDATA_A21			.SRES	4	;下限
_SVP_GENITI_A21			.SRES	4	;現位置
_SVP_MODORI_A21			.SRES	2	;戻り量
_SVP_DNSTOP_A21			.SRES	2	;下降停止
_SVP_UPSTOP_A21			.SRES	2	;上昇停止
_SVP_SL_TENPOS			.SRES	2	;スライド自動調整の小数点位置
_SVP_SLPOS_DIR			.SRES	2	;位置決め方向

;	-------------- 最大値選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
_SVP_OVERE1_A26			.SRES	2	; 荷重計　オーバーロード１
_SVP_ROALM1_A26			.SRES	2	; 荷重計　ロアーリッミト１
_SVP_OVERE2_A26			.SRES	2	; 荷重計　オーバーロード２
_SVP_ROALM2_A26			.SRES	2	; 荷重計　ロアーリッミト２
_SVP_OVERE3_A26			.SRES	2	; 荷重計　オーバーロード３
_SVP_ROALM3_A26			.SRES	2	; 荷重計　ロアーリッミト３

;	-------------- 最小(ﾏｲﾅｽ最大)選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
_SVP_OVERE1_A27			.SRES	2	; 荷重計　オーバーロード１ 　（最小値）
_SVP_ROALM1_A27			.SRES	2	; 荷重計　ロアーリッミト１  　（最小値）
_SVP_OVERE2_A27			.SRES	2	; 荷重計　オーバーロード２  　（最小値）
_SVP_ROALM2_A27			.SRES	2	; 荷重計　ロアーリッミト２  　（最小値）
_SVP_OVERE3_A27			.SRES	2	; 荷重計　オーバーロード３  　（最小値）
_SVP_ROALM3_A27			.SRES	2	; 荷重計　ロアーリッミト３  　（最小値）

;	-------------- 振幅選択時 ｵｰﾊﾞﾛｰﾄﾞ,ﾛｱﾘﾐｯﾄ 左,合計,右
_SVP_OVERE1_A28			.SRES	2	; 荷重計　オーバーロード１ 　（振幅）
_SVP_ROALM1_A28			.SRES	2	; 荷重計　ロアーリッミト１  　（振幅）
_SVP_OVERE2_A28			.SRES	2	; 荷重計　オーバーロード２  　（振幅）
_SVP_ROALM2_A28			.SRES	2	; 荷重計　ロアーリッミト２  　（振幅）
_SVP_OVERE3_A28			.SRES	2	; 荷重計　オーバーロード３  　（振幅）
_SVP_ROALM3_A28			.SRES	2	; 荷重計　ロアーリッミト３  　（振幅）

;	=== 2014-06-09(2014/03/12) ===
_SVP_KAJOBJ_HAB			.SRES	2	;荷重完了範囲

;	=== 2014/08/27 ===	SHIMA
_SVP_INTLIM_SNO		.SRES	2	;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　行程
_SVP_INTLIM_AGL		.SRES	2	;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　角度
	.ALIGN	4
_SVP_INTLIM_POS		.SRES	4	;//ｽﾗｲﾄﾞ自動待機機能  干渉限界位置設定　位置
_SVP_WTTIM_MAX		.SRES	2	;//ｽﾗｲﾄﾞ自動待機機能  待機時間上限

;	=== 2014/09/02 ===	SHIMA
_SVP_RCAMON_SA00	.SRES	2	;				/* ロータリカム０１  ON進角  角度	*/
_SVP_RCAMON_ST00	.SRES	2	;				/* ロータリカム０１  ON進角  時間	*/
_SVP_RCAMOF_SA00	.SRES	2	;				/* ロータリカム０１  OFF進角  角度	*/
_SVP_RCAMOF_ST00	.SRES	2	;				/* ロータリカム０１  OFF進角  時間	*/
_SVP_RCAMON_SA01	.SRES	2	;				/* ロータリカム０２  ON進角  角度	*/
_SVP_RCAMON_ST01	.SRES	2	;				/* ロータリカム０２  ON進角  時間	*/
_SVP_RCAMOF_SA01	.SRES	2	;				/* ロータリカム０２  OFF進角  角度	*/
_SVP_RCAMOF_ST01	.SRES	2	;				/* ロータリカム０２  OFF進角  時間	*/
_SVP_RCAMON_SA02	.SRES	2	;				/* ロータリカム０３  ON進角  角度	*/
_SVP_RCAMON_ST02	.SRES	2	;				/* ロータリカム０３  ON進角  時間	*/
_SVP_RCAMOF_SA02	.SRES	2	;				/* ロータリカム０３  OFF進角  角度	*/
_SVP_RCAMOF_ST02	.SRES	2	;				/* ロータリカム０３  OFF進角  時間	*/
_SVP_RCAMON_SA03	.SRES	2	;				/* ロータリカム０４  ON進角  角度	*/
_SVP_RCAMON_ST03	.SRES	2	;				/* ロータリカム０４  ON進角  時間	*/
_SVP_RCAMOF_SA03	.SRES	2	;				/* ロータリカム０４  OFF進角  角度	*/
_SVP_RCAMOF_ST03	.SRES	2	;				/* ロータリカム０４  OFF進角  時間	*/
_SVP_RCAMON_SA04	.SRES	2	;				/* ロータリカム０５  ON進角  角度	*/
_SVP_RCAMON_ST04	.SRES	2	;				/* ロータリカム０５  ON進角  時間	*/
_SVP_RCAMOF_SA04	.SRES	2	;				/* ロータリカム０５  OFF進角  角度	*/
_SVP_RCAMOF_ST04	.SRES	2	;				/* ロータリカム０５  OFF進角  時間	*/
_SVP_RCAMON_SA05	.SRES	2	;				/* ロータリカム０６  ON進角  角度	*/
_SVP_RCAMON_ST05	.SRES	2	;				/* ロータリカム０６  ON進角  時間	*/
_SVP_RCAMOF_SA05	.SRES	2	;				/* ロータリカム０６  OFF進角  角度	*/
_SVP_RCAMOF_ST05	.SRES	2	;				/* ロータリカム０６  OFF進角  時間	*/
_SVP_RCAMON_SA06	.SRES	2	;				/* ロータリカム０７  ON進角  角度	*/
_SVP_RCAMON_ST06	.SRES	2	;				/* ロータリカム０７  ON進角  時間	*/
_SVP_RCAMOF_SA06	.SRES	2	;				/* ロータリカム０７  OFF進角  角度	*/
_SVP_RCAMOF_ST06	.SRES	2	;				/* ロータリカム０７  OFF進角  時間	*/
_SVP_RCAMON_SA07	.SRES	2	;				/* ロータリカム０８  ON進角  角度	*/
_SVP_RCAMON_ST07	.SRES	2	;				/* ロータリカム０８  ON進角  時間	*/
_SVP_RCAMOF_SA07	.SRES	2	;				/* ロータリカム０８  OFF進角  角度	*/
_SVP_RCAMOF_ST07	.SRES	2	;				/* ロータリカム０８  OFF進角  時間	*/
_SVP_RCAMON_SA08	.SRES	2	;				/* ロータリカム０９  ON進角  角度	*/
_SVP_RCAMON_ST08	.SRES	2	;				/* ロータリカム０９  ON進角  時間	*/
_SVP_RCAMOF_SA08	.SRES	2	;				/* ロータリカム０９  OFF進角  角度	*/
_SVP_RCAMOF_ST08	.SRES	2	;				/* ロータリカム０９  OFF進角  時間	*/
_SVP_RCAMON_SA09	.SRES	2	;				/* ロータリカム１０  ON進角  角度	*/
_SVP_RCAMON_ST09	.SRES	2	;				/* ロータリカム１０  ON進角  時間	*/
_SVP_RCAMOF_SA09	.SRES	2	;				/* ロータリカム１０  OFF進角  角度	*/
_SVP_RCAMOF_ST09	.SRES	2	;				/* ロータリカム１０  OFF進角  時間	*/
_SVP_RCAMON_SA10	.SRES	2	;				/* ロータリカム１１  ON進角  角度	*/
_SVP_RCAMON_ST10	.SRES	2	;				/* ロータリカム１１  ON進角  時間	*/
_SVP_RCAMOF_SA10	.SRES	2	;				/* ロータリカム１１  OFF進角  角度	*/
_SVP_RCAMOF_ST10	.SRES	2	;				/* ロータリカム１１  OFF進角  時間	*/
_SVP_RCAMON_SA11	.SRES	2	;				/* ロータリカム１２  ON進角  角度	*/
_SVP_RCAMON_ST11	.SRES	2	;				/* ロータリカム１２  ON進角  時間	*/
_SVP_RCAMOF_SA11	.SRES	2	;				/* ロータリカム１２  OFF進角  角度	*/
_SVP_RCAMOF_ST11	.SRES	2	;				/* ロータリカム１２  OFF進角  時間	*/
_SVP_RCAMON_SA12	.SRES	2	;				/* ロータリカム１３  ON進角  角度	*/
_SVP_RCAMON_ST12	.SRES	2	;				/* ロータリカム１３  ON進角  時間	*/
_SVP_RCAMOF_SA12	.SRES	2	;				/* ロータリカム１３  OFF進角  角度	*/
_SVP_RCAMOF_ST12	.SRES	2	;				/* ロータリカム１３  OFF進角  時間	*/
_SVP_RCAMON_SA13	.SRES	2	;				/* ロータリカム１４  ON進角  角度	*/
_SVP_RCAMON_ST13	.SRES	2	;				/* ロータリカム１４  ON進角  時間	*/
_SVP_RCAMOF_SA13	.SRES	2	;				/* ロータリカム１４  OFF進角  角度	*/
_SVP_RCAMOF_ST13	.SRES	2	;				/* ロータリカム１４  OFF進角  時間	*/
_SVP_RCAMON_SA14	.SRES	2	;				/* ロータリカム１５  ON進角  角度	*/
_SVP_RCAMON_ST14	.SRES	2	;				/* ロータリカム１５  ON進角  時間	*/
_SVP_RCAMOF_SA14	.SRES	2	;				/* ロータリカム１５  OFF進角  角度	*/
_SVP_RCAMOF_ST14	.SRES	2	;				/* ロータリカム１５  OFF進角  時間	*/
_SVP_RCAMON_SA15	.SRES	2	;				/* ロータリカム１６  ON進角  角度	*/
_SVP_RCAMON_ST15	.SRES	2	;				/* ロータリカム１６  ON進角  時間	*/
_SVP_RCAMOF_SA15	.SRES	2	;				/* ロータリカム１６  OFF進角  角度	*/
_SVP_RCAMOF_ST15	.SRES	2	;				/* ロータリカム１６  OFF進角  時間	*/

_SVP_SMPMAX_CNT2	.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　最大個数(SIT)
_SVP_SMPCYC_TIM2	.SRES	2	; ｻﾝﾌﾟﾘﾝｸﾞ　周期(SIT)

_SVP_MOTREP_STGS	.SRES	2	;繰り返し開始行程
_SVP_MOTREP_STGE	.SRES	2	;繰り返し終了行程
_SVP_MOTREP_SPD		.SRES	2	;繰り返し戻り速度
_SVP_MOTREP_CNT		.SRES	2	;繰り返し回数

_SVP_ROTCAM_ONR		.SRES	2	;ﾛｰﾀﾘｶﾑ ON行程 ﾘﾋﾟｰﾄ戻り
_SVP_ROTCAM_OFR		.SRES	2	;ﾛｰﾀﾘｶﾑ OFF行程 ﾘﾋﾟｰﾄ戻り
_SVP_EJECAM_ONR		.SRES	2	;ｴｼﾞｪｸﾀ ON行程 ﾘﾋﾟｰﾄ戻り
_SVP_EJECAM_OFR		.SRES	2	;ｴｼﾞｪｸﾀ OFF行程 ﾘﾋﾟｰﾄ戻り
_SVP_MISCAM_ONR		.SRES	2	;ﾐｽﾌｨｰﾄﾞ  ON行程 ﾘﾋﾟｰﾄ戻り
_SVP_MISCAM_OFR		.SRES	2	;ﾐｽﾌｨｰﾄﾞ  OFF行程 ﾘﾋﾟｰﾄ戻り

_SVP_MOT_FIX		.SRES	2	;一定速度領域 行程BIT情報


;	***********************************************************
;	***		実測関連				***
;	***********************************************************
	.ORG	H'1A00					;

;	=== 2014/04/16 SHIMA ===
_PVP_CKAGL_OVBIT	.SRES	2		;赤表示(BIT0~BIT9)
_PVP_CKLMT_AGLTOP:
_PVP_CKLMT_AGL01	.SRES	2		;1段目
_PVP_CKLMT_AGL02	.SRES	2		;2段目
_PVP_CKLMT_AGL03	.SRES	2		;3段目
_PVP_CKLMT_AGL04	.SRES	2		;4段目
_PVP_CKLMT_AGL05	.SRES	2		;5段目
_PVP_CKLMT_AGL06	.SRES	2		;6段目
_PVP_CKLMT_AGL07	.SRES	2		;7段目
_PVP_CKLMT_AGL08	.SRES	2		;8段目
_PVP_CKLMT_AGL09	.SRES	2		;9段目
_PVP_CKLMT_AGL10	.SRES	2		;10段目

;	=== 2014/08/27 ===	SHIMA
_PVP_WTJUD_SNO		.SRES	2	;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（行程）
_PVP_WTJUD_AGL		.SRES	2	;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（角度）
	.ALIGN	4
_PVP_WTJUD_POS		.SRES	4	;//ｽﾗｲﾄﾞ自動待機機能  待機判定位置（位置）

;	=== 2014/09/02 ===	SHIMA
_PVP_SINKAKU_UPDN1	.SRES	2	;//BITn：1=ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。
_PVP_SINKAKU_UPDN2	.SRES	2	;//BITn：1=ﾛｰﾀﾘｶﾑnのON進角が加減速範囲にある。


;	==== 2015/07/03[速度ﾘﾐｯﾄ青●表示] ====
;	==== 2015/07/07[速度ﾘﾐｯﾄ対象行程] ====
_PVP_CKSPD_LMBIT	.SRES	2		;青●表示(BIT0~BIT9 BIT15:戻速度)[16F6]
_PVP_CKSPD_STPBT	.SRES	2		;速度ﾘﾐｯﾄ対象行程 BIT0~BIT9,BIT15(ﾁｪｯｸ対象行程)


;	=== 2021-06-24[H2W-CE3:2020-08-11 ﾀﾞｲﾊｲﾄANSﾊﾞｯｸ]=======
	.ALIGN	4
_PVP_ATSLID_OBJ1	.SRES		4	; スライド自動調節設定値（現在動作中）0.001mmのANSﾊﾞｯｸ [***]





;	------------- これはいつでもこのファイルの最後 1FFE以下かｿﾌﾄでﾁｪｯｸする-------------------
_DP_CPUDCOM_FILE_END	.SRES	2		;ｿﾌﾄ
;--------------------------- "1FFF"まで 2000~はcpud-bまたはcpud-a専用--------------------------------------