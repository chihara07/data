#pragma once

#include "DxLib.h"
#include "../Math/Math.h"

namespace MyLib {
	// 2Dベクトル定義(float型)
	class Vector2D {
	public:
		// スタティック関数
		// 変数宣言時の初期化関数
		inline static Vector2D VGet(float x, float y) { return Vector2D(x, y); }
		inline static Vector2D VGet(float xy) { return Vector2D(xy, xy); }
		inline static Vector2D VGet(const VECTOR& v) { return Vector2D(v.x, v.y); }

		// ゼロベクトル
		inline static Vector2D ZeroVec() { return Vector2D(0.f, 0.f); }

		/*
			全ての要素を足し合わせる
			引数： vec 足し合わせたいベクトル
			戻り値： 結果
		*/
		inline static float AllElementVec2DAdd(const Vector2D& v) { return (v._X + v._Y); }

	public:
		// コンストラクタ
		constexpr Vector2D() noexcept :_X(0.f), _Y(0.f) {}
		explicit constexpr Vector2D(float xy) noexcept : _X(xy), _Y(xy) {}
		constexpr Vector2D(float x, float y) noexcept : _X(x), _Y(y) {}
		constexpr Vector2D(const Vector2D& v) noexcept : _X(v._X), _Y(v._Y) {}
		constexpr Vector2D(const VECTOR& v) noexcept : _X(v.x), _Y(v.y) {}

	public:
		// オペレーターのオーバーロード宣言
		// 数値設定
		inline Vector2D operator()(float xy) { _X = xy; _Y = xy; return *this; }
		inline Vector2D operator()(float x, float y) { _X = x; _Y = y; return *this; }
		inline Vector2D operator()(const Vector2D& v) { _X = v._X; _Y = v._Y; return *this; }

		/*
			ベクトルの加算
			引数：	V	:	加算するベクトル
			戻り値：加算結果
		*/
		inline Vector2D operator+(const Vector2D& v) const { return Vector2D(_X + v._X, _Y + v._Y); }
		/*
			ベクトルの加算コピー
			引数：	V	:	加算するベクトル
			戻り値：加算したベクトルのコピー
		*/
		inline Vector2D operator+=(const Vector2D& v) { return *this = *this + v; }
		/*
			ベクトルの加算(入力された数値を各要素それぞれ加算する)
			引数：	value	:	加算する数値
			戻り値：加算結果
		*/
		inline Vector2D operator+(float value) const { return Vector2D(_X + value, _Y + value); }
		/*
			ベクトルの加算コピー(入力された数値を各要素それぞれ加算する)
			引数：	value	:	加算する数値
			戻り値：加算したベクトルのコピー
		*/
		inline Vector2D operator+=(float value) { return *this = *this + value; }
		/*
			ベクトルの減算
			引数：	V	:	減算するベクトル
			戻り値：減算結果
		*/
		inline Vector2D operator-(const Vector2D& v) const { return Vector2D(_X - v._X, _Y - v._Y); }
		/*
			ベクトルの減算コピー
			引数：	V	:	減算するベクトル
			戻り値：減算したベクトルのコピー
		*/
		inline Vector2D operator-=(const Vector2D& v) { return Vector2D(_X - v._X, _Y - v._Y); }
		/*
			ベクトルの減算(入力された数値を各要素それぞれ減算する)
			引数：	value	:	減算する数値
			戻り値：減算結果
		*/
		inline Vector2D operator-(float value) const { return Vector2D(_X - value, _Y - value); }
		/*
			ベクトルの減算コピー(入力された数値を各要素それぞれ減算する)
			引数：	value	:	減算する数値
			戻り値：減算したベクトルのコピー
		*/
		inline Vector2D operator-=(float value) { return *this = *this - value; }
		/*
			ベクトルのスケール倍
			引数：	V	:	スケール倍するベクトル
			戻り値：スケール倍した結果
		*/
		inline Vector2D operator*(const Vector2D& v) const { return this->Scale(v); }
		/*
			ベクトルのスケール倍(入力された数値を各要素それぞれスケール倍する)
			引数：	value	:	スケール倍する数値
			戻り値：除算結果
		*/
		inline Vector2D operator*(float value) const { return this->Scale(value); }
		/*
			ベクトルのスケール倍コピー
			引数：	V	:	スケール倍するベクトル
			戻り値：スケール倍したベクトルのコピー
		*/
		inline Vector2D operator*=(const Vector2D& v) { return *this = *this * v; }
		/*
			ベクトルのスケール倍コピー(入力された数値を各要素それぞれスケール倍する)
			引数：	value	:	スケール倍する数値
			戻り値：スケール倍したベクトルのコピー
		*/
		inline Vector2D operator*=(float value) { return *this = *this * value; }
		/*
			ベクトルの除算(入力された数値を各要素それぞれ除算する)
			引数：	value	:	除算する数値
			戻り値：除算結果
		*/
		inline Vector2D operator/(float value) { return Vector2D(_X / value, _Y / value); }
		/*
			ベクトルの除算
			引数：	V	:	除算するベクトル
			戻り値：除算結果
		*/
		inline Vector2D operator/(const Vector2D& v) { return Vector2D(_X / v._X, _Y / v._Y); }
		/*
			ベクトルの除算コピー(入力された数値を各要素それぞれ除算する)
			引数：	value	:	除算する数値
			戻り値：除算したベクトルのコピー
		*/
		inline Vector2D operator/=(float value) { return *this = *this / value; }
		/*
			ベクトルの除算コピー
			引数：	V	:	除算するベクトル
			戻り値：除算したベクトルのコピー
		*/
		inline Vector2D operator/=(const Vector2D& v) { return *this = *this / v; }
		/*
			自身と入力ベクトルとの外積
			引数：	V	:	入力ベクトル
			戻り値：外積結果
		*/
		inline float operator^(const Vector2D& v) { return this->Cross(v); }
		/*
			自身と入力ベクトルとの内積
			引数：	V	:	入力ベクトル
			戻り値：内積結果
		*/
		inline float operator|(const Vector2D& v) { return this->Dot(v); }

