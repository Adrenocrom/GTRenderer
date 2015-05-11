#include "zikade.h"

rgbWxH in1;
rgbWxH in2;
rgbWxH out;

real3 calcDifference();

int main(int argc, char* argv[]) {
	string str_in1; if(argc > 1) str_in1 = argv[1];
	string str_in2; if(argc > 2) str_in2 = argv[2];
	string str_out = "result.pbm"; if(argc > 3) str_out = argv[3];

	if(str_in1.empty() || str_in2.empty()) {
		cerr << "no filename insert"<<endl;
		return 1;
	}


	loadPbmToRgbWxH(in1, str_in1.c_str());
	loadPbmToRgbWxH(in2, str_in2.c_str());

	real3 r = calcDifference();
	r /= SI_WIDTH*SI_HEIGHT;
	
	saveRgbWxHToPbm(out, str_out.c_str());

	cout << "akkumulated error: "<<r.x<<" "<<r.y<<" "<<r.z<<endl;
	return 0;
}

real3 calcDifference() {
	real3 d, r;
	for(uint y = 0; y < SI_HEIGHT; ++y) {
		for(uint x = 0; x < SI_WIDTH; ++x) {
			d = in1[x][y] - in2[x][y];
			d.x = (real)abs(d.x);
			d.y = (real)abs(d.y);
			d.z = (real)abs(d.z);
			out[x][y] = d;
			r += d;
		}
	}

	return r;
}
