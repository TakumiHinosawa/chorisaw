//=========================================================================================
//
// オブジェクトビルボード [objectbillboard.cpp]
// Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "objectbillboard.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define SIZE	(50.0f)	//サイズ

//=========================================================================================
//3Dオブジェクトのコンストラクタ
//=========================================================================================
CObjectBillboard::CObjectBillboard()
{
	//各種変数初期化
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fHeight = SIZE;
	m_fWidth = SIZE;
}

//=========================================================================================
//3Dオブジェクトのデストラクタ
//=========================================================================================
CObjectBillboard::~CObjectBillboard()
{

}

//=========================================================================================
//3Dオブジェクトの初期化処理
//=========================================================================================
HRESULT CObjectBillboard::Init(void)
{
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

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = (- m_fWidth);
	pVtx[1].pos.x = (+ m_fWidth);
	pVtx[2].pos.x = (- m_fWidth);
	pVtx[3].pos.x = (+ m_fWidth);
					   
	pVtx[0].pos.y = (+ m_fHeight);
	pVtx[1].pos.y = (+ m_fHeight);
	pVtx[2].pos.y = (- m_fHeight);
	pVtx[3].pos.y = (- m_fHeight);

	pVtx[0].pos.z = (0.0f);
	pVtx[1].pos.z = (0.0f);
	pVtx[2].pos.z = (0.0f);
	pVtx[3].pos.z = (0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
void CObjectBillboard::Uninit(void)
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
void CObjectBillboard::Update(void)
{

}

//=========================================================================================
//3Dオブジェクトの描画処理
//=========================================================================================
void CObjectBillboard::Draw(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ビューマトリックス取得用
	D3DXMATRIX mtxView;	

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//=========================================================================================
//3Dオブジェクトの設定
//=========================================================================================
void CObjectBillboard::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pos = pos;
	m_rot = rot;
}

//=========================================================================================
//3Dオブジェクトの生成
//=========================================================================================
CObjectBillboard *CObjectBillboard::Create(void)
{
	//ポインタの変数を宣言
	CObjectBillboard *pObectBillboard;

	//オブジェクト3Dの生成
	pObectBillboard = new CObjectBillboard;

	if (pObectBillboard != NULL)
	{//使用されているとき

		//初期化処理
		pObectBillboard->Init();
	}

	//オブジェクト情報を返す
	return pObectBillboard;
}

//=========================================================================================
//バインドテクスチャ
//=========================================================================================
void CObjectBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=========================================================================================
//位置情報の取得
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//位置情報の取得
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetRot(void)
{
	return m_rot;
}

//=========================================================================================
//位置情報の取得
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetMove(void)
{
	return m_move;
}

//=========================================================================================
//位置情報の設定処理
//=========================================================================================
void CObjectBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//位置情報の設定処理
//=========================================================================================
void CObjectBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=========================================================================================
//位置情報の設定処理
//=========================================================================================
void CObjectBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=========================================================================================
//弾の発射の設定処理
//=========================================================================================
void CObjectBillboard::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=========================================================================================
//高さの大きさ取得処理
//=========================================================================================
float CObjectBillboard::GetHeight(void)
{
	return m_fHeight;
}

//=========================================================================================
//幅の大きさ取得処理
//=========================================================================================
float CObjectBillboard::GetWidth(void)
{
	return m_fWidth;
}

//=========================================================================================
//サイズの設定処理
//=========================================================================================
void CObjectBillboard::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	//バーテックス設定処理
	SetVtx();
}

//=========================================================================================
//バーテックスの設定処理
//=========================================================================================
void CObjectBillboard::SetVtx(void)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = (-m_fWidth);
	pVtx[1].pos.x = (+m_fWidth);
	pVtx[2].pos.x = (-m_fWidth);
	pVtx[3].pos.x = (+m_fWidth);

	pVtx[0].pos.y = (+m_fHeight);
	pVtx[1].pos.y = (+m_fHeight);
	pVtx[2].pos.y = (-m_fHeight);
	pVtx[3].pos.y = (-m_fHeight);

	pVtx[0].pos.z = (0.0f);
	pVtx[1].pos.z = (0.0f);
	pVtx[2].pos.z = (0.0f);
	pVtx[3].pos.z = (0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//アニメーションの設定処理
//=========================================================================================
void CObjectBillboard::SetAnim(int nCntAnim)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f + nCntAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f + nCntAnim * 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nCntAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f + nCntAnim * 0.125f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}