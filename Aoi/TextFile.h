// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 既定のヘッダ
#include <string>	// std::string
// 独自のヘッダ
#include "BinaryFile.h"	// CBinaryFile

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// テキストファイルクラス
class CTextFile : public CBinaryFile {

	// publicメンバ
	public:

		// 列挙型の定義.
		// BOM
		typedef enum TAG_BOM_TYPE {
			BOM_NONE,
			BOM_TYPE_UTF16LE,
			BOM_TYPE_UTF16BE,
			BOM_TYPE_UTF8
		} BOM_TYPE;
		// 改行
		typedef enum TAG_NEW_LINE {
			NEW_LINE_NONE,
			NEW_LINE_LF,
			NEW_LINE_CR,
			NEW_LINE_CRLF
		} NEW_LINE;
		// 文字コード
		typedef enum TAG_ENCODING {
			ENCODING_NONE,
			ENCODING_UTF16LE,
			ENCODING_SHIFTJIS,
			ENCODING_UTF8
		} ENCODING;

		// publicメンバ変数
		TCHAR *m_ptszRawText;	// TCHARにデコード済みのテキストへのポインタm_ptszRawText.(改行コードは元のまま.)
		tstring m_tstrText;		// 改行コードはCRLFのテキストm_tstrText.
		DWORD m_dwLen;	// テキストの長さm_dwLen.
		BOM_TYPE m_BOMType;	// BOMタイプm_BOMType.
		NEW_LINE m_NewLine;	// 改行コードm_NewLine.
		ENCODING m_Encoding;	// 文字コードm_Encoding.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CTextFile();	// コンストラクタCTextFile
		virtual ~CTextFile();	// コンストラクタ~CTextFile
		virtual BOOL Read(LPCTSTR lpctszFileName);	// テキストの読み込み関数Read.
		void DecodeUtf16LE();	// Utf16LEの読み込み関数DecodeUtf16LE.
		void DecodeShiftJis();	// ShiftJisの読み込み関数DecodeShiftJis.
		void DecodeUtf8();		// Utf8の読み込み関数DecodeUtf8.
		void CheckBOM();	// BOMのチェック関数CheckBOM.
		void CheckNewLine();	// 改行のチェック及びCRLFへの修正を行う関数CheckNewLine.
		void GetText();	// テキストを取得する関数GetText.(改行コードはCRLFに変更済み.)
		void replace(tstring &target, const tstring &before, const tstring &after);	// tstringの置換関数replace.
		void SetText(tstring tstrText);	// テキストをセットする関数SetText.
		void SetNewLine(NEW_LINE newline);	// 改行をセットする関数SetNewLine.
		void SetEncoding(ENCODING encoding, BOM_TYPE bomtype);	// 文字コードをセットする関数SetEncoding.
		tstring ReplaceNewLine(tstring str, NEW_LINE newline);	// 指定のテキストの改行コードを置き換えたものを返す関数ReplaceNewLine.
		void SetBytesUtf16LEWithBOM(tstring text);	// BOM付きUTF16LEのバイト列をセットする関数SetBytesUtf16LEWithBOM.
		void SetBytesShiftJIS(tstring text);	// ShiftJISのバイト列をセットする関数SetBytesShiftJIS.
		void SetBytesUtf8WithBOM(tstring text);	// BOM付きUTF8のバイト列をセットする関数SetBytesUtf8WithBOM.
		void ResetRawText(tstring text);	// 指定されたテキストにローテキストをリセットする.
		virtual BOOL Write(LPCTSTR lpctszFileName);	// テキストの書き込み関数Write.
		void Clear();	// バッファのクリア関数Clear

};