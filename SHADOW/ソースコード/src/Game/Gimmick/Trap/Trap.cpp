#include "Trap.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr float TRAP_RAD = 20.0f;						//�e�̔��a

//�R���X�g���N�^�E�f�X�g���N�^
CTrap::CTrap() {
	_Hndl = -1;
	_Rad = TRAP_RAD;
}
CTrap::~CTrap() {
	Fin();
}

//������
void CTrap::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rad = TRAP_RAD;
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
}

//���[�h
void CTrap::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::TRAP)); }
}

//�Z�b�g
void CTrap::Set() {
	//�g�嗦�Z�b�g�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetPosition(_Hndl, _Pos);
}

//���C������
void CTrap::Step() {
}

//�`��
void CTrap::Draw() {
	MV1DrawModel(_Hndl);
}

//�X�V����
void CTrap::Update() {
	MV1SetPosition(_Hndl, _Pos);
}

//�I��
void CTrap::Fin() {
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}
