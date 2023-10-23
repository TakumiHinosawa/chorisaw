//=========================================================================================
//
// モデル
// Author:日野澤匠泉	[objectX.cpp]
//
//=========================================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define MAX_XFILE	(4)		//オブジェクト最大数

//=========================================================================================
//モデルのコンストラクタ	
//=========================================================================================
CObjectX::CObjectX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fHeight = 0.0f;
	m_fWidth = 0.0f;

	m_dwNumMat = 0;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_pTexture = NULL;

	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	m_nNumVtx = 0;		
	m_dwSizeFVF = 0;	
	m_pVtxBuff = NULL;		

	bUse = false;
}
	
//=========================================================================================
//モデルのデストラクタ
//=========================================================================================
CObjectX::~CObjectX()
{

}

//=========================================================================================
//モデルの初期化処理
//=========================================================================================
HRESULT CObjectX::Init(void)
{
	//オブジェクト情報取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//過去の位置を保存
	m_posOld = m_pos;

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\chorizo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
	m_nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//頂点座標の代入

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//頂点座標の代入(モデルの頂点数)

		//最大数、最小数抜き出す
		if (m_vtxMax.x <= vtx.x)
		{	
			m_vtxMax.x = vtx.x;
		}	
		if (m_vtxMax.z <= vtx.z)
		{	
			m_vtxMax.z = vtx.z;
		}	
		if (m_vtxMin.x >= vtx.x)
		{	
			m_vtxMin.x = vtx.x;
		}	
		if (m_vtxMin.z >= vtx.z)
		{	
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//使用されていたら

		//メモリ開放
		delete[] m_pTexture;

		//メモリ初期化
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//使用されていないとき

		//メモリ確保
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}

	//オブジェクトの配置
	Set(m_pos, m_rot, 0, 0);

	return S_OK;
}

//=========================================================================================
//モデルの初期化処理
//=========================================================================================
HRESULT CObjectX::Init(char *pFilename)
{
	//オブジェクト情報取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//過去の位置を保存
	m_posOld = m_pos;

	bUse = false;

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
	m_nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//頂点座標の代入

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//頂点座標の代入(モデルの頂点数)
		
		//最大数、最小数抜き出す
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}

		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	if (m_pBuffMat == NULL)
	{//使用されていないとき

		return E_FAIL;
	}

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//使用されていたら

		//メモリ開放
		delete[] m_pTexture;

		//メモリ初期化
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//使用されていないとき

		//メモリ確保
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = NULL;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
		else
		{
			//初期化
			m_pTexture[nCntMat] = NULL;
		}
	}

	return S_OK;
}

//=========================================================================================
//モデルの終了処理
//=========================================================================================
void CObjectX::Uninit(void)
{
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{//NULLじゃなかった場合

		//メモリを破棄する
		delete[] m_pTexture;

		//使用されていない状態にする
		m_pTexture = NULL;
	}

	if (m_pBuffMat != NULL)
	{//情報が入っていたら

		//メモリを解放
		m_pBuffMat->Release();

		//初期化
		m_pBuffMat = NULL;
	}

	//開放
	Release();
}

//=========================================================================================
//モデルの更新処理
//=========================================================================================
void CObjectX::Update(void)
{
	//現在の位置を保存
	m_posOld = m_pos;

	m_rot.y -= 0.01f;

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		bUse = true;
	}
	if (bUse == true)
	{
		m_rot.y -= 0.76f;
		m_pos.y += 0.89f;
	}
}

//=========================================================================================
//モデルの描画処理
//=========================================================================================
void CObjectX::Draw(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

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

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=========================================================================================
//モデルの設定処理 (幅 * 高さ　調整不可)
//=========================================================================================
void CObjectX::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//モデルの生成処理
//=========================================================================================
CObjectX *CObjectX::Create(char *pFilename)
{
	//ポインタの変数を宣言
	CObjectX *pObectX;

	//オブジェクト3Dの生成
	pObectX = new CObjectX;

	if (pObectX != NULL)
	{//使用されているとき

		//初期化処理
		pObectX->Init(pFilename);
	}

	//オブジェクト情報を返す
	return pObectX;
}

//=========================================================================================
//モデルの再読み込み
//=========================================================================================
void CObjectX::ReloadObject(char *pFilename)
{
	//オブジェクト情報取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{//NULLじゃなかった場合

		//メモリを破棄する
		delete[] m_pTexture;

		//使用されていない状態にする
		m_pTexture = NULL;
	}

	if (m_pBuffMat != NULL)
	{//情報が入っていたら

		//メモリを解放
		m_pBuffMat->Release();

		//初期化
		m_pBuffMat = NULL;
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
	m_nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//頂点座標の代入

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//頂点座標の代入(モデルの頂点数)

		//最大数、最小数抜き出す
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}
		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//使用されていたら

		//メモリ開放
		delete[] m_pTexture;

		//メモリ初期化
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//使用されていないとき

		//メモリ確保
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = NULL;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
		else
		{
			//初期化
			m_pTexture[nCntMat] = NULL;
		}
	}
}

//=========================================================================================
//モデルの位置取得処理
//=========================================================================================
D3DXVECTOR3 CObjectX::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//モデルの現在の位置取得処理
//=========================================================================================
D3DXVECTOR3 CObjectX::GetPositionOld(void)
{
	return m_posOld;
}

//=========================================================================================
//モデルの位置設定処理
//=========================================================================================
void CObjectX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//モデルの現在の位置設定処理
//=========================================================================================
void CObjectX::SetPositionOld(D3DXVECTOR3 pos)
{
	m_posOld = pos;
}

//=========================================================================================
//モデルの移動取得
//=========================================================================================
D3DXVECTOR3 CObjectX::GetMove(void)
{
	return m_move;
}

//=========================================================================================
//モデルの移動設定処理
//=========================================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=========================================================================================
//モデルの向き取得
//=========================================================================================
D3DXVECTOR3 CObjectX::GetRot(void)
{
	return m_rot;
}

//=========================================================================================
//モデルの向き設定処理
//=========================================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=========================================================================================
//モデルの高さ設定処理
//=========================================================================================
float CObjectX::GetHeight(void)
{
	return m_fHeight;
}

//=========================================================================================
//モデルの幅設定処理
//=========================================================================================
float CObjectX::GetWidth(void)
{
	return m_fWidth;
}

//=========================================================================================
//モデルの幅設定処理
//=========================================================================================
void CObjectX::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//バーテックス最大値の設定処理
//=========================================================================================
void CObjectX::SetVtxMax(D3DXVECTOR3 vtxMax)
{
	m_vtxMax = vtxMax;
}

//=========================================================================================
//バーテックス最大値の取得処理
//=========================================================================================
D3DXVECTOR3 CObjectX::GetVtxMax(void)
{
	return m_vtxMax;
}

//=========================================================================================
//バーテックス最小値の設定処理
//=========================================================================================
void CObjectX::SetVtxMin(D3DXVECTOR3 vtxMin)
{
	m_vtxMin = vtxMin;
}

//=========================================================================================
//バーテックス最小値の取得処理
//=========================================================================================
D3DXVECTOR3 CObjectX::GetVtxMin(void)
{
	return m_vtxMin;
}

