/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			画　面　表　示															*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-29
*
*************************************************************************************/

#include "ssc_ver1.h"							//各種の共通定義
#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
/* 外部参照変数定義 -------------------------------------------------- */
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];
/* 定数定義 ---------------------------------------------------------- */
/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	DATA_svsw(UNs, UNs);					//
UNi		MIS_check(void);						//ミスフィード有無チェック
UNi		ROT1_check(void);						//ロータリカム１～８有無チェック
UNi		ROT2_check(void);						//ロータリカム９～１６有無チェック
UNi		ROT3_check(void);						//ロータリカム１７～２０有無チェック
UNi		EJE_check(void);						//エジェクタ有無チェック

void	DISP_cam_csr_name(void);				//カムカーソル名称表示

void	CAM_next_cls(UNs);						//設定値の次のキャラクタをスペース
void	LENG_svpv(UNs, UNs);					//小数点の変更(設定値&実測値)
void	CSR_cls(UNs, UNs, UNs);					//ｶｰｿﾙ情報ﾃｰﾌﾞﾙの非表示 設定
void	SV_cls(UNs, UNs, UNs);					//設定値情報ﾃｰﾌﾞﾙの非表示 設定
void	PV_cls(UNs, UNs, UNs);					//実測値情報ﾃｰﾌﾞﾙの非表示 設定
void	SW_cls(UNs, UNs, UNs);					//SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの非表示 設定
void	EJE_grp(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);	//ｴｼﾞｪｸﾀ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
void	EJE_csr(UNs, UNs, UNs, UNs, UNs, UNs);	//ｴｼﾞｪｸﾀ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの設定値個数消去処理
void	EJE_sw(UNs, UNs, UNs);					//ｴｼﾞｪｸﾀ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
void	ROT_cam_sv(UNs, UNs, UNs, UNs, UNs, UNs, UNs, UNs);		//ﾛｰﾀﾘｶﾑ用設定値情報ﾃｰﾌﾞﾙの消去処理
void	ROT_cam_sw(UNs, UNs, UNs, UNs, UNs);	//ﾛｰﾀﾘｶﾑ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
void	ROT_cam_csr(UNs, UNs, UNs, UNs, UNs, UNs, UNs);			//ﾛｰﾀﾘｶﾑ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
void	MIS_sv(UNs, UNs, UNs);					//ﾐｽﾌｨｰﾄﾞ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
void	MIS_csr(UNs, UNs, UNs, UNs, UNs);		//ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
void	ATU_svpv(UNs, UNs);						//設定値情報ﾃｰﾌﾞﾙの変更
void	DANsel_csr(UNs, UNs, UNs, UNs);			//ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
void	DAN_sel(UNs *, UNs, UNs, UNs);			//段取り用　各選択の消去処理
void	DAN_csr_set(void);						//段取画面　表示した個数カウンタ
void	KAT_cls(UNs, UNs, UNs, UNs);			//型ﾃﾞｰﾀの実測値情報ﾃｰﾌﾞﾙの非表示 設定
void	MEMO_cls(UNs, UNs, UNs, UNs);			//メモの実測値情報ﾃｰﾌﾞﾙの非表示 設定
void	PVdata_non_sub(void);					//実測値情報ﾃｰﾌﾞﾙの非表示 設定
void	SCAN_kat_cls(void);						//
void	NAME_cls_sub(void);						//第一言語　ｶﾀｶﾅの非表示
void	MISS_swcara(void);						//ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示
void	MISS56_swcara(void);						//ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示
void	MISS_swcara_win(void);					//ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示(ｳｨﾝﾄﾞｳ用)

