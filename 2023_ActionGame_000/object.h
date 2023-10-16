//=========================================================================================
//
//[object.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _OBJECT_H_			//このマクロ定義がされなかったら
#define _OBJECT_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//オブジェクトクラス
//*****************************************************************************************
class CObject
{
public:

	//種類の列挙型定義
	typedef enum
	{
		TYPE_NONE = 0,		//何も無いとき
		TYPE_PLAYER,		//プレイヤー
		TYPE_BUILDING,		//建物
		TYPE_TITLE,			//タイトル
		TYPE_RESULT,		//リザルト
		TYPE_TUTORIAL,		//チュートリアル
		TYPE_MAX
	}TYPE;

	CObject();
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,float fHeight,float fWidth) = 0;

	virtual D3DXVECTOR3 GetPosition(void);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetMove(void);
	virtual void SetMove(D3DXVECTOR3 move);
	virtual D3DXVECTOR3 GetRot(void);
	virtual void SetRot(D3DXVECTOR3 rot);

	virtual void SetVtxMax(D3DXVECTOR3 vtxMax);
	virtual D3DXVECTOR3 GetVtxMax(void);

	virtual void SetVtxMin(D3DXVECTOR3 vtxMin);
	virtual D3DXVECTOR3 GetVtxMin(void);

	//virtual void SetColor(void);

	virtual void Hit(void);

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetType(TYPE type);
	TYPE GetType(void);
	static CObject *GetObject(int nIdx);

protected:
	void Release(void);

private:
	static CObject *m_apObject[MAX_CHAR];	//オブジェクト情報
	static int m_nNumAll;		//オブジェクト総数
	int m_nID;					//自分自身のID
	TYPE m_type;				//タイプ
};

#endif
