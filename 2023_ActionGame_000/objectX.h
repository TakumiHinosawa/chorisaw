//=========================================================================================
//
// �I�u�W�F�N�gX [objectX.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _OBJECTX_H_			//���̃}�N����`������Ȃ�������
#define _OBJECTX_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define NUM_OBJ	(256)	//�I�u�W�F�N�g�ő吔

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CObjectX : public CObject
{
public:
	CObjectX();
	~CObjectX();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	HRESULT Init(char *pFilename);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	static CObjectX *Create(char *pFilename);

	D3DXVECTOR3 GetPosition(void);
	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPositionOld(void);
	void SetPositionOld(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetMove(void);
	void SetMove(D3DXVECTOR3 move);

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);

	void SetVtxMax(D3DXVECTOR3 vtxMax);
	D3DXVECTOR3 GetVtxMax(void);

	void SetVtxMin(D3DXVECTOR3 vtxMin);
	D3DXVECTOR3 GetVtxMin(void);

	float GetHeight(void);
	float GetWidth(void);
	void SetSize(float fHeight, float fWidth);

	void ReloadObject(char *pFilename);

private:
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���̃|�C���^
	DWORD m_dwNumMat;			//�}�e���A���̐�
	LPDIRECT3DTEXTURE9* m_pTexture;		//�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posOld;//�ߋ��̈ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_rot;	//����
	float m_fHeight;	//����
	float m_fWidth;		//��

	D3DXVECTOR3 m_vtxMin;	//���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMax;	//���f���̍ő�l

	int m_nNumVtx;		//���_��
	DWORD m_dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *m_pVtxBuff;		//���_�o�b�t�@�̃|�C���^
};

#endif


