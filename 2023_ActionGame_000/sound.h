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
		SOUND_LABEL_SE_SHOT,		//射撃
		SOUND_LABEL_SE_EXPLOSION,	//爆発
		SOUND_LABEL_SE_DAMAGE,		//ダメージ
		SOUND_LABEL_SE_777,			//当たり	
		SOUND_LABEL_SE_HORYU,		//保留音
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
