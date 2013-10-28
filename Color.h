#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	float r;
	float g;
	float b;
	Color(float x, float y, float z);
	Color();
	static Color add(Color& color1, Color& color2);
	static Color multiply(float val, Color& color);
	static Color divide(float val, Color& color);
};

#endif