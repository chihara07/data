#include "Map.h"
#include <math.h>
#include "../../Library/Math/Math.h"
#include "../../Library/Common.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D FIELD_START_POS( 0.0f, -30.0f, 250.0f );	//�t�B�[���h�������W
constexpr Vector3D FIELD_SCALE( 1.f, 1.f, 1.f );			//�t�B�[���h�䗦
constexpr Vector3D SKY_START_POS(0.0f, 0.0f, -2000.0f);		//�t�B�[���h�������W
constexpr Vector3D SKY_SCALE(40.f, 40.f, 40.f);				//�t�B�[���h�䗦
constexpr float SKY_SPD = 0.0003f;							//�t�B�[���h��]���x
//�t�B�[���h������]�p�x
constexpr Vector3D FIELD_START_ROT( 0.0f, (180.0f * DX_PI_F) / 180.0f, 0.0f );
//�V���̃��f���p�X
constexpr char SKY_PATH[] = "data/Sky/sky.mv1";

//�R���X�g���N�^
CBg::CBg() {
	Init();
}

//�f�X�g���N�^
CBg::~CBg() {
	Fin();
}

//����������
void CBg::Init() {
	_Pos = FIELD_START_POS;			//�t�B�[���h���W������
	_Scale = FIELD_SCALE;			//�t�B�[���h�䗦������
	_Rot = FIELD_START_ROT;			//�t�B�[���h��]�p�x������
	_Hndl = -1;						//�t�B�[���h�摜�n���h��������
	_ColHndl = -1;
	_SkyHndl = -1;					//�V���摜�n���h��
	_SkyPos = SKY_START_POS;		//�V�����W
	_SkyScale = SKY_SCALE;			//�V���䗦
	_SkyRot = Vector3D::ZeroVec();	//�V����]�p�x
}

//���[�h����
void CBg::Load() {
	//�X�e�[�WID���ƂɃX�e�[�W���f�����R�s�[
	if (StageID == eStageID::STAGE_0) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP0_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP0_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_1) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP1_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP1_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_2) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP2_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP2_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_3) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP3_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP3_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_4) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP4_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP4_COL_PATH)); }
	}
	//�V�����f�����[�h
	if (_SkyHndl == -1) { _SkyHndl = MV1LoadModel(SKY_PATH); }
}

//�Z�b�g
void CBg::Set() {
	//�����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(_Hndl, -1, TRUE);

	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetPosition(_Hndl, _Pos);
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_ColHndl, _Pos);
	MV1SetScale(_ColHndl, _Scale);
	MV1SetRotationXYZ(_ColHndl, _Rot);
	MV1SetPosition(_SkyHndl, _Pos);
	MV1SetScale(_SkyHndl, _SkyScale);
	MV1SetRotationXYZ(_SkyHndl, _SkyRot);

	//�R���W�������\�z
	MV1SetupCollInfo(_ColHndl);
}

//�I������
void CBg::Fin() {
	//�R���W�������j��
	MV1TerminateCollInfo(_ColHndl);
	//�t�B�[���h�摜�j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	//�V���摜�j��
	if (_SkyHndl != -1) { MV1DeleteModel(_SkyHndl); _SkyHndl = -1; }
}

//���C������
void CBg::Step() {
	//�V����]����
	_SkyRot._Y += SKY_SPD;

	_SkyRot._Y = MyLib::UnwindDegrees(_SkyRot._Y);
}

//�`�揈��
void CBg::Draw() {
	MV1DrawModel(_Hndl);			//�t�B�[���h�`��
	MV1DrawModel(_SkyHndl);			//�V���`��
}

//�A�b�v�f�[�g����
void CBg::Update() {
	MV1SetPosition(_Hndl, _Pos);				//���W�Z�b�g
	MV1SetPosition(_ColHndl, _Pos);				//���W�Z�b�g
	MV1SetPosition(_SkyHndl, _SkyPos);			//���W�Z�b�g
	MV1SetRotationXYZ(_SkyHndl, _SkyRot);		//�V����]�p�x�Z�b�g

	// �|���S�������X�V����
	MV1RefreshReferenceMesh(_ColHndl, -1, TRUE);
}
