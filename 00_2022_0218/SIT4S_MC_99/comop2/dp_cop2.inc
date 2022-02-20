;	*******************************************************************
;	***								***
;	***								***
;	***								***
;	***	cpuA(sh4)-Servo-Cpu(sh4) I/F Dual Port RAM		***
;	***								***
;	***								***
;	***								***
;	*******************************************************************
;	このファイルはsh4のアセンブラソースにインクルードされ
;	その中で、実アドレスを割り付ける			
;	このではdpramのオフセットアドレスを定義する
;	このファイルのextern宣言として
;	dp_.ext(ｱｾﾝﾌﾞﾗ用)
;	dp_.h(c言語ｿｰｽ用)
;

;	*******************************************
;	***					***
;	***					***
;	*******************************************
		.ORG	H'0000		;
_COP2DPRAM_TOP:

_COP2_CPUA_COD1		.SRES	4	;CPUA-->COP2 WR:12345678//COP2 0CLR
_COP2_CPUA_COD2		.SRES	4	;CPUA-->COP2 WR:9ABCEDF0//COP2 0CLR
_COP2_COP2_COD1		.SRES	4	;COP2-->CPUA WR:NOT 12345678
_COP2_COP2_COD2		.SRES	4	;COP2-->CPUA WR:NOT 9ABCDEF0

;	----------- 16byte 
_DEBUG_COP2_SIG1	.SRES	2	;
_DEBUG_COP2_SIG2	.SRES	2	;

_COP2_PLS_OUTF		.SRES	2	;
_COP2_CPUA_SV_STEP	.SRES	2	;
_COP2_CPUB_SV_STEP	.SRES	2	;
_COP2_CPUC_SV_STEP	.SRES	2	;

;	*******************************************
;	***					***
;	***	SH2<->SH4　ﾊﾝﾄﾞｼｪｲｸ		***
;	***					***
;	*******************************************
		.ORG	H'0020
_COP2_HS_SVCHG_B_TO_A	.SRES	4	;
_COP2_HS_SVCHG_A_TO_B	.SRES	4	;

_COP2_HS_PVP_TAKIKI_FLG	.SRES	2	;
_COP2_HS_PVP_LOTCNT_FLG	.SRES	2	;

;	==== 2003-07-09 ===
_COP2_CMD_1CYCLE_DSP1	.SRES	2	;
_COP2_CMD_DAIPOS_DSP1	.SRES	2	;

	.ALIGN	4			;
_COP2_PSD_ORG_PLS1	.SRES	4	;ORIGIN DATA(FUNUC)
_COP2_PSD_ORG_PLS2	.SRES	4	;ORIGIN DATA(FUNUC)
_COP2_PSD_ORG_PLS_CMD1	.SRES	2	;
_COP2_PSD_ORG_PLS_CMD2	.SRES	2	;

;	==== 2013-01-10 =============
_COP2_PV_CH2_OUTPUTF	.SRES	2		;3C,3D
;3E,3F あと2BYTEまで


;	***************************************************
;	***	4/2BYTE  ﾊﾞｯｸｱｯﾌﾟ返し領域(64b)		***
;	***************************************************
		.ORG	H'0040
_COP2_SVB_RNAORG_PLS1	.SRES	4		;ﾘﾆｱ基準位置ﾊﾟﾙｽ
						;予備4byte領域
_COP2_SVB_DYHITO_POS	.SRES	4		;2003-07-09 ﾀﾞｲﾊｲﾄ(下限位置)
_COP2_SVB_SLIDE_POS	.SRES	4		;2003-07-09 生産下限位置

_COP2_SVB_BAKORG_PLS1	.SRES	4		;ﾘﾆｱ基準位置mm
_COP2_SVB_BAKORG_PLS2	.SRES	4		;ﾘﾆｱ基準位置mm

;	***************************************************
;	***	ｻｰﾎﾞﾊﾟﾗﾒｰﾀ領域	4/2BYTE領域		***
;	***************************************************
		.ORG	H'0060
_COP2_SVP_RNADIR_SEL1		.SRES	2	;ﾘﾆｱｾﾝｻ極性
_COP2_SVP_INCDIR_SEL1		.SRES	2	;PG極性
_COP2_SVP_INCPLS_1REV		.SRES	2	;PG1回転のﾊﾟﾙｽ選択
_COP2_SVP_INCPLS_HOSN		.SRES	2	;PG補正N　ﾓｰﾀN回
_COP2_SVP_INCPLS_HOSM		.SRES	2	;PG補正M　ｸﾗﾝｸ角度M
_COP2_SVP_MOTRPM_MAXM		.SRES	2	;ﾓｰﾀ最大回転数

	.ALIGN	4				;
_COP2_SVP_MOTMAX_FREQ		.SRES	4	;ﾓｰﾀ最大時指令周波数
_COP2_SVP_RNAORG_POS1		.SRES	4	;機械原点入力
_COP2_SVP_RNAPOS_MAXP		.SRES	4	;機械上限
_COP2_SVP_RNAPOS_MINP		.SRES	4	;機械下限
_COP2_SVP_UPAREA_JUDG		.SRES	4	;上死点判定範囲
_COP2_SVP_DNAREA_JUDG		.SRES	4	;反転設定不可範囲



_COP2_SVP_DNDINC_SPD1		.SRES	2	;段取速度	
_COP2_SVP_UPAREA_SPD1		.SRES	2	;待機点復帰速度	
_COP2_SVP_STDINC_SPD1		.SRES	2	;寸動速度	
_COP2_SVP_REVDAT_SPD1		.SRES	2	;予備速度１	(クリープ速度)
_COP2_SVP_REVDAT_SPD2		.SRES	2	;予備速度２	(自起動INCHING)
_COP2_SVP_REVDAT_SPD3		.SRES	2	;予備速度３	
_COP2_SVP_TEPDAT_SPD1		.SRES	2	;手動ﾊﾟﾙｻ速度	
_COP2_SVP_TEPLAT_DAT1		.SRES	2	;手動ﾊﾟﾙｻ低倍率	
_COP2_SVP_TEPLAT_DAT2		.SRES	2	;手動ﾊﾟﾙｻ高倍率	

