
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
		m_apScore[nCntLine] = 0;
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
	CNumber::Load();

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
		//オブジェクト生成
		m_apScore[nCntLine] = CScore::Create();

		//セットスコア
		m_apScore[nCntLine]->SetScore();

		//位置設定処理
		m_apScore[nCntLine]->SetPosition(D3DXVECTOR3(300.0f, 200.0f + nCntLine * 140.0f, 0.0f));
	}

	//ロード処理
	Load();

	//ソート処理
	Sort();

	//セーブ処理
	Save();

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		//位置設定処理
		m_apScore[nCntLine]->SetPosition(D3DXVECTOR3(300.0f, 200.0f + nCntLine * 140.0f, 0.0f));
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
	CNumber::Unload();

	//********************************************************
	//ナンバー終了処理
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		//オブジェクト終了	
		m_apScore[nCntLine]->Uninit();
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CRanking::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	m_nCtr++;		//カウンター加算

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_TITLE);
	}
	if (m_nCtr >= 350)
	{
		//画面遷移
		CManager::GetManager()->SetMode(CScene::MODE_TITLE);

		m_nCtr = 0;		//カウンターリセット
	}
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
		//オブジェクト終了	
		m_apScore[nCntLine]->Draw();
	}
}

//=============================================================================
//ロード処理
//=============================================================================
void CRanking::Load(void)
{
	FILE *pFile = NULL;

	//ファイル作成
	pFile = fopen("data\\text\\ranking.txt", "r");

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
	pFile = fopen("data\\text\\ranking.txt", "w");

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
	{
		//スコアの取得処理
		int nScore = 0;

		FILE *pFile;

		//ファイル作成
		pFile = fopen("data\\text\\score.txt", "r");

		if (pFile == NULL)
		{//ファイルがなかった場合
			return;
		}

		fscanf(pFile, "%d", &nScore);

		//ファイルを閉じる
		fclose(pFile);

		if (nScore > m_aData[NUM_LINE - 1])
		{
			m_aData[NUM_LINE - 1] = nScore;
		}
	}

	//降順処理(ソート)
	for (int nCnt1 = 0; nCnt1 < NUM_LINE - 1; nCnt1++)
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < NUM_LINE; nCnt2++)
		{
			if (m_aData[nCnt1] < m_aData[nCnt2])
			{
				//一度別の変数にデータを確保してから上書きする
				int nTemp = m_aData[nCnt1];
				m_aData[nCnt1] = m_aData[nCnt2];
				m_aData[nCnt2] = nTemp;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		m_apScore[nCnt]->SetScoreRanking(m_aData[nCnt]);
	}
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

//=========================================================================================
//取得処理
//=========================================================================================
//int CRanking::GetScore(void)
//{
//	FILE *pFile = NULL;
//
//	//ファイル作成
//	pFile = fopen("text\\score.txt", "r");
//
//	if (pFile == NULL)
//	{//ファイルがなかった場合
//		return;
//	}
//
//	fscanf(pFile, "%d", &m_aData[0]);
//
//	//ファイルを閉じる
//	fclose(pFile);
//
//	return m_aData[0];
//}