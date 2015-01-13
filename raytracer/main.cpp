#include "GTRenderer.h"

int main() {
	Sphere first(Vector3(0.0f, 0.0f, 30.0f), 100.0f);
	//LightSource test;
	Scene scene;
	scene.m_vSpheres.push_back(first);
	Camera camera(640, 480, Vector3(0.0f, 0.0f, -2.0f), Vector3(0.0f, 0.0f, 1.0f));
	Renderer* tracer = new RayTracer();

	tracer->render(&scene, &camera);

	camera.saveImageToFile("image.png");		

	return 0;
}
