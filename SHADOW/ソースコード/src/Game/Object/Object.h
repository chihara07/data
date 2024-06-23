#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

//�I�u�W�F�N�g�N���X
class CObj {
protected:
	Vector3D _Pos;		//���W
	Vector3D _Move;		//�ړ���
	Vector3D _Scale;	//�䗦
	Vector3D _Rot;		//��]�p�x
	int _Hndl;			//���f���n���h��
	int _Size;			//�T�C�Y
	int _Life;			//���C�t
	float _Rad;			//���a
	float _Spd;			//�ړ����x
	bool _IsActive;		//�����t���O
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObj():_Hndl(-1), _IsActive(), _Size(), _Rad(), _Spd(), _Life() {};
	~CObj() {};

	//������
	virtual void Init() {};
	//���[�h
	virtual void Load() {};
	//���C������
	virtual void Step() {};
	//�`��
	virtual void Draw() {};
	//�I��
	virtual void Fin() {};
	//�X�V����
	virtual void Update() {};

	//���C�t�擾
	int GetLife() const { return _Life; }

	void SubLife() { _Life--; }
};