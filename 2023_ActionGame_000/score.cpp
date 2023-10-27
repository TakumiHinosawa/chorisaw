//=========================================================================================
//
//�X�R�A�\������ [score.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "score.h"
#include "number.h"
#include "object2d.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include <stdio.h>

//=========================================================================================
//�R���X�g���N�^
//=========================================================================================
CScore::CScore()
{
	m_nScore = 0;
	m_nValue = 0;
	m_nCtr = 0;
	m_Dist = 0;
	m_pos = D3DXVECTOR3( 0.0f,0.0f,0.0f );

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

//=========================================================================================
//�f�X�g���N�^
//=========================================================================================
CScore::~CScore()
{

}

//=========================================================================================
//�X�R�A�̏���������
//=========================================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//�I�u�W�F�N�g����
		m_apNumber[nCnt] = CNumber::Create();
	}

	return S_OK;
}

//=========================================================================================
//�X�R�A�̏I������
//=========================================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{//�g�p����Ă���Ƃ�

			//�I�u�W�F�N�g�I������
			m_apNumber[nCnt]->Uninit();

			//�I�u�W�F�N�g��j��
			delete m_apNumber[nCnt];

			//�I�u�W�F�N�g������
			m_apNumber[nCnt] = NULL;
		}
	}
}

//=========================================================================================
//�X�R�A�̍X�V����
//=========================================================================================
void CScore::Update(void)
{
	//�Z�b�g�X�R�A
	SetScore();
}

//=========================================================================================
//�X�R�A�̕`�揈��
//=========================================================================================
void CScore::Draw(void)
{

}

//=========================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================
CScore *CScore::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CScore *pScore;

	//�I�u�W�F�N�g2D�̐���
	pScore = new CScore;

	if (pScore != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pScore->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pScore;
}

//=========================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================
void CScore::SetScore(void)
{
	int aTexU[NUM_PLACE];		//�e���̐��l���i�[

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//�X�R�A�̐ݒ菈��
		m_apNumber[nCnt]->SetScore(D3DXVECTOR3(500.0f,10.0f,0.0f), nCnt, aTexU[nCnt]);
	}
}

//=========================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================
void CScore::SetScoreRanking(int nNum)
{
	int aTexU[NUM_PLACE];		//�e���̐��l���i�[

	m_nScore = nNum;

	aTexU[0] = nNum % 100000 / 10000;
	aTexU[1] = nNum % 10000 / 1000;
	aTexU[2] = nNum % 1000 / 100;
	aTexU[3] = nNum % 100 / 10;
	aTexU[4] = nNum % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//�X�R�A�̐ݒ菈��
		m_apNumber[nCnt]->SetScore(D3DXVECTOR3(600.0f, 10.0f, 0.0f), nCnt, aTexU[nCnt]);
	}
}

//=========================================================================================
//�X�R�A�̉��Z����
//=========================================================================================
void CScore::AddScore(int nValue)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	int aTexU[NUM_PLACE];		//�e���̐��l���i�[

	m_nScore += nValue;

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	if (m_nScore > 1000 && m_Dist == 0)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_1000M);

		m_Dist = 1;
	}
	if (m_nScore > 2000 && m_Dist == 1)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_2000M);

		m_Dist = 2;
	}
	if (m_nScore > 3000 && m_Dist == 2)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_3000M);

		m_Dist = 3;
	}
	if (m_nScore > 4000 && m_Dist == 3)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_4000M);

		m_Dist = 4;
	}
	if (m_nScore > 5000 && m_Dist == 4)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_5000M);

		m_Dist = 5;
	}
	if (m_nScore > 6000 && m_Dist == 5)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_6000M);

		m_Dist = 6;
	}
	if (m_nScore > 7000 && m_Dist == 6)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_7000M);

		m_Dist = 7;
	}
	if (m_nScore > 8000 && m_Dist == 7)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_8000M);

		m_Dist = 8;
	}
}

//=========================================================================================
//�X�R�A�̌��Z����
//=========================================================================================
void CScore::SubScore(int nValue)
{
	int aTexU[NUM_PLACE];		//�e���̐��l���i�[

	if (m_nScore <= 0)
	{//�X�R�A��0�ȉ��̏ꍇ

		return;
	}

	m_nScore -= nValue;

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;
}

//=========================================================================================
//�X�R�A�̕ۑ�
//=========================================================================================
void CScore::SaveScore(void)
{
	FILE *pFile;

	//�t�@�C���쐬
	pFile = fopen("data\\text\\score.txt", "w");

	if (pFile == NULL)
	{//�t�@�C�����Ȃ������ꍇ
		return;
	}

	fprintf(pFile, "%d", m_nScore - 2);

	//�t�@�C�������
	fclose(pFile);
}

//=========================================================================================
//�X�R�A�̎擾
//=========================================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=========================================================================================
//�X�R�A�̈ʒu�ݒ菈��
//=========================================================================================
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	int aTexU[NUM_PLACE];		//�e���̐��l���i�[

	aTexU[0] = m_nScore % 100000 / 10000;
	aTexU[1] = m_nScore % 10000 / 1000;
	aTexU[2] = m_nScore % 1000 / 100;
	aTexU[3] = m_nScore % 100 / 10;
	aTexU[4] = m_nScore % 10;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//�X�R�A�̐ݒ菈��
		m_apNumber[nCnt]->SetScore(pos, nCnt, aTexU[nCnt]);
	}
}