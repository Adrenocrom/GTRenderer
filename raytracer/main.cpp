#include "GTRenderer.h"

int main() {

	SceneLoader sl;
	Scene scene = sl.loadSceneFromFile("scene.txt");
	scene.switchOnLights();
	
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
