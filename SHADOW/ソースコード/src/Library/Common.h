#pragma once

//�E�B���h�E�̕��E����
constexpr int WINDOW_HEIGHT = 600;
constexpr int WINDOW_WIDTH = 800;

//�ݒ�t���[�����[�g
constexpr int FRAME_RATE = 60;

//�j�A�E�t�@�[�E�p�[�X
constexpr float CAMERA_NEAR = 1.0f;
constexpr float CAMERA_FAR = 7000.0f;
constexpr float CAMERA_PARS = 60.f * DX_PI_F / 180.f;

constexpr float MAP_FLOOR_NORM_Y_MIN = (0.1f);	//�@����Y������Βl�����̒l�ȏ�ł���Ώ�
constexpr float MAP_WALL_NORM_Z_MIN = (0.5f);	//�@����Z������Βl�����̒l�ȏ�ł����XY���ʂ̕�
constexpr float MAP_WALL_NORM_X_MIN = (0.5f);	//�@����X������Βl�����̒l�ȏ�ł����YZ���ʂ̕�
constexpr float MAP_CEIL_NORM_Y = (-0.9f);		//�@����Y���������̒l�ȉ��ł���ΓV��

#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

enum class eStageID {
	STAGE_0 = 0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,

	STAGE_NUM,
};

extern eStageID StageID;
