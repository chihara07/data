#include "PlayerAttack.h"
#include "../../Library/Color.h"
#include "../../Library/Common.h"
#include "../../Library/Matrix/Matrix.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Sound/SoundManager.h"

constexpr Vector3D ATTACK_SCALE(0.1f);					//攻撃拡大率
constexpr Vector3D AREA_SCALE(0.2f);					//影エリア拡大率
constexpr Vector3D ATTACK_DISTANCE(10.f, 0.f, 20.f);	//攻撃距離
constexpr float ATTACK_RAD = 13.f;						//攻撃半径
constexpr float AREA_ENERGY = 60.f;						//影エリア基本エネルギー量
constexpr float AREA_RAD = 20.f;						//影エリア半径
constexpr float RECOVERY_FAST = 3.f;					//速い回復量
constexpr float RECOVERY_SLOW = 0.5f;					//遅い回復量
constexpr float HOLD_COUNT_INCREASE = 0.0666666666f;	//長押し時間増加量
constexpr float HOLD_COUNT_MAX = 5.f;					//最大長押し時間
constexpr int DURATION = 25;							//持続時間
constexpr int ATTACK_INTERVAL = 60;						//攻撃インターバル

CPlayerAttack* CPlayerAttack::_Instance = nullptr;

CPlayerAttack* CPlayerAttack::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CPlayerAttack;
	}

	return _Instance;
}

void CPlayerAttack::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CPlayerAttack::CPlayerAttack() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = 0;
		_AreaIsActive[area_index] = false;
		_AreaHndl[area_index] = -1;
	}
	_Scale = Vector3D::ZeroVec();
	_Rad = 0;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_Hndl = -1;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = 0.f;
	_EnergyCnt = 0;
	_IsHold = false;
	_IsCharge = false;
}
CPlayerAttack::~CPlayerAttack() {

}

//初期化
void CPlayerAttack::Init() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = AREA_RAD;
		_AreaIsActive[area_index] = false;
		_AreaHndl[area_index] = -1;
	}
	_Scale = ATTACK_SCALE;
	_Rad = ATTACK_RAD;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_Hndl = -1;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = AREA_ENERGY;
	_EnergyCnt = AREA_ENERGY_MAX;
	_IsHold = false;
	_IsCharge = false;
}

//ロード
void CPlayerAttack::Load() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaHndl[area_index] == -1) {
			_AreaHndl[area_index] = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_AREA));
		}
	}

	if (_Hndl == -1) { 
		_Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::PLAYER_ATTACK));
	}
}

//セット
void CPlayerAttack::Set() {
	//拡大率、回転角度、座標セット
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		//比率セット
		MV1SetScale(_AreaHndl[area_index], _AreaScale[area_index]);
		MV1SetPosition(_AreaHndl[area_index], _AreaPos[area_index]);
	}

	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, cPlayer->GetRot());
	MV1SetPosition(_Hndl, ((_Pos[0] + _Pos[1]) / 2));
}

//メイン処理
void CPlayerAttack::Step() {
	if (_IsActive == true) {
		//原点に平行移動する行列を作成
		MyMatrix OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
		//プレイヤーのY軸回転行列を作成
		MyMatrix RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
		//平行移動する行列を作成
		MyMatrix MoveMat[ATTACK_NUM];
		MoveMat[0] = MyMatrix::GetTranslateMat(ATTACK_DISTANCE._X, 0.f, -ATTACK_DISTANCE._Z);
		MoveMat[1] = MyMatrix::GetTranslateMat(-ATTACK_DISTANCE._X, 0.f, -ATTACK_DISTANCE._Z);
		//元の位置に戻す平行移動する行列を作成
		MyMatrix ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

		//各行列を合成
		MyMatrix playerCompoundMat[ATTACK_NUM];
		for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
			playerCompoundMat[attack_index] = ReturnMat * RotYMat;
			playerCompoundMat[attack_index] *= MoveMat[attack_index];
			playerCompoundMat[attack_index] *= OriginMat;

			//座標に行列を掛けて攻撃の座標を算出
			_Pos[attack_index] = playerCompoundMat[attack_index] * cPlayer->GetPos();
		}

		_Cnt++;
	}

	//時間になったら生存フラグオフ
	if (_Cnt > DURATION && _IsActive == true) {
		_IsActive = false;
		_Interval = ATTACK_INTERVAL;
	}

	//生存フラグオフならインターバルをへらす
	if (_Interval > 0 && _IsActive == false) {
		_Interval--;
	}

	//プレイヤーの状態にあわせてエネルギー回復
	if (cPlayer->GetState() == CPlayer::ePlayerState::SHADOW ||
		cPlayer->GetState() == CPlayer::ePlayerState::CLIMB)
		_EnergyCnt += RECOVERY_FAST;
	else
		_EnergyCnt += RECOVERY_SLOW;

	//エネルギー上限
	if (_EnergyCnt >= AREA_ENERGY_MAX) {
		_EnergyCnt = AREA_ENERGY_MAX;
	}

	//長押し時間処理
	if (_IsHold == true) {
		_HoldCnt += HOLD_COUNT_INCREASE;

		if (_HoldCnt > HOLD_COUNT_MAX)
			_HoldCnt = HOLD_COUNT_MAX;
	}
	else {
		_HoldCnt = 1;
		_IsCharge = false;
	}
}

