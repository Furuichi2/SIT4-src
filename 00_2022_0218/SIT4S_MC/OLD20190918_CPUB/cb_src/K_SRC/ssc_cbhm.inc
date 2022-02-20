
//	***********************************
//	***				***
//	***	画面データ		***
//	***	0.1角度→0.001mm変換	***
//	***				***
//	***********************************
//	内容
//	Input	mem1 +/- 0~360.0度
//	Output  mem2 +/- 999.999mm

	extern	S4b	SVP_RNA_STLORK;
	extern	S4b	DISP_SV_MM_DAT;
	extern	S4b	DISP_SV_DG_DAT;	
	extern	U2b	PVP_1ROT_CALSPM	;//予想運転速度

	extern	C_ASM_CHG_ROOT(void);
	extern	void Calc1CycleSpmMake(void);

S4b DigRnaChange1(S2b digdt){
	S4b ret4b;

	if(digdt<3599){
		DISP_SV_DG_DAT=digdt;//0.1度
		C_ASM_DISP_DG_CHG_MM();
		ret4b=DISP_SV_MM_DAT;//0.001mm
	}else{
		ret4b=0;// DaTa ERR
	}
	return(ret4b);	//100.000mm
}


//	***********************************
//	***				***
//	***	画面データ		***
//	***	0.001mm->0.1度変換	***
//	***				***
//	***********************************
//	内容
//	Input	前回までmem1 +/- 0~360.0度,mem2 +/- 999.999mm
//	Output  今回の0~360.0度

S2b RnaDigChange1(S2b old_digdt,S4b renea_pos){
	S4b wk4b1;
	S2b	ret2b;
	DISP_SV_DG_DAT=(S4b)old_digdt;//0.1度
	DISP_SV_MM_DAT=renea_pos;//0.001mm data
	C_ASM_DISP_MM_CHG_DG();
	wk4b1=DISP_SV_DG_DAT;//0.1度
	
	if(3599<wk4b1){//2007-01-11
		wk4b1=0;
	}
	ret2b=(S2b)wk4b1;
	return(ret2b);	//100.000mm
	
}

//	***********************************
//	***				***
//	***	画面データ		***
//	***	角度→mm変換サンプル	***
//	***				***
//	***********************************
void smp1_test(void){
	S4b wk;
	wk=DigRnaChange1(300);// 30.0度の意味
	
}

void smp3_test(void){
	S2b wk;
	wk=RnaDigChange1(400,50000);//前回角度=40.0度 今回設定=50.000mm
	
}



//	***********************************************************
//	***							***
//	***	設定－サイクル時間・目標位置グラフ		***
//	***	x,y-DOT						***
//	***							***
//	***********************************************************
//	Input
//	S2b *xdot  	Ｘ座標格納ｱﾄﾞﾚｽ
//	S2b *ydot  	Ｙ座標格納ｱﾄﾞﾚｽ
//	S2b *cnt	ﾃﾞｰﾀ個数ｱﾄﾞﾚｽ (今回)
//	S2b *point	X,Y格納ｱﾄﾞﾚｽのTOPを示す
//	S2b *chkflg	演算結果　ﾃﾞｰﾀ有効、始点、終点情報
//
//10段仕様の場合
//POS1,TIM1*10=20+10+3=>33
//[30]==>40が必要
//


	extern	S2b DRAW_CHK_XDOT[30];
	extern	S2b DRAW_CHK_YDOT[30];
	extern	S2b DRAW_CHKFLG;
	extern	S2b DRAW_POINT;
	extern	S2b DRAW_CNT;
           
	extern	S2b SvStepXYDataMake1(S2b *xdot,S2b *ydot,S2b *cnt,S2b *point,S2b *chkflg);
void draw_smple(void){ 
	S2b wk;
	wk=1;
	wk=SvStepXYDataMake1(&(DRAW_CHK_XDOT[0]),&(DRAW_CHK_YDOT[0]),&DRAW_CNT,&DRAW_POINT,&DRAW_CHKFLG);
}


