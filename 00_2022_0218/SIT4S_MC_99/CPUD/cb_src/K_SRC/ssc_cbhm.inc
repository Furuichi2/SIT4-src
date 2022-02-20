//	*******************************************
//	***					***
//	***	HMI���ւ̒񋟂���֐�		***
//	***					***
//	*******************************************



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
//	***						***
//	***						***
//	***		�`��\�t�g			***
//	***						***
//	***						***
//	***						***
//	***************************************************
#include	"ssc_def.h" 

//#define		SYSPOS_STEP_MAX	98		//2015-11-20 �ǉ� 98�i+1�i(��)=99�iMAX

//	-------------- HMI�������Ȑݒ�l---------------
extern	UNl		SV_TAIKIPOS_SRV;            // �ҋ@�ʒu        �ݒ�50.00mm->����50000(50.000mm)
//extern	UNs		SV_KAITEN_SRV;              // ��]���� 
extern	UNs		SV_DANSUU_SRV;              // �i�� 
extern	UNs		SV_TAIKIKAKU_SRV;           // �ҋ@�p 
extern	UNs		SV_TAIKSPD_SRV;             // ����x(�ߑ��x) 50.0%->����500(50.0%)
extern	UNs		SV_TAIKTIM_SRV;             // �ҋ@�_��~����   20.0S->����200(20.0S)

extern	UNs		SV_1DANDEG_SRV;             // 1�i�ږڕW�p�x*98 50�x->����500(50.0�x)
//extern	UNl		SV_1DANPOS_SRV;             // 1�i�ږڕW�ʒu*98 41.07mm->����41070(41.070mm)
extern	UNs		SV_1DANSPD_SRV;             // 1�i�ڈړ����x*98 50.0%->����500(50.0%)
extern	UNs		SV_1DANTIM_SRV;             // 1�i�ڒ�~����*98 10.0s->����100(10.0S)


//	--------------CPUA�Ƃ�DPRAM�� --------------


//	------------- �����Ȑݒ�,�T�[�{�p��--------------
extern	U2b		SV_ACCLAT__TIM1;	//������
extern	U2b		SV_INCPLS_HOSN;		//�␳n
extern	U2b		SV_INCPLS_HOSM;		//��ݸ�pM
extern	U2b		SV_MOTRPM_MAXM;		//Ӱ��ő��]��

//	------------- ROM���Ұ�-----------------
extern	U2b		GMN_PAR085;
extern	U2b		CB_SYS_PARAM044;	//PAR_CLINK_LINK
//	------------- ���ݽ(�A��,�A���ȊO)------
extern	S2b		SEQ_PAR_200;//�^�] �A��(BIT3=1)
extern	S2b		SEQ_PAR_050;//����(BIT0(��]),BIT1(���]),BIT2(�U�q))

//	----------- �����֐�---------------
extern	U2b CdigToLdigChange(U2b cdig);


//	***************************************************
//	***						***
//	***		�`��\�t�g�쐬��		***
//	***						***
//	***************************************************
//	�A��<=>����
//	��]<=>���] :�U�q���Ȃ� 
//
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

//	extern	U4b	SVP_UPAREA_POS0		;//�ҋ@�_�ʒu

	extern	U2b	SVP_UPAREA_DIG0		;//�ҋ@�_�p�x
	extern	U2b	SVP_UPAREA_SPD0		;//����x
	extern	U2b	SVP_UPAREA_TIM0		;//�ҋ@����


	extern	S2b mot_length_make1(S2b obj_Ldig,S2b st_dig,S2b last_cnt_flg);//�����t
	extern	U4b tim_calc_up_dn(S2b length,S2b v_s,S2b v_x,S2b v_e,S2b Ta_max,S2b Vmax);
	extern	S2b area1800chg(S2b digdata);//

//	�X�^�b�N������Ȃ����߃O���[�o���ց@2015-11-20
	S4b xtim[200+20];//+20(2004-01-26 add 20)
	S2b yLdig[200+20];//
	S2b yCdig[200+20];//

