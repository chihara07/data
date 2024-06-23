#pragma once

#include "DxLib.h"
#include "../Math/Math.h"

namespace MyLib {
	// 2D�x�N�g����`(float�^)
	class Vector2D {
	public:
		// �X�^�e�B�b�N�֐�
		// �ϐ��錾���̏������֐�
		inline static Vector2D VGet(float x, float y) { return Vector2D(x, y); }
		inline static Vector2D VGet(float xy) { return Vector2D(xy, xy); }
		inline static Vector2D VGet(const VECTOR& v) { return Vector2D(v.x, v.y); }

		// �[���x�N�g��
		inline static Vector2D ZeroVec() { return Vector2D(0.f, 0.f); }

		/*
			�S�Ă̗v�f�𑫂����킹��
			�����F vec �������킹�����x�N�g��
			�߂�l�F ����
		*/
		inline static float AllElementVec2DAdd(const Vector2D& v) { return (v._X + v._Y); }

	public:
		// �R���X�g���N�^
		constexpr Vector2D() noexcept :_X(0.f), _Y(0.f) {}
		explicit constexpr Vector2D(float xy) noexcept : _X(xy), _Y(xy) {}
		constexpr Vector2D(float x, float y) noexcept : _X(x), _Y(y) {}
		constexpr Vector2D(const Vector2D& v) noexcept : _X(v._X), _Y(v._Y) {}
		constexpr Vector2D(const VECTOR& v) noexcept : _X(v.x), _Y(v.y) {}

	public:
		// �I�y���[�^�[�̃I�[�o�[���[�h�錾
		// ���l�ݒ�
		inline Vector2D operator()(float xy) { _X = xy; _Y = xy; return *this; }
		inline Vector2D operator()(float x, float y) { _X = x; _Y = y; return *this; }
		inline Vector2D operator()(const Vector2D& v) { _X = v._X; _Y = v._Y; return *this; }

		/*
			�x�N�g���̉��Z
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z����
		*/
		inline Vector2D operator+(const Vector2D& v) const { return Vector2D(_X + v._X, _Y + v._Y); }
		/*
			�x�N�g���̉��Z�R�s�[
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator+=(const Vector2D& v) { return *this = *this + v; }
		/*
			�x�N�g���̉��Z(���͂��ꂽ���l���e�v�f���ꂼ����Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z����
		*/
		inline Vector2D operator+(float value) const { return Vector2D(_X + value, _Y + value); }
		/*
			�x�N�g���̉��Z�R�s�[(���͂��ꂽ���l���e�v�f���ꂼ����Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator+=(float value) { return *this = *this + value; }
		/*
			�x�N�g���̌��Z
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z����
		*/
		inline Vector2D operator-(const Vector2D& v) const { return Vector2D(_X - v._X, _Y - v._Y); }
		/*
			�x�N�g���̌��Z�R�s�[
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator-=(const Vector2D& v) { return Vector2D(_X - v._X, _Y - v._Y); }
		/*
			�x�N�g���̌��Z(���͂��ꂽ���l���e�v�f���ꂼ�ꌸ�Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z����
		*/
		inline Vector2D operator-(float value) const { return Vector2D(_X - value, _Y - value); }
		/*
			�x�N�g���̌��Z�R�s�[(���͂��ꂽ���l���e�v�f���ꂼ�ꌸ�Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator-=(float value) { return *this = *this - value; }
		/*
			�x�N�g���̃X�P�[���{
			�����F	V	:	�X�P�[���{����x�N�g��
			�߂�l�F�X�P�[���{��������
		*/
		inline Vector2D operator*(const Vector2D& v) const { return this->Scale(v); }
		/*
			�x�N�g���̃X�P�[���{(���͂��ꂽ���l���e�v�f���ꂼ��X�P�[���{����)
			�����F	value	:	�X�P�[���{���鐔�l
			�߂�l�F���Z����
		*/
		inline Vector2D operator*(float value) const { return this->Scale(value); }
		/*
			�x�N�g���̃X�P�[���{�R�s�[
			�����F	V	:	�X�P�[���{����x�N�g��
			�߂�l�F�X�P�[���{�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator*=(const Vector2D& v) { return *this = *this * v; }
		/*
			�x�N�g���̃X�P�[���{�R�s�[(���͂��ꂽ���l���e�v�f���ꂼ��X�P�[���{����)
			�����F	value	:	�X�P�[���{���鐔�l
			�߂�l�F�X�P�[���{�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator*=(float value) { return *this = *this * value; }
		/*
			�x�N�g���̏��Z(���͂��ꂽ���l���e�v�f���ꂼ�ꏜ�Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z����
		*/
		inline Vector2D operator/(float value) { return Vector2D(_X / value, _Y / value); }
		/*
			�x�N�g���̏��Z
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z����
		*/
		inline Vector2D operator/(const Vector2D& v) { return Vector2D(_X / v._X, _Y / v._Y); }
		/*
			�x�N�g���̏��Z�R�s�[(���͂��ꂽ���l���e�v�f���ꂼ�ꏜ�Z����)
			�����F	value	:	���Z���鐔�l
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator/=(float value) { return *this = *this / value; }
		/*
			�x�N�g���̏��Z�R�s�[
			�����F	V	:	���Z����x�N�g��
			�߂�l�F���Z�����x�N�g���̃R�s�[
		*/
		inline Vector2D operator/=(const Vector2D& v) { return *this = *this / v; }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��
			�����F	V	:	���̓x�N�g��
			�߂�l�F�O�ό���
		*/
		inline float operator^(const Vector2D& v) { return this->Cross(v); }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̓���
			�����F	V	:	���̓x�N�g��
			�߂�l�F���ό���
		*/
		inline float operator|(const Vector2D& v) { return this->Dot(v); }

