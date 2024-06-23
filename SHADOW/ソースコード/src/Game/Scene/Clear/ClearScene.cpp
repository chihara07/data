#include "DxLib.h"
#include "ClearScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../Library/Loading/Loading.h"
#include "../../Game/Draw/DrawManager.h"

// コンストラクタ
CClearScene::CClearScene()
{
	_SceneID = eKind::SCENE_INIT;
}

//デストラクタ
CClearScene::~CClearScene()
{
	Fin();
}

//繰り返し行う処理
int CClearScene::Loop()
{
	int iRet = 0;

	//シーン切り替え関数ポインタ実行
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	if (_IsEnd == true)
		iRet = (int)CSceneManager::eScene::TITLE;

	return iRet;
}

//ロード処理
void CClearScene::Load()
{
	CSoundManager::Play(CSoundManager::eSoundID::CLEAR_BGN, DX_PLAYTYPE_LOOP);
	CSoundManager::SetVolume(CSoundManager::eSoundID::CLEAR_BGN, BGM_VOLUME);

	_SceneID = eKind::SCENE_LOOP;
}

//描画処理
void CClearScene::Draw() {
	CDrawManager::GetInstance()->Draw(PATH_TYPE::BG_CLEAR, 0, 0);
}

//初期化
void CClearScene::Init() {
	_IsEnd = false;

	_SceneID = eKind::SCENE_LOAD;
}

//メイン処理
void CClearScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN) != 0 || CInput::IsXPadPush(XINPUT_BUTTON_START) == true)
		_SceneID = eKind::SCENE_EXIT;
}

//後処理
void CClearScene::Fin()
{
	_IsEnd = true;

	CSoundManager::StopAll();
	CLoading::Fin();

	_SceneID = eKind::SCENE_INIT;
}
