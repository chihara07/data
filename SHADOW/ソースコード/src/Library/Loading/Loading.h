#pragma once

#include "DxLib.h"
#include "../Vector/Vector3D.h"

constexpr int LOAD_HNDL_NUM = 12;		//�摜��
constexpr int LOAD_ANIM_MAX_CNT = 3;	//�ő�A�j���[�V�����J�E���g

class CLoading {
private:
	static Vector2D _Pos;					//�摜���W
	static int _Hndl[LOAD_HNDL_NUM];		//�摜�n���h��
	static int _Cnt;						//�J�E���g
	static int _AnimCnt;					//�A�j���[�V�����J�E���g
	static int _HndlID;						//�摜ID
	static bool _IsLoading;					//���[�h���Ă��邩�t���O
	static bool _IsLoad;					//���[�h�������t���O
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CLoading();
	~CLoading();
	//������
	static void Init();
	//�ǂݍ���(�ق��̓ǂݍ��݂͂���̌�ɍs��)
	static void Load();
	//���[�h�J�n
	static void LoadStart();
	//�`��
	static void Draw();
	//���C������
	static void Step();
	//�I��
	static void Fin();
	//���[�h�I��
	static void LoadEnd();
	//���[�h��ʂ��I���ł��邩
	static bool IsLoadEnd();
	//���[�h���Ă��邩�t���O�擾
	static bool GetLoading();
	//���[�h���Ă��邩�t���O�Z�b�g
	static void SetLoading(bool f);
	//���[�h�������t���O�擾
	static bool GetLoad();
	//���[�h�������t���O�Z�b�g
	static void SetLoad(bool f);
	//�J�E���g���Z�b�g
	static void Reset();
};