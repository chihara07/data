#include "goal.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

//�R���X�g���N�^�E�f�X�g���N�^
CGoal::CGoal() {
	_Hndl = -1;
}
CGoal::~CGoal() {
	Fin();
}

//������
void CGoal::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
}

//���[�h
void CGoal::Load() {
	//���f���ǂݍ���
	if (_Hndl == -1){
		_Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::GOAL));
	}
}

//�Z�b�g
void CGoal::Set() {
	//�䗦�E���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetPosition(_Hndl, _Pos);
}

//���C������
void CGoal::Step() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�����蔻�茋��
	MV1_COLL_RESULT_POLY_DIM res;
	//�����蔻�茋�ʊi�[
	res = MV1CollCheck_Sphere(_Hndl, -1, cPlayer->GetPos(), cPlayer->GetRad());

	//�q�b�g���Ă���Ȃ�
	if (res.HitNum > 0) {
		cPlayer->SetClear(true);
	}

	//�R���W�����f�[�^�j��
	MV1CollResultPolyDimTerminate(res);
}

//�`��
void CGoal::Draw() {
	MV1DrawModel(_Hndl);
}

//�X�V����
void CGoal::Update() {
	//��]�p�x�A���W�Z�b�g
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//�I��
void CGoal::Fin() {
	//���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�q�b�g�֐�
void CGoal::HitCalc() {
}
