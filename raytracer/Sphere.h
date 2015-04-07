#ifndef SPHERE_H
#define SPHERE_H

#pragma once

class Ray;
class IntersectionInfo;
class AABBox;

class Sphere : public Primitive {
	public:
		double	m_fRadius;
	
		Sphere();
		Sphere(const Vector3 vPosition, double fRadius, Material material);
		~Sphere();

		std::pair<double, double> intersect(const Ray& ray, int* iNumIntersects = NULL);
		
		IntersectionInfo getIntersectionInfo(const Ray& ray, int iObjectId = -1);
		AABBox			  createAABBox();		

	private:
		int CalcQuadricRoots(double a, double b, double c, double* x1, double* x2);
		double PSgn(double d);
};

#endif
