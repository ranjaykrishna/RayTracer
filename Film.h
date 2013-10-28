#ifndef FILM_H
#define FILM_H

#include <FreeImage.h>
#include <string>
#include "Sample.h"
#include "Color.h"

class Film {
public:
	void commit(Sample& sample, Color& color);
	void writeImage(std::string filename);
	FIBITMAP* bitmap;
	int max_x;
	int max_y;
	Film(const int ww, const int hh);
};

#endif 