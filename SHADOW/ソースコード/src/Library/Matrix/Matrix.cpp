#include "Matrix.h"


//行列の加算
MyMatrix MyMatrix::operator+(const MyMatrix& m) const {
	//自身の行列をコピー
	MyMatrix result = *this;

	//引数に入っている行列を加算する
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] += m._M[i][j];
		}
	}

	//演算結果を返す
	return result;
}

//行列の加算(コピー)
MyMatrix MyMatrix::operator+=(const MyMatrix& m) {
	// 自身の行列に引数の行列を加算する
	*this = *this + m;

	// 自身の行列を返す
	return *this;
}

//行列の減算
MyMatrix MyMatrix::operator-(const MyMatrix& m) const {
	//自身の行列をコピー
	MyMatrix result = *this;

	//引数に入っている行列を減算する
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] -= m._M[i][j];
		}
	}

	//演算結果を返す
	return result;
}

//行列の減算(コピー)
MyMatrix MyMatrix::operator-=(const MyMatrix& m) {
	// 自身の行列に引数の行列を減算する
	*this = *this - m;

	// 自身の行列を返す
	return *this;
}

//行列の掛算
MyMatrix MyMatrix::operator*(const MyMatrix& m) const {
	//自身の行列をコピー
	MyMatrix OwnMat = *this;
	//結果用行列
	MyMatrix result = ZeroMat();

	//引数に入っている行列を掛算する
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] = (OwnMat._M[i][0] * m._M[0][j]) + (OwnMat._M[i][1] * m._M[1][j])
				+ (OwnMat._M[i][2] * m._M[2][j]) + (OwnMat._M[i][3] * m._M[3][j]);
		}
	}

	//演算結果を返す
	return result;
}

//行列の掛算(コピー)
MyMatrix MyMatrix::operator*=(const MyMatrix& m) {
	// 自身の行列に引数の行列を掛算する
	*this = *this * m;

	// 自身の行列を返す
	return *this;
}

//行列をスカラー倍
MyMatrix MyMatrix::operator*(float value) const {
	//自身の行列をコピー
	MyMatrix result = *this;

	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] = result._M[i][j] * value;
		}
	}

	return result;
}

//行列をスカラー倍(コピー)
MyMatrix MyMatrix::operator*=(float value) {
	// 自身の行列をスカラー倍する
	*this = *this * value;

	// 自身の行列を返す
	return *this;
}

//行列×ベクトル
Vector3D MyMatrix::operator*(const Vector3D& v) const {
	Vector3D result = Vector3D::ZeroVec();

	result._X = (this->_M[0][0] * v._X) + (this->_M[0][1] * v._Y)
		+ (this->_M[0][2] * v._Z) + (this->_M[0][3] * 1);
	result._Y = (this->_M[1][0] * v._X) + (this->_M[1][1] * v._Y)
		+ (this->_M[1][2] * v._Z) + (this->_M[1][3] * 1);
	result._Z = (this->_M[2][0] * v._X) + (this->_M[2][1] * v._Y)
		+ (this->_M[2][2] * v._Z) + (this->_M[2][3] * 1);
			
	return result;
}
