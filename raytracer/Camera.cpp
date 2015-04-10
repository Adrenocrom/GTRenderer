#include "GTRenderer.h"

Camera::Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vFocus)
: m_iWidth(iWidth), m_iHeight(iHeight), m_vPosition(vPosition), m_vFocus(vFocus) {
	m_ppvSensor = NULL;
	m_ppvSensor = new Vector3*[m_iWidth];
	
	for(int x = 0; x < iWidth; ++x) {
		m_ppvSensor[x] = new Vector3[m_iHeight];
	}

	m_dAspect = (double)m_iWidth / (double)m_iHeight;
	m_dWidth	 = 10.0f * m_dAspect;
	m_dHeight = 10.0f;
	m_dWStep	 = m_dWidth / (double) m_iWidth;
	m_dHStep	 = m_dHeight / (double) m_iHeight;

	m_vDirection = Vector3Normalize(m_vFocus - m_vDirection);
}

Camera::~Camera() {
	if(m_ppvSensor) {
		for(int x = 0; x < m_iWidth; ++x) {
			delete[] m_ppvSensor[x];
			m_ppvSensor[x] = NULL;
		}
		delete[] m_ppvSensor;
		m_ppvSensor = NULL;
	}
}

Ray Camera::getRay(int x, int y) {
	/*
	double dX = x * m_dWStep - (m_dWidth / 2.0);
	double dY = y * m_dHStep - (m_dHeight / 2.0);
	Vector3 vO = Vector3(0.0, 0.0, 0.0);
	Vector3 vF = Vector3(dX, dY, 1.0);
	return Ray(vO, Vector3Normalize(vF));*/

	double bottom  = -0.2;
	double top		= 0.2;
	double left		= -m_dAspect * 0.2;
	double right	= m_dAspect * 0.2;
	double xpart, ypart;

	Vector3 vOrigin = Vector3(((double)x) / ((double)m_iWidth),
									  ((double)y) / ((double)m_iHeight),
									  0.0);
	vOrigin.x = (left + vOrigin.x * (right - left));//* m_dAspect;
	vOrigin.y =  top  + vOrigin.y * (bottom - top);
	Vector3 vDirection = Vector3( vOrigin.x,
											vOrigin.y,
											1.0 );
	return Ray(m_vPosition,  Vector3Normalize(vDirection));
}



void Camera::saveImageToFile(const char* pcFilename) {
	QImage result(m_iWidth, m_iHeight, QImage::Format_RGB32);

	for(int y = 0; y < m_iHeight; ++y) {
		for(int x = 0; x < m_iWidth; ++x) {
			result.setPixel(x, y, qRgb((int)m_ppvSensor[x][y].r,
												(int)m_ppvSensor[x][y].g,
												(int)m_ppvSensor[x][y].b));			
		}
	}

	result.save(pcFilename);
}

void saveImageToFile(Camera& camera, const char* pcFilename) {
	FILE* pFile = NULL;
	if((pFile = fopen(pcFilename, "w")) == NULL) {
		printf("couldn't write file %s", pcFilename);
		return;
	}

	fprintf(pFile, "P3\n%d %d 255\n", camera.m_iWidth, camera.m_iHeight);

	for(int y = 0; y < camera.m_iHeight; ++y) {
		for(int x = 0; x < camera.m_iWidth; ++x) {
			fprintf(pFile, "%d ", (int)camera.m_ppvSensor[x][y].x);
			fprintf(pFile, "%d ", (int)camera.m_ppvSensor[x][y].y);

			if(x == (camera.m_iWidth-1))
				fprintf(pFile, "%d\n", (int)camera.m_ppvSensor[x][y].z);
			else
				fprintf(pFile, "%d ", (int)camera.m_ppvSensor[x][y].z);

		}
	}

	fclose(pFile);
	pFile = NULL;
}
