#pragma once
#include "../../Library/Vector/Vector3D.h"

//�����蔻��N���X
class CCollision {
public:
	/// <summary>
	/// // �~�̓����蔻��
	/// </summary>
	/// <param name="x1">:�Ώ�1��x���W</param>
	/// <param name="y1">:�Ώ�1��y���W</param>
	/// <param name="r1">:�Ώ�1�̔��a</param>
	/// <param name="x2">:�Ώ�2��x���W</param>
	/// <param name="y2">:�Ώ�2��y���W</param>
	/// <param name="r2">:�Ώ�2�̔��a</param>
	/// <returns></returns>
	static bool IsHitCircle(float x1, float y1, float r1, float x2, float y2, float r2);

	/// <summary>
	/// // ��`�̓����蔻��
	/// </summary>
	/// <param name="x1">:�Ώ�1�̍���x���W</param>
	/// <param name="y1">:�Ώ�1�̍���y���W</param>
	/// <param name="w1">:�Ώ�1�̉���</param>
	/// <param name="h1">:�Ώ�1�̍���</param>
	/// <param name="x2">:�Ώ�2�̍���x���W</param>
	/// <param name="y2">:�Ώ�2�̍���y���W</param>
	/// <param name="w2">:�Ώ�2�̉���</param>
	/// <param name="h2">:�Ώ�2�̍���</param>
	/// <returns></returns>
	static bool IsHitRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

	/// <summary>
	/// //�������蔻��
	/// </summary>
	/// <param name="pos1">:�Ώ�1�̍��W</param>
	/// <param name="r1">:�Ώ�1�̔��a</param>
	/// <param name="pos2">:�Ώ�2�̍��W</param>
	/// <param name="r2">:�Ώ�2�̔��a</param>
	/// <returns></returns>
	static bool IsHitSphere(Vector3D pos1, float r1, Vector3D pos2, float r2);

	/// <summary>
	/// //�������蔻��
	/// </summary>
	/// <param name="pos1">:�Ώ�1�̍��W</param>
	/// <param name="size1">:�Ώ�1�̕�</param>
	/// <param name="pos2">:�Ώ�2�̍��W</param>
	/// <param name="size2">:�Ώ�2�̕�</param>
	/// <returns></returns>
	static bool IsHitBox(Vector3D pos1, Vector3D size1, Vector3D pos2, Vector3D size2);

	/// <summary>
	/// // XY���ʏ�ł̎O�p�`�̓����蔻��
	/// </summary>
	/// <param name="point">:�Ώۂ̍��W</param>
	/// <param name="vertexA">:�O�p�`�̒��_A</param>
	/// <param name="vertexB">:�O�p�`�̒��_B</param>
	/// <param name="vertexC">:�O�p�`�̒��_C</param>
	/// <returns></returns>
	static bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

	/// <summary>
	/// // XZ���ʏ�ł̎O�p�`�̓����蔻��
	/// </summary>
	/// <param name="point">:�Ώۂ̍��W</param>
	/// <param name="vertexA">:�O�p�`�̒��_A</param>
	/// <param name="vertexB">:�O�p�`�̒��_B</param>
	/// <param name="vertexC">:�O�p�`�̒��_C</param>
	/// <returns></returns>
	static bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

	/// <summary>
	/// // YZ���ʏ�ł̎O�p�`�̓����蔻��
	/// </summary>
	/// <param name="point">:�Ώۂ̍��W</param>
	/// <param name="vertexA">:�O�p�`�̒��_A</param>
	/// <param name="vertexB">:�O�p�`�̒��_B</param>
	/// <param name="vertexC">:�O�p�`�̒��_C</param>
	/// <returns></returns>
	static bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);
};
