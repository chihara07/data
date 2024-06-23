#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerParameter.h"
#include <iostream>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/InputManager.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Effect/effekseer.h"
#include "../../Game/Enemy/EnemyManager.h"

using namespace PLAYER;

CPlayer* CPlayer::_Instance = nullptr;

Vector3D playerVec;
Vector3D playerPos;
int _ChangeEffectHndl = -1;

CPlayer* CPlayer::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CPlayer;
	}

	return _Instance;
}

void CPlayer::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//�R���X�g���N�^�E�f�X�g���N�^
CPlayer::CPlayer() {
	Init(Vector3D::ZeroVec());
}
CPlayer::~CPlayer() {
	CPlayerAttack::GetInstance()->DeleteInstance();
}

//������
void CPlayer::Init(Vector3D v) {
	_Pos = v;
	_SavePos = v;
	_TeleportPos = Vector3D::ZeroVec();
	_TeleportTargetPos = Vector3D::ZeroVec();
	_Move = Vector3D::ZeroVec();
	_TeleportMove = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = PLAYER_SCALE;
	_Hndl = -1;
	_ShadowHndl = -1;
	_TeleportHndl = -1;
	_DeathEffectHndl = -1;
	_ChangeEffectHndl = -1;
	_Spd = PLAYER_SPD;
	_ShadowSpd = SHADOW_SPD;
	_TeleportSpd = TELEPORT_SPD;
	_Rad = PLAYER_RAD;
	_Gravity = 0.f;
	_Life = PLAYER_LIFE;
	_HaveCoin = 0;
	_IsActive = true;
	_Teleport = false;
	_IsClimb = false;
	_IsGround = false;
	_HitArea = false;
	_IsClear = false;
	_IsDeath = false;
	_State = ePlayerState::NORMAL;
	_OldState = ePlayerState::NORMAL;
}

//���[�h
void CPlayer::Load() {
	if (_Hndl == -1) {
		_Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER));
	}
	if (_ShadowHndl == -1) {
		_ShadowHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_SHADOW));
	}
	if (_TeleportHndl == -1) {
		_TeleportHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_TELEPORT));
	}
}

//�Z�b�g
void CPlayer::Set() {
	//�g�嗦�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_ShadowHndl, _Scale);
	MV1SetScale(_TeleportHndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_ShadowHndl, _Rot);
	MV1SetPosition(_ShadowHndl, { _Pos._X, _Pos._Y, _Pos._Z });
	MV1SetPosition(_ShadowHndl, { _Pos._X, _Pos._Y - PLAYER_SHADOW_HEIGHT, _Pos._Z });
	MV1SetRotationXYZ(_TeleportHndl, _Rot);
	MV1SetPosition(_TeleportHndl, _TeleportPos);
}

