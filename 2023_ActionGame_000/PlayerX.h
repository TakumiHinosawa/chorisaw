//=========================================================================================
//
// プレイヤーX [playerX.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _PLAYERX_H_			//このマクロ定義がされなかったら
#define _PLAYERX_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//オブジェクトXクラス
//*****************************************************************************************
class CPlayerX : public CObjectX
{
public:

	//プレイヤーの状態
	typedef enum
	{
		PLAYERJUMP_NONE = 0,		// ジャンプしてないとき
		PLAYERJUMP_UP,				// ジャンプを始めた時
		PLAYERJUMP_TOP,				// ジャンプ頂点
		PLAYERJUMP_DOWN,			// ジャンプ落ち始め
		PLAYERJUMP_MAX
	}PLAYERJUMP;

	CPlayerX();
	~CPlayerX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Controller(void);
	static CPlayerX *Create(void);
	void CollisionBuilding(void);

private:

	// --- デバッグ用 --- //
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_VtxMax;
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_BuildingPos;
	// ----------------- //

	PLAYERJUMP m_JumpState;		// ジャンプの状態

	int m_nJumpCtr;			// ジャンプカウンター
	int m_nTime;			// 時間
	int m_nAirborne;		// 滞空時間のカウント
};

#endif


