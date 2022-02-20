//;	*******************************************************************
//;	***																***
//;	***																***
//;	***		�g�l�h�e�C���^�[�t�F�C�X�\�t�g							***
//;	***																***
//;	***																***
//;	*******************************************************************
#include	"cm_equ1.h"
#include	"CPU_REG.h"
#include	"ssc_wrms.h"
#include	"ssc_ver1.h"
#include	"ssc_def.h"

extern	U2b	LCD_WORK1[15][16][40];
extern	U2b	LCD_WORK2[15][16][40];

extern	U1b	LCD_CTRL[2];
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
extern	U1b	kan_bank_outp;
#else
extern	U4b	kan_bank_outp;
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
#endif

extern	void LCD_CR_ASM(void);
extern	void GLC_BUSY(void);
extern	void WDT_Rifresh(void);
extern	void KATA_SAVE_ASM(void);
extern	void KATA_LOAD_ASM(void);
extern	void kan_rom_top(void);

extern	U2b		SEQ_043_SV;
extern	U2b		SEQ_044_SV;
extern	U2b		SEQ_045_SV;
extern	U2b		SEQ_046_SV;
extern	U2b		SEQ_047_SV;



#pragma	section
//;	***************************************************
//;	***												***
//;	***		�^�f�[�^���e�q�n�l						***
//;	***												***
//;	***************************************************
void kata_save(U2b no, U2b *poi1)
{
	kata_no_sv = no;
	kata_adr_sv = poi1;

	KATA_SAVE_ASM();
}


//;	***************************************************
//;	***												***
//;	***		�^�f�[�^���e�q�n�l						***
//;	***												***
//;	***************************************************
void kata_load(U2b no, U2b *poi1)
{
	kata_no_ld = no;
	kata_adr_ld = poi1;

//2016/04/22
	SEQ_043_SV_WK = SEQ_043_SV;			//PUSH	MB(�O/�S/��)�I���A�h���(�O/�S/��)�I��
	SEQ_044_SV_WK = SEQ_044_SV;			//PUSH	�o�����T����(�ݒ舳/���)�I���A�X���C�h��������(���Y/�i��1/�i��2)�I��
	SEQ_045_SV_WK = SEQ_045_SV;			//PUSH	�_�C�N�b�V��������(��/�E)�I��
	SEQ_046_SV_WK = SEQ_046_SV;			//PUSH	�_�C�N�b�V��������(��۰��^����)
	SEQ_047_SV_WK = SEQ_047_SV;			//PUSH	ADC(����/����/���o)

	KATA_LOAD_ASM();

//2016/04/22
	SEQ_043_SV = SEQ_043_SV_WK;										//POP	MB(�O/�S/��)�I���A�h���(�O/�S/��)�I��
	SEQ_044_SV = SEQ_044_SV_WK;										//POP	�o�����T����(�ݒ舳/���)�I���A�X���C�h��������(���Y/�i��1/�i��2)�I��
	SEQ_045_SV = (SEQ_045_SV & 0xff00) | (SEQ_045_SV_WK & 0x00ff);	//POP	�_�C�N�b�V��������(��/�E)�I��
	SEQ_046_SV = (SEQ_046_SV & 0x00ff) | (SEQ_046_SV_WK & 0xff00);	//POP	�_�C�N�b�V��������(��۰��^����)
	SEQ_047_SV = SEQ_047_SV_WK;										//POP	ADC(����/����/���o)
}


