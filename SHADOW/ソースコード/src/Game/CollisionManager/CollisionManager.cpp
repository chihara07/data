#include "CollisionManager.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Color.h"
#include "../../Library/Common.h"
#include "../../Library/Sound/SoundManager.h"
#include "../Player/Player.h"
#include "../Player/PlayerAttack.h"
#include "../../Library/Effect/effekseer.h"

//法線を比べるときの誤差
constexpr float NORMAL_ERROR = 0.01f;

//プレイヤーと敵の当たり判定
void  CCOllisionManager::CheckHitPlayerToEnemy(CEnemyObj* cEnemy) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//カメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cPlayer->GetDeath() == true || cEnemy->GetActive() == false)
		return;

	//プレイヤーと敵が当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetPos(), cEnemy->GetRad())) {
		//プレイヤー死亡関数実行
		cPlayer->DeathCalc();
	}
}

//プレイヤーとフラッシュ攻撃の当たり判定
void CCOllisionManager::CheckHitPlayerToFlash(CEnemyObj* cEnemy) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//カメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cEnemy->GetFlashActive() == false || cPlayer->GetDeath() == true || cEnemy->GetActive() == false ||
		(cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetState() != CPlayer::ePlayerState::CLIMB))
		return;

	//プレイヤーとフラッシュ攻撃が当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetPos(), cEnemy->GetFlashRad())) {
		//プレイヤー死亡関数実行
		cPlayer->DeathCalc();
	}

}

//プレイヤーと敵の弾の当たり判定
void  CCOllisionManager::CheckHitPlayerToEnemyBullet(CEnemyObj* cEnemy) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//カメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cPlayer->GetState() == CPlayer::ePlayerState::SHADOW || cPlayer->GetState() == CPlayer::ePlayerState::CLIMB ||
		cEnemy->GetActive() == false || cEnemy->GetBulletActive() == false || cPlayer->GetDeath() == true)
		return;

	//プレイヤーと敵の弾が当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetBulletPos(), cEnemy->GetBulletRad())) {
		//プレイヤー死亡関数実行
		cPlayer->DeathCalc();
	}
}

//プレイヤーの攻撃と敵の当たり判定
void CCOllisionManager::CheckHitPlayerAttackToEnemy(CEnemyObj* cEnemy) {
	//プレイヤー取得、プレイヤー攻撃取得
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();


	if (cEnemy->GetActive() == false || cPlayer->GetDeath() == true || cPlayerAttack->GetActive() == false
		|| cEnemy->GetState() == CEnemy::eEnemyState::KNOCKBACK)
		return;

	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {

		//プレイヤーの攻撃と敵が当たっているか
		if (CCollision::IsHitSphere(cPlayerAttack->GetPos(attack_index), cPlayerAttack->GetRad(), cEnemy->GetPos(), cEnemy->GetRad()))
		{
			if (cEnemy->GetType() != CEnemyObj::eEnemyType::WALL) {
				if (cEnemy->GetForward() || cEnemy->GetState() == CEnemy::eEnemyState::DISCOVERY) {
					cEnemy->SubLife();
					cEnemy->SetState(CEnemy::eEnemyState::KNOCKBACK);
					cEnemy->SetMoveVec(cPlayer->GetPos().Create(cEnemy->GetPos()));
					break;
				}
				else
					//敵死亡関数実行
					cEnemy->DeathCalc();
			}
			else {
				if (cEnemy->GetForward() == false) {
					//敵死亡関数実行
					cEnemy->DeathCalc();
				}
			}
		}
	}
}

//プレイヤーの影エリアとプレイヤーの当たり判定
void CCOllisionManager::CheckHitPlayerToArea() {
	//プレイヤー取得、プレイヤー攻撃取得
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();


	if (cPlayer->GetDeath() == true)
		return;

	//とりあえず接触フラグオフ
	cPlayer->SetHitArea(false);
	
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;
		//プレイヤーの影エリアとプレイヤーが当たっているか
		if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), cPlayer->GetPos(), cPlayer->GetRad()))
		{
			cPlayer->SetHitArea(true);
		}
	}
}

//敵の攻撃と影エリア判定
void CCOllisionManager::CheckHitFlashToArea(CEnemyObj* cEnemy) {
	if (cEnemy->GetFlashActive() == false || cEnemy->GetActive() == false)
		return;

	//プレイヤー取得、プレイヤー攻撃取得
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;
		//影エリアと敵の攻撃が当たっているか
		if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), cEnemy->GetPos(), cEnemy->GetFlashRad())){
			//当たっているならその影エリアと敵の接触フラグをオフ
			cPlayerAttack->AreaReset(area_index);
			cEnemy->SetHitArea(area_index, false);
		}
	}
}

//プレイヤーと敵のコイン当たり判定
bool CCOllisionManager::CheckHitPlayerToCoin(Vector3D coin_pos, float coin_rad, bool coin_active) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayer->GetDeath() == true || coin_active == false)
		return false;

	//プレイヤーと敵のコインが当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), coin_pos, coin_rad))
	{
		//当たっているならプレイヤーの所持枚数を増やし、コインのフラグはfalseを返す
		cPlayer->AddCoin();
		return false;
	}
	else
		return true;
}

//プレイヤーと影の当たり判定
void CCOllisionManager::CheckHitPlayerToShadow(CGimmickObj* cGimmick) {
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cGimmick->GetActive() == true) {
		//プレイヤーと影が当たっているか
		if (CCollision::IsHitSphere(cPlayer->GetTeleportPos(), cPlayer->GetRad(), cGimmick->GetPos(), cGimmick->GetRad()))
		{
			//当たっているならプレイヤーのテレポート関数とギミックのヒット関数実行
			cPlayer->TeleportCalc(cGimmick->GetPos());
			cGimmick->HitCalc();
		}
	}
}

