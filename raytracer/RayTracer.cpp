#include "GTRenderer.h"

RayTracer::RayTracer() {
}

void RayTracer::render(Scene* pScene, Camera* pCamera) const {
	Vector3 vCamPos = pCamera->m_vPosition;
	vCamPos 			-= Vector3((float)pCamera->m_iWidth / 2.0f,
									  (float)pCamera->m_iHeight / 2.0f,
									  0.0f);

	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {

			for(int i = 0; i < pScene->m_vSpheres.size(); ++i) {
				Vector3 vOrigin = vCamPos + Vector3(x, y, 0);
				Ray ray(vOrigin, pCamera->m_vDirection);

				float t = pScene->m_vSpheres[i].intersect(ray);
				if(t == 0)
					pCamera->m_ppvSensor[x][y] = Vector3(20, 60, 70);
				else {
					//pCamera->m_ppvSensor[x][y] = Vector3(120, 0, 0);

					Vector3 normal = Vector3Normalize(vOrigin + t * pCamera->m_vDirection);
					float fCosAngle = Vector3Dot(normal, pCamera->m_vDirection);

					pCamera->m_ppvSensor[x][y] = Vector3(fCosAngle*255, 0, 0);
				}
					
			}
		}
	}

}
