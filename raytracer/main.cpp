#include "GTRenderer.h"

int main() {
	Sphere first(Vector3(0.0, 0.0, 0.0), 100.0);
	Sphere second(Vector3(0.0, 5000100.0, 0.0), 5000000.0);
	Sphere third(Vector3(0.0, 0.0, 55000.0), 50000.0);
	PointLight light0(Vector3(0.0, -150.0, -150.0), Vector3(100.0, 100.0, 100.0));
	//LightSource test;
	Scene scene;
	//scene.m_vSpheres.push_back(third);
	//scene.m_vSpheres.push_back(second);
	scene.m_vSpheres.push_back(first);
	scene.m_vPointLights.push_back(light0);
	Camera camera(640, 480, Vector3(-320.0,  -240.0, -150.0), Vector3(0.0, 0.0, 1.0));
	Renderer* tracer = new RayTracer();

	tracer->render(&scene, &camera);

	camera.saveImageToFile("image.png");		

	return 0;
}
