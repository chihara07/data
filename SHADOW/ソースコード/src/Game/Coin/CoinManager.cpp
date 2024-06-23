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

//�R���X�g���N�^�E�f�X�g���N�^
CCoinManager::CCoinManager() {
	_Hndl = -1;
}

CCoinManager::~CCoinManager() {
	Fin();
}

//������
void CCoinManager::Init() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Init();
	}
}

//���[�h
void CCoinManager::Load() {
	_Hndl = MV1LoadModel(COIN_PATH);

	for (auto coin_itr : _CoinList) {
		coin_itr->Load(_Hndl);
	}
}

//�Z�b�g
void CCoinManager::Set() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Set();
	}
}

//���C������
void CCoinManager::Step() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Step();
	}
}

//�����蔻��
void CCoinManager::Collision() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Collision();
	}
}

//�`��
void CCoinManager::Draw() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Draw();
	}
}

//�I��
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

//�X�V����
void CCoinManager::Update() {
	for (auto coin_itr : _CoinList) {
		coin_itr->Update();
	}
}
