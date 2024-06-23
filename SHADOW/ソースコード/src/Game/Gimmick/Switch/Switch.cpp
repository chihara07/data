#include "Switch.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D SWITCH_SCALE(0.1f, 0.1f, 0.1f);		//�X�C�b�`�g�嗦
constexpr Vector2D NEED_COIN_GRAPH_POS(0.5f, 0.5f);		//�K�v�R�C�������W
constexpr float SWITCH_RAD = 10.0f;						//�X�C�b�`���a
constexpr float NEED_COIN_GRAPH_HEIGHT = 20.f;			//�K�v�R�C�����̍���
constexpr float NEED_COIN_GRAPH_SIZE = 15.f;			//�K�v�R�C�����̃T�C�Y

//�R���X�g���N�^�E�f�X�g���N�^
CSwitch::CSwitch() {
	Init();
}
CSwitch::~CSwitch() {
	Fin();
}

//������
void CSwitch::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = SWITCH_SCALE;
	_Rad = SWITCH_RAD;
	_Hndl = -1;
	for(int need_coin_index = 0; need_coin_index < NEED_COIN_MAX_NUM; need_coin_index++)
		_CoinHndl[need_coin_index] = -1;
	_PressedHndl = -1;
	_IsPressed = false;
	_IsHit = false;
	_NeedCoinNum = 0;
}

//���[�h
void CSwitch::Load() {
	//���f���ǂݍ���
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SWITCH)); }
	if (_PressedHndl == -1){ _PressedHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::SWITCH2)); }
	if (_CoinHndl[0] == -1) _CoinHndl[0] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN1);
	if (_CoinHndl[1] == -1) _CoinHndl[1] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN2);
	if (_CoinHndl[2] == -1) _CoinHndl[2] = CHndlManager::GetInstance()->GetHndl(PATH_TYPE::COIN3);
}

//�Z�b�g
void CSwitch::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_PressedHndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_PressedHndl, _Rot);
	MV1SetPosition(_PressedHndl, _Pos);
}

//���C������
void CSwitch::Step() {
	_IsHit = false;
}

//�`��
void CSwitch::Draw() {
	//�X�C�b�`��������Ă��Ȃ��Ȃ�
	if (_IsPressed == false){ MV1DrawModel(_Hndl); }
	//�X�C�b�`��������Ă���Ȃ�
	else { MV1DrawModel(_PressedHndl); }	

	//�v���C���[���擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (_IsPressed == false && _IsHit == true) {
		DrawBillboard3D(VGet(cPlayer->GetPos()._X, cPlayer->GetPos()._Y + NEED_COIN_GRAPH_HEIGHT, cPlayer->GetPos()._Z),
			NEED_COIN_GRAPH_POS._X, NEED_COIN_GRAPH_POS._Y, NEED_COIN_GRAPH_SIZE, 0.f, _CoinHndl[_NeedCoinNum - 1], true);
	}
}

//�X�V����
void CSwitch::Update() {
	//��]�p�x�A���W�Z�b�g
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_PressedHndl, _Rot);
	MV1SetPosition(_PressedHndl, _Pos);
}

//�I��
void CSwitch::Fin() {
	//���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_PressedHndl != -1) { MV1DeleteModel(_PressedHndl); _PressedHndl = -1; }
}

//�����ꂽ�֐�
void CSwitch::PressedCalc() {
	//�����ꂽ���t���O�I��
	_IsPressed = true;
}

//�K�v�R�C���\��
void CSwitch::HitCalc() {
	_IsHit = true;
}
