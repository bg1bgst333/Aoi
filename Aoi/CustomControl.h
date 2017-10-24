// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// 既定のヘッダ
#include <string>	// std::string
// 独自のヘッダ
#include "Window.h"	// CWindow

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// カスタムコントロールクラス
class CCustomControl : public CWindow {

	// publicメンバ
	public:

		// publicメンバ変数
		// staticメンバ変数
		static std::map<tstring, WNDPROC> m_mapBaseWindowProcMap;	// 既定のウィンドウクラス名をキー, 既定のウィンドウプロシージャを値とするマップm_mapBaseWindowProcMap.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CCustomControl();	// コンストラクタCCustomControl
		// staticメンバ関数
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// カスタムコントロール専用のStaticWindowProc.
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create(ウィンドウクラス名指定バージョン.)
		virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// StaticWindowProcから各ウィンドウオブジェクトごとに呼び出されるサブウィンドウプロシージャDynamicWindowProc.
		virtual void OnDestroy();	// ウィンドウ破棄時のハンドラOnDestroy.

};