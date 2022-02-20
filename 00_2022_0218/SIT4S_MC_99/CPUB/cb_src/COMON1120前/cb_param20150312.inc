;2014-08-05
;_PAR_DAIHAI_SEL	=1
;_PAR_ORGDRV_MD2	=1
;_PAR_ORGDRV_MOD	=0


;	***********************************
;	***				***
;	***	cbﾊﾟﾗﾒｰﾀ		***
;	***				***
;	***********************************
_CB_SYS_PARAM000:					;[H1F=昔][H2W=昔]_WR_CB_SYS_CHKCOD1
_CB_SYS_CHKCOD1		.DATA.W		H'1234		;ﾊﾟﾗﾒｰﾀWR開始

_CB_SYS_PARAM001:					;[H1F=昔][H2W=昔]_WR_CB_SYS_CHKCOD2
_CB_SYS_CHKCOD2		.DATA.W		H'4321		;ﾊﾟﾗﾒｰﾀWR開始

_CB_SYS_PARAM002:					;[H1F=昔][H2W=昔]
_PAR_SFTSWER_TM		.DATA.W		D'1000		;前安選択ＳＷ異常時間１秒

_CB_SYS_PARAM003:					;[H1F=昔][H2W=昔]
_PAR_BTNER_TM		.DATA.W		D'100		;運転ボタン異常時間１秒

_CB_SYS_PARAM004:					;[H1F=昔][H2W=昔]
_PAR_MODSER_TM1		.DATA.W		D'1000		;入力モード選択ＳＷ無し異常時間１秒

_CB_SYS_PARAM005:					;[H1F=昔][H2W=昔]
_PAR_MODSER_TM2		.DATA.W		D'100		;[入力モード2個以上選択異常時間0.1秒

_CB_SYS_PARAM006:					;[H1F=昔][H2W=昔]
_PAR_VLVER11_TM1	.DATA.W		D'200		;バルブ1異常1時間ON-OF;

_CB_SYS_PARAM007:					;[H1F=昔][H2W=昔]
_PAR_VLVER12_TM1	.DATA.W		D'200*3		;バルブ1異常2時間OF-ON;

_CB_SYS_PARAM008:					;[H1F=昔][H2W=昔]
_PAR_VLVER21_TM1	.DATA.W		D'200		;バルブ2異常1時間ON-OF;

_CB_SYS_PARAM009:					;[H1F=昔][H2W=昔]
_PAR_VLVER22_TM1	.DATA.W		D'200		;バルブ2異常2時間OF-ON;

_CB_SYS_PARAM010:					;[H1F=昔][H2W=昔]
_PAR_VLVER31_TM1	.DATA.W		D'200		;バルブ3異常1時間ON-OF;

_CB_SYS_PARAM011:					;[H1F=昔][H2W=昔]
_PAR_VLVER32_TM1	.DATA.W		D'200		;バルブ3異常2時間OF-ON;

_CB_SYS_PARAM012:					;[H1F=昔][H2W=昔]
_PAR_CMP_ERR_TIM1:					;
_PAR_CMPER2_TM:		.DATA.W		D'500		;二重回路2異常時間 500ms

_CB_SYS_PARAM013:					;[H1F=昔][H2W=昔]
_PAR_FSFTTRER_TM	.DATA.W		D'30		;前安全装置FCYCL用ﾄﾗﾝｼﾞｽﾀ異常時間

_CB_SYS_PARAM014:					;[H1F=昔][H2W=昔]
_PAR_RSFTTRER_TM	.DATA.W		D'30		;後安全装置RCYCL用ﾄﾗﾝｼﾞｽﾀ異常時間

;	====== 2002-12-22 (動作中・停止中)====
_CB_SYS_PARAM015:					;[H1F=2002-12-22][H2W=昔]
_PAR_STOP_SMPTIM	.DATA.W		25		;ﾘﾆｱｾﾝｻ/ｴﾝｺｰﾀﾞの停止判定用ｻﾝﾌﾟﾘﾝｸﾞ時間 25msec

_CB_SYS_PARAM016:					;[H1F=2002-12-22][H2W=昔]
_PAR_STOP_RNALNG	.DATA.W		20		;ﾘﾆｱｾﾝｻ停止判断用距離 0.020mm 0.001~32.767mm

_CB_SYS_PARAM017:					;[H1F=2002-12-22][H2W=昔]
_PAR_STOP_INCLNG	.DATA.W		50		;INCｴﾝｺｰﾀﾞ停止判断用ﾊﾟﾙｽ数 1pls~32767pls

_CB_SYS_PARAM018:					;[H1F=2002-12-22][H2W=昔]
_PAR_STOP_FILTER	.DATA.W		2/2		;ﾌｨﾙﾀ回数 2回の場合1と設定する

;	=====2003-01-27 ========================
_CB_SYS_PARAM019:					;[H1F=2003-01-27][H2W=昔]
_PAR_BIT_DATA_ER1	.DATA.W		3		;ﾋﾞｯﾄ飛/化け(=0ならやらない 旧ﾊﾟﾗﾒｰﾀでは0)

_CB_SYS_PARAM020:					;[H1F=2003-01-28][H2W=昔]
_PAR_CMP_ERR_TIM2	.DATA.W		2000		;工程二重回路

_CB_SYS_PARAM021:					;[H1F=昔][H2W=昔]
_PAR_SELF_MATH_SEL	.DATA.W		0		;セルフチェック選択 *0,*1,*2,*3, 0*,1*,2*,3* 
							;2:やらない
							;1:非常停止解除時 VS,遮光,ﾊﾟﾙｽﾃｽﾄ 1ｻｲｸﾙ終了時ﾊﾟﾙｽﾃｽﾄ
							;0:非常停止解除時 VS,遮光　　　　　1ｻｲｸﾙ終了時はない
							
_CB_SYS_PARAM022:					;[H1F=昔][H2W=昔]
_PAR_SELF_WAIT_TM	.DATA.W		200		;ｾﾙﾌﾁｪｯｸまたは位置決めからﾛｯｸ開始遅延時間(停止確認用)

;	===================================
;	===				===
;	===	2003-02-03 		===
;	===	運転中ﾀﾞｲﾊｲﾄ補正	===
;	===				===
;	===================================
_CB_SYS_PARAM023:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_SEL1	.DATA.W		2		;補正入／切での運転中のﾀﾞｲﾊｲﾄ補正

_CB_SYS_PARAM024:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_DIG1	.DATA.W		500		;DBG用360ｴﾝｺｰﾀﾞ角度上 170.0度(ｻﾝﾌﾟﾘﾝｸﾞ開始可能な角度) 170~359<ｻﾝﾌﾟﾘﾝｸﾞ可>

_CB_SYS_PARAM025:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_DIG2	.DATA.W		3400		;DBG用

_CB_SYS_PARAM026:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_WAITCNT	.DATA.W		0		;初回のｶｳﾝﾄ開始待ち回数 2->0

_CB_SYS_PARAM027:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_AVLCNT	.DATA.W		10		;移動平均の元データ回数

_CB_SYS_PARAM028:					;[H1F=2003-02-03][H2W=昔]
_PAR_DRVHOS_NO_USE	.DATA.W		0		;読み飛ばしデータ回数 上限側


_CB_SYS_PARAM029					;[H1F=2003-02-03][H2W=昔]
_PAR_START_WAIT_DND	.DATA.W		500		;段取時切替WAIT時間

;	<<< 2003-05-12 OVER-RUN,STOP,REV ERR  >>>
_CB_SYS_PARAM030:					;[H1F=2003-05-12][H2W=昔]
_PAR_INCSTP_EDYTM1	.DATA.W		1000		;停止の瞬間から停止異常を検知しない時間 1.000sec

_CB_SYS_PARAM031:					;[H1F=2003-05-12][H2W=昔]
_PAR_INCSTP_EDYTM2	.DATA.W		2000		;EMG停止の瞬間から停止異常を検知しない時間 1.000sec

_CB_SYS_PARAM032:					;[H1F=2003-05-12][H2W=昔]
_PAR_INC_ERRLNG1	.DATA.W		8000		;逆転異常量として使用

_CB_SYS_PARAM033:					;[H1F=2003-05-12][H2W=昔]
_PAR_RNA_SFTY_LNG1	.DATA.W		1000		;安全装置２ 1.000mm
;	>>> 2003-05-12 <<<

;	=== 2003-07-01 ==
_CB_SYS_PARAM034					;[H1F=2003-07-01][H2W=昔]
_PAR_ZERO_SPD		.DATA.W		10		;実速度算出用　周波数 1000=1KHZ

_CB_SYS_PARAM035					;[H1F=2003-07-01][H2W=昔]
_PAR_BRK_SEL_SPD	.DATA.W		500		;ﾌﾞﾚｰｷ異常見ない速度 5.00%

_CB_SYS_PARAM036					;[H1F=2003-07-01][H2W=昔]
_PAR_BRK1_DLYTM		.DATA.W		500		;msec(未使用　画面へ)

_CB_SYS_PARAM037					;[H1F=2003-07-01][H2W=昔]
_PAR_BRK1_ACCTM		.DATA.W		200		;msec(未使用　画面へ)

_CB_SYS_PARAM038					;[H1F=2003-07-01][H2W=昔]
_PAR_BRK2_ACCTM		.DATA.W		20		;msec　ﾌﾞﾚｰｷ2減速時間

_CB_SYS_PARAM039					;[H1F=2010-08-20][H2W=未作]********************
_PAR_STOPING_TIM	.DATA.W		50		;H1F:ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ,ﾌﾞﾚｰｷﾀｲﾏ用時間(2010-08-20以前は50ms固定)

