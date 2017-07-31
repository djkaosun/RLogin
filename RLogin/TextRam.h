// TextRam.h: CTextRam クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTRAM_H__CBEA227A_D7D7_4213_88B1_4F4C0DF48089__INCLUDED_)
#define AFX_TEXTRAM_H__CBEA227A_D7D7_4213_88B1_4F4C0DF48089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <afxmt.h>
#include "Data.h"
#include "IConv.h"
#include "TekWnd.h"
#include "GhostWnd.h"

#define	COLS_MAX		512
#define	LINE_MAX		512
#define	HIS_MAX			200000			// HIS_MAX * COLS_MAX * sizeof(CVram) = 1,638,400,000 byte
#define	DEF_TAB			8
#define	FKEY_MAX		24
#define	KANBUFMAX		128

#define	TEK_WIN_WIDTH	4096
#define	TEK_WIN_HEIGHT	3072

#define	EUC_SET			0
#define	SJIS_SET		1
#define	ASCII_SET		2
#define	UTF8_SET		3
#define	BIG5_SET		4

#define	LOGMOD_RAW		0
#define	LOGMOD_CTRL		1
#define	LOGMOD_CHAR		2
#define	LOGMOD_LINE		3

#define ATT_BOLD		0x0000001		// [1m bold or increased intensity
#define	ATT_HALF		0x0000002		// [2m faint, decreased intensity or second colour
#define ATT_ITALIC		0x0000004		// [3m italicized
#define ATT_UNDER		0x0000008		// [4m singly underlined
#define ATT_SBLINK		0x0000010		// [5m slowly blinking
#define ATT_REVS		0x0000020		// [7m negative image
#define ATT_SECRET		0x0000040		// [8m concealed characters
#define ATT_LINE		0x0000080		// [9m crossed-out
#define ATT_BLINK		0x0000100		// [6m rapidly blinking 
#define ATT_DUNDER		0x0000200		// [21m doubly underlined
#define ATT_FRAME		0x0000400		// [51m framed
#define ATT_CIRCLE		0x0000800		// [52m encircled
#define ATT_OVER		0x0001000		// [53m overlined
#define ATT_RSLINE		0x0002000		// [60m right side line
#define ATT_RDLINE		0x0004000		// [61m double line on the right side
#define ATT_LSLINE		0x0008000		// [62m left side line
#define ATT_LDLINE		0x0010000		// [63m double line on the left side
#define ATT_STRESS		0x0020000		// [64m stress marking
#define ATT_DOVER		0x0040000		// double over line
#define	ATT_MARK		0x0400000		// Search Mark
#define	ATT_CLIP		0x0800000		// Mouse Clip
#define	ATT_RTOL		0x1000000		// RtoL Char
#define	ATT_BORDER		0x2000000		// U+2500 Border Char
#define	ATT_BITS		0x8000000		// 7 * 4 = 28 bit

#define CODE_MAX		0x0400
#define CODE_MASK		0x03FF
#define SET_MASK		0x0300
#define SET_94			0x0000
#define SET_96			0x0100
#define SET_94x94		0x0200
#define SET_96x96		0x0300
#define	SET_UNICODE		0x03FF

#define	EM_ISOPROTECT	1
#define	EM_DECPROTECT	2

#define DM_SWSH			0
#define DM_DWSH			1
#define DM_DWDHT		2
#define DM_DWDHB		3

#define CM_ASCII		0
#define CM_1BYTE		1
#define CM_2BYTE		2
#define	CM_IMAGE		3

#define IS_ASCII(a) 	((a) == CM_ASCII)
#define IS_1BYTE(a) 	((a) == CM_1BYTE)
#define IS_2BYTE(a) 	((a) == CM_2BYTE)
#define IS_IMAGE(a)	 	((a) == CM_IMAGE)

// DEC Terminal Option	0-199
#define	TO_DECCKM		1			// Cursor key mode
#define	TO_DECANM		2			// ANSI/VT52 Mode
#define	TO_DECCOLM		3			// 80/132 Column mode
#define	TO_DECSCLM		4			// Scrolling mode
#define	TO_DECSCNM		5			// Light or Dark Screen
#define TO_DECOM		6			// Origin mode
#define TO_DECAWM		7			// Autowrap mode
#define	TO_XTMOSREP		9			// X10 mouse reporting
#define	TO_DECPEX		19			// Print Extent Mode
#define	TO_DECTCEM		25			// Text Cursor Enable Mode
#define	TO_DECTEK		38			// Graphics (Tek)
#define	TO_XTMCSC		40			// XTerm Column switch control
#define	TO_XTMCUS		41			// XTerm tab bug fix
#define TO_XTMRVW		45			// XTerm Reverse-wraparound mode
#define	TO_XTMABUF		47			// XTerm alternate buffer
#define	TO_DECBKM		67			// Backarrow key mode (BS)
#define	TO_DECLRMM		69			// Left Right Margin Mode
#define	TO_DECSDM		80			// Sixel Display Mode Control reset = Scroll mode Enable
#define	TO_DECNCSM		95			// Set/Reset No Clearing Screen On Column Change
#define	TO_DECECM		117			// SGR space color disable
// ANSI Screen Option	0-99(200-299)
#define	TO_ANSIKAM		(2+200)		// KAM Set Keyboard Action Mode
#define	TO_ANSIIRM		(4+200)		// IRM Insertion replacement mode
#define	TO_ANSIERM		(6+200)		// ERM Erasure mode
#define	TO_ANSISRM		(12+200)	// SRM Set Send/Receive mode (Local echo off)
#define	TO_ANSITSM		(18+200)	// ISM Tabulation stop mode
#define	TO_ANSILNM		(20+200)	// LNM Line feed/new line mode
// XTerm Option			1000-1079(300-379)
#define	TO_XTNOMTRK		(1000-700)	// X11 normal mouse tracking
#define	TO_XTHILTRK		(1001-700)	// X11 hilite mouse tracking
#define	TO_XTBEVTRK		(1002-700)	// X11 button-event mouse tracking
#define	TO_XTAEVTRK		(1003-700)	// X11 any-event mouse tracking
#define	TO_XTFOCEVT		(1004-700)	// Send Focus Event (CSI I / CSI O)
#define	TO_XTEXTMOS		(1005-700)	// Enable Extended Mouse Mode
#define	TO_XTSGRMOS		(1006-700)	// SGR Extended Mouse Mode
#define	TO_XTURXMOS		(1015-700)	// URXVT Extended Mouse Mode
#define	TO_XTALTSCR		(1047-700)	// Alternate/Normal screen buffer
#define	TO_XTSRCUR		(1048-700)	// Save/Restore cursor as in DECSC/DECRC
#define	TO_XTALTCLR		(1049-700)	// Alternate screen with clearing
// XTerm Option 2		2000-2019(380-399)
#define	TO_XTBRPAMD		(2004-1620)	// Bracketed Paste Mode
// RLogin Option		8400-8511(400-511)
#define	TO_RLGCWA		400			// ESC[m space att enable
#define	TO_RLGNDW		401			// 行末での遅延改行を無効にする
#define	TO_RLGAWL		402			// http;//で始まる文字列をコピーすると自動でブラウザを起動する
#define	TO_RLBOLD		403			// ボールド文字を有効にする
#define	TO_RLFONT		404			// フォントサイズから一行あたりの文字数を決定
#define	TO_RLBPLUS		405			// BPlus/ZModemファイル転送を有効にする
#define	TO_RLALTBDIS	406			// 拡張バッファを使用しない
#define	TO_RLADBELL		416			// ベルコード(07)による動作を選択 x1
#define	TO_RLVSBELL		417			// ベルコード(07)による動作を選択 1x
#define	TO_RLUNIAWH		428			// UnicodeのAタイプの文字を半角として表示する
#define	TO_RLSPCTAB		429			// 選択した文字列から連続したスペースをタブに変換する
#define	TO_RLNORESZ		435			// DECCOLMの文字数切換でウィンドウをリサイズする
#define	TO_RLKANAUTO	437			// 漢字コードを自動で追従する
#define	TO_RLMOSWHL		438			// マウスホイールをヌルヌル禁止
#define	TO_RLMSWAPP		439			// マウスホイールのCKMモード時カーソルキー動作を禁止
#define	TO_RLPNAM		440			// 0:Normal Keypad (DECPNM) / 1:Application Keypad (DECPAM)
#define	TO_IMECTRL		441			// IME Open/Close
#define	TO_RLCKMESC		442			// ESCキーをDECCKMに含める		7727  -  Application Escape mode を有効にする。 
#define	TO_RLMSWAPE		443			// ホイールのキー変換強制		7786  -  マウスホイール - カーソルキー変換を有効にする。
#define	TO_RLTEKINWND	446			// Tekウィンドウをビューで描く
#define	TO_RLOSCPAM		447			// OSC/DCS...キャンセル時にバッファを書き戻す
#define	TO_RLUNINOM		448			// Unicode ノーマライズを禁止する
#define	TO_RLUNIAHF		449			// Unicodeの半角時にサイズを調整する
#define	TO_RLMODKEY		450			// modfiyKeysを優先する
#define	TO_RLDRWLINE	451			// 罫線を線描画に置き換えない