S2b SvStepXYDataMake1(S2b *xdot,S2b *ydot,S2b *cnt,S2b *point,S2b *chkflg){
	U2b step_sys_max;//2015-11-20
	U2b *sv_ObjTim;//2015-11-20
	U2b *sv_ObjSpd;//2015-11-20
	U2b *sv_ObjCdig;//2015-11-20
	U2b LinkTaikiten;

	S2b XdotMax;
	S2b YdotMax;


	S2b step_max,ret2b,data_cnt,i,dim_max;
	S2b Vmax;
	U4b wk4b1,wk4b2,total_tim;
	S2b Ta_max,ta,stop_flg,dirct_flg,last_cnt_flg;
//2015-11-20	S4b xtim[200+20];//
//2015-11-20	S2b yLdig[200+20],yCdig[200+20];//
	S2b v_s,v_x,v_e,w_t;
	S2b st_dig,obj_Ldig,obj_Cdig,length,length180,wkflg1,wkflg2;
	
	ret2b=0;
	XdotMax=500;
	YdotMax=500;

	// 2015-11-20
	sv_ObjTim=&SV_1DANTIM_SRV;//SVP_OBJECT_TIM_TOP 0.01
	sv_ObjSpd=&SV_1DANSPD_SRV;//SVP_OBJECT_SPD_TOP
	sv_ObjCdig=&SV_1DANDEG_SRV;//��ݸ�p�x

	//2015-11-20
	if(GMN_PAR085){
		if(GMN_PAR085<=SYSPOS_STEP_MAX){
			step_sys_max=GMN_PAR085;
		}else{
			step_sys_max=SYSPOS_STEP_MAX;
		}
	}else{
		step_sys_max=10;
	}
	
	dim_max=SV_DANSUU_SRV;//2015-11-20 SET1_MTSTEP_MAXM;
	if((dim_max==0)||(step_sys_max<dim_max)){//0,�܂��͔͈͊O�Ȃ�s��=1
		dim_max=1;
	}
	step_max=dim_max+1;

	Ta_max=SV_ACCLAT__TIM1/10;//1msec==>10msec
	Ta_max=1;//���Ԃ̑΂���X���C�h�ʒu��������������Ԃ𖳎����Ă��قړ����G�ɂȂ�
	
	if(Ta_max==0){
		Ta_max=1;
	}

//2015-11-20
//	if(SET1_INCPLS_HOSN){
//		wk4b1=SET1_MOTRPM_MAXM*SETY_INCPLS_HOSM01X;//SET1_INCPLS_HOSM;
//		wk4b1=wk4b1/SET1_INCPLS_HOSN/(60*10);//2000.0rpm/60.0*360.0
//		Vmax=wk4b1;
//	}else{
//		Vmax=1;//***.*�x/sec
//	}
//
	if(SV_INCPLS_HOSN){
		wk4b1=(SV_MOTRPM_MAXM)*(SV_INCPLS_HOSM*10);//2000.0rpm*360.0
		wk4b2=SV_INCPLS_HOSN*60*10;
		wk4b1=wk4b1/wk4b2;// xxx.x�x
		Vmax=wk4b1;
		//2015-11-20 wk4b1=SET1_MOTRPM_MAXM*SETY_INCPLS_HOSM01X;//SET1_INCPLS_HOSM;
		//2015-11-20 wk4b1=wk4b1/SET1_INCPLS_HOSN/(60*10);//2000.0rpm/60.0*360.0
		//2015-11-20 Vmax=wk4b1;//0.1dig/s
	}else{
		Vmax=1;//***.*�x/sec
	}


	//���Ԃ̎Z�o
	//�J�n�߲��

	data_cnt=1;//x,y���W�ް���
	xtim[0]=0;
	
	//��]�ł����L�f�[�^�͕K�v�ȏꍇ�O�ɂȂ�̂Ń��[�h����s�v 2015-11-20
	yCdig[0]=SVP_UPAREA_DIG0;//��ݸ�p�x
	LinkTaikiten=CdigToLdigChange(yLdig[0]);//
	yLdig[0]=LinkTaikiten;

	//if(SEQ_PAR_050&cBIT0){//��]
	//	yCdig[0]=0;//
	//}else{
	//	yCdig[0]=SVP_UPAREA_DIG0;//��ݸ�p�x
	//}
	//yLdig[0]=SETX_UPAREA_DIG;//�ݸ�p�x

	i=1;
	v_x=0;
	v_s=0;
	v_e=0;
	last_cnt_flg=0;
	dirct_flg=0;//���]���J�n
	stop_flg=1;//�O���~
	total_tim=0;
	while(i <= step_max){
		if(i==step_max){//�߂�s��?
			v_s=v_x;
			v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1�i��
			
			v_e=0;
			w_t=SVP_UPAREA_TIM0*10;//10ms->100ms
			if(stop_flg){
				v_s=0;//�O���~
			}
			
			if(SEQ_PAR_200&cBIT3){//�A��
				if(SEQ_PAR_050&cBIT0){//��]
					if(w_t==0){
						v_e=sv_ObjSpd[0]*Vmax/1000;//100.0% 1�i��
					}
				}
			}
			st_dig=yLdig[data_cnt-1];

			//2015-11-20
			obj_Cdig=SVP_UPAREA_DIG0;//��ݸ�p�x
			obj_Ldig=CdigToLdigChange(obj_Cdig);//SETX_UPAREA_DIG;//�ݸ�p�x
			if(SEQ_PAR_050&cBIT0){//��]
				last_cnt_flg=1;
			}else{
				//2015-11-20
				//��]�łȂ���Δ��](�ҋ@�_�ɖ߂�)���U�q �װ
				//�U�q�Ή�:���܂ł͉�]�łȂ���Δ��](�ҋ@�_�ɖ߂��ďI���)
				if(SEQ_PAR_050&cBIT2){//�U�q
					if(SVP_UPAREA_DIG0<1800){
						obj_Cdig=3600-SVP_UPAREA_DIG0;//�װ��ݸ�p�x(180-sv+180 )
					}else{
						obj_Cdig=0;//���肦�Ȃ�
					}
					obj_Ldig=CdigToLdigChange(obj_Cdig);
				}
			}

			//2015-11-20	if(SEQ_PAR_050&cBIT0){//��]
			//2015-11-20	obj_Cdig=0;//��ݸ=0
			//2015-11-20	obj_Ldig=CdigToLdigChange(obj_Cdig);//SETX_UPAREA_DIG;//�ݸ�p�x
			//2015-11-20	last_cnt_flg=1;
			//2015-11-20}else{
			//2015-11-20	obj_Cdig=SVP_UPAREA_DIG0;//��ݸ�p�x
			//2015-11-20	obj_Ldig=CdigToLdigChange(obj_Cdig);//SETX_UPAREA_DIG;//�ݸ�p�x
			//2015-11-20}
			
		}else{
			v_s=v_x;//�J�n���x
			v_x=sv_ObjSpd[i-1]*Vmax/1000;//100.0%�@�ڕW���x
			v_e=0;
			w_t=sv_ObjTim[i-1]*10;//2015-11-20 0.1s->0.01s
			if(stop_flg){
				v_s=0;//�O���~
			}
			if(i==1){//1�i
				if(SEQ_PAR_200&cBIT3){//�A��
					if(SEQ_PAR_050&cBIT0){//��]
						if(SVP_UPAREA_TIM0==0){
							v_s=v_x;
						}
					}
				}
			}
			st_dig=yLdig[data_cnt-1];
			obj_Cdig=sv_ObjCdig[i-1];//SVP_OBJECT_DIG_TOP
			obj_Ldig=CdigToLdigChange(obj_Cdig);//SET1_OBJECT_DIG_TOP[i-1];
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
			ydot[i]=YdotMax-(1800-(3600-yCdig[i]))*YdotMax/1800;
		}else{
			ydot[i]=YdotMax-(1800-yCdig[i])*YdotMax/1800;
		}

		;
		yLdig[0]=LinkTaikiten;//	SETX_UPAREA_DIG;//�ݸ�p�x
	
		i++;
	}
	ret2b=(cBIT2|cBIT1|cBIT0);//�ް��L��
	

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

		tx=((S4b)length-(S4b)delt_ss-delt_se)*100/(S4b)v_x;//*100��0msec�P�ʂɂ���
		wk1=tx+delt_ts+delt_te;
		if(tx>0){
			tx=wk1;//�ʒu�~100�{�ň����Ă��邩�� �葬����������΂����ok
		}else{
	//		tx=delt_ts;//�{���͖ʓ|�Ȏ� �����\�t�g
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
	U2b LinkTaikiten;

	LinkTaikiten=CdigToLdigChange(SVP_UPAREA_DIG0);//��ݸ�p�x
	
	if(last_cnt_flg){
		if(st_dig >= LinkTaikiten){			//SETX_UPAREA_DIG
			length=3600-st_dig+LinkTaikiten;	//SETX_UPAREA_DIG;
		}else{
			length=LinkTaikiten-st_dig;		//SETX_UPAREA_DIG
		}
		goto exit;
		
	}

	if(SEQ_PAR_050&cBIT0){//��]
		if(obj_Ldig >= LinkTaikiten){//SETX_UPAREA_DIG
			if(st_dig >= LinkTaikiten){//SETX_UPAREA_DIG
				length=obj_Ldig-st_dig;
			}else{//�t�]
				length=-1*(3600-obj_Ldig+st_dig);
			}
		}else{
			if(st_dig >= LinkTaikiten){//SETX_UPAREA_DIG
				length=3600-st_dig+obj_Ldig;//
			}else{//
				length=obj_Ldig-st_dig;
			}
		}
	}else{
		//�����ł͉�]�Ɠ���
		if(obj_Ldig >= LinkTaikiten){//SETX_UPAREA_DIG
			if(st_dig >= LinkTaikiten){	//SETX_UPAREA_DIG
				length=obj_Ldig-st_dig;
			}else{//�t�]
				length=-1*(3600-obj_Ldig+st_dig);
			}
		}else{
			if(st_dig >= LinkTaikiten){	//SETX_UPAREA_DIG
				length=3600-st_dig+obj_Ldig;//
			}else{//
				length=obj_Ldig-st_dig;
			}
		}
	}
exit:;
	return(length);
	
}



S2b area1800chg(S2b digdata){
	S2b ret2b;
	U2b LinkTaikiten;
	LinkTaikiten=CdigToLdigChange(SVP_UPAREA_DIG0);//��ݸ�p�x
	
	if(LinkTaikiten > 1800){		//SETX_UPAREA_DIG
		if(LinkTaikiten < digdata){	//SETX_UPAREA_DIG
				ret2b=0;//���~
		}else{
			if(digdata >= 1800){
				ret2b=1;//�㏸
			}else{
				ret2b=0;//���~
			}
		}
		
	}else{
		if((LinkTaikiten<digdata) && (digdata<=1800)){	//SETX_UPAREA_DIG
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
//	�A��<=>���S��s��
//	��]<=>���]	(�ӂ肱���Ȃ�)
//	
void Calc1CycleSpmMake(void){
	U2b step_sys_max;//2015-11-20
	U2b *sv_ObjTim;//2015-11-20
	U2b *sv_ObjSpd;//2015-11-20
	U2b *sv_ObjCdig;//2015-11-20
	U2b LinkTaikiten;


	S2b step_max,ret2b,data_cnt,i,dim_max;
	U4b wk4b1,wk4b2,total_tim;
	S2b Ta_max,ta,stop_flg,dirct_flg,last_cnt_flg;
//	S4b xtim[200+20];//+20(2004-01-26 add 20)
//	S2b yLdig[200+20];//
	S2b st_dig;
	S2b Vmax;
	S2b v_s,v_x,v_e,w_t;
	S2b obj_Ldig,length;

	//2015-11-20
	sv_ObjTim=&SV_1DANTIM_SRV;//SVP_OBJECT_TIM_TOP 0.01
	sv_ObjSpd=&SV_1DANSPD_SRV;//SVP_OBJECT_SPD_TOP
	sv_ObjCdig=&SV_1DANDEG_SRV;//SVP_OBJECT_DIG_TOP�@��ݸ�p�x

	LinkTaikiten=CdigToLdigChange(SVP_UPAREA_DIG0);//��ݸ�p�x

	//2015-11-20
	if(GMN_PAR085){
		if(GMN_PAR085<=SYSPOS_STEP_MAX){
			step_sys_max=GMN_PAR085;
		}else{
			step_sys_max=SYSPOS_STEP_MAX;
		}
	}else{
		step_sys_max=10;
	}
	dim_max=SV_DANSUU_SRV;//2015-11-20 SET1_MTSTEP_MAXM;
	if((dim_max==0)||(step_sys_max<dim_max)){//0,�܂��͔͈͊O�Ȃ�s��=1
		dim_max=1;
	}
	step_max=dim_max+1;



	Ta_max=SV_ACCLAT__TIM1/10;//1msec==>10msec
	if(Ta_max==0){
		Ta_max=1;
	}

	if(SV_INCPLS_HOSN){
		wk4b1=(SV_MOTRPM_MAXM)*(SV_INCPLS_HOSM*10);//2000.0rpm*360.0
		wk4b2=SV_INCPLS_HOSN*60*10;
		wk4b1=wk4b1/wk4b2;// xxx.x�x
		Vmax=wk4b1;
	}else{
		Vmax=1;//***.*�x/sec
	}

	//���Ԃ̎Z�o
	//�J�n�߲��
	data_cnt=1;//x,y���W�ް���
	xtim[0]=0;
	yLdig[0]=LinkTaikiten;//SETX_UPAREA_DIG;//�ݸ�p�x
	i=1;
	v_x=0;//top���x
	v_s=0;//start���x
	v_e=0;//end���x
	last_cnt_flg=0;
	dirct_flg=0;//���]���J�n
	stop_flg=1;//�O���~
	total_tim=0;

	//��]�̘A�����[�h�̏㎀�_��~�^�C�}���������A�J�n���ɑ��x�����݂���
	if(SEQ_PAR_200&cBIT3){//�A��
		if(SEQ_PAR_050&cBIT0){//��]
			if(SVP_UPAREA_TIM0==0){//�ҋ@�_��~�Ȃ�
				v_s=sv_ObjSpd[step_max-1]*Vmax/1000;//100.0% 1�i��
				v_x=v_s;
				v_e=v_s;
				stop_flg=0;//�O���~�Ȃ�
			}
		}
	}
	
	//
	while(i <= step_max){
		if(i!=step_max){//�߂�s���ł͂Ȃ�:1,2,,,,,
			if(stop_flg){
				v_s=0;//�O���~
			}else{
				v_s=v_x;//�J�n���x
			}
			v_x=sv_ObjSpd[i-1]*Vmax/1000;//100.0%�@�ڕW���x
			v_e=0;
			w_t=sv_ObjTim[i-1]*10;//2015-11-20 0.1s->0.01s
			st_dig=yLdig[data_cnt-1];
			//2015-11-20 obj_Ldig=SET1_OBJECT_DIG_TOP[i-1];
			obj_Ldig=CdigToLdigChange(sv_ObjCdig[i-1]);//SVP_OBJECT_DIG_TOP
			
			if(w_t==0){
				v_e=v_x;
				stop_flg=0;//non stop
			}else{
				stop_flg=1;//stop
			}
		}else{//max:�߂�s���ł���
			if(stop_flg){
				v_s=0;//�O���~
			}else{
				v_s=v_x;
			}
			v_x=SVP_UPAREA_SPD0*Vmax/1000;//100.0% 1�i��
			v_e=0;//�A����nonstop�ȊO��0�ŏI���
			w_t=SVP_UPAREA_TIM0*10;//10ms->100ms

			if(SEQ_PAR_200&cBIT3){//�A��
				if(SEQ_PAR_050&cBIT0){//��]
					if(w_t==0){
						v_e=v_x;
					}
				}
			}
			st_dig=yLdig[data_cnt-1];
			obj_Ldig=LinkTaikiten;//SETX_UPAREA_DIG;//�ݸ�p�x[�߂�ʒu�͑ҋ@�_:���]�ɂȂ�]
			
			if(SEQ_PAR_050&cBIT0){//��]
				last_cnt_flg=1;//���̉�]�̑ҋ@�_�ɖڕW��ς���
			}else{	
			//2015-11-20
			//�U�q�Ή�:���܂ł͉�]�łȂ���Δ��](�ҋ@�_�ɖ߂��ďI���)
				if(SEQ_PAR_050&cBIT2){//�U�q
					if(SVP_UPAREA_DIG0<1800){
						wk4b1=3600-SVP_UPAREA_DIG0;//�װ��ݸ�p�x(180-sv+180 )
					}else{
						wk4b1=0;//���肦�Ȃ�
					}
					obj_Ldig=CdigToLdigChange(wk4b1);
				}
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



extern	U2b CLNK_SV_CHG_LINK_TBL_TOP[3600];

U2b CdigToLdigChange(U2b cdig){
	U2b ans;
	ans=cdig;
	if(CB_SYS_PARAM044!=1){
		ans=CLNK_SV_CHG_LINK_TBL_TOP[cdig+1];
	}
	return(ans);
}

