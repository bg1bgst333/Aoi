// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "FileDialog.h"	// CFileDialog

// �R���X�g���N�^CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags)
CFileDialog::CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags) {

	// �����o�̃Z�b�g.
	if (lpctszDefFileName == NULL) {	// NULL�Ȃ�.
		m_tstrDefFileName = _T("");	// m_tstrDefFileName����ɂ���.
	}
	else {	// �����łȂ��ꍇ.
		m_tstrDefFileName = lpctszDefFileName;	// �f�t�H���g�t�@�C����.
	}
	if (lpctszExt == NULL) {	// NULL�Ȃ�.
		m_tstrExt = _T("");	// m_tstrExt����ɂ���.
	}
	else {	// �����łȂ��ꍇ.
		m_tstrExt = lpctszExt;	// �f�t�H���g�g���q.
	}
	size_t len = _tcslen(lpctszFilter);	// �t�B���^�̒������擾.
	m_ptszFilter = new TCHAR[len + 1];	// �t�B���^���i�[����z��𐶐�.
	wmemset(m_ptszFilter, _T('\0'), len + 1);	// wmemset��0�Ŗ��߂�.
	_tcscpy_s(m_ptszFilter, len + 1, lpctszFilter);	// �t�B���^�̃R�s�[.
	for (unsigned int i = 0; i < len; i++) {	// �t�B���^��'|'��'\0'�ɒu��������.
		if (m_ptszFilter[i] == '|') {	// '|'�Ȃ�.
			m_ptszFilter[i] = '\0';	// '\0'���Z�b�g.
		}
	}
	m_dwFlags = dwFlags;	// �t���O���Z�b�g.

}

// �f�X�g���N�^~CFileDialog
CFileDialog::~CFileDialog() {

	// �����o�̏I������.
	delete[] m_ptszFilter;	// delete[]��m_ptszFilter�����.

}

// �����o�֐�ShowOpenDialog
BOOL CFileDialog::ShowOpenDialog(HWND hwnd) {

	// �ϐ��̐錾�E������.
	OPENFILENAME ofn = { 0 };	// OPENFILENAME�\���̕ϐ�ofn��0�ŏ�����.
	TCHAR *ptszPath = new TCHAR[1024];	// ptszPath�𐶐�.
	wmemset(ptszPath, _T('\0'), 1024);	// 0�Ŗ��߂�.
	_tcscpy_s(ptszPath, m_tstrDefFileName.length() + 1, m_tstrDefFileName.c_str());	// �w��̃p�X���R�s�[.

	// ofn�ɒl���Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// �\���̂̃T�C�Y.
	ofn.hwndOwner = hwnd;	// �I�[�i�[�E�B���h�E.
	ofn.lpstrFile = ptszPath;	// �f�t�H���g�p�X.
	ofn.nMaxFile = 1024;	// MAX��1024.
	ofn.lpstrDefExt = m_tstrExt.c_str();	// �f�t�H���g�g���q.
	ofn.lpstrFilter = m_ptszFilter;	// �t�B���^��m_tszFilter���Z�b�g.
	ofn.Flags = m_dwFlags;	// �t���O

	// �t�@�C���I��.
	if (!GetOpenFileName(&ofn)) {	// GetOpenFileName�Ńt�@�C����I��.

		// �I�����Ȃ������ꍇ.(�L�����Z��)
		delete[] ptszPath;	// ptszPath�����.
		m_tstrPath = _T("");	// ""���Z�b�g.
		return FALSE;	// �������ĂȂ��̂Ŗ߂�l�Ƃ���FALSE��Ԃ�.

	}

	// �p�X���i�[.
	m_tstrPath = ptszPath;	// ptszPath��m_tstrPath�Ɋi�[.

	// �o�b�t�@�����.
	delete[] ptszPath;	// ptszPath�����.

	// ���������̂�TRUE��Ԃ�.
	return TRUE;	// ���������̂Ŗ߂�l�Ƃ���TRUE��Ԃ�.

}

// �����o�֐�ShowSaveDialog
BOOL CFileDialog::ShowSaveDialog(HWND hwnd) {

	// �ϐ��̐錾�E������.
	OPENFILENAME ofn = { 0 };	// OPENFILENAME�\���̕ϐ�ofn��0�ŏ�����.
	TCHAR *ptszPath = new TCHAR[1024];	// ptszPath�𐶐�.
	wmemset(ptszPath, _T('\0'), 1024);	// 0�Ŗ��߂�.
	_tcscpy_s(ptszPath, m_tstrDefFileName.length() + 1, m_tstrDefFileName.c_str());	// �w��̃p�X���R�s�[.

	// ofn�ɒl���Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// �\���̂̃T�C�Y.
	ofn.hwndOwner = hwnd;	// �I�[�i�[�E�B���h�E.
	ofn.lpstrFile = ptszPath;	// �f�t�H���g�p�X.
	ofn.nMaxFile = 1024;	// MAX��1024.
	ofn.lpstrDefExt = m_tstrExt.c_str();	// �f�t�H���g�g���q.
	ofn.lpstrFilter = m_ptszFilter;	// �t�B���^��m_tszFilter���Z�b�g.
	ofn.Flags = m_dwFlags;	// �t���O

	// �t�@�C���I��.
	if (!GetSaveFileName(&ofn)) {	// GetSaveFileName�Ńt�@�C����I��.

		// �I�����Ȃ������ꍇ.(�L�����Z��)
		delete[] ptszPath;	// ptszPath�����.
		m_tstrPath = _T("");	// ""���Z�b�g.
		return FALSE;	// �������ĂȂ��̂Ŗ߂�l�Ƃ���FALSE��Ԃ�.

	}

	// �p�X���i�[.
	m_tstrPath = ptszPath;	// ptszPath��m_tstrPath�Ɋi�[.

	// �o�b�t�@�����.
	delete[] ptszPath;	// ptszPath�����.

	// ���������̂�TRUE��Ԃ�.
	return TRUE;	// ���������̂Ŗ߂�l�Ƃ���TRUE��Ԃ�.

}