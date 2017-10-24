// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <cstring>	// C�����񏈗�.
#include <wchar.h>	// ���C�h����.
// �Ǝ��̃w�b�_
#include "TextFile.h"	// CTextFile

// �R���X�g���N�^CTextFile
CTextFile::CTextFile() : CBinaryFile(){

	// �����o�̏�����
	m_ptszRawText = NULL;	// m_ptszRawText��NULL���Z�b�g.
	m_dwLen = 0;	// m_dwLen��0���Z�b�g.
	m_NewLine = NEW_LINE_NONE;	// m_NewLine��NEW_LINE_NONE���Z�b�g.
	m_BOMType = BOM_NONE;	// BOM_NONE.
	m_Encoding = ENCODING_NONE;	// ENCODING_NONE.
	m_tstrText.clear();	// �N���A.

}

// �f�X�g���N�^CTextFile
CTextFile::~CTextFile() {

	// �t�@�C���ƃo�b�t�@���N���A����.
	Close();	// �t�@�C�������.
	Clear();	// �o�b�t�@��j��.

}

// �����o�֐�Read
BOOL CTextFile::Read(LPCTSTR lpctszFileName) {

	// �t�@�C���������������.
	CBinaryFile::Clear();	// �o�b�t�@�N���A
	CFile::Close();	// �n���h�����Ƃ���.

	// �w�肳�ꂽ�t�@�C�����̃t�@�C����ǂݍ���.
	if (CBinaryFile::Read(lpctszFileName)) {	// �ǂݍ��݂ɐ���������.

		// �����R�[�h����.
		CheckBOM();	// BOM�̃`�F�b�N.
		if (m_BOMType == BOM_TYPE_UTF16LE) {	// UTF-16LE�̏ꍇ.
			
			// �o�C�i������UTF16LE�e�L�X�g�ւ̕ϊ�.
			m_Encoding = ENCODING_UTF16LE;	// ENCODING_UTF16LE.
			DecodeUtf16LE();	// DecodeUtf16LE��m_ptszRawText��TCHAR(���s�R�[�h���ϊ�)�e�L�X�g���i�[�����.
			CheckNewLine();	// ���s�R�[�h�̎擾.
			GetText();	// CRLF�̃e�L�X�g�������o�ɃZ�b�g.

			// �ǂݍ��ݐ����Ȃ̂�TRUE.
			return TRUE;	// TRUE��Ԃ�.

		}
		else if (m_BOMType == BOM_TYPE_UTF8) {	// UTF-8�̏ꍇ.

			// �o�C�i������UTF-8�e�L�X�g�ւ̕ϊ�.
			m_Encoding = ENCODING_UTF8;	// ENCODING_UTF8.
			DecodeUtf8();	// DecodeUtf8��m_ptszRawText��TCHAR(���s�R�[�h���ϊ�)�e�L�X�g���i�[�����.
			CheckNewLine();	// ���s�R�[�h�̎擾.
			GetText();	// CRLF�̃e�L�X�g�������o�ɃZ�b�g.

			// �ǂݍ��ݐ����Ȃ̂�TRUE.
			return TRUE;	// TRUE��Ԃ�.

		}
		else {	// ����ȊO�̏ꍇ��Shift_JIS�Ƃ݂Ȃ�.

			// �o�C�i������ShiftJIS�e�L�X�g�ւ̕ϊ�.
			m_Encoding = ENCODING_SHIFTJIS;	// ENCODING_SHIFTJIS.
			DecodeShiftJis();	// DecodeShiftJis��m_ptszRawText��TCHAR(���s�R�[�h���ϊ�)�e�L�X�g���i�[�����.
			CheckNewLine();	// ���s�R�[�h�̎擾.
			GetText();	// CRLF�̃e�L�X�g�������o�ɃZ�b�g.

			// �ǂݍ��ݐ����Ȃ̂�TRUE.
			return TRUE;	// TRUE��Ԃ�.

		}

	}

	// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
	return FALSE;	// FALSE��Ԃ�.

}

