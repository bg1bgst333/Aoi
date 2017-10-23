// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow

// メンバ関数RegisterClass
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// ウィンドウクラス"CMainWindow"の登録.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClassでウィンドウクラス"CMainWindow"を登録.

}

// メンバ関数Create
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// CWindow::Createでウィンドウ作成.
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createでウィンドウクラス名"CMainWindow"がウィンドウを作成.

}

// メンバ関数OnCreate
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// 今回は常にウィンドウ作成成功とする.
	return 0;	// 成功なら0を返す.

}