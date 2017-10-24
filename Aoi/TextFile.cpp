// ヘッダのインクルード
// 既定のヘッダ
#include <cstring>	// C文字列処理.
#include <wchar.h>	// ワイド文字.
// 独自のヘッダ
#include "TextFile.h"	// CTextFile

// コンストラクタCTextFile
CTextFile::CTextFile() : CBinaryFile(){

	// メンバの初期化
	m_ptszRawText = NULL;	// m_ptszRawTextにNULLをセット.
	m_dwLen = 0;	// m_dwLenに0をセット.
	m_NewLine = NEW_LINE_NONE;	// m_NewLineにNEW_LINE_NONEをセット.
	m_BOMType = BOM_NONE;	// BOM_NONE.
	m_Encoding = ENCODING_NONE;	// ENCODING_NONE.
	m_tstrText.clear();	// クリア.

}

// デストラクタCTextFile
CTextFile::~CTextFile() {

	// ファイルとバッファをクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

}

// メンバ関数Read
BOOL CTextFile::Read(LPCTSTR lpctszFileName) {

	// ファイルをいったん閉じる.
	CBinaryFile::Clear();	// バッファクリア
	CFile::Close();	// ハンドルもとじる.

	// 指定されたファイル名のファイルを読み込む.
	if (CBinaryFile::Read(lpctszFileName)) {	// 読み込みに成功したら.

		// 文字コード判定.
		CheckBOM();	// BOMのチェック.
		if (m_BOMType == BOM_TYPE_UTF16LE) {	// UTF-16LEの場合.
			
			// バイナリからUTF16LEテキストへの変換.
			m_Encoding = ENCODING_UTF16LE;	// ENCODING_UTF16LE.
			DecodeUtf16LE();	// DecodeUtf16LEでm_ptszRawTextにTCHAR(改行コード未変換)テキストが格納される.
			CheckNewLine();	// 改行コードの取得.
			GetText();	// CRLFのテキストをメンバにセット.

			// 読み込み成功なのでTRUE.
			return TRUE;	// TRUEを返す.

		}
		else if (m_BOMType == BOM_TYPE_UTF8) {	// UTF-8の場合.

			// バイナリからUTF-8テキストへの変換.
			m_Encoding = ENCODING_UTF8;	// ENCODING_UTF8.
			DecodeUtf8();	// DecodeUtf8でm_ptszRawTextにTCHAR(改行コード未変換)テキストが格納される.
			CheckNewLine();	// 改行コードの取得.
			GetText();	// CRLFのテキストをメンバにセット.

			// 読み込み成功なのでTRUE.
			return TRUE;	// TRUEを返す.

		}
		else {	// それ以外の場合はShift_JISとみなす.

			// バイナリからShiftJISテキストへの変換.
			m_Encoding = ENCODING_SHIFTJIS;	// ENCODING_SHIFTJIS.
			DecodeShiftJis();	// DecodeShiftJisでm_ptszRawTextにTCHAR(改行コード未変換)テキストが格納される.
			CheckNewLine();	// 改行コードの取得.
			GetText();	// CRLFのテキストをメンバにセット.

			// 読み込み成功なのでTRUE.
			return TRUE;	// TRUEを返す.

		}

	}

	// 読み込み失敗なのでFALSE.
	return FALSE;	// FALSEを返す.

}

// メンバ関数GetTextUtf16LE
void CTextFile::DecodeUtf16LE() {

	// テキスト配列の生成.
	m_ptszRawText = new TCHAR[m_dwSize - 2 + 1];	// (バイト数 - 2 + 1)分のTCHAR配列があれば十分かと思われる.
	wmemset(m_ptszRawText, _T('\0'), m_dwSize - 2 + 1);	// wmemsetでm_ptszRawTextを0で埋める.
	memcpy(m_ptszRawText, m_pBytes + 2, m_dwSize - 2);	// memcpyでm_pBytesの3バイト目からm_ptszRawTextにコピー.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslenの値をm_dwLenに格納.

}

// メンバ関数DecodeShiftJis
void CTextFile::DecodeShiftJis() {

	// 文字コード変換.
	int len = MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, NULL, NULL);	// MultiByteToWideCharでバイト列の変換に必要なバッファの長さlenを求める.
	m_ptszRawText = new TCHAR[len];	// lenの分のTCHAR動的配列を用意し, ポインタをm_ptszRawTextに格納.
	wmemset(m_ptszRawText, _T('\0'), len);	// wmemsetでm_ptszRawTextを0で埋める.
	MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, m_ptszRawText, len);	// MultiByteToWideCharでマルチバイト文字からワイド文字への変換.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslenの値をm_dwLenに格納.

}

