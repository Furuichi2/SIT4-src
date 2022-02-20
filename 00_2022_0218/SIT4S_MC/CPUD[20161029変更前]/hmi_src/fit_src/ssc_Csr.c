/************************************************************************************/
/*																					*/
/*		㈱小松製作所殿向け　ＳＩＴ－Ｓ　制御プログラム								*/
/*																					*/
/*----------------------------------------------------------------------------------*/
/*																					*/
/*			ｶｰｿﾙ/設定値/実測値/SWﾃﾞｰﾀ　の情報ﾃｰﾌﾞﾙ関係								*/
/*																					*/
/************************************************************************************/
/*	変更履歴
*		原本(asm)		：Katsushige Mamada
*		改版(asm -> c)	：FIT)田端		ON:2002-05-22
*
*************************************************************************************/

#include "string.h"								//標準ライブラリ

#include "ssc_ver1.h"							//各種の共通定義
#include	"cm_equ1.h"		//MCにて分離

#include "ssc_def.h"							//各種の共通定義
#include "ssc_ext.h"							//参照関数定義
#include "ssc_fram_ext.h"						//参照変数定義
#include "ssc_wk_ext.h"							//参照変数定義

#include	"dp_cpud.h"		//[MC-add 2013-11]
//#include "dp_cpuab.h"							//参照変数定義

#include "ssa_opram.h"							//OPRAM参照変数定義
#include "ssc_dpram_seq_ext.h"					//参照変数定義


/* 外部参照関数定義 -------------------------------------------------- */
extern	UNs		swap_iw(void *);						//ｲﾝﾃﾙ形式の格納ﾃﾞｰﾀを取得(word)

/* 外部参照変数定義 -------------------------------------------------- */
extern	UNs		SEQ_PAR_033, SEQ_PAR_035, SEQ_PAR_041, SEQ_PAR_042, SEQ_PAR_043, SEQ_PAR_044, SEQ_PAR_045, SEQ_PAR_046;
extern	UNs		SEQ_PAR_050;
extern	UNs		SEQ_PAR_101;
extern	UNb		LCD_VRAM[PanelHeight][PanelWidth];
extern	UNb		LCD_VBASE[PanelHeight][PanelWidth];

/* 定数定義 ---------------------------------------------------------- */
extern	const	UNs	SW56_Up_Pos_Tbl_color[13][2];

/* データ型定義 ------------------------------------------------------ */
/* プロトタイプ宣言 -------------------------------------------------- */
void	CSR_move(UNs, UNs);						//カーソル移動

UNs		CSR_pos_chk(void);						//カーソル位置存在チェック
UNi		CSR_pos_shr_dn(UNs, UNs);				//カーソル位置　下検索
UNi		CSR_pos_shr_up(UNs, UNs);				//カーソル位置　上検索
void	CSR_disp(void);							//カーソル表示
void	CSR_disp_off(void);						//カーソル表示消去
void	CSR_disp_cls(UNs);						//仕様有無によるカーソル表示削除
void	CSR_sw56_disp(void);					//ＳＷ５６キャラクタ表示

void	SUBERI_out(void);						//スベリ量カーソル信号出力

void	SEI_test_out_sw5(void);					//生産設定ﾃｽﾄ出力処理(SW5)
void	SEI_test_out_sw6(void);					//生産設定ﾃｽﾄ出力処理(SW6)
void	csr_sw56_sub(UNs);						//SW5/SW6 ﾃﾞｰﾀ処理番号 処理

void	DYHITO_POS_Teaching(void);				//V00m
void	KAJYUU_Teaching(void);					//V01k

void	INS_MOTION(void);						//V06g
void	Sinkaku_Agl_Tim_Chg(UNs *SEQ, UNs seqbit, UNs t_no1, UNs t_no2);		//2014/09/01
void	INS_FIXARA_SPD(void);					//2014/09/10


/* 内部変数定義 ------------------------------------------------------ */
/* テーブル定義 ------------------------------------------------------ */
typedef struct {
	UNs	*ADDR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNs	BIT_P;			//ﾋﾞｯﾄﾊﾟﾀｰﾝ
	} EJE_SW6_TDEF;

const	EJE_SW6_TDEF	Eje_sw6_Tbl[6]={
			{&SEQ_017_SV, BIT_5},		//エジェクタ１　タイマ仕様有無
			{&SEQ_017_SV, BIT_8},		//エジェクタ２　タイマ仕様有無
			{&SEQ_017_SV, BIT_B},		//エジェクタ３　タイマ仕様有無
			{&SEQ_017_SV, BIT_E},		//エジェクタ４　タイマ仕様有無
			{&SEQ_018_SV, BIT_1},		//エジェクタ５　タイマ仕様有無
			{&SEQ_018_SV, BIT_4}		//エジェクタ６　タイマ仕様有無
		};

typedef struct {
	UNs	LCD_LINE;			//行
	UNs	LCD_KETA;			//桁
	UNs	LCD_BYTE;			//ﾊﾞｲﾄ長
	} CSR_CLS_TDEF;

