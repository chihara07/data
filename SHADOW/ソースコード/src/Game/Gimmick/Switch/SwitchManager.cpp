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

//�R���X�g���N�^�E�f�X�g���N�^
CSwitchManager::CSwitchManager() {
	_Hndl = -1;
	_PressedHndl = -1;
}

CSwitchManager::~CSwitchManager() {
	Fin();
}

//������
void CSwitchManager::Init() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Init();
	}
}

//���[�h
void CSwitchManager::Load() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Load();
	}
}

//�Z�b�g
void CSwitchManager::Set() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Set();
	}
}

//���C������
void CSwitchManager::Step() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Step();
	}
}

//�����蔻��
void CSwitchManager::Collision() {
	for (auto switch_itr : _SwitchList) {
		CCOllisionManager::CheckHitPlayerToSwitch(switch_itr);
	}
}

//�`��
void CSwitchManager::Draw() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Draw();
	}
}

//�I��
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

//�X�V����
void CSwitchManager::Update() {
	for (auto switch_itr : _SwitchList) {
		switch_itr->Update();
	}
}
