#pragma once
#include "../../Object/SceneObj.h"

//�N���A�V�[���N���X
class CClearScene : public CSceneObj {
public:
	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();

	//�R���X�g���N�^�E�f�X�g���N�^
	CClearScene();
	~CClearScene();

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
