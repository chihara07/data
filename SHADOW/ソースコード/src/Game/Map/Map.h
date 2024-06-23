#pragma once
#include <DxLib.h>
#include "../../Library/Vector/Vector3D.h"

//�o�b�N�O���E���h�N���X
class CBg {
private:
	int _Hndl;				//�t�B�[���h�摜�n���h��
	int _ColHndl;			//�����蔻��n���h��
	Vector3D _Pos;			//�t�B�[���h���W
	Vector3D _Scale;		//�t�B�[���h�䗦
	Vector3D _Rot;			//�t�B�[���h��]�p�x
	int _SkyHndl;			//�V���摜�n���h��
	Vector3D _SkyPos;		//�V�����W
	Vector3D _SkyScale;		//�V���䗦
	Vector3D _SkyRot;		//�V����]�p�x
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBg();
	~CBg();

	//����������
	void Init();

	//���[�h����
	void Load();

	//�Z�b�g
	void Set();

	//�I������
	void Fin();

	//���C������
	void Step();

	//�`�揈��
	void Draw();

	//�A�b�v�f�[�g����
	void Update();

	//�n���h���擾
	int GetHndl() { return _ColHndl; }

	//��]�p�x�Z�b�g
	void SetRot(Vector3D r) { _Rot = r; }
};
