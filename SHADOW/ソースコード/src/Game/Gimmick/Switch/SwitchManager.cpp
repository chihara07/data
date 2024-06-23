#include "SwitchManager.h"
#include "../../Game/CollisionManager/CollisionManager.h"

CSwitchManager* CSwitchManager::_Instance = nullptr;

CSwitchManager* CSwitchManager::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CSwitchManager;
	}

	return _Instance;
}

void CSwitchManager::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CSwitchManager::CSwitchManager() {
	_Hndl = -1;
	_PressedHndl = -1;
}

CSwitchManager::~CSwitchManager() {
	Fin();
}

//初期化
void CSwitchManager::Init() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Init();
	}
}

//ロード
void CSwitchManager::Load() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Load();
	}
}

//セット
void CSwitchManager::Set() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Set();
	}
}

//メイン処理
void CSwitchManager::Step() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Step();
	}
}

//当たり判定
void CSwitchManager::Collision() {
	for (auto switch_itr : _SwitchList) {
		CCOllisionManager::CheckHitPlayerToSwitch(switch_itr);
	}
}

//描画
void CSwitchManager::Draw() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Draw();
	}
}

//終了
void CSwitchManager::Fin() {
	for (auto switch_itr = _SwitchList.begin(); switch_itr != _SwitchList.end();) {
		(*switch_itr)->Fin();
		delete* switch_itr;
		switch_itr = _SwitchList.erase(switch_itr);
	}

	_SwitchList.clear();

	MV1DeleteModel(_Hndl);
	_Hndl = -1;
	MV1DeleteModel(_PressedHndl);
	_PressedHndl = -1;
}

//更新処理
void CSwitchManager::Update() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Update();
	}
}
