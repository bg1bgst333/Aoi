// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// メニューバークラスCMenuBar
class CMenuBar {

	// publicメンバ
	public:

		// publicメンバ変数
		HMENU m_hMenu;	// HMENU型メニューハンドルm_hMenu.
		HWND m_hWnd;	// HWND型ウィンドウハンドルm_hWnd.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMenuBar();	// コンストラクタCMenuBar()
		virtual ~CMenuBar();	// デストラクタ~CMenuBar()
		// メンバ関数
		virtual BOOL LoadMenu(HINSTANCE hInstance, UINT nID);	// メニューをリソースからロードする関数LoadMenu.
		virtual BOOL SetMenu(HWND hwnd);	// メニューをウィンドウにセットする関数SetMenu.

};