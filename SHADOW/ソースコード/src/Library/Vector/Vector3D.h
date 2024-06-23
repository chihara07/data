#pragma once

#include "Vector2D.h"

namespace MyLib {
	// 3Dベクトル定義(float型)
	class Vector3D {
	public: // メンバ変数
		float _X, _Y, _Z;

	public: // コンストラクタ

		explicit constexpr Vector3D() noexcept : _X(0), _Y(0), _Z(0) {}
		explicit constexpr Vector3D(float xyz) noexcept : _X(xyz), _Y(xyz), _Z(xyz) {}
		explicit constexpr Vector3D(float x, float y, float z) noexcept : _X(x), _Y(y), _Z(z) {}
		constexpr Vector3D(const Vector3D& v) noexcept : _X(v._X), _Y(v._Y), _Z(v._Z) {}
		constexpr Vector3D(const VECTOR& v) noexcept : _X(v.x), _Y(v.y), _Z(v.z) {}

	public: // スタティック関数

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

		// 任意のベクトル取得
		inline static Vector3D VGet(float X, float Y, float Z) { return Vector3D(X, Y, Z); }
		inline static Vector3D VGet(float XYZ) { return Vector3D(XYZ); }
		inline static Vector3D VGet(const VECTOR& V) { return Vector3D(V); }

	public: // 演算子のオーバーロード

		// 数値設定
		inline Vector3D operator() (float xyz) { _X = xyz; _Y = xyz; _Z = xyz; return *this; }
		inline Vector3D operator() (float x, float y, float z) { _X = x; _Y = y; _Z = z; return *this; }
		inline Vector3D operator() (const Vector3D& v) { _X = v._X; _Y = v._Y; _Z = v._Z; return *this; }
		inline Vector3D operator() (const VECTOR& v) { _X = v.x; _Y = v.y; _Z = v.z; return *this; }

		/*
			ベクトルを加算
			引数：	V	:	加算するベクトル
			戻り値：加算結果
		*/
		Vector3D operator+(const Vector3D& v) const;
		/*
			ベクトルを加算(コピー)
			引数：	V	:	加算するベクトル
			戻り値：加算したベクトルのコピー
		*/
		Vector3D operator+=(const Vector3D& v);
		/*
			入力された数値を各要素ごとに加算する
			引数：	Value	:	加算する数値
			戻り値：加算したベクトル
		*/
		Vector3D operator+(float value) const;
		/*
			入力された数値を各要素ごとに加算する(コピー)
			引数：	Value	:	加算する数値
			戻り値：加算したベクトルのコピー
		*/
		Vector3D operator+=(float value);
		/*
			ベクトルを減算
			(Vector3D型を引数にとる-演算子のオーバーロード)
			引数：	V	:	減算するベクトル(Vector3D型)
			戻り値：減算結果
		*/
		Vector3D operator-(const Vector3D& v) const;
		/*
			ベクトルを減算(コピー)
			(Vector3D型を引数にとる-=演算子のオーバーロード)
			引数：	V	:	減算するベクトル(Vector3D型)
			戻り値：減算したベクトルのコピー
		*/
		Vector3D operator-=(const Vector3D& v);
		/*
			入力された数値を各要素ごとに減算する
			(float型引数にとる-演算子のオーバーロード)
			引数：	Value	:	減算する数値(float)
			戻り値：減算したベクトル
		*/
		Vector3D operator-(float value) const;
		/*
			入力された数値を各要素ごとに減算する(コピー)
			(float型引数にとる-=演算子のオーバーロード)
			引数：	Value	:	減算する数値(float型)
			戻り値：減算したベクトルのコピー
		*/
		Vector3D operator-=(float value);
		/*
			ベクトルをスケール倍
			引数：	V	:	スケール倍するベクトル
			戻り値：スケール倍結果
		*/
		Vector3D operator*(const Vector3D& v) const;
		/*
			ベクトルをスケール倍(コピー)
			引数：	V	:	スケール倍するベクトル
			戻り値：スケール倍したベクトルのコピー
		*/
		Vector3D operator*=(const Vector3D& v);
		/*
			入力された数値を各要素ごとにスケール倍する
			引数：	Value	:	スケール倍する数値
			戻り値：スケール倍したベクトル
		*/
		Vector3D operator*(float value) const;
		/*
			入力された数値を各要素ごとにスケール倍する(コピー)
			引数：	Value	:	スケール倍する数値
			戻り値：スケール倍したベクトルのコピー
		*/
		Vector3D operator*=(float value);
		/*
			ベクトルを除算
			引数：	V	:	除算するベクトル
			戻り値：除算結果
		*/
		Vector3D operator/(const Vector3D& v) const;
		/*
			ベクトルを除算(コピー)
			引数：	V	:	除算するベクトル
			戻り値：除算したベクトルのコピー
		*/
		Vector3D operator/=(const Vector3D& v);
		/*
			入力された数値を各要素ごとに除算する
			引数：	Value	:	除算する数値
			戻り値：除算したベクトル
		*/
		Vector3D operator/(float value) const;
		/*
			入力された数値を各要素ごとに除算する(コピー)
			引数：	Value	:	除算する数値
			戻り値：除算したベクトルのコピー
		*/
		Vector3D operator/=(float value);
		/*
			自身と入力ベクトルとの外積
			引数：	V	:	入力ベクトル
			戻り値：外積結果
		*/
		Vector3D operator^(const Vector3D& v) const;
		/*
			自身と入力ベクトルとの外積(コピー)
			引数：	V	:	入力ベクトル
			戻り値：外積結果のコピー
		*/
		Vector3D operator^=(const Vector3D& v);
		/*
			自身と入力ベクトルとの内積
			引数：	V	:	入力ベクトル
			戻り値：内積結果
		*/
		float operator|(const Vector3D& v) const;
		/*
			ベクトルの反転
			戻り値：反転結果
		*/
		inline Vector3D operator-() const { return Vector3D(-_X, -_Y, -_Z); }
		/*
			ベクトルの代入
			引数：	V	:	代入したいベクトル(VECTOR)
			戻り値：代入結果
		*/
		inline Vector3D operator=(const VECTOR& v) { return this->operator()(v.x, v.y, v.z); }

