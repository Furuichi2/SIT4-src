;	*******************************************
;	***					***
;	***					***
;	***					***
;	***		加速テーブル		***
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	ssa_acct.incにｲﾝｸﾙｰﾄﾞされる
;;;;	.global		_ACC_IN_TBL1

;	----------------SIN(**)---------
;;;;;_ACC_IN_TBL1
	.data.w		1	;1

	.data.w		1	;2　本当のﾃﾞｰﾀはここから
	.data.w		95 	;3
	.data.w		345 	;4
	.data.w		657 	;5
	.data.w		971 	;6
	.data.w		1285 	;7
	.data.w		1597 	;8
	.data.w		1909 	;9
	.data.w		2218 	;10
	.data.w		2526 	;11
	.data.w		2832 	;12
	.data.w		3135 	;13
	.data.w		3436 	;14
	.data.w		3733 	;15
	.data.w		4026 	;16
	.data.w		4316 	;17
	.data.w		4602 	;18
	.data.w		4883 	;19
	.data.w		5159 	;20
	.data.w		5430 	;21
	.data.w		5696 	;22
	.data.w		5956 	;23
	.data.w		6210 	;24
	.data.w		6458 	;25
	.data.w		6700 	;26
	.data.w		6934 	;27
	.data.w		7162 	;28
	.data.w		7382 	;29
	.data.w		7595 	;30
	.data.w		7800 	;31
	.data.w		7997 	;32
	.data.w		8186 	;33
	.data.w		8366 	;34
	.data.w		8538 	;35
	.data.w		8701 	;36
	.data.w		8855 	;37
	.data.w		9000 	;38
	.data.w		9136 	;39
	.data.w		9262 	;40
	.data.w		9378 	;41
	.data.w		9485 	;42
	.data.w		9582 	;43
	.data.w		9669 	;44
	.data.w		9747 	;45
	.data.w		9814 	;46
	.data.w		9870 	;47
	.data.w		9917 	;48
	.data.w		9953 	;49
	.data.w		9979 	;50
	.data.w		9995 	;51
	.data.w		10000	;52[ここまでが必要]
	.data.w		10000	;53 
	.data.w		10000	;54 
	.data.w		10000	;55 
	.data.w		10000	;56 


;	----------- 台形--------------------
;;;;_ACC_IN_TBL2
	.DATA.W		1 		;	0
	.DATA.W		1 		;	1
	.DATA.W		26 		;	2
	.DATA.W		103 		;	3
	.DATA.W		226 		;	4
	.DATA.W		391 		;	5
	.DATA.W		589 		;	6
	.DATA.W		810 		;	7
	.DATA.W		1045 		;	8
	.DATA.W		1282 		;	9
	.DATA.W		1519 		;	10
	.DATA.W		1756 		;	11
	.DATA.W		1994 		;	12
	.DATA.W		2231 		;	13
	.DATA.W		2468 		;	14
	.DATA.W		2705 		;	15
	.DATA.W		2942 		;	16
	.DATA.W		3180 		;	17
	.DATA.W		3417 		;	18
	.DATA.W		3654 		;	19
	.DATA.W		3891 		;	20
	.DATA.W		4128 		;	21
	.DATA.W		4366 		;	22
	.DATA.W		4603 		;	23
	.DATA.W		4840 		;	24
	.DATA.W		5077 		;	25
	.DATA.W		5314 		;	26
	.DATA.W		5552 		;	27
	.DATA.W		5789 		;	28
	.DATA.W		6026 		;	29
	.DATA.W		6263 		;	30
	.DATA.W		6500 		;	31
	.DATA.W		6738 		;	32
	.DATA.W		6975 		;	33
	.DATA.W		7212 		;	34
	.DATA.W		7449 		;	35
	.DATA.W		7686 		;	36
	.DATA.W		7924 		;	37
	.DATA.W		8160 		;	38
	.DATA.W		8392 		;	39
	.DATA.W		8618 		;	40
	.DATA.W		8835 		;	41
	.DATA.W		9040 		;	42
	.DATA.W		9231 		;	43
	.DATA.W		9405 		;	44
	.DATA.W		9560 		;	45
	.DATA.W		9695 		;	46
	.DATA.W		9808 		;	47
	.DATA.W		9897 		;	48
	.DATA.W		9961 		;	49
	.DATA.W		10000 		;	50
	.DATA.W		10000 		;	51
	.DATA.W		10000 		;	52
	.DATA.W		10000 		;	50

