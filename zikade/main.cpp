#include "zikade.h"

rgbWxH image;

int main() {
	zikade zi;
	zi.loadScene("scene.txt");
	//zi.loadScene("construct.txt");
	zi.render(image);

	saveRgbWxHToPbm(image, "image.pbm");

	return 0;
}
