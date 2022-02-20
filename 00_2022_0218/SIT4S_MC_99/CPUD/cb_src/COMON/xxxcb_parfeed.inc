;	*******************************************
;	***					***
;	***	フィーダに関わるパラメータ	***
;	***					***
;	*******************************************
;	ﾊﾟﾗﾒｰﾀ番号上は2000~4095まで使用可能
;	<ﾌｨｰﾀﾞ機能有りの判定は par0001=x1234 par0002=0x4321 par0005=1>
;	par0001=x1234 par0002=0x4321以外では「ﾊﾟﾗﾒｰﾀが古い」＝旧バージョンへの対応
;
;
__PAR_FED_ORG	.equ	2000*2
__PAR_FED_OFS	.equ	50*2
__PAR_FED_BLK	.equ	64

	.org	__PAR_FED_ORG
_CB_SYS_PARAM2000
_GMN_PAR1896

_SYS_FEED_PAR_TOP
_SYS_FEED_PAR0001	.DATA.W		H'1234		;ﾊﾟﾗﾒｰﾀWR開始
_SYS_FEED_PAR0002	.DATA.W		H'4321		;ﾊﾟﾗﾒｰﾀWR開始
_SYS_FEED_PAR0003	.DATA.W		__PAR_FED_OFS	;ﾃｰﾌﾞﾙのINFO:OFSET=100ﾊﾞｲﾄ
_SYS_FEED_PAR0004	.DATA.W		__PAR_FED_BLK	;ﾃｰﾌﾞﾙのINFO:1BLK=64ﾊﾞｲﾄ
_SYS_FEED_PAR0005	.DATA.W		1		;ﾌｨｰﾀﾞ機能有(1)／無(0)
_SYS_FEED_PAR0006	.DATA.W		0		;ﾌｨｰﾀﾞ通信方法選択(0)
_SYS_FEED_PAR0007	.DATA.W		0		;ﾌｨｰﾀﾞｽﾞﾚ用別置ｴﾝｺｰﾀﾞ極性(0/1)
_SYS_FEED_PAR0008	.DATA.W		2000		;ﾌｨｰﾀﾞｽﾞﾚ用別置ｴﾝｺｰﾀﾞ　位置換算ﾊﾟﾙｽN[PLS]   20000PLS
_SYS_FEED_PAR0009	.DATA.W		1000		;ﾌｨｰﾀﾞｽﾞﾚ用別置ｴﾝｺｰﾀﾞ　位置換算距離M[0.1mm]  10.00mm
_SYS_FEED_PAR0010	.DATA.W		20		;ﾌｨｰﾀﾞ型式番号上限1~20
_SYS_FEED_PAR0011	.DATA.W		50		;ﾌｨｰﾀﾞ低速時速度上限50%
_SYS_FEED_PAR0012	.DATA.W		0		;
_SYS_FEED_PAR0013	.DATA.W		0		;
_SYS_FEED_PAR0014	.DATA.W		0		;
_SYS_FEED_PAR0015	.DATA.W		0		;
_SYS_FEED_PAR0016	.DATA.W		0		;
_SYS_FEED_PAR0017	.DATA.W		0		;
_SYS_FEED_PAR0018	.DATA.W		0		;
_SYS_FEED_PAR0019	.DATA.W		0		;
_SYS_FEED_PAR0020	.DATA.W		0		;
_SYS_FEED_PAR0021	.DATA.W		0		;
_SYS_FEED_PAR0022	.DATA.W		0		;
_SYS_FEED_PAR0023	.DATA.W		0		;
_SYS_FEED_PAR0024	.DATA.W		0		;
_SYS_FEED_PAR0025	.DATA.W		0		;
_SYS_FEED_PAR0026	.DATA.W		0		;
_SYS_FEED_PAR0027	.DATA.W		0		;
_SYS_FEED_PAR0028	.DATA.W		0		;
_SYS_FEED_PAR0029	.DATA.W		0		;
_SYS_FEED_PAR0030	.DATA.W		0		;
_SYS_FEED_PAR0031	.DATA.W		0		;
_SYS_FEED_PAR0032	.DATA.W		0		;
_SYS_FEED_PAR0033	.DATA.W		0		;
_SYS_FEED_PAR0034	.DATA.W		0		;
_SYS_FEED_PAR0035	.DATA.W		0		;
_SYS_FEED_PAR0036	.DATA.W		0		;
_SYS_FEED_PAR0037	.DATA.W		0		;
_SYS_FEED_PAR0038	.DATA.W		0		;
_SYS_FEED_PAR0039	.DATA.W		0		;
_SYS_FEED_PAR0040	.DATA.W		0		;
_SYS_FEED_PAR0041	.DATA.W		0		;
_SYS_FEED_PAR0042	.DATA.W		0		;
_SYS_FEED_PAR0043	.DATA.W		0		;
_SYS_FEED_PAR0044	.DATA.W		0		;
_SYS_FEED_PAR0045	.DATA.W		0		;
_SYS_FEED_PAR0046	.DATA.W		0		;
_SYS_FEED_PAR0047	.DATA.W		0		;
_SYS_FEED_PAR0048	.DATA.W		0		;
_SYS_FEED_PAR0049	.DATA.W		0		;
_SYS_FEED_PAR0050	.DATA.W		0		;

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*0
_SYS_FEED_PAR_BLK01:
__FORM_FED_TOP
__FORM_FED_NAME		.DATA.B		"0","1"		;01型式名称01文字目,2文字
			.DATA.B		"2","3"		;02型式名称03
			.DATA.B		"4","5"		;03型式名称05
			.DATA.B		"6","7"		;04型式名称07
			.DATA.B		"8","9"		;05型式名称09
			.DATA.B		"A","B"		;06型式名称11
			.DATA.B		"C","D"		;07型式名称13
			.DATA.B		"E","F"		;08型式名称15文字目,16文字

