// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止

// ヘッダのインクルード
// 既定のヘッダ
#include <cstring>	// C文字列処理
#include <string>	// std::string
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// ファイルダイアログクラスCFileDialog
class CFileDialog {

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrPath;	// tstring型ファイルパスm_tstrPath
		tstring m_tstrDefFileName;	// tstring型ファイル名m_tstrDefName
		tstring m_tstrExt;	// tstring型デフォルト拡張子m_tstrExt
		TCHAR *m_ptszFilter;	// TCHAR型フィルタ文字列へのポインタm_ptszFilter
		DWORD m_dwFlags;	// DWORD型フラグm_dwFlags

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags);	// コンストラクタCFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags)
		virtual ~CFileDialog();	// デストラクタ~CFileDialog
		BOOL ShowOpenDialog(HWND hwnd);	// "開く"ダイアログの表示ShowOpenDialog
		BOOL ShowSaveDialog(HWND hwnd);	// "名前を付けて保存"ダイアログの表示ShowSaveDialog

};