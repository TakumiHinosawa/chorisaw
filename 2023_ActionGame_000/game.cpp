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
	struct SBuildingInfo
	{
		CBuilding::TYPE mType;
		float mX;
		float mY;
		float mZ;
	};

	SBuildingInfo buildingInfo[] =
	{
		// チュートリアル 
		{ CBuilding::TYPE_START, 1800.0f,-200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL,800.0f,-30.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 1200.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 1600.0f,90.0f,0.0f },
		{ CBuilding::TYPE_THIN, 1900.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2300.0f,210.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2500.0f,270.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 2500.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2800.0f,90.0f,0.0f },

		// レベル1 (ジャンプ練習)
		{ CBuilding::TYPE_NORMAL, 3700.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4100.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4500.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4900.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 5400.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6000.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6600.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7100.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7600.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8200.0f,-100.0f,0.0f },

		// レベル2
		{ CBuilding::TYPE_THIN, 8500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10300.0f,30.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10600.0f,70.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10600.0f,70.0f,0.0f },
		{ CBuilding::TYPE_THIN, 11100.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 11600.0f,-50.0f,0.0f },

		//レベル 3
		{ CBuilding::TYPE_NORMAL, 12100.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 12600.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 13000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 13500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14000.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14500.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14900.0f,0.0f,0.0f },

		// ごちゃ混ぜ
		{ CBuilding::TYPE_NORMAL, 15300.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN,	  15700.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 16300.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN,   16700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 17100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 17500.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN,   17900.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 18300.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 18800.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 19300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 19800.0f,50.0f,0.0f },

		// 階段　下り
		{ CBuilding::TYPE_THIN, 20000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20050.0f,80.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20100.0f,60.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20150.0f,40.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20200.0f,20.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20250.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20300.0f,-20.0f,0.0f },

		// ごちゃ混ぜ レベルマックス
		{ CBuilding::TYPE_NORMAL, 20700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 21100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 21500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 21900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 22300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 22700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 23100.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 23500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 23900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 24400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 24900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 25400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 25900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 26400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 26800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 27200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 27700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 28000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 28300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 28700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 29000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 29300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 29700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 30000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 30400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 30800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 31200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 31600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 32000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 32400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 32700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 33100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 33500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 33900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 34300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 34700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 35100.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 35500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 35900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 36400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 36900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 37400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 37900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 38400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 38800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 39200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 39700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 40000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 40300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 40700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 41000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 41300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 41700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 42000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 42400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 42800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 43200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 43600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 44000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 44400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 44700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 46300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 46700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 48400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 48900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 49400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 49800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 50200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 50700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 54200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 54600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 55000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 55400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 55700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 56100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 56500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 56900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 57300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 57700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 59400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 59900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 60400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 60800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 61200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 61700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 62000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 62300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 62700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 64000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 64400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 64800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 65200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 65600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 66000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 66400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 66700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 68300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 68700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 70400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 70900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 71400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 71800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 72200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 72700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 76200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 76600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 77000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 77400.0f,50.0f,0.0f },

		// 壁紙
		{ CBuilding::TYPE_WALLPAPER, 2200.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 5500.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 8800.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 11100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 14400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 17700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 21700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 25000.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 28300.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 31600.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 34900.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 37200.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 40500.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 43800.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 47100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 50400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 53700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 54100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 57400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 60700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 64000.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 67300.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 70600.0f,0.0f,80.0f },
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
	//サウンド
	//********************************************************
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

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
	//カメラ
	//********************************************************
	if (m_pCamera != NULL)
	{//使用されていたら

		//更新処理
		m_pCamera->Update();
	}

	//プレイヤーの位置情報取得
	D3DXVECTOR3 pos = m_pPlayerX->GetPosition();
	
	if (pos.y <= -700.0f)
	{// プレイヤーが落ちた場合

		//サウンド情報取得
		CSound *pSound = CManager::GetManager()->GetSound();

		//サウンドの再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DOWN);

		if (m_pScore != NULL)
		{//使用されていたら

			//スコアの保存
			m_pScore->SaveScore();
		}

		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_RANKING);
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
