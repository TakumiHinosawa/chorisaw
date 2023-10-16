//=========================================================================================
//
//[object2D.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define MAX_IMAGE	(2)
#define IMAGE_SAIZE	(50.0f)

//=========================================================================================
//2D�I�u�W�F�N�g�̃R���X�g���N�^
//=========================================================================================
CObject2D::CObject2D()
{
	//�e��ϐ�������
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//2D�I�u�W�F�N�g�̃f�X�g���N�^
//=========================================================================================
CObject2D::~CObject2D()
{

}

//=========================================================================================
//2D�I�u�W�F�N�g�̏���������
//=========================================================================================
HRESULT CObject2D::Init(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
//2D�I�u�W�F�N�g�̏I������
//=========================================================================================
void CObject2D::Uninit(void)
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
//2D�I�u�W�F�N�g�̍X�V����
//=========================================================================================
void CObject2D::Update(void)
{

}

//=========================================================================================
//2D�I�u�W�F�N�g�̕`�揈��
//=========================================================================================
void CObject2D::Draw(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�v���C���[�̕`�揈��
	pDevice->SetTexture(0, m_pTexture);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u�̎��
}

//=========================================================================================
//2D�I�u�W�F�N�g�̐ݒ菈��
//=========================================================================================
void CObject2D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fHeight,float fWidth)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	float nfLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 1.0f;

	//�Ίp���̊p�x���Z�o����
	float nfAngle = atan2f(fWidth, fHeight);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = pos.x + sinf(rot.z + (-D3DX_PI + nfAngle)) * nfLength;
	pVtx[0].pos.y = pos.y + cosf(rot.z + (-D3DX_PI + nfAngle)) * nfLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - nfAngle)) * nfLength;
	pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - nfAngle)) * nfLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(rot.z - nfAngle) * nfLength;
	pVtx[2].pos.y = pos.y + cosf(rot.z - nfAngle) * nfLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(rot.z + nfAngle) * nfLength;
	pVtx[3].pos.y = pos.y + cosf(rot.z + nfAngle) * nfLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�ړ��ʍX�V
	m_pos = pos;
	m_rot = rot;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//2D�I�u�W�F�N�g(�A�j���[�V�����p)�̐ݒ菈��
//=========================================================================================
void CObject2D::SetAnim(int nCntAnim)
{
	VERTEX_2D *pVtx;

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

//=========================================================================================
//2D�I�u�W�F�N�g(�G�t�F�N�g�p)�̐ݒ菈��
//=========================================================================================
void CObject2D::SetEffect(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	D3DXVECTOR3 rot;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//2D�I�u�W�F�N�g(���d�X�N���[��)�̐ݒ菈��
//=========================================================================================
void CObject2D::SetBg(float fTexV)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexV + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexV + 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//�I�u�W�F�N�g�e�N�X�`���̊��蓖��
//=========================================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=========================================================================================
//�I�u�W�F�N�g�̐ݒ菈��
//=========================================================================================
CObject2D *CObject2D::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CObject2D *pObect2D;

	//�I�u�W�F�N�g2D�̐���
	pObect2D = new CObject2D;

	if (pObect2D != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pObect2D->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pObect2D;
}

//=========================================================================================
//�I�u�W�F�N�g�̈ʒu�擾
//=========================================================================================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//=========================================================================================
//�o�b�t�@�̎擾
//=========================================================================================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtx(void)
{
	return m_pVtxBuff;
}

//=========================================================================================
//���݂̈ʒu�̎擾
//=========================================================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=========================================================================================
//�ߋ��̈ʒu�̐ݒ�
//=========================================================================================
D3DXVECTOR3 CObject2D::GetOldPosition(void)
{
	return m_Oldpos;
}

//=========================================================================================
//�ߋ��̈ʒu�̎擾
//=========================================================================================
void CObject2D::SetOldPosition(D3DXVECTOR3 pos)
{
	m_Oldpos = pos;
}

//=========================================================================================
//�J���[�̐ݒ菈��
//=========================================================================================
void CObject2D::SetColor(int nType)
{
	VERTEX_2D *pVtx;
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (nType)
	{
	case 0:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case 1:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================================================
//�J���[�̐ݒ菈��
//=========================================================================================
void CObject2D::Sort(int aData[4], int nScore, int aTexU[8])
{
	////�~������(�\�[�g)
	//for (int nCnt1 = 0; nCnt1 < 4 - 1; nCnt1++)
	//{
	//	for (int nCnt2 = nCnt1 + 1; nCnt2 < 4; nCnt2++)
	//	{
	//		if (aData[nCnt1] < aData[nCnt2])
	//		{
	//			//��x�ʂ̕ϐ��Ƀf�[�^���m�ۂ��Ă���㏑������
	//			int nTemp = aData[nCnt1];
	//			aData[nCnt1] = aData[nCnt2];
	//			aData[nCnt2] = nTemp;
	//		}
	//	}
	//}

	//int aTexU[8];		//�e���̐��l���i�[
	//int nCntScore;

	//VERTEX_2D *pVtx;

	////���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nCntLine = 0; nCntLine < 8; nCntLine++)
	//{
	//	aTexU[0] = aData[nCntLine] % 100000000 / 10000000;
	//	aTexU[1] = aData[nCntLine] % 10000000 / 1000000;
	//	aTexU[2] = aData[nCntLine] % 1000000 / 100000;
	//	aTexU[3] = aData[nCntLine] % 100000 / 10000;
	//	aTexU[4] = aData[nCntLine] % 10000 / 1000;
	//	aTexU[5] = aData[nCntLine] % 1000 / 100;
	//	aTexU[6] = aData[nCntLine] % 100 / 10;
	//	aTexU[7] = aData[nCntLine] % 10;

	//	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	//	{
	//		//�ʒu���X�V
	//		pVtx[0].pos = D3DXVECTOR3(400.0f + nCntScore * 60.0f, 160.0f + nCntLine *  105, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(450.0f + nCntScore * 60.0f, 160.0f + nCntLine *  105, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(400.0f + nCntScore * 60.0f, 210.0f + nCntLine * 105, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(450.0f + nCntScore * 60.0f, 210.0f + nCntLine * 105, 0.0f);

	//		//�e�N�X�`�����W�̍X�V
	//		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

	//		pVtx += 4;
	//	}
	//}
	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();
}