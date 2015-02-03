#include "GTRenderer.h"

int main() {
	Sphere first(Vector3(0.0, 0.0, 0.0), 100.0);
	Sphere second(Vector3(200.0, 0.0, 100.0), 50.0);
	PointLight light0(Vector3(0.0, 20000.0, 0.0), Vector3(30.0, 220.0, 0.9));
	//LightSource test;
	Scene scene;
	scene.m_vSpheres.push_back(first);
	//scene.m_vSpheres.push_back(second);
	scene.m_vPointLights.push_back(light0);
	Camera camera(640, 480, Vector3(0.0, 0.0, -2.0), Vector3(0.0, 0.0, 1.0));
	Renderer* tracer = new RayTracer();

	tracer->render(&scene, &camera);

	camera.saveImageToFile("image3.png");		

	return 0;
}
