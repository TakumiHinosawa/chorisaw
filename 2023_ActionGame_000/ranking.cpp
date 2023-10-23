
//=============================================================================
//
// ranking
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//インクルード
//*****************************************************************************
#include "ranking.h"
#include "input.h"
#include "modeimage.h"
#include "score.h"
#include <stdio.h>
#include "number.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_nValue = 0;			
	m_nScore = 0;			
	m_nCounter = 0;		
	m_nCtr = 0;

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		m_aData[nCntLine] = 0;
	}

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			m_apNumber[nCntLine][nCntPlace] = 0;
		}
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	//********************************************************
	//テクスチャ読み込み
	//********************************************************
	m_pModeImage->Load(1);

	//背景生成
	m_pModeImage = CModeImage::Create(1);

	if (m_pModeImage != nullptr)
	{
		//初期化
		m_pModeImage = nullptr;
	}
	else
	{
		//初期化処理
		m_pModeImage->Init(1);
	}

	//********************************************************
	//ナンバー生成
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//スコアのロード
			m_apNumber[nCntLine][nCntPlace]->Load();

			//オブジェクト生成
			m_apNumber[nCntLine][nCntPlace] = CNumber::Create();

			//セットスコア
			m_apNumber[nCntLine][nCntPlace]->SetScore(D3DXVECTOR3(350.0f + nCntPlace * 30.0f, 200.0f + nCntLine * 140.0f, 0.0f), 
				nCntPlace, 0);
		}
	}

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CRanking::Uninit(void)
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

	//********************************************************
	//ナンバー終了処理
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//スコアのアンロード
			m_apNumber[nCntLine][nCntPlace]->Unload();

			//オブジェクト終了	
			m_apNumber[nCntLine][nCntPlace]->Uninit();
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CRanking::Update(void)
{
	m_nCtr++;		//カウンター加算

	//if (m_nCtr >= 200)
	//{
	//	//画面遷移
	//	CManager::GetManager()->SetMode(CScene::MODE_TITLE);

	//	m_nCtr = 0;		//カウンターリセット
	//}
}

//=============================================================================
//描画処理
//=============================================================================
void CRanking::Draw(void)
{
	//********************************************************
	//ナンバー描画処理
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//オブジェクト終了	
			m_apNumber[nCntLine][nCntPlace]->Draw();
		}
	}
}

//=============================================================================
//ロード処理
//=============================================================================
void CRanking::Load(void)
{
	FILE *pFile = NULL;

	//ファイル作成
	pFile = fopen("text\\ranking.txt", "r");

	if (pFile == NULL)
	{//ファイルがなかった場合
		return;
	}

	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		fscanf(pFile, "%d", &m_aData[nCnt]);
	}

	//ファイルを閉じる
	fclose(pFile);
}

//=============================================================================
//セーブ処理
//=============================================================================
void CRanking::Save(void)
{
	FILE *pFile;

	//ファイル作成
	pFile = fopen("text\\ranking.txt", "w");

	if (pFile == NULL)
	{//ファイルがなかった場合
		return;
	}
	
	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		fprintf(pFile, "%d\n", m_aData[nCnt]);
	}

	//ファイルを閉じる
	fclose(pFile);
}

//=============================================================================
//ソート処理
//=============================================================================
void CRanking::Sort(void)
{
	////スコア情報取得
	//int nScore = CScore::GetScore();	//スコア情報取得

	//if (nScore > m_aData[NUM_LINE - 1])
	//{
	//	m_aData[NUM_LINE - 1] = nScore;
	//}
}

//=========================================================================================
//生成処理
//=========================================================================================
CRanking *CRanking::Create(void)
{
	//ポインタの変数を宣言
	CRanking *pRanking;

	//生成
	pRanking = new CRanking;

	if (pRanking != NULL)
	{//使用されているとき

		//初期化処理
		pRanking->Init();
	}

	//オブジェクト情報を返す
	return pRanking;
}