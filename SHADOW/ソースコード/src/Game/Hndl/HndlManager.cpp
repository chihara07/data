#include "HndlManager.h"
#include <iostream>
#include "../../Library/Common.h"
#include "../../Library/File/File.h"

//xmlファイルパス
constexpr char GRAPH_XML_PATH[] = "data/Xml/graphdata.xml";
constexpr char MODEL_XML_PATH[] = "data/Xml/modeldata.xml";

constexpr char NODE_NAME[] = "path";

CHndlManager* CHndlManager::_Instance = nullptr;

CHndlManager* CHndlManager::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CHndlManager;
	}

	return _Instance;
}

void CHndlManager::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CHndlManager::CHndlManager() {

}
CHndlManager::~CHndlManager() {
	Reset();
}

void CHndlManager::Init() {
	Reset();

	for (auto& hndl : _Hndl) hndl = -1;
	for (auto& hndl : _ModelHndl) hndl = -1;
}

void CHndlManager::Reset() {
	for (auto& hndl : _Hndl) {
		DeleteGraph(hndl);
		hndl = -1;
	}
	for (auto& hndl : _Hndl) {
		MV1DeleteModel(hndl);
		hndl = -1;
	}
}

void CHndlManager::Load() {
	//xmlファイル読み込み
	CFile::XmlFileInput(_Hndl, GRAPH_XML_PATH, NODE_NAME, false);
	
	CFile::XmlFileInput(_ModelHndl, MODEL_XML_PATH, NODE_NAME, true);
}

int CHndlManager::GetHndl(PATH_TYPE id) {
	return _Hndl[static_cast<int>(id)];
}

int CHndlManager::GetModelHndl(MODEL_PATH_TYPE id) {
	return _ModelHndl[static_cast<int>(id)];
}