const	CSR_CLS_TDEF	Csr_disp_cls_Tbl[153] = {
//		行, 桁, 数,
		{00, 00, 00},			//0
		{5,  23, 17},			//1		DW	5*40*16+23,16	; 1/*  ロットカウンタ１　カーソル位置 	*/
		{7,  23, 17},			//2		DW	7*40*16+23,16	; 2/*  ロットカウンタ１　設定文字 	*/
		{8,  23, 17},			//3		DW	8*40*16+23,16	; 3/*  ロットカウンタ２　カーソル位置 	*/
		{10, 23, 17},			//4		DW	10*40*16+23,16	; 4/*  ロットカウンタ３　設定文字 	*/
		{11, 17, 23},			//5		DW	11*40*16+18,21	; 5/*  ダイハイト固定文字	 	*/
		{12, 00, 40},			//6		DW	12*40*16+0,40	; 6/*  荷重実測表示固定文字		*/
		{5,  00, 40},			//7		DW	5*40*16+0,40	; 7/*  ロットカウンタ１　一行		*/
		{6,  00, 40},			//8		DW	6*40*16+0,40	; 8/*  ロットカウンタ２　一行		*/
		{7,  00, 20},			//9		DW	7*40*16+0,20	; 9/*  自動調節表示			*/
		{8,  00, 20},			//10	DW	8*40*16+0,20	;10/*  生産自動調節表示			*/
		{9,  00, 20},			//11	DW	9*40*16+0,20	;11/*  生産自動調節表示			*/
		{10, 00, 20},			//12	DW	10*40*16+0,20	;12/*  生産自動調節表示			*/
		{11, 00, 20},			//13	DW	11*40*16+0,20	;13/*  バランサ圧力表示			*/
		{7,  20, 20},			//14	DW	7*40*16+20,20	;14/*  荷重表示				*/
		{8,  20, 20},			//15	DW	8*40*16+20,20	;15/*  荷重表示				*/
		{9,  20, 20},			//16	DW	9*40*16+20,20	;16/*  荷重表示				*/
		{10, 20, 20},			//17	DW	10*40*16+20,20	;17/*  荷重表示				*/
		{11, 20, 20},			//18	DW	11*40*16+20,20	;18/*  荷重表示				*/
		{4,  22, 18},			//19	DW	4*40*16+22,18	;19/*  エジェクタ１進角表示		*/
		{5,  22, 18},			//20	DW	5*40*16+22,18	;20/*  エジェクタ２進角表示		*/
		{6,  22, 18},			//21	DW	6*40*16+22,18	;21/*  エジェクタ３進角表示		*/
		{7,  22, 18},			//22	DW	7*40*16+22,18	;22/*  エジェクタ４進角表示		*/
		{8,  22, 18},			//23	DW	8*40*16+22,18	;23/*  エジェクタ５進角表示		*/
		{9,  22, 18},			//24	DW	9*40*16+22,18	;24/*  エジェクタ６進角表示		*/
		{4,  00, 40},			//25	DW	4*40*16,20		;25/*  エジェクタ１カーソル表示		*/
		{5,  00, 40},			//26	DW	5*40*16,20		;26/*  エジェクタ２カーソル表示		*/
		{6,  00, 40},			//27	DW	6*40*16,20		;27/*  エジェクタ３カーソル表示		*/
		{7,  00, 40},			//28	DW	7*40*16,20		;28/*  エジェクタ４カーソル表示		*/
		{8,  00, 40},			//29	DW	8*40*16,20		;29/*  エジェクタ５カーソル表示		*/
		{9,  00, 40},			//30	DW	9*40*16,20		;30/*  エジェクタ６カーソル表示		*/
		{4,  00, 40},			//31	DW	4*40*16,40		;31/*  ミスフィード１カーソル表示	*/
		{6,  00, 40},			//32	DW	5*40*16,40		;32/*  ミスフィード２カーソル表示	*/
		{8,  00, 40},			//33	DW	6*40*16,40		;33/*  ミスフィード３カーソル表示	*/
		{10, 00, 40},			//34	DW	7*40*16,40		;34/*  ミスフィード４カーソル表示	*/
		{4,  20, 20},			//35	DW	4*40*16+20,20	;35/*  ロータリカム１進角表示		*/
		{5,  20, 20},			//36	DW	5*40*16+20,20	;36/*  ロータリカム２進角表示		*/
		{6,  20, 20},			//37	DW	6*40*16+20,20	;37/*  ロータリカム３進角表示		*/
		{7,  20, 20},			//38	DW	7*40*16+20,20	;38/*  ロータリカム４進角表示		*/
		{8,  20, 20},			//39	DW	8*40*16+20,20	;39/*  ロータリカム５進角表示		*/
		{9,  20, 20},			//40	DW	9*40*16+20,20	;40/*  ロータリカム６進角表示		*/
		{10, 20, 20},			//41	DW	10*40*16+20,20	;41/*  ロータリカム７進角表示		*/
		{11, 20, 20},			//42	DW	11*40*16+20,20	;42/*  ロータリカム８進角表示		*/
		{4,  00, 40},			//43	DW	4*40*16,20		;43/*  ロータリカム１カーソル表示	*/
		{5,  00, 40},			//44	DW	5*40*16,20		;44/*  ロータリカム２カーソル表示	*/
		{6,  00, 40},			//45	DW	6*40*16,20		;45/*  ロータリカム３カーソル表示	*/
		{7,  00, 40},			//46	DW	7*40*16,20		;46/*  ロータリカム４カーソル表示	*/
		{8,  00, 40},			//47	DW	8*40*16,20		;47/*  ロータリカム５カーソル表示	*/
		{9,  00, 40},			//48	DW	9*40*16,20		;48/*  ロータリカム６カーソル表示	*/
		{10, 00, 40},			//49	DW	10*40*16,20		;49/*  ロータリカム７カーソル表示	*/
		{11, 00, 40},			//50	DW	11*40*16,20		;50/*  ロータリカム８カーソル表示	*/
		{3,  00, 20},			//51	DW	3*40*16,20		;51/*  上型クランパ選択表示		*/
		{5,  00, 20},			//52	DW	5*40*16,20		;52/*  下型クランパ選択表示		*/
		{7,  00, 20},			//53	DW	7*40*16,20		;53/*  ダイリフタ選択表示		*/
		{9,  00, 20},			//54	DW	9*40*16,20		;54/*  ダイクッション選択表示		*/
		{3,  20, 20},			//55	DW	3*40*16+20,20	;55/*  ダイクッション自動調節表示	*/
		{4,  20, 20},			//56	DW	4*40*16+20,20	;56/*  ダイクッション自動調節表示	*/
		{5,  20, 20},			//57	DW	5*40*16+20,20	;57/*  ダイクッション自動調節表示	*/
		{7,  20, 20},			//58	DW	7*40*16+20,20	;58/*  ダイクッション自動調節表示	*/
		{8,  20, 20},			//59	DW	8*40*16+20,20	;59/*  ダイクッション自動調節表示	*/
		{9,  20, 20},			//60	DW	9*40*16+20,20	;60/*  ダイクッション自動調節表示	*/
		{2,  20, 20},			//61	DW	2*40*16+20,20	;61/*  スキャンタイム表示		*/
		{6,  00, 40},			//62	DW	6*40*16,20		;62/*  ウインドウ画面エジェクタ１表示	*/
		{7,  00, 40},			//63	DW	7*40*16,20		;63/*  ウインドウ画面エジェクタ２表示	*/
		{8,  00, 40},			//64	DW	8*40*16,20		;64/*  ウインドウ画面エジェクタ３表示	*/
		{9,  00, 40},			//65	DW	9*40*16,20		;65/*  ウインドウ画面エジェクタ４表示	*/
		{10, 00, 40},			//66	DW	10*40*16,20		;66/*  ウインドウ画面エジェクタ５表示	*/
		{11, 00, 40},			//67	DW	11*40*16,20		;67/*  ウインドウ画面エジェクタ６表示	*/
		{6,  00, 40},			//68	DW	7*40*16+20,20	;68/*  ウインドウ画面ミスフィード１表示	*/
		{7,  00, 40},			//69	DW	8*40*16+20,20	;69/*  ウインドウ画面ミスフィード２表示	*/
		{8,  00, 40},			//70	DW	9*40*16+20,20	;70/*  ウインドウ画面ミスフィード３表示	*/
		{9,  00, 40},			//71	DW	10*40*16+20,20	;71/*  ウインドウ画面ミスフィード４表示	*/
		{3,  22, 18},			//72	DW	3*40*16+22,18	;72/*  上型クランパ表示			*/
		{4,  22, 18},			//73	DW	4*40*16+22,18	;73/*  下型クランパ表示			*/
		{5,  22, 18},			//74	DW	5*40*16+22,18	;74/*  ダイリフタ表示			*/
		{6,  22, 18},			//75	DW	6*40*16+22,18	;75/*  ダイクッション表示		*/
		{7,  22, 18},			//76	DW	7*40*16+22,18	;76/*  防護柵表示			*/
		{8,  22, 18},			//77	DW	8*40*16+22,18	;77/*  スライド調節表示			*/
		{6,  00, 18},			//78	DW	6*40*16,18		;78/*  段取ウインドウスライド表示	*/
		{9,  4,  16},			//79	DW	9*40*16+4,16	;79/*  ストッピングタイム表示		*/
		{10, 4,  16},			//80	DW	10*40*16+4,16	;80/*  ストッピングタイム表示		*/
		{1,  20, 20},			//81	DW	1*40*16+20,20	;81/*  生産＆段取り画面型名称		*/
		{1,  00, 40},			//82	DW	1*40*16,40		;82/*  生産＆段取り画面型名称		*/
		{12, 00, 22},			//83	DW	12*40*16,22		;83/* V03i,40->22 段取り画面メモ	*/
		{7,  00, 23},			//84	DW	7*40*16,23		;84/*  段取り画面スライド自動カーソル	*/
		{9,  00, 23},			//85	DW	9*40*16,23		;85/*  段取り画面スライド自動生産設定	*/
		{10, 00, 23},			//86	DW	10*40*16,23		;86/*  段取り画面スライド自動段取１設定	*/
		{11, 00, 23},			//87	DW	11*40*16,23		;87/*  段取り画面スライド自動段取２設定	*/
		{9,  00, 40},			//88	DW	9*40*16,40		;88/*  メンテナンス画面実測値表示	*/
		{10, 00, 40},			//89	DW	10*40*16,40		;89/*  メンテナンス画面実測値表示	*/
		{11, 00, 40},			//90	DW	11*40*16,40		;90/*  メンテナンス画面実測値表示	*/
		{12, 00, 20},			//91	DW	12*40*16,20		;91/*  ウインドウ画面オーバーロード表示	*/
		{11, 20, 20},			//92	DW	11*40*16+20,20	;92/*  ウインドウ画面項目番号０１表示	*/
		{6,  00, 20},			//93	DW	6*40*16+0,20	;93/*　生産＆段取画面表示設定速度表示	*/
		{3,  00, 40},			//94	DW	3*40*16+0,40	;94/*　生産＆段取画面表示設定速度表示	*/
/* V00m */
//		{3,  24, 6},			//95	DW	3*40*16+24,6	;95/*  システム画面オプション表示	*/
		{2,  32, 3},			//95	DW	3*40*16+24,6	;95/*  システム画面オプション表示	*/
		{5,  00, 40},			//96	DW	5*40*16+0,40	;96/*	名称画面カタカナ表示		*/
		{6,  00, 40},			//97	DW	6*40*16+0,40	;97/*	名称画面カタカナ表示		*/
		{7,  00, 10},			//98	DW	7*40*16+0,10	;98/*	名称画面カタカナ表示		*/
		{8,  00, 40},			//99	DW	8*40*16,40		;99/*  ミスフィード５カーソル表示	*/
		{9,  00, 40},			//100	DW	9*40*16,40		;100/*  ミスフィード６カーソル表示	*/
		{10, 00, 40},			//101	DW	10*40*16,40		;101/*  ミスフィード７カーソル表示	*/
		{11, 00, 40},			//102	DW	11*40*16,40		;102/*  ミスフィード８カーソル表示	*/
		{11, 20, 20},			//103	DW	11*40*16+20,20	;103/*10-11  ウインドウ画面ミスフィード５表示*/
		{12, 20, 20},			//104	DW	12*40*16+20,20	;104/*11-12  ウインドウ画面ミスフィード６表示*/
		{3,  20, 20},			//105	DW	3*40*16+20,20	;105/*  ダイクッション自動表示		*/
		{4,  20, 20},			//106	DW	4*40*16+20,20	;106/*  ダイクッション自動左表示	*/
		{5,  20, 20},			//107	DW	5*40*16+20,20	;107/*  ダイクッション自動右表示	*/
		{7,  20, 20},			//108	DW	7*40*16+20,20	;108/*  ダイクッション調圧表示		*/
		{8,  20, 20},			//109	DW	8*40*16+20,20	;109/*  ダイクッション調圧表示		*/
		{9,  20, 20},			//110	DW	9*40*16+20,20	;110/*  ダイクッション調圧表示		*/
		{4,  00, 40},			//111	DW	4*40*16,40		;111/*  コイルライン設定１		*/
		{5,  00, 40},			//112	DW	5*40*16,40		;112/*  コイルライン設定２		*/
		{6,  00, 40},			//113	DW	6*40*16,40		;113/*  コイルライン設定３		*/
		{7,  00, 40},			//114	DW	7*40*16,40		;114/*  コイルライン設定４		*/
		{8,  00, 40},			//115	DW	8*40*16,40		;115/*  コイルライン設定５		*/
		{9,  00, 40},			//116	DW	9*40*16,40		;116/*  コイルライン設定６		*/
		{11, 00, 40},			//117	DW	11*40*16,40		;117/*  コイルライン設定段取り選択画面	*/
		{3,  22, 18},			//118	DW	3*40*16+22,18	;118;/* 金型自動交換 			*/
		{4,  22, 18},			//119	DW	4*40*16+22,18	;119;/* スライド調節 			*/
		{5,  22, 18},			//120	DW	5*40*16+22,18	;120;/* 上型クランパ 			*/
		{6,  22, 18},			//121	DW	6*40*16+22,18	;121;/* 下型クランパ 			*/
		{7,  22, 18},			//122	DW	7*40*16+22,18	;122;/* ダイリフタ	 		*/
		{8,  22, 18},			//123	DW	8*40*16+22,18	;123;/* ダイクッション 			*/
		{9,  22, 18},			//124	DW	9*40*16+22,18	;124;/* 防護柵				*/
		{10, 22, 18},			//125	DW	10*40*16+22,18	;125;/* ＭＢ				*/
		{11, 22, 18},			//126	DW	11*40*16+22,18	;126;/* バランサ			*/
		{12, 22, 18},			//127	DW	12*40*16+22,18	;127;/* ﾀﾞｲｸｯｼｮﾝ調節			*/
		{8,  00, 23},			//128	DW	8*40*16,23		;128/*  ストローク調節左実測値		*/
		{6,  00, 40},			//129	DW	6*40*16,40		;129/*ＡＤＣ次型消去			*/
		{11, 17, 23},			//130	DW	11*40*16+17,23	;130/*ＡＤＣダイクッション右実測	*/
		{12, 17, 23},			//131	DW	12*40*16+17,23	;131/*ＡＤＣダイクッション右設定	*/
		{6,  20, 20},			//132	DW	6*40*16+20,20	;132/*  ウインドウ画面ミスフィード無効表示	*/
		{8,  00, 23},			//133	DW	8*40*16,23		;133/*  段取り画面スライド自動生産設定	*/
		{6,  20, 20},			//134	DW	6*40*16+20,20	;134/* ダイクッション自動ＳＷ表示 	*/
		{10, 20, 20},			//135	DW	10*40*16+20,20	;135/* ダイクッション調圧ＳＷ表示 	*/
		{2,  20, 20},			//136 ﾓｰｼｮﾝ設定 下往復
		{2,  20, 20},			//137 ﾓｰｼｮﾝ設定 上往復
		{5,  00, 40},			//138 ミスフィード１カーソル表示
		{7,  00, 40},			//139 ミスフィード２カーソル表示
		{9,  00, 40},			//140 ミスフィード３カーソル表示
		{11, 00, 40},			//141 ミスフィード４カーソル表示
		{4,  10, 30},			//142 ロータリカム１汎用出力選択時 表示
		{5,  10, 30},			//143 ロータリカム２汎用出力選択時 表示
		{6,  10, 30},			//144 ロータリカム３汎用出力選択時 表示
		{7,  10, 30},			//145 ロータリカム４汎用出力選択時 表示
		{8,  10, 30},			//146 ロータリカム５汎用出力選択時 表示
		{9,  10, 30},			//147 ロータリカム６汎用出力選択時 表示
		{10, 10, 30},			//148 ロータリカム７汎用出力選択時 表示
		{11, 10, 30},			//149 ロータリカム８汎用出力選択時 表示
		{2,  16, 8},			//150 ﾓｰｼｮﾝ設定 反転
		{6,  10, 6},			//151 サイクル 表示					V01  (INS)
		{8,  3, 12},			//152 生産下限／下限上高 表示		V01  (INS)
		};



/*
********************************************************************************
*  Module Name:		CSR_move
*  Function Name:	カーソル移動
*  Input	:		ｶｰｿﾙ情報	０：ホームポジション
*								１：←左方向
*								２：→右方向
*								３：↓下方向
*								４：↑上方向
*								５：戻り値指定
*					ｶｰｿﾙﾏｽｸ		00：移動OK
*								ff：移動禁止
*
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-24
********************************************************************************
*/
void	CSR_move( UNs c_no, UNs c_msk )
{
	UNs		i, j, next_no;

	next_no = c_no;

	if( CSR_CNT == 00 ||								//カーソルなし
			(next_no != 5 && c_msk == 0xff) ) {			//戻り値指定以外 && カーソル移動禁止
		return;
	}
	else{
		SVdata_disp_ent(SV_TBL_POS_NOW);				//設定途中の物は、元に戻す処理

		DANseq_alloff();								//段取り用シーケンスＯＦＦ		//V05q

		do{
			switch(next_no) {
				default:
					next_no = 0xf0;						//終了
					break;
//100
				case 0x00:		//ホームポジション
					CSR_FLG_CNT = 1;					//初期値セット
					SV_FLG_CNT = 1;						//初期値セット
					SW_FLG_CNT	= 1;					//初期値セット
					if( 00 == CSR_pos_chk() ) {			//カーソル位置存在チェック
						SVSW_tbl_enzan();				//ＳＶＳＷテーブルアドレス演算
						next_no = 0xff;					//終了
					}
					else {								//ｶｰｿﾙなし
						CSR_TBL_POS_NOW = 0;			//現在のｶｰｿﾙ位置情報
						next_no = 3;					//存在しないときは下へ移動
					}
					break;
//200
				case 0x01:		//←左方向
					if(SV_FLG_CNT != 0) {					//上戻り？
						SV_FLG_CNT --;						//左に移動
					}
					if(SV_FLG_CNT == 0) {					//上戻り？
						SV_FLG_CNT = 1;						//設定値初期値セット
						if(CSR_FLG_CNT != 01){				//上に移動可能？
							i = CSR_FLG_CNT;
							while( next_no < 0xf0 ){
								CSR_FLG_CNT --;
								if( 00 != CSR_pos_chk() ) {	//カーソル位置存在チェック
									if(CSR_FLG_CNT == 1){	//まだ左方向にカーソルがある？
										CSR_FLG_CNT = i;
										next_no = 0xf0;		//無い場合は終わり
									}
								}
								else{
									SVSW_tbl_enzan();		//ＳＶＳＷテーブルアドレス演算
									next_no = 0xff;			//終了
								}
							}
						}
						else {
							SVSW_tbl_enzan();				//ＳＶＳＷテーブルアドレス演算
							next_no = 0xff;					//終了
						}
					}
					else {
						SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
						next_no = 0xff;						//終了
					}
					break;
//300
				case 0x02:		//→右方向
					i = SV_FLG_CNT;
					SV_FLG_CNT ++;										//右に移動
					if(SV_FLG_CNT <= CSR_buff[CSR_TBL_POS_NOW].SV_MAX){	//下移動？
						SVSW_tbl_enzan();								//ＳＶＳＷテーブルアドレス演算
						next_no = 0xff;									//終了
					}
					else {
						SV_FLG_CNT = 1;									//設定値初期値セット 
						if( CSR_FLG_CNT == CSR_CNT ) {					//下に移動可能？
							SV_FLG_CNT = CSR_buff[CSR_TBL_POS_NOW].SV_MAX;
							next_no = 0xff;								//終了
						}
						else {
							j = CSR_FLG_CNT;
							while( next_no < 0xf0 ){
								CSR_FLG_CNT ++;
								if( 00 != CSR_pos_chk() ) {				//カーソル位置存在チェック
									if(CSR_FLG_CNT >= CSR_CNT){
										SV_FLG_CNT = i;
										CSR_FLG_CNT = j;
										next_no = 0xf0;					//無い場合は終わり
									}
								}
								else{									//ｶｰｿﾙあり
									SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算
									next_no = 0xff;						//終了
								}
							}
						}
					}
					break;
//400
				case 0x03:		//↓下方向
					if( 00 == CSR_pos_shr_dn(CSR_TBL_POS_NOW, next_no)){	//カーソル位置　下検索
						next_no = 0x05;									//戻り値指定へ
					}
					else{
						next_no = 0xf0;									//無い場合は終わり
					}
					break;
//500
				case 0x04:		//↑上方向
					if( 00 == CSR_pos_shr_up(CSR_TBL_POS_NOW, next_no)){	//カーソル位置　上検索
						next_no = 5;									//戻り値指定へ
					}
					else{
						next_no = 0xf0;									//無い場合は終わり
					}
					break;
//600
				case 0x05:		//戻り値指定
					SVSW_tbl_enzan();									//ＳＶＳＷテーブルアドレス演算
					next_no = 0xff;										//終了
					break;
			}
		} while(next_no < 0xf0);

		if(next_no == 0xff ) {
//700
			CSR_disp();								//カーソル表示
			SV_csr_set();							//設定値カーソル
			CSR_sw56_disp();						//ＳＷ５６キャラクタ表示

//2次		SUBERI_out();							//スベリ量カーソル信号出力

			SV_DATA_CHG = 0;						//設定ﾃﾞｰﾀ変更ﾌﾗｸﾞ(0:なし/55:小数点入力/ff:整数入力)
			SV_DISP_BUFF = 0;

			CSR_ON_FLG = 0x00ff;					//カーソル表示フラグＯＮ

			DAN_SW14_no_set();						//段取画面 SW14認識番号転送
			DAN_select_diap();						//段取画面 選択項目セレクト表示

//2014/09/02			Under_grph();							//下段のグラフィックセット
			Gamenn_Graphic_All();					//画面Ｎｏ．ｎのグラフィック全表示

			DAN_dispseq_out();						//段取画面 ｶｰｿﾙ位置ｼｰｹﾝｽ出力

			WIN_grph();								//ウインドウ画面上グラフィック描画
		}
	}
}