_COP2_SVP_INCPOS_KP01		.SRES	2	;PG位置比例ｹﾞｲﾝ
_COP2_SVP_RNAPOS_KP01		.SRES	2	;ﾘﾆｱ位置比例ｹﾞｲﾝ
_COP2_SVP_ACCLAT_TIM1		.SRES	2	;加減速時間
_COP2_SVP_SSCURV_TIM1		.SRES	2	;Ｓ字時間
_COP2_SVP_UPAREA_INP1		.SRES	2	;上死点ｲﾝﾎﾟｼﾞｼｮﾝ
_COP2_SVP_DNAREA_INP1		.SRES	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ
_COP2_SVP_OBJARA_INP1		.SRES	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ
_COP2_SVP_INPPOS_TIM1		.SRES	2	;ｲﾝﾎﾟｼﾞｼｮﾝﾁｪｯｸ時間
_COP2_SVP_ARACHK_LNG1		.SRES	2	;上／下死点通過判定量
_COP2_SVP_UPAREA_DIG1		.SRES	2	;回転時待機点(上死点)

_COP2_SVP_INCHEN_ELNG		.SRES	2	;PG偏差異常幅
_COP2_SVP_INCENC_ELNG		.SRES	2	;PG-ENC一致量 0.1度
_COP2_SVP_INCRNA_ELNG		.SRES	2	;PG-ﾘﾆｱ一致量
_COP2_SVP_INCSTP_ELNG		.SRES	2	;PG停止異常量
_COP2_SVP_RNASTP_ELNG		.SRES	2	;ﾘﾆｱ停止異常量
_COP2_SVP_INCREV_ELNG		.SRES	2	;PG逆転異常量
_COP2_SVP_RNAREV_ELNG		.SRES	2	;ﾘﾆｱ逆転異常量
_COP2_SVP_DAIHAI_LNG1		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(小)
_COP2_SVP_DAIHAI_LNG2		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(中)
_COP2_SVP_DAIHAI_LNG3		.SRES	2	;ﾀﾞｲﾊｲﾄ補正比較値(大)

_COP2_SVP_AMPERR_VLT1		.SRES	2	;過負荷電圧1
_COP2_SVP_AMPERR_TIM1		.SRES	2	;過負荷時間1
_COP2_SVP_AMPERR_VLT2		.SRES	2	;過負荷電圧2
_COP2_SVP_AMPERR_TIM2		.SRES	2	;過負荷時間2
_COP2_SVP_AMPERR_VLT3		.SRES	2	;過負荷電圧3
_COP2_SVP_AMPERR_TIM3		.SRES	2	;過負荷時間3

;	==== 2002-08-08 ==
_COP2_SVP_CNT_TIM			.SRES	2	;連続タイマ
_COP2_SVP_CNT_CNT			.SRES	2	;連続カウンタ
_COP2_SVP_BREAK_DIG			.SRES	2	;ﾌﾞﾚｰｷ角度   0.1度
_COP2_SVP_BREAK_TIM1			.SRES	2	;ブレーキタイマ設定
_COP2_SVP_WT_DIG1			.SRES	2	;待機点選択1
_COP2_SVP_WT_DIG2			.SRES	2	;待機点選択2
_COP2_SVP_WT_DIG3			.SRES	2	;待機点選択3
_COP2_SVP_MOTWT_TIM			.SRES	2	;起動保証時間
_COP2_SVP_PSMOD_SEL			.SRES	2	;PSID　ﾓｰﾄﾞ選択

;	==== 2002-08-21 ==
	.ALIGN	4				;
_COP2_SVP_RNA_STLORK			.SRES	4	;
_COP2_SVP_OUTPLS_HOSA		.SRES	2	;
_COP2_SVP_OUTPLS_HOSB		.SRES	2	;
_COP2_SVP_UPHOLD_DIG			.SRES	2	;
_COP2_SVP_MACINE_SEL1		.SRES	2	;

;	==== 2003-01-27 ==
	.ALIGN	4				;
_COP2_SVP_NEG_OFS_LNG		.SRES	4	;反転下限距離(0.001mm ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)
_COP2_SVP_AMP100P_VLT		.SRES	2	;AMP100%相当時の電圧値 0~10.0v(ｻｰﾎﾞﾊﾟﾗﾒｰﾀ)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
	.ALIGN	4				;
_COP2_SVP_LSAABN_AGL1		.SRES	4	;//LSA異常検知の角度1
_COP2_SVP_LSAABN_AGL2		.SRES	4	;//LSA異常検知の角度2
_COP2_SVP_PLSALO_PLS			.SRES	2	;//パルサ倍率低
_COP2_SVP_PLSAHI_PLS			.SRES	2	;//パルサ倍率高

;	***************************************************
;	***	ｸﾗｯﾁ制御画面設定1 4/2BYTE領域		***
;	***************************************************
	.ALIGN	4				;
