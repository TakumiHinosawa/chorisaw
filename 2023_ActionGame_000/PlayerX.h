//=========================================================================================
//
// �v���C���[X [playerX.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _PLAYERX_H_			//���̃}�N����`������Ȃ�������
#define _PLAYERX_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CPlayerX : public CObjectX
{
public:

	//�v���C���[�̏��
	typedef enum
	{
		PLAYERJUMP_NONE = 0,		// �W�����v���ĂȂ��Ƃ�
		PLAYERJUMP_UP,				// �W�����v���n�߂���
		PLAYERJUMP_TOP,				// �W�����v���_
		PLAYERJUMP_DOWN,			// �W�����v�����n��
		PLAYERJUMP_MAX
	}PLAYERJUMP;

	CPlayerX();
	~CPlayerX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Controller(void);
	static CPlayerX *Create(void);
	void CollisionBuilding(void);

private:

	// --- �f�o�b�O�p --- //
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_VtxMax;
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_BuildingPos;
	// ----------------- //

	PLAYERJUMP m_JumpState;		// �W�����v�̏��

	int m_nJumpCtr;			// �W�����v�J�E���^�[
	int m_nTime;			// ����
	int m_nAirborne;		// �؋󎞊Ԃ̃J�E���g
};

#endif


