#include "Enemy.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Hndl/HndlManager.h"
#include "../../Game/Draw/DrawManager.h"

//コンストラクタ・デストラクタ
CEnemy::CEnemy() {
	_IsForward = false;
	_KnockBackSpd = 0.f;
	_SearchRange = 0.f;
	_SaveRotY = 0.f;
	_CoinType = eCoin::NONE;
	_DiscoveryCount = 0;
	cCoin = nullptr;
}
CEnemy::~CEnemy() {
	Fin();
}

//初期化
void CEnemy::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_SaveVec = Vector3D::ZeroVec();
	_LimitCenterPos = Vector3D::ZeroVec();
	_LimitDistance = Vector2D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = ENEMY_SCALE;
	_Hndl = -1;
	_DiscoveryCount = 0;
	_Spd = ENEMY_SPD;
	_SearchRange = SEARCH_RANGE;
	_KnockBackSpd = KNOCKBACK_SPD;
	_Rad = ENEMY_RAD;
	_SaveRotY = 0.f;
	_Life = ENEMY_LIFE;
	_IsActive = true;
	_IsForward = false;
	_State = eEnemyState::NORMAL;
	_OldState = eEnemyState::NORMAL;
	_CoinType = eCoin::NONE;
	_MoveID = eEnemyMoveState::MOVE_STATE_1;
	_OldID = eEnemyMoveState::NON;
}

//ロード
void CEnemy::Load() {
	//モデルをコピー
	if (_Hndl == -1){ _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY)); }
}

//セット
void CEnemy::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//メイン処理
void CEnemy::Step() {
	if (!_IsActive)
		return;
	//移動関数実行
	Move();
	//状態変化関数実行
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//描画
void CEnemy::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }

	if(_State == eEnemyState::DISCOVERY && _IsActive == true)
		CDrawManager::GetInstance()->Draw(PATH_TYPE::DISCOVERY, VGet(_Pos._X, _Pos._Y + DISCOVERY_GRAPH_HEIGHT, _Pos._Z), 
											DISCOVERY_GRAPH_POS._X, DISCOVERY_GRAPH_POS._Y, DISCOVERY_GRAPH_SIZE, 0.f);
}

//終了
void CEnemy::Fin() {
	//コピーモデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//更新処理
void CEnemy::Update() {
	//回転角度、座標を更新
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
}

//移動関数
void CEnemy::Move() {
	(this->*ActFunc[static_cast<int>(_State)])();

	//移動制限処理
	if (_SavePos._X > _LimitCenterPos._X + _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X + _LimitDistance._X;
	if (_SavePos._X < _LimitCenterPos._X - _LimitDistance._X)
		_SavePos._X = _LimitCenterPos._X - _LimitDistance._X;
	if (_SavePos._Z > _LimitCenterPos._Z + _LimitDistance._Y)
		_SavePos._Z = _LimitCenterPos._Z + _LimitDistance._Y;
	if (_SavePos._Z < _LimitCenterPos._Z - _LimitDistance._Y)
		_SavePos._Z = _LimitCenterPos._Z - _LimitDistance._Y;

	//敵の座標を代入
	_Pos = _SavePos;
}

//状態変化関数
void CEnemy::ChangeState() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//敵からプレイヤーまでのベクトル
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	//プレイヤーが影状態以外、索敵範囲内、前方にいるなら発見状態へ
	if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount < DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::DISCOVERY;
		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_OldID = eEnemyMoveState::NON;
	}
	//プレイヤーが影状態以外、索敵範囲内、前方にいる、発見カウントがたまったらなら追いかける状態へ
	else if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount >= DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	//追いかける状態でプレイヤーが範囲外なら振り向き状態へ
	else if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY) {
		if (MyLib::Abs(_Pos.Long(_MovePos1)) < MyLib::Abs(_Pos.Long(_MovePos2))) {
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
			_OldID = eEnemyMoveState::MOVE_STATE_1;
			_SaveVec = _Pos.Create(_MovePos1);
		}
		else {
			_MoveID = eEnemyMoveState::MOVE_STATE_1;
			_OldID = eEnemyMoveState::MOVE_STATE_2;
			_SaveVec = _Pos.Create(_MovePos2);
		}

		_State = eEnemyState::TURN;
		_OldState = eEnemyState::CHASE;


		_SaveRotY = atan2f(-_SaveVec._X, -_SaveVec._Z);

		_DiscoveryCount = 0;
	}

	//前の状態が振り向き状態なら前の状態を通常状態へ
	if (_OldState == eEnemyState::TURN)
		_OldState = eEnemyState::NORMAL;
	//移動しているか
	else if (_State != eEnemyState::KNOCKBACK && _State != eEnemyState::TURN && _OldState != eEnemyState::TURN) {
		//移動しているなら移動ベクトルから角度を計算し代入
		if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Z * _MoveVec._Z >= MyLib::TOLERANCE) {
			_Rot = VGet(0.0f, atan2f(-_MoveVec._X, -_MoveVec._Z), 0.0f);
		}
	}

	//状態によって索敵範囲を変える
	if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY)
		_SearchRange = SEARCH_RANGE2;
	else
		_SearchRange = SEARCH_RANGE;

}

//ヒット関数
void CEnemy::HitCalc(){
	_Pos = _MovePos1;							//座標1へ
	_Rot = Vector3D::ZeroVec();					//回転角度初期化
	_MoveID = eEnemyMoveState::MOVE_STATE_1;	//状態1へ
	_State = eEnemyState::NORMAL;				//通常状態へ
}

