//=========================================================================================
//
//	[fade.h]
//	Author:�����V����
//
//=========================================================================================
#ifndef _FADE_H_	//���̒�`������Ă��Ȃ�������
#define _FADE_H_	//��d�C���N���[�h�h�~�̃}�N����`������

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "manager.h"
#include "object2D.h"

//*****************************************************************************************
//�t�F�[�h�N���X
//*****************************************************************************************
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̏�Ԃ̗񋓌^
	typedef enum
	{
		FADE_NONE = 0,		//�������Ă��Ȃ����
		FADE_IN,			//�t�F�[�h�C�����
		FADE_OUT,			//�t�F�[�h�A�E�g���
		FADE_MAX

	}FADE;

	CFade();
	~CFade();

	void Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(CScene::MODE modeNext);
	FADE Get(void);

private:
	FADE m_fade;				//�t�F�[�h�̏��
	CScene::MODE m_modeNext;	//���̉��(���[�h)
	D3DXCOLOR m_colorFade;		//�|���S��(�t�F�[�h)�̐F
};

#endif
