#pragma once
#include <DxLib.h>
#include "../../Library/Vector/Vector3D.h"

//バックグラウンドクラス
class CBg {
private:
	int _Hndl;				//フィールド画像ハンドル
	int _ColHndl;			//当たり判定ハンドル
	Vector3D _Pos;			//フィールド座標
	Vector3D _Scale;		//フィールド比率
	Vector3D _Rot;			//フィールド回転角度
	int _SkyHndl;			//天球画像ハンドル
	Vector3D _SkyPos;		//天球座標
	Vector3D _SkyScale;		//天球比率
	Vector3D _SkyRot;		//天球回転角度
public:
	//コンストラクタ・デストラクタ
	CBg();
	~CBg();

	//初期化処理
	void Init();

	//ロード処理
	void Load();

	//セット
	void Set();

	//終了処理
	void Fin();

	//メイン処理
	void Step();

	//描画処理
	void Draw();

	//アップデート処理
	void Update();

	//ハンドル取得
	int GetHndl() { return _ColHndl; }

	//回転角度セット
	void SetRot(Vector3D r) { _Rot = r; }
};
