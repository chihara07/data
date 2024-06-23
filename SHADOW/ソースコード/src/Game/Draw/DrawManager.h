#pragma once

#include "DxLib.h"
#include <vector>
#include "../Hndl/Path.h"
#include "../Hndl/HndlManager.h"

class CDrawManager {
private:
	static CDrawManager* _Instance;		//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	CDrawManager();
	~CDrawManager();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CDrawManager(const CDrawManager& other);
	CDrawManager operator= (const CDrawManager& other) {}

	std::vector<int> _Hndl;		//�n���h���p�z��

	//�n���h���擾
	CHndlManager* cHndlManager = CHndlManager::GetInstance();
public:
	//�C���X�^���X�擾
	static CDrawManager* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();

	//������
	void Init();
	//���Z�b�g
	void Reset();
	//�n���h���Z�b�g
	void SetHndl();
	/// <summary>
	/// 2D�`��(int�^)
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="x">= X���W</param>
	/// <param name="y">= Y���W</param>
	void Draw(PATH_TYPE id, int x, int y);
	/// <summary>
	/// 2D�`��(float�^)
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="x">= X���W</param>
	/// <param name="y">= Y���W</param>
	void Draw(PATH_TYPE id, float x, float y);
	/// <summary>
	/// 2D��]�`��(int�^)
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="x">= X���W</param>
	/// <param name="y">= Y���W</param>
	/// <param name="rate">= �g�嗦</param>
	/// <param name="angle">= ��]�p�x</param>
	void Draw(PATH_TYPE id, int x, int y, float rate, float angle);
	/// <summary>
	/// 2D��]�`��(float�^)
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="x">= X���W</param>
	/// <param name="y">= Y���W</param>
	/// <param name="rate">= �g�嗦</param>
	/// <param name="angle">= ��]�p�x</param>
	void Draw(PATH_TYPE id, float x, float y, float rate, float angle);
	/// <summary>
	/// �r���{�[�h�`��
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="pos">= ���W</param>
	/// <param name="cx">= �摜�̒��SX���W(0.f�`1.f)</param>
	/// <param name="cy">= �摜�̒��SY���W(0.f�`1.f)</param>
	/// <param name="size">= �T�C�Y</param>
	/// <param name="angle">= ��]�p�x</param>
	void Draw(PATH_TYPE id, VECTOR pos, float cx, float cy, float size, float angle);
	/// <summary>
	/// 2D�g��k���`��
	/// </summary>
	/// <param name="id">= �摜ID</param>
	/// <param name="x1">= �摜����X���W</param>
	/// <param name="y1">= �摜����Y���W</param>
	/// <param name="x2">= �摜�E��X���W</param>
	/// <param name="y2">= �摜�E��Y���W</param>
	void Draw(PATH_TYPE id, int x1, int y1, int x2, int y2);
};