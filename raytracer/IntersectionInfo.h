#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

class IntersectionInfo {
	public:
		int	  m_iObjectId;		// Object
		double  m_fLength;
		Ray	  m_incomingRay;
		Vector3 m_vNormal;		// Surfacenormal

		IntersectionInfo(Ray r, double fLength = -1);
		~IntersectionInfo();

		void setNormal(Vector3 vNormal) {m_vNormal = vNormal;}
		Vector3 getNormal() {return m_vNormal;}
};

#endif
