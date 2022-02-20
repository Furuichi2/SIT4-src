/*==========================================================================*/
/*		�e��̋��ʒ�`														*/
/*==========================================================================*/

/***************************************/
/****	��ʃo�[�W�����̒�`		****/
/***************************************/
#define		E_CPUC_VER1	'V'							//CPU-C VER. No.
#define		E_CPUC_VER2	'0'							//CPU-C VER. No.
#define		E_CPUC_VER3	'1'							//CPU-C VER. No.
#define		E_CPUC_VER4	'f'							//CPU-C VER. No.

//�ύX����
//V00a	: 2013-12-20	SIT4-MC
//V00b	: 2014-02-05	
//V01	: 2015-01-23	
//V01a	: 2015-01-28	mm�̲���ϊ��Ή��AӰ��݉׏d����Ή�
//V01	: 2015-02-03	�o�[�W���������ύX
//V01b	: 2015-07-10	���[�V�����C���^�[���b�N�Ή�
//V01c	: 2015/09/20	SUM�ُ�΍�
//V01d	: 2015/09/29	�T�[�{�p��58.�_�C�n�C�g�����inch��mm�ϊ�����Ă����s����C��
//		: 2015/11/26	SUM�ُ�΍�(�^�ް����ӓo�^��)
//V01e	: 2016/02/25	100�i�d�l�ŏC���������e��ǉ��ASIT4��ʏC���d�l�Ή�
//		: 2016/03/17	���Y�ݒ�win�Ő��Y���l�ݒ薳���̎���ýďo�͂�L���Ƃ���B�ް��ݒ��ʂŒP��ton�̎��ɵ��ް۰��/۱�ЯĂɏ����_��ǉ��B
//V01f	: 2016/04/22	���Ӌ@�A���@�\�ǉ��d�l


/***************************************/
/****	�f�[�^�^�̒�`				****/
/***************************************/
typedef	unsigned int	UNi;
typedef	unsigned char	UNb;
typedef	unsigned short	UNs;
typedef	unsigned long	UNl;

typedef	unsigned long	usCount;

