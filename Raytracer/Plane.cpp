#include "Plane.h"

Plane::Plane(const Vector &normal, float d, const Material &material) : normal(normal), d(d) {
	this->material = material;
}

Plane::~Plane() {
}

vector<float> Plane::intersect(const Ray &r) const {
	Vector v = transMatrix.transform(r.v);
	float b = (normal * v);
	if (b == 0) {
		return{};
	}
	float t = (normal * r.p + d) / -b;
	if (t <= 0.01f) {
		return{};
	}
	else {
		return{ t };
	}
}
