#pragma once
#include "DxLib.h"

//�Q�[���p�v���W�F�N�g�̃V�X�e�����܂Ƃ߂�����
class CGameSystem
{
	//�R���X�g���N�^�A�f�X�g���N�^��j������
	CGameSystem() = delete;
	~CGameSystem() = delete;

public:
	static void Start();		//�Q�[���̋N��
	static void MainLoop();		//���C�����[�v
	static void Fin();			//�Q�[���̌㏈��

private:
	static void Init();			//������
	static void Step();			//�X�e�b�v����


public://�A�N�Z�T�[
	static bool IsGameEnd() { return _IsGemeEnd; }	//�Q�[�����I�������邩

	static void RequestGameEnd() { _IsGemeEnd = true; }	//�Q�[���I�����N�G�X�g

private:
	static bool _IsGemeEnd;	//�Q�[���I����
};