void	mmon_tbl_cls(UNs);						//ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの非表示 設定
void	mmon_tbl_open(UNs);						//ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの表示 設定
void	grpno_sv_cls(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの非表示 設定
void	grpno_sv_open(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの表示 設定
UNs		grpno_sv_srch(UNs);						//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ

void	kag_to_kaj_sub_chg(void);				//下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換


/* 内部変数定義 ------------------------------------------------------ */
UNs		SV_GENGO_KAT;

/* テーブル定義 ------------------------------------------------------ */

const	UNs *	SW56_Cam_Name_Tbl[69]={
			&PV_CAMNA01_C1[0],		//80/* ロータリカム１名称 */
			&PV_CAMNA02_C1[0],		//81/* ロータリカム２名称 */
			&PV_CAMNA03_C1[0],		//82/* ロータリカム３名称 */
			&PV_CAMNA04_C1[0],		//83/* ロータリカム４名称 */
			&PV_CAMNA05_C1[0],		//84/* ロータリカム５名称 */
			&PV_CAMNA06_C1[0],		//85/* ロータリカム６名称 */
			&PV_CAMNA07_C1[0],		//86/* ロータリカム７名称 */
			&PV_CAMNA08_C1[0],		//87/* ロータリカム８名称 */
			&PV_CAMNA09_C1[0],		//88/* ロータリカム９名称 */
			&PV_CAMNA10_C1[0],		//89/* ロータリカム１０名称 */
			&PV_CAMNA11_C1[0],		//8A/* ロータリカム１１名称 */
			&PV_CAMNA12_C1[0],		//8B/* ロータリカム１２名称 */
			&PV_CAMNA13_C1[0],		//8C/* ロータリカム１３名称 */
			&PV_CAMNA14_C1[0],		//8D/* ロータリカム１４名称 */
			&PV_CAMNA15_C1[0],		//8E/* ロータリカム１５名称 */
			&PV_CAMNA16_C1[0],		//8F/* ロータリカム１６名称 */
			&PV_CAMNAM_C1[0],		//90
			&SV_EJENAM01_C1[0],		//91/* エジェクタ１ */
			&SV_EJENAM02_C1[0],		//92/* エジェクタ２ */
			&SV_EJENAM03_C1[0],		//93/* エジェクタ３ */
			&SV_EJENAM04_C1[0],		//94/* エジェクタ４ */
			&SV_EJENAM05_C1[0],		//95/* エジェクタ５ */
			&SV_EJENAM06_C1[0],		//96/* エジェクタ６ */
//			&PV_EJECT1_NAME,		//91/* エジェクタ１ */
//			&PV_EJECT2_NAME,		//92/* エジェクタ１ */
//			&PV_EJECT3_NAME,		//93/* エジェクタ１ */
//			&PV_EJECT4_NAME,		//94/* エジェクタ１ */
//			&PV_EJECT5_NAME,		//95/* エジェクタ１ */
//			&PV_EJECT6_NAME,		//96/* エジェクタ１ */
			&PV_KOUMOKU1_NAME[0],	//97/* 項目番号１　 */
			&PV_KOUMOKU2_NAME[0],	//98/* 項目番号２　 */
			&PV_KOUMOKU3_NAME[0],	//99/* 項目番号３　 */
			&PV_KOUMOKU4_NAME[0],	//9A/* 項目番号４　 */
			&PV_CAMNA17_C1[0],		//9B/* ロータリカム１７名称 */
			&PV_CAMNA18_C1[0],		//9C/* ロータリカム１８名称 */
			&PV_CAMNA19_C1[0],		//9D/* ロータリカム１９名称 */
			&PV_CAMNA20_C1[0],		//9E/* ロータリカム２０名称 */
			&PV_CAMNAM_C1[0],		//9F/* 予備 */
			&KAT_NAME_01[0],		//A0/* 型データ名称１ */
			&KAT_NAME_02[0],		//A1/* 型データ名称２ */
			&KAT_NAME_03[0],		//A2/* 型データ名称３ */
			&KAT_NAME_04[0],		//A3/* 型データ名称４ */
			&KAT_NAME_05[0],		//A4/* 型データ名称５ */
			&KAT_NAME_06[0],		//A5/* 型データ名称６ */
			&KAT_NAME_07[0],		//A6/* 型データ名称７ */
			&KAT_NAME_08[0],		//A7/* 型データ名称８ */
			&KAT_NAME_09[0],		//A8/* 型データ名称９ */
			&KAT_NAME_10[0],		//A9/* 型データ名称1０ */
			&PV_MLDNO2_F0[0],		//AA/* 型ﾃﾞｰﾀ 名称＆メモの現在表示 */
			&KAT_MEMO_01[0],		//AB/* 型データメモ１ */
			&KAT_MEMO_02[0],		//AC/* 型データメモ２ */
			&KAT_MEMO_03[0],		//AD/* 型データメモ３ */
			&KAT_MEMO_04[0],		//AE/* 型データメモ４ */
			&KAT_MEMO_05[0],		//AF/* 型データメモ５ */
			&KAT_MEMO_06[0],		//B0/* 型データメモ６ */
			&KAT_MEMO_07[0],		//B1/* 型データメモ７ */
			&KAT_MEMO_08[0],		//B2/* 型データメモ８ */
			&KAT_MEMO_09[0],		//B3/* 型データメモ９ */
			&KAT_MEMO_10[0],		//B4/* 型データメモ1０ */
			&PV_KINOU01_NAE[0],		//B5/* 機能選択項目１ 　*/
			&PV_KINOU02_NAE[0],		//B6/* 機能選択項目２ 　*/
			&PV_KINOU03_NAE[0],		//B7/* 機能選択項目３　 */
			&PV_KINOU04_NAE[0],		//B8/* 機能選択項目４ 　*/
			&PV_KINOU05_NAE[0],		//B9/* 機能選択項目５ 　*/
			&PV_KINOU06_NAE[0],		//BA/* 機能選択項目６ 　*/
			&PV_KINOU07_NAE[0],		//BB/* 機能選択項目７ 　*/
			&PV_KINOU08_NAE[0],		//BC/* 機能選択項目８ 　*/
			&PV_KINOU09_NAE[0],		//BD/* 機能選択項目９ 　*/
			&PV_KINOU10_NAE[0],		//BE/* 機能選択項目１０ */
			&PV_KINOU11_NAE[0],		//BF/* 機能選択項目１１ */
			&PV_KINOU12_NAE[0],		//C0/* 機能選択項目１２ */
			&PV_KINOU13_NAE[0],		//C1/* 機能選択項目１３ */
			&PV_KINOU14_NAE[0],		//C2/* 機能選択項目１４ */
			&PV_KINOU15_NAE[0],		//C3/* 機能選択項目１５ */
			&PV_KINOU16_NAE[0]		//C4/* 機能選択項目１６ */
		};

//型ﾃﾞｰﾀ 名称領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
//const	UNs *	KAT_sv_name_tbl[101] = {
//const	UNs *	KAT_sv_name_tbl[201] = {		//V06n
const	UNs *	KAT_sv_name_tbl[221] = {		//2014/04/16	SIT-4 MC
		&KAT_NAME_01[0],			/* ダミー */
		&KAT_NAME_01[0],			/* 型データ名称１ */
		&KAT_NAME_02[0],			/* 型データ名称２ */
		&KAT_NAME_03[0],			/* 型データ名称３ */
		&KAT_NAME_04[0],			/* 型データ名称４ */
		&KAT_NAME_05[0],			/* 型データ名称５ */
		&KAT_NAME_06[0],			/* 型データ名称６ */
		&KAT_NAME_07[0],			/* 型データ名称７ */
		&KAT_NAME_08[0],			/* 型データ名称８ */
		&KAT_NAME_09[0],			/* 型データ名称９ */
		&KAT_NAME_10[0],			/* 型データ名称１０ */
		&KAT_NAME_11[0],			/* 型データ名称１１ */
		&KAT_NAME_12[0],			/* 型データ名称１２ */
		&KAT_NAME_13[0],			/* 型データ名称１３ */
		&KAT_NAME_14[0],			/* 型データ名称１４ */
		&KAT_NAME_15[0],			/* 型データ名称１５ */
		&KAT_NAME_16[0],			/* 型データ名称１６ */
		&KAT_NAME_17[0],			/* 型データ名称１７ */
		&KAT_NAME_18[0],			/* 型データ名称１８ */
		&KAT_NAME_19[0],			/* 型データ名称１９ */
		&KAT_NAME_20[0],			/* 型データ名称２０ */
		&KAT_NAME_21[0],			/* 型データ名称２１ */
		&KAT_NAME_22[0],			/* 型データ名称２２ */
		&KAT_NAME_23[0],			/* 型データ名称２３ */
		&KAT_NAME_24[0],			/* 型データ名称２４ */
		&KAT_NAME_25[0],			/* 型データ名称２５ */
		&KAT_NAME_26[0],			/* 型データ名称２６ */
		&KAT_NAME_27[0],			/* 型データ名称２７ */
		&KAT_NAME_28[0],			/* 型データ名称２８ */
		&KAT_NAME_29[0],			/* 型データ名称２９ */
		&KAT_NAME_30[0],			/* 型データ名称３０ */
		&KAT_NAME_31[0],			/* 型データ名称３１ */
		&KAT_NAME_32[0],			/* 型データ名称３２ */
		&KAT_NAME_33[0],			/* 型データ名称３３ */
		&KAT_NAME_34[0],			/* 型データ名称３４ */
		&KAT_NAME_35[0],			/* 型データ名称３５ */
		&KAT_NAME_36[0],			/* 型データ名称３６ */
		&KAT_NAME_37[0],			/* 型データ名称３７ */
		&KAT_NAME_38[0],			/* 型データ名称３８ */
		&KAT_NAME_39[0],			/* 型データ名称３９ */
		&KAT_NAME_40[0],			/* 型データ名称４０ */
		&KAT_NAME_41[0],			/* 型データ名称４１ */
		&KAT_NAME_42[0],			/* 型データ名称４２ */
		&KAT_NAME_43[0],			/* 型データ名称４３ */
		&KAT_NAME_44[0],			/* 型データ名称４４ */
		&KAT_NAME_45[0],			/* 型データ名称４５ */
		&KAT_NAME_46[0],			/* 型データ名称４６ */
		&KAT_NAME_47[0],			/* 型データ名称４７ */
		&KAT_NAME_48[0],			/* 型データ名称４８ */
		&KAT_NAME_49[0],			/* 型データ名称４９ */
		&KAT_NAME_50[0],			/* 型データ名称５０ */
		&KAT_NAME_51[0],			/* 型データ名称５１ */
		&KAT_NAME_52[0],			/* 型データ名称５２ */
		&KAT_NAME_53[0],			/* 型データ名称５３ */
		&KAT_NAME_54[0],			/* 型データ名称５４ */
		&KAT_NAME_55[0],			/* 型データ名称５５ */
		&KAT_NAME_56[0],			/* 型データ名称５６ */
		&KAT_NAME_57[0],			/* 型データ名称５７ */
		&KAT_NAME_58[0],			/* 型データ名称５８ */
		&KAT_NAME_59[0],			/* 型データ名称５９ */
		&KAT_NAME_60[0],			/* 型データ名称６０ */
		&KAT_NAME_61[0],			/* 型データ名称６１ */
		&KAT_NAME_62[0],			/* 型データ名称６２ */
		&KAT_NAME_63[0],			/* 型データ名称６３ */
		&KAT_NAME_64[0],			/* 型データ名称６４ */
		&KAT_NAME_65[0],			/* 型データ名称６５ */
		&KAT_NAME_66[0],			/* 型データ名称６６ */
		&KAT_NAME_67[0],			/* 型データ名称６７ */
		&KAT_NAME_68[0],			/* 型データ名称６８ */
		&KAT_NAME_69[0],			/* 型データ名称６９ */
		&KAT_NAME_70[0],			/* 型データ名称７０ */
		&KAT_NAME_71[0],			/* 型データ名称７１ */
		&KAT_NAME_72[0],			/* 型データ名称７２ */
		&KAT_NAME_73[0],			/* 型データ名称７３ */
		&KAT_NAME_74[0],			/* 型データ名称７４ */
		&KAT_NAME_75[0],			/* 型データ名称７５ */
		&KAT_NAME_76[0],			/* 型データ名称７６ */
		&KAT_NAME_77[0],			/* 型データ名称７７ */
		&KAT_NAME_78[0],			/* 型データ名称７８ */
		&KAT_NAME_79[0],			/* 型データ名称７９ */
		&KAT_NAME_80[0],			/* 型データ名称８０ */
		&KAT_NAME_81[0],			/* 型データ名称８１ */
		&KAT_NAME_82[0],			/* 型データ名称８２ */
		&KAT_NAME_83[0],			/* 型データ名称８３ */
		&KAT_NAME_84[0],			/* 型データ名称８４ */
		&KAT_NAME_85[0],			/* 型データ名称８５ */
		&KAT_NAME_86[0],			/* 型データ名称８６ */
		&KAT_NAME_87[0],			/* 型データ名称８７ */
		&KAT_NAME_88[0],			/* 型データ名称８８ */
		&KAT_NAME_89[0],			/* 型データ名称８９ */
		&KAT_NAME_90[0],			/* 型データ名称９０ */
		&KAT_NAME_91[0],			/* 型データ名称９１ */
		&KAT_NAME_92[0],			/* 型データ名称９２ */
		&KAT_NAME_93[0],			/* 型データ名称９３ */
		&KAT_NAME_94[0],			/* 型データ名称９４ */
		&KAT_NAME_95[0],			/* 型データ名称９５ */
		&KAT_NAME_96[0],			/* 型データ名称９６ */
		&KAT_NAME_97[0],			/* 型データ名称９７ */
		&KAT_NAME_98[0],			/* 型データ名称９８ */
		&KAT_NAME_99[0],			/* 型データ名称９９ */
		&KAT_NAME_100[0],			/* 型データ名称１００ */
		&KAT_NAME_101[0],			/* 型データ名称１０１ */
		&KAT_NAME_102[0],			/* 型データ名称１０２ */
		&KAT_NAME_103[0],			/* 型データ名称１０３ */
		&KAT_NAME_104[0],			/* 型データ名称１０４ */
		&KAT_NAME_105[0],			/* 型データ名称１０５ */
		&KAT_NAME_106[0],			/* 型データ名称１０６ */
		&KAT_NAME_107[0],			/* 型データ名称１０７ */
		&KAT_NAME_108[0],			/* 型データ名称１０８ */
		&KAT_NAME_109[0],			/* 型データ名称１０９ */
		&KAT_NAME_110[0],			/* 型データ名称１１０ */
		&KAT_NAME_111[0],			/* 型データ名称１１１ */
		&KAT_NAME_112[0],			/* 型データ名称１１２ */
		&KAT_NAME_113[0],			/* 型データ名称１１３ */
		&KAT_NAME_114[0],			/* 型データ名称１１４ */
		&KAT_NAME_115[0],			/* 型データ名称１１５ */
		&KAT_NAME_116[0],			/* 型データ名称１１６ */
		&KAT_NAME_117[0],			/* 型データ名称１１７ */
		&KAT_NAME_118[0],			/* 型データ名称１１８ */
		&KAT_NAME_119[0],			/* 型データ名称１１９ */
		&KAT_NAME_120[0],			/* 型データ名称１２０ */
		&KAT_NAME_121[0],			/* 型データ名称１２１ */
		&KAT_NAME_122[0],			/* 型データ名称１２２ */
		&KAT_NAME_123[0],			/* 型データ名称１２３ */
		&KAT_NAME_124[0],			/* 型データ名称１２４ */
		&KAT_NAME_125[0],			/* 型データ名称１２５ */
		&KAT_NAME_126[0],			/* 型データ名称１２６ */
		&KAT_NAME_127[0],			/* 型データ名称１２７ */
		&KAT_NAME_128[0],			/* 型データ名称１２８ */
		&KAT_NAME_129[0],			/* 型データ名称１２９ */
		&KAT_NAME_130[0],			/* 型データ名称１３０ */
		&KAT_NAME_131[0],			/* 型データ名称１３１ */
		&KAT_NAME_132[0],			/* 型データ名称１３２ */
		&KAT_NAME_133[0],			/* 型データ名称１３３ */
		&KAT_NAME_134[0],			/* 型データ名称１３４ */
		&KAT_NAME_135[0],			/* 型データ名称１３５ */
		&KAT_NAME_136[0],			/* 型データ名称１３６ */
		&KAT_NAME_137[0],			/* 型データ名称１３７ */
		&KAT_NAME_138[0],			/* 型データ名称１３８ */
		&KAT_NAME_139[0],			/* 型データ名称１３９ */
		&KAT_NAME_140[0],			/* 型データ名称１４０ */
		&KAT_NAME_141[0],			/* 型データ名称１４１ */
		&KAT_NAME_142[0],			/* 型データ名称１４２ */
		&KAT_NAME_143[0],			/* 型データ名称１４３ */
		&KAT_NAME_144[0],			/* 型データ名称１４４ */
		&KAT_NAME_145[0],			/* 型データ名称１４５ */
		&KAT_NAME_146[0],			/* 型データ名称１４６ */
		&KAT_NAME_147[0],			/* 型データ名称１４７ */
		&KAT_NAME_148[0],			/* 型データ名称１４８ */
		&KAT_NAME_149[0],			/* 型データ名称１４９ */
		&KAT_NAME_150[0],			/* 型データ名称１５０ */
		&KAT_NAME_151[0],			/* 型データ名称１５１ */
		&KAT_NAME_152[0],			/* 型データ名称１５２ */
		&KAT_NAME_153[0],			/* 型データ名称１５３ */
		&KAT_NAME_154[0],			/* 型データ名称１５４ */
		&KAT_NAME_155[0],			/* 型データ名称１５５ */
		&KAT_NAME_156[0],			/* 型データ名称１５６ */
		&KAT_NAME_157[0],			/* 型データ名称１５７ */
		&KAT_NAME_158[0],			/* 型データ名称１５８ */
		&KAT_NAME_159[0],			/* 型データ名称１５９ */
		&KAT_NAME_160[0],			/* 型データ名称１６０ */
		&KAT_NAME_161[0],			/* 型データ名称１６１ */
		&KAT_NAME_162[0],			/* 型データ名称１６２ */
		&KAT_NAME_163[0],			/* 型データ名称１６３ */
		&KAT_NAME_164[0],			/* 型データ名称１６４ */
		&KAT_NAME_165[0],			/* 型データ名称１６５ */
		&KAT_NAME_166[0],			/* 型データ名称１６６ */
		&KAT_NAME_167[0],			/* 型データ名称１６７ */
		&KAT_NAME_168[0],			/* 型データ名称１６８ */
		&KAT_NAME_169[0],			/* 型データ名称１６９ */
		&KAT_NAME_170[0],			/* 型データ名称１７０ */
		&KAT_NAME_171[0],			/* 型データ名称１７１ */
		&KAT_NAME_172[0],			/* 型データ名称１７２ */
		&KAT_NAME_173[0],			/* 型データ名称１７３ */
		&KAT_NAME_174[0],			/* 型データ名称１７４ */
		&KAT_NAME_175[0],			/* 型データ名称１７５ */
		&KAT_NAME_176[0],			/* 型データ名称１７６ */
		&KAT_NAME_177[0],			/* 型データ名称１７７ */
		&KAT_NAME_178[0],			/* 型データ名称１７８ */
		&KAT_NAME_179[0],			/* 型データ名称１７９ */
		&KAT_NAME_180[0],			/* 型データ名称１８０ */
		&KAT_NAME_181[0],			/* 型データ名称１８１ */
		&KAT_NAME_182[0],			/* 型データ名称１８２ */
		&KAT_NAME_183[0],			/* 型データ名称１８３ */
		&KAT_NAME_184[0],			/* 型データ名称１８４ */
		&KAT_NAME_185[0],			/* 型データ名称１８５ */
		&KAT_NAME_186[0],			/* 型データ名称１８６ */
		&KAT_NAME_187[0],			/* 型データ名称１８７ */
		&KAT_NAME_188[0],			/* 型データ名称１８８ */
		&KAT_NAME_189[0],			/* 型データ名称１８９ */
		&KAT_NAME_190[0],			/* 型データ名称１９０ */
		&KAT_NAME_191[0],			/* 型データ名称１９１ */
		&KAT_NAME_192[0],			/* 型データ名称１９２ */
		&KAT_NAME_193[0],			/* 型データ名称１９３ */
		&KAT_NAME_194[0],			/* 型データ名称１９４ */
		&KAT_NAME_195[0],			/* 型データ名称１９５ */
		&KAT_NAME_196[0],			/* 型データ名称１９６ */
		&KAT_NAME_197[0],			/* 型データ名称１９７ */
		&KAT_NAME_198[0],			/* 型データ名称１９８ */
		&KAT_NAME_199[0],			/* 型データ名称１９９ */
		&KAT_NAME_200[0],			/* 型データ名称２００ */
		&KAT_NAME_201[0],			/* 型データ名称２０１ */
		&KAT_NAME_202[0],			/* 型データ名称２０２ */
		&KAT_NAME_203[0],			/* 型データ名称２０３ */
		&KAT_NAME_204[0],			/* 型データ名称２０４ */
		&KAT_NAME_205[0],			/* 型データ名称２０５ */
		&KAT_NAME_206[0],			/* 型データ名称２０６ */
		&KAT_NAME_207[0],			/* 型データ名称２０７ */
		&KAT_NAME_208[0],			/* 型データ名称２０８ */
		&KAT_NAME_209[0],			/* 型データ名称２０９ */
		&KAT_NAME_210[0],			/* 型データ名称２１０ */
		&KAT_NAME_211[0],			/* 型データ名称２１１ */
		&KAT_NAME_212[0],			/* 型データ名称２１２ */
		&KAT_NAME_213[0],			/* 型データ名称２１３ */
		&KAT_NAME_214[0],			/* 型データ名称２１４ */
		&KAT_NAME_215[0],			/* 型データ名称２１５ */
		&KAT_NAME_216[0],			/* 型データ名称２１６ */
		&KAT_NAME_217[0],			/* 型データ名称２１７ */
		&KAT_NAME_218[0],			/* 型データ名称２１８ */
		&KAT_NAME_219[0],			/* 型データ名称２１９ */
		&KAT_NAME_220[0]			/* 型データ名称２２０ */
	};

//型ﾃﾞｰﾀ メモ領域のｱﾄﾞﾚｽ･ﾃｰﾌﾞﾙ
//const	UNs *	KAT_sv_memo_tbl[101] = {
//const	UNs *	KAT_sv_memo_tbl[201] = {		//V06n
const	UNs *	KAT_sv_memo_tbl[221] = {		//2014/04/16	SIT-4 MC
		&KAT_MEMO_01[0],			/* ダミー */
		&KAT_MEMO_01[0],			/* 型データメモ１ */
		&KAT_MEMO_02[0],			/* 型データメモ２ */
		&KAT_MEMO_03[0],			/* 型データメモ３ */
		&KAT_MEMO_04[0],			/* 型データメモ４ */
		&KAT_MEMO_05[0],			/* 型データメモ５ */
		&KAT_MEMO_06[0],			/* 型データメモ６ */
		&KAT_MEMO_07[0],			/* 型データメモ７ */
		&KAT_MEMO_08[0],			/* 型データメモ８ */
		&KAT_MEMO_09[0],			/* 型データメモ９ */
		&KAT_MEMO_10[0],			/* 型データメモ１０ */
		&KAT_MEMO_11[0],			/* 型データメモ１１ */
		&KAT_MEMO_12[0],			/* 型データメモ１２ */
		&KAT_MEMO_13[0],			/* 型データメモ１３ */
		&KAT_MEMO_14[0],			/* 型データメモ１４ */
		&KAT_MEMO_15[0],			/* 型データメモ１５ */
		&KAT_MEMO_16[0],			/* 型データメモ１６ */
		&KAT_MEMO_17[0],			/* 型データメモ１７ */
		&KAT_MEMO_18[0],			/* 型データメモ１８ */
		&KAT_MEMO_19[0],			/* 型データメモ１９ */
		&KAT_MEMO_20[0],			/* 型データメモ２０ */
		&KAT_MEMO_21[0],			/* 型データメモ２１ */
		&KAT_MEMO_22[0],			/* 型データメモ２２ */
		&KAT_MEMO_23[0],			/* 型データメモ２３ */
		&KAT_MEMO_24[0],			/* 型データメモ２４ */
		&KAT_MEMO_25[0],			/* 型データメモ２５ */
		&KAT_MEMO_26[0],			/* 型データメモ２６ */
		&KAT_MEMO_27[0],			/* 型データメモ２７ */
		&KAT_MEMO_28[0],			/* 型データメモ２８ */
		&KAT_MEMO_29[0],			/* 型データメモ２９ */
		&KAT_MEMO_30[0],			/* 型データメモ３０ */
		&KAT_MEMO_31[0],			/* 型データメモ３１ */
		&KAT_MEMO_32[0],			/* 型データメモ３２ */
		&KAT_MEMO_33[0],			/* 型データメモ３３ */
		&KAT_MEMO_34[0],			/* 型データメモ３４ */
		&KAT_MEMO_35[0],			/* 型データメモ３５ */
		&KAT_MEMO_36[0],			/* 型データメモ３６ */
		&KAT_MEMO_37[0],			/* 型データメモ３７ */
		&KAT_MEMO_38[0],			/* 型データメモ３８ */
		&KAT_MEMO_39[0],			/* 型データメモ３９ */
		&KAT_MEMO_40[0],			/* 型データメモ４０ */
		&KAT_MEMO_41[0],			/* 型データメモ４１ */
		&KAT_MEMO_42[0],			/* 型データメモ４２ */
		&KAT_MEMO_43[0],			/* 型データメモ４３ */
		&KAT_MEMO_44[0],			/* 型データメモ４４ */
		&KAT_MEMO_45[0],			/* 型データメモ４５ */
		&KAT_MEMO_46[0],			/* 型データメモ４６ */
		&KAT_MEMO_47[0],			/* 型データメモ４７ */
		&KAT_MEMO_48[0],			/* 型データメモ４８ */
		&KAT_MEMO_49[0],			/* 型データメモ４９ */
		&KAT_MEMO_50[0],			/* 型データメモ５０ */
		&KAT_MEMO_51[0],			/* 型データメモ５１ */
		&KAT_MEMO_52[0],			/* 型データメモ５２ */
		&KAT_MEMO_53[0],			/* 型データメモ５３ */
		&KAT_MEMO_54[0],			/* 型データメモ５４ */
		&KAT_MEMO_55[0],			/* 型データメモ５５ */
		&KAT_MEMO_56[0],			/* 型データメモ５６ */
		&KAT_MEMO_57[0],			/* 型データメモ５７ */
		&KAT_MEMO_58[0],			/* 型データメモ５８ */
		&KAT_MEMO_59[0],			/* 型データメモ５９ */
		&KAT_MEMO_60[0],			/* 型データメモ６０ */
		&KAT_MEMO_61[0],			/* 型データメモ６１ */
		&KAT_MEMO_62[0],			/* 型データメモ６２ */
		&KAT_MEMO_63[0],			/* 型データメモ６３ */
		&KAT_MEMO_64[0],			/* 型データメモ６４ */
		&KAT_MEMO_65[0],			/* 型データメモ６５ */
		&KAT_MEMO_66[0],			/* 型データメモ６６ */
		&KAT_MEMO_67[0],			/* 型データメモ６７ */
		&KAT_MEMO_68[0],			/* 型データメモ６８ */
		&KAT_MEMO_69[0],			/* 型データメモ６９ */
		&KAT_MEMO_70[0],			/* 型データメモ７０ */
		&KAT_MEMO_71[0],			/* 型データメモ７１ */
		&KAT_MEMO_72[0],			/* 型データメモ７２ */
		&KAT_MEMO_73[0],			/* 型データメモ７３ */
		&KAT_MEMO_74[0],			/* 型データメモ７４ */
		&KAT_MEMO_75[0],			/* 型データメモ７５ */
		&KAT_MEMO_76[0],			/* 型データメモ７６ */
		&KAT_MEMO_77[0],			/* 型データメモ７７ */
		&KAT_MEMO_78[0],			/* 型データメモ７８ */
		&KAT_MEMO_79[0],			/* 型データメモ７９ */
		&KAT_MEMO_80[0],			/* 型データメモ８０ */
		&KAT_MEMO_81[0],			/* 型データメモ８１ */
		&KAT_MEMO_82[0],			/* 型データメモ８２ */
		&KAT_MEMO_83[0],			/* 型データメモ８３ */
		&KAT_MEMO_84[0],			/* 型データメモ８４ */
		&KAT_MEMO_85[0],			/* 型データメモ８５ */
		&KAT_MEMO_86[0],			/* 型データメモ８６ */
		&KAT_MEMO_87[0],			/* 型データメモ８７ */
		&KAT_MEMO_88[0],			/* 型データメモ８８ */
		&KAT_MEMO_89[0],			/* 型データメモ８９ */
		&KAT_MEMO_90[0],			/* 型データメモ９０ */
		&KAT_MEMO_91[0],			/* 型データメモ９１ */
		&KAT_MEMO_92[0],			/* 型データメモ９２ */
		&KAT_MEMO_93[0],			/* 型データメモ９３ */
		&KAT_MEMO_94[0],			/* 型データメモ９４ */
		&KAT_MEMO_95[0],			/* 型データメモ９５ */
		&KAT_MEMO_96[0],			/* 型データメモ９６ */
		&KAT_MEMO_97[0],			/* 型データメモ９７ */
		&KAT_MEMO_98[0],			/* 型データメモ９８ */
		&KAT_MEMO_99[0],			/* 型データメモ９９ */
		&KAT_MEMO_100[0],			/* 型データメモ１００ */
		&KAT_MEMO_101[0],			/* 型データメモ１０１ */
		&KAT_MEMO_102[0],			/* 型データメモ１０２ */
		&KAT_MEMO_103[0],			/* 型データメモ１０３ */
		&KAT_MEMO_104[0],			/* 型データメモ１０４ */
		&KAT_MEMO_105[0],			/* 型データメモ１０５ */
		&KAT_MEMO_106[0],			/* 型データメモ１０６ */
		&KAT_MEMO_107[0],			/* 型データメモ１０７ */
		&KAT_MEMO_108[0],			/* 型データメモ１０８ */
		&KAT_MEMO_109[0],			/* 型データメモ１０９ */
		&KAT_MEMO_110[0],			/* 型データメモ１１０ */
		&KAT_MEMO_111[0],			/* 型データメモ１１１ */
		&KAT_MEMO_112[0],			/* 型データメモ１１２ */
		&KAT_MEMO_113[0],			/* 型データメモ１１３ */
		&KAT_MEMO_114[0],			/* 型データメモ１１４ */
		&KAT_MEMO_115[0],			/* 型データメモ１１５ */
		&KAT_MEMO_116[0],			/* 型データメモ１１６ */
		&KAT_MEMO_117[0],			/* 型データメモ１１７ */
		&KAT_MEMO_118[0],			/* 型データメモ１１８ */
		&KAT_MEMO_119[0],			/* 型データメモ１１９ */
		&KAT_MEMO_120[0],			/* 型データメモ１２０ */
		&KAT_MEMO_121[0],			/* 型データメモ１２１ */
		&KAT_MEMO_122[0],			/* 型データメモ１２２ */
		&KAT_MEMO_123[0],			/* 型データメモ１２３ */
		&KAT_MEMO_124[0],			/* 型データメモ１２４ */
		&KAT_MEMO_125[0],			/* 型データメモ１２５ */
		&KAT_MEMO_126[0],			/* 型データメモ１２６ */
		&KAT_MEMO_127[0],			/* 型データメモ１２７ */
		&KAT_MEMO_128[0],			/* 型データメモ１２８ */
		&KAT_MEMO_129[0],			/* 型データメモ１２９ */
		&KAT_MEMO_130[0],			/* 型データメモ１３０ */
		&KAT_MEMO_131[0],			/* 型データメモ１３１ */
		&KAT_MEMO_132[0],			/* 型データメモ１３２ */
		&KAT_MEMO_133[0],			/* 型データメモ１３３ */
		&KAT_MEMO_134[0],			/* 型データメモ１３４ */
		&KAT_MEMO_135[0],			/* 型データメモ１３５ */
		&KAT_MEMO_136[0],			/* 型データメモ１３６ */
		&KAT_MEMO_137[0],			/* 型データメモ１３７ */
		&KAT_MEMO_138[0],			/* 型データメモ１３８ */
		&KAT_MEMO_139[0],			/* 型データメモ１３９ */
		&KAT_MEMO_140[0],			/* 型データメモ１４０ */
		&KAT_MEMO_141[0],			/* 型データメモ１４１ */
		&KAT_MEMO_142[0],			/* 型データメモ１４２ */
		&KAT_MEMO_143[0],			/* 型データメモ１４３ */
		&KAT_MEMO_144[0],			/* 型データメモ１４４ */
		&KAT_MEMO_145[0],			/* 型データメモ１４５ */
		&KAT_MEMO_146[0],			/* 型データメモ１４６ */
		&KAT_MEMO_147[0],			/* 型データメモ１４７ */
		&KAT_MEMO_148[0],			/* 型データメモ１４８ */
		&KAT_MEMO_149[0],			/* 型データメモ１４９ */
		&KAT_MEMO_150[0],			/* 型データメモ１５０ */
		&KAT_MEMO_151[0],			/* 型データメモ１５１ */
		&KAT_MEMO_152[0],			/* 型データメモ１５２ */
		&KAT_MEMO_153[0],			/* 型データメモ１５３ */
		&KAT_MEMO_154[0],			/* 型データメモ１５４ */
		&KAT_MEMO_155[0],			/* 型データメモ１５５ */
		&KAT_MEMO_156[0],			/* 型データメモ１５６ */
		&KAT_MEMO_157[0],			/* 型データメモ１５７ */
		&KAT_MEMO_158[0],			/* 型データメモ１５８ */
		&KAT_MEMO_159[0],			/* 型データメモ１５９ */
		&KAT_MEMO_160[0],			/* 型データメモ１６０ */
		&KAT_MEMO_161[0],			/* 型データメモ１６１ */
		&KAT_MEMO_162[0],			/* 型データメモ１６２ */
		&KAT_MEMO_163[0],			/* 型データメモ１６３ */
		&KAT_MEMO_164[0],			/* 型データメモ１６４ */
		&KAT_MEMO_165[0],			/* 型データメモ１６５ */
		&KAT_MEMO_166[0],			/* 型データメモ１６６ */
		&KAT_MEMO_167[0],			/* 型データメモ１６７ */
		&KAT_MEMO_168[0],			/* 型データメモ１６８ */
		&KAT_MEMO_169[0],			/* 型データメモ１６９ */
		&KAT_MEMO_170[0],			/* 型データメモ１７０ */
		&KAT_MEMO_171[0],			/* 型データメモ１７１ */
		&KAT_MEMO_172[0],			/* 型データメモ１７２ */
		&KAT_MEMO_173[0],			/* 型データメモ１７３ */
		&KAT_MEMO_174[0],			/* 型データメモ１７４ */
		&KAT_MEMO_175[0],			/* 型データメモ１７５ */
		&KAT_MEMO_176[0],			/* 型データメモ１７６ */
		&KAT_MEMO_177[0],			/* 型データメモ１７７ */
		&KAT_MEMO_178[0],			/* 型データメモ１７８ */
		&KAT_MEMO_179[0],			/* 型データメモ１７９ */
		&KAT_MEMO_180[0],			/* 型データメモ１８０ */
		&KAT_MEMO_181[0],			/* 型データメモ１８１ */
		&KAT_MEMO_182[0],			/* 型データメモ１８２ */
		&KAT_MEMO_183[0],			/* 型データメモ１８３ */
		&KAT_MEMO_184[0],			/* 型データメモ１８４ */
		&KAT_MEMO_185[0],			/* 型データメモ１８５ */
		&KAT_MEMO_186[0],			/* 型データメモ１８６ */
		&KAT_MEMO_187[0],			/* 型データメモ１８７ */
		&KAT_MEMO_188[0],			/* 型データメモ１８８ */
		&KAT_MEMO_189[0],			/* 型データメモ１８９ */
		&KAT_MEMO_190[0],			/* 型データメモ１９０ */
		&KAT_MEMO_191[0],			/* 型データメモ１９１ */
		&KAT_MEMO_192[0],			/* 型データメモ１９２ */
		&KAT_MEMO_193[0],			/* 型データメモ１９３ */
		&KAT_MEMO_194[0],			/* 型データメモ１９４ */
		&KAT_MEMO_195[0],			/* 型データメモ１９５ */
		&KAT_MEMO_196[0],			/* 型データメモ１９６ */
		&KAT_MEMO_197[0],			/* 型データメモ１９７ */
		&KAT_MEMO_198[0],			/* 型データメモ１９８ */
		&KAT_MEMO_199[0],			/* 型データメモ１９９ */
		&KAT_MEMO_200[0],			/* 型データメモ２００ */
		&KAT_MEMO_201[0],			/* 型データメモ１８１ */
		&KAT_MEMO_202[0],			/* 型データメモ１８２ */
		&KAT_MEMO_203[0],			/* 型データメモ１８３ */
		&KAT_MEMO_204[0],			/* 型データメモ１８４ */
		&KAT_MEMO_205[0],			/* 型データメモ１８５ */
		&KAT_MEMO_206[0],			/* 型データメモ１８６ */
		&KAT_MEMO_207[0],			/* 型データメモ１８７ */
		&KAT_MEMO_208[0],			/* 型データメモ１８８ */
		&KAT_MEMO_209[0],			/* 型データメモ１８９ */
		&KAT_MEMO_210[0],			/* 型データメモ１９０ */
		&KAT_MEMO_211[0],			/* 型データメモ１９１ */
		&KAT_MEMO_212[0],			/* 型データメモ１９２ */
		&KAT_MEMO_213[0],			/* 型データメモ１９３ */
		&KAT_MEMO_214[0],			/* 型データメモ１９４ */
		&KAT_MEMO_215[0],			/* 型データメモ１９５ */
		&KAT_MEMO_216[0],			/* 型データメモ１９６ */
		&KAT_MEMO_217[0],			/* 型データメモ１９７ */
		&KAT_MEMO_218[0],			/* 型データメモ１９８ */
		&KAT_MEMO_219[0],			/* 型データメモ１９９ */
		&KAT_MEMO_220[0]			/* 型データメモ２００ */
	};


/*
********************************************************************************
*  Module Name:		DATA_svsw
*  Function Name:
*  Input	:		ﾃﾞｰﾀ
*					ﾋﾞｯﾄﾊﾟﾀｰﾝ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
void	DATA_svsw(UNs data,UNs bit)
{
	if( 0 == (data & bit) ) {
		SV_CNT = 0;
		SW_CNT = 0;
		CSR_CNT = 0;
	}
}


/*
********************************************************************************
*  Module Name:		MIS_check
*  Function Name:	ミスフィード有無チェック
*  Input	:		なし
*  Return	: 		＝00:無し
*					≠00:あり
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	MIS_check(void)
{

//	return(SEQ_018_SV & 0x0f00);		//ﾐｽﾌｨｰﾄﾞ1,2,6,8(1:有)
//V05g	return(SEQ_018_SV & 0x0700);		//ﾐｽﾌｨｰﾄﾞ1,2,6(1:有)
	return(SEQ_018_SV & 0x0F00);		//ﾐｽﾌｨｰﾄﾞ1,2,4,6(1:有)

}


/*
********************************************************************************
*  Module Name:		ROT1_check
*  Function Name:	ロータリカム１～８有無チェック
*  Input	:		なし
*  Return	: 		＝00:無し
*					≠00:あり
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	ROT1_check(void)
{

	return(SEQ_018_SV & 0x5000);		//ﾛｰﾀﾘｶﾑ1～4,5～8(1:有)

}


/*
********************************************************************************
*  Module Name:		ROT2_check
*  Function Name:	ロータリカム９～１６有無チェック
*  Input	:		なし
*  Return	: 		＝00:無し
*					≠00:あり
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	ROT2_check(void)
{

	return(SEQ_019_SV & 0x0005);		//ﾛｰﾀﾘｶﾑ9～12,13～16(1:有)

}

/*
********************************************************************************
*  Module Name:		ROT3_check
*  Function Name:	ロータリカム１７～２０有無チェック
*  Input	:		なし
*  Return	: 		＝00:無し
*					≠00:あり
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	ROT3_check(void)
{

	return(SEQ_018_SV & BIT_6);			//ﾛｰﾀﾘｶﾑ17～20(1:有)

}


/*
********************************************************************************
*  Module Name:		EJE_check
*  Function Name:	エジェクタ有無チェック
*  Input	:		なし
*  Return	: 		＝00:無し
*					≠00:あり
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-29
********************************************************************************
*/
UNi	EJE_check(void)
{
	UNs		i;

	i = SEQ_017_SV & 0x2490;			//ｴｼﾞｪｸﾀ1,2,3,4(1:有)
	i |= SEQ_018_SV & 0x0009;			//ｴｼﾞｪｸﾀ5,6(1:有)

	return( i );
}


/*
********************************************************************************
*  Module Name:		DISP_cam_csr_name
*  Function Name:	カムカーソル名称表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-30
********************************************************************************
*/
void	DISP_cam_csr_name(void)
{
	UNs	c_no, cnt, *g_p, xy_no;
	UNi	t_no;

	if(CSR_CNT1 == 0 ){
		return;
	}
	for( cnt=CSR_CNT1, t_no=0 ; cnt > 0 ; cnt--, t_no++ ) {

		c_no = CSR_buff[t_no].SW56_UP;							//SW56上段ｷｬﾗｸﾀ
		if( c_no >= 0x80 && c_no < 0xc5 ) {						//0x80 ≦ 上段ｷｬﾗｸﾀ ＜ 0xc5
			if( 0 == (CSR_buff[t_no].TOK_NO & BIT_0)) {			//特殊番号(B0:ｶｰｿﾙ無し)
				g_p = SW56_Cam_Name_Tbl[c_no - 0x80];
				if( (c_no >= 0xa0) && (c_no < 0xb5) &&			//現在の名称表示処理？  CSR_SW56_UP=0AAH
					 (c_no != 0xaa) && (MLD_100_GNO != 0) ) {	//１１～１００型の名称＆メモ表示

					if( c_no < 0xab ){							//型管理番号を１０倍して型管理番号を細工する
						c_no -= 0xa0;							//名称表示
						g_p = KAT_sv_name_tbl[c_no+(MLD_100_GNO*10)+1];
					}
					else{
						c_no -= 0xab;							//メモ表示
						g_p = KAT_sv_memo_tbl[c_no+(MLD_100_GNO*10)+1];
					}
				}

				//名称リフレッシュ
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
				disp_moji_s(CSR_buff[t_no].XY_POS, g_p, &LCD_WORK1[0][0][0], 0x00);
#else
				disp_moji_s_color(
					CSR_buff[t_no].M_LEN,					/* ｷｬﾗｸ長			*/
					CSR_buff[t_no].X_POS,					/* 書出しX位置		*/
					CSR_buff[t_no].Y_POS,					/* 書出しY位置		*/
					CSR_buff[t_no].C_COL,					/* 文字色			*/
					CSR_buff[t_no].B_COL1,					/* 背景色			*/
					CSR_buff[t_no].SIZE,					/* 文字ｻｲｽﾞ			*/
					g_p,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE								/* 表示ﾒﾓﾘ			*/
					);
				disp_moji_s_rif(
					CSR_buff[t_no].M_LEN,					/* ｷｬﾗｸ長			*/
					CSR_buff[t_no].X_POS,					/* 書出しX位置		*/
					CSR_buff[t_no].Y_POS,					/* 書出しY位置		*/
					CSR_buff[t_no].SIZE					/* 文字ｻｲｽﾞ			*/
					);
#endif
			}
		}
	}
	
//V06p
	if ( (CSR_buff[0].SW56_UP == 0x88) && (SEQ_019_SV & BIT_0) && (SEQ_PAR_113 & BIT_14) ) {	//ﾛｰﾀﾘｶﾑ9-12有効／ﾛｰﾀﾘｶﾑ9を光線遮光
		g_p = &PV_CAMSWD_C1[0];							//光線遮光とする。
		disp_moji_s_color(
			CSR_buff[0].M_LEN,					/* ｷｬﾗｸ長			*/
			CSR_buff[0].X_POS,					/* 書出しX位置		*/
			CSR_buff[0].Y_POS,					/* 書出しY位置		*/
			CSR_buff[0].C_COL,					/* 文字色			*/
			CSR_buff[0].B_COL1,					/* 背景色			*/
			CSR_buff[0].SIZE,					/* 文字ｻｲｽﾞ			*/
			g_p,									/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
			LCD_VBASE								/* 表示ﾒﾓﾘ			*/
			);
		disp_moji_s_rif(
			CSR_buff[0].M_LEN,					/* ｷｬﾗｸ長			*/
			CSR_buff[0].X_POS,					/* 書出しX位置		*/
			CSR_buff[0].Y_POS,					/* 書出しY位置		*/
			CSR_buff[0].SIZE					/* 文字ｻｲｽﾞ			*/
			);
	}

}


#if (mot100_test == 1)
/*
********************************************************************************
*  Module Name:		DISP_step_csr_name
*  Function Name:	モーション行程No.カーソル表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shima		ON:2015-08-24
********************************************************************************
*/
void	DISP_step_csr_name(void)
{
	UNs		c_no, cnt, *g_p, xy_no;
	UNs		c_wk[16], w_bf;
	UNi		i, j, k, t_no;
	UNb		wk[16];
	UNl		bcd_d;
	UNs		dan, d_no, end_page;

	if ( (GAMEN_NO != 3) && (GAMEN_NO != 28) ) {
		return;
	}

	if(CSR_CNT1 == 0 ){
		return;
	}

	memset(&wk[0], E_AS_SP, 16);					//領域 ｽﾍﾟｰｽ ｸﾘｱ

	dan = 5;
	end_page = (SV_DANSUU_SRV - 1) / 5;
	if (SV_MOT_PAGE >= end_page) {
		dan = SV_DANSUU_SRV % 5;			//表示段数
		if (dan==0) {
			dan = 5;
		}
	}
	d_no = 97;

	for (; dan>0; dan--, d_no++) {
		for( cnt=CSR_CNT1, t_no=0 ; cnt > 0 ; cnt--, t_no++ ) {
			if (CSR_buff[t_no].DATA_NO == d_no) {
				bcd_d = SV0_DISP_STEP_NO[d_no-97];
				bcd_d = HEX_BCD4(bcd_d);					//HEX → BCD 変換
				BCD_ASCII(bcd_d, &wk[0]);					//BCD→ASCII 変換

				i = CSR_buff[t_no].XY_POS >> 10;			//BYTE -> WORD に変換
				for( j=0 ; i > 0 ; i--, j++ ){
					w_bf = wk[i-1];
					w_bf <<= 8;
					if(i <= 1){
						w_bf |= (UNb)E_AS_SP;				//スペース［ASCIIｺｰﾄﾞ］
					}
					else{
						i--;
						w_bf |= wk[i-1];
					}
					c_wk[j] = w_bf;
				}

				//名称リフレッシュ
				disp_moji_s_color(
					2,										/* ｷｬﾗｸ長			CSR_buff[t_no].M_LEN */
					CSR_buff[t_no].X_POS,					/* 書出しX位置		*/
					CSR_buff[t_no].Y_POS,					/* 書出しY位置		*/
					CSR_buff[t_no].C_COL,					/* 文字色			*/
					CSR_buff[t_no].B_COL1,					/* 背景色			*/
					CSR_buff[t_no].SIZE,					/* 文字ｻｲｽﾞ			*/
					&c_wk[0],								/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
					LCD_VBASE								/* 表示ﾒﾓﾘ			*/
					);
//				disp_moji_s_rif(
//					CSR_buff[t_no].M_LEN,					/* ｷｬﾗｸ長			*/
//					CSR_buff[t_no].X_POS,					/* 書出しX位置		*/
//					CSR_buff[t_no].Y_POS,					/* 書出しY位置		*/
//					CSR_buff[t_no].SIZE					/* 文字ｻｲｽﾞ			*/
//					);
				break;
			}
		}
	}
}
#endif


/*
********************************************************************************
*  Module Name:		CAM_next_cls
*  Function Name:	設定値の次のキャラクタをスペースする
*  Input	:		情報ﾃｰﾌﾞﾙの番号
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	CAM_next_cls(UNs t_no)
{
	UNs		xy_no, xy_no2;

	xy_no2 = xy_no = SV_buff[t_no].XY_POS;
	xy_no &= 0x03ff;									//次ｷｬﾗｸﾀ位置の算出
	xy_no2 >>= 6;
	xy_no2 &= 0x03f0;
	xy_no += xy_no2;
	xy_no &= 0x03ff;
	xy_no |= 0x0400;									//ｶｰｿﾙ長 1を設定
	disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定

}


/*
********************************************************************************
*  Module Name:		LENG_svpv
*  Function Name:	小数点の変更(設定値&実測値)
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					情報ﾃｰﾌﾞﾙの少数点位置
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	LENG_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].TEN_POS = ten_pos;				//少数点の位置 変更
		}
	}

															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			PV_buff[t_no].TEN_POS = ten_pos;				//少数点の位置 変更
		}
	}
}


/*
********************************************************************************
*  Module Name:		kag_to_kaj_sub_chg
*  Function Name:	下限位置→目標荷重 ｻﾌﾞﾙｰﾁﾝNo.切換
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-07-05		V01k
********************************************************************************
*/
void	kag_to_kaj_sub_chg(void)
{
	UNs		cnt, t_no;
	UNs		xy_no, *g_p;
	UNl		adr;

//V01m	if (SEQ_024_SV & BIT_4)								//荷重補正あり？
	if (SEQ_050_SV & BIT_9)								//荷重補正あり？
	{
		/*「下限」→「荷重」*/
#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		xy_no = 3;							// 3行目
		xy_no |= /*32 V01k*/23<<4;			// 32桁目 -> 23桁目
		xy_no |= /*4 V01k*/6<<10;			// 4文字 -> 6文字
		g_p = mess_adr_shr(7);				//メッセージ画面キャラクタアドレス検索
		g_p += 66*5;						//ｷｬﾗｸﾀNo.10倍
		disp_moji_s(xy_no, g_p, &LCD_WORK1[0][0][0], 0x00);		//文字表示用文字ｺｰﾄﾞ→ﾄﾞｯﾄ変換
#else
		for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
			if(CSR_buff[t_no].DATA_NO == 117)				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			{
				CSR_buff[t_no].CARA_NO = 510;
			}
		}
#endif
		for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
			if(SV_buff[t_no].GRP_NO == 117)				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			{
				SV_buff[t_no].DATA_ADR = &SV_KAJYUU_OBJP;	//格納先ｱﾄﾞﾚｽ変更	V01m(INS)
				SV_buff[t_no].TOK_FLG = 0;					//特殊ﾌﾗｸﾞの変更
				SV_buff[t_no].BYTE_NO = 2;					//ﾊﾞｲﾄ長の変更
			}
		}
		for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		// V01m(INS)
			if(SV_buff[t_no].GRP_NO == 118)				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			{
				SV_buff[t_no].DATA_ADR = &SV_KAJYUU_PRS;	//格納先ｱﾄﾞﾚｽ変更
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_cls
*  Function Name:	ｶｰｿﾙ情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	CSR_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SV_cls
*  Function Name:	設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	SV_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		PV_cls
*  Function Name:	実測値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	PV_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				PV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_cls
*  Function Name:	SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	SW_cls(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//SWﾃﾞｰﾀ情報テーブル
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				SW_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_cls_disp
*  Function Name:	SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの非表示/表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2014/03/17
********************************************************************************
*/
void	SW_cls_disp(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				SW_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
			}
			else {
				SW_buff[t_no].SUB_NO &= ~BIT_15;			//表示の設定
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EJE_grp
*  Function Name:	ｴｼﾞｪｸﾀ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号(開始)
*					情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号(終了)
*					ｴｼﾞｪｸﾀﾀｲﾏ 比較ﾋﾞｯﾄ
*					ｴｼﾞｪｸﾀ 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ 比較ﾋﾞｯﾄ
*					ｴｼﾞｪｸﾀ進角のｸﾞﾙｰﾌﾟ番号
*					ｴｼﾞｪｸﾀ進角 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ進角 比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	EJE_grp(UNs grp_sno, UNs grp_eno, UNs ejet_bit,
				 UNs eje_data, UNs eje_bit, UNs ejek_grp, UNs ejek_data, UNs ejek_bit, UNs eje_csr)
{
	UNs	cnt, t_no, t_no2, t_no3, t_no4;

	CSR_CLS_FLG = 0;
													//設定値情報テーブル
	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//ｴｼﾞｪｸ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no].GRP_NO == grp_sno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ1;
		}
	}
	goto EJ11;

EJ1:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//ｴｼﾞｪｸ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no2].GRP_NO == grp_sno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ2;
		}
	}
	goto EJ11;

EJ2:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//ｴｼﾞｪｸ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no3].GRP_NO == grp_sno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ3;
		}
	}
	goto EJ11;

