#include "goal.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

//コンストラクタ・デストラクタ
CGoal::CGoal() {
	_Hndl = -1;
}
CGoal::~CGoal() {
	Fin();
}

//初期化
void CGoal::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
}

//ロード
void CGoal::Load() {
	//モデル読み込み
	if (_Hndl == -1){
		_Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::GOAL));
	}
}

//セット
void CGoal::Set() {
	//比率・座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetPosition(_Hndl, _Pos);
}

//メイン処理
void CGoal::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//当たり判定結果
	MV1_COLL_RESULT_POLY_DIM res;
	//当たり判定結果格納
	res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetPos(), cPlayer->GetRad());

	//ヒットしているなら
	if (res.HitNum > 0) {
		cPlayer->SetClear(true);
	}

	//コリジョンデータ破棄
	MV1CollResultPolyDimTerminate(res);
}

//描画
void CGoal::Draw() {
	MV1DrawModel(_Hndl);
}

//更新処理
void CGoal::Update() {
	//回転角度、座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//終了
void CGoal::Fin() {
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//ヒット関数
void CGoal::HitCalc() {
}
