#pragma once

constexpr float BGM_VOLUME = 0.5f;						//BGM音量

//タイトルシーンクラス
class CSceneObj {
public:
	//ゲーム中の流れ
	enum class eKind {
		SCENE_INIT,		//初期化
		SCENE_LOAD,		//ロード
		SCENE_LOOP,		//ループ
		SCENE_EXIT,		//終了

		SCENE_NUM
	};

	eKind _SceneID;		//シーンID

	bool _IsEnd = false;	//終了フラグ
public:
	//繰り返し行う処理
	virtual int Loop() { return 0; }
	//描画処理
	virtual void Draw() {};

	//コンストラクタ・デストラクタ
	CSceneObj() {};
	virtual ~CSceneObj() {};

public:
	//初期化
	virtual void Init() {};

	//メイン処理
	virtual void Step() {};

	//ロード処理
	virtual void Load() {};

	//後処理
	virtual void Fin() {};

public:
	//タイトルシーン切り替え関数ポインタ
	void (CSceneObj::* SceneSwitchFunc[static_cast<int>(eKind::SCENE_NUM)])() =
	{ &CSceneObj::Init, &CSceneObj::Load, &CSceneObj::Step, &CSceneObj::Fin };
};