#pragma	section	hwsetup1
//;	***************************************************
//;	***												***
//;	***		�k�b�c�V�X�e���V�j�V�����C�Y			***
//;	***												***
//;	***************************************************
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
void init_LCD(void)
{
	U2b		i;

	LCD_CTRL[1] = 0x40;							// [[ LCD SYSTEM RESET PROCESSING ]]
	LCD_CTRL[0] = 0x30;							// P1 : [M0:0][M1:0][M2:0][WS:0]
	LCD_CTRL[0] = 0x07;							// P2 : [FX:7][WF:0]
	LCD_CTRL[0] = 0x07;							// P3 : [FY:7]
	LCD_CTRL[0] = 0x27;							// P4 : [CR:27]
	LCD_CTRL[0] = 0x40;							// P5 : [TC/R: 68 -> 40 ]
	LCD_CTRL[0] = 0xef;							// P6 : [LF:EF]
	LCD_CTRL[0] = 0x28;							// P7 : [APL:28]
	LCD_CTRL[0] = 0x00;							// P8 : [APH:00]

	LCD_CTRL[1] = 0x5a;							// [[ HDOT SCR SET PROCESSING ]]
	LCD_CTRL[0] = 0x00;							// SCROLE : [D0,D1,D2 : 000]

	LCD_CTRL[1] = 0x44;							// [[ SCROLL SET PROSECCING ]]
	LCD_CTRL[0] = 0x00;							// SAD1L
	LCD_CTRL[0] = 0x00;							// ASD1H
	LCD_CTRL[0] = 0xef;							// SL1
	LCD_CTRL[0] = 0x80;							// SAD2L
	LCD_CTRL[0] = 0x25;							// SAD2H
	LCD_CTRL[0] = 0xef;							// SL2
	LCD_CTRL[0] = 0x00;							// SAD3L
	LCD_CTRL[0] = 0x4b;							// SAD3H
	LCD_CTRL[0] = 0x00;							// SAD4L
	LCD_CTRL[0] = 0x60;							// SAD4H

	LCD_CTRL[1] = 0x5b;							// [[ OVLAY SET PROCESSING ]]
	LCD_CTRL[0] = 0x0d;							//

	LCD_CTRL[1] = 0x59;							// [[ DISP ON SET ]]
	LCD_CTRL[0] = 0x54;							//
///���߂�12-23	LCD_CTRL[0] = 0x04;							//

	LCD_CTRL[1] = 0x46;							// [[ DISPALY V.REM ALL CLEAR ]]
	LCD_CTRL[0] = 0x00;							//
	LCD_CTRL[0] = 0x00;							//

	LCD_CTRL[1] = 0x4c;							// [[ SIFT COMMAND OUTPUT ]]
	LCD_CTRL[1] = 0x42;							// DATA WRITE COMMAND OUTPUT

	for (i=0x4b00; i>0; --i)					// CLEAR COUNTER SET
	{
		LCD_CTRL[0] = 0x00;						//
	}

	LCD_CTRL[1] = 0x46;							//  [[ DISPALY V.REM ALL CLEAR ]]
	LCD_CTRL[0] = 0x80;							//
	LCD_CTRL[0] = 0x25;							//

	LCD_CTRL[1] = 0x4c;							// [[ SIFT COMMAND OUTPUT ]]
	LCD_CTRL[1] = 0x42;							// DATA WRITE COMMAND OUTPUT

	for (i=0x2580; i>0; --i)					// CLEAR COUNTER SET
	{
		LCD_CTRL[0] = 0x00;						//
	}
}

#else