	public: // ベクトルに必要な関数群

		/*
			ベクトルの生成
			引数：	V	:	目標とするベクトル
			戻り値：生成結果
		*/
		inline Vector3D Create(const Vector3D& v) const { return v - *this; }
		/*
			ベクトルの正規化
			戻り値：正規化されたベクトル
			※この関数を読んだ時点で自身のベクトルを正規化が完了します
		*/
		inline Vector3D Normalize() {
			// ベクトルの長さを取得
			const float size = this->Long();
			if (size != 0.f && size != 1.f) {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}

			return *this;
		}
		/*
			//ポリゴンの法線ベクトル
			戻り値：ポリゴンの法線ベクトル
		*/
		const inline Vector3D PolygonNormalize(const Vector3D& v_b, const Vector3D& v_c) {
			// ベクトルの長さを取得
			Vector3D vecAB = this->Create(v_b);
			Vector3D vecAC = this->Create(v_c);
			Vector3D vecABAC = vecAB ^ vecAC;

			vecABAC.Normalize();

			return vecABAC;
		}
		/*
			ベクトルの長さを取得
			引数：	V	:	始点ベクトル(デフォルトは原点)
			戻り値：ベクトルの長さ
		*/
		inline float Long(const Vector3D& v = Vector3D::ZeroVec()) const {
			return Sqrt((Square(_X - v._X) + Square(_Y - v._Y) + Square(_Z - v._Z)));
		}
		/*
			ベクトルの２乗の長さを取得
			引数：	V	:	視点ベクトル(デフォルトは原点)
			戻り値：ベクトルの長さ(２乗)
		*/
		inline float LongSq(const Vector3D& v = Vector3D::ZeroVec()) const {
			return Square(_X - v._X) + Square(_Y - v._Y) + Square(_Z - v._Z);
		}
		/*
			イコール関数
			引数：	V			:	比較したいベクトル
					Tolerance	:	寛容誤差
		*/
		inline bool Equals(const Vector3D& v, float tolerance = TOLERANCE) {
			return MyLib::Abs(_X - v._X) <= tolerance
				&& MyLib::Abs(_Y - v._Y) <= tolerance
				&& MyLib::Abs(_Z - v._Z) <= tolerance;
		}
		/*
			全ての要素がイコールかどうか
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool AllComponentsEqual(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X - _Y) <= tolerance
				&& MyLib::Abs(_Y - _Z) <= tolerance
				&& MyLib::Abs(_Z - _X) <= tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視する)
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool IsNearlyZero(float tolerance = TOLERANCE) {
			return MyLib::Abs(_X) <= tolerance
				&& MyLib::Abs(_Y) <= tolerance
				&& MyLib::Abs(_Z) <= tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視しない = 完全にゼロベクトル)
		*/
		const inline bool IsZero() {
			return _X == 0.f && _Y == 0.f && _Z == 0.f;
		}
		/*
			垂直関係にあるベクトルかどうか
		*/
		const inline bool IsVertical(const Vector3D& v) {
			float d = *this | v;
			return MyLib::Abs(d) < TOLERANCE;		// 誤差範囲内なら垂直と判定
		}
		/*
			平行関係にあるベクトルかどうか
		*/
		const inline bool IsParallel(const Vector3D& v) {
			float d = (*this ^ v).LongSq();
			return MyLib::Abs(d) < TOLERANCE;		// 誤差範囲内なら平行と判定
		}
		/*
			鋭角関係かどうか
		*/
		const inline bool IsSharpAngle(const Vector3D& v) {
			return (*this | v) >= 0.f;
		}
		
