#include "DxLib.h"
#include "TitleScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../Library/Loading/Loading.h"
#include "../../Game/Draw/DrawManager.h"

constexpr int INTERVAL = 100;		//�摜�؂�ւ��̃C���^�[�o��

eStageID StageID;					//�X�e�[�WID

// �R���X�g���N�^
CTitleScene::CTitleScene(){
	_GraphID = PATH_TYPE::BG_TITLE;
	_Interval = 0;
	_SceneID = eKind::SCENE_INIT;
}

//�f�X�g���N�^
CTitleScene::~CTitleScene()
{
	
}

//�J��Ԃ��s������
int CTitleScene::Loop()
{
	int iRet = 0;

	//�V�[���؂�ւ��֐��|�C���^���s
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	if (_IsEnd == true)
		iRet = (int)CSceneManager::eScene::PLAY;

	return iRet;
}

//���[�h����
void CTitleScene::Load()
{
	//���[�h���̓��[�h��ʂɂ���
	if (CLoading::GetLoading() == true && CLoading::GetLoad() == false) {
		CHndlManager::GetInstance()->Load();
		CLoading::SetLoad(true);
	}
	//���[�h�I������玟��
	if (CLoading::IsLoadEnd() == true) {
		CDrawManager::GetInstance()->SetHndl();
		CLoading::LoadEnd();
		CSoundManager::Play(CSoundManager::eSoundID::BGM, DX_PLAYTYPE_LOOP, true);
		CSoundManager::SetVolume(CSoundManager::eSoundID::BGM, BGM_VOLUME);

		_SceneID = eKind::SCENE_LOOP;
	}
}

//�`�揈��
void CTitleScene::Draw()
{
	CDrawManager::GetInstance()->Draw(_GraphID, 0, 0);
}

//������
void CTitleScene::Init()
{
	_Interval = 0;
	_GraphID = PATH_TYPE::BG_TITLE;
	_IsEnd = false;
	CLoading::Init();
	CLoading::Load();
	CLoading::LoadStart();
	CHndlManager::GetInstance()->Init();
	CDrawManager::GetInstance()->Init();
	CSoundManager::Init();
	CSoundManager::LoadAllData();

	_SceneID = eKind::SCENE_LOAD;
}

//���C������
void CTitleScene::Step()
{
	//�L�[�{�[�h�ŉ����ꂽ���p�b�h�ŉ����ꂽ���ŉ摜��ς���
	if (CInput::IsXPadPush(XINPUT_BUTTON_START) == true)
		_GraphID = PATH_TYPE::DESCRIPTION1;
	else if (CInput::IsKeyPush(KEY_INPUT_RETURN) != 0)
		_GraphID = PATH_TYPE::DESCRIPTION2;

	if ((CInput::IsKeyPush(KEY_INPUT_RETURN) != 0 || CInput::IsXPadPush(XINPUT_BUTTON_START) == true)
		&& _GraphID != PATH_TYPE::BG_TITLE && _Interval >= INTERVAL)
		_SceneID = eKind::SCENE_EXIT;

	if (_GraphID != PATH_TYPE::BG_TITLE)
		_Interval++;
}

//�㏈��
void CTitleScene::Fin() {
	_IsEnd = true;
	StageID = eStageID::STAGE_0;

	CSoundManager::Stop(CSoundManager::eSoundID::BGM);

	_SceneID = eKind::SCENE_INIT;
}
