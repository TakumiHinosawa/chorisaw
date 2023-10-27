//=========================================================================================
//
//ポーズ処理
//Author:日野澤匠泉	[pause.cpp]
//
//=========================================================================================

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "input.h"
#include "game.h"
#include "pause.h"
#include "sound.h"

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define NUM_PAUSE		(4)		//テクスチャの数
#define SELECT_PAUSE	(3)		//選択できる数

//=========================================================================================
//ポーズの初期化処理
//=========================================================================================
CPause::CPause()
{
	m_nPauseMenu = 0;
	m_bPause = false;
}

//=========================================================================================
//ポーズの初期化処理
//=========================================================================================
CPause::~CPause()
{

}

//=========================================================================================
//ポーズの初期化処理
//=========================================================================================
HRESULT CPause::Init(void)
{
	//ポーズメニュー
	m_nPauseMenu = PAUSE_MENU_CONTINUE;

	// 2d読み込み　4枚分


	return S_OK;
}

//=========================================================================================
//ポーズの終了処理
//=========================================================================================
void CPause::Uninit(void)
{

}
//=========================================================================================
//ポーズの更新処理
//=========================================================================================
void CPause::Update(void)
{
	VERTEX_2D *pVtx;  //頂点情報へのポインタ

					  //頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W) == true || GetGamePadTrigger(BUTTON_0, 0))
	{
		g_PauseMenu = (g_PauseMenu + 2) % 3;

		//サウンド
		PlaySound(SOUND_LABEL_SE_CHOOSE);
	}

	if (GetKeyboardTrigger(DIK_S) == true || GetGamePadTrigger(BUTTON_1, 0))
	{
		g_PauseMenu = (g_PauseMenu + 1) % 3;

		//サウンド
		PlaySound(SOUND_LABEL_SE_CHOOSE);
	}

	if (g_PauseMenu == PAUSE_MENU_CONTINUE)
	{
		//頂点カラーの設定
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (g_PauseMenu == PAUSE_MENU_RETRY)
	{
		//頂点カラーの設定
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_CONTINUE * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (g_PauseMenu == PAUSE_MENU_QUIT)
	{
		//頂点カラーの設定
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_CONTINUE * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && g_Pause == false || GetGamePadTrigger(BUTTON_A, 0) && g_Pause == false)
	{
		//サウンド
		PlaySound(SOUND_LABEL_SE_ENTER);

		//決定キー(ENTERキー)が押された
		switch (g_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:    //ゲームに戻る
									 //モード設定(ゲーム画面に戻る)
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:       //ゲームをやり直す
									 //モード設定(ゲーム画面に移行)
			SetFade(MODE_GAME);
			g_Pause = false;
			break;

		case PAUSE_MENU_QUIT:        //タイトル画面に戻る
									 //モード設定(タイトル画面に移行)
			SetFade(MODE_TITLE);
			g_Pause = true;
			break;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}
//=========================================================================================
//ポーズの描画処理
//=========================================================================================
void CPause::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//ポリゴンの描画  四角形
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPause, 2);
	}
}

//=========================================================================================
//オブジェクトの設定処理
//=========================================================================================
CPause *CPause::Create(void)
{
	//ポインタの変数を宣言
	CPause *pPause;

	//オブジェクト2Dの生成
	pPause = new CPause;

	if (pPause != NULL)
	{//使用されているとき

		//初期化処理
		pPause->Init();
	}

	//オブジェクト情報を返す
	return pPause;
}
