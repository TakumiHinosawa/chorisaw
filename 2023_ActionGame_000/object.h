//=========================================================================================
//
//[object.h]
//Author:�����V����
//
//=========================================================================================
#ifndef _OBJECT_H_			//���̃}�N����`������Ȃ�������
#define _OBJECT_H_			//2�d�C���N���[�h�h�~�̃}�N����`����

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************************
class CObject
{
public:

	//��ނ̗񋓌^��`
	typedef enum
	{
		TYPE_NONE = 0,		//���������Ƃ�
		TYPE_PLAYER,		//�v���C���[
		TYPE_BUILDING,		//����
		TYPE_TITLE,			//�^�C�g��
		TYPE_RESULT,		//���U���g
		TYPE_TUTORIAL,		//�`���[�g���A��
		TYPE_MAX
	}TYPE;

	CObject();
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,float fHeight,float fWidth) = 0;

	virtual D3DXVECTOR3 GetPosition(void);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetMove(void);
	virtual void SetMove(D3DXVECTOR3 move);
	virtual D3DXVECTOR3 GetRot(void);
	virtual void SetRot(D3DXVECTOR3 rot);

	virtual void SetVtxMax(D3DXVECTOR3 vtxMax);
	virtual D3DXVECTOR3 GetVtxMax(void);

	virtual void SetVtxMin(D3DXVECTOR3 vtxMin);
	virtual D3DXVECTOR3 GetVtxMin(void);

	//virtual void SetColor(void);

	virtual void Hit(void);

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetType(TYPE type);
	TYPE GetType(void);
	static CObject *GetObject(int nIdx);

protected:
	void Release(void);

private:
	static CObject *m_apObject[MAX_CHAR];	//�I�u�W�F�N�g���
	static int m_nNumAll;		//�I�u�W�F�N�g����
	int m_nID;					//�������g��ID
	TYPE m_type;				//�^�C�v
};

#endif
