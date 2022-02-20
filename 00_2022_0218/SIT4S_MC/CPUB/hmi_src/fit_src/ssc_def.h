/*==========================================================================*/
/*		各種の共通定義														*/
/*==========================================================================*/

/***************************************/
/****	画面バージョンの定義		****/
/***************************************/
#define		E_CPUC_VER1	'V'							//CPU-C VER. No.
#define		E_CPUC_VER2	'0'							//CPU-C VER. No.
#define		E_CPUC_VER3	'6'							//CPU-C VER. No.
#define		E_CPUC_VER4	'r'							//CPU-C VER. No.

//変更履歴
//V00m	: 2003/01/27		いっぱい仕様変更
//V00n	: 2003/01/29		ｲﾝﾀｰﾛｯｸﾃﾞｰﾀのﾊﾞｰｼﾞｮﾝを表示
//V00o	: 2003/01/29		ｶﾞｲﾀﾞﾝｽ画面の横線が描画しなくなった不具合を修正
//V00p	: 2003/02/03		ﾊﾞｰｼﾞｮﾝｷｬﾗｸﾀ表示／ﾙｰﾚｯﾄ再描画／ｼｰｹﾝｽｱﾄﾞﾚｽ上限値変更／初期値ﾃﾞｰﾀ追加
//V00q	: 2003/02/04		下限位置教示変更／ﾃﾞﾊﾞｯｸﾞ画面に実測値4個追加
//V00r	: 2003/02/10		補正値の下限ﾁｪｯｸ追加
//V00s	: 2003/02/13		ロータリカム汎用出力をシーケンスへ
//V00t	: 2003/03/17		WDTﾘﾌﾚｯｼｭを1ms定周期へ／ﾛｯﾄｶｳﾝﾀのﾘｾｯﾄ処理を5ms定周期へ
//V00u  : 2003/05/07		HwsetupのLCDｱｸｾｽ時間の変更 =>5wait
//V01   : 2003/07/			生産下限追加等
//V01a  : 2003/07			異常履歴画面追加等
//V01b  : 2003/07/23		画面ﾁﾗﾂｷ対策
//V01c  : 2003/08/07		教示変更
//V01d  : 2004/01/09~16		連続寸動一行程対応、行程段数10段対応、ﾐｽﾌｨｰﾄﾞ6回路対応
//V01e  : 2004/03/29		ﾓｰｼｮﾝ6~10画面で5段以下設定時はﾓｰｼｮﾝ1~5画面へ自動遷移／ﾓｰｼｮﾝ6~10画面の初期ｶｰｿﾙ位置変更
//V01g  : 2004/04/20		ﾊﾞｰｼﾞｮﾝUP変更  5段使用で'f'使用のため'g'にする。
//V01h  : 2004/05/06		設定値の設定単位や上限値を変更。
//V01i  : 2004/05/19		待機点1,2,3対応、上位通信対応。
//V01j  : 2004/07/01		中型対応
//V01k  : 2004/07/05		荷重補正対応
//V01l  : 2004/08/18		ｵｰﾊﾞｰﾛｰﾄﾞﾘﾐｯﾄ対応、通信ﾀｲﾑｱｳﾄ追加
//V01l_a: 2004/09/16		ｺﾏﾂ産機殿にて現調時に修正
//V01l_b: 2004/09/17		ｺﾏﾂ産機殿にて現調時に修正
//V01l_c: 2004/09/27		ｽﾗｲﾄﾞ自動調節不具合修正
//V01l_d: 2004/09/27		ﾎﾟｼﾞｼｮﾅﾋﾞｯﾄ飛び回数設定
//V01l_e: 2004/09/28		ﾃﾞﾊﾞｯｸﾞ画面ｱﾄﾞﾚｽ設定上限値変更
//V01m  : 2004/10/04		下限／荷重切換、ｽﾗｲﾄﾞ自動調節の少数点設定対応
//V01m_a: 2004/11/26		待機角転送追加(電源投入時、待機角かC/Bへ渡らない不具合対策)
//V01n  : 2004/11/30		ﾄﾗﾝｽﾌｧﾓｰｼｮﾝ(ﾓｰｼｮﾝの3段目だけ設定可能)対応
//V01o  : 2005/01/17		C/Bへ渡す荷重値変更
//V01o_a: 2005/01/29		反映指令でﾘﾆｱ位置をﾊﾞｯｸｱｯﾌﾟしない。（反映指令でSVSW_CHG_FLGのBIT8をONしない） ｴｸｾﾃﾞｨにて
//V01p  : 2005/03/04		C/Bへ渡す荷重値転送ﾊﾟﾗﾒｰﾀ切換。通信BCC異常返信
//							ｴｸｾﾃﾞｨにて行ったV01n_b機能追加(機械原点狂う？の網掛け）
//V01q  : 2005/04/06		上位通信の反映指令でﾓｰｼｮﾝ設定が反映されない不具合を修正
//V01r  : 2005/04/29		段取画面を標準と中型に分ける。ﾐｽﾌｨｰﾄﾞ5,6のSW5,6表示変更
//V01s  : 2005/08/26		反映指令で再描画
//V01t  : 2005/11/25		荷重教示不具合修正
//V01u  : 2005/12/07		ﾓｰｼｮﾝで下限表示時に荷重の型ﾃﾞｰﾀを読込むと単位がmmになってしまう示不具合修正
//							型ﾃﾞｰﾀ変更中の電源OFFでも型ﾃﾞｰﾀ読出し時に「変更されています」ﾒｯｾｰｼﾞを表示
//V01v  : 2006/07/11		LSA用ｻｰﾎﾞﾊﾟﾗﾒｰﾀ追加、ﾊﾟﾙｻ用ｻｰﾎﾞﾊﾟﾗﾒｰﾀ追加、ﾄﾚﾝﾄﾞ対応
//V01w  : 2006/07/25		ｵｰﾊﾞﾗｲﾄﾞ設定、段取寸動停止設定、補正ﾓﾆﾀWindow追加
//V01x  : 2006/09/01		ｼｰｹﾝｽによる言語切換機能追加、推定SPM表示追加
//V01y  : 2006/10/10		反転ﾙｰﾚｯﾄ表示対応、SW1～6の反転処理、角度表示専用4倍角対応、COP2対応
//V01z  : 2006/11/17		ｵｰﾊﾞﾗｲﾄﾞSW追加、ﾄﾚﾝﾄﾞ画面追加、補正ﾓﾆﾀの荷重実測値変更
//V02   : 2006/12/01		定周期でWDT_CLR、稼動回数をCPUAに転送
//V02a  : 2006/12/05		荷重教示を荷重平均にする。荷重平均ﾊﾞｯｸｱｯﾌﾟ処理追加。荷重教示有効／無効処理追加
//V04   : 2006/12/08		荷重設定を実測と常に比較する(50.11)。これをSIT4の初版ﾊﾞｰｼﾞｮﾝとする。
//V04a  : 2006/12/20		ｶﾑ名称入力で"-"を入力したとき、"="となるﾊﾞｸﾞを修正
//V04a  : 2006/12/21		ｼｰｹﾝｽによる言語切換えでﾓｰｼｮﾝｸﾞﾗﾌが出ない不具合を修正
//V05   : 2007/01/10		ﾊﾞｰｼﾞｮﾝUP時のﾘﾄﾗｲ、SUMﾁｪｯｸ処理追加、外字対応、ET1対応
//V05a  : 2007/01/29		型段取画面のSW表示が出ない不具合修正
//V05b  : 2007/02/13		ｻﾝﾌﾟﾘﾝｸﾞ関係の設定値を初期化の対象とする。
//V05c  : 2007/02/13		2軸ｻｰﾎﾞﾊﾟﾗｰﾒｰﾀ対応
//V05d  : 2007/03/02		現型番号をSEQ076へ転送
//V05e  : 2007/03/07		ｵﾌﾟｼｮﾝｽﾃｰﾀｽをｲﾆｼｬﾙﾘｰﾄﾞ処理
//V05f  : 2007/04/24		ﾓｰｼｮﾝ5段時にﾓｰｼｮﾝ設定画面で変更した内容がﾓｰｼｮﾝﾓﾆﾀ画面に反映されないﾊﾞｸﾞを修正
//V05g  : 2007/05/22		補正ﾓﾆﾀ画面での生産数値設定無の対応、固定文字の表示条件追加
//V05h  : 2007/06/20		ET1がついていないのについていると見えてしまう不具合修正
//V05i  : 2007/10/05		荷重計ﾊﾞｯｸｱｯﾌﾟ化け調査ﾌﾟﾛｸﾞﾗﾑ組込み
//V05j  : 2007/12/07		荷重計ﾊﾞｯｸｱｯﾌﾟ化け対策、調査ﾌﾟﾛｸﾞﾗﾑは外す、ET1のIPｱﾄﾞﾚｽ対応
//V05k  : 2008/08/27		H2W用ｻｰﾎﾞﾊﾟﾗに遷移する不具合修正、段取画面のｽﾗｲﾄﾞ調節でSW6表示は「開く」のはずが「下降」「上昇」を表示してしまう不具合修正
//V05l  : 2009/03/19		通信異常対策+Ｔﾘﾝｸ対策
//V05l-a: 2009/03/24		SIT(HMI)->OP(PLC)のTﾘﾝｸ領域は、仕様設定77がONの時とする。OFFのときはSIT(SEQ)->OP(PLC)となる
//V05m  : 2009/07/14		ｲﾝﾀｰﾛｯｸｶﾞｲﾀﾞﾝｽ情報を出力（HMI→CB→KOMTORAX→上位装置）
//V05n  : 2009/08/04		ﾌﾞﾚｰｷ角度、ﾌﾞﾚｰｷﾀｲﾑ上限値追加
//V05o  : 2009/08/17		ﾓｰｼｮﾝ実測ｻﾝﾌﾟﾘﾝｸﾞ波形画面、ﾓｰｼｮﾝ実測ﾄﾚﾝﾄﾞ波形画面追加
//V05p  : 2009/11/04		ｻｰﾎﾞﾊﾟﾗﾒｰﾀ12の上限値変更
//V05q  : 2010/07/07		KEYの2個同時押し対策、KEYのONｴｯｼﾞOFFｴｯｼﾞ同時発生時の対策、ｶｰｿﾙ移動時の出力OFF対策
//V05r  : 2010/08/10~		制動性能試験用ﾀｲﾏ関係追加、JIS第2水準対応、
//V06   : 2010/09/14		電力モニタ画面追加・・・画面データ格納領域変更（これに伴いバージョンUPも変更）
//V06a  : 2010/10/18		電力モニタ画面変更、サンプリング波形画面の電力符号対応
//V06b  : 2010/12/08		
//V06c  : 2011/01/05		生産管理ｳｨﾝﾄﾞｳ追加
//V06d  : 2011/03/18		
//V06e  : 2011/05/01		ロットカウンタアップ信号追加
//V06f  : 2011/07/06		ｻｰﾎﾞﾊﾟﾗﾒｰﾀBH～BM追加、振子の上限角／上限位置設定にﾘﾐｯﾀ、
//V06g  : 2011/07/28		タッチ位置自動検出機能追加
//V06h  : 2011/09/09		制動性能試験インターベルタイマのバックアップ対応
//V06i  : 2011/12/05		ADCﾓｰﾄﾞ変更時のSUMｴﾗｰ不具合修正
//V06j  : 2012/03/24		ロットカウンタ誤アップ修正
//V06k  : 2012/04/17		反転時の目標角上限ﾘﾐｯﾀ不具合修正
//V06l  : 2012/09/20		簡易見える化無し用のｻﾝﾌﾟﾘﾝｸﾞ設定画面／ﾄﾚﾝﾄﾞ設定画面を追加
//V06m  : 2012/09/24		仕様設定画面9，10追加
//V06n  : 2012/10/15		仕様変更
//V06o  : 2013/02/04		改善
//V06p  : 2013/02/16		仕様変更
//V06q  : 2013/06/18		バージョンアップ不具合修正
//V06r  : 2013/09/30        113.10,113.11にてﾎﾞﾙｽﾀLも+50/-50mmする


