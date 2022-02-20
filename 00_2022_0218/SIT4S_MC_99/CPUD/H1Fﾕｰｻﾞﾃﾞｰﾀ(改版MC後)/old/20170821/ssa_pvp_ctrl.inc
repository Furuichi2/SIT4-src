
;/*     実測値制御情報テーブル      */

;PV0001
    .data.w 0, 0
    .data.l _DEBUG_CNT
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0002
    .data.w 0, 0
    .data.l _PV_TOTLC1_B3
    .data.w 7, 0, h'0084, 4, 0, 0, 0, 0;
;PV0003
    .data.w 0, 0
    .data.l _PV_LOTCT1_B1
    .data.w 7, 50, h'0084, 4, 0, 0, 0, 0;
;PV0004
    .data.w 0, 0
    .data.l _PV_LOTCT2_B1
    .data.w 7, 51, h'0084, 4, 0, 0, 0, 0;
;PV0005
    .data.w 0, 0
    .data.l _PV0_KAGEN_POSITIONER
    .data.w 7, 52, h'0004, 4, 2, 0, 0, 0;
;PV0006
    .data.w 0, 0
    .data.l _PV_KAJYU1_A24
    .data.w 4, 53, h'0004, 2, 0, 0, 0, 0;
;PV0007
    .data.w 0, 0
    .data.l _PV_KAJYU2_A24
    .data.w 4, 53, h'0004, 2, 0, 0, 0, 0;
;PV0008
    .data.w 0, 0
    .data.l _PV_KAJYU3_A24
    .data.w 4, 53, h'0004, 2, 0, 0, 0, 0;
;PV0009
    .data.w 0, 0
    .data.l _PVP_CYCLE_SPM1
    .data.w 13, 0, h'0084, 2, 0, 0, 0, 0;
;PV0010
    .data.w 0, 0
    .data.l _PV0_NOWPOSI_SLIDE
    .data.w 14, 19, h'0084, 4, 2, 0, 0, 0;
;PV0011
    .data.w 0, 0
    .data.l _PVP_STOP_TIM
    .data.w 0, 68, 0, 2, 0, 0, 0, 0;
;PV0012
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0013
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0014
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0015
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0016
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0017
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0018
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0019
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0020
    .data.w 0, 0
    .data.l _PVP_NOW_ANGLE_RNA
    .data.w 0, 0, h'0100, 2, 0, 0, 0, 0;
;PV0021
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, h'0200, 4, 2, 0, 0, 0;
;PV0022
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0023
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0024
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 1;
;PV0025
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 1;
;PV0026
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 1;
;PV0027
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 1;
;PV0028
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 1;
;PV0029
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0030
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0031
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0032
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0033
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0034
    .data.w 0, 0
    .data.l _PVP_NOW_ANGLE_RNA
    .data.w 0, 0, h'0100, 2, 0, 0, 0, 0;
;PV0035
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, h'0200, 4, 2, 0, 0, 0;
;PV0036
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0037
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0038
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0039
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0040
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0041
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0042
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0043
    .data.w 0, 0
    .data.l _PVP_NOW_ANGLE_RNA
    .data.w 0, 0, h'0100, 2, 0, 0, 0, 0;
;PV0044
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, h'0200, 4, 2, 0, 0, 0;
;PV0045
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0046
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0047
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 0;
;PV0048
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 0;
;PV0049
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 0;
;PV0050
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 0;
;PV0051
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 0;
;PV0052
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0053
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0054
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, 4, 2, 0, 0, 0, 0;
;PV0055
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0056
    .data.w 0, 0
    .data.l _PV_MLDNO3_F1
    .data.w 6, 69, 0, 14, 0, 0, 0, 0;
;PV0057
    .data.w 0, 0
    .data.l _PVP_CYCLE_SPM1
    .data.w 13, 0, h'0084, 2, 0, 0, 0, 0;
;PV0058
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, h'0284, 4, 2, 0, 0, 0;
;PV0059
    .data.w 0, 0
    .data.l _PVP_STOP_TIM
    .data.w 0, 68, 0, 2, 0, 0, 0, 0;
;PV0060
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0061
    .data.w 0, 0
    .data.l _PV0_DYHITO_POS
    .data.w 7, 52, h'0204, 4, 2, 0, 0, 0;
;PV0062
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0063
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, 4, 2, 0, 0, 0, 0;
;PV0064
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0065
    .data.w 0, 0
    .data.l _PV_MLDNO3_F1
    .data.w 6, 69, 0, 14, 0, 0, 0, 0;
;PV0066
    .data.w 0, 0
    .data.l _PVP_CYCLE_SPM1
    .data.w 13, 0, h'0084, 2, 0, 0, 0, 0;
