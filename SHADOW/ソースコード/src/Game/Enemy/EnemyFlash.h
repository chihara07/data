#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"

//敵クラス
class CEnemyFlash : public CEnemyObj {
public:
	//敵に近いもの用列挙型
	enum class eNearType {
		AREA1 = 0,
		AREA2,
		AREA3,
		PLAYER,
	};
private:
	Vector3D _FlashScale;		//フラッシュ攻撃拡大率
	Vector3D _AreaChaseVec;		//影エリアを追うベクトル用
	int _FlashCount;			//フラッシュ攻撃カウント
	int _FlashHndl;				//フラッシュ攻撃ハンドル
	bool _IsFlashStandby;		//フラッシュ攻撃準備フラグ
	bool _IsFindArea[AREA_NUM];	//影エリア発見フラグ
	eNearType _NearType;		//近い物の種類
public:
	//コンストラクタ・デストラクタ
	CEnemyFlash();
	~CEnemyFlash();

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
	//影エリアを追いかけている状態関数
	void ChaseAreaAct();
	//攻撃状態関数
	void AttackAct();
	//索敵範囲に影エリアがあるか
	bool CheckPlayerAreaLength(int id);
	//影エリアとプレイヤーのどれが近いか
	void CheckLength();
	//影エリアのチェック
	void CheckArea();
	//フラッシュ攻撃可能か
	bool IsFlash();
	//影エリアの方が近いか
	bool IsNearArea();
};
