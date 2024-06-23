#include "Wall.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Camera/Camera.h"
#include "../../Game/Hndl/HndlManager.h"

//コンストラクタ・デストラクタ
CWall::CWall() {
	_Hndl = -1;
}
CWall::~CWall() {
	Fin();
}

//初期化
void CWall::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
}

//ロード
void CWall::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::WALL)); }
}

//セット
void CWall::Set() {
	//拡大率セット、回転角度、座標セット
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(_Hndl, -1, TRUE);

	//コリジョン情報構築
	MV1SetupCollInfo(_Hndl);
}

//メイン処理
void CWall::Step() {
	//プレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();
	//プレイヤーカメラ取得
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(_Hndl, -1, TRUE);
	Vector3D playerPos = cPlayer->GetPos();
	float playerRad = cPlayer->GetRad();
	float playerRotY = 0;
	float cameraRotY = 0;

	// ポリゴンの数だけ繰り返す
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// ポリゴン情報を取得する
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
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
			if (CCollision::IsHitTriangleXZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から床の高さを計算
				float floor_height = GetTriangleHeightXZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = playerPos._Y - playerRad;
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い かつ 足元と床との距離が離れすぎていなければ押し上げる
				if (dist < 0.0f && MyLib::Abs(dist) <= playerRad) {
				}
			}
		}
		else if (norm._Y <= MAP_CEIL_NORM_Y) {
			// 天井の場合
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から天井の高さを計算
				float ceil_height = GetTriangleHeightXZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの脳天の座標を計算
				float player_top = playerPos._Y + playerRad;
				// 天井から脳天までの距離を計算
				float dist = player_top - ceil_height;
				// 脳天の方が高い かつ 脳天と天井との距離が離れすぎていなければ押し下げる
				if (dist > 0.0f && MyLib::Abs(dist) <= playerRad) {

				}
			}
		}
		else {
			// そうでなければ壁
			if (MyLib::Abs(norm._Z) >= MAP_WALL_NORM_Z_MIN) {
				// XY平面の壁
				if (CCollision::IsHitTriangleXY(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = GetTriangleHeightXY(playerPos, vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm._Z < 0.0f ? playerPos._Z + playerRad : playerPos._Z - playerRad;
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (MyLib::Abs(dist) <= playerRad) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm._Z <= 0.0f && dist >= 0.0f)) {
							//壁に触れているならプレイヤーの壁のぼりフラグオン、
							//接触フラグオン、プレイヤーY軸回転角度、カメラY軸回転角度代入
							cPlayer->SetClimb(true);
							playerRotY = MyLib::STRAIGHT_ANGLE;
							cameraRotY = MyLib::STRAIGHT_ANGLE;
						}
						else if ((norm._Z >= 0.0f && dist <= 0.0f)) {
							//壁に触れているならプレイヤーの壁のぼりフラグオン、
							//接触フラグオン、プレイヤーY軸回転角度、カメラY軸回転角度代入
							cPlayer->SetClimb(true);
							playerRotY = 0.f;
							cameraRotY = 0.f;
						}
					}
				}
			}
			else {
				// YZ平面の壁
				if (CCollision::IsHitTriangleYZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = GetTriangleHeightYZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm._X < 0.0f ? playerPos._X + playerRad : playerPos._X - playerRad;
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (MyLib::Abs(dist) <= playerRad) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm._X <= 0.0f && dist >= 0.0f)) {
							//壁に触れているならプレイヤーの壁のぼりフラグオン、
							//接触フラグオン、プレイヤーY軸回転角度、カメラY軸回転角度代入
							cPlayer->SetClimb(true);
							playerRotY = -MyLib::RIGHT_ANGLE;
							cameraRotY = -MyLib::RIGHT_ANGLE;
						}
						else if ((norm._X >= 0.0f && dist <= 0.0f)) {
							//壁に触れているならプレイヤーの壁のぼりフラグオン、
							//接触フラグオン、プレイヤーY軸回転角度、カメラY軸回転角度代入
							cPlayer->SetClimb(true);
							playerRotY = MyLib::RIGHT_ANGLE;
							cameraRotY = MyLib::RIGHT_ANGLE;
						}
					}
				}
			}
		}
	}
	//プレイヤーが壁のぼり状態で壁のぼりフラグオンなら
	if (cPlayer->GetState() == CPlayer::ePlayerState::CLIMB
		&& cPlayer->GetClimb() == true) {
		//回転角度セット
		cPlayer->SetRotX(MyLib::RIGHT_ANGLE);
		cPlayer->SetRotY(playerRotY);
		cPlayerCamera->SetRotY(cameraRotY);
	}
}

//描画
void CWall::Draw() {
	//プレイヤー情報取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	MV1DrawModel(_Hndl);
}

//更新処理
void CWall::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(_Hndl, -1, TRUE);
}

//終了
void CWall::Fin() {
	//コリジョン情報破棄
	MV1TerminateCollInfo(_Hndl);

	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//ヒット関数
void CWall::HitCalc() {
}
