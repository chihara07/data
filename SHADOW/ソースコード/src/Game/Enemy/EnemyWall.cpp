#include "EnemyWall.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D ENEMYWALL_ROT(90.0f * PI * (1 / 180.f), 0.0f, 0.0f);	//壁敵回転角度

//コンストラクタ・デストラクタ
CEnemyWall::CEnemyWall() {
	_IsForward = false;
	_CoinType = eCoin::NONE;
}
CEnemyWall::~CEnemyWall() {
	Fin();
}

//初期化
void CEnemyWall::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_LimitCenterPos = Vector3D::ZeroVec();
	_LimitDistance = Vector2D::ZeroVec();
	_Rot = ENEMYWALL_ROT;
	_MoveID = eEnemyMoveState::MOVE_STATE_1;
	_Scale = ENEMY_SCALE;
	_Hndl = -1;
	_Spd = ENEMY_SPD;
	_Rad = ENEMY_RAD;
	_Life = 2;
	_IsActive = true;
	_IsForward = false;
	_State = eEnemyState::NORMAL;
	_CoinType = eCoin::NONE;
}

//ロード
void CEnemyWall::Load() {
	//モデルをコピー
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_FLASH)); }
}

//セット
void CEnemyWall::Set() {
	//比率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//メイン処理
void CEnemyWall::Step() {
	if (!_IsActive)
		return;
	//移動関数実行
	CEnemyWall::Move();
	//状態変化関数実行
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//描画
void CEnemyWall::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
}

//終了
void CEnemyWall::Fin() {
	//コピーモデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//更新処理
void CEnemyWall::Update() {
	//回転角度、座標を更新
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//移動関数
void CEnemyWall::Move() {
	//移動処理---------------------------------------------------
	(this->*ActFunc[static_cast<int>(_State)])();

	//移動制限処理
	if (_SavePos._X > _LimitCenterPos._X + _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X + _LimitDistance._X;
	if (_SavePos._X < _LimitCenterPos._X - _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X - _LimitDistance._X;
	if (_SavePos._Y > _LimitCenterPos._Z + _LimitDistance._Y)
		_SavePos._Y = _LimitCenterPos._Z + _LimitDistance._Y;
	if (_SavePos._Y < _LimitCenterPos._Z - _LimitDistance._Y)
		_SavePos._Y = _LimitCenterPos._Z - _LimitDistance._Y;

	//敵の座標を代入
	_Pos = _SavePos;
}

//状態変化関数
void CEnemyWall::ChangeState() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//敵からプレイヤーまでのベクトル
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	//プレイヤーが影状態以外、索敵範囲内、前方にいるなら追いかける状態へ
	if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, SEARCH_RANGE) == true
		&& cPlayer->GetState() == CPlayer::ePlayerState::CLIMB && cPlayer->GetDeath() == false) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	//追いかける状態でプレイヤーが範囲外なら帰還状態へ
	else if (_State != eEnemyState::NORMAL) {
		if (MyLib::Abs(_Pos.Long(_MovePos1)) < MyLib::Abs(_Pos.Long(_MovePos2))) {
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
			_SaveVec = _Pos.Create(_MovePos1);
		}
		else {
			_MoveID = eEnemyMoveState::MOVE_STATE_1;
			_SaveVec = _Pos.Create(_MovePos2);
		}
	}

	//移動ベクトルから角度を計算し代入
	if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Y * _MoveVec._Y >= MyLib::TOLERANCE) {
		_Rot._Z = atan2f(-_MoveVec._Y, -_MoveVec._X) + MyLib::RIGHT_ANGLE;
	}

	_Rot._X = MyLib::RIGHT_ANGLE;
}

//通常状態アクション関数
void CEnemyWall::NormalAct() {
	switch (_MoveID)
	{
		//状態1なら座標2まで移動
	case eEnemyMoveState::MOVE_STATE_1:
	{
		//座標2に向かう
		HeadToDestination(_MovePos2, Vector3D::VGet(_Spd));

		//誤差の範囲まで移動したら座標を代入し状態2へ
		if (_Pos.Long(_MovePos2) < RETURN_ERROR) {
			_SavePos = _MovePos2;
			_SaveVec = _MovePos2.Create(_MovePos1);

			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		}
	}
	break;
	//状態2なら座標1まで移動
	case eEnemyMoveState::MOVE_STATE_2:
	{
		//座標1に向かう
		HeadToDestination(_MovePos1, Vector3D::VGet(_Spd));

		//誤差の範囲まで移動したら座標を代入し状態1へ
		if (_Pos.Long(_MovePos1) < RETURN_ERROR) {
			_SavePos = _MovePos1;
			_SaveVec = _MovePos1.Create(_MovePos2);

			_MoveID = eEnemyMoveState::MOVE_STATE_1;
		}
	}
	break;
	}
}
//プレイヤーを追いかけている状態関数
void CEnemyWall::ChaseAct() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//プレイヤーに向かう
	HeadToDestination(cPlayer->GetPos(), Vector3D::VGet(ENEMY_CHASE_SPD));
}

//ヒット関数
void CEnemyWall::HitCalc(){
	_Pos = _MovePos1;									//座標1へ
	_Rot = ENEMYWALL_ROT;								//回転角度初期化
	_MoveID = eEnemyMoveState::MOVE_STATE_1;			//状態1へ
	_State = eEnemyState::NORMAL;						//通常状態へ
}

//死亡関数
void CEnemyWall::DeathCalc() {
	if (_CoinType == eCoin::HAVE) {
		cCoin->SetActive(true);
		cCoin->SetPos(_Pos);
		CSoundManager::Play(CSoundManager::eSoundID::SE_ENCOIN);
	}
	_IsActive = false;
}