/*==========================================================================*/
/*		���e�[�u���̒�`													*/
/*==========================================================================*/
/***************************************/
/****	�J�[�\�����e�[�u����`	****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//���ق�X,Y��
	UNs	DATA_NO;			//���َ�ʔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
	UNs	SV_MAX;				//�ݒ�lð��ٌ�
	UNs	SW_MAX;				//SWð��ٌ�
	UNs	CARA_NO;			//���ٕ\����׎�ʁi���g�p�j
	UNs	MOVE_NO;			//��ʈړ��ԍ�
	UNs	TOK_NO;				//����ԍ�(B0:���ٖ���)
	UNs	YOBI1;				//�\���P
	UNs	YOBI2;				//�\���Q
	UNs	SW56_UP;			//SW56��i��׸�
	UNs	SW5_DN;				//SW5���i��׸�
	UNs	SW6_DN;				//SW6���i��׸�
	UNs	SW5_SUB;			//SW5�ް������ԍ�
	UNs	SW6_SUB;			//SW6�ް������ԍ�
	UNs	YOBI3;				//�\���R
	UNs	AKI;				//��
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//�\��X�ޯĈʒu
	UNs	Y_POS;				//�\��Y�ޯĈʒu
	UNs	M_LEN;				//�\��������(���p��)
	UNs	SIZE;				//�����T�C�Y
	UNs	C_COL;				//�����F
	UNs	B_COL1;				//�w�i�F
	UNs	B_COL2;				//�w�i�F
#endif
	} CSR_TBL_TDEF;


/***************************************/
/****	�ݒ�l���e�[�u����`		****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//�ݒ�l�\����X,Y��
	UNs	AKI;				//��
	UNs	*DATA_ADR;			//�ް��i�[���ڽ
	UNs	SUB_NO;				//���ٰ�ݔԍ�
	UNs	GRP_NO;				//��ٰ�ߔԍ�
	UNs	TOK_FLG;			//�����׸�
	UNs	BYTE_NO;			//�ް��i�[����޲Ē�
	UNs	TEN_POS;			//�����_�̈ʒu
	UNs	CSR_NO;				//���ٔF���ԍ�
	UNs	DSP_NO;				//���ٔF���ԍ����̈ړ�����
	UNs	SAVE_NO;			//�i�[�׸�
	UNs	YOBI_NO;			//�\��
	UNs	AKI2;				//��
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//�\��X�ޯĈʒu
	UNs	Y_POS;				//�\��Y�ޯĈʒu
	UNs	M_LEN;				//�\��������(���p��)
	UNs	SIZE;				//�����T�C�Y
	UNs	C_COL;				//�����F
	UNs	B_COL1;				//�w�i�F
	UNs	B_COL2;				//�w�i�F
#endif
	} SV_TBL_TDEF;


/***************************************/
/****	�����l���e�[�u����`		****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//�����l�\����X,Y��
	UNs	AKI;				//��
	UNs	*DATA_ADR;			//�ް��i�[���ڽ
	UNs	SUB_NO;				//���ٰ�ݔԍ�
	UNs	GRP_NO;				//��ٰ�ߔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
	UNs	TOK_FLG;			//�����׸�
	UNs	BYTE_NO;			//�ް��i�[����޲Ē�
	UNs	TEN_POS;			//�����_�̈ʒu
	UNs	YOBI1;				//�\���P
	UNs	YOBI2;				//�\���Q
	UNs	AKI2;				//��
	UNs	AKI3;				//��
	UNs	AKI4;				//��
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//�\��X�ޯĈʒu
	UNs	Y_POS;				//�\��Y�ޯĈʒu
	UNs	M_LEN;				//�\��������(���p��)
	UNs	SIZE;				//�����T�C�Y
	UNs	C_COL;				//�����F
	UNs	B_COL1;				//�w�i�F
	UNs	B_COL2;				//�w�i�F
#endif
	} PV_TBL_TDEF;


/***************************************/
/****	�r�v�f�[�^���e�[�u����`	****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//�����l�\����X,Y��
	UNs	AKI;				//��
	UNs	*DATA_ADR;			//�ް��i�[���ڽ
	UNs	SUB_NO;				//���ٰ�ݔԍ�
	UNs	GRP_NO;				//��ٰ�ߔԍ��i�ݒ�l�̸�ٰ�ߔԍ��Ɠ����j
	UNs	TOK_FLG;			//�����׸�
	UNs	CHG_NO;				//�ް��i�[��̕ύX�ޯĈʒu
	UNs	CSR_NO;				//���̐ݒ�l�̑����鶰�ٔF���ԍ�
	UNs	DSP_NO;				//���ٔF���ԍ����̈ړ�����
	UNs	CARA_NO;			//�\���p��׸��ԍ�
	UNs	KAN_NO;				//�֘A�޲�
	UNs	*KAN_ADR;			//�֘A���ڽ
//	UNs	YOBI1;				//�\���P(SW_SAVE_NO)
	UNs	SAVE_NO;			//�i�[�׸�
	UNs	YOBI2;				//�\���Q
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//�\��X�ޯĈʒu
	UNs	Y_POS;				//�\��Y�ޯĈʒu
	UNs	M_LEN;				//�\��������(���p��)
	UNs	SIZE;				//�����T�C�Y
	UNs	C_COL;				//�����F
	UNs	B_COL1;				//�w�i�F
	UNs	B_COL2;				//�w�i�F
#endif
	} SW_TBL_TDEF;


typedef struct {				//��ʕʃw�b�_�[���̍\��
	UNb		chr_cnt;			//�������
	UNb		csr_cnt;			//���ٌ�
	UNb		svp_cnt;			//�ݒ�l��
	UNb		pvp_cnt;			//�����l��
	UNb		swl_cnt;			//SW-LAMP��
	UNb		grp_cnt;			//���̨����
	UNb		scr_col;			//��ذݐF
	UNb		rev;				//��
	} GAMENn_HEAD_st;


typedef struct {				//�e�f�[�^�\�����̍\��
	UNs		link_no;			//�ݸNo.
	UNs		rev1;				//�\��
	UNs		bgn_xdot;			//�n�_X
	UNs		bgn_ydot;			//�n�_Y
	UNs		chr_no;				//��׸�No�i���̨���̎��͋���X�j
	UNs		chr_size;			//�������ށi���̨���̎��͋���Y�j
	UNb		chr_col;			//�����F
	UNb		bgnd1_col;			//�w�i�F1
	UNb		bgnd2_col;			//�w�i�F2
	UNb		option;				//��߼��
	UNb		parts_no;			//�߰�No.
	UNb		rev2;				//�\��
	UNs		rev3;				//�\��
	} DISP_INFO_st;


typedef struct {				//���������ݸ��ް��̍\��		//V05o
	UNl		renia1;				//�Ʊ1�ʒu(0.001mm)
	UNl		renia2;				//�Ʊ2�ʒu(0.001mm)
	UNs		angle;				//�p�x(0.1�x)
	UNs		kajyuT;				//�׏d���v(KN)
	UNs		kajyuL;				//�׏d��(KN)
	UNs		kajyuR;				//�׏d�E(KN)
	UNs		seq;				//���ݽ
	UNs		yob1;				//�\��
	UNl		elepw;				//�u���d��(0.01kW)		V06
	} WAVE_SAMP_DATA_ST;


typedef struct {				//����������ް��̍\��			//V05o
	UNl		renia1;				//�Ʊ1�ʒu(0.001mm)
	UNl		renia2;				//�Ʊ2�ʒu(0.001mm)
	UNs		kajyuT;				//�׏d���v(KN)
	UNs		kajyuL;				//�׏d��(KN)
	UNs		kajyuR;				//�׏d�E(KN)
//V06	UNs		yob1;				//�\��
	UNs		elepw;				//1���ٓd��(0.01kWh)	V06
	} WAVE_TRND_DATA_ST;


typedef struct {				//���������ݸ��ް��̍\��		//V05o
	UNs		renia1;				//�Ʊ1�ʒu(0.01mm)
	UNs		renia2;				//�Ʊ2�ʒu(0.01mm)
	UNs		angle;				//�p�x(0.1�x)
	UNs		kajyuT;				//�׏d���v(KN)
	UNs		kajyuL;				//�׏d��(KN)
	UNs		kajyuR;				//�׏d�E(KN)
	UNs		seq1;				//���ݽ
	UNs		seq2;				//���ݽ
	UNs		elepw;				//�u���d��(0.01kW)		V06
	} WAVE_SAMP_DOT_ST;


typedef struct {				//����������ް��̍\��			//V05o
	UNs		renia1;				//�Ʊ1�ʒu(0.01mm)
	UNs		renia2;				//�Ʊ2�ʒu(0.01mm)
	UNs		kajyuT;				//�׏d���v(KN)
	UNs		kajyuL;				//�׏d��(KN)
	UNs		kajyuR;				//�׏d�E(KN)
	UNs		rnaupl;				//������o�ʒu
	UNs		rnadnl;				//�������o�ʒu
	UNs		elepw;				//1���ٓd��(0.01kWh)	V06
	} WAVE_TRND_DOT_ST;



/* �萔��` ---------------------------------------------------------- */
#define		BIT_0		0x0001
#define		BIT_1		0x0002
#define		BIT_2		0x0004
#define		BIT_3		0x0008
#define		BIT_4		0x0010
#define		BIT_5		0x0020
#define		BIT_6		0x0040
#define		BIT_7		0x0080
#define		BIT_8		0x0100
#define		BIT_9		0x0200
#define		BIT_A		0x0400
#define		BIT_B		0x0800
#define		BIT_C		0x1000
#define		BIT_D		0x2000
#define		BIT_E		0x4000
#define		BIT_F		0x8000
#define		BIT_00FF	0x00ff
#define		BIT_FF00	0xff00
#define		BIT_FFFF	0xffff
#define		BIT_OFF		0x0000

