#include "PlayerAttack.h"
#include "../../Library/Color.h"
#include "../../Library/Common.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Sound/SoundManager.h"

constexpr Vector3D ATTACK_SCALE(0.1f);					//�U���g�嗦
constexpr Vector3D AREA_SCALE(0.2f);					//�e�G���A�g�嗦
constexpr Vector3D ATTACK_DISTANCE(10.f, 0.f, 20.f);	//�U������
constexpr float ATTACK_RAD = 13.f;						//�U�����a
constexpr float AREA_ENERGY = 60.f;						//�e�G���A��{�G�l���M�[��
constexpr float AREA_RAD = 20.f;						//�e�G���A���a
constexpr float RECOVERY_FAST = 3.f;					//�����񕜗�
constexpr float RECOVERY_SLOW = 0.5f;					//�x���񕜗�
constexpr float HOLD_COUNT_INCREASE = 0.0666666666f;	//���������ԑ�����
constexpr float HOLD_COUNT_MAX = 5.f;					//�ő咷��������
constexpr int DURATION = 25;							//��������
constexpr int ATTACK_INTERVAL = 60;						//�U���C���^�[�o��

CPlayerAttack* CPlayerAttack::_Instance = nullptr;

CPlayerAttack* CPlayerAttack::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CPlayerAttack;
	}

	return _Instance;
}

void CPlayerAttack::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//�R���X�g���N�^�E�f�X�g���N�^
CPlayerAttack::CPlayerAttack() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = 0;
		_AreaIsActive[area_index] = false;
		_AreaHndl[area_index] = -1;
	}
	_Scale = Vector3D::ZeroVec();
	_Rad = 0;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_Hndl = -1;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = 0.f;
	_EnergyCnt = 0;
	_IsHold = false;
	_IsCharge = false;
}
CPlayerAttack::~CPlayerAttack() {

}

//������
void CPlayerAttack::Init() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = AREA_RAD;
		_AreaIsActive[area_index] = false;
		_AreaHndl[area_index] = -1;
	}
	_Scale = ATTACK_SCALE;
	_Rad = ATTACK_RAD;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_Hndl = -1;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = AREA_ENERGY;
	_EnergyCnt = AREA_ENERGY_MAX;
	_IsHold = false;
	_IsCharge = false;
}

//���[�h
void CPlayerAttack::Load() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaHndl[area_index] == -1) {
			_AreaHndl[area_index] = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_AREA));
		}
	}

	if (_Hndl == -1) { 
		_Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_ATTACK));
	}
}

//�Z�b�g
void CPlayerAttack::Set() {
	//�g�嗦�A��]�p�x�A���W�Z�b�g
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		//�䗦�Z�b�g
		MV1SetScale(_AreaHndl[area_index], _AreaScale[area_index]);
		MV1SetPosition(_AreaHndl[area_index], _AreaPos[area_index]);
	}

	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, cPlayer->GetRot());
	MV1SetPosition(_Hndl, ((_Pos[0] + _Pos[1]) / 2));
}

//���C������
void CPlayerAttack::Step() {
	if (_IsActive == true) {
		//���_�ɕ��s�ړ�����s����쐬
		MyMatrix OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
		//�v���C���[��Y����]�s����쐬
		MyMatrix RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
		//���s�ړ�����s����쐬
		MyMatrix MoveMat[ATTACK_NUM];
		MoveMat[0] = MyMatrix::GetTranslateMat(ATTACK_DISTANCE._X, 0.f, -ATTACK_DISTANCE._Z);
		MoveMat[1] = MyMatrix::GetTranslateMat(-ATTACK_DISTANCE._X, 0.f, -ATTACK_DISTANCE._Z);
		//���̈ʒu�ɖ߂����s�ړ�����s����쐬
		MyMatrix ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

		//�e�s�������
		MyMatrix playerCompoundMat[ATTACK_NUM];
		for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
			playerCompoundMat[attack_index] = ReturnMat * RotYMat;
			playerCompoundMat[attack_index] *= MoveMat[attack_index];
			playerCompoundMat[attack_index] *= OriginMat;

			//���W�ɍs����|���čU���̍��W���Z�o
			_Pos[attack_index] = playerCompoundMat[attack_index] * cPlayer->GetPos();
		}

		_Cnt++;
	}

	//���ԂɂȂ����琶���t���O�I�t
	if (_Cnt > DURATION && _IsActive == true) {
		_IsActive = false;
		_Interval = ATTACK_INTERVAL;
	}

	//�����t���O�I�t�Ȃ�C���^�[�o�����ւ炷
	if (_Interval > 0 && _IsActive == false) {
		_Interval--;
	}

	//�v���C���[�̏�Ԃɂ��킹�ăG�l���M�[��
	if (cPlayer->GetState() == CPlayer::ePlayerState::SHADOW ||
		cPlayer->GetState() == CPlayer::ePlayerState::CLIMB)
		_EnergyCnt += RECOVERY_FAST;
	else
		_EnergyCnt += RECOVERY_SLOW;

	//�G�l���M�[���
	if (_EnergyCnt >= AREA_ENERGY_MAX) {
		_EnergyCnt = AREA_ENERGY_MAX;
	}

	//���������ԏ���
	if (_IsHold == true) {
		_HoldCnt += HOLD_COUNT_INCREASE;

		if (_HoldCnt > HOLD_COUNT_MAX)
			_HoldCnt = HOLD_COUNT_MAX;
	}
	else {
		_HoldCnt = 1;
		_IsCharge = false;
	}
}

