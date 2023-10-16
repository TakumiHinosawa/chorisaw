//=========================================================================================
//
//�L�[�{�[�h���͏���[input.cpp]
//Author;�����V����
//
//=========================================================================================
#include "input.h"

//*****************************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;		//�|�C���^�̏�����

//=========================================================================================
//�C���v�b�g�̃R���X�g���N�^
//=========================================================================================
CInput::CInput()
{
	//�N���A
	m_pDevice = NULL;
}

//=========================================================================================
//�C���v�b�g�̃f�X�g���N�^
//=========================================================================================
CInput::~CInput()
{

}

//=========================================================================================
//�C���v�b�g�̏���������
//=========================================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{//�g�p����Ă��Ȃ�������

		//DirectInput�I�u�W�F�N�g�̏�����
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

//=========================================================================================
//�C���v�b�g�̏I������
//=========================================================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Directinput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=========================================================================================
//�L�[�{�[�h�̃R���X�g���N�^
//=========================================================================================
CInputKeyboard::CInputKeyboard()
{
	// �e��ϐ�������
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateRipeat[0], 0, sizeof(m_aKeyStateRipeat));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=========================================================================================
//�L�[�{�[�h�̃f�X�g���N�^
//=========================================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=========================================================================================
//�L�[�{�[�h�̏�����
//=========================================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�C���v�b�g�̏���������
	CInput::Init(hInstance,hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//=========================================================================================
//�L�[�{�[�h�I������
//=========================================================================================
void CInputKeyboard::Uninit(void)
{
	//�I������
	CInput::Uninit();
}

//=========================================================================================
//�L�[�{�[�h�X�V����
//=========================================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//m_aKeyStateRipeat[nCntKey] = (m_aKeyState[nCntKey] & aKeyState[nCntKey]);		//�L�[�{�[�h�̃��s�[�g����ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//�L�[�{�[�h�̃g���K�[����ۑ�

			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];		//�L�[�{�[�h�̃����[�X����ۑ�


			m_aKeyState[nCntKey] = aKeyState[nCntKey];			//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=========================================================================================
//�L�[�{�[�h�̃v���X�����擾
//=========================================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//=========================================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//�L�[�{�[�h�̃��s�[�g�����擾
//=========================================================================================
bool CInputKeyboard::GetRipeat(int nKey)
{
	return (m_aKeyStateRipeat[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//�L�[�{�[�h�̃����[�X�����擾
//=========================================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//�Q�[���p�b�h�̃f�X�g���N�^
//=========================================================================================
CInputController::CInputController()
{
	//�������̏�����(�v���C���[��)
	for (int nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		memset(&m_aGamePadState[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateTrigger[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateRelease[nCntPad], 0, sizeof(XINPUT_STATE));
	}
}

//=========================================================================================
//�Q�[���p�b�h�̃f�X�g���N�^
//=========================================================================================
CInputController::~CInputController()
{

}

//=========================================================================================
//�Q�[���p�b�h����������
//=========================================================================================
HRESULT CInputController::Init(void)
{
	//XInput�̃X�e�[�g(�g�����)
	XInputEnable(true);

	return S_OK;
}

//=======================================================================
//�Q�[���p�b�h�̏I������
//=======================================================================
void CInputController::Uninit(void)
{
	//XInput�̃X�e�[�g(�g��Ȃ����)
	XInputEnable(false);
}

//=======================================================================
//�Q�[���p�b�h�̍X�V����
//=======================================================================
void CInputController::Update(void)
{
	//�ϐ��錾
	int nCntPad;

	XINPUT_STATE aGamePadState;			//�Q�[���p�b�h�̓��͏��

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCntPad, &aGamePadState) == ERROR_SUCCESS)
		{
			//�Q�[���p�b�h�̃g���K�[����ۑ�
			m_aGamePadStateTrigger[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons ^ aGamePadState.Gamepad.wButtons) & aGamePadState.Gamepad.wButtons;

			//���s�[�g���
			m_aGamePadStateRepeat[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons & aGamePadState.Gamepad.wButtons);

			//�����[�X���
			m_aGamePadStateRelease[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons | aGamePadState.Gamepad.wButtons) ^ aGamePadState.Gamepad.wButtons;

			//�Q�[���p�b�h�̃v���X����ۑ�
			m_aGamePadState[nCntPad] = aGamePadState;
		}
	}
}

//=======================================================================
//�W���C�X�e�B�b�N���擾
//=======================================================================
SHORT CInputController::GetJoyStickLX(int nPlayer)
{
	//����Ԃ�
	return m_aGamePadState[nPlayer].Gamepad.sThumbLX;
}

//=======================================================================
//�W���C�X�e�B�b�N���擾
//=======================================================================
SHORT CInputController::GetJoyStickLY(int nPlayer)
{
	//����Ԃ�
	return m_aGamePadState[nPlayer].Gamepad.sThumbLY;
}

//=======================================================================
//�W���C�X�e�B�b�N���擾
//=======================================================================
SHORT CInputController::GetJoyStickRX(int nPlayer)
{
	//����Ԃ�
	return m_aGamePadState[nPlayer].Gamepad.sThumbRX;
}

//=======================================================================
//�W���C�X�e�B�b�N���擾
//=======================================================================
SHORT CInputController::GetJoyStickRY(int nPlayer)
{
	//����Ԃ�
	return m_aGamePadState[nPlayer].Gamepad.sThumbRY;
}

//=======================================================================
//�Q�[���p�b�h�̃v���X�����擾
//=======================================================================
bool CInputController::GetPress(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadState[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//�Q�[���p�b�h�̃g���K�[�����擾
//=======================================================================
bool CInputController::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateTrigger[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//�Q�[���p�b�h�̃����[�X�����擾
//=======================================================================
bool CInputController::GetRelease(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateRelease[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//���s�[�g���擾
//=======================================================================
bool CInputController::GetRepeat(JOYKEY nKey, int nPlayer)
{
	return(m_aGamePadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//=======================================================================
//�U�����擾
//=======================================================================
void CInputController::GetVibration(int nValue, int nPlayer)
{
	m_aGamePadVibration[nPlayer].wLeftMotorSpeed = nValue;
	m_aGamePadVibration[nPlayer].wRightMotorSpeed = nValue;

	XInputSetState(m_aGamePadVibration[nPlayer].wLeftMotorSpeed, m_aGamePadVibration);
	XInputSetState(m_aGamePadVibration[nPlayer].wRightMotorSpeed, m_aGamePadVibration);

	DWORD controllerIndex = 0;

	DWORD result = XInputSetState(controllerIndex, m_aGamePadVibration);
}