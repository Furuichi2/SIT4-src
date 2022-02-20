
/* 外部参照関数定義 -------------------------------------------------- */
extern	void Lcd_all(UNs, UNs, UNs *);					//全表示
extern	void Lcd_line(UNs, UNs, UNs, UNs *);			//行表示
extern	void Lcd_cr(UNs, UNs, UNs *);					//ｷｬﾗ単位表示
extern	void Lcd_draw(UNs, UNs, UNs, UNs, UNs *);		//ﾄﾞｯﾄ表示
extern	void Lcd_on(void);								//画面ON
extern	void Lcd_off(void);								//画面OFF
extern	void Lcd_contrast_chage(UNs);					//LCD輝度設定
extern	UNb *	kan_rom_set(UNs);						//漢字ＲＯＭよりデータセット

/***	ssc_if_disp.c	***/
extern	void	GENGO_chg(UNi);							//第２カ国語切替え処理
extern	void	Disp_line(UNs, UNs, UNs, UNs);			//画面表示用 1行表示
extern	void	Disp_moji(UNs, UNs *, UNs);				//文字表示
extern	void	Disp_char(UNs, UNs, UNs, UNs *, UNs);	//ﾄﾞｯﾄ表示
extern	void	disp_all_s(UNs, UNs, UNs);				//全画面表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
extern	void	disp_line_s(UNs, UNs *, UNs *);			//1行表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
extern	void	disp_memset(UNs, UNs *, UNs);			//表示用領域を指定ﾃﾞｰﾀで設定
extern	UNi		disp_memnot(UNs, UNs *);				//表示用領域の指定ﾃﾞｰﾀを反転
extern	void	disp_moji_s(UNs , UNs *, UNs *, UNi);	//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
extern	UNi		code_dot_cnv(UNs, UNb *, UNi);			//文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
extern	UNs *	disp_adr_shr(UNs, UNs, UNs);			//画面のｷｬﾗｸﾀｱﾄﾞﾚｽの算出
extern	void	disp_char_cpy(UNs, UNs, UNs, UNs *, UNs);	//画面のｷｬﾗｸﾀのｺﾋﾟｰ
extern	UNs *	mess_adr_shr(UNi);						//メッセージ画面キャラクタアドレス検索
extern	void	BCD_ASCII(UNl, UNb *);					//BCD→ASCII　変換
extern	UNl		BCD_HEX4(UNl);							//BCD→HEX　変換
extern	UNl		HEX_BCD4(UNl);							//HEX→BCD　変換
extern	void	Ascii_Sjis(UNs, UNb *, UNs *);			//Asciiｺｰﾄﾞ → 全角S-Jisｺｰﾄﾞ　変換
extern	UNs		jiscnv(UNs);							//シフトＪＩＳ→ＪＩＳ変換
extern	void	memset_word(UNs *, UNs, UNs);			//指定領域を指定ﾃﾞｰﾀにてﾜｰﾄﾞ単位で設定
extern	void	memset_long(UNl *, UNl, UNs);			//指定領域を指定ﾃﾞｰﾀにてlong単位で設定			//V06a
extern	void	memcpy_word(UNs *, UNs *, UNs);			//指定領域を指定領域先にてﾜｰﾄﾞ単位でコピー

/***	ssc_SvPv.c	***/
extern	void	SVdata_disp(void);						//設定値情報　表示
extern	void	SVdata_disp_ent(UNs);					//設定途中の物は、元に戻す処理
extern	void	SV_csr_set(void);						//設定値カーソル表示
extern	void	SV_csr_reset(UNs);						//設定値カーソル消去
extern	void	PVdata_disp_all(void);					//全　実測値情報　表示
extern	UNs		PVdata_disp(UNs, UNs );					//実測値情報　表示
extern	void	SVPV_data_disp(UNl, void *, UNs, UNs);	//設定値＆実測値 表示
extern	void	Count_hosei_csr_on(UNs);				//カウンタ補正の実測値反転処理
extern	void	SVSW_tbl_enzan(void);					//ＳＶＳＷテーブルアドレス演算
extern	void	kyoutyou_set(UNs);						//強調文字変換

