#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

namespace PLAYER {
	constexpr Vector3D PLAYER_POS(0.f, 0.f, 300.f);			//プレイヤー座標
	constexpr Vector3D PLAYER_SCALE(0.1f, 0.1f, 0.1f);		//プレイヤー比率
	constexpr Vector3D LIFE_TEXT_POS(760.f, 10.f, 0.f);		//ライフ表示用座標
	constexpr Vector3D COIN_TEXT_POS(760.f, 10.f, 0.f);		//コイン表示用座標
	constexpr Vector3D LIFE_GRAPH_POS(740.f, 15.f, 0.f);	//ライフ画像用座標
	constexpr Vector3D COIN_GRAPH_POS(740.f, 17.f, 0.f);	//コイン画像用座標
	constexpr Vector3D SHADOW_EFFECT_SCALE(9.f, 5.f, 9.f);	//影エフェクト拡大率
	constexpr Vector3D EFFECT_SCALE(2.5f);					//エフェクトの拡大率
	constexpr float PLAYER_SPD = 3.f;						//プレイヤーの移動速度
	constexpr float SHADOW_SPD = 5.f;						//影の移動速度
	constexpr float PLAYER_RAD = 10.f;						//プレイヤーの半径
	constexpr float TELEPORT_SPD = 5.f;						//テレポートの移動速度
	constexpr float TELEPORT_MOVE_MAX = 300.f;				//テレポートの最大移動距離
	constexpr float PLAYER_SHADOW_HEIGHT = 9.f;				//影状態用の高さ
	constexpr float PLAYER_GRAVITY = 0.45f;					//重力
	constexpr float PLAYER_GRAVITY2 = 0.2f;					//重力2
	constexpr float PLAYER_GRAVITY_MAX = -5.f;				//重力の最大値
	constexpr float PLAYER_GRAVITY_MAX2 = -2.f;				//重力の最大値2
	constexpr float PLAYER_JUMP_POWER = 7.f;				//ジャンプ力
	constexpr float DEATH_HEIGHT = -400.f;					//死ぬ高さ
	constexpr float CAN_DRAW_CAMERA_DISTANCE = 50.f;		//プレイヤーを描画できるカメラとの距離
	constexpr float JUMP_VOLUME = 0.5f;						//ジャンプ音量
	constexpr int PLAYER_LIFE = 500;						//ライフ
}