#pragma once

#include <vector>
#include "Material.h"
#include "Matrix.h"
#include "Ray.h"

using std::vector;

struct Object {
	Material material;
	Matrix transMatrix;
	virtual vector<float> intersect(const Ray &r) const = 0;
	virtual Vector getNormal(const Vector &point) const = 0;
	Vector getPoint(const Ray &ray, float t) const;
	void setTransMatrix(const Matrix &transMatrix);
};
