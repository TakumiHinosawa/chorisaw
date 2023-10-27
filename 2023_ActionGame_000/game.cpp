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
		{ CBuilding::TYPE_THIN, 19800.0f,50.0f,0.0f },

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

		{ CBuilding::TYPE_THIN, 32700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 33100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 33500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 33900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 34300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 34700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 35100.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 35500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 35900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 36400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 36900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 37400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 37900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 38400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 38800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 39200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 39700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 40000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 40300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 40700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 41000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 41300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 41700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 42000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 42400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 42800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 43200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 43600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 44000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 44400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 44700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 45900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 46300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 46700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 47900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 48400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 48900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 49400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 49800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 50200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 50700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 51700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 52700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 53800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 54200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 54600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 55000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 55400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 55700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 56100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 56500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 56900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 57300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 57700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 58900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 59400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 59900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 60400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 60800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 61200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 61700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 62000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 62300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 62700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 63700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 64000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 64400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 64800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 65200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 65600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_NORMAL, 66000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 66400.0f,50.0f,0.0f },

		{ CBuilding::TYPE_THIN, 66700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67100.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67500.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 67900.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 68300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 68700.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 69900.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 70400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 70900.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 71400.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 71800.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 72200.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 72700.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73000.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73300.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 73700.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74000.0f,100.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74300.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 74700.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75400.0f,150.0f,0.0f },
		{ CBuilding::TYPE_THIN, 75800.0f,200.0f,0.0f },
		{ CBuilding::TYPE_THIN, 76200.0f,-50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 76600.0f,0.0f,0.0f },
		{ CBuilding::TYPE_THIN, 77000.0f,50.0f,0.0f },
		{ CBuilding::TYPE_THIN, 77400.0f,50.0f,0.0f },

		// �ǎ�
		{ CBuilding::TYPE_WALLPAPER, 2200.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 5500.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 8800.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 11100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 14400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 17700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 21700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 25000.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 28300.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 31600.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 34900.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 37200.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 40500.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 43800.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 47100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 50400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 53700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 54100.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 57400.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 60700.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 64000.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 67300.0f,0.0f,80.0f },
		{ CBuilding::TYPE_WALLPAPER, 70600.0f,0.0f,80.0f },
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
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

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

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 pos = m_pPlayerX->GetPosition();
	
	if (pos.y <= -700.0f)
	{// �v���C���[���������ꍇ

		//�T�E���h���擾
		CSound *pSound = CManager::GetManager()->GetSound();

		//�T�E���h�̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DOWN);

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
