#ifndef SCENE_H
#define SCENE_H

#pragma once

class LightSource;

#ifdef USECUDA
	#include "CudaKernels.h"
#endif

class Scene {
	public:
		std::vector<LightSource*> 	 m_vpLightSources;
		std::vector<PointLight>	 	 m_vPointLights;
		std::vector<DirectionLight> m_vDirectionLight;
		std::vector<Primitive*>		 m_vpPrimitives;
		std::vector<Sphere>		 	 m_vSpheres;
		std::vector<Box>				 m_vBoxes;
		double							 m_dLambda;

		KDTree							 m_kdTree;

		Scene();
		~Scene();

		void switchOnLights() {
			int iSize[3];
			iSize[0] = m_vPointLights.size();
			iSize[1] = m_vDirectionLight.size();
			iSize[2] = m_vSpheres.size();

			for(int i = 0; i < iSize[0]; ++i) 
				m_vpLightSources.push_back(&m_vPointLights[i]);
			for(int i = 0; i < iSize[1]; ++i)
				m_vpLightSources.push_back(&m_vDirectionLight[i]);

			for(int i = 0; i < iSize[2]; ++i)
				m_vpPrimitives.push_back(&m_vSpheres[i]);

			m_kdTree.createTree();

			loadUpScene();			
		}
		
		void switchOffLights() {
			m_vpLightSources.clear();
			m_vpPrimitives.clear();
		}
};

#endif
