#include <iostream>
#include <gl/glut.h>
#include "Cylinder.h"
#include "Plane.h"
#include "Scene.h"
#include "Sphere.h"

using std::cout;
using std::endl;

#define IMAGE_WIDTH 848
#define IMAGE_HEIGHT 480

static char currentScene = '1';
static float frameBuffer[IMAGE_HEIGHT][IMAGE_WIDTH][3];
static Scene scenes[4];

static void clearFrameBuffer() {
	for (int i = 0; i < IMAGE_HEIGHT; ++i) {
		for (int j = 0; j < IMAGE_WIDTH; ++j) {
			frameBuffer[i][j][0] = 0.0;
			frameBuffer[i][j][1] = 0.0;
			frameBuffer[i][j][2] = 0.0;
		}
	}
}

static Material *getMaterials() {
	static Material materials[6];

	// Flat turquoise
	materials[0].diffuseCoeff = Vector(0, 0.4, 0.5);
	materials[0].ambientCoeff = Vector(0, 0, 0);

	// Glossy, plasticy green
	materials[1].ambientCoeff = Vector(0, 0.3, 0);
	materials[1].diffuseCoeff = Vector(0, 0.4, 0);
	materials[1].specularCoeff = Vector(1, 1, 1);
	materials[1].specularExp = 100.0;
	materials[1].reflectCoeff = 0.3;

	// Metallic red
	materials[2].ambientCoeff = Vector(0.2, 0, 0);
	materials[2].diffuseCoeff = Vector(0.35, 0, 0);
	materials[2].specularCoeff = Vector(1, 1, 1);
	materials[2].specularExp = 10.0;
	materials[2].reflectCoeff = 0.4;

	// White matte
	materials[3].ambientCoeff = Vector(.25, .25, .25);
	materials[3].diffuseCoeff = Vector(0.5, 0.5, 0.5);

	// Semi-reflective white
	materials[4].diffuseCoeff = Vector(0.5, 0.5, 0.5);
	materials[4].reflectCoeff = 0.3;

	// Polished metal
	materials[5].specularCoeff = Vector(1, 1, 1);
	materials[5].specularExp = 250.0;
	materials[5].reflectCoeff = 1;

	return materials;
}

static void initScene1(const Material *materials) {
	scenes[0] = Scene(Vector(0, 0, 1), Vector(0, 0, 0));
	scenes[0].addLight(Light(Vector(1, 1, 1), Vector(1, -1, 1), Vector(1, 1, 1)));
	scenes[0].addLight(Light(Vector(1, 1, 1), Vector(-1, -1, 1), Vector(1, 1, 1)));
	static Matrix squishY;
	static Vector ellipsoidCenter(0.15, -0.1, 0.35);
	squishY.nScale(ellipsoidCenter, Vector(0, 1, 0), 0.5);
	static Sphere *ellipsoid = new Sphere(ellipsoidCenter, 0.2, materials[2]);
	ellipsoid->setTransMatrix(squishY);
	scenes[0].addObject(ellipsoid);
	scenes[0].addObject(new Sphere(Vector(-0.2, 0.2, -0.2), 0.4, materials[1]));
	scenes[0].addObject(new Plane(Vector(0, -6, 1), 4, materials[0]));
}

static void initScene2(const Material *materials) {
	scenes[1] = Scene(Vector(0, 0, 5), Vector(0.05, 0, 0));
	scenes[1].addLight(Light(Vector(1, 1, 1), Vector(-6, -5, 10), Vector(1, 1, 1)));
	scenes[1].addObject(new Sphere(Vector(0.25, -0.25, 0), 0.4, materials[1]));
	scenes[1].addObject(new Cylinder(Vector(-0.5, -0.5, 0), Vector(0.2, -1, 0), 0.2, materials[2]));
	scenes[1].addObject(new Plane(Vector(0.2, -1, 0), 1, materials[2]));
}

