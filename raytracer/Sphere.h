#ifndef SPHERE_H
#define SPHERE_H

#pragma once

class Ray;

class Sphere {
	public:
		Vector3	m_vPosition;
		float		m_fRadius;
	
		Sphere();
		Sphere(const Vector3 vPosition, float fRadius);
		~Sphere();

		float intersect(const Ray& r);
};

#endif