// �����o�֐�GetTextUtf16LE
void CTextFile::DecodeUtf16LE() {

	// �e�L�X�g�z��̐���.
	m_ptszRawText = new TCHAR[m_dwSize - 2 + 1];	// (�o�C�g�� - 2 + 1)����TCHAR�z�񂪂���Ώ\�����Ǝv����.
	wmemset(m_ptszRawText, _T('\0'), m_dwSize - 2 + 1);	// wmemset��m_ptszRawText��0�Ŗ��߂�.
	memcpy(m_ptszRawText, m_pBytes + 2, m_dwSize - 2);	// memcpy��m_pBytes��3�o�C�g�ڂ���m_ptszRawText�ɃR�s�[.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslen�̒l��m_dwLen�Ɋi�[.

}

// �����o�֐�DecodeShiftJis
void CTextFile::DecodeShiftJis() {

	// �����R�[�h�ϊ�.
	int len = MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, NULL, NULL);	// MultiByteToWideChar�Ńo�C�g��̕ϊ��ɕK�v�ȃo�b�t�@�̒���len�����߂�.
	m_ptszRawText = new TCHAR[len];	// len�̕���TCHAR���I�z���p�ӂ�, �|�C���^��m_ptszRawText�Ɋi�[.
	wmemset(m_ptszRawText, _T('\0'), len);	// wmemset��m_ptszRawText��0�Ŗ��߂�.
	MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, m_ptszRawText, len);	// MultiByteToWideChar�Ń}���`�o�C�g�������烏�C�h�����ւ̕ϊ�.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslen�̒l��m_dwLen�Ɋi�[.

}

// �����o�֐�DecodeUtf8
void CTextFile::DecodeUtf8() {

	// �����R�[�h�ϊ�.
	int len = MultiByteToWideChar(CP_UTF8, 0, (char *)(m_pBytes + 3), -1, NULL, NULL);	// MultiByteToWideChar�Ńo�C�g��̕ϊ��ɕK�v�ȃo�b�t�@�̒���len�����߂�.(BOM��3�o�C�g����̂Ő擪��3�o�C�g�悩��n��.)
	m_ptszRawText = new TCHAR[len];	// len�̕���TCHAR���I�z���p�ӂ�, �|�C���^��m_ptszRawText�Ɋi�[.
	wmemset(m_ptszRawText, _T('\0'), len);	// wmemset��m_ptszRawText��0�Ŗ��߂�.
	MultiByteToWideChar(CP_UTF8, 0, (char *)(m_pBytes + 3), -1, m_ptszRawText, len);	// MultiByteToWideChar�Ń}���`�o�C�g�������烏�C�h�����ւ̕ϊ�.
	m_dwLen = _tcslen(m_ptszRawText);	// _tcslen�̒l��m_dwLen�Ɋi�[.

}

// �����o�֐�CheckBOM
void CTextFile::CheckBOM() {

	// BOM�̔���.
	if (m_dwSize >= 2 && m_pBytes[0] == 0xff && m_pBytes[1] == 0xfe) {	// UTF-16LE�̏ꍇ.
		m_BOMType = BOM_TYPE_UTF16LE;	// BOM_TYPE_UTF16LE���Z�b�g.
	}
	else if (m_dwSize >= 3 && m_pBytes[0] == 0xef && m_pBytes[1] == 0xbb && m_pBytes[2] == 0xbf) {	// UTF-8�̏ꍇ.
		m_BOMType = BOM_TYPE_UTF8;	// BOM_TYPE_UTF8���Z�b�g.
	}
	else {	// ����ȊO.
		m_BOMType = BOM_NONE;	// �Ƃ肠����BOM_NONE�Ƃ���.
	}

}

