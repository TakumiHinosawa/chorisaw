//=========================================================================================
//
// �I�u�W�F�N�g3D [object3D.cpp]
// Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "object3D.h"
#include "renderer.h"
#include "manager.h"

//=========================================================================================
//3D�I�u�W�F�N�g�̃R���X�g���N�^
//=========================================================================================
CObject3D::CObject3D()
{
	//�e��ϐ�������
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}

//=========================================================================================
//3D�I�u�W�F�N�g�̃f�X�g���N�^
//=========================================================================================
CObject3D::~CObject3D()
{

}

//=========================================================================================
//3D�I�u�W�F�N�g�̏���������
//=========================================================================================
HRESULT CObject3D::Init(void)
{
	VERTEX_3D *pVtx;

	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (- 300.0f);
	pVtx[1].pos.x = (+ 300.0f);
	pVtx[2].pos.x = (- 300.0f);
	pVtx[3].pos.x = (+ 300.0f);

	pVtx[0].pos.y = (+ 0.0f);
	pVtx[1].pos.y = (+ 0.0f);
	pVtx[2].pos.y = (+ 0.0f);
	pVtx[3].pos.y = (+ 0.0f);

	pVtx[0].pos.z = (+ 300.0f);
	pVtx[1].pos.z = (+ 300.0f);
	pVtx[2].pos.z = (- 300.0f);
	pVtx[3].pos.z = (- 300.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================================================
//3D�I�u�W�F�N�g�̏I������
//=========================================================================================
void CObject3D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{//��񂪓����Ă�����

		//�����������
		m_pVtxBuff->Release();

		//������
		m_pVtxBuff = NULL;
	}

	//�J��
	Release();
}

//=========================================================================================
//3D�I�u�W�F�N�g�̍X�V����
//=========================================================================================
void CObject3D::Update(void)
{

}

//=========================================================================================
//3D�I�u�W�F�N�g�̕`�揈��
//=========================================================================================
void CObject3D::Draw(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`�揈��
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//�v���~�e�B�u�̎��
}

//=========================================================================================
//3D�I�u�W�F�N�g�̐ݒ�
//=========================================================================================
void CObject3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (- fWidth);
	pVtx[1].pos.x = (+ fWidth);
	pVtx[2].pos.x = (- fWidth);
	pVtx[3].pos.x = (+ fWidth);

	pVtx[0].pos.y = (+ 0.0f);
	pVtx[1].pos.y = (+ 0.0f);
	pVtx[2].pos.y = (+ 0.0f);
	pVtx[3].pos.y = (+ 0.0f);

	pVtx[0].pos.z = (+ fHeight);
	pVtx[1].pos.z = (+ fHeight);
	pVtx[2].pos.z = (- fHeight);
	pVtx[3].pos.z = (- fHeight);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//3D�I�u�W�F�N�g�E�H�[���̐ݒ�
//=========================================================================================
void CObject3D::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth, int nType)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (nType)
	{
	case WALL_FRONT:	//�O��

		//���_���W�̐ݒ�
		pVtx[0].pos.x = (- fWidth);
		pVtx[1].pos.x = (+ fWidth);
		pVtx[2].pos.x = (- fWidth);
		pVtx[3].pos.x = (+ fWidth);

		pVtx[0].pos.y = (+ fHeight * 0.25f);
		pVtx[1].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ 0.0f);

		pVtx[0].pos.z = (+0.0f);
		pVtx[1].pos.z = (+0.0f);
		pVtx[2].pos.z = (+0.0f);
		pVtx[3].pos.z = (+0.0f);
		break;

	case WALL_BACK:		//��둤

		//���_���W�̐ݒ�
		pVtx[0].pos.x = (- fWidth);
		pVtx[1].pos.x = (+ fWidth);
		pVtx[2].pos.x = (- fWidth);
		pVtx[3].pos.x = (+ fWidth);

		pVtx[0].pos.y = (+ 0.0f);
		pVtx[1].pos.y = (+ 0.0f);
		pVtx[2].pos.y = (+ fHeight * 0.25f);
		pVtx[3].pos.y = (+ fHeight * 0.25f);
						   
		pVtx[0].pos.z = (+ 0.0f);
		pVtx[1].pos.z = (+ 0.0f);
		pVtx[2].pos.z = (+ 0.0f);
		pVtx[3].pos.z = (+ 0.0f);
		break;

	case WALL_LEFT:		//����

		//���_���W�̐ݒ�
		pVtx[0].pos.x = (- 0.0f);
		pVtx[1].pos.x = (+ 0.0f);
		pVtx[2].pos.x = (- 0.0f);
		pVtx[3].pos.x = (+ 0.0f);
						   
		pVtx[0].pos.y = (+ fHeight * 0.25f);
		pVtx[1].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ 0.0f);
						   
		pVtx[0].pos.z = (- fWidth);
		pVtx[1].pos.z = (+ fWidth);
		pVtx[2].pos.z = (- fWidth);
		pVtx[3].pos.z = (+ fWidth);
		break;

	case WALL_RIGHT:		//�E��

		//���_���W�̐ݒ�
		pVtx[0].pos.x = (- 0.0f);
		pVtx[1].pos.x = (+ 0.0f);
		pVtx[2].pos.x = (- 0.0f);
		pVtx[3].pos.x = (+ 0.0f);
						   
		pVtx[0].pos.y = (+ 0.0f);
		pVtx[1].pos.y = (+ 0.0f);
		pVtx[3].pos.y = (+ fHeight * 0.25f);
		pVtx[2].pos.y = (+ fHeight * 0.25f);
						   
		pVtx[0].pos.z = (- fWidth);
		pVtx[1].pos.z = (+ fWidth);
		pVtx[2].pos.z = (- fWidth);
		pVtx[3].pos.z = (+ fWidth);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_pos = pos;
	m_rot = rot;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
}

//=========================================================================================
//3D�I�u�W�F�N�g�̐���
//=========================================================================================
CObject3D *CObject3D::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CObject3D *pObect3D;

	//�I�u�W�F�N�g3D�̐���
	pObect3D = new CObject3D;

	if (pObect3D != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pObect3D->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pObect3D;
}

//=========================================================================================
//3D�I�u�W�F�N�g�e�N�X�`���̊��蓖��
//=========================================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