/***************************************/
/****	データ型の定義				****/
/***************************************/
typedef	unsigned int	UNi;
typedef	unsigned char	UNb;
typedef	unsigned short	UNs;
typedef	unsigned long	UNl;

typedef	unsigned long	usCount;

/*==========================================================================*/
/*		情報テーブルの定義													*/
/*==========================================================================*/
/***************************************/
/****	カーソル情報テーブル定義	****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//ｶｰｿﾙのX,Y軸
	UNs	DATA_NO;			//ｶｰｿﾙ種別番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
	UNs	SV_MAX;				//設定値ﾃｰﾌﾞﾙ個数
	UNs	SW_MAX;				//SWﾃｰﾌﾞﾙ個数
	UNs	CARA_NO;			//ｶｰｿﾙ表示ｷｬﾗ種別（未使用）
	UNs	MOVE_NO;			//画面移動番号
	UNs	TOK_NO;				//特殊番号(B0:ｶｰｿﾙ無し)
	UNs	YOBI1;				//予備１
	UNs	YOBI2;				//予備２
	UNs	SW56_UP;			//SW56上段ｷｬﾗｸﾀ
	UNs	SW5_DN;				//SW5下段ｷｬﾗｸﾀ
	UNs	SW6_DN;				//SW6下段ｷｬﾗｸﾀ
	UNs	SW5_SUB;			//SW5ﾃﾞｰﾀ処理番号
	UNs	SW6_SUB;			//SW6ﾃﾞｰﾀ処理番号
	UNs	YOBI3;				//予備３
	UNs	AKI;				//空き
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//表示Xﾄﾞｯﾄ位置
	UNs	Y_POS;				//表示Yﾄﾞｯﾄ位置
	UNs	M_LEN;				//表示文字数(半角で)
	UNs	SIZE;				//文字サイズ
	UNs	C_COL;				//文字色
	UNs	B_COL1;				//背景色
	UNs	B_COL2;				//背景色
#endif
	} CSR_TBL_TDEF;


/***************************************/
/****	設定値情報テーブル定義		****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//設定値表示のX,Y軸
	UNs	AKI;				//空き
	UNs	*DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNs	SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
	UNs	GRP_NO;				//ｸﾞﾙｰﾌﾟ番号
	UNs	TOK_FLG;			//特殊ﾌﾗｸﾞ
	UNs	BYTE_NO;			//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
	UNs	TEN_POS;			//少数点の位置
	UNs	CSR_NO;				//ｶｰｿﾙ認識番号
	UNs	DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
	UNs	SAVE_NO;			//格納ﾌﾗｸﾞ
	UNs	YOBI_NO;			//予備
	UNs	AKI2;				//空き
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//表示Xﾄﾞｯﾄ位置
	UNs	Y_POS;				//表示Yﾄﾞｯﾄ位置
	UNs	M_LEN;				//表示文字数(半角で)
	UNs	SIZE;				//文字サイズ
	UNs	C_COL;				//文字色
	UNs	B_COL1;				//背景色
	UNs	B_COL2;				//背景色
#endif
	} SV_TBL_TDEF;


/***************************************/
/****	実測値情報テーブル定義		****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//実測値表示のX,Y軸
	UNs	AKI;				//空き
	UNs	*DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNs	SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
	UNs	GRP_NO;				//ｸﾞﾙｰﾌﾟ番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
	UNs	TOK_FLG;			//特殊ﾌﾗｸﾞ
	UNs	BYTE_NO;			//ﾃﾞｰﾀ格納先のﾊﾞｲﾄ長
	UNs	TEN_POS;			//少数点の位置
	UNs	YOBI1;				//予備１
	UNs	YOBI2;				//予備２
	UNs	AKI2;				//空き
	UNs	AKI3;				//空き
	UNs	AKI4;				//空き
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//表示Xﾄﾞｯﾄ位置
	UNs	Y_POS;				//表示Yﾄﾞｯﾄ位置
	UNs	M_LEN;				//表示文字数(半角で)
	UNs	SIZE;				//文字サイズ
	UNs	C_COL;				//文字色
	UNs	B_COL1;				//背景色
	UNs	B_COL2;				//背景色
#endif
	} PV_TBL_TDEF;


/***************************************/
/****	ＳＷデータ情報テーブル定義	****/
/***************************************/
typedef struct {

	UNs	XY_POS;				//実測値表示のX,Y軸
	UNs	AKI;				//空き
	UNs	*DATA_ADR;			//ﾃﾞｰﾀ格納ｱﾄﾞﾚｽ
	UNs	SUB_NO;				//ｻﾌﾞﾙｰﾁﾝ番号
	UNs	GRP_NO;				//ｸﾞﾙｰﾌﾟ番号（設定値のｸﾞﾙｰﾌﾟ番号と同じ）
	UNs	TOK_FLG;			//特殊ﾌﾗｸﾞ
	UNs	CHG_NO;				//ﾃﾞｰﾀ格納先の変更ﾋﾞｯﾄ位置
	UNs	CSR_NO;				//この設定値の属するｶｰｿﾙ認識番号
	UNs	DSP_NO;				//ｶｰｿﾙ認識番号内の移動順位
	UNs	CARA_NO;			//表示用ｷｬﾗｸﾀ番号
	UNs	KAN_NO;				//関連ﾊﾞｲﾄ
	UNs	*KAN_ADR;			//関連ｱﾄﾞﾚｽ
//	UNs	YOBI1;				//予備１(SW_SAVE_NO)
	UNs	SAVE_NO;			//格納ﾌﾗｸﾞ
	UNs	YOBI2;				//予備２
#if ( SIT_TYPE_SEL == TYPE_SIT4 )
	UNs	X_POS;				//表示Xﾄﾞｯﾄ位置
	UNs	Y_POS;				//表示Yﾄﾞｯﾄ位置
	UNs	M_LEN;				//表示文字数(半角で)
	UNs	SIZE;				//文字サイズ
	UNs	C_COL;				//文字色
	UNs	B_COL1;				//背景色
	UNs	B_COL2;				//背景色
#endif
	} SW_TBL_TDEF;