//描画
void CPlayerAttack::Draw() {
	if (_IsActive == true) {
		MV1DrawModel(_Hndl);
	}

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaIsActive[area_index] == true) {
			MV1DrawModel(_AreaHndl[area_index]);
			//DrawSphere3D(_AreaPos[area_index], _AreaRad[area_index], 10, COLOR::RED, COLOR::RED, false);
		}
	}
}

//終了
void CPlayerAttack::Fin() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaHndl[area_index] != -1) { MV1DeleteModel(_AreaHndl[area_index]); _AreaHndl[area_index] = -1; }
	}
}

//更新処理
void CPlayerAttack::Update() {
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		MV1SetPosition(_AreaHndl[area_index], _AreaPos[area_index]);
		MV1SetScale(_AreaHndl[area_index], _AreaScale[area_index]);
	}
	MV1SetRotationXYZ(_Hndl, cPlayer->GetRot());
	MV1SetPosition(_Hndl, ((_Pos[0] + _Pos[1]) / 2));
}

//リクエスト
void CPlayerAttack::Request() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		if (_Interval == 0 && _IsActive == false) {
			_IsActive = true;
			_Cnt = 0;
			CSoundManager::Play(CSoundManager::eSoundID::SE_PLATTACK);

			break;
		}
	}
}

//影エリアリクエスト
void CPlayerAttack::AreaRequest(bool f) {
	//すべて使用中ならすべてオフ
	if (_AreaIsActive[0] == true && _AreaIsActive[1] == true && _AreaIsActive[2] == true) {
		for (int area_index = 0; area_index < AREA_NUM; area_index++) {
			_AreaIsActive[area_index] = false;
			_AreaScale[area_index] = AREA_SCALE;
			_AreaRad[area_index] = AREA_RAD;
		}

		return;
	}

	if (_EnergyCnt < _Energy)
		return;

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (_AreaIsActive[area_index] == false) {
			_AreaIsActive[area_index] = true;
			if (_Energy * _HoldCnt > _EnergyCnt) {
				_AreaScale[area_index] *= _EnergyCnt / _Energy;
				_AreaRad[area_index] *= _EnergyCnt / _Energy;
				_EnergyCnt = 0.f;
			}
			else {
				_AreaScale[area_index] *= _HoldCnt;
				_AreaRad[area_index] *= _HoldCnt;
				_EnergyCnt -= _Energy * _HoldCnt;
			}

			//原点に平行移動する行列を作成
			MyMatrix OriginMat;
			//プレイヤーのY軸回転行列を作成
			MyMatrix RotYMat;
			//平行移動する行列を作成
			MyMatrix MoveMat;
			//元の位置に戻す平行移動する行列を作成
			MyMatrix ReturnMat;

			//フラグがtrueなら上向きに出す
			if (f == true) {
				//原点に平行移動する行列を作成
				OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
				//プレイヤーのY軸回転行列を作成
				RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
				//平行移動する行列を作成
				MoveMat = MyMatrix::GetTranslateMat(0.f, (cPlayer->GetRad() + _AreaRad[area_index]), 0.f);
				//元の位置に戻す平行移動する行列を作成
				ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

				//各行列を合成
				MyMatrix playerCompoundMat;
				playerCompoundMat = ReturnMat * RotYMat;
				playerCompoundMat *= MoveMat;
				playerCompoundMat *= OriginMat;

				//座標に行列を掛けて影エリアの座標を算出
				_AreaPos[area_index] = playerCompoundMat * cPlayer->GetPos();
			}
			//falseなら正面に出す
			else {
				//原点に平行移動する行列を作成
				OriginMat = MyMatrix::GetTranslateMat(-cPlayer->GetPos());
				//プレイヤーのY軸回転行列を作成
				RotYMat = MyMatrix::GetYawMatrix(cPlayer->GetRot()._Y);
				//平行移動する行列を作成
				MoveMat = MyMatrix::GetTranslateMat(0.f, 0.f, - _AreaRad[area_index]);
				//元の位置に戻す平行移動する行列を作成
				ReturnMat = MyMatrix::GetTranslateMat(cPlayer->GetPos());

				//各行列を合成
				MyMatrix playerCompoundMat;
				playerCompoundMat = ReturnMat * RotYMat;
				playerCompoundMat *= MoveMat;
				playerCompoundMat *= OriginMat;

				//座標に行列を掛けてプレイヤーの座標を算出
				_AreaPos[area_index] = playerCompoundMat * cPlayer->GetPos();
			}

			return;
		}
	}
}

//指定した影エリアリセット
void CPlayerAttack::AreaReset(int id) {
	_AreaIsActive[id] = false;
	_AreaScale[id] = AREA_SCALE;
	_AreaRad[id] = AREA_RAD;
}

//リセット
void CPlayerAttack::AllReset() {
	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {
		_Pos[attack_index] = Vector3D::ZeroVec();
	}
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		_AreaScale[area_index] = AREA_SCALE;
		_AreaPos[area_index] = Vector3D::ZeroVec();
		_AreaRad[area_index] = AREA_RAD;
		_AreaIsActive[area_index] = false;
	}
	_Scale = Vector3D::ZeroVec();
	_Rad = ATTACK_RAD;
	_Cnt = 0;
	_Interval = 0;
	_IsActive = false;
	_HoldCnt = 1;
	_IsPlayerMove = false;
	_Energy = AREA_ENERGY;
	_EnergyCnt = AREA_ENERGY_MAX;
	_IsHold = false;
	_IsCharge = false;
}
