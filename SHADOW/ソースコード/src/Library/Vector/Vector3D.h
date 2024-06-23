#pragma once

#include "Vector2D.h"

namespace MyLib {
	// 3D�x�N�g����`(float�^)
	class Vector3D {
	public: // �����o�ϐ�
		float _X, _Y, _Z;

	public: // �R���X�g���N�^

		explicit constexpr Vector3D() noexcept : _X(0), _Y(0), _Z(0) {}
		explicit constexpr Vector3D(float xyz) noexcept : _X(xyz), _Y(xyz), _Z(xyz) {}
		explicit constexpr Vector3D(float x, float y, float z) noexcept : _X(x), _Y(y), _Z(z) {}
		constexpr Vector3D(const Vector3D& v) noexcept : _X(v._X), _Y(v._Y), _Z(v._Z) {}
		constexpr Vector3D(const VECTOR& v) noexcept : _X(v.x), _Y(v.y), _Z(v.z) {}

	public: // �X�^�e�B�b�N�֐�

		// (0, 0, 0)
		inline static constexpr Vector3D ZeroVec()		{ return Vector3D(0.f, 0.f, 0.f); }
		// (1, 1, 1)
		inline static constexpr Vector3D OneVec()		{ return Vector3D(1.f, 1.f, 1.f); }
		// (0, 1, 0)
		inline static constexpr Vector3D UpVec()		{ return Vector3D(0.f, 1.f, 0.f); }
		// (0, -1, 0)
		inline static constexpr Vector3D DownVec()		{ return Vector3D(0.f, -1.f, 0.f); }
		// (0, 0, 1)
		inline static constexpr Vector3D ForwardVec()	{ return Vector3D(0.f, 0.f, 1.f); }
		// (0, 0, -1)
		inline static constexpr Vector3D BackwardVec()	{ return Vector3D(0.f, 0.f, -1.f); }
		// (1, 0, 0)
		inline static constexpr Vector3D RightVec()		{ return Vector3D(1.f, 0.f, 0.f); }
		// (-1, 0, 0)
		inline static constexpr Vector3D LeftVec()		{ return Vector3D(-1.f, 0.f, 0.f); }
		// (1, 0, 0)
		inline static constexpr Vector3D XAxisVec()		{ return Vector3D(1.f, 0.f, 0.f); }
		// (0, 1, 0)
		inline static constexpr Vector3D YAxisVec()		{ return Vector3D(0.f, 1.f, 0.f); }
		// (0, 0, 1)
		inline static constexpr Vector3D ZAxisVec()		{ return Vector3D(0.f, 0.f, 1.f); }

		// �C�ӂ̃x�N�g���擾
		inline static Vector3D VGet(float X, float Y, float Z) { return Vector3D(X, Y, Z); }
		inline static Vector3D VGet(float XYZ) { return Vector3D(XYZ); }
		inline static Vector3D VGet(const VECTOR& V) { return Vector3D(V); }

	public: // ���Z�q�̃I�[�o�[���[�h

		// ���l�ݒ�
		inline Vector3D operator() (float xyz) { _X = xyz; _Y = xyz; _Z = xyz; return *this; }
		inline Vector3D operator() (float x, float y, float z) { _X = x; _Y = y; _Z = z; return *this; }
		inline Vector3D operator() (const Vector3D& v) { _X = v._X; _Y = v._Y; _Z = v._Z; return *this; }
		inline Vector3D operator() (const VECTOR& v) { _X = v.x; _Y = v.y; _Z = v.z; return *this; }

