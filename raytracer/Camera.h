#ifndef IMAGE_H
#define IMAGE_H

#pragma once

class Ray;

class Camera {
	public:
		Vector3		m_vPosition;
		Vector3		m_vFocus;
		Vector3		m_vDirection;
		int 			m_iWidth;
		int 			m_iHeight;
		double		m_dAspect;
		Vector3** 	m_ppvSensor;

		Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vFocus);
		~Camera();

		void saveImageToFile(const char* pcFilename);
		Ray	getRay(int x, int y);
	private:
		double	m_dWidth;
		double	m_dHeight;
		double	m_dWStep;
		double	m_dHStep;
};

#endif
