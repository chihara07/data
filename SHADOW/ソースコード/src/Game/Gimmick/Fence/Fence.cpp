#include "Fence.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D FENCE_COLLISION_SCALE( 0.5f, 0.5f, 0.7f );			//�t�F���X�����蔻��g�嗦

//�R���X�g���N�^�E�f�X�g���N�^
CFence::CFence() {
	_Hndl = -1;
	_CollisionHndl = -1;
}
CFence::~CFence() {
	Fin();
}

//������
void CFence::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_CollisionScale = FENCE_COLLISION_SCALE;
	_Hndl = -1;
	_CollisionHndl = -1;
}

//���[�h
void CFence::Load() {
	//���f���ǂݍ���
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FENCE)); }
	if (_CollisionHndl == -1){ _CollisionHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FENCE_COL)); }
}

//�Z�b�g
void CFence::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_CollisionHndl, _CollisionScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(_CollisionHndl, -1, TRUE);

	//�R���W�������\�z
	MV1SetupCollInfo(_CollisionHndl);
}

//���C������
void CFence::Step() {
	
}

//�`��
void CFence::Draw() {
	//���f���`��
	MV1DrawModel(_Hndl);
}

//�X�V����
void CFence::Update() {
	//��]�p�x�A���W�Z�b�g
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// �|���S�������X�V����
	MV1RefreshReferenceMesh(_CollisionHndl, -1, TRUE);
}

//�I��
void CFence::Fin() {
	//�R���W�������j��
	MV1TerminateCollInfo(_CollisionHndl);
	//���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_CollisionHndl != -1) { MV1DeleteModel(_CollisionHndl); _CollisionHndl = -1; }
}

//�q�b�g�֐�
void CFence::HitCalc() {
}
