#include "EnemyFlash.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Sound/SoundManager.h"

constexpr float FLASH_SCALE = 0.7f;		//�t���b�V���U���g�嗦
constexpr float FLASH_RAD = 70.f;		//�t���b�V���U�����a
constexpr int FLASH_COUNT_MAX = 60;		//�t���b�V���U���J�E���g�ő�l

//�R���X�g���N�^�E�f�X�g���N�^
CEnemyFlash::CEnemyFlash(){
	_FlashScale = Vector3D::ZeroVec();
	_IsForward = false;
	_KnockBackSpd = 0.f;
	_SearchRange = 0.f;
	_CoinType = eCoin::NONE;
	_NearType = eNearType::PLAYER;
	_FlashHndl = -1;
	_FlashRad = 0.f;
	_FlashCount = 0;
	_IsFlashActive = false;
	_IsFlashStandby = false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_IsFindArea[area_index] = false;
		_HitArea[area_index] = false;
	}
	_DiscoveryCount = 0;
}
CEnemyFlash::~CEnemyFlash() {
	Fin();
}

//������
void CEnemyFlash::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_LimitCenterPos = Vector3D::ZeroVec();
	_LimitDistance = Vector2D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_FlashScale(FLASH_SCALE);
	_FlashRad = FLASH_RAD;
	_FlashCount = 0;
	_DiscoveryCount = 0;
	_MoveID = eEnemyMoveState::MOVE_STATE_1;
	_NearType = eNearType::PLAYER;
	_Scale = ENEMY_SCALE;
	_Hndl = -1;
	_FlashHndl = -1;
	_Spd = ENEMY_SPD;
	_KnockBackSpd = KNOCKBACK_SPD;
	_SearchRange = SEARCH_RANGE;
	_Rad = ENEMY_RAD;
	_IsActive = true;
	_IsForward = false;
	_IsFlashActive = false;
	_IsFlashStandby = false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_HitArea[area_index] = false;
	}
	_State = eEnemyState::NORMAL;
	_CoinType = eCoin::NONE;
}

//���[�h
void CEnemyFlash::Load() {
	//���f�����R�s�[
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_FLASH)); }
	if (_FlashHndl == -1) { _FlashHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FLASH_AREA)); }
}

//�Z�b�g
void CEnemyFlash::Set() {
	//�䗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_FlashHndl, _FlashScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_FlashHndl, _Rot);
	MV1SetPosition(_FlashHndl, _Pos);
}

//���C������
void CEnemyFlash::Step() {
	if (!_IsActive)
		return;
	//�ړ��֐����s
	Move();
	//�e�G���A�̃`�F�b�N
	CheckArea();
	//��ԕω��֐����s
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//�`��
void CEnemyFlash::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
	if (_IsActive == true && (_IsFlashStandby == true || _IsFlashActive == true)) { MV1DrawModel(_FlashHndl); }
	if (_State == eEnemyState::DISCOVERY && _IsActive == true)
		CDrawManager::GetInstance()->Draw(PATH_TYPE::DISCOVERY, VGet(_Pos._X, _Pos._Y + DISCOVERY_GRAPH_HEIGHT, _Pos._Z),
			DISCOVERY_GRAPH_POS._X, DISCOVERY_GRAPH_POS._Y, DISCOVERY_GRAPH_SIZE, 0.f);
}

//�I��
void CEnemyFlash::Fin() {
	//�R�s�[���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_FlashHndl != -1) { MV1DeleteModel(_FlashHndl); _FlashHndl = -1; }
}

//�X�V����
void CEnemyFlash::Update() {
	//��]�p�x�A���W���X�V
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetPosition(_FlashHndl, _Pos);
	MV1SetScale(_FlashHndl, _FlashScale);
	//��]�p�x�A���W���X�V
}

//�ړ��֐�
void CEnemyFlash::Move() {
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
void CEnemyFlash::ChangeState() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�G����v���C���[�܂ł̃x�N�g��
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	if (IsFlash()) {
		_State = eEnemyState::FLASH;
	}
	else if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount < DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::DISCOVERY;

		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_OldID = eEnemyMoveState::NON;
	}
	//�v���C���[���e��ԈȊO�A���G�͈͓��A�O���ɂ���Ȃ�ǂ��������Ԃ�
	else if (cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _NearType == eNearType::PLAYER && _DiscoveryCount >= DISCOVERY_MAX_COUNT
		&& _MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	else if (IsNearArea()) {
		_State = eEnemyState::CHASE_AREA;
	}
	//�ǂ��������ԂŃv���C���[���͈͊O�Ȃ�A�ҏ�Ԃ�
	else if (_State == eEnemyState::CHASE || _State == eEnemyState::CHASE_AREA || _State == eEnemyState::FLASH
		|| _State == eEnemyState::DISCOVERY) {
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

	if (_OldState == eEnemyState::TURN)
		_OldState = eEnemyState::NORMAL;
	else if (_State != eEnemyState::KNOCKBACK && _State != eEnemyState::TURN && _OldState != eEnemyState::TURN) {
		//�ړ��x�N�g������p�x���v�Z�����
		if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Z * _MoveVec._Z >= MyLib::TOLERANCE) {
			_Rot = VGet(0.f, atan2f(-_MoveVec._X, -_MoveVec._Z), 0.f);
		}
	}

	if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY)
		_SearchRange = SEARCH_RANGE2;
	else
		_SearchRange = SEARCH_RANGE;
}

