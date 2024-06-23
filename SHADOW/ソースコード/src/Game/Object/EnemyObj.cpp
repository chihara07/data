#include "EnemyObj.h"
#include "../../Library/Sound/SoundManager.h"

//�ʏ��ԃA�N�V�����֐�
void CEnemyObj::NormalAct() {
	switch (_MoveID)
	{
		//���1�Ȃ���W2�܂ňړ�
	case eEnemyMoveState::MOVE_STATE_1:
	{
		//���W2�Ɍ�����
		HeadToDestination(_MovePos2, Vector3D::VGet(_Spd));

		//�덷�͈̔͂܂ňړ���������W���������2��
		if (_Pos.Long(_MovePos2) < RETURN_ERROR) {
			_SavePos = _MovePos2;
			_SaveVec = _MovePos2.Create(_MovePos1);
			_SaveRotY = atan2f(-_SaveVec._X, -_SaveVec._Z);
			_State = eEnemyState::TURN;
		}

		_OldID = eEnemyMoveState::MOVE_STATE_1;
	}
	break;
	//���2�Ȃ���W1�܂ňړ�
	case eEnemyMoveState::MOVE_STATE_2:
	{
		//���W1�Ɍ�����
		HeadToDestination(_MovePos1, Vector3D::VGet(_Spd));

		//�덷�͈̔͂܂ňړ���������W���������1��
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
//�v���C���[��ǂ������Ă����Ԋ֐�
void CEnemyObj::ChaseAct() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�v���C���[�Ɍ�����
	HeadToDestination(cPlayer->GetPos(), Vector3D::VGet(ENEMY_CHASE_SPD, 0.f, ENEMY_CHASE_SPD));
};
//�m�b�N�o�b�N��Ԋ֐�
void CEnemyObj::KnockBackAct() {
	_MoveVec.Normalize();
	_SavePos = _Pos + Vector3D::VGet((_MoveVec._X * _KnockBackSpd), 0.f, (_MoveVec._Z * _KnockBackSpd));
	_KnockBackSpd *= KNOCKBACK_SPD_REDUCE;

	if (_KnockBackSpd < KNOCKBACK_SPD_MIN) {
		_State = eEnemyState::CHASE;
		_KnockBackSpd = KNOCKBACK_SPD;
	}
};
//�v���C���[������Ԋ֐�
void CEnemyObj::DiscoveryAct() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	_MoveVec = _Pos.Create(cPlayer->GetPos());

	_SavePos = _Pos;

	_DiscoveryCount++;
};
//�U�������Ԋ֐�
void CEnemyObj::TurnAct() {
	//�ړI�̊p�x�܂ŉ�]������ʏ��Ԃ�
	if (MyLib::Abs(_Rot._Y - _SaveRotY) < MyLib::ConvertDegreesToRadian(TURN_ROT)) {
		_Rot._Y = _SaveRotY;

		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_State = eEnemyState::NORMAL;

		_OldState = eEnemyState::TURN;
	}

	//�ړI�n�܂ł̊p�x���m�F
	_CheckRot = _MoveVec ^ _SaveVec;
	//�p�x�̋߂����ɉ�]
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

//���S�֐�
void CEnemyObj::DeathCalc() {
	//�R�C���������Ă���Ȃ�R�C������
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

//�ړI�n�Ɍ������֐�
void CEnemyObj::HeadToDestination(Vector3D destination, Vector3D spd) {
	//�ړI�n�܂ł̃x�N�g�������߂Ĉړ����x���i�߂�
	_SavePos = _Pos;
	_MoveVec = _SavePos.Create(destination);
	_MoveVec.Normalize();
	_SavePos = _MoveVec * spd;
	_SavePos += _Pos;
}
