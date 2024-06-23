#pragma once

//2D�摜�p�X
enum class PATH_TYPE{
	PLAYER_LIFE,		//�v���C���[���C�t
	PLAYER_HAVECOIN,	//�v���C���[�����R�C��
	COIN1,				//�R�C��1
	COIN2,				//�R�C��2
	COIN3,				//�R�C��3
	BG_CLEAR,			//�N���A���
	BG_GAMEOVER,		//�Q�[���I�[�o�[���
	BG_TITLE,			//�^�C�g�����
	DESCRIPTION1,		//�������1
	DESCRIPTION2,		//�������2
	AREAENERGY1,		//�e�G���A�G�l���M�[1
	AREAENERGY2,		//�e�G���A�G�l���M�[2
	ENERGY,				//�G�l���M�[
	CONSUMPTION,		//�G�l���M�[����
	DISCOVERY,			//�r�b�N���}�[�N
	TEXT1,				//�e�L�X�g1
	TEXT2,				//�e�L�X�g2
	TUTORIAL1,			//�`���[�g���A��1
	TUTORIAL2,			//�`���[�g���A��2
	TUTORIAL3,			//�`���[�g���A��3
	TUTORIAL4,			//�`���[�g���A��4
	TUTORIAL5,			//�`���[�g���A��5
	TUTORIAL6,			//�`���[�g���A��6
	TUTORIAL7,			//�`���[�g���A��7
	TUTORIAL8,			//�`���[�g���A��8
	TUTORIAL9,			//�`���[�g���A��9
	TUTORIAL10,			//�`���[�g���A��10
	TUTORIAL11,			//�`���[�g���A��11
	TUTORIAL12,			//�`���[�g���A��12
	TUTORIAL13,			//�`���[�g���A��13
	TUTORIAL14,			//�`���[�g���A��14
	TUTORIAL15,			//�`���[�g���A��15
	TUTORIAL16,			//�`���[�g���A��16
	TUTORIAL17,			//�`���[�g���A��17
	TUTORIAL18,			//�`���[�g���A��18
	TUTORIAL19,			//�`���[�g���A��19
	TUTORIAL20,			//�`���[�g���A��20
	TUTORIAL21,			//�`���[�g���A��21
	TUTORIAL22,			//�`���[�g���A��22
	TUTORIAL23,			//�`���[�g���A��23

	PATH_TYPE_NUM
};

//3D���f���p�X
enum class MODEL_PATH_TYPE {
	PLAYER,			//�v���C���[
	PLAYER_SHADOW,	//�v���C���[�e���
	PLAYER_TELEPORT,//�v���C���[�e���|�[�g���
	PLAYER_ATTACK,	//�v���C���[�U��
	PLAYER_AREA,	//�v���C���[�e�G���A
	ENEMY,			//�G
	ENEMY_SHOT,		//�e��łG
	ENEMY_FLASH,	//�t���b�V���U��������G
	BULLET,			//�e
	FLASH_AREA,		//�t���b�V���U��
	BLOCK,			//�u���b�N
	BLOCK2,			//�u���b�N2
	FENCE,			//�t�F���X
	FENCE_COL,		//�t�F���X�����蔻��
	GOAL,			//�S�[��
	NOSHADOW,		//�e�֎~
	SWITCH,			//�X�C�b�`
	SWITCH2,		//�X�C�b�`2
	SHADOW,			//�e
	SHADOW2,		//�e2
	TRAP,			//�g���b�v
	WALL,			//��
	CROSS,			//�\��
	CROSS_COL,		//�\�������蔻��
	MAP0_PATH,		//�}�b�v0
	MAP0_COL_PATH,	//�}�b�v0�����蔻��
	MAP1_PATH,		//�}�b�v1
	MAP1_COL_PATH,	//�}�b�v1�����蔻��
	MAP2_PATH,		//�}�b�v2
	MAP2_COL_PATH,	//�}�b�v2�����蔻��
	MAP3_PATH,		//�}�b�v3
	MAP3_COL_PATH,	//�}�b�v3�����蔻��
	MAP4_PATH,		//�}�b�v4
	MAP4_COL_PATH,	//�}�b�v4�����蔻��

	NUM,
};
