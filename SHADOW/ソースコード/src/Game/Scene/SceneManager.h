#pragma once
#include "Play/PlayScene.h"
#include "Title/TitleScene.h"
#include "Clear/ClearScene.h"
#include "GameOver/GameOverScene.h"
#include "../../Library/Sound/SoundManager.h"

//�V�[���}�l�[�W���[�N���X
class CSceneManager {
public:
	//���݂̃V�[��
	enum class eScene {
		TITLE = 1,
		PLAY,
		GAME_CLEAR,
		GAME_OVER
	};
	//�V�[���̏��
	enum class eManagerState {
		INIT,
		MAIN,
		FIN,

		NUM
	};
private:
	int _PlayID;
	eManagerState _State;
	CSceneObj* _Scene;

	eScene _SceneID;
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSceneManager();
	~CSceneManager();

	//���[�v����
	void Loop() { (this->*LoopSwitchFunc[static_cast<int>(_State)])(); }
	//������
	void Init();
	//���C��
	void Main();
	//�I��
	void Fin();
	//�`�揈��
	void Draw();
	//�V�[������
	void CreateScene(eScene id);

	//���[�v�؂�ւ��֐��|�C���^
	void (CSceneManager::* LoopSwitchFunc[static_cast<int>(eManagerState::NUM)])() =
	{ &CSceneManager::Init, &CSceneManager::Main, &CSceneManager::Fin };
};
