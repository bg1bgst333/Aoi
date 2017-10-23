// ヘッダのインクルード
// 独自のヘッダ
#include "Application.h"	// CApplication

// メンバ関数Run
int CApplication::Run() {

	// 構造体の宣言.
	MSG msg;	// MSG型メッセージ構造体msg

	// メッセージループの処理.
	while (GetMessage(&msg, NULL, 0, 0) > 0) {	// GetMessageでウィンドウメッセージを取得し, msgに格納.(0以下なら, ここを抜ける.)

		// メッセージの変換と送出.
		TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字メッセージへ変換.
		DispatchMessage(&msg);	// DispatchMessageでメッセージをウィンドウプロシージャWindowProcに送出.

	}

	// 終了処理.
	return ExitInstance();	// 終了処理をExitInstanceに任せ, その戻り値をそのまま返す.

}

// メンバ関数ExitInstance
int CApplication::ExitInstance() {

	// とりあえず, 今回は常に成功時の0を返す.
	return 0;	// 0を返して正常終了.

}
