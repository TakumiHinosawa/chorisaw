//=========================================================================================
//
// オブジェクトX [objectX.h]
// Author:日野澤匠泉
//
//=========================================================================================
#ifndef _OBJECTX_H_			//このマクロ定義がされなかったら
#define _OBJECTX_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define NUM_OBJ	(256)	//オブジェクト最大数

//*****************************************************************************************
//オブジェクトXクラス
//*****************************************************************************************
class CObjectX : public CObject
{
public:
	CObjectX();
	~CObjectX();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	HRESULT Init(char *pFilename);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	static CObjectX *Create(char *pFilename);

	D3DXVECTOR3 GetPosition(void);
	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPositionOld(void);
	void SetPositionOld(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetMove(void);
	void SetMove(D3DXVECTOR3 move);

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);

	void SetVtxMax(D3DXVECTOR3 vtxMax);
	D3DXVECTOR3 GetVtxMax(void);

	void SetVtxMin(D3DXVECTOR3 vtxMin);
	D3DXVECTOR3 GetVtxMin(void);

	float GetHeight(void);
	float GetWidth(void);
	void SetSize(float fHeight, float fWidth);

	void ReloadObject(char *pFilename);

private:
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアルのポインタ
	DWORD m_dwNumMat;			//マテリアルの数
	LPDIRECT3DTEXTURE9* m_pTexture;		//テクスチャへのポインタ

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posOld;//過去の位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_rot;	//向き
	float m_fHeight;	//高さ
	float m_fWidth;		//幅

	D3DXVECTOR3 m_vtxMin;	//モデルの最小値
	D3DXVECTOR3 m_vtxMax;	//モデルの最大値

	int m_nNumVtx;		//頂点数
	DWORD m_dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE *m_pVtxBuff;		//頂点バッファのポインタ
};

#endif


