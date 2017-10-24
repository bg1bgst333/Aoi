// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
#include <map>	// std::map
// 独自のヘッダ
#include "HandlerConditions.h"	// 構造体HandlerConditions

// ウィンドウクラスCWindow
class CWindow {

	// publicメンバ
	public:

		// publicメンバ変数
		HWND m_hWnd;	// HWND型ウィンドウハンドルm_hWnd.
		// staticメンバ変数
		static std::map<HWND, CWindow *> m_mapWindowMap;	// ウィンドウハンドルをキー, CWindowオブジェクトポインタを値とするm_mapWindowMap.
		static std::map<DWORD, HandlerConditions *> m_mapHandlerMap;	// nIDをキー, HandlerConditionsポインタを値とするマップm_mapHandlerMap.

		// publicメンバ関数
		CWindow();	// コンストラクタCWindow()
		virtual ~CWindow();	// デストラクタ~CWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName);	// ウィンドウクラス登録関数RegisterClass
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャStaticWindowProc
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create
		virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create(ウィンドウクラス名あり.)
		virtual BOOL ShowWindow(int nCmdShow);	// ウィンドウ表示関数ShowWindow
		virtual void AddCommandHandler(UINT nID, UINT nCode, int(CWindow:: * handler)(WPARAM wParam, LPARAM lParam));	// コマンドハンドラ追加関数AddCommandHandler
		virtual void DeleteCommandHandler(UINT nID, UINT nCode);	// コマンドハンドラ削除関数DeleteCommandHandler
		virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// StaticWindowProcから各ウィンドウオブジェクトごとに呼び出されるサブウィンドウプロシージャDynamicWindowProc.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウ作成時のハンドラOnCreate.
		virtual void OnDestroy();	// ウィンドウ破棄時のハンドラOnDestroy.
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	// コマンド発生時のハンドラOnCommand.

};