/*
********************************************************************************
*  Module Name:		CSR_pos_chk
*  Function Name:	カーソル位置存在チェック
*  Input	:		なし
*  Return	: 		＝00：ｶｰｿﾙあり／≠00：ｶｰｿﾙなし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
UNs		CSR_pos_chk(void)
{
	UNs		i, r_bf;

	i = CSR_FLG_CNT;
	i --;

	r_bf = 0;										//ｶｰｿﾙあり

	if( CSR_buff[i].TOK_NO & BIT_0) {				//特殊番号(B0:ｶｰｿﾙ無し)
		r_bf = 01;									//ｶｰｿﾙなし
	}

	return(r_bf);
}


/*
********************************************************************************
*  Module Name:		CSR_pos_shr_dn
*  Function Name:	カーソル位置　下検索
*  Input	:		カーソル情報ﾃｰﾌﾞﾙの番号
*					ｶｰｿﾙ情報
*  Return	: 		＝00：ｶｰｿﾙあり／≠00：ｶｰｿﾙなし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
UNi		CSR_pos_shr_dn(UNs T_no, UNs c_inf)
{
	UNs		i, xy_no, cnt, r_bf;

	if( CSR_CNT == 00 ) {					//カーソルなし
		return(0);
	}
	xy_no = (CSR_buff[T_no].XY_POS + 1);		//行+1
	xy_no &= 0x03ff;							//行・桁を有効

	for( i=xy_no ; (i & 0x000f) < 14 ; i++ ) {					//挑戦アドレスセット
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x03ff)) {			//一致？
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//特殊番号(B0:ｶｰｿﾙ無し)

					CSR_FLG_CNT = T_no+1;		//カーソル番号決定
					SV_FLG_CNT = 1;				//カーソル番号検索
					SW_FLG_CNT = 1;				//カーソル番号検索
					return(0);					//正常終了
				}
			}
		}
	}

	i = xy_no & 0x000f;
	if(c_inf == 0) {								//ホームポジションの時だけ頭から検索する
		i = 0x0001;									//再検索時は上から見る
	}
	for(  ; i < 14 ; i++ ) {									//挑戦アドレスセット
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x000f)) {			//一致？
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//特殊番号(B0:ｶｰｿﾙ無し)

					CSR_FLG_CNT = T_no+1;		//カーソル番号決定
					SV_FLG_CNT = 1;				//カーソル番号検索
					SW_FLG_CNT = 1;				//カーソル番号検索
					return(0);					//正常終了
				}
			}
		}
	}
	return(0xff);

}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
UNi		CSR_pos_shr_dn(UNs T_no, UNs c_inf)
{
	UNs		i, x_pos, y_pos, cnt, r_bf, wk1, wk2, T_no_new;
	UNs		wkx1, wkx2;

	if( CSR_CNT <= 1 ) {					//カーソルなし
		return(0xff);
	}

	y_pos = (CSR_buff[T_no].Y_POS);			//現在のカーソル位置
	x_pos = (CSR_buff[T_no].X_POS);			//現在のカーソル位置
	wk1 = 0xffff;
	wkx1 = 0xffff;
	T_no_new = T_no;
	for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
	{
		if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//特殊番号(B0:ｶｰｿﾙ無し)
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
			if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//特殊番号(B0:ｶｰｿﾙ無し)
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
		CSR_FLG_CNT = T_no_new+1;	//カーソル番号決定
		SV_FLG_CNT = 1;				//カーソル番号検索
		SW_FLG_CNT = 1;				//カーソル番号検索
		return(0);					//正常終了
	}
	return(0xff);
}
#endif


/*
********************************************************************************
*  Module Name:		CSR_pos_shr_up
*  Function Name:	カーソル位置　上検索
*  Input	:		カーソル情報ﾃｰﾌﾞﾙの番号
*					ｶｰｿﾙ情報
*  Return	: 		＝00：ｶｰｿﾙあり／≠00：ｶｰｿﾙなし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
#if	( SIT_TYPE_SEL == TYPE_SIT3 )
/*★★★★★★★★★	ＳＩＴ－３用	★★★★★★★★★*/
UNi		CSR_pos_shr_up(UNs T_no, UNs c_inf)
{
	UNs		i, xy_no, cnt, r_bf;

	if( CSR_CNT == 00 ) {					//カーソルなし
		return(0);
	}
	xy_no = (CSR_buff[T_no].XY_POS - 1);		//行-11
	xy_no &= 0x03ff;							//行・桁を有効

	for( i=xy_no ; (i & 0x000f) > 0 ; i-- ) {					//挑戦アドレスセット
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x03ff)) {			//一致？
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//特殊番号(B0:ｶｰｿﾙ無し)

					CSR_FLG_CNT = T_no+1;		//カーソル番号決定
					SV_FLG_CNT = 1;				//カーソル番号検索
					SW_FLG_CNT = 1;				//カーソル番号検索
					return(0);					//正常終了
				}
			}
		}
	}

	i = xy_no & 0x000f;
	for(  ; i > 0 ; i-- ) {									//挑戦アドレスセット
		T_no = 0;
		for(cnt = CSR_CNT ; cnt > 0 ; cnt--, T_no++ ) {
			if(i == (CSR_buff[T_no].XY_POS & 0x000f)) {			//一致？
				if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0)) {	//特殊番号(B0:ｶｰｿﾙ無し)

					CSR_FLG_CNT = T_no+1;		//カーソル番号決定
					SV_FLG_CNT = 1;				//カーソル番号検索
					SW_FLG_CNT = 1;				//カーソル番号検索
					return(0);					//正常終了
				}
			}
		}
	}
	return(0xff);

}
#else
/*★★★★★★★★★	ＳＩＴ－４用	★★★★★★★★★*/
UNi		CSR_pos_shr_up(UNs T_no, UNs c_inf)
{
	UNs		i, x_pos, y_pos, cnt, r_bf, wk1, wk2, T_no_new;
	UNs		wkx1, wkx2;

	if( CSR_CNT <= 1 ) {					//カーソルなし
		return(0xff);
	}

	y_pos = (CSR_buff[T_no].Y_POS);			//現在のカーソル位置
	x_pos = (CSR_buff[T_no].X_POS);			//現在のカーソル位置
	wk1 = 0xffff;
	wkx1 = 0xffff;
	T_no_new = T_no;
	for(cnt=CSR_CNT, T_no=0 ; cnt > 0 ; cnt--, T_no++ )
	{
		if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//特殊番号(B0:ｶｰｿﾙ無し)
		{
			if ( x_pos <= CSR_buff[T_no].X_POS)
			{
				wkx2 = CSR_buff[T_no].X_POS - x_pos;
				if (wkx1 >= wkx2)
				{
					if ( y_pos > CSR_buff[T_no].Y_POS)
					{
						wk2 = y_pos - CSR_buff[T_no].Y_POS;			//現在のカーソル位置
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
			if( 00 == (CSR_buff[T_no].TOK_NO & BIT_0))		//特殊番号(B0:ｶｰｿﾙ無し)
			{
				if ( y_pos > CSR_buff[T_no].Y_POS)
				{
					wk2 = y_pos - CSR_buff[T_no].Y_POS;			//現在のカーソル位置
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
		CSR_FLG_CNT = T_no_new+1;	//カーソル番号決定
		SV_FLG_CNT = 1;				//カーソル番号検索
		SW_FLG_CNT = 1;				//カーソル番号検索
		return(0);					//正常終了
	}
	return(0xff);
}
#endif


/*
********************************************************************************
*  Module Name:		CSR_disp
*  Function Name:	カーソル表示
*  Input	:		
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
void	CSR_disp(void)
{
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	CSR_disp_color();
#else
	UNs		xy_no, t_no;

	t_no = CSR_TBL_POS_NOW;
	xy_no = CSR_buff[t_no].XY_POS;							//ｶｰｿﾙのX,Y軸

	if(xy_no == CSR_POS_LAST) {								//カーソルポジションデータ更新 ?
		return;												//カーソル位置が一緒の場合は終了
	}

	if( CSR_POS_LAST != 0xffff &&							//前回カーソルポジションデータなし
			00 == (CSR_buff[t_no].TOK_NO & BIT_0) &&		//特殊番号(B0:ｶｰｿﾙ無し)
			00 != (CSR_POS_LAST >> 10) ) {					//ｶｰｿﾙ長=０？

		disp_memnot(CSR_POS_LAST, &LCD_WORK2[0][0][0]);		//表示用領域の指定ﾃﾞｰﾀを反転
		Lcd_cr(0x01, CSR_POS_LAST, &LCD_WORK2[0][0][0]);	//ｷｬﾗ単位表示
	}

	if( 00 == (CSR_buff[t_no].TOK_NO & BIT_0) ) {			//特殊番号(B0:ｶｰｿﾙ無し)
		if( 00 != (xy_no >> 10) ) {							//ｶｰｿﾙ長=０？

			disp_memnot(xy_no, &LCD_WORK2[0][0][0]);		//表示用領域の指定ﾃﾞｰﾀを反転
			Lcd_cr(0x01, xy_no, &LCD_WORK2[0][0][0]);		//ｷｬﾗ単位表示
		}
	}
	else {
		xy_no = 0;
	}
	CSR_POS_LAST = xy_no;								//カーソルポジションデータ更新
#endif
}


/*
********************************************************************************
*  Module Name:		CSR_disp_off
*  Function Name:	カーソル表示消去
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
void	CSR_disp_off(void)
{
	UNs		xy_no;
	UNl		adr;
	UNs		*g_p;

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
	if( CSR_TBL_POS_NOW == 0xff ||					//前回カーソル無し？
			CSR_POS_LAST == 0xffff ) {				//前回カーソルポジション
		return;
	}
#else
	if( CSR_TBL_POS_NOW == 0xff ||					//前回カーソル無し？
			CSR_BAK_X_POS == 0xffff ) {				//前回カーソルポジション
		return;
	}
#endif
	if(00 == (CSR_buff[CSR_TBL_POS_NOW].TOK_NO & BIT_0)) {	//カーソル表示無し？

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
		xy_no = CSR_buff[CSR_TBL_POS_NOW].XY_POS;			//ｶｰｿﾙのX,Y軸
		if(00 == disp_memnot(xy_no, &LCD_WORK2[0][0][0])){	//表示用領域の指定ﾃﾞｰﾀを反転
			Lcd_cr(01, xy_no, &LCD_WORK2[0][0][0]);			//ｷｬﾗ単位表示
		}
#else
		adr = CSR_TABLE_ADR + ((CSR_buff[CSR_TBL_POS_NOW].CARA_NO-1) * CHAR_CSR_SIZE);		// ｷｬﾗｸﾀNo.からｷｬﾗｸﾀﾃﾞｰﾀが格納されているｱﾄﾞﾚｽを算出
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
		CSR_POS_LAST = 0xffff;				//前回カーソルポジションデータ読込
		CSR_BAK_X_POS = 0xffff;				/* 前回カーソルポジションデータクリア */
		CSR_TBL_POS_NOW = 0xff;
		SV_TBL_POS_NOW = 0xff;
		SW_TBL_POS_NOW = 0xff;
	}
}


/*
********************************************************************************
*  Module Name:		CSR_disp_cls
*  Function Name:	仕様有無によるカーソル表示削除
*  Input	:		削除番号
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-07-15
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
		disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);		//表示用領域を指定ﾃﾞｰﾀで設定
	}
}


/*
********************************************************************************
*  Module Name:		CSR_sw56_disp
*  Function Name:	ＳＷ５６キャラクタ表示
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-27
********************************************************************************
*/
void	CSR_sw56_disp(void)
{
	UNi		i;
	UNs		xy_no, bit_ptn, cr_no, *bf_p;
	UNs		s_bf[4];
	UNs		x_dot, y_dot, len;
	UNs		j, bit;

	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
	SW56_upcara_disp(cr_no, 5);						//キャラクタをＳＷ領域へ格納

	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW5_DN;		//SW5下段ｷｬﾗｸﾀ
	SW56_dncara_disp(cr_no, 7);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納
	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW6_DN;		//SW6下段ｷｬﾗｸﾀ
	SW56_dncara_disp(cr_no, 8);						//SW56下段ｷｬﾗｸﾀをSW領域へ格納


	/* V01d */
	if (CSR_buff[CSR_TBL_POS_NOW].SW6_SUB == 57)	//SW5/SW6 ﾃﾞｰﾀ処理番号
	{
		if(SV_DANSUU_SRV <= 5)
		{
#if( SIT_TYPE_SEL == TYPE_SIT3 )
			xy_no = 6 << 10;				// ﾊﾞｲﾄ数
			xy_no |= 31 << 4;				// 桁
			xy_no |= 14;					// 行
			disp_memset(xy_no, &LCD_WORK1[0][0][0], 0x00);
#else
			s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
			len = 5;
			x_dot = SW56_Up_Pos_Tbl_color[8][0];				//表示位置(画面の最初の位置)
			y_dot = SW56_Up_Pos_Tbl_color[8][1];				//表示位置(画面の最初の位置)
			disp_moji_s_color(
				len,					/* ｷｬﾗｸ長			*/
				x_dot,					/* 書出しX位置		*/
				y_dot,					/* 書出しY位置		*/
				0,						/* 文字色			*/
				GAMENn_HEAD.scr_col,	/* 背景色			*/
				0x0202, 				/* 文字ｻｲｽﾞ			*/
				&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
				LCD_VBASE				/* 表示ﾒﾓﾘ			*/
				);
#endif
		}
	}

	if( (GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30) &&		// V01j
		CSR_buff[CSR_TBL_POS_NOW].SW56_UP == /*91 V01k*/ 96)
	{
//V01m		if (SEQ_024_SV & BIT_4) {								//荷重あり？
		if (SEQ_050_SV & BIT_9) {								//荷重あり？
			SW56_upcara_disp(101, 5);							//SW56上段ｷｬﾗｸﾀを101(荷重)にする。
		}
	}

//V06p
	if (GAMEN_NO == 15) {
		j = CSR_buff[CSR_TBL_POS_NOW].SW56_UP;		//SW56上段ｷｬﾗｸﾀ
		if ( (0xa0 <= j) && (j <= 0xa9) ) {
			j &= 0x000f;
			bit = BIT_0;
		}
		else if ( (0xab <= j) && (j <= 0xb4) ) {
			j -= 0xab;
			j &= 0x000f;
			bit = BIT_0;
		}
		else {
			bit = 0;
		}
		if (bit) {
			bit<<=j;
			if (PV0_KATRD_BIT & bit) {					//回転方式不一致
				SW56_dncara_disp(0xff, 7);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納
				SW56_dncara_disp(0xff, 8);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納
			}
		}
	}

//V06p
	if( GAMEN_NO==3 || GAMEN_NO==6 || GAMEN_NO==28 || GAMEN_NO==30 ) {
		j = CSR_buff[CSR_TBL_POS_NOW].DATA_NO;
		if ( (97<=j) && (j<=102) ) {							//工程行？
			if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 99) {		//SW56upｷｬﾗ＝速度＝ｶｰｿﾙは速度
				if (j==102) {									//戻り速度？
					bit = BIT_15;
				}
				else {
					j -= 97;
					bit = BIT_0;
					if (GAMEN_NO==6 || GAMEN_NO==30) {
						j += 5;
					}
					bit <<= j;
				}

//2015/07/10				if ( (PV0_CKSPD_OVBIT & bit) == 0 ) {			//速度超過？
				if ( ( (PV0_CKSPD_OVBIT & bit) == 0 ) &&			//速度超過？
					 ( (PV0_CKSPD_LMBIT & bit) == 0 ) ) {			//速度下限？
					s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
					len = 5;
					x_dot = SW56_Up_Pos_Tbl_color[8][0];				//表示位置(画面の最初の位置)
					y_dot = SW56_Up_Pos_Tbl_color[8][1];				//表示位置(画面の最初の位置)
					disp_moji_s_color(
						len,					/* ｷｬﾗｸ長			*/
						x_dot,					/* 書出しX位置		*/
						y_dot,					/* 書出しY位置		*/
						0,						/* 文字色			*/
						GAMENn_HEAD.scr_col,	/* 背景色			*/
						0x0202, 				/* 文字ｻｲｽﾞ			*/
						&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
						LCD_VBASE				/* 表示ﾒﾓﾘ			*/
						);
				}
			}
			if (CSR_buff[CSR_TBL_POS_NOW].SW56_UP == 97) {		//SW56upｷｬﾗ＝角度＝ｶｰｿﾙは角度		2014/04/15
				j -= 97;
				bit = BIT_0;
				if (GAMEN_NO==6 || GAMEN_NO==30) {
					j += 5;
				}
				bit <<= j;

				if ( (PVP_CKAGL_OVBIT & bit) == 0 ) {			//角度リミット？
					s_bf[0] = s_bf[1] = s_bf[2] = s_bf[3] = 0x2020;
					len = 5;
					x_dot = SW56_Up_Pos_Tbl_color[8][0];				//表示位置(画面の最初の位置)
					y_dot = SW56_Up_Pos_Tbl_color[8][1];				//表示位置(画面の最初の位置)
					disp_moji_s_color(
						len,					/* ｷｬﾗｸ長			*/
						x_dot,					/* 書出しX位置		*/
						y_dot,					/* 書出しY位置		*/
						0,						/* 文字色			*/
						GAMENn_HEAD.scr_col,	/* 背景色			*/
						0x0202, 				/* 文字ｻｲｽﾞ			*/
						&s_bf[0],				/* ｷｬｸﾀ格納ｱﾄﾞﾚｽ	*/
						LCD_VBASE				/* 表示ﾒﾓﾘ			*/
						);
				}
			}
		}
	}


//エジェクタＳＷ６表示クリア処理
	cr_no = CSR_buff[CSR_TBL_POS_NOW].SW6_SUB;		//SW6ﾃﾞｰﾀ処理番号
	if(cr_no == 20 ){
		i = 0;										//エジェクタ１
	}
	else if(cr_no == 39) {
		i = 1;										//エジェクタ２
	}
	else if(cr_no == 40) {
		i = 2;										//エジェクタ３
	}
	else if(cr_no == 41) {
		i = 3;										//エジェクタ４
	}
	else if(cr_no == 42) {
		i = 4;										//エジェクタ５
	}
	else if(cr_no == 43) {
		i = 5;										//エジェクタ６
	}
	else {
		return;
	}

	bf_p = Eje_sw6_Tbl[i].ADDR;
	bit_ptn = Eje_sw6_Tbl[i].BIT_P;
	if(00 == (*bf_p & bit_ptn)) {					//タイマ仕様有り？
		SW56_dncara_disp(0xff, 0x08);				//SW56下段ｷｬﾗｸﾀをSW領域へ格納
	}

}


/*
********************************************************************************
*  Module Name:		SUBERI_out
*  Function Name:	スベリ量カーソル信号出力
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-05-28
********************************************************************************
*/
void	SUBERI_out(void)
{
	UNs		*bf_p, i;

	if(GAMEN_NO==39 || GAMEN_NO==40){
		i = CSR_buff[CSR_TBL_POS_NOW].YOBI3;		//カーソル現在位置アドレス
//??		bf_p = CBA_RAM_TOP+0A4H						//スベリ量カーソル位置転送
		*bf_p = i;
	}
	else{
//??		bf_p = CBA_RAM_TOP+0A4H						//スベリ量カーソル位置転送
		*bf_p = 0x0000;
	}
}


/*
********************************************************************************
*  Module Name:		SEI_test_out_sw5
*  Function Name:	生産設定ﾃｽﾄ出力処理(SW5)
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-19
********************************************************************************
*/
void	SEI_test_out_sw5(void)
{

	csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW5_SUB);	//SW5/SW6 ﾃﾞｰﾀ処理番号

}


/*
********************************************************************************
*  Module Name:		SEI_test_out_sw6
*  Function Name:	生産設定ﾃｽﾄ出力処理(SW6)
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-19
********************************************************************************
*/
void	SEI_test_out_sw6(void)
{

	csr_sw56_sub(CSR_buff[CSR_TBL_POS_NOW].SW6_SUB);	//SW5/SW6 ﾃﾞｰﾀ処理番号

}


/*
********************************************************************************
*  Module Name:		csr_sw56_sub
*  Function Name:	SW5/SW6 ﾃﾞｰﾀ処理番号 処理
*  Input	:		SW5/SW6 ﾃﾞｰﾀ処理番号
*  Return	: 		なし
*  Note		:
*
*  履 歴	:FIT)田端		ON:2002-06-19
********************************************************************************
*/
void	csr_sw56_sub(UNs sub_no)
{
	UNs		wk_w;
	UNs		i;				/* V00m */
	UNs		xy_no, *g_p;
	UNs		t_no;

	if(sub_no >= 0x80){
		return;
	}

	switch(sub_no) {
		default:
//V01l		case 7:				//ｵｰﾊﾞｰﾛｰﾄﾞ
		case 31:			//カム名称選択（未使用）
		case 32:			//カム名称登録（未使用）
		case 51:			//ﾊﾞｯｸｱｯﾌﾟ画面現位置変更
			break;

		case 1:				//ｴｼﾞｪｸﾀ1出力
			SEQ_PAR_035 |= BIT_0;
			break;
		case 2:				//ｴｼﾞｪｸﾀ2出力
			SEQ_PAR_035 |= BIT_1;
			break;
		case 3:				//ｴｼﾞｪｸﾀ3出力
			SEQ_PAR_035 |= BIT_2;
			break;
		case 4:				//ｴｼﾞｪｸﾀ4出力
			SEQ_PAR_035 |= BIT_3;
			break;
		case 5:				//ｴｼﾞｪｸﾀ5出力
			SEQ_PAR_035 |= BIT_4;
			break;
		case 6:				//ｴｼﾞｪｸﾀ6出力
			SEQ_PAR_035 |= BIT_5;
			break;

		case 7:				//ｵｰﾊﾞｰﾛｰﾄﾞ				// V01l
			SEQ_PAR_035 |= BIT_7;
			break;

		case 8:				//ﾄｰﾀﾙｶｳﾝﾀ1ｸﾘｱ
			PV_TOTLC1_B3 = 0;
			KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			break;
		case 9:				//ﾄｰﾀﾙｶｳﾝﾀ2ｸﾘｱ
			PV_TOTLC2_B31 = 0;
			KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			break;

		case 10:			//ﾛｯﾄｶｳﾝﾀ1ｸﾘｱ
			PV_LOTCT1_B4 = 0;
			KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			SEQ_PAR_033 &= ~BIT_0;
			break;
		case 11:			//ﾛｯﾄｶｳﾝﾀ2ｸﾘｱ
			PV_LOTCT2_B41 = 0;
			KAT_DATCHG_FLG = 0xff;					//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			SEQ_PAR_033 &= ~BIT_1;
			break;

		case 12:			//上型ｸﾗﾝﾊﾟ閉
			SEQ_PAR_041 |= BIT_0;					//段取　上型クランパ閉
			break;
		case 13:			//上型ｸﾗﾝﾊﾟ開
			SEQ_PAR_041 |= BIT_1;					//段取　上型クランパ開
			break;
		case 14:			//下型ｸﾗﾝﾊﾟ閉
			SEQ_PAR_041 |= BIT_8;					//段取　下型クランパ閉
			break;
		case 15:			//下型ｸﾗﾝﾊﾟ開
			SEQ_PAR_041 |= BIT_9;					//段取　下型クランパ開
			break;

		case 16:			//ﾀﾞｲﾘﾌﾀ下降
			SEQ_PAR_042 |= BIT_0;					//段取　ﾀﾞｲﾘﾌﾀ下降
			break;
		case 17:			//ﾀﾞｲﾘﾌﾀ上昇
			SEQ_PAR_042 |= BIT_1;					//段取　ﾀﾞｲﾘﾌﾀ上昇
			break;

		case 18:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				PV_LIFE_COUNT[0] = 0;
				PV_LIFE_COUNT[1] = 0;
				PV_LIFE_COUNT[2] = 0;
			}
			break;
		case 19:			//稼働時間ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_TIM1 = 0;
				MCN_MENT_TIM1_10 = 0;
			}
			break;

		case 21:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ1 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT1 = 0;
			}
			break;
		case 22:			//ﾒﾝﾃﾅﾝｽﾀｲﾏ1 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_TIM2 = 0;
				MCN_MENT_TIM2_10 = 0;
			}
			break;
		case 23:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ2 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT2 = 0;
			}
			break;
		case 24:			//ﾒﾝﾃﾅﾝｽﾀｲﾏ2 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_TIM3 = 0;
				MCN_MENT_TIM3_10 = 0;
			}
			break;
		case 25:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ3 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT3 = 0;
			}
			break;
		case 26:			//ﾒﾝﾃﾅﾝｽﾀｲﾏ3 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT6 = 0;
			}
			break;
		case 27:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ4 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT4 = 0;
			}
			break;
		case 28:			//ﾒﾝﾃﾅﾝｽﾀｲﾏ4 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT7 = 0;
			}
			break;
		case 29:			//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ5 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT5 = 0;
			}
			break;
		case 30:			//ﾒﾝﾃﾅﾝｽﾀｲﾏ5 ｸﾘｱ
			if(SEQ_PAR_101 & BIT_2){				//ﾒﾝﾃﾅﾝｽｶｳﾝﾀ等ﾘｾｯﾄOK？(1:OK)
				MCN_MENT_CNT8 = 0;
			}
			break;

		case 33:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ下降
			SEQ_PAR_042 |= BIT_8;
			break;

		case 34:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ上昇
			SEQ_PAR_042 |= BIT_9;
			break;

		case 35:	/*V01j*/		//防護柵下降
			SEQ_PAR_043 |= BIT_0;
			break;

		case 36:	/*V01j*/		//防護柵上昇
			SEQ_PAR_043 |= BIT_1;
			break;

		case 37:			//ｽﾗｲﾄﾞ下降
			SEQ_PAR_044 |= BIT_0;
			break;

		case 38:			//ｽﾗｲﾄﾞ上昇
			SEQ_PAR_044 |= BIT_1;
			break;

		case 20:			//ｴｼﾞｪｸﾀ1 ｶﾑ/ﾀｲﾏ
			if(SEQ_017_SV & BIT_5){					//ｴｼﾞｪｸﾀ1 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_8){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_8;
				}
				else{
					SEQ_034_SV |= BIT_8;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;
		case 39:			//ｴｼﾞｪｸﾀ2 ｶﾑ/ﾀｲﾏ
			if(SEQ_017_SV & BIT_8){					//ｴｼﾞｪｸﾀ2 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_9){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_9;
				}
				else{
					SEQ_034_SV |= BIT_9;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;
		case 40:			//ｴｼﾞｪｸﾀ3 ｶﾑ/ﾀｲﾏ
			if(SEQ_017_SV & BIT_B){				//ｴｼﾞｪｸﾀ3 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_A){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_A;
				}
				else{
					SEQ_034_SV |= BIT_A;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;
		case 41:			//ｴｼﾞｪｸﾀ4 ｶﾑ/ﾀｲﾏ
			if(SEQ_017_SV & BIT_E){					//ｴｼﾞｪｸﾀ4 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_B){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_B;
				}
				else{
					SEQ_034_SV |= BIT_B;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;
		case 42:			//ｴｼﾞｪｸﾀ5 ｶﾑ/ﾀｲﾏ
			if(SEQ_018_SV & BIT_1){					//ｴｼﾞｪｸﾀ5 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_C){			//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_C;
				}
				else{
					SEQ_034_SV |= BIT_C;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;
		case 43:			//ｴｼﾞｪｸﾀ6 ｶﾑ/ﾀｲﾏ
			if(SEQ_018_SV & BIT_4){					//ｴｼﾞｪｸﾀ6 ﾀｲﾏ無し
				if(SEQ_034_SV & BIT_D){			//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
					SEQ_034_SV &= ~BIT_D;
				}
				else{
					SEQ_034_SV |= BIT_D;
				}
				SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?				SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
													//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
				Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

				FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

				SVdata_disp();						//設定値情報　表示
				Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
				SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

				SV_csr_set();						//設定値カーソル

				wk_w = SW_CNT;
				while(wk_w--){
					SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
				}
			}
			break;

		case 44:			//ﾐｽﾌｨｰﾄﾞ1 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_8){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_8;
			}
			else{
				SEQ_036_SV |= BIT_8;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?			SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
												//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
//			Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

//			SVdata_disp();						//設定値情報　表示
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
//			SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;
		case 45:			//ﾐｽﾌｨｰﾄﾞ2 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_9){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_9;
			}
			else{
				SEQ_036_SV |= BIT_9;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?			SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
												//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
//			Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

//			SVdata_disp();						//設定値情報　表示
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
//			SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;
		case 46:			//ﾐｽﾌｨｰﾄﾞ3 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_A){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_A;
			}
			else{
				SEQ_036_SV |= BIT_A;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?			SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
												//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
//			Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

//			SVdata_disp();						//設定値情報　表示
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
//			SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;
		case 47:			//ﾐｽﾌｨｰﾄﾞ4 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_B){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_B;
			}
			else{
				SEQ_036_SV |= BIT_B;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
//?			SVSW_CHG_FLG &= ~BIT_6;				//ｴｼﾞｪｸﾀ ｶﾑ/ﾀｲﾏ ﾃﾞｰﾀ変更？
												//ｴｼﾞｪｸﾀの表示画面の時は設定値を再表示
//			Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

//			SVdata_disp();						//設定値情報　表示
//			Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
//			SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;

		case 48:			//ｵﾌｾｯﾄ調整ｽﾀｰﾄ
			if ( (GAMEN_NO != 108) || ((GAMEN_NO == 108) && (SV0_OFSET_ENB == 1)) ) {	//機器交換画面では制限をかける		2016/02/25
				OFF_set_start();					//ｵﾌｾｯﾄ調整ｽﾀｰﾄ
			}
//V05j			KJ_CHK_CNT1++;						//V05i
			break;
		case 49:			//ｹﾞｲﾝ調整ｽﾀｰﾄ
			if ( (GAMEN_NO != 108) || ((GAMEN_NO == 108) && (SV0_KOUSEI_ENB == 1)) ) {	//機器交換画面では制限をかける		2016/02/25
				KOUSEI_start();						//校正ｽﾀｰﾄ
			}
//V05j			KJ_CHK_CNT2++;						//V05i
			break;

		case 50:			//ｽﾗｲﾄﾞ自動調節ｽﾀｰﾄ
			SEQ_PAR_044 |= BIT_6;
			break;

		case 56:	/* V00m */		//下限位置教示
//V01m			if (SEQ_024_SV & BIT_4)						//荷重補正あり？	V01k
			if (SEQ_050_SV & BIT_9)						//荷重補正あり？
			{
//V02a				if( (SEQ_020_SV & BIT_8) && (SEQ_PAR_385 & BIT_7) )		//荷重計有＆荷重計表示指令有	/* V01m */
				if( (SEQ_020_SV & BIT_8) && (SEQ_PAR_385 & BIT_7) &&
					(CMD_KJTECH_DSP1 != 0) )				//荷重計有＆荷重計表示指令有	/* V01m */
				{
					i = SV_TBL_POS_NOW;
					KAJYUU_Teaching();						//
					mmon_sv_chg(i);							//角度&位置の設定値変更
					mmon_tchk_disp(0x00);					//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();						//回転方式によるﾃﾞｰﾀの格納
				}
			}
			else
			{
				if (CMD_DAIPOS_DSP1) {		// 0=非表示 1=表示  表示しているときだけ教示有効  /* V01c */
					i = SV_TBL_POS_NOW;
					DYHITO_POS_Teaching();					//
					mmon_sv_chg(i);							//角度&位置の設定値変更
					mmon_tchk_disp(0x00);					//ﾓｰｼｮﾝ画面用情報ﾃｰﾌﾞﾙのﾁｪｯｸ&表示
					mmon_trans_put();						//回転方式によるﾃﾞｰﾀの格納
				}
			}
		break;

		case 52:	/* V01d */		//ﾐｽﾌｨｰﾄﾞ5 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_C){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_C;
			}
			else{
				SEQ_036_SV |= BIT_C;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;

		case 53:	/* V01d */		//ﾐｽﾌｨｰﾄﾞ6 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_D){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_D;
			}
			else{
				SEQ_036_SV |= BIT_D;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;

		case 54:	/* V01d */		//ﾐｽﾌｨｰﾄﾞ7 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_E){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_E;
			}
			else{
				SEQ_036_SV |= BIT_E;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;

		case 55:	/* V01d */		//ﾐｽﾌｨｰﾄﾞ8 即／連
			KAT_DATCHG_FLG = 0xff;				//ｶｳﾝﾀ値変更ﾌﾗｸﾞ
			if(SEQ_036_SV & BIT_F){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
				SEQ_036_SV &= ~BIT_F;
			}
			else{
				SEQ_036_SV |= BIT_F;
			}
			SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			wk_w = SW_CNT;
			while(wk_w--){
				SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
			}
			break;

		case 57:	/* V01d */		//モーション画面次項
			if (SV_DANSUU_SRV > 5) {
				if (disp_stg_sel == E_sstg_mmon) {
					disp_stg_sel = E_sstg_mmon2;		//生産[モーションモニタ6～10]へ
					GAMEN_NO = 6;
					GAMEN_disp();						//画面表示
					CSR_move(03,00);					//ｶｰｿﾙ下移動	/*V01e*/
					Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)	/*V01e*/
					Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)	/*V01e*/
					Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示(LCD2)	/*V01e*/
					Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示(LCD2)	/*V01e*/
				}
				if (disp_stg_sel == E_dstg_mset) {
					disp_stg_sel = E_dstg_mset2;		//データ設定[モーションモニタ6～10]へ
					GAMEN_NO = 30;
					GAMEN_disp();						//画面表示
					CSR_move(03,00);					//ｶｰｿﾙ下移動	/*V01e*/
					Lcd_line(00, 13, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)	/*V01e*/
					Lcd_line(00, 14, E_line_bf, &LCD_WORK1[0][0][0]);	//行表示(LCD1)	/*V01e*/
					Lcd_line(01, 13, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示(LCD2)	/*V01e*/
					Lcd_line(01, 14, E_line_bf, &LCD_WORK2[0][0][0]);	//行表示(LCD2)	/*V01e*/
				}
			}
			break;

		case 58:	/* V01d */		//モーション画面前項
			if (disp_stg_sel == E_sstg_mmon2) {
				disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ6～10]へ
				GAMEN_NO = 3;
				GAMEN_disp();						//画面表示
			}
			if (disp_stg_sel == E_dstg_mset2) {
				disp_stg_sel = E_dstg_mset;			//データ設定[モーションモニタ6～10]へ
				GAMEN_NO = 28;
				GAMEN_disp();						//画面表示
			}
			break;

		case 61:	/*V01j*/		//MB 入
			SEQ_PAR_043 |= BIT_8;
			break;

		case 62:	/*V01j*/		//MB 出
			SEQ_PAR_043 |= BIT_9;
			break;

		case 63:	/*V01j*/		//ﾊﾞﾗﾝｻ調圧ｽﾀｰﾄ
			SEQ_PAR_044 |= BIT_14;
			break;

		case 64:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ調節-ｽﾄﾛｰｸ調節 下降
			SEQ_PAR_045 |= BIT_0;
			break;

		case 65:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ調節-ｽﾄﾛｰｸ調節 下降
			SEQ_PAR_045 |= BIT_1;
			break;

		case 66:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ調節-ｽﾄﾛｰｸ自動調節 ｽﾀｰﾄ
			SEQ_PAR_045 |= BIT_14;
			break;

		case 67:	/*V01j*/		//ﾀﾞｲｸｯｼｮﾝ調節-圧力調節 ｽﾀｰﾄ
			SEQ_PAR_046 |= BIT_6;
			break;

		case 68:	/*V01m*/		//下限／荷重切換
			if (SEQ_024_SV & BIT_4)				//荷重補正あり？
			{
				SEQ_050_SV ^= BIT_9;
			}
			else
			{
				SEQ_050_SV &= ~BIT_9;
			}
			SVSW_CHG_FLG |= 0x0008;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ
			CAR_mkssi_set();
			GAMEN_disp();

			break;

		case 71:	/* V06g */		//タッチ位置転送
			INS_MOTION();
			break;

		case 72:	//オーバーロード表示切替		2014/03/17
			SV_OVLD_SEL++;
			if (SV_OVLD_SEL > 2) {
				SV_OVLD_SEL = 0;
			}

			t_no = grpno_sv_srch(128);								//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ

			if (SV_OVLD_SEL == 1) {								//ｵｰﾊﾞｰﾛｰﾄﾞ最小値
				wk_w = BIT_1;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A27;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A27;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A27;
			}
			else if (SV_OVLD_SEL == 2) {							//ｵｰﾊﾞｰﾛｰﾄﾞ振幅
				wk_w = BIT_2;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A28;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A28;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A28;
			}
			else {													//ｵｰﾊﾞｰﾛｰﾄﾞ最大値
				wk_w = BIT_0;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_OVERE1_A26;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_OVERE2_A26;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_OVERE3_A26;
			}
			if ((SEQ_020_SV & BIT_8)== 0) {
				wk_w = 0;
			}
			SW_cls_disp(128, wk_w, BIT_0);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最大値
			SW_cls_disp(129, wk_w, BIT_1);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最小値
			SW_cls_disp(130, wk_w, BIT_2);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ振幅

			SWchg_disp_pv();										//ＳＷＣＨＧデータ表示実測処理
			SVdata_disp();											//全設定値表示
			SV_csr_set();											//設定値ｶｰｿﾙ表示
			break;

		case 73:	//ロアーリミット表示切替		2014/03/17
			SV_LWLM_SEL++;
			if (SV_LWLM_SEL > 2) {
				SV_LWLM_SEL = 0;
			}

			t_no = grpno_sv_srch(131);								//ｸﾞﾙｰﾌﾟ番号 設定値情報ﾃｰﾌﾞﾙのｻｰﾁ

			if (SV_LWLM_SEL == 1) {									//ﾛｱｰﾘﾐｯﾄ最小値
				wk_w = BIT_1;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A27;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A27;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A27;
			}
			else if (SV_LWLM_SEL == 2) {							//ﾛｱｰﾘﾐｯﾄ振幅
				wk_w = BIT_2;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A28;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A28;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A28;
			}
			else {													//ﾛｱｰﾘﾐｯﾄ最大値
				wk_w = BIT_0;
				SV_buff[t_no+0].DATA_ADR = (UNs *)&SV_ROALM1_A26;
				SV_buff[t_no+1].DATA_ADR = (UNs *)&SV_ROALM2_A26;
				SV_buff[t_no+2].DATA_ADR = (UNs *)&SV_ROALM3_A26;
			}
			if ((SEQ_020_SV & BIT_8)== 0) {
				wk_w = 0;
			}
			SW_cls_disp(131, wk_w, BIT_0);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最大値
			SW_cls_disp(132, wk_w, BIT_1);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最小値
			SW_cls_disp(133, wk_w, BIT_2);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ振幅

			SVdata_disp();											//全設定値表示
			SV_csr_set();											//設定値ｶｰｿﾙ表示
			break;

		case 74:	//トレンド画面  記録荷重切替		2014/03/17
			SV_KAJAREA_SEL++;
			if (SV_KAJAREA_SEL > 2) {
				SV_KAJAREA_SEL = 0;
			}
			if (SV_KAJAREA_SEL == 1) {								//ﾛｱｰﾘﾐｯﾄ最小値
				wk_w = BIT_1;
			}
			else if (SV_KAJAREA_SEL == 2) {							//ﾛｱｰﾘﾐｯﾄ振幅
				wk_w = BIT_2;
			}
			else {													//ﾛｱｰﾘﾐｯﾄ最大値
				wk_w = BIT_0;
			}
			SW_cls_disp(134, wk_w, BIT_0);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最大値
			SW_cls_disp(135, wk_w, BIT_1);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ最小値
			SW_cls_disp(136, wk_w, BIT_2);								//荷重計ｵｰﾊﾞﾛｰﾄﾞ振幅

			FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

			SVSW_CHG_FLG |= BIT_3;
			break;

		case 75:	//ロータリカム０１  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_0, 0*8+4, 0*8+5);
			break;

		case 76:	//ロータリカム０１  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_0, 0*8+6, 0*8+7);
			break;

		case 77:	//ロータリカム０２  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_1, 1*8+4, 1*8+5);
			break;

		case 78:	//ロータリカム０２  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_1, 1*8+6, 1*8+7);
			break;

		case 79:	//ロータリカム０３  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_2, 2*8+4, 2*8+5);
			break;

		case 80:	//ロータリカム０３  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_2, 2*8+6, 2*8+7);
			break;

		case 81:	//ロータリカム０４  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_3, 3*8+4, 3*8+5);
			break;

		case 82:	//ロータリカム０４  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_3, 3*8+6, 3*8+7);
			break;

		case 83:	//ロータリカム０５  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_4, 4*8+4, 4*8+5);
			break;

		case 84:	//ロータリカム０５  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_4, 4*8+6, 4*8+7);
			break;

		case 85:	//ロータリカム０６  ＯＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_5, 5*8+4, 5*8+5);
			break;

		case 86:	//ロータリカム０６  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_5, 5*8+6, 5*8+7);
			break;

		case 87:	//ロータリカム０７  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_6, 6*8+4, 6*8+5);
			break;

		case 88:	//ロータリカム０７  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_6, 6*8+6, 6*8+7);
			break;

		case 89:	//ロータリカム０８  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_7, 7*8+4, 7*8+5);
			break;

		case 90:	//ロータリカム０８  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_7, 7*8+6, 7*8+7);
			break;

		case 91:	//ロータリカム０９  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_8, 0*8+4, 0*8+5);
			break;

		case 92:	//ロータリカム０９  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_8, 0*8+6, 0*8+7);
			break;

		case 93:	//ロータリカム１０  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_9, 1*8+4, 1*8+5);
			break;

		case 94:	//ロータリカム１０  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_9, 1*8+6, 1*8+7);
			break;

		case 95:	//ロータリカム１１  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_10, 2*8+4, 2*8+5);
			break;

		case 96:	//ロータリカム１１  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_10, 2*8+6, 2*8+7);
			break;

		case 97:	//ロータリカム１２  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_11, 3*8+4, 3*8+5);
			break;

		case 98:	//ロータリカム１２  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_11, 3*8+6, 3*8+7);
			break;

		case 99:	//ロータリカム１３  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_12, 4*8+4, 4*8+5);
			break;

		case 100:	//ロータリカム１３  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_12, 4*8+6, 4*8+7);
			break;

		case 101:	//ロータリカム１４  ＯＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_13, 5*8+4, 5*8+5);
			break;

		case 102:	//ロータリカム１４  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_13, 5*8+6, 5*8+7);
			break;

		case 103:	//ロータリカム１５  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_14, 6*8+4, 6*8+5);
			break;

		case 104:	//ロータリカム１５  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_14, 6*8+6, 6*8+7);
			break;

		case 105:	//ロータリカム１６  ＯＮ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_055_SV, BIT_15, 7*8+4, 7*8+5);
			break;

		case 106:	//ロータリカム１６  ＯＦＦ進角		2014/09/01
			Sinkaku_Agl_Tim_Chg(&SEQ_059_SV, BIT_15, 7*8+6, 7*8+7);
			break;

		case 107:	//一定速領域転送					2014/09/09
			INS_FIXARA_SPD();
			break;

	}
}


/*
********************************************************************************
*  Module Name:		DYHITO_POS_Teaching
*  Function Name:	現在の下限位置(旧ﾀﾞｲﾊｲﾄ)をティーチング
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2003-01-27 (V00m)
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
	cnv_bf = PV0_SLIDE_POS;								//生産下限0.001mm

	if( SEQ_016_SV & BIT_6 ) {					//単位切替 mm/INCH 単位系(1:INCH)
		cnv_bf = cnv_mm_inch(cnv_bf,0);			//0.001mm -> 0.001INCH
	}

	Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ

	PV0_KAGENHOS_BAK = *Dst_lp;							//今までのデータを前回値として記憶		/* V01w */

	*Dst_lp = cnv_bf;

	FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	flag = 0x01;										//HEX
	z_f = 0x00;											//ゼロサプレス有り

	SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)

	WIN_grph();											//ウインドウ画面上グラフィック描画

	Key_sv_tokusyu_chk(t_no);							//設定値特殊処理

	TENKEY_CNT = 0;
	SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//格納ﾌﾗｸﾞ

	if(WINDOW_NO == 0) {
	}
	else{
		Lcd_line( 00, 6, E_line_bf, &LCD_WORK1[0][0][0] );	//行表示
	}
}


