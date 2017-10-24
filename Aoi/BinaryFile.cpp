// ヘッダのインクルード
// 独自のヘッダ
#include "BinaryFile.h"	// CBinaryFile

// コンストラクタCBinaryFile
CBinaryFile::CBinaryFile() : CFile(){

	// メンバの初期化
	m_pBytes = NULL;	// m_pBytesをNULLにセット.
	m_dwSize = 0;		// m_dwSizeを0にセット.

}

// デストラクタ~CBinaryFile
CBinaryFile::~CBinaryFile() {

	// ファイルとバッファをクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

}

// メンバ関数Read
BOOL CBinaryFile::Read(LPCTSTR lpctszFileName) {

	// いったんファイルを閉じて, バッファもクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

	// ファイルのオープン
	BOOL bRet = Open(lpctszFileName, GENERIC_READ, OPEN_EXISTING);	// Openで指定のファイルを開く.
	if (bRet) {	// 成功.

		// ファイルサイズの取得.
		DWORD dwSize = GetFileSize(m_hFile, NULL);	// GetFileSizeでサイズを取得し, dwSizeに格納.

		// バッファの作成.
		m_pBytes = new BYTE[dwSize + 1];	// newでdwSize + 1のバイト列を作成し, ポインタをm_pBytesに格納.
		ZeroMemory(m_pBytes, dwSize + 1);	// ZeroMemoryでm_pBytesを(dwSize + 1)分, 0で埋める.

		// ファイルの読み込み.
		m_dwSize = CFile::Read(m_pBytes, dwSize);	// CFile::Readでデータを読み込む.
		if (m_dwSize == dwSize) {	// 全て読み込めたら.
			return TRUE;	// 成功.
		}

	}

	// 失敗.
	return FALSE;	// FALSEを返す.

}

// メンバ関数Write
BOOL CBinaryFile::Write(LPCTSTR lpctszFileName) {

	// ファイルのオープン
	BOOL bRet = Open(lpctszFileName, GENERIC_WRITE, CREATE_ALWAYS);	// Openで指定のファイルを開く.
	if (bRet) {	// 成功.

		// ファイルの書き込み.
		CFile::Write(m_pBytes, m_dwSize);	// CFile::Writeでデータを書き込む.

	}

	// bRetで成功かどうかがわかる.
	return bRet;	// bRetを返す.

}

// メンバ関数Set
void CBinaryFile::Set(BYTE * pBytes, DWORD dwSize) {

	// バッファをクリアする.
	Clear();	// バッファを破棄.

	// メンバにセット.
	m_dwSize = dwSize;	// m_dwSizeにdwSizeをセット.

	// バッファの作成.
	m_pBytes = new BYTE[m_dwSize + 1];	// newでm_dwSize + 1のバイト列を作成し, ポインタをm_pBytesに格納.
	ZeroMemory(m_pBytes, m_dwSize + 1);	// ZeroMemoryでm_pBytesを(m_dwSize + 1)分, 0で埋める.

	// データのコピー.
	CopyMemory(m_pBytes, pBytes, m_dwSize);	// CopyMemoryでコピー.

}

// メンバ関数Clear
void CBinaryFile::Clear() {

	// バッファの破棄.
	if (m_pBytes != NULL) {	// バッファが残っていたら.
		delete[] m_pBytes;	// delete[]でm_pBytesを解放.
		m_pBytes = NULL;	// m_pBytesにNULLをセット.
	}
	m_dwSize = 0;	// サイズも0にする.

}