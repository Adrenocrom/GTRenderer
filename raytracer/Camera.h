#ifndef IMAGE_H
#define IMAGE_H

#pragma once

class Camera {
	public:
		Vector3		m_vPosition;
		Vector3		m_vFocus;
		Vector3		m_vDirection;
		int 			m_iWidth;
		int 			m_iHeight;
		Vector3** 	m_ppvSensor;

		Camera(int iWidth, int iHeight, Vector3 vPosition, Vector3 vFocus);
		~Camera();

		void saveImageToFile(const std::string& str_filename);

};

#endif
