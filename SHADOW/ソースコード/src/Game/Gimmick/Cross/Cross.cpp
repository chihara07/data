#include "Cross.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Player/Player.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/CollisionManager/CollisionManager.h"

//�R���X�g���N�^�E�f�X�g���N�^
CCross::CCross() {
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
	_Hndl = -1;
	_CollisionHndl = -1;
}
CCross::~CCross() {
	Fin();
}

//������
void CCross::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
}

//���[�h
void CCross::Load() {
	//���f���ǂݍ���
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::CROSS)); }
	if (_CollisionHndl == -1) { _CollisionHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::CROSS_COL)); }
}

//�Z�b�g
void CCross::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_CollisionHndl, _Scale);
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
void CCross::Step() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//��]������
	_Rot._Y += _Spd;
	//�͈͎w��
	_Rot._Y = MyLib::UnwindRadians(_Rot._Y);
	//�v���C���[������Ă�����ꏏ�ɉ�]����
	if (CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), _CollisionHndl))
	{
		//���_�ɕ��s�ړ�������s��
		MyMatrix moveOriginMat = MyMatrix::GetTranslateMat(-_Pos);
		//��]���x����Y����]�s��
		MyMatrix rotYMat = MyMatrix::GetYawMatrix(_Spd);
		//���̋������ړ������镽�s�ړ��s��
		MyMatrix moveDistanceMat = MyMatrix::GetTranslateMat(Vector3D::VGet(cPlayer->GetPos()._X - _Pos._X, cPlayer->GetPos()._Y, cPlayer->GetPos()._Z - _Pos._Z));
		//���Ƃ̈ʒu�ɖ߂����s�ړ��s��
		MyMatrix returnMat = MyMatrix::GetTranslateMat(_Pos);

		//�e�s�������
		MyMatrix cameraCompoundMat = returnMat * rotYMat;
		cameraCompoundMat *= moveDistanceMat;
		cameraCompoundMat *= moveOriginMat;

		//���������̂��v���C���[���W�ɑ��
		cPlayer->SetPos(cameraCompoundMat * _Pos);
	}
}

//�`��
void CCross::Draw() {
	MV1DrawModel(_Hndl);
}

//�X�V����
void CCross::Update() {
	//��]�p�x�A���W�Z�b�g
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// �|���S�������X�V����
	MV1RefreshReferenceMesh(_CollisionHndl, -1, TRUE);
	//�R���W�������\�z
	MV1SetupCollInfo(_CollisionHndl);
}

//�I��
void CCross::Fin() {
	//�R���W�������j��
	MV1TerminateCollInfo(_CollisionHndl);
	//���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_CollisionHndl != -1) { MV1DeleteModel(_CollisionHndl); _CollisionHndl = -1; }
}

//�q�b�g�֐�
void CCross::HitCalc() {
}
