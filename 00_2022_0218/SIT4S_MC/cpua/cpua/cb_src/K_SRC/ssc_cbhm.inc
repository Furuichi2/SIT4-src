
//	***********************************
//	***				***
//	***	��ʃf�[�^		***
//	***	0.1�p�x��0.001mm�ϊ�	***
//	***				***
//	***********************************
//	���e
//	Input	mem1 +/- 0~360.0�x
//	Output  mem2 +/- 999.999mm

	extern	S4b	SVP_RNA_STLORK;
	extern	S4b	DISP_SV_MM_DAT;
	extern	S4b	DISP_SV_DG_DAT;	
	extern	U2b	PVP_1ROT_CALSPM	;//�\�z�^�]���x

	extern	C_ASM_CHG_ROOT(void);
	extern	void Calc1CycleSpmMake(void);

S4b DigRnaChange1(S2b digdt){
	S4b ret4b;

	if(digdt<3599){
		DISP_SV_DG_DAT=digdt;//0.1�x
		C_ASM_DISP_DG_CHG_MM();
		ret4b=DISP_SV_MM_DAT;//0.001mm
	}else{
		ret4b=0;// DaTa ERR
	}
	return(ret4b);	//100.000mm
}


//	***********************************
//	***				***
//	***	��ʃf�[�^		***
//	***	0.001mm->0.1�x�ϊ�	***
//	***				***
//	***********************************
//	���e
//	Input	�O��܂�mem1 +/- 0~360.0�x,mem2 +/- 999.999mm
//	Output  �����0~360.0�x

S2b RnaDigChange1(S2b old_digdt,S4b renea_pos){
	S4b wk4b1;
	S2b	ret2b;
	DISP_SV_DG_DAT=(S4b)old_digdt;//0.1�x
	DISP_SV_MM_DAT=renea_pos;//0.001mm data
	C_ASM_DISP_MM_CHG_DG();
	wk4b1=DISP_SV_DG_DAT;//0.1�x
	
	if(3599<wk4b1){//2007-01-11
		wk4b1=0;
	}
	ret2b=(S2b)wk4b1;
	return(ret2b);	//100.000mm
	
}

//	***********************************
//	***				***
//	***	��ʃf�[�^		***
//	***	�p�x��mm�ϊ��T���v��	***
//	***				***
//	***********************************
void smp1_test(void){
	S4b wk;
	wk=DigRnaChange1(300);// 30.0�x�̈Ӗ�
	
}

void smp3_test(void){
	S2b wk;
	wk=RnaDigChange1(400,50000);//�O��p�x=40.0�x ����ݒ�=50.000mm
	
}



//	***********************************************************
//	***							***
//	***	�ݒ�|�T�C�N�����ԁE�ڕW�ʒu�O���t		***
//	***	x,y-DOT						***
//	***							***
//	***********************************************************
//	Input
//	S2b *xdot  	�w���W�i�[���ڽ
//	S2b *ydot  	�x���W�i�[���ڽ
//	S2b *cnt	�ް������ڽ (����)
//	S2b *point	X,Y�i�[���ڽ��TOP������
//	S2b *chkflg	���Z���ʁ@�ް��L���A�n�_�A�I�_���
//
//10�i�d�l�̏ꍇ
//POS1,TIM1*10=20+10+3=>33
//[30]==>40���K�v
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
//	***		�`��\�t�g�쐬��		***
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
//	 �n�_(x,y)
//	|(0sec,0�x)
//	|p0(0,y0)
//	| +
//	|  + p1(x1,y1),t1
//	|   +------
//	|
//	|
//	|
//	|
//	|
//	|(0sec,180�x)
//	+------------------------------------------->(����)
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
//        dig(�ݸ��]�p)
//
//    (x0,y0)    v1    (x1,y1)t1 
//      V[rpm]/60
//
//   N��]��M�x���삷��
//
//    dig
//
//	[1] ��ݸ�ݒ�A->�ݸ�p�xa
//	    ��ݸ�ݒ�B->�ݸ�p�xb
//	�ݸ���쑬�x=2000.0rpm/60*M/N
//	(b-a)/V=t
//	��������V*T/Vmax���x�ɂ��Ă�����
//	10msec�P�ʂōl����
//
// XdotMax=
// YdotMax=
//
//	��{��  t=s/v		  :step 
//
//		t= (s-ta*v)/v+2ta :��`
//		
//		t= (s-ta*v/2)/v+ta :�Б���` 
//
	extern	U2b SET1_MRTION_SEL1;//.SRES	2	;��]����
	extern	U2b SET1_MTSTEP_MAXM;//.SRES	2	;�i��
	extern	U2b MODE_SEL;
	extern	U2b SET1_OBJECT_TIM_TOP;//
	extern	U2b SET1_INCPLS_HOSN;//PG�␳N�@Ӱ�N�� 1rpm�P��
