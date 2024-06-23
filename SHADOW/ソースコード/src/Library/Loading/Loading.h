#pragma once

#include "DxLib.h"
#include "../Vector/Vector3D.h"

constexpr int LOAD_HNDL_NUM = 12;		//画像数
constexpr int LOAD_ANIM_MAX_CNT = 3;	//最大アニメーションカウント

class CLoading {
private:
	static Vector2D _Pos;					//画像座標
	static int _Hndl[LOAD_HNDL_NUM];		//画像ハンドル
	static int _Cnt;						//カウント
	static int _AnimCnt;					//アニメーションカウント
	static int _HndlID;						//画像ID
	static bool _IsLoading;					//ロードしているかフラグ
	static bool _IsLoad;					//ロードしたかフラグ
public:
	//コンストラクタ・デストラクタ
	CLoading();
	~CLoading();
	//初期化
	static void Init();
	//読み込み(ほかの読み込みはこれの後に行う)
	static void Load();
	//ロード開始
	static void LoadStart();
	//描画
	static void Draw();
	//メイン処理
	static void Step();
	//終了
	static void Fin();
	//ロード終了
	static void LoadEnd();
	//ロード画面を終了できるか
	static bool IsLoadEnd();
	//ロードしているかフラグ取得
	static bool GetLoading();
	//ロードしているかフラグセット
	static void SetLoading(bool f);
	//ロードしたかフラグ取得
	static bool GetLoad();
	//ロードしたかフラグセット
	static void SetLoad(bool f);
	//カウントリセット
	static void Reset();
};