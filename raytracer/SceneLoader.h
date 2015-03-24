#ifndef SCENELOADER_H
#define SCENELOADER_H

#pragma once

class SceneLoader {
	public:
		SceneLoader();

		Scene loadSceneFromFile(const std::string &str_filename);
	
	private:
		void readLine(std::stringstream &line, Scene &scene);	
};

#endif
