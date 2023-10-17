//=========================================================================================
//
//[game.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "number.h"
#include "score.h"
#include "light.h"
#include "camera.h"
#include "playerx.h"
#include "time.h"
#include "game.h"
#include "input.h"
#include "string.h"
#include "sound.h"
#include "manager.h"
#include "building.h"
#include <stdio.h>

//*****************************************************************************************
//静的メンバ変数
//*****************************************************************************************
CPlayerX *CGame::m_pPlayerX = NULL;
CScore *CGame::m_pScore = NULL;
CCamera *CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CObjectX *CGame::m_pObjectX = NULL;
CTime *CGame::m_pTime = NULL;
CBuilding *CGame::m_apBuilding[NUM_BUILD] = {};

//=========================================================================================
//ゲームのコンストラクタ
//=========================================================================================
CGame::CGame()
{

}

//=========================================================================================
//ゲームのデストラクタ	
//=========================================================================================
CGame::~CGame()
{

}

//=========================================================================================
//ゲームの初期化処理	
//=========================================================================================
HRESULT CGame::Init(void)
{
	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	//********************************************************
	//カメラの生成
	//********************************************************
	if (m_pCamera == NULL)
	{//使用されていないとき

		//生成
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//使用されているとき

		//カメラの初期化処理
		m_pCamera->Init();
	}

	//********************************************************
	//ライトの生成
	//********************************************************
	if (m_pLight == NULL)
	{//使用されていないとき

		//生成
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//使用されているとき

		//ライトの初期化処理
		m_pLight->Init();
	}

	//********************************************************
	//テクスチャ読み込み
	//********************************************************
	CNumber::Load();

	//********************************************************
	//プレイヤー
	//********************************************************
	if (m_pPlayerX == NULL)
	{//使用されていないとき

		//プレイヤー作成
		m_pPlayerX = CPlayerX::Create();
	}

	//********************************************************
	//建物 配置
	//********************************************************

	//建物配置の構造体定義
	struct SBuildingInfo
	{
		CBuilding::TYPE mType;
		float mX;
		float mY;
		float mZ;
	};

	SBuildingInfo buildingInfo[] =
	{
		{ CBuilding::TYPE_NORMAL, 70.0f + 0 * 500.0f,-120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 70.0f + 1 * 500.0f,-120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 70.0f + 2 * 500.0f,-120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 70.0f + 3 * 500.0f,-120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 2000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 2700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 3300.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 3600.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4500.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 5100.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 5600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6100.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6600.0f,120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7000.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7200.0f,-80.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7600.0f,-80.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7900.0f,120.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8350.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8450.0f,80.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8550.0f,60.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8650.0f,40.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8750.0f,20.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9250.0f,20.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9550.0f,80.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9850.0f,20.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10150.0f,80.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10450.0f,20.0f,0.0f },

	};

	for (int nCnt = 0; nCnt < NUM_BUILD; nCnt++)
	{
		if (m_apBuilding[nCnt] == NULL)
		{//使用されていないとき

			//プレイヤー作成
			m_apBuilding[nCnt] = CBuilding::Create();
			m_apBuilding[nCnt]->SetType(buildingInfo[nCnt].mType);
			m_apBuilding[nCnt]->SetPosition(D3DXVECTOR3(buildingInfo[nCnt].mX, buildingInfo[nCnt].mY, buildingInfo[nCnt].mZ));
		}
	}

	//********************************************************
	//スコア
	//********************************************************
	if (m_pScore == NULL)
	{//使用されていないとき

		//スコアオブジェクトの情報を取得
		m_pScore = CScore::Create();

		//オブジェクト設定
		m_pScore->SetScore();
	}

	//********************************************************
	//タイマー
	//********************************************************
	if (m_pTime == NULL)
	{//使用されていないとき

		//オブジェクトの情報を取得
		m_pTime = CTime::Create();

		//オブジェクト設定
		m_pTime->SetTime();
	}

	//********************************************************
	//サウンド
	//********************************************************
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=============================================================================
//ゲームの終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//オブジェクトの破棄
	CObject::ReleaseAll();

	//********************************************************
	//スコア
	//********************************************************
	if (m_pScore != NULL)
	{//使用されていたら

		//スコアの終了処理
		m_pScore->Uninit();

		//破棄
		delete m_pScore;

		//初期化
		m_pScore = NULL;
	}

	//********************************************************
	//タイマー
	//********************************************************
	if (m_pTime != NULL)
	{//使用されていたら

		//タイマーの終了処理
		m_pTime->Uninit();

		//破棄
		delete m_pTime;

		//初期化
		m_pTime = NULL;
	}

	//********************************************************
	//ライト
	//********************************************************
	if (m_pLight != NULL)
	{
		//終了処理
		m_pLight->Uninit();

		//破棄
		delete m_pLight;

		//初期化
		m_pLight = NULL;
	}

	//********************************************************
	//カメラ
	//********************************************************	
	if (m_pCamera != NULL)
	{
		//終了処理
		m_pCamera->Uninit();

		//破棄
		delete m_pCamera;

		//初期化
		m_pCamera = NULL;
	}

	//********************************************************
	//プレイヤー
	//********************************************************
	if (m_pPlayerX != NULL)
	{//使用されているとき

		//初期化
		m_pPlayerX = NULL;
	}

	//********************************************************
	//建物
	//********************************************************
	for (int nCnt = 0; nCnt < NUM_BUILD; nCnt++)
	{
		if (m_apBuilding != NULL)
		{//使用されているとき

			//初期化
			m_apBuilding[nCnt] = NULL;
		}
	}

	//各種テクスチャ破棄
	CNumber::Unload();
}

