//=========================================================================================
//
//スコア表示処理 [score.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "score.h"
#include "number.h"
#include "object2d.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include <stdio.h>

//=========================================================================================
//コンストラクタ
//=========================================================================================
CScore::CScore()
{
	m_nScore = 0;
	m_nValue = 0;
	m_nCtr = 0;
	m_Dist = 0;
	m_pos = D3DXVECTOR3( 0.0f,0.0f,0.0f );

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

//=========================================================================================
//デストラクタ
//=========================================================================================
CScore::~CScore()
{

}

//=========================================================================================
//スコアの初期化処理
//=========================================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//オブジェクト生成
		m_apNumber[nCnt] = CNumber::Create();
	}

	return S_OK;
}

//=========================================================================================
//スコアの終了処理
//=========================================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{//使用されているとき

			//オブジェクト終了処理
			m_apNumber[nCnt]->Uninit();

			//オブジェクトを破棄
			delete m_apNumber[nCnt];

			//オブジェクト初期化
			m_apNumber[nCnt] = NULL;
		}
	}
}

//=========================================================================================
//スコアの更新処理
//=========================================================================================
void CScore::Update(void)
{
	//セットスコア
	SetScore();
}

//=========================================================================================
//スコアの描画処理
//=========================================================================================
void CScore::Draw(void)
{

}

//=========================================================================================
//スコアの設定処理
//=========================================================================================
CScore *CScore::Create(void)
{
	//ポインタの変数を宣言
	CScore *pScore;

	//オブジェクト2Dの生成
	pScore = new CScore;

	if (pScore != NULL)
	{//使用されているとき

		//初期化処理
		pScore->Init();
	}

	//オブジェクト情報を返す
	return pScore;
}

//=========================================================================================
//スコアの設定処理
//=========================================================================================
void CScore::SetScore(void)
{
	int aTexU[NUM_PLACE];		//各桁の数値を格納

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//スコアの設定処理
		m_apNumber[nCnt]->SetScore(D3DXVECTOR3(500.0f,10.0f,0.0f), nCnt, aTexU[nCnt]);
	}
}

//=========================================================================================
//スコアの設定処理
//=========================================================================================
void CScore::SetScoreRanking(int nNum)
{
	int aTexU[NUM_PLACE];		//各桁の数値を格納

	m_nScore = nNum;

	aTexU[0] = nNum % 100000 / 10000;
	aTexU[1] = nNum % 10000 / 1000;
	aTexU[2] = nNum % 1000 / 100;
	aTexU[3] = nNum % 100 / 10;
	aTexU[4] = nNum % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//スコアの設定処理
		m_apNumber[nCnt]->SetScore(D3DXVECTOR3(600.0f, 10.0f, 0.0f), nCnt, aTexU[nCnt]);
	}
}

//=========================================================================================
//スコアの加算処理
//=========================================================================================
void CScore::AddScore(int nValue)
{
	//サウンド情報取得
	CSound *pSound = CManager::GetManager()->GetSound();

	int aTexU[NUM_PLACE];		//各桁の数値を格納

	m_nScore += nValue;

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	if (m_nScore > 1000 && m_Dist == 0)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_1000M);

		m_Dist = 1;
	}
	if (m_nScore > 2000 && m_Dist == 1)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_2000M);

		m_Dist = 2;
	}
	if (m_nScore > 3000 && m_Dist == 2)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_3000M);

		m_Dist = 3;
	}
	if (m_nScore > 4000 && m_Dist == 3)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_4000M);

		m_Dist = 4;
	}
	if (m_nScore > 5000 && m_Dist == 4)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_5000M);

		m_Dist = 5;
	}
	if (m_nScore > 6000 && m_Dist == 5)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_6000M);

		m_Dist = 6;
	}
	if (m_nScore > 7000 && m_Dist == 6)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_7000M);

		m_Dist = 7;
	}
	if (m_nScore > 8000 && m_Dist == 7)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_8000M);

		m_Dist = 8;
	}
}

//=========================================================================================
//スコアの減算処理
//=========================================================================================
void CScore::SubScore(int nValue)
{
	int aTexU[NUM_PLACE];		//各桁の数値を格納

	if (m_nScore <= 0)
	{//スコアが0以下の場合

		return;
	}

	m_nScore -= nValue;

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;
}

//=========================================================================================
//スコアの保存
//=========================================================================================
void CScore::SaveScore(void)
{
	FILE *pFile;

	//ファイル作成
	pFile = fopen("data\\text\\score.txt", "w");

	if (pFile == NULL)
	{//ファイルがなかった場合
		return;
	}

	fprintf(pFile, "%d", m_nScore - 2);

	//ファイルを閉じる
	fclose(pFile);
}

//=========================================================================================
//スコアの取得
//=========================================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=========================================================================================
//スコアの位置設定処理
//=========================================================================================
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	int aTexU[NUM_PLACE];		//各桁の数値を格納

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//スコアの設定処理
		m_apNumber[nCnt]->SetScore(pos, nCnt, aTexU[nCnt]);
	}
}