//=========================================================================================
//
// �r���f�B���O [billding.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _BILLDING_H_			//���̃}�N����`������Ȃ�������
#define _BILLDING_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "objectX.h"

//*****************************************************************************************
//�I�u�W�F�N�gX�N���X
//*****************************************************************************************
class CBuilding : public CObjectX
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//���ʂ̑���
		TYPE_THIN,			//�ׂ�����
		TYPE_WALL,			//��
		TYPE_WALLPAPER,		//�ǎ�
		TYPE_MAX
	}TYPE;

	CBuilding();
	~CBuilding();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBuilding *Create(void);
	TYPE GetType(void);
	void SetType(TYPE type);

private:
	TYPE m_Type;
};

#endif