		/*
			ベクトルの反転
			戻り値：反転したベクトル
		*/
		inline Vector2D operator-() const { return Vector2D(-_X, -_Y); }
		/*
			ベクトルの代入
			戻り値：代入結果
		*/
		inline Vector2D operator=(const VECTOR& v) { _X = v.x; _Y = v.y; return *this; }

		// ベクトルの要素が同一か
		inline bool operator==(const Vector2D& v) const { return (_X == v._X && _Y == v._Y); }
		inline bool operator!=(const Vector2D& v) const { return !(*this == v); }

		// 比較演算
		inline bool operator>=(const Vector2D& v)	const { return _X >= v._X	  && _Y >= v._Y;	 }
		inline bool operator> (const Vector2D& v)	const { return _X >  v._X   && _Y >  v._Y;	 }
		inline bool operator>=(float value)			const { return _X >= value && _Y >= value; }
		inline bool operator> (float value)			const { return _X >  value && _Y >  value; }

		inline bool operator<=(const Vector2D& v)	const { return _X <= v._X	  && _Y <= v._Y;	 }
		inline bool operator< (const Vector2D& v)	const { return _X <  v._X   && _Y <  v._Y;	 }
		inline bool operator<=(float value)			const { return _X <= value && _Y <= value; }
		inline bool operator< (float value)			const { return _X <  value && _Y <  value; }

		//DXライブラリベクトル構造体へのキャスト演算子
		inline operator VECTOR() const { return VECTOR{ (float)_X, (float)_Y, 0.f }; }

	public:
		/*
			ベクトルのスケール倍(入力された数値を各要素それぞれスケール倍する)
			引数：	value	:	スケール倍する数値
			戻り値：除算結果
		*/
		inline Vector2D Scale(float value) const { return Vector2D(_X * value, _Y * value); }
		/*
			ベクトルのスケール倍
			引数：	V	:	スケール倍するベクトル
			戻り値：スケール倍した結果
		*/
		inline Vector2D Scale(const Vector2D& v) const { return Vector2D(_X * v._X, _Y * v._Y); }
		/*
			自身と入力ベクトルとの外積
			引数：	V	:	入力ベクトル
			戻り値：外積結果
		*/
		inline float Cross(const Vector2D& v) const { return _X * v._Y - _Y * v._X; }
		/*
			自身と入力ベクトルとの内積
			引数：	V	:	入力ベクトル
			戻り値：内積結果
		*/
		inline float Dot(const Vector2D& v) const { return _X * v._X + _Y * v._Y; }
		/*
			自身と入力ベクトルとの間でのベクトル生成
			引数：	V	:	入力ベクトル
			戻り値：生成結果
		*/
		inline Vector2D Create(const Vector2D& v) const { return Vector2D(v._X - _X, v._Y - _Y); }
		/*
			入力ベクトルの長さ
			引数：	V	:	始点ベクトル
			戻り値：始点ベクトルから自身への長さ
		*/
		inline float Long(const Vector2D& v = Vector2D::VGet(0.f, 0.f)) const { return sqrtf((_X - v._X) * (_X - v._X) + (_Y - v._Y) * (_Y - v._Y)); }
		/*
			入力ベクトルの長さ(2乗)
			引数：	V	:	始点ベクトル
			戻り値：始点ベクトルから自身への長さ(2乗)
		*/
		inline float LongSq(const Vector2D& v = Vector2D::VGet(0.f, 0.f)) const { return Square(_X - v._X) + Square(_Y - v._Y); }
		/*
			ベクトルの正規化
			戻り値：正規化されたベクトル
		*/
		Vector2D Normalize() {
			//インライン化していないのはsize変数の命名被りによるエラー回避の為
			float size = this->Long();
			if (size == 0.0f || size == 1.0f) { return *this; }
			else {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}
		}
		/*
			ゼロベクトルかどうか(誤差は無視する)
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool IsNearlyZero(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X) <= tolerance
				&& MyLib::Abs(_Y) <= tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視しない = 完全にゼロベクトル)
		*/
		inline bool IsZero() {
			return _X == 0.f && _Y == 0.f;
		}

	public:
		float _X, _Y;
	};

	/*
		ベクトルのスケーリング
		引数：	Scale	:	スケール倍
				V		:	スケーリングしたいベクトル
		戻り値：演算結果
	*/
	inline Vector2D operator*(float scale, const Vector2D& v) {
		return v.operator*(scale);
	}
}

using MyLib::Vector2D;