EJ3:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//ｴｼﾞｪｸ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no4].GRP_NO == grp_sno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ4;
		}
	}
	goto EJ11;

EJ4:
	if( eje_data & eje_bit ){						//仕様無し？
		if(SEQ_034_SV & ejet_bit){					//ﾀｲﾏ選択あり？
			SV_buff[t_no].SUB_NO |= BIT_15;			//非表示の設定
			SV_buff[t_no2].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no3].SUB_NO &= ~BIT_15;		//表示の設定
			SV_buff[t_no4].SUB_NO &= ~BIT_15;		//表示の設定
		}
		else{										//なし
			SV_buff[t_no4].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no3].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no2].SUB_NO &= ~BIT_15;		//表示の設定
			SV_buff[t_no].SUB_NO &= ~BIT_15;		//表示の設定
		}
	}
	else{											//無し
		SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
		SV_buff[t_no2].SUB_NO |= BIT_15;			//非表示の設定
		SV_buff[t_no3].SUB_NO |= BIT_15;			//非表示の設定
		SV_buff[t_no4].SUB_NO |= BIT_15;			//非表示の設定
		CSR_CLS_FLG = 0xff;
	}


	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//ｴｼﾞｪｸ終了 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no].GRP_NO == grp_eno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ6;
		}
	}
	goto EJ11;