		/*
			�x�N�g���̔��]
			�߂�l�F���]�����x�N�g��
		*/
		inline Vector2D operator-() const { return Vector2D(-_X, -_Y); }
		/*
			�x�N�g���̑��
			�߂�l�F�������
		*/
		inline Vector2D operator=(const VECTOR& v) { _X = v.x; _Y = v.y; return *this; }

		// �x�N�g���̗v�f�����ꂩ
		inline bool operator==(const Vector2D& v) const { return (_X == v._X && _Y == v._Y); }
		inline bool operator!=(const Vector2D& v) const { return !(*this == v); }

		// ��r���Z
		inline bool operator>=(const Vector2D& v)	const { return _X >= v._X	  && _Y >= v._Y;	 }
		inline bool operator> (const Vector2D& v)	const { return _X >  v._X   && _Y >  v._Y;	 }
		inline bool operator>=(float value)			const { return _X >= value && _Y >= value; }
		inline bool operator> (float value)			const { return _X >  value && _Y >  value; }

		inline bool operator<=(const Vector2D& v)	const { return _X <= v._X	  && _Y <= v._Y;	 }
		inline bool operator< (const Vector2D& v)	const { return _X <  v._X   && _Y <  v._Y;	 }
		inline bool operator<=(float value)			const { return _X <= value && _Y <= value; }
		inline bool operator< (float value)			const { return _X <  value && _Y <  value; }

		//DX���C�u�����x�N�g���\���̂ւ̃L���X�g���Z�q
		inline operator VECTOR() const { return VECTOR{ (float)_X, (float)_Y, 0.f }; }

	public:
		/*
			�x�N�g���̃X�P�[���{(���͂��ꂽ���l���e�v�f���ꂼ��X�P�[���{����)
			�����F	value	:	�X�P�[���{���鐔�l
			�߂�l�F���Z����
		*/
		inline Vector2D Scale(float value) const { return Vector2D(_X * value, _Y * value); }
		/*
			�x�N�g���̃X�P�[���{
			�����F	V	:	�X�P�[���{����x�N�g��
			�߂�l�F�X�P�[���{��������
		*/
		inline Vector2D Scale(const Vector2D& v) const { return Vector2D(_X * v._X, _Y * v._Y); }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��
			�����F	V	:	���̓x�N�g��
			�߂�l�F�O�ό���
		*/
		inline float Cross(const Vector2D& v) const { return _X * v._Y - _Y * v._X; }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̓���
			�����F	V	:	���̓x�N�g��
			�߂�l�F���ό���
		*/
		inline float Dot(const Vector2D& v) const { return _X * v._X + _Y * v._Y; }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊Ԃł̃x�N�g������
			�����F	V	:	���̓x�N�g��
			�߂�l�F��������
		*/
		inline Vector2D Create(const Vector2D& v) const { return Vector2D(v._X - _X, v._Y - _Y); }
		/*
			���̓x�N�g���̒���
			�����F	V	:	�n�_�x�N�g��
			�߂�l�F�n�_�x�N�g�����玩�g�ւ̒���
		*/
		inline float Long(const Vector2D& v = Vector2D::VGet(0.f, 0.f)) const { return sqrtf((_X - v._X) * (_X - v._X) + (_Y - v._Y) * (_Y - v._Y)); }
		/*
			���̓x�N�g���̒���(2��)
			�����F	V	:	�n�_�x�N�g��
			�߂�l�F�n�_�x�N�g�����玩�g�ւ̒���(2��)
		*/
		inline float LongSq(const Vector2D& v = Vector2D::VGet(0.f, 0.f)) const { return Square(_X - v._X) + Square(_Y - v._Y); }
		/*
			�x�N�g���̐��K��
			�߂�l�F���K�����ꂽ�x�N�g��
		*/
		Vector2D Normalize() {
			//�C�����C�������Ă��Ȃ��̂�size�ϐ��̖������ɂ��G���[����̈�
			float size = this->Long();
			if (size == 0.0f || size == 1.0f) { return *this; }
			else {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖�������)
			�����F	Tolerance	:	���e�덷
		*/
		inline bool IsNearlyZero(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X) <= tolerance
				&& MyLib::Abs(_Y) <= tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖������Ȃ� = ���S�Ƀ[���x�N�g��)
		*/
		inline bool IsZero() {
			return _X == 0.f && _Y == 0.f;
		}

	public:
		float _X, _Y;
	};

	/*
		�x�N�g���̃X�P�[�����O
		�����F	Scale	:	�X�P�[���{
				V		:	�X�P�[�����O�������x�N�g��
		�߂�l�F���Z����
	*/
	inline Vector2D operator*(float scale, const Vector2D& v) {
		return v.operator*(scale);
	}
}

using MyLib::Vector2D;
