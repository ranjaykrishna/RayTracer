#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
	public:
		float x, y, z;
		Vertex(float, float, float);
		static float dot(Vertex& a, Vertex& b);
		static Vertex add(Vertex& a, Vertex& b);
		static Vertex subtract(Vertex& a, Vertex& b);
		static Vertex multiply(float mul, Vertex& v);
		static Vertex divide(float div, Vertex& v);
		static Vertex normalize(Vertex& v);
		static Vertex cross(Vertex& a, Vertex& b);
		static void print(Vertex& v);
}; 

#endif 