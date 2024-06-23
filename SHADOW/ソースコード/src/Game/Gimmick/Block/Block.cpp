#include "Block.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr float MOVE_SPD = 3.f;						//�ړ����x
constexpr float RETURN_ERROR = 2.0f;				//�߂�Ƃ��̌덷

//�R���X�g���N�^�E�f�X�g���N�^
CBlock::CBlock() {
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
	_Hndl = -1;
}
CBlock::~CBlock() {
	Fin();
}

//������
void CBlock::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Spd = MOVE_SPD;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
}

//���[�h
void CBlock::Load() {
	//���f���ǂݍ���
	if (_State == eState::NORMAL) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BLOCK)); }
	}
	else {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BLOCK2)); }
	}
}

//�Z�b�g
void CBlock::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//�R���W�������\�z
	MV1SetupCollInfo(_Hndl);
}

//���C������
void CBlock::Step() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�����蔻�茋��
	MV1_COLL_RESULT_POLY_DIM res;

	if (_State == eState::NORMAL) {
		//�����蔻�茋�ʊi�[
		res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetTeleportPos(), cPlayer->GetRad());

		//�q�b�g���Ă���Ȃ�
		if (res.HitNum > 0 && cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
			cPlayer->SetState(CPlayer::ePlayerState::NORMAL);
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLRETURN);
		}
	}
	else {
		//�����蔻�茋�ʊi�[
		res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetTeleportPos(), cPlayer->GetRad());

		//�q�b�g���Ă���Ȃ�
		if (res.HitNum > 0 && cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
			cPlayer->SetState(CPlayer::ePlayerState::NORMAL);
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLRETURN);
		}
	}

	MV1CollResultPolyDimTerminate(res);

	if (_State == eState::MOVE) {
		switch (_MoveID)
		{
			//���1�Ȃ���W2�܂ňړ�
		case eMoveState::MOVE1:
		{
			//�ړI�̏ꏊ�܂ł̃x�N�g�������߂āA�ړ����x���i�߂�
			_SavePos = _Pos;
			_MoveVec = _SavePos.Create(_MovePos2);
			_MoveVec.Normalize();
			_SavePos = _MoveVec * _Spd;
			_SavePos += _Pos;

			//�덷�͈̔͂܂ňړ���������W���������2��
			if (_Pos.Long(_MovePos2) < RETURN_ERROR) {
				_Pos = _MovePos2;
				_MoveID = eMoveState::MOVE2;
			}
		}
		break;
		//���2�Ȃ���W1�܂ňړ�
		case eMoveState::MOVE2:
		{
			//�ړI�̏ꏊ�܂ł̃x�N�g�������߂āA�ړ����x���i�߂�
			_SavePos = _Pos;
			_MoveVec = _SavePos.Create(_MovePos1);
			_MoveVec.Normalize();
			_SavePos = _MoveVec * _Spd;
			_SavePos += _Pos;

			//�덷�͈̔͂܂ňړ���������W���������1��
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

//�`��
void CBlock::Draw() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
		MV1DrawModel(_Hndl);
	}
}

//�X�V����
void CBlock::Update() {
	//�䗦�E���W�Z�b�g
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	//�R���W�������\�z
	MV1SetupCollInfo(_Hndl);
}

//�I��
void CBlock::Fin() {
	//���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�q�b�g�֐�
void CBlock::HitCalc() {
}
