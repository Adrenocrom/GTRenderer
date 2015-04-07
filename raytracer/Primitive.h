#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Ray;
class IntersectionInfo;
class AABBox;

class Primitive {
	public:
		Vector3 	m_vPosition;
		Material	m_material;
	
		virtual IntersectionInfo getIntersectionInfo(const Ray& ray, int iObjectId) = 0;
		virtual AABBox				 createAABBox() = 0;
};

#endif
