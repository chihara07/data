#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../../Library/Effect/effekseer.h"
#include "../CollisionManager/CollisionManager.h"

using namespace PLAYER;

//コンストラクタ・デストラクタ
CPlayerManager::CPlayerManager() {

}
CPlayerManager::~CPlayerManager() {

}

//初期化
void CPlayerManager::Init() {
	cPlayer->Init(PLAYER_POS);
	cPlayerAttack->Init();
}
//ロード
void CPlayerManager::Load() {
	cPlayer->Load();
	cPlayerAttack->Load();
}
//セット
void CPlayerManager::Set() {
	cPlayer->Set();
	cPlayerAttack->Set();
}
//メイン処理
void CPlayerManager::Step() {
	cPlayer->Step();
	cPlayerAttack->Step();
}
//当たり判定
void CPlayerManager::Collision(int map_hndl) {
	cPlayer->SetGround(CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), map_hndl));
	cPlayer->SetPos(CCOllisionManager::HitCheck(cPlayer->GetPos(), cPlayer->GetRad(), map_hndl));
	cPlayer->SetTeleportPos(CCOllisionManager::HitCheck(cPlayer->GetTeleportPos(), cPlayer->GetRad(), map_hndl));
	CCOllisionManager::CheckHitPlayerToArea();
}
//描画
void CPlayerManager::Draw() {
	cPlayer->Draw();
	CEffekseerCtrl::Draw();
	cPlayerAttack->Draw();
	cPlayerUI.Draw();
}
//終了
void CPlayerManager::Fin() {
	cPlayer->Fin();
	cPlayerAttack->Fin();
}
//更新処理
void CPlayerManager::Update() {
	cPlayer->Update();
	cPlayerAttack->Update();
}

//破棄
void CPlayerManager::Delete() {
	cPlayer->DeleteInstance();
	cPlayerAttack->DeleteInstance();
}
	