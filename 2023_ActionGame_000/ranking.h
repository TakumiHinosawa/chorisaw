//=========================================================================================
//
//[ranking.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _RANKING_H_			//このマクロ定義がされなかったら
#define _RANKING_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//前方宣言
//*****************************************************************************************
class CModeImage;
class CScore;

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "manager.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define NUM_LINE	(4)		//ランキング表示列分
#define HEIGHT		(105)	//高さ

//*****************************************************************************************
//クラス定義
//*****************************************************************************************
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);
	void Save(void);
	void Sort(void);
	static CRanking *Create(void);

private:
	CModeImage *m_pModeImage;
	D3DXVECTOR3 m_pos;		//スコアの位置
	int m_nValue;			//スコアの値
	int m_nScore;			//スコア合計値
	int m_nCounter;			//ランキングカウンター
	int m_aData[NUM_LINE];	//ランキングデータ格納用
	int m_nCtr;				//遷移カウンター
	CScore *m_apScore[NUM_LINE];		//数字情報
	CScore *m_pMyScore;				//自分の記録
	bool bUse;
};

#endif