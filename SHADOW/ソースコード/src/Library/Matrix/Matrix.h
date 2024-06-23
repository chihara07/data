#pragma once

#include "DxLib.h"
#include <math.h>
#include "../Vector/Vector3D.h"

constexpr int MATRIX_NUM = 4;		//行列数

namespace MyLib {
	//行列定義(float型)
	class MyMatrix {
	public:
		//メンバー行列
		float _M[MATRIX_NUM][MATRIX_NUM];
	public: // コンストラクタ

		explicit constexpr MyMatrix() : _M{ 0 } {}
		explicit constexpr MyMatrix(float m) : _M{ m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m } {}
		explicit constexpr MyMatrix(float(&m)[MATRIX_NUM][MATRIX_NUM]) : _M{ m[0][0], m[0][1], m[0][2], m[0][3],
														m[1][0], m[1][1], m[1][2], m[1][3],
														m[2][0], m[2][1], m[2][2], m[2][3],
														m[3][0], m[3][1], m[3][2], m[3][3] } {}
		explicit constexpr MyMatrix(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8,
			float m9, float m10, float m11, float m12, float m13, float m14, float m15, float m16) :
			_M{ m1, m2, m3, m4, m5, m6, m7, m8,
				m9, m10, m11, m12, m13, m14, m15, m16 } {}
		constexpr MyMatrix(const MyMatrix& m) : _M{ m._M[0][0], m._M[0][1], m._M[0][2], m._M[0][3],
												m._M[1][0], m._M[1][1], m._M[1][2], m._M[1][3],
												m._M[2][0], m._M[2][1], m._M[2][2], m._M[2][3],
												m._M[3][0], m._M[3][1], m._M[3][2], m._M[3][3] } {}
		constexpr MyMatrix(const MATRIX& m) : _M{ m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
												m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
												m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
												m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] } {}
	public: // スタティック関数

		//オールゼロ行列
		inline static constexpr MyMatrix ZeroMat() { return MyMatrix(0.f); }
		//単位ゼロ行列
		inline static constexpr MyMatrix IdentityMat() {
			return MyMatrix(1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f);
		}
		//平行移動行列取得(float型)
		inline static MyMatrix GetTranslateMat(float move_x, float move_y, float move_z)
		{
			return MyMatrix(1, 0, 0, move_x,
				0, 1, 0, move_y,
				0, 0, 1, move_z,
				0, 0, 0, 1);
		}
		//平行移動行列取得(Vector3D型)
		inline static MyMatrix GetTranslateMat(Vector3D move)
		{
			return MyMatrix(1, 0, 0, move._X,
				0, 1, 0, move._Y,
				0, 0, 1, move._Z,
				0, 0, 0, 1);
		}
		//拡縮行列取得(float型)
		inline static MyMatrix GetScaleMatrix(float scale_x, float scale_y, float scale_z)
		{
			return MyMatrix(scale_x, 0, 0, 0,
				0, scale_y, 0, 0,
				0, 0, scale_z, 0,
				0, 0, 0, 1);
		}

		//拡縮行列取得(Vector3D型)
		inline static MyMatrix GetScaleMatrix(Vector3D scale)
		{
			return MyMatrix(scale._X, 0, 0, 0,
				0, scale._Y, 0, 0,
				0, 0, scale._Z, 0,
				0, 0, 0, 1);
		}

		//X軸回転行列取得
		inline static MyMatrix GetPitchMatrix(float rad)
		{
			return MyMatrix(1, 0, 0, 0,
				0, cosf(rad), -sinf(rad), 0,
				0, sinf(rad), cosf(rad), 0,
				0, 0, 0, 1);
		}

		//Y軸回転行列取得
		inline static MyMatrix GetYawMatrix(float rad)
		{
			return MyMatrix(cosf(rad), 0, sinf(rad), 0,
				0, 1, 0, 0,
				-sinf(rad), 0, cosf(rad), 0,
				0, 0, 0, 1);
		}

		//Z軸回転行列取得
		inline static MyMatrix GetRollMatrix(float rad)
		{
			return MyMatrix(cosf(rad), -sinf(rad), 0, 0,
				sinf(rad), cosf(rad), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
	public: //演算子のオーバーロード
		// 数値設定
		inline MyMatrix operator() (float m) {
			for (int i = 0; i < MATRIX_NUM; i++) {
				for (int j = 0; j < MATRIX_NUM; j++)
				{
					_M[i][j] = m;
				}
			}; return *this;
		}
		inline MyMatrix operator() (float(&m)[MATRIX_NUM][MATRIX_NUM]) {
			for (int i = 0; i < MATRIX_NUM; i++) {
				for (int j = 0; j < MATRIX_NUM; j++)
				{
					_M[i][j] = m[i][j];
				}
			}; return *this;
		}
		inline MyMatrix operator() (float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8,
			float m9, float m10, float m11, float m12, float m13, float m14, float m15, float m16) {
			_M[0][0] = m1; _M[0][1] = m2; _M[0][2] = m3; _M[0][3] = m4;
			_M[1][0] = m5; _M[1][1] = m6; _M[1][2] = m7; _M[1][3] = m8;
			_M[2][0] = m9; _M[2][1] = m10; _M[2][2] = m11; _M[2][3] = m12;
			_M[3][0] = m13; _M[3][1] = m14; _M[3][2] = m15; _M[3][3] = m16; return *this;
		}
		inline MyMatrix operator() (const MyMatrix& m) {
			for (int i = 0; i < MATRIX_NUM; i++) {
				for (int j = 0; j < MATRIX_NUM; j++)
				{
					_M[i][j] = m._M[i][j];
				}
			}; return *this;
		}
		inline MyMatrix operator() (const MATRIX& m) {
			for (int i = 0; i < MATRIX_NUM; i++) {
				for (int j = 0; j < MATRIX_NUM; j++)
				{
					_M[i][j] = m.m[i][j];
				}
			}; return *this;
		}


		//行列を加算
		//引数：	m	:	加算する行列
		//戻り値：加算結果
		MyMatrix operator+(const MyMatrix& m) const;

		//行列を加算(コピー)
		//引数：	m : 加算する行列
		//戻り値：加算した行列のコピー
		MyMatrix operator+=(const MyMatrix& m);

		//行列を減算
		//引数：	m	:	減算する行列
		//戻り値：減算結果
		MyMatrix operator-(const MyMatrix& m) const;

		//行列を減算(コピー)
		//引数：	m : 減算する行列
		//戻り値：減算した行列のコピー
		MyMatrix operator-=(const MyMatrix& m);

		//行列を掛算
		//引数：	m	:	掛算する行列
		//戻り値：掛算結果
		MyMatrix operator*(const MyMatrix& m) const;

		//行列を掛算(コピー)
		//引数：	m : 掛算する行列
		//戻り値：掛算した行列のコピー
		MyMatrix operator*=(const MyMatrix& m);

		//行列をスカラー倍
		//引数：	Value	:	スカラー倍する数値
		//戻り値：スカラー倍した行列結果
		MyMatrix operator*(float value) const;

		//行列をスカラー倍(コピー)
		//引数：	Value : スカラー倍する数値
		//戻り値：スカラー倍した行列のコピー
		MyMatrix operator*=(float value);

		//行列×ベクトル
		//引数：	m	:	掛算するベクトル
		//戻り値：掛算結果
		Vector3D operator*(const Vector3D& v) const;

		//行列の代入
		//引数：	m : 代入したい行列(MATRIX)
		//戻り値：代入結果
		inline MyMatrix operator=(const MATRIX& m) { return this->operator()(m); }

	public: //行列に必要な関数群

		//行列転置を行う
		//戻り値：行列転置結果
		//※この関数を読んだ時点で自身の行列転置が完了します
		inline MyMatrix Transpose() {
			MyMatrix mat = *this;

			for (int i = 0; i < MATRIX_NUM; i++) {
				for (int j = 0; j < MATRIX_NUM; j++) {
					this->_M[i][j] = mat._M[j][i];
				}
			}

			return *this;
		}
		// DXライブラリ行列構造体へのキャスト演算子
		inline operator MATRIX() const {
			return { _M[0][0], _M[0][1], _M[0][2], _M[0][3],
					  _M[1][0], _M[1][1], _M[1][2], _M[1][3],
					  _M[2][0], _M[2][1], _M[2][2], _M[2][3],
					  _M[3][0], _M[3][1], _M[3][2], _M[3][3] };
		}
	};
}

// 名前を短くするため
using MyLib::MyMatrix;
