#ifndef SCENE_H
#define SCENE_H

#pragma once

class LightSource;

class Scene {
	public:
		std::vector<LightSource*> 	 m_vpLightSources;
		std::vector<PointLight>	 	 m_vPointLights;
		std::vector<DirectionLight> m_vDirectionLight;
		std::vector<Primitive*>		 m_vpPrimitives;
		std::vector<Sphere>		 	 m_vSpheres;
		std::vector<Box>				 m_vBoxes;

		KDTree							 m_kdTree;

		Scene();
		~Scene();

		void switchOnLights() {
			for(int i = 0; i < m_vPointLights.size(); ++i) 
				m_vpLightSources.push_back(&m_vPointLights[i]);
			for(int i = 0; i < m_vDirectionLight.size(); ++i)
				m_vpLightSources.push_back(&m_vDirectionLight[i]);

			for(int i = 0; i < m_vSpheres.size(); ++i)
				m_vpPrimitives.push_back(&m_vSpheres[i]);

			m_kdTree.createTree();
		}
		
		void switchOffLights() {
			m_vpLightSources.clear();
			m_vpPrimitives.clear();
		}
};

#endif
