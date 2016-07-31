#include <cmath>
#include "Light.h"

Light::Light(const Vector &amount, const Vector &direction, const Vector &ambIntensity) : amount(amount), position(direction), ambIntensity(ambIntensity) {
}

Light::~Light() {
}

Vector Light::getColor(const Vector &eye, const Vector &point, const Vector &normal, const Material &material) const {
	float ambientComponent = material.ambientCoeff * ambIntensity;
	Vector reflected = -2.0f * (position * normal) * normal + position;
	float diffuseComponent, specularComponent;

	// Only want 1-sided lighting
	if (position * normal <= 0) {
		specularComponent = 0;
		diffuseComponent = 0;
	}
	else {
		diffuseComponent = normal * (position - point).normalize();
		specularComponent = pow(reflected.normalize() * (eye - point).normalize(), material.specularExp);
	}

	// No negative lighting
	if (diffuseComponent < 0) {
		diffuseComponent = 0;
	}
	if (specularComponent < 0) {
		specularComponent = 0;
	}

	float redComponent = ambientComponent * material.ambientCoeff.x + (diffuseComponent * material.diffuseCoeff.x + specularComponent * material.specularCoeff.x) * amount.x;
	float greenComponent = ambientComponent * material.ambientCoeff.y + (diffuseComponent * material.diffuseCoeff.y + specularComponent * material.specularCoeff.y) * amount.y;
	float blueComponent = ambientComponent * material.ambientCoeff.z + (diffuseComponent * material.diffuseCoeff.z + specularComponent * material.specularCoeff.z) * amount.z;
	return Vector(redComponent, greenComponent, blueComponent);
}

Vector Light::getPosition() const {
	return position;
}
