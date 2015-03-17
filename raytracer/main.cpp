#include "GTRenderer.h"

int main() {
	//std::cout<<omp_get_num_procs()<<std::endl;
	
	Sphere s1(Vector3(-5.0, 5.0, 0.0), 2.0);
	Sphere s2(Vector3( 0.0, 5.0, 0.0), 2.0);
	Sphere s3(Vector3( 5.0, 5.0, 0.0), 2.0);
	Sphere s4(Vector3(-5.0, 0.0, 0.0), 2.0);
	Sphere s5(Vector3( 0.0, 0.0, 0.0), 2.0);
	Sphere s6(Vector3( 5.0, 0.0, 0.0), 2.0);
	Sphere s7(Vector3(-5.0,-5.0, 0.0), 2.0);
	Sphere s8(Vector3( 0.0,-5.0, 0.0), 2.0);
	Sphere s9(Vector3( 5.0,-5.0, 0.0), 2.0);

	PointLight 		light0(Vector3(0.0, 9.0, 0.0), Vector3(10.0, 100.0, 10.0));
	PointLight 		light1(Vector3(0.0,-9.0, 0.0), Vector3(100.0, 10.0, 10.0));
	PointLight 		light2(Vector3(-9.0, 0.0, 0.0), Vector3(100.0, 10.0, 10.0));
	DirectionLight light3(Vector3(-1.0, 0.0, 0.02), Vector3(0.0, 0.0, 40.0));
	//LightSource test;
	Scene scene;
	//scene.m_vSpheres.push_back(s1);
	scene.m_vSpheres.push_back(s2);
	//scene.m_vSpheres.push_back(s3);
	scene.m_vSpheres.push_back(s4);
	scene.m_vSpheres.push_back(s5);
	scene.m_vSpheres.push_back(s6);
	//scene.m_vSpheres.push_back(s7);
	scene.m_vSpheres.push_back(s8);
	//scene.m_vSpheres.push_back(s9);
	scene.m_vpLightSources.push_back(&light0);
	scene.m_vpLightSources.push_back(&light1);
	//scene.m_vpLightSources.push_back(&light2);
	//scene.m_vpLightSources.push_back(&light3);
	Camera camera(640, 480, Vector3(0.0,  0.0, -40.0), Vector3(0.0, 0.0, 1.0));
	Renderer* tracer = new RayTracer();
	Renderer* otracer = new OCTracer();
/*
	std::cout<<"Render: \033[31mSimpleRayCast with local lighting\033[0m"<<std::endl;
	tracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");
*/
	//std::cout<<"Render: \033[31mOCRaycast\033[0m"<<std::endl;
	otracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");

	return 0;
}