/*
********************************************************************************
*  Module Name:		KAJYUU_Teaching
*  Function Name:	現在の最大荷重をティーチング
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2004-07-05 (V01k)
********************************************************************************
*/
void	KAJYUU_Teaching(void)
{
	UNs		t_no, z_f, *Dst_p, cnt, flag, cnv_bf;
//V01t	UNl		*Dst_lp;
	UNs		*Dst_lp, ww0;
	UNl		wl0, wl1;

	t_no = SV_TBL_POS_NOW;

//V02a	cnv_bf = swap_iw(&CLO_LOAD_T);						//荷重（TON）(1word) 
	cnv_bf = PVP_ARA1_KAJ_T2;							//荷重（TON）(1word) 

//V01t	Dst_lp = (UNl *)SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
//V01t	*Dst_lp = (UNl)cnv_bf;
	Dst_lp = (UNs *)SV_buff[t_no].DATA_ADR;				//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ

//V02a	PV0_KAJYUHOS_BAK = *Dst_lp;							//今までのデータを前回値として記憶		/* V01w */
	ww0 = kajyu_chk( Dst_lp, cnv_bf );
	if (ww0 != 0) {
		SEQ_050_SV |= BIT_10;
	}
	else {
		SEQ_050_SV &= ~BIT_10;							// 変更大きすぎず小さすぎず
	}
	SVSW_CHG_FLG |= 0x0008;				//格納ﾌﾗｸﾞ

	*Dst_lp = cnv_bf;

	FRAM_csum_set();									//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	flag = 0x01;										//HEX
	z_f = 0x00;											//ゼロサプレス有り

	SVPV_data_disp(cnv_bf, &SV_buff[t_no], z_f, flag);	//設定値＆実測値 表示(ｾﾞﾛｻﾌﾟﾚｽ/正常表示)

	WIN_grph();											//ウインドウ画面上グラフィック描画

	Key_sv_tokusyu_chk(t_no);							//設定値特殊処理

	TENKEY_CNT = 0;
	SVSW_CHG_FLG |= SV_buff[t_no].SAVE_NO;				//格納ﾌﾗｸﾞ

}