;PV0067
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, h'0284, 4, 2, 0, 0, 0;
;PV0068
    .data.w 0, 0
    .data.l _PVP_STOP_TIM
    .data.w 0, 68, 0, 2, 0, 0, 0, 0;
;PV0069
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0070
    .data.w 0, 0
    .data.l _PV_TOTLC1_B3
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0071
    .data.w 0, 0
    .data.l _PV_LOTCT1_B1
    .data.w 0, 50, 0, 4, 0, 0, 0, 0;
;PV0072
    .data.w 0, 0
    .data.l _PV_LOTCT2_B1
    .data.w 0, 51, 0, 4, 0, 0, 0, 0;
;PV0073
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0074
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0075
    .data.w 0, 0
    .data.l _PV_LIFE_COUNT
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0076
    .data.w 0, 0
    .data.l _MCN_MENT_TIM1
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0077
    .data.w 0, 0
    .data.l _MCN_MENT_CNT1
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0078
    .data.w 0, 0
    .data.l _MCN_MENT_CNT2
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0079
    .data.w 0, 0
    .data.l _MCN_MENT_CNT3
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0080
    .data.w 0, 0
    .data.l _MCN_MENT_CNT4
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0081
    .data.w 0, 0
    .data.l _MCN_MENT_CNT5
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0082
    .data.w 0, 0
    .data.l _MCN_MENT_TIM2
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0083
    .data.w 0, 0
    .data.l _MCN_MENT_TIM3
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0084
    .data.w 0, 0
    .data.l _MCN_MENT_CNT6
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0085
    .data.w 0, 0
    .data.l _MCN_MENT_CNT7
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0086
    .data.w 0, 0
    .data.l _MCN_MENT_CNT8
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0087
    .data.w 0, 0
    .data.l _PVP_BREAK_DIG
    .data.w 0, 0, 0, 2, 1, 0, 0, 0;
;PV0088
    .data.w 0, 0
    .data.l _PVP_BREAK_TIM1
    .data.w 0, 68, 0, 2, 0, 0, 0, 0;
;PV0089
    .data.w 0, 0
    .data.l _PV_MLNO01_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0090
    .data.w 0, 0
    .data.l _PV_MLNO02_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0091
    .data.w 0, 0
    .data.l _PV_MLNO03_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0092
    .data.w 0, 0
    .data.l _PV_MLNO04_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0093
    .data.w 0, 0
    .data.l _PV_MLNO05_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0094
    .data.w 0, 0
    .data.l _PV_MLNO06_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0095
    .data.w 0, 0
    .data.l _PV_MLNO07_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0096
    .data.w 0, 0
    .data.l _PV_MLNO08_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0097
    .data.w 0, 0
    .data.l _PV_MLNO09_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0098
    .data.w 0, 0
    .data.l _PV_MLNO10_C15
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0099
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 0, 0, 2, 0, 0, 0, 0;
;PV0100
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 0, 0, 14, 0, 0, 0, 0;
;PV0101
    .data.w 0, 0
    .data.l _PV_MLDNO1_F0
    .data.w 9, 0, h'0004, 2, 0, 0, 0, 0;
;PV0102
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0103
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0104
    .data.w 0, 0
    .data.l _PV_TOTLC1_B3
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0105
    .data.w 0, 0
    .data.l _PV_LOTCT1_B1
    .data.w 0, 50, 0, 4, 0, 0, 0, 0;
;PV0106
    .data.w 0, 0
    .data.l _PV_LOTCT2_B1
    .data.w 0, 51, 0, 4, 0, 0, 0, 0;
;PV0107
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0108
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0109
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0110
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0111
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0112
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0113
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, 4, 2, 0, 0, 0, 0;
;PV0114
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0115
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0116
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0117
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0118
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0119
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0120
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0121
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0122
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0123
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0124
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0125
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0126
    .data.w 0, 0
    .data.l _PV_MLDNO1_F0
    .data.w 9, 0, h'0004, 2, 0, 0, 0, 0;
;PV0127
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0128
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0129
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0130
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0131
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0132
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 1;
;PV0133
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 1;
;PV0134
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 1;
;PV0135
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 1;
;PV0136
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 1;
;PV0137
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 143, 0, 4, 0, 0, 0, 0;
;PV0138
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0139
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0140
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0141
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0142
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0143
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0144
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0145
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0146
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0044, 2, 0, 0, 0, 0;
;PV0147
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0148
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0149
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0150
    .data.w 0, 0
    .data.l _CAR_LNG_KAJ_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0151
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 0;
;PV0152
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 0;
;PV0153
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 0;
;PV0154
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 0;
;PV0155
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 0;
;PV0156
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0157
    .data.w 0, 0
    .data.l _CAR_MICRO_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0158
    .data.w 0, 0
    .data.l _PV_CBAVER_A1
    .data.w 6, 0, h'0008, 6, 0, 0, 0, 0;
