#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "DxLib.h"

#define PHI_F 3.141592653f

//ベクトルや行列の計算処理をまとめたクラス
class MyMath
{
public:
	static VECTOR VecCreate(VECTOR PosA, VECTOR PosB);//ベクトル作成
	static float VecLong(VECTOR Vec);//ベクトルの長さ
	static VECTOR VecAdd(VECTOR vecA, VECTOR vecB);//ベクトルの足し算
	static VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);//ベクトルの引き算
	static VECTOR VecScale(VECTOR vec, float scale);//ベクトルのスカラー倍
	static float VecDot(VECTOR vecA, VECTOR vecB);//ベクトルの内積
	static VECTOR VecCross(VECTOR vecA, VECTOR vecB);//ベクトルの外積
	static VECTOR VecNormalize(VECTOR vec);//ベクトルの正規化
	static VECTOR GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);//ポリゴンの法線ベクトル
	static float GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float Abs(float val);
	static float GetDistance(VECTOR posA, VECTOR posB);
};
#endif