// ヘッダのインクルード
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow

// コンストラクタCMenuWindow
CMenuWindow::CMenuWindow() : CWindow() {

	// メンバの初期化
	m_pMenuBar = NULL;	// m_pMenuBarをNULLで初期化.

}

// デストラクタ~CMenuWindow
CMenuWindow::~CMenuWindow() {

	// メンバの終了処理.
	if (m_pMenuBar != NULL) {	// m_pMenuBarがNULLでなければ.
		delete m_pMenuBar;	// deleteでm_pMenuBarを解放.
		m_pMenuBar = NULL;	// m_pMenuBarをNULLで埋める.
	}

}

// メンバ関数RegisterClass
BOOL CMenuWindow::RegisterClass(HINSTANCE hInstance) {

	// ウィンドウクラス名"CMenuWindow"を登録.
	return CWindow::RegisterClass(hInstance, _T("CMenuWindow"));	// // CWindow::RegisterClassで"CMenuWindow"を登録し, 戻り値をそのまま返す.

}

// メンバ関数RegisterClass(ウィンドウクラス名指定バージョン.)
BOOL CMenuWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName) {

	// 指定のウィンドウクラス名lpctszClassNameを登録.
	return CWindow::RegisterClass(hInstance, lpctszClassName);	// CWindow::RegisterClassでlpctszClassNameを登録し, 戻り値をそのまま返す.

}

// メンバ関数Create
BOOL CMenuWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// ウィンドウクラス名"CMenuWindow"のウィンドウを作成.
	return CWindow::Create(_T("CMenuWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createのウィンドウクラス名に"CMenuWindow"を指定.

}

// メンバ関数Create(ウィンドウクラス名指定バージョン.)
BOOL CMenuWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// 指定のウィンドウクラス名lpctszClassNameのウィンドウを作成.
	return CWindow::Create(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createのウィンドウクラス名にlpctszClassNameを指定.

}