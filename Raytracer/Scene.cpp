#include <algorithm>
#include <iostream>
#include "Light.h"
#include "Ray.h"
#include "Scene.h"
#include "Plane.h"

#define MAX_REFLECTION_DEPTH 5
#define SHADOWS true

using std::cout;
using std::endl;
using std::max;
using std::min;

Scene::Scene(Vector eye, Vector backgroundColor) : eye(eye), backgroundColor(backgroundColor) {
}

Scene::~Scene() {
	for (Object *obj : objects) {
		delete obj;
	}
}

void Scene::addObject(Object *obj) {
	objects.push_back(obj);
}

void Scene::addLight(const Light &light) {
	lights.push_back(light);
}

void Scene::removeAllObjects() {
	for (Object *obj : objects) {
		delete obj;
	}
	objects.clear();
}

void Scene::removeAllLights() {
	lights.clear();
}

Vector Scene::trace(const Ray &ray, float depth) const {
	Vector color(backgroundColor);
	float tNear = INFINITY;
	Object *obj = NULL;
	Vector normal, point;
	for (Object *intObj : objects) {
		for (float t : intObj->intersect(ray)) {
			if (t < tNear) {
				tNear = t;
				obj = intObj;
			}
		}
	}
	if (!obj) return color;
	point = obj->getPoint(ray, tNear);
	normal = obj->getNormal(point);
	Vector currentColor(0, 0, 0);
	if (depth < MAX_REFLECTION_DEPTH && obj->material.reflectCoeff > 0 && ray.producer != obj) {
		Ray reflectedRay;
		reflectedRay.p = point;
		reflectedRay.v = -2.0f * (ray.v * normal) * normal + ray.v;
		reflectedRay.producer = obj;
		currentColor = obj->material.reflectCoeff * trace(reflectedRay, depth + 1);
	}
	for (Light light : lights) {
		bool inShadow = false;
#if SHADOWS
		Ray shadowRay;
		shadowRay.p = point;
		shadowRay.v = light.getPosition() - shadowRay.p;
		for (Object *shadowObj : objects) {
			if (shadowObj == obj) continue;
			if (dynamic_cast<Plane*>(shadowObj) != NULL) continue;
			if (shadowObj->intersect(shadowRay).size()) {
				inShadow = true;
				break;
			}
		}
#endif
		if (!inShadow) {
			currentColor = currentColor + light.getColor(ray.p, point, normal, obj->material);
		}
	}
	color = currentColor;
	return color;
}

void Scene::render(int width, int height, void *frameBuffer) const {
	float *frameBufferPtr = (float*)frameBuffer;
	int pixelNum;
	Ray ray;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			pixelNum = (y * width + x) * 3;
			float trueX = (width - (2.0f * x)) / (float)min(width, height);
			float trueY = (height - (2.0f * y)) / (float)min(width, height);
			Vector point(trueX, trueY, 0);
			ray.p = eye;
			ray.v = point - ray.p;
			ray.producer = NULL;
			Vector color = trace(ray, 0);
			frameBufferPtr[pixelNum + 0] = color.x;
			frameBufferPtr[pixelNum + 1] = color.y;
			frameBufferPtr[pixelNum + 2] = color.z;
		}
	}
}
