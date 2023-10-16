//=========================================================================================
//
//[object2D.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _OBJECT2D_H_			//このマクロ定義がされなかったら
#define _OBJECT2D_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//オブジェクトクラス
//*****************************************************************************************
class CObject2D : public CObject
{
public:
	CObject2D();
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos , D3DXVECTOR3 rot,float fHeight,float fWidth);
	void SetAnim(int nCntAnim);
	void SetEffect(D3DXCOLOR col);
	void SetBg(float fTexV);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CObject2D *Create(void);	
	D3DXVECTOR3 GetPosition(void) override;
	void SetPosition(D3DXVECTOR3 pos);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	D3DXVECTOR3 GetOldPosition(void);
	void SetOldPosition(D3DXVECTOR3 pos);
	void SetColor(int nType);
	void Sort(int aData[4],int nScore, int aTexU[8]);

protected:
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_Oldpos;		//位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR2 m_size;			//縦横比

	LPDIRECT3DTEXTURE9	m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点情報へのポインタ
};

#endif

