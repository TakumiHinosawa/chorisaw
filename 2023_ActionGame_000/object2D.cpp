//=========================================================================================
//
//[object2D.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define MAX_IMAGE	(2)
#define IMAGE_SAIZE	(50.0f)

//=========================================================================================
//2Dオブジェクトのコンストラクタ
//=========================================================================================
CObject2D::CObject2D()
{
	//各種変数初期化
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//2Dオブジェクトのデストラクタ
//=========================================================================================
CObject2D::~CObject2D()
{

}

//=========================================================================================
//2Dオブジェクトの初期化処理
//=========================================================================================
HRESULT CObject2D::Init(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
//2Dオブジェクトの終了処理
//=========================================================================================
void CObject2D::Uninit(void)
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
//2Dオブジェクトの更新処理
//=========================================================================================
void CObject2D::Update(void)
{

}

//=========================================================================================
//2Dオブジェクトの描画処理
//=========================================================================================
void CObject2D::Draw(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//プレイヤーの描画処理
	pDevice->SetTexture(0, m_pTexture);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブの種類
}

//=========================================================================================
//2Dオブジェクトの設定処理
//=========================================================================================
void CObject2D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fHeight,float fWidth)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	float nfLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 1.0f;

	//対角線の角度を算出する
	float nfAngle = atan2f(fWidth, fHeight);

	//頂点座標の設定
	pVtx[0].pos.x = pos.x + sinf(rot.z + (-D3DX_PI + nfAngle)) * nfLength;
	pVtx[0].pos.y = pos.y + cosf(rot.z + (-D3DX_PI + nfAngle)) * nfLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - nfAngle)) * nfLength;
	pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - nfAngle)) * nfLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(rot.z - nfAngle) * nfLength;
	pVtx[2].pos.y = pos.y + cosf(rot.z - nfAngle) * nfLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(rot.z + nfAngle) * nfLength;
	pVtx[3].pos.y = pos.y + cosf(rot.z + nfAngle) * nfLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//移動量更新
	m_pos = pos;
	m_rot = rot;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//2Dオブジェクト(アニメーション用)の設定処理
//=========================================================================================
void CObject2D::SetAnim(int nCntAnim)
{
	VERTEX_2D *pVtx;

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

//=========================================================================================
//2Dオブジェクト(エフェクト用)の設定処理
//=========================================================================================
void CObject2D::SetEffect(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	D3DXVECTOR3 rot;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//2Dオブジェクト(多重スクロール)の設定処理
//=========================================================================================
void CObject2D::SetBg(float fTexV)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(fTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexV + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexV + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//オブジェクトテクスチャの割り当て
//=========================================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=========================================================================================
//オブジェクトの設定処理
//=========================================================================================
CObject2D *CObject2D::Create(void)
{
	//ポインタの変数を宣言
	CObject2D *pObect2D;

	//オブジェクト2Dの生成
	pObect2D = new CObject2D;

	if (pObect2D != NULL)
	{//使用されているとき

		//初期化処理
		pObect2D->Init();
	}

	//オブジェクト情報を返す
	return pObect2D;
}

//=========================================================================================
//オブジェクトの位置取得
//=========================================================================================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//バッファの取得
//=========================================================================================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtx(void)
{
	return m_pVtxBuff;
}

//=========================================================================================
//現在の位置の取得
//=========================================================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//過去の位置の設定
//=========================================================================================
D3DXVECTOR3 CObject2D::GetOldPosition(void)
{
	return m_Oldpos;
}

//=========================================================================================
//過去の位置の取得
//=========================================================================================
void CObject2D::SetOldPosition(D3DXVECTOR3 pos)
{
	m_Oldpos = pos;
}

//=========================================================================================
//カラーの設定処理
//=========================================================================================
void CObject2D::SetColor(int nType)
{
	VERTEX_2D *pVtx;
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (nType)
	{
	case 0:
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case 1:
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//カラーの設定処理
//=========================================================================================
void CObject2D::Sort(int aData[4], int nScore, int aTexU[8])
{
	////降順処理(ソート)
	//for (int nCnt1 = 0; nCnt1 < 4 - 1; nCnt1++)
	//{
	//	for (int nCnt2 = nCnt1 + 1; nCnt2 < 4; nCnt2++)
	//	{
	//		if (aData[nCnt1] < aData[nCnt2])
	//		{
	//			//一度別の変数にデータを確保してから上書きする
	//			int nTemp = aData[nCnt1];
	//			aData[nCnt1] = aData[nCnt2];
	//			aData[nCnt2] = nTemp;
	//		}
	//	}
	//}

	//int aTexU[8];		//各桁の数値を格納
	//int nCntScore;

	//VERTEX_2D *pVtx;

	////頂点バッファをロックし、頂点データへのポインタを取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nCntLine = 0; nCntLine < 8; nCntLine++)
	//{
	//	aTexU[0] = aData[nCntLine] % 100000000 / 10000000;
	//	aTexU[1] = aData[nCntLine] % 10000000 / 1000000;
	//	aTexU[2] = aData[nCntLine] % 1000000 / 100000;
	//	aTexU[3] = aData[nCntLine] % 100000 / 10000;
	//	aTexU[4] = aData[nCntLine] % 10000 / 1000;
	//	aTexU[5] = aData[nCntLine] % 1000 / 100;
	//	aTexU[6] = aData[nCntLine] % 100 / 10;
	//	aTexU[7] = aData[nCntLine] % 10;

	//	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	//	{
	//		//位置を更新
	//		pVtx[0].pos = D3DXVECTOR3(400.0f + nCntScore * 60.0f, 160.0f + nCntLine *  105, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(450.0f + nCntScore * 60.0f, 160.0f + nCntLine *  105, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(400.0f + nCntScore * 60.0f, 210.0f + nCntLine * 105, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(450.0f + nCntScore * 60.0f, 210.0f + nCntLine * 105, 0.0f);

	//		//テクスチャ座標の更新
	//		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

	//		pVtx += 4;
	//	}
	//}
	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();
}