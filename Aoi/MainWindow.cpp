// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"	// ���\�[�XID

// �R���X�g���N�^CMainWindow
CMainWindow::CMainWindow() : CMenuWindow(){

}

// �f�X�g���N�^~CMainWindow
CMainWindow::~CMainWindow() {

}

// �����o�֐�RegisterClass
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// �E�B���h�E�N���X"CMainWindow"�̓o�^.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CMenuWindow::RegisterClass�ŃE�B���h�E�N���X"CMainWindow"��o�^.

}

// �����o�֐�Create
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// CMenuWindow::Create�ŃE�B���h�E�쐬.
	return CMenuWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CMenuWindow::Create�ŃE�B���h�E�N���X��"CMainWindow"�̃E�B���h�E���쐬.

}

// �����o�֐�OnCreate
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// ���j���[�o�[�̍쐬.(���I�ɍ쐬����ꍇ.)
	m_pMenuBar = new CMenuBar();	// CMenuBar�I�u�W�F�N�g���쐬��, �|�C���^��m_pMenuBar�Ɋi�[.

	// ���j���[�̃��[�h.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MAINMENU);	// LoadMenu��ID_MAINMENU�����[�h.

	// ���j���[�̃Z�b�g.
	m_pMenuBar->SetMenu(hwnd);	// SetMenu��hwnd�Ƀ��j���[���Z�b�g.

	// ���j���[�n���h���̒ǉ�.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
	AddCommandHandler(ID_FILE_SAVEAS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_FILE_SAVEAS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.

	// ����͏�ɃE�B���h�E�쐬�����Ƃ���.
	return 0;	// �����Ȃ�0��Ԃ�.

}

// �����o�֐�OnDestroy
void CMainWindow::OnDestroy() {

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_SAVEAS, 0);	// DeleteCommandHandler��ID_FILE_SAVEAS�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.

	// �e��OnDestroy���Ă�.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroy���Ă�.

}

// �����o�֐�OnFileOpen
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// "�J��"�ƕ\��.
	MessageBox(m_hWnd, _T("�J��"), _T("Aoi"), MB_OK | MB_ICONASTERISK);	// MessageBox��"�J��"�ƕ\��.

	// ���������̂�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}

// �����o�֐�OnFileSaveAs
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam) {

	// "���O��t���ĕۑ�"�ƕ\��.
	MessageBox(m_hWnd, _T("���O��t���ĕۑ�"), _T("Aoi"), MB_OK | MB_ICONASTERISK);	// MessageBox��"���O��t���ĕۑ�"�ƕ\��.

	// ���������̂�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}