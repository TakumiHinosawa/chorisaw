//=========================================================================================
//
// ���f��
// Author:�����V����	[objectX.cpp]
//
//=========================================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define MAX_XFILE	(4)		//�I�u�W�F�N�g�ő吔

//=========================================================================================
//���f���̃R���X�g���N�^	
//=========================================================================================
CObjectX::CObjectX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fHeight = 0.0f;
	m_fWidth = 0.0f;

	m_dwNumMat = 0;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_pTexture = NULL;

	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	m_nNumVtx = 0;		
	m_dwSizeFVF = 0;	
	m_pVtxBuff = NULL;		

	bUse = false;
}
	
//=========================================================================================
//���f���̃f�X�g���N�^
//=========================================================================================
CObjectX::~CObjectX()
{

}

//=========================================================================================
//���f���̏���������
//=========================================================================================
HRESULT CObjectX::Init(void)
{
	//�I�u�W�F�N�g���擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//�ߋ��̈ʒu��ۑ�
	m_posOld = m_pos;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\chorizo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//���_�����擾
	m_nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//���_���W�̑��

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//���_���W�̑��(���f���̒��_��)

		//�ő吔�A�ŏ��������o��
		if (m_vtxMax.x <= vtx.x)
		{	
			m_vtxMax.x = vtx.x;
		}	
		if (m_vtxMax.z <= vtx.z)
		{	
			m_vtxMax.z = vtx.z;
		}	
		if (m_vtxMin.x >= vtx.x)
		{	
			m_vtxMin.x = vtx.x;
		}	
		if (m_vtxMin.z >= vtx.z)
		{	
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//�g�p����Ă�����

		//�������J��
		delete[] m_pTexture;

		//������������
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�������m��
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}

	//�I�u�W�F�N�g�̔z�u
	Set(m_pos, m_rot, 0, 0);

	return S_OK;
}

//=========================================================================================
//���f���̏���������
//=========================================================================================
HRESULT CObjectX::Init(char *pFilename)
{
	//�I�u�W�F�N�g���擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//�ߋ��̈ʒu��ۑ�
	m_posOld = m_pos;

	bUse = false;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//���_�����擾
	m_nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//���_���W�̑��

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//���_���W�̑��(���f���̒��_��)
		
		//�ő吔�A�ŏ��������o��
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}

		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	if (m_pBuffMat == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		return E_FAIL;
	}

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//�g�p����Ă�����

		//�������J��
		delete[] m_pTexture;

		//������������
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�������m��
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = NULL;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
		else
		{
			//������
			m_pTexture[nCntMat] = NULL;
		}
	}

	return S_OK;
}

//=========================================================================================
//���f���̏I������
//=========================================================================================
void CObjectX::Uninit(void)
{
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{//NULL����Ȃ������ꍇ

		//��������j������
		delete[] m_pTexture;

		//�g�p����Ă��Ȃ���Ԃɂ���
		m_pTexture = NULL;
	}

	if (m_pBuffMat != NULL)
	{//��񂪓����Ă�����

		//�����������
		m_pBuffMat->Release();

		//������
		m_pBuffMat = NULL;
	}

	//�J��
	Release();
}

//=========================================================================================
//���f���̍X�V����
//=========================================================================================
void CObjectX::Update(void)
{
	//���݂̈ʒu��ۑ�
	m_posOld = m_pos;

	m_rot.y -= 0.01f;

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		bUse = true;
	}
	if (bUse == true)
	{
		m_rot.y -= 0.76f;
		m_pos.y += 0.89f;
	}
}

