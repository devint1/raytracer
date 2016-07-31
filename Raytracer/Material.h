#pragma once

#include "Vector.h"

struct Material {
	Vector ambientCoeff;
	Vector diffuseCoeff;
	Vector specularCoeff;
	float specularExp = 0;
	float reflectCoeff = 0;
};
