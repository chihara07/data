#include "SceneManager.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Loading/Loading.h"

//コンストラクタ
CSceneManager::CSceneManager()
{
	_SceneID = eScene::TITLE;
	_State = eManagerState::INIT;
	_Scene = nullptr;
	_PlayID = 0;
}

//デストラクタ
CSceneManager::~CSceneManager()
{
	CSoundManager::Fin();
	Fin();
}

//描画処理
void CSceneManager::Draw() {
	if (_SceneID == static_cast<eScene>(0)) {
		// シーン後処理
		_Scene->Draw();

		if (CLoading::GetLoading() == true) {
			CLoading::Step();
			CLoading::Draw();
		}
	}
}

void CSceneManager::Init() {
	//IDにあわせてシーン作成
	CreateScene(_SceneID);
	_State = eManagerState::MAIN;
}

void CSceneManager::Main() {
	// シーン後処理
	_SceneID = static_cast<eScene>(_Scene->Loop());

	if (_SceneID != static_cast<eScene>(0))
		_State = eManagerState::FIN;
}

void CSceneManager::Fin() {
	delete _Scene;
	_Scene = nullptr;

	_State = eManagerState::INIT;
}

void CSceneManager::CreateScene(eScene id)
{
	if (_Scene != nullptr) {
		delete _Scene;
		_Scene = nullptr;
	}

	switch (id) {
	case eScene::TITLE:			_Scene = New CTitleScene;	break;
	case eScene::PLAY:			_Scene = New CPlayScene;	break;
	case eScene::GAME_CLEAR:	_Scene = New CClearScene;	break;
	case eScene::GAME_OVER:		_Scene = New CGameOverScene;break;
	default:												break;
	}
}