_COP2_SVP_OBJECT_POS_TOP:
_COP2_SVP_OBJECT_PS01		.SRES	4	;01段目目標位置
_COP2_SVP_OBJECT_PS02		.SRES	4	;02段目目標位置
_COP2_SVP_OBJECT_PS03		.SRES	4	;03段目目標位置
_COP2_SVP_OBJECT_PS04		.SRES	4	;04段目目標位置
_COP2_SVP_OBJECT_PS05		.SRES	4	;05段目目標位置
_COP2_SVP_OBJECT_PS06		.SRES	4	;06段目目標位置
_COP2_SVP_OBJECT_PS07		.SRES	4	;07段目目標位置
_COP2_SVP_OBJECT_PS08		.SRES	4	;08段目目標位置
_COP2_SVP_OBJECT_PS09		.SRES	4	;09段目目標位置
_COP2_SVP_OBJECT_PS10		.SRES	4	;10段目目標位置
_COP2_SVP_OBJECT_PS11		.SRES	4	;11段目目標位置
_COP2_SVP_OBJECT_PS12		.SRES	4	;12段目目標位置
_COP2_SVP_OBJECT_PS13		.SRES	4	;13段目目標位置
_COP2_SVP_OBJECT_PS14		.SRES	4	;14段目目標位置
_COP2_SVP_OBJECT_PS15		.SRES	4	;15段目目標位置
_COP2_SVP_OBJECT_PS16		.SRES	4	;16段目目標位置
_COP2_SVP_OBJECT_PS17		.SRES	4	;17段目目標位置
_COP2_SVP_OBJECT_PS18		.SRES	4	;18段目目標位置
_COP2_SVP_OBJECT_PS19		.SRES	4	;19段目目標位置
_COP2_SVP_OBJECT_PS20		.SRES	4	;20段目目標位置

_COP2_SVP_OBJECT_DIG_TOP:				;01段目角度位置
_COP2_SVP_OBJECT_DG01		.SRES	2	;01段目角度位置
_COP2_SVP_OBJECT_DG02		.SRES	2	;02段目角度位置
_COP2_SVP_OBJECT_DG03		.SRES	2	;03段目角度位置
_COP2_SVP_OBJECT_DG04		.SRES	2	;04段目角度位置
_COP2_SVP_OBJECT_DG05		.SRES	2	;05段目角度位置
_COP2_SVP_OBJECT_DG06		.SRES	2	;06段目角度位置
_COP2_SVP_OBJECT_DG07		.SRES	2	;07段目角度位置
_COP2_SVP_OBJECT_DG08		.SRES	2	;08段目角度位置
_COP2_SVP_OBJECT_DG09		.SRES	2	;09段目角度位置
_COP2_SVP_OBJECT_DG10		.SRES	2	;10段目角度位置
_COP2_SVP_OBJECT_DG11		.SRES	2	;予備11段目角度位置
_COP2_SVP_OBJECT_DG12		.SRES	2	;予備12段目角度位置
_COP2_SVP_OBJECT_DG13		.SRES	2	;予備13段目角度位置
_COP2_SVP_OBJECT_DG14		.SRES	2	;予備14段目角度位置
_COP2_SVP_OBJECT_DG15		.SRES	2	;予備15段目角度位置
_COP2_SVP_OBJECT_DG16		.SRES	2	;予備16段目角度位置
_COP2_SVP_OBJECT_DG17		.SRES	2	;予備17段目角度位置
_COP2_SVP_OBJECT_DG18		.SRES	2	;予備18段目角度位置
_COP2_SVP_OBJECT_DG19		.SRES	2	;予備19段目角度位置
_COP2_SVP_OBJECT_DG20		.SRES	2	;予備20段目角度位置

_COP2_SVP_OBJECT_SPD_TOP:				;01段目移動速度
_COP2_SVP_OBJECT_SP01		.SRES	2	;01段目移動速度
_COP2_SVP_OBJECT_SP02		.SRES	2	;02段目移動速度
_COP2_SVP_OBJECT_SP03		.SRES	2	;03段目移動速度
_COP2_SVP_OBJECT_SP04		.SRES	2	;04段目移動速度
_COP2_SVP_OBJECT_SP05		.SRES	2	;05段目移動速度
_COP2_SVP_OBJECT_SP06		.SRES	2	;06段目移動速度
_COP2_SVP_OBJECT_SP07		.SRES	2	;07段目移動速度
_COP2_SVP_OBJECT_SP08		.SRES	2	;08段目移動速度
_COP2_SVP_OBJECT_SP09		.SRES	2	;09段目移動速度
_COP2_SVP_OBJECT_SP10		.SRES	2	;10段目移動速度
_COP2_SVP_OBJECT_SP11		.SRES	2	;予備11段目移動速度
_COP2_SVP_OBJECT_SP12		.SRES	2	;予備12段目移動速度
_COP2_SVP_OBJECT_SP13		.SRES	2	;予備13段目移動速度
_COP2_SVP_OBJECT_SP14		.SRES	2	;予備14段目移動速度
_COP2_SVP_OBJECT_SP15		.SRES	2	;予備15段目移動速度
_COP2_SVP_OBJECT_SP16		.SRES	2	;予備16段目移動速度
_COP2_SVP_OBJECT_SP17		.SRES	2	;予備17段目移動速度
_COP2_SVP_OBJECT_SP18		.SRES	2	;予備18段目移動速度
_COP2_SVP_OBJECT_SP19		.SRES	2	;予備19段目移動速度
_COP2_SVP_OBJECT_SP20		.SRES	2	;予備20段目移動速度

_COP2_SVP_OBJECT_TIM_TOP				;01段目停止時間
_COP2_SVP_OBJECT_TM01		.SRES	2	;01段目停止時間
_COP2_SVP_OBJECT_TM02		.SRES	2	;02段目停止時間
_COP2_SVP_OBJECT_TM03		.SRES	2	;03段目停止時間
_COP2_SVP_OBJECT_TM04		.SRES	2	;04段目停止時間
_COP2_SVP_OBJECT_TM05		.SRES	2	;05段目停止時間
_COP2_SVP_OBJECT_TM06		.SRES	2	;06段目停止時間
_COP2_SVP_OBJECT_TM07		.SRES	2	;07段目停止時間
_COP2_SVP_OBJECT_TM08		.SRES	2	;08段目停止時間
_COP2_SVP_OBJECT_TM09		.SRES	2	;09段目停止時間
_COP2_SVP_OBJECT_TM10		.SRES	2	;10段目停止時間
_COP2_SVP_OBJECT_TM11		.SRES	2	;11段目停止時間
_COP2_SVP_OBJECT_TM12		.SRES	2	;12段目停止時間
_COP2_SVP_OBJECT_TM13		.SRES	2	;13段目停止時間
_COP2_SVP_OBJECT_TM14		.SRES	2	;14段目停止時間
_COP2_SVP_OBJECT_TM15		.SRES	2	;15段目停止時間
_COP2_SVP_OBJECT_TM16		.SRES	2	;16段目停止時間
_COP2_SVP_OBJECT_TM17		.SRES	2	;17段目停止時間
_COP2_SVP_OBJECT_TM18		.SRES	2	;18段目停止時間
_COP2_SVP_OBJECT_TM19		.SRES	2	;19段目停止時間
_COP2_SVP_OBJECT_TM20		.SRES	2	;20段目停止時間