//���C������
void CPlayer::Step() {
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (_ChangeEffectHndl != -1 && (_IsDeath == true || _State == ePlayerState::NORMAL)) {
		CEffekseerCtrl::Stop(_ChangeEffectHndl);
	}

	//�v���C���[���S�G�t�F�N�g���I�������
	if (CEffekseerCtrl::IsActive(_DeathEffectHndl) == false && _IsDeath == true) {
		CPlayer::ReSpawn();
		cPlayerCamera->Init();
	}

	if (_IsDeath == true) return;

	playerPos = _Pos;

	//�������͂��Ȃ��Ȃ�ړ���0
	_Move = Vector3D::ZeroVec();
	_TeleportMove = Vector3D::ZeroVec();

	//�d�͏���
	//=====================================
	if (_State != ePlayerState::CLIMB) {
		if (_State == ePlayerState::TELEPORT) {
			_Pos._Y += _Gravity;
			_Gravity -= PLAYER_GRAVITY2;

			if (_Gravity < PLAYER_GRAVITY_MAX2) { _Gravity = PLAYER_GRAVITY_MAX2; }
		}
		else {
			_Pos._Y += _Gravity;
			_Gravity -= PLAYER_GRAVITY;

			if (_Gravity < PLAYER_GRAVITY_MAX) { _Gravity = PLAYER_GRAVITY_MAX; }
		}
	}
	//=====================================
	if (_Life <= 0)
		_IsActive = false;

	(this->*ActFunc[static_cast<int>(_State)])();

	Move(cPlayerCamera->GetCameraRot()._Y);

	CPlayerAttack::GetInstance()->SetPlayerMove(false);

	if (_Pos._Y < DEATH_HEIGHT) {
		ReSpawn();
		playerVec = Vector3D::ZeroVec();
		playerPos = Vector3D::ZeroVec();
		CEnemyManager::GetInstance()->Reset();
		cPlayerCamera->Init();
	}

	if (_State != ePlayerState::CLIMB) {
		playerVec = playerPos.Create(_Pos);
		if (playerVec._X * playerVec._X >= MyLib::TOLERANCE || playerVec._Z * playerVec._Z >= MyLib::TOLERANCE) {
			_Rot = Vector3D::VGet(0.0f, atan2f(-playerVec._X, -playerVec._Z), 0.0f);
			CPlayerAttack::GetInstance()->SetPlayerMove(true);
		}	
	}
}

//�`��
void CPlayer::Draw() {
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (_IsDeath == false){
		if (_Pos.Long(cPlayerCamera->GetcameraPos()) > CAN_DRAW_CAMERA_DISTANCE) {
			if (_State == ePlayerState::SHADOW || _State == ePlayerState::CLIMB) {
				MV1DrawModel(_ShadowHndl);
			}
			else {
				MV1DrawModel(_Hndl);
			}
		}

		if (_TeleportPos.Long(cPlayerCamera->GetcameraPos()) > CAN_DRAW_CAMERA_DISTANCE &&_State == ePlayerState::TELEPORT) {
			MV1DrawModel(_TeleportHndl);
		}
	}
}

//�I��
void CPlayer::Fin() {
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_ShadowHndl != -1) { MV1DeleteModel(_ShadowHndl); _ShadowHndl = -1; }
	if (_TeleportHndl != -1) { MV1DeleteModel(_TeleportHndl); _TeleportHndl = -1; }
	_DeathEffectHndl = -1;
	_ChangeEffectHndl = -1;
}

//�X�V����
void CPlayer::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_ShadowHndl, _Rot);
	if (_State == ePlayerState::CLIMB) {
		MV1SetPosition(_ShadowHndl, { _Pos._X, _Pos._Y, _Pos._Z });
	}
	else{
		MV1SetPosition(_ShadowHndl, { _Pos._X, _Pos._Y - PLAYER_SHADOW_HEIGHT, _Pos._Z });
	}
	MV1SetRotationXYZ(_TeleportHndl, _Rot);
	MV1SetPosition(_TeleportHndl, _TeleportPos);
	if (_ChangeEffectHndl != -1) {
		CEffekseerCtrl::SetPosition(_ChangeEffectHndl, _Pos);
		CEffekseerCtrl::SetRot(_ChangeEffectHndl, _Rot);
	}
}

