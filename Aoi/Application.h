// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
// 独自のヘッダ
#include "Window.h"	// CWindow
// アプリケーションクラスCApplication
class CApplication {

	// publicメンバ
	public:

		// publicメンバ変数
		CWindow *m_pMainWindow;	// ウィンドウオブジェクトポインタm_pMainWindow.

		// publicメンバ関数
		// コンストラクタ
		CApplication();	// コンストラクタCApplication
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) = 0;	// 初期化関数InitInstance(純粋仮想関数)
		virtual int Run();	// メッセージループ処理関数Run
		virtual int ExitInstance();	// 終了処理関数ExitInstance

};