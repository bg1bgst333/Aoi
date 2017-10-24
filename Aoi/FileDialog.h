// ��d�C���N���[�h�h�~
#pragma once	// #pragma once�œ�d�C���N���[�h�h�~

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <cstring>	// C�����񏈗�
#include <string>	// std::string
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI

// �}�N���̒�`
// UNICODE�؂�ւ�
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// �t�@�C���_�C�A���O�N���XCFileDialog
class CFileDialog {

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrPath;	// tstring�^�t�@�C���p�Xm_tstrPath
		tstring m_tstrDefFileName;	// tstring�^�t�@�C����m_tstrDefName
		tstring m_tstrExt;	// tstring�^�f�t�H���g�g���qm_tstrExt
		TCHAR *m_ptszFilter;	// TCHAR�^�t�B���^������ւ̃|�C���^m_ptszFilter
		DWORD m_dwFlags;	// DWORD�^�t���Om_dwFlags

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags);	// �R���X�g���N�^CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags)
		virtual ~CFileDialog();	// �f�X�g���N�^~CFileDialog
		BOOL ShowOpenDialog(HWND hwnd);	// "�J��"�_�C�A���O�̕\��ShowOpenDialog
		BOOL ShowSaveDialog(HWND hwnd);	// "���O��t���ĕۑ�"�_�C�A���O�̕\��ShowSaveDialog

};