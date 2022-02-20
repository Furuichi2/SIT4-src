
;/*     表示条件文字制御情報テーブル      */

;CH0001  荷重関係
    .data.l _SEQ_020_SV
    .data.w h'0100, 0, 0, 0, 0, 0; 
;CH0002  型関係
    .data.l _SEQ_PAR_107
    .data.w h'0001, 0, 0, 0, 0, 0; 
;CH0003  ﾛｯﾄｶｳﾝﾀ1
    .data.l _SEQ_016_SV
    .data.w h'1000, 0, 0, 0, 0, 0; 
;CH0004  ﾛｯﾄｶｳﾝﾀ2
    .data.l _SEQ_016_SV
    .data.w h'4000, 0, 0, 0, 0, 0; 
;CH0005  ｴｼﾞｪｸﾀ1
    .data.l _SEQ_017_SV
    .data.w h'0010, 0, 0, 0, 0, 0; 
;CH0006  ｴｼﾞｪｸﾀ2
    .data.l _SEQ_017_SV
    .data.w h'0080, 0, 0, 0, 0, 0; 
;CH0007  ｴｼﾞｪｸﾀ3
    .data.l _SEQ_017_SV
    .data.w h'0400, 0, 0, 0, 0, 0; 
;CH0008  ｴｼﾞｪｸﾀ4
    .data.l _SEQ_017_SV
    .data.w h'2000, 0, 0, 0, 0, 0; 
;CH0009  ｴｼﾞｪｸﾀ5
    .data.l _SEQ_018_SV
    .data.w h'0001, 0, 0, 0, 0, 0; 
;CH0010  ｴｼﾞｪｸﾀ6
    .data.l _SEQ_018_SV
    .data.w h'0008, 0, 0, 0, 0, 0; 
;CH0011  ﾐｽﾌｨｰﾄﾞ1
    .data.l _SEQ_018_SV
    .data.w h'0100, 0, 0, 0, 0, 0; 
;CH0012  ﾐｽﾌｨｰﾄﾞ2
    .data.l _SEQ_018_SV
    .data.w h'0200, 0, 0, 0, 0, 0; 
;CH0013  ﾐｽﾌｨｰﾄﾞ4回路
    .data.l _SEQ_018_SV
    .data.w h'0400, 0, 0, 0, 0, 0; 
;CH0014  ﾐｽﾌｨｰﾄﾞ6回路
    .data.l _SEQ_018_SV
    .data.w h'0800, 0, 0, 0, 0, 0; 
;CH0015  ﾛｰﾀﾘｶﾑ1～4
    .data.l _SEQ_018_SV
    .data.w h'1000, 0, 0, 0, 0, 0; 
;CH0016  ﾛｰﾀﾘｶﾑ5～8
    .data.l _SEQ_018_SV
    .data.w h'4000, 0, 0, 0, 0, 0; 
;CH0017  ﾛｰﾀﾘｶﾑ9～12
    .data.l _SEQ_019_SV
    .data.w h'0001, 0, 0, 0, 0, 0; 
;CH0018  ﾛｰﾀﾘｶﾑ13～16
    .data.l _SEQ_019_SV
    .data.w h'0004, 0, 0, 0, 0, 0; 
;CH0019  ﾛｰﾀﾘｶﾑ17～20
    .data.l _SEQ_018_SV
    .data.w h'0040, 0, 0, 0, 0, 0; 
;CH0020  ﾀﾞｲﾊｲﾄ表示
    .data.l _SEQ_020_SV
    .data.w h'0020, 0, 0, 0, 0, 0; 
;CH0021  ｽﾗｲﾄﾞ自動調節
    .data.l _SEQ_020_SV
    .data.w h'0040, 0, 0, 0, 0, 0; 
;CH0022  簡易見える化
    .data.l _SEQ_024_SV
    .data.w h'0080, 0, 0, 0, 0, 0; 
;CH0023  加振機能設定
    .data.l _SEQ_024_SV
    .data.w h'0400, 0, 0, 0, 0, 0; 
;CH0024  電力モニタ
    .data.l _SEQ_024_SV
    .data.w h'0800, 0, 0, 0, 0, 0; 
;CH0025  負荷率表示
    .data.l _SEQ_PAR_103
    .data.w h'1000, 1, 0, 0, 0, 0; 
;CH0026  電力量表示
    .data.l _SEQ_PAR_103
    .data.w h'1000, 0, 0, 0, 0, 0; 
;CH0027  電力量単位kW
    .data.l _SV0_EP_AVE
    .data.w h'0001, 0, 0, 0, 0, 0; 
;CH0028  電力量単位Wh
    .data.l _SV0_EP_AVE
    .data.w h'0002, 0, 0, 0, 0, 0; 
;CH0029  電力量単位kW
    .data.l _SV0_EP_AVE
    .data.w h'0010, 0, 0, 0, 0, 0; 
;CH0030  電力量単位Wh
    .data.l _SV0_EP_AVE
    .data.w h'0020, 0, 0, 0, 0, 0; 
;CH0031  ｶｳﾝﾄ値修正
    .data.l _SEQ_PAR_107
    .data.w h'0010, 0, 0, 0, 0, 0; 
;CH0032  生産管理
    .data.l _SEQ_PAR_113
    .data.w h'0200, 0, 0, 0, 0, 0; 
;CH0033  制動試験ﾀｲﾏ表示
    .data.l _SEQ_PAR_113
    .data.w h'0008, 0, 0, 0, 0, 0; 
;CH0034  ｼｽﾃﾑ設定遷移
    .data.l _SEQ_PAR_051
    .data.w h'8000, 0, 0, 0, 0, 0; 
;CH0035  ﾀｯﾁ位置検出速度%
    .data.l _SEQ_PAR_103
    .data.w h'0400, 1, 0, 0, 0, 0; 
;CH0036  ｼｽﾃﾑ設定1-15非表示
    .data.l _SEQ_PAR_113
    .data.w h'0080, 1, 0, 0, 0, 0; 
;CH0037  機械下限／上限の非表示指令
    .data.l _SEQ_PAR_113
    .data.w h'0020, 1, 0, 0, 0, 0; 

