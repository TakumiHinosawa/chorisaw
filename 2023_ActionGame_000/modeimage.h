//=========================================================================================
//
//[modeimage.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _MODEIMAGE_H_			//このマクロ定義がされなかったら
#define _MODEIMAGE_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************************************************
//モードイメージクラス
//*****************************************************************************************
class CModeImage : public CObject2D
{
public:
	CModeImage();
	~CModeImage();

	static HRESULT Load(int nType);
	static void Unload(void);
	HRESULT Init(int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModeImage *Create(int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ情報
	CObject2D *m_pModeImage;
};

#endif