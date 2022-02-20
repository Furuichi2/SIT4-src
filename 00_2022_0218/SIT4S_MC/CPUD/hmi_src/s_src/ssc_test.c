/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			�\�@���@�ց@��															*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-21
*
*************************************************************************************/


/* �f�[�^�^��` ------------------------------------------------------ */
typedef	unsigned int	UNi;
typedef	unsigned char	UNb;
typedef	unsigned short	UNs;
typedef	unsigned long	UNl;

/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void Lcd_all(UNs, UNs, UNs *);					//�S�\��
extern	void Lcd_line(UNs, UNs, UNs, UNs *);			//�s�\��
extern	void Lcd_cr(UNs, UNs, UNs *);					//��גP�ʕ\��
extern	void Lcd_draw(UNs, UNs, UNs, UNs, UNs *);		//�ޯĕ\��
extern	void Lcd_on(void);								//���ON
extern	void Lcd_off(void);								//���OFF
extern	UNb *	kan_rom_set(UNs);						//�����q�n�l���f�[�^�Z�b�g

/* �O���Q�ƕϐ���` -------------------------------------------------- */
/* �萔��` ---------------------------------------------------------- */
/***	�\���p�̒�`	***/
#define	E_gmen_bf		15*16*40				//1��ʂ̕\���p�ޯ̧��
#define	E_gmen_size		15*16*40*2				//1��ʂ̕\���p�ޯ̧�����
#define	E_line			40						//1�s�̕\��������
#define	E_line_bf		16*40					//1�s�̕\���p�ޯ̧��
#define	E_line_size		16*40*2					//1�s�̕\���p�ޯ̧�����
#define	E_next_dot		40*2					//1�����̎�dot�ʒu��

/* �v���g�^�C�v�錾 -------------------------------------------------- */
/* �����ϐ���` ------------------------------------------------------ */
UNs		LCD_WORK1[15][16][40];		/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */

/* �e�[�u����` ------------------------------------------------------ */


/*
********************************************************************************
*  Module Name:		disp_test
*  Function Name:	�\���e�X�g
*  Input	:		�Ȃ�
*  Return	:		�Ȃ�
*  Note		:
********************************************************************************
*/
void	disp_test(void)
{
	UNb	*src_p;
	UNs	*dst_p, wk1;
	UNi	i, j, k, type;


/*		LCD_WORK1��1��ʕ��̃f�[�^��ݒ肷��		*/
//0�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2422);			//"��"(0x2422)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[0][0][j];			//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//1�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x242b);			//"��"(0x242b)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[1][0][j];			//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//2�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2435);			//"��"(0x2435)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[2][0][j];			//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//3�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x254f);			//"�n"(0x254f)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[3][0][j];			//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//4�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x255e);			//"�}"(0x255e)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[4][0][j];			//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//5�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2564);				//"��"(0x2564)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[5][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//6�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2330);				//"�O"(0x2330)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[6][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//7�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2331);				//"�P"(0x2331)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[7][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//8�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2332);				//"�Q"(0x2332)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[8][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//9�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2358);				//"�w"(0x2358)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[9][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//10�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x2359);				//"�x"(0x2359)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[10][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//11�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x235a);				//"�y"(0x235a)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[11][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//12�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3021);				//"��"(0x3021)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[12][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//13�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3066);				//"��"(0x3066)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[13][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}

//14�s��
	for( i=20, j=0 ; i > 0 ; i--, j+=2 ){
		src_p = kan_rom_set(0x3127);				//"�F"(0x3127)�@JIS�ϊ�������ROM���ڽ
		dst_p = &LCD_WORK1[14][0][j];				//1�s�𖄂߂�B
		k = 16;
		while(k--){
			*dst_p++ = *src_p++;
			*dst_p = *src_p++;
			dst_p += 39*2;
		}
	}


/*		�f�[�^��\������		*/

	type = 0;

	if( type == 0 ) {		//�S�\��?
		Lcd_off();											//���OFF

		Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);		//�S�\��

		Lcd_on();											//���ON
	}
	else{
		Lcd_cr(00, 0xa000, &LCD_WORK1[0][0][0]);					//LCD1��0�s�ڂ�\������B
		Lcd_cr(01, 0xa002, &LCD_WORK1[0][0][0]);					//LCD2��2�s�ڂ�\������B

		Lcd_line(0x00, 4, E_line_bf, &LCD_WORK1[0][0][0]);			//LCD1��4�s�ڂ�\������B
		Lcd_line(0x01, 6, E_line_bf, &LCD_WORK1[0][0][0]);			//LCD2��6�s�ڂ�\������B

		Lcd_draw(0x00, 0, 8*16, 40, &LCD_WORK1[8][0][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+1, 40, &LCD_WORK1[8][1][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+2, 40, &LCD_WORK1[8][2][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+3, 40, &LCD_WORK1[8][3][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+4, 40, &LCD_WORK1[8][4][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+5, 40, &LCD_WORK1[8][5][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+6, 40, &LCD_WORK1[8][6][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+7, 40, &LCD_WORK1[8][7][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+8, 40, &LCD_WORK1[8][8][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+9, 40, &LCD_WORK1[8][9][0]);			//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+10, 40, &LCD_WORK1[8][10][0]);		//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+11, 40, &LCD_WORK1[8][11][0]);		//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+12, 40, &LCD_WORK1[8][12][0]);		//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+13, 40, &LCD_WORK1[8][13][0]);		//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+14, 40, &LCD_WORK1[8][14][0]);		//LCD1��8�s�ڂ�\������B
		Lcd_draw(0x00, 0, 8*16+15, 40, &LCD_WORK1[8][15][0]);		//LCD1��8�s�ڂ�\������B

		Lcd_draw(0x01, 0, 10*16, 40, &LCD_WORK1[10][0][0]);			//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+1, 40, &LCD_WORK1[10][1][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+2, 40, &LCD_WORK1[10][2][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+3, 40, &LCD_WORK1[10][3][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+4, 40, &LCD_WORK1[10][4][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+5, 40, &LCD_WORK1[10][5][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+6, 40, &LCD_WORK1[10][6][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+7, 40, &LCD_WORK1[10][7][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+8, 40, &LCD_WORK1[10][8][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+9, 40, &LCD_WORK1[10][9][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+10, 40, &LCD_WORK1[10][10][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+11, 40, &LCD_WORK1[10][11][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+12, 40, &LCD_WORK1[10][12][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+13, 40, &LCD_WORK1[10][13][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+14, 40, &LCD_WORK1[10][14][0]);		//LCD2��10�s�ڂ�\������B
		Lcd_draw(0x01, 0, 10*16+15, 40, &LCD_WORK1[10][15][0]);		//LCD2��10�s�ڂ�\������B
	}

}



/*** END ***/
