//=========================================================================================
//
// �T�E���h���� [sound.h]
// Author : takumi hinosawa
//
//=========================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//�T�E���h�N���X
//*****************************************************************************************
class CSound
{
public:

	//�T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM_GAME = 0,	//�Q�[��
		SOUND_LABEL_SE_SHOT,		//�ˌ�
		SOUND_LABEL_SE_EXPLOSION,	//����
		SOUND_LABEL_SE_DAMAGE,		//�_���[�W
		SOUND_LABEL_SE_777,			//������	
		SOUND_LABEL_SE_HORYU,		//�ۗ���
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// �T�E���h���̍\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
