#include "GTRenderer.h"

double g_dCounter;

bool g_compare_positions (const IntersectionInfo& first, const IntersectionInfo& second) {
	if(first.m_vIntersects[1] > second.m_vIntersects[2])
  		return false;
	return true;
}

void renderPixel(int tId, int iChunkSize, double dMax, Scene* pScene, Camera* pCamera) {
	int begin = tId * iChunkSize;
	int end	 = (tId + 1) * iChunkSize;
	if(end > pCamera->m_iHeight)
		end = pCamera->m_iHeight;

	for(int y = begin; y < end; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			Ray ray = pCamera->getRay(x, y);
			pCamera->m_ppvSensor[x][y] = OCTracer::calcColorOfRay(pScene, &ray, Vector3(20, 20, 20), -1, 0, 1);
					
			if(pCamera->m_ppvSensor[x][y].r < 0) pCamera->m_ppvSensor[x][y].r = 0;
			if(pCamera->m_ppvSensor[x][y].g < 0) pCamera->m_ppvSensor[x][y].g = 0;
			if(pCamera->m_ppvSensor[x][y].b < 0) pCamera->m_ppvSensor[x][y].b = 0;
			if(pCamera->m_ppvSensor[x][y].r > 255) pCamera->m_ppvSensor[x][y].r = 255;
			if(pCamera->m_ppvSensor[x][y].g > 255) pCamera->m_ppvSensor[x][y].g = 255;
			if(pCamera->m_ppvSensor[x][y].b > 255) pCamera->m_ppvSensor[x][y].b = 255;

			g_dCounter++;
			printf("\rRender: [\033[31m%.2f %%\033[0m]", (float)((g_dCounter / dMax) * 100.0));
		}
	}
}

OCTracer::OCTracer() {
}

void OCTracer::render(Scene* pScene, Camera* pCamera) {
	double	dNumPixel = (double)(pCamera->m_iWidth * pCamera->m_iHeight);
	double	dNumCalcd = 0;

	std::vector<std::thread> threads;
	int iNumThreads = 32;
	int iChunkSize	 = pCamera->m_iHeight / iNumThreads;
	g_dCounter = 0;

	for(int t = 0; t < iNumThreads; ++t)
		threads.push_back(std::thread(renderPixel, t, iChunkSize, dNumPixel, pScene, pCamera));

	for (auto& th : threads) 
		th.join();
/*
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
*/
}

Vector3 OCTracer::calcColorOfRay(Scene* 	pScene, 
				 							Ray* 		pRay, 
											Vector3 	vLightColor,
											int		iObjectId,
											int 		iDepth, 
											int 		iMaxDepth) {
	std::list<IntersectionInfo> zBuffer;
	Vector3 result 	  = vLightColor;
	double  dNumSamples = 100;

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
			IntersectionInfo &info = *it;
			double dTau = exp(-pScene->m_vSpheres[info.m_iObjectId].m_material.m_dLambda  * info.m_vSegmentLengths[0]);
			double dOpacity = 1-dTau;
			Vector3 vPower = Vector3(0.0, 0.0, 0.0);
			
			if(iDepth < iMaxDepth) {
				double	dDelta = (info.m_vSegmentLengths[0] / dNumSamples) * (1.0/(double)iNumLights);
				//printf("\nDelta: %f\n", dDelta);
				double	dInteg = 0.0;
				double	dFx 	 = 0.0;
				for(double t = info.m_vIntersects[0]; t < info.m_vIntersects[1]; t += dDelta) {
					Vector3 vPosition = pRay->m_vOrigin + t * pRay->m_vDirection;
					Vector3 vColor		= Vector3(0.0, 0.0, 0.0);
					//printf("\nint: %f, end: %f, is: %f\n", info.m_vIntersects[0], info.m_vIntersects[1], t);

					for(int l = 0; l < iNumLights; ++l) {
						//printf("\n%d\n", l);
						Vector3 vLightDirection = pScene->m_vpLightSources[l]->getLightDirection(&vPosition);
						Ray ray(vPosition, -vLightDirection);
					
						IntersectionInfo sInfo = pScene->m_vSpheres[info.m_iObjectId].getIntersectionInfo(ray);
						dFx = exp(-pScene->m_vSpheres[info.m_iObjectId].m_material.m_dLambda * sInfo.m_vIntersects[1]);
						//dFx *= Vector3Dot(sInfo.m_vNormals[1], -vLightDirection);
						vColor += (1 - dFx) * pScene->m_vSpheres[info.m_iObjectId].m_material.m_vColor
								 +  dFx * calcColorOfRay(pScene, &ray, pScene->m_vpLightSources[l]->m_vTotalPower, info.m_iObjectId, iDepth+1, iMaxDepth);

					}
					dInteg = exp(-pScene->m_vSpheres[info.m_iObjectId].m_material.m_dLambda * (t - info.m_vIntersects[0]));
					vPower += dDelta * vColor * dInteg + (1-dInteg) * pScene->m_vSpheres[info.m_iObjectId].m_material.m_vColor;
				}
				//printf("\njumpOut\n");
			}

			result = /*dOpacity * pScene->m_vSpheres[info.m_iObjectId].m_material.m_vColor +*/ (1-dOpacity) * result + vPower;
		}
	} 

	return result;
}
