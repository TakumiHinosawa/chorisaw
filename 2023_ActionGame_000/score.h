//=========================================================================================
//
//スコア表示処理[score.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _SCORE_H_	//この定義がされていなかったら
#define _SCORE_H_	//二重インクルード防止のマクロ定義をする

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include"main.h"

//*****************************************************************************************
//前方宣言
//*****************************************************************************************
class CNumber;

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define NUM_PLACE		(8)		//スコアの桁数

//*****************************************************************************************
//クラス定義
//*****************************************************************************************
class CScore
{
public:
	CScore();
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *Create(void);

	void SetScore(void);
	void SetScoreRanking(int nNum);
	void AddScore(int nValue);
	void SubScore(int nValue);
	int GetScore(void);
	void SaveScore(void);
	void SetPosition(D3DXVECTOR3 pos);

private:
	int m_nScore;						//スコア
	int m_nValue;						//スコアの総数
	int m_nCtr;							//カウンター
	D3DXVECTOR3 m_pos;					//位置情報
	CNumber *m_apNumber[NUM_PLACE];		//数字情報
};

#endif