/*
********************************************************************************
*  Module Name:		INS_MOTION
*  Function Name:	タッチ位置のモーションを挿入する
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2011-07-28 (V06g)
********************************************************************************
*/
//2012-10-17,19の変更
//<10/19は[2-3]になった
//[1]挿入する行のﾀｲﾏは0とする(今までは0.01)
//
//	2012-10-19 変更仕様
//[2-1]挿入する行が１段目の場合、
//	   挿入する行は挿入前の１段目に設定されていた速度となる
//	   挿入された次の行は挿入した行の1/2の速度に変える.

//[2-2]挿入する行の後ろに戻り以外の行程がある場合
//	   挿入する行は挿入前の行に設定されていた速度となる
//	   挿入された次の行は挿入した行の1/2の速度に変える.
//[2-3]挿入する行が戻りの直前（次に段がなくて戻りになる）場合は2行挿入する
//		挿入する1行目は 前段の速度の1/2とし、角度,位置はPVP_MOTINS_AGL,PVP_MOTINS_POS
//		挿入する2行目は 挿入した１行目の速度と同じとし,角度,位置はPVP_MOTINS_AG2,PVP_MOTINS_PS2
//
//[3-1]10段仕様で10段設定または5段仕様で5段設定の場合、挿入しない
//[3-2]10段仕様で9段設定または5段仕様で4段設定の場合に２行挿入する場合は、挿入しない

