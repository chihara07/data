#pragma once

#include "DxLib.h"
#include <vector>
#include "Path.h"

class CHndlManager {
private:
	static CHndlManager* _Instance;		//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	CHndlManager();
	~CHndlManager();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CHndlManager(const CHndlManager& other);
	CHndlManager operator= (const CHndlManager& other) {}

	std::vector<int> _Hndl;			//�n���h���i�[�p���X�g
	std::vector<int> _ModelHndl;	//���f���n���h���i�[�p���X�g
public:
	//�C���X�^���X�擾
	static CHndlManager* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();
	//������
	void Init();
	//���Z�b�g
	void Reset();
	//���[�h
	void Load();
	//�n���h���擾
	int GetHndl(PATH_TYPE id);
	//���f���n���h���擾
	int GetModelHndl(MODEL_PATH_TYPE id);
};