//=============================================================================
//ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	//********************************************************
	//スコア
	//********************************************************
	if (m_pScore != NULL)
	{//使用されていたら

		//更新処理
		m_pScore->Update();

		//スコアの更新
		m_pScore->AddScore(1);
	}

	//********************************************************
	//タイマー
	//********************************************************
	if (m_pTime != NULL)
	{//使用されていたら

		//更新処理
		m_pTime->Update();
	}

	//********************************************************
	//カメラ
	//********************************************************
	if (m_pCamera != NULL)
	{//使用されていたら

		//更新処理
		m_pCamera->Update();
	}

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_RESULT);

		if (m_pScore != NULL)
		{//使用されていたら

			// スコアの更新 ( 停止 )
			m_pScore->AddScore(0);
		}
	}
}

//=============================================================================
//ゲームの描画処理
//=============================================================================
void CGame::Draw(void)
{
	//カメラ情報取得
	CCamera *pCamera = CGame::GetCamera();

	//カメラの描画
	pCamera->SetCamera();
}

//=========================================================================================
//ゲームの生成処理
//=========================================================================================
CGame *CGame::Create(void)
{
	//ポインタの変数を宣言
	CGame *pGame;

	//生成
	pGame = new CGame;

	if (pGame != NULL)
	{//使用されているとき

		//初期化処理
		pGame->Init();
	}

	//オブジェクト情報を返す
	return pGame;
}

//=========================================================================================
//プレイヤー情報取得
//=========================================================================================
CPlayerX *CGame::GetPlayer(void)
{
	return m_pPlayerX;
}

//=========================================================================================
//スコア情報取得
//=========================================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=========================================================================================
//スコア情報取得
//=========================================================================================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//=========================================================================================
//カメラの情報取得
//=========================================================================================
CCamera *CGame::GetCamera(void)
{
	return m_pCamera;
}

//=========================================================================================
//ライトの情報取得
//=========================================================================================
CLight *CGame::GetLight(void)
{
	return m_pLight;
}

//=========================================================================================
//ライトの情報取得
//=========================================================================================
CObjectX *CGame::GetObjectX(void)
{
	return m_pObjectX;
}

//=========================================================================================
//建物の情報取得
//=========================================================================================
CBuilding *CGame::GetBuilding(int nIdx)
{
	return m_apBuilding[nIdx];
}