EJ6:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//ｴｼﾞｪｸ終了 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no2].GRP_NO == grp_eno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ7;
		}
	}
	goto EJ11;

EJ7:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//ｴｼﾞｪｸ終了 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no3].GRP_NO == grp_eno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ8;
		}
	}
	goto EJ11;

EJ8:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//ｴｼﾞｪｸ終了 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no4].GRP_NO == grp_eno) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto EJ9;
		}
	}
	goto EJ11;

EJ9:
	if( eje_data & eje_bit ){						//仕様無し？
		if(SEQ_034_SV & ejet_bit){					//ﾀｲﾏ選択あり？
			SV_buff[t_no].SUB_NO |= BIT_15;			//非表示の設定
			SV_buff[t_no2].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no3].SUB_NO &= ~BIT_15;		//表示の設定
			SV_buff[t_no4].SUB_NO &= ~BIT_15;		//表示の設定
		}
		else{										//なし
			SV_buff[t_no4].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no3].SUB_NO |= BIT_15;		//非表示の設定
			SV_buff[t_no2].SUB_NO &= ~BIT_15;		//表示の設定
			SV_buff[t_no].SUB_NO &= ~BIT_15;		//表示の設定
		}
	}
	else{											//無し
		SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
		SV_buff[t_no2].SUB_NO |= BIT_15;			//非表示の設定
		SV_buff[t_no3].SUB_NO |= BIT_15;			//非表示の設定
		SV_buff[t_no4].SUB_NO |= BIT_15;			//非表示の設定
		CSR_CLS_FLG = 0xff;
	}

