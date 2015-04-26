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
	int  	p;
	real3 min;
	real3 max;
};

class kdTree {
	private:
		uint				 numSpheres;
		sphere*			 spheres;
		vector<real3>	 tmMins;
		vector<real3>	 tmMaxs;
		vector<kdNode>	 tmNodes;

		uint insert(list<uint>& indizes);
		void creatBoundingBox(list<uint>& indizes, real3& min, real3& max);
		void split(list<uint>& indizes, list<uint>& l, list<uint>& r);

	public:
		kdTree(const uint& _numSpheres, sphere* _spheres);

		void hit(const ray& r, list<hitInfo>& infos, int id = -1);
};

#endif
