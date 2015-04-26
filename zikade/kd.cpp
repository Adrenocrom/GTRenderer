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

kdTree::kdTree(const uint& _numSpheres, sphere* _spheres) {
	numSpheres = _numSpheres;
	spheres	  = _spheres;
	kd_spheres = _spheres;
	list<uint> indizes;
	
	for(uint i = 0; i < numSpheres; ++i) {
		indizes.push_back(i);
		tmMins.push_back(spheres[i].p - spheres[i].r);
		tmMaxs.push_back(spheres[i].p + spheres[i].r);
	}

	insert(indizes);
}

void kdTree::creatBoundingBox(list<uint>& indizes, real3& min, real3& max) {
	min = tmMins[indizes.front()];
	max = tmMaxs[indizes.front()];

	for(uint index : indizes) {
		min = real3Min(min, tmMins[index]);
		max = real3Max(max, tmMaxs[index]);
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

uint kdTree::insert(list<uint>& indizes) {
	uint size = indizes.size();
	kdNode node;
	node.id = tmNodes.size();
	tmNodes.push_back(node);
	real3 max, min;

	if(size == 1) {
		tmNodes[node.id].l 	= -1;
		tmNodes[node.id].r 	= -1;
		tmNodes[node.id].p 	= indizes.front();
		tmNodes[node.id].min = tmMins[indizes.front()];
		tmNodes[node.id].max = tmMaxs[indizes.front()];
	} 
	else {
		list<uint> l, r;
		creatBoundingBox(indizes, min, max);
		split(indizes, l, r);

		tmNodes[node.id].p 	= -1;
		tmNodes[node.id].min = min;
		tmNodes[node.id].max = max;
		uint left 	= insert(l);
		uint right 	= insert(r);
		tmNodes[node.id].l 	= left;
		tmNodes[node.id].r 	= right;
	}
	return node.id;
}

void kdTree::hit(const ray& r, list<hitInfo>& infos, int id) {
	hitInfo			 	info;
	list<kdNode>		stack;
	uint					num;

	stack.push_back(tmNodes.front());
	while(!stack.empty()) {
		kdNode& node = stack.front();

		if(node.p != -1) {
			num = intersect(r, spheres[node.p], info);
			info.id = node.p;

			if(num != 0 && info.tn > 0 && info.id != id)
				infos.push_back(info);
		} else {
			if(intersect(r, node.min, node.max)) {
				stack.push_back(tmNodes[node.l]);
				stack.push_back(tmNodes[node.r]);
			}
		}

		stack.pop_front();
	}
}
