
/* �O���Q�Ɗ֐���` -------------------------------------------------- */
extern	void Lcd_all(UNs, UNs, UNs *);					//�S�\��
extern	void Lcd_line(UNs, UNs, UNs, UNs *);			//�s�\��
extern	void Lcd_cr(UNs, UNs, UNs *);					//��גP�ʕ\��
extern	void Lcd_draw(UNs, UNs, UNs, UNs, UNs *);		//�ޯĕ\��
extern	void Lcd_on(void);								//���ON
extern	void Lcd_off(void);								//���OFF
extern	void Lcd_contrast_chage(UNs);					//LCD�P�x�ݒ�
extern	UNb *	kan_rom_set(UNs);						//�����q�n�l���f�[�^�Z�b�g

/***	ssc_if_disp.c	***/
extern	void	GENGO_chg(UNi);							//��Q�J����ؑւ�����
extern	void	Disp_line(UNs, UNs, UNs, UNs);			//��ʕ\���p 1�s�\��
extern	void	Disp_moji(UNs, UNs *, UNs);				//�����\��
extern	void	Disp_char(UNs, UNs, UNs, UNs *, UNs);	//�ޯĕ\��
extern	void	disp_all_s(UNs, UNs, UNs);				//�S��ʕ\���p�������ށ��ޯĕϊ�
extern	void	disp_line_s(UNs, UNs *, UNs *);			//1�s�\���p�������ށ��ޯĕϊ�
extern	void	disp_memset(UNs, UNs *, UNs);			//�\���p�̈���w���ް��Őݒ�
extern	UNi		disp_memnot(UNs, UNs *);				//�\���p�̈�̎w���ް��𔽓]
extern	void	disp_moji_s(UNs , UNs *, UNs *, UNi);	//�����\���p�������ށ��ޯĕϊ�
extern	UNi		code_dot_cnv(UNs, UNb *, UNi);			//�������ށ��ޯĕϊ�
extern	UNs *	disp_adr_shr(UNs, UNs, UNs);			//��ʂ̷�׸����ڽ�̎Z�o
extern	void	disp_char_cpy(UNs, UNs, UNs, UNs *, UNs);	//��ʂ̷�׸��̺�߰
extern	UNs *	mess_adr_shr(UNi);						//���b�Z�[�W��ʃL�����N�^�A�h���X����
extern	void	BCD_ASCII(UNl, UNb *);					//BCD��ASCII�@�ϊ�
extern	UNl		BCD_HEX4(UNl);							//BCD��HEX�@�ϊ�
extern	UNl		HEX_BCD4(UNl);							//HEX��BCD�@�ϊ�
extern	void	Ascii_Sjis(UNs, UNb *, UNs *);			//Ascii���� �� �S�pS-Jis���ށ@�ϊ�
extern	UNs		jiscnv(UNs);							//�V�t�g�i�h�r���i�h�r�ϊ�
extern	void	memset_word(UNs *, UNs, UNs);			//�w��̈���w���ް��ɂ�ܰ�ޒP�ʂŐݒ�
extern	void	memset_long(UNl *, UNl, UNs);			//�w��̈���w���ް��ɂ�long�P�ʂŐݒ�			//V06a
extern	void	memcpy_word(UNs *, UNs *, UNs);			//�w��̈���w��̈��ɂ�ܰ�ޒP�ʂŃR�s�[

/***	ssc_SvPv.c	***/
extern	void	SVdata_disp(void);						//�ݒ�l���@�\��
extern	void	SVdata_disp_ent(UNs);					//�ݒ�r���̕��́A���ɖ߂�����
extern	void	SV_csr_set(void);						//�ݒ�l�J�[�\���\��
extern	void	SV_csr_reset(UNs);						//�ݒ�l�J�[�\������
extern	void	PVdata_disp_all(void);					//�S�@�����l���@�\��
extern	UNs		PVdata_disp(UNs, UNs );					//�����l���@�\��
extern	void	SVPV_data_disp(UNl, void *, UNs, UNs);	//�ݒ�l�������l �\��
extern	void	Count_hosei_csr_on(UNs);				//�J�E���^�␳�̎����l���]����
extern	void	SVSW_tbl_enzan(void);					//�r�u�r�v�e�[�u���A�h���X���Z
extern	void	kyoutyou_set(UNs);						//���������ϊ�

/***	ssc_Sw.c	***/
extern	void	SWchg_ent(void);						//SW CHG �f�[�^ ENT
extern	void	SWchg_move_ent(void);					//SW CHG�̈ړ� �ް�ENT
extern	void	SWchg_mmon_ent(void);					//Ӱ��ݗp SW�ް� ENT
extern	void	SWchg_bit_chk(void);					//�r�v�f�[�^���͎������I�����ۏ���
extern	void	SWchg_disp_pv_any(void);				//SW�ް��@�����l �\��
extern	void	SWchg_disp_pv(void);					//�r�v�b�g�f�f�[�^�\����������
extern	void	SWchg_disp(void);						//�r�v�f�[�^���@�\��
extern	void	SWchg_disp_gaibu(void);					//SW�ް����@�\��
extern	void	SWchg_disp_one(UNi);					//1�r�v�f�[�^���@�\��
extern	void	SWchg_set(UNi, UNs, UNs *);				//�r�v�L�����N�^�\������
extern	void	SWchg_set_dan(UNi, UNs *);				//�r�v�L�����N�^�\������(�i���p)
extern	void	SWchg_set_op(UNi, UNs *);				//�r�v�L�����N�^�\������(�I�t�Z�b�g���ߗp)
extern	void	SWchg_dispset(UNi);						//�J�[�\�����]�\������
extern	void	SWchg_dispset_dan(UNi);					//�J�[�\�����]�\������(�i���p)
extern	void	Under_grph(void);						//���i�̃O���t�B�b�N�Z�b�g
extern	void	WIN_grph(void);							//�E�C���h�E��ʏ�O���t�B�b�N�`��
extern	void	SW16data_onset(UNs, UNi);				//�r�v�P�`�U�̔��]�w����s��
extern	void	SW56_upcara_disp(UNs, UNs);				//�r�v�T�U��i�L�����N�^���r�v�̈�֊i�[
extern	void	SW56_dncara_disp(UNs, UNs);				//SW56���i��׸���SW�̈�֊i�[
extern	void	SW56dn_clear(UNs);						//SW��׸����ް��߰��ݸر

/***	ssc_Csr.c	***/
extern	void	CSR_move(UNs, UNs);						//�J�[�\���ړ�
extern	UNs		CSR_pos_chk(void);						//�J�[�\���ʒu���݃`�F�b�N
extern	UNi		CSR_pos_shr_dn(UNs, UNs);				//�J�[�\���ʒu�@������
extern	UNi		CSR_pos_shr_up(UNs, UNs);				//�J�[�\���ʒu�@�㌟��
extern	void	CSR_disp(void);							//�J�[�\���\��
extern	void	CSR_disp_off(void);						//�J�[�\���\������
extern	void	CSR_disp_cls(UNs);						//�d�l�L���ɂ��J�[�\���\���폜
extern	void	CSR_sw56_disp(void);					//�r�v�T�U�L�����N�^�\��
extern	void	SUBERI_out(void);						//�X�x���ʃJ�[�\���M���o��
extern	void	SEI_test_out_sw5(void);					//���Y�ݒ�ýďo�͏���(SW5)
extern	void	SEI_test_out_sw6(void);					//���Y�ݒ�ýďo�͏���(SW6)
extern	void	csr_sw56_sub(UNs);						//SW5/SW6 �ް������ԍ� ����

/***	ssc_key.c	***/
extern	void	Key_mng(void);							//�����͊m��
extern	void	Key_Ten_in(UNs );						//Ten KEY����
extern	void	Key_Ent_sv(void);						//�ݒ�l�̊m��
//2014/08/27	extern	void	Key_sv_limt_chk(UNs, UNl *);			//�ݒ�l�̏㉺���`�F�b�N
extern	UNs		Key_sv_limt_chk(UNs, UNl *);			//�ݒ�l�̏㉺���`�F�b�N
extern	void	Key_sv_tokusyu_chk(UNs);				//�ݒ�l�̓��ꏈ��
extern	void	dansuu_zero_set(void);					//�т̒i ����00�ݒ�

/***	ssc_disp.c	***/
extern	void	GAMEN_disp(void);						//��ʕ\��
extern	void	WIN_gamen_disp(void);					//����޳��ʕ\��
extern	void	GAMEN_base_disp(void);					//�x�[�X��ʕ\��
extern	void	GAMEN_no_chg(void);						//��ʂm���D�ύX
extern	void	GAMEN_cls(void);						//��ʃf�[�^�N���A
extern	void	WIN_gamen_cls(void);					//����޳��ʃf�[�^�N���A
extern	void	DISP_after_csr(void);					//��ʕ\���̃J�[�\���㏈��
extern	void	DISP_after(void);						//��ʕ\���̌㏈��
extern	void	WIN_disp_after(void);					//����޳��ʕ\���̌㏈��
extern	void	WIN_disp_after2(void);					//����޳��ʕ\���̌㏈��2
extern	void	Alltbl_set(void);						//���ð��ق̍쐬
extern	void	Wintbl_set(void);						//����޳��ʂ̏��ð��ق̍쐬
extern	void	Disp_data_set(void);					//���ð��ق̔�\������(�쐬)
extern	void	gamen_tbl_set(void);					//��ʂ̏��ð��ق̔�\������(�쐬)
extern	void	win_tbl_set(void);						//����޳��ʂ̏��ð��ق̔�\������(�쐬)