typedef struct {				//画面別ヘッダー情報の構造
	UNb		chr_cnt;			//文字列個数
	UNb		csr_cnt;			//ｶｰｿﾙ個数
	UNb		svp_cnt;			//設定値個数
	UNb		pvp_cnt;			//実測値個数
	UNb		swl_cnt;			//SW-LAMP個数
	UNb		grp_cnt;			//ｸﾞﾗﾌｨｯｸ個数
	UNb		scr_col;			//ｽｸﾘｰﾝ色
	UNb		rev;				//空き
	} GAMENn_HEAD_st;


typedef struct {				//各データ表示情報の構造
	UNs		link_no;			//ﾘﾝｸNo.
	UNs		rev1;				//予備
	UNs		bgn_xdot;			//始点X
	UNs		bgn_ydot;			//始点Y
	UNs		chr_no;				//ｷｬﾗｸﾀNo（ｸﾞﾗﾌｨｯｸの時は距離X）
	UNs		chr_size;			//文字ｻｲｽﾞ（ｸﾞﾗﾌｨｯｸの時は距離Y）
	UNb		chr_col;			//文字色
	UNb		bgnd1_col;			//背景色1
	UNb		bgnd2_col;			//背景色2
	UNb		option;				//ｵﾌﾟｼｮﾝ
	UNb		parts_no;			//ﾊﾟｰﾂNo.
	UNb		rev2;				//予備
	UNs		rev3;				//予備
	} DISP_INFO_st;


