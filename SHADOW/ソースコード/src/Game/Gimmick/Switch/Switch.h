#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

constexpr int NEED_COIN_MAX_NUM = 3;	//必要コイン最大数

//スイッチクラス
class CSwitch {
private:
	Vector3D _Pos;						//座標
	Vector3D _Scale;					//比率
	Vector3D _Rot;						//回転角度
	int _Hndl;							//モデルハンドル
	int _PressedHndl;					//押されたモデルハンドル
	int _CoinHndl[NEED_COIN_MAX_NUM];	//コイン画像ハンドル
	int _NeedCoinNum;					//必要コイン枚数
	float _Rad;							//半径
	bool _IsPressed;					//押されたか
	bool _IsHit;						//触れているか
public:
	//コンストラクタ・デストラクタ
	CSwitch();
	~CSwitch();

	//初期化
	void Init();
	//セット
	void Set();
	//ロード
	void Load();
	//メイン処理
	void Step();
	//描画
	void Draw();
	//必要コイン表示
	void HitCalc();
	//終了
	void Fin();
	//更新処理
	void Update();
	//押された関数
	void PressedCalc();

	//座標取得
	Vector3D GetPos() { return _Pos; }
	//押されたかフラグ取得
	bool GetPressed() { return _IsPressed; }
	//座標セット
	void SetPos(Vector3D v) { _Pos = v; }
	//半径取得
	float GetRad() { return _Rad; }
	//必要コイン枚数取得
	int GetNeedCoinNum() { return _NeedCoinNum; }
	//必要コイン枚数セット
	void SetNeedCoinNum(int n) { _NeedCoinNum = n; }
};
