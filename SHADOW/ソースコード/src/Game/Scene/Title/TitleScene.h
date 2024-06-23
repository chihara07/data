#pragma once
#include "../../Object/SceneObj.h"
#include "../../Game/Hndl/HndlManager.h"

//�^�C�g���V�[���N���X
class CTitleScene : public CSceneObj {
private:
	PATH_TYPE _GraphID;			//�摜
	int _Interval;				//�C���^�[�o��
public:
	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();

	//�R���X�g���N�^�E�f�X�g���N�^
	CTitleScene();
	~CTitleScene();

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