		/*
			�x�N�g�������Z
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z����
		*/
		Vector3D operator+(const Vector3D& v) const;
		/*
			�x�N�g�������Z(�R�s�[)
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator+=(const Vector3D& v);
		/*
			���͂��ꂽ���l���e�v�f���Ƃɉ��Z����
			�����F	Value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g��
		*/
		Vector3D operator+(float value) const;
		/*
			���͂��ꂽ���l���e�v�f���Ƃɉ��Z����(�R�s�[)
			�����F	Value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator+=(float value);
		/*
			�x�N�g�������Z
			(Vector3D�^�������ɂƂ�-���Z�q�̃I�[�o�[���[�h)
			�����F	V	:	���Z����x�N�g��(Vector3D�^)
			�߂�l�F���Z����
		*/
		Vector3D operator-(const Vector3D& v) const;
		/*
			�x�N�g�������Z(�R�s�[)
			(Vector3D�^�������ɂƂ�-=���Z�q�̃I�[�o�[���[�h)
			�����F	V	:	���Z����x�N�g��(Vector3D�^)
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator-=(const Vector3D& v);
		/*
			���͂��ꂽ���l���e�v�f���ƂɌ��Z����
			(float�^�����ɂƂ�-���Z�q�̃I�[�o�[���[�h)
			�����F	Value	:	���Z���鐔�l(float)
			�߂�l�F���Z�����x�N�g��
		*/
		Vector3D operator-(float value) const;
		/*
			���͂��ꂽ���l���e�v�f���ƂɌ��Z����(�R�s�[)
			(float�^�����ɂƂ�-=���Z�q�̃I�[�o�[���[�h)
			�����F	Value	:	���Z���鐔�l(float�^)
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator-=(float value);
		/*
			�x�N�g�����X�P�[���{
			�����F	V	:	�X�P�[���{����x�N�g��
			�߂�l�F�X�P�[���{����
		*/
		Vector3D operator*(const Vector3D& v) const;
		/*
			�x�N�g�����X�P�[���{(�R�s�[)
			�����F	V	:	�X�P�[���{����x�N�g��
			�߂�l�F�X�P�[���{�����x�N�g���̃R�s�[
		*/
		Vector3D operator*=(const Vector3D& v);
		/*
			���͂��ꂽ���l���e�v�f���ƂɃX�P�[���{����
			�����F	Value	:	�X�P�[���{���鐔�l
			�߂�l�F�X�P�[���{�����x�N�g��
		*/
		Vector3D operator*(float value) const;
		/*
			���͂��ꂽ���l���e�v�f���ƂɃX�P�[���{����(�R�s�[)
			�����F	Value	:	�X�P�[���{���鐔�l
			�߂�l�F�X�P�[���{�����x�N�g���̃R�s�[
		*/
		Vector3D operator*=(float value);
		/*
			�x�N�g�������Z
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z����
		*/
		Vector3D operator/(const Vector3D& v) const;
		/*
			�x�N�g�������Z(�R�s�[)
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator/=(const Vector3D& v);
		/*
			���͂��ꂽ���l���e�v�f���Ƃɏ��Z����
			�����F	Value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g��
		*/
		Vector3D operator/(float value) const;
		/*
			���͂��ꂽ���l���e�v�f���Ƃɏ��Z����(�R�s�[)
			�����F	Value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		Vector3D operator/=(float value);
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��
			�����F	V	:	���̓x�N�g��
			�߂�l�F�O�ό���
		*/
		Vector3D operator^(const Vector3D& v) const;
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��(�R�s�[)
			�����F	V	:	���̓x�N�g��
			�߂�l�F�O�ό��ʂ̃R�s�[
		*/
		Vector3D operator^=(const Vector3D& v);
		/*
			���g�Ɠ��̓x�N�g���Ƃ̓���
			�����F	V	:	���̓x�N�g��
			�߂�l�F���ό���
		*/
		float operator|(const Vector3D& v) const;
		/*
			�x�N�g���̔��]
			�߂�l�F���]����
		*/
		inline Vector3D operator-() const { return Vector3D(-_X, -_Y, -_Z); }
		/*
			�x�N�g���̑��
			�����F	V	:	����������x�N�g��(VECTOR)
			�߂�l�F�������
		*/
		inline Vector3D operator=(const VECTOR& v) { return this->operator()(v.x, v.y, v.z); }

	public: // �x�N�g���ɕK�v�Ȋ֐��Q

		/*
			�x�N�g���̐���
			�����F	V	:	�ڕW�Ƃ���x�N�g��
			�߂�l�F��������
		*/
		inline Vector3D Create(const Vector3D& v) const { return v - *this; }
		/*
			�x�N�g���̐��K��
			�߂�l�F���K�����ꂽ�x�N�g��
			�����̊֐���ǂ񂾎��_�Ŏ��g�̃x�N�g���𐳋K�����������܂�
		*/
		inline Vector3D Normalize() {
			// �x�N�g���̒������擾
			const float size = this->Long();
			if (size != 0.f && size != 1.f) {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}

			return *this;
		}
		/*
			//�|���S���̖@���x�N�g��
			�߂�l�F�|���S���̖@���x�N�g��
		*/
		const inline Vector3D PolygonNormalize(const Vector3D& v_b, const Vector3D& v_c) {
			// �x�N�g���̒������擾
			Vector3D vecAB = this->Create(v_b);
			Vector3D vecAC = this->Create(v_c);
			Vector3D vecABAC = vecAB ^ vecAC;

			vecABAC.Normalize();

			return vecABAC;
		}
		/*
			�x�N�g���̒������擾
			�����F	V	:	�n�_�x�N�g��(�f�t�H���g�͌��_)
			�߂�l�F�x�N�g���̒���
		*/
		inline float Long(const Vector3D& v = Vector3D::ZeroVec()) const {
			return Sqrt((Square(_X - v._X) + Square(_Y - v._Y) + Square(_Z - v._Z)));
		}
		/*
			�x�N�g���̂Q��̒������擾
			�����F	V	:	���_�x�N�g��(�f�t�H���g�͌��_)
			�߂�l�F�x�N�g���̒���(�Q��)
		*/
		inline float LongSq(const Vector3D& v = Vector3D::ZeroVec()) const {
			return Square(_X - v._X) + Square(_Y - v._Y) + Square(_Z - v._Z);
		}
		/*
			�C�R�[���֐�
			�����F	V			:	��r�������x�N�g��
					Tolerance	:	���e�덷
		*/
		inline bool Equals(const Vector3D& v, float tolerance = TOLERANCE) {
			return MyLib::Abs(_X - v._X) <= tolerance
				&& MyLib::Abs(_Y - v._Y) <= tolerance
				&& MyLib::Abs(_Z - v._Z) <= tolerance;
		}
		/*
			�S�Ă̗v�f���C�R�[�����ǂ���
			�����F	Tolerance	:	���e�덷
		*/
		inline bool AllComponentsEqual(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X - _Y) <= tolerance
				&& MyLib::Abs(_Y - _Z) <= tolerance
				&& MyLib::Abs(_Z - _X) <= tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖�������)
			�����F	Tolerance	:	���e�덷
		*/
		inline bool IsNearlyZero(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X) <= tolerance
				&& MyLib::Abs(_Y) <= tolerance
				&& MyLib::Abs(_Z) <= tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖������Ȃ� = ���S�Ƀ[���x�N�g��)
		*/
		const inline bool IsZero() {
			return _X == 0.f && _Y == 0.f && _Z == 0.f;
		}
		/*
			�����֌W�ɂ���x�N�g�����ǂ���
		*/
		const inline bool IsVertical(const Vector3D& v) {
			float d = *this | v;
			return MyLib::Abs(d) < TOLERANCE;		// �덷�͈͓��Ȃ琂���Ɣ���
		}
		/*
			���s�֌W�ɂ���x�N�g�����ǂ���
		*/
		const inline bool IsParallel(const Vector3D& v) {
			float d = (*this ^ v).LongSq();
			return MyLib::Abs(d) < TOLERANCE;		// �덷�͈͓��Ȃ畽�s�Ɣ���
		}
		/*
			�s�p�֌W���ǂ���
		*/
		const inline bool IsSharpAngle(const Vector3D& v) {
			return (*this | v) >= 0.f;
		}
		
		/*
			���g��Vector2D�ɕϊ�����(XY����)
		*/
		inline Vector2D ToVector2DXY() const { return Vector2D(_X, _Y); }
		/*
			���g��Vector2D�ɕϊ�����(XZ����)
		*/
		inline Vector2D ToVector2DXZ() const { return Vector2D(_X, _Z); }
		/*
			���g��Vector2D�ɕϊ�����(YZ����)
		*/
		inline Vector2D ToVector2DYZ() const { return Vector2D(_Y, _Z); }

		// DX���C�u�����x�N�g���\���̂ւ̃L���X�g���Z�q
		inline operator VECTOR() const { return {_X, _Y, _Z }; }

		// Vector2D�^�ւ̃L���X�g���Z�q
		inline operator Vector2D() const { return Vector2D(_X, _Y); }
	};

