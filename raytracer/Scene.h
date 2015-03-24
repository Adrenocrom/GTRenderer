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

		void switchOnLights() {
			for(int i = 0; i < m_vPointLights.size(); ++i) 
				m_vpLightSources.push_back(&m_vPointLights[i]);
			for(int i = 0; i < m_vDirectionLight.size(); ++i)
				m_vpLightSources.push_back(&m_vDirectionLight[i]);
		}
		
		void switchOffLights() {
			m_vpLightSources.clear();
		}
};

#endif
