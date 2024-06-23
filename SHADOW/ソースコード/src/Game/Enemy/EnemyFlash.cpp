#include "EnemyFlash.h"
#include <math.h>
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Input/Input.h"
#include "../../Library/Sound/SoundManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Collision/Collision.h"
#include "../../Game/Player/Player.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Sound/SoundManager.h"

constexpr float FLASH_SCALE = 0.7f;		//フラッシュ攻撃拡大率
constexpr float FLASH_RAD = 70.f;		//フラッシュ攻撃半径
constexpr int FLASH_COUNT_MAX = 60;		//フラッシュ攻撃カウント最大値

//コンストラクタ・デストラクタ
CEnemyFlash::CEnemyFlash(){
	_FlashScale = Vector3D::ZeroVec();
	_IsForward = false;
	_KnockBackSpd = 0.f;
	_SearchRange = 0.f;
	_CoinType = eCoin::NONE;
	_NearType = eNearType::PLAYER;
	_FlashHndl = -1;
	_FlashRad = 0.f;
	_FlashCount = 0;
	_IsFlashActive = false;
	_IsFlashStandby = false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_IsFindArea[area_index] = false;
		_HitArea[area_index] = false;
	}
	_DiscoveryCount = 0;
}
CEnemyFlash::~CEnemyFlash() {
	Fin();
}

//初期化
void CEnemyFlash::Init() {
	_Pos = Vector3D::ZeroVec();
	_MovePos1 = Vector3D::ZeroVec();
	_MovePos2 = Vector3D::ZeroVec();
	_MoveVec = Vector3D::ZeroVec();
	_LimitCenterPos = Vector3D::ZeroVec();
	_LimitDistance = Vector2D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_FlashScale(FLASH_SCALE);
	_FlashRad = FLASH_RAD;
	_FlashCount = 0;
	_DiscoveryCount = 0;
	_MoveID = eEnemyMoveState::MOVE_STATE_1;
	_NearType = eNearType::PLAYER;
	_Scale = ENEMY_SCALE;
	_Hndl = -1;
	_FlashHndl = -1;
	_Spd = ENEMY_SPD;
	_KnockBackSpd = KNOCKBACK_SPD;
	_SearchRange = SEARCH_RANGE;
	_Rad = ENEMY_RAD;
	_IsActive = true;
	_IsForward = false;
	_IsFlashActive = false;
	_IsFlashStandby = false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_HitArea[area_index] = false;
	}
	_State = eEnemyState::NORMAL;
	_CoinType = eCoin::NONE;
}

//ロード
void CEnemyFlash::Load() {
	//モデルをコピー
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::ENEMY_FLASH)); }
	if (_FlashHndl == -1) { _FlashHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::FLASH_AREA)); }
}

//セット
void CEnemyFlash::Set() {
	//比率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetScale(_FlashHndl, _FlashScale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetRotationXYZ(_FlashHndl, _Rot);
	MV1SetPosition(_FlashHndl, _Pos);
}

//メイン処理
void CEnemyFlash::Step() {
	if (!_IsActive)
		return;
	//移動関数実行
	Move();
	//影エリアのチェック
	CheckArea();
	//状態変化関数実行
	ChangeState();

	if (CPlayer::GetInstance()->GetDeath() == true) {
		HitCalc();
	}
}

//描画
void CEnemyFlash::Draw() {
	if (_IsActive == true) { MV1DrawModel(_Hndl); }
	if (_IsActive == true && (_IsFlashStandby == true || _IsFlashActive == true)) { MV1DrawModel(_FlashHndl); }
	if (_State == eEnemyState::DISCOVERY && _IsActive == true)
		CDrawManager::GetInstance()->Draw(PATH_TYPE::DISCOVERY, VGet(_Pos._X, _Pos._Y + DISCOVERY_GRAPH_HEIGHT, _Pos._Z),
			DISCOVERY_GRAPH_POS._X, DISCOVERY_GRAPH_POS._Y, DISCOVERY_GRAPH_SIZE, 0.f);
}

