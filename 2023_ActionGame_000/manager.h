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

	CRenderer *GetRenderer(void);
	CInputKeyboard *GetInputKeyboard(void);
	CInputController *GetInputController(void);
	CSound *GetSound(void);
	CDebugProc *GetDebugProc(void);
	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void);
	static CManager *GetManager(void);

private:
	CRenderer *m_pRenderer;
	CInputKeyboard *m_pInputKeyboard;
	CInputController *m_pInputController;
	CSound *m_pSound;
	CDebugProc *m_pDebugProc;
	CScene *m_pScene;
	static CManager *m_pManager;
};

#endif