// メンバ関数DecodeUtf8
void CTextFile::DecodeUtf8() {

	// 文字コード変換.
	int len = MultiByteToWideChar(CP_UTF8, 0, (char *)(m_pBytes + 3), -1, NULL, NULL);	// MultiByteToWideCharでバイト列の変換に必要なバッファの長さlenを求める.(BOMが3バイトあるので先頭の3バイト先から渡す.)
	m_ptszRawText = new TCHAR[len];	// lenの分のTCHAR動的配列を用意し, ポインタをm_ptszRawTextに格納.
	wmemset(m_ptszRawText, _T('\0'), len);	// wmemsetでm_ptszRawTextを0で埋める.
	MultiByteToWideChar(CP_UTF8, 0, (char *)(m_pBytes + 3), -1, m_ptszRawText, len);	// MultiByteToWideCharでマルチバイト文字からワイド文字への変換.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslenの値をm_dwLenに格納.

}

// メンバ関数CheckBOM
void CTextFile::CheckBOM() {

	// BOMの判定.
	if (m_dwSize >= 2 && m_pBytes[0] == 0xff && m_pBytes[1] == 0xfe) {	// UTF-16LEの場合.
		m_BOMType = BOM_TYPE_UTF16LE;	// BOM_TYPE_UTF16LEをセット.
	}
	else if (m_dwSize >= 3 && m_pBytes[0] == 0xef && m_pBytes[1] == 0xbb && m_pBytes[2] == 0xbf) {	// UTF-8の場合.
		m_BOMType = BOM_TYPE_UTF8;	// BOM_TYPE_UTF8をセット.
	}
	else {	// それ以外.
		m_BOMType = BOM_NONE;	// とりあえずBOM_NONEとする.
	}

}

// メンバ関数CheckNewLine
void CTextFile::CheckNewLine() {

	// 一時的にtstrTempに格納.
	tstring tstrTemp = m_ptszRawText;	// tstrTempをm_ptszRawTextで初期化.
	size_t p1 = tstrTemp.find_first_of(_T('\r'));	// tstrTemp.find_first_ofで'\r'があるかを調べる.
	size_t p2 = 0;	// sizet_t型p2.
	if (p1 != -1) {	// '\r'がある.
		p2 = tstrTemp.find_first_of(_T('\n'), p1);	// tstrTemp.find_first_ofで'\r'の後に'\n'があるかを調べる.
		if (p2 != -1) {	// '\n'がある.
			m_NewLine = NEW_LINE_CRLF;	// NEW_LINE_CRLFをセット.(CRLFの場合はこのまま.)
		}
		else {	// '\r'だけ.
			m_NewLine = NEW_LINE_CR;	// NEW_LINE_CRをセット.
		}
	}
	else {	// '\r'はない.
		p2 = tstrTemp.find_first_of(_T('\n'));	// tstrTemp.find_first_ofで'\n'があるかを調べる.
		if (p2 != -1) {	// '\n'がある.
			m_NewLine = NEW_LINE_LF;	// NEW_LINE_LFをセット.
		}
		else {	// '\n'もない.
			m_NewLine = NEW_LINE_NONE;	// NEW_LINE_NONEをセット.
		}
	}

}

// メンバ関数GetText
void CTextFile::GetText() {

	// 変数の宣言.
	tstring tstrTemp;	// 一時的にテキストを保持するtstrTemp.

	// いったんtstrTempに入れる.
	tstrTemp = m_ptszRawText;	// m_ptszRawTextをtstrTempに代入.

	// 改行コードをCRLFに統一.
	if (m_NewLine == NEW_LINE_CR) {	// CR.
		replace(tstrTemp, _T("\r"), _T("\r\n"));	// replaceで"\r\n"に置換.
	}
	else if (m_NewLine == NEW_LINE_LF) {	// LF.
		replace(tstrTemp, _T("\n"), _T("\r\n"));	// replaceで"\r\n"に置換.
	}
	
	// CRLFにしたテキストをm_tstrTextに入れる.
	m_tstrText = tstrTemp;	//tstrTempをm_tstrTextに格納.

}

