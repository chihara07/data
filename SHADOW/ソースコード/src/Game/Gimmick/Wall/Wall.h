#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"

//�ǃN���X
class CWall : public CGimmickObj {
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CWall();
	~CWall();

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
	//�X�V����
	void Update();
	//�q�b�g�֐�
	void HitCalc();
};