;	***************************************************
;	***	ｸﾗｯﾁ制御画面設定2 4/2BYTE領域		***
;	***************************************************
	.ALIGN	4				;
_COP2_SVP_DAIHAI_ORG0		.SRES	4	;ダイハイト
_COP2_SVP_MRTION_SEL1		.SRES	2	;回転方式
_COP2_SVP_MTSTEP_MAXM		.SRES	2	;段数
	.ALIGN	4				;
_COP2_SVP_UPAREA_POS0		.SRES	4	;待機点位置
_COP2_SVP_UPAREA_DIG0		.SRES	2	;待機点角度
_COP2_SVP_UPAREA_SPD0		.SRES	2	;基準速度
_COP2_SVP_UPAREA_TIM0		.SRES	2	;待機時間
_COP2_SVP_DNAREA_INP0		.SRES	2	;下死点ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
_COP2_SVP_OBJARA_INP0		.SRES	2	;目標位置ｲﾝﾎﾟｼﾞｼｮﾝ(2002-06-28)
_COP2_SVP_DAIHSA_LENG		.SRES	2	;ﾀﾞｲﾊｲﾄ補正距離

;	==== 2002-08-08======
	.ALIGN	4				;
_COP2_SVP_SLID_POS1		.SRES	4	;ｽﾗｲﾄﾞ位置　生産
_COP2_SVP_SLID_POS2		.SRES	4	;ｽﾗｲﾄﾞ位置　段取1
_COP2_SVP_SLID_POS3		.SRES	4	;ｽﾗｲﾄﾞ位置　段取2

;	===== 2002-08-29==
	.ALIGN	4				;
_COP2_SVP_ATSLID_OBJ1	.SRES		4	; スライド自動調節設定値（現在動作中）0.001mm
_COP2_SVP_ATSLID_DNOBJ1	.SRES		2	; スライド自動調節　下降停止 0~99
_COP2_SVP_ATSLID_UPOBJ1	.SRES		2	; スライド自動調節　上昇停止 "
_COP2_SVP_ATSLID_BAKLNG	.SRES		2	; スライド自動調節　戻り量   "
_COP2_SVP_ATSLID_COEF1	.SRES		2	; スライド自動調節　制御精度 "

;	===== 2004-06-08　=====
_COP2_SVP_KAJYUU_PRS1	.SRES	2		;荷重補正 1Kn (2004-06-08)
_COP2_SVP_KAJYUU_OBJP	.SRES	2		;荷重目標値 1Kn(2004-07-01)
_COP2_SVP_KAJYUU_PV1		.SRES	2		;最大荷重(ｵﾌﾟｼｮﾝの実測をC/Bの設定として渡す)

;	=== 2006-07-11 ===	SHIMA(HMI:V01v)
_COP2_PVP_KAJLIV_LFT		.SRES	2		;//荷重生（TON）(1word)
_COP2_PVP_KAJLIV_TTL		.SRES	2		;//荷重生（TON）(1word)
_COP2_PVP_KAJLIV_RIH		.SRES	2		;//荷重生（TON）(1word)


;	=====2006-07-24(ｵｰﾊﾞﾗｲﾄﾞ) ====
_COP2_SVP_OVERLIDE_COF	.SRES	2		;0,1~127%
_COP2_SVP_DND_STOPDIG1	.SRES	2		;段取停止角度 0~358.0
;;[]
;;[];	=====2006-07-24(荷重補正) ====
;;[]_COP2_SVP_KJSTR_STEP1	.SRES	2		;0,1~工程 
;;[]_COP2_SVP_KJSTR_DIG1		.SRES	2		;359.0
;;[]_COP2_SVP_KJEND_STEP1	.SRES	2		;0,1~工程
;;[]_COP2_SVP_KJEND_DIG1		.SRES	2		;359.0
_COP2_PVP_ARA1_KAJ_R		.SRES	2		;OPTION 区間最大荷重
_COP2_PVP_ARA1_KAJ_L		.SRES	2		;OPTION 区間最大荷重
_COP2_PVP_ARA1_KAJ_T		.SRES	2		;OPTION 区間最大荷重TOTALのみ使用

;	=====2006-10-13(COP2関係) ====
	.ALIGN	4
;;[]_COP2_PVP_ORGRNA_MOV1		.SRES	4		;ﾘﾆｱ移動量実測1
;;[]_COP2_PVP_ORGRNA_MOV2		.SRES	4		;ﾘﾆｱ移動量実測2
;;[]_COP2_PVP_ORGSTRK_LEG1		.SRES	4		;ｽﾄﾛｰｸ1実測
;;[]_COP2_PVP_ORGSTRK_LEG2		.SRES	4		;ｽﾄﾛｰｸ2実測
;;[]_COP2_PVP_BAKORG_PLS1		.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
;;[]_COP2_PVP_BAKORG_PLS2		.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
;;[]_COP2_PVP_RENIA_POS1		.SRES	4		;ﾘﾆｱｽｹｰﾙ1実測
;;[]_COP2_PVP_RENIA_POS2		.SRES	4		;ﾘﾆｱｽｹｰﾙ2実測
;;[]_COP2_PVP_360_DEG		.SRES	2		;360度ｴﾝｺｰﾀﾞ角度
;;[]_COP2_PVP_PG_DEG1		.SRES	2		;PG角度1
;;[]_COP2_PVP_PG_DEG2		.SRES	2		;PG角度2
;;[]_COP2_PVP_ZURE_PLS		.SRES	2		;軸間ｽﾞﾚ実測
;;[]_COP2_PVP_ZURE_RNA		.SRES	2		;軸間ｽﾞﾚﾘﾆｱ

	.ALIGN	4
