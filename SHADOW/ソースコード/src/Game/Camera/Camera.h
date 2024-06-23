#pragma once
#include <DxLib.h>
#include "../../Library/Vector/Vector3D.h"

//�J�����N���X
class CPlayerCamera {
private:
	static CPlayerCamera* _Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayerCamera();
	~CPlayerCamera();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CPlayerCamera(const CPlayerCamera& other);
	CPlayerCamera operator= (const CPlayerCamera& other) {}

	Vector3D _CameraPos;	//�J�������_
	Vector3D _TargetPos;	//�J���������_
	Vector3D _CameraUp;		//�J���������
	Vector3D _Rot;			//��]�p�x

public:
	//�C���X�^���X�擾
	static CPlayerCamera* GetInstance();

	//�C���X�^���X�폜
	static void DeleteInstance();

	//����������
	void Init();

	//�`�拗���Z�b�g
	void SetNearFarPars();

	//���C������()
	void Step();

	//�X�V����
	void Update();

	//�J�������_�擾
	Vector3D GetcameraPos() { return _CameraPos; }
	//�J�������_�Z�b�g
	void SetCameraPos(Vector3D v) { _CameraPos = v; }
	//�J���������_�擾
	Vector3D GetTargetPos() { return _TargetPos; }
	//�J����������擾
	Vector3D GetCameraUp() { return _CameraUp; }
	//�J������]�p�x�擾
	Vector3D GetCameraRot() { return _Rot; }
	//��]�p�xX�Z�b�g
	void SetRotY(float rot_y) { _Rot._Y = rot_y; }
};
