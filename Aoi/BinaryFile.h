// 二重インクルード防止
#pragma once	// #pragma onceで二重インクルード防止.

// ヘッダのインクルード
// 独自のヘッダ
#include "File.h"	// CFile

// バイナリファイルクラス
class CBinaryFile : public CFile {

	// publicメンバ
	public:

		// publicメンバ変数
		BYTE *m_pBytes;	// バイト列へのポインタm_pBytes.
		DWORD m_dwSize;	// ファイルサイズm_dwSize.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CBinaryFile();	// コンストラクタCBinaryFile
		virtual ~CBinaryFile();	// デストラクタ~CBinaryFile

		// メンバ関数
		virtual BOOL Read(LPCTSTR lpctszFileName);	// バイナリの読み込み関数Read
		virtual BOOL Write(LPCTSTR lpctszFileName);	// バイナリの書き込み関数Write
		void Set(BYTE *pBytes, DWORD dwSize);	// バッファのセット関数Set
		void Clear();	// バッファのクリア関数Clear

};