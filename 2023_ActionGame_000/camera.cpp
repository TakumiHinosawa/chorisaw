//=========================================================================================
//
// カメラ　[camera.cpp]
// Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "playerx.h"
#include "debugproc.h"
#include "game.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define MOVE	(1.0f)		//移動量
#define MOVES	(0.01f)		//角度移動量
#define DIS		(700.0f)	//距離
#define WIDTH	(350.0f)	//プレイヤーとカメラの距離幅 [ X座標 ]

//*****************************************************************************************
//静的メンバ変数初期化
//*****************************************************************************************
D3DXVECTOR3 CCamera::m_rot = {};

//=========================================================================================
//カメラのコンストラクタ
//=========================================================================================
CCamera::CCamera()
{
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//カメラのデストラクタ
//=========================================================================================
CCamera::~CCamera()
{

}

//=========================================================================================
//カメラの初期化処理
//=========================================================================================
HRESULT CCamera::Init(void)
{
	//画面設定
	m_viewport.X = 0;
	m_viewport.Y = 0;
	m_viewport.Width = SCREEN_WIDTH;
	m_viewport.Height = SCREEN_HEIGHT;
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;

	m_posV = D3DXVECTOR3(0.0f, 150.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=========================================================================================
//カメラの終了処理
//=========================================================================================
void CCamera::Uninit(void)
{
	
}

//=========================================================================================
//カメラの更新処理
//=========================================================================================
void CCamera::Update(void)
{
	//キーボードへのポインタ取得
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//コントローラーへのポインタを取得
	CInputController *pInputController = CManager::GetManager()->GetInputController();

	//デバッグ情報取得
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	if (pInputKeyboard->GetPress(DIK_X) == true)
	{//Y座標上
		m_move.y += MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_Z) == true)
	{//Y座標下
		m_move.y -= MOVE;
	}

	//移動方向の補正
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//カメラ回転
	m_posR.x = m_posV.x + sinf(m_rot.y) * DIS;		//視点から見てrotの方向にどれだけ離れているか
	m_posR.z = m_posV.z + cosf(m_rot.y) * DIS;

	if (pInputKeyboard->GetPress(DIK_E) == true)
	{//視点回転
		m_rot.y += MOVES;
	}
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{//視点回転
		m_rot.y -= MOVES;
	}

	//移動方向の補正
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//カメラ回転
	m_posV.x = m_posR.x + sinf(m_rot.y) * -DIS;	//注視点から見てrotの方向にどれだけ離れているか
	m_posV.z = m_posR.z + cosf(m_rot.y) * -DIS;

	if (pInputKeyboard->GetPress(DIK_T) == true)
	{//上を向く
		m_posR.y += MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_G) == true)
	{//下を向く
		m_posR.y -= MOVE;
	}

	//移動量代入
	m_posV += m_move;
	m_posR += m_move;

	//プレイヤーの取得処理
	CPlayerX *pPlayer = CGame::GetPlayer();

	//プレイヤーの位置情報取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	//モデルの移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.12f;
	m_move.y += (0.0f - m_move.y) * 0.12f;
	m_move.z += (0.0f - m_move.z) * 0.12f;

	//慣性
	m_posVDest.x = PlayerPos.x + WIDTH + sinf(m_rot.y) * -DIS;		//目的の視点にモデルの位置を代入(相対座標)
	m_posVDest.z = PlayerPos.z + cosf(m_rot.y) * -DIS;				//目的の視点にモデルの位置を代入(相対座標)
	(m_posVDest - m_posV) * 0.1f;

	float targetHeight = 0.0f; // カメラを引く高さ

	if (PlayerPos.y > targetHeight)
	{
		// カメラ位置を調整
		m_posR.y = PlayerPos.y - 50.0f;
		m_posV.y = PlayerPos.y;
	}

	//カメラ追従処理
	m_posV.x += (m_posVDest.x - m_posV.x) * 0.1f;	//視点にモデルの位置を代入(相対座標)
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.1f;	//視点にモデルの位置を代入(相対座標)

	//デバッグ表示
	pDebug->Print("カメラ　[注視点] ( X: %f Y: %f Z: %f )\n", m_posR.x, m_posR.y, m_posR.z);
	pDebug->Print("        　[視点] ( X: %f Y: %f Z: %f )\n\n", m_posV.x, m_posV.y, m_posV.z);
}

//=========================================================================================
//カメラの設定処理
//=========================================================================================
void CCamera::SetCamera(void)
{
	//オブジェクト取得
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	pDevice->SetViewport(&m_viewport);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//視野角
		(float)m_viewport.Width / (float)m_viewport.Height,	//アスペクト比
		10.0f,		//Z値の最小値
		5000.0f);	//Z値の最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	//視点
		&m_posR,	//注視点
		&m_vecR);	//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=========================================================================================
//カメラのロット情報取得
//=========================================================================================
D3DXVECTOR3 CCamera::GetRotCamera(void)
{
	return m_rot;
}

//=========================================================================================
//カメラの設定処理
//=========================================================================================
void CCamera::RotCamera(void)
{
	//目標の角度
	D3DXVECTOR3 RotDiff;

	//プレイヤーの取得処理
	CPlayerX *pPlayer = CGame::GetPlayer();

	//プレイヤーの位置情報取得
	D3DXVECTOR3 PlayerRot = pPlayer->GetRot();

	//プレイヤーの角度を設定
	m_rotDest = PlayerRot;
	RotDiff = m_rotDest - m_rot;

	//移動方向の補正
	if (RotDiff.y > D3DX_PI || RotDiff.y < -D3DX_PI)
	{
		if (RotDiff.y > D3DX_PI)
		{
			RotDiff.y += -D3DX_PI * 2;
		}
		else if (RotDiff.y < -D3DX_PI)
		{
			RotDiff.y += D3DX_PI * 2;
		}
	}

	m_rot.y += RotDiff.y * 0.03f;

	//移動方向の補正
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}
	m_posV.x = m_posR.x + sinf(m_rot.y) * -DIS;		//注視点から見てrotの方向にどれだけ離れているか
	m_posV.z = m_posR.z + cosf(m_rot.y) * -DIS;
}
