#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

//敵クラス
class CCoin {
public:
	//敵の種類用列挙型
	enum class eCoinType {
		NONE,		//不所持
		HAVE,		//所持

		NUM,
	};
private:
	Vector3D _Pos;			//座標1
	Vector3D _Rot;			//コイン回転角度
	Vector3D _Scale;		//拡大率
	int _Hndl;				//ハンドル
	float _Rad;				//半径
	bool _IsActive;			//コイン生存フラグ
	eCoinType _CoinType;	//敵の種類
public:
	//コンストラクタ・デストラクタ
	CCoin();
	~CCoin();

	//初期化
	void Init();
	//セット
	void Set();
	//ロード
	void Load(int coin_hndl);
	//メイン処理
	void Step();
	//描画
	void Draw();
	//終了
	void Fin();
	//当たり判定
	void Collision();
	//更新処理
	void Update();

	//座標取得
	Vector3D GetPos() { return _Pos; }
	//座標セット
	void SetPos(Vector3D v) { _Pos = v; }
	//半径取得
	const float GetRad() { return _Rad; }
	//生存フラグ取得
	const bool GetActive() { return _IsActive; }
	//生存フラグセット
	void SetActive(bool f) { _IsActive = f; }
	//種類取得
	const eCoinType GetCoinType() { return _CoinType; }
	//種類セット
	void SetCoinType(eCoinType t) { _CoinType = t; }
};