;;[]_COP2_SVP_ORGSOK_PLS		.SRES	4		;原点測定ﾊﾟﾙｽ
;;[]_COP2_SVP_ORGCAL_DAT1		.SRES	4		;演算係数1
;;[]_COP2_SVP_ORGCAL_DAT2		.SRES	4		;演算係数2
;;[]_COP2_SVP_ORGCAL_DAT3		.SRES	4		;演算係数3
;;[]_COP2_SVP_ORGCAL_DAT4		.SRES	4		;演算係数4
;;[]_COP2_SVP_ORGCAL_DAT5		.SRES	4		;演算係数5
;;[]_COP2_SVP_ORGCAL_DAT6		.SRES	4		;演算係数6
;;[]_COP2_SVP_ORGSTRK_LEN1		.SRES	4		;ｽﾄﾛｰｸ1
;;[]_COP2_SVP_ORGSTRK_LEN2		.SRES	4		;ｽﾄﾛｰｸ2
;;[]_COP2_SVP_RNAORGMEM_LEG1	.SRES	4		;ﾘﾆｱ原点1軸記憶
;;[]_COP2_SVP_RNAORG_PLS1		.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
;;[]_COP2_SVP_RNAORGMEM_LEG2	.SRES	4		;ﾘﾆｱ原点2軸記憶
;;[]_COP2_SVP_RNAORG_PLS2		.SRES	4		;ﾊﾞｯｸｱｯﾌﾟ実測
;;[]_COP2_SVP_RNAORG_SIN1		.SRES	2		;ﾊﾞｯｸｱｯﾌﾟ実測符号
;;[]_COP2_SVP_RNAORG_SIN2		.SRES	2		;ﾊﾞｯｸｱｯﾌﾟ実測符号
;;[]_COP2_SVP_ORGRUP_DEG		.SRES	2		;原点右区間上
;;[]_COP2_SVP_ORGRDN_DEG		.SRES	2		;原点右区間下
;;[]_COP2_SVP_ORGLUP_DEG		.SRES	2		;原点左区間上
;;[]_COP2_SVP_ORGLDN_DEG		.SRES	2		;原点左区間下
;;[]_COP2_SVP_ORGMEM_DEG1		.SRES	2		;角度1軸
;;[]_COP2_SVP_ORGMEM_DEGS1		.SRES	2		;角度1軸　ON/OFF
;;[]_COP2_SVP_ORGMEM_DEG2		.SRES	2		;角度2軸
;;[]_COP2_SVP_ORGMEM_DEGS2		.SRES	2		;角度2軸　ON/OFF
;;[]_COP2_SVP_ORGMPL_SEL1		.SRES	2		;手ﾊﾟﾙｻ選択1軸　ON/OFF
;;[]_COP2_SVP_ORGMPL_SEL2		.SRES	2		;手ﾊﾟﾙｻ選択2軸　ON/OFF
;;[]_COP2_SVP_HOSRAG_PLS1		.SRES	2		;軸間補正範囲１
;;[]_COP2_SVP_HOSRAG_PLS2		.SRES	2		;軸間補正範囲２（ｼｽﾃﾑ異常）
;;[]_COP2_SVP_HOSEI_SPD		.SRES	2		;補正速度
;;[]_COP2_SVP_MANSAM_LEN		.SRES	2		;手動時同期
;;[]_COP2_SVP_DANSAM_LEN		.SRES	2		;段取字同期
;;[]_COP2_SVP_RUNSAMER_LEN1		.SRES	2		;運転同期異常１　未使用に変更
;;[]_COP2_SVP_RUNSAMER_LEN2		.SRES	2		;運転同期異常２
;;[]_COP2_SVP_MANSAMER_PLS		.SRES	2		;手動同期異常
;;[]_COP2_SVP_RUNSAMER_PLS		.SRES	2		;運転同期異常



;	*******************************************
;	***					***
;	***		予備			***
;	***	通信やﾄﾚﾝﾄﾞ関係			***
;	*******************************************
;	***************************
;	***	ﾃﾞﾊﾞｯｸ画面	***
;	***************************
	.ALIGN	4

;	*******************************************
;	***		実測 4/2BYTE領域	***
;	*******************************************
	.ALIGN	4
