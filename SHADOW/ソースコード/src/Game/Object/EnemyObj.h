#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Coin/CoinManager.h"
#include "../Player/PlayerAttack.h"

constexpr Vector3D ENEMY_SCALE(0.1f, 0.1f, 0.1f);	//敵拡大率
constexpr Vector2D DISCOVERY_GRAPH_POS(0.5f, 0.5f);	//発見マーク座標
constexpr int DISCOVERY_MAX_COUNT = 50;				//移動回数
constexpr int ENEMY_LIFE = 2;						//敵のライフ
constexpr float DISCOVERY_GRAPH_HEIGHT = 20.f;		//発見マークの高さ
constexpr float DISCOVERY_GRAPH_SIZE = 15.f;		//発見マークのサイズ
constexpr float SEARCH_RANGE = 150.0f;				//索敵範囲1
constexpr float SEARCH_RANGE2 = 200.0f;				//索敵範囲2
constexpr float ENEMY_SPD = 1.2f;					//敵の移動速度
constexpr float KNOCKBACK_SPD = 5.f;				//ノックバック速度
constexpr float ENEMY_CHASE_SPD = 2.0f;				//敵の追跡移動速度
constexpr float ENEMY_RAD = 10.0f;					//敵の半径
constexpr float KNOCKBACK_SPD_REDUCE = 0.9f;		//ノックバック速度を減らす量
constexpr float KNOCKBACK_SPD_MIN = 0.1f;			//ノックバック速度最低値
constexpr float TURN_ROT = 6.f;						//振り向き回転角度
constexpr float TURN_ROT_MAX = 180.f;				//振り向き回転角度上限
constexpr float RETURN_ERROR = 2.0f;				//戻るときの誤差

//敵オブジェクトクラス
class CEnemyObj {
public:
	//敵の状態用列挙型
	enum class eEnemyState {
		NORMAL,		//通常状態
		CHASE,		//プレイヤーを追いかけている状態
		CHASE_AREA,	//影エリアを追いかけている状態
		FLASH,		//フラッシュ攻撃
		KNOCKBACK,	//ノックバック
		DISCOVERY,	//プレイヤー発見
		TURN,		//振り向き

		NUM,
	};
	//敵の種類用列挙型
	enum class eCoin {
		NONE,		//通常
		HAVE,		//コイン

		NUM,
	};
	//敵の移動状態用列挙型
	enum class eEnemyMoveState {
		MOVE_STATE_1 = 1,	//状態1
		MOVE_STATE_2,		//状態2

		NON,
	};
	//敵の種類
	enum class eEnemyType {
		NORMAL,
		SHOT,
		FLASH,
		WALL,

		NUM
	};
protected:
	Vector3D _Pos;				//座標
	Vector3D _MovePos1;			//座標1
	Vector3D _MovePos2;			//座標2
	Vector3D _SavePos;			//座標保存
	Vector3D _BulletPos;		//弾座標
	Vector3D _Move;				//移動量
	Vector3D _MoveVec;			//敵の移動ベクトル用
	Vector3D _SaveVec;			//ベクトル保存
	Vector3D _CheckRot;			//回転角度確認
	Vector3D _LimitCenterPos;	//移動制限の中心
	Vector2D _LimitDistance;	//移動制限距離
	Vector3D _Scale;			//拡大率
	Vector3D _Rot;				//回転角度
	Vector3D _ResetRot;			//リセット用回転角度
	int _Hndl;					//モデルハンドル
	int _Size;					//サイズ
	int _Life;					//ライフ
	float _Rad;					//半径
	float _BulletRad;			//弾半径
	float _FlashRad;			//フラッシュ攻撃半径
	float _Spd;					//移動速度
	bool _IsActive;				//生存フラグ
	bool _IsBulletActive;		//弾生存フラグ
	bool _IsFlashActive;		//フラッシュ攻撃生存フラグ
	float _KnockBackSpd;		//ノックバックスピード
	float _SearchRange;			//索敵範囲
	float _SaveRotY;			//Y軸角度保存
	int _DiscoveryCount;		//発見カウント
	bool _IsForward;			//前方フラグ
	bool _HitArea[AREA_NUM];	//影エリアに触れてるか
	eEnemyState _State;		//敵の状態
	eEnemyState _OldState;	//古い状態
	eCoin _CoinType;			//コインびの有無
	eEnemyType _Type;			//敵の種類
	eEnemyMoveState _MoveID;	//動きID
	eEnemyMoveState _OldID;	//古いID

