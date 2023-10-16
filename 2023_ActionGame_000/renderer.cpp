//=========================================================================================
//
//レンダラー [renderer.cpp]
//Author:日野澤匠泉
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "renderer.h"
#include "object.h"
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "game.h"

//=========================================================================================
//レンダラーのコンストラクタ
//=========================================================================================
CRenderer::CRenderer()
{
	//デバイス関係初期化
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=========================================================================================
//レンダラーのデストラクタ
//=========================================================================================
CRenderer::~CRenderer()
{

}

//=========================================================================================
//レンダラーの初期化処理
//=========================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	//初期化処理
	D3DDISPLAYMODE d3ddm;				//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		//プレゼンテーションパラメータ

	//DirectX 3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現行のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータ設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;								//バックバッファの形式
	d3dpp.BackBufferCount = 1;											//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;								//デプスバッファとステンツルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//デプスバッファとして16bit使う
	d3dpp.Windowed = bWindow;											//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

	//DirectX 3Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//=========================================================================================
//レンダラーの終了処理
//=========================================================================================
void CRenderer::Uninit(void)
{
	//Direct 3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=========================================================================================
//レンダラーの更新処理
//=========================================================================================
void CRenderer::Update(void)
{
	//更新処理
	CObject::UpdateAll();
}

//=========================================================================================
//レンダラーの描画処理
//=========================================================================================
void CRenderer::Draw(void)
{
	//画面クリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

	//	D3DVIEWPORT9 viewportDef;

		//現在のヴューポートを取得
	//	m_pD3DDevice->GetViewport(&viewportDef);

		{
			//シーンの描画
			//CScene::Draw();

			//描画処理
			CObject::DrawAll();
		}

		//画面クリア
		m_pD3DDevice->Clear(0, NULL,D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		{
			if (CManager::GetManager()->GetMode() == CScene::MODE_GAME)
			{
				//カメラ情報取得
				CCamera *pCamera = CGame::GetCamera();

				//カメラの描画
				pCamera->SetCamera();

			}
		}

		{
			//デバッグ情報取得
			CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

			if (pDebug != NULL)
			{//使用されていたら

				//描画処理
				pDebug->Draw();
			}
		}

		//ヴューポートを元に戻す
		//	m_pD3DDevice->SetViewport(&viewportDef);

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックアップとフロントバッファの切り替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================
//レンダラーデバイスの取得
//=========================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

