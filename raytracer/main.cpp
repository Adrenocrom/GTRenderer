#include "GTRenderer.h"

int main() {
	Sphere s1(Vector3(0.0, 0.0, 50.0), 30.0);
	Sphere s2(Vector3(0.0, 0.0, 120.0), 30.0);
	Sphere s3(Vector3(0.0, 30.0, 80.0), 30.0);
	PointLight light0(Vector3(70.0, 0.0, 10.0), Vector3(100.0, 100.0, 100.0));
	DirectionLight light1(Vector3(3.0, 3.0, 3.0), Vector3(100.0, 100.0, 100.0));
	//LightSource test;
	Scene scene;
	scene.m_vSpheres.push_back(s1);
	scene.m_vSpheres.push_back(s2);
	scene.m_vSpheres.push_back(s3);
	scene.m_vpLightSources.push_back(&light0);
	scene.m_vpLightSources.push_back(&light1);
	Camera camera(640, 480, Vector3(0.0,  0.0, -10.0), Vector3(0.0, 0.0, 1.0));
	Renderer* tracer = new RayTracer();
	Renderer* otracer = new OCTracer();
/*
	std::cout<<"Render: \033[31mSimpleRayCast with local lighting\033[0m"<<std::endl;
	tracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");
*/
	std::cout<<"Render: \033[31mOCRaycast\033[0m"<<std::endl;
	otracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");

	return 0;
}
