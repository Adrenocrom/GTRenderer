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
	double r[9];
	double dSinA = sin(m_vRotation.x);
	double dCosA = cos(m_vRotation.x);
	double dSinB = sin(m_vRotation.y);
	double dCosB = cos(m_vRotation.y);
	
	r[0] = dCosB;
	r[1] = -(dSinA*dSinB);
	r[2] = dCosA * dSinB;
	r[3] = 0.0;
	r[4] = dCosA;
	r[5] = -dSinA;
	r[6] = -dSinB;
	r[7] = -(dSinA * dCosB);
	r[8] = dCosA * dCosB;

	Vector3 vResult(v.x * r[0] + v.y * r[1] + v.z * r[2],
						 v.x * r[3] + v.y * r[4] + v.z * r[5],
						 v.x * r[6] + v.y * r[7] + v.z * r[8]);
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