_CB_SYS_PARAM040					;[H1F=2003-07-01][H2W=昔]
_PAR_ILNGERR_LNG	.DATA.W		2000		;移動量異常ｵｰﾊﾞ許容値plS

_CB_SYS_PARAM041					;[H1F=無し][H2W=無し]
_PAR_ILNGERR_DIG	.DATA.W		0		;

_CB_SYS_PARAM042					;[H1F=2003-07-09][H2W=昔]
_PAR_ORGDRV_MOD		.DATA.W		0		;原点復帰方法変更(0:ﾚﾍﾞﾙ/1:ｴｯｼﾞ)

_CB_SYS_PARAM043					;[H1F=2003-07-09][H2W=昔]
_PAR_ORGDRV_CNT		.DATA.W		0		;原点復帰回数0=1回 1=2回

;	========= 2004-05-24 ﾊﾟﾗﾒｰﾀ追加(中型対応)====
_CB_SYS_PARAM044					;[H1F=2004-05-24][H2W=昔]
_PAR_CLINK_LINK		.DATA.W		0		;中型対応 通常0:ｸﾗﾝｸ・ﾘﾝｸ変換する 1:しない

_CB_SYS_PARAM045					;[H1F=2004-05-24][H2W=昔]
_PAR_WTSEL_USE		.DATA.W		0		;通常0:型 1:待機点切替有(HMI)入力有効(C/B)/一部中型の認識
							;トヨタ仕様でも 1にすること
							;
_CB_SYS_PARAM046	.DATA.W		0		;[H1F=未作][H2W=未作]
							;連続時ﾛｯﾄｶｳﾝﾀｶｳﾝﾄ角度,連続以外は及び0設定だと下死点 
							;機能作成未　予約
;	======== 2006-ﾊﾟﾗﾒ-ﾀ===========
_CB_SYS_PARAM047					;[H1F=2006-**-**][H2W=昔]
_PAR_BRKLOCK_TIM	.DATA.W		1000		;2000;ﾌﾞﾚｰｷﾛｯｸ遅延時間100msec

_CB_SYS_PARAM048					;[H1F=2006-**-**][H2W=昔]
_PAR_BRKDISE_TIM	.DATA.W		50		;1000;ﾌﾞﾚｰｷ釈放遅延時間1000msec

_CB_SYS_PARAM049					;[H1F=2006-**-**][H2W=昔]
_PAR_SLFTRQ_UPP		.DATA.W		300		;ｾﾙﾌﾁｪｯｸ時の負荷率 30.0%


_CB_SYS_PARAM050					;[H1F=2006-**-**][H2W=昔]
_PAR_SFTY_BRKSEL	.DATA.W		1		;1:遮光時ﾌﾞﾚｰｷ選択

;	========2006-07-16=========
_CB_SYS_PARAM051					;[H1F=2006-07-16][H2W=昔]
_PAR_LSA_FILTIM		.DATA.W		0		;LSA1,2異常ﾌｨﾙﾀ時間 0:3msec 1:4msec設定+3msec

;	========2006-07-28=========
_CB_SYS_PARAM052					;[H1F=2006-07-28][H2W=昔]
_PAR_OVRLIDE_GMN	.DATA.W		1		;"1"画面ｵｰﾊﾞﾗｲﾄﾞ有効;→2007-01-23(不要ｼｰｹﾝｽへもっていくので未使用)
							;

;	========2006-07-28=========
_CB_SYS_PARAM053					;[H1F=2006-07-28][H2W=昔]
_PAR_ORG2CHK_TIM	.DATA.W		2000		;//2秒 起動時の動作

;	========2006-09-30(ﾓﾆﾀ入力切替)=========
_CB_SYS_PARAM054					;[H1F=2006-09-30][H2W=昔]
_PAR_ANAIN_SEL		.DATA.W		1		;[H1F=][H2W=]0:0~10V:X%(SIT3-TYPE) 1:-100%~(0)5~10V(100%):

;	========2006-09-30(ｵｰﾊﾞﾗｲﾄﾞ加減速時間)=========
_CB_SYS_PARAM055					;[H1F=2006-09-30][H2W=昔]
_PAR_ACCTYP_SEL		.DATA.W		1		;0:加速距離一定(SIT3ｴｸｾﾃﾞｨ) 1:加速時間一定 2:加速度一定(ELSE)
							;2007-01-23(不要ｼｰｹﾝｽへもっていくので未使用)

;	=======2006-11-21 安全装置へに論理選択==========
_CB_SYS_PARAM056					;[H1F=2006-11-21][H2W=昔]
_PAR_SFTY_LOGIC		.DATA.W		0		;0:ｾﾙﾌﾁｪｯｸ時1:L 1:ｾﾙﾌﾁｪｯｸ時1:H

;	======= 2007-01-16 安全一行程のみﾌﾞﾚｰｷ作動遅延==
_CB_SYS_PARAM057					;[H1F=2007-01-16][H2W=昔]
_PAR_SLOCK_DLY2		.DATA.W		1000		;

;	======= 2007-09-07 ｾﾙﾌﾁｪｯｸﾀｲﾐﾝｸﾞ元
_CB_SYS_PARAM058					;[H1F=2007-09-07][H2W=昔]
_PAR_SELFCHK_POWSEL	.DATA.W		0		;0:電源投入時のみPARAM21 1:PARAM21のﾀｲﾐﾝｸﾞ

;	========= 2008-04-01 ===========
_CB_SYS_PARAM059					;[H1F=無][H2W=2008-04-01]
_PAR_FUL_ENDSPD		.DATA.W		500		;COP2 フルクローズ終了軸あわせ速度 0.01%

_CB_SYS_PARAM060					;
_PAR_RNA_ALMSEL		.DATA.W		1		;[H1F=昔][H2W=2008-05-10,06-11]
							; 0:読取停止　 1:継続+ﾘｾｯﾄﾌﾘｰで可能 2008-05-10
							;10:読取停止　11:継続+ﾘｾｯﾄﾌﾘｰで可能(新ﾘﾆｱﾌﾟﾛﾄﾛﾙ)2008-06-11
							;20:X会社     21:X会社
_CB_SYS_PARAM061					;
_PAR_ORGIN_HAB1		.DATA.W		60		;[H1F=2008-07-29][H2W=YYY]
							;sit3の特殊で原点の振り角度で使用(2008-07-29)
							;40=-4度戻る
_CB_SYS_PARAM062					;
_PAR_ORGIN_HAB2		.DATA.W		70		;[H1F=2008-07-29][H2W=YYY]
							;sit3の特殊で原点の振り角度で使用(2008-07-29)
							;30=3度+(4度)進む
;	========= 2009-03-11(ﾄﾖﾀ仕様) ===========
_CB_SYS_PARAM063					;[H1F=2009-03-11][H2W=未作]
_PAR_MCNRNA_SEL		.DATA.W		0		;1:機械でﾘﾆｱｽｹｰﾙを使用しない構造･･原点復帰
							;ﾘﾆｱｽｹｰﾙの異常は

_CB_SYS_PARAM064					;[H1F=2009-03-11][H2W=未作]
_PAR_CUPCHK_SEL		.DATA.W		2		;1:SIT2用ｶｯﾌﾟﾘﾝｸﾞﾁｪｯｸ　2:ﾍﾞﾙﾄ+ｶｯﾌﾟﾘﾝｸﾞ

_CB_SYS_PARAM065					;停止中の360ｴﾝｺｰﾀﾞの動作許容量
_PAR_360STP_HAB		.DATA.W		20		;[H1F=2009-03-11][H2W=未作]0:未使用 2.0:停止中2度は許容する 358-359-0度-1-2

;	========= 2010-08-20[H1F2型　ﾏｲﾅ-ﾁｪﾝｼﾞ] ===
_CB_SYS_PARAM066					;[H1F=2010-08-20][H2W=未作]
_PAR_SFYOPT_USEL	.DATA.W		1		;0[現行の画面SWに従う]:1[上昇無効にしない]
							;関連PARAM066,279,332

_CB_SYS_PARAM067					;[H1F=2010-08-20][H2W=未作]
_PAR_BRKTCHK_SPD	.DATA.W		2500		;制動試験回転速度％ 98.00%

_CB_SYS_PARAM068					;[H1F=2010-08-20][H2W=無]
_PAR_BRKTOUT_SPD	.DATA.W		3000		;0:100.00% 1~100.00% 30.00%制動試験　出力速度


_CB_SYS_PARAM069					;[H1F=2011-03-22][H2W=無]
_PAR_ACC_MATHED		.DATA.W		1		;ふりこ加速方式 0:直線加速度　1:テーブルフリー加速


_CB_SYS_PARAM070					;[H1F=2011-03-22][H2W=無]
_PAR_DAIHAI_SEL		.DATA.W		1		;1:手動ﾀﾞｲﾊｲﾄの演算方法の変更1:2011-03-22ﾀｲﾌﾟﾟ[ｸﾗﾝｸ機構MC　H1F]
							;NO.23ﾀﾞｲﾊｲﾄ補正

_CB_SYS_PARAM071					;[H1F=2011-03-22][H2W=無]
_PAR_ORGDRV_MD2		.DATA.W		0		;1:原点復帰方法 1:ﾀｲﾌﾟ[ｸﾗﾝｸ機構MC　H1F]

_CB_SYS_PARAM072					;[H1F=2011-03-22][H2W=未作]
_PAR_SLDALM_LNG		.DATA.W		1000		;0:未検出 0.001~32.767mmｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動量 [ｸﾗﾝｸ機構MC　H1F]

