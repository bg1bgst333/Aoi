// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Window.h"	// CWindow

// static�����o�ϐ��̒�`.
std::map<HWND, CWindow *> CWindow::m_mapWindowMap;	// �E�B���h�E�}�b�vm_mapWindowMap.
std::map<DWORD, HandlerConditions*> CWindow::m_mapHandlerMap;	// �n���h���}�b�vm_mapHandlerMap.

// �R���X�g���N�^CWindow()
CWindow::CWindow() {

	// �����o�̏�����.
	m_hWnd = NULL;	// m_hWnd��NULL�ŏ�����.
}

// �f�X�g���N�^~CWindow()
CWindow::~CWindow() {

	// �����o�̏I������.
	if (m_hWnd != NULL) {	// m_hWnd��NULL�łȂ���.

		// �E�B���h�E�̔j��.
		DestroyWindow(m_hWnd);	// DestroyWindow��m_hWnd��j��.
		m_hWnd = NULL;	// m_hWnd��NULL���Z�b�g.

	}

}

// �����o�֐�RegisterClass
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName) {

	// �\���̂̐錾.
	WNDCLASS wc;	// WNDCLASS�^�E�B���h�E�N���X�\����wc

	// �E�B���h�E�N���X�\����wc�Ƀp�����[�^��ݒ�.
	wc.lpszClassName = lpctszClassName;	// �E�B���h�E�N���X���ɂ�lpctszClassName��n��.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// �X�^�C���͂Ƃ肠����CS_HREDRAW | CS_VREDRAW.
	wc.lpfnWndProc = StaticWindowProc;	// �E�B���h�E�v���V�[�W����StaticWindowProc.
	wc.hInstance = hInstance;	// �A�v���P�[�V�����C���X�^���X�n���h���͈�����hInstance���g��.
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	// LoadIcon�ŃA�v���P�[�V��������̃A�C�R�������[�h.
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);	// LoadCursor�ŃA�v���P�[�V��������̃J�[�\�������[�h.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// GetStockObject�Ŕ��u���V��w�i�F�Ƃ���.
	wc.lpszMenuName = NULL;	// �Ƃ肠�������j���[�͂Ȃ�(NULL�ɂ���.)
	wc.cbClsExtra = 0;	// �Ƃ肠����0���w��.
	wc.cbWndExtra = 0;	// �Ƃ肠����0���w��.

	// �E�B���h�E�N���X�̓o�^.
	if (!::RegisterClass(&wc)) {	// WindowsAPI��RegisterClass�ŃE�B���h�E�N���X��o�^����.

		// �߂�l��0�Ȃ�o�^���s�Ȃ̂ŃG���[����.
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-1)"), _T("Aoi"), MB_OK);	// MessageBox��"�\�����ʃG���[���������܂���!(-1)"�ƕ\��.
		return FALSE;	// FALSE��Ԃ��Ĉُ�I��.

	}

	// �����Ȃ�TRUE.
	return TRUE;	// �����Ȃ̂�TRUE��Ԃ�.

}

