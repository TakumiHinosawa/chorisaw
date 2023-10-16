//=========================================================================================
//
// �v���C���[
// Author:�����V����	[playerX.cpp]
//
//=========================================================================================
#include "main.h"
#include "playerX.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "score.h"
#include "sound.h"
#include "game.h"

//=========================================================================================
//�}�N����`
//=========================================================================================
#define GRAVITY	(0.8f)			//�d��
#define MOVE_PLAYER	(0.80f)		//�ړ���
#define JUMPHEIGHT (16.0f)		//�W�����v��
#define AIRBORNE (20)			//���V����
#define ROTSPEED (0.7f)			//��]���x

//=========================================================================================
//�v���C���[�̃R���X�g���N�^	
//=========================================================================================
CPlayerX::CPlayerX()
{
	m_VtxMax = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BuildingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nJumpCtr = 0;
	m_nTime = 0;
	m_nAirborne = 0;
	m_JumpState = PLAYERJUMP_NONE;
}

//=========================================================================================
//�v���C���[�̃f�X�g���N�^
//=========================================================================================
CPlayerX::~CPlayerX()
{

}

//=========================================================================================
//�v���C���[�̏���������
//=========================================================================================
HRESULT CPlayerX::Init(void)
{
	//�I�u�W�F�N�g�̏���������
	CObjectX::Init("data\\MODEL\\chorizo.x");

	//��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	return S_OK;
}

//=========================================================================================
//�v���C���[�̏I������
//=========================================================================================
void CPlayerX::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//=========================================================================================
//�v���C���[�̍X�V����
//=========================================================================================
void CPlayerX::Update(void)
{
	//�v���C���[���쏈��
	Controller(); 
}

//=========================================================================================
//�v���C���[�̕`�揈��
//=========================================================================================
void CPlayerX::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//=========================================================================================
//�v���C���[�̃R���g���[���[
//=========================================================================================
void CPlayerX::Controller(void)
{
	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	//�J�������擾
	D3DXVECTOR3 RotCamera = CCamera::GetRotCamera();

	//�L�[�{�[�h�ւ̃|�C���^�擾
	CInputKeyboard *pInputKeyboard = CManager::GetManager()->GetInputKeyboard();

	//�R���g���[���[�ւ̃|�C���^�擾
	CInputController *pInputController = CManager::GetManager()->GetInputController();

	//�J�������擾
	D3DXVECTOR3 CameraRot = CCamera::GetRotCamera();

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//�����擾����
	D3DXVECTOR3 rot = CObjectX::GetRot();
	D3DXVECTOR3 move = CObjectX::GetMove();
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	//���݂̈ʒu��ۑ�
	m_OldPos = pos;

	//�J�������擾
	float fRotMove = rot.y;		//���݂̌���
	float fRotDest = rot.y;		//�s����������
	float fRotDiff = fRotDest - fRotMove;	//�ړI�̕���
	bool bUse = false;
	
	//*********************************************************************
	//�@����
	//*********************************************************************
	move.x += sinf(RotCamera.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;
	move.z += cosf(RotCamera.y - (-D3DX_PI * 0.5f)) * MOVE_PLAYER;

	// --- �W�����v --- //
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_nJumpCtr == 0)
	{// �C�ӂ̃L�[�������ꂽ�Ƃ�

		//�W�����v�͑��
		move.y = JUMPHEIGHT;

		//�W�����v�J�E���^�[���Z
		m_nJumpCtr += 1;

		//�W�����v�㏸��ԂɑJ��
		m_JumpState = PLAYERJUMP_UP;
	}
	else if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_nJumpCtr >= 1)
	{//�C�ӂ̃L�[�������ꂽ�Ƃ�

		//�W�����v�͑��
		move.y = JUMPHEIGHT;

		//�W�����v�J�E���^�[���Z
		m_nJumpCtr = -1;	

		//�W�����v�㏸��ԂɑJ��
		m_JumpState = PLAYERJUMP_UP;
	}
	if (m_JumpState == PLAYERJUMP_UP)
	{//�W�����v���̎�

		//��]
		rot.z -= ROTSPEED;
	}
	else
	{
		//���ɖ߂�
		rot.z = 0.0f;
	}

	//�ړ��ʂ��X�V(����������)
	move.x += (0.0f - move.x) * 0.12f;
	move.z += (0.0f - move.z) * 0.12f;

	//�p�x�Z�o
	fRotDiff = fRotDest - fRotMove;		//�ڕW�̈ړ������܂ł̍���

	//�ړ������̕␳
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += -D3DX_PI * 2;
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2;
		}
	}

	rot.y += fRotDiff * 0.1f;

	//�ړ������̕␳
	if (rot.y > D3DX_PI || rot.y < -D3DX_PI)
	{
		if (rot.y > D3DX_PI)
		{
			rot.y += -D3DX_PI * 2;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}
	}

	//�d��
	move.y -= GRAVITY;

	//�ړ��ʉ��Z
	pos += move;

	//�ʒu���X�V
	SetPosition(pos);

	//�ړ��ʍX�V
	SetMove(move);

	//�����Ƃ̓����蔻�菈��
	CollisionBuilding();

	//��]�X�V
	SetRot(rot);

	//�f�o�b�O�\��
	pDebug->Print("\n�d�� : %f\n",move.y);

	//�J�E���^�[���Z
	m_nTime++;
}

//=========================================================================================
//�v���C���[�̐�������
//=========================================================================================
CPlayerX *CPlayerX::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CPlayerX *pPlayerX;

	//�I�u�W�F�N�g3D�̐���
	pPlayerX = new CPlayerX;

	if (pPlayerX != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pPlayerX->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pPlayerX;
}