//終了
void CEnemyFlash::Fin() {
	//コピーモデル破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	if (_FlashHndl != -1) { MV1DeleteModel(_FlashHndl); _FlashHndl = -1; }
}

//更新処理
void CEnemyFlash::Update() {
	//回転角度、座標を更新
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	MV1SetPosition(_FlashHndl, _Pos);
	MV1SetScale(_FlashHndl, _FlashScale);
	//回転角度、座標を更新
}

//移動関数
void CEnemyFlash::Move() {
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
void CEnemyFlash::ChangeState() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//敵からプレイヤーまでのベクトル
	Vector3D playerVec = _Pos.Create(cPlayer->GetPos());

	_IsForward = false;

	if (IsFlash()) {
		_State = eEnemyState::FLASH;
	}
	else if (_MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true
		&& cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _DiscoveryCount < DISCOVERY_MAX_COUNT) {
		_State = eEnemyState::DISCOVERY;

		if (_OldID == eEnemyMoveState::MOVE_STATE_1)
			_MoveID = eEnemyMoveState::MOVE_STATE_2;
		else if (_OldID == eEnemyMoveState::MOVE_STATE_2)
			_MoveID = eEnemyMoveState::MOVE_STATE_1;

		_OldID = eEnemyMoveState::NON;
	}
	//プレイヤーが影状態以外、索敵範囲内、前方にいるなら追いかける状態へ
	else if (cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetDeath() == false && _NearType == eNearType::PLAYER && _DiscoveryCount >= DISCOVERY_MAX_COUNT
		&& _MoveVec.IsSharpAngle(playerVec) == true && CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), _Pos, _SearchRange) == true) {
		_State = eEnemyState::CHASE;
		_IsForward = true;
	}
	else if (IsNearArea()) {
		_State = eEnemyState::CHASE_AREA;
	}
	//追いかける状態でプレイヤーが範囲外なら帰還状態へ
	else if (_State == eEnemyState::CHASE || _State == eEnemyState::CHASE_AREA || _State == eEnemyState::FLASH
		|| _State == eEnemyState::DISCOVERY) {
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

	if (_OldState == eEnemyState::TURN)
		_OldState = eEnemyState::NORMAL;
	else if (_State != eEnemyState::KNOCKBACK && _State != eEnemyState::TURN && _OldState != eEnemyState::TURN) {
		//移動ベクトルから角度を計算し代入
		if (_MoveVec._X * _MoveVec._X >= MyLib::TOLERANCE || _MoveVec._Z * _MoveVec._Z >= MyLib::TOLERANCE) {
			_Rot = VGet(0.f, atan2f(-_MoveVec._X, -_MoveVec._Z), 0.f);
		}
	}

	if (_State == eEnemyState::CHASE || _State == eEnemyState::DISCOVERY)
		_SearchRange = SEARCH_RANGE2;
	else
		_SearchRange = SEARCH_RANGE;
}

//影エリアを追いかけている状態関数
void CEnemyFlash::ChaseAreaAct() {
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	if (_IsFindArea[static_cast<int>(_NearType)] == true) {
		//影エリアまでのベクトルを求めて移動速度分進める
		_SavePos = _Pos;
		_AreaChaseVec = _SavePos.Create(cPlayerAttack->GetAreaPos(static_cast<int>(_NearType)));
		_AreaChaseVec.Normalize();
		_SavePos = Vector3D::VGet(_AreaChaseVec._X * ENEMY_CHASE_SPD, 0.f, _AreaChaseVec._Z * ENEMY_CHASE_SPD);
		_SavePos += _Pos;

		//追いかけるベクトルを敵の移動ベクトルに代入
		_MoveVec = _AreaChaseVec;
	}
}
//攻撃状態関数
void CEnemyFlash::AttackAct() {
	if (_IsFlashStandby == true) {
		_FlashScale -= (FLASH_SCALE / static_cast<float>(FLASH_COUNT_MAX));
		if (_FlashScale._X < 0.f) {
			_IsFlashStandby = false;
			_IsFlashActive = true;
			CSoundManager::Stop(CSoundManager::eSoundID::SE_ENCHARGE);
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENFLASH);
			_FlashScale(FLASH_SCALE);
		}
	}
	else if (_IsFlashActive == true) {
		_FlashCount++;

		if (_FlashCount > FLASH_COUNT_MAX) {
			_IsFlashActive = false;
			_FlashCount = 0;
			for (int area_index = 0; area_index < AREA_NUM; area_index++) {
				_HitArea[area_index] = false;
			}
		}
	}
}

