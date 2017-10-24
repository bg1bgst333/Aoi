// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow

// staticメンバ変数の定義.
std::map<HWND, CWindow *> CWindow::m_mapWindowMap;	// ウィンドウマップm_mapWindowMap.
std::map<DWORD, HandlerConditions*> CWindow::m_mapHandlerMap;	// ハンドラマップm_mapHandlerMap.

// コンストラクタCWindow()
CWindow::CWindow() {

	// メンバの初期化.
	m_hWnd = NULL;	// m_hWndをNULLで初期化.
}

// デストラクタ~CWindow()
CWindow::~CWindow() {

	// メンバの終了処理.
	if (m_hWnd != NULL) {	// m_hWndがNULLでない時.

		// ウィンドウの破棄.
		DestroyWindow(m_hWnd);	// DestroyWindowでm_hWndを破棄.
		m_hWnd = NULL;	// m_hWndにNULLをセット.

	}

}

// メンバ関数RegisterClass
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName) {

	// 構造体の宣言.
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータを設定.
	wc.lpszClassName = lpctszClassName;	// ウィンドウクラス名にはlpctszClassNameを渡す.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// スタイルはとりあえずCS_HREDRAW | CS_VREDRAW.
	wc.lpfnWndProc = StaticWindowProc;	// ウィンドウプロシージャはStaticWindowProc.
	wc.hInstance = hInstance;	// アプリケーションインスタンスハンドルは引数のhInstanceを使う.
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	// LoadIconでアプリケーション既定のアイコンをロード.
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);	// LoadCursorでアプリケーション既定のカーソルをロード.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// GetStockObjectで白ブラシを背景色とする.
	wc.lpszMenuName = NULL;	// とりあえずメニューはなし(NULLにする.)
	wc.cbClsExtra = 0;	// とりあえず0を指定.
	wc.cbWndExtra = 0;	// とりあえず0を指定.

	// ウィンドウクラスの登録.
	if (!::RegisterClass(&wc)) {	// WindowsAPIのRegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-1)"), _T("Aoi"), MB_OK);	// MessageBoxで"予期せぬエラーが発生しました!(-1)"と表示.
		return FALSE;	// FALSEを返して異常終了.

	}

	// 成功ならTRUE.
	return TRUE;	// 成功なのでTRUEを返す.

}

// メンバ関数StaticWindowProc
LRESULT CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// ポインタの初期化
	CWindow *pWindow = NULL;	// CWindowオブジェクトポインタpWIndowをNULLに初期化.

	// ウィンドウメッセージ処理.
	switch (uMsg) {	// uMsgごとに振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// ポインタの初期化.
				LPCREATESTRUCT lpCreateStruct = NULL;	// CREATESTRUCT構造体へのポインタlpCreateStructをNULL.
				// lParamからlpCreateStructを取り出す.
				lpCreateStruct = (LPCREATESTRUCT)lParam;	// lParamをLPCREATESTRUCT型にキャストしてlpCreateStructに格納.
				if (lpCreateStruct != NULL) {	// lpCreateStructがNULLでなければ.
					pWindow = (CWindow *)lpCreateStruct->lpCreateParams;	// lpCreateStruct->lpCreateParamsはCWindowオブジェクトポインタにキャストし, pWindowに格納.
					CWindow::m_mapWindowMap.insert(std::pair<HWND, CWindow *>(hwnd, pWindow));	// CWindow::m_mapWindowMapにhwndとpWindowのペアを登録.
				}

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外の時.
		default:

			// defaultブロック
			{

				// hwndでCWindowオブジェクトポインタが引けたら, pWindowに格納.
				if (CWindow::m_mapWindowMap.find(hwnd) != CWindow::m_mapWindowMap.end()) {	// findでキーをhwndとするCWindowオブジェクトポインタが見つかったら.
					pWindow = CWindow::m_mapWindowMap[hwnd];	// pWindowにhwndで引けるCWindowオブジェクトポインタを格納.
				}

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	}

	// CWindowオブジェクトポインタが取得できなかった場合, 取得できた場合で分ける.
	if (pWindow == NULL) {	// pWindowがNULL.

		// DefWindowProcに任せる.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcにそのまま引数を渡して, その値を戻り値とする.

	}
	else {	// pWindowがNULLでない.

		// そのCWindowオブジェクトのDynamicWindowProcに渡す.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamicWindowProcにそのまま引数を渡して, その値を戻り値とする.

	}

}

// メンバ関数Create
BOOL CWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// ウィンドウクラス名は"CWindow"とする.
	return CWindow::Create(_T("CWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createのクラス名に"CWindow"を指定して作成.

}

// メンバ関数Create(ウィンドウクラス名あり.)
BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// ウィンドウの作成.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, this);	// CreateWindowでウィンドウを作成し, ハンドルをm_hWndに格納.(最後の引数にthisを渡す.)
	if (m_hWnd == NULL) {	// m_hWndがNULLなら失敗.

		// 失敗ならFALSEを返す.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-2)"), _T("Aoi"), MB_OK);	// MessageBoxで"予期せぬエラーが発生しました!(-2)"と表示.
		return FALSE;	// FALSEを返す.

	}

	// 成功ならTRUE.
	return TRUE;	// TRUEを返す.

}

