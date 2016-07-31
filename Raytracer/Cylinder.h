#pragma once

#include <vector>
#include "Object.h"

using std::vector;

class Cylinder : public Object {
	Vector center;
	Vector axisDir;
	float radius;
public:
	Cylinder(const Vector &center, const Vector &axisDir, float radius, const Material &material);
	~Cylinder();
	vector<float> intersect(const Ray &r) const;
	Vector getNormal(const Vector &point) const;
};

