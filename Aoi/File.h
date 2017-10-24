// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
#include <windows.h>	// 標準WindowsAPI
#include <tchar.h>		// TCHAR型
#include <string>		// std::string

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// ファイルクラス
class CFile {

	// publicメンバ
	public:
		
		// publicメンバ変数
		HANDLE m_hFile;	// ファイルハンドルm_hFile
		tstring m_tstrFileName;	// ファイル名m_tstrFileName

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFile();
		virtual ~CFile();
		// メンバ関数
		virtual BOOL Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);	// メンバ関数Open
		virtual void Close();	// メンバ関数Close
		virtual DWORD Read(LPVOID lpBuf, DWORD dwBytes);	// メンバ関数Read
		virtual DWORD Write(LPVOID lpBuf, DWORD dwBytes);	// メンバ関数Write

};