typedef struct {				//実測ｻﾝﾌﾟﾘﾝｸﾞﾃﾞｰﾀの構造		//V05o
	UNl		renia1;				//ﾘﾆｱ1位置(0.001mm)
	UNl		renia2;				//ﾘﾆｱ2位置(0.001mm)
	UNs		angle;				//角度(0.1度)
	UNs		kajyuT;				//荷重合計(KN)
	UNs		kajyuL;				//荷重左(KN)
	UNs		kajyuR;				//荷重右(KN)
	UNs		seq;				//ｼｰｹﾝｽ
	UNs		yob1;				//予備
	UNl		elepw;				//瞬時電力(0.01kW)		V06
	} WAVE_SAMP_DATA_ST;


typedef struct {				//実測ﾄﾚﾝﾄﾞﾃﾞｰﾀの構造			//V05o
	UNl		renia1;				//ﾘﾆｱ1位置(0.001mm)
	UNl		renia2;				//ﾘﾆｱ2位置(0.001mm)
	UNs		kajyuT;				//荷重合計(KN)
	UNs		kajyuL;				//荷重左(KN)
	UNs		kajyuR;				//荷重右(KN)
//V06	UNs		yob1;				//予備
	UNs		elepw;				//1ｻｲｸﾙ電力(0.01kWh)	V06
	} WAVE_TRND_DATA_ST;


