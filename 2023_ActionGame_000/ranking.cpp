
//=============================================================================
//
// ranking
// Author : Hinosawa Takumi
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include "ranking.h"
#include "input.h"
#include "modeimage.h"
#include "score.h"
#include <stdio.h>
#include "number.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_nValue = 0;			
	m_nScore = 0;			
	m_nCounter = 0;		
	m_nCtr = 0;

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		m_aData[nCntLine] = 0;
	}

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			m_apNumber[nCntLine][nCntPlace] = 0;
		}
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//********************************************************
	//�e�N�X�`���ǂݍ���
	//********************************************************
	m_pModeImage->Load(1);

	//�w�i����
	m_pModeImage = CModeImage::Create(1);

	if (m_pModeImage != nullptr)
	{
		//������
		m_pModeImage = nullptr;
	}
	else
	{
		//����������
		m_pModeImage->Init(1);
	}

	//********************************************************
	//�i���o�[����
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//�X�R�A�̃��[�h
			m_apNumber[nCntLine][nCntPlace]->Load();

			//�I�u�W�F�N�g����
			m_apNumber[nCntLine][nCntPlace] = CNumber::Create();

			//�Z�b�g�X�R�A
			m_apNumber[nCntLine][nCntPlace]->SetScore(D3DXVECTOR3(350.0f + nCntPlace * 30.0f, 200.0f + nCntLine * 140.0f, 0.0f), 
				nCntPlace, 0);
		}
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CRanking::Uninit(void)
{
	if (m_pModeImage != nullptr)
	{
		//�I������
		m_pModeImage->Uninit();

		//������
		m_pModeImage = nullptr;
	}

	//********************************************************
	//�e�N�X�`���j��
	//********************************************************
	m_pModeImage->Unload();

	//********************************************************
	//�i���o�[�I������
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//�X�R�A�̃A�����[�h
			m_apNumber[nCntLine][nCntPlace]->Unload();

			//�I�u�W�F�N�g�I��	
			m_apNumber[nCntLine][nCntPlace]->Uninit();
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CRanking::Update(void)
{
	m_nCtr++;		//�J�E���^�[���Z

	//if (m_nCtr >= 200)
	//{
	//	//��ʑJ��
	//	CManager::GetManager()->SetMode(CScene::MODE_TITLE);

	//	m_nCtr = 0;		//�J�E���^�[���Z�b�g
	//}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	//********************************************************
	//�i���o�[�`�揈��
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			//�I�u�W�F�N�g�I��	
			m_apNumber[nCntLine][nCntPlace]->Draw();
		}
	}
}

//=============================================================================
//���[�h����
//=============================================================================
void CRanking::Load(void)
{
	FILE *pFile = NULL;

	//�t�@�C���쐬
	pFile = fopen("text\\ranking.txt", "r");

	if (pFile == NULL)
	{//�t�@�C�����Ȃ������ꍇ
		return;
	}

	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		fscanf(pFile, "%d", &m_aData[nCnt]);
	}

	//�t�@�C�������
	fclose(pFile);
}

//=============================================================================
//�Z�[�u����
//=============================================================================
void CRanking::Save(void)
{
	FILE *pFile;

	//�t�@�C���쐬
	pFile = fopen("text\\ranking.txt", "w");

	if (pFile == NULL)
	{//�t�@�C�����Ȃ������ꍇ
		return;
	}
	
	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		fprintf(pFile, "%d\n", m_aData[nCnt]);
	}

	//�t�@�C�������
	fclose(pFile);
}

//=============================================================================
//�\�[�g����
//=============================================================================
void CRanking::Sort(void)
{
	////�X�R�A���擾
	//int nScore = CScore::GetScore();	//�X�R�A���擾

	//if (nScore > m_aData[NUM_LINE - 1])
	//{
	//	m_aData[NUM_LINE - 1] = nScore;
	//}
}

//=========================================================================================
//��������
//=========================================================================================
CRanking *CRanking::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CRanking *pRanking;

	//����
	pRanking = new CRanking;

	if (pRanking != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pRanking->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pRanking;
}