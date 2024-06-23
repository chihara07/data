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

constexpr Vector3D ENEMYWALL_ROT(90.0f * PI * (1 / 180.f), 0.0f, 0.0f);	//�ǓG��]�p�x

//�R���X�g���N�^�E�f�X�g���N�^
CEnemyWall::CEnemyWall() {
	_IsForward = false;
	_CoinType = eCoin::NONE;
}
CEnemyWall::~CEnemyWall() {
	Fin();
}

//������
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

//���[�h
void CEnemyWall::Load() {
	//���f�����R�s�[
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_FLASH)); }
}

//�Z�b�g
void CEnemyWall::Set() {
	//�䗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//���C������
void CEnemyWall::Step() {
	if (!_IsActive)
		return;
	//�ړ��֐����s
	CEnemyWall::Move();
	//��ԕω��֐����s
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//�`��
void CEnemyWall::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
}

//�I��
void CEnemyWall::Fin() {
	//�R�s�[���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�X�V����
void CEnemyWall::Update() {
	//��]�p�x�A���W���X�V
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//�ړ��֐�
void CEnemyWall::Move() {
	//�ړ�����---------------------------------------------------
	(this->*ActFunc[static_cast<int>(_State)])();

	//�ړ���������
	if (_SavePos._X > _LimitCenterPos._X + _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X + _LimitDistance._X;
	if (_SavePos._X < _LimitCenterPos._X - _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X - _LimitDistance._X;
	if (_SavePos._Y > _LimitCenterPos._Z + _LimitDistance._Y)
		_SavePos._Y = _LimitCenterPos._Z + _LimitDistance._Y;
	if (_SavePos._Y < _LimitCenterPos._Z - _LimitDistance._Y)
		_SavePos._Y = _LimitCenterPos._Z - _LimitDistance._Y;

	//�G�̍��W����
	_Pos = _SavePos;
}

//��ԕω��֐�
void CEnemyWall::ChangeState() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�G����v���C���[�܂ł̃x�N�g��
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	//�v���C���[���e��ԈȊO�A���G�͈͓��A�O���ɂ���Ȃ�ǂ��������Ԃ�
	if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, SEARCH_RANGE) == true
		&& cPlayer->GetState() == CPlayer::ePlayerState::CLIMB && cPlayer->GetDeath() == false) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	//�ǂ��������ԂŃv���C���[���͈͊O�Ȃ�A�ҏ�Ԃ�
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

	//�ړ��x�N�g������p�x���v�Z�����
	if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Y * _MoveVec._Y >= MyLib::TOLERANCE) {
		_Rot._Z = atan2f(-_MoveVec._Y, -_MoveVec._X) + MyLib::RIGHT_ANGLE;
	}

	_Rot._X = MyLib::RIGHT_ANGLE;
}

//�ʏ��ԃA�N�V�����֐�
void CEnemyWall::NormalAct() {
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

			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		}
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

			_MoveID = eEnemyMoveState::MOVE_STATE_1;
		}
	}
	break;
	}
}
//�v���C���[��ǂ������Ă����Ԋ֐�
void CEnemyWall::ChaseAct() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�v���C���[�Ɍ�����
	HeadToDestination(cPlayer->GetPos(), Vector3D::VGet(ENEMY_CHASE_SPD));
}

//�q�b�g�֐�
void CEnemyWall::HitCalc(){
	_Pos = _MovePos1;									//���W1��
	_Rot = ENEMYWALL_ROT;								//��]�p�x������
	_MoveID = eEnemyMoveState::MOVE_STATE_1;			//���1��
	_State = eEnemyState::NORMAL;						//�ʏ��Ԃ�
}

//���S�֐�
void CEnemyWall::DeathCalc() {
	if (_CoinType == eCoin::HAVE) {
		cCoin->SetActive(true);
		cCoin->SetPos(_Pos);
		CSoundManager::Play(CSoundManager::eSoundID::SE_ENCOIN);
	}
	_IsActive = false;
}