typedef struct {				//実測ｻﾝﾌﾟﾘﾝｸﾞﾃﾞｰﾀの構造		//V05o
	UNs		renia1;				//ﾘﾆｱ1位置(0.01mm)
	UNs		renia2;				//ﾘﾆｱ2位置(0.01mm)
	UNs		angle;				//角度(0.1度)
	UNs		kajyuT;				//荷重合計(KN)
	UNs		kajyuL;				//荷重左(KN)
	UNs		kajyuR;				//荷重右(KN)
	UNs		seq1;				//ｼｰｹﾝｽ
	UNs		seq2;				//ｼｰｹﾝｽ
	UNs		elepw;				//瞬時電力(0.01kW)		V06
	} WAVE_SAMP_DOT_ST;


typedef struct {				//実測ﾄﾚﾝﾄﾞﾃﾞｰﾀの構造			//V05o
	UNs		renia1;				//ﾘﾆｱ1位置(0.01mm)
	UNs		renia2;				//ﾘﾆｱ2位置(0.01mm)
	UNs		kajyuT;				//荷重合計(KN)
	UNs		kajyuL;				//荷重左(KN)
	UNs		kajyuR;				//荷重右(KN)
	UNs		rnaupl;				//上限検出位置
	UNs		rnadnl;				//下限検出位置
	UNs		elepw;				//1ｻｲｸﾙ電力(0.01kWh)	V06
	} WAVE_TRND_DOT_ST;



/* 定数定義 ---------------------------------------------------------- */
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

/***	Key用の定義	***/
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

#define	E_key_csr_mode	0x03					//ｶｰｿﾙ key mode
#define	E_key_left		0x01					//key code ←
#define	E_key_right		0x02					//key code →
#define	E_key_down		0x03					//key code ↓
#define	E_key_up		0x04					//key code ↑

#define	E_key_sw14_mode	0x04					//SW1～4 key mode
#define	E_key_sw1		0x01					//key code SW1
#define	E_key_sw2		0x02					//key code SW2
#define	E_key_sw3		0x03					//key code SW3
#define	E_key_sw4		0x04					//key code SW4
#define	E_key_sw1_down	0x11					//key code SW1(立下り)
#define	E_key_sw2_down	0x12					//key code SW2(立下り)
#define	E_key_sw3_down	0x13					//key code SW3(立下り)
#define	E_key_sw4_down	0x14					//key code SW4(立下り)
#define	E_key_sw7_down	0x17					//key code SW7(立下り)	/* V01z */

#define	E_key_sw56_mode	0x05					//SW5/6 key mode
#define	E_key_sw5		0x05					//key code SW5
#define	E_key_sw6		0x06					//key code SW6
#define	E_key_sw5_down	0x15					//key code SW5(立下り)
#define	E_key_sw6_down	0x16					//key code SW6(立下り)

#define	E_key_sw7_mode	0x06					//SW7 key mode
#define	E_key_sw7		0x07					//key code SW7

/***	表示用の定義	***/
#define	E_gmen_bf		15*16*40				//1画面の表示用ﾊﾞｯﾌｧ数
#define	E_gmen_size		15*16*40*2				//1画面の表示用ﾊﾞｯﾌｧ･ｻｲｽﾞ
#define	E_line			40						//1行の表示文字数
#define	E_line_bf		16*40					//1行の表示用ﾊﾞｯﾌｧ数
//#define	E_line_size		16*40*2					//1行の表示用ﾊﾞｯﾌｧ･ｻｲｽﾞ
#define	E_line_size		16*40					//1行の表示用ﾊﾞｯﾌｧ･ｻｲｽﾞ
#define	E_next_dot		40						//1文字の次dot位置数

/***	文字コードの定義	***/
#define	E_AS_SP			0x20					//スペース［ASCIIｺｰﾄﾞ］
#define	E_AS_SPSP		0x2020					//スペース［ASCIIｺｰﾄﾞ］
#define	E_AS_TEN		0x2e					//”.”　 ［ASCIIｺｰﾄﾞ］

#define	E_SJ_SP			0x8140					//スペース［S-JISｺｰﾄﾞ］
#define	E_SJ_TEN		0x8144					//”.”　 ［S-JISｺｰﾄﾞ］
#define	E_SJ_Base		0x821f					//ASCII+0x821f=０～９［S-JISｺｰﾄﾞ］