// RLogin SockOpt		1000-1511(0-511)
#define	TO_RLTENAT		1406		// 自動ユーザー認証を行わない
#define	TO_RLTENEC		1407		// データの暗号化を禁止する
#define	TO_RLPOFF		1408		// 接続が切れると自動でプログラムを終了する
#define	TO_RLUSEPASS	1409		// 接続時にパスワード入力を求める
#define	TO_RLRCLICK		1410		// 右ダブルクリックだけでクリップボードからペーストする
#define	TO_RLCKCOPY		1411		// 左クリックの範囲指定だけでクリップボードにコピーする
#define	TO_RLDSECHO		1412		// キーボード入力をローカルエディットモードにする
#define	TO_RLDELAY		1413		// 改行(CR)を確認し指定時間待って次を送信する(ms)
#define	TO_RLHISFILE	1414		// ヒストリーを保存し次接続時に復元する
#define	TO_RLKEEPAL		1415		// TCPオプションのKeepAliveを有効にする
#define	TO_SSH1MODE		1420		// SSHバージョン１で接続する
#define	TO_SSHPFORY		1421		// ポートフォワードだけ行う （SSH2のみ）
#define	TO_SSHKEEPAL	1422		// KeepAliveパケットの送信間隔(sec)
#define	TO_SSHAGENT		1423		// エージェント転送を有効にする(SSH2のみ)
#define	TO_SSHSFENC		1424		// 暗号シャッフル
#define	TO_SSHSFMAC		1425		// 検証シャッフル
#define	TO_RLHISDATE	1430		// 通信ログを年月日を付けて自動作成する
#define	TO_RLLOGMODE	1431		// ファイルに保存する通信ログの形式を選択 x1
#define	TO_RLLOGMOD2	1432		// ファイルに保存する通信ログの形式を選択 1x
#define	TO_RLLOGCODE	1433		// ログの文字コードを選択(RAWモード以外で有効) x1
#define	TO_RLLOGCOD2	1434		// ログの文字コードを選択(RAWモード以外で有効) 1x
#define	TO_SSHX11PF		1436		// X11ポートフォワードを使用する
#define	TO_RLTENLM		1444		// TELNET LINEMODE を禁止する
#define	TO_RLSCRDEBUG	1445		// スクリプトデバックを行う
#define	TO_RLCURIMD		1452		// カーソルをIで表示
#define TO_RLRSPAST		1453		// 右クリックだけでクリップボードからペーストする
#define	TO_RLGWDIS		1454		// ゴーストウィンドウを表示しない
#define	TO_RLMWDIS		1455		// リサイズメッセージを表示しない	

#define	IS_ENABLE(p,n)	(p[(n) / 32] & (1 << ((n) % 32)))

#define	WTTL_ENTRY		0000		// m_EntryName
#define	WTTL_HOST		0001		// m_HostName
#define	WTTL_PORT		0002		// m_HostName:m_PotrtName
#define	WTTL_USER		0003		// m_UserName
#define	WTTL_ALGO		0010		// with status or algorithm
#define	WTTL_CHENG		0020		// OSC Title cheng disable
#define	WTTL_REPORT		0040		// XTWOP Title report disable

#define	ERM_ISOPRO		0001		// SPA,EPA,ERM	ED, EL, EF, EA
#define	ERM_DECPRO		0002		// DECSCA		DECSERA, DECSED, DECSEL
#define	ERM_SAVEDM		0004		// DECDHL...

#define	MOS_EVENT_NONE	0
#define	MOS_EVENT_X10	1			//    9 X10 mouse reporting
#define	MOS_EVENT_NORM	2			// 1000 X11 normal mouse tracking
#define	MOS_EVENT_HILT	3			// 1001 X11 hilite mouse tracking
#define	MOS_EVENT_BTNE	4			// 1002 X11 button-event mouse tracking
#define	MOS_EVENT_ANYE	5			// 1003 X11 any-event mouse tracking
#define	MOS_EVENT_LOCA	6			// DECLRP (Locator report)

#define	MOS_LOCA_INIT	0			//	Init Mode
#define	MOS_LOCA_LEDN	1			//	Left Down
#define	MOS_LOCA_LEUP	2			//	Left Up
#define	MOS_LOCA_RTDN	3			//	Right Down
#define	MOS_LOCA_RTUP	4			//	Right Up
#define	MOS_LOCA_MOVE	5			//	Mouse Move
#define	MOS_LOCA_REQ	6			//	Request