// メンバ関数ShowWindow
BOOL CWindow::ShowWindow(int nCmdShow) {

	// ウィンドウの表示
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPIのShowWindowでm_hWndを表示.

}

// メンバ関数AddCommandHandler
void CWindow::AddCommandHandler(UINT nID, UINT nCode, int(CWindow:: * handler)(WPARAM wParam, LPARAM lParam)) {

	// HandlerConditionsの生成.
	HandlerConditions *pCond = new HandlerConditions();	// HandlerConditionsオブジェクトを作成し, ポインタをpCondに格納.
	pCond->nID = nID;	// pCond->nIDにnIDを格納.
	pCond->nCode = nCode;	// pCond->nCodeにnCodeを格納.
	pCond->hfp = handler;	// pCond->hfpにhandlerを格納.
	CWindow::m_mapHandlerMap.insert(std::pair<DWORD, HandlerConditions *>((DWORD)MAKEWPARAM(nID, nCode), pCond));	// CWindow::m_mapHandlerMap.insertでnID, nCodeをMAKEWPARAMしたものをキー, pCondを値として登録.

}

// メンバ関数
void CWindow::DeleteCommandHandler(UINT nID, UINT nCode) {

	// ハンドラ情報を削除.
	HandlerConditions *pCond = NULL;	// HandlerConditionsオブジェクトポインタpCondをNULLに初期化.
	std::map<DWORD, HandlerConditions *>::iterator itor = CWindow::m_mapHandlerMap.find((DWORD)(MAKEWPARAM(nID, nCode)));	// findでキーを(DWORD)(MAKEWPARAM(nID, nCode))とするHandlerConditionsオブジェクトポインタのイテレータ取得.
	if (itor != CWindow::m_mapHandlerMap.end()) {	// 見つかったら.
		pCond = CWindow::m_mapHandlerMap[(DWORD)(MAKEWPARAM(nID, nCode))];	// (DWORD)(MAKEWPARAM(nID, nCode))を使ってハンドラマップからHandlerConditionsオブジェクトポインタを引き出す.
		delete pCond;	// HandlerConditionsオブジェクトを破棄.
		CWindow::m_mapHandlerMap.erase(itor);	// itorの指す要素を削除.
	}

}

// メンバ関数DynamicWindowProc
LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// ウィンドウメッセージ処理
	switch (uMsg) {

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// OnCreateに任せる.
				return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwndとlParamをOnCreateに渡し, あとは任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// OnDestroyに任せる.
				OnDestroy();	// OnDestroyを呼ぶ.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// コマンドが発生した時.
		case WM_COMMAND:

			// WM_COMMANDブロック
			{

				// OnCommandに任せる.
				return OnCommand(wParam, lParam) ? 0 : 1;	// wParamとlParamを渡して任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	}

	// DefWindowProcに任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcにそのまま引数を渡して, その値を戻り値とする.

}

// メンバ関数OnCreate
int CWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// 常にウィンドウ作成成功とする.
	return 0;	// 成功なら0を返す.

}

// メンバ関数OnDestroy
void CWindow::OnDestroy() {

	// 自分のウィンドウハンドルが残っていたらマップから削除.
	if (CWindow::m_mapWindowMap.find(m_hWnd) != CWindow::m_mapWindowMap.end()) {	// findで見つかったら.
		CWindow::m_mapWindowMap.erase(m_hWnd);	// CWindow::m_mapWindowMap.eraseで削除.
	}

	// メッセージループ終了.
	PostQuitMessage(0);	// PostQuitMessageでメッセージループを抜けさせる.

}

// メンバ関数OnCommand
BOOL CWindow::OnCommand(WPARAM wParam, LPARAM lParam) {

	// wParamからハンドラ情報を引き出す.
	HandlerConditions *pCond = NULL;	// HandlerConditionsオブジェクトポインタpCondをNULLに初期化.
	if (CWindow::m_mapHandlerMap.find(wParam) != CWindow::m_mapHandlerMap.end()) {	// findでキーをwParamとするHandlerConditionsオブジェクトポインタが見つかったら.
		pCond = CWindow::m_mapHandlerMap[wParam];	// wParamでキーが取得できるので, それを使ってハンドラマップからHandlerConditionsオブジェクトポインタを引き出す.
	}
	if (pCond != NULL) {	// pCondがNULLでないなら, ハンドラが登録されている.
		int iRet = (this->*pCond->hfp)(wParam, lParam);	// 登録したハンドラpCond->hfpを呼び出し, 戻り値はiRetに格納.
		if (iRet == 0) {	// 0なら処理をした.
			return TRUE;	// 処理をしたのでTRUE.
		}
	}

	// コマンドを処理していないのでFALSE.
	return FALSE;	// FALSEを返す.

}