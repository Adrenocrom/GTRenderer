#include "zikade.h"

rgbWxH image;

void renderScene(int& argc, char* argv[]); 

int main(int argc, char* argv[]) {
	renderScene(argc, argv);

	return 0;
}

void renderScene(int& argc, char* argv[]) {
	string sname 		= "scene.txt";
	string iname 		= "out.pbm";
	uint	 numSamples = 30;
	uint	 apxLevel	= 3;

	if(argc > 1) {
		sname = argv[1];
		if(argc > 2) {
			iname = argv[2];
		}
	}

	zikade zi;
	zi.loadScene(sname.c_str());

	time_t begin, end;
	time(&begin);
	zi.render(image);
	time(&end);
	printf("time in seconds: %.2f\n", difftime(end, begin));

	saveRgbWxHToPbm(image, iname.c_str());
} 
