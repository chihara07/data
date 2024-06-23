#include "FrameRate.h"
#include "../Color.h"

//変数の初期化
int CFrameRate::_CurrentTime = 0;				//現在の時間
int CFrameRate::_LastFrameTime = 0;				//前回のフレーム実行時の時間
int CFrameRate::_FrameCnt = 0;					//フレームカウント用
int CFrameRate::_UpdateFrameRateTime = 0;		//フレームレートを更新した時間
float CFrameRate::_FrameRate = 0.0f;			//フレームレート（表示用）

//フレームレートの名前空間
namespace FrameRate
{
	constexpr float		GAME_FRAME_RATE			= 60.0f;					//ゲームのフレームレート
	constexpr float		ONE_SECOND_MILI_TIME	= 1000.0f;					//1秒(ミリ秒)
	constexpr float		FRAME_TIME				= ONE_SECOND_MILI_TIME / GAME_FRAME_RATE;				//1フレームの時間
	constexpr VECTOR	DRAW_FRAMERATE_POSITION	= { 10.0f, 10.0f, 0.0f };	//フレームレートの描画位置
	constexpr int		DRAW_FRAMERATE_COLOR	= 0x000000;					//フレームレートの描画色(白)
}
//名前空間省略
using namespace FrameRate;

CFrameRate::CFrameRate()
{
	_CurrentTime = 0;
	_LastFrameTime = 0;
	_FrameCnt = 0;
	_UpdateFrameRateTime = 0;
	_FrameRate = 0.0f;
}

CFrameRate::~CFrameRate()
{
}

//初期化
void CFrameRate::Init()
{
	_CurrentTime = 0;
	_LastFrameTime = 0;
	_FrameCnt = 0;
	_UpdateFrameRateTime = 0;
	_FrameRate = 0.0f;
}

//通常
void CFrameRate::Step()
{
	//現在の時刻を取得
	_CurrentTime = GetNowCount();

	//最初のループなら
	//現在の時間を、FPSの計算をした時間に設定
	if (_UpdateFrameRateTime == 0.0f)
	{
		_UpdateFrameRateTime = _CurrentTime;
		_FrameRate = GAME_FRAME_RATE;
	}
}

//更新
void CFrameRate::Update()
{
	//フレーム実行時の時間を更新
	_LastFrameTime = _CurrentTime;

	//フレーム数をカウント
	_FrameCnt++;

	//フレームレートの計算
	CalcFrameRate();
}

//描画
void CFrameRate::Draw()
{
	DrawFrameRate();
}

//実行可能か調べる
bool CFrameRate::IsExecutable()
{
	// 現在の時刻が、前回のフレーム時より
	// 1/60秒経過していたら処理を実行する
	if (_CurrentTime - _LastFrameTime >= (int)FRAME_TIME) {
		return true;
	}
	else
	return false;
}


//フレームレートの計算
void CFrameRate::CalcFrameRate()
{
	//前回のフレームレート更新からの経過時間を求める
	int nDifTime = _CurrentTime - _UpdateFrameRateTime;

	//前回のフレームレート更新から
	//１秒以上経過していたらフレームレートを更新する
	if (nDifTime > ONE_SECOND_MILI_TIME)
	{
		//フレーム回数をミリ秒に合わせる
		float fFrameCnt = ((float)_FrameCnt * ONE_SECOND_MILI_TIME);

		//フレームレートを求める
		//理想どおりなら 60000 / 1000 で 60 となる
		_FrameRate = fFrameCnt / nDifTime;

		//フレームカウントをクリア
		_FrameCnt = 0;

		//フレームレート更新時間を更新
		_UpdateFrameRateTime = _CurrentTime;
	}
}

//フレームレートの描画
void CFrameRate::DrawFrameRate()
{
	DrawFormatString(static_cast<int>(DRAW_FRAMERATE_POSITION.x), static_cast<int>(DRAW_FRAMERATE_POSITION.y),
		COLOR::RED, "FPS[%.2f]", _FrameRate);
}