//�ʏ��Ԃ̃A�N�V�����֐�
void CPlayer::NormalAct() {
	//�W�����v�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsPush(CInputManager::eInputType::JUMP) == true
		&& _IsGround == true && CPlayerAttack::GetInstance()->GetHold() == false) {
		//�W�����v�\�Ȃ�W�����v��Ԃ�
		_Gravity = PLAYER_JUMP_POWER;
		_State = ePlayerState::JUMP;
		_IsGround = false;
		CSoundManager::Play(CSoundManager::eSoundID::SE_PLJUMP);
		CSoundManager::SetVolume(CSoundManager::eSoundID::SE_PLJUMP, JUMP_VOLUME);
	}

	//�e�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsDown(CInputManager::eInputType::SHADOW) == true && _HitArea == true) {
		if (_IsClimb == true) {
			//�Ǐ��\�Ȃ�Ǐ���Ԃ�
			_State = ePlayerState::CLIMB;
			if (_OldState == ePlayerState::NORMAL) {
				_ChangeEffectHndl = CEffekseerCtrl::Request(CEffekseerCtrl::_ID[(int)CEffekseerCtrl::eEffectID::CHANGE], _Pos, false);
				CEffekseerCtrl::SetScale(_ChangeEffectHndl, SHADOW_EFFECT_SCALE);
				CSoundManager::Play(CSoundManager::eSoundID::SE_PLSHADOW);
			}
		}
		else if (_IsGround) {
			//����ȊO�Ȃ�e��Ԃ�
			_State = ePlayerState::SHADOW;
			if (_OldState == ePlayerState::NORMAL) {
				_ChangeEffectHndl = CEffekseerCtrl::Request(CEffekseerCtrl::_ID[(int)CEffekseerCtrl::eEffectID::CHANGE], _Pos, false);
				CEffekseerCtrl::SetScale(_ChangeEffectHndl, SHADOW_EFFECT_SCALE);
				CSoundManager::Play(CSoundManager::eSoundID::SE_PLSHADOW);
			}
		}
	}

	//�e���|�[�g�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsPush(CInputManager::eInputType::TELEPORT) == true) {
		//�e���|�[�g��Ԃ�
		_State = ePlayerState::TELEPORT;
		_TeleportPos = _Pos;
		CSoundManager::Play(CSoundManager::eSoundID::SE_PLCHANGE);
	}
	//�U���L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsPush(CInputManager::eInputType::SELECT) == true) {
		//�U�����N�G�X�g
		CPlayerAttack::GetInstance()->Request();
	}
	//�e�G���A�L�[�܂��̓{�^���������ꑱ�����Ă��邩
	if (CInputManager::IsKeep(CInputManager::eInputType::FALL) == true)
		CPlayerAttack::GetInstance()->SetHold(true);
	else
		CPlayerAttack::GetInstance()->SetHold(false);

	//�e�G���A�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsRelease(CInputManager::eInputType::FALL) && _IsGround) {
		//�e�G���A���N�G�X�g
		CPlayerAttack::GetInstance()->AreaRequest(CInputManager::IsDown(CInputManager::eInputType::JUMP));
	}

	if (_OldState == ePlayerState::CLIMB) {
		_Move._Z -= PLAYER_RAD;
		_Move._Y += PLAYER_RAD;
	}

	_OldState = ePlayerState::NORMAL;
}
//�e��Ԃ̃A�N�V�����֐�
void CPlayer::ShadowAct() {
	//�e�G���A�L�[�܂��̓{�^���������ꑱ�����Ă��邩
	if (CInputManager::IsKeep(CInputManager::eInputType::FALL) == true)
		CPlayerAttack::GetInstance()->SetHold(true);
	else
		CPlayerAttack::GetInstance()->SetHold(false);

	//�e�L�[�܂��̓{�^���������ꂽ�������͉e�G���A���痣�ꂽ��
	if (CInputManager::IsRelease(CInputManager::eInputType::SHADOW) == true || _HitArea == false) {
		//�ʏ��Ԃ�
		_State = ePlayerState::NORMAL;
		_Rot._X = 0.f;
	}
	else if (_IsClimb == true) {
		//�Ǐ��\�Ȃ�Ǐ���Ԃ�
		_State = ePlayerState::CLIMB;
	}
	else if (_IsGround == false) {
		//�󒆂ɂ���ꍇ�͒ʏ��Ԃ�
		_State = ePlayerState::NORMAL;
	}

	if (_OldState == ePlayerState::CLIMB) {
		_Move._Z -= PLAYER_RAD;
		_Move._Y += PLAYER_RAD;
	}

	_OldState = ePlayerState::SHADOW;
}
//�W�����v��Ԃ̃A�N�V�����֐�
void CPlayer::JumpAct() {
	_State = ePlayerState::NORMAL;
	_OldState = ePlayerState::JUMP;
}
//�e���|�[�g��Ԃ̃A�N�V�����֐�
void CPlayer::TeleportAct() {
	//�W�����v�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsDown(CInputManager::eInputType::JUMP) == true) {
		//�㏸
		_TeleportMove._Y += _TeleportSpd;
	}
	//���~�L�[�܂��̓{�^���������ꂽ��
	else if (CInputManager::IsDown(CInputManager::eInputType::FALL) == true) {
		//���~
		_TeleportMove._Y -= _TeleportSpd;
	}

	//�I���L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsPush(CInputManager::eInputType::SELECT) == true
		&& _Teleport == true) {
		//�e���|�[�g�\�Ȃ�e���|�[�g����
		_State = ePlayerState::NORMAL;
		_Pos = _TeleportTargetPos;
		CSoundManager::Play(CSoundManager::eSoundID::SE_PLTELEPORT);
	}
	//�e���|�[�g�L�[�܂��̓{�^���������ꂽ��
	if (CInputManager::IsPush(CInputManager::eInputType::TELEPORT) == true) {
		//�ʏ��Ԃ�
		_State = ePlayerState::NORMAL;
		_TeleportPos = _Pos;
		CSoundManager::Play(CSoundManager::eSoundID::SE_PLCHANGE);
	}

	_OldState = ePlayerState::TELEPORT;
}
//�ǂ̂ڂ��Ԃ̃A�N�V�����֐�
void CPlayer::ClimbAct() {
	//�e�L�[�܂��̓{�^���������ꂽ�������͉e�G���A���痣�ꂽ��
	if (CInputManager::IsRelease(CInputManager::eInputType::SHADOW) == true || _HitArea == false) {
		_Move._Z += _ShadowSpd;
		_State = ePlayerState::NORMAL;
		_Rot._X = 0.f;
	}
	//�e�L�[�܂��̓{�^���������ꂽ���Ǐ��s�\��
	if (CInputManager::IsDown(CInputManager::eInputType::SHADOW) == true &&
		_IsClimb == false && _IsGround == true && _HitArea == true) {
		//�e��Ԃ�
		_State = ePlayerState::SHADOW;
	}
	//�e�L�[�܂��̓{�^���������ꂽ���Ǐ��s�\���󒆂�
	if (CInputManager::IsDown(CInputManager::eInputType::SHADOW) == true &&
		_IsClimb == false && _IsGround == false) {
		//�ʏ��ԂցA�����㏸����
		_State = ePlayerState::NORMAL;
		_Gravity = PLAYER_JUMP_POWER;
	}

	_OldState = ePlayerState::CLIMB;
}

