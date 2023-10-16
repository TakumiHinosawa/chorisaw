//=========================================================================================
//
// �I�u�W�F�N�g�r���{�[�h[objectbillboard.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _OBJECTBILLBOARD_H_			//���̃}�N����`������Ȃ�������
#define _OBJECTBILLBOARD_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************************
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	static CObjectBillboard *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetMove(void);
	void SetMove(D3DXVECTOR3 move);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

	float GetHeight(void);
	float GetWidth(void);
	void SetSize(float fHeight,float hWidth);

	void SetVtx(void);

	void SetAnim(int nCntAnim);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`�����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@���
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����

	float m_fHeight;		//����
	float m_fWidth;			//��
};

#endif


