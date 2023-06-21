// ================
// Quaternion.cpp
// ================
#include "Quaternion.h"
#include<cmath>

Quaternion::Quaternion()
	:x(0), y(0), z(0), w(1)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{
}

Quaternion Quaternion::Multiply(Quaternion q)
{
	Quaternion temp;

	temp.w = ((w * q.w) - (x * q.x) - (q.y * y) - (z * q.z));
	temp.x = ((y * q.z) - (z * q.y) + (q.w * x) + (w * q.x));
	temp.y = ((z * q.x) - (x * q.z) + (q.w * y) + (w * q.y));
	temp.z = ((x * q.y) - (y * q.x) + (q.w * z) + (w * q.z));

	return temp;
}

Quaternion Quaternion::IdentityQuaternion()
{
	Quaternion temp(0, 0, 0, 1);

	return temp;
}

Quaternion Quaternion::Conjugate()
{
	Quaternion temp;

	temp.x = -x;
	temp.y = -y;
	temp.z = -z;
	temp.w = w;

	return temp;
}

float Quaternion::Norm() const
{
	float temp = sqrt(x * x + y * y + z * z + w * w);

	return temp;
}

Quaternion Quaternion::Normalize()
{
	Quaternion temp = *this;
	float len = Norm();

	if (len != 0)
	{
		temp.x /= len;
		temp.y /= len;
		temp.z /= len;
		temp.w /= len;

		return temp;
	}
	return temp;
}

Quaternion Quaternion::Inverse()
{
	Quaternion temp = this->Conjugate() / (Norm() * Norm());

	return temp;
}

Vector3 Quaternion::RotateVector(const Vector3& v)
{
	Quaternion temp;
	Quaternion qrVec;
	Quaternion qrCon = Conjugate();

	qrVec.w = 0;
	qrVec.x = v.x;
	qrVec.y = v.y;
	qrVec.z = v.z;

	temp = Multiply(qrVec);
	temp = temp.Multiply(qrCon);

	return { temp.x,temp.y,temp.z };
}


Matrix4 Quaternion::MakeRotateMatrix()
{
	Matrix4 temp = Identity();

	temp.m[0][0] = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;
	temp.m[0][1] = 2 * (this->x * this->y + this->w * this->z);
	temp.m[0][2] = 2 * (this->x * this->z - this->w * this->y);
	temp.m[1][0] = 2 * (this->x * this->y - this->w * this->z);
	temp.m[1][1] = this->w * this->w - this->x * this->x + this->y * this->y - this->z * this->z;
	temp.m[1][2] = 2 * (this->y * this->z + this->w * this->x);
	temp.m[2][0] = 2 * (this->x * this->z + this->w * this->y);
	temp.m[2][1] = 2 * (this->y * this->z - this->w * this->x);
	temp.m[2][2] = this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z;

	return temp;
}

Quaternion Quaternion::operator+() const
{
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion& Quaternion::operator+=(const Quaternion& q)
{
	this->x += q.x;
	this->y += q.y;
	this->z += q.z;
	this->w += q.w;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q)
{
	this->x -= q.x;
	this->y -= q.y;
	this->z -= q.z;
	this->w -= q.w;
	return *this;
}

Quaternion& Quaternion::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}

Quaternion& Quaternion::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}

//============ Quaternion ƒNƒ‰ƒX‚É‘®‚³‚È‚¢ŠÖ”ŒQ ==============//

const Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion temp(q1);
	return temp += q2;
}

const Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion temp(q1);
	return temp -= q2;
}

const Quaternion operator*(const Quaternion& q, float s)
{
	Quaternion temp(q);
	return temp *= s;
}

const Quaternion operator*(float s, const Quaternion& q)
{
	return q * s;
}

const Quaternion operator/(const Quaternion& q, float s)
{
	Quaternion temp(q);
	return temp /= s;
}

Quaternion MakeAxisAngle(const Vector3& axis, float angle)
{
	Quaternion temp;
	Vector3 v;

	temp.w = cosf(angle / 2);
	v = axis * sinf(angle / 2);

	temp.x = v.x;
	temp.y = v.y;
	temp.z = v.z;

	temp.Normalize();

	return temp;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion temp0 = q0;
	Quaternion temp1 = q1;
	float EPSILON = 0.0005f;

	// “àÏˆ—
	float dot = (temp0.x * temp1.x) + (temp0.y * temp1.y) + (temp0.z * temp1.z) + (temp0.w * temp1.w);

	// ”½“]ˆ—
	if (dot < 0)
	{
		temp0 = -temp0; //‚à‚¤•Ğ•û‚Ì‰ñ“]‚ğ—˜—p‚·‚é
		dot = -dot; //“àÏ‚à”½“]
	}

	// ‚È‚·Šp‚ğ‹‚ß‚é
	float theta = std::acos(dot);

	//theta‚Æsin‚ğg‚Á‚Ä•âŠÔŒW”scale0,scale1‚ğ‹‚ß‚é
	float scale0, scale1;
	scale0 = sinf((1 - t) * theta) / sinf(theta);
	scale1 = sinf(t * theta) / sinf(theta);

	if (dot >= 1.0f - EPSILON)
	{
		return (1.0 - t) * temp0 + t * temp1;
	}

	// ‚»‚ê‚¼‚ê‚Ì•âŠÔŒW”‚ğ—˜—p‚µ‚Ä•âŠÔŒã‚ÌQuaternion‚ğ‹‚ß‚é
	return scale0 * temp0 + scale1 * temp1;
}

Quaternion DirectionToDirection(const Vector3& u, const Vector3& v)
{
	Quaternion temp;
	Vector3 v0 = u;
	Vector3 v1 = v;

	v0.Normalize();
	v1.Normalize();

	// ³‹K‰»‚µ‚Ä“àÏ‚ğ‹‚ß‚é
	float dot = v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;

	// u,v‚ÌŠOÏ‚ğ‚Æ‚é
	Vector3 cross = v0.Cross(v1);

	// ³‹K‰»
	Vector3 axis = cross.Normalize();

	// ’PˆÊƒxƒNƒgƒ‹‚Å“àÏ‚ğæ‚Á‚Ä‚¢‚é‚Ì‚Åacos‚ÅŠp“x‚ğ‹‚ß‚é
	float theta = std::acos(dot);

	// axis‚Ætheta‚Å”CˆÓ²‰ñ“]‚ğì‚Á‚Ä•Ô‚·
	temp = MakeAxisAngle(axis, theta);
	return temp;
}