//	extern	U2b SET1_INCPLS_HOSM;//PG�␳M�@��ݸ�p�xM
	extern	U4b SETY_INCPLS_HOSM01X;//0.1�x
	extern	U2b SET1_MOTRPM_MAXM;//Ӱ��ő��]��
	extern	U2b SET1_ACCLAT_TIM1;//����������
	extern	U2b SVP_OBJECT_TIM_TOP[20]	;//01�i�ڒ�~����
	extern	U2b SVP_OBJECT_SPD_TOP[20]	;//
	extern	U4b SVP_OBJECT_POS_TOP[20]	;//01�i�ږڕW�ʒu
	extern	U2b SVP_OBJECT_DIG_TOP[20]	;//01�i�ڊp�x�ʒu(��ݸ)
	extern	U2b SET1_OBJECT_DIG_TOP[40]	;//01�i�ڊp�x�ʒu(�ݸ)
	extern	U4b	SVP_UPAREA_POS0		;//�ҋ@�_�ʒu
	extern	U2b	SVP_UPAREA_DIG0		;//�ҋ@�_�p�x
	extern	U2b	SVP_UPAREA_SPD0		;//����x
	extern	U2b	SVP_UPAREA_TIM0		;//�ҋ@����
	extern	U2b	SETX_UPAREA_DIG;

	extern	S2b mot_length_make1(S2b obj_Ldig,S2b st_dig,S2b last_cnt_flg);//�����t
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
	S2b yLdig[20+20],yCdig[20+20];//yVCdig<��ݸ> (2004-01-26 add 20)
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
		Vmax=1;//***.*�x/sec
	}

