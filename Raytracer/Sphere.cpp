#include <algorithm>
#include <cmath>
#include "Matrix.h"
#include "Sphere.h"

using std::min;

Sphere::Sphere(const Vector &center, float radius, const Material &material) : center(center), radius(radius) {
	this->material = material;
}

Sphere::~Sphere() {
}

vector<float> Sphere::intersect(const Ray &r) const {
	Vector v = transMatrix.transform(r.v); 
	float a = v * v;
	float b = 2 * v * (r.p - center);
	float c = (r.p - center) * (r.p - center) - radius * radius;
	float desc = b * b - 4 * a * c;
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

Vector Sphere::getNormal(const Vector &point) const {
	return (point - center).normalize();
}
