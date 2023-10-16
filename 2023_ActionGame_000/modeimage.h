//=========================================================================================
//
//[modeimage.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _MODEIMAGE_H_			//���̃}�N����`������Ȃ�������
#define _MODEIMAGE_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************************************************
//���[�h�C���[�W�N���X
//*****************************************************************************************
class CModeImage : public CObject2D
{
public:
	CModeImage();
	~CModeImage();

	static HRESULT Load(int nType);
	static void Unload(void);
	HRESULT Init(int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModeImage *Create(int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`�����
	CObject2D *m_pModeImage;
};

#endif