#define		BIT_15		0x8000
#define		BIT_14		0x4000
#define		BIT_13		0x2000
#define		BIT_12		0x1000
#define		BIT_11		0x0800
#define		BIT_10		0x0400
#define		BIT_09		0x0200
#define		BIT_08		0x0100
#define		BIT_07		0x0080
#define		BIT_06		0x0040
#define		BIT_05		0x0020
#define		BIT_04		0x0010
#define		BIT_03		0x0008
#define		BIT_02		0x0004
#define		BIT_01		0x0002
#define		BIT_00		0x0001

/***	Key�p�̒�`	***/
#define	E_key_ten_mode	0x01					//ten key mode
#define	E_key_0			0x00					//key code 0
#define	E_key_1			0x01					//key code 1
#define	E_key_2			0x02					//key code 2
#define	E_key_3			0x03					//key code 3
#define	E_key_4			0x04					//key code 4
#define	E_key_5			0x05					//key code 5
#define	E_key_6			0x06					//key code 6
#define	E_key_7			0x07					//key code 7
#define	E_key_8			0x08					//key code 8
#define	E_key_9			0x09					//key code 9
#define	E_key_ten		'.'						//key code .
#define	E_key_cl		0x0f					//key code CL

#define	E_key_ent_mode	0x02					//ENT key mode
#define	E_key_ent		0x01					//key code ENT

