//=========================================================================================
//
// ビルディング [billding.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _BILLDING_H_			//このマクロ定義がされなかったら
#define _BILLDING_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//オブジェクトXクラス
//*****************************************************************************************
class CBuilding : public CObjectX
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//普通の足場
		TYPE_THIN,			//細い足場
		TYPE_WALL,			//壁
		TYPE_WALLPAPER,		//壁紙
		TYPE_MAX
	}TYPE;

	CBuilding();
	~CBuilding();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBuilding *Create(void);
	TYPE GetType(void);
	void SetType(TYPE type);

private:
	TYPE m_Type;
};

#endif


