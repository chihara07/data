#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../Coin/CoinManager.h"

//�G�N���X
class CEnemy : public CEnemyObj {
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemy();
	~CEnemy();

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
	//�ړ��֐�
	void Move();
	//��ԕω��֐�
	void ChangeState();
};
