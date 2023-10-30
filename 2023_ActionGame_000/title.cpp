//=============================================================================
//
// title
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//インクルード
//*****************************************************************************
#include "title.h"
#include "modeimage.h"
#include "input.h"
#include "PlayerX.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "building.h"
#include "sound.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pCamera = NULL;
	m_pModeImage = NULL;
	m_pObjectX = NULL;
	m_pLight = NULL;
	m_nCtr = 0;
	m_nTrans = 0;
	bUse = false;
	bSound = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	//********************************************************
	//カメラの生成・初期化
	//********************************************************
	m_pCamera = new CCamera;

	if (m_pCamera != NULL)
	{//使用されていないとき

		//カメラの初期化処理
		m_pCamera->Init();
	}

	//********************************************************
	//ライトの生成・初期化
	//********************************************************
	m_pLight = new CLight;

	if (m_pLight != NULL)
	{//使用されていないとき

		//ライトの初期化処理
		m_pLight->Init();
	}

	//********************************************************
	//オブジェクト初期化
	//********************************************************
	m_pObjectX = CObjectX::Create("data\\MODEL\\title.x");
	m_pObjectX->SetPosition(D3DXVECTOR3(0.0f,90.0f, -200.0f));
	m_pObjectX->SetRot(D3DXVECTOR3(0.5f,0.0f,0.0f));

	//********************************************************
	//テクスチャ読み込み
	//********************************************************
	m_pModeImage->Load(0);

	//背景生成
	m_pModeImage = CModeImage::Create(0);

	if (m_pModeImage != nullptr)
	{
		//初期化
		m_pModeImage = nullptr;
	}
	else
	{
		//初期化処理
		m_pModeImage->Init(0);
	}

	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	bUse = false;

	if (m_pModeImage != nullptr)
	{
		//終了処理
		m_pModeImage->Uninit();

		//初期化
		m_pModeImage = nullptr;
	}

	//********************************************************
	//テクスチャ破棄
	//********************************************************
	m_pModeImage->Unload();

	//********************************************************
	//カメラの終了処理
	//********************************************************
	if (m_pCamera != NULL)
	{//使用されているとき

		//カメラの初期化処理
		m_pCamera->Uninit();
	}

	//********************************************************
	//ライトの終了処理
	//********************************************************
	if (m_pLight != NULL)
	{//使用されているとき

		//カメラの初期化処理
		m_pLight->Uninit();
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CTitle::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	m_nTrans++;

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && bSound == false)
	{
		bUse = true;
		bSound = true;

		//ジャンプ音
		pSound->PlaySound(CSound::SOUND_LABEL_SE_TITLE);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SPACE);
	}
	if (bUse == true)
	{
		m_nCtr++;
	}
	if (m_nCtr > 150)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_TUTORIAL);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_TRANSITION);

		m_nCtr = 0;		//カウンター初期化
	}
	if (m_nTrans >= 550)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_RANKING);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_TRANSITION);

		m_nTrans = 0;
	}
	//********************************************************
	//ライトの更新処理
	//********************************************************
	if (m_pLight != NULL)
	{//使用されているとき

		//カメラの初期化処理
		m_pLight->Update();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CTitle::Draw(void)
{
	//********************************************************
	//カメラの設定処理
	//********************************************************
	if (m_pCamera != NULL)
	{//使用されているとき

		//カメラの初期化処理
		m_pCamera->SetCamera();
	}
}

//=========================================================================================
//生成処理
//=========================================================================================
CTitle *CTitle::Create(void)
{
	//ポインタの変数を宣言
	CTitle *pTitle;

	//生成
	pTitle = new CTitle;

	if (pTitle != NULL)
	{//使用されているとき

		//初期化処理
		pTitle->Init();
	}

	//オブジェクト情報を返す
	return pTitle;
}