#define	E_key_csr_mode	0x03					//���� key mode
#define	E_key_left		0x01					//key code ��
#define	E_key_right		0x02					//key code ��
#define	E_key_down		0x03					//key code ��
#define	E_key_up		0x04					//key code ��

#define	E_key_sw14_mode	0x04					//SW1�`4 key mode
#define	E_key_sw1		0x01					//key code SW1
#define	E_key_sw2		0x02					//key code SW2
#define	E_key_sw3		0x03					//key code SW3
#define	E_key_sw4		0x04					//key code SW4
#define	E_key_sw1_down	0x11					//key code SW1(������)
#define	E_key_sw2_down	0x12					//key code SW2(������)
#define	E_key_sw3_down	0x13					//key code SW3(������)
#define	E_key_sw4_down	0x14					//key code SW4(������)
#define	E_key_sw7_down	0x17					//key code SW7(������)	/* V01z */

#define	E_key_sw56_mode	0x05					//SW5/6 key mode
#define	E_key_sw5		0x05					//key code SW5
#define	E_key_sw6		0x06					//key code SW6
#define	E_key_sw5_down	0x15					//key code SW5(������)
#define	E_key_sw6_down	0x16					//key code SW6(������)

#define	E_key_sw7_mode	0x06					//SW7 key mode
#define	E_key_sw7		0x07					//key code SW7

/***	�\���p�̒�`	***/
#define	E_gmen_bf		15*16*40				//1��ʂ̕\���p�ޯ̧��
#define	E_gmen_size		15*16*40*2				//1��ʂ̕\���p�ޯ̧�����
#define	E_line			40						//1�s�̕\��������
#define	E_line_bf		16*40					//1�s�̕\���p�ޯ̧��
//#define	E_line_size		16*40*2					//1�s�̕\���p�ޯ̧�����
#define	E_line_size		16*40					//1�s�̕\���p�ޯ̧�����
#define	E_next_dot		40						//1�����̎�dot�ʒu��

/***	�����R�[�h�̒�`	***/
#define	E_AS_SP			0x20					//�X�y�[�X�mASCII���ށn
#define	E_AS_SPSP		0x2020					//�X�y�[�X�mASCII���ށn
#define	E_AS_TEN		0x2e					//�h.�h�@ �mASCII���ށn

#define	E_SJ_SP			0x8140					//�X�y�[�X�mS-JIS���ށn
#define	E_SJ_TEN		0x8144					//�h.�h�@ �mS-JIS���ށn
#define	E_SJ_Base		0x821f					//ASCII+0x821f=�O�`�X�mS-JIS���ށn