//	***************************************************
//	***						***
//	***		描画ソフト作成中		***
//	***						***
//	***************************************************
//
//	(0,0)			(500,0)
//	|
//	|
//	|
//	|
//	|
//	|
//	+---------------------------+
//	(0,500)			(500,500)
//
//	 始点(x,y)
//	|(0sec,0度)
//	|p0(0,y0)
//	| +
//	|  + p1(x1,y1),t1
//	|   +------
//	|
//	|
//	|
//	|
//	|
//	|(0sec,180度)
//	+------------------------------------------->(時間)
//	p0(x,y)=(0,y0)
//
//
//			  +++++*++++++++++++++*
//		          +   *              + *
//		          +  *               +  *
//		      	  + *                +   *
//     +------------------+                  +----*-------+
//     +     v=pls/s                                      +
//     +                                                  +
//  ---+                                                  +--------------
//    f(dig1-dig0)  /v =t1
//
//        dig(ﾘﾝｸ回転角)
//
//    (x0,y0)    v1    (x1,y1)t1 
//      V[rpm]/60
//
//   N回転でM度動作する
//
//    dig
//
//	[1] ｸﾗﾝｸ設定A->ﾘﾝｸ角度a
//	    ｸﾗﾝｸ設定B->ﾘﾝｸ角度b
//	ﾘﾝｸ動作速度=2000.0rpm/60*M/N
//	(b-a)/V=t
//	加速時間V*T/Vmax程度にしておくか
//	10msec単位で考える
//
// XdotMax=
// YdotMax=
//
//	基本式  t=s/v		  :step 
//
//		t= (s-ta*v)/v+2ta :台形
//		
//		t= (s-ta*v/2)/v+ta :片側台形 
//
	extern	U2b SET1_MRTION_SEL1;//.SRES	2	;回転方式
	extern	U2b SET1_MTSTEP_MAXM;//.SRES	2	;段数
	extern	U2b MODE_SEL;
	extern	U2b SET1_OBJECT_TIM_TOP;//
	extern	U2b SET1_INCPLS_HOSN;//PG補正N　ﾓｰﾀN回 1rpm単位
//	extern	U2b SET1_INCPLS_HOSM;//PG補正M　ｸﾗﾝｸ角度M
	extern	U4b SETY_INCPLS_HOSM01X;//0.1度
	extern	U2b SET1_MOTRPM_MAXM;//ﾓｰﾀ最大回転数
	extern	U2b SET1_ACCLAT_TIM1;//加減速時間
	extern	U2b SVP_OBJECT_TIM_TOP[20]	;//01段目停止時間
	extern	U2b SVP_OBJECT_SPD_TOP[20]	;//
	extern	U4b SVP_OBJECT_POS_TOP[20]	;//01段目目標位置
	extern	U2b SVP_OBJECT_DIG_TOP[20]	;//01段目角度位置(ｸﾗﾝｸ)
	extern	U2b SET1_OBJECT_DIG_TOP[40]	;//01段目角度位置(ﾘﾝｸ)
	extern	U4b	SVP_UPAREA_POS0		;//待機点位置
	extern	U2b	SVP_UPAREA_DIG0		;//待機点角度
	extern	U2b	SVP_UPAREA_SPD0		;//基準速度
	extern	U2b	SVP_UPAREA_TIM0		;//待機時間
	extern	U2b	SETX_UPAREA_DIG;

	extern	S2b mot_length_make1(S2b obj_Ldig,S2b st_dig,S2b last_cnt_flg);//符号付
	extern	U4b tim_calc_up_dn(S2b length,S2b v_s,S2b v_x,S2b v_e,S2b Ta_max,S2b Vmax);
	extern	S2b area1800chg(S2b digdata);//