//生産の管理ｽﾃｰｼﾞ数
#define		E_sstg_init		0x00		//生産[基本]へ
#define		E_sstg_set1		0x01		//生産[生産設定1]へ
#define		E_sstg_set2		0x02		//生産[生産設定2]へ
#define		E_sstg_koud		0x03		//生産[輝度設定]へ
#define		E_sstg_gaid		0x04		//生産[ガイダンス表示]へ
#define		E_sstg_schk		0x05		//生産[シーケンスチェック]へ
#define		E_sstg_mmon		0x06		//生産[モーションモニタ]へ
#define		E_sstg_mcg		0x07		//生産[モーショングラフ]へ
#define		E_sstg_deb		0x08		//生産[デバッグ]へ
#define		E_sstg_his		0x09		//生産[異常履歴]へ
#define		E_sstg_mmon2	0x0a		//生産[モーションモニタ6～10]へ		/* V01d */
#define		E_sstg_samp		0x0b		//生産[サンプリング]へ				/* V01v */
#define		E_sstg_hos		0x0C		//生産[補正モニタ]へ				/* V01w */
#define		E_sstg_trnd		0x0d		//生産[トレンド]へ					/* V01z */
#define		E_sstg_pvsmp	0x0e		//生産[モーションサンプリング表示]へ	/* V05o */
#define		E_sstg_pvtrd	0x0f		//生産[モーショントレンド表示]へ		/* V05o */
#define		E_sstg_epm		0x10		//生産[電力モニタ]へ				/* V06  */
#define		E_sstg_seidou	0x11		//生産[制動試験WIN]へ				/* V06  */
#define		E_sstg_seikan	0x12		//生産[生産管理WIN]へ				/* V06c */
#define		E_sstg_wkstr0	0x13		//生産[作業開始1WIN]へ				/* V06c */
#define		E_sstg_wkstr1	0x14		//生産[作業開始2WIN]へ				/* V06c */
#define		E_sstg_wkstr2	0x15		//生産[作業開始3WIN]へ				/* V06c */
#define		E_sstg_wkstr3	0x16		//生産[作業開始4WIN]へ				/* V06c */
#define		E_sstg_wkstr4	0x17		//生産[作業開始5WIN]へ				/* V06c */
#define		E_sstg_wkstr5	0x18		//生産[作業開始6WIN]へ				/* V06c */
#define		E_sstg_wkstr6	0x19		//生産[作業開始7WIN]へ				/* V06c */
#define		E_sstg_wkstp0	0x1a		//生産[作業終了0WIN]へ				/* V06c */
//段取の管理ｽﾃｰｼﾞ数
#define		E_kstg_init		0x00		//段取[基本]へ
#define		E_kstg_gaid		0x01		//段取[ガイダンス表示]へ
#define		E_kstg_schk		0x02		//段取[シーケンスチェック]へ
#define		E_kstg_scon		0x03		//段取[スライド調節]へ
#define		E_kstg_bara		0x04		//段取[バランサ調圧]へ
#define		E_kstg_daic		0x05		//段取[ダイクッション調節]へ
#define		E_kstg_kana		0x06		//段取[自動金型交換]へ
//データ設定の管理ｽﾃｰｼﾞ数
#define		E_dstg_init		0x00		//データ設定[基本]へ
#define		E_dstg_mset		0x01		//データ設定[モーション設定]へ
#define		E_dstg_mcg		0x02		//データ設定[モーショングラフ]へ
#define		E_dstg_tms1		0x03		//データ設定[エジェクタ]へ
#define		E_dstg_tms2		0x04		//データ設定[ミスフィード1]へ
#define		E_dstg_tms3		0x05		//データ設定[ミスフィード2]へ
#define		E_dstg_tms4		0x06		//データ設定[ロータリカム1]へ
#define		E_dstg_tms5		0x07		//データ設定[ロータリカム2]へ
#define		E_dstg_tms6		0x08		//データ設定[ロータリカム名称]へ
#define		E_dstg_kata		0x09		//データ設定[型番号]へ
#define		E_dstg_name		0x0a		//データ設定[型番号名称]へ
#define		E_dstg_memo		0x0b		//データ設定[型番号メモ]へ
#define		E_dstg_mmon		0x0c		//データ設定[メンテナンスモニタ]へ
#define		E_dstg_ksel		0x0d		//データ設定[機能選択]へ
#define		E_dstg_mset2	0x0e		//データ設定[モーションモニタ6～10]へ	/* V01d */
#define		E_dstg_ksin		0x0f		//データ設定[加振機能設定]へ			/* V05r */
#define		E_dstg_cntc		0x10		//データ設定[ｶｳﾝﾄ値修正]へ				/* V06b */
#define		E_dstg_Lang		0x11		//データ設定[言語設定]へ				/* V06m */
#define		E_dstg_wkstr0	0x13		//データ設定[作業開始1WIN]へ			/* V06c */
#define		E_dstg_wkstr1	0x14		//データ設定[作業開始2WIN]へ			/* V06c */
#define		E_dstg_wkstr2	0x15		//データ設定[作業開始3WIN]へ			/* V06c */
#define		E_dstg_wkstr3	0x16		//データ設定[作業開始4WIN]へ			/* V06c */
#define		E_dstg_wkstr4	0x17		//データ設定[作業開始5WIN]へ			/* V06c */
#define		E_dstg_wkstr5	0x18		//データ設定[作業開始6WIN]へ			/* V06c */
#define		E_dstg_wkstr6	0x19		//データ設定[作業開始7WIN]へ			/* V06c */
#define		E_dstg_wkstp0	0x1a		//データ設定[作業終了0WIN]へ			/* V06c */
//ｼｽﾃﾑ設定の管理ｽﾃｰｼﾞ数
#define		E_ystg_init		0x00		//ｼｽﾃﾑ設定[基本]へ
//#define		E_ystg_sys1		0x01		//ｼｽﾃﾑ設定[仕様設定1]へ
//#define		E_ystg_sys2		0x02		//ｼｽﾃﾑ設定[仕様設定2]へ
//#define		E_ystg_sys3		0x03		//ｼｽﾃﾑ設定[仕様設定3]へ
//#define		E_ystg_sys4		0x04		//ｼｽﾃﾑ設定[仕様設定4]へ
//#define		E_ystg_sys5		0x05		//ｼｽﾃﾑ設定[仕様設定5]へ
//#define		E_ystg_sys6		0x06		//ｼｽﾃﾑ設定[仕様設定6]へ
//#define		E_ystg_sys7		0x07		//ｼｽﾃﾑ設定[仕様設定7]へ
//#define		E_ystg_sys8		0x08		//ｼｽﾃﾑ設定[仕様設定8]へ
#define		E_ystg_sys1		0x41		//ｼｽﾃﾑ設定[仕様設定1]へ
#define		E_ystg_sys2		0x42		//ｼｽﾃﾑ設定[仕様設定2]へ
#define		E_ystg_sys3		0x43		//ｼｽﾃﾑ設定[仕様設定3]へ
#define		E_ystg_sys4		0x44		//ｼｽﾃﾑ設定[仕様設定4]へ
#define		E_ystg_sys5		0x45		//ｼｽﾃﾑ設定[仕様設定5]へ
#define		E_ystg_sys6		0x46		//ｼｽﾃﾑ設定[仕様設定6]へ
#define		E_ystg_sys7		0x47		//ｼｽﾃﾑ設定[仕様設定7]へ
#define		E_ystg_sys8		0x48		//ｼｽﾃﾑ設定[仕様設定8]へ
#define		E_ystg_sys9		0x49		//ｼｽﾃﾑ設定[仕様設定9]へ			V06m
#define		E_ystg_sysA		0x4a		//ｼｽﾃﾑ設定[仕様設定10]へ		V06m

