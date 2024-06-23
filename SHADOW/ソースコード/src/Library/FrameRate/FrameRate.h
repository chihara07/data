#pragma once

#include "DxLib.h"

class CFrameRate
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CFrameRate();
	~CFrameRate();

public:
	static void Init();		//������
	static void Step();		//�ʏ�
	static void Update();	//�X�V
	static void Draw();		//�`��

public:
	static bool IsExecutable();		//���s�\�����ׂ�

private:
	static void CalcFrameRate();	//�t���[�����[�g�̌v�Z	CalcFPS�Ɠ���
	static void DrawFrameRate();	//�t���[�����[�g�̕`��

private:
	static int _CurrentTime;				//���݂̎���
	static int _LastFrameTime;				//�O��̃t���[�����s���̎���
	static int _FrameCnt;					//�t���[���J�E���g�p
	static int _UpdateFrameRateTime;		//�t���[�����[�g���X�V��������
	static float _FrameRate;				//�t���[�����[�g�i�\���p�j
};