_CB_SYS_PARAM073					;[H1F=2010-08-20][H2W=未作]1msec~32767msec
_PAR_SLDALM_TIM		.DATA.W		2000		;ｽﾗｲﾄﾞ移動異常検出用　ｽﾗｲﾄﾞ移動測定時間2011-03-22[ｸﾗﾝｸ機構MC　H1F]

_CB_SYS_PARAM074					;[H1F=2010-08-20][H2W=無]
_PAR_ORGPOS_LNG1	.DATA.W		1500		;原点関係比較距離

_CB_SYS_PARAM075					;[H1F=2011-05-11][H2W=未作]
_PAR_BRKTST_ORGDEG	.DATA.W		2700		;制動試験時の原点復帰完了角度 270.0度[画面表示上の角度]

_CB_SYS_PARAM076					;[H1F=2011-07-**][H2W=未作]
_PAR_ACC_ERR_FLT	.DATA.W		20		;上昇無効のための速度検出時間

_CB_SYS_PARAM077					;[H1F=2011-09-06][H2W=未作]
_PAR_UPCHK_SEL1		.DATA.W		1		;MC上昇無効のタイミング切替 1:NEW

_CB_SYS_PARAM078					;[H1F=2011-09-14][H2W=未作]
_PAR_FSWFUN_SEL		.DATA.W		1		;1以外:安全装置有効無効SW／1:制動試験モードSW

_CB_SYS_PARAM079					;[H1F=2011-09-14][H2W=未作]
_PAR_FSWSEL_MASK	.DATA.W		0		;1以外:安全装置有効固定/1:安全装置無効
;	===================================
;	===	2003-02-03		===
;	===	荷重計用	 	===
;	===     PARAM80~		===
;	===				===
;	===================================
_CB_SYS_PARAM080:					;[H1F=2003-02-03][H2W=昔]
_PAR_COP_CNTROT_ZDG1	.DATA.W		100		;回転 ｾﾞﾛ調開始角度=100(10.0度)+10.0度　待機点＋の意味だと思う

_CB_SYS_PARAM081					;[H1F=2003-02-03][H2W=昔]
_PAR_COP_CNTROT_ZDG2	.DATA.W		200		;回転 ｾﾞﾛ調終了    =荷重測定開始角度 +20.0度

_CB_SYS_PARAM082					;[H1F=2003-02-03][H2W=昔]
_PAR_COP_CNTROT_SDG1	.DATA.W		210		;回転 荷重測定開始角度 +21.0度

_CB_SYS_PARAM083					;[H1F=2003-02-03][H2W=昔]
_PAR_COP_CNTROT_SDG2	.DATA.W		2700		;回転 荷重測定開始終了270.0度

_CB_SYS_PARAM084:					;[H1F=2003-**-**][H2W=昔]
_PAR_COP_REVRSE_ZDG1	.DATA.W		50		;反転 ｾﾞﾛ調開始角度   +N 5.0度

_CB_SYS_PARAM085:					;[H1F=2003-**-**][H2W=昔]
_PAR_COP_REVRSE_ZDG2	.DATA.W		100		;反転 ｾﾞﾛ調開始終了   +M 10.0度

_CB_SYS_PARAM086:					;[H1F=2003-**-**][H2W=昔]
_PAR_COP_REVRSE_SDG1	.DATA.W		110		;反転 荷重測定開始角度+N  待機点+6.0度を横切った角度

_CB_SYS_PARAM087:					;[H1F=2003-**-**][H2W=昔]
_PAR_COP_REVRSE_SDG2	.DATA.W		30		;反転 荷重測定開始終了+M 待機点+4.0度を横切った角度:最終工程以降

_CB_SYS_PARAM088:					;[H1F=2010-12-27][H2W=未作]
_PAR_COP_DISP_SPM1	.DATA.W		0		;荷重切替サイクル速度比較1spm単位

_CB_SYS_PARAM089	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM090	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM091	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM092	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM093	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM094	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM095	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM096	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]
_CB_SYS_PARAM097	.DATA.W		0		;[H1F=未作or無][H2W=未作or無]

;	----------- 2007-08-21---------
_CB_SYS_PARAM098					;[H1F=無][H2W=2007-08-21]
_PAR_COP2_SYNC_COEF	.DATA.W		2000		;EMG/EXQ時の同期比率 1000=100%

_CB_SYS_PARAM099	.DATA.W		0		;[H1F=未作][H2W=未作]
;	===================================
;	===	2003-02-06		===
;	===	画面用		 	===
;	===     PARAM100~		===
;	===	PARAM101~		===
;	===================================
_CB_SYS_PARAM100				;[H1F=2003-02-06][H2W=昔]
_GMN_PAR000		.DATA.W		0	;PARAM100=1有効ﾊﾟﾗﾒｰﾀ

_CB_SYS_PARAM101				;[H1F=2003-02-06][H2W=昔]
_GMN_PAR001		.DATA.W		10	;10u ﾀﾞｲﾊｲﾄ補正下限ﾘﾐｯﾀ

_CB_SYS_PARAM102				;[H1F=2003-02-06][H2W=昔]
_GMN_PAR002		.DATA.W		9800	;98.00%  段取速度上限

_CB_SYS_PARAM103				;[H1F=2004-01-**][H2W=昔]
_GMN_PAR003		.DATA.W		1850	;185.0度  連寸一行程時の目標角度上限角度(2004-01-)

_CB_SYS_PARAM104				;[H1F=2004-05-24][H2W=昔]
_GMN_PAR004		.DATA.W		2700	;270.0度  待機点角度設定下限値(2004-05-24)

_CB_SYS_PARAM105				;[H1F=2004-05-24][H2W=昔]
_GMN_PAR005		.DATA.W		900	;90.0度  待機点角度設定上限値(2004-05-24)

_CB_SYS_PARAM106				;[H1F=2004-06-30][H2W=昔]
_GMN_PAR006		.DATA.W		600	;60.0度  ﾓｰｼｮﾝ角度設定下限値(2004-6-30)

_CB_SYS_PARAM107				;[H1F=2004-06-30][H2W=昔]
_GMN_PAR007		.DATA.W		2700	;270.0度 ﾓｰｼｮﾝ角度設定上限値(2004-6-30)

_CB_SYS_PARAM108				;[H1F=2004-06-30][H2W=昔]
_GMN_PAR008		.DATA.W		0	;ﾓｰｼｮﾝ角度大小比較有効／無効  1=有効  (2004-6-30)

_CB_SYS_PARAM109				;[H1F=2004-09-27][H2W=昔]
_GMN_PAR009		.DATA.W		3	;ﾎﾟｼﾞｼｮﾅ(ｵﾌﾟｼｮﾝ)ﾋﾞｯﾄ飛び回数	(2004-09-27)

_CB_SYS_PARAM110				;[H1F=2004-**-**][H2W=昔]
_GMN_PAR010		.DATA.W		5	;5u 荷重補正下限ﾘﾐｯﾀ

_CB_SYS_PARAM111				;[H1F=2004-**-**][H2W=昔]
_GMN_PAR011		.DATA.W		100	;100kN 荷重目標変更上下限値

_CB_SYS_PARAM112				;[H1F=2004-**-**][H2W=昔]
_GMN_PAR012		.DATA.W		100	;0.100mm 下限目標変更上下限値

_CB_SYS_PARAM113				;[H1F=2004-07-25][H2W=昔]
_GMN_PAR013		.DATA.W		0	;0kN(ton) ﾓｰｼｮﾝ目標荷重下限値 (2004/07/05)

_CB_SYS_PARAM114				;[H1F=200*-**-**][H2W=昔]
_GMN_PAR014		.DATA.W		1	;荷重転送切換  0：旧  1：新

_CB_SYS_PARAM115				;[H1F=2007-01-10][H2W=昔]
_GMN_PAR015		.DATA.W		1500	;150.0度  反転の上限角上限値(2007-01-10)

_CB_SYS_PARAM116				;[H1F=200*-**-**][H2W=*]
_GMN_PAR016		.DATA.W		3500	;160.0度　ふりこの上限角上限設定

_CB_SYS_PARAM117				;[H1F=200*-**-**][H2W=*]
_GMN_PAR017		.DATA.W		100	;ﾌﾞﾚｰｷ角度上限値（0～359度）

_CB_SYS_PARAM118				;[H1F=200*-**-**][H2W=*]
_GMN_PAR018		.DATA.W		300	;ﾌﾞﾚｰｷﾀｲﾑ上限値（0～999ms）

_CB_SYS_PARAM119				;[H1F=200*-**-**][H2W=*]
_GMN_PAR019		.DATA.W		0	;10.0度　ふりこの上限角下限リミット

_CB_SYS_PARAM120				;[H1F=2012-09-24][H2W=未作or無]
_GMN_PAR020		.DATA.W		50	;50mm  ダイハイトオフセット

_CB_SYS_PARAM121				;[H1F=2012-09-24][H2W=未作or無]
_GMN_PAR021		.DATA.W		0	;振子ﾓｰｼｮﾝ設定制限  0:制限無し  1:制限有り

_CB_SYS_PARAM122	
_GMN_PAR022		.DATA.W		0	;

_CB_SYS_PARAM123
_GMN_PAR023		.DATA.W		0	;

;	====	2003-02-03	=====
_CB_SYS_PARAM124:
_PAR_SYS_VERCHAR	.DATA.W		"B"	;

;	====	2003-01-27	=====
_CB_SYS_PARAM125:
_PAR_SYS_VERDSP		.DATA.W		D'12	;(ｼｽﾃﾑﾊﾟﾗﾒｰﾀのﾊﾞｰｼﾞｮﾝ表示追加 1~999まで)

