#include "GTRenderer.h"

bool g_compare_positions (const IntersectionInfo& first, const IntersectionInfo& second) {
	if(first.m_vIntersects[1] > second.m_vIntersects[2])
  		return false;
	return true;
}

OCTracer::OCTracer() {
}

void OCTracer::render(Scene* pScene, Camera* pCamera) {
	Vector3 vCamPos = pCamera->m_vPosition;
	std::vector<LightSource*>* pLights = &pScene->m_vpLightSources;
	double	dNumPixel = (double)(pCamera->m_iWidth * pCamera->m_iHeight);
	double	dNumCalcd = 0;
	double	dSamples	 = 100;
	
	#pragma omp parallel for schedule(dynamic, 1)
	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			Ray ray = pCamera->getRay(x, y);
			pCamera->m_ppvSensor[x][y] = calcColorOfRay(pScene, &ray, Vector3(20, 20, 20), -1, 0, 1);
					
			if(pCamera->m_ppvSensor[x][y].r < 0) pCamera->m_ppvSensor[x][y].r = 0;
			if(pCamera->m_ppvSensor[x][y].g < 0) pCamera->m_ppvSensor[x][y].g = 0;
			if(pCamera->m_ppvSensor[x][y].b < 0) pCamera->m_ppvSensor[x][y].b = 0;
			if(pCamera->m_ppvSensor[x][y].r > 255) pCamera->m_ppvSensor[x][y].r = 255;
			if(pCamera->m_ppvSensor[x][y].g > 255) pCamera->m_ppvSensor[x][y].g = 255;
			if(pCamera->m_ppvSensor[x][y].b > 255) pCamera->m_ppvSensor[x][y].b = 255;
				
			dNumCalcd++;
			printf("\rRender: [\033[31m%.2f %%\033[0m]", (float)((dNumCalcd / dNumPixel) * 100.0));
		}
	}
}

Vector3 OCTracer::calcColorOfRay(Scene* 	pScene, 
											Ray* 		pRay, 
											Vector3 	vLightColor,
											int		iObjectId,
											int 		iDepth, 
											int 		iMaxDepth) {
	std::list<IntersectionInfo> zBuffer;
	Vector3 result 	  = vLightColor;
	double  dNumSamples = 1000;

	int iNumLights	 = pScene->m_vpLightSources.size();
	int iNumSpheres = pScene->m_vSpheres.size();
	for(int i = 0; i < iNumSpheres; ++i) {
		IntersectionInfo info = pScene->m_vSpheres[i].getIntersectionInfo(*pRay, i);

		if(iObjectId != i)
			if(info.m_iNumIntersects != 0)
				zBuffer.push_back(info);
	}
	zBuffer.sort(g_compare_positions);

	if(zBuffer.size() > 0) {
		auto zEnd = zBuffer.end();
		for(auto it = zBuffer.begin(); it != zEnd; ++it) {
			IntersectionInfo info = *it;
			double dLambda = 0.2159;
			double dTau = exp(-dLambda * info.m_vSegmentLengths[0]);
			double dOpacity = 1-dTau;
			Vector3 vPower = Vector3(0.0, 0.0, 0.0);
			
			if(iDepth < iMaxDepth) {
				double	dDelta = info.m_vSegmentLengths[0] / dNumSamples;
				//printf("\nDelta: %f\n", dDelta);
				double	dInteg = 0.0;
				double	dFx 	 = 0.0;
				for(double t = info.m_vIntersects[0]; t < info.m_vIntersects[1]; t += dDelta) {
					Vector3 vPosition = pRay->m_vOrigin + t * pRay->m_vDirection;
					Vector3 vLight	= Vector3(0.0, 0.0, 0.0);
					//printf("\nint: %f, end: %f, is: %f\n", info.m_vIntersects[0], info.m_vIntersects[1], t);

					for(int l = 0; l < iNumLights; ++l) {
						//printf("\n%d\n", l);
						Vector3 vLightDirection = pScene->m_vpLightSources[l]->getLightDirection(&vPosition);
						Ray ray(vPosition, -vLightDirection);
					
						IntersectionInfo sInfo = pScene->m_vSpheres[info.m_iObjectId].getIntersectionInfo(ray);
						dFx = exp(-dLambda * sInfo.m_vIntersects[1]);
						//dFx *= Vector3Dot(sInfo.m_vNormals[1], -vLightDirection);
						vLight += dFx * calcColorOfRay(pScene, &ray, pScene->m_vpLightSources[l]->m_vTotalPower, info.m_iObjectId, iDepth+1, iMaxDepth);

					}

					vPower += dDelta * vLight * exp(-dLambda * (info.m_vIntersects[0] - t));
				}
				//printf("\njumpOut\n");
			}

			result = dOpacity * Vector3(7.0, 7.0, 7.0) + (1-dOpacity) * result + vPower;
		}
	} 

	return result;
}
