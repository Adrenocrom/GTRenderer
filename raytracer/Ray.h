#ifndef RAY_H
#define RAY_H

#pragma once

class Ray {
	public:
		Vector3	m_vOrigin;
		Vector3	m_vDirection;

		Ray(Vector3 vO, Vector3 vD) : m_vOrigin(vO), m_vDirection(vD) {
			m_vDirection = Vector3Normalize(m_vDirection);
		}
};

#endif