void INS_MOTION(void)
{
	UNs	i, c ,j;
	UNs	AGL[10];
	UNl	POS[10];
	UNs	SPD[10];
	UNs	TIM[10];

	UNs	AGL2[10];
	UNl	POS2[10];
	UNs	SPD2[10];
	UNs	TIM2[10];

	UNs	*Src_s;
	UNl	*Src_l;

	UNs	*Dst_AGL, *Dst_SPD, *Dst_TIM;
	UNl	*Dst_POS;

	UNs	errflg;//koma
	UNs	inscnt,danmax,setdan;//koma
	UNs	pvdan,pvdanbef,pvdanaft;
	UNs	kattch_spd,aglwk1,aglwk2,spdwk;

	errflg=0;//err
	inscnt=0;//挿入個数
	danmax=0;


	setdan=SV_DANSUU_SRV;
	pvdan=PVP_MOTINS_DAN;//ﾃﾞｰﾀ保証
	pvdanbef=PVP_MOTINS_DANBEF;
	pvdanaft=PVP_MOTINS_DANAFT;
	kattch_spd=SVP_KATTCH_SPD/10;//0.01%->0.1%

	//現状設定をworkへ
	Dst_AGL = &SV_1DANDEG_SRV;
	Dst_POS = &SV_1DANPOS_SRV;
	Dst_SPD = &SV_1DANSPD_SRV;
	Dst_TIM = &SV_1DANTIM_SRV;

	for (i=0; i<10; i++) {
		AGL[i]	=	Dst_AGL[i];
		POS[i]	=	Dst_POS[i];
		SPD[i]	=	Dst_SPD[i];
		TIM[i]	=	Dst_TIM[i];

		AGL2[i]	=	Dst_AGL[i];
		POS2[i]	=	Dst_POS[i];
		SPD2[i]	=	Dst_SPD[i];
		TIM2[i]	=	Dst_TIM[i];
	}

// koma 2012-10-19 5段仕様/10段仕様による段数
	if ( SEQ_024_SV & BIT_3) {danmax=10;}else {danmax=5;}
	if((setdan==0)||(danmax<setdan)){
		errflg=1;//挿入不可能
		setdan=1;//暴走対策
	}

//	CPUAからの挿入情報
	if(PVP_MOTINS_INF != 0){
		errflg=1;//挿入不可能
	}else{
		if(pvdan){//1
//		=== タッチ挿入に同じデータが存在するかチェック =========
			aglwk2=PVP_MOTINS_AGL/10;
			j=setdan;
			if(pvdan<j){
				j=pvdan;//ﾁｪｯｸ回数
			}
			for(i=0;i<j;i++){
				aglwk1=AGL[i]/10;
				if((aglwk1==aglwk2) && (SPD[i]==kattch_spd)){
					pvdan=0;
				}
			}
			if(pvdan){//1
				inscnt++;//2段挿入は決定
			}
		}
//		=== 減速に同じデータが存在するかチェック =========
		if(pvdanbef){
			aglwk2=PVP_MOTINS_AG2/10;
			j=setdan;
			if(pvdanbef<j){
				j=pvdanbef;//ﾁｪｯｸ回数
			}

			if(pvdanbef==1){
				spdwk=Dst_SPD[pvdanbef-1];//変更前の挿入して後ろにいく方の速度
			}else{
				spdwk=Dst_SPD[pvdanbef-2];//挿入した結果,前段の速度あっているか？
			}

			for(i=0;i<j;i++){
				aglwk1=AGL[i]/10;
				if((aglwk1==aglwk2) && (SPD[i]==spdwk)){
					pvdanbef=0;
				}
			}

			if(pvdanbef){
				inscnt++;//2段挿入は決定
			}
		}


//		=== 180度挿入に同じデータが存在するかチェック =========
		if(pvdanaft){
			aglwk2=PVP_MOTINS_AG3/10;
			j=setdan;
			if(pvdanaft<j){
				j=pvdanaft;//ﾁｪｯｸ回数
			}
			for(i=0;i<j;i++){
				aglwk1=AGL[i]/10;
				if((aglwk1==aglwk2) && (SPD[i]==kattch_spd)){
					pvdanaft=0;
				}
			}
			if(pvdanaft){
				inscnt++;//2or3段挿入は決定
			}
		}
	}




	if(inscnt==0){
		errflg=1;//挿入する段数がない
	}

	if( setdan+inscnt <= danmax) {//挿入した結果が10段または5段以下であること
		if(	(pvdan<=danmax)	&&
			(pvdanbef<=danmax)	&&
			(pvdanaft<=danmax)		){//挿入する段数は適正? 1~5 or 1~10
			//ok
		}else{
			errflg=1;//挿入不可能 段数設定が変
		}
	}else{
		errflg=1;//挿入不可能 段数がもはやmax状態
	}

	if ( errflg==0 ) {	//
																		//段数(1～9)=>10に変更koma2012-10-17

//	AGL2,SPD2,TIM2,POS2は元ﾃﾞｰﾀとして残す
//	====== 180度位置の挿入 => 金型タッチ位置 =>減速開始位置順で行う

//	==== 180度挿入 ====
		if(pvdanaft != 0){
			pvdanaft--;
			j=0;
			for (i=0; i<10; i++) {//
				if(i==pvdanaft){
					AGL2[i]	=PVP_MOTINS_AG3;//金型ﾀｯﾁ後角度
					POS2[i]	=PVP_MOTINS_PS3;
					SPD2[i]	=kattch_spd;//100.00%=> 100.0% DATA
					TIM2[i]	=0;
					j=1;//挿入
				}else{
					AGL2[i]	=AGL[i-j];
					POS2[i]	=POS[i-j];
					SPD2[i]	=SPD[i-j];
					TIM2[i]	=TIM[i-j];
				}
			}
			for(i=0;i<10;i++){//
				AGL[i]	=AGL2[i];
				POS[i]	=POS2[i];
				SPD[i]	=SPD2[i];
				TIM[i]	=TIM2[i];
			}
		}

//	==== ﾀｯﾁ位置挿入 ====
		if(pvdan != 0){
			pvdan--;
			j=0;
			for (i=0; i<10; i++) {//
				if(i==pvdan){
					AGL2[i]	=PVP_MOTINS_AGL;//金型ﾀｯﾁ角度
					POS2[i]	=PVP_MOTINS_POS;
					SPD2[i]	=kattch_spd;//100.00%=> 100.0% DATA
					TIM2[i]	=0;
					j=1;
				}else{
					AGL2[i]	=AGL[i-j];
					POS2[i]	=POS[i-j];
					SPD2[i]	=SPD[i-j];
					TIM2[i]	=TIM[i-j];
				}
			}
			for(i=0;i<10;i++){
				AGL[i]	=AGL2[i];
				POS[i]	=POS2[i];
				SPD[i]	=SPD2[i];
				TIM[i]	=TIM2[i];
			}
		}


//	==== 減速位置挿入 ====
		if(pvdanbef != 0){
			pvdanbef--;
			j=0;
			for (i=0; i<10; i++) {//
				if(i==pvdanbef){
					if(pvdanbef==0){
						spdwk=Dst_SPD[pvdanbef];//変更前の速度
					}else{
						spdwk=Dst_SPD[pvdanbef-1];
					}

					AGL2[i]	=PVP_MOTINS_AG2;//減速角度
					POS2[i]	=PVP_MOTINS_PS2;
					if(pvdanbef==0){
						SPD2[i]	=Dst_SPD[pvdanbef];//変更前の速度
					}else{
						SPD2[i]	=Dst_SPD[pvdanbef-1];
					}
					TIM2[i]	=0;
					j=1;
				}else{
					AGL2[i]	=AGL[i-j];
					POS2[i]	=POS[i-j];
					SPD2[i]	=SPD[i-j];
					TIM2[i]	=TIM[i-j];
				}
			}
			for(i=0;i<10;i++){
				AGL[i]	=AGL2[i];
				POS[i]	=POS2[i];
				SPD[i]	=SPD2[i];
				TIM[i]	=TIM2[i];
			}
		}


		//設定ﾃﾞｰﾀへ演算結果を戻す[]
		if(inscnt != 0){
			for (i=0; i<10; i++) {//戻す
				Dst_AGL[i]	=	AGL[i];
				Dst_POS[i]	=	POS[i];
				Dst_SPD[i]	=	SPD[i];
				Dst_TIM[i]	=	TIM[i];
			}
			SV_DANSUU_SRV=SV_DANSUU_SRV+inscnt;			//段数 挿入
			// 挿入
			mmon_trans_put();					//回転方式によるﾃﾞｰﾀの格納
			disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
			GAMEN_NO = 3;
			GAMEN_disp();						//画面表示
		}

		SEQ_PAR_098 &= ~cBIT2;//正常または挿入したものと同じ

	}else{
	//2013-02-20 挿入しなかった
		SEQ_PAR_098 |= cBIT2;

	}

}


