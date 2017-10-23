// ヘッダのインクルード
// 独自のヘッダ
#include "MenuBar.h"	// CMenuBar

// コンストラクタCMenuBar()
CMenuBar::CMenuBar() {

	// メンバの初期化.
	m_hMenu = NULL;	// m_hMenuをNULLで初期化.

}

// デストラクタ~CMenuBar()
CMenuBar::~CMenuBar() {

	// メンバの終了処理.
	// とりあえず何もしない.
}

// メンバ関数LoadMenu
BOOL CMenuBar::LoadMenu(HINSTANCE hInstance, UINT nID) {

	// メニューnIDをロード.
	m_hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(nID));	// LoadMenuでnIDをロード.
	if (m_hMenu == NULL) {	// m_hMenuがNULLなら.

		// 失敗なのでFALSEを返す.
		return FALSE;	// FALSEを返す.

	}

	// 成功なのでTRUEを返す.
	return 0;	// TRUEを返す.

}

// メンバ関数SetMenu
BOOL CMenuBar::SetMenu(HWND hwnd) {

	// メンバに引数をセット.
	m_hWnd = hwnd;	// m_hWndにhwndをセット.

	// メニューのセット.
	return ::SetMenu(m_hWnd, m_hMenu);	// SetMenuでm_hMenuをセットし, 戻り値をそのまま返す.

}