const	U4b		TFT_COL_PLDATA[64]={			//V06  16->64
/*	   0,R,G,B		*/
	0x00000000,					/* 00�F��				R:000,G:000,B:000	*/
	0x000000FF,					/* 01�F��				R:000,G:000,B:255	*/
	0x0000FF00,					/* 02�F��				R:000,G:255,B:000	*/
	0x0000FFFF,					/* 03�F��݁i���F�j		R:000,G:255,B:255	*/
	0x00FF0000,					/* 04�F��				R:255,G:000,B:000	*/
	0x00FF00FF,					/* 05�FϾ���ށi��ݸ�j	R:255,G:000,B:255	*/
	0x00FFFF00,					/* 06�F��				R:255,G:255,B:000	*/
	0x00FFFFFF,					/* 07�F��				R:255,G:255,B:255	*/
	0x00D8D8D8,					/* 08�F�D�F1			R:216,G:216,B:216	*/
	0x00C0C0C0,					/* 09�F�D�F2			R:192,G:192,B:192	*/
	0x00A0A0A0,					/* 0A�F�D�F3			R:160,G:160,B:160	*/
	0x00808080,					/* 0B�F�D�F4			R:128,G:128,B:128	*/
	0x00FF8000,					/* 0C�F��ݼ�			R:255,G:128,B:000	*/	//V05o
	0x0080FF00,					/* 0D�F����				R:128,G:255,B:000	*/	//V05o
	0x00000000,					/* 0E�F�\��									*/
	0x00000000,					/* 0F�F�\��									*/
	0x00000000,					/* 10�F�\��									*/
	0x00000000,					/* 11�F�\��									*/
	0x00000000,					/* 12�F�\��									*/
	0x00000000,					/* 13�F�\��									*/
	0x00000000,					/* 14�F�\��									*/
	0x00000000,					/* 15�F�\��									*/
	0x00000000,					/* 16�F�\��									*/
	0x00000000,					/* 17�F�\��									*/
	0x00000000,					/* 18�F�\��									*/
	0x00000000,					/* 19�F�\��									*/
	0x00000000,					/* 1A�F�\��									*/
	0x00000000,					/* 1B�F�\��									*/
	0x00000000,					/* 1C�F�\��									*/
	0x00000000,					/* 1D�F�\��									*/
	0x00000000,					/* 1E�F�\��									*/
	0x00000000,					/* 1F�F�\��									*/
	0x00000000,					/* 20�F�\��									*/
	0x00000000,					/* 21�F�\��									*/
	0x00000000,					/* 22�F�\��									*/
	0x00000000,					/* 23�F�\��									*/
	0x00000000,					/* 24�F�\��									*/
	0x00000000,					/* 25�F�\��									*/
	0x00000000,					/* 26�F�\��									*/
	0x00000000,					/* 27�F�\��									*/
	0x00000000,					/* 28�F�\��									*/
	0x00000000,					/* 29�F�\��									*/
	0x00000000,					/* 2A�F�\��									*/
	0x00000000,					/* 2B�F�\��									*/
	0x00000000,					/* 2C�F�\��									*/
	0x00000000,					/* 2D�F�\��									*/
	0x00000000,					/* 2E�F�\��									*/
	0x00000000,					/* 2F�F�\��									*/
	0x00008F00,					/* 30�FEcoMeter0		R:000,G:255,B:000	*/
	0x00009F00,					/* 31�FEcoMeter1		R:000,G:-16,B:000	*/
	0x0000AF00,					/* 32�FEcoMeter2		R:000,G:-16,B:000	*/
	0x0000BF00,					/* 33�FEcoMeter3		R:000,G:-16,B:000	*/
	0x0000CF00,					/* 34�FEcoMeter4		R:000,G:-16,B:000	*/
	0x0000DF00,					/* 35�FEcoMeter5		R:000,G:-16,B:000	*/
	0x0000EF00,					/* 36�FEcoMeter6		R:000,G:-16,B:000	*/
	0x0000FF00,					/* 37�FEcoMeter7		R:000,G:-16,B:000	*/
	0x00000000,					/* 38�F�\��									*/
	0x00000000,					/* 39�F�\��									*/
	0x00000000,					/* 3A�F�\��									*/
	0x00000000,					/* 3B�F�\��									*/
	0x00000000,					/* 3C�F�\��									*/
	0x00000000,					/* 3D�F�\��									*/
	0x00000000,					/* 3E�F�\��									*/
	0x00000000					/* 3F�F�\��									*/
};

