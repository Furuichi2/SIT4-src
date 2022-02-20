/************************************************************************************/
/*																					*/
/*		���������쏊�a�����@�r�h�s�|�r�@����v���O����								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			����/�ݒ�l/�����l/SW�ް��@�̏��ð��ي֌W								*/
/*																					*/
/************************************************************************************/
/*	�ύX����
*		���{(asm)		�FKatsushige Mamada
*		����(asm -> c)	�FFIT)�c�[		ON:2002-05-22
*
*************************************************************************************/

#include "string.h"								//�W�����C�u����

#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`
#include "ssc_ext.h"							//�Q�Ɗ֐���`
#include "ssc_fram_ext.h"						//�Q�ƕϐ���`
#include "ssc_wk_ext.h"							//�Q�ƕϐ���`
#include "dp_cpuab.h"							//�Q�ƕϐ���`
#include "ssa_opram.h"							//OPRAM�Q�ƕϐ���`
#include "ssc_dpram_seq_ext.h"					//�Q�ƕϐ���`


/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	UNs		swap_iw(void *);						//���ٌ`���̊i�[�ް����擾(word)

/* �O���Q�ƕϐ���` -------------------------------------------------- */
extern	UNs		SEQ_PAR_033, SEQ_PAR_035, SEQ_PAR_041, SEQ_PAR_042, SEQ_PAR_043, SEQ_PAR_044, SEQ_PAR_045, SEQ_PAR_046;
extern	UNs		SEQ_PAR_050;
extern	UNs		SEQ_PAR_101;
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];

/* �萔��` ---------------------------------------------------------- */
extern	const	UNs	SW56_Up_Pos_Tbl_color[13][2];

/* �f�[�^�^��` ------------------------------------------------------ */
/* �v���g�^�C�v�錾 -------------------------------------------------- */
void	CSR_move(UNs, UNs);						//�J�[�\���ړ�

UNs		CSR_pos_chk(void);						//�J�[�\���ʒu���݃`�F�b�N
UNi		CSR_pos_shr_dn(UNs, UNs);				//�J�[�\���ʒu�@������
UNi		CSR_pos_shr_up(UNs, UNs);				//�J�[�\���ʒu�@�㌟��
void	CSR_disp(void);							//�J�[�\���\��
void	CSR_disp_off(void);						//�J�[�\���\������
void	CSR_disp_cls(UNs);						//�d�l�L���ɂ��J�[�\���\���폜
void	CSR_sw56_disp(void);					//�r�v�T�U�L�����N�^�\��

void	SUBERI_out(void);						//�X�x���ʃJ�[�\���M���o��

void	SEI_test_out_sw5(void);					//���Y�ݒ�ýďo�͏���(SW5)
void	SEI_test_out_sw6(void);					//���Y�ݒ�ýďo�͏���(SW6)
void	csr_sw56_sub(UNs);						//SW5/SW6 �ް������ԍ� ����

void	DYHITO_POS_Teaching(void);				//V00m
void	KAJYUU_Teaching(void);					//V01k

void	INS_MOTION(void);						//V06g


/* �����ϐ���` ------------------------------------------------------ */
/* �e�[�u����` ------------------------------------------------------ */
typedef struct {
	UNs	*ADDR;			//�ް��i�[���ڽ
	UNs	BIT_P;			//�ޯ������
	} EJE_SW6_TDEF;

const	EJE_SW6_TDEF	Eje_sw6_Tbl[6]={
			{&SEQ_017_SV, BIT_5},		//�G�W�F�N�^�P�@�^�C�}�d�l�L��
			{&SEQ_017_SV, BIT_8},		//�G�W�F�N�^�Q�@�^�C�}�d�l�L��
			{&SEQ_017_SV, BIT_B},		//�G�W�F�N�^�R�@�^�C�}�d�l�L��
			{&SEQ_017_SV, BIT_E},		//�G�W�F�N�^�S�@�^�C�}�d�l�L��
			{&SEQ_018_SV, BIT_1},		//�G�W�F�N�^�T�@�^�C�}�d�l�L��
			{&SEQ_018_SV, BIT_4}		//�G�W�F�N�^�U�@�^�C�}�d�l�L��
		};

typedef struct {
	UNs	LCD_LINE;			//�s
	UNs	LCD_KETA;			//��
	UNs	LCD_BYTE;			//�޲Ē�
	} CSR_CLS_TDEF;

