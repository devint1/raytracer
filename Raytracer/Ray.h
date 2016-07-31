#pragma once

#include "Vector.h"

struct Object;

struct Ray {
	Vector v;
	Vector p;
	Object *producer;
};
