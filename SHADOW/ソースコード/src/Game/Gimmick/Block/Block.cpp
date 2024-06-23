#include "Block.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr float MOVE_SPD = 3.f;						//移動速度
constexpr float RETURN_ERROR = 2.0f;				//戻るときの誤差

//コンストラクタ・デストラクタ
CBlock::CBlock() {
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
	_Hndl = -1;
}
CBlock::~CBlock() {
	Fin();
}

//初期化
void CBlock::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Spd = MOVE_SPD;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
}

//ロード
void CBlock::Load() {
	//モデル読み込み
	if (_State == eState::NORMAL) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BLOCK)); }
	}
	else {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BLOCK2)); }
	}
}

//セット
void CBlock::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//コリジョン情報構築
	MV1SetupCollInfo(_Hndl);
}

//メイン処理
void CBlock::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//当たり判定結果
	MV1_COLL_RESULT_POLY_DIM res;

	if (_State == eState::NORMAL) {
		//当たり判定結果格納
		res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetTeleportPos(), cPlayer->GetRad());

		//ヒットしているなら
		if (res.HitNum > 0 && cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
			cPlayer->SetState(CPlayer::ePlayerState::NORMAL);
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLRETURN);
		}
	}
	else {
		//当たり判定結果格納
		res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetTeleportPos(), cPlayer->GetRad());

		//ヒットしているなら
		if (res.HitNum > 0 && cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
			cPlayer->SetState(CPlayer::ePlayerState::NORMAL);
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLRETURN);
		}
	}

	MV1CollResultPolyDimTerminate(res);

	if (_State == eState::MOVE) {
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
void CBlock::Draw() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
		MV1DrawModel(_Hndl);
	}
}

//更新処理
void CBlock::Update() {
	//比率・座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//コリジョン情報構築
	MV1SetupCollInfo(_Hndl);
}

//終了
void CBlock::Fin() {
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//ヒット関数
void CBlock::HitCalc() {
}