const	CSR_CLS_TDEF	Csr_disp_cls_Tbl[153] = {
//		�s, ��, ��,
		{00, 00, 00},			//0
		{5,  23, 17},			//1		DW	5*40*16+23,16	; 1/*  ���b�g�J�E���^�P�@�J�[�\���ʒu 	*/
		{7,  23, 17},			//2		DW	7*40*16+23,16	; 2/*  ���b�g�J�E���^�P�@�ݒ蕶�� 	*/
		{8,  23, 17},			//3		DW	8*40*16+23,16	; 3/*  ���b�g�J�E���^�Q�@�J�[�\���ʒu 	*/
		{10, 23, 17},			//4		DW	10*40*16+23,16	; 4/*  ���b�g�J�E���^�R�@�ݒ蕶�� 	*/
		{11, 17, 23},			//5		DW	11*40*16+18,21	; 5/*  �_�C�n�C�g�Œ蕶��	 	*/
		{12, 00, 40},			//6		DW	12*40*16+0,40	; 6/*  �׏d�����\���Œ蕶��		*/
		{5,  00, 40},			//7		DW	5*40*16+0,40	; 7/*  ���b�g�J�E���^�P�@��s		*/
		{6,  00, 40},			//8		DW	6*40*16+0,40	; 8/*  ���b�g�J�E���^�Q�@��s		*/
		{7,  00, 20},			//9		DW	7*40*16+0,20	; 9/*  �������ߕ\��			*/
		{8,  00, 20},			//10	DW	8*40*16+0,20	;10/*  ���Y�������ߕ\��			*/
		{9,  00, 20},			//11	DW	9*40*16+0,20	;11/*  ���Y�������ߕ\��			*/
		{10, 00, 20},			//12	DW	10*40*16+0,20	;12/*  ���Y�������ߕ\��			*/
		{11, 00, 20},			//13	DW	11*40*16+0,20	;13/*  �o�����T���͕\��			*/
		{7,  20, 20},			//14	DW	7*40*16+20,20	;14/*  �׏d�\��				*/
		{8,  20, 20},			//15	DW	8*40*16+20,20	;15/*  �׏d�\��				*/
		{9,  20, 20},			//16	DW	9*40*16+20,20	;16/*  �׏d�\��				*/
		{10, 20, 20},			//17	DW	10*40*16+20,20	;17/*  �׏d�\��				*/
		{11, 20, 20},			//18	DW	11*40*16+20,20	;18/*  �׏d�\��				*/
		{4,  22, 18},			//19	DW	4*40*16+22,18	;19/*  �G�W�F�N�^�P�i�p�\��		*/
		{5,  22, 18},			//20	DW	5*40*16+22,18	;20/*  �G�W�F�N�^�Q�i�p�\��		*/
		{6,  22, 18},			//21	DW	6*40*16+22,18	;21/*  �G�W�F�N�^�R�i�p�\��		*/
		{7,  22, 18},			//22	DW	7*40*16+22,18	;22/*  �G�W�F�N�^�S�i�p�\��		*/
		{8,  22, 18},			//23	DW	8*40*16+22,18	;23/*  �G�W�F�N�^�T�i�p�\��		*/
		{9,  22, 18},			//24	DW	9*40*16+22,18	;24/*  �G�W�F�N�^�U�i�p�\��		*/
		{4,  00, 40},			//25	DW	4*40*16,20		;25/*  �G�W�F�N�^�P�J�[�\���\��		*/
		{5,  00, 40},			//26	DW	5*40*16,20		;26/*  �G�W�F�N�^�Q�J�[�\���\��		*/
		{6,  00, 40},			//27	DW	6*40*16,20		;27/*  �G�W�F�N�^�R�J�[�\���\��		*/
		{7,  00, 40},			//28	DW	7*40*16,20		;28/*  �G�W�F�N�^�S�J�[�\���\��		*/
		{8,  00, 40},			//29	DW	8*40*16,20		;29/*  �G�W�F�N�^�T�J�[�\���\��		*/
		{9,  00, 40},			//30	DW	9*40*16,20		;30/*  �G�W�F�N�^�U�J�[�\���\��		*/
		{4,  00, 40},			//31	DW	4*40*16,40		;31/*  �~�X�t�B�[�h�P�J�[�\���\��	*/
		{6,  00, 40},			//32	DW	5*40*16,40		;32/*  �~�X�t�B�[�h�Q�J�[�\���\��	*/
		{8,  00, 40},			//33	DW	6*40*16,40		;33/*  �~�X�t�B�[�h�R�J�[�\���\��	*/
		{10, 00, 40},			//34	DW	7*40*16,40		;34/*  �~�X�t�B�[�h�S�J�[�\���\��	*/
		{4,  20, 20},			//35	DW	4*40*16+20,20	;35/*  ���[�^���J���P�i�p�\��		*/
		{5,  20, 20},			//36	DW	5*40*16+20,20	;36/*  ���[�^���J���Q�i�p�\��		*/
		{6,  20, 20},			//37	DW	6*40*16+20,20	;37/*  ���[�^���J���R�i�p�\��		*/
		{7,  20, 20},			//38	DW	7*40*16+20,20	;38/*  ���[�^���J���S�i�p�\��		*/
		{8,  20, 20},			//39	DW	8*40*16+20,20	;39/*  ���[�^���J���T�i�p�\��		*/
		{9,  20, 20},			//40	DW	9*40*16+20,20	;40/*  ���[�^���J���U�i�p�\��		*/
		{10, 20, 20},			//41	DW	10*40*16+20,20	;41/*  ���[�^���J���V�i�p�\��		*/
		{11, 20, 20},			//42	DW	11*40*16+20,20	;42/*  ���[�^���J���W�i�p�\��		*/
		{4,  00, 40},			//43	DW	4*40*16,20		;43/*  ���[�^���J���P�J�[�\���\��	*/
		{5,  00, 40},			//44	DW	5*40*16,20		;44/*  ���[�^���J���Q�J�[�\���\��	*/
		{6,  00, 40},			//45	DW	6*40*16,20		;45/*  ���[�^���J���R�J�[�\���\��	*/
		{7,  00, 40},			//46	DW	7*40*16,20		;46/*  ���[�^���J���S�J�[�\���\��	*/
		{8,  00, 40},			//47	DW	8*40*16,20		;47/*  ���[�^���J���T�J�[�\���\��	*/
		{9,  00, 40},			//48	DW	9*40*16,20		;48/*  ���[�^���J���U�J�[�\���\��	*/
		{10, 00, 40},			//49	DW	10*40*16,20		;49/*  ���[�^���J���V�J�[�\���\��	*/
		{11, 00, 40},			//50	DW	11*40*16,20		;50/*  ���[�^���J���W�J�[�\���\��	*/
		{3,  00, 20},			//51	DW	3*40*16,20		;51/*  ��^�N�����p�I��\��		*/
		{5,  00, 20},			//52	DW	5*40*16,20		;52/*  ���^�N�����p�I��\��		*/
		{7,  00, 20},			//53	DW	7*40*16,20		;53/*  �_�C���t�^�I��\��		*/
		{9,  00, 20},			//54	DW	9*40*16,20		;54/*  �_�C�N�b�V�����I��\��		*/
		{3,  20, 20},			//55	DW	3*40*16+20,20	;55/*  �_�C�N�b�V�����������ߕ\��	*/
		{4,  20, 20},			//56	DW	4*40*16+20,20	;56/*  �_�C�N�b�V�����������ߕ\��	*/
		{5,  20, 20},			//57	DW	5*40*16+20,20	;57/*  �_�C�N�b�V�����������ߕ\��	*/
		{7,  20, 20},			//58	DW	7*40*16+20,20	;58/*  �_�C�N�b�V�����������ߕ\��	*/
		{8,  20, 20},			//59	DW	8*40*16+20,20	;59/*  �_�C�N�b�V�����������ߕ\��	*/
		{9,  20, 20},			//60	DW	9*40*16+20,20	;60/*  �_�C�N�b�V�����������ߕ\��	*/
		{2,  20, 20},			//61	DW	2*40*16+20,20	;61/*  �X�L�����^�C���\��		*/
		{6,  00, 40},			//62	DW	6*40*16,20		;62/*  �E�C���h�E��ʃG�W�F�N�^�P�\��	*/
		{7,  00, 40},			//63	DW	7*40*16,20		;63/*  �E�C���h�E��ʃG�W�F�N�^�Q�\��	*/
		{8,  00, 40},			//64	DW	8*40*16,20		;64/*  �E�C���h�E��ʃG�W�F�N�^�R�\��	*/
		{9,  00, 40},			//65	DW	9*40*16,20		;65/*  �E�C���h�E��ʃG�W�F�N�^�S�\��	*/
		{10, 00, 40},			//66	DW	10*40*16,20		;66/*  �E�C���h�E��ʃG�W�F�N�^�T�\��	*/
		{11, 00, 40},			//67	DW	11*40*16,20		;67/*  �E�C���h�E��ʃG�W�F�N�^�U�\��	*/
		{6,  00, 40},			//68	DW	7*40*16+20,20	;68/*  �E�C���h�E��ʃ~�X�t�B�[�h�P�\��	*/
		{7,  00, 40},			//69	DW	8*40*16+20,20	;69/*  �E�C���h�E��ʃ~�X�t�B�[�h�Q�\��	*/
		{8,  00, 40},			//70	DW	9*40*16+20,20	;70/*  �E�C���h�E��ʃ~�X�t�B�[�h�R�\��	*/
		{9,  00, 40},			//71	DW	10*40*16+20,20	;71/*  �E�C���h�E��ʃ~�X�t�B�[�h�S�\��	*/
		{3,  22, 18},			//72	DW	3*40*16+22,18	;72/*  ��^�N�����p�\��			*/
		{4,  22, 18},			//73	DW	4*40*16+22,18	;73/*  ���^�N�����p�\��			*/
		{5,  22, 18},			//74	DW	5*40*16+22,18	;74/*  �_�C���t�^�\��			*/
		{6,  22, 18},			//75	DW	6*40*16+22,18	;75/*  �_�C�N�b�V�����\��		*/
		{7,  22, 18},			//76	DW	7*40*16+22,18	;76/*  �h���\��			*/
		{8,  22, 18},			//77	DW	8*40*16+22,18	;77/*  �X���C�h���ߕ\��			*/
		{6,  00, 18},			//78	DW	6*40*16,18		;78/*  �i��E�C���h�E�X���C�h�\��	*/
		{9,  4,  16},			//79	DW	9*40*16+4,16	;79/*  �X�g�b�s���O�^�C���\��		*/
		{10, 4,  16},			//80	DW	10*40*16+4,16	;80/*  �X�g�b�s���O�^�C���\��		*/
		{1,  20, 20},			//81	DW	1*40*16+20,20	;81/*  ���Y���i����ʌ^����		*/
		{1,  00, 40},			//82	DW	1*40*16,40		;82/*  ���Y���i����ʌ^����		*/
		{12, 00, 22},			//83	DW	12*40*16,22		;83/* V03i,40->22 �i����ʃ���	*/
		{7,  00, 23},			//84	DW	7*40*16,23		;84/*  �i����ʃX���C�h�����J�[�\��	*/
		{9,  00, 23},			//85	DW	9*40*16,23		;85/*  �i����ʃX���C�h�������Y�ݒ�	*/
		{10, 00, 23},			//86	DW	10*40*16,23		;86/*  �i����ʃX���C�h�����i��P�ݒ�	*/
		{11, 00, 23},			//87	DW	11*40*16,23		;87/*  �i����ʃX���C�h�����i��Q�ݒ�	*/
		{9,  00, 40},			//88	DW	9*40*16,40		;88/*  �����e�i���X��ʎ����l�\��	*/
		{10, 00, 40},			//89	DW	10*40*16,40		;89/*  �����e�i���X��ʎ����l�\��	*/
		{11, 00, 40},			//90	DW	11*40*16,40		;90/*  �����e�i���X��ʎ����l�\��	*/
		{12, 00, 20},			//91	DW	12*40*16,20		;91/*  �E�C���h�E��ʃI�[�o�[���[�h�\��	*/
		{11, 20, 20},			//92	DW	11*40*16+20,20	;92/*  �E�C���h�E��ʍ��ڔԍ��O�P�\��	*/
		{6,  00, 20},			//93	DW	6*40*16+0,20	;93/*�@���Y���i���ʕ\���ݒ葬�x�\��	*/
		{3,  00, 40},			//94	DW	3*40*16+0,40	;94/*�@���Y���i���ʕ\���ݒ葬�x�\��	*/
/* V00m */
//		{3,  24, 6},			//95	DW	3*40*16+24,6	;95/*  �V�X�e����ʃI�v�V�����\��	*/
		{2,  32, 3},			//95	DW	3*40*16+24,6	;95/*  �V�X�e����ʃI�v�V�����\��	*/
		{5,  00, 40},			//96	DW	5*40*16+0,40	;96/*	���̉�ʃJ�^�J�i�\��		*/
		{6,  00, 40},			//97	DW	6*40*16+0,40	;97/*	���̉�ʃJ�^�J�i�\��		*/
		{7,  00, 10},			//98	DW	7*40*16+0,10	;98/*	���̉�ʃJ�^�J�i�\��		*/
		{8,  00, 40},			//99	DW	8*40*16,40		;99/*  �~�X�t�B�[�h�T�J�[�\���\��	*/
		{9,  00, 40},			//100	DW	9*40*16,40		;100/*  �~�X�t�B�[�h�U�J�[�\���\��	*/
		{10, 00, 40},			//101	DW	10*40*16,40		;101/*  �~�X�t�B�[�h�V�J�[�\���\��	*/
		{11, 00, 40},			//102	DW	11*40*16,40		;102/*  �~�X�t�B�[�h�W�J�[�\���\��	*/
		{11, 20, 20},			//103	DW	11*40*16+20,20	;103/*10-11  �E�C���h�E��ʃ~�X�t�B�[�h�T�\��*/
		{12, 20, 20},			//104	DW	12*40*16+20,20	;104/*11-12  �E�C���h�E��ʃ~�X�t�B�[�h�U�\��*/
		{3,  20, 20},			//105	DW	3*40*16+20,20	;105/*  �_�C�N�b�V���������\��		*/
		{4,  20, 20},			//106	DW	4*40*16+20,20	;106/*  �_�C�N�b�V�����������\��	*/
		{5,  20, 20},			//107	DW	5*40*16+20,20	;107/*  �_�C�N�b�V���������E�\��	*/
		{7,  20, 20},			//108	DW	7*40*16+20,20	;108/*  �_�C�N�b�V���������\��		*/
		{8,  20, 20},			//109	DW	8*40*16+20,20	;109/*  �_�C�N�b�V���������\��		*/
		{9,  20, 20},			//110	DW	9*40*16+20,20	;110/*  �_�C�N�b�V���������\��		*/
		{4,  00, 40},			//111	DW	4*40*16,40		;111/*  �R�C�����C���ݒ�P		*/
		{5,  00, 40},			//112	DW	5*40*16,40		;112/*  �R�C�����C���ݒ�Q		*/
		{6,  00, 40},			//113	DW	6*40*16,40		;113/*  �R�C�����C���ݒ�R		*/
		{7,  00, 40},			//114	DW	7*40*16,40		;114/*  �R�C�����C���ݒ�S		*/
		{8,  00, 40},			//115	DW	8*40*16,40		;115/*  �R�C�����C���ݒ�T		*/
		{9,  00, 40},			//116	DW	9*40*16,40		;116/*  �R�C�����C���ݒ�U		*/
		{11, 00, 40},			//117	DW	11*40*16,40		;117/*  �R�C�����C���ݒ�i���I�����	*/
		{3,  22, 18},			//118	DW	3*40*16+22,18	;118;/* ���^�������� 			*/
		{4,  22, 18},			//119	DW	4*40*16+22,18	;119;/* �X���C�h���� 			*/
		{5,  22, 18},			//120	DW	5*40*16+22,18	;120;/* ��^�N�����p 			*/
		{6,  22, 18},			//121	DW	6*40*16+22,18	;121;/* ���^�N�����p 			*/
		{7,  22, 18},			//122	DW	7*40*16+22,18	;122;/* �_�C���t�^	 		*/
		{8,  22, 18},			//123	DW	8*40*16+22,18	;123;/* �_�C�N�b�V���� 			*/
		{9,  22, 18},			//124	DW	9*40*16+22,18	;124;/* �h���				*/
		{10, 22, 18},			//125	DW	10*40*16+22,18	;125;/* �l�a				*/
		{11, 22, 18},			//126	DW	11*40*16+22,18	;126;/* �o�����T			*/
		{12, 22, 18},			//127	DW	12*40*16+22,18	;127;/* �޲����ݒ���			*/
		{8,  00, 23},			//128	DW	8*40*16,23		;128/*  �X�g���[�N���ߍ������l		*/
		{6,  00, 40},			//129	DW	6*40*16,40		;129/*�`�c�b���^����			*/
		{11, 17, 23},			//130	DW	11*40*16+17,23	;130/*�`�c�b�_�C�N�b�V�����E����	*/
		{12, 17, 23},			//131	DW	12*40*16+17,23	;131/*�`�c�b�_�C�N�b�V�����E�ݒ�	*/
		{6,  20, 20},			//132	DW	6*40*16+20,20	;132/*  �E�C���h�E��ʃ~�X�t�B�[�h�����\��	*/
		{8,  00, 23},			//133	DW	8*40*16,23		;133/*  �i����ʃX���C�h�������Y�ݒ�	*/
		{6,  20, 20},			//134	DW	6*40*16+20,20	;134/* �_�C�N�b�V���������r�v�\�� 	*/
		{10, 20, 20},			//135	DW	10*40*16+20,20	;135/* �_�C�N�b�V���������r�v�\�� 	*/
		{2,  20, 20},			//136 Ӱ��ݐݒ� ������
		{2,  20, 20},			//137 Ӱ��ݐݒ� �㉝��
		{5,  00, 40},			//138 �~�X�t�B�[�h�P�J�[�\���\��
		{7,  00, 40},			//139 �~�X�t�B�[�h�Q�J�[�\���\��
		{9,  00, 40},			//140 �~�X�t�B�[�h�R�J�[�\���\��
		{11, 00, 40},			//141 �~�X�t�B�[�h�S�J�[�\���\��
		{4,  10, 30},			//142 ���[�^���J���P�ėp�o�͑I���� �\��
		{5,  10, 30},			//143 ���[�^���J���Q�ėp�o�͑I���� �\��
		{6,  10, 30},			//144 ���[�^���J���R�ėp�o�͑I���� �\��
		{7,  10, 30},			//145 ���[�^���J���S�ėp�o�͑I���� �\��
		{8,  10, 30},			//146 ���[�^���J���T�ėp�o�͑I���� �\��
		{9,  10, 30},			//147 ���[�^���J���U�ėp�o�͑I���� �\��
		{10, 10, 30},			//148 ���[�^���J���V�ėp�o�͑I���� �\��
		{11, 10, 30},			//149 ���[�^���J���W�ėp�o�͑I���� �\��
		{2,  16, 8},			//150 Ӱ��ݐݒ� ���]
		{6,  10, 6},			//151 �T�C�N�� �\��					V01  (INS)
		{8,  3, 12},			//152 ���Y�����^�����㍂ �\��		V01  (INS)
		};



