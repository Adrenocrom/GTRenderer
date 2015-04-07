#include "GTRenderer.h"

Sphere::Sphere() {
	m_vPosition = Vector3(0.0, 0.0, 0.0);
	m_fRadius = 1.0f;
}

Sphere::Sphere(const Vector3 vPosition, double fRadius, Material material) {
	m_vPosition = vPosition;
	m_fRadius	= fRadius;
	m_material	= material;
}

Sphere::~Sphere() {

}

std::pair<double, double> Sphere::intersect(const Ray& r, int* iNumIntersects) {
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

	if(iNumIntersects) {
		*iNumIntersects = roots;
	} 
		
	if(roots == 1)
		return std::make_pair(t1, t1);
	else if(roots == 2)
		return std::make_pair(t1, t2);
	else
		return std::make_pair(0, 0);
}

IntersectionInfo Sphere::getIntersectionInfo(const Ray& ray, int iObjectId) {
	std::vector<Vector3> vPositions;
	std::vector<Vector3> vNormals;
	std::vector<double>  vIntersects;
	std::vector<double>	vSegmentLengths;
	int iNumIntersects = 0;
	Vector3	vPosition;
	Vector3	vNormal;

	std::pair<double, double> t12 = intersect(ray, &iNumIntersects);
	
	if(iNumIntersects > 0) {
		vPosition = ray.m_vOrigin + t12.first * ray.m_vDirection;
		vNormal   = Vector3Normalize(vPosition - m_vPosition);
		vPositions.push_back(vPosition);
		vNormals.push_back(vNormal);
		vIntersects.push_back(t12.first);

		vSegmentLengths.push_back(t12.second - t12.first);

		vPosition = ray.m_vOrigin + t12.second * ray.m_vDirection;
		vNormal   = Vector3Normalize(vPosition - m_vPosition);
		vPositions.push_back(vPosition);
		vNormals.push_back(vNormal);
		vIntersects.push_back(t12.second);
	}

	return IntersectionInfo(ray,
									vPositions,
									vNormals,
									vIntersects,
									vSegmentLengths,
									iObjectId);
}

AABBox Sphere::createAABBox() {
	Vector3 vMax = m_vPosition + m_fRadius;
	Vector3 vMin = m_vPosition - m_fRadius;
	return AABBox(vMin, vMax);
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
