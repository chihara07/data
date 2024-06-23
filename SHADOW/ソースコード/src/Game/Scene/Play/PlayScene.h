#pragma once
#include <DxLib.h>
#include "../../Player/PlayerManager.h"
#include "../../Camera/Camera.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Enemy/EnemyShot.h"
#include "../../Enemy/EnemyFlash.h"
#include "../../Enemy/EnemyWall.h"
#include "../../Gimmick/GimmickManager.h"
#include "../../Map/Map.h"
#include "../../Object/SceneObj.h"
#include "../../Tutorial/Tutorial.h"
#include "../../Coin/CoinManager.h"

//�v���C�V�[���N���X
class CPlayScene : public CSceneObj {
private:
	CPlayer* cPlayer = CPlayer::GetInstance();
	CPlayerManager cPlayerManager;
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();
	CEnemyManager* cEnemyManager = CEnemyManager::GetInstance();
	CGimmickManager cGimmickManager;
	CTutorial* cTutorial = CTutorial::GetInstance();
	CBg cBg;
	bool player_active = false;
	CCoinManager* cCoinManager = CCoinManager::GetInstance();
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayScene();
	~CPlayScene();

	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();
private:
	//������
	void Init();
	//���[�h����
	void Load();
	//�I������
	void Fin();
	//���t���[���Ăԏ���
	void Step();
};
