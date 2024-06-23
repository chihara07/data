#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"

//敵クラス
class CEnemyWall : public CEnemyObj {
public:
	//コンストラクタ・デストラクタ
	CEnemyWall();
	~CEnemyWall();

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
	//死亡関数
	void DeathCalc();
	//更新処理
	void Update();
	//移動関数
	void Move();
	//状態変化関数
	void ChangeState();

	//通常状態アクション関数
	void NormalAct();
	//プレイヤーを追いかけている状態関数
	void ChaseAct();
};