;	----------- 13次--------------------
;;;;;_ACC_IN_TBL3
	.DATA.W		1 		;	
	.DATA.W		1 		;	1
	.DATA.W		19 		;	2
	.DATA.W		86 		;	3
	.DATA.W		209 		;	4
	.DATA.W		391 		;	5
	.DATA.W		630 		;	6
	.DATA.W		920 		;	7
	.DATA.W		1256 		;	8
	.DATA.W		1629 		;	9
	.DATA.W		2033 		;	10
	.DATA.W		2459 		;	11
	.DATA.W		2901 		;	12
	.DATA.W		3351 		;	13
	.DATA.W		3804 		;	14
	.DATA.W		4255 		;	15
	.DATA.W		4698 		;	16
	.DATA.W		5132 		;	17
	.DATA.W		5551 		;	18
	.DATA.W		5955 		;	19
	.DATA.W		6341 		;	20
	.DATA.W		6707 		;	21
	.DATA.W		7054 		;	22
	.DATA.W		7379 		;	23
	.DATA.W		7682 		;	24
	.DATA.W		7965 		;	25
	.DATA.W		8225 		;	26
	.DATA.W		8464 		;	27
	.DATA.W		8682 		;	28
	.DATA.W		8880 		;	29
	.DATA.W		9057 		;	30
	.DATA.W		9216 		;	31
	.DATA.W		9356 		;	32
	.DATA.W		9478 		;	33
	.DATA.W		9584 		;	34
	.DATA.W		9675 		;	35
	.DATA.W		9751 		;	36
	.DATA.W		9814 		;	37
	.DATA.W		9865 		;	38
	.DATA.W		9906 		;	39
	.DATA.W		9938 		;	40
	.DATA.W		9961 		;	41
	.DATA.W		9978 		;	42
	.DATA.W		9989 		;	43
	.DATA.W		9995 		;	44
	.DATA.W		9999 		;	45
	.DATA.W		10000 		;	46
	.DATA.W		10000 		;	47
	.DATA.W		10000 		;	48
	.DATA.W		10000 		;	49
	.DATA.W		10000 		;	50
	.DATA.W		10000 		;	50
	.DATA.W		10000 		;	50
	.DATA.W		10000 		;	50
	.DATA.W		10000 		;	50

