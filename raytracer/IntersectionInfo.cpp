#include "GTRenderer.h"

IntersectionInfo::IntersectionInfo() {
}

IntersectionInfo::IntersectionInfo(Ray ray,
							  				  std::vector<Vector3> vPositions,
							  				  std::vector<Vector3> vNormals,
							  				  std::vector<double>  vIntersects,
							  				  std::vector<double>  vSegmentLengths,
											  int iObjectId)
: 	m_ray(ray), 
	m_vPositions(vPositions),
	m_vNormals(vNormals),
	m_vIntersects(vIntersects),
	m_vSegmentLengths(vSegmentLengths),
	m_iObjectId(iObjectId) {
	m_iNumIntersects = vIntersects.size();
}

IntersectionInfo::~IntersectionInfo() {
}
