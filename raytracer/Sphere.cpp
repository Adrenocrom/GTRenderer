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