#define		E_ystg_cbs1		0x09		//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ1]へ
#define		E_ystg_cbs2		0x0a		//ｼｽﾃﾑ設定[C/Bｼｽﾃﾑ2]へ
#define		E_ystg_spr1		0x0b		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ1]へ
#define		E_ystg_spr2		0x0c		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ2]へ
#define		E_ystg_spr3		0x0d		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ3]へ
#define		E_ystg_spr4		0x0e		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ4]へ
#define		E_ystg_spr5		0x0f		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ5]へ
#define		E_ystg_spr6		0x10		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ6]へ
#define		E_ystg_scm		0x11		//ｼｽﾃﾑ設定[ｼｽﾃﾑｶﾑ設定]へ
#define		E_ystg_tmct		0x12		//ｼｽﾃﾑ設定[ﾀｲﾏ/ｶｳﾝﾀ]へ
#define		E_ystg_kjyu		0x13		//ｼｽﾃﾑ設定[荷重計設定]へ
#define		E_ystg_sura		0x14		//ｼｽﾃﾑ設定[ｽﾗｲﾄﾞ設定]へ
#define		E_ystg_dbak		0x15		//ｼｽﾃﾑ設定[ﾊﾞｯｸｱｯﾌﾟﾃﾞｰﾀ設定]へ
#define		E_ystg_dini		0x16		//ｼｽﾃﾑ設定[ﾃﾞｰﾀ初期化]へ
#define		E_ystg_dail		0x17		//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節左]へ		/* V01j */
#define		E_ystg_dair		0x18		//ｼｽﾃﾑ設定[ﾀﾞｲｸｯｼｮﾝ調節右]へ		/* V01j */
#define		E_ystg_atuc		0x19		//ｼｽﾃﾑ設定[圧力調節設定]へ			/* V01j */
#define		E_ystg_spr7		0x1a		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ7]へ			/* V01v */
#define		E_ystg_spr8		0x1b		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ8]へ			/* COP2対応 */
#define		E_ystg_spr9		0x1c		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ9]へ			/* COP2対応 */
#define		E_ystg_sprA		0x1d		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ10]へ			/* COP2対応 */
#define		E_ystg_sprB		0x1e		//ｼｽﾃﾑ設定[ｻｰﾎﾞﾊﾟﾗﾒｰﾀ11]へ			/* V06 */
#define		E_ystg_kchg		0x1f		//ｼｽﾃﾑ設定[機器交換時設定]へ		/* V06p */

/****************************************************************************/
#define		INTROCK_MAX		7					/* ｲﾝﾀｰﾛｯｸ検索件数			*/

/****************************************************************************/

#define		DISP_MN		'-'							//V01 
#define		DISP_PL		' '							//V01 


//★★★★★★★	以下、ＳＩＴ－４で追加		★★★★★★★
#define		PanelWidth		640//dot
#define		PanelHeight		480//dot
#define		WindowHeight	288//dot
#define		PanelDANWidth	336//dot
#define		Window2Height	 96//dot				//V06c

#define		SV_UNDER_COLOR		0			//設定値のアンダーラインカーソル色（マゼンダ）

#define		GAMENn_HEAD_SIZE	 8//byte
//#define		DISP_INFO_SIZE		18//byte
#define		DISP_INFO_SIZE		20//byte

