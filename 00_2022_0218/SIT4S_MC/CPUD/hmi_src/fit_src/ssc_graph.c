/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�O���t�`�揈��										*/
/*																			*/
/*						2002.07.31				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
#define		EXTRN		extern
#define		BYTE		unsigned char
#define		WORD		unsigned short
#define		DWORD		unsigned long

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include	"cm_equ1.h"		//MC�ɂĕ���

#include	"ssc_addr.h"
#include	"ssc_def.h"

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include	"dp_cpuab.h"

#include	"ssc_dpram_seq_ext.h"
#include	"ssc_fram_ext.h"
#include	"ssc_wk_ext.h"

// #define	DEBUG_1									/* ���ޯ��	����ٕ`��	*/
// #define	DEBUG_2									/* ���ޯ��	�����W�`��	*/
// #define	DEBUG_3									/* ���ޯ��	�����W�`��	*/

#define		ALL_DISP			0xFF				/* �S��ʕ\��			*/
#define		HALF_DISP			0x55				/* �E�B���h�E�\��		*/
#define		NO_DISP				0x00				/* �\�����Ȃ�			*/

#define		GRAPH_CLEAR_POS		0xA005				/* ���̕`��ر�ʒu���	*/
													/* 40BYTE,X=0���,Y=5���	*/
#define		GRAPH_CLM_TOP		  2					/* ���̕`��ō�����	*/
#define		GRAPH_CLM_MAX		 37					/* ���̕`��P�s�̶�ѐ�	*/
#define		GRAPH_LIN_TOP		  5					/* ���̕`��ŏ�s���	*/
#define		GRAPH_LIN_MAX		  6					/* ���̕`��ײݐ�(��� )	*/
#define		GRAPH_DOT_MAX		 94					/* ���̕`��ײݐ�(�ޯ�)	*/

#define		GRAPH_DOT_TOP		 81					/* �`��\�͈� �ޯ�	*/
#define		GRAPH_DOT_LEFT		 16					/* GRAPH_CLM_TOP * 8	*/
#define		GRAPH_DOT_BTM		174					/* DOT TOP + MAX - 1	*/
#define		GRAPH_DOT_RIGHT		304					/* CLM * 8				*/

#define		GRAPH_RATE			600					/* Y�����Z�E����\		*/
#define		GRAPH_RATE_HALF		(GRAPH_RATE / 2)	/* �l�̌ܓ��p			*/

// #define	GRAPH_POINT_MAX		 23					/* �ő���W��			*/
#define		GRAPH_POINT_MAX		 46					/* �ő���W��			*/

#define		GRAPH_X_RATE1		 72					/* �ޯčő�l	288 / 4	*/
#define		GRAPH_X_RATE2		125					/* ���̍ő�l	500 / 4	*/
#define		GRAPH_Y_RATE1		 93					/* �ޯčő�l	-1		*/
#define		GRAPH_Y_RATE2		500					/* ���̍ő�l			*/

/* �O���ϐ� */
WORD		BT[ 8 ];								/* �ޯ��ް�				*/
WORD		OT[ GRAPH_POINT_MAX ][ 2 ];				/* X-Y ���W�Q �O��l	*/
WORD		PT[ GRAPH_POINT_MAX ][ 2 ];				/* X-Y ���W�Q			*/
WORD		GT[ GRAPH_DOT_MAX   ][ GRAPH_CLM_MAX ];	/* �����ް��̈�			*/

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];


/* �v���g�^�C�v */
void		GRAPH_DOT_SET	(WORD,WORD,WORD,WORD);	/* �ޯ��ް����			*/

