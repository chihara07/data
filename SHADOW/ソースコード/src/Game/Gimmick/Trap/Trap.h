#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"
#include "../../Library/Vector/Vector3D.h"

//�g���b�v�N���X
class CTrap : public CGimmickObj {
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTrap();
	~CTrap();

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
};
