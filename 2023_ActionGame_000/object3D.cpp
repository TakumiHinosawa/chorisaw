//=========================================================================================
//
// オブジェクト3D [object3D.cpp]
// Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "object3D.h"
#include "renderer.h"
#include "manager.h"

//=========================================================================================
//3Dオブジェクトのコンストラクタ
//=========================================================================================
CObject3D::CObject3D()
{
	//各種変数初期化
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}

//=========================================================================================
//3Dオブジェクトのデストラクタ
//=========================================================================================
CObject3D::~CObject3D()
{

}

//=========================================================================================
//3Dオブジェクトの初期化処理
//=========================================================================================
HRESULT CObject3D::Init(void)
{
	VERTEX_3D *pVtx;

	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = (- 300.0f);
	pVtx[1].pos.x = (+ 300.0f);
	pVtx[2].pos.x = (- 300.0f);
	pVtx[3].pos.x = (+ 300.0f);

	pVtx[0].pos.y = (+ 0.0f);
	pVtx[1].pos.y = (+ 0.0f);
	pVtx[2].pos.y = (+ 0.0f);
	pVtx[3].pos.y = (+ 0.0f);

	pVtx[0].pos.z = (+ 300.0f);
	pVtx[1].pos.z = (+ 300.0f);
	pVtx[2].pos.z = (- 300.0f);
	pVtx[3].pos.z = (- 300.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================================================
//3Dオブジェクトの終了処理
//=========================================================================================
void CObject3D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{//情報が入っていたら

		//メモリを解放
		m_pVtxBuff->Release();

		//初期化
		m_pVtxBuff = NULL;
	}

	//開放
	Release();
}

//=========================================================================================
//3Dオブジェクトの更新処理
//=========================================================================================
void CObject3D::Update(void)
{

}

//=========================================================================================
//3Dオブジェクトの描画処理
//=========================================================================================
void CObject3D::Draw(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画処理
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//プリミティブの種類
}

//=========================================================================================
//3Dオブジェクトの設定
//=========================================================================================
void CObject3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = (- fWidth);
	pVtx[1].pos.x = (+ fWidth);
	pVtx[2].pos.x = (- fWidth);
	pVtx[3].pos.x = (+ fWidth);

	pVtx[0].pos.y = (+ 0.0f);
	pVtx[1].pos.y = (+ 0.0f);
	pVtx[2].pos.y = (+ 0.0f);
	pVtx[3].pos.y = (+ 0.0f);

	pVtx[0].pos.z = (+ fHeight);
	pVtx[1].pos.z = (+ fHeight);
	pVtx[2].pos.z = (- fHeight);
	pVtx[3].pos.z = (- fHeight);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//3Dオブジェクトウォールの設定
//=========================================================================================
void CObject3D::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth, int nType)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (nType)
	{
	case WALL_FRONT:	//前側

		//頂点座標の設定
		pVtx[0].pos.x = (- fWidth);
		pVtx[1].pos.x = (+ fWidth);
		pVtx[2].pos.x = (- fWidth);
		pVtx[3].pos.x = (+ fWidth);

		pVtx[0].pos.y = (+ fHeight * 0.25f);
		pVtx[1].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ 0.0f);

		pVtx[0].pos.z = (+0.0f);
		pVtx[1].pos.z = (+0.0f);
		pVtx[2].pos.z = (+0.0f);
		pVtx[3].pos.z = (+0.0f);
		break;

	case WALL_BACK:		//後ろ側

		//頂点座標の設定
		pVtx[0].pos.x = (- fWidth);
		pVtx[1].pos.x = (+ fWidth);
		pVtx[2].pos.x = (- fWidth);
		pVtx[3].pos.x = (+ fWidth);

		pVtx[0].pos.y = (+ 0.0f);
		pVtx[1].pos.y = (+ 0.0f);
		pVtx[2].pos.y = (+ fHeight * 0.25f);
		pVtx[3].pos.y = (+ fHeight * 0.25f);
						   
		pVtx[0].pos.z = (+ 0.0f);
		pVtx[1].pos.z = (+ 0.0f);
		pVtx[2].pos.z = (+ 0.0f);
		pVtx[3].pos.z = (+ 0.0f);
		break;

	case WALL_LEFT:		//左側

		//頂点座標の設定
		pVtx[0].pos.x = (- 0.0f);
		pVtx[1].pos.x = (+ 0.0f);
		pVtx[2].pos.x = (- 0.0f);
		pVtx[3].pos.x = (+ 0.0f);
						   
		pVtx[0].pos.y = (+ fHeight * 0.25f);
		pVtx[1].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ 0.0f);
						   
		pVtx[0].pos.z = (- fWidth);
		pVtx[1].pos.z = (+ fWidth);
		pVtx[2].pos.z = (- fWidth);
		pVtx[3].pos.z = (+ fWidth);
		break;

	case WALL_RIGHT:		//右側

		//頂点座標の設定
		pVtx[0].pos.x = (- 0.0f);
		pVtx[1].pos.x = (+ 0.0f);
		pVtx[2].pos.x = (- 0.0f);
		pVtx[3].pos.x = (+ 0.0f);
						   
		pVtx[0].pos.y = (+ 0.0f);
		pVtx[1].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ fHeight * 0.25f);
						   
		pVtx[0].pos.z = (- fWidth);
		pVtx[1].pos.z = (+ fWidth);
		pVtx[2].pos.z = (- fWidth);
		pVtx[3].pos.z = (+ fWidth);
		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//3Dオブジェクトの生成
//=========================================================================================
CObject3D *CObject3D::Create(void)
{
	//ポインタの変数を宣言
	CObject3D *pObect3D;

	//オブジェクト3Dの生成
	pObect3D = new CObject3D;

	if (pObect3D != NULL)
	{//使用されているとき

		//初期化処理
		pObect3D->Init();
	}

	//オブジェクト情報を返す
	return pObect3D;
}

//=========================================================================================
//3Dオブジェクトテクスチャの割り当て
//=========================================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