/****************************************************************************/
/*																			*/
/*	�O���t�`�揉������		�F	�O���t�`��̏����ݒ菈�����s���B			*/
/*																			*/
/*		GRAPH_DISP_FLG		�F	�O���t�`��t���O							*/
/*																			*/
/****************************************************************************/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void	GRAPH_INIT	(void)
{
	WORD	i,	t;
	WORD	pos;
	WORD	nop	[ 40 ];
	WORD	lin	[ 40 ];

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* �O���t�`�悵�Ȃ�		*/

	for (i=0; i<40; i++)		nop[i] = 0x2020;	/* NOP �ް��쐬			*/
	for (i=0; i<40; i++)		lin[i] = 0xFFFF;	/* LINE �ް��쐬		*/

	pos = GRAPH_CLEAR_POS;							/* ���̕`��ʒu���		*/
	i	= 0;										/*						*/

CLEAR_LOOP:											/* ����޳�����ر LOOP	*/
	Disp_moji(pos,nop,0);							/* LCD������\���E����	*/
	pos ++;											/* �s��шʒu�X�V		*/
	i	++;											/* �����				*/
	if (i < GRAPH_LIN_MAX)		goto  CLEAR_LOOP;	/* 						*/

	lin[ 0] = 0xFF00;								/* �O�g�`��				*/
	lin[ 1] = 0xFF01;								/*						*/
	lin[38] = 0xFFC0;								/*						*/
	lin[39] = 0xFF00;								/*						*/
	Lcd_draw (0,0,GRAPH_DOT_TOP-1,40,lin);			/*						*/
	Lcd_draw (0,0,GRAPH_DOT_BTM+1,40,lin);			/*						*/
	lin[38] = 0xFF40;								/*						*/
	for (i=GRAPH_DOT_TOP;i<=GRAPH_DOT_BTM;i++){		/*						*/
		Lcd_draw (0, 1,i,1,&lin[ 1]);				/* ���g					*/
		Lcd_draw (0,38,i,1,&lin[38]);				/* �E�g					*/
	}												/*						*/

	lin[0] = 0xFF40;								/* ���g�`��				*/
	lin[1] = 0xFF10;								/* �P�_����				*/
	lin[2] = 0xFF08;								/*						*/
	lin[3] = 0xFF02;								/*						*/
	for (i=GRAPH_DOT_TOP+1;i<=GRAPH_DOT_BTM;i+=2){	/*						*/
		Lcd_draw (0, 9,i,1,&lin[0]);				/*						*/
		Lcd_draw (0,16,i,1,&lin[1]);				/*						*/
		Lcd_draw (0,23,i,1,&lin[2]);				/*						*/
		Lcd_draw (0,30,i,1,&lin[3]);				/*						*/
	}												/*						*/

	for (t=0; t<GRAPH_DOT_MAX; t++){				/* �����ް��ر			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ر		*/
		OT[i][0] = 0xFFFF;							/* X					*/
		OT[i][1] = 0xFFFF;							/* Y					*/
		PT[i][0] = 0;								/* X					*/
		PT[i][1] = 0;								/* Y					*/
	}												/*						*/

	for (t=0x0080,i=0; i<8; i++){					/* �ޯ��ް��쐬			*/
		BT[i] = (0xFF00 | t);						/*						*/
		t = (t >> 1);								/*						*/
	}												/*						*/
}
#else

#define		GRAPH_XDOT_LEG		500
#define		GRAPH_YDOT_LEG		190//200

#define		GRAPH_XDOT_BGN1		70				
#define		GRAPH_XDOT_BGN2		GRAPH_XDOT_BGN1 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN3		GRAPH_XDOT_BGN2 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN4		GRAPH_XDOT_BGN3 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN5		GRAPH_XDOT_BGN4 + (GRAPH_XDOT_LEG/5)
#define		GRAPH_XDOT_BGN6		GRAPH_XDOT_BGN1 + GRAPH_XDOT_LEG
#define		GRAPH_YDOT_BGN1		160				
#define		GRAPH_YDOT_BGN2		GRAPH_YDOT_BGN1 + GRAPH_YDOT_LEG

