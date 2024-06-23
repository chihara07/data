#include "CoinManager.h"
#include "../CollisionManager/CollisionManager.h"

CCoinManager* CCoinManager::_Instance = nullptr;

CCoinManager* CCoinManager::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CCoinManager;
	}

	return _Instance;
}

void CCoinManager::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CCoinManager::CCoinManager() {
	_Hndl = -1;
}

CCoinManager::~CCoinManager() {
	Fin();
}

//初期化
void CCoinManager::Init() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Init();
	}
}

//ロード
void CCoinManager::Load() {
	_Hndl = MV1LoadModel(COIN_PATH);

	for (auto coin_itr : _CoinList) {
		coin_itr->Load(_Hndl);
	}
}

//セット
void CCoinManager::Set() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Set();
	}
}

//メイン処理
void CCoinManager::Step() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Step();
	}
}

//当たり判定
void CCoinManager::Collision() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Collision();
	}
}

//描画
void CCoinManager::Draw() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Draw();
	}
}

//終了
void CCoinManager::Fin() {
	for (auto coin_itr = _CoinList.begin(); coin_itr != _CoinList.end();) {
		(*coin_itr)->Fin();
		delete* coin_itr;
		coin_itr = _CoinList.erase(coin_itr);
	}

	_CoinList.clear();

	MV1DeleteModel(_Hndl);
	_Hndl = -1;
}

//更新処理
void CCoinManager::Update() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Update();
	}
}
