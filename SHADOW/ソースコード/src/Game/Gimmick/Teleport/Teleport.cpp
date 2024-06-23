#include "Teleport.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/Tutorial/Tutorial.h"

constexpr float SHADOW_RAD = 15.0f;							//影の半径
constexpr float SHADOW_HEIGHT = 9.0f;						//影を下に下げる用の高さ

//コンストラクタ・デストラクタ
CTeleportShadow::CTeleportShadow() {
	_Hndl = -1;
	_SelectHndl = -1;
	_Rad = SHADOW_RAD;
	_IsActive = false;
	_CheckTeleport = false;
}
CTeleportShadow::~CTeleportShadow() {
	Fin();
}

//初期化
void CTeleportShadow::Init() {
	_Pos = Vector3D::ZeroVec();
	_SelectingPos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Rad = SHADOW_RAD;
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
	_SelectHndl = -1;
	_IsActive = false;
	_CheckTeleport = false;
	_cSwitch = nullptr;
}

//ロード
void CTeleportShadow::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SHADOW)); }
	if (_SelectHndl == -1) { _SelectHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SHADOW2)); }
}

//セット
void CTeleportShadow::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_SelectHndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, { _Pos._X, _Pos._Y - SHADOW_HEIGHT, _Pos._Z });
	MV1SetRotationXYZ(_SelectHndl, _Rot);
	MV1SetPosition(_SelectHndl, { _SelectingPos._X, _SelectingPos._Y - SHADOW_HEIGHT, _SelectingPos._Z });
}

//メイン処理
void CTeleportShadow::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//一旦プレイヤーのテレポートフラグオフ
	cPlayer->SetTeleport(false);
	//一旦テレポートフラグオフ
	_CheckTeleport = false;

	//スイッチがnullでなけらば
	if (_cSwitch != nullptr) {
		//スイッチが押されているなら生存フラグオン
		_IsActive = _cSwitch->GetPressed();
		if (StageID == eStageID::STAGE_0)
			CTutorial::GetInstance()->SetPressed(_cSwitch->GetPressed());
	}
}

//描画
void CTeleportShadow::Draw() {
	//プレイヤー情報取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_IsActive == true) {
		if (_CheckTeleport == false) {
			//テレポート不可モデル描画
			MV1DrawModel(_Hndl);
		}
		else if (_CheckTeleport == true) {
			//テレポート可能モデル描画
			MV1DrawModel(_SelectHndl);
		}
	}
}

//更新処理
void CTeleportShadow::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, { _Pos._X, _Pos._Y - SHADOW_HEIGHT, _Pos._Z });
	MV1SetRotationXYZ(_SelectHndl, _Rot);
	MV1SetPosition(_SelectHndl, { _SelectingPos._X, _SelectingPos._Y - SHADOW_HEIGHT, _SelectingPos._Z });
}

//終了
void CTeleportShadow::Fin() {
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_SelectHndl != -1) { MV1DeleteModel(_SelectHndl); _SelectHndl = -1; }
}

//ヒット関数
void CTeleportShadow::HitCalc() {
	_CheckTeleport = true;
	_SelectingPos = _Pos;
}
