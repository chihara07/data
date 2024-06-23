#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../../Game/Player/Player.h"

//�G�N���X
class CEnemyShot : public CEnemyObj {
private:
	Vector3D _BulletMove;		//�e�ړ��x�N�g��
	Vector3D _BulletRot;		//�e��]�p�x
	Vector3D _BulletScale;		//�e�g�嗦
	int _BulletHndl;			//�e�n���h��
	int _BulletCount;			//�e�J�E���g
	int _BulletInterval;		//�e�C���^�[�o��
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyShot();
	~CEnemyShot();

	//������
	void Init();
	//���[�h
	void Load();
	//�Z�b�g
	void Set();
	//���C������
	void Step();
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�q�b�g�֐�
	void HitCalc();
	//�X�V����
	void Update();
	//���ˊ֐�
	void Shot();
	//�e���N�G�X�g
	void BulletRequest();
};