//�e���|�[�g�֐�
void CPlayer::TeleportCalc(Vector3D shadow_pos) {
	_Teleport = true;
	_TeleportTargetPos( shadow_pos._X, shadow_pos._Y, shadow_pos._Z );
}

//�q�b�g�֐�
void CPlayer::DeathCalc(){
	//�v���C���[���S�t���O�I���E���S�G�t�F�N�g���s
	_IsDeath = true;
	_DeathEffectHndl = CEffekseerCtrl::Request(CEffekseerCtrl::_ID[(int)CEffekseerCtrl::eEffectID::DEATH], _Pos, false);
	CEffekseerCtrl::SetScale(_DeathEffectHndl, EFFECT_SCALE);
	CEffekseerCtrl::SetRot(_DeathEffectHndl, _Rot);
}

//���X�|�[���֐�
void CPlayer::ReSpawn() {
	_Pos = _SavePos;
	_TeleportPos = Vector3D::ZeroVec();
	_TeleportTargetPos = Vector3D::ZeroVec();
	_Move = Vector3D::ZeroVec();
	_TeleportMove = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Gravity = 0.0f;
	_Teleport = false;
	_IsClimb = false;
	_IsGround = false;
	_State = ePlayerState::NORMAL;
	_IsDeath = false;

	CPlayerAttack::GetInstance()->AllReset();
}

