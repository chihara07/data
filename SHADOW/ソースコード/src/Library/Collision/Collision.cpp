#include "DxLib.h"
#include "Collision.h"
#include "../../Library/Math/Math.h"

constexpr float HALF = 0.5f;		//����

// �~�̓����蔻��
bool CCollision::IsHitCircle(float x1, float y1, float r1, float x2, float y2, float r2)
{
	//�Q�̔��a�̍��v
	float sum_radius = r1 + r2;
	sum_radius *= sum_radius;

	//�~���m�̒���
	float x_len = x1 - x2;
	x_len *= x_len;

	float y_len = y1 - y2;
	y_len *= y_len;

	//�~�̓����蔻��
	if (sum_radius > x_len + y_len)
	{
		return true;
	}

	return false;
}

//�������蔻��
bool CCollision::IsHitSphere(Vector3D pos1, float r1, Vector3D pos2, float r2)
{
	// 2�_�Ԃ������Z����
	Vector3D dist = pos1 - pos2;
	// 2�_�Ԃ̋�����2����v�Z����
	float length = (dist._X * dist._X) + (dist._Y * dist._Y)
		+ (dist._Z * dist._Z);
	// ��̋��̔��a�𑫂���2�悷��
	float radius = (r1 + r2) * (r1 + r2);

	// �ŏI�I�ȓ����蔻��
	if (length < radius) return true;
	else return false;
}

// ��`�̓����蔻��
bool CCollision::IsHitRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 < x2 + w2 && x1 + w1 > x2 &&
		y1 + h1 > y2 && y1 < y2 + h2)
	{
		return true;
	}

	return false;
}

//�������蔻��
bool CCollision::IsHitBox(Vector3D pos1, Vector3D size1, Vector3D pos2, Vector3D size2)
{
	Vector3D halfSize1 = Vector3D::VGet( size1._X * HALF, size1._Y * HALF, size1._Z * HALF);
	Vector3D halfSize2 = Vector3D::VGet( size2._X * HALF, size2._Y * HALF, size2._Z * HALF);
	if (pos1._X - halfSize1._X < pos2._X + halfSize2._X
		&& pos1._X + halfSize1._X > pos2._X - halfSize2._X
		&& pos1._Y - halfSize1._Y < pos2._Y + halfSize2._Y
		&& pos1._Y + halfSize1._Y > pos2._Y - halfSize2._Y
		&& pos1._Z - halfSize1._Z < pos2._Z + halfSize2._Z
		&& pos1._Z + halfSize1._Z > pos2._Z - halfSize2._Z)
	{
		return true;
	}
	return false;
}

// XY���ʏ�ł̎O�p�`�̓����蔻��
bool CCollision::IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	Vector3D vecAB = vertexA.Create(vertexB); vecAB._Z = 0.0f;
	Vector3D vecBC = vertexB.Create(vertexC); vecBC._Z = 0.0f;
	Vector3D vecCA = vertexC.Create(vertexA); vecCA._Z = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	Vector3D vecAP = vertexA.Create(point); vecAP._Z = 0.0f;
	Vector3D vecBP = vertexB.Create(point); vecBP._Z = 0.0f;
	Vector3D vecCP = vertexC.Create(point); vecCP._Z = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	Vector3D vecABAP = (vecAB ^ vecAP);
	Vector3D vecBCBP = (vecBC ^ vecBP);
	Vector3D vecCACP = (vecCA ^ vecCP);

	// �e�O�ς�Z������0�ȉ��ł���Γ������Ă���
	if (vecABAP._Z >= 0 && vecBCBP._Z >= 0 && vecCACP._Z >= 0) {
		return true;
	}

	if (vecABAP._Z <= 0 && vecBCBP._Z <= 0 && vecCACP._Z <= 0) {
		return true;
	}

	return false;
}

// XZ���ʏ�ł̎O�p�`�̓����蔻��
bool CCollision::IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	Vector3D vecAB = vertexA.Create(vertexB); vecAB._Y = 0.0f;
	Vector3D vecBC = vertexB.Create(vertexC); vecBC._Y = 0.0f;
	Vector3D vecCA = vertexC.Create(vertexA); vecCA._Y = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	Vector3D vecAP = vertexA.Create(point); vecAP._Y = 0.0f;
	Vector3D vecBP = vertexB.Create(point); vecBP._Y = 0.0f;
	Vector3D vecCP = vertexC.Create(point); vecCP._Y = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	Vector3D vecABAP = (vecAB ^ vecAP);
	Vector3D vecBCBP = (vecBC ^ vecBP);
	Vector3D vecCACP = (vecCA ^ vecCP);

	// �e�O�ς�Y������0�ȉ��ł���Γ������Ă���
	if (vecABAP._Y >= 0 && vecBCBP._Y >= 0 && vecCACP._Y >= 0) {
		return true;
	}

	if (vecABAP._Y <= 0 && vecBCBP._Y <= 0 && vecCACP._Y <= 0) {
		return true;
	}


	return false;
}

// YZ���ʏ�ł̎O�p�`�̓����蔻��
bool CCollision::IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	Vector3D vecAB = vertexA.Create(vertexB); vecAB._X = 0.0f;
	Vector3D vecBC = vertexB.Create(vertexC); vecBC._X = 0.0f;
	Vector3D vecCA = vertexC.Create(vertexA); vecCA._X = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	Vector3D vecAP = vertexA.Create(point); vecAP._X = 0.0f;
	Vector3D vecBP = vertexB.Create(point); vecBP._X = 0.0f;
	Vector3D vecCP = vertexC.Create(point); vecCP._X = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	Vector3D vecABAP = (vecAB ^ vecAP);
	Vector3D vecBCBP = (vecBC ^ vecBP);
	Vector3D vecCACP = (vecCA ^ vecCP);

	// �e�O�ς�X������0�ȉ��ł���Γ������Ă���
	if (vecABAP._X >= 0 && vecBCBP._X >= 0 && vecCACP._X >= 0) {
		return true;
	}

	if (vecABAP._X <= 0 && vecBCBP._X <= 0 && vecCACP._X <= 0) {
		return true;
	}

	return false;
}
