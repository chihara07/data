#include "Camera.h"
#include <math.h>
#include "../../Library/Input/InputManager.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Common.h"
#include "../Player/Player.h"

constexpr Vector3D CAMERA_START_POS( 0.0f, 10.0f, 100.0f );		//�J���������ʒu
constexpr Vector3D CAMERA_CLIMB_POS(0.0f, 10.0f, 150.0f);		//�J���������ʒu
constexpr Vector3D TARGET_START_POS( 0.0f, 0.0f, 0.0f );		//�J���������_�����ʒu
constexpr Vector3D CAMERA_START_UP( 0.0f, 1.0f, 0.0f );			//�J��������������ʒu
constexpr Vector3D CAMERA_START_ROT(-0.4f, 0.f, 0.f);			//�J����������]�p�x
constexpr Vector2D CAMERA_LIMIT_ROT(80.f, 360.f);			//�J����������]�p�x
constexpr float CAMERA_SPD = 0.03f;								//�J�������_�ړ����x

CPlayerCamera* CPlayerCamera::_Instance = nullptr;

CPlayerCamera* CPlayerCamera::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CPlayerCamera;
	}

	return _Instance;
}

void CPlayerCamera::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//�R���X�g���N�^
CPlayerCamera::CPlayerCamera()
{
	//���ׂĂ�0������
	_CameraPos = Vector3D::ZeroVec();
	_TargetPos = Vector3D::ZeroVec();
	_CameraUp = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
}
CPlayerCamera::~CPlayerCamera() {

}

//����������
void CPlayerCamera::Init(){
	_CameraPos = CAMERA_START_POS;
	_TargetPos = TARGET_START_POS;
	_CameraUp = CAMERA_START_UP;
	_Rot = CAMERA_START_ROT;
}

//�`�拗���Z�b�g
void CPlayerCamera::SetNearFarPars(){
	//�j�A�E�t�@�[�Z�b�g
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	//�p�[�X�Z�b�g
	SetupCamera_Perspective(CAMERA_PARS);

	//�J�����X�V
	SetCameraPositionAndTargetAndUpVec(_CameraPos, _TargetPos, _CameraUp);
}

//���C������
void CPlayerCamera::Step(){
	//p�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�J�������_�ړ�����
	//�����_���
	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT)
		_TargetPos = cPlayer->GetTeleportPos();
	else
		_TargetPos = cPlayer->GetPos();
	//�Ǐ���ԂȂ�ړ��s��
	if (cPlayer->GetState() != CPlayer::ePlayerState::CLIMB) {
		//�J�����ړ�
		_Rot._X += CInputManager::GetRInputY() * CAMERA_SPD;
		_Rot._Y += CInputManager::GetRInputX() * CAMERA_SPD;

		//�J�����ړ��̊p�x�𐧌�����
		if (_Rot._X <= MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._X)) {
			_Rot._X = MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._X);
		}
		if (_Rot._X >= MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._X)) {
			_Rot._X = MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._X);
		}
		if (_Rot._Y >= MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._Y)) {
			_Rot._Y = 0.0f;
		}
		if (_Rot._Y <= MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._Y)) {
			_Rot._Y = 0.0f;
		}
	}

	//��]�p�x������W���v�Z
	//�����_�����_�ɕ��s�ړ�����s����쐬
	MyMatrix cameraMoveOriginMat = MyMatrix::GetTranslateMat(-_TargetPos);
	//�J������Y����]�s����쐬
	MyMatrix cameraRotYMat = MyMatrix::GetYawMatrix(_Rot._Y);
	//�J������X����]�s����쐬
	MyMatrix cameraRotXMat = MyMatrix::GetPitchMatrix(_Rot._X);
	//�J�����𒍎��_����O�Ɉړ������镽�s�ړ��s����쐬
	MyMatrix cameraMoveBackMat;
	//�v���C���[�̏�Ԃɂ���Ĉړ�������ς���
	if(cPlayer->GetState() != CPlayer::ePlayerState::CLIMB)
		cameraMoveBackMat = MyMatrix::GetTranslateMat(CAMERA_START_POS);
	else
		cameraMoveBackMat = MyMatrix::GetTranslateMat(CAMERA_CLIMB_POS);
	//�����_�����̈ʒu�ɖ߂����s�ړ�����s����쐬
	MyMatrix cameraReturnMat = MyMatrix::GetTranslateMat(_TargetPos);

	//�e�s�������
	MyMatrix cameraCompoundMat = cameraReturnMat * cameraRotYMat;
	cameraCompoundMat *= cameraRotXMat;
	cameraCompoundMat *= cameraMoveBackMat;
	cameraCompoundMat *= cameraMoveOriginMat;

	//�����_�ɍs����|���ăJ�����̍��W���Z�o
	_CameraPos = cameraCompoundMat * _TargetPos;
}

//�X�V����
void CPlayerCamera::Update(){
	//�J�����X�V
	SetCameraPositionAndTargetAndUpVec(_CameraPos, _TargetPos, _CameraUp);
}
