// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow
#include "Edit.h"	// CEdit
#include "TextFile.h"	// CTextFile

// メインウィンドウクラスCMainWindow
class CMainWindow : public CMenuWindow {

	// publicメンバ
	public:

		// publicメンバ変数
		CEdit *m_pEdit;	// CEditオブジェクトポインタm_pEdit.
		CTextFile *m_pTextFile;	// CTextFileオブジェクトポインタm_pTextFile.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウ作成時のハンドラOnCreate.
		virtual void OnDestroy();	// ウィンドウ破棄時のハンドラOnDestroy.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウサイズが変更された時のハンドラOnSize.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"を選択された時のハンドラOnFileOpen.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "名前を付けて保存"を選択された時のハンドラOnFileSaveAs

};