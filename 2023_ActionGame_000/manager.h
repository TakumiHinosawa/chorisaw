//=========================================================================================
//
//[manager.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _MANAGER_H_			//���̃}�N����`������Ȃ�������
#define _MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�O���錾
//*****************************************************************************************
class CInputKeyboard;
class CInputController;
class CRenderer;
class CDebugProc;
class CSound;

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//�V�[���N���X
//*****************************************************************************************
class CScene
{
public:

	//���[�h�̗񋓌^��`
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
	MODE m_mode;	//���[�h���
};

//*****************************************************************************************
//�}�l�[�W���N���X
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