//=========================================================================================
//���f���̕`�揈��
//=========================================================================================
void CObjectX::Draw(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=========================================================================================
//���f���̐ݒ菈�� (�� * �����@�����s��)
//=========================================================================================
void CObjectX::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//���f���̐�������
//=========================================================================================
CObjectX *CObjectX::Create(char *pFilename)
{
	//�|�C���^�̕ϐ���錾
	CObjectX *pObectX;

	//�I�u�W�F�N�g3D�̐���
	pObectX = new CObjectX;

	if (pObectX != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pObectX->Init(pFilename);
	}

	//�I�u�W�F�N�g����Ԃ�
	return pObectX;
}

//=========================================================================================
//���f���̍ēǂݍ���
//=========================================================================================
void CObjectX::ReloadObject(char *pFilename)
{
	//�I�u�W�F�N�g���擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{//NULL����Ȃ������ꍇ

		//��������j������
		delete[] m_pTexture;

		//�g�p����Ă��Ȃ���Ԃɂ���
		m_pTexture = NULL;
	}

	if (m_pBuffMat != NULL)
	{//��񂪓����Ă�����

		//�����������
		m_pBuffMat->Release();

		//������
		m_pBuffMat = NULL;
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//���_�����擾
	m_nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);		//���_���W�̑��

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;		//���_���W�̑��(���f���̒��_��)

		//�ő吔�A�ŏ��������o��
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}
		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		m_pVtxBuff += m_dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{//�g�p����Ă�����

		//�������J��
		delete[] m_pTexture;

		//������������
		m_pTexture = NULL;
	}

	if (m_pTexture == NULL)
	{//�g�p����Ă��Ȃ��Ƃ�

		//�������m��
		m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	}

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = NULL;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
		else
		{
			//������
			m_pTexture[nCntMat] = NULL;
		}
	}
}

//=========================================================================================
//���f���̈ʒu�擾����
//=========================================================================================
D3DXVECTOR3 CObjectX::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//���f���̌��݂̈ʒu�擾����
//=========================================================================================
D3DXVECTOR3 CObjectX::GetPositionOld(void)
{
	return m_posOld;
}

//=========================================================================================
//���f���̈ʒu�ݒ菈��
//=========================================================================================
void CObjectX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//���f���̌��݂̈ʒu�ݒ菈��
//=========================================================================================
void CObjectX::SetPositionOld(D3DXVECTOR3 pos)
{
	m_posOld = pos;
}

//=========================================================================================
//���f���̈ړ��擾
//=========================================================================================
D3DXVECTOR3 CObjectX::GetMove(void)
{
	return m_move;
}

//=========================================================================================
//���f���̈ړ��ݒ菈��
//=========================================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=========================================================================================
//���f���̌����擾
//=========================================================================================
D3DXVECTOR3 CObjectX::GetRot(void)
{
	return m_rot;
}

//=========================================================================================
//���f���̌����ݒ菈��
//=========================================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=========================================================================================
//���f���̍����ݒ菈��
//=========================================================================================
float CObjectX::GetHeight(void)
{
	return m_fHeight;
}

//=========================================================================================
//���f���̕��ݒ菈��
//=========================================================================================
float CObjectX::GetWidth(void)
{
	return m_fWidth;
}

//=========================================================================================
//���f���̕��ݒ菈��
//=========================================================================================
void CObjectX::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//�o�[�e�b�N�X�ő�l�̐ݒ菈��
//=========================================================================================
void CObjectX::SetVtxMax(D3DXVECTOR3 vtxMax)
{
	m_vtxMax = vtxMax;
}

//=========================================================================================
//�o�[�e�b�N�X�ő�l�̎擾����
//=========================================================================================
D3DXVECTOR3 CObjectX::GetVtxMax(void)
{
	return m_vtxMax;
}

//=========================================================================================
//�o�[�e�b�N�X�ŏ��l�̐ݒ菈��
//=========================================================================================
void CObjectX::SetVtxMin(D3DXVECTOR3 vtxMin)
{
	m_vtxMin = vtxMin;
}

//=========================================================================================
//�o�[�e�b�N�X�ŏ��l�̎擾����
//=========================================================================================
D3DXVECTOR3 CObjectX::GetVtxMin(void)
{
	return m_vtxMin;
}