/*
********************************************************************************
*  Module Name:		CSR_move
*  Function Name:	�J�[�\���ړ�
*  Input	:		���ُ��	�O�F�z�[���|�W�V����
*								�P�F��������
*								�Q�F���E����
*								�R�F��������
*								�S�F�������
*								�T�F�߂�l�w��
*					����Ͻ�		00�F�ړ�OK
*								ff�F�ړ��֎~
*
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-24
********************************************************************************
*/
void	CSR_move( UNs c_no, UNs c_msk )
{
	UNs		i, j, next_no;

	next_no = c_no;

	if( CSR_CNT == 00 ||								//�J�[�\���Ȃ�
			(next_no != 5 && c_msk == 0xff) ) {			//�߂�l�w��ȊO && �J�[�\���ړ��֎~
		return;
	}
	else{
		SVdata_disp_ent(SV_TBL_POS_NOW);				//�ݒ�r���̕��́A���ɖ߂�����

		DANseq_alloff();								//�i���p�V�[�P���X�n�e�e		//V05q

		do{
			switch(next_no) {
				default:
					next_no = 0xf0;						//�I��
					break;
//100
				case 0x00:		//�z�[���|�W�V����
					CSR_FLG_CNT = 1;					//�����l�Z�b�g
					SV_FLG_CNT = 1;						//�����l�Z�b�g
					SW_FLG_CNT	= 1;					//�����l�Z�b�g
					if( 00 == CSR_pos_chk() ) {			//�J�[�\���ʒu���݃`�F�b�N
						SVSW_tbl_enzan();				//�r�u�r�v�e�[�u���A�h���X���Z
						next_no = 0xff;					//�I��
					}
					else {								//���قȂ�
						CSR_TBL_POS_NOW = 0;			//���̶݂��وʒu���
						next_no = 3;					//���݂��Ȃ��Ƃ��͉��ֈړ�
					}
					break;
//200
				case 0x01:		//��������
					if(SV_FLG_CNT != 0) {					//��߂�H
						SV_FLG_CNT --;						//���Ɉړ�
					}
					if(SV_FLG_CNT == 0) {					//��߂�H
						SV_FLG_CNT = 1;						//�ݒ�l�����l�Z�b�g
						if(CSR_FLG_CNT != 01){				//��Ɉړ��\�H
							i = CSR_FLG_CNT;
							while( next_no < 0xf0 ){
								CSR_FLG_CNT --;
								if( 00 != CSR_pos_chk() ) {	//�J�[�\���ʒu���݃`�F�b�N
									if(CSR_FLG_CNT == 1){	//�܂��������ɃJ�[�\��������H
										CSR_FLG_CNT = i;
										next_no = 0xf0;		//�����ꍇ�͏I���
									}
								}
								else{
									SVSW_tbl_enzan();		//�r�u�r�v�e�[�u���A�h���X���Z
									next_no = 0xff;			//�I��
								}
							}
						}
						else {
							SVSW_tbl_enzan();				//�r�u�r�v�e�[�u���A�h���X���Z
							next_no = 0xff;					//�I��
						}
					}
					else {
						SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
						next_no = 0xff;						//�I��
					}
					break;
//300
				case 0x02:		//���E����
					i = SV_FLG_CNT;
					SV_FLG_CNT ++;										//�E�Ɉړ�
					if(SV_FLG_CNT <= CSR_buff[CSR_TBL_POS_NOW].SV_MAX){	//���ړ��H
						SVSW_tbl_enzan();								//�r�u�r�v�e�[�u���A�h���X���Z
						next_no = 0xff;									//�I��
					}
					else {
						SV_FLG_CNT = 1;									//�ݒ�l�����l�Z�b�g 
						if( CSR_FLG_CNT == CSR_CNT ) {					//���Ɉړ��\�H
							SV_FLG_CNT = CSR_buff[CSR_TBL_POS_NOW].SV_MAX;
							next_no = 0xff;								//�I��
						}
						else {
							j = CSR_FLG_CNT;
							while( next_no < 0xf0 ){
								CSR_FLG_CNT ++;
								if( 00 != CSR_pos_chk() ) {				//�J�[�\���ʒu���݃`�F�b�N
									if(CSR_FLG_CNT >= CSR_CNT){
										SV_FLG_CNT = i;
										CSR_FLG_CNT = j;
										next_no = 0xf0;					//�����ꍇ�͏I���
									}
								}
								else{									//���ق���
									SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z
									next_no = 0xff;						//�I��
								}
							}
						}
					}
					break;
//400
				case 0x03:		//��������
					if( 00 == CSR_pos_shr_dn(CSR_TBL_POS_NOW, next_no)){	//�J�[�\���ʒu�@������
						next_no = 0x05;									//�߂�l�w���
					}
					else{
						next_no = 0xf0;									//�����ꍇ�͏I���
					}
					break;
//500
				case 0x04:		//�������
					if( 00 == CSR_pos_shr_up(CSR_TBL_POS_NOW, next_no)){	//�J�[�\���ʒu�@�㌟��
						next_no = 5;									//�߂�l�w���
					}
					else{
						next_no = 0xf0;									//�����ꍇ�͏I���
					}
					break;
//600
				case 0x05:		//�߂�l�w��
					SVSW_tbl_enzan();									//�r�u�r�v�e�[�u���A�h���X���Z
					next_no = 0xff;										//�I��
					break;
			}
		} while(next_no < 0xf0);

		if(next_no == 0xff ) {
//700
			CSR_disp();								//�J�[�\���\��
			SV_csr_set();							//�ݒ�l�J�[�\��
			CSR_sw56_disp();						//�r�v�T�U�L�����N�^�\��

//2��		SUBERI_out();							//�X�x���ʃJ�[�\���M���o��

			SV_DATA_CHG = 0;						//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
			SV_DISP_BUFF = 0;

			CSR_ON_FLG = 0x00ff;					//�J�[�\���\���t���O�n�m

			DAN_SW14_no_set();						//�i���� SW14�F���ԍ��]��
			DAN_select_diap();						//�i���� �I�����ڃZ���N�g�\��

			Under_grph();							//���i�̃O���t�B�b�N�Z�b�g

			DAN_dispseq_out();						//�i���� ���وʒu���ݽ�o��

			WIN_grph();								//�E�C���h�E��ʏ�O���t�B�b�N�`��
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_pos_chk
*  Function Name:	�J�[�\���ʒu���݃`�F�b�N
*  Input	:		�Ȃ�
*  Return	: 		��00�F���ق���^��00�F���قȂ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
UNs		CSR_pos_chk(void)
{
	UNs		i, r_bf;

	i = CSR_FLG_CNT;
	i --;

	r_bf = 0;										//���ق���

	if( CSR_buff[i].TOK_NO & BIT_0) {				//����ԍ�(B0:���ٖ���)
		r_bf = 01;									//���قȂ�
	}

	return(r_bf);
}


/*
********************************************************************************
*  Module Name:		CSR_pos_shr_dn
*  Function Name:	�J�[�\���ʒu�@������
*  Input	:		�J�[�\�����ð��ق̔ԍ�
*					���ُ��
*  Return	: 		��00�F���ق���^��00�F���قȂ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
UNi		CSR_pos_shr_dn(UNs T_no, UNs c_inf)
{
	UNs		i, xy_no, cnt, r_bf;

	if( CSR_CNT == 00 ) {					//�J�[�\���Ȃ�
		return(0);
	}
	xy_no = (CSR_buff[T_no].XY_POS + 1);		//�s+1
	xy_no &= 0x03ff;							//�s�E����L��

	for( i=xy_no ; (i & 0x000f) < 14 ; i++ ) {					//����A�h���X�Z�b�g
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x03ff)) {			//��v�H
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//����ԍ�(B0:���ٖ���)

					CSR_FLG_CNT = T_no+1;		//�J�[�\���ԍ�����
					SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
					SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
					return(0);					//����I��
				}
			}
		}
	}

	i = xy_no & 0x000f;
	if(c_inf == 0) {								//�z�[���|�W�V�����̎����������猟������
		i = 0x0001;									//�Č������͏ォ�猩��
	}
	for(  ; i < 14 ; i++ ) {									//����A�h���X�Z�b�g
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x000f)) {			//��v�H
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//����ԍ�(B0:���ٖ���)

					CSR_FLG_CNT = T_no+1;		//�J�[�\���ԍ�����
					SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
					SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
					return(0);					//����I��
				}
			}
		}
	}
	return(0xff);

}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
UNi		CSR_pos_shr_dn(UNs T_no, UNs c_inf)
{
	UNs		i, x_pos, y_pos, cnt, r_bf, wk1, wk2, T_no_new;
	UNs		wkx1, wkx2;

	if( CSR_CNT <= 1 ) {					//�J�[�\���Ȃ�
		return(0xff);
	}

	y_pos = (CSR_buff[T_no].Y_POS);			//���݂̃J�[�\���ʒu
	x_pos = (CSR_buff[T_no].X_POS);			//���݂̃J�[�\���ʒu
	wk1 = 0xffff;
	wkx1 = 0xffff;
	T_no_new = T_no;
	for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
	{
		if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//����ԍ�(B0:���ٖ���)
		{
			if ( x_pos <= CSR_buff[T_no].X_POS)
			{
				wkx2 = CSR_buff[T_no].X_POS - x_pos;
				if (wkx1 >= wkx2)
				{
					if ( y_pos < CSR_buff[T_no].Y_POS)
					{
						wk2 = CSR_buff[T_no].Y_POS - y_pos;
						if (wk1 > wk2)
						{
							wkx1 = wkx2;
							wk1 = wk2;
							T_no_new = T_no;
						}
					}
				}
			}
		}
	}
	if ( wk1 == 0xffff) {
		for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
		{
			if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//����ԍ�(B0:���ٖ���)
			{
				if ( y_pos < CSR_buff[T_no].Y_POS)
				{
					wk2 = CSR_buff[T_no].Y_POS - y_pos;
					if (wk1 > wk2)
					{
						wk1 = wk2;
						T_no_new = T_no;
					}
				}
			}
		}
	}
	if ( wk1 != 0xffff) {
		CSR_FLG_CNT = T_no_new+1;	//�J�[�\���ԍ�����
		SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
		SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
		return(0);					//����I��
	}
	return(0xff);
}
#endif

/*
********************************************************************************
*  Module Name:		CSR_pos_shr_up
*  Function Name:	�J�[�\���ʒu�@�㌟��
*  Input	:		�J�[�\�����ð��ق̔ԍ�
*					���ُ��
*  Return	: 		��00�F���ق���^��00�F���قȂ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*������������������	�r�h�s�|�R�p	������������������*/
UNi		CSR_pos_shr_up(UNs T_no, UNs c_inf)
{
	UNs		i, xy_no, cnt, r_bf;

	if( CSR_CNT == 00 ) {					//�J�[�\���Ȃ�
		return(0);
	}
	xy_no = (CSR_buff[T_no].XY_POS - 1);		//�s-11
	xy_no &= 0x03ff;							//�s�E����L��

	for( i=xy_no ; (i & 0x000f) > 0 ; i-- ) {					//����A�h���X�Z�b�g
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x03ff)) {			//��v�H
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//����ԍ�(B0:���ٖ���)

					CSR_FLG_CNT = T_no+1;		//�J�[�\���ԍ�����
					SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
					SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
					return(0);					//����I��
				}
			}
		}
	}

	i = xy_no & 0x000f;
	for(  ; i > 0 ; i-- ) {									//����A�h���X�Z�b�g
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x000f)) {			//��v�H
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//����ԍ�(B0:���ٖ���)

					CSR_FLG_CNT = T_no+1;		//�J�[�\���ԍ�����
					SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
					SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
					return(0);					//����I��
				}
			}
		}
	}
	return(0xff);

}
#else
/*������������������	�r�h�s�|�S�p	������������������*/
UNi		CSR_pos_shr_up(UNs T_no, UNs c_inf)
{
	UNs		i, x_pos, y_pos, cnt, r_bf, wk1, wk2, T_no_new;
	UNs		wkx1, wkx2;

	if( CSR_CNT <= 1 ) {					//�J�[�\���Ȃ�
		return(0xff);
	}

	y_pos = (CSR_buff[T_no].Y_POS);			//���݂̃J�[�\���ʒu
	x_pos = (CSR_buff[T_no].X_POS);			//���݂̃J�[�\���ʒu
	wk1 = 0xffff;
	wkx1 = 0xffff;
	T_no_new = T_no;
	for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
	{
		if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//����ԍ�(B0:���ٖ���)
		{
			if ( x_pos <= CSR_buff[T_no].X_POS)
			{
				wkx2 = CSR_buff[T_no].X_POS - x_pos;
				if (wkx1 >= wkx2)
				{
					if ( y_pos > CSR_buff[T_no].Y_POS)
					{
						wk2 = y_pos - CSR_buff[T_no].Y_POS;			//���݂̃J�[�\���ʒu
						if (wk1 > wk2)
						{
							wkx1 = wkx2;
							wk1 = wk2;
							T_no_new = T_no;
						}
					}
				}
			}
		}
	}
	if ( wk1 == 0xffff) {
		for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
		{
			if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//����ԍ�(B0:���ٖ���)
			{
				if ( y_pos > CSR_buff[T_no].Y_POS)
				{
					wk2 = y_pos - CSR_buff[T_no].Y_POS;			//���݂̃J�[�\���ʒu
					if (wk1 > wk2)
					{
						wk1 = wk2;
						T_no_new = T_no;
					}
				}
			}
		}
	}
	if ( wk1 != 0xffff) {
		CSR_FLG_CNT = T_no_new+1;	//�J�[�\���ԍ�����
		SV_FLG_CNT = 1;				//�J�[�\���ԍ�����
		SW_FLG_CNT = 1;				//�J�[�\���ԍ�����
		return(0);					//����I��
	}
	return(0xff);
}
#endif


/*
********************************************************************************
*  Module Name:		CSR_disp
*  Function Name:	�J�[�\���\��
*  Input	:		
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
void	CSR_disp(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	CSR_disp_color();
#else
	UNs		xy_no, t_no;

	t_no = CSR_TBL_POS_NOW;
	xy_no = CSR_buff[t_no].XY_POS;							//���ق�X,Y��

	if(xy_no == CSR_POS_LAST) {								//�J�[�\���|�W�V�����f�[�^�X�V ?
		return;												//�J�[�\���ʒu���ꏏ�̏ꍇ�͏I��
	}

	if( CSR_POS_LAST != 0xffff &&							//�O��J�[�\���|�W�V�����f�[�^�Ȃ�
			00 == (CSR_buff[t_no].TOK_NO & BIT_0) &&		//����ԍ�(B0:���ٖ���)
			00 != (CSR_POS_LAST >> 10) ) {					//���ْ�=�O�H

		disp_memnot(CSR_POS_LAST, &LCD_WORK2[0][0][0]);		//�\���p�̈�̎w���ް��𔽓]
		Lcd_cr(0x01, CSR_POS_LAST, &LCD_WORK2[0][0][0]);	//��גP�ʕ\��
	}

	if( 00 == (CSR_buff[t_no].TOK_NO & BIT_0) ) {			//����ԍ�(B0:���ٖ���)
		if( 00 != (xy_no >> 10) ) {							//���ْ�=�O�H

			disp_memnot(xy_no, &LCD_WORK2[0][0][0]);		//�\���p�̈�̎w���ް��𔽓]
			Lcd_cr(0x01, xy_no, &LCD_WORK2[0][0][0]);		//��גP�ʕ\��
		}
	}
	else {
		xy_no = 0;
	}
	CSR_POS_LAST = xy_no;								//�J�[�\���|�W�V�����f�[�^�X�V
#endif
}


/*
********************************************************************************
*  Module Name:		CSR_disp_off
*  Function Name:	�J�[�\���\������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
void	CSR_disp_off(void)
{
	UNs		xy_no;
	UNl		adr;
	UNs		*g_p;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	if( CSR_TBL_POS_NOW == 0xff ||					//�O��J�[�\�������H
			CSR_POS_LAST == 0xffff ) {				//�O��J�[�\���|�W�V����
		return;
	}
#else
	if( CSR_TBL_POS_NOW == 0xff ||					//�O��J�[�\�������H
			CSR_BAK_X_POS == 0xffff ) {				//�O��J�[�\���|�W�V����
		return;
	}
#endif
	if(00 == (CSR_buff[CSR_TBL_POS_NOW].TOK_NO & BIT_0)) {	//�J�[�\���\�������H

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		xy_no = CSR_buff[CSR_TBL_POS_NOW].XY_POS;			//���ق�X,Y��
		if(00 == disp_memnot(xy_no, &LCD_WORK2[0][0][0])){	//�\���p�̈�̎w���ް��𔽓]
			Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);			//��גP�ʕ\��
		}
#else
		adr = CSR_TABLE_ADR + ((CSR_buff[CSR_TBL_POS_NOW].CARA_NO-1) * CHAR_CSR_SIZE);		// ��׸�No.���緬׸��ް����i�[����Ă�����ڽ���Z�o
		adr += CSR_HEAD_SIZE;
		g_p = (U2b *)adr;
		disp_moji_s_color(
			CSR_buff[CSR_TBL_POS_NOW].M_LEN,
			CSR_buff[CSR_TBL_POS_NOW].X_POS,
			CSR_buff[CSR_TBL_POS_NOW].Y_POS,
			CSR_buff[CSR_TBL_POS_NOW].C_COL,
			CSR_buff[CSR_TBL_POS_NOW].B_COL1,
			CSR_buff[CSR_TBL_POS_NOW].SIZE,
			g_p,
			LCD_VBASE
			);
		disp_moji_s_rif(
			CSR_buff[CSR_TBL_POS_NOW].M_LEN,
			CSR_buff[CSR_TBL_POS_NOW].X_POS,
			CSR_buff[CSR_TBL_POS_NOW].Y_POS,
			CSR_buff[CSR_TBL_POS_NOW].SIZE
			);
#endif
		CSR_POS_LAST = 0xffff;				//�O��J�[�\���|�W�V�����f�[�^�Ǎ�
		CSR_BAK_X_POS = 0xffff;				/* �O��J�[�\���|�W�V�����f�[�^�N���A */
		CSR_TBL_POS_NOW = 0xff;
		SV_TBL_POS_NOW = 0xff;
		SW_TBL_POS_NOW = 0xff;
	}
}


/*
********************************************************************************
*  Module Name:		CSR_disp_cls
*  Function Name:	�d�l�L���ɂ��J�[�\���\���폜
*  Input	:		�폜�ԍ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-07-15
********************************************************************************
*/
void	CSR_disp_cls(UNs del_no)
{
	UNs		xy_no;

	if(CSR_CLS_FLG != 0){
		xy_no = Csr_disp_cls_Tbl[del_no].LCD_BYTE;
		xy_no <<= 10;
		xy_no |= (Csr_disp_cls_Tbl[del_no].LCD_KETA << 4);
		xy_no |= Csr_disp_cls_Tbl[del_no].LCD_LINE;
		disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//�\���p�̈���w���ް��Őݒ�
	}
}


/*
********************************************************************************
*  Module Name:		CSR_sw56_disp
*  Function Name:	�r�v�T�U�L�����N�^�\��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-27
********************************************************************************
*/
void	CSR_sw56_disp(void)
{
	UNi		i;
	UNs		xy_no, bit_ptn, cr_no, *bf_p;
	UNs		s_bf[4];
	UNs		x_dot, y_dot, len;

	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56��i��׸�
	SW56_upcara_disp(cr_no, 5);						//�L�����N�^���r�v�̈�֊i�[

	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW5_DN;		//SW5���i��׸�
	SW56_dncara_disp(cr_no, 7);						//SW56���i��׸���SW�̈�֊i�[
	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW6_DN;		//SW6���i��׸�
	SW56_dncara_disp(cr_no, 8);						//SW56���i��׸���SW�̈�֊i�[


	/* V01d */
	if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57)	//SW5/SW6 �ް������ԍ�
	{
		if(SV_DANSUU_SRV <= 5)
		{
#if( SIT_TYPE_SEL == TYPE_SIT3 )
			xy_no = 6 << 10;				// �޲Đ�
			xy_no |= 31 << 4;				// ��
			xy_no |= 14;					// �s
			disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);
#else
			s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
			len = 5;
			x_dot = SW56_Up_Pos_Tbl_color[8][0];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
			y_dot = SW56_Up_Pos_Tbl_color[8][1];				//�\���ʒu(��ʂ̍ŏ��̈ʒu)
			disp_moji_s_color(
				len,					/* ��׸��			*/
				x_dot,					/* ���o��X�ʒu		*/
				y_dot,					/* ���o��Y�ʒu		*/
				0,						/* �����F			*/
				GAMENn_HEAD.scr_col,	/* �w�i�F			*/
				0x0202, 				/* ��������			*/
				&s_bf[0],				/* �����i�[���ڽ	*/
				LCD_VBASE				/* �\�����			*/
				);
#endif
		}
	}

	if( (GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30) &&		// V01j
		CSR_buff[CSR_TBL_POS_NOW].SW56_UP == /*91 V01k*/ 96)
	{
//V01m		if (SEQ_024_SV & BIT_4) {								//�׏d����H
		if (SEQ_050_SV & BIT_9) {								//�׏d����H
			SW56_upcara_disp(101, 5);							//SW56��i��׸���101(�׏d)�ɂ���B
		}
	}

//�G�W�F�N�^�r�v�U�\���N���A����
	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW6_SUB;		//SW6�ް������ԍ�
	if(cr_no == 20 ){
		i = 0;										//�G�W�F�N�^�P
	}
	else if(cr_no == 39) {
		i = 1;										//�G�W�F�N�^�Q
	}
	else if(cr_no == 40) {
		i = 2;										//�G�W�F�N�^�R
	}
	else if(cr_no == 41) {
		i = 3;										//�G�W�F�N�^�S
	}
	else if(cr_no == 42) {
		i = 4;										//�G�W�F�N�^�T
	}
	else if(cr_no == 43) {
		i = 5;										//�G�W�F�N�^�U
	}
	else {
		return;
	}

	bf_p = Eje_sw6_Tbl[i].ADDR;
	bit_ptn = Eje_sw6_Tbl[i].BIT_P;
	if(00 == (*bf_p & bit_ptn)) {					//�^�C�}�d�l�L��H
		SW56_dncara_disp(0xff, 0x08);				//SW56���i��׸���SW�̈�֊i�[
	}

}


/*
********************************************************************************
*  Module Name:		SUBERI_out
*  Function Name:	�X�x���ʃJ�[�\���M���o��
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-05-28
********************************************************************************
*/
void	SUBERI_out(void)
{
	UNs		*bf_p, i;

	if(GAMEN_NO==39 || GAMEN_NO==40){
		i = CSR_buff[CSR_TBL_POS_NOW].YOBI3;		//�J�[�\�����݈ʒu�A�h���X
//??		bf_p = CBA_RAM_TOP+0A4H						//�X�x���ʃJ�[�\���ʒu�]��
		*bf_p = i;
	}
	else{
//??		bf_p = CBA_RAM_TOP+0A4H						//�X�x���ʃJ�[�\���ʒu�]��
		*bf_p = 0x0000;
	}
}


/*
********************************************************************************
*  Module Name:		SEI_test_out_sw5
*  Function Name:	���Y�ݒ�ýďo�͏���(SW5)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-19
********************************************************************************
*/
void	SEI_test_out_sw5(void)
{

	csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB);	//SW5/SW6 �ް������ԍ�

}


/*
********************************************************************************
*  Module Name:		SEI_test_out_sw6
*  Function Name:	���Y�ݒ�ýďo�͏���(SW6)
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-19
********************************************************************************
*/
void	SEI_test_out_sw6(void)
{

	csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB);	//SW5/SW6 �ް������ԍ�

}


/*
********************************************************************************
*  Module Name:		csr_sw56_sub
*  Function Name:	SW5/SW6 �ް������ԍ� ����
*  Input	:		SW5/SW6 �ް������ԍ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:FIT)�c�[		ON:2002-06-19
********************************************************************************
*/
void	csr_sw56_sub(UNs sub_no)
{
	UNs		wk_w;
	UNs		i;				/* V00m */
	UNs		xy_no, *g_p;

	if(sub_no >= 0x80){
		return;
	}

	switch(sub_no) {
		default:
//V01l		case 7:				//���ް۰��
		case 31:			//�J�����̑I���i���g�p�j
		case 32:			//�J�����̓o�^�i���g�p�j
		case 51:			//�ޯ����߉�ʌ��ʒu�ύX
			break;

		case 1:				//��ު��1�o��
			SEQ_PAR_035 |= BIT_0;
			break;
		case 2:				//��ު��2�o��
			SEQ_PAR_035 |= BIT_1;
			break;
		case 3:				//��ު��3�o��
			SEQ_PAR_035 |= BIT_2;
			break;
		case 4:				//��ު��4�o��
			SEQ_PAR_035 |= BIT_3;
			break;
		case 5:				//��ު��5�o��
			SEQ_PAR_035 |= BIT_4;
			break;
		case 6:				//��ު��6�o��
			SEQ_PAR_035 |= BIT_5;
			break;

		case 7:				//���ް۰��				// V01l
			SEQ_PAR_035 |= BIT_7;
			break;

		case 8:				//İ�ٶ���1�ر
			PV_TOTLC1_B3 = 0;
			KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
			break;
		case 9:				//İ�ٶ���2�ر
			PV_TOTLC2_B31 = 0;
			KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
			break;

		case 10:			//ۯĶ���1�ر
			PV_LOTCT1_B4 = 0;
			KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
			SEQ_PAR_033 &= ~BIT_0;
			break;
		case 11:			//ۯĶ���2�ر
			PV_LOTCT2_B41 = 0;
			KAT_DATCHG_FLG = 0xff;					//�����l�ύX�׸�
			SEQ_PAR_033 &= ~BIT_1;
			break;

		case 12:			//��^����ߕ�
			SEQ_PAR_041 |= BIT_0;					//�i��@��^�N�����p��
			break;
		case 13:			//��^����ߊJ
			SEQ_PAR_041 |= BIT_1;					//�i��@��^�N�����p�J
			break;
		case 14:			//���^����ߕ�
			SEQ_PAR_041 |= BIT_8;					//�i��@���^�N�����p��
			break;
		case 15:			//���^����ߊJ
			SEQ_PAR_041 |= BIT_9;					//�i��@���^�N�����p�J
			break;

		case 16:			//�޲������~
			SEQ_PAR_042 |= BIT_0;					//�i��@�޲������~
			break;
		case 17:			//�޲����㏸
			SEQ_PAR_042 |= BIT_1;					//�i��@�޲����㏸
			break;

		case 18:			//����ݽ���� �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				PV_LIFE_COUNT[0] = 0;
				PV_LIFE_COUNT[1] = 0;
				PV_LIFE_COUNT[2] = 0;
			}
			break;
		case 19:			//�ғ����Ըر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_TIM1 = 0;
				MCN_MENT_TIM1_10 = 0;
			}
			break;

		case 21:			//����ݽ����1 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT1 = 0;
			}
			break;
		case 22:			//����ݽ���1 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_TIM2 = 0;
				MCN_MENT_TIM2_10 = 0;
			}
			break;
		case 23:			//����ݽ����2 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT2 = 0;
			}
			break;
		case 24:			//����ݽ���2 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_TIM3 = 0;
				MCN_MENT_TIM3_10 = 0;
			}
			break;
		case 25:			//����ݽ����3 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT3 = 0;
			}
			break;
		case 26:			//����ݽ���3 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT6 = 0;
			}
			break;
		case 27:			//����ݽ����4 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT4 = 0;
			}
			break;
		case 28:			//����ݽ���4 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT7 = 0;
			}
			break;
		case 29:			//����ݽ����5 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT5 = 0;
			}
			break;
		case 30:			//����ݽ���5 �ر
			if(SEQ_PAR_101 & BIT_2){				//����ݽ������ؾ��OK�H(1:OK)
				MCN_MENT_CNT8 = 0;
			}
			break;

		case 33:	/*V01j*/		//�޲����݉��~
			SEQ_PAR_042 |= BIT_8;
			break;

		case 34:	/*V01j*/		//�޲����ݏ㏸
			SEQ_PAR_042 |= BIT_9;
			break;

		case 35:	/*V01j*/		//�h��򉺍~
			SEQ_PAR_043 |= BIT_0;
			break;

		case 36:	/*V01j*/		//�h���㏸
			SEQ_PAR_043 |= BIT_1;
			break;

		case 37:			//�ײ�މ��~
			SEQ_PAR_044 |= BIT_0;
			break;

		case 38:			//�ײ�ޏ㏸
			SEQ_PAR_044 |= BIT_1;
			break;

		case 20:			//��ު��1 ��/���
			if(SEQ_017_SV & BIT_5){					//��ު��1 ��ϖ���
				if(SEQ_034_SV & BIT_8){				//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_8;
				}
				else{
					SEQ_034_SV |= BIT_8;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;
		case 39:			//��ު��2 ��/���
			if(SEQ_017_SV & BIT_8){					//��ު��2 ��ϖ���
				if(SEQ_034_SV & BIT_9){				//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_9;
				}
				else{
					SEQ_034_SV |= BIT_9;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;
		case 40:			//��ު��3 ��/���
			if(SEQ_017_SV & BIT_B){				//��ު��3 ��ϖ���
				if(SEQ_034_SV & BIT_A){				//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_A;
				}
				else{
					SEQ_034_SV |= BIT_A;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;
		case 41:			//��ު��4 ��/���
			if(SEQ_017_SV & BIT_E){					//��ު��4 ��ϖ���
				if(SEQ_034_SV & BIT_B){				//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_B;
				}
				else{
					SEQ_034_SV |= BIT_B;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;
		case 42:			//��ު��5 ��/���
			if(SEQ_018_SV & BIT_1){					//��ު��5 ��ϖ���
				if(SEQ_034_SV & BIT_C){			//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_C;
				}
				else{
					SEQ_034_SV |= BIT_C;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;
		case 43:			//��ު��6 ��/���
			if(SEQ_018_SV & BIT_4){					//��ު��6 ��ϖ���
				if(SEQ_034_SV & BIT_D){			//�ύX�ޯ��ް��������ް���蔽�]����
					SEQ_034_SV &= ~BIT_D;
				}
				else{
					SEQ_034_SV |= BIT_D;
				}
				SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?				SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
													//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
				Disp_data_set();					//���ð��ق̔�\������(�쐬)

				FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

				SVdata_disp();						//�ݒ�l���@�\��
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
				SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
				}
			}
			break;

		case 44:			//н̨���1 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_8){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_8;
			}
			else{
				SEQ_036_SV |= BIT_8;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?			SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
												//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
//			Disp_data_set();					//���ð��ق̔�\������(�쐬)

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

//			SVdata_disp();						//�ݒ�l���@�\��
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
//			SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;
		case 45:			//н̨���2 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_9){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_9;
			}
			else{
				SEQ_036_SV |= BIT_9;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?			SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
												//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
//			Disp_data_set();					//���ð��ق̔�\������(�쐬)

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

//			SVdata_disp();						//�ݒ�l���@�\��
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
//			SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;
		case 46:			//н̨���3 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_A){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_A;
			}
			else{
				SEQ_036_SV |= BIT_A;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?			SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
												//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
//			Disp_data_set();					//���ð��ق̔�\������(�쐬)

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

//			SVdata_disp();						//�ݒ�l���@�\��
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
//			SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;
		case 47:			//н̨���4 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_B){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_B;
			}
			else{
				SEQ_036_SV |= BIT_B;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���
//?			SVSW_CHG_FLG &= ~BIT_6;				//��ު�� ��/��� �ް��ύX�H
												//��ު���̕\����ʂ̎��͐ݒ�l���ĕ\��
//			Disp_data_set();					//���ð��ق̔�\������(�쐬)

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

//			SVdata_disp();						//�ݒ�l���@�\��
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//�S�\��
//			SVSW_tbl_enzan();					//�r�u�r�v�e�[�u���A�h���X���Z

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;

		case 48:			//�̾�Ē�������
			OFF_set_start();					//�̾�Ē�������
//V05j			KJ_CHK_CNT1++;						//V05i
			break;
		case 49:			//�޲ݒ�������
			KOUSEI_start();						//�Z������
//V05j			KJ_CHK_CNT2++;						//V05i
			break;

		case 50:			//�ײ�ގ������߽���
			SEQ_PAR_044 |= BIT_6;
			break;

		case 56:	/* V00m */		//�����ʒu����
//V01m			if (SEQ_024_SV & BIT_4)						//�׏d�␳����H	V01k
			if (SEQ_050_SV & BIT_9)						//�׏d�␳����H
			{
//V02a				if( (SEQ_020_SV & BIT_8) && (SEQ_PAR_385 & BIT_7) )		//�׏d�v�L���׏d�v�\���w�ߗL	/* V01m */
				if( (SEQ_020_SV & BIT_8) && (SEQ_PAR_385 & BIT_7) &&
					(CMD_KJTECH_DSP1 != 0) )				//�׏d�v�L���׏d�v�\���w�ߗL	/* V01m */
				{
					i = SV_TBL_POS_NOW;
					KAJYUU_Teaching();						//
					mmon_sv_chg(i);							//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);					//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();						//��]�����ɂ���ް��̊i�[
				}
			}
			else
			{
				if (CMD_DAIPOS_DSP1) {		// 0=��\�� 1=�\��  �\�����Ă���Ƃ����������L��  /* V01c */
					i = SV_TBL_POS_NOW;
					DYHITO_POS_Teaching();					//
					mmon_sv_chg(i);							//�p�x&�ʒu�̐ݒ�l�ύX
					mmon_tchk_disp(0x00);					//Ӱ��݉�ʗp���ð��ق�����&�\��
					mmon_trans_put();						//��]�����ɂ���ް��̊i�[
				}
			}
		break;

		case 52:	/* V01d */		//н̨���5 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_C){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_C;
			}
			else{
				SEQ_036_SV |= BIT_C;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;

		case 53:	/* V01d */		//н̨���6 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_D){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_D;
			}
			else{
				SEQ_036_SV |= BIT_D;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;

		case 54:	/* V01d */		//н̨���7 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_E){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_E;
			}
			else{
				SEQ_036_SV |= BIT_E;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;

		case 55:	/* V01d */		//н̨���8 ���^�A
			KAT_DATCHG_FLG = 0xff;				//�����l�ύX�׸�
			if(SEQ_036_SV & BIT_F){				//�ύX�ޯ��ް��������ް���蔽�]����
				SEQ_036_SV &= ~BIT_F;
			}
			else{
				SEQ_036_SV |= BIT_F;
			}
			SVSW_CHG_FLG |= 0x0028;				//�ް���ݼ� �׸� ���

			FRAM_csum_set();					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//�r�v�b�g�f�f�[�^�\����������
			}
			break;

		case 57:	/* V01d */		//���[�V������ʎ���
			if (SV_DANSUU_SRV > 5) {
				if (disp_stg_sel == E_sstg_mmon) {
					disp_stg_sel = E_sstg_mmon2;		//���Y[���[�V�������j�^6�`10]��
					GAMEN_NO = 6;
					GAMEN_disp();						//��ʕ\��
					CSR_move(03,00);					//���ى��ړ�	/*V01e*/
					Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)	/*V01e*/
					Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)	/*V01e*/
					Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)	/*V01e*/
					Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)	/*V01e*/
				}
				if (disp_stg_sel == E_dstg_mset) {
					disp_stg_sel = E_dstg_mset2;		//�f�[�^�ݒ�[���[�V�������j�^6�`10]��
					GAMEN_NO = 30;
					GAMEN_disp();						//��ʕ\��
					CSR_move(03,00);					//���ى��ړ�	/*V01e*/
					Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)	/*V01e*/
					Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//�s�\��(LCD1)	/*V01e*/
					Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)	/*V01e*/
					Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//�s�\��(LCD2)	/*V01e*/
				}
			}
			break;

		case 58:	/* V01d */		//���[�V������ʑO��
			if (disp_stg_sel == E_sstg_mmon2) {
				disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^6�`10]��
				GAMEN_NO = 3;
				GAMEN_disp();						//��ʕ\��
			}
			if (disp_stg_sel == E_dstg_mset2) {
				disp_stg_sel = E_dstg_mset;			//�f�[�^�ݒ�[���[�V�������j�^6�`10]��
				GAMEN_NO = 28;
				GAMEN_disp();						//��ʕ\��
			}
			break;

		case 61:	/*V01j*/		//MB ��
			SEQ_PAR_043 |= BIT_8;
			break;

		case 62:	/*V01j*/		//MB �o
			SEQ_PAR_043 |= BIT_9;
			break;

		case 63:	/*V01j*/		//���ݻ��������
			SEQ_PAR_044 |= BIT_14;
			break;

		case 64:	/*V01j*/		//�޲����ݒ���-��۰����� ���~
			SEQ_PAR_045 |= BIT_0;
			break;

		case 65:	/*V01j*/		//�޲����ݒ���-��۰����� ���~
			SEQ_PAR_045 |= BIT_1;
			break;

		case 66:	/*V01j*/		//�޲����ݒ���-��۰��������� ����
			SEQ_PAR_045 |= BIT_14;
			break;

		case 67:	/*V01j*/		//�޲����ݒ���-���͒��� ����
			SEQ_PAR_046 |= BIT_6;
			break;

		case 68:	/*V01m*/		//�����^�׏d�؊�
			if (SEQ_024_SV & BIT_4)				//�׏d�␳����H
			{
				SEQ_050_SV ^= BIT_9;
			}
			else
			{
				SEQ_050_SV &= ~BIT_9;
			}
			SVSW_CHG_FLG |= 0x0008;				//�ް���ݼ� �׸� ���
			CAR_mkssi_set();
			GAMEN_disp();

			break;

		case 71:	/* V06g */		//�^�b�`�ʒu�]��
			INS_MOTION();
			break;

	}
}


