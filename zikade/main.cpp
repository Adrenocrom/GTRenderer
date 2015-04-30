#include "zikade.h"

rgbWxH image;

int main(int argc, char* argv[]) {
	string sname 		= "scene.txt";
	string iname 		= "out.pbm";
	uint	 numSamples = 30;
	uint	 apxLevel	= 3;

	if(argc > 1) {
		sname = argv[1];
		if(argc > 2) {
			iname = argv[2];
			if(argc > 4) {
				numSamples = (uint) atoi(argv[3]);
				apxLevel	  = (uint) atoi(argv[4]);
			}
		}
	}

	zikade zi;
	zi.loadScene(sname.c_str());

	zi.setApproximationLevel(apxLevel);
	zi.setNumSamples(numSamples);

	zi.render(image);

	saveRgbWxHToPbm(image, iname.c_str());

	return 0;
}
