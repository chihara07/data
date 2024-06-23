#pragma once

#include "DxLib.h"

class CFrameRate
{
public:
	//コンストラクタ・デストラクタ
	CFrameRate();
	~CFrameRate();

public:
	static void Init();		//初期化
	static void Step();		//通常
	static void Update();	//更新
	static void Draw();		//描画

public:
	static bool IsExecutable();		//実行可能か調べる

private:
	static void CalcFrameRate();	//フレームレートの計算	CalcFPSと同じ
	static void DrawFrameRate();	//フレームレートの描画

private:
	static int _CurrentTime;				//現在の時間
	static int _LastFrameTime;				//前回のフレーム実行時の時間
	static int _FrameCnt;					//フレームカウント用
	static int _UpdateFrameRateTime;		//フレームレートを更新した時間
	static float _FrameRate;				//フレームレート（表示用）
};