void init_LCD(void)
{
	U2b		i;

	LDICKR = 0x0002;			//; �C���v�b�g�N���b�N���W�X�^
								//; ���͸ۯ���CKIO �^ �����1/2  ����āADOTCLK��29.4912MHz
	LDMTR = 0xc02b;				//; ���W���[���^�C�v���W�X�^
								//; �s�e�s�J���[�P�U�r�b�g�f�[�^�o�X���W���[��
	LDDFR = 0x000C;				//; �f�[�^�t�H�[�}�b�g���W�X�^
								//; �J���[256�F8bpp�i��گČo�R�j
//	LDSMR = �����l�łn�j		//; �X�L�������[�h���W�X�^

	LDSARU = (U4b)&LCD_VRAM[0][0];	//; �㕔�\���p�l���p�f�[�^��荞�݊J�n�A�h���X���W�X�^
//	LDSARL = �����l�łn�j		//; �����\���p�l���p�f�[�^��荞�݊J�n�A�h���X���W�X�^

	LDLAOR = 640;				//; �\���p�l���p��荞�݃f�[�^���C���A�h���X�I�t�Z�b�g���W�X�^
								//; ����640
	LDHCNR = 0x4F63;			//; �����L�����N�^�i���o�[���W�X�^
								//; �\����׸����ް �� 79 �� ��640�^�����8�ޯĒP�ʁ|1    ����׸����ް �� 99 �� ��800�^ �����8�ޯĒP�ʁ|1
	LDHSYNR = 0xB051;			//; ���������M�����W�X�^
								//; �M���� �� 11 �� 96�ޯ�/�����8�ޯĒP��-1    �M���o�͈ʒu �� 81 �� (��640�{�����߰�16�ޯ�)�^�����8�ޯĒP�ʁ|1
	LDVDLNR = 479;				//; �����\�����C���i���o�[���W�X�^
								//; �c480�|1
	LDVTLNR = 524;				//; ���������C���i���o�[���W�X�^
								//; �c525�|1
	LDVSYNR = 0x11E8;			//; ���������M�����W�X�^
								//; ���������M���� �� 1 �� 2ײ݁|1   ���������M���o�͈ʒu �� 488 �� 490ײݖځ|2

	LDPMMR = 0xFF70;			//; �p���[�}�l�W�����g���[�h���W�X�^
								//; RGB�ް��A���ݸ��ް��́A�߰Ăŏo�ͲȰ��قɂ��Ă��邩����ۂ�VCPWC���o�͂����������B
	LDPSPR = 0xFFFF;			//; �d���V�[�P���X���ԃ��W�X�^
								//; RGB�ް��A���ݸ��ް��́A�߰Ăŏo�ͲȰ��قɂ��Ă��邩����ۂ�VCPWC���o�͂����������B

//�J���[�p���b�g�ݒ�
	LDPALCR = 0x0001;			//; �b�o�t���p���b�g���g�p�B

	for (i=0; i<64; i++)		//V06  16->64
	{
		LDPR00[i] = TFT_COL_PLDATA[i];
	}

	LDPALCR = 0x0000;			//; �k�b�c�b���p���b�g���g�p�B

}
#endif


#pragma	section	hwsetup1
/*
********************************************************************************
*
*  Function Name:	�k�b�c�C�j�V������ʕ\��
*
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT4 )

extern	const	UNs	Han_MPtn_Table[256][16];		//���p�����p�^�[���@�e�[�u��

const	char	INIT_MOJI[] = "Initialize";
const	char	INIT_MOJI_dummy = 0x00;			//V05g

UNs	init_code_dot_cnv(UNs d_cara, UNb *Dst_p, UNs flg)
{
	UNs	*Src_p;
	UNs	*Dst_px;
	UNb	code1;
	UNs	*Srcw_p, d_cara_swap, dat;
	UNi	type, r_wk, size;

	Dst_px = (UNs *)Dst_p;

	code1 = d_cara & 0x00ff;

	/**************** ���p�R�[�h�h�b�g�ϊ����� ***************/
	Srcw_p = &Han_MPtn_Table[code1][0];	//���p���������ð��� ���ڽ�Z�o

	if(flg == 0xff ) {					//���]�\���H
		size = 16;						/* �ް�Copy */
		while( size-- ) {
			*Dst_p++ = ~(*Srcw_p++);	//�ޯĔ��]
		}
	}
	else {								//����\��
		size = 16;						/* �ް�Copy */
		while( size-- ) {
			*Dst_p++ = *Srcw_p++;
		}
	}
	r_wk = 0;							//���p����
	return (r_wk);
}


