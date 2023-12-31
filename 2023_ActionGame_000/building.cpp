//=========================================================================================
//
// ビルディング
// Author:日野澤匠泉	[playerX.cpp]
//
//=========================================================================================
#include "main.h"
#include "building.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "game.h"

//=========================================================================================
//マクロ定義
//=========================================================================================

//=========================================================================================
//ビルディングのコンストラクタ	
//=========================================================================================
CBuilding::CBuilding()
{
	m_Type = TYPE_NORMAL;
}

//=========================================================================================
//ビルディングのデストラクタ
//=========================================================================================
CBuilding::~CBuilding()
{

}

//=========================================================================================
//ビルディングの初期化処理
//=========================================================================================
HRESULT CBuilding::Init(void)
{
	//オブジェクトの初期化処理
	CObjectX::Init("data\\MODEL\\tentative.x");

	//種類の設定
	CObject::SetType(TYPE_BUILDING);

	return S_OK;
}

//=========================================================================================
//ビルディングの終了処理
//=========================================================================================
void CBuilding::Uninit(void)
{
	//オブジェクトの終了処理
	CObjectX::Uninit();
}

//=========================================================================================
//ビルディングの更新処理
//=========================================================================================
void CBuilding::Update(void)
{

}

//=========================================================================================
//ビルディングの描画処理
//=========================================================================================
void CBuilding::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}

//=========================================================================================
//ビルディングの生成処理
//=========================================================================================
CBuilding *CBuilding::Create(void)
{
	//ポインタの変数を宣言
	CBuilding *pBuilding;

	//オブジェクト3Dの生成
	pBuilding = new CBuilding;

	if (pBuilding != NULL)
	{//使用されているとき

		//初期化処理
		pBuilding->Init();
	}

	//オブジェクト情報を返す
	return pBuilding;
}

//=========================================================================================
//ビルディングの設定処理
//=========================================================================================
void CBuilding::SetType(TYPE type)
{
	m_Type = type;

	switch (m_Type)
	{
	case TYPE_NORMAL:
		CObjectX::ReloadObject("data\\MODEL\\tentative.x");
		break;

	case TYPE_THIN:
		CObjectX::ReloadObject("data\\MODEL\\building_thin.x");
		break;

	case TYPE_WALL:
		CObjectX::ReloadObject("data\\MODEL\\building_wall.x");
		break;

	case TYPE_WALLPAPER:
		CObjectX::ReloadObject("data\\MODEL\\wallpaper.x");
		break;

	case TYPE_SKY:
		CObjectX::ReloadObject("data\\MODEL\\sky.x");
		break;

	case TYPE_START:
		CObjectX::ReloadObject("data\\MODEL\\start.x");
		break;
	}
}

//=========================================================================================
//ビルディングの取得処理
//=========================================================================================
CBuilding::TYPE CBuilding::GetType(void)
{
	return m_Type;
}