#define	LOC_MODE_ENABLE		0x0001
#define	LOC_MODE_ONESHOT	0x0002
#define	LOC_MODE_FILTER		0x0004
#define	LOC_MODE_PIXELS		0x0008
#define	LOC_MODE_EVENT		0x0010
#define	LOC_MODE_UP			0x0020
#define	LOC_MODE_DOWN		0x0040

#define	UTF16BE			0
#define	UTF16LE			1

#define	RESET_CURSOR	0x0001
#define	RESET_TABS		0x0002
#define	RESET_BANK		0x0004
#define	RESET_ATTR		0x0008
#define	RESET_COLOR		0x0010
#define	RESET_TEK		0x0020
#define	RESET_SAVE		0x0040
#define	RESET_MOUSE		0x0080
#define	RESET_CHAR		0x0100
#define	RESET_OPTION	0x0200
#define	RESET_CLS		0x0400
#define	RESET_ALL		0xFFFF

#define	RC_DCS			0
#define	RC_SOS			1
#define	RC_CSI			2
#define	RC_ST			3
#define	RC_OSC			4
#define	RC_PM			5
#define	RC_APC			6

#define	OSC52_READ		001
#define	OSC52_WRITE		002

#define	USFTWMAX		24
#define	USFTHMAX		36
#define	USFTLNSZ		((USFTHMAX + 5) / 6)
#define	USFTCHSZ		(USFTWMAX * USFTLNSZ)

#define	DELAY_NON		0
#define	DELAY_PAUSE		1
#define	DELAY_WAIT		2

#define	UNICODE_MAX		0x0010FFFF		// U+000000 - U+10FFFF 21 bit (サロゲート可能範囲)
#define	UNICODE_UNKOWN	0x000025A1		// □

#define	UNI_NAR			0x00000001		// 1 width char
#define	UNI_WID			0x00000002		// 2 width char
#define	UNI_AMB			0x00000004		// A type char 1 or 2 width
#define	UNI_NSM			0x00000008		// Non Spaceing Mark char
#define	UNI_IVS			0x00000010		// IVS Mark
#define	UNI_SGH			0x00000020		// サロゲート Hi
#define	UNI_SGL			0x00000040		// サロゲート Low
#define	UNI_CTL			0x00000080		// RtoL LtoR Control char
#define	UNI_HNF			0x00000100		// Hangle Fast
#define	UNI_HNM			0x00000200		// Hangle Mid
#define	UNI_HNL			0x00000400		// Hangle Last
#define	UNI_RTL			0x00000800		// Right to Left block

										// CSI > Ps T/t		xterm CASE_RM_TITLE/CASE_SM_TITLE option flag bits m_XtOptFlag
#define	XTOP_SETHEX		0x0001			//    Ps = 0  -> Set window/icon labels using hexadecimal.
#define	XTOP_GETHEX		0x0002			//    Ps = 1  -> Query window/icon labels using hexadecimal.
#define	XTOP_SETUTF		0x0004			//    Ps = 2  -> Set window/icon labels using UTF-8.
#define	XTOP_GETUTF		0x0008			//    Ps = 3  -> Query window/icon labels using UTF-8.

#define	MODKEY_ALLOW	0				//    how to handle legacy/vt220 keyboard
#define	MODKEY_CURSOR	1				//    how to handle cursor-key modifiers
#define	MODKEY_FUNC		2				//    how to handle function-key modifiers
#define	MODKEY_KEYPAD	3				//    how to handle keypad key-modifiers
#define	MODKEY_OTHER	4				//    how to handle other key-modifiers
#define	MODKEY_STRING	5				//    how to handle string() modifiers
#define	MODKEY_MAX		6

#define	EXTCOL_BEGIN			256
#define	EXTCOL_VT_TEXT_FORE		256				// 10  -> Change VT100 text foreground color to Pt.
#define	EXTCOL_VT_TEXT_BACK		257				// 11  -> Change VT100 text background color to Pt.
#define	EXTCOL_TEXT_CURSOR		258				// 12  -> Change text cursor color to Pt.
#define	EXTCOL_MOUSE_FORE		259				// 13  -> Change mouse foreground color to Pt.
#define	EXTCOL_MOUDE_BACK		260				// 14  -> Change mouse background color to Pt.
#define	EXTCOL_TEK_FORE			261				// 15  -> Change Tektronix foreground color to Pt.
#define	EXTCOL_TEK_BACK			262				// 16  -> Change Tektronix background color to Pt.
#define	EXTCOL_HILIGHT_BACK		263				// 17  -> Change highlight background color to Pt.
#define	EXTCOL_TEK_CURSOR		264				// 18  -> Change Tektronix cursor color to Pt.
#define	EXTCOL_HILIGHT_FORE		265				// 19  -> Change highlight foreground color to Pt.

#define	EXTCOL_SP_BEGIN			266
#define	EXTCOL_TEXT_BOLD		266				// 5;0 <- resource colorBD (BOLD).
#define	EXTCOL_TEXT_UNDER		267				// 5;1 <- resource colorUL (UNDERLINE).
#define	EXTCOL_TEXT_BLINK		268				// 5;2 <- resource colorBL (BLINK).
#define	EXTCOL_TEXT_REVERSE		269				// 5;3 <- resource colorRV (REVERSE).

#define	EXTCOL_MAX				270

#define issjis1(c)		(((unsigned char)(c) >= 0x81 && \
						  (unsigned char)(c) <= 0x9F) || \
						 ((unsigned char)(c) >= 0xE0 && \
						  (unsigned char)(c) <= 0xFC) )

#define issjis2(c)		(((unsigned char)(c) >= 0x40 && \
						  (unsigned char)(c) <= 0x7E) || \
						 ((unsigned char)(c) >= 0x80 && \
						  (unsigned char)(c) <= 0xFC) )

#define iskana(c)		((unsigned char)(c) >= 0xA0 && \
						 (unsigned char)(c) <= 0xDF)

#define isbig51(c)		(((unsigned char)(c) >= 0xA1 && \
						  (unsigned char)(c) <= 0xC6) || \
						 ((unsigned char)(c) >= 0xC9 && \
						  (unsigned char)(c) <= 0xF9) )

#define isbig52(c)		(((unsigned char)(c) >= 0x40 && \
						  (unsigned char)(c) <= 0x7E) || \
						 ((unsigned char)(c) >= 0xA1 && \
						  (unsigned char)(c) <= 0xFE) )

enum ETextRamStat {
		ST_ENDOF,		ST_NULL,
		ST_CONF_LEVEL,
		ST_COLM_SET,	ST_COLM_SET_2,
		ST_DEC_OPT,
		ST_DOCS_OPT,	ST_DOCS_OPT_2,
		ST_TEK_OPT,
		ST_CHARSET_1,	ST_CHARSET_2
};