void	disp_init_moji(
			UNs len,
			UNs x,
			UNs y,
			UNs c_col, 
			UNs b_col, 
			UNs size, 
			UNs *g_adr_p
			)
{
	UNi		i, j, k, l, flg;
	UNs		cnt, cnv_wk, *Dst_p;
	UNs		xdot, ydot, xdot_bak, ydot_bak;
	UNs		xsize, ysize, xcnt, ycnt;
	UNs		x_dot_leng, y_dot_leng;
	UNb		moji[E_line], dot_wk[32], wk1b;

	flg = 0;

	cnt = len;											//�������@�Z�o
	xsize = (size>>8) & 0x0ff;					// X�̻���
	ysize = size & 0x0ff;						// Y�̻���

	/******** �w�i�F�h��ׂ� *********/
	x_dot_leng = xsize * cnt * 8;				// ���� �~ �޲Ē� �~ 8�ޯ�/1byte
	y_dot_leng = ysize * 16;					// ���� �~ 16dot�^1����
	xdot = x;
	for (xcnt=x_dot_leng; xcnt>0; xcnt--,xdot++)			// X�����{�P�ޯ�
	{
		ydot = y;
		for (ycnt=y_dot_leng;  ycnt>0; ycnt--,ydot++)		// Y�����h��ׂ�
		{
			LCD_VRAM[ydot][xdot] = b_col;
		}
	}

	/******** �����\�� *********/
	xdot = x;
	ydot = y;

	for( i=0 ; i < cnt ; i += 2 ) {						//ܰ�ށ��޲ĒP�ʱ����\�̈�ɺ�߰
		cnv_wk = *g_adr_p++;
		moji[i+1] = cnv_wk;
		moji[i] = cnv_wk >> 8;
	}

	xdot_bak = xdot;
	for( i=0 ; i < cnt ; i++ ) {
		cnv_wk = moji[i+1];								//�������ނ̐ݒ�
		cnv_wk <<= 8;
		cnv_wk |= moji[i];

		if( 0 == init_code_dot_cnv(cnv_wk, &dot_wk[0], flg) ) {	//�������ށ��ޯĕϊ�
															//���p
			for ( l=0, k=0; l<16; l++ ) {
				for ( ycnt=0; ycnt<ysize; ycnt++) {
					for ( j=0,wk1b=0x80; j<8; j++,wk1b>>=1 ) {
						if ( dot_wk[k] & wk1b ) {					// dot�f�[�^���ޯĂ������Ă���H
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								LCD_VRAM[ydot][xdot] = c_col;
								xdot++;
							}
						}
						else {
							for ( xcnt=0; xcnt<xsize; xcnt++ ) {
								xdot++;
							}
						}
					}
					xdot = xdot_bak;
					ydot++;
				}
				k++;
			}
			xdot_bak += xsize * 1 * 8;
			xdot = xdot_bak;
			ydot = y;
		}
		else {												//�S�p
		}
	}
}


void init_DISP(void)
{
	UNl		col, cnt, *vram;

	col = 0x06060606;
	vram = (UNl *)&LCD_VRAM[0][0];
	cnt = (PanelWidth * PanelHeight) / 4;
	
	while (cnt--)
	{
		*vram++ = col;
	}

	disp_init_moji(
		10,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		224,					/* SW_buff[T_no].Y_POS, 	*/
		0,						/* SW_buff[T_no].C_COL,		*/
		8,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&INIT_MOJI
		);

	LDCNTR = 0x0011;					//SH7727-LCDC����

	for(cnt=0x0ffffff; cnt>0; cnt--)
	{
		if( (LDPMMR & 0x0003) == 0x0003)
		{
			break;
		}
	}
	if (cnt != 0)
	{
		PEDR = 0;					// *LCD_ON�C�l�[�u��
	}
}


/*
********************************************************************************
*
*  Function Name:	�u��ʂ��ް�ޮ�UP���Ă��������v�̕\��		V05i
*
********************************************************************************
*/
const	char	VUP_MESG_MOJI[] = "PLEASE V-UP[G]";
const	char	VUP_MESG__MOJIdummy = 0x00;

void vup_mesG_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESG_MOJI
		);
}


/*
********************************************************************************
*
*  Function Name:	�uCPUB���ް�ޮ�UP���Ă��������v�̕\��		V05i
*
********************************************************************************
*/
const	char	VUP_MESB_MOJI[] = "PLEASE V-UP[B]";
const	char	VUP_MESB__MOJIdummy = 0x00;

void vup_mesB_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESB_MOJI
		);
}


/*
********************************************************************************
*
*  Function Name:	�uCPUA���ް�ޮ�UP���Ă��������v�̕\��		V05i
*
********************************************************************************
*/
const	char	VUP_MESA_MOJI[] = "PLEASE V-UP[A]";
const	char	VUP_MESA__MOJIdummy = 0x00;