//索敵範囲に影エリアがあるか
bool CEnemyFlash::CheckPlayerAreaLength(int id) {
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	//渡されたID以外をいれる
	int otherID[AREA_NUM][2] = {
		{1,2},
		{0,2},
		{0,1}
	};

	if(cPlayerAttack->GetAreaActive(id) == false)
		return false;

	if ((cPlayerAttack->GetAreaActive(otherID[id][0]) == false ||
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(id)) - cPlayerAttack->GetAreaRad(id)) <=
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(otherID[id][0])) - cPlayerAttack->GetAreaRad(otherID[id][0]))) &&
		(cPlayerAttack->GetAreaActive(otherID[id][1]) == false ||
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(id)) - cPlayerAttack->GetAreaRad(id)) <=
		MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(otherID[id][1])) - cPlayerAttack->GetAreaRad(otherID[id][1]))))
		return true;

	return false;
}

//影エリアとプレイヤーのどれが近いか
void CEnemyFlash::CheckLength(){
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayerAttack->GetAreaActive(0) == false && cPlayerAttack->GetAreaActive(1) == false &&
		cPlayerAttack->GetAreaActive(2) == false) {
		_NearType = eNearType::PLAYER;
		return;
	}

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (CheckPlayerAreaLength(area_index) == true) {
			if (MyLib::Abs(_Pos.Long(cPlayerAttack->GetAreaPos(area_index)) - cPlayerAttack->GetAreaRad(area_index))
				>= MyLib::Abs(_Pos.Long(cPlayer->GetPos()) - cPlayer->GetRad())) {
				_NearType = eNearType::PLAYER;
			}
			else
				_NearType = static_cast<eNearType>(area_index);
		}
	}
}

//影エリアのチェック
void CEnemyFlash::CheckArea() {
	//プレイヤー攻撃取得
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	//影エリア分回す
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_IsFindArea[area_index] = false;

		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;

		//影エリアに触れていたらフラッシュ攻撃をする
		if (_IsFlashActive == false
			&& CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), _Pos, _Rad) == true) {
			_HitArea[area_index] = true;
			_IsFlashStandby = true;
			CSoundManager::Play(CSoundManager::eSoundID::SE_ENCHARGE);
		}
		//索敵範囲内に影エリアにがあれば発見フラグオン
		else if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), _Pos, SEARCH_RANGE) == true) {
			_IsFindArea[area_index] = true;
		}
	}
	//影エリアとプレイヤーのどれが近いか
	CheckLength();
}

//ヒット関数
void CEnemyFlash::HitCalc() {
	_Pos = _MovePos1;							//座標1へ
	_Rot = Vector3D::ZeroVec();					//回転角度初期化
	_MoveID = eEnemyMoveState::MOVE_STATE_1;	//状態1へ
	_State = eEnemyState::NORMAL;				//通常状態へ
}

//フラッシュ攻撃可能か
bool CEnemyFlash::IsFlash() {
	if (_IsFlashActive) return true;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_HitArea[area_index]) return true;
	}
	return false;
}
//影エリアの方が近いか
bool CEnemyFlash::IsNearArea() {
	if (_NearType == eNearType::PLAYER) return false;
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_IsFindArea[area_index]) return true;
	}
	return false;
}
