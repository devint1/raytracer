#include <cmath>
#include "Matrix.h"

Matrix::Matrix() {
	// Initialize with identity matrix
	matInternal[0][0] = 1;
	matInternal[0][1] = 0;
	matInternal[0][2] = 0;
	matInternal[0][3] = 0;

	matInternal[1][0] = 0;
	matInternal[1][1] = 1;
	matInternal[1][2] = 0;
	matInternal[1][3] = 0;

	matInternal[2][0] = 0;
	matInternal[2][1] = 0;
	matInternal[2][2] = 1;
	matInternal[2][3] = 0;

	matInternal[3][0] = 0;
	matInternal[3][1] = 0;
	matInternal[3][2] = 0;
	matInternal[3][3] = 1;
}

Matrix::Matrix(float matrix[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matInternal[i][j] = matrix[i][j];
		}
	}
}

void Matrix::nScale(const Vector &p, const Vector &v, float alpha) {
	alpha = 1 / alpha;
	float scaleMatrixInternal[4][4] =
	{
		{ alpha * pow(v.x, 2) - pow(v.x, 2) + 1,	(alpha - 1) * v.x * v.y,				(alpha - 1) * v.x * v.z,				-(alpha - 1) * (p.x * v.x + p.y * v.y + p.z * v.z) * v.x },
		{ (alpha - 1) * v.x * v.y,					alpha * pow(v.y, 2) - pow(v.y, 2) + 1,	(alpha - 1) * v.y * v.z,				-(alpha - 1) * (p.x * v.x + p.y * v.y + p.z * v.z) * v.y },
		{ (alpha - 1) * v.z * v.z,					(alpha - 1) * v.x * v.z,				alpha * pow(v.z, 2) - pow(v.z, 2) + 1,	-(alpha - 1) * (p.x * v.x + p.y * v.y + p.z * v.z) * v.z },
		{ 0,										0,										0,										1														 }
	};
	Matrix scaleMatrix(scaleMatrixInternal);
	*this = *this * scaleMatrix;
}

Vector Matrix::transform(const Vector &v) const {
	Vector result;
	result.x = matInternal[0][0] * v.x + matInternal[0][1] * v.y + matInternal[0][2] * v.z + matInternal[0][3];
	result.y = matInternal[1][0] * v.x + matInternal[1][1] * v.y + matInternal[1][2] * v.z + matInternal[1][3];
	result.z = matInternal[2][0] * v.x + matInternal[2][1] * v.y + matInternal[2][2] * v.z + matInternal[2][3];
	return result;
}

Matrix Matrix::operator*(const Matrix &m) const {
	float result[4][4] = { 0 };
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3; ++k) {
				result[i][j] += matInternal[i][k] * m.matInternal[k][j];
			}
		}
	}
	return Matrix(result);
}

Matrix::~Matrix() {
}