enum ETabSetNum {
		TAB_COLSSET,	TAB_COLSCLR,	TAB_COLSALLCLR,	TAB_COLSALLCLRACT,
		TAB_LINESET,	TAB_LINECLR,	TAB_LINEALLCLR,
		TAB_RESET,
		TAB_DELINE,		TAB_INSLINE,
		TAB_ALLCLR,
		TAB_COLSNEXT,	TAB_COLSBACK,
		TAB_LINENEXT,	TAB_LINEBACK,
};

enum EStageNum {
		STAGE_ESC = 0,	STAGE_CSI,		STAGE_EXT1,		STAGE_EXT2,		STAGE_EXT3,		// Use 0,1,2,3,4 !!! Look up fc_Case()
		STAGE_EXT4,		STAGE_EUC,
		STAGE_94X94,	STAGE_96X96,
		STAGE_SJIS,		STAGE_SJIS2,
		STAGE_BIG5,		STAGE_BIG52,
		STAGE_UTF8,		STAGE_UTF82,
		STAGE_OSC1,		STAGE_OSC2,
		STAGE_TEK,
		STAGE_STAT,		STAGE_GOTOXY,
		STAGE_MAX,
};

typedef struct _Vram {
	union {
		DWORD	ch;
		struct {
			DWORD	id:12;		// イメージ番号
			  DWORD	iy:10;		// イメージ横位置
			  DWORD	ix:10;		// イメージ縦位置
		} im;
		WCHAR	cb[2];
	} pk;

	DWORD	at:28;		// アトリビュート
	  DWORD	ft:4;		// フォント番号

	WORD	md:10;		// フォントバンク
	  WORD	em:2;		// 消去属性
	  WORD	dm:2;		// 拡大属性
	  WORD	cm:2;		// 文字種
	BYTE	fc;			// 文字色番号
	BYTE	bc;			// 背景色番号
} VRAM;

//#define	FIXWCHAR	1

#ifdef	FIXWCHAR
#define	MAXCHARSIZE	10
#else
#define	MAXCHARSIZE	31
WCHAR *WCharAlloc(int len);
void WCharFree(WCHAR *ptr);
int WCharSize(WCHAR *ptr);
void AllWCharAllocFree();
#endif

class CVram
{
public:
#ifdef	FIXWCHAR
	WCHAR		ch[MAXCHARSIZE];
#else
	WCHAR		*ch;
#endif
	VRAM		pr;

	inline CVram();
	inline ~CVram();

	inline void Empty() { if ( !IS_IMAGE(pr.cm) ) ch[0] = 0; }
	inline BOOL IsEmpty() { return (IS_IMAGE(pr.cm) || ch[0] == 0 ? TRUE : FALSE); }
	inline operator LPCWSTR () { return (IS_IMAGE(pr.cm) ? L"" : ch); }
	inline operator DWORD () { return ((ch[0] == 0 ? 0 : (ch[1] == 0 ? ch[0] : ((ch[0] << 16) | ch[1])))); }
	inline const CVram & operator = (CVram &data);
	inline void operator = (VRAM &ram);
//	inline int Compare(LPCWSTR str) { return wcscmp(str, (LPCWSTR)*this); }
	inline int Compare(LPCWSTR str) { return 0; }

	inline void operator = (DWORD c);
	void operator = (LPCWSTR str);
	void operator += (DWORD c);
	void SetVRAM(VRAM &ram);

	void SetBuffer(CBuffer &buf);
	void GetBuffer(CBuffer &buf);
	void SetString(CString &str);
	void GetString(LPCTSTR str);

	void Read(CFile &file, int ver = 3);
	void Write(CFile &file);
};

class CFontNode : public CObject
{
public:
	BYTE m_Shift;
	int m_ZoomW;
	int m_ZoomH;
	int m_OffsetW;
	int m_OffsetH;
	int m_CharSet;
	CString m_FontName[16];
	CString m_EntryName;
	CString m_IContName;
	CString m_IndexName;
	int m_Hash[16];
	int m_Quality;
	BOOL m_Init;
	int m_UserFontWidth;
	int m_UserFontHeight;
	CBitmap m_UserFontMap;
	BYTE m_UserFontDef[96 / 8];
	int m_FontWidth;
	int m_FontHeight;
	CBitmap m_FontMap;

	void SetHash(int num);
	void Init();
	void SetArray(CStringArrayExt &stra);
	void GetArray(CStringArrayExt &stra);
	CFontChacheNode *GetFont(int Width, int Height, int Style, int FontNum);
	const CFontNode & operator = (CFontNode &data);
	void SetUserBitmap(int code, int width, int height, CBitmap *pMap, int ofx, int ofy);
	void SetUserFont(int code, int width, int height, LPBYTE map);
	BOOL SetFontImage(int width, int height);

	CFontNode();
	~CFontNode();
};

class CFontTab : public COptObject
{
public:
	CFontNode m_Data[CODE_MAX];

	void Init();
	void SetArray(CStringArrayExt &stra);
	void GetArray(CStringArrayExt &stra);
	void SetIndex(int mode, CStringIndex &index);

	int Find(LPCTSTR entry);
	int IndexFind(int code, LPCTSTR name);
	void IndexRemove(int idx);
	inline CFontNode & operator[](int nIndex) { return m_Data[nIndex]; }
	const CFontTab & operator = (CFontTab &data);
	CFontTab();
};

#define	PROCTYPE_ESC	0
#define	PROCTYPE_CSI	1
#define	PROCTYPE_DCS	2

class CProcNode : public CObject
{
public:
	int		m_Type;
	int		m_Code;
	CString	m_Name;

	const CProcNode & operator = (CProcNode &data);
	CProcNode();
};

class CProcTab : public COptObject
{
public:
	CArray<CProcNode, CProcNode &> m_Data;

	void Add(int type, int code, LPCTSTR name);
	inline void RemoveAll() { m_Data.RemoveAll(); }
	inline int GetSize() { return m_Data.GetSize(); }
	inline CProcNode & operator[](int nIndex) { return m_Data[nIndex]; }

	void Init();
	void SetIndex(int mode, CStringIndex &index);
	void SetArray(CStringArrayExt &stra);
	void GetArray(CStringArrayExt &stra);

	const CProcTab & operator = (CProcTab &data);
	CProcTab();
};

class CTextSave : public CObject
{
public:
	class CTextSave *m_Next;

	CVram *m_VRam;
	VRAM m_AttNow;
	VRAM m_AttSpc;

	int m_Cols;
	int m_Lines;
	int m_CurX;
	int m_CurY;
	int m_TopY;
	int m_BtmY;
	int m_LeftX;
	int m_RightX;

	int m_DoWarp;
	DWORD m_AnsiOpt[16];

	int m_BankGL;
	int m_BankGR;
	int m_BankSG;
	WORD m_BankTab[5][4];

	BYTE m_TabMap[LINE_MAX + 1][COLS_MAX / 8 + 1];

	VRAM m_Save_AttNow;
	VRAM m_Save_AttSpc;

	int m_Save_CurX;
	int m_Save_CurY;

