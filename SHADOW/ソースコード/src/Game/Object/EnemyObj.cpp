#include "EnemyObj.h"
#include "../../Library/Sound/SoundManager.h"

//通常状態アクション関数
void CEnemyObj::NormalAct() {
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
			_SaveRotY = atan2f(-_SaveVec._X, -_SaveVec._Z);
			_State = eEnemyState::TURN;
		}

		_OldID = eEnemyMoveState::MOVE_STATE_1;
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
			_SaveRotY = atan2f(-_SaveVec._X, -_SaveVec._Z);
			_State = eEnemyState::TURN;
		}

		_OldID = eEnemyMoveState::MOVE_STATE_2;
	}
	break;
	}
};
//プレイヤーを追いかけている状態関数
void CEnemyObj::ChaseAct() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//プレイヤーに向かう
	HeadToDestination(cPlayer->GetPos(), Vector3D::VGet(ENEMY_CHASE_SPD, 0.f, ENEMY_CHASE_SPD));
};
//ノックバック状態関数
void CEnemyObj::KnockBackAct() {
	_MoveVec.Normalize();
	_SavePos = _Pos + Vector3D::VGet((_MoveVec._X * _KnockBackSpd), 0.f, (_MoveVec._Z * _KnockBackSpd));
	_KnockBackSpd *= KNOCKBACK_SPD_REDUCE;

	if (_KnockBackSpd < KNOCKBACK_SPD_MIN) {
		_State = eEnemyState::CHASE;
		_KnockBackSpd = KNOCKBACK_SPD;
	}
};
//プレイヤー発見状態関数
void CEnemyObj::DiscoveryAct() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	_MoveVec = _Pos.Create(cPlayer->GetPos());

	_SavePos = _Pos;

	_DiscoveryCount++;
};
//振り向き状態関数
void CEnemyObj::TurnAct() {
	//目的の角度まで回転したら通常状態へ
	if (MyLib::Abs(_Rot._Y - _SaveRotY) < MyLib::ConvertDegreesToRadian(TURN_ROT)) {
		_Rot._Y = _SaveRotY;

		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_State = eEnemyState::NORMAL;

		_OldState = eEnemyState::TURN;
	}

	//目的地までの角度を確認
	_CheckRot = _MoveVec ^ _SaveVec;
	//角度の近い方に回転
	if (_CheckRot._Y > 0) {
		_Rot._Y += MyLib::ConvertDegreesToRadian(TURN_ROT);
		if (_Rot._Y > (MyLib::ConvertDegreesToRadian(TURN_ROT_MAX)))
			_Rot._Y = (MyLib::ConvertDegreesToRadian(-TURN_ROT_MAX));
	}
	else {
		_Rot._Y -= MyLib::ConvertDegreesToRadian(TURN_ROT);
		if (_Rot._Y < (MyLib::ConvertDegreesToRadian(-TURN_ROT_MAX)))
			_Rot._Y = (MyLib::ConvertDegreesToRadian(TURN_ROT_MAX));
	}

	_SavePos = _Pos;
}

//死亡関数
void CEnemyObj::DeathCalc() {
	//コインを持っているならコイン生成
	if (_CoinType == eCoin::HAVE) {
		cCoin->SetActive(true);
		cCoin->SetPos(_Pos);
		CSoundManager::Play(CSoundManager::eSoundID::SE_ENCOIN);
	}
	_IsActive = false;
	_IsBulletActive = false;
	_IsFlashActive = false;
	CSoundManager::Play(CSoundManager::eSoundID::SE_ENDEATH);
}

//目的地に向かう関数
void CEnemyObj::HeadToDestination(Vector3D destination, Vector3D spd) {
	//目的地までのベクトルを求めて移動速度分進める
	_SavePos = _Pos;
	_MoveVec = _SavePos.Create(destination);
	_MoveVec.Normalize();
	_SavePos = _MoveVec * spd;
	_SavePos += _Pos;
}
