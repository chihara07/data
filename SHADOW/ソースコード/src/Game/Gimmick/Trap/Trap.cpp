#include "Trap.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr float TRAP_RAD = 20.0f;						//影の半径

//コンストラクタ・デストラクタ
CTrap::CTrap() {
	_Hndl = -1;
	_Rad = TRAP_RAD;
}
CTrap::~CTrap() {
	Fin();
}

//初期化
void CTrap::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rad = TRAP_RAD;
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
}

//ロード
void CTrap::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::TRAP)); }
}

//セット
void CTrap::Set() {
	//拡大率セット、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetPosition(_Hndl, _Pos);
}

//メイン処理
void CTrap::Step() {
}

//描画
void CTrap::Draw() {
	MV1DrawModel(_Hndl);
}

//更新処理
void CTrap::Update() {
	MV1SetPosition(_Hndl, _Pos);
}

//終了
void CTrap::Fin() {
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}
