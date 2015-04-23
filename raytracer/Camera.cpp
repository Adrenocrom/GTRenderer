#include "GTRenderer.h"

Camera::Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vRotation, double dFocalLength)
: m_iWidth(iWidth), m_iHeight(iHeight), m_vPosition(vPosition), m_vRotation(vRotation), m_dFocalLength(dFocalLength) {
	m_ppvSensor = NULL;
	m_ppvSensor = new Vector3*[m_iWidth];
	
	for(int x = 0; x < iWidth; ++x) {
		m_ppvSensor[x] = new Vector3[m_iHeight];
	}

	m_dAspect = (double)m_iWidth / (double)m_iHeight;

	m_vRotation *= 0.017453293;
	//m_vRotation.x *= -1.0;

	double dSinA = sin(m_vRotation.x);
	double dCosA = cos(m_vRotation.x);
	double dSinB = sin(m_vRotation.y);
	double dCosB = cos(m_vRotation.y);
					
	m_Matrix[0] = dCosB;
	m_Matrix[1] = -(dSinA*dSinB);
	m_Matrix[2] = dCosA * dSinB;
	m_Matrix[3] = 0.0;
	m_Matrix[4] = dCosA;
	m_Matrix[5] = -dSinA;
	m_Matrix[6] = -dSinB;
	m_Matrix[7] = -(dSinA * dCosB);
	m_Matrix[8] = dCosA * dCosB;
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
	Vector3 vDirection = Vector3((-m_dAspect) + (((double)x) / ((double)m_iWidth)) * 2.0 * m_dAspect,
							   1.0 + ((double)y) / ((double)m_iHeight) * -2.0,
							   m_dFocalLength);
	return Ray(m_vPosition,  Vector3Normalize(rotateCamera(vDirection)));
}


/*
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
}*/

Vector3 Camera::rotateCamera(Vector3& v) {
	Vector3 vResult(v.x * m_Matrix[0] + v.y * m_Matrix[1] + v.z * m_Matrix[2],
						 v.x * m_Matrix[3] + v.y * m_Matrix[4] + v.z * m_Matrix[5],
						 v.x * m_Matrix[6] + v.y * m_Matrix[7] + v.z * m_Matrix[8]);
	return vResult;
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
