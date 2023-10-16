//=========================================================================================
//
//[manager.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _MANAGER_H_			//このマクロ定義がされなかったら
#define _MANAGER_H_			//2重インクルード防止のマクロ定義する

//*****************************************************************************************
//前方宣言
//*****************************************************************************************
class CInputKeyboard;
class CInputController;
class CRenderer;
class CDebugProc;
class CSound;

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//シーンクラス
//*****************************************************************************************
class CScene
{
public:

	//モードの列挙型定義
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	}MODE;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	MODE GetMode(void);
	void SetMode(MODE mode);
	static CScene *Create(MODE mode);

private:
	MODE m_mode;	//モード情報
};

//*****************************************************************************************
//マネージャクラス
//*****************************************************************************************
class CManager
{
public:
	CManager();
	virtual ~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputController *GetInputController(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDebugProc(void);
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);

private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputController *m_pInputController;
	static CSound *m_pSound;
	static CDebugProc *m_pDebugProc;
	static CScene *m_pScene;
};

#endif

