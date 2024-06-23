#include "Map.h"
#include <math.h>
#include "../../Library/Math/Math.h"
#include "../../Library/Common.h"
#include "../../Game/Hndl/HndlManager.h"

constexpr Vector3D FIELD_START_POS( 0.0f, -30.0f, 250.0f );	//フィールド初期座標
constexpr Vector3D FIELD_SCALE( 1.f, 1.f, 1.f );			//フィールド比率
constexpr Vector3D SKY_START_POS(0.0f, 0.0f, -2000.0f);		//フィールド初期座標
constexpr Vector3D SKY_SCALE(40.f, 40.f, 40.f);				//フィールド比率
constexpr float SKY_SPD = 0.0003f;							//フィールド回転速度
//フィールド初期回転角度
constexpr Vector3D FIELD_START_ROT( 0.0f, (180.0f * DX_PI_F) / 180.0f, 0.0f );
//天球のモデルパス
constexpr char SKY_PATH[] = "data/Sky/sky.mv1";

//コンストラクタ
CBg::CBg() {
	Init();
}

//デストラクタ
CBg::~CBg() {
	Fin();
}

//初期化処理
void CBg::Init() {
	_Pos = FIELD_START_POS;			//フィールド座標初期化
	_Scale = FIELD_SCALE;			//フィールド比率初期化
	_Rot = FIELD_START_ROT;			//フィールド回転角度初期化
	_Hndl = -1;						//フィールド画像ハンドル初期化
	_ColHndl = -1;
	_SkyHndl = -1;					//天球画像ハンドル
	_SkyPos = SKY_START_POS;		//天球座標
	_SkyScale = SKY_SCALE;			//天球比率
	_SkyRot = Vector3D::ZeroVec();	//天球回転角度
}

//ロード処理
void CBg::Load() {
	//ステージIDごとにステージモデルをコピー
	if (StageID == eStageID::STAGE_0) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP0_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP0_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_1) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP1_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP1_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_2) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP2_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP2_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_3) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP3_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP3_COL_PATH)); }
	}
	else if (StageID == eStageID::STAGE_4) {
		if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP4_PATH)); }
		if (_ColHndl == -1) { _ColHndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::MAP4_COL_PATH)); }
	}
	//天球モデルロード
	if (_SkyHndl == -1) { _SkyHndl = MV1LoadModel(SKY_PATH); }
}

//セット
void CBg::Set() {
	//当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(_Hndl, -1, TRUE);

	//拡大率セット、回転角度、座標セット
	MV1SetPosition(_Hndl, _Pos);
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_ColHndl, _Pos);
	MV1SetScale(_ColHndl, _Scale);
	MV1SetRotationXYZ(_ColHndl, _Rot);
	MV1SetPosition(_SkyHndl, _Pos);
	MV1SetScale(_SkyHndl, _SkyScale);
	MV1SetRotationXYZ(_SkyHndl, _SkyRot);

	//コリジョン情報構築
	MV1SetupCollInfo(_ColHndl);
}

//終了処理
void CBg::Fin() {
	//コリジョン情報破棄
	MV1TerminateCollInfo(_ColHndl);
	//フィールド画像破棄
	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
	//天球画像破棄
	if (_SkyHndl != -1) { MV1DeleteModel(_SkyHndl); _SkyHndl = -1; }
}

//メイン処理
void CBg::Step() {
	//天球回転処理
	_SkyRot._Y += SKY_SPD;

	_SkyRot._Y = MyLib::UnwindDegrees(_SkyRot._Y);
}

//描画処理
void CBg::Draw() {
	MV1DrawModel(_Hndl);			//フィールド描画
	MV1DrawModel(_SkyHndl);			//天球描画
}

//アップデート処理
void CBg::Update() {
	MV1SetPosition(_Hndl, _Pos);				//座標セット
	MV1SetPosition(_ColHndl, _Pos);				//座標セット
	MV1SetPosition(_SkyHndl, _SkyPos);			//座標セット
	MV1SetRotationXYZ(_SkyHndl, _SkyRot);		//天球回転角度セット

	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(_ColHndl, -1, TRUE);
}
