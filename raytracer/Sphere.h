#ifndef SPHERE_H
#define SPHERE_H

#pragma once

class Ray;

class Sphere {
	public:
		Vector3	m_vPosition;
		double	m_fRadius;
	
		Sphere();
		Sphere(const Vector3 vPosition, double fRadius);
		~Sphere();

		double intersect(const Ray& r);
		std::pair<double, double> intersect2(const Ray& r);

	private:
		int CalcQuadricRoots(double a, double b, double c, double* x1, double* x2);
		double PSgn(double d);
};

#endif