;PV0159
    .data.w 0, 0
    .data.l _PV_GMNVER_A1
    .data.w 6, 0, h'0008, 4, 0, 0, 0, 0;
;PV0160
    .data.w 0, 0
    .data.l _PV_OPCVER_A1
    .data.w 3, 73, 0, 1, 0, 0, 0, 0;
;PV0161
    .data.w 0, 0
    .data.l _PV_CBBVER_A1
    .data.w 6, 0, h'0008, 6, 0, 0, 0, 0;
;PV0162
    .data.w 0, 0
    .data.l _PV0_TBL_B_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0163
    .data.w 0, 0
    .data.l _PV0_TBL_A_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0164
    .data.w 0, 0
    .data.l _PVP_PAR_B_VER-_dpram_top+_dpramB_top
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0165
    .data.w 0, 0
    .data.l _PVP_PAR_A_VER
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0166
    .data.w 0, 0
    .data.l _SEQ_PAR_199
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0167
    .data.w 0, 0
    .data.l _PV0_DEFULT_VER1
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0168
    .data.w 0, 0
    .data.l _PV0_INTER_VER1
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0169
    .data.w 0, 0
    .data.l _PV0_INTER_VER2
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0170
    .data.w 0, 0
    .data.l _PV0_DEFULT_VER2
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0171
    .data.w 0, 0
    .data.l _PV0_SEQ_VER2
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0172
    .data.w 0, 0
    .data.l _PV0_PAR_A_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0173
    .data.w 0, 0
    .data.l _PV0_PAR_B_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0174
    .data.w 0, 0
    .data.l _SVB_RNAORG_PLS1
    .data.w 11, 0, 0, 4, 0, 0, 0, 0;
;PV0175
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0176
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0177
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0178
    .data.w 0, 0
    .data.l _PV_KAJYU1_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0179
    .data.w 0, 0
    .data.l _PV_KAJYU2_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0180
    .data.w 0, 0
    .data.l _PV_KAJYU3_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0181
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 0, h'0008, 4, 0, 0, 0, 0;
;PV0182
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 0, h'0008, 4, 0, 0, 0, 0;
;PV0183
    .data.w 0, 0
    .data.l _PV_LAMPDT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0184
    .data.w 0, 0
    .data.l _PV_AMPDAT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0185
    .data.w 0, 0
    .data.l _PV_RAMPDT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0186
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 0, h'0008, 4, 0, 0, 0, 0;
;PV0187
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0188
    .data.w 0, 0
    .data.l _PVP_RNA_STLORK
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0189
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0190
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0191
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0192
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0193
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0194
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0195
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0196
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0197
    .data.w 0, 0
    .data.l _PV_MLDNO1_F1
    .data.w 9, 56, h'0004, 2, 0, 0, 0, 0;
;PV0198
    .data.w 0, 0
    .data.l _PV_MLDNO2_F1
    .data.w 6, 56, 0, 14, 0, 0, 0, 0;
