#pragma once
#include "DxLib.h"
#include "Player.h"
#include "../../Library/Vector/Vector3D.h"

constexpr int ATTACK_NUM = 2;						//攻撃の数
constexpr int AREA_NUM = 3;							//影エリアの数
constexpr float AREA_ENERGY_MAX = 600.f;			//影エリア最大エネルギー量

class CPlayerAttack {
private:
	static CPlayerAttack* _Instance;		//インスタンス

	//コンストラクタ・デストラクタ
	CPlayerAttack();
	~CPlayerAttack();

	//シングルトンなので他での生成を禁止
	CPlayerAttack(const CPlayerAttack& other);
	CPlayerAttack operator= (const CPlayerAttack& other) {}
public:
	//インスタンス取得
	static CPlayerAttack* GetInstance();
	//インスタンス削除
	static void DeleteInstance();
private:
	Vector3D _Pos[ATTACK_NUM];		//座標
	Vector3D _AreaPos[AREA_NUM];	//影エリア座標
	Vector3D _Scale;				//拡大率
	Vector3D _AreaScale[AREA_NUM];	//影エリア拡大率
	float _Rad;						//半径
	float _AreaRad[AREA_NUM];		//影エリア半径
	int _Cnt;						//カウント
	float _Energy;					//エネルギー
	float _EnergyCnt;				//エネルギーカウント
	float _HoldCnt;					//長押し時間
	int _Interval;					//インターバル
	int _Hndl;						//ハンドル
	int _AreaHndl[AREA_NUM];		//影エリアハンドル
	bool _IsActive;					//生存フラグ
	bool _AreaIsActive[AREA_NUM];	//影エリア生存フラグ
	bool _IsPlayerMove;				//プレイヤーが動いているか
	bool _IsHold;					//長押しされてるか
	bool _IsCharge;					//チャージされてるか
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
public:
	//初期化
	void Init();
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
	//リクエスト
	void Request();
	//影エリアリクエスト
	void AreaRequest(bool f);

	//座標取得
	Vector3D GetPos(int id) { if (id >= ATTACK_NUM) id = ATTACK_NUM - 1; return _Pos[id]; }
	//影エリア座標取得
	Vector3D GetAreaPos(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1; return _AreaPos[id]; }
	//生存フラグ取得
	const bool GetActive() { return _IsActive; }
	//影エリア生存フラグ取得
	const bool GetAreaActive(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1;  return _AreaIsActive[id]; }
	//プレイヤー移動フラグ取得
	const bool GetPlayerMove() { return _IsPlayerMove; }
	//プレイヤー移動フラグセット
	void SetPlayerMove(bool f) { _IsPlayerMove = f; }
	//長押しフラグ取得
	const bool GetHold() { return _IsHold; }
	//長押しフラグセット
	void SetHold(bool f) { _IsHold = f; }
	//チャージフラグ取得
	const bool GetCharge() { return _IsCharge; }
	//半径取得
	const float GetRad() { return _Rad; }
	//長押し時間取得
	const float GetHoldCnt() { return _HoldCnt; }
	//エネルギー取得
	const float GetEnergy() { return _Energy; }
	//エネルギーカウント取得
	const float GetEnergyCnt() { return _EnergyCnt; }
	//エリア半径取得
	float GetAreaRad(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1; return _AreaRad[id]; }
	//指定した影エリアリセット
	void AreaReset(int id);
	//リセット
	void AllReset();
};
