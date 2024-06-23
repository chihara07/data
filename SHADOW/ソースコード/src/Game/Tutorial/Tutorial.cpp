#include "DxLib.h"
#include "Tutorial.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Input/InputManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Common.h"
#include "../Player/Player.h"

constexpr int GRAPH_POS_Y = 450;				//画像描画Y座標
constexpr int WAIT_COUNT = 5;					//待機時間
constexpr float TUTORIAL_START_POS_Z1 = 200.f;
constexpr float TUTORIAL_START_POS_Z2 = 0.f;
constexpr float TUTORIAL_START_POS_Z3 = -350.f;
constexpr float TUTORIAL_START_POS_Z4 = -750.f;
constexpr float TUTORIAL_START_POS_Z5 = 1200.f;
constexpr float TUTORIAL_START_POS_Z6 = -1600.f;
constexpr float TUTORIAL_START_POS_Z7 = -1300.f;
constexpr float TUTORIAL_START_POS_Z8 = 160.f;
constexpr float SWITCH_HIT_SIZE = 15.f;

CTutorial* CTutorial::_Instance = nullptr;

CTutorial* CTutorial::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CTutorial;
	}

	return _Instance;
}

void CTutorial::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

// コンストラクタ
CTutorial::CTutorial() : _TutorialEnd() {
	_IsTutorial = false;
	_IsPressed = false;
	_HndlID = PATH_TYPE::TEXT1;
}

//デストラクタ
CTutorial::~CTutorial()
{

}


//ロード処理
void CTutorial::Load() {

}

//描画処理
void CTutorial::Draw() {
	if(_IsTutorial == true)
		CDrawManager::GetInstance()->Draw(_HndlID, 0, GRAPH_POS_Y);
}

//初期化
void CTutorial::Init() {
	_IsPressed = false;
	//ステージIDごとにID代入
	if (StageID == eStageID::STAGE_0) {
		_HndlID = PATH_TYPE::TEXT1;
		_TutorialEnd = PATH_TYPE::TEXT2;
		_IsTutorial = true;
	}
	else if (StageID == eStageID::STAGE_1) {
		_IsTutorial = false;
		_TutorialEnd = PATH_TYPE::TUTORIAL22;
		_HndlID = PATH_TYPE::TUTORIAL20;
	}
	else if (StageID == eStageID::STAGE_2) {
		_IsTutorial = false;
		_TutorialEnd = PATH_TYPE::TUTORIAL23;
		_HndlID = PATH_TYPE::TUTORIAL23;
	}
}

//メイン処理
void CTutorial::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_IsTutorial == true) {
		AdvanceTutorial();
	}

	//ステージの決まった状況でチュートリアル開始
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z1 && _HndlID == PATH_TYPE::TUTORIAL1 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL4;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z2 && _HndlID == PATH_TYPE::TUTORIAL5 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL7;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z3 && _HndlID == PATH_TYPE::TUTORIAL8 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL8;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z4 && (int)_HndlID == (int)PATH_TYPE::TUTORIAL9 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL12;
	}
	if (MyLib::Abs(cPlayer->GetPos()._Z + TUTORIAL_START_POS_Z5) <= SWITCH_HIT_SIZE &&
		MyLib::Abs(cPlayer->GetPos()._X) <= SWITCH_HIT_SIZE && _HndlID == PATH_TYPE::TUTORIAL13 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL15;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z6 && _IsPressed  == true && _HndlID == PATH_TYPE::TUTORIAL16 && StageID == eStageID::STAGE_0) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL19;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z7 && _HndlID == PATH_TYPE::TUTORIAL20 && StageID == eStageID::STAGE_1) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL22;
	}
	if (cPlayer->GetPos()._Z <= TUTORIAL_START_POS_Z8 && _HndlID == PATH_TYPE::TUTORIAL23 && cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT
		&& StageID == eStageID::STAGE_2) {
		_IsTutorial = true;
		_TutorialEnd = PATH_TYPE::TUTORIAL23;
	}
}

//チュートリアルを進める
void CTutorial::AdvanceTutorial() {
	//IDごとに次に進むかプレイに戻るか
	if (CInput::IsKeyPush(KEY_INPUT_RETURN) != 0 || CInput::IsXPadPush(XINPUT_BUTTON_START) == true ||
		CInputManager::IsPush(CInputManager::eInputType::JUMP) == true || CInputManager::IsPush(CInputManager::eInputType::SELECT)) {
		if (_HndlID == _TutorialEnd) {
			_HndlID = static_cast<PATH_TYPE>(static_cast<int>(_HndlID) + 1);
			_IsTutorial = false;
		}
		else {
			_HndlID = static_cast<PATH_TYPE>(static_cast<int>(_HndlID) + 1);
		}
	}
}

//後処理
void CTutorial::Fin() {

}
