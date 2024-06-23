#pragma once

#include "DxLib.h"
#include <vector>
#include "../Hndl/Path.h"
#include "../Hndl/HndlManager.h"

class CDrawManager {
private:
	static CDrawManager* _Instance;		//インスタンス

	//コンストラクタ・デストラクタ
	CDrawManager();
	~CDrawManager();

	//シングルトンなので他での生成を禁止
	CDrawManager(const CDrawManager& other);
	CDrawManager operator= (const CDrawManager& other) {}

	std::vector<int> _Hndl;		//ハンドル用配列

	//ハンドル取得
	CHndlManager* cHndlManager = CHndlManager::GetInstance();
public:
	//インスタンス取得
	static CDrawManager* GetInstance();
	//インスタンス削除
	static void DeleteInstance();

	//初期化
	void Init();
	//リセット
	void Reset();
	//ハンドルセット
	void SetHndl();
	/// <summary>
	/// 2D描画(int型)
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="x">= X座標</param>
	/// <param name="y">= Y座標</param>
	void Draw(PATH_TYPE id, int x, int y);
	/// <summary>
	/// 2D描画(float型)
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="x">= X座標</param>
	/// <param name="y">= Y座標</param>
	void Draw(PATH_TYPE id, float x, float y);
	/// <summary>
	/// 2D回転描画(int型)
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="x">= X座標</param>
	/// <param name="y">= Y座標</param>
	/// <param name="rate">= 拡大率</param>
	/// <param name="angle">= 回転角度</param>
	void Draw(PATH_TYPE id, int x, int y, float rate, float angle);
	/// <summary>
	/// 2D回転描画(float型)
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="x">= X座標</param>
	/// <param name="y">= Y座標</param>
	/// <param name="rate">= 拡大率</param>
	/// <param name="angle">= 回転角度</param>
	void Draw(PATH_TYPE id, float x, float y, float rate, float angle);
	/// <summary>
	/// ビルボード描画
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="pos">= 座標</param>
	/// <param name="cx">= 画像の中心X座標(0.f～1.f)</param>
	/// <param name="cy">= 画像の中心Y座標(0.f～1.f)</param>
	/// <param name="size">= サイズ</param>
	/// <param name="angle">= 回転角度</param>
	void Draw(PATH_TYPE id, VECTOR pos, float cx, float cy, float size, float angle);
	/// <summary>
	/// 2D拡大縮小描画
	/// </summary>
	/// <param name="id">= 画像ID</param>
	/// <param name="x1">= 画像左上X座標</param>
	/// <param name="y1">= 画像左上Y座標</param>
	/// <param name="x2">= 画像右下X座標</param>
	/// <param name="y2">= 画像右下Y座標</param>
	void Draw(PATH_TYPE id, int x1, int y1, int x2, int y2);
};