EJ11:
	t_no = 0;										//ダミー

/* 進角データ有無管理 */
//	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//ｴｼﾞｪｸﾀ進角 ｻｰﾁ
//		if(SV_buff[t_no].GRP_NO == ejek_grp) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
//			if(00 == (eje_data & eje_bit) ||				//仕様無し？
//				00 == (ejek_data & ejek_bit)) {
//
//				SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
//				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(eje_csr);
//			}
//		}
//	}

}


/*
********************************************************************************
*  Module Name:		EJE_csr
*  Function Name:	ｴｼﾞｪｸﾀ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの設定値個数消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのSW56上段ｷｬﾗｸﾀ
*					ｴｼﾞｪｸﾀ 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ 比較ﾋﾞｯﾄ
*					ｴｼﾞｪｸﾀ進角 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ進角 比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	EJE_csr(UNs sw56_up, UNs eje_data, UNs eje_bit, UNs ejek_data, UNs ejek_bit, UNs eje_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//ｴｼﾞｪｸﾀ ｻｰﾁ
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56上段ｷｬﾗｸﾀ
//			if(00 == (ejek_data & ejek_bit)) {				//進角が存在しないときは非表示
//				CSR_buff[t_no].SV_MAX = 2;					//設定値ﾃｰﾌﾞﾙ個数
//			}
			if(00 == (eje_data & eje_bit)){					//仕様無し？
				CSR_buff[t_no].SV_MAX = 0;					//設定値ﾃｰﾌﾞﾙ個数
				CSR_buff[t_no].SW_MAX = 0;					//SWﾃｰﾌﾞﾙ個数
				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(eje_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		EJE_sw
*  Function Name:	ｴｼﾞｪｸﾀ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	EJE_sw(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				SW_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				SW_buff[t_no].TOK_FLG &= ~BIT_0;			//ON反転表示のｸﾘｱ
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_grp
*  Function Name:	ﾛｰﾀﾘｶﾑ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号(開始)
*					情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号(終了)
*					ｴｼﾞｪｸﾀﾀｲﾏ 比較ﾋﾞｯﾄ
*					ｴｼﾞｪｸﾀ 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ 比較ﾋﾞｯﾄ
*					ｴｼﾞｪｸﾀ進角のｸﾞﾙｰﾌﾟ番号
*					ｴｼﾞｪｸﾀ進角 比較ﾃﾞｰﾀ
*					ｴｼﾞｪｸﾀ進角 比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2016/11/15
********************************************************************************
*/
void	ROT_cam_tim(UNs grp_no, UNs rct_bit)
{
	UNs	cnt, t_no, t_no2, t_no3, t_no4, t_no5, t_no6, t_no7, t_no8;

	t_no = 0;
	for(cnt=SV_CNT ; cnt > 0 ; cnt--, t_no++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC1;
		}
	}
	goto RC11;

