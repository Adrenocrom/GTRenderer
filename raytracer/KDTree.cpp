#include <GTRenderer.h>

//#include <cuda.h>

bool g_compare_positions_x (const int& first, const int& second) {
	if(g_pScene->m_vpPrimitives[first]->m_vPosition.x > g_pScene->m_vpPrimitives[second]->m_vPosition.x)
  		return false;
	return true;
}

bool g_compare_positions_y (const int& first, const int& second) {
	if(g_pScene->m_vpPrimitives[first]->m_vPosition.y > g_pScene->m_vpPrimitives[second]->m_vPosition.y)
  		return false;
	return true;
}

bool g_compare_positions_z (const int& first, const int& second) {
	if(g_pScene->m_vpPrimitives[first]->m_vPosition.z > g_pScene->m_vpPrimitives[second]->m_vPosition.z)
  		return false;
	return true;
}

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
	
	if(tMin > tMax)
		return false;

	return true;
}

KDTree::KDTree() {}

KDTree::~KDTree() {}

void KDTree::createTree() {
	int iNumPrimives = g_pScene->m_vpPrimitives.size();
	std::list<int> viPrimitives;

	for(int i = 0; i < iNumPrimives; ++i) {
		m_vAABBoxes.push_back(g_pScene->m_vpPrimitives[i]->createAABBox());
		viPrimitives.push_back(i);
	}
	
	insertInTree(viPrimitives);
}

int KDTree::insertInTree(std::list<int> viPrimitives, int iParent) {
	int 		iNumPrimives = viPrimitives.size();

	SKDNode 	node;
	node.iParent = iParent;
	node.iD		 = m_vSKDNodes.size();
	m_vSKDNodes.push_back(node);

	if(iNumPrimives == 1) {
		m_vSKDNodes[node.iD].iLeft 	= -1;
		m_vSKDNodes[node.iD].iRight 	= -1;
		m_vSKDNodes[node.iD].bLeaf		= true;
		m_vSKDNodes[node.iD].iPrimitiv = viPrimitives.front();
	}
	else {
		m_vSKDNodes[node.iD].bLeaf			= false;
		m_vSKDNodes[node.iD].iPrimitiv	= -1;
		m_vSKDNodes[node.iD].aabb			= createAABBox(viPrimitives);
		
		auto childs = splitPrimitives(viPrimitives, node.iD);

		int iLeft 	= insertInTree(childs.first, 	node.iD);
		int iRight 	= insertInTree(childs.second, node.iD);
		m_vSKDNodes[node.iD].iLeft	 = iLeft;
		m_vSKDNodes[node.iD].iRight = iRight;
	}
	return node.iD;
}

AABBox KDTree::createAABBox(std::list<int>& viPrimitives) {
	Vector3 vMin = g_pScene->m_vpPrimitives[viPrimitives.front()]->createAABBox().m_vMin;
	Vector3 vMax = g_pScene->m_vpPrimitives[viPrimitives.front()]->createAABBox().m_vMax;
	
	for(int index : viPrimitives) {
		AABBox aabb = g_pScene->m_vpPrimitives[index]->createAABBox();
		vMin = Vector3Min(vMin, aabb.m_vMin);
		vMax = Vector3Max(vMax, aabb.m_vMax);
	}

	return AABBox(vMin, vMax);
}

std::pair<std::list<int>, std::list<int> >	KDTree::splitPrimitives(std::list<int>& viPrimitives, int iD) {
	std::pair<std::list<int>, std::list<int> > result;
	Vector3 vMinPos = g_pScene->m_vpPrimitives[viPrimitives.front()]->m_vPosition;
	Vector3 vMaxPos = g_pScene->m_vpPrimitives[viPrimitives.front()]->m_vPosition;

	// finde die weiteste ausdehnung
	auto end = viPrimitives.end();
	for(auto it = viPrimitives.begin(); it != end; ++it) {
		vMinPos = Vector3Min(vMinPos, g_pScene->m_vpPrimitives[*it]->m_vPosition);
		vMaxPos = Vector3Max(vMaxPos, g_pScene->m_vpPrimitives[*it]->m_vPosition);
	}

	int iDim = Vector3BiggestDimension(vMaxPos - vMinPos);
	// sortiere alle primitiven nach den mittelpunkten
	switch(iDim) {
		case 0:
			viPrimitives.sort(g_compare_positions_x);
		break;
		case 1:
			viPrimitives.sort(g_compare_positions_y);
		break;
		case 2:
			viPrimitives.sort(g_compare_positions_z);
		break;
	}

	// splitte am median
	int iMedian = (int)((float)(viPrimitives.size() + 1) / 2.0f);
	int iLoop 	= 0;
	for(auto it = viPrimitives.begin(); it != end; ++it) {
		if(iLoop < iMedian)
			result.first.push_back(*it);
		else
			result.second.push_back(*it);

		iLoop++;
	} 

	return result;
}

std::vector<IntersectionInfo> KDTree::hit(Ray &ray) {
	std::vector<IntersectionInfo> infos;
	std::list<SKDNode>				stack;

	stack.push_back(m_vSKDNodes.front());
	while(!stack.empty()) {
		SKDNode node = stack.front();

		//std::cout<<node.iD<<std::endl;

		if(node.bLeaf) {
			IntersectionInfo info = g_pScene->m_vpPrimitives[node.iPrimitiv]->getIntersectionInfo(ray, node.iPrimitiv);
			if(info.m_iNumIntersects != 0 && info.m_vIntersects[0] > 0)
				infos.push_back(info);
		} else {
		//	std::cout<<node.iLeft<<" - "<<node.iRight<<std::endl;
			if(node.aabb.hit(ray)) {
				stack.push_back(m_vSKDNodes[node.iLeft]);
				stack.push_back(m_vSKDNodes[node.iRight]);
			}
		}

		stack.pop_front();
	}

	return infos;
}

std::vector<IntersectionInfo> cudaHit(Ray &ray) {
/*	std::vector<IntersectionInfo> infos;
	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;

	cudaMalloc((void **) &dev_a, N*sizeof(int));
	cudaMalloc((void **) &dev_b, N*sizeof(int));
	cudaMalloc((void **) &dev_c, N*sizeof(int));

	// Fill Arrays
	for (int i = 0; i < N; i++) {
		a[i] = i,
		b[i] = 1;
	}

	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);

	add<<<N,1>>>(dev_a, dev_b, dev_c);

	cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);
	return infos;*/
}
