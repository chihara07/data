#pragma once

#include "DxLib.h"

// カラーをまとめた名前空間
namespace COLOR {
	static const unsigned int BLACK =		GetColor(	0,	0,	0);		// 黒
	static const unsigned int WHITE =		GetColor( 255,255,255);		// 白
	static const unsigned int GLEY =		GetColor( 113,115,117);		// 灰色
	static const unsigned int RED =			GetColor( 255,	0,	0);		// 赤
	static const unsigned int GREEN =		GetColor(	0,255,	0);		// 緑
	static const unsigned int BLUE =		GetColor(	0,	0,255);		// 青
	static const unsigned int YELLOW =		GetColor( 255,255,	0);		// 黄
	static const unsigned int AQUA =		GetColor(	0,255,255);		// 海
	static const unsigned int LIGHTYELLOW = GetColor( 255,255,224);		// ライトイエロー
	static const unsigned int LIGHTBLUE =	GetColor( 173,216,230);		// ライトブルー
	static const unsigned int GREENYELLOW = GetColor( 173,255, 47);		// グリーンイエロー
	static const unsigned int YELLOWGREEN = GetColor( 154,205,	0);		// イエローグリーン
	static const unsigned int SPRINGGREEN = GetColor(	0,255,127);		// エメラルドグリーン
	static const unsigned int PINK =		GetColor( 255,192,203);		// ピンク
	static const unsigned int LIGHTPINK =	GetColor( 255,182,193);		// ライトピンク
}