void	GRAPH_INIT	(void)
{
	UNs		xpos, ypos;
	short	cnt;
	WORD	i,	t;

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_XDOT_LEG;
	for ( ; 0<cnt; cnt--, xpos++) {					//���ド�C���쐬
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN2;
	cnt = GRAPH_XDOT_LEG;
	for ( ; 0<cnt; cnt--, xpos++) {					//�������C���쐬
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN1;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt--, ypos++) {					//��ԍ��c���C���쐬�i���O�g�j
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN6;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt--, ypos++) {					//��ԉE���C���쐬�i�E�O�g�j
		LCD_VRAM[ypos][xpos] = 0;
	}

	xpos = GRAPH_XDOT_BGN2;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//������Q�Ԗڃ��C���쐬
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN3;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//������R�Ԗڃ��C���쐬
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN4;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//������S�Ԗڃ��C���쐬
		LCD_VRAM[ypos][xpos] = 1;
	}

	xpos = GRAPH_XDOT_BGN5;
	ypos = GRAPH_YDOT_BGN1;
	cnt = GRAPH_YDOT_LEG;
	for ( ; 0<cnt; cnt-=2, ypos+=2) {				//������T�Ԗڃ��C���쐬
		LCD_VRAM[ypos][xpos] = 1;
	}

	for (t=0; t<GRAPH_DOT_MAX; t++){				/* �����ް��ر			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ر		*/
		OT[i][0] = 0xFFFF;							/* X					*/
		OT[i][1] = 0xFFFF;							/* Y					*/
		PT[i][0] = 0;								/* X					*/
		PT[i][1] = 0;								/* Y					*/
	}												/*						*/
}
#endif




#if ( SIT_TYPE_SEL == TYPE_SIT3 )	//--------------------------------------------------------------------------------------------

/****************************************************************************/
/*																			*/
/*	�O���t�`�揈��			�F	�O���t��`�悷��B							*/
/*																			*/
/*		GRAPH_DISP_FLG		�F	�O���t�`��t���O							*/
/*																			*/
/****************************************************************************/
void	GRAPH_DISP	(void)
{
	WORD	i,	t;
	WORD	x1,	x2,	y1,	y2;
	WORD	ret;
	WORD	XT [ GRAPH_POINT_MAX ];
	WORD	YT [ GRAPH_POINT_MAX ];
	WORD	CT,	ST,	FL;

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* �O���t�`�悵�Ȃ�		*/

#ifdef	DEBUG_1
	CT	=  0;
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;		/* ������ް� ���W		*/
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;		/* X = 16 �` 304		*/
	PT[CT][0]	=  17;		PT[CT++][1]	= 173;		/* Y = 81 �` 174		*/
	PT[CT][0]	=  17;		PT[CT++][1]	= 173;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	PT[CT][0]	=  17;		PT[CT++][1]	=  82;
	PT[CT][0]	=  17;		PT[CT++][1]	= 112;
	PT[CT][0]	=  47;		PT[CT++][1]	= 112;
	PT[CT][0]	=  77;		PT[CT++][1]	= 142;
	PT[CT][0]	=  77;		PT[CT++][1]	= 173;
	PT[CT][0]	= 168;		PT[CT++][1]	=  82;
	PT[CT][0]	= 169;		PT[CT++][1]	= 173;
	PT[CT][0]	= 200;		PT[CT++][1]	= 173;
	PT[CT][0]	= 201;		PT[CT++][1]	=  82;
	PT[CT][0]	= 231;		PT[CT++][1]	= 112;
	PT[CT][0]	= 261;		PT[CT++][1]	= 113;
	PT[CT][0]	= 261;		PT[CT++][1]	= 153;
	PT[CT][0]	= 291;		PT[CT++][1]	= 152;
	PT[CT][0]	= 303;		PT[CT++][1]	=  82;
	PT[CT][0]	= 303;		PT[CT++][1]	= 173;
	goto	DISP_CHECK;
#endif

	ST	= 0;										/*						*/
	ret = SvStepXYDataMake1 (XT,YT,&CT,&ST,&FL);	/* ���W�ݒ�֐�			*/

#ifdef	DEBUG_2
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

#ifdef	DEBUG_3
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 500;
	XT[CT] = 200;		YT[CT++] =   0;
	XT[CT] = 300;		YT[CT++] = 500;
	XT[CT] = 400;		YT[CT++] =   0;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

	if ( FL == 0)						return;		/* �L����-��Ȃ�			*/
	if ((CT <= 0)||(CT > GRAPH_POINT_MAX))			/* �L���ް��� NG		*/
										return;		/*						*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* �����ް���߰			*/
		if (i < CT){								/* �L���ް�				*/
			PT[i][0] = (XT[i]*GRAPH_X_RATE1/GRAPH_X_RATE2+GRAPH_DOT_LEFT);
			PT[i][1] = (YT[i]*GRAPH_Y_RATE1/GRAPH_Y_RATE2+GRAPH_DOT_TOP );
		}else{										/*						*/
			PT[i][0] = 0;							/* X �ر				*/
			PT[i][1] = 0;							/* Y �ر				*/
		}											/*						*/
	}												/*						*/