RC1:
	t_no2 = t_no;
	for( t_no2++ ; cnt > 0 ; cnt--, t_no2++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no2].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC2;
		}
	}
	goto RC11;

RC2:
	t_no3 = t_no2;
	for( t_no3++ ; cnt > 0 ; cnt--, t_no3++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no3].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC3;
		}
	}
	goto RC11;

RC3:
	t_no4 = t_no3;
	for( t_no4++ ; cnt > 0 ; cnt--, t_no4++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ｶﾑ側)
		if(SV_buff[t_no4].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC4;
		}
	}
	goto RC11;

RC4:
	t_no5 = t_no4;
	for( t_no5++ ; cnt > 0 ; cnt--, t_no5++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no5].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC5;
		}
	}
	goto RC11;

RC5:
	t_no6 = t_no5;
	for( t_no6++ ; cnt > 0 ; cnt--, t_no6++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no6].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC6;
		}
	}
	goto RC11;

RC6:
	t_no7 = t_no6;
	for( t_no7++ ; cnt > 0 ; cnt--, t_no7++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no7].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC7;
		}
	}
	goto RC11;

RC7:
	t_no8 = t_no7;
	for( t_no8++ ; cnt > 0 ; cnt--, t_no8++){		//ﾛｰﾀﾘｶﾑ開始 ｻｰﾁ(ﾀｲﾏｰ側)
		if(SV_buff[t_no8].GRP_NO == grp_no) {		//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			goto RC8;
		}
	}
	goto RC11;

RC8:
	if(SEQ_039_SV & rct_bit){					//ﾀｲﾏ選択あり？
		SV_buff[t_no].SUB_NO |= BIT_15;			//非表示の設定
		SV_buff[t_no2].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no3].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no4].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no5].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no6].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no7].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no8].SUB_NO &= ~BIT_15;		//表示の設定
	}
	else{										//なし
		SV_buff[t_no].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no2].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no3].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no4].SUB_NO &= ~BIT_15;		//表示の設定
		SV_buff[t_no5].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no6].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no7].SUB_NO |= BIT_15;		//非表示の設定
		SV_buff[t_no8].SUB_NO |= BIT_15;		//非表示の設定
	}

RC11:
	t_no = 0;										//ダミー

}


/*
********************************************************************************
*  Module Name:		ROT_cam_sv
*  Function Name:	ﾛｰﾀﾘｶﾑ用設定値情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのｶｰｿﾙ認識番号
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾋﾞｯﾄ
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾋﾞｯﾄ
*					情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					ﾛｰﾀﾘｶﾑ進角 比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_sv(UNs csr_no, UNs rot_bit, UNs rot_data,
				 UNs seq_data, UNs seq_bit, UNs grp_no, UNs rotk_bit, UNs rot_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//ｶｰｿﾙ認識番号 ｻｰﾁ
			if(00 == (rot_data & rot_bit) ||				//ﾛｰﾀﾘｶﾑ選択種別
				00 == (seq_data & seq_bit) ){				//ﾛｰﾀﾘｶﾑ有無
				SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
//				CAM_next_cls(t_no);							//設定値の次のキャラクタをスペースする
				CSR_CLS_FLG = 0xff;
			}
		}
	}

/* 進角無し時の処理 */										//2014/09/01
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & rotk_bit)) {				//ﾛｰﾀﾘｶﾑ有無
				SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(rot_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_sw
*  Function Name:	ﾛｰﾀﾘｶﾑ用SWﾃﾞｰﾀ情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾋﾞｯﾄ
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_sw(UNs grp_no, UNs rot_bit, UNs rot_data, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (rot_data & rot_bit) ||				//ﾛｰﾀﾘｶﾑ選択種別
				00 == (seq_data & seq_bit) ){				//ﾛｰﾀﾘｶﾑ有無
				SW_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				SW_buff[t_no].TOK_FLG &= ~BIT_0;			//ON反転表示のｸﾘｱ
			}
//2014/09/08			break;
		}
	}
}


