#include "GTRenderer.h"

Sphere::Sphere() {
	m_fRadius = 1.0f;
}

Sphere::Sphere(const Vector3 vPosition, double fRadius) {
	m_vPosition = vPosition;
	m_fRadius	= fRadius;
}

Sphere::~Sphere() {

}

double Sphere::intersect(const Ray& r) {
	Vector3 op = m_vPosition - r.m_vOrigin;
	double t 	  = 0.0f;
	double b	  = Vector3Dot(op, r.m_vDirection);
	double det  = b*b - Vector3Dot(op, op) + m_fRadius*m_fRadius;
	
	if(det < 0)
		return 0;
	else
		det = sqrt(det);

	return (t = b - det) > 1e-4 ? t : ((t = b + det) > 1e-4 ? t : 0);
}

std::pair<double, double> Sphere::intersect2(const Ray& r) {
	double boundingSquare = m_fRadius * m_fRadius ;
	Vector3 origin = r.m_vOrigin - m_vPosition;
 	double a, b, c;
 	a = Vector3Dot(r.m_vDirection, r.m_vDirection );
	// DotDot ^= Skalarprod mit sichselbst : <d, d>
	b = 2 * Vector3Dot(origin, r.m_vDirection );
	// * ^= normales Skalarprod
	c = Vector3Dot(origin, origin) - boundingSquare;
 
	double t1 , t2 ;
	int roots = CalcQuadricRoots (a, b, c, &t1, &t2) ;
 
   if (roots > 0)
		return std::make_pair((t1 >= 0 ? t1 : t2), -1);
 /*     // kleinsterpositiver pos. Wert aus t1, t2
	else if(roots == 2)
		return std::make_pair(t1, t2);*/
	else
		return std::make_pair(-1, -1);
}

int Sphere::CalcQuadricRoots(double a, double b, double c, double* x1, double* x2) {
	double determinant = b * b - 4 * a * c;
	if (determinant < 0) {
		*x1 = 0.0;
		*x2 = 0.0;
		return 0;
	}
    
	determinant = sqrt(determinant);
	double q = -0.5 * (b + PSgn(b) * determinant);
	// Psgn: gives - 1 if b < 0 and 1 if b >= 0. 
	// so no zero as normal sgn would give us.
	*x1 = q / a;
	*x2 = c / q;
 	// Sort by value
	if (*x1 > *x2) {
		q = *x2; *x2 = *x1; *x1 = q;
	}
	return *x1 == *x2 ? 1 : 2;
}

double Sphere::PSgn(double d) {
	if(d < 0)
		return -1;
	return 1;
}
