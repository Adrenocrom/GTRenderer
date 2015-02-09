#include "GTRenderer.h"

RayTracer::RayTracer() {
}

void RayTracer::render(Scene* pScene, Camera* pCamera) const {
	Vector3 vCamPos = pCamera->m_vPosition;
	std::vector<PointLight>* pLights = &pScene->m_vPointLights;
	bool bOverZero = false;

	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			pCamera->m_ppvSensor[x][y] = Vector3(20, 20, 20);

			// Berechnung der Lokalen Beleuchtung
			for(int i = 0; i < pScene->m_vSpheres.size(); ++i) {
				Vector3 vOrigin = vCamPos + Vector3(x, y, 0);
				Ray ray(vOrigin, pCamera->m_vDirection);

				std::pair<double, double> t12 = pScene->m_vSpheres[i].intersect2(ray);
				double t = t12.first >= 0 ? t12.first : t12.second;

				if(t12.first == -1 && t12.second == -1)	
					pCamera->m_ppvSensor[x][y] += Vector3(0, 0, 0);
				else {
					IntersectionInfo info(ray, t);
					Vector3 pos	   = (vOrigin + t * pCamera->m_vDirection);
					Vector3 normal = Vector3Normalize((pos - pScene->m_vSpheres[i].m_vPosition));
					Vector3 lDir	= Vector3Normalize(pos - pScene->m_vPointLights[0].m_vPosition);
					info.setNormal(normal);
					
					double fCosDiff		= Vector3Dot(normal, -lDir);
					double fDoubleScalar	= 2 * Vector3Dot(-lDir, normal);

					if(fDoubleScalar < 0)
						fDoubleScalar = 0;

					Vector3 vReflect 	= Vector3Normalize((fDoubleScalar * normal) + lDir);

					double fCosSpec  	= Vector3Dot(ray.m_vDirection, vReflect);
					//std::cout<<(acos(fCosSpec))<<std::endl;
					double fN = 50;
					double fK = (0.5 * fCosDiff) + (0.5 * ((fN + 2)/(2*FM_PI)) * pow(fCosSpec, fN));

					//std::cout<<fK<<std::endl;
					
					pCamera->m_ppvSensor[x][y] += Vector3(50.0, 50.0, 100.0) * fK;
					
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
