#include "GTRenderer.h"

RayTracer::RayTracer() {
}

void RayTracer::render(Scene* pScene, Camera* pCamera) const {

	for(int y = 0; y < pCamera->m_iHeight; ++y) {
		for(int x = 0; x < pCamera->m_iWidth; ++x) {
			if(x == y)
				pCamera->m_ppvSensor[x][y] = Vector3(20, 60, 70);
		}
	}

}
