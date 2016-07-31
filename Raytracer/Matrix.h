#pragma once

#include "Vector.h"

/* 
 * A 4x4 matrix used in affine transformations.
 *
 * This can be used for any transformation classified as affine;
 * however, only functionality for non-uniform scaling is built-in.
 */
class Matrix {
	float matInternal[4][4];
public:
	Matrix();
	Matrix(float matrix[4][4]);
	void nScale(const Vector &p, const Vector &v, float alpha);
	Vector transform(const Vector &v) const;
	Matrix operator*(const Matrix &m) const;
	~Matrix();
};