DISP_CHECK:											/* �`�攻��				*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ω�����	*/
		if ((OT[i][0] != PT[i][0]) ||				/* 0 : X ���W			*/
			(OT[i][1] != PT[i][1]))					/* 1 : Y ���W			*/
		goto	DISP_STEP;							/* �ω����� �`��		*/
	}												/*						*/
	return;											/* �ω��Ȃ�				*/

DISP_STEP:											/* �`��J�n				*/
	for (t=0; t<GRAPH_DOT_MAX; t++){				/* �����ް��ر			*/
	for (i=0; i<GRAPH_CLM_MAX; i++){				/*						*/
		GT[t][i] = 0xFF00;							/*						*/
	}}												/*						*/

	for (i=0; i<(CT-1); i++)						/* �����ް����			*/
		GRAPH_DOT_SET (PT[i][0],PT[i][1],PT[i+1][0],PT[i+1][1]);

	for (t=0; t<GRAPH_DOT_MAX; t++)					/* �����ް��`��			*/
		Lcd_draw (1,GRAPH_CLM_TOP,GRAPH_DOT_TOP+t,GRAPH_CLM_MAX,&GT[t][0]);

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ۑ�		*/
		OT[i][0] = PT[i][0];						/* X					*/
		OT[i][1] = PT[i][1];						/* Y					*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	�h�b�g�f�[�^�Z�b�g		�F	�O���t�p�h�b�g�f�[�^���Z�b�g����B			*/