//���Y�̊Ǘ��ð�ސ�
#define		E_sstg_init		0x00		//���Y[��{]��
#define		E_sstg_set1		0x01		//���Y[���Y�ݒ�1]��
#define		E_sstg_set2		0x02		//���Y[���Y�ݒ�2]��
#define		E_sstg_koud		0x03		//���Y[�P�x�ݒ�]��
#define		E_sstg_gaid		0x04		//���Y[�K�C�_���X�\��]��
#define		E_sstg_schk		0x05		//���Y[�V�[�P���X�`�F�b�N]��
#define		E_sstg_mmon		0x06		//���Y[���[�V�������j�^]��
#define		E_sstg_mcg		0x07		//���Y[���[�V�����O���t]��
#define		E_sstg_deb		0x08		//���Y[�f�o�b�O]��
#define		E_sstg_his		0x09		//���Y[�ُ헚��]��
#define		E_sstg_mmon2	0x0a		//���Y[���[�V�������j�^6�`10]��		/* V01d */
#define		E_sstg_samp		0x0b		//���Y[�T���v�����O]��				/* V01v */
#define		E_sstg_hos		0x0C		//���Y[�␳���j�^]��				/* V01w */
#define		E_sstg_trnd		0x0d		//���Y[�g�����h]��					/* V01z */
#define		E_sstg_pvsmp	0x0e		//���Y[���[�V�����T���v�����O�\��]��	/* V05o */
#define		E_sstg_pvtrd	0x0f		//���Y[���[�V�����g�����h�\��]��		/* V05o */
#define		E_sstg_epm		0x10		//���Y[�d�̓��j�^]��				/* V06  */
#define		E_sstg_seidou	0x11		//���Y[��������WIN]��				/* V06  */
#define		E_sstg_seikan	0x12		//���Y[���Y�Ǘ�WIN]��				/* V06c */
#define		E_sstg_wkstr0	0x13		//���Y[��ƊJ�n1WIN]��				/* V06c */
#define		E_sstg_wkstr1	0x14		//���Y[��ƊJ�n2WIN]��				/* V06c */
#define		E_sstg_wkstr2	0x15		//���Y[��ƊJ�n3WIN]��				/* V06c */
#define		E_sstg_wkstr3	0x16		//���Y[��ƊJ�n4WIN]��				/* V06c */
#define		E_sstg_wkstr4	0x17		//���Y[��ƊJ�n5WIN]��				/* V06c */
#define		E_sstg_wkstr5	0x18		//���Y[��ƊJ�n6WIN]��				/* V06c */
#define		E_sstg_wkstr6	0x19		//���Y[��ƊJ�n7WIN]��				/* V06c */
#define		E_sstg_wkstp0	0x1a		//���Y[��ƏI��0WIN]��				/* V06c */
//�i��̊Ǘ��ð�ސ�
#define		E_kstg_init		0x00		//�i��[��{]��
#define		E_kstg_gaid		0x01		//�i��[�K�C�_���X�\��]��
#define		E_kstg_schk		0x02		//�i��[�V�[�P���X�`�F�b�N]��
#define		E_kstg_scon		0x03		//�i��[�X���C�h����]��
#define		E_kstg_bara		0x04		//�i��[�o�����T����]��
#define		E_kstg_daic		0x05		//�i��[�_�C�N�b�V��������]��
#define		E_kstg_kana		0x06		//�i��[�������^����]��
//�f�[�^�ݒ�̊Ǘ��ð�ސ�
#define		E_dstg_init		0x00		//�f�[�^�ݒ�[��{]��
#define		E_dstg_mset		0x01		//�f�[�^�ݒ�[���[�V�����ݒ�]��
#define		E_dstg_mcg		0x02		//�f�[�^�ݒ�[���[�V�����O���t]��
#define		E_dstg_tms1		0x03		//�f�[�^�ݒ�[�G�W�F�N�^]��
#define		E_dstg_tms2		0x04		//�f�[�^�ݒ�[�~�X�t�B�[�h1]��
#define		E_dstg_tms3		0x05		//�f�[�^�ݒ�[�~�X�t�B�[�h2]��
#define		E_dstg_tms4		0x06		//�f�[�^�ݒ�[���[�^���J��1]��
#define		E_dstg_tms5		0x07		//�f�[�^�ݒ�[���[�^���J��2]��
#define		E_dstg_tms6		0x08		//�f�[�^�ݒ�[���[�^���J������]��
#define		E_dstg_kata		0x09		//�f�[�^�ݒ�[�^�ԍ�]��
#define		E_dstg_name		0x0a		//�f�[�^�ݒ�[�^�ԍ�����]��
#define		E_dstg_memo		0x0b		//�f�[�^�ݒ�[�^�ԍ�����]��
#define		E_dstg_mmon		0x0c		//�f�[�^�ݒ�[�����e�i���X���j�^]��
#define		E_dstg_ksel		0x0d		//�f�[�^�ݒ�[�@�\�I��]��
#define		E_dstg_mset2	0x0e		//�f�[�^�ݒ�[���[�V�������j�^6�`10]��	/* V01d */
#define		E_dstg_ksin		0x0f		//�f�[�^�ݒ�[���U�@�\�ݒ�]��			/* V05r */
#define		E_dstg_cntc		0x10		//�f�[�^�ݒ�[���Ēl�C��]��				/* V06b */
#define		E_dstg_Lang		0x11		//�f�[�^�ݒ�[����ݒ�]��				/* V06m */
#define		E_dstg_wkstr0	0x13		//�f�[�^�ݒ�[��ƊJ�n1WIN]��			/* V06c */
#define		E_dstg_wkstr1	0x14		//�f�[�^�ݒ�[��ƊJ�n2WIN]��			/* V06c */
#define		E_dstg_wkstr2	0x15		//�f�[�^�ݒ�[��ƊJ�n3WIN]��			/* V06c */
#define		E_dstg_wkstr3	0x16		//�f�[�^�ݒ�[��ƊJ�n4WIN]��			/* V06c */
#define		E_dstg_wkstr4	0x17		//�f�[�^�ݒ�[��ƊJ�n5WIN]��			/* V06c */
#define		E_dstg_wkstr5	0x18		//�f�[�^�ݒ�[��ƊJ�n6WIN]��			/* V06c */
#define		E_dstg_wkstr6	0x19		//�f�[�^�ݒ�[��ƊJ�n7WIN]��			/* V06c */
#define		E_dstg_wkstp0	0x1a		//�f�[�^�ݒ�[��ƏI��0WIN]��			/* V06c */
#define		E_dstg_CamAtCal	0x20		//�f�[�^�ݒ�[�J���o�͎������Z]��		/* SIT4-MC */
#define		E_dstg_slatwt	0x21		//�f�[�^�ݒ�[�X���C�h�����ҋ@�@�\]��	/* SIT4-MC */
#define		E_dstg_rep_fix	0x22		//�f�[�^�ݒ�[�J��Ԃ��^���̈�]��		/* SIT4-MC */
//���ѐݒ�̊Ǘ��ð�ސ�
#define		E_ystg_init		0x00		//���ѐݒ�[��{]��
//#define		E_ystg_sys1		0x01		//���ѐݒ�[�d�l�ݒ�1]��
//#define		E_ystg_sys2		0x02		//���ѐݒ�[�d�l�ݒ�2]��
//#define		E_ystg_sys3		0x03		//���ѐݒ�[�d�l�ݒ�3]��
//#define		E_ystg_sys4		0x04		//���ѐݒ�[�d�l�ݒ�4]��
//#define		E_ystg_sys5		0x05		//���ѐݒ�[�d�l�ݒ�5]��
//#define		E_ystg_sys6		0x06		//���ѐݒ�[�d�l�ݒ�6]��
//#define		E_ystg_sys7		0x07		//���ѐݒ�[�d�l�ݒ�7]��
//#define		E_ystg_sys8		0x08		//���ѐݒ�[�d�l�ݒ�8]��
#define		E_ystg_sys1		0x41		//���ѐݒ�[�d�l�ݒ�1]��
#define		E_ystg_sys2		0x42		//���ѐݒ�[�d�l�ݒ�2]��
#define		E_ystg_sys3		0x43		//���ѐݒ�[�d�l�ݒ�3]��
#define		E_ystg_sys4		0x44		//���ѐݒ�[�d�l�ݒ�4]��
#define		E_ystg_sys5		0x45		//���ѐݒ�[�d�l�ݒ�5]��
#define		E_ystg_sys6		0x46		//���ѐݒ�[�d�l�ݒ�6]��
#define		E_ystg_sys7		0x47		//���ѐݒ�[�d�l�ݒ�7]��
#define		E_ystg_sys8		0x48		//���ѐݒ�[�d�l�ݒ�8]��
#define		E_ystg_sys9		0x49		//���ѐݒ�[�d�l�ݒ�9]��			V06m
#define		E_ystg_sysA		0x4a		//���ѐݒ�[�d�l�ݒ�10]��		V06m

