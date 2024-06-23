#include "DxLib.h"
#include "TitleScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../Library/Loading/Loading.h"
#include "../../Game/Draw/DrawManager.h"

constexpr int INTERVAL = 100;		//画像切り替えのインターバル

eStageID StageID;					//ステージID

// コンストラクタ
CTitleScene::CTitleScene(){
	_GraphID = PATH_TYPE::BG_TITLE;
	_Interval = 0;
	_SceneID = eKind::SCENE_INIT;
}

//デストラクタ
CTitleScene::~CTitleScene()
{
	
}

//繰り返し行う処理
int CTitleScene::Loop()
{
	int iRet = 0;

	//シーン切り替え関数ポインタ実行
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	if (_IsEnd == true)
		iRet = (int)CSceneManager::eScene::PLAY;

	return iRet;
}

//ロード処理
void CTitleScene::Load()
{
	//ロード中はロード画面にする
	if (CLoading::GetLoading() == true && CLoading::GetLoad() == false) {
		CHndlManager::GetInstance()->Load();
		CLoading::SetLoad(true);
	}
	//ロード終わったら次へ
	if (CLoading::IsLoadEnd() == true) {
		CDrawManager::GetInstance()->SetHndl();
		CLoading::LoadEnd();
		CSoundManager::Play(CSoundManager::eSoundID::BGM, DX_PLAYTYPE_LOOP, true);
		CSoundManager::SetVolume(CSoundManager::eSoundID::BGM, BGM_VOLUME);

		_SceneID = eKind::SCENE_LOOP;
	}
}

//描画処理
void CTitleScene::Draw()
{
	CDrawManager::GetInstance()->Draw(_GraphID, 0, 0);
}

//初期化
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

//メイン処理
void CTitleScene::Step()
{
	//キーボードで押されたかパッドで押されたかで画像を変える
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

//後処理
void CTitleScene::Fin() {
	_IsEnd = true;
	StageID = eStageID::STAGE_0;

	CSoundManager::Stop(CSoundManager::eSoundID::BGM);

	_SceneID = eKind::SCENE_INIT;
}
