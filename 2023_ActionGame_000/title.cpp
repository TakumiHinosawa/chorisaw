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

//=============================================================================
//コンストラクタ
//=============================================================================
CTitle::CTitle()
{

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

	//********************************************************
	//オブジェクト初期化
	//********************************************************
	CPlayerX::Create();

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CTitle::Uninit(void)
{
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
}

//=============================================================================
//更新処理
//=============================================================================
void CTitle::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//画面遷移
		CManager::SetMode(CScene::MODE_TUTORIAL);
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CTitle::Draw(void)
{

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