/*
********************************************************************************
*  Module Name:		DYHITO_POS_Teaching
*  Function Name:	���݂̉����ʒu(���޲ʲ�)���e�B�[�`���O
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2003-01-27 (V00m)
********************************************************************************
*/
void	DYHITO_POS_Teaching(void)
{
	UNs		t_no, z_f, *Dst_p, cnt, flag;
	UNl		cnv_bf, *Dst_lp;
	UNl		wl0, wl1;

	t_no = SV_TBL_POS_NOW;

//V00q	cnv_bf = PVP_DYHITO_POS;						//0.001mm
//V01 	cnv_bf = PV0_DYHITO_POS;						//0.001mm
	cnv_bf = PV0_SLIDE_POS;								//���Y����0.001mm

	if( SEQ_016_SV & BIT_6 ) {					//�P�ʐؑ� mm/INCH �P�ʌn(1:INCH)
		cnv_bf = cnv_mm_inch(cnv_bf,0);			//0.001mm -> 0.001INCH
	}

	Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ

	PV0_KAGENHOS_BAK = *Dst_lp;							//���܂ł̃f�[�^��O��l�Ƃ��ċL��		/* V01w */

	*Dst_lp = cnv_bf;

	FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	flag = 0x01;										//HEX
	z_f = 0x00;											//�[���T�v���X�L��

	SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)

	WIN_grph();											//�E�C���h�E��ʏ�O���t�B�b�N�`��

	Key_sv_tokusyu_chk(t_no);							//�ݒ�l���ꏈ��

	TENKEY_CNT = 0;
	SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//�i�[�׸�

	if(WINDOW_NO == 0) {
	}
	else{
		Lcd_line( 00, 6, E_line_bf, &LCD_WORK1[0][0][0] );	//�s�\��
	}
}


