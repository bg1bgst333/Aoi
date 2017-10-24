// ヘッダのインクルード
// 独自のヘッダ
#include "Edit.h"	// CEdit

// コンストラクタCEdit()
CEdit::CEdit() : CCustomControl() {

}

// コンストラクタCEdit(HWND hParent, UINT nID)
CEdit::CEdit(HWND hParent, UINT nID) {

	// エディットコントロールのロード.
	Load(hParent, nID);	// LoadでnIDのエディットコントロールをロード.

}

// メンバ関数Load
HWND CEdit::Load(HWND hParent, UINT nID) {

	// リソースIDのエディットコントロールのウィンドウハンドルを取得.
	m_nID = nID;	// メンバにセット.
	m_hWnd = GetDlgItem(hParent, m_nID);	// GetDlgItemでm_nIDのエディットコントロールウィンドウハンドルを取得し, m_hWndに格納.
	return m_hWnd;	// m_hWndを返す.

}

// メンバ関数Create
BOOL CEdit::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// メンバにセット.
	m_nID = (int)hMenu;	// hMenuをm_nIDに代入.
	return CCustomControl::Create(_T("Edit"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)m_nID, hInstance);	// CCustomControl::Createでエディットコントロールを作成.

}

// メンバ関数SetText
void CEdit::SetText(tstring tstrText) {

	// テキストのセット.
	m_tstrText = tstrText;	// m_tstrTextにtstrTextを格納.
	SetWindowText(m_hWnd, tstrText.c_str());	// SetWindowTextでtstrTextをセット.

}

// メンバ関数GetText
void CEdit::GetText() {

	// テキストの長さを取得.
	int iLen = GetWindowTextLength(m_hWnd);	// GetWindowTextLengthで長さを取得.

	// テキスト動的配列の作成.
	TCHAR *ptszText = new TCHAR[iLen + 1];	// ptszTextの作成.

	// テキストの取得.
	GetWindowText(m_hWnd, ptszText, iLen + 1);	// GetWindowTextでテキストを取得.

	// m_tstrTextに格納.
	m_tstrText = ptszText;	// m_tstrTextにptszTextをセット.

	// 配列の破棄.
	delete[] ptszText;	// ptszTextの破棄.

}