/*
********************************************************************************
*  Module Name:		ROT_cam_csr
*  Function Name:	ﾛｰﾀﾘｶﾑ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのSW56上段ｷｬﾗｸﾀ
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾋﾞｯﾄ
*					ﾛｰﾀﾘｶﾑ選択種別比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾃﾞｰﾀ
*					ﾛｰﾀﾘｶﾑ 比較ﾋﾞｯﾄ
*					ﾛｰﾀﾘｶﾑ進角 比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	ROT_cam_csr(UNs sw56_up, UNs rot_bit, UNs rot_data,
				 UNs seq_data, UNs seq_bit, UNs rotk_bit, UNs rot_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//ﾛｰﾀﾘｶﾑ ｻｰﾁ
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56上段ｷｬﾗｸﾀ
			if(00 == (rot_data & rot_bit)) {				//仕様無し？
				CSR_buff[t_no].SV_MAX = 0;					//設定値ﾃｰﾌﾞﾙ個数
				CSR_buff[t_no].SW_MAX = 0;					//SWﾃｰﾌﾞﾙ個数
			}
			break;
		}
	}
//	if(00 == (seq_data & rotk_bit)) {						//進角が存在しないとき
//		CSR_buff[t_no].SV_MAX = 2;							//設定値ﾃｰﾌﾞﾙ個数
//	}

	if(00 == (seq_data & seq_bit)) {						//仕様無し
		CSR_buff[t_no].SV_MAX = 0;							//設定値ﾃｰﾌﾞﾙ個数
		CSR_buff[t_no].SW_MAX = 0;							//SWﾃｰﾌﾞﾙ個数
		CSR_buff[t_no].TOK_NO |= BIT_0;						//非表示の設定
		CSR_CLS_FLG = 0xff;
		CSR_disp_cls(rot_csr);
	}
}


/*
********************************************************************************
*  Module Name:		MIS_sv
*  Function Name:	ﾐｽﾌｨｰﾄﾞ用設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	MIS_sv(UNs grp_no, UNs seq_data, UNs seq_bit)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？

				SV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
//				CAM_next_cls(t_no);							//設定値の次のキャラクタをスペースする
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MIS_csr
*  Function Name:	ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのSW56上段ｷｬﾗｸﾀ
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*					ｶｰｿﾙ消去位置情報2
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	MIS_csr(UNs sw56_up, UNs seq_data, UNs seq_bit, UNs mis_csr, UNs mis_csr2)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){		//ﾛｰﾀﾘｶﾑ ｻｰﾁ
		if(CSR_buff[t_no].SW56_UP == sw56_up){				//SW56上段ｷｬﾗｸﾀ

			if(00 == (seq_data & seq_bit)) {				//仕様無し
				CSR_buff[t_no].SV_MAX = 0;					//設定値ﾃｰﾌﾞﾙ個数
				CSR_buff[t_no].SW_MAX = 0;					//SWﾃｰﾌﾞﾙ個数
				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定

				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(mis_csr);
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(mis_csr2);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		ATU_svpv
*  Function Name:	設定値情報ﾃｰﾌﾞﾙの変更
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					情報ﾃｰﾌﾞﾙの少数点位置
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	ATU_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no, xy_no;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].TEN_POS = ten_pos;				//少数点の位置 変更

			if(ten_pos == 00){
				xy_no = SV_buff[t_no].XY_POS;				//設定値表示のX,Y軸
				xy_no &= 0x03ff;							//カーソル長変更
				xy_no |= 0x0c00;							//半角３個
				xy_no += 0x0010;							//表示位置
				SV_buff[t_no].XY_POS = xy_no;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		KAJ_svpv
*  Function Name:	小数点の変更(設定値&実測値)
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					情報ﾃｰﾌﾞﾙの少数点位置
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shima		ON:2010-08-12		V05r
********************************************************************************
*/
void	KAJ_svpv(UNs grp_no, UNs ten_pos)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].TEN_POS = ten_pos;				//少数点の位置 変更
		}
	}
	
															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			PV_buff[t_no].TEN_POS = ten_pos;				//少数点の位置 変更
		}
	}
}


/*
********************************************************************************
*  Module Name:		DANsel_csr
*  Function Name:	ﾐｽﾌｨｰﾄﾞ用ｶｰｿﾙ情報ﾃｰﾌﾞﾙの消去処理
*  Input	:		情報ﾃｰﾌﾞﾙのSW56上段ｷｬﾗｸﾀ
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	DANsel_csr(UNs grp_no, UNs seq_data, UNs seq_bit, UNs dan_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++) {	//ﾛｰﾀﾘｶﾑ ｻｰﾁ
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)) {				//仕様無し？
				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(dan_csr);
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_sel
*  Function Name:	段取り用　各選択の消去処理
*  Input	:		ｼｰｹﾝｽ ﾃﾞｰﾀ･ｱﾄﾞﾚｽ
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*					ﾌﾗｸﾞ:0=b0～b7 / 1=b8～b15
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-06
********************************************************************************
*/
void	DAN_sel(UNs *seq_no, UNs seq_data, UNs seq_bit, UNs flag)
{
	UNs		data;

	data = *seq_no;

	if(flag == 00){							//b0～b7
		if(seq_data & seq_bit){
			data &= 0x001c;
			if( data != BIT_2 &&
				data != BIT_3 &&
				data != BIT_4 ) {

				*seq_no &= 0xff00;
				*seq_no |= BIT_2;
				ONOFF_FLG = 0xff;
			}
		}
		else if(data & 0x001c){
			*seq_no &= 0xff00;
			ONOFF_FLG = 0xff;
		}
	}
	else{									//b8～b15
		if(seq_data & seq_bit){
			data &= 0x1c00;
			if( data != BIT_10 &&
				data != BIT_11 &&
				data != BIT_12 ) {

				*seq_no &= 0x00ff;
				*seq_no |= BIT_10;
				ONOFF_FLG = 0xff;
			}
		}
		else if(data & 0x1c00){
			*seq_no &= 0x00ff;
			ONOFF_FLG = 0xff;
		}
	}
}


/*
********************************************************************************
*  Module Name:		DAN_csr_set(旧:CSR_G07_SET)
*  Function Name:	段取画面　表示した個数カウンタ
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-27
********************************************************************************
*/
void	DAN_csr_set(void)
{
	UNs		cnt;

	CSR_G07_NO1 = 0;					//カーソル先頭位置
	CSR_G07_NO2 = 0;					//カーソル最終位置
	DAN_CLS_CNT = 0;					//表示した個数カウンタ

	cnt = 1;

	if (GAMEN_NO == 8)				//V01r
	{
		if(SEQ_020_SV & BIT_14){			//金型自動交換
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

	cnt ++;
	}

	if(SEQ_020_SV & (BIT_6 | BIT_4)){	//スライド調節
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_4){				//上型クランパ
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_6){				//下型クランパ
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	cnt ++;
	if(SEQ_019_SV & BIT_8){				//ダイリフタ
		DAN_CLS_CNT ++;
		if(CSR_G07_NO1 == 0){
			CSR_G07_NO1 = cnt;
		}
		else{
			CSR_G07_NO2 = cnt;
		}
	}

	if (GAMEN_NO == 8)				//V01r
	{
		cnt ++;
		if(SEQ_019_SV & BIT_10){			//ダイクッション	V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_1){				//防護柵		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_15){			//ＭＢ			V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_020_SV & BIT_11){			//バランサ		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}

		cnt ++;
		if(SEQ_019_SV & (BIT_12 | BIT_13 | BIT_15)){	//ﾀﾞｲｸｯｼｮﾝ調節		V01j
			DAN_CLS_CNT ++;
			if(CSR_G07_NO1 == 0){
				CSR_G07_NO1 = cnt;
			}
			else{
				CSR_G07_NO2 = cnt;
			}
		}
	}

//V06p
	DAN_CLS_CNT ++;
	cnt ++;
	CSR_G07_NO2 = cnt;			//段取速度

}


/*
********************************************************************************
*  Module Name:		KAT_cls
*  Function Name:	型ﾃﾞｰﾀの実測値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	KAT_cls(UNs grp_no, UNs seq_data, UNs seq_bit, UNs kat_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				PV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(kat_csr);
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MEMO_cls
*  Function Name:	メモの実測値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*					比較ﾃﾞｰﾀ
*					比較ﾋﾞｯﾄ
*					ｶｰｿﾙ消去位置情報
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
********************************************************************************
*/
void	MEMO_cls(UNs grp_no, UNs seq_data, UNs seq_bit, UNs memo_csr)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(00 == (seq_data & seq_bit)){					//仕様無し？
				PV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
				CSR_CLS_FLG = 0xff;
				CSR_disp_cls(memo_csr);
				break;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		PVdata_non_sub
*  Function Name:	実測値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-16
********************************************************************************
*/
void	PVdata_non_sub(void)
{
	UNs	i, j, k;

	PVDATA_NON = 0;

	for( i=0,j=0, k=PV_CNT ; k > 0 ; i++,k-- ) {
		if( PV_buff[i].SUB_NO & BIT_15 ) {				//実測値データ未使用？
			j ++;
		}
		else if( PV_buff[i].TOK_FLG & BIT_6 ) {			//単位％型データ？
			j ++;
		}
	}
	if( j >= PV_CNT ) {
		PVDATA_NON = 0xff;
	}
}


/*
********************************************************************************
*  Module Name:		SCAN_kat_cls
*  Function Name:
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-16
********************************************************************************
*/
void	SCAN_kat_cls(void)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;

	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == 56 &&					//型ﾃﾞｰﾀ？
			00 == (SEQ_PAR_107 & BIT_0)){					//仕様無し？
			PV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
			CSR_CLS_FLG = 0xff;
			CSR_disp_cls(81);
			goto KAT_CLS_130;
		}
	}
	goto KAT_CLS_200;

KAT_CLS_130:
	for(t_no++ ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == 56 &&					//型ﾃﾞｰﾀ？
			00 == (SEQ_PAR_107 & BIT_0)){					//仕様無し？
			PV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
			CSR_CLS_FLG = 0xff;
			CSR_disp_cls(61);
			break;
		}
	}

KAT_CLS_200:
	CSR_CLS_FLG = 0;
//	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
//		if(PV_buff[t_no].GRP_NO == 57){						//ｽｷｬﾝﾀｲﾑ表示？
//			if(SEQ_020_SV & BIT_3){							//ｽｷｬﾝﾀｲﾑ表示？
//				t_no++;
//				PV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
//				CSR_CLS_FLG = 0xff;
//				CSR_disp_cls(61);
//			}
//			else{
//				PV_buff[t_no].SUB_NO |= BIT_15;				//非表示の設定
//				CSR_CLS_FLG = 0xff;
//			}
//			break;
//		}
//	}

}


/*
********************************************************************************
*  Module Name:		ADC_NEXT_cls
*  Function Name:	
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2016/04/22
********************************************************************************
*/
void	ADC_NEXT_cls(void)
{
	if(WINDOW_NO == 12)
	{
		if(SEQ_047_SV & BIT_7)
		{
			CSR_CNT = 0;					/* 搬出が選ばれてステップモニタ画面を表示する場合はカーソルを表示しない */
			CSR_MOVE_OK_FLG = 0xff;			/* カーソル移動ＮＧ */
			SV_buff[0].SUB_NO |= BIT_15;	/* 次型番号消去 */
			PV_buff[0].SUB_NO |= BIT_15;	/* 次型番号消去 */

			CSR_CLS_FLG = 0xff;
//V00iM			CSR_disp_cls(129);
			disp_moji_s_paint(			/* 右「設定値」文字消す	*/
				40,						/* ｷｬﾗｸ長(半角で)	*/
				0,						/* 書出しX位置		*/
				192,					/* 書出しY位置		*/
				GAMENn_HEAD.scr_col,	/* 塗り潰し色		*/
				0x0202,					/* 文字ｻｲｽﾞ			*/
				LCD_VBASE				/* 表示ﾒﾓﾘ			*/
				);
			CSR_buff[0].TOK_NO |= BIT_0;			// V00iM
		}
	}
	else
	{
		if(SEQ_047_SV & BIT_7)
		{
			CSR_CNT = 0;					/* 搬出が選ばれてステップモニタ画面を表示する場合はカーソルを表示しない */
			CSR_MOVE_OK_FLG = 0xff;			/* カーソル移動ＮＧ */
			PV_buff[0].SUB_NO |= BIT_15;	/* 次型番号消去 */
			PV_buff[1].SUB_NO |= BIT_15;	/* 次型番号消去 */

			CSR_CLS_FLG = 0xff;
//V00iM			CSR_disp_cls(129);
			disp_moji_s_paint(			/* 右「設定値」文字消す	*/
				40,						/* ｷｬﾗｸ長(半角で)	*/
				0,						/* 書出しX位置		*/
				192,					/* 書出しY位置		*/
				GAMENn_HEAD.scr_col,	/* 塗り潰し色		*/
				0x0202,					/* 文字ｻｲｽﾞ			*/
				LCD_VBASE				/* 表示ﾒﾓﾘ			*/
				);
		}
	}
}


