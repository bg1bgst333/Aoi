// ヘッダのインクルード
// 独自のヘッダ
#include "FileDialog.h"	// CFileDialog

// コンストラクタCFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags)
CFileDialog::CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags) {

	// メンバのセット.
	if (lpctszDefFileName == NULL) {	// NULLなら.
		m_tstrDefFileName = _T("");	// m_tstrDefFileNameを空にする.
	}
	else {	// そうでない場合.
		m_tstrDefFileName = lpctszDefFileName;	// デフォルトファイル名.
	}
	if (lpctszExt == NULL) {	// NULLなら.
		m_tstrExt = _T("");	// m_tstrExtを空にする.
	}
	else {	// そうでない場合.
		m_tstrExt = lpctszExt;	// デフォルト拡張子.
	}
	size_t len = _tcslen(lpctszFilter);	// フィルタの長さを取得.
	m_ptszFilter = new TCHAR[len + 1];	// フィルタを格納する配列を生成.
	wmemset(m_ptszFilter, _T('\0'), len + 1);	// wmemsetで0で埋める.
	_tcscpy_s(m_ptszFilter, len + 1, lpctszFilter);	// フィルタのコピー.
	for (unsigned int i = 0; i < len; i++) {	// フィルタの'|'を'\0'に置き換える.
		if (m_ptszFilter[i] == '|') {	// '|'なら.
			m_ptszFilter[i] = '\0';	// '\0'をセット.
		}
	}
	m_dwFlags = dwFlags;	// フラグをセット.

}

// デストラクタ~CFileDialog
CFileDialog::~CFileDialog() {

	// メンバの終了処理.
	delete[] m_ptszFilter;	// delete[]でm_ptszFilterを解放.

}

// メンバ関数ShowOpenDialog
BOOL CFileDialog::ShowOpenDialog(HWND hwnd) {

	// 変数の宣言・初期化.
	OPENFILENAME ofn = { 0 };	// OPENFILENAME構造体変数ofnを0で初期化.
	TCHAR *ptszPath = new TCHAR[1024];	// ptszPathを生成.
	wmemset(ptszPath, _T('\0'), 1024);	// 0で埋める.
	_tcscpy_s(ptszPath, m_tstrDefFileName.length() + 1, m_tstrDefFileName.c_str());	// 指定のパスをコピー.

	// ofnに値をセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// 構造体のサイズ.
	ofn.hwndOwner = hwnd;	// オーナーウィンドウ.
	ofn.lpstrFile = ptszPath;	// デフォルトパス.
	ofn.nMaxFile = 1024;	// MAXは1024.
	ofn.lpstrDefExt = m_tstrExt.c_str();	// デフォルト拡張子.
	ofn.lpstrFilter = m_ptszFilter;	// フィルタはm_tszFilterをセット.
	ofn.Flags = m_dwFlags;	// フラグ

	// ファイル選択.
	if (!GetOpenFileName(&ofn)) {	// GetOpenFileNameでファイルを選択.

		// 選択しなかった場合.(キャンセル)
		delete[] ptszPath;	// ptszPathを解放.
		m_tstrPath = _T("");	// ""をセット.
		return FALSE;	// 処理してないので戻り値としてFALSEを返す.

	}

	// パスを格納.
	m_tstrPath = ptszPath;	// ptszPathをm_tstrPathに格納.

	// バッファを解放.
	delete[] ptszPath;	// ptszPathを解放.

	// 処理したのでTRUEを返す.
	return TRUE;	// 処理したので戻り値としてTRUEを返す.

}

// メンバ関数ShowSaveDialog
BOOL CFileDialog::ShowSaveDialog(HWND hwnd) {

	// 変数の宣言・初期化.
	OPENFILENAME ofn = { 0 };	// OPENFILENAME構造体変数ofnを0で初期化.
	TCHAR *ptszPath = new TCHAR[1024];	// ptszPathを生成.
	wmemset(ptszPath, _T('\0'), 1024);	// 0で埋める.
	_tcscpy_s(ptszPath, m_tstrDefFileName.length() + 1, m_tstrDefFileName.c_str());	// 指定のパスをコピー.

	// ofnに値をセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// 構造体のサイズ.
	ofn.hwndOwner = hwnd;	// オーナーウィンドウ.
	ofn.lpstrFile = ptszPath;	// デフォルトパス.
	ofn.nMaxFile = 1024;	// MAXは1024.
	ofn.lpstrDefExt = m_tstrExt.c_str();	// デフォルト拡張子.
	ofn.lpstrFilter = m_ptszFilter;	// フィルタはm_tszFilterをセット.
	ofn.Flags = m_dwFlags;	// フラグ

	// ファイル選択.
	if (!GetSaveFileName(&ofn)) {	// GetSaveFileNameでファイルを選択.

		// 選択しなかった場合.(キャンセル)
		delete[] ptszPath;	// ptszPathを解放.
		m_tstrPath = _T("");	// ""をセット.
		return FALSE;	// 処理してないので戻り値としてFALSEを返す.

	}

	// パスを格納.
	m_tstrPath = ptszPath;	// ptszPathをm_tstrPathに格納.

	// バッファを解放.
	delete[] ptszPath;	// ptszPathを解放.

	// 処理したのでTRUEを返す.
	return TRUE;	// 処理したので戻り値としてTRUEを返す.

}