#include <algorithm>
#include "Cylinder.h"

using std::min;

Cylinder::Cylinder(const Vector &center, const Vector &axisDir, float radius, const Material &material) : center(center), axisDir(axisDir), radius(radius) {
	this->material = material;
}

Cylinder::~Cylinder() {
}

vector<float> Cylinder::intersect(const Ray &r) const {
	Vector v = transMatrix.transform(r.v);
	float a = (v - (v * axisDir) * axisDir) * (v - (v * axisDir) * axisDir);
	float b = 2 * ((v - (v * axisDir) * axisDir) * ((r.p - center) - ((r.p - center) * axisDir) * axisDir));
	float c = ((r.p - center) - ((r.p - center) * axisDir) * axisDir) * ((r.p - center) - ((r.p - center) * axisDir) * axisDir) - pow(radius, 2);
	float desc = pow(b, 2) - 4 * a * c;
	if (desc < 0) {
		return{};
	}
	float t0 = (-b - sqrt(desc)) / (2 * a);
	float t1 = (-b + sqrt(desc)) / (2 * a);
	if (t0 <= 0.01f && t1 <= 0.01f) {
		return{};
	}
	else if (t0 <= 0.01f) {
		return{ t1 };
	}
	else if (t1 <= 0.01f) {
		return{ t0 };
	}
	else {
		return{ t0, t1 };
	}
}

Vector Cylinder::getNormal(const Vector &point) const {
	return ((point - center - ((point - center) * axisDir) * axisDir) / radius).normalize();
}