_CB_SYS_PARAM126:				;_WR_CB_SYS_CHKCOD3
_CB_SYS_CHKCOD3		.DATA.W		H'5678	;ﾊﾟﾗﾒｰﾀWR-END

_CB_SYS_PARAM127:				;_WR_CB_SYS_CHKCOD4
_CB_SYS_CHKCOD4		.DATA.W		H'8765	;ﾊﾟﾗﾒｰﾀWR-END

;	====	2004-11-26[二重化非対象]	=====
_CB_SYS_PARAM128	
_GMN_PAR024		.DATA.W		0	;0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度0
_CB_SYS_PARAM129	
_GMN_PAR025		.DATA.W		100	;10.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度1
_CB_SYS_PARAM130	
_GMN_PAR026		.DATA.W		200	;20.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度2
_CB_SYS_PARAM131	
_GMN_PAR027		.DATA.W		300	;30.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度3
_CB_SYS_PARAM132	
_GMN_PAR028		.DATA.W		400	;40.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度4
_CB_SYS_PARAM133	
_GMN_PAR029		.DATA.W		500	;50.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度5
_CB_SYS_PARAM134	
_GMN_PAR030		.DATA.W		600	;60.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度6
_CB_SYS_PARAM135
_GMN_PAR031		.DATA.W		700	;70.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度7
_CB_SYS_PARAM136	
_GMN_PAR032		.DATA.W		800	;80.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度8
_CB_SYS_PARAM137
_GMN_PAR033		.DATA.W		900	;90.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度9
_CB_SYS_PARAM138
_GMN_PAR034		.DATA.W		1000	;100.0% ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ速度10
_CB_SYS_PARAM139	
_GMN_PAR035		.DATA.W		0	;0.00sec ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間0
_CB_SYS_PARAM140	
_GMN_PAR036		.DATA.W		10	;0.10sec ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間1
_CB_SYS_PARAM141	
_GMN_PAR037		.DATA.W		20	;0.20sec ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間2
_CB_SYS_PARAM142	
_GMN_PAR038		.DATA.W		30	;0.30sec ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ停止時間3

;	====	2010-08-12	=====
_CB_SYS_PARAM143				;[H1F=2010-08-12][H2W=未作]
_GMN_PAR039		.DATA.W		3	;24時間	制動性能試験ｲﾝﾀｰﾊﾞﾙﾀｲﾏ設定
_CB_SYS_PARAM144				;[H1F=2010-08-12][H2W=未作]
_GMN_PAR040		.DATA.W		2	;2時間	制動性能試験予告ﾀｲﾏ設定値
_CB_SYS_PARAM145				;[H1F=2010-08-12][H2W=未作]
_GMN_PAR041		.DATA.W		10000	;100.00sec	外部ﾀｲﾏ設定上限値


_CB_SYS_PARAM146				;[H1F=2012-10-16][H2W=未作or無]
_GMN_PAR042		.DATA.W		9	;反転Sの上限

_CB_SYS_PARAM147				;[H1F=2012-10-16][H2W=未作or無]
_GMN_PAR043		.DATA.W		9	;反転Pの上限

_CB_SYS_PARAM148				;[H1F=2013-02-04][H2W=未作or無]
_GMN_PAR044		.DATA.W		100	;1.00%	段取速度下限

_CB_SYS_PARAM149				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR045		.DATA.W		0	;H1F-MC2　2014-02-05　メッセージ色赤　異常メッセージ領域

_CB_SYS_PARAM150				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR046		.DATA.W		30000	;R01　荷重制御 荷重の上限 2014-03-11 30000KN

_CB_SYS_PARAM151				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR047		.DATA.W		10	;R01　荷重制御荷重の下限 2014-03-11 1KN[R01]

_CB_SYS_PARAM152				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR048		.DATA.W		1	;R01　荷重制御データ有効(HMI)2014-05-15[R01]

_CB_SYS_PARAM153				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR049		.DATA.W		3000	;ﾏｲﾅｽ最大(最小)左・右の荷重の上限設定

_CB_SYS_PARAM154				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR050		.DATA.W		2000	;ﾏｲﾅｽ最大(最小)合計の荷重の上限設定


_CB_SYS_PARAM155				;
_GMN_PAR051		.DATA.W		1000	;初期値:リリース高さ
_CB_SYS_PARAM156				;
_GMN_PAR052		.DATA.W		1	;初期値:リリースカムオン行程
_CB_SYS_PARAM157				;
_GMN_PAR053		.DATA.W		10	;初期値:リリースカムオン角度
_CB_SYS_PARAM158				;
_GMN_PAR054		.DATA.W		1	;初期値:リリースカムオフ行程
_CB_SYS_PARAM159				;
_GMN_PAR055		.DATA.W		20	;初期値:リリースカムオフ角度
_CB_SYS_PARAM160				;
_GMN_PAR056		.DATA.W		1	;初期値:リリースカム設定対象
_CB_SYS_PARAM161				;
_GMN_PAR057		.DATA.W		2000	;初期値:送り高さ
_CB_SYS_PARAM162				;
_GMN_PAR058		.DATA.W		2	;初期値:送りカムオン行程
_CB_SYS_PARAM163				;
_GMN_PAR059		.DATA.W		30	;初期値:送りカムオン角度
_CB_SYS_PARAM164				;
_GMN_PAR060		.DATA.W		2	;初期値:送りカムオフ行程
_CB_SYS_PARAM165				;
_GMN_PAR061		.DATA.W		40	;初期値:送りカムオフ角度
_CB_SYS_PARAM166				;
_GMN_PAR062		.DATA.W		2	;送りカム設定対象
_CB_SYS_PARAM167				;
_GMN_PAR063		.DATA.W		3	;初期値:タイミングカムオン行程
_CB_SYS_PARAM168				;
_GMN_PAR064		.DATA.W		50	;初期値:タイミングカムオン角度
_CB_SYS_PARAM169				;
_GMN_PAR065		.DATA.W		3	;初期値:タイミングカムオフ行程
_CB_SYS_PARAM170				;
_GMN_PAR066		.DATA.W		60	;初期値:タイミングカムオフ角度
_CB_SYS_PARAM171				;
_GMN_PAR067		.DATA.W		3	;タイミングカム設定対象
_CB_SYS_PARAM172				;
_GMN_PAR068		.DATA.W		1	;カム自動演算機能 有効／無効

_CB_SYS_PARAM173				;
_GMN_PAR069		.DATA.W		500	;スライド自動待機機能  待機時間上限設定の上限値

_CB_SYS_PARAM174				;
_GMN_PAR070		.DATA.W		150	;リリースカムオフ角度(回転,ふりこ)
_CB_SYS_PARAM175				;(0~359で指定)
_GMN_PAR071		.DATA.W		-20	;リリースカムオフ角度差分(反転) data+sysparam(+/-)
_CB_SYS_PARAM176				;(小さくするので　マイナスで指定すること)
_GMN_PAR072		.DATA.W		-50	;送りカムｏｎ差分data+sysparam(+/-)
_CB_SYS_PARAM177				;(小さくするので　マイナスで指定すること)
_GMN_PAR073		.DATA.W		60	;タイミングカムｏｎ差分 data+sysparam(+/-)
_CB_SYS_PARAM178				;
_GMN_PAR074		.DATA.W		70	;タイミングカムｏｆｆ差分data+sysparam(+/-)


_CB_SYS_PARAM179				;
_GMN_PAR075		.DATA.W		300	;進角  角度入力上限値(0～359°)
_CB_SYS_PARAM180				;
_GMN_PAR076		.DATA.W		500	;進角  時間入力上限値(0～999ms)

_CB_SYS_PARAM181				;
_GMN_PAR077
_PAR_REPCNT		.DATA.W		10	;繰り返し入力可能上限

_CB_SYS_PARAM182				;
_GMN_PAR078		.DATA.W		0	;カム出力自動演算画面のカム番号設定不可

_CB_SYS_PARAM183				;
_GMN_PAR079
_PAR_CONST_USE		.DATA.W		1	;一定領域設定（0：無効、1：有効）

_CB_SYS_PARAM184				;
_GMN_PAR080		.DATA.W		500	;500u ﾀﾞｲﾊｲﾄ補正上限ﾘﾐｯﾀ

_CB_SYS_PARAM185				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR081		.DATA.W		100	;100  荷重補正上限ﾘﾐｯﾀ