S2b SvStepXYDataMake1(S2b *xdot,S2b *ydot,S2b *cnt,S2b *point,S2b *chkflg){
	S2b XdotMax;
	S2b YdotMax;

	S2b step_max,ret2b,data_cnt,i,dim_max;
	S2b Vmax;
	U4b wk4b1,wk4b2,total_tim;
	S2b Ta_max,ta,stop_flg,dirct_flg,last_cnt_flg;
	S4b xtim[20+20];//+20(2004-01-26 add 20)
	S2b yLdig[20+20],yCdig[20+20];//yVCdig<ｸﾗﾝｸ> (2004-01-26 add 20)
	S2b v_s,v_x,v_e,w_t;
	S2b st_dig,obj_Ldig,obj_Cdig,length,length180,wkflg1,wkflg2;
	
	ret2b=0;
	XdotMax=500;
	YdotMax=500;

	Ta_max=SET1_ACCLAT_TIM1/10;//1msec==>10msec
	Ta_max=1;
	
	if(Ta_max==0){
		Ta_max=1;
	}

	dim_max=SET1_MTSTEP_MAXM;
	step_max=SET1_MTSTEP_MAXM+1;
	if(SET1_INCPLS_HOSN){
		wk4b1=SET1_MOTRPM_MAXM*SETY_INCPLS_HOSM01X;//SET1_INCPLS_HOSM;
		wk4b1=wk4b1/SET1_INCPLS_HOSN/(60*10);//2000.0rpm/60.0*360.0
		Vmax=wk4b1;
	}else{
		Vmax=1;//***.*度/sec
	}

//2004-01-26	if((step_max<0) || (6<step_max) ){
	if((step_max<0) || ((10+1)<step_max) ){//step_maxは保証されているからﾘﾐｯﾄは不要
		data_cnt=2;//x,y座標ﾃﾞｰﾀ数
		xdot[0]=0;//ﾃﾞｰﾀ異常
		ydot[0]=0;//ﾃﾞｰﾀ異常
		xdot[1]=1;//ﾃﾞｰﾀ異常
		ydot[1]=1;//ﾃﾞｰﾀ異常
		step_max=1;
	}else{
		//時間の算出
		//開始ﾎﾟｲﾝﾄ

		data_cnt=1;//x,y座標ﾃﾞｰﾀ数
		xtim[0]=0;
		yLdig[0]=SETX_UPAREA_DIG;//ﾘﾝｸ角度
		if(SET1_MRTION_SEL1&cBIT0){//回転
			yCdig[0]=0;//
		}else{
			yCdig[0]=SVP_UPAREA_DIG0;//ｸﾗﾝｸ角度
		}

		i=1;
		v_x=0;
		v_s=0;
		v_e=0;
		last_cnt_flg=0;
		dirct_flg=0;//正転より開始
		stop_flg=1;//前回停止
		total_tim=0;
		while(i <= step_max){
			if(i==step_max){
				v_s=v_x;
				//v_x=SVP_UPAREA_SPD0;
				v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1段目
				
				v_e=0;
				w_t=SVP_UPAREA_TIM0;
				if(stop_flg){
					v_s=0;//前回停止
				}
				
				if(MODE_SEL&cBIT3){//連続
					if(SET1_MRTION_SEL1&cBIT0){//回転
						if(w_t==0){
							v_e=SVP_OBJECT_SPD_TOP[0]*Vmax/1000;//100.0% 1段目
						}
					}
				}
				st_dig=yLdig[data_cnt-1];
				if(SET1_MRTION_SEL1&cBIT0){//回転
					obj_Ldig=SETX_UPAREA_DIG;//ﾘﾝｸ角度
					obj_Cdig=0;//ｸﾗﾝｸ=0
					last_cnt_flg=1;
				}else{
					obj_Ldig=SETX_UPAREA_DIG;//ﾘﾝｸ角度
					obj_Cdig=SVP_UPAREA_DIG0;//ｸﾗﾝｸ角度
				}
				
			}else{
				v_s=v_x;//開始速度
				v_x=SVP_OBJECT_SPD_TOP[i-1]*Vmax/1000;//100.0%　目標速度
				v_e=0;
				w_t=SVP_OBJECT_TIM_TOP[i-1];
				if(stop_flg){
					v_s=0;//前回停止
				}
				if(i==1){//1段
					if(MODE_SEL&cBIT3){//連続
						if(SET1_MRTION_SEL1&cBIT0){//回転
							if(SVP_UPAREA_TIM0==0){
								v_s=v_x;
							}
						}
					}
				}
				st_dig=yLdig[data_cnt-1];
				obj_Cdig=SVP_OBJECT_DIG_TOP[i-1];
				obj_Ldig=SET1_OBJECT_DIG_TOP[i-1];
				if(w_t==0){
					v_e=v_x;
					stop_flg=0;
				}else{
					stop_flg=1;
				}
			}
			
			length=mot_length_make1(obj_Ldig,st_dig,last_cnt_flg);//符号付
			if(length<0){
				if(dirct_flg==0){//前は正転
					v_s=0;
				}
				dirct_flg=1;//逆転
				length=length*-1;
			}else{
				if(dirct_flg!=0){//前は逆転
					v_s=0;
				}
				dirct_flg=0;//正転
			}
			wkflg1=0;
			//無理やり180度(ﾘﾝｸもｸﾗﾝｸも180度は同じ)通過演算をいれる
			if(i==1){
				wkflg2=0;//開始は下降
			}else{
				wkflg2=area1800chg(st_dig);
			}
			if(dirct_flg==0){//正転
				if(!wkflg2){//下降
					wkflg2=area1800chg(obj_Ldig);//0:正転
					if(wkflg2){//今回上昇
						wkflg1=1;
					}
				}
			}else{//逆転
				if(wkflg2){//上昇
					wkflg2=area1800chg(obj_Ldig);//
					if(!wkflg2){//今回下降
						wkflg1=1;
					}
				}
			}
			//通常の計算
			wk4b1=tim_calc_up_dn(length,v_s,v_x,v_e,Ta_max,Vmax);
			wk4b2=0;
			if(wkflg1){//180度をまたぐ
				length180=mot_length_make1(1800,st_dig,0);//符号付
				if(length180<0){
					length180= -1*length180;
				}
				//とりあえず対策 うそソフト
				wk4b2=tim_calc_up_dn(length180,v_s,v_x,v_x,Ta_max,Vmax);
				//if(wk4b1<=wk4b2){//wk4b1と同じ結果になった
				//	wk4b2=wk4b2/2;//半分の点にしておく
				//}
				//
				xtim[data_cnt]=wk4b2;
				total_tim=total_tim+wk4b2;
				yLdig[data_cnt]=1800;//
				yCdig[data_cnt]=1800;//
				data_cnt++;
			}
			//xtim[data_cnt]=wk4b1;
			//total_tim=total_tim+wk4b1;
			xtim[data_cnt]=wk4b1-wk4b2;
			total_tim=total_tim+wk4b1-wk4b2;
			yLdig[data_cnt]=obj_Ldig;
			yCdig[data_cnt]=obj_Cdig;
			data_cnt++;
			if(w_t!=0){
				xtim[data_cnt]=w_t;
				total_tim=total_tim+(U4b)w_t;
				yLdig[data_cnt]=obj_Ldig;
				yCdig[data_cnt]=obj_Cdig;
				data_cnt++;
			}

			i++;
		}

	//	***************************
	//	***	ﾄﾞｯﾄ変換	***
	//	***************************
		i=0;
		wk4b1=0;
		while(i<data_cnt){
			wk4b1=wk4b1+(S4b)xtim[i];
			xdot[i]=wk4b1*XdotMax/total_tim;
			
			if(yCdig[i]>=1800){
//				ydot[i]=(1800-(3600-yCdig[i]))*YdotMax/1800;
				ydot[i]=YdotMax-(1800-(3600-yCdig[i]))*YdotMax/1800;
			}else{
//				ydot[i]=(1800-yCdig[i])*YdotMax/1800;
				ydot[i]=YdotMax-(1800-yCdig[i])*YdotMax/1800;
			}

			;
			yLdig[0]=SETX_UPAREA_DIG;//ﾘﾝｸ角度
		
			i++;
		}
		ret2b=(cBIT2|cBIT1|cBIT0);//ﾃﾞｰﾀ有効
	}

	*(point+0)=data_cnt-1;
	*(cnt+0)=data_cnt;
	*(chkflg+0)=ret2b;
	
	
	Calc1CycleSpmMake();//予想spm表示
	
	return(ret2b);
}

