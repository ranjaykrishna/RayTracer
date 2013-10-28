#include <math.h>
#include <iostream>
#include "Vertex.h"

float Vertex::dot(Vertex& a, Vertex& b) {
	float ret = a.x * b.x + a.y * b.y + a.z * b.z;
	return ret;
}

Vertex Vertex::cross(Vertex& a, Vertex& b) {
	Vertex* ret = new Vertex::Vertex(
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
		);
	return *ret;
}

Vertex Vertex::add(Vertex& a, Vertex& b) {
	Vertex* ret = new Vertex::Vertex(a.x + b.x, a.y + b.y, a.z + b.z);
	return *ret;
}

Vertex Vertex::subtract(Vertex& a, Vertex& b) {
	Vertex* ret = new Vertex::Vertex(a.x - b.x, a.y - b.y, a.z - b.z);
	return *ret;
}

Vertex Vertex::multiply(float mul, Vertex& v) {
	Vertex* ret = new Vertex::Vertex(
		v.x * mul,
		v.y * mul,
		v.z * mul);
	return *ret;
}
Vertex Vertex::divide(float val, Vertex& v) {
	if (val == 0) {
		val = 1.f;
	}
	Vertex* ret = new Vertex::Vertex(
		v.x / val,
		v.y / val,
		v.z / val);
	return *ret;
}

Vertex Vertex::normalize(Vertex& v) {
	float magnitute = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	Vertex ret = Vertex::divide(magnitute, v);
	return ret;
}

Vertex::Vertex(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}

void Vertex::print(Vertex& v) {
	printf("%f, %f, %f.\n", v.x, v.y, v.z);
}