	BOOL m_Save_DoWarp;
	BOOL m_Save_Decom;
	DWORD m_Save_AnsiOpt[16];

	int m_Save_BankGL;
	int m_Save_BankGR;
	int m_Save_BankSG;
	WORD m_Save_BankTab[5][4];

	BYTE m_Save_TabMap[LINE_MAX + 1][COLS_MAX / 8 + 1];
};

class CTextRam : public COptObject
{
public:	// Options
	COLORREF m_DefColTab[16];
	CString m_SendCharSet[5];
	DWORD m_DefAnsiOpt[16];
	int m_DefCols[2];
	int m_DefHisMax;
	int m_DefFontSize;
	int m_DefFontHw;
	VRAM m_DefAtt;
	int m_KanjiMode;
	int m_BankGL;
	int m_BankGR;
	WORD m_DefBankTab[5][4];
	int m_WheelSize;
	CString m_BitMapFile;
	int m_DelayMSec;
	CString m_HisFile;
	int m_KeepAliveSec;
	CString m_LogFile;
	int m_DropFileMode;
	CString m_DropFileCmd[8];
	CString m_WordStr;
	int m_MouseTrack;
	BYTE m_MouseMode[4];
	CRect m_MouseRect;
	int m_MouseOldSw;
	CPoint m_MouseOldPos;
	DWORD m_MetaKeys[256 / 32];
	CProcTab m_ProcTab;
	CBuffer m_FuncKey[FKEY_MAX];
	int m_ClipFlag;
	CStringArrayExt m_ShellExec;
	int m_DefModKey[MODKEY_MAX];
	CRect m_ScrnOffset;

	void Init();
	void SetIndex(int mode, CStringIndex &index);
	void SetArray(CStringArrayExt &stra);
	void GetArray(CStringArrayExt &stra);
	void ScriptInit(int cmds, int shift, class CScriptValue &value);
	void ScriptTable(const struct _ScriptCmdsDefs *defs, class CScriptValue &value, int mode);
	void ScriptValue(int cmds, class CScriptValue &value, int mode);
	void Serialize(int mode);
	void Serialize(int mode, CBuffer &buf);
	void Serialize(CArchive& ar);
	const CTextRam & operator = (CTextRam &data);

public:
	class CRLoginDoc *m_pDocument;
	class CFontTab m_FontTab;

	BOOL m_bOpen;
	CVram *m_VRam;
	VRAM m_AttSpc;
	VRAM m_AttNow;

	int m_Cols;
	int m_Lines;
	int m_CurX;
	int m_CurY;
	int m_TopY;
	int m_BtmY;
	int m_LeftX;
	int m_RightX;
	int m_DefTab;
	COLORREF m_ColTab[EXTCOL_MAX];
	DWORD m_AnsiOpt[16];
	DWORD m_OptTab[16];
	int m_ModKey[MODKEY_MAX];
	CString m_ModKeyList[MODKEY_MAX];
	char m_ModKeyTab[256];

	int m_ColsMax;
	int m_LineUpdate;

	int m_HisMax;
	int m_HisPos;
	int m_HisLen;
	int m_HisUse;
	CFile m_HisFhd;

	int m_DispCaret;
	int m_TypeCaret;
	BOOL m_DoWarp;
	int m_Status;
	int m_RecvCrLf;
	int m_SendCrLf;

	DWORD m_BackChar;
	int m_BackMode;
	DWORD m_LastChar;
	int m_LastFlag;
	int m_LastPos;
	BOOL m_bRtoL;

	CParaIndex m_AnsiPara;
	int m_OscMode;
	CBuffer m_OscPara;
	BYTE m_TabMap[LINE_MAX + 1][COLS_MAX / 8 + 1];
	BOOL m_RetSync;
	BOOL m_Exact;
	CString m_StrPara;
	DWORD m_MacroExecFlag[64 / 32];
	CBuffer m_Macro[64];
	DWORD m_UnitId;

	int m_VtLevel;
	int m_TermId;
	BOOL m_StsFlag;
	int m_StsMode;
	int m_StsLed;
	CStringW m_StsPara;
	int m_LangMenu;
	LPCTSTR m_RetChar[7];
	int m_ImageIndex;
	int m_bOscActive;
	LPCTSTR m_OscName;
	class CCancelDlg *m_pCanDlg;
	BOOL m_bIntTimer;
	int m_IntCounter;

	WORD m_BankTab[5][4];
	int m_BankNow;
	int m_BankSG;
	int m_CodeLen;

	VRAM m_Save_AttNow;
	VRAM m_Save_AttSpc;
	int m_Save_CurX;
	int m_Save_CurY;
	DWORD m_Save_AnsiOpt[16];
	int m_Save_BankGL;
	int m_Save_BankGR;
	int m_Save_BankSG;
	BOOL m_Save_DoWarp;
	BOOL m_Save_Decom;
	WORD m_Save_BankTab[5][4];
	BYTE m_Save_TabMap[LINE_MAX + 1][COLS_MAX / 8 + 1];

	int m_Page;
	CPtrArray m_PageTab;

	CTextSave *m_pTextSave;
	CTextSave *m_pTextStack;
	CIConv m_IConv;
	CRect m_UpdateRect;
	BOOL m_UpdateFlag;
	BOOL m_FrameCheck;

	BOOL m_LineEditMode;
	int m_LineEditIndex;
	int m_LineEditX, m_LineEditY;
	int m_LineEditPos;
	CBuffer m_LineEditBuff;
	int m_LineEditHisPos;
	CSpace m_LineEditNow;
	CArray<CSpace, CSpace &> m_LineEditHis;
	int m_LineEditMapsPos;
	int m_LineEditMapsTop;
	CStringW m_LineEditMapsDir;
	CStringW m_LineEditMapsStr;
	int m_LineEditMapsInit;
	int m_LineEditMapsIndex;
	CStringMaps m_LineEditMapsTab[3];
	int m_LogCharSet[4];
	int m_TitleMode;
	BOOL m_FileSaveFlag;
	DWORD m_XtOptFlag;
	CStringArray m_TitleStack;
	CRect m_Margin;
	
	// Window Fonction
	BOOL IsInitText() { return (m_bOpen && m_VRam != NULL ? TRUE : FALSE); }
	void InitText(int Width, int Height);
	void InitScreen(int cols, int lines);
	int Write(LPBYTE lpBuf, int nBufLen, BOOL *sync);
	void OnTimer(int id);

	int LineEdit(CBuffer &buf);
	void LineEditEcho();
	void LineEditCwd(int sx, int sy, CStringW &cwd);
	void SetKanjiMode(int mode);

	BOOL OpenHisFile();
	void InitHistory();
	void SaveHistory();

	CRegEx m_MarkReg;
	int m_MarkPos;
	int m_MarkLen;
	BOOL m_MarkEol;

	void HisRegCheck(int ch, DWORD pos);
	int HisRegMark(LPCTSTR str);
	int HisRegNext();
	int HisMarkCheck(int top, int line, class CRLoginView *pView);