//�`��
void CPlayerAttack::Draw() {
	if (_IsActive == true) {
		MV1DrawModel(_Hndl);
	}

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaIsActive[area_index] == true) {
			MV1DrawModel(_AreaHndl[area_index]);
			//DrawSphere3D(_AreaPos[area_index], _AreaRad[area_index], 10, COLOR::RED, COLOR::RED, false);
		}
	}
}

//�I��
void CPlayerAttack::Fin() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaHndl[area_index] != -1) { MV1DeleteModel(_AreaHndl[area_index]); _AreaHndl[area_index] = -1; }
	}
}

//�X�V����
void CPlayerAttack::Update() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		MV1SetPosition(_AreaHndl[area_index], _AreaPos[area_index]);
		MV1SetScale(_AreaHndl[area_index], _AreaScale[area_index]);
	}
	MV1SetRotationXYZ(_Hndl, cPlayer->GetRot());
	MV1SetPosition(_Hndl, ((_Pos[0] + _Pos[1]) / 2));
}

//���N�G�X�g
void CPlayerAttack::Request() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		if (_Interval == 0 && _IsActive == false) {
			_IsActive = true;
			_Cnt = 0;
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLATTACK);

			break;
		}
	}
}

//�e�G���A���N�G�X�g
void CPlayerAttack::AreaRequest(bool f) {
	//���ׂĎg�p���Ȃ炷�ׂăI�t
	if (_AreaIsActive[0] == true && _AreaIsActive[1] == true && _AreaIsActive[2] == true) {
		for (int area_index = 0; area_index < AREA_NUM; area_index++) {
			_AreaIsActive[area_index] = false;
			_AreaScale[area_index] = AREA_SCALE;
			_AreaRad[area_index] = AREA_RAD;
		}

		return;
	}

	if (_EnergyCnt < _Energy)
		return;

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaIsActive[area_index] == false) {
			_AreaIsActive[area_index] = true;
			if (_Energy * _HoldCnt > _EnergyCnt) {
				_AreaScale[area_index] *= _EnergyCnt / _Energy;
				_AreaRad[area_index] *= _EnergyCnt / _Energy;
				_EnergyCnt = 0.f;
			}
			else {
				_AreaScale[area_index] *= _HoldCnt;
				_AreaRad[area_index] *= _HoldCnt;
				_EnergyCnt -= _Energy * _HoldCnt;
			}

			//���_�ɕ��s�ړ�����s����쐬
			MyMatrix OriginMat;
			//�v���C���[��Y����]�s����쐬
			MyMatrix RotYMat;
			//���s�ړ�����s����쐬
			MyMatrix MoveMat;
			//���̈ʒu�ɖ߂����s�ړ�����s����쐬
			MyMatrix ReturnMat;

			//�t���O��true�Ȃ������ɏo��
			if (f == true) {
				//���_�ɕ��s�ړ�����s����쐬
				OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
				//�v���C���[��Y����]�s����쐬
				RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
				//���s�ړ�����s����쐬
				MoveMat = MyMatrix::GetTranslateMat(0.f, (cPlayer->GetRad() + _AreaRad[area_index]), 0.f);
				//���̈ʒu�ɖ߂����s�ړ�����s����쐬
				ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

				//�e�s�������
				MyMatrix playerCompoundMat;
				playerCompoundMat = ReturnMat * RotYMat;
				playerCompoundMat *= MoveMat;
				playerCompoundMat *= OriginMat;

				//���W�ɍs����|���ĉe�G���A�̍��W���Z�o
				_AreaPos[area_index] = playerCompoundMat * cPlayer->GetPos();
			}
			//false�Ȃ琳�ʂɏo��
			else {
				//���_�ɕ��s�ړ�����s����쐬
				OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
				//�v���C���[��Y����]�s����쐬
				RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
				//���s�ړ�����s����쐬
				MoveMat = MyMatrix::GetTranslateMat(0.f, 0.f, - _AreaRad[area_index]);
				//���̈ʒu�ɖ߂����s�ړ�����s����쐬
				ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

				//�e�s�������
				MyMatrix playerCompoundMat;
				playerCompoundMat = ReturnMat * RotYMat;
				playerCompoundMat *= MoveMat;
				playerCompoundMat *= OriginMat;

				//���W�ɍs����|���ăv���C���[�̍��W���Z�o
				_AreaPos[area_index] = playerCompoundMat * cPlayer->GetPos();
			}

			return;
		}
	}
}

//�w�肵���e�G���A���Z�b�g
void CPlayerAttack::AreaReset(int id) {
	_AreaIsActive[id] = false;
	_AreaScale[id] = AREA_SCALE;
	_AreaRad[id] = AREA_RAD;
}

//���Z�b�g
void CPlayerAttack::AllReset() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = AREA_RAD;
		_AreaIsActive[area_index] = false;
	}
	_Scale = Vector3D::ZeroVec();
	_Rad = ATTACK_RAD;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = AREA_ENERGY;
	_EnergyCnt = AREA_ENERGY_MAX;
	_IsHold = false;
	_IsCharge = false;
}
