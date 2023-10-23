//=========================================================================================
//
// �J�����@[camera.cpp]
// Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "playerx.h"
#include "debugproc.h"
#include "game.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define MOVE	(1.0f)		//�ړ���
#define MOVES	(0.01f)		//�p�x�ړ���
#define DIS		(700.0f)	//����
#define WIDTH	(350.0f)	//�v���C���[�ƃJ�����̋����� [ X���W ]

//*****************************************************************************************
//�ÓI�����o�ϐ�������
//*****************************************************************************************
D3DXVECTOR3 CCamera::m_rot = {};

//=========================================================================================
//�J�����̃R���X�g���N�^
//=========================================================================================
CCamera::CCamera()
{
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=========================================================================================
//�J�����̃f�X�g���N�^
//=========================================================================================
CCamera::~CCamera()
{

}

//=========================================================================================
//�J�����̏���������
//=========================================================================================
HRESULT CCamera::Init(void)
{
	//��ʐݒ�
	m_viewport.X = 0;
	m_viewport.Y = 0;
	m_viewport.Width = SCREEN_WIDTH;
	m_viewport.Height = SCREEN_HEIGHT;
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;

	m_posV = D3DXVECTOR3(0.0f, 150.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=========================================================================================
//�J�����̏I������
//=========================================================================================
void CCamera::Uninit(void)
{
	
}

//=========================================================================================
//�J�����̍X�V����
//=========================================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�ւ̃|�C���^�擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//�R���g���[���[�ւ̃|�C���^���擾
	CInputController *pInputController = CManager::GetManager()->GetInputController();

	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	if (pInputKeyboard->GetPress(DIK_X) == true)
	{//Y���W��
		m_move.y += MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_Z) == true)
	{//Y���W��
		m_move.y -= MOVE;
	}

	//�ړ������̕␳
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//�J������]
	m_posR.x = m_posV.x + sinf(m_rot.y) * DIS;		//���_���猩��rot�̕����ɂǂꂾ������Ă��邩
	m_posR.z = m_posV.z + cosf(m_rot.y) * DIS;

	if (pInputKeyboard->GetPress(DIK_E) == true)
	{//���_��]
		m_rot.y += MOVES;
	}
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{//���_��]
		m_rot.y -= MOVES;
	}

	//�ړ������̕␳
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//�J������]
	m_posV.x = m_posR.x + sinf(m_rot.y) * -DIS;	//�����_���猩��rot�̕����ɂǂꂾ������Ă��邩
	m_posV.z = m_posR.z + cosf(m_rot.y) * -DIS;

	if (pInputKeyboard->GetPress(DIK_T) == true)
	{//�������
		m_posR.y += MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_G) == true)
	{//��������
		m_posR.y -= MOVE;
	}

	//�ړ��ʑ��
	m_posV += m_move;
	m_posR += m_move;

	//�v���C���[�̎擾����
	CPlayerX *pPlayer = CGame::GetPlayer();

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	//���f���̈ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.12f;
	m_move.y += (0.0f - m_move.y) * 0.12f;
	m_move.z += (0.0f - m_move.z) * 0.12f;

	//����
	m_posVDest.x = PlayerPos.x + WIDTH + sinf(m_rot.y) * -DIS;		//�ړI�̎��_�Ƀ��f���̈ʒu����(���΍��W)
	m_posVDest.z = PlayerPos.z + cosf(m_rot.y) * -DIS;				//�ړI�̎��_�Ƀ��f���̈ʒu����(���΍��W)
	(m_posVDest - m_posV) * 0.1f;

	float targetHeight = 0.0f; // �J��������������

	if (PlayerPos.y > targetHeight)
	{
		// �J�����ʒu�𒲐�
		m_posR.y = PlayerPos.y - 50.0f;
		m_posV.y = PlayerPos.y;
	}

	//�J�����Ǐ]����
	m_posV.x += (m_posVDest.x - m_posV.x) * 0.1f;	//���_�Ƀ��f���̈ʒu����(���΍��W)
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.1f;	//���_�Ƀ��f���̈ʒu����(���΍��W)

	//�f�o�b�O�\��
	pDebug->Print("�J�����@[�����_] ( X: %f Y: %f Z: %f )\n", m_posR.x, m_posR.y, m_posR.z);
	pDebug->Print("        �@[���_] ( X: %f Y: %f Z: %f )\n\n", m_posV.x, m_posV.y, m_posV.z);
}

//=========================================================================================
//�J�����̐ݒ菈��
//=========================================================================================
void CCamera::SetCamera(void)
{
	//�I�u�W�F�N�g�擾
	CRenderer *pRenderer = CManager::GetManager()->GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	pDevice->SetViewport(&m_viewport);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//����p
		(float)m_viewport.Width / (float)m_viewport.Height,	//�A�X�y�N�g��
		10.0f,		//Z�l�̍ŏ��l
		5000.0f);	//Z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	//���_
		&m_posR,	//�����_
		&m_vecR);	//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=========================================================================================
//�J�����̃��b�g���擾
//=========================================================================================
D3DXVECTOR3 CCamera::GetRotCamera(void)
{
	return m_rot;
}

//=========================================================================================
//�J�����̐ݒ菈��
//=========================================================================================
void CCamera::RotCamera(void)
{
	//�ڕW�̊p�x
	D3DXVECTOR3 RotDiff;

	//�v���C���[�̎擾����
	CPlayerX *pPlayer = CGame::GetPlayer();

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerRot = pPlayer->GetRot();

	//�v���C���[�̊p�x��ݒ�
	m_rotDest = PlayerRot;
	RotDiff = m_rotDest - m_rot;

	//�ړ������̕␳
	if (RotDiff.y > D3DX_PI || RotDiff.y < -D3DX_PI)
	{
		if (RotDiff.y > D3DX_PI)
		{
			RotDiff.y += -D3DX_PI * 2;
		}
		else if (RotDiff.y < -D3DX_PI)
		{
			RotDiff.y += D3DX_PI * 2;
		}
	}

	m_rot.y += RotDiff.y * 0.03f;

	//�ړ������̕␳
	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}
	m_posV.x = m_posR.x + sinf(m_rot.y) * -DIS;		//�����_���猩��rot�̕����ɂǂꂾ������Ă��邩
	m_posV.z = m_posR.z + cosf(m_rot.y) * -DIS;
}
