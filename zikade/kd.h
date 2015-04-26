#ifndef KD_H
#define KD_H

#pragma once

bool kd_comp_x (const uint& a, const uint& b);
bool kd_comp_y (const uint& a, const uint& b);
bool kd_comp_z (const uint& a, const uint& b);

extern sphere* kd_spheres;

struct kdNode {
	uint 	id;
	int 	l;
	int 	r;
	uint* p;
	uint 	s;
	real3 min;
	real3 max;

	uint intersect(const ray& r) {
		real3 invr = 1.0 / r.d;
		real r1   = (min.x - r.o.x) * invr.x;
		real r2   = (max.x - r.o.x) * invr.x;
		real tmin = MIN(r1,r2);
		real tmax = MAX(r1,r2);

		r1   = (min.y - r.o.y) * invr.y;
		r2   = (max.y - r.o.y) * invr.y;
		tmin = MAX(MIN(r1, r2), tmin);
		tmax = MIN(MAX(r1, r2), tmax);

		r1   = (min.z - r.o.z) * invr.z;
		r2   = (max.z - r.o.z) * invr.z;
		tmin = MAX(MIN(r1, r2), tmin);
		tmax = MIN(MAX(r1, r2), tmax);
		return ((tmax >= tmin) && (tmax >= 0.0));
	}
};

class kdTree {
	private:
		uint				 numSpheres;
		uint				 numNodes;
		uint				 maxd;
		sphere*			 spheres;
		real3*			 mins;
		real3*			 maxs;
		kdNode*			 nodes;
		vector<kdNode>	 tmNodes;

		uint insert(list<uint>& indizes, uint d = 1);
		void creatBoundingBox(list<uint>& indizes, real3& min, real3& max);
		void split(list<uint>& indizes, list<uint>& l, list<uint>& r);

	public:
		kdTree(const uint& _numSpheres, sphere* _spheres, uint maxDepth = 20);
		~kdTree();

		void hit(const ray& r, list<hitInfo>& infos, int id = -1);
};

#endif
