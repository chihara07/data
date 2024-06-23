#pragma once
#include <DxLib.h>
#include "../../Library/Vector/Vector3D.h"

//カメラクラス
class CPlayerCamera {
private:
	static CPlayerCamera* _Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	CPlayerCamera();
	~CPlayerCamera();

	//シングルトンなので他での生成を禁止
	CPlayerCamera(const CPlayerCamera& other);
	CPlayerCamera operator= (const CPlayerCamera& other) {}

	Vector3D _CameraPos;	//カメラ視点
	Vector3D _TargetPos;	//カメラ注視点
	Vector3D _CameraUp;		//カメラ上方向
	Vector3D _Rot;			//回転角度

public:
	//インスタンス取得
	static CPlayerCamera* GetInstance();

	//インスタンス削除
	static void DeleteInstance();

	//初期化処理
	void Init();

	//描画距離セット
	void SetNearFarPars();

	//メイン処理()
	void Step();

	//更新処理
	void Update();

	//カメラ視点取得
	Vector3D GetcameraPos() { return _CameraPos; }
	//カメラ視点セット
	void SetCameraPos(Vector3D v) { _CameraPos = v; }
	//カメラ注視点取得
	Vector3D GetTargetPos() { return _TargetPos; }
	//カメラ上方向取得
	Vector3D GetCameraUp() { return _CameraUp; }
	//カメラ回転角度取得
	Vector3D GetCameraRot() { return _Rot; }
	//回転角度Xセット
	void SetRotY(float rot_y) { _Rot._Y = rot_y; }
};
