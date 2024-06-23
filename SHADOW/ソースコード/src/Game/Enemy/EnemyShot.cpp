#include "EnemyShot.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D BULLET_SCALE(0.04f, 0.04f, 0.04f);		//�e�g�嗦
constexpr Vector3D BULLET_SHOT_POS(0.f, -3.f, -5.f);	//�G���ˈʒu
constexpr float SOUND_RANGE = 300.0f;					//���̕�������͈�
constexpr float BULLET_RAD = 4.f;						//�e���a
constexpr float BULLET_SPD = 3.f;						//�e���x
constexpr int BULLET_MAX_COUNT = 50;					//�e�J�E���g�ő�l
constexpr int BULLET_INTERVAL = 40;						//�e�C���^�[�o��

//�R���X�g���N�^�E�f�X�g���N�^
CEnemyShot::CEnemyShot() {
	_BulletRot = Vector3D::ZeroVec();
	_BulletMove = Vector3D::ZeroVec();
	_BulletScale = Vector3D::ZeroVec();
	_BulletRad = 0.f;
	_IsForward = false;
	_IsBulletActive = false;
	_KnockBackSpd = 0.f;
	_CoinType = eCoin::NONE;
	_BulletHndl = -1;
	_BulletCount = 0;
	_BulletInterval = 0;
}
CEnemyShot::~CEnemyShot() {
	Fin();
}

//������
void CEnemyShot::Init() {
	_Pos = Vector3D::ZeroVec();;
	_Rot = Vector3D::ZeroVec();;
	_ResetRot = _Rot;
	_BulletRot = Vector3D::ZeroVec();
	_BulletMove = Vector3D::VGet(0.f, 0.f, -BULLET_SPD);
	_Scale = ENEMY_SCALE;
	_BulletScale = BULLET_SCALE;
	_Rad = ENEMY_RAD;
	_BulletRad = BULLET_RAD;
	_IsActive = true;
	_IsForward = false;
	_IsBulletActive = false;
	_KnockBackSpd = 0.f;
	_CoinType = eCoin::NONE;
	_BulletHndl = -1;
	_BulletCount = 0;
	_BulletInterval = 0;
}

//���[�h
void CEnemyShot::Load() {
	//���f�����R�s�[
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_SHOT)); }
	if (_BulletHndl == -1) { _BulletHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BULLET)); }
}

//�Z�b�g
void CEnemyShot::Set() {
	//�䗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_BulletHndl, _BulletScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_BulletHndl, _BulletRot);
	MV1SetPosition(_BulletHndl, _BulletPos);
}

//���C������
void CEnemyShot::Step() {
	if (!_IsActive)
		return;

	//���_�ɕ��s�ړ�����s����쐬
	MyMatrix OriginMat = MyMatrix::GetTranslateMat(-_Pos);
	//�v���C���[��Y����]�s����쐬
	MyMatrix RotYMat = MyMatrix::GetYawMatrix(_Rot._Y);
	//���s�ړ�����s����쐬
	MyMatrix MoveMat = MyMatrix::GetTranslateMat(_BulletMove);
	//���̈ʒu�ɖ߂����s�ړ�����s����쐬
	MyMatrix ReturnMat = MyMatrix::GetTranslateMat(_Pos);

	//�e�s�������
	MyMatrix CompoundMat;
	CompoundMat = ReturnMat * RotYMat;
	CompoundMat *= MoveMat;
	CompoundMat *= OriginMat;

	Vector3D moveVec = CompoundMat * _Pos;

	moveVec = _Pos.Create(moveVec);

	//�G����v���C���[�܂ł̃x�N�g��
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	//�v���C���[���e��ԈȊO�A���G�͈͓��A�O���ɂ���Ȃ�ǂ��������Ԃ�
	if (moveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, SEARCH_RANGE2) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetState() != CPlayer::ePlayerState::CLIMB &&
		cPlayer->GetDeath() == false) {
		_Rot = Vector3D::VGet(0.0f, atan2f(-playerVec._X, -playerVec._Z), 0.0f);
		_IsForward = true;
	}
	else {
		_Rot._Y = _ResetRot._Y;
		_IsForward = false;
	}

	Shot();

	/*if (_Life <= 0)
		DeathCalc();*/

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//�`��
void CEnemyShot::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
	if (_IsBulletActive == true) { MV1DrawModel(_BulletHndl); }
}