/*																			*/
/*		�w�|�x���W�Q�_�Ŏ�����郉�C���i�h�b�g�f�[�^�j��					*/
/*		�`��p�f�[�^��ɃZ�b�g����B�`��͍s��Ȃ��B						*/
/*																			*/
/****************************************************************************/
void	GRAPH_DOT_SET	(WORD X1,WORD Y1,WORD X2,WORD Y2)
{
	WORD	i;
	WORD	bt;
	WORD	xb,		yb;
	WORD	cnt,	db;
	WORD	wb,		zb;
	WORD	tb,		nb,		hb;
	WORD	x_dif,	y_dif;
	WORD	minus;
	WORD	temp;
	WORD	rate_0;

	if ((X1 < GRAPH_DOT_LEFT) || (X1 > GRAPH_DOT_RIGHT) ||
		(X2 < GRAPH_DOT_LEFT) || (X2 > GRAPH_DOT_RIGHT) ||
		(Y1 < GRAPH_DOT_TOP ) || (Y1 > GRAPH_DOT_BTM  ) ||
		(Y2 < GRAPH_DOT_TOP ) || (Y2 > GRAPH_DOT_BTM  ))
		return;										/* �`��͈� �װ			*/

//	�擪�̃o�C�g�ʒu�A�r�b�g�ʒu���Z�o ///////////////////////////////////////
	yb = ( Y1 - GRAPH_DOT_TOP );					/* Y���޲� �ʒu�Z�o		*/
	xb = ((X1 - GRAPH_DOT_LEFT) / 8);				/* X���޲� �ʒu�Z�o		*/
	bt = ((X1 - GRAPH_DOT_LEFT) % 8);				/* �J�n�ޯĈʒu�Z�o		*/

//	�^�e���A���R������ ///////////////////////////////////////////////////////
	if (X1 == X2){									/* �Ð� X�������ω��Ȃ�	*/
		if (Y1 == Y2){								/* Y�������ω��Ȃ�		*/
			GT[yb][xb] |= BT[bt];					/* 1 �ޯč��W ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y�� �������ω�		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				GT[yb+nb][xb] |= BT[bt];			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}else{										/* Y�� ������ω�		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				GT[yb-nb][xb] |= BT[bt];			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 �Ή��Ȃ�		*/

	if (Y1 == Y2){									/* ֺ�� Y�������ω��Ȃ�	*/
		for (i=X1; i<=X2; i++){						/* X�����ޯĐ��J��Ԃ�	*/
			GT[yb][xb] |= BT[bt];					/* ��ײ� �ޯč��W ON	*/
			bt ++;									/* X�� ���ޯĂɍX�V		*/
			if (bt > 7){							/*						*/
				bt  = 0;							/*						*/
				xb += 1;							/* ���޲Ăֈړ�			*/
			}										/*						*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	�ʏ�̐��i�ȂȂߐ��j�`�揈�� /////////////////////////////////////////////
	if (Y1 < Y2){									/* �`����������߂�		*/
			minus = 0;								/* plus  direction	��	*/
			y_dif = ((Y2 - Y1) * GRAPH_RATE);		/* 600�{�ŉ��Z����		*/
	}else{											/* max 95 * 600 = 57000	*/
			minus = 1;								/* minus direction	��	*/
			y_dif = ((Y1 - Y2) * GRAPH_RATE);		/*						*/
	}												/*						*/

	x_dif  = (X2 - X1);								/* X�����ޯĕω����Z�o	*/
	rate_0 = (y_dif / x_dif);						/* X���ɑ΂���Y����		*/

	GT[yb][xb] |= BT[bt];							/* �擪�ޯč��W ON		*/
	zb	= yb;										/* Y���O��l�ۑ�		*/
	cnt	= 1; 										/* �ޯĶ���				*/

DOT_LOOP:											/*						*/
	if (cnt > x_dif)				return;			/* �S�ޯĕ`��I��		*/

	temp = (rate_0 * cnt);							/* Y���̕ω������Z�o	*/
	db	 = (temp / GRAPH_RATE);						/*						*/
	temp = (temp % GRAPH_RATE);						/*						*/
	if (temp >= GRAPH_RATE_HALF)	db += 1;		/* �l�̌ܓ�				*/

	if (minus == 0){								/* plus  direction		*/
			wb = (yb + db);							/* Y�����ʒu			*/
			tb = (wb - zb);							/* Y������				*/
	}else{											/* minus direction		*/
			wb = (yb - db);							/*						*/
			tb = (zb - wb);							/*						*/
	}												/*						*/

//	�x���ړ��ʂ��P�ȉ��̏ꍇ�̃h�b�g�`�揈�� /////////////////////////////////
	if (tb <= 1){									/* �Ȃ����s�v			*/
		bt ++;										/* X�ʒu�����ޯĂɍX�V	*/
		if (bt > 7){								/* ���޲Ăֈړ�			*/
			bt  = 0;								/*						*/
			xb += 1;								/*						*/
		}											/*						*/
		GT[wb][xb] |= BT[bt];						/* �ޯč��W ON			*/
		zb = wb;									/* Y���O��l�ۑ�		*/
		cnt ++;										/*						*/
		goto	DOT_LOOP;							/*						*/
	}												/*						*/

//	�x���ړ��ʂ��傫���ꍇ�̂Ȃ����`�揈�� /////////////////////////////////
	hb = ((tb + 1) / 2);							/* Y���̔����̈ʒu�Z�o	*/
	nb	= 0; 										/* ײݶ���				*/

LIN_LOOP:											/* �Ȃ����`��			*/
	if (nb > tb){									/* �S�ޯĕ`��I��		*/
		zb = wb;									/* Y���O��l�ۑ�		*/
		cnt ++;										/*						*/
		goto	DOT_LOOP;							/*						*/
	}
	if (nb == hb){									/* ����					*/
		bt ++;										/* X�ʒu�����ޯĂɍX�V	*/
		if (bt > 7){								/* ���޲Ăֈړ�			*/
			bt  = 0;								/*						*/
			xb += 1;								/*						*/
		}											/*						*/
	}
	if (minus == 0)		wb = (zb + nb);				/* Y�����ʒu			*/
	else				wb = (zb - nb);				/*						*/

	GT[wb][xb] |= BT[bt];							/* �ޯč��W ON			*/
	nb ++;											/*						*/
	goto	LIN_LOOP;								/*						*/
}

#else		//--------------------------------------------------------------------------------------------------------------------

/****************************************************************************/
/*																			*/
/*	�O���t�`�揈��			�F	�O���t��`�悷��B							*/
/*																			*/
/*		GRAPH_DISP_FLG		�F	�O���t�`��t���O							*/
/*																			*/
/****************************************************************************/
void	GRAPH_DISP	(void)
{
	WORD	i,	t;
	WORD	x1,	x2,	y1,	y2;
	WORD	ret;
	WORD	XT [ GRAPH_POINT_MAX ];
	WORD	YT [ GRAPH_POINT_MAX ];
	WORD	CT,	ST,	FL;

//	GRAPH_DISP_FLG = ALL_DISP;						/* DEBUG				*/
//	if (GRAPH_DISP_FLG != ALL_DISP)		return;		/* �O���t�`�悵�Ȃ�		*/

	ST	= 0;										/*						*/
	ret = SvStepXYDataMake1 (XT,YT,&CT,&ST,&FL);	/* ���W�ݒ�֐�			*/

#ifdef	DEB_1
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] =   0;
	XT[CT] = 100;		YT[CT++] = 100;
	XT[CT] = 200;		YT[CT++] = 100;
	XT[CT] = 200;		YT[CT++] = 200;
	XT[CT] = 300;		YT[CT++] = 200;
	XT[CT] = 300;		YT[CT++] = 300;
	XT[CT] = 400;		YT[CT++] = 300;
	XT[CT] = 400;		YT[CT++] = 400;
	XT[CT] = 500;		YT[CT++] = 400;
	XT[CT] = 500;		YT[CT++] = 500;
#endif
#ifdef	DEB_2
	FL	=  1;
	CT	=  0;
	XT[CT] =   0;		YT[CT++] =   0;
	XT[CT] =  50;		YT[CT++] = 500;
	XT[CT] = 100;		YT[CT++] =  50;
	XT[CT] = 150;		YT[CT++] = 200;
	XT[CT] = 200;		YT[CT++] = 150;
	XT[CT] = 250;		YT[CT++] = 300;
	XT[CT] = 300;		YT[CT++] = 250;
	XT[CT] = 350;		YT[CT++] = 400;
	XT[CT] = 400;		YT[CT++] = 350;
	XT[CT] = 450;		YT[CT++] = 350;
	XT[CT] = 500;		YT[CT++] = 500;
#endif

	if ( FL == 0)						return;		/* �L����-��Ȃ�			*/
	if ((CT <= 0)||(CT > GRAPH_POINT_MAX))			/* �L���ް��� NG		*/
										return;		/*						*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* �����ް���߰			*/
		if (i < CT){								/* �L���ް�				*/
			PT[i][0] = XT[i];
			PT[i][1] = (YT[i]*GRAPH_YDOT_LEG)/GRAPH_XDOT_LEG;
		}else{										/*						*/
			PT[i][0] = 0;							/* X �ر				*/
			PT[i][1] = 0;							/* Y �ر				*/
		}											/*						*/
	}												/*						*/

DISP_CHECK:											/* �`�攻��				*/
	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ω�����	*/
		if ((OT[i][0] != PT[i][0]) ||				/* 0 : X ���W			*/
			(OT[i][1] != PT[i][1]))					/* 1 : Y ���W			*/
		goto	DISP_STEP;							/* �ω����� �`��		*/
	}												/*						*/
	return;											/* �ω��Ȃ�				*/

DISP_STEP:											/* �`��J�n				*/
	for (i=0; i<(CT-1); i++)						/* �����ް����			*/
		GRAPH_DOT_SET (PT[i][0],PT[i][1],PT[i+1][0],PT[i+1][1]);

	for (i=0; i<GRAPH_POINT_MAX; i++){				/* X-Y ���W�Q�ۑ�		*/
		OT[i][0] = PT[i][0];						/* X					*/
		OT[i][1] = PT[i][1];						/* Y					*/
	}												/*						*/
}
/****************************************************************************/
/*																			*/
/*	�h�b�g�f�[�^�Z�b�g		�F	�O���t�p�h�b�g�f�[�^���Z�b�g����B			*/
/*																			*/
/*		�w�|�x���W�Q�_�Ŏ�����郉�C���i�h�b�g�f�[�^�j��					*/
/*		�`��p�f�[�^��ɃZ�b�g����B�`��͍s��Ȃ��B						*/
/*																			*/
/****************************************************************************/
void	GRAPH_DOT_SET	(WORD X1,WORD Y1,WORD X2,WORD Y2)
{
	WORD	i;
	WORD	bt;
	WORD	xb,		yb;
	WORD	cnt,	db;
	WORD	wb,		zb;
	WORD	tb,		nb,		hb;
	WORD	x_dif,	y_dif;
	WORD	minus;
	WORD	temp;
	WORD	rate_0;
	UNl		wkl;


//	�擪�̃o�C�g�ʒu�A�r�b�g�ʒu���Z�o ///////////////////////////////////////
	yb = Y1+GRAPH_YDOT_BGN1;//( Y1 - GRAPH_DOT_TOP );					/* Y���޲� �ʒu�Z�o		*/
	xb = X1+GRAPH_XDOT_BGN1;//((X1 - GRAPH_DOT_LEFT) / 8);				/* X���޲� �ʒu�Z�o		*/
	bt = 4;//((X1 - GRAPH_DOT_LEFT) % 8);				/* �J�n�ޯĈʒu�Z�o		*/

//	�^�e���A���R������ ///////////////////////////////////////////////////////
	if (X1 == X2){									/* �Ð� X�������ω��Ȃ�	*/
		if (Y1 == Y2){								/* Y�������ω��Ȃ�		*/
			LCD_VRAM[yb][xb] = bt;						/* 1 �ޯč��W ON		*/
			return;									/*						*/
		}											/*						*/
		if (Y1 < Y2){								/* Y�� �������ω�		*/
			for (i=Y1,nb=0; i<=Y2; i++,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				LCD_VRAM[yb+nb][xb] = bt;			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}else{										/* Y�� ������ω�		*/
			for (i=Y1,nb=0; i>=Y2; i--,nb++)		/* Y�����ޯĐ��J��Ԃ�	*/
				LCD_VRAM[yb-nb][xb] |= bt;			/* �cײ� �ޯč��W ON	*/
			return;									/*						*/
		}											/*						*/
	}												/*						*/
	if (X1 > X2)					return;			/* X1 > X2 �Ή��Ȃ�		*/

	if (Y1 == Y2){									/* ֺ�� Y�������ω��Ȃ�	*/
		for (i=X1; i<=X2; i++){						/* X�����ޯĐ��J��Ԃ�	*/
			LCD_VRAM[yb][xb] = bt;					/* ��ײ� �ޯč��W ON	*/
			xb += 1;								/* ���޲Ăֈړ�			*/
		}											/*						*/
		return;										/*						*/
	}												/*						*/

//	�ʏ�̐��i�ȂȂߐ��j�`�揈�� /////////////////////////////////////////////
	if (Y1 < Y2){									/* �`����������߂�		*/
		y_dif = (Y2 - Y1);				/* 600�{�ŉ��Z����		*/
		x_dif = (X2 - X1);				/* X�����ޯĕω����Z�o	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				yb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					yb++;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
	else
	{											/* max 95 * 600 = 57000	*/
		y_dif = (Y1 - Y2);				/* 600�{�ŉ��Z����		*/
		x_dif = (X2 - X1);				/* X�����ޯĕω����Z�o	*/
		if ( y_dif < x_dif)
		{
			rate_0 = x_dif / y_dif;
			zb = temp = x_dif % y_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (y_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					xb++;
					temp -= y_dif;
				}
				for (i=0; i<rate_0; i++, xb++)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				yb--;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
		else
		{
			rate_0 = y_dif / x_dif;
			zb = temp = y_dif % x_dif;
			for (; xb<(X2+GRAPH_XDOT_BGN1); )
			{
				if (x_dif <= temp)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
					yb--;
					temp -= x_dif;
				}
				for (i=0; i<rate_0; i++, yb--)
				{
					LCD_VRAM[yb][xb] = bt;				/* ��ײ� �ޯč��W ON	*/
				}
				xb++;
				temp += zb;
			}											/*						*/
			return;										/*						*/
		}
	}
}
#endif		//--------------------------------------------------------------------------------------------------------------------


#include	"ssc_pvwave.c"			//V05o(INS)


/*** END ***/

