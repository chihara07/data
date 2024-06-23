#pragma once

#include "DxLib.h"
#include <vector>
#include "Path.h"

class CHndlManager {
private:
	static CHndlManager* _Instance;		//インスタンス

	//コンストラクタ・デストラクタ
	CHndlManager();
	~CHndlManager();

	//シングルトンなので他での生成を禁止
	CHndlManager(const CHndlManager& other);
	CHndlManager operator= (const CHndlManager& other) {}

	std::vector<int> _Hndl;			//ハンドル格納用リスト
	std::vector<int> _ModelHndl;	//モデルハンドル格納用リスト
public:
	//インスタンス取得
	static CHndlManager* GetInstance();
	//インスタンス削除
	static void DeleteInstance();
	//初期化
	void Init();
	//リセット
	void Reset();
	//ロード
	void Load();
	//ハンドル取得
	int GetHndl(PATH_TYPE id);
	//モデルハンドル取得
	int GetModelHndl(MODEL_PATH_TYPE id);
};