/*
********************************************************************************
*  Function Name:	進角 角度／時間切替
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2014-09-01
********************************************************************************
*/
void	Sinkaku_Agl_Tim_Chg(UNs *SEQ, UNs seqbit, UNs t_no1, UNs t_no2)
{
	UNs		wk_w;

	if(*SEQ & seqbit){				//変更ﾋﾞｯﾄﾃﾞｰﾀを今のﾃﾞｰﾀより反転する
		*SEQ &= ~seqbit;
	}
	else{
		*SEQ |= seqbit;
	}
	SVSW_CHG_FLG |= 0x0028;				//ﾃﾞｰﾀﾁｪﾝｼﾞ ﾌﾗｸﾞ ｾｯﾄ

	Disp_data_set();					//情報ﾃｰﾌﾞﾙの非表示処理(作成)

	FRAM_csum_set();					//ﾌﾗｼｭRAM領域の設定値のﾁｪｯｸｻﾑ･ｺｰﾄﾞを作成

	SVdata_disp_one(t_no1);				//設定値情報　表示
	SVdata_disp_one(t_no2);				//設定値情報　表示
	Lcd_all(00, E_gmen_bf, &LCD_WORK1[0][0][0]);	//全表示
	SVSW_tbl_enzan();					//ＳＶＳＷテーブルアドレス演算

	SV_csr_set();

	wk_w = SW_CNT;
	while(wk_w--){
		SWchg_disp_pv();				//ＳＷＣＨＧデータ表示実測処理
	}
}


/*
********************************************************************************
*  Function Name:	一定速領域追加
*  Input	:		なし
*  Return	: 		なし
*  Note		:
*
*  履 歴	:Shima		ON:2014-09-09
********************************************************************************
*/
//	
extern	void API_SV_DEGMAX_CALC(void);//ssa_dtmk.src
extern	U4b	SETD_DEGSPD_MAX		;//
extern	U4b	SETD_DEGMAX_LNGTH	;//MAX*加速時間/1000

extern	U4b AccLengthCalc1(S4b spd1,S4b spd2);
extern	S2b MOTION_INS_DEL(U2b inscnt,U2b insstep,U2b delcnt,U2b delstep,
						U2b *insAGL,U4b *insPOS,U2b *insSPD,U2b *insTIM);

extern	U2b WORD_BIT_TBL0[16];
//UNs		SV0_FIXARA_AGLS;			//一定領域　開始角度
//UNl		SV0_FIXARA_POSS;			//一定領域　開始位置
//UNs		SV0_FIXARA_SPDB;			//一定領域　開始前速度 未使用
//UNs		SV0_FIXARA_SPDF;			//一定領域　一定速度
//UNs		SV0_FIXARA_AGLE;			//一定領域　終了角度
//UNl		SV0_FIXARA_POSE;			//一定領域　終了位置

extern	U2b CAM_KOUTEI_SEARCH2(U2b sel,S2b dig);

