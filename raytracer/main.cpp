#include "GTRenderer.h"

int main() {
	Sphere s1(Vector3(-20.0, 20.0, 0.0), 10.0);
	Sphere s2(Vector3(0.0, 20.0, 0.0), 10.0);
	Sphere s3(Vector3(20.0, 20.0, 0.0), 10.0);
	Sphere s4(Vector3(-20.0, 0.0, 0.0), 10.0);
	Sphere s5(Vector3(0.0, 0.0, 0.0), 10.0);
	Sphere s6(Vector3(20.0, 0.0, 0.0), 10.0);
	Sphere s7(Vector3(-20.0, -20.0, 0.0), 10.0);
	Sphere s8(Vector3(0.0, -20.0, 0.0), 10.0);
	Sphere s9(Vector3(20.0, -20.0, 0.0), 10.0);
	PointLight light0(Vector3(0.0, 0.0, -150.0), Vector3(100.0, 100.0, 100.0));
	//LightSource test;
	Scene scene;
	scene.m_vSpheres.push_back(s1);
	scene.m_vSpheres.push_back(s2);
	scene.m_vSpheres.push_back(s3);
	scene.m_vSpheres.push_back(s4);
	scene.m_vSpheres.push_back(s5);
	scene.m_vSpheres.push_back(s6);
	scene.m_vSpheres.push_back(s7);
	scene.m_vSpheres.push_back(s8);
	scene.m_vSpheres.push_back(s9);
	scene.m_vPointLights.push_back(light0);
	Camera camera(3300, 3300, Vector3(0.0,  0.0, -50.0), Vector3(0.0, 0.0, 1.0));
	Renderer* tracer = new RayTracer();

	tracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");

	return 0;
}
