#include "Loading.h"
#include "../../Game/Hndl/HndlManager.h"

//変数の初期化
Vector2D CLoading::_Pos(0.f);					//画像座標
int CLoading::_Hndl[LOAD_HNDL_NUM] = { -1 };	//画像ハンドル
int CLoading::_Cnt = 0;							//ロード画面カウント
int CLoading::_AnimCnt = 0;						//アニメーションカウント
int CLoading::_HndlID = 0;						//画像ID
bool CLoading::_IsLoading = false;				//ロードしているかフラグ
bool CLoading::_IsLoad = false;					//ロードしたかフラグ

constexpr int LOAD_LOWEST_TIME = 90;			//ロード画面描画最低時間
//ロード画面
constexpr char BG_LOADING[] = "data/Image/load.png";
//ロード画面画像パス
static constexpr char LOADING_PATH[LOAD_HNDL_NUM][128] = {
	"data/Image/loading1.png",
	"data/Image/loading2.png",
	"data/Image/loading3.png",
	"data/Image/loading4.png",
	"data/Image/loading5.png",
	"data/Image/loading6.png",
	"data/Image/loading7.png",
	"data/Image/loading8.png",
	"data/Image/loading9.png",
	"data/Image/loading10.png",
	"data/Image/loading11.png",
	"data/Image/loading12.png",
};

//コンストラクタ・デストラクタ
CLoading::CLoading() {
	_Pos(0.f);
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		_Hndl[hndl_index] = -1;
	}
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = false;
	_IsLoad = false;
}
CLoading::~CLoading() {
	
}

//初期化
void CLoading::Init() {
	_Pos(0.f);
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		_Hndl[hndl_index] = -1;
	}
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = true;
	_IsLoad = false;
	//念のため非同期読み込みフラグオフ
	SetUseASyncLoadFlag(FALSE);
}

//読み込み(ほかの読み込みはこれの後に行う)
void CLoading::Load() {
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		if (_Hndl[hndl_index] == -1) _Hndl[hndl_index] = LoadGraph(LOADING_PATH[hndl_index]);
	}
}

//ロード開始
void CLoading::LoadStart() {
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = true;
	_IsLoad = false;

	//非同期読み込みフラグオン
	SetUseASyncLoadFlag(TRUE);
}

//描画
void CLoading::Draw() {
	DrawGraphF(_Pos._X, _Pos._Y, _Hndl[_HndlID % LOAD_HNDL_NUM], TRUE);
}

//メイン処理
void CLoading::Step() {
	//最低ロード時間までカウントする
	if(_Cnt < LOAD_LOWEST_TIME) _Cnt++;

	//アニメーション時間を超えたら次の画像へ
	if (_AnimCnt >= LOAD_ANIM_MAX_CNT) {
		_AnimCnt = 0;
		_HndlID++;
	}
	//アニメーション時間をカウントする
	_AnimCnt++;
}

//終了
void CLoading::Fin() {
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		if (_Hndl[hndl_index] != -1) _Hndl[hndl_index] = -1;
	}
}

//ロード終了
void CLoading::LoadEnd() {
	SetLoading(false);
	SetLoad(false);
	//念のため非同期読み込みフラグオフ
	SetUseASyncLoadFlag(FALSE);
}

//ロード画面を終了できるか
bool CLoading::IsLoadEnd() {
	//読み込みが終了しているかつ最低ロード時間を超えているならロード終了
	if (GetASyncLoadNum() == 0 && _Cnt >= LOAD_LOWEST_TIME)
		return true;

	return false;
}

//ロードしているかフラグ取得
bool CLoading::GetLoading() { return _IsLoading; }

//ロードしているかフラグセット
void CLoading::SetLoading(bool f) { _IsLoading = f; }

//ロードしたかフラグ取得
bool CLoading::GetLoad() { return _IsLoad; }

//ロードしたかフラグセット
void CLoading::SetLoad(bool f) { _IsLoad = f; }

//カウントリセット
void CLoading::Reset() { _Cnt = 0; }
