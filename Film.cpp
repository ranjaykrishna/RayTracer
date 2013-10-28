#include "Film.h"

char convertToPixel(float x) {
	if (x < 0.f) return ((unsigned char) (0.f));
	else if (x >= 1.f) return ((unsigned char) (255.f));
	else return ((unsigned char) (x * 255.f));
}

void Film::commit(Sample& sample, Color& color) {
	if (sample.x < 0 || sample.x >= max_x) return;
	else if (sample.y < 0 || sample.y >= max_y) return;
	RGBQUAD* pixel = new RGBQUAD();
	pixel->rgbRed = convertToPixel(color.b);
	pixel->rgbGreen = convertToPixel(color.g);
	pixel->rgbBlue = convertToPixel(color.r);
	//printf("PIXEL: %d, %d, COLOR: %f, %f, %f.\n", sample.x, sample.y, color.r, color.g, color.b);
	FreeImage_SetPixelColor ( bitmap , sample.x , sample.y , pixel );
}

void Film::writeImage(std::string filename) {
	FreeImage_Save(FIF_PNG, bitmap, ("testscenes/" + filename).c_str(), 0);
}

Film::Film(const int ww, const int hh) {
	bitmap = FreeImage_Allocate(ww, hh, 24);
	max_x = ww;
	max_y = hh;
}