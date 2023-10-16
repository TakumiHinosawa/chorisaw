//=========================================================================================
//
// オブジェクトビルボード[objectbillboard.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _OBJECTBILLBOARD_H_			//このマクロ定義がされなかったら
#define _OBJECTBILLBOARD_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//オブジェクトクラス
//*****************************************************************************************
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	static CObjectBillboard *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetMove(void);
	void SetMove(D3DXVECTOR3 move);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

	float GetHeight(void);
	float GetWidth(void);
	void SetSize(float fHeight,float hWidth);

	void SetVtx(void);

	void SetAnim(int nCntAnim);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファ情報
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き

	float m_fHeight;		//高さ
	float m_fWidth;			//幅
};

#endif