;PV0199
    .data.w 0, 0
    .data.l _PV0_MONALM_A01
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0200
    .data.w 0, 0
    .data.l _PV0_MONALM_A02
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0201
    .data.w 0, 0
    .data.l _PV0_MONALM_A03
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0202
    .data.w 0, 0
    .data.l _PV0_MONALM_A04
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0203
    .data.w 0, 0
    .data.l _PV0_MONALM_A05
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0204
    .data.w 0, 0
    .data.l _PV0_MONALM_A06
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0205
    .data.w 0, 0
    .data.l _PV0_MONALM_A07
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0206
    .data.w 0, 0
    .data.l _PV0_MONALM_A08
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0207
    .data.w 0, 0
    .data.l _PV0_MONALM_B01
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0208
    .data.w 0, 0
    .data.l _PV0_MONALM_B02
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0209
    .data.w 0, 0
    .data.l _PV0_MONALM_B03
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0210
    .data.w 0, 0
    .data.l _PV0_MONALM_B04
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0211
    .data.w 0, 0
    .data.l _PV0_MONALM_B05
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0212
    .data.w 0, 0
    .data.l _PV0_MONALM_B06
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0213
    .data.w 0, 0
    .data.l _PV0_MONALM_B07
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0214
    .data.w 0, 0
    .data.l _PV0_MONALM_B08
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0215
    .data.w 0, 0
    .data.l _PV0_MONALM_C01
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0216
    .data.w 0, 0
    .data.l _PV0_MONALM_C02
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0217
    .data.w 0, 0
    .data.l _PV0_MONALM_C03
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0218
    .data.w 0, 0
    .data.l _PV0_MONALM_C04
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0219
    .data.w 0, 0
    .data.l _PV0_MONALM_C05
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0220
    .data.w 0, 0
    .data.l _PV0_MONALM_C06
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0221
    .data.w 0, 0
    .data.l _PV0_MONALM_C07
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0222
    .data.w 0, 0
    .data.l _PV0_MONALM_C08
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0223
    .data.w 0, 0
    .data.l _PV0_MONALM_P01
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0224
    .data.w 0, 0
    .data.l _PV0_MONALM_P02
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0225
    .data.w 0, 0
    .data.l _PV0_MONALM_P03
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0226
    .data.w 0, 0
    .data.l _PV0_MONALM_P04
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0227
    .data.w 0, 0
    .data.l _PV0_MONALM_B01_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0228
    .data.w 0, 0
    .data.l _PV0_MONALM_B02_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0229
    .data.w 0, 0
    .data.l _PV0_MONALM_B03_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0230
    .data.w 0, 0
    .data.l _PV0_MONALM_B04_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0231
    .data.w 0, 0
    .data.l _PV0_MONALM_B05_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0232
    .data.w 0, 0
    .data.l _PV0_MONALM_B06_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0233
    .data.w 0, 0
    .data.l _PV0_MONALM_B07_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0234
    .data.w 0, 0
    .data.l _PV0_MONALM_B08_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0235
    .data.w 0, 0
    .data.l _PV0_MONALM_C01_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0236
    .data.w 0, 0
    .data.l _PV0_MONALM_C02_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0237
    .data.w 0, 0
    .data.l _PV0_MONALM_C03_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0238
    .data.w 0, 0
    .data.l _PV0_MONALM_C04_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0239
    .data.w 0, 0
    .data.l _PV0_MONALM_C05_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0240
    .data.w 0, 0
    .data.l _PV0_MONALM_C06_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0241
    .data.w 0, 0
    .data.l _PV0_MONALM_C07_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0242
    .data.w 0, 0
    .data.l _PV0_MONALM_C08_SIGN
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0243
    .data.w 0, 0
    .data.l _PVP_DEB_DAT0
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0244
    .data.w 0, 0
    .data.l _PVP_DEB_DAT1
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0245
    .data.w 0, 0
    .data.l _PVP_DEB_DAT2
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0246
    .data.w 0, 0
    .data.l _PVP_DEB_DAT3
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0247
    .data.w 0, 0
    .data.l _PVP_DEB_DAT4
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0248
    .data.w 0, 0
    .data.l _PVP_DEB_DAT5
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0249
    .data.w 0, 0
    .data.l _PVP_DEB_DAT6
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0250
    .data.w 0, 0
    .data.l _PVP_DEB_DAT7
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0251
    .data.w 0, 0
    .data.l _PVP_DEB_DAT8
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0252
    .data.w 0, 0
    .data.l _PVP_DEB_DAT9
    .data.w 12, 0, 0, 2, 0, 0, 0, 0;
;PV0253
    .data.w 0, 0
    .data.l _PVP_CPUA_TEPPLS
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0254
    .data.w 0, 0
    .data.l _PVP_CPUB_TEPPLS-_dpram_top+_dpramB_top
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0255
    .data.w 0, 0
    .data.l _PVP_CPUA_ANAIN
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0256
    .data.w 0, 0
    .data.l _PVP_CPUB_ANAIN-_dpram_top+_dpramB_top
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0257
    .data.w 0, 0
    .data.l _KIDO_FLG_PV
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0258
    .data.w 0, 0
    .data.l _PVP_COM_ADR
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0259
    .data.w 0, 0
    .data.l _PV0_KAGEN_POSITIONER
    .data.w 7, 52, h'0004, 4, 2, 0, 0, 0;
;PV0260
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0261
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0262
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0263
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0264
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 55, 0, 4, 0, 0, 0, 0;
;PV0265
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 55, 0, 4, 0, 0, 0, 0;
;PV0266
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 55, 0, 4, 0, 0, 0, 0;
;PV0267
    .data.w 0, 0
    .data.l _PV_BARANS_C27
    .data.w 7, 21, h'0004, 2, 2, 0, 0, 0;
;PV0268
    .data.w 0, 0
    .data.l _SV_BARKIJ_A45
    .data.w 0, 21, h'0004, 2, 2, 0, 0, 0;
;PV0269
    .data.w 0, 0
    .data.l _PV_DAIKA1_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0270
    .data.w 0, 0
    .data.l _PV_DAIKA2_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0271
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0272
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0273
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0274
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0275
    .data.w 0, 0
    .data.l _PV_DAITY1_C27
    .data.w 7, 77, h'0004, 2, 2, 0, 0, 0;
