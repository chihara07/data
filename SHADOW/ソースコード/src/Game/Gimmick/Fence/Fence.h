#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"
#include "../../Library/Vector/Vector3D.h"

//�t�F���X�N���X
class CFence : public CGimmickObj {
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CFence();
	~CFence();

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
