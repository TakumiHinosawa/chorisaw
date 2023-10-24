//=========================================================================================
//
//[game.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "number.h"
#include "score.h"
#include "light.h"
#include "camera.h"
#include "playerx.h"
#include "time.h"
#include "game.h"
#include "input.h"
#include "string.h"
#include "sound.h"
#include "manager.h"
#include "building.h"
#include <stdio.h>

//*****************************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************************
CPlayerX *CGame::m_pPlayerX = NULL;
CScore *CGame::m_pScore = NULL;
CCamera *CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CObjectX *CGame::m_pObjectX = NULL;
CBuilding *CGame::m_apBuilding[NUM_BUILD] = {};

//=========================================================================================
//�Q�[���̃R���X�g���N�^
//=========================================================================================
CGame::CGame()
{

}

//=========================================================================================
//�Q�[���̃f�X�g���N�^	
//=========================================================================================
CGame::~CGame()
{

}

//=========================================================================================
//�Q�[���̏���������	
//=========================================================================================
HRESULT CGame::Init(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//********************************************************
	//�J�����̐���
	//********************************************************
	if (m_pCamera == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//����
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//�g�p����Ă���Ƃ�

		//�J�����̏���������
		m_pCamera->Init();
	}

	//********************************************************
	//���C�g�̐���
	//********************************************************
	if (m_pLight == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//����
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//�g�p����Ă���Ƃ�

		//���C�g�̏���������
		m_pLight->Init();
	}

	//********************************************************
	//�e�N�X�`���ǂݍ���
	//********************************************************
	CNumber::Load();

	//********************************************************
	//�v���C���[
	//********************************************************
	if (m_pPlayerX == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�v���C���[�쐬
		m_pPlayerX = CPlayerX::Create();
	}

	//********************************************************
	//���� �z�u
	//********************************************************

	//�����z�u�̍\���̒�`
	struct SBuildingInfo
	{
		CBuilding::TYPE mType;
		float mX;
		float mY;
		float mZ;
	};

	SBuildingInfo buildingInfo[] =
	{
		// �`���[�g���A�� 
		{ CBuilding::TYPE_START, 1800.0f,-200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL,800.0f,-30.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 1200.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 1600.0f,90.0f,0.0f },
		{ CBuilding::TYPE_THIN, 1900.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2300.0f,210.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2500.0f,270.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 2500.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 2800.0f,90.0f,0.0f },

		// ���x��1 (�W�����v���K)
		{ CBuilding::TYPE_NORMAL, 3700.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4100.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4500.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 4900.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 5400.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6000.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 6600.0f,-100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7100.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 7600.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 8200.0f,-100.0f,0.0f },

		// ���x��2
		{ CBuilding::TYPE_THIN, 8500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 9500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10300.0f,30.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10600.0f,70.0f,0.0f },
		{ CBuilding::TYPE_THIN, 10600.0f,70.0f,0.0f },
		{ CBuilding::TYPE_THIN, 11100.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 11600.0f,-50.0f,0.0f },

		//���x�� 3
		{ CBuilding::TYPE_NORMAL, 12100.0f,100.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 12600.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 13000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 13500.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14000.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14500.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 14900.0f,0.0f,0.0f },

		// �����፬��
		{ CBuilding::TYPE_NORMAL, 15300.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN,	  15700.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 16300.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN,   16700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 17100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 17500.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN,   17900.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 18300.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 18800.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 19300.0f,50.0f,0.0f },

		// �K�i�@����
		{ CBuilding::TYPE_THIN, 20000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20050.0f,80.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20100.0f,60.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20150.0f,40.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20200.0f,20.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20250.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 20300.0f,-20.0f,0.0f },

		// �����፬�� ���x���}�b�N�X
		{ CBuilding::TYPE_NORMAL, 20700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 21100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 21500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 21900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 22300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 22700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 23100.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 23500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 23900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 24400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 24900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 25400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 25900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 26400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 26800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 27200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 27700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 28000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 28300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 28700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 29000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 29300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 29700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 30000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 30400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 30800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 31200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 31600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 32000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 32400.0f,50.0f,0.0f },

		// �ǎ�
		{ CBuilding::TYPE_WALLPAPER, 2200.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 5500.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 8800.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 11100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 14400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 17700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 21700.0f,0.0f,80.0f },
	};

	for (int nCnt = 0; nCnt < NUM_BUILD; nCnt++)
	{
		if (m_apBuilding[nCnt] == NULL)
		{//�g�p����Ă��Ȃ��Ƃ�

			//�v���C���[�쐬
			m_apBuilding[nCnt] = CBuilding::Create();
			m_apBuilding[nCnt]->SetType(buildingInfo[nCnt].mType);
			m_apBuilding[nCnt]->SetPosition(D3DXVECTOR3(buildingInfo[nCnt].mX, buildingInfo[nCnt].mY, buildingInfo[nCnt].mZ));
		}
	}

	//********************************************************
	//�X�R�A
	//********************************************************
	if (m_pScore == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�X�R�A�I�u�W�F�N�g�̏����擾
		m_pScore = CScore::Create();

		//�I�u�W�F�N�g�ݒ�
		m_pScore->SetScore();
	}

	//********************************************************
	//�T�E���h
	//********************************************************
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=============================================================================
//�Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//********************************************************
	//�X�R�A
	//********************************************************
	if (m_pScore != NULL)
	{//�g�p����Ă�����

		//�X�R�A�̏I������
		m_pScore->Uninit();

		//�j��
		delete m_pScore;

		//������
		m_pScore = NULL;
	}

	//********************************************************
	//���C�g
	//********************************************************
	if (m_pLight != NULL)
	{
		//�I������
		m_pLight->Uninit();

		//�j��
		delete m_pLight;

		//������
		m_pLight = NULL;
	}

	//********************************************************
	//�J����
	//********************************************************	
	if (m_pCamera != NULL)
	{
		//�I������
		m_pCamera->Uninit();

		//�j��
		delete m_pCamera;

		//������
		m_pCamera = NULL;
	}

	//********************************************************
	//�v���C���[
	//********************************************************
	if (m_pPlayerX != NULL)
	{//�g�p����Ă���Ƃ�

		//������
		m_pPlayerX = NULL;
	}

	//********************************************************
	//����
	//********************************************************
	for (int nCnt = 0; nCnt < NUM_BUILD; nCnt++)
	{
		if (m_apBuilding != NULL)
		{//�g�p����Ă���Ƃ�

			//������
			m_apBuilding[nCnt] = NULL;
		}
	}

	//�e��e�N�X�`���j��
	CNumber::Unload();
}

//=============================================================================
//�Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	//********************************************************
	//�X�R�A
	//********************************************************
	if (m_pScore != NULL)
	{//�g�p����Ă�����

		//�X�V����
		m_pScore->Update();

		//�X�R�A�̍X�V
		m_pScore->AddScore(1);
	}

	//********************************************************
	//�J����
	//********************************************************
	if (m_pCamera != NULL)
	{//�g�p����Ă�����

		//�X�V����
		m_pCamera->Update();
	}

	if (m_pScore->GetScore() >= 1000)
	{
		m_pPlayerX->GetMove();


	}

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 pos = m_pPlayerX->GetPosition();
	
	if (pos.y <= -700.0f)
	{// �v���C���[���������ꍇ

		if (m_pScore != NULL)
		{//�g�p����Ă�����

			//�X�R�A�̕ۑ�
			m_pScore->SaveScore();
		}

		//��ʑJ��
		CManager::GetManager()->SetMode(CScene::MODE_RANKING);
	}
}

//=============================================================================
//�Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{
	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();

	//�J�����̕`��
	pCamera->SetCamera();
}

//=========================================================================================
//�Q�[���̐�������
//=========================================================================================
CGame *CGame::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CGame *pGame;

	//����
	pGame = new CGame;

	if (pGame != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pGame->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pGame;
}

//=========================================================================================
//�v���C���[���擾
//=========================================================================================
CPlayerX *CGame::GetPlayer(void)
{
	return m_pPlayerX;
}

//=========================================================================================
//�X�R�A���擾
//=========================================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=========================================================================================
//�J�����̏��擾
//=========================================================================================
CCamera *CGame::GetCamera(void)
{
	return m_pCamera;
}

//=========================================================================================
//���C�g�̏��擾
//=========================================================================================
CLight *CGame::GetLight(void)
{
	return m_pLight;
}

//=========================================================================================
//���C�g�̏��擾
//=========================================================================================
CObjectX *CGame::GetObjectX(void)
{
	return m_pObjectX;
}

//=========================================================================================
//�����̏��擾
//=========================================================================================
CBuilding *CGame::GetBuilding(int nIdx)
{
	return m_apBuilding[nIdx];
}
