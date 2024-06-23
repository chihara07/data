#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../Coin/CoinManager.h"

//敵クラス
class CEnemy : public CEnemyObj {
public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

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
	//ヒット関数
	void HitCalc();
	//更新処理
	void Update();
	//移動関数
	void Move();
	//状態変化関数
	void ChangeState();
};