// �����o�֐�CheckNewLine
void CTextFile::CheckNewLine() {

	// �ꎞ�I��tstrTemp�Ɋi�[.
	tstring tstrTemp = m_ptszRawText;	// tstrTemp��m_ptszRawText�ŏ�����.
	size_t p1 = tstrTemp.find_first_of(_T('\r'));	// tstrTemp.find_first_of��'\r'�����邩�𒲂ׂ�.
	size_t p2 = 0;	// sizet_t�^p2.
	if (p1 != -1) {	// '\r'������.
		p2 = tstrTemp.find_first_of(_T('\n'), p1);	// tstrTemp.find_first_of��'\r'�̌��'\n'�����邩�𒲂ׂ�.
		if (p2 != -1) {	// '\n'������.
			m_NewLine = NEW_LINE_CRLF;	// NEW_LINE_CRLF���Z�b�g.(CRLF�̏ꍇ�͂��̂܂�.)
		}
		else {	// '\r'����.
			m_NewLine = NEW_LINE_CR;	// NEW_LINE_CR���Z�b�g.
		}
	}
	else {	// '\r'�͂Ȃ�.
		p2 = tstrTemp.find_first_of(_T('\n'));	// tstrTemp.find_first_of��'\n'�����邩�𒲂ׂ�.
		if (p2 != -1) {	// '\n'������.
			m_NewLine = NEW_LINE_LF;	// NEW_LINE_LF���Z�b�g.
		}
		else {	// '\n'���Ȃ�.
			m_NewLine = NEW_LINE_NONE;	// NEW_LINE_NONE���Z�b�g.
		}
	}

}

// �����o�֐�GetText
void CTextFile::GetText() {

	// �ϐ��̐錾.
	tstring tstrTemp;	// �ꎞ�I�Ƀe�L�X�g��ێ�����tstrTemp.

	// ��������tstrTemp�ɓ����.
	tstrTemp = m_ptszRawText;	// m_ptszRawText��tstrTemp�ɑ��.

	// ���s�R�[�h��CRLF�ɓ���.
	if (m_NewLine == NEW_LINE_CR) {	// CR.
		replace(tstrTemp, _T("\r"), _T("\r\n"));	// replace��"\r\n"�ɒu��.
	}
	else if (m_NewLine == NEW_LINE_LF) {	// LF.
		replace(tstrTemp, _T("\n"), _T("\r\n"));	// replace��"\r\n"�ɒu��.
	}
	
	// CRLF�ɂ����e�L�X�g��m_tstrText�ɓ����.
	m_tstrText = tstrTemp;	//tstrTemp��m_tstrText�Ɋi�[.

}

// �����o�֐�replace
void CTextFile::replace(tstring & target, const tstring & before, const tstring & after) {

	// tstring�̕�����u��.
	tstring::size_type pos = target.find(before);	// target�ōŏ���before�����������ꏊ��pos�Ɋi�[.
	while (pos != tstring::npos) {
		target.replace(pos, before.size(), after);	// target��before����after�ɒu��.
		pos = target.find(before, pos + after.size());	// ����pos��T��.
	}

}

// �����o�֐�SetText
void CTextFile::SetText(tstring tstrText) {

	// �e�L�X�g�̃Z�b�g.
	m_tstrText = tstrText;	// m_tstrText��tstrText���Z�b�g.

}

// �����o�֐�SetNewLine
void CTextFile::SetNewLine(NEW_LINE newline) {

	// ���s�R�[�h�̃Z�b�g.
	m_NewLine = newline;	// m_NewLine��newline���Z�b�g.

}

// �����o�֐�SetEncoding
void CTextFile::SetEncoding(ENCODING encoding, BOM_TYPE bomtype) {

	// �����R�[�h��BOM�̃Z�b�g.
	m_Encoding = encoding;	// m_Encoding��encoding���Z�b�g.
	m_BOMType = bomtype;	// m_BOMType��bomtype���Z�b�g.

}

