#pragma once

#include <vector>
#include "Object.h"

using std::vector;

class Plane : public Object {
	Vector normal;
	float d;
public:
	Plane(const Vector &normal, float d, const Material &material);
	~Plane();
	vector<float> intersect(const Ray &r) const;
	Vector getNormal(const Vector &point) const { return normal.normalize(); };
};

