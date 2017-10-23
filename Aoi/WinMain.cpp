// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>	// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc

// _tWinMain関数
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// 変数・構造体の宣言.
	HWND hWnd;	// HWND型ウィンドウハンドルhWnd
	MSG msg;	// MSG型メッセージ構造体msg
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
		return -1;	// -1を返して異常終了.

	}

	// ウィンドウの作成
	hWnd = CreateWindow(wc.lpszClassName, _T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindowでウィンドウクラス名"Aoi"なウィンドウ"Aoi"を作成.
	if (hWnd == NULL) {	// hWndがNULLならウィンドウ作成失敗.

		// エラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-2)"), _T("Aoi"), MB_OK);	// MessageBoxで"予期せぬエラーが発生しました!(-2)"と表示.
		return -2;	// -2を返して異常終了.

	}

	// ウィンドウの表示.
	ShowWindow(hWnd, SW_SHOW);	// ShowWindowでウィンドウを表示.

	// メッセージループの処理.
	while (GetMessage(&msg, NULL, 0, 0) > 0) {	// GetMessageでウィンドウメッセージを取得し, msgに格納.(0以下なら, ここを抜ける.)

		// メッセージの変換と送出.
		TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字メッセージへ変換.
		DispatchMessage(&msg);	// DispatchMessageでメッセージをウィンドウプロシージャWindowProcに送出.

	}

	// プログラムの終了.
	return (int)msg.wParam;	// 終了コード(msg.wParam)を戻り値として返す.

}

// ウィンドウプロシージャWindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// ウィンドウメッセージの処理.
	switch (uMsg) {	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// ウィンドウ作成成功
				return 0;	// 0を返すと, ウィンドウ作成成功ということになる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// 終了メッセージの送信.
				PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 上記以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// あとは既定の処理に任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 戻り値も含めDefWindowProcに既定の処理を任せる.

}