#include "DrawManager.h"
#include <iostream>
#include "../../Library/Common.h"

CDrawManager* CDrawManager::_Instance = nullptr;

CDrawManager* CDrawManager::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CDrawManager;
	}

	return _Instance;
}

void CDrawManager::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CDrawManager::CDrawManager() {

}
CDrawManager::~CDrawManager() {
	Reset();
	cHndlManager->DeleteInstance();
}

//初期化
void CDrawManager::Init() {
	Reset();

	_Hndl.resize(static_cast<int>(PATH_TYPE::PATH_TYPE_NUM));

	for (auto& hndl : _Hndl) hndl = -1;
}
//リセット
void CDrawManager::Reset() {
	for (auto& hndl : _Hndl) {
		hndl = -1;
	}
}
//ハンドルセット
void CDrawManager::SetHndl() {
	int cnt = 0;

	for (auto& hndl : _Hndl) {
		hndl = cHndlManager->GetHndl((PATH_TYPE)cnt);

		cnt++;
	}
}

void CDrawManager::Draw(PATH_TYPE id, int x, int y) {
	DrawGraph(x, y, _Hndl[static_cast<int>(id)], true);
}

void CDrawManager::Draw(PATH_TYPE id, float x, float y) {
	DrawGraphF(x, y, _Hndl[static_cast<int>(id)], true);
}

void CDrawManager::Draw(PATH_TYPE id, int x, int y, float rate, float angle) {
	DrawRotaGraph(x, y, rate, angle, _Hndl[static_cast<int>(id)], true);
}

void CDrawManager::Draw(PATH_TYPE id, float x, float y, float rate, float angle) {
	DrawRotaGraphF(x, y, rate, angle, _Hndl[static_cast<int>(id)], true);
}

void CDrawManager::Draw(PATH_TYPE id, VECTOR pos,float cx, float cy,float size, float angle) {
	DrawBillboard3D(pos, cx, cy, size, angle, _Hndl[static_cast<int>(id)], true);
}

void CDrawManager::Draw(PATH_TYPE id, int x1, int y1, int x2, int y2) {
	DrawExtendGraph(x1, y1, x2, y2, _Hndl[static_cast<int>(id)], true);
}
