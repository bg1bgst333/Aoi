// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc

// メンバ関数InitInstance
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// 変数・構造体の宣言.
	HWND hWnd;	// HWND型ウィンドウハンドルhWnd
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータを設定.
	wc.lpszClassName = _T("Aoi");	// ウィンドウクラス名はとりあえず"Aoi"とする.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// スタイルはとりあえずCS_HREDRAW | CS_VREDRAW.
	wc.lpfnWndProc = WindowProc;	// ウィンドウプロシージャは下で定義するWindowProc.
	wc.hInstance = hInstance;	// アプリケーションインスタンスハンドルは引数のhInstanceを使う.
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	// LoadIconでアプリケーション既定のアイコンをロード.
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);	// LoadCursorでアプリケーション既定のカーソルをロード.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// GetStockObjectで白ブラシを背景色とする.
	wc.lpszMenuName = NULL;	// とりあえずメニューはなし(NULLにする.)
	wc.cbClsExtra = 0;	// とりあえず0を指定.
	wc.cbWndExtra = 0;	// とりあえず0を指定.

	// ウィンドウクラスの登録.
	if (!RegisterClass(&wc)) {	// RegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-1)"), _T("Aoi"), MB_OK);	// MessageBoxで"予期せぬエラーが発生しました!(-1)"と表示.
		return FALSE;	// FALSEを返して異常終了.

	}

	// ウィンドウの作成
	hWnd = CreateWindow(wc.lpszClassName, _T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindowでウィンドウクラス名"Aoi"なウィンドウ"Aoi"を作成.
	if (hWnd == NULL) {	// hWndがNULLならウィンドウ作成失敗.

		// エラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-2)"), _T("Aoi"), MB_OK);	// MessageBoxで"予期せぬエラーが発生しました!(-2)"と表示.
		return FALSE;	// FALSEを返して異常終了.

	}

	// ウィンドウの表示.
	ShowWindow(hWnd, SW_SHOW);	// ShowWindowでウィンドウを表示.

	// 初期化成功.
	return TRUE;	// TRUEを返して正常終了.

}