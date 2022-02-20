//	***************************
//	***			***
//	***	ﾎﾟｼﾞｼｮﾅ用ﾒﾓﾘ	***
//	***			***
//	***************************
S4b	POSINER_PV_POS;
S4b	POSINER_OLDPV_POS;
S4b	POSINER_MOSTPV_POS;//指令OFF後のｲﾝﾎﾟｼﾞｼｮﾝにもっとも近い位置
S4b	POSINER_SV_POS;//目標位置
S4b	POSINER_SV_OVRPOS;//目標位置+ｵｰﾊﾞ量
S4b	POSINER_SV_STPPOS;//目標位置+停止量
S2b	POSINER_FLG;
S2b	POSINER_STS;
S2b	POSINER_RETRY_CNT;
S2b	POSINER_STOPCHK_TIM1;//1000 1秒
S2b	POSINER_STOPCHK_TIM2;//1000 1秒


//
S4b	SET1_ATSLID_BAKLNG	;//スライド自動調節　戻り量   "
S4b	SET1_ATSLID_DNOBJ1	;//スライド自動調節　下降停止 0~99
S4b	SET1_ATSLID_UPOBJ1	;//スライド自動調節　上昇停止 "
S4b	SET1_ATSLID_COEF1	;//スライド自動調節　制御精度 "
S2b	SET1_ATDAT_DOTPOS	;//小数点


