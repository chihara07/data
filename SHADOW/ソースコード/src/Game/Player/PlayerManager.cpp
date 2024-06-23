#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../../Library/Effect/effekseer.h"
#include "../CollisionManager/CollisionManager.h"

using namespace PLAYER;

//�R���X�g���N�^�E�f�X�g���N�^
CPlayerManager::CPlayerManager() {

}
CPlayerManager::~CPlayerManager() {

}

//������
void CPlayerManager::Init() {
	cPlayer->Init(PLAYER_POS);
	cPlayerAttack->Init();
}
//���[�h
void CPlayerManager::Load() {
	cPlayer->Load();
	cPlayerAttack->Load();
}
//�Z�b�g
void CPlayerManager::Set() {
	cPlayer->Set();
	cPlayerAttack->Set();
}
//���C������
void CPlayerManager::Step() {
	cPlayer->Step();
	cPlayerAttack->Step();
}
//�����蔻��
void CPlayerManager::Collision(int map_hndl) {
	cPlayer->SetGround(CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), map_hndl));
	cPlayer->SetPos(CCOllisionManager::HitCheck(cPlayer->GetPos(), cPlayer->GetRad(), map_hndl));
	cPlayer->SetTeleportPos(CCOllisionManager::HitCheck(cPlayer->GetTeleportPos(), cPlayer->GetRad(), map_hndl));
	CCOllisionManager::CheckHitPlayerToArea();
}
//�`��
void CPlayerManager::Draw() {
	cPlayer->Draw();
	CEffekseerCtrl::Draw();
	cPlayerAttack->Draw();
	cPlayerUI.Draw();
}
//�I��
void CPlayerManager::Fin() {
	cPlayer->Fin();
	cPlayerAttack->Fin();
}
//�X�V����
void CPlayerManager::Update() {
	cPlayer->Update();
	cPlayerAttack->Update();
}

//�j��
void CPlayerManager::Delete() {
	cPlayer->DeleteInstance();
	cPlayerAttack->DeleteInstance();
}
	