void vup_mesA_disp(void)
{
	disp_init_moji(
		14,						/* len, 					*/
		240,					/* SW_buff[T_no].X_POS, 	*/
		288,					/* SW_buff[T_no].Y_POS, 	*/
		4,						/* SW_buff[T_no].C_COL,		*/
		6,						/* SW_buff[T_no].B_COL2, 	*/
		0x0202,					/* SW_buff[T_no].SIZE, 		*/
		(UNs *)&VUP_MESA_MOJI
		);
}


#endif



#pragma section

//;	***************************************************
//;	***												***
//;	***		��ʷ�ו\��								***
//;	***												***
//;	***************************************************
/******************** V01b ********************
void Lcd_cr(U2b lcd_no, U2b xy_pos, U2b *poi1)
{
	U2b	i,i2,j,k,m,n,d;
	U2b	*poi2;

	i = (xy_pos & 0x000f);			// �s�ԍ��Ǎ���
	j = ((xy_pos>>4) & 0x003f);			// ���ԍ�
	k = (xy_pos>>10) & 0x003f;			// ������

	i = i * 640 + j;				// �\�����Ĉʒu
	poi1 = poi1 + i * 1;				// 

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	for(n=16; n>0; --n)
	{
		poi2 = poi1;
		GLC_BUSY();
		LCD_CTRL[1] = 0x46;		// ���Ĉʒu�ݒ����ޔ��s
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[0] = i;		// ���ı��ڽ(����)���s
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[0] = i>>8;		// ���ı��ڽ(���)���s
		while(LCD_CTRL[0] & 0x40){}
		LCD_CTRL[1] = 0x42;		// �\����؂ւ̏����ݺ���ޔ��s

		GLC_BUSY();
		for (m=0; m<k; ++m)
		{
			if(lcd_no==0)
			{
				d = ~*poi2++;			// �\���ް�������
			}
			else{
				d = *poi2++;
			}
			LCD_CTRL[0] = d;		// �\���ް�������
		}
		poi1 += 40;
		i += 40;
	}
}
********************* V01b *******************/

