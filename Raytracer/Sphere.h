#pragma once

#include <vector>
#include "Object.h"

using std::vector;

class Sphere : public Object {
	Vector center;
	float radius;
public:
	Sphere(const Vector &center, float radius, const Material &material);
	~Sphere();
	vector<float> intersect(const Ray &r) const;
	Vector getNormal(const Vector &point) const;
};
