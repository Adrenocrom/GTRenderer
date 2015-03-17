#ifndef SCENE_H
#define SCENE_H

#pragma once

class LightSource;

class Scene {
	public:
		std::vector<LightSource*> 	 m_vpLightSources;
		std::vector<PointLight>	 	 m_vPointLights;
		std::vector<DirectionLight> m_vDirectionLight;
		std::vector<Sphere>		 	 m_vSpheres;

		Scene();
		~Scene();
};

#endif