//�I��
void CEnemyShot::Fin() {
	//�R�s�[���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_BulletHndl != -1) { MV1DeleteModel(_BulletHndl); _BulletHndl = -1; }
}

//�X�V����
void CEnemyShot::Update() {
	//��]�p�x�A���W���X�V
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	//��]�p�x�A���W���X�V
	MV1SetRotationXYZ(_BulletHndl, _BulletRot);
	MV1SetPosition(_BulletHndl, _BulletPos);
	//��]�p�x�A���W���X�V
}

//���ˊ֐�
void CEnemyShot::Shot() {
	if (_IsBulletActive == true) {
		//���_�ɕ��s�ړ�����s����쐬
		MyMatrix enemyMoveOriginMat = MyMatrix::GetTranslateMat(-_BulletPos);
		//�v���C���[��Y����]�s����쐬
		MyMatrix enemyRotYMat = MyMatrix::GetYawMatrix(_BulletRot._Y);
		//���s�ړ�����s����쐬
		MyMatrix enemyMoveMat = MyMatrix::GetTranslateMat(_BulletMove);
		//���̈ʒu�ɖ߂����s�ړ�����s����쐬
		MyMatrix enemyReturnMat = MyMatrix::GetTranslateMat(_BulletPos);

		//�e�s�������
		MyMatrix playerCompoundMat = enemyReturnMat * enemyRotYMat;
		playerCompoundMat *= enemyMoveMat;
		playerCompoundMat *= enemyMoveOriginMat;

		//���W�ɍs����|���Ēe�̍��W���Z�o
		_BulletPos = playerCompoundMat * _BulletPos;

		_BulletCount--;
	}

	if (_BulletCount <= 0) {
		_IsBulletActive = false;
		_BulletInterval++;
	}

	if (_BulletInterval > BULLET_INTERVAL) {
		BulletRequest();
		_BulletInterval = 0;
	}
}

//�e���N�G�X�g
void CEnemyShot::BulletRequest() {
	if (_IsBulletActive == true) {
		return;
	}

	if (_IsActive == true) {
		_IsBulletActive = true;

		//�v���C���[�Ƌ߂��Ȃ特���o��
		if (MyLib::Abs(cPlayer->GetPos().Long(_Pos)) < SOUND_RANGE) {
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENSHOT);
		}

		_BulletCount = BULLET_MAX_COUNT;

		//���_�ɕ��s�ړ�����s����쐬
		MyMatrix OriginMat = MyMatrix::GetTranslateMat(-_Pos);
		//�v���C���[��Y����]�s����쐬
		_BulletRot._Y = _Rot._Y;
		MyMatrix RotYMat = MyMatrix::GetYawMatrix(_BulletRot._Y);
		//���s�ړ�����s����쐬
		MyMatrix MoveMat = MyMatrix::GetTranslateMat(BULLET_SHOT_POS);
		//���̈ʒu�ɖ߂����s�ړ�����s����쐬
		MyMatrix ReturnMat = MyMatrix::GetTranslateMat(_Pos);

		//�e�s�������
		MyMatrix CompoundMat;
		CompoundMat = ReturnMat * RotYMat;
		CompoundMat *= MoveMat;
		CompoundMat *= OriginMat;

		//���W�ɍs����|���Ēe�̍��W���Z�o
		_BulletPos = CompoundMat * _Pos;
	}
}

//�q�b�g�֐�
void CEnemyShot::HitCalc() {
	_Rot = Vector3D::ZeroVec();					//��]�p�x������
	_State = eEnemyState::NORMAL;				//�ʏ��Ԃ�
}

