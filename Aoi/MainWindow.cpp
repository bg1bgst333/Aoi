// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow

// �����o�֐�RegisterClass
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// �E�B���h�E�N���X"CMainWindow"�̓o�^.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClass�ŃE�B���h�E�N���X"CMainWindow"��o�^.

}

// �����o�֐�Create
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// CWindow::Create�ŃE�B���h�E�쐬.
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ŃE�B���h�E�N���X��"CMainWindow"���E�B���h�E���쐬.

}

// �����o�֐�OnCreate
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// ����͏�ɃE�B���h�E�쐬�����Ƃ���.
	return 0;	// �����Ȃ�0��Ԃ�.

}