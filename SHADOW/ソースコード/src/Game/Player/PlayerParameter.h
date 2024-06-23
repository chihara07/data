#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

namespace PLAYER {
	constexpr Vector3D PLAYER_POS(0.f, 0.f, 300.f);			//�v���C���[���W
	constexpr Vector3D PLAYER_SCALE(0.1f, 0.1f, 0.1f);		//�v���C���[�䗦
	constexpr Vector3D LIFE_TEXT_POS(760.f, 10.f, 0.f);		//���C�t�\���p���W
	constexpr Vector3D COIN_TEXT_POS(760.f, 10.f, 0.f);		//�R�C���\���p���W
	constexpr Vector3D LIFE_GRAPH_POS(740.f, 15.f, 0.f);	//���C�t�摜�p���W
	constexpr Vector3D COIN_GRAPH_POS(740.f, 17.f, 0.f);	//�R�C���摜�p���W
	constexpr Vector3D SHADOW_EFFECT_SCALE(9.f, 5.f, 9.f);	//�e�G�t�F�N�g�g�嗦
	constexpr Vector3D EFFECT_SCALE(2.5f);					//�G�t�F�N�g�̊g�嗦
	constexpr float PLAYER_SPD = 3.f;						//�v���C���[�̈ړ����x
	constexpr float SHADOW_SPD = 5.f;						//�e�̈ړ����x
	constexpr float PLAYER_RAD = 10.f;						//�v���C���[�̔��a
	constexpr float TELEPORT_SPD = 5.f;						//�e���|�[�g�̈ړ����x
	constexpr float TELEPORT_MOVE_MAX = 300.f;				//�e���|�[�g�̍ő�ړ�����
	constexpr float PLAYER_SHADOW_HEIGHT = 9.f;				//�e��ԗp�̍���
	constexpr float PLAYER_GRAVITY = 0.45f;					//�d��
	constexpr float PLAYER_GRAVITY2 = 0.2f;					//�d��2
	constexpr float PLAYER_GRAVITY_MAX = -5.f;				//�d�͂̍ő�l
	constexpr float PLAYER_GRAVITY_MAX2 = -2.f;				//�d�͂̍ő�l2
	constexpr float PLAYER_JUMP_POWER = 7.f;				//�W�����v��
	constexpr float DEATH_HEIGHT = -400.f;					//���ʍ���
	constexpr float CAN_DRAW_CAMERA_DISTANCE = 50.f;		//�v���C���[��`��ł���J�����Ƃ̋���
	constexpr float JUMP_VOLUME = 0.5f;						//�W�����v����
	constexpr int PLAYER_LIFE = 500;						//���C�t
}