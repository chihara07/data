#include "DxLib.h"
#include "GameOverScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../Library/Loading/Loading.h"
#include "../../Game/Draw/DrawManager.h"

// �R���X�g���N�^
CGameOverScene::CGameOverScene()
{
	_SceneID = eKind::SCENE_INIT;
}

//�f�X�g���N�^
CGameOverScene::~CGameOverScene()
{
	Fin();
	//�e�}�l�[�W���[�폜
	CDrawManager::GetInstance()->DeleteInstance();
}

//�J��Ԃ��s������
int CGameOverScene::Loop()
{
	int iRet = 0;

	//�V�[���؂�ւ��֐��|�C���^���s
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	if (_IsEnd == true)
		iRet = (int)CSceneManager::eScene::TITLE;

	return iRet;
}

//���[�h����
void CGameOverScene::Load()
{
	CSoundManager::Play(CSoundManager::eSoundID::GAMEOVER_BGM, DX_PLAYTYPE_LOOP);
	CSoundManager::SetVolume(CSoundManager::eSoundID::GAMEOVER_BGM, BGM_VOLUME);

	_SceneID = eKind::SCENE_LOOP;
}

//�`�揈��
void CGameOverScene::Draw()
{
	CDrawManager::GetInstance()->Draw(PATH_TYPE::BG_GAMEOVER, 0, 0);
}

//������
void CGameOverScene::Init()
{
	_IsEnd = false;

	_SceneID = eKind::SCENE_LOAD;
}

//���C������
void CGameOverScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN) != 0 || CInput::IsXPadPush(XINPUT_BUTTON_START) == true)
		_SceneID = eKind::SCENE_EXIT;
}

//�㏈��
void CGameOverScene::Fin()
{
	_IsEnd = true;

	CSoundManager::StopAll();
	CLoading::Fin();

	_SceneID = eKind::SCENE_INIT;
}
