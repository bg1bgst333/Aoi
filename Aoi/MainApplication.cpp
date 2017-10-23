// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication
#include "MainWindow.h"	// CMainWindow

// メンバ関数InitInstance
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// ウィンドウクラスの登録.
	CMainWindow::RegisterClass(hInstance);	// CMainWindow::RegisterClassでウィンドウクラス名"CMainWindow"を登録.

	// CMainWindowオブジェクトの作成.
	m_pMainWindow = new CMainWindow();	// CMainWindowオブジェクトを作成し, m_pMainWindowに格納.

	// ウィンドウの作成.
	if (!m_pMainWindow->Create(_T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)) {	// m_pMainWindow->Createでウィンドウ作成に失敗した時.

		// 失敗ならFALSE.
		return FALSE;	// FALSEを返す.

	}

	// ウィンドウの表示.
	m_pMainWindow->ShowWindow(SW_SHOW);	// m_pMainWindow->ShowWindowでウィンドウを表示.

	// 初期化成功
	return TRUE;	// TRUEを返して正常終了.

}