// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <windows.h>	// �W��WindowsAPI
#include <tchar.h>		// TCHAR�^
// �Ǝ��̃w�b�_
#include "File.h"	// CFile

// �R���X�g���N�^CFile
CFile::CFile() {

	// �����o�̏�����
	m_hFile = NULL;	// m_hFile��NULL���Z�b�g.
	m_tstrFileName.clear();	// m_tstrFileName.clear�ŃN���A.

}

// �f�X�g���N�^~CFile
CFile::~CFile() {

	// �����o�̏I������
	if (m_hFile != NULL) {	// m_hFile��NULL�łȂ��ꍇ.
		Close();	// Close�ŕ���.
	}

}

// �����o�֐�Open
BOOL CFile::Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition) {

	// �����o�̃Z�b�g.
	m_tstrFileName = lpctszFileName;	// m_tstrFileName��lpctszFileName���Z�b�g.

	// �t�@�C���n���h���̎擾.
	m_hFile = CreateFile(m_tstrFileName.c_str(), dwDesiredAccess, FILE_SHARE_READ, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);	// CreateFile��m_tstrFileName�̃t�@�C���n���h�����擾��, m_hFile�Ɋi�[.
	if (m_hFile == INVALID_HANDLE_VALUE) {	// ���s�Ȃ�.
		return FALSE;	// FALSE��Ԃ�.
	}

	// �����Ȃ�TRUE.
	return TRUE;	// �����Ȃ�TRUE��Ԃ�.

}

// �����o�֐�Close
void CFile::Close() {

	// �t�@�C���n���h�������.
	if (m_hFile != NULL) {	// �n���h�����c���Ă�����.
		CloseHandle(m_hFile);	// CloseHandle��m_hFile�����.
		m_hFile = NULL;	// m_hFile��NULL���Z�b�g.
	}

	// �t�@�C�������N���A.
	m_tstrFileName.clear();	// m_tstrFileName.clear�Ńt�@�C�������N���A.

}

// �����o�֐�Read
DWORD CFile::Read(LPVOID lpBuf, DWORD dwBytes) {

	// �ϐ��̏�����.
	DWORD dwReadBytes = 0;	// �ǂݍ��񂾃o�C�g��dwReadBytes��0�ɏ�����.

	// �t�@�C����ǂݍ���.
	ReadFile(m_hFile, lpBuf, dwBytes, &dwReadBytes, NULL);	// ReadFile�œǂݍ���.

	// �ǂݍ��񂾃o�C�g����Ԃ�.
	return dwReadBytes;	// dwReadBytes��Ԃ�.

}

// �����o�֐�Write
DWORD CFile::Write(LPVOID lpBuf, DWORD dwBytes) {

	// �ϐ��̏�����.
	DWORD dwWrittenBytes = 0;	// �������񂾃o�C�g��dwWrittenBytes��0�ɏ�����.

	// �t�@�C������������.
	WriteFile(m_hFile, lpBuf, dwBytes, &dwWrittenBytes, NULL);	// WriteFile�ŏ�������.

	// �������񂾃o�C�g����Ԃ�.
	return dwWrittenBytes;	// dwWrittenBytes��Ԃ�.

}