	CCoin* cCoin;				//コインポインタ
public:
	//コンストラクタ・デストラクタ
	CEnemyObj():_Hndl(-1), _IsActive(), _Size(), _Rad(), _Spd(), _Life(), _KnockBackSpd(),
		_SearchRange(), _SaveRotY(), _DiscoveryCount(), _IsForward(), _State(), _OldState(),
		_CoinType(), _MoveID(), _OldID(), cCoin() {};
	~CEnemyObj() {};

	//初期化
	virtual void Init() = 0;
	//ロード
	virtual void Load() = 0;
	//セット
	virtual void Set() = 0;
	//メイン処理
	virtual void Step() = 0;
	//描画
	virtual void Draw() = 0;
	//終了
	virtual void Fin() = 0;
	//更新処理
	virtual void Update() = 0;
	//ヒット関数
	virtual void HitCalc() = 0;
	//死亡関数
	virtual void DeathCalc();
	//移動関数
	virtual void Move() {};
	//状態変化関数
	virtual void ChangeState() {};
	//通常状態アクション関数
	virtual void NormalAct();
	//プレイヤーを追いかけている状態関数
	virtual void ChaseAct();
	//影エリアを追いかけている状態関数
	virtual void ChaseAreaAct() {};
	//攻撃状態関数
	virtual void AttackAct() {};
	//ノックバック状態関数
	virtual void KnockBackAct();
	//プレイヤー発見状態関数
	virtual void DiscoveryAct();
	//振り向き状態関数
	virtual void TurnAct();
	/// <summary>
	/// 目的地に向かう関数
	/// </summary>
	/// <param name="destination">目的地座標</param>
	/// <param name="spd">移動速度</param>
	void HeadToDestination(Vector3D destination, Vector3D spd);

	//座標取得
	Vector3D GetPos() { return _Pos; }
	//座標セット
	void SetPos(Vector3D v) { _Pos = v; }
	//弾座標取得
	Vector3D GetBulletPos() { return _BulletPos; }
	//弾座標セット
	void SetBulletPos(Vector3D v) { _BulletPos = v; }
	//回転角度セット
	void SetRot(Vector3D r) { _Rot = r; }
	//リセット回転角度セット
	void SetResetRot(Vector3D r) { _ResetRot = r; }
	//移動ベクトルセット
	void SetMoveVec(Vector3D v) { _MoveVec = v; }
	//座標セット
	void SetLimitCenterPos(Vector3D v) { _LimitCenterPos = v; }
	//座標セット
	void SetLimitDistance(Vector2D v) { _LimitDistance = v; }
	//座標セット
	void SetMovePos1(Vector3D v) { _MovePos1 = v; }
	//座標セット
	void SetMovePos2(Vector3D v) { _MovePos2 = v; }
	//生存フラグ取得
	const bool GetActive() { return _IsActive; }
	//前方フラグ取得
	const bool GetForward() { return _IsForward; }
	//半径取得
	const float GetRad() { return _Rad; }
	//状態取得
	const eEnemyState GetState() { return _State; }
	//状態セット
	void SetState(eEnemyState s) { _State = s; }
	//コイン種類取得
	const eCoin GetCoinType() { return _CoinType; }
	//種類取得
	const eEnemyType GetType() { return _Type; }
	//コイン種類セット
	void SetCoinType(eCoin t) { _CoinType = t; }
	//種類セット
	void SetType(eEnemyType t) { _Type = t; }
	//ライフ現象
	void SubLife() { _Life--; }
	//コインセット
	void SetCoin(CCoin* c) { cCoin = c; }
	//生存フラグ取得
	const bool GetBulletActive() { return _IsBulletActive; }
	//半径取得
	const float GetBulletRad() { return _BulletRad; }
	//フラッシュ攻撃生存フラグ取得
	const bool GetFlashActive() { return _IsFlashActive; }
	//フラッシュ攻撃半径取得
	const float GetFlashRad() { return _FlashRad; }
	//影エリア触れているかセット
	void SetHitArea(int id, bool f) { _HitArea[id] = f; }

	//アクション切り替え関数ポインタ
	void (CEnemyObj::* ActFunc[static_cast<int>(eEnemyState::NUM)])() = {
		&CEnemyObj::NormalAct,
		&CEnemyObj::ChaseAct,
		&CEnemyObj::ChaseAreaAct,
		&CEnemyObj::AttackAct,
		&CEnemyObj::KnockBackAct,
		&CEnemyObj::DiscoveryAct,
		&CEnemyObj::TurnAct };
};