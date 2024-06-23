#include <crtdbg.h>
#include <math.h>
#include "GameSystem.h"
#include "../Library/Common.h"
#include "../Library/FrameRate/FrameRate.h"
#include "../Library/Input/InputManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../Game/Scene/SceneManager.h"
#include "../../Library/Effect/effekseer.h"

//�ÓI�ϐ��̎��Ԑ錾
bool CGameSystem::_IsGemeEnd = false;
//�V�[��
CSceneManager cSceneManager;

void CGameSystem::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// ���������[�N�`�F�b�N�p
	//�E�B���h�E�̐ݒ�
	ChangeWindowMode(true);
}

void CGameSystem::Start()
{
	//DxLib���N������O�ɍs������
	Init();

	//DX���C�u��������������
	if (DxLib_Init() == -1) {
		RequestGameEnd();
	}

	//�E�B���h�E�T�C�Y��ݒ�
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 0, 255);	// ���ߐF�w��

	//���͏�����
	CInputManager::Init();

}

void CGameSystem::MainLoop()
{
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		//ESC�L�[���Q�[���I���t���O�������Ă���ΏI��
		if (CheckHitKey(KEY_INPUT_ESCAPE) || IsGameEnd()) break;

		//�ʏ폈��
		Step();
	}
}

void CGameSystem::Step()
{
	//�V�X�e���ɏ�����Ԃ�
	Sleep(1);
	//=====================

	//�t���[�����[�g�ʏ폈��
	CFrameRate::Step();

	//���s�\�Ȃ烁�C���̏����ɒʂ�
	if (CFrameRate::IsExecutable())
	{
		//�t���[�����[�g�X�V����
		CFrameRate::Update();

		//��ʂɕ\�����ꂽ���̂�������(1���[�v��1�x�����s��)
		ClearDrawScreen();

		//���̓X�e�b�v
		CInputManager::Step();

		//�������ɃQ�[���̃��C�������Ƃ�����
		cSceneManager.Loop();

		cSceneManager.Draw();

		//�t���b�v�֐�(���[�v�̏I����1�x�����s��)
		ScreenFlip();
	}
}

void CGameSystem::Fin()
{
	//�`��}�l�[�W���[�j��
	CDrawManager::GetInstance()->DeleteInstance();
	//�G�t�F�N�g�j��
	CEffekseerCtrl::Fin();

	//�g�p�������ׂẲ摜��j��
	InitGraph();

	//DX���C�u�����̏I������
	DxLib_End();
}
