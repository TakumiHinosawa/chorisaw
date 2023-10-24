//=========================================================================================
//
//[game.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _GAME_H_			//このマクロ定義がされなかったら
#define _GAME_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "manager.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define NUM_BUILD	(94)		//建物最大数

//*****************************************************************************************
//前方宣言
//*****************************************************************************************
class CSound;
class CScore;
class CCamera;
class CLight;
class CObjectX;
class CBuilding;
class CDebugProc;
class CPlayerX;
class CObject;

//*****************************************************************************************
//ゲームクラス定義
//*****************************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGame *Create(void);

	static CPlayerX *GetPlayer(void);
	static CScore *GetScore(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CObjectX *GetObjectX(void);
	static CBuilding *GetBuilding(int nIdx);

private:
	static CPlayerX *m_pPlayerX;
	static CScore *m_pScore;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CObjectX *m_pObjectX;
	static CBuilding *m_apBuilding[NUM_BUILD];
	int m_nCtr;
};

#endif

