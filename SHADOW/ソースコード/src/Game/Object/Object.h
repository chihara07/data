#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

//オブジェクトクラス
class CObj {
protected:
	Vector3D _Pos;		//座標
	Vector3D _Move;		//移動量
	Vector3D _Scale;	//比率
	Vector3D _Rot;		//回転角度
	int _Hndl;			//モデルハンドル
	int _Size;			//サイズ
	int _Life;			//ライフ
	float _Rad;			//半径
	float _Spd;			//移動速度
	bool _IsActive;		//生存フラグ
public:
	//コンストラクタ・デストラクタ
	CObj():_Hndl(-1), _IsActive(), _Size(), _Rad(), _Spd(), _Life() {};
	~CObj() {};

	//初期化
	virtual void Init() {};
	//ロード
	virtual void Load() {};
	//メイン処理
	virtual void Step() {};
	//描画
	virtual void Draw() {};
	//終了
	virtual void Fin() {};
	//更新処理
	virtual void Update() {};

	//ライフ取得
	int GetLife() const { return _Life; }

	void SubLife() { _Life--; }
};