void Lcd_cr(U2b lcd_no, U2b xy_pos, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	i,i2,j,k,m,n,d;
	U2b	*poi2;

	i = (xy_pos & 0x000f);			// �s�ԍ��Ǎ���
	j = ((xy_pos>>4) & 0x003f);			// ���ԍ�
	k = (xy_pos>>10) & 0x003f;			// ������

	i = i * 640 + j;				// �\�����Ĉʒu
	poi1 = poi1 + i * 1;				// 

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	aLCD_NO = lcd_no;
	aLCD_MOZI_SUU = k;

	for(n=16; n>0; --n)
	{
		aLCD_BUFF = poi1;
		aLCD_WR_ADR = i;
		LCD_CR_ASM();
		poi1 += 40;
		i += 40;
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		���1�s�\��								***
//;	***												***
//;	***************************************************
void Lcd_line(U2b lcd_no, U2b l_no, U2b cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	xy;
	xy = l_no | (0<<4) | (40<<10);
	Lcd_cr(lcd_no, xy, &(poi1[0]));
#else
	UNl		*Src_p, *Dis_p;
	UNl		i;
	if(lcd_no == 0)
	{
		Src_p = (UNl *)&LCD_VBASE[l_no*16*2][0];
		Dis_p = (UNl *)&LCD_VRAM[l_no*16*2][0];
		i = (PanelWidth * (1*16*2)) / 4;
		while(i--)
		{
			*Dis_p++ = *Src_p++;
		}
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		��ʑS�\��								***
//;	***												***
//;	***************************************************
void Lcd_all(U2b lcd_no, U2b cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	l_no;
	cnt = 0;

	for (l_no=0; l_no<15; ++l_no)
	{
		WDT_Rifresh();
		Lcd_line(lcd_no, l_no, cnt, &(poi1[0]));
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		����ޯĕ\��							***
//;	***												***
//;	***************************************************
/******************** V01b ********************
void Lcd_draw(U2b lcd_no, U2b X_clm, U2b Y_dot, U2b C_cnt, U2b *poi1)
{
	U2b	no,x,y,c;
	U2b	*poi2;

	no = lcd_no;
	x = X_clm;									// ��ѐ擪		0�`39
	y = Y_dot;									// �ޯĈʒu		0�`239(16�~15)
	c = C_cnt;									// �\����ѐ�	1�`40
	poi2 = poi1;

	y = y * 40 + x;								// �\�����Ĉʒu

	if (no!=0) {
		y += 15*16*40;
	}

	GLC_BUSY();
	LCD_CTRL[1] = 0x46;		// ���Ĉʒu�ݒ����ޔ��s
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[0] = y;		// ���ı��ڽ(����)���s
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[0] = y>>8;		// ���ı��ڽ(���)���s
	while(LCD_CTRL[0] & 0x40){}
	LCD_CTRL[1] = 0x42;		// �\����؂ւ̏����ݺ���ޔ��s
	while(LCD_CTRL[0] & 0x40){}//(2002-12-23�����·�΍�1)
	GLC_BUSY();

	for ( ; c>0; --c)
	{
		if(no==0)
		{
			LCD_CTRL[0] = ~*poi2++;			// �\��
		}
		else{
			LCD_CTRL[0] = *poi2++;			// �\��
		}
		while(LCD_CTRL[0] & 0x40){}//(2002-12-23�����·�΍�1)
	}
}
********************* V01b *******************/

void Lcd_draw(U2b lcd_no, U2b X_clm, U2b Y_dot, U2b C_cnt, U2b *poi1)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	U2b	k,i;

	k = C_cnt;									// �\����ѐ�	1�`40
	i = Y_dot * 40 + X_clm;								// �\�����Ĉʒu

	if (lcd_no!=0) {
		i += 15*16*40;
	}

	aLCD_NO = lcd_no;
	aLCD_MOZI_SUU = k;
	aLCD_BUFF = poi1;
	aLCD_WR_ADR = i;
	LCD_CR_ASM();
#endif
}

//;	***************************************************
//;	***												***
//;	***		���ON									***
//;	***												***
//;	***************************************************
void Lcd_on(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	LCD_CTRL[1] = 0x59;
	LCD_CTRL[0] = 0x54;
	GAMEN_ON_FLG = 0;
#endif
}

//;	***************************************************
//;	***												***
//;	***		���OFF									***
//;	***												***
//;	***************************************************
void Lcd_off(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	if(GAMEN_ON_FLG != 0x0ff)
	{
		LCD_CTRL[1] = 0x58;
		LCD_CTRL[0] = 0x54;
	}
#endif
}

//;	***************************************************
//;	***												***
//;	***		LCD�P�x�ݒ�								***
//;	***												***
//;	***************************************************
	extern	U2b	IOGA1_CTRL_DAT1[8];
#define		IOGA_P4		4*2
void Lcd_contrast_chage(U2b con)
{
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	PADR = (PADR & 0xff0f) | ((con<<4) & 0x00f0);
#else
	*(IOGA1_CTRL_DAT1+IOGA_P4) = (con & 0x000f);
#endif
}

//;	***************************************************
//;	***  �����q�n�l���f�[�^�Z�b�g					***
//;	***  Input	: JIS�R�[�h							***
//;	***  Return	: �����q�n�l�A�h���X				***
//;	***************************************************
#define		E_gai_code		0xEB9F					//�O���R�[�h
#define		GAMEN_ADR_TOP	0x400000				//1��ʕ������ނ�į�� ���ڽ
#define		E_GAMEN_LIM		0x280					//1��ʕ������ނ̗̈撷
#define		E_line			40						//1�s�̕\��������
#define		E_line_byte		16*40					//1�s�̕\���p�ޯ̧��

#define		E_AS_SP			0x20					//�X�y�[�X�mASCII���ށn
#define		E_AS_TEN		0x2e					//�h.�h�@ �mASCII���ށn

#define		E_SJ_SP			0x8140					//�X�y�[�X�mS-JIS���ށn
#define		E_SJ_TEN		0x8144					//�h.�h�@ �mS-JIS���ށn
#define		E_SJ_Base		0x821f					//ASCII+0x821f=�O�`�X�mS-JIS���ށn

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define		DEF_KAN_ROM_TOP		0x00860000
#else
#define		DEF_KAN_ROM_TOP		0xA0058000
#endif


U1b *kan_rom_set(U2b d_cara)
{
	U2b	k;
	U4b	i,j;
	U1b	*ch;

	i = d_cara >> 8;
	if(i < 0x30) {									// �񊿎��R�[�h

		/************ �񊿎��R�[�h *****************/
		i = d_cara;									// �����o���N�|�[�g�m��
		j = d_cara >> 8;

		j &= 0x07;									//AND	BH,07H
		i &= 0x60;									//AND	DL,60H
		i >>= 2;									//SHR 	DL,2
		j |= i;										//OR 	BH,DL
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;									//SHL	BH,2
		k = (kan_bank_dat & 0x0003);				//MOV	AL,DAT_LCD_KAN_BAK		;//AND	AL,00000011B			;
		k |= j;										//OR	BH,AL				;
		kan_bank_outp = k;							/* �f�[�^�o�� */
#else
		j <<= 12;
		kan_bank_outp = j;							/* �f�[�^�o�� */
		kan_bank_outp &= 0x03f000;					/* �f�[�^�o�� */
#endif
		d_cara &= 0x001f;							//AND	BL,00011111B			;
		d_cara <<= 5;								//SHL	BX,5				;
	}

	else if(i< 0x50) {								//��P���������R�[�h

		/************ �����R�[�h *******************/
		i = d_cara;									/* �����o���N�|�[�g�m�� */
		j = d_cara >> 8;

		j &= 0x4f;
		i = j & 0xf0;
		i >>= 2;
		i &= 0x10;
		j &= 0x0f;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;
		k = (kan_bank_dat & 0x0003);
		k |= j;
		kan_bank_outp = k;							/* �f�[�^�o�� */
#else
		j <<= 12;
		kan_bank_outp = j;							/* �f�[�^�o�� */
		kan_bank_outp &= 0x03f000;					/* �f�[�^�o�� */
#endif
		d_cara &= 0x007f;
		d_cara <<= 5;
	}

	else if(i < 0x70) {								//��Q�����R�[�h(0x50,0x60)

	/************ �T�O�g�C�U�O�g�@�����R�[�h *******************/
		i = d_cara;									/* �����o���N�|�[�g�m�� */
		j = d_cara >> 8;

		j &= 0x2f;
		i = j & 0xf0;
		i >>= 1;
		i &= 0x10;
		j &= 0x0f;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 2;
		k = (kan_bank_dat & 0x0007);
		k |= j;
		k |= 0x80;									/* CA12=1 ��񐅏������� */
		kan_bank_outp = k;							/* �f�[�^�o�� */
#else
		j <<= 12;
		kan_bank_outp = j;							/* �f�[�^�o�� */
		kan_bank_outp |= 0x020000;					/* �f�[�^�o�� */	//V05r(INS)
		kan_bank_outp &= 0x03f000;					/* �f�[�^�o�� */
#endif
		d_cara &= 0x007f;
		d_cara <<= 5;
	}

	else{											//��Q�����R�[�h(0x70)

	/************ �V�O�g�����R�[�h *****************/
		i = d_cara;									/* �����o���N�|�[�g�m�� */
		j = d_cara >> 8;

		j &= 0x07;
		i &= 0x60;
		i >>= 2;
		j |= i;
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		j <<= 1;
		k = (kan_bank_dat & 0x0007);
		k |= j;
		k |= 0x80;								/* CA12=1 ��񐅏������� */
		kan_bank_outp = k;						/* �f�[�^�o�� */
#else
		j <<= 12;
		kan_bank_outp = j;							/* �f�[�^�o�� */
		kan_bank_outp |= 0x020000;					/* �f�[�^�o�� */	//V05r(INS)
		kan_bank_outp &= 0x03f000;					/* �f�[�^�o�� */
#endif
		d_cara &= 0x001f;
		d_cara <<= 5;
	}

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	ch=(U1b *)d_cara;
#else
	kan_bank_outp |= d_cara;
	ch=(U1b *)kan_bank_outp;
#endif

//	ch += DEF_KAN_ROM_TOP;
	ch += (U4b)&kan_rom_top;
	return(ch);
}


/*
********************************************************************************
*  Function Name:	�w��^�f�[�^�Ǐo���^������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:A.Shima		ON:2014/04/17
********************************************************************************
*/
void	KATAn_RW(viod)
{
}


/*** END ***/
