#pragma once
#include "DxLib.h"
#include "../../Game/Camera/Camera.h"
#include "../Object/Object.h"

//プレイヤークラス
class CPlayer : public CObj {
private:
	static CPlayer* _Instance;

	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//シングルトンなので他での生成を禁止
	CPlayer(const CPlayer& other);
	CPlayer operator= (const CPlayer& other) {}
public:
	//プレイヤーの状態用列挙型
	enum class ePlayerState {
		NORMAL,
		SHADOW,
		JUMP,
		TELEPORT,
		CLIMB,

		NUM,
	};

	//インスタンス取得
	static CPlayer* GetInstance();
	//インスタンス削除
	static void DeleteInstance();
private:
	Vector3D _SavePos;				//プレイヤー座標保存
	Vector3D _TeleportPos;			//テレポート用座標
	Vector3D _TeleportMove;			//テレポート移動量
	Vector3D _TeleportTargetPos;	//テレポート先の座標
	Vector3D _Forward;				//前向きベクトル
	float _ShadowSpd;				//影移動速度
	float _TeleportSpd;				//テレポート移動速度
	float _Gravity;					//重力
	int _ShadowHndl;				//影状態のハンドル
	int _TeleportHndl;				//テレポートのハンドル
	int _DeathEffectHndl;			//死亡時エフェクトハンドル
	int _ChangeEffectHndl;			//変身時エフェクトハンドル
	int _HaveCoin;					//コイン所持数
	bool _Teleport;					//テレポート出来るか
	bool _IsClimb;					//登れるか
	bool _IsGround;					//地面にいるか
	bool _HitArea;					//エリアに触れているか
	bool _IsClear = false;			//クリアしたか
	bool _IsDeath = false;			//しんだか
	ePlayerState _State;			//プレイヤーの状態
	ePlayerState _OldState;		//前フレームのプレイヤーの状態
public:
	//初期化
	void Init(Vector3D v);
	//ロード
	void Load();
	//セット
	void Set();
	//メイン処理
	void Step();
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//移動関数
	void Move(float rot_y);
	//通常状態のアクション関数
	void NormalAct();
	//影状態のアクション関数
	void ShadowAct();
	//ジャンプ状態のアクション関数
	void JumpAct();
	//テレポート状態のアクション関数
	void TeleportAct();
	//壁のぼり状態のアクション関数
	void ClimbAct();
	//テレポート関数
	void TeleportCalc(Vector3D shadow_pos);
	//死亡関数
	void DeathCalc();
	//リスポーン関数
	void ReSpawn();

	//座標取得
	Vector3D GetPos() { return _Pos; }
	//回転角度得
	Vector3D GetRot() { return _Rot; }
	//座標セット
	void SetPos(Vector3D v) { _Pos = v; }
	//回転角度Xセット
	void SetRotX(float rot_x) { _Rot._X = rot_x; }
	//回転角度Xセット
	void SetRotY(float rot_y) { _Rot._Y = rot_y; }
	//テレポート座標取得
	Vector3D GetTeleportPos() { return _TeleportPos; }
	//テレポート座標セット
	void SetTeleportPos(Vector3D v) { _TeleportPos = v; }
	//前向きベクトル取得
	Vector3D GetForward() { return _Forward; }
	//状態取得
	const ePlayerState GetState() { return _State; }
	//状態セット
	void SetState(ePlayerState s) { _State = s; }
	//コイン取得
	const int GetCoin() { return _HaveCoin; }
	//コイン加算
	void AddCoin() { _HaveCoin++; }
	//コイン減算
	void SubCoin(int n) { _HaveCoin -= n; }
	//生存フラグ取得
	const bool GetActive() { return _IsActive; }
	//テレポートフラグ取得
	const bool GetTeleport() { return _Teleport; }
	//テレポートフラグセット
	void SetTeleport(bool f) { _Teleport = f; }
	//登りフラグ取得
	const bool GetClimb() { return _IsClimb; }
	//登りフラグセット
	void SetClimb(bool f) { _IsClimb = f; }
	//地面にいるかフラグ取得
	const bool GetGround() { return _IsGround; }
	//地面にいるかフラグセット
	void SetGround(bool f) { _IsGround = f; }
	//エリアに触れているかフラグ取得
	const bool GetHitArea() { return _HitArea; }
	//エリアに触れているかフラグセット
	void SetHitArea(bool f) { _HitArea = f; }
	//クリアしたかフラグ取得
	const bool GetClear() { return _IsClear; }
	//クリアしたかフラグセット
	void SetClear(bool f) { _IsClear = f; }
	//死んだかフラグ取得
	const bool GetDeath() { return _IsDeath; }
	//死んだかフラグセット
	void SetDeath(bool f) { _IsDeath = f; }
	//エフェクトハンドル取得
	const int GetEffectHndl() { return _DeathEffectHndl; }
	//エフェクトハンドルセット
	void SetEffectHndl(int hndl) { _DeathEffectHndl = hndl; }
	//半径取得
	const float GetRad() { return _Rad; }

	//アクション切り替え関数ポインタ
	void (CPlayer::* ActFunc[static_cast<int>(ePlayerState::NUM)])() =
	{ &CPlayer::NormalAct, &CPlayer::ShadowAct, &CPlayer::JumpAct, &CPlayer::TeleportAct, &CPlayer::ClimbAct };
};
