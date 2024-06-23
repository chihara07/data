#include "Coin.h"
#include "../CollisionManager/CollisionManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"

constexpr Vector3D COIN_SCALE(0.1f, 0.1f, 0.1f);		//�R�C���g�嗦
constexpr float COIN_RAD = 10.f;						//�R�C�����a
constexpr float COIN_SPD = 0.1f;						//�R�C����]���x

//�R���X�g���N�^�E�f�X�g���N�^
CCoin::CCoin() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Hndl = -1;
	_Rad = COIN_RAD;
	_IsActive = false;
	_CoinType = eCoinType::NONE;
}

CCoin::~CCoin() {

}

//������
void CCoin::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Hndl = -1;
	_Rad = COIN_RAD;
	_Scale = COIN_SCALE;
	_IsActive = false;
	_CoinType = eCoinType::NONE;
}

//���[�h
void CCoin::Load(int coin_hndl) {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(coin_hndl); }
}

//�Z�b�g
void CCoin::Set() {
	//�䗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//���C������
void CCoin::Step() {
	if (_IsActive == true) {
		_Rot._Y += COIN_SPD;
	}
}
//�`��
void CCoin::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
}

//�I��
void CCoin::Fin() {
	//�R�s�[���f���j��
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�����蔻��
void CCoin::Collision() {
	_IsActive = CCOllisionManager::CheckHitPlayerToCoin(_Pos, _Rad, _IsActive);
}

//�X�V����
void CCoin::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}