;PV0276
    .data.w 0, 0
    .data.l _PV_DAITY2_C27
    .data.w 7, 77, h'0004, 2, 2, 0, 0, 0;
;PV0277
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0278
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0279
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0280
    .data.w 0, 0
    .data.l _CAR_ATU_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0281
    .data.w 0, 0
    .data.l _PVP_COM_ADR
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0282
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0283
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0284
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0285
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0286
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0287
    .data.w 0, 0
    .data.l _PV_DAIHAI_B5
    .data.w 7, 19, h'0004, 4, 2, 0, 0, 0;
;PV0288
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0289
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0290
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0291
    .data.w 0, 0
    .data.l _PV_DAIHAI_B5
    .data.w 7, 19, h'0004, 4, 0, 0, 0, 0;
;PV0292
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0293
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0294
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0295
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0296
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0297
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0298
    .data.w 0, 0
    .data.l _PV_DAIKA1_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0299
    .data.w 0, 0
    .data.l _PV_DAIKA2_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0300
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0301
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0302
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0303
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0304
    .data.w 0, 0
    .data.l _PV_DAIKA1_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0305
    .data.w 0, 0
    .data.l _PV_DAIKA2_C27
    .data.w 7, 76, h'0004, 4, 2, 0, 0, 0;
;PV0306
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0307
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0308
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0309
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0310
    .data.w 0, 0
    .data.l _SV_NEXTNO_D1
    .data.w 15, 56, h'0004, 2, 0, 0, 0, 0;
;PV0311
    .data.w 0, 0
    .data.l _PV_MLDNO2_F11
    .data.w 16, 56, 0, 14, 0, 0, 0, 0;
;PV0312
    .data.w 0, 0
    .data.l _PVP_NOW_ANGLE_RNA
    .data.w 0, 0, H'0100, 2, 0, 0, 0, 0;
;PV0313
    .data.w 0, 0
    .data.l _PV0_NOW_POSI000
    .data.w 0, 19, H'0200, 4, 2, 0, 0, 0;
;PV0314
    .data.w 0, 0
    .data.l _PVP_POWER_MONI
    .data.w 0, 121, h'0100, 2, 0, 0, 0, 0;
;PV0315
    .data.w 0, 0
    .data.l _PV0_SLIDE_POS
    .data.w 0, 117, h'0200, 4, 2, 0, 0, 0;
;PV0316
    .data.w 0, 0
    .data.l _PVP_ARA1_KAJ_T2
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0317
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0318
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0319
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0320
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0321
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0322
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 54, 0, 4, 0, 0, 0, 0;
;PV0323
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0324
    .data.w 0, 0
    .data.l _PVP_1ROT_CALSPM
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0325
    .data.w 0, 0
    .data.l _PVP_ORGRNA_MOV1
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0326
    .data.w 0, 0
    .data.l _PVP_ORGRNA_MOV2
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0327
    .data.w 0, 0
    .data.l _PVP_ORGSTRK_LEG1
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0328
    .data.w 0, 0
    .data.l _PVP_ORGSTRK_LEG2
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0329
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0330
    .data.w 0, 0
    .data.l _PVW_BAKORG_SIN1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0331
    .data.w 0, 0
    .data.l _SVBW_BAKORG_PLS1
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0332
    .data.w 0, 0
    .data.l _PVW_BAKORG_SIN2
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0333
    .data.w 0, 0
    .data.l _SVBW_BAKORG_PLS2
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0334
    .data.w 0, 0
    .data.l _PVP_360_DEG
    .data.w 0, 0, 0, 2, 1, 0, 0, 0;
;PV0335
    .data.w 0, 0
    .data.l _PVP_RENIA_POS1
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0336
    .data.w 0, 0
    .data.l _PVP_RENIA_POS2
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0337
    .data.w 0, 0
    .data.l _PVP_PG_DEG1X
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0338
    .data.w 0, 0
    .data.l _PVP_PG_DEG2X
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0339
    .data.w 0, 0
    .data.l _PVW_ZURE_PLS_SIN
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0340
    .data.w 0, 0
    .data.l _PVW_ZURE_PLS
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0341
    .data.w 0, 0
    .data.l _PVW_ZURE_RNA_SIN
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0342
    .data.w 0, 0
    .data.l _PVW_ZURE_RNA
    .data.w 0, 0, 0, 2, 3, 0, 0, 0;
;PV0343
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0344
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0345
    .data.w 0, 0
    .data.l _PV_ET1VER_A1
    .data.w 6, 119, h'0008, 4, 0, 0, 0, 0;