;;[]_COP2_PVP_RNAORG_PLS1		.SRES	4	;ﾘﾆｱ基準位置ﾊﾟﾙｽ(ﾊﾞｯｸｱｯﾌﾟ専用)
;;[]_COP2_PVP_NOW_POSI000		.SRES	4	;下死点高さ位置(表示用 原点完了まではABS値)
;;[]_COP2_PVP_RENIA_POSI0		.SRES	4	;リニアセンサ現在位置(生表示用 ABS値 何も使っていない?HMIで)
;;[]_COP2_PVP_NOW_ANGLE00		.SRES	2	;SH2->SH4　360度ｴﾝｺｰﾀﾞ(CHEAK用)
;;[]_COP2_PVP_CYCLE_TIME0		.SRES	2	;サイクル時間表示用
;;[];	----- 追加2002/07/02 ---
;;[]_COP2_PVP_CYCLE_SPM1			.SRES	2	;サイクル速度表示用
;;[]_COP2_PVP_DISP_SPM2			.SRES	2	;高速時描画を塗りつぶしにする為の速度(単位不明)
;;[]_COP2_PVP_NOW_ANGLE_RNA		.SRES	2	;現在角度0.1度HEX(ﾘﾆｱｽｹｰﾙからの1度単位 SH4->SH2)(画面表示用)
;;[]_COP2_PVP_DYHITO_HOSLNG		.SRES	2	;ﾀﾞｲﾊｲﾄ補正量 1um(0.001mm) +/-
;;[]	.ALIGN	4				;
;;[]_COP2_PVP_DYHITO_POS			.SRES	4	;ﾀﾞｲﾊｲﾄ実測 生産初期画面表示値 
;;[]						;2003-07-09 下限位置のまま
;;[]_COP2_PVP_SLIDE_POS		.SRES	4	;ｽﾗｲﾄﾞ位置・ﾀﾞｲﾊｲﾄを含めた位置(ｸﾗｯﾁは未使用)
;;[]						;2003-07-09 生産下限位置
;;[]_COP2_PVP_TAIKITEN_POS		.SRES	2	;待機点角度表示（描画用）
;;[]
;;[];	----- 追加2002/08/01 ---
;;[]	.ALIGN	4				;
;;[]_COP2_PVP_RNA_STLORK			.SRES	4	;ｽﾄﾛｰｸ実測
;;[]_COP2_PVP_STOP_TIM			.SRES	2	;ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ 1msec data
;;[]_COP2_PVP_BREAK_DIG			.SRES	2	;ﾌﾞﾚｰｷ角度   0.1度
;;[]_COP2_PVP_BREAK_TIM1			.SRES	2	;
;;[]
;;[]
;;[];	========== 2003-01-27 過負荷実測追加====
;;[]_COP2_PVP_POWER_MONI		.SRES	2	;ADR=3854
;;[]
;	========= 2003-02-04 ======
_COP2_PVP_CPUA_TEPPLS		.SRES	2	;
_COP2_PVP_CPUA_ANAIN		.SRES	2	;

	.ALIGN	4			;
_COP2_PVP_ENC_PLS_SPD	.SRES	4	;SHIN
_COP2_PVP_OUT_PLS_SPD	.SRES	4	;SHIN
_COP2_PVP_ABS_ENC_SPD	.SRES	4	;ABS
_COP2_PVP_ABS_OUT_SPD	.SRES	4	;ABS
_COP2_PVP_ENC_SPD_PER	.SRES	2	;
_COP2_PVP_OUT_SPD_PER	.SRES	2	;
_COP2_PVP_BRK_ENC_SPD	.SRES	2	;
_COP2_PVP_BRK_OUT_SPD	.SRES	2	;
_COP2_PVP_ENC_SPD_DIR	.SRES	2	;
_COP2_PVP_OUT_SPD_DIR	.SRES	2	;


;	*******************************************
;	***					***
;	***	2002-08-29			***
;	***	固定実測(ﾊﾞｰｼﾞｮﾝ表示)		***
;	*******************************************
	.ALIGN	4
_COP2_COP2_PVP_CB_A_VER		.SRES	2*6	;ASCIIﾃﾞｰﾀ (1WORDでｷｬﾗｸﾀする 6char) SH4-->
_COP2_COP2_PVP_CB_B_VER		.SRES	2*6	;ASCIIﾃﾞｰﾀ (6char) SH2-->

;	======= 2003-01-27 ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ追加 =====
_COP2_PVP_PAR_A_VER		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ HEX data
_COP2_PVP_TBL_A_VER		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号1~99 HEX data
_COP2_PVP_PAR_A_CHAR		.SRES	2	;ﾊﾟﾗﾒｰﾀﾊﾞｰｼﾞｮﾝ 末尾ｷｬﾗｸﾀ ASCII(2BYTE)
_COP2_PVP_TBL_A_CHAR		.SRES	2	;ｾﾝｻのﾃｰﾌﾞﾙ番号()


;	=== 2004-01-27 ERR-INFO ===
_COP2_ERR_INFO_CPUA_FLG	.SRES	2	;CPUA=>WRITE 55AA CPUB=>0CLR
	.ALIGN	4						;
_COP2_ERR_INFO_CPUA_TOP	.SRES	_CB_ERR_INFO_MEM	;80	;(CPUAはDPRAM経由)<4の倍数>

;	*******************************************
;	***					***
;	***	SH2←SH4　ﾊﾝﾄﾞｼｪｲｸ		***
;	***					***
;	*******************************************
	.ALIGN	4
_COP2_PVX_RNA_INDAT		.SRES	4	;生	SH4-->SH2 生
_COP2_PVX_RNA_POSD1		.SRES	4	;変換	SH4-->SH2 極性・ｵﾌｾｯﾄ分
_COP2_PVX_RNA_POSD2		.SRES	4	;変換	SH4-->SH2 0.5um->1mm+原点
_COP2_PVX_RNA_POSDT		.SRES	4	;制御用
_COP2_PVX_RNA_DIGDT		.SRES	4	;角度	360.0度程度 RNAｾﾝｻから求まる角度
_COP2_PVX_RNA_PLS_P		.SRES	4	;RNAｾﾝｻから求まるｵﾌｾｯﾄﾊﾟﾙｽP

;	----------- 2007-02-16(共通化)
_COP2_EMG_CPA_TO_CP2:		.SRES	2	;((((CPUA==>COP2))))
_COP2_EXQ_CPA_TO_CP2:		.SRES	2	;((((CPUA==>COP2))))

_COP2_EMG_CP2_TO_CPA:		.SRES	2	;((((COP2==>CPUA))))
_COP2_EXQ_CP2_TO_CPA:		.SRES	2	;((((COP2==>CPUA))))


_COP2_PVX_SH4_OUTPLS		.SRES	4*2	;8BYTE

_COP2_STEP_NO			.SRES	4	;工程二重回路ﾁｪｯｸ用/ COP2=>CPUA
_COP2_STEP_NO_A			.SRES	4	;工程二重回路ﾁｪｯｸ用/ CPUA=>COP2

_COP2_SH4_POS_STS1		.SRES	2	;上記信号 SH4==> WRITE SH2 ==>BIT7 CLR
_COP2_SH2_POS_STS1		.SRES	2	;上記信号 SH2==> WRITE SH4 ==>BIT7 CLR
_COP2_SH4_CMP_STS1		.SRES	2	;(二重化異常信号 203同様      生)
_COP2_SH2_CMP_STS1		.SRES	2	;(二重化異常信号 273同様      生)
_COP2_SH4_CMP_STS2		.SRES	2	;(二重化異常信号 BIT0位置決中 生)
_COP2_SH2_CMP_STS2		.SRES	2	;(二重化異常信号 BIT0位置決中 生)