/***	ssc_disp1.c	***/
extern	void	DATA_svsw(UNs, UNs);					//
extern	UNi		MIS_check(void);						//�~�X�t�B�[�h�L���`�F�b�N
extern	UNi		ROT1_check(void);						//���[�^���J���P�`�W�L���`�F�b�N
extern	UNi		ROT2_check(void);						//���[�^���J���X�`�P�U�L���`�F�b�N
extern	UNi		ROT3_check(void);						//���[�^���J���P�V�`�Q�O�L���`�F�b�N
extern	UNi		EJE_check(void);						//�G�W�F�N�^�L���`�F�b�N
extern	void	DISP_cam_csr_name(void);				//�J���J�[�\�����̕\��
extern	void	CAM_next_cls(UNs);						//�ݒ�l�̎��̃L�����N�^���X�y�[�X
extern	void	LENG_svpv(UNs, UNs);					//�����_�̕ύX(�ݒ�l&�����l)
extern	void	CSR_cls(UNs, UNs, UNs);					//���ُ��ð��ق̔�\�� �ݒ�
extern	void	SV_cls(UNs, UNs, UNs);					//�ݒ�l���ð��ق̔�\�� �ݒ�
extern	void	PV_cls(UNs, UNs, UNs);					//�����l���ð��ق̔�\�� �ݒ�
extern	void	SW_cls(UNs, UNs, UNs);					//SW�ް����ð��ق̔�\�� �ݒ�
extern	void	SW_cls_disp(UNs, UNs, UNs);				//SW�ް����ð��ق̔�\��/�\�� �ݒ�						2014/03/17
extern	void	EJE_grp(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);	//��ު���p�ݒ�l���ð��ق̔�\�� �ݒ�
extern	void	EJE_csr(UNs, UNs, UNs, UNs, UNs, UNs);	//��ު���p���ُ��ð��ق̐ݒ�l����������
extern	void	EJE_sw(UNs, UNs, UNs);					//��ު���pSW�ް����ð��ق̏�������
extern	void	ROT_cam_sv(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);		//۰�ضїp�ݒ�l���ð��ق̏�������
extern	void	ROT_cam_sw(UNs, UNs, UNs, UNs, UNs);	//۰�ضїpSW�ް����ð��ق̏�������
extern	void	ROT_cam_csr(UNs, UNs, UNs, UNs, UNs, UNs, UNs);			//۰�ضїp���ُ��ð��ق̏�������
extern	void	MIS_sv(UNs, UNs, UNs);					//н̨��ޗp�ݒ�l���ð��ق̔�\�� �ݒ�
extern	void	MIS_csr(UNs, UNs, UNs, UNs, UNs);		//н̨��ޗp���ُ��ð��ق̏�������
extern	void	ATU_svpv(UNs, UNs);						//�ݒ�l���ð��ق̕ύX
extern	void	DANsel_csr(UNs, UNs, UNs, UNs);			//н̨��ޗp���ُ��ð��ق̏�������
extern	void	DAN_sel(UNs *, UNs, UNs, UNs);			//�i���p�@�e�I���̏�������
extern	void	DAN_csr_set(void);						//�i���ʁ@�\���������J�E���^
extern	void	KAT_cls(UNs, UNs, UNs, UNs);			//�^�ް��̎����l���ð��ق̔�\�� �ݒ�
extern	void	MEMO_cls(UNs, UNs, UNs, UNs);			//�����̎����l���ð��ق̔�\�� �ݒ�
extern	void	PVdata_non_sub(void);					//�����l���ð��ق̔�\�� �ݒ�
extern	void	SCAN_kat_cls(void);						//
extern	void	NAME_cls_sub(void);						//��ꌾ��@���ł̔�\��
extern	void	MISS_swcara(void);						//н̨���SW�\����א؊����̔�\��
extern	void	MISS_swcara_win(void);					//н̨���SW�\����א؊����̔�\��(����޳�p)
extern	void	mmon_tbl_cls(UNs);						//Ӱ��ݐݒ�@���ð��ق̔�\�� �ݒ�
extern	void	mmon_tbl_open(UNs);						//Ӱ��ݐݒ�@���ð��ق̕\�� �ݒ�
extern	void	grpno_sv_cls(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̔�\�� �ݒ�
extern	void	grpno_sv_open(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̕\�� �ݒ�
extern	UNs		grpno_sv_srch(UNs);						//��ٰ�ߔԍ� �ݒ�l���ð��ق̻��

/***	ssc_Seisa.c	***/
extern	void	dsp_Seisan(void);						//���Y�̊Ǘ�
extern	void	sw34_gamen_01(UNs);						//���Y[��{]��SW3�4�̏���
extern	void	sw56_gamen_01(UNs);						//���Y[��{]��SW5�6�̏���
extern	void	sw56_window_02(UNs);					//���Y[�P�x�ݒ�]��SW5�6�̏���
extern	void	kido_data_set(void);					//�P�x�\�� & �f�[�^�쐬
extern	void	mmon_kaiten_chg(void);					//��]�����ɂ��ݒ�l �؊���
extern	void	mmon_sv_chg(UNs);						//�p�x&�ʒu�̐ݒ�l�ύX
extern	void	mmon_tchk_disp(UNi);					//Ӱ��݉�ʗp���ð��ق�����&�\��
extern	void	mmon_sel_chk(void);						//Ӱ��݂̕����I������
extern	void	mmon_trans_get(void);					//��]�����ɂ���ް��̎擾
extern	void	mmon_trans_put(void);					//��]�����ɂ���ް��̊i�[
extern	UNl		cnv_mi_mi_sur(UNl);						//�P�ʐؑ�(mm/INCH��mm/INCH)
extern	UNl		cnv_mi_mi(UNl);							//�P�ʐؑ�(mm/INCH��mm/INCH)
extern	UNl		cnv_mm_inch(UNl, UNi);					//�P�ʐؑ�(mm��mm/INCH)
extern	UNl		cnv_inch_mm(UNl, UNi);					//�P�ʐؑ�(mm/INCH��mm)
extern	UNl		cnv_um_uinch(UNl um_bf);				//�P�ʐؑ�(um��um/uINCH)
extern	UNl		cnv_uinch_um(UNl uinch_bf);				//�P�ʐؑ�(um/uINCH��um)
extern	void	SEI_csr_ichk(void);						//���Y�J�[�\���ʒu������
extern	void	SEI_csr_mng(void);						//���Y[��{]�̐�p�@�J�[�\���ړ��Ǘ�

/***	ssc_Dandor.c	***/
extern	void	dsp_Dandori(void);						//�i��̊Ǘ�
extern	void	sw56_gamen_07(UNs);						//�i��[��{]��SW5�6�̏���
extern	void	DANseq_sw56off(UNs);					//�i���p���ݽOFF
extern	void	DAN_select_ent(UNs);					//�i����ʑI�����ڃZ���N�g����
extern	void	DANseq_alloff(void);					//�i���p�V�[�P���X�n�e�e
extern	void	DAN_select_diap(void);					//�i���� �I�����ڃZ���N�g�\��
extern	void	DAN_sel_cara(UNs);						//�i���I�����ڃL�����N�^�\��
extern	void	DAN_SW14_no_set(void);					//�i���� SW14�F���ԍ��]��
extern	void	DAN_dispseq_out(void);					//�i���� ���وʒu���ݽ�o��
extern	void	DAN_csr_ichk(void);						//�i��J�[�\���ʒu������
extern	void	DAN_csr_mng(void);						//�i��[��{]�̐�p�@�J�[�\���ړ��Ǘ�
extern	void	SURA_sv_chg(void);						//�X���C�h�������߂r�u�ύX����

/***	ssc_Dataset.c	***/
extern	void	dsp_Dataset(void);						//�f�[�^�ݒ�̊Ǘ�
extern	void	Data_sel_cam(void);						//���ݸސݒ�ւ̑J��(��ު��/н̨���/۰�ض�)
extern	void	SHARCH_gamen_15(void);					//�������͎��̉�ʈړ�
extern	void	SW56_gamen_15(void);					//�^�ް���ʁ@SW56����
extern	void	MEMO_data_write(void);					//�^�ް� �ӏ���
extern	void	KAT_data_read(void);					//�^�ް� �Ǎ�
extern	void	KAT_data_write(void);					//�^�ް� ����
extern	void	KAT_read_sura_chk(void);				//�^�f�[�^�Ǎ��ݎ��X���C�h�ݒ�l�`�F�b�N
extern	void	NAME_csr_mng(void);						//���̉�ʃJ�[�\������
extern	void	KATname_inp(void);						//�^���� ���͏���
extern	void	KATname_cls(void);						//�^���� ��������
extern	void	KATname_ref(UNs, UNs *);				//�J�����̃��t���b�V��
extern	void	CSR_disp_on(UNs);						//����ʔ��]
extern	UNs		NAME_leng_chk(UNb *, UNs);				//���̂̓��͕��������`�F�b�N
extern	void	CAMname_inp(void);						//�J������ ���͏���
extern	void	CAMname_cls(void);						//�J������ ��������
extern	UNi		CAMname_inp_chk(void);					//�J�����̓��͉`�F�b�N
extern	void	CAMname_touroku(void);					//�J�����̓o�^
extern	void	CAMname_sw_ent(void);					//�ėp�o�͑I��
extern	void	CAM_name_ref(void);						//۰�ضєėp�I����ʂɑΉ������і��̂̍X�V

/***	ssc_Sysset.c	***/
extern	void	dsp_Sysset(void);						//�V�X�e���ݒ�̊Ǘ�
extern	void	Sys_sel_dstg_mmon(void);				//�f�[�^�ݒ�[�����e�i���X���j�^]��
extern	void	Sys_sel_dstg_ksel(void);				//�f�[�^�ݒ�[�@�\�I��]��
extern	void	Sys_dsp_move(void);						//��ʂƊǗ��ð�ނ̈ړ�
extern	void	CAR_mkssi_set(void);					//�P�ʐ؊��ް��i�[����
extern	void	INI_data_set(void);						//�f�[�^������

/***	ssc_option.c	***/
extern	void	OPDP_trans_chk(void);					//OP-DPRAM �� FRAM �ް��]�� & ��������
extern	void	OPdata_set_kaku(void);					//��߼�� �ް��]������
extern	void	OPdata_sys_kaku(void);					//��߼�݂ɼ���ׂ��i�[
extern	void	OP_pvdata_smp(void);					//��߼�ݎ����l�ް������ݸޏ���
extern	void	POSdata_set_kaku(void);					//�߼޼�Ű �ް��]������
extern	void	OFF_set_start(void);					//�̾�Ē�������
extern	void	OFF_set_start_mng(void);				//�̾�� ���ĕ\���Ǘ�
extern	void	OPdata_offkan_smp(void);				//��߼�� �̾�Ċ������ް������ݸޏ���
extern	void	KOUSEI_start(void);						//�Z������
extern	void	KOUSEI_start_mng(void);					//�Z�����ĕ\���Ǘ�
extern	void	AUTO_sura_seq_start(void);				//�ײ�ގ����������ݽ ����
extern	void	AUTO_sura_start(void);					//�ײ�ގ�����������
extern	void	OPdata_koukan_smp(void);				//��߼�ݍZ���������ް������ݸޏ���
extern	void	SURA_auto_start_mng(void);				//�ײ�ގ����������ĕ\���Ǘ�
extern	void	MAIN_op_seq(void);						//���ݽ���߼�݂֓]��
extern	void	OPdata_bak_up(void);					//��߼�� �ޯ� ���ߏ���
extern	void	SURA_select_mng(void);					//�ײ�ގ������ߑI��؂芷������
extern	void	POJI_data_chk(void);					//�߼޼���ޯ����ߒl�Ď�
extern	void	OPdata_bak(void);						//��߼�݂̌��ʒu�ް��Ԋ�

/***	ssc_main.c	***/
extern	void	dsp_init1(void);						//�����݉����O1��
extern	void	dsp_init2(void);						//�����݉�����1��
extern	void	dsp_init3(void);						//�Ƽ���ް���M��1��
extern	void	dsp_time_5ms(void);						//5ms���������
extern	void	dsp_main(void);							//��ʕ\�����C�����[�`��
extern	void	Mode_mng(void);							//�j�����R�[�h�ɂ�胂�[�h�Ǘ�
extern	void	Any_mng(void);							//���X�L�����̌Œ菈��
extern	void	keep_ry_smp(void);						//�L�[�v�����[�T���v�����O
extern	void	GAIBU_cnt_rst(void);					//�O���J�E���^�N���A����
extern	void	ONOFF_mng(void);						//�d�l �L�^�� �ɂ�鼰�ݽ����
extern	void	ONOFF_sub(void);						//�d�l �L�^�� �ɂ����ؐ���
extern	void	ROTTO_chk(void);						//ۯĶ��� ���� ����
extern	void	CAMname_pon_read(void);					//�d���������̔ėp�і��̂̓Ǎ���
extern	void	FRAM_csum_set(void);					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ��쐬
extern	void	FRAM_csum_chk(void);					//�׼�RAM�̈�̐ݒ�l�������ѥ���ނ�����
extern	void	FRAM_KAT_csum_set(void);				//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ��쐬
extern	void	FRAM_KAT_csum_chk(void);				//�׼�RAM�̈�̌^�ް� ���́������������ѥ���ނ�����

//
extern	void	FRAM_csum_set_Spec(void);	//2020-09-01 koma �шُ펞���s���Ȃ�
extern	void	FRAM_KAT_csum_set_Spec();	//2020-09-01 koma �шُ펞���s���Ȃ�

