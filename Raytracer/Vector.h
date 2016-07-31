#pragma once

class Vertex;

class Vector
{
public:
	float x, y, z;
	Vector();
	Vector(float x, float y, float z);
	~Vector();
	float operator*(const Vector& v) const; // Dot product
	Vector operator%(const Vector& v) const; // Cross product
	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	float magnitude() const;
	Vector normalize() const;
};

float distance(const Vector &v1, const Vector &v2);
Vector operator+(const Vector &v, const float &f);
Vector operator+(const float &f, const Vector &v);
Vector operator-(const Vector &v, const float &f);
Vector operator-(const float &f, const Vector &v);
Vector operator*(const float &f, const Vector &v);
Vector operator*(const Vector &v, const float &f);
Vector operator/(const Vector &v, const float &f);
