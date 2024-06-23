#pragma once
#include "DxLib.h"
#include "../../Game/Coin/Coin.h"
#include "../../Library/File/File.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

//コインのモデルパス
constexpr char COIN_PATH[] = "data/Enemy/coin.x";

//敵マネージャークラス
class CCoinManager {
private:
	//コンストラクタ・デストラクタ
	CCoinManager();
	~CCoinManager();

	static CCoinManager* _Instance;		//インスタンス

	//シングルトンなので他での生成を禁止
	CCoinManager(const CCoinManager& other);
	CCoinManager operator= (const CCoinManager& other) {}

	int _Hndl;							//ハンドル
public:
	//インスタンス取得
	static CCoinManager* GetInstance();

	//インスタンス削除
	static void DeleteInstance();

	//初期化
	void Init();
	//ロード
	void Load();
	//セット
	void Set();
	//メイン処理
	void Step();
	//当たり判定
	void Collision();
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//コインクラス生成
	CCoin* CreateCoin() {
		CCoin* result = nullptr;
		result = New CCoin();
		_CoinList.push_back(result);
		return result;
	}
	//指定のコイン削除
	void DeleteCoin(const CCoin* p) {
		for (auto coin_itr = _CoinList.begin(); coin_itr != _CoinList.end(); ++coin_itr) {
			auto coin = *coin_itr;
			if (coin != p)
				continue;
			delete p;
			_CoinList.erase(coin_itr);
			break;
		}
	}

	list<CCoin*> _CoinList;		//コインクラス格納リスト
};