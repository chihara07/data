#include "Switch.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D SWITCH_SCALE(0.1f, 0.1f, 0.1f);		//スイッチ拡大率
constexpr Vector2D NEED_COIN_GRAPH_POS(0.5f, 0.5f);		//必要コイン数座標
constexpr float SWITCH_RAD = 10.0f;						//スイッチ半径
constexpr float NEED_COIN_GRAPH_HEIGHT = 20.f;			//必要コイン数の高さ
constexpr float NEED_COIN_GRAPH_SIZE = 15.f;			//必要コイン数のサイズ

//コンストラクタ・デストラクタ
CSwitch::CSwitch() {
	Init();
}
CSwitch::~CSwitch() {
	Fin();
}

//初期化
void CSwitch::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = SWITCH_SCALE;
	_Rad = SWITCH_RAD;
	_Hndl = -1;
	for(int need_coin_index = 0; need_coin_index < NEED_COIN_MAX_NUM; need_coin_index++)
		_CoinHndl[need_coin_index] = -1;
	_PressedHndl = -1;
	_IsPressed = false;
	_IsHit = false;
	_NeedCoinNum = 0;
}

//ロード
void CSwitch::Load() {
	//モデル読み込み
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SWITCH)); }
	if (_PressedHndl == -1){ _PressedHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SWITCH2)); }
	if (_CoinHndl[0] == -1) _CoinHndl[0] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN1);
	if (_CoinHndl[1] == -1) _CoinHndl[1] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN2);
	if (_CoinHndl[2] == -1) _CoinHndl[2] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN3);
}

//セット
void CSwitch::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_PressedHndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_PressedHndl, _Rot);
	MV1SetPosition(_PressedHndl, _Pos);
}

//メイン処理
void CSwitch::Step() {
	_IsHit = false;
}

//描画
void CSwitch::Draw() {
	//スイッチが押されていないなら
	if (_IsPressed == false){ MV1DrawModel(_Hndl); }
	//スイッチが押されているなら
	else { MV1DrawModel(_PressedHndl); }	

	//プレイヤー情報取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_IsPressed == false && _IsHit == true) {
		DrawBillboard3D(VGet(cPlayer->GetPos()._X, cPlayer->GetPos()._Y + NEED_COIN_GRAPH_HEIGHT, cPlayer->GetPos()._Z),
			NEED_COIN_GRAPH_POS._X, NEED_COIN_GRAPH_POS._Y, NEED_COIN_GRAPH_SIZE, 0.f, _CoinHndl[_NeedCoinNum - 1], true);
	}
}

//更新処理
void CSwitch::Update() {
	//回転角度、座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_PressedHndl, _Rot);
	MV1SetPosition(_PressedHndl, _Pos);
}

//終了
void CSwitch::Fin() {
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_PressedHndl != -1) { MV1DeleteModel(_PressedHndl); _PressedHndl = -1; }
}

//押された関数
void CSwitch::PressedCalc() {
	//押されたかフラグオン
	_IsPressed = true;
}

//必要コイン表示
void CSwitch::HitCalc() {
	_IsHit = true;
}