	/*
		�x�N�g���̃X�P�[�����O
		�����F	Scale	:	�X�P�[���{
				V		:	�X�P�[���{�������x�N�g��
		�߂�l�F�@�X�P�[���{���ꂽ�x�N�g��
	*/
	inline Vector3D operator*(float scale, const Vector3D& v) {
		return v.operator*(scale);
	}
	inline Vector3D GetPolygonNormalVec(Vector3D v_a, Vector3D v_b, Vector3D v_c) {
		// �x�N�g���̒������擾
		Vector3D vecAB = v_a.Create(v_b);
		Vector3D vecAC = v_a.Create(v_c);
		Vector3D vecABAC = vecAB ^ vecAC;

		return vecABAC.Normalize();
	}
	/*���ʂ���̍���(XY��)*/
	inline float GetTriangleHeightXY(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// �ӂɉ������x�N�g��AB��AC���v�Z
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// �ʖ@�����v�Z
		Vector3D vecNorm = (vecAB ^ vecAC);
		vecNorm.Normalize();
		// ���ʂ̕��������獂���iY���W���v�Z�j
		float z = (-vecNorm._X * (point._X - vertex_a._X) - vecNorm._Y * (point._Y - vertex_a._Y) + vecNorm._Z * vertex_a._Z) / vecNorm._Z;

		return z;
	}

	/*���ʂ���̍���(XZ��)*/
	inline float GetTriangleHeightXZ(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// �ӂɉ������x�N�g��AB��AC���v�Z
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// �ʖ@�����v�Z
		Vector3D vecNorm = (vecAB ^ vecAC);
		vecNorm.Normalize();
		// ���ʂ̕��������獂���iY���W���v�Z�j
		float y = (-vecNorm._X * (point._X - vertex_a._X) - vecNorm._Z * (point._Z - vertex_a._Z) + vecNorm._Y * vertex_a._Y) / vecNorm._Y;

		return y;
	}

	/*���ʂ���̍���(YZ��)*/
	inline float GetTriangleHeightYZ(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// �ӂɉ������x�N�g��AB��AC���v�Z
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// �ʖ@�����v�Z
		Vector3D vecNorm = vecAB ^ vecAC;
		vecNorm.Normalize();
		// ���ʂ̕��������獂���iY���W���v�Z�j
		float x = (-vecNorm._Y * (point._Y - vertex_a._Y) - vecNorm._Z * (point._Z - vertex_a._Z) + vecNorm._X * vertex_a._X) / vecNorm._X;

		return x;
	}
}

// ���O��Z�����邽��
using MyLib::Vector3D;