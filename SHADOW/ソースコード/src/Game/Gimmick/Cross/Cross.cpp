#include "Cross.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Player/Player.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/CollisionManager/CollisionManager.h"

//コンストラクタ・デストラクタ
CCross::CCross() {
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
	_Hndl = -1;
	_CollisionHndl = -1;
}
CCross::~CCross() {
	Fin();
}

//初期化
void CCross::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Spd = 0.f;
	_MoveID = eMoveState::MOVE1;
	_State = eState::NORMAL;
}

//ロード
void CCross::Load() {
	//モデル読み込み
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::CROSS)); }
	if (_CollisionHndl == -1) { _CollisionHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::CROSS_COL)); }
}

//セット
void CCross::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_CollisionHndl, _Scale);
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
void CCross::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//回転させる
	_Rot._Y += _Spd;
	//範囲指定
	_Rot._Y = MyLib::UnwindRadians(_Rot._Y);
	//プレイヤーが乗っていたら一緒に回転する
	if (CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), _CollisionHndl))
	{
		//原点に平行移動させる行列
		MyMatrix moveOriginMat = MyMatrix::GetTranslateMat(-_Pos);
		//回転速度分回すY軸回転行列
		MyMatrix rotYMat = MyMatrix::GetYawMatrix(_Spd);
		//元の距離分移動させる平行移動行列
		MyMatrix moveDistanceMat = MyMatrix::GetTranslateMat(Vector3D::VGet(cPlayer->GetPos()._X - _Pos._X, cPlayer->GetPos()._Y, cPlayer->GetPos()._Z - _Pos._Z));
		//もとの位置に戻す平行移動行列
		MyMatrix returnMat = MyMatrix::GetTranslateMat(_Pos);

		//各行列を合成
		MyMatrix cameraCompoundMat = returnMat * rotYMat;
		cameraCompoundMat *= moveDistanceMat;
		cameraCompoundMat *= moveOriginMat;

		//かけたものをプレイヤー座標に代入
		cPlayer->SetPos(cameraCompoundMat * _Pos);
	}
}

//描画
void CCross::Draw() {
	MV1DrawModel(_Hndl);
}

//更新処理
void CCross::Update() {
	//回転角度、座標セット
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_CollisionHndl, _Rot);
	MV1SetPosition(_CollisionHndl, _Pos);

	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(_CollisionHndl, -1, TRUE);
	//コリジョン情報構築
	MV1SetupCollInfo(_CollisionHndl);
}

//終了
void CCross::Fin() {
	//コリジョン情報破棄
	MV1TerminateCollInfo(_CollisionHndl);
	//モデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_CollisionHndl != -1) { MV1DeleteModel(_CollisionHndl); _CollisionHndl = -1; }
}

//ヒット関数
void CCross::HitCalc() {
}
