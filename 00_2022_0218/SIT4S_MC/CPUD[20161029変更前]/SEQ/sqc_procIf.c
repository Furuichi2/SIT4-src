//	*******************************************
//	***										***
//	***										***
//	***		本体(cpud)とのｲﾝﾀｰﾌｪｲｽ関数		***
//	***										***
//	***										***
//	***										***
//	*******************************************
//	本体とのｲﾝﾀｰﾌｪｲｽをこれだけ
//	[このﾌｧｲﾙ内ではｵﾘｼﾞﾅﾙの構造体,define,equを使用しない]

//	------------ 外部への定義 ------------
void SqcInit1(void);
void SqcInit2(void);
void SqcIntHigh(void);	//1~3msec
void SqcIntMDL(void);	//10msec
void SqcMain(void);		//ﾊﾞｯｸｸﾞﾗﾝﾄﾞ


//	------------ ﾒﾓﾘ定義---------
char SqcInitFlg;
char SqcStartF;



//	***********************************************
//	***											***
//	***		inital1								***
//	***		このｿﾌﾄの中で1番初めに1回呼ばれる	***
//	***		割込解除前							***
//	***											***
//	***********************************************
void SqcInit1(void){
}

//	***********************************************
//	***											***
//	***		inital2								***
//	***		このｿﾌﾄの中で2番目に				***
//	***		ﾃﾞｰﾀ参照可能な条件で1回だけ呼ばれる	***
//	***											***
//	***********************************************
void SqcInit2(void){

	SqcInitFlg=1;
}

//	***********************************************
//	***											***
//	***		定周期								***
//	***											***
//	***********************************************
//	1ms,2ms,2.5ms,3.3ms,5ms		
//	-->10msecﾀｲﾏを作成できること但し、標準で10msec作成できるなら不要
//	予定は2msec
void SqcIntHigh(void){
	if(SqcInitFlg){//ﾀｲﾏ割込の純粋なﾀｲﾏ処理,
	}
	if(SqcStartF){	//ｼｰｹﾝｽ,ｼｰｹﾝｽﾀｲﾏ処理
	}
}

//	***********************************************
//	***											***
//	***		定周期								***
//	***											***
//	***********************************************
//	5ms,10ms,20ms,50ms,100ms
//	予定は10ms
void SqcIntMDL(void){
	if(SqcInitFlg){	//ﾀｲﾏ割込の純粋なﾀｲﾏ処理,
	}
	if(SqcStartF){	//ｼｰｹﾝｽ,ｼｰｹﾝｽﾀｲﾏ処理
	}
}

//	***********************************************
//	***											***
//	***		メイン								***
//	***											***
//	***********************************************
void SqcMain(void){
	if(SqcInitFlg){
		SqcStartF=1;//割込ｼｰｹﾝｽ起動
	}
}

