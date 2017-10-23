// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc

// メンバ関数InitInstance
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// ウィンドウクラスの登録.
	CWindow::RegisterClass(hInstance, _T("Aoi"));	// CWindow::RegisterClassでウィンドウクラス名"Aoi"を登録.

	// CWindowオブジェクトの作成.
	m_pMainWindow = new CWindow();	// CWindowオブジェクトを作成し, m_pMainWindowに格納.

	// ウィンドウの作成.
	if (!m_pMainWindow->Create(_T("Aoi"), _T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)) {	// m_pMainWindow->Createでウィンドウ作成に失敗した時.

		// 失敗ならFALSE.
		return FALSE;	// FALSEを返す.

	}

	// ウィンドウの表示.
	m_pMainWindow->ShowWindow(SW_SHOW);	// m_pMainWindow->ShowWindowでウィンドウを表示.

	// 初期化成功
	return TRUE;	// TRUEを返して正常終了.

}