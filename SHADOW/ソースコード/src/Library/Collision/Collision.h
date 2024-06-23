#pragma once
#include "../../Library/Vector/Vector3D.h"

//当たり判定クラス
class CCollision {
public:
	/// <summary>
	/// // 円の当たり判定
	/// </summary>
	/// <param name="x1">:対象1のx座標</param>
	/// <param name="y1">:対象1のy座標</param>
	/// <param name="r1">:対象1の半径</param>
	/// <param name="x2">:対象2のx座標</param>
	/// <param name="y2">:対象2のy座標</param>
	/// <param name="r2">:対象2の半径</param>
	/// <returns></returns>
	static bool IsHitCircle(float x1, float y1, float r1, float x2, float y2, float r2);

	/// <summary>
	/// // 矩形の当たり判定
	/// </summary>
	/// <param name="x1">:対象1の左上x座標</param>
	/// <param name="y1">:対象1の左上y座標</param>
	/// <param name="w1">:対象1の横幅</param>
	/// <param name="h1">:対象1の高さ</param>
	/// <param name="x2">:対象2の左上x座標</param>
	/// <param name="y2">:対象2の左上y座標</param>
	/// <param name="w2">:対象2の横幅</param>
	/// <param name="h2">:対象2の高さ</param>
	/// <returns></returns>
	static bool IsHitRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

	/// <summary>
	/// //球当たり判定
	/// </summary>
	/// <param name="pos1">:対象1の座標</param>
	/// <param name="r1">:対象1の半径</param>
	/// <param name="pos2">:対象2の座標</param>
	/// <param name="r2">:対象2の半径</param>
	/// <returns></returns>
	static bool IsHitSphere(Vector3D pos1, float r1, Vector3D pos2, float r2);

	/// <summary>
	/// //箱当たり判定
	/// </summary>
	/// <param name="pos1">:対象1の座標</param>
	/// <param name="size1">:対象1の幅</param>
	/// <param name="pos2">:対象2の座標</param>
	/// <param name="size2">:対象2の幅</param>
	/// <returns></returns>
	static bool IsHitBox(Vector3D pos1, Vector3D size1, Vector3D pos2, Vector3D size2);

	/// <summary>
	/// // XY平面上での三角形の当たり判定
	/// </summary>
	/// <param name="point">:対象の座標</param>
	/// <param name="vertexA">:三角形の頂点A</param>
	/// <param name="vertexB">:三角形の頂点B</param>
	/// <param name="vertexC">:三角形の頂点C</param>
	/// <returns></returns>
	static bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

	/// <summary>
	/// // XZ平面上での三角形の当たり判定
	/// </summary>
	/// <param name="point">:対象の座標</param>
	/// <param name="vertexA">:三角形の頂点A</param>
	/// <param name="vertexB">:三角形の頂点B</param>
	/// <param name="vertexC">:三角形の頂点C</param>
	/// <returns></returns>
	static bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

	/// <summary>
	/// // YZ平面上での三角形の当たり判定
	/// </summary>
	/// <param name="point">:対象の座標</param>
	/// <param name="vertexA">:三角形の頂点A</param>
	/// <param name="vertexB">:三角形の頂点B</param>
	/// <param name="vertexC">:三角形の頂点C</param>
	/// <returns></returns>
	static bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);
};