//	v_x=v_s:立ち上がりステップ
//	v_x=v_e:立下りステップ
//	v_x=v_s=v_e 両方ステップ
//	ans.10msec
//
//	時間は1:10MSEC
//	速度は0.1度/SEC
//	位置は0.1度
//
//
typedef float 	dbl;		/*	s4b	*/

U4b tim_calc_up_dn(S2b length,S2b v_s,S2b v_x,S2b v_e,S2b Ta_max,S2b Vmax){
	S4b tx,delt_v,delt_ts,delt_ss,delt_te,delt_se,wk1,chk1,chk2;
	dbl dbtm1,dbtm2,dbA,dbB,dbC,dbwk1,dbwk2;
	
	if(v_x==0){
		tx=1;
	}else{
	//立ち上がり時間と面積
		delt_ts=((S4b)v_x-(S4b)v_s)*(S4b)Ta_max/(S4b)Vmax;	//v_s開始速度 v_x目標速度 開始から目標に達する時間(msec)
		if(delt_ts<0){
			delt_ts=delt_ts*-1;	//下降時は負
		}
		delt_ss=((S4b)v_x+(S4b)v_s)*(S4b)delt_ts/2;	//tsの台形の面積 msecなので1000された距離
		delt_ss=delt_ss/100;				//0.1度単位に戻す 2004-05-26


	//立ち下がり時間と面積(停止タイプのみ発生　連続はv_x=v_e)
		delt_te=((S4b)v_x-(S4b)v_e)*(S4b)Ta_max/(S4b)Vmax;
		if(delt_te<0){
			delt_te=delt_te*-1;
		}
		delt_se=((S4b)v_x+(S4b)v_e)*(S4b)delt_te/2;
		delt_se=delt_se/100				;//2004-05-26

//		tx=((S4b)length*100-(S4b)delt_ss-delt_se)/(S4b)v_x+delt_ts+delt_te;//
		tx=((S4b)length-(S4b)delt_ss-delt_se)*100/(S4b)v_x;//*100は0msec単位にする
		wk1=tx+delt_ts+delt_te;
		if(tx>0){
			tx=wk1;//位置×100倍で扱っているから 定速部分があればこれでok
		}else{
//			tx=delt_ts;//本当は面倒な式 うそソフト
			dbA=(dbl)Vmax/(dbl)Ta_max;//10msec当たりの加速時間
			if(v_s > v_x){
				dbA=dbA*(-1);
			}
			//	x=[-b±sqrt(b*b-4ac)]/2a;
			dbB=(dbl)(v_s)*2;
			dbC=(dbl)length*-2;
			dbwk1=dbB*dbB-4*dbA*dbC;
			chk1=(S4b)dbwk1;
			if(0<dbwk1){
				ROOT_MAIN_INP=(S4b)dbwk1;
				C_ASM_CHG_ROOT();
				dbwk2=(S4b)ROOT_MAIN_OUT;

				//dbwk2=sqrt(dbwk1);
				chk1=(S4b)dbwk1;
			}else{
				dbwk2=0;
			}
			dbwk1=dbwk2;
			dbtm1= (-1*dbB+ dbwk1)/2/dbA;
			dbtm2= (-1*dbB- dbwk1)/2/dbA;
			chk1=(S4b)dbtm1;
			chk2=(S4b)dbtm2;
			
			if(0<=dbtm1&&(dbtm1<=(dbl)Ta_max) ){
			}else{
				if(0<=dbtm2&&(dbtm2<=(dbl)Ta_max) ){
					dbtm1=dbtm2;
				}else{
					dbtm1=0;
				}
			}
			tx=(S4b)dbtm1;
		}
		if(tx<=0){
			tx=1;
		}
	}
	return((U2b)tx);
}