	struct DrawWork {
		int		att;
		int		fcn, bcn;
		int		mod, fnm;
		int		dmf, csz;
		int		idx, stx, edx, sty;
	};

	int IsWord(int ch);
	int GetPos(int x, int y);
	BOOL IncPos(int &x, int &y);
	BOOL DecPos(int &x, int &y);
	void EditWordPos(int *sps, int *eps);
	void EditCopy(int sps, int eps, BOOL rectflag = FALSE, BOOL lineflag = FALSE);
	void GetVram(int staX, int endX, int staY, int endY, CBuffer *pBuf);
	void LineOut(CDC *pDC, CRect &box, COLORREF fc, COLORREF bc, int rv, struct DrawWork &prop, int len, LPCWSTR str, int *spc, class CRLoginView *pView);
	void StrOut(CDC *pDC, CDC *pWdc, LPCRECT pRect, struct DrawWork &prop, int len, LPCWSTR str, int *spc, class CRLoginView *pView);
	void DrawVram(CDC *pDC, int x1, int y1, int x2, int y2, class CRLoginView *pView);

	CWnd *GetAciveView();
	void PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

	BOOL IsOptEnable(int opt);
	void EnableOption(int opt);
	void DisableOption(int opt);
	void ReversOption(int opt);
	int IsOptValue(int opt, int len);
	void SetOptValue(int opt, int len, int value);
	inline void SetOption(int opt, BOOL sw) { if ( sw ) EnableOption(opt); else DisableOption(opt); }
	void InitDefParam(BOOL bCheck, int modFlag = (-1));
	void InitModKeyTab();

	inline int GetCalcPos(int x, int y) { return (m_ColsMax * (y + m_HisPos + m_HisMax) + x); }
	inline void SetCalcPos(int pos, int *x, int *y) { *x = pos % m_ColsMax; *y = (pos / m_ColsMax - m_HisPos - m_HisMax); }
	inline int GetDm(int y) { CVram *vp = GETVRAM(0, y); return vp->pr.dm; }
	inline void SetDm(int y, int dm) { CVram *vp = GETVRAM(0, y); vp->pr.dm = dm; }

	inline int GetLeftMargin() { return (IsOptEnable(TO_DECLRMM) ? m_LeftX : 0); }
	inline int GetRightMargin() { return (IsOptEnable(TO_DECLRMM) ? m_RightX : m_Cols); }
	inline int GetTopMargin() { return m_TopY; }
	inline int GetBottomMargin() { return m_BtmY; }

#define	MARCHK_NONE		0
#define	MARCHK_COLS		1
#define	MARCHK_LINES	2
#define	MARCHK_BOTH		3
	BOOL GetMargin(int bCheck = MARCHK_NONE);

	void OnClose();
	void CallReciveLine(int y);
	void CallReciveChar(int ch);
	int UnicodeCharFlag(DWORD code);
	int UnicodeWidth(DWORD code);
	void SetRetChar(BOOL f8);

	// Static Lib
	static void CTextRam::MsToIconvUniStr(LPCTSTR charset, LPWSTR str, int len);
	static DWORD CTextRam::IconvToMsUnicode(DWORD code);
	static DWORD UCS2toUCS4(DWORD code);
	static DWORD UCS4toUCS2(DWORD code);
	static DWORD CTextRam::UnicodeNomal(DWORD code1, DWORD code2);
	static void CTextRam::IconvToMsUniStr(LPCWSTR p, int len, CBuffer &out);

	// Low Level
	void RESET(int mode = RESET_CURSOR | RESET_TABS | RESET_BANK | RESET_ATTR | RESET_COLOR | RESET_TEK | RESET_SAVE | RESET_MOUSE | RESET_CHAR);

	CVram *GETVRAM(int cols, int lines);
	void UNGETSTR(LPCTSTR str, ...);
	void BEEP();
	void FLUSH();
	void CUROFF();
	void CURON();
	void DISPVRAM(int sx, int sy, int w, int h);
	void DISPUPDATE();
	void DISPRECT(int sx, int sy, int ex, int ey);
	int BLINKUPDATE(class CRLoginView *pView);
	int GETCOLIDX(int red, int green, int blue);

	// Mid Level
	int GetAnsiPara(int index, int defvalue, int minvalue, int maxvalue = -1);
	void SetAnsiParaArea(int top);
	LPCTSTR GetHexPara(LPCTSTR str, CBuffer &buf);
	void LOCATE(int x, int y);
	void ERABOX(int sx, int sy, int ex, int ey, int df = 0);
	void FORSCROLL(int sx, int sy, int ex, int ey);
	void BAKSCROLL(int sx, int sy, int ex, int ey);
	void LEFTSCROLL();
	void RIGHTSCROLL();
	void DOWARP();
	void INSCHAR(BOOL bMargin = TRUE);
	void DELCHAR();
	void ONEINDEX();
	void REVINDEX();
	void PUT1BYTE(int ch, int md, int at = 0);
	void PUT2BYTE(int ch, int md, int at = 0);
	void PUTADD(int x, int y, int ch, int cf);
	void INSMDCK(int len);
	void ANSIOPT(int opt, int bit);
	void SAVERAM();
	void LOADRAM();
	void PUSHRAM();
	void POPRAM();
	void SETPAGE(int page);
	CTextSave *GETPAGE(int page);
	void COPY(int sp, int sx, int sy, int ex, int ey, int dp, int dx, int dy);
	void TABSET(int sw);
	void PUTSTR(LPBYTE lpBuf, int nBufLen);

	CTextRam();
	virtual ~CTextRam();

	typedef struct _PROCTAB {
		BYTE	sc, ec;
		void (CTextRam::*proc)(int ch);
	} PROCTAB;

	typedef struct _CSIEXTTAB {
		int		code;
		void (CTextRam::*proc)(int ch);
	} CSIEXTTAB;

	typedef struct _ESCNAMEPROC {
		LPCTSTR		name;
		union {
			void (CTextRam::*proc)(int ch);
			BYTE byte[sizeof(void (CTextRam::*)(int))];
		} data;
		struct _ESCNAMEPROC	*left;
		struct _ESCNAMEPROC	*right;
	} ESCNAMEPROC;

	void ((CTextRam::**m_Func)(int ch));
	int m_Stage;
	int m_StPos;
	int m_Stack[16];
	void (CTextRam::*m_LocalProc[5][256])(int ch);
	CArray<CTextRam::CSIEXTTAB, CTextRam::CSIEXTTAB &> m_CsiExt;
	CArray<CTextRam::CSIEXTTAB, CTextRam::CSIEXTTAB &> m_DcsExt;

	void fc_Init_Proc(int stage, const PROCTAB *tp, int b = 0);
	ESCNAMEPROC *fc_InitProcName(CTextRam::ESCNAMEPROC *tab, int *max);
	void fc_Init(int mode);
	void fc_TraceCall(int ch);
	inline void fc_Call(int ch);
	inline void fc_Case(int stage);
	inline void fc_Push(int stage);

