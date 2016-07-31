#pragma once

#include <vector>
#include "Light.h"
#include "Object.h"

using std::vector;

class Scene {
	vector<Object*> objects;
	vector<Light> lights;
	Vector eye;
	Vector backgroundColor;
public:
	Scene() {}
	Scene(Vector eye, Vector backgroundColor);
	~Scene();
	void addObject(Object *obj);
	void addLight(const Light &light);
	void removeAllObjects();
	void removeAllLights();
	Vector trace(const Ray &ray, float depth) const;
	void render(int width, int height, void *frameBuffer) const;
};