//;//符号付
S2b mot_length_make1(S2b obj_Ldig,S2b st_dig,S2b last_cnt_flg){
	S2b length;
	if(last_cnt_flg){
		if(st_dig >= SETX_UPAREA_DIG){
			length=3600-st_dig+SETX_UPAREA_DIG;
		}else{
			length=SETX_UPAREA_DIG-st_dig;
		}
		goto exit;
		
	}

	if(SET1_MRTION_SEL1&cBIT0){//回転
		if(obj_Ldig >= SETX_UPAREA_DIG){
			if(st_dig >= SETX_UPAREA_DIG){
				length=obj_Ldig-st_dig;
			}else{//逆転
				length=-1*(3600-obj_Ldig+st_dig);
			}
		}else{
			if(st_dig >= SETX_UPAREA_DIG){
				length=3600-st_dig+obj_Ldig;//
			}else{//
				length=obj_Ldig-st_dig;
			}
		}
	}else{
		//これ上では回転と同じ
		if(obj_Ldig >= SETX_UPAREA_DIG){
			if(st_dig >= SETX_UPAREA_DIG){
				length=obj_Ldig-st_dig;
			}else{//逆転
				length=-1*(3600-obj_Ldig+st_dig);
			}
		}else{
			if(st_dig >= SETX_UPAREA_DIG){
				length=3600-st_dig+obj_Ldig;//
			}else{//
				length=obj_Ldig-st_dig;
			}
		}
	}
exit:;
	return(length);
	
}

