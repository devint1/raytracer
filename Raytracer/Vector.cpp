#include <cmath>
#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0) {
}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {
}

Vector::~Vector() {
}

float Vector::operator*(const Vector &v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator%(const Vector &v) const {
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator+(const Vector& v) const {
	float newX = x + v.x;
	float newY = y + v.y;
	float newZ = z + v.z;
	return Vector(newX, newY, newZ);
}

Vector Vector::operator-(const Vector& v) const {
	float newX = x - v.x;
	float newY = y - v.y;
	float newZ = z - v.z;
	return Vector(newX, newY, newZ);
}

float Vector::magnitude() const {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector Vector::normalize() const {
	float a = magnitude();
	float newX = x / a;
	float newY = y / a;
	float newZ = z / a;
	return Vector(newX, newY, newZ);
}

float distance(const Vector &v1, const Vector &v2) {
	float xd = v2.x - v1.x;
	float yd = v2.y - v1.y;
	float zd = v2.z - v1.z;
	return sqrt(xd * xd + yd * yd + zd * zd);
}

Vector operator+(const Vector &v, const float &f) {
	float newX = v.x + f;
	float newY = v.y + f;
	float newZ = v.z + f;
	return Vector(newX, newY, newZ);
}

Vector operator+(const float &f, const Vector &v) {
	float newX = f + v.x;
	float newY = f + v.y;
	float newZ = f + v.z;
	return Vector(newX, newY, newZ);
}

Vector operator-(const Vector &v, const float &f) {
	float newX = v.x - f;
	float newY = v.y - f;
	float newZ = v.z - f;
	return Vector(newX, newY, newZ);
}

Vector operator-(const float &f, const Vector &v) {
	float newX = f - v.x;
	float newY = f - v.y;
	float newZ = f - v.z;
	return Vector(newX, newY, newZ);
}

Vector operator*(const float& f, const Vector& v) {
	float newX = f * v.x;
	float newY = f * v.y;
	float newZ = f * v.z;
	return Vector(newX, newY, newZ);
}

Vector operator*(const Vector &v, const float &f) {
	float newX = v.x * f;
	float newY = v.y * f;
	float newZ = v.z * f;
	return Vector(newX, newY, newZ);
}

Vector operator/(const Vector &v, const float &f) {
	float newX = v.x / f;
	float newY = v.y / f;
	float newZ = v.z / f;
	return Vector(newX, newY, newZ);
}
