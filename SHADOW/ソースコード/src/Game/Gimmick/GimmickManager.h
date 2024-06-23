#pragma once
#include "DxLib.h"
#include "../Object/GimmickObj.h"
#include "Block/Block.h"
#include "Fence/Fence.h"
#include "Goal/Goal.h"
#include "NoShadow/NoShadow.h"
#include "Teleport/Teleport.h"
#include "Trap/Trap.h"
#include "Wall/Wall.h"
#include "Cross/Cross.h"
#include "Switch/SwitchManager.h"
#include "../../Library/File/File.h"
#include "../Camera/Camera.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

constexpr int GIMMICK_NUM0 = 5;			//stage0のギミックの数
constexpr int GIMMICK_NUM = 14;			//stage1のギミックの数
constexpr int GIMMICK_NUM2 = 29;		//stage2のギミックの数
constexpr int GIMMICK_NUM3 = 31;		//stage3のギミックの数
constexpr int GIMMICK_NUM4 = 28;		//stage4のギミックの数

//ギミックマネージャークラス
class CGimmickManager {
private:
	//ギミックデータ
	enum class eGimmickData {
		ID = 0,				//番号
		VEC_X,				//ベクトル1X
		VEC_Y,				//ベクトル1Y
		VEC_Z,				//ベクトル1Z
		VEC2_X,				//ベクトル2X
		VEC2_Y,				//ベクトル2Y
		VEC2_Z,				//ベクトル2Z
		VEC3_X,				//ベクトル3X
		VEC3_Y,				//ベクトル3Y
		VEC3_Z,				//ベクトル3Z
		SCALE_X,			//拡大率X
		SCALE_Y,			//拡大率Y
		SCALE_Z,			//拡大率Z
		TYPE,				//ギミックごとの種類
		NOSHADOW_ID,		//影禁止エリアの動きID
		TYPE2,				//ギミックの種類

		DATA_NUM,
	};

	int _GimmickID;						//敵ID
	int _GimmickNum;					//敵の数
	vector<vector<float>> _GimmickData;	//敵データ

	//スイッチマネージャー取得
	CSwitchManager* cSwitchManager = CSwitchManager::GetInstance();
public:
	//コンストラクタ・デストラクタ
	CGimmickManager();
	~CGimmickManager();

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
	void Collision();
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//ギミック生成
	CGimmickObj* CreateGimmick(CGimmickObj::eGimmickType t) {
		CGimmickObj* result = nullptr;
		switch (t) {
		case CGimmickObj::eGimmickType::BLOCK:		result = New CBlock;			break;
		case CGimmickObj::eGimmickType::FENCE:		result = New CFence;			break;
		case CGimmickObj::eGimmickType::GOAL:		result = New CGoal;				break;
		case CGimmickObj::eGimmickType::NOSHADOW:	result = New CNoShadow;			break;
		case CGimmickObj::eGimmickType::TELEPORT:	result = New CTeleportShadow;	break;
		case CGimmickObj::eGimmickType::TRAP:		result = New CTrap;				break;
		case CGimmickObj::eGimmickType::WALL:		result = New CWall;				break;
		case CGimmickObj::eGimmickType::CROSS:		result = New CCross;				break;
		default:																	break;
		}
		_GimmickList.push_back(result);
		return result;
	}
	//指定のギミック削除
	void DeleteGimmick(const CGimmickObj* p) {
		for (auto enemy_itr = _GimmickList.begin(); enemy_itr != _GimmickList.end(); ++enemy_itr) {
			auto enemy = *enemy_itr;
			if (enemy != p)
				continue;
			delete p;
			_GimmickList.erase(enemy_itr);
			break;
		}
	}

	//ギミック格納用リスト
	list<CGimmickObj*> _GimmickList;
};
