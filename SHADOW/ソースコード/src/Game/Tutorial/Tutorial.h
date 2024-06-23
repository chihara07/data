#pragma once

#include "DxLib.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr int HNDL_NUM = 21;

class CTutorial {
private:
	static CTutorial* _Instance;

	//コンストラクタ・デストラクタ
	CTutorial();
	~CTutorial();

	//シングルトンなので他での生成を禁止
	CTutorial(const CTutorial& other);
	CTutorial operator= (const CTutorial& other) {}

	bool _IsTutorial;		//チュートリアル中か
	bool _IsPressed;		//押されたか
	PATH_TYPE _TutorialEnd;	//チュートリアルの最後
	PATH_TYPE _HndlID;		//ハンドルID
public:
	//インスタンス取得
	static CTutorial* GetInstance();
	//インスタンス削除
	static void DeleteInstance();
	//初期化
	void Init();
	//ロード
	void Load();
	//ステップ
	void Step();
	//描画
	void Draw();
	//終了
	void Fin();
	//チュートリアルを進める
	void AdvanceTutorial();
	//チュートリアル中か取得
	const bool GetTutorial() { return _IsTutorial; }
	//チュートリアル中かセット
	void SetTutorial(bool f) { _IsTutorial = f; }
	//押されたかセット
	void SetPressed(bool f) { _IsPressed = f; }
};