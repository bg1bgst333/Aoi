// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"	// ���\�[�XID

// �R���X�g���N�^CMainWindow
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.
	m_pTextFile = NULL;	// m_pTextFile��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow
CMainWindow::~CMainWindow() {

	// �����o�̏I������.
	if (m_pTextFile != NULL) {
		delete m_pTextFile;	// delete��m_pTextFile�����.
		m_pTextFile = NULL;	// m_pTextFile��NULL���Z�b�g.
	}
	if (m_pEdit != NULL) {
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// m_pEdit��NULL���Z�b�g.
	}

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

	// �G�f�B�b�g�R���g���[���I�u�W�F�N�g�̍쐬.
	m_pEdit = new CEdit();	// CEdit�I�u�W�F�N�g���쐬��, �|�C���^��m_pEdit�Ɋi�[.

	// �G�f�B�b�g�R���g���[���̍쐬.
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Create�ŃG�f�B�b�g�R���g���[�����쐬.

	// �e�L�X�g�t�@�C���I�u�W�F�N�g�̐���.
	m_pTextFile = new CTextFile();	// CTextFile�I�u�W�F�N�g���쐬��, �|�C���^��m_pTextFile�Ɋi�[.

	// ����͏�ɃE�B���h�E�쐬�����Ƃ���.
	return 0;	// �����Ȃ�0��Ԃ�.

}

// �����o�֐�OnDestroy
void CMainWindow::OnDestroy() {

	// �e�L�X�g�t�@�C���I�u�W�F�N�g�̔j��.
	if (m_pTextFile != NULL) {
		delete m_pTextFile;	// delete��m_pTextFile�����.
		m_pTextFile = NULL;	// m_pTextFile��NULL���Z�b�g.
	}

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_SAVEAS, 0);	// DeleteCommandHandler��ID_FILE_SAVEAS�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.

	// �e��OnDestroy���Ă�.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroy���Ă�.

}

// �����o�֐�OnSize
void CMainWindow::OnSize(UINT nType, int cx, int cy) {

	// �q�E�B���h�E�̃T�C�Y�����킹��.
	if (m_pEdit != NULL) {	// NULL�łȂ��Ȃ�.
		MoveWindow(m_pEdit->m_hWnd, 0, 0, cx, cy, TRUE);	// MoveWindow�ŃG�f�B�b�g�R���g���[���̃T�C�Y�����킹��.
	}

}

// �����o�֐�OnFileOpen
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// �t�@�C���_�C�A���O�̕\��.
	CFileDialog selDlg(NULL, NULL, _T("Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenDialog(m_hWnd)) {	// selDlg.ShowOpenDialog��"�J��"�_�C�A���O��\��.

		// �e�L�X�g�t�@�C�����J����, �e�L�X�g���G�f�B�b�g�R���g���[���ɃZ�b�g.
		if (m_pTextFile->Read(selDlg.m_tstrPath.c_str())) {	// m_pTextFile->Read�œǂݍ���.
			m_pEdit->SetText(m_pTextFile->m_tstrText);	// m_pEdit->SetText�ŃG�f�B�b�g�R���g���[����m_pTextFile->m_tstrText���Z�b�g.
		}

	}

	// ���������̂�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}

// �����o�֐�OnFileSaveAs
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam) {

	// �t�@�C���_�C�A���O�̕\��.
	CFileDialog selDlg(NULL, _T("txt"), _T("Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveDialog(m_hWnd)) {	// selDlg.ShowSaveDialog��"���O��t���ĕۑ�"�_�C�A���O��\��.

		// �w�肵���e�L�X�g�t�@�C����, �G�f�B�b�g�R���g���[���̃e�L�X�g��ۑ�.
		m_pEdit->GetText();	// �G�f�B�b�g�R���g���[���̃e�L�X�g���擾.
		m_pTextFile->SetText(m_pEdit->m_tstrText);	// �e�L�X�g�t�@�C���ɏ������ރe�L�X�gm_pEdit->m_tstrText���Z�b�g.
		m_pTextFile->SetNewLine(CTextFile::NEW_LINE_CRLF);	// ���s�R�[�h��CRLF.
		m_pTextFile->SetEncoding(CTextFile::ENCODING_SHIFTJIS, CTextFile::BOM_NONE);	// Shift_JIS, BOM�Ȃ�.
		m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// m_pTextFile->Write��selDlg.m_tstrPath�ɏ�������.

	}

	// ���������̂�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}