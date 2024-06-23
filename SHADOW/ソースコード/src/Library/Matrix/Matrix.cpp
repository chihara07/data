#include "Matrix.h"


//�s��̉��Z
MyMatrix MyMatrix::operator+(const MyMatrix& m) const {
	//���g�̍s����R�s�[
	MyMatrix result = *this;

	//�����ɓ����Ă���s������Z����
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] += m._M[i][j];
		}
	}

	//���Z���ʂ�Ԃ�
	return result;
}

//�s��̉��Z(�R�s�[)
MyMatrix MyMatrix::operator+=(const MyMatrix& m) {
	// ���g�̍s��Ɉ����̍s������Z����
	*this = *this + m;

	// ���g�̍s���Ԃ�
	return *this;
}

//�s��̌��Z
MyMatrix MyMatrix::operator-(const MyMatrix& m) const {
	//���g�̍s����R�s�[
	MyMatrix result = *this;

	//�����ɓ����Ă���s������Z����
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] -= m._M[i][j];
		}
	}

	//���Z���ʂ�Ԃ�
	return result;
}

//�s��̌��Z(�R�s�[)
MyMatrix MyMatrix::operator-=(const MyMatrix& m) {
	// ���g�̍s��Ɉ����̍s������Z����
	*this = *this - m;

	// ���g�̍s���Ԃ�
	return *this;
}

//�s��̊|�Z
MyMatrix MyMatrix::operator*(const MyMatrix& m) const {
	//���g�̍s����R�s�[
	MyMatrix OwnMat = *this;
	//���ʗp�s��
	MyMatrix result = ZeroMat();

	//�����ɓ����Ă���s����|�Z����
	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] = (OwnMat._M[i][0] * m._M[0][j]) + (OwnMat._M[i][1] * m._M[1][j])
				+ (OwnMat._M[i][2] * m._M[2][j]) + (OwnMat._M[i][3] * m._M[3][j]);
		}
	}

	//���Z���ʂ�Ԃ�
	return result;
}

//�s��̊|�Z(�R�s�[)
MyMatrix MyMatrix::operator*=(const MyMatrix& m) {
	// ���g�̍s��Ɉ����̍s����|�Z����
	*this = *this * m;

	// ���g�̍s���Ԃ�
	return *this;
}

//�s����X�J���[�{
MyMatrix MyMatrix::operator*(float value) const {
	//���g�̍s����R�s�[
	MyMatrix result = *this;

	for (int i = 0; i < MATRIX_NUM; i++) {
		for (int j = 0; j < MATRIX_NUM; j++) {
			result._M[i][j] = result._M[i][j] * value;
		}
	}

	return result;
}

//�s����X�J���[�{(�R�s�[)
MyMatrix MyMatrix::operator*=(float value) {
	// ���g�̍s����X�J���[�{����
	*this = *this * value;

	// ���g�̍s���Ԃ�
	return *this;
}

//�s��~�x�N�g��
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