#define		E_ystg_cbs1		0x09		//���ѐݒ�[C/B����1]��
#define		E_ystg_cbs2		0x0a		//���ѐݒ�[C/B����2]��
#define		E_ystg_spr1		0x0b		//���ѐݒ�[�������Ұ�1]��
#define		E_ystg_spr2		0x0c		//���ѐݒ�[�������Ұ�2]��
#define		E_ystg_spr3		0x0d		//���ѐݒ�[�������Ұ�3]��
#define		E_ystg_spr4		0x0e		//���ѐݒ�[�������Ұ�4]��
#define		E_ystg_spr5		0x0f		//���ѐݒ�[�������Ұ�5]��
#define		E_ystg_spr6		0x10		//���ѐݒ�[�������Ұ�6]��
#define		E_ystg_scm		0x11		//���ѐݒ�[���Ѷѐݒ�]��
#define		E_ystg_tmct		0x12		//���ѐݒ�[���/����]��
#define		E_ystg_kjyu		0x13		//���ѐݒ�[�׏d�v�ݒ�]��
#define		E_ystg_sura		0x14		//���ѐݒ�[�ײ�ސݒ�]��
#define		E_ystg_dbak		0x15		//���ѐݒ�[�ޯ������ް��ݒ�]��
#define		E_ystg_dini		0x16		//���ѐݒ�[�ް�������]��
#define		E_ystg_dail		0x17		//���ѐݒ�[�޲����ݒ��ߍ�]��		/* V01j */
#define		E_ystg_dair		0x18		//���ѐݒ�[�޲����ݒ��߉E]��		/* V01j */
#define		E_ystg_atuc		0x19		//���ѐݒ�[���͒��ߐݒ�]��			/* V01j */
#define		E_ystg_spr7		0x1a		//���ѐݒ�[�������Ұ�7]��			/* V01v */
#define		E_ystg_spr8		0x1b		//���ѐݒ�[�������Ұ�8]��			/* COP2�Ή� */
#define		E_ystg_spr9		0x1c		//���ѐݒ�[�������Ұ�9]��			/* COP2�Ή� */
#define		E_ystg_sprA		0x1d		//���ѐݒ�[�������Ұ�10]��			/* COP2�Ή� */
#define		E_ystg_sprB		0x1e		//���ѐݒ�[�������Ұ�11]��			/* V06 */
#define		E_ystg_kchg		0x1f		//���ѐݒ�[�@��������ݒ�]��		/* V06p */

