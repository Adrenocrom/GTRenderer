#include <GTRenderer.h>

bool AABBox::hit(Ray &ray) {
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
	
	if(tMin < 0)
		return false;
	
	if(tMin > tMax)
		return false;

	return true;
}

KDNode::KDNode() {

}

void KDNode::insertInNode(KDNode* pNode, std::vector<Sphere> spheres, KDNode* pParent) {

}

KDTree::KDTree() {
	
}

KDTree::~KDTree() {

}

void KDTree::insertInTree(std::vector<Sphere> spheres) {

}

AABBox KDTree::createAABBFromSphere(Sphere &sphere) {
	Vector3 vMax = sphere.m_vPosition + sphere.m_fRadius;
	Vector3 vMin = sphere.m_vPosition - sphere.m_fRadius;

	return AABBox(vMin, vMax);
}

std::vector<IntersectionInfo> KDTree::hit(Ray &ray) {
	std::vector<IntersectionInfo> infos;

	return infos;
}
