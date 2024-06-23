#include "PlayScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Common.h"
#include "../../Library/Effect/effekseer.h"
#include "../../Library/Loading/Loading.h"

constexpr int EFFECT_NUM = 20;		//エフェクト総数
constexpr int PARTICLE_NUM = 2000;	//パーティクル総数

//コンストラクタ
CPlayScene::CPlayScene()
{
	_SceneID = eKind::SCENE_INIT;
}

//デストラクタ
CPlayScene::~CPlayScene()
{
	//各マネージャー削除
	cPlayerManager.Delete();
	cCoinManager->DeleteInstance();
	cEnemyManager->DeleteInstance();
	cTutorial->DeleteInstance();
	cPlayerCamera->DeleteInstance();
	CEffekseerCtrl::Fin();
}

//繰り返し行う処理
int CPlayScene::Loop()
{
	int iRet = 0;
	
	//シーン切り替え関数ポインタ実行
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	//プレイヤーが死んでいればゲームオーバーへ
	if (_IsEnd == true && player_active == false){ 
		iRet = (int)CSceneManager::eScene::GAME_OVER;
		cPlayer->DeleteInstance();
	}
	//クリアしているなら次のステージまたはクリアへ
	else if (_IsEnd == true) {
		if (StageID != eStageID::STAGE_4) {
			iRet = (int)CSceneManager::eScene::PLAY;
			StageID = static_cast<eStageID>(static_cast<int>(StageID) + 1);
		}
		else
			iRet = (int)CSceneManager::eScene::GAME_CLEAR;
	}
		
	player_active = false;

	return iRet;
}

//描画処理
void CPlayScene::Draw()
{
	if (_SceneID == eKind::SCENE_LOOP) {
		cBg.Draw();
		cCoinManager->Draw();
		cGimmickManager.Draw();
		cEnemyManager->Draw();
		cPlayerManager.Draw();
		cTutorial->Draw();
	}
}

//初期化
void CPlayScene::Init()
{
	cPlayerManager.Init();
	cPlayerCamera->Init();
	cPlayerCamera->SetNearFarPars();
	cEnemyManager->Init();
	cGimmickManager.Init();
	cTutorial->Init();
	cBg.Init();
	CEffekseerCtrl::Init(EFFECT_NUM, PARTICLE_NUM);
	CEffekseerCtrl::SetProjectionMtx(CAMERA_PARS, ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), CAMERA_NEAR, CAMERA_FAR);
	CLoading::LoadStart();

	_SceneID = eKind::SCENE_LOAD;

	_IsEnd = false;
}

//ロード処理
void CPlayScene::Load()
{
	//ロード中はロード画面にする
	if (CLoading::GetLoading() == true && CLoading::GetLoad() == false) {
		CLoading::SetLoad(true);
		cPlayerManager.Load();
		cEnemyManager->DataSet();
		cEnemyManager->Load();
		cCoinManager->Init();
		cCoinManager->Load();
		cGimmickManager.DataSet();
		cGimmickManager.Load();
		cBg.Load();
		CEffekseerCtrl::LoadData();
	}
	//ロード終わったら次へ
	if (CLoading::IsLoadEnd() == true) {
		cPlayerManager.Set();
		cEnemyManager->Set();
		cCoinManager->Set();
		cGimmickManager.Set();
		cBg.Set();
		CLoading::LoadEnd();
		CSoundManager::Play(CSoundManager::eSoundID::BGM, DX_PLAYTYPE_LOOP, true);
		CSoundManager::SetVolume(CSoundManager::eSoundID::BGM, BGM_VOLUME);

		_SceneID = eKind::SCENE_LOOP;
	}
}

//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	cTutorial->Step();

	if (cTutorial->GetTutorial() == false) {
		cEnemyManager->Step();
		cPlayerManager.Step();
		cBg.Step();
		cGimmickManager.Step();
		cCoinManager->Step();

		//各当たり判定処理
		cPlayerManager.Collision(cBg.GetHndl());
		cGimmickManager.Collision();
		cEnemyManager->Collision(cBg.GetHndl());
		cCoinManager->Collision();

		//カメラ処理
		cPlayerCamera->Step();
		CCOllisionManager::HitCheckCamera(cBg.GetHndl());

		//各アップデート処理
		cPlayerCamera->Update();
		cPlayerManager.Update();
		cEnemyManager->Update();
		cGimmickManager.Update();
		cBg.Update();
		cCoinManager->Update();
		CEffekseerCtrl::SetCameraMtx(cPlayerCamera->GetcameraPos(), cPlayerCamera->GetTargetPos(), cPlayerCamera->GetCameraUp());
		CEffekseerCtrl::Update();

		//クリアまたはプレイヤー死亡で次へ
		if (cPlayer->GetClear() == true || cPlayer->GetActive() == false)
			_SceneID = eKind::SCENE_EXIT;
	}
}

//終了処理
void CPlayScene::Fin()
{
	CLoading::SetLoading(true);
	CLoading::Reset();
	_IsEnd = true;

	player_active = cPlayer->GetActive();

	cEnemyManager->Fin();
	cGimmickManager.Fin();
	cBg.Fin();
	cPlayerManager.Fin();
	cCoinManager->Fin();
	CEffekseerCtrl::Fin();

	CSoundManager::Stop(CSoundManager::eSoundID::BGM);

	_SceneID = eKind::SCENE_INIT;
}
