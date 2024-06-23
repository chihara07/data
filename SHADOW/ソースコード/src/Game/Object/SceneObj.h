#pragma once

constexpr float BGM_VOLUME = 0.5f;						//BGM����

//�^�C�g���V�[���N���X
class CSceneObj {
public:
	//�Q�[�����̗���
	enum class eKind {
		SCENE_INIT,		//������
		SCENE_LOAD,		//���[�h
		SCENE_LOOP,		//���[�v
		SCENE_EXIT,		//�I��

		SCENE_NUM
	};

	eKind _SceneID;		//�V�[��ID

	bool _IsEnd = false;	//�I���t���O
public:
	//�J��Ԃ��s������
	virtual int Loop() { return 0; }
	//�`�揈��
	virtual void Draw() {};

	//�R���X�g���N�^�E�f�X�g���N�^
	CSceneObj() {};
	virtual ~CSceneObj() {};

public:
	//������
	virtual void Init() {};

	//���C������
	virtual void Step() {};

	//���[�h����
	virtual void Load() {};

	//�㏈��
	virtual void Fin() {};

public:
	//�^�C�g���V�[���؂�ւ��֐��|�C���^
	void (CSceneObj::* SceneSwitchFunc[static_cast<int>(eKind::SCENE_NUM)])() =
	{ &CSceneObj::Init, &CSceneObj::Load, &CSceneObj::Step, &CSceneObj::Fin };
};