// �����o�֐�ReplaceNewLine
tstring CTextFile::ReplaceNewLine(tstring str, NEW_LINE newline) {

	// ���s�R�[�h��u��������.
	tstring after;	// �u����after.
	if (newline == NEW_LINE_CR) {
		after = _T("\r");	// after��"\r".
	}
	else if (newline == NEW_LINE_LF) {
		after = _T("\n");	// after��"\n".
	}
	else if (newline == NEW_LINE_CRLF) {
		after = _T("\r\n");	// after��"\r\n".
	}
	replace(str, _T("\r\n"), after);	// replace��before����after�ɒu��.
	return str;	// str��Ԃ�.

}

// �����o�֐�SetBytesUtf16LEWithBOM.
void CTextFile::SetBytesUtf16LEWithBOM(tstring text) {

	// �o�C�g��̃Z�b�g.
	BYTE *pByteWithBOM = new BYTE[(text.length() + 1) * 2];	// BOM�t���o�C�g����i�[����z��pByteWithBOM.
	pByteWithBOM[0] = 0xff;	// 0�Ԗڂ�0xff.
	pByteWithBOM[1] = 0xfe;	// 1�Ԗڂ�0xfe.
	memcpy(pByteWithBOM + 2, (BYTE *)text.c_str(), text.length() * 2);	// pByteWithBOM + 2�ȍ~�ɃR�s�[.
	Set(pByteWithBOM, (text.length() + 1) * 2);	// pByteWithBOM���Z�b�g.(�T���Q�[�g�y�A��Ή�.)
	delete[] pByteWithBOM;	// delete��pByteWithBOM�����.

}

// �����o�֐�SetBytesShiftJIS.
void CTextFile::SetBytesShiftJIS(tstring text) {

	// �o�C�g��̃Z�b�g.
	int len = WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, NULL, 0, NULL, NULL);	// �ϊ��ɕK�v�ȃo�b�t�@�̒������擾.
	BYTE *pByte = new BYTE[len];	// �o�C�g����i�[����z��pByte.
	ZeroMemory(pByte, sizeof(BYTE) * len);	// pByte��0�Ŗ��߂�.
	WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, (char *)pByte, len, NULL, NULL);	// ���C�h��������}���`�o�C�g�����ւ̕ϊ�.
	if (len > 0) {	// len��0���傫���ꍇ.
		Set(pByte, len - 1);	// pByte��(len - 1)���Z�b�g.
	}
	delete[] pByte;	// delete��pByte�����.

}

// �����o�֐�SetBytesUtf8WithBOM
void CTextFile::SetBytesUtf8WithBOM(tstring text) {

	// �o�C�g��̃Z�b�g.
	int len = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, NULL, 0, NULL, NULL);	// �ϊ��ɕK�v�ȃo�b�t�@�̒������擾.
	BYTE *pByte = new BYTE[len + 3];	// �o�C�g����i�[����z��pByte.(BOM�̒������܂߂��len + 3.)
	ZeroMemory(pByte, sizeof(BYTE) * (len + 3));	// pByte��0�Ŗ��߂�.
	pByte[0] = 0xef;	// 0�Ԗڂ�0xef.
	pByte[1] = 0xbb;	// 1�Ԗڂ�0xbb.
	pByte[2] = 0xbf;	// 2�Ԗڂ�0xbf.
	WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, (char *)(pByte + 3), len, NULL, NULL);	// ���C�h��������}���`�o�C�g�����ւ̕ϊ�.
	if (len > 0) {	//len��0���傫���ꍇ.
		Set(pByte, len + 2);	// pByte��(len + 2)���Z�b�g.
	}
	delete[] pByte;	// delete��pByte�����.

}

// �����o�֐�ResetRawText
void CTextFile::ResetRawText(tstring text) {

	// ���[�e�L�X�g�̍Đ���.
	delete[] m_ptszRawText;	// ���[�e�L�X�g�j��.
	m_ptszRawText = new TCHAR[text.length() + 1];	// text.length() + 1�̔z�񐶐�.
	wmemset(m_ptszRawText, _T('\0'), text.length() + 1);	// wmemset��0�Ŗ��߂�.
	_tcscpy_s(m_ptszRawText, text.length() + 1, text.c_str());
	m_dwLen = _tcslen(m_ptszRawText);	// ������m_dwLen.

}