/*
********************************************************************************
*  Module Name:		KAJYUU_Teaching
*  Function Name:	���݂̍ő�׏d���e�B�[�`���O
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2004-07-05 (V01k)
********************************************************************************
*/
void	KAJYUU_Teaching(void)
{
	UNs		t_no, z_f, *Dst_p, cnt, flag, cnv_bf;
//V01t	UNl		*Dst_lp;
	UNs		*Dst_lp, ww0;
	UNl		wl0, wl1;

	t_no = SV_TBL_POS_NOW;

//V02a	cnv_bf = swap_iw(&CLO_LOAD_T);						//�׏d�iTON�j(1word) 
	cnv_bf = PVP_ARA1_KAJ_T2;							//�׏d�iTON�j(1word) 

//V01t	Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ
//V01t	*Dst_lp = (UNl)cnv_bf;
	Dst_lp = (UNs *)SV_buff[t_no].DATA_ADR;				//�ް��i�[���ڽ

//V02a	PV0_KAJYUHOS_BAK = *Dst_lp;							//���܂ł̃f�[�^��O��l�Ƃ��ċL��		/* V01w */
	ww0 = kajyu_chk( Dst_lp, cnv_bf );
	if (ww0 != 0) {
		SEQ_050_SV |= BIT_10;
	}
	else {
		SEQ_050_SV &= ~BIT_10;							// �ύX�傫����������������
	}
	SVSW_CHG_FLG |= 0x0008;				//�i�[�׸�

	*Dst_lp = cnv_bf;

	FRAM_csum_set();									//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬

	flag = 0x01;										//HEX
	z_f = 0x00;											//�[���T�v���X�L��

	SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);	//�ݒ�l�������l �\��(��ۻ��ڽ/����\��)

	WIN_grph();											//�E�C���h�E��ʏ�O���t�B�b�N�`��

	Key_sv_tokusyu_chk(t_no);							//�ݒ�l���ꏈ��

	TENKEY_CNT = 0;
	SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//�i�[�׸�

}


