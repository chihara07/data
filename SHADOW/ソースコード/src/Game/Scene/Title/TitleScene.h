#pragma once
#include "../../Object/SceneObj.h"
#include "../../Game/Hndl/HndlManager.h"

//タイトルシーンクラス
class CTitleScene : public CSceneObj {
private:
	PATH_TYPE _GraphID;			//画像
	int _Interval;				//インターバル
public:
	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();

	//コンストラクタ・デストラクタ
	CTitleScene();
	~CTitleScene();

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
