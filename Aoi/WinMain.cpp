// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc

// _tWinMain関数
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// 変数の宣言.
	int iRet;	// 戻り値を受け取るint型変数iRet.

	// メインアプリケーションオブジェクトの作成.
	CApplication *pApplication = new CMainApplication();	// newでCMainApplicationオブジェクトを作成し, CApplicationオブジェクトポインタpApplicationに格納.

	// メインアプリケーションの初期化.
	if (!pApplication->InitInstance(hInstance, lpCmdLine, nShowCmd)) {	// pApplication->InitInstanceで初期化.

		// 失敗したらExitInstanceを呼ぶ.
		iRet = pApplication->ExitInstance();	// pApplication->ExitInstanceを呼び, 戻り値をiRetに格納.

	}
	else {	// 成功した時.

		// メッセージループと終了処理.
		iRet = pApplication->Run();	// pApplication->Runでメッセージループ処理.(中でExitInstanceも実行される.)

	}

	// アプリケーションオブジェクトの破棄.
	delete pApplication;	// deleteでpApplicationを破棄.

	// プログラムの終了.
	return iRet;	// iRetを返す.

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