#pragma once
#include "../../Object/SceneObj.h"

//�Q�[���I�[�o�[�V�[���N���X
class CGameOverScene : public CSceneObj {
public:
	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();

	//�R���X�g���N�^�E�f�X�g���N�^
	CGameOverScene();
	~CGameOverScene();

private:
	//������
	void Init();

	//���C������
	void Step();

	//���[�h����
	void Load();

	//�㏈��
	void Fin();
};
