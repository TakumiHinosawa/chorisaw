//=========================================================================================
//
// �I�u�W�F�N�g�r���{�[�h [objectbillboard.cpp]
// Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "objectbillboard.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define SIZE	(50.0f)	//�T�C�Y

//=========================================================================================
//3D�I�u�W�F�N�g�̃R���X�g���N�^
//=========================================================================================
CObjectBillboard::CObjectBillboard()
{
	//�e��ϐ�������
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fHeight = SIZE;
	m_fWidth = SIZE;
}

//=========================================================================================
//3D�I�u�W�F�N�g�̃f�X�g���N�^
//=========================================================================================
CObjectBillboard::~CObjectBillboard()
{

}

//=========================================================================================
//3D�I�u�W�F�N�g�̏���������
//=========================================================================================
HRESULT CObjectBillboard::Init(void)
{
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

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (- m_fWidth);
	pVtx[1].pos.x = (+ m_fWidth);
	pVtx[2].pos.x = (- m_fWidth);
	pVtx[3].pos.x = (+ m_fWidth);
					   
	pVtx[0].pos.y = (+ m_fHeight);
	pVtx[1].pos.y = (+ m_fHeight);
	pVtx[2].pos.y = (- m_fHeight);
	pVtx[3].pos.y = (- m_fHeight);

	pVtx[0].pos.z = (0.0f);
	pVtx[1].pos.z = (0.0f);
	pVtx[2].pos.z = (0.0f);
	pVtx[3].pos.z = (0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
void CObjectBillboard::Uninit(void)
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
void CObjectBillboard::Update(void)
{

}

//=========================================================================================
//3D�I�u�W�F�N�g�̕`�揈��
//=========================================================================================
void CObjectBillboard::Draw(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;	

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//=========================================================================================
//3D�I�u�W�F�N�g�̐ݒ�
//=========================================================================================
void CObjectBillboard::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pos = pos;
	m_rot = rot;
}

//=========================================================================================
//3D�I�u�W�F�N�g�̐���
//=========================================================================================
CObjectBillboard *CObjectBillboard::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CObjectBillboard *pObectBillboard;

	//�I�u�W�F�N�g3D�̐���
	pObectBillboard = new CObjectBillboard;

	if (pObectBillboard != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pObectBillboard->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pObectBillboard;
}

//=========================================================================================
//�o�C���h�e�N�X�`��
//=========================================================================================
void CObjectBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=========================================================================================
//�ʒu���̎擾
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//�ʒu���̎擾
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetRot(void)
{
	return m_rot;
}

//=========================================================================================
//�ʒu���̎擾
//=========================================================================================
D3DXVECTOR3 CObjectBillboard::GetMove(void)
{
	return m_move;
}

//=========================================================================================
//�ʒu���̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//�ʒu���̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=========================================================================================
//�ʒu���̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=========================================================================================
//�e�̔��˂̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=========================================================================================
//�����̑傫���擾����
//=========================================================================================
float CObjectBillboard::GetHeight(void)
{
	return m_fHeight;
}

//=========================================================================================
//���̑傫���擾����
//=========================================================================================
float CObjectBillboard::GetWidth(void)
{
	return m_fWidth;
}

//=========================================================================================
//�T�C�Y�̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	//�o�[�e�b�N�X�ݒ菈��
	SetVtx();
}

//=========================================================================================
//�o�[�e�b�N�X�̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetVtx(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (-m_fWidth);
	pVtx[1].pos.x = (+m_fWidth);
	pVtx[2].pos.x = (-m_fWidth);
	pVtx[3].pos.x = (+m_fWidth);

	pVtx[0].pos.y = (+m_fHeight);
	pVtx[1].pos.y = (+m_fHeight);
	pVtx[2].pos.y = (-m_fHeight);
	pVtx[3].pos.y = (-m_fHeight);

	pVtx[0].pos.z = (0.0f);
	pVtx[1].pos.z = (0.0f);
	pVtx[2].pos.z = (0.0f);
	pVtx[3].pos.z = (0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//�A�j���[�V�����̐ݒ菈��
//=========================================================================================
void CObjectBillboard::SetAnim(int nCntAnim)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + nCntAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f + nCntAnim * 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nCntAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f + nCntAnim * 0.125f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}