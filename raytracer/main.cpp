#include "GTRenderer.h"

int main() {

	SceneLoader sl;
	Scene scene = sl.loadSceneFromFile("scene.txt");
	g_pScene = &scene;
	g_pScene->switchOnLights();
	//scene.switchOnLights();
	
	Camera camera(640, 480, Vector3(0.0,  0.0, -500.0), Vector3(0.0, 0.0, 0.0), 5.0);
	Renderer* tracer = new RayTracer();
	Renderer* otracer = new OCTracer();
/*
	std::cout<<"Render: \033[31mSimpleRayCast with local lighting\033[0m"<<std::endl;
	tracer->render(&scene, &camera);
	camera.saveImageToFile("image.png");
*/
	//std::cout<<"Render: \033[31mOCRaycast\033[0m"<<std::endl;
	otracer->render(&camera);
	saveImageToFile(camera, "image.pbm");

	return 0;
}
