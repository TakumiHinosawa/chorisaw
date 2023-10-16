//=========================================================================================
//
//キーボード入力処理[input.cpp]
//Author;日野澤匠泉
//
//=========================================================================================
#include "input.h"

//*****************************************************************************************
//静的メンバ変数
//*****************************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;		//ポインタの初期化

//=========================================================================================
//インプットのコンストラクタ
//=========================================================================================
CInput::CInput()
{
	//クリア
	m_pDevice = NULL;
}

//=========================================================================================
//インプットのデストラクタ
//=========================================================================================
CInput::~CInput()
{

}

//=========================================================================================
//インプットの初期化処理
//=========================================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{//使用されていなかったら

		//DirectInputオブジェクトの初期化
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

//=========================================================================================
//インプットの終了処理
//=========================================================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();			//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Directinputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=========================================================================================
//キーボードのコンストラクタ
//=========================================================================================
CInputKeyboard::CInputKeyboard()
{
	// 各種変数初期化
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateRipeat[0], 0, sizeof(m_aKeyStateRipeat));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=========================================================================================
//キーボードのデストラクタ
//=========================================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=========================================================================================
//キーボードの初期化
//=========================================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//インプットの初期化処理
	CInput::Init(hInstance,hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//強調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//=========================================================================================
//キーボード終了処理
//=========================================================================================
void CInputKeyboard::Uninit(void)
{
	//終了処理
	CInput::Uninit();
}

//=========================================================================================
//キーボード更新処理
//=========================================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];			//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//m_aKeyStateRipeat[nCntKey] = (m_aKeyState[nCntKey] & aKeyState[nCntKey]);		//キーボードのリピート情報を保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//キーボードのトリガー情報を保存

			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];		//キーボードのリリース情報を保存


			m_aKeyState[nCntKey] = aKeyState[nCntKey];			//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();			//キーボードへのアクセス権を獲得
	}
}

//=========================================================================================
//キーボードのプレス情報を取得
//=========================================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//キーボードのトリガー情報を取得
//=========================================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//キーボードのリピート情報を取得
//=========================================================================================
bool CInputKeyboard::GetRipeat(int nKey)
{
	return (m_aKeyStateRipeat[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//キーボードのリリース情報を取得
//=========================================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=========================================================================================
//ゲームパッドのデストラクタ
//=========================================================================================
CInputController::CInputController()
{
	//メモリの初期化(プレイヤー分)
	for (int nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		memset(&m_aGamePadState[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateTrigger[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateRelease[nCntPad], 0, sizeof(XINPUT_STATE));
	}
}

//=========================================================================================
//ゲームパッドのデストラクタ
//=========================================================================================
CInputController::~CInputController()
{

}

//=========================================================================================
//ゲームパッド初期化処理
//=========================================================================================
HRESULT CInputController::Init(void)
{
	//XInputのステート(使う状態)
	XInputEnable(true);

	return S_OK;
}

//=======================================================================
//ゲームパッドの終了処理
//=======================================================================
void CInputController::Uninit(void)
{
	//XInputのステート(使わない状態)
	XInputEnable(false);
}

//=======================================================================
//ゲームパッドの更新処理
//=======================================================================
void CInputController::Update(void)
{
	//変数宣言
	int nCntPad;

	XINPUT_STATE aGamePadState;			//ゲームパッドの入力情報

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCntPad, &aGamePadState) == ERROR_SUCCESS)
		{
			//ゲームパッドのトリガー情報を保存
			m_aGamePadStateTrigger[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons ^ aGamePadState.Gamepad.wButtons) & aGamePadState.Gamepad.wButtons;

			//リピート情報
			m_aGamePadStateRepeat[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons & aGamePadState.Gamepad.wButtons);

			//リリース情報
			m_aGamePadStateRelease[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons | aGamePadState.Gamepad.wButtons) ^ aGamePadState.Gamepad.wButtons;

			//ゲームパッドのプレス情報を保存
			m_aGamePadState[nCntPad] = aGamePadState;
		}
	}
}

//=======================================================================
//ジョイスティック情報取得
//=======================================================================
SHORT CInputController::GetJoyStickLX(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbLX;
}

//=======================================================================
//ジョイスティック情報取得
//=======================================================================
SHORT CInputController::GetJoyStickLY(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbLY;
}

//=======================================================================
//ジョイスティック情報取得
//=======================================================================
SHORT CInputController::GetJoyStickRX(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbRX;
}

//=======================================================================
//ジョイスティック情報取得
//=======================================================================
SHORT CInputController::GetJoyStickRY(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbRY;
}

//=======================================================================
//ゲームパッドのプレス情報を取得
//=======================================================================
bool CInputController::GetPress(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadState[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//ゲームパッドのトリガー情報を取得
//=======================================================================
bool CInputController::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateTrigger[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//ゲームパッドのリリース情報を取得
//=======================================================================
bool CInputController::GetRelease(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateRelease[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//=======================================================================
//リピート情報取得
//=======================================================================
bool CInputController::GetRepeat(JOYKEY nKey, int nPlayer)
{
	return(m_aGamePadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//=======================================================================
//振動情報取得
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