//=========================================================================================
//�v���C���[�ƌ����̓����蔻��
//=========================================================================================
void CPlayerX::CollisionBuilding(void)
{
	//�f�o�b�O���擾
	CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

	CObject *pObj;

	//�T�E���h���擾
	CSound *pSound = CManager::GetManager()->GetSound();

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = GetPosition();

	//�v���C���[�̈ړ����擾
	D3DXVECTOR3 PlayerMove = GetMove();

	//�v���C���[�̌��݂̈ʒu���擾
	D3DXVECTOR3 PlayerPosOld = GetPositionOld();

	//�v���C���[�̃T�C�Y�ۊǗp�ϐ�
	D3DXVECTOR3 vtxMin, vtxMax;

	//�v���C���[�̃T�C�Y�擾
	vtxMin = GetVtxMin();
	vtxMax = GetVtxMax();

	for (int nCnt = 0; nCnt < MAX_CHAR; nCnt++)
	{
		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCnt);

		if (pObj != NULL)
		{//�g�p����Ă���Ƃ�

			if (pObj->GetType() == TYPE_BUILDING)
			{//�����̎�

				//�G�̈ʒu�擾
				D3DXVECTOR3 BuildingPosition = pObj->GetPosition();

				//�����̃T�C�Y���擾
				D3DXVECTOR3 BuildingVtxMax = pObj->GetVtxMax();
				D3DXVECTOR3 BuildingVtxMin = pObj->GetVtxMin();

				// ******************************		�����蔻��		******************************* //

				//------------------------------------------------------------------------
				//	���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{//���̔���
					if (BuildingPosition.z + BuildingVtxMax.z <= m_OldPos.z + vtxMin.z
						&& BuildingPosition.z + BuildingVtxMax.z > PlayerPos.z + vtxMin.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMax.z - vtxMin.z;
					}
					if (BuildingPosition.z + BuildingVtxMin.z >= m_OldPos.z + vtxMax.z
						&& BuildingPosition.z + BuildingVtxMin.z < PlayerPos.z + vtxMax.z)
					{
						PlayerPos.z = BuildingPosition.z + BuildingVtxMin.z - vtxMax.z;
					}
				}

				//------------------------------------------------------------------------
				//���̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z
					&& BuildingPosition.y + BuildingVtxMin.y <= m_OldPos.y + vtxMax.y
					&& BuildingPosition.y + BuildingVtxMax.y >= m_OldPos.y + vtxMin.y)
				{
					if (BuildingPosition.x + BuildingVtxMin.x >= m_OldPos.x + vtxMax.x
						&& BuildingPosition.x + BuildingVtxMin.x < PlayerPos.x + vtxMax.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMin.x - vtxMax.x - 0.001f;
					}
					if (BuildingPosition.x + BuildingVtxMax.x <= m_OldPos.x + vtxMin.x
						&& BuildingPosition.x + BuildingVtxMax.x > PlayerPos.x + vtxMin.x)
					{
						PlayerPos.x = BuildingPosition.x + BuildingVtxMax.x - vtxMin.x;
					}
				}

				//------------------------------------------------------------------------
				//�c�̔���
				//------------------------------------------------------------------------
				if (BuildingPosition.x + BuildingVtxMin.x <= PlayerPos.x + vtxMax.x
					&& BuildingPosition.x + BuildingVtxMax.x >= PlayerPos.x + vtxMin.x
					&& BuildingPosition.z + BuildingVtxMin.z <= PlayerPos.z + vtxMax.z
					&& BuildingPosition.z + BuildingVtxMax.z >= PlayerPos.z + vtxMin.z)
				{
					if (BuildingPosition.y + BuildingVtxMin.y >= m_OldPos.y + vtxMax.y
						&& BuildingPosition.y + BuildingVtxMin.y < PlayerPos.y + vtxMax.y)
					{//�@���̔���

						//�ʒu�X�V
						PlayerPos.y = BuildingPosition.y + BuildingVtxMin.y - vtxMax.y;
					}
					if (BuildingPosition.y + BuildingVtxMax.y <= m_OldPos.y + vtxMin.y
						&& BuildingPosition.y + BuildingVtxMax.y > PlayerPos.y + vtxMin.y)
					{//�@��̔���
						
						//�ʒu�X�V
						PlayerPos.y = BuildingPosition.y + BuildingVtxMax.y - vtxMin.y;

						//�d�͏�����
						PlayerMove.y = 0.0f;

						//�J�E���^�[������
						m_nJumpCtr = 0;

						//�v���C���[�̃W�����v��Ԃ𖳌�������
						m_JumpState = PLAYERJUMP_NONE;

						pDebug->Print("\n����Ă��锻�� \n\n");
					}
				}
				//���݂̃T�C�Y�̍��W��ۑ�����
				m_VtxMax = BuildingVtxMax;
				m_VtxMin = BuildingVtxMin;

				//�ʒu����ۑ�
				m_BuildingPos = BuildingPosition;
			}
		}
	}

	//�ʒu���X�V
	SetPosition(PlayerPos);

	//�ړ����X�V
	SetMove(PlayerMove);

	//�f�o�b�O�\��
	pDebug->Print("[�����@���W] ( X:%f Y:%f Z:%f )\n", m_BuildingPos.x, m_BuildingPos.y, m_BuildingPos.z);
	pDebug->Print("[�����@�ő�T�C�Y] ( X:%f Y:%f Z:%f )\n", m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);
	pDebug->Print("[�����@�ŏ��T�C�Y] ( X:%f Y:%f Z:%f )\n\n", m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
	pDebug->Print("[�v���C���[�@���W] ( X:%f Y:%f Z:%f )\n", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	pDebug->Print("[�v���C���[ ���݂̍��W] ( X:%f Y:%f Z:%f )\n\n", m_OldPos.x, m_OldPos.y, m_OldPos.z);
}