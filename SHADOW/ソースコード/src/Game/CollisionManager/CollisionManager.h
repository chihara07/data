#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Gimmick/Teleport/Teleport.h"
#include "../Gimmick/Switch/Switch.h"
#include "../Gimmick/Trap/Trap.h"
#include "../Gimmick/GimmickManager.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Camera/Camera.h"
#include <list>

using std::list;

//当たり判定マネージャークラス
class CCOllisionManager {
public:
	//プレイヤーと敵の当たり判定
	static void CheckHitPlayerToEnemy(CEnemyObj* cEnemy);
	//プレイヤーとフラッシュ攻撃の当たり判定
	static void CheckHitPlayerToFlash(CEnemyObj* cEnemy);
	//プレイヤーと敵の弾の当たり判定
	static void CheckHitPlayerToEnemyBullet(CEnemyObj* cEnemy);
	//プレイヤーの攻撃と敵の当たり判定
	static void CheckHitPlayerAttackToEnemy(CEnemyObj* cEnemy);
	//プレイヤーと影エリア判定
	static void CheckHitPlayerToArea();
	//敵の攻撃と影エリア判定
	static void CheckHitFlashToArea(CEnemyObj* cEnemy);
	/// <summary>
	/// プレイヤーと敵のコイン当たり判定
	/// </summary>
	/// <param name="coin_pos">コイン座標</param>
	/// <param name="coin_rad">コイン半径</param>
	/// <param name="coin_active">コイン生存フラグ</param>
	/// <returns></returns>
	static bool CheckHitPlayerToCoin(Vector3D coin_pos,float coin_rad, bool coin_active);
	//プレイヤーと影の当たり判定
	static void CheckHitPlayerToShadow(CGimmickObj* cGimmick);
	//プレイヤーとトラップの当たり判定
	static void CheckHitPlayerToTrap(CGimmickObj* cGimmick);
	//プレイヤーとスイッチの当たり判定
	static void CheckHitPlayerToSwitch(CSwitch* cSwitch);

	/// <summary>
	/// プレイヤーとマップ当たり判定
	/// </summary>
	/// <param name="pos">対象の座標</param>
	/// <param name="rad">対象の半径</param>
	/// <param name="hndl">マップハンドル</param>
	/// <returns>true : 地面に触れている</returns>
	static bool CheckCollision(Vector3D pos, float rad, const int hndl);
	
	/// <summary>
	/// モデルとの当たり判定
	/// </summary>
	/// <param name="pos">対象の座標</param>
	/// <param name="rad">対象の半径</param>
	/// <param name="hndl">マップハンドル</param>
	/// <returns>押し出し後の座標</returns>
	static Vector3D HitCheck(Vector3D pos, float rad, const int hndl);
	//カメラがめり込まないようにする
	static void HitCheckCamera(const int hndl);

	//当たり判定データ
	struct CollData{
		Vector3D _Normal;
		
		Vector3D _Distance;
	};
};
