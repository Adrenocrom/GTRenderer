#include "zikade.h"

rgbWxH image;

int main(int argc, char* argv[]) {
	string sname = "scene.txt";
	string iname = "out.pbm";

	if(argc > 1) {
		sname = argv[1];
		if(argc > 2) iname = argv[2];
	}

	zikade zi;
	zi.loadScene(sname.c_str());
	//zi.loadScene("construct.txt");
	zi.render(image);

	saveRgbWxHToPbm(image, iname.c_str());

	return 0;
}
