#include "DxLib.h"
#include "ClearScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../Library/Loading/Loading.h"
#include "../../Game/Draw/DrawManager.h"

// �R���X�g���N�^
CClearScene::CClearScene()
{
	_SceneID = eKind::SCENE_INIT;
}

//�f�X�g���N�^
CClearScene::~CClearScene()
{
	Fin();
}

//�J��Ԃ��s������
int CClearScene::Loop()
{
	int iRet = 0;

	//�V�[���؂�ւ��֐��|�C���^���s
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	if (_IsEnd == true)
		iRet = (int)CSceneManager::eScene::TITLE;

	return iRet;
}

//���[�h����
void CClearScene::Load()
{
	CSoundManager::Play(CSoundManager::eSoundID::CLEAR_BGN, DX_PLAYTYPE_LOOP);
	CSoundManager::SetVolume(CSoundManager::eSoundID::CLEAR_BGN, BGM_VOLUME);

	_SceneID = eKind::SCENE_LOOP;
}

//�`�揈��
void CClearScene::Draw() {
	CDrawManager::GetInstance()->Draw(PATH_TYPE::BG_CLEAR, 0, 0);
}

//������
void CClearScene::Init() {
	_IsEnd = false;

	_SceneID = eKind::SCENE_LOAD;
}

//���C������
void CClearScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN) != 0 || CInput::IsXPadPush(XINPUT_BUTTON_START) == true)
		_SceneID = eKind::SCENE_EXIT;
}

//�㏈��
void CClearScene::Fin()
{
	_IsEnd = true;

	CSoundManager::StopAll();
	CLoading::Fin();

	_SceneID = eKind::SCENE_INIT;
}
