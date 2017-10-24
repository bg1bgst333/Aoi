// ��d�C���N���[�h�h�~
#pragma once	// #pragma once�œ�d�C���N���[�h�h�~.

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <string>	// std::string
// �Ǝ��̃w�b�_
#include "BinaryFile.h"	// CBinaryFile

// �}�N���̒�`
// UNICODE�؂�ւ�
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// �e�L�X�g�t�@�C���N���X
class CTextFile : public CBinaryFile {

	// public�����o
	public:

		// �񋓌^�̒�`.
		// BOM
		typedef enum TAG_BOM_TYPE {
			BOM_NONE,
			BOM_TYPE_UTF16LE,
			BOM_TYPE_UTF16BE,
			BOM_TYPE_UTF8
		} BOM_TYPE;
		// ���s
		typedef enum TAG_NEW_LINE {
			NEW_LINE_NONE,
			NEW_LINE_LF,
			NEW_LINE_CR,
			NEW_LINE_CRLF
		} NEW_LINE;
		// �����R�[�h
		typedef enum TAG_ENCODING {
			ENCODING_NONE,
			ENCODING_UTF16LE,
			ENCODING_SHIFTJIS,
			ENCODING_UTF8
		} ENCODING;

		// public�����o�ϐ�
		TCHAR *m_ptszRawText;	// TCHAR�Ƀf�R�[�h�ς݂̃e�L�X�g�ւ̃|�C���^m_ptszRawText.(���s�R�[�h�͌��̂܂�.)
		tstring m_tstrText;		// ���s�R�[�h��CRLF�̃e�L�X�gm_tstrText.
		DWORD m_dwLen;	// �e�L�X�g�̒���m_dwLen.
		BOM_TYPE m_BOMType;	// BOM�^�C�vm_BOMType.
		NEW_LINE m_NewLine;	// ���s�R�[�hm_NewLine.
		ENCODING m_Encoding;	// �����R�[�hm_Encoding.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CTextFile();	// �R���X�g���N�^CTextFile
		virtual ~CTextFile();	// �R���X�g���N�^~CTextFile
		virtual BOOL Read(LPCTSTR lpctszFileName);	// �e�L�X�g�̓ǂݍ��݊֐�Read.
		void DecodeUtf16LE();	// Utf16LE�̓ǂݍ��݊֐�DecodeUtf16LE.
		void DecodeShiftJis();	// ShiftJis�̓ǂݍ��݊֐�DecodeShiftJis.
		void DecodeUtf8();		// Utf8�̓ǂݍ��݊֐�DecodeUtf8.
		void CheckBOM();	// BOM�̃`�F�b�N�֐�CheckBOM.
		void CheckNewLine();	// ���s�̃`�F�b�N�y��CRLF�ւ̏C�����s���֐�CheckNewLine.
		void GetText();	// �e�L�X�g���擾����֐�GetText.(���s�R�[�h��CRLF�ɕύX�ς�.)
		void replace(tstring &target, const tstring &before, const tstring &after);	// tstring�̒u���֐�replace.
		void SetText(tstring tstrText);	// �e�L�X�g���Z�b�g����֐�SetText.
		void SetNewLine(NEW_LINE newline);	// ���s���Z�b�g����֐�SetNewLine.
		void SetEncoding(ENCODING encoding, BOM_TYPE bomtype);	// �����R�[�h���Z�b�g����֐�SetEncoding.
		tstring ReplaceNewLine(tstring str, NEW_LINE newline);	// �w��̃e�L�X�g�̉��s�R�[�h��u�����������̂�Ԃ��֐�ReplaceNewLine.
		void SetBytesUtf16LEWithBOM(tstring text);	// BOM�t��UTF16LE�̃o�C�g����Z�b�g����֐�SetBytesUtf16LEWithBOM.
		void SetBytesShiftJIS(tstring text);	// ShiftJIS�̃o�C�g����Z�b�g����֐�SetBytesShiftJIS.
		void SetBytesUtf8WithBOM(tstring text);	// BOM�t��UTF8�̃o�C�g����Z�b�g����֐�SetBytesUtf8WithBOM.
		void ResetRawText(tstring text);	// �w�肳�ꂽ�e�L�X�g�Ƀ��[�e�L�X�g�����Z�b�g����.
		virtual BOOL Write(LPCTSTR lpctszFileName);	// �e�L�X�g�̏������݊֐�Write.
		void Clear();	// �o�b�t�@�̃N���A�֐�Clear

};