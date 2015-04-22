#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

class IntersectionInfo {
	public:
		int	  m_iObjectId;
		Ray	  m_ray;
		std::vector<Vector3> m_vPositions;
		std::vector<Vector3> m_vNormals;
		std::vector<double>	m_vIntersects;
		std::vector<double>	m_vSegmentLengths;
		int	  m_iNumIntersects;

		//IntersectionInfo() {}
		IntersectionInfo(Ray ray,
							  std::vector<Vector3> vPositions,
							  std::vector<Vector3> vNormals,
							  std::vector<double>  vIntersects,
							  std::vector<double>  vSegmentLengths,
							  int iObjectId = -1);

		~IntersectionInfo();
};

#endif