_CB_SYS_PARAM186				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR082		.DATA.W		0	;
_CB_SYS_PARAM187				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR083		.DATA.W		0	;
_CB_SYS_PARAM188				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR084		.DATA.W		0	;
_CB_SYS_PARAM189				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR085		.DATA.W		0	;
_CB_SYS_PARAM190				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR086		.DATA.W		0	;
_CB_SYS_PARAM191				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR087		.DATA.W		0	;
_CB_SYS_PARAM192				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR088		.DATA.W		0	;
_CB_SYS_PARAM193				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR089		.DATA.W		0	;
_CB_SYS_PARAM194				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR090		.DATA.W		0	;
_CB_SYS_PARAM195				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR091		.DATA.W		0	;
_CB_SYS_PARAM196				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR092		.DATA.W		0	;
_CB_SYS_PARAM197				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR093		.DATA.W		0	;
_CB_SYS_PARAM198				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR094		.DATA.W		0	;
_CB_SYS_PARAM199				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR095		.DATA.W		0	;
_CB_SYS_PARAM200				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR096		.DATA.W		0	;
_CB_SYS_PARAM201				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR097		.DATA.W		0	;
_CB_SYS_PARAM202				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR098		.DATA.W		0	;
_CB_SYS_PARAM203				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR099		.DATA.W		0	;
_CB_SYS_PARAM204				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR100		.DATA.W		0	;
_CB_SYS_PARAM205				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR101		.DATA.W		0	;
_CB_SYS_PARAM206				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR102		.DATA.W		0	;
_CB_SYS_PARAM207				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR103		.DATA.W		0	;
_CB_SYS_PARAM208				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR104		.DATA.W		0	;
_CB_SYS_PARAM209				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR105		.DATA.W		0	;
_CB_SYS_PARAM210				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR106		.DATA.W		0	;
_CB_SYS_PARAM211				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR107		.DATA.W		0	;
_CB_SYS_PARAM212				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR108		.DATA.W		0	;
_CB_SYS_PARAM213				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR109		.DATA.W		0	;
_CB_SYS_PARAM214				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR110		.DATA.W		0	;
_CB_SYS_PARAM215				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR111		.DATA.W		0	;
_CB_SYS_PARAM216				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR112		.DATA.W		0	;
_CB_SYS_PARAM217				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR113		.DATA.W		0	;
_CB_SYS_PARAM218				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR114		.DATA.W		0	;
_CB_SYS_PARAM219				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR115		.DATA.W		0	;
_CB_SYS_PARAM220				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR116		.DATA.W		0	;
_CB_SYS_PARAM221				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR117		.DATA.W		0	;
_CB_SYS_PARAM222				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR118		.DATA.W		0	;
_CB_SYS_PARAM223				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR119		.DATA.W		0	;
_CB_SYS_PARAM224				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR120		.DATA.W		0	;
_CB_SYS_PARAM225				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR121		.DATA.W		0	;
_CB_SYS_PARAM226				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR122		.DATA.W		0	;
_CB_SYS_PARAM227				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR123		.DATA.W		0	;
_CB_SYS_PARAM228				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR124		.DATA.W		0	;
_CB_SYS_PARAM229				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR125		.DATA.W		0	;
_CB_SYS_PARAM230				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR126		.DATA.W		0	;
_CB_SYS_PARAM231				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR127		.DATA.W		0	;
_CB_SYS_PARAM232				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR128		.DATA.W		0	;
_CB_SYS_PARAM233				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR129		.DATA.W		0	;
_CB_SYS_PARAM234				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR130		.DATA.W		0	;
_CB_SYS_PARAM235				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR131		.DATA.W		0	;
_CB_SYS_PARAM236				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR132		.DATA.W		0	;
_CB_SYS_PARAM237				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR133		.DATA.W		0	;
_CB_SYS_PARAM238				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR134		.DATA.W		0	;
_CB_SYS_PARAM239				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR135		.DATA.W		0	;
_CB_SYS_PARAM240				;[H1F=未作or無][H2W=未作or無]
_GMN_PAR136		.DATA.W		0	;

;	---------------- 2010-10-25------
_CB_SYS_PARAM241				;[H1F=2010-10-25][H2W=無]
_GMN_PAR137		.DATA.W		0	;電力表示時のデータ内容 0:1ｻｲｸﾙ平均電力[0.01kw] 1:電力量[0.01wh]
						;0は2010-10-7試作品と同様
						
_CB_SYS_PARAM242				;[H1F=2010-10-25][H2W=未作or無]
_GMN_PAR138		.DATA.W		1	;ｴｺﾒｰﾀ表示0:削減率 1:回生電力


;	-----------------2010-09-17-------------------------------------
_CB_SYS_PARAM243				;[H1F=2010-09-17][H2W=無]
_PAR_IVW_RANGE					;ｻﾝﾌﾟﾘﾝｸﾞ描画の瞬時電力 
_GMN_PAR139		.DATA.W		0	;0:小数点２桁 1:小数点１桁

;	------------------ 2010-08-23加振制御テーブル(C/B用) -----------------
_CB_SYS_PARAM244				;[H1F2010-08-23][H2W=無]
_PAR_KJYU_STOPTBL				;
_GMN_PAR140		.DATA.W		9500	;1:荷重0% 停止時間  0はこの区間では制御しない

_CB_SYS_PARAM245				;[H1F2010-08-23][H2W=無]
_GMN_PAR141		.DATA.W		0	;2:荷重1%~9 停止時間 6000:6秒後から加振制御する

_CB_SYS_PARAM246				;[H1F2010-08-23][H2W=無]
_GMN_PAR142		.DATA.W		9000	;3:荷重10%~19 停止時間 

_CB_SYS_PARAM247				;[H1F2010-08-23][H2W=無]
_GMN_PAR143		.DATA.W		8500	;4:荷重20%~29 停止時間 

_CB_SYS_PARAM248				;[H1F2010-08-23][H2W=無]
_GMN_PAR144		.DATA.W		8000	;5:荷重30%~39 停止時間 

_CB_SYS_PARAM249				;[H1F2010-08-23][H2W=無]
_GMN_PAR145		.DATA.W		7000	;6:荷重40%~49 停止時間 

_CB_SYS_PARAM250				;[H1F2010-08-23][H2W=無]
_GMN_PAR146		.DATA.W		6000	;7:荷重50%~59 停止時間 

_CB_SYS_PARAM251				;[H1F2010-08-23][H2W=無]
_GMN_PAR147		.DATA.W		5000	;8:荷重60%~69 停止時間 

_CB_SYS_PARAM252				;[H1F2010-08-23][H2W=無]
_GMN_PAR148		.DATA.W		4000	;9:荷重70%~79 停止時間 

_CB_SYS_PARAM253				;[H1F2010-08-23][H2W=無]
_GMN_PAR149		.DATA.W		3000	;10:荷重80%~89 停止時間 

_CB_SYS_PARAM254				;[H1F2010-08-23][H2W=無]
_GMN_PAR150		.DATA.W		2000	;11:荷重80%~99 停止時間 

_CB_SYS_PARAM255				;[H1F2010-08-23][H2W=無]
_GMN_PAR151		.DATA.W		1000	;12:荷重100 停止時間 


