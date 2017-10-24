// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"	// リソースID

// コンストラクタCMainWindow
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_pEdit = NULL;	// m_pEditをNULLで初期化.

}

// デストラクタ~CMainWindow
CMainWindow::~CMainWindow() {

	// メンバの終了処理.
	if (m_pEdit != NULL) {
		delete m_pEdit;	// deleteでm_pEditを解放.
		m_pEdit = NULL;	// m_pEditにNULLをセット.
	}

}

// メンバ関数RegisterClass
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// ウィンドウクラス"CMainWindow"の登録.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CMenuWindow::RegisterClassでウィンドウクラス"CMainWindow"を登録.

}

// メンバ関数Create
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// CMenuWindow::Createでウィンドウ作成.
	return CMenuWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CMenuWindow::Createでウィンドウクラス名"CMainWindow"のウィンドウを作成.

}

// メンバ関数OnCreate
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// メニューバーの作成.(動的に作成する場合.)
	m_pMenuBar = new CMenuBar();	// CMenuBarオブジェクトを作成し, ポインタをm_pMenuBarに格納.

	// メニューのロード.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MAINMENU);	// LoadMenuでID_MAINMENUをロード.

	// メニューのセット.
	m_pMenuBar->SetMenu(hwnd);	// SetMenuでhwndにメニューをセット.

	// メニューハンドラの追加.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
	AddCommandHandler(ID_FILE_SAVEAS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_FILE_SAVEASに対するハンドラCMainWindow::OnFileSaveAsを登録.

	// エディットコントロールオブジェクトの作成.
	m_pEdit = new CEdit();	// CEditオブジェクトを作成し, ポインタをm_pEditに格納.

	// エディットコントロールの作成.
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Createでエディットコントロールを作成.

	// 今回は常にウィンドウ作成成功とする.
	return 0;	// 成功なら0を返す.

}

// メンバ関数OnDestroy
void CMainWindow::OnDestroy() {

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_SAVEAS, 0);	// DeleteCommandHandlerでID_FILE_SAVEASのハンドラを削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.

	// 親のOnDestroyを呼ぶ.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroyを呼ぶ.

}

// メンバ関数OnSize
void CMainWindow::OnSize(UINT nType, int cx, int cy) {

	// 子ウィンドウのサイズも合わせる.
	if (m_pEdit != NULL) {	// NULLでないなら.
		MoveWindow(m_pEdit->m_hWnd, 0, 0, cx, cy, TRUE);	// MoveWindowでエディットコントロールのサイズを合わせる.
	}

}

// メンバ関数OnFileOpen
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// ファイルダイアログの表示.
	CFileDialog selDlg(NULL, NULL, _T("Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenDialog(m_hWnd)) {	// selDlg.ShowOpenDialogで"開く"ダイアログを表示.

		// 選択したファイル名の表示.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("Aoi"), MB_OK | MB_ICONASTERISK);	// MessageBoxでselDlg.m_tstrPathを表示.

	}

	// 処理したので0を返す.
	return 0;	// 0を返す.

}

// メンバ関数OnFileSaveAs
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam) {

	// ファイルダイアログの表示.
	CFileDialog selDlg(NULL, _T("txt"), _T("Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveDialog(m_hWnd)) {	// selDlg.ShowSaveDialogで"名前を付けて保存"ダイアログを表示.

		// 指定したファイル名の表示.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("Aoi"), MB_OK | MB_ICONASTERISK);	// MessageBoxでselDlg.m_tstrPathを表示.

	}

	// 処理したので0を返す.
	return 0;	// 0を返す.

}