__FORM_FED_SPDMX	.DATA.W		1000		;09 1000mm/sec 最高速度
__FORM_FED_ACCLT	.DATA.W		500		;10 500msec 加速時間
__FORM_FED_LDYTM	.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
__FORM_FED_HOSSL	.DATA.W		0		;12 矯正量自動調整有(1)無(0)
__FORM_FED_DIRCT	.DATA.W		0		;13 ﾓｰﾀ軸PG極性
__FORM_FED_PLS_N	.DATA.W		100		;14 換算比率 "N"100 PLS
__FORM_FED_LNG_M	.DATA.W		123		;15 換算比率 "M"12.3mm

__FORM_FED_INPPS	.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
__FORM_FED_SYLNG	.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

__FORM_FED_HSIUP	.DATA.W		999		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
__FORM_FED_HSIDN	.DATA.W		-999		;19 補正(HOS)入口(In)下限(DN)  -9.99
__FORM_FED_HSOUP	.DATA.W		789		;20 補正(HOS)出口(Out)上限(UP)  9.99
__FORM_FED_HSODN	.DATA.W		-987		;21 補正(HOS)出口(Out)下限(DN) -9.87
__FORM_FED_INPTM	.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
__FORM_FED_HENSA	.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
__FORM_FED_STPE1	.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
__FORM_FED_STPE2	.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
__FORM_FED_CMPE1	.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
__FORM_FED_CMPE2	.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
__FORM_FED_YB1		.DATA.W		0		;28
__FORM_FED_YB2		.DATA.W		0		;29
__FORM_FED_YB3		.DATA.W		0		;30
__FORM_FED_YB4		.DATA.W		0		;31
__FORM_FED_YB5		.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*1
_SYS_FEED_PAR_BLK02:
			.DATA.B		"F","0"		;01型式名称01文字目,2文字
			.DATA.B		"D","E"		;02型式名称03
			.DATA.B		"B","C"		;03型式名称05
			.DATA.B		"9","A"		;04型式名称07
			.DATA.B		"7","7"		;05型式名称09
			.DATA.B		"5","6"		;06型式名称11
			.DATA.B		"3","4"		;07型式名称13
			.DATA.B		"1","2"		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*2
_SYS_FEED_PAR_BLK03:
			.DATA.B		"3"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" ","a"		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*3
_SYS_FEED_PAR_BLK04:
			.DATA.B		"4"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" ","b"		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*4
_SYS_FEED_PAR_BLK05:
			.DATA.B		"5"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*5
