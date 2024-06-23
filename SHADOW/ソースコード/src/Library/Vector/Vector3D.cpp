#include "Vector3D.h"

/*
	ベクトルの加算
*/
Vector3D MyLib::Vector3D::operator+(const Vector3D& v) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っているベクトルをX,Y,Zそれぞれ加算する
	result._X += v._X;
	result._Y += v._Y;
	result._Z += v._Z;
	
	// 演算結果を返す
	return result;
}

/*
	ベクトルの加算(コピー)
*/
Vector3D MyLib::Vector3D::operator+=(const Vector3D& v)
{
	// 自身のベクトルに引数のベクトルを加算する
	*this = *this + v;

	// 自身のベクトルを返す
	return *this;
}

/*
	入力された数値を各要素ごとに加算する
*/
Vector3D MyLib::Vector3D::operator+(float value) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っている値をX,Y,Zそれぞれ加算する
	result._X += value;
	result._Y += value;
	result._Z += value;
	
	// 演算結果を返す
	return result;
}

/*
	入力された数値を各要素ごとに加算する(コピー)
*/
Vector3D MyLib::Vector3D::operator+=(float value)
{
	// 自身のベクトルに引数の値を加算する
	*this = *this + value;

	// 自身のベクトルを返す
	return *this;
}

/*
	ベクトルの減算
	(Vector3D型を引数にとる-演算子のオーバーロード)
*/
Vector3D MyLib::Vector3D::operator-(const Vector3D& v) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っているベクトルをX,Y,Zそれぞれ減算する
	result._X -= v._X;
	result._Y -= v._Y;
	result._Z -= v._Z;

	// 演算結果を返す
	return result;
}

/*
	ベクトルの減算(コピー)
	(Vector3D型を引数にとる-=演算子のオーバーロード)
*/
Vector3D MyLib::Vector3D::operator-=(const Vector3D& v)
{
	// 自身のベクトルに引数のベクトルを減算する
	*this = *this - v;

	// 自身のベクトルを返す
	return *this;
}

/*
	入力された数値を各要素ごとに減算する
	(float型引数にとる-演算子のオーバーロード)
*/
Vector3D MyLib::Vector3D::operator-(float value) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っている値をX,Y,Zそれぞれ減算する
	result._X -= value;
	result._Y -= value;
	result._Z -= value;

	// 演算結果を返す
	return result;
}

/*
	入力された数値を各要素ごとに減算する(コピー)
	(float型引数にとる-=演算子のオーバーロード)
*/
Vector3D MyLib::Vector3D::operator-=(float value)
{
	// 自身のベクトルに引数の値を減算する
	*this = *this - value;

	// 自身のベクトルを返す
	return *this;
}

/*
	ベクトルのスケール倍
*/
Vector3D MyLib::Vector3D::operator*(const Vector3D& v) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っているベクトルをX,Y,Zそれぞれスケール倍する
	result._X *= v._X;
	result._Y *= v._Y;
	result._Z *= v._Z;

	// 演算結果を返す
	return result;
}

/*
	ベクトルのスケール倍(コピー)
*/
Vector3D MyLib::Vector3D::operator*=(const Vector3D& v)
{
	// 自身のベクトルに引数のベクトルをスケール倍する
	*this = *this * v;

	// 自身のベクトルを返す
	return *this;
}

/*
	入力された数値を各要素ごとにスケール倍する
*/
Vector3D MyLib::Vector3D::operator*(float value) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っている値をX,Y,Zそれぞれスケール倍する
	result._X *= value;
	result._Y *= value;
	result._Z *= value;

	// 演算結果を返す
	return result;
}

/*
	入力された数値を各要素ごとにスケール倍する(コピー)
*/
Vector3D MyLib::Vector3D::operator*=(float value)
{
	// 自身のベクトルに引数の値をスケール倍する
	*this = *this * value;

	// 自身のベクトルを返す
	return *this;
}

/*
	ベクトルの除算
*/
Vector3D MyLib::Vector3D::operator/(const Vector3D& v) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っているベクトルをX,Y,Zそれぞれ除算する
	result._X /= v._X;
	result._Y /= v._Y;
	result._Z /= v._Z;

	// 演算結果を返す
	return result;
}

/*
	ベクトルの除算(コピー)
*/
Vector3D MyLib::Vector3D::operator/=(const Vector3D& v)
{
	// 自身のベクトルに引数のベクトルを除算する
	*this = *this / v;

	// 自身のベクトルを返す
	return *this;
}

/*
	入力された数値を各要素ごとに除算する
*/
Vector3D MyLib::Vector3D::operator/(float value) const
{
	// 自身のベクトルをコピー
	Vector3D result = *this;

	// 引数に入っている値をX,Y,Zそれぞれ除算する
	result._X /= value;
	result._Y /= value;
	result._Z /= value;

	// 演算結果を返す
	return result;
}

/*
	入力された数値を各要素ごとに除算する(コピー)
*/
Vector3D MyLib::Vector3D::operator/=(float value)
{
	// 自身のベクトルに引数の値を除算する
	*this = *this / value;

	// 自身のベクトルを返す
	return *this;
}

/*
	ベクトルの外積
*/
Vector3D MyLib::Vector3D::operator^(const Vector3D& v) const
{
	// 自身のベクトルをコピー
	Vector3D result = ZeroVec();

	// 外積
	result._X = this->_Y * v._Z - this->_Z * v._Y;
	result._Y = this->_Z * v._X - this->_X * v._Z;
	result._Z = this->_X * v._Y - this->_Y * v._X;

	// 演算結果を返す
	return result;
}

/*
	ベクトルの外積(コピー)
*/
Vector3D MyLib::Vector3D::operator^=(const Vector3D& v)
{
	// 自身のベクトルと引数のベクトルを外積する
	*this = *this ^ v;

	// 自身のベクトルを返す
	return *this;
}

/*
	ベクトルの内積
*/
float MyLib::Vector3D::operator|(const Vector3D& v) const
{
	// 演算結果
	float result = 0.f;

	// 自身のベクトルをコピー
	const Vector3D copy = *this;

	// X,Y,Zそれぞれ内積
	result += copy._X * v._X;
	result += copy._Y * v._Y;
	result += copy._Z * v._Z;

	// 演算結果を返す
	return result;
}
