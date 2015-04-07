#include "GTRenderer.h"

Box::Box() {
	m_vPosition = Vector3(0.0);
	m_vMin		= Vector3(-1.0);
	m_vMax		= Vector3(1.0);
}

Box::Box(const Vector3 vPosition, Vector3 vMin, Vector3 vMax, Material material) {
	m_vPosition	= vPosition;
	m_vMin		= vMin;
	m_vMax		= vMax;
	m_material	= material;
}

Box::~Box() {
}

IntersectionInfo Box::getIntersectionInfo(const Ray& ray, int iObjectId) {
	std::vector<Vector3> vPositions;
	std::vector<Vector3> vNormals;
	std::vector<double>  vIntersects;
	std::vector<double>	vSegmentLengths;
	Vector3	vPosition;
	Vector3	vNormal;

	Vector3 vDirFrac = 1.0 / ray.m_vDirection;
	double t[6];

	t[0] = (m_vMin.x - ray.m_vOrigin.x) * vDirFrac.x;
	t[1] = (m_vMax.x - ray.m_vOrigin.x) * vDirFrac.x;	
	t[2] = (m_vMin.y - ray.m_vOrigin.y) * vDirFrac.y;
	t[3] = (m_vMax.y - ray.m_vOrigin.y) * vDirFrac.y;
	t[4] = (m_vMin.z - ray.m_vOrigin.z) * vDirFrac.z;
	t[5] = (m_vMax.z - ray.m_vOrigin.z) * vDirFrac.z;

	double tMin = FM_MAX(FM_MAX(FM_MIN(t[0], t[1]), FM_MIN(t[2], t[3])), FM_MIN(t[4], t[5]));
	double tMax = FM_MIN(FM_MIN(FM_MAX(t[0], t[1]), FM_MAX(t[2], t[3])), FM_MAX(t[4], t[5]));
	
	if(tMin <= tMax) {
		vPosition = ray.m_vOrigin + tMin * ray.m_vDirection;
		vPositions.push_back(vPosition);
		vIntersects.push_back(tMin);
	// Normalen Fehlen
		vSegmentLengths.push_back(tMax - tMin);
	// Normalen Fehlen
		vPosition = ray.m_vOrigin + tMax * ray.m_vDirection;
		vPositions.push_back(vPosition);
		vIntersects.push_back(tMax);
	}

	return IntersectionInfo(ray,
									vPositions,
									vNormals,
									vIntersects,
									vSegmentLengths,
									iObjectId);
}

AABBox Box::createAABBox() {
	return AABBox(m_vMin, m_vMax);
}
