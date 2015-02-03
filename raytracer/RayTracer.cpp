#include "GTRenderer.h"

RayTracer::RayTracer() {
}

void RayTracer::render(Scene* pScene, Camera* pCamera) const {
	Vector3 vCamPos = pCamera->m_vPosition;
	vCamPos 			-= Vector3((double)pCamera->m_iWidth / 2.0,
									  (double)pCamera->m_iHeight / 2.0,
									  0.0);
	std::vector<PointLight>* pLights = &pScene->m_vPointLights;

	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			pCamera->m_ppvSensor[x][y] = Vector3(20, 20, 20);

			// Berechnung der Lokalen Beleuchtung
			for(int i = 0; i < pScene->m_vSpheres.size(); ++i) {
				Vector3 vOrigin = vCamPos + Vector3(x, y, 0);
				Ray ray(vOrigin, pCamera->m_vDirection);

				double t = pScene->m_vSpheres[i].intersect2(ray).first;
				if(t < 0)	
					pCamera->m_ppvSensor[x][y] = Vector3(20, 20, 20);
				else {
					IntersectionInfo info(ray, t);
					Vector3 pos	   = (vOrigin + t * pCamera->m_vDirection);
					Vector3 normal = Vector3Normalize((pos - pScene->m_vSpheres[i].m_vPosition) + pos);
					Vector3 lDir	= Vector3Normalize(pos - pScene->m_vPointLights[0].m_vPosition);
					info.setNormal(normal);
					
					double fCosDiff	= Vector3Dot(normal, lDir);

					Vector3 vReflect 	= Vector3Normalize(((2 * Vector3Dot(lDir, normal)) * normal) + lDir);

					double fCosSpec  	= Vector3Dot(ray.m_vDirection, vReflect);
					std::cout<<(acos(fCosSpec))<<std::endl;
					double fN = 50;
					double fK = (0.5 * fCosDiff) + (0.5 * ((fN + 2)/(2*FM_PI)) * pow(fCosSpec, 2));

					//std::cout<<fK<<std::endl;
					
					pCamera->m_ppvSensor[x][y] = pScene->m_vPointLights[0].m_vTotalPower * fK;
					
					if(pCamera->m_ppvSensor[x][y].r < 0) pCamera->m_ppvSensor[x][y].r = 0;
					if(pCamera->m_ppvSensor[x][y].g < 0) pCamera->m_ppvSensor[x][y].g = 0;
					if(pCamera->m_ppvSensor[x][y].b < 0) pCamera->m_ppvSensor[x][y].b = 0;
					if(pCamera->m_ppvSensor[x][y].r > 255) pCamera->m_ppvSensor[x][y].r = 255;
					if(pCamera->m_ppvSensor[x][y].g > 255) pCamera->m_ppvSensor[x][y].g = 255;
					if(pCamera->m_ppvSensor[x][y].b > 255) pCamera->m_ppvSensor[x][y].b = 255;
				}
					
			}
		}
	}

}
