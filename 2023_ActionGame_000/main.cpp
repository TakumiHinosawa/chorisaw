//=========================================================================================
//
//メイン [main.cpp]
//Author:日野澤匠泉
//
//=========================================================================================
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "manager.h"
#include <time.h>

//*****************************************************************************************
//マクロ定義
//*****************************************************************************************
#define CLASS_NAME		"WindowClass"		//ウインドクラスの名前
#define WINDOW_NAME		"チョリ走 ～チョリソーついに全ツッパの巻～"	//ウインドの名前

//*****************************************************************************************
//プロトタイプ宣言
//*****************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************************
//ぐろーばる宣言
//*****************************************************************************************
int g_nCountFPS = 0;							//FPSカウンター

//=========================================================================================
//メイン関数
//=========================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;		//最後に処理した時刻
	DWORD dwFrameCount;			//フレームカウンター
	DWORD dwFPSLastTime;		//最後にFPSを計測した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSのメモリサイズ
		CS_CLASSDC,							//ウインドウスタイル
		WindowProc,							//ウインドウプロシージャ
		0,									//0にする
		0,									//0にする
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウインドウハンドル(識別子)
		LoadIcon(NULL,IDI_APPLICATION)		//メッセージを格納する変数
	};

	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	HWND hWnd;			//ウインドウハンドル
	MSG msg;			//メッセージを格納する変数

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };	//画面サイズの構造体

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウインドスタイル
		CLASS_NAME,					//ウインドウクラスの名前
		WINDOW_NAME,				//ウインドウの名前
		WS_OVERLAPPEDWINDOW,		//ウインドウスタイル
		CW_USEDEFAULT,				//ウインドウ左上X座標
		CW_USEDEFAULT,				//ウインドウ左上Y座標
		SCREEN_WIDTH,				//ウインドウ幅
		SCREEN_HEIGHT,				//ウインドウ高さ
		NULL,						//親ウインドウのハンドル
		NULL,						//メニューまたは子ウインドウのID
		hInstance,					//インスタンスハンドル
		NULL);						//ウインドウ作成データ

	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得

	dwFrameCount = 0;					//初期化する
	dwFPSLastTime = timeGetTime();		//現在時刻を取得
	srand((unsigned int)time(NULL));

	//マネージャーのポインタ
	CManager *pManager = NULL;

	if (pManager == NULL)
	{//情報が無いとき

		//マネージャーの生成
		pManager = new CManager;
	}

	if (pManager != NULL)
	{//メモリが確保されてるとき

		//マネージャーの初期化処理
		pManager->Init(hInstance,hWnd,TRUE);
	}

	//ウインドの表示
	ShowWindow(hWnd, nCmdShow);			//ウインドウの表示状態を設定
	UpdateWindow(hWnd);					//クライアント領域を更新

										//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  //ウインドウプロシージャへメッセージを送出
			}

		}

		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5秒経過
			//FPSを計測
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			dwFPSLastTime = dwCurrentTime;		//FPSを計測した時刻を保存
			dwFrameCount = 0;					//フレームカウントをクリア

		}

		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				dwFrameCount++;		//フレームカウントを加算

				//更新処理
				pManager->Update();

				//描画処理
				pManager->Draw();
			}
		}
	}

	if (pManager != NULL)
	{//レンダラー情報があった時

		//終了処理
		pManager->Uninit();

		//メモリ開放
		delete pManager;

		//マネージャー初期化
		pManager = NULL;
	}

	//全てのオブジェクトを破棄
	CObject::ReleaseAll();

	//ウインドクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================================================================
//ウインドウプロシージャ
//=========================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;													//返り値を格納
	char aString[256] = "test";									//描画するテキストを格納
	static POINT pos = { 100,100 };								//線分の始点(X座標・Y座標)
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//ウインドウの領域
	static POINT move = { 2,3 };								//線分の視点移動量(X方向・Y方向)

	switch (uMsg)
	{
	case WM_DESTROY:		//ウインドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_CLOSE:			//閉じるボタンの押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{//終了ボタンが押された

			//ウインドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0を返さないと終了してしまう
		}
		break;

	case WM_KEYDOWN:		//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//ESCキーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

