#include "zikade.h"

rgbWxH image;

int main() {
	zikade zi;
	zi.loadScene("scene.txt");
	zi.render(image);

	saveRgbWxHToPbm(image, "image.pbm");

	return 0;
}
