//=========================================================================================
//
//���C�� [main.cpp]
//Author:�����V����
//
//=========================================================================================
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "manager.h"
#include <time.h>

//*****************************************************************************************
//�}�N����`
//*****************************************************************************************
#define CLASS_NAME		"WindowClass"		//�E�C���h�N���X�̖��O
#define WINDOW_NAME		"�`������ �`�`�����\�[���ɑS�c�b�p�̊��`"	//�E�C���h�̖��O

//*****************************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************************
//����[�΂�錾
//*****************************************************************************************
int g_nCountFPS = 0;							//FPS�J�E���^�[

//=========================================================================================
//���C���֐�
//=========================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������
	DWORD dwFrameCount;			//�t���[���J�E���^�[
	DWORD dwFPSLastTime;		//�Ō��FPS���v����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASS�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���
		0,									//0�ɂ���
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�n���h��(���ʎq)
		LoadIcon(NULL,IDI_APPLICATION)		//���b�Z�[�W���i�[����ϐ�
	};

	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	HWND hWnd;			//�E�C���h�E�n���h��
	MSG msg;			//���b�Z�[�W���i�[����ϐ�

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�C���h�X�^�C��
		CLASS_NAME,					//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�C���h�E����X���W
		CW_USEDEFAULT,				//�E�C���h�E����Y���W
		SCREEN_WIDTH,				//�E�C���h�E��
		SCREEN_HEIGHT,				//�E�C���h�E����
		NULL,						//�e�E�C���h�E�̃n���h��
		NULL,						//���j���[�܂��͎q�E�C���h�E��ID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�C���h�E�쐬�f�[�^

	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾

	dwFrameCount = 0;					//����������
	dwFPSLastTime = timeGetTime();		//���ݎ������擾
	srand((unsigned int)time(NULL));

	//�}�l�[�W���[�̃|�C���^
	CManager *pManager = NULL;

	if (pManager == NULL)
	{//��񂪖����Ƃ�

		//�}�l�[�W���[�̐���
		pManager = new CManager;
	}

	if (pManager != NULL)
	{//���������m�ۂ���Ă�Ƃ�

		//�}�l�[�W���[�̏���������
		pManager->Init(hInstance,hWnd,TRUE);
	}

	//�E�C���h�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

										//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  //�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}

		}

		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5�b�o��
			//FPS���v��
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			dwFPSLastTime = dwCurrentTime;		//FPS���v������������ۑ�
			dwFrameCount = 0;					//�t���[���J�E���g���N���A

		}

		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;

				dwFrameCount++;		//�t���[���J�E���g�����Z

				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();
			}
		}
	}

	if (pManager != NULL)
	{//�����_���[��񂪂�������

		//�I������
		pManager->Uninit();

		//�������J��
		delete pManager;

		//�}�l�[�W���[������
		pManager = NULL;
	}

	//�S�ẴI�u�W�F�N�g��j��
	CObject::ReleaseAll();

	//�E�C���h�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================================================================
//�E�C���h�E�v���V�[�W��
//=========================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;													//�Ԃ�l���i�[
	char aString[256] = "test";									//�`�悷��e�L�X�g���i�[
	static POINT pos = { 100,100 };								//�����̎n�_(X���W�EY���W)
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//�E�C���h�E�̗̈�
	static POINT move = { 2,3 };								//�����̎��_�ړ���(X�����EY����)

	switch (uMsg)
	{
	case WM_DESTROY:		//�E�C���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_CLOSE:			//����{�^���̉����̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{//�I���{�^���������ꂽ

			//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_KEYDOWN:		//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//ESC�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

