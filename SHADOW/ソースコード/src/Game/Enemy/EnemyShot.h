#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../../Game/Player/Player.h"

//敵クラス
class CEnemyShot : public CEnemyObj {
private:
	Vector3D _BulletMove;		//弾移動ベクトル
	Vector3D _BulletRot;		//弾回転角度
	Vector3D _BulletScale;		//弾拡大率
	int _BulletHndl;			//弾ハンドル
	int _BulletCount;			//弾カウント
	int _BulletInterval;		//弾インターバル
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
public:
	//コンストラクタ・デストラクタ
	CEnemyShot();
	~CEnemyShot();

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
	//発射関数
	void Shot();
	//弾リクエスト
	void BulletRequest();
};
