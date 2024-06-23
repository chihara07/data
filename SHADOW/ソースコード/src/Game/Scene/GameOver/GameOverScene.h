#pragma once
#include "../../Object/SceneObj.h"

//ゲームオーバーシーンクラス
class CGameOverScene : public CSceneObj {
public:
	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();

	//コンストラクタ・デストラクタ
	CGameOverScene();
	~CGameOverScene();

private:
	//初期化
	void Init();

	//メイン処理
	void Step();

	//ロード処理
	void Load();

	//後処理
	void Fin();
};
