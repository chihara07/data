#pragma once
#include "DxLib.h"
#include "Switch.h"
#include "../../Library/File/File.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

//スイッチマネージャークラス
class CSwitchManager {
private:
	//コンストラクタ・デストラクタ
	CSwitchManager();
	~CSwitchManager();

	static CSwitchManager* _Instance;		//インスタンス

	//複数生成を防ぐ
	CSwitchManager(const CSwitchManager& other);
	CSwitchManager operator= (const CSwitchManager& other) {}

	int _Hndl;							//スイッチのモデルハンドル
	int _PressedHndl;					//押されたモデルハンドル
public:
	//インスタンス取得
	static CSwitchManager* GetInstance();
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
	//スイッチ生成
	CSwitch* CreateSwitch(Vector3D p, int n) {
		CSwitch* result = nullptr;
		result = New CSwitch();
		//座標と必要コイン数をセットし格納する
		result->SetPos(p);
		result->SetNeedCoinNum(n);
		_SwitchList.push_back(result);
		return result;
	}
	//指定の敵削除
	void DeleteSwitch(const CSwitch* p) {
		for (auto switch_itr = _SwitchList.begin(); switch_itr != _SwitchList.end(); ++switch_itr) {
			auto coin = *switch_itr;
			if (coin != p)
				continue;
			delete p;
			_SwitchList.erase(switch_itr);
			break;
		}
	}

	//スイッチ格納用リスト
	list<CSwitch*> _SwitchList;
};