//�e�G���A��ǂ������Ă����Ԋ֐�
void CEnemyFlash::ChaseAreaAct() {
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	if (_IsFindArea[static_cast<int>(_NearType)] == true) {
		//�e�G���A�܂ł̃x�N�g�������߂Ĉړ����x���i�߂�
		_SavePos = _Pos;
		_AreaChaseVec = _SavePos.Create(cPlayerAttack->GetAreaPos(static_cast<int>(_NearType)));
		_AreaChaseVec.Normalize();
		_SavePos = Vector3D::VGet(_AreaChaseVec._X * ENEMY_CHASE_SPD, 0.f, _AreaChaseVec._Z * ENEMY_CHASE_SPD);
		_SavePos += _Pos;

		//�ǂ�������x�N�g����G�̈ړ��x�N�g���ɑ��
		_MoveVec = _AreaChaseVec;
	}
}
//�U����Ԋ֐�
void CEnemyFlash::AttackAct() {
	if (_IsFlashStandby == true) {
		_FlashScale -= (FLASH_SCALE / static_cast<float>(FLASH_COUNT_MAX));
		if (_FlashScale._X < 0.f) {
			_IsFlashStandby = false;
			_IsFlashActive = true;
			CSoundManager::Stop(CSoundManager::eSoundID::SE_ENCHARGE);
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENFLASH);
			_FlashScale(FLASH_SCALE);
		}
	}
	else if (_IsFlashActive == true) {
		_FlashCount++;

		if (_FlashCount > FLASH_COUNT_MAX) {
			_IsFlashActive = false;
			_FlashCount = 0;
			for (int area_index = 0; area_index < AREA_NUM; area_index++) {
				_HitArea[area_index] = false;
			}
		}
	}
}

//���G�͈͂ɉe�G���A�����邩
bool CEnemyFlash::CheckPlayerAreaLength(int id) {
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	//�n���ꂽID�ȊO�������
	int otherID[AREA_NUM][2] = {
		{1,2},
		{0,2},
		{0,1}
	};

	if(cPlayerAttack->GetAreaActive(id) == false)
		return false;

	if ((cPlayerAttack->GetAreaActive(otherID[id][0]) == false ||
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(id)) - cPlayerAttack->GetAreaRad(id)) <=
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(otherID[id][0])) - cPlayerAttack->GetAreaRad(otherID[id][0]))) &&
		(cPlayerAttack->GetAreaActive(otherID[id][1]) == false ||
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(id)) - cPlayerAttack->GetAreaRad(id)) <=
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(otherID[id][1])) - cPlayerAttack->GetAreaRad(otherID[id][1]))))
		return true;

	return false;
}

//�e�G���A�ƃv���C���[�̂ǂꂪ�߂���
void CEnemyFlash::CheckLength(){
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayerAttack->GetAreaActive(0) == false && cPlayerAttack->GetAreaActive(1) == false &&
		cPlayerAttack->GetAreaActive(2) == false) {
		_NearType = eNearType::PLAYER;
		return;
	}

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (CheckPlayerAreaLength(area_index) == true) {
			if (MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(area_index)) - cPlayerAttack->GetAreaRad(area_index))
				>= MyLib::Abs(_Pos.Long(cPlayer->GetPos()) - cPlayer->GetRad())) {
				_NearType = eNearType::PLAYER;
			}
			else
				_NearType = static_cast<eNearType>(area_index);
		}
	}
}

//�e�G���A�̃`�F�b�N
void CEnemyFlash::CheckArea() {
	//�v���C���[�U���擾
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	//�e�G���A����
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_IsFindArea[area_index] = false;

		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;

		//�e�G���A�ɐG��Ă�����t���b�V���U��������
		if (_IsFlashActive == false
			&& CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), _Pos, _Rad) == true) {
			_HitArea[area_index] = true;
			_IsFlashStandby = true;
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENCHARGE);
		}
		//���G�͈͓��ɉe�G���A�ɂ�����Δ����t���O�I��
		else if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), _Pos, SEARCH_RANGE) == true) {
			_IsFindArea[area_index] = true;
		}
	}
	//�e�G���A�ƃv���C���[�̂ǂꂪ�߂���
	CheckLength();
}

//�q�b�g�֐�
void CEnemyFlash::HitCalc() {
	_Pos = _MovePos1;							//���W1��
	_Rot = Vector3D::ZeroVec();					//��]�p�x������
	_MoveID = eEnemyMoveState::MOVE_STATE_1;	//���1��
	_State = eEnemyState::NORMAL;				//�ʏ��Ԃ�
}

//�t���b�V���U���\��
bool CEnemyFlash::IsFlash() {
	if (_IsFlashActive) return true;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_HitArea[area_index]) return true;
	}
	return false;
}
//�e�G���A�̕����߂���
bool CEnemyFlash::IsNearArea() {
	if (_NearType == eNearType::PLAYER) return false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_IsFindArea[area_index]) return true;
	}
	return false;
}