/*
********************************************************************************
*  Module Name:		NAME_cls_sub
*  Function Name:	第一言語　ｶﾀｶﾅの非表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-16
********************************************************************************
*/
void	NAME_cls_sub(void)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){

		if(CSR_buff[t_no].DATA_NO == 74) {					//名称第二国で削除？
			if(SV_GENGO_KAT == 1 ||							//第一言語カタカナ不要(1:ｶﾀｶﾅ不要)
				language_chg != 00) {						//日本語？

				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS_swcara
*  Function Name:	ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-16
********************************************************************************
*/
void	MISS_swcara(void)
{
	UNs	s_bit;
	UNi	cnt, t_no;
															//ｶｰｿﾙ情報テーブル
	s_bit = SYS_MISSEL_SV;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].SW6_DN == 58 ||					//SW6下段ｷｬﾗｸﾀ(表示用ｷｬﾗｸﾀ番号 ｻｰﾁ)
			CSR_buff[t_no].SW6_DN == 59){					//SW6下段ｷｬﾗｸﾀ(表示用ｷｬﾗｸﾀ番号 ｻｰﾁ)
			if( s_bit & BIT_0 ){
				CSR_buff[t_no].SW6_DN = 59;					//表示用ｷｬﾗｸﾀ番号 変更(接／排)
			}
			s_bit >>= 1;
		}
	}

															//SWﾃﾞｰﾀ情報テーブル
	s_bit = SYS_MISSEL_SV;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CARA_NO == 22 ||					//表示用ｷｬﾗｸﾀ番号 ｻｰﾁ
			SW_buff[t_no].CARA_NO == 23) {					//表示用ｷｬﾗｸﾀ番号 ｻｰﾁ
			if( s_bit & BIT_0 ){
				SW_buff[t_no].CARA_NO = 23;					//表示用ｷｬﾗｸﾀ番号 変更
			}
			s_bit >>= 1;
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS56_swcara
*  Function Name:	ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:A.Shimamura		ON:2005-04-28	V01r
********************************************************************************
*/
void	MISS56_swcara(void)
{
	UNs	s_bit;
	UNi	cnt, t_no;
															//ｶｰｿﾙ情報テーブル
	s_bit = SYS_MISSEL_SV;
	s_bit >>= 4;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].SW6_DN == 58 ||					//SW6下段ｷｬﾗｸﾀ(表示用ｷｬﾗｸﾀ番号 ｻｰﾁ)
			CSR_buff[t_no].SW6_DN == 59){					//SW6下段ｷｬﾗｸﾀ(表示用ｷｬﾗｸﾀ番号 ｻｰﾁ)
			if( s_bit & BIT_0 ){
				CSR_buff[t_no].SW6_DN = 59;					//表示用ｷｬﾗｸﾀ番号 変更(接／排)
			}
			s_bit >>= 1;
		}
	}

															//SWﾃﾞｰﾀ情報テーブル
	s_bit = SYS_MISSEL_SV;
	s_bit >>= 4;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CARA_NO == 22 ||					//表示用ｷｬﾗｸﾀ番号 ｻｰﾁ
			SW_buff[t_no].CARA_NO == 23) {					//表示用ｷｬﾗｸﾀ番号 ｻｰﾁ
			if( s_bit & BIT_0 ){
				SW_buff[t_no].CARA_NO = 23;					//表示用ｷｬﾗｸﾀ番号 変更
			}
			s_bit >>= 1;
		}
	}
}


/*
********************************************************************************
*  Module Name:		MISS_swcara_win
*  Function Name:	ﾐｽﾌｨｰﾄﾞSW表示ｷｬﾗ切換えの非表示(ｳｨﾝﾄﾞｳ用)
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-19
********************************************************************************
*/
const	UNs	MISS_win_Tbl[9][4]={
		{15, BIT_8, BIT_0, 1},			//SW56上段ｷｬﾗｸﾀ, ﾋﾞｯﾄ位置, ﾋﾞｯﾄ位置, 予備2
		{16, BIT_9, BIT_1, 2},
		{17, BIT_10,BIT_2, 3},
		{18, BIT_11,BIT_3, 4},
		{79, BIT_12,BIT_4, 5},
		{80, BIT_13,BIT_5, 6},
		{81, BIT_14,BIT_6, 7},
		{82, BIT_15,BIT_7, 8},
		{0xff, 0x00, 0x00, 0xff}
	};

void	MISS_swcara_win(void)
{
	UNi	cnt, t_no, tp_no;
	UNs	s_bit;

															//ｶｰｿﾙ情報テーブル
	s_bit = SYS_MISSEL_SV;
	tp_no = 0;
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if( CSR_buff[t_no].SW56_UP == MISS_win_Tbl[tp_no][0] ){
			if(00 == (SEQ_037_SV & MISS_win_Tbl[tp_no][1])){
				CSR_buff[t_no].SW5_DN = 61;					//切／接
			}
			else{
				if(00 == (s_bit & MISS_win_Tbl[tp_no][2])){
					CSR_buff[t_no].SW5_DN = 62;				//切／保
				}
				else{
					CSR_buff[t_no].SW5_DN = 63;				//切／排
				}
			}
			tp_no++;
		}
	}

															//SWﾃﾞｰﾀ情報テーブル
	s_bit = SYS_MISSEL_SV;
	tp_no = 0;
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if( SW_buff[t_no].YOBI2 == MISS_win_Tbl[tp_no][3] ){
			if(00 == (SEQ_037_SV & MISS_win_Tbl[tp_no][1])){
				SW_buff[t_no].CARA_NO = 24;					//切／接
			}
			else{
				if(00 == (s_bit & MISS_win_Tbl[tp_no][2])){
					SW_buff[t_no].CARA_NO = 25;				//切／保
				}
				else{
					SW_buff[t_no].CARA_NO = 26;				//切／排
				}
			}
			tp_no++;
		}
	}
}


/*
********************************************************************************
*  Module Name:		mmon_tbl_cls
*  Function Name:	ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	mmon_tbl_cls(UNs grp_no)
{
	UNs	cnt, t_no;

															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			CSR_buff[t_no].TOK_NO |= BIT_0;					//非表示の設定
		}
	}

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
		}
	}

															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			PV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
		}
	}

															//SWﾃﾞｰﾀ情報テーブル
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SW_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
		}
	}

}


/*
********************************************************************************
*  Module Name:		mmon_tbl_open
*  Function Name:	ﾓｰｼｮﾝ設定　情報ﾃｰﾌﾞﾙの表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	mmon_tbl_open(UNs grp_no)
{
	UNs	cnt, t_no;

															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			CSR_buff[t_no].TOK_NO &= ~BIT_0;				//表示の設定
		}
	}

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//表示の設定
		}
	}

															//実測値情報テーブル
	for(cnt=PV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(PV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			PV_buff[t_no].SUB_NO &= ~BIT_15;				//表示の設定
		}
	}

															//SWﾃﾞｰﾀ情報テーブル
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SW_buff[t_no].SUB_NO &= ~BIT_15;				//表示の設定
		}
	}

}


/*
********************************************************************************
*  Module Name:		grpno_sv_cls
*  Function Name:	ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	grpno_sv_cls(UNs grp_no)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_cls
*  Function Name:	ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	csrno_sv_cls(UNs csr_no)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO |= BIT_15;					//非表示の設定
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_open
*  Function Name:	ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	grpno_sv_open(UNs grp_no)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//表示の設定
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_open
*  Function Name:	ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙの表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-25
********************************************************************************
*/
void	csrno_sv_open(UNs csr_no)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			SV_buff[t_no].SUB_NO &= ~BIT_15;				//表示の設定
		}
	}
}


/*
********************************************************************************
*  Module Name:		grpno_sv_srch
*  Function Name:	ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*
*  Return	: 		設定値の情報ﾃｰﾌﾞﾙの番号
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-08-02
********************************************************************************
*/
UNs		grpno_sv_srch(UNs grp_no)
{
	UNs	cnt, t_no;

															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			return(t_no);
		}
	}
	return(0xffff);
}


/*
********************************************************************************
*  Module Name:		SV_col_chg
*  Function Name:	仕様による背景色の変更
*  Input	:		削除番号
*  Return	: 		なし
*  Note		:		グループ番号から検索
*
*  履 歴	:A.Shimamura		ON:2010-12-06		V06b
********************************************************************************
*/
void	SV_col_chg(UNs grp_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].GRP_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
				SV_buff[t_no].C_COL  = MOJI_COL;			//文字色の変更
				SV_buff[t_no].B_COL1 = BAK_COL1;			//背景色の変更
				SV_buff[t_no].B_COL2 = BAK_COL2;			//背景色の変更
		}
	}
}


/*
********************************************************************************
*  Module Name:		SV_col_chg2
*  Function Name:	仕様による背景色の変更
*  Input	:		削除番号
*  Return	: 		なし
*  Note		:		カーソル識別番号から検索
*
*  履 歴	:A.Shimamura		ON:2010-12-06		V06m
********************************************************************************
*/
void	SV_col_chg2(UNs csr_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//設定値情報テーブル
	for(cnt=SV_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SV_buff[t_no].CSR_NO == csr_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
				SV_buff[t_no].C_COL  = MOJI_COL;			//文字色の変更
				SV_buff[t_no].B_COL1 = BAK_COL1;			//背景色の変更
				SV_buff[t_no].B_COL2 = BAK_COL2;			//背景色の変更
		}
	}
}


/*
********************************************************************************
*  Module Name:		SW_col_chg2
*  Function Name:	仕様による背景色の変更
*  Input	:		削除番号
*  Return	: 		なし
*  Note		:		カーソル識別番号から検索
*
*  履 歴	:A.Shimamura		ON:2010-12-06		V06m
********************************************************************************
*/
void	SW_col_chg2(UNs csr_no, UNs MOJI_COL, UNs BAK_COL1, UNs BAK_COL2)
{
	UNs	cnt, t_no;
															//設定値情報テーブル
	for(cnt=SW_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(SW_buff[t_no].CSR_NO == csr_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
				SW_buff[t_no].C_COL  = MOJI_COL;			//文字色の変更
				SW_buff[t_no].B_COL1 = BAK_COL1;			//背景色の変更
				SW_buff[t_no].B_COL2 = BAK_COL2;			//背景色の変更
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_cls_tokusyu
*  Function Name:	ｶｰｿﾙ情報ﾃｰﾌﾞﾙの非表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*  Input	:		情報ﾃｰﾌﾞﾙのSW56ｷｬﾗｸﾀ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	CSR_cls_tokusyu(UNs grp_no, UNs sw56_up)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(CSR_buff[t_no].SW56_UP == sw56_up) {			//SW56上段番号 ｻｰﾁ
				CSR_buff[t_no].TOK_NO |= BIT_0;				//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_opn_tokusyu
*  Function Name:	ｶｰｿﾙ情報ﾃｰﾌﾞﾙの表示 設定
*  Input	:		情報ﾃｰﾌﾞﾙのｸﾞﾙｰﾌﾟ番号
*  Input	:		情報ﾃｰﾌﾞﾙのSW56ｷｬﾗｸﾀ番号
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-12
********************************************************************************
*/
void	CSR_opn_tokusyu(UNs grp_no, UNs sw56_up)
{
	UNs	cnt, t_no;

	CSR_CLS_FLG = 0;
															//ｶｰｿﾙ情報テーブル
	for(cnt=CSR_CNT, t_no=0 ; cnt > 0 ; cnt--, t_no++){
		if(CSR_buff[t_no].DATA_NO == grp_no) {				//ｸﾞﾙｰﾌﾟ番号 ｻｰﾁ
			if(CSR_buff[t_no].SW56_UP == sw56_up) {			//SW56上段番号 ｻｰﾁ
				CSR_buff[t_no].TOK_NO &= ~BIT_0;			//非表示の設定
				CSR_CLS_FLG = 0xff;
			}
		}
	}
}


/*** END ***/
