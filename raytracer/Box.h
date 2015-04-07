#ifndef BOX_H
#define BOX_H

class AABBox;

class Box : public Primitive {
	public:
		Vector3 m_vMin;
		Vector3 m_vMax;

		Box();
		Box(Vector3 vPosition, Vector3 vMin, Vector3 vMax, Material material);
		~Box();
		
		IntersectionInfo getIntersectionInfo(const Ray& ray, int iObjectId = -1);
		AABBox			  createAABBox();
};

#endif
