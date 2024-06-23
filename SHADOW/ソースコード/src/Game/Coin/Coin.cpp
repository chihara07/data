#include "Coin.h"
#include "../CollisionManager/CollisionManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"

constexpr Vector3D COIN_SCALE(0.1f, 0.1f, 0.1f);		//コイン拡大率
constexpr float COIN_RAD = 10.f;						//コイン半径
constexpr float COIN_SPD = 0.1f;						//コイン回転速度

//コンストラクタ・デストラクタ
CCoin::CCoin() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Hndl = -1;
	_Rad = COIN_RAD;
	_IsActive = false;
	_CoinType = eCoinType::NONE;
}

CCoin::~CCoin() {

}

//初期化
void CCoin::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Hndl = -1;
	_Rad = COIN_RAD;
	_Scale = COIN_SCALE;
	_IsActive = false;
	_CoinType = eCoinType::NONE;
}

//ロード
void CCoin::Load(int coin_hndl) {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(coin_hndl); }
}

//セット
void CCoin::Set() {
	//比率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//メイン処理
void CCoin::Step() {
	if (_IsActive == true) {
		_Rot._Y += COIN_SPD;
	}
}
//描画
void CCoin::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
}

//終了
void CCoin::Fin() {
	//コピーモデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//当たり判定
void CCoin::Collision() {
	_IsActive = CCOllisionManager::CheckHitPlayerToCoin(_Pos, _Rad, _IsActive);
}

//更新処理
void CCoin::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}