	void EscNameProc(int ch, LPCTSTR name);
	LPCTSTR EscProcName(void (CTextRam::*proc)(int ch));
	void SetEscNameCombo(CComboBox *pCombo);

	void CsiNameProc(int code, LPCTSTR name);
	LPCTSTR CsiProcName(void (CTextRam::*proc)(int ch));
	void SetCsiNameCombo(CComboBox *pCombo);

	void DcsNameProc(int code, LPCTSTR name);
	LPCTSTR DcsProcName(void (CTextRam::*proc)(int ch));
	void SetDcsNameCombo(CComboBox *pCombo);

	void EscCsiDefName(LPCTSTR *esc, LPCTSTR *csi, LPCTSTR *dcs);
	void ParseColor(int cmd, int idx, LPCTSTR para, int ch);

	int m_Kan_Pos;
	BYTE m_Kan_Buf[KANBUFMAX];
	
	void fc_KANCHK();
	inline void fc_KANJI(int ch) { if ( ch >= 128 || m_Kan_Buf[(m_Kan_Pos - 1) & (KANBUFMAX - 1)] >= 128 ) { m_Kan_Buf[m_Kan_Pos++] = ch; m_Kan_Pos &= (KANBUFMAX - 1); } }

	// Print...
	void fc_IGNORE(int ch);
	void fc_POP(int ch);
	void fc_RETRY(int ch);
	void fc_TEXT(int ch);
	void fc_TEXT2(int ch);
	void fc_TEXT3(int ch);
	void fc_SJIS1(int ch);
	void fc_SJIS2(int ch);
	void fc_SJIS3(int ch);
	void fc_BIG51(int ch);
	void fc_BIG52(int ch);
	void fc_BIG53(int ch);
	void fc_UTF81(int ch);
	void fc_UTF82(int ch);
	void fc_UTF83(int ch);
	void fc_UTF84(int ch);
	void fc_UTF85(int ch);
	void fc_UTF86(int ch);
	void fc_UTF87(int ch);
	void fc_UTF88(int ch);
	void fc_UTF89(int ch);
	void fc_SESC(int ch);
	void fc_CESC(int ch);
	void fc_STAT(int ch);
	void fc_GOTOXY(int ch);

	// Ctrl...
	void fc_SOH(int ch);
	void fc_ENQ(int ch);
	void fc_BEL(int ch);
	void fc_BS(int ch);
	void fc_HT(int ch);
	void fc_LF(int ch);
	void fc_VT(int ch);
	void fc_FF(int ch);
	void fc_CR(int ch);
	void fc_SO(int ch);
	void fc_SI(int ch);
	void fc_DLE(int ch);
	void fc_CAN(int ch);
	void fc_ESC(int ch);
	void fc_A3CUP(int ch);
	void fc_A3CDW(int ch);
	void fc_A3CLT(int ch);
	void fc_A3CRT(int ch);

	// ESC...
	void fc_DECHTS(int ch);
	void fc_DECAHT(int ch);
	void fc_DECVTS(int ch);
	void fc_DECAVT(int ch);
	void fc_BI(int ch);
	void fc_SC(int ch);
	void fc_RC(int ch);
	void fc_FI(int ch);
	void fc_V5CUP(int ch);
	void fc_BPH(int ch);
	void fc_NBH(int ch);
	void fc_IND(int ch);
	void fc_NEL(int ch);
	void fc_SSA(int ch);
	void fc_ESA(int ch);
	void fc_HTS(int ch);
	void fc_HTJ(int ch);
	void fc_VTS(int ch);
	void fc_PLD(int ch);
	void fc_PLU(int ch);
	void fc_RI(int ch);
	void fc_STS(int ch);
	void fc_CCH(int ch);
	void fc_MW(int ch);
	void fc_SPA(int ch);
	void fc_EPA(int ch);
	void fc_SCI(int ch);
	void fc_RIS(int ch);
	void fc_LMA(int ch);
	void fc_USR(int ch);
	void fc_V5EX(int ch);
	void fc_DECPAM(int ch);
	void fc_DECPNM(int ch);
	void fc_SS2(int ch);
	void fc_SS3(int ch);
	void fc_LS2(int ch);
	void fc_LS3(int ch);
	void fc_LS1R(int ch);
	void fc_LS2R(int ch);
	void fc_LS3R(int ch);
	void fc_CSC0W(int ch);
	void fc_CSC0(int ch);
	void fc_CSC1(int ch);
	void fc_CSC2(int ch);
	void fc_CSC3(int ch);
	void fc_CSC0A(int ch);
	void fc_CSC1A(int ch);
	void fc_CSC2A(int ch);
	void fc_CSC3A(int ch);
	void fc_V5MCP(int ch);
	void fc_DECSOP(int ch);
	void fc_ACS(int ch);
	void fc_ESCI(int ch);
	void fc_DOCS(int ch);

	// ESC [ CSI
	void fc_CSI(int ch);
	void fc_CSI_ESC(int ch);
	void fc_CSI_DIGIT(int ch);
	void fc_CSI_PUSH(int ch);
	void fc_CSI_SEPA(int ch);
	void fc_CSI_EXT(int ch);
	void fc_CSI_ETC(int ch);

