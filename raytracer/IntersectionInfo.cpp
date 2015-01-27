#include "GTRenderer.h"

IntersectionInfo::IntersectionInfo(Ray r, double fLength)
: m_incomingRay(r), m_fLength(fLength) {
	
}

IntersectionInfo::~IntersectionInfo() {
}
