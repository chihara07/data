#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../../Game/Enemy/Enemy.h"
#include "../../Game/Enemy/EnemyFlash.h"
#include "../../Game/Enemy/EnemyShot.h"
#include "../../Game/Enemy/EnemyWall.h"
#include "../../Library/File/File.h"
#include "../Camera/Camera.h"
#include <list>
#include "../../Library/Common.h"
#include "../Coin/CoinManager.h"

using namespace std;

constexpr int ENEMY_NUM0 = 4;		//敵の数
constexpr int ENEMY_NUM = 12;		//敵の数
constexpr int ENEMY_NUM2 = 16;		//stage2の敵の数
constexpr int ENEMY_NUM3 = 11;		//stage3の敵の数
constexpr int ENEMY_NUM4 = 8;		//stage3の敵の数

//敵マネージャークラス
class CEnemyManager {
private:
	//敵データ
	enum class eEnemyData {
		ID = 0,				//番号
		VEC_X,				//ベクトル1X
		VEC_Y,				//ベクトル1Y
		VEC_Z,				//ベクトル1Z
		VEC2_X,				//ベクトル2X
		VEC2_Y,				//ベクトル2Y
		VEC2_Z,				//ベクトル2Z
		LIMIT_POS_X,		//移動制限X座標
		LIMIT_POS_Z,		//移動制限Z座標
		LIMIT_DIS_X,		//移動制限X距離
		LIMIT_DIS_Y,		//移動制限Y距離
		TYPE,				//種類
		COIN_TYPE,			//コインを持ってるか

		DATA_NUM,
	};

	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	//インスタンス
	static CEnemyManager* _Instance;

	//シングルトンなので他での生成を禁止
	CEnemyManager(const CEnemyManager& other);
	CEnemyManager operator= (const CEnemyManager& other) {}

	int _EnemyID;						//敵ID
	int _EnemyNum;						//敵の数
	vector<vector<float>> _EnemyData;	//敵データ

	//コインマネージャー取得
	CCoinManager* cCoinManager = CCoinManager::GetInstance();
public:
	//インスタンス取得
	static CEnemyManager* GetInstance();
	//インスタンス削除
	static void DeleteInstance();

	//初期化
	void Init();
	//ロード
	void Load();
	//セット
	void Set();
	//データセット
	void DataSet();
	//メイン処理
	void Step();
	//当たり判定
	void Collision(int hndl);
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//リセット処理
	void Reset();
	//敵生成
	CEnemyObj* CreateEnemy(CEnemyObj::eEnemyType t) {
		CEnemyObj* result = nullptr;
		switch (t) {
		case CEnemyObj::eEnemyType::NORMAL:	result = New CEnemy;		break;
		case CEnemyObj::eEnemyType::SHOT:	result = New CEnemyShot;	break;
		case CEnemyObj::eEnemyType::FLASH:	result = New CEnemyFlash;	break;
		case CEnemyObj::eEnemyType::WALL:	result = New CEnemyWall;	break;
		default:												break;
		}
		_EnemyList.push_back(result);
		return result;
	}
	//指定の敵削除
	void DeleteEnemy(const CEnemyObj* p) {
		for (auto enemy_itr = _EnemyList.begin(); enemy_itr != _EnemyList.end(); ++enemy_itr) {
			auto enemy = *enemy_itr;
			if (enemy != p)
				continue;
			delete p;
			_EnemyList.erase(enemy_itr);
			break;
		}
	}

	//敵格納リスト
	list<CEnemyObj*> _EnemyList;
};