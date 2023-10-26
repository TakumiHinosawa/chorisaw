
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
		m_apScore[nCntLine] = 0;
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
	CNumber::Load();

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
		//�I�u�W�F�N�g����
		m_apScore[nCntLine] = CScore::Create();

		//�Z�b�g�X�R�A
		m_apScore[nCntLine]->SetScore();

		//�ʒu�ݒ菈��
		m_apScore[nCntLine]->SetPosition(D3DXVECTOR3(300.0f, 200.0f + nCntLine * 140.0f, 0.0f));
	}

	//���[�h����
	Load();

	//�\�[�g����
	Sort();

	//�Z�[�u����
	Save();

	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		//�ʒu�ݒ菈��
		m_apScore[nCntLine]->SetPosition(D3DXVECTOR3(300.0f, 200.0f + nCntLine * 140.0f, 0.0f));
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
	CNumber::Unload();

	//********************************************************
	//�i���o�[�I������
	//********************************************************
	for (int nCntLine = 0; nCntLine < NUM_LINE; nCntLine++)
	{
		//�I�u�W�F�N�g�I��	
		m_apScore[nCntLine]->Uninit();
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	m_nCtr++;		//�J�E���^�[���Z

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//��ʑJ��
		CManager::GetManager()->SetMode(CScene::MODE_TITLE);
	}
	if (m_nCtr >= 350)
	{
		//��ʑJ��
		CManager::GetManager()->SetMode(CScene::MODE_TITLE);

		m_nCtr = 0;		//�J�E���^�[���Z�b�g
	}
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
		//�I�u�W�F�N�g�I��	
		m_apScore[nCntLine]->Draw();
	}
}

//=============================================================================
//���[�h����
//=============================================================================
void CRanking::Load(void)
{
	FILE *pFile = NULL;

	//�t�@�C���쐬
	pFile = fopen("data\\text\\ranking.txt", "r");

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
	pFile = fopen("data\\text\\ranking.txt", "w");

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
	{
		//�X�R�A�̎擾����
		int nScore = 0;

		FILE *pFile;

		//�t�@�C���쐬
		pFile = fopen("data\\text\\score.txt", "r");

		if (pFile == NULL)
		{//�t�@�C�����Ȃ������ꍇ
			return;
		}

		fscanf(pFile, "%d", &nScore);

		//�t�@�C�������
		fclose(pFile);

		if (nScore > m_aData[NUM_LINE - 1])
		{
			m_aData[NUM_LINE - 1] = nScore;
		}
	}

	//�~������(�\�[�g)
	for (int nCnt1 = 0; nCnt1 < NUM_LINE - 1; nCnt1++)
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < NUM_LINE; nCnt2++)
		{
			if (m_aData[nCnt1] < m_aData[nCnt2])
			{
				//��x�ʂ̕ϐ��Ƀf�[�^���m�ۂ��Ă���㏑������
				int nTemp = m_aData[nCnt1];
				m_aData[nCnt1] = m_aData[nCnt2];
				m_aData[nCnt2] = nTemp;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_LINE; nCnt++)
	{
		m_apScore[nCnt]->SetScoreRanking(m_aData[nCnt]);
	}
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

//=========================================================================================
//�擾����
//=========================================================================================
//int CRanking::GetScore(void)
//{
//	FILE *pFile = NULL;
//
//	//�t�@�C���쐬
//	pFile = fopen("text\\score.txt", "r");
//
//	if (pFile == NULL)
//	{//�t�@�C�����Ȃ������ꍇ
//		return;
//	}
//
//	fscanf(pFile, "%d", &m_aData[0]);
//
//	//�t�@�C�������
//	fclose(pFile);
//
//	return m_aData[0];
//}