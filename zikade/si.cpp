#include "zikade.h"

uint intersect(const ray& r, const sphere& s, hitInfo& info) {
	real b, c, d;

	real3 sr = r.o - s.c;
	b = dot(sr, r.d);
	c = dot(sr, sr) - (s.r * s.r);
	d = b * b - c;
	
	if (d < 0)
		return 0;
	
	real e = sqrt(d);
	info.tn = -b-e;
	info.tf = -b+e;
	return 1;
}

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