static void initScene3(const Material *materials) {
	scenes[2] = Scene(Vector(-0.25, 0, 3), Vector(0.05, 0.05, 0.05));
	scenes[2].addLight(Light(Vector(1, 1, 1), Vector(1, -1, 1), Vector(1, 1, 1)));
	scenes[2].addLight(Light(Vector(1, 1, 1), Vector(-1, -1, 1), Vector(1, 1, 1)));
	scenes[2].addObject(new Sphere(Vector(-0.45, 0.5, -0.5), 0.4, materials[1]));
	scenes[2].addObject(new Sphere(Vector(-0.45, -0.2, -0.25), .2, materials[2]));
	scenes[2].addObject(new Sphere(Vector(0.5, 0.3, -2), 1, materials[5]));
	scenes[2].addObject(new Plane(Vector(0, -6, 1), 10, materials[0]));
}

static void initScene4(const Material *materials) {
	scenes[3] = Scene(Vector(0, 1, 4), Vector(0, 0.05, 0));

	// Christmas colors!
	scenes[3].addLight(Light(Vector(1, 0, 0), Vector(-1, -1, 1), Vector(1, 1, 1)));
	scenes[3].addLight(Light(Vector(0, 1, 0), Vector(1, -1, 1), Vector(1, 1, 1)));

	// Center lights
	scenes[3].addLight(Light(Vector(1, 1, 1), Vector(0, -.75, -1), Vector(1, 1, 1)));
	scenes[3].addLight(Light(Vector(1, 1, 1), Vector(0, .75, -1), Vector(1, 1, 1)));

	// Body
	scenes[3].addObject(new Sphere(Vector(0, 0.4, 0), 0.4, materials[3]));
	scenes[3].addObject(new Sphere(Vector(0, -0.1, 0.1), 0.3, materials[3]));
	scenes[3].addObject(new Sphere(Vector(0, -0.4, 0.2), 0.2, materials[3]));

	// Nose
	scenes[3].addObject(new Sphere(Vector(0, -0.35, 0.4), 0.015, materials[5]));

	// Smile
	scenes[3].addObject(new Sphere(Vector(-0.1, -0.3, 0.4), 0.015, materials[5]));
	scenes[3].addObject(new Sphere(Vector(-0.075, -0.275, 0.4), 0.015, materials[5]));
	scenes[3].addObject(new Sphere(Vector(-0.03, -0.27, 0.4), 0.015, materials[5]));
	scenes[3].addObject(new Sphere(Vector(0.075, -0.275, 0.4), 0.015, materials[5]));
	scenes[3].addObject(new Sphere(Vector(0.03, -0.27, 0.4), 0.015, materials[5]));
	scenes[3].addObject(new Sphere(Vector(0.1, -0.3, 0.4), 0.015, materials[5]));

	// Eyes
	scenes[3].addObject(new Sphere(Vector(-0.075, -0.4, 0.4), 0.02, materials[5]));
	scenes[3].addObject(new Sphere(Vector(0.075, -0.4, 0.4), 0.02, materials[5]));

	// Buttons
	scenes[3].addObject(new Sphere(Vector(0, -0.1, 0.4125), 0.025, materials[5]));
	scenes[3].addObject(new Sphere(Vector(0, 0.3, 0.4275), 0.025, materials[5]));

	scenes[3].addObject(new Plane(Vector(0, -6, 1), 4, materials[4]));
}

static void initScenes() {
	static Material *materials = getMaterials();

	initScene1(materials);
	initScene2(materials);
	initScene3(materials);
	initScene4(materials);
}

static void display() {
	int sceneNum = atoi(&currentScene) - 1;
	if (sceneNum < 0 || sceneNum >= 4) {
		return;
	}
	cout << "Begin scene drawing..." << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	clearFrameBuffer();
	scenes[sceneNum].render(IMAGE_WIDTH, IMAGE_HEIGHT, frameBuffer);
	glDrawPixels(IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
	glFlush();
	cout << "Scene drawing complete." << endl;
}

static void keyboard(unsigned char key, int x, int y) {
	currentScene = key;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	initScenes();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Raytracer");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
