// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication

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
