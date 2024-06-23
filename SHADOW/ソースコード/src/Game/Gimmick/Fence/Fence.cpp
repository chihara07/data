#include "Fence.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D FENCE_COLLISION_SCALE( 0.5f, 0.5f, 0.7f );			//フェンス当たり判定拡大率

//コンストラクタ・デストラクタ
CFence::CFence() {
	_Hndl = -1;
	_CollisionHndl = -1;
}
CFence::~CFence() {
	Fin();
}

//初期化
void CFence::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_CollisionScale = FENCE_COLLISION_SCALE;
	_Hndl = -1;
	_CollisionHndl = -1;
}

//ロード
void CFence::Load() {
	//モデル読み込み
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FENCE)); }
	if (_CollisionHndl == -1){ _CollisionHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FENCE_COL)); }
}

//セット
void CFence::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_CollisionHndl, _CollisionScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(_CollisionHndl, -1, TRUE);

	//コリジョン情報構築
	MV1SetupCollInfo(_CollisionHndl);
}

//メイン処理
void CFence::Step() {
	
}

//描画
void CFence::Draw() {
	//モデル描画
	MV1DrawModel(_Hndl);
}

//更新処理
void CFence::Update() {
	//回転角度、座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(_CollisionHndl, -1, TRUE);
}

//終了
void CFence::Fin() {
	//コリジョン情報破棄
	MV1TerminateCollInfo(_CollisionHndl);
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_CollisionHndl != -1) { MV1DeleteModel(_CollisionHndl); _CollisionHndl = -1; }
}

//ヒット関数
void CFence::HitCalc() {
}
