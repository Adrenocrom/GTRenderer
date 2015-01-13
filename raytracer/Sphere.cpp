#include "GTRenderer.h"

Sphere::Sphere() {
	m_fRadius = 1.0f;
}

Sphere::Sphere(const Vector3 vPosition, float fRadius) {
	m_vPosition = vPosition;
	m_fRadius	= fRadius;
}

Sphere::~Sphere() {

}

float Sphere::intersect(const Ray& r) {
	Vector3 op = m_vPosition - r.m_vOrigin;
	float t 	  = 0.0f;
	float b	  = Vector3Dot(op, r.m_vDirection);
	float det  = b*b - Vector3Dot(op, op) + m_fRadius*m_fRadius;
	
	if(det < 0)
		return 0;
	else
		det = sqrt(det);

	return (t = b - det) > 1e-4 ? t : ((t = b + det) > 1e-4 ? t : 0);
}
