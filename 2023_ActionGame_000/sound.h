//=========================================================================================
//
// サウンド処理 [sound.h]
// Author : takumi hinosawa
//
//=========================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//サウンドクラス
//*****************************************************************************************
class CSound
{
public:

	//サウンド一覧
	typedef enum
	{
		SOUND_LABEL_BGM_GAME = 0,	//ゲーム
		SOUND_LABEL_SE_JUMP,		//ジャンプ
		SOUND_LABEL_SE_2NDJUNP,		//二段ジャンプ
		SOUND_LABEL_SE_DOWN,		//ダウン
		SOUND_LABEL_SE_TITLE,		//タイトル
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// サウンド情報の構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};

#endif
