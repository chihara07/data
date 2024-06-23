#pragma once
#include "Play/PlayScene.h"
#include "Title/TitleScene.h"
#include "Clear/ClearScene.h"
#include "GameOver/GameOverScene.h"
#include "../../Library/Sound/SoundManager.h"

//シーンマネージャークラス
class CSceneManager {
public:
	//現在のシーン
	enum class eScene {
		TITLE = 1,
		PLAY,
		GAME_CLEAR,
		GAME_OVER
	};
	//シーンの状態
	enum class eManagerState {
		INIT,
		MAIN,
		FIN,

		NUM
	};
private:
	int _PlayID;
	eManagerState _State;
	CSceneObj* _Scene;

	eScene _SceneID;
public:
	//コンストラクタ・デストラクタ
	CSceneManager();
	~CSceneManager();

	//ループ処理
	void Loop() { (this->*LoopSwitchFunc[static_cast<int>(_State)])(); }
	//初期化
	void Init();
	//メイン
	void Main();
	//終了
	void Fin();
	//描画処理
	void Draw();
	//シーン生成
	void CreateScene(eScene id);

	//ループ切り替え関数ポインタ
	void (CSceneManager::* LoopSwitchFunc[static_cast<int>(eManagerState::NUM)])() =
	{ &CSceneManager::Init, &CSceneManager::Main, &CSceneManager::Fin };
};
