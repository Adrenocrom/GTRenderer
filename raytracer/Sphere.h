#ifndef SPHERE_H
#define SPHERE_H

#pragma once

class Ray;
class IntersectionInfo;

class Sphere {
	public:
		Vector3	m_vPosition;
		double	m_fRadius;
		Material m_material;
	
		Sphere();
		Sphere(const Vector3 vPosition, double fRadius, Material material);
		~Sphere();

		std::pair<double, double> intersect(const Ray& ray, int* iNumIntersects = NULL);
		IntersectionInfo getIntersectionInfo(const Ray& ray, int iObjectId = -1);

	private:
		int CalcQuadricRoots(double a, double b, double c, double* x1, double* x2);
		double PSgn(double d);
};

#endif
