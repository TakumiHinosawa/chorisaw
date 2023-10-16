//=========================================================================================
//
//�J���� [camera.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//�N���X�錾
//*****************************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void RotCamera(void);
	static D3DXVECTOR3 GetRotCamera(void);

private:
	D3DXMATRIX m_mtxView;				//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;			//�v���W�F�N�V�����}�g���b�N�X
	D3DVIEWPORT9 m_viewport;				//�r���[�|�[�g
	D3DXVECTOR3 m_posV;					//���_
	D3DXVECTOR3 m_posR;					//�����_
	D3DXVECTOR3 m_posVDest;				//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;				//�ړI�̒����_
	D3DXVECTOR3 m_vecR;					//������x�N�g��
	static D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_rotDest;				//�ڕW�̊p�x
	int m_nType;						//�^�C�v
};

#endif