// メンバ関数replace
void CTextFile::replace(tstring & target, const tstring & before, const tstring & after) {

	// tstringの文字列置換.
	tstring::size_type pos = target.find(before);	// targetで最初にbeforeが見つかった場所をposに格納.
	while (pos != tstring::npos) {
		target.replace(pos, before.size(), after);	// targetをbeforeからafterに置換.
		pos = target.find(before, pos + after.size());	// 次のposを探す.
	}

}

// メンバ関数SetText
void CTextFile::SetText(tstring tstrText) {

	// テキストのセット.
	m_tstrText = tstrText;	// m_tstrTextにtstrTextをセット.

}

// メンバ関数SetNewLine
void CTextFile::SetNewLine(NEW_LINE newline) {

	// 改行コードのセット.
	m_NewLine = newline;	// m_NewLineにnewlineをセット.

}

// メンバ関数SetEncoding
void CTextFile::SetEncoding(ENCODING encoding, BOM_TYPE bomtype) {

	// 文字コードとBOMのセット.
	m_Encoding = encoding;	// m_Encodingにencodingをセット.
	m_BOMType = bomtype;	// m_BOMTypeにbomtypeをセット.

}

// メンバ関数ReplaceNewLine
tstring CTextFile::ReplaceNewLine(tstring str, NEW_LINE newline) {

	// 改行コードを置き換える.
	tstring after;	// 置換後after.
	if (newline == NEW_LINE_CR) {
		after = _T("\r");	// afterは"\r".
	}
	else if (newline == NEW_LINE_LF) {
		after = _T("\n");	// afterは"\n".
	}
	else if (newline == NEW_LINE_CRLF) {
		after = _T("\r\n");	// afterは"\r\n".
	}
	replace(str, _T("\r\n"), after);	// replaceでbeforeからafterに置換.
	return str;	// strを返す.

}

// メンバ関数SetBytesUtf16LEWithBOM.
void CTextFile::SetBytesUtf16LEWithBOM(tstring text) {

	// バイト列のセット.
	BYTE *pByteWithBOM = new BYTE[(text.length() + 1) * 2];	// BOM付きバイト列を格納する配列pByteWithBOM.
	pByteWithBOM[0] = 0xff;	// 0番目は0xff.
	pByteWithBOM[1] = 0xfe;	// 1番目は0xfe.
	memcpy(pByteWithBOM + 2, (BYTE *)text.c_str(), text.length() * 2);	// pByteWithBOM + 2以降にコピー.
	Set(pByteWithBOM, (text.length() + 1) * 2);	// pByteWithBOMをセット.(サロゲートペア非対応.)
	delete[] pByteWithBOM;	// deleteでpByteWithBOMを解放.

}

// メンバ関数SetBytesShiftJIS.
void CTextFile::SetBytesShiftJIS(tstring text) {

	// バイト列のセット.
	int len = WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, NULL, 0, NULL, NULL);	// 変換に必要なバッファの長さを取得.
	BYTE *pByte = new BYTE[len];	// バイト列を格納する配列pByte.
	ZeroMemory(pByte, sizeof(BYTE) * len);	// pByteを0で埋める.
	WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, (char *)pByte, len, NULL, NULL);	// ワイド文字からマルチバイト文字への変換.
	if (len > 0) {	// lenが0より大きい場合.
		Set(pByte, len - 1);	// pByteを(len - 1)分セット.
	}
	delete[] pByte;	// deleteでpByteを解放.

}

// メンバ関数SetBytesUtf8WithBOM
void CTextFile::SetBytesUtf8WithBOM(tstring text) {

	// バイト列のセット.
	int len = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, NULL, 0, NULL, NULL);	// 変換に必要なバッファの長さを取得.
	BYTE *pByte = new BYTE[len + 3];	// バイト列を格納する配列pByte.(BOMの長さを含めるとlen + 3.)
	ZeroMemory(pByte, sizeof(BYTE) * (len + 3));	// pByteを0で埋める.
	pByte[0] = 0xef;	// 0番目に0xef.
	pByte[1] = 0xbb;	// 1番目に0xbb.
	pByte[2] = 0xbf;	// 2番目に0xbf.
	WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, (char *)(pByte + 3), len, NULL, NULL);	// ワイド文字からマルチバイト文字への変換.
	if (len > 0) {	//lenが0より大きい場合.
		Set(pByte, len + 2);	// pByteを(len + 2)分セット.
	}
	delete[] pByte;	// deleteでpByteを解放.

}

