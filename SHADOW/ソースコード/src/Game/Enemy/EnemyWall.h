#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"

//�G�N���X
class CEnemyWall : public CEnemyObj {
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyWall();
	~CEnemyWall();

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
	//���S�֐�
	void DeathCalc();
	//�X�V����
	void Update();
	//�ړ��֐�
	void Move();
	//��ԕω��֐�
	void ChangeState();

	//�ʏ��ԃA�N�V�����֐�
	void NormalAct();
	//�v���C���[��ǂ������Ă����Ԋ֐�
	void ChaseAct();
};
