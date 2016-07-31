#pragma once

#include "Material.h"
#include "Vector.h"

class Light {
	Vector amount;
	Vector position;
	Vector ambIntensity;
public:
	Light(const Vector &amount, const Vector &position, const Vector &ambIntensity);
	~Light();
	Vector getColor(const Vector &eye, const Vector &point, const Vector &normal, const Material &material) const;
	Vector getPosition() const;
};