_SYS_FEED_PAR_BLK06:
			.DATA.B		" "," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" ","6"		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*6
_SYS_FEED_PAR_BLK07:
			.DATA.B		"7"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*7
_SYS_FEED_PAR_BLK08:
			.DATA.B		"8"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*8
_SYS_FEED_PAR_BLK09:
			.DATA.B		"9"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*9
_SYS_FEED_PAR_BLK10:
			.DATA.B		"A"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*10
_SYS_FEED_PAR_BLK11:
			.DATA.B		"B"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*11
_SYS_FEED_PAR_BLK12:
			.DATA.B		"C"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*12
_SYS_FEED_PAR_BLK13:
			.DATA.B		"D"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*13
_SYS_FEED_PAR_BLK14:
			.DATA.B		"E"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*14
_SYS_FEED_PAR_BLK15:
			.DATA.B		"F"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*15
_SYS_FEED_PAR_BLK16:
			.DATA.B		"G"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*16
_SYS_FEED_PAR_BLK17:
			.DATA.B		"H"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*17
_SYS_FEED_PAR_BLK18:
			.DATA.B		"I"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*18
_SYS_FEED_PAR_BLK19:
			.DATA.B		"J"," "		;01型式名称01文字目,2文字
			.DATA.B		" "," "		;02型式名称03
			.DATA.B		" "," "		;03型式名称05
			.DATA.B		" "," "		;04型式名称07
			.DATA.B		" "," "		;05型式名称09
			.DATA.B		" "," "		;06型式名称11
			.DATA.B		" "," "		;07型式名称13
			.DATA.B		" "," "		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		200		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-300		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		400		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-500		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*19
_SYS_FEED_PAR_BLK20:
			.DATA.B		"Z","E"		;01型式名称01文字目,2文字
			.DATA.B		"N","D"		;02型式名称03
			.DATA.B		"1","2"		;03型式名称05
			.DATA.B		"3","4"		;04型式名称07
			.DATA.B		"5","6"		;05型式名称09
			.DATA.B		"7","8"		;06型式名称11
			.DATA.B		"9","a"		;07型式名称13
			.DATA.B		"b","c"		;08型式名称15文字目,16文字

			.DATA.W		1000		;09 1000mm/sec 最高速度
			.DATA.W		500		;10 500msec 加速時間
			.DATA.W		30		;11 30msec  リリース(L)反応遅延(DLY)
			.DATA.W		0		;12 矯正量自動調整有(1)無(0)
			.DATA.W		0		;13 ﾓｰﾀ軸PG極性
			.DATA.W		100		;14 換算比率 "N"100 PLS
			.DATA.W		123		;15 換算比率 "M"12.3mm

			.DATA.W		500		;16 ｲﾝﾎﾟｼﾞｼｮﾝ 500pls
			.DATA.W		102		;17 遮光時材料移動量 10.2mm [0.1mm]

			.DATA.W		100		;18 補正(HOS)入口(In)上限(UP)   9.99[0.01mm]
			.DATA.W		-110		;19 補正(HOS)入口(In)下限(DN)  -9.99
			.DATA.W		200		;20 補正(HOS)出口(Out)上限(UP)  9.99
			.DATA.W		-220		;21 補正(HOS)出口(Out)下限(DN) -9.87
			.DATA.W		100		;22 ﾌｨｰﾀﾞ余裕時間[1ms]
			.DATA.W		0		;23 出力パルス偏差異常 0,1~30000PLS[1PLS]
			.DATA.W		0		;24 停止時ﾓｰﾀ軸移動異常   0,1~300.00mm[0.01mm]
			.DATA.W		0		;25 停止時別置ENC移動異常 0,1~300.00mm[0.01mm]
			.DATA.W		0		;26 停止中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;27 動作中ﾓｰﾀ軸と別設置一致許容量0,1~300.00mm[0.01mm]
			.DATA.W		0		;28
			.DATA.W		0		;29
			.DATA.W		0		;30
			.DATA.W		0		;31
			.DATA.W		0		;32

;	----領域ramにcopy使用するためのラベル(feed領域の最後)--------
	.org	__PAR_FED_ORG+__PAR_FED_OFS+__PAR_FED_BLK*20
_SYS_FEED_PAR_END:


