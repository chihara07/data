#include "Vector3D.h"

/*
	�x�N�g���̉��Z
*/
Vector3D MyLib::Vector3D::operator+(const Vector3D& v) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���x�N�g����X,Y,Z���ꂼ����Z����
	result._X += v._X;
	result._Y += v._Y;
	result._Z += v._Z;
	
	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	�x�N�g���̉��Z(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator+=(const Vector3D& v)
{
	// ���g�̃x�N�g���Ɉ����̃x�N�g�������Z����
	*this = *this + v;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	���͂��ꂽ���l���e�v�f���Ƃɉ��Z����
*/
Vector3D MyLib::Vector3D::operator+(float value) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���l��X,Y,Z���ꂼ����Z����
	result._X += value;
	result._Y += value;
	result._Z += value;
	
	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	���͂��ꂽ���l���e�v�f���Ƃɉ��Z����(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator+=(float value)
{
	// ���g�̃x�N�g���Ɉ����̒l�����Z����
	*this = *this + value;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	�x�N�g���̌��Z
	(Vector3D�^�������ɂƂ�-���Z�q�̃I�[�o�[���[�h)
*/
Vector3D MyLib::Vector3D::operator-(const Vector3D& v) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���x�N�g����X,Y,Z���ꂼ�ꌸ�Z����
	result._X -= v._X;
	result._Y -= v._Y;
	result._Z -= v._Z;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	�x�N�g���̌��Z(�R�s�[)
	(Vector3D�^�������ɂƂ�-=���Z�q�̃I�[�o�[���[�h)
*/
Vector3D MyLib::Vector3D::operator-=(const Vector3D& v)
{
	// ���g�̃x�N�g���Ɉ����̃x�N�g�������Z����
	*this = *this - v;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	���͂��ꂽ���l���e�v�f���ƂɌ��Z����
	(float�^�����ɂƂ�-���Z�q�̃I�[�o�[���[�h)
*/
Vector3D MyLib::Vector3D::operator-(float value) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���l��X,Y,Z���ꂼ�ꌸ�Z����
	result._X -= value;
	result._Y -= value;
	result._Z -= value;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	���͂��ꂽ���l���e�v�f���ƂɌ��Z����(�R�s�[)
	(float�^�����ɂƂ�-=���Z�q�̃I�[�o�[���[�h)
*/
Vector3D MyLib::Vector3D::operator-=(float value)
{
	// ���g�̃x�N�g���Ɉ����̒l�����Z����
	*this = *this - value;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	�x�N�g���̃X�P�[���{
*/
Vector3D MyLib::Vector3D::operator*(const Vector3D& v) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���x�N�g����X,Y,Z���ꂼ��X�P�[���{����
	result._X *= v._X;
	result._Y *= v._Y;
	result._Z *= v._Z;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	�x�N�g���̃X�P�[���{(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator*=(const Vector3D& v)
{
	// ���g�̃x�N�g���Ɉ����̃x�N�g�����X�P�[���{����
	*this = *this * v;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	���͂��ꂽ���l���e�v�f���ƂɃX�P�[���{����
*/
Vector3D MyLib::Vector3D::operator*(float value) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���l��X,Y,Z���ꂼ��X�P�[���{����
	result._X *= value;
	result._Y *= value;
	result._Z *= value;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	���͂��ꂽ���l���e�v�f���ƂɃX�P�[���{����(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator*=(float value)
{
	// ���g�̃x�N�g���Ɉ����̒l���X�P�[���{����
	*this = *this * value;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	�x�N�g���̏��Z
*/
Vector3D MyLib::Vector3D::operator/(const Vector3D& v) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���x�N�g����X,Y,Z���ꂼ�ꏜ�Z����
	result._X /= v._X;
	result._Y /= v._Y;
	result._Z /= v._Z;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	�x�N�g���̏��Z(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator/=(const Vector3D& v)
{
	// ���g�̃x�N�g���Ɉ����̃x�N�g�������Z����
	*this = *this / v;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	���͂��ꂽ���l���e�v�f���Ƃɏ��Z����
*/
Vector3D MyLib::Vector3D::operator/(float value) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = *this;

	// �����ɓ����Ă���l��X,Y,Z���ꂼ�ꏜ�Z����
	result._X /= value;
	result._Y /= value;
	result._Z /= value;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	���͂��ꂽ���l���e�v�f���Ƃɏ��Z����(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator/=(float value)
{
	// ���g�̃x�N�g���Ɉ����̒l�����Z����
	*this = *this / value;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	�x�N�g���̊O��
*/
Vector3D MyLib::Vector3D::operator^(const Vector3D& v) const
{
	// ���g�̃x�N�g�����R�s�[
	Vector3D result = ZeroVec();

	// �O��
	result._X = this->_Y * v._Z - this->_Z * v._Y;
	result._Y = this->_Z * v._X - this->_X * v._Z;
	result._Z = this->_X * v._Y - this->_Y * v._X;

	// ���Z���ʂ�Ԃ�
	return result;
}

/*
	�x�N�g���̊O��(�R�s�[)
*/
Vector3D MyLib::Vector3D::operator^=(const Vector3D& v)
{
	// ���g�̃x�N�g���ƈ����̃x�N�g�����O�ς���
	*this = *this ^ v;

	// ���g�̃x�N�g����Ԃ�
	return *this;
}

/*
	�x�N�g���̓���
*/
float MyLib::Vector3D::operator|(const Vector3D& v) const
{
	// ���Z����
	float result = 0.f;

	// ���g�̃x�N�g�����R�s�[
	const Vector3D copy = *this;

	// X,Y,Z���ꂼ�����
	result += copy._X * v._X;
	result += copy._Y * v._Y;
	result += copy._Z * v._Z;

	// ���Z���ʂ�Ԃ�
	return result;
}
