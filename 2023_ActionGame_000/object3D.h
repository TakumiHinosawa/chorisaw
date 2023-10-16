//=========================================================================================
//
// �I�u�W�F�N�g3D[object3D.h]
// Author:�����V����
//
//=========================================================================================
#ifndef _OBJECT3D_H_			//���̃}�N����`������Ȃ�������
#define _OBJECT3D_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************************
class CObject3D : public CObject
{
public:

	//�E�H�[���^�C�v�̗񋓌^��`
	typedef enum
	{
		WALL_NONE = 0,		//���������Ƃ�
		WALL_FRONT,			//�O��
		WALL_BACK,			//��둤
		WALL_LEFT,			//����
		WALL_RIGHT,			//�E��
		WALL_MAX
	}WALL_TYPE;

	CObject3D();
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth,int nType);
	static CObject3D *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`�����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@���

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����

	float m_fHeight;			//����
	float m_fWidth;				//��
};

#endif