void	INS_FIXARA_SPD(void)
{

	U4b	length;
	U2b	stepDef,stepwk,stepFirst;
	S2b	digset,digFirst;
	U2b	spdobjN,spdobjN_1;//
	U2b	*spdsv;
	U2b	err1=0,err2=0;
	S2b	endF=0;

	//
	U2b	insFirstStep;
	U2b	insSecondStep=0;
	U2b	delStep,delCnt;

	//
	U2b SVAGL[2];
	U2b SVSPD[2];
	U2b SVTIM[2];
	U4b SVPOS[2];

	API_SV_DEGMAX_CALC();//ｲﾆｼｬﾙ計算　最大速度,最大速度時~0までの減速距離



	digset=SV0_FIXARA_AGLS;	//指定角度 0.1度単位
	stepDef=CAM_KOUTEI_SEARCH2(0,(digset/10));//挿入予定行程1
	stepwk=stepDef;
	spdobjN=SV0_FIXARA_SPDF;//設定速度0.1%単位

	if(!(SV0_FIXARA_AGLS<SV0_FIXARA_AGLE)){//	開始≧終了はだめ
		endF=-1;//だめ
		err1=1;//
		
	}

	spdsv = &SV_1DANSPD_SRV;//2014-10-06 koma
	while(endF==0){
		if(stepwk==0){
			err1=1;//stepwkがだめ 挿入できない
		}else{
			if (stepwk<= 1) {
				// １段目より前の速度は無い
				// spdobjN_1= 0;						//一定速度開始前速度
				spdobjN_1=spdsv[0];//2014-10-06 koma
			}else {
				// ２段目から前の速度が存在する
				spdsv = &SV_1DANSPD_SRV;
				spdobjN_1 = spdsv[stepwk-2];			//一定速度開始前速度　0.1%
			}

			length=AccLengthCalc1(spdobjN_1,spdobjN);//0.1度
			length=(length+9)/10;		//切り上げて1度単位へ変更
			digFirst=digset-length*10;	//
	
			if(	(digFirst<0)					||
				(digFirst<SV_TAIKIKAKU_SRV)		||
				(digFirst< SV_TAIKIKAKU_SRV+5)	){
				err2=1;//待機点を跨いだ digFirstがだめ･･･挿入できない
			}else{
				stepFirst=CAM_KOUTEI_SEARCH2(0,(digFirst/10));//
				if(stepFirst){
					if(stepFirst==stepwk){//これなら挿入可能
						endF=1;//stepFirstを使用する
					}else{
						if(stepwk<stepFirst){//戻った stepwk(小さい方)を使用する
							endF=2;//stepwkを使用する,ﾃﾞｰﾀは使用できる
						}else{
							stepwk=stepFirst;//loop
						}
					}
				}else{
					err2=1;//
				}
			}
		}

		//終了
		if(endF==0){
			if((err1)||(err2)){
				endF=-1;
			}
		}
	}


	//開始行程を挿入できる
	if((endF==1)||(endF==2)){
		if(endF==1){
			insFirstStep=stepFirst;
		}else{
			insFirstStep=stepwk;
		}
		if(insFirstStep<=1){
			//2014-10-06 spdobjN_1=0;
			spdobjN_1=spdsv[0];
		}else{
			spdobjN_1=spdsv[insFirstStep-2];
		}
		length=AccLengthCalc1(spdobjN_1,spdobjN);//0.1度
		length=(length+9)/10;	//切り上げて1度単位へ変更
		SVAGL[0]=digset-length*10;	//
		if(SVAGL[0]<0){
			SVAGL[0]=3590;//ありえない
		}


		//後行程
		digset=SV0_FIXARA_AGLE;
		stepwk=CAM_KOUTEI_SEARCH2(0,(digset/10));//
		if(insFirstStep<=stepwk){//step=0ははじける
			if((stepwk==1)||(stepwk==insFirstStep)){//挿入だけ
				delStep=0;
				delCnt=0;
			}else{
				delStep=insFirstStep;
				delCnt=stepwk-insFirstStep;
			}
			insSecondStep=stepwk;
		}

		//
		if(insSecondStep){	//
			if(insFirstStep==1){
				//2014-10-06 削除:spdobjN_1=spdobjN;
			}
			
			SVPOS[0]=DigRnaChange1(SVAGL[0]);	//角度→mm変換
			SVSPD[0]=spdobjN_1;
			SVTIM[0]=0;

			SVSPD[1]=spdobjN;
			SVAGL[1]=SV0_FIXARA_AGLE;
			SVPOS[1]=SV0_FIXARA_POSE;
			SVTIM[1]=0;
	
	
			err1=MOTION_INS_DEL(2,insFirstStep,delCnt,delStep,&SVAGL[0],&SVPOS[0],&SVSPD[0],&SVTIM[0]);
			if(err1==0){
			
				//一定速度領域 行程BIT情報
//2014/10/09				SV_MOT_FIX = WORD_BIT_TBL0[insFirstStep]+WORD_BIT_TBL0[insFirstStep+1];
				SV0_MOT_FIX = WORD_BIT_TBL0[insFirstStep]+WORD_BIT_TBL0[insFirstStep+1];
				SVSW_CHG_FLG |= BIT_2;				//ﾓｰｼｮﾝ(MOT)要求(cpud=>cpua)
			}
	
		}

	}

	if (err1 || err2) {
		MOT_FERR_TIM = 1000/5;					//1sec  F挿入ERR信号ON時間
		PV0_FMOTSET_MES1 = 14;					//設定不可メッセージ表示			2014/10/09
	}
	else {
		PV0_FMOTSET_MES1 = 13;					//設定完了メッセージ表示			2014/10/09
	}

}











//	***********************************
//	***								***
//	***								***
//	***								***
//	***********************************
//	100%*100%=10000
//	3000spm(ﾓｰﾀ1回転で機械1回転)でも50(rot/sec)*3600*10000 6d49,d200 余裕
//	
U4b AccLengthCalc1(S4b spd1,S4b spd2){
	S4b spd;
	U4b	length;

	spd=(spd1*spd1)-(spd2*spd2);//
	if(spd<0){
		spd=spd*-1;
	}
	if(spd){
		spd=spd/100;//0.1%など減速距離に影響はない?
		length=SETD_DEGMAX_LNGTH*spd/10000;//0.1度
	}else{
		length=0;
	}
	
	return(length);


}


//	***********************************
//	***								***
//	***								***
//	***								***
//	***								***
//	***********************************
//	(1)ﾓｰｼｮﾝを1個または2個挿入する
//	(2)ﾓｰｼｮﾝを削除する
//	INPUT 速度
//	INPUT 角度
//	INPUT 位置
//	INPUT タイマ
//	inscnt=0:ｲﾝｻｰﾄしない
//	delcnt=0:削除しない
//	削除を実行後　ｲﾝｻｰﾄを行う
//
S2b MOTION_INS_DEL(U2b inscnt,U2b insstep,U2b delcnt,U2b delstep,
					U2b *insAGL,U4b *insPOS,U2b *insSPD,U2b *insTIM){

	UNs	i,j,k;
	UNs	AGL[20];
	UNl	POS[20];
	UNs	SPD[20];
	UNs	TIM[20];

	UNs	AGL2[20];
	UNl	POS2[20];
	UNs	SPD2[20];
	UNs	TIM2[20];

	UNs	*Dst_AGL, *Dst_SPD, *Dst_TIM;
	UNl	*Dst_POS;

	UNs	errflg;//
	S2b danmax,setdan,changedan;//

	errflg=0;//err
	danmax=0;


	setdan=SV_DANSUU_SRV;

	//現状設定をworkへ
	Dst_AGL = &SV_1DANDEG_SRV;
	Dst_POS = &SV_1DANPOS_SRV;
	Dst_SPD = &SV_1DANSPD_SRV;
	Dst_TIM = &SV_1DANTIM_SRV;

	for (i=0; i<10; i++) {
		AGL[i]	=	Dst_AGL[i];
		POS[i]	=	Dst_POS[i];
		SPD[i]	=	Dst_SPD[i];
		TIM[i]	=	Dst_TIM[i];

		AGL2[i]	=	Dst_AGL[i];//ﾊﾞｯｸｱｯﾌﾟ
		POS2[i]	=	Dst_POS[i];//
		SPD2[i]	=	Dst_SPD[i];//
		TIM2[i]	=	Dst_TIM[i];//
	}

	for(i=10;i<20;i++){
		AGL[i]	=	123;
		POS[i]	=	123;
		SPD[i]	=	123;
		TIM[i]	=	123;

		AGL2[i]	=	123;//ﾊﾞｯｸｱｯﾌﾟ
		POS2[i]	=	123;//
		SPD2[i]	=	123;//
		TIM2[i]	=	123;//
	}

// koma 2012-10-19 5段仕様/10段仕様による段数
	if ( SEQ_024_SV & BIT_3) {
		danmax=10;
	}else {
		danmax=5;
	}

	//現行の段数	ﾃﾞｰﾀ化け対策
	if((setdan<1)||(danmax<setdan)){
		errflg=1;//挿入不可能
		setdan=1;//暴走対策
	}

	changedan=setdan+inscnt-delcnt;
	if( (1<=changedan) && (changedan<=danmax) ){//
		//削除
		if((delcnt!=0)&&(0<delstep)){
			j=(delstep-1);
			k=10-delcnt-j;
			for (i=0;i<k; i++) {//
				AGL[j+i]	=	AGL2[i+j+delcnt];
				POS[j+i]	=	POS2[i+j+delcnt];
				SPD[j+i]	=	SPD2[i+j+delcnt];
				TIM[j+i]	=	TIM2[i+j+delcnt];
			}
		}

		for(i=0;i<10;i++){
			AGL2[i]	=	AGL[i];
			POS2[i]	=	POS[i];
			SPD2[i]	=	SPD[i];
			TIM2[i]	=	TIM[i];
		}

		//挿入 "instep<=delstep"が条件となる簡易演算･･･call元で
		if((inscnt!=0)&&(0<insstep)){
			j=insstep-1;
			for (i=0;i<inscnt; i++) {//
				AGL[i+j]=insAGL[i];
				POS[i+j]=insPOS[i];
				SPD[i+j]=insSPD[i];
				TIM[i+j]=insTIM[i];
			}
			i=i+j;
			k=inscnt;
			for (;i<10; i++) {//
				AGL[i]=AGL2[i-k];
				POS[i]=POS2[i-k];
				SPD[i]=SPD2[i-k];
				TIM[i]=TIM2[i-k];
			}

			for (i=0; i<10; i++) {//戻す
				Dst_AGL[i]	=	AGL[i];
				Dst_POS[i]	=	POS[i];
				Dst_SPD[i]	=	SPD[i];
				Dst_TIM[i]	=	TIM[i];
			}
			SV_DANSUU_SRV=changedan;	//段数 挿入
												// 挿入
			mmon_trans_put();					//回転方式によるﾃﾞｰﾀの格納
		}
	}else{
		errflg=2;//挿入不可能
	}
	return(errflg);

}




//	島村からのサンプル
//void	INS_FIXARA_SPD(void)
//{
//	SV_MOT_FIX = BIT_0;					//一定速度領域 行程BIT情報
//	SVSW_CHG_FLG |= BIT_2;				//ﾓｰｼｮﾝ(MOT)要求(cpud=>cpua)
//}




//	2012-10-17 変更前
//void INS_MOTION(void)
//{
//	UNs	i, c;
//	UNs	AGL[10];
//	UNl	POS[10];
//	UNs	SPD[10];
//	UNs	TIM[10];
//
//	UNs	*Src_s;
//	UNl	*Src_l;
//
//	UNs	*Dst_AGL, *Dst_SPD, *Dst_TIM;
//	UNl	*Dst_POS;
//
//	if ( (1<=PVP_MOTINS_DAN) && (PVP_MOTINS_DAN<=9) ) {		//モーション挿入(C/B->HMI) 段数(1～9)
//
//		Src_s = &SV_1DANDEG_SRV;
//		for (i=0; i<10; i++, Src_s++) {
//			AGL[i] = *Src_s;
//		}
//    
//		Src_l = &SV_1DANPOS_SRV;
//		for (i=0; i<10; i++, Src_l++) {
//			POS[i] = *Src_l;
//		}
//    
//		Src_s = &SV_1DANSPD_SRV;
//		for (i=0; i<10; i++, Src_s++) {
//			SPD[i] = *Src_s;
//		}
//    
//		Src_s = &SV_1DANTIM_SRV;
//		for (i=0; i<10; i++, Src_s++) {
//			TIM[i] = *Src_s;
//		}
//
//		Dst_AGL = &SV_1DANDEG_SRV;
//		Dst_POS = &SV_1DANPOS_SRV;
//		Dst_SPD = &SV_1DANSPD_SRV;
//		Dst_TIM = &SV_1DANTIM_SRV;
//
//		for(i=0; i<9; i++) {
//			if (PVP_MOTINS_DAN == (i+1)) {
//				break;
//			}
//			*Dst_AGL = AGL[i];
//			*Dst_POS = POS[i];
//			*Dst_SPD = SPD[i];
//			*Dst_TIM = TIM[i];
//			Dst_AGL++;
//			Dst_POS++;
//			Dst_SPD++;
//			Dst_TIM++;
//		}
//
//		/* 挿入 */
//		*Dst_AGL = PVP_MOTINS_AGL;		//モーション挿入(C/B->HMI) 角度(少数点1桁データ)
//		*Dst_POS = PVP_MOTINS_POS;		//モーション挿入(C/B->HMI) 位置(少数点3桁データ)
//		*Dst_SPD = SPD[i];
//		*Dst_TIM = 1;					//0.01sec
//		Dst_AGL++;
//		Dst_POS++;
//		Dst_SPD++;
//		Dst_TIM++;
//
//		for(; i<9; i++) {
//			*Dst_AGL = AGL[i];
//			*Dst_POS = POS[i];
//			*Dst_SPD = SPD[i];
//			*Dst_TIM = TIM[i];
//			Dst_AGL++;
//			Dst_POS++;
//			Dst_SPD++;
//			Dst_TIM++;
//		}
//
//		if (SEQ_024_SV & BIT_3) {			//10段仕様？
//			if (SV_DANSUU_SRV < 10) {
//				SV_DANSUU_SRV++;			//段数+1
//			}
//		}
//		else {
//			if (SV_DANSUU_SRV < 5) {
//				SV_DANSUU_SRV++;			//段数+1
//			}
//		}
//
//V06n　2012-10-17 shima	挿入した次の速度を半分にする。
//		Dst_SPD = &SV_1DANSPD_SRV;
//		Dst_SPD +=PVP_MOTINS_DAN;
//		*Dst_SPD /= 2;
//
//		mmon_trans_put();					//回転方式によるﾃﾞｰﾀの格納
//
//		disp_stg_sel = E_sstg_mmon;			//生産[モーションモニタ]へ
//		GAMEN_NO = 3;
//		GAMEN_disp();						//画面表示
//
//	}
//
//}











/*** END ***/
