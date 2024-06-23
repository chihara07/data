#include "Teleport.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/Tutorial/Tutorial.h"

constexpr float SHADOW_RAD = 15.0f;							//�e�̔��a
constexpr float SHADOW_HEIGHT = 9.0f;						//�e�����ɉ�����p�̍���

//�R���X�g���N�^�E�f�X�g���N�^
CTeleportShadow::CTeleportShadow() {
	_Hndl = -1;
	_SelectHndl = -1;
	_Rad = SHADOW_RAD;
	_IsActive = false;
	_CheckTeleport = false;
}
CTeleportShadow::~CTeleportShadow() {
	Fin();
}

//������
void CTeleportShadow::Init() {
	_Pos = Vector3D::ZeroVec();
	_SelectingPos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Rad = SHADOW_RAD;
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
	_SelectHndl = -1;
	_IsActive = false;
	_CheckTeleport = false;
	_cSwitch = nullptr;
}

//���[�h
void CTeleportShadow::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SHADOW)); }
	if (_SelectHndl == -1) { _SelectHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SHADOW2)); }
}

//�Z�b�g
void CTeleportShadow::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_SelectHndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, { _Pos._X, _Pos._Y - SHADOW_HEIGHT, _Pos._Z });
	MV1SetRotationXYZ(_SelectHndl, _Rot);
	MV1SetPosition(_SelectHndl, { _SelectingPos._X, _SelectingPos._Y - SHADOW_HEIGHT, _SelectingPos._Z });
}

//���C������
void CTeleportShadow::Step() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//��U�v���C���[�̃e���|�[�g�t���O�I�t
	cPlayer->SetTeleport(false);
	//��U�e���|�[�g�t���O�I�t
	_CheckTeleport = false;

	//�X�C�b�`��null�łȂ����
	if (_cSwitch != nullptr) {
		//�X�C�b�`��������Ă���Ȃ琶���t���O�I��
		_IsActive = _cSwitch->GetPressed();
		if (StageID == eStageID::STAGE_0)
			CTutorial::GetInstance()->SetPressed(_cSwitch->GetPressed());
	}
}

//�`��
void CTeleportShadow::Draw() {
	//�v���C���[���擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_IsActive == true) {
		if (_CheckTeleport == false) {
			//�e���|�[�g�s���f���`��
			MV1DrawModel(_Hndl);
		}
		else if (_CheckTeleport == true) {
			//�e���|�[�g�\���f���`��
			MV1DrawModel(_SelectHndl);
		}
	}
}

//�X�V����
void CTeleportShadow::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, { _Pos._X, _Pos._Y - SHADOW_HEIGHT, _Pos._Z });
	MV1SetRotationXYZ(_SelectHndl, _Rot);
	MV1SetPosition(_SelectHndl, { _SelectingPos._X, _SelectingPos._Y - SHADOW_HEIGHT, _SelectingPos._Z });
}

//�I��
void CTeleportShadow::Fin() {
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_SelectHndl != -1) { MV1DeleteModel(_SelectHndl); _SelectHndl = -1; }
}

//�q�b�g�֐�
void CTeleportShadow::HitCalc() {
	_CheckTeleport = true;
	_SelectingPos = _Pos;
}
