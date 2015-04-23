#ifndef IMAGE_H
#define IMAGE_H

#pragma once

class Ray;
class Camera;

void saveImageToFile(Camera& camera, const char* pcFilename);

class Camera {
	public:
		Vector3		m_vPosition;
		Vector3		m_vRotation;
		Vector3		m_vLookAt;
		int 			m_iWidth;
		int 			m_iHeight;
		Vector3** 	m_ppvSensor;

		Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vRotation, double dFocalLength);
		~Camera();

		//void saveImageToFile(const char* pcFilename);
		Ray	getRay(int x, int y);

	private:
		double		m_dFocalLength;
		double		m_dAspect;
		double		m_Matrix[9];

		Vector3		rotateCamera(Vector3& v);
};

#endif
