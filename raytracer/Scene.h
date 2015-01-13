#ifndef SCENE_H
#define SCENE_H

#pragma once

class LightSource;

class Scene {
	public:
		std::vector<LightSource> m_vLightSources;
		std::vector<Sphere>		 m_vSpheres;

		Scene();
		~Scene();
};

#endif
