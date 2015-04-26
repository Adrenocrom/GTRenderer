#include "zikade.h"

sphere* kd_spheres;

bool kd_comp_x (const uint& a, const uint& b) {
	if(kd_spheres[a].p.x > kd_spheres[b].p.x)
	  		return false;
	return true;
}

bool kd_comp_y (const uint& a, const uint& b) {
	if(kd_spheres[a].p.y > kd_spheres[b].p.y)
	  		return false;
	return true;
}

bool kd_comp_z (const uint& a, const uint& b) {
	if(kd_spheres[a].p.z > kd_spheres[b].p.z)
	  		return false;
	return true;
}

kdTree::kdTree(const uint& _numSpheres, sphere* _spheres, uint maxDepth) {
	numSpheres 	= _numSpheres;
	spheres	  	= _spheres;
	kd_spheres 	= _spheres;
	maxd			= maxDepth;
	mins 			= new real3[numSpheres];
	maxs 			= new real3[numSpheres];
	list<uint> indizes;

	for(uint i = 0; i < numSpheres; ++i) {
		indizes.push_back(i);
		mins[i] = spheres[i].p - spheres[i].r;
		maxs[i] = spheres[i].p + spheres[i].r;
	}

	insert(indizes);
	numNodes = tmNodes.size();
	nodes = new kdNode[numNodes];
	for(uint i = 0; i < numNodes; ++i)
		nodes[i] = tmNodes[i];
	tmNodes.clear();
}

kdTree::~kdTree() {
	SAFE_DELETE_ARRAY(mins);
	SAFE_DELETE_ARRAY(maxs);
	SAFE_DELETE_ARRAY(nodes);
}

void kdTree::creatBoundingBox(list<uint>& indizes, real3& min, real3& max) {
	min = mins[indizes.front()];
	max = maxs[indizes.front()];

	for(uint index : indizes) {
		min = real3Min(min, mins[index]);
		max = real3Max(max, maxs[index]);
	}
}

void kdTree::split(list<uint>& indizes, list<uint>& l, list<uint>& r) {
	real3 min_pos = spheres[indizes.front()].p;
	real3 max_pos = min_pos;

	// finde die weiteste ausdehnung
	auto end = indizes.end();
	for(auto it = indizes.begin(); it != end; ++it) {
		min_pos = real3Min(min_pos, spheres[*it].p);
		max_pos = real3Max(max_pos, spheres[*it].p);
	}

	uint d = real3MaxDim(max_pos - min_pos);
	// sortiere alle primitiven nach den mittelpunkten
	switch(d) {
		case 0:
			indizes.sort(&kd_comp_x);
		break;
		case 1:
			indizes.sort(&kd_comp_y);
		break;
		case 2:
			indizes.sort(&kd_comp_z);
		break;
	}
	// splitte am median
	uint median = (uint)((real)(indizes.size() + 1) / 2.0);
	uint loop 	= 0;
	for(auto it = indizes.begin(); it != end; ++it) {
		if(loop < median)
			l.push_back(*it);
		else
			r.push_back(*it);
		loop++;
	} 
}

uint kdTree::insert(list<uint>& indizes, uint d) {
	uint size = indizes.size();
	kdNode node;
	node.id = tmNodes.size();
	tmNodes.push_back(node);
	real3 min, max;
	creatBoundingBox(indizes, min, max);

	if(d >= maxd || size == 1) {
		tmNodes[node.id].l 	= -1;
		tmNodes[node.id].r 	= -1;
		tmNodes[node.id].p 	= new uint[size];
		tmNodes[node.id].s	= size;
		tmNodes[node.id].min = min;
		tmNodes[node.id].max = max;
			
		uint cnt	 = 0;
		for(uint index : indizes) {
			tmNodes[node.id].p[cnt] = index;
			cnt++;
		}
	} 
	else {
		list<uint> l, r;
		split(indizes, l, r);

		tmNodes[node.id].p 	= NULL;
		tmNodes[node.id].s	= 0;
		tmNodes[node.id].min = min;
		tmNodes[node.id].max = max;
		uint left 	= insert(l, d+1);
		uint right 	= insert(r, d+1);
		tmNodes[node.id].l 	= left;
		tmNodes[node.id].r 	= right;
	}
	return node.id;
}

void kdTree::hit(const ray& r, list<hitInfo>& infos, int id) {
	hitInfo			 	info;
	list<uint>			stack;
	uint					num;

	stack.push_back(0);
	while(!stack.empty()) {
		kdNode& node = nodes[stack.front()];

		if(node.p) {
			for(uint i = 0; i < node.s; ++i) {
				num = spheres[node.p[i]].intersect(r, info);
				info.id = node.p[i];

				if(num != 0 && info.tn > 0 && info.id != id)
					infos.push_back(info);
			}
		} else {
			if(node.intersect(r)) {
				stack.push_back(node.l);
				stack.push_back(node.r);
			}
		}

		stack.pop_front();
	}
}
