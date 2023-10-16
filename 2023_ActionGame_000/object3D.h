//=========================================================================================
//
// オブジェクト3D[object3D.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _OBJECT3D_H_			//このマクロ定義がされなかったら
#define _OBJECT3D_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//オブジェクトクラス
//*****************************************************************************************
class CObject3D : public CObject
{
public:

	//ウォールタイプの列挙型定義
	typedef enum
	{
		WALL_NONE = 0,		//何も無いとき
		WALL_FRONT,			//前側
		WALL_BACK,			//後ろ側
		WALL_LEFT,			//左側
		WALL_RIGHT,			//右側
		WALL_MAX
	}WALL_TYPE;

	CObject3D();
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth,int nType);
	static CObject3D *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャ情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファ情報

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//向き

	float m_fHeight;			//高さ
	float m_fWidth;				//幅
};

#endif