;PV0346
    .data.w 0, 0
    .data.l _PVP_PG_PLS1
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0347
    .data.w 0, 0
    .data.l _PVP_PG_PLS2
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0348
    .data.w 0, 0
    .data.l _PVP_PG12_DEG1
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0349
    .data.w 0, 0
    .data.l _PV0_CB_C_VER
    .data.w 6, 0, h'0008, 6, 0, 0, 0, 0;
;PV0350
    .data.w 0, 0
    .data.l _PV0_TBL_C_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0351
    .data.w 0, 0
    .data.l _PVP_PAR_C_VER
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0352
    .data.w 0, 0
    .data.l _PV0_PAR_C_CHAR
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0353
    .data.w 0, 0
    .data.l _PV0_IPM_ADR0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0354
    .data.w 0, 0
    .data.l _PV0_IPM_ADR1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0355
    .data.w 0, 0
    .data.l _PV0_IPM_ADR2
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0356
    .data.w 0, 0
    .data.l _PV0_IPM_ADR3
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0357
    .data.w 0, 0
    .data.l 0;_PV0_ATCOL_TIM
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0358
    .data.w 0, 0
    .data.l _PV0_SMPCSR_KJT
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0359
    .data.w 0, 0
    .data.l _PV0_SMPCSR_KJL
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0360
    .data.w 0, 0
    .data.l _PV0_SMPCSR_KJR
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0361
    .data.w 0, 0
    .data.l _PV0_SMPCSR_AGL
    .data.w 0, 0, h'0100, 2, 0, 0, 0, 0;
;PV0362
    .data.w 0, 0
    .data.l _PV0_SMPCSR_RNA1
    .data.w 0, 120, h'0200, 4, 2, 0, 0, 0;
;PV0363
    .data.w 0, 0
    .data.l _PV0_SMPCSR_RNA2
    .data.w 0, 120, h'0200, 4, 2, 0, 0, 0;
;PV0364
    .data.w 0, 0
    .data.l _PV0_SMPCSR_SEQ0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0365
    .data.w 0, 0
    .data.l _PV0_SMPCSR_SEQ1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0366
    .data.w 0, 0
    .data.l _PV0_SMPCSR_TIM
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0367
    .data.w 0, 0
    .data.l _PV0_SMPCSR_POS
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0368
    .data.w 0, 0
    .data.l _PV0_TRDCSR_KJT
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0369
    .data.w 0, 0
    .data.l _PV0_TRDCSR_KJL
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0370
    .data.w 0, 0
    .data.l _PV0_TRDCSR_KJR
    .data.w 0, 53, 0, 2, 0, 0, 0, 0;
;PV0371
    .data.w 0, 0
    .data.l _PV0_TRDCSR_RNA1
    .data.w 0, 120, h'0200, 4, 2, 0, 0, 0;
;PV0372
    .data.w 0, 0
    .data.l _PV0_TRDCSR_RNA2
    .data.w 0, 120, h'0200, 4, 2, 0, 0, 0;
;PV0373
    .data.w 0, 0
    .data.l _PV0_TRDCSR_RNAU
    .data.w 0, 127, 0, 4, 2, 0, 0, 0;
;PV0374
    .data.w 0, 0
    .data.l _PV0_TRDCSR_RNAD
    .data.w 0, 127, 0, 4, 2, 0, 0, 0;
;PV0375
    .data.w 0, 0
    .data.l _PV0_TRDCSR_TIM
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0376
    .data.w 0, 0
    .data.l _PV0_TRDCSR_POS
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0377
    .data.w 0, 0
    .data.l _PV0_TRDCSR_POSL
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0378
    .data.w 0, 0
    .data.l _PV0_TRDCSR_POSR
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0379
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 53, 0, 4, 0, 0, 0, 0;
;PV0380
    .data.w 0, 0
    .data.l _PVP_POWER_KWH
    .data.w 0, 122, 0, 2, 2, 0, 0, 0;
;PV0381
    .data.w 0, 0
    .data.l _PVP_POWER_KWH
    .data.w 0, 122, 0, 2, 2, 0, 0, 0;
;PV0382
    .data.w 0, 0
    .data.l _PVP_POWER_KWH
    .data.w 0, 122, 0, 2, 2, 0, 0, 0;
;PV0383
    .data.w 0, 0
    .data.l _PVP_POWER_KWH
    .data.w 0, 122, 0, 2, 2, 0, 0, 0;
;PV0384
    .data.w 0, 0
    .data.l _PV0_EPMCSR_HOR
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0385
    .data.w 0, 0
    .data.l _PV0_EPMCSR_MIN
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0386
    .data.w 0, 0
    .data.l _PV0_EPMCSR_UEP
    .data.w 0, 0, 0, 4, 2, 0, 0, 0;
