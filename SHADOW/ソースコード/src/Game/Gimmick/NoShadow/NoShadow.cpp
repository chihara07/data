#include "NoShadow.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr float MOVE_SPD = 1.0f;					//移動速度
constexpr float RETURN_ERROR = 2.0f;				//戻るときの誤差

//コンストラクタ・デストラクタ
CNoShadow::CNoShadow() {
	_Hndl = -1;
	_Spd = 0.f;
	_State = eState::NORMAL;
	_MoveID = eMoveState::MOVE1;
}
CNoShadow::~CNoShadow() {
	Fin();
}

//初期化
void CNoShadow::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_Spd = MOVE_SPD;
	_Hndl = -1;
	_State = eState::NORMAL;
	_MoveID = eMoveState::MOVE1;
}

//ロード
void CNoShadow::Load() {
	//モデル読み込み
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::NOSHADOW)); }
}

//セット
void CNoShadow::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//コリジョン情報構築
	MV1SetupCollInfo(_Hndl);
}

//メイン処理
void CNoShadow::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_State == eState::SPECIAL && _MoveID == eMoveState::MOVE2) {

	}
	else {
		//当たり判定結果
		MV1_COLL_RESULT_POLY_DIM res;
		//当たり判定結果格納
		res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetPos(), cPlayer->GetRad());

		//ヒットしているなら
		if (res.HitNum > 0 &&
			(cPlayer->GetState() == CPlayer::ePlayerState::SHADOW || cPlayer->GetState() == CPlayer::ePlayerState::CLIMB)) {
			cPlayer->SetState(CPlayer::ePlayerState::NORMAL);
		}

		//コリジョンデータ破棄
		MV1CollResultPolyDimTerminate(res);
	}

	if (_State == eState::MOVE || _State == eState::SPECIAL) {
		switch (_MoveID)
		{
			//状態1なら座標2まで移動
		case eMoveState::MOVE1:
		{
			//目的の場所までのベクトルを求めて、移動速度分進める
			_SavePos = _Pos;
			_MoveVec = _SavePos.Create(_MovePos2);
			_MoveVec.Normalize();
			_SavePos = _MoveVec * _Spd;
			_SavePos += _Pos;

			//誤差の範囲まで移動したら座標を代入し状態2へ
			if (_Pos.Long(_MovePos2) < RETURN_ERROR) {
				_Pos = _MovePos2;
				_MoveID = eMoveState::MOVE2;
			}
		}
		break;
		//状態2なら座標1まで移動
		case eMoveState::MOVE2:
		{
			//目的の場所までのベクトルを求めて、移動速度分進める
			_SavePos = _Pos;
			_MoveVec = _SavePos.Create(_MovePos1);
			_MoveVec.Normalize();
			_SavePos = _MoveVec * _Spd;
			_SavePos += _Pos;

			//誤差の範囲まで移動したら座標を代入し状態1へ
			if (_Pos.Long(_MovePos1) < RETURN_ERROR) {
				_Pos = _MovePos1;
				_MoveID = eMoveState::MOVE1;
			}
		}
		break;
		}

		_Pos = _SavePos;
	}
}

//描画
void CNoShadow::Draw() {
	if (_State == eState::SPECIAL && _MoveID == eMoveState::MOVE2) {

	}
	else {
		MV1DrawModel(_Hndl);
	}
}

//更新処理
void CNoShadow::Update() {
	//回転角度、座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//コリジョン情報構築
	MV1SetupCollInfo(_Hndl);
}

//終了
void CNoShadow::Fin() {
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//ヒット関数
void CNoShadow::HitCalc() {
}
