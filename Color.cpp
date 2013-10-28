#include "Color.h"

Color::Color() {

}

Color::Color(float x, float y, float z) {
	r = x;
	g = y;
	b = z;
}

Color Color::add(Color& color1, Color& color2) {
	Color* color = new Color(
		color1.r + color2.r,
		color1.g + color2.g,
		color1.b + color2.b);
	return *color;
}

Color Color::multiply(float val, Color& color) {
	Color* ret = new Color(
		color.r * val,
		color.g * val,
		color.b * val);
	return *ret;
}

Color Color::divide(float val, Color& color) {
	Color* ret = new Color(
		color.r / val,
		color.g / val,
		color.b / val);
	return *ret;
}