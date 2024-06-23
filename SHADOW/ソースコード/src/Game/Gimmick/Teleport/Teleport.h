#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"
#include "../../Library/Vector/Vector3D.h"

//テレポート影クラス
class CTeleportShadow : public CGimmickObj {
private:
	Vector3D _SelectingPos;		//選択中の影座標
	int _SelectHndl;			//選択中の影モデルハンドル
	bool _CheckTeleport;		//テレポート可能かどうかフラグ
public:
	//コンストラクタ・デストラクタ
	CTeleportShadow();
	~CTeleportShadow();

	//初期化
	void Init();
	//ロード
	void Load();
	//セット
	void Set();
	//メイン処理
	void Step();
	//描画
	void Draw();
	//終了
	void Fin();
	//更新処理
	void Update();
	//ヒット関数
	void HitCalc();

	//テレポート可能かどうかフラグセット
	void SetCheckTeleport(bool f) { _CheckTeleport = f; }
};
