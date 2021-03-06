#include "GTRenderer.h"

SceneLoader::SceneLoader() {

}

Scene SceneLoader::loadSceneFromFile(const std::string &str_filename) {
	Scene scene;

	std::ifstream file(str_filename.c_str());
	if (!file.is_open())	{
		std::cerr << "Error: Could not find file "<<str_filename<<"."<<std::endl;
		return scene;
	}

	std::string str_line;
	while(std::getline(file, str_line, '\n')) {
		std::stringstream line(str_line);
		readLine(line, scene);
	}

	file.close();
	return scene;
}

void SceneLoader::readLine(std::stringstream &line, Scene &scene) {
	std::string entry;
	getline(line, entry, ' ');

	if(entry.empty())
		return;

	if('#' == entry[0])
		return;
	
	if(entry == "lambda") {
		double dLambda;
		line >> dLambda;

		scene.m_dLambda = dLambda;
	}
	else if(entry == "sphere") {
		Vector3 	vPosition;
		double  	dRadius;
		Material	m;
		line >> vPosition.x; line >> vPosition.y; line >> vPosition.z;
		line >> dRadius;
		line >> m.m_vColor.r; line >> m.m_vColor.g; line >> m.m_vColor.b;
		line >> m.m_dLambda;

		m.m_dLambda = (-1.0 / (scene.m_dLambda * 2.0 * dRadius)) * log(1 - m.m_dLambda);

		Sphere s(vPosition, dRadius, m);
		scene.m_vSpheres.push_back(s);
		return;
	}
	else if(entry == "pointlight") {
		Vector3 vPosition;
		Vector3 vColor;
		line >> vPosition.x; line >> vPosition.y; line >> vPosition.z;
		line >> vColor.r;		line >> vColor.g;		line >> vColor.b;

		PointLight p(vPosition, vColor);
		scene.m_vPointLights.push_back(p);
		return;
	} 
	else if(entry == "directional") {
		Vector3 vDir;
		Vector3 vColor;
		line >> vDir.x; 	line >> vDir.y; 	line >> vDir.z;
		line >> vColor.r; line >> vColor.g; line >> vColor.b;
		
		DirectionLight d(vDir, vColor);
		scene.m_vDirectionLight.push_back(d);
		return;
	}
	else if(entry == "loadFromSiff") {
		std::string str_fn;

		line >> str_fn;

		loadSpheresFromSiff(str_fn, scene);
		return;
	}
}

void SceneLoader::loadSpheresFromSiff(std::string &str_filename, Scene &scene) {
	std::ifstream file(str_filename.c_str());
	if (!file.is_open())	{
		std::cerr << "Error: Could not find siff file "<<str_filename<<"."<<std::endl;
		return;
	}

	std::string nam = "../Data/" + str_filename + "_ply";
	FILE* pFile = fopen(nam.c_str(), "w");

	fprintf(pFile, "ply\nformat ascii 1.0\nelement vertex \nproperty float x\nproperty float y\nproperty float z\nproperty uchar red\nproperty uchar green\nproperty uchar blue\nend_header\n");

	printf("Load spheres from %s\n", str_filename.c_str());
	int iNum = 0;

	std::string str_line;
	while(std::getline(file, str_line, '\n')) {
		std::stringstream line(str_line);
		std::string entry;
		getline(line, entry, ' ');
		
		if(entry == "SIFFa1.0") {
		}
		else {
			Vector3 	vPosition;
			double  	dRadius;
			Material	m;
			line >> vPosition.x; line >> vPosition.y; line >> vPosition.z;
			line >> dRadius;
			line >> m.m_vColor.r; line >> m.m_vColor.g; line >> m.m_vColor.b;
			
			m.m_dLambda = 0.05;
			m.m_dLambda = (-1.0 / (scene.m_dLambda * 2.0 * dRadius)) * log(1 - m.m_dLambda);
			
			vPosition *= 0.01;
			fprintf(pFile, "%f %f %f %d %d %d\n", vPosition.x, vPosition.y, vPosition.z, (int)m.m_vColor.r, (int)m.m_vColor.g, (int)m.m_vColor.b);
			Sphere s(vPosition, dRadius, m);
			scene.m_vSpheres.push_back(s);
			iNum++;
		}
	}

	fclose(pFile);

	printf("Loaded %d spheres from File\n", iNum);

	file.close();
}
