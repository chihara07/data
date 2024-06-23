#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Gimmick/Switch/Switch.h"
#include "../Gimmick/Switch/SwitchManager.h"
#include "../Camera/Camera.h"

//オブジェクトクラス
class CGimmickObj {
public:
	//ギミックの状態
	enum class eState {
		NORMAL,		//通常状態
		MOVE,		//動く状態
		SPECIAL,	//特殊状態

		NUM,
	};
	//動きの状態
	enum class eMoveState {
		MOVE1,		//動き1
		MOVE2,		//動き2

		NUM,
	};
	//ギミックの種類
	enum class eGimmickType {
		BLOCK,		//ブロック
		FENCE,		//フェンス
		GOAL,		//ゴール
		NOSHADOW,	//影禁止
		TELEPORT,	//テレポート
		TRAP,		//トラップ
		WALL,		//壁
		CROSS,		//十字

		NUM,
	};
protected:
	Vector3D _Pos;				//座標
	Vector3D _MovePos1;			//動き座標1
	Vector3D _MovePos2;			//動き座標2
	Vector3D _SavePos;			//一時保存座標
	Vector3D _MoveVec;			//移動ベクトル
	Vector3D _Scale;			//比率
	Vector3D _CollisionScale;	//比率
	Vector3D _Rot;				//回転角度
	int _Hndl;					//モデルハンドル
	int _CollisionHndl;			//当たり判定モデルハンドル
	bool _IsActive;				//生存フラグ
	float _Spd;					//移動速度
	float _Rad;					//半径
	eState _State;			//ギミックの状態
	eMoveState _MoveID;		//動きID
	eGimmickType _Type;			//ギミックの種類

	CSwitch* _cSwitch;			//スイッチポインタ
public:
	//コンストラクタ・デストラクタ
	CGimmickObj() :_Hndl(-1), _Pos(), _Scale(), _Rot(), _IsActive(), _CollisionHndl(), _MoveID(),
					_Rad(), _Spd(), _State(), _Type(), _cSwitch() {};
	~CGimmickObj() {};

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
	virtual void HitCalc() {};

	//座標取得
	Vector3D GetPos() { return _Pos; }
	//座標セット
	void SetPos(Vector3D v) { _Pos = v; }
	//動き座標1セット
	void SetMovePos1(Vector3D v) { _MovePos1 = v; }
	//動き座標2セット
	void SetMovePos2(Vector3D v) { _MovePos2 = v; }
	//回転角度セット
	void SetRot(Vector3D r) { _Rot = r; }
	//比率セット
	void SetScale(Vector3D s) { _Scale = s; }
	//状態セット
	void SetState(eState s) { _State = s; }
	//動きIDセット
	void SetMoveID(eMoveState id) { _MoveID = id; }
	//生存フラグ取得
	const bool GetActive() { return _IsActive; }
	//生存フラグセット
	void SetActive(bool f) { _IsActive = f; }
	//種類セット
	void SetType(eGimmickType t) { _Type = t; }
	//種類取得
	const eGimmickType GetType() { return _Type; }
	//ハンドル取得
	const int GetHndl() { return _Hndl; }
	//当たり判定ハンドル取得
	const int GetCollisionHndl() { return _CollisionHndl; }
	//半径取得
	const float GetRad() { return _Rad; }
	//速度セット
	void SetSpd(float s) { _Spd = s; }
	//スイッチセット
	void SetSwitch(CSwitch* s) { _cSwitch = s; }
};