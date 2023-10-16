//=========================================================================================
//
//���͏���
//Author:�����V����
//
//=========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include"main.h"
#include"Xinput.h"
#pragma comment(lib,"xinput.lib")

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define NUM_KEY_MAX			(256)			//�L�[�̍ő吔
#define NUM_PLAYER			(4)				//�v���C���[��

//*****************************************************************************************
//�N���X��`
//*****************************************************************************************

//�C���v�b�g�N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;		//�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;		//���̓f�o�C�X�ւ̃|�C���^
};

//�L�[�{�[�h�N���X
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRipeat(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�v���X�̏��
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//�L�[�{�[�h�g���K�[�̏��
	BYTE m_aKeyStateRipeat[NUM_KEY_MAX];				//�L�[�{�[�h���s�[�g�̏��
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//�L�[�{�[�h�����[�X�̏��
};

//�R���g���[���[�N���X
class CInputController : public CInput
{
public:
	typedef enum 
	{
		BUTTON_0 = 0,				// �\���� 
		BUTTON_1,					// �\����
		BUTTON_2,					// �\����
		BUTTON_3,					// �\����
		BUTTON_START,				// start
		BUTTON_BACK,				// back
		BUTTON_LS,					// ���X�e�B�b�N��������
		BUTTON_RS,					// �E�X�e�B�b�N��������
		BUTTON_LB,					// LB/5
		BUTTON_RB,					// RB/6
		BUTTON_10,					// ?
		BUTTON_11,					// ?
		BUTTON_A,					// A/3 
		BUTTON_B,					// B/4
		BUTTON_X,					// X/1
		BUTTON_Y,					// Y/2
		BUTTON_16,					// ?
		BUTTON_17,					// ?
		BUTTON_18,					// ?
		BUTTON_19,					// ?
		BUTTON_20,					// ?
		BUTTON_MAX
	} JOYKEY;

	CInputController();
	~CInputController();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY nKey, int nPlayer);
	bool GetTrigger(JOYKEY nKey, int nPlayer);
	bool GetRelease(JOYKEY nkey, int nPlayer);
	bool GetRepeat(JOYKEY nKey, int nPlayer);
	void GetVibration(int nValue,int nPlayer);
	SHORT GetJoyStickLX(int nPlayer);
	SHORT GetJoyStickLY(int nPlayer);
	SHORT GetJoyStickRX(int nPlayer);
	SHORT GetJoyStickRY(int nPlayer);

private:
	XINPUT_STATE m_aGamePadState[NUM_PLAYER];			//�Q�[���p�b�h�v���X�̏��
	XINPUT_STATE m_aGamePadStateTrigger[NUM_PLAYER];	//�Q�[���p�b�h�g���K�[�̏��
	XINPUT_STATE m_aGamePadStateRelease[NUM_PLAYER];	//�Q�[���p�b�h�����[�X�̏��
	XINPUT_STATE m_aGamePadStateRepeat[NUM_PLAYER];		//�Q�[���p�b�h
	XINPUT_VIBRATION m_aGamePadVibration[NUM_PLAYER];
};

#endif