;	====================================
_COP2_HD_CTRL_REDY	.SRES	2	;準備完了にしたい COP2-->CPUA
_COP2_HD_CTRL_REDY_A	.SRES	2	;準備完了にしたい CPUA-->COP2

_COP2_SH4_HD_CTRL_BUSY	.SRES	2	;NO USED(2008-02-16)
_COP2_SH2_HD_CTRL_BUSY	.SRES	2	;NO USED(2008-02-16)
_COP2_HD_POS_START	.SRES	2	;起動したい
_COP2_HD_POS_START_A	.SRES	2	;起動したい　CPUA==>CPUC

_COP2_HD_SFTY_AUTO	.SRES	2	;AUTOにしたい/安全一工程,連続ｶｳﾝﾀ[2013-04-14]
_COP2_HD_SFTY_AUTO_A	.SRES	2	;AUTOにしたい/安全一工程,連続ｶｳﾝﾀ[2013-04-14]
_COP2_HD_NEAR_ZERO	.SRES	2	;ﾆｱｾﾞﾛ処理を行いたい(COP2)
_COP2_HD_NEAR_ZERO_A	.SRES	2	;ﾆｱｾﾞﾛ処理を行いたい(未使用)
_COP2_HD_CNT_STOP	.SRES	2	;COP2=>CPUA,CPUB  2013-04-14
_COP2_HD_CNT_STOP_A	.SRES	2	;CPUA,CPUB==>COP2 2013-04-14
_COP2_HD_STEP_END	.SRES	2	;位置決め完了としたい(COP2)
_COP2_HD_STEP_END_A	.SRES	2	;位置決め完了としたい(使用済み)
_COP2_HD_CNT_CNT	.SRES	2	;連続停止しないで次へいくぞ[2013-04-14]
_COP2_HD_CNT_CNT_A	.SRES	2	;連続停止しないで次へいくぞ[2013-04-14]

;	===== 2002-09-12 SAITO =====
;	SELF CHECK HAND SHAKE FLG
;	===== 2008-09-21 KOMA =====
_CPUA_COP2_SELF_REQ	.SRES	2	;START/CODE _COP2_CPUA_SELF_HAND_FLG; CPUA-->COP2
_CPUA_COP2_SELF_ANS	.SRES	2	;END _COP2_CPUB_SELF_HAND_FLG	    ; COP2-->CPUA

;	===================================
;	===	各ｶｰﾄﾞのｽﾃｰﾀｽ作成用	===
;	===================================
;	運転開始
;	１工程開始
;	最終工程開始
;	終了/
;	==== 2004-03-01 同期ｽﾞﾚ測定用時間 =====
_COP2_CPU_CTRL_CLK		.SRES	2	;(同期ｽﾞﾚ測定ﾀｲﾑｽﾀﾝﾌﾟ)


;	=========== 2006-04-10 =========
_COP2_CPUA_SELF2_STR		.SRES	2	;
_COP2_CPUA_SELF2_END		.SRES	2	;
_COP2_CPUA_SELF2_CD1		.SRES	2	;
_COP2_CPUA_SELF2_CD2		.SRES	2	;
_COP2_CPUA_SELF2_CD3		.SRES	2	;
_COP2_CPUA_SELF2_CD4		.SRES	2	;

_COP2_CPUB_SELF2_STR		.SRES	2	;
_COP2_CPUB_SELF2_END		.SRES	2	;
_COP2_CPUB_SELF2_CD1		.SRES	2	;
_COP2_CPUB_SELF2_CD2		.SRES	2	;
_COP2_CPUB_SELF2_CD3		.SRES	2	;
_COP2_CPUB_SELF2_CD4		.SRES	2	;



;	*******************************************
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_SEQ_DP_024		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_028		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_029		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_032		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_033		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_050		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_056		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_109		.SRES	2		;CMD(C/B)
_COP2_SEQ_DP_340		.SRES	30*2		;CMD(C/B)340~369　2007-04-05
_COP2_SEQ_DP_200		.SRES	70*2		;STS：204以外使用していない、通常はTﾘﾝｸ領域経由


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	***		COP2->SIT4		***
;	***		制御情報		***
;	***		RNA,PG,POS		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_CH1RNA_INDAT	.SRES	4			;生
_COP2_PG1_PLS		.SRES	4			;
_COP2_OUT1_PLS		.SRES	2			;払出パルス

	.ALIGN	4					;
_COP2_CH2RNA_INDAT	.SRES	4			;生
_COP2_PG2_PLS		.SRES	4			;PG
_COP2_OUT2_PLS		.SRES	2			;払出パルス


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		フィーダ		***
;	***		設定・実測		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
;	=== 2016-03-20 ﾚﾍﾞﾙﾌｨｰﾀﾞの意味で"LFEED"で統一する(上がALIGN 4だからOK)=====
_COP2_SVP_LFEED_LNG1		.SRES	4	;送り長さ　0.01mm
_COP2_SVP_LFEED_STRPOS	.SRES	4	;送り開始位置 0.001mm
_COP2_SVP_LFEED_STRDEG	.SRES	2	;送り開始角度 0.1度
_COP2_SVP_LFEED_STRNO	.SRES	2	;送り開始行程		
;	ALIGN4不要(位置,角度,行程の3点ｾｯﾄ)
_COP2_SVP_LFEED_ENDPOS	.SRES	4	;送り終了位置 0.001mm
_COP2_SVP_LFEED_ENDDEG	.SRES	2	;送り終了角度 0.1度
_COP2_SVP_LFEED_ENDNO	.SRES	2	;送り終了行程
;	ALIGN4不要(位置,角度,行程の3点ｾｯﾄ)
_COP2_SVP_LFEED_SPD1		.SRES	2	;通常の送り速度1%
_COP2_SVP_LFEED_SPD2		.SRES	2	;低速の送り速度1%
_COP2_SVP_LFEED_SELNO	.SRES	2	;型式の選択番号
_COP2_SVP_LFEED_HOSIN	.SRES	2	;矯正量(ｸﾘｱﾗﾝｽ) 入口
_COP2_SVP_LFEED_HOSOT	.SRES	2	;矯正量(ｸﾘｱﾗﾝｽ) 出口