/****************************************************************************/
#define		INTROCK_MAX		7					/* ����ۯ���������			*/

/****************************************************************************/

#define		DISP_MN		'-'							//V01 
#define		DISP_PL		' '							//V01 


//��������������	�ȉ��A�r�h�s�|�S�Œǉ�		��������������
#define		PanelWidth		640//dot
#define		PanelHeight		480//dot
#define		WindowHeight	288//dot
#define		PanelDANWidth	336//dot
#define		Window2Height	 96//dot				//V06c

#define		SV_UNDER_COLOR		0			//�ݒ�l�̃A���_�[���C���J�[�\���F�i�}�[���_�j

#define		GAMENn_HEAD_SIZE	 8//byte
//#define		DISP_INFO_SIZE		18//byte
#define		DISP_INFO_SIZE		20//byte

#define		MOJI_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P��������̃w�b�_��
#define		MOJI_DATA_SIZE		16//byte			// �L�����N�e�[�u���̂P��������̃L�����N�^�f�[�^��
#define		CSR_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�J�[�\�����̃w�b�_��
#define		CSR_DATA_SIZE		22//byte			// �L�����N�e�[�u���̂P�J�[�\�����̃L�����N�^�f�[�^��
#define		SWL_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�r�v�|�k�`�l�o���̃w�b�_��
#define		SWL_DATA_SIZE		 8//byte			// �L�����N�e�[�u���̂P�r�v�|�k�`�l�o���̃L�����N�^�f�[�^��
#define		S56_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�r�v�T�E�U���̃w�b�_��
#define		S56_DATA_SIZE		 8//byte			// �L�����N�e�[�u���̂P�r�v�T�E�U���̃L�����N�^�f�[�^��
#define		MES_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃w�b�_��
#define		MES_DATA_SIZE		40//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃L�����N�^�f�[�^��
#define		S56U_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃w�b�_��
#define		S56U_DATA_SIZE		16//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃L�����N�^�f�[�^��
#define		SPE_HEAD_SIZE		 2//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃w�b�_��
#define		SPE_DATA_SIZE		40//byte			// �L�����N�e�[�u���̂P�C���^�[���b�N���̃L�����N�^�f�[�^��

