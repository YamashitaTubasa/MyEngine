#pragma once

#include <cmath>

class Vector4
{
public:
	float x; // x����
	float y; // y����
	float z; // z����
	float w; // w����

public: // �R���X�g���N�^
	Vector4();
	Vector4(float x, float y, float z, float w);

public: // �����o�֐�
	float Length() const;                 // �m����(����)�����߂�
	Vector4& Normalize();                 // ���K������
	float Dot(const Vector4& v)const;     // ���ς����߂�
	Vector4 Cross(const Vector4& v)const; // �O�ς����߂�

	// �P�����Z�q�̃I�[�o�[���[�h
	Vector4 operator+() const;
	Vector4 operator-() const;

	// ������Z�q�̃I�[�o�[���[�h
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);
};
// 2�����Z�q�I�[�o�[���[�h
const Vector4 operator+(const Vector4& v1, const Vector4& v2);
const Vector4 operator-(const Vector4& v1, const Vector4& v2);
const Vector4 operator*(const Vector4& v, float s);
const Vector4 operator*(float s, const Vector4& v);
const Vector4 operator/(const Vector4& v, float s);