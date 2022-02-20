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


#pragma	section
//;	***************************************************
//;	***												***
//;	***		�^�f�[�^���e�q�n�l						***
//;	***												***
//;	***************************************************
void kata_save(U2b no, U2b *poi1)
{
}


//;	***************************************************
//;	***												***
//;	***		�^�f�[�^���e�q�n�l						***
//;	***												***
//;	***************************************************
void kata_load(U2b no, U2b *poi1)
{
}


#pragma	section	hwsetup1
//;	***************************************************
//;	***												***
//;	***		�k�b�c�V�X�e���V�j�V�����C�Y			***
//;	***												***
//;	***************************************************
void init_LCD(void)
{
}


#pragma	section	hwsetup1
/*
********************************************************************************
*
*  Function Name:	�k�b�c�C�j�V������ʕ\��
*
********************************************************************************
*/
#if ( SIT_TYPE_SEL == TYPE_SIT4 )

const	char	INIT_MOJI[] = "Initialize";
const	char	INIT_MOJI_dummy = 0x00;			//V05g

UNs	init_code_dot_cnv(UNs d_cara, UNb *Dst_p, UNs flg)
{
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
}


void init_DISP(void)
{
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
}


#endif



#pragma section

void Lcd_cr(U2b lcd_no, U2b xy_pos, U2b *poi1)
{
}

//;	***************************************************
//;	***												***
//;	***		���1�s�\��								***
//;	***												***
//;	***************************************************
void Lcd_line(U2b lcd_no, U2b l_no, U2b cnt, U2b *poi1)
{
}

//;	***************************************************
//;	***												***
//;	***		��ʑS�\��								***
//;	***												***
//;	***************************************************
void Lcd_all(U2b lcd_no, U2b cnt, U2b *poi1)
{
}

void Lcd_draw(U2b lcd_no, U2b X_clm, U2b Y_dot, U2b C_cnt, U2b *poi1)
{
}

//;	***************************************************
//;	***												***
//;	***		���ON									***
//;	***												***
//;	***************************************************
void Lcd_on(void)
{
}

//;	***************************************************
//;	***												***
//;	***		���OFF									***
//;	***												***
//;	***************************************************
void Lcd_off(void)
{
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
	return(0);
}


/*** END ***/
