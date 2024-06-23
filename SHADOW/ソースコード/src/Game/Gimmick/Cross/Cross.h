#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"
#include "../../Library/Vector/Vector3D.h"

//十字クラス
class CCross : public CGimmickObj {
public:
	//コンストラクタ・デストラクタ
	CCross();
	~CCross();

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
	//ヒット関数
	void HitCalc();
};