/***	ssc_Sw.c	***/
extern	void	SWchg_ent(void);						//SW CHG データ ENT
extern	void	SWchg_move_ent(void);					//SW CHGの移動 ﾃﾞｰﾀENT
extern	void	SWchg_mmon_ent(void);					//ﾓｰｼｮﾝ用 SWﾃﾞｰﾀ ENT
extern	void	SWchg_bit_chk(void);					//ＳＷデータ入力時強制選択拒否処理
extern	void	SWchg_disp_pv_any(void);				//SWﾃﾞｰﾀ　実測値 表示
extern	void	SWchg_disp_pv(void);					//ＳＷＣＨＧデータ表示実測処理
extern	void	SWchg_disp(void);						//ＳＷデータ情報　表示
extern	void	SWchg_disp_gaibu(void);					//SWﾃﾞｰﾀ情報　表示
extern	void	SWchg_disp_one(UNi);					//1ＳＷデータ情報　表示
extern	void	SWchg_set(UNi, UNs, UNs *);				//ＳＷキャラクタ表示処理
extern	void	SWchg_set_dan(UNi, UNs *);				//ＳＷキャラクタ表示処理(段取り用)
extern	void	SWchg_set_op(UNi, UNs *);				//ＳＷキャラクタ表示処理(オフセット調節用)
extern	void	SWchg_dispset(UNi);						//カーソル反転表示処理
extern	void	SWchg_dispset_dan(UNi);					//カーソル反転表示処理(段取り用)
extern	void	Under_grph(void);						//下段のグラフィックセット
extern	void	WIN_grph(void);							//ウインドウ画面上グラフィック描画
extern	void	SW16data_onset(UNs, UNi);				//ＳＷ１～６の反転指定を行う
extern	void	SW56_upcara_disp(UNs, UNs);				//ＳＷ５６上段キャラクタをＳＷ領域へ格納
extern	void	SW56_dncara_disp(UNs, UNs);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納
extern	void	SW56dn_clear(UNs);						//SWｷｬﾗｸﾀのﾃﾞｰﾀﾊﾟｰﾀｰﾝｸﾘｱ

/***	ssc_Csr.c	***/
extern	void	CSR_move(UNs, UNs);						//カーソル移動
extern	UNs		CSR_pos_chk(void);						//カーソル位置存在チェック
extern	UNi		CSR_pos_shr_dn(UNs, UNs);				//カーソル位置　下検索
extern	UNi		CSR_pos_shr_up(UNs, UNs);				//カーソル位置　上検索
extern	void	CSR_disp(void);							//カーソル表示
extern	void	CSR_disp_off(void);						//カーソル表示消去
extern	void	CSR_disp_cls(UNs);						//仕様有無によるカーソル表示削除
extern	void	CSR_sw56_disp(void);					//ＳＷ５６キャラクタ表示
extern	void	SUBERI_out(void);						//スベリ量カーソル信号出力
extern	void	SEI_test_out_sw5(void);					//生産設定ﾃｽﾄ出力処理(SW5)
extern	void	SEI_test_out_sw6(void);					//生産設定ﾃｽﾄ出力処理(SW6)
extern	void	csr_sw56_sub(UNs);						//SW5/SW6 ﾃﾞｰﾀ処理番号 処理

/***	ssc_key.c	***/
extern	void	Key_mng(void);							//ｷｰ入力確定
extern	void	Key_Ten_in(UNs );						//Ten KEY入力
extern	void	Key_Ent_sv(void);						//設定値の確定
//2014/08/27	extern	void	Key_sv_limt_chk(UNs, UNl *);			//設定値の上下限チェック
extern	UNs		Key_sv_limt_chk(UNs, UNl *);			//設定値の上下限チェック
extern	void	Key_sv_tokusyu_chk(UNs);				//設定値の特殊処理
extern	void	dansuu_zero_set(void);					//ｶﾑの段 強制00設定

/***	ssc_disp.c	***/
extern	void	GAMEN_disp(void);						//画面表示
extern	void	WIN_gamen_disp(void);					//ｳｲﾝﾄﾞｳ画面表示
extern	void	GAMEN_base_disp(void);					//ベース画面表示
extern	void	GAMEN_no_chg(void);						//画面Ｎｏ．変更
extern	void	GAMEN_cls(void);						//画面データクリア
extern	void	WIN_gamen_cls(void);					//ｳｲﾝﾄﾞｳ画面データクリア
extern	void	DISP_after_csr(void);					//画面表示のカーソル後処理
extern	void	DISP_after(void);						//画面表示の後処理
extern	void	WIN_disp_after(void);					//ｳｲﾝﾄﾞｳ画面表示の後処理
extern	void	WIN_disp_after2(void);					//ｳｲﾝﾄﾞｳ画面表示の後処理2
extern	void	Alltbl_set(void);						//情報ﾃｰﾌﾞﾙの作成
extern	void	Wintbl_set(void);						//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの作成
extern	void	Disp_data_set(void);					//情報ﾃｰﾌﾞﾙの非表示処理(作成)
extern	void	gamen_tbl_set(void);					//画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)
extern	void	win_tbl_set(void);						//ｳｨﾝﾄﾞｳ画面の情報ﾃｰﾌﾞﾙの非表示処理(作成)