// メンバ関数ResetRawText
void CTextFile::ResetRawText(tstring text) {

	// ローテキストの再生成.
	delete[] m_ptszRawText;	// ローテキスト破棄.
	m_ptszRawText = new TCHAR[text.length() + 1];	// text.length() + 1の配列生成.
	wmemset(m_ptszRawText, _T('\0'), text.length() + 1);	// wmemsetで0で埋める.
	_tcscpy_s(m_ptszRawText, text.length() + 1, text.c_str());
	m_dwLen = _tcslen(m_ptszRawText);	// 長さをm_dwLen.

}

// メンバ関数Write
BOOL CTextFile::Write(LPCTSTR lpctszFileName) {

	// ファイルをいったん閉じる.
	CBinaryFile::Clear();	// バッファクリア
	CFile::Close();	// ハンドルもとじる.

	// 一時変数tstrTempに改行コードを置き換えたテキストを格納.
	tstring tstrTemp = ReplaceNewLine(m_tstrText, m_NewLine);	// ReplaceNewLineで置き換えたものをtstrTempに格納.

	// テキストからバイト列を生成.
	if (m_Encoding == ENCODING_UTF16LE) {	// UTF16LEの場合.
		if (m_BOMType == BOM_TYPE_UTF16LE) {	// BOM付き.
			SetBytesUtf16LEWithBOM(tstrTemp);	// tstrTempはUTF16LEに変換され, BOM付きバイトとしてセット.
			if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Writeで書き込み成功.
				ResetRawText(tstrTemp);	// ローテキストの作り直し.
				// 書き込み成功.
				return TRUE;	// TRUEを返す.
			}
			else {

				// 読み込み失敗なのでFALSE.
				return FALSE;	// FALSEを返す.

			}
		}
		else {

			// 読み込み失敗なのでFALSE.
			return FALSE;	// FALSEを返す.

		}
	}
	else if (m_Encoding == ENCODING_UTF8) {	// UTF8の場合.
		if (m_BOMType == BOM_TYPE_UTF8) {	// BOM付き.
			SetBytesUtf8WithBOM(tstrTemp);	// tstrTempはUTF8に変換され, BOM付きバイトとしてセット.
			if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Writeで書き込み成功.
				ResetRawText(tstrTemp);	// ローテキストの作り直し.
				// 書き込み成功.
				return TRUE;	// TRUEを返す.
			}
			else {

				// 読み込み失敗なのでFALSE.
				return FALSE;	// FALSEを返す.

			}
		}
		else {

			// 読み込み失敗なのでFALSE.
			return FALSE;	// FALSEを返す.

		}
	}
	else if (m_Encoding == ENCODING_SHIFTJIS) {	// SHIFTJISの場合.
		SetBytesShiftJIS(tstrTemp);	// tstrTempはSHIFTJISに変換され, バイト列がセット.
		if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Writeで書き込み成功.
			ResetRawText(tstrTemp);	// ローテキストの作り直し.
			// 書き込み成功.
			return TRUE;	// TRUEを返す.
		}
		else {

			// 読み込み失敗なのでFALSE.
			return FALSE;	// FALSEを返す.

		}
	}
	else {

		// 読み込み失敗なのでFALSE.
		return FALSE;	// FALSEを返す.

	}

}

// メンバ関数Clear
void CTextFile::Clear() {

	// テキスト配列の解放.
	if (m_ptszRawText != NULL) {	// m_ptszRawTextがNULLでない時.
		delete[] m_ptszRawText;	// delete[]で解放.
		m_ptszRawText = NULL;		// m_ptszRawTextにNULLをセット.
	}
	m_dwLen = 0;	// m_dwLenに0をセット.
	m_NewLine = NEW_LINE_NONE;	// m_NewLineにNEW_LINE_NONEをセット.
	m_BOMType = BOM_NONE;	// BOM_NONE.
	m_Encoding = ENCODING_NONE;	// ENCODING_NONE.
	m_tstrText.clear();	// クリア.

	// バイナリデータもクリア.
	CBinaryFile::Clear();	// CBinaryFile::Clearでクリア.

}