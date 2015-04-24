#include "zikade.h"

int main() {

	rgbWxH image;

	zikade zi;
	zi.loadScene("scene.txt");
	zi.render(image);

	saveRgbWxHToPbm(image, "image.pbm");

	return 0;
}
