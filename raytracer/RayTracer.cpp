#include "GTRenderer.h"

RayTracer::RayTracer() {
}

void RayTracer::render(Camera* pCamera) {
/*	Vector3 vCamPos = pCamera->m_vPosition;
	std::vector<PointLight>* pLights = &pScene->m_vPointLights;
	bool bOverZero = false;

	std::uniform_real_distribution<double> unif(-20.0, 20.0);
   std::default_random_engine re;

   double fnx = 0;
   double fny = 0;
   double fnz = 0;

	int Y = 0;
	int X = 0;


	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			pCamera->m_ppvSensor[x][y] = Vector3(20, 20, 20);
			Ray ray = pCamera->getRay(x, y);
			
			// Berechnung der Lokalen Beleuchtung
			for(int i = 0; i < pScene->m_vSpheres.size(); ++i) {
				std::pair<double, double> t12 = pScene->m_vSpheres[i].intersect2(ray);
				double t = t12.first >= 0 ? t12.first : t12.second;

				if(t12.first == -1 && t12.second == -1)	
					pCamera->m_ppvSensor[x][y] += Vector3(0, 0, 0);
				else {
					fnx = unif(re);
   				fny = unif(re);
   				fnz = unif(re);

					IntersectionInfo info(ray, t);
					Vector3 pos	   = (ray.m_vOrigin + t * ray.m_vDirection);
				//	Vector3 mPos	= pos + Vector3(fnx, fny, fnz);
					Vector3 normal = Vector3Normalize((pos - pScene->m_vSpheres[i].m_vPosition));
					Vector3 lDir	= Vector3Normalize(pos - pScene->m_vPointLights[0].m_vPosition);
					info.setNormal(normal);
					
					double fCosDiff		= Vector3Dot(normal, -lDir);
					double fDoubleScalar	= 2 * Vector3Dot(lDir, normal);

					if(-fDoubleScalar < 0)
						fDoubleScalar = 0;

					Vector3 vReflect 	= Vector3Normalize((fDoubleScalar * normal) + lDir);

					double fCosSpec  	= Vector3Dot(ray.m_vDirection, vReflect);
					//std::cout<<(acos(fCosSpec))<<std::endl;
					double fN = 50 + (double)Y*200000;
					double fK = ((((double)X/3)+0.1) * fCosDiff) + ((1-((double)X/3)) * ((fN + 2)/(2*FM_PI)) * pow(fCosSpec, fN));

					//std::cout<<fK<<std::endl;
					
					pCamera->m_ppvSensor[x][y] = Vector3(50.0, 50.0, 100.0) * fK;
					
					if(pCamera->m_ppvSensor[x][y].r < 0) pCamera->m_ppvSensor[x][y].r = 0;
					if(pCamera->m_ppvSensor[x][y].g < 0) pCamera->m_ppvSensor[x][y].g = 0;
					if(pCamera->m_ppvSensor[x][y].b < 0) pCamera->m_ppvSensor[x][y].b = 0;
					if(pCamera->m_ppvSensor[x][y].r > 255) pCamera->m_ppvSensor[x][y].r = 255;
					if(pCamera->m_ppvSensor[x][y].g > 255) pCamera->m_ppvSensor[x][y].g = 255;
					if(pCamera->m_ppvSensor[x][y].b > 255) pCamera->m_ppvSensor[x][y].b = 255;
				}
				
				X = (X+1) % 3;	
			}
			Y = (Y+1) % 3;
		}
	}
*/
}