//プレイヤーとスイッチの当たり判定
void CCOllisionManager::CheckHitPlayerToSwitch(CSwitch* cSwitch) {
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cSwitch->GetPressed() == true)
		return;

	//プレイヤーとスイッチが当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cSwitch->GetPos(), cSwitch->GetRad()))
	{
		//当たっているならスイッチのヒット関数実行
		cSwitch->HitCalc();

		//プレイヤーの所持枚数が必要枚数あるか
		if (cPlayer->GetCoin() >= cSwitch->GetNeedCoinNum()) {
			//必要枚数あるならスイッチを押す
			CSoundManager::Play(CSoundManager::eSoundID::SE_SWITCH);
			cSwitch->PressedCalc();
			cPlayer->SubCoin(cSwitch->GetNeedCoinNum());
		}
	}
}

//プレイヤーとトラップの当たり判定
void CCOllisionManager::CheckHitPlayerToTrap(CGimmickObj* cGimmick) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//カメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	//プレイヤーとトラップが当たっているか
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cGimmick->GetPos(), cGimmick->GetRad())
		&& cPlayer->GetDeath() == false) {
		//プレイヤー死亡関数実行
		cPlayer->DeathCalc();
	}
}

//マップとの当たり判定
bool CCOllisionManager::CheckCollision(Vector3D pos, float rad, const int hndl) {
	// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(hndl, -1, TRUE);

	// ポリゴンの数だけ繰り返す
	for (int pol_index = 0; pol_index < polygons.PolygonNum; pol_index++) {
		// ポリゴン情報を取得する
		MV1_REF_POLYGON polygon = polygons.Polygons[pol_index];
		// ポリゴンを形成する三角形の3頂点を取得する
		Vector3D vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;

		// ポリゴン法線を算出する
		Vector3D norm = GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// 法線のY成分がMAP_FLOOR_NORM_Y_MIN以上であれば床
		if (norm._Y >= MAP_FLOOR_NORM_Y_MIN) {
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(pos, vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から床の高さを計算
				float floor_height = GetTriangleHeightXZ(pos, vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = pos._Y - rad;
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い かつ 足元と床との距離が離れすぎていなければ押し上げる
				if (dist < 0.0f && MyLib::Abs(dist) <= rad) {
					return  true;
				}
			}
		}
	}

	return false;
}

//モデルとの当たり判定
Vector3D CCOllisionManager::HitCheck(Vector3D pos, float rad, const int hndl) {
	//押し出すベクトル
	Vector3D pushVec(Vector3D::ZeroVec());
	//当たったところとの距離ベクトル
	Vector3D distance(Vector3D::ZeroVec());
	//当たったところとの距離
	float length = 0.f;
	CollData data;
	list<CollData> List;
	//当たり判定結果
	MV1_COLL_RESULT_POLY_DIM res;
	//当たり判定結果格納
	res = MV1CollCheck_Sphere(hndl, -1, pos, rad);

	//ヒットしているなら
	if (res.HitNum > 0) {
		for (int pol_index = 0; pol_index < res.HitNum; pol_index++) {
			//同じ向きの法線があるかフラグ
			bool check = true;

			distance = VSub(res.Dim[pol_index].HitPosition, pos);
			length = distance.Long();
			//めり込み距離を計算
			length = rad - length;
			//当たったポリゴンの法線の向きにめり込んだ長さ分かける
			distance = VScale(res.Dim[pol_index].Normal, length);
			data._Normal = res.Dim[pol_index].Normal;
			data._Distance = distance;

			//法線方向が同じならリストに格納しない
			if (pol_index == 0) {
				List.emplace_back(data);
			}
			else {
				for (auto itr = List.begin(); itr != List.end(); ++itr) {
					if (MyLib::Abs(itr->_Normal._X - res.Dim[pol_index].Normal.x) <= NORMAL_ERROR &&
						MyLib::Abs(itr->_Normal._Y - res.Dim[pol_index].Normal.y) <= NORMAL_ERROR &&
						MyLib::Abs(itr->_Normal._Z - res.Dim[pol_index].Normal.z) <= NORMAL_ERROR) {
						check = false;
						if (itr->_Distance.Long() < distance.Long())
							itr->_Distance = distance;
						break;
					}
				}
				if (check == true) {
					List.emplace_back(data);
				}
			}
		}

		//リストに格納してあるベクトルを合計する
		for (auto itr = List.begin(); itr != List.end(); ++itr) {
			pushVec += itr->_Distance;
		}
	}

	//コリジョンデータ破棄
	MV1CollResultPolyDimTerminate(res);

	List.clear();

	//合計したベクトルを加算し返す
	return (pos + pushVec);
}

//カメラがめり込まないようにする
void CCOllisionManager::HitCheckCamera(const int hndl) {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//カメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	MV1_COLL_RESULT_POLY res;
	//当たり判定結果格納
	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
		res = MV1CollCheck_Line(hndl, -1, cPlayer->GetTeleportPos(), cPlayerCamera->GetcameraPos());
	}
	else
		res = MV1CollCheck_Line(hndl, -1, cPlayer->GetPos(), cPlayerCamera->GetcameraPos());

	//めり込んでいるなら押し出す
	if (res.HitFlag != 0) {
		cPlayerCamera->SetCameraPos(res.HitPosition);
	}
}