/*
********************************************************************************
*  Module Name:		INS_MOTION
*  Function Name:	�^�b�`�ʒu�̃��[�V������}������
*  Input	:		�Ȃ�
*  Return	: 		�Ȃ�
*  Note		:
*
*  �� ��	:Shima		ON:2011-07-28 (V06g)
********************************************************************************
*/
void INS_MOTION(void)
{
	UNs	i, c;
	UNs	AGL[10];
	UNl	POS[10];
	UNs	SPD[10];
	UNs	TIM[10];

	UNs	*Src_s;
	UNl	*Src_l;

	UNs	*Dst_AGL, *Dst_SPD, *Dst_TIM;
	UNl	*Dst_POS;

	if ( (1<=PVP_MOTINS_DAN) && (PVP_MOTINS_DAN<=9) ) {		//���[�V�����}��(C/B->HMI) �i��(1�`9)

		Src_s = &SV_1DANDEG_SRV;
		for (i=0; i<10; i++, Src_s++) {
			AGL[i] = *Src_s;
		}
    
		Src_l = &SV_1DANPOS_SRV;
		for (i=0; i<10; i++, Src_l++) {
			POS[i] = *Src_l;
		}
    
		Src_s = &SV_1DANSPD_SRV;
		for (i=0; i<10; i++, Src_s++) {
			SPD[i] = *Src_s;
		}
    
		Src_s = &SV_1DANTIM_SRV;
		for (i=0; i<10; i++, Src_s++) {
			TIM[i] = *Src_s;
		}

		Dst_AGL = &SV_1DANDEG_SRV;
		Dst_POS = &SV_1DANPOS_SRV;
		Dst_SPD = &SV_1DANSPD_SRV;
		Dst_TIM = &SV_1DANTIM_SRV;

		for(i=0; i<9; i++) {
			if (PVP_MOTINS_DAN == (i+1)) {
				break;
			}
			*Dst_AGL = AGL[i];
			*Dst_POS = POS[i];
			*Dst_SPD = SPD[i];
			*Dst_TIM = TIM[i];
			Dst_AGL++;
			Dst_POS++;
			Dst_SPD++;
			Dst_TIM++;
		}

		/* �}�� */
		*Dst_AGL = PVP_MOTINS_AGL;		//���[�V�����}��(C/B->HMI) �p�x(�����_1���f�[�^)
		*Dst_POS = PVP_MOTINS_POS;		//���[�V�����}��(C/B->HMI) �ʒu(�����_3���f�[�^)
		*Dst_SPD = SPD[i];
		*Dst_TIM = 1;					//0.01sec
		Dst_AGL++;
		Dst_POS++;
		Dst_SPD++;
		Dst_TIM++;

		for(; i<9; i++) {
			*Dst_AGL = AGL[i];
			*Dst_POS = POS[i];
			*Dst_SPD = SPD[i];
			*Dst_TIM = TIM[i];
			Dst_AGL++;
			Dst_POS++;
			Dst_SPD++;
			Dst_TIM++;
		}

		SV_DANSUU_SRV++;					//�i��+1

		mmon_trans_put();					//��]�����ɂ���ް��̊i�[

		disp_stg_sel = E_sstg_mmon;			//���Y[���[�V�������j�^]��
		GAMEN_NO = 3;
		GAMEN_disp();						//��ʕ\��

	}

}



/*** END ***/