;PV0387
    .data.w 0, 0
    .data.l _PV0_EPMCSR_KEP
    .data.w 0, 0, 0, 4, 2, 0, 0, 0;
;PV0388
    .data.w 0, 0
    .data.l _PV0_EPMCSR_TEP
    .data.w 0, 0, 0, 4, 2, 0, 0, 0;
;PV0389
    .data.w 0, 0
    .data.l _PV0_EPML_SCRH
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0390
    .data.w 0, 0
    .data.l _PV0_EPML_SCRM
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0391
    .data.w 0, 0
    .data.l _PV0_EPML_SCRL
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0392
    .data.w 0, 0
    .data.l _PV0_EPMR_SCRH
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0393
    .data.w 0, 0
    .data.l _PV0_EPMR_SCRM
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0394
    .data.w 0, 0
    .data.l _PV0_EPMR_SCRL
    .data.w 0, 0, H'0100, 4, 1, 0, 0, 0;
;PV0395
    .data.w 0, 0
    .data.l _PV0_SMPCSR_EP
    .data.w 0, 122, 0, 4, 2, 0, 0, 0;
;PV0396
    .data.w 0, 0
    .data.l _PV0_TRDCSR_EP
    .data.w 0, 0, 0, 4, 2, 0, 0, 0;
;PV0397
    .data.w 0, 0
    .data.l _SV0_WORKER_COD
    .data.w 3, 123, 0, 2, 0, 0, 0, 0;
;PV0398
    .data.w 0, 0
    .data.l _SV0_ORDER_COD
    .data.w 3, 0, 0, 4, 0, 0, 0, 0;
;PV0399
    .data.w 0, 0
    .data.l _SV0_WORKER_COD
    .data.w 3, 0, 0, 2, 0, 0, 0, 0;
;PV0400
    .data.w 0, 0
    .data.l _SV0_ORDER_COD
    .data.w 3, 0, 0, 4, 0, 0, 0, 0;
;PV0401
    .data.w 0, 0
    .data.l _SV0_PLAN_CNT
    .data.w 0, 0, 0, 4, 0, 0, 0, 0;
;PV0402
    .data.w 0, 0
    .data.l _PV0_INTER_TIM
    .data.w 0, 124, 0, 2, 0, 0, 0, 0;
;PV0403
    .data.w 0, 0
    .data.l _SV0_RNAPOS_MAXO
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0404
    .data.w 0, 0
    .data.l _SV0_RNAPOS_MINO
    .data.w 0, 0, 0, 4, 3, 0, 0, 0;
;PV0405
    .data.w 0, 0
    .data.l _SV0_DAIHAI_LNG1O
    .data.w 0, 0, 0, 2, 1, 0, 0, 0;
;PV0406
    .data.w 0, 0
    .data.l _SV0_DAIHAI_LNG2O
    .data.w 0, 0, 0, 2, 1, 0, 0, 0;
;PV0407
    .data.w 0, 0
    .data.l _PV_KAJYU1_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0408
    .data.w 0, 0
    .data.l _PV_KAJYU2_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0409
    .data.w 0, 0
    .data.l _PV_KAJYU3_A24
    .data.w 4, 53, 4, 2, 0, 0, 0, 0;
;PV0410
    .data.w 0, 0
    .data.l _PV_LAMPDT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0411
    .data.w 0, 0
    .data.l _PV_AMPDAT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0412
    .data.w 0, 0
    .data.l _PV_RAMPDT_A23
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0413
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 0, h'0008, 4, 0, 0, 0, 0;
;PV0414
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0415
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 127, 0, 4, 0, 0, 0, 0;
;PV0416
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 127, 0, 4, 0, 0, 0, 0;
;PV0417
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 127, 0, 4, 0, 0, 0, 0;
;PV0418
    .data.w 0, 0
    .data.l _SV0_RELE_SNO0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0419
    .data.w 0, 0
    .data.l _SV0_RELE_AGL0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0420
    .data.w 0, 0
    .data.l _SV0_RELE_SNO1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0421
    .data.w 0, 0
    .data.l _SV0_RELE_AGL1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0422
    .data.w 0, 0
    .data.l _SV0_SEND_SNO0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0423
    .data.w 0, 0
    .data.l _SV0_SEND_AGL0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0424
    .data.w 0, 0
    .data.l _SV0_SEND_SNO1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0425
    .data.w 0, 0
    .data.l _SV0_SEND_AGL1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0426
    .data.w 0, 0
    .data.l _SV0_TIMING_SNO0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0427
    .data.w 0, 0
    .data.l _SV0_TIMING_AGL0
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0428
    .data.w 0, 0
    .data.l _SV0_TIMING_SNO1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0429
    .data.w 0, 0
    .data.l _SV0_TIMING_AGL1
    .data.w 0, 0, 0, 2, 0, 0, 0, 0;
