#include "GTRenderer.h"

Camera::Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vFocus)
: m_iWidth(iWidth), m_iHeight(iHeight), m_vPosition(vPosition), m_vFocus(vFocus) {
	m_ppvSensor = NULL;
	m_ppvSensor = new Vector3*[m_iWidth];
	
	for(int x = 0; x < iWidth; ++x) {
		m_ppvSensor[x] = new Vector3[m_iHeight];
	}

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
