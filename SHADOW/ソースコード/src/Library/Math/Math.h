#pragma once

#include <math.h>
#include <string>

#define PI (3.1415926535897932384626433832795f)

namespace MyLib {
	/* 寛容誤差 */
	constexpr float TOLERANCE = 0.0001f;
	/* 直角 */
	constexpr float RIGHT_ANGLE = 90.0f * PI * (1 / 180.f);
	/* 平角 */
	constexpr float STRAIGHT_ANGLE = 180.0f * PI * (1 / 180.f);

	/* 絶対値取得 */
	template<class T>
	static inline T Abs(const T value) { return (value >= (T)0) ? value : -value; }

	/* 誤差を許容するイコール関数 */
	template <class T>
	static constexpr inline bool IsNearlyEqual(T a, T b, float Tolerance = TOLERANCE) { return Abs(a - b) <= Tolerance; }
	
	/* 誤差を許容するゼロ判定関数 */
	template <class T>
	static constexpr inline bool IsNearlyZero(T a, float tolerance = TOLERANCE) { return Abs(a) <= tolerance; }
	
	/* ２つの数値の最大値 */
	template <class T>
	static constexpr inline T Max(T a, T b) { return (a >= b) ? a : b; }
	
	/* ３つの数値の最大値 */
	template <class T>
	static constexpr inline T Max3(T a, T b, T c) {
		return Max(Max(a, b), c);
	}
	
	/* ２つの数値の最小値 */
	template <class T>
	static constexpr inline T Min(T a, T b) { return (a <= b) ? a : b; }
	
	/* ３つの数値の最小値 */
	template <class T>
	static constexpr inline T Min3(T a, T b, T c) {
		return Min(Min(a, b), c);
	}

	/* ２つの数値の差 */
	template<class T>
	static constexpr inline T Difference2(T a, T b) {
		// Bが大きい
		if (a < b) {
			return (b - a);
		}
		// Aが大きい
		else if (a > b) {
			return (a - b);
		}
		// 数値が同じ
		else {
			return static_cast<T>(0);
		}
	}

	/* スワップ関数 */
	template <class T>
	static constexpr inline void Swap(T* a, T* b) {
		const T temp = *a;
		*a = *b;
		*b = temp;
	}
	
	/* 
		クランプ関数 
		引数：	value		:	戻り値
				max			:	最大値
				min			:	最小値
	*/
	template<class T>
	static inline void Clamp(T* value, T max, T min) {
		if (max < *value) { *value = max; }
		else if (min > *value) { *value = min; }
	}

	/* ２乗の値を取得 */
	template<class T>
	static inline  T Square(T value) { return value * value; }

	/* Sin波を取得 */
	static inline float Sin(float rad) { return sinf(rad); }

	/* 数値の桁数を取得 */
	static inline int GetDigit(int num) {
		return static_cast<int>(std::to_string(num).length()) - (num < 0 ? 1 : 0);
	}

	/*
		決められた範囲でのSin波を取得
		引数：	min		:	最小値
				max		:	最大値
				rad		:	角度
	*/
	static inline float DefinedRangeSin(float min, float max, float rad) {
		const float mult = (max - min) / 2.f;
		return (Sin(rad) + 1.f) * mult + min;
	}

	/* 逆Sin波を取得 */
	static inline float Asin(float rad) { return asinf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* 双曲線Sin波を取得 */
	static inline float Sinh(float rad) { return sinhf(rad); }

	/* Cos波を取得 */
	static inline float Cos(float rad) { return cosf(rad); }

	/* 逆Cos波を取得 */
	static inline float Acos(float rad) { return acosf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* 双曲線Cos波を取得 */
	static inline float Cosh(float rad) { return coshf(rad); }

	/* Tan波を取得 */
	static inline float Tan(float rad) { return tanf(rad); }

	/* 逆Tan波を取得 */
	static inline float Atan(float rad) { return atanf(rad); }

	/* 逆数を取得 */
	static inline float Inv(float value) { return 1.f / value; }

	/* 平方根の値を取得 */
	static inline float Sqrt(float value) { return sqrtf(value); }

	/* 平方根の逆数の値を取得 */
	static inline float InvSqrt(float value) { return 1.f / sqrtf(value); }

	/* AのB乗の値を取得(float型) */
	static inline float Pow(float a, float b) { return powf(a, b); }

	/* AのB乗の値を取得(int型) */
	static inline int Pow(int a, int b) {
		float result = powf(static_cast<float>(a), static_cast<float>(b));

		return static_cast<int>(result);
	}

	/* アークタンジェント */
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
		余弦定理から角度を取得する
		引数：	a	:	求める角度の対辺の長さ
				b	:	求める角度をはさむ辺1
				c	:	求める角度をはさむ辺2
		戻り値：角度
	*/
	static inline float LawOfCosines(float a, float b, float c) {
		const float A = Square(b) + Square(c) - Square(a);
		const float B = 2.f * b * c;
		return Acos(A / B);
	}

	/* 与えられたラジアン角が +/- πの範囲外だった場合、範囲内に戻す */
	static inline float UnwindRadians(float degree) {
		while (degree > PI) {
			degree -= (PI * 2.f);
		}
		while (degree < -PI) {
			degree += (PI * 2.f);
		}

		return degree;
	}

	/* 回転値を0 ～ 2πの値にする */
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

	/* 与えられたディグリー角が+/- 180度の範囲外だった場合、範囲内に戻す */
	static inline float UnwindDegrees(float degree) {
		while (degree > 180.f) {
			degree -= 360.f;
		}
		while (degree < -180.f) {
			degree += 360.f;
		}
		return degree;
	}

	/* ディグリー角をラジアン角に変換する */
	static inline float ConvertDegreesToRadian(float degree) {
		return degree * PI * Inv(180.f);
	}
}