;PV0430
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0431
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0432
    .data.w 0, 0
    .data.l _PVP_WTJUD_SNO
    .data.w 18, 0, 0, 2, 0, 0, 0, 0;
;PV0433
    .data.w 0, 0
    .data.l _PVP_WTJUD_AGL
    .data.w 0, 0, h'0100, 2, 0, 0, 0, 0;
;PV0434
    .data.w 0, 0
    .data.l _PVP_WTJUD_POS
    .data.w 0, 140, h'0200, 4, 2, 0, 0, 0;
;PV0435
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0436
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0437
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 139, 0, 4, 0, 0, 0, 0;
;PV0438
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 139, 0, 4, 0, 0, 0, 0;
;PV0439
    .data.w 0, 0
    .data.l _SV0_RELE_CAM
    .data.w 0, 137, 0, 2, 0, 0, 0, 0;
;PV0440
    .data.w 0, 0
    .data.l _SV0_SEND_CAM
    .data.w 0, 137, 0, 2, 0, 0, 0, 0;
;PV0441
    .data.w 0, 0
    .data.l _SV0_TIMING_CAM
    .data.w 0, 137, 0, 2, 0, 0, 0, 0;
;PV0442
    .data.w 0, 0
    .data.l _PV0_FIXBF_SPD
    .data.w 0, 139, 0, 2, 1, 0, 0, 0;
;PV0443
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 142, 0, 4, 0, 0, 0, 101;
;PV0444
    .data.w 0, 0
    .data.l _CAR_KAJ_AREA
    .data.w 6, 142, 0, 4, 0, 0, 0, 101;
;PV0445
    .data.w 0, 0
    .data.l _CAR_DO_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 0;
;PV0446
    .data.w 0, 0
    .data.l _CAR_DO_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 0;
;PV0447
    .data.w 0, 0
    .data.l _CAR_DO_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 0;
;PV0448
    .data.w 0, 0
    .data.l _CAR_DO_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 0;
;PV0449
    .data.w 0, 0
    .data.l _CAR_DO_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 0;
;PV0450
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 0;
;PV0451
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 0;
;PV0452
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 0;
;PV0453
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 0;
;PV0454
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 0;
;PV0455
    .data.w 0, 0
    .data.l _CAR_PAR_AREA
    .data.w 6, 102, 0, 4, 0, 0, 0, 0;
;PV0456
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 97, 0, 4, 0, 0, 0, 0;
;PV0457
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 98, 0, 4, 0, 0, 0, 0;
;PV0458
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 99, 0, 4, 0, 0, 0, 0;
;PV0459
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 100, 0, 4, 0, 0, 0, 0;
;PV0460
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 101, 0, 4, 0, 0, 0, 0;
;PV0461
    .data.w 0, 0
    .data.l _CAR_TIM_AREA
    .data.w 6, 102, 0, 4, 0, 0, 0, 0;
;PV0462
    .data.w 0, 0
    .data.l _PV0_LFEED_POS
    .data.w 0, 152, 0, 4, 2, 0, 0, 0;
;PV0463
    .data.w 0, 0
    .data.l _SV0_LFEED_HSIS
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0464
    .data.w 0, 0
    .data.l _SV_LFEED_HOSIN
    .data.w 11, 153, 0, 2, 2, 0, 0, 0;
;PV0465
    .data.w 0, 0
    .data.l _SV0_LFEED_HSOS
    .data.w 6, 0, 0, 2, 0, 0, 0, 0;
;PV0466
    .data.w 0, 0
    .data.l _SV_LFEED_HOSOT
    .data.w 11, 153, 0, 2, 2, 0, 0, 0;
;PV0467
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0468
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0469
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0470
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0471
    .data.w 0, 0
    .data.l _PV0_LFEED_TYPE
    .data.w 6, 147, 0, 16, 0, 0, 0, 0;
;PV0472
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 147, 0, 4, 0, 0, 0, 0;
;PV0473
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 147, 0, 4, 0, 0, 0, 0;
;PV0474
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 147, 0, 4, 0, 0, 0, 0;
;PV0475
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 147, 0, 4, 0, 0, 0, 0;
;PV0476
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 147, 0, 4, 0, 0, 0, 0;
;PV0477
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0478
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;
;PV0479
    .data.w 0, 0
    .data.l _CAR_LNG_AREA
    .data.w 6, 0, 0, 4, 0, 0, 0, 0;

