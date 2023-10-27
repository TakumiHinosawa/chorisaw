//=========================================================================================
//
//�|�[�Y����
//Author:�����V����	[pause.cpp]
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "main.h"
#include "input.h"
#include "game.h"
#include "pause.h"
#include "sound.h"

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define NUM_PAUSE		(4)		//�e�N�X�`���̐�
#define SELECT_PAUSE	(3)		//�I���ł��鐔

//=========================================================================================
//�|�[�Y�̏���������
//=========================================================================================
CPause::CPause()
{
	m_nPauseMenu = 0;
	m_bPause = false;
}

//=========================================================================================
//�|�[�Y�̏���������
//=========================================================================================
CPause::~CPause()
{

}

//=========================================================================================
//�|�[�Y�̏���������
//=========================================================================================
HRESULT CPause::Init(void)
{
	//�|�[�Y���j���[
	m_nPauseMenu = PAUSE_MENU_CONTINUE;

	// 2d�ǂݍ��݁@4����


	return S_OK;
}

//=========================================================================================
//�|�[�Y�̏I������
//=========================================================================================
void CPause::Uninit(void)
{

}
//=========================================================================================
//�|�[�Y�̍X�V����
//=========================================================================================
void CPause::Update(void)
{
	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

					  //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W) == true || GetGamePadTrigger(BUTTON_0, 0))
	{
		g_PauseMenu = (g_PauseMenu + 2) % 3;

		//�T�E���h
		PlaySound(SOUND_LABEL_SE_CHOOSE);
	}

	if (GetKeyboardTrigger(DIK_S) == true || GetGamePadTrigger(BUTTON_1, 0))
	{
		g_PauseMenu = (g_PauseMenu + 1) % 3;

		//�T�E���h
		PlaySound(SOUND_LABEL_SE_CHOOSE);
	}

	if (g_PauseMenu == PAUSE_MENU_CONTINUE)
	{
		//���_�J���[�̐ݒ�
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (g_PauseMenu == PAUSE_MENU_RETRY)
	{
		//���_�J���[�̐ݒ�
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_CONTINUE * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (g_PauseMenu == PAUSE_MENU_QUIT)
	{
		//���_�J���[�̐ݒ�
		pVtx[g_PauseMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[g_PauseMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[PAUSE_MENU_CONTINUE * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_CONTINUE * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		pVtx[PAUSE_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[PAUSE_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && g_Pause == false || GetGamePadTrigger(BUTTON_A, 0) && g_Pause == false)
	{
		//�T�E���h
		PlaySound(SOUND_LABEL_SE_ENTER);

		//����L�[(ENTER�L�[)�������ꂽ
		switch (g_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:    //�Q�[���ɖ߂�
									 //���[�h�ݒ�(�Q�[����ʂɖ߂�)
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:       //�Q�[������蒼��
									 //���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_GAME);
			g_Pause = false;
			break;

		case PAUSE_MENU_QUIT:        //�^�C�g����ʂɖ߂�
									 //���[�h�ݒ�(�^�C�g����ʂɈڍs)
			SetFade(MODE_TITLE);
			g_Pause = true;
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}
//=========================================================================================
//�|�[�Y�̕`�揈��
//=========================================================================================
void CPause::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//�|���S���̕`��  �l�p�`
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPause, 2);
	}
}

//=========================================================================================
//�I�u�W�F�N�g�̐ݒ菈��
//=========================================================================================
CPause *CPause::Create(void)
{
	//�|�C���^�̕ϐ���錾
	CPause *pPause;

	//�I�u�W�F�N�g2D�̐���
	pPause = new CPause;

	if (pPause != NULL)
	{//�g�p����Ă���Ƃ�

		//����������
		pPause->Init();
	}

	//�I�u�W�F�N�g����Ԃ�
	return pPause;
}