_COP2_SVP_LFEED_GMNSQ1	.SRES	2	;ｼｰｹﾝｽ409
_COP2_SVP_LFEED_GMNSQ2	.SRES	2	;ｼｰｹﾝｽ410
_COP2_SVP_LFEED_GMNSQ3	.SRES	2	;ｼｰｹﾝｽ411
_COP2_SVP_LFEED_GMNSQ4	.SRES	2	;ｼｰｹﾝｽ412

	.ALIGN	4				;
_COP2_PVP_LFEED_POS	.SRES	4		;ﾌｨｰﾀﾞ現在位置表示


;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	***		SIT4->COP2		***
;	***		制御情報		***
;	***		DI,360ENC		***
;	***					***
;	***					***
;	***					***
;	*******************************************
	.ALIGN	4					;
_COP2_ENC360_INDT	.SRES	2			;WR/RD OK
_COP2_INT_SFY_INP_DAT	.SRES	2			;
_COP2_INT_STP_INP_DAT	.SRES	2			;
_COP2_PVX_SH4_SFTY_IN	.SRES	2			;
_COP2_di1_cb_ctl1	.SRES	2			;
_COP2_di2_cb_ctl2	.SRES	2			;
_COP2_di3_cb_inp1	.SRES	2			;
_COP2_di4_cb_inp2	.SRES	2			;
_COP2_REAL_INP1_DATA	.SRES	2			;
_COP2_FACT_IN_DATA	.SRES	2			;
_COP2_FDEV_IN_DATA	.SRES	2			;
_COP2_RACT_IN_DATA	.SRES	2			;
_COP2_RDEV_IN_DATA	.SRES	2			;





;	***************************************************
;	***						***
;	***						***
;	***						***
;	***************************************************
	.ALIGN	4					;
_COP2_PVP_LFD_PVABSPOS1		.SRES	4		;ﾌｨｰﾀﾞ現在位置1(ABS)
_COP2_PVP_LFD_PVABSPOS2		.SRES	4		;ﾌｨｰﾀﾞ現在位置2(ABS)
_COP2_PVP_LFD_PVABSPLS1		.SRES	4		;ﾌｨｰﾀﾞ現在位置PLS1(ABS)
_COP2_PVP_LFD_PVABSPLS2		.SRES	4		;ﾌｨｰﾀﾞ現在位置PLS2(ABS)

_COP2_PVP_LFD_PVINCPOS1		.SRES	4		;ﾌｨｰﾀﾞ現在位置1(INC)
_COP2_PVP_LFD_PVINCPOS2		.SRES	4		;ﾌｨｰﾀﾞ現在位置2(INC)
_COP2_PVP_LFD_PVINCPLS1		.SRES	4		;ﾌｨｰﾀﾞ現在位置PLS1(INC)
_COP2_PVP_LFD_PVINCPLS2		.SRES	4		;ﾌｨｰﾀﾞ現在位置PLS2(INC)

_COP2_PVP_LFD_OBJABSPLS		.SRES	4		;ﾌｨｰﾀﾞ現在位置1(ABS)
_COP2_PVP_LFD_OBJINCPLS		.SRES	4		;ﾌｨｰﾀﾞ現在位置PLS1(INC)

_COP2_PVP_LFD_OBJSPD		.SRES	2		;+/- PER
_COP2_PVP_LFD_ENCSPD		.SRES	2		;+/- PER

_COP2_LFD_SITMCN_SIG		.SRES	2		;470 ﾌｨｰﾀﾞ動作信号 BI0,BIT1,BIT2,BIT3


;	***************************************************
;	***												***
;	***			2017-06-29							***
;	***			COP3-CPUC展示会用					***
;	***			見える化表示機能					***
;	***			1msタイマ							***
;	***												***
;	***************************************************
_COP23_1MS_CNT				.SRES	2	;
_COP23_CTL_ENC360			.SRES	2	;
_COP23_INC_ENC360			.SRES	2	;

	.ALIGN	4							;
_COP23_RNA_ABS_POS			.SRES	4	;RNA_ABS_POS 4BYTE
_COP23_RNA_CTL_POS1			.SRES	4	;
_COP23_RNA_ABS_MAXPOS		.SRES	4	;
_COP23_RNA_ABS_MINPOS		.SRES	4	;
_COP23_SHOT_MOST_DOWN_POS	.SRES	4	;
_COP23_LINK_RL_OBJ_ABSPLS	.SRES	8	;
_COP23_LINK_PV_ABSPLS		.SRES	8	;


;	---------- ｻﾝﾌﾟﾘﾝｸﾞ専用----------------
_COP23_PV_OUT_SPD_PER		.SRES	2	;PV_OUT_SPD_PER 2BYTE 0.1
_COP23_PV_ENC_SPD_PER		.SRES	2	;PV_ENC_SPD_PER 2BYTE 0.1
_COP23_TRD_SMP_PV_SEQ		.SRES	2	;
_COP23_PVP_POWER_MONI		.SRES	2	;
_COP23_PV_IVW_DAT_DSP		.SRES	2	;[単位切り替え付き]
_COP23_MON_SV_IVW_USED		.SRES	2	;


_COP23_TRD_SEQMONI_01		.SRES	2*16	;ADR
_COP23_TRD_SMPTRG_CNT		.SRES	2		;

_COP2DPRAM_END:
;	------------07ffhしかないから注意-----------------

