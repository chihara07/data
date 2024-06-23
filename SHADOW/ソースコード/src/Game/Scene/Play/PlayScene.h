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

//プレイシーンクラス
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
	//コンストラクタ・デストラクタ
	CPlayScene();
	~CPlayScene();

	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();
private:
	//初期化
	void Init();
	//ロード処理
	void Load();
	//終了処理
	void Fin();
	//毎フレーム呼ぶ処理
	void Step();
};