#define		MOJI_HEAD_SIZE		 2//byte			// キャラクテーブルの１文字列内のヘッダ部
#define		MOJI_DATA_SIZE		16//byte			// キャラクテーブルの１文字列内のキャラクタデータ部
#define		CSR_HEAD_SIZE		 2//byte			// キャラクテーブルの１カーソル内のヘッダ部
#define		CSR_DATA_SIZE		22//byte			// キャラクテーブルの１カーソル内のキャラクタデータ部
#define		SWL_HEAD_SIZE		 2//byte			// キャラクテーブルの１ＳＷ－ＬＡＭＰ内のヘッダ部
#define		SWL_DATA_SIZE		 8//byte			// キャラクテーブルの１ＳＷ－ＬＡＭＰ内のキャラクタデータ部
#define		S56_HEAD_SIZE		 2//byte			// キャラクテーブルの１ＳＷ５・６内のヘッダ部
#define		S56_DATA_SIZE		 8//byte			// キャラクテーブルの１ＳＷ５・６内のキャラクタデータ部
#define		MES_HEAD_SIZE		 2//byte			// キャラクテーブルの１インターロック内のヘッダ部
#define		MES_DATA_SIZE		40//byte			// キャラクテーブルの１インターロック内のキャラクタデータ部
#define		S56U_HEAD_SIZE		 2//byte			// キャラクテーブルの１インターロック内のヘッダ部
#define		S56U_DATA_SIZE		16//byte			// キャラクテーブルの１インターロック内のキャラクタデータ部
#define		SPE_HEAD_SIZE		 2//byte			// キャラクテーブルの１インターロック内のヘッダ部
#define		SPE_DATA_SIZE		40//byte			// キャラクテーブルの１インターロック内のキャラクタデータ部

#define		CHAR_MOJI_SIZE		(MOJI_HEAD_SIZE + MOJI_DATA_SIZE)		//byte
#define		CHAR_CSR_SIZE		(CSR_HEAD_SIZE + CSR_DATA_SIZE)			//byte
#define		CHAR_SWL_SIZE		(SWL_HEAD_SIZE + (SWL_DATA_SIZE * 2))	//byte
#define		CHAR_S56_SIZE		(S56_HEAD_SIZE + S56_DATA_SIZE)			//byte
#define		CHAR_MES_SIZE		(MES_HEAD_SIZE + MES_DATA_SIZE)			//byte
#define		CHAR_S56U_SIZE		(S56U_HEAD_SIZE + S56U_DATA_SIZE)		//byte
#define		CHAR_SPE_SIZE		(SPE_HEAD_SIZE + SPE_DATA_SIZE)			//byte

#define		M_char				16//byte			//文字列最大16ﾊﾞｲﾄ長

#define		All_chr_tbl_top		0xA0070000
#define		All_chr_head_size	16//byte

#define		CTL_CSR_TBL_SIZE	32//;byte
#define		CTL_SVP_TBL_SIZE	28//;byte
#define		CTL_PVP_TBL_SIZE	24//;byte
#define		CTL_SWL_TBL_SIZE	32//;byte
#define		CTL_CHR_TBL_SIZE	16//;byte



#define		COL_BLACK	0x00	/* 00：黒				R:000,G:000,B:000	*/
#define		COL_BLUE	0x01	/* 01：青				R:000,G:000,B:255	*/
#define		COL_GREEN	0x02	/* 02：緑				R:000,G:255,B:000	*/
#define		COL_LBULE	0x03	/* 03：水色				R:000,G:255,B:255	*/
#define		COL_RED		0x04	/* 04：赤				R:255,G:000,B:000	*/
#define		COL_PINK	0x05	/* 05：ﾏｾﾞﾝﾀﾞ（ﾋﾟﾝｸ）	R:255,G:000,B:255	*/
#define		COL_YELLOW	0x06	/* 06：黄				R:255,G:255,B:000	*/
#define		COL_WHITE	0x07	/* 07：白				R:255,G:255,B:255	*/
#define		COL_GRAY1	0x08	/* 08：灰色1			R:216,G:216,B:216	*/
#define		COL_GRAY2	0x09	/* 09：灰色2			R:192,G:192,B:192	*/
#define		COL_GRAY3	0x0A	/* 0A：灰色3			R:160,G:160,B:160	*/
#define		COL_GRAY4	0x0B	/* 0B：灰色4			R:128,G:128,B:128	*/
#define		COL_ORANGE	0x0C	/* 0C：ｵﾚﾝｼﾞ			R:255,G:128,B:000	*/	//V05o
#define		COL_YELGRN	0x0D	/* 0D：黄緑				R:128,G:255,B:000	*/	//V05o
#define		COL_YOBI3	0x0E	/* 0E：予備									*/
#define		COL_YOBI4	0x0F	/* 0F：予備									*/
#define		COL_EcoM0	0x30	/* 30：EcoMeter0							*/	//V06 
#define		COL_EcoM1	0x31	/* 31：EcoMeter1							*/	//V06 
#define		COL_EcoM2	0x32	/* 32：EcoMeter2							*/	//V06 
#define		COL_EcoM3	0x33	/* 33：EcoMeter3							*/	//V06 
#define		COL_EcoM4	0x34	/* 34：EcoMeter4							*/	//V06 
#define		COL_EcoM5	0x35	/* 35：EcoMeter5							*/	//V06 
#define		COL_EcoM6	0x36	/* 36：EcoMeter6							*/	//V06 
#define		COL_EcoM7	0x37	/* 37：EcoMeter7							*/	//V06 

