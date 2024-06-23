#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "DxLib.h"

#define PHI_F 3.141592653f

//�x�N�g����s��̌v�Z�������܂Ƃ߂��N���X
class MyMath
{
public:
	static VECTOR VecCreate(VECTOR PosA, VECTOR PosB);//�x�N�g���쐬
	static float VecLong(VECTOR Vec);//�x�N�g���̒���
	static VECTOR VecAdd(VECTOR vecA, VECTOR vecB);//�x�N�g���̑����Z
	static VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);//�x�N�g���̈����Z
	static VECTOR VecScale(VECTOR vec, float scale);//�x�N�g���̃X�J���[�{
	static float VecDot(VECTOR vecA, VECTOR vecB);//�x�N�g���̓���
	static VECTOR VecCross(VECTOR vecA, VECTOR vecB);//�x�N�g���̊O��
	static VECTOR VecNormalize(VECTOR vec);//�x�N�g���̐��K��
	static VECTOR GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);//�|���S���̖@���x�N�g��
	static float GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float Abs(float val);
	static float GetDistance(VECTOR posA, VECTOR posB);
};
#endif