// �����o�֐�StaticWindowProc
LRESULT CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// �|�C���^�̏�����
	CWindow *pWindow = NULL;	// CWindow�I�u�W�F�N�g�|�C���^pWIndow��NULL�ɏ�����.

	// �E�B���h�E���b�Z�[�W����.
	switch (uMsg) {	// uMsg���ƂɐU�蕪����.

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{

				// �|�C���^�̏�����.
				LPCREATESTRUCT lpCreateStruct = NULL;	// CREATESTRUCT�\���̂ւ̃|�C���^lpCreateStruct��NULL.
				// lParam����lpCreateStruct�����o��.
				lpCreateStruct = (LPCREATESTRUCT)lParam;	// lParam��LPCREATESTRUCT�^�ɃL���X�g����lpCreateStruct�Ɋi�[.
				if (lpCreateStruct != NULL) {	// lpCreateStruct��NULL�łȂ����.
					pWindow = (CWindow *)lpCreateStruct->lpCreateParams;	// lpCreateStruct->lpCreateParams��CWindow�I�u�W�F�N�g�|�C���^�ɃL���X�g��, pWindow�Ɋi�[.
					CWindow::m_mapWindowMap.insert(std::pair<HWND, CWindow *>(hwnd, pWindow));	// CWindow::m_mapWindowMap��hwnd��pWindow�̃y�A��o�^.
				}

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO�̎�.
		default:

			// default�u���b�N
			{

				// hwnd��CWindow�I�u�W�F�N�g�|�C���^����������, pWindow�Ɋi�[.
				if (CWindow::m_mapWindowMap.find(hwnd) != CWindow::m_mapWindowMap.end()) {	// find�ŃL�[��hwnd�Ƃ���CWindow�I�u�W�F�N�g�|�C���^������������.
					pWindow = CWindow::m_mapWindowMap[hwnd];	// pWindow��hwnd�ň�����CWindow�I�u�W�F�N�g�|�C���^���i�[.
				}

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	}

	// CWindow�I�u�W�F�N�g�|�C���^���擾�ł��Ȃ������ꍇ, �擾�ł����ꍇ�ŕ�����.
	if (pWindow == NULL) {	// pWindow��NULL.

		// DefWindowProc�ɔC����.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProc�ɂ��̂܂܈�����n����, ���̒l��߂�l�Ƃ���.

	}
	else {	// pWindow��NULL�łȂ�.

		// ����CWindow�I�u�W�F�N�g��DynamicWindowProc�ɓn��.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamicWindowProc�ɂ��̂܂܈�����n����, ���̒l��߂�l�Ƃ���.

	}

}

// �����o�֐�Create
BOOL CWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CWindow"�Ƃ���.
	return CWindow::Create(_T("CWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�̃N���X����"CWindow"���w�肵�č쐬.

}

// �����o�֐�Create(�E�B���h�E�N���X������.)
BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// �E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, this);	// CreateWindow�ŃE�B���h�E���쐬��, �n���h����m_hWnd�Ɋi�[.(�Ō�̈�����this��n��.)
	if (m_hWnd == NULL) {	// m_hWnd��NULL�Ȃ玸�s.

		// ���s�Ȃ�FALSE��Ԃ�.
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-2)"), _T("Aoi"), MB_OK);	// MessageBox��"�\�����ʃG���[���������܂���!(-2)"�ƕ\��.
		return FALSE;	// FALSE��Ԃ�.

	}

	// �����Ȃ�TRUE.
	return TRUE;	// TRUE��Ԃ�.

}

// �����o�֐�ShowWindow
BOOL CWindow::ShowWindow(int nCmdShow) {

	// �E�B���h�E�̕\��
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPI��ShowWindow��m_hWnd��\��.

}

// �����o�֐�AddCommandHandler
void CWindow::AddCommandHandler(UINT nID, UINT nCode, int(CWindow:: * handler)(WPARAM wParam, LPARAM lParam)) {

	// HandlerConditions�̐���.
	HandlerConditions *pCond = new HandlerConditions();	// HandlerConditions�I�u�W�F�N�g���쐬��, �|�C���^��pCond�Ɋi�[.
	pCond->nID = nID;	// pCond->nID��nID���i�[.
	pCond->nCode = nCode;	// pCond->nCode��nCode���i�[.
	pCond->hfp = handler;	// pCond->hfp��handler���i�[.
	CWindow::m_mapHandlerMap.insert(std::pair<DWORD, HandlerConditions *>((DWORD)MAKEWPARAM(nID, nCode), pCond));	// CWindow::m_mapHandlerMap.insert��nID, nCode��MAKEWPARAM�������̂��L�[, pCond��l�Ƃ��ēo�^.

}

// �����o�֐�
void CWindow::DeleteCommandHandler(UINT nID, UINT nCode) {

	// �n���h�������폜.
	HandlerConditions *pCond = NULL;	// HandlerConditions�I�u�W�F�N�g�|�C���^pCond��NULL�ɏ�����.
	std::map<DWORD, HandlerConditions *>::iterator itor = CWindow::m_mapHandlerMap.find((DWORD)(MAKEWPARAM(nID, nCode)));	// find�ŃL�[��(DWORD)(MAKEWPARAM(nID, nCode))�Ƃ���HandlerConditions�I�u�W�F�N�g�|�C���^�̃C�e���[�^�擾.
	if (itor != CWindow::m_mapHandlerMap.end()) {	// ����������.
		pCond = CWindow::m_mapHandlerMap[(DWORD)(MAKEWPARAM(nID, nCode))];	// (DWORD)(MAKEWPARAM(nID, nCode))���g���ăn���h���}�b�v����HandlerConditions�I�u�W�F�N�g�|�C���^�������o��.
		delete pCond;	// HandlerConditions�I�u�W�F�N�g��j��.
		CWindow::m_mapHandlerMap.erase(itor);	// itor�̎w���v�f���폜.
	}

}

// �����o�֐�DynamicWindowProc
LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// �E�B���h�E���b�Z�[�W����
	switch (uMsg) {

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{

				// OnCreate�ɔC����.
				return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwnd��lParam��OnCreate�ɓn��, ���Ƃ͔C����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// OnDestroy�ɔC����.
				OnDestroy();	// OnDestroy���Ă�.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// �R�}���h������������.
		case WM_COMMAND:

			// WM_COMMAND�u���b�N
			{

				// OnCommand�ɔC����.
				return OnCommand(wParam, lParam) ? 0 : 1;	// wParam��lParam��n���ĔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	}

	// DefWindowProc�ɔC����.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProc�ɂ��̂܂܈�����n����, ���̒l��߂�l�Ƃ���.

}

// �����o�֐�OnCreate
int CWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// ��ɃE�B���h�E�쐬�����Ƃ���.
	return 0;	// �����Ȃ�0��Ԃ�.

}

// �����o�֐�OnDestroy
void CWindow::OnDestroy() {

	// �����̃E�B���h�E�n���h�����c���Ă�����}�b�v����폜.
	if (CWindow::m_mapWindowMap.find(m_hWnd) != CWindow::m_mapWindowMap.end()) {	// find�Ō���������.
		CWindow::m_mapWindowMap.erase(m_hWnd);	// CWindow::m_mapWindowMap.erase�ō폜.
	}

	// ���b�Z�[�W���[�v�I��.
	PostQuitMessage(0);	// PostQuitMessage�Ń��b�Z�[�W���[�v�𔲂�������.

}

// �����o�֐�OnCommand
BOOL CWindow::OnCommand(WPARAM wParam, LPARAM lParam) {

	// wParam����n���h�����������o��.
	HandlerConditions *pCond = NULL;	// HandlerConditions�I�u�W�F�N�g�|�C���^pCond��NULL�ɏ�����.
	if (CWindow::m_mapHandlerMap.find(wParam) != CWindow::m_mapHandlerMap.end()) {	// find�ŃL�[��wParam�Ƃ���HandlerConditions�I�u�W�F�N�g�|�C���^������������.
		pCond = CWindow::m_mapHandlerMap[wParam];	// wParam�ŃL�[���擾�ł���̂�, ������g���ăn���h���}�b�v����HandlerConditions�I�u�W�F�N�g�|�C���^�������o��.
	}
	if (pCond != NULL) {	// pCond��NULL�łȂ��Ȃ�, �n���h�����o�^����Ă���.
		int iRet = (this->*pCond->hfp)(wParam, lParam);	// �o�^�����n���h��pCond->hfp���Ăяo��, �߂�l��iRet�Ɋi�[.
		if (iRet == 0) {	// 0�Ȃ珈��������.
			return TRUE;	// �����������̂�TRUE.
		}
	}

	// �R�}���h���������Ă��Ȃ��̂�FALSE.
	return FALSE;	// FALSE��Ԃ�.

}