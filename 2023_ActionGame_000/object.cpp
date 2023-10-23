//=========================================================================================
//
//[object.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "object.h"
#include "camera.h"
#include "manager.h"

//*****************************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************************
CObject *CObject::m_apObject[MAX_CHAR] = {};
int  CObject::m_nNumAll = 0;

//=========================================================================================
//�I�u�W�F�N�g�̃R���X�g���N�^
//=========================================================================================
CObject::CObject()
{
	//������
	m_type = TYPE_NONE;

	if(m_nNumAll > MAX_CHAR)
	{//�ő吔�𒴂�����

		//�������I���
		return;
	}

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		if (m_apObject[nCnt] == NULL)
		{//�g�p����Ă��Ȃ��Ƃ�

			m_apObject[nCnt] = this;	//�������g����
			m_nID = nCnt;				//�������g��ID��ۑ�
			m_nNumAll++;				//�I�u�W�F�N�g�������Z
			break;						//if�����甲����
		}
	}
}

//=========================================================================================
//�I�u�W�F�N�g�̃f�X�g���N�^
//=========================================================================================
CObject::~CObject()
{

}

//=========================================================================================
//�S�ẴI�u�W�F�N�g�j��
//=========================================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{//�g�p����Ă���Ƃ�

			//�I�u�W�F�N�g�̏I������
			m_apObject[nCnt]->Uninit();
		}
	}
}

//=========================================================================================
//�S�ẴI�u�W�F�N�g�X�V����
//=========================================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{//�g�p����Ă���Ƃ�

			//�I�u�W�F�N�g�̍X�V����
			m_apObject[nCnt]->Update();
		}
	}
}

//=========================================================================================
//�S�ẴI�u�W�F�N�g�`�揈��
//=========================================================================================
void CObject::DrawAll(void)
{
	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{//�g�p����Ă���Ƃ�

			//�I�u�W�F�N�g�̕`�揈��
			m_apObject[nCnt]->Draw();
		}
	}
}

//=========================================================================================
//�I�u�W�F�N�g�̔j��
//=========================================================================================
void CObject::Release(void)
{
	int nID = m_nID;

	if (m_apObject[nID] != NULL)
	{//�g�p����Ă���Ƃ�

		//�������g��j��
		delete m_apObject[nID];

		//�I�u�W�F�N�g�̏�����
		m_apObject[nID] = NULL;

		//�������J�E���g�_�E��
		m_nNumAll--;
	}
}

//=========================================================================================
//�I�u�W�F�N�g�̐ݒ�
//=========================================================================================
void CObject::SetType(TYPE type)
{
	//�^�C�v�ݒ�
	m_type = type;
}

//=========================================================================================SetPosition
//�I�u�W�F�N�g�^�C�v�̎擾
//=========================================================================================
CObject::TYPE CObject::GetType(void)
{
	//�^�C�v��Ԃ�
	return m_type;
}

//=========================================================================================
//�I�u�W�F�N�g�̎擾
//=========================================================================================
CObject *CObject::GetObject(int nIdx)
{
	return m_apObject[nIdx];
}

D3DXVECTOR3 CObject::GetPosition(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CObject::SetPosition(D3DXVECTOR3 pos)
{

}

D3DXVECTOR3 CObject::GetMove(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CObject::SetMove(D3DXVECTOR3 move)
{

}

D3DXVECTOR3 CObject::GetRot(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CObject::SetRot(D3DXVECTOR3 rot)
{

}

void CObject::SetVtxMax(D3DXVECTOR3 vtxMax)
{

}

D3DXVECTOR3 CObject::GetVtxMax(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CObject::SetVtxMin(D3DXVECTOR3 vtxMin)
{

}

D3DXVECTOR3 CObject::GetVtxMin(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CObject::Hit(void)
{

}

//HRESULT CObject::Init(int nType)
//{
//	return S_OK;
//}