	// CSI @-Z
	void fc_ICH(int ch);
	void fc_CUU(int ch);
	void fc_CUD(int ch);
	void fc_CUF(int ch);
	void fc_CUB(int ch);
	void fc_CNL(int ch);
	void fc_CPL(int ch);
	void fc_CHA(int ch);
	void fc_CUP(int ch);
	void fc_CHT(int ch);
	void fc_ED(int ch);
	void fc_EL(int ch);
	void fc_IL(int ch);
	void fc_DL(int ch);
	void fc_EF(int ch);
	void fc_EA(int ch);
	void fc_DCH(int ch);
	void fc_SEE(int ch);
	void fc_SU(int ch);
	void fc_SD(int ch);
	void fc_NP(int ch);
	void fc_PP(int ch);
	void fc_CTC(int ch);
	void fc_ECH(int ch);
	void fc_CVT(int ch);
	void fc_CBT(int ch);
	// CSI a-z
	void fc_HPR(int ch);
	void fc_REP(int ch);
	void fc_DA1(int ch);
	void fc_VPA(int ch);
	void fc_VPR(int ch);
	void fc_HVP(int ch);
	void fc_TBC(int ch);
	void fc_SM(int ch);
	void fc_RM(int ch);
	void fc_MC(int ch);
	void fc_HPB(int ch);
	void fc_VPB(int ch);
	void fc_SGR(int ch);
	void fc_DSR(int ch);
	void fc_DAQ(int ch);
	void fc_ORGBFAT(int ch);
	void fc_DECSSL(int ch);	
	void fc_DECLL(int ch);
	void fc_DECSTBM(int ch);
	void fc_DECSLRM(int ch);
	void fc_DECSLPP(int ch);
	void fc_DECSHTS(int ch);
	void fc_DECSVTS(int ch);
	void fc_SCOSC(int ch);
	void fc_XTWOP(int ch);
	void fc_SCORC(int ch);
	void fc_ORGSCD(int ch);
	void fc_REQTPARM(int ch);
	void fc_DECTST(int ch);
	void fc_DECVERP(int ch);
	void fc_SRS(int ch);
	void fc_PTX(int ch);
	void fc_SDS(int ch);
	void fc_SIMD(int ch);
	void fc_HPA(int ch);
	void fc_LINUX(int ch);
	void fc_DECFNK(int ch);
	// CSI ? ...
	void fc_DECSED(int ch);
	void fc_DECSEL(int ch);
	void fc_DECST8C(int ch);
	void fc_DECSET(int ch);
	void fc_DECMC(int ch);
	void fc_DECRST(int ch);
	void fc_XTREST(int ch);
	void fc_XTSAVE(int ch);
	void fc_DECDSR(int ch);
	void fc_DECSRET(int ch);
	// CSI $ ...
	void fc_DECRQM(int ch);
	void fc_DECCARA(int ch);
	void fc_DECRARA(int ch);
	void fc_DECRQTSR(int ch);
	void fc_DECCRA(int ch);
	void fc_DECRQPSR(int ch);
	void fc_DECFRA(int ch);
	void fc_DECERA(int ch);
	void fc_DECSERA(int ch);
	void fc_DECSCPP(int ch);
	void fc_DECSASD(int ch);
	void fc_DECSSDT(int ch);
	// CSI ...
	void fc_DECRQMH(int ch);
	void fc_SL(int ch);
	void fc_SR(int ch);
	void fc_FNT(int ch);
	void fc_PPA(int ch);
	void fc_PPR(int ch);
	void fc_PPB(int ch);
	void fc_DECSCUSR(int ch);
	void fc_DECTME(int ch);
	void fc_DECSTR(int ch);
	void fc_DECSCL(int ch);
	void fc_DECSCA(int ch);
	void fc_DECRQDE(int ch);
	void fc_DECRQUPSS(int ch);
	void fc_DECEFR(int ch);
	void fc_DECELR(int ch);
	void fc_DECSLE(int ch);
	void fc_DECRQLP(int ch);
	void fc_DECIC(int ch);
	void fc_DECDC(int ch);
	void fc_DECPS(int ch);
	void fc_DECSTGLT(int ch);
	void fc_DECSACE(int ch);
	void fc_DECRQCRA(int ch);
	void fc_DECINVM(int ch);
	void fc_DECSR(int ch);
	void fc_DECPQPLFM(int ch);
	void fc_DECAC(int ch);
	void fc_DECTID(int ch);
	void fc_DECATC(int ch);
	void fc_DA2(int ch);
	void fc_DA3(int ch);
	void fc_C25LCT(int ch);
	void fc_TTIMESV(int ch);
	void fc_TTIMEST(int ch);
	void fc_TTIMERS(int ch);
	void fc_XTRMTT(int ch);
	void fc_XTMDKEY(int ch);
	void fc_XTMDKYD(int ch);
	void fc_XTHDPT(int ch);
	void fc_XTSMTT(int ch);

	// ESC PX^_] DCS/PM/APC/SOS/OSC
	void fc_TimerSet(LPCTSTR name);
	void fc_TimerReset();
	void fc_TimerAbort(BOOL bOut);
	void fc_DCS(int ch);
	void fc_PM(int ch);
	void fc_APC(int ch);
	void fc_SOS(int ch);
	void fc_OSC(int ch);
	void fc_OSC_CMD(int ch);
	void fc_OSC_PAM(int ch);
	void fc_OSC_ST(int ch);
	void fc_DECUDK(int ch);
	void fc_DECREGIS(int ch);
	void fc_DECSIXEL(int ch);
	void fc_DECDLD(int ch);
	void fc_DECRSTS(int ch);
	void fc_DECRQSS(int ch);
	void fc_DECRSPS(int ch);
	void fc_DECDMAC(int ch);
	void fc_DECSTUI(int ch);
	void fc_XTRQCAP(int ch);
	void fc_OSCEXE(int ch);
	void fc_OSCNULL(int ch);

	// TEK
	typedef struct _TEKNODE {
		struct _TEKNODE *next;
		BYTE md, st, rv[2];
		short sx, sy, ex, ey;
		int ch;
	} TEKNODE;

	int m_Tek_Ver;
	int m_Tek_Mode;
	int m_Tek_Stat;
	int m_Tek_Pen;
	BOOL m_Tek_Gin;
	int m_Tek_Line;
	int m_Tek_Font;
	int m_Tek_Point;
	int m_Tek_Angle;
	int m_Tek_Base;
	int m_Tek_cX, m_Tek_cY;
	int m_Tek_lX, m_Tek_lY;
	int m_Tek_wX, m_Tek_wY;
	int m_Tek_Int;
	int m_Tek_Pos;
	BOOL m_Tek_Flush;
	TEKNODE *m_Tek_Top;
	TEKNODE *m_Tek_Free;
	class CTekWnd *m_pTekWnd;

	inline BOOL IsTekMode() { return (m_Stage == STAGE_TEK ? TRUE : FALSE); }
	void TekInit(int ver);
	void TekClose();
	void TekForcus(BOOL fg);
	void TekFlush();
	void TekDraw(CDC *pDC, CRect &frame);
	void TekClear(BOOL bFlush = TRUE);
	void TekLine(int st, int sx, int sy, int ex, int ey);
	void TekText(int st, int sx, int sy, int ch);
	void TekMark(int st, int no, int sx, int sy);
	void TekEdge(int ag);

	void fc_TEK_IN(int ch);
	void fc_TEK_LEFT(int ch);
	void fc_TEK_RIGHT(int ch);
	void fc_TEK_DOWN(int ch);
	void fc_TEK_UP(int ch);
	void fc_TEK_FLUSH(int ch);
	void fc_TEK_MODE(int ch);
	void fc_TEK_STAT(int ch);

	// DEC Locator
	int m_Loc_Mode;
	CRect m_Loc_Rect;
	int m_Loc_Pb;
	int m_Loc_LastX;
	int m_Loc_LastY;

	void LocReport(int md, int sw, int x, int y);
	void MouseReport(int md, int sw, int x, int y);

	CPtrArray m_GrapWndTab;

	class CGrapWnd *GetGrapWnd(int index);
	void AddGrapWnd(void *pWnd);
	void RemoveGrapWnd(void *pWnd);
	void *LastGrapWnd(int type);
};

#endif // !defined(AFX_TEXTRAM_H__CBEA227A_D7D7_4213_88B1_4F4C0DF48089__INCLUDED_)
