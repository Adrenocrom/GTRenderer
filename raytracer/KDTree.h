#ifndef KDTREE_H
#define KDTREE_H

#pragma once

class Scene;

bool g_compare_positions_x (const int& first, const int& second);
bool g_compare_positions_y (const int& first, const int& second);
bool g_compare_positions_z (const int& first, const int& second);

class AABBox {
	public:
		AABBox() : m_vMin(Vector3(-1.0)), m_vMax(Vector3(1.0)) {}
		AABBox(Vector3 vMin, Vector3 vMax) : m_vMin(vMin), m_vMax(vMax) {}
	
		bool hit(Ray &ray);

		Vector3	m_vMin;
		Vector3	m_vMax;
};

struct SKDNode {
		AABBox  aabb;
		int 	  iParent;
		int	  iD;
		int	  iLeft;
		int	  iRight;
		bool	  bLeaf;
		int	  iPrimitiv;
};

class KDTree {
	public:
		KDTree();
		~KDTree();

		std::vector<SKDNode> m_vSKDNodes;

		void createTree();

		std::vector<IntersectionInfo> hit(Ray &ray);

		// find intersects via GPU
		std::vector<IntersectionInfo> cudaHit(Ray &ray);

	private:
		int insertInTree(std::list<int> viPrimitives, int iParent = -1);
		std::pair<std::list<int>, std::list<int> >	splitPrimitives(std::list<int>& viPrimitives, int iD);
		AABBox	createAABBox(std::list<int>& viPrimitives);

		std::vector<AABBox>	m_vAABBoxes;
};

#endif
