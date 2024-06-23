#include "Enemy.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/Draw/DrawManager.h"

//�R���X�g���N�^�E�f�X�g���N�^
CEnemy::CEnemy() {
	_IsForward = false;
	_KnockBackSpd = 0.f;
	_SearchRange = 0.f;
	_SaveRotY = 0.f;
	_CoinType = eCoin::NONE;
	_DiscoveryCount = 0;
	cCoin = nullptr;
}
CEnemy::~CEnemy() {
	Fin();
}

//������
void CEnemy::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_SaveVec = Vector3D::ZeroVec();
	_LimitCenterPos = Vector3D::ZeroVec();
	_LimitDistance = Vector2D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = ENEMY_SCALE;
	_Hndl = -1;
	_DiscoveryCount = 0;
	_Spd = ENEMY_SPD;
	_SearchRange = SEARCH_RANGE;
	_KnockBackSpd = KNOCKBACK_SPD;
	_Rad = ENEMY_RAD;
	_SaveRotY = 0.f;
	_Life = ENEMY_LIFE;
	_IsActive = true;
	_IsForward = false;
	_State = eEnemyState::NORMAL;
	_OldState = eEnemyState::NORMAL;
	_CoinType = eCoin::NONE;
	_MoveID = eEnemyMoveState::MOVE_STATE_1;
	_OldID = eEnemyMoveState::NON;
}

//���[�h
void CEnemy::Load() {
	//���f�����R�s�[
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY)); }
}

//�Z�b�g
void CEnemy::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//���C������
void CEnemy::Step() {
	if (!_IsActive)
		return;
	//�ړ��֐����s
	Move();
	//��ԕω��֐����s
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//�`��
void CEnemy::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }

	if(_State == eEnemyState::DISCOVERY && _IsActive == true)
		CDrawManager::GetInstance()->Draw(PATH_TYPE::DISCOVERY, VGet(_Pos._X, _Pos._Y + DISCOVERY_GRAPH_HEIGHT, _Pos._Z), 
											DISCOVERY_GRAPH_POS._X, DISCOVERY_GRAPH_POS._Y, DISCOVERY_GRAPH_SIZE, 0.f);
}

//�I��
void CEnemy::Fin() {
	//�R�s�[���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�X�V����
void CEnemy::Update() {
	//��]�p�x�A���W���X�V
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//�ړ��֐�
void CEnemy::Move() {
	(this->*ActFunc[static_cast<int>(_State)])();

	//�ړ���������
	if (_SavePos._X > _LimitCenterPos._X + _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X + _LimitDistance._X;
	if (_SavePos._X < _LimitCenterPos._X - _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X - _LimitDistance._X;
	if (_SavePos._Z > _LimitCenterPos._Z + _LimitDistance._Y)
		_SavePos._Z = _LimitCenterPos._Z + _LimitDistance._Y;
	if (_SavePos._Z < _LimitCenterPos._Z - _LimitDistance._Y)
		_SavePos._Z = _LimitCenterPos._Z - _LimitDistance._Y;

	//�G�̍��W����
	_Pos = _SavePos;
}

//��ԕω��֐�
void CEnemy::ChangeState() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�G����v���C���[�܂ł̃x�N�g��
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	//�v���C���[���e��ԈȊO�A���G�͈͓��A�O���ɂ���Ȃ甭����Ԃ�
	if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount < DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::DISCOVERY;
		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_OldID = eEnemyMoveState::NON;
	}
	//�v���C���[���e��ԈȊO�A���G�͈͓��A�O���ɂ���A�����J�E���g�����܂�����Ȃ�ǂ��������Ԃ�
	else if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount >= DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	//�ǂ��������ԂŃv���C���[���͈͊O�Ȃ�U�������Ԃ�
	else if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY) {
		if (MyLib::Abs(_Pos.Long(_MovePos1)) < MyLib::Abs(_Pos.Long(_MovePos2))) {
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
			_OldID = eEnemyMoveState::MOVE_STATE_1;
			_SaveVec = _Pos.Create(_MovePos1);
		}
		else {
			_MoveID = eEnemyMoveState::MOVE_STATE_1;
			_OldID = eEnemyMoveState::MOVE_STATE_2;
			_SaveVec = _Pos.Create(_MovePos2);
		}

		_State = eEnemyState::TURN;
		_OldState = eEnemyState::CHASE;


		_SaveRotY = atan2f(-_SaveVec._X, -_SaveVec._Z);

		_DiscoveryCount = 0;
	}

	//�O�̏�Ԃ��U�������ԂȂ�O�̏�Ԃ�ʏ��Ԃ�
	if (_OldState == eEnemyState::TURN)
		_OldState = eEnemyState::NORMAL;
	//�ړ����Ă��邩
	else if (_State != eEnemyState::KNOCKBACK && _State != eEnemyState::TURN && _OldState != eEnemyState::TURN) {
		//�ړ����Ă���Ȃ�ړ��x�N�g������p�x���v�Z�����
		if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Z * _MoveVec._Z >= MyLib::TOLERANCE) {
			_Rot = VGet(0.0f, atan2f(-_MoveVec._X, -_MoveVec._Z), 0.0f);
		}
	}

	//��Ԃɂ���č��G�͈͂�ς���
	if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY)
		_SearchRange = SEARCH_RANGE2;
	else
		_SearchRange = SEARCH_RANGE;

}

//�q�b�g�֐�
void CEnemy::HitCalc(){
	_Pos = _MovePos1;							//���W1��
	_Rot = Vector3D::ZeroVec();					//��]�p�x������
	_MoveID = eEnemyMoveState::MOVE_STATE_1;	//���1��
	_State = eEnemyState::NORMAL;				//�ʏ��Ԃ�
}