		/*
			自身をVector2Dに変換する(XY平面)
		*/
		inline Vector2D ToVector2DXY() const { return Vector2D(_X, _Y); }
		/*
			自身をVector2Dに変換する(XZ平面)
		*/
		inline Vector2D ToVector2DXZ() const { return Vector2D(_X, _Z); }
		/*
			自身をVector2Dに変換する(YZ平面)
		*/
		inline Vector2D ToVector2DYZ() const { return Vector2D(_Y, _Z); }

		// DXライブラリベクトル構造体へのキャスト演算子
		inline operator VECTOR() const { return {_X, _Y, _Z }; }

		// Vector2D型へのキャスト演算子
		inline operator Vector2D() const { return Vector2D(_X, _Y); }
	};

	/*
		ベクトルのスケーリング
		引数：	Scale	:	スケール倍
				V		:	スケール倍したいベクトル
		戻り値：　スケール倍されたベクトル
	*/
	inline Vector3D operator*(float scale, const Vector3D& v) {
		return v.operator*(scale);
	}
	inline Vector3D GetPolygonNormalVec(Vector3D v_a, Vector3D v_b, Vector3D v_c) {
		// ベクトルの長さを取得
		Vector3D vecAB = v_a.Create(v_b);
		Vector3D vecAC = v_a.Create(v_c);
		Vector3D vecABAC = vecAB ^ vecAC;

		return vecABAC.Normalize();
	}
	/*平面からの高さ(XY面)*/
	inline float GetTriangleHeightXY(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// 辺に沿ったベクトルABとACを計算
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// 面法線を計算
		Vector3D vecNorm = (vecAB ^ vecAC);
		vecNorm.Normalize();
		// 平面の方程式から高さ（Y座標を計算）
		float z = (-vecNorm._X * (point._X - vertex_a._X) - vecNorm._Y * (point._Y - vertex_a._Y) + vecNorm._Z * vertex_a._Z) / vecNorm._Z;

		return z;
	}

	/*平面からの高さ(XZ面)*/
	inline float GetTriangleHeightXZ(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// 辺に沿ったベクトルABとACを計算
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// 面法線を計算
		Vector3D vecNorm = (vecAB ^ vecAC);
		vecNorm.Normalize();
		// 平面の方程式から高さ（Y座標を計算）
		float y = (-vecNorm._X * (point._X - vertex_a._X) - vecNorm._Z * (point._Z - vertex_a._Z) + vecNorm._Y * vertex_a._Y) / vecNorm._Y;

		return y;
	}

	/*平面からの高さ(YZ面)*/
	inline float GetTriangleHeightYZ(Vector3D point, Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c)
	{
		// 辺に沿ったベクトルABとACを計算
		Vector3D vecAB = vertex_a;
		vecAB = vecAB.Create(vertex_b);
		Vector3D vecAC = vertex_a;
		vecAC = vecAC.Create(vertex_c);
		// 面法線を計算
		Vector3D vecNorm = vecAB ^ vecAC;
		vecNorm.Normalize();
		// 平面の方程式から高さ（Y座標を計算）
		float x = (-vecNorm._Y * (point._Y - vertex_a._Y) - vecNorm._Z * (point._Z - vertex_a._Z) + vecNorm._X * vertex_a._X) / vecNorm._X;

		return x;
	}
}

// 名前を短くするため
using MyLib::Vector3D;