#include "Object.h"

Vector Object::getPoint(const Ray &ray, float t) const {
	return ray.p + transMatrix.transform(ray.v) * t;
}

void Object::setTransMatrix(const Matrix &transMatrix) {
	this->transMatrix = transMatrix;
}