;-------255


	.DATA.W		0 	;	0
	.DATA.W		1 	;	1
	.DATA.W		1 	;	2
	.DATA.W		1 	;	3
	.DATA.W		2 	;	4
	.DATA.W		4 	;	5
	.DATA.W		6 	;	6
	.DATA.W		9 	;	7
	.DATA.W		13 	;	8
	.DATA.W		18 	;	9
	.DATA.W		24 	;	10
	.DATA.W		30 	;	11
	.DATA.W		37 	;	12
	.DATA.W		45 	;	13
	.DATA.W		54 	;	14
	.DATA.W		63 	;	15
	.DATA.W		73 	;	16
	.DATA.W		84 	;	17
	.DATA.W		96 	;	18
	.DATA.W		109 	;	19
	.DATA.W		122 	;	20
	.DATA.W		136 	;	21
	.DATA.W		151 	;	22
	.DATA.W		166 	;	23
	.DATA.W		183 	;	24
	.DATA.W		200 	;	25
	.DATA.W		218 	;	26
	.DATA.W		236 	;	27
	.DATA.W		256 	;	28
	.DATA.W		276 	;	29
	.DATA.W		296 	;	30
	.DATA.W		318 	;	31
	.DATA.W		340 	;	32
	.DATA.W		363 	;	33
	.DATA.W		387 	;	34
	.DATA.W		411 	;	35
	.DATA.W		437 	;	36
	.DATA.W		463 	;	37
	.DATA.W		489 	;	38
	.DATA.W		517 	;	39
	.DATA.W		545 	;	40
	.DATA.W		573 	;	41
	.DATA.W		603 	;	42
	.DATA.W		633 	;	43
	.DATA.W		664 	;	44
	.DATA.W		695 	;	45
	.DATA.W		728 	;	46
	.DATA.W		760 	;	47
	.DATA.W		794 	;	48
	.DATA.W		828 	;	49
	.DATA.W		863 	;	50
	.DATA.W		899 	;	51
	.DATA.W		935 	;	52
	.DATA.W		972 	;	53
	.DATA.W		1009 	;	54
	.DATA.W		1047 	;	55
	.DATA.W		1086 	;	56
	.DATA.W		1125 	;	57
	.DATA.W		1165 	;	58
	.DATA.W		1206 	;	59
	.DATA.W		1247 	;	60
	.DATA.W		1289 	;	61
	.DATA.W		1331 	;	62
	.DATA.W		1374 	;	63
	.DATA.W		1418 	;	64
	.DATA.W		1462 	;	65
	.DATA.W		1506 	;	66
	.DATA.W		1551 	;	67
	.DATA.W		1597 	;	68
	.DATA.W		1643 	;	69
	.DATA.W		1690 	;	70
	.DATA.W		1738 	;	71
	.DATA.W		1785 	;	72
	.DATA.W		1834 	;	73
	.DATA.W		1883 	;	74
	.DATA.W		1932 	;	75
	.DATA.W		1982 	;	76
	.DATA.W		2032 	;	77
	.DATA.W		2083 	;	78
	.DATA.W		2134 	;	79
	.DATA.W		2186 	;	80
	.DATA.W		2238 	;	81
	.DATA.W		2291 	;	82
	.DATA.W		2344 	;	83
	.DATA.W		2397 	;	84
	.DATA.W		2451 	;	85
	.DATA.W		2506 	;	86
	.DATA.W		2560 	;	87
	.DATA.W		2615 	;	88
	.DATA.W		2671 	;	89
	.DATA.W		2727 	;	90
	.DATA.W		2783 	;	91
	.DATA.W		2839 	;	92
	.DATA.W		2896 	;	93
	.DATA.W		2954 	;	94
	.DATA.W		3011 	;	95
	.DATA.W		3069 	;	96
	.DATA.W		3127 	;	97
	.DATA.W		3186 	;	98
	.DATA.W		3244 	;	99
	.DATA.W		3303 	;	100
	.DATA.W		3363 	;	101
	.DATA.W		3422 	;	102
	.DATA.W		3482 	;	103
	.DATA.W		3542 	;	104
	.DATA.W		3603 	;	105
	.DATA.W		3663 	;	106
	.DATA.W		3724 	;	107
	.DATA.W		3785 	;	108
	.DATA.W		3846 	;	109
	.DATA.W		3907 	;	110
	.DATA.W		3969 	;	111
	.DATA.W		4030 	;	112
	.DATA.W		4092 	;	113
	.DATA.W		4154 	;	114
	.DATA.W		4216 	;	115
	.DATA.W		4279 	;	116
	.DATA.W		4341 	;	117
	.DATA.W		4403 	;	118
	.DATA.W		4466 	;	119
	.DATA.W		4529 	;	120
	.DATA.W		4591 	;	121
	.DATA.W		4654 	;	122
	.DATA.W		4717 	;	123
	.DATA.W		4780 	;	124
	.DATA.W		4843 	;	125
	.DATA.W		4906 	;	126
	.DATA.W		4969 	;	127
	.DATA.W		5031 	;	128
	.DATA.W		5094 	;	129
	.DATA.W		5157 	;	130
	.DATA.W		5220 	;	131
	.DATA.W		5283 	;	132
	.DATA.W		5346 	;	133
	.DATA.W		5409 	;	134
	.DATA.W		5471 	;	135
	.DATA.W		5534 	;	136
	.DATA.W		5597 	;	137
	.DATA.W		5659 	;	138
	.DATA.W		5721 	;	139
	.DATA.W		5784 	;	140
	.DATA.W		5846 	;	141
	.DATA.W		5908 	;	142
	.DATA.W		5970 	;	143
	.DATA.W		6031 	;	144
	.DATA.W		6093 	;	145
	.DATA.W		6154 	;	146
	.DATA.W		6215 	;	147
	.DATA.W		6276 	;	148
	.DATA.W		6337 	;	149
	.DATA.W		6397 	;	150
	.DATA.W		6458 	;	151
	.DATA.W		6518 	;	152
	.DATA.W		6578 	;	153
	.DATA.W		6637 	;	154
	.DATA.W		6697 	;	155
	.DATA.W		6756 	;	156
	.DATA.W		6814 	;	157
	.DATA.W		6873 	;	158
	.DATA.W		6931 	;	159
	.DATA.W		6989 	;	160
	.DATA.W		7046 	;	161
	.DATA.W		7104 	;	162
	.DATA.W		7161 	;	163
	.DATA.W		7217 	;	164
	.DATA.W		7273 	;	165
	.DATA.W		7329 	;	166
	.DATA.W		7385 	;	167
	.DATA.W		7440 	;	168
	.DATA.W		7494 	;	169
	.DATA.W		7549 	;	170
	.DATA.W		7603 	;	171
	.DATA.W		7656 	;	172
	.DATA.W		7709 	;	173
	.DATA.W		7762 	;	174
	.DATA.W		7814 	;	175
	.DATA.W		7866 	;	176
	.DATA.W		7917 	;	177
	.DATA.W		7968 	;	178
	.DATA.W		8018 	;	179
	.DATA.W		8068 	;	180
	.DATA.W		8117 	;	181
	.DATA.W		8166 	;	182
	.DATA.W		8215 	;	183
	.DATA.W		8262 	;	184
	.DATA.W		8310 	;	185
	.DATA.W		8357 	;	186
	.DATA.W		8403 	;	187
	.DATA.W		8449 	;	188
	.DATA.W		8494 	;	189
	.DATA.W		8538 	;	190
	.DATA.W		8582 	;	191
	.DATA.W		8626 	;	192
	.DATA.W		8669 	;	193
	.DATA.W		8711 	;	194
	.DATA.W		8753 	;	195
	.DATA.W		8794 	;	196
	.DATA.W		8835 	;	197
	.DATA.W		8875 	;	198
	.DATA.W		8914 	;	199
	.DATA.W		8953 	;	200
	.DATA.W		8991 	;	201
	.DATA.W		9028 	;	202
	.DATA.W		9065 	;	203
	.DATA.W		9101 	;	204
	.DATA.W		9137 	;	205
	.DATA.W		9172 	;	206
	.DATA.W		9206 	;	207
	.DATA.W		9240 	;	208
	.DATA.W		9272 	;	209
	.DATA.W		9305 	;	210
	.DATA.W		9336 	;	211
	.DATA.W		9367 	;	212
	.DATA.W		9397 	;	213
	.DATA.W		9427 	;	214
	.DATA.W		9455 	;	215
	.DATA.W		9483 	;	216
	.DATA.W		9511 	;	217
	.DATA.W		9537 	;	218
	.DATA.W		9563 	;	219
	.DATA.W		9589 	;	220
	.DATA.W		9613 	;	221
	.DATA.W		9637 	;	222
	.DATA.W		9660 	;	223
	.DATA.W		9682 	;	224
	.DATA.W		9704 	;	225
	.DATA.W		9724 	;	226
	.DATA.W		9744 	;	227
	.DATA.W		9764 	;	228
	.DATA.W		9782 	;	229
	.DATA.W		9800 	;	230
	.DATA.W		9817 	;	231
	.DATA.W		9834 	;	232
	.DATA.W		9849 	;	233
	.DATA.W		9864 	;	234
	.DATA.W		9878 	;	235
	.DATA.W		9891 	;	236
	.DATA.W		9904 	;	237
	.DATA.W		9916 	;	238
	.DATA.W		9927 	;	239
	.DATA.W		9937 	;	240
	.DATA.W		9946 	;	241
	.DATA.W		9955 	;	242
	.DATA.W		9963 	;	243
	.DATA.W		9970 	;	244
	.DATA.W		9976 	;	245
	.DATA.W		9982 	;	246
	.DATA.W		9987 	;	247
	.DATA.W		9991 	;	248
	.DATA.W		9994 	;	249
	.DATA.W		9996 	;	250
	.DATA.W		9998 	;	251
	.DATA.W		9999 	;	252
	.DATA.W		10000 	;	253
	.DATA.W		10000 	;	254
	.DATA.W		10000 	;	255

	.DATA.W		0 	;	256(参照されない)
	.DATA.W		0 	;	257(参照されない)