/***	ssc_disp1.c	***/
extern	void	DATA_svsw(UNs, UNs);					//
extern	UNi		MIS_check(void);						//ミスフィード有無チェック
extern	UNi		ROT1_check(void);						//ロータリカム１～８有無チェック
extern	UNi		ROT2_check(void);						//ロータリカム９～１６有無チェック
extern	UNi		ROT3_check(void);						//ロータリカム１７～２０有無チェック
extern	UNi		EJE_check(void);						//エジェクタ有無チェック
extern	void	DISP_cam_csr_name(void);				//カムカーソル名称表示
extern	void	CAM_next_cls(UNs);						//設定値の次のキャラクタをスペース
extern	void	LENG_svpv(UNs, UNs);					//小数点の変更(設定値&実測値)
extern	void	CSR_cls(UNs, UNs, UNs);					//ｶｰｿﾙ情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	SV_cls(UNs, UNs, UNs);					//設定値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	PV_cls(UNs, UNs, UNs);					//実測値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	SW_cls(UNs, UNs, UNs);					//SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	SW_cls_disp(UNs, UNs, UNs);				//SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの非表示/表示 設定						2014/03/17
extern	void	EJE_grp(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);	//ｴｼﾞｪｸﾀ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	EJE_csr(UNs, UNs, UNs, UNs, UNs, UNs);	//ｴｼﾞｪｸﾀ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの設定値個数消去処理
extern	void	EJE_sw(UNs, UNs, UNs);					//ｴｼﾞｪｸﾀ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
extern	void	ROT_cam_sv(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);		//ﾛｰﾀﾘｶﾑ用設定値情報ﾃｰﾌﾞﾙの消去処理
extern	void	ROT_cam_sw(UNs, UNs, UNs, UNs, UNs);	//ﾛｰﾀﾘｶﾑ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
extern	void	ROT_cam_csr(UNs, UNs, UNs, UNs, UNs, UNs, UNs);			//ﾛｰﾀﾘｶﾑ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
extern	void	MIS_sv(UNs, UNs, UNs);					//ﾐｽﾌｨｰﾄﾞ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	MIS_csr(UNs, UNs, UNs, UNs, UNs);		//ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
extern	void	ATU_svpv(UNs, UNs);						//設定値情報ﾃｰﾌﾞﾙの変更
extern	void	DANsel_csr(UNs, UNs, UNs, UNs);			//ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
extern	void	DAN_sel(UNs *, UNs, UNs, UNs);			//段取り用　各選択の消去処理
extern	void	DAN_csr_set(void);						//段取画面　表示した個数カウンタ
extern	void	KAT_cls(UNs, UNs, UNs, UNs);			//型ﾃﾞｰﾀの実測値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	MEMO_cls(UNs, UNs, UNs, UNs);			//メモの実測値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	PVdata_non_sub(void);					//実測値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	SCAN_kat_cls(void);						//
extern	void	NAME_cls_sub(void);						//第一言語　ｶﾀｶﾅの非表示
extern	void	MISS_swcara(void);						//ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示
extern	void	MISS_swcara_win(void);					//ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示(ｳｨﾝﾄﾞｳ用)
extern	void	mmon_tbl_cls(UNs);						//ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	mmon_tbl_open(UNs);						//ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの表示 設定
extern	void	grpno_sv_cls(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの非表示 設定
extern	void	grpno_sv_open(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの表示 設定
extern	UNs		grpno_sv_srch(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ

/***	ssc_Seisa.c	***/
extern	void	dsp_Seisan(void);						//生産の管理
extern	void	sw34_gamen_01(UNs);						//生産[基本]のSW3･4の処理
extern	void	sw56_gamen_01(UNs);						//生産[基本]のSW5･6の処理
extern	void	sw56_window_02(UNs);					//生産[輝度設定]のSW5･6の処理
extern	void	kido_data_set(void);					//輝度表示 & データ作成
extern	void	mmon_kaiten_chg(void);					//回転方式による設定値 切換え
extern	void	mmon_sv_chg(UNs);						//角度&位置の設定値変更
extern	void	mmon_tchk_disp(UNi);					//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
extern	void	mmon_sel_chk(void);						//ﾓｰｼｮﾝの方式選択ﾁｪｯｸ
extern	void	mmon_trans_get(void);					//回転方式によるﾃﾞｰﾀの取得
extern	void	mmon_trans_put(void);					//回転方式によるﾃﾞｰﾀの格納
extern	UNl		cnv_mi_mi_sur(UNl);						//単位切替(mm/INCH→mm/INCH)
extern	UNl		cnv_mi_mi(UNl);							//単位切替(mm/INCH→mm/INCH)
extern	UNl		cnv_mm_inch(UNl, UNi);					//単位切替(mm→mm/INCH)
extern	UNl		cnv_inch_mm(UNl, UNi);					//単位切替(mm/INCH→mm)
extern	UNl		cnv_um_uinch(UNl um_bf);				//単位切替(um→um/uINCH)
extern	UNl		cnv_uinch_um(UNl uinch_bf);				//単位切替(um/uINCH→um)
extern	void	SEI_csr_ichk(void);						//生産カーソル位置初期化
extern	void	SEI_csr_mng(void);						//生産[基本]の専用　カーソル移動管理

/***	ssc_Dandor.c	***/
extern	void	dsp_Dandori(void);						//段取の管理
extern	void	sw56_gamen_07(UNs);						//段取[基本]のSW5･6の処理
extern	void	DANseq_sw56off(UNs);					//段取り用ｼｰｹﾝｽOFF
extern	void	DAN_select_ent(UNs);					//段取り画面選択項目セレクト入力
extern	void	DANseq_alloff(void);					//段取り用シーケンスＯＦＦ
extern	void	DAN_select_diap(void);					//段取画面 選択項目セレクト表示
extern	void	DAN_sel_cara(UNs);						//段取り選択項目キャラクタ表示
extern	void	DAN_SW14_no_set(void);					//段取画面 SW14認識番号転送
extern	void	DAN_dispseq_out(void);					//段取画面 ｶｰｿﾙ位置ｼｰｹﾝｽ出力
extern	void	DAN_csr_ichk(void);						//段取カーソル位置初期化
extern	void	DAN_csr_mng(void);						//段取[基本]の専用　カーソル移動管理
extern	void	SURA_sv_chg(void);						//スライド自動調節ＳＶ変更処理

/***	ssc_Dataset.c	***/
extern	void	dsp_Dataset(void);						//データ設定の管理
extern	void	Data_sel_cam(void);						//ﾀｲﾐﾝｸﾞ設定への遷移(ｴｼﾞｪｸﾀ/ﾐｽﾌｨｰﾄﾞ/ﾛｰﾀﾘｶﾑ)
extern	void	SHARCH_gamen_15(void);					//検索入力時の画面移動
extern	void	SW56_gamen_15(void);					//型ﾃﾞｰﾀ画面　SW56処理
extern	void	MEMO_data_write(void);					//型ﾃﾞｰﾀ ﾒﾓ書込
extern	void	KAT_data_read(void);					//型ﾃﾞｰﾀ 読込
extern	void	KAT_data_write(void);					//型ﾃﾞｰﾀ 書込
extern	void	KAT_read_sura_chk(void);				//型データ読込み時スライド設定値チェック
extern	void	NAME_csr_mng(void);						//名称画面カーソル制御
extern	void	KATname_inp(void);						//型名称 入力処理
extern	void	KATname_cls(void);						//型名称 訂正処理
extern	void	KATname_ref(UNs, UNs *);				//カム名称リフレッシュ
extern	void	CSR_disp_on(UNs);						//裏画面反転
extern	UNs		NAME_leng_chk(UNb *, UNs);				//名称の入力文字数をチェック
extern	void	CAMname_inp(void);						//カム名称 入力処理
extern	void	CAMname_cls(void);						//カム名称 訂正処理
extern	UNi		CAMname_inp_chk(void);					//カム名称入力可チェック
extern	void	CAMname_touroku(void);					//カム名称登録
extern	void	CAMname_sw_ent(void);					//汎用出力選択
extern	void	CAM_name_ref(void);						//ﾛｰﾀﾘｶﾑ汎用選択種別に対応したｶﾑ名称の更新

/***	ssc_Sysset.c	***/
extern	void	dsp_Sysset(void);						//システム設定の管理
extern	void	Sys_sel_dstg_mmon(void);				//データ設定[メンテナンスモニタ]へ
extern	void	Sys_sel_dstg_ksel(void);				//データ設定[機能選択]へ
extern	void	Sys_dsp_move(void);						//画面と管理ｽﾃｰｼﾞの移動
extern	void	CAR_mkssi_set(void);					//単位切換ﾃﾞｰﾀ格納処理
extern	void	INI_data_set(void);						//データ初期化

/***	ssc_option.c	***/
extern	void	OPDP_trans_chk(void);					//OP-DPRAM ⇔ FRAM ﾃﾞｰﾀ転送 & ﾁｪｯｸ処理
extern	void	OPdata_set_kaku(void);					//ｵﾌﾟｼｮﾝ ﾃﾞｰﾀ転送処理
extern	void	OPdata_sys_kaku(void);					//ｵﾌﾟｼｮﾝにｼｽﾊﾟﾗを格納
extern	void	OP_pvdata_smp(void);					//ｵﾌﾟｼｮﾝ実測値ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
extern	void	POSdata_set_kaku(void);					//ﾎﾟｼﾞｼｮﾅｰ ﾃﾞｰﾀ転送処理
extern	void	OFF_set_start(void);					//ｵﾌｾｯﾄ調整ｽﾀｰﾄ
extern	void	OFF_set_start_mng(void);				//ｵﾌｾｯﾄ ｽﾀｰﾄ表示管理
extern	void	OPdata_offkan_smp(void);				//ｵﾌﾟｼｮﾝ ｵﾌｾｯﾄ完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
extern	void	KOUSEI_start(void);						//校正ｽﾀｰﾄ
extern	void	KOUSEI_start_mng(void);					//校正ｽﾀｰﾄ表示管理
extern	void	AUTO_sura_seq_start(void);				//ｽﾗｲﾄﾞ自動調整ｼｰｹﾝｽ ｽﾀｰﾄ
extern	void	AUTO_sura_start(void);					//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ
extern	void	OPdata_koukan_smp(void);				//ｵﾌﾟｼｮﾝ校正完了時ﾃﾞｰﾀｻﾝﾌﾟﾘﾝｸﾞ処理
extern	void	SURA_auto_start_mng(void);				//ｽﾗｲﾄﾞ自動調整ｽﾀｰﾄ表示管理
extern	void	MAIN_op_seq(void);						//ｼｰｹﾝｽをｵﾌﾟｼｮﾝへ転送
extern	void	OPdata_bak_up(void);					//ｵﾌﾟｼｮﾝ ﾊﾞｯｸ ｱｯﾌﾟ処理
extern	void	SURA_select_mng(void);					//ｽﾗｲﾄﾞ自動調節選択切り換え処理
extern	void	POJI_data_chk(void);					//ﾎﾟｼﾞｼｮﾅﾊﾞｯｸｱｯﾌﾟ値監視
extern	void	OPdata_bak(void);						//ｵﾌﾟｼｮﾝの現位置ﾃﾞｰﾀ返還

/***	ssc_main.c	***/
extern	void	dsp_init1(void);						//割込み解除前1回
extern	void	dsp_init2(void);						//割込み解除後1回
extern	void	dsp_init3(void);						//ｲﾆｼｬﾙﾃﾞｰﾀ受信後1回
extern	void	dsp_time_5ms(void);						//5ms定周期処理
extern	void	dsp_main(void);							//画面表示メインルーチン
extern	void	Mode_mng(void);							//Ｋｅｙコードによりモード管理
extern	void	Any_mng(void);							//毎スキャンの固定処理
extern	void	keep_ry_smp(void);						//キープリレーサンプリング
extern	void	GAIBU_cnt_rst(void);					//外部カウンタクリア処理
extern	void	ONOFF_mng(void);						//仕様 有／無 によるｼｰｹﾝｽ制御
extern	void	ONOFF_sub(void);						//仕様 有／無 による入切制御
extern	void	ROTTO_chk(void);						//ﾛｯﾄｶｳﾝﾀ ｱｯﾌﾟ ﾁｪｯｸ
extern	void	CAMname_pon_read(void);					//電源投入時の汎用ｶﾑ名称の読込み
extern	void	FRAM_csum_set(void);					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
extern	void	FRAM_csum_chk(void);					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ
extern	void	FRAM_KAT_csum_set(void);				//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成
extern	void	FRAM_KAT_csum_chk(void);				//ﾌﾗｼｭRAM領域の型ﾃﾞｰﾀ 名称＆メモのﾁｪｯｸｻﾑ･ｺｰﾄﾞのﾁｪｯｸ

//
extern	void	FRAM_csum_set_Spec(void);	//2020-09-01 koma ｻﾑ異常時実行しない
extern	void	FRAM_KAT_csum_set_Spec();	//2020-09-01 koma ｻﾑ異常時実行しない

