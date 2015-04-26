#include "zikade.h"
/*
uint intersect(const ray& r, const sphere& s, hitInfo& info) {
	real b, d;

	real3 op = r.o - s.p;
	b = dot(op, r.d);
	d = b*b - dot(op, op) + s.r * s.r;
	
	if (d < 0)
		return 0;
	
	d = sqrt(d);
	info.tn = -b-d;
	info.tf = -b+d;
	return 1;
}

uint intersect(const ray& r, const real3& min, const real3& max) {
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
*/
void saveRgbWxHToPbm(const rgbWxH& image, const char* pcFilename) {
	FILE* file = NULL;

	if((file = fopen(pcFilename, "w")) == NULL) {
		printf("couldn't write file %s", pcFilename);
		return;
	}

	fprintf(file, "P3\n%d %d 255\n", SI_WIDTH, SI_HEIGHT);
	for(int y = 0; y < SI_HEIGHT; ++y) {
		for(int x = 0; x < SI_WIDTH; ++x) {
			fprintf(file, "%d ", image[x][y].r);
			fprintf(file, "%d ", image[x][y].g);

			if(x == (SI_WIDTH-1))
				fprintf(file, "%d\n", image[x][y].b);
			else
				fprintf(file, "%d ", image[x][y].b);
		}
	}

	fclose(file);
}
