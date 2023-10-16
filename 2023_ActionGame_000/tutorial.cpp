//=============================================================================
//
// tutorial
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//インクルード
//*****************************************************************************
#include "tutorial.h"
#include "modeimage.h"
#include "input.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//********************************************************
	//テクスチャ読み込み
	//********************************************************
	m_pModeImage->Load(2);

	//背景生成
	m_pModeImage = CModeImage::Create(2);

	if (m_pModeImage != nullptr)
	{
		//初期化
		m_pModeImage = nullptr;
	}
	else
	{
		//初期化処理
		m_pModeImage->Init(2);
	}

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_GAME);
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}

//=========================================================================================
//生成処理
//=========================================================================================
CTutorial *CTutorial::Create(void)
{
	//ポインタの変数を宣言
	CTutorial *pTutorial;

	//生成
	pTutorial = new CTutorial;

	if (pTutorial != NULL)
	{//使用されているとき

		//初期化処理
		pTutorial->Init();
	}

	//オブジェクト情報を返す
	return pTutorial;
}
