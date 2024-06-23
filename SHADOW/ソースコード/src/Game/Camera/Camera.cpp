#include "Camera.h"
#include <math.h>
#include "../../Library/Input/InputManager.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Library/Math/Math.h"
#include "../../Library/Common.h"
#include "../Player/Player.h"

constexpr Vector3D CAMERA_START_POS( 0.0f, 10.0f, 100.0f );		//カメラ初期位置
constexpr Vector3D CAMERA_CLIMB_POS(0.0f, 10.0f, 150.0f);		//カメラ初期位置
constexpr Vector3D TARGET_START_POS( 0.0f, 0.0f, 0.0f );		//カメラ注視点初期位置
constexpr Vector3D CAMERA_START_UP( 0.0f, 1.0f, 0.0f );			//カメラ上方向初期位置
constexpr Vector3D CAMERA_START_ROT(-0.4f, 0.f, 0.f);			//カメラ初期回転角度
constexpr Vector2D CAMERA_LIMIT_ROT(80.f, 360.f);			//カメラ初期回転角度
constexpr float CAMERA_SPD = 0.03f;								//カメラ視点移動速度

CPlayerCamera* CPlayerCamera::_Instance = nullptr;

CPlayerCamera* CPlayerCamera::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CPlayerCamera;
	}

	return _Instance;
}

void CPlayerCamera::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ
CPlayerCamera::CPlayerCamera()
{
	//すべてに0を入れる
	_CameraPos = Vector3D::ZeroVec();
	_TargetPos = Vector3D::ZeroVec();
	_CameraUp = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
}
CPlayerCamera::~CPlayerCamera() {

}

//初期化処理
void CPlayerCamera::Init(){
	_CameraPos = CAMERA_START_POS;
	_TargetPos = TARGET_START_POS;
	_CameraUp = CAMERA_START_UP;
	_Rot = CAMERA_START_ROT;
}

//描画距離セット
void CPlayerCamera::SetNearFarPars(){
	//ニア・ファーセット
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	//パースセット
	SetupCamera_Perspective(CAMERA_PARS);

	//カメラ更新
	SetCameraPositionAndTargetAndUpVec(_CameraPos, _TargetPos, _CameraUp);
}

//メイン処理
void CPlayerCamera::Step(){
	//pプレイヤー取得
	CPlayer* cPlayer = CPlayer::GetInstance();

	//カメラ視点移動処理
	//注視点代入
	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT)
		_TargetPos = cPlayer->GetTeleportPos();
	else
		_TargetPos = cPlayer->GetPos();
	//壁上り状態なら移動不可
	if (cPlayer->GetState() != CPlayer::ePlayerState::CLIMB) {
		//カメラ移動
		_Rot._X += CInputManager::GetRInputY() * CAMERA_SPD;
		_Rot._Y += CInputManager::GetRInputX() * CAMERA_SPD;

		//カメラ移動の角度を制限する
		if (_Rot._X <= MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._X)) {
			_Rot._X = MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._X);
		}
		if (_Rot._X >= MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._X)) {
			_Rot._X = MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._X);
		}
		if (_Rot._Y >= MyLib::ConvertDegreesToRadian(CAMERA_LIMIT_ROT._Y)) {
			_Rot._Y = 0.0f;
		}
		if (_Rot._Y <= MyLib::ConvertDegreesToRadian(-CAMERA_LIMIT_ROT._Y)) {
			_Rot._Y = 0.0f;
		}
	}

	//回転角度から座標を計算
	//注視点を原点に平行移動する行列を作成
	MyMatrix cameraMoveOriginMat = MyMatrix::GetTranslateMat(-_TargetPos);
	//カメラのY軸回転行列を作成
	MyMatrix cameraRotYMat = MyMatrix::GetYawMatrix(_Rot._Y);
	//カメラのX軸回転行列を作成
	MyMatrix cameraRotXMat = MyMatrix::GetPitchMatrix(_Rot._X);
	//カメラを注視点より手前に移動させる平行移動行列を作成
	MyMatrix cameraMoveBackMat;
	//プレイヤーの状態によって移動距離を変える
	if(cPlayer->GetState() != CPlayer::ePlayerState::CLIMB)
		cameraMoveBackMat = MyMatrix::GetTranslateMat(CAMERA_START_POS);
	else
		cameraMoveBackMat = MyMatrix::GetTranslateMat(CAMERA_CLIMB_POS);
	//注視点を元の位置に戻す平行移動する行列を作成
	MyMatrix cameraReturnMat = MyMatrix::GetTranslateMat(_TargetPos);

	//各行列を合成
	MyMatrix cameraCompoundMat = cameraReturnMat * cameraRotYMat;
	cameraCompoundMat *= cameraRotXMat;
	cameraCompoundMat *= cameraMoveBackMat;
	cameraCompoundMat *= cameraMoveOriginMat;

	//注視点に行列を掛けてカメラの座標を算出
	_CameraPos = cameraCompoundMat * _TargetPos;
}

//更新処理
void CPlayerCamera::Update(){
	//カメラ更新
	SetCameraPositionAndTargetAndUpVec(_CameraPos, _TargetPos, _CameraUp);
}
