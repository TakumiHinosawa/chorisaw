//=========================================================================================
//
//[game.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _GAME_H_			//���̃}�N����`������Ȃ�������
#define _GAME_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "manager.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define NUM_BUILD	(94)		//�����ő吔

//*****************************************************************************************
//�O���錾
//*****************************************************************************************
class CSound;
class CScore;
class CCamera;
class CLight;
class CObjectX;
class CBuilding;
class CDebugProc;
class CPlayerX;
class CObject;

//*****************************************************************************************
//�Q�[���N���X��`
//*****************************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGame *Create(void);

	static CPlayerX *GetPlayer(void);
	static CScore *GetScore(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CObjectX *GetObjectX(void);
	static CBuilding *GetBuilding(int nIdx);

private:
	static CPlayerX *m_pPlayerX;
	static CScore *m_pScore;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CObjectX *m_pObjectX;
	static CBuilding *m_apBuilding[NUM_BUILD];
	int m_nCtr;
};

#endif

