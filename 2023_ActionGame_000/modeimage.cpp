//=========================================================================================
//
// [modeimage.cpp]
// Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
// インクルード
//*****************************************************************************************
#include "modeimage.h"
#include "renderer.h"
#include "manager.h"
#include "object2D.h"
#include "input.h"
#include "sound.h"
#include "object.h"

//*****************************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************************
LPDIRECT3DTEXTURE9 CModeImage::m_pTexture = NULL;

//=========================================================================================
// モードイメージのコンストラクタ
//=========================================================================================
CModeImage::CModeImage()
{
	m_pModeImage = NULL;
}

//=========================================================================================
// モードイメージのデストラクタ
//=========================================================================================
CModeImage::~CModeImage()
{

}

//=========================================================================================
// モードイメージのテクスチャ読み込み
//=========================================================================================
HRESULT CModeImage::Load(int nType)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	switch (nType)
	{
	case 0:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\title.png",
			&m_pTexture);
		break;

	case 1:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\ranking.png",
			&m_pTexture);
		break;

	case 2:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial.png",
			&m_pTexture);
		break;

	case 3:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial.png",
			&m_pTexture);
		break;
	}
	return S_OK;
}

//=========================================================================================
// モードイメージのテクスチャ破棄
//=========================================================================================
void CModeImage::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=========================================================================================
// モードイメージの初期化処理
//=========================================================================================
HRESULT CModeImage::Init(int nType)
{
	if (m_pModeImage == NULL)
	{//使用されていないとき

		//生成
		m_pModeImage = new CObject2D;
	}

	if (m_pModeImage != NULL)
	{//使用されているとき

		//初期化処理
		m_pModeImage->Init();

		//テクスチャの割り当て
		m_pModeImage->BindTexture(m_pTexture);
	}

	switch (nType)
	{
	case 0:
		//種類の設定
		SetType(TYPE_TITLE);
		break;

	case 1:
		//種類の設定
		SetType(TYPE_RANKING);
		break;

	case 2:
		//種類の設定
		SetType(TYPE_TUTORIAL);
		break;

	case 3:
		//種類の設定
		SetType(TYPE_RESULT);
		break;
	}

	//画像設定
	m_pModeImage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 360.0f, 650.0f);

	return S_OK;
}

//=========================================================================================
// モードイメージの終了処理
//=========================================================================================
void CModeImage::Uninit(void)
{
	//開放
	Release();
}

//=========================================================================================
// モードイメージの更新処理
//=========================================================================================
void CModeImage::Update(void)
{
	m_pModeImage->GetMove();
}

//=========================================================================================
// モードイメージの描画処理
//=========================================================================================
void CModeImage::Draw(void)
{
	//描画処理
	m_pModeImage->Draw();
}

//=========================================================================================
// モードイメージの設定処理
//=========================================================================================
CModeImage *CModeImage::Create(int nType)
{
	//ポインタの変数を宣言
	CModeImage *pModeImage = NULL;

	//オブジェクト2Dの生成
	pModeImage = new CModeImage;

	if (pModeImage != NULL)
	{//使用されているとき

		//初期化処理
		pModeImage->Init(nType);

		//テクスチャの割り当て
		pModeImage->BindTexture(m_pTexture);
	}

	//オブジェクト情報を返す
	return pModeImage;
}
