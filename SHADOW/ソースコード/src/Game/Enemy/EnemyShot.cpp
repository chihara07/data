#include "EnemyShot.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D BULLET_SCALE(0.04f, 0.04f, 0.04f);		//弾拡大率
constexpr Vector3D BULLET_SHOT_POS(0.f, -3.f, -5.f);	//敵発射位置
constexpr float SOUND_RANGE = 300.0f;					//音の聞こえる範囲
constexpr float BULLET_RAD = 4.f;						//弾半径
constexpr float BULLET_SPD = 3.f;						//弾速度
constexpr int BULLET_MAX_COUNT = 50;					//弾カウント最大値
constexpr int BULLET_INTERVAL = 40;						//弾インターバル

//コンストラクタ・デストラクタ
CEnemyShot::CEnemyShot() {
	_BulletRot = Vector3D::ZeroVec();
	_BulletMove = Vector3D::ZeroVec();
	_BulletScale = Vector3D::ZeroVec();
	_BulletRad = 0.f;
	_IsForward = false;
	_IsBulletActive = false;
	_KnockBackSpd = 0.f;
	_CoinType = eCoin::NONE;
	_BulletHndl = -1;
	_BulletCount = 0;
	_BulletInterval = 0;
}
CEnemyShot::~CEnemyShot() {
	Fin();
}

//初期化
void CEnemyShot::Init() {
	_Pos = Vector3D::ZeroVec();;
	_Rot = Vector3D::ZeroVec();;
	_ResetRot = _Rot;
	_BulletRot = Vector3D::ZeroVec();
	_BulletMove = Vector3D::VGet(0.f, 0.f, -BULLET_SPD);
	_Scale = ENEMY_SCALE;
	_BulletScale = BULLET_SCALE;
	_Rad = ENEMY_RAD;
	_BulletRad = BULLET_RAD;
	_IsActive = true;
	_IsForward = false;
	_IsBulletActive = false;
	_KnockBackSpd = 0.f;
	_CoinType = eCoin::NONE;
	_BulletHndl = -1;
	_BulletCount = 0;
	_BulletInterval = 0;
}

//ロード
void CEnemyShot::Load() {
	//モデルをコピー
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_SHOT)); }
	if (_BulletHndl == -1) { _BulletHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::BULLET)); }
}

//セット
void CEnemyShot::Set() {
	//比率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_BulletHndl, _BulletScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_BulletHndl, _BulletRot);
	MV1SetPosition(_BulletHndl, _BulletPos);
}

//メイン処理
void CEnemyShot::Step() {
	if (!_IsActive)
		return;

	//原点に平行移動する行列を作成
	MyMatrix OriginMat = MyMatrix::GetTranslateMat(-_Pos);
	//プレイヤーのY軸回転行列を作成
	MyMatrix RotYMat = MyMatrix::GetYawMatrix(_Rot._Y);
	//平行移動する行列を作成
	MyMatrix MoveMat = MyMatrix::GetTranslateMat(_BulletMove);
	//元の位置に戻す平行移動する行列を作成
	MyMatrix ReturnMat = MyMatrix::GetTranslateMat(_Pos);

	//各行列を合成
	MyMatrix CompoundMat;
	CompoundMat = ReturnMat * RotYMat;
	CompoundMat *= MoveMat;
	CompoundMat *= OriginMat;

	Vector3D moveVec = CompoundMat * _Pos;

	moveVec = _Pos.Create(moveVec);

	//敵からプレイヤーまでのベクトル
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	//プレイヤーが影状態以外、索敵範囲内、前方にいるなら追いかける状態へ
	if (moveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, SEARCH_RANGE2) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetState() != CPlayer::ePlayerState::CLIMB &&
		cPlayer->GetDeath() == false) {
		_Rot = Vector3D::VGet(0.0f, atan2f(-playerVec._X, -playerVec._Z), 0.0f);
		_IsForward = true;
	}
	else {
		_Rot._Y = _ResetRot._Y;
		_IsForward = false;
	}

	Shot();

	/*if (_Life <= 0)
		DeathCalc();*/

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//描画
void CEnemyShot::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
	if (_IsBulletActive == true) { MV1DrawModel(_BulletHndl); }
}

//終了
void CEnemyShot::Fin() {
	//コピーモデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_BulletHndl != -1) { MV1DeleteModel(_BulletHndl); _BulletHndl = -1; }
}

//更新処理
void CEnemyShot::Update() {
	//回転角度、座標を更新
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	//回転角度、座標を更新
	MV1SetRotationXYZ(_BulletHndl, _BulletRot);
	MV1SetPosition(_BulletHndl, _BulletPos);
	//回転角度、座標を更新
}

//発射関数
void CEnemyShot::Shot() {
	if (_IsBulletActive == true) {
		//原点に平行移動する行列を作成
		MyMatrix enemyMoveOriginMat = MyMatrix::GetTranslateMat(-_BulletPos);
		//プレイヤーのY軸回転行列を作成
		MyMatrix enemyRotYMat = MyMatrix::GetYawMatrix(_BulletRot._Y);
		//平行移動する行列を作成
		MyMatrix enemyMoveMat = MyMatrix::GetTranslateMat(_BulletMove);
		//元の位置に戻す平行移動する行列を作成
		MyMatrix enemyReturnMat = MyMatrix::GetTranslateMat(_BulletPos);

		//各行列を合成
		MyMatrix playerCompoundMat = enemyReturnMat * enemyRotYMat;
		playerCompoundMat *= enemyMoveMat;
		playerCompoundMat *= enemyMoveOriginMat;

		//座標に行列を掛けて弾の座標を算出
		_BulletPos = playerCompoundMat * _BulletPos;

		_BulletCount--;
	}

	if (_BulletCount <= 0) {
		_IsBulletActive = false;
		_BulletInterval++;
	}

	if (_BulletInterval > BULLET_INTERVAL) {
		BulletRequest();
		_BulletInterval = 0;
	}
}

//弾リクエスト
void CEnemyShot::BulletRequest() {
	if (_IsBulletActive == true) {
		return;
	}

	if (_IsActive == true) {
		_IsBulletActive = true;

		//プレイヤーと近いなら音を出す
		if (MyLib::Abs(cPlayer->GetPos().Long(_Pos)) < SOUND_RANGE) {
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENSHOT);
		}

		_BulletCount = BULLET_MAX_COUNT;

		//原点に平行移動する行列を作成
		MyMatrix OriginMat = MyMatrix::GetTranslateMat(-_Pos);
		//プレイヤーのY軸回転行列を作成
		_BulletRot._Y = _Rot._Y;
		MyMatrix RotYMat = MyMatrix::GetYawMatrix(_BulletRot._Y);
		//平行移動する行列を作成
		MyMatrix MoveMat = MyMatrix::GetTranslateMat(BULLET_SHOT_POS);
		//元の位置に戻す平行移動する行列を作成
		MyMatrix ReturnMat = MyMatrix::GetTranslateMat(_Pos);

		//各行列を合成
		MyMatrix CompoundMat;
		CompoundMat = ReturnMat * RotYMat;
		CompoundMat *= MoveMat;
		CompoundMat *= OriginMat;

		//座標に行列を掛けて弾の座標を算出
		_BulletPos = CompoundMat * _Pos;
	}
}

//ヒット関数
void CEnemyShot::HitCalc() {
	_Rot = Vector3D::ZeroVec();					//回転角度初期化
	_State = eEnemyState::NORMAL;				//通常状態へ
}

