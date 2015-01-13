#include "GTRenderer.h"

int main() {
	Sphere first;
	//LightSource test;
	Scene scene;
	Camera camera(640, 480, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	Renderer* tracer = new RayTracer();

	tracer->render(&scene, &camera);

	camera.saveImageToFile("image.png");		

	return 0;
}