// �����o�֐�Write
BOOL CTextFile::Write(LPCTSTR lpctszFileName) {

	// �t�@�C���������������.
	CBinaryFile::Clear();	// �o�b�t�@�N���A
	CFile::Close();	// �n���h�����Ƃ���.

	// �ꎞ�ϐ�tstrTemp�ɉ��s�R�[�h��u���������e�L�X�g���i�[.
	tstring tstrTemp = ReplaceNewLine(m_tstrText, m_NewLine);	// ReplaceNewLine�Œu�����������̂�tstrTemp�Ɋi�[.

	// �e�L�X�g����o�C�g��𐶐�.
	if (m_Encoding == ENCODING_UTF16LE) {	// UTF16LE�̏ꍇ.
		if (m_BOMType == BOM_TYPE_UTF16LE) {	// BOM�t��.
			SetBytesUtf16LEWithBOM(tstrTemp);	// tstrTemp��UTF16LE�ɕϊ�����, BOM�t���o�C�g�Ƃ��ăZ�b�g.
			if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Write�ŏ������ݐ���.
				ResetRawText(tstrTemp);	// ���[�e�L�X�g�̍�蒼��.
				// �������ݐ���.
				return TRUE;	// TRUE��Ԃ�.
			}
			else {

				// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
				return FALSE;	// FALSE��Ԃ�.

			}
		}
		else {

			// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
			return FALSE;	// FALSE��Ԃ�.

		}
	}
	else if (m_Encoding == ENCODING_UTF8) {	// UTF8�̏ꍇ.
		if (m_BOMType == BOM_TYPE_UTF8) {	// BOM�t��.
			SetBytesUtf8WithBOM(tstrTemp);	// tstrTemp��UTF8�ɕϊ�����, BOM�t���o�C�g�Ƃ��ăZ�b�g.
			if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Write�ŏ������ݐ���.
				ResetRawText(tstrTemp);	// ���[�e�L�X�g�̍�蒼��.
				// �������ݐ���.
				return TRUE;	// TRUE��Ԃ�.
			}
			else {

				// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
				return FALSE;	// FALSE��Ԃ�.

			}
		}
		else {

			// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
			return FALSE;	// FALSE��Ԃ�.

		}
	}
	else if (m_Encoding == ENCODING_SHIFTJIS) {	// SHIFTJIS�̏ꍇ.
		SetBytesShiftJIS(tstrTemp);	// tstrTemp��SHIFTJIS�ɕϊ�����, �o�C�g�񂪃Z�b�g.
		if (CBinaryFile::Write(lpctszFileName)) {	// CBinaryFile::Write�ŏ������ݐ���.
			ResetRawText(tstrTemp);	// ���[�e�L�X�g�̍�蒼��.
			// �������ݐ���.
			return TRUE;	// TRUE��Ԃ�.
		}
		else {

			// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
			return FALSE;	// FALSE��Ԃ�.

		}
	}
	else {

		// �ǂݍ��ݎ��s�Ȃ̂�FALSE.
		return FALSE;	// FALSE��Ԃ�.

	}

}

// �����o�֐�Clear
void CTextFile::Clear() {

	// �e�L�X�g�z��̉��.
	if (m_ptszRawText != NULL) {	// m_ptszRawText��NULL�łȂ���.
		delete[] m_ptszRawText;	// delete[]�ŉ��.
		m_ptszRawText = NULL;		// m_ptszRawText��NULL���Z�b�g.
	}
	m_dwLen = 0;	// m_dwLen��0���Z�b�g.
	m_NewLine = NEW_LINE_NONE;	// m_NewLine��NEW_LINE_NONE���Z�b�g.
	m_BOMType = BOM_NONE;	// BOM_NONE.
	m_Encoding = ENCODING_NONE;	// ENCODING_NONE.
	m_tstrText.clear();	// �N���A.

	// �o�C�i���f�[�^���N���A.
	CBinaryFile::Clear();	// CBinaryFile::Clear�ŃN���A.

}