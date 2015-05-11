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
int saveRgbWxHToPbm(const rgbWxH& image, const char* filename) {
	FILE* file = NULL;

	if((file = fopen(filename, "w")) == NULL) {
		printf("couldn't write file %s", filename);
		return 1;
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
	return 0;
}

int loadPbmToRgbWxH(rgbWxH& image, const char* filename) {
	ifstream file(filename);
	if(!file.is_open()) {
		cerr << "Error: Could not find file "<<filename<<endl;
		return 1;
	}

	uint x = 0, y = 1; 
	uint width, height;
	int r, b, g;
	string str_line, entry;
	getline(file, str_line, '\n');
	getline(file, str_line, '\n');
	stringstream line(str_line);
	line >> width; line >> height;
	
	if(width != SI_WIDTH || height != SI_HEIGHT) {
		cerr << "Error: Wrong image size "<<width<<"x"<<height<<" ( you need: "<<SI_WIDTH<<"x"<<SI_HEIGHT<<")"<<endl;
		return 2;
	}

	while(getline(file, str_line, '\n')) {
		stringstream line(str_line);
		
		for(x = 0; x < SI_WIDTH; ++x) {
			line >> r; line >> b; line >> g;
			image[x][y].r = (uint)r;
			image[x][y].g = (uint)g;
			image[x][y].b = (uint)b;
		}
			
		y++;
	}

	file.close();
	return 0;
}