#define		CHAR_MOJI_SIZE		(MOJI_HEAD_SIZE + MOJI_DATA_SIZE)		//byte
#define		CHAR_CSR_SIZE		(CSR_HEAD_SIZE + CSR_DATA_SIZE)			//byte
#define		CHAR_SWL_SIZE		(SWL_HEAD_SIZE + (SWL_DATA_SIZE * 2))	//byte
#define		CHAR_S56_SIZE		(S56_HEAD_SIZE + S56_DATA_SIZE)			//byte
#define		CHAR_MES_SIZE		(MES_HEAD_SIZE + MES_DATA_SIZE)			//byte
#define		CHAR_S56U_SIZE		(S56U_HEAD_SIZE + S56U_DATA_SIZE)		//byte
#define		CHAR_SPE_SIZE		(SPE_HEAD_SIZE + SPE_DATA_SIZE)			//byte

#define		M_char				16//byte			//������ő�16�޲Ē�

#define		All_chr_tbl_top		0xA0070000
#define		All_chr_head_size	16//byte

#define		CTL_CSR_TBL_SIZE	32//;byte
#define		CTL_SVP_TBL_SIZE	28//;byte
#define		CTL_PVP_TBL_SIZE	24//;byte
#define		CTL_SWL_TBL_SIZE	32//;byte
#define		CTL_CHR_TBL_SIZE	16//;byte



#define		COL_BLACK	0x00	/* 00�F��				R:000,G:000,B:000	*/
#define		COL_BLUE	0x01	/* 01�F��				R:000,G:000,B:255	*/
#define		COL_GREEN	0x02	/* 02�F��				R:000,G:255,B:000	*/
#define		COL_LBULE	0x03	/* 03�F���F				R:000,G:255,B:255	*/
#define		COL_RED		0x04	/* 04�F��				R:255,G:000,B:000	*/
#define		COL_PINK	0x05	/* 05�FϾ���ށi��ݸ�j	R:255,G:000,B:255	*/
#define		COL_YELLOW	0x06	/* 06�F��				R:255,G:255,B:000	*/
#define		COL_WHITE	0x07	/* 07�F��				R:255,G:255,B:255	*/
#define		COL_GRAY1	0x08	/* 08�F�D�F1			R:216,G:216,B:216	*/
#define		COL_GRAY2	0x09	/* 09�F�D�F2			R:192,G:192,B:192	*/
#define		COL_GRAY3	0x0A	/* 0A�F�D�F3			R:160,G:160,B:160	*/
#define		COL_GRAY4	0x0B	/* 0B�F�D�F4			R:128,G:128,B:128	*/
#define		COL_ORANGE	0x0C	/* 0C�F��ݼ�			R:255,G:128,B:000	*/	//V05o
#define		COL_YELGRN	0x0D	/* 0D�F����				R:128,G:255,B:000	*/	//V05o
#define		COL_YOBI3	0x0E	/* 0E�F�\��									*/
#define		COL_YOBI4	0x0F	/* 0F�F�\��									*/
#define		COL_EcoM0	0x30	/* 30�FEcoMeter0							*/	//V06 
#define		COL_EcoM1	0x31	/* 31�FEcoMeter1							*/	//V06 
#define		COL_EcoM2	0x32	/* 32�FEcoMeter2							*/	//V06 
#define		COL_EcoM3	0x33	/* 33�FEcoMeter3							*/	//V06 
#define		COL_EcoM4	0x34	/* 34�FEcoMeter4							*/	//V06 
#define		COL_EcoM5	0x35	/* 35�FEcoMeter5							*/	//V06 
#define		COL_EcoM6	0x36	/* 36�FEcoMeter6							*/	//V06 
#define		COL_EcoM7	0x37	/* 37�FEcoMeter7							*/	//V06 

