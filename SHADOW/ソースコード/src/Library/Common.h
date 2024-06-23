#pragma once

//ウィンドウの幅・高さ
constexpr int WINDOW_HEIGHT = 600;
constexpr int WINDOW_WIDTH = 800;

//設定フレームレート
constexpr int FRAME_RATE = 60;

//ニア・ファー・パース
constexpr float CAMERA_NEAR = 1.0f;
constexpr float CAMERA_FAR = 7000.0f;
constexpr float CAMERA_PARS = 60.f * DX_PI_F / 180.f;

constexpr float MAP_FLOOR_NORM_Y_MIN = (0.1f);	//法線のY成分絶対値がこの値以上であれば床
constexpr float MAP_WALL_NORM_Z_MIN = (0.5f);	//法線のZ成分絶対値がこの値以上であればXY平面の壁
constexpr float MAP_WALL_NORM_X_MIN = (0.5f);	//法線のX成分絶対値がこの値以上であればYZ平面の壁
constexpr float MAP_CEIL_NORM_Y = (-0.9f);		//法線のY成分がこの値以下であれば天井

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
