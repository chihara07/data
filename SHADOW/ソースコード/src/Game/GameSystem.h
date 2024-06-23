#pragma once
#include "DxLib.h"

//ゲーム用プロジェクトのシステムをまとめたもの
class CGameSystem
{
	//コンストラクタ、デストラクタを破棄する
	CGameSystem() = delete;
	~CGameSystem() = delete;

public:
	static void Start();		//ゲームの起動
	static void MainLoop();		//メインループ
	static void Fin();			//ゲームの後処理

private:
	static void Init();			//初期化
	static void Step();			//ステップ処理


public://アクセサー
	static bool IsGameEnd() { return _IsGemeEnd; }	//ゲームを終了させるか

	static void RequestGameEnd() { _IsGemeEnd = true; }	//ゲーム終了リクエスト

private:
	static bool _IsGemeEnd;	//ゲーム終了か
};