//	== メモ ===
//	Input 必要となる情報
//	工程数
//	速度、位置、時間
//	運転モード（待機点と終点）
//	Ｘ座標基数   500
//	Ｙ座標基数 10000
//	Output
//	X1,Y1,,,Xn,Yn及び個数
//	始点があるかどうか(実測時には必要)FLG1
//	終点があるかどうか(実測時には必要)FLG2
//	(実測時にはあったほうが良い)
//
//
S2b SvStepXYDataMake2(S2b *xdot,S2b *ydot,S2b *cnt,S2b *point,S2b *chkflg){
	S2b ret2b,i;
	S2b step_no=4;//本来画面設定
	
	ret2b=0;	//ﾃﾞｰﾀ無効 bit0=bit1=BIT2=0
			//	   BIT0=1ﾃﾞｰﾀ有効
			//始点有り bit1=1始点有り
			//終点有り bit2=1終点有り
	i=1;
	while(i<step_no){
		*(xdot+(*point))=100*i;
		*(ydot+(*point))=1000*i;
		i++;
		*point++;
	}
	*cnt=i;//
	ret2b=(cBIT2|cBIT1|cBIT0);//ﾃﾞｰﾀ有効


	*chkflg=ret2b;
	return(ret2b);
}


S2b area1800chg(S2b digdata){
	S2b ret2b;
	if(SETX_UPAREA_DIG > 1800){
		if(SETX_UPAREA_DIG < digdata){
				ret2b=0;//下降
		}else{
			if(digdata >= 1800){
				ret2b=1;//上昇
			}else{
				ret2b=0;//下降
			}
		}
		
	}else{
		if((SETX_UPAREA_DIG<digdata) && (digdata<=1800)){
			ret2b=0;//下降
		}else{
			ret2b=1;//上昇
		}
	}
	return(ret2b);
}


