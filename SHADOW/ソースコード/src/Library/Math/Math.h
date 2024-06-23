#pragma once

#include <math.h>
#include <string>

#define PI (3.1415926535897932384626433832795f)

namespace MyLib {
	/* ���e�덷 */
	constexpr float TOLERANCE = 0.0001f;
	/* ���p */
	constexpr float RIGHT_ANGLE = 90.0f * PI * (1 / 180.f);
	/* ���p */
	constexpr float STRAIGHT_ANGLE = 180.0f * PI * (1 / 180.f);

	/* ��Βl�擾 */
	template<class T>
	static inline T Abs(const T value) { return (value >= (T)0) ? value : -value; }

	/* �덷�����e����C�R�[���֐� */
	template <class T>
	static constexpr inline bool IsNearlyEqual(T a, T b, float Tolerance = TOLERANCE) { return Abs(a - b) <= Tolerance; }
	
	/* �덷�����e����[������֐� */
	template <class T>
	static constexpr inline bool IsNearlyZero(T a, float tolerance = TOLERANCE) { return Abs(a) <= tolerance; }
	
	/* �Q�̐��l�̍ő�l */
	template <class T>
	static constexpr inline T Max(T a, T b) { return (a >= b) ? a : b; }
	
	/* �R�̐��l�̍ő�l */
	template <class T>
	static constexpr inline T Max3(T a, T b, T c) {
		return Max(Max(a, b), c);
	}
	
	/* �Q�̐��l�̍ŏ��l */
	template <class T>
	static constexpr inline T Min(T a, T b) { return (a <= b) ? a : b; }
	
	/* �R�̐��l�̍ŏ��l */
	template <class T>
	static constexpr inline T Min3(T a, T b, T c) {
		return Min(Min(a, b), c);
	}

	/* �Q�̐��l�̍� */
	template<class T>
	static constexpr inline T Difference2(T a, T b) {
		// B���傫��
		if (a < b) {
			return (b - a);
		}
		// A���傫��
		else if (a > b) {
			return (a - b);
		}
		// ���l������
		else {
			return static_cast<T>(0);
		}
	}

	/* �X���b�v�֐� */
	template <class T>
	static constexpr inline void Swap(T* a, T* b) {
		const T temp = *a;
		*a = *b;
		*b = temp;
	}
	
	/* 
		�N�����v�֐� 
		�����F	value		:	�߂�l
				max			:	�ő�l
				min			:	�ŏ��l
	*/
	template<class T>
	static inline void Clamp(T* value, T max, T min) {
		if (max < *value) { *value = max; }
		else if (min > *value) { *value = min; }
	}

	/* �Q��̒l���擾 */
	template<class T>
	static inline  T Square(T value) { return value * value; }

	/* Sin�g���擾 */
	static inline float Sin(float rad) { return sinf(rad); }

	/* ���l�̌������擾 */
	static inline int GetDigit(int num) {
		return static_cast<int>(std::to_string(num).length()) - (num < 0 ? 1 : 0);
	}

	/*
		���߂�ꂽ�͈͂ł�Sin�g���擾
		�����F	min		:	�ŏ��l
				max		:	�ő�l
				rad		:	�p�x
	*/
	static inline float DefinedRangeSin(float min, float max, float rad) {
		const float mult = (max - min) / 2.f;
		return (Sin(rad) + 1.f) * mult + min;
	}

	/* �tSin�g���擾 */
	static inline float Asin(float rad) { return asinf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* �o�Ȑ�Sin�g���擾 */
	static inline float Sinh(float rad) { return sinhf(rad); }

	/* Cos�g���擾 */
	static inline float Cos(float rad) { return cosf(rad); }

	/* �tCos�g���擾 */
	static inline float Acos(float rad) { return acosf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* �o�Ȑ�Cos�g���擾 */
	static inline float Cosh(float rad) { return coshf(rad); }

	/* Tan�g���擾 */
	static inline float Tan(float rad) { return tanf(rad); }

	/* �tTan�g���擾 */
	static inline float Atan(float rad) { return atanf(rad); }

	/* �t�����擾 */
	static inline float Inv(float value) { return 1.f / value; }

	/* �������̒l���擾 */
	static inline float Sqrt(float value) { return sqrtf(value); }

	/* �������̋t���̒l���擾 */
	static inline float InvSqrt(float value) { return 1.f / sqrtf(value); }

	/* A��B��̒l���擾(float�^) */
	static inline float Pow(float a, float b) { return powf(a, b); }

	/* A��B��̒l���擾(int�^) */
	static inline int Pow(int a, int b) {
		float result = powf(static_cast<float>(a), static_cast<float>(b));

		return static_cast<int>(result);
	}

	/* �A�[�N�^���W�F���g */
	static inline float Atan2(float y, float x) {
		const float absX = Abs(x);
		const float absY = Abs(y);
		const bool yAbsBigger = (absY > absX);
		float t0 = yAbsBigger ? absY : absX;	/* Max(absY, absX) */
		float t1 = yAbsBigger ? absX : absY;	/* Min(absY, absX) */

		if (t0 == 0.f) { return 0.f; }

		float t3 = t1 / t0;
		float t4 = t3 * t3;

		static const float c[7] = {
			+7.2128853633444123e-03f,
			-3.5059680836411644e-02f,
			+8.1675882859940430e-02f,
			-1.3374657325451267e-01f,
			+1.9856563505717162e-01f,
			-3.3324998579202170e-01f,
			+1.0f
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
		t3 = (x < 0.0f) ? PI - t3 : t3;
		t3 = (y < 0.0f) ? -t3 : t3;

		return t3;
	}

	/*
		�]���藝����p�x���擾����
		�����F	a	:	���߂�p�x�̑Εӂ̒���
				b	:	���߂�p�x���͂��ޕ�1
				c	:	���߂�p�x���͂��ޕ�2
		�߂�l�F�p�x
	*/
	static inline float LawOfCosines(float a, float b, float c) {
		const float A = Square(b) + Square(c) - Square(a);
		const float B = 2.f * b * c;
		return Acos(A / B);
	}

	/* �^����ꂽ���W�A���p�� +/- �΂͈̔͊O�������ꍇ�A�͈͓��ɖ߂� */
	static inline float UnwindRadians(float degree) {
		while (degree > PI) {
			degree -= (PI * 2.f);
		}
		while (degree < -PI) {
			degree += (PI * 2.f);
		}

		return degree;
	}

	/* ��]�l��0 �` 2�΂̒l�ɂ��� */
	static inline void RadianNormalize(float* rad) {
		float result = *rad;
		if (result < 0.0f) {
			while (result < 0.0f) {
				result += PI * 2.f;
			}
		}
		else if (result > PI * 2.f) {
			while (result <= PI * 2.f) {
				result -= PI * 2.f;
			}
		}

		*rad = result;
	}

	/* �^����ꂽ�f�B�O���[�p��+/- 180�x�͈̔͊O�������ꍇ�A�͈͓��ɖ߂� */
	static inline float UnwindDegrees(float degree) {
		while (degree > 180.f) {
			degree -= 360.f;
		}
		while (degree < -180.f) {
			degree += 360.f;
		}
		return degree;
	}

	/* �f�B�O���[�p�����W�A���p�ɕϊ����� */
	static inline float ConvertDegreesToRadian(float degree) {
		return degree * PI * Inv(180.f);
	}
}