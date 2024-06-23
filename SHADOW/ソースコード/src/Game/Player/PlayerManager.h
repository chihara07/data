#pragma once
#include "PlayerUI.h"
#include "Player.h"
#include "PlayerAttack.h"

//プレイヤーマネージャークラス
class CPlayerManager {
private:
	CPlayer* cPlayer = CPlayer::GetInstance();
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayerUI cPlayerUI;
public:
	//コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init();
	//ロード
	void Load();
	//セット
	void Set();
	//メイン処理
	void Step();
	//当たり判定
	void Collision(int map_hndl);
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//破棄
	void Delete();
};
