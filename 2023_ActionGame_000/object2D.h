//=========================================================================================
//
//[object2D.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _OBJECT2D_H_			//���̃}�N����`������Ȃ�������
#define _OBJECT2D_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************************
class CObject2D : public CObject
{
public:
	CObject2D();
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos , D3DXVECTOR3 rot,float fHeight,float fWidth);
	void SetAnim(int nCntAnim);
	void SetEffect(D3DXCOLOR col);
	void SetBg(float fTexV);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CObject2D *Create(void);	
	D3DXVECTOR3 GetPosition(void) override;
	void SetPosition(D3DXVECTOR3 pos);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	D3DXVECTOR3 GetOldPosition(void);
	void SetOldPosition(D3DXVECTOR3 pos);
	void SetColor(int nType);
	void Sort(int aData[4],int nScore, int aTexU[8]);

protected:
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_Oldpos;		//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR2 m_size;			//�c����

	LPDIRECT3DTEXTURE9	m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_���ւ̃|�C���^
};

#endif