//	***************************************************
//	***						***
//	***						***
//	***						***
//	***						***
//	***						***
//	***			SH2側のｿﾌﾄ		***
//	***			推定速度		***
//	***						***
//	***						***
//	***						***
//	***						***
//	***						***
//	***						***
//	***************************************************
//	連続
//	安全一行程
//
void Calc1CycleSpmMake(void){
	S2b step_max,ret2b,data_cnt,i,dim_max;
	U4b wk4b1,wk4b2,total_tim;
	S2b Ta_max,ta,stop_flg,dirct_flg,last_cnt_flg;
	S4b xtim[20+20];//+20(2004-01-26 add 20)
	S2b yLdig[20+20];//
	S2b st_dig;
	S2b Vmax;
	S2b v_s,v_x,v_e,w_t;
	S2b obj_Ldig,length;

	Ta_max=SET1_ACCLAT_TIM1/10;//1msec==>10msec

	if(Ta_max==0){
		Ta_max=1;
	}

	dim_max=SET1_MTSTEP_MAXM;
	step_max=SET1_MTSTEP_MAXM+1;
	if(SET1_INCPLS_HOSN){
		wk4b1=SET1_MOTRPM_MAXM*SETY_INCPLS_HOSM01X;//SET1_INCPLS_HOSM;
		wk4b1=wk4b1/SET1_INCPLS_HOSN/(60*10);//2000.0rpm/60.0*360.0
		Vmax=wk4b1;//0.1dig/s
	}else{
		Vmax=1;//***.*度/sec
	}

	if((step_max<0) || ((10+1)<step_max) ){//step_maxは保証されているからﾘﾐｯﾄは不要
		data_cnt=2;//x,y座標ﾃﾞｰﾀ数
		step_max=1;
	}else{
		//時間の算出
		//開始ﾎﾟｲﾝﾄ
		data_cnt=1;//x,y座標ﾃﾞｰﾀ数
		xtim[0]=0;
		yLdig[0]=SETX_UPAREA_DIG;//ﾘﾝｸ角度
		i=1;
		v_x=0;//top速度
		v_s=0;//start速度
		v_e=0;//end速度
		last_cnt_flg=0;
		dirct_flg=0;//正転より開始
		stop_flg=1;//前回停止
		total_tim=0;
		//mode
		if(MODE_SEL&cBIT3){//連続
			if(SET1_MRTION_SEL1&cBIT0){//回転
				if(SVP_UPAREA_TIM0==0){//待機点停止なし
					v_s=SVP_OBJECT_SPD_TOP[step_max-1]*Vmax/1000;//100.0% 1段目
					v_x=v_s;
					v_e=v_s;
					stop_flg=0;//前回停止なし
				}
			}
		}
	
		//
		while(i <= step_max){
			if(i!=step_max){//1,2,,,,,
				if(stop_flg){
					v_s=0;//前回停止
				}else{
					v_s=v_x;//開始速度
				}
				v_x=SVP_OBJECT_SPD_TOP[i-1]*Vmax/1000;//100.0%　目標速度
				v_e=0;
				w_t=SVP_OBJECT_TIM_TOP[i-1];
				st_dig=yLdig[data_cnt-1];
				obj_Ldig=SET1_OBJECT_DIG_TOP[i-1];
				if(w_t==0){
					v_e=v_x;
					stop_flg=0;//non stop
				}else{
					stop_flg=1;//stop
				}
			}else{//max
				if(stop_flg){
					v_s=0;//前回停止
				}else{
					v_s=v_x;
				}
				v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1段目
				v_e=0;//連続のnonstop以外は0で終わる
				w_t=SVP_UPAREA_TIM0;
				if(MODE_SEL&cBIT3){//連続
					if(SET1_MRTION_SEL1&cBIT0){//回転
						if(w_t==0){
							v_e=v_x;
						}
					}
				}
				st_dig=yLdig[data_cnt-1];
				if(SET1_MRTION_SEL1&cBIT0){//回転
					obj_Ldig=SETX_UPAREA_DIG;//ﾘﾝｸ角度
					last_cnt_flg=1;
				}else{
					obj_Ldig=SETX_UPAREA_DIG;//ﾘﾝｸ角度
				}
			}
			
			length=mot_length_make1(obj_Ldig,st_dig,last_cnt_flg);//符号付
			if(length<0){
				if(dirct_flg==0){//前は正転
					v_s=0;
				}
				dirct_flg=1;//逆転
				length=length*-1;
			}else{
				if(dirct_flg!=0){//前は逆転
					v_s=0;
				}
				dirct_flg=0;//正転
			}
			//通常の計算
			wk4b1=tim_calc_up_dn(length,v_s,v_x,v_e,Ta_max,Vmax);
			wk4b2=0;
			xtim[data_cnt]=wk4b1-wk4b2;
			total_tim=total_tim+wk4b1-wk4b2;
			yLdig[data_cnt]=obj_Ldig;
			data_cnt++;
			if(w_t!=0){
				xtim[data_cnt]=w_t;
				total_tim=total_tim+(U4b)w_t;
				yLdig[data_cnt]=obj_Ldig;
				data_cnt++;
			}
			i++;
		}

	//	***************************
	//	***	ﾀｲﾑ積算		***
	//	***************************
		i=0;
		wk4b1=0;
		while(i<data_cnt){
			wk4b1=wk4b1+(S4b)xtim[i];
			i++;
		}
		
		if(wk4b1!=0){
			PVP_1ROT_CALSPM=(60*100)/wk4b1	;//予想運転速度 wk4b1*10msec:1rot 6000
		}
		
	}

}

