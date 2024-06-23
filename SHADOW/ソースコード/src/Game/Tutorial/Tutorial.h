#pragma once

#include "DxLib.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr int HNDL_NUM = 21;

class CTutorial {
private:
	static CTutorial* _Instance;

	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial();
	~CTutorial();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CTutorial(const CTutorial& other);
	CTutorial operator= (const CTutorial& other) {}

	bool _IsTutorial;		//�`���[�g���A������
	bool _IsPressed;		//�����ꂽ��
	PATH_TYPE _TutorialEnd;	//�`���[�g���A���̍Ō�
	PATH_TYPE _HndlID;		//�n���h��ID
public:
	//�C���X�^���X�擾
	static CTutorial* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();
	//������
	void Init();
	//���[�h
	void Load();
	//�X�e�b�v
	void Step();
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�`���[�g���A����i�߂�
	void AdvanceTutorial();
	//�`���[�g���A�������擾
	const bool GetTutorial() { return _IsTutorial; }
	//�`���[�g���A�������Z�b�g
	void SetTutorial(bool f) { _IsTutorial = f; }
	//�����ꂽ���Z�b�g
	void SetPressed(bool f) { _IsPressed = f; }
};