;	==================2011-09-12~[[[[[[[[旧バージョンは0,FFFFのどちらか]]]]]]]]]======================
;	MCの制動試験用に二重化対象AREAとして追加
;	256,257,510,511のｺｰﾄﾞが規定したものでなければ、この領域のパラメータは０として扱う
;	[コードが正しくなくてもパラメータ異常にはしない///旧バージョンに入れた場合の想定]
;	
_CB_SYS_PARAM256					;[H1F2011-09-12][H2W=未作]
_CB_SYS_CHKCOD1A	.DATA.W		H'1234		;新規ﾊﾟﾗﾒｰﾀ空間有効[2011-09-12]

_CB_SYS_PARAM257					;[H1F2011-09-12][H2W=未作]
_CB_SYS_CHKCOD2A	.DATA.W		H'4321		;

_CB_SYS_PARAM258					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_STPDEG	.DATA.W		600		;制動試験停止角度 60.0度[画面表示上の角度]

_CB_SYS_PARAM259					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_CMPTM1	.DATA.W		300		;制動試験警告時間140msec

_CB_SYS_PARAM260					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_CMPDG1	.DATA.W		120		;制動試験警告角度12.0度

_CB_SYS_PARAM261					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_CMPTM2	.DATA.W		300		;制動試験異常時間200msec

_CB_SYS_PARAM262					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_CMPDG2	.DATA.W		300		;制動試験異常角度30.0度

_CB_SYS_PARAM263					;[H1F2011-09-12][H2W=未作]
_PAR_BRKTST_DNDLMT	.DATA.W		2000		;制動試験前(349.6)段取速度の上限の制限20.00%



;---------------------2012-02-10 [H2Wで追加] 2012-03-06[H1Fに移植]
_CB_SYS_PARAM264					;[H1F=2012-03-06][H2W=逆転異常検知ﾏｽｸ時間]
_PAR_REVERR_MASKTM	.DATA.W		100		;4 100msec

_CB_SYS_PARAM265					;[H1F=未作or無][H2W=ｲﾝﾎﾟｼﾞｼｮﾝに入らない異常]
_PAR_INP_ERRTIM		.DATA.W		200		;5 200msec

_CB_SYS_PARAM266					;[H1F=未作or無][H2W=上昇無効速度0.01%]
_PAR_UPMASK_SPD		.DATA.W		300		;6 3.00%

;----------------------2012-03-06 [H1Fで追加]
_CB_SYS_PARAM267					;[H1F=1:空走時間選択][H2W=未作or無]
_PAR_BKTMCL_TMSEL	.DATA.W		0		;7 0:固定値　1:演算

_CB_SYS_PARAM268					;[H1F=空走時間][H2W=未作or無]
_PAR_BKTMCL_TMDEF	.DATA.W		1		;8 固定値のとき10msec

_CB_SYS_PARAM269					;[H1F=最小速度][H2W=未作or無]
_PAR_BKTMCL_SPMIN	.DATA.W		1000		;9 10.00%

_CB_SYS_PARAM270					;[H1F=加速度算出時間][H2W=未作or無]
_PAR_BKTMCL_ACCTM	.DATA.W		10		;7 10msec[MAX50]

_CB_SYS_PARAM271					;[H1F=加速度のしきいち][H2W=未作or無]
_PAR_BKTMCL_ACCCK	.DATA.W		2		;1 1234=1234000 p/s/s 15=15000p/s/s

_CB_SYS_PARAM272					;[H1F=加速度の継続時間][H2W=未作or無]
_PAR_BKTMCL_TIMCK	.DATA.W		20		;2 20msecX

_CB_SYS_PARAM273					;[H1F=演算の空走時間上限異常][H2W=未作or無]
_PAR_BKTMCL_TMDFCK	.DATA.W		50		;3 50msec

;----------------------- 2012-03-19[H1Fで追加]
_CB_SYS_PARAM274					;[H1F=検知速度][H2W=未作or無]
_PAR_BKTMCL_LSPD	.DATA.W		300		;4:3.00%


_CB_SYS_PARAM275					;[H1F=未作or無][H2W=未作or無]
_PAR_BKTMCL_CAL1	.DATA.W		0		;演算方式 0:VX 1:VS

_CB_SYS_PARAM276					;[H1F=未作or無][H2W=未作or無]
_PAR_BKTMCL_TMXCK	.DATA.W		1		;

;	-----------反転 TEST 2012-05-29[H1F]-----------
_CB_SYS_PARAM277					;[H1F=制御切替待時間][H2W=未作or無]
_PAR_NEGWAIT_TIM	.DATA.W		50		;7 1=1msec~100=100msce (0:50msec)

_CB_SYS_PARAM278					;[H1F=反転ｲﾝﾎﾟｼﾞ処理選択][H2W=未作or無]
_PAR_NEGERR_ENB		.DATA.W		1		;8 1:ｲﾝﾎﾟｼﾞに入らない場合EXIT有り[H1F]


;	----------- 2012-09-25--------
;	------ﾐｭｰﾃﾝｸﾞSW選択----
_CB_SYS_PARAM279					;[H1F=未作or無][H2W=未作or無]
_PAR_MYUTING_SEL	.DATA.W		1		;9 2012-09-20 0:今まで 0: / 1:待機点2SWを参照
							;関連PARAM066,279,332

;	------金型ﾀｯﾁ位置----
_CB_SYS_PARAM280	
_PAR_INSERT_SMPTM	.DATA.W		4		;80 4msec 金型ﾀｯﾁ位置算出用ﾌｨﾙﾀ時間

;	-------過負荷判定ﾄﾙｸ・電流変換係数
_CB_SYS_PARAM281
_PAR_IVW_KAMP		.DATA.W		2000		;1000/1000=1 100(0.1)~2000(2.0) 過負荷判定ﾄﾙｸ・電流変換係数

;	========== ｽﾄﾛｰｸ-電流ﾃｰﾌﾞﾙ回転--=====
_CB_SYS_PARAM282
_PAR_ROTITBL_Y0		.DATA.W		100		;2 回転 100A

;	========== ｽﾄﾛｰｸ-電流ﾃｰﾌﾞﾙ反転=====
_CB_SYS_PARAM283					;
_PAR_REVITBL_X0		.DATA.W		0		;3 反転ｽﾄﾛｰｸX0 0mm [0~32767mm]
_CB_SYS_PARAM284					;
_PAR_REVITBL_Y0		.DATA.W		100		;4 反転電流Y0 100A [0~32767A]
_CB_SYS_PARAM285	.DATA.W		15		;5  X1 15mm
_CB_SYS_PARAM286	.DATA.W		150		;6  Y1 120A
_CB_SYS_PARAM287	.DATA.W		20		;7  X2 20mm
_CB_SYS_PARAM288	.DATA.W		200		;8  Y2 140A
_CB_SYS_PARAM289	.DATA.W		22		;9  X3 22mm
_CB_SYS_PARAM290	.DATA.W		220		;90 Y3 200A
_CB_SYS_PARAM291	.DATA.W		24		;1  X4 24mm
_CB_SYS_PARAM292	.DATA.W		240		;2  Y4 80A
_CB_SYS_PARAM293	.DATA.W		25		;3  X5 25mm
_CB_SYS_PARAM294	.DATA.W		250		;4  Y5 50A
_CB_SYS_PARAM295	.DATA.W		30		;5  X6 30mm
_CB_SYS_PARAM296	.DATA.W		150		;6  Y6 10A

;	========== ｽﾄﾛｰｸ-電流ﾃｰﾌﾞﾙふりこ１=====
_CB_SYS_PARAM297
_PAR_DN1ITBL_X0		.DATA.W		0		;7 X0 0mm [0~32767mm]
_CB_SYS_PARAM298
_PAR_DN1ITBL_Y0		.DATA.W		200		;8 Y0 100A [0~32767A]
_CB_SYS_PARAM299	.DATA.W		15		;9    X1
_CB_SYS_PARAM300	.DATA.W		240		;300  Y1
_CB_SYS_PARAM301	.DATA.W		20		;1    X2
_CB_SYS_PARAM302	.DATA.W		280		;2    Y2
_CB_SYS_PARAM303	.DATA.W		22		;3    X3
_CB_SYS_PARAM304	.DATA.W		400		;4    Y3
_CB_SYS_PARAM305	.DATA.W		24		;5    X4
_CB_SYS_PARAM306	.DATA.W		160		;6    Y4
_CB_SYS_PARAM307	.DATA.W		26		;7    X5
_CB_SYS_PARAM308	.DATA.W		100		;8    Y5
_CB_SYS_PARAM309	.DATA.W		30		;9    X6
_CB_SYS_PARAM310	.DATA.W		20		;10   Y6


;	============　反転加減速時間 2012-09-25 ===============
_CB_SYS_PARAM311
_PAR_NEG_ACCLATE	.DATA.W		2000		;1 反転加減速時間比率 2000=200.0% 2012-09-25

_CB_SYS_PARAM312
_PAR_NEG_EXITTIM	.DATA.W		3000		;2 2012-10-5追い込み失敗の待ち時間

_CB_SYS_PARAM313
_PAR_OVHALM_WTCNT	.DATA.W		3		;3 2012-10-06 連続時異常を見ないサイクル

;	============　反転ﾃｰﾌﾞﾙ 2012-09-25(手前ﾊﾟﾙｽ) ===============
_CB_SYS_PARAM314
_PAR_BEFRE_PLSP1	.DATA.W		100		;4  P1
_CB_SYS_PARAM315	.DATA.W		200		;5  P2
_CB_SYS_PARAM316	.DATA.W		500		;6  P3
_CB_SYS_PARAM317	.DATA.W		1000		;7  P4
_CB_SYS_PARAM318	.DATA.W		2000		;8  P5
_CB_SYS_PARAM319	.DATA.W		4000		;9  P6
_CB_SYS_PARAM320	.DATA.W		5000		;20 P7
_CB_SYS_PARAM321	.DATA.W		10000		;1  P8
_CB_SYS_PARAM322	.DATA.W		20000		;2  P9

;	============　反転ﾃｰﾌﾞﾙ 2012-09-25(反転ｲﾝﾁﾝｸﾞ速度) ===============
_CB_SYS_PARAM323
_PAR_NEGCTL_SPDS1	.DATA.W		1000		;3  S1
_CB_SYS_PARAM324	.DATA.W		500		;4  S2
_CB_SYS_PARAM325	.DATA.W		400		;5  S3
_CB_SYS_PARAM326	.DATA.W		300		;6  S4 1.00
_CB_SYS_PARAM327	.DATA.W		200		;7  S5 0.50
_CB_SYS_PARAM328	.DATA.W		100		;8  S6 0.10%
_CB_SYS_PARAM329	.DATA.W		50		;9  S7 0.05%
_CB_SYS_PARAM330	.DATA.W		20		;30 S8 0.02%
_CB_SYS_PARAM331	.DATA.W		10		;1  S9


;	============ 2012-10-16 ========			
_CB_SYS_PARAM332					;関連PARAM066,279,332
_PAR_MYUTING_MATH	.DATA.W		2		;2  0:従来ｻｰﾎﾞﾛｯｸはとめない,一行程 1:2:ふりこ止めない

;	============ 2012-10-16 ========		
_CB_SYS_PARAM333	
_PAR_TECH2_KN1		.DATA.W		100		;3 0:演算は行わない +100knを超えた位置を記憶
_CB_SYS_PARAM334
_PAR_TECH2_KN2		.DATA.W		200		;4                  +200knを超えた位置を記憶
_CB_SYS_PARAM335
_PAR_TECH2_OFSPLS	.DATA.W		-10		;5 -10PLS 演算結果から10ﾊﾟﾙｽ引き算する

_CB_SYS_PARAM336
_PAR_OVRH_LATE2		.DATA.W		5000		;6 ｵｰﾊﾞﾋｰﾄ閾値倍率 

_CB_SYS_PARAM337					;2012-10-19
_PAR_ELSE_ORGDEG	.DATA.W		3500		;7 原点復帰角度２　349.5=1[ふりこ時０度に止めたい]


_CB_SYS_PARAM338					;2013-02-08
_PAR_DNMDEND_DLY	.DATA.W		8		;8 ふりこの終了を遅らせる:現状未使用


_CB_SYS_PARAM339					;2013-02-15
_PAR_INCSPD_UPLMT	.DATA.W		8000		;9 80.00% 0.01~100.00% [0設定は100%とする]

_CB_SYS_PARAM340
_PAR_TECH_GENPLS	.DATA.W		1000		;40 2013-02-23 金型ﾀｯﾁ減速位置ｽﾞﾗｽ
							;ﾘﾝｸ上のﾊﾟﾙｽ数 0~8192程度 2.4度

_CB_SYS_PARAM341
_PAR_CPUB_DN_HOVR	.DATA.W		60000		;41 2013-03-10 CPUBのふりこｵｰﾊﾞ 1~30000

_CB_SYS_PARAM342
_PAR_STOPTIM_MAX	.DATA.W		200		;2 2013-03-10 ｽﾄｯﾋﾟﾝｸﾞﾀｲﾏ　ｼｽﾃﾑ最大

;	-------- 2013-05-26 --------
_CB_SYS_PARAM343
_PAR_TEP_WATTIM		.DATA.W		50		;3 1~50msec

_CB_SYS_PARAM344
_PAR_TEP_BEFPLS		.DATA.W		10		;4 10pls

_CB_SYS_PARAM345					;手動ﾊﾟﾙｻ最小値　0:
_PAR_TEP_MINSPD		.DATA.W		20		;5  0.50%[注意 自起動*7PLS/Sとはﾚﾝｼﾞが異なる]


;	-------- 2013-09-30---------
_CB_SYS_PARAM346
_PAR_EPSENCR_TIM	.DATA.W		1000		;6 1000=10000msec[10msecﾀｲﾏ]　10秒


_CB_SYS_PARAM347
_PAR_BVLVCTL_SEL	.DATA.W		1		;7 1:停止ﾊﾞﾙﾌﾞ制御有り

_CB_SYS_PARAM348
_PAR_BVLV_DLYTM		.DATA.W		200		;8遅延 200msec

_CB_SYS_PARAM349
_PAR_BVLV_INCTM		.DATA.W		300		;9寸動 200msec

;	----------------2013-11-29[h2w]----------------
_CB_SYS_PARAM350
_PAR_SETUP_TIM		.DATA.W		5000	;50 H2W ｾｯﾄｱｯﾌﾟ時間DEF=2000
_CB_SYS_PARAM351
_PAR_SAME_BTNTIM	.DATA.W		2000	;1  H2W 運転釦同時時間=500
_CB_SYS_PARAM352
_PAR_SAME_TEPTIM	.DATA.W		500	;2  H2W 手動ﾊﾟﾙｻ時間=500≦運転同時時間


;	---------------- 2014-02-18[R02R03但し]
_CB_SYS_PARAM353
_PAR_MYUTERR_SEL	.DATA.W		1	;3 0: 1:異常 行程異常を監視する[R02R03　2014-02-18]


_CB_SYS_PARAM354
_PAR_KJYU_IDOSEL	.DATA.W		10	;4 荷重制御時の移動平均回数0,1は1回[R01 2014-03-14]

_CB_SYS_PARAM355
_PAR_COP1DT_SEL		.DATA.W		1	;5 0:ﾘｱﾙﾀｲﾑ荷重ﾃﾞｰﾀ=+のみ(E55)  1:ﾘｱﾙﾀｲﾑ荷重ﾃﾞｰﾀ+/-(E57)


;	--------------- 2014-04-24 R01前の構造規格で追加
_CB_SYS_PARAM356
_PAR_BRKT_CHGDGST	.DATA.W		100	;6　制動性能試験２使用　開始角度 10.0

_CB_SYS_PARAM357
_PAR_BRKT_CHGDGED	.DATA.W		900	;7　制動性能試験２使用　終了角度 90.0

_CB_SYS_PARAM358
_PAR_BRKTST_CMPTM1X	.DATA.W		300	;8　制動試験警告時間２

_CB_SYS_PARAM359
_PAR_BRKTST_CMPTM2X	.DATA.W		300	;9　制動試験異常時間２

;	--------------- 2014-05-15 R01(SIT4-CE2)で追加
_CB_SYS_PARAM360
_PAR_SFTY2_LNGTH	.DATA.W		200	;60　ｽﾗｲﾄﾞ下降中の遮光を見る区間 上死点~下方向20.0mmまで見る


;	--------------------------2014-07-14 荷重制御(R01)
_CB_SYS_PARAM361
_PAR_KAJYU_HLDSPD	.DATA.W		10	;1　一旦停止中の荷重制御速度
;	--------------------------2014-08-20 荷重制御(R01)----------------
_CB_SYS_PARAM362
_PAR_KAJYU_ARASPD	.DATA.W		50	;2[荷重制御]一旦停止中のromﾊﾟﾗ範囲外 荷重制御速度 pls7/s
_CB_SYS_PARAM363
_PAR_KAJYU_CHGARA	.DATA.W		20	;3[荷重制御] 20KNを設定の荷重完了範囲から引くARA->HLD


_CB_SYS_PARAM364	.DATA.W		0	;4
_CB_SYS_PARAM365	.DATA.W		0	;5
_CB_SYS_PARAM366	.DATA.W		0	;6
_CB_SYS_PARAM367	.DATA.W		0	;7
_CB_SYS_PARAM368	.DATA.W		0	;8
_CB_SYS_PARAM369	.DATA.W		0	;9

_CB_SYS_PARAM370	.DATA.W		0	;70
_CB_SYS_PARAM371	.DATA.W		0	;1
_CB_SYS_PARAM372	.DATA.W		0	;2
_CB_SYS_PARAM373	.DATA.W		0	;3
_CB_SYS_PARAM374	.DATA.W		0	;4
_CB_SYS_PARAM375	.DATA.W		0	;5
_CB_SYS_PARAM376	.DATA.W		0	;6
_CB_SYS_PARAM377	.DATA.W		0	;7
_CB_SYS_PARAM378	.DATA.W		0	;8
_CB_SYS_PARAM379	.DATA.W		0	;9

_CB_SYS_PARAM380	.DATA.W		0	;80
_CB_SYS_PARAM381	.DATA.W		0	;1
_CB_SYS_PARAM382	.DATA.W		0	;2
_CB_SYS_PARAM383	.DATA.W		0	;3
_CB_SYS_PARAM384	.DATA.W		0	;4
_CB_SYS_PARAM385	.DATA.W		0	;5
_CB_SYS_PARAM386	.DATA.W		0	;6
_CB_SYS_PARAM387	.DATA.W		0	;7
_CB_SYS_PARAM388	.DATA.W		0	;8
_CB_SYS_PARAM389	.DATA.W		0	;9

_CB_SYS_PARAM390	.DATA.W		0	;90
_CB_SYS_PARAM391	.DATA.W		0	;1
_CB_SYS_PARAM392	.DATA.W		0	;2
_CB_SYS_PARAM393	.DATA.W		0	;3
_CB_SYS_PARAM394	.DATA.W		0	;4
_CB_SYS_PARAM395	.DATA.W		0	;5
_CB_SYS_PARAM396	.DATA.W		0	;6
_CB_SYS_PARAM397	.DATA.W		0	;7
_CB_SYS_PARAM398	.DATA.W		0	;8

_CB_SYS_PARAM399	.DATA.W		0	;9


;	------------- "MC2 SIT4-CE3　R02,R03"　400から使用
_CB_SYS_PARAM400
_PAR_PNL_REMOTE		.DATA.W		1	;00 1:分離型ﾊﾟﾈﾙ

_CB_SYS_PARAM401
_PAR_PNL_BKLIGHT	.DATA.W		150	;1 "250*60%=150" "100%=250" 0:50%

_CB_SYS_PARAM402
_PAR_EXTDRV_SEL		.DATA.W		1	;2 外部起動機能有効 2014-02-18

_CB_SYS_PARAM403
_PAR_STOPTIM_SEL	.DATA.W		1	;3 2014-05-30 ﾀｲﾏの停止後の処理 0:初めから 1:継続 2:ﾀｲﾑｱｯﾌﾟから

_CB_SYS_PARAM404
_PAR_KJ_MINSHOS		.DATA.W		10000	;4　0,1~100.00%


;	-------------- EPｾﾝｻﾁｪｯｸ -------------
_CB_SYS_PARAM405
_PAR_EPCHK_SEL		.DATA.W		1	;5 0:EPｾﾝｻﾁｪｯｸしない 1:ﾁｪｯｸする

_CB_SYS_PARAM406
_PAR_EP1STR_DLYTM	.DATA.W		200	;6 開始遅延時間 ms

_CB_SYS_PARAM407
_PAR_EP2FVINOF_ERTM	.DATA.W		200	;7 片方ﾘﾚｰOF(0)確認時間兼ﾀｲﾑｱｳﾄ 3000,700

_CB_SYS_PARAM408
_PAR_EP3BRKON_DLYTM	.DATA.W		500	;8 ﾌﾞﾚｰｷON出力遅延

_CB_SYS_PARAM409
_PAR_EP4EPINOF_ERTM	.DATA.W		200	;9 EPｾﾝｻoff確認時間兼ﾀｲﾑｱｳﾄ 3500

_CB_SYS_PARAM410
_PAR_EP5RSTON_DLYTM	.DATA.W		200	;10 EPｾﾝｻﾘｾｯﾄON遅延時間

_CB_SYS_PARAM411
_PAR_EP6RSTON_JGTM	.DATA.W		200	;1 ﾘｾｯﾄON時間兼判定時間 4000

_CB_SYS_PARAM412
_PAR_EP6RSTOF_INTTM	.DATA.W		200	;2 OFFｲﾝﾀ-ﾊﾞﾙ時間       1000

_CB_SYS_PARAM413
_PAR_EP6RST_RETRY	.DATA.W		1	;3 ﾘｾｯﾄﾘﾄﾗｲ回数

_CB_SYS_PARAM414
_PAR_EP7AB_DLYTM	.DATA.W		200	;4 CPUA-->CPUBﾃｽﾄ遅延時間

_CB_SYS_PARAM415
_PAR_EP7END_DLYTM	.DATA.W		200	;5 CPUB-->終了遅延時間


_CB_SYS_PARAM416
_PAR_POSHLD1_BEFPLS	.DATA.W		-410	;6 自動待機時停止位置補正量 -1~-30000 410=1度

_CB_SYS_PARAM417				;2014-09-16
_PAR_POSHLD1_HENSAP	.DATA.W		1200	;7 自動待機時表示値補正[偏差分] 0~30000(内部でﾏｲﾅｽ)

_CB_SYS_PARAM418
_PAR_SPL_MONUSE		.DATA.W		0	;8 1:ｽﾌﾟｰﾙﾓﾆﾀ機能有効

_CB_SYS_PARAM419
_PAR_BRKON_SPLDLY	.DATA.W		3000	;9:ﾌﾞﾚｰｷON-ｽﾌﾟｰﾙOFFで正常:

_CB_SYS_PARAM420
_PAR_BRKOF_SPLDLY	.DATA.W		4000	;20ﾌﾞﾚｰｷOFF-ｽﾌﾟｰﾙONで正常:

;	---------------2014-09-25 寸動---------
_CB_SYS_PARAM421
_PAR_INCMODE_SEL	.DATA.W		1	;1　寸動のその場起動

_CB_SYS_PARAM422
_PAR_INCMODE_EPLS	.DATA.W		5	;2 終了とみなせるパルス

;	-------------- 2014-10-12 比較----------
_CB_SYS_PARAM423
_AD2_CMP1		.DATA.W		500	;3

_CB_SYS_PARAM424
_AD3_CMP1		.DATA.W		700	;4

_CB_SYS_PARAM425
_AD3_CMP2		.DATA.W		600	;5

_CB_SYS_PARAM426
_AD4_CMP1		.DATA.W		900	;6

_CB_SYS_PARAM427
_AD4_CMP2		.DATA.W		800	;7

_CB_SYS_PARAM428	.DATA.W		0	;8:予約SEQ 0or1234
_CB_SYS_PARAM429	.DATA.W		0	;9:予約SEQ 0or1


_CB_SYS_PARAM430	.DATA.W		0	;30
_CB_SYS_PARAM431	.DATA.W		0	;1
_CB_SYS_PARAM432	.DATA.W		0	;2
_CB_SYS_PARAM433	.DATA.W		0	;3
_CB_SYS_PARAM434	.DATA.W		0	;4
_CB_SYS_PARAM435	.DATA.W		0	;5
_CB_SYS_PARAM436	.DATA.W		0	;6
_CB_SYS_PARAM437	.DATA.W		0	;7
_CB_SYS_PARAM438	.DATA.W		0	;8
_CB_SYS_PARAM439	.DATA.W		0	;9

_CB_SYS_PARAM440	.DATA.W		0	;40
_CB_SYS_PARAM441	.DATA.W		0	;1
_CB_SYS_PARAM442	.DATA.W		0	;2
_CB_SYS_PARAM443	.DATA.W		0	;3
_CB_SYS_PARAM444	.DATA.W		0	;4
_CB_SYS_PARAM445	.DATA.W		0	;5
_CB_SYS_PARAM446	.DATA.W		0	;6
_CB_SYS_PARAM447	.DATA.W		0	;7
_CB_SYS_PARAM448	.DATA.W		0	;8
_CB_SYS_PARAM449	.DATA.W		0	;9

_CB_SYS_PARAM450	.DATA.W		0	;50
_CB_SYS_PARAM451	.DATA.W		0	;1
_CB_SYS_PARAM452	.DATA.W		0	;2
_CB_SYS_PARAM453	.DATA.W		0	;3
_CB_SYS_PARAM454	.DATA.W		0	;4
_CB_SYS_PARAM455	.DATA.W		0	;5
_CB_SYS_PARAM456	.DATA.W		0	;6
_CB_SYS_PARAM457	.DATA.W		0	;7
_CB_SYS_PARAM458	.DATA.W		0	;8
_CB_SYS_PARAM459	.DATA.W		0	;9

_CB_SYS_PARAM460	.DATA.W		0	;60
_CB_SYS_PARAM461	.DATA.W		0	;1
_CB_SYS_PARAM462	.DATA.W		0	;2
_CB_SYS_PARAM463	.DATA.W		0	;3
_CB_SYS_PARAM464	.DATA.W		0	;4
_CB_SYS_PARAM465	.DATA.W		0	;5
_CB_SYS_PARAM466	.DATA.W		0	;6
_CB_SYS_PARAM467	.DATA.W		0	;7
_CB_SYS_PARAM468	.DATA.W		0	;8
_CB_SYS_PARAM469	.DATA.W		0	;9

_CB_SYS_PARAM470	.DATA.W		0	;70
_CB_SYS_PARAM471	.DATA.W		0	;1
_CB_SYS_PARAM472	.DATA.W		0	;2
_CB_SYS_PARAM473	.DATA.W		0	;3
_CB_SYS_PARAM474	.DATA.W		0	;4
_CB_SYS_PARAM475	.DATA.W		0	;5
_CB_SYS_PARAM476	.DATA.W		0	;6
_CB_SYS_PARAM477	.DATA.W		0	;7
_CB_SYS_PARAM478	.DATA.W		0	;8
_CB_SYS_PARAM479	.DATA.W		0	;9

_CB_SYS_PARAM480	.DATA.W		0	;80
_CB_SYS_PARAM481	.DATA.W		0	;1
_CB_SYS_PARAM482	.DATA.W		0	;2
_CB_SYS_PARAM483	.DATA.W		0	;3
_CB_SYS_PARAM484	.DATA.W		0	;4
_CB_SYS_PARAM485	.DATA.W		0	;5
_CB_SYS_PARAM486	.DATA.W		0	;6
_CB_SYS_PARAM487	.DATA.W		0	;7
_CB_SYS_PARAM488	.DATA.W		0	;8
_CB_SYS_PARAM489	.DATA.W		0	;9

_CB_SYS_PARAM490	.DATA.W		0	;90
_CB_SYS_PARAM491	.DATA.W		0	;1
_CB_SYS_PARAM492	.DATA.W		0	;2
_CB_SYS_PARAM493	.DATA.W		0	;3
_CB_SYS_PARAM494	.DATA.W		0	;4
_CB_SYS_PARAM495	.DATA.W		0	;5
_CB_SYS_PARAM496	.DATA.W		0	;6
_CB_SYS_PARAM497	.DATA.W		0	;7
_CB_SYS_PARAM498	.DATA.W		0	;8
_CB_SYS_PARAM499	.DATA.W		0	;9


_CB_SYS_PARAM500	.DATA.W		0	;00
_CB_SYS_PARAM501	.DATA.W		0	;1
_CB_SYS_PARAM502	.DATA.W		0	;2
_CB_SYS_PARAM503	.DATA.W		0	;3
_CB_SYS_PARAM504	.DATA.W		0	;4
_CB_SYS_PARAM505	.DATA.W		0	;5
_CB_SYS_PARAM506	.DATA.W		0	;6
_CB_SYS_PARAM507	.DATA.W		0	;7
_CB_SYS_PARAM508	.DATA.W		0	;8
_CB_SYS_PARAM509	.DATA.W		0	;9

_CB_SYS_PARAM510
_CB_SYS_CHKCOD3A	.DATA.W		H'5678	;10

_CB_SYS_PARAM511
_CB_SYS_CHKCOD4A	.DATA.W		H'8765	;11

;	-------- [2011-09-14]まさかのために　512~2039以降も0にしておく---
	.DATA.W	0			;512
	.DATA.W	0			;513
	.DATA.W	0			;514
	.DATA.W	0			;515
	.DATA.W	0			;516
	.DATA.W	0			;517
	.DATA.W	0			;518
	.DATA.W	0			;519

	.DATA.W	0			;520
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;530
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;540
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;550
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;560
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;570
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;580
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;590
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;600
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;610
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;620
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;630
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;640
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;650
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;660
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;670
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;680
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;690
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;700
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;710
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;720
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;730
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;740
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;750
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;760
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;770
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;780
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;790
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;800
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9
	
	.DATA.W	0			;810
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;820
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;830
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;840
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;850
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;860
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;870
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;880
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0			;890
	.DATA.W	0			;1
	.DATA.W	0			;2
	.DATA.W	0			;3
	.DATA.W	0			;4
	.DATA.W	0			;5
	.DATA.W	0			;6
	.DATA.W	0			;7
	.DATA.W	0			;8
	.DATA.W	0			;9

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1000~1009
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1010~1019
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1020~1029
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1030~1039
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1040~1049
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1050~1059
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1060~1069
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1070~1079
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1080~1089
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1090~1099
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1100~1009
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1110~1119
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1120~1129
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1130~1139
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1140~1149
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1150~1159
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1160~1169
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1170~1179
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1180~1189
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1190~1199
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1200~1209
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1210~1219
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1220~1229
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1230~1239
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1240~1249
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1250~1259
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1260~1269
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1270~1279
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1280~1289
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1290~1299
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1300~1309
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1310~1319
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1320~1329
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1330~1339
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1340~1349
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1350~1359
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1360~1369
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1370~1379
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1380~1389
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1390~1399

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1400~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1410~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1420~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1430~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1440~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1450~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1460~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1470~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1480~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1490~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1500~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1510~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1520~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1530~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1540~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1550~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1560~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1570~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1580~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1590~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1600~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1610~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1620~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1630~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1640~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1650~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1660~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1670~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1680~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1690~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1700~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1710~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1720~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1730~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1740~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1750~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1760~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1770~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1780~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1790~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1800~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1810~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1820~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1830~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1840~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1850~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1860~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1870~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1880~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1890~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1900~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1910~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1920~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1930~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1940~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1950~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1960~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1970~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1980~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;1990~

	.DATA.W	0,0,0,0,0,0,0,0,0,0	;2000~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;2010~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;2020~
	.DATA.W	0,0,0,0,0,0,0,0,0,0	;2030~2039


;	------------------- 2010-10-20 ふりこ加速のﾃｰﾌﾞﾙ[ｺﾏﾂ殿作成]-----------------
	.INCLUDE	"cb_partbl.inc"	; //H'2000[8192byte 4096個]から