//�ړ��֐�
void CPlayer::Move(float rot_y) {
	if (_State == ePlayerState::NORMAL)
		_Move._Z -= CInputManager::GetLInputY() * _Spd;
	else if (_State == ePlayerState::SHADOW)
		_Move._Z -= CInputManager::GetLInputY() * _ShadowSpd;
	else if (_State == ePlayerState::TELEPORT)
		_TeleportMove._Z -= CInputManager::GetLInputY() * _TeleportSpd;

	if (CInputManager::GetLInputX() != 0.f) {
		if (_State == ePlayerState::NORMAL)
			_Move._X -= CInputManager::GetLInputX() * _Spd;
		else if (_State == ePlayerState::SHADOW  || _State == ePlayerState::CLIMB)
			_Move._X -= CInputManager::GetLInputX() * _ShadowSpd;
		else if (_State == ePlayerState::TELEPORT)
			_TeleportMove._X -= CInputManager::GetLInputX() * _TeleportSpd;
	}

	if (_State == ePlayerState::CLIMB) {
		_Move._Y += CInputManager::GetLInputY() * _ShadowSpd;
	}

	if (_State != ePlayerState::TELEPORT) {
		//���_�ɕ��s�ړ�����s����쐬
		MyMatrix playerMoveOriginMat = MyMatrix::GetTranslateMat(-_Pos._X, -_Pos._Y, -_Pos._Z);
		//�v���C���[��Y����]�s����쐬
		MyMatrix playerRotYMat = MyMatrix::GetYawMatrix(rot_y);
		//���s�ړ�����s����쐬
		MyMatrix playerMoveMat = MyMatrix::GetTranslateMat(_Move);
		//���̈ʒu�ɖ߂����s�ړ�����s����쐬
		MyMatrix playerReturnMat = MyMatrix::GetTranslateMat(_Pos);

		//�e�s�������
		MyMatrix playerCompoundMat = playerReturnMat * playerRotYMat;
		playerCompoundMat *= playerMoveMat;
		playerCompoundMat *= playerMoveOriginMat;

		//���W�ɍs����|���ăv���C���[�̍��W���Z�o
		_Pos = playerCompoundMat * _Pos;
	}
	else if (_State == ePlayerState::TELEPORT) {
		//���_�ɕ��s�ړ�����s����쐬
		MyMatrix teleportMoveOriginMat = MyMatrix::GetTranslateMat(-_TeleportPos._X, -_TeleportPos._Y, -_TeleportPos._Z);
		//�e���|�[�g��Y����]�s����쐬
		MyMatrix teleportRotYMat = MyMatrix::GetYawMatrix(rot_y);
		//���s�ړ�����s����쐬
		MyMatrix teleportMoveMat = MyMatrix::GetTranslateMat(_TeleportMove);
		//���̈ʒu�ɖ߂����s�ړ�����s����쐬
		MyMatrix teleportReturnMat = MyMatrix::GetTranslateMat(_TeleportPos);

		//�e�s�������
		MyMatrix teleportCompoundMat = teleportReturnMat * teleportRotYMat;
		teleportCompoundMat *= teleportMoveMat;
		teleportCompoundMat *= teleportMoveOriginMat;

		//���W�ɍs����|���ăe���|�[�g�̍��W���Z�o
		_TeleportPos = teleportCompoundMat * _TeleportPos;

		Vector3D playerToTeleportVec = _Pos.Create(_TeleportPos);
		float playerToTeleportLong = playerToTeleportVec.Long();
		if (playerToTeleportLong >= TELEPORT_MOVE_MAX) {
			playerToTeleportVec.Normalize();
			playerToTeleportVec = playerToTeleportVec * TELEPORT_MOVE_MAX;
			_TeleportPos = _Pos + playerToTeleportVec;
		}
	}
}
