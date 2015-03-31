#ifndef KDTREE_H
#define KDTREE_H

class AABBox {
	public:
		AABBox() : m_vMin(Vector3(-1.0)), m_vMax(Vector3(1.0)) {}
		AABBox(Vector3 vMin, Vector3 vMax) : m_vMin(vMin), m_vMax(vMax) {}
	
		bool hit(Ray &ray);

	private:
		Vector3	m_vMin;
		Vector3	m_vMax;
};

class KDNode {
	public:
		KDNode();

		AABBox  m_vAABB;
		KDNode* m_pParent;
		KDNode* m_pLeft;
		KDNode* m_pRight;
		bool	  m_isLeaf;
		int	  m_iSphere;

		void insertInNode(KDNode* pNode, std::vector<Sphere> spheres, KDNode* pParent = 0);
};

class KDTree {
	public:
		KDTree();
		~KDTree();

		KDNode m_pRoot;

		void insertInTree(std::vector<Sphere> spheres);
		AABBox createAABBFromSphere(Sphere &sphere);

		std::vector<IntersectionInfo> hit(Ray &ray);
};

#endif