//2004-01-26	if((step_max<0) || (6<step_max) ){
	if((step_max<0) || ((10+1)<step_max) ){//step_max�͕ۏ؂���Ă��邩���ЯĂ͕s�v
		data_cnt=2;//x,y���W�ް���
		xdot[0]=0;//�ް��ُ�
		ydot[0]=0;//�ް��ُ�
		xdot[1]=1;//�ް��ُ�
		ydot[1]=1;//�ް��ُ�
		step_max=1;
	}else{
		//���Ԃ̎Z�o
		//�J�n�߲��

		data_cnt=1;//x,y���W�ް���
		xtim[0]=0;
		yLdig[0]=SETX_UPAREA_DIG;//�ݸ�p�x
		if(SET1_MRTION_SEL1&cBIT0){//��]
			yCdig[0]=0;//
		}else{
			yCdig[0]=SVP_UPAREA_DIG0;//��ݸ�p�x
		}

		i=1;
		v_x=0;
		v_s=0;
		v_e=0;
		last_cnt_flg=0;
		dirct_flg=0;//���]���J�n
		stop_flg=1;//�O���~
		total_tim=0;
		while(i <= step_max){
			if(i==step_max){
				v_s=v_x;
				//v_x=SVP_UPAREA_SPD0;
				v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1�i��
				
				v_e=0;
				w_t=SVP_UPAREA_TIM0;
				if(stop_flg){
					v_s=0;//�O���~
				}
				
				if(MODE_SEL&cBIT3){//�A��
					if(SET1_MRTION_SEL1&cBIT0){//��]
						if(w_t==0){
							v_e=SVP_OBJECT_SPD_TOP[0]*Vmax/1000;//100.0% 1�i��
						}
					}
				}
				st_dig=yLdig[data_cnt-1];
				if(SET1_MRTION_SEL1&cBIT0){//��]
					obj_Ldig=SETX_UPAREA_DIG;//�ݸ�p�x
					obj_Cdig=0;//��ݸ=0
					last_cnt_flg=1;
				}else{
					obj_Ldig=SETX_UPAREA_DIG;//�ݸ�p�x
					obj_Cdig=SVP_UPAREA_DIG0;//��ݸ�p�x
				}
				
			}else{
				v_s=v_x;//�J�n���x
				v_x=SVP_OBJECT_SPD_TOP[i-1]*Vmax/1000;//100.0%�@�ڕW���x
				v_e=0;
				w_t=SVP_OBJECT_TIM_TOP[i-1];
				if(stop_flg){
					v_s=0;//�O���~
				}
				if(i==1){//1�i
					if(MODE_SEL&cBIT3){//�A��
						if(SET1_MRTION_SEL1&cBIT0){//��]
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
			
			length=mot_length_make1(obj_Ldig,st_dig,last_cnt_flg);//�����t
			if(length<0){
				if(dirct_flg==0){//�O�͐��]
					v_s=0;
				}
				dirct_flg=1;//�t�]
				length=length*-1;
			}else{
				if(dirct_flg!=0){//�O�͋t�]
					v_s=0;
				}
				dirct_flg=0;//���]
			}
			wkflg1=0;
			//�������180�x(�ݸ���ݸ��180�x�͓���)�ʉ߉��Z�������
			if(i==1){
				wkflg2=0;//�J�n�͉��~
			}else{
				wkflg2=area1800chg(st_dig);
			}
			if(dirct_flg==0){//���]
				if(!wkflg2){//���~
					wkflg2=area1800chg(obj_Ldig);//0:���]
					if(wkflg2){//����㏸
						wkflg1=1;
					}
				}
			}else{//�t�]
				if(wkflg2){//�㏸
					wkflg2=area1800chg(obj_Ldig);//
					if(!wkflg2){//���񉺍~
						wkflg1=1;
					}
				}
			}
			//�ʏ�̌v�Z
			wk4b1=tim_calc_up_dn(length,v_s,v_x,v_e,Ta_max,Vmax);
			wk4b2=0;
			if(wkflg1){//180�x���܂���
				length180=mot_length_make1(1800,st_dig,0);//�����t
				if(length180<0){
					length180= -1*length180;
				}
				//�Ƃ肠�����΍� �����\�t�g
				wk4b2=tim_calc_up_dn(length180,v_s,v_x,v_x,Ta_max,Vmax);
				//if(wk4b1<=wk4b2){//wk4b1�Ɠ������ʂɂȂ���
				//	wk4b2=wk4b2/2;//�����̓_�ɂ��Ă���
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
	//	***	�ޯĕϊ�	***
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
			yLdig[0]=SETX_UPAREA_DIG;//�ݸ�p�x
		
			i++;
		}
		ret2b=(cBIT2|cBIT1|cBIT0);//�ް��L��
	}

	*(point+0)=data_cnt-1;
	*(cnt+0)=data_cnt;
	*(chkflg+0)=ret2b;
	
	
	Calc1CycleSpmMake();//�\�zspm�\��
	
	return(ret2b);
}

//	v_x=v_s:�����オ��X�e�b�v
//	v_x=v_e:������X�e�b�v
//	v_x=v_s=v_e �����X�e�b�v
//	ans.10msec
//
//	���Ԃ�1:10MSEC
//	���x��0.1�x/SEC
//	�ʒu��0.1�x
//
//
typedef float 	dbl;		/*	s4b	*/

U4b tim_calc_up_dn(S2b length,S2b v_s,S2b v_x,S2b v_e,S2b Ta_max,S2b Vmax){
	S4b tx,delt_v,delt_ts,delt_ss,delt_te,delt_se,wk1,chk1,chk2;
	dbl dbtm1,dbtm2,dbA,dbB,dbC,dbwk1,dbwk2;
	
	if(v_x==0){
		tx=1;
	}else{
	//�����オ�莞�ԂƖʐ�
		delt_ts=((S4b)v_x-(S4b)v_s)*(S4b)Ta_max/(S4b)Vmax;	//v_s�J�n���x v_x�ڕW���x �J�n����ڕW�ɒB���鎞��(msec)
		if(delt_ts<0){
			delt_ts=delt_ts*-1;	//���~���͕�
		}
		delt_ss=((S4b)v_x+(S4b)v_s)*(S4b)delt_ts/2;	//ts�̑�`�̖ʐ� msec�Ȃ̂�1000���ꂽ����
		delt_ss=delt_ss/100;				//0.1�x�P�ʂɖ߂� 2004-05-26


	//���������莞�ԂƖʐ�(��~�^�C�v�̂ݔ����@�A����v_x=v_e)
		delt_te=((S4b)v_x-(S4b)v_e)*(S4b)Ta_max/(S4b)Vmax;
		if(delt_te<0){
			delt_te=delt_te*-1;
		}
		delt_se=((S4b)v_x+(S4b)v_e)*(S4b)delt_te/2;
		delt_se=delt_se/100				;//2004-05-26

//		tx=((S4b)length*100-(S4b)delt_ss-delt_se)/(S4b)v_x+delt_ts+delt_te;//
		tx=((S4b)length-(S4b)delt_ss-delt_se)*100/(S4b)v_x;//*100��0msec�P�ʂɂ���
		wk1=tx+delt_ts+delt_te;
		if(tx>0){
			tx=wk1;//�ʒu�~100�{�ň����Ă��邩�� �葬����������΂����ok
		}else{
//			tx=delt_ts;//�{���͖ʓ|�Ȏ� �����\�t�g
			dbA=(dbl)Vmax/(dbl)Ta_max;//10msec������̉�������
			if(v_s > v_x){
				dbA=dbA*(-1);
			}
			//	x=[-b�}sqrt(b*b-4ac)]/2a;
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


//;//�����t
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

	if(SET1_MRTION_SEL1&cBIT0){//��]
		if(obj_Ldig >= SETX_UPAREA_DIG){
			if(st_dig >= SETX_UPAREA_DIG){
				length=obj_Ldig-st_dig;
			}else{//�t�]
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
		//�����ł͉�]�Ɠ���
		if(obj_Ldig >= SETX_UPAREA_DIG){
			if(st_dig >= SETX_UPAREA_DIG){
				length=obj_Ldig-st_dig;
			}else{//�t�]
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

//	== ���� ===
//	Input �K�v�ƂȂ���
//	�H����
//	���x�A�ʒu�A����
//	�^�]���[�h�i�ҋ@�_�ƏI�_�j
//	�w���W�   500
//	�x���W� 10000
//	Output
//	X1,Y1,,,Xn,Yn�y�ь�
//	�n�_�����邩�ǂ���(�������ɂ͕K�v)FLG1
//	�I�_�����邩�ǂ���(�������ɂ͕K�v)FLG2
//	(�������ɂ͂������ق����ǂ�)
//
//
S2b SvStepXYDataMake2(S2b *xdot,S2b *ydot,S2b *cnt,S2b *point,S2b *chkflg){
	S2b ret2b,i;
	S2b step_no=4;//�{����ʐݒ�
	
	ret2b=0;	//�ް����� bit0=bit1=BIT2=0
			//	   BIT0=1�ް��L��
			//�n�_�L�� bit1=1�n�_�L��
			//�I�_�L�� bit2=1�I�_�L��
	i=1;
	while(i<step_no){
		*(xdot+(*point))=100*i;
		*(ydot+(*point))=1000*i;
		i++;
		*point++;
	}
	*cnt=i;//
	ret2b=(cBIT2|cBIT1|cBIT0);//�ް��L��


	*chkflg=ret2b;
	return(ret2b);
}


S2b area1800chg(S2b digdata){
	S2b ret2b;
	if(SETX_UPAREA_DIG > 1800){
		if(SETX_UPAREA_DIG < digdata){
				ret2b=0;//���~
		}else{
			if(digdata >= 1800){
				ret2b=1;//�㏸
			}else{
				ret2b=0;//���~
			}
		}
		
	}else{
		if((SETX_UPAREA_DIG<digdata) && (digdata<=1800)){
			ret2b=0;//���~
		}else{
			ret2b=1;//�㏸
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
//	***			SH2���̿��		***
//	***			���葬�x		***
//	***						***
//	***						***
//	***						***
//	***						***
//	***						***
//	***						***
//	***************************************************
//	�A��
//	���S��s��
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
		Vmax=1;//***.*�x/sec
	}

	if((step_max<0) || ((10+1)<step_max) ){//step_max�͕ۏ؂���Ă��邩���ЯĂ͕s�v
		data_cnt=2;//x,y���W�ް���
		step_max=1;
	}else{
		//���Ԃ̎Z�o
		//�J�n�߲��
		data_cnt=1;//x,y���W�ް���
		xtim[0]=0;
		yLdig[0]=SETX_UPAREA_DIG;//�ݸ�p�x
		i=1;
		v_x=0;//top���x
		v_s=0;//start���x
		v_e=0;//end���x
		last_cnt_flg=0;
		dirct_flg=0;//���]���J�n
		stop_flg=1;//�O���~
		total_tim=0;
		//mode
		if(MODE_SEL&cBIT3){//�A��
			if(SET1_MRTION_SEL1&cBIT0){//��]
				if(SVP_UPAREA_TIM0==0){//�ҋ@�_��~�Ȃ�
					v_s=SVP_OBJECT_SPD_TOP[step_max-1]*Vmax/1000;//100.0% 1�i��
					v_x=v_s;
					v_e=v_s;
					stop_flg=0;//�O���~�Ȃ�
				}
			}
		}
	
		//
		while(i <= step_max){
			if(i!=step_max){//1,2,,,,,
				if(stop_flg){
					v_s=0;//�O���~
				}else{
					v_s=v_x;//�J�n���x
				}
				v_x=SVP_OBJECT_SPD_TOP[i-1]*Vmax/1000;//100.0%�@�ڕW���x
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
					v_s=0;//�O���~
				}else{
					v_s=v_x;
				}
				v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1�i��
				v_e=0;//�A����nonstop�ȊO��0�ŏI���
				w_t=SVP_UPAREA_TIM0;
				if(MODE_SEL&cBIT3){//�A��
					if(SET1_MRTION_SEL1&cBIT0){//��]
						if(w_t==0){
							v_e=v_x;
						}
					}
				}
				st_dig=yLdig[data_cnt-1];
				if(SET1_MRTION_SEL1&cBIT0){//��]
					obj_Ldig=SETX_UPAREA_DIG;//�ݸ�p�x
					last_cnt_flg=1;
				}else{
					obj_Ldig=SETX_UPAREA_DIG;//�ݸ�p�x
				}
			}
			
			length=mot_length_make1(obj_Ldig,st_dig,last_cnt_flg);//�����t
			if(length<0){
				if(dirct_flg==0){//�O�͐��]
					v_s=0;
				}
				dirct_flg=1;//�t�]
				length=length*-1;
			}else{
				if(dirct_flg!=0){//�O�͋t�]
					v_s=0;
				}
				dirct_flg=0;//���]
			}
			//�ʏ�̌v�Z
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
	//	***	��ѐώZ		***
	//	***************************
		i=0;
		wk4b1=0;
		while(i<data_cnt){
			wk4b1=wk4b1+(S4b)xtim[i];
			i++;
		}
		
		if(wk4b1!=0){
			PVP_1ROT_CALSPM=(60*100)/wk4b1	;//�\�z�^�]���x wk4b1